#include "EndfUtils/MFxxMTyyyParser/MF23Parser.hpp"

using namespace frendy;

//constructor
MF23Parser::MF23Parser(void)
{
  clear();

  err_obj.set_output_mode(err_obj.warning_off);
}

//destructor
MF23Parser::~MF23Parser(void)
{ 
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF23Parser::store_data() 
{
  MultiParser mp_obj;

  //Text file data check
  if( static_cast<Integer>(text.size()) < 2 )
  {
    string class_name = "MF23Parser";
    string func_name  = "store_data()";

    ostringstream oss;
    oss << static_cast<Integer>(text.size());
    string str_data = "Text line number : " + oss.str();

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("The text line number is not appropriate for MF=23.");
    err_com.push_back("The text line number should be larger than 1.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //Check MF number
  if( mp_obj.check_mf(text, mf_no) != 0)
  {
    string class_name = "MF23Parser";
    string func_name  = "store_data()";

    ostringstream oss01;
    oss01 << mf_no;
    string str_data01 = "Text data at first line : " + text[0];
    string str_data02 = "File number (MF)        : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("The MF number is different to MF=23.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  mp_obj.get_mat(text, mat_no);

  int             line_no = 0;
  vector<Real>    r_vec;
  vector<Integer> i_vec;
  r_vec.resize(6);
  i_vec.resize(6);

  //Get MT number
  mp_obj.get_mf_mt(text, i_vec[0], mt_no);

  //Line No.01
  //ZA, AWR
  mp_obj.read_head(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3]);
  ZA  = r_vec[0];
  AWR = r_vec[1];

  mp_obj.read_tab1(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                   NBT_S, INT_S, E_INT_S, S_TAB);
  EPE = r_vec[0];
  EFL = r_vec[1];
  
  r_vec.clear();
  i_vec.clear();

  mp_obj.line_no_check(text, line_no, mf_no, mt_no);

  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF23Parser::clear()
{
  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);

  mat_no = unassigned_mat_no;
  mt_no  = unassigned_mt_no;
  ZA     = 0.0;
  AWR    = 0.0;
  EPE    = 0.0;
  EFL    = 0.0;

  NBT_S.clear();
  INT_S.clear();
  E_INT_S.clear();
  S_TAB.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF23Parser::set_text(vector<string> text_data)
{
  clear();

  text = text_data;
  store_data();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string>  MF23Parser::get_text()
{
  return text;
}

Integer         MF23Parser::get_mat_no()
{
  return mat_no;
}

Integer         MF23Parser::get_mt_no()
{
  return mt_no;
}

Real            MF23Parser::get_ZA()
{
  return ZA;
}

Real            MF23Parser::get_AWR()
{
  return AWR;
}

Real            MF23Parser::get_EPE()
{
  return EPE;
}

Real            MF23Parser::get_EFL()
{
  return EFL;
}

vector<Integer> MF23Parser::get_NBT_S()
{
  return NBT_S;
}

vector<Integer> MF23Parser::get_INT_S()
{
  return INT_S;
}

vector<Real>    MF23Parser::get_E_INT_S()
{
  return E_INT_S;
}

vector<Real>    MF23Parser::get_S_TAB()
{
  return S_TAB;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void MF23Parser::set_mat_no(Integer& int_data)
{
  mat_no = int_data;
}

void MF23Parser::set_mt_no(Integer& int_data)
{
  mt_no = int_data;
}


void MF23Parser::set_ZA(Real& real_data)
{
  ZA = real_data;
}

void MF23Parser::set_AWR(Real& real_data)
{
  AWR = real_data;
}

void MF23Parser::set_EPE(Real& real_data)
{
  EPE = real_data;
}

void MF23Parser::set_EFL(Real& real_data)
{
  EFL = real_data;
}

void MF23Parser::set_NBT_S(vector<Integer>& int_vec)
{
  NBT_S = int_vec;
}

void MF23Parser::set_INT_S(vector<Integer>& int_vec)
{
  INT_S = int_vec;
}

void MF23Parser::set_E_INT_S(vector<Real>& real_vec)
{
  E_INT_S = real_vec;
}

void MF23Parser::set_S_TAB(vector<Real>& real_vec)
{
  S_TAB = real_vec;
}

