#include "FrendyUtils/ArgumentVectorReader.hpp"

using namespace frendy;

ArgumentVectorReader::ArgumentVectorReader(void)
{
  clear();

  //For argument flg
  flg_no = 11;
  flg_list.resize(flg_no);
  flg_mode.resize(flg_no);

  flg_list[ 0] = "--input=";
  flg_list[ 1] = "--inp=";
  flg_list[ 2] = "--i=";
  flg_list[ 3] = "--nucl=";
  flg_list[ 4] = "--n=";
  flg_list[ 5] = "--endf=";
  flg_list[ 6] = "--e=";
  flg_list[ 7] = "--temp=";
  flg_list[ 8] = "--t=";
  flg_list[ 9] = "--mode=";
  flg_list[10] = "--m=";

  flg_mode[ 0] = input_file_name_flg;
  flg_mode[ 1] = input_file_name_flg;
  flg_mode[ 2] = input_file_name_flg;
  flg_mode[ 3] = nucl_file_name_flg;
  flg_mode[ 4] = nucl_file_name_flg;
  flg_mode[ 5] = nucl_file_name_flg;
  flg_mode[ 6] = nucl_file_name_flg;
  flg_mode[ 7] = temp_flg;
  flg_mode[ 8] = temp_flg;
  flg_mode[ 9] = calc_mode_flg;
  flg_mode[10] = calc_mode_flg;

  //For calculation mode list
  calc_mode_no = 4;
  calc_mode_list_mode.resize(calc_mode_no);
  calc_mode_list_name.resize(calc_mode_no);

  calc_mode_list_name[ 0] = "ace";
  calc_mode_list_name[ 1] = "ace_fast";
  calc_mode_list_name[ 2] = "ace_dosi";
  calc_mode_list_name[ 3] = "ace_dosimetry";

  calc_mode_list_mode[ 0] = frendy_utils.ace_fast_mode;
  calc_mode_list_mode[ 1] = frendy_utils.ace_fast_mode;
  calc_mode_list_mode[ 2] = frendy_utils.ace_dosi_mode;
  calc_mode_list_mode[ 3] = frendy_utils.ace_dosi_mode;
}

