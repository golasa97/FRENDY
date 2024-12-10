#include "NjoyUtils/ThermrInputReader.hpp"

using namespace frendy;

ThermrInputReader::ThermrInputReader(void)
{
  clear();
}

ThermrInputReader::~ThermrInputReader(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermrInputReader::read_input(string file_name)
{
  read_input(file_name, 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermrInputReader::read_input(string file_name, int line_no)
{
  clear();

  input_thermr = file_name;

  //open input file
  ifstream fin(input_thermr.c_str());
  if( !fin )
  {
    string class_name = "ThermrInputReader";
    string func_name  = "read_input(string file_name)";

    string str_data = "File name : " + file_name;

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("There is no input file.");
    err_com.push_back("Please check the input file name.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //read until thermr input 
  string input_case = "thermr";
  rn_obj.search_each_input(fin, input_case, line_no);

  //read thermr input
  read_file_name(fin);
  read_card02_data(fin);
  read_card03_data(fin);
  read_card04_data(fin);

  fin.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermrInputReader::read_file_name(ifstream& fin)
{
  string line_data;
  vector<string> input_data;

  //Card 01
  getline(fin, line_data);
  input_data = rn_obj.read_line_without_slash(line_data);

  if( static_cast<int>(input_data.size()) < 3 )
  {
    string class_name = "ThermrInputReader";
    string func_name  = "read_file_name(ifstream& fin)";

    ostringstream oss;
    oss << input_data.size();
    string str_data01 = "Input file name = " + input_thermr;
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
      string class_name = "ThermrInputReader";
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

void ThermrInputReader::read_card02_data(ifstream& fin)
{
  string line_data;
  vector<string> input_data;

  //Card 02
  getline(fin, line_data);
  input_data = rn_obj.read_line_without_slash(line_data);

  if( static_cast<int>(input_data.size()) < 8 )
  {
    string class_name = "ThermrInputReader";
    string func_name  = "read_card02_data(ifstream& fin)";

    ostringstream oss01;
    oss01 << input_data.size();
    string str_data01 = "Input file name = " + input_thermr;
    string str_data02 = "Data no         = " + oss01.str();
    string str_data03 = "Input data      = " + line_data;

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("The data number in Card 2 is less than the required data no (9).");
    for(int i=0; i<static_cast<int>(input_data.size()); i++)
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

  mat_endf      = numeric_string_cast<Integer>(input_data[0]);
  mat_pendf     = numeric_string_cast<Integer>(input_data[1]);
  bin_no        = numeric_string_cast<Integer>(input_data[2]);
  temp_no       = numeric_string_cast<Integer>(input_data[3]);
  opt_inelastic = numeric_string_cast<Integer>(input_data[4]);
  opt_elastic   = numeric_string_cast<Integer>(input_data[5]);
  atom_no       = numeric_string_cast<Integer>(input_data[6]);
  mt_out        = numeric_string_cast<Integer>(input_data[7]);

  opt_print = 0;
  if( static_cast<int>(input_data.size()) > 8 )
  {
    opt_print = numeric_string_cast<Integer>(input_data[8]);
  }

  //NJOY2012 and NJOY2016 mode
  int njoy2012_flg = 0;
  if( mt_out > 0 && mt_out < 100 )
  {
    njoy2012_flg = 1;

    //output_format = numeric_string_cast<Integer>(input_data[6]);
    atom_no       = numeric_string_cast<Integer>(input_data[7]);
    mt_out        = numeric_string_cast<Integer>(input_data[8]);

    if( opt_inelastic == 2 )
    {
      opt_inelastic = 4;
    }

    opt_print = 0;
    if( static_cast<int>(input_data.size()) > 9 )
    {
      opt_print = numeric_string_cast<Integer>(input_data[9]);
    }

    string class_name = "ThermrInputReader";
    string func_name  = "read_card02_data(ifstream& fin)";
    vector<string> err_com;
    err_com.push_back("Though this input file for the NJOY2012 or the later version of NJOY,");
    err_com.push_back("FRENDY avilable for the NJOY99 format.");
    err_com.push_back("The output format option is skipped (invalid) in this calculation.");
    err_obj.output_caution(class_name, func_name, err_com);
  }


  if( mat_endf == 0 )
  {
    if( (opt_inelastic != 0 && opt_inelastic != 1) || opt_elastic != 0 )
    {
      string class_name = "ThermrInputReader";
      string func_name  = "read_card02_data(ifstream& fin)";

      vector<string> err_com;
      for(int i=0; i<static_cast<int>(input_data.size()); i++)
      {
        string str_data;
        if( i== 0 )      str_data = "Material number on Endf file   : " + input_data[i];
        else if( i== 1 ) str_data = "Material number on Pendf file  : " + input_data[i];
        else if( i== 2 ) str_data = "Inelastic option               : " + input_data[i];
        else if( i== 3 ) str_data = "Elastic option                 : " + input_data[i];
        err_com.push_back(str_data);
      }
      err_com.push_back("");

      err_com.push_back("When the material number on Endf file is zero, inelastic and elastic");
      err_com.push_back("options are limited.");
      if( opt_inelastic != 0 && opt_inelastic != 1 )
      {
        err_com.push_back("Inelastic option must be 0 (none) or 1 (compute as free gas).");
      }
      if( opt_elastic != 0 )
      {
        err_com.push_back("Elastic option must be 0 (none).");
      }

      err_com.push_back("Please check the input file.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }

  if( mat_pendf <= 0 || bin_no <= 0 || temp_no   <= 0|| opt_inelastic < 0 || opt_elastic < 0 ||
      atom_no   <= 0 || mt_out <= 0 || opt_print < 0 || opt_print > 2 )
  {
    string class_name = "ThermrInputReader";
    string func_name  = "read_card02_data(ifstream& fin)";

    vector<string> err_com;
    for(int i=0; i<static_cast<int>(input_data.size()); i++)
    {
      string str_data;
      if( njoy2012_flg == 0 )
      {
        if( i==0 )      str_data = "Material number on Endf file   : " + input_data[i];
        else if( i==1 ) str_data = "Material number on Pendf file  : " + input_data[i];
        else if( i==2 ) str_data = "Number of equi-probable angles : " + input_data[i];
        else if( i==3 ) str_data = "Number of temperatures         : " + input_data[i];
        else if( i==4 ) str_data = "Inelastic option               : " + input_data[i];
        else if( i==5 ) str_data = "Elastic option                 : " + input_data[i];
        else if( i==6 ) str_data = "Number of principal atoms      : " + input_data[i];
        else if( i==7 ) str_data = "MT for inelastic reaction      : " + input_data[i];
        else if( i==8 ) str_data = "Print options                  : " + input_data[i];
      }
      else
      {
        if( i==0 )      str_data = "Material number on Endf file   : " + input_data[i];
        else if( i==1 ) str_data = "Material number on Pendf file  : " + input_data[i];
        else if( i==2 ) str_data = "Number of equi-probable angles : " + input_data[i];
        else if( i==3 ) str_data = "Number of temperatures         : " + input_data[i];
        else if( i==4 ) str_data = "Inelastic option               : " + input_data[i];
        else if( i==5 ) str_data = "Elastic option                 : " + input_data[i];
        else if( i==6 ) str_data = "Output format (not used)       : " + input_data[i];
        else if( i==7 ) str_data = "Number of principal atoms      : " + input_data[i];
        else if( i==8 ) str_data = "MT for inelastic reaction      : " + input_data[i];
        else if( i==9 ) str_data = "Print options                  : " + input_data[i];
      }
      err_com.push_back(str_data);
    }
    err_com.push_back("");

    if( mat_pendf <= 0 )
    {
      err_com.push_back("Material number on Pendf file must be larger than 0.");
    }
    if( bin_no <= 0 )
    {
      err_com.push_back("Number of equi-probable angles must be larger than 0.");
    }
    if( temp_no <= 0 )
    {
      err_com.push_back("Number of temperatures must be larger than 0.");
    }
    if( opt_inelastic < 0 )
    {
      err_com.push_back("Inelastic option must be larger than or equal to 0.");
    }
    if( opt_elastic < 0 )
    {
      err_com.push_back("Elastic option must be larger than or equal to 0.");
    }
    if( atom_no <= 0 )
    {
      err_com.push_back("Number of principal atoms must be larger than 0.");
    }
    if( mt_out <= 0 )
    {
      err_com.push_back("MT for inelastic reaction must be larger than 0.");
    }
    if( opt_print > 2 || opt_print < 0 )
    {
      err_com.push_back("Print options in Card 2 is only available for 0, 1 and 2.");
    }

    err_com.push_back("Please check the input file.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  line_data.clear();
  clr_obj.clear_vec_array1_str(input_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermrInputReader::read_card03_data(ifstream& fin)
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
      string class_name = "ThermrInputReader";
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
    string class_name = "ThermrInputReader";
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

void ThermrInputReader::read_card04_data(ifstream& fin)
{
  string line_data;
  vector<string> input_data;

  //Card 04
  getline(fin, line_data);
  input_data = rn_obj.read_line_without_slash(line_data);

  if( static_cast<Integer>(input_data.size()) < 2 )
  {
    string class_name = "ThermrInputReader";
    string func_name  = "read_card04_data(ifstream& fin)";

    ostringstream oss01;
    oss01 << input_data.size();
    string str_data01 = "Input file name = " + input_thermr;
    string str_data02 = "Data no         = " + oss01.str();
    string str_data03 = "Input data      = " + line_data;

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("The data number in Card 4 is less than the required data no (2).");

    for(int i=0; i<static_cast<int>(input_data.size()); i++)
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

  err     = numeric_string_cast<Real8>(input_data[0]);
  ene_max = numeric_string_cast<Real8>(input_data[1]);

  if( err < min_value || ene_max < min_value )
  {
    string class_name = "ThermrInputReader";
    string func_name  = "read_card04_data(ifstream& fin)";

    ostringstream oss01, oss02;
    string str_data01 = "  tolerance      : " + oss01.str();
    string str_data02 = "  maximum energy : " + oss02.str();
    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);

    if( err < min_value )
    {
      err_com.push_back("Tolerance is less than or equal to zero.");
    }
    if( ene_max < min_value )
    {
      err_com.push_back("Maximum energy is less than or equal to zero.");
    }
    err_com.push_back("Please check input data.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
  
  line_data.clear();
  clr_obj.clear_vec_array1_str(input_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermrInputReader::clear()
{
  input_thermr.clear();
  endf_name.clear();
  pendf_name_old.clear();
  pendf_name_new.clear();

  mat_endf      = unassigned_mat_no;
  mat_pendf     = unassigned_mat_no;
  bin_no        = -1;
  temp_no       = -1;
  opt_inelastic = -1;
  opt_elastic   = -1;
  atom_no       = -1;
  mt_out        = unassigned_mt_no;
  opt_print     = -1;

  temp.clear();

  err     = 0.0;
  ene_max = 0.0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

string        ThermrInputReader::get_input_thermr()
{
  return input_thermr;
}

string        ThermrInputReader::get_endf_name()
{
  return endf_name;
}

string        ThermrInputReader::get_pendf_name_old()
{
  return pendf_name_old;
}

string        ThermrInputReader::get_pendf_name_new()
{
  return pendf_name_new;
}

Integer       ThermrInputReader::get_mat_endf()
{
  return mat_endf;
}

Integer       ThermrInputReader::get_mat_pendf()
{
  return mat_pendf;
}

Integer       ThermrInputReader::get_bin_no()
{
  return bin_no;
}

Integer       ThermrInputReader::get_temp_no()
{
  return temp_no;
}

Integer       ThermrInputReader::get_opt_inelastic()
{
  return opt_inelastic;
}

Integer       ThermrInputReader::get_opt_elastic()
{
  return opt_elastic;
}

Integer       ThermrInputReader::get_atom_no()
{
  return atom_no;
}

Integer       ThermrInputReader::get_mt_out()
{
  return mt_out;
}

Integer       ThermrInputReader::get_opt_print()
{
  return opt_print;
}

vector<Real8> ThermrInputReader::get_temp()
{
  return temp;
}

Real8         ThermrInputReader::get_err()
{
  return err;
}

Real8         ThermrInputReader::get_ene_max()
{
  return ene_max;
}

