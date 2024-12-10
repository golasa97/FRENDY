#include "NjoyUtils/MatxsrInputReader.hpp"

using namespace frendy;

MatxsrInputReader::MatxsrInputReader(void)
{
  clear();
}

MatxsrInputReader::~MatxsrInputReader(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsrInputReader::read_input(string file_name)
{
  read_input(file_name, 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsrInputReader::read_input(string file_name, int line_no)
{
  clear();

  input_matxsr = file_name;

  //open input file
  ifstream fin(input_matxsr.c_str());
  if( !fin )
  {
    string class_name = "MatxsrInputReader";
    string func_name  = "read_input(string file_name)";

    string str_data = "File name : " + file_name;

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("There is no input file.");
    err_com.push_back("Please check the input file name.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //read until matxsr input 
  string input_case = "matxsr";
  rn_obj.search_each_input(fin, input_case, line_no);

  //read matxsr input
  read_file_name(fin);
  read_cards_two_and_three(fin);
  read_cards_four_to_nine(fin);
  read_card_ten(fin);

  fin.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsrInputReader::read_file_name(ifstream& fin)
{
  string line_data;
  vector<string> input_data;

  //Card 01
  getline(fin, line_data);
  input_data = rn_obj.read_line_without_slash(line_data);

  int i_max = static_cast<int>(input_data.size());
  if( i_max > 8 )
  {
    i_max = 8;
  }
  for(int i=0; i<i_max; i++)
  {
    int j = static_cast<int>(input_data[i].find_first_of("-"));
    if( j >= 0 )
    {
      string class_name = "MatxsrInputReader";
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

  if( i_max < 3 )
  {
    string class_name = "MatxsrInputReader";
    string func_name  = "read_file_name(ifstream& fin)";

    ostringstream oss;
    oss << input_data.size();
    string str_data01 = "Input file name = " + input_matxsr;
    string str_data02 = "Data no         = " + oss.str();
    string str_data03 = "Input data      = " + line_data;

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("The data number of card 1 is less than 3.");
    err_com.push_back("In card 1, more than or equal to three integer data are required, i.e., ngen1, ngen2, and nmatxs.");
    err_com.push_back("Please check the input file.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  group_file_name = "tape" + input_data[0];
  gamin_file_name = "tape" + input_data[1];
  matxs_name      = "tape" + input_data[2];

  proton_name   = "";
  if( i_max > 3 )
  {
    proton_name   = "tape" + input_data[3];
  }

  deuteron_name = "";
  if( i_max > 4 )
  {
    deuteron_name = "tape" + input_data[4];
  }

  triton_name   = "";
  if( i_max > 5 )
  {
    triton_name   = "tape" + input_data[5];
  }

  he_name   = "";
  if( i_max > 6 )
  {
    he_name       = "tape" + input_data[6];
  }

  alpha_name    = "";
  if( i_max > 7 )
  {
    alpha_name    = "tape" + input_data[7];
  }

  line_data.clear();
  clr_obj.clear_vec_array1_str(input_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsrInputReader::read_cards_two_and_three(ifstream& fin)
{
  string line_data;
  vector<string> input_data;

  //Card 02
  getline(fin, line_data);
  input_data = rn_obj.read_line_without_slash(line_data);
  int i_max = static_cast<int>(input_data.size());

  ivers = 0;
  if( i_max > 0 )
  {
    ivers = numeric_string_cast<Integer>(input_data[0]);
  }

  huse = "";
  if( i_max > 1 )
  {
    huse = input_data[1];
    if( static_cast<int>(huse.length()) > 16 )
    {
      huse = huse.substr(0, 16);
    }
  }

  //Card 03
  getline(fin, line_data);
  input_data = rn_obj.read_line_without_slash(line_data);

  if( static_cast<int>(input_data.size()) < 4 )
  {
    string class_name = "MatxsrInputReader";
    string func_name  = "read_cards_two_and_three(ifstream& fin)";

    ostringstream oss;
    oss << input_data.size();
    string str_data01 = "Input file name = " + input_matxsr;
    string str_data02 = "Data no         = " + oss.str();
    string str_data03 = "Input data      = " + line_data;

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("The data number of card 3 is less than 4.");
    err_com.push_back("In card 3, four integer data are required, i.e., npart, ntype, nholl, and nmat.");
    err_com.push_back("Please check the input file.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  npart = numeric_string_cast<Integer>(input_data[0]);
  ntype = numeric_string_cast<Integer>(input_data[1]);
  nholl = numeric_string_cast<Integer>(input_data[2]);
  nmat  = numeric_string_cast<Integer>(input_data[3]);

  line_data.clear();
  clr_obj.clear_vec_array1_str(input_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsrInputReader::read_cards_four_to_nine(ifstream& fin)
{
  string line_data;
  vector<string> input_data;

  //Card 4
  hsetid.resize(static_cast<int>(nholl));
  for(int i=0; i<static_cast<int>(nholl); i++)
  {
    getline(fin, line_data);
    if( fin.eof() )
    {
      string class_name = "MatxsrInputReader";
      string func_name  = "read_cards_four_to_nine(ifstream& fin)";
      vector<string> err_com;
      err_com.push_back("The input file is reached the end until reading the hsetid data in card 4.");
      err_com.push_back("The hsetid data number may not be appropriate.");
      err_com.push_back("Please check input file.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    input_data = rn_obj.read_line(line_data);
    hsetid[i] = "";
    if( static_cast<int>(input_data.size()) > 0 )
    {
      hsetid[i] = input_data[0];
    }

    if( static_cast<int>(hsetid[i].length()) > 72 )
    {
      hsetid[i] = hsetid[i].substr(0, 72);
    }
  }

  //Card 5
  hpart.resize(static_cast<int>(npart));
  int ele_no = 0;
  while( ele_no < npart )
  {
    getline(fin, line_data);
    input_data = rn_obj.read_line_without_slash(line_data);

    int i_max = static_cast<int>(input_data.size());
    for(int i=0; i<i_max; i++)
    {
      hpart[ele_no] = input_data[i];
      if( static_cast<int>(hpart[ele_no].length()) > 8 )
      {
        hpart[ele_no] = hpart[ele_no].substr(0, 8);
      }

      ele_no++;

      if( ele_no >= npart )
      {
        break;
      }
    }

    if( fin.eof() )
    {
      string class_name = "MatxsrInputReader";
      string func_name  = "read_cards_four_to_nine(ifstream& fin)";
      vector<string> err_com;
      err_com.push_back("The input file is reached the end until reading the hpart data in card 5.");
      err_com.push_back("The hpart data may not be appropriate.");
      err_com.push_back("Please check input file.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }

  //Card 6
  ngrp.resize(static_cast<int>(npart));

  ele_no = 0;
  while( ele_no < npart )
  {
    getline(fin, line_data);
    input_data = rn_obj.read_line_without_slash(line_data);

    int i_max = static_cast<int>(input_data.size());
    for(int i=0; i<i_max; i++)
    {
      ngrp[ele_no] = numeric_string_cast<Integer>(input_data[i]);
      ele_no++;

      if( ele_no >= npart )
      {
        break;
      }
    }

    if( fin.eof() )
    {
      string class_name = "MatxsrInputReader";
      string func_name  = "read_cards_four_to_nine(ifstream& fin)";
      vector<string> err_com;
      err_com.push_back("The input file is reached the end until reading the ngrp data in card 6.");
      err_com.push_back("The ngrp data may not be appropriate.");
      err_com.push_back("Please check input file.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }

  //Card 7
  htype.resize(static_cast<int>(ntype));

  ele_no = 0;
  while( ele_no < ntype )
  {
    getline(fin, line_data);
    input_data = rn_obj.read_line_without_slash(line_data);

    int i_max = static_cast<int>(input_data.size());
    for(int i=0; i<i_max; i++)
    {
      htype[ele_no] = input_data[i];
      if( static_cast<int>(htype[ele_no].length()) > 8 )
      {
        htype[ele_no] = htype[ele_no].substr(0, 8);
      }

      ele_no++;

      if( ele_no >= ntype )
      {
        break;
      }
    }

    if( fin.eof() )
    {
      string class_name = "MatxsrInputReader";
      string func_name  = "read_cards_four_to_nine(ifstream& fin)";
      vector<string> err_com;
      err_com.push_back("The input file is reached the end until reading the htype data in card 7.");
      err_com.push_back("The htype data may not be appropriate.");
      err_com.push_back("Please check input file.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }

  //Card 8
  jinp.resize(static_cast<int>(ntype));

  ele_no = 0;
  while( ele_no < ntype )
  {
    getline(fin, line_data);
    input_data = rn_obj.read_line_without_slash(line_data);

    int i_max = static_cast<int>(input_data.size());
    for(int i=0; i<i_max; i++)
    {
      jinp[ele_no] = numeric_string_cast<Integer>(input_data[i]);
      ele_no++;

      if( ele_no >= ntype )
      {
        break;
      }
    }

    if( fin.eof() )
    {
      string class_name = "MatxsrInputReader";
      string func_name  = "read_cards_four_to_nine(ifstream& fin)";
      vector<string> err_com;
      err_com.push_back("The input file is reached the end until reading the jinp data in card 8.");
      err_com.push_back("The jinp data may not be appropriate.");
      err_com.push_back("Please check input file.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }

  //Card 9
  joutp.resize(static_cast<int>(ntype));

  ele_no = 0;
  while( ele_no < ntype )
  {
    getline(fin, line_data);
    input_data = rn_obj.read_line_without_slash(line_data);

    int i_max = static_cast<int>(input_data.size());
    for(int i=0; i<i_max; i++)
    {
      joutp[ele_no] = numeric_string_cast<Integer>(input_data[i]);
      ele_no++;

      if( ele_no >= ntype )
      {
        break;
      }
    }

    if( fin.eof() )
    {
      string class_name = "MatxsrInputReader";
      string func_name  = "read_cards_four_to_nine(ifstream& fin)";
      vector<string> err_com;
      err_com.push_back("The input file is reached the end until reading the joutp data in card 9.");
      err_com.push_back("The joutp data may not be appropriate.");
      err_com.push_back("Please check input file.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }

  line_data.clear();
  clr_obj.clear_vec_array1_str(input_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsrInputReader::read_card_ten(ifstream& fin)
{
  string line_data;
  vector<string> input_data;

  int i_max = static_cast<int>(nmat);
  hmat.resize(i_max);
  matno.resize(i_max);
  matgg.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    getline(fin, line_data);

    if( fin.eof() )
    {
      string class_name = "MatxsrInputReader";
      string func_name  = "read_card_ten(ifstream& fin)";
      vector<string> err_com;
      err_com.push_back("The input file is reached the end until reading the joutp data in card 9.");
      err_com.push_back("The joutp data number may not be appropriate.");
      err_com.push_back("Please check input file.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    input_data = rn_obj.read_line_without_slash(line_data);
    if( static_cast<int>(input_data.size()) < 2 )
    {
      string class_name = "MatxsrInputReader";
      string func_name  = "read_card_ten(ifstream& fin)";

      ostringstream oss01, oss02, oss03;
      oss01 << i+1;
      oss02 << i_max;
      oss03 << input_data.size();
      string str_data01 = "Input file name = " + input_matxsr;
      string str_data02 = "Position        = " + oss01.str() + " / " + oss02.str();
      string str_data03 = "Data no         = " + oss03.str();
      string str_data04 = "Input data      = " + line_data;

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back(str_data04);
      err_com.push_back("The data number of card 10 is less than 2.");
      err_com.push_back("In card 10, one string data and one integer data are required, i.e., hmat, matno.");
      err_com.push_back("Please check the input file.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    line_data = input_data[0];
    if( static_cast<int>(line_data.length()) > 8 )
    {
      line_data = line_data.substr(0, 8);
    }
    hmat[i] = line_data;

    matno[i] = numeric_string_cast<Integer>(input_data[1]);

    matgg[i] = 100 * (matno[i] / 100);
    if( static_cast<int>(input_data.size()) > 2 )
    {
      matgg[i] = numeric_string_cast<Integer>(input_data[2]);
    }
  }

  line_data.clear();
  clr_obj.clear_vec_array1_str(input_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsrInputReader::clear()
{
  input_matxsr.clear();

  //Card 1
  group_file_name.clear();
  gamin_file_name.clear();
  matxs_name.clear();
  proton_name.clear();
  deuteron_name.clear();
  triton_name.clear();
  he_name.clear();
  alpha_name.clear();

  //Card 2
  ivers = 0;
  huse  = "";

  //Card 3
  npart = 0;
  ntype = 0;
  nholl = 0;
  nmat  = 0;

  //Card 6
  ngrp.clear();

  //Card 4, 5, 7-10
  clr_obj.clear_vec_array1_str(hsetid);
  clr_obj.clear_vec_array1_str(hpart);
  clr_obj.clear_vec_array1_str(htype);
  clr_obj.clear_vec_array1_str(hmat);
  jinp.clear();
  joutp.clear();

  matno.clear();
  matgg.clear();

  ngrp.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

string          MatxsrInputReader::get_input_matxsr()
{
  return input_matxsr;
}

string          MatxsrInputReader::get_group_file_name()
{
  return group_file_name;
}

string          MatxsrInputReader::get_gamin_file_name()
{
  return gamin_file_name;
}

string          MatxsrInputReader::get_matxs_name()
{
  return matxs_name;
}

string          MatxsrInputReader::get_proton_name()
{
  return proton_name;
}

string          MatxsrInputReader::get_deuteron_name()
{
  return deuteron_name;
}

string          MatxsrInputReader::get_triton_name()
{
  return triton_name;
}

string          MatxsrInputReader::get_he_name()
{
  return he_name;
}

string          MatxsrInputReader::get_alpha_name()
{
  return alpha_name;
}

Integer         MatxsrInputReader::get_ivers()
{
  return ivers;
}

string          MatxsrInputReader::get_huse()
{
  return huse;
}

Integer         MatxsrInputReader::get_npart()
{
  return npart;
}

Integer         MatxsrInputReader::get_ntype()
{
  return ntype;
}

Integer         MatxsrInputReader::get_nholl()
{
  return nholl;
}

Integer         MatxsrInputReader::get_nmat()
{
  return nmat;
}

vector<string>  MatxsrInputReader::get_hsetid()
{
  return hsetid;
}

vector<string>  MatxsrInputReader::get_hpart()
{
  return hpart;
}

vector<Integer> MatxsrInputReader::get_ngrp()
{
  return ngrp;
}

vector<string>  MatxsrInputReader::get_htype()
{
  return htype;
}

vector<Integer> MatxsrInputReader::get_jinp()
{
  return jinp;
}

vector<Integer> MatxsrInputReader::get_joutp()
{
  return joutp;
}

vector<string>  MatxsrInputReader::get_hmat()
{
  return hmat;
}

vector<Integer> MatxsrInputReader::get_matno()
{
  return matno;
}

vector<Integer> MatxsrInputReader::get_matgg()
{
  return matgg;
}


