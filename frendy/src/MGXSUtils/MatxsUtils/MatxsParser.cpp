#include "MGXSUtils/MatxsUtils/MatxsParser.hpp"

using namespace frendy;

// ***** MatxsParser ***** //
//constructor
MatxsParser::MatxsParser(void)
{
  clear();
}

//destructor
MatxsParser::~MatxsParser(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsParser::clear()
{
  matxs_obj.clear();

  file_name.clear();

  VectorClearer clr_obj;
  clr_obj.clear_vec_array1_str(text);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsParser::read_matxs()
{
  matxs_obj.read_data(text);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsParser::set_file_name(string str_data)
{
  clear();

  file_name = str_data;
  ifstream fin(file_name.c_str());

  //Output error message and abort if input file can't open.
  if(!fin)
  {
    string class_name = "MatxsParser";
    string func_name  = "set_file_name(string str_data)";

    vector<string> err_com;
    err_com.push_back("There is no MATXS file.");

    string str_data = "File name : " + file_name;
    err_com.push_back(str_data);
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //Copy endf file text data to vector<string>
  string line_data;
  const Integer char_length = 500;
  char *buf_char;
  buf_char = new char[char_length];
  while(!fin.eof())
  {
    fin.getline(buf_char, char_length);
    line_data = buf_char;

    if(!fin.eof())
    {
      text.push_back(line_data);
    }
  }
  line_data.clear();
  delete [] buf_char;

  read_matxs();
}

void MatxsParser::set_text(vector<string>& text_data)
{
  clear();

  text = text_data;

  read_matxs();
}

string MatxsParser::get_file_name()
{
  return file_name;
}

vector<string> MatxsParser::get_text()
{
  return text;
}

MatxsCommonData MatxsParser::get_matxs_obj()
{
  return matxs_obj;
} 

