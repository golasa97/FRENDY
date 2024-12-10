#include "NjoyUtils/BroadrInputReader.hpp"

using namespace frendy;

BroadrInputReader::BroadrInputReader(void)
{
  clear();
}

BroadrInputReader::~BroadrInputReader(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void BroadrInputReader::read_input(string file_name)
{
  read_input(file_name, 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void BroadrInputReader::read_input(string file_name, int line_no)
{
  clear();

  input_broadr = file_name;

  //open input file
  ifstream fin(input_broadr.c_str());
  if( !fin )
  {
    string class_name = "BroadrInputReader";
    string func_name  = "read_input(string file_name)";

    string str_data = "File name : " + file_name;

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("There is no input file.");
    err_com.push_back("Please check the input file name.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //read until broadr input 
  string input_case = "broadr";
  rn_obj.search_each_input(fin, input_case, line_no);

  //read broadr input
  read_file_name(fin);
  read_mat_data(fin);

  fin.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void BroadrInputReader::read_file_name(ifstream& fin)
{
  string line_data;
  vector<string> input_data;

  //Card 01
  getline(fin, line_data);
  input_data = rn_obj.read_line_without_slash(line_data);

  if( static_cast<int>(input_data.size()) < 3 )
  {
    string class_name = "BroadrInputReader";
    string func_name  = "read_file_name(ifstream& fin)";

    ostringstream oss;
    oss << input_data.size();
    string str_data01 = "Input file name = " + input_broadr;
    string str_data02 = "Data no         = " + oss.str();
    string str_data03 = "Input data      = " + line_data;

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("The data number of card 1 is less than 3.");
    err_com.push_back("In card 1, three integer data are required, i.e., nendf, nin, and nout.");
    err_com.push_back("Please check the input file.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  for(int i=0; i<3; i++)
  {
    int j = static_cast<int>(input_data[i].find_first_of("-"));
    if( j >= 0 )
    {
      string class_name = "BroadrInputReader";
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

  endf_name  = "tape" + input_data[0];
  pendf_in   = "tape" + input_data[1];
  pendf_out  = "tape" + input_data[2];

  line_data.clear();
  clr_obj.clear_vec_array1_str(input_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void BroadrInputReader::read_mat_data(ifstream& fin)
{
  string line_data;
  vector<string> input_data;
  int mat_no = 0;
  
  getline(fin, line_data);
  input_data = rn_obj.read_line_without_slash(line_data);

  if( static_cast<int>(input_data.size()) < 1 )
  {
    string class_name = "BroadrInputReader";
    string func_name  = "read_mat_data(ifstream& fin)";

    ostringstream oss;
    oss << input_data.size();
    string str_data01 = "Input file name = " + input_broadr;
    string str_data02 = "Data no         = " + oss.str();
    string str_data03 = "Input data      = " + line_data;

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("The data number of card 2 is less than 1.");
    err_com.push_back("In card 2, more than or equal to one integer data is required, i.e., mat1.");
    err_com.push_back("Please check the input file.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  if( numeric_string_cast<Integer>(input_data[0]) <= 0 )
  {
    string class_name = "BroadrInputReader";
    string func_name  = "read_mat_data(ifstream& fin)";

    string str_data = "Material number : " + input_data[0];

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("There is no material data.");
    err_com.push_back("Please check the input file.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  int copy_flg = 0;
  while( numeric_string_cast<Integer>(input_data[0]) > 0 )
  {
    if( copy_flg < 100 )
    {
      //Card 02
      read_mat_no(fin, mat_no, input_data);
    }
    else
    {
      mat.push_back(copy_flg);
      temp_no.push_back(temp_no[mat_no-1]);
      istart.push_back(istart[mat_no-1]);
      istrap.push_back(istrap[mat_no-1]);
      temp_ini.push_back(temp_ini[mat_no-1]);
    }

    //Card 03
    read_err_data(fin, mat_no, copy_flg, input_data);
    if( copy_flg == 0 )
    {
      //Card 04
      read_temp_data(fin, mat_no);
    }
    else
    {
      temp_no[mat_no]     = temp_no[mat_no-1];
      istart[mat_no]      = istart[mat_no-1];
      istrap[mat_no]      = istrap[mat_no-1];
      temp_ini[mat_no]    = temp_ini[mat_no-1];

      err.push_back(err[mat_no-1]);
      err_max.push_back(err_max[mat_no-1]);
      err_int.push_back(err_int[mat_no-1]);
      dop_ene_max.push_back(dop_ene_max[mat_no-1]);
      temp.push_back(temp[mat_no-1]);

      if(copy_flg < 100)
      {
        break;
      }

      mat_no++;
      continue;
    }

    //check next line
    getline(fin, line_data);
    clr_obj.clear_vec_array1_str(input_data);
    input_data = rn_obj.read_line_without_slash(line_data);

    mat_no++;
  }
  line_data.clear();
  clr_obj.clear_vec_array1_str(input_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void BroadrInputReader::read_mat_no(ifstream& fin, int& mat_no, vector<string>& input_data)
{
  //Card 02
  //initialize input data
  mat.push_back(-1);
  temp_no.push_back(1);
  istart.push_back(0);
  istrap.push_back(0);
  temp_ini.push_back(0.0);
  
  int i_max = static_cast<int>(input_data.size());
  for(int i=0; i<i_max; i++)
  {
    if( i==0 )
    {
      mat[mat_no] = numeric_string_cast<Integer>(input_data[i]);
    }
    else if( i==1 )
    {
      temp_no[mat_no] = numeric_string_cast<Integer>(input_data[i]);
    }
    else if( i==2 )
    {
      istart[mat_no] = numeric_string_cast<Integer>(input_data[i]);
    }
    else if( i==3 )
    {
      istrap[mat_no] = numeric_string_cast<Integer>(input_data[i]);
    }
    else if( i==4 )
    {
      temp_ini[mat_no] = numeric_string_cast<Real8>(input_data[i]);
    }
  }

  if( ( mat[mat_no] <= 0 ) || ( temp_no[mat_no] <= 0 ) || ( istart[mat_no] != 0 && istart[mat_no] != 1 ) ||
      ( istrap[mat_no] != 0 && istrap[mat_no] != 1 ) || ( temp_ini[mat_no] < 0.0 ) )
  {
    string class_name = "BroadrInputReader";
    string func_name  = "read_mat_no(ifstream& fin, int& mat_no, vector<string>& input_data)";

    ostringstream oss01, oss02, oss03, oss04, oss05;
    oss01 << mat[mat_no]; 
    oss02 << temp_no[mat_no];
    oss03 << istart[mat_no];
    oss04 << istrap[mat_no];
    oss05 << temp_ini[mat_no];
    string str_data01 = "Material number              : " + oss01.str();
    string str_data02 = "Number of final temperatures : " + oss02.str();
    string str_data03 = "istart value                 : " + oss03.str();
    string str_data04 = "istrap value                 : " + oss04.str();
    string str_data05 = "Starting temperature         : " + oss05.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back(str_data05);

    if( mat[mat_no] <= 0 )
    {
      err_com.push_back("Please input material number.");
    }
    if( temp_no[mat_no] <= 0 )
    {
      err_com.push_back("Please input number of final temperatures");
    }
    if( istart[mat_no] != 0 && istart[mat_no] != 1 )
    {
      err_com.push_back("istart value must be 0 or 1.");
    }
    if( istrap[mat_no] != 0 && istrap[mat_no] != 1 )
    {
      err_com.push_back("istrap value must be 0 or 1.");
    }
    if( temp_ini[mat_no] < 0.0 )
    {
      err_com.push_back("Starting temperature must be larger than 0.0.");
    }
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
  clr_obj.clear_vec_array1_str(input_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void BroadrInputReader::read_err_data(ifstream& fin, int& mat_no, int& copy_flg,
                                      vector<string>& input_data)
{
  //Card 03
  string line_data;

  getline(fin, line_data);
  input_data = rn_obj.read_line_without_slash(line_data);

  int i_max = static_cast<int>(input_data.size());
  if( i_max < 1 )
  {
    string class_name = "BroadrInputReader";
    string func_name  = "read_err_data(ifstream& fin)";

    ostringstream oss;
    oss << input_data.size();
    string str_data01 = "Input file name = " + input_broadr;
    string str_data02 = "Data no         = " + oss.str();
    string str_data03 = "Input data      = " + line_data;

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("The data number of card 3 is less than 1.");
    err_com.push_back("In card 3, more than or equal to onereal data is required, i.e., errthn");
    err_com.push_back("Please check the input file.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  copy_flg = 0;
  for(int i=0; i<i_max; i++)
  {
    if( i==0 )
    {
      if( mat_no > 0 && (fabs(numeric_string_cast<Real8>(input_data[i])) < min_value ||
                         fabs(numeric_string_cast<Real8>(input_data[i])) > 99.0)     )
      {
        if( fabs(numeric_string_cast<Real8>(input_data[i])) < min_value )
        {
          copy_flg = 1;
        }
        else
        {
          copy_flg = numeric_string_cast<Integer>(input_data[i]);
        }
        return;
      }
      else
      {
        //initialize input data
        err.push_back(-1.0);
        err_max.push_back(-1.0);
        err_int.push_back(-1.0);
        dop_ene_max.push_back(dop_ene_max_def);
      }
      err[mat_no] = numeric_string_cast<Real8>(input_data[i]);

      err_max[mat_no] = 10.0*err[mat_no];
      err_int[mat_no] = err[mat_no]/20000.0;
    }
    else if( i==1 )
    {
      dop_ene_max[mat_no] = numeric_string_cast<Real8>(input_data[i]);
    }
    else if( i==2 )
    {
      err_max[mat_no] = numeric_string_cast<Real8>(input_data[i]);
      if( fabs(err_max[mat_no]) < min_value )
      {
        err_max[mat_no] = 10.0*err[mat_no];
      }
      else if( err_max[mat_no] < err[mat_no] )
      {
        err_max[mat_no] = err[mat_no];
      }
    }
    else if( i==3 )
    {
      err_int[mat_no] = numeric_string_cast<Real8>(input_data[i]);
      if( fabs(err_int[mat_no]) < min_value )
      {
        err_int[mat_no] = err[mat_no]/20000.0;
      }
    }
  }
  if( err[mat_no] < 0.0 || err_int[mat_no] < 0.0 )
  {
    string class_name = "BroadrInputReader";
    string func_name  = "read_err_data(ifstream& fin, int& mat_no)";

    ostringstream oss01, oss02;
    oss01 << err[mat_no];
    oss02 << err_int[mat_no];
    string str_data01 = "err     : " + oss01.str();
    string str_data02 = "err_int : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    if( err[mat_no] < 0.0 )
    {
      err_com.push_back("Please input error value.");
    }
    if( err_int[mat_no] < 0.0 )
    {
      err_com.push_back("Err int must be larger than 0.0.");
    }
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
  line_data.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void BroadrInputReader::read_temp_data(ifstream& fin, int& mat_no)
{
  //Card 04
  string line_data;
  vector<string> input_data;
  
  int ele_no = 0;
  vector<Real8> temp_vec;
  temp_vec.resize(static_cast<int>(temp_no[mat_no]));
  while( ele_no < temp_no[mat_no] )
  {
    getline(fin, line_data);
    input_data = rn_obj.read_line_without_slash(line_data);

    int i_max = static_cast<int>(input_data.size());
    for(int i=0; i<i_max; i++)
    {
      temp_vec[ele_no] = numeric_string_cast<Real8>(input_data[i]);
      ele_no++;
      
      if( ele_no >= temp_no[mat_no] )
      {
        break;
      }
    }

    if( fin.eof() )
    {
      string class_name = "BroadrInputReader";
      string func_name  = "read_temp_data(ifstream& fin, int& mat_no)";
      vector<string> err_com;
      err_com.push_back("The input file is reached the end until reading the temperature data.");
      err_com.push_back("The temperature data number may not be appropriate.");
      err_com.push_back("Please check input file.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }
  temp.push_back(temp_vec);
  temp_vec.clear();
  line_data.clear();
  clr_obj.clear_vec_array1_str(input_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void BroadrInputReader::clear()
{
  input_broadr.clear();
  endf_name.clear();
  pendf_in.clear();
  pendf_out.clear();

  mat.clear();
  temp_no.clear();
  istart.clear();
  istrap.clear();
  temp_ini.clear();
  err.clear();
  err_max.clear();
  err_int.clear();
  dop_ene_max.clear();

  clr_obj.clear_vec_array2_real8(temp);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

string                  BroadrInputReader::get_input_broadr()
{
  return input_broadr;
}

string                  BroadrInputReader::get_endf_name()
{
  return endf_name;
}

string                  BroadrInputReader::get_pendf_input_name()
{
  return pendf_in;
}

string                  BroadrInputReader::get_pendf_output_name()
{
  return pendf_out;
}

vector<Integer>         BroadrInputReader::get_mat()
{
  return mat;
}

vector<Integer>         BroadrInputReader::get_temp_no()
{
  return temp_no;
}

vector<Integer>         BroadrInputReader::get_istart()
{
  return istart;
}

vector<Integer>         BroadrInputReader::get_istrap()
{
  return istrap;
}

vector<Real8>           BroadrInputReader::get_temp_ini()
{
  return temp_ini;
}

vector<Real8>           BroadrInputReader::get_err()
{
  return err;
}

vector<Real8>           BroadrInputReader::get_err_max()
{
  return err_max;
}

vector<Real8>           BroadrInputReader::get_err_int()
{
  return err_int;
}

vector<Real8>           BroadrInputReader::get_dop_ene_max()
{
  return dop_ene_max;
}

vector<vector<Real8> > BroadrInputReader::get_temp()
{
  return temp;
}


