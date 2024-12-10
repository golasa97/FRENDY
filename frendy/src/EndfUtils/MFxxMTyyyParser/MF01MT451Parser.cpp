#include "EndfUtils/MFxxMTyyyParser/MF01MT451Parser.hpp"

using namespace frendy;

//constructor
MF01MT451Parser::MF01MT451Parser(void)
{
  clear();

  err_obj.set_output_mode(err_obj.warning_off);
}

//destructor
MF01MT451Parser::~MF01MT451Parser(void)
{ 
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF01MT451Parser::store_data() 
{
  MultiParser mp_obj;

  //Text file data check
  if( static_cast<Integer>(text.size()) < 5 )
  {
    string class_name = "MF01MT451Parser";
    string func_name  = "store_data()";

    ostringstream oss;
    oss << static_cast<Integer>(text.size());
    string str_data = "Text line number : " + oss.str();

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("The text line number is not appropriate for  MF=01, MT=451.");
    err_com.push_back("The text line number should be larger than 5.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //Check MT and MF number
  if( mp_obj.check_mf_mt(text, mf_no, mt_no) != 0)
  {
    string class_name = "MF01MT451Parser";
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
    err_com.push_back("The MF and MT numbers are different to MF=01, MT=451.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  mp_obj.get_mat(text, mat_no);

  int     line_no = 0;
  Integer tmp_int;
  Real    tmp_real;
  string  tmp_str;

  //Line No.01
  //ZA, AWR, LRP, LFI, NLIB, NMOD
  mp_obj.read_head(text, line_no, ZA, AWR, LRP, LFI, NLIB, NMOD);  
  if( NLIB == -1 ) //For GENDF
  {
    string class_name = "MF01MT451Parser";
    string func_name  = "store_data()";

    ostringstream oss01;
    oss01 << NLIB;
    string str_data01 = "NLIB : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("This file is the GENDF formatted file.");
    err_com.push_back("TEMP data is only parsed.");

    //err_obj.output_caution(class_name, func_name, err_com);

    vector<Real> e_vec;
    mp_obj.read_list(text, line_no, TEMP, tmp_real, tmp_int, tmp_int, tmp_int, tmp_int,
                     e_vec);
    VectorClearer clr_vec;
    clr_vec.clear_vec_array1_str(text);

    return;
  }

  //Line No.02
  //ELIS, STA, LIS, LISO, 0, NFOR
  mp_obj.read_cont(text, line_no, ELIS, tmp_real, LIS, LISO, tmp_int, NFOR);
  STA = static_cast<Integer>(tmp_real);
  if( NFOR < 6 )
  {
    string class_name = "MF01MT451Parser";
    string func_name  = "store_data()";

    ostringstream oss01;
    oss01 << NFOR;
    string str_data01 = "NFOR             : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("This format number may not available in this program.");
    err_com.push_back("The processing method may be incorrect.");
    err_com.push_back("");
    err_com.push_back("This format type data does not include AWI (mass of projectile).");
    err_com.push_back("This program considers that AWI=1.0 and NSUB=10.");
    err_com.push_back("");
    err_com.push_back("Please check the processing results.");

    err_obj.output_caution(class_name, func_name, err_com);
  }

  if( NFOR >= 6 ) //For ENDF-6 format
  {
    //Line No.03
    //AWI, EMAX, LREL, 0, NSUB, NVER
    mp_obj.read_cont(text, line_no, AWI, EMAX, LREL, tmp_int, NSUB, NVER);
  }
  else
  {
    AWI  = 1.000000; //for neutron induced reaction
    NSUB = 10;       //for neutron induced reaction
  }

  //Line No.04
  //TEMP, ERROR, LDRV, 0, NWD, NXC
  mp_obj.read_cont(text, line_no, TEMP, ERROR, LDRV, tmp_int, NWD, NXC);

  comment_line.resize(static_cast<int>(NWD));

  int add_line_no = 4;
  if( NFOR < 6 ) //For ENDF-5 format
  {
    add_line_no = 3;
  }
  if(NWD + NXC + add_line_no > static_cast<Integer>(text.size()))
  {
    string class_name = "MF01MT451Parser";
    string func_name  = "store_data()";

    ostringstream oss01, oss02, oss03, oss04, oss05;
    oss01 << NWD;
    oss02 << NXC;
    oss03 << static_cast<Integer>(text.size());
    oss04 << add_line_no;
    oss05 << NWD + NXC + add_line_no;
    string str_data01 = "NWD              : " + oss01.str();
    string str_data02 = "NXC              : " + oss02.str();
    string str_data03 = "Text line number : " + oss03.str();
    string str_data04 = "NWD + NXC + " + oss04.str() + "    : " + oss05.str();
    string str_data05 = "MF=01, MT=451 line no is smaller than NWD+NXC+" + oss04.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back(str_data05);

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  if( NWD > 0 )
  {
    //Line No.05
    //ZSYMAM, ALAB, EDATE, AUTH
    mp_obj.read_text(text, line_no, tmp_str);
    comment_line[0] = tmp_str.substr( 0,66);
    ZSYMAM = tmp_str.substr( 0,11);
    ALAB   = tmp_str.substr(11,11);
    EDATE  = tmp_str.substr(22,10);
    AUTH   = tmp_str.substr(33,33);
  }

  if( NWD > 1 )
  {
    if( NFOR >= 6 ) //For ENDF-6 format
    {
      //Line No.06
      //REF, DDATE, RDATE, ENDATE
      mp_obj.read_text(text, line_no, tmp_str);
      comment_line[1] = tmp_str.substr( 0,66);
      REF    = tmp_str.substr( 1,21);
      DDATE  = tmp_str.substr(22,10);
      RDATE  = tmp_str.substr(33,10);
      ENDATE = tmp_str.substr(55, 8);
    }
    else //For ENDF-5 format
    {
      //Line No.06
      //REF, DDATE, RDATE, ENDATE
      mp_obj.read_text(text, line_no, tmp_str);
      comment_line[1] = tmp_str.substr( 0,66);
      REF    = tmp_str.substr( 1,21);
      DDATE  = tmp_str.substr(22,10);
      RDATE  = tmp_str.substr(33,10);
      ENDATE = tmp_str.substr(44, 8);
    }
  }

  if( NWD > 2 )
  {
    //Line No.07
    //HSUB
    mp_obj.read_text(text, line_no, tmp_str);
    comment_line[2] = tmp_str.substr( 0,66);
    HSUB = tmp_str.substr( 0,66);
  }

  int i_max = static_cast<int>(NWD-3);
  for(int i=0; i<i_max; i++)
  {
    mp_obj.read_text(text, line_no, tmp_str);
    comment_line[i+3] = tmp_str.substr( 0,66);
  }

  //MF, MT, NC MOD (after comment lines)
  i_max = static_cast<int>(NXC);
  MF.resize(i_max);
  MT.resize(i_max);
  NC.resize(i_max);
  MOD.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    mp_obj.read_cont(text, line_no, tmp_real, tmp_real, MF[i], MT[i], NC[i], MOD[i]);
  }

  mp_obj.line_no_check(text, line_no, mf_no, mt_no);

  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF01MT451Parser::clear()
{
  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);

  mat_no = unassigned_mat_no;
  ZA     = 0;
  AWR    = 0.0;
  LRP    = 0;
  LFI    = 0;
  NLIB   = 0;
  NMOD   = 0;
  ELIS   = 0.0;
  STA    = 0;
  LIS    = 0;
  LISO   = 0;
  NFOR   = 0;
  AWI    = 0.0;
  EMAX   = 0.0;
  LREL   = 0;
  NSUB   = 0;
  NVER   = 0;
  TEMP   = 0.0;
  ERROR  = 0.0;
  LDRV   = 0;
  NWD    = 0;
  NXC    = 0;
  ZSYMAM = "";
  ALAB   = "";
  EDATE  = "";
  AUTH   = "";
  REF    = "";
  DDATE  = "";
  RDATE  = "";
  ENDATE = "";
  HSUB   = "";

  clr_vec.clear_vec_array1_str(comment_line);

//  comment.clear();
  MF.clear();
  MT.clear();
  NC.clear();
  MOD.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF01MT451Parser::set_text(vector<string> text_data)
{
  clear();

  text = text_data;
  store_data();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> MF01MT451Parser::get_text()
{
  return text;
}

Integer MF01MT451Parser::get_mat_no()
{
  return mat_no;
}

//Getter at line No.01
Real MF01MT451Parser::get_ZA()
{
  return ZA;
}

Real MF01MT451Parser::get_AWR()
{
  return AWR;
}

Integer MF01MT451Parser::get_LRP()
{
  return LRP;
}

Integer MF01MT451Parser::get_LFI()
{
  return LFI;
}

Integer MF01MT451Parser::get_NLIB()
{
  return NLIB;
}

Integer MF01MT451Parser::get_NMOD()
{
  return NMOD;
}

//Getter at line No.02
Real MF01MT451Parser::get_ELIS()
{
  return ELIS;
}

Integer MF01MT451Parser::get_STA()
{
  return STA;
}

Integer MF01MT451Parser::get_LIS()
{
  return LIS;
}

Integer MF01MT451Parser::get_LISO()
{
  return LISO;
}

Integer MF01MT451Parser::get_NFOR()
{
  return NFOR;
}

//Getter at line No.03
Real MF01MT451Parser::get_AWI()
{
  return AWI;
}

Real MF01MT451Parser::get_EMAX()
{
  return EMAX;
}

Integer MF01MT451Parser::get_LREL()
{
  return LREL;
}

Integer MF01MT451Parser::get_NSUB()
{
  return NSUB;
}

Integer MF01MT451Parser::get_NVER()
{
  return NVER;
}

//Getter at line No.04
Real MF01MT451Parser::get_TEMP()
{
  return TEMP;
}

Real MF01MT451Parser::get_ERROR()
{
  return ERROR;
}

Integer MF01MT451Parser::get_LDRV()
{
  return LDRV;
}

Integer MF01MT451Parser::get_NWD()
{
  return NWD;
}

Integer MF01MT451Parser::get_NXC()
{
  return NXC;
}

//Getter at line No.05
string MF01MT451Parser::get_ZSYMAM()
{
  return ZSYMAM;
}

string MF01MT451Parser::get_ALAB()
{
  return ALAB;
}

string MF01MT451Parser::get_EDATE()
{
  return EDATE;
}

string MF01MT451Parser::get_AUTH()
{
  return AUTH;
}

//Getter at line No.06
string MF01MT451Parser::get_REF()
{
  return REF;
}

string MF01MT451Parser::get_DDATE()
{
  return DDATE;
}

string MF01MT451Parser::get_RDATE()
{
  return RDATE;
}

string MF01MT451Parser::get_ENDATE()
{
  return ENDATE;
}

//Getter at line No.07
string MF01MT451Parser::get_HSUB()
{
  return HSUB;
}


vector<string> MF01MT451Parser::get_comment_line()
{
  return comment_line;
}


//Getter at other data (MF, MT, NC, MOD)
vector<Integer> MF01MT451Parser::get_MF()
{
  return MF;
}

vector<Integer> MF01MT451Parser::get_MT()
{
  return MT;
}

vector<Integer> MF01MT451Parser::get_NC()
{
  return NC;
}

vector<Integer> MF01MT451Parser::get_MOD()
{
  return MOD;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//Setter
void MF01MT451Parser::set_mat_no(Integer& int_data)
{
  mat_no = int_data;
}

//Setter at line No.01
void MF01MT451Parser::set_ZA(Real& real_data)
{
  ZA = real_data;
}

void MF01MT451Parser::set_AWR(Real& real_data)
{
  AWR = real_data;
}

void MF01MT451Parser::set_LRP(Integer& int_data)
{
  LRP = int_data;
}

void MF01MT451Parser::set_LFI(Integer& int_data)
{
  LFI = int_data;
}

void MF01MT451Parser::set_NLIB(Integer& int_data)
{
  NLIB = int_data;
}

void MF01MT451Parser::set_NMOD(Integer& int_data)
{
  NMOD = int_data;
}


//Setter at line No.02
void MF01MT451Parser::set_ELIS(Real& real_data)
{
  ELIS = real_data;
}

void MF01MT451Parser::set_STA(Integer& int_data)
{
  STA = int_data;
}

void MF01MT451Parser::set_LIS(Integer& int_data)
{
  LIS = int_data;
}

void MF01MT451Parser::set_LISO(Integer& int_data)
{
  LISO = int_data;
}

void MF01MT451Parser::set_NFOR(Integer& int_data)
{
  NFOR = int_data;
}


//Setter at line No.03
void MF01MT451Parser::set_AWI(Real& real_data)
{
  AWI = real_data;
}

void MF01MT451Parser::set_EMAX(Real& real_data)
{
  EMAX = real_data;
}

void MF01MT451Parser::set_LREL(Integer& int_data)
{
  LREL = int_data;
}

void MF01MT451Parser::set_NSUB(Integer& int_data)
{
  NSUB = int_data;
}

void MF01MT451Parser::set_NVER(Integer& int_data)
{
  NVER = int_data;
}


//Setter at line No.04
void MF01MT451Parser::set_TEMP(Real& real_data)
{
  TEMP = real_data;
}

void MF01MT451Parser::set_ERROR(Real& real_data)
{
  ERROR = real_data;
}

void MF01MT451Parser::set_LDRV(Integer& int_data)
{
  LDRV = int_data;
}

void MF01MT451Parser::set_NWD(Integer& int_data)
{
  NWD = int_data;
}

void MF01MT451Parser::set_NXC(Integer& int_data)
{
  NXC = int_data;
}


//Setter at line No.05
void MF01MT451Parser::set_ZSYMAM(string& str_data)
{
  ZSYMAM = str_data;
}

void MF01MT451Parser::set_ALAB(string& str_data)
{
  ALAB = str_data;
}

void MF01MT451Parser::set_EDATE(string& str_data)
{
  EDATE = str_data;
}

void MF01MT451Parser::set_AUTH(string& str_data)
{
  AUTH = str_data;
}


//Setter at line No.06
void MF01MT451Parser::set_REF(string& str_data)
{
  REF = str_data;
}

void MF01MT451Parser::set_DDATE(string& str_data)
{
  DDATE = str_data;
}

void MF01MT451Parser::set_RDATE(string& str_data)
{
  RDATE = str_data;
}

void MF01MT451Parser::set_ENDATE(string& str_data)
{
  ENDATE = str_data;
}


//Setter at line No.07
void MF01MT451Parser::set_HSUB(string& str_data)
{
  HSUB = str_data;
}


void MF01MT451Parser::set_comment_line(vector<string>& str_vec)
{
  comment_line = str_vec;

  NWD = static_cast<Integer>(comment_line.size());
}


//Setter at other data (MF, MT, NC, MOD)
void MF01MT451Parser::set_MF(vector<Integer>& int_vec)
{
  MF = int_vec;
}

void MF01MT451Parser::set_MT(vector<Integer>& int_vec)
{
  MT = int_vec;
}

void MF01MT451Parser::set_NC(vector<Integer>& int_vec)
{
  NC = int_vec;
}

void MF01MT451Parser::set_MOD(vector<Integer>& int_vec)
{
  MOD = int_vec;
}

