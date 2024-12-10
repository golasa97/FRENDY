#include "EndfUtils/MFxxMTyyyParser/MF35Parser.hpp"

using namespace frendy;

//constructor
MF35Parser::MF35Parser(void)
{
  clear();

  err_obj.set_output_mode(err_obj.warning_off);
}

//destructor
MF35Parser::~MF35Parser(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF35Parser::store_data()
{
  MultiParser mp_obj;

  //Text file data check
  if( static_cast<Integer>(text.size()) < 1 )
  {
    string class_name = "MF35Parser";
    string func_name  = "store_data()";

    ostringstream oss;
    oss << static_cast<Integer>(text.size());
    string str_data = "Text line number : " + oss.str();

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("The text line number is not appropriate for MF=35.");
    err_com.push_back("The text line number should be larger than 1.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //Check MF number
  if( mp_obj.check_mf(text, mf_no) != 0)
  {
    string class_name = "MF35Parser";
    string func_name  = "store_data()";

    ostringstream oss01;
    oss01 << mf_no;
    string str_data01 = "Text data at first line : " + text[0];
    string str_data02 = "File number (MF)        : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("The MF number is different to MF=35.");

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

  resize_matrix(static_cast<int>(NK));

  for(int i=0; i<static_cast<int>(NK); i++)
  {
    vector<Real> e_vec;
    mp_obj.read_list(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                     e_vec);
    E1[i] = r_vec[0];
    E2[i] = r_vec[1];
    LS[i] = i_vec[0];
    LB[i] = i_vec[1];
    NT[i] = i_vec[2];
    NE[i] = i_vec[3];

    /*if( LB[i] >= 0 && LB[i] <= 4 )
    {
      store_lb00(e_vec, i);
    }
    else if( LB[i] == 5 )
    {
      store_lb05(e_vec, i);
    }
    else if( LB[i] == 6 )
    {
      store_lb06(e_vec, i);
    }
    else if( LB[i] == 7 )
    {
      store_lb05(e_vec, i);
    }
    else if( LB[i]==8 || LB[i]==9 )
    {
      if( LS[i] != 0 )
      {
        string class_name = "MF35Parser";
        string func_name  = "store_data()";

        ostringstream oss00, oss01, oss02, oss03;
        oss00 << mt_no;
        oss01 << i;
        oss02 << static_cast<int>(NK);
        oss03 << LS[i];
        string str_data00 = "Section number (MT) : " + oss00.str();
        string str_data01 = "NK                  : " + oss01.str() + " / " + oss02.str();
        string str_data02 = "LS                  : " + oss03.str();

        vector<string> err_com;
        err_com.push_back(str_data00);
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back("IF you use LB=8 or 9, LS must be 0.");

        err_obj.output_runtime_error(class_name, func_name, err_com);
      }
      store_lb00(e_vec, i);
    }*/

    if( LB[i] == 7 )
    {
      if( LS[i] != 1 )
      {
        string class_name = "MF35Parser";
        string func_name  = "store_data()";

        ostringstream oss00, oss01, oss02, oss03;
        oss00 << mt_no;
        oss01 << i;
        oss02 << static_cast<int>(NK);
        oss03 << LS[i];
        string str_data00 = "Section number (MT) : " + oss00.str();
        string str_data01 = "NK                  : " + oss01.str() + " / " + oss02.str();
        string str_data02 = "LS                  : " + oss03.str();

        vector<string> err_com;
        err_com.push_back(str_data00);
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back("IF you use LB=7, LS must be 1.");

        err_obj.output_runtime_error(class_name, func_name, err_com);
      }
      store_lb05(e_vec, i);
    }
    else
    {
      string class_name = "MF35Parser";
      string func_name  = "store_data()";

      ostringstream oss00, oss01, oss02, oss03;
      oss00 << mt_no;
      oss01 << i;
      oss02 << static_cast<int>(NK);
      oss03 << LB[i];
      string str_data00 = "Section number (MT) : " + oss00.str();
      string str_data01 = "NK                  : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "LB                  : " + oss03.str();

      vector<string> err_com;
      err_com.push_back(str_data00);
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back("This LB value at MF=35 is not supported in this program.");
      err_com.push_back("Supported LB value is 0 - 9.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
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

void MF35Parser::store_lb00(vector<Real>& e_vec, int& i)
{
  if( NT[i]!=2*NE[i] )
  {
    string class_name = "MF35Parser";
    string func_name  = "store_lb00(vector<Real>& e_vec, int& i)";

    ostringstream oss00, oss01, oss02, oss03, oss04;
    oss00 << mt_no;
    oss01 << i;
    oss02 << static_cast<int>(NK);
    oss03 << NT[i];
    oss03 << NE[i];
    string str_data00 = "Section number (MT) : " + oss00.str();
    string str_data01 = "NK                  : " + oss01.str() + " / " + oss02.str();
    string str_data02 = "NT=2*NE             : " + oss03.str();
    string str_data03 = "NE                  : " + oss04.str();

    vector<string> err_com;
    err_com.push_back(str_data00);
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("NT is not equal to 2*NE at LB=0-4, 8-9.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  int lt_j = static_cast<int>(NE[i] - LS[i]);
  E_K[i].resize(lt_j);
  F_K[i].resize(lt_j);
  E_T[i].resize(static_cast<int>(LS[i]));
  F_T[i].resize(static_cast<int>(LS[i]));
  for(int j=0; j<lt_j; j++)
  {
    E_K[i][j] =         e_vec[2*j];
    F_K[i][j].push_back(e_vec[2*j+1]);
  }
  for(int j=0; j<static_cast<int>(LS[i]); j++)
  {
    E_T[i][j] =         e_vec[2*lt_j+2*j];
    F_T[i][j].push_back(e_vec[2*lt_j+2*j+1]);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF35Parser::store_lb05(vector<Real>& e_vec, int& i)
{
  int ne = NE[i];
  E_K[i].resize(ne);
  for(int j=0; j<ne; j++)
  {
    E_K[i][j] = e_vec[j];
  }

  if( LS[i]==0 )
  {
    if( NT[i]!=ne*(ne-1)+1 )
    {
      string class_name = "MF35Parser";
      string func_name  = "store_lb05(vector<Real>& e_vec, int& i)";

      ostringstream oss00, oss01, oss02, oss03, oss04;
      oss00 << mt_no;
      oss01 << i;
      oss02 << static_cast<int>(NK);
      oss03 << NT[i];
      oss03 << ne;
      string str_data00 = "Section number (MT) : " + oss00.str();
      string str_data01 = "NK                  : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "NT=NE(NE-1)+1       : " + oss03.str();
      string str_data03 = "NE                  : " + oss04.str();

      vector<string> err_com;
      err_com.push_back(str_data00);
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back("NT at LB=5, LS=0 is not equal to NE(NE-1)+1.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    int ele_no = ne;
    F_K[i].resize(ne-1);
    for(int j=0; j<ne-1; j++)
    {
      F_K[i][j].resize(ne-1);
      for(int k=0; k<ne-1; k++)
      {
        F_K[i][j][k] = e_vec[ele_no];
        ele_no++;
      }
    }
  }
  else if( LS[i]==1 )
  {
    if( NT[i]!=(ne*(ne+1))/2 )
    {
      string class_name = "MF35Parser";
      string func_name  = "store_lb05(vector<Real>& e_vec, int& i)";

      ostringstream oss00, oss01, oss02, oss03, oss04;
      oss00 << mt_no;
      oss01 << i;
      oss02 << static_cast<int>(NK);
      oss03 << NT[i];
      oss03 << ne;
      string str_data00 = "Section number (MT) : " + oss00.str();
      string str_data01 = "NK                  : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "NT=NE(NE-1)+1       : " + oss03.str();
      string str_data03 = "NE                  : " + oss04.str();

      vector<string> err_com;
      err_com.push_back(str_data00);
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back("NT at LB=7, LS=1 is not equal to NE(NE+1)/2.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    int ele_no = ne;
    F_K[i].resize(ne-1);
    for(int j=0; j<ne-1; j++)
    {
      int ne_d = ne-1-j;
      F_K[i][j].resize(ne_d);
      for(int k=0; k<ne_d; k++)
      {
        F_K[i][j][k] = e_vec[ele_no];
        ele_no++;
      }
    }
  }
  else
  {
    string class_name = "MF35Parser";
    string func_name  = "store_lb05(vector<Real>& e_vec, int& i)";

    ostringstream oss00, oss01, oss02, oss03;
    oss00 << mt_no;
    oss01 << i;
    oss02 << static_cast<int>(NK);
    oss03 << LS[i];
    string str_data00 = "Section number (MT) : " + oss00.str();
    string str_data01 = "NK                  : " + oss01.str() + " / " + oss02.str();
    string str_data02 = "LS                  : " + oss03.str();

    vector<string> err_com;
    err_com.push_back(str_data00);
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("This LS value at MF=35 is not supported in this program.");
    err_com.push_back("Supported LS value is 0 and 1.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF35Parser::store_lb06(vector<Real>& e_vec, int& i)
{
  int ner =  NE[i];
  int nec = (NT[i] - 1)/ner;

  if( NT[i] != 1+ner*nec )
  {
    string class_name = "MF35Parser";
    string func_name  = "store_lb06(vector<Real>& e_vec, int& i)";

    ostringstream oss00, oss01, oss02, oss03, oss04, oss05;
    oss00 << mt_no;
    oss01 << i;
    oss02 << static_cast<int>(NK);
    oss03 << NT[i];
    oss04 << ner;
    oss05 << nec;
    string str_data00 = "Section number (MT) : " + oss00.str();
    string str_data01 = "NK                  : " + oss01.str() + " / " + oss02.str();
    string str_data02 = "NT=1+NER*NEC        : " + oss03.str();
    string str_data03 = "NER                 : " + oss04.str();
    string str_data04 = "NEC                 : " + oss05.str();

    vector<string> err_com;
    err_com.push_back(str_data00);
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back("NT at LB=6 is not equal to 1+NER*NEC.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  E_K[i].resize(ner);
  for(int j=0; j<ner; j++)
  {
    E_K[i][j] = e_vec[j];
  }

  int ele_no = ner;
  E_T[i].resize(nec);
  for(int j=0; j<nec; j++)
  {
    E_T[i][j] =  e_vec[ele_no];
    ele_no++;
  }

  F_K[i].resize(ner-1);
  for(int j=0; j<ner-1; j++)
  {
    F_K[i][j].resize(nec-1);
    for(int k=0; k<nec-1; k++)
    {
      F_K[i][j][k] = e_vec[ele_no];
      ele_no++;
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF35Parser::clear()
{
  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);

  mat_no = unassigned_mat_no;
  mt_no  = unassigned_mt_no;
  ZA     = 0.0;
  AWR    = 0.0;
  NK     = 0;

  E1.clear();
  E2.clear();
  LS.clear();
  LB.clear();
  NT.clear();
  NE.clear();

  clr_vec.clear_vec_array2_real(E_K);
  clr_vec.clear_vec_array2_real(E_T);
  clr_vec.clear_vec_array3_real(F_K);
  clr_vec.clear_vec_array3_real(F_T);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF35Parser::resize_matrix(int i_max)
{
  E1.resize(i_max);
  E2.resize(i_max);
  LS.resize(i_max);
  LB.resize(i_max);
  NT.resize(i_max);
  NE.resize(i_max);

  E_K.resize(i_max);
  F_K.resize(i_max);

  E_T.resize(i_max);
  F_T.resize(i_max);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF35Parser::set_text(vector<string> text_data)
{
  clear();

  text = text_data;
  store_data();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string>                 MF35Parser::get_text()
{
  return text;
}

Integer                        MF35Parser::get_mat_no()
{
  return mat_no;
}

Integer                        MF35Parser::get_mt_no()
{
  return mt_no;
}


Real                           MF35Parser::get_ZA()
{
  return ZA;
}

Real                           MF35Parser::get_AWR()
{
  return AWR;
}

Integer                        MF35Parser::get_NK()
{
  return NK;
}


vector<Real>                   MF35Parser::get_E1()
{
  return E1;
}

vector<Real>                   MF35Parser::get_E2()
{
  return E2;
}

vector<Integer>                MF35Parser::get_LS()
{
  return LS;
}

vector<Integer>                MF35Parser::get_LB()
{
  return LB;
}

vector<Integer>                MF35Parser::get_NT()
{
  return NT;
}

vector<Integer>                MF35Parser::get_NE()
{
  return NE;
}


vector<vector<Real> >          MF35Parser::get_E_K()
{
  return E_K;
}

vector<vector<vector<Real> > > MF35Parser::get_F_K()
{
  return F_K;
}

vector<vector<Real> >          MF35Parser::get_E_T()
{
  return E_T;
}

vector<vector<vector<Real> > > MF35Parser::get_F_T()
{
  return F_T;
}


vector<vector<Real> >          MF35Parser::get_E_K_NER()
{
  return E_K;
}

vector<vector<Real> >          MF35Parser::get_E_K_NEC()
{
  return E_T;
}


////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void MF35Parser::set_mat_no(Integer& int_data)
{
  mat_no = int_data;
}

void MF35Parser::set_mt_no(Integer& int_data)
{
  mt_no = int_data;
}

void MF35Parser::set_ZA(Real& real_data)
{
  ZA = real_data;
}

void MF35Parser::set_AWR(Real& real_data)
{
  AWR = real_data;
}

void MF35Parser::set_NK(Integer& int_data)
{
  NK = int_data;
}

void MF35Parser::set_E1(vector<Real>& real_vec)
{
  E1 = real_vec;
}

void MF35Parser::set_E2(vector<Real>& real_vec)
{
  E2 = real_vec;
}

void MF35Parser::set_LS(vector<Integer>& int_vec)
{
  LS = int_vec;
}

void MF35Parser::set_LB(vector<Integer>& int_vec)
{
  LB = int_vec;
}

void MF35Parser::set_NT(vector<Integer>& int_vec)
{
  NT = int_vec;
}

void MF35Parser::set_NE(vector<Integer>& int_vec)
{
  NE = int_vec;
}

void MF35Parser::set_E_K(vector<vector<Real> >& real_vec)
{
  E_K = real_vec;
}

void MF35Parser::set_F_K(vector<vector<vector<Real> > >& real_vec)
{
  F_K = real_vec;
}

