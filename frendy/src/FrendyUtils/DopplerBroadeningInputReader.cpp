#include "FrendyUtils/DopplerBroadeningInputReader.hpp"

using namespace frendy;

DopplerBroadeningInputReader::DopplerBroadeningInputReader(void)
{
  clear();
}

DopplerBroadeningInputReader::~DopplerBroadeningInputReader(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void DopplerBroadeningInputReader::clear()
{
  set_error_max_flg      = 0;
  set_error_integral_flg = 0;
  print_title_flg        = 0;

  print_set_data_flg = frendy_utils.get_print_set_data_flg_def();
  process_flg        = frendy_utils.get_process_flg_def();
  write_pendf_flg    = frendy_utils.get_write_pendf_flg_def();

  nucl_file_name     = frendy_utils.get_nucl_file_name_def();
  pendf_file_name    = frendy_utils.get_pendf_file_name_def();
  pendf_label_data   = frendy_utils.get_pendf_label_data_def();
  comment_data       = frendy_utils.get_comment_data_def();

  temp               = frendy_utils.get_temp_def();
  error              = frendy_utils.get_error_def();
  error_max          = frendy_utils.get_error_max_def();
  error_integral     = frendy_utils.get_error_integral_def();
  max_broadening_ene = frendy_utils.get_max_broadening_ene_def();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void DopplerBroadeningInputReader::read_input_data_from_input_file(string file_name)
{
  FileCommentRemover file_handling_obj;
  vector<vector<string> > input_data = file_handling_obj.remove_comment_and_devide_text_data(file_name);

  read_input_data(input_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<int> DopplerBroadeningInputReader::read_input_data(vector<vector<string> >& input_data)
{
  int i_max = static_cast<int>(input_data.size());
  int i_sta = 0;
  if( i_max%2 == 1 ) //include calculation mode at input_data[0][0]
  {
    i_sta = 1;
  }

  int data_no = (i_max - i_sta) / 2;
  vector<int> inp_check_vec;
  inp_check_vec.resize(data_no);

  int ele_no = 0;
  for(int i=i_sta; i<i_max; i+=2)
  {
    inp_check_vec[ele_no] = read_input_data(input_data[i], input_data[i+1]);
    ele_no++;
  }

  return inp_check_vec;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int DopplerBroadeningInputReader::read_input_data(vector<string>& input_type, vector<string>& input_data)
{
  if( static_cast<int>(input_type.size()) != 1 )
  {
    string class_name = "DopplerBroadeningInputReader";
    string func_name  = "read_input_data(vector<string>& input_type, vector<string>& input_data)";
    frendy_utils.error_input_type_size(class_name, func_name, input_type);
  }

  return read_input_data(input_type[0], input_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int DopplerBroadeningInputReader::read_input_data(string& input_type, vector<string>& input_data)
{
  if( static_cast<int>(input_data.size()) == 0 )
  {
    string class_name = "DopplerBroadeningInputReader";
    string func_name  = "read_input_data(string& input_type, vector<string>& input_data)";
    frendy_utils.error_input_data_size_is_zero(class_name, func_name, input_data);
  }

  if( print_set_data_flg == frendy_utils.print_set_data && print_title_flg == 0 )
  {
    print_title_flg = 1;
    cout << "=== Read input data for DopplerBroadening ===" << endl;
  }

  //Modify capital letter to lower-case letter
  string input_type_mod = input_type;
  transform(input_type_mod.begin(), input_type_mod.end(), input_type_mod.begin(), ::tolower);
  replace(input_type_mod.begin(), input_type_mod.end(), '-', '_');

  int inp_check = 1;
  if( input_type_mod == "nucl_file_name" || input_type_mod == "nucl_name" ||
      input_type_mod == "endf_file_name" || input_type_mod == "endf_name" )
  {
    set_nucl_file_name(input_data);
  }
  else if( input_type_mod == "pendf_label_data" || input_type_mod == "endf_label_data" )
  {
    set_pendf_label_data(input_data);
  }
  else if( input_type_mod == "comment_data" )
  {
    set_comment_data(input_data);
  }
  else if( input_type_mod == "temp" || input_type_mod == "temperature" )
  {
    set_temp(input_data);
  }
  else if( input_type_mod == "error" )
  {
    set_error(input_data);
  }
  else if( input_type_mod == "error_max" )
  {
    set_error_max(input_data);
  }
  else if( input_type_mod == "error_integral" )
  {
    set_error_integral(input_data);
  }
  else if( input_type_mod == "max_broadening_ene" )
  {
    set_max_broadening_ene(input_data);
  }
  else if( input_type_mod == "print_set_data_dop" ||
           input_type_mod == "print_set_data_doppler_broadening" )
  {
    set_print_set_data_flg(input_data);
  }
  else if( input_type_mod == "process_dop" ||
           input_type_mod == "process_doppler_broadening" )
  {
    set_process_flg(input_data);
  }
  else if( input_type_mod == "write_pendf_dop" ||
           input_type_mod == "write_pendf_doppler_broadening" )
  {
    set_write_pendf_flg(input_data);
  }
  else if( input_type_mod == "pendf_file_name_dop" ||
           input_type_mod == "pendf_file_name_doppler_broadening" )
  {
    set_pendf_file_name(input_data);
  }
  else
  {
    inp_check = 0;
  }

  return inp_check;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void DopplerBroadeningInputReader::set_nucl_file_name(string input_data)
{
  vector<string> str_vec;
  str_vec.resize(1);

  str_vec[0] = input_data;

  set_nucl_file_name(str_vec);
}

void DopplerBroadeningInputReader::set_nucl_file_name(vector<string> input_data)
{
  nucl_file_name = input_data;

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    for(int i=0; i<static_cast<int>(nucl_file_name.size()); i++)
    {
      if( i==0 )
      {
        cout << "  nucl_file_name          : " << input_data[i] << endl;
      }
      else
      {
        cout << "                          : " << input_data[i] << endl;
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void DopplerBroadeningInputReader::set_pendf_label_data(string input_data)
{
  vector<string> str_vec;
  str_vec.resize(1);

  str_vec[0] = input_data;

  set_pendf_label_data(str_vec);
}

void DopplerBroadeningInputReader::set_pendf_label_data(vector<string> input_data)
{
  pendf_label_data = input_data;

  if( print_set_data_flg == frendy_utils.print_set_data && write_pendf_flg == frendy_utils.write_pendf )
  {
    for(int i=0; i<static_cast<int>(pendf_label_data.size()); i++)
    {
      if( i==0 )
      {
        cout << "  pendf_label_data        : " << input_data[i] << endl;
      }
      else
      {
        cout << "                          : " << input_data[i] << endl;
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void DopplerBroadeningInputReader::set_comment_data(vector<string> input_data)
{
  comment_data = input_data;

  if( print_set_data_flg == frendy_utils.print_set_data && write_pendf_flg == frendy_utils.write_pendf )
  {
    cout << "  comment_data" << endl;
    int i_max = static_cast<int>(input_data.size());
    for(int i=0; i<i_max; i++)
    {
      cout << "    " << i+1 << " / " << i_max << " : " << input_data[i] << endl;
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void DopplerBroadeningInputReader::set_temp(vector<string>& input_data)
{
  if( static_cast<int>(input_data.size()) > 1 )
  {
    string class_name = "DopplerBroadeningInputReader";
    string func_name  = "set_temp(vector<string>& input_data)";
    frendy_utils.error_input_data_size_is_larger_than_one(class_name, func_name, input_data);
  }

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  temp [K]                : " << input_data[0] << endl;
  }

  str_obj.string_check(input_data[0]);
  temp = numeric_string_cast<Real>(input_data[0]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void DopplerBroadeningInputReader::set_error(vector<string>& input_data)
{
  if( static_cast<int>(input_data.size()) > 1 )
  {
    string class_name = "DopplerBroadeningInputReader";
    string func_name  = "set_error(vector<string>& input_data)";
    frendy_utils.error_input_data_size_is_larger_than_one(class_name, func_name, input_data);
  }

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  error                   : " << input_data[0] << endl;
  }

  str_obj.string_check(input_data[0]);
  error = numeric_string_cast<Real>(input_data[0]);

  if( set_error_max_flg == 0 )
  {
    error_max = error * 10.0;

    if( print_set_data_flg == frendy_utils.print_set_data )
    {
      cout << "  error_max               : " << error_max << " (automatically modified by error value)" << endl;
    }
  }

  if( set_error_integral_flg == 0 )
  {
    error_integral = error / 2.0E+4;

    if( print_set_data_flg == frendy_utils.print_set_data )
    {
      cout << "  error_integral          : " << error_integral << " (automatically modified by error value)" << endl;
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void DopplerBroadeningInputReader::set_error_max(vector<string>& input_data)
{
  set_error_max_flg = 1;

  if( static_cast<int>(input_data.size()) > 1 )
  {
    string class_name = "DopplerBroadeningInputReader";
    string func_name  = "set_error_max(vector<string>& input_data)";
    frendy_utils.error_input_data_size_is_larger_than_one(class_name, func_name, input_data);
  }

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  error_max               : " << input_data[0] << endl;
  }

  str_obj.string_check(input_data[0]);
  error_max = numeric_string_cast<Real>(input_data[0]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void DopplerBroadeningInputReader::set_error_integral(vector<string>& input_data)
{
  set_error_integral_flg = 1;

  if( static_cast<int>(input_data.size()) > 1 )
  {
    string class_name = "DopplerBroadeningInputReader";
    string func_name  = "set_error_integral(vector<string>& input_data)";
    frendy_utils.error_input_data_size_is_larger_than_one(class_name, func_name, input_data);
  }

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  error_integral          : " << input_data[0] << endl;
  }

  str_obj.string_check(input_data[0]);
  error_integral = numeric_string_cast<Real>(input_data[0]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void DopplerBroadeningInputReader::set_max_broadening_ene(vector<string>& input_data)
{
  if( static_cast<int>(input_data.size()) > 1 )
  {
    string class_name = "DopplerBroadeningInputReader";
    string func_name  = "set_max_broadening_ene(vector<string>& input_data)";
    frendy_utils.error_input_data_size_is_larger_than_one(class_name, func_name, input_data);
  }

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  max_broadening_ene [eV] : " << input_data[0] << endl;
  }

  str_obj.string_check(input_data[0]);
  max_broadening_ene = numeric_string_cast<Real>(input_data[0]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void DopplerBroadeningInputReader::set_temp(Real real_data)
{
  temp = real_data;
}

void DopplerBroadeningInputReader::set_error(Real real_data)
{
  error = real_data;
}

void DopplerBroadeningInputReader::set_error_max(Real real_data)
{
  error_max = real_data;
}

void DopplerBroadeningInputReader::set_error_integral(Real real_data)
{
  error_integral = real_data;
}

void DopplerBroadeningInputReader::set_max_broadening_ene(Real real_data)
{
  max_broadening_ene = real_data;
}


////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> DopplerBroadeningInputReader::get_nucl_file_name()
{
  return nucl_file_name;
}

vector<string> DopplerBroadeningInputReader::get_pendf_file_name()
{
  int i_max = static_cast<int>(nucl_file_name.size());
  if( i_max > 0 )
  {
    if( static_cast<int>(pendf_file_name.size()) != i_max )
    {
      pendf_file_name.resize(i_max);
    }
  }

  return pendf_file_name;
}

vector<string> DopplerBroadeningInputReader::get_pendf_label_data()
{
  int i_max = static_cast<int>(nucl_file_name.size());
  if( i_max > 0 )
  {
    if( static_cast<int>(pendf_label_data.size()) != i_max )
    {
      pendf_label_data.resize(i_max);
    }
  }

  return pendf_label_data;
}

vector<string> DopplerBroadeningInputReader::get_comment_data()
{
  return comment_data;
}

Real DopplerBroadeningInputReader::get_temp()
{
  return temp;
}

Real DopplerBroadeningInputReader::get_error()
{
  return error;
}

Real DopplerBroadeningInputReader::get_error_max()
{
  return error_max;
}

Real DopplerBroadeningInputReader::get_error_integral()
{
  return error_integral;
}

Real DopplerBroadeningInputReader::get_max_broadening_ene()
{
  return max_broadening_ene;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void DopplerBroadeningInputReader::set_print_set_data_flg(vector<string>& input_data)
{
  string class_name = "DopplerBroadeningInputReader";
  string func_name  = "set_print_set_data_flg(vector<string>& input_data)";

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  print_set_data_flg      : " << input_data[0] << endl;
  }

  print_set_data_flg = frendy_utils.read_print_set_data_flg(class_name, func_name, input_data);
}

void DopplerBroadeningInputReader::set_process_flg(vector<string>& input_data)
{
  string class_name = "DopplerBroadeningInputReader";
  string func_name  = "set_process_flg(vector<string>& input_data)";

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  process_flg             : " << input_data[0] << endl;
  }

  process_flg = frendy_utils.read_process_flg(class_name, func_name, input_data);
}

void DopplerBroadeningInputReader::set_write_pendf_flg(vector<string>& input_data)
{
  string class_name = "DopplerBroadeningInputReader";
  string func_name  = "set_write_pendf_flg(vector<string>& input_data)";

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  write_pendf_flg         : " << input_data[0] << endl;
  }

  write_pendf_flg = frendy_utils.read_write_pendf_flg(class_name, func_name, pendf_file_name, input_data);
}

void DopplerBroadeningInputReader::set_pendf_file_name(string input_data)
{
  vector<string> str_vec;
  str_vec.resize(1);
  str_vec[0] = input_data;

  set_pendf_file_name(str_vec);
}

void DopplerBroadeningInputReader::set_pendf_file_name(vector<string> input_data)
{
  set_write_pendf_flg(frendy_utils.write_pendf, input_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void DopplerBroadeningInputReader::set_print_set_data_flg(int int_val)
{
  frendy_utils.check_print_set_data_flg("DopplerBroadeningInputReader", int_val);

  print_set_data_flg = int_val;
}

void DopplerBroadeningInputReader::set_process_flg(int int_val)
{
  frendy_utils.check_process_flg("DopplerBroadeningInputReader", int_val);

  process_flg = int_val;
}

void DopplerBroadeningInputReader::set_write_pendf_flg(int int_val)
{
  frendy_utils.check_write_pendf_flg_no_str_data("DopplerBroadeningInputReader", pendf_file_name, int_val);

  write_pendf_flg = int_val;
}

void DopplerBroadeningInputReader::set_write_pendf_flg(int int_val, string file_name)
{
  vector<string> str_vec;
  str_vec.resize(1);
  str_vec[0] = file_name;

  set_write_pendf_flg(int_val, str_vec);
}

void DopplerBroadeningInputReader::set_write_pendf_flg(int int_val, vector<string> file_name)
{
  frendy_utils.check_write_pendf_flg("DopplerBroadeningInputReader", int_val);

  write_pendf_flg = int_val;
  pendf_file_name = file_name;

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    frendy_utils.write_pendf_data(pendf_file_name, pendf_label_data, comment_data, write_pendf_flg);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int DopplerBroadeningInputReader::get_print_set_data_flg()
{
  return print_set_data_flg;
}

int DopplerBroadeningInputReader::get_process_flg()
{
  return process_flg;
}

int DopplerBroadeningInputReader::get_write_pendf_flg()
{
  return write_pendf_flg;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

