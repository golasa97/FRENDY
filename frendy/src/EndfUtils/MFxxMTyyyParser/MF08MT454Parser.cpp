#include "EndfUtils/MFxxMTyyyParser/MF08MT454Parser.hpp"

using namespace frendy;

//constructor
MF08MT454Parser::MF08MT454Parser(void)
{
  clear();

  err_obj.set_output_mode(err_obj.warning_off);
}

//destructor
MF08MT454Parser::~MF08MT454Parser(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF08MT454Parser::store_data()
{
  MultiParser mp_obj;

  //Text file data check
  if( static_cast<Integer>(text.size()) < 2 )
  {
    string class_name = "MF08MT454Parser";
    string func_name  = "store_data()";

    ostringstream oss;
    oss << static_cast<Integer>(text.size());
    string str_data = "Text line number : " + oss.str();

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("The text line number is not appropriate for  MF=08, MT=454.");
    err_com.push_back("The text line number should be larger than 1.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //Check MF number
  if( mp_obj.check_mf(text, mf_no) != 0)
  {
    string class_name = "MF08MT454Parser";
    string func_name  = "store_data()";

    ostringstream oss01;
    oss01 << mf_no;
    string str_data01 = "Text data at first line : " + text[0];
    string str_data02 = "File number (MF)        : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("The MF and MT numbers are different to MF=08.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  mp_obj.get_mat(text, mat_no);

  int             line_no = 0;
  vector<Real>    r_vec;
  vector<Integer> i_vec;
  r_vec.resize(6);
  i_vec.resize(6);

  mp_obj.get_mf_mt(text, i_vec[0], mt_no);
  if( mt_no != 454 )
  {
    string class_name = "MF08MT454Parser";
    string func_name  = "store_data()";

    ostringstream oss01;
    oss01 << mt_no;
    string str_data01 = "Text data at first line : " + text[0];
    string str_data02 = "Section number (MT)     : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    if( mt_no == 457 )
    {
      err_com.push_back("This MT number is not supported in this class, please use MT08MF457Parser class.");
    }
    else if( mt_no == 459 )
    {
      err_com.push_back("This MT number is not supported in this class, please use MT08MF459Parser class.");
    }
    else
    {
      err_com.push_back("This MT number is not supported in this class, please use MT08Parser class.");
    }
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //Line No.01
  //ZA, AWR, LE
  mp_obj.read_head(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3]);
  ZA   = r_vec[0];
  AWR  = r_vec[1];
  LE   = i_vec[0] - 1;

  int i_max = static_cast<int>(LE+1);
  E.resize(i_max);
  I.resize(i_max);
  ZAFP.resize(i_max);
  FPS.resize( i_max);
  YI.resize(  i_max);
  DYI.resize( i_max);
  for(int i=0; i<i_max; i++)
  {
    vector<Real> e_vec;
    mp_obj.read_list(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                     e_vec);
    E[i] = r_vec[0];
    I[i] = i_vec[0];

    int j_max = static_cast<int>(e_vec.size())/4;
    ZAFP[i].resize(j_max);
    FPS[i].resize( j_max);
    YI[i].resize(  j_max);
    DYI[i].resize( j_max);
    for(int j=0; j<j_max; j++)
    {
    ZAFP[i][j] = e_vec[4*j+0];
    FPS[i][j]  = e_vec[4*j+1];
    YI[i][j]   = e_vec[4*j+2];
    DYI[i][j]  = e_vec[4*j+3];
    }
    e_vec.clear();
  }
  r_vec.clear();
  i_vec.clear();

  mp_obj.line_no_check(text, line_no, mf_no, mt_no);

  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF08MT454Parser::clear()
{
  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);

  mat_no = unassigned_mat_no;
  ZA     = 0.0;
  AWR    = 0.0;
  LE     = 0;

  E.clear();
  I.clear();

  clr_vec.clear_vec_array2_real(ZAFP);
  clr_vec.clear_vec_array2_real(FPS);
  clr_vec.clear_vec_array2_real(YI);
  clr_vec.clear_vec_array2_real(DYI);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF08MT454Parser::set_text(vector<string> text_data)
{
  clear();

  text = text_data;
  store_data();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string>        MF08MT454Parser::get_text()
{
  return text;
}

Integer               MF08MT454Parser::get_mat_no()
{
  return mat_no;
}

Integer               MF08MT454Parser::get_mt_no()
{
  return mt_no;
}


Real                  MF08MT454Parser::get_ZA()
{
  return ZA;
}

Real                  MF08MT454Parser::get_AWR()
{
  return AWR;
}

Integer               MF08MT454Parser::get_LE()
{
  return LE;
}

vector<Real>          MF08MT454Parser::get_E()
{
  return E;
}

vector<Integer>       MF08MT454Parser::get_I()
{
  return I;
}

vector<vector<Real> > MF08MT454Parser::get_ZAFP()
{
  return ZAFP;
}

vector<vector<Real> > MF08MT454Parser::get_FPS()
{
  return FPS;
}

vector<vector<Real> > MF08MT454Parser::get_YI()
{
  return YI;
}

vector<vector<Real> > MF08MT454Parser::get_DYI()
{
  return DYI;
}


////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void MF08MT454Parser::set_mat_no(Integer& int_data)
{
  mat_no = int_data;
}

void MF08MT454Parser::set_mt_no(Integer& int_data)
{
  mt_no = int_data;
}

void MF08MT454Parser::set_ZA(Real& real_data)
{
  ZA = real_data;
}

void MF08MT454Parser::set_AWR(Real& real_data)
{
  AWR = real_data;
}

void MF08MT454Parser::set_LE(Integer& int_data)
{
  LE = int_data;
}

void MF08MT454Parser::set_E(vector<Real>& real_vec)
{
  E = real_vec;
}

void MF08MT454Parser::set_I(vector<Integer>& int_vec)
{
  I = int_vec;
}

void MF08MT454Parser::set_ZAFP(vector<vector<Real> >& real_vec)
{
  ZAFP = real_vec;
}

void MF08MT454Parser::set_FPS(vector<vector<Real> >& real_vec)
{
  FPS = real_vec;
}

void MF08MT454Parser::set_YI(vector<vector<Real> >& real_vec)
{
  YI = real_vec;
}

void MF08MT454Parser::set_DYI(vector<vector<Real> >& real_vec)
{
  DYI = real_vec;
}

