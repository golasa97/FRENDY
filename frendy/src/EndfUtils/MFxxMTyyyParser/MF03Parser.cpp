#include "EndfUtils/MFxxMTyyyParser/MF03Parser.hpp"

using namespace frendy;

//constructor
MF03Parser::MF03Parser(void)
{
  clear();

  err_obj.set_output_mode(err_obj.warning_off);
}

//destructor
MF03Parser::~MF03Parser(void)
{ 
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF03Parser::store_data() 
{
  MultiParser mp_obj;

  //Text file data check
  if( static_cast<Integer>(text.size()) < 2 )
  {
    string class_name = "MF03Parser";
    string func_name  = "store_data()";

    ostringstream oss;
    oss << static_cast<Integer>(text.size());
    string str_data = "Text line number : " + oss.str();

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("The text line number is not appropriate for MF=03.");
    err_com.push_back("The text line number should be larger than 1.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //Check MF number
  if( mp_obj.check_mf(text, mf_no) != 0)
  {
    string class_name = "MF03Parser";
    string func_name  = "store_data()";

    ostringstream oss01;
    oss01 << mf_no;
    string str_data01 = "Text data at first line : " + text[0];
    string str_data02 = "File number (MF)        : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("The MF number is different to MF=03.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  mp_obj.get_mat(text, mat_no);

  int     line_no = 0;
  Integer tmp_int;

  //Get MT number
  mp_obj.get_mf_mt(text, tmp_int, mt_no);

  //Line No.01
  //ZA, AWR
  mp_obj.read_head(text, line_no, ZA, AWR, tmp_int, tmp_int, tmp_int, tmp_int);

  vector<Integer> nbt_vec, int_vec;
  vector<Real>    e_vec,   sig_vec;
  nbt_vec.clear();
  int_vec.clear();
  e_vec.clear();
  sig_vec.clear();

  //Line No.02
  //QM, QI, LR and sigma
  Integer NR, NP;
  mp_obj.read_tab1(text, line_no, QM, QI, tmp_int, LR, NR, NP, NBT_SIG, INT_SIG, E_INT_SIG, SIG_TAB);

  int i_max = static_cast<int>(E_INT_SIG.size());
  if( static_cast<int>(E_INT_SIG.size()) > 0 && QI < 0.0 )
  {
    Real ene_min = 0.0;
    for(int i=0; i<i_max-1; i++)
    {
      if( SIG_TAB[i+1] > min_value )
      {
        ene_min = E_INT_SIG[i];
        break;
      }
    }

    if( ene_min < fabs(QI) )
    {
      string class_name = "MF03Parser";
      string func_name  = "store_data()";

      ostringstream oss01, oss02, oss03, oss04;
      oss01 << mt_no;
      oss02 << QI;
      oss03 << E_INT_SIG[0];
      string str_data01 = "Reaction type (MT)    : " + oss01.str();
      string str_data02 = "Reaction Q value (QI) : " + oss02.str();
      string str_data03 = "Lowest energy         : " + oss03.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back("The Q value is larger than the lowest energy.");
      err_com.push_back("The Q value or cross section data may not be appropriate.");

      err_obj.output_caution(class_name, func_name, err_com);
    }
  }

  mp_obj.line_no_check(text, line_no, mf_no, mt_no);

  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF03Parser::clear()
{
  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);

  mat_no = unassigned_mat_no;
  mt_no  = unassigned_mt_no;
  ZA     = 0;
  AWR    = 0.0;
  QM     = 0.0;
  QI     = 0.0;
  LR     = 0;

//  comment.clear();
  NBT_SIG.clear();
  INT_SIG.clear();
  E_INT_SIG.clear();
  SIG_TAB.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF03Parser::set_text(vector<string> text_data)
{
  clear();

  text = text_data;
  store_data();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string>  MF03Parser::get_text()
{
  return text;
}

Integer         MF03Parser::get_mat_no()
{
  return mat_no;
}

Integer         MF03Parser::get_mt_no()
{
  return mt_no;
}

//Getter at line No.01
Real            MF03Parser::get_ZA()
{
  return ZA;
}

Real            MF03Parser::get_AWR()
{
  return AWR;
}

//Getter at line No.02
Real            MF03Parser::get_QM()
{
  return QM;
}

Real            MF03Parser::get_QI()
{
  return QI;
}

Integer         MF03Parser::get_LR()
{
  return LR;
}

vector<Integer> MF03Parser::get_NBT_SIG()
{
  return NBT_SIG;
}

vector<Integer> MF03Parser::get_INT_SIG()
{
  return INT_SIG;
}

vector<Real>    MF03Parser::get_E_INT_SIG()
{
  return E_INT_SIG;
}

vector<Real>    MF03Parser::get_SIG_TAB()
{
  return SIG_TAB;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void MF03Parser::set_mat_no(Integer& int_no)
{
  mat_no = int_no;
}

void MF03Parser::set_mt_no(Integer& int_no)
{
  mt_no = int_no;
}

//line No.01
void MF03Parser::set_ZA(Real& real_data)
{
  ZA = real_data;
}

void MF03Parser::set_AWR(Real& real_data)
{
  AWR = real_data;
}

//line No.02
void MF03Parser::set_QM(Real& real_data)
{
  QM = real_data;
}

void MF03Parser::set_QI(Real& real_data)
{
  QI = real_data;
}

void MF03Parser::set_LR(Integer& int_data)
{
  LR = int_data;
}

void MF03Parser::set_NBT_SIG(vector<Integer>& int_vec)
{
  NBT_SIG = int_vec;
}

void MF03Parser::set_INT_SIG(vector<Integer>& int_vec)
{
  INT_SIG = int_vec;
}

void MF03Parser::set_E_INT_SIG(vector<Real>& real_vec)
{
  E_INT_SIG = real_vec;
}

void MF03Parser::set_SIG_TAB(vector<Real>& real_vec)
{
  SIG_TAB = real_vec;
}

