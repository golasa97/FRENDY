#include "EndfUtils/MFxxMTyyyParser/MF12Parser.hpp"

using namespace frendy;

//constructor
MF12Parser::MF12Parser(void)
{
  clear();

  err_obj.set_output_mode(err_obj.warning_off);
}

//destructor
MF12Parser::~MF12Parser(void)
{ 
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF12Parser::store_data() 
{
  MultiParser mp_obj;

  //Text file data check
  if( static_cast<Integer>(text.size()) < 1 )
  {
    string class_name = "MF12Parser";
    string func_name  = "store_data()";

    ostringstream oss;
    oss << static_cast<Integer>(text.size());
    string str_data = "Text line number : " + oss.str();

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("The text line number is not appropriate for MF=12.");
    err_com.push_back("The text line number should be larger than 1.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //Check MF number
  if( mp_obj.check_mf(text, mf_no) != 0)
  {
    string class_name = "MF12Parser";
    string func_name  = "store_data()";

    ostringstream oss01;
    oss01 << mf_no;
    string str_data01 = "Text data at first line : " + text[0];
    string str_data02 = "File number (MF)        : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("The MF number is different to MF=12.");

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
  //ZA, AWR, LIS, NK
  mp_obj.read_head(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3]);
  ZA  = r_vec[0];
  AWR = r_vec[1];
  LO  = i_vec[0];
  LG  = i_vec[1];
  NK  = i_vec[2];

  if( LO == 1 )
  {
    store_lo01(mp_obj, line_no);
  }
  else if( LO == 2 )
  {
    store_lo02(mp_obj, line_no);
  }
  else
  {
    string class_name = "MF12Parser";
    string func_name  = "store_data()";

    ostringstream oss00, oss01;
    oss00 << mt_no;
    oss01 << LO;
    string str_data00 = "Section number (MT) : " + oss00.str();
    string str_data01 = "LO                  : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data00);
    err_com.push_back(str_data01);
    err_com.push_back("This LO value at MF=12 is not supported in this program.");
    err_com.push_back("Supported LO value is 1 and 2.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
  r_vec.clear();
  i_vec.clear();

  mp_obj.line_no_check(text, line_no, mf_no, mt_no);

  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF12Parser::store_lo01(MultiParser& mp_obj, int& line_no)
{
  vector<Real>    r_vec;
  vector<Integer> i_vec;
  r_vec.resize(6);
  i_vec.resize(6);

  if( NK > 1 )
  {
    mp_obj.read_tab1(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                     NBT_Y_LO01, INT_Y_LO01, E_INT_Y_LO01, Y_TAB_LO01);
  }

  int nk = static_cast<int>(NK);
  EG_LO01.resize(nk);
  ES_LO01.resize(nk);
  LP_LO01.resize(nk);
  LF_LO01.resize(nk);
  NBT_Y_K_LO01.resize(  nk);
  INT_Y_K_LO01.resize(  nk);
  E_INT_Y_K_LO01.resize(nk);
  Y_K_TAB_LO01.resize(  nk);

  for(int i=0; i<nk; i++)
  {
    vector<Integer> nbt_vec, int_vec;
    vector<Real>    e_vec,   ap_vec;

    mp_obj.read_tab1(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                     nbt_vec, int_vec, e_vec, ap_vec);

    EG_LO01[i] = r_vec[0];
    ES_LO01[i] = r_vec[1];
    LP_LO01[i] = i_vec[0];
    LF_LO01[i] = i_vec[1];

    NBT_Y_K_LO01[i]   = nbt_vec;
    INT_Y_K_LO01[i]   = int_vec;
    E_INT_Y_K_LO01[i] = e_vec;
    Y_K_TAB_LO01[i]   = ap_vec;
    nbt_vec.clear();
    int_vec.clear();
    e_vec.clear();
    ap_vec.clear();
  }
  r_vec.clear();
  i_vec.clear();

  if( NK == 1 )
  {
    NBT_Y_LO01   = NBT_Y_K_LO01[0];
    INT_Y_LO01   = INT_Y_K_LO01[0];
    E_INT_Y_LO01 = E_INT_Y_K_LO01[0];
    Y_TAB_LO01   = Y_K_TAB_LO01[0];
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF12Parser::store_lo02(MultiParser& mp_obj, int& line_no)
{
  vector<Real>    r_vec;
  vector<Integer> i_vec;
  r_vec.resize(6);
  i_vec.resize(6);

  vector<Real> e_vec;

  mp_obj.read_list(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                   e_vec);
  ES_LO02 = r_vec[0];
  LP_LO02 = i_vec[0];
  NT_LO02 = i_vec[3];

  if( i_vec[2] != (LG+1)*i_vec[3] )
  {
    string class_name = "MF12Parser";
    string func_name  = "store_lo02(MultiParser& mp_obj, int& line_no)";

    ostringstream oss00, oss01, oss02, oss03;
    oss00 << mt_no;
    oss01 << i_vec[2];
    oss02 << LG;
    oss03 << i_vec[3];
    string str_data00 = "Section number (MT) : " + oss00.str();
    string str_data01 = "(LG+1)*NT           : " + oss01.str();
    string str_data02 = "LG                  : " + oss02.str();
    string str_data03 = "NT                  : " + oss03.str();

    vector<string> err_com;
    err_com.push_back(str_data00);
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("The number of (LG+1)*NT at LO=2 is not correct value. Please check MF=12.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  int j_max = static_cast<int>(e_vec.size());
  B_LO02.resize(j_max);
  for(int j=0; j<j_max; j++)
  {
    B_LO02[j] = e_vec[j];
  }
  e_vec.clear();
  r_vec.clear();
  i_vec.clear();
}


////////////////////////////////////////////////////////////////////////////////////////////////////

void MF12Parser::clear()
{
  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);

  mat_no = unassigned_mat_no;
  mt_no  = unassigned_mt_no;
  ZA     = 0.0;
  AWR    = 0.0;
  LO     = 0;
  LG     = 0;
  NK     = 0;

  NBT_Y_LO01.clear();
  INT_Y_LO01.clear();
  E_INT_Y_LO01.clear();
  Y_TAB_LO01.clear();

  EG_LO01.clear();
  ES_LO01.clear();
  LP_LO01.clear();
  LF_LO01.clear();

  clr_vec.clear_vec_array2_int( NBT_Y_K_LO01);
  clr_vec.clear_vec_array2_int( INT_Y_K_LO01);
  clr_vec.clear_vec_array2_real(E_INT_Y_K_LO01);
  clr_vec.clear_vec_array2_real(Y_K_TAB_LO01);

  ES_LO02 = 0.0;
  LP_LO02 = 0;
  NT_LO02 = 0;
  B_LO02.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF12Parser::set_text(vector<string> text_data)
{
  clear();

  text = text_data;
  store_data();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string>           MF12Parser::get_text()
{
  return text;
}

Integer                  MF12Parser::get_mat_no()
{
  return mat_no;
}

Integer                  MF12Parser::get_mt_no()
{
  return mt_no;
}

//Getter at line No.01-02
Real                     MF12Parser::get_ZA()
{
  return ZA;
}

Real                     MF12Parser::get_AWR()
{
  return AWR;
}

Integer                  MF12Parser::get_LO()
{
  return LO;
}

Integer                  MF12Parser::get_LG()
{
  return LG;
}

Integer                  MF12Parser::get_NK()
{
  return NK;
}

Integer                  MF12Parser::get_NS()
{
  return NK;
}


vector<Integer>          MF12Parser::get_NBT_Y_LO01()
{
  return NBT_Y_LO01;
}

vector<Integer>          MF12Parser::get_INT_Y_LO01()
{
  return INT_Y_LO01;
}

vector<Real>             MF12Parser::get_E_INT_Y_LO01()
{
  return E_INT_Y_LO01;
}

vector<Real>             MF12Parser::get_Y_TAB_LO01()
{
  return Y_TAB_LO01;
}


vector<Real>             MF12Parser::get_EG_LO01()
{
  return EG_LO01;
}

vector<Real>             MF12Parser::get_ES_LO01()
{
  return ES_LO01;
}

vector<Integer>          MF12Parser::get_LP_LO01()
{
  return LP_LO01;
}

vector<Integer>          MF12Parser::get_LF_LO01()
{
  return LF_LO01;
}

vector<vector<Integer> > MF12Parser::get_NBT_Y_K_LO01()
{
  return NBT_Y_K_LO01;
}

vector<vector<Integer> > MF12Parser::get_INT_Y_K_LO01()
{
  return INT_Y_K_LO01;
}

vector<vector<Real> >    MF12Parser::get_E_INT_Y_K_LO01()
{
  return E_INT_Y_K_LO01;
}

vector<vector<Real> >    MF12Parser::get_Y_K_TAB_LO01()
{
  return Y_K_TAB_LO01;
}


Real                     MF12Parser::get_ES_LO02()
{
  return ES_LO02;
}

Integer                  MF12Parser::get_LP_LO02()
{
  return LP_LO02;
}

Integer                  MF12Parser::get_NT_LO02()
{
  return NT_LO02;
}

vector<Real>             MF12Parser::get_B_LO02()
{
  return B_LO02;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void MF12Parser::set_mat_no(Integer& int_data)
{
  mat_no = int_data;
}

void MF12Parser::set_mt_no(Integer& int_data)
{
  mt_no = int_data;
}


void MF12Parser::set_ZA(Real& real_data)
{
  ZA = real_data;
}

void MF12Parser::set_AWR(Real& real_data)
{
  AWR = real_data;
}

void MF12Parser::set_LO(Integer& int_data)
{
  LO = int_data;
}

void MF12Parser::set_LG(Integer& int_data)
{
  LG = int_data;
}

void MF12Parser::set_NK(Integer& int_data)
{
  NK = int_data;
}

void MF12Parser::set_NS(Integer& int_data)
{
  NK = int_data;
}


void MF12Parser::set_NBT_Y_LO01(vector<Integer>& int_vec)
{
  NBT_Y_LO01 = int_vec;
}

void MF12Parser::set_INT_Y_LO01(vector<Integer>& int_vec)
{
  INT_Y_LO01 = int_vec;
}

void MF12Parser::set_E_INT_Y_LO01(vector<Real>& real_vec)
{
  E_INT_Y_LO01 = real_vec;
}

void MF12Parser::set_Y_TAB_LO01(vector<Real>& real_vec)
{
  Y_TAB_LO01 = real_vec;
}


void MF12Parser::set_EG_LO01(vector<Real>& real_vec)
{
  EG_LO01 = real_vec;
}

void MF12Parser::set_ES_LO01(vector<Real>& real_vec)
{
  ES_LO01 = real_vec;
}

void MF12Parser::set_LP_LO01(vector<Integer>& int_vec)
{
  LP_LO01 = int_vec;
}

void MF12Parser::set_LF_LO01(vector<Integer>& int_vec)
{
  LF_LO01 = int_vec;
}

void MF12Parser::set_NBT_Y_K_LO01(vector<vector<Integer> >& int_vec)
{
  NBT_Y_K_LO01 = int_vec;
}

void MF12Parser::set_INT_Y_K_LO01(vector<vector<Integer> >& int_vec)
{
  INT_Y_K_LO01 = int_vec;
}

void MF12Parser::set_E_INT_Y_K_LO01(vector<vector<Real> >& real_vec)
{
  E_INT_Y_K_LO01 = real_vec;
}

void MF12Parser::set_Y_K_TAB_LO01(vector<vector<Real> >& real_vec)
{
  Y_K_TAB_LO01 = real_vec;
}


void MF12Parser::set_ES_LO02(Real& real_data)
{
  ES_LO02 = real_data;
}

void MF12Parser::set_LP_LO02(Integer& int_data)
{
  LP_LO02 = int_data;
}

void MF12Parser::set_NT_LO02(Integer& int_data)
{
  NT_LO02 = int_data;
}

void MF12Parser::set_B_LO02(vector<Real>& real_vec)
{
  B_LO02 = real_vec;
}

