#include "MGXSUtils/InputUtils/MultiGroupDataGeneratorInputConverter.hpp"

using namespace frendy;

NuclearDataInfoNjoyMG::NuclearDataInfoNjoyMG(void)
{
  clear();
}

NuclearDataInfoNjoyMG::~NuclearDataInfoNjoyMG(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataInfoNjoyMG::clear()
{
  nucl_data_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataInfoNjoyMG::set_nucl_data_obj(frendy::NuclearDataObject& nucl_obj)
{
  nucl_data_obj = nucl_obj;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

string NuclearDataInfoNjoyMG::get_tsl_data_type(int tsl_flg)
{
  MatxsCommonData matxs_obj;

  return matxs_obj.get_tsl_name(tsl_flg);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Integer NuclearDataInfoNjoyMG::get_mat_no()
{
  return nucl_data_obj.get_general_data_obj().get_mat_no();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Real NuclearDataInfoNjoyMG::get_el()
{
  vector<Real> e_vec = nucl_data_obj.get_nucl_reaction_data_obj().get_xs_data_obj(1).get_xs_ene_data();

  int i_max  = static_cast<int>(e_vec.size());
  Real e_val = 0.0;
  if( i_max > 0 )
  {
    e_val = e_vec[0];
  }

  return e_val;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Real NuclearDataInfoNjoyMG::get_eh()
{
  vector<Real> e_vec = nucl_data_obj.get_nucl_reaction_data_obj().get_xs_data_obj(1).get_xs_ene_data();

  int i_max  = static_cast<int>(e_vec.size());
  Real e_val = 0.0;
  if( i_max > 0 )
  {
    e_val = e_vec[i_max-1];
  }

  return e_val;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Real NuclearDataInfoNjoyMG::get_thermal_cutoff()
{
  vector<Real> e_vec, xs_vec;

  for(int mt_no=221; mt_no<=250; mt_no++)
  {
    e_vec = nucl_data_obj.get_nucl_reaction_data_obj().get_xs_data_obj(mt_no).get_xs_ene_data();
    if( static_cast<int>(e_vec.size()) > 0 )
    {
      xs_vec = nucl_data_obj.get_nucl_reaction_data_obj().get_xs_data_obj(mt_no).get_xs_data();
      break;
    }
  }

  int i_max  = static_cast<int>(e_vec.size());
  Real e_val = 0.0;
  if( i_max > 0 )
  {
    for(int i=i_max-1; i>=0; i-- )
    {
      if( xs_vec[i] > min_sig_val )
      {
        e_val = e_vec[i];
        break;
      }
    }
  }

  return e_val;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //

MultiGroupDataGeneratorInputConverter::MultiGroupDataGeneratorInputConverter(void)
{
  clear();
}

MultiGroupDataGeneratorInputConverter::~MultiGroupDataGeneratorInputConverter(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputConverter::clear()
{
  //Select output mode for GENDF and MATXS (MF=6/MT=18)
  output_mode = njoy16_mode;
  //output_mode = njoy99_mode;
  //output_mode = full_mode;

  f_inp_obj.clear();
  n_inp_obj.clear();
  groupr_obj.clear();
  matxsr_obj.clear();

  set_data_flg  = -1;
  set_data_mode =  0;

  //For input data of NJOY
  tsl_data_flg = 0;
  ace_data_obj_fast.clear();
  ace_data_obj_tsl.clear();

  //For input data of FRENDY/MG
  input_data_key.clear();
  clr_obj.clear_vec_array2_str(input_data);

  //For ultra_fine_group
  ultra_fine_group_ene.clear();
  ultra_fine_group_div_no.clear();
  ultra_fine_group_opt.clear();

  //For mult_group
  multi_group.clear();
  multi_group_gam.clear();
  clr_obj.clear_vec_array1_str(multi_group_auto);

  //For default_spectrum
  default_spectrum_mode.clear();
  default_spectrum_eh           = 0.0;
  default_spectrum_el           = 0.0;
  default_spectrum_temp_fis     = 0.0;
  default_spectrum_temp_maxwell = 0.0;
  default_spectrum_el_fis       = 0.0;
  default_spectrum_eh_maxwell   = 0.0;
  default_spectrum_ene.clear();
  default_spectrum_weight.clear();

  //For material
  material_id.clear();
  material_id_set.clear();
  material_number_density.clear();
  material_sab_id.clear();
  material_sab_id_set.clear();
  material_sab_type.clear();

  //For ace_file
  ace_file.clear();
  ace_file_fast.clear();
  ace_file_tsl.clear();

  //For thermal_cutoff
  thermal_cutoff_ene_in  = 0.0;
  thermal_cutoff_ene_out = 0.0;

  //For calc_cond
  calc_cond_opt.clear();
  calc_cond_atomic_weight.clear();
  calc_cond_el.clear();
  calc_cond_eh.clear();
  calc_cond_sab_opt.clear(); //NoThermalXS

  //For bg_xs_set
  bg_xs_set.clear();
  bg_xs_auto.clear();

  //For potential_xs
  potential_xs.clear();

  //For max_pl
  max_pl = 0;

  //For reso_upscat
  reso_up_scat_mode = 0;
  reso_up_scat_0k_data.clear();

  //For edit_xs
  edit_xs_opt.clear();
  edit_xs_mt.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> MultiGroupDataGeneratorInputConverter::get_id_list(vector<string> ace_name_list)
{
  int i_max = static_cast<int>(ace_name_list.size());

  vector<string> id_list;
  id_list.resize(i_max);

  for(int i=0; i<i_max; i++)
  {
    id_list[i] = get_id(ace_name_list[i]);
  }

  return id_list;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

string         MultiGroupDataGeneratorInputConverter::get_id(string ace_name)
{
  AceFileReader ace_read_obj;
  
  Integer mcnpx_mode_flg = 0;
  Real    aw0            = 0.0;
  Real    tz             = 0.0;
  string  discriptive_data = "";
  vector<string> title_data;
  title_data.clear();

  FILE* fp = fopen(ace_name.c_str(), "r");
  if( fp == NULL )
  {
    return "";
  }
  fclose(fp);

  ace_read_obj.set_file_name(ace_name);
  ace_read_obj.get_title_data(mcnpx_mode_flg, aw0, tz, discriptive_data, title_data);
  ace_read_obj.clear();

  return title_data[0];
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputConverter::convert_input_data()
{
  if( set_data_flg > 0 )
  {
    //Skip converter
    return;
  }
  else if( set_data_flg < 0 )
  {
    string class_name = "MultiGroupDataGeneratorInputConverter";
    string func_name  = "convert_input_data()";

    vector<string> err_com;
    err_com.push_back("Please set FRENDY or NJOY input data object.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  set_data_flg = 1;

  if( set_data_mode == frendy_mode )
  {
    convert_input_data_frendy();
    check_input_data();
    make_input_data_list();
  }
  else if( set_data_mode == njoy_mode )
  {
    convert_input_data_njoy();
    check_input_data();
    make_input_data_list();
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputConverter::convert_input_data_frendy()
{
  //For ultra_fine_group
  //vector<Real>    ultra_fine_group_ene;
  //vector<Integer> ultra_fine_group_div_no;
  //vector<string>  ultra_fine_group_opt;
  ultra_fine_group_ene    = f_inp_obj.get_mg_ufg_structure();
  ultra_fine_group_div_no = f_inp_obj.get_mg_ufg_div_no();
  ultra_fine_group_opt    = f_inp_obj.get_mg_ufg_div_mode();

  //For mult_group
  //vector<Real>    multi_group;
  multi_group      = f_inp_obj.get_mg_structure();
  multi_group_auto = f_inp_obj.get_mg_structure_auto();
  multi_group_gam  = f_inp_obj.get_mg_structure_gam();

  //For default_spectrum
  //string          default_spectrum_mode;
  //Real            default_spectrum_eh,       default_spectrum_el,
  //                default_spectrum_temp_fis, default_spectrum_temp_maxwell,
  //                default_spectrum_el_fis,   default_spectrum_eh_maxwell;
  //vector<Real>    default_spectrum_ene,      default_spectrum_weight;
  default_spectrum_mode = f_inp_obj.get_mg_weighting_spectrum_mode();

  string e_mode       = "1/e";
  string maxwell_mode = "fission+1/e+maxwell";
  string mode_name    = default_spectrum_mode;
  transform(mode_name.begin(), mode_name.end(), mode_name.begin(), ::tolower);
  if( mode_name == maxwell_mode )
  {
    default_spectrum_eh           = f_inp_obj.get_mg_weighting_spectrum_eh();
    default_spectrum_el           = f_inp_obj.get_mg_weighting_spectrum_el();
    default_spectrum_temp_fis     = f_inp_obj.get_mg_weighting_fission_temp();
    default_spectrum_temp_maxwell = f_inp_obj.get_temp();
    default_spectrum_el_fis       = f_inp_obj.get_mg_weighting_1e_eh();
    default_spectrum_eh_maxwell   = f_inp_obj.get_mg_weighting_1e_el();
  }
  else if( mode_name == e_mode )
  {
  }
  else
  {
    default_spectrum_mode   = "input";
    default_spectrum_ene    = f_inp_obj.get_mg_weighting_spectrum_data_e();
    default_spectrum_weight = f_inp_obj.get_mg_weighting_spectrum_data_w();
  }
  
  //For material
  //vector<string>  material_id;
  //vector<Real>    material_number_density;
  //vector<string>  material_sab_id,  material_sab_type;
  material_id             = get_id_list(f_inp_obj.get_ace_file_name());
  material_number_density = f_inp_obj.get_mg_number_density();
  material_sab_id         = get_id_list(f_inp_obj.get_ace_file_name_tsl());
  material_sab_type       = f_inp_obj.get_mg_tsl_data_type();

  if( static_cast<int>(material_id.size()) == 0 )
  {
    material_id = material_id_set;
  }
  else if( static_cast<int>(material_id_set.size()) == 0 )
  {
  }
  else if( static_cast<int>(material_id.size()) != static_cast<int>(material_id_set.size()) )
  {
      string class_name = "MultiGroupDataGeneratorInputConverter";
      string func_name  = "convert_input_data_frendy()";

      ostringstream oss01, oss02;
      oss01 << static_cast<int>(material_id_set.size());
      oss02 << static_cast<int>(material_id.size());

      string str01 = "  Data size of material_id from input : " + oss01.str();
      string str02 = "  Data size of ACE file               : " + oss02.str();

      vector<string> err_com;
      err_com.push_back("The data size of material_id is different to that of ace file.");
      err_com.push_back("Please check the number of material_id and ACE file.");
      err_com.push_back("");
      err_com.push_back(str01);
      err_com.push_back(str02);
      err_obj.output_caution(class_name, func_name, err_com);
  }
  else
  {
    int id_no = static_cast<int>(material_id.size());

    int id_chk_flg = 0;
    vector<int> id_chk_list;
    id_chk_list.resize(id_no);
    for(int i=0; i<id_no; i++)
    {
      string mat_id = material_id[i];
      transform(mat_id.begin(), mat_id.end(), mat_id.begin(), ::tolower);

      string mat_id_set = material_id_set[i];
      transform(mat_id_set.begin(), mat_id_set.end(), mat_id_set.begin(), ::tolower);

      id_chk_list[i] = 0;
      if( mat_id[i] != mat_id_set[i] )
      {
        id_chk_flg++;
        id_chk_list[i] = 1;
      }
    }

    if( id_chk_flg > 0 )
    {
      string class_name = "MultiGroupDataGeneratorInputConverter";
      string func_name  = "convert_input_data_frendy()";

      vector<string> err_com;
      err_com.push_back("The material_id and zaid of ACE file is different.");
      err_com.push_back("The processing results may be wrong.");
      err_com.push_back("Please check material_id and ACE file.");
      err_com.push_back("");
      err_com.push_back("  material_id  /  zaid of ACE file");
      for(int i=0; i<id_no; i++)
      {
        string str_data = "  " + material_id[i] + " / " + material_id_set[i];
        if( id_chk_list[i] > 0 )
        {
          str_data = str_data + " <- different";
        }
        err_com.push_back(str_data);
      }
      //err_obj.output_runtime_error(class_name, func_name, err_com);
      err_obj.output_caution(class_name, func_name, err_com);
    }
  }

  if( static_cast<int>(material_sab_id.size()) == 0 )
  {
    material_sab_id = material_sab_id_set;
  }

  //For ace_file
  //vector<string>  ace_file;
  ace_file_fast = f_inp_obj.get_ace_file_name();
  ace_file      = ace_file_fast;

  ace_file_tsl = f_inp_obj.get_ace_file_name_tsl();
  if( static_cast<int>(ace_file_tsl.size()) > 0 )
  {
    if( static_cast<int>(ace_file_fast.size()) !=
        static_cast<int>(ace_file_tsl.size()) )
    {
      string class_name = "MultiGroupDataGeneratorInputConverter";
      string func_name  = "convert_input_data_frendy()";

      ostringstream oss01, oss02;
      oss01 << static_cast<int>(ace_file_fast.size());
      oss02 << static_cast<int>(ace_file_tsl.size());

      string str01 = "  Data size of ace_file_fast : " + oss01.str();
      string str02 = "  Data size of ace_file_tsl  : " + oss02.str();

      vector<string> err_com;
      err_com.push_back("The data size of ace_file_fast is different to that of ace_file_tsl.");
      err_com.push_back("Please check ace_file_fast and ace_file_tsl.");
      err_com.push_back("");
      err_com.push_back(str01);
      err_com.push_back(str02);
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    for(int i=0; i<static_cast<int>(ace_file_tsl.size()); i++)
    {
      ace_file.push_back(ace_file_tsl[i]);
    }
  }

  //For thermal_cutoff
  //Real            thermal_cutoff_ene_in, thermal_cutoff_ene_out;
  thermal_cutoff_ene_in  = f_inp_obj.get_max_thermal_ene_e_in();
  thermal_cutoff_ene_out = f_inp_obj.get_max_thermal_ene_e_out();

  if( thermal_cutoff_ene_in < 1.0E-5 )
  {
    thermal_cutoff_ene_in = 1.0E-5;
  }
  if( thermal_cutoff_ene_out < 1.0E-5 )
  {
    thermal_cutoff_ene_out = 1.0E-5;
  }

  if( fabs(f_inp_obj.get_temp() + 100.0) < 0.01 )
  {
    //Skip (default temperature)
  }
  else if( f_inp_obj.get_temp() < 10.0 )
  {
    string class_name = "MultiGroupDataGeneratorInputConverter";
    string func_name  = "convert_input_data_frendy()";

    ostringstream oss00, oss01, oss02, oss03, oss04;
    oss00 << setw(8) << std::showpoint << std::scientific << f_inp_obj.get_temp();
    oss01 << setw(8) << std::showpoint << std::scientific << thermal_cutoff_ene_in;
    oss02 << setw(8) << std::showpoint << std::scientific << thermal_cutoff_ene_out;
    string str_data00 = "Temperature : " + oss00.str() + " [K]";
    string str_data01 = "Thermal cut-off energy from input";
    string str_data02 = "  thermal cut-off energy for incident energy [eV] : " + oss01.str();
    string str_data03 = "  thermal cut-off energy for outgoing energy [eV] : " + oss02.str();

    thermal_cutoff_ene_in  =  50.0 * boltzmann_const * f_inp_obj.get_temp();
    thermal_cutoff_ene_out = 100.0 * boltzmann_const * f_inp_obj.get_temp();
    oss03 << setw(8) << std::showpoint << std::scientific << thermal_cutoff_ene_in;
    oss04 << setw(8) << std::showpoint << std::scientific << thermal_cutoff_ene_out;
    string str_data11 = "Modified thermal cut-off energy";
    string str_data12 = "  thermal cut-off energy for incident energy [eV] : " + oss03.str();
    string str_data13 = "  thermal cut-off energy for outgoing energy [eV] : " + oss04.str();

    vector<string> err_com;
    err_com.push_back(str_data00);
    err_com.push_back("");
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("");
    err_com.push_back(str_data11);
    err_com.push_back(str_data12);
    err_com.push_back(str_data13);
    err_com.push_back("");
    err_com.push_back("Since the maximum upperscattering at low temperature is not so high.");
    err_com.push_back("The thermal cut-off energy is modified.");
    err_obj.output_caution(class_name, func_name, err_com);
  }

  //For calc_cond
  //vector<string>  calc_cond_opt;
  //vector<Real>    calc_cond_atomic_weight, calc_cond_el, calc_cond_eh;
  //string          calc_cond_sab_opt; //NoThermalXS
  calc_cond_opt           = f_inp_obj.get_mg_flux_calc_mode();
  calc_cond_atomic_weight = f_inp_obj.get_mg_flux_calc_w();
  calc_cond_el            = f_inp_obj.get_mg_flux_calc_el();
  calc_cond_eh            = f_inp_obj.get_mg_flux_calc_eh();

  calc_cond_sab_opt.clear();
  if( f_inp_obj.get_mg_thermal_xs_treatment() == frendy_utils.off )
  {
    int sab_flg = 0;
    for(int i=0; i<static_cast<int>(material_sab_id.size()); i++)
    {
      if( static_cast<int>(material_sab_id[i].size()) > 0 )
      {
        sab_flg++;
      }
    }

    if( sab_flg > 0 )
    {
      string class_name = "MultiGroupDataGeneratorInputConverter";
      string func_name  = "convert_input_data_frendy()";

      vector<string> err_com;
      err_com.push_back("The thermal scattering law (TSL) data is found.");
      err_com.push_back("mg_thermal_xs_treatment is modified from OFF to ON to treat the TSL data.");
      err_obj.output_caution(class_name, func_name, err_com);
    }
    else //if( sab_flg == 0 )
    {
      calc_cond_sab_opt = "NoThermalXS";
    }
  }

  //For bg_xs_set
  //vector<Real>    bg_xs_set;
  bg_xs_set  = f_inp_obj.get_sigma_zero_data();
  bg_xs_auto = f_inp_obj.get_sigma_zero_data_auto();

  //For potential_xs
  //vector<Real>    potential_xs
  potential_xs = f_inp_obj.get_potential_scat_xs();

  //For max_pl
  //Integer         max_pl;
  max_pl = f_inp_obj.get_legendre_order();

  //For reso_upscat
  //Integer         reso_up_scat_mode;
  //vector<string>  reso_up_scat_0k_data;
  reso_up_scat_mode    = f_inp_obj.get_reso_up_scat_mode();
  reso_up_scat_0k_data = f_inp_obj.get_reso_up_scat_0k_data();

  //For edit_xs
  //vector<string>           edit_xs_opt;
  //vector<vector<Integer> > edit_xs_mt;
  edit_xs_opt = f_inp_obj.get_mg_edit_mode();
  int edit_no = static_cast<int>(edit_xs_opt.size());
  if( edit_no == 0 )
  {
    edit_no = 3;
    edit_xs_opt.resize(edit_no);

    edit_xs_opt[2] = "SkipPrintout";
    if( output_mode == njoy16_mode )
    {
      //For NJOY2016 (consideration of background XS for MF=6/MT=18)
      edit_xs_opt[0] = "GENDF";
      edit_xs_opt[1] = "MATXS";
    }
    else if( output_mode == njoy99_mode )
    {
      //For NJOY99 (no consideration of background XS for MF=6/MT=18)
      edit_xs_opt[0] = "SIMPLEGENDF";
      edit_xs_opt[1] = "SIMPLEMATXS";
    }
    else if( output_mode == full_mode )
    {
      //Consideration of PL order and back ground XS for MF=6/MT=18)
      edit_xs_opt[0] = "FULLGENDF";
      edit_xs_opt[1] = "FULLMATXS";
    }
    else
    {
      string class_name = "MultiGroupDataGeneratorInputConverter";
      string func_name  = "convert_input_data_frendy()";
  
      ostringstream oss01, oss02;
      oss01 << output_mode;

      string str01 = "  Output option of GENDF and MATXS : " + oss01.str();

      vector<string> err_com;
      err_com.push_back(str01);
      err_com.push_back("This output option of GENDF and MATXS is not available.");
      err_com.push_back("Available output option is as follows:");
      err_com.push_back("  NJOY2016 mode (consideration of background XS for MF=6/MT=18)              : 1");
      err_com.push_back("  NJOY99 mode   (no consideration of background XS for MF=6/MT=18)           : 2");
      err_com.push_back("  NJOY2016 mode (consideration of PL order and background XS for MF=6/MT=18) : 3");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }

  edit_xs_mt.resize(edit_no);
  for(int i=0; i<edit_no; i++)
  {
    edit_xs_mt[i].clear();
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputConverter::convert_input_data_njoy()
{
  //For ultra_fine_group
  //vector<Real>    ultra_fine_group_ene;
  //vector<Integer> ultra_fine_group_div_no;
  //vector<string>  ultra_fine_group_opt;
  f_inp_obj.get_ufg_data_def(ultra_fine_group_ene, ultra_fine_group_div_no, ultra_fine_group_opt);

  //For mult_group
  //vector<Real>    multi_group;
  Integer ign = groupr_obj.get_ign()[pos_i];
  if( ign == 1 )
  {
    multi_group = groupr_obj.get_egn()[pos_i];
  }
  else
  {
    GroupStructureNeutron egn_obj;
    multi_group = egn_obj.get_group_structure(ign);
  }

  Integer igg = groupr_obj.get_igg()[pos_i];
  if( igg == 1 )
  {
    multi_group_gam = groupr_obj.get_egg()[pos_i];
  }
  else
  {
    GroupStructureGamma egg_obj;
    multi_group_gam = egg_obj.get_group_structure(igg);
  }

  //For default_spectrum
  //string          default_spectrum_mode;
  //Real            default_spectrum_eh,       default_spectrum_el,
  //                default_spectrum_temp_fis, default_spectrum_temp_maxwell,
  //                default_spectrum_el_fis,   default_spectrum_eh_maxwell;
  //vector<Real>    default_spectrum_ene,      default_spectrum_weight;
  Integer iwt  = groupr_obj.get_iwt()[pos_i];
  Real    temp = groupr_obj.get_temp()[pos_i][pos_j];
  MultiGroupWeightFunction weight_obj;
  vector<Real> e_vec, w_vec;
  weight_obj.get_weighting_function(iwt, temp, e_vec, w_vec);

  if( static_cast<int>(e_vec.size()) > 0 ) //iwt == 2, 5-12
  {
    if( iwt == 2 || iwt == -2 )
    {
      e_vec.resize(2);
      w_vec.resize(2);
      e_vec[0] = n_inp_obj.get_el();
      e_vec[1] = n_inp_obj.get_eh();
      w_vec[0] = 1.0;
      w_vec[1] = 1.0;
    }

    default_spectrum_mode   = "input";
    default_spectrum_ene    = e_vec;
    default_spectrum_weight = w_vec;
  }
  else if( iwt == 0 || iwt == 1 )
  {
    default_spectrum_mode      = "input";

    vector<Integer> nbt_vec,    int_vec;
    vector<Real>    wght_e_vec, wght_w_vec;
    if( iwt == 1 || iwt == -1 )
    {
      nbt_vec    = groupr_obj.get_wght_nbt()[pos_i];
      int_vec    = groupr_obj.get_wght_int()[pos_i];
      wght_e_vec = groupr_obj.get_wght_e()[pos_i];
      wght_w_vec = groupr_obj.get_wght_w()[pos_i];
    }
    else if( iwt == 0 )
    {
      //string wght_name = groupr_obj.get_ninwt()[pos_i];

      //ifstream fin_wght;
      //fin_wght.open(wght_name.c_str());

      string class_name = "MultiGroupDataGeneratorInputConverter";
      string func_name  = "convert_input_data_njoy()";

      vector<string> err_com;
      err_com.push_back("iwt = 0 (read resonance flux for flux calculator) is not available.");
      err_com.push_back("Please use other iwt option.");
      err_com.push_back("");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    Real err_relative = 1.0E-3;
    Real err_min      = err_relative*1.0E-3;

    LinearizeTabData tab_obj;
    tab_obj.linearize_tab1_data(nbt_vec, int_vec, wght_e_vec, wght_w_vec, err_relative, err_min);

    default_spectrum_ene    = wght_e_vec;
    default_spectrum_weight = wght_w_vec;
  }
  else if( iwt == 3 || iwt == -3 ) //1/e
  {
    default_spectrum_mode = "1/e";
  }
  else if( iwt == 4 || iwt == -4 ) //1/e + fission spectrum + thermal Maxwellian
  {
    default_spectrum_mode = "fission+1/e+maxwell";

    Real temp_maxwell             = groupr_obj.get_tb()[pos_i] / boltzmann_const; //eV -> K
    default_spectrum_el           = n_inp_obj.get_el();
    default_spectrum_eh           = n_inp_obj.get_eh();
    default_spectrum_eh_maxwell   = groupr_obj.get_eb()[pos_i];
    default_spectrum_temp_maxwell = temp_maxwell;
    default_spectrum_el_fis       = groupr_obj.get_ec()[pos_i];
    default_spectrum_temp_fis     = groupr_obj.get_tc()[pos_i];

    if( fabs(groupr_obj.get_temp()[pos_i][pos_j] - temp_maxwell) > 10.0 )
    {
      string class_name = "MultiGroupDataGeneratorInputConverter";
      string func_name  = "convert_input_data_njoy()";
      ostringstream oss01, oss02, oss03;
      oss01 << groupr_obj.get_temp()[pos_i][pos_j];
      oss02 << temp_maxwell;
      oss03 << groupr_obj.get_tb()[pos_i];

      string str01 = "  Temperature from PENDF file (K)  : " + oss01.str();
      string str02 = "  Temperature from input file (K)  : " + oss02.str();
      string str03 = "  Temperature from input file (eV) : " + oss03.str();


      vector<string> err_com;
      err_com.push_back("The temprature from PENDF file is different to that from input file.");
      err_com.push_back("The PENDF file or input data (tb in GROUPR) may not be correct.");
      err_com.push_back("");
      err_com.push_back(str01);
      err_com.push_back(str02);
      err_com.push_back(str03);

      err_obj.output_caution(class_name, func_name, err_com);
    }
  }
  else
  {
    string class_name = "MultiGroupDataGeneratorInputConverter";
    string func_name  = "convert_input_data_njoy()";

    ostringstream oss01;
    oss01 << iwt;

    string str01 = "  Weight function option : " + oss01.str();

    vector<string> err_com;
    err_com.push_back("This weighting function type is not available in this program.");
    err_com.push_back("Available weighting function type is as follows:");
    err_com.push_back("   1      read in");
    err_com.push_back("   2      constant");
    err_com.push_back("   3      1/e");
    err_com.push_back("   4      1/e + fission spectrum + thermal Maxwellian");
    err_com.push_back("   5      EPRI-CELL LWR");
    err_com.push_back("   6      (thermal) -- (1/e) -- (fission + fusion)");
    err_com.push_back("   7      same with t-dep thermal part");
    err_com.push_back("   8      thermal--1/e--fast reactor--fission + fusion");
    err_com.push_back("   9      claw weight function");
    err_com.push_back("  10      claw with t-dependent thermal part");
    err_com.push_back("  11      vitamin-e weight function (ornl-5505)");
    err_com.push_back("  12      vit-e with t-dep thermal part");
    err_com.push_back("");
    err_com.push_back(str01);
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
 
  //For material
  //vector<string>  material_id;
  //vector<Real>    material_number_density;
  //vector<string>  material_sab_id,  material_sab_type;
  material_id.resize(1);
  material_id[0]             = ace_data_obj_fast.get_title_data()[0];
  material_number_density    = frendy_utils.get_mg_number_density_def();

  if( tsl_data_flg > 0 )
  {
    material_sab_id.resize(1);
    material_sab_type.resize(1);
    material_sab_id[0]   = ace_data_obj_tsl.get_title_data()[0];
    material_sab_type[0] = n_inp_obj.get_tsl_data_type(tsl_data_flg);
  }
  else
  {
    material_sab_id.resize(0);
    material_sab_type.resize(0);
  }

  if( static_cast<int>(material_id.size()) == 0 )
  {
    material_id = material_id_set;
  }
  else if( static_cast<int>(material_id_set.size()) == 0 )
  {
  }
  else if( static_cast<int>(material_id.size()) != static_cast<int>(material_id_set.size()) )
  {
      string class_name = "MultiGroupDataGeneratorInputConverter";
      string func_name  = "convert_input_data_njoy()";

      ostringstream oss01, oss02;
      oss01 << static_cast<int>(material_id_set.size());
      oss02 << static_cast<int>(material_id.size());

      string str01 = "  Data size of material_id from input : " + oss01.str();
      string str02 = "  Data size of ACE file               : " + oss02.str();

      vector<string> err_com;
      err_com.push_back("The data size of material_id is different to that of ace file.");
      err_com.push_back("Please check the number of material_id and ACE file.");
      err_com.push_back("");
      err_com.push_back(str01);
      err_com.push_back(str02);
      err_obj.output_caution(class_name, func_name, err_com);
  }
  else
  {
    int id_no = static_cast<int>(material_id.size());

    int id_chk_flg = 0;
    vector<int> id_chk_list;
    id_chk_list.resize(id_no);
    for(int i=0; i<id_no; i++)
    {
      string mat_id = material_id[i];
      transform(mat_id.begin(), mat_id.end(), mat_id.begin(), ::tolower);

      string mat_id_set = material_id_set[i];
      transform(mat_id_set.begin(), mat_id_set.end(), mat_id_set.begin(), ::tolower);

      id_chk_list[i] = 0;
      if( mat_id[i] != mat_id_set[i] )
      {
        id_chk_flg++;
        id_chk_list[i] = 1;
      }
    }

    if( id_chk_flg > 0 )
    {
      string class_name = "MultiGroupDataGeneratorInputConverter";
      string func_name  = "convert_input_data_njoy()";

      vector<string> err_com;
      err_com.push_back("The material_id and zaid of ACE file is different.");
      err_com.push_back("Please check material_id and ACE file.");
      err_com.push_back("");
      err_com.push_back("  material_id  /  zaid of ACE file");
      for(int i=0; i<id_no; i++)
      {
        string str_data = "  " + material_id[i] + " / " + material_id_set[i];
        if( id_chk_list[i] > 0 )
        {
          str_data = str_data + " <- different";
        }
        err_com.push_back(str_data);
      }
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }

  if( static_cast<int>(material_sab_id.size()) == 0 )
  {
    material_sab_id = material_sab_id_set;
  }

  //For ace_file
  //vector<string>  ace_file;
  ace_file_fast.resize(1);
  ace_file_fast[0] = groupr_obj.get_ace_file_name();
  ace_file         = ace_file_fast;

  if( tsl_data_flg > 0 )
  {
    ace_file_tsl.resize(1);
    ace_file_tsl[0] = groupr_obj.get_ace_file_name() + ".tsl";
    ace_file.push_back(ace_file_tsl[0]);
  }
  else
  {
    ace_file_tsl.resize(0);
  }

  //For calc_cond
  //vector<string>  calc_cond_opt;
  //vector<Real>    calc_cond_atomic_weight, calc_cond_el, calc_cond_eh;
  //string          calc_cond_sab_opt; //NoThermalXS
  calc_cond_atomic_weight = frendy_utils.get_mg_flux_calc_w_def();
  calc_cond_el            = frendy_utils.get_mg_flux_calc_el_def();

  calc_cond_opt.resize(1);
  if( groupr_obj.get_iwt()[pos_i] >= 0 )
  {
    calc_cond_opt[0]        = "NR";
    calc_cond_eh            = frendy_utils.get_mg_flux_calc_eh_def();
  }
  else
  {
    calc_cond_opt[0]        = "SLD";

    calc_cond_eh.resize(1);
    calc_cond_eh[0]         = groupr_obj.get_fehi()[pos_i];
  }

  //For thermal_cutoff
  //Real            thermal_cutoff_ene_in, thermal_cutoff_ene_out;
  thermal_cutoff_ene_in  = n_inp_obj.get_thermal_cutoff();
  thermal_cutoff_ene_out = thermal_cutoff_ene_in;

  calc_cond_sab_opt.clear();
  if( thermal_cutoff_ene_in < min_value )
  {
    if( tsl_data_flg > 0 )
    {
      string class_name = "MultiGroupDataGeneratorInputConverter";
      string func_name  = "convert_input_data_njoy()";

      ostringstream oss01;
      oss01 << setw(8) << std::showpoint << std::scientific << thermal_cutoff_ene_in;
      string str01 = "Thermal cut-off energy [eV] : " + oss01.str();

      vector<string> err_com;
      err_com.push_back(str01);
      err_com.push_back("");
      err_com.push_back("The thermal cut-off energy is less than or equal to 0.0 eV.");
      err_com.push_back("The thermal cut-off energy should be larger than 0.0 eV");
      err_com.push_back("to process the thermal scattering law data.");
      err_obj.output_caution(class_name, func_name, err_com);
    }
    else
    {
      calc_cond_sab_opt = "NoThermalXS";
    }
  }
  else if( groupr_obj.get_temp()[pos_i][pos_j] < 10.0 )
  {
    string class_name = "MultiGroupDataGeneratorInputConverter";
    string func_name  = "convert_input_data_njoy()";

    ostringstream oss00, oss01, oss02, oss03, oss04;
    oss00 << setw(8) << std::showpoint << std::scientific << groupr_obj.get_temp()[pos_i][pos_j];
    oss01 << setw(8) << std::showpoint << std::scientific << thermal_cutoff_ene_in;
    oss02 << setw(8) << std::showpoint << std::scientific << thermal_cutoff_ene_out;
    string str_data00 = "Temperature : " + oss00.str() + " [K]";
    string str_data01 = "Thermal cut-off energy from input";
    string str_data02 = "  thermal cut-off energy for incident energy [eV] : " + oss01.str();
    string str_data03 = "  thermal cut-off energy for outgoing energy [eV] : " + oss02.str();

    thermal_cutoff_ene_in  =  50.0 * boltzmann_const * groupr_obj.get_temp()[pos_i][pos_j];
    thermal_cutoff_ene_out = 100.0 * boltzmann_const * groupr_obj.get_temp()[pos_i][pos_j];
    oss03 << setw(8) << std::showpoint << std::scientific << thermal_cutoff_ene_in;
    oss04 << setw(8) << std::showpoint << std::scientific << thermal_cutoff_ene_out;
    string str_data11 = "Modified thermal cut-off energy";
    string str_data12 = "  thermal cut-off energy for incident energy [eV] : " + oss03.str();
    string str_data13 = "  thermal cut-off energy for outgoing energy [eV] : " + oss04.str();

    vector<string> err_com;
    err_com.push_back(str_data00);
    err_com.push_back("");
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("");
    err_com.push_back(str_data11);
    err_com.push_back(str_data12);
    err_com.push_back(str_data13);
    err_com.push_back("");
    err_com.push_back("Since the maximum upperscattering at low temperature is not so high.");
    err_com.push_back("The thermal cut-off energy is modified.");
    err_obj.output_caution(class_name, func_name, err_com);
  }
  else
  {
    if( thermal_cutoff_ene_in < 1.0E-5 )
    {
      thermal_cutoff_ene_in = 1.0E-5;
    }
    if( thermal_cutoff_ene_out < 1.0E-5 )
    {
      thermal_cutoff_ene_out = 1.0E-5;
    }
  }

  //For bg_xs_set
  //vector<Real>    bg_xs_set;
  bg_xs_set = groupr_obj.get_sigz()[pos_i];

  //For potential_xs
  //Vector<Real> potential_xs
  potential_xs.resize(1);
  potential_xs[0] = groupr_obj.get_sigpot()[pos_i];
  //If sig_pot is not defined, use default value.
  if( fabs(potential_xs[0]) < min_value )
  {
    potential_xs.clear();
  }

  //For max_pl
  //Integer         max_pl;
  max_pl = groupr_obj.get_lord()[pos_i];

  //For reso_upscat
  //Integer         reso_up_scat_mode;
  //vector<string>  reso_up_scat_0k_data;
  reso_up_scat_mode = f_inp_obj.reso_up_scat_2d;
  reso_up_scat_0k_data.clear();

  //For edit_xs
  //vector<string>           edit_xs_opt;
  //vector<vector<Integer> > edit_xs_mt;
  edit_xs_opt.resize(3);
  edit_xs_mt.resize(3);
  edit_xs_mt[0].clear();
  edit_xs_mt[1].clear();
  edit_xs_mt[2].clear();

  edit_xs_opt[2] = "SkipPrintout";

  if( output_mode == njoy16_mode )
  {
    //For NJOY2016 (consideration of background XS for MF=6/MT=18)
    edit_xs_opt[0] = "GENDF";
    edit_xs_opt[1] = "MATXS";
  }
  else if( output_mode == njoy99_mode )
  {
    //For NJOY99 (no consideration of background XS for MF=6/MT=18)
    edit_xs_opt[0] = "SIMPLEGENDF";
    edit_xs_opt[1] = "SIMPLEMATXS";
  }
  else if( output_mode == full_mode )
  {
    //Consideration of PL order and back ground XS for MF=6/MT=18)
    edit_xs_opt[0] = "FULLGENDF";
    edit_xs_opt[1] = "FULLMATXS";
  }
  else
  {
    string class_name = "MultiGroupDataGeneratorInputConverter";
    string func_name  = "convert_input_data_frendy()";

    ostringstream oss01, oss02;
    oss01 << output_mode;

    string str01 = "  Output option of GENDF and MATXS : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str01);
    err_com.push_back("This output option of GENDF and MATXS is not available.");
    err_com.push_back("Available output option is as follows:");
    err_com.push_back("  NJOY2016 mode (consideration of background XS for MF=6/MT=18)              : 1");
    err_com.push_back("  NJOY99 mode   (no consideration of background XS for MF=6/MT=18)           : 2");
    err_com.push_back("  NJOY2016 mode (consideration of PL order and background XS for MF=6/MT=18) : 3");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputConverter::check_input_data()
{
  string class_name = "MultiGroupDataGeneratorInputConverter";
  string func_name  = "check_input_data()";

  string str_data = "";
  ostringstream oss_i, oss_r;
  oss_i.precision(7);
  oss_r.precision(7);
  oss_r.setf(ios::showpoint);
  oss_r.setf(ios::scientific);

  //For ultra_fine_group
  //vector<Real>    ultra_fine_group_ene;
  //vector<Integer> ultra_fine_group_div_no;
  //vector<string>  ultra_fine_group_opt;
  int i_max = static_cast<int>(ultra_fine_group_ene.size());
  if( i_max <= 1 ||
      static_cast<int>(ultra_fine_group_div_no.size()) != i_max-1 ||
      static_cast<int>(ultra_fine_group_opt.size())    != i_max-1 )
  {
    vector<string> err_com;
    err_com.push_back("The data size of ultra fine group input options is not correct.");
    err_com.push_back("Please check ultra fine group input options.");
    err_com.push_back("");

    oss_i << i_max;
    str_data = "  Data size of ultra_fine_group_ene (mg_ufg_structure) : " + oss_i.str();
    err_com.push_back(str_data);
    oss_i.str("");
    for(int i=0; i<i_max; i++)
    {
      oss_r << ultra_fine_group_ene[i];
      str_data = "    " + oss_r.str();
      err_com.push_back(str_data);
      oss_r.str("");
    }
    err_com.push_back("");
 
    oss_i << static_cast<int>(ultra_fine_group_div_no.size());
    str_data = "  Data size of ultra_fine_group_div_no (mg_ufg_structure or mg_ufg_div_no): " + oss_i.str();
    err_com.push_back(str_data);
    oss_i.str("");
    for(int i=0; i<static_cast<int>(ultra_fine_group_div_no.size()); i++)
    {
      oss_i << ultra_fine_group_div_no[i];
      str_data = "    " + oss_i.str();
      err_com.push_back(str_data);
      oss_i.str("");
    }
    err_com.push_back("");
 
    oss_i << static_cast<int>(ultra_fine_group_opt.size());
    str_data = "  Data size of ultra_fine_group_opt (mg_ufg_structure or mg_ufg_div_mode) : " + oss_i.str();
    err_com.push_back(str_data);
    oss_i.str("");
    for(int i=0; i<static_cast<int>(ultra_fine_group_opt.size()); i++)
    {
      str_data = "    " + ultra_fine_group_opt[i];
      err_com.push_back(str_data);
    }
    err_com.push_back("");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //For mult_group
  //vector<Real>    multi_group;
  if( static_cast<int>(multi_group.size()) == 0 && static_cast<int>(multi_group_auto.size()) == 0 )
  {
    vector<string> err_com;
    err_com.push_back("The data size of multi-group energy grid number is zero.");
    err_com.push_back("Please check multi-group energy grid data.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //For default_spectrum
  //string          default_spectrum_mode;
  //Real            default_spectrum_eh,       default_spectrum_el,
  //                default_spectrum_temp_fis, default_spectrum_temp_maxwell,
  //                default_spectrum_el_fis,   default_spectrum_eh_maxwell;
  //vector<Real>    default_spectrum_ene,      default_spectrum_weight;

  string e_mode       = "1/e";
  string maxwell_mode = "fission+1/e+maxwell";
  string mode_name    = default_spectrum_mode;
  transform(mode_name.begin(), mode_name.end(), mode_name.begin(), ::tolower);
  if( mode_name != maxwell_mode && mode_name != e_mode )
  {
    if( static_cast<int>(default_spectrum_ene.size()) != static_cast<int>(default_spectrum_weight.size()) )
    {
      vector<string> err_com;
      err_com.push_back("The data size of default_spectrum_ene and/or default_spectrum_weight is not correct.");
      err_com.push_back("These data must be larger than zero and the size of these data must be identical");
      err_com.push_back("when default_spectrum_mode is not 1/e or fission+1/e+maxwell.");
      err_com.push_back("");

      str_data = "default_spectrum_mode : " + default_spectrum_mode;
      err_com.push_back(str_data);
      err_com.push_back("");

      oss_i << static_cast<int>(default_spectrum_ene.size());
      str_data = "  Data size of default_spectrum_ene (mg_weighting_spectrum_data) : " + oss_i.str();
      oss_i.str("");
      err_com.push_back(str_data);
      for(int i=0; i<static_cast<int>(default_spectrum_ene.size()); i++)
      {
        oss_r << default_spectrum_ene[i];
        str_data = "    " + oss_r.str();
        oss_r.str("");
        err_com.push_back(str_data);
      }
      err_com.push_back("");

      oss_i << static_cast<int>(default_spectrum_weight.size());
      str_data = "  Data size of default_spectrum_weight (mg_weighting_spectrum_data) : " + oss_i.str();
      oss_i.str("");
      err_com.push_back(str_data);
      for(int i=0; i<static_cast<int>(default_spectrum_weight.size()); i++)
      {
        oss_r << default_spectrum_weight[i];
        str_data = "    " + oss_r.str();
        oss_r.str("");
        err_com.push_back(str_data);
      }
      err_com.push_back("");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }
  if( mode_name == maxwell_mode )
  {
    if( default_spectrum_temp_maxwell < 100.0 )
    {
      if( default_spectrum_eh_maxwell > 0.1 )
      {
        oss_r << default_spectrum_temp_maxwell;
        string str_data01 = "temp/tb [K]                                             : " + oss_r.str();
        oss_r.str("");

        oss_r << default_spectrum_eh_maxwell;
        string str_data02 = "E2/eb (Energy boundary between 1/E and Maxwell spectra) : " + oss_r.str();
        oss_r.str("");

        vector<string> err_com;
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back("Though temperature is so small, the energy boundary between 1/E");
        err_com.push_back("and Maxwell spectra  is large.");
        err_com.push_back("The E2/eb value is modified to correctly treat the upscattering");
        err_com.push_back("cross section.");

        default_spectrum_eh_maxwell = 0.0;

        err_obj.output_caution(class_name, func_name, err_com);
      }
    }
  }
  
  //For material
  //vector<string>  material_id;
  //vector<Real>    material_number_density;
  //vector<string>  material_sab_id,  material_sab_type;
  i_max = static_cast<int>(material_id.size());
  if( i_max == 0 ||
      static_cast<int>(material_number_density.size()) != i_max )
  {
    vector<string> err_com;
    err_com.push_back("The data size of material_id and/or material_number_density is not correct.");
    err_com.push_back("These data must be larger than zero and the size of these data must be identical.");
    err_com.push_back("");

    oss_i << i_max;
    str_data = "  Data size of material_id (number of fast ACE files) : " + oss_i.str();
    oss_i.str("");
    err_com.push_back(str_data);
    for(int i=0; i<i_max; i++)
    {
      str_data = "    " + material_id[i];
      err_com.push_back(str_data);
    }
    err_com.push_back("");

    oss_i << static_cast<int>(material_number_density.size());
    str_data = "  Data size of material_number_density (mg_number_density) : " + oss_i.str();
    oss_i.str("");
    err_com.push_back(str_data);
    for(int i=0; i<static_cast<int>(material_number_density.size()); i++)
    {
      oss_r << material_number_density[i];
      str_data = "    " + oss_r.str();
      oss_r.str("");
      err_com.push_back(str_data);
    }
    err_com.push_back("");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  if( static_cast<int>(material_sab_id.size())   > 0 ||
      static_cast<int>(material_sab_type.size()) > 0 )
  {
    if( static_cast<int>(material_sab_id.size())   != i_max ||
        static_cast<int>(material_sab_type.size()) != i_max )
    {
      vector<string> err_com;
      if( static_cast<int>(material_sab_type.size()) == 0 )
      {
        err_com.push_back("The data size of material_sab_type (mg_tsl_data_type) is zero.");
        err_com.push_back("The material_sab_type is automatically set \"other\".");
        err_com.push_back("");
      }
      else
      {
        err_com.push_back("The data size of material_sab_id and/or material_sab_type (mg_tsl_data_type) is not correct.");
        err_com.push_back("The data size of these data must be identical to that of material_id.");
        err_com.push_back("");
      }

      oss_i << i_max;
      str_data = "  Data size of material_id (number of fast ACE files) : " + oss_i.str();
      oss_i.str("");
      err_com.push_back(str_data);
      for(int i=0; i<i_max; i++)
      {
        str_data = "    " + material_id[i];
        err_com.push_back(str_data);
      }
      err_com.push_back("");

      oss_i << static_cast<int>(material_sab_id.size());
      str_data = "  Data size of material_sab_id (number of TSL ACE files) : " + oss_i.str();
      oss_i.str("");
      err_com.push_back(str_data);
      for(int i=0; i<static_cast<int>(material_sab_id.size()); i++)
      {
        str_data = "    " + material_sab_id[i];
        err_com.push_back(str_data);
      }
      err_com.push_back("");

      if( static_cast<int>(material_sab_type.size()) == 0 )
      {
        err_obj.output_caution(class_name, func_name, err_com);

        material_sab_type.resize(i_max);
        for(int i=0; i<i_max; i++)
        {
          material_sab_type[i] = "other";
        }
      }
      else
      {
        oss_i << static_cast<int>(material_sab_type.size());
        str_data = "  Data size of material_sab_type (mg_tsl_data_type) : " + oss_i.str();
        oss_i.str("");
        err_com.push_back(str_data);
        for(int i=0; i<static_cast<int>(material_sab_type.size()); i++)
        {
          str_data = "    " + material_sab_type[i];
          err_com.push_back(str_data);
        }
        err_com.push_back("");
        err_obj.output_runtime_error(class_name, func_name, err_com);
      }
    }
  }

  //For ace_file
  //vector<string>  ace_file;
  i_max = static_cast<int>(ace_file.size());

  if( i_max == 0 )
  {
    //ace_file = material_id;
  }
  else if( i_max != static_cast<int>(material_id.size())
                  + static_cast<int>(material_sab_id.size()) )
  {
    vector<string> err_com;
    err_com.push_back("The data size of ace_file is not correct.");
    err_com.push_back("The data size of these data must be identical to that of material_id + material_sab_id.");
    err_com.push_back("");

    oss_i << i_max;
    str_data = "  Data size of ace_file : " + oss_i.str();
    oss_i.str("");
    err_com.push_back(str_data);
    for(int i=0; i<i_max; i++)
    {
      str_data = "    " + ace_file[i];
      err_com.push_back(str_data);
    }
    err_com.push_back("");

    oss_i << static_cast<int>(material_id.size());
    str_data = "  Data size of material_id (from fast ACE file) : " + oss_i.str();
    oss_i.str("");
    err_com.push_back(str_data);
    for(int i=0; i<static_cast<int>(material_id.size()); i++)
    {
      str_data = "    " + material_id[i];
      err_com.push_back(str_data);
    }
    err_com.push_back("");

    oss_i << static_cast<int>(material_sab_id.size());
    str_data = "  Data size of material_sab_id (from TSL ACE file) : " + oss_i.str();
    oss_i.str("");
    err_com.push_back(str_data);
    for(int i=0; i<static_cast<int>(material_sab_id.size()); i++)
    {
      str_data = "    " + material_sab_id[i];
      err_com.push_back(str_data);
    }
    err_com.push_back("");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //For calc_cond
  //vector<string>  calc_cond_opt;
  //vector<Real>    calc_cond_atomic_weight, calc_cond_el, calc_cond_eh;
  //string          calc_cond_sab_opt; //NoThermalXS
  i_max = static_cast<int>(calc_cond_opt.size());
  if( static_cast<int>(calc_cond_atomic_weight.size()) > 0 )
  {
    if( static_cast<int>(calc_cond_atomic_weight.size()) != i_max ||
        static_cast<int>(calc_cond_el.size())            != i_max ||
        static_cast<int>(calc_cond_eh.size())            != i_max )
    {
      vector<string> err_com;
      err_com.push_back("The data size of calc_cond_opt, calc_cond_atomic_weight, calc_cond_el, and/or calc_cond_eh is not correct.");
      err_com.push_back("The data size of these data must be identical.");
      err_com.push_back("");

      oss_i << i_max;
      str_data = "  Data size of calc_cond_opt (NR / SLD) : " + oss_i.str();
      oss_i.str("");
      err_com.push_back(str_data);
      for(int i=0; i<i_max; i++)
      {
        str_data = "    " + calc_cond_opt[i];
        err_com.push_back(str_data);
      }
      err_com.push_back("");

      oss_i << static_cast<int>(calc_cond_atomic_weight.size());
      str_data = "  Data size of calc_cond_atomic_weight (mg_flux_calc_w_eh_el or mg_flux_calc_w ) : " + oss_i.str();
      oss_i.str("");
      err_com.push_back(str_data);
      for(int i=0; i<static_cast<int>(calc_cond_atomic_weight.size()); i++)
      {
        oss_r << calc_cond_atomic_weight[i];
        str_data = "    " + oss_r.str();
        oss_r.str("");
        err_com.push_back(str_data);
      }
      err_com.push_back("");

      oss_i << static_cast<int>(calc_cond_el.size());
      str_data = "  Data size of calc_cond_el (mg_flux_calc_w_eh_el or mg_flux_calc_el) : " + oss_i.str();
      oss_i.str("");
      err_com.push_back(str_data);
      for(int i=0; i<static_cast<int>(calc_cond_el.size()); i++)
      {
        oss_r << calc_cond_el[i];
        str_data = "    " + oss_r.str();
        oss_r.str("");
        err_com.push_back(str_data);
      }
      err_com.push_back("");

      oss_i << static_cast<int>(calc_cond_eh.size());
      str_data = "  Data size of calc_cond_eh (mg_flux_calc_w_eh_el or mg_flux_calc_eh) : " + oss_i.str();
      oss_i.str("");
      err_com.push_back(str_data);
      for(int i=0; i<static_cast<int>(calc_cond_eh.size()); i++)
      {
        oss_r << calc_cond_eh[i];
        str_data = "    " + oss_r.str();
        oss_r.str("");
        err_com.push_back(str_data);
      }
      err_com.push_back("");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }

  //For bg_xs_set
  if( static_cast<int>(bg_xs_set.size()) > 0 )
  {
    sort(bg_xs_set.begin(), bg_xs_set.end(),std::greater<Real>());
    if( bg_xs_set[0]  < 9.9E9 )
    {
      oss_r << bg_xs_set[0];
      str_data = "Maximum background cross section (sig zero) : " + oss_r.str();
      oss_r.str("");

      vector<string> err_com;
      err_com.push_back(str_data);
      err_com.push_back("");
      err_com.push_back("Maximum background cross section (sig zero) must be larger than or equal to 1.0E+10.");
      err_com.push_back("Please check background cross section data.");
      err_com.push_back("");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }

  //For potential_xs
  //vector<Real>    potential_xs;
  i_max = static_cast<int>(potential_xs.size());
  if( i_max > 0 )
  {
    if( i_max != static_cast<int>(material_id.size()) )
    {
      ostringstream oss01, oss02;
      oss01 << i_max;
      oss02 << static_cast<int>(ace_file.size());

      string str_data01 = "Number of potentilal_xs is different to that of ace_file.";
      string str_data02 = "Number of potentilal_xs : " + oss01.str();
      string str_data03 = "Number of material_id   : " + oss02.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      for(int i=0; i<i_max; i++)
      {
        oss_r << potential_xs[i];
        string str_data04 = "    " + oss_r.str();
        oss_r.str("");
        err_com.push_back(str_data04);
      }

      err_com.push_back(str_data03);
      for(int i=0; i<static_cast<int>(material_id.size()); i++)
      {
        string str_data05 = "    " + material_id[i];
        err_com.push_back(str_data05);
      }
      err_com.push_back("Please check potential scattering cross section data.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }

  //For max_pl
  //Integer         max_pl;
  if( max_pl > 7 )
  {
    ostringstream oss01;
    oss01 << max_pl;

    string str_data01 = "Maximum number of Legendre order (Pl) : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("The maximum number of Legendre order (Pl) must be less than or equal to 7.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //For reso_upscat
  //Integer         reso_up_scat_mode;
  //vector<string>  reso_up_scat_0k_data;
  i_max = static_cast<int>(reso_up_scat_0k_data.size());
  if( i_max > 0 )
  {
    if( i_max != static_cast<int>(material_id.size()) )
    {
      ostringstream oss01, oss02;
      oss01 << i_max;
      oss02 << static_cast<int>(ace_file.size());

      string str_data01 = "Number of reso_up_scat_data is different to that of ace_file.";
      string str_data02 = "Number of reso_up_scat_data : " + oss01.str();
      string str_data03 = "Number of material_id       : " + oss02.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      for(int i=0; i<i_max; i++)
      {
        string str_data04 = "    " + reso_up_scat_0k_data[i];
        err_com.push_back(str_data04);
      }

      err_com.push_back(str_data03);
      for(int i=0; i<static_cast<int>(material_id.size()); i++)
      {
        string str_data05 = "    " + material_id[i];
        err_com.push_back(str_data05);
      }
      err_com.push_back("Please check resonance up-scattering data.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputConverter::make_input_data_list()
{
  input_data_key.clear();
  clr_obj.clear_vec_array2_str(input_data);

  vector<string> str_vec;
  string str_data;
  str_vec.clear();
  str_data.clear();

  ostringstream oss;
  oss.str("");
  int sig_no = 15;

  //For ultra_fine_group
  //vector<Real>    ultra_fine_group_ene;
  //vector<Integer> ultra_fine_group_div_no;
  //vector<string>  ultra_fine_group_opt;
  input_data_key.push_back("ultra_fine_group");

  int i_max = static_cast<int>(ultra_fine_group_opt.size());
  for(int i=0; i<i_max; i++)
  {
    oss << setw(sig_no) << std::showpoint << std::scientific << ultra_fine_group_ene[i];
    str_data = "  " + oss.str();
    oss.str("");

    oss << setw(sig_no) << std::showpoint << std::scientific << ultra_fine_group_div_no[i];
    str_data = str_data + "  " + oss.str() + "  " + ultra_fine_group_opt[i];
    oss.str("");

    str_vec.push_back(str_data);
  }

  oss << setw(sig_no) << std::showpoint << std::scientific << ultra_fine_group_ene[i_max];
  str_data = "  " + oss.str();
  oss.str("");
  str_vec.push_back(str_data);
  str_data.clear();

  input_data.push_back(str_vec);
  str_vec.clear();

  //For mult_group
  //vector<Real>    multi_group;
  input_data_key.push_back("multi_group");
  i_max = static_cast<int>(multi_group.size());

  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      oss << setw(sig_no) << std::showpoint << std::scientific << multi_group[i];
      str_data = str_data + "  " + oss.str();
      oss.str("");

      if( (i+1)%10 == 0 )
      {
        str_vec.push_back(str_data);
        str_data.clear();
      }
    }
    if( static_cast<int>(str_data.size()) > 0 )
    {
      str_vec.push_back(str_data);
      str_data.clear();
    }
  }
  else
  {
    str_vec = multi_group_auto;
  }

  input_data.push_back(str_vec);
  str_vec.clear();

  //For default_spectrum
  //string          default_spectrum_mode;
  //Real            default_spectrum_eh,       default_spectrum_el,
  //                default_spectrum_temp_fis, default_spectrum_temp_maxwell,
  //                default_spectrum_el_fis,   default_spectrum_eh_maxwell;
  //vector<Real>    default_spectrum_ene,      default_spectrum_weight;
  input_data_key.push_back("default_spectrum");
  str_vec.push_back(default_spectrum_mode);

  string e_mode       = "1/e";
  string maxwell_mode = "fission+1/e+maxwell";
  string mode_name    = default_spectrum_mode;
  transform(mode_name.begin(), mode_name.end(), mode_name.begin(), ::tolower);
  if( mode_name == maxwell_mode )
  {
    oss << setw(sig_no) << std::showpoint << std::scientific << default_spectrum_eh;
    str_data = "  " + oss.str();
    oss.str("");

    oss << setw(sig_no) << std::showpoint << std::scientific << default_spectrum_el;
    str_data = str_data + "  " + oss.str();
    oss.str("");

    oss << setw(sig_no) << std::showpoint << std::scientific << default_spectrum_temp_fis;
    str_data = str_data + "  " + oss.str();
    oss.str("");

    oss << setw(sig_no) << std::showpoint << std::scientific << default_spectrum_temp_maxwell;
    str_data = str_data + "  " + oss.str();
    oss.str("");

    oss << setw(sig_no) << std::showpoint << std::scientific << default_spectrum_el_fis;
    str_data = str_data + "  " + oss.str();
    oss.str("");

    oss << setw(sig_no) << std::showpoint << std::scientific << default_spectrum_eh_maxwell;
    str_data = str_data + "  " + oss.str();
    oss.str("");

    str_vec.push_back(str_data);
  }
  else if( mode_name == e_mode )
  {
  }
  else //if( mode_name == "input" )
  {
    i_max = static_cast<int>(default_spectrum_ene.size());
    for(int i=0; i<i_max; i++)
    {
      oss << setw(sig_no) << std::showpoint << std::scientific << default_spectrum_ene[i];
      str_data = "  " + oss.str();
      oss.str("");

      oss << setw(sig_no) << std::showpoint << std::scientific << default_spectrum_weight[i];
      str_data = str_data + "  " + oss.str();
      oss.str("");

      str_vec.push_back(str_data);
    }
  }

  input_data.push_back(str_vec);
  str_vec.clear();

  //For material
  //vector<string>  material_id;
  //vector<Real>    material_number_density;
  //vector<string>  material_sab_id,  material_sab_type;
  input_data_key.push_back("material");

  i_max = static_cast<int>(material_id.size());
  if( static_cast<int>(material_sab_id.size()) == 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      str_data = "  " + material_id[i];

      oss << setw(sig_no) << std::showpoint << std::scientific << material_number_density[i];
      str_data = str_data + "  " + oss.str();
      oss.str("");
      str_vec.push_back(str_data);
    }
  }
  else
  {
    for(int i=0; i<i_max; i++)
    {
      if( static_cast<int>(material_sab_id[i].size()) > 0 )
      {
        str_data = "  " + material_id[i]
                 + "  " + material_sab_id[i] + "  " + material_sab_type[i];
      }
      else
      {
        str_data = "  " + material_id[i];
      }

      oss << setw(sig_no) << std::showpoint << std::scientific << material_number_density[i];
      str_data = str_data + "  " + oss.str();
      oss.str("");
      str_vec.push_back(str_data);
    }
  }

  input_data.push_back(str_vec);
  str_vec.clear();

  //For ace_file
  //vector<string>  ace_file;
  input_data_key.push_back("ace_file");

  i_max = static_cast<int>(ace_file.size());
  for(int i=0; i<i_max; i++)
  {
    str_data = "  " + ace_file[i];
    str_vec.push_back(str_data);
  }

  input_data.push_back(str_vec);
  str_vec.clear();

  //For thermal_cutoff
  //Real            thermal_cutoff_ene_in, thermal_cutoff_ene_out;
  input_data_key.push_back("thermal_cutoff");
  oss << setw(sig_no) << std::showpoint << std::scientific << thermal_cutoff_ene_in;
  str_data = "  " + oss.str();
  oss.str("");

  oss << setw(sig_no) << std::showpoint << std::scientific << thermal_cutoff_ene_out;
  str_data = str_data + "  " + oss.str();
  oss.str("");
  str_vec.push_back(str_data);

  input_data.push_back(str_vec);
  str_vec.clear();

  //For calc_cond
  //vector<string>  calc_cond_opt;
  //vector<Real>    calc_cond_atomic_weight, calc_cond_el, calc_cond_eh;
  //string          calc_cond_sab_opt; //NoThermalXS

  i_max = static_cast<int>(calc_cond_opt.size());
  if( i_max > 0 )
  {
    input_data_key.push_back("calc_cond");
    for(int i=0; i<i_max; i++)
    {
      str_data = "  " + calc_cond_opt[i];

      if( static_cast<int>(calc_cond_atomic_weight.size()) > 0 )
      {
        oss << setw(sig_no) << std::showpoint << std::scientific << calc_cond_atomic_weight[i];
        str_data = str_data + "  " + oss.str();
        oss.str("");

        oss << setw(sig_no) << std::showpoint << std::scientific << calc_cond_eh[i];
        str_data = str_data + "  " + oss.str();
        oss.str("");

        oss << setw(sig_no) << std::showpoint << std::scientific << calc_cond_el[i];
        str_data = str_data + "  " + oss.str();
        oss.str("");
      }

      str_vec.push_back(str_data);
    }

    if( static_cast<int>(calc_cond_sab_opt.length()) > 0 )
    {
      str_vec.push_back(calc_cond_sab_opt);
    }

    input_data.push_back(str_vec);
    str_vec.clear();
  }

  //For bg_xs_set
  //vector<Real>    bg_xs_set;
  input_data_key.push_back("bg_xs_set");

  i_max = static_cast<int>(bg_xs_set.size());
  str_data.clear();

  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      oss << setw(sig_no) << std::showpoint << std::scientific << bg_xs_set[i];
      str_data = str_data + "  " + oss.str();
      oss.str("");

      if( (i+1)%10 == 0 )
      {
        str_vec.push_back(str_data);
        str_data.clear();
      }
    }
    if( static_cast<int>(str_data.size()) > 0 )
    {
      str_vec.push_back(str_data);
      str_data.clear();
    }
  }
  else
  {
    str_vec.push_back(bg_xs_auto);
  }
  input_data.push_back(str_vec);
  str_vec.clear();

  //For potential_xs
  //vector<Real>    potential_xs;
  i_max = static_cast<int>(potential_xs.size());
  if( i_max > 0 )
  {
    input_data_key.push_back("potential_xs");

    str_data.clear();
    for(int i=0; i<i_max; i++)
    {
      oss << setw(sig_no) << std::showpoint << std::scientific << potential_xs[i];
      str_data = "  " + material_id[i] + "  " + oss.str();
      oss.str("");
      str_vec.push_back(str_data);
      str_data.clear();
    }

    input_data.push_back(str_vec);
    str_vec.clear();
  }

  //For max_pl
  //Integer         max_pl;
  input_data_key.push_back("max_pl");

  oss << setw(sig_no) << std::showpoint << std::scientific << max_pl;
  str_data = "  " + oss.str();
  oss.str("");
  str_vec.push_back(str_data);

  input_data.push_back(str_vec);
  str_vec.clear();

  //For reso_upscat
  //Integer         reso_up_scat_mode;
  //vector<string>  reso_up_scat_0k_data;
  i_max = static_cast<int>(reso_up_scat_0k_data.size());
  if( i_max > 0 )
  {
    input_data_key.push_back("reso_upscat");
    str_data.clear();
    for(int i=0; i<i_max; i++)
    {
      if( static_cast<int>(reso_up_scat_0k_data[i].length()) > 0 )
      {
        str_data = "  " + material_id[i] + "  " +  reso_up_scat_0k_data[i];

        if( reso_up_scat_mode == f_inp_obj.reso_up_scat_1d )
        {
          str_data = str_data + "  1D";
        }
        str_vec.push_back(str_data);
        str_data.clear();
      }
    }

    input_data.push_back(str_vec);
    str_vec.clear();
  }

  //For edit_xs
  //string          edit_xs_opt;
  //vector<Integer> edit_xs_mt;
  input_data_key.push_back("edit_xs");

  i_max = static_cast<int>(edit_xs_opt.size());
  for(int i=0; i<i_max; i++)
  {
    str_data = "  " + edit_xs_opt[i];
    str_vec.push_back(str_data);

    int j_max = static_cast<int>(edit_xs_mt[i].size());
    str_data.clear();
    for(int j=0; j<j_max; j++)
    {
      oss << setw(sig_no) << std::showpoint << std::scientific << edit_xs_mt[i][j];
      str_data = str_data + "  " + oss.str();
      oss.str("");
    }
    if( static_cast<int>(str_data.size()) > 0 )
    {
      str_vec.push_back(str_data);
    }
  }

  input_data.push_back(str_vec);
  str_vec.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//*** Setter ***//
void MultiGroupDataGeneratorInputConverter::set_input_obj_frendy(MultiGroupDataGeneratorInputReader inp_obj)
{
  set_data_flg  = 0;
  set_data_mode = frendy_mode;

  f_inp_obj     = inp_obj;
  inp_obj.clear();
}

void MultiGroupDataGeneratorInputConverter::set_input_obj_njoy
       (int i, int j, NuclearDataInfoNjoyMG& nucl_data_info_obj,
        GrouprInputReader inp_obj_groupr, MatxsrInputReader inp_obj_matxsr,
        int tsl_flg, FastAceDataObject&           ace_obj_fast,
                     ThermalScatterAceDataObject& ace_obj_tsl)
{
  set_data_flg  = 0;
  set_data_mode = njoy_mode;

  pos_i         = i;
  pos_j         = j;

  n_inp_obj     = nucl_data_info_obj;
  groupr_obj    = inp_obj_groupr;
  matxsr_obj    = inp_obj_matxsr;
  inp_obj_groupr.clear();
  inp_obj_matxsr.clear();

  tsl_data_flg      = tsl_flg;
  ace_data_obj_fast = ace_obj_fast;
  ace_data_obj_tsl  = ace_obj_tsl;
}

void MultiGroupDataGeneratorInputConverter::set_material_id(vector<string> str_vec)
{
  material_id_set = str_vec;
}

void MultiGroupDataGeneratorInputConverter::set_material_sab_id(vector<string> str_vec)
{
  material_sab_id_set = str_vec;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//*** Getter ***//
//For ultra_fine_group
vector<Real>    MultiGroupDataGeneratorInputConverter::get_ultra_fine_group_ene()
{
  convert_input_data();

  return ultra_fine_group_ene;
}

vector<Integer> MultiGroupDataGeneratorInputConverter::get_ultra_fine_group_div_no()
{
  convert_input_data();

  return ultra_fine_group_div_no;
}

vector<string>  MultiGroupDataGeneratorInputConverter::get_ultra_fine_group_opt()
{
  convert_input_data();

  return ultra_fine_group_opt;
}

//For mult_group
vector<Real>    MultiGroupDataGeneratorInputConverter::get_multi_group()
{
  convert_input_data();

  sort(multi_group.begin(), multi_group.end());
  return multi_group;
}

vector<Real>    MultiGroupDataGeneratorInputConverter::get_multi_group_gam()
{
  convert_input_data();

  sort(multi_group_gam.begin(), multi_group_gam.end());
  return multi_group_gam;
}

//For default_spectrum
string          MultiGroupDataGeneratorInputConverter::get_default_spectrum_mode()
{
  convert_input_data();

  return default_spectrum_mode;
}

Real            MultiGroupDataGeneratorInputConverter::get_default_spectrum_eh()
{
  convert_input_data();

  return default_spectrum_eh;
}

Real            MultiGroupDataGeneratorInputConverter::get_default_spectrum_el()
{
  convert_input_data();

  return default_spectrum_el;
}

Real            MultiGroupDataGeneratorInputConverter::get_default_spectrum_temp_fis()
{
  convert_input_data();

  return default_spectrum_temp_fis;
}

Real            MultiGroupDataGeneratorInputConverter::get_default_spectrum_temp_maxwell()
{
  convert_input_data();

  return default_spectrum_temp_maxwell;
}

Real            MultiGroupDataGeneratorInputConverter::get_default_spectrum_el_fis()
{
  convert_input_data();

  return default_spectrum_el_fis;
}

Real            MultiGroupDataGeneratorInputConverter::get_default_spectrum_eh_maxwell()
{
  convert_input_data();

  return default_spectrum_eh_maxwell;
}

vector<Real>    MultiGroupDataGeneratorInputConverter::get_default_spectrum_ene()
{
  convert_input_data();

  return default_spectrum_ene;
}

vector<Real>    MultiGroupDataGeneratorInputConverter::get_default_spectrum_weight()
{
  convert_input_data();

  return default_spectrum_weight;
}

//For material
vector<string>  MultiGroupDataGeneratorInputConverter::get_material_id()
{
  convert_input_data();

  return material_id;
}

vector<Real>    MultiGroupDataGeneratorInputConverter::get_material_number_density()
{
  convert_input_data();

  return material_number_density;
}

vector<string>  MultiGroupDataGeneratorInputConverter::get_material_sab_id()
{
  convert_input_data();

  return material_sab_id;
}

vector<string>  MultiGroupDataGeneratorInputConverter::get_material_sab_type()
{
  convert_input_data();

  return material_sab_type;
}

//For ace_file
vector<string>  MultiGroupDataGeneratorInputConverter::get_ace_file()
{
  convert_input_data();

  return ace_file;
}

vector<string>  MultiGroupDataGeneratorInputConverter::get_ace_file_fast()
{
  convert_input_data();

  return ace_file_fast;
}

vector<string>  MultiGroupDataGeneratorInputConverter::get_ace_file_tsl()
{
  convert_input_data();

  return ace_file_tsl;
}

//For thermal_cutoff
Real            MultiGroupDataGeneratorInputConverter::get_thermal_cutoff_ene_in()
{
  convert_input_data();

  return thermal_cutoff_ene_in;
}

Real            MultiGroupDataGeneratorInputConverter::get_thermal_cutoff_ene_out()
{
  convert_input_data();

  return thermal_cutoff_ene_out;
}

//For calc_cond
vector<string>  MultiGroupDataGeneratorInputConverter::get_calc_cond_opt()
{
  convert_input_data();

  return calc_cond_opt;
}

vector<Real>    MultiGroupDataGeneratorInputConverter::get_calc_cond_atomic_weight()
{
  convert_input_data();

  return calc_cond_atomic_weight;
}

vector<Real>    MultiGroupDataGeneratorInputConverter::get_calc_cond_el()
{
  convert_input_data();

  return calc_cond_el;
}

vector<Real>    MultiGroupDataGeneratorInputConverter::get_calc_cond_eh()
{
  convert_input_data();

  return calc_cond_eh;
}

string          MultiGroupDataGeneratorInputConverter::get_calc_cond_sab_opt()
{
  convert_input_data();

  return calc_cond_sab_opt;
}

//For bg_xs_set
vector<Real>    MultiGroupDataGeneratorInputConverter::get_bg_xs_set()
{
  convert_input_data();

  return bg_xs_set;
}

//For max_pl
Integer         MultiGroupDataGeneratorInputConverter::get_max_pl()
{
  convert_input_data();

  return max_pl;
}

//For reso_upscat
Integer         MultiGroupDataGeneratorInputConverter::get_reso_up_scat_mode()
{
  convert_input_data();

  return reso_up_scat_mode;
}

vector<string>  MultiGroupDataGeneratorInputConverter::get_reso_up_scat_0k_data()
{
  convert_input_data();

  return reso_up_scat_0k_data;
}


//For edit_xs
vector<string>           MultiGroupDataGeneratorInputConverter::get_edit_xs_opt()
{
  convert_input_data();

  return edit_xs_opt;
}

vector<vector<Integer> > MultiGroupDataGeneratorInputConverter::get_edit_xs_mt()
{
  convert_input_data();

  return edit_xs_mt;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//For input data of FRENDY/MG
vector<string>  MultiGroupDataGeneratorInputConverter::get_input_data_key()
{
  convert_input_data();

  return input_data_key;
}

vector<vector<string> > MultiGroupDataGeneratorInputConverter::get_input_data()
{
  convert_input_data();

  return input_data;
}

map<string, vector<string> > MultiGroupDataGeneratorInputConverter::get_input_data_map()
{
  convert_input_data();

  int i_max = static_cast<int>(input_data_key.size());
  if( i_max != static_cast<int>(input_data.size()) )
  {
    string class_name = "MultiGroupDataGeneratorInputConverter";
    string func_name  = "get_input_data_map()";

    ostringstream oss01, oss02;
    oss01 << i_max;
    oss02 << static_cast<int>(input_data.size());

    string str01 = "  Data size of input_data_key : " + oss01.str();
    string str02 = "  Data size of input_data     : " + oss02.str();

    vector<string> err_com;
    err_com.push_back("The data size of input_data_key is different to that of input_data.");
    err_com.push_back("Please check input_data_key and input_data.");
    err_com.push_back("");
    err_com.push_back(str01);
    err_com.push_back(str02);
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  map<string, vector<string> > input_data_map;
  for(int i=0; i<i_max; i++)
  {
    input_data_map[input_data_key[i]] = input_data[i];
  }

  return input_data_map;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputConverter::output_input_data()
{
  convert_input_data();

  int i_max = static_cast<int>(input_data_key.size());
  if( i_max != static_cast<int>(input_data.size()) )
  {
    string class_name = "MultiGroupDataGeneratorInputConverter";
    string func_name  = "output_input_data()";

    ostringstream oss01, oss02;
    oss01 << i_max;
    oss02 << static_cast<int>(input_data.size());

    string str01 = "  Data size of input_data_key : " + oss01.str();
    string str02 = "  Data size of input_data     : " + oss02.str();

    vector<string> err_com;
    err_com.push_back("The data size of input_data_key is different to that of input_data.");
    err_com.push_back("Please check input_data_key and input_data.");
    err_com.push_back("");
    err_com.push_back(str01);
    err_com.push_back(str02);
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  cout << "========== Input data for FRENDY/MG ==========" << endl;
  cout << endl;
  for(int i=0; i<i_max; i++)
  {
    cout << input_data_key[i] << endl;

    int j_max = static_cast<int>(input_data[i].size());
    for(int j=0; j<j_max; j++)
    {
      cout << "  " << input_data[i][j] << endl;
    }
    cout << endl;
  }
  cout << endl;
  cout << "==============================================" << endl;
  cout << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

