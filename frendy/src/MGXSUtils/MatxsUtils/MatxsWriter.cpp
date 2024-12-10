#include "MGXSUtils/MatxsUtils/MatxsWriter.hpp"

using namespace frendy;

// ***** MatxsWriter ***** //
//constructor
MatxsWriter::MatxsWriter(void)
{
  clear();
}

//destructor
MatxsWriter::~MatxsWriter(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsWriter::clear()
{
  matxs_obj.clear();

  file_name.clear();
  huse.clear();

  huse_flg   = 0;
  hsetid_flg = 0;

  VectorClearer clr_obj;
  clr_obj.clear_vec_array1_str(text);
  clr_obj.clear_vec_array1_str(hsetid);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsWriter::write_matxs()
{
  if( huse_flg > 0 )
  {
    matxs_obj.set_huse(huse);
  }

  if( hsetid_flg > 0 )
  {
    matxs_obj.set_hsetid(hsetid);
  }

  text = matxs_obj.write_data();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsWriter::write_matxs(string str_data)
{
  set_file_name(str_data);

  write_matxs();

  ofstream fout;
  fout.open(file_name.c_str());

  if( fout.fail() )
  {
    string class_name = "MatxsWriter";
    string func_name  = "write_matxs(string file_name)";

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

void MatxsWriter::set_file_name(string str_data)
{
  file_name = str_data;
}

void MatxsWriter::set_matxs_obj(MatxsCommonData data_obj)
{
  matxs_obj = data_obj;
}

void MatxsWriter::set_huse(string str_data)
{
  huse_flg = 1;
  huse     = str_data;
}

void MatxsWriter::set_hsetid(vector<string> str_vec)
{
  hsetid_flg = 1;
  hsetid     = str_vec;
}

string MatxsWriter::get_file_name()
{
  return file_name;
}

vector<string> MatxsWriter::get_text()
{
  write_matxs();

  return text;
}

MatxsCommonData MatxsWriter::get_matxs_obj()
{
  return matxs_obj;
} 

string MatxsWriter::get_huse()
{
  return huse;
}

vector<string> MatxsWriter::get_hsetid()
{
  return hsetid;
}
