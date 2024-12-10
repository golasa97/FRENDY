#include "EndfUtils/MFxxMTyyyParser/MF30MT001Parser.hpp"

using namespace frendy;

//constructor
MF30MT001Parser::MF30MT001Parser(void)
{
  clear();

  err_obj.set_output_mode(err_obj.warning_off);
}

//destructor
MF30MT001Parser::~MF30MT001Parser(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF30MT001Parser::store_data()
{
  MultiParser mp_obj;

  //Text file data check
  if( static_cast<Integer>(text.size()) < 2 )
  {
    string class_name = "MF30MT001Parser";
    string func_name  = "store_data()";

    ostringstream oss;
    oss << static_cast<Integer>(text.size());
    string str_data = "Text line number : " + oss.str();

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("The text line number is not appropriate for  MF=30, MT=001.");
    err_com.push_back("The text line number should be larger than 1.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //Check MF number
  if( mp_obj.check_mf(text, mf_no) != 0)
  {
    string class_name = "MF30MT001Parser";
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
  if( mt_no_chk != 001 )
  {
    string class_name = "MF30MT001Parser";
    string func_name  = "store_data()";

    ostringstream oss01;
    oss01 << mt_no_chk;
    string str_data01 = "Text data at first line : " + text[0];
    string str_data02 = "Section number (MT)     : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    if( mt_no_chk == 002 )
    {
      err_com.push_back("This MT number is not supported in this class, please use MF30MT002Parser class.");
    }
    else
    {
      err_com.push_back("This MT number is not supported in this class, please use MF30Parser class.");
    }
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //Line No.01
  //ZA, AWR, NP
  mp_obj.read_head(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3]);
  ZA    = r_vec[0];
  AWR   = r_vec[1];
  NP    = i_vec[3];

  mp_obj.read_cont(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3]);
  NDIR  = i_vec[2];
  NCTAB = i_vec[3];

  int i_max = static_cast<int>(NDIR);
  MP_NDIR.resize(   i_max);
  MFSEN_NDIR.resize(i_max);
  MTSEN_NDIR.resize(i_max);
  NC_NDIR.resize(   i_max);
  for(int i=0; i<i_max; i++)
  {
    mp_obj.read_cont(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3]);
    MP_NDIR[i]    = i_vec[0];
    MFSEN_NDIR[i] = i_vec[1];
    MTSEN_NDIR[i] = i_vec[2];
    NC_NDIR[i]    = i_vec[3];
  }

  i_max = static_cast<int>(NCTAB);
  MP_NCTAB.resize(  i_max);
  LIBF_NCTAB.resize(i_max);
  MATF_NCTAB.resize(i_max);
  MPF_NCTAB.resize( i_max);
  for(int i=0; i<i_max; i++)
  {
    mp_obj.read_cont(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3]);
    MP_NCTAB[i]   = i_vec[0];
    LIBF_NCTAB[i] = i_vec[1];
    MATF_NCTAB[i] = i_vec[2];
    MPF_NCTAB[i]  = i_vec[3];
  }
  r_vec.clear();
  i_vec.clear();

  mp_obj.line_no_check(text, line_no, mf_no, mt_no);

  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF30MT001Parser::clear()
{
  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);

  mat_no = unassigned_mat_no;
  ZA     = 0.0;
  AWR    = 0.0;
  NP     = 0;
  NDIR   = 0;
  NCTAB  = 0;

  MP_NDIR.clear();
  MFSEN_NDIR.clear();
  MTSEN_NDIR.clear();
  NC_NDIR.clear();

  MP_NCTAB.clear();
  LIBF_NCTAB.clear();
  MATF_NCTAB.clear();
  MPF_NCTAB.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF30MT001Parser::set_text(vector<string> text_data)
{
  clear();

  text = text_data;
  store_data();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string>  MF30MT001Parser::get_text()
{
  return text;
}

Integer         MF30MT001Parser::get_mat_no()
{
  return mat_no;
}

Integer         MF30MT001Parser::get_mt_no()
{
  return mt_no;
}


Real            MF30MT001Parser::get_ZA()
{
  return ZA;
}

Real            MF30MT001Parser::get_AWR()
{
  return AWR;
}

Integer         MF30MT001Parser::get_NP()
{
  return NP;
}

Integer         MF30MT001Parser::get_NDIR()
{
  return NDIR;
}

Integer         MF30MT001Parser::get_NCTAB()
{
  return NCTAB;
}


vector<Integer> MF30MT001Parser::get_MP_NDIR()
{
  return MP_NDIR;
}

vector<Integer> MF30MT001Parser::get_MFSEN_NDIR()
{
  return MFSEN_NDIR;
}

vector<Integer> MF30MT001Parser::get_MTSEN_NDIR()
{
  return MTSEN_NDIR;
}

vector<Integer> MF30MT001Parser::get_NC_NDIR()
{
  return NC_NDIR;
}


vector<Integer> MF30MT001Parser::get_MP_NCTAB()
{
  return MP_NCTAB;
}

vector<Integer> MF30MT001Parser::get_LIBF_NCTAB()
{
  return LIBF_NCTAB;
}

vector<Integer> MF30MT001Parser::get_MATF_NCTAB()
{
  return MATF_NCTAB;
}

vector<Integer> MF30MT001Parser::get_MPF_NCTAB()
{
  return MPF_NCTAB;
}


////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void MF30MT001Parser::set_mat_no(Integer& int_data)
{
  mat_no = int_data;
}

void MF30MT001Parser::set_ZA(Real& real_data)
{
  ZA = real_data;
}

void MF30MT001Parser::set_AWR(Real& real_data)
{
  AWR = real_data;
}

void MF30MT001Parser::set_NP(Integer& int_data)
{
  NP = int_data;
}

void MF30MT001Parser::set_NDIR(Integer& int_data)
{
  NDIR = int_data;
}

void MF30MT001Parser::set_NCTAB(Integer& int_data)
{
  NCTAB = int_data;
}

void MF30MT001Parser::set_MP_NDIR(vector<Integer>& int_vec)
{
  MP_NDIR = int_vec;
}

void MF30MT001Parser::set_MFSEN_NDIR(vector<Integer>& int_vec)
{
  MFSEN_NDIR = int_vec;
}

void MF30MT001Parser::set_MTSEN_NDIR(vector<Integer>& int_vec)
{
  MTSEN_NDIR = int_vec;
}

void MF30MT001Parser::set_NC_NDIR(vector<Integer>& int_vec)
{
  NC_NDIR = int_vec;
}

void MF30MT001Parser::set_MP_NCTAB(vector<Integer>& int_vec)
{
  MP_NCTAB = int_vec;
}

void MF30MT001Parser::set_LIBF_NCTAB(vector<Integer>& int_vec)
{
  LIBF_NCTAB = int_vec;
}

void MF30MT001Parser::set_MATF_NCTAB(vector<Integer>& int_vec)
{
  MATF_NCTAB = int_vec;
}

void MF30MT001Parser::set_MPF_NCTAB(vector<Integer>& int_vec)
{
  MPF_NCTAB = int_vec;
}

