#include "EndfUtils/MFxxMTyyyParser/MF26Parser.hpp"

using namespace frendy;

//constructor
MF26Parser::MF26Parser(void)
{
  clear();

  err_obj.set_output_mode(err_obj.warning_off);
}

//destructor
MF26Parser::~MF26Parser(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF26Parser::store_data()
{
  MultiParser mp_obj;

  //Text file data check
  if( static_cast<Integer>(text.size()) < 2 )
  {
    string class_name = "MF26Parser";
    string func_name  = "store_data()";

    ostringstream oss;
    oss << static_cast<Integer>(text.size());
    string str_data = "Text line number : " + oss.str();

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("The text line number is not appropriate for MF=26.");
    err_com.push_back("The text line number should be larger than 1.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //Check MF number
  if( mp_obj.check_mf(text, mf_no) != 0)
  {
    string class_name = "MF26Parser";
    string func_name  = "store_data()";

    ostringstream oss01;
    oss01 << mf_no;
    string str_data01 = "Text data at first line : " + text[0];
    string str_data02 = "File number (MF)        : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("The MF number is different to MF=26.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  mp_obj.get_mat(text, mat_no);

  int             line_no = 0;
  vector<Real>    r_vec;
  vector<Integer> i_vec;
  r_vec.resize(6);
  i_vec.resize(6);

  //Get MT number
  mp_obj.get_mf_mt(text, i_vec[0], mt_no);

  //Line No.01
  //ZA, AWR, NK
  mp_obj.read_head(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3]);
  ZA  = r_vec[0];
  AWR = r_vec[1];
  NK  = i_vec[2];

  int i_max = static_cast<int>(NK);
  resize_matrix(i_max);

  for( int i=0; i<i_max; i++)
  {
    vector<Integer> nbt_vec, int_vec;
    vector<Real>    e_vec,   y_vec;
    mp_obj.read_tab1(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                     nbt_vec, int_vec, e_vec, y_vec);
    ZAP[i] = r_vec[0];
    LAW[i] = i_vec[1];

    NBT_Y[i]   = nbt_vec;
    INT_Y[i]   = int_vec;
    E_INT_Y[i] = e_vec;
    Y_TAB[i]   = y_vec;
    nbt_vec.clear();
    int_vec.clear();
    e_vec.clear();
    y_vec.clear();

    if( LAW[i] == 1 )
    {
      store_law01(mp_obj, line_no, i);
    }
    else if( LAW[i] == 2 )
    {
      store_law02(mp_obj, line_no, i);
    }
    else if( LAW[i] == 8 )
    {
      store_law08(mp_obj, line_no, i);
    }
    else
    {
      string class_name = "MF26Parser";
      string func_name  = "store_data()";

      ostringstream oss00, oss01, oss02, oss03;
      oss00 << mt_no;
      oss01 << i;
      oss02 << static_cast<int>(NK);
      oss03 << LAW[i];
      string str_data00 = "Section number (MT) : " + oss00.str();
      string str_data01 = "NK                  : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "LAW                 : " + oss03.str();

      vector<string> err_com;
      err_com.push_back(str_data00);
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back("This LAW value at MF=26 is not supported in this program.");
      err_com.push_back("Supported LAW value is 1, 2 and 8.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }
  r_vec.clear();
  i_vec.clear();

  mp_obj.line_no_check(text, line_no, mf_no, mt_no);

  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF26Parser::store_law01(MultiParser& mp_obj, int& line_no, int& i)
{
  vector<Real>    r_vec;
  vector<Integer> i_vec;
  r_vec.resize(6);
  i_vec.resize(6);

  vector<Integer> nbt_vec, int_vec;
  mp_obj.read_tab2(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                   nbt_vec, int_vec);

  LANG_LAW01[i] = i_vec[0];
  LEP_LAW01[i]  = i_vec[1];
  NE[i]         = i_vec[3];

  NBT_E[i]   = nbt_vec;
  INT_E[i]   = int_vec;
  nbt_vec.clear();
  int_vec.clear();

  int ne = static_cast<int>(NE[i]);
  E1_LAW01[i].resize(ne);
  ND_LAW01[i].resize(ne);
  E2_LAW01[i].resize(ne);
  B_LAW01[i].resize( ne);

  for(int j=0; j<ne; j++)
  {
    vector<Real> e_vec;
    mp_obj.read_list(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                     e_vec);

    E1_LAW01[i][j] = r_vec[1];
    ND_LAW01[i][j] = i_vec[0];

    int na  = static_cast<int>(i_vec[1]);
    int nep = static_cast<int>(i_vec[3]);
    if( i_vec[2] != nep*(na+2) )
    {
      string class_name = "MF26Parser";
      string func_name  = "store_law01(MultiParser& mp_obj, int& line_no, int& i)";

      ostringstream oss00, oss01, oss02, oss03, oss04, oss05, oss06, oss07;
      oss00 << mt_no;
      oss01 << i;
      oss02 << static_cast<int>(NK);
      oss03 << j;
      oss04 << ne;
      oss05 << i_vec[2];
      oss06 << nep;
      oss07 << na;
      string str_data00 = "Section number (MT) : " + oss00.str();
      string str_data01 = "NK                  : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "NE                  : " + oss03.str() + " / " + oss04.str();
      string str_data03 = "NEP*(NA+2)          : " + oss05.str();
      string str_data04 = "NEP                 : " + oss06.str();
      string str_data05 = "NA                  : " + oss07.str();

      vector<string> err_com;
      err_com.push_back(str_data00);
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back(str_data04);
      err_com.push_back(str_data05);
      err_com.push_back("NW at LAW=1 is not qual to NEP*(NA+2).");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    E2_LAW01[i][j].resize(nep);
    B_LAW01[i][j].resize(nep);

    for(int k=0; k<nep; k++)
    {
      B_LAW01[i][j][k].resize(na+1);

      int ele_no = (na+2)*k;
      E2_LAW01[i][j][k] = e_vec[ele_no];

      for(int l=1; l<na+2; l++)
      {
        B_LAW01[i][j][k][l-1] = e_vec[ele_no+l];
      }
    }
    e_vec.clear();
  }
  r_vec.clear();
  i_vec.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF26Parser::store_law02(MultiParser& mp_obj, int& line_no, int& i)
{
  vector<Real>    r_vec;
  vector<Integer> i_vec;
  r_vec.resize(6);
  i_vec.resize(6);

  vector<Integer> nbt_vec, int_vec;
  mp_obj.read_tab2(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                   nbt_vec, int_vec);
  NE[i] = i_vec[3];

  NBT_E[i] = nbt_vec;
  INT_E[i] = int_vec;
  nbt_vec.clear();
  int_vec.clear();

  int j_max = static_cast<int>(NE[i]);
  E_LAW02[i].resize(j_max);
  LANG_LAW02[i].resize(j_max);
  NL_LAW02[i].resize(j_max);
  A_LAW02[i].resize(j_max);

  for(int j=0; j<j_max; j++)
  {
    vector<Real> e_vec;
    mp_obj.read_list(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                     e_vec);
    E_LAW02[i][j]    = r_vec[1];
    LANG_LAW02[i][j] = i_vec[0];
    NL_LAW02[i][j]   = i_vec[3];
    if( (LANG_LAW02[i][j] == 0 && i_vec[2] != i_vec[3]) || (LANG_LAW02[i][j] > 0 && i_vec[2] != i_vec[3]*2) )
    {
      string class_name = "MF26Parser";
      string func_name  = "store_law02(MultiParser& mp_obj, int& line_no, int& i)";

      ostringstream oss00, oss01, oss02, oss03, oss04, oss05, oss06, oss07;
      oss00 << mt_no;
      oss01 << i;
      oss02 << static_cast<int>(NK);
      oss03 << j;
      oss04 << j_max;
      oss05 << LANG_LAW02[i][j];
      oss06 << i_vec[2];
      oss07 << i_vec[3];
      string str_data00 = "Section number (MT) : " + oss00.str();
      string str_data01 = "NK                  : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "NE                  : " + oss03.str() + " / " + oss04.str();
      string str_data03 = "LANG                : " + oss05.str();
      string str_data04 = "NW                  : " + oss06.str();
      string str_data05 = "NL                  : " + oss07.str();

      vector<string> err_com;
      err_com.push_back(str_data00);
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back(str_data04);
      err_com.push_back(str_data05);

      if(LANG_LAW02[i][j] == 0 && i_vec[2] != i_vec[3])
      {
        err_com.push_back("NW at LAW=2 is not equal to NL. Please check MF=26");
      }
      else if(LANG_LAW02[i][j] > 0 && i_vec[2] != i_vec[3]*2)
      {
        err_com.push_back("NW at LAW=2 is not equal to 2*NL. Please check MF=26");
      }
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    A_LAW02[i][j] = e_vec;
    e_vec.clear();
  }
  r_vec.clear();
  i_vec.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF26Parser::store_law08(MultiParser& mp_obj, int& line_no, int& i)
{
  vector<Real>    r_vec;
  vector<Integer> i_vec;
  r_vec.resize(6);
  i_vec.resize(6);

  vector<Integer> nbt_vec, int_vec;
  vector<Real>    e_vec,   et_vec;
  mp_obj.read_tab1(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                   nbt_vec, int_vec, e_vec, et_vec);

  NBT_ET[i]   = nbt_vec;
  INT_ET[i]   = int_vec;
  E_INT_ET[i] = e_vec;
  ET_TAB[i]   = et_vec;
  nbt_vec.clear();
  int_vec.clear();
  e_vec.clear();
  et_vec.clear();

  r_vec.clear();
  i_vec.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF26Parser::clear()
{
  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);

  mat_no = unassigned_mat_no;
  mt_no  = unassigned_mt_no;
  ZA     = 0.0;
  NK     = 0;

  ZAP.clear();
  LAW.clear();

  clr_vec.clear_vec_array2_int( NBT_Y);
  clr_vec.clear_vec_array2_int( INT_Y);
  clr_vec.clear_vec_array2_real(E_INT_Y);
  clr_vec.clear_vec_array2_real(Y_TAB);

  LANG_LAW01.clear();
  LEP_LAW01.clear();
  NE.clear();
  clr_vec.clear_vec_array2_int( NBT_E);
  clr_vec.clear_vec_array2_int( INT_E);
  clr_vec.clear_vec_array2_real(E1_LAW01);
  clr_vec.clear_vec_array2_int( ND_LAW01);
  clr_vec.clear_vec_array3_real(E2_LAW01);
  clr_vec.clear_vec_array4_real(B_LAW01);

  clr_vec.clear_vec_array2_real(E_LAW02);
  clr_vec.clear_vec_array2_int( LANG_LAW02);
  clr_vec.clear_vec_array2_int( NL_LAW02);
  clr_vec.clear_vec_array3_real(A_LAW02);

  clr_vec.clear_vec_array2_int( NBT_ET);
  clr_vec.clear_vec_array2_int( INT_ET);
  clr_vec.clear_vec_array2_real(E_INT_ET);
  clr_vec.clear_vec_array2_real(ET_TAB);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF26Parser::resize_matrix(int i_max)
{
  ZAP.resize(i_max);
  LAW.resize(i_max);

  NBT_Y.resize(  i_max);
  INT_Y.resize(  i_max);
  E_INT_Y.resize(i_max);
  Y_TAB.resize(  i_max);

  LANG_LAW01.resize(i_max);
  LEP_LAW01.resize( i_max);
  NE.resize(i_max);

  NBT_E.resize(i_max);
  INT_E.resize(i_max);

  E1_LAW01.resize(i_max);
  ND_LAW01.resize(i_max);
  E2_LAW01.resize(i_max);
  B_LAW01.resize( i_max);

  E_LAW02.resize(   i_max);
  LANG_LAW02.resize(i_max);
  NL_LAW02.resize(  i_max);
  A_LAW02.resize(  i_max);

  NBT_ET.resize(  i_max);
  INT_ET.resize(  i_max);
  E_INT_ET.resize(i_max);
  ET_TAB.resize(  i_max);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF26Parser::set_text(vector<string> text_data)
{
  clear();

  text = text_data;
  store_data();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string>           MF26Parser::get_text()
{
  return text;
}

Integer                  MF26Parser::get_mat_no()
{
  return mat_no;
}

Integer                  MF26Parser::get_mt_no()
{
  return mt_no;
}

Real                     MF26Parser::get_ZA()
{
  return ZA;
}

Real                     MF26Parser::get_AWR()
{
  return AWR;
}

Integer                  MF26Parser::get_NK()
{
  return NK;
}

vector<Real>             MF26Parser::get_ZAP()
{
  return ZAP;
}

vector<Integer>          MF26Parser::get_LAW()
{
  return LAW;
}

vector<vector<Integer> > MF26Parser::get_NBT_Y()
{
  return NBT_Y;
}

vector<vector<Integer> > MF26Parser::get_INT_Y()
{
  return INT_Y;
}

vector<vector<Real> >    MF26Parser::get_E_INT_Y()
{
  return E_INT_Y;
}

vector<vector<Real> >    MF26Parser::get_Y_TAB()
{
  return Y_TAB;
}


vector<Integer>          MF26Parser::get_LANG_LAW01()
{
  return LANG_LAW01;
}

vector<Integer>          MF26Parser::get_LEP_LAW01()
{
  return LEP_LAW01;
}

vector<Integer>          MF26Parser::get_NE_LAW01()
{
  return NE;
}

vector<vector<Integer> > MF26Parser::get_NBT_E_LAW01()
{
  return NBT_E;
}

vector<vector<Integer> > MF26Parser::get_INT_E_LAW01()
{
  return INT_E;
}

vector<vector<Real> >    MF26Parser::get_E1_LAW01()
{
  return E1_LAW01;
}

vector<vector<Integer> > MF26Parser::get_ND_LAW01()
{
  return ND_LAW01;
}


vector<vector<vector<Real> > > MF26Parser::get_E2_LAW01()
{
  return E2_LAW01;
}

vector<vector<vector<vector<Real> > > > MF26Parser::get_B_LAW01()
{
  return B_LAW01;
}


vector<Integer>          MF26Parser::get_NE_LAW02()
{
  return NE;
}

vector<vector<Integer> > MF26Parser::get_NBT_E_LAW02()
{
  return NBT_E;
}

vector<vector<Integer> > MF26Parser::get_INT_E_LAW02()
{
  return INT_E;
}

vector<vector<Real> >    MF26Parser::get_E_LAW02()
{
  return E_LAW02;
}

vector<vector<Integer> > MF26Parser::get_LANG_LAW02()
{
  return LANG_LAW02;
}

vector<vector<Integer> > MF26Parser::get_NL_LAW02()
{
  return NL_LAW02;
}

vector<vector<vector<Real> > > MF26Parser::get_A_LAW02()
{
  return A_LAW02;
}


vector<vector<Integer> > MF26Parser::get_NBT_ET_LAW08()
{
  return NBT_ET;
}

vector<vector<Integer> > MF26Parser::get_INT_ET_LAW08()
{
  return INT_ET;
}

vector<vector<Real> >    MF26Parser::get_E_INT_ET_LAW08()
{
  return E_INT_ET;
}

vector<vector<Real> >    MF26Parser::get_ET_TAB_LAW08()
{
  return ET_TAB;
}


////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void MF26Parser::set_mat_no(Integer& int_data)
{
  mat_no = int_data;
}

void MF26Parser::set_mt_no(Integer& int_data)
{
  mt_no = int_data;
}

void MF26Parser::set_ZA(Real& real_data)
{
  ZA = real_data;
}

void MF26Parser::set_AWR(Real& real_data)
{
  AWR = real_data;
}

void MF26Parser::set_NK(Integer& int_data)
{
  NK = int_data;
}

void MF26Parser::set_ZAP(vector<Real>& real_vec)
{
  ZAP = real_vec;
}

void MF26Parser::set_LAW(vector<Integer>& int_vec)
{
  LAW = int_vec;
}

void MF26Parser::set_NBT_Y(vector<vector<Integer> >& int_vec)
{
  NBT_Y = int_vec;
}

void MF26Parser::set_INT_Y(vector<vector<Integer> >& int_vec)
{
  INT_Y = int_vec;
}

void MF26Parser::set_E_INT_Y(vector<vector<Real> >& real_vec)
{
  E_INT_Y = real_vec;
}

void MF26Parser::set_Y_TAB(vector<vector<Real> >& real_vec)
{
  Y_TAB = real_vec;
}

void MF26Parser::set_LANG_LAW01(vector<Integer>& int_vec)
{
  LANG_LAW01 = int_vec;
}

void MF26Parser::set_LEP_LAW01(vector<Integer>& int_vec)
{
  LEP_LAW01 = int_vec;
}

void MF26Parser::set_NE_LAW01(vector<Integer>& int_vec)
{
  NE = int_vec;
}

void MF26Parser::set_NBT_E_LAW01(vector<vector<Integer> >& int_vec)
{
  NBT_E = int_vec;
}

void MF26Parser::set_INT_E_LAW01(vector<vector<Integer> >& int_vec)
{
  INT_E = int_vec;
}

void MF26Parser::set_E1_LAW01(vector<vector<Real> >& real_vec)
{
  E1_LAW01 = real_vec;
}

void MF26Parser::set_ND_LAW01(vector<vector<Integer> >& int_vec)
{
  ND_LAW01 = int_vec;
}

void MF26Parser::set_E2_LAW01(vector<vector<vector<Real> > >& real_vec)
{
  E2_LAW01 = real_vec;
}

void MF26Parser::set_B_LAW01(vector<vector<vector<vector<Real> > > >& real_vec)
{
  B_LAW01 = real_vec;
}

void MF26Parser::set_NE_LAW02(vector<Integer>& int_vec)
{
  NE = int_vec;
}

void MF26Parser::set_NBT_E_LAW02(vector<vector<Integer> >& int_vec)
{
  NBT_E = int_vec;
}

void MF26Parser::set_INT_E_LAW02(vector<vector<Integer> >& int_vec)
{
  INT_E = int_vec;
}

void MF26Parser::set_E_LAW02(vector<vector<Real> >& real_vec)
{
  E_LAW02 = real_vec;
}

void MF26Parser::set_LANG_LAW02(vector<vector<Integer> >& int_vec)
{
  LANG_LAW02 = int_vec;
}

void MF26Parser::set_NL_LAW02(vector<vector<Integer> >& int_vec)
{
  NL_LAW02 = int_vec;
}

void MF26Parser::set_A_LAW02(vector<vector<vector<Real> > >& real_vec)
{
  A_LAW02 = real_vec;
}

void MF26Parser::set_NBT_ET_LAW08(vector<vector<Integer> >& int_vec)
{
  NBT_ET = int_vec;
}

void MF26Parser::set_INT_ET_LAW08(vector<vector<Integer> >& int_vec)
{
  INT_ET = int_vec;
}

void MF26Parser::set_E_INT_ET_LAW08(vector<vector<Real> >& real_vec)
{
  E_INT_ET = real_vec;
}

void MF26Parser::set_ET_TAB_LAW08(vector<vector<Real> >& real_vec)
{
  ET_TAB = real_vec;
}

