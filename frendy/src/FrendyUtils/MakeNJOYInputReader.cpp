#include "FrendyUtils/MakeNJOYInputReader.hpp"

using namespace frendy;

MakeNJOYInputReader::MakeNJOYInputReader(void)
{
  clear();
}

MakeNJOYInputReader::~MakeNJOYInputReader(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MakeNJOYInputReader::clear()
{
  print_title_flg = 0;

  print_set_data_flg = frendy_utils.get_print_set_data_flg_def();

  set_all_calc_flg_on();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MakeNJOYInputReader::set_all_calc_flg_on()
{
  reconr_flg = 1;
  broadr_flg = 1;
  gaspr_flg  = 1;
  purr_flg   = 1;
  thermr_flg = 1;
  acer_flg   = 1;
  groupr_flg = 1;
  matxsr_flg = 1;
  heatr_flg  = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MakeNJOYInputReader::set_all_calc_flg_off()
{
  reconr_flg = 0;
  broadr_flg = 0;
  gaspr_flg  = 0;
  purr_flg   = 0;
  thermr_flg = 0;
  acer_flg   = 0;
  groupr_flg = 0;
  matxsr_flg = 0;
  heatr_flg  = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MakeNJOYInputReader::read_input_data_from_input_file(string file_name)
{
  FileCommentRemover file_handling_obj;
  vector<vector<string> > input_data = file_handling_obj.remove_comment_and_devide_text_data(file_name);

  read_input_data(input_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<int> MakeNJOYInputReader::read_input_data(vector<vector<string> >& input_data)
{
  int i_max = static_cast<int>(input_data.size());
  int i_sta = 0;
  if( i_max%2 == 1 ) //include calculation mode at input_data[0][0]
  {
    i_sta = 1;
  }

  int data_no = (i_max - i_sta) / 2;
  vector<int> inp_check_vec;
  inp_check_vec.resize(data_no);

  int ele_no = 0;
  for(int i=i_sta; i<i_max; i+=2)
  {
    inp_check_vec[ele_no] = read_input_data(input_data[i], input_data[i+1]);
    ele_no++;
  }

  return inp_check_vec;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int MakeNJOYInputReader::read_input_data(vector<string>& input_type, vector<string>& input_data)
{
  if( static_cast<int>(input_type.size()) != 1 )
  {
    string class_name = "MakeNJOYInputReader";
    string func_name  = "read_input_data(vector<string>& input_type, vector<string>& input_data)";
    frendy_utils.error_input_type_size(class_name, func_name, input_type);
  }

  return read_input_data(input_type[0], input_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int MakeNJOYInputReader::read_input_data(string& input_type, vector<string>& input_data)
{
  if( static_cast<int>(input_data.size()) == 0 )
  {
    string class_name = "MakeNJOYInputReader";
    string func_name  = "read_input_data(string& input_type, vector<string>& input_data)";
    frendy_utils.error_input_data_size_is_zero(class_name, func_name, input_data);
  }

  //Modify capital letter to lower-case letter
  string input_type_mod = input_type;
  transform(input_type_mod.begin(), input_type_mod.end(), input_type_mod.begin(), ::tolower);
  replace(input_type_mod.begin(), input_type_mod.end(), '-', '_');

  int inp_check = 1;
  if( input_type_mod == "make_input_module" )
  {
    if( print_set_data_flg == frendy_utils.print_set_data && print_title_flg == 0 )
    {
      print_title_flg = 1;
      cout << "=== Read input data for MakeNJOY ===" << endl;
    }

    set_make_input_module(input_data);
  }
  else
  {
    inp_check = 0;
  }

  return inp_check;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MakeNJOYInputReader::set_make_input_module(vector<string> input_data)
{
  set_all_calc_flg_off();

  int i_max = static_cast<int>(input_data.size());
  for(int i=0; i<i_max; i++)
  {
    if( print_set_data_flg == frendy_utils.print_set_data )
    {
      if( i==0 )
      {
        cout << "  NJOY input module name : " << input_data[i] << endl;
      }
      else
      {
        cout << "                         : " << input_data[i] << endl;
      }
    }

    string input_data_mod = input_data[i];
    transform(input_data_mod.begin(), input_data_mod.end(), input_data_mod.begin(), ::tolower);

    if( input_data_mod == "reconr" || input_data_mod == "recon" )
    {
      reconr_flg = 1;
    }
    else if( input_data_mod == "broadr" || input_data_mod == "broad" )
    {
      broadr_flg = 1;
    }
    else if( input_data_mod == "gaspr" || input_data_mod == "gasp" )
    {
      gaspr_flg = 1;
    }
    else if( input_data_mod == "purr"   || input_data_mod == "pur"   ||
             input_data_mod == "unresr" || input_data_mod == "unres" )
    {
      purr_flg = 1;
    }
    else if( input_data_mod == "thermr" || input_data_mod == "therm" )
    {
      thermr_flg = 1;
    }
    else if( input_data_mod == "acer" || input_data_mod == "ace" )
    {
      acer_flg = 1;
    }
    else if( input_data_mod == "groupr" || input_data_mod == "group" )
    {
      groupr_flg = 1;
    }
    else if( input_data_mod == "matxsr" || input_data_mod == "matxs" )
    {
      matxsr_flg = 1;
    }
    else if( input_data_mod == "heatr" || input_data_mod == "heat" )
    {
      heatr_flg = 1;
    }
    else
    {
      string class_name = "MakeNJOYInputReader";
      string func_name  = "set_make_input_module(vector<string> input_data)";

      string str_data   = "Module name : " + input_data_mod;

      vector<string> err_com;
      err_com.push_back("This module is not available in this program.");
      err_com.push_back("The available modile is RECONR, BROADR, GASPR, PURR, THERMR,");
      err_com.push_back("GROUPR, and MATXSR.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//Getter

int MakeNJOYInputReader::get_reconr_flg()
{
  return reconr_flg;
}

int MakeNJOYInputReader::get_broadr_flg()
{
  return broadr_flg;
}

int MakeNJOYInputReader::get_gaspr_flg()
{
  return gaspr_flg;
}

int MakeNJOYInputReader::get_purr_flg()
{
  return purr_flg;
}

int MakeNJOYInputReader::get_thermr_flg()
{
  return thermr_flg;
}

int MakeNJOYInputReader::get_acer_flg()
{
  return acer_flg;
}

int MakeNJOYInputReader::get_groupr_flg()
{
  return groupr_flg;
}

int MakeNJOYInputReader::get_matxsr_flg()
{
  return matxsr_flg;
}

int MakeNJOYInputReader::get_heatr_flg()
{
  return heatr_flg;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

