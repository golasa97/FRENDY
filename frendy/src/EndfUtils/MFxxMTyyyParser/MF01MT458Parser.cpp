#include "EndfUtils/MFxxMTyyyParser/MF01MT458Parser.hpp"

using namespace frendy;

//constructor
MF01MT458Parser::MF01MT458Parser(void)
{
  clear();

  err_obj.set_output_mode(err_obj.warning_off);
}

//destructor
MF01MT458Parser::~MF01MT458Parser(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF01MT458Parser::store_data()
{
  //Text file data check
  if( static_cast<Integer>(text.size()) < 2 )
  {
    string class_name = "MF01MT458Parser";
    string func_name  = "store_data()";

    ostringstream oss;
    oss << static_cast<Integer>(text.size());
    string str_data = "Text line number : " + oss.str();

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("The text line number is not appropriate for  MF=01, MT=458.");
    err_com.push_back("The text line number should be larger than 1.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //Check MT and MF number
  if( mp_obj.check_mf_mt(text, mf_no, mt_no) != 0)
  {
    string class_name = "MF01MT458Parser";
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
    err_com.push_back("The MF and MT numbers are different to MF=01, MT=458.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  mp_obj.get_mat(text, mat_no);

  line_no = 0;
  Integer tmp_int;

  //Line No.01
  //ZA, AWR
  mp_obj.read_head(text, line_no, ZA, AWR, tmp_int, LFC, tmp_int, NFC);

  if( LFC == 0 )
  {
    store_polynomial_evaluation();
  }
  else if( LFC == 1 )
  {
    store_polynomial_evaluation();
    store_tabular_evaluation();
  }
  else
  {
    string class_name = "MF01MT458Parser";
    string func_name  = "store_data()";

    ostringstream oss01;
    oss01 << LFC;
    string str_data01 = "Data reperesentation (LFC) : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("LFC is only available for LFC=0 (polynomial distribution)");
    err_com.push_back("or LFC=1 (tabulated distribution).");
    err_com.push_back("Please check LFC value.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  mp_obj.line_no_check(text, line_no, mf_no, mt_no);

  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF01MT458Parser::store_polynomial_evaluation()
{
  //Line No.02
  //NPLY, N1, N2
  Integer tmp_int;
  Real    tmp_real;
  vector<Real> real_data;
  real_data.clear();
  mp_obj.read_list(text, line_no, tmp_real, tmp_real, tmp_int, NPLY, N1, N2, real_data);

  if( LFC == 1 )
  {
    if( NPLY != 0 )
    {
      string class_name = "MF01MT458Parser";
      string func_name  = "store_polynomial_evaluation()";

      ostringstream oss01;
      oss01 << NPLY;
      string str_data01 = "NPLY : " + oss01.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back("NPLY=0 is only available when LFC=1 (tabulated distribution).");
      err_com.push_back("Please check line2 at MF=01, MT=458.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }

  if( N1 != 18*(NPLY+1) )
  {
    string class_name = "MF01MT458Parser";
    string func_name  = "store_polynomial_evaluation()";

    ostringstream oss01, oss02;
    oss01 << N1;
    oss02 << NPLY;
    string str_data01 = "N1   : " + oss01.str();
    string str_data02 = "NPLY : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("N1 is not equal to 18*(NPLY+1).");
    err_com.push_back("Please check line2 at MF=01, MT=458.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  if( N2 != 9*(NPLY+1) )
  {
    string class_name = "MF01MT458Parser";
    string func_name  = "store_polynomial_evaluation()";

    ostringstream oss01, oss02;
    oss01 << N2;
    oss02 << NPLY;
    string str_data01 = "N2   : " + oss01.str();
    string str_data02 = "NPLY : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("N2 is not equal to 9*(NPLY+1).");
    err_com.push_back("Please check line2 at MF=01, MT=458.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  set_energy_independent_data(NPLY, real_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF01MT458Parser::set_energy_independent_data(Integer NPLY, vector<Real>& real_data)
{
  int npl = static_cast<int>(NPLY+1);
  EFR.resize(npl);
  ENP.resize(npl);
  END.resize(npl);
  EGP.resize(npl);
  EGD.resize(npl);
  EB.resize(npl);
  ENU.resize(npl);
  ER.resize(npl);
  ET.resize(npl);

  D_EFR.resize(npl);
  D_ENP.resize(npl);
  D_END.resize(npl);
  D_EGP.resize(npl);
  D_EGD.resize(npl);
  D_EB.resize(npl);
  D_ENU.resize(npl);
  D_ER.resize(npl);
  D_ET.resize(npl);
  for(int i=0; i<npl; i++)
  {
    Integer j=i*18;
    EFR[i] = real_data[j+ 0];
    ENP[i] = real_data[j+ 2];
    END[i] = real_data[j+ 4];
    EGP[i] = real_data[j+ 6];
    EGD[i] = real_data[j+ 8];
    EB[i] =  real_data[j+10];
    ENU[i] = real_data[j+12];
    ER[i] =  real_data[j+14];
    ET[i] =  real_data[j+16];

    D_EFR[i] = real_data[j+ 1];
    D_ENP[i] = real_data[j+ 3];
    D_END[i] = real_data[j+ 5];
    D_EGP[i] = real_data[j+ 7];
    D_EGD[i] = real_data[j+ 9];
    D_EB[i] =  real_data[j+11];
    D_ENU[i] = real_data[j+13];
    D_ER[i] =  real_data[j+15];
    D_ET[i] =  real_data[j+17];
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF01MT458Parser::store_tabular_evaluation()
{
  int i_max = static_cast<int>(NFC);
  LDRV.resize(i_max);
  IFC.resize(i_max);
  NBT_EIFC.resize(i_max);
  INT_EIFC.resize(i_max);
  E_INT_EIFC.resize(i_max);
  EIFC_TAB.resize(i_max);
  for(int i=0; i<static_cast<int>(NFC); i++)
  {
    //Line No.03
    //LDRV, IFC, EIFC(E)
    Real    tmp_real;
    Integer NR, NP;
    mp_obj.read_tab1(text, line_no, tmp_real, tmp_real, LDRV[i], IFC[i], NR, NP,
                     NBT_EIFC[i], INT_EIFC[i], E_INT_EIFC[i], EIFC_TAB[i]);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF01MT458Parser::clear()
{
  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);

  line_no = 0;

  mat_no = unassigned_mat_no;
  ZA     = 0;
  AWR    = 0.0;
  LFC    = 0;
  NFC    = 0;
  NPLY   = 0;
  N1     = 0;
  N2     = 0;
  D_EFR.clear();
  D_ENP.clear();
  D_END.clear();
  D_EGP.clear();
  D_EGD.clear();
  D_EB.clear();
  D_ENU.clear();
  D_ER.clear();
  D_ET.clear();
  EFR.clear();
  ENP.clear();
  END.clear();
  EGP.clear();
  EGD.clear();
  EB.clear();
  ENU.clear();
  ER.clear();
  ET.clear();

  LDRV.clear();
  IFC.clear();
  clr_vec.clear_vec_array2_int(NBT_EIFC);
  clr_vec.clear_vec_array2_int(INT_EIFC);
  clr_vec.clear_vec_array2_real(E_INT_EIFC);
  clr_vec.clear_vec_array2_real(EIFC_TAB);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF01MT458Parser::set_text(vector<string> text_data)
{
  clear();

  text = text_data;
  store_data();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> MF01MT458Parser::get_text()
{
  return text;
}

Integer MF01MT458Parser::get_mat_no()
{
  return mat_no;
}

//Getter at line No.01
Real MF01MT458Parser::get_ZA()
{
  return ZA;
}

Real MF01MT458Parser::get_AWR()
{
  return AWR;
}

Integer MF01MT458Parser::get_LFC()
{
  return LFC;
}

Integer MF01MT458Parser::get_NFC()
{
  return NFC;
}

//Getter at line No.02
Integer MF01MT458Parser::get_NPLY()
{
  return NPLY;
}

Integer MF01MT458Parser::get_N1()
{
  return N1;
}

Integer MF01MT458Parser::get_N2()
{
  return N2;
}

vector<Real> MF01MT458Parser::get_EFR()
{
  return EFR;
}

vector<Real> MF01MT458Parser::get_ENP()
{
  return ENP;
}

vector<Real> MF01MT458Parser::get_END()
{
  return END;
}

vector<Real> MF01MT458Parser::get_EGP()
{
  return EGP;
}

vector<Real> MF01MT458Parser::get_EGD()
{
  return EGD;
}

vector<Real> MF01MT458Parser::get_EB()
{
  return EB;
}

vector<Real> MF01MT458Parser::get_ENU()
{
  return ENU;
}

vector<Real> MF01MT458Parser::get_ER()
{
  return ER;
}

vector<Real> MF01MT458Parser::get_ET()
{
  return ET;
}

vector<Real> MF01MT458Parser::get_D_EFR()
{
  return D_EFR;
}

vector<Real> MF01MT458Parser::get_D_ENP()
{
  return D_ENP;
}

vector<Real> MF01MT458Parser::get_D_END()
{
  return D_END;
}

vector<Real> MF01MT458Parser::get_D_EGP()
{
  return D_EGP;
}

vector<Real> MF01MT458Parser::get_D_EGD()
{
  return D_EGD;
}

vector<Real> MF01MT458Parser::get_D_EB()
{
  return D_EB;
}

vector<Real> MF01MT458Parser::get_D_ENU()
{
  return D_ENU;
}

vector<Real> MF01MT458Parser::get_D_ER()
{
  return D_ER;
}

vector<Real> MF01MT458Parser::get_D_ET()
{
  return D_ET;
}

//Getter at line No.03
vector<Integer>          MF01MT458Parser::get_LDRV()
{
  return LDRV;
}

vector<Integer>          MF01MT458Parser::get_IFC()
{
  return IFC;
}

vector<vector<Integer> > MF01MT458Parser::get_NBT_EIFC()
{
  return NBT_EIFC;
}

vector<vector<Integer> > MF01MT458Parser::get_INT_EIFC()
{
  return INT_EIFC;
}

vector<vector<Real> >    MF01MT458Parser::get_E_INT_EIFC()
{
  return E_INT_EIFC;
}

vector<vector<Real> >    MF01MT458Parser::get_EIFC_TAB()
{
  return EIFC_TAB;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void MF01MT458Parser::set_mat_no(Integer& int_data)
{
  mat_no = int_data;
}

void MF01MT458Parser::set_ZA(Real& real_data)
{
  ZA = real_data;
}

void MF01MT458Parser::set_AWR(Real& real_data)
{
  AWR = real_data;
}

void MF01MT458Parser::set_LFC(Integer& int_data)
{
  LFC = int_data;
}

void MF01MT458Parser::set_NFC(Integer& int_data)
{
  NFC = int_data;
}

void MF01MT458Parser::set_NPLY(Integer& int_data)
{
  NPLY = int_data;
}

void MF01MT458Parser::set_N1(Integer& int_data)
{
  N1 = int_data;
}

void MF01MT458Parser::set_N2(Integer& int_data)
{
  N2 = int_data;
}

void MF01MT458Parser::set_EFR(vector<Real>& real_vec)
{
  EFR = real_vec;
}

void MF01MT458Parser::set_ENP(vector<Real>& real_vec)
{
  ENP = real_vec;
}

void MF01MT458Parser::set_END(vector<Real>& real_vec)
{
  END = real_vec;
}

void MF01MT458Parser::set_EGP(vector<Real>& real_vec)
{
  EGP = real_vec;
}

void MF01MT458Parser::set_EGD(vector<Real>& real_vec)
{
  EGD = real_vec;
}

void MF01MT458Parser::set_EB(vector<Real>& real_vec)
{
  EB = real_vec;
}

void MF01MT458Parser::set_ENU(vector<Real>& real_vec)
{
  ENU = real_vec;
}

void MF01MT458Parser::set_ER(vector<Real>& real_vec)
{
  ER = real_vec;
}

void MF01MT458Parser::set_ET(vector<Real>& real_vec)
{
  ET = real_vec;
}

void MF01MT458Parser::set_D_EFR(vector<Real>& real_vec)
{
  D_EFR = real_vec;
}

void MF01MT458Parser::set_D_ENP(vector<Real>& real_vec)
{
  D_ENP = real_vec;
}

void MF01MT458Parser::set_D_END(vector<Real>& real_vec)
{
  D_END = real_vec;
}

void MF01MT458Parser::set_D_EGP(vector<Real>& real_vec)
{
  D_EGP = real_vec;
}

void MF01MT458Parser::set_D_EGD(vector<Real>& real_vec)
{
  D_EGD = real_vec;
}

void MF01MT458Parser::set_D_EB(vector<Real>& real_vec)
{
  D_EB = real_vec;
}

void MF01MT458Parser::set_D_ENU(vector<Real>& real_vec)
{
  D_ENU = real_vec;
}

void MF01MT458Parser::set_D_ER(vector<Real>& real_vec)
{
  D_ER = real_vec;
}

void MF01MT458Parser::set_D_ET(vector<Real>& real_vec)
{
  D_ET = real_vec;
}

void MF01MT458Parser::set_LDRV(vector<Integer>& int_vec)
{
  LDRV = int_vec;
}

void MF01MT458Parser::set_IFC(vector<Integer>& int_vec)
{
  IFC = int_vec;
}

void MF01MT458Parser::set_NBT_EIFC(vector<vector<Integer> >& int_vec)
{
  NBT_EIFC = int_vec;
}

void MF01MT458Parser::set_INT_EIFC(vector<vector<Integer> >& int_vec)
{
  INT_EIFC = int_vec;
}

void MF01MT458Parser::set_E_INT_EIFC(vector<vector<Real> >& real_vec)
{
  E_INT_EIFC = real_vec;
}

void MF01MT458Parser::set_EIFC_TAB(vector<vector<Real> >& real_vec)
{
  EIFC_TAB = real_vec;
}

