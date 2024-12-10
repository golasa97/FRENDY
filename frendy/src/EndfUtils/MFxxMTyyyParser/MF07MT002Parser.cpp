#include "EndfUtils/MFxxMTyyyParser/MF07MT002Parser.hpp"

using namespace frendy;

//constructor
MF07MT002Parser::MF07MT002Parser(void)
{
  clear();

  err_obj.set_output_mode(err_obj.warning_off);
}

//destructor
MF07MT002Parser::~MF07MT002Parser(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF07MT002Parser::store_data()
{
  MultiParser mp_obj;

  //Text file data check
  if( static_cast<Integer>(text.size()) < 2 )
  {
    string class_name = "MF07MT002Parser";
    string func_name  = "store_data()";

    ostringstream oss;
    oss << static_cast<Integer>(text.size());
    string str_data = "Text line number : " + oss.str();

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("The text line number is not appropriate for MF=07, MT=002.");
    err_com.push_back("The text line number should be larger than 1.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //Check MT and MF number
  if( mp_obj.check_mf_mt(text, mf_no, mt_no) != 0)
  {
    string class_name = "MF07MT002Parser";
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
    err_com.push_back("The MF and MT numbers are different to MF=07, MT=002.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  mp_obj.get_mat(text, mat_no);

  int     line_no = 0;
  Integer tmp_int;

  //Line No.01
  //ZA, AWR, LTHR
  mp_obj.read_head(text, line_no, ZA, AWR, LTHR, tmp_int, tmp_int, tmp_int);

  if( LTHR == 1 )
  {
    store_lthr01(mp_obj, line_no);
  }
  else if( LTHR == 2 )
  {
    store_lthr02(mp_obj, line_no);
  }
  else if( LTHR == 3 )
  {
    store_lthr01(mp_obj, line_no);
    store_lthr02(mp_obj, line_no);
  }
  else
  {
    string class_name = "MF07MT002Parser";
    string func_name  = "store_data()";

    ostringstream oss01;
    oss01 << LTHR;
    string str_data01 = "LTHR : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("This LTHR value at MF=07, MT=002 is not supported in this program.");
    err_com.push_back("Supported LTHR value is 1 and 2");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  mp_obj.line_no_check(text, line_no, mf_no, mt_no);

  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF07MT002Parser::store_lthr01(MultiParser& mp_obj, int& line_no)
{
  vector<Real>    r_vec;
  vector<Integer> i_vec;
  r_vec.resize(6);
  i_vec.resize(6);

  vector<Integer> nbt_vec, int_vec;
  vector<Real>    e_vec,   ap_vec;

  mp_obj.read_tab1(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                   nbt_vec, int_vec, e_vec, ap_vec);

  T0 = r_vec[0];
  LT = i_vec[0];

  int i_max = static_cast<int>(nbt_vec.size());
  for(int i=0; i<i_max; i++)
  {
    if( int_vec[i] != static_cast<Integer>(int_const) )
    {
      string class_name = "MF07MT002Parser";
      string func_name  = "store_lthr01(MultiParser& mp_obj, int& line_no)";

      ostringstream oss01, oss02, oss03;
      oss01 << i;
      oss02 << i_max;
      oss03 << int_vec[i];
      string str_data01 = "i = " + oss01.str() + " / " + oss02.str();
      string str_data02 = "Interpolation value : " + oss03.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back("Histogram iterpolation (Interpolation value = 1) is only available.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }

  NBT_S = nbt_vec;
  INT_S = int_vec;
  E_INT_S = e_vec;
  S_TAB   = ap_vec;
  nbt_vec.clear();
  int_vec.clear();
  e_vec.clear();
  ap_vec.clear();

  i_max = static_cast<int>(LT);
  T.resize(i_max);
  LI.resize(i_max);
  S.resize(i_max);

  for(int i=0; i<i_max; i++)
  {
    mp_obj.read_list(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                     e_vec);
    T[i]  = r_vec[0];
    LI[i] = i_vec[0];

    int j_max = static_cast<int>(e_vec.size());
    S[i].resize(j_max);
    for(int j=0; j<j_max; j++)
    {
      S[i][j] = e_vec[j];
    }
    e_vec.clear();
  }
  r_vec.clear();
  i_vec.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF07MT002Parser::store_lthr02(MultiParser& mp_obj, int& line_no)
{
  vector<Real>    r_vec;
  vector<Integer> i_vec;
  r_vec.resize(6);
  i_vec.resize(6);

  vector<Integer> nbt_vec, int_vec;
  vector<Real>    e_vec,   ap_vec;

  mp_obj.read_tab1(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                   nbt_vec, int_vec, e_vec, ap_vec);

  SB = r_vec[0];
  r_vec.clear();
  i_vec.clear();

  NBT_W   = nbt_vec;
  INT_W   = int_vec;
  T_INT_W = e_vec;
  W_TAB   = ap_vec;
  nbt_vec.clear();
  int_vec.clear();
  e_vec.clear();
  ap_vec.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF07MT002Parser::clear()
{
  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);

  mat_no = unassigned_mat_no;
  ZA     = 0.0;
  AWR    = 0.0;
  LTHR   = 0;

  T0   = 0.0;
  LT   = 0;
  NBT_S.clear();
  INT_S.clear();
  E_INT_S.clear();
  S_TAB.clear();
  T.clear();
  LI.clear();

  clr_vec.clear_vec_array2_real(S);

  SB = 0.0;
  NBT_W.clear();
  INT_W.clear();
  T_INT_W.clear();
  W_TAB.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF07MT002Parser::set_text(vector<string> text_data)
{
  clear();

  text = text_data;
  store_data();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> MF07MT002Parser::get_text()
{
  return text;
}

Integer MF07MT002Parser::get_mat_no()
{
  return mat_no;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Real                  MF07MT002Parser::get_ZA()
{
  return ZA;
}

Real                  MF07MT002Parser::get_AWR()
{
  return AWR;
}

Integer               MF07MT002Parser::get_LTHR()
{
  return LTHR;
}


//LTHR=1
Real                  MF07MT002Parser::get_T0_LTHR01()
{
  return T0;
}

Integer               MF07MT002Parser::get_LT_LTHR01()
{
  return LT;
}

vector<Integer>       MF07MT002Parser::get_NBT_S_LTHR01()
{
  return NBT_S;
}

vector<Integer>       MF07MT002Parser::get_INT_S_LTHR01()
{
  return INT_S;
}

vector<Real>          MF07MT002Parser::get_E_INT_S_LTHR01()
{
  return E_INT_S;
}

vector<Real>          MF07MT002Parser::get_S_TAB_LTHR01()
{
  return S_TAB;
}

vector<Real>          MF07MT002Parser::get_T_LTHR01()
{
  return T;
}

vector<Integer>       MF07MT002Parser::get_LI_LTHR01()
{
  return LI;
}

vector<vector<Real> > MF07MT002Parser::get_S_LTHR01()
{
  return S;
}


//LTHR=2
Real                  MF07MT002Parser::get_SB_LTHR02()
{
  return SB;
}

vector<Integer>       MF07MT002Parser::get_NBT_W_LTHR02()
{
  return NBT_W;
}

vector<Integer>       MF07MT002Parser::get_INT_W_LTHR02()
{
  return INT_W;
}

vector<Real>          MF07MT002Parser::get_T_INT_W_LTHR02()
{
  return T_INT_W;
}

vector<Real>          MF07MT002Parser::get_W_TAB_LTHR02()
{
  return W_TAB;
}


////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void MF07MT002Parser::set_mat_no(Integer& int_data)
{
  mat_no = int_data;
}

void MF07MT002Parser::set_ZA(Real& real_data)
{
  ZA = real_data;
}

void MF07MT002Parser::set_AWR(Real& real_data)
{
  AWR = real_data;
}

void MF07MT002Parser::set_LTHR(Integer& int_data)
{
  LTHR = int_data;
}

void MF07MT002Parser::set_T0_LTHR01(Real& real_data)
{
  T0 = real_data;
}

void MF07MT002Parser::set_LT_LTHR01(Integer& int_data)
{
  LT = int_data;
}

void MF07MT002Parser::set_NBT_S_LTHR01(vector<Integer>& int_vec)
{
  NBT_S = int_vec;
}

void MF07MT002Parser::set_INT_S_LTHR01(vector<Integer>& int_vec)
{
  INT_S = int_vec;
}

void MF07MT002Parser::set_E_INT_S_LTHR01(vector<Real>& real_vec)
{
  E_INT_S = real_vec;
}

void MF07MT002Parser::set_S_TAB_LTHR01(vector<Real>& real_vec)
{
  S_TAB = real_vec;
}

void MF07MT002Parser::set_T_LTHR01(vector<Real>& real_vec)
{
  T = real_vec;
}

void MF07MT002Parser::set_LI_LTHR01(vector<Integer>& int_vec)
{
  LI = int_vec;
}

void MF07MT002Parser::set_S_LTHR01(vector<vector<Real> >& real_vec)
{
  S = real_vec;
}

void MF07MT002Parser::set_SB_LTHR02(Real& real_data)
{
  SB = real_data;
}

void MF07MT002Parser::set_NBT_W_LTHR02(vector<Integer>& int_vec)
{
  NBT_W = int_vec;
}

void MF07MT002Parser::set_INT_W_LTHR02(vector<Integer>& int_vec)
{
  INT_W = int_vec;
}

void MF07MT002Parser::set_T_INT_W_LTHR02(vector<Real>& real_vec)
{
  T_INT_W = real_vec;
}

void MF07MT002Parser::set_W_TAB_LTHR02(vector<Real>& real_vec)
{
  W_TAB = real_vec;
}

