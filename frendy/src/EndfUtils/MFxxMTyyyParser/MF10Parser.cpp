#include "EndfUtils/MFxxMTyyyParser/MF10Parser.hpp"

using namespace frendy;

//constructor
MF10Parser::MF10Parser(void)
{
  clear();

  err_obj.set_output_mode(err_obj.warning_off);
}

//destructor
MF10Parser::~MF10Parser(void)
{ 
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF10Parser::store_data() 
{
  MultiParser mp_obj;

  //Text file data check
  if( static_cast<Integer>(text.size()) < 1 )
  {
    string class_name = "MF10Parser";
    string func_name  = "store_data()";

    ostringstream oss;
    oss << static_cast<Integer>(text.size());
    string str_data = "Text line number : " + oss.str();

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("The text line number is not appropriate for MF=10.");
    err_com.push_back("The text line number should be larger than 1.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //Check MF number
  if( mp_obj.check_mf(text, mf_no) != 0)
  {
    string class_name = "MF10Parser";
    string func_name  = "store_data()";

    ostringstream oss01;
    oss01 << mf_no;
    string str_data01 = "Text data at first line : " + text[0];
    string str_data02 = "File number (MF)        : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("The MF number is different to MF=10.");

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

  int ns = static_cast<int>(NS);
  QM.resize(  ns);
  QI.resize(  ns);
  IZAP.resize(ns);
  LFS.resize( ns);
  NBT_S.resize(  ns);
  INT_S.resize(  ns);
  E_INT_S.resize(ns);
  S_TAB.resize(  ns);

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

    NBT_S[i]   = nbt_vec;
    INT_S[i]   = int_vec;
    E_INT_S[i] = e_vec;
    S_TAB[i]   = ap_vec;
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

void MF10Parser::clear()
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

  clr_vec.clear_vec_array2_int( NBT_S);
  clr_vec.clear_vec_array2_int( INT_S);
  clr_vec.clear_vec_array2_real(E_INT_S);
  clr_vec.clear_vec_array2_real(S_TAB);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF10Parser::set_text(vector<string> text_data)
{
  clear();

  text = text_data;
  store_data();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string>           MF10Parser::get_text()
{
  return text;
}

Integer                  MF10Parser::get_mat_no()
{
  return mat_no;
}

Integer                  MF10Parser::get_mt_no()
{
  return mt_no;
}

//Getter at line No.01-02
Real                     MF10Parser::get_ZA()
{
  return ZA;
}

Real                     MF10Parser::get_AWR()
{
  return AWR;
}

Integer                  MF10Parser::get_LIS()
{
  return LIS;
}

Integer                  MF10Parser::get_NS()
{
  return NS;
}

vector<Real>             MF10Parser::get_QM()
{
  return QM;
}

vector<Real>             MF10Parser::get_QI()
{
  return QI;
}

vector<Integer>          MF10Parser::get_IZAP()
{
  return IZAP;
}

vector<Integer>          MF10Parser::get_LFS()
{
  return LFS;
}

vector<vector<Integer> > MF10Parser::get_NBT_S()
{
  return NBT_S;
}

vector<vector<Integer> > MF10Parser::get_INT_S()
{
  return INT_S;
}

vector<vector<Real> >    MF10Parser::get_E_INT_S()
{
  return E_INT_S;
}

vector<vector<Real> >    MF10Parser::get_S_TAB()
{
  return S_TAB;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void MF10Parser::set_mat_no(Integer& int_data)
{
  mat_no = int_data;
}

void MF10Parser::set_mt_no(Integer& int_data)
{
  mt_no = int_data;
}


void MF10Parser::set_ZA(Real& real_data)
{
  ZA = real_data;
}

void MF10Parser::set_AWR(Real& real_data)
{
  AWR = real_data;
}

void MF10Parser::set_LIS(Integer& int_data)
{
  LIS = int_data;
}

void MF10Parser::set_NS(Integer& int_data)
{
  NS = int_data;
}

void MF10Parser::set_QM(vector<Real>& real_vec)
{
  QM = real_vec;
}

void MF10Parser::set_QI(vector<Real>& real_vec)
{
  QI = real_vec;
}

void MF10Parser::set_IZAP(vector<Integer>& int_vec)
{
  IZAP = int_vec;
}

void MF10Parser::set_LFS(vector<Integer>& int_vec)
{
  LFS = int_vec;
}

void MF10Parser::set_NBT_S(vector<vector<Integer> >& int_vec)
{
  NBT_S = int_vec;
}

void MF10Parser::set_INT_S(vector<vector<Integer> >& int_vec)
{
  INT_S = int_vec;
}

void MF10Parser::set_E_INT_S(vector<vector<Real> >& real_vec)
{
  E_INT_S = real_vec;
}

void MF10Parser::set_S_TAB(vector<vector<Real> >& real_vec)
{
  S_TAB = real_vec;
}

