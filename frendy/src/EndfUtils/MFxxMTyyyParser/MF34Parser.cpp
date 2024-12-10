#include "EndfUtils/MFxxMTyyyParser/MF34Parser.hpp"

using namespace frendy;

//constructor
MF34Parser::MF34Parser(void)
{
  clear();

  err_obj.set_output_mode(err_obj.warning_off);
}

//destructor
MF34Parser::~MF34Parser(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF34Parser::store_data()
{
  MultiParser mp_obj;

  //Text file data check
  if( static_cast<Integer>(text.size()) < 1 )
  {
    string class_name = "MF34Parser";
    string func_name  = "store_data()";

    ostringstream oss;
    oss << static_cast<Integer>(text.size());
    string str_data = "Text line number : " + oss.str();

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("The text line number is not appropriate for MF=34.");
    err_com.push_back("The text line number should be larger than 1.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //Check MF number
  if( mp_obj.check_mf(text, mf_no) != 0)
  {
    string class_name = "MF34Parser";
    string func_name  = "store_data()";

    ostringstream oss01;
    oss01 << mf_no;
    string str_data01 = "Text data at first line : " + text[0];
    string str_data02 = "File number (MF)        : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("The MF number is different to MF=34.");

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
  //ZA, AWR, LTT, NMT1
  mp_obj.read_head(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3]);
  ZA   = r_vec[0];
  AWR  = r_vec[1];
  LTT  = i_vec[1];
  NMT1 = i_vec[3];

  int i_max = static_cast<int>(NMT1);
  resize_matrix_first(i_max);

  for(int i=0; i<i_max; i++)
  {
    mp_obj.read_cont(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3]);
    MAT1[i] = i_vec[0];
    MT1[i]  = i_vec[1];
    NL[i]   = i_vec[2];
    NL1[i]  = i_vec[3];

    mp_obj.read_cont(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3]);
    Integer L_first  = i_vec[0];
    Integer L1_first = i_vec[1];
    line_no--;

    int         j_max;
    vector<int> k_max;
    if( L1_first >= L_first )
    {
      NSS[i] = NL[i]*(NL[i]+1)/2;
      j_max =  static_cast<int>(NL[i]);
      k_max.resize(j_max);
      for(int j=0; j<j_max; j++)
      {
        k_max[j] = j_max - j;
      }
    }
    else
    {
      NSS[i] = NL[i]*NL1[i];
      j_max =  static_cast<int>(NL[i]);
      k_max.resize(j_max);
      for(int j=0; j<j_max; j++)
      {
        k_max[j] = static_cast<int>(NL1[i]);
      }
    }
    store_NSS(mp_obj, line_no, i, j_max, k_max);
  }
  r_vec.clear();
  i_vec.clear();

  mp_obj.line_no_check(text, line_no, mf_no, mt_no);

  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF34Parser::store_NSS(MultiParser& mp_obj, int& line_no, int& i, int& j_max, vector<int>& k_max)
{
  vector<Real>    r_vec;
  vector<Integer> i_vec;
  r_vec.resize(6);
  i_vec.resize(6);

  resize_matrix_second(i, j_max, k_max);

  for(int j=0; j<j_max; j++)
  {
    for(int k=0; k<k_max[j]; k++)
    {
      mp_obj.read_cont(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3]);
      L[i][j][k]   = i_vec[0];
      L1[i][j][k]  = i_vec[1];
      LCT[i][j][k] = i_vec[2];
      NI[i][j][k]  = i_vec[3];

      int l_max = static_cast<int>(i_vec[3]);
      resize_matrix_third(i, j, k, l_max);

      for(int l=0; l<l_max; l++)
      {
        vector<Real> e_vec;
        mp_obj.read_list(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                         e_vec);
        LS[i][j][k][l] = i_vec[0];
        LB[i][j][k][l] = i_vec[1];
        NT[i][j][k][l] = i_vec[2];
        NE[i][j][k][l] = i_vec[3];

        if( LB[i][j][k][l] == 0 || LB[i][j][k][l] == 1 || LB[i][j][k][l] == 2 )
        {
          store_lb00(e_vec, i, j, k, l);
        }
        else if( LB[i][j][k][l] == 5 )
        {
          store_lb05(e_vec, i, j, k, l);
        }
        else if( LB[i][j][k][l] == 6 )
        {
          store_lb06(e_vec, i, j, k, l);
        }
        else
        {
          string class_name = "MF34Parser";
          string func_name  = "store_NSS(MultiParser& mp_obj, int& line_no, ";
                 func_name += "int& i, int& j_max, vector<int>& k_max)";

          ostringstream oss00, oss01, oss02, oss03, oss04, oss05, oss06, oss07, oss08, oss09;
          oss00 << mt_no;
          oss01 << i;
          oss02 << static_cast<int>(NMT1);
          oss03 << j;
          oss04 << j_max;
          oss05 << k;
          oss06 << k_max[j];
          oss07 << l;
          oss08 << l_max;
          oss09 << LB[i][j][k][l];
          string str_data00 = "Section number (MT) : " + oss00.str();
          string str_data01 = "NNT1                : " + oss01.str() + " / " + oss02.str();
          string str_data02 = "J                   : " + oss03.str() + " / " + oss04.str();
          string str_data03 = "K                   : " + oss05.str() + " / " + oss06.str();
          string str_data04 = "L                   : " + oss07.str() + " / " + oss08.str();
          string str_data05 = "LB                  : " + oss09.str();

          vector<string> err_com;
          err_com.push_back(str_data00);
          err_com.push_back(str_data01);
          err_com.push_back(str_data02);
          err_com.push_back(str_data03);
          err_com.push_back(str_data04);
          err_com.push_back(str_data05);
          err_com.push_back("This LB value at MF=34 is not supported in this program.");
          err_com.push_back("Supported LB value is 0 - 2, 5 and 6.");

          err_obj.output_runtime_error(class_name, func_name, err_com);
        }
        e_vec.clear();
      }
    }
  }
  r_vec.clear();
  i_vec.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF34Parser::store_lb00(vector<Real>& e_vec, int& i, int& j, int& k, int& l)
{

  if( NT[i][j][k][l] != 2*NE[i][j][k][l] )
  {
    string class_name = "MF34Parser";
    string func_name  = "store_lb00(vector<Real>& e_vec, int& i, int& j, int& k, int& l)";

    ostringstream oss00, oss01, oss02, oss03, oss04, oss05, oss06, oss07;
    oss00 << mt_no;
    oss01 << i;
    oss02 << static_cast<int>(NMT1);
    oss03 << j;
    oss04 << k;
    oss05 << l;
    oss06 << NT[i][j][k][l];
    oss07 << NE[i][j][k][l];
    string str_data00 = "Section number (MT) : " + oss00.str();
    string str_data01 = "NNT1                : " + oss01.str() + " / " + oss02.str();
    string str_data02 = "J                   : " + oss03.str();
    string str_data03 = "K                   : " + oss04.str();
    string str_data04 = "L                   : " + oss05.str();
    string str_data05 = "NT=2*NE             : " + oss06.str();
    string str_data06 = "NE                  : " + oss07.str();

    vector<string> err_com;
    err_com.push_back(str_data00);
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back(str_data05);
    err_com.push_back(str_data06);
    err_com.push_back("NT is not equal to 2*NE at LB=0-2.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  int ls_m = static_cast<int>(NE[i][j][k][l] - LS[i][j][k][l]);
  E_K[i][j][k][l].resize(ls_m);
  F_K[i][j][k][l].resize(ls_m);
  E_T[i][j][k][l].resize(static_cast<int>(LS[i][j][k][l]));
  F_T[i][j][k][l].resize(static_cast<int>(LS[i][j][k][l]));
  for(int m=0; m<ls_m; m++)
  {
    E_K[i][j][k][l][m] =         e_vec[2*m];
    F_K[i][j][k][l][m].push_back(e_vec[2*m+1]);
  }
  for(int m=0; m<static_cast<int>(LS[i][j][k][l]); m++)
  {
    E_T[i][j][k][l][m] =         e_vec[2*ls_m+2*m];
    F_T[i][j][k][l][m].push_back(e_vec[2*ls_m+2*m+1]);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF34Parser::store_lb05(vector<Real>& e_vec, int& i, int& j, int& k, int& l)
{
  int ne = static_cast<int>(NE[i][j][k][l]);
  E_K[i][j][k][l].resize(ne);
  for(int m=0; m<ne; m++)
  {
    E_K[i][j][k][l][m] = e_vec[m];
  }

  if( LS[i][j][k][l] == 0 )
  {
    if( NT[i][j][k][l]!=ne*(ne-1)+1 )
    {
      string class_name = "MF34Parser";
      string func_name  = "store_lb05(vector<Real>& e_vec, int& i, int& j, int& k, int& l)";

      ostringstream oss00, oss01, oss02, oss03, oss04, oss05, oss06, oss07;
      oss00 << mt_no;
      oss01 << i;
      oss02 << static_cast<int>(NMT1);
      oss03 << j;
      oss04 << k;
      oss05 << l;
      oss06 << NT[i][j][k][l];
      oss07 << ne;
      string str_data00 = "Section number (MT) : " + oss00.str();
      string str_data01 = "NNT1                : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "J                   : " + oss03.str();
      string str_data03 = "K                   : " + oss04.str();
      string str_data04 = "L                   : " + oss05.str();
      string str_data05 = "NT=NE(NE-1)+1       : " + oss06.str();
      string str_data06 = "NE                  : " + oss07.str();

      vector<string> err_com;
      err_com.push_back(str_data00);
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back(str_data04);
      err_com.push_back(str_data05);
      err_com.push_back(str_data06);
      err_com.push_back("NT at LB=5, LS=0 is not equal to NE(NE-1)+1.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    int ele_no = ne;
    F_K[i][j][k][l].resize(ne-1);
    for(int m=0; m<ne-1; m++)
    {
      F_K[i][j][k][l][m].resize(ne-1);
      for(int n=0; n<ne-1; n++)
      {
        F_K[i][j][k][l][m][n] = e_vec[ele_no];
        ele_no++;
      }
    }
  }
  else if( LS[i][j][k][l]==1 )
  {
    if( NT[i][j][k][l]!=(ne*(ne+1))/2 )
    {
      string class_name = "MF34Parser";
      string func_name  = "store_lb05(vector<Real>& e_vec, int& i, int& j, int& k, int& l)";

      ostringstream oss00, oss01, oss02, oss03, oss04, oss05, oss06, oss07;
      oss00 << mt_no;
      oss01 << i;
      oss02 << static_cast<int>(NMT1);
      oss03 << j;
      oss04 << k;
      oss05 << l;
      oss06 << NT[i][j][k][l];
      oss07 << ne;
      string str_data00 = "Section number (MT) : " + oss00.str();
      string str_data01 = "NNT1                : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "J                   : " + oss03.str();
      string str_data03 = "K                   : " + oss04.str();
      string str_data04 = "L                   : " + oss05.str();
      string str_data05 = "NT=NE(NE+1)/2       : " + oss06.str();
      string str_data06 = "NE                  : " + oss07.str();

      vector<string> err_com;
      err_com.push_back(str_data00);
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back(str_data04);
      err_com.push_back(str_data05);
      err_com.push_back(str_data06);
      err_com.push_back("NT at LB=5, LS=1 is not equal to NE(NE+1)/2.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    int ele_no = ne;
    F_K[i][j][k][l].resize(ne-1);
    for(int m=0; m<ne-1; m++)
    {
      int ne_d = ne-1-m;
      F_K[i][j][k][l][m].resize(ne_d);
      for(int n=0; n<ne_d; n++)
      {
        F_K[i][j][k][l][m][n] = e_vec[ele_no];
        ele_no++;
      }
    }
  }
  else
  {
    string class_name = "MF34Parser";
    string func_name  = "store_lb05(vector<Real>& e_vec, int& i, int& j, int& k, int& l)";

    ostringstream oss00, oss01, oss02, oss03, oss04, oss05, oss06;
    oss00 << mt_no;
    oss01 << i;
    oss02 << static_cast<int>(NMT1);
    oss03 << j;
    oss04 << k;
    oss05 << l;
    oss06 << LS[i][j][k][l];
    string str_data00 = "Section number (MT) : " + oss00.str();
    string str_data01 = "NNT1                : " + oss01.str() + " / " + oss02.str();
    string str_data02 = "J                   : " + oss03.str();
    string str_data03 = "K                   : " + oss04.str();
    string str_data04 = "L                   : " + oss05.str();
    string str_data05 = "LS                  : " + oss06.str();

    vector<string> err_com;
    err_com.push_back(str_data00);
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back(str_data05);
    err_com.push_back("This LS value at MF=34 is not supported in this program.");
    err_com.push_back("Supported LS value is 0 and 1.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF34Parser::store_lb06(vector<Real>& e_vec, int& i, int& j, int& k, int& l)
{
  int ner =  NE[i][j][k][l];
  int nec = (NT[i][j][k][l] - 1)/ner;

  if( NT[i][j][k][l] != 1+ner*nec )
  {
    string class_name = "MF34Parser";
    string func_name  = "store_lb06(vector<Real>& e_vec, int& i, int& j, int& k, int& l)";

    ostringstream oss00, oss01, oss02, oss03, oss04, oss05, oss06, oss07, oss08;
    oss00 << mt_no;
    oss01 << i;
    oss02 << static_cast<int>(NMT1);
    oss03 << j;
    oss04 << k;
    oss05 << l;
    oss06 << NT[i][j][k][l];
    oss07 << ner;
    oss08 << nec;
    string str_data00 = "Section number (MT) : " + oss00.str();
    string str_data01 = "NNT1                : " + oss01.str() + " / " + oss02.str();
    string str_data02 = "J                   : " + oss03.str();
    string str_data03 = "K                   : " + oss04.str();
    string str_data04 = "L                   : " + oss05.str();
    string str_data05 = "NT=1+NER*NEC        : " + oss06.str();
    string str_data06 = "NER                 : " + oss07.str();
    string str_data07 = "NEC                 : " + oss08.str();

    vector<string> err_com;
    err_com.push_back(str_data00);
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back(str_data05);
    err_com.push_back(str_data06);
    err_com.push_back(str_data07);
    err_com.push_back("NT at LB=6 is not equal to 1+NER*NEC.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  int ele_no = 0;
  E_K[i][j][k][l].resize(ner);
  for(int m=0; m<ner; m++)
  {
    E_K[i][j][k][l][m] =  e_vec[ele_no];
    ele_no++;
  }
  E_T[i][j][k][l].resize(nec);
  for(int m=0; m<nec; m++)
  {
    E_T[i][j][k][l][m] =  e_vec[ele_no];
    ele_no++;
  }

  F_K[i][j][k][l].resize(ner-1);
  for(int m=0; m<ner-1; m++)
  {
    F_K[i][j][k][l][m].resize(nec-1);
    for(int n=0; n<nec-1; n++)
    {
      F_K[i][j][k][l][m][n] = e_vec[ele_no];
      ele_no++;
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF34Parser::clear()
{
  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);

  mat_no = unassigned_mat_no;
  mt_no  = unassigned_mt_no;
  ZA     = 0.0;
  AWR    = 0.0;
  LTT    = 0;
  NMT1   = 0;

  MAT1.clear();
  MT1.clear();
  NL.clear();
  NL1.clear();
  NSS.clear();

  clr_vec.clear_vec_array3_int(L);
  clr_vec.clear_vec_array3_int(L1);
  clr_vec.clear_vec_array3_int(LCT);
  clr_vec.clear_vec_array3_int(NI);
  clr_vec.clear_vec_array4_int(LS);
  clr_vec.clear_vec_array4_int(LB);
  clr_vec.clear_vec_array4_int(NT);
  clr_vec.clear_vec_array4_int(NE);

  clr_vec.clear_vec_array5_real(E_K);
  clr_vec.clear_vec_array5_real(E_T);
  clr_vec.clear_vec_array6_real(F_K);
  clr_vec.clear_vec_array6_real(F_T);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF34Parser::resize_matrix_first(int i_max)
{
  MAT1.resize(i_max);
  MT1.resize( i_max);
  NL.resize(  i_max);
  NL1.resize( i_max);

  NSS.resize(i_max);

  L.resize(  i_max);
  L1.resize( i_max);
  LCT.resize(i_max);
  NI.resize( i_max);

  LS.resize(i_max);
  LB.resize(i_max);
  NT.resize(i_max);
  NE.resize(i_max);

  E_K.resize(i_max);
  E_T.resize(i_max);
  F_K.resize(i_max);
  F_T.resize(i_max);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF34Parser::resize_matrix_second(int i, int j_max, vector<int> k_max)
{
  L[i].resize(  j_max);
  L1[i].resize( j_max);
  LCT[i].resize(j_max);
  NI[i].resize( j_max);

  LS[i].resize(j_max);
  LB[i].resize(j_max);
  NT[i].resize(j_max);
  NE[i].resize(j_max);

  E_K[i].resize(j_max);
  E_T[i].resize(j_max);
  F_K[i].resize(j_max);
  F_T[i].resize(j_max);

  for(int j=0; j<j_max; j++)
  {
    L[i][j].resize(  k_max[j]);
    L1[i][j].resize( k_max[j]);
    LCT[i][j].resize(k_max[j]);
    NI[i][j].resize( k_max[j]);

    LS[i][j].resize(k_max[j]);
    LB[i][j].resize(k_max[j]);
    NT[i][j].resize(k_max[j]);
    NE[i][j].resize(k_max[j]);

    E_K[i][j].resize(k_max[j]);
    E_T[i][j].resize(k_max[j]);
    F_K[i][j].resize(k_max[j]);
    F_T[i][j].resize(k_max[j]);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF34Parser::resize_matrix_third(int i, int j, int k, int l_max)
{
  LS[i][j][k].resize(l_max);
  LB[i][j][k].resize(l_max);
  NT[i][j][k].resize(l_max);
  NE[i][j][k].resize(l_max);

  E_K[i][j][k].resize(l_max);
  E_T[i][j][k].resize(l_max);
  F_K[i][j][k].resize(l_max);
  F_T[i][j][k].resize(l_max);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF34Parser::set_text(vector<string> text_data)
{
  clear();

  text = text_data;
  store_data();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string>                    MF34Parser::get_text()
{
  return text;
}

Integer                           MF34Parser::get_mat_no()
{
  return mat_no;
}

Integer                           MF34Parser::get_mt_no()
{
  return mt_no;
}

//Getter at line No.01-02
Real                              MF34Parser::get_ZA()
{
  return ZA;
}

Real                              MF34Parser::get_AWR()
{
  return AWR;
}

Integer                           MF34Parser::get_LTT()
{
  return LTT;
}

Integer                           MF34Parser::get_NMT1()
{
  return NMT1;
}

vector<Integer>                   MF34Parser::get_MAT1()
{
  return MAT1;
}

vector<Integer>                   MF34Parser::get_MT1()
{
  return MT1;
}

vector<Integer>                   MF34Parser::get_NL()
{
  return NL;
}

vector<Integer>                   MF34Parser::get_NL1()
{
  return NL1;
}


vector<Integer>                   MF34Parser::get_NSS()
{
  return NSS;
}


vector<vector<vector<Integer> > > MF34Parser::get_L()
{
  return L;
}

vector<vector<vector<Integer> > > MF34Parser::get_L1()
{
  return L1;
}

vector<vector<vector<Integer> > > MF34Parser::get_LCT()
{
  return LCT;
}

vector<vector<vector<Integer> > > MF34Parser::get_NI()
{
  return NI;
}

vector<vector<vector<vector<Integer> > > > MF34Parser::get_LS()
{
  return LS;
}

vector<vector<vector<vector<Integer> > > > MF34Parser::get_LB()
{
  return LB;
}

vector<vector<vector<vector<Integer> > > > MF34Parser::get_NT()
{
  return NT;
}

vector<vector<vector<vector<Integer> > > > MF34Parser::get_NE()
{
  return NE;
}


vector<vector<vector<vector<vector<Real> > > > >          MF34Parser::get_E_K()
{
  return E_K;
}

vector<vector<vector<vector<vector<Real> > > > >          MF34Parser::get_E_T()
{
  return E_T;
}

vector<vector<vector<vector<vector<vector<Real> > > > > > MF34Parser::get_F_K()
{
  return F_K;
}

vector<vector<vector<vector<vector<vector<Real> > > > > > MF34Parser::get_F_T()
{
  return F_T;
}


vector<vector<vector<vector<vector<Real> > > > >          MF34Parser::get_E_K_NER()
{
  return E_K;
}

vector<vector<vector<vector<vector<Real> > > > >          MF34Parser::get_E_K_NEC()
{
  return E_T;
}


////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void MF34Parser::set_mat_no(Integer& int_data)
{
  mat_no = int_data;
}

void MF34Parser::set_mt_no(Integer& int_data)
{
  mt_no = int_data;
}

void MF34Parser::set_ZA(Real& real_data)
{
  ZA = real_data;
}

void MF34Parser::set_AWR(Real& real_data)
{
  AWR = real_data;
}

void MF34Parser::set_LTT(Integer& int_data)
{
  LTT = int_data;
}

void MF34Parser::set_NMT1(Integer& int_data)
{
  NMT1 = int_data;
}

void MF34Parser::set_MAT1(vector<Integer>& int_vec)
{
  MAT1 = int_vec;
}

void MF34Parser::set_MT1(vector<Integer>& int_vec)
{
  MT1 = int_vec;
}

void MF34Parser::set_NL(vector<Integer>& int_vec)
{
  NL = int_vec;
}

void MF34Parser::set_NL1(vector<Integer>& int_vec)
{
  NL1 = int_vec;
}

void MF34Parser::set_NSS(vector<Integer>& int_vec)
{
  NSS = int_vec;
}

void MF34Parser::set_L(vector<vector<vector<Integer> > >& int_vec)
{
  L = int_vec;
}

void MF34Parser::set_L1(vector<vector<vector<Integer> > >& int_vec)
{
  L1 = int_vec;
}

void MF34Parser::set_LCT(vector<vector<vector<Integer> > >& int_vec)
{
  LCT = int_vec;
}

void MF34Parser::set_NI(vector<vector<vector<Integer> > >& int_vec)
{
  NI = int_vec;
}

void MF34Parser::set_LS(vector<vector<vector<vector<Integer> > > >& int_vec)
{
  LS = int_vec;
}

void MF34Parser::set_LB(vector<vector<vector<vector<Integer> > > >& int_vec)
{
  LB = int_vec;
}

void MF34Parser::set_NT(vector<vector<vector<vector<Integer> > > >& int_vec)
{
  NT = int_vec;
}

void MF34Parser::set_NE(vector<vector<vector<vector<Integer> > > >& int_vec)
{
  NE = int_vec;
}

void MF34Parser::set_E_K(vector<vector<vector<vector<vector<Real> > > > >& real_vec)
{
  E_K = real_vec;
}

void MF34Parser::set_E_T(vector<vector<vector<vector<vector<Real> > > > >& real_vec)
{
  E_T = real_vec;
}

void MF34Parser::set_F_K(vector<vector<vector<vector<vector<vector<Real> > > > > >& real_vec)
{
  F_K = real_vec;
}

void MF34Parser::set_F_T(vector<vector<vector<vector<vector<vector<Real> > > > > >& real_vec)
{
  F_T = real_vec;
}

void MF34Parser::set_E_K_NER(vector<vector<vector<vector<vector<Real> > > > >& real_vec)
{
  E_K = real_vec;
}

void MF34Parser::set_E_K_NEC(vector<vector<vector<vector<vector<Real> > > > >& real_vec)
{
  E_T = real_vec;
}

