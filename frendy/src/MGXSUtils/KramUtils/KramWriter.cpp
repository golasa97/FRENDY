#include "MGXSUtils/KramUtils/KramWriter.hpp"

using namespace frendy;

// ***** KramWriter ***** //
//constructor
KramWriter::KramWriter(void)
{
  clear();
}

//destructor
KramWriter::~KramWriter(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void KramWriter::clear()
{
  kram_obj.clear();

  file_name.clear();

  VectorClearer clr_obj;
  clr_obj.clear_vec_array1_str(text);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void KramWriter::write_kram()
{
  text = kram_obj.write_data();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void KramWriter::write_kram(string str_data)
{
  set_file_name(str_data);

  write_kram();

  ofstream fout;
  fout.open(file_name.c_str());

  if( fout.fail() )
  {
    string class_name = "KramWriter";
    string func_name  = "write_kram(string file_name)";

    string str_data = "  Output file name : " + file_name;

    vector<string> err_com;
    err_com.push_back("Output file can not be open.");
    err_com.push_back("Please check the file name, directory name or access authority.");
    err_com.push_back(str_data);

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  int i_max = static_cast<int>(text.size());
  for(int i=0; i<i_max; i++)
  {
    fout << text[i] << endl;
  }
  fout.close();
}

void KramWriter::set_file_name(string str_data)
{
  file_name = str_data;
}

void KramWriter::set_kram_obj(KramCommonData data_obj)
{
  kram_obj = data_obj;
}

string KramWriter::get_file_name()
{
  return file_name;
}

vector<string> KramWriter::get_text()
{
  write_kram();

  return text;
}

KramCommonData KramWriter::get_kram_obj()
{
  return kram_obj;
} 

