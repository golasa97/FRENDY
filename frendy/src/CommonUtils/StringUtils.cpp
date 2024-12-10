#include "CommonUtils/StringUtils.hpp"

using namespace frendy;

//constructor
StringUtils::StringUtils(void)
{
  clear();

  space_list    = " 　,\t\v\r\n";
  //linefeed_list = "\r\n";
  linefeed_list = "\r\n";

  quote_single = "'";
  quote_double = "\"";
  quote_list   = quote_single+quote_double;

  bracket_sta        = "(";
  bracket_end        = ")";
  curly_bracket_sta  = "{";
  curly_bracket_end  = "}";
  angled_bracket_sta = "[";
  angled_bracket_end = "]";
}

//destructor
StringUtils::~StringUtils(void)
{
  clear();

  space_list.clear();
  linefeed_list.clear();

  quote_list.clear();
  quote_single.clear();
  quote_double.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void StringUtils::clear()
{
  data_no     = 0;
  data_no_tot = 0;

  quote_pos_list.clear();

  vector<string>().swap(text_data);
  vector<vector<string> >().swap(div_data);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

string StringUtils::trim_space(string str_data)
{
  return trim_data(str_data, space_list);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

string StringUtils::trim_data(string str_data, string trim_character)
{
  string::size_type left_pos = str_data.find_first_not_of(trim_character.c_str());

  if( left_pos != string::npos )
  {
    string::size_type right_pos = str_data.find_last_not_of(trim_character.c_str());

    str_data = str_data.substr(left_pos, right_pos-left_pos+1);
  }
  else if( str_data.find_first_of(trim_character.c_str()) != string::npos )
  {
    str_data.clear();
  }

  return str_data;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

string StringUtils::replace_space(string str_data, string replace_data)
{
  str_data = trim_space(str_data);

  string::size_type space_pos = str_data.find_last_of(space_list.c_str());
  int space_pos_pre = static_cast<int>(space_pos);

  while( space_pos != string::npos )
  {
    if( static_cast<int>(space_pos) == space_pos_pre - 1 )
    {
      str_data = str_data.substr(0, space_pos) + str_data.substr(space_pos+1);
    }
    else
    {
      str_data = str_data.substr(0, space_pos) + replace_data + str_data.substr(space_pos+1);
    }

    space_pos_pre = static_cast<int>(space_pos);
    space_pos     = str_data.find_last_of(space_list.c_str());
  }

  return str_data;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

string StringUtils::basename(string str_data)
{
  if( static_cast<int>(str_data.size()) == 0 )
  {
    return str_data;
  }

  str_data = trim_space(str_data);

  if( str_data.find_last_of("/\\") != string::npos )
  {
    //Similar to the basename command in Linux
    str_data = str_data.substr(str_data.find_last_of("/\\")+1);
  }

  return str_data;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

string StringUtils::basename(string str_data, string suffix)
{
  if( static_cast<int>(str_data.size()) == 0 )
  {
    return str_data;
  }

  str_data = basename(str_data);
  str_data = remove_suffix(str_data, suffix);

  return str_data;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

string StringUtils::basename_without_suffix(string str_data)
{
  if( static_cast<int>(str_data.size()) == 0 )
  {
    return str_data;
  }

  str_data = basename(str_data);

  if( str_data.find_last_of(".") != string::npos )
  {
    if( static_cast<int>(str_data.find_last_of(".")) != 0 )
    {
      string suffix = str_data.substr(str_data.find_last_of("."));
      str_data = remove_suffix(str_data, suffix);
    }
  }

  return str_data;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

string StringUtils::remove_suffix(string str_data, string suffix)
{
  int str_char_no    = static_cast<int>(str_data.length());
  int suffix_char_no = static_cast<int>(suffix.length());

  string::size_type left_pos = str_data.rfind(suffix.c_str());

  if( static_cast<int>(left_pos) == str_char_no - suffix_char_no )
  {
    str_data = str_data.substr(0, str_char_no-suffix_char_no);
  }

  return str_data;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

string StringUtils::remove_after_space(string str_data)
{
  str_data = trim_space(str_data);

  string::size_type space_pos = str_data.find_first_of(space_list.c_str());
  if( space_pos != string::npos )
  {
    str_data = str_data.substr(0, space_pos);
  }

  return str_data;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

string StringUtils::get_formatted_string_data(string str_data, int char_no)
{
  //char_no > 0 :       str_data + " "
  //char_no < 0 : " " + str_data

  string str_mod;
  str_mod.clear();

  int char_no_abs = char_no;
  if( char_no_abs < 0 )
  {
    char_no_abs *= -1;
  }

  int str_size = static_cast<int>(str_data.size());
  if( str_size > char_no_abs )
  {
    str_mod = str_data.substr(0, char_no_abs);
  }
  else
  {
    str_mod = str_data;
    if( char_no > 0 )
    {
      for(int i=str_size; i<char_no_abs; i++)
      {
        str_mod = str_mod + " ";
      }
    }
    else
    {
      for(int i=str_size; i<char_no_abs; i++)
      {
        str_mod = " " + str_mod;
      }
    }
  }

  return str_mod;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

string StringUtils::get_formatted_real_data(Real real_data, int char_no)
{
  string str_data;
  str_data.clear();

  int char_no_abs = char_no;
  if( char_no_abs < 0 )
  {
    char_no_abs *= -1;
  }

  int decimal_part_no = char_no_abs - 7; //" 1.23456E+78" -> " 1." + "23456" + "E+78"
  if( decimal_part_no < 0 )
  {
    string class_name = "StringUtils";
    string func_name  = "get_formatted_real_data(Real real_data, int char_no)";

    ostringstream oss_char_no;
    oss_char_no << char_no_abs;

    vector<string> err_com;
    string str_data01 = "Maximum character number : " + oss_char_no.str();
    err_com.push_back(str_data01);
    err_com.push_back("The maximum character number (char_no) must be larger than or equal to 7.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  ostringstream oss_real;
  oss_real.precision(decimal_part_no);
  oss_real.setf(ios::scientific);
  oss_real.setf(ios::showpoint);
  oss_real << real_data;

  str_data = "";
  if( real_data >= 0.0 )
  {
    str_data = " ";
  }

  str_data = str_data + oss_real.str();

  return str_data;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

string StringUtils::get_formatted_int_data(int int_data, int char_no)
{
  //char_no > 0 :       int_data + " "
  //char_no < 0 : " " + int_data

  string str_data;
  str_data.clear();

  int char_no_abs = char_no;
  if( char_no_abs < 0 )
  {
    char_no_abs *= -1;
  }

  ostringstream oss;
  oss << int_data;

  str_data = oss.str();
  if( static_cast<int>(str_data.size()) > char_no_abs )
  {
    string class_name = "StringUtils";
    string func_name  = "get_formatted_int_data(int int_data, int char_no)";

    ostringstream oss_char_no;
    oss_char_no << char_no;

    vector<string> err_com;
    string str_data01 = "Maximum character number : " + oss_char_no.str();
    string str_data02 = "int_data                 : " + oss.str();
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("The number of digits of int_data is larger than the absolute value of the maximum character number.");
    err_com.push_back("The string data is not collect.");
    err_com.push_back("Please check int_data or modify char_no");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  str_data = get_formatted_string_data(str_data, char_no);

  return str_data;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

string StringUtils::get_merged_string_vector_data(vector<string> str_vec)
{
  string str_data = "";

  int i_max = static_cast<int>(str_vec.size());
  for(int i=0; i<i_max; i++)
  {
    if( static_cast<int>(str_vec[i].length()) == 0 )
    {
      continue;
    }
    str_data = str_data + str_vec[i];
  }

  return str_data;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> StringUtils::get_merged_string_vector_data(vector<string> str_vec, int data_no)
{
  vector<string> str_mod;
  str_mod.clear();

  string str_data = "";

  int i_max   = static_cast<int>(str_vec.size());
  int str_pos = 0;
  for(int i=0; i<i_max; i++)
  {
    str_data = str_data + str_vec[i];
    if( (str_pos + 1)%data_no == 0 )
    {
      str_mod.push_back(str_data);
      str_data.clear();
      str_pos = 0;
    }
    else
    {
      str_pos++;
    }
  }

  if( str_pos > 0 )
  {
    str_mod.push_back(str_data);
  }

  return str_mod;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void StringUtils::add_string_vector_data(vector<string>& text, vector<string> text_add)
{
  int i_max = static_cast<int>(text_add.size());
  for(int i=0; i<i_max; i++)
  {
    text.push_back(text_add[i]);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> StringUtils::divide_string_data(string str_data, int data_width)
{
  vector<string> str_vec;
  str_vec.clear();

  while( static_cast<int>(str_data.length()) > 0 )
  {
    string str_add = str_data.substr(0, data_width);
    str_vec.push_back(str_add);
    str_add.clear();

    str_data = str_data.substr(data_width);

    if( static_cast<int>(str_data.length()) < data_width )
    {
      data_width = static_cast<int>(str_data.length());
    }
  }

  return str_vec;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> StringUtils::divide_string_data(string str_data, int data_width, int max_char_no)
{
  str_data = get_formatted_string_data(str_data, max_char_no);

  return divide_string_data(str_data, data_width);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> StringUtils::divide_string_data_by_linefeed_code(string str_data)
{
  vector<string> str_vec;
  str_vec.clear();

  vector<int> pos_vec;
  string::size_type linefeed_pos = str_data.find_first_of(linefeed_list);
  while( linefeed_pos != string::npos )
  {
    pos_vec.push_back(linefeed_pos);

    linefeed_pos = str_data.find_first_of(linefeed_list, linefeed_pos+1);
  }

  int i_max = static_cast<int>(pos_vec.size());
  str_vec.resize(i_max);

  int pos_cur = 0;
  int pos_pre = 0;
  for(int i=0; i<i_max; i++)
  {
    pos_cur = pos_vec[i];
    str_vec[i] = str_data.substr(pos_pre, pos_cur - pos_pre);
    pos_pre = pos_cur + 1;
  }

  str_data = str_data.substr(pos_pre);
  if( static_cast<int>(str_data.length()) > 0 )
  {
    str_vec.push_back(str_data);
  }

  return str_vec;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> StringUtils::divide_string_data_by_space_code(string str_data)
{
  vector<string> str_vec;
  str_vec.clear();

  vector<int> pos_vec;
  string::size_type space_pos = str_data.find_first_of(space_list);
  while( space_pos != string::npos )
  {
    pos_vec.push_back(space_pos);

    space_pos = str_data.find_first_of(space_list, space_pos+1);
  }

  int i_max = static_cast<int>(pos_vec.size());

  int pos_cur = 0;
  int pos_pre = 0;
  for(int i=0; i<i_max; i++)
  {
           pos_cur = pos_vec[i];
    string str_tmp = trim_space(str_data.substr(pos_pre, pos_cur - pos_pre));
           pos_pre = pos_cur + 1;

    if( static_cast<int>(str_tmp.size()) > 0 )
    {
      str_vec.push_back(str_tmp);
    }
  }

  str_data = trim_space(str_data.substr(pos_pre));
  if( static_cast<int>(str_data.length()) > 0 )
  {
    str_vec.push_back(str_data);
  }

  return str_vec;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void StringUtils::check_string_vector_data_end(vector<string>& text, int line_no,
                                               string class_name, string func_name)
{
  if( static_cast<int>(text.size()) < line_no )
  {
    ostringstream oss01, oss02;
    oss01 << static_cast<int>(text.size());
    oss02 << line_no;

    string str_data01 = "Total line number of text : " + oss01.str();
    string str_data02 = "Current line number       : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("The current line number is larger than the total line number of the text data.");
    err_com.push_back("Please check the text data.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

int StringUtils::get_no_space_string_length(string str_data)
{
  str_data = trim_space(str_data);
  return static_cast<int>(str_data.length());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void StringUtils::skip_no_space_string_data(vector<string>& str_vec, int& line_no)
{
  if( static_cast<int>(str_vec.size()) <= line_no )
  {
    return;
  }

  while( get_no_space_string_length(str_vec[line_no]) == 0 )
  {
    line_no++;
    if( static_cast<int>(str_vec.size()) == line_no )
    {
      line_no--;
      break;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void StringUtils::divide_text_data()
{
  //Remove extra space data
  vector<string> text_mod;

  int i_max = static_cast<int>(text_data.size());
  text_mod.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    text_mod[i] = trim_space(text_data[i]);
  }

  //Search enclosed text data
  vector<vector<int> > quote_pos = get_quote_pos_data(text_mod);

  vector<vector<string> >().swap(div_data);
  quote_pos_list.clear();

  //divide text data
  int j_max  = static_cast<int>(quote_pos.size());
  int ele_no = 0;
  for(int i=0; i<i_max; i++)
  {
    string line_data = text_mod[i];

    if( ele_no < j_max )
    {
      int quote_data_no = 0;
      while( quote_pos[ele_no][0] == i && ele_no < j_max )
      {
        int char_sta      = quote_pos[ele_no][1] + 1;
        if( quote_data_no == 0 )
        {
          if( quote_pos[ele_no][1] > 0 )
          {
            divide_string_data(line_data.substr(0, quote_pos[ele_no][1]));
          }
        }
        else
        {
          char_sta = quote_pos[ele_no][1] - (quote_pos[ele_no-1][1] + quote_pos[ele_no-1][3]);
          if( char_sta - 2 > 0 )
          {
            divide_string_data(line_data.substr(0, char_sta-1));
          }
        }

        vector<string> line_tmp;
        if( quote_pos[ele_no][0] != quote_pos[ele_no][2] )
        {
          line_tmp.push_back(line_data.substr(char_sta));
          i++;

          while( i < quote_pos[ele_no][2] )
          {
            line_tmp.push_back(text_mod[i]);
            i++;
          }
          line_data = text_mod[i];

          if( quote_pos[ele_no][0] != quote_pos[ele_no][2] )
          {
            line_tmp.push_back(line_data.substr(0,quote_pos[ele_no][3]));
            line_data = line_data.substr(quote_pos[ele_no][3]+1);
          }
        }
        else
        {
          int char_no = quote_pos[ele_no][3] - 1;
          line_tmp.push_back(line_data.substr(char_sta,char_no));
          line_data = line_data.substr(char_sta + quote_pos[ele_no][3]);
        }
        div_data.push_back(line_tmp);
        quote_pos_list.push_back(1); //line_tmp is comment data
        vector<string>().swap(line_tmp);

        quote_data_no++;
        ele_no++;
        if( ele_no >= j_max )
        {
          break;
        }
      }
    }

    divide_string_data(line_data);
  }
  vector<string>().swap(text_mod);

  divide_string_data_by_bracket();
  quote_pos_list.clear();

  //get data_no_tot and reset data_no
  data_no     = 0;
  data_no_tot = static_cast<int>(div_data.size());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void StringUtils::divide_string_data(string str_data)
{
  vector<string> str_vec;
  str_vec.resize(1);
  if( static_cast<int>(str_data.size()) > 0 )
  {
    string::size_type space_pos = str_data.find_first_of(space_list.c_str());
    while( space_pos != string::npos )
    {
      string str_tmp = str_data.substr(0, static_cast<int>(space_pos));

      if( static_cast<int>(str_tmp.size()) > 0 )
      {
        str_vec[0] = str_tmp;
        div_data.push_back(str_vec);
        quote_pos_list.push_back(0); //str_vec is not comment data
      }

      str_tmp  = str_data.substr(static_cast<int>(space_pos));
      str_data = trim_space(str_tmp);
      space_pos = str_data.find_first_of(space_list.c_str());

      if( space_pos != string::npos && static_cast<int>(str_data.size()) <= 1 )
      {
        break;
      }
    }

    space_pos = str_data.find_first_of(space_list.c_str());
    if( space_pos == string::npos && static_cast<int>(str_data.size()) > 0 )
    {
      //Copy last string data
      str_vec[0] = str_data;
      div_data.push_back(str_vec);
      quote_pos_list.push_back(0); //str_vec is not comment data
    }
  }
  vector<string>().swap(str_vec);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

vector<vector<int> > StringUtils::get_quote_pos_data(vector<string>& text_vec)
{
  vector<vector<int> > quote_pos_vec;

  int i_max = static_cast<int>(text_vec.size());
  for(int i=0; i<i_max; i++)
  {
    int pos_sta = 0;

    string::size_type quote_pos_all = text_vec[i].find_first_of(quote_list.c_str(), pos_sta);
    while( quote_pos_all != string::npos )
    {
      pos_sta = static_cast<int>(quote_pos_all+1);

      int quote_mode = 2;
      string::size_type quote_pos_s, quote_pos_d, quote_pos;
      quote_pos_s = text_vec[i].find_first_of(quote_single.c_str(), quote_pos_all);
      quote_pos_d = text_vec[i].find_first_of(quote_double.c_str(), quote_pos_all);
      if( quote_pos_s != string::npos && quote_pos_d != string::npos )
      {
        if( static_cast<int>(quote_pos_s) <  static_cast<int>(quote_pos_d) )
        {
          quote_mode = 1;
        }
      }
      else if( quote_pos_s != string::npos )
      {
        quote_mode = 1;
      }

      vector<int> quote_pos_tmp;
      quote_pos_tmp.resize(4);
      quote_pos_tmp[0] = i;       //start  line no
      quote_pos_tmp[2] = i_max-1; //finish line no
      quote_pos_tmp[3] = static_cast<int>(text_vec[i_max-1].size());

      string quote_check = quote_double;
      if( quote_mode == 1 )
      {
        quote_pos        = quote_pos_s;
        quote_check      = quote_single;
      }
      else //if( quote_mode == 2 )
      {
        quote_pos        = quote_pos_d;
        quote_check      = quote_double;
      }
      quote_pos_tmp[1] = static_cast<int>(quote_pos);

      int quote_data_no = 1;
      string::size_type quote_pos_end = text_vec[i].find(quote_check.c_str(), quote_pos+1);
      while( quote_pos_end == string::npos )
      {
        quote_data_no++;
        i++;
        quote_pos_end = text_vec[i].find(quote_check.c_str());

        if( i >= i_max )
        {
          break;
        }
      }
      if( i >= i_max )
      {
        break;
      }

      quote_pos_tmp[2] = i;
      if( quote_data_no == 1 )
      {
        quote_pos_tmp[3] = static_cast<int>(quote_pos_end - quote_pos);
      }
      else
      {
        quote_pos_tmp[3] = static_cast<int>(quote_pos_end);
      }
      quote_pos_vec.push_back(quote_pos_tmp);

      pos_sta = static_cast<int>(quote_pos_end+1);
      quote_pos_all = text_vec[i].find_first_of(quote_list.c_str(), pos_sta);
    }
  }

  return quote_pos_vec;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void StringUtils::divide_string_data_by_bracket()
{
  vector<vector<string> > div_mod;

  int i_max = static_cast<int>(div_data.size());
  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(div_data[i].size());
    if( j_max > 1 || j_max == 0 )
    {
      div_mod.push_back(div_data[i]);
      continue;
    }

    if( static_cast<int>(quote_pos_list.size()) == i_max )
    {
      if( quote_pos_list[i] != 0 )
      {
        //if div_data[i] is comment data, bracket data is not checked.
        div_mod.push_back(div_data[i]);
        continue;
      }
    }

    //check open bracket
    string::size_type bracket_flg, curly_bracket_flg, angled_bracket_flg;
    bracket_flg        = div_data[i][0].find_first_of(bracket_sta.c_str());
    curly_bracket_flg  = div_data[i][0].find_first_of(curly_bracket_sta.c_str());
    angled_bracket_flg = div_data[i][0].find_first_of(angled_bracket_sta.c_str());
    if( bracket_flg == string::npos && curly_bracket_flg == string::npos &&
        angled_bracket_flg == string::npos )
    {
      div_mod.push_back(div_data[i]);
      continue;
    }

    vector<string> bracket_str;

    int bracket_pos = 0;
    if( bracket_flg != string::npos )
    {
      bracket_pos = static_cast<int>(bracket_flg);
    }
    else if( curly_bracket_flg != string::npos )
    {
      bracket_pos = static_cast<int>(curly_bracket_flg);
    }
    else if( angled_bracket_flg != string::npos )
    {
      bracket_pos = static_cast<int>(angled_bracket_flg);
    }

    if( bracket_pos > 0 )
    {
      vector<string> str_vec;
      str_vec.resize(1);
      str_vec[0] = div_data[i][0].substr(0, bracket_pos);

      if( static_cast<int>(str_vec.size()) > 0 )
      {
        div_mod.push_back(str_vec);
        vector<string>().swap(str_vec);
      }
    }
    div_data[i][0] = div_data[i][0].substr(bracket_pos+1);
    if( static_cast<int>(div_data[i][0].size()) == 0 )
    {
      i++;
    }

    bracket_flg        = div_data[i][0].find_first_of(bracket_end.c_str());
    curly_bracket_flg  = div_data[i][0].find_first_of(curly_bracket_end.c_str());
    angled_bracket_flg = div_data[i][0].find_first_of(angled_bracket_end.c_str());
    while( bracket_flg == string::npos && curly_bracket_flg == string::npos &&
           angled_bracket_flg == string::npos )
    {
      bracket_str.push_back(div_data[i][0]);
      i++;
      j_max = static_cast<int>(div_data[i].size());
      while( j_max != 1 )
      {
        if( j_max > 1 )
        {
          string class_name = "StringUtils";
          string func_name  = "divide_string_data_by_bracket";

          vector<string> err_com;
          err_com.push_back("This data may not be appropriate.");
          err_com.push_back("Please check the string data.");
          err_com.push_back("The following data can not be read in this program.");
          for(int j=0; j<j_max; j++)
          {
            err_com.push_back(div_data[i][j]);
          }
          err_obj.output_caution(class_name, func_name, err_com);
        }

        i++;
        j_max = static_cast<int>(div_data[i].size());
      }

      bracket_flg        = div_data[i][0].find_first_of(bracket_end.c_str());
      curly_bracket_flg  = div_data[i][0].find_first_of(curly_bracket_end.c_str());
      angled_bracket_flg = div_data[i][0].find_first_of(angled_bracket_end.c_str());
    }

    if( bracket_flg != string::npos )
    {
      bracket_pos = static_cast<int>(bracket_flg);
    }
    else if( curly_bracket_flg != string::npos )
    {
      bracket_pos = static_cast<int>(curly_bracket_flg);
    }
    else if( angled_bracket_flg != string::npos )
    {
      bracket_pos = static_cast<int>(angled_bracket_flg);
    }

    if( bracket_pos > 0 )
    {
      bracket_str.push_back(div_data[i][0].substr(0, bracket_pos));
    }
    div_mod.push_back(bracket_str);
    vector<string>().swap(bracket_str);

    if( bracket_pos+1 < static_cast<int>(div_data[i][0].size()) )
    {
      vector<string> str_vec;
      str_vec.resize(1);
      str_vec[0] = div_data[i][0].substr(bracket_pos+1);

      div_mod.push_back(str_vec);
      vector<string>().swap(str_vec);
    }
  }

  div_data = div_mod;
  vector<vector<string> >().swap(div_mod);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void StringUtils::set_file_name(string file_name)
{
  ifstream fin(file_name.c_str());

  if(!fin)
  {
    string class_name = "StringUtils";
    string func_name  = "set_file_name(string file_name)";
    vector<string> err_com;
    err_com.push_back("This file name can not be found.");
    err_com.push_back("Please check the file name or directory name.");
    string str_data = "  File name : " + file_name;
    err_com.push_back(str_data);
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  int blank_no = 0;
  vector<string>().swap(text_data);
  while(!fin.eof())
  {
    string line_data;
    getline(fin, line_data);
    text_data.push_back(line_data);

    if( line_data.size() > 0 )
    {
      blank_no = 0;
    }
    else
    {
      blank_no++;

      if( blank_no > 100000000 )
      {
        string class_name = "StringUtils";
        string func_name  = "set_file_name(string file_name)";

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
    line_data.clear();
  }
  fin.close();

  divide_text_data();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void StringUtils::set_text_data(vector<string>& str_vec)
{
  clear();

  text_data = str_vec;

  divide_text_data();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> StringUtils::get_text_data()
{
  return text_data;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

int StringUtils::get_data_no()
{
  return static_cast<int>(div_data.size());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

string StringUtils::get_div_string_data()
{
  if( data_no >= data_no_tot )
  {
    //Return void data
    string str_tmp;
    str_tmp.clear();

    return str_tmp;
  }

  int i_max = static_cast<int>(div_data[data_no].size());
  if( i_max > 1 )
  {
    string class_name = "StringUtils";
    string func_name  = "get_div_string_data()";

    ostringstream oss01, oss02;
    oss01 << data_no;
    oss02 << i_max;
    string str_data01 = "Data no            : " + oss01.str();
    string str_data02 = "Total element no   : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("Only first element data is read.");
    err_com.push_back("The following data were skipped.");
    for(int i=1; i<i_max; i++)
    {
      err_com.push_back(div_data[data_no][i]);
    }
    err_obj.output_caution(class_name, func_name, err_com);
  }
  
  data_no++;
  return div_data[data_no-1][0];
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> StringUtils::get_div_string_vec()
{
  if( data_no >= data_no_tot )
  {
    //Return void data
    vector<string> str_vec_tmp;
    vector<string>().swap(str_vec_tmp);

    return str_vec_tmp;
  }

  data_no++;
  return div_data[data_no-1];
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

string StringUtils::get_div_string_data(int pos)
{
  return get_div_string_vec(pos)[0];
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> StringUtils::get_div_string_vec(int pos)
{
  if( pos >= data_no_tot || pos < 0 )
  {
    string class_name = "StringUtils";
    string func_name  = "get_div_string_vec(int pos)";

    ostringstream oss01, oss02;
    oss01 << data_no_tot;
    oss02 << pos;
    string str_data01 = "Total data no : " + oss01.str();
    string str_data02 = "Set data no   : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    if( pos >= data_no_tot )
    {
      err_com.push_back("Total data number is less than set data number");
    }
    err_com.push_back("The set data number is not appropriate.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  return div_data[pos];
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

vector<vector<string> > StringUtils::get_div_string_vec_all()
{
  return div_data;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> StringUtils::divide_minus_value(vector<string> str_vec)
{
  string minus_mod = "-";

  int i_max = static_cast<int>(str_vec.size());
  for(int i=0; i<i_max; i++)
  {
    replace(str_vec[i].begin(), str_vec[i].end(), '_', '-');
  }

  vector<string> str_new;
  str_new.clear();

  for(int i=0; i<i_max; i++)
  {
    int minus_pos = 1;
    while( str_vec[i].find(minus_mod, minus_pos) != string::npos &&
           static_cast<int>(str_vec[i].size()) > 1 )
    {
      if( str_vec[i].find(minus_mod, minus_pos) != string::npos )
      {
        int div_pos = static_cast<int>(str_vec[i].find(minus_mod, minus_pos));
        str_new.push_back(str_vec[i].substr(0, div_pos));
        str_vec[i] = str_vec[i].substr(div_pos);
      }
      else 
      {
        str_new.push_back(str_vec[i]);
        str_vec[i].clear();
      }
    }

    if( static_cast<int>(str_vec[i].size()) > 0 )
    {
      str_new.push_back(str_vec[i]);
      str_vec[i].clear();
    }
  }
  str_vec.clear();

  return str_new;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

string StringUtils::get_string_num(int int_val, int int_max)
{
  if( int_val < 0 || int_max < 0 || int_val > int_max )
  {
    string class_name = "StringUtils";
    string func_name  = "get_string_num(int int_val, int int_max)";

    ostringstream oss01, oss02;
    oss01 << int_val;
    oss02 << int_max;
    string str_data01 = "int_val : " + oss01.str();
    string str_data02 = "int_max : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);

    int runtime_flg = 0;
    if( int_val < 0 )
    {
      runtime_flg++;
      err_com.push_back("int_val must be larger than or equal to 0.");
      err_com.push_back("");
    }
    if( int_max < 0 )
    {
      runtime_flg++;
      err_com.push_back("int_max must be larger than or equal to 0.");
      err_com.push_back("");
    }
    if( int_val > int_max )
    {
      err_com.push_back("int_max is smaller than int_val.");
      err_com.push_back("int_max is modified to be equal to int_val.");
      err_com.push_back("");
      int_max = int_val;
    }

    if( runtime_flg > 0 )
    {
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
    else
    {
      err_obj.output_caution(class_name, func_name, err_com);
    }
  }

  int width     =  1;
  int max_order = 10;
  while( int_max >= max_order )
  {
    max_order *= 10;
    width++;
  }

  ostringstream oss_int;
  oss_int << setw(width) << setfill('0') << int_val;

  return oss_int.str();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> StringUtils::read_data(vector<string>& text_vec, int& line_no)
{
  int str_no = 0;
  return read_data(text_vec, line_no, str_no);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> StringUtils::read_data(vector<string>& text_vec, int& line_no, int& str_no)
{
  if( static_cast<int>(text_vec.size()) <= line_no )
  {
    string class_name = "StringUtils";
    string func_name  = "read_data(vector<string>& text_vec, int& line_no, int& str_no)";

    ostringstream oss01, oss02;
    oss01 << line_no+1;
    oss02 << static_cast<int>(text_vec.size());

    string str_data01 = "Line number (line_no)               : " + oss01.str();
    string str_data02 = "Total line number (text_vec.size()) : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("The line number is larger than the total line number.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  vector<string> str_vec = divide_string_data_by_space_code(text_vec[line_no]);
  line_no++;

  str_no = static_cast<int>(str_vec.size());

  return str_vec;
}

