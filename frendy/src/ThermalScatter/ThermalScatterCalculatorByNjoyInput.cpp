#include "ThermalScatter/ThermalScatterCalculatorByNjoyInput.hpp"

using namespace frendy;

//constructor
ThermalScatterCalculatorByNjoyInput::ThermalScatterCalculatorByNjoyInput(void)
{
  clear();
}

//destructor
ThermalScatterCalculatorByNjoyInput::~ThermalScatterCalculatorByNjoyInput(void)
{
  clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterCalculatorByNjoyInput::clear()
{
  calc_flg = 0;
  scat_calc_obj.clear();
  scat_conv_obj.clear();

  vector<NuclearDataObject>().swap(pendf_new_data_obj);
  //for(int i=0; i<static_cast<int>(pendf_new_data_obj.size()); i++)
  //{
  //  pendf_new_data_obj[i].clear();
  //}
  //pendf_new_data_obj.clear();

  input_file_name_njoy.clear();
  start_line_no = 0;

  endf_name.clear();
  pendf_name_old.clear();
  pendf_name_new.clear();

  mat_endf      = unassigned_mat_no;
  mat_pendf     = unassigned_mat_no;
  bin_no        = -1;
  temp_no       = -1;
  opt_inelastic = -1;
  opt_elastic   = -1;
  atom_no       = -1;
  mt_out        = unassigned_mt_no;
  opt_print     = -1;

  temp.clear();

  err     = 0.0;
  ene_max = 0.0;

  temp_no_int  = -1;
  endf_data_no = -1;
  temp_no_list.clear();

  time_total = 0.0;
  time_each_temp.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterCalculatorByNjoyInput::calc_thermal_scatter()
{
  if( calc_flg == 1 )
  {
    return;
  }
  calc_flg = 1;

  cout << "****************************** Thermal scattering xs calculation ******************************";
  cout << endl << endl;
  time_obj.output_current_time();

  set_input_data();
  output_input_file_name();

  boost::timer::cpu_timer timer_total;

  set_pendf_new_data_obj();

  time_each_temp.resize(temp_no_int);
  for(int i=0; i<temp_no_int; i++)
  {
    cout << "  Temperature : " << temp[i] << " [K]" << endl;
    boost::timer::cpu_timer timer_temp;

    //Calculation of thermal scatter cross section at each temperature
    int ele_no = temp_no_list[i];
    scat_calc_obj.set_temp(temp[i]);
    scat_calc_obj.set_nucl_data_obj(pendf_new_data_obj[ele_no]);
    scat_calc_obj.calc_thermal_scatter();

    scat_calc_obj.output_set_data_information();
    scat_calc_obj.calc_thermal_scatter();
    pendf_new_data_obj[ele_no] = scat_calc_obj.get_nucl_data_obj();

    scat_conv_obj.convert_thermal_scatter_data(mt_out, pendf_new_data_obj[temp_no_list[i]]);

    time_each_temp[i] = static_cast<Real>(timer_temp.elapsed().wall * 1.0E-9);   
    cout << "  Calculation time of temperature " << temp[i] << " [K] : " << time_each_temp[i] << " [s]" << endl;
    cout << endl;
  }
  time_total = static_cast<Real>(timer_total.elapsed().wall * 1.0E-9);
  cout << "Total calculation time : " << time_total << " [s]" << endl;
  cout << endl;
  cout << "***********************************************************************************************";
  cout << endl << endl;

  scat_calc_obj.clear();
  scat_conv_obj.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterCalculatorByNjoyInput::output_input_file_name()
{
  cout << "=== Nuclear data file information ===" << endl;
  cout << "  Input File Name          : " << input_file_name_njoy << endl;
  cout << "  ENDF  File Name          : " << endf_name            << endl;
  cout << "  PENDF File Name (input)  : " << pendf_name_old       << endl;
  cout << "  PENDF File Name (output) : " << pendf_name_new       << endl;
  cout << "  Material Number (ENDF)   : " << mat_endf             << endl;
  cout << "  Material Number (PENDF)  : " << mat_pendf            << endl;
  cout << endl;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterCalculatorByNjoyInput::set_input_data()
{
  //Read thermr input file
  ThermrInputReader read_njoy_obj;
  read_njoy_obj.read_input(input_file_name_njoy, start_line_no);

  endf_name      = read_njoy_obj.get_endf_name();
  pendf_name_old = read_njoy_obj.get_pendf_name_old();
  pendf_name_new = read_njoy_obj.get_pendf_name_new();
  mat_endf       = read_njoy_obj.get_mat_endf();
  mat_pendf      = read_njoy_obj.get_mat_pendf();
  bin_no         = read_njoy_obj.get_bin_no();
  temp_no        = read_njoy_obj.get_temp_no();
  opt_inelastic  = read_njoy_obj.get_opt_inelastic();
  opt_elastic    = read_njoy_obj.get_opt_elastic();
  atom_no        = read_njoy_obj.get_atom_no();
  mt_out         = read_njoy_obj.get_mt_out();
  opt_print      = read_njoy_obj.get_opt_print();
  temp           = read_njoy_obj.get_temp();
  err            = read_njoy_obj.get_err();
  ene_max        = read_njoy_obj.get_ene_max();
  temp_no_int    = static_cast<int>(temp.size());
  temp_no_list.resize(temp_no_int);
  for(int i=0; i<temp_no_int; i++)
  {
    temp_no_list[i] = -1;
  }

  read_njoy_obj.clear();

  //Set common data to scat_calc_obj
  set_scat_calc_obj();

  //Check temperature number
  if( temp_no != static_cast<Integer>(temp_no_int) )
  {
    string class_name = "ThermalScatterCalculatorByNjoyInput";
    string func_name  = "set_scat_calc_obj()";

    ostringstream oss01, oss02;
    oss01 << temp_no;
    oss02 << temp_no_int;
    string str_data01 = "Temperature number    : " + oss01.str();
    string str_data02 = "Temperature data size : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("Temperature number is not identical to temperature data size.");
    err_com.push_back("Please check the thermr input file.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterCalculatorByNjoyInput::set_scat_calc_obj()
{
  scat_calc_obj.clear();
  scat_calc_obj.set_opt_inelastic(opt_inelastic);
  scat_calc_obj.set_opt_elastic(opt_elastic);
  scat_calc_obj.set_bin_no(bin_no);
  scat_calc_obj.set_atom_no(atom_no);
  scat_calc_obj.set_err(err);
  scat_calc_obj.set_ene_max(ene_max);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterCalculatorByNjoyInput::set_pendf_new_data_obj()
{
  EndfTapeDivider         div_obj;
  EndfFileReader          efr_obj;
  Endf6Converter          conv_obj;
  vector<string>          endf_file_text;
  vector<vector<string> > pendf_old_file_text;
  Endf6Parser             endf_file_parser, pendf_old_file_parser;
  NuclearDataObject       endf_data_obj;
  endf_data_obj.clear();

  if( mat_endf > 0 )
  {
    //For endf_data
    div_obj.set_file_name(endf_name);
    endf_file_text = div_obj.get_data(mat_endf);
    efr_obj.set_endf_data(endf_file_text);
    clr_obj.clear_vec_array1_str(endf_file_text);
    vector<Integer> mt_no_list = efr_obj.get_mt_list(7);
    if( static_cast<int>(mt_no_list.size()) == 0 )
    {
      string class_name = "ThermalScatterCalculatorByNjoyInput";
      string func_name  = "set_pendf_new_data_obj()";
      ostringstream oss01;
      oss01 << mat_endf;
      string str_data01 = "Evaluate nuclear data file name (TSL) : " + endf_name;
      string str_data02 = "Material number                       : " + oss01.str();
      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back("The thermal scattering law data (MF=7) is not found.");
      err_com.push_back("There is no problem if you want to process thermal scattering law data using free gas model.");
      err_com.push_back("Please check the nuclear data file name or MAT number if you want to process thermal scattering law data in ENDF file.");
      err_obj.output_caution(class_name, func_name, err_com);
    }

    for(int i=0; i<static_cast<Integer>(mt_no_list.size()); i++)
    {
      if( mt_no_list[i] == 2 )
      {
        if( opt_elastic == 1 )
        {
          opt_elastic = 10;
        }
        else
        {
          string class_name = "ThermalScatterCalculatorByNjoyInput";
          string func_name  = "set_pendf_new_data_obj()";
          ostringstream oss01;
          oss01 << opt_elastic;
          string str_data01 = "Elastic option : " + oss01.str();
          vector<string> err_com;
          err_com.push_back(str_data01);
          err_com.push_back("The elastic scattering data(MF=7, MT=2) is exist in the ENDF data.");
          err_com.push_back("However, this input data does not use the ENDF data.");
          err_obj.output_caution(class_name, func_name, err_com);
        }
      }
      else if( mt_no_list[i] == 4 )
      {
        if( opt_inelastic != 2 && opt_inelastic != 4 ) //free gas model or no_calc
        {
          string class_name = "ThermalScatterCalculatorByNjoyInput";
          string func_name  = "set_pendf_new_data_obj()";
          ostringstream oss01;
          oss01 << opt_inelastic;
          string str_data01 = "Inelastic option : " + oss01.str();
          vector<string> err_com;
          err_com.push_back(str_data01);
          err_com.push_back("The inelastic scattering data(MF=7, MT=4) is exist in the ENDF data.");
          err_com.push_back("However, this input data does not use the ENDF data.");
          err_obj.output_caution(class_name, func_name, err_com);
        }
      }
    }

    //Read ENDF data file
    endf_file_parser.set_endf_file_reader(efr_obj);
    conv_obj.convert_endf_format_to_frendy(endf_file_parser, endf_data_obj);
    efr_obj.clear();
    endf_file_parser.clear();
  }

  //Copy endf_data and pendf_old_data to pendf_new_data
  for(int i=0; i<static_cast<int>(pendf_new_data_obj.size()); i++)
  {
    pendf_new_data_obj[i].clear();
  }
  pendf_new_data_obj.clear();

  //Get text data for material number = mat_pendf
  div_obj.set_file_name(pendf_name_old);
  pendf_old_file_text = div_obj.get_data_all(mat_pendf);
  label_data          = div_obj.get_label_data();
  endf_data_no        = static_cast<int>(pendf_old_file_text.size());
  pendf_new_data_obj.resize(endf_data_no);

  //Convert text data to NuclearDataObject
  for(int i=0; i<endf_data_no; i++)
  {
    pendf_old_file_parser.set_text(pendf_old_file_text[i]);
    clr_obj.clear_vec_array1_str(pendf_old_file_text[i]);
    conv_obj.convert_endf_format_to_frendy(pendf_old_file_parser, pendf_new_data_obj[i]);
    pendf_old_file_parser.clear();
  }
  div_obj.clear();
  pendf_old_file_text.clear();

  //Search nuclear data which the temperature is identical to input
  for(int i=endf_data_no-1; i>=0; i--)
  {
    Real8 temp_nucl = static_cast<Real8>(pendf_new_data_obj[i].get_general_data_obj().get_temp());
    Real8 temp_dif  = min_ene_dif;
    if( fabs(temp_nucl) > min_ene_dif)
    {
      temp_dif *= fabs(temp_nucl);
    }

    for(int j=0; j<temp_no_int; j++)
    {
      if( fabs(temp_nucl - temp[j]) < temp_dif )
      {
        //Add endf data to pendf_old_data
        temp_no_list[j] = i;
        pendf_new_data_obj[i].set_thermal_scat_data_obj(endf_data_obj.get_thermal_scat_data_obj());
      }
    }
  }
  endf_data_obj.clear();

  for(int i=0; i<temp_no_int; i++)
  {
    if( temp_no_list[i] < 0 )
    {
      string class_name = "ThermalScatterCalculatorByNjoyInput";
      string func_name  = "set_pendf_new_data_obj()";
      string str_data01 = "The input temperature is not found in the PENDF file.";
      string str_data02 = "PENDF file name : " + pendf_name_old;
      string str_data03 = "Temperature list in the PENDF file :";
      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      int j_max = static_cast<int>(pendf_old_file_text.size());
      for(int j=0; j<j_max; j++)
      {
        ostringstream oss01;
        oss01 << static_cast<Real8>(pendf_new_data_obj[j].get_general_data_obj().get_temp());
        string str_data04 = "  " + oss01.str();
        err_com.push_back(str_data04);
      }
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterCalculatorByNjoyInput::write_pendf_file()
{
  calc_thermal_scatter();

  vector<string> text;
  clr_obj.clear_vec_array1_str(text);

  //Open PENDF file
  ofstream fout;
  fout.open(pendf_name_new.c_str());

  if( fout.fail() )
  {
    string class_name = "ThermalScatterCalculatorByNjoyInput";
    string func_name  = "write_pendf_file()";

    string str_data = "  Output file name : " + pendf_name_new;

    vector<string> err_com;
    err_com.push_back("Output file can not be open.");
    err_com.push_back("Please check the file name, directory name or access authority.");
    err_com.push_back(str_data);

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //Write PENDF file in each temperature
  for(int i=0; i<endf_data_no; i++)
  {
    write_pendf_file_each_temp(i, text);
    for(int j=0; j<static_cast<int>(text.size()); j++)
    {
      fout << text[j] << endl;
    }
    clr_obj.clear_vec_array1_str(text);
  }

  //Write other PENDF fine in pendf_name_old
  EndfTapeDivider  div_obj;
  div_obj.set_file_name(pendf_name_old);
  vector<string> pendf_other = div_obj.get_data_without_specified_mat(mat_pendf);
  div_obj.clear();
  
  EndfFileWriter efw_obj;
  string tape_end   = efw_obj.write_tape_end();
  for(int i=0; i<static_cast<int>(pendf_other.size()); i++)
  {
    if( static_cast<int>(pendf_other[i].length()) > 66 &&
        pendf_other[i].find(tape_end.c_str(),0) == string::npos )
    {
      fout << pendf_other[i] << endl;
    }
  }

  //Write tape end
  fout << tape_end << endl;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterCalculatorByNjoyInput::write_pendf_file_each_temp(int ele_no, vector<string>& text)
{
  NuclearDataObject nucl_data_obj_mod = pendf_new_data_obj[ele_no];

  ThermalScatterDataContainer tsl_obj;
  tsl_obj.clear();

  nucl_data_obj_mod.set_thermal_scat_data_obj(tsl_obj);

  //Write PENDF file
  Endf6Writer wri_obj;
  wri_obj.set_nucl_data_obj(nucl_data_obj_mod);
  if( ele_no == 0 )
  {
    wri_obj.set_pendf_label(label_data);
    text = wri_obj.get_endf_text_data();
  }
  else
  {
    text = wri_obj.get_endf_text_data_without_label();
  }
  wri_obj.clear();
  nucl_data_obj_mod.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//Setter

void ThermalScatterCalculatorByNjoyInput::set_njoy_input_file_name(string str_data)
{
  set_njoy_input_file_name(str_data, 0);
}

void ThermalScatterCalculatorByNjoyInput::set_njoy_input_file_name(string str_data, int line_no)
{
  calc_flg = 0;
  input_file_name_njoy = str_data;
  start_line_no        = line_no;

  str_data.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//Getter

vector<NuclearDataObject> ThermalScatterCalculatorByNjoyInput::get_nucl_data_obj()
{
  calc_thermal_scatter();

  return pendf_new_data_obj;
}

vector<NuclearDataObject> ThermalScatterCalculatorByNjoyInput::get_nucl_data_obj_without_tsl()
{
  calc_thermal_scatter();

  vector<NuclearDataObject> pendf_new_data_obj_without_tsl = pendf_new_data_obj;

  ThermalScatterDataContainer tsl_obj;
  tsl_obj.clear();

  int i_max = static_cast<int>(pendf_new_data_obj.size());
  for(int i=0; i<i_max; i++)
  {
    pendf_new_data_obj_without_tsl[i].set_thermal_scat_data_obj(tsl_obj);
  }

  return pendf_new_data_obj_without_tsl;
}

string        ThermalScatterCalculatorByNjoyInput::get_njoy_input_file_name()
{
  return input_file_name_njoy;
}

string        ThermalScatterCalculatorByNjoyInput::get_endf_name()
{
  return endf_name;
}

string        ThermalScatterCalculatorByNjoyInput::get_pendf_name_old()
{
  return pendf_name_old;
}

string        ThermalScatterCalculatorByNjoyInput::get_pendf_name_new()
{
  return pendf_name_new;
}

Integer       ThermalScatterCalculatorByNjoyInput::get_mat_endf()
{
  return mat_endf;
}

Integer       ThermalScatterCalculatorByNjoyInput::get_mat_pendf()
{
  return mat_pendf;
}

Integer       ThermalScatterCalculatorByNjoyInput::get_bin_no()
{
  return bin_no;
}

Integer       ThermalScatterCalculatorByNjoyInput::get_temp_no()
{
  return temp_no;
}

Integer       ThermalScatterCalculatorByNjoyInput::get_opt_inelastic()
{
  return opt_inelastic;
}

Integer       ThermalScatterCalculatorByNjoyInput::get_opt_elastic()
{
  return opt_elastic;
}

Integer       ThermalScatterCalculatorByNjoyInput::get_atom_no()
{
  return atom_no;
}

Integer       ThermalScatterCalculatorByNjoyInput::get_mt_out()
{
  return mt_out;
}

Integer       ThermalScatterCalculatorByNjoyInput::get_opt_print()
{
  return opt_print;
}

vector<Real8> ThermalScatterCalculatorByNjoyInput::get_temp()
{
  return temp;
}

Real8         ThermalScatterCalculatorByNjoyInput::get_err()
{
  return err;
}

Real8         ThermalScatterCalculatorByNjoyInput::get_ene_max()
{
  return ene_max;
}

Real8         ThermalScatterCalculatorByNjoyInput::get_time_total()
{
  return time_total;
}

vector<Real8> ThermalScatterCalculatorByNjoyInput::get_time_each_temp()
{
  return time_each_temp;
}

