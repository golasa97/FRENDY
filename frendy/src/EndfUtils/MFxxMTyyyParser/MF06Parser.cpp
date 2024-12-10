#include "EndfUtils/MFxxMTyyyParser/MF06Parser.hpp"

using namespace frendy;

//constructor
MF06Parser::MF06Parser(void)
{
  clear();

  err_obj.set_output_mode(err_obj.warning_off);
}

//destructor
MF06Parser::~MF06Parser(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF06Parser::store_data()
{
  MultiParser mp_obj;

  //Text file data check
  if( static_cast<Integer>(text.size()) < 1 )
  {
    string class_name = "MF06Parser";
    string func_name  = "store_data()";

    ostringstream oss;
    oss << static_cast<Integer>(text.size());
    string str_data = "Text line number : " + oss.str();

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("The text line number is not appropriate for MF=06.");
    err_com.push_back("The text line number should be larger than 1.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //Check MF number
  if( mp_obj.check_mf(text, mf_no) != 0)
  {
    string class_name = "MF06Parser";
    string func_name  = "store_data()";

    ostringstream oss01;
    oss01 << mf_no;
    string str_data01 = "Text data at first line : " + text[0];
    string str_data02 = "File number (MF)        : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("The MF number is different to MF=06.");
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
  //ZA, AWR, LTT
  mp_obj.read_head(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3]);
  ZA  = r_vec[0];
  AWR = r_vec[1];
  LCT = i_vec[1];
  NK  = i_vec[2];

  set_JP(i_vec[0]);

  if( LCT == 5 || LCT == 6 || LCT == 7 )
  {
    store_thermal_scatter(mp_obj, line_no);
  }
  else if( LCT < 1 || LCT > 3 )
  {
    string class_name = "MF06Parser";
    string func_name  = "store_data()";

    ostringstream oss00, oss01;
    oss00 << mt_no;
    oss01 << LCT;
    string str_data00 = "Section number (MT) : " + oss00.str();
    string str_data01 = "LCT                 : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data00);
    err_com.push_back(str_data01);
    err_com.push_back("This LAW value at MF=06 is not supported in this program.");
    err_com.push_back("Supported LCT value is 1, 2 and 3.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  resize_matrix();

  for(int i=0; i<static_cast<int>(NK); i++)
  {
    //Line No.02
    //LF, p
    vector<Integer> nbt_vec, int_vec;
    vector<Real>    e_vec,   ap_vec;

    mp_obj.read_tab1(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                     nbt_vec, int_vec, e_vec, ap_vec);
    ZAP[i] = r_vec[0];
    AWP[i] = r_vec[1];
    LIP[i] = i_vec[0];
    LAW[i] = i_vec[1];

    if( (LAW[i] == 0 || LAW[i] == 1) && LIP[i] < 0 )
    {
      if( NK == 1 )
      {
        store_thermal_scatter_new_format(mp_obj, line_no, LAW[i], LIP[i]);
        continue;
      }
      else
      {
        string class_name = "MF06Parser";
        string func_name  = "store_data()";

        ostringstream oss00, oss01, oss02, oss03;
        oss00 << mt_no;
        oss01 << i+1;
        oss02 << NK;
        oss03 << LIP[i];
        string str_data00 = "Section number (MT) : " + oss00.str();
        string str_data01 = "Position            : " + oss01.str() + " / " + oss02.str();
        string str_data02 = "LIP                 : " + oss03.str();

        vector<string> err_com;
        err_com.push_back(str_data00);
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back("This LIP value at MF=06 is not supported in this program.");
        err_obj.output_runtime_error(class_name, func_name, err_com);
      }
    }

    NBT_Y[i]   = nbt_vec;
    INT_Y[i]   = int_vec;
    E_INT_Y[i] = e_vec;
    Y_TAB[i]   = ap_vec;
    e_vec.clear();
    ap_vec.clear();

    if( LAW[i] < 0 && JP > 0 )
    {
      //No LAW-dependent structure is given.
    }
    else if( LAW[i] == 0 )
    {
      //No LAW-dependent structure is given.
    }
    else if( LAW[i] == 1 )
    {
      store_law01(mp_obj, line_no, i);
    }
    else if( LAW[i] == 2 )
    {
      store_law02(mp_obj, line_no, i);
    }
    else if( LAW[i] == 3 )
    {
      //No LAW-dependent structure is given.
    }
    else if( LAW[i] == 4 )
    {
      //No LAW-dependent structure is given.
    }
    else if( LAW[i] == 5 )
    {
      store_law05(mp_obj, line_no, i);
    }
    else if( LAW[i] == 6 )
    {
      mp_obj.read_cont(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3]);
      APSX_LAW06[i] = r_vec[0];
      NPSX_LAW06[i] = i_vec[3];
    }
    else if( LAW[i] == 7 )
    {
      store_law07(mp_obj, line_no, i);
    }
    else
    {
      string class_name = "MF06Parser";
      string func_name  = "store_data()";

      ostringstream oss00, oss01, oss02, oss03, oss04;
      oss00 << mt_no;
      oss01 << JP;
      oss02 << i;
      oss03 << static_cast<int>(NK);
      oss04 << LAW[i];
      string str_data00 = "Section number (MT) : " + oss00.str();
      string str_data01 = "JP                  : " + oss01.str();
      string str_data02 = "NK                  : " + oss02.str() + " / " + oss03.str();
      string str_data03 = "LAW                 : " + oss04.str();

      vector<string> err_com;
      err_com.push_back(str_data00);
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back("This LAW value at MF=06 is not supported in this program.");
      err_com.push_back("Supported LAW value is 0 - 7 or LAW < 0 when JP > 0.");
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

void MF06Parser::store_law01(MultiParser& mp_obj, int& line_no, int& i)
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

  NBT_E[i] = nbt_vec;
  INT_E[i] = int_vec;
  nbt_vec.clear();
  int_vec.clear();

  int j_max = static_cast<int>(NE[i]);
  E1_LAW01[i].resize(j_max);
  ND_LAW01[i].resize(j_max);
  E2_LAW01[i].resize(j_max);
  B_LAW01[i].resize( j_max);
  for(int j=0; j<j_max; j++)
  {
    vector<Real> e_vec;
    mp_obj.read_list(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                     e_vec);
    E1_LAW01[i][j] = r_vec[1];
    ND_LAW01[i][j] = i_vec[0];

    int nd  = static_cast<int>(i_vec[0]);
    int na  = static_cast<int>(i_vec[1]);
    int nep = static_cast<int>(i_vec[3]);
    if( i_vec[2] != nep*(na+2) )
    {
      string class_name = "MF06Parser";
      string func_name  = "store_law01(MultiParser& mp_obj, int& line_no, int& i)";

      ostringstream oss00, oss01, oss02, oss03;
      oss00 << mt_no;
      oss01 << i_vec[2];
      oss02 << na;
      oss03 << nep;
      string str_data00 = "Section number (MT) : " + oss00.str();
      string str_data01 = "NEP*(NA+2)          : " + oss01.str();
      string str_data02 = "NA                  : " + oss02.str();
      string str_data03 = "NEP                 : " + oss03.str();

      vector<string> err_com;
      err_com.push_back(str_data00);
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
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

    if( nd > 0 && nd < nep )
    {
      for(int k=nd+1; k<nep; k++)
      {
        if( E2_LAW01[i][j][k] * (1.0 + min_ene_dif) < E2_LAW01[i][j][k-1] )
        {
          string class_name = "MF06Parser";
          string func_name  = "store_law01(MultiParser& mp_obj, int& line_no, int& i)";

          ostringstream oss00, oss01, oss02, oss03, oss04, oss05, oss06, oss07;
          oss06.precision(8);
          oss06.setf(ios::showpoint);
          oss06.setf(ios::scientific);
          oss07.precision(8);
          oss07.setf(ios::showpoint);
          oss07.setf(ios::scientific);
          oss00 << mt_no;
          oss01 << i+1;
          oss02 << j+1;
          oss03 << j_max;
          oss04 << k+1;
          oss05 << nep;
          oss06 << E2_LAW01[i][j][k-1];
          oss07 << E2_LAW01[i][j][k];
          string str_data00 = "Section number (MT) : " + oss00.str();
          string str_data01 = "Position i (NK)     : " + oss01.str();
          string str_data02 = "Position j (NE)     : " + oss02.str() + " / " + oss03.str();
          string str_data03 = "Position k (NEP)    : " + oss04.str() + " / " + oss05.str();
          string str_data04 = "E2_LAW01[i][j][k-1] : " + oss06.str();
          string str_data05 = "E2_LAW01[i][j][k]   : " + oss07.str();

          vector<string> err_com;
          err_com.push_back(str_data00);
          err_com.push_back(str_data01);
          err_com.push_back(str_data02);
          err_com.push_back(str_data03);
          err_com.push_back(str_data04);
          err_com.push_back(str_data05);
          err_com.push_back("E2_LAW01[i][j][k] is similar to E2_LAW01[i][j][k-1].");
          err_com.push_back("The energy grid of E2_LAW01 may not be not appropriate.");
          err_obj.output_caution(class_name, func_name, err_com);
          break;
        }
      }
    }
  }
  r_vec.clear();
  i_vec.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF06Parser::store_law02(MultiParser& mp_obj, int& line_no, int& i)
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
      string class_name = "MF06Parser";
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
        err_com.push_back("NW at LAW=2 is not equal to NL.");
      }
      else
      {
        err_com.push_back("NW at LAW=2 is not equal to 2*NL. Please check MF=06");
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

void MF06Parser::store_law05(MultiParser& mp_obj, int& line_no, int& i)
{
  vector<Real>    r_vec;
  vector<Integer> i_vec;
  r_vec.resize(6);
  i_vec.resize(6);

  vector<Integer> nbt_vec, int_vec;
  mp_obj.read_tab2(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                   nbt_vec, int_vec);

  SPI_LAW05[i]  = r_vec[0];
  LIDP_LAW05[i] = i_vec[0];
  NE[i]         = i_vec[3];

  NBT_E[i] = nbt_vec;
  INT_E[i] = int_vec;
  nbt_vec.clear();
  int_vec.clear();

  int j_max = static_cast<int>(NE[i]);
  E_LAW05[i].resize(  j_max);
  LTP_LAW05[i].resize(j_max);
  B_LAW05[i].resize(j_max);
  RA_LAW05[i].resize(j_max);
  IA_LAW05[i].resize(j_max);
  P_LAW05[i].resize(j_max);

  for(int j=0; j<j_max; j++)
  {
    vector<Real> e_vec;
    mp_obj.read_list(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                     e_vec);
    E_LAW05[i][j]   = r_vec[1];
    LTP_LAW05[i][j] = i_vec[0];

    int nl = static_cast<int>(i_vec[3]);

    string class_name = "MF06Parser";
    string func_name  = "store_law05(MultiParser& mp_obj, int& line_no, int& i)";

    ostringstream oss00, oss01, oss02, oss03, oss04, oss05, oss06, oss07, oss08;
    oss00 << mt_no;
    oss01 << i;
    oss02 << static_cast<int>(NK);
    oss03 << j;
    oss04 << j_max;
    oss05 << LTP_LAW05[i][j];
    oss06 << LIDP_LAW05[i];
    oss07 << i_vec[2];
    oss08 << nl;
    string str_data00 = "Section number (MT) : " + oss00.str();
    string str_data01 = "NK                  : " + oss01.str() + " / " + oss02.str();
    string str_data02 = "NE                  : " + oss03.str() + " / " + oss04.str();
    string str_data03 = "LTP                 : " + oss05.str();
    string str_data04 = "LIDP                : " + oss06.str();
    string str_data05 = "NW                  : " + oss07.str();
    string str_data06 = "NL                  : " + oss08.str();

    vector<string> err_com;
    err_com.push_back(str_data00);
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back(str_data05);
    err_com.push_back(str_data06);

    if( LTP_LAW05[i][j]==1 && LIDP_LAW05[i]==0 )
    {
      if( i_vec[2] != 4*nl+3 )
      {
        err_com.push_back("NW at LTP=1, LIDP=0, LAW=5 is not equal to 4*NL+3.");
        err_obj.output_runtime_error(class_name, func_name, err_com);
      }

      int k_max = nl+1;
      B_LAW05[i][j].resize(k_max+nl);
      RA_LAW05[i][j].resize(k_max);
      IA_LAW05[i][j].resize(k_max);
      int ele_no = 0;
      for(int k=0; k<k_max+nl; k++)
      {
        B_LAW05[i][j][k] = e_vec[ele_no];
        ele_no++;
      }
      for(int k=0; k<k_max; k++)
      {
        RA_LAW05[i][j][k] = e_vec[ele_no];
        ele_no++;
        IA_LAW05[i][j][k] = e_vec[ele_no];
        ele_no++;
      }
    }
    else if( LTP_LAW05[i][j]==1 && LIDP_LAW05[i]==1 )
    {
      if( i_vec[2] != 3*nl+3 )
      {
        err_com.push_back("NW at LTP=1, LIDP=1, LAW=5 is not equal to 3*NL+3.");
        err_obj.output_runtime_error(class_name, func_name, err_com);
      }

      int k_max = nl+1;
      B_LAW05[i][j].resize(k_max);
      RA_LAW05[i][j].resize(k_max);
      IA_LAW05[i][j].resize(k_max);
      for(int k=0; k<k_max; k++)
      {
        B_LAW05[i][j][k]  = e_vec[k];
        RA_LAW05[i][j][k] = e_vec[k_max + 2*k+0];
        IA_LAW05[i][j][k] = e_vec[k_max + 2*k+1];
      }
    }
    else if( LTP_LAW05[i][j]==2 )
    {
      if( i_vec[2] != nl+1 )
      {
        err_com.push_back("NW at LTP=2, LAW=5 is not equal to NL+1.");
        err_obj.output_runtime_error(class_name, func_name, err_com);
      }

      B_LAW05[i][j].resize(nl+1);
      for(int k=0; k<nl+1; k++)
      {
        B_LAW05[i][j][k] = e_vec[k]; //C -> B
      }
    }
    else if( LTP_LAW05[i][j]>2 )
    {
      if( i_vec[2] != 2*nl )
      {
        err_com.push_back("NW at LTP>2, LAW=5 is not equal to 2*NL.");
        err_obj.output_runtime_error(class_name, func_name, err_com);
      }

      B_LAW05[i][j].resize(nl);
      P_LAW05[i][j].resize(nl);
      for(int k=0; k<nl; k++)
      {
        B_LAW05[i][j][k] = e_vec[2*k+0]; //Mu -> B
        P_LAW05[i][j][k] = e_vec[2*k+1];
      }
    }
    else
    {
      err_com.push_back("These LIDP and LTP values at MF=06 are not supported in this program.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
    e_vec.clear();

    VectorClearer clr_vec;
    clr_vec.clear_vec_array1_str(err_com);
  }
  r_vec.clear();
  i_vec.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF06Parser::store_law07(MultiParser& mp_obj, int& line_no, int& i)
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
  E_LAW07[i].resize(      j_max);
  NMU_LAW07[i].resize(    j_max);
  NBT_MU_LAW07[i].resize( j_max);
  INT_MU_LAW07[i].resize( j_max);
  MU_LAW07[i].resize(     j_max);
  NBT_F_LAW07[i].resize(  j_max);
  INT_F_LAW07[i].resize(  j_max);
  E_INT_F_LAW07[i].resize(j_max);
  F_TAB_LAW07[i].resize(  j_max);

  for(int j=0; j<j_max; j++)
  {
    mp_obj.read_tab2(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                   nbt_vec, int_vec);
    E_LAW07[i][j]   = r_vec[1];
    NMU_LAW07[i][j] = i_vec[3];

    NBT_MU_LAW07[i][j] = nbt_vec;
    INT_MU_LAW07[i][j] = int_vec;
    nbt_vec.clear();
    int_vec.clear();

    int k_max = static_cast<int>(NMU_LAW07[i][j]);
    MU_LAW07[i][j].resize(     k_max);
    NBT_F_LAW07[i][j].resize(  k_max);
    INT_F_LAW07[i][j].resize(  k_max);
    E_INT_F_LAW07[i][j].resize(k_max);
    F_TAB_LAW07[i][j].resize(  k_max);

    for(int k=0; k<k_max; k++)
    {
      vector<Real> n_vec, e_vec;
      mp_obj.read_tab1(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                       nbt_vec, int_vec, e_vec, n_vec);

      MU_LAW07[i][j][k] = r_vec[1];

      NBT_F_LAW07[i][j][k]   = nbt_vec;
      INT_F_LAW07[i][j][k]   = int_vec;
      E_INT_F_LAW07[i][j][k] = e_vec;
      F_TAB_LAW07[i][j][k]   = n_vec;
      nbt_vec.clear();
      int_vec.clear();
      e_vec.clear();
      n_vec.clear();
    }
  }
  r_vec.clear();
  i_vec.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF06Parser::store_thermal_scatter(MultiParser& mp_obj, int& line_no)
{
  //This special format is used in the output of THERMR by NJOY99.

  if( LCT == 5 ) //For incoherent inelastic scatter cross section
  {
    store_incoherent_inelastic_scatter(mp_obj, line_no);
  }
  else if( LCT == 6 ) //For incoherent elastic scatter cross section
  {
    store_incoherent_elastic_scatter(mp_obj, line_no);
  }
  else //For coherent elastic scatter cross section
  {
    vector<Real>    r_vec;
    vector<Integer> i_vec;
    r_vec.resize(6);
    i_vec.resize(6);
    mp_obj.read_cont(text, line_no, TEMP, r_vec[1], i_vec[0], i_vec[1], i_vec[2], NBRAGG);
    r_vec.clear();
    i_vec.clear();
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF06Parser::store_thermal_scatter_new_format
                   ( MultiParser& mp_obj, int& line_no, Integer law_val, Integer ltt_val )
{
  //This special format is used in the output of THERMR by NJOY2012.

  clear_vec_data();

  if( law_val == 1 )
  {
    if( ltt_val == -1 ) //For incoherent inelastic scatter cross section
    {
      LCT = 5;
      store_incoherent_inelastic_scatter(mp_obj, line_no);
    }
    else if( ltt_val == -2 ) //For incoherent elastic scatter cross section
    {
      LCT = 6;
      store_incoherent_elastic_scatter(mp_obj, line_no);
    }
    else
    {
      string class_name = "MF06Parser";
      string func_name  = "store_thermal_scatter_new_format";

      ostringstream oss00, oss01;
      oss00 << mt_no;
      oss01 << ltt_val;
      string str_data00 = "Section number (MT) : " + oss00.str();
      string str_data01 = "LTT                 : " + oss01.str();

      vector<string> err_com;
      err_com.push_back(str_data00);
      err_com.push_back(str_data01);
      err_com.push_back("This LTT value at MF=06 is not supported in this program.");
      err_com.push_back("The appricable LTT value is as follows;");
      err_com.push_back("  -1 (for incoherent inelastic scattering)");
      err_com.push_back("  -2 (for incoherent elastic scattering)");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }
  else if( law_val == 0 )
  {
    LCT    =  7;
    NBRAGG = -1 * ltt_val;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF06Parser::store_incoherent_inelastic_scatter(MultiParser& mp_obj, int& line_no)
{
  vector<Real>    r_vec, e_vec;
  vector<Integer> i_vec, nbt_vec, int_vec;
  r_vec.resize(6);
  i_vec.resize(6);

  mp_obj.read_tab2(text, line_no, TEMP, r_vec[1], i_vec[0], i_vec[1], i_vec[2], NNE, nbt_vec, int_vec);
  for(int i=0; i<static_cast<int>(int_vec.size()); i++)
  {
    if( int_vec[i] != int_lin_lin )
    {
      string class_name = "MF06Parser";
      string func_name  = "store_incoherent_inelastic_scatter(MultiParser& mp_obj, int& line_no)";

      ostringstream oss00, oss01, oss02, oss03;
      oss00 << mt_no;
      oss01 << i;
      oss02 << static_cast<int>(int_vec.size());
      oss03 << int_vec[i];
      string str_data00 = "Section number (MT)   : " + oss00.str();
      string str_data01 = "Interpolation No.     : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "Interpolation scheme  : " + oss03.str();

      vector<string> err_com;
      err_com.push_back(str_data00);
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back("The appricable interpolation scheme is only linear-linear (2).");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }

  int i_max = static_cast<int>(NNE);
  EN.resize(i_max);
  EP.resize(i_max);
  PP.resize(i_max);
  EPM.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    mp_obj.read_list(text, line_no, r_vec[0], EN[i], i_vec[0], i_vec[1], i_vec[2], i_vec[3], e_vec);

    int j_max = static_cast<int>(i_vec[2]/i_vec[3]);
    int k_max = static_cast<int>(i_vec[3] - 2);
    if( i_vec[2]%i_vec[3] != 0 )
    {
      string class_name = "MF06Parser";
      string func_name  = "store_coherent_elastic_scatter(MultiParser& mp_obj, int& line_no)";

      ostringstream oss00, oss01, oss02, oss03, oss04;
      oss00 << mt_no;
      oss01 << i;
      oss02 << i_max;
      oss03 << i_vec[2];
      oss04 << i_vec[3];
      string str_data00 = "Section number (MT) : " + oss00.str();
      string str_data01 = "NNE                 : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "NEP*(NL+1)          : " + oss03.str();
      string str_data03 = "NL+1                : " + oss04.str();

      vector<string> err_com;
      err_com.push_back(str_data00);
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back("The remainder of NEP*(NL+1) / (NL+1) is not equal to 0.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    int ele_no = 0;
    EP[i].resize(j_max);
    PP[i].resize(j_max);
    EPM[i].resize(j_max);
    for(int j=0; j<j_max; j++)
    {
      EP[i][j] = e_vec[ele_no];
      PP[i][j] = e_vec[ele_no+1];

      ele_no += 2;
      EPM[i][j].resize(k_max);
      for(int k=0; k<k_max; k++)
      {
        EPM[i][j][k] = e_vec[ele_no];
        ele_no++;
      }
    }
    e_vec.clear();
  }
  r_vec.clear();
  i_vec.clear();
  nbt_vec.clear();
  int_vec.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF06Parser::store_incoherent_elastic_scatter(MultiParser& mp_obj, int& line_no)
{
  vector<Real>    r_vec, e_vec;
  vector<Integer> i_vec, nbt_vec, int_vec;
  r_vec.resize(6);
  i_vec.resize(6);

  mp_obj.read_tab2(text, line_no, TEMP, r_vec[1], i_vec[0], i_vec[1], i_vec[2], NNE, nbt_vec, int_vec);
  for(int i=0; i<static_cast<int>(int_vec.size()); i++)
  {
    if( int_vec[i] != int_lin_lin )
    {
      string class_name = "MF06Parser";
      string func_name  = "store_incoherent_elastic_scatter(MultiParser& mp_obj, int& line_no)";

      ostringstream oss00, oss01, oss02, oss03;
      oss00 << mt_no;
      oss01 << i;
      oss02 << static_cast<int>(int_vec.size());
      oss03 << int_vec[i];
      string str_data00 = "Section number (MT)   : " + oss00.str();
      string str_data01 = "Interpolation No.     : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "Interpolation scheme  : " + oss03.str();

      vector<string> err_com;
      err_com.push_back(str_data00);
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back("The appricable interpolation scheme is only linear-linear (2).");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }

  int i_max = static_cast<int>(NNE);
  EN.resize(i_max);
  U.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    mp_obj.read_list(text, line_no, r_vec[0], EN[i], i_vec[0], i_vec[1], i_vec[2], i_vec[3], e_vec);

    int j_max = static_cast<int>(e_vec.size());
    U[i].resize(j_max-2);
    for(int j=2; j<j_max; j++)
    {
      U[i][j-2] = e_vec[j];
    }
    e_vec.clear();
  }
  r_vec.clear();
  i_vec.clear();
  nbt_vec.clear();
  int_vec.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF06Parser::clear()
{
  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);

  mat_no = unassigned_mat_no;
  mt_no  = unassigned_mt_no;
  ZA     = 0.0;
  AWR    = 0.0;
  NK     = 0;

  JP     = 0;
  JPP    = 0;
  JPN    = 0;

  clear_vec_data();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF06Parser::clear_vec_data()
{
  VectorClearer clr_vec;

  ZAP.clear();
  AWP.clear();
  LIP.clear();
  LAW.clear();

  //Common data
  NE.clear();
  clr_vec.clear_vec_array2_int( NBT_Y);
  clr_vec.clear_vec_array2_int( INT_Y);
  clr_vec.clear_vec_array2_real(E_INT_Y);
  clr_vec.clear_vec_array2_real(Y_TAB);
  clr_vec.clear_vec_array2_int( NBT_E);
  clr_vec.clear_vec_array2_int( INT_E);

  //LAW = 1
  LANG_LAW01.clear();
  LEP_LAW01.clear();
  clr_vec.clear_vec_array2_real(E1_LAW01);
  clr_vec.clear_vec_array2_int( ND_LAW01);
  clr_vec.clear_vec_array3_real(E2_LAW01);
  clr_vec.clear_vec_array4_real(B_LAW01);

  //LAW = 2
  clr_vec.clear_vec_array2_real(E_LAW02);
  clr_vec.clear_vec_array2_int( LANG_LAW02);
  clr_vec.clear_vec_array2_int( NL_LAW02);
  clr_vec.clear_vec_array3_real(A_LAW02);

  //LAW = 5
  SPI_LAW05.clear();
  LIDP_LAW05.clear();
  clr_vec.clear_vec_array2_real(E_LAW05);
  clr_vec.clear_vec_array2_int( LTP_LAW05);
  clr_vec.clear_vec_array3_real(B_LAW05);
  clr_vec.clear_vec_array3_real(RA_LAW05);
  clr_vec.clear_vec_array3_real(IA_LAW05);
  clr_vec.clear_vec_array3_real(P_LAW05);

  //LAW = 6
  APSX_LAW06.clear();
  NPSX_LAW06.clear();

  //LAW = 7
  clr_vec.clear_vec_array2_real(E_LAW07);
  clr_vec.clear_vec_array2_int( NMU_LAW07);
  clr_vec.clear_vec_array3_int( NBT_MU_LAW07);
  clr_vec.clear_vec_array3_int( INT_MU_LAW07);
  clr_vec.clear_vec_array3_real(MU_LAW07);
  clr_vec.clear_vec_array4_int( NBT_F_LAW07);
  clr_vec.clear_vec_array4_int( INT_F_LAW07);
  clr_vec.clear_vec_array4_real(E_INT_F_LAW07);
  clr_vec.clear_vec_array4_real(F_TAB_LAW07);

  //For thermal scatter (LCT = 5-7 )
  NBRAGG = 0;
  NNE    = 0;
  TEMP   = 0.0;
  EN.clear();
  clr_vec.clear_vec_array2_real(EP);
  clr_vec.clear_vec_array2_real(PP);
  clr_vec.clear_vec_array2_real(U);
  clr_vec.clear_vec_array3_real(EPM);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MF06Parser::resize_matrix()
{
  int nk = static_cast<int>(NK);

  //Common data
  ZAP.resize(nk);
  AWP.resize(nk);
  LIP.resize(nk);
  LAW.resize(nk);

  NE.resize(nk);
  NBT_Y.resize(nk);
  INT_Y.resize(nk);
  E_INT_Y.resize(nk);
  Y_TAB.resize(nk);
  NBT_E.resize(nk);
  INT_E.resize(nk);

  //LAW = 1
  LANG_LAW01.resize(nk);
  LEP_LAW01.resize(nk);
  E1_LAW01.resize(nk);
  ND_LAW01.resize(nk);
  E2_LAW01.resize(nk);
  B_LAW01.resize(nk);

  //LAW = 2
  E_LAW02.resize(nk);
  LANG_LAW02.resize(nk);
  NL_LAW02.resize(nk);
  A_LAW02.resize(nk);

  //LAW = 5
  SPI_LAW05.resize(nk);
  LIDP_LAW05.resize(nk);
  E_LAW05.resize(nk);
  LTP_LAW05.resize(nk);
  B_LAW05.resize(nk);
  RA_LAW05.resize(nk);
  IA_LAW05.resize(nk);
  P_LAW05.resize(nk);

  //LAW = 6
  APSX_LAW06.resize(nk);
  NPSX_LAW06.resize(nk);

  //LAW = 7
  E_LAW07.resize(nk);
  NMU_LAW07.resize(nk);
  NBT_MU_LAW07.resize(nk);
  INT_MU_LAW07.resize(nk);
  MU_LAW07.resize(nk);
  NBT_F_LAW07.resize(nk);
  INT_F_LAW07.resize(nk);
  E_INT_F_LAW07.resize(nk);
  F_TAB_LAW07.resize(nk);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF06Parser::set_text(vector<string> text_data)
{
  clear();

  text = text_data;
  store_data();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string>                    MF06Parser::get_text()
{
  return text;
}

Integer                           MF06Parser::get_mat_no()
{
  return mat_no;
}

Integer                           MF06Parser::get_mt_no()
{
  return mt_no;
}

//Getter at line No.01-02
Real                              MF06Parser::get_ZA()
{
  return ZA;
}

Real                              MF06Parser::get_AWR()
{
  return AWR;
}

Integer                           MF06Parser::get_JP()
{
  JP = 10*JPP + JPN;
  return JP;
}

Integer                           MF06Parser::get_JPP()
{
  return JPP;
}

Integer                           MF06Parser::get_JPN()
{
  return JPN;
}

Integer                           MF06Parser::get_LCT()
{
  return LCT;
}

Integer                           MF06Parser::get_NK()
{
  return NK;
}

vector<Real>                      MF06Parser::get_ZAP()
{
  return ZAP;
}

vector<Real>                      MF06Parser::get_AWP()
{
  return AWP;
}

vector<Integer>                   MF06Parser::get_LIP()
{
  return LIP;
}

vector<Integer>                   MF06Parser::get_LAW()
{
  return LAW;
}

vector<vector<Integer> >          MF06Parser::get_NBT_Y()
{
  return NBT_Y;
}

vector<vector<Integer> >          MF06Parser::get_INT_Y()
{
  return INT_Y;
}

vector<vector<Real> >             MF06Parser::get_E_INT_Y()
{
  return E_INT_Y;
}

vector<vector<Real> >             MF06Parser::get_Y_TAB()
{
  return Y_TAB;
}


//LAW = 1
vector<Integer>                   MF06Parser::get_LANG_LAW01()
{
  return LANG_LAW01;
}

vector<Integer>                   MF06Parser::get_LEP_LAW01()
{
  return LEP_LAW01;
}

vector<Integer>                   MF06Parser::get_NE_LAW01()
{
  return NE;
}

vector<vector<Integer> >          MF06Parser::get_NBT_E_LAW01()
{
  return NBT_E;
}

vector<vector<Integer> >          MF06Parser::get_INT_E_LAW01()
{
  return INT_E;
}

vector<vector<Real> >             MF06Parser::get_E1_LAW01()
{
  return E1_LAW01;
}

vector<vector<Integer> >          MF06Parser::get_ND_LAW01()
{
  return ND_LAW01;
}

vector<vector<vector<Real> > >    MF06Parser::get_E2_LAW01()
{
  return E2_LAW01;
}

vector<vector<vector<vector<Real> > > > MF06Parser::get_B_LAW01()
{
  return B_LAW01;
}


//LAW = 2
vector<Integer>                   MF06Parser::get_NE_LAW02()
{
  return NE;
}

vector<vector<Integer> >          MF06Parser::get_NBT_E_LAW02()
{
  return NBT_E;
}

vector<vector<Integer> >          MF06Parser::get_INT_E_LAW02()
{
  return INT_E;
}

vector<vector<Real> >             MF06Parser::get_E_LAW02()
{
  return E_LAW02;
}

vector<vector<Integer> >          MF06Parser::get_LANG_LAW02()
{
  return LANG_LAW02;
}

vector<vector<Integer> >          MF06Parser::get_NL_LAW02()
{
  return NL_LAW02;
}

vector<vector<vector<Real> > >    MF06Parser::get_A_LAW02()
{
  return A_LAW02;
}


//LAW = 5
vector<Real>                      MF06Parser::get_SPI_LAW05()
{
  return SPI_LAW05;
}

vector<Integer>                   MF06Parser::get_LIDP_LAW05()
{
  return LIDP_LAW05;
}

vector<Integer>                   MF06Parser::get_NE_LAW05()
{
  return NE;
}

vector<vector<Integer> >          MF06Parser::get_NBT_E_LAW05()
{
  return NBT_E;
}

vector<vector<Integer> >          MF06Parser::get_INT_E_LAW05()
{
  return INT_E;
}

vector<vector<Real> >             MF06Parser::get_E_LAW05()
{
  return E_LAW05;
}

vector<vector<Integer> >          MF06Parser::get_LTP_LAW05()
{
  return LTP_LAW05;
}

vector<vector<vector<Real> > >    MF06Parser::get_B_LAW05()
{
  return B_LAW05;
}

vector<vector<vector<Real> > >    MF06Parser::get_RA_LAW05()
{
  return RA_LAW05;
}

vector<vector<vector<Real> > >    MF06Parser::get_IA_LAW05()
{
  return IA_LAW05;
}

vector<vector<vector<Real> > >    MF06Parser::get_C_LAW05()
{
  return B_LAW05;
}

vector<vector<vector<Real> > >    MF06Parser::get_MU_LAW05()
{
  return B_LAW05;
}

vector<vector<vector<Real> > >    MF06Parser::get_P_LAW05()
{
  return P_LAW05;
}


//LAW = 6
vector<Real>                      MF06Parser::get_APSX_LAW06()
{
  return APSX_LAW06;
}

vector<Integer>                   MF06Parser::get_NPSX_LAW06()
{
  return NPSX_LAW06;
}


//LAW = 7
vector<Integer>                   MF06Parser::get_NE_LAW07()
{
  return NE;
}

vector<vector<Integer> >          MF06Parser::get_NBT_E_LAW07()
{
  return NBT_E;
}

vector<vector<Integer> >          MF06Parser::get_INT_E_LAW07()
{
  return INT_E;
}

vector<vector<Real> >             MF06Parser::get_E_LAW07()
{
  return E_LAW07;
}

vector<vector<Integer> >          MF06Parser::get_NMU_LAW07()
{
  return NMU_LAW07;
}

vector<vector<vector<Integer> > > MF06Parser::get_NBT_MU_LAW07()
{
  return NBT_MU_LAW07;
}

vector<vector<vector<Integer> > > MF06Parser::get_INT_MU_LAW07()
{
  return INT_MU_LAW07;
}

vector<vector<vector<Real> > >    MF06Parser::get_MU_LAW07()
{
  return MU_LAW07;
}

vector<vector<vector<vector<Integer> > > > MF06Parser::get_NBT_F_LAW07()
{
  return NBT_F_LAW07;
}

vector<vector<vector<vector<Integer> > > > MF06Parser::get_INT_F_LAW07()
{
  return INT_F_LAW07;
}

vector<vector<vector<vector<Real> > > >    MF06Parser::get_E_INT_F_LAW07()
{
  return E_INT_F_LAW07;
}

vector<vector<vector<vector<Real> > > >    MF06Parser::get_F_TAB_LAW07()
{
  return F_TAB_LAW07;
}


//For thermal scatter (LCT = 5-7 )
Integer                        MF06Parser::get_NBRAGG()
{
  return NBRAGG;
}

Integer                        MF06Parser::get_NNE()
{
  return NNE;
}

Real                           MF06Parser::get_TEMP()
{
  return TEMP;
}

vector<vector<Real> >          MF06Parser::get_EP()
{
  return EP;
}

vector<vector<Real> >          MF06Parser::get_PP()
{
  return PP;
}

vector<vector<vector<Real> > > MF06Parser::get_EPM()
{
  return EPM;
}

vector<vector<Real> >          MF06Parser::get_U()
{
  return U;
}

vector<Real>                   MF06Parser::get_EN()
{
  return EN;
}


////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void MF06Parser::set_mat_no(Integer& int_data)
{
  mat_no = int_data;
}

void MF06Parser::set_mt_no(Integer& int_data)
{
  mt_no = int_data;
}

void MF06Parser::set_ZA(Real& real_data)
{
  ZA = real_data;
}

void MF06Parser::set_AWR(Real& real_data)
{
  AWR = real_data;
}

void MF06Parser::set_JP(Integer int_data)
{
  JP  = int_data;
  set_JPP(JP/10);
  set_JPN(JP%10);
}

void MF06Parser::set_JPP(Integer int_data)
{
  JPP = int_data;

  if( JPP != 0 && JPP != 1 && JPP != 2 )
  {
    string class_name = "MF06Parser";
    string func_name  = "set_JPP(Integer int_data)";

    ostringstream oss01, oss02;
    oss01 << JP;
    oss02 << JPP;
    string str_data01 = "JP  : " + oss01.str();
    string str_data02 = "JPP : " + oss02.str();

    vector<string> err_com;
    if( JPP > 0 )
    {
      err_com.push_back(str_data01);
    }
    err_com.push_back(str_data02);

    err_com.push_back("The available JPP value is 0, 1, and 2.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

void MF06Parser::set_JPN(Integer int_data)
{
  JPN = int_data;

  if( JPN != 0 && JPN != 1 && JPN != 2 )
  {
    string class_name = "MF06Parser";
    string func_name  = "set_JPN(Integer int_data)";

    ostringstream oss01, oss02;
    oss01 << JP;
    oss02 << JPN;
    string str_data01 = "JP  : " + oss01.str();
    string str_data02 = "JPN : " + oss02.str();

    vector<string> err_com;
    if( JPN > 0 )
    {
      err_com.push_back(str_data01);
    }
    err_com.push_back(str_data02);

    err_com.push_back("The available JPN value is 0, 1, and 2.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

void MF06Parser::set_LCT(Integer int_data)
{
  LCT = int_data;
}

void MF06Parser::set_NK(Integer int_data)
{
  NK = int_data;
}

void MF06Parser::set_ZAP(vector<Real>& real_vec)
{
  ZAP = real_vec;
}

void MF06Parser::set_AWP(vector<Real>& real_vec)
{
  AWP = real_vec;
}

void MF06Parser::set_LIP(vector<Integer>& int_vec)
{
  LIP = int_vec;
}

void MF06Parser::set_LAW(vector<Integer>& int_vec)
{
  LAW = int_vec;
}

void MF06Parser::set_NBT_Y(vector<vector<Integer> >& int_vec)
{
  NBT_Y = int_vec;
}

void MF06Parser::set_INT_Y(vector<vector<Integer> >& int_vec)
{
  INT_Y = int_vec;
}

void MF06Parser::set_E_INT_Y(vector<vector<Real> >& real_vec)
{
  E_INT_Y = real_vec;
}

void MF06Parser::set_Y_TAB(vector<vector<Real> >& real_vec)
{
  Y_TAB = real_vec;
}

void MF06Parser::set_LANG_LAW01(vector<Integer>& int_vec)
{
  LANG_LAW01 = int_vec;
}

void MF06Parser::set_LEP_LAW01(vector<Integer>& int_vec)
{
  LEP_LAW01 = int_vec;
}

void MF06Parser::set_NE_LAW01(vector<Integer>& int_vec)
{
  NE = int_vec;
}

void MF06Parser::set_NBT_E_LAW01(vector<vector<Integer> >& int_vec)
{
  NBT_E = int_vec;
}

void MF06Parser::set_INT_E_LAW01(vector<vector<Integer> >& int_vec)
{
  INT_E = int_vec;
}

void MF06Parser::set_E1_LAW01(vector<vector<Real> >& real_vec)
{
  E1_LAW01 = real_vec;
}

void MF06Parser::set_ND_LAW01(vector<vector<Integer> >& int_vec)
{
  ND_LAW01 = int_vec;
}

void MF06Parser::set_E2_LAW01(vector<vector<vector<Real> > >& real_vec)
{
  E2_LAW01 = real_vec;
}

void MF06Parser::set_B_LAW01(vector<vector<vector<vector<Real> > > >& real_vec)
{
  B_LAW01 = real_vec;
}

void MF06Parser::set_NE_LAW02(vector<Integer>& int_vec)
{
  NE = int_vec;
}

void MF06Parser::set_NBT_E_LAW02(vector<vector<Integer> >& int_vec)
{
  NBT_E = int_vec;
}

void MF06Parser::set_INT_E_LAW02(vector<vector<Integer> >& int_vec)
{
  INT_E = int_vec;
}

void MF06Parser::set_E_LAW02(vector<vector<Real> >& real_vec)
{
  E_LAW02 = real_vec;
}

void MF06Parser::set_LANG_LAW02(vector<vector<Integer> >& int_vec)
{
  LANG_LAW02 = int_vec;
}

void MF06Parser::set_NL_LAW02(vector<vector<Integer> >& int_vec)
{
  NL_LAW02 = int_vec;
}

void MF06Parser::set_A_LAW02(vector<vector<vector<Real> > >& real_vec)
{
  A_LAW02 = real_vec;
}

void MF06Parser::set_SPI_LAW05(vector<Real>& real_vec)
{
  SPI_LAW05 = real_vec;
}

void MF06Parser::set_LIDP_LAW05(vector<Integer>& int_vec)
{
  LIDP_LAW05 = int_vec;
}

void MF06Parser::set_NE_LAW05(vector<Integer>& int_vec)
{
  NE = int_vec;
}

void MF06Parser::set_NBT_E_LAW05(vector<vector<Integer> >& int_vec)
{
  NBT_E = int_vec;
}

void MF06Parser::set_INT_E_LAW05(vector<vector<Integer> >& int_vec)
{
  INT_E = int_vec;
}

void MF06Parser::set_E_LAW05(vector<vector<Real> >& real_vec)
{
  E_LAW05 = real_vec;
}

void MF06Parser::set_LTP_LAW05(vector<vector<Integer> >& int_vec)
{
  LTP_LAW05 = int_vec;
}

void MF06Parser::set_B_LAW05(vector<vector<vector<Real> > >& real_vec)
{
  B_LAW05 = real_vec;
}

void MF06Parser::set_RA_LAW05(vector<vector<vector<Real> > >& real_vec)
{
  RA_LAW05 = real_vec;
}

void MF06Parser::set_IA_LAW05(vector<vector<vector<Real> > >& real_vec)
{
  IA_LAW05 = real_vec;
}

void MF06Parser::set_C_LAW05(vector<vector<vector<Real> > >& real_vec)
{
  B_LAW05 = real_vec;
}

void MF06Parser::set_MU_LAW05(vector<vector<vector<Real> > >& real_vec)
{
  B_LAW05 = real_vec;
}

void MF06Parser::set_P_LAW05(vector<vector<vector<Real> > >& real_vec)
{
  P_LAW05 = real_vec;
}

void MF06Parser::set_APSX_LAW06(vector<Real>& real_vec)
{
  APSX_LAW06 = real_vec;
}

void MF06Parser::set_NPSX_LAW06(vector<Integer>& int_vec)
{
  NPSX_LAW06 = int_vec;
}

void MF06Parser::set_NE_LAW07(vector<Integer>& int_vec)
{
  NE = int_vec;
}

void MF06Parser::set_NBT_E_LAW07(vector<vector<Integer> >& int_vec)
{
  NBT_E = int_vec;
}

void MF06Parser::set_INT_E_LAW07(vector<vector<Integer> >& int_vec)
{
  INT_E = int_vec;
}

void MF06Parser::set_E_LAW07(vector<vector<Real> >& real_vec)
{
  E_LAW07 = real_vec;
}

void MF06Parser::set_NMU_LAW07(vector<vector<Integer> >& int_vec)
{
  NMU_LAW07 = int_vec;
}

void MF06Parser::set_NBT_MU_LAW07(vector<vector<vector<Integer> > >& int_vec)
{
  NBT_MU_LAW07 = int_vec;
}

void MF06Parser::set_INT_MU_LAW07(vector<vector<vector<Integer> > >& int_vec)
{
  INT_MU_LAW07 = int_vec;
}

void MF06Parser::set_MU_LAW07(vector<vector<vector<Real> > >& real_vec)
{
  MU_LAW07 = real_vec;
}

void MF06Parser::set_NBT_F_LAW07(vector<vector<vector<vector<Integer> > > >& int_vec)
{
  NBT_F_LAW07 = int_vec;
}

void MF06Parser::set_INT_F_LAW07(vector<vector<vector<vector<Integer> > > >& int_vec)
{
  INT_F_LAW07 = int_vec;
}

void MF06Parser::set_E_INT_F_LAW07(vector<vector<vector<vector<Real> > > >& real_vec)
{
  E_INT_F_LAW07 = real_vec;
}

void MF06Parser::set_F_TAB_LAW07(vector<vector<vector<vector<Real> > > >& real_vec)
{
  F_TAB_LAW07 = real_vec;
}

void MF06Parser::set_NBRAGG(Integer& int_data)
{
  NBRAGG = int_data;
}

void MF06Parser::set_NNE(Integer& int_data)
{
  NNE = int_data;
}

void MF06Parser::set_TEMP(Real& real_data)
{
  TEMP = real_data;
}

void MF06Parser::set_EP(vector<vector<Real> >& real_vec)
{
  EP = real_vec;
}

void MF06Parser::set_PP(vector<vector<Real> >& real_vec)
{
  PP = real_vec;
}

void MF06Parser::set_EPM(vector<vector<vector<Real> > >& real_vec)
{
  EPM = real_vec;
}

void MF06Parser::set_EN(vector<Real>& real_vec)
{
  EN = real_vec;
}

void MF06Parser::set_U(vector<vector<Real> >& real_vec)
{
  U = real_vec;
}

