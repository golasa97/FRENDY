#include "FrendyUtils/FrendyInputReader.hpp"

using namespace frendy;

FrendyInputReader::FrendyInputReader(void)
{
  clear();

  func_name_mode.clear();
  clr_obj.clear_vec_array1_str(func_name_list);

  //For ACE file generation with incident particle data
  func_name_list.push_back("ace_file_generation_fast_mode");
  func_name_list.push_back("ace_file_generation_normal_mode");
  func_name_list.push_back("ace_fast_mode");
  func_name_list.push_back("ace_normal_mode");
  func_name_list.push_back("ace_fast");
  func_name_list.push_back("ace_normal");

  func_name_mode.push_back(inp_common_obj.ace_fast_mode);  //ace_file_generation_fast_mode
  func_name_mode.push_back(inp_common_obj.ace_fast_mode);  //ace_file_generation_normal_mode
  func_name_mode.push_back(inp_common_obj.ace_fast_mode);  //ace_fast_mode
  func_name_mode.push_back(inp_common_obj.ace_fast_mode);  //ace_normal_mode
  func_name_mode.push_back(inp_common_obj.ace_fast_mode);  //ace_fast
  func_name_mode.push_back(inp_common_obj.ace_fast_mode);  //ace_normal


  //For ACE file generation with thermal scattering law data
  func_name_list.push_back("ace_file_generation_thermal_scattering_mode");
  func_name_list.push_back("ace_file_generation_thermal_scatter_mode");
  func_name_list.push_back("ace_file_generation_tsl_mode");
  func_name_list.push_back("ace_thermal_scattering_mode");
  func_name_list.push_back("ace_thermal_scatter_mode");
  func_name_list.push_back("ace_therm_mode");
  func_name_list.push_back("ace_tsl_mode");
  func_name_list.push_back("ace_therm");
  func_name_list.push_back("ace_tsl");

  func_name_mode.push_back(inp_common_obj.ace_therm_mode); //ace_file_generation_thermal_scattering_mode
  func_name_mode.push_back(inp_common_obj.ace_therm_mode); //ace_file_generation_thermal_scatter_mode
  func_name_mode.push_back(inp_common_obj.ace_therm_mode); //ace_thermal_scattering_mode
  func_name_mode.push_back(inp_common_obj.ace_therm_mode); //ace_thermal_scatter_mode
  func_name_mode.push_back(inp_common_obj.ace_therm_mode); //ace_file_generation_tsl_mode
  func_name_mode.push_back(inp_common_obj.ace_therm_mode); //ace_therm_mode
  func_name_mode.push_back(inp_common_obj.ace_therm_mode); //ace_tsl_mode
  func_name_mode.push_back(inp_common_obj.ace_therm_mode); //ace_therm
  func_name_mode.push_back(inp_common_obj.ace_therm_mode); //ace_tsl


  //For ACE file generation with dosimetry data
  func_name_list.push_back("ace_file_generation_dosimetry_mode");
  func_name_list.push_back("ace_dosi_mode");
  func_name_list.push_back("ace_dosi");

  func_name_mode.push_back(inp_common_obj.ace_dosi_mode);  //ace_file_generation_dosimetry_mode
  func_name_mode.push_back(inp_common_obj.ace_dosi_mode);  //ace_dosi_mode
  func_name_mode.push_back(inp_common_obj.ace_dosi_mode);  //ace_dosi


  //For ACE file generation with dosimetry data
  func_name_list.push_back("mg_generation_neutron_mode");
  func_name_list.push_back("mg_neutron_mode");
  func_name_list.push_back("mg_neutron");
  func_name_list.push_back("mg_n_mode");
  func_name_list.push_back("mg_n");
  func_name_list.push_back("mg_mode");
  func_name_list.push_back("mg");

  func_name_mode.push_back(inp_common_obj.mg_neutron_mode);  //mg_generation_neutron_mode
  func_name_mode.push_back(inp_common_obj.mg_neutron_mode);  //mg_neutron_mode
  func_name_mode.push_back(inp_common_obj.mg_neutron_mode);  //mg_neutron
  func_name_mode.push_back(inp_common_obj.mg_neutron_mode);  //mg_n_mode
  func_name_mode.push_back(inp_common_obj.mg_neutron_mode);  //mg_n
  func_name_mode.push_back(inp_common_obj.mg_neutron_mode);  //mg_mode
  func_name_mode.push_back(inp_common_obj.mg_neutron_mode);  //mg


  //For ACE file generation with dosimetry data
  func_name_list.push_back("mg_generation_therm_mode");
  func_name_list.push_back("mg_therm_mode");
  func_name_list.push_back("mg_therm");
  func_name_list.push_back("mg_generation_tsl_mode");
  func_name_list.push_back("mg_tsl_mode");
  func_name_list.push_back("mg_tsl");
  func_name_list.push_back("mg_file_generation_thermal_scattering_mode");
  func_name_list.push_back("mg_file_generation_thermal_scatter_mode");
  func_name_list.push_back("mg_file_generation_tsl_mode");
  func_name_list.push_back("mg_thermal_scattering_mode");
  func_name_list.push_back("mg_thermal_scatter_mode");

  func_name_mode.push_back(inp_common_obj.mg_tsl_mode);  //mg_generation_therm_mode
  func_name_mode.push_back(inp_common_obj.mg_tsl_mode);  //mg_therm_mode
  func_name_mode.push_back(inp_common_obj.mg_tsl_mode);  //mg_therm
  func_name_mode.push_back(inp_common_obj.mg_tsl_mode);  //mg_generation_tsl_mode
  func_name_mode.push_back(inp_common_obj.mg_tsl_mode);  //mg_tsl_mode
  func_name_mode.push_back(inp_common_obj.mg_tsl_mode);  //mg_tsl
  func_name_mode.push_back(inp_common_obj.mg_tsl_mode);  //"mg_file_generation_thermal_scattering_mode
  func_name_mode.push_back(inp_common_obj.mg_tsl_mode);  //"mg_file_generation_thermal_scatter_mode
  func_name_mode.push_back(inp_common_obj.mg_tsl_mode);  //"mg_file_generation_tsl_mode
  func_name_mode.push_back(inp_common_obj.mg_tsl_mode);  //"mg_thermal_scattering_mode
  func_name_mode.push_back(inp_common_obj.mg_tsl_mode);  //"mg_thermal_scatter_mode



  //Make NJOY input mode
  int i_max = static_cast<int>(func_name_list.size());
  for(int i=0; i<i_max; i++)
  {
    string str_name0 =                 func_name_list[i] + "_make_inp";
    string str_name1 =                 func_name_list[i] + "_make_inp_mode";
    string str_name2 = "make_inp_"   + func_name_list[i];
    string str_name3 = "make_inp_"   + func_name_list[i] + "_mode";
    string str_name4 =                 func_name_list[i] + "_make_input";
    string str_name5 =                 func_name_list[i] + "_make_input_mode";
    string str_name6 = "make_input_" + func_name_list[i];
    string str_name7 = "make_input_" + func_name_list[i] + "_mode";
    func_name_list_make_inp.push_back(str_name0);
    func_name_list_make_inp.push_back(str_name1);
    func_name_list_make_inp.push_back(str_name2);
    func_name_list_make_inp.push_back(str_name3);
    func_name_list_make_inp.push_back(str_name4);
    func_name_list_make_inp.push_back(str_name5);
    func_name_list_make_inp.push_back(str_name6);
    func_name_list_make_inp.push_back(str_name7);

    func_name_mode_make_inp.push_back(func_name_mode[i] + inp_common_obj.make_inp_mode); //0
    func_name_mode_make_inp.push_back(func_name_mode[i] + inp_common_obj.make_inp_mode); //1
    func_name_mode_make_inp.push_back(func_name_mode[i] + inp_common_obj.make_inp_mode); //2
    func_name_mode_make_inp.push_back(func_name_mode[i] + inp_common_obj.make_inp_mode); //3
    func_name_mode_make_inp.push_back(func_name_mode[i] + inp_common_obj.make_inp_mode); //4
    func_name_mode_make_inp.push_back(func_name_mode[i] + inp_common_obj.make_inp_mode); //5
    func_name_mode_make_inp.push_back(func_name_mode[i] + inp_common_obj.make_inp_mode); //6
    func_name_mode_make_inp.push_back(func_name_mode[i] + inp_common_obj.make_inp_mode); //7
  }

  //ENDF-6 file format data modification mode
  func_name_list.push_back("endf_file_modification_mode");
  func_name_list.push_back("endf_file_modify_mode");
  func_name_list.push_back("endf_file_mod_mode");
  func_name_list.push_back("endf_mod_mode");
  func_name_list.push_back("endf_mod");
  func_name_list.push_back("modification_endf_file_mode");
  func_name_list.push_back("modify_endf_file_mode");
  func_name_list.push_back("mod_endf_file_mode");
  func_name_list.push_back("mod_endf_mode");
  func_name_list.push_back("mod_endf");

  func_name_mode.push_back(inp_common_obj.endf_modify_mode);  //endf_file_modification_mode
  func_name_mode.push_back(inp_common_obj.endf_modify_mode);  //endf_file_modify_mode
  func_name_mode.push_back(inp_common_obj.endf_modify_mode);  //endf_file_mod_mode
  func_name_mode.push_back(inp_common_obj.endf_modify_mode);  //endf_mod_mode
  func_name_mode.push_back(inp_common_obj.endf_modify_mode);  //endf_mod
  func_name_mode.push_back(inp_common_obj.endf_modify_mode);  //modification_endf_file_mode
  func_name_mode.push_back(inp_common_obj.endf_modify_mode);  //modify_endf_file_mode
  func_name_mode.push_back(inp_common_obj.endf_modify_mode);  //mod_endf_file_mode
  func_name_mode.push_back(inp_common_obj.endf_modify_mode);  //mod_endf_mode
  func_name_mode.push_back(inp_common_obj.endf_modify_mode);  //mod_endf

  //Check ENDF format
  func_name_list.push_back("check_endf_format_mode");
  func_name_list.push_back("check_endf_mode");
  func_name_list.push_back("check_endf_format");
  func_name_list.push_back("check_endf");

  func_name_mode.push_back(inp_common_obj.check_endf_mode);  //check_endf_format_mode
  func_name_mode.push_back(inp_common_obj.check_endf_mode);  //check_endf_mode
  func_name_mode.push_back(inp_common_obj.check_endf_mode);  //check_endf_format
  func_name_mode.push_back(inp_common_obj.check_endf_mode);  //check_endf

  //Comp ENDF mode
  func_name_list.push_back("comp_ace_file_mode");
  func_name_list.push_back("comp_endf_file_mode");
  func_name_list.push_back("comp_pendf_file_mode");
  func_name_list.push_back("comp_gendf_file_mode");
  func_name_list.push_back("comp_ace_mode");
  func_name_list.push_back("comp_endf_mode");
  func_name_list.push_back("comp_pendf_mode");
  func_name_list.push_back("comp_gendf_mode");
  func_name_list.push_back("comp_file_mode");
  func_name_list.push_back("comp_mode");
  func_name_list.push_back("plot_ace_file_mode");
  func_name_list.push_back("plot_endf_file_mode");
  func_name_list.push_back("plot_pendf_file_mode");
  func_name_list.push_back("plot_gendf_file_mode");
  func_name_list.push_back("plot_ace_mode");
  func_name_list.push_back("plot_endf_mode");
  func_name_list.push_back("plot_gendf_mode");
  func_name_list.push_back("plot_pendf_mode");
  func_name_list.push_back("plot_file_mode");
  func_name_list.push_back("plot_mode");
  func_name_list.push_back("output_xs_ace_file_mode");
  func_name_list.push_back("output_xs_endf_file_mode");
  func_name_list.push_back("output_xs_pendf_file_mode");
  func_name_list.push_back("output_xs_gendf_file_mode");
  func_name_list.push_back("output_xs_ace_mode");
  func_name_list.push_back("output_xs_endf_mode");
  func_name_list.push_back("output_xs_pendf_mode");
  func_name_list.push_back("output_xs_gendf_mode");
  func_name_list.push_back("output_xs_file_mode");
  func_name_list.push_back("output_xs_mode");

  func_name_mode.push_back(inp_common_obj.plot_mode);  //comp_ace_file_mode
  func_name_mode.push_back(inp_common_obj.plot_mode);  //comp_pendf_file_mode
  func_name_mode.push_back(inp_common_obj.plot_mode);  //comp_endf_file_mode
  func_name_mode.push_back(inp_common_obj.plot_mode);  //comp_gendf_file_mode
  func_name_mode.push_back(inp_common_obj.plot_mode);  //comp_ace_mode
  func_name_mode.push_back(inp_common_obj.plot_mode);  //comp_pendf_mode
  func_name_mode.push_back(inp_common_obj.plot_mode);  //comp_endf_mode
  func_name_mode.push_back(inp_common_obj.plot_mode);  //comp_gendf_mode
  func_name_mode.push_back(inp_common_obj.plot_mode);  //comp_file_mode
  func_name_mode.push_back(inp_common_obj.plot_mode);  //comp_mode
  func_name_mode.push_back(inp_common_obj.plot_mode);  //plot_ace_file_mode
  func_name_mode.push_back(inp_common_obj.plot_mode);  //plot_endf_file_mode
  func_name_mode.push_back(inp_common_obj.plot_mode);  //plot_pendf_file_mode
  func_name_mode.push_back(inp_common_obj.plot_mode);  //plot_gendf_file_mode
  func_name_mode.push_back(inp_common_obj.plot_mode);  //plot_ace_mode
  func_name_mode.push_back(inp_common_obj.plot_mode);  //plot_endf_mode
  func_name_mode.push_back(inp_common_obj.plot_mode);  //plot_pendf_mode
  func_name_mode.push_back(inp_common_obj.plot_mode);  //plot_gendf_mode
  func_name_mode.push_back(inp_common_obj.plot_mode);  //plot_file_mode
  func_name_mode.push_back(inp_common_obj.plot_mode);  //plot_mode
  func_name_mode.push_back(inp_common_obj.plot_mode);  //output_xs_ace_file_mode
  func_name_mode.push_back(inp_common_obj.plot_mode);  //output_xs_pendf_file_mode
  func_name_mode.push_back(inp_common_obj.plot_mode);  //output_xs_endf_file_mode
  func_name_mode.push_back(inp_common_obj.plot_mode);  //output_xs_gendf_file_mode
  func_name_mode.push_back(inp_common_obj.plot_mode);  //output_xs_ace_mode
  func_name_mode.push_back(inp_common_obj.plot_mode);  //output_xs_pendf_mode
  func_name_mode.push_back(inp_common_obj.plot_mode);  //output_xs_endf_mode
  func_name_mode.push_back(inp_common_obj.plot_mode);  //output_xs_gendf_mode
  func_name_mode.push_back(inp_common_obj.plot_mode);  //output_xs_file_mode
  func_name_mode.push_back(inp_common_obj.plot_mode);  //output_xs_mode
}

