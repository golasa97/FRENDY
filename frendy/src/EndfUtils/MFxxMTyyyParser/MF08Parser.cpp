#include "EndfUtils/MFxxMTyyyParser/MF08Parser.hpp"

using namespace frendy;

//constructor
MF08Parser::MF08Parser(void)
{
  clear();

  err_obj.set_output_mode(err_obj.warning_off);
}

//destructor
MF08Parser::~MF08Parser(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF08Parser::store_data()
{
  MultiParser mp_obj;

  //Text file data check
  if( static_cast<Integer>(text.size()) < 1 )
  {
    string class_name = "MF08Parser";
    string func_name  = "store_data()";

    ostringstream oss;
    oss << static_cast<Integer>(text.size());
    string str_data = "Text line number : " + oss.str();

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("The text line number is not appropriate for MF=08.");
    err_com.push_back("The text line number should be larger than 1.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //Check MF number
  if( mp_obj.check_mf(text, mf_no) != 0)
  {
    string class_name = "MF08Parser";
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

  //Get MT number
  mp_obj.get_mf_mt(text, i_vec[0], mt_no);
  if( mt_no == 454 || mt_no == 457 || mt_no == 459 )
  {
    string class_name = "MF08Parser";
    string func_name  = "store_data()";

    ostringstream oss01;
    oss01 << mt_no;
    string str_data01 = "Text data at first line : " + text[0];
    string str_data02 = "Section number (MT)     : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    if( mt_no == 454 )
    {
      err_com.push_back("This MT number is not supported in this class, please use MT08MF454Parser class.");
    }
    else if( mt_no == 459 )
    {
      err_com.push_back("This MT number is not supported in this class, please use MT08MF459Parser class.");
    }
    else if( mt_no == 457 )
    {
      err_com.push_back("This MT number is not supported in this class, please use MT08MF457Parser class.");
    }
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //Line No.01
  //ZA, AWR, LIS, LISO, NS, NO
  mp_obj.read_head(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3]);
  ZA   = r_vec[0];
  AWR  = r_vec[1];
  LIS  = i_vec[0];
  LISO = i_vec[1];
  NS   = i_vec[2];
  NO   = i_vec[3];

  if( NO == 0 )
  {
    int ns = static_cast<int>(NS);
    ZAP.resize(ns);
    ELFS.resize(ns);
    LMF.resize(ns);
    LFS.resize(ns);

    HL.resize(ns);
    RTYP.resize(ns);
    ZAN.resize(ns);
    BR.resize(ns);
    END.resize(ns);
    CT.resize(ns);

    for(int i=0; i<ns; i++)
    {
      vector<Real> e_vec;
      mp_obj.read_list(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                       e_vec);
      ZAP[i]  = r_vec[0];
      ELFS[i] = r_vec[1];
      LMF[i]  = i_vec[0];
      LFS[i]  = i_vec[1];

      if( i_vec[2] % 6 != 0)
      {
        string class_name = "MF08Parser";
        string func_name  = "store_data()";

        ostringstream oss00, oss01, oss02, oss03;
        oss00 << mt_no;
        oss01 << i;
        oss02 << ns;
        oss03 << i_vec[2];
        string str_data00 = "Section number (MT) : " + oss00.str();
        string str_data01 = "NS                  : " + oss01.str() + " / " + oss02.str();
        string str_data02 = "6*ND                : " + oss03.str();

        vector<string> err_com;
        err_com.push_back(str_data00);
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back("The number of 6*ND must be multiple of 6.");

        err_obj.output_runtime_error(class_name, func_name, err_com);
      }

      int j_max = static_cast<int>(e_vec.size())/6;
      HL[i].resize(j_max);
      RTYP[i].resize(j_max);
      ZAN[i].resize(j_max);
      BR[i].resize(j_max);
      END[i].resize(j_max);
      CT[i].resize(j_max);
      for(int j=0; j<j_max; j++)
      {
        HL[i][j]   = e_vec[6*j+0];
        RTYP[i][j] = e_vec[6*j+1];
        ZAN[i][j]  = e_vec[6*j+2];
        BR[i][j]   = e_vec[6*j+3];
	END[i][j]  = e_vec[6*j+4];
        CT[i][j]   = e_vec[6*j+5];
      }
      e_vec.clear();
    }
  }
  else if( NO == 1 )
  {
    int ns = static_cast<int>(NS);
    ZAP.resize(ns);
    ELFS.resize(ns);
    LMF.resize(ns);
    LFS.resize(ns);

    for(int i=0; i<ns; i++)
    {
      mp_obj.read_cont(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3]);

      ZAP[i]  = r_vec[0];
      ELFS[i] = r_vec[1];
      LMF[i]  = i_vec[0];
      LFS[i]  = i_vec[1];
    }
  }
  else
  {
    string class_name = "MF08Parser";
    string func_name  = "store_data()";

    ostringstream oss00, oss01;
    oss00 << mt_no;
    oss01 << NO;
    string str_data00 = "Section number (MT) : " + oss00.str();
    string str_data01 = "NO                  : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data00);
    err_com.push_back(str_data01);
    err_com.push_back("This NO value at MF=08 is not supported in this program.");
    err_com.push_back("Supported NO value is 0 and 1.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
  r_vec.clear();
  i_vec.clear();

  mp_obj.line_no_check(text, line_no, mf_no, mt_no);

  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF08Parser::clear()
{
  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);

  mat_no = unassigned_mat_no;
  mt_no  = unassigned_mt_no;
  ZA     = 0.0;
  AWR    = 0.0;
  LIS    = 0;
  LISO   = 0;
  NS     = 0;
  NO     = 0;

  ZAP.clear();
  ELFS.clear();
  LMF.clear();
  LFS.clear();

  clr_vec.clear_vec_array2_real(HL);
  clr_vec.clear_vec_array2_real(RTYP);
  clr_vec.clear_vec_array2_real(ZAN);
  clr_vec.clear_vec_array2_real(BR);
  clr_vec.clear_vec_array2_real(END);
  clr_vec.clear_vec_array2_real(CT);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF08Parser::set_text(vector<string> text_data)
{
  clear();

  text = text_data;
  store_data();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string>        MF08Parser::get_text()
{
  return text;
}

Integer               MF08Parser::get_mat_no()
{
  return mat_no;
}

Integer               MF08Parser::get_mt_no()
{
  return mt_no;
}


Real                  MF08Parser::get_ZA()
{
  return ZA;
}

Real                  MF08Parser::get_AWR()
{
  return AWR;
}

Integer               MF08Parser::get_LIS()
{
  return LIS;
}

Integer               MF08Parser::get_LISO()
{
  return LISO;
}

Integer               MF08Parser::get_NS()
{
  return NS;
}

Integer               MF08Parser::get_NO()
{
  return NO;
}


vector<Real>          MF08Parser::get_ZAP()
{
  return ZAP;
}

vector<Real>          MF08Parser::get_ELFS()
{
  return ELFS;
}

vector<Integer>       MF08Parser::get_LMF()
{
  return LMF;
}

vector<Integer>       MF08Parser::get_LFS()
{
  return LFS;
}

vector<vector<Real> > MF08Parser::get_HL()
{
  return HL;
}

vector<vector<Real> > MF08Parser::get_RTYP()
{
  return RTYP;
}

vector<vector<Real> > MF08Parser::get_ZAN()
{
  return ZAN;
}

vector<vector<Real> > MF08Parser::get_BR()
{
  return BR;
}

vector<vector<Real> > MF08Parser::get_END()
{
  return END;
}

vector<vector<Real> > MF08Parser::get_CT()
{
  return CT;
}



////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void MF08Parser::set_mat_no(Integer& int_data)
{
  mat_no = int_data;
}

void MF08Parser::set_mt_no(Integer& int_data)
{
  mt_no = int_data;
}

void MF08Parser::set_ZA(Real& real_data)
{
  ZA = real_data;
}

void MF08Parser::set_AWR(Real& real_data)
{
  AWR = real_data;
}

void MF08Parser::set_LIS(Integer& int_data)
{
  LIS = int_data;
}

void MF08Parser::set_LISO(Integer& int_data)
{
  LISO = int_data;
}

void MF08Parser::set_NS(Integer& int_data)
{
  NS = int_data;
}

void MF08Parser::set_NO(Integer& int_data)
{
  NO = int_data;
}

void MF08Parser::set_ZAP(vector<Real>& real_vec)
{
  ZAP = real_vec;
}

void MF08Parser::set_ELFS(vector<Real>& real_vec)
{
  ELFS = real_vec;
}

void MF08Parser::set_LMF(vector<Integer>& int_vec)
{
  LMF = int_vec;
}

void MF08Parser::set_LFS(vector<Integer>& int_vec)
{
  LFS = int_vec;
}

void MF08Parser::set_HL(vector<vector<Real> >& real_vec)
{
  HL = real_vec;
}

void MF08Parser::set_RTYP(vector<vector<Real> >& real_vec)
{
  RTYP = real_vec;
}

void MF08Parser::set_ZAN(vector<vector<Real> >& real_vec)
{
  ZAN = real_vec;
}

void MF08Parser::set_BR(vector<vector<Real> >& real_vec)
{
  BR = real_vec;
}

void MF08Parser::set_END(vector<vector<Real> >& real_vec)
{
  END = real_vec;
}

void MF08Parser::set_CT(vector<vector<Real> >& real_vec)
{
  CT = real_vec;
}

