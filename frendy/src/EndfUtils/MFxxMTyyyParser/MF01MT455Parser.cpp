#include "EndfUtils/MFxxMTyyyParser/MF01MT455Parser.hpp"

using namespace frendy;

//constructor
MF01MT455Parser::MF01MT455Parser(void)
{
  clear();

  err_obj.set_output_mode(err_obj.warning_off);
}

//destructor
MF01MT455Parser::~MF01MT455Parser(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF01MT455Parser::store_data()
{
  MultiParser mp_obj;

  //Text file data check
  if( static_cast<Integer>(text.size()) < 2 )
  {
    string class_name = "MF01MT455Parser";
    string func_name  = "store_data()";

    ostringstream oss;
    oss << static_cast<Integer>(text.size());
    string str_data = "Text line number : " + oss.str();

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("The text line number is not appropriate for  MF=01, MT=455.");
    err_com.push_back("The text line number should be larger than 1.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //Check MT and MF number
  if( mp_obj.check_mf_mt(text, mf_no, mt_no) != 0)
  {
    string class_name = "MF01MT455Parser";
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
    err_com.push_back("The MF and MT numbers are different to MF=01, MT=455.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  mp_obj.get_mat(text, mat_no);

  int     line_no = 0;
  Integer tmp_int;
  Real    tmp_real;

  //Line No.01
  //ZA, AWR, LNU
  mp_obj.read_head(text, line_no, ZA, AWR, LDG, LNU, tmp_int, tmp_int);

  if( LDG == 0 )
  {
    mp_obj.read_list(text, line_no, tmp_real, tmp_real, tmp_int, tmp_int, NNF, tmp_int, RAMDA);
  }
  else if( LDG == 1 )
  {
    mp_obj.read_tab2(text, line_no, tmp_real, tmp_real, tmp_int, tmp_int, NR_E, NE_E, NBT_E, INT_E);
    E.resize(static_cast<int>(NE_E));
    for(int g=0; g<static_cast<int>(NE_E); g++)
    {
      vector<Real> real_vec;
      real_vec.clear();

      Real Energy;
      mp_obj.read_list(text, line_no, tmp_real, Energy, tmp_int, tmp_int, NNF, tmp_int, real_vec);
      E[g] = Energy;

      if( NNF % 2 != 0)
      {
        string class_name = "MF01MT455Parser";
        string func_name  = "store_data()";

        ostringstream oss01;
        oss01 << NNF;
        string str_data01 = "NNF : " + oss01.str();

        vector<string> err_com;
        err_com.push_back(str_data01);
        err_com.push_back("The number of NNF at LDG=1 must be multiple of 2.");

        err_obj.output_runtime_error(class_name, func_name, err_com);
      }

      NNF = NNF/2;
      if( g==0 )
      {
        RAMDA_MAP.resize(static_cast<int>(NE_E));
        ALPHA_MAP.resize(static_cast<int>(NE_E));
      }
      RAMDA_MAP[g].resize(static_cast<int>(NNF));
      ALPHA_MAP[g].resize(static_cast<int>(NNF));

      for(int i=0; i<static_cast<int>(NNF); i++)
      {
        RAMDA_MAP[g][i] = real_vec[i*2];
        ALPHA_MAP[g][i] = real_vec[i*2+1];
      }
    }
  }

  if( LNU == 1 )
  {
    mp_obj.read_list(text, line_no, tmp_real, tmp_real, tmp_int, tmp_int, NC, tmp_int, NU);
  }
  else if( LNU == 2 )
  {
    mp_obj.read_tab1(text, line_no, tmp_real, tmp_real, tmp_int, tmp_int,
                     NR_NU, NP_NU, NBT_NU, INT_NU, E_INT_NU, NU);
  }

  mp_obj.line_no_check(text, line_no, mf_no, mt_no);

  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF01MT455Parser::clear()
{
  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);

  mat_no = unassigned_mat_no;
  ZA     = 0;
  AWR    = 0.0;
  LDG    = 0;
  LNU    = 0;
  NC     = 0;
  NNF    = 0;
  NR_E   = 0;
  NE_E   = 0;
  NR_NU  = 0;
  NP_NU  = 0;

  RAMDA.clear();
  E.clear();
  NBT_E.clear();
  INT_E.clear();
  NBT_NU.clear();
  INT_NU.clear();
  E_INT_NU.clear();
  NU.clear();

  clr_vec.clear_vec_array2_real(RAMDA_MAP);
  clr_vec.clear_vec_array2_real(ALPHA_MAP);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF01MT455Parser::set_text(vector<string> text_data)
{
  clear();

  text = text_data;
  store_data();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> MF01MT455Parser::get_text()
{
  return text;
}

Integer MF01MT455Parser::get_mat_no()
{
  return mat_no;
}

//Getter at line No.01
Real MF01MT455Parser::get_ZA()
{
  return ZA;
}

Real MF01MT455Parser::get_AWR()
{
  return AWR;
}

Integer MF01MT455Parser::get_LDG()
{
  return LDG;
}

Integer MF01MT455Parser::get_LNU()
{
  return LNU;
}

//Getter at line No.02
Integer MF01MT455Parser::get_NC()
{
  return NC;
}

Integer MF01MT455Parser::get_NNF()
{
  return NNF;
}

Integer MF01MT455Parser::get_NR_E()
{
  return NR_E;
}

Integer MF01MT455Parser::get_NE_E()
{
  return NE_E;
}

Integer MF01MT455Parser::get_NP_NU()
{
  return NP_NU;
}

Integer MF01MT455Parser::get_NR_NU()
{
  return NR_NU;
}

vector<Real> MF01MT455Parser::get_RAMDA()
{
  return RAMDA;
}

vector<Real> MF01MT455Parser::get_E()
{
  return E;
}

vector<Integer> MF01MT455Parser::get_NBT_E()
{
  return NBT_E;
}

vector<Integer> MF01MT455Parser::get_INT_E()
{
  return INT_E;
}

vector<Integer> MF01MT455Parser::get_NBT_NU()
{
  return NBT_NU;
}

vector<Integer> MF01MT455Parser::get_INT_NU()
{
  return INT_NU;
}

vector<Real> MF01MT455Parser::get_E_INT_NU()
{
  return E_INT_NU;
}

vector<Real> MF01MT455Parser::get_NU()
{
  return NU;
}

vector<vector<Real> > MF01MT455Parser::get_ALPHA_MAP()
{
  return ALPHA_MAP;
}

vector<vector<Real> > MF01MT455Parser::get_RAMDA_MAP()
{
  return RAMDA_MAP;
}


////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void MF01MT455Parser::set_mat_no(Integer& int_data)
{
  mat_no = int_data;
}

void MF01MT455Parser::set_ZA(Real& real_data)
{
  ZA = real_data;
}

void MF01MT455Parser::set_AWR(Real& real_data)
{
  AWR = real_data;
}

void MF01MT455Parser::set_LDG(Integer& int_data)
{
  LDG = int_data;
}

void MF01MT455Parser::set_LNU(Integer& int_data)
{
  LNU = int_data;
}

void MF01MT455Parser::set_NC(Integer& int_data)
{
  NC = int_data;
}

void MF01MT455Parser::set_NNF(Integer& int_data)
{
  NNF = int_data;
}

void MF01MT455Parser::set_NR_E(Integer& int_data)
{
  NR_E = int_data;
}

void MF01MT455Parser::set_NE_E(Integer& int_data)
{
  NE_E = int_data;
}

void MF01MT455Parser::set_NR_NU(Integer& int_data)
{
  NR_NU = int_data;
}

void MF01MT455Parser::set_NP_NU(Integer& int_data)
{
  NP_NU = int_data;
}

void MF01MT455Parser::set_NBT_E(vector<Integer>& int_vec)
{
  NBT_E = int_vec;
}

void MF01MT455Parser::set_INT_E(vector<Integer>& int_vec)
{
  INT_E = int_vec;
}

void MF01MT455Parser::set_NBT_NU(vector<Integer>& int_vec)
{
  NBT_NU = int_vec;
}

void MF01MT455Parser::set_INT_NU(vector<Integer>& int_vec)
{
  INT_NU = int_vec;
}

void MF01MT455Parser::set_RAMDA(vector<Real>& real_vec)
{
  RAMDA = real_vec;
}

void MF01MT455Parser::set_E(vector<Real>& real_vec)
{
  E = real_vec;
}

void MF01MT455Parser::set_E_INT_NU(vector<Real>& real_vec)
{
  E_INT_NU = real_vec;
}

void MF01MT455Parser::set_NU(vector<Real>& real_vec)
{
  NU = real_vec;
}

void MF01MT455Parser::set_ALPHA_MAP(vector<vector<Real> >& real_vec)
{
  ALPHA_MAP = real_vec;
}

void MF01MT455Parser::set_RAMDA_MAP(vector<vector<Real> >& real_vec)
{
  RAMDA_MAP = real_vec;
}

