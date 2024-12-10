#include "EndfUtils/MFxxMTyyyParser/MF30MT002Parser.hpp"

using namespace frendy;

//constructor
MF30MT002Parser::MF30MT002Parser(void)
{
  clear();

  err_obj.set_output_mode(err_obj.warning_off);
}

//destructor
MF30MT002Parser::~MF30MT002Parser(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF30MT002Parser::store_data()
{
  MultiParser mp_obj;

  //Text file data check
  if( static_cast<Integer>(text.size()) < 2 )
  {
    string class_name = "MF30MT002Parser";
    string func_name  = "store_data()";

    ostringstream oss;
    oss << static_cast<Integer>(text.size());
    string str_data = "Text line number : " + oss.str();

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("The text line number is not appropriate for  MF=30, MT=002.");
    err_com.push_back("The text line number should be larger than 1.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //Check MF number
  if( mp_obj.check_mf(text, mf_no) != 0)
  {
    string class_name = "MF30MT002Parser";
    string func_name  = "store_data()";

    ostringstream oss01;
    oss01 << mf_no;
    string str_data01 = "Text data at first line : " + text[0];
    string str_data02 = "File number (MF)        : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("The MF and MT numbers are different to MF=30.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  mp_obj.get_mat(text, mat_no);

  int             line_no = 0;
  vector<Real>    r_vec;
  vector<Integer> i_vec;
  r_vec.resize(6);
  i_vec.resize(6);

  Integer mt_no_chk = 0;
  mp_obj.get_mf_mt(text, i_vec[0], mt_no_chk);
  if( mt_no_chk != 002 )
  {
    string class_name = "MF30MT002Parser";
    string func_name  = "store_data()";

    ostringstream oss01;
    oss01 << mt_no_chk;
    string str_data01 = "Text data at first line : " + text[0];
    string str_data02 = "Section number (MT)     : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    if( mt_no_chk == 001 )
    {
      err_com.push_back("This MT number is not supported in this class, please use MF30MT001Parser class.");
    }
    else
    {
      err_com.push_back("This MT number is not supported in this class, please use MT30Parser class.");
    }
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //Line No.01
  //ZA, AWR, NP
  mp_obj.read_head(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3]);
  ZA    = r_vec[0];
  AWR   = r_vec[1];
  NP    = i_vec[3];

  int i_max = static_cast<int>(NP);
  R_COV.resize(i_max);
  PARM.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    vector<Real> e_vec;
    mp_obj.read_list(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                     e_vec);
    PARM[i] = r_vec[0];

    R_COV[i] = e_vec;
    e_vec.clear();
  }
  r_vec.clear();
  i_vec.clear();

  mp_obj.line_no_check(text, line_no, mf_no, mt_no);

  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF30MT002Parser::clear()
{
  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);

  mat_no = unassigned_mat_no;
  ZA     = 0.0;
  AWR    = 0.0;
  NP     = 0;

  PARM.clear();

  clr_vec.clear_vec_array2_real(R_COV);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF30MT002Parser::set_text(vector<string> text_data)
{
  clear();

  text = text_data;
  store_data();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string>        MF30MT002Parser::get_text()
{
  return text;
}

Integer               MF30MT002Parser::get_mat_no()
{
  return mat_no;
}

Integer               MF30MT002Parser::get_mt_no()
{
  return mt_no;
}


Real                  MF30MT002Parser::get_ZA()
{
  return ZA;
}

Real                  MF30MT002Parser::get_AWR()
{
  return AWR;
}

Integer               MF30MT002Parser::get_NP()
{
  return NP;
}


vector<Real>          MF30MT002Parser::get_PARM()
{
  return PARM;
}

vector<vector<Real> > MF30MT002Parser::get_R_COV()
{
  return R_COV;
}


////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void MF30MT002Parser::set_mat_no(Integer& int_data)
{
  mat_no = int_data;
}

void MF30MT002Parser::set_ZA(Real& real_data)
{
  ZA = real_data;
}

void MF30MT002Parser::set_AWR(Real& real_data)
{
  AWR = real_data;
}

void MF30MT002Parser::set_NP(Integer& int_data)
{
  NP = int_data;
}

void MF30MT002Parser::set_PARM(vector<Real>& real_vec)
{
  PARM = real_vec;
}

void MF30MT002Parser::set_R_COV(vector<vector<Real> >& real_vec)
{
  R_COV = real_vec;
}

