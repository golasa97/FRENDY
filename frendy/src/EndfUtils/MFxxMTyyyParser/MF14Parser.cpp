#include "EndfUtils/MFxxMTyyyParser/MF14Parser.hpp"

using namespace frendy;

//constructor
MF14Parser::MF14Parser(void)
{
  clear();

  err_obj.set_output_mode(err_obj.warning_off);
}

//destructor
MF14Parser::~MF14Parser(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF14Parser::store_data()
{
  MultiParser mp_obj;

  //Text file data check
  if( static_cast<Integer>(text.size()) < 1 )
  {
    string class_name = "MF14Parser";
    string func_name  = "store_data()";

    ostringstream oss;
    oss << static_cast<Integer>(text.size());
    string str_data = "Text line number : " + oss.str();

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("The text line number is not appropriate for MF=14.");
    err_com.push_back("The text line number should be larger than 1.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //Check MF number
  if( mp_obj.check_mf(text, mf_no) != 0)
  {
    string class_name = "MF14Parser";
    string func_name  = "store_data()";

    ostringstream oss01;
    oss01 << mf_no;
    string str_data01 = "Text data at first line : " + text[0];
    string str_data02 = "File number (MF)        : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("The MF number is different to MF=14.");

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
  //ZA, AWR, LI, NK
  mp_obj.read_head(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3]);
  ZA  = r_vec[0];
  AWR = r_vec[1];
  LI  = i_vec[0];
  NK  = i_vec[2];

  if( LI == 0 )
  {
    LTT = i_vec[1];
    NI  = i_vec[3];

    if( LTT == 1 )
    {
      store_ltt01(mp_obj, line_no);
    }
    else if( LTT == 2 )
    {
      store_ltt02(mp_obj, line_no);
    }
    else
    {
      string class_name = "MF14Parser";
      string func_name  = "store_data()";

      ostringstream oss00, oss01;
      oss00 << mt_no;
      oss01 << LTT;
      string str_data00 = "Section number (MT) : " + oss00.str();
      string str_data01 = "LTT                 : " + oss01.str();

      vector<string> err_com;
      err_com.push_back(str_data00);
      err_com.push_back(str_data01);
      err_com.push_back("This LTT value at MF=14 is not supported in this program.");
      err_com.push_back("Supported LTT value is 1 and 2.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }
  else if( LI == 1 )
  {
    //There is no optional (additional) input.
  }
  else
  {
    string class_name = "MF14Parser";
    string func_name  = "store_data()";

    ostringstream oss00, oss01;
    oss00 << mt_no;
    oss01 << LI;
    string str_data00 = "Section number (MT) : " + oss00.str();
    string str_data01 = "LI                  : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data00);
    err_com.push_back(str_data01);
    err_com.push_back("This LI value at MF=14 is not supported in this program.");
    err_com.push_back("Supported LI value is 0 and 1.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
  r_vec.clear();
  i_vec.clear();

  mp_obj.line_no_check(text, line_no, mf_no, mt_no);

  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF14Parser::store_ltt01(MultiParser& mp_obj, int& line_no)
{
  vector<Real>    r_vec;
  vector<Integer> i_vec;
  r_vec.resize(6);
  i_vec.resize(6);

  resize_matrix();
  for(int i=0; i<static_cast<int>(NI); i++)
  {
    mp_obj.read_cont(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3]);
    EG[i] = r_vec[0];
    ES[i] = r_vec[1];
  }

  for(int i=static_cast<int>(NI); i<static_cast<int>(NK); i++)
  {
    vector<Integer> nbt_vec, int_vec;
    mp_obj.read_tab2(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                     nbt_vec, int_vec);
    EG[i] = r_vec[0];
    ES[i] = r_vec[1];
    NE[i] = i_vec[3];

    NBT_E[i] = nbt_vec;
    INT_E[i] = int_vec;

    int j_max = static_cast<int>(NE[i]);
    E[i].resize(j_max);
    A[i].resize(j_max);
    for(int j=0; j<j_max; j++)
    {
      vector<Real> e_vec;
      mp_obj.read_list(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                     e_vec);
      E[i][j] = r_vec[1];

      A[i][j] = e_vec;
      e_vec.clear();
    }
  }
  r_vec.clear();
  i_vec.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF14Parser::store_ltt02(MultiParser& mp_obj, int& line_no)
{
  vector<Real>    r_vec;
  vector<Integer> i_vec;
  r_vec.resize(6);
  i_vec.resize(6);

  resize_matrix();
  for(int i=0; i<static_cast<int>(NI); i++)
  {
    mp_obj.read_cont(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3]);
    EG[i] = r_vec[0];
    ES[i] = r_vec[1];
  }

  for(int i=static_cast<int>(NI); i<static_cast<int>(NK); i++)
  {
    vector<Integer> nbt_vec, int_vec;
    mp_obj.read_tab2(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                     nbt_vec, int_vec);
    EG[i] = r_vec[0];
    ES[i] = r_vec[1];
    NE[i] = i_vec[3];

    NBT_E[i] = nbt_vec;
    INT_E[i] = int_vec;

    int j_max = static_cast<int>(NE[i]);
    E[i].resize(j_max);

    NBT_P[i].resize(   j_max);
    INT_P[i].resize(   j_max);
    MU_INT_P[i].resize(j_max);
    P_TAB[i].resize(   j_max);
    for(int j=0; j<j_max; j++)
    {
      vector<Real> e_vec, n_vec;
      mp_obj.read_tab1(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                       nbt_vec, int_vec, e_vec, n_vec);
      E[i][j] = r_vec[1];

      NBT_P[i][j]    = nbt_vec;
      INT_P[i][j]    = int_vec;
      MU_INT_P[i][j] = e_vec;
      P_TAB[i][j]    = n_vec;
      nbt_vec.clear();
      int_vec.clear();
      e_vec.clear();
      n_vec.clear();
    }
  }
  r_vec.clear();
  i_vec.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF14Parser::clear()
{
  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);

  mat_no = unassigned_mat_no;
  mt_no  = unassigned_mt_no;
  ZA     = 0.0;
  AWR    = 0.0;
  LI     = 0;
  NK     = 0;
  LTT    = 0;
  NI     = 0;

  EG.clear();
  ES.clear();
  NE.clear();

  clr_vec.clear_vec_array2_int( NBT_E);
  clr_vec.clear_vec_array2_int( INT_E);
  clr_vec.clear_vec_array2_real(E);

  clr_vec.clear_vec_array3_real(A);
  clr_vec.clear_vec_array3_int( NBT_P);
  clr_vec.clear_vec_array3_int( INT_P);
  clr_vec.clear_vec_array3_real(MU_INT_P);
  clr_vec.clear_vec_array3_real(P_TAB);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF14Parser::resize_matrix()
{
  int nk = static_cast<int>(NK);

  EG.resize(   nk);
  ES.resize(   nk);
  NE.resize(   nk);
  NBT_E.resize(nk);
  INT_E.resize(nk);
  E.resize(    nk);

  A.resize(       nk);
  NBT_P.resize(   nk);
  INT_P.resize(   nk);
  MU_INT_P.resize(nk);
  P_TAB.resize(   nk);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF14Parser::set_text(vector<string> text_data)
{
  clear();

  text = text_data;
  store_data();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string>        MF14Parser::get_text()
{
  return text;
}

Integer               MF14Parser::get_mat_no()
{
  return mat_no;
}

Integer               MF14Parser::get_mt_no()
{
  return mt_no;
}

//Getter at line No.01
Real                  MF14Parser::get_ZA()
{
  return ZA;
}

Real                  MF14Parser::get_AWR()
{
  return AWR;
}

Integer               MF14Parser::get_LI()
{
  return LI;
}

Integer               MF14Parser::get_NK()
{
  return NK;
}

Integer               MF14Parser::get_LTT()
{
  return LTT;
}

Integer               MF14Parser::get_NI()
{
  return NI;
}


vector<Real>             MF14Parser::get_EG()
{
  return EG;
}

vector<Real>             MF14Parser::get_ES()
{
  return ES;
}

vector<Integer>          MF14Parser::get_NE()
{
  return NE;
}

vector<vector<Integer> > MF14Parser::get_NBT_E()
{
  return NBT_E;
}

vector<vector<Integer> > MF14Parser::get_INT_E()
{
  return INT_E;
}

vector<vector<Real> >    MF14Parser::get_E()
{
  return E;
}


vector<vector<vector<Real> > >    MF14Parser::get_A()
{
  return A;
}

vector<vector<vector<Integer> > > MF14Parser::get_NBT_P()
{
  return NBT_P;
}

vector<vector<vector<Integer> > > MF14Parser::get_INT_P()
{
  return INT_P;
}

vector<vector<vector<Real> > >    MF14Parser::get_MU_INT_P()
{
  return MU_INT_P;
}

vector<vector<vector<Real> > >    MF14Parser::get_P_TAB()
{
  return P_TAB;
}


////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void MF14Parser::set_mat_no(Integer& int_data)
{
  mat_no = int_data;
}

void MF14Parser::set_mt_no(Integer& int_data)
{
  mt_no = int_data;
}

void MF14Parser::set_ZA(Real& real_data)
{
  ZA = real_data;
}

void MF14Parser::set_AWR(Real& real_data)
{
  AWR = real_data;
}

void MF14Parser::set_LI(Integer& int_data)
{
  LI = int_data;
}

void MF14Parser::set_NK(Integer& int_data)
{
  NK = int_data;
}

void MF14Parser::set_LTT(Integer& int_data)
{
  LTT = int_data;
}

void MF14Parser::set_NI(Integer& int_data)
{
  NI = int_data;
}

void MF14Parser::set_EG(vector<Real>& real_vec)
{
  EG = real_vec;
}

void MF14Parser::set_ES(vector<Real>& real_vec)
{
  ES = real_vec;
}

void MF14Parser::set_NE(vector<Integer>& int_vec)
{
  NE = int_vec;
}

void MF14Parser::set_NBT_E(vector<vector<Integer> >& int_vec)
{
  NBT_E = int_vec;
}

void MF14Parser::set_INT_E(vector<vector<Integer> >& int_vec)
{
  INT_E = int_vec;
}

void MF14Parser::set_E(vector<vector<Real> >& real_vec)
{
  E = real_vec;
}

void MF14Parser::set_A(vector<vector<vector<Real> > >& real_vec)
{
  A = real_vec;
}

void MF14Parser::set_NBT_P(vector<vector<vector<Integer> > >& int_vec)
{
  NBT_P = int_vec;
}

void MF14Parser::set_INT_P(vector<vector<vector<Integer> > >& int_vec)
{
  INT_P = int_vec;
}

void MF14Parser::set_MU_INT_P(vector<vector<vector<Real> > >& real_vec)
{
  MU_INT_P = real_vec;
}

void MF14Parser::set_P_TAB(vector<vector<vector<Real> > >& real_vec)
{
  P_TAB = real_vec;
}

