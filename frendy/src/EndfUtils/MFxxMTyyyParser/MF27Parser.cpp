#include "EndfUtils/MFxxMTyyyParser/MF27Parser.hpp"

using namespace frendy;

//constructor
MF27Parser::MF27Parser(void)
{
  clear();

  err_obj.set_output_mode(err_obj.warning_off);
}

//destructor
MF27Parser::~MF27Parser(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF27Parser::store_data()
{
  MultiParser mp_obj;

  //Text file data check
  if( static_cast<Integer>(text.size()) < 2 )
  {
    string class_name = "MF27Parser";
    string func_name  = "store_data()";

    ostringstream oss;
    oss << static_cast<Integer>(text.size());
    string str_data = "Text line number : " + oss.str();

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("The text line number is not appropriate for MF=27.");
    err_com.push_back("The text line number should be larger than 1.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //Check MF number
  if( mp_obj.check_mf(text, mf_no) != 0)
  {
    string class_name = "MF27Parser";
    string func_name  = "store_data()";

    ostringstream oss01;
    oss01 << mf_no;
    string str_data01 = "Text data at first line : " + text[0];
    string str_data02 = "File number (MF)        : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("The MF number is different to MF=27.");

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
                   NBT_H, INT_H, Q_INT_H, H_TAB);
  Z = r_vec[1];

  r_vec.clear();
  i_vec.clear();

  mp_obj.line_no_check(text, line_no, mf_no, mt_no);

  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF27Parser::clear()
{
  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);

  mat_no = unassigned_mat_no;
  mt_no  = unassigned_mt_no;
  ZA     = 0.0;
  AWR    = 0.0;
  Z      = 0.0;

  NBT_H.clear();
  INT_H.clear();
  Q_INT_H.clear();
  H_TAB.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF27Parser::set_text(vector<string> text_data)
{
  clear();

  text = text_data;
  store_data();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string>  MF27Parser::get_text()
{
  return text;
}

Integer         MF27Parser::get_mat_no()
{
  return mat_no;
}

Integer         MF27Parser::get_mt_no()
{
  return mt_no;
}

Real            MF27Parser::get_ZA()
{
  return ZA;
}

Real            MF27Parser::get_AWR()
{
  return AWR;
}

Real            MF27Parser::get_Z()
{
  return Z;
}


vector<Integer> MF27Parser::get_NBT_H()
{
  return NBT_H;
}

vector<Integer> MF27Parser::get_INT_H()
{
  return INT_H;
}

vector<Real>    MF27Parser::get_Q_INT_H()
{
  return Q_INT_H;
}

vector<Real>    MF27Parser::get_H_TAB()
{
  return H_TAB;
}


vector<Integer> MF27Parser::get_NBT_F()
{
  return NBT_H;
}

vector<Integer> MF27Parser::get_INT_F()
{
  return INT_H;
}

vector<Real>    MF27Parser::get_E_INT_F()
{
  return Q_INT_H;
}

vector<Real>    MF27Parser::get_F_TAB()
{
  return H_TAB;
}


////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void MF27Parser::set_mat_no(Integer& int_data)
{
  mat_no = int_data;
}

void MF27Parser::set_mt_no(Integer& int_data)
{
  mt_no = int_data;
}

void MF27Parser::set_ZA(Real& real_data)
{
  ZA = real_data;
}

void MF27Parser::set_AWR(Real& real_data)
{
  AWR = real_data;
}

void MF27Parser::set_Z(Real& real_data)
{
  Z = real_data;
}

void MF27Parser::set_NBT_H(vector<Integer>& int_vec)
{
  NBT_H = int_vec;
}

void MF27Parser::set_INT_H(vector<Integer>& int_vec)
{
  INT_H = int_vec;
}

void MF27Parser::set_Q_INT_H(vector<Real>& real_vec)
{
  Q_INT_H = real_vec;
}

void MF27Parser::set_H_TAB(vector<Real>& real_vec)
{
  H_TAB = real_vec;
}

void MF27Parser::set_NBT_F(vector<Integer>& int_vec)
{
  NBT_H = int_vec;
}

void MF27Parser::set_INT_F(vector<Integer>& int_vec)
{
  INT_H = int_vec;
}

void MF27Parser::set_E_INT_F(vector<Real>& real_vec)
{
  Q_INT_H = real_vec;
}

void MF27Parser::set_F_TAB(vector<Real>& real_vec)
{
  H_TAB = real_vec;
}

