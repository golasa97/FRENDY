#include "EndfUtils/MFxxMTyyyParser/MF02MT152Parser.hpp"

using namespace frendy;

//constructor
MF02MT152Parser::MF02MT152Parser(void)
{
  clear();

  err_obj.set_output_mode(err_obj.warning_off);
}

//destructor
MF02MT152Parser::~MF02MT152Parser(void)
{ 
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF02MT152Parser::store_data() 
{
  MultiParser mp_obj;

  //Text file data check
  if( static_cast<Integer>(text.size()) < 2 )
  {
    string class_name = "MF02MT152Parser";
    string func_name  = "store_data()";

    ostringstream oss;
    oss << static_cast<Integer>(text.size());
    string str_data = "Text line number : " + oss.str();

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("The text line number is not appropriate for  MF=02, MT=152.");
    err_com.push_back("The text line number should be larger than 1.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //Check MT and MF number
  if( mp_obj.check_mf_mt(text, mf_no, mt_no) != 0)
  {
    string class_name = "MF02MT152Parser";
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
    err_com.push_back("The MF and MT numbers are different to MF=02, MT=152.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  mp_obj.get_mat(text, mat_no);

  int     line_no = 0;
  Integer tmp_int;

  //Line No.01
  //ZA, AWR, LSSF and INT
  mp_obj.read_head(text, line_no, ZAR, AWR, LSSF, tmp_int, tmp_int, INT);

  vector<Real>    e_vec, r_vec;
  vector<Integer> i_vec;
  r_vec.resize(6);
  i_vec.resize(6);

  //Line No.02
  mp_obj.read_list(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                   e_vec);
  TEMP = r_vec[0];
  OPT1 = i_vec[0];
  OPT2 = i_vec[1];
  NE   = i_vec[3];

  if( i_vec[2] == 1+6*NE )
  {
    store_data_reconr_mode(e_vec);
  }
  else if( i_vec[2] == OPT2+NE*(1+5*OPT2) )
  {
    store_data_purr_mode(e_vec);
  }
  else
  {
    string class_name = "MF02MT152Parser";
    string func_name  = "store_data()";

    ostringstream oss01, oss02, oss03, oss04;
    oss01 << i_vec[2];
    oss02 << OPT1;
    oss03 << OPT2;
    oss04 << NE;
    string str_data01 = "Number of list data : " + oss01.str();
    string str_data02 = "OPT1                : " + oss02.str();
    string str_data03 = "OPT2                : " + oss03.str();
    string str_data04 = "NE                  : " + oss04.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("The number of list data is not equal to RECONR mode (1+6*NE) nor");
    err_com.push_back("PURR mode (OPT2+NE*(1+5*OPT2)).");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
  r_vec.clear();
  i_vec.clear();
  e_vec.clear();

  mp_obj.line_no_check(text, line_no, mf_no, mt_no);

  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF02MT152Parser::store_data_reconr_mode(vector<Real>& e_vec)
{
  int i_max = static_cast<int>(NE);
  E.resize(i_max);
  SIG_SC.resize(i_max);
  SIG_TOT.resize(i_max);
  SIG_FIS.resize(i_max);
  SIG_RAD.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    E[i]       = e_vec[6*i+1];
    SIG_TOT[i] = e_vec[6*i+2];
    SIG_SC[i]  = e_vec[6*i+3];
    SIG_FIS[i] = e_vec[6*i+4];
    SIG_RAD[i] = e_vec[6*i+5];
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF02MT152Parser::store_data_purr_mode(vector<Real>& e_vec)
{
  int ele_no = 0;

  int sig_zero_no = static_cast<int>(OPT2);
  SIG_ZERO.resize(sig_zero_no);
  for(int i=0; i<sig_zero_no; i++)
  {
    SIG_ZERO[i] = e_vec[ele_no];
    ele_no++;
  }

  int energy_no = static_cast<int>(NE);
  E.resize(energy_no);
  B_TABLE.resize(energy_no);
  for(int i=0; i<energy_no; i++)
  {
    E[i] = e_vec[ele_no];
    ele_no++;

    int j_max = 5; //P0 total, scatter, fission, radiation, P1 total
    B_TABLE[i].resize(j_max);
    for(int j=0; j<j_max; j++)
    {
      B_TABLE[i][j].resize(sig_zero_no);
      for(int k=0; k<sig_zero_no; k++)
      {
        B_TABLE[i][j][k] = e_vec[ele_no];
        ele_no++;
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF02MT152Parser::clear()
{
  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);

  mat_no = unassigned_mat_no;
  ZAR    = 0.0;
  AWR    = 0.0;
  TEMP   = 0.0;
  LSSF   = 0;
  INT    = 0;
  OPT1   = 0;
  OPT2   = 0;
  NE     = 0;
  E.clear();
  SIG_TOT.clear();
  SIG_SC.clear();
  SIG_FIS.clear();
  SIG_RAD.clear();  
  SIG_ZERO.clear();
  clr_obj.clear_vec_array3_real8(B_TABLE);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF02MT152Parser::set_text(vector<string> text_data)
{
  clear();

  text = text_data;
  store_data();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> MF02MT152Parser::get_text()
{
  return text;
}

Integer MF02MT152Parser::get_mat_no()
{
  return mat_no;
}


Real         MF02MT152Parser::get_ZAR()
{
  return ZAR;
}

Real         MF02MT152Parser::get_AWR()
{
  return AWR;
}

Integer      MF02MT152Parser::get_LSSF()
{
  return LSSF;
}

Integer      MF02MT152Parser::get_INT()
{
  return INT;
}


Real         MF02MT152Parser::get_TEMP()
{
  return TEMP;
}

Integer      MF02MT152Parser::get_OPT1()
{
  return OPT1;
}

Integer      MF02MT152Parser::get_OPT2()
{
  return OPT2;
}

Integer      MF02MT152Parser::get_NE()
{
  return NE;
}

vector<Real> MF02MT152Parser::get_E()
{
  return E;
}

vector<Real> MF02MT152Parser::get_SIG_TOT()
{
  return SIG_TOT;
}

vector<Real> MF02MT152Parser::get_SIG_SC()
{
  return SIG_SC;
}

vector<Real> MF02MT152Parser::get_SIG_FIS()
{
  return SIG_FIS;
}

vector<Real> MF02MT152Parser::get_SIG_RAD()
{
  return SIG_RAD;
}

vector<Real> MF02MT152Parser::get_SIG_ZERO()
{
  return SIG_ZERO;
}

vector<vector<vector<Real> > > MF02MT152Parser::get_B_TABLE()
{
  return B_TABLE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF02MT152Parser::set_mat_no(Integer& int_data)
{
  mat_no = int_data;
}

void MF02MT152Parser::set_ZAR(Real& real_data)
{
  ZAR = real_data;
}

void MF02MT152Parser::set_AWR(Real& real_data)
{
  AWR = real_data;
}

void MF02MT152Parser::set_LSSF(Integer& int_data)
{
  LSSF = int_data;
}

void MF02MT152Parser::set_INT(Integer& int_data)
{
  INT = int_data;
}


void MF02MT152Parser::set_TEMP(Real& real_data)
{
  TEMP = real_data;
}

void MF02MT152Parser::set_OPT1(Integer& int_data)
{
  OPT1 = int_data;
}

void MF02MT152Parser::set_OPT2(Integer& int_data)
{
  OPT2 = int_data;
}

void MF02MT152Parser::set_NE(Integer& int_data)
{
  NE = int_data;
}

void MF02MT152Parser::set_E(vector<Real>& real_vec)
{
  E = real_vec;
}

void MF02MT152Parser::set_SIG_TOT(vector<Real>& real_vec)
{
  SIG_TOT = real_vec;
}

void MF02MT152Parser::set_SIG_SC(vector<Real>& real_vec)
{
  SIG_SC = real_vec;
}

void MF02MT152Parser::set_SIG_FIS(vector<Real>& real_vec)
{
  SIG_FIS = real_vec;
}

void MF02MT152Parser::set_SIG_RAD(vector<Real>& real_vec)
{
  SIG_RAD = real_vec;
}

void MF02MT152Parser::set_SIG_ZERO(vector<Real>& real_vec)
{
  SIG_ZERO = real_vec;
}

void MF02MT152Parser::set_B_TABLE(vector<vector<vector<Real> > >& real_vec)
{
  B_TABLE = real_vec;
}

