#include "FrendyUtils/ThermalScatterInputReader.hpp"

using namespace frendy;

ThermalScatterInputReader::ThermalScatterInputReader(void)
{
  clear();
}

ThermalScatterInputReader::~ThermalScatterInputReader(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterInputReader::clear()
{
  print_title_flg    = 0;

  print_set_data_flg = frendy_utils.get_print_set_data_flg_def();
  process_flg        = frendy_utils.get_process_flg_def();
  write_pendf_flg    = frendy_utils.get_write_pendf_flg_def();

  nucl_file_name     = frendy_utils.get_nucl_file_name_def();
  pendf_file_name    = frendy_utils.get_pendf_file_name_def();
  pendf_label_data   = frendy_utils.get_pendf_label_data_def();
  comment_data       = frendy_utils.get_comment_data_def();

  nucl_file_name_tsl            = frendy_utils.get_nucl_file_name_tsl_def();
  equi_probable_angle_no        = frendy_utils.get_equi_probable_angle_no_tsl_def();
  //inelastic_distribution_format = frendy_utils.get_inelastic_distribution_format_def();
  principal_atom_no             = frendy_utils.get_principal_atom_no_def();
  inelastic_reaction_type_no    = frendy_utils.get_inelastic_reaction_type_no_def();
  max_thermal_ene               = frendy_utils.get_max_thermal_ene_in_def();
  error                         = frendy_utils.get_error_def();

  set_max_thermal_ene_flg       = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterInputReader::read_input_data_from_input_file(string file_name)
{
  FileCommentRemover file_handling_obj;
  vector<vector<string> > input_data = file_handling_obj.remove_comment_and_devide_text_data(file_name);

  read_input_data(input_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<int> ThermalScatterInputReader::read_input_data(vector<vector<string> >& input_data)
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

int ThermalScatterInputReader::read_input_data(vector<string>& input_type, vector<string>& input_data)
{
  if( static_cast<int>(input_type.size()) != 1 )
  {
    string class_name = "ThermalScatterInputReader";
    string func_name  = "read_input_data(vector<string>& input_type, vector<string>& input_data)";
    frendy_utils.error_input_type_size(class_name, func_name, input_type);
  }

  return read_input_data(input_type[0], input_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int ThermalScatterInputReader::read_input_data(string& input_type, vector<string>& input_data)
{
  if( static_cast<int>(input_data.size()) == 0 )
  {
    string class_name = "ThermalScatterInputReader";
    string func_name  = "read_input_data(string& input_type, vector<string>& input_data)";
    frendy_utils.error_input_data_size_is_zero(class_name, func_name, input_data);
  }

  if( print_set_data_flg == frendy_utils.print_set_data && print_title_flg == 0 )
  {
    print_title_flg = 1;
    cout << "=== Read input data for ThermalScatter ===" << endl;
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
  else if( input_type_mod == "nucl_file_name_tsl" || input_type_mod == "nucl_name_tsl" ||
           input_type_mod == "endf_file_name_tsl" || input_type_mod == "endf_name_tsl" )
  {
    set_nucl_file_name_tsl(input_data);
  }
  else if( input_type_mod == "equi_probable_angle_no" )
  {
    set_equi_probable_angle_no(input_data);
  }
  //else if( input_type_mod == "inelastic_distribution_format" )
  //{
  //  set_inelastic_distribution_format(input_data);
  //}
  else if( input_type_mod == "principal_atom_no" )
  {
    set_principal_atom_no(input_data);
  }
  else if( input_type_mod == "inelastic_reaction_type_no" )
  {
    set_inelastic_reaction_type_no(input_data);
  }
  else if( input_type_mod == "max_thermal_ene" )
  {
    set_max_thermal_ene(input_data);
  }
  else if( input_type_mod == "error" )
  {
    set_error(input_data);
  }
  else if( input_type_mod == "print_set_data_tsl"                ||
           input_type_mod == "print_set_data_thermal_scattering" ||
           input_type_mod == "print_set_data_thermal_scattering_law" )
  {
    set_print_set_data_flg(input_data);
  }
  else if( input_type_mod == "process_tsl"                ||
           input_type_mod == "process_thermal_scattering" ||
           input_type_mod == "process_thermal_scattering_law" )
  {
    set_process_flg(input_data);
  }
  else if( input_type_mod == "write_pendf_tsl"                ||
           input_type_mod == "write_pendf_thermal_scattering" ||
           input_type_mod == "write_pendf_thermal_scattering_law" )
  {
    set_write_pendf_flg(input_data);
  }
  else if( input_type_mod == "pendf_file_name_tsl"                ||
           input_type_mod == "pendf_file_name_thermal_scattering" ||
           input_type_mod == "pendf_file_name_thermal_scattering_law" )
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

void ThermalScatterInputReader::set_nucl_file_name(string input_data)
{
  vector<string> str_vec;
  str_vec.resize(1);

  str_vec[0] = input_data;

  set_nucl_file_name(str_vec);
}

void ThermalScatterInputReader::set_nucl_file_name(vector<string> input_data)
{
  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    for(int i=0; i<static_cast<int>(input_data.size()); i++)
    {
      if( i==0 )
      {
        cout << "  nucl_file_name                : " << input_data[i] << endl;
      }
      else
      {
        cout << "                                : " << input_data[i] << endl;
      }
    }
  }

  nucl_file_name = input_data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterInputReader::set_pendf_label_data(string input_data)
{
  vector<string> str_vec;
  str_vec.resize(1);

  str_vec[0] = input_data;

  set_pendf_label_data(str_vec);
}

void ThermalScatterInputReader::set_pendf_label_data(vector<string> input_data)
{
  if( print_set_data_flg == frendy_utils.print_set_data && write_pendf_flg == frendy_utils.write_pendf )
  {
    for(int i=0; i<static_cast<int>(input_data.size()); i++)
    {
      if( i==0 )
      {
        cout << "  pendf_label_data              : " << input_data[i] << endl;
      }
      else
      {
        cout << "                                : " << input_data[i] << endl;
      }
    }
  }

  pendf_label_data = input_data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterInputReader::set_comment_data(vector<string> input_data)
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

void ThermalScatterInputReader::set_nucl_file_name_tsl(vector<string> input_data)
{
  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  nucl_file_name_tsl" << endl;
    for(int i=0; i<static_cast<int>(input_data.size()); i++)
    {
      cout << "     " << input_data[i] << endl;
    }
  }

  nucl_file_name_tsl = input_data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterInputReader::set_equi_probable_angle_no(vector<string>& input_data)
{
  if( static_cast<int>(input_data.size()) > 1 )
  {
    string class_name = "ThermalScatterInputReader";
    string func_name  = "set_equi_probable_angle_no(vector<string>& input_data)";
    frendy_utils.error_input_data_size_is_larger_than_one(class_name, func_name, input_data);
  }

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  equi_probable_angle_no        : " << input_data[0] << endl;
  }

  str_obj.string_check(input_data[0]);
  equi_probable_angle_no = numeric_string_cast<Integer>(input_data[0]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//void ThermalScatterInputReader::set_inelastic_distribution_format(vector<string>& input_data)
//{
//  if( static_cast<int>(input_data.size()) > 1 )
//  {
//    string class_name = "ThermalScatterInputReader";
//    string func_name  = "set_inelastic_distribution_format(vector<string>& input_data)";
//    frendy_utils.error_input_data_size_is_larger_than_one(class_name, func_name, input_data);
//  }
//
//  if( print_set_data_flg == frendy_utils.print_set_data )
//  {
//    cout << "  inelastic_distribution_format : " << input_data[0] << endl;
//  }
//
//  str_obj.string_check(input_data[0]);
//  inelastic_distribution_format = numeric_string_cast<Integer>(input_data[0]);
//}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterInputReader::set_principal_atom_no(vector<string>& input_data)
{
  if( static_cast<int>(input_data.size()) > 1 )
  {
    string class_name = "ThermalScatterInputReader";
    string func_name  = "set_principal_atom_no(vector<string>& input_data)";
    frendy_utils.error_input_data_size_is_larger_than_one(class_name, func_name, input_data);
  }

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  principal_atom_no             : " << input_data[0] << endl;
  }

  str_obj.string_check(input_data[0]);
  principal_atom_no = numeric_string_cast<Integer>(input_data[0]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterInputReader::set_inelastic_reaction_type_no(vector<string>& input_data)
{
  if( static_cast<int>(input_data.size()) > 1 )
  {
    string class_name = "ThermalScatterInputReader";
    string func_name  = "set_inelastic_reaction_type_no(vector<string>& input_data)";
    frendy_utils.error_input_data_size_is_larger_than_one(class_name, func_name, input_data);
  }

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  inelastic_reaction_type_no    : " << input_data[0] << endl;
  }

  str_obj.string_check(input_data[0]);
  inelastic_reaction_type_no = numeric_string_cast<Integer>(input_data[0]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterInputReader::set_max_thermal_ene(vector<string>& input_data)
{
  if( static_cast<int>(input_data.size()) > 1 )
  {
    string class_name = "ThermalScatterInputReader";
    string func_name  = "set_max_thermal_ene(vector<string>& input_data)";
    frendy_utils.error_input_data_size_is_larger_than_one(class_name, func_name, input_data);
  }

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  max_thermal_ene [eV]          : " << input_data[0] << endl;
  }

  str_obj.string_check(input_data[0]);
  max_thermal_ene = numeric_string_cast<Real>(input_data[0]);

  set_max_thermal_ene_flg = 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterInputReader::set_error(vector<string>& input_data)
{
  if( static_cast<int>(input_data.size()) > 1 )
  {
    string class_name = "ThermalScatterInputReader";
    string func_name  = "set_error(vector<string>& input_data)";
    frendy_utils.error_input_data_size_is_larger_than_one(class_name, func_name, input_data);
  }

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  error                         : " << input_data[0] << endl;
  }

  str_obj.string_check(input_data[0]);
  error = numeric_string_cast<Real>(input_data[0]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterInputReader::set_equi_probable_angle_no(Integer int_data)
{
  equi_probable_angle_no = int_data;
}

//void ThermalScatterInputReader::set_inelastic_distribution_format(Integer int_data)
//{
//  inelastic_distribution_format = int_data;
//}

void ThermalScatterInputReader::set_principal_atom_no(Integer int_data)
{
  principal_atom_no = int_data;
}

void ThermalScatterInputReader::set_inelastic_reaction_type_no(Integer int_data)
{
  inelastic_reaction_type_no = int_data;
}

void ThermalScatterInputReader::set_max_thermal_ene(Real real_data)
{
  max_thermal_ene = real_data;
}

void ThermalScatterInputReader::set_error(Real real_data)
{
  error = real_data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> ThermalScatterInputReader::get_nucl_file_name()
{
  return nucl_file_name;
}

vector<string> ThermalScatterInputReader::get_pendf_file_name()
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

vector<string> ThermalScatterInputReader::get_pendf_label_data()
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

vector<string> ThermalScatterInputReader::get_comment_data()
{
  return comment_data;
}

vector<string> ThermalScatterInputReader::get_nucl_file_name_tsl()
{
  return nucl_file_name_tsl;
}

Integer ThermalScatterInputReader::get_equi_probable_angle_no()
{
  return equi_probable_angle_no;
}

//Integer ThermalScatterInputReader::get_inelastic_distribution_format()
//{
//  return inelastic_distribution_format;
//}

Integer ThermalScatterInputReader::get_principal_atom_no()
{
  return principal_atom_no;
}

Integer ThermalScatterInputReader::get_inelastic_reaction_type_no()
{
  return inelastic_reaction_type_no;
}

Real ThermalScatterInputReader::get_max_thermal_ene()
{
  return max_thermal_ene;
}

Real ThermalScatterInputReader::get_error()
{
  return error;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterInputReader::set_print_set_data_flg(vector<string>& input_data)
{
  string class_name = "ThermalScatterInputReader";
  string func_name  = "set_print_set_data_flg(vector<string>& input_data)";

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  print_set_data_flg            : " << input_data[0] << endl;
  }

  print_set_data_flg = frendy_utils.read_print_set_data_flg(class_name, func_name, input_data);
}

void ThermalScatterInputReader::set_process_flg(vector<string>& input_data)
{
  string class_name = "ThermalScatterInputReader";
  string func_name  = "set_process_flg(vector<string>& input_data)";

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  process_flg                   : " << input_data[0] << endl;
  }

  process_flg = frendy_utils.read_process_flg(class_name, func_name, input_data);
}

void ThermalScatterInputReader::set_write_pendf_flg(vector<string>& input_data)
{
  string class_name = "ThermalScatterInputReader";
  string func_name  = "set_write_pendf_flg(vector<string>& input_data)";

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  write_pendf_flg               : " << input_data[0] << endl;
  }

  write_pendf_flg = frendy_utils.read_write_pendf_flg(class_name, func_name, pendf_file_name, input_data);
}

void ThermalScatterInputReader::set_pendf_file_name(string input_data)
{
  vector<string> str_vec;
  str_vec.resize(1);
  str_vec[0] = input_data;

  set_pendf_file_name(str_vec);
}

void ThermalScatterInputReader::set_pendf_file_name(vector<string> input_data)
{
  if( static_cast<int>(input_data.size()) > 1 )
  {
    string class_name = "ThermalScatterInputReader";
    string func_name  = "set_pendf_file_name(vector<string>& input_data)";
    frendy_utils.error_input_data_size_is_larger_than_one(class_name, func_name, input_data);
  }

  set_write_pendf_flg(frendy_utils.write_pendf, input_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterInputReader::set_print_set_data_flg(int int_val)
{
  frendy_utils.check_print_set_data_flg("ThermalScatterInputReader", int_val);

  print_set_data_flg = int_val;
}

void ThermalScatterInputReader::set_process_flg(int int_val)
{
  frendy_utils.check_process_flg("ThermalScatterInputReader", int_val);

  process_flg = int_val;
}

void ThermalScatterInputReader::set_write_pendf_flg(int int_val)
{
  frendy_utils.check_write_pendf_flg_no_str_data("ThermalScatterInputReader", pendf_file_name, int_val);

  write_pendf_flg = int_val;
}

void ThermalScatterInputReader::set_write_pendf_flg(int int_val, string file_name)
{
  vector<string> str_vec;
  str_vec.resize(1);
  str_vec[0] = file_name;

  set_write_pendf_flg(int_val, str_vec);
}


void ThermalScatterInputReader::set_write_pendf_flg(int int_val, vector<string> file_name)
{
  frendy_utils.check_write_pendf_flg("ThermalScatterInputReader", int_val);

  write_pendf_flg = int_val;
  pendf_file_name = file_name;

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    frendy_utils.write_pendf_data(pendf_file_name, pendf_label_data, comment_data, write_pendf_flg);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int ThermalScatterInputReader::get_print_set_data_flg()
{
  return print_set_data_flg;
}

int ThermalScatterInputReader::get_process_flg()
{
  return process_flg;
}

int ThermalScatterInputReader::get_write_pendf_flg()
{
  return write_pendf_flg;
}

int ThermalScatterInputReader::get_set_max_thermal_ene_flg()
{
  return set_max_thermal_ene_flg;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

