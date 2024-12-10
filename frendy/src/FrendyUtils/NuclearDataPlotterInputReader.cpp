#include "FrendyUtils/NuclearDataPlotterInputReader.hpp"

using namespace frendy;

NuclearDataPlotterInputReader::NuclearDataPlotterInputReader(void)
{
  clear();
}

NuclearDataPlotterInputReader::~NuclearDataPlotterInputReader(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

const int NuclearDataPlotterInputReader::no_file;
const int NuclearDataPlotterInputReader::endf_file;
const int NuclearDataPlotterInputReader::ace_file;
const int NuclearDataPlotterInputReader::pendf_file;
const int NuclearDataPlotterInputReader::gendf_file;

const int NuclearDataPlotterInputReader::histogram; //or two_point
const int NuclearDataPlotterInputReader::two_point;
const int NuclearDataPlotterInputReader::one_point;

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataPlotterInputReader::clear()
{
  print_title_flg    = 0;
  print_set_data_flg = frendy_utils.get_print_set_data_flg_def();

  ref_flg = no_file;
  com_flg = no_file;
  file_no = 0;

  nucl_file_name_tsl.clear();
  nucl_file_name     = frendy_utils.get_nucl_file_name_def();
//  nucl_file_name_tsl = frendy_utils.get_nucl_file_name_tsl_def();
  ace_file_name      = frendy_utils.get_ace_file_name_def();
  pendf_file_name    = frendy_utils.get_pendf_file_name_def();
  gendf_file_name    = frendy_utils.get_pendf_file_name_def();

  error              = 10.0*frendy_utils.get_error_def();
  error_max          = 10.0*frendy_utils.get_error_max_def();
  error_integral     = 10.0*frendy_utils.get_error_integral_def();

  input_file_name    = "";
  output_file_name   = "";
  edit_flg           = histogram;

  mf_list.clear();
  mt_list.clear();
  mat_no                 = -1;
  temp                   = -1.0;

  mg_flg                 = 0;

  set_error_max_flg      = 0;
  set_error_integral_flg = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataPlotterInputReader::read_input_data_from_input_file(string file_name)
{
  input_file_name = file_name;

  FileCommentRemover file_handling_obj;
  vector<vector<string> > input_data = file_handling_obj.remove_comment_and_devide_text_data(file_name);

  read_input_data(input_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<int> NuclearDataPlotterInputReader::read_input_data(string inp_name, vector<vector<string> >& input_data)
{
  input_file_name = inp_name;

  return read_input_data(input_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<int> NuclearDataPlotterInputReader::read_input_data(vector<vector<string> >& input_data)
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

int NuclearDataPlotterInputReader::read_input_data(vector<string>& input_type, vector<string>& input_data)
{
  if( static_cast<int>(input_type.size()) != 1 )
  {
    string class_name = "NuclearDataPlotterInputReader";
    string func_name  = "read_input_data(vector<string>& input_type, vector<string>& input_data)";
    frendy_utils.error_input_type_size(class_name, func_name, input_type);
  }

  return read_input_data(input_type[0], input_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int NuclearDataPlotterInputReader::read_input_data(string& input_type, vector<string>& input_data)
{
  if( static_cast<int>(input_data.size()) == 0 )
  {
    string class_name = "NuclearDataPlotterInputReader";
    string func_name  = "read_input_data(string& input_type, vector<string>& input_data)";
    frendy_utils.error_input_data_size_is_zero(class_name, func_name, input_data);
  }

  if( print_set_data_flg == frendy_utils.print_set_data && print_title_flg == 0 )
  {
    print_title_flg = 1;
    cout << "=== Read input data for NuclearDataPlotter ===" << endl;
  }

  //Modify capital letter to lower-case letter
  string input_type_mod = input_type;
  transform(input_type_mod.begin(), input_type_mod.end(), input_type_mod.begin(), ::tolower);
  replace(input_type_mod.begin(), input_type_mod.end(), '-', '_');

  int inp_check = 1;
  if( input_type_mod == "nucl_file_name" || input_type_mod == "nucl_name" ||
      input_type_mod == "endf_file_name" || input_type_mod == "endf_name" ||
      input_type_mod == "nucl_file_name_tsl" || input_type_mod == "nucl_name_tsl" ||
      input_type_mod == "endf_file_name_tsl" || input_type_mod == "endf_name_tsl" )
  {
    set_nucl_file_name(input_data);
  }
//  else if( input_type_mod == "nucl_file_name_tsl" || input_type_mod == "nucl_name_tsl" ||
//           input_type_mod == "endf_file_name_tsl" || input_type_mod == "endf_name_tsl" )
//  {
//    set_nucl_file_name_tsl(input_data);
//  }
  else if( input_type_mod == "ace_file_name"     || input_type_mod == "ace_name" ||
           input_type_mod == "ace_file_name_tsl" || input_type_mod == "ace_name_tsl" )
  {
    set_ace_file_name(input_data);
  }
  else if( input_type_mod == "pendf_file_name" || input_type_mod == "pendf_name" )
  {
    set_pendf_file_name(input_data);
  }
  else if( input_type_mod == "gendf_file_name" || input_type_mod == "gendf_name" )
  {
    set_gendf_file_name(input_data);
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
  else if( input_type_mod == "mg_weighting_spectrum_mode" )
  {
    mg_flg++;
  }
  else if( input_type_mod == "mg_weighting_spectrum_data" || input_type_mod == "mg_weighting_spectrum" )
  {
    mg_flg++;
  }
  else if( input_type_mod == "mg_weighting_spectrum_data_int" || input_type_mod == "mg_weighting_spectrum_int" )
  {
    mg_flg++;
  }
  else if( input_type_mod == "mg_structure"          ||
           input_type_mod == "mg_structure_neutron"  ||
           input_type_mod == "mg_structure_neutrons" ||
           input_type_mod == "multi_group_structure" ||
           input_type_mod == "multi_group_neutrons"  ||
           input_type_mod == "multi_group_neutron"   )
  {
    mg_flg++;
  }
  else if( input_type_mod == "temp" || input_type_mod == "temperature" )
  {
    set_temp(input_data);
  }

  // Following input option is only for this calculation mode
  else if( input_type_mod == "output_name"      || input_type_mod == "out_name" ||
           input_type_mod == "output_file"      || input_type_mod == "out_file" ||
           input_type_mod == "output_file_name" || input_type_mod == "out_file_name" ||
           input_type_mod == "output" )
  {
    set_output_file_name(input_data);
  }
  else if( input_type_mod == "edit_flag" || input_type_mod == "edit_mode" ||
           input_type_mod == "edit_flg" )
  {
    set_edit_flg(input_data);
  }
  else if( input_type_mod == "mf"           || input_type_mod == "mf_list" ||
           input_type_mod == "mf_type_list" || input_type_mod == "mf_type" ||
           input_type_mod == "mf_data_list" || input_type_mod == "mf_data" ||
           input_type_mod == "mf_list_data" || input_type_mod == "mf_type_data" )
  {
    set_mf_list(input_data);
  }
  else if( input_type_mod == "mt"                 || input_type_mod == "mt_list"            ||
           input_type_mod == "mt_type_list"       || input_type_mod == "mt_type"            ||
           input_type_mod == "mt_data_list"       || input_type_mod == "mt_data"            ||
           input_type_mod == "mt_list_data"       ||
           input_type_mod == "xs_type_list"       || input_type_mod == "xs_type"            ||
           input_type_mod == "xs_list"            || input_type_mod == "xs_type_data"       ||
           input_type_mod == "xs_list_data"       ||
           input_type_mod == "react_type_list"    || input_type_mod == "react_type"         ||
           input_type_mod == "react_list"         || input_type_mod == "react_type_data"    ||
           input_type_mod == "react_list_data"    || 
           input_type_mod == "reaction_type_list" || input_type_mod == "reaction_type"      ||
           input_type_mod == "reaction_list"      || input_type_mod == "reaction_type_data" ||
           input_type_mod == "reaction_list_data" )
  {
    set_mt_list(input_data);
  }
  else if( input_type_mod == "mat_no"      || input_type_mod == "mat" ||
           input_type_mod == "mat_type"    ||
           input_type_mod == "material_no" || input_type_mod == "material" ||
           input_type_mod == "material_type" )
  {
    set_mat_no(input_data);
  }
  else
  {
    inp_check = 0;
  }

  return inp_check;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataPlotterInputReader::set_nucl_file_name(vector<string>& input_data)
{
  file_no+= static_cast<int>(input_data.size());
  if( ref_flg <= 0 )
  {
    ref_flg = endf_file;
    if( static_cast<int>(input_data.size()) > 1 )
    {
      com_flg = endf_file;
    }
  }
  else if( com_flg <= 0 )
  {
    com_flg = endf_file;
  }

  nucl_file_name = input_data;

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    for(int i=0; i<static_cast<int>(nucl_file_name.size()); i++)
    {
      if( i==0 )
      {
        cout << "  nucl_file_name     : " << input_data[i] << endl;
      }
      else
      {
        cout << "                     : " << input_data[i] << endl;
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataPlotterInputReader::set_nucl_file_name_tsl(vector<string>& input_data)
{
  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    int i_max = static_cast<int>(input_data.size());
    if( i_max == 1 )
    {
      cout << "  nucl_file_name_tsl                   : " << input_data[0] << endl;
    }
    else
    {
      cout << "  No. of nucl_file_name_tsl            : " << i_max << endl;
      for(int i=0; i<i_max; i++)
      {
        cout << "    nucl_file_name_tsl                 : " << input_data[i] << endl;
      }
    }
  }

  nucl_file_name_tsl = input_data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataPlotterInputReader::set_ace_file_name(vector<string>& input_data)
{
  file_no+=static_cast<int>(input_data.size());
  if( ref_flg <= 0 )
  {
    ref_flg = ace_file;
    if( static_cast<int>(input_data.size()) > 1 )
    {
      com_flg = ace_file;
    }
  }
  else if( com_flg <= 0 )
  {
    com_flg = ace_file;
  }

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    int i_max = static_cast<int>(input_data.size());
    if( i_max == 1 )
    {
      cout << "  ace_file_name                        : " << input_data[0] << endl;
    }
    else
    {
      cout << "  No. of ace_file_name                 : " << i_max << endl;
      for(int i=0; i<i_max; i++)
      {
        cout << "    ace_file_name                      : " << input_data[i] << endl;
      }
    }
  }

  ace_file_name = input_data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataPlotterInputReader::set_pendf_file_name(vector<string>& input_data)
{
  file_no+=static_cast<int>(input_data.size());
  if( ref_flg <= 0 )
  {
    ref_flg = pendf_file;
    if( static_cast<int>(input_data.size()) > 1 )
    {
      com_flg = pendf_file;
    }
  }
  else if( com_flg <= 0 )
  {
    com_flg = pendf_file;
  }

  pendf_file_name = input_data;

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    for(int i=0; i<static_cast<int>(pendf_file_name.size()); i++)
    {
      if( i==0 )
      {
        cout << "  pendf_file_name    : " << input_data[i] << endl;
      }
      else
      {
        cout << "                     : " << input_data[i] << endl;
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataPlotterInputReader::set_gendf_file_name(vector<string>& input_data)
{
  file_no+=static_cast<int>(input_data.size());
  if( ref_flg <= 0 )
  {
    ref_flg = gendf_file;
    if( static_cast<int>(input_data.size()) > 1 )
    {
      com_flg = gendf_file;
    }
  }
  else if( com_flg <= 0 )
  {
    com_flg = gendf_file;
  }

  gendf_file_name = input_data;

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    for(int i=0; i<static_cast<int>(gendf_file_name.size()); i++)
    {
      if( i==0 )
      {
        cout << "  gendf_file_name    : " << input_data[i] << endl;
      }
      else
      {
        cout << "                     : " << input_data[i] << endl;
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataPlotterInputReader::set_error(vector<string>& input_data)
{
  if( static_cast<int>(input_data.size()) > 1 )
  {
    string class_name = "NuclearDataPlotterInputReader";
    string func_name  = "set_error(vector<string>& input_data)";
    frendy_utils.error_input_data_size_is_larger_than_one(class_name, func_name, input_data);
  }

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  error              : " << input_data[0] << endl;
  }

  str_obj.string_check(input_data[0]);
  error = numeric_string_cast<Real>(input_data[0]);

  if( set_error_max_flg == 0 )
  {
    error_max = error * 10.0;

    if( print_set_data_flg == frendy_utils.print_set_data )
    {
      cout << "  error_max          : " << error_max << " (automatically modified by error value)" << endl;
    }
  }

  if( set_error_integral_flg == 0 )
  {
    error_integral = error / 2.0E+4;

    if( print_set_data_flg == frendy_utils.print_set_data )
    {
      cout << "  error_integral     : " << error_integral << " (automatically modified by error value)" << endl;
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataPlotterInputReader::set_error_max(vector<string>& input_data)
{
  set_error_max_flg = 1;

  if( static_cast<int>(input_data.size()) > 1 )
  {
    string class_name = "NuclearDataPlotterInputReader";
    string func_name  = "set_error_max(vector<string>& input_data)";
    frendy_utils.error_input_data_size_is_larger_than_one(class_name, func_name, input_data);
  }

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  error_max          : " << input_data[0] << endl;
  }

  str_obj.string_check(input_data[0]);
  error_max = numeric_string_cast<Real>(input_data[0]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataPlotterInputReader::set_error_integral(vector<string>& input_data)
{
  set_error_integral_flg = 1;

  if( static_cast<int>(input_data.size()) > 1 )
  {
    string class_name = "NuclearDataPlotterInputReader";
    string func_name  = "set_error_integral(vector<string>& input_data)";
    frendy_utils.error_input_data_size_is_larger_than_one(class_name, func_name, input_data);
  }

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  error_integral     : " << input_data[0] << endl;
  }

  str_obj.string_check(input_data[0]);
  error_integral = numeric_string_cast<Real>(input_data[0]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataPlotterInputReader::set_output_file_name(string str_data)
{
  vector<string> input_data;
  input_data.clear();

  input_data.resize(1);
  input_data[0] = str_data;

  set_output_file_name(input_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataPlotterInputReader::set_output_file_name(vector<string>& input_data)
{
  if( static_cast<int>(input_data.size()) > 1 )
  {
    string class_name = "NuclearDataPlotterInputReader";
    string func_name  = "set_output_file_name(vector<string>& input_data)";
    frendy_utils.error_input_data_size_is_larger_than_one(class_name, func_name, input_data);
  }

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  output_file_name   : " << input_data[0] << endl;
  }

  output_file_name = input_data[0];
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataPlotterInputReader::set_edit_flg(string str_data)
{
  vector<string> input_data;
  input_data.clear();

  input_data.resize(1);
  input_data[0] = str_data;

  set_edit_flg(input_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataPlotterInputReader::set_edit_flg(vector<string>& input_data)
{
  if( static_cast<int>(input_data.size()) > 1 )
  {
    string class_name = "NuclearDataPlotterInputReader";
    string func_name  = "set_edit_flg(vector<string>& input_data)";
    frendy_utils.error_input_data_size_is_larger_than_one(class_name, func_name, input_data);
  }

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  edit_flag          : " << input_data[0] << endl;
  }

  string edit_flg_mod = input_data[0];
  transform(edit_flg_mod.begin(), edit_flg_mod.end(), edit_flg_mod.begin(), ::tolower);
  replace(edit_flg_mod.begin(), edit_flg_mod.end(), '-', '_');

  if( edit_flg_mod == "histogram"  || edit_flg_mod == "hist" ||
      edit_flg_mod == "two_point"  || edit_flg_mod == "two" )
  {
    edit_flg = histogram;
  }
  else if( edit_flg_mod == "non_histogram" || edit_flg_mod == "non_hist" ||
           edit_flg_mod == "no_histogram"  || edit_flg_mod == "no_hist"  ||
           edit_flg_mod == "one_point"     || edit_flg_mod == "one" )
  {
    edit_flg = one_point;
  }
  else
  {
    string class_name = "NuclearDataPlotterInputReader";
    string func_name  = "set_edit_flg(vector<string>& input_data)";
    vector<string> err_com;
    err_com.push_back("This edit_flag is not available in this program.");
    err_com.push_back("Available edit_flag is histogram, two_point, and one_point.");
    err_com.push_back("Please check the edit_flg.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataPlotterInputReader::set_mf_list(vector<string>& input_data)
{
  mf_list = str_conv_obj.get_int_data_list(input_data);

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    int i_max = static_cast<int>(mf_list.size());
    for(int i=0; i<i_max; i++)
    {
      if( i==0 )
      {
        cout << "  mf_list            : " << mf_list[i] << endl;
      }
      else
      {
        cout << "                     : " << mf_list[i] << endl;
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataPlotterInputReader::set_mt_list(vector<string>& input_data)
{
  mt_list = str_conv_obj.get_int_data_list(input_data);

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    int i_max = static_cast<int>(mt_list.size());
    for(int i=0; i<i_max; i++)
    {
      if( i==0 )
      {
        cout << "  mt_list            : " << mt_list[i] << endl;
      }
      else
      {
        cout << "                     : " << mt_list[i] << endl;
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataPlotterInputReader::set_temp(vector<string>& input_data)
{
  set_error_integral_flg = 1;

  if( static_cast<int>(input_data.size()) > 1 )
  {
    string class_name = "NuclearDataPlotterInputReader";
    string func_name  = "set_temp(vector<string>& input_data)";
    frendy_utils.error_input_data_size_is_larger_than_one(class_name, func_name, input_data);
  }

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  temperature        : " << input_data[0] << endl;
  }

  str_obj.string_check(input_data[0]);
  temp = numeric_string_cast<Real>(input_data[0]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataPlotterInputReader::set_mat_no(vector<string>& input_data)
{
  set_error_integral_flg = 1;

  if( static_cast<int>(input_data.size()) > 1 )
  {
    string class_name = "NuclearDataPlotterInputReader";
    string func_name  = "set_mat_no(vector<string>& input_data)";
    frendy_utils.error_input_data_size_is_larger_than_one(class_name, func_name, input_data);
  }

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  MAT (material no)  : " << input_data[0] << endl;
  }

  str_obj.string_check(input_data[0]);
  mat_no = numeric_string_cast<Integer>(input_data[0]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataPlotterInputReader::set_input_file_name(string str_data)
{
  input_file_name = str_data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataPlotterInputReader::set_error(Real real_data)
{
  error = real_data;
}

void NuclearDataPlotterInputReader::set_error_max(Real real_data)
{
  error_max = real_data;
}

void NuclearDataPlotterInputReader::set_error_integral(Real real_data)
{
  error_integral = real_data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataPlotterInputReader::set_print_set_data_flg(vector<string>& input_data)
{
  string class_name = "NuclearDataPlotterInputReader";
  string func_name  = "set_print_set_data_flg(vector<string>& input_data)";

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  print_set_data_flg : " << input_data[0] << endl;
  }

  print_set_data_flg = frendy_utils.read_print_set_data_flg(class_name, func_name, input_data);
}

void NuclearDataPlotterInputReader::set_print_set_data_flg(int int_val)
{
  frendy_utils.check_print_set_data_flg("NuclearDataPlotterInputReader", int_val);

  print_set_data_flg = int_val;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> NuclearDataPlotterInputReader::get_nucl_file_name()
{
  return nucl_file_name;
}

vector<string> NuclearDataPlotterInputReader::get_pendf_file_name()
{
  return pendf_file_name;
}

vector<string> NuclearDataPlotterInputReader::get_gendf_file_name()
{
  return gendf_file_name;
}

//vector<string> NuclearDataPlotterInputReader::get_nucl_file_name_tsl()
//{
//  return nucl_file_name_tsl;
//}

vector<string> NuclearDataPlotterInputReader::get_ace_file_name()
{
  return ace_file_name;
}

Real NuclearDataPlotterInputReader::get_error()
{
  return error;
}

Real NuclearDataPlotterInputReader::get_error_max()
{
  return error_max;
}

Real NuclearDataPlotterInputReader::get_error_integral()
{
  return error_integral;
}

string NuclearDataPlotterInputReader::get_input_file_name()
{
  return input_file_name;
}

string NuclearDataPlotterInputReader::get_output_file_name()
{
  return output_file_name;
}

int NuclearDataPlotterInputReader::get_edit_flg()
{
  return edit_flg;
}

int NuclearDataPlotterInputReader::get_ref_flg()
{
  return ref_flg;
}

int NuclearDataPlotterInputReader::get_file_no()
{
  return file_no;
}

int NuclearDataPlotterInputReader::get_com_flg()
{
  return com_flg;
}

int NuclearDataPlotterInputReader::get_mg_flg()
{
  return mg_flg;
}

vector<Integer> NuclearDataPlotterInputReader::get_mf_list()
{
  return mf_list;
}

vector<Integer> NuclearDataPlotterInputReader::get_mt_list()
{
  return mt_list;
}

vector<Integer> NuclearDataPlotterInputReader::get_xs_type_list()
{
  return mt_list;
}

Integer NuclearDataPlotterInputReader::get_mat_no()
{
  return mat_no;
}

Real NuclearDataPlotterInputReader::get_temp()
{
  return temp;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int NuclearDataPlotterInputReader::get_print_set_data_flg()
{
  return print_set_data_flg;
}

