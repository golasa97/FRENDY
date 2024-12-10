#include "EndfUtils/MFxxMTyyyParser/MF13Parser.hpp"

using namespace frendy;

//constructor
MF13Parser::MF13Parser(void)
{
  clear();

  err_obj.set_output_mode(err_obj.warning_off);
}

//destructor
MF13Parser::~MF13Parser(void)
{ 
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF13Parser::store_data() 
{
  MultiParser mp_obj;

  //Text file data check
  if( static_cast<Integer>(text.size()) < 1 )
  {
    string class_name = "MF13Parser";
    string func_name  = "store_data()";

    ostringstream oss;
    oss << static_cast<Integer>(text.size());
    string str_data = "Text line number : " + oss.str();

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("The text line number is not appropriate for MF=13.");
    err_com.push_back("The text line number should be larger than 1.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //Check MF number
  if( mp_obj.check_mf(text, mf_no) != 0)
  {
    string class_name = "MF13Parser";
    string func_name  = "store_data()";

    ostringstream oss01;
    oss01 << mf_no;
    string str_data01 = "Text data at first line : " + text[0];
    string str_data02 = "File number (MF)        : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("The MF number is different to MF=13.");

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
  //ZA, AWR, NK
  mp_obj.read_head(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3]);
  ZA  = r_vec[0];
  AWR = r_vec[1];
  NK  = i_vec[2];

  if( NK > 1 )
  {
    mp_obj.read_tab1(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                     NBT_S_TOT, INT_S_TOT, E_INT_S_TOT, S_TOT_TAB);
  }

  int nk = static_cast<int>(NK);
  resize_matrix(nk);

  for(int i=0; i<nk; i++)
  {
    vector<Integer> nbt_vec, int_vec;
    vector<Real>    e_vec,   ap_vec;
    mp_obj.read_tab1(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                     nbt_vec, int_vec, e_vec, ap_vec);
    EG[i] = r_vec[0];
    ES[i] = r_vec[1];
    LP[i] = i_vec[0];
    LF[i] = i_vec[1];

    NBT_S_K[i]   = nbt_vec;
    INT_S_K[i]   = int_vec;
    E_INT_S_K[i] = e_vec;
    S_K_TAB[i]   = ap_vec;
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

  if( NK == 1 )
  {
    NBT_S_TOT   = NBT_S_K[0];
    INT_S_TOT   = INT_S_K[0];
    E_INT_S_TOT = E_INT_S_K[0];
    S_TOT_TAB   = S_K_TAB[0];
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF13Parser::resize_matrix(int i_max)
{
  EG.resize(i_max);
  ES.resize(i_max);
  LP.resize(i_max);
  LF.resize(i_max);
  NBT_S_K.resize(  i_max);
  INT_S_K.resize(  i_max);
  E_INT_S_K.resize(i_max);
  S_K_TAB.resize(  i_max);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF13Parser::clear()
{
  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);

  mat_no = unassigned_mat_no;
  mt_no  = unassigned_mt_no;
  ZA     = 0.0;
  AWR    = 0.0;
  NK     = 0;

  NBT_S_TOT.clear();
  INT_S_TOT.clear();
  E_INT_S_TOT.clear();
  S_TOT_TAB.clear();

  EG.clear();
  ES.clear();
  LP.clear();
  LF.clear();

  clr_vec.clear_vec_array2_int( NBT_S_K);
  clr_vec.clear_vec_array2_int( INT_S_K);
  clr_vec.clear_vec_array2_real(E_INT_S_K);
  clr_vec.clear_vec_array2_real(S_K_TAB);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF13Parser::set_text(vector<string> text_data)
{
  clear();

  text = text_data;
  store_data();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string>           MF13Parser::get_text()
{
  return text;
}

Integer                  MF13Parser::get_mat_no()
{
  return mat_no;
}

Integer                  MF13Parser::get_mt_no()
{
  return mt_no;
}

//Getter at line No.01-02
Real                     MF13Parser::get_ZA()
{
  return ZA;
}

Real                     MF13Parser::get_AWR()
{
  return AWR;
}

Integer                  MF13Parser::get_NK()
{
  return NK;
}


vector<Integer>          MF13Parser::get_NBT_S_TOT()
{
  return NBT_S_TOT;
}

vector<Integer>          MF13Parser::get_INT_S_TOT()
{
  return INT_S_TOT;
}

vector<Real>             MF13Parser::get_E_INT_S_TOT()
{
  return E_INT_S_TOT;
}

vector<Real>             MF13Parser::get_S_TOT_TAB()
{
  return S_TOT_TAB;
}


vector<Real>             MF13Parser::get_EG()
{
  return EG;
}

vector<Real>             MF13Parser::get_ES()
{
  return ES;
}

vector<Integer>          MF13Parser::get_LP()
{
  return LP;
}

vector<Integer>          MF13Parser::get_LF()
{
  return LF;
}

vector<vector<Integer> > MF13Parser::get_NBT_S_K()
{
  return NBT_S_K;
}

vector<vector<Integer> > MF13Parser::get_INT_S_K()
{
  return INT_S_K;
}

vector<vector<Real> >    MF13Parser::get_E_INT_S_K()
{
  return E_INT_S_K;
}

vector<vector<Real> >    MF13Parser::get_S_K_TAB()
{
  return S_K_TAB;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void MF13Parser::set_mat_no(Integer& int_data)
{
  mat_no = int_data;
}

void MF13Parser::set_mt_no(Integer& int_data)
{
  mt_no = int_data;
}


void MF13Parser::set_ZA(Real& real_data)
{
  ZA = real_data;
}

void MF13Parser::set_AWR(Real& real_data)
{
  AWR = real_data;
}

void MF13Parser::set_NK(Integer& int_data)
{
  NK = int_data;
}


void MF13Parser::set_NBT_S_TOT(vector<Integer>& int_vec)
{
  NBT_S_TOT = int_vec;
}

void MF13Parser::set_INT_S_TOT(vector<Integer>& int_vec)
{
  INT_S_TOT = int_vec;
}

void MF13Parser::set_E_INT_S_TOT(vector<Real>& real_vec)
{
  E_INT_S_TOT = real_vec;
}

void MF13Parser::set_S_TOT_TAB(vector<Real>& real_vec)
{
  S_TOT_TAB = real_vec;
}


void MF13Parser::set_EG(vector<Real>& real_vec)
{
  EG = real_vec;
}

void MF13Parser::set_ES(vector<Real>& real_vec)
{
  ES = real_vec;
}

void MF13Parser::set_LP(vector<Integer>& int_vec)
{
  LP = int_vec;
}

void MF13Parser::set_LF(vector<Integer>& int_vec)
{
  LF = int_vec;
}

void MF13Parser::set_NBT_S_K(vector<vector<Integer> >& int_vec)
{
  NBT_S_K = int_vec;
}

void MF13Parser::set_INT_S_K(vector<vector<Integer> >& int_vec)
{
  INT_S_K = int_vec;
}

void MF13Parser::set_E_INT_S_K(vector<vector<Real> >& real_vec)
{
  E_INT_S_K = real_vec;
}

void MF13Parser::set_S_K_TAB(vector<vector<Real> >& real_vec)
{
  S_K_TAB = real_vec;
}


