#include "EndfUtils/MFxxMTyyyParser/MF40Parser.hpp"

using namespace frendy;

//constructor
MF40Parser::MF40Parser(void)
{
  clear();

  err_obj.set_output_mode(err_obj.warning_off);
}

//destructor
MF40Parser::~MF40Parser(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF40Parser::store_data()
{
  MultiParser mp_obj;

  //Text file data check
  if( static_cast<Integer>(text.size()) < 1 )
  {
    string class_name = "MF40Parser";
    string func_name  = "store_data()";

    ostringstream oss;
    oss << static_cast<Integer>(text.size());
    string str_data = "Text line number : " + oss.str();

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("The text line number is not appropriate for MF=40.");
    err_com.push_back("The text line number should be larger than 1.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //Check MF number
  if( mp_obj.check_mf(text, mf_no) != 0)
  {
    string class_name = "MF40Parser";
    string func_name  = "store_data()";

    ostringstream oss01;
    oss01 << mf_no;
    string str_data01 = "Text data at first line : " + text[0];
    string str_data02 = "File number (MF)        : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("The MF number is different to MF=40.");

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
  //ZA, AWR, LIS, NS
  mp_obj.read_head(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3]);
  ZA  = r_vec[0];
  AWR = r_vec[1];
  LIS = i_vec[0];
  NS  = i_vec[2];

  resize_matrix_first(static_cast<int>(NS));

  for(int i=0; i<static_cast<int>(NS); i++)
  {
    mp_obj.read_cont(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3]);
    QM[i]   = r_vec[0];
    QI[i]   = r_vec[1];
    IZAP[i] = i_vec[0];
    LFS[i]  = i_vec[1];
    NL[i]   = i_vec[3];

    resize_matrix_second(i, static_cast<int>(NL[i]));

    for(int j=0; j<static_cast<int>(NL[i]); j++)
    {
      mp_obj.read_cont(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3]);
      XMF1[i][j]  = r_vec[0];
      XLFS1[i][j] = r_vec[1];
      MAT1[i][j]  = i_vec[0];
      MT1[i][j]   = i_vec[1];
      NC[i][j]    = i_vec[2];
      NI[i][j]    = i_vec[3];

      //NC-type Sub-Sub-Subsections
      if( NC[i][j] > 0 )
      {
        resize_matrix_NC(i, j, static_cast<int>(NC[i][j]));
        for(int k=0; k<static_cast<int>(NC[i][j]); k++)
        {
          store_NC(mp_obj, line_no, i, j, k);
        }
      }

      //NI-type Sub-Sub-Subsections
      if( NI[i][j] > 0 )
      {
        resize_matrix_NI(i, j, static_cast<int>(NI[i][j]));
        for(int k=0; k<static_cast<int>(NI[i][j]); k++)
        {
          store_NI(mp_obj, line_no, i, j, k);
        }
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

void MF40Parser::store_NC(MultiParser& mp_obj, int& line_no, int& i, int& j, int& k)
{
  vector<Real>    r_vec;
  vector<Integer> i_vec;
  r_vec.resize(6);
  i_vec.resize(6);

  mp_obj.read_cont(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3]);
  LTY[i][j][k] = i_vec[1];

  vector<Real> e_vec;
  mp_obj.read_list(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                   e_vec);
  E1[i][j][k] = r_vec[0];
  E2[i][j][k] = r_vec[1];

  if( LTY[i][j][k]==0 )
  {
    if( i_vec[2]!=2*i_vec[3] )
    {
      string class_name = "MF40Parser";
      string func_name  = "store_NC(MultiParser& mp_obj, int& line_no, int& i, int& j, int& k)";

      ostringstream oss00, oss01, oss02, oss03, oss04, oss05, oss06, oss07, oss08;
      oss00 << mt_no;
      oss01 << i;
      oss02 << static_cast<int>(NS);
      oss03 << j;
      oss04 << static_cast<int>(NL[i]);
      oss05 << k;
      oss06 << NC[i][j];
      oss07 << i_vec[2];
      oss08 << i_vec[3];
      string str_data00 = "Section number (MT) : " + oss00.str();
      string str_data01 = "NS                  : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "NL                  : " + oss03.str() + " / " + oss04.str();
      string str_data03 = "NC                  : " + oss05.str() + " / " + oss06.str();
      string str_data04 = "2*NCI               : " + oss07.str();
      string str_data05 = "NCI                 : " + oss08.str();

      vector<string> err_com;
      err_com.push_back(str_data00);
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back(str_data04);
      err_com.push_back(str_data05);
      err_com.push_back("2*NCI at LTY=0 is not appropriate.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

	int l_max = static_cast<int>(i_vec[3]);
    CI[i][j][k].resize(  l_max);
    XMTI[i][j][k].resize(l_max);
    for(int l=0; l<static_cast<int>(i_vec[3]); l++)
    {
      CI[i][j][k][l]   = e_vec[2*l];
      XMTI[i][j][k][l] = e_vec[2*l+1];
    }
  }
  else if( LTY[i][j][k]==1 || LTY[i][j][k]==2 || LTY[i][j][k]==3 )
  {
    MATS[i][j][k] = i_vec[0];
    MTS[i][j][k]  = i_vec[1];

    if( i_vec[2]!=2*i_vec[3]+2 )
    {
      string class_name = "MF40Parser";
      string func_name  = "store_NC(MultiParser& mp_obj, int& line_no, int& i, int& j, int& k)";

      ostringstream oss00, oss01, oss02, oss03, oss04, oss05, oss06, oss07, oss08;
      oss00 << mt_no;
      oss01 << i;
      oss02 << static_cast<int>(NS);
      oss03 << j;
      oss04 << static_cast<int>(NL[i]);
      oss05 << k;
      oss06 << NC[i][j];
      oss07 << i_vec[2];
      oss08 << i_vec[3];
      string str_data00 = "Section number (MT) : " + oss00.str();
      string str_data01 = "NS                  : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "NL                  : " + oss03.str() + " / " + oss04.str();
      string str_data03 = "NC                  : " + oss05.str() + " / " + oss06.str();
      string str_data04 = "2*NEI+2             : " + oss07.str();
      string str_data05 = "NEI                 : " + oss08.str();

      vector<string> err_com;
      err_com.push_back(str_data00);
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back(str_data04);
      err_com.push_back(str_data05);
      err_com.push_back("2*NEI+2 at LTY=1 or 2 or 3 is not appropriate.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
    XMFS[i][j][k]  = e_vec[0];
    XLFSS[i][j][k] = e_vec[1];

	int l_max = static_cast<int>(i_vec[3]);
    EI[i][j][k].resize( l_max);
    WEI[i][j][k].resize(l_max);
    for(int l=0; l<static_cast<int>(i_vec[3]); l++)
    {
      EI[i][j][k][l] =  e_vec[2*l+2];
      WEI[i][j][k][l] = e_vec[2*l+3];
    }
  }
  else
  {
    string class_name = "MF40Parser";
    string func_name  = "store_NC(MultiParser& mp_obj, int& line_no, int& i, int& j, int& k)";

    ostringstream oss00, oss01, oss02, oss03, oss04, oss05, oss06, oss07;
    oss00 << mt_no;
    oss01 << i;
    oss02 << static_cast<int>(NS);
    oss03 << j;
    oss04 << static_cast<int>(NL[i]);
    oss05 << k;
    oss06 << NC[i][j];
    oss07 << LTY[i][j][k];
    string str_data00 = "Section number (MT) : " + oss00.str();
    string str_data01 = "NS                  : " + oss01.str() + " / " + oss02.str();
    string str_data02 = "NL                  : " + oss03.str() + " / " + oss04.str();
    string str_data03 = "NC                  : " + oss05.str() + " / " + oss06.str();
    string str_data04 = "LTY                 : " + oss07.str();

    vector<string> err_com;
    err_com.push_back(str_data00);
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back("This LTY value at MF=40 is not supported in this program.");
    err_com.push_back("Supported LTY value is 0 - 3.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
  e_vec.clear();
  r_vec.clear();
  i_vec.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF40Parser::store_NI(MultiParser& mp_obj, int& line_no, int& i, int& j, int& k)
{
  vector<Real>    r_vec;
  vector<Integer> i_vec;
  r_vec.resize(6);
  i_vec.resize(6);

  vector<Real> e_vec;
  mp_obj.read_list(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                   e_vec);

  LB[i][j][k] = i_vec[1];

  if( LB[i][j][k] >= 0 && LB[i][j][k] <= 4 )
  {
    store_NI_lb00(r_vec, i_vec, e_vec, i, j, k);
  }
  else if( LB[i][j][k]==5 )
  {
    store_NI_lb05(r_vec, i_vec, e_vec, i, j, k);
  }
  else if( LB[i][j][k]==6 )
  {
    store_NI_lb06(r_vec, i_vec, e_vec, i, j, k);
  }
  else if( LB[i][j][k]==8 || LB[i][j][k]==9 )
  {
    if( i_vec[0] != 0 )
    {
      string class_name = "MF40Parser";
      string func_name  = "store_NI(MultiParser& mp_obj, int& line_no, int& i, int& j, int& k)";

      ostringstream oss00, oss01, oss02, oss03, oss04, oss05, oss06, oss07;
      oss00 << mt_no;
      oss01 << i;
      oss02 << static_cast<int>(NS);
      oss03 << j;
      oss04 << static_cast<int>(NL[i]);
      oss05 << k;
      oss06 << NI[i][j];
      oss07 << i_vec[0];
      string str_data00 = "Section number (MT) : " + oss00.str();
      string str_data01 = "NS                  : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "NL                  : " + oss03.str() + " / " + oss04.str();
      string str_data03 = "NI                  : " + oss05.str() + " / " + oss06.str();
      string str_data04 = "LT                  : " + oss07.str();

      vector<string> err_com;
      err_com.push_back(str_data00);
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back(str_data04);
      err_com.push_back("When you use LB=8 or 9, LT must be 0.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
    store_NI_lb00(r_vec, i_vec, e_vec, i, j, k);
  }
  else
  {
    string class_name = "MF40Parser";
    string func_name  = "store_NI(MultiParser& mp_obj, int& line_no, int& i, int& j, int& k)";

    ostringstream oss00, oss01, oss02, oss03, oss04, oss05, oss06, oss07;
    oss00 << mt_no;
    oss01 << i;
    oss02 << static_cast<int>(NS);
    oss03 << j;
    oss04 << static_cast<int>(NL[i]);
    oss05 << k;
    oss06 << NI[i][j];
    oss07 << LB[i][j][k];
    string str_data00 = "Section number (MT) : " + oss00.str();
    string str_data01 = "NS                  : " + oss01.str() + " / " + oss02.str();
    string str_data02 = "NL                  : " + oss03.str() + " / " + oss04.str();
    string str_data03 = "NI                  : " + oss05.str() + " / " + oss06.str();
    string str_data04 = "LB                  : " + oss07.str();

    vector<string> err_com;
    err_com.push_back(str_data00);
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back("This LB value at MF=40 is not supported in this program.");
    err_com.push_back("Supported LB value is 0 - 6, 8 and 9.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
  r_vec.clear();
  i_vec.clear();
  e_vec.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF40Parser::store_NI_lb00(vector<Real>& r_vec, vector<Integer>& i_vec, vector<Real>& e_vec,
                               int& i, int& j, int& k)
{
  LT[i][j][k] = i_vec[0];

  if( i_vec[2]!=2*i_vec[3] )
  {
    string class_name = "MF40Parser";
    string func_name  = "store_NI_lb00(vector<Real>& r_vec, vector<Integer>& i_vec, vector<Real>& e_vec, ";
           func_name += "int& i, int& j, int& k)";

    ostringstream oss00, oss01, oss02, oss03, oss04, oss05, oss06, oss07, oss08;
    oss00 << mt_no;
    oss01 << i;
    oss02 << static_cast<int>(NS);
    oss03 << j;
    oss04 << static_cast<int>(NL[i]);
    oss05 << k;
    oss06 << NI[i][j];
    oss07 << i_vec[2];
    oss08 << i_vec[3];
    string str_data00 = "Section number (MT) : " + oss00.str();
    string str_data01 = "NS                  : " + oss01.str() + " / " + oss02.str();
    string str_data02 = "NL                  : " + oss03.str() + " / " + oss04.str();
    string str_data03 = "NI                  : " + oss05.str() + " / " + oss06.str();
    string str_data04 = "NT=2*NP             : " + oss07.str();
    string str_data05 = "NP                  : " + oss08.str();

    vector<string> err_com;
    err_com.push_back(str_data00);
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back(str_data05);
    err_com.push_back("NT is not equal to 2*NP at LB=0-4, 8-9.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  int lt_l = static_cast<int>(i_vec[3] - LT[i][j][k]);
  E_K[i][j][k].resize(lt_l);
  F_K[i][j][k].resize(lt_l);
  for(int l=0; l<lt_l; l++)
  {
    E_K[i][j][k][l] =         e_vec[2*l];
    F_K[i][j][k][l].push_back(e_vec[2*l+1]);
  }

  int lt_t = static_cast<int>(LT[i][j][k]);
  E_T[i][j][k].resize(lt_t);
  F_T[i][j][k].resize(lt_t);
  for(int l=0; l<lt_t; l++)
  {
    E_T[i][j][k][l] =         e_vec[2*lt_l+2*l];
    F_T[i][j][k][l].push_back(e_vec[2*lt_l+2*l+1]);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF40Parser::store_NI_lb05(vector<Real>& r_vec, vector<Integer>& i_vec, vector<Real>& e_vec,
                               int& i, int& j, int& k)
{
  LT[i][j][k] = i_vec[0];

  int ne = i_vec[3];
  E_K[i][j][k].resize(ne);
  for(int l=0; l<ne; l++)
  {
    E_K[i][j][k][l] = e_vec[l];
  }

  if( LT[i][j][k]==0 )
  {
    if( i_vec[2]!=ne*(ne-1)+1 )
    {
      string class_name = "MF40Parser";
      string func_name  = "store_NI_lb05(vector<Real>& r_vec, vector<Integer>& i_vec, vector<Real>& e_vec, ";
             func_name += "int& i, int& j, int& k)";

      ostringstream oss00, oss01, oss02, oss03, oss04, oss05, oss06, oss07, oss08;
      oss00 << mt_no;
      oss01 << i;
      oss02 << static_cast<int>(NS);
      oss03 << j;
      oss04 << static_cast<int>(NL[i]);
      oss05 << k;
      oss06 << NI[i][j];
      oss07 << i_vec[2];
      oss08 << ne;
      string str_data00 = "Section number (MT) : " + oss00.str();
      string str_data01 = "NS                  : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "NL                  : " + oss03.str() + " / " + oss04.str();
      string str_data03 = "NI                  : " + oss05.str() + " / " + oss06.str();
      string str_data04 = "NT=NE(NE-1)+1       : " + oss07.str();
      string str_data05 = "NE                  : " + oss08.str();

      vector<string> err_com;
      err_com.push_back(str_data00);
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back(str_data04);
      err_com.push_back(str_data05);
      err_com.push_back("NT at LB=5, LS=0 is not equal to NE(NE-1)+1.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    int ele_no = ne;
    F_K[i][j][k].resize(ne-1);
    for(int l=0; l<ne-1; l++)
    {
      F_K[i][j][k][l].resize(ne-1);
      for(int m=0; m<ne-1; m++)
      {
        F_K[i][j][k][l][m] = e_vec[ele_no];
        ele_no++;
      }
    }
  }
  else if( LT[i][j][k]==1 )
  {
    if( i_vec[2]!=(ne*(ne+1))/2 )
    {
      string class_name = "MF40Parser";
      string func_name  = "store_NI_lb05(vector<Real>& r_vec, vector<Integer>& i_vec, vector<Real>& e_vec, ";
             func_name += "int& i, int& j, int& k)";

      ostringstream oss00, oss01, oss02, oss03, oss04, oss05, oss06, oss07, oss08;
      oss00 << mt_no;
      oss01 << i;
      oss02 << static_cast<int>(NS);
      oss03 << j;
      oss04 << static_cast<int>(NL[i]);
      oss05 << k;
      oss06 << NI[i][j];
      oss07 << i_vec[2];
      oss08 << ne;
      string str_data00 = "Section number (MT) : " + oss00.str();
      string str_data01 = "NS                  : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "NL                  : " + oss03.str() + " / " + oss04.str();
      string str_data03 = "NI                  : " + oss05.str() + " / " + oss06.str();
      string str_data04 = "NT=NE(NE+1)/2       : " + oss07.str();
      string str_data05 = "NE                  : " + oss08.str();

      vector<string> err_com;
      err_com.push_back(str_data00);
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back(str_data04);
      err_com.push_back(str_data05);
      err_com.push_back("NT at LB=5, LS=1 is not equal to NE(NE+1)/2.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    int ele_no = ne;
    F_K[i][j][k].resize(ne-1);
    for(int l=0; l<ne-1; l++)
    {
      int ne_d = ne-1-l;
      F_K[i][j][k][l].resize(ne_d);
      for(int m=0; m<ne_d; m++)
      {
        F_K[i][j][k][l][m] = e_vec[ele_no];
        ele_no++;
      }
    }
  }
  else
  {
    string class_name = "MF40Parser";
    string func_name  = "store_NI_lb05(vector<Real>& r_vec, vector<Integer>& i_vec, vector<Real>& e_vec, ";
           func_name += "int& i, int& j, int& k)";

    ostringstream oss00, oss01, oss02, oss03, oss04, oss05, oss06, oss07;
    oss00 << mt_no;
    oss01 << i;
    oss02 << static_cast<int>(NS);
    oss03 << j;
    oss04 << static_cast<int>(NL[i]);
    oss05 << k;
    oss06 << NI[i][j];
    oss07 << LT[i][j][k];
    string str_data00 = "Section number (MT) : " + oss00.str();
    string str_data01 = "NS                  : " + oss01.str() + " / " + oss02.str();
    string str_data02 = "NL                  : " + oss03.str() + " / " + oss04.str();
    string str_data03 = "NI                  : " + oss05.str() + " / " + oss06.str();
    string str_data04 = "LS                  : " + oss07.str();

    vector<string> err_com;
    err_com.push_back(str_data00);
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back("This LS value at MF=40 is not supported in this program.");
    err_com.push_back("Supported LS value is 0 and 1.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF40Parser::store_NI_lb06(vector<Real>& r_vec, vector<Integer>& i_vec, vector<Real>& e_vec,
                               int& i, int& j, int& k)
{
  LT[i][j][k] = i_vec[0];

  int ner =  i_vec[3];
  int nec = (i_vec[2] - 1)/ner;

  if( i_vec[2] != 1+ner*nec )
  {
    string class_name = "MF40Parser";
    string func_name  = "store_NI_lb06(vector<Real>& r_vec, vector<Integer>& i_vec, vector<Real>& e_vec, ";
           func_name += "int& i, int& j, int& k)";

    ostringstream oss00, oss01, oss02, oss03, oss04, oss05, oss06, oss07, oss08, oss09;
    oss00 << mt_no;
    oss01 << i;
    oss02 << static_cast<int>(NS);
    oss03 << j;
    oss04 << static_cast<int>(NL[i]);
    oss05 << k;
    oss06 << NI[i][j];
    oss07 << i_vec[2];
    oss08 << ner;
    oss09 << nec;
    string str_data00 = "Section number (MT) : " + oss00.str();
    string str_data01 = "NS                  : " + oss01.str() + " / " + oss02.str();
    string str_data02 = "NL                  : " + oss03.str() + " / " + oss04.str();
    string str_data03 = "NI                  : " + oss05.str() + " / " + oss06.str();
    string str_data04 = "NT=1+NER*NEC        : " + oss07.str();
    string str_data05 = "NER                 : " + oss08.str();
    string str_data06 = "NEC                 : " + oss09.str();

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

  E_K[i][j][k].resize(ner);
  for(int l=0; l<ner; l++)
  {
    E_K[i][j][k][l] = e_vec[l];
  }

  int ele_no = ner;
  E_T[i][j][k].resize(nec);
  for(int l=0; l<nec; l++)
  {
    E_T[i][j][k][l] = e_vec[ele_no];
    ele_no++;
  }

  F_K[i][j][k].resize(ner-1);
  for(int l=0; l<ner-1; l++)
  {
    F_K[i][j][k][l].resize(nec-1);
    for(int m=0; m<nec-1; m++)
    {
      F_K[i][j][k][l][m] = e_vec[ele_no];
      ele_no++;
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF40Parser::clear()
{
  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);

  mat_no = unassigned_mat_no;
  mt_no  = unassigned_mt_no;
  ZA     = 0.0;
  AWR    = 0.0;
  LIS    = 0;
  NS     = 0;

  QM.clear();
  QI.clear();
  IZAP.clear();
  LFS.clear();
  NL.clear();

  clr_vec.clear_vec_array2_real(XMF1);
  clr_vec.clear_vec_array2_real(XLFS1);
  clr_vec.clear_vec_array2_int( MAT1);
  clr_vec.clear_vec_array2_int( MT1);
  clr_vec.clear_vec_array2_int( NC);
  clr_vec.clear_vec_array2_int( NI);

  //NC-type Sub-Sub-Subsections
  clr_vec.clear_vec_array3_int( LTY);
  clr_vec.clear_vec_array3_real(E1);
  clr_vec.clear_vec_array3_real(E2);
  clr_vec.clear_vec_array4_real(CI);
  clr_vec.clear_vec_array4_real(XMTI);

  clr_vec.clear_vec_array3_int( MATS);
  clr_vec.clear_vec_array3_int( MTS);
  clr_vec.clear_vec_array3_real(XMFS);
  clr_vec.clear_vec_array3_real(XLFSS);
  clr_vec.clear_vec_array4_real(EI);
  clr_vec.clear_vec_array4_real(WEI);

  //NI-type Sub-Sub-Subsections
  clr_vec.clear_vec_array3_int( LB);
  clr_vec.clear_vec_array3_int( LT);

  clr_vec.clear_vec_array4_real(E_K);
  clr_vec.clear_vec_array4_real(E_T);
  clr_vec.clear_vec_array5_real(F_K);
  clr_vec.clear_vec_array5_real(F_T);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF40Parser::resize_matrix_first(int i_max)
{
  QM.resize(  i_max);
  QI.resize(  i_max);
  IZAP.resize(i_max);
  LFS.resize( i_max);
  NL.resize(  i_max);

  XMF1.resize( i_max);
  XLFS1.resize(i_max);
  MAT1.resize( i_max);
  MT1.resize(  i_max);
  NC.resize(   i_max);
  NI.resize(   i_max);

  //NC-type Sub-Sub-Subsections
  LTY.resize( i_max);
  E1.resize(  i_max);
  E2.resize(  i_max);
  CI.resize(  i_max);
  XMTI.resize(i_max);

  MATS.resize( i_max);
  MTS.resize(  i_max);
  XMFS.resize( i_max);
  XLFSS.resize(i_max);
  EI.resize(   i_max);
  WEI.resize(  i_max);

  //NI-type Sub-Sub-Subsections
  LB.resize( i_max);
  LT.resize( i_max);
  E_K.resize(i_max);
  E_T.resize(i_max);
  F_K.resize(i_max);
  F_T.resize(i_max);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF40Parser::resize_matrix_second(int& i, int j_max)
{
  XMF1[i].resize( j_max);
  XLFS1[i].resize(j_max);
  MAT1[i].resize( j_max);
  MT1[i].resize(  j_max);
  NC[i].resize(   j_max);
  NI[i].resize(   j_max);

  //NC-type Sub-Sub-Subsections
  LTY[i].resize( j_max);
  E1[i].resize(  j_max);
  E2[i].resize(  j_max);
  CI[i].resize(  j_max);
  XMTI[i].resize(j_max);

  MATS[i].resize( j_max);
  MTS[i].resize(  j_max);
  XMFS[i].resize( j_max);
  XLFSS[i].resize(j_max);
  EI[i].resize(   j_max);
  WEI[i].resize(  j_max);

  //NI-type Sub-Sub-Subsections
  LB[i].resize( j_max);
  LT[i].resize( j_max);
  E_K[i].resize(j_max);
  E_T[i].resize(j_max);
  F_K[i].resize(j_max);
  F_T[i].resize(j_max);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF40Parser::resize_matrix_NC(int& i, int& j, int k_max)
{
  LTY[i][j].resize( k_max);
  E1[i][j].resize(  k_max);
  E2[i][j].resize(  k_max);
  CI[i][j].resize(  k_max);
  XMTI[i][j].resize(k_max);

  MATS[i][j].resize( k_max);
  MTS[i][j].resize(  k_max);
  XMFS[i][j].resize( k_max);
  XLFSS[i][j].resize(k_max);
  EI[i][j].resize(   k_max);
  WEI[i][j].resize(  k_max);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF40Parser::resize_matrix_NI(int& i, int& j, int k_max)
{
  LB[i][j].resize( k_max);
  LT[i][j].resize( k_max);
  E_K[i][j].resize(k_max);
  E_T[i][j].resize(k_max);
  F_K[i][j].resize(k_max);
  F_T[i][j].resize(k_max);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF40Parser::set_text(vector<string> text_data)
{
  clear();

  text = text_data;
  store_data();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string>                    MF40Parser::get_text()
{
  return text;
}

Integer                           MF40Parser::get_mat_no()
{
  return mat_no;
}

Integer                           MF40Parser::get_mt_no()
{
  return mt_no;
}

//Getter ad line No.01-02
Real                              MF40Parser::get_ZA()
{
  return ZA;
}

Real                              MF40Parser::get_AWR()
{
  return AWR;
}

Integer                           MF40Parser::get_LIS()
{
  return LIS;
}

Integer                           MF40Parser::get_NS()
{
  return NS;
}


vector<Real>                      MF40Parser::get_QM()
{
  return QM;
}

vector<Real>                      MF40Parser::get_QI()
{
  return QI;
}

vector<Integer>                   MF40Parser::get_IZAP()
{
  return IZAP;
}

vector<Integer>                   MF40Parser::get_LFS()
{
  return LFS;
}

vector<Integer>                   MF40Parser::get_NL()
{
  return NL;
}


vector<vector<Real> >             MF40Parser::get_XMF1()
{
  return XMF1;
}

vector<vector<Real> >             MF40Parser::get_XLFS1()
{
  return XLFS1;
}

vector<vector<Integer> >          MF40Parser::get_MAT1()
{
  return MAT1;
}

vector<vector<Integer> >          MF40Parser::get_MT1()
{
  return MT1;
}

vector<vector<Integer> >          MF40Parser::get_NC()
{
  return NC;
}

vector<vector<Integer> >          MF40Parser::get_NI()
{
  return NI;
}


//NC-type Sub-Sub-Subsections
vector<vector<vector<Integer> > > MF40Parser::get_LTY()
{
  return LTY;
}

vector<vector<vector<Real> > >    MF40Parser::get_E1()
{
  return E1;
}

vector<vector<vector<Real> > >    MF40Parser::get_E2()
{
  return E2;
}

vector<vector<vector<vector<Real> > > > MF40Parser::get_CI()
{
  return CI;
}

vector<vector<vector<vector<Real> > > > MF40Parser::get_XMTI()
{
  return XMTI;
}


vector<vector<vector<Integer> > > MF40Parser::get_MATS()
{
  return MATS;
}

vector<vector<vector<Integer> > > MF40Parser::get_MTS()
{
  return MTS;
}

vector<vector<vector<Real> > >    MF40Parser::get_XMFS()
{
  return XMFS;
}

vector<vector<vector<Real> > >    MF40Parser::get_XLFSS()
{
  return XLFSS;
}

vector<vector<vector<vector<Real> > > > MF40Parser::get_EI()
{
  return EI;
}

vector<vector<vector<vector<Real> > > > MF40Parser::get_WEI()
{
  return WEI;
}


//NI-type Sub-Sub-Subsections
vector<vector<vector<Integer> > > MF40Parser::get_LB()
{
  return LB;
}

vector<vector<vector<Integer> > > MF40Parser::get_LT()
{
  return LT;
}

vector<vector<vector<Integer> > > MF40Parser::get_LS()
{
  return LT;
}


vector<vector<vector<vector<Real> > > >          MF40Parser::get_E_K()
{
  return E_K;
}

vector<vector<vector<vector<Real> > > >          MF40Parser::get_E_T()
{
  return E_T;
}

vector<vector<vector<vector<vector<Real> > > > > MF40Parser::get_F_K()
{
  return F_K;
}

vector<vector<vector<vector<vector<Real> > > > > MF40Parser::get_F_T()
{
  return F_T;
}

vector<vector<vector<vector<Real> > > >          MF40Parser::get_E_K_NER()
{
  return E_K;
}

vector<vector<vector<vector<Real> > > >          MF40Parser::get_E_K_NEC()
{
  return E_T;
}


////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void MF40Parser::set_mat_no(Integer& int_data)
{
  mat_no = int_data;
}

void MF40Parser::set_mt_no(Integer& int_data)
{
  mt_no = int_data;
}

void MF40Parser::set_ZA(Real& real_data)
{
  ZA = real_data;
}

void MF40Parser::set_AWR(Real& real_data)
{
  AWR = real_data;
}

void MF40Parser::set_LIS(Integer& int_data)
{
  LIS = int_data;
}

void MF40Parser::set_NS(Integer& int_data)
{
  NS = int_data;
}

void MF40Parser::set_QM(vector<Real>& real_vec)
{
  QM = real_vec;
}

void MF40Parser::set_QI(vector<Real>& real_vec)
{
  QI = real_vec;
}

void MF40Parser::set_IZAP(vector<Integer>& int_vec)
{
  IZAP = int_vec;
}

void MF40Parser::set_LFS(vector<Integer>& int_vec)
{
  LFS = int_vec;
}

void MF40Parser::set_NL(vector<Integer>& int_vec)
{
  NL = int_vec;
}

void MF40Parser::set_XMF1(vector<vector<Real> >& real_vec)
{
  XMF1 = real_vec;
}

void MF40Parser::set_XLFS1(vector<vector<Real> >& real_vec)
{
  XLFS1 = real_vec;
}

void MF40Parser::set_MAT1(vector<vector<Integer> >& int_vec)
{
  MAT1 = int_vec;
}

void MF40Parser::set_MT1(vector<vector<Integer> >& int_vec)
{
  MT1 = int_vec;
}

void MF40Parser::set_NC(vector<vector<Integer> >& int_vec)
{
  NC = int_vec;
}

void MF40Parser::set_NI(vector<vector<Integer> >& int_vec)
{
  NI = int_vec;
}

void MF40Parser::set_LTY(vector<vector<vector<Integer> > >& int_vec)
{
  LTY = int_vec;
}

void MF40Parser::set_E1(vector<vector<vector<Real> > >& real_vec)
{
  E1 = real_vec;
}

void MF40Parser::set_E2(vector<vector<vector<Real> > >& real_vec)
{
  E2 = real_vec;
}

void MF40Parser::set_CI(vector<vector<vector<vector<Real> > > >& real_vec)
{
  CI = real_vec;
}

void MF40Parser::set_XMTI(vector<vector<vector<vector<Real> > > >& real_vec)
{
  XMTI = real_vec;
}

void MF40Parser::set_MATS(vector<vector<vector<Integer> > >& int_vec)
{
  MATS = int_vec;
}

void MF40Parser::set_MTS(vector<vector<vector<Integer> > >& int_vec)
{
  MTS = int_vec;
}

void MF40Parser::set_XMFS(vector<vector<vector<Real> > >& real_vec)
{
  XMFS = real_vec;
}

void MF40Parser::set_XLFSS(vector<vector<vector<Real> > >& real_vec)
{
  XLFSS = real_vec;
}

void MF40Parser::set_EI(vector<vector<vector<vector<Real> > > >& real_vec)
{
  EI = real_vec;
}

void MF40Parser::set_WEI(vector<vector<vector<vector<Real> > > >& real_vec)
{
  WEI = real_vec;
}

void MF40Parser::set_LB(vector<vector<vector<Integer> > >& int_vec)
{
  LB = int_vec;
}

void MF40Parser::set_LT(vector<vector<vector<Integer> > >& int_vec)
{
  LT = int_vec;
}

void MF40Parser::set_LS(vector<vector<vector<Integer> > >& int_vec)
{
  LT = int_vec;
}

void MF40Parser::set_E_K(vector<vector<vector<vector<Real> > > >& real_vec)
{
  E_K = real_vec;
}

void MF40Parser::set_E_T(vector<vector<vector<vector<Real> > > >& real_vec)
{
  E_T = real_vec;
}

void MF40Parser::set_F_K(vector<vector<vector<vector<vector<Real> > > > >& real_vec)
{
  F_K = real_vec;
}

void MF40Parser::set_F_T(vector<vector<vector<vector<vector<Real> > > > >& real_vec)
{
  F_T = real_vec;
}

void MF40Parser::set_E_K_NER(vector<vector<vector<vector<Real> > > >& real_vec)
{
  E_K = real_vec;
}

void MF40Parser::set_E_K_NEC(vector<vector<vector<vector<Real> > > >& real_vec)
{
  E_T = real_vec;
}

