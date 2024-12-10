#include "FrendyUtils/ProbTableInputReader.hpp"

using namespace frendy;

ProbTableInputReader::ProbTableInputReader(void)
{
  clear();
}

ProbTableInputReader::~ProbTableInputReader(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbTableInputReader::clear()
{
  print_title_flg        = 0;

  print_set_data_flg     = frendy_utils.get_print_set_data_flg_def();
  process_flg            = frendy_utils.get_process_flg_def();
  write_pendf_flg        = frendy_utils.get_write_pendf_flg_def();

  nucl_file_name         = frendy_utils.get_nucl_file_name_def();
  pendf_file_name        = frendy_utils.get_pendf_file_name_def();
  pendf_label_data       = frendy_utils.get_pendf_label_data_def();
  comment_data           = frendy_utils.get_comment_data_def();

  probability_bin_no     = frendy_utils.get_probability_bin_no_def();
  ladder_no              = frendy_utils.get_ladder_no_def();
  err_p_tab              = frendy_utils.get_err_p_tab_def();
  ene_grid_no_per_ladder = frendy_utils.get_ene_grid_no_per_ladder_def();
  sigma_zero_data        = frendy_utils.get_sigma_zero_data_def();

  random_seed            = frendy_utils.get_random_seed_def();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbTableInputReader::read_input_data_from_input_file(string file_name)
{
  FileCommentRemover file_handling_obj;
  vector<vector<string> > input_data = file_handling_obj.remove_comment_and_devide_text_data(file_name);

  read_input_data(input_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<int> ProbTableInputReader::read_input_data(vector<vector<string> >& input_data)
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

int ProbTableInputReader::read_input_data(vector<string>& input_type, vector<string>& input_data)
{
  if( static_cast<int>(input_type.size()) != 1 )
  {
    string class_name = "ProbTableInputReader";
    string func_name  = "read_input_data(vector<string>& input_type, vector<string>& input_data)";
    frendy_utils.error_input_type_size(class_name, func_name, input_type);
  }

  return read_input_data(input_type[0], input_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int ProbTableInputReader::read_input_data(string& input_type, vector<string>& input_data)
{
  if( static_cast<int>(input_data.size()) == 0 )
  {
    string class_name = "ProbTableInputReader";
    string func_name  = "read_input_data(string& input_type, vector<string>& input_data)";
    frendy_utils.error_input_data_size_is_zero(class_name, func_name, input_data);
  }

  if( print_set_data_flg == frendy_utils.print_set_data && print_title_flg == 0 )
  {
    print_title_flg = 1;
    cout << "=== Read input data for ProbTable ===" << endl;
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
  else if( input_type_mod == "probability_bin_no" )
  {
    set_probability_bin_no(input_data);
  }
  else if( input_type_mod == "ladder_no" || input_type_mod == "lad_no" )
  {
    set_ladder_no(input_data);
  }
  else if( input_type_mod == "err_p_table" || input_type_mod == "err_p_tab" ||
           input_type_mod == "err_ptab" )
  {
    set_err_p_tab(input_data);
  }
  else if( input_type_mod == "ene_grid_no_per_ladder" ||
           input_type_mod == "ene_grid_per_ladder"    ||
           input_type_mod == "ene_no_per_ladder"      ||
           input_type_mod == "ene_grid_no_per_lad"    ||
           input_type_mod == "ene_grid_per_lad"       ||
           input_type_mod == "ene_no_per_lad"         )
  {
    set_ene_grid_no_per_ladder(input_data);
  }
  else if( input_type_mod == "sigma_zero_data" || input_type_mod == "sig_zero_data" ||
           input_type_mod == "sigma_zero"      || input_type_mod == "sig_zero"  )
  {
    set_sigma_zero_data(input_data);
  }
  else if( input_type_mod == "random_seed" )
  {
    set_random_seed(input_data);
  }
  else if( input_type_mod == "print_set_data_prob_table"                  ||
           input_type_mod == "print_set_data_prob_table_generator"        ||
           input_type_mod == "print_set_data_probability_table"           ||
           input_type_mod == "print_set_data_probability_table_generator" ||
           input_type_mod == "print_set_data_unreso_utils" )
  {
    set_print_set_data_flg(input_data);
  }
  else if( input_type_mod == "process_prob_table"                  ||
           input_type_mod == "process_prob_table_generator"        ||
           input_type_mod == "process_probability_table"           ||
           input_type_mod == "process_probability_table_generator" ||
           input_type_mod == "process_unreso_utils" )
  {
    set_process_flg(input_data);
  }
  else if( input_type_mod == "write_pendf_prob_table"                  ||
           input_type_mod == "write_pendf_prob_table_generator"        ||
           input_type_mod == "write_pendf_probability_table"           ||
           input_type_mod == "write_pendf_probability_table_generator" ||
           input_type_mod == "write_pendf_unreso_utils" )
  {
    set_write_pendf_flg(input_data);
  }
  else if( input_type_mod == "pendf_file_name_prob_table"                  ||
           input_type_mod == "pendf_file_name_prob_table_generator"        ||
           input_type_mod == "pendf_file_name_probability_table"           ||
           input_type_mod == "pendf_file_name_probability_table_generator" ||
           input_type_mod == "pendf_file_name_unreso_utils" )
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

void ProbTableInputReader::set_nucl_file_name(string input_data)
{
  vector<string> str_vec;
  str_vec.resize(1);

  str_vec[0] = input_data;

  set_nucl_file_name(str_vec);
}

void ProbTableInputReader::set_nucl_file_name(vector<string> input_data)
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

void ProbTableInputReader::set_pendf_label_data(string input_data)
{
  vector<string> str_vec;
  str_vec.resize(1);

  str_vec[0] = input_data;

  set_pendf_label_data(str_vec);
}

void ProbTableInputReader::set_pendf_label_data(vector<string> input_data)
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

void ProbTableInputReader::set_comment_data(vector<string> input_data)
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

void ProbTableInputReader::set_probability_bin_no(vector<string>& input_data)
{
  if( static_cast<int>(input_data.size()) > 1 )
  {
    string class_name = "ProbTableInputReader";
    string func_name  = "set_probability_bin_no(vector<string>& input_data)";
    frendy_utils.error_input_data_size_is_larger_than_one(class_name, func_name, input_data);
  }

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  probability_bin_no      : " << input_data[0] << endl;
  }

  str_obj.string_check(input_data[0]);
  probability_bin_no = numeric_string_cast<Integer>(input_data[0]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbTableInputReader::set_ladder_no(vector<string>& input_data)
{
  if( static_cast<int>(input_data.size()) > 1 )
  {
    string class_name = "ProbTableInputReader";
    string func_name  = "set_ladder_no(vector<string>& input_data)";
    frendy_utils.error_input_data_size_is_larger_than_one(class_name, func_name, input_data);
  }

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  ladder_no               : " << input_data[0] << endl;
  }

  str_obj.string_check(input_data[0]);
  ladder_no = numeric_string_cast<Integer>(input_data[0]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbTableInputReader::set_err_p_tab(vector<string>& input_data)
{
  if( static_cast<int>(input_data.size()) > 1 )
  {
    string class_name = "ProbTableInputReader";
    string func_name  = "set_err_p_tab(vector<string>& input_data)";
    frendy_utils.error_input_data_size_is_larger_than_one(class_name, func_name, input_data);
  }

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  err_p_tab               : " << input_data[0] << endl;
  }

  str_obj.string_check(input_data[0]);
  err_p_tab = numeric_string_cast<Real>(input_data[0]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbTableInputReader::set_ene_grid_no_per_ladder(vector<string>& input_data)
{
  if( static_cast<int>(input_data.size()) > 1 )
  {
    string class_name = "ProbTableInputReader";
    string func_name  = "set_ene_grid_no_per_ladder(vector<string>& input_data)";
    frendy_utils.error_input_data_size_is_larger_than_one(class_name, func_name, input_data);
  }

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  ene_grid_no_per_ladder  : " << input_data[0] << endl;
  }

  str_obj.string_check(input_data[0]);
  ene_grid_no_per_ladder = numeric_string_cast<Integer>(input_data[0]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbTableInputReader::set_sigma_zero_data(vector<string>& input_data)
{
  int i_max = static_cast<int>(input_data.size());
  if( i_max > 0 )
  {
    string str_data = input_data[0];
    transform(str_data.begin(), str_data.end(), str_data.begin(), ::tolower);

    if( str_data == "auto" )
    {
      sigma_zero_data = frendy_utils.get_sigma_zero_data_def();
      return;
    }
  }

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  sigma_zero_data [barn]" << endl;
  }

  sigma_zero_data.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    if( print_set_data_flg == frendy_utils.print_set_data )
    {
      cout << "    " << i+1 << " / " << i_max << " : " << input_data[i] << endl;
    }

    str_obj.string_check(input_data[i]);
    sigma_zero_data[i] = numeric_string_cast<Real>(input_data[i]);
  }

  sort( sigma_zero_data.begin(), sigma_zero_data.end(), greater<Real>() );
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbTableInputReader::set_random_seed(vector<string>& input_data)
{
  if( static_cast<int>(input_data.size()) > 1 )
  {
    string class_name = "ProbTableInputReader";
    string func_name  = "set_random_seed(vector<string>& input_data)";
    frendy_utils.error_input_data_size_is_larger_than_one(class_name, func_name, input_data);
  }

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  random seed             : " << input_data[0] << endl;
  }

  str_obj.string_check(input_data[0]);
  random_seed = numeric_string_cast<Integer>(input_data[0]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbTableInputReader::set_probability_bin_no(Integer int_data)
{
  probability_bin_no = int_data;
}

void ProbTableInputReader::set_ladder_no(Integer int_data)
{
  ladder_no = int_data;
}
void ProbTableInputReader::set_err_p_tab(Real real_data)
{
  err_p_tab = real_data;
}

void ProbTableInputReader::set_ene_grid_no_per_ladder(Integer int_data)
{
  ene_grid_no_per_ladder = int_data;
}

void ProbTableInputReader::set_sigma_zero_data(vector<Real> real_vec)
{
  sigma_zero_data = real_vec;

  sort( sigma_zero_data.begin(), sigma_zero_data.end(), greater<Real>() );
}

void ProbTableInputReader::set_random_seed(Integer int_data)
{
  random_seed = int_data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> ProbTableInputReader::get_nucl_file_name()
{
  return nucl_file_name;
}

vector<string> ProbTableInputReader::get_pendf_file_name()
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

vector<string> ProbTableInputReader::get_pendf_label_data()
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

vector<string> ProbTableInputReader::get_comment_data()
{
  return comment_data;
}

Integer ProbTableInputReader::get_probability_bin_no()
{
  return probability_bin_no;
}

Integer ProbTableInputReader::get_ladder_no()
{
  return ladder_no;
}

Real    ProbTableInputReader::get_err_p_tab()
{
  return err_p_tab;
}

Integer ProbTableInputReader::get_ene_grid_no_per_ladder()
{
  return ene_grid_no_per_ladder;
}

vector<Real> ProbTableInputReader::get_sigma_zero_data()
{
  return sigma_zero_data;
}

Integer ProbTableInputReader::get_random_seed()
{
  return random_seed;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbTableInputReader::set_print_set_data_flg(vector<string>& input_data)
{
  string class_name = "ProbTableInputReader";
  string func_name  = "set_print_set_data_flg(vector<string>& input_data)";

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  print_set_data_flg      : " << input_data[0] << endl;
  }

  print_set_data_flg = frendy_utils.read_print_set_data_flg(class_name, func_name, input_data);
}

void ProbTableInputReader::set_process_flg(vector<string>& input_data)
{
  string class_name = "ProbTableInputReader";
  string func_name  = "set_process_flg(vector<string>& input_data)";

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  process_flg             : " << input_data[0] << endl;
  }

  process_flg = frendy_utils.read_process_flg(class_name, func_name, input_data);
}

void ProbTableInputReader::set_write_pendf_flg(vector<string>& input_data)
{
  string class_name = "ProbTableInputReader";
  string func_name  = "set_write_pendf_flg(vector<string>& input_data)";

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  write_pendf_flg         : " << input_data[0] << endl;
  }

  write_pendf_flg = frendy_utils.read_write_pendf_flg(class_name, func_name, pendf_file_name, input_data);
}

void ProbTableInputReader::set_pendf_file_name(string input_data)
{
  vector<string> str_vec;
  str_vec.resize(1);
  str_vec[0] = input_data;

  set_pendf_file_name(str_vec);
}

void ProbTableInputReader::set_pendf_file_name(vector<string> input_data)
{
  set_write_pendf_flg(frendy_utils.write_pendf, input_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbTableInputReader::set_print_set_data_flg(int int_val)
{
  frendy_utils.check_print_set_data_flg("ProbTableInputReader", int_val);

  print_set_data_flg = int_val;
}

void ProbTableInputReader::set_process_flg(int int_val)
{
  frendy_utils.check_process_flg("ProbTableInputReader", int_val);

  process_flg = int_val;
}

void ProbTableInputReader::set_write_pendf_flg(int int_val)
{
  frendy_utils.check_write_pendf_flg_no_str_data("ProbTableInputReader", pendf_file_name, int_val);

  write_pendf_flg = int_val;
}

void ProbTableInputReader::set_write_pendf_flg(int int_val, string file_name)
{
  vector<string> str_vec;
  str_vec.resize(1);
  str_vec[0] = file_name;

  set_write_pendf_flg(int_val, str_vec);
}

void ProbTableInputReader::set_write_pendf_flg(int int_val, vector<string> file_name)
{
  frendy_utils.check_write_pendf_flg("ProbTableInputReader", int_val);

  write_pendf_flg = int_val;
  pendf_file_name = file_name;

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    frendy_utils.write_pendf_data(pendf_file_name, pendf_label_data, comment_data, write_pendf_flg);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int ProbTableInputReader::get_print_set_data_flg()
{
  return print_set_data_flg;
}

int ProbTableInputReader::get_process_flg()
{
  return process_flg;
}

int ProbTableInputReader::get_write_pendf_flg()
{
  return write_pendf_flg;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

