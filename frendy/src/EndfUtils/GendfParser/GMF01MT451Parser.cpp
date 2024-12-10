#include "EndfUtils/GendfParser/GMF01MT451Parser.hpp"

using namespace frendy;

//constructor
GMF01MT451Parser::GMF01MT451Parser(void)
{
  clear();

  err_obj.set_output_mode(err_obj.warning_off);
}

//destructor
GMF01MT451Parser::~GMF01MT451Parser(void)
{ 
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GMF01MT451Parser::store_data() 
{
  MultiParser mp_obj;

  //Text file data check
  if( static_cast<Integer>(text.size()) < 3 )
  {
    string class_name = "GMF01MT451Parser";
    string func_name  = "store_data()";

    ostringstream oss;
    oss << static_cast<Integer>(text.size());
    string str_data = "Text line number : " + oss.str();

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("The text line number is not appropriate for  MF=01, MT=451.");
    err_com.push_back("The text line number should be larger than 3.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //Check MT and MF number
  if( mp_obj.check_mf_mt(text, mf_no, mt_no) != 0)
  {
    string class_name = "GMF01MT451Parser";
    string func_name  = "store_data()";

    ostringstream oss01, oss02;
    oss01 << mf_no;
    oss02 << mt_no;
    string str_data01 = "Text data at first line : " + text[0];
    string str_data02 = "File number (MF)        : " + oss01.str();
    string str_data03 = "Section number (MT)     : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("The MF and MT numbers are different to MF=01, MT=451.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  mp_obj.get_mat(text, mat_no);

  int     line_no = 0;
  Integer tmp_int;
  Real    tmp_real;

  //Line No.01
  //ZA, AWR, 0, NSIGZ, NLIB, NTW
  mp_obj.read_head(text, line_no, ZA, AWR, tmp_int, NSIGZ, NLIB, NTW);  
  if( NLIB != -1 )
  {
    string class_name = "GMF01MT451Parser";
    string func_name  = "store_data()";

    ostringstream oss01;
    oss01 << NLIB;
    string str_data01 = "NLIB : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("This file may not be the GENDF formatted file.");
    err_com.push_back("Please check the setting file is correct or not.");

    err_obj.output_caution(class_name, func_name, err_com);
  }

  //Line No.02
  //TEMP, NGN, NGG
  vector<Real> e_vec;
  Integer NW = 0;
  mp_obj.read_list(text, line_no, TEMP, tmp_real, NGN, NGG, NW, tmp_int,
                   e_vec);

  int title_no = static_cast<int>(NTW);
  int sigz_no  = static_cast<int>(NSIGZ);
  int egn_no   = static_cast<int>(NGN) + 1;
  int egg_no   = static_cast<int>(NGG) + 1;
  if( static_cast<int>(e_vec.size()) != title_no + sigz_no + egn_no + egg_no )
  {
    string class_name = "GMF01MT451Parser";
    string func_name  = "store_data()";

    ostringstream oss01, oss02, oss03, oss04, oss05, oss06;
    oss01 << static_cast<int>(e_vec.size());
    oss02 << title_no;
    oss03 << sigz_no;
    oss04 << egn_no;
    oss05 << egg_no;
    oss06 << title_no + sigz_no + egn_no + egg_no;
    string str_data01 = "Number of list data (NW)               : " + oss01.str();
    string str_data02 = "Number of title data (NTW)             : " + oss02.str();
    string str_data03 = "Number of sig_zero data (NSIGZ)        : " + oss03.str();
    string str_data04 = "Number of particle energy grid (NGN+1) : " + oss04.str();
    string str_data05 = "Number of gammma energy grid (NGG+1)   : " + oss05.str();
    string str_data06 = "NTW + NSIG + NGN + 1 + NGG + 1         : " + oss06.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back(str_data05);
    err_com.push_back(str_data06);
    err_com.push_back("NW must be NTW + NSIG + NGN + 1 + NGG + 1.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  int ele_no = 0;

  TITLE.resize(title_no);
  for(int i=0; i<title_no; i++)
  {
    TITLE[i] = e_vec[ele_no];
    ele_no++;
  }

  SIGZ.resize(sigz_no);
  for(int i=0; i<sigz_no; i++)
  {
    SIGZ[i] = e_vec[ele_no];
    ele_no++;
  }

  EGN.resize(egn_no);
  for(int i=0; i<egn_no; i++)
  {
    EGN[i] = e_vec[ele_no];
    ele_no++;
  }

  EGG.resize(egg_no);
  for(int i=0; i<egg_no; i++)
  {
    EGG[i] = e_vec[ele_no];
    ele_no++;
  }

  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GMF01MT451Parser::clear()
{
  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);

  mat_no = unassigned_mat_no;
  ZA     = 0;
  AWR    = 0.0;
  NSIGZ  = 0;
  NLIB   = 0;
  NTW    = 0;

  TEMP   = 0.0;
  NGN    = 0;
  NGG    = 0;
  TITLE.clear();
  SIGZ.clear();
  EGN.clear();
  EGG.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GMF01MT451Parser::set_text(vector<string> text_data)
{
  clear();

  text = text_data;
  store_data();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> GMF01MT451Parser::get_text()
{
  return text;
}

Integer GMF01MT451Parser::get_mat_no()
{
  return mat_no;
}

//Getter at line No.01
Real GMF01MT451Parser::get_ZA()
{
  return ZA;
}

Real GMF01MT451Parser::get_AWR()
{
  return AWR;
}

Integer GMF01MT451Parser::get_NSIGZ()
{
//  return NSIGZ;
  return static_cast<Integer>(SIGZ.size());
}

Integer GMF01MT451Parser::get_NLIB()
{
  return NLIB;
}

Integer GMF01MT451Parser::get_NTW()
{
  return NTW;
}


//Getter at line No.02
Real GMF01MT451Parser::get_TEMP()
{
  return TEMP;
}

Integer GMF01MT451Parser::get_NGN()
{
  //return NGN;
  return static_cast<Integer>(EGN.size()) - 1;
}

Integer GMF01MT451Parser::get_NGG()
{
  //return NGG;
  return static_cast<Integer>(EGG.size()) - 1;
}

vector<Real> GMF01MT451Parser::get_TITLE()
{
  return TITLE;
}

vector<Real> GMF01MT451Parser::get_SIGZ()
{
  return SIGZ;
}

vector<Real> GMF01MT451Parser::get_EGN()
{
  return EGN;
}

vector<Real> GMF01MT451Parser::get_EGG()
{
  return EGG;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//Setter
void GMF01MT451Parser::set_mat_no(Integer int_data)
{
  mat_no = int_data;
}

//Setter at line No.01
void GMF01MT451Parser::set_ZA(Real real_data)
{
  ZA = real_data;
}

void GMF01MT451Parser::set_AWR(Real real_data)
{
  AWR = real_data;
}

void GMF01MT451Parser::set_NSIGZ(Integer int_data)
{
  NSIGZ = int_data;
}

void GMF01MT451Parser::set_NLIB(Integer int_data)
{
  NLIB = int_data;
}

void GMF01MT451Parser::set_NTW(Integer int_data)
{
  NTW = int_data;
}


//Setter at line No.02
void GMF01MT451Parser::set_TEMP(Real real_data)
{
  TEMP = real_data;
}

void GMF01MT451Parser::set_NGN(Integer int_data)
{
  NGN = int_data;
}

void GMF01MT451Parser::set_NGG(Integer int_data)
{
  NGG = int_data;
}

void GMF01MT451Parser::set_TITLE(vector<Real> real_vec)
{
  TITLE = real_vec;
}

void GMF01MT451Parser::set_SIGZ(vector<Real> real_vec)
{
  SIGZ = real_vec;
}

void GMF01MT451Parser::set_EGN(vector<Real> real_vec)
{
  EGN = real_vec;

  NGN = static_cast<Integer>(EGN.size()) - 1;
}

void GMF01MT451Parser::set_EGG(vector<Real> real_vec)
{
  EGG = real_vec;

  NGG = static_cast<Integer>(EGG.size()) - 1;
}

