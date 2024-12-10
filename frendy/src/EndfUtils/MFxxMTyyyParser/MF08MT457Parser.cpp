#include "EndfUtils/MFxxMTyyyParser/MF08MT457Parser.hpp"

using namespace frendy;

//constructor
MF08MT457Parser::MF08MT457Parser(void)
{
  clear();

  err_obj.set_output_mode(err_obj.warning_off);
}

//destructor
MF08MT457Parser::~MF08MT457Parser(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF08MT457Parser::store_data()
{
  MultiParser mp_obj;

  //Text file data check
  if( static_cast<Integer>(text.size()) < 2 )
  {
    string class_name = "MF08MT457Parser";
    string func_name  = "store_data()";

    ostringstream oss;
    oss << static_cast<Integer>(text.size());
    string str_data = "Text line number : " + oss.str();

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("The text line number is not appropriate for  MF=08, MT=457.");
    err_com.push_back("The text line number should be larger than 1.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //Check MF number
  if( mp_obj.check_mf_mt(text, mf_no, mt_no) != 0)
  {
    Integer mf, mt;
    mp_obj.get_mf_mt(text, mf, mt);
    string class_name = "MF08MT457Parser";
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
    if( mt == 454 )
    {
      err_com.push_back("This MT number is not supported in this class, please use MT08MF454Parser class.");
    }
    else if( mt == 459 )
    {
      err_com.push_back("This MT number is not supported in this class, please use MT08MF459Parser class.");
    }
    else
    {
      err_com.push_back("This MT number is not supported in this class, please use MF08Parser class.");
    }
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  mp_obj.get_mat(text, mat_no);

  int             line_no = 0;
  vector<Real>    r_vec;
  vector<Integer> i_vec;
  r_vec.resize(6);
  i_vec.resize(6);

  //Line No.01
  //ZA, AWR, LIS, LISO, NST, NSP
  mp_obj.read_head(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3]);
  ZA   = r_vec[0];
  AWR  = r_vec[1];
  LIS  = i_vec[0];
  LISO = i_vec[1];
  NST  = i_vec[2];
  NSP  = i_vec[3];
  r_vec.clear();
  i_vec.clear();

  if( NST == 0 )
  {
    store_nst00(mp_obj, line_no);
  }
  else if( NST == 1 )
  {
    store_nst01(mp_obj, line_no);
  }

  mp_obj.line_no_check(text, line_no, mf_no, mt_no);

  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF08MT457Parser::store_nst00(MultiParser& mp_obj, int& line_no)
{
  vector<Real>    r_vec;
  vector<Integer> i_vec;
  r_vec.resize(6);
  i_vec.resize(6);

  vector<Real> e_vec;
  mp_obj.read_list(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                   e_vec);
  T_HALF   = r_vec[0];
  D_T_HALF = r_vec[1];

  if( i_vec[2] % 2 != 0)
  {
    string class_name = "MF08MT457Parser";
    string func_name  = "store_nst00(MultiParser& mp_obj, int& line_no)";

    ostringstream oss01;
    oss01 << i_vec[2];
    string str_data01 = "NC : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("The number of NC at NST=0 must be multiple of 2.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  int i_max = static_cast<int>(e_vec.size())/2;
  E_X.resize(i_max);
  D_E_X.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    E_X[i]   = e_vec[2*i];
    D_E_X[i] = e_vec[2*i+1];
  }
  e_vec.clear();


  mp_obj.read_list(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                   e_vec);
  SPI = r_vec[0];
  PAR = r_vec[1];

  if( i_vec[2] != i_vec[3]*6 )
  {
    string class_name = "MF08MT457Parser";
    string func_name  = "store_nst00(MultiParser& mp_obj, int& line_no)";

    ostringstream oss01, oss02;
    oss01 << i_vec[2];
    oss02 << i_vec[3];
    string str_data01 = "6*NDK : " + oss01.str();
    string str_data02 = "NDK   : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("The number of 6*NDK at NST=0 is not correct value.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  int ndk = i_vec[3];
  RTYP0.resize(ndk);
  RFS.resize(ndk);
  Q.resize(ndk);
  D_Q.resize(ndk);
  BR.resize(ndk);
  D_BR.resize(ndk);
  for(int i=0; i<ndk; i++)
  {
    RTYP0[i] = e_vec[6*i+0];
    RFS[i]   = e_vec[6*i+1];
    Q[i]     = e_vec[6*i+2];
    D_Q[i]   = e_vec[6*i+3];
    BR[i]    = e_vec[6*i+4];
    D_BR[i]  = e_vec[6*i+5];
  }
  e_vec.clear();

  resize_matrix();

  for(int i=0; i<static_cast<int>(NSP); i++)
  {
    mp_obj.read_list(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                     e_vec);
    STYP[i] = r_vec[1];
    LCON[i] = i_vec[0];
    NER[i]  = i_vec[3];

    if( i_vec[2] != 6 )
    {
      string class_name = "MF08MT457Parser";
      string func_name  = "store_nst00(MultiParser& mp_obj, int& line_no)";

      ostringstream oss01, oss02, oss03;
      oss01 << i;
      oss02 << static_cast<int>(NSP);
      oss03 << i_vec[2];
      string str_data01 = "NSP : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "6   : " + oss03.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back("The number of list at [MAT, 8, 457/ 0.0, STYP, LCON, 0, 6, NER] (NST=0)");
      err_com.push_back("is not equal to 6.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    FD[i]      = e_vec[0];
    D_FD[i]    = e_vec[1];
    ER_AV[i]   = e_vec[2];
    D_ER_AV[i] = e_vec[3];
    FC[i]      = e_vec[4];
    D_FC[i]    = e_vec[5];

    if( LCON[i] != 1 )
    {
      int j_max = static_cast<int>(NER[i]);
      ER[i].resize(j_max);
      D_ER[i].resize(  j_max);
      RTYP1[i].resize( j_max);
      TYPE[i].resize(  j_max);
      RI[i].resize(    j_max);
      D_RI[i].resize(  j_max);
      RIS[i].resize(   j_max);
      D_RIS[i].resize( j_max);
      RICC[i].resize(  j_max);
      D_RICC[i].resize(j_max);
      RICK[i].resize(  j_max);
      D_RICK[i].resize(j_max);
      RICL[i].resize(  j_max);
      D_RICL[i].resize(j_max);
      for(int j=0; j<j_max; j++)
      {
        mp_obj.read_list(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                         e_vec);
        ER[i][j]   = r_vec[0];
        D_ER[i][j] = r_vec[1];

        if( i_vec[2] % 2 != 0 && i_vec[2] > 2 )
        {
          string class_name = "MF08MT457Parser";
          string func_name  = "store_nst00(MultiParser& mp_obj, int& line_no)";

          ostringstream oss01, oss02, oss03, oss04, oss05;
          oss01 << i;
          oss02 << static_cast<int>(NSP);
          oss03 << j;
          oss04 << static_cast<int>(NER[i]);
          oss05 << i_vec[2];
          string str_data01 = "NSP : " + oss01.str() + " / " + oss02.str();
          string str_data02 = "NER : " + oss03.str() + " / " + oss04.str();
          string str_data03 = "NT  : " + oss05.str();

          vector<string> err_com;
          err_com.push_back(str_data01);
          err_com.push_back(str_data02);
          err_com.push_back(str_data03);
          err_com.push_back("The number of NT at NST=0 must be 4, 6, 8, 10, or 12.");

          err_obj.output_runtime_error(class_name, func_name, err_com);
        }

        RTYP1[i][j]  = e_vec[ 0];
        TYPE[i][j]   = e_vec[ 1];
        RI[i][j]     = e_vec[ 2];
        D_RI[i][j]   = e_vec[ 3];
        RIS[i][j]    = static_cast<Real>(unassigned_data_val);
        D_RIS[i][j]  = static_cast<Real>(unassigned_data_val);
        RICC[i][j]   = static_cast<Real>(unassigned_data_val);
        D_RICC[i][j] = static_cast<Real>(unassigned_data_val);
        RICK[i][j]   = static_cast<Real>(unassigned_data_val);
        D_RICK[i][j] = static_cast<Real>(unassigned_data_val);
        RICL[i][j]   = static_cast<Real>(unassigned_data_val);
        D_RICL[i][j] = static_cast<Real>(unassigned_data_val);

        if( i_vec[2] > 4 )
        {
          RIS[i][j]    = e_vec[ 4];
          D_RIS[i][j]  = e_vec[ 5];
        }

        if( i_vec[2] > 6 )
        {
          RICC[i][j]   = e_vec[ 6];
          D_RICC[i][j] = e_vec[ 7];
        }

        if( i_vec[2] > 8 )
        {
          RICK[i][j]   = e_vec[ 8];
          D_RICK[i][j] = e_vec[ 9];
        }

        if( i_vec[2] > 10 )
        {
          RICL[i][j]   = e_vec[10];
          D_RICL[i][j] = e_vec[11];
        }
        e_vec.clear();
      }
    }

    if( LCON[i] != 0 )
    {
      vector<Integer> nbt_vec, int_vec;
      vector<Real>    rp_vec;

      mp_obj.read_tab1(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                       nbt_vec, int_vec, e_vec, rp_vec);
      RTYP2[i] = r_vec[0];
      LCOV[i]  = i_vec[1];

      NBT_RP[i] = nbt_vec;
      INT_RP[i] = int_vec;
      E_INT_RP[i] = e_vec;
      RP_TAB[i]   = rp_vec;
      nbt_vec.clear();
      int_vec.clear();
      e_vec.clear();
      rp_vec.clear();

      if( LCOV[i] != 0 )
      {
        mp_obj.read_list(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                         e_vec);
        LB[i] = i_vec[1];
        if( i_vec[2] != i_vec[3]*2 )
        {
          string class_name = "MF08MT457Parser";
          string func_name  = "store_nst00(MultiParser& mp_obj, int& line_no)";

          ostringstream oss01, oss02, oss03, oss04;
          oss01 << i;
          oss02 << static_cast<int>(NSP);
          oss03 << i_vec[2];
          oss04 << i_vec[3];
          string str_data01 = "NSP   : " + oss01.str() + " / " + oss02.str();
          string str_data02 = "2*NPP : " + oss03.str();
          string str_data03 = "NPP   : " + oss04.str();

          vector<string> err_com;
          err_com.push_back(str_data01);
          err_com.push_back(str_data02);
          err_com.push_back(str_data03);
          err_com.push_back("The number of 2*NPP at NST=0 is not correct value.");

          err_obj.output_runtime_error(class_name, func_name, err_com);
        }

        int j_max = static_cast<int>(e_vec.size())/2;
        E_K[i].resize(j_max);
        F_K[i].resize(j_max);
        for(int j=0; j<j_max; j++)
        {
          E_K[i][j] = e_vec[2*j];
          F_K[i][j] = e_vec[2*j+1];
        }
        e_vec.clear();
      }
    }
  }
  r_vec.clear();
  i_vec.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF08MT457Parser::store_nst01(MultiParser& mp_obj, int& line_no)
{
  vector<Real>    r_vec;
  vector<Integer> i_vec;
  r_vec.resize(6);
  i_vec.resize(6);

  vector<Real> e_vec;
  mp_obj.read_list(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                   e_vec);
  e_vec.clear();

  int line_no_pre = line_no;
  mp_obj.read_list(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                   e_vec);
  SPI = r_vec[0];
  PAR = r_vec[1];

  if( static_cast<int>(e_vec.size()) == 0 && line_no - line_no_pre > 1 )
  {
    //Modification of the line_no.
    //List data read the next line even if i_vec[2] (the size of e_vec) is zero.
    line_no--;
  }

  r_vec.clear();
  i_vec.clear();
  e_vec.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF08MT457Parser::clear()
{
  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);

  mat_no = unassigned_mat_no;
  ZA     = 0.0;
  AWR    = 0.0;
  LIS    = 0;
  LISO   = 0;
  NST    = 0;
  NSP    = 0;

  T_HALF   = 0.0;
  D_T_HALF = 0.0;
  E_X.clear();
  D_E_X.clear();

  SPI  = 0.0;
  PAR  = 0.0;
  RTYP0.clear();
  RFS.clear();
  Q.clear();
  D_Q.clear();
  BR.clear();
  D_BR.clear();

  STYP.clear();
  LCON.clear();
  NER.clear();
  FD.clear();
  D_FD.clear();
  ER_AV.clear();
  D_ER_AV.clear();
  FC.clear();
  D_FC.clear();

  clr_vec.clear_vec_array2_real(ER);
  clr_vec.clear_vec_array2_real(D_ER);
  clr_vec.clear_vec_array2_real(RTYP1);
  clr_vec.clear_vec_array2_real(TYPE);
  clr_vec.clear_vec_array2_real(RI);
  clr_vec.clear_vec_array2_real(D_RI);
  clr_vec.clear_vec_array2_real(RIS);
  clr_vec.clear_vec_array2_real(D_RIS);
  clr_vec.clear_vec_array2_real(RICC);
  clr_vec.clear_vec_array2_real(D_RICC);
  clr_vec.clear_vec_array2_real(RICK);
  clr_vec.clear_vec_array2_real(D_RICK);
  clr_vec.clear_vec_array2_real(RICL);
  clr_vec.clear_vec_array2_real(D_RICL);

  RTYP2.clear();
  LCOV.clear();
  clr_vec.clear_vec_array2_int(NBT_RP);
  clr_vec.clear_vec_array2_int(INT_RP);
  clr_vec.clear_vec_array2_real(E_INT_RP);
  clr_vec.clear_vec_array2_real(RP_TAB);

  LB.clear();
  clr_vec.clear_vec_array2_real(E_K);
  clr_vec.clear_vec_array2_real(F_K);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF08MT457Parser::resize_matrix()
{
  int nsp = static_cast<int>(NSP);
  STYP.resize(nsp);
  LCON.resize(nsp);
  NER.resize(nsp);
  FD.resize(nsp);
  D_FD.resize(nsp);
  ER_AV.resize(nsp);
  D_ER_AV.resize(nsp);
  FC.resize(nsp);
  D_FC.resize(nsp);

  ER.resize(nsp);
  D_ER.resize(nsp);
  RTYP1.resize(nsp);
  TYPE.resize(nsp);
  RI.resize(nsp);
  D_RI.resize(nsp);
  RIS.resize(nsp);
  D_RIS.resize(nsp);
  RICC.resize(nsp);
  D_RICC.resize(nsp);
  RICK.resize(nsp);
  D_RICK.resize(nsp);
  RICL.resize(nsp);
  D_RICL.resize(nsp);

  RTYP2.resize(nsp);
  LCOV.resize(nsp);
  NBT_RP.resize(nsp);
  INT_RP.resize(nsp);
  E_INT_RP.resize(nsp);
  RP_TAB.resize(nsp);

  LB.resize(nsp);
  E_K.resize(nsp);
  F_K.resize(nsp);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF08MT457Parser::set_text(vector<string> text_data)
{
  clear();

  text = text_data;
  store_data();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string>        MF08MT457Parser::get_text()
{
  return text;
}

Integer               MF08MT457Parser::get_mat_no()
{
  return mat_no;
}

Real                     MF08MT457Parser::get_ZA()
{
  return ZA;
}

Real                     MF08MT457Parser::get_AWR()
{
  return AWR;
}


Integer                  MF08MT457Parser::get_LIS()
{
  return LIS;
}

Integer                  MF08MT457Parser::get_LISO()
{
  return LISO;
}

Integer                  MF08MT457Parser::get_NST()
{
  return NST;
}

Integer                  MF08MT457Parser::get_NSP()
{
  return NSP;
}


Real                     MF08MT457Parser::get_T_HALF()
{
  return T_HALF;
}

Real                     MF08MT457Parser::get_D_T_HALF()
{
  return D_T_HALF;
}

vector<Real>             MF08MT457Parser::get_E_X()
{
  return E_X;
}

vector<Real>             MF08MT457Parser::get_D_E_X()
{
  return D_E_X;
}


Real                     MF08MT457Parser::get_SPI()
{
  return SPI;
}

Real                     MF08MT457Parser::get_PAR()
{
  return PAR;
}

vector<Real>             MF08MT457Parser::get_RTYP0()
{
  return RTYP0;
}

vector<Real>             MF08MT457Parser::get_RFS()
{
  return RFS;
}

vector<Real>             MF08MT457Parser::get_Q()
{
  return Q;
}

vector<Real>             MF08MT457Parser::get_D_Q()
{
  return D_Q;
}

vector<Real>             MF08MT457Parser::get_BR()
{
  return BR;
}

vector<Real>             MF08MT457Parser::get_D_BR()
{
  return D_BR;
}


vector<Real>             MF08MT457Parser::get_STYP()
{
  return STYP;
}

vector<Integer>          MF08MT457Parser::get_LCON()
{
  return LCON;
}

vector<Integer>          MF08MT457Parser::get_NER()
{
  return NER;
}

vector<Real>             MF08MT457Parser::get_FD()
{
  return FD;
}

vector<Real>             MF08MT457Parser::get_D_FD()
{
  return D_FD;
}

vector<Real>             MF08MT457Parser::get_ER_AV()
{
  return ER_AV;
}

vector<Real>             MF08MT457Parser::get_D_ER_AV()
{
  return D_ER_AV;
}

vector<Real>             MF08MT457Parser::get_FC()
{
  return FC;
}

vector<Real>             MF08MT457Parser::get_D_FC()
{
  return D_FC;
}


vector<vector<Real> >    MF08MT457Parser::get_ER()
{
  return ER;
}

vector<vector<Real> >    MF08MT457Parser::get_D_ER()
{
  return D_ER;
}

vector<vector<Real> >    MF08MT457Parser::get_RTYP1()
{
  return RTYP1;
}

vector<vector<Real> >    MF08MT457Parser::get_TYPE()
{
  return TYPE;
}

vector<vector<Real> >    MF08MT457Parser::get_RI()
{
  return RI;
}

vector<vector<Real> >    MF08MT457Parser::get_D_RI()
{
  return D_RI;
}

vector<vector<Real> >    MF08MT457Parser::get_RIS()
{
  return RIS;
}

vector<vector<Real> >    MF08MT457Parser::get_D_RIS()
{
  return D_RIS;
}

vector<vector<Real> >    MF08MT457Parser::get_RICC()
{
  return RICC;
}

vector<vector<Real> >    MF08MT457Parser::get_D_RICC()
{
  return D_RICC;
}

vector<vector<Real> >    MF08MT457Parser::get_RICK()
{
  return RICK;
}

vector<vector<Real> >    MF08MT457Parser::get_D_RICK()
{
  return D_RICK;
}

vector<vector<Real> >    MF08MT457Parser::get_RICL()
{
  return RICL;
}

vector<vector<Real> >    MF08MT457Parser::get_D_RICL()
{
  return D_RICL;
}


vector<Real>             MF08MT457Parser::get_RTYP2()
{
  return RTYP2;
}

vector<Integer>          MF08MT457Parser::get_LCOV()
{
  return LCOV;
}

vector<vector<Integer> > MF08MT457Parser::get_NBT_RP()
{
  return NBT_RP;
}

vector<vector<Integer> > MF08MT457Parser::get_INT_RP()
{
  return INT_RP;
}

vector<vector<Real> >    MF08MT457Parser::get_E_INT_RP()
{
  return E_INT_RP;
}

vector<vector<Real> >    MF08MT457Parser::get_RP_TAB()
{
  return RP_TAB;
}


vector<Integer>          MF08MT457Parser::get_LB()
{
  return LB;
}

vector<vector<Real> >    MF08MT457Parser::get_E_K()
{
  return E_K;
}

vector<vector<Real> >    MF08MT457Parser::get_F_K()
{
  return F_K;
}


////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void MF08MT457Parser::set_mat_no(Integer& int_data)
{
  mat_no = int_data;
}

void MF08MT457Parser::set_ZA(Real& real_data)
{
  ZA = real_data;
}

void MF08MT457Parser::set_AWR(Real& real_data)
{
  AWR = real_data;
}

void MF08MT457Parser::set_LIS(Integer& int_data)
{
  LIS = int_data;
}

void MF08MT457Parser::set_LISO(Integer& int_data)
{
  LISO = int_data;
}

void MF08MT457Parser::set_NST(Integer& int_data)
{
  NST = int_data;
}

void MF08MT457Parser::set_NSP(Integer& int_data)
{
  NSP = int_data;
}

void MF08MT457Parser::set_T_HALF(Real& real_data)
{
  T_HALF = real_data;
}

void MF08MT457Parser::set_D_T_HALF(Real& real_data)
{
  D_T_HALF = real_data;
}

void MF08MT457Parser::set_E_X(vector<Real>& real_vec)
{
  E_X = real_vec;
}

void MF08MT457Parser::set_D_E_X(vector<Real>& real_vec)
{
  D_E_X = real_vec;
}

void MF08MT457Parser::set_SPI(Real& real_data)
{
  SPI = real_data;
}

void MF08MT457Parser::set_PAR(Real& real_data)
{
  PAR = real_data;
}

void MF08MT457Parser::set_RTYP0(vector<Real>& real_vec)
{
  RTYP0 = real_vec;
}

void MF08MT457Parser::set_RFS(vector<Real>& real_vec)
{
  RFS = real_vec;
}

void MF08MT457Parser::set_Q(vector<Real>& real_vec)
{
  Q = real_vec;
}

void MF08MT457Parser::set_D_Q(vector<Real>& real_vec)
{
  D_Q = real_vec;
}

void MF08MT457Parser::set_BR(vector<Real>& real_vec)
{
  BR = real_vec;
}

void MF08MT457Parser::set_D_BR(vector<Real>& real_vec)
{
  D_BR = real_vec;
}

void MF08MT457Parser::set_STYP(vector<Real>& real_vec)
{
  STYP = real_vec;
}

void MF08MT457Parser::set_LCON(vector<Integer>& int_vec)
{
  LCON = int_vec;
}

void MF08MT457Parser::set_NER(vector<Integer>& int_vec)
{
  NER = int_vec;
}

void MF08MT457Parser::set_FD(vector<Real>& real_vec)
{
  FD = real_vec;
}

void MF08MT457Parser::set_D_FD(vector<Real>& real_vec)
{
  D_FD = real_vec;
}

void MF08MT457Parser::set_ER_AV(vector<Real>& real_vec)
{
  ER_AV = real_vec;
}

void MF08MT457Parser::set_D_ER_AV(vector<Real>& real_vec)
{
  D_ER_AV = real_vec;
}

void MF08MT457Parser::set_FC(vector<Real>& real_vec)
{
  FC = real_vec;
}

void MF08MT457Parser::set_D_FC(vector<Real>& real_vec)
{
  D_FC = real_vec;
}

void MF08MT457Parser::set_ER(vector<vector<Real> >& real_vec)
{
  ER = real_vec;
}

void MF08MT457Parser::set_D_ER(vector<vector<Real> >& real_vec)
{
  D_ER = real_vec;
}

void MF08MT457Parser::set_RTYP1(vector<vector<Real> >& real_vec)
{
  RTYP1 = real_vec;
}

void MF08MT457Parser::set_TYPE(vector<vector<Real> >& real_vec)
{
  TYPE = real_vec;
}

void MF08MT457Parser::set_RI(vector<vector<Real> >& real_vec)
{
  RI = real_vec;
}

void MF08MT457Parser::set_D_RI(vector<vector<Real> >& real_vec)
{
  D_RI = real_vec;
}

void MF08MT457Parser::set_RIS(vector<vector<Real> >& real_vec)
{
  RIS = real_vec;
}

void MF08MT457Parser::set_D_RIS(vector<vector<Real> >& real_vec)
{
  D_RIS = real_vec;
}

void MF08MT457Parser::set_RICC(vector<vector<Real> >& real_vec)
{
  RICC = real_vec;
}

void MF08MT457Parser::set_D_RICC(vector<vector<Real> >& real_vec)
{
  D_RICC = real_vec;
}

void MF08MT457Parser::set_RICK(vector<vector<Real> >& real_vec)
{
  RICK = real_vec;
}

void MF08MT457Parser::set_D_RICK(vector<vector<Real> >& real_vec)
{
  D_RICK = real_vec;
}

void MF08MT457Parser::set_RICL(vector<vector<Real> >& real_vec)
{
  RICL = real_vec;
}

void MF08MT457Parser::set_D_RICL(vector<vector<Real> >& real_vec)
{
  D_RICL = real_vec;
}

void MF08MT457Parser::set_RTYP2(vector<Real>& real_vec)
{
  RTYP2 = real_vec;
}

void MF08MT457Parser::set_LCOV(vector<Integer>& int_vec)
{
  LCOV = int_vec;
}

void MF08MT457Parser::set_NBT_RP(vector<vector<Integer> >& int_vec)
{
  NBT_RP = int_vec;
}

void MF08MT457Parser::set_INT_RP(vector<vector<Integer> >& int_vec)
{
  INT_RP = int_vec;
}

void MF08MT457Parser::set_E_INT_RP(vector<vector<Real> >& real_vec)
{
  E_INT_RP = real_vec;
}

void MF08MT457Parser::set_RP_TAB(vector<vector<Real> >& real_vec)
{
  RP_TAB = real_vec;
}

void MF08MT457Parser::set_LB(vector<Integer>& int_vec)
{
  LB = int_vec;
}

void MF08MT457Parser::set_E_K(vector<vector<Real> >& real_vec)
{
  E_K = real_vec;
}

void MF08MT457Parser::set_F_K(vector<vector<Real> >& real_vec)
{
  F_K = real_vec;
}

