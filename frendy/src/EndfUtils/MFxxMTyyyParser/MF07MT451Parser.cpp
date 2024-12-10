#include "EndfUtils/MFxxMTyyyParser/MF07MT451Parser.hpp"

using namespace frendy;

//constructor
MF07MT451Parser::MF07MT451Parser(void)
{
  clear();

  err_obj.set_output_mode(err_obj.warning_off);
}

//destructor
MF07MT451Parser::~MF07MT451Parser(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF07MT451Parser::store_data()
{
  MultiParser mp_obj;

  //Text file data check
  if( static_cast<Integer>(text.size()) < 2 )
  {
    string class_name = "MF07MT451Parser";
    string func_name  = "store_data()";

    ostringstream oss;
    oss << static_cast<Integer>(text.size());
    string str_data = "Text line number : " + oss.str();

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("The text line number is not appropriate for MF=07, MT=451.");
    err_com.push_back("The text line number should be larger than 1.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //Check MT and MF number
  if( mp_obj.check_mf_mt(text, mf_no, mt_no) != 0)
  {
    string class_name = "MF07MT451Parser";
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
    err_com.push_back("The MF and MT numbers are different to MF=07, MT=451.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  mp_obj.get_mat(text, mat_no);

  int          line_no = 0;
  vector<Real> e_vec;
  Real         tmp_real;
  Integer      tmp_int;

  //Line No.01
  //ZA, AWR, NA
  mp_obj.read_head(text, line_no, ZA, AWR, NA, tmp_int, tmp_int, tmp_int);

  //NAS
  Integer e_vec_no = 0;
  mp_obj.read_list(text, line_no, tmp_real, tmp_real, NAS, tmp_int, e_vec_no, NI,
                   e_vec);

  if( e_vec_no != 6*NI )
  {
    string class_name = "MF07MT451Parser";
    string func_name  = "store_data()";

    ostringstream oss01, oss02;
    oss01 << e_vec_no;
    oss02 << NI;
    string str_data01 = "6*NI : " + oss01.str();
    string str_data02 = "NI   : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("6*NI must be multiples of 6.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  int i_max  = static_cast<int>(NI);
  ZAI.resize(i_max);
  AFI.resize(i_max);
  SFI.resize(i_max);
  AWRI.resize(i_max);
  LISI.resize(i_max);
  int ele_no = 0;
  for(int i=0; i<i_max; i++)
  {
    ZAI[i]  = e_vec[ele_no+0];
    LISI[i] = static_cast<int>(round(e_vec[ele_no+1]));
    AFI[i]  = e_vec[ele_no+2];
    AWRI[i] = e_vec[ele_no+3];
    SFI[i]  = e_vec[ele_no+4];
    ele_no += 6;
  }

  mp_obj.line_no_check(text, line_no, mf_no, mt_no);

  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF07MT451Parser::clear()
{
  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);

  mat_no = unassigned_mat_no;
  ZA     = 0.0;
  AWR    = 0.0;
  NA     = 0;
  NAS    = 0;
  NI     = 0;

  ZAI.clear();
  AFI.clear();
  SFI.clear();
  AWRI.clear();
  LISI.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF07MT451Parser::set_text(vector<string> text_data)
{
  clear();

  text = text_data;
  store_data();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> MF07MT451Parser::get_text()
{
  return text;
}

Integer MF07MT451Parser::get_mat_no()
{
  return mat_no;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Real                  MF07MT451Parser::get_ZA()
{
  return ZA;
}

Real                  MF07MT451Parser::get_AWR()
{
  return AWR;
}

Integer               MF07MT451Parser::get_NA()
{
  return NA;
}

Integer               MF07MT451Parser::get_NAS()
{
  return NAS;
}

Integer               MF07MT451Parser::get_NI()
{
  return NI;
}


vector<Real>          MF07MT451Parser::get_ZAI()
{
  return ZAI;
}

vector<Real>          MF07MT451Parser::get_AFI()
{
  return AFI;
}

vector<Real>          MF07MT451Parser::get_SFI()
{
  return SFI;
}

vector<Real>          MF07MT451Parser::get_AWRI()
{
  return AWRI;
}

vector<Integer>       MF07MT451Parser::get_LISI()
{
  return LISI;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void MF07MT451Parser::set_mat_no(Integer& int_data)
{
  mat_no = int_data;
}

void MF07MT451Parser::set_ZA(Real& real_data)
{
  ZA = real_data;
}

void MF07MT451Parser::set_AWR(Real& real_data)
{
  AWR = real_data;
}

void MF07MT451Parser::set_NA(Integer& int_data)
{
  NA = int_data;
}

void MF07MT451Parser::set_NAS(Integer& int_data)
{
  NAS = int_data;
}

void MF07MT451Parser::set_NI(Integer& int_data)
{
  NI = int_data;
}


void MF07MT451Parser::set_ZAI(vector<Real>& real_vec)
{
  ZAI = real_vec;
}

void MF07MT451Parser::set_AFI(vector<Real>& real_vec)
{
  AFI = real_vec;
}

void MF07MT451Parser::set_SFI(vector<Real>& real_vec)
{
  SFI = real_vec;
}

void MF07MT451Parser::set_AWRI(vector<Real>& real_vec)
{
  AWRI = real_vec;
}

void MF07MT451Parser::set_LISI(vector<Integer>& int_vec)
{
  LISI = int_vec;
}

