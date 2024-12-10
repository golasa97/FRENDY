#include "EndfUtils/EndfFileReader/StringConverter.hpp"

using namespace frendy;

//constructor
StringConverter::StringConverter(void)
{
  value_str.resize(value_str_size);
  value_str[ 0] = "0";
  value_str[ 1] = "1";
  value_str[ 2] = "2";
  value_str[ 3] = "3";
  value_str[ 4] = "4";
  value_str[ 5] = "5";
  value_str[ 6] = "6";
  value_str[ 7] = "7";
  value_str[ 8] = "8";
  value_str[ 9] = "9";
  value_str[10] = "e";
  value_str[11] = "E";
  value_str[12] = "+";
  value_str[13] = "-";
  value_str[14] = ".";

  buf_all.clear();
  parse_pos = 0;
}

//destructor
StringConverter::~StringConverter(void)
{
  for(int i=0; i<value_str_size; i++)
  {
    value_str[i].clear();
  }
  value_str.clear();

  buf_all.clear();
  parse_pos = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void StringConverter::cut_text(string& buf, vector<string>& strC, vector<string>& strM)
{
  buf_all   = buf;
  parse_pos = 0;

  strC.resize(c_size);
  for(int i=0; i<c_size; i++)
  {
    strC[i] = buf.substr(i*11,11);
  }

  strM.resize(m_size);
  strM[0] = buf.substr(66,4);
  strM[1] = buf.substr(70,2);
  strM[2] = buf.substr(72,3);
  strM[3] = "0"; //dummy data
  if( static_cast<int>(buf.length()) > 76 )
  {
    strM[3] = buf.substr(75,5); //This data is not use for calculation.
  }

  for(int i=0; i<c_size; i++)
  {
    parse_pos++;
    string_check(strC[i]);
  }
  for(int i=0; i<m_size; i++)
  {
    parse_pos++;
    string_check(strM[i]);
  }
  buf_all.clear();
  parse_pos = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void StringConverter::cut_text(string& buf, vector<string>& strC)
{
  buf_all   = buf;
  parse_pos = 0;

  strC.resize(c_size);
  for(int i=0; i<c_size; i++)
  {
    strC[i] = buf.substr(i*11,11);
  }

  for(int i=0; i<c_size; i++)
  {
    parse_pos++;
    string_check(strC[i]);
  }
  buf_all.clear();
  parse_pos = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//This member function is check whether the string is numerical value or not.
//However, this function can not check all data.
//Forexample, this function recognize numerical value following case;
//e001, e+-, e.1, 1+-1, +-, ., and so on.
//Please be careful that using this function.
void StringConverter::string_check(string& buf)
{
  space_eraser(buf);

  vector<Integer> value_count;
  value_count.resize(200);
  int value_no = 0;

  Integer value_chk = 0; //flag(1:numeric character is exist before)
  Integer space_chk = 0; //flag(1:space is exist after numeric character)
  Integer blank_chk = 0; //Number of space (To check whether string data is constructed by all space)
  for(int i=0; i<static_cast<int>(buf.length()); i++)
  {
    Integer alpha_chk = 0; //flag(1:numeric character)
    if(buf.substr(i,1) != " " )
    {
      for(int j=0; j<value_str_size; j++)
      {
        if(buf.substr(i,1) == value_str[j]) //check numeric charactor or not
        {
          value_count[value_no] = j;
          value_no++;
          alpha_chk = 1;
          break;
        }
      }

      if( alpha_chk == 0 || space_chk > 0 ) 
      {
        string class_name = "StringConverter";
        string func_name  = "string_check(string& buf)";

        string str_data = "String data : " + buf;

        vector<string> err_com;
        err_com.push_back(str_data);
        if( static_cast<int>(buf_all.length()) > 0 )
        {
          string str_add = "Line data in cluding this string : " + buf_all;
          err_com.push_back(str_add);

          ostringstream oss;
          oss << parse_pos;
          str_add = "Data position : " + oss.str();
          err_com.push_back(str_add);
        }

        if( alpha_chk == 0 )
        {
          err_com.push_back("This string data contains alpha character.");
        }
        if( space_chk > 0 ) //check divided numerical character, e.g., "1 1".
        {
          err_com.push_back("This string data construncts two or more value.");
        }

        err_obj.output_runtime_error(class_name, func_name, err_com);
      }
      else if( space_chk == 0 ) 
      {
        value_chk = 1; 
      }
    }
    else
    {
      blank_chk++; 
      if( value_chk > 0 ) 
      {
        space_chk = 1; 
      }
    }
  }

  Integer index_chk = 0; //count the number of e/E
  Integer sign_chk  = 0; //count the number of +/-
  Integer point_chk = 0; //count the number of .
  for(int i=0; i<value_no; i++)
  {
    if( value_count[i] == 10 || value_count[i] == 11 )
    {
      index_chk++;
    }
    else if( value_count[i] == 12 || value_count[i] == 13 )
    {
      sign_chk++;
    }
    else if( value_count[i] == 14 )
    {
      point_chk++;
    }
  }
  if( index_chk > 1 || sign_chk > 2 || point_chk > 2 )
  {

    string class_name = "StringConverter";
    string func_name  = "string_check(string& buf)";

    string str_data = "String data : " + buf;

    vector<string> err_com;
    err_com.push_back(str_data);
    if( static_cast<int>(buf_all.length()) > 0 )
    {
      string str_add = "Line data in cluding this string : |" + buf_all + "|";
      err_com.push_back(str_add);

      ostringstream oss;
      oss << parse_pos;
      str_add = "Data position : " + oss.str();
      err_com.push_back(str_add);
    }
    err_com.push_back("This string data may not be numerical value.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //If string data is constructed by all space, string date set "0.0".
  if(blank_chk == static_cast<Integer>(buf.length()))
  {
    buf = "0"; 
  }
  value_count.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void StringConverter::space_eraser(string& buf)
{
  vector<Integer> space_no_chk;
  space_no_chk.resize(200);
  int space_no = 0;

  //serch unwanted space
  for(int i=1; i<static_cast<int>(buf.length())-1; i++)
  {
    if( buf.substr(i,1) == " " )
    {
      if( buf.substr(i-1,1)==" " || buf.substr(i-1,1)=="+" || buf.substr(i-1,1)=="-" ||
          buf.substr(i+1,1)==" " || buf.substr(i+1,1)=="+" || buf.substr(i+1,1)=="-" )
      {
        space_no_chk[space_no] = i;
        space_no++;
      }
    }
  }

  //erase unwanted space
  if( space_no > 0 ) 
  {
    for(int i=space_no-1; i>=0; i--)
    {
      buf.erase(space_no_chk[i],1);
    }
  }
  space_no_chk.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void StringConverter::read_line(string& buf, vector<Real>& C_value, vector<Integer>& M_value)
{
  vector<string> strC, strM;
  cut_text(buf, strC, strM);

  C_value.clear();
  M_value.clear();

  C_value.resize(c_size);
  M_value.resize(m_size);
  for(int i=0; i<c_size; i++)
  {
    C_value[i] = numeric_string_cast<Real>(strC[i]);
  }

  for(int i=0; i<m_size; i++)
  {
    M_value[i] = numeric_string_cast<Integer>(strM[i]);
  }
  strC.clear();
  strM.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void StringConverter::read_line(string& buf, vector<Real>& C_value)
{
  vector<string> strC;
  cut_text(buf, strC);

  C_value.clear();

  C_value.resize(c_size);
  for(int i=0; i<c_size; i++)
  {
    C_value[i] = numeric_string_cast<Real>(strC[i]);
  }
  strC.clear();
}

