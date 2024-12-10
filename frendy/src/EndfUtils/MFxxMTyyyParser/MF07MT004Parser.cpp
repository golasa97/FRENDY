#include "EndfUtils/MFxxMTyyyParser/MF07MT004Parser.hpp"

using namespace frendy;

//constructor
MF07MT004Parser::MF07MT004Parser(void)
{
  clear();

  err_obj.set_output_mode(err_obj.warning_off);
}

//destructor
MF07MT004Parser::~MF07MT004Parser(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF07MT004Parser::store_data()
{
  MultiParser mp_obj;

  int skip_sab_flg = 0;

  //Text file data check
  if( static_cast<Integer>(text.size()) < 5 )
  {
    string class_name = "MF07MT004Parser";
    string func_name  = "store_data()";

    ostringstream oss;
    oss << static_cast<Integer>(text.size());
    string str_data = "Text line number : " + oss.str();

    vector<string> err_com;
    err_com.push_back(str_data);
    if( static_cast<Integer>(text.size()) == 4 )
    {
      skip_sab_flg = 1;
      err_com.push_back("This format type is not equal to ENDF-6 format.");
      err_com.push_back("This format type may be ENDF-5 format.");
      err_com.push_back("BN data in the second line are only parsed.");
      err_com.push_back("Please check the nuclear data format.");

      err_obj.output_caution(class_name, func_name, err_com);
    }
    else
    {
      err_com.push_back("The text line number is not appropriate for  MF=07, MT=004.");
      err_com.push_back("The text line number should be larger than 4.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }

  //Check MT and MF number
  if( mp_obj.check_mf_mt(text, mf_no, mt_no) != 0)
  {
    string class_name = "MF07MT004Parser";
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
    err_com.push_back("The MF and MT numbers are different to MF=07, MT=004.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  mp_obj.get_mat(text, mat_no);

  int     line_no = 0;
  Integer tmp_int;
  vector<Real>    r_vec;
  vector<Integer> i_vec;
  r_vec.resize(6);
  i_vec.resize(6);

  //Line No.01
  //ZA, AWR, LTHR
  mp_obj.read_head(text, line_no, ZA, AWR, tmp_int, LAT, LASYM, tmp_int);

  //Line No.02
  //LLN, NS
  mp_obj.read_list(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                   B);
  LLN = i_vec[0];
  NS  = i_vec[3];
  if( skip_sab_flg == 1 )
  {
    NB = 0;
    resize_matrix();
    NBT_T.resize(0);
    INT_T.resize(0);
    T_INT_T.resize(0);
    T_TAB.resize(0);

    return;
  }

  mp_obj.read_tab2(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                   NBT_BETA, INT_BETA);
  NB  = i_vec[3];

  resize_matrix();

  for(int i=0; i< static_cast<int>(NB); i++)
  {
    vector<Integer> nbt_vec, int_vec;
    vector<Real>    e_vec,   ap_vec;

    mp_obj.read_tab1(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                     nbt_vec, int_vec, e_vec, ap_vec);
    T0[i]   = r_vec[0];
    BETA[i] = r_vec[1];
    if( i > 0 )
    {
      if( BETA[i] < BETA[i-1] )
      {
        string class_name = "MF07MT004Parser";
        string func_name  = "store_data()";

        ostringstream oss01, oss02, oss03, oss04;
        oss01 << i+1;
        oss02 << T0[i];
        oss03 << BETA[i-1];
        oss04 << BETA[i];
        string str_data01 = "The order of beta data list is not appropriate (beta[i] < beta[i-1]).";
        string str_data02 = "Element i : " + oss01.str();
        string str_data03 = "temp[i]   : " + oss02.str();
        string str_data04 = "beta[i-1] : " + oss03.str();
        string str_data05 = "beta[i]   : " + oss04.str();

        vector<string> err_com;
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back(str_data04);
        err_com.push_back(str_data05);
        err_com.push_back("Please check ENDF file.");

        err_obj.output_runtime_error(class_name, func_name, err_com);
      }
    }

    NBT_S0[i]   = nbt_vec;
    INT_S0[i]   = int_vec;
    A_INT_S0[i] = e_vec;
    S0_TAB[i]   = ap_vec;
    nbt_vec.clear();
    int_vec.clear();
    e_vec.clear();
    ap_vec.clear();

    int lt = static_cast<int>(i_vec[0]);
    T[i].resize( lt);
    LI[i].resize(lt);
    S[i].resize( lt);
    for(int j=0; j<lt; j++)
    {
      mp_obj.read_list(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                       e_vec);
      T[i][j]  = r_vec[0];
      LI[i][j] = i_vec[0];

      int k_max = static_cast<int>(e_vec.size());
      S[i][j].resize(k_max);
      for(int k=0; k<k_max; k++)
      {
        S[i][j][k] = e_vec[k];
      }
      e_vec.clear();
    }
  }

  int b_size   = static_cast<int>(B.size());
  for( int i=0; i<4; i++)
  {
    int read_flg = -1;
    if( i==0 )
    {
      read_flg = 1;
    }
    else
    {
      if( b_size > i*6 )
      {
        if ( B[i*6]==0 )
        {
          read_flg = 1;
        }
      }
    }

    if( read_flg > 0 )
    {
      vector<Integer> nbt_vec, int_vec;
      vector<Real>    e_vec,   ap_vec;
      mp_obj.read_tab1(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                       nbt_vec, int_vec, e_vec, ap_vec);

      NBT_T[i]   = nbt_vec;
      INT_T[i]   = int_vec;
      T_INT_T[i] = e_vec;
      T_TAB[i]   = ap_vec;
      nbt_vec.clear();
      int_vec.clear();
      e_vec.clear();
      ap_vec.clear();
    }
  }
  r_vec.clear();
  i_vec.clear();

  mp_obj.line_no_check(text, line_no, mf_no, mt_no);

  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF07MT004Parser::clear()
{
  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);

  mat_no = unassigned_mat_no;
  ZA     = 0.0;
  AWR    = 0.0;
  LAT    = 0;
  LASYM  = 0;

  LLN    = 0;
  NS     = 0;
  B.clear();

  NB     = 0;
  NBT_BETA.clear();
  INT_BETA.clear();

  T0.clear();
  BETA.clear();
  clr_vec.clear_vec_array2_int( NBT_S0);
  clr_vec.clear_vec_array2_int( INT_S0);
  clr_vec.clear_vec_array2_real(A_INT_S0);
  clr_vec.clear_vec_array2_real(S0_TAB);

  clr_vec.clear_vec_array2_real(T);
  clr_vec.clear_vec_array2_int( LI);
  clr_vec.clear_vec_array3_real(S);
  clr_vec.clear_vec_array2_int( NBT_T);
  clr_vec.clear_vec_array2_int( INT_T);
  clr_vec.clear_vec_array2_real(T_INT_T);
  clr_vec.clear_vec_array2_real(T_TAB);
}


////////////////////////////////////////////////////////////////////////////////////////////////////
void MF07MT004Parser::resize_matrix()
{
  int nb = static_cast<int>(NB);
  T0.resize(nb);
  BETA.resize(nb);

  NBT_S0.resize(  nb);
  INT_S0.resize(  nb);
  A_INT_S0.resize(nb);
  S0_TAB.resize(  nb);

  T.resize(   nb);
  LI.resize(  nb);
  S.resize(   nb);

  NBT_T.resize(4);
  INT_T.resize(4);
  T_INT_T.resize(4);
  T_TAB.resize(4);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF07MT004Parser::set_text(vector<string> text_data)
{
  clear();

  text = text_data;
  store_data();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> MF07MT004Parser::get_text()
{
  return text;
}

Integer MF07MT004Parser::get_mat_no()
{
  return mat_no;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Real                     MF07MT004Parser::get_ZA()
{
  return ZA;
}

Real                     MF07MT004Parser::get_AWR()
{
  return AWR;
}

Integer                  MF07MT004Parser::get_LAT()
{
  return LAT;
}

Integer                  MF07MT004Parser::get_LASYM()
{
  return LASYM;
}

Integer                  MF07MT004Parser::get_LLN()
{
  return LLN;
}

Integer                  MF07MT004Parser::get_NS()
{
  return NS;
}

vector<Real>             MF07MT004Parser::get_B()
{
  return B;
}

Integer                  MF07MT004Parser::get_NB()
{
  return NB;
}

vector<Integer>          MF07MT004Parser::get_NBT_BETA()
{
  return NBT_BETA;
}

vector<Integer>          MF07MT004Parser::get_INT_BETA()
{
  return INT_BETA;
}

vector<Real>             MF07MT004Parser::get_T0()
{
  return T0;
}

vector<Real>             MF07MT004Parser::get_BETA()
{
  return BETA;
}

vector<vector<Integer> > MF07MT004Parser::get_NBT_S0()
{
  return NBT_S0;
}

vector<vector<Integer> > MF07MT004Parser::get_INT_S0()
{
  return INT_S0;
}

vector<vector<Real> >    MF07MT004Parser::get_A_INT_S0()
{
  return A_INT_S0;
}

vector<vector<Real> >    MF07MT004Parser::get_S0_TAB()
{
  return S0_TAB;
}

vector<vector<Real> >    MF07MT004Parser::get_T()
{
  return T;
}

vector<vector<Integer> > MF07MT004Parser::get_LI()
{
  return LI;
}

vector<vector<vector<Real> > > MF07MT004Parser::get_S()
{
  return S;
}

vector<vector<Integer> > MF07MT004Parser::get_NBT_T()
{
  return NBT_T;
}

vector<vector<Integer> > MF07MT004Parser::get_INT_T()
{
  return INT_T;
}

vector<vector<Real> >    MF07MT004Parser::get_T_INT_T()
{
  return T_INT_T;
}

vector<vector<Real> >    MF07MT004Parser::get_T_TAB()
{
  return T_TAB;
}



////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void MF07MT004Parser::set_mat_no(Integer& int_data)
{
  mat_no = int_data;
}

void MF07MT004Parser::set_ZA(Real& real_data)
{
  ZA = real_data;
}

void MF07MT004Parser::set_AWR(Real& real_data)
{
  AWR = real_data;
}

void MF07MT004Parser::set_LAT(Integer& int_data)
{
  LAT = int_data;
}

void MF07MT004Parser::set_LASYM(Integer& int_data)
{
  LASYM = int_data;
}

void MF07MT004Parser::set_LLN(Integer& int_data)
{
  LLN = int_data;
}

void MF07MT004Parser::set_NS(Integer& int_data)
{
  NS = int_data;
}

void MF07MT004Parser::set_B(vector<Real>& real_vec)
{
  B = real_vec;
}

void MF07MT004Parser::set_NB(Integer& int_data)
{
  NB = int_data;
}

void MF07MT004Parser::set_NBT_BETA(vector<Integer>& int_vec)
{
  NBT_BETA = int_vec;
}

void MF07MT004Parser::set_INT_BETA(vector<Integer>& int_vec)
{
  INT_BETA = int_vec;
}

void MF07MT004Parser::set_T0(vector<Real>& real_vec)
{
  T0 = real_vec;
}

void MF07MT004Parser::set_BETA(vector<Real>& real_vec)
{
  BETA = real_vec;
}

void MF07MT004Parser::set_NBT_S0(vector<vector<Integer> >& int_vec)
{
  NBT_S0 = int_vec;
}

void MF07MT004Parser::set_INT_S0(vector<vector<Integer> >& int_vec)
{
  INT_S0 = int_vec;
}

void MF07MT004Parser::set_A_INT_S0(vector<vector<Real> >& real_vec)
{
  A_INT_S0 = real_vec;
}

void MF07MT004Parser::set_S0_TAB(vector<vector<Real> >& real_vec)
{
  S0_TAB = real_vec;
}

void MF07MT004Parser::set_T(vector<vector<Real> >& real_vec)
{
  T = real_vec;
}

void MF07MT004Parser::set_LI(vector<vector<Integer> >& int_vec)
{
  LI = int_vec;
}

void MF07MT004Parser::set_S(vector<vector<vector<Real> > >& real_vec)
{
  S = real_vec;
}

void MF07MT004Parser::set_NBT_T(vector<vector<Integer> >& int_vec)
{
  NBT_T = int_vec;
}

void MF07MT004Parser::set_INT_T(vector<vector<Integer> >& int_vec)
{
  INT_T = int_vec;
}

void MF07MT004Parser::set_T_INT_T(vector<vector<Real> >& real_vec)
{
  T_INT_T = real_vec;
}

void MF07MT004Parser::set_T_TAB(vector<vector<Real> >& real_vec)
{
  T_TAB = real_vec;
}

