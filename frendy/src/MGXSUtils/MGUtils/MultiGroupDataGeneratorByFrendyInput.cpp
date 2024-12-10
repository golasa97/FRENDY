//-----------------------------------------------------
// Multi-group cross section generator from ACE file
//-----------------------------------------------------

#include "MGXSUtils/MGUtils/MultiGroupDataGeneratorByFrendyInput.hpp"

using namespace frendy;

//constructor
MultiGroupDataGeneratorByFrendyInput::MultiGroupDataGeneratorByFrendyInput(void)
{
  clear();
}

//destructor
MultiGroupDataGeneratorByFrendyInput::~MultiGroupDataGeneratorByFrendyInput(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorByFrendyInput::clear()
{
  mat_no.clear();
  tsl_mt_no = 0;

  f_inp_obj.clear();
  conv_inp_obj.clear();

  vector<NuclearDataObject>().swap(nucl_data_obj);

  vector<FastAceDataObject>().swap(ace_obj_fast);
  vector<ThermalScatterAceDataObject>().swap(ace_obj_tsl);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorByFrendyInput::run_frendy_mg()
{
  int ace_file_no = static_cast<int>(ace_obj_fast.size());
  if( ace_file_no == 0 )
  {
    read_ace_file();
    ace_file_no = static_cast<int>(ace_obj_fast.size());
  }

  vector<string> mat_id_vec;
  mat_id_vec.resize(ace_file_no);
  for(int i=0; i<ace_file_no; i++)
  {
    mat_id_vec[i] = ace_obj_fast[i].get_title_data()[0];
  }
  conv_inp_obj.set_material_id(mat_id_vec);

  if( static_cast<int>(ace_obj_tsl.size()) > 0 )
  {
    mat_id_vec.clear();
    mat_id_vec.resize(static_cast<int>(ace_obj_tsl.size()));
    for(int i=0; i<static_cast<int>(ace_obj_tsl.size()); i++)
    {
      if( static_cast<int>(ace_obj_tsl[i].get_title_data().size()) > 0 )
      {
        mat_id_vec[i] = ace_obj_tsl[i].get_title_data()[0];
      }
      else
      {
        mat_id_vec[i].clear();
      }
    }
    conv_inp_obj.set_material_sab_id(mat_id_vec);
  }

  //Comparison of temperature of ACE files and input file
  check_temp();

  //Output input data of FRENDY/MG
  conv_inp_obj.output_input_data();

  //stab for frendy integration
  map<string, vector<string> > input_data = conv_inp_obj.get_input_data_map();

  //Running FRENDY/MG
  FMGen::FMGenerator fm_gen;
  fm_gen.readInputData(input_data);

  //repeat the following for necessary times. set data for fast and thermal ace files
  for(int i=0; i<ace_file_no; i++)
  {
    FastAceDataWriter ace_wri_obj;

    string zaid;
    vector<string> _title;
    vector<int> _izaw;
    vector<int> _nxs;
    vector<int> _jxs;
    vector<double> _xss;
    ace_wri_obj.set_ace_data_obj(ace_obj_fast[i]);
    ace_wri_obj.get_ace_data_for_mg(_title, _izaw, _nxs, _jxs, _xss);

    //zaid is the first data of _title[0]
    zaid = str_obj.trim_space(_title[0]);
    string::size_type zaid_end_pos = zaid.find_first_of(" ");
    if( zaid_end_pos != string::npos )
    {
      zaid = zaid.substr(0, static_cast<int>(zaid_end_pos));
    }

    fm_gen.data_container.setACEFileData(zaid, _title, _izaw, _nxs, _jxs, _xss);
  }

  if( static_cast<int>(ace_obj_tsl.size()) > 0 )
  {
    if( ace_file_no != static_cast<int>(ace_obj_tsl.size()) )
    {
      string class_name = "MultiGroupDataGeneratorByFrendyInput";
      string func_name  = "run_frendy_mg()";

      ostringstream oss01, oss02;
      oss01 << ace_file_no;
      oss02 << static_cast<int>(ace_obj_tsl.size());

      string str_data01 = "  Data size of ace_obj_fast : " + oss01.str();
      string str_data02 = "  Data size of ace_obj_tsl  : " + oss02.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back("");
      err_com.push_back("The data size of ace_obj_fast is different to that of ace_obj_tsl.");
      err_com.push_back("Please check ace_obj_fast and ace_obj_tsl.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    for(int i=0; i<ace_file_no; i++)
    {
      if( static_cast<int>(ace_obj_tsl[i].get_title_data().size()) == 0 )
      {
        continue;
      }

      ThermalScatterAceDataWriter ace_wri_obj;

      string zaid;
      vector<string> _title;
      vector<int> _izaw;
      vector<int> _nxs;
      vector<int> _jxs;
      vector<double> _xss;
      ace_wri_obj.set_ace_data_obj(ace_obj_tsl[i]);
      ace_wri_obj.get_ace_data_for_mg(_title, _izaw, _nxs, _jxs, _xss);

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

  fm_gen.data_container.checkACEFiles();
  fm_gen.data_container.readAndSetUFEnergyGroupStructure();
  fm_gen.data_container.doInitialize();

  fm_gen.run();

  run_mg_photon_production(fm_gen);

  write_xs_data(fm_gen);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorByFrendyInput::check_temp()
{
  int ace_file_no = static_cast<int>(ace_obj_fast.size());

  vector<Real> temp_ace_fast, temp_ace_tsl;
  temp_ace_fast.resize(ace_file_no);
  for(int i=0; i<ace_file_no; i++)
  {
    temp_ace_fast[i] = ace_obj_fast[i].get_temp_kelvin();
  }

  temp_ace_tsl = temp_ace_fast;
  if( static_cast<int>(ace_obj_tsl.size()) > 0 )
  {
    for(int i=0; i<static_cast<int>(ace_obj_tsl.size()); i++)
    {
      if( static_cast<int>(ace_obj_tsl[i].get_title_data().size()) > 0 )
      {
        temp_ace_tsl[i] = ace_obj_tsl[i].get_temp_kelvin();
      }
    }
  }

  //Comparison of temperature of ACE files
  for(int i=0; i<ace_file_no; i++)
  {
    if( fabs(temp_ace_fast[i]) < min_value )
    {
      continue;
    }

    Real temp_dif = fabs(temp_ace_fast[i] - temp_ace_tsl[i]);
    if( temp_ace_fast[i] > min_value )
    {
      temp_dif /= temp_ace_fast[i];
    }

    if( temp_dif > 1.0E-3 )
    {
      string class_name = "MultiGroupDataGeneratorByFrendyInput";
      string func_name  = "check_temp()";

      ostringstream oss01, oss02, oss03, oss04, oss05;
      oss01 << i+1;
      oss02 << ace_file_no;

      oss03.precision(8);
      oss04.precision(8);
      oss05.precision(8);
      oss03 << temp_ace_fast[i];
      oss04 << temp_ace_tsl[i];
      oss05 << temp_dif * 100.0;

      string str_data01 = "  Data position                   : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "  Temperature of ace_obj_fast [K] : " + oss03.str();
      string str_data03 = "  Temperature of ace_obj_tsl [K]  : " + oss04.str();
      string str_data04 = "  Relative difference             : " + oss05.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back(str_data04);
      err_com.push_back("");
      err_com.push_back("Temperature of ace_obj_fast is different to that of ace_obj_tsl.");

      if( temp_dif > 1.0E-1 )
      {
        err_com.push_back("Please check ace_obj_fast and ace_obj_tsl.");
        err_obj.output_runtime_error(class_name, func_name, err_com);
      }
      else
      {
        err_com.push_back("The ace_obj_fast or ace_obj_tsl data may be incorrect.");
        err_obj.output_caution(class_name, func_name, err_com);
      }
    }
  }


  //Comparison of temperature of input file and fast ACE file
  FrendyInputCommonUtils inp_obj_common;
  Real temp_def = inp_obj_common.get_temp_def();

  Real temp_inp = f_inp_obj.get_temp();
  for(int i=0; i<ace_file_no; i++)
  {
    Real temp_ace = temp_ace_fast[i];
    if( fabs(temp_ace) < min_value )
    {
      temp_ace = temp_ace_tsl[i];
    }

    Real temp_dif_def = fabs((temp_ace - temp_def) / temp_def);
    if( temp_dif_def < 1.0E-4 )
    {
      continue;
    }

    Real temp_dif     = fabs(temp_ace - temp_inp);
    if( temp_ace > min_value )
    {
      temp_dif /= temp_ace;
    }

    if( temp_dif > 1.0E-3 )
    {
      string class_name = "MultiGroupDataGeneratorByFrendyInput";
      string func_name  = "check_temp()";

      ostringstream oss01, oss02, oss03, oss04, oss05;
      oss01 << i+1;
      oss02 << ace_file_no;

      oss03.precision(8);
      oss04.precision(8);
      oss05.precision(8);
      oss03 << temp_ace;
      oss04 << temp_inp;
      oss05 << temp_dif * 100.0;

      string str_data01 = "  Data position                 : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "  Temperature of ace file [K]   : " + oss03.str();
      string str_data03 = "  Temperature of input file [K] : " + oss04.str();
      string str_data04 = "  Relative difference           : " + oss05.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back(str_data04);
      err_com.push_back("");
      err_com.push_back("Temperature of the ace file is different to that of the input file.");

      if( temp_dif > 1.0E-1 )
      {
        err_com.push_back("Please check the input file and the ace file.");
        err_obj.output_runtime_error(class_name, func_name, err_com);
      }
      else
      {
        err_com.push_back("The input file or the ace file may be incorrect.");
        err_obj.output_caution(class_name, func_name, err_com);
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorByFrendyInput::run_mg_photon_production(FMGen::FMGenerator& fm_gen)
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
//    int pl_no = 0;

  int i_max = static_cast<int>(ace_obj_fast.size());
  g_prod_obj.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    g_prod_obj[i].calc_photon_production_data(ace_obj_fast[i], ene_vec, flux_vec_mod, st_sb_vec_mod,
                                              mg_ein, mg_eout, pl_no);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorByFrendyInput::write_xs_data(FMGen::FMGenerator& fm_gen)
{
  vector<string>          matxs_name, gendf_name;
  vector<vector<string> > matxs_data_str, gendf_data_str;
  string suffix_str = ".txt";

  map<string, string>::iterator it;
  for (it  = fm_gen.data_container.output_list_data.begin();
       it != fm_gen.data_container.output_list_data.end(); it++)
  {
    string wk = it->first;
    if( wk.substr(0, 7) == "FMMatxs" )
    {
      //Get string data of MATXS file
      vector<string> matxs_tmp = str_obj.divide_string_data_by_linefeed_code
                                   (fm_gen.data_container.output_list_data[wk]);
      if( static_cast<int>(matxs_tmp.size()) > 0 )
      {
        string matxs_name_tmp = wk.substr(12); //FMMatxsFile_
        matxs_name_tmp = str_obj.remove_suffix(matxs_name_tmp, suffix_str);
        matxs_name_tmp = str_obj.replace_space(matxs_name_tmp, "_");
        matxs_name.push_back(matxs_name_tmp);

        matxs_data_str.push_back(matxs_tmp);
        vector<string>().swap(matxs_tmp);
      }
    }
    else if( wk.substr(0, 7) == "FMGENDF" )
    {
      //Get string data of GENDF file
      vector<string> gendf_tmp = str_obj.divide_string_data_by_linefeed_code
                                   (fm_gen.data_container.output_list_data[wk]);
      if( static_cast<int>(gendf_tmp.size()) > 0 )
      {
        string gendf_name_tmp = wk.substr(12); //FMGENDFFile_
        gendf_name_tmp = str_obj.remove_suffix(gendf_name_tmp, suffix_str);
        gendf_name_tmp = str_obj.replace_space(gendf_name_tmp, "_");
        gendf_name.push_back(gendf_name_tmp);

        gendf_data_str.push_back(gendf_tmp);
        vector<string>().swap(gendf_tmp);
      }
    }
    else
    {
      write_other_data(wk, fm_gen);
    }
  }

  write_gendf(gendf_name, gendf_data_str);
  write_matxs(matxs_name, matxs_data_str);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorByFrendyInput::write_matxs(vector<string>& matxs_name,
                                                       vector<vector<string> >& matxs_data_str)
{
  Real temp_inp = f_inp_obj.get_temp();

  //Read MATXS file
  int matxs_no = static_cast<int>(matxs_data_str.size());
  vector<MatxsCommonData> matxs_obj;
  matxs_obj.resize(matxs_no);

  for(int i=0; i<matxs_no; i++)
  {
    MatxsParser read_matxs_obj;
    read_matxs_obj.set_text(matxs_data_str[i]);
    matxs_obj[i] = read_matxs_obj.get_matxs_obj();
    read_matxs_obj.clear();
    vector<string>().swap(matxs_data_str[i]);

    //Modify temperature
    vector<MatxsMaterialData> matxs_mat_obj = matxs_obj[i].get_mat_obj();
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
        if( fabs(temp_matxs[l] - temp_inp) < temp_dif )
        {
          temp_matxs[l] = temp_inp;
        }
      }
      matxs_mat_obj[k].set_temp(temp_matxs);
      temp_matxs.clear();
    }
    matxs_obj[i].set_mat_obj(matxs_mat_obj);
    vector<MatxsMaterialData>().swap(matxs_mat_obj);

    //Modify TSL name of MATXS file
    matxs_obj[i].mod_tsl_name(tsl_mt_no);

    //Merge photon production data
    int j_max = static_cast<int>(g_prod_obj.size());
    if( j_max > 0 && static_cast<int>(matxs_obj[i].get_mat_obj().size()) > 0 )
    {
      Real awr_matxs = matxs_obj[i].get_mat_obj()[0].get_amass();

      for(int j=0; j<j_max; j++)
      {
        Real awr_photon = g_prod_obj[j].get_awr_val();
        if( fabs(awr_matxs - awr_photon) < fabs(awr_photon * 1.0E-6) )
        {
          vector<GMF16Parser> mf16_vec = g_prod_obj[j].get_mf16_data();
          vector<Real>        mg_ein   = conv_inp_obj.get_multi_group();
          vector<Real>        mg_eout  = conv_inp_obj.get_multi_group_gam();

          matxs_obj[i].add_photon_production_data(mf16_vec, mg_ein, mg_eout);

          vector<GMF16Parser>().swap(mf16_vec);
          mg_ein.clear();
          mg_eout.clear();
          break;
        }
      }
    }
  }
  vector<vector<string> >().swap(matxs_data_str);

  //Output MATXS file
  vector<string> mg_file_name = f_inp_obj.get_mg_file_name();
  vector<string> mg_edit_mode = f_inp_obj.get_mg_edit_mode();
  for(int i=0; i<static_cast<int>(mg_file_name.size()); i++)
  {
    transform(mg_edit_mode[i].begin(), mg_edit_mode[i].end(), mg_edit_mode[i].begin(), ::tolower);
    mg_edit_mode[i] = str_obj.replace_space(mg_edit_mode[i], "_");

    if( mg_edit_mode[i] == "matxs" || mg_edit_mode[i] == "simplematxs" )
    {
      //Output MATXS file
      for(int j=0; j<matxs_no; j++)
      {
        string out_name = mg_file_name[i];
        if( matxs_no > 0 )
        {
          string suffix_str = ".mg";
          //out_name = str_obj.remove_suffix(out_name, suffix_str);
          out_name = out_name + "_" + matxs_name[j] + suffix_str;
        }

        cout << "  Write MATXS file : " << out_name << endl;
        cout << endl;

        MatxsWriter wri_obj;
        wri_obj.set_matxs_obj(matxs_obj[j]);
        wri_obj.write_matxs(out_name);
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorByFrendyInput::write_gendf(vector<string>& gendf_name,
                                                       vector<vector<string> >& gendf_data_str)
{
  Real temp_inp = f_inp_obj.get_temp();

  //Read GENDF file
  int gendf_no = static_cast<int>(gendf_data_str.size());
  vector<GendfParser> read_gendf_obj;
  read_gendf_obj.resize(gendf_no);

  for(int i=0; i<gendf_no; i++)
  {
    read_gendf_obj[i].set_text(gendf_data_str[i]);
    vector<string>().swap(gendf_data_str[i]);

    Real za_gendf = read_gendf_obj[i].get_mf01_mt451_data().get_ZA();

    //Merge photon production data
    int j_max = static_cast<int>(g_prod_obj.size());
    if( j_max > 0 )
    {
      for(int j=0; j<j_max; j++)
      {
        Real za_photon = static_cast<Real>(g_prod_obj[j].get_za_val());
        if( fabs(za_gendf - za_photon) < fabs(za_photon * 1.0E-6) )
        {
          g_prod_obj[j].merge_gendf(read_gendf_obj[i]);
          break;
        }
      }
    }


    j_max = static_cast<int>(nucl_data_obj.size());
    if( j_max > 0 )
    {
      for(int j=0; j<j_max; j++)
      {
        Real za_nucl  = nucl_data_obj[j].get_general_data_obj().get_mat_data();
        if( fabs(za_gendf - za_nucl) < fabs(za_nucl * 1.0E-6) )
        {
          //Modify MAT number of GENDF file
          read_gendf_obj[i].set_mat_no(nucl_data_obj[j].get_general_data_obj().get_mat_no());

          //Modify LR flag in GMF03
          read_gendf_obj[i].mod_reaction_flg(nucl_data_obj[j]);
          break;
        }
      }
    }
    else
    {
      int ace_no = static_cast<int>(ace_obj_fast.size());
      vector<string> str_vec;
      vector<Real>   awr_vec;
      str_vec.resize(ace_no);
      awr_vec.resize(ace_no);
      for(int j=0; j<ace_no; j++)
      {
        str_vec[j] = ace_obj_fast[j].get_title_data()[2];
        awr_vec[j] = ace_obj_fast[j].get_aw0();
      }

      ace_no = static_cast<int>(ace_obj_tsl.size());
      if( ace_no > 0 )
      {
        for(int j=0; j<ace_no; j++)
        {
          vector<string> str_tsl = ace_obj_tsl[j].get_title_data();
          Real           awr_tsl = ace_obj_tsl[j].get_aw0();
          if( static_cast<int>(str_tsl.size()) > 2 && awr_tsl > min_value )
          {
            string::size_type char_pos = str_tsl[2].find("mat");
            if( char_pos != string::npos )
            {
              str_vec[j] = str_tsl[2];
              awr_vec[j] = awr_tsl;
            }
          }
        }
      }

           ace_no    = static_cast<int>(awr_vec.size());
      Real awr_gendf = read_gendf_obj[i].get_mf01_mt451_data().get_AWR();
      for(int j=0; j<ace_no; j++)
      {
        if( fabs(awr_gendf - awr_vec[j]) < fabs(awr_gendf * 1.0E-4) )
        {
          string::size_type char_pos = str_vec[j].find("mat");
          if( char_pos == string::npos )
          {
            continue;
          }
          string  mat_no_str = str_vec[j].substr(char_pos+3);
                  mat_no_str = str_obj.trim_space(mat_no_str);
          Integer mat_ace    = numeric_string_cast<Integer>(mat_no_str);

          //Modify MAT number of GENDF file
          read_gendf_obj[i].set_mat_no(mat_ace);
          break;
        }
      }
    }

    if( static_cast<int>(mat_no.size()) > 0 )
    {
      read_gendf_obj[i].set_mat_no(mat_no[i]);
    }

    //Modify temperature
    Real temp_gendf = read_gendf_obj[i].get_mf01_mt451_data().get_TEMP();
    Real temp_dif = 1.0E-3;
    if( fabs(temp_gendf) > min_value )
    {
      temp_dif *= fabs(temp_gendf);
    }
    if( fabs(temp_gendf - temp_inp) < temp_dif )
    {
      read_gendf_obj[i].mod_temp(temp_inp);
    }
  }
  vector<vector<string> >().swap(gendf_data_str);

  //Output GENDF file
  vector<string> mg_file_name = f_inp_obj.get_mg_file_name();
  vector<string> mg_edit_mode = f_inp_obj.get_mg_edit_mode();
  for(int i=0; i<static_cast<int>(mg_file_name.size()); i++)
  {
    transform(mg_edit_mode[i].begin(), mg_edit_mode[i].end(), mg_edit_mode[i].begin(), ::tolower);
    mg_edit_mode[i] = str_obj.replace_space(mg_edit_mode[i], "_");
    if( mg_edit_mode[i] == "gendf" || mg_edit_mode[i] == "fullgendf" || mg_edit_mode[i] == "simplegendf" )
    {
      //Output GENDF file
      for(int j=0; j<gendf_no; j++)
      {
        string out_name = mg_file_name[i];
        if( gendf_no > 0 )
        {
          string suffix_str = ".mg";

          //out_name = str_obj.remove_suffix(out_name, suffix_str);
          out_name = out_name + "_" + gendf_name[j] + suffix_str;
        }

        cout << "  Write GENDF file : " << out_name << endl;
        cout << endl;

        GendfWriter  wri_obj;
        wri_obj.set_gendf_label(f_inp_obj.get_mg_label_data());
        wri_obj.set_gendf_parser(read_gendf_obj[j]);
        wri_obj.write_gendf_with_tape_end(out_name);
      }
    }
/*
    else
    {
      string class_name = "MultiGroupDataGeneratorByFrendyInput";
      string func_name  = "run_frendy_mg()";

      ostringstream oss01, oss02;
      oss01 << i+1;
      oss02 << static_cast<int>(mg_file_name.size());

      string str_data01 = "  Position     : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "  mg_edit_mode : " + mg_edit_mode[i];
      string str_data03 = "  mg_file_name : " + mg_file_name[i];

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back("");
      err_com.push_back("The mg_edit_mode is not available in this program.");
      err_com.push_back("The available mg_edit_mode is matxs and gendf.");
      err_obj.output_caution(class_name, func_name, err_com);
    }
*/
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorByFrendyInput::write_other_data(string wk, FMGen::FMGenerator& fm_gen)
{
  string suffix_str    = ".mg";
  string suffix_str_mg = ".txt";

  //Make output file name
  string mat_name = "";
  string::size_type mat_name_pos = wk.find_first_of("_");
  if( mat_name_pos != string::npos )
  {
    mat_name = wk.substr(static_cast<int>(mat_name_pos));
    mat_name = str_obj.remove_suffix(mat_name, suffix_str_mg);
  }

  vector<string> mg_file_name     = f_inp_obj.get_mg_file_name();
  vector<string> mg_edit_mode     = f_inp_obj.get_mg_edit_mode();

  int file_no = static_cast<int>(mg_file_name.size());
  for(int i=0; i<file_no; i++)
  {
    //mg_file_name[i] = str_obj.remove_suffix(mg_file_name[i], suffix_str);
    if( static_cast<int>(mat_name.size()) > 0 )
    {
      mg_file_name[i] = mg_file_name[i] + mat_name;
    }

    transform(mg_edit_mode[i].begin(), mg_edit_mode[i].end(), mg_edit_mode[i].begin(), ::tolower);
    mg_edit_mode[i] = str_obj.replace_space(mg_edit_mode[i], "_");
  }


  //Check output data type
  vector<string> out_name_vec;
  out_name_vec.clear();
  if( wk.substr(0, 9) == "FMMicXS1d" )
  {
    //1DXS
    for(int i=0; i<file_no; i++)
    {
      if( mg_edit_mode[i].substr(0, 4) == "1dxs" || mg_edit_mode[i].substr(0, 6) == "mg1dxs" )
      {
        string out_name = mg_file_name[i] + suffix_str;
        out_name_vec.push_back(out_name);
      }
    }
  }
  else if( wk.substr(0, 9) == "FMMicXS2d" )
  {
    //2DXS
    for(int i=0; i<file_no; i++)
    {
      if( mg_edit_mode[i].substr(0, 4) == "2dxs" || mg_edit_mode[i].substr(0, 6) == "mg2dxs" )
      {
        string out_name = mg_file_name[i] + suffix_str;
        out_name_vec.push_back(out_name);
      }
    }
  }
  else if( wk.substr(0, 7) == "FMNuChi" )
  {
    //NuChi
    for(int i=0; i<file_no; i++)
    {
      if( mg_edit_mode[i].substr(0, 5) == "nuchi" )
      {
        string out_name = mg_file_name[i] + suffix_str;
        out_name_vec.push_back(out_name);
      }
    }
  }
  else if( wk.substr(0, 8) == "FMKRAMXS" )
  {
    //KRAMXS
    for(int i=0; i<file_no; i++)
    {
      if( mg_edit_mode[i].substr(0, 6) == "kramxs" ||
          mg_edit_mode[i].substr(0, 4) == "kram" )
      {
        string out_name = mg_file_name[i] + suffix_str;
        out_name_vec.push_back(out_name);
      }
    }
  }
  else if( wk.substr(0,12) == "FMUFGMicXS1d" )
  {
    //UFG1DXS
    for(int i=0; i<file_no; i++)
    {
      if( mg_edit_mode[i].substr(0, 7) == "ufg1dxs" )
      {
        string out_name = mg_file_name[i] + suffix_str;
        out_name_vec.push_back(out_name);
      }
    }
  }
  else if (wk.substr(0, 21) == "FMUFGInputGridMicXS1d")
  {
      //UFG1DXS
      for (int i = 0; i < file_no; i++)
      {
          if (mg_edit_mode[i].substr(0, 16) == "ufg1dxsinputgrid")
          {
              string out_name = mg_file_name[i] + suffix_str;
              out_name_vec.push_back(out_name);
          }
      }
  }
  else if( wk.substr(0, 5) == "FMUFG" )
  {
    //UFG
    for(int i=0; i<file_no; i++)
    {
      if( mg_edit_mode[i].substr(0, 3) == "ufg" && mg_edit_mode[i].substr(0, 7) != "ufg1dxs" )
      {
        string ufg_mode = "flux";
        if( wk.substr(0,16) == "FMUFGTotalSource" )
        {
          ufg_mode = "src_tot";
        }
        else if( wk.substr(0,16) == "FMUFGSlowingdown" ) //FMUFGSlowingdownSource
        {
          ufg_mode = "src_sld";
        }
        else if( wk.substr(0,13) == "FMUFGSigTotal" )
        {
          ufg_mode = "sig_tot";
        }

        string out_name = mg_file_name[i] + "_" + ufg_mode + suffix_str;
        out_name_vec.push_back(out_name);
      }
    }
  }
  else if( wk.substr(0, 8) == "FMMGFlux" )
  {
    //Flux
    for(int i=0; i<file_no; i++)
    {
      if( mg_edit_mode[i].substr(0, 4) == "flux" || mg_edit_mode[i].substr(0, 6) == "mgflux" )
      {
        string out_name = mg_file_name[i] + suffix_str;
        out_name_vec.push_back(out_name);
      }
    }
  }
  else if( wk.substr(0,11) == "FMMGCurrent" )
  {
    //Current
    for(int i=0; i<file_no; i++)
    {
      if( mg_edit_mode[i].substr(0, 7) == "current" || mg_edit_mode[i].substr(0, 9) == "mgcurrent" )
      {
        string out_name = mg_file_name[i] + suffix_str;
        out_name_vec.push_back(out_name);
      }
    }
  }
  else if( wk.substr(0,5) == "FMRUC" )
  {
    //RUC (Resonance upperscattering correction)
    for(int i=0; i<file_no; i++)
    {
      if( mg_edit_mode[i].substr(0, 3) == "ruc" )
      {
        string out_name = mg_file_name[i] + suffix_str;
        out_name_vec.push_back(out_name);
      }
    }
  }
  mg_file_name.clear();
  mg_edit_mode.clear();


  //Output multi-group data
  file_no = static_cast<int>(out_name_vec.size());
  if( file_no > 0 )
  {
    cout << "  Write multi_group data" << endl;
    for(int i=0; i<file_no; i++)
    {
      string out_name = str_obj.replace_space(out_name_vec[i], "_");

      cout << "    " << i+1 << " / " << file_no << " : " << out_name << endl;
      ofstream fout_mg(out_name.c_str());
      fout_mg << fm_gen.data_container.output_list_data[wk];
      fout_mg.close();
    }
    cout << endl;
  }
  out_name_vec.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorByFrendyInput::read_ace_file()
{
  vector<string> ace_file_name_fast = conv_inp_obj.get_ace_file_fast();
  vector<string> ace_file_name_tsl  = conv_inp_obj.get_ace_file_tsl();

  if( static_cast<int>(ace_file_name_tsl.size()) == 0 )
  {
    set_ace_file_name_fast(ace_file_name_fast);
  }
  else
  {
    set_ace_file_name_tsl(ace_file_name_fast, ace_file_name_tsl);
  }

  vector<string>().swap(ace_file_name_fast);
  vector<string>().swap(ace_file_name_tsl);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorByFrendyInput::set_frendy_inp_obj(MultiGroupDataGeneratorInputReader inp_obj)
{
  f_inp_obj = inp_obj;
  inp_obj.clear();

  conv_inp_obj.set_input_obj_frendy(f_inp_obj);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorByFrendyInput::set_ace_file_name_fast(string ace_file_name)
{
  vector<FastAceDataObject>().swap(ace_obj_fast);
  vector<ThermalScatterAceDataObject>().swap(ace_obj_tsl);

  FastAceDataParser read_obj;
  read_obj.set_file_name(ace_file_name);

  ace_obj_fast.resize(1);
  ace_obj_fast[0] = read_obj.get_ace_data_obj();
  read_obj.clear();
}

void MultiGroupDataGeneratorByFrendyInput::set_ace_file_name_fast(vector<string> ace_file_name)
{
  vector<FastAceDataObject>().swap(ace_obj_fast);
  vector<ThermalScatterAceDataObject>().swap(ace_obj_tsl);

  int i_max = static_cast<int>(ace_file_name.size());
  ace_obj_fast.resize(i_max);
  
  for(int i=0; i<i_max; i++)
  {
    FastAceDataParser read_obj;
    read_obj.set_file_name(ace_file_name[i]);

    ace_obj_fast[i] = read_obj.get_ace_data_obj();
    read_obj.clear();
  }

  vector<string>().swap(ace_file_name);
}

void MultiGroupDataGeneratorByFrendyInput::set_ace_file_name_tsl
                                (string ace_file_name_fast, string ace_file_name_tsl)
{
  vector<FastAceDataObject>().swap(ace_obj_fast);
  vector<ThermalScatterAceDataObject>().swap(ace_obj_tsl);

  FastAceDataParser read_obj_fast;
  read_obj_fast.set_file_name(ace_file_name_fast);

  ace_obj_fast.resize(1);
  ace_obj_fast[0] = read_obj_fast.get_ace_data_obj();
  read_obj_fast.clear();


  ThermalScatterAceDataParser read_obj_tsl;
  read_obj_tsl.set_file_name(ace_file_name_tsl);

  ace_obj_tsl.resize(1);
  ace_obj_tsl[0] = read_obj_tsl.get_ace_data_obj();
  read_obj_tsl.clear();
}

void MultiGroupDataGeneratorByFrendyInput::set_ace_file_name_tsl
                                (vector<string> ace_file_name_fast,
                                 vector<string> ace_file_name_tsl)
{
  vector<FastAceDataObject>().swap(ace_obj_fast);
  vector<ThermalScatterAceDataObject>().swap(ace_obj_tsl);

  int i_max = static_cast<int>(ace_file_name_fast.size());
  ace_obj_fast.resize(i_max);

  for(int i=0; i<i_max; i++)
  {
    FastAceDataParser read_obj_fast;
    read_obj_fast.set_file_name(ace_file_name_fast[i]);

    ace_obj_fast[i] = read_obj_fast.get_ace_data_obj();
    read_obj_fast.clear();
  }


  i_max = static_cast<int>(ace_file_name_tsl.size());
  ace_obj_tsl.resize(i_max);
  
  for(int i=0; i<i_max; i++)
  {
    ThermalScatterAceDataParser read_obj_tsl;
    read_obj_tsl.set_file_name(ace_file_name_tsl[i]);

    ace_obj_tsl[i] = read_obj_tsl.get_ace_data_obj();
    read_obj_tsl.clear();
  }

  vector<string>().swap(ace_file_name_fast);
  vector<string>().swap(ace_file_name_tsl);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorByFrendyInput::set_mat_no(vector<Integer> int_vec)
{
  mat_no = int_vec;
}

void MultiGroupDataGeneratorByFrendyInput::set_tsl_mt_no(Integer int_val)
{
  tsl_mt_no = int_val;
}

void MultiGroupDataGeneratorByFrendyInput::set_ace_obj_fast(FastAceDataObject& ace_obj)
{
  vector<FastAceDataObject>().swap(ace_obj_fast);
  vector<ThermalScatterAceDataObject>().swap(ace_obj_tsl);

  ace_obj_fast.resize(1);
  ace_obj_fast[0] = ace_obj;
}

void MultiGroupDataGeneratorByFrendyInput::set_ace_obj_fast(vector<FastAceDataObject>& ace_obj)
{
  vector<FastAceDataObject>().swap(ace_obj_fast);
  vector<ThermalScatterAceDataObject>().swap(ace_obj_tsl);

  ace_obj_fast = ace_obj;
}

void MultiGroupDataGeneratorByFrendyInput::set_ace_obj_tsl
                               (FastAceDataObject&           ace_obj_f,
                                ThermalScatterAceDataObject& ace_obj_t)
{
  vector<FastAceDataObject>().swap(ace_obj_fast);
  vector<ThermalScatterAceDataObject>().swap(ace_obj_tsl);

  ace_obj_fast.resize(1);
  ace_obj_fast[0] = ace_obj_f;
  ace_obj_tsl.resize(1);
  ace_obj_tsl[0] = ace_obj_t;
}

void MultiGroupDataGeneratorByFrendyInput::set_ace_obj_tsl
                                (vector<FastAceDataObject>&           ace_obj_f,
                                 vector<ThermalScatterAceDataObject>& ace_obj_t)
{
  vector<FastAceDataObject>().swap(ace_obj_fast);
  vector<ThermalScatterAceDataObject>().swap(ace_obj_tsl);

  ace_obj_fast = ace_obj_f;
  ace_obj_tsl  = ace_obj_t;
}

void MultiGroupDataGeneratorByFrendyInput::set_nucl_data_obj
                                             (vector<NuclearDataObject> nucl_obj)
{
  nucl_data_obj = nucl_obj;
}
