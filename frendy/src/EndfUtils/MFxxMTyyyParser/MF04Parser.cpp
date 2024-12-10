#include "EndfUtils/MFxxMTyyyParser/MF04Parser.hpp"

using namespace frendy;

//constructor
MF04Parser::MF04Parser(void)
{
  clear();

  err_obj.set_output_mode(err_obj.warning_off);
}

//destructor
MF04Parser::~MF04Parser(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF04Parser::store_data()
{
  MultiParser mp_obj;

  //Text file data check
  if( static_cast<Integer>(text.size()) < 2 )
  {
    string class_name = "MF04Parser";
    string func_name  = "store_data()";

    ostringstream oss;
    oss << static_cast<Integer>(text.size());
    string str_data = "Text line number : " + oss.str();

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("The text line number is not appropriate for MF=04.");
    err_com.push_back("The text line number should be larger than 1.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //Check MF number
  if( mp_obj.check_mf(text, mf_no) != 0)
  {
    string class_name = "MF04Parser";
    string func_name  = "store_data()";

    ostringstream oss01;
    oss01 << mf_no;
    string str_data01 = "Text data at first line : " + text[0];
    string str_data02 = "File number (MF)        : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("The MF number is different to MF=04.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  mp_obj.get_mat(text, mat_no);

  int     line_no = 0;
  Integer tmp_int;
  Real    tmp_real;

  //Get MT number
  mp_obj.get_mf_mt(text, tmp_int, mt_no);

  //Line No.01
  //ZA, AWR, LVT, LTT
  mp_obj.read_head(text, line_no, ZA, AWR, LVT, LTT, tmp_int, tmp_int);

  //Line No.02
  //LI, LCT
  if( LVT == 0 )
  {
    mp_obj.read_cont(text, line_no, tmp_real, tmp_real, LI, LCT, NK, NM);
  }
  else if( LVT == 1 )
  {
    mp_obj.read_list(text, line_no, tmp_real, tmp_real, LI, LCT, NK, NM, U);
  }
  else
  {
    string class_name = "MF04Parser";
    string func_name  = "store_data()";

    ostringstream oss00, oss01;
    oss00 << mt_no;
    oss01 << LVT;
    string str_data00 = "Section number (MT) : " + oss00.str();
    string str_data01 = "LVT                 : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data00);
    err_com.push_back(str_data01);
    err_com.push_back("This LVT value at MF=04 are not supported in this program.");
    err_com.push_back("The suppoted LVT is 0 and 1.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  if( LTT == 0 && LI == 1 )
  {

  }
  else if( LTT == 1 && LI == 0 )
  {
    store_ltt01(mp_obj, line_no);
  }
  else if( LTT == 2 && LI == 0 )
  {
    store_ltt02(mp_obj, line_no);
  }
  else if( LTT == 3 && LI == 0 )
  {
    //Legendre coefficients
    store_ltt01(mp_obj, line_no);

    //Tabulated data
    store_ltt02(mp_obj, line_no);
  }
  else
  {
    string class_name = "MF04Parser";
    string func_name  = "store_data()";

    ostringstream oss00, oss01, oss02;
    oss00 << mt_no;
    oss01 << LTT;
    oss01 << LI;
    string str_data00 = "Section number (MT) : " + oss00.str();
    string str_data01 = "LTT                 : " + oss01.str();
    string str_data02 = "LI                  : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data00);
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("These LTT and LI values at MF=04 are not supported in this program.");
    err_com.push_back("The suppoted LTT and LI is (LTT, LI) = (0, 1), (1, 0), (2, 0) and (3, 0)");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  mp_obj.line_no_check(text, line_no, mf_no, mt_no);

  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF04Parser::store_ltt01(MultiParser& mp_obj, int& line_no)
{
  vector<Real>    r_vec;
  vector<Integer> i_vec;
  r_vec.resize(6);
  i_vec.resize(6);

  mp_obj.read_tab2(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                   NBT_E_LTT01, INT_E_LTT01);

  NE_LTT01 = i_vec[3];

  int i_max = static_cast<int>(NE_LTT01);
  resize_matrix_ltt01(i_max);

  for(int i=0; i<i_max; i++)
  {
    vector<Real> e_vec;
    mp_obj.read_list(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                     e_vec);

    T_LTT01[i]  = r_vec[0];
    E_LTT01[i]  = r_vec[1];
    LT_LTT01[i] = i_vec[0];
    NL_LTT01[i] = i_vec[2];

    A_LTT01[i]  = e_vec;
    e_vec.clear();
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF04Parser::store_ltt02(MultiParser& mp_obj, int& line_no)
{
  vector<Real>    r_vec;
  vector<Integer> i_vec;
  r_vec.resize(6);
  i_vec.resize(6);

  mp_obj.read_tab2(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                   NBT_E_LTT02, INT_E_LTT02);

  NE_LTT02 = i_vec[3];
  int i_max = static_cast<int>(NE_LTT02);
  resize_matrix_ltt02(i_max);

  for(int i=0; i<i_max; i++)
  {
    vector<Integer> nbt_vec, int_vec;
    vector<Real>    m_vec,   f_vec;

    mp_obj.read_tab1(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                     nbt_vec, int_vec, m_vec, f_vec);
    T_LTT02[i]  = r_vec[0];
    E_LTT02[i]  = r_vec[1];
    LT_LTT02[i] = i_vec[0];
    NR_LTT02[i] = i_vec[2];
    NP_LTT02[i] = i_vec[3];

    NBT_F_LTT02[i]   = nbt_vec;
    INT_F_LTT02[i]   = int_vec;
    M_INT_F_LTT02[i] = m_vec;
    F_TAB_LTT02[i]   = f_vec;
    nbt_vec.clear();
    int_vec.clear();
    m_vec.clear();
    f_vec.clear();
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF04Parser::resize_matrix_ltt01(int i_max)
{
  T_LTT01.resize(i_max);
  E_LTT01.resize(i_max);
  LT_LTT01.resize(i_max);
  NL_LTT01.resize(i_max);

  A_LTT01.resize(i_max);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF04Parser::resize_matrix_ltt02(int i_max)
{
  T_LTT02.resize( i_max);
  E_LTT02.resize( i_max);
  LT_LTT02.resize(i_max);
  NR_LTT02.resize(i_max);
  NP_LTT02.resize(i_max);

  NBT_F_LTT02.resize(  i_max);
  INT_F_LTT02.resize(  i_max);
  M_INT_F_LTT02.resize(i_max);
  F_TAB_LTT02.resize(  i_max);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF04Parser::clear()
{
  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);

  mat_no = unassigned_mat_no;
  mt_no  = unassigned_mt_no;
  ZA     = 0;
  AWR    = 0.0;
  LVT    = 0;
  LTT    = 0;
  LI     = 0;
  LCT    = 0;
  NK     = 0;
  NM     = 0;
  U.clear();

  //LTT = 1
  NE_LTT01 = 0;
  NBT_E_LTT01.clear();
  INT_E_LTT01.clear();
  T_LTT01.clear();
  E_LTT01.clear();
  LT_LTT01.clear();
  NL_LTT01.clear();
  clr_vec.clear_vec_array2_real(A_LTT01);

  //LTT = 2
  NE_LTT02 = 0;
  NBT_E_LTT02.clear();
  INT_E_LTT02.clear();
  T_LTT02.clear();
  E_LTT02.clear();
  LT_LTT02.clear();
  NP_LTT02.clear();
  NR_LTT02.clear();
  clr_vec.clear_vec_array2_int( NBT_F_LTT02);
  clr_vec.clear_vec_array2_int( INT_F_LTT02);
  clr_vec.clear_vec_array2_real(M_INT_F_LTT02);
  clr_vec.clear_vec_array2_real(F_TAB_LTT02);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF04Parser::set_text(vector<string> text_data)
{
  clear();

  text = text_data;
  store_data();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string>  MF04Parser::get_text()
{
  return text;
}

Integer         MF04Parser::get_mat_no()
{
  return mat_no;
}

Integer         MF04Parser::get_mt_no()
{
  return mt_no;
}

//Getter at line No.01-02
Real            MF04Parser::get_ZA()
{
  return ZA;
}

Real            MF04Parser::get_AWR()
{
  return AWR;
}

Integer         MF04Parser::get_LVT()
{
  return LVT;
}

Integer         MF04Parser::get_LTT()
{
  return LTT;
}

Integer         MF04Parser::get_LI()
{
  return LI;
}

Integer         MF04Parser::get_LCT()
{
  return LCT;
}

Integer         MF04Parser::get_NK()
{
  return NK;
}

Integer         MF04Parser::get_NM()
{
  return NM;
}

vector<Real>    MF04Parser::get_U()
{
  return U;
}


//LTT = 1
Integer                       MF04Parser::get_NE_LTT01()
{
  return NE_LTT01;
}

vector<Integer>               MF04Parser::get_NBT_E_LTT01()
{
  return NBT_E_LTT01;
}

vector<Integer>               MF04Parser::get_INT_E_LTT01()
{
  return INT_E_LTT01;
}

vector<vector<Real> >         MF04Parser::get_A_LTT01()
{
  return A_LTT01;
}

vector<Real>                  MF04Parser::get_T_LTT01()
{
  return T_LTT01;
}

vector<Real>                  MF04Parser::get_E_LTT01()
{
  return E_LTT01;
}

vector<Integer>               MF04Parser::get_LT_LTT01()
{
  return LT_LTT01;
}

vector<Integer>               MF04Parser::get_NL_LTT01()
{
  return NL_LTT01;
}


//LTT = 2
Integer                       MF04Parser::get_NE_LTT02()
{
  return NE_LTT02;
}

vector<Integer>               MF04Parser::get_NBT_E_LTT02()
{
  return NBT_E_LTT02;
}

vector<Integer>               MF04Parser::get_INT_E_LTT02()
{
  return INT_E_LTT02;
}

vector<vector<Integer> > MF04Parser::get_NBT_F_LTT02()
{
  return NBT_F_LTT02;
}

vector<vector<Integer> > MF04Parser::get_INT_F_LTT02()
{
  return INT_F_LTT02;
}

vector<vector<Real> >    MF04Parser::get_M_INT_F_LTT02()
{
  return M_INT_F_LTT02;
}

vector<vector<Real> >    MF04Parser::get_F_TAB_LTT02()
{
  return F_TAB_LTT02;
}

vector<Real>                  MF04Parser::get_T_LTT02()
{
  return T_LTT02;
}

vector<Real>                  MF04Parser::get_E_LTT02()
{
  return E_LTT02;
}

vector<Integer>               MF04Parser::get_LT_LTT02()
{
  return LT_LTT02;
}

vector<Integer>               MF04Parser::get_NR_LTT02()
{
  return NR_LTT02;
}

vector<Integer>               MF04Parser::get_NP_LTT02()
{
  return NP_LTT02;
}


//LTT = 3. Legendre coefficients
Integer                       MF04Parser::get_NE_LTT03_L()
{
  return NE_LTT01;
}

vector<Integer>               MF04Parser::get_NBT_E_LTT03_L()
{
  return NBT_E_LTT01;
}

vector<Integer>               MF04Parser::get_INT_E_LTT03_L()
{
  return INT_E_LTT01;
}

vector<vector<Real> >         MF04Parser::get_A_LTT03_L()
{
  return A_LTT01;
}

vector<Real>                  MF04Parser::get_T_LTT03_L()
{
  return T_LTT01;
}

vector<Real>                  MF04Parser::get_E_LTT03_L()
{
  return E_LTT01;
}

vector<Integer>               MF04Parser::get_LT_LTT03_L()
{
  return LT_LTT01;
}

vector<Integer>               MF04Parser::get_NL_LTT03_L()
{
  return NL_LTT01;
}


//LTT = 3, Tabulated data
Integer                       MF04Parser::get_NE_LTT03_T()
{
  return NE_LTT02;
}

vector<Integer>               MF04Parser::get_NBT_E_LTT03_T()
{
  return NBT_E_LTT02;
}

vector<Integer>               MF04Parser::get_INT_E_LTT03_T()
{
  return INT_E_LTT02;
}

vector<vector<Integer> >      MF04Parser::get_NBT_F_LTT03_T()
{
  return NBT_F_LTT02;
}

vector<vector<Integer> >      MF04Parser::get_INT_F_LTT03_T()
{
  return INT_F_LTT02;
}

vector<vector<Real> >         MF04Parser::get_M_INT_F_LTT03_T()
{
  return M_INT_F_LTT02;
}

vector<vector<Real> >         MF04Parser::get_F_TAB_LTT03_T()
{
  return F_TAB_LTT02;
}

vector<Real>                  MF04Parser::get_T_LTT03_T()
{
  return T_LTT02;
}

vector<Real>                  MF04Parser::get_E_LTT03_T()
{
  return E_LTT02;
}

vector<Integer>               MF04Parser::get_LT_LTT03_T()
{
  return LT_LTT02;
}

vector<Integer>               MF04Parser::get_NR_LTT03_T()
{
  return NR_LTT02;
}

vector<Integer>               MF04Parser::get_NP_LTT03_T()
{
  return NP_LTT02;
}


////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void MF04Parser::set_mat_no(Integer& int_data)
{
  mat_no = int_data;
}

void MF04Parser::set_mt_no(Integer& int_data)
{
  mt_no = int_data;
}

void MF04Parser::set_ZA(Real& real_data)
{
  ZA = real_data;
}

void MF04Parser::set_AWR(Real& real_data)
{
  AWR = real_data;
}

void MF04Parser::set_LVT(Integer& int_data)
{
  LVT = int_data;
}

void MF04Parser::set_LTT(Integer& int_data)
{
  LTT = int_data;
}

void MF04Parser::set_LI(Integer& int_data)
{
  LI = int_data;
}

void MF04Parser::set_LCT(Integer& int_data)
{
  LCT = int_data;
}

void MF04Parser::set_NK(Integer& int_data)
{
  NK = int_data;
}

void MF04Parser::set_NM(Integer& int_data)
{
  NM = int_data;
}

void MF04Parser::set_U(vector<Real>& real_vec)
{
  U = real_vec;
}

void MF04Parser::set_NE_LTT01(Integer& int_data)
{
  NE_LTT01 = int_data;
}

void MF04Parser::set_NBT_E_LTT01(vector<Integer>& int_vec)
{
  NBT_E_LTT01 = int_vec;
}

void MF04Parser::set_INT_E_LTT01(vector<Integer>& int_vec)
{
  INT_E_LTT01 = int_vec;
}

void MF04Parser::set_A_LTT01(vector<vector<Real> >& real_vec)
{
  A_LTT01 = real_vec;
}

void MF04Parser::set_T_LTT01(vector<Real>& real_vec)
{
  T_LTT01 = real_vec;
}

void MF04Parser::set_E_LTT01(vector<Real>& real_vec)
{
  E_LTT01 = real_vec;
}

void MF04Parser::set_LT_LTT01(vector<Integer>& int_vec)
{
  LT_LTT01 = int_vec;
}

void MF04Parser::set_NL_LTT01(vector<Integer>& int_vec)
{
  NL_LTT01 = int_vec;
}

void MF04Parser::set_NE_LTT02(Integer& int_data)
{
  NE_LTT02 = int_data;
}

void MF04Parser::set_NBT_E_LTT02(vector<Integer>& int_vec)
{
  NBT_E_LTT02 = int_vec;
}

void MF04Parser::set_INT_E_LTT02(vector<Integer>& int_vec)
{
  INT_E_LTT02 = int_vec;
}

void MF04Parser::set_NBT_F_LTT02(vector<vector<Integer> >& int_vec)
{
  NBT_F_LTT02 = int_vec;
}

void MF04Parser::set_INT_F_LTT02(vector<vector<Integer> >& int_vec)
{
  INT_F_LTT02 = int_vec;
}

void MF04Parser::set_M_INT_F_LTT02(vector<vector<Real> >& real_vec)
{
  M_INT_F_LTT02 = real_vec;
}

void MF04Parser::set_F_TAB_LTT02(vector<vector<Real> >& real_vec)
{
  F_TAB_LTT02 = real_vec;
}

void MF04Parser::set_T_LTT02(vector<Real>& real_vec)
{
  T_LTT02 = real_vec;
}

void MF04Parser::set_E_LTT02(vector<Real>& real_vec)
{
  E_LTT02 = real_vec;
}

void MF04Parser::set_LT_LTT02(vector<Integer>& int_vec)
{
  LT_LTT02 = int_vec;
}

void MF04Parser::set_NR_LTT02(vector<Integer>& int_vec)
{
  NR_LTT02 = int_vec;
}

void MF04Parser::set_NP_LTT02(vector<Integer>& int_vec)
{
  NP_LTT02 = int_vec;
}

void MF04Parser::set_NE_LTT03_L(Integer& int_data)
{
  NE_LTT01 = int_data;
}

void MF04Parser::set_NBT_E_LTT03_L(vector<Integer>& int_vec)
{
  NBT_E_LTT01 = int_vec;
}

void MF04Parser::set_INT_E_LTT03_L(vector<Integer>& int_vec)
{
  INT_E_LTT01 = int_vec;
}

void MF04Parser::set_A_LTT03_L(vector<vector<Real> >& real_vec)
{
  A_LTT01 = real_vec;
}

void MF04Parser::set_T_LTT03_L(vector<Real>& real_vec)
{
  T_LTT01 = real_vec;
}

void MF04Parser::set_E_LTT03_L(vector<Real>& real_vec)
{
  E_LTT01 = real_vec;
}

void MF04Parser::set_LT_LTT03_L(vector<Integer>& int_vec)
{
  LT_LTT01 = int_vec;
}

void MF04Parser::set_NL_LTT03_L(vector<Integer>& int_vec)
{
  NL_LTT01 = int_vec;
}

void MF04Parser::set_NE_LTT03_T(Integer& int_data)
{
  NE_LTT02 = int_data;
}

void MF04Parser::set_NBT_E_LTT03_T(vector<Integer>& int_vec)
{
  NBT_E_LTT02 = int_vec;
}

void MF04Parser::set_INT_E_LTT03_T(vector<Integer>& int_vec)
{
  INT_E_LTT02 = int_vec;
}

void MF04Parser::set_NBT_F_LTT03_T(vector<vector<Integer> >& int_vec)
{
  NBT_F_LTT02 = int_vec;
}

void MF04Parser::set_INT_F_LTT03_T(vector<vector<Integer> >& int_vec)
{
  INT_F_LTT02 = int_vec;
}

void MF04Parser::set_M_INT_F_LTT03_T(vector<vector<Real> >& real_vec)
{
  M_INT_F_LTT02 = real_vec;
}

void MF04Parser::set_F_TAB_LTT03_T(vector<vector<Real> >& real_vec)
{
  F_TAB_LTT02 = real_vec;
}

void MF04Parser::set_T_LTT03_T(vector<Real>& real_vec)
{
  T_LTT02 = real_vec;
}

void MF04Parser::set_E_LTT03_T(vector<Real>& real_vec)
{
  E_LTT02 = real_vec;
}

void MF04Parser::set_LT_LTT03_T(vector<Integer>& int_vec)
{
  LT_LTT02 = int_vec;
}

void MF04Parser::set_NR_LTT03_T(vector<Integer>& int_vec)
{
  NR_LTT02 = int_vec;
}

void MF04Parser::set_NP_LTT03_T(vector<Integer>& int_vec)
{
  NP_LTT02 = int_vec;
}

