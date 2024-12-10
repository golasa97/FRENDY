#include "NjoyUtils/ModerInputReader.hpp"

using namespace frendy;

ModerInputReader::ModerInputReader(void)
{
  clear();
}

ModerInputReader::~ModerInputReader(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ModerInputReader::read_input(string file_name)
{
  read_input(file_name, 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ModerInputReader::read_input(string file_name, int line_no)
{
  clear();

  input_moder = file_name;

  //open input file
  ifstream fin(input_moder.c_str());
  if( !fin )
  {
    string class_name = "ModerInputReader";
    string func_name  = "read_input(string file_name)";

    string str_data = "File name : " + file_name;

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("There is no input file.");
    err_com.push_back("Please check the input file name.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //read until moder input 
  string input_case = "moder";
  rn_obj.search_each_input(fin, input_case, line_no);

  //read moder input
  read_file_name(fin);

  if( abs(data_format_no) < 20 )
  {
    read_other_data(fin);
  }

  fin.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ModerInputReader::read_file_name(ifstream& fin)
{
  string line_data;
  vector<string> input_data;

  //Card 01
  getline(fin, line_data);
  input_data = rn_obj.read_line_without_slash(line_data);

  if( static_cast<int>(input_data.size()) < 2 )
  {
    string class_name = "ModerInputReader";
    string func_name  = "read_file_name(ifstream& fin)";

    ostringstream oss;
    oss << input_data.size();
    string str_data01 = "Input file name = " + input_moder;
    string str_data02 = "Data no         = " + oss.str();
    string str_data03 = "Input data      = " + line_data;

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("The data number of card 1 is less than 2.");
    err_com.push_back("In card 1, two integer data are required, i.e., nin and nout.");
    err_com.push_back("Please check the input file.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  for(int i=0; i<2; i++)
  {
    int j = static_cast<int>(input_data[i].find_first_of("-"));
    if( j >= 0 )
    {
      string class_name = "ModerInputReader";
      string func_name  = "read_file_name(ifstream& fin)";

      string str_data = "tape no : " + input_data[i];

      vector<string> err_com;
      err_com.push_back(str_data);
      err_com.push_back("Binary mode, i.e., tape no less than 0, can not treat in FRENDY.");

      if( j==0 )
      {
        err_com.push_back("This file considered as the ascii mode file.");
        err_obj.output_caution(class_name, func_name, err_com);
      }
      else
      {
        err_com.push_back("Please check the input file name.");
        err_obj.output_runtime_error(class_name, func_name, err_com);
      }

      input_data[i] = input_data[i].substr(j+1);
    }
  }

  pendf_in   = "tape" + input_data[0]; 
  pendf_out  = "tape" + input_data[1]; 

  data_format_no = atoi(input_data[0].c_str());

  line_data.clear();
  clr_obj.clear_vec_array1_str(input_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ModerInputReader::read_other_data(ifstream& fin)
{
  string line_data;
  vector<string> input_data;

  tape_id.clear();
  clr_obj.clear_vec_array1_str(tape_in);
  mat.clear();
  
  //Card 02
  getline(fin, line_data);
  input_data = rn_obj.read_line_without_slash(line_data);
  if( input_data[0].size() == 1 && static_cast<int>(input_data[0].find_first_of("0")) == 0 )
  {
    return;
  }
  tape_id = input_data[0];

  int nin_val = 100;
  while( nin_val != 0 )
  {
    //Card 03
    getline(fin, line_data);
    input_data = rn_obj.read_line_without_slash(line_data);
    nin_val = numeric_string_cast<Integer>(input_data[0]);
    if( input_data[0].size() == 1 && nin_val == 0 )
    {
      break;
    }

    int j = static_cast<int>(input_data[0].find_first_of("-"));
    if( j >= 0 )
    {
      string class_name = "ModerInputReader";
      string func_name  = "read_file_name(ifstream& fin)";

      string str_data = "tape no : " + input_data[0];

      vector<string> err_com;
      err_com.push_back(str_data);
      err_com.push_back("Binary mode, i.e., tape no less than 0, can not treat in FRENDY.");
      err_com.push_back("This file considered as the ascii mode file.");

      err_obj.output_caution(class_name, func_name, err_com);

      input_data[0] = input_data[0].substr(j+1);
    }

    tape_in.push_back("tape" + input_data[0]);
    mat.push_back(numeric_string_cast<Integer>(input_data[1]));
  }

  line_data.clear();
  clr_obj.clear_vec_array1_str(input_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ModerInputReader::clear()
{
  input_moder.clear();
  pendf_in.clear();
  pendf_out.clear();
  tape_id.clear();

  clr_obj.clear_vec_array1_str(tape_in);
  mat.clear();
  data_format_no = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

string   ModerInputReader::get_input_moder()
{
  return input_moder;
}

string   ModerInputReader::get_pendf_input_name()
{
  return pendf_in;
}

string   ModerInputReader::get_pendf_output_name()
{
  return pendf_out;
}

string   ModerInputReader::get_tape_id()
{
  return tape_id;
}

vector<string>   ModerInputReader::get_tape_name()
{
  return tape_in;
}

vector<Integer>  ModerInputReader::get_mat()
{
  return mat;
}

Integer          ModerInputReader::get_data_format_no()
{
  return data_format_no;
}

