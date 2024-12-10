#include "EndfUtils/MFxxMTyyyParser/MF01MT460Parser.hpp"

using namespace frendy;

//constructor
MF01MT460Parser::MF01MT460Parser(void)
{
  clear();

  err_obj.set_output_mode(err_obj.warning_off);
}

//destructor
MF01MT460Parser::~MF01MT460Parser(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF01MT460Parser::store_data()
{
  MultiParser mp_obj;

  //Text file data check
  if( static_cast<Integer>(text.size()) < 2 )
  {
    string class_name = "MF01MT460Parser";
    string func_name  = "store_data()";

    ostringstream oss;
    oss << static_cast<Integer>(text.size());
    string str_data = "Text line number : " + oss.str();

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("The text line number is not appropriate for  MF=01, MT=460.");
    err_com.push_back("The text line number should be larger than 1.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //Check MT and MF number
  if( mp_obj.check_mf_mt(text, mf_no, mt_no) != 0)
  {
    string class_name = "MF01MT460Parser";
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
    err_com.push_back("The MF and MT numbers are different to MF=01, MT=460.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  mp_obj.get_mat(text, mat_no);

  int     line_no = 0;
  Integer tmp_int;
  Real    tmp_real;

  //Line No.01
  //ZA, AWR, LO, NG
  mp_obj.read_head(text, line_no, ZA, AWR, LO, tmp_int, NG, tmp_int);

  if( LO == 1 )
  {
    E.resize(static_cast<int>(NG));
    for(int g=0; g<static_cast<int>(NG); g++)
    {
      vector<Integer> nbt_vec,  int_vec;
      vector<Real>    tint_vec, t_vec;
      Real            Energy;
      mp_obj.read_tab1(text, line_no, Energy, tmp_real, tmp_int, tmp_int, NR, NP,
                       nbt_vec, int_vec, tint_vec, t_vec);
      E[g] = Energy;

      if( g==0 )
      {
        NBT_MAP.resize(  static_cast<int>(NG));
        INT_MAP.resize(  static_cast<int>(NG));
        T_INT_MAP.resize(static_cast<int>(NG));
        T_MAP.resize(    static_cast<int>(NG));
      }
      NBT_MAP[g].resize(  static_cast<int>(NR));
      INT_MAP[g].resize(  static_cast<int>(NR));
      T_INT_MAP[g].resize(static_cast<int>(NP));
      T_MAP[g].resize(    static_cast<int>(NP));

      for(int i=0; i<static_cast<int>(NR); i++)
      {
        NBT_MAP[g][i] = nbt_vec[i];
        INT_MAP[g][i] = int_vec[i];
      }
      for(int i=0; i<static_cast<int>(NP); i++)
      {
        T_INT_MAP[g][i] = tint_vec[i];
        T_MAP[g][i]     = t_vec[i];
      }
    }
  }
  else if( LO == 2)
  {
    mp_obj.read_list(text, line_no, tmp_real, tmp_real, tmp_int, tmp_int, NNF, tmp_int, RAMDA);
  }

  mp_obj.line_no_check(text, line_no, mf_no, mt_no);

  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF01MT460Parser::clear()
{
  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);

  mat_no = unassigned_mat_no;
  ZA     = 0;
  AWR    = 0.0;
  LO     = 0;
  NG     = 0;
  NR     = 0;
  NP     = 0;
  NNF    = 0;

  E.clear();
  RAMDA.clear();

  clr_vec.clear_vec_array2_int(NBT_MAP);
  clr_vec.clear_vec_array2_int(INT_MAP);
  clr_vec.clear_vec_array2_real(T_INT_MAP);
  clr_vec.clear_vec_array2_real(T_MAP);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF01MT460Parser::set_text(vector<string> text_data)
{
  clear();

  text = text_data;
  store_data();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> MF01MT460Parser::get_text()
{
  return text;
}

Integer MF01MT460Parser::get_mat_no()
{
  return mat_no;
}

//Getter at line No.01
Real MF01MT460Parser::get_ZA()
{
  return ZA;
}

Real MF01MT460Parser::get_AWR()
{
  return AWR;
}

Integer MF01MT460Parser::get_LO()
{
  return LO;
}

Integer MF01MT460Parser::get_NG()
{
  return NG;
}

//Getter at line No.02
Integer MF01MT460Parser::get_NR()
{
  return NR;
}

Integer MF01MT460Parser::get_NP()
{
  return NP;
}

Integer MF01MT460Parser::get_NNF()
{
  return NNF;
}

vector<Real> MF01MT460Parser::get_E()
{
  return E;
}

vector<Real> MF01MT460Parser::get_RAMDA()
{
  return RAMDA;
}

vector<vector<Integer> > MF01MT460Parser::get_NBT_MAP()
{
  return NBT_MAP;
}

vector<vector<Integer> > MF01MT460Parser::get_INT_MAP()
{
  return INT_MAP;
}

vector<vector<Real> >    MF01MT460Parser::get_T_INT_MAP()
{
  return T_INT_MAP;
}

vector<vector<Real> >    MF01MT460Parser::get_T_MAP()
{
  return T_MAP;
}



////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void MF01MT460Parser::set_mat_no(Integer& int_data)
{
  mat_no = int_data;
}

void MF01MT460Parser::set_ZA(Real& real_data)
{
  ZA = real_data;
}

void MF01MT460Parser::set_AWR(Real& real_data)
{
  AWR = real_data;
}

void MF01MT460Parser::set_LO(Integer& int_data)
{
  LO = int_data;
}

void MF01MT460Parser::set_NG(Integer& int_data)
{
  NG = int_data;
}

void MF01MT460Parser::set_NR(Integer& int_data)
{
  NR = int_data;
}

void MF01MT460Parser::set_NP(Integer& int_data)
{
  NP = int_data;
}

void MF01MT460Parser::set_NNF(Integer& int_data)
{
  NNF = int_data;
}

void MF01MT460Parser::set_E(vector<Real>& real_vec)
{
  E = real_vec;
}

void MF01MT460Parser::set_RAMDA(vector<Real>& real_vec)
{
  RAMDA = real_vec;
}

void MF01MT460Parser::set_NBT_MAP(vector<vector<Integer> >& int_vec)
{
  NBT_MAP = int_vec;
}

void MF01MT460Parser::set_INT_MAP(vector<vector<Integer> >& int_vec)
{
  INT_MAP = int_vec;
}

void MF01MT460Parser::set_T_INT_MAP(vector<vector<Real> >& real_vec)
{
  T_INT_MAP = real_vec;
}

void MF01MT460Parser::set_T_MAP(vector<vector<Real> >& real_vec)
{
  T_MAP = real_vec;
}

