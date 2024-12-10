#include "FrendyUtils/Endf6FormatCheckInputReader.hpp"

using namespace frendy;

Endf6FormatCheckInputReader::Endf6FormatCheckInputReader(void)
{
  clear();
}

Endf6FormatCheckInputReader::~Endf6FormatCheckInputReader(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6FormatCheckInputReader::clear()
{
  print_title_flg    = 0;

  print_set_data_flg = frendy_utils.get_print_set_data_flg_def();

  nucl_file_name     = frendy_utils.get_nucl_file_name_def();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6FormatCheckInputReader::read_input_data_from_input_file(string file_name)
{
  FileCommentRemover file_handling_obj;
  vector<vector<string> > input_data = file_handling_obj.remove_comment_and_devide_text_data(file_name);

  read_input_data(input_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<int> Endf6FormatCheckInputReader::read_input_data(vector<vector<string> >& input_data)
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

int Endf6FormatCheckInputReader::read_input_data(vector<string>& input_type, vector<string>& input_data)
{
  if( static_cast<int>(input_type.size()) != 1 )
  {
    string class_name = "Endf6FormatCheckInputReader";
    string func_name  = "read_input_data(vector<string>& input_type, vector<string>& input_data)";
    frendy_utils.error_input_type_size(class_name, func_name, input_type);
  }

  return read_input_data(input_type[0], input_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int Endf6FormatCheckInputReader::read_input_data(string& input_type, vector<string>& input_data)
{
  if( static_cast<int>(input_data.size()) == 0 )
  {
    string class_name = "Endf6FormatCheckInputReader";
    string func_name  = "read_input_data(string& input_type, vector<string>& input_data)";
    frendy_utils.error_input_data_size_is_zero(class_name, func_name, input_data);
  }

  if( print_set_data_flg == frendy_utils.print_set_data && print_title_flg == 0 )
  {
    print_title_flg = 1;
    cout << "=== Read input data for Endf6FormatCheckInputReader ===" << endl;
  }

  //Modify capital letter to lower-case letter
  string input_type_mod = input_type;
  transform(input_type_mod.begin(), input_type_mod.end(), input_type_mod.begin(), ::tolower);
  replace(input_type_mod.begin(), input_type_mod.end(),  '-', '_');

  int inp_check = 1;
  if( input_type_mod == "nucl_file_name" || input_type_mod == "nucl_name" ||
      input_type_mod == "endf_file_name" || input_type_mod == "endf_name" )
  {
    set_nucl_file_name(input_data);
  }
  else
  {
    inp_check = 0;
  }

  return inp_check;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6FormatCheckInputReader::set_nucl_file_name(vector<string> input_data)
{
  if( static_cast<int>(input_data.size()) > 1 )
  {
    string class_name = "Endf6FormatCheckInputReader";
    string func_name  = "set_nucl_file_name(vector<string>& input_data)";
    frendy_utils.error_input_data_size_is_larger_than_one(class_name, func_name, input_data);
  }

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  nucl_file_name          : " << input_data[0] << endl;
  }

  nucl_file_name = input_data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6FormatCheckInputReader::set_nucl_file_name(string str_data)
{
  nucl_file_name.resize(1);
  nucl_file_name[0] = str_data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> Endf6FormatCheckInputReader::get_nucl_file_name()
{
  return nucl_file_name;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

