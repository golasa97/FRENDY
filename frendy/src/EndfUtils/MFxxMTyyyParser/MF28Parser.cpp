#include "EndfUtils/MFxxMTyyyParser/MF28Parser.hpp"

using namespace frendy;

//constructor
MF28Parser::MF28Parser(void)
{
  clear();

  err_obj.set_output_mode(err_obj.warning_off);
}

//destructor
MF28Parser::~MF28Parser(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF28Parser::store_data()
{
  MultiParser mp_obj;

  //Text file data check
  if( static_cast<Integer>(text.size()) < 2 )
  {
    string class_name = "MF28Parser";
    string func_name  = "store_data()";

    ostringstream oss;
    oss << static_cast<Integer>(text.size());
    string str_data = "Text line number : " + oss.str();

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("The text line number is not appropriate for MF=28.");
    err_com.push_back("The text line number should be larger than 1.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //Check MF number
  if( mp_obj.check_mf(text, mf_no) != 0)
  {
    string class_name = "MF28Parser";
    string func_name  = "store_data()";

    ostringstream oss01;
    oss01 << mf_no;
    string str_data01 = "Text data at first line : " + text[0];
    string str_data02 = "File number (MF)        : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("The MF number is different to MF=28.");

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
  if( mt_no < 533 || mt_no > 599 )
  {
    string class_name = "MF28Parser";
    string func_name  = "store_data()";

    ostringstream oss01;
    oss01 << mt_no;
    string str_data01 = "Section number (MT) : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("The MT number of MF=28 is only applicable from 533 to 599.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //Line No.01
  //ZA, AWR, NSS
  mp_obj.read_head(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3]);
  ZA  = r_vec[0];
  AWR = r_vec[1];
  NSS = i_vec[2];

  int nss = static_cast<int>(NSS);
  SUBI.resize(nss);
  EBI.resize(nss);
  ELN.resize(nss);

  SUBJ.resize(nss);
  SUBK.resize(nss);
  ETR.resize( nss);
  FTR.resize( nss);

  for(int i=0; i<nss; i++)
  {
    vector<Real> e_vec;
    mp_obj.read_list(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                     e_vec);
    if( i_vec[2] != 6*(1+i_vec[3]) )
    {
      string class_name = "MF28Parser";
      string func_name  = "store_data()";

      ostringstream oss00, oss01, oss02, oss03, oss04;
      oss00 << mt_no;
      oss01 << i;
      oss02 << nss;
      oss03 << i_vec[2];
      oss04 << i_vec[3];
      string str_data00 = "Section number (MT) : " + oss00.str();
      string str_data01 = "NSS                 : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "6*(1+NTR)           : " + oss03.str();
      string str_data03 = "NTR                 : " + oss04.str();

      vector<string> err_com;
      err_com.push_back(str_data00);
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back("NW is not equal to 6*(1+NTR).");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    SUBI[i] = r_vec[0];
    EBI[i]  = e_vec[0];
    ELN[i]  = e_vec[1];

    int ntr = static_cast<int>(i_vec[3]);
    SUBJ[i].resize(ntr);
    SUBK[i].resize(ntr);
    ETR[i].resize( ntr);
    FTR[i].resize( ntr);
    for(int j=0; j<ntr; j++)
    {
      SUBJ[i][j] = e_vec[6*(j+1)+0];
      SUBK[i][j] = e_vec[6*(j+1)+1];
      ETR[i][j]  = e_vec[6*(j+1)+2];
      FTR[i][j]  = e_vec[6*(j+1)+3];
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

void MF28Parser::clear()
{
  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);

  mat_no = unassigned_mat_no;
  mt_no  = unassigned_mt_no;
  ZA     = 0.0;
  AWR    = 0.0;
  NSS    = 0;

  SUBI.clear();
  EBI.clear();
  ELN.clear();

  clr_vec.clear_vec_array2_real(SUBJ);
  clr_vec.clear_vec_array2_real(SUBK);
  clr_vec.clear_vec_array2_real(ETR);
  clr_vec.clear_vec_array2_real(FTR);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF28Parser::set_text(vector<string> text_data)
{
  clear();

  text = text_data;
  store_data();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string>        MF28Parser::get_text()
{
  return text;
}

Integer               MF28Parser::get_mat_no()
{
  return mat_no;
}

Integer               MF28Parser::get_mt_no()
{
  return mt_no;
}

Real                  MF28Parser::get_ZA()
{
  return ZA;
}

Real                  MF28Parser::get_AWR()
{
  return AWR;
}

Integer               MF28Parser::get_NSS()
{
  return NSS;
}

vector<Real>          MF28Parser::get_SUBI()
{
  return SUBI;
}

vector<Real>          MF28Parser::get_EBI()
{
  return EBI;
}

vector<Real>          MF28Parser::get_ELN()
{
  return ELN;
}

vector<vector<Real> > MF28Parser::get_SUBJ()
{
  return SUBJ;
}

vector<vector<Real> > MF28Parser::get_SUBK()
{
  return SUBK;
}

vector<vector<Real> > MF28Parser::get_ETR()
{
  return ETR;
}

vector<vector<Real> > MF28Parser::get_FTR()
{
  return FTR;
}


////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void MF28Parser::set_mat_no(Integer& int_data)
{
  mat_no = int_data;
}

void MF28Parser::set_mt_no(Integer& int_data)
{
  mt_no = int_data;
}

void MF28Parser::set_ZA(Real& real_data)
{
  ZA = real_data;
}

void MF28Parser::set_AWR(Real& real_data)
{
  AWR = real_data;
}

void MF28Parser::set_NSS(Integer& int_data)
{
  NSS = int_data;
}

void MF28Parser::set_SUBI(vector<Real>& real_vec)
{
  SUBI = real_vec;
}

void MF28Parser::set_EBI(vector<Real>& real_vec)
{
  EBI = real_vec;
}

void MF28Parser::set_ELN(vector<Real>& real_vec)
{
  ELN = real_vec;
}

void MF28Parser::set_SUBJ(vector<vector<Real> >& real_vec)
{
  SUBJ = real_vec;
}

void MF28Parser::set_SUBK(vector<vector<Real> >& real_vec)
{
  SUBK = real_vec;
}

void MF28Parser::set_ETR(vector<vector<Real> >& real_vec)
{
  ETR = real_vec;
}

void MF28Parser::set_FTR(vector<vector<Real> >& real_vec)
{
  FTR = real_vec;
}

