#include "EndfUtils/MFxxMTyyyParser/MF09Parser.hpp"

using namespace frendy;

//constructor
MF09Parser::MF09Parser(void)
{
  clear();

  err_obj.set_output_mode(err_obj.warning_off);
}

//destructor
MF09Parser::~MF09Parser(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF09Parser::store_data()
{
  MultiParser mp_obj;

  //Text file data check
  if( static_cast<Integer>(text.size()) < 1 )
  {
    string class_name = "MF09Parser";
    string func_name  = "store_data()";

    ostringstream oss;
    oss << static_cast<Integer>(text.size());
    string str_data = "Text line number : " + oss.str();

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("The text line number is not appropriate for MF=09.");
    err_com.push_back("The text line number should be larger than 1.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //Check MF number
  if( mp_obj.check_mf(text, mf_no) != 0)
  {
    string class_name = "MF09Parser";
    string func_name  = "store_data()";

    ostringstream oss01;
    oss01 << mf_no;
    string str_data01 = "Text data at first line : " + text[0];
    string str_data02 = "File number (MF)        : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("The MF number is different to MF=09.");

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
  //ZA, AWR, LIS, NS
  mp_obj.read_head(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3]);
  ZA  = r_vec[0];
  AWR = r_vec[1];
  LIS = i_vec[0];
  NS  = i_vec[2];

  if( static_cast<int>(text.size()) != line_no && NS == 0 )
  {
    string class_name = "MF09Parser";
    string func_name  = "store_data()";

    ostringstream oss01, oss02;
    oss01 << mt_no;
    oss01 << static_cast<int>(text.size());
    string str_data01 = "MT number                 : " + oss01.str();
    string str_data02 = "Text data at first line   : "  + text[0];
    string str_data03 = "Total line number of MF=9 : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("");
    err_com.push_back("Though NS is equal to 0, TAB1 data is found.");
    err_com.push_back("NS is modified from 0 to 1.");
    err_com.push_back("This modification may be incorrect.");
    err_com.push_back("Please check the nuclear data file");

    err_obj.output_caution(class_name, func_name, err_com);

    NS = 1;
  }

  int ns = static_cast<int>(NS);
  QM.resize(  ns);
  QI.resize(  ns);
  IZAP.resize(ns);
  LFS.resize( ns);
  NBT_Y.resize(  ns);
  INT_Y.resize(  ns);
  E_INT_Y.resize(ns);
  Y_TAB.resize(  ns);

  for(int i=0; i<ns; i++)
  {
    vector<Integer> nbt_vec, int_vec;
    vector<Real>    e_vec,   ap_vec;
    mp_obj.read_tab1(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                     nbt_vec, int_vec, e_vec, ap_vec);

    QM[i]   = r_vec[0];
    QI[i]   = r_vec[1];
    IZAP[i] = i_vec[0];
    LFS[i]  = i_vec[1];

    NBT_Y[i]   = nbt_vec;
    INT_Y[i]   = int_vec;
    E_INT_Y[i] = e_vec;
    Y_TAB[i]   = ap_vec;
    nbt_vec.clear();
    int_vec.clear();
    e_vec.clear();
    ap_vec.clear();
  }
  r_vec.clear();
  i_vec.clear();

  mp_obj.line_no_check(text, line_no, mf_no, mt_no);

  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF09Parser::clear()
{
  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);

  mat_no = unassigned_mat_no;
  mt_no  = unassigned_mt_no;
  ZA     = 0.0;
  AWR    = 0.0;
  LIS    = 0;
  NS     = 0;

  QM.clear();
  QI.clear();
  IZAP.clear();
  LFS.clear();

  clr_vec.clear_vec_array2_int( NBT_Y);
  clr_vec.clear_vec_array2_int( INT_Y);
  clr_vec.clear_vec_array2_real(E_INT_Y);
  clr_vec.clear_vec_array2_real(Y_TAB);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF09Parser::set_text(vector<string> text_data)
{
  clear();

  text = text_data;
  store_data();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string>           MF09Parser::get_text()
{
  return text;
}

Integer                  MF09Parser::get_mat_no()
{
  return mat_no;
}

Integer                  MF09Parser::get_mt_no()
{
  return mt_no;
}

//Getter at line No.01-02
Real                     MF09Parser::get_ZA()
{
  return ZA;
}

Real                     MF09Parser::get_AWR()
{
  return AWR;
}

Integer                  MF09Parser::get_LIS()
{
  return LIS;
}

Integer                  MF09Parser::get_NS()
{
  return NS;
}

vector<Real>             MF09Parser::get_QM()
{
  return QM;
}

vector<Real>             MF09Parser::get_QI()
{
  return QI;
}

vector<Integer>          MF09Parser::get_IZAP()
{
  return IZAP;
}

vector<Integer>          MF09Parser::get_LFS()
{
  return LFS;
}

vector<vector<Integer> > MF09Parser::get_NBT_Y()
{
  return NBT_Y;
}

vector<vector<Integer> > MF09Parser::get_INT_Y()
{
  return INT_Y;
}

vector<vector<Real> >    MF09Parser::get_E_INT_Y()
{
  return E_INT_Y;
}

vector<vector<Real> >    MF09Parser::get_Y_TAB()
{
  return Y_TAB;
}


////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void MF09Parser::set_mat_no(Integer& int_data)
{
  mat_no = int_data;
}

void MF09Parser::set_mt_no(Integer& int_data)
{
  mt_no = int_data;
}

void MF09Parser::set_ZA(Real& real_data)
{
  ZA = real_data;
}

void MF09Parser::set_AWR(Real& real_data)
{
  AWR = real_data;
}

void MF09Parser::set_LIS(Integer& int_data)
{
  LIS = int_data;
}

void MF09Parser::set_NS(Integer& int_data)
{
  NS = int_data;
}

void MF09Parser::set_QM(vector<Real>& real_vec)
{
  QM = real_vec;
}

void MF09Parser::set_QI(vector<Real>& real_vec)
{
  QI = real_vec;
}

void MF09Parser::set_IZAP(vector<Integer>& int_vec)
{
  IZAP = int_vec;
}

void MF09Parser::set_LFS(vector<Integer>& int_vec)
{
  LFS = int_vec;
}

void MF09Parser::set_NBT_Y(vector<vector<Integer> >& int_vec)
{
  NBT_Y = int_vec;
}

void MF09Parser::set_INT_Y(vector<vector<Integer> >& int_vec)
{
  INT_Y = int_vec;
}

void MF09Parser::set_E_INT_Y(vector<vector<Real> >& real_vec)
{
  E_INT_Y = real_vec;
}

void MF09Parser::set_Y_TAB(vector<vector<Real> >& real_vec)
{
  Y_TAB = real_vec;
}