ArgumentVectorReader::~ArgumentVectorReader(void)
{
  clear();

  flg_no = 0;
  flg_mode.clear();
  clr_obj.clear_vec_array1_str(flg_list);

  calc_mode_no = 0;
  calc_mode_list_mode.clear();
  clr_obj.clear_vec_array1_str(calc_mode_list_name);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ArgumentVectorReader::clear()
{
  set_arg_vec_flg    = 0;

  clr_obj.clear_vec_array1_str(arg_vec);

  clear_input_data();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ArgumentVectorReader::clear_input_data()
{
  input_file_name    = frendy_utils.get_input_file_name_def();
  nucl_file_name     = frendy_utils.get_nucl_file_name_def();
  temp               = frendy_utils.get_temp_def();
  calc_mode          = frendy_utils.get_calc_mode_def();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ArgumentVectorReader::read_argument_data()
{
  if( set_arg_vec_flg > 0 )
  {
    return;
  }

  clear_input_data();
  set_arg_vec_flg = 1;

  int i_max = static_cast<int>(arg_vec.size());
  if( i_max > 1 )
  {
    for(int i=0; i<i_max; i++)
    {
      read_flg_data(arg_vec[i]);
    }
  }
  else if( i_max == 1 )
  {
    if( search_flg_mode(arg_vec[0]) < 0 )
    {
      FrendyInputReader frendy_inp_obj;
      int calc_mode = frendy_inp_obj.check_file_format(arg_vec[0]);
      if( calc_mode == frendy_utils.non_related )
      {
        nucl_file_name.resize(1);
        nucl_file_name[0] = arg_vec[0];
      }
      else
      {
        input_file_name = arg_vec[0];
      }
    }
    else
    {
      read_flg_data(arg_vec[0]);
    }
  }
  else
  {
    string class_name = "ArgumentVectorReader";
    string func_name  = "read_argument_data()";

    vector<string> err_com;
    err_com.push_back("There is no argument data.");
    err_com.push_back("Please set argument data, e.g., nuclear file name, input file name and so on.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ArgumentVectorReader::read_flg_data(string arg_flg)
{
  int inp_flg     = check_flg_data(arg_flg);
  int flg_data    = flg_mode[inp_flg];
  int flg_char_no = static_cast<int>(flg_list[inp_flg].size());

  string arg_data = arg_flg.substr(flg_char_no);

  if( flg_data == input_file_name_flg )
  {
    input_file_name = arg_data;
  }
  else if( flg_data == nucl_file_name_flg )
  {
    nucl_file_name.resize(1);
    nucl_file_name[0] = arg_data;
  }
  else if( flg_data == temp_flg )
  {
    str_obj.string_check(arg_data);
    temp = numeric_string_cast<Real>(arg_data);
  }
  else if( flg_data == calc_mode_flg )
  {
    read_calc_mode(arg_data); 
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ArgumentVectorReader::read_calc_mode(string arg_data)
{
  int mode_set_flg = -1;

  for(int j=0; j<calc_mode_no; j++)
  {
    if( strcmp(arg_data.c_str(), calc_mode_list_name[j].c_str()) == 0 )
    {
      mode_set_flg = j;
      break;
    }
  }

  if( mode_set_flg >= 0 )
  {
    calc_mode = calc_mode_list_mode[mode_set_flg];
  }
  else
  {
    string class_name = "ArgumentVectorReader";
    string func_name  = "read_calc_mode(string arg_data)";

    vector<string> err_com;
    string str_data01 = "Calculation mode : " + arg_data;
    err_com.push_back(str_data01);
    err_com.push_back("This calculation mode is not available in this program.");
    err_com.push_back("Available calculation mode is as follows:");
    for(int j=0; j<calc_mode_no; j++)
    {
      string str_data02 = "  ";
      int multiple_flg = 0;
      if( j > 0 )
      {
        if( calc_mode_list_mode[j] == calc_mode_list_mode[j-1] )
        {
          multiple_flg = 1;
        }
      }

      if( multiple_flg == 0 )
      {
        if( calc_mode_list_mode[j] == input_file_name_flg )
        {
          str_data02 = str_data02 + "For fast ace file      : ";
        }
        else if( calc_mode_list_mode[j] == nucl_file_name_flg )
        {
          str_data02 = str_data02 + "For dosimetry ace file : ";
        }
      }
      else
      {
        str_data02 = str_data02 + "                         ";
      }

      str_data02 = str_data02 + calc_mode_list_name[j];
      err_com.push_back(str_data02);
    }
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int ArgumentVectorReader::search_flg_mode(string str_data)
{
  int inp_flg = -1;
  for(int j=0; j<flg_no; j++)
  {
    if( str_data.find(flg_list[j].c_str()) == 0 )
    {
      inp_flg = j;
      break;
    }
  }

  return inp_flg; 
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int ArgumentVectorReader::check_flg_data(string str_data)
{
  int inp_flg = search_flg_mode(str_data);

  if( inp_flg < 0 )
  {
    string class_name = "ArgumentVectorReader";
    string func_name  = "check_flg_data(string str_data)";

    vector<string> err_com;
    string str_data01 = "Argument data : " + str_data;
    err_com.push_back(str_data01);
    err_com.push_back("This argument data is not available in this program.");
    err_com.push_back("Available argument is as follows:");
    for(int j=0; j<flg_no; j++)
    {
      string str_data02 = "  ";
      int multiple_flg = 0;
      if( j > 0 )
      {
        if( flg_mode[j] == flg_mode[j-1] )
        {
          multiple_flg = 1;
        }
      }

      if( multiple_flg == 0 )
      {
        if( flg_mode[j] == input_file_name_flg )
        {
          str_data02 = str_data02 + "For input file name  : ";
        }
        else if( flg_mode[j] == nucl_file_name_flg )
        {
          str_data02 = str_data02 + "For nucl file name   : ";
        }
        else if( flg_mode[j] == temp_flg )
        {
          str_data02 = str_data02 + "For temperature      : ";
        }
        else if( flg_mode[j] == calc_mode_flg )
        {
          str_data02 = str_data02 + "For calculation mode : ";
        }
      }
      else
      {
        str_data02 = str_data02 + "                       ";
      }

      str_data02 = str_data02 + flg_list[j];
      err_com.push_back(str_data02);
    }
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  return inp_flg;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ArgumentVectorReader::set_argument_vector(vector<string> str_vec)
{
  set_arg_vec_flg = 0;

  arg_vec = str_vec;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> ArgumentVectorReader::get_argument_vector()
{
  return arg_vec;
}

string ArgumentVectorReader::get_input_file_name()
{
  read_argument_data();

  return input_file_name;
}

vector<string> ArgumentVectorReader::get_nucl_file_name()
{
  read_argument_data();

  return nucl_file_name;
}

Real ArgumentVectorReader::get_temp()
{
  read_argument_data();

  return temp;
}

int ArgumentVectorReader::get_calc_mode()
{
  read_argument_data();

  return calc_mode;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

