#include "EndfUtils/EndfFileReader/EndfFileReader.hpp"

using namespace frendy;

//========== private function ==========//
//constructor
EndfFileReader::EndfFileReader(void)
{
  clear();
}

//destructor
EndfFileReader::~EndfFileReader(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void EndfFileReader::clear()
{
  file_name.clear();
  clr_obj.clear_vec_array1_str(endf_data_all);
  clr_obj.clear_vec_array1_str(endf_data);
  mf_data_all.clear();
  mt_data_all.clear();
  mt_no_list.clear();
  endf_line_no = 0;
  mat_no       = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//call read endf file 
void EndfFileReader::read_endf_file()
{
  ifstream fin(file_name.c_str());

  //Output error message and abort if input file can't open.
  if(!fin) 
  {
    string class_name = "EndfFileReader";
    string func_name  = "read_endf_file()";

    vector<string> err_com;
    err_com.push_back("There is no endf file.");

    string str_data = "File name : " + file_name;
    err_com.push_back(str_data);
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //Copy endf file text data to vector<string>
  string line_data;
  const Integer char_length = 500;
  char *buf_char;
  buf_char = new char[char_length];
  mat_no   = 0;
  int blank_no  = 0;
  while(!fin.eof())
  {
    if( line_data.size() > 0 )
    {
      blank_no = 0;
    }
    else
    {
      blank_no++;

      if( blank_no > 100000000 )
      {
        string class_name = "EndfFileReader";
        string func_name  = "read_endf_file()";

        string str_data   = "  file name : " + file_name;

        vector<string> err_com;
        err_com.push_back("A huge number of blank line data is found.");
        err_com.push_back("The file name may not be the directory name.");
        err_com.push_back("Please check the file name is collect or not.");
        err_com.push_back("");
        err_com.push_back(str_data);
        err_com.push_back("");
        err_com.push_back("FRENDY recognizes that after // is comment line.");
        err_com.push_back("Please check that the file name contains // or not.");

        err_obj.output_runtime_error(class_name, func_name, err_com);
      }
    }

    //getline(fin, line_data);
    fin.getline(buf_char, char_length);
    line_data = buf_char;

    Integer mf_chk, mt_chk;
    read_mf_mt_no(line_data, mf_chk, mt_chk);

    endf_data_all.push_back(line_data);
    mf_data_all.push_back(mf_chk);
    mt_data_all.push_back(mt_chk);

    if( mat_no <= 0 && mf_chk > 0 && mt_chk > 0 )
    {
      read_mat_no(line_data);
    }
  }
  line_data.clear();
  delete [] buf_char;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//read MF and MT number from endf_data_all
void EndfFileReader::read_mf_mt_no(string& data, Integer &mf_int, Integer &mt_int)
{
  //In the endf file, the number of characters must be 80.
  //So, this if statement will not be required.
  if( static_cast<Integer>(data.size()) >= 75 ) 
  {
    //string mf_str = data.substr(70, 2);
    //string mt_str = data.substr(72, 3);
    //mf_int = numeric_string_cast<Integer>(mf_str);
    //mt_int = numeric_string_cast<Integer>(mt_str);
    //mf_str.clear();
    //mt_str.clear();
    mf_int = numeric_string_cast<Integer>(data.substr(70, 2));
    mt_int = numeric_string_cast<Integer>(data.substr(72, 3));
  }
  else  
  {
    mf_int = -1;
    mt_int = -1;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//read MF and MT number from endf_data_all
void EndfFileReader::read_mat_no(string& data)
{
  mat_no = numeric_string_cast<Integer>(data.substr(66, 4));
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//clip endf file from endf_data_all to endf_data
void EndfFileReader::clip_endf_file(Integer MF, Integer MT)
{
  //Initializing string data
  clr_obj.clear_vec_array1_str(endf_data);

  int read_flg   = 0;
  int mt_end_flg = 0;
  for(int i=0; i<static_cast<int>(endf_data_all.size()); i++)
  {
    if(mf_data_all[i] == MF)
    {
      if(mt_data_all[i] == MT)
      {
        if( read_flg > 0 && mt_end_flg > 0 )
        {
          string class_name = "EndfFileReader";
          string func_name  = "clip_endf_file(Integer MF, Integer MT)";

          ostringstream oss01, oss02;
          oss01 << i+1;
          oss02 << static_cast<int>(endf_data_all.size());

          string str_data01 = "File name : " + file_name;
          string str_data02 = "Line no   : " + oss01.str() + " / " + oss02.str();

          vector<string> err_com;
          err_com.push_back(str_data01);
          err_com.push_back(str_data02);
          err_com.push_back("");
          err_com.push_back("The text data (i-2, i-1, i)");
          err_com.push_back(endf_data_all[i-2]);
          err_com.push_back(endf_data_all[i-1]);
          err_com.push_back(endf_data_all[i]);
          err_com.push_back("");
          err_com.push_back("The input MT is found afther the MT end.");
          err_com.push_back("This MT data is overlapped.");
          err_com.push_back("The first data is only persed.");
          err_obj.output_caution(class_name, func_name, err_com);

          break;
        }

        read_flg = 1;
        endf_data.push_back( endf_data_all[i] );
      }

      if( read_flg > 0 && mt_data_all[i] != MT )
      {
        mt_end_flg = 1;
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//search all MT number included in file number MF.
void  EndfFileReader::search_mt_number(Integer MF)
{
  Integer prev_mt = -987654321;
  mt_no_list.clear();

  for(int i=0; i<static_cast<int>(endf_data_all.size()); i++)
  {
    if( mf_data_all[i] == MF)
    {
      if(prev_mt != mt_data_all[i])
      {
        if( mt_data_all[i] > 0)
        {
          mt_no_list.push_back(mt_data_all[i]);
          prev_mt = mt_data_all[i];
        } 
      } 
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//========== public function ==========//
//read the endf file name from user input
void EndfFileReader::set_file_name(string& name)
{
  clear();

  file_name = name;
  read_endf_file();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//set endf text data
void EndfFileReader::set_endf_data(vector<string>& text)
{
  clear();
  //file_name = "direct_input";

  //Copy endf file text data to vector<string>
  endf_data_all = text;
  int i_max = static_cast<int>(text.size());
  for(int i=0; i<i_max; i++)
  {
    Integer mf_chk, mt_chk;
    read_mf_mt_no(text[i], mf_chk, mt_chk);
    mf_data_all.push_back(mf_chk);
    mt_data_all.push_back(mt_chk);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//return the endf file name which read by set_file_name
string EndfFileReader::get_file_name()
{
  return file_name;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//return total line number of the endf file
int EndfFileReader::get_line_no_all()
{
  return static_cast<int>(endf_data_all.size());
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//return all text data of the endf file
vector<string> EndfFileReader::get_data_all()
{
  return endf_data_all;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//return line number of the part of the endf file(MF, MT)
int EndfFileReader::get_line_no(Integer MF, Integer MT)
{
  endf_line_no = 0;

  for(int i=0; i<static_cast<int>(endf_data_all.size()); i++)
  {
    if( mf_data_all[i] == MF )
    {
      if( mt_data_all[i] == MT )
      {
        endf_line_no++;
      }
    }
  }
  return endf_line_no;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//return text data of the part of the endf file(MF, MT)
vector<string> EndfFileReader::get_data(Integer MF, Integer MT)
{
  //call clip endf file from endf_data_all to endf_data
  clip_endf_file(MF, MT);

  return endf_data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//return initial MAT number
Integer EndfFileReader::get_mat_no()
{
  return mat_no;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//return all MT number included in file number MF.
vector<Integer> EndfFileReader::get_mt_list(Integer MF)
{
  search_mt_number(MF);

  sort(mt_no_list.begin(), mt_no_list.end());
 
  return mt_no_list;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//return all MF number included
vector<Integer> EndfFileReader::get_mf_list()
{
  vector<Integer> mf_no = mf_data_all;
  sort(mf_no.begin(), mf_no.end());

  vector<Integer> mf_no_list;
  int i_max = static_cast<int>(mf_no.size());
  if( i_max == 0 )
  {
    return mf_no_list;
  }

  Integer mf_pre = mf_no[0];
  if( mf_pre > 0 )
  {
    mf_no_list.push_back(mf_pre);
  }

  for(int i=1; i<i_max; i++)
  {
    if( mf_no[i] != mf_pre )
    {
      mf_pre = mf_no[i];
      if( mf_pre > 0 )
      {
        mf_no_list.push_back(mf_pre);
      }
    }
  }

  sort(mt_no_list.begin(), mt_no_list.end());

  return mf_no_list;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
