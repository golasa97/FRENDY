#include "EndfUtils/MFxxMTyyyParser/MF33Parser.hpp"

using namespace frendy;

//constructor
MF33Parser::MF33Parser(void)
{
  clear();

  err_obj.set_output_mode(err_obj.warning_off);
}

//destructor
MF33Parser::~MF33Parser(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF33Parser::store_data()
{
  MultiParser mp_obj;

  //Text file data check
  if( static_cast<Integer>(text.size()) < 1 )
  {
    string class_name = "MF33Parser";
    string func_name  = "store_data()";

    ostringstream oss;
    oss << static_cast<Integer>(text.size());
    string str_data = "Text line number : " + oss.str();

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("The text line number is not appropriate for MF=33.");
    err_com.push_back("The text line number should be larger than 1.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //Check MF number
  if( mp_obj.check_mf(text, mf_no) != 0)
  {
    string class_name = "MF33Parser";
    string func_name  = "store_data()";

    ostringstream oss01;
    oss01 << mf_no;
    string str_data01 = "Text data at first line : " + text[0];
    string str_data02 = "File number (MF)        : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("The MF number is different to MF=33.");

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
  //ZA, AWR, MTL, NL
  mp_obj.read_head(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3]);
  ZA  = r_vec[0];
  AWR = r_vec[1];
  MTL = i_vec[1];
  NL  = i_vec[3];
  resize_matrix_NL();

  for(int i=0; i<static_cast<int>(NL); i++)
  {
    mp_obj.read_cont(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3]);
    XMF[i]  = r_vec[0];
    XLFS[i] = r_vec[1];
    MAT[i]  = i_vec[0];
    MT[i]   = i_vec[1];
    NC[i]   = i_vec[2];
    NI[i]   = i_vec[3];

    //NC-type Sub-Subsections
    if( NC[i] > 0 )
    {
      resize_matrix_NC(i);
      for(int j=0; j<static_cast<int>(NC[i]); j++)
      {
        store_NC(mp_obj, line_no, i, j);
      }
    }

    //NI-type Sub-Subsections
    if( NI[i] > 0 )
    {
      resize_matrix_NI(i);
      for(int j=0; j<static_cast<int>(NI[i]); j++)
      {
        store_NI(mp_obj, line_no, i, j);
      }
    }
  }
  r_vec.clear();
  i_vec.clear();

  mp_obj.line_no_check(text, line_no, mf_no, mt_no);

  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF33Parser::store_NC(MultiParser& mp_obj, int& line_no, int& i, int& j)
{
  vector<Real>    r_vec;
  vector<Integer> i_vec;
  r_vec.resize(6);
  i_vec.resize(6);

  mp_obj.read_cont(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3]);
  LTY[i][j] = i_vec[1];

  vector<Real> e_vec;
  mp_obj.read_list(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                   e_vec);
  E1[i][j] = r_vec[0];
  E2[i][j] = r_vec[1];

  if( LTY[i][j] == 0 )
  {
    if( i_vec[2]!=2*i_vec[3] )
    {
      string class_name = "MF33Parser";
      string func_name  = "store_NC(MultiParser& mp_obj, int& line_no, int& i, int& j)";

      ostringstream oss00, oss01, oss02, oss03, oss04, oss05, oss06;
      oss00 << mt_no;
      oss01 << i;
      oss02 << static_cast<int>(NL);
      oss03 << j;
      oss04 << static_cast<int>(NC[i]);
      oss05 << i_vec[2];
      oss06 << i_vec[3];
      string str_data00 = "Section number (MT) : " + oss00.str();
      string str_data01 = "NL                  : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "NC                  : " + oss03.str() + " / " + oss04.str();
      string str_data03 = "2*NCI               : " + oss05.str();
      string str_data04 = "NCI                 : " + oss06.str();

      vector<string> err_com;
      err_com.push_back(str_data00);
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back(str_data04);
      err_com.push_back("2*NCI at LTY=0 is not appropriate.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    int k_max = static_cast<int>(i_vec[3]);
    CI[i][j].resize(k_max);
    XMTI[i][j].resize(k_max);
    for(int k=0; k<k_max; k++)
    {
      CI[i][j][k]   = e_vec[2*k];
      XMTI[i][j][k] = e_vec[2*k+1];
    }
  }
  else if( LTY[i][j] == 1 || LTY[i][j] == 2 || LTY[i][j] == 3 )
  {
    MATS[i][j] = i_vec[0];
    MTS[i][j]  = i_vec[1];

    if( i_vec[2]!=2*i_vec[3]+2 )
    {
      string class_name = "MF33Parser";
      string func_name  = "store_NC(MultiParser& mp_obj, int& line_no, int& i, int& j)";

      ostringstream oss00, oss01, oss02, oss03, oss04;
      oss00 << mt_no;
      oss01 << i;
      oss02 << static_cast<int>(NL);
      oss03 << j;
      oss04 << static_cast<int>(NC[i]);
      string str_data00 = "Section number (MT) : " + oss00.str();
      string str_data01 = "NL                  : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "NC                  : " + oss03.str() + " / " + oss04.str();

      vector<string> err_com;
      err_com.push_back(str_data00);
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);

      if( i_vec[2]==2*i_vec[3] )
      {
        err_com.push_back("This format type is not equal to ENDF-6 format.");
        err_com.push_back("This format type may be ENDF-5 format.");
        err_com.push_back("XMFS and XLFSS values are set as 0.0.");
        err_com.push_back("Please check the nuclear data format.");

        err_obj.output_caution(class_name, func_name, err_com);
      }
      else
      {
        ostringstream oss05, oss06;
        oss05 << i_vec[2];
        oss06 << i_vec[3];
        string str_data03 = "2*NEI+2             : " + oss05.str();
        string str_data04 = "NEI                 : " + oss06.str();
        err_com.push_back(str_data03);
        err_com.push_back(str_data04);
        err_com.push_back("2*NEI+2 at LTY=1 or 2 or 3 is not appropriate.");

        err_obj.output_runtime_error(class_name, func_name, err_com);
      }
    }

    int i_sta = 2;
    if( i_vec[2]==2*i_vec[3] )
    {
      i_sta = 0;
      XMFS[i][j]  = 0.0;
      XLFSS[i][j] = 0.0;
    }
    else
    {
      XMFS[i][j]  = e_vec[0];
      XLFSS[i][j] = e_vec[1];
    }

    int k_max = static_cast<int>(i_vec[3]);
    EI[i][j].resize(k_max);
    WEI[i][j].resize(k_max);
    for(int k=0; k<k_max; k++)
    {
      EI[i][j][k]  = e_vec[2*k+i_sta];
      WEI[i][j][k] = e_vec[2*k+i_sta+1];
    }
  }
  else
  {
    string class_name = "MF33Parser";
    string func_name  = "store_NC(MultiParser& mp_obj, int& line_no, int& i, int& j)";

    ostringstream oss00, oss01, oss02, oss03, oss04, oss05;
    oss00 << mt_no;
    oss01 << i;
    oss02 << static_cast<int>(NL);
    oss03 << j;
    oss04 << static_cast<int>(NC[i]);
    oss05 << LTY[i][j];
    string str_data00 = "Section number (MT) : " + oss00.str();
    string str_data01 = "NL                  : " + oss01.str() + " / " + oss02.str();
    string str_data02 = "NC                  : " + oss03.str() + " / " + oss04.str();
    string str_data03 = "LTY                 : " + oss05.str();

    vector<string> err_com;
    err_com.push_back(str_data00);
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("This LTY value at MF=33 is not supported in this program.");
    err_com.push_back("Supported LTY value is 0 - 3.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
  e_vec.clear();
  r_vec.clear();
  i_vec.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF33Parser::store_NI(MultiParser& mp_obj, int& line_no, int& i, int& j)
{
  vector<Real>    r_vec;
  vector<Integer> i_vec;
  r_vec.resize(6);
  i_vec.resize(6);

  vector<Real> e_vec;
  mp_obj.read_list(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                   e_vec);

  LB[i][j] = i_vec[1];

  if( LB[i][j] >= 0 && LB[i][j] <= 4 )
  {
    store_NI_lb00(r_vec, i_vec, e_vec, i, j);
  }
  else if( LB[i][j] == 5 )
  {
    store_NI_lb05(r_vec, i_vec, e_vec, i, j);
  }
  else if( LB[i][j] == 6 )
  {
    store_NI_lb06(r_vec, i_vec, e_vec, i, j);
  }
  else if( LB[i][j] == 8 || LB[i][j] == 9 )
  {
    if( i_vec[0] != 0 )
    {
      string class_name = "MF33Parser";
      string func_name  = "store_NI(MultiParser& mp_obj, int& line_no, int& i, int& j)";

      ostringstream oss00, oss01, oss02, oss03, oss04, oss05;
      oss00 << mt_no;
      oss01 << i;
      oss02 << static_cast<int>(NL);
      oss03 << j;
      oss04 << static_cast<int>(NI[i]);
      oss05 << i_vec[0];
      string str_data00 = "Section number (MT) : " + oss00.str();
      string str_data01 = "NL                  : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "NI                  : " + oss03.str() + " / " + oss04.str();
      string str_data03 = "LT                  : " + oss05.str();

      vector<string> err_com;
      err_com.push_back(str_data00);
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back("IF you use LB=8 or 9, LT must be 0.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
    store_NI_lb00(r_vec, i_vec, e_vec, i, j);
  }
  else
  {
    string class_name = "MF33Parser";
    string func_name  = "store_NI(MultiParser& mp_obj, int& line_no, int& i, int& j)";

    ostringstream oss00, oss01, oss02, oss03, oss04, oss05;
    oss00 << mt_no;
    oss01 << i;
    oss02 << static_cast<int>(NL);
    oss03 << j;
    oss04 << static_cast<int>(NI[i]);
    oss05 << LB[i][j];
    string str_data00 = "Section number (MT) : " + oss00.str();
    string str_data01 = "NL                  : " + oss01.str() + " / " + oss02.str();
    string str_data02 = "NI                  : " + oss03.str() + " / " + oss04.str();
    string str_data03 = "LB                  : " + oss05.str();

    vector<string> err_com;
    err_com.push_back(str_data00);
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("This LB value at MF=33 is not supported in this program.");
    err_com.push_back("Supported LB value is 0 - 6, 8 and 9.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
  r_vec.clear();
  i_vec.clear();
  e_vec.clear();
}


////////////////////////////////////////////////////////////////////////////////////////////////////

void MF33Parser::store_NI_lb00(vector<Real>& r_vec, vector<Integer>& i_vec, vector<Real>& e_vec, int& i, int& j)
{
  LT[i][j] = i_vec[0];

  if( i_vec[2]!=2*i_vec[3] )
  {
    string class_name = "MF33Parser";
    string func_name  = "store_NI_lb00(vector<Real>& r_vec, vector<Integer>& i_vec, vector<Real>& e_vec, ";
           func_name += "int& i, int& j)";

    ostringstream oss00, oss01, oss02, oss03, oss04, oss05, oss06;
    oss00 << mt_no;
    oss01 << i;
    oss02 << static_cast<int>(NL);
    oss03 << j;
    oss04 << static_cast<int>(NI[i]);
    oss05 << i_vec[2];
    oss06 << i_vec[3];
    string str_data00 = "Section number (MT) : " + oss00.str();
    string str_data01 = "NL                  : " + oss01.str() + " / " + oss02.str();
    string str_data02 = "NI                  : " + oss03.str() + " / " + oss04.str();
    string str_data03 = "NT=2*NP             : " + oss05.str();
    string str_data04 = "NP                  : " + oss05.str();

    vector<string> err_com;
    err_com.push_back(str_data00);
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back("NT is not equal to 2*NP at LB=0-4, 8-9.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  int lt_k = static_cast<int>(i_vec[3] - LT[i][j]);
  E_K[i][j].resize(lt_k);
  F_K[i][j].resize(lt_k);
  E_T[i][j].resize(static_cast<int>(LT[i][j]));
  F_T[i][j].resize(static_cast<int>(LT[i][j]));
  for(int k=0; k<lt_k; k++)
  {
    E_K[i][j][k] =         e_vec[2*k];
    F_K[i][j][k].push_back(e_vec[2*k+1]);
  }
  for(int k=0; k<static_cast<int>(LT[i][j]); k++)
  {
    E_T[i][j][k] =         e_vec[2*lt_k+2*k];
    F_T[i][j][k].push_back(e_vec[2*lt_k+2*k+1]);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF33Parser::store_NI_lb05(vector<Real>& r_vec, vector<Integer>& i_vec, vector<Real>& e_vec, int& i, int& j)
{
  LT[i][j] = i_vec[0];

  int ne = static_cast<int>(i_vec[3]);
  E_K[i][j].resize(ne);
  for(int k=0; k<ne; k++)
  {
    E_K[i][j][k] = e_vec[k];
  }

  if( LT[i][j]==0 )
  {
    if( i_vec[2]!=ne*(ne-1)+1 )
    {
      string class_name = "MF33Parser";
      string func_name  = "store_NI_lb05(vector<Real>& r_vec, vector<Integer>& i_vec, vector<Real>& e_vec, ";
             func_name += "int& i, int& j)";

      ostringstream oss00, oss01, oss02, oss03, oss04, oss05, oss06;
      oss00 << mt_no;
      oss01 << i;
      oss02 << static_cast<int>(NL);
      oss03 << j;
      oss04 << static_cast<int>(NI[i]);
      oss05 << i_vec[2];
      oss06 << ne;
      string str_data00 = "Section number (MT) : " + oss00.str();
      string str_data01 = "NL                  : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "NI                  : " + oss03.str() + " / " + oss04.str();
      string str_data03 = "NT=NE(NE-1)+1       : " + oss05.str();
      string str_data04 = "NE                  : " + oss06.str();

      vector<string> err_com;
      err_com.push_back(str_data00);
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back(str_data04);
      err_com.push_back("NT at LB=5, LS=0 is not equal to NE(NE-1)+1.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    int ele_no = ne;
    F_K[i][j].resize(ne-1);
    for(int k=0; k<ne-1; k++)
    {
      F_K[i][j][k].resize(ne-1);
      for(int l=0; l<ne-1; l++)
      {
        F_K[i][j][k][l] = e_vec[ele_no];
        ele_no++;
      }
    }
  }
  else if( LT[i][j]==1 )
  {
    if( i_vec[2]!=(ne*(ne+1))/2 )
    {
      string class_name = "MF33Parser";
      string func_name  = "store_NI_lb05(vector<Real>& r_vec, vector<Integer>& i_vec, vector<Real>& e_vec, ";
             func_name += "int& i, int& j)";

      ostringstream oss00, oss01, oss02, oss03, oss04, oss05, oss06;
      oss00 << mt_no;
      oss01 << i;
      oss02 << static_cast<int>(NL);
      oss03 << j;
      oss04 << static_cast<int>(NI[i]);
      oss05 << i_vec[2];
      oss06 << ne;
      string str_data00 = "Section number (MT) : " + oss00.str();
      string str_data01 = "NL                  : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "NI                  : " + oss03.str() + " / " + oss04.str();
      string str_data03 = "NT=NE(NE+1)/2       : " + oss05.str();
      string str_data04 = "NE                  : " + oss06.str();

      vector<string> err_com;
      err_com.push_back(str_data00);
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back(str_data04);
      err_com.push_back("NT at LB=5, LS=1 is not equal to NE(NE+1)/2.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    int ele_no = ne;
    F_K[i][j].resize(ne-1);
    for(int k=0; k<ne-1; k++)
    {
      int ne_d = ne-1-k;
      F_K[i][j][k].resize(ne_d);
      for(int l=0; l<ne_d; l++)
      {
        F_K[i][j][k][l] = e_vec[ele_no];
        ele_no++;
      }
    }
  }
  else
  {
    string class_name = "MF33Parser";
    string func_name  = "store_NI_lb05(vector<Real>& r_vec, vector<Integer>& i_vec, vector<Real>& e_vec, ";
           func_name += "int& i, int& j)";

    ostringstream oss00, oss01, oss02, oss03, oss04, oss05;
    oss00 << mt_no;
    oss01 << i;
    oss02 << static_cast<int>(NL);
    oss03 << j;
    oss04 << static_cast<int>(NI[i]);
    oss05 << LT[i][j];
    string str_data00 = "Section number (MT) : " + oss00.str();
    string str_data01 = "NL                  : " + oss01.str() + " / " + oss02.str();
    string str_data02 = "NI                  : " + oss03.str() + " / " + oss04.str();
    string str_data03 = "LS                  : " + oss05.str();

    vector<string> err_com;
    err_com.push_back(str_data00);
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("This LS value at MF=33 is not supported in this program.");
    err_com.push_back("Supported LS value is 0 and 1.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF33Parser::store_NI_lb06(vector<Real>& r_vec, vector<Integer>& i_vec, vector<Real>& e_vec, int& i, int& j)
{
  LT[i][j] = i_vec[0];

  int ner = static_cast<int>( i_vec[3]);
  int nec = static_cast<int>((i_vec[2] - 1)/ner);

  if( i_vec[2] != 1+ner*nec )
  {
    string class_name = "MF33Parser";
    string func_name  = "store_NI_lb06(vector<Real>& r_vec, vector<Integer>& i_vec, vector<Real>& e_vec, ";
           func_name += "int& i, int& j)";

    ostringstream oss00, oss01, oss02, oss03, oss04, oss05, oss06, oss07;
    oss00 << mt_no;
    oss01 << i;
    oss02 << static_cast<int>(NL);
    oss03 << j;
    oss04 << static_cast<int>(NI[i]);
    oss05 << i_vec[2];
    oss06 << ner;
    oss07 << nec;
    string str_data00 = "Section number (MT) : " + oss00.str();
    string str_data01 = "NL                  : " + oss01.str() + " / " + oss02.str();
    string str_data02 = "NI                  : " + oss03.str() + " / " + oss04.str();
    string str_data03 = "NT=1+NER*NEC        : " + oss05.str();
    string str_data04 = "NER                 : " + oss06.str();
    string str_data05 = "NEC                 : " + oss07.str();

    vector<string> err_com;
    err_com.push_back(str_data00);
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back(str_data05);
    err_com.push_back("NT at LB=6 is not equal to 1+NER*NEC.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  E_K[i][j].resize(ner);
  for(int k=0; k<ner; k++)
  {
    E_K[i][j][k] =  e_vec[k];
  }

  int ele_no = ner;
  E_T[i][j].resize(nec);
  for(int k=0; k<nec; k++)
  {
    E_T[i][j][k] =  e_vec[ele_no];
    ele_no++;
  }

  F_K[i][j].resize(ner-1);
  for(int k=0; k<ner-1; k++)
  {
    F_K[i][j][k].resize(nec-1);
    for(int l=0; l<nec-1; l++)
    {
      F_K[i][j][k][l] = e_vec[ele_no];
      ele_no++;
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF33Parser::clear()
{
  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);

  mat_no = unassigned_mat_no;
  mt_no  = unassigned_mt_no;
  ZA     = 0.0;
  AWR    = 0.0;
  MTL    = 0;
  NL     = 0;

  XMF.clear();
  XLFS.clear();
  MAT.clear();
  MT.clear();
  NC.clear();
  NI.clear();

  //NC-type Sub-Subsections
  clr_vec.clear_vec_array2_int( LTY);
  clr_vec.clear_vec_array2_real(E1);
  clr_vec.clear_vec_array2_real(E2);

  clr_vec.clear_vec_array3_real(CI);
  clr_vec.clear_vec_array3_real(XMTI);

  clr_vec.clear_vec_array2_int( MATS);
  clr_vec.clear_vec_array2_int( MTS);
  clr_vec.clear_vec_array2_real(XMFS);
  clr_vec.clear_vec_array2_real(XLFSS);
  clr_vec.clear_vec_array3_real(EI);
  clr_vec.clear_vec_array3_real(WEI);

  //NI-type Sub-Subsections
  clr_vec.clear_vec_array2_int( LB);

  clr_vec.clear_vec_array2_int( LT);
  clr_vec.clear_vec_array3_real(E_K);
  clr_vec.clear_vec_array3_real(E_T);
  clr_vec.clear_vec_array4_real(F_K);
  clr_vec.clear_vec_array4_real(F_T);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF33Parser::resize_matrix_NL()
{
  int nl = static_cast<int>(NL);

  XMF.resize(nl);
  XLFS.resize(nl);
  MAT.resize(nl);
  MT.resize(nl);
  NC.resize(nl);
  NI.resize(nl);

  //NC-type Sub-Subsections
  LTY.resize(nl);
  E1.resize( nl);
  E2.resize( nl);

  CI.resize(   nl);
  XMTI.resize( nl);
  MATS.resize( nl);
  MTS.resize(  nl);
  XMFS.resize( nl);
  XLFSS.resize(nl);
  EI.resize(   nl);
  WEI.resize(  nl);

  //NI-type Sub-Subsections
  LB.resize(     nl);
  LT.resize(     nl);
  E_K.resize(    nl);
  E_T.resize(    nl);
  F_K.resize(    nl);
  F_T.resize(    nl);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF33Parser::resize_matrix_NC(int& i)
{
  int nc = static_cast<int>(NC[i]);
  LTY[i].resize(nc);
  E1[i].resize( nc);
  E2[i].resize( nc);

  CI[i].resize(   nc);
  XMTI[i].resize( nc);
  MATS[i].resize( nc);
  MTS[i].resize(  nc);
  XMFS[i].resize( nc);
  XLFSS[i].resize(nc);
  EI[i].resize(   nc);
  WEI[i].resize(  nc);
}


////////////////////////////////////////////////////////////////////////////////////////////////////

void MF33Parser::resize_matrix_NI(int& i)
{
  int ni = static_cast<int>(NI[i]);
  LB[i].resize(     ni);
  LT[i].resize(     ni);
  E_K[i].resize(    ni);
  E_T[i].resize(    ni);
  F_K[i].resize(    ni);
  F_T[i].resize(    ni);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF33Parser::set_text(vector<string> text_data)
{
  clear();

  text = text_data;
  store_data();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string>                    MF33Parser::get_text()
{
  return text;
}

Integer                           MF33Parser::get_mat_no()
{
  return mat_no;
}

Integer                           MF33Parser::get_mt_no()
{
  return mt_no;
}

//Getter at line No.01-02
Real                              MF33Parser::get_ZA()
{
  return ZA;
}

Real                              MF33Parser::get_AWR()
{
  return AWR;
}

Integer                           MF33Parser::get_MTL()
{
  return MTL;
}

Integer                           MF33Parser::get_NL()
{
  return NL;
}

vector<Real>                      MF33Parser::get_XMF()
{
  return XMF;
}

vector<Real>                      MF33Parser::get_XLFS()
{
  return XLFS;
}

vector<Integer>                   MF33Parser::get_MAT()
{
  return MAT;
}

vector<Integer>                   MF33Parser::get_MT()
{
  return MT;
}

vector<Integer>                   MF33Parser::get_NC()
{
  return NC;
}

vector<Integer>                   MF33Parser::get_NI()
{
  return NI;
}


//NC-type Sub-Subsections
vector<vector<Integer> >          MF33Parser::get_LTY()
{
  return LTY;
}

vector<vector<Real> >             MF33Parser::get_E1()
{
  return E1;
}

vector<vector<Real> >             MF33Parser::get_E2()
{
  return E2;
}


vector<vector<vector<Real> > >    MF33Parser::get_CI()
{
  return CI;
}

vector<vector<vector<Real> > >    MF33Parser::get_XMTI()
{
  return XMTI;
}


vector<vector<Integer> >          MF33Parser::get_MATS()
{
  return MATS;
}

vector<vector<Integer> >          MF33Parser::get_MTS()
{
  return MTS;
}

vector<vector<Real> >             MF33Parser::get_XMFS()
{
  return XMFS;
}

vector<vector<Real> >             MF33Parser::get_XLFSS()
{
  return XLFSS;
}

vector<vector<vector<Real> > >    MF33Parser::get_EI()
{
  return EI;
}

vector<vector<vector<Real> > >    MF33Parser::get_WEI()
{
  return WEI;
}


//NI-type Sub-Subsections
vector<vector<Integer> >          MF33Parser::get_LB()
{
  return LB;
}


vector<vector<Integer> >          MF33Parser::get_LT()
{
  return LT;
}

vector<vector<vector<Real> > >    MF33Parser::get_E_K()
{
  return E_K;
}

vector<vector<vector<Real> > >    MF33Parser::get_E_T()
{
  return E_T;
}

vector<vector<vector<vector<Real> > > > MF33Parser::get_F_K()
{
  return F_K;
}

vector<vector<vector<vector<Real> > > > MF33Parser::get_F_T()
{
  return F_T;
}


vector<vector<Integer> >          MF33Parser::get_LS()
{
  return LT;
}


vector<vector<vector<Real> > >    MF33Parser::get_E_K_NER()
{
  return E_K;
}

vector<vector<vector<Real> > >    MF33Parser::get_E_K_NEC()
{
  return E_T;
}


////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void MF33Parser::set_mat_no(Integer& int_data)
{
  mat_no = int_data;
}

void MF33Parser::set_mt_no(Integer& int_data)
{
  mt_no = int_data;
}

void MF33Parser::set_ZA(Real& real_data)
{
  ZA = real_data;
}

void MF33Parser::set_AWR(Real& real_data)
{
  AWR = real_data;
}

void MF33Parser::set_MTL(Integer& int_data)
{
  MTL = int_data;
}

void MF33Parser::set_NL(Integer& int_data)
{
  NL = int_data;
}

void MF33Parser::set_XMF(vector<Real>& real_vec)
{
  XMF = real_vec;
}

void MF33Parser::set_XLFS(vector<Real>& real_vec)
{
  XLFS = real_vec;
}

void MF33Parser::set_MAT(vector<Integer>& int_vec)
{
  MAT = int_vec;
}

void MF33Parser::set_MT(vector<Integer>& int_vec)
{
  MT = int_vec;
}

void MF33Parser::set_NC(vector<Integer>& int_vec)
{
  NC = int_vec;
}

void MF33Parser::set_NI(vector<Integer>& int_vec)
{
  NI = int_vec;
}

void MF33Parser::set_LTY(vector<vector<Integer> >& int_vec)
{
  LTY = int_vec;
}

void MF33Parser::set_E1(vector<vector<Real> >& real_vec)
{
  E1 = real_vec;
}

void MF33Parser::set_E2(vector<vector<Real> >& real_vec)
{
  E2 = real_vec;
}

void MF33Parser::set_CI(vector<vector<vector<Real> > >& real_vec)
{
  CI = real_vec;
}

void MF33Parser::set_XMTI(vector<vector<vector<Real> > >& real_vec)
{
  XMTI = real_vec;
}

void MF33Parser::set_MATS(vector<vector<Integer> >& int_vec)
{
  MATS = int_vec;
}

void MF33Parser::set_MTS(vector<vector<Integer> >& int_vec)
{
  MTS = int_vec;
}

void MF33Parser::set_XMFS(vector<vector<Real> >& real_vec)
{
  XMFS = real_vec;
}

void MF33Parser::set_XLFSS(vector<vector<Real> >& real_vec)
{
  XLFSS = real_vec;
}

void MF33Parser::set_EI(vector<vector<vector<Real> > >& real_vec)
{
  EI = real_vec;
}

void MF33Parser::set_WEI(vector<vector<vector<Real> > >& real_vec)
{
  WEI = real_vec;
}

void MF33Parser::set_LB(vector<vector<Integer> >& int_vec)
{
  LB = int_vec;
}

void MF33Parser::set_LT(vector<vector<Integer> >& int_vec)
{
  LT = int_vec;
}

void MF33Parser::set_E_K(vector<vector<vector<Real> > >& real_vec)
{
  E_K = real_vec;
}

void MF33Parser::set_E_T(vector<vector<vector<Real> > >& real_vec)
{
  E_T = real_vec;
}

void MF33Parser::set_F_K(vector<vector<vector<vector<Real> > > >& real_vec)
{
  F_K = real_vec;
}

void MF33Parser::set_F_T(vector<vector<vector<vector<Real> > > >& real_vec)
{
  F_T = real_vec;
}

void MF33Parser::set_LS(vector<vector<Integer> >& int_vec)
{
  LT = int_vec;
}

void MF33Parser::set_E_K_NER(vector<vector<vector<Real> > >& real_vec)
{
  E_K = real_vec;
}

void MF33Parser::set_E_K_NEC(vector<vector<vector<Real> > >& real_vec)
{
  E_T = real_vec;
}

