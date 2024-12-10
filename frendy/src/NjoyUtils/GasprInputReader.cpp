#include "NjoyUtils/GasprInputReader.hpp"

using namespace frendy;

GasprInputReader::GasprInputReader(void)
{
  clear();
}

GasprInputReader::~GasprInputReader(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GasprInputReader::read_input(string file_name)
{
  read_input(file_name, 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GasprInputReader::read_input(string file_name, int line_no)
{
  clear();

  input_gaspr = file_name;

  //open input file
  ifstream fin(input_gaspr.c_str());
  if( !fin )
  {
    string class_name = "GasprInputReader";
    string func_name  = "read_input(string file_name)";

    string str_data = "File name : " + file_name;

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("There is no input file.");
    err_com.push_back("Please check the input file name.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //read until gaspr input 
  string input_case = "gaspr";
  rn_obj.search_each_input(fin, input_case, line_no);

  //read gaspr input
  read_file_name(fin);

  fin.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GasprInputReader::read_file_name(ifstream& fin)
{
  string line_data;
  vector<string> input_data;

  //Card 01
  getline(fin, line_data);
  input_data = rn_obj.read_line_without_slash(line_data);

  if( static_cast<int>(input_data.size()) < 3 )
  {
    string class_name = "GasprInputReader";
    string func_name  = "read_file_name(ifstream& fin)";

    ostringstream oss;
    oss << input_data.size();
    string str_data01 = "Input file name = " + input_gaspr;
    string str_data02 = "Data no         = " + oss.str();
    string str_data03 = "Input data      = " + line_data;

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("The data number of card 1 is less than 3.");
    err_com.push_back("In card 1, three integer data is required, i.e., nendf, nin, and nout.");
    err_com.push_back("Please check the input file.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }


  for(int i=0; i<3; i++)
  {
    int j = static_cast<int>(input_data[i].find_first_of("-"));
    if( j >= 0 )
    {
      string class_name = "GasprInputReader";
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

  endf_name  = "tape" + input_data[0];
  pendf_in   = "tape" + input_data[1];
  pendf_out  = "tape" + input_data[2];

  line_data.clear();
  clr_obj.clear_vec_array1_str(input_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GasprInputReader::clear()
{
  input_gaspr.clear();
  endf_name.clear();
  pendf_in.clear();
  pendf_out.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

string                  GasprInputReader::get_input_gaspr()
{
  return input_gaspr;
}

string                  GasprInputReader::get_endf_name()
{
  return endf_name;
}

string                  GasprInputReader::get_pendf_input_name()
{
  return pendf_in;
}

string                  GasprInputReader::get_pendf_output_name()
{
  return pendf_out;
}

