#include "NjoyUtils/ReconrInputReader.hpp"

using namespace frendy;

ReconrInputReader::ReconrInputReader(void)
{
  clear();
}

ReconrInputReader::~ReconrInputReader(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ReconrInputReader::read_input(string file_name)
{
  read_input(file_name, 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ReconrInputReader::read_input(string file_name, int line_no)
{
  clear();

  input_reconr = file_name;

  //open input file
  ifstream fin(input_reconr.c_str());
  if( !fin )
  {
    string class_name = "ReconrInputReader";
    string func_name  = "read_input(string file_name)";

    string str_data = "File name : " + file_name;

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("There is no input file.");
    err_com.push_back("Please check the input file name.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //read until reconr input 
  string input_case = "reconr";
  rn_obj.search_each_input(fin, input_case, line_no);

  //read reconr input
  read_file_name(fin);
  read_mat_data(fin);

  fin.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ReconrInputReader::read_file_name(ifstream& fin)
{
  string line_data;
  vector<string> input_data;

  //Card 01
  getline(fin, line_data);
  input_data = rn_obj.read_line_without_slash(line_data);

  if( static_cast<int>(input_data.size()) < 2 )
  {
    string class_name = "ReconrInputReader";
    string func_name  = "read_file_name(ifstream& fin)";

    ostringstream oss;
    oss << input_data.size();
    string str_data01 = "Input file name = " + input_reconr;
    string str_data02 = "Data no         = " + oss.str();
    string str_data03 = "Input data      = " + line_data;

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("The data number of card 1 is less than 2.");
    err_com.push_back("In card 1, two integer data is required, i.e., nendf and npend.");
    err_com.push_back("Please check the input file.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  for(int i=0; i<2; i++)
  {
    int j = static_cast<int>(input_data[i].find_first_of("-"));
    if( j >= 0 )
    {
      string class_name = "ReconrInputReader";
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
  pendf_name = "tape" + input_data[1];

  //Card 02
  getline(fin, line_data);
  input_data = rn_obj.read_line(line_data);
  label_name = input_data[0]; 

  line_data.clear();
  clr_obj.clear_vec_array1_str(input_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ReconrInputReader::read_mat_data(ifstream& fin)
{
  string line_data;
  vector<string> input_data;
  int mat_no = 0;

  vector<string> cards_dummy;
  vector<Real8>  grid_dummy;

  //Card 03
  getline(fin, line_data);
  input_data = rn_obj.read_line_without_slash(line_data);

  if( static_cast<int>(input_data.size()) < 1 )
  {
    return;
  }

  if( numeric_string_cast<Integer>(input_data[0]) <= 0 )
  {
    string class_name = "ReconrInputReader";
    string func_name  = "read_mat_data(ifstream& fin)";

    string str_data = "Material number : " + input_data[0];

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("There is no material data.");
    err_com.push_back("Please check the input file.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  while( numeric_string_cast<Integer>(input_data[0]) > 0 )
  {
    mat.push_back(-1);
    ncards.push_back(0);
    ngrid.push_back(0);
    for(int i=0; i<static_cast<int>(input_data.size()); i++)
    {
      if( i==0 )
      {
        mat[mat_no] = numeric_string_cast<Integer>(input_data[i]);
      }
      else if( i==1 )
      {
        ncards[mat_no] = numeric_string_cast<Integer>(input_data[i]);
      }
      else if( i==2 )
      {
        ngrid[mat_no] = numeric_string_cast<Integer>(input_data[i]);
      }
    }
    if( mat[mat_no] < 0 )
    {
      string class_name = "ReconrInputReader";
      string func_name  = "read_mat_data(ifstream& fin)";

      ostringstream oss01;
      oss01 << mat[mat_no];
      string str_data01 = "Material number : " + oss01.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back("Please input mat number.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    //Card 04
    read_err_data(fin, mat_no);

    //Card 05
    cards.push_back(cards_dummy);
    if( ncards[mat_no] > 0 )
    {
      cards[mat_no] = read_cards_data(fin, mat_no);
    }

    //Card 06
    grid.push_back(grid_dummy);
    if( ngrid[mat_no] > 0 )
    {
      grid[mat_no] = read_grid_data(fin, mat_no);
    }

    //check next line
    getline(fin, line_data);
    clr_obj.clear_vec_array1_str(input_data);
    input_data = rn_obj.read_line_without_slash(line_data);

    mat_no++;
  }
  line_data.clear();
  clr_obj.clear_vec_array1_str(input_data);
  clr_obj.clear_vec_array1_str(cards_dummy);
  grid_dummy.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ReconrInputReader::read_err_data(ifstream& fin, int& mat_no)
{
  string line_data;
  vector<string> input_data;

  //Card 04
  getline(fin, line_data);
  input_data = rn_obj.read_line_without_slash(line_data);

  if( static_cast<int>(input_data.size()) < 1 )
  {
    string class_name = "ReconrInputReader";
    string func_name  = "read_err_data(ifstream& fin)";

    ostringstream oss;
    oss << input_data.size();
    string str_data01 = "Input file name = " + input_reconr;
    string str_data02 = "Data no         = " + oss.str();
    string str_data03 = "Input data      = " + line_data;

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("The data number of card 4 is less than 1.");
    err_com.push_back("In card 4, one real data is required, i.e., err.");
    err_com.push_back("Please check the input file.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  err.push_back(-1.0);
  err_max.push_back(-1.0);
  err_int.push_back(-1.0);
  tempr.push_back(0.0);
  for(int i=0; i<static_cast<int>(input_data.size()); i++)
  {
    if( i==0 )
    {
      err[mat_no] = numeric_string_cast<Real8>(input_data[i]);

      err_max[mat_no] = 10.0*err[mat_no];
      err_int[mat_no] = err[mat_no]/20000.0;
    }
    else if( i==1 )
    {
      tempr[mat_no] = numeric_string_cast<Real8>(input_data[i]);
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
  line_data.clear();
  clr_obj.clear_vec_array1_str(input_data);

  if( err[mat_no] < 0.0 )
  {
    string class_name = "ReconrInputReader";
    string func_name  = "read_mat_data(ifstream& fin)";

    ostringstream oss01;
    oss01 << err[mat_no];
    string str_data01 = "Error value : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("Please input error value.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> ReconrInputReader::read_cards_data(ifstream& fin, int& mat_no)
{
  string line_data;
  vector<string> input_data, cards_data;

  //Card 05
  for(int n=0; n<static_cast<int>(ncards[mat_no]); n++)
  {
    getline(fin, line_data);
    input_data = rn_obj.read_line(line_data);

    if( static_cast<int>(input_data.size()) < 1 )
    {
      cards_data.push_back(line_data);
    }
    else
    {
      cards_data.push_back(input_data[0]);
    }
  }
  line_data.clear();
  clr_obj.clear_vec_array1_str(input_data);
 
  return cards_data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<Real8> ReconrInputReader::read_grid_data(ifstream& fin, int& mat_no)
{
  string line_data;
  vector<string> input_data;
  vector<Real8>  grid_data; 

  int grid_no = static_cast<int>(ngrid[mat_no]);
  int tot_no  = 0;

  //Card 06
  grid_data.clear();
  while( tot_no < grid_no )
  {
    getline(fin, line_data);
    input_data = rn_obj.read_line_without_slash(line_data);

    int size = static_cast<int>(input_data.size());
    for(int i=0; i<size; i++)
    {
      if( tot_no >= grid_no )
      {
        break;
      }

      grid_data.push_back(numeric_string_cast<Real8>(input_data[i]));
      tot_no++;
    }

    if( fin.eof() )
    {
      string class_name = "ReconrInputReader";
      string func_name  = "read_grid_data(ifstream& fin, int& mat_no)";
      vector<string> err_com;
      err_com.push_back("The input file is reached the end until reading the temperature data.");
      err_com.push_back("The temperature data number may not be appropriate.");
      err_com.push_back("Please check input file.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }
  line_data.clear();
  clr_obj.clear_vec_array1_str(input_data);

  return grid_data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ReconrInputReader::clear()
{
  input_reconr.clear();
  endf_name.clear();
  pendf_name.clear();
  label_name.clear();

  mat.clear();
  ncards.clear();
  ngrid.clear();
  err.clear();
  err_max.clear();
  err_int.clear();
  tempr.clear();

  clr_obj.clear_vec_array2_str(cards);
  clr_obj.clear_vec_array2_real8(grid);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

string                  ReconrInputReader::get_input_reconr()
{
  return input_reconr;
}

string                  ReconrInputReader::get_endf_name()
{
  return endf_name;
}

string                  ReconrInputReader::get_pendf_name()
{
  return pendf_name;
}

string                  ReconrInputReader::get_label_name()
{
  return label_name;
}

vector<Integer>         ReconrInputReader::get_mat()
{
  return mat;
}

vector<Integer>         ReconrInputReader::get_ncards()
{
  return ncards;
}

vector<Integer>         ReconrInputReader::get_ngrid()
{
  return ngrid;
}

vector<Real8>           ReconrInputReader::get_err()
{
  return err;
}

vector<Real8>           ReconrInputReader::get_err_max()
{
  return err_max;
}

vector<Real8>           ReconrInputReader::get_err_int()
{
  return err_int;
}

vector<Real8>           ReconrInputReader::get_tempr()
{
  return tempr;
}

vector<vector<string> > ReconrInputReader::get_cards()
{
  return cards;
}

vector<vector<Real8> >  ReconrInputReader::get_grid()
{
  return grid;
}

