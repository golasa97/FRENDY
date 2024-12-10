#include "NjoyUtils/PurrInputReader.hpp"

using namespace frendy;

PurrInputReader::PurrInputReader(void)
{
  clear();
}

PurrInputReader::~PurrInputReader(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PurrInputReader::read_input(string file_name)
{
  read_input(file_name, 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PurrInputReader::read_input(string file_name, int line_no)
{
  clear();

  input_purr = file_name;

  //open input file
  ifstream fin(input_purr.c_str());
  if( !fin )
  {
    string class_name = "PurrInputReader";
    string func_name  = "read_input(string file_name)";

    string str_data = "File name : " + file_name;

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("There is no input file.");
    err_com.push_back("Please check the input file name.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //read until purr input 
  string input_case = "purr";
  rn_obj.search_each_input(fin, input_case, line_no);

  //read purr input
  read_file_name(fin);
  read_card02_data(fin);
  read_card03_data(fin);
  read_card04_data(fin);

  fin.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PurrInputReader::read_file_name(ifstream& fin)
{
  string line_data;
  vector<string> input_data;

  //Card 01
  getline(fin, line_data);
  input_data = rn_obj.read_line_without_slash(line_data);

  if( static_cast<int>(input_data.size()) < 3 )
  {
    string class_name = "PurrInputReader";
    string func_name  = "read_file_name(ifstream& fin)";

    ostringstream oss;
    oss << input_data.size();
    string str_data01 = "Input file name = " + input_purr;
    string str_data02 = "Data no         = " + oss.str();
    string str_data03 = "Input data      = " + line_data;

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("The data number of card 1 is less than 3.");
    err_com.push_back("In card 3, three integer data is required, i.e., nendf, nin, and nout.");
    err_com.push_back("Please check the input file.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  for(int i=0; i<3; i++)
  {
    int j = static_cast<int>(input_data[i].find_first_of("-"));
    if( j >= 0 )
    {
      string class_name = "PurrInputReader";
      string func_name  = "read_file_name(ifstream& fin)";

      string str_data = "tape no : " + input_data[i];

      vector<string> err_com;
      err_com.push_back(str_data);
      err_com.push_back("Binary mode, i.e., tape no less than 0, can not treat in FRENDY.");

      if( j==0 )
      {
        err_com.push_back("This file considered as the ascii mode file.");
        err_obj.output_caution(class_name, func_name, err_com);
      }
      else
      {
        err_com.push_back("Please check the input file name.");
        err_obj.output_runtime_error(class_name, func_name, err_com);
      }

      input_data[i] = input_data[i].substr(j+1);
    }
  }

  endf_name      = "tape" + input_data[0];
  pendf_name_old = "tape" + input_data[1];
  pendf_name_new = "tape" + input_data[2];

  line_data.clear();
  clr_obj.clear_vec_array1_str(input_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PurrInputReader::read_card02_data(ifstream& fin)
{
  string line_data;
  vector<string> input_data;

  //Card 02
  getline(fin, line_data);
  input_data = rn_obj.read_line_without_slash(line_data);

  int i_max = static_cast<int>(input_data.size());
  if( i_max < 5 )
  {
    string class_name = "PurrInputReader";
    string func_name  = "read_card02_data(ifstream& fin)";

    ostringstream oss;
    oss << input_data.size();
    string str_data01 = "Input file name = " + input_purr;
    string str_data02 = "Data no         = " + oss.str();
    string str_data03 = "Input data      = " + line_data;

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("The data number in Card 2 is less than the required data no (5).");
    for(int i=0; i<i_max; i++)
    {
      ostringstream oss;
      string        str_data;
      str_data.clear();

      oss << i+1;
      str_data = "  Data " + oss.str() + " : " + input_data[i];
      err_com.push_back(str_data);
    }
    err_com.push_back("Please check the input file.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  mat         = numeric_string_cast<Integer>(input_data[0]);
  temp_no     = numeric_string_cast<Integer>(input_data[1]);
  sig_zero_no = numeric_string_cast<Integer>(input_data[2]);
  bin_no      = numeric_string_cast<Integer>(input_data[3]);
  ladder_no   = numeric_string_cast<Integer>(input_data[4]);

  opt_print   = 1;
  ene_grid_no = 0;
  random_seed = random_seed_ini;
  sample_no   = sample_no_ini;
  p_tab_file_name.clear();
  if( i_max > 5 )
  {
    opt_print   = numeric_string_cast<Integer>(input_data[5]);
  }
  if( i_max > 6 )
  {
    ene_grid_no = numeric_string_cast<Integer>(input_data[6]);
  }
  if( i_max > 7 )
  {
    //Special case for FRENDY
    random_seed = numeric_string_cast<Integer>(input_data[7]);
  }
  if( i_max > 8 )
  {
    //Special case for FRENDY
    sample_no = numeric_string_cast<Integer>(input_data[8]);
  }
  if( i_max > 9 )
  {
    //Special case for FRENDY
    p_tab_file_name = input_data[9];
  }

  if( mat < 0 || temp_no < 1 || sig_zero_no < 1 || bin_no < 15 || ladder_no < 1 || 
      opt_print < 0 || opt_print > 1 || ene_grid_no < 0 )
  {
    string class_name = "PurrInputReader";
    string func_name  = "read_card02_data(ifstream& fin)";

    vector<string> err_com;
    for(int i=0; i<static_cast<int>(input_data.size()); i++)
    {
      string str_data;
      if( i==0 )      str_data = "Material number             : " + input_data[i];
      else if( i==1 ) str_data = "Number of temperatures      : " + input_data[i];
      else if( i==2 ) str_data = "Number of sigma zeros       : " + input_data[i];
      else if( i==3 ) str_data = "Number of probability bins  : " + input_data[i];
      else if( i==4 ) str_data = "Number of resonance ladders : " + input_data[i];
      else if( i==5 ) str_data = "Print option                : " + input_data[i];
      else if( i==6 ) str_data = "Number of energy points     : " + input_data[i];
      err_com.push_back(str_data);
    }
    err_com.push_back("");

    if( mat < 0 )
    {
      err_com.push_back("Material number must be larger than or equal to 0.");
    }
    if( temp_no < 1 )
    {
      err_com.push_back("Number of temperatures must be larger than 0.");
    }
    if( sig_zero_no < 1 )
    {
      err_com.push_back("Number of sigma zeros must be larger than 0.");
    }
    if( bin_no < 15 )
    {
      err_com.push_back("Number of probability bins must be larger than or equal to 15.");
    }
    if( ladder_no < 1 )
    {
      err_com.push_back("Number of resonance ladders must be larger than 0.");
    }
    if( opt_print < 0 || opt_print > 1 )
    {
      err_com.push_back("Print option is only available for 0 or 1.");
    }
    if( ene_grid_no < 0 )
    {
      err_com.push_back("Number of energy points must be larger than or equal to 0.");
    }
    err_com.push_back("Please check the input file.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  line_data.clear();
  clr_obj.clear_vec_array1_str(input_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PurrInputReader::read_card03_data(ifstream& fin)
{
  temp.resize(static_cast<int>(temp_no));

  string line_data;
  vector<string> input_data;

  int ele_no = 0;
  while( ele_no < temp_no )
  {
    //Card 03
    getline(fin, line_data);
    input_data = rn_obj.read_line_without_slash(line_data);

    int i_max = static_cast<int>(input_data.size());
    for(int i=0; i<i_max; i++)
    {
      temp[ele_no] = numeric_string_cast<Real8>(input_data[i]);
      ele_no++;

      if( ele_no >= temp_no )
      {
        break;
      }
    }

    if( fin.eof() )
    {
      string class_name = "PurrInputReader";
      string func_name  = "read_card03_data(ifstream& fin)";
      vector<string> err_com;
      err_com.push_back("The input file is reached the end until reading the temperature data.");
      err_com.push_back("The temperature data number may not be appropriate.");
      err_com.push_back("Please check input file.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }

  //Check temperature data
  int i_max   = static_cast<int>(temp_no);
  int err_flg = -1;
  for(int i=0; i<i_max; i++)
  {
    if( temp[i] < min_value )
    {
      err_flg = 1;
    }
  }

  if( err_flg > 0 )
  {
    string class_name = "PurrInputReader";
    string func_name  = "read_card03_data(ifstream& fin)";

    vector<string> err_com;
    err_com.push_back("The temperature is less than or equal to zero).");
    for(int i=0; i<static_cast<int>(input_data.size()); i++)
    {
      ostringstream oss;
      oss << i+1;
      string str_data = "  Data " + oss.str() + " : " + input_data[i];
      err_com.push_back(str_data);
      str_data.clear();
    }
    err_com.push_back("Please check the input file.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  line_data.clear();
  clr_obj.clear_vec_array1_str(input_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PurrInputReader::read_card04_data(ifstream& fin)
{
  sig_zero.resize(static_cast<int>(sig_zero_no));

  string line_data;
  vector<string> input_data;

  int ele_no = 0;
  while( ele_no < sig_zero_no )
  {
    //Card 04
    getline(fin, line_data);
    input_data = rn_obj.read_line_without_slash(line_data);

    int i_max = static_cast<int>(input_data.size());
    for(int i=0; i<i_max; i++)
    {
      sig_zero[ele_no] = numeric_string_cast<Real8>(input_data[i]);
      ele_no++;

      if( ele_no >= sig_zero_no )
      {
        break;
      }
    }

    if( fin.eof() )
    {
      string class_name = "PurrInputReader";
      string func_name  = "read_card04_data(ifstream& fin)";
      vector<string> err_com;
      err_com.push_back("The input file is reached the end until reading the sig zero data.");
      err_com.push_back("The sig zero data number may not be appropriate.");
      err_com.push_back("Please check input file.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }
  line_data.clear();
  clr_obj.clear_vec_array1_str(input_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PurrInputReader::clear()
{
  input_purr.clear();
  endf_name.clear();
  pendf_name_old.clear();
  pendf_name_new.clear();

  mat         = unassigned_mat_no;
  temp_no     = -1;
  sig_zero_no = -1;
  bin_no      = -1;
  ladder_no   = -1;
  opt_print   = -1;
  ene_grid_no = -1;
  random_seed = random_seed_ini;
  sample_no   = sample_no_ini;
  p_tab_file_name.clear();

  temp.clear();
  sig_zero.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

string        PurrInputReader::get_input_purr()
{
  return input_purr;
}

string        PurrInputReader::get_endf_name()
{
  return endf_name;
}

string        PurrInputReader::get_pendf_name_old()
{
  return pendf_name_old;
}

string        PurrInputReader::get_pendf_name_new()
{
  return pendf_name_new;
}

Integer       PurrInputReader::get_mat()
{
  return mat;
}

Integer       PurrInputReader::get_temp_no()
{
  return temp_no;
}

Integer       PurrInputReader::get_sig_zero_no()
{
  return sig_zero_no;
}

Integer       PurrInputReader::get_bin_no()
{
  return bin_no;
}

Integer       PurrInputReader::get_ladder_no()
{
  return ladder_no;
}

Integer       PurrInputReader::get_opt_print()
{
  return opt_print;
}

Integer       PurrInputReader::get_ene_grid_no()
{
  return ene_grid_no;
}

Integer       PurrInputReader::get_random_seed()
{
  return random_seed;
}

Integer       PurrInputReader::get_sample_no()
{
  return sample_no;
}

string        PurrInputReader::get_p_tab_file_name()
{
  return p_tab_file_name;
}

vector<Real8> PurrInputReader::get_temp()
{
  return temp;
}

vector<Real8> PurrInputReader::get_sig_zero()
{
  return sig_zero;
}

