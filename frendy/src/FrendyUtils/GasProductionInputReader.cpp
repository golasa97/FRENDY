#include "FrendyUtils/GasProductionInputReader.hpp"

using namespace frendy;

GasProductionInputReader::GasProductionInputReader(void)
{
  clear();
}

GasProductionInputReader::~GasProductionInputReader(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GasProductionInputReader::clear()
{
  print_title_flg    = 0;

  print_set_data_flg = frendy_utils.get_print_set_data_flg_def();
  process_flg        = frendy_utils.get_process_flg_def();
  write_pendf_flg    = frendy_utils.get_write_pendf_flg_def();

  nucl_file_name     = frendy_utils.get_nucl_file_name_def();
  pendf_file_name    = frendy_utils.get_pendf_file_name_def();
  pendf_label_data   = frendy_utils.get_pendf_label_data_def();
  comment_data       = frendy_utils.get_comment_data_def();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GasProductionInputReader::read_input_data_from_input_file(string file_name)
{
  FileCommentRemover file_handling_obj;
  vector<vector<string> > input_data = file_handling_obj.remove_comment_and_devide_text_data(file_name);

  read_input_data(input_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<int> GasProductionInputReader::read_input_data(vector<vector<string> >& input_data)
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

int GasProductionInputReader::read_input_data(vector<string>& input_type, vector<string>& input_data)
{
  if( static_cast<int>(input_type.size()) != 1 )
  {
    string class_name = "GasProductionInputReader";
    string func_name  = "read_input_data(vector<string>& input_type, vector<string>& input_data)";
    frendy_utils.error_input_type_size(class_name, func_name, input_type);
  }

  return read_input_data(input_type[0], input_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int GasProductionInputReader::read_input_data(string& input_type, vector<string>& input_data)
{
  if( static_cast<int>(input_data.size()) == 0 )
  {
    string class_name = "GasProductionInputReader";
    string func_name  = "read_input_data(string& input_type, vector<string>& input_data)";
    frendy_utils.error_input_data_size_is_zero(class_name, func_name, input_data);
  }

  if( print_set_data_flg == frendy_utils.print_set_data && print_title_flg == 0 )
  {
    print_title_flg = 1;
    cout << "=== Read input data for GasProduction ===" << endl;
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
  else if( input_type_mod == "print_set_data_gas"                  ||
           input_type_mod == "print_set_data_gas_xs"               ||
           input_type_mod == "print_set_data_gas_prod_xs"          ||
           input_type_mod == "print_set_data_gas_production"       ||
           input_type_mod == "print_set_data_gas_production_xs"    ||
           input_type_mod == "print_set_data_gas_production_cross_section" )
  {
    set_print_set_data_flg(input_data);
  }
  else if( input_type_mod == "process_gas"               ||
           input_type_mod == "process_gas_xs"            ||
           input_type_mod == "process_gas_prod_xs"       ||
           input_type_mod == "process_gas_production"    ||
           input_type_mod == "process_gas_production_xs" ||
           input_type_mod == "process_gas_production_cross_section" )
  {
    set_process_flg(input_data);
  }
  else if( input_type_mod == "write_pendf_gas"               ||
           input_type_mod == "write_pendf_gas_xs"            ||
           input_type_mod == "write_pendf_gas_prod_xs"       ||
           input_type_mod == "write_pendf_gas_production"    ||
           input_type_mod == "write_pendf_gas_production_xs" ||
           input_type_mod == "write_pendf_gas_production_cross_section" )
  {
    set_write_pendf_flg(input_data);
  }
  else if( input_type_mod == "pendf_file_name_gas"               ||
           input_type_mod == "pendf_file_name_gas_xs"            ||
           input_type_mod == "pendf_file_name_gas_prod_xs"       ||
           input_type_mod == "pendf_file_name_gas_production"    ||
           input_type_mod == "pendf_file_name_gas_production_xs" ||
           input_type_mod == "pendf_file_name_gas_production_cross_section" )
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

void GasProductionInputReader::set_nucl_file_name(string input_data)
{
  vector<string> str_vec;
  str_vec.resize(1);

  str_vec[0] = input_data;

  set_nucl_file_name(str_vec);
}

void GasProductionInputReader::set_nucl_file_name(vector<string> input_data)
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

void GasProductionInputReader::set_pendf_label_data(string input_data)
{
  vector<string> str_vec;
  str_vec.resize(1);

  str_vec[0] = input_data;

  set_pendf_label_data(str_vec);
}

void GasProductionInputReader::set_pendf_label_data(vector<string> input_data)
{
  pendf_label_data = input_data;

  if( print_set_data_flg == frendy_utils.print_set_data && write_pendf_flg == frendy_utils.write_pendf )
  {
    for(int i=0; i<static_cast<int>(pendf_label_data.size()); i++)
    {
      if( i==0 )
      {
        cout << "  pendf_label_data   : " << input_data[i] << endl;
      }
      else
      {
        cout << "                     : " << input_data[i] << endl;
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GasProductionInputReader::set_comment_data(vector<string> input_data)
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

vector<string> GasProductionInputReader::get_nucl_file_name()
{
  return nucl_file_name;
}

vector<string> GasProductionInputReader::get_pendf_file_name()
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

vector<string> GasProductionInputReader::get_pendf_label_data()
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

vector<string> GasProductionInputReader::get_comment_data()
{
  return comment_data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GasProductionInputReader::set_print_set_data_flg(vector<string>& input_data)
{
  string class_name = "GasProductionInputReader";
  string func_name  = "set_print_set_data_flg(vector<string>& input_data)";

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  print_set_data_flg      : " << input_data[0] << endl;
  }

  print_set_data_flg = frendy_utils.read_print_set_data_flg(class_name, func_name, input_data);
}

void GasProductionInputReader::set_process_flg(vector<string>& input_data)
{
  string class_name = "GasProductionInputReader";
  string func_name  = "set_process_flg(vector<string>& input_data)";

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  process_flg             : " << input_data[0] << endl;
  }

  process_flg = frendy_utils.read_process_flg(class_name, func_name, input_data);
}

void GasProductionInputReader::set_write_pendf_flg(vector<string>& input_data)
{
  string class_name = "GasProductionInputReader";
  string func_name  = "set_write_pendf_flg(vector<string>& input_data)";

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  write_pendf_flg         : " << input_data[0] << endl;
  }

  write_pendf_flg = frendy_utils.read_write_pendf_flg(class_name, func_name, pendf_file_name, input_data);
}

void GasProductionInputReader::set_pendf_file_name(string input_data)
{
  vector<string> str_vec;
  str_vec.resize(1);
  str_vec[0] = input_data;

  set_pendf_file_name(str_vec);
}

void GasProductionInputReader::set_pendf_file_name(vector<string> input_data)
{
  set_write_pendf_flg(frendy_utils.write_pendf, input_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GasProductionInputReader::set_print_set_data_flg(int int_val)
{
  frendy_utils.check_print_set_data_flg("GasProductionInputReader", int_val);

  print_set_data_flg = int_val;
}

void GasProductionInputReader::set_process_flg(int int_val)
{
  frendy_utils.check_process_flg("GasProductionInputReader", int_val);

  process_flg = int_val;
}

void GasProductionInputReader::set_write_pendf_flg(int int_val)
{
  frendy_utils.check_write_pendf_flg_no_str_data("GasProductionInputReader", pendf_file_name, int_val);

  write_pendf_flg = int_val;
}

void GasProductionInputReader::set_write_pendf_flg(int int_val, vector<string> file_name)
{
  frendy_utils.check_write_pendf_flg("GasProductionInputReader", int_val);

  write_pendf_flg = int_val;
  pendf_file_name = file_name;

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    frendy_utils.write_pendf_data(pendf_file_name, pendf_label_data, comment_data, write_pendf_flg);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int GasProductionInputReader::get_print_set_data_flg()
{
  return print_set_data_flg;
}

int GasProductionInputReader::get_process_flg()
{
  return process_flg;
}

int GasProductionInputReader::get_write_pendf_flg()
{
  return write_pendf_flg;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

