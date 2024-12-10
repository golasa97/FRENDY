#include "NjoyUtils/UnresrInputReader.hpp"

using namespace frendy;

UnresrInputReader::UnresrInputReader(void)
{
  clear();
}

UnresrInputReader::~UnresrInputReader(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void UnresrInputReader::read_input(string file_name)
{
  read_input(file_name, 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void UnresrInputReader::read_input(string file_name, int line_no)
{
  clear();

  input_unresr = file_name;

  //open input file
  ifstream fin(input_unresr.c_str());
  if( !fin )
  {
    string class_name = "UnresrInputReader";
    string func_name  = "read_input(string file_name)";

    string str_data = "File name : " + file_name;

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("There is no input file.");
    err_com.push_back("Please check the input file name.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //read until unresr input 
  string input_case = "unresr";
  rn_obj.search_each_input(fin, input_case, line_no);

  set_default_value();

  //read unresr input
  read_file_name(fin);
  read_card02_data(fin);
  read_card03_data(fin);
  read_card04_data(fin);

  fin.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void UnresrInputReader::set_default_value()
{
  bin_no    = frendy_utils.get_probability_bin_no_def();
  ladder_no = frendy_utils.get_ladder_no_def();

  temp.resize(1);
  sig_zero.resize(1);
  temp[0]     = frendy_utils.get_temp_def();
  sig_zero[0] = 1.0E+10;

  temp_no     = static_cast<int>(temp.size());
  sig_zero_no = static_cast<int>(sig_zero.size());
  opt_print   = 0;
  ene_grid_no = 0;

  random_seed = random_seed_ini;
  sample_no   = sample_no_ini;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void UnresrInputReader::read_file_name(ifstream& fin)
{
  string line_data;
  vector<string> input_data;

  //Card 01
  getline(fin, line_data);
  input_data = rn_obj.read_line_without_slash(line_data);

  if( static_cast<int>(input_data.size()) < 3 )
  {
    string class_name = "UnresrInputReader";
    string func_name  = "read_file_name(ifstream& fin)";

    ostringstream oss;
    oss << input_data.size();
    string str_data01 = "Input file name = " + input_unresr;
    string str_data02 = "Data no         = " + oss.str();
    string str_data03 = "Input data      = " + line_data;

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("The data number of card 1 is less than 3.");
    err_com.push_back("In card 1, three integer data is required, i.e., nendf, nin, and nout.");
    err_com.push_back("Please check the input file.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  for(int i=0; i<3; i++)
  {
    int j = static_cast<int>(input_data[i].find_first_of("-"));
    if( j >= 0 )
    {
      string class_name = "UnresrInputReader";
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

void UnresrInputReader::read_card02_data(ifstream& fin)
{
  string line_data;
  vector<string> input_data;

  //Card 02
  getline(fin, line_data);
  input_data = rn_obj.read_line_without_slash(line_data);

  int i_max = static_cast<int>(input_data.size());
  if( i_max < 1 )
  {
    string class_name = "UnresrInputReader";
    string func_name  = "read_card02_data(ifstream& fin)";

    ostringstream oss01;
    oss01 << input_data.size();
    string str_data01 = "Input file name = " + input_unresr;
    string str_data02 = "Data no         = " + oss01.str();
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

  mat = numeric_string_cast<Integer>(input_data[0]);

  if( i_max > 1 )
  {
    temp_no = numeric_string_cast<Integer>(input_data[1]);
  }

  if( i_max > 2 )
  {
    sig_zero_no = numeric_string_cast<Integer>(input_data[2]);
  }

  if( i_max > 3 )
  {
    opt_print = numeric_string_cast<Integer>(input_data[3]);
  }

  if( mat < 0 || temp_no < 1 || sig_zero_no < 1 || bin_no < 15 || ladder_no < 1 || 
      opt_print < 0 || opt_print > 1 || ene_grid_no < 0 )
  {
    string class_name = "UnresrInputReader";
    string func_name  = "read_card02_data(ifstream& fin)";

    vector<string> err_com;
    for(int i=0; i<static_cast<int>(input_data.size()); i++)
    {
      string str_data;
      if( i==0 )      str_data = "Material number             : " + input_data[i];
      else if( i==1 ) str_data = "Number of temperatures      : " + input_data[i];
      else if( i==2 ) str_data = "Number of sigma zeros       : " + input_data[i];
      else if( i==3 ) str_data = "Print option                : " + input_data[i];
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

void UnresrInputReader::read_card03_data(ifstream& fin)
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
      string class_name = "UnresrInputReader";
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
    string class_name = "UnresrInputReader";
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

void UnresrInputReader::read_card04_data(ifstream& fin)
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
      string class_name = "UnresrInputReader";
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

void UnresrInputReader::clear()
{
  input_unresr.clear();
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

  temp.clear();
  sig_zero.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

string        UnresrInputReader::get_input_unresr()
{
  return input_unresr;
}

string        UnresrInputReader::get_endf_name()
{
  return endf_name;
}

string        UnresrInputReader::get_pendf_name_old()
{
  return pendf_name_old;
}

string        UnresrInputReader::get_pendf_name_new()
{
  return pendf_name_new;
}

Integer       UnresrInputReader::get_mat()
{
  return mat;
}

Integer       UnresrInputReader::get_temp_no()
{
  return temp_no;
}

Integer       UnresrInputReader::get_sig_zero_no()
{
  return sig_zero_no;
}

Integer       UnresrInputReader::get_bin_no()
{
  return bin_no;
}

Integer       UnresrInputReader::get_ladder_no()
{
  return ladder_no;
}

Integer       UnresrInputReader::get_opt_print()
{
  return opt_print;
}

Integer       UnresrInputReader::get_ene_grid_no()
{
  return ene_grid_no;
}

Integer       UnresrInputReader::get_random_seed()
{
  return random_seed;
}

Integer       UnresrInputReader::get_sample_no()
{
  return sample_no;
}

vector<Real8> UnresrInputReader::get_temp()
{
  return temp;
}

vector<Real8> UnresrInputReader::get_sig_zero()
{
  return sig_zero;
}

