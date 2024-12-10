#include "MGXSUtils/MGUtils/MultiGroupDataGeneratorByNjoyInput.hpp"

using namespace frendy;

//Initialize static const value
const Real MultiGroupDataGeneratorByNjoyInput::suffix_za_id_def = 0.0;

//constructor
MultiGroupDataGeneratorByNjoyInput::MultiGroupDataGeneratorByNjoyInput(void)
{
  clear();
}

//destructor
MultiGroupDataGeneratorByNjoyInput::~MultiGroupDataGeneratorByNjoyInput(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorByNjoyInput::clear()
{
  conv_inp_obj.clear();

  read_groupr_obj.clear();

  vector<MatxsrInputReader>().swap(read_matxsr_obj);

  nucl_data_info_obj.clear();
  nucl_data_obj.clear();
  nucl_data_obj_tsl.clear();
  ace_data_obj_fast.clear();
  ace_data_obj_tsl.clear();
  ace_data_obj_dosi.clear();

  calc_flg      = 0;
  start_line_no = 0;

  input_file_name_njoy.clear();
  matxsr_line_no.clear();

  time_total = 0.0;

  endf_name.clear();
  pendf_name.clear();
  gendf_name_out.clear();
  title_vec.clear();
  mat_vec.clear();
  clr_obj.clear_vec_array2_real(temp_vec);
  clr_obj.clear_vec_array2_real(sigz_vec);

  //For thermal scattering law data
  tsl_data_flg = 0;
  tsl_mt_no.clear();
  tsl_ref_frame_flg.clear();

  //For dosimetry data
  dosi_data_flg = 0;
  mf_dosi.clear();
  mt_dosi.clear();
  clr_obj.clear_vec_array3_real(dosi_xs);

  gendf_obj.clear();
  matxs_obj.clear();
  clr_obj.clear_vec_array1_str(matxs_obj_name_list);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorByNjoyInput::generate_mg_data()
{
  if( calc_flg == 1 )
  {
    return;
  }
  calc_flg = 1;

  cout << "******************************* Multi-group XS file generation ********************************";
  cout << endl << endl;
  time_obj.output_current_time();

  boost::timer::cpu_timer timer_total;

  set_input_data();
  output_input_file_name();

  ofstream fout_gendf;
  fout_gendf.open(gendf_name_out.c_str());
  if( fout_gendf.fail() )
  {
    string class_name = "MultiGroupDataGeneratorByNjoyInput";
    string func_name  = "generate_mg_data()";

    string str_data = "  Output GENDF file name : " + gendf_name_out;

    vector<string> err_com;
    err_com.push_back("Output GENDF file can not be open.");
    err_com.push_back("Please check the file name, directory name or access authority.");
    err_com.push_back(str_data);

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  int mg_file_no = 1;
  int mat_no     = static_cast<int>(temp_vec.size());
  for(int i=0; i<mat_no; i++)
  {
    int temp_no = static_cast<int>(temp_vec[i].size());
    for(int j=0; j<temp_no; j++)
    {
      cout << "*** Processing condition of multigroup cross section generation ***" << endl;
      cout << "  MAT No.     = " << mat_vec[i]     << endl;
      cout << "  Temperature = " << temp_vec[i][j] << endl;
      cout << endl;

      //Check dosimetry
      dosi_data_flg = 0;
      vector<Integer> mf_list = read_groupr_obj.get_mf()[i][j];
      for(int i=0; i<static_cast<int>(mf_list.size()); i++)
      {
        if( mf_list[i] > 10000000 && mf_list[i] < 50000000 )
        {
          //1zzzaaam: nuclide production for zzzaaam subsection from file  3
          //2zzzaaam: nuclide production for zzzaaam subsection from file  6
          //3zzzaaam: nuclide production for zzzaaam subsection from file  9
          //4zzzaaam: nuclide production for zzzaaam subsection from file 10
          dosi_data_flg = 1;
          break;
        }
      }

      cout << "  Read PENDF file" << endl;
      set_nucl_data_obj(mat_vec[i], temp_vec[i][j]);

      cout << "  ACE file generation" << endl;
      ace_file_generation(i, j);
      //read_ace_file(i, j);  //For debug only
      cout << "  Multi-group XS file generation" << endl;
      mg_file_generation(i, j);

      if( mat_no == 1 && temp_no == 1 )
      {
        mg_file_no = -1;
      }

      cout << "  Output multi-group XS file" << endl;
      if( dosi_data_flg > 0 )
      {
        output_gendf_file_dosi(fout_gendf, i, j);
      }
      else
      {
        output_gendf_file(fout_gendf, i, j);
        output_matxs_file(mg_file_no);
      }
      mg_file_no++;
      cout << endl;

      nucl_data_obj.clear();
    }
  }

  //Write tape end
  EndfFileWriter efw_obj;
  fout_gendf << efw_obj.write_tape_end() << endl;
  fout_gendf.close();

  output_matxs_file_merge();

  time_total = static_cast<Integer>(timer_total.elapsed().wall * 1.0E-9);
  cout << "Total calculation time : " << time_total << " [s]" << endl;
  cout << endl;
  cout << "***********************************************************************************************";
  cout << endl << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorByNjoyInput::output_input_file_name()
{
  cout << "=== Nuclear data file information ===" << endl;
  cout << "  Input File Name          : " << input_file_name_njoy << endl;
  cout << "  ENDF  File Name          : " << endf_name            << endl;
  cout << "  PENDF File Name          : " << pendf_name           << endl;
  cout << "  GENDF File Name (out)    : " << gendf_name_out       << endl;

  int mat_no = static_cast<int>(temp_vec.size());
  cout << "  Number of Material data  : " << mat_no << endl;
  for(int i=0; i<mat_no; i++)
  {
    cout << "    Material number            : " << mat_vec[i] << endl;
    cout << "    Sigma zero data            :";
    for(int j=0; j<static_cast<int>(sigz_vec[i].size()); j++)
    {
      cout << " " << sigz_vec[i][j];
    }
    cout << endl;

    int temp_no = static_cast<int>(temp_vec[i].size());
    cout << "    Temperature [K]            :";
    for(int j=0; j<temp_no; j++)
    {
      cout << " " << temp_vec[i][j];
    }
    cout << endl;

    cout << endl;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorByNjoyInput::set_input_data()
{
  //Read groupr input file
  read_groupr_obj.read_input(input_file_name_njoy, start_line_no);

  int i_max = static_cast<int>(matxsr_line_no.size());
  read_matxsr_obj.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    read_matxsr_obj[i].read_input(input_file_name_njoy, matxsr_line_no[i]);
  }

  endf_name      = read_groupr_obj.get_endf_file_name();
  pendf_name     = read_groupr_obj.get_pendf_file_name();
  gendf_name_out = read_groupr_obj.get_gendf_file_name_out();
  title_vec      = read_groupr_obj.get_title();
  mat_vec        = read_groupr_obj.get_matb();
  temp_vec       = read_groupr_obj.get_temp();
  sigz_vec       = read_groupr_obj.get_sigz();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorByNjoyInput::set_nucl_data_obj(Integer mat_no, Real temp)
{
  Endf6FileStore    read_endf_obj;
  NuclearDataObject nucl_data_obj_pendf = read_endf_obj.get_nucl_data_obj(pendf_name, mat_no, temp);

  //Check tsl data or not
  NuclearReactionDataContainer nucl_reaction_data_obj = nucl_data_obj_pendf.get_nucl_reaction_data_obj();
  tsl_data_flg = 0;
  tsl_mt_no.clear();
  tsl_ref_frame_flg.clear();
  nucl_reaction_data_obj.clear();

  //For fast ace data generation
  nucl_data_obj = read_endf_obj.get_nucl_data_obj(endf_name, mat_no, 0.0);

  //Copy resonance data
  nucl_data_obj.set_reso_data_obj(nucl_data_obj_pendf.get_reso_data_obj());

  //Copy temperature and error data
  Real temp_val  = nucl_data_obj_pendf.get_general_data_obj().get_temp();
  Real error_val = nucl_data_obj_pendf.get_general_data_obj().get_error_value();

  GeneralDataContainer gen_obj = nucl_data_obj.get_general_data_obj();
  gen_obj.set_temp(temp_val);
  gen_obj.set_error_value(error_val);
  nucl_data_obj.set_general_data_obj(gen_obj);

  //Copy cross section data
  vector<CrossSectionDataContainer> xs_obj, xs_obj_mod;
  xs_obj = nucl_data_obj_pendf.get_nucl_reaction_data_obj().get_xs_data_obj();

  tsl_mt_no.clear();
  xs_obj_mod.clear();
  for(int i=0; i<static_cast<int>(xs_obj.size()); i++)
  {
    Integer react_type = xs_obj[i].get_reaction_type();
    xs_obj_mod.push_back(xs_obj[i]);
    if( react_type < 221 || react_type > 250 )
    {
      //No tsl data
    }
    else
    {
      tsl_data_flg = react_type;
      tsl_mt_no.push_back(react_type);

      Integer ref_flame_flg = nucl_data_obj_pendf.get_nucl_reaction_data_obj().get_product_distr_data_obj(react_type).get_ref_frame_flg();
      tsl_ref_frame_flg.push_back(ref_flame_flg); 
    }
  }

  nucl_reaction_data_obj = nucl_data_obj.get_nucl_reaction_data_obj();
  nucl_reaction_data_obj.set_xs_data_obj(xs_obj_mod);
  vector<CrossSectionDataContainer>().swap(xs_obj);
  vector<CrossSectionDataContainer>().swap(xs_obj_mod);

  //Set cross section data to NuclearDataObject
  nucl_data_obj.set_nucl_reaction_data_obj(nucl_reaction_data_obj);
  nucl_reaction_data_obj.clear();

  nucl_data_info_obj.set_nucl_data_obj(nucl_data_obj);

  if( tsl_data_flg > 0 )
  {
    if( check_tsl_data(nucl_data_obj_pendf) == 0 )
    {
      tsl_data_flg = 0;
    }
  }

  //For thermal ace data generation
  nucl_data_obj_tsl.clear();
  if( tsl_data_flg > 0 )
  {
    //Only PENDF file is required for thermal scattering law data. 
    nucl_data_obj_tsl = nucl_data_obj_pendf;
    nucl_data_info_obj.set_nucl_data_obj(nucl_data_obj_tsl);
  }
  nucl_data_obj_pendf.clear();  
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Integer MultiGroupDataGeneratorByNjoyInput::check_tsl_data(NuclearDataObject& pendf_obj)
{
  if ( static_cast<int>(tsl_mt_no.size()) == 0 )
  {
    //This data is not thermal scattering law data
    return 0;
  }
  else if ( static_cast<int>(tsl_mt_no.size()) != 1 )
  {
    //skip check tsl data (both elastic and inelastic scattering data are found)
    return 1000;
  }

  CrossSectionDataContainer xs_obj_tsl, xs_obj_ela;
  xs_obj_tsl = pendf_obj.get_nucl_reaction_data_obj().get_xs_data_obj(tsl_mt_no[0]);
  xs_obj_ela = pendf_obj.get_nucl_reaction_data_obj().get_xs_data_obj(2);

  vector<Real> ene_vec_tsl = xs_obj_tsl.get_xs_ene_data();
  vector<Real> xs_vec_tsl  = xs_obj_tsl.get_xs_data(); 
  vector<Real> ene_vec_ela = xs_obj_ela.get_xs_ene_data();
  vector<Real> xs_vec_ela  = xs_obj_ela.get_xs_data(); 
  if( static_cast<int>(ene_vec_ela.size()) == 0 &&
      static_cast<int>(xs_vec_ela.size())  == 0 )
  {
    //if pendf file does not have elastic scattering cross section data
    return 10000;
  }
      
  int i_max = static_cast<int>(ene_vec_tsl.size());
  Real ene_max_th = ene_vec_tsl[i_max-1];
  for(int i=i_max-1; i>=0; i--)
  {
    if( xs_vec_tsl[i] > min_value )
    {
      ene_max_th = ene_vec_tsl[i];
      break;
    }
  }

  TabInterpolator ti_obj;
  vector<Real> xs_dif;
  xs_dif.resize(i_max);

  //Comparison of thermal scattering cross section and elastic scattering cross section
  int dif_flg = 0;
  for(int i=0; i<i_max; i++)
  {
    if( ene_vec_tsl[i] < ene_max_th )
    {
      Real xs_val = 0.0;
      ti_obj.interpolation_1d(int_lin_lin, ene_vec_tsl[i], xs_val, ene_vec_ela, xs_vec_ela);

      xs_dif[i] = fabs((xs_val - xs_vec_tsl[i])/xs_vec_tsl[i]);
      if( xs_dif[i] > 1.0E-2 )
      {
        dif_flg++;
      }
    }
  }

  return dif_flg;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorByNjoyInput::read_ace_file(int i, int j)
{
  string ace_file_name_fast = read_groupr_obj.get_ace_file_name();
  cout << "  Read ACE file (fast) : " << ace_file_name_fast << endl;

  FastAceDataParser read_obj_fast;
  read_obj_fast.set_file_name(ace_file_name_fast);
  ace_data_obj_fast = read_obj_fast.get_ace_data_obj();
  read_obj_fast.clear();

  if( tsl_data_flg > 0 )
  {
    string ace_file_name_tsl = read_groupr_obj.get_ace_file_name() + ".tsl";
    cout << "  Read ACE file (tsl)  : " << ace_file_name_tsl << endl;

    ThermalScatterAceDataParser read_obj_tsl;
    read_obj_tsl.set_file_name(ace_file_name_tsl);
    ace_data_obj_tsl = read_obj_tsl.get_ace_data_obj();
    read_obj_tsl.clear();
  }

  if( dosi_data_flg > 0 )
  {
    string ace_file_name_dosi = read_groupr_obj.get_ace_file_name() + ".dosi";
    cout << "  Read ACE file (dosi) : " << ace_file_name_dosi << endl;

    DosimetryAceDataParser read_obj_dosi;
    read_obj_dosi.set_file_name(ace_file_name_dosi);
    ace_data_obj_dosi = read_obj_dosi.get_ace_data_obj();
    read_obj_dosi.clear();
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorByNjoyInput::ace_file_generation(int i, int j)
{
  AceDataGenerator ace_gen_obj;

  //*** Set input data ***//
  //For input data (Common)
  ace_gen_obj.set_ace_file_name(read_groupr_obj.get_ace_file_name());
  ace_gen_obj.set_mcnp_dir(read_groupr_obj.get_mcnp_dir_name());
  ace_gen_obj.set_mat(mat_vec[i]);
  ace_gen_obj.set_temp(temp_vec[i][j]);
  ace_gen_obj.set_suffix_za_id(suffix_za_id_def);

  //*** Set nuclear data object ***//
  ace_gen_obj.set_nucl_data_obj(nucl_data_obj);

  //For input data (Fast)
  ace_gen_obj.set_opt_run(1); //fast

  //*** Running ACE file generation ***
  ace_data_obj_fast = ace_gen_obj.get_ace_data_obj().get_fast_ace_data_obj();
  ace_gen_obj.clear();

  if( tsl_data_flg > 0 )
  {
    string ace_file_name_tsl = read_groupr_obj.get_ace_file_name() + ".tsl";
    string mcnp_dir_name_tsl = read_groupr_obj.get_mcnp_dir_name() + ".tsl";

    //*** Set input data ***//
    //For input data (Common)
    ace_gen_obj.set_ace_file_name(ace_file_name_tsl);
    ace_gen_obj.set_mcnp_dir(mcnp_dir_name_tsl);
    ace_gen_obj.set_mat(mat_vec[i]);
    ace_gen_obj.set_temp(temp_vec[i][j]);
    ace_gen_obj.set_suffix_za_id(suffix_za_id_def);

    //*** Set nuclear data object ***//
    ace_gen_obj.set_nucl_data_obj(nucl_data_obj_tsl);

    //For input data (Thermal scattering law)
    ace_gen_obj.set_opt_run(2); //thermal (tsl)
    ace_gen_obj.set_opt_weight(f_inp_common_obj.tabulated_weight); //iwt=2
    ace_gen_obj.set_ene_max_th(nucl_data_info_obj.get_thermal_cutoff());
    set_thermal_data(i, j, ace_gen_obj);

    for(int i=0; i<static_cast<int>(tsl_mt_no.size()); i++)
    {
      if( tsl_ref_frame_flg[i] == 5 )
      {
        ace_gen_obj.set_mt_inelastic(tsl_mt_no[i]);
        ace_gen_obj.set_bin_no(f_inp_common_obj.get_equi_probable_angle_no_def());
      }
      else if( tsl_ref_frame_flg[i] == 6 )
      {
        ace_gen_obj.set_mt_elastic(tsl_mt_no[i]);
        ace_gen_obj.set_elastic_flg(1); //incoherent elastic
      }
      else if( tsl_ref_frame_flg[i] == 7 )
      {
        ace_gen_obj.set_mt_elastic(tsl_mt_no[i]);
        ace_gen_obj.set_elastic_flg(0); //coherent elastic
      }
    }

    //*** Running ACE file generation ***
    ace_data_obj_tsl = ace_gen_obj.get_ace_data_obj().get_thermal_scat_ace_data_obj();
    ace_gen_obj.clear();
  }

  if( dosi_data_flg > 0 )
  {
    string ace_file_name_dosi = read_groupr_obj.get_ace_file_name() + ".dosi";
    string mcnp_dir_name_dosi = read_groupr_obj.get_mcnp_dir_name() + ".dosi";

    //*** Set input data ***//
    //For input data (Common)
    ace_gen_obj.set_ace_file_name(ace_file_name_dosi);
    ace_gen_obj.set_mcnp_dir(mcnp_dir_name_dosi);
    ace_gen_obj.set_mat(mat_vec[i]);
    ace_gen_obj.set_temp(temp_vec[i][j]);
    ace_gen_obj.set_suffix_za_id(suffix_za_id_def);

    //*** Set nuclear data object ***//
    ace_gen_obj.set_nucl_data_obj(nucl_data_obj);

    //For input data (Fast)
    ace_gen_obj.set_opt_run(3); //dosimetry

    //*** Running ACE file generation ***
    ace_data_obj_dosi = ace_gen_obj.get_ace_data_obj().get_dosimetry_ace_data_obj();
    ace_gen_obj.clear();
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorByNjoyInput::set_thermal_data(int i, int j, AceDataGenerator& ace_gen_obj)
{
  //Get thermal za_id name (e.g., lwtr)
  string za_id_name = "tsl";
  ace_gen_obj.set_thermal_za_id_name(za_id_name);

  //The atom_no_th value of some materials, e.g., benzene and BeinBeo of old library is 2.
  //ACE file generator compares incoherent inelastic scattering cross section and elastic
  //scattering cross section (MT=2) at the highest energy of the incoherent inelastic
  //scattering cross section. If the difference between incoherent inelastic scattering
  //cross section and MT=2, the atom_no_th value is modified.
  ace_gen_obj.set_atom_no_th(1);

  Integer mod_za_val = static_cast<Integer>(round(nucl_data_obj.get_general_data_obj().get_mat_data()));
  vector<Integer> mod_za_vec;
  mod_za_vec.clear();
  mod_za_vec.push_back(mod_za_val);
  ace_gen_obj.set_mod_za(mod_za_vec);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorByNjoyInput::mg_file_generation(int i, int j)
{
  FMGen::FMGenerator fm_gen;

  set_mg_input(i, j, fm_gen);

  set_ace_file_data(i, j, fm_gen);

  fm_gen.data_container.checkACEFiles();
  fm_gen.data_container.readAndSetUFEnergyGroupStructure();
  fm_gen.data_container.doInitialize();

  fm_gen.run();

  run_mg_photon_production(fm_gen);
  if( dosi_data_flg > 0 )
  {
    run_mg_dosimetry_production(i, j, fm_gen);
  }
  ace_data_obj_fast.clear();
  ace_data_obj_dosi.clear();

  output_mg_file_data(i, j, fm_gen);

  fm_gen.data_container.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorByNjoyInput::set_mg_input(int i, int j, FMGen::FMGenerator& fm_gen)
{
  conv_inp_obj.clear();

  MatxsrInputReader                      matxsr_inp_obj_dummy;
  matxsr_inp_obj_dummy.clear();

  conv_inp_obj.set_input_obj_njoy(i, j, nucl_data_info_obj, read_groupr_obj, matxsr_inp_obj_dummy,
                                  tsl_data_flg, ace_data_obj_fast, ace_data_obj_tsl);

  //Output input data of FRENDY/MG
  conv_inp_obj.output_input_data();

  //stab for frendy integration
  map<string, vector<string> > input_data = conv_inp_obj.get_input_data_map();
  fm_gen.readInputData(input_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorByNjoyInput::set_ace_file_data(int i, int j, FMGen::FMGenerator& fm_gen)
{
  string zaid;
  vector<string> _title;
  vector<int> _izaw;
  vector<int> _nxs;
  vector<int> _jxs;
  vector<double> _xss;

  //For fast
  FastAceDataWriter ace_wri_obj;
  ace_wri_obj.set_ace_data_obj(ace_data_obj_fast);
  ace_wri_obj.get_ace_data_for_mg(_title, _izaw, _nxs, _jxs, _xss);
  ace_wri_obj.clear();
  //ace_data_obj_fast.clear();

  //zaid is the first data of _title[0]
  zaid = str_obj.trim_space(_title[0]);
  string::size_type zaid_end_pos = zaid.find_first_of(" ");
  if( zaid_end_pos != string::npos )
  {
    zaid = zaid.substr(0, static_cast<int>(zaid_end_pos));
  }

  fm_gen.data_container.setACEFileData(zaid, _title, _izaw, _nxs, _jxs, _xss);

  //For thermal scattering law data
  if( tsl_data_flg > 0 )
  {
    ThermalScatterAceDataWriter ace_wri_obj_tsl;
    ace_wri_obj_tsl.set_ace_data_obj(ace_data_obj_tsl);
    ace_wri_obj_tsl.get_ace_data_for_mg(_title, _izaw, _nxs, _jxs, _xss);
    ace_wri_obj_tsl.clear();
    ace_data_obj_tsl.clear();

    //zaid is the first data of _title[0]
    zaid = str_obj.trim_space(_title[0]);
    string::size_type zaid_end_pos = zaid.find_first_of(" ");
    if( zaid_end_pos != string::npos )
    {
      zaid = zaid.substr(0, static_cast<int>(zaid_end_pos));
    }

    fm_gen.data_container.setACEFileData(zaid, _title, _izaw, _nxs, _jxs, _xss);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorByNjoyInput::output_mg_file_data(int i, int j, FMGen::FMGenerator& fm_gen)
{
  map<string, string>::iterator it;
  for (it  = fm_gen.data_container.output_list_data.begin();
       it != fm_gen.data_container.output_list_data.end(); it++)
  {
    string wk = it->first;

    //Get MATXS data
    if (wk.substr(0, 7) == "FMMatxs")
    {
      //Get string data of MATXS file
      vector<string> matxs_data_str = str_obj.divide_string_data_by_linefeed_code
                                        (fm_gen.data_container.output_list_data[wk]);

      //Read MATXS file
      MatxsParser read_matxs_obj;
      read_matxs_obj.set_text(matxs_data_str);
      matxs_obj = read_matxs_obj.get_matxs_obj();
      read_matxs_obj.clear();
      clr_obj.clear_vec_array1_str(matxs_data_str);

      //Modify temperature
      vector<MatxsMaterialData> matxs_mat_obj = matxs_obj.get_mat_obj();
      for(int k=0; k<static_cast<int>(matxs_mat_obj.size()); k++)
      {
        vector<Real> temp_matxs = matxs_mat_obj[k].get_temp();
        for(int l=0; l<static_cast<int>(temp_matxs.size()); l++)
        {
          Real temp_dif = 1.0E-3;
          if( fabs(temp_matxs[l]) > min_value )
          {
            temp_dif *= fabs(temp_matxs[l]);
          }
          if( fabs(temp_matxs[l] - temp_vec[i][j]) < temp_dif )
          {
            temp_matxs[l] = temp_vec[i][j];
          }
        }
        matxs_mat_obj[k].set_temp(temp_matxs);
        temp_matxs.clear();
      }
      matxs_obj.set_mat_obj(matxs_mat_obj);
      vector<MatxsMaterialData>().swap(matxs_mat_obj);

      //Modify hmatn
      if( static_cast<int>(tsl_mt_no.size()) > 0 )
      {
        matxs_obj.mod_tsl_name(tsl_mt_no[0]);
      }

      //Merge photon production data
      Real awr_matxs = matxs_obj.get_mat_obj()[0].get_amass();
      Real awr_photon = g_prod_obj.get_awr_val();
      if( fabs(awr_matxs - awr_photon) < fabs(awr_photon * 1.0E-6) )
      {
        vector<GMF16Parser> mf16_vec = g_prod_obj.get_mf16_data();
        vector<Real>        mg_ein   = conv_inp_obj.get_multi_group();
        vector<Real>        mg_eout  = conv_inp_obj.get_multi_group_gam();

        matxs_obj.add_photon_production_data(mf16_vec, mg_ein, mg_eout);

        vector<GMF16Parser>().swap(mf16_vec);
        mg_ein.clear();
        mg_eout.clear();
      }
    }

    //Get GENDF data
    if (wk.substr(0, 7) == "FMGENDF")
    {
      //Get string data of GENDF file
      vector<string> gendf_data_str = str_obj.divide_string_data_by_linefeed_code
                                        (fm_gen.data_container.output_list_data[wk]);

      //Read GENDF file
      gendf_obj.set_text(gendf_data_str);
      clr_obj.clear_vec_array1_str(gendf_data_str);

      //Merge photon production data
      g_prod_obj.merge_gendf(gendf_obj);

      //Modify material number and temperature
      gendf_obj.set_mat_no(nucl_data_info_obj.get_mat_no());
      gendf_obj.mod_temp(temp_vec[i][j]);
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorByNjoyInput::run_mg_photon_production(FMGen::FMGenerator& fm_gen)
{
  vector<Real>          ene_vec   = fm_gen.data_container.uf_energy_boundary;
  vector<vector<Real> > flux_vec  = fm_gen.data_container.uf_flux;
  vector<vector<Real> > st_sb_vec = fm_gen.data_container.uf_sig_total_sigb;
  if( static_cast<int>(flux_vec.size()) == 0 )
  {
    flux_vec = fm_gen.data_container.uf_flux_nr;
  }

  vector<vector<Real> > flux_vec_mod  = flux_vec;
  vector<vector<Real> > st_sb_vec_mod = st_sb_vec;
  int b_no = static_cast<int>(st_sb_vec_mod.size());
  if( b_no > 1 )
  {
    flux_vec_mod.resize(1);
    flux_vec_mod[0] = flux_vec[0];

    st_sb_vec_mod.resize(1);
    st_sb_vec_mod[0] = st_sb_vec[0];
  }
  flux_vec.clear();
  st_sb_vec.clear();

  vector<Real> mg_ein  = conv_inp_obj.get_multi_group();
  vector<Real> mg_eout = conv_inp_obj.get_multi_group_gam();
  int          pl_no   = conv_inp_obj.get_max_pl();
//  int          pl_no   = fm_gen.data_container.max_pl;
//  int pl_no = 0;
  g_prod_obj.calc_photon_production_data(ace_data_obj_fast, ene_vec, flux_vec_mod, st_sb_vec_mod,
                                         mg_ein, mg_eout, pl_no);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorByNjoyInput::run_mg_dosimetry_production(int i, int j,
                                                                     FMGen::FMGenerator& fm_gen)
{
  vector<Integer> mf_list, mt_list;
  mf_list = read_groupr_obj.get_mf()[i][j];
  mt_list = read_groupr_obj.get_mt()[i][j];
  mf_dosi.clear();
  mt_dosi.clear();

  int k_max = static_cast<int>(mf_list.size());
  for(int k=0; k<k_max; k++)
  {
    if( mf_list[k] > 10000000 && mf_list[k] < 50000000 )
    {
      //1zzzaaam: nuclide production for zzzaaam subsection from file  3
      //2zzzaaam: nuclide production for zzzaaam subsection from file  6
      //3zzzaaam: nuclide production for zzzaaam subsection from file  9
      //4zzzaaam: nuclide production for zzzaaam subsection from file 10
      mf_dosi.push_back(mf_list[k]);
      mt_dosi.push_back(mt_list[k]);
    }
  }

  k_max = static_cast<int>(mf_dosi.size());
  if( k_max == 0 )
  {
    return;
  }

  vector<Real>          ene_vec   = fm_gen.data_container.uf_energy_boundary;
  vector<vector<Real> > flux_vec  = fm_gen.data_container.uf_flux;
  vector<vector<Real> > st_sb_vec = fm_gen.data_container.uf_sig_total_sigb;
  if( static_cast<int>(flux_vec.size()) == 0 )
  {
    flux_vec = fm_gen.data_container.uf_flux_nr;
  }

  int b_no = static_cast<int>(flux_vec.size());
  vector<vector<Real> > flux_vec_mod  = flux_vec;
  vector<vector<Real> > st_sb_vec_mod = st_sb_vec;
  if( b_no > 1 )
  {
    flux_vec_mod.resize(1);
    flux_vec_mod[0] = flux_vec[0];

    st_sb_vec_mod.resize(1);
    st_sb_vec_mod[0] = st_sb_vec[0];
  }
  flux_vec  = flux_vec_mod;
  st_sb_vec = st_sb_vec_mod;
  flux_vec_mod.clear();
  st_sb_vec_mod.clear();

  g_prod_obj.modify_flux(ene_vec, flux_vec, st_sb_vec);


  MGUtils  mg_obj;
  b_no = static_cast<int>(flux_vec.size());
  vector<Real> mg_ein  = conv_inp_obj.get_multi_group();
  vector<Real> mg_eout = conv_inp_obj.get_multi_group_gam();

  dosi_xs.resize(k_max);
  for(int k=0; k<k_max; k++)
  {
    vector<Real>          dosi_xs_fine_ene, ace_ene_grid, ace_dosi_xs;
    vector<vector<Real> > dosi_xs_fine;
    dosi_xs_fine.resize(b_no);

    get_dosi_xs_data(mf_dosi[k], mt_dosi[k], ace_ene_grid, ace_dosi_xs);

    //Modify unit of ace_ene_grid (MeV -> eV)
    for(int l=0; l<static_cast<int>(ace_ene_grid.size()); l++)
    {
      ace_ene_grid[l] *= unit_mega;
    }

    //Multigroup cross section generation using the MGUtils class.
    dosi_xs[k].resize(b_no);
    for(int b=0; b<b_no; b++)
    {
      mg_obj.calc_mg_xs(ene_vec, flux_vec[b], ace_ene_grid, ace_dosi_xs, mg_ein, dosi_xs[k][b]);

      vector<Real> dosi_xs_const, dosi_xs_1e;
      mg_obj.calc_mg_xs_with_const(ace_ene_grid, ace_dosi_xs, mg_ein, dosi_xs_const);
      mg_obj.calc_mg_xs_with_1e(ace_ene_grid, ace_dosi_xs, mg_ein, dosi_xs_1e);
    }
    ace_ene_grid.clear();
    ace_dosi_xs.clear();
    dosi_xs_fine_ene.clear();
    clr_obj.clear_vec_array2_real(dosi_xs_fine);
  }
  mg_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorByNjoyInput::get_dosi_xs_data 
                                           (int mf, int mt, vector<Real>& dosi_ene_vec, vector<Real>& dosi_xs_vec)
{
  dosi_ene_vec.clear();
  dosi_xs_vec.clear();

  //mf = 1zzzaaam or 3zzzaaam or 4zzzaaam
  int mf_flg    =  mf/10000000;
  int state_val =  mf%10;

  if( mf_flg != 1 && mf_flg != 3 && mf_flg != 4 )
  {
    string class_name = "MultiGroupDataGeneratorByNjoyInput";
    string func_name  = "get_dosi_xs_data";

    ostringstream oss01;
    oss01 << mf;
    string str01 = "MF value : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str01);
    err_com.push_back("");
    err_com.push_back("This MF value is not available in this program.");
    err_com.push_back("The available MF value is as follows:");
    err_com.push_back("  1zzzaaam (subsection from file 3)");
    err_com.push_back("  3zzzaaam (subsection from file 9)");
    err_com.push_back("  4zzzaaam (subsection from file 10)");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //For cross section (MF=3)
  vector<Integer>          mt_vec   = ace_data_obj_dosi.get_reaction_xs_reaction_type();
  vector<vector<Integer> > xs_range = ace_data_obj_dosi.get_reaction_xs_range_data();
  vector<vector<Integer> > xs_int   = ace_data_obj_dosi.get_reaction_xs_int_data();
  vector<vector<Real> >    xs_ene   = ace_data_obj_dosi.get_reaction_xs_ene_data();
  vector<vector<Real> >    xs_vec   = ace_data_obj_dosi.get_reaction_xs_data();

  int mt_pos = -1;
  for(int i=0; i<static_cast<int>(mt_vec.size()); i++)
  {
    if( mt_vec[i] == mt )
    {
      mt_pos = i;
      break;
    }
  }
  if( mt_pos < 0 )
  {
    if( mf_flg == 1 && mf_flg == 3 ) //subsection from file 3 or 9
    {
      string class_name = "MultiGroupDataGeneratorByNjoyInput";
      string func_name  = "get_dosi_xs_data";

      ostringstream oss01;
      oss01 << mt;
      string str01 = "MT value : " + oss01.str();

      vector<string> err_com;
      err_com.push_back(str01);
      err_com.push_back("");
      err_com.push_back("This MT value is not found in the ACE file.");
      err_com.push_back("Available MT value in the ACE file is as follows:");
      for(int i=0; i<static_cast<int>(mt_vec.size()); i++)
      {
        ostringstream oss02;
        oss02 << mt_vec[i];
        string str02 = "  " + oss02.str();
        err_com.push_back(str02);
      }
      err_com.push_back("This MT value is skipped.");

      err_obj.output_caution(class_name, func_name, err_com);
      return;
    }
  }
  else //if( mt_pos >= 0 )
  {
    //Linerize cross section data
    LinearizeTabData lin_tab_obj;
    lin_tab_obj.linearize_tab1_data(xs_range[mt_pos], xs_int[mt_pos], xs_ene[mt_pos], xs_vec[mt_pos]);

    //1zzzaaam (subsection from file 3)
    if( mf_flg == 1 ) //subsection from file 3
    {
      dosi_ene_vec = xs_ene[mt_pos];
      dosi_xs_vec  = xs_vec[mt_pos];
      return;
    }
  }


  //For production cross section (MF10 = MF3 * MF9)
  vector<vector<Integer> > state_no = ace_data_obj_dosi.get_production_xs_state_no_product();
  int s_pos_i = -1;
  int s_pos_j = -1;
  int i_max_s = static_cast<int>(state_no.size());
  for(int i=0; i<i_max_s; i++)
  {
    int j_max_s = static_cast<int>(state_no[i].size());
    for(int j=0; j<j_max_s; j++)
    {
      if( state_no[i][j]%1000 == mt && state_no[i][j]/1000 - 10 == state_val )
      {
        s_pos_i = i;
        s_pos_j = j;
        break;
      }
    }

    if( s_pos_i >= 0 && s_pos_j >= 0 ) break;
  }

  if( s_pos_i < 0 && s_pos_j < 0 )
  {
    string class_name = "MultiGroupDataGeneratorByNjoyInput";
    string func_name  = "get_dosi_xs_data";

    ostringstream oss01, oss02, oss03;
    oss01 << mt;
    oss02 << mf%10000000;
    oss03 << mf%10;
    string str01 = "MT value      : " + oss01.str();
    string str02 = "zzzaaam value : " + oss02.str();
    string str03 = "state value   : " + oss03.str();

    vector<string> err_com;
    err_com.push_back(str01);
    err_com.push_back(str02);
    err_com.push_back(str03);
    err_com.push_back("");
    err_com.push_back("This MT value and/or state value (m in zzzaaam) are not found in the ACE file.");
    err_com.push_back("Available MT value ans state value pairs are as follows:");
    int i_max_s = static_cast<int>(state_no.size());
    for(int i=0; i<i_max_s; i++)
    {
      int j_max_s = static_cast<int>(state_no[i].size());
      for(int j=0; j<j_max_s; j++)
      {
        ostringstream oss10, oss11;
        oss10 << state_no[i][j]%1000;
        oss11 << state_no[i][j]/1000 - 10;
        string str10 = "  MT = " + oss10.str() + " / state = " + oss11.str();
        err_com.push_back(str10);
      }
    }
    err_com.push_back("This zzzaaam value is skipped.");

    err_obj.output_caution(class_name, func_name, err_com);
    return;
  }

  vector<Integer> prod_range = ace_data_obj_dosi.get_production_xs_range_data()[s_pos_i][s_pos_j];
  vector<Integer> prod_int   = ace_data_obj_dosi.get_production_xs_int_data()[s_pos_i][s_pos_j];
  vector<Real>    prod_ene   = ace_data_obj_dosi.get_production_xs_ene_data()[s_pos_i][s_pos_j];
  vector<Real>    prod_vec   = ace_data_obj_dosi.get_production_xs_data()[s_pos_i][s_pos_j];


  //Linerize production cross section data
  LinearizeTabData lin_tab_obj;
  lin_tab_obj.linearize_tab1_data(prod_range, prod_int, prod_ene, prod_vec);

  //4zzzaaam (subsection from file 10) and 3zzzaaam (subsection from file 9)
  //NJOY outputs cross section even if mfd=3zzzaaam
  dosi_ene_vec = prod_ene;
  dosi_xs_vec  = prod_vec;


  //3zzzaaam (subsection from file 9)
//  if( mf_flg == 3 ) //subsection from file 9
//  {
//    //MF9 = MF10 / MF3
//    TabInterpolator ti_obj;
//    for(int i=0; i<static_cast<int>(dosi_ene_vec.size()); i++)
//    {
//      Real ene_val = dosi_ene_vec[i];
//      Real xs_val  = 0.0;
//      ti_obj.interpolation_1d(int_lin_lin, ene_val, xs_val, xs_ene[mt_pos], xs_vec[mt_pos]);
//
//      if( xs_val < min_sig_val )
//      {
//        xs_val = min_sig_val;
//      }
//      dosi_xs_vec[i] /= xs_val;
//    }
//  }

  clr_obj.clear_vec_array2_int(xs_range);
  clr_obj.clear_vec_array2_int(xs_int);
  clr_obj.clear_vec_array2_real(xs_ene);
  clr_obj.clear_vec_array2_real(xs_vec);
  clr_obj.clear_vec_array2_int(state_no);
  prod_range.clear();
  prod_int.clear();
  prod_ene.clear();
  prod_vec.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorByNjoyInput::output_gendf_file_dosi(ofstream& fout_gendf, int i, int j)
{
  GendfParser gendf_obj_dosi;
  gendf_obj_dosi.clear();
  gendf_obj_dosi.set_mat_no( gendf_obj.get_mat_no() );
  gendf_obj_dosi.set_mf01_mt451_data( gendf_obj.get_mf01_mt451_data() );

  vector<GMF03Parser> mf03_vec, mf03_vec_ori;
  mf03_vec_ori = gendf_obj.get_mf03_data();
  mf03_vec.clear();

  GMF03Parser mf03_ori;
  mf03_ori.clear();
  for(int k=0; k<static_cast<int>(mf03_vec_ori.size()); k++)
  {
    if( static_cast<int>(mf03_vec_ori[k].get_FLUX().size()) > 0 )
    {
      mf03_ori = mf03_vec_ori[k];
      break;
    }   
  }
  mf03_vec_ori.clear();

  vector<vector<vector<Real> > > mf03_flux = mf03_ori.get_FLUX();

  MGUtils  mg_obj;
  int k_max = static_cast<int>(mt_dosi.size());
  for(int k=0; k<k_max; k++)
  {
    if( static_cast<int>(dosi_xs[k].size()) > 0 )
    {
      GMF03Parser mf03_dosi = mf03_ori;
      vector<vector<vector<Real> > > xs_mod;
      vector<int> ig_vec, ng2_vec, ig2lo_vec;
      ig_vec.clear();
      ng2_vec.clear();
      ig2lo_vec.clear();
      xs_mod = mg_obj.remove_zero_xs_data(dosi_xs[k], ig_vec, ng2_vec, ig2lo_vec);

      if( static_cast<int>(xs_mod.size()) > 0 )
      {
        int ein_no = static_cast<int>(dosi_xs[k][0].size());
        int bg_no  = static_cast<int>(dosi_xs[k].size());
        int pl_no  = 1;

        GMF03Parser mf03_vec_each;
        mf03_vec_each.set_mt_no(mt_dosi[k]);
        mf03_vec_each.set_NL(pl_no);
        mf03_vec_each.set_NSIGZ(bg_no);
        mf03_vec_each.set_LR(0);
        mf03_vec_each.set_NGN(ein_no);

        mf03_vec_each.set_NG2(ng2_vec);
        mf03_vec_each.set_IG2LO(ig2lo_vec);
        mf03_vec_each.set_IG(ig_vec);
        mf03_vec_each.set_SIG(xs_mod);

        mf03_vec_each.set_mat_no(mf03_ori.get_mat_no());
        mf03_vec_each.set_ZA(mf03_ori.get_ZA());
        mf03_vec_each.set_AWR(mf03_ori.get_AWR());
        mf03_vec_each.set_TEMP(mf03_ori.get_TEMP());
        mf03_vec_each.set_FLUX(mg_obj.modify_flux(mf03_flux, ig_vec, bg_no, pl_no));

        mf03_vec.push_back(mf03_vec_each);
        mf03_vec_each.clear();
      }
    }
  }
  clr_obj.clear_vec_array3_real(mf03_flux);

  gendf_obj_dosi.set_mf03_data(mf03_vec);
  mf03_vec.clear();

  gendf_obj = gendf_obj_dosi;
  gendf_obj_dosi.clear();

  //Write GENDF
  write_gendf_file(fout_gendf, i, j);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorByNjoyInput::output_gendf_file(ofstream& fout_gendf, int i, int j)
{
  vector<Integer> mf_list = read_groupr_obj.get_mf()[i][j];
  vector<Integer> mt_list = read_groupr_obj.get_mt()[i][j];

  check_mf_mt_list(mf_list, mt_list, gendf_obj);
  modify_gendf(mf_list, mt_list, gendf_obj);

  //Modify LR flag in GMF03
  gendf_obj.mod_reaction_flg(nucl_data_obj);

  //Write GENDF
  write_gendf_file(fout_gendf, i, j);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorByNjoyInput::write_gendf_file(ofstream& fout_gendf, int i, int j)
{
  GendfWriter    wri_obj;
  vector<string> gendf_data_str;
  wri_obj.set_gendf_parser(gendf_obj);
  if( i == 0 && j == 0 )
  {
    if( static_cast<int>(title_vec.size()) > 0 )
    {
      wri_obj.set_gendf_label(title_vec[0]);
    }
    gendf_data_str = wri_obj.get_gendf_text_data();
  }
  else
  {
    gendf_data_str = wri_obj.get_gendf_text_data_without_label();
  }
  wri_obj.clear();

  int k_max = static_cast<int>(gendf_data_str.size());
  for(int k=0; k<k_max; k++)
  {
    fout_gendf << gendf_data_str[k] << endl;
  }
  clr_obj.clear_vec_array1_str(gendf_data_str);

  gendf_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorByNjoyInput::check_mf_mt_list
  (vector<Integer> mf_list, vector<Integer> mt_list, frendy::GendfParser& gendf_data)
{
  vector<Integer> no_mf_list, no_mt_list;
  no_mf_list.clear();
  no_mt_list.clear();

  int i_max = static_cast<int>(mf_list.size());
  for(int i=0; i<i_max; i++)
  {
    if( mf_list[i] == 0 || mt_list[i] == 0 )
    {
      continue;
    }
    else if( mt_list[i] < 0 )
    {
      mt_list[i] *= -1;
    }

    if( mf_list[i] == 3 )
    {
      if( gendf_data.get_mf03_data(mt_list[i]).get_mt_no() != mt_list[i] )
      {
        no_mf_list.push_back(mf_list[i]);
        no_mt_list.push_back(mt_list[i]);
      }
    }

    if( mf_list[i] == 5 || mf_list[i] == 6 )
    {
      if( gendf_data.get_mf05_data(mt_list[i]).get_mt_no() != mt_list[i] )
      {
        if(   mf_list[i] == 5 ||
            ( mf_list[i] == 6 && gendf_data.get_mf06_data(mt_list[i]).get_mt_no() != mt_list[i] ) )
        {
          no_mf_list.push_back(mf_list[i]);
          no_mt_list.push_back(mt_list[i]);
        }
      }
    }

    if( mf_list[i] == 5 || mf_list[i] == 6 || mf_list[i] == 8 )
    {
      if( gendf_data.get_mf06_data(mt_list[i]).get_mt_no() != mt_list[i] )
      {
        if(   mf_list[i] == 6 || mf_list[i] == 8 ||
            ( mf_list[i] == 5 && gendf_data.get_mf05_data(mt_list[i]).get_mt_no() != mt_list[i] ) )
        {
          no_mf_list.push_back(mf_list[i]);
          no_mt_list.push_back(mt_list[i]);
        }
      }
    }

    if( mf_list[i] == 12 || mf_list[i] == 13 )
    {
      if( gendf_data.get_mf13_data(mt_list[i]).get_mt_no() != mt_list[i] )
      {
        no_mf_list.push_back(mf_list[i]);
        no_mt_list.push_back(mt_list[i]);
      }
    }

    if( mf_list[i] >= 15 && mf_list[i] <= 18 )
    {
      if( gendf_data.get_mf16_data(mt_list[i]).get_mt_no() != mt_list[i] )
      {
        no_mf_list.push_back(mf_list[i]);
        no_mt_list.push_back(mt_list[i]);
      }
    }
  }

  i_max = static_cast<int>(no_mf_list.size());
  if( i_max > 0 )
  {
    string class_name = "MultiGroupDataGeneratorByNjoyInput";
    string func_name  = "check_mf_mt_list";

    vector<string> err_com;
    err_com.push_back("The following MF/MT data are set in GROUPR input file.");
    err_com.push_back("However, the corresponding MF/MT data are not found in the GENDF file.");
    err_com.push_back("Output of these MF/MT data are skipped.");
    err_com.push_back("");
    err_com.push_back("MF / MT data list");

    for(int i=0; i<i_max; i++)
    {
      ostringstream oss01, oss02;
      oss01 << no_mf_list[i];
      oss02 << no_mt_list[i];
      string str_data01 = "    MF = " + oss01.str() + ", MT = " + oss02.str();
      err_com.push_back(str_data01);
    }
    err_obj.output_caution(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorByNjoyInput::modify_gendf
  (vector<Integer> mf_list, vector<Integer> mt_list, frendy::GendfParser& gendf_data)
{
  GendfModifier   gendf_mod_obj;

  vector<Integer> mf_no_list;
  mf_no_list.push_back(3);
  mf_no_list.push_back(5);
  mf_no_list.push_back(6);
  mf_no_list.push_back(13);
  mf_no_list.push_back(16);

  int i_max = static_cast<int>(mf_no_list.size());
  for(int i=0; i<i_max; i++)
  {
    vector<Integer> output_list, remove_list;

    output_list = get_output_mt_list(mf_no_list[i], mf_list, mt_list);
    remove_list = get_remove_mt_list(gendf_data.get_mt_list(mf_no_list[i]), output_list); 
    output_list.clear();

    int j_max = static_cast<int>(remove_list.size());
    for(int j=0; j<j_max; j++)
    {
      gendf_mod_obj.remove_specified_MF_MT_data(gendf_data, mf_no_list[i], remove_list[j]);
    }
    remove_list.clear();
  }
  mf_no_list.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<Integer> MultiGroupDataGeneratorByNjoyInput::get_output_mt_list
                  (Integer mf_no, vector<Integer>& mf_list, vector<Integer>& mt_list)
{
  vector<Integer> remove_mt_list, output_mt_list;
  remove_mt_list.clear();
  output_mt_list.clear();

  int mf_all_flg = 0;

  int i_max = static_cast<int>(mf_list.size());
  for(int i=0; i<i_max; i++)
  {
    int mf_flg = 0;
    if( mf_no == 3 && mf_list[i] == mf_no )
    {
      mf_flg = 1;
    }
    else if( mf_no == 5 && (mf_list[i] == 5 || mf_list[i] == 6) )
    {
      mf_flg = 1;
    }
    else if( mf_no == 6 && (mf_list[i] == 6 || mf_list[i] == 8) )
    {
      mf_flg = 1;
    }
    else if( mf_no == 13 && (mf_list[i] == 13 || mf_list[i] == 12) )
    {
      mf_flg = 1;
    }
    else if( mf_no == 16 && (mf_list[i] == 16 || mf_list[i] == 17 || mf_list[i] == 18) )
    {
      mf_flg = 1;
    }

    if( mf_flg > 0 )
    {
      if( mt_list[i] == 0 )
      {
        mf_all_flg = 1;
        break;
      }
      else if( mt_list[i] < 0 )
      {
        int mt_max = -1 * mt_list[i];
        if( mt_max > 1000 )
        {
          mt_max = 1000;
        }

        for(int j=1; j<=mt_max; j++)
        {
          output_mt_list.push_back(j);
        }
      }
      else
      {
        output_mt_list.push_back(mt_list[i]);
      }
    }
  }

  if( mf_all_flg == 1 )
  {
    output_mt_list.resize(1000);
    for(int i=0; i<1000; i++)
    {
      output_mt_list[i] = i+1;
    }
  }

  return output_mt_list;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<Integer> MultiGroupDataGeneratorByNjoyInput::get_remove_mt_list
                  (vector<Integer> gendf_mt_list, vector<Integer> output_mt_list)
{
  sort(gendf_mt_list.begin(), gendf_mt_list.end());
  sort(output_mt_list.begin(), output_mt_list.end());

  int i_max = static_cast<int>(gendf_mt_list.size());
  int j_max = static_cast<int>(output_mt_list.size());

  vector<Integer> remove_mt_list;
  remove_mt_list.clear();

  for(int i=0; i<i_max; i++)
  {
    Integer mt_find_flg = 0;
    Integer gendf_mt_no = gendf_mt_list[i];
    for(int j=0; j<j_max; j++)
    {
      if( gendf_mt_no == output_mt_list[j] )
      {
        mt_find_flg = 1;
        break;
      }
    }

    if( mt_find_flg == 0 )
    {
      remove_mt_list.push_back(gendf_mt_no);
    }
  }

  return remove_mt_list;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorByNjoyInput::output_matxs_file(int mg_file_no)
{
  int matxs_no = static_cast<int>(read_matxsr_obj.size());
  for(int i=0; i<matxs_no; i++)
  {
    string matxs_name_out = read_matxsr_obj[i].get_matxs_name();

    if( mg_file_no > 0 )
    {
      ostringstream oss;
      oss << mg_file_no;
      if( mg_file_no < 10 )
      {
        matxs_name_out = matxs_name_out + "_0" + oss.str();
      }
      else
      {
        matxs_name_out = matxs_name_out + "_" + oss.str();
      }
    }

    MatxsWriter wri_obj;
    wri_obj.set_matxs_obj(matxs_obj);
    wri_obj.write_matxs(matxs_name_out);
    wri_obj.clear();

    matxs_obj_name_list.push_back(matxs_name_out);
  }

  matxs_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorByNjoyInput::output_matxs_file_merge()
{
  int i_max = static_cast<int>(matxs_obj_name_list.size());
  if( i_max <= 1 )
  {
    return;
  }

  MatxsMerger merge_obj;
  merge_obj.merge_matxs_file(matxs_obj_name_list);

  int matxs_no = static_cast<int>(read_matxsr_obj.size());
  for(int i=0; i<matxs_no; i++)
  {
    merge_obj.write_matxs_obj(read_matxsr_obj[i].get_matxs_name());
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//Setter

void MultiGroupDataGeneratorByNjoyInput::set_njoy_input_file_name
                                          (string str_data, int line_no, vector<int> matxsr_line_no_vec)
{
  calc_flg = 0;

  input_file_name_njoy  = str_data;
  start_line_no         = line_no;
  matxsr_line_no        = matxsr_line_no_vec;

  str_data.clear();
  matxsr_line_no_vec.clear();
}

