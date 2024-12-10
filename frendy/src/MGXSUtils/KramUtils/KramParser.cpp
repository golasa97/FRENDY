#include "MGXSUtils/KramUtils/KramParser.hpp"

using namespace frendy;

// ***** KramParser ***** //
//constructor
KramParser::KramParser(void)
{
  clear();
}

//destructor
KramParser::~KramParser(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void KramParser::clear()
{
  kram_obj.clear();

  file_name.clear();

  VectorClearer clr_obj;
  clr_obj.clear_vec_array1_str(text);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void KramParser::read_kram(int mg_no)
{
  kram_obj.read_data(text, mg_no);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void KramParser::set_file_name(string str_data, int mg_no)
{
  clear();

  file_name = str_data;
  ifstream fin(file_name.c_str());

  //Output error message and abort if input file can't open.
  if(!fin)
  {
    string class_name = "KramParser";
    string func_name  = "set_file_name(string str_data)";

    vector<string> err_com;
    err_com.push_back("There is no KRAM file.");

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

  read_kram(mg_no);
}

void KramParser::set_text(vector<string>& text_data, int mg_no)
{
  clear();
  text = text_data;

  read_kram(mg_no);
}

string KramParser::get_file_name()
{
  return file_name;
}

vector<string> KramParser::get_text()
{
  return text;
}

KramCommonData KramParser::get_kram_obj()
{
  return kram_obj;
} 

