#include "EndfUtils/OtherUtils/EndfTapeDivider.hpp"

using namespace frendy;

//constructor
EndfTapeDivider::EndfTapeDivider(void)
{
  endf_file_end = "                                                                     0 0  0    1";
  clear();
}

//destructor
EndfTapeDivider::~EndfTapeDivider(void)
{
  clear();
  endf_file_end.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void EndfTapeDivider::clear()
{
  file_name.clear();

  label_data.clear();

  mat_list.clear();
  clr_obj.clear_vec_array2_real(temp_list);
  clr_obj.clear_vec_array3_str(endf_data_each);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//call read endf file 
void EndfTapeDivider::read_endf_file()
{
  ifstream fin(file_name.c_str());

  //Output error message and abort if input file can't open.
  if(!fin) 
  {
    string class_name = "EndfTapeDivider";
    string func_name  = "read_endf_file()";

    string str_data   = "  file name : " + file_name;

    vector<string> err_com;
    err_com.push_back("There is no endf tape.");
    err_com.push_back("Reading endf tape data is skipped.");
    err_com.push_back(str_data);

    err_obj.output_caution(class_name, func_name, err_com);

    return;
  }

  //Check whether file_name is the ENDF-6 formatted file or not
  check_endf_format();

  //Copy endf file text data to vector<string>
  vector<string>          clip_data;
  vector<vector<string> > endf_data_each_mat;
  clr_obj.clear_vec_array1_str(clip_data);
  clr_obj.clear_vec_array2_str(endf_data_each_mat);
  int           blank_no  = 0;
  int           ele_no    = 0;
  int           label_flg = 0;
  Integer       mat_chk   = -999999;
  Integer       mat_pre   = -999999;
  Integer       mat_old   = -999999;
  string        line_data;
  const Integer char_length = 500;
  char *buf_char;
  buf_char = new char[char_length];
  while( !fin.eof() )
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
        string class_name = "EndfTapeDivider";
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
    mat_pre = mat_chk;

    fin.getline(buf_char, char_length);
    line_data = buf_char;
    clip_data.push_back(line_data);

    if( label_flg == 0 )
    {
      label_flg = 1;

      MultiParser mp_obj;
      int line_no = 0;
      mp_obj.read_text(clip_data, line_no, label_data);
    }

    read_mat_no(line_data, mat_chk);
    if( mat_old == -999999 )
    {
      mat_old = mat_chk;
    }

    if( mat_old != mat_chk && mat_chk > 0 )
    {
      //add endf data in each mat
      add_endf_data_each_mat(endf_data_each_mat, mat_old, mat_pre, clip_data);

      mat_old = mat_chk;
      ele_no++;
    }
  }

  for(int i=0; i<static_cast<int>(clip_data.size()); i++)
  {
    read_mat_no(clip_data[i], mat_chk);
    if( mat_chk > 0 )
    {
      break;
    }
  }
  clip_data.push_back(endf_file_end); //add dummy data at the end of vector
  add_endf_data_each_mat(endf_data_each_mat, mat_chk, mat_pre, clip_data);
  
  line_data.clear();
  clr_obj.clear_vec_array1_str(clip_data);
  delete [] buf_char;

  //Check temperature data at each data
  set_endf_data_each_temp(endf_data_each_mat);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void EndfTapeDivider::add_endf_data_each_mat(vector<vector<string> >& endf_data_each_mat,
                                             Integer mat_cur, Integer mat_pre, vector<string>& clip_data)
{
  int line_no = static_cast<int>(clip_data.size()) -1;
  vector<string> copy_data;
  copy_data.resize(line_no);
  for(int i=0; i<line_no; i++)
  {
    copy_data[i] = clip_data[i];
  }

  string next_data = clip_data[line_no];
  clr_obj.clear_vec_array1_str(clip_data);
  clip_data.push_back(next_data);
  next_data.clear();
  if( line_no <= 1 )
  {
    return;
  }

  if( line_no < 2 || mat_pre > 0 )
  {
    copy_data.push_back(endf_file_end);
  }

  int data_pos = search_mat_data(mat_cur);
  if( data_pos < 0 )
  {
    mat_list.push_back(mat_cur);

    endf_data_each_mat.push_back(copy_data);
  }
  else
  {
    for(int i=0; i<line_no; i++)
    {
      endf_data_each_mat[data_pos].push_back(copy_data[i]);
    }
  }
  clr_obj.clear_vec_array1_str(copy_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void EndfTapeDivider::check_endf_format()
{
  ifstream fin_chk(file_name.c_str());

  int           endf_flg     = 0;
  int           max_blank_no = 100000000;
  int           blank_no     = 0;

  string        line_data;
  const Integer char_length = 500;
  char *buf_char;
  buf_char = new char[char_length];
  while( !fin_chk.eof() )
  {
    fin_chk.getline(buf_char, char_length);
    line_data = buf_char;

    if( static_cast<int>(line_data.size()) == 0 )
    {
      blank_no++;
      if( blank_no > max_blank_no )
      {
        break;
      }
    }
    else
    {
      blank_no = 0;
      if( static_cast<int>(line_data.size()) >= 75 )
      {
        line_data = line_data.substr(70,5);
        std::string::size_type char_pos = line_data.find(" 1451");
        if( char_pos != string::npos )
        {
          endf_flg = 1;
          break;
        }
      }
    }
  }
  fin_chk.close();

  if( endf_flg == 0 )
  {
    string class_name = "EndfTapeDivider";
    string func_name  = "check_endf_format()";

    string str_data   = "  file name : " + file_name;

    vector<string> err_com;
    err_com.push_back("This file may not be the ENDF formatted file.");
    err_com.push_back("Please check the file format.");
    err_com.push_back(str_data);

    err_obj.output_caution(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int EndfTapeDivider::search_mat_data(Integer mat_no)
{
  int mat_pos = -1;
  for(int i=0; i<static_cast<int>(mat_list.size()); i++)
  {
    if( mat_list[i] == mat_no )
    {
      mat_pos = i;
      break;
    }
  }

  return mat_pos;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void EndfTapeDivider::set_endf_data_each_temp(vector<vector<string> >& endf_data_each_mat)
{
  EndfFileReader  efr_obj;
  MF01MT451Parser parser_obj;

  int i_max = static_cast<int>(mat_list.size());
  temp_list.resize(i_max);
  endf_data_each.resize(i_max);

  vector<string> clip_data;
  for(int i=0; i<i_max; i++)
  {
    //Devide endf data in each temperature
    int line_tot = static_cast<int>(endf_data_each_mat[i].size());
    int line_no  = 0;
    while( line_no < line_tot )
    {
      clip_data = get_file_data(endf_data_each_mat[i], line_no);
      if( static_cast<int>(clip_data.size()) > 0 )
      {
        endf_data_each[i].push_back(clip_data);

        //Get temperature data from MF=1, MT=451
        Real temp = 0.0;
        efr_obj.set_endf_data(clip_data);
        clr_obj.clear_vec_array1_str(clip_data);
        if( efr_obj.get_line_no(1, 451) > 0 )
        {
          parser_obj.set_text(efr_obj.get_data(1, 451));
          efr_obj.clear();
          temp = parser_obj.get_TEMP();
          parser_obj.clear();
        }
        temp_list[i].push_back(temp);
      }
    }
  }

  clr_obj.clear_vec_array2_str(endf_data_each_mat);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> EndfTapeDivider::get_file_data(Integer mat, vector<string>& endf_data, int& line_no)
{
  vector<string> clip_data;
  clr_obj.clear_vec_array1_str(clip_data);

  //line_no indicates the end of line numer which is already readed in endf_data
  //If i <= line_no, line number i has already readed.
  //If i >  line_no, line number i has not readed yet.
  Integer mat_line  = 0;
  int     break_flg = 0;
  int     i_max     = static_cast<int>(endf_data.size());
  if( i_max > line_no )
  {
    for(int i=line_no; i<i_max; i++)
    {
      read_mat_no(endf_data[i], mat_line);
      if( mat_line == mat )
      {
        clip_data.push_back(endf_data[i]);
      }
      else if( i != line_no && endf_data[i].substr(66, 9) == "   0 0  0" )
      {
        clip_data.push_back(endf_data[i]);
        break_flg = 1;
        line_no   = i+1;
        break;
      }
    }
  }

  if( break_flg == 0 )
  {
    line_no = i_max;
  }
  else
  {
    Integer mat_no = 0;
    while( line_no < i_max && mat_no <= 0 )
    {
      read_mat_no(endf_data[line_no], mat_no);
      if( mat_no <= 0 )
      {
        clip_data.push_back(endf_data[line_no]);
        line_no++;
      }
    }
  }

  return clip_data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> EndfTapeDivider::get_file_data(vector<string>& endf_data, int& line_no)
{
  vector<string> clip_data;
  clr_obj.clear_vec_array1_str(clip_data);

  //line_no indicates the end of line numer which is already readed in endf_data.
  //If i <= line_no, line number i has already readed.
  //If i >  line_no, line number i has not readed yet.
  int break_flg = 0;
  int i_max     = static_cast<int>(endf_data.size());
  if( i_max > line_no )
  {
    for(int i=line_no; i<i_max; i++)
    {
      clip_data.push_back(endf_data[i]);
      if( i != line_no && endf_data[i].substr(66, 9) == "   0 0  0" )
      {
        break_flg = 1;
        line_no   = i+1;
        break;
      }
    }
  }

  if( break_flg == 0 )
  {
    line_no = i_max;
  }
  else
  {
    Integer mat_no = 0;
    while( line_no < i_max && mat_no <= 0 )
    {
      read_mat_no(endf_data[line_no], mat_no);
      if( mat_no <= 0 )
      {
        clip_data.push_back(endf_data[line_no]);
        line_no++;
      }
    }
  }

  return clip_data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//read MAT, MF, and MT number
void EndfTapeDivider::read_mat_no(string& data, Integer& mat_int, Integer& mf_int, Integer& mt_int)
{
  read_mat_no(data, mat_int);

  //In the endf file, the number of characters must be 80.
  //So, this if statement will not be required.
  if( static_cast<Integer>(data.size()) >= 75 ) 
  {
    mf_int  = numeric_string_cast<Integer>(data.substr(70, 2));
    mt_int  = numeric_string_cast<Integer>(data.substr(72, 3));
  }
  else  
  {
    mf_int  = -1;
    mt_int  = -1;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//read MAT number
void EndfTapeDivider::read_mat_no(string& data, Integer& mat_int)
{
  //In the endf file, the number of characters must be 80.
  //So, this if statement will not be required.
  if( static_cast<Integer>(data.size()) >= 71 ) 
  {
    mat_int = numeric_string_cast<Integer>(data.substr(66, 4));
  }
  else  
  {
    mat_int = -1;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void EndfTapeDivider::set_file_name(string& name)
{
  clear();

  file_name = name;
  read_endf_file();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

string EndfTapeDivider::get_file_name()
{
  return file_name;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

string EndfTapeDivider::get_label_data()
{
  return label_data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> EndfTapeDivider::get_data_all()
{
  vector<string> endf_data_all;
  clr_obj.clear_vec_array1_str(endf_data_all);

  for(int i=0; i<static_cast<int>(endf_data_each.size()); i++)
  {
    for(int j=0; j<static_cast<int>(endf_data_each[i].size()); j++)
    {
      for(int k=0; k<static_cast<int>(endf_data_each[i][j].size()); k++)
      {
        endf_data_all.push_back(endf_data_each[i][j][k]);
      }
    }
  }
  
  return endf_data_all;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> EndfTapeDivider::get_data(Integer mat)
{
  vector<string> endf_data_each_mat;
  clr_obj.clear_vec_array1_str(endf_data_each_mat);

  for(int i=0; i<static_cast<int>(mat_list.size()); i++)
  {
    if( mat_list[i] == mat )
    {
      for(int j=0; j<static_cast<int>(temp_list[i].size()); j++)
      {
        int k_max = static_cast<int>(endf_data_each[i][j].size());
        for(int k=0; k<k_max; k++)
        {
          endf_data_each_mat.push_back(endf_data_each[i][j][k]);
        }
      }
    }
  }

  return endf_data_each_mat;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> EndfTapeDivider::get_data_without_specified_mat(Integer mat)
{
  vector<string> endf_data_without_mat;
  clr_obj.clear_vec_array1_str(endf_data_without_mat);

  for(int i=0; i<static_cast<int>(mat_list.size()); i++)
  {
    if( mat_list[i] != mat && mat_list[i] > 0 )
    {
      for(int j=0; j<static_cast<int>(temp_list[i].size()); j++)
      {
        int k_max = static_cast<int>(endf_data_each[i][j].size());
        if( mat_list[i] == 1 && k_max == 2 ) //skip title data
        {
          continue; 
        }
        for(int k=0; k<k_max; k++)
        {
          endf_data_without_mat.push_back(endf_data_each[i][j][k]);
        }
      }
    }
  }

  return endf_data_without_mat;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> EndfTapeDivider::get_designated_temp_data(Integer mat, Real temp)
{
  Real diff;
  if( fabs(temp) < min_ene_dif)
  {
    temp = 0.0;
  }

  int no_mat_flg = -1;
  for(int case_no=0; case_no<2; case_no++)
  {
    if( case_no == 0 )
    {
      if( fabs(temp) < min_ene_dif)
      {
        diff = 1.0E-4;
      }
      else
      {
        diff = 1.0E-4 * fabs(temp);
      }
    }
    else
    {
      if( fabs(temp) < min_ene_dif)
      {
        diff = 1.0E-2;
      }
      else
      {
        diff = 1.0E-2 * fabs(temp);
      }
    }

    for(int i=0; i<static_cast<int>(mat_list.size()); i++)
    {
      if( mat_list[i] == mat )
      {
        no_mat_flg = i;

        int j_max = static_cast<int>(temp_list[i].size());
        for(int j=0; j<j_max; j++)
        {
          if( fabs(temp_list[i][j] - temp) < diff )
          {
            if( case_no > 0 )
            {
              string class_name = "EndfTapeDivider";
              string func_name  = "get_designated_temp_data(Integer mat, Real temp)";
              ostringstream oss01, oss02, oss03;
              oss01 << temp;
              oss02 << temp_list[i][j];
              oss03 << fabs((temp_list[i][j] - temp)/temp);
              string str_data01 = "Temperature (input) : " + oss01.str();
              string str_data02 = "Temperature (ENDF)  : " + oss02.str();
              string str_data03 = "Relative difference : " + oss03.str();
              vector<string> err_com;
              err_com.push_back("Relative temperature difference is larger than 1.0E-4");
              err_com.push_back("You may set the wrong temperature value.");
              err_com.push_back(str_data01);
              err_com.push_back(str_data02);
              for(int k=0; k<j_max; k++)
              {
                ostringstream oss04, oss05, oss06;
                oss04 << temp_list[i][k];
                oss05 << k+1;
                oss06 << j_max;
                string str_data04 = "Temperature list    : " + oss04.str()
                                  + "\t(" + oss05.str() + "/" + oss06.str() + ")";
                err_com.push_back(str_data04);
              }
              err_obj.output_caution(class_name, func_name, err_com);
            }
            return endf_data_each[i][j];
          }
        }
      }
    }  
  } 

  string class_name = "EndfTapeDivider";
  string func_name  = "get_designated_temp_data(Integer mat, Real temp)";
  vector<string> err_com;
  if( no_mat_flg < 0 )
  {
    ostringstream oss01;
    oss01 << mat;
    string str_data01 = "Material number (input) : " + oss01.str();
    err_com.push_back("There is no material data in this ENDF file.");
    err_com.push_back("Please check the material number or ENDF file.");
    err_com.push_back(str_data01);
    for(int i=0; i<static_cast<int>(mat_list.size()); i++)
    {
      ostringstream oss02, oss03, oss04;
      oss02 << mat_list[i];
      oss03 << i+1;
      oss04 << static_cast<int>(mat_list.size());
      string str_data02 = "Material number list    : " + oss02.str()
                        + "\t(" + oss03.str() + "/" + oss04.str() + ")";
    }
  }
  else
  {
    ostringstream oss01, oss02;
    oss01 << temp;
    string str_data01 = "Temperature (input) : " + oss01.str();
    err_com.push_back("Relative temperature difference is larger than 1.0E-2");
    err_com.push_back("Please check the temperature or ENDF file.");
    err_com.push_back(str_data01);
    for(int i=0; i<static_cast<int>(temp_list[no_mat_flg].size()); i++)
    {
      ostringstream oss02, oss03, oss04;
      oss02 << temp_list[no_mat_flg][i];
      oss03 << i+1;
      oss04 << static_cast<int>(temp_list[no_mat_flg].size());
      string str_data02 = "Temperature list    : " + oss02.str()
                        + "\t(" + oss03.str() + "/" + oss04.str() + ")";
      err_com.push_back(str_data02);
    }
  }
  err_obj.output_runtime_error(class_name, func_name, err_com);

  vector<string> text_void;
  clr_obj.clear_vec_array1_str(text_void);
  return text_void;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> EndfTapeDivider::get_nearby_temp_data(Integer mat, Real temp)
{
  //Get closed tempearture data not exceeded temp.
  int mat_pos, temp_pos;
  get_nearby_mat_temp_pos(mat, temp, mat_pos, temp_pos);

  if( mat_pos < 0 || temp_pos < 0 )
  {
    string class_name = "EndfTapeDivider";
    string func_name  = "get_nearby_temp_data(Integer mat, Real temp)";

    ostringstream oss01, oss02;
    oss01 << mat;
    oss02 << setw(6) << std::showpoint << temp;
    string str_data01 = "File name             : " + file_name;
    string str_data02 = "MAT (material number) : " + oss01.str();
    string str_data03 = "Temperature           : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("The nuclear data such MAT and temperature data is not found in this ENDF file.");
    err_com.push_back("");
    err_com.push_back("The avalable MAT number and temperature is as follows:");
    err_com.push_back("  MAT / temp");
    for(int i=0; i<static_cast<int>(mat_list.size()); i++)
    {
      for(int j=0; j<static_cast<int>(temp_list[i].size()); j++)
      {
        ostringstream oss03, oss04;
        oss03 << mat_list[i];
        oss04 << setw(6) << std::showpoint << temp_list[i][j];
        string str_data04 = "  " + oss03.str() + " / " + oss04.str();
        err_com.push_back(str_data04);
      }
    }

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  return endf_data_each[mat_pos][temp_pos];
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void EndfTapeDivider::get_nearby_mat_temp_pos(Integer mat, Real temp,
                                              int& mat_pos, int& temp_pos)
{
  mat_pos  = -1;
  temp_pos = -1;

  int i_max    = static_cast<int>(mat_list.size());
  for(int i=0; i<i_max; i++)
  {
    if( mat_list[i] == mat || mat < 0 )
    {
      mat_pos = i;

      int  temp_dif_pos = -1;
      Real temp_dif_min = 1.0E+30;
      for(int j=0; j<static_cast<int>(temp_list[i].size()); j++)
      {
        Real temp_dif = temp - temp_list[i][j];
        if( fabs(temp_dif) < 0.1 || temp < -1.0*min_value )
        {
          temp_pos = j;
          break;
        }
        else if( temp_dif > min_value && temp_dif < temp_dif_min )
        {
          temp_dif_pos = j;
          temp_dif_min = temp_dif;
        }
      }

      if( temp_pos < 0 )
      {
        temp_pos = temp_dif_pos;
      }

      break;
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> EndfTapeDivider::get_data(Integer mat, int file_no)
{
  for(int i=0; i<static_cast<int>(mat_list.size()); i++)
  {
    if( mat_list[i] == mat )
    {
      if( static_cast<int>(endf_data_each[i].size()) > file_no )
      {
        return endf_data_each[i][file_no];
      }
    }
  }

  vector<string> text_void;
  clr_obj.clear_vec_array1_str(text_void);
  return text_void;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<vector<string> > EndfTapeDivider::get_data_all(Integer mat)
{
  for(int i=0; i<static_cast<int>(mat_list.size()); i++)
  {
    if( mat_list[i] == mat )
    {
      return endf_data_each[i];
    }
  }

  vector<vector<string> > text_void;
  clr_obj.clear_vec_array2_str(text_void);
  return text_void;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<Integer> EndfTapeDivider::get_mat_list()
{
  return mat_list;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<Real> EndfTapeDivider::get_temp_list(Integer mat)
{
  vector<Real> temp_list_each_mat;
  temp_list_each_mat.clear();

  for(int i=0; i<static_cast<int>(mat_list.size()); i++)
  {
    if( mat_list[i] == mat )
    {
      temp_list_each_mat = temp_list[i];
      break;
    }
  }

  return temp_list_each_mat;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<vector<Real> > EndfTapeDivider::get_temp_list()
{
  return temp_list;
}