FrendyInputReader::~FrendyInputReader(void)
{
  clear();

  func_name_mode.clear();
  func_name_mode_make_inp.clear();
  clr_obj.clear_vec_array1_str(func_name_list);
  clr_obj.clear_vec_array1_str(func_name_list_make_inp);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void FrendyInputReader::clear()
{
  read_flg  = 0;
  calc_mode = inp_common_obj.get_calc_mode_def();

  inp_recon_obj.clear();
  inp_dop_obj.clear();
  inp_gas_xs_obj.clear();
  inp_prob_table_obj.clear();
  inp_thermal_scatter_obj.clear();
  inp_ace_obj.clear();
  inp_mg_obj.clear();

  inp_make_njoy_obj.clear();

  inp_check_recon.clear();
  inp_check_dop.clear();
  inp_check_gas.clear();
  inp_check_prob_table.clear();
  inp_check_therm.clear();
  inp_check_ace.clear();
  inp_check_mg.clear();
  inp_check_make_njoy.clear();

  input_name.clear();

  nucl_file_name = inp_common_obj.get_nucl_file_name_def();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void FrendyInputReader::read_input_file()
{
  if( read_flg != 0 )
  {
    return;
  }
  read_flg = 1;

  //Check calculation mode
  calc_mode = check_file_format(input_name);
  if( calc_mode == inp_common_obj.njoy_mode )
  {
    //Skip to read input file when input data format is NJOY input format.
    return;
  }

  //Remove comment data
  FileCommentRemover file_mod_obj;
  vector<vector<string> > input_data = file_mod_obj.remove_comment_and_devide_text_data(input_name);
  file_mod_obj.clear();

  read_input_data(input_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void FrendyInputReader::read_input_data(vector<vector<string> >& input_data)
{
  if( read_flg == 0 )
  {
    read_flg = 1;
  }

  if( calc_mode == inp_common_obj.get_calc_mode_def() )
  {
    string input_case = "";
    if( static_cast<int>(input_data.size()) > 0 )
    {
      if( static_cast<int>(input_data[0].size()) > 0 )
      {
        input_case = input_data[0][0];
      }
    }

    calc_mode = check_input_case(input_case);
  }

  inp_check_make_njoy = inp_make_njoy_obj.read_input_data(input_data);

  read_common_input(input_data);

  int add_val = inp_common_obj.make_inp_mode;
  if( calc_mode == inp_common_obj.ace_fast_mode  || calc_mode == inp_common_obj.ace_fast_mode  + add_val ||
      calc_mode == inp_common_obj.ace_therm_mode || calc_mode == inp_common_obj.ace_therm_mode + add_val ||
      calc_mode == inp_common_obj.ace_dosi_mode  || calc_mode == inp_common_obj.ace_dosi_mode  + add_val ||
      calc_mode == inp_common_obj.check_endf_mode )
  {
    read_input_for_ace_mode(input_data);
  }
  else if( calc_mode == inp_common_obj.mg_neutron_mode || calc_mode == inp_common_obj.mg_neutron_mode + add_val ||
           calc_mode == inp_common_obj.mg_tsl_mode     || calc_mode == inp_common_obj.mg_tsl_mode     + add_val )
  {
    read_input_for_mg_mode(input_data);
  }
  else if( calc_mode == inp_common_obj.endf_modify_mode )
  {
    //skip reading input file
    //The reading input file process is called called in the modify_endf_file function in the NuclearDataProcessorByFrendyInput class.
  }
  else if( calc_mode == inp_common_obj.plot_mode )
  {
    //skip reading input file
    //The reading input file process is called called in the plot_file function in the NuclearDataProcessorByFrendyInput class.
  }
  else
  {
    string class_name = "FrendyInputReader";
    string func_name  = "read_input_data(vector<vector<string> >& input_data)";

    ostringstream oss;
    oss << calc_mode;
    string str_data = "calc_mode : " + oss.str();

    vector<string> err_com;
    err_com.push_back(str_data);

    err_com.push_back("This calc_mode cannot treat in this program.");
    err_com.push_back("Please modify this source file or calc_mode.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  clr_obj.clear_vec_array2_str(input_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int FrendyInputReader::check_file_format(string file_name)
{
  //Remove comment data
  FileCommentRemover file_mod_obj;
  vector<string> input_vec = file_mod_obj.remove_comment(file_name);
  file_mod_obj.clear();

  StringUtils str_obj;
  str_obj.set_text_data(input_vec);
  clr_obj.clear_vec_array1_str(input_vec);
  
  vector<vector<string> > input_data = str_obj.get_div_string_vec_all();
  str_obj.clear();

  string input_case = "";
  if( static_cast<int>(input_data.size()) > 0 )
  {
    input_case = input_data[0][0];
  }
  clr_obj.clear_vec_array2_str(input_data);

  //return calculation mode
  return check_input_case(input_case);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int FrendyInputReader::check_input_case(string input_case)
{
  int input_case_flg = inp_common_obj.non_related;

  if( njoy_reader_obj.check_input_case(input_case) >= 0 )
  {
    input_case_flg = inp_common_obj.njoy_mode;
  }
  else
  {
    string input_case_up = input_case;
    transform(input_case_up.begin(), input_case_up.end(), input_case_up.begin(), ::toupper);

    int i_max = static_cast<int>(func_name_list.size());
    for(int i=0; i<i_max; i++)
    {
      string func_name_up = func_name_list[i];
      transform(func_name_up.begin(), func_name_up.end(), func_name_up.begin(), ::toupper);

      if( strcmp(input_case_up.c_str(), func_name_up.c_str()) == 0 )
      {
        input_case_flg = func_name_mode[i];
        break;
      }
    }

    //Check make_input_mode
    int j_max = static_cast<int>(func_name_list_make_inp.size());
    if( input_case_flg == inp_common_obj.non_related )
    {
      for(int j=0; j<j_max; j++)
      {
        string func_name_up = func_name_list_make_inp[j];
        transform(func_name_up.begin(), func_name_up.end(), func_name_up.begin(), ::toupper);

        if( strcmp(input_case_up.c_str(), func_name_up.c_str()) == 0 )
        {
          input_case_flg = func_name_mode_make_inp[j];
          break;
        }
      }
    }

    if( input_case_flg == inp_common_obj.non_related )
    {
      string class_name = "FrendyInputReader";
      string func_name  = "check_input_case(string input_case)";

      vector<string> err_com;
      err_com.push_back("This input file may not be input file for this program.");
      err_com.push_back("Please check the input file.");
      err_com.push_back("The available input mode is as follows:");

      for(int i=0; i<i_max; i++)
      {
        string str_data = "  " + func_name_list[i];
        err_com.push_back(str_data);
      }
      //err_com.push_back("");
      for(int j=0; j<j_max; j++)
      {
        //string str_data = "  " + func_name_list_make_inp[j];
        //err_com.push_back(str_data);
      }
      err_obj.output_caution(class_name, func_name, err_com);
    }
  }

  //return calculation mode
  return input_case_flg;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void FrendyInputReader::read_common_input(vector<vector<string> >& input_data)
{
  //Remove input common input parameter from input_data
  vector<vector<string> > input_data_mod;
  clr_obj.clear_vec_array2_str(input_data_mod);

  int i_max = static_cast<int>(input_data.size());
  int i_sta = 0;
  if( i_max%2 == 1 ) //include calculation mode at input_data[0][0]
  {
    i_sta = 1;
    input_data_mod.push_back(input_data[0]);
  }

  for(int i=i_sta; i<i_max; i+=2)
  {
    if( static_cast<int>(input_data[i].size()) != 1 )
    {
      input_data_mod.push_back(input_data[i]);
      input_data_mod.push_back(input_data[i+1]);
      continue;
    }

    if( static_cast<int>(input_data[i+1].size()) == 0 )
    {
      input_data_mod.push_back(input_data[i]);
      input_data_mod.push_back(input_data[i+1]);
      continue;
    }

    //Modify capital letter to lower-case letter
    string input_type_mod = input_data[i][0];
    transform(input_type_mod.begin(), input_type_mod.end(), input_type_mod.begin(), ::tolower);
    replace(input_type_mod.begin(), input_type_mod.end(), '-', '_');
    if( input_type_mod == "nan_err_mes_opt" || input_type_mod == "err_mes_nan_opt" ||
        input_type_mod == "err_nan_opt"     || input_type_mod == "nan_opt" )
    {
      cout << "  Error message mode when data is NaN : " << input_data[i+1][0] << endl;

      string mode_name = input_data[i+1][0];
      transform(mode_name.begin(), mode_name.end(), mode_name.begin(), ::tolower);
      replace(mode_name.begin(), mode_name.end(), '-', '_');
      if( mode_name == "def" || mode_name == "default" )
      {
        err_obj.set_err_mes_nan_opt(err_obj.warning_default);
      }
      else if( mode_name == "runtime" || mode_name == "runtime_error" || mode_name == "error" )
      {
        err_obj.set_err_mes_nan_opt(err_obj.warning_runtime_error);
      }
      else if( mode_name == "caution" || mode_name == "warning" )
      {
        err_obj.set_err_mes_nan_opt(err_obj.warning_caution);
      }
      else
      {
        StringConverter str_obj;
        str_obj.string_check(mode_name);
        int mode_val = numeric_string_cast<int>(mode_name);
        err_obj.set_err_mes_nan_opt(mode_val);
      }

      if( err_obj.get_err_mes_nan_opt() == err_obj.warning_runtime_error )
      {
        cout << "    (Calculation is aborted when NaN value is found.)" << endl;
      }
      else //if( err_obj.get_err_mes_nan_opt() == err_obj.warning_caution )
      {
        cout << "    (Warning message is output and caulculation is not stopped  when NaN value is found.)" << endl;
      }
      cout << endl;
    }
    else
    {
      input_data_mod.push_back(input_data[i]);
      input_data_mod.push_back(input_data[i+1]);
    }
  }

  input_data = input_data_mod;
  clr_obj.clear_vec_array2_str(input_data_mod);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void FrendyInputReader::read_input_for_ace_mode(vector<vector<string> >& input_data)
{
  //Check input data number
  check_input_data_number(input_data);

  //Read input data in each calculation
  inp_check_recon      = inp_recon_obj.read_input_data(input_data);
  inp_check_dop        = inp_dop_obj.read_input_data(input_data);
  inp_check_gas        = inp_gas_xs_obj.read_input_data(input_data);
  inp_check_prob_table = inp_prob_table_obj.read_input_data(input_data);
  inp_check_therm      = inp_thermal_scatter_obj.read_input_data(input_data);
  inp_check_ace        = inp_ace_obj.read_input_data(input_data);

  set_common_data();

  check_not_used_input_data(input_data);

  //Check input data is appropriate or not
  int inp_mode_ace = inp_ace_obj.inp_mode_fast;
  if( calc_mode == inp_common_obj.ace_therm_mode ||
      calc_mode == inp_common_obj.ace_therm_mode + inp_common_obj.make_inp_mode )
  {
    inp_mode_ace = inp_ace_obj.inp_mode_therm;
  }
  else if( calc_mode == inp_common_obj.ace_dosi_mode ||
           calc_mode == inp_common_obj.ace_dosi_mode + inp_common_obj.make_inp_mode )
  {
    inp_mode_ace = inp_ace_obj.inp_mode_dosi;
  }
  inp_ace_obj.set_generation_mode(inp_mode_ace);

  int i_max   = static_cast<int>(inp_check_recon.size());
  int err_flg = 0;
  vector<string> err_com;
  for(int i=0; i<i_max; i++)
  {
    if( inp_check_ace[i] != 0 && inp_check_ace[i] != inp_ace_obj.inp_mode_common &&
        inp_check_ace[i] != inp_mode_ace )
    {
      err_flg++;

      set_err_com_for_input_data_check(i, input_data, err_com);

      string str_data01 = "This input type is not used for ";
      if( inp_check_ace[i] == inp_ace_obj.inp_mode_fast )
      {
        str_data01 = str_data01 + func_name_list[inp_common_obj.ace_fast_mode] + ".";
      }
      else if( inp_check_ace[i] == inp_ace_obj.inp_mode_therm )
      {
        str_data01 = str_data01 + func_name_list[inp_common_obj.ace_therm_mode] + ".";
      }
      else if( inp_check_ace[i] == inp_ace_obj.inp_mode_dosi )
      {
        str_data01 = str_data01 + func_name_list[inp_common_obj.ace_dosi_mode] + ".";
      }
      err_com.push_back(str_data01);
      err_com.push_back("");
    }
  }

  if( err_flg > 0 )
  {
    string class_name = "FrendyInputReader";
    string func_name  = "read_input_for_ace_mode(vector<vector<string> >& input_data)";

    err_com.push_back("Please check the calculation mode or input type.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}


////////////////////////////////////////////////////////////////////////////////////////////////////

void FrendyInputReader::read_input_for_mg_mode(vector<vector<string> >& input_data)
{
  //Check input data number
  check_input_data_number(input_data);

  //Read input data in each calculation
  inp_check_recon      = inp_recon_obj.read_input_data(input_data);
  inp_check_dop        = inp_dop_obj.read_input_data(input_data);
  inp_check_gas        = inp_gas_xs_obj.read_input_data(input_data);
  inp_check_prob_table = inp_prob_table_obj.read_input_data(input_data);
  //if( calc_mode == inp_common_obj.mg_tsl_mode ||
  //    calc_mode == inp_common_obj.mg_tsl_mode + inp_common_obj.make_inp_mode )
  //{
    inp_check_therm      = inp_thermal_scatter_obj.read_input_data(input_data);
  //}
  inp_check_ace        = inp_ace_obj.read_input_data(input_data);
  inp_check_mg         = inp_mg_obj.read_input_data(input_name, input_data);

  set_common_data();

  check_not_used_input_data(input_data);

  //Check input data is appropriate or not
  int inp_mode_ace = inp_ace_obj.inp_mode_fast;
  if( calc_mode == inp_common_obj.mg_tsl_mode ||
      calc_mode == inp_common_obj.mg_tsl_mode + inp_common_obj.make_inp_mode )
  {
    inp_mode_ace = inp_ace_obj.inp_mode_therm;
  }
  else if( calc_mode == inp_common_obj.ace_dosi_mode ||
           calc_mode == inp_common_obj.ace_dosi_mode + inp_common_obj.make_inp_mode )
  {
    inp_mode_ace = inp_ace_obj.inp_mode_dosi;
  }
  inp_ace_obj.set_generation_mode(inp_mode_ace);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void FrendyInputReader::check_not_used_input_data(vector<vector<string> >& input_data)
{
  int i_max = 0;
  if( static_cast<int>(inp_check_recon.size()) > 0 )
  {
    i_max = static_cast<int>(inp_check_recon.size());
  }
  else if( static_cast<int>(inp_check_dop.size()) > 0 )
  {
    i_max = static_cast<int>(inp_check_dop.size());
  }
  else if( static_cast<int>(inp_check_gas.size()) > 0 )
  {
    i_max = static_cast<int>(inp_check_gas.size());
  }
  else if( static_cast<int>(inp_check_prob_table.size()) > 0 )
  {
    i_max = static_cast<int>(inp_check_prob_table.size());
  }
  else if( static_cast<int>(inp_check_therm.size()) > 0 )
  {
    i_max = static_cast<int>(inp_check_therm.size());
  }
  else if( static_cast<int>(inp_check_ace.size()) > 0 )
  {
    i_max = static_cast<int>(inp_check_ace.size());
  }
  else if( static_cast<int>(inp_check_mg.size()) > 0 )
  {
    i_max = static_cast<int>(inp_check_mg.size());
  }

  set_inp_check_data(i_max, inp_check_recon);
  set_inp_check_data(i_max, inp_check_dop);
  set_inp_check_data(i_max, inp_check_gas);
  set_inp_check_data(i_max, inp_check_prob_table);
  set_inp_check_data(i_max, inp_check_therm);
  set_inp_check_data(i_max, inp_check_ace);
  set_inp_check_data(i_max, inp_check_mg);
  set_inp_check_data(i_max, inp_check_make_njoy);

  int err_flg = 0;
  vector<string> err_com;
  for(int i=0; i<i_max; i++)
  {
    if( inp_check_recon[i]      == 0 && inp_check_dop[i]   == 0 && inp_check_gas[i] == 0 &&
        inp_check_prob_table[i] == 0 && inp_check_therm[i] == 0 && inp_check_ace[i] == 0 &&
        inp_check_mg[i]         == 0 && inp_check_make_njoy[i] == 0)
    {
      err_flg++;

      set_err_com_for_input_data_check(i, input_data, err_com);

      int ele_no = calc_mode;
      if( ele_no >= inp_common_obj.make_inp_mode )
      {
        ele_no -= inp_common_obj.make_inp_mode;
      }
      string str_data04 = "This input type is not used for " + func_name_list[ele_no] + ".";
      err_com.push_back(str_data04);
      err_com.push_back("");
    }
  }

  if( err_flg > 0 )
  {
    string class_name = "FrendyInputReader";
    string func_name  = "check_not_used_input_data(vector<vector<string> >& input_data)";

    err_com.push_back("Please check the calculation mode or input type.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void FrendyInputReader::set_err_com_for_input_data_check
                          (int i, vector<vector<string> >& input_vec, vector<string>& err_com)
{
  string str_data01 = "Input type : " + input_vec[2*i+1][0];
  err_com.push_back(str_data01);

  if( static_cast<int>(input_vec.size()) > 2*i+2 )
  {
    int j_max = static_cast<int>(input_vec[2*i+2].size());
    ostringstream oss01;
    oss01 << j_max;
    string str_data02 = "Input data (Number of data : " + oss01.str() + ")";
    err_com.push_back(str_data02);
    for(int j=0; j<j_max; j++)
    {
      ostringstream oss02;
      oss02 << j+1;
      string str_data03  = "  " + oss02.str() + " / " + oss01.str() + " : " + input_vec[2*i+2][j];
      err_com.push_back(str_data03);
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void FrendyInputReader::set_inp_check_data(int i_max, vector<int>& inp_check_data)
{
  if( static_cast<int>(inp_check_data.size()) != i_max )
  {
    inp_check_data.resize(i_max);
    for(int i=0; i<i_max; i++)
    {
     inp_check_data[i] = 0;
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void FrendyInputReader::check_input_data_number(vector<vector<string> >& input_data)
{
  int i_max = static_cast<int>(input_data.size());
  if( i_max%2 != 1 )
  {
    string class_name = "FrendyInputReader";
    string func_name  = "check_input_data_number(vector<vector<string> >& input_data)";

    vector<string> err_com;
    ostringstream oss01;
    oss01 << i_max;
    string str_data01 = "Number of input data : " + oss01.str();
    string str_data02 = "Calculation mode     : " + input_data[0][0];
    string str_data03 = "Input type";
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    for(int i=1; i<i_max; i+=2)
    {
      ostringstream oss02;
      oss02 << i+1;
      string str_data04 = "  " + oss02.str() + " / " + oss01.str() + input_data[i][0];
      err_com.push_back(str_data04);
    }
    err_com.push_back("The number of input data must be odd numbers.");
    err_com.push_back("Please check the input file (calculation mode, input type and so on.");
    err_com.push_back(str_data03);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void FrendyInputReader::set_common_data()
{
  nucl_file_name   = inp_common_obj.get_nucl_file_name_def();

  //For nucl_file_name
  if( static_cast<int>(inp_recon_obj.get_nucl_file_name().size()) > 0 )
  {
    nucl_file_name = inp_recon_obj.get_nucl_file_name();
  }
  else if( static_cast<int>(inp_dop_obj.get_nucl_file_name().size()) > 0 )
  {
    nucl_file_name = inp_dop_obj.get_nucl_file_name();
  }
  else if( static_cast<int>(inp_gas_xs_obj.get_nucl_file_name().size()) > 0 )
  {
    nucl_file_name = inp_gas_xs_obj.get_nucl_file_name();
  }
  else if( static_cast<int>(inp_prob_table_obj.get_nucl_file_name().size()) > 0 )
  {
    nucl_file_name = inp_prob_table_obj.get_nucl_file_name();
  }
  else if( static_cast<int>(inp_thermal_scatter_obj.get_nucl_file_name().size()) > 0 )
  {
    nucl_file_name = inp_thermal_scatter_obj.get_nucl_file_name();
  }
  else if( static_cast<int>(inp_ace_obj.get_nucl_file_name().size()) > 0 )
  {
    nucl_file_name = inp_ace_obj.get_nucl_file_name();
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void FrendyInputReader::set_input_file_name(string input)
{
  read_flg   = 0;
  input_name = input;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void FrendyInputReader::set_inp_recon_obj(ReconResonanceInputReader inp_obj)
{
  inp_recon_obj = inp_obj;
}

void FrendyInputReader::set_inp_dop_obj(DopplerBroadeningInputReader inp_obj)
{
  inp_dop_obj = inp_obj;
}

void FrendyInputReader::set_inp_gas_xs_obj(GasProductionInputReader inp_obj)
{
  inp_gas_xs_obj = inp_obj;
}

void FrendyInputReader::set_inp_prob_table_obj(ProbTableInputReader inp_obj)
{
  inp_prob_table_obj = inp_obj;
}

void FrendyInputReader::set_inp_thermal_scatter_obj(ThermalScatterInputReader inp_obj)
{
  inp_thermal_scatter_obj = inp_obj;
}

void FrendyInputReader::set_inp_ace_obj(AceDataGeneratorInputReader inp_obj)
{
  inp_ace_obj = inp_obj;
}

void FrendyInputReader::set_inp_mg_obj(MultiGroupDataGeneratorInputReader inp_obj)
{
  inp_mg_obj = inp_obj;
}

void FrendyInputReader::set_inp_make_njoy_obj(MakeNJOYInputReader inp_obj)
{
  inp_make_njoy_obj = inp_obj;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

string FrendyInputReader::get_input_file_name()
{
  read_input_file();

  return input_name;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int FrendyInputReader::get_calc_mode()
{
  read_input_file();

  return calc_mode;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> FrendyInputReader::get_func_name_list()
{
  return func_name_list;
}

vector<int> FrendyInputReader::get_func_name_mode()
{
  return func_name_mode;
}

vector<string> FrendyInputReader::get_func_name_list_make_inp()
{
  return func_name_list_make_inp;
}

vector<int> FrendyInputReader::get_func_name_mode_make_inp()
{
  return func_name_mode_make_inp;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

ReconResonanceInputReader    FrendyInputReader::get_inp_recon_obj()
{
  read_input_file();

  return inp_recon_obj;
}

DopplerBroadeningInputReader FrendyInputReader::get_inp_dop_obj()
{
  read_input_file();

  return inp_dop_obj;
}

GasProductionInputReader     FrendyInputReader::get_inp_gas_xs_obj()
{
  read_input_file();

  return inp_gas_xs_obj;
}

ProbTableInputReader         FrendyInputReader::get_inp_prob_table_obj()
{
  read_input_file();

  return inp_prob_table_obj;
}

ThermalScatterInputReader    FrendyInputReader::get_inp_thermal_scatter_obj()
{
  read_input_file();

  return inp_thermal_scatter_obj;
}

AceDataGeneratorInputReader  FrendyInputReader::get_inp_ace_obj()
{
  read_input_file();

  return inp_ace_obj;
}

MultiGroupDataGeneratorInputReader  FrendyInputReader::get_inp_mg_obj()
{
  read_input_file();

  return inp_mg_obj;
}

MakeNJOYInputReader  FrendyInputReader::get_inp_make_njoy_obj()
{
  read_input_file();

  return inp_make_njoy_obj;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> FrendyInputReader::get_nucl_file_name()
{
  read_input_file();

  return nucl_file_name;
}

