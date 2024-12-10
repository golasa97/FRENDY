#include "EndfUtils/MFxxMTyyyParser/MF01MT456Parser.hpp"

using namespace frendy;

//constructor
MF01MT456Parser::MF01MT456Parser(void)
{
  clear();

  err_obj.set_output_mode(err_obj.warning_off);
}

//destructor
MF01MT456Parser::~MF01MT456Parser(void)
{ 
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF01MT456Parser::store_data() 
{
  MultiParser mp_obj;

  //Text file data check
  if( static_cast<Integer>(text.size()) < 2 )
  {
    string class_name = "MF01MT456Parser";
    string func_name  = "store_data()";

    ostringstream oss;
    oss << static_cast<Integer>(text.size());
    string str_data = "Text line number : " + oss.str();

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("The text line number is not appropriate for  MF=01, MT=456.");
    err_com.push_back("The text line number should be larger than 1.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //Check MT and MF number
  if( mp_obj.check_mf_mt(text, mf_no, mt_no) != 0)
  {
    string class_name = "MF01MT456Parser";
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
    err_com.push_back("The MF and MT numbers are different to MF=01, MT=456.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  mp_obj.get_mat(text, mat_no);

  int     line_no = 0;
  Integer tmp_int;
  Real    tmp_real;

  //Line No.01
  //ZA, AWR, LNU
  mp_obj.read_head(text, line_no, ZA, AWR, tmp_int, LNU, tmp_int, tmp_int);

  if( LNU == 1 ) 
  {
    mp_obj.read_list(text, line_no, tmp_real, tmp_real, tmp_int, tmp_int, NC, tmp_int, NU);
  }
  else if( LNU == 2 ) 
  {
    mp_obj.read_tab1(text, line_no, tmp_real, tmp_real, tmp_int, tmp_int, NR, NP, NBT, INT, E_INT, NU);
  }

  mp_obj.line_no_check(text, line_no, mf_no, mt_no);

  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF01MT456Parser::clear()
{
  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);

  mat_no = unassigned_mat_no;
  ZA     = 0;
  AWR    = 0.0;
  LNU    = 0;
  NC     = 0;
  NR     = 0;
  NP     = 0;
  NBT.clear();
  INT.clear();
  E_INT.clear();
  NU.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF01MT456Parser::set_text(vector<string> text_data)
{
  clear();

  text = text_data;
  store_data();
}

void MF01MT456Parser::set_mat_no(Integer int_data)
{
  mat_no = int_data;
}

//Getter at line No.01
void MF01MT456Parser::set_ZA(Real real_data)
{
  ZA = real_data;
}

void MF01MT456Parser::set_AWR(Real real_data)
{
  AWR = real_data;
}

void MF01MT456Parser::set_LNU(Integer int_data)
{
  LNU = int_data;
}

//Getter at line No.02
void MF01MT456Parser::set_NC(Integer int_data)
{
  NC = int_data;
}

void MF01MT456Parser::set_NR(Integer int_data)
{
  NR = int_data;
}

void MF01MT456Parser::set_NP(Integer int_data)
{
  NP = int_data;
}

void MF01MT456Parser::set_NBT(vector<Integer> int_vec)
{
  NBT = int_vec;
}

void MF01MT456Parser::set_INT(vector<Integer> int_vec)
{
  INT = int_vec;
}

void MF01MT456Parser::set_E_INT(vector<Real> real_vec)
{
  E_INT = real_vec;
}

void MF01MT456Parser::set_NU(vector<Real> real_vec)
{
  NU = real_vec;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> MF01MT456Parser::get_text()
{
  return text;
}

Integer MF01MT456Parser::get_mat_no()
{
  return mat_no;
}

//Getter at line No.01
Real MF01MT456Parser::get_ZA()
{
  return ZA;
}

Real MF01MT456Parser::get_AWR()
{
  return AWR;
}

Integer MF01MT456Parser::get_LNU()
{
  return LNU;
}

//Getter at line No.02
Integer MF01MT456Parser::get_NC()
{
  return NC;
}

Integer MF01MT456Parser::get_NR()
{
  return NR;
}

Integer MF01MT456Parser::get_NP()
{
  return NP;
}

vector<Integer> MF01MT456Parser::get_NBT()
{
  return NBT;
}

vector<Integer> MF01MT456Parser::get_INT()
{
  return INT;
}

vector<Real> MF01MT456Parser::get_E_INT()
{
  return E_INT;
}

vector<Real> MF01MT456Parser::get_NU()
{
  return NU;
}

