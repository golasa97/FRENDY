#include "NuclearDataProcessor/NuclearDataProcessorByFrendyInput.hpp"

using namespace frendy;

//constructor
NuclearDataProcessorByFrendyInput::NuclearDataProcessorByFrendyInput(void)
{
  clear();
}

//destructor
NuclearDataProcessorByFrendyInput::~NuclearDataProcessorByFrendyInput(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataProcessorByFrendyInput::clear()
{
  input_name.clear();

  calc_mode = 0;

  frendy_inp_obj.clear();

  principal_atom_no         = frendy_inp_common_obj.get_principal_atom_no_def();
  atom_type_no              = frendy_inp_common_obj.get_atom_type_no_def();
  tsl_za_data_principal     = 0;
  tsl_za_data_non_principal = 0;

  tsl_mat_data_pos          = -1;

  vector<NuclearDataObject>().swap(nucl_data_obj_ori);
  vector<NuclearDataObject>().swap(nucl_data_obj_cal);
  vector<NuclearDataObject>().swap(nucl_data_obj_tsl);

  //Please modify set_nucl_file_name_tsl function in AceDataGeneratorInputReader class
  //if you modify skip_nucl_name_tsl.
  skip_nucl_name_tsl.resize(3);
  skip_nucl_name_tsl[0] = "no";
  skip_nucl_name_tsl[1] = "none";
  skip_nucl_name_tsl[2] = "skip";
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataProcessorByFrendyInput::process_nucl_data(string input_file_name)
{
  input_name = input_file_name;

  //Output title of FRENDY and original input data
  common_obj.output_frendy_start();
  common_obj.output_frendy_input_file_information(input_name);
  common_obj.output_frendy_input_file_information_without_comment(input_name);

  //Read frendy input file and check calculation mode
  frendy_inp_obj.set_input_file_name(input_name);
  calc_mode = frendy_inp_obj.get_calc_mode(); 

  if( calc_mode == frendy_inp_common_obj.njoy_mode )
  {
    process_nucl_data_njoy();
  }
  else if( calc_mode == frendy_inp_common_obj.endf_modify_mode )
  {
    modify_endf_file();
  }
  else if( calc_mode == frendy_inp_common_obj.check_endf_mode )
  {
    check_endf_file();
  }
  else if( calc_mode == frendy_inp_common_obj.plot_mode )
  {
    plot_file();
  }
  else
  {
    if( calc_mode >= frendy_inp_common_obj.make_inp_mode )
    {
      make_input_from_frendy_to_njoy();
    }
    else
    {
      process_nucl_data_frendy();
    }
  }

  common_obj.output_frendy_end(input_file_name);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataProcessorByFrendyInput::process_nucl_data(vector<vector<string> >& input_data)
{
  //Output title of FRENDY and original input data
  common_obj.output_frendy_start();

  //Read frendy input file and check calculation mode
  frendy_inp_obj.read_input_data(input_data);
  calc_mode = frendy_inp_obj.get_calc_mode(); 

  if( calc_mode == frendy_inp_common_obj.njoy_mode )
  {
    string class_name = "NuclearDataProcessorByFrendyInput";
    string func_name  = "process_nucl_data(vector<vector<string> >& input_data)";

    vector<string> err_com;
    err_com.push_back("This function does not treat NJOY input format.");
    err_com.push_back("Please modify this function.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
  else if( calc_mode == frendy_inp_common_obj.endf_modify_mode )
  {
    modify_endf_file(input_data);
  }
  else if( calc_mode == frendy_inp_common_obj.check_endf_mode )
  {
    check_endf_file(input_data);
  }
  else if( calc_mode == frendy_inp_common_obj.plot_mode )
  {
    plot_file(input_data);
  }
  else
  {
    if( calc_mode >= frendy_inp_common_obj.make_inp_mode )
    {
      string class_name = "NuclearDataProcessorByFrendyInput";
      string func_name  = "process_nucl_data(vector<vector<string> >& input_data)";

      vector<string> err_com;
      err_com.push_back("This function can not generate the NJOY input file from the FRENDY input file");
      err_com.push_back("since the NJOY input file name is generated from the FRENDY input file.");
      err_com.push_back("Please modify this function.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
    else
    {
      process_nucl_data_frendy();
    }
  }

  string str_tmp = "";
  common_obj.output_frendy_end(str_tmp);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataProcessorByFrendyInput::check_endf_file()
{
  Endf6FormatCheckInputReader input_reader_obj;
  input_reader_obj.read_input_data_from_input_file(frendy_inp_obj.get_input_file_name());

  check_endf_file(input_reader_obj);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataProcessorByFrendyInput::check_endf_file(vector<vector<string> >& input_data)
{
  Endf6FormatCheckInputReader input_reader_obj;
  input_reader_obj.read_input_data(input_data);

  check_endf_file(input_reader_obj);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataProcessorByFrendyInput::check_endf_file(Endf6FormatCheckInputReader& input_reader_obj)
{
  vector<string> nucl_file_name = input_reader_obj.get_nucl_file_name();

  err_obj.set_err_mes_format_opt(err_obj.output_format_warning);

  int i_max = static_cast<int>(nucl_file_name.size());
  for(int i=0; i<i_max; i++)
  {
    EndfTapeDivider div_obj;
    div_obj.set_file_name(nucl_file_name[i]);
    vector<Integer> mat_list = div_obj.get_mat_list();
    for(int j=0; j<static_cast<int>(mat_list.size()); j++)
    {
      vector<Real> temp_list = div_obj.get_temp_list(mat_list[j]);
      for(int k=0; k<static_cast<int>(temp_list.size()); k++)
      {
        cout << "=== Check ENDF file information ===" << endl;
        cout << "  ENDF file name    : " << nucl_file_name[i] << endl;
        cout << "  Material number   : " << mat_list[j] << endl;
        cout << "  Temperature       : " << temp_list[k] << endl;
        cout << endl;

        vector<string> text_data = div_obj.get_designated_temp_data(mat_list[j], temp_list[k]);

        Endf6FileStore store_obj;
        NuclearDataObject nucl_data_obj = store_obj.get_nucl_data_obj(text_data);
        text_data.clear();
        nucl_data_obj.clear();

        cout << endl;
        cout << "======================================================================" << endl;
        cout << endl;
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataProcessorByFrendyInput::modify_endf_file()
{
  Endf6ModifierByFrendyInput endf_modify_obj;
  endf_modify_obj.set_frendy_input(frendy_inp_obj.get_input_file_name());
  endf_modify_obj.calc_endf6_modifier();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataProcessorByFrendyInput::modify_endf_file(vector<vector<string> >& input_data)
{
  Endf6ModifierInputReader read_obj;
  read_obj.read_input_data(input_data);

  Endf6ModifierByFrendyInput endf_modify_obj;
  endf_modify_obj.set_frendy_inp_obj(read_obj);
  endf_modify_obj.calc_endf6_modifier();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataProcessorByFrendyInput::plot_file()
{
  PlotDataByFrendyInput plot_data_obj;
  plot_data_obj.set_frendy_input(frendy_inp_obj.get_input_file_name());
  plot_data_obj.plot_data();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataProcessorByFrendyInput::plot_file(vector<vector<string> >& input_data)
{
  NuclearDataPlotterInputReader read_obj;
  read_obj.read_input_data(input_data);

  PlotDataByFrendyInput plot_data_obj;
  plot_data_obj.set_frendy_inp_obj(read_obj);
  plot_data_obj.plot_data();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataProcessorByFrendyInput::process_nucl_data_njoy()
{
  NuclearDataProcessorByNjoyInput njoy_run_obj;
  njoy_run_obj.process_nucl_data_without_title_output(frendy_inp_obj.get_input_file_name());
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataProcessorByFrendyInput::process_nucl_data_frendy()
{
  vector<string> nucl_file_name = frendy_inp_obj.get_nucl_file_name();
  int i_max = static_cast<int>(nucl_file_name.size());
  nucl_data_obj_ori.resize(i_max);
  nucl_data_obj_tsl.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    Endf6FileStore endf_read_obj;
    nucl_data_obj_ori[i] = endf_read_obj.get_nucl_data_obj(nucl_file_name[i]);
    endf_read_obj.clear();
  }
  nucl_data_obj_cal = nucl_data_obj_ori;

  int tsl_no = static_cast<int>(frendy_inp_obj.get_inp_ace_obj().get_nucl_file_name_tsl().size());
  if( calc_mode == frendy_inp_common_obj.ace_fast_mode )
  {
    if( tsl_no == 0 )
    {
      process_nucl_data_ace_fast();
    }
    else //if( tsl_no > 0 )
    {
      string class_name = "NuclearDataProcessorByFrendyInput";
      string func_name  = "process_nucl_data_frendy()";

      vector<string> err_com;
      err_com.push_back("The number of nucl_file_name_tsl is not zero.");
      err_com.push_back("The processing mode is changed from ace_fast_mode to ace_tsl_mode.");
      err_obj.output_caution(class_name, func_name, err_com);

      calc_mode = frendy_inp_common_obj.ace_therm_mode;
      process_nucl_data_ace_therm();
    }
  }
  else if( calc_mode == frendy_inp_common_obj.ace_therm_mode )
  {
    if( tsl_no > 0 )
    {
      process_nucl_data_ace_therm();
    }
    else //if( tsl_no == 0 )
    {
      string class_name = "NuclearDataProcessorByFrendyInput";
      string func_name  = "process_nucl_data_frendy()";

      vector<string> err_com;
      err_com.push_back("The number of nucl_file_name_tsl is zero.");
      err_com.push_back("The processing mode is changed from ace_tsl_mode to ace_fast_mode.");
      err_obj.output_caution(class_name, func_name, err_com);

      calc_mode = frendy_inp_common_obj.ace_fast_mode;
      process_nucl_data_ace_fast();
    }
  }
  else if( calc_mode == frendy_inp_common_obj.ace_dosi_mode )
  {
    process_nucl_data_ace_dosi();
  }
  else if( calc_mode == frendy_inp_common_obj.mg_neutron_mode )
  {
    if( tsl_no == 0 &&
        static_cast<int>(frendy_inp_obj.get_inp_mg_obj().get_ace_file_name_tsl().size()) == 0 )
    {
      process_nucl_data_mg_neutron();
    }
    else
    {
      string class_name = "NuclearDataProcessorByFrendyInput";
      string func_name  = "process_nucl_data_frendy()";

      vector<string> err_com;
      err_com.push_back("The number of nucl_file_name_tsl or ace_file_name_tsl is not zero.");
      err_com.push_back("The processing mode is changed from mg_neutron_mode to mg_tsl_mode.");
      err_obj.output_caution(class_name, func_name, err_com);

      calc_mode = frendy_inp_common_obj.mg_tsl_mode;
      process_nucl_data_mg_tsl();
    }
  }
  else if( calc_mode == frendy_inp_common_obj.mg_tsl_mode )
  {
    if( tsl_no > 0 ||
        static_cast<int>(frendy_inp_obj.get_inp_mg_obj().get_ace_file_name_tsl().size()) > 0 )
    {
      process_nucl_data_mg_tsl();
    }
    else
    {
      string class_name = "NuclearDataProcessorByFrendyInput";
      string func_name  = "process_nucl_data_frendy()";

      vector<string> err_com;
      err_com.push_back("The number of nucl_file_name_tsl and ace_file_name_tsl is zero.");
      err_com.push_back("The processing mode is changed from mg_tsl_mode to mg_neutron_mode.");
      err_obj.output_caution(class_name, func_name, err_com);

      calc_mode = frendy_inp_common_obj.mg_neutron_mode;
      process_nucl_data_mg_neutron();
    }
  }
  else
  {
    string class_name = "NuclearDataProcessorByFrendyInput";
    string func_name  = "process_nucl_data_frendy()";

    vector<string> err_com;
    err_com.push_back("This input file may not be input file for this program.");
    err_com.push_back("Please check the input file.");
    err_com.push_back("The available input mode is as follows:");
    
    vector<string> func_name_list = frendy_inp_obj.get_func_name_list();
    for(int i=0; i<static_cast<int>(func_name_list.size()); i++)
    {
      string str_data = "  " + func_name_list[i];
      err_com.push_back(str_data);
    }
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataProcessorByFrendyInput::make_input_from_frendy_to_njoy()
{
  string output_name = input_name + ".njoy_input.dat";

  MakeInputFromFRENDYtoNJOY make_njoy_input_obj;
  make_njoy_input_obj.make_input_from_frendy_to_njoy(frendy_inp_obj, output_name);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataProcessorByFrendyInput::process_nucl_data_ace_fast()
{
  int i_max = static_cast<int>(nucl_data_obj_ori.size());
  for(int i=0; i<i_max; i++)
  {
    linearize_cross_section(i);
    calc_gas_production_xs(i);
    calc_probability_table(i);
  
    generate_ace_file(i);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataProcessorByFrendyInput::process_nucl_data_ace_therm()
{
  int i_max = static_cast<int>(nucl_data_obj_ori.size());
  for(int i=0; i<i_max; i++)
  {
    //Check tsl nucler data file name
    string nucl_name_tsl = frendy_inp_obj.get_inp_thermal_scatter_obj().get_nucl_file_name_tsl()[i];
    transform(nucl_name_tsl.begin(), nucl_name_tsl.end(), nucl_name_tsl.begin(), ::tolower);

    int skip_flg = 0;
    for(int j=0; j<static_cast<int>(skip_nucl_name_tsl.size()); j++)
    {
      if( nucl_name_tsl == skip_nucl_name_tsl[j] )
      {
        skip_flg = 1;
        break;
      }
    }
    if( skip_flg > 0 )
    {
      continue;
    }

    linearize_cross_section(i);
    calc_gas_production_xs(i);

    calc_thermal_scatter(i);

    calc_probability_table(i);

    generate_ace_file(i);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataProcessorByFrendyInput::process_nucl_data_ace_dosi()
{
  int i_max = static_cast<int>(nucl_data_obj_ori.size());
  for(int i=0; i<i_max; i++)
  {
    linearize_cross_section(i);
    calc_gas_production_xs(i);

    generate_ace_file(i);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataProcessorByFrendyInput::process_nucl_data_mg_neutron()
{
  MultiGroupDataGeneratorInputReader inp_mg_obj = frendy_inp_obj.get_inp_mg_obj();

  string mode_name = inp_mg_obj.get_mg_start_file_mode();
  transform(mode_name.begin(), mode_name.end(), mode_name.begin(), ::tolower);

  int nucl_no = static_cast<int>(inp_mg_obj.get_nucl_file_name().size());

  vector<FastAceDataObject> ace_obj_fast;
  vector<FastAceDataObject>().swap(ace_obj_fast);

  vector<Integer> mat_no;
  mat_no.clear();
  if( mode_name == "endf"  && nucl_no > 0 )
  {
    int i_max = static_cast<int>(nucl_data_obj_ori.size());
    ace_obj_fast.resize(i_max);
    for(int i=0; i<i_max; i++)
    {
      linearize_cross_section(i);
      calc_gas_production_xs(i);
      calc_probability_table(i);

      AceDataObject ace_obj;
      generate_ace_file(i, ace_obj, inp_mg_obj);
      ace_obj_fast[i] = ace_obj.get_fast_ace_data_obj();
      ace_obj.clear();
    }

    vector<string> ace_name = inp_mg_obj.get_ace_file_name();
    int ace_no = static_cast<int>(ace_name.size());
    for(int i=0; i<i_max; i++)
    {  
      if( i < ace_no )
      {
        FastAceDataWriter ace_wri_obj;
        ace_wri_obj.set_ace_data_obj(ace_obj_fast[i]);
        ace_wri_obj.set_ace_file_name(ace_name[i]);
        ace_wri_obj.write_ace_format();
      }
    }
  }
  else //if( mode_name == "ace" )
  {
    mat_no = inp_mg_obj.get_mg_mat_list();

    vector<string> ace_name = inp_mg_obj.get_ace_file_name();
    vector<Real>   temp_vec;

    int i_max = static_cast<int>(ace_name.size());
    if( i_max == 0 )
    {
      string class_name = "NuclearDataProcessorByFrendyInput";
      string func_name  = "process_nucl_data_mg_neutron()";

      vector<string> err_com;
      err_com.push_back("The ace file is selected as a start file.");
      err_com.push_back("However, there is no ace file name.");
      err_com.push_back("Please set the ace file name or use nucl_file_name and nucl_file_name_tsl.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    ace_obj_fast.resize(i_max);
    temp_vec.resize(i_max);
    for(int i=0; i<i_max; i++)
    {
      FastAceDataParser ace_read_obj;
      ace_read_obj.set_file_name(ace_name[i]);
      ace_obj_fast[i] = ace_read_obj.get_ace_data_obj();
      temp_vec[i]     = ace_obj_fast[i].get_temp_kelvin();
      ace_read_obj.clear();
    }

    if( inp_mg_obj.get_temp() < -10.0 ) //There is no temperature data in input file
    {
      inp_mg_obj.set_temp(temp_vec[0]);
    }
  }

  MultiGroupDataGeneratorByFrendyInput mg_obj;
  mg_obj.set_frendy_inp_obj(inp_mg_obj);

  mg_obj.set_ace_obj_fast(ace_obj_fast);
  vector<FastAceDataObject>().swap(ace_obj_fast);

  if( static_cast<int>(nucl_data_obj_ori.size()) > 0 )
  {
    mg_obj.set_nucl_data_obj(nucl_data_obj_ori);
  }
  else
  {
    mg_obj.set_mat_no(mat_no);
  }

  mg_obj.run_frendy_mg();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataProcessorByFrendyInput::process_nucl_data_mg_tsl()
{
  MultiGroupDataGeneratorInputReader inp_mg_obj = frendy_inp_obj.get_inp_mg_obj();

  string mode_name = inp_mg_obj.get_mg_start_file_mode();
  transform(mode_name.begin(), mode_name.end(), mode_name.begin(), ::tolower);

  int nucl_no = static_cast<int>(inp_mg_obj.get_nucl_file_name_tsl().size());

  vector<FastAceDataObject>           ace_obj_fast;
  vector<ThermalScatterAceDataObject> ace_obj_tsl;
  vector<FastAceDataObject>().swap(ace_obj_fast);
  vector<ThermalScatterAceDataObject>().swap(ace_obj_tsl);

  vector<int>     skip_tsl_flg;
  vector<Integer> mat_no;
  Integer tsl_mt_no = 0;
  if( mode_name == "endf" && nucl_no > 0 )
  {
    int i_max = static_cast<int>(nucl_data_obj_ori.size());
    ace_obj_fast.resize(i_max);
    ace_obj_tsl.resize(i_max);
    skip_tsl_flg.resize(i_max);

    for(int i=0; i<i_max; i++)
    {
      //Common part
      linearize_cross_section(i);
      calc_gas_production_xs(i);
      calc_probability_table(i);

      //Stop ACE file output option
      //(ACE file was output after ACE file generation)
      inp_mg_obj.set_ace_output_flg(frendy_inp_common_obj.off);

      //Generation of fast ACE file
      AceDataObject ace_obj;
      calc_mode = frendy_inp_common_obj.mg_tsl_mode_fast;
      generate_ace_file(i, ace_obj, inp_mg_obj);
      ace_obj_fast[i] = ace_obj.get_fast_ace_data_obj();
      ace_obj.clear();

      //Check tsl nucler data file name
      string nucl_name_tsl = inp_mg_obj.get_nucl_file_name_tsl()[i];
      transform(nucl_name_tsl.begin(), nucl_name_tsl.end(), nucl_name_tsl.begin(), ::tolower);

      skip_tsl_flg[i] = 0;
      for(int j=0; j<static_cast<int>(skip_nucl_name_tsl.size()); j++)
      {
        if( nucl_name_tsl == skip_nucl_name_tsl[j] )
        {
          skip_tsl_flg[i] = 1;
          break;
        }
      }
      if( skip_tsl_flg[i] > 0 )
      {
        ace_obj_tsl[i].clear();
        continue;
      }

      //Generation of thermal ACE file
      calc_mode = frendy_inp_common_obj.mg_tsl_mode;
      calc_thermal_scatter(i);
      generate_ace_file(i, ace_obj, inp_mg_obj);
      ace_obj_tsl[i] = ace_obj.get_thermal_scat_ace_data_obj();
      ace_obj.clear();

      //Write ACE files (fast and tsl)
      string ace_name_fast = "";
      string ace_name_tsl  = "";
      if( static_cast<int>(inp_mg_obj.get_ace_file_name_tsl().size()) == i_max )
      {
        ace_name_tsl  = inp_mg_obj.get_ace_file_name_tsl()[i];
      }
      if( static_cast<int>(inp_mg_obj.get_ace_file_name().size()) == i_max )
      {
        if( static_cast<int>(ace_name_tsl.size()) > 0 )
        {
          ace_name_fast = inp_mg_obj.get_ace_file_name()[i];
        }
        else
        {
          ace_name_tsl = inp_mg_obj.get_ace_file_name()[i];
        }
      }

      if( static_cast<int>(ace_name_fast.size()) > 0 )
      {
        FastAceDataWriter           ace_wri_fast;
        string                      ace_dir_fast = ace_name_fast + ".ace.dir";
        ace_wri_fast.set_ace_data_obj(ace_obj_fast[i]);
        ace_wri_fast.set_ace_file_name(ace_name_fast);
        ace_wri_fast.write_ace_format();
        ace_wri_fast.write_dir_data(ace_dir_fast);
      }

      if( static_cast<int>(ace_name_tsl.size()) > 0 )
      {
        ThermalScatterAceDataWriter ace_wri_tsl;
        string                      ace_dir_tsl  = ace_name_tsl  + ".ace.dir";
        ace_wri_tsl.set_ace_data_obj(ace_obj_tsl[i]);
        ace_wri_tsl.set_ace_file_name(ace_name_tsl);
        ace_wri_tsl.write_ace_format();
        ace_wri_tsl.write_dir_data(ace_dir_tsl);
      }
    }

    //Clear ACE file name
    inp_mg_obj.clear_ace_file_name();
  }
  else //if( mode_name == "ace" )
  {
    mat_no = inp_mg_obj.get_mg_mat_list();

    vector<string> ace_name_fast = inp_mg_obj.get_ace_file_name();
    vector<string> ace_name_tsl  = inp_mg_obj.get_ace_file_name_tsl();
    vector<Real>   temp_vec;

    int i_max = static_cast<int>(ace_name_fast.size());
    if( i_max == 0 )
    {
      string class_name = "NuclearDataProcessorByFrendyInput";
      string func_name  = "process_nucl_data_mg_tsl()";

      vector<string> err_com;
      err_com.push_back("The ace file is selected as a start file.");
      err_com.push_back("However, there is no ace file name.");
      err_com.push_back("Please set the ace file name or use nucl_file_name.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    ace_obj_fast.resize(i_max);
    ace_obj_tsl.resize(i_max);
    temp_vec.resize(i_max);
    skip_tsl_flg.resize(i_max);
    for(int i=0; i<i_max; i++)
    {
      FastAceDataParser ace_read_obj_fast;
      ace_read_obj_fast.set_file_name(ace_name_fast[i]);
      ace_obj_fast[i] = ace_read_obj_fast.get_ace_data_obj();
      temp_vec[i]     = ace_obj_fast[i].get_temp_kelvin();
      ace_read_obj_fast.clear();

      //Check tsl ACE file name
      string nucl_name_tsl = inp_mg_obj.get_ace_file_name_tsl()[i];
      transform(nucl_name_tsl.begin(), nucl_name_tsl.end(), nucl_name_tsl.begin(), ::tolower);

      skip_tsl_flg[i] = 0;
      for(int j=0; j<static_cast<int>(skip_nucl_name_tsl.size()); j++)
      {
        if( nucl_name_tsl == skip_nucl_name_tsl[j] )
        {
          skip_tsl_flg[i] = 1;
          break;
        }
      }
      if( skip_tsl_flg[i] > 0 )
      {
        ace_obj_tsl[i].clear();
        continue;
      }

      ThermalScatterAceDataParser ace_read_obj_tsl;
      ace_read_obj_tsl.set_file_name(ace_name_tsl[i]);
      ace_obj_tsl[i] = ace_read_obj_tsl.get_ace_data_obj();
      ace_read_obj_tsl.clear();
    }

    if( inp_mg_obj.get_temp() < -10.0 ) //There is no temperature data in input file
    {
      inp_mg_obj.set_temp(temp_vec[0]);
    }
  }

  MultiGroupDataGeneratorByFrendyInput mg_obj;
  mg_obj.set_frendy_inp_obj(inp_mg_obj);

  mg_obj.set_ace_obj_tsl(ace_obj_fast, ace_obj_tsl);
  vector<FastAceDataObject>().swap(ace_obj_fast);
  vector<ThermalScatterAceDataObject>().swap(ace_obj_tsl);

  if( static_cast<int>(nucl_data_obj_ori.size()) > 0 )
  {
    mg_obj.set_nucl_data_obj(nucl_data_obj_ori);
  }
  else
  {
    mg_obj.set_mat_no(mat_no);
  }
  mg_obj.set_tsl_mt_no(tsl_mt_no);

  mg_obj.run_frendy_mg();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataProcessorByFrendyInput::linearize_cross_section(int i)
{
  //Resonance reconstruction and linearize cross section data
  if( frendy_inp_obj.get_inp_recon_obj().get_process_flg() == frendy_inp_common_obj.process_data )
  {
    ResonanceXSReconstructorByFrendyInput recon_obj;
    recon_obj.set_frendy_inp_obj(frendy_inp_obj.get_inp_recon_obj());
    recon_obj.set_nucl_data_obj(nucl_data_obj_ori[i]);

    nucl_data_obj_cal[i] = recon_obj.get_nucl_data_obj();
    recon_obj.clear();

    if( frendy_inp_obj.get_inp_recon_obj().get_print_set_data_flg() == frendy_inp_common_obj.write_pendf )
    {
      write_pendf( i, frendy_inp_obj.get_inp_recon_obj().get_pendf_file_name()[i],
                      frendy_inp_obj.get_inp_recon_obj().get_pendf_label_data()[i],
                      frendy_inp_obj.get_inp_recon_obj().get_comment_data() );
    }
  }

  //Doppler broadening
  if( frendy_inp_obj.get_inp_dop_obj().get_process_flg() == frendy_inp_common_obj.process_data )
  {
    DopplerCalculatorByFrendyInput dop_obj;
    dop_obj.set_frendy_inp_obj(frendy_inp_obj.get_inp_dop_obj());
    dop_obj.set_nucl_data_obj(nucl_data_obj_cal[i]);
    dop_obj.set_nucl_data_obj_ori(nucl_data_obj_ori[i]);

    nucl_data_obj_cal[i] = dop_obj.get_nucl_data_obj();
    dop_obj.clear();

    if( frendy_inp_obj.get_inp_dop_obj().get_print_set_data_flg() == frendy_inp_common_obj.write_pendf )
    {
      write_pendf( i, frendy_inp_obj.get_inp_dop_obj().get_pendf_file_name()[i],
                      frendy_inp_obj.get_inp_dop_obj().get_pendf_label_data()[i],
                      frendy_inp_obj.get_inp_dop_obj().get_comment_data() );
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataProcessorByFrendyInput::calc_gas_production_xs(int i)
{
  if( frendy_inp_obj.get_inp_gas_xs_obj().get_process_flg() == frendy_inp_common_obj.skip_process_data )
  {
    return;
  }

  GasProductionXSCalculatorByFrendyInput gas_xs_obj;
  gas_xs_obj.set_frendy_inp_obj(frendy_inp_obj.get_inp_gas_xs_obj());
  gas_xs_obj.set_nucl_data_obj(nucl_data_obj_cal[i]);
  gas_xs_obj.set_nucl_data_obj_ori(nucl_data_obj_ori[i]);

  nucl_data_obj_cal[i] = gas_xs_obj.get_nucl_data_obj();
  gas_xs_obj.clear();

  if( frendy_inp_obj.get_inp_gas_xs_obj().get_print_set_data_flg() == frendy_inp_common_obj.write_pendf )
  {
    write_pendf( i, frendy_inp_obj.get_inp_gas_xs_obj().get_pendf_file_name()[i],
                    frendy_inp_obj.get_inp_gas_xs_obj().get_pendf_label_data()[i],
                    frendy_inp_obj.get_inp_gas_xs_obj().get_comment_data() );
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataProcessorByFrendyInput::calc_probability_table(int i)
{
  if( frendy_inp_obj.get_inp_prob_table_obj().get_process_flg() == frendy_inp_common_obj.skip_process_data )
  {
    return;
  }

  ProbabilityTableCalculatorByFrendyInput prob_table_obj;
  prob_table_obj.set_frendy_inp_obj(frendy_inp_obj.get_inp_prob_table_obj());
  prob_table_obj.set_nucl_data_obj(nucl_data_obj_cal[i]);
  prob_table_obj.set_nucl_data_obj_ori(nucl_data_obj_ori[i]);

  nucl_data_obj_cal[i] = prob_table_obj.get_nucl_data_obj();
  prob_table_obj.clear();

  if( frendy_inp_obj.get_inp_prob_table_obj().get_print_set_data_flg() == frendy_inp_common_obj.write_pendf )
  {
    write_pendf( i, frendy_inp_obj.get_inp_prob_table_obj().get_pendf_file_name()[i],
                    frendy_inp_obj.get_inp_prob_table_obj().get_pendf_label_data()[i],
                    frendy_inp_obj.get_inp_prob_table_obj().get_comment_data() );
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataProcessorByFrendyInput::calc_thermal_scatter(int i)
{
  string nucl_file_name_tsl = frendy_inp_obj.get_inp_thermal_scatter_obj().get_nucl_file_name_tsl()[i];

  if( frendy_inp_obj.get_inp_thermal_scatter_obj().get_process_flg()
        == frendy_inp_common_obj.skip_process_data &&
      static_cast<int>(nucl_file_name_tsl.size()) == 0 )
  {
    return;
  }

  //Read nucler data object containing thermal scattering law data
  Endf6FileStore endf_read_obj;
  nucl_data_obj_tsl[i] = endf_read_obj.get_nucl_data_obj(nucl_file_name_tsl);
  endf_read_obj.clear();

  //Check FRENDY input file concerning thermal scattering law data
  check_tsl_data(i);

  if( frendy_inp_obj.get_inp_thermal_scatter_obj().get_process_flg()
        == frendy_inp_common_obj.skip_process_data )
  {
    return;
  }

  ThermalScatterCalculatorByFrendyInput thermal_scatter_obj;
  thermal_scatter_obj.set_frendy_inp_obj(frendy_inp_obj.get_inp_thermal_scatter_obj());
  thermal_scatter_obj.set_nucl_data_obj(nucl_data_obj_cal[i]);
  thermal_scatter_obj.set_nucl_data_obj_tsl(nucl_data_obj_tsl[i]);

  nucl_data_obj_cal[i] = thermal_scatter_obj.get_nucl_data_obj_without_tsl();
  thermal_scatter_obj.clear();

  if( frendy_inp_obj.get_inp_thermal_scatter_obj().get_print_set_data_flg()
        == frendy_inp_common_obj.write_pendf )
  {
    write_pendf( 0, frendy_inp_obj.get_inp_thermal_scatter_obj().get_pendf_file_name()[i],
                    frendy_inp_obj.get_inp_thermal_scatter_obj().get_pendf_label_data()[i],
                    frendy_inp_obj.get_inp_thermal_scatter_obj().get_comment_data() );
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataProcessorByFrendyInput::check_tsl_data(int i)
{
  check_tsl_mass_data(i);

  read_principal_atom_no(i);

  read_atom_type_no_and_tsl_za_data(i);

  check_thermal_scatter_inp_data(i);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataProcessorByFrendyInput::check_tsl_mass_data(int i)
{
  Real mass_nucl = nucl_data_obj_cal[i].get_general_data_obj().get_mass();

  //Check mass data
  Integer elastic_scat_flg = nucl_data_obj_tsl[i].get_thermal_scat_data_obj().get_elastic_scat_flg();
  if( elastic_scat_flg == 1 || elastic_scat_flg == 2 )
  {
    Real mass_tsl  = nucl_data_obj_tsl[i].get_general_data_obj().get_mass();
    if( mass_tsl * 0.9 > mass_nucl || mass_tsl * 1.1 < mass_nucl )
    {
      string class_name = "NuclearDataProcessorByFrendyInput";
      string func_name  = "check_tsl_mass_data(int i)";

      ostringstream oss01, oss02;
      oss01 << mass_nucl;
      oss02 << mass_tsl;
      string str_data01 = "Mass of nucleus                              : " + oss01.str();
      string str_data02 = "Standard mass of thermal scattering law data : " + oss02.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back("The difference beween mass of nucleus and sandard mass of thermal");
      err_com.push_back("scattering law data is large.");
      err_com.push_back("The thermal scattering law data may not be appropriate.");
      err_com.push_back("Please check the explanation of the principal atom.");
      err_obj.output_caution(class_name, func_name, err_com);
    } 
  }

  //Check mass data in incoherent inelastic scattering law data
  vector<Real> inelastic_scat_law_coef
                 = nucl_data_obj_tsl[i].get_thermal_scat_data_obj().get_inelastic_scat_law_coef();

  int mass_err_flg = 0;
  int i_max        = static_cast<int>(inelastic_scat_law_coef.size());
  for(int i=2; i<i_max; i+=6)
  {
    if( i == 2 )
    {
      Real mass_principal = inelastic_scat_law_coef[i];
      if( mass_principal * 0.9 > mass_nucl || mass_principal * 1.1 < mass_nucl )
      {
        mass_err_flg++;

        string class_name = "NuclearDataProcessorByFrendyInput";
        string func_name  = "check_tsl_mass_data(int i)";

        ostringstream oss01, oss02;
        oss01 << mass_nucl;
        oss02 << mass_principal;
        string str_data01 = "Mass of nucleus                                           : " + oss01.str();
        string str_data02 = "Mass of principal atom in incoherent inelastic scattering : " + oss02.str();

        vector<string> err_com;
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back("The difference beween mass of nucleus and mass of principal atom");
        err_com.push_back("is large.");
        err_com.push_back("The thermal scattering law data may not be appropriate.");
        err_com.push_back("Please check the explanation of the principal atom.");
        err_obj.output_caution(class_name, func_name, err_com);
      }
    }
    else
    {
      Real mass_non_principal = inelastic_scat_law_coef[i];
      if( mass_non_principal * 0.9 < mass_nucl && mass_nucl < mass_non_principal * 1.1 )
      {
        string class_name = "NuclearDataProcessorByFrendyInput";
        string func_name  = "check_tsl_mass_data(int i)";

        ostringstream oss01, oss02;
        oss01 << mass_nucl;
        oss02 << mass_non_principal;
        string str_data01 = "Mass of nucleus                                               : " + oss01.str();
        string str_data02 = "Mass of non principal atom in incoherent inelastic scattering : " + oss02.str();

        vector<string> err_com;
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back("The mass of nucleus is similar to that of non principal atom.");

        if( mass_err_flg == 0 )
        {
          err_com.push_back("This nucleus may be non principal atom.");
          err_com.push_back("Please check the explanation of the principal atom.");
          err_obj.output_caution(class_name, func_name, err_com);
        }
        else
        {
          err_com.push_back("Since the mass of nuleus is different to standard mass of thermal");
          err_com.push_back("scattering law data and mass of principal atom, this program recognize");
          err_com.push_back("that this nucleus is non principal atom.");
          err_com.push_back("Please check the explanation of the principal atom.");
          err_obj.output_runtime_error(class_name, func_name, err_com);
        }
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataProcessorByFrendyInput::read_principal_atom_no(int i)
{
  //Read principal_atom_no from thermal scattering law data
  int atom_no_flg = 0;
  if( frendy_inp_obj.get_inp_thermal_scatter_obj().get_principal_atom_no() !=
      frendy_inp_common_obj.get_principal_atom_no_def() )
  {
    atom_no_flg = 1;
  }

  int mat_no_tsl  = nucl_data_obj_tsl[i].get_general_data_obj().get_mat_no();
  int mat_no_nucl = nucl_data_obj_cal[i].get_general_data_obj().get_mat_no();

  ThermalScatterMatList tsl_list;
  vector<ThermalScatterMatData> tsl_data = tsl_list.get_thermal_scat_data(mat_no_tsl);

  tsl_mat_data_pos = -1;
  if( static_cast<int>(tsl_data.size()) == 1 )
  {
    tsl_mat_data_pos = 0;
  }
  else if( static_cast<int>(tsl_data.size()) == 0 )
  {
    string class_name = "MakeInputFromFRENDYtoNJOY";
    string func_name  = "read_principal_atom_no(int i)";

    vector<string> err_com;

    ostringstream oss01;
    oss01 << mat_no_tsl;
    string str_data01 = "Material number of TSL : " + oss01.str();
    err_com.push_back(str_data01);
    err_com.push_back("This material number is not available in this program.");
    err_com.push_back("Please check your input file, nuclear data file, and FrendyUtils/ThermalScatterMatList.cpp.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
  else if( static_cast<int>(tsl_data.size()) > 1 )
  {
    for(int j=0; j<static_cast<int>(tsl_data.size()); j++)
    {
      if( mat_no_nucl/100 == tsl_data[j].get_mat_no_principal() / 100 )
      {
        tsl_mat_data_pos = j;
        break;
      }
    }

    string class_name = "MakeInputFromFRENDYtoNJOY";
    string func_name  = "read_principal_atom_no(int i)";

    vector<string> err_com;
    if( tsl_mat_data_pos < 0 )
    {
      err_com.push_back("Material number of nucleus is different to FRENDY data from");
      err_com.push_back("FrendyUtils/ThermalScatterMatList.cpp.");
      err_com.push_back("The nuleus data may be inappropriate.");
      err_com.push_back("The first material number from ThermalScatterMatList is used for the material number.");
      err_com.push_back("Please check your input file and nuclear data file.");

      tsl_mat_data_pos = 0;
    }
    else
    {
      err_com.push_back("Material number of nucleus is duplicated.");
      err_com.push_back("The first material number from ThermalScatterMatList is used for the material number.");
      err_com.push_back("Please check your input file, nuclear data file, and FrendyUtils/ThermalScatterMatList.cpp.");
    }

    ostringstream oss01;
    oss01 << mat_no_nucl;
    string str_data01 = "  Material number of nucleus : " + oss01.str();
    err_com.push_back(str_data01);

    err_com.push_back("  Material name / number from ThermalScatterMatList : ");
    for(int j=0; j<static_cast<int>(tsl_data.size()); j++)
    {
      ostringstream oss02;
      oss02 << static_cast<Integer>(tsl_data[j].get_mat_no_principal());
      string str_data02 = "    " + tsl_data[j].get_mat_name() + " / " + oss02.str();

      if( j == tsl_mat_data_pos )
      {
        str_data02 = str_data02 + " *** use this data ***";
      }
      err_com.push_back(str_data02);
    }
    err_obj.output_caution(class_name, func_name, err_com);
  }

  principal_atom_no = 0;
  vector<Real> scat_law_coef = nucl_data_obj_tsl[i].get_thermal_scat_data_obj().get_inelastic_scat_law_coef();
  if( static_cast<int>(scat_law_coef.size()) >= 5 )
  {
    principal_atom_no = static_cast<Integer>(scat_law_coef[5]);
  }

  if( principal_atom_no <= 0 )
  {
    principal_atom_no = tsl_data[tsl_mat_data_pos].get_atom_no_principal();
  }

  //Check material number
  if( tsl_data[tsl_mat_data_pos].get_mat_no() != mat_no_tsl )
  {
    string class_name = "NuclearDataProcessorByFrendyInput";
    string func_name  = "read_principal_atom_no(int i)";

    ostringstream oss01;
    oss01 << mat_no_tsl;
    string str_data01 = "Material number in thermal scattering law data : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("This material number is not listed in the ThermalScatterMatData class");
    err_com.push_back("in FrendyUtils/ThermalScatterMatList.cpp");
    err_com.push_back("This material number may not be appropriate for the thermal scattering law data.");
    err_com.push_back("Please check the thermal scattering law data or modify ThermalScatterMatData.");

    if( atom_no_flg == 0 )
    {
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
    else
    {
      err_obj.output_caution(class_name, func_name, err_com);
    }
  }

  int mat_no_principal     = tsl_data[tsl_mat_data_pos].get_mat_no_principal();
  int mat_no_non_principal = tsl_data[tsl_mat_data_pos].get_mat_no_non_principal();
  if( mat_no_nucl/100 != mat_no_principal/100 )
  {
    string class_name = "NuclearDataProcessorByFrendyInput";
    string func_name  = "read_principal_atom_no(int i)";

    ostringstream oss01, oss02, oss03;
    oss01 << mat_no_nucl / 100;
    oss02 << mat_no_principal / 100;
    oss03 << mat_no_non_principal / 100;
    string str_data01 = "Proton number in nuclear data            : " + oss01.str();
    string str_data02 = "Proton number of principal atom data     : " + oss02.str();
    string str_data03 = "Proton number of non principal atom data : " + oss03.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    if( mat_no_non_principal > 0 )
    {
      err_com.push_back(str_data03);
    }

    err_com.push_back("The proton number in nuclear data is not identical to that of");
    err_com.push_back("principal atom data (obtained from ThermalScatterMatData).");

    if( mat_no_nucl/100 == mat_no_non_principal/100 )
    {
      err_com.push_back("Since the proton number in nuclear data is identical to that of");
      err_com.push_back("non principal atom data, you may be mistake to choice the principal atom.");
    }
    err_com.push_back("This proton number in nuclear data may not be appropriate.");
    err_com.push_back("Please check the thermal scattering law data or modify ThermalScatterMatData.");
    if( atom_no_flg == 0 )
    {
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
    else
    {
      err_obj.output_caution(class_name, func_name, err_com);
    }
  }
  else if( mat_no_principal%100 > 0 && mat_no_nucl != mat_no_principal )
  {
    string class_name = "NuclearDataProcessorByFrendyInput";
    string func_name  = "read_principal_atom_no(int i)";

    ostringstream oss01, oss02, oss03;
    oss01 << mat_no_nucl;
    oss02 << mat_no_principal;
    oss03 << mat_no_non_principal;
    string str_data01 = "Material number in nuclear data            : " + oss01.str();
    string str_data02 = "Material number of principal atom data     : " + oss02.str();
    string str_data03 = "Material number of non principal atom data : " + oss03.str();

    vector<string> err_com; 
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    if( mat_no_non_principal > 0 )
    {
      err_com.push_back(str_data03);
    }

    err_com.push_back("The material number in nuclear data is not identical to that of");
    err_com.push_back("principal atom data (obtained from ThermalScatterMatData).");

    if( mat_no_nucl == mat_no_non_principal )
    {
      err_com.push_back("Since the material number in nuclear data is identical to that of");
      err_com.push_back("non principal atom data, you may be mistake to choice the principal atom.");
    }
    err_com.push_back("This material number in nuclear data may not be appropriate.");
    err_com.push_back("Please check the thermal scattering law data or modify ThermalScatterMatData.");
    if( atom_no_flg == 0 )
    {
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
    else
    {
      err_obj.output_caution(class_name, func_name, err_com);
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataProcessorByFrendyInput::read_atom_type_no_and_tsl_za_data(int i)
{
  //Read atom_type_no and tsl_za_data_non_principal from thermal scattering law data
  ThermalScatterMatList tsl_list;

  atom_type_no              = 1;
  tsl_za_data_principal     = static_cast<Integer>(round(nucl_data_obj_cal[i].get_general_data_obj().get_mat_data()));
  tsl_za_data_non_principal = 0;

  vector<Real> inelastic_scat_law_coef
                 = nucl_data_obj_tsl[i].get_thermal_scat_data_obj().get_inelastic_scat_law_coef();
 
  int i_max = static_cast<int>(inelastic_scat_law_coef.size());
  if( i_max > 9 )
  {
     //The type of analytic function used for this atom type is SCT approximation.
    if( inelastic_scat_law_coef[6] < min_value )
    {
      Real mass_tsl           = nucl_data_obj_tsl[i].get_general_data_obj().get_mass();
      Real mass_principal     = inelastic_scat_law_coef[2];
      Real mass_non_principal = inelastic_scat_law_coef[8];

      Real mass_beo           = 24.79280;   //From JENDL-4.0 BeO
      Real mass_be            =  8.93476;   //From JENDL-4.0 Be-9
      Real mass_o             = 15.85750;   //From JENDL-4.0 O-16

      Real mass_benzene       = 77.38300;   //From JENDL-4.0 Benzene
      Real mass_h             =  0.9991673; //From JENDL-4.0 H-1
      Real mass_c             = 11.89690;   //From JENDL-4.0 C-0

      Real mass_sio2          = 27.84423;   //From ENDF/B-VIII.0 SiO2
      Real mass_si            = 29.5; 
      if( mass_beo * 0.9 < mass_tsl           && mass_tsl           < mass_beo * 1.1 && 
          mass_be  * 0.9 < mass_principal     && mass_principal     < mass_be  * 1.1 && 
          mass_o   * 0.9 < mass_non_principal && mass_non_principal < mass_o   * 1.1 )
      {
        //The thermal scattering law data is BeO.
        atom_type_no = 2; //Be + O

        ThermalScatterMatData tsl_data = tsl_list.get_thermal_scat_data(27)[0]; //Be_in_BeO
        tsl_za_data_non_principal = tsl_data.get_mat_data_non_principal();
       tsl_data.clear();
      }
      if( mass_benzene * 0.9 < mass_tsl           && mass_tsl           < mass_benzene * 1.1 && 
          mass_h       * 0.9 < mass_principal     && mass_principal     < mass_h       * 1.1 && 
          mass_c       * 0.9 < mass_non_principal && mass_non_principal < mass_c       * 1.1 )
      {
        //The thermal scattering law data is Benzene.
        atom_type_no = 2; //C + H

        ThermalScatterMatData tsl_data = tsl_list.get_thermal_scat_data(40)[0]; //H_in_benzene
        tsl_za_data_non_principal = tsl_data.get_mat_data_non_principal();
        tsl_data.clear();
      }
      if( mass_sio2 * 0.9 < mass_tsl           && mass_tsl           < mass_sio2 * 1.1 && 
          mass_si   * 0.9 < mass_principal     && mass_principal     < mass_si   * 1.1 && 
          mass_o    * 0.9 < mass_non_principal && mass_non_principal < mass_o    * 1.1 )
      {
        //The thermal scattering law data is SiO2
        //atom_type_no = 3; //Si + O + O

        ThermalScatterMatData tsl_data = tsl_list.get_thermal_scat_data(47)[0]; //si_in_alpha_quartz
        tsl_za_data_non_principal = tsl_data.get_mat_data_non_principal();
        atom_type_no              = tsl_data.get_atom_no_mix(); //=3 (Si + O + O)
        tsl_data.clear();
      }
      else if( frendy_inp_obj.get_inp_ace_obj().get_atom_type_no() == 1 )
      {
        string class_name = "NuclearDataProcessorByFrendyInput";
        string func_name  = "read_atom_type_no_and_tsl_za_data(int i)";

        vector<string> err_com;
        err_com.push_back("The SCT approximation is used for non-principal atom in this thermal");
        err_com.push_back("scattering law data.");
        err_com.push_back("In this program, BeO, Benzene, and SiO2 are only available for this option.");
        err_com.push_back("This thermal scattering law data can not set atom_type_no and");
        err_com.push_back("moderator_za_data automaticaly.");
        err_com.push_back("Please check the thermal scattering law data or set above values manually.");
        err_obj.output_runtime_error(class_name, func_name, err_com);
      }
    }
  }

  tsl_list.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataProcessorByFrendyInput::check_thermal_scatter_inp_data(int i)
{
  ThermalScatterInputReader inp_thermal_scatter_obj = frendy_inp_obj.get_inp_thermal_scatter_obj();

  Integer principal_atom_no_inp = inp_thermal_scatter_obj.get_principal_atom_no();
  if( principal_atom_no_inp == frendy_inp_common_obj.get_principal_atom_no_def() ||
      static_cast<int>(frendy_inp_obj.get_inp_mg_obj().get_nucl_file_name_tsl().size()) > 1 )
  {
    principal_atom_no_inp = principal_atom_no;
    inp_thermal_scatter_obj.set_principal_atom_no(principal_atom_no_inp);
    frendy_inp_obj.set_inp_thermal_scatter_obj(inp_thermal_scatter_obj);
  }
  else if( principal_atom_no_inp != principal_atom_no )
  {
    string class_name = "NuclearDataProcessorByFrendyInput";
    string func_name  = "check_thermal_scatter_inp_data()";

    ostringstream oss01, oss02;
    oss01 << principal_atom_no_inp;
    oss02 << principal_atom_no;
    string str_data01 = "principal_atom_no from FRENDY input file           : " + oss01.str();
    string str_data02 = "principal_atom_no from thermal scattering law data : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("The number of principal atoms (principal_atom_no) in the input file");
    err_com.push_back("is not identical to that in the thermal scattering law data.");
    err_com.push_back("The principal_atom_no from FRENDY input file may not be appropriate.");
    err_com.push_back("");
    err_com.push_back("Please check the input file or thermal scattering law data.");
    err_obj.output_caution(class_name, func_name, err_com);
  }
  inp_thermal_scatter_obj.clear();
  
  //Check input data for ace file generation
  if( calc_mode == frendy_inp_common_obj.ace_therm_mode ||
      calc_mode == frendy_inp_common_obj.mg_tsl_mode )
  {
    check_thermal_scatter_inp_data_ace_mode(i);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataProcessorByFrendyInput::check_thermal_scatter_inp_data_ace_mode(int i)
{
  vector<string> err_com;

  AceDataGeneratorInputReader inp_ace_obj = frendy_inp_obj.get_inp_ace_obj();

  Integer atom_type_no_inp = inp_ace_obj.get_atom_type_no();
  if( atom_type_no_inp == frendy_inp_common_obj.get_atom_type_no_def() ||
      static_cast<int>(frendy_inp_obj.get_inp_mg_obj().get_nucl_file_name_tsl().size()) > 1 )
  {
    atom_type_no_inp = atom_type_no;
    inp_ace_obj.set_atom_type_no(atom_type_no_inp);
  }
  else if( i > 0 )
  {
    atom_type_no_inp = atom_type_no;
    inp_ace_obj.set_atom_type_no(atom_type_no_inp);
  }
  else if( atom_type_no_inp != atom_type_no )
  {
    ostringstream oss01, oss02;
    oss01 << atom_type_no_inp;
    oss02 << atom_type_no;
    string str_data01 = "atom_type_no from FRENDY input file           : " + oss01.str();
    string str_data02 = "atom_type_no from thermal scattering law data : " + oss02.str();
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("The number of atom types in mixed moderator (atom_type_no) in the input file");
    err_com.push_back("is not identical to that in the thermal scattering law data.");
    err_com.push_back("The atom_type_no from FRENDY input file may not be appropriate.");
    err_com.push_back("");
  }

  MakeInputFromFRENDYtoNJOY  make_njoy_input_obj;
  vector<Integer> moderator_za_data_ref
                    = make_njoy_input_obj.get_moderator_za_data
                                            (nucl_data_obj_tsl[i], nucl_data_obj_ori[i], tsl_mat_data_pos);
  vector<Integer> moderator_za_data_inp = inp_ace_obj.get_moderator_za_data();
  if( static_cast<int>(moderator_za_data_inp.size()) == 0 )
  {
    moderator_za_data_inp = moderator_za_data_ref;
  }
  else if( i > 0 )
  {
    moderator_za_data_inp = moderator_za_data_ref;
  }
  else
  {
    if( moderator_za_data_inp[0] != tsl_za_data_principal )
    {
      ostringstream oss01, oss02;
      oss01 << moderator_za_data_inp[0];
      oss02 << tsl_za_data_principal;
      string str_data01 = "First moderator_za_data from FRENDY input file           : " + oss01.str();
      string str_data02 = "First moderator_za_data from thermal scattering law data : " + oss02.str();
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back("The first moderator component za value (moderator_za_data) from FRENDY");
      err_com.push_back("input file is not identical to that in the thermal scattering law data.");
      err_com.push_back("The first moderator_za_data from FRENDY input file may not be appropriate.");
      err_com.push_back("");
    }

    if( atom_type_no_inp == 2 )
    {
      if( static_cast<int>(moderator_za_data_inp.size()) == 1 )
      {
        moderator_za_data_inp.push_back(tsl_za_data_non_principal);
      }
      else
      {
        if( moderator_za_data_inp[1] != tsl_za_data_non_principal )
        {
          ostringstream oss01, oss02;
          oss01 << moderator_za_data_inp[1];
          oss02 << tsl_za_data_non_principal;
          string str_data01 = "Second moderator_za_data from FRENDY input file           : " + oss01.str();
          string str_data02 = "Second moderator_za_data from thermal scattering law data : " + oss02.str();
          err_com.push_back(str_data01);
          err_com.push_back(str_data02);
          err_com.push_back("The second moderator component za value (moderator_za_data) from FRENDY");
          err_com.push_back("input file is not identical to that in the thermal scattering law data.");
          err_com.push_back("The second moderator_za_data from FRENDY input file may not be appropriate.");
          err_com.push_back("");
        }
      }
    }
  }
  inp_ace_obj.set_moderator_za_data(moderator_za_data_inp);

  frendy_inp_obj.set_inp_ace_obj(inp_ace_obj);
  inp_ace_obj.clear();

  if( static_cast<int>(err_com.size()) > 0 )
  {
    string class_name = "NuclearDataProcessorByFrendyInput";
    string func_name  = "check_thermal_scatter_inp_data_ace_mode(int i)";

    err_com.push_back("Some input problems for thermal scattering law data are observed.");
    err_com.push_back("Please check the input file or thermal scattering law data.");
    err_obj.output_caution(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataProcessorByFrendyInput::generate_ace_file(int i)
{
  AceDataGeneratorByFrendyInput ace_gen_obj;

  generate_ace_file_common(i, ace_gen_obj);

  ace_gen_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataProcessorByFrendyInput::generate_ace_file(int i, AceDataObject& ace_obj,
                                                          MultiGroupDataGeneratorInputReader& inp_mg_obj)
{
  AceDataGeneratorByFrendyInput ace_gen_obj;

  if( inp_mg_obj.get_ace_output_flg() == frendy_inp_common_obj.off )
  {
    ace_gen_obj.set_write_ace_flg(ace_gen_obj.skip_write_ace);
  }

  generate_ace_file_common(i, ace_gen_obj);

  ace_obj = ace_gen_obj.get_ace_data_obj();
  ace_gen_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataProcessorByFrendyInput::generate_ace_file_common
                                          (int i, AceDataGeneratorByFrendyInput& ace_gen_obj)
{
  if( frendy_inp_obj.get_inp_ace_obj().get_process_flg() == frendy_inp_common_obj.skip_process_data )
  {
    return;
  }

  ace_gen_obj.set_frendy_inp_obj(frendy_inp_obj.get_inp_ace_obj());
  ace_gen_obj.set_nucl_data_obj(nucl_data_obj_cal[i]);
  ace_gen_obj.set_inp_pos(i);


  if( calc_mode == frendy_inp_common_obj.mg_tsl_mode_fast )
  {
    AceDataGeneratorInputReader ace_inp_obj_mod = frendy_inp_obj.get_inp_ace_obj();
    ace_inp_obj_mod.set_generation_mode(ace_inp_obj_mod.inp_mode_fast);
    ace_gen_obj.set_frendy_inp_obj(ace_inp_obj_mod);
    ace_inp_obj_mod.clear();
  }

  if( calc_mode == frendy_inp_common_obj.ace_therm_mode ||
      calc_mode == frendy_inp_common_obj.mg_tsl_mode )
  {
    AceDataGeneratorInputReader ace_inp_obj_mod = frendy_inp_obj.get_inp_ace_obj();
    ace_inp_obj_mod.set_generation_mode(ace_inp_obj_mod.inp_mode_therm);
    ace_gen_obj.set_frendy_inp_obj(ace_inp_obj_mod);
    ace_gen_obj.set_nucl_data_obj_ori(nucl_data_obj_tsl[i]);
  }
  else
  {
    ace_gen_obj.set_nucl_data_obj_ori(nucl_data_obj_ori[i]);
  }

  ace_gen_obj.generate_ace_data();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataProcessorByFrendyInput::write_pendf(int i, string pendf_name, string pendf_label,
                                                    vector<string> comment_data)
{
  if( static_cast<int>(pendf_name.size()) == 0 )
  {
    return;
  }

  Endf6Writer endf_wri_obj;
  endf_wri_obj.set_nucl_data_obj(nucl_data_obj_cal[i]);
  endf_wri_obj.set_pendf_label(pendf_label);
  endf_wri_obj.set_additional_comment(comment_data);
  endf_wri_obj.write_pendf_with_tape_end(pendf_name);
  endf_wri_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

string NuclearDataProcessorByFrendyInput::get_input_name()
{
  return input_name;
}

