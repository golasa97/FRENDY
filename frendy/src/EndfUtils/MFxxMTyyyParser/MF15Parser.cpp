#include "EndfUtils/MFxxMTyyyParser/MF15Parser.hpp"

using namespace frendy;

//constructor
MF15Parser::MF15Parser(void)
{
  clear();

  err_obj.set_output_mode(err_obj.warning_off);
}

//destructor
MF15Parser::~MF15Parser(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF15Parser::store_data()
{
  MultiParser mp_obj;

  //Text file data check
  if( static_cast<Integer>(text.size()) < 1 )
  {
    string class_name = "MF15Parser";
    string func_name  = "store_data()";

    ostringstream oss;
    oss << static_cast<Integer>(text.size());
    string str_data = "Text line number : " + oss.str();

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("The text line number is not appropriate for MF=15.");
    err_com.push_back("The text line number should be larger than 1.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //Check MF number
  if( mp_obj.check_mf(text, mf_no) != 0)
  {
    string class_name = "MF15Parser";
    string func_name  = "store_data()";

    ostringstream oss01;
    oss01 << mf_no;
    string str_data01 = "Text data at first line : " + text[0];
    string str_data02 = "File number (MF)        : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("The MF number is different to MF=15.");

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
  //ZA, AWR, NC
  mp_obj.read_head(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3]);
  ZA  = r_vec[0];
  AWR = r_vec[1];
  NC  = i_vec[2];

  resize_matrix();
  for(int i=0; i<static_cast<int>(NC); i++)
  {
    vector<Integer> nbt_vec, int_vec;
    vector<Real>    e_vec, a_vec;
    mp_obj.read_tab1(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                     nbt_vec, int_vec, e_vec, a_vec);

    LF[i] = i_vec[1];

    NBT_P[i]   = nbt_vec;
    INT_P[i]   = int_vec;
    E_INT_P[i] = e_vec;
    P_TAB[i]   = a_vec;
    nbt_vec.clear();
    int_vec.clear();
    e_vec.clear();
    a_vec.clear();

    if( LF[i] == 1 )
    {
      store_lf01(mp_obj, line_no, i);
    }
    else if( LF[i] == 5 )
    {
      store_lf05(mp_obj, line_no, i);
    }
    else if( LF[i] == 7 )
    {
      store_lf07(mp_obj, line_no, i);
    }
    else if( LF[i] == 9 )
    {
      store_lf07(mp_obj, line_no, i);
    }
    else if( LF[i] == 11 )
    {
      store_lf05(mp_obj, line_no, i);
    }
    else
    {
      string class_name = "MF15Parser";
      string func_name  = "store_data()";

      ostringstream oss00, oss01, oss02, oss03;
      oss00 << mt_no;
      oss01 << i;
      oss02 << static_cast<int>(NC);
      oss03 << LF[i];
      string str_data00 = "Section number (MT) : " + oss00.str();
      string str_data01 = "NC                  : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "LF                  : " + oss03.str();

      vector<string> err_com;
      err_com.push_back(str_data00);
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back("This LF value at MF=15 is not supported in this program.");
      err_com.push_back("Supported LF value is 1, 5, 7, 9 and 11.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }
  r_vec.clear();
  i_vec.clear();

  mp_obj.line_no_check(text, line_no, mf_no, mt_no);

  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Copy from MF05Parser::store_lf01
void MF15Parser::store_lf01(MultiParser& mp_obj, int& line_no, int& i)
{
  vector<Real>    r_vec;
  vector<Integer> i_vec;
  r_vec.resize(6);
  i_vec.resize(6);

  vector<Integer> nbt_vec, int_vec;
  mp_obj.read_tab2(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                   nbt_vec, int_vec);

  NE_LF01[i] = i_vec[3];

  NBT_E_LF01[i] = nbt_vec;
  INT_E_LF01[i] = int_vec;
  nbt_vec.clear();
  int_vec.clear();

  int j_max = static_cast<int>(NE_LF01[i]);
  E_LF01[i].resize(      j_max);
  NBT_G_LF01[i].resize(  j_max);
  INT_G_LF01[i].resize(  j_max);
  E_INT_G_LF01[i].resize(j_max);
  G_TAB_LF01[i].resize(  j_max);

  for(int j=0; j<j_max; j++)
  {
    vector<Real> e_vec, g_vec;

    mp_obj.read_tab1(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                     nbt_vec, int_vec, e_vec, g_vec);

    E_LF01[i][j] = r_vec[1];

    NBT_G_LF01[i][j]   = nbt_vec;
    INT_G_LF01[i][j]   = int_vec;
    E_INT_G_LF01[i][j] = e_vec;
    G_TAB_LF01[i][j]   = g_vec;
    nbt_vec.clear();
    int_vec.clear();
    e_vec.clear();
    g_vec.clear();
  }
  r_vec.clear();
  i_vec.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Copy from MF05Parser::store_lf05
void MF15Parser::store_lf05(MultiParser& mp_obj, int& line_no, int& i)
{
  for(int j=0; j<2; j++)
  {
    vector<Real>    r_vec;
    vector<Integer> i_vec;
    r_vec.resize(6);
    i_vec.resize(6);

    vector<Integer> nbt_vec, int_vec;
    vector<Real>    e_vec, a_vec;
    mp_obj.read_tab1(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                     nbt_vec, int_vec, e_vec, a_vec);

    if( j==0 )
    {
      NBT_S_LF05[i]   = nbt_vec;
      INT_S_LF05[i]   = int_vec;
      E_INT_S_LF05[i] = e_vec;
      S_TAB_LF05[i]   = a_vec;
    }
    else
    {
      NBT_G_LF05[i]   = nbt_vec;
      INT_G_LF05[i]   = int_vec;
      E_INT_G_LF05[i] = e_vec;
      G_TAB_LF05[i]   = a_vec;
    }
    r_vec.clear();
    i_vec.clear();
    nbt_vec.clear();
    int_vec.clear();
    e_vec.clear();
    a_vec.clear();
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Copy from MF05Parser::store_lf07
void MF15Parser::store_lf07(MultiParser& mp_obj, int& line_no, int& i)
{
  vector<Real>    r_vec;
  vector<Integer> i_vec;
  r_vec.resize(6);
  i_vec.resize(6);

  vector<Integer> nbt_vec, int_vec;
  vector<Real>    e_vec, a_vec;
  mp_obj.read_tab1(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                   nbt_vec, int_vec, e_vec, a_vec);

  NBT_S_LF05[i]   = nbt_vec;
  INT_S_LF05[i]   = int_vec;
  E_INT_S_LF05[i] = e_vec;
  S_TAB_LF05[i]   = a_vec;
  r_vec.clear();
  i_vec.clear();
  nbt_vec.clear();
  int_vec.clear();
  e_vec.clear();
  a_vec.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF15Parser::clear()
{
  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);

  mat_no = unassigned_mat_no;
  mt_no  = unassigned_mt_no;
  ZA     = 0.0;
  AWR    = 0.0;
  NC     = 0;

  LF.clear();
  NBT_P.clear();
  INT_P.clear();
  E_INT_P.clear();
  P_TAB.clear();

  //LF = 1
  NE_LF01.clear();
  clr_vec.clear_vec_array2_int( NBT_E_LF01);
  clr_vec.clear_vec_array2_int( INT_E_LF01);
  clr_vec.clear_vec_array2_real(E_LF01);
  clr_vec.clear_vec_array3_int( NBT_G_LF01);
  clr_vec.clear_vec_array3_int( INT_G_LF01);
  clr_vec.clear_vec_array3_real(E_INT_G_LF01);
  clr_vec.clear_vec_array3_real(G_TAB_LF01);

  //LF = 5
  clr_vec.clear_vec_array2_int( NBT_S_LF05);
  clr_vec.clear_vec_array2_int( INT_S_LF05);
  clr_vec.clear_vec_array2_real(E_INT_S_LF05);
  clr_vec.clear_vec_array2_real(S_TAB_LF05);
  clr_vec.clear_vec_array2_int( NBT_G_LF05);
  clr_vec.clear_vec_array2_int( INT_G_LF05);
  clr_vec.clear_vec_array2_real(E_INT_G_LF05);
  clr_vec.clear_vec_array2_real(G_TAB_LF05);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF15Parser::resize_matrix()
{
  int nc = static_cast<int>(NC);
  LF.resize(nc);

  NBT_P.resize(nc);
  INT_P.resize(nc);
  E_INT_P.resize(nc);
  P_TAB.resize(nc);

  //LF = 1
  NE_LF01.resize(nc);

  NBT_E_LF01.resize(nc);
  INT_E_LF01.resize(nc);
  E_LF01.resize(nc);
  NBT_G_LF01.resize(nc);
  INT_G_LF01.resize(nc);
  E_INT_G_LF01.resize(nc);
  G_TAB_LF01.resize(nc);

  //LF = 5
  NBT_S_LF05.resize(nc);
  INT_S_LF05.resize(nc);
  E_INT_S_LF05.resize(nc);
  S_TAB_LF05.resize(nc);
  NBT_G_LF05.resize(nc);
  INT_G_LF05.resize(nc);
  E_INT_G_LF05.resize(nc);
  G_TAB_LF05.resize(nc);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF15Parser::set_text(vector<string> text_data)
{
  clear();

  text = text_data;
  store_data();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string>                    MF15Parser::get_text()
{
  return text;
}

Integer                           MF15Parser::get_mat_no()
{
  return mat_no;
}

Integer                           MF15Parser::get_mt_no()
{
  return mt_no;
}

//Getter at line No.01
Real                              MF15Parser::get_ZA()
{
  return ZA;
}

Real                              MF15Parser::get_AWR()
{
  return AWR;
}

Integer                           MF15Parser::get_NC()
{
  return NC;
}

vector<Integer>                   MF15Parser::get_LF()
{
  return LF;
}

vector<vector<Integer> >          MF15Parser::get_NBT_P()
{
  return NBT_P;
}

vector<vector<Integer> >          MF15Parser::get_INT_P()
{
  return INT_P;
}

vector<vector<Real> >             MF15Parser::get_E_INT_P()
{
  return E_INT_P;
}

vector<vector<Real> >             MF15Parser::get_P_TAB()
{
  return P_TAB;
}


//LF = 1
vector<Integer>                   MF15Parser::get_NE_LF01()
{
  return NE_LF01;
}

vector<vector<Integer> >          MF15Parser::get_NBT_E_LF01()
{
  return NBT_E_LF01;
}

vector<vector<Integer> >          MF15Parser::get_INT_E_LF01()
{
  return INT_E_LF01;
}

vector<vector<Real> >             MF15Parser::get_E_LF01()
{
  return E_LF01;
}

vector<vector<vector<Integer> > > MF15Parser::get_NBT_G_LF01()
{
  return NBT_G_LF01;
}

vector<vector<vector<Integer> > > MF15Parser::get_INT_G_LF01()
{
  return INT_G_LF01;
}

vector<vector<vector<Real> > >    MF15Parser::get_E_INT_G_LF01()
{
  return E_INT_G_LF01;
}

vector<vector<vector<Real> > >    MF15Parser::get_G_TAB_LF01()
{
  return G_TAB_LF01;
}


//LF = 5
vector<vector<Integer> >          MF15Parser::get_NBT_S_LF05()
{
  return NBT_S_LF05;
}

vector<vector<Integer> >          MF15Parser::get_INT_S_LF05()
{
  return INT_S_LF05;
}

vector<vector<Real> >             MF15Parser::get_E_INT_S_LF05()
{
  return E_INT_S_LF05;
}

vector<vector<Real> >             MF15Parser::get_S_TAB_LF05()
{
  return S_TAB_LF05;
}

vector<vector<Integer> >          MF15Parser::get_NBT_G_LF05()
{
  return NBT_G_LF05;
}

vector<vector<Integer> >          MF15Parser::get_INT_G_LF05()
{
  return INT_G_LF05;
}

vector<vector<Real> >             MF15Parser::get_E_INT_G_LF05()
{
  return E_INT_G_LF05;
}

vector<vector<Real> >             MF15Parser::get_G_TAB_LF05()
{
  return G_TAB_LF05;
}


//LF = 7
vector<vector<Integer> >          MF15Parser::get_NBT_S_LF07()
{
  return NBT_S_LF05;
}

vector<vector<Integer> >          MF15Parser::get_INT_S_LF07()
{
  return INT_S_LF05;
}

vector<vector<Real> >             MF15Parser::get_E_INT_S_LF07()
{
  return E_INT_S_LF05;
}

vector<vector<Real> >             MF15Parser::get_S_TAB_LF07()
{
  return S_TAB_LF05;
}


//LF = 9
vector<vector<Integer> >          MF15Parser::get_NBT_S_LF09()
{
  return NBT_S_LF05;
}

vector<vector<Integer> >          MF15Parser::get_INT_S_LF09()
{
  return INT_S_LF05;
}

vector<vector<Real> >             MF15Parser::get_E_INT_S_LF09()
{
  return E_INT_S_LF05;
}

vector<vector<Real> >             MF15Parser::get_S_TAB_LF09()
{
  return S_TAB_LF05;
}


//LF = 11
vector<vector<Integer> >          MF15Parser::get_NBT_A_LF11()
{
  return NBT_S_LF05;
}

vector<vector<Integer> >          MF15Parser::get_INT_A_LF11()
{
  return INT_S_LF05;
}

vector<vector<Real> >             MF15Parser::get_E_INT_A_LF11()
{
  return E_INT_S_LF05;
}

vector<vector<Real> >             MF15Parser::get_A_TAB_LF11()
{
  return S_TAB_LF05;
}

vector<vector<Integer> >          MF15Parser::get_NBT_B_LF11()
{
  return NBT_G_LF05;
}

vector<vector<Integer> >          MF15Parser::get_INT_B_LF11()
{
  return INT_G_LF05;
}

vector<vector<Real> >             MF15Parser::get_E_INT_B_LF11()
{
  return E_INT_G_LF05;
}

vector<vector<Real> >             MF15Parser::get_B_TAB_LF11()
{
  return G_TAB_LF05;
}


////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void MF15Parser::set_mat_no(Integer& int_data)
{
  mat_no = int_data;
}

void MF15Parser::set_mt_no(Integer& int_data)
{
  mt_no = int_data;
}

void MF15Parser::set_ZA(Real& real_data)
{
  ZA = real_data;
}

void MF15Parser::set_AWR(Real& real_data)
{
  AWR = real_data;
}

void MF15Parser::set_NC(Integer& int_data)
{
  NC = int_data;
}

void MF15Parser::set_LF(vector<Integer>& int_vec)
{
  LF = int_vec;
}

void MF15Parser::set_NBT_P(vector<vector<Integer> >& int_vec)
{
  NBT_P = int_vec;
}

void MF15Parser::set_INT_P(vector<vector<Integer> >& int_vec)
{
  INT_P = int_vec;
}

void MF15Parser::set_E_INT_P(vector<vector<Real> >& real_vec)
{
  E_INT_P = real_vec;
}

void MF15Parser::set_P_TAB(vector<vector<Real> >& real_vec)
{
  P_TAB = real_vec;
}

void MF15Parser::set_NE_LF01(vector<Integer>& int_vec)
{
  NE_LF01 = int_vec;
}

void MF15Parser::set_NBT_E_LF01(vector<vector<Integer> >& int_vec)
{
  NBT_E_LF01 = int_vec;
}

void MF15Parser::set_INT_E_LF01(vector<vector<Integer> >& int_vec)
{
  INT_E_LF01 = int_vec;
}

void MF15Parser::set_E_LF01(vector<vector<Real> >& real_vec)
{
  E_LF01 = real_vec;
}

void MF15Parser::set_NBT_G_LF01(vector<vector<vector<Integer> > >& int_vec)
{
  NBT_G_LF01 = int_vec;
}

void MF15Parser::set_INT_G_LF01(vector<vector<vector<Integer> > >& int_vec)
{
  INT_G_LF01 = int_vec;
}

void MF15Parser::set_E_INT_G_LF01(vector<vector<vector<Real> > >& real_vec)
{
  E_INT_G_LF01 = real_vec;
}

void MF15Parser::set_G_TAB_LF01(vector<vector<vector<Real> > >& real_vec)
{
  G_TAB_LF01 = real_vec;
}

void MF15Parser::set_NBT_S_LF05(vector<vector<Integer> >& int_vec)
{
  NBT_S_LF05 = int_vec;
}

void MF15Parser::set_INT_S_LF05(vector<vector<Integer> >& int_vec)
{
  INT_S_LF05 = int_vec;
}

void MF15Parser::set_E_INT_S_LF05(vector<vector<Real> >& real_vec)
{
  E_INT_S_LF05 = real_vec;
}

void MF15Parser::set_S_TAB_LF05(vector<vector<Real> >& real_vec)
{
  S_TAB_LF05 = real_vec;
}

void MF15Parser::set_NBT_G_LF05(vector<vector<Integer> >& int_vec)
{
  NBT_G_LF05 = int_vec;
}

void MF15Parser::set_INT_G_LF05(vector<vector<Integer> >& int_vec)
{
  INT_G_LF05 = int_vec;
}

void MF15Parser::set_E_INT_G_LF05(vector<vector<Real> >& real_vec)
{
  E_INT_G_LF05 = real_vec;
}

void MF15Parser::set_G_TAB_LF05(vector<vector<Real> >& real_vec)
{
  G_TAB_LF05 = real_vec;
}

void MF15Parser::set_NBT_S_LF07(vector<vector<Integer> >& int_vec)
{
  NBT_S_LF05 = int_vec;
}

void MF15Parser::set_INT_S_LF07(vector<vector<Integer> >& int_vec)
{
  INT_S_LF05 = int_vec;
}

void MF15Parser::set_E_INT_S_LF07(vector<vector<Real> >& real_vec)
{
  E_INT_S_LF05 = real_vec;
}

void MF15Parser::set_S_TAB_LF07(vector<vector<Real> >& real_vec)
{
  S_TAB_LF05 = real_vec;
}

void MF15Parser::set_NBT_S_LF09(vector<vector<Integer> >& int_vec)
{
  NBT_S_LF05 = int_vec;
}

void MF15Parser::set_INT_S_LF09(vector<vector<Integer> >& int_vec)
{
  INT_S_LF05 = int_vec;
}

void MF15Parser::set_E_INT_S_LF09(vector<vector<Real> >& real_vec)
{
  E_INT_S_LF05 = real_vec;
}

void MF15Parser::set_S_TAB_LF09(vector<vector<Real> >& real_vec)
{
  S_TAB_LF05 = real_vec;
}

void MF15Parser::set_NBT_A_LF11(vector<vector<Integer> >& int_vec)
{
  NBT_S_LF05 = int_vec;
}

void MF15Parser::set_INT_A_LF11(vector<vector<Integer> >& int_vec)
{
  INT_S_LF05 = int_vec;
}

void MF15Parser::set_E_INT_A_LF11(vector<vector<Real> >& real_vec)
{
  E_INT_S_LF05 = real_vec;
}

void MF15Parser::set_A_TAB_LF11(vector<vector<Real> >& real_vec)
{
  S_TAB_LF05 = real_vec;
}

void MF15Parser::set_NBT_B_LF11(vector<vector<Integer> >& int_vec)
{
  NBT_G_LF05 = int_vec;
}

void MF15Parser::set_INT_B_LF11(vector<vector<Integer> >& int_vec)
{
  INT_G_LF05 = int_vec;
}

void MF15Parser::set_E_INT_B_LF11(vector<vector<Real> >& real_vec)
{
  E_INT_G_LF05 = real_vec;
}

void MF15Parser::set_B_TAB_LF11(vector<vector<Real> >& real_vec)
{
  G_TAB_LF05 = real_vec;
}

