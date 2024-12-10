#include "EndfUtils/MFxxMTyyyConverter/MF30MT001Converter.hpp"

using namespace frendy;

//constructor
MF30MT001Converter::MF30MT001Converter(void)
{
}

//destructor
MF30MT001Converter::~MF30MT001Converter(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//CovarianceGeneralDataContainer -> MF30MT001Parser
void MF30MT001Converter::convert_frendy_to_endf_format( CovarianceGeneralDataContainer& frendy_obj, MF30MT001Parser& endf_obj )
{
  //Get frendy data
  Integer         MAT        = frendy_obj.get_mat_no();
  Real            ZA         = frendy_obj.get_mat_data();
  Real            AWR        = frendy_obj.get_mass();
  vector<Integer> MP_NDIR    = frendy_obj.get_sensitivity_parameter();
  vector<Integer> MFSEN_NDIR = frendy_obj.get_sensitivity_type_mf();
  vector<Integer> MTSEN_NDIR = frendy_obj.get_sensitivity_type_mt();
  vector<Integer> NC_NDIR    = frendy_obj.get_sensitivity_data_no();
  vector<Integer> MP_NCTAB   = frendy_obj.get_mat_parameter();
  vector<Integer> LIBF_NCTAB = frendy_obj.get_sub_lib_no();
  vector<Integer> MATF_NCTAB = frendy_obj.get_sub_mat_no();
  vector<Integer> MPF_NCTAB  = frendy_obj.get_parameter_no();

  //Integer NDIR  = static_cast<Integer>(MP_NDIR.size());
  //Integer NCTAB = static_cast<Integer>(MP_NCTAB.size());
  //Integer NP    = NDIR + NCTAB;

  //Set ENDF format data
  endf_obj.clear();
  endf_obj.set_mat_no(MAT);
  endf_obj.set_ZA(ZA);
  endf_obj.set_AWR(AWR);
  endf_obj.set_MP_NDIR(MP_NDIR);
  endf_obj.set_MFSEN_NDIR(MFSEN_NDIR);
  endf_obj.set_MTSEN_NDIR(MTSEN_NDIR);
  endf_obj.set_NC_NDIR(NC_NDIR);
  endf_obj.set_MP_NCTAB(MP_NCTAB);
  endf_obj.set_LIBF_NCTAB(LIBF_NCTAB);
  endf_obj.set_MATF_NCTAB(MATF_NCTAB);
  endf_obj.set_MPF_NCTAB(MPF_NCTAB);

  //Clear declared data
  MAT   = 0;
  ZA    = 0.0;
  AWR   = 0.0;
  //NP    = 0;
  //NDIR  = 0;
  //NCTAB = 0;
  MP_NDIR.clear();
  MFSEN_NDIR.clear();
  MTSEN_NDIR.clear();
  NC_NDIR.clear();
  MP_NCTAB.clear();
  LIBF_NCTAB.clear();
  MATF_NCTAB.clear();
  MPF_NCTAB.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//MF30MT001Parser -> CovarianceGeneralDataContainer
void MF30MT001Converter::convert_endf_format_to_frendy( MF30MT001Parser& endf_obj, CovarianceGeneralDataContainer& frendy_obj )
{
  //Get frendy data
  Integer         mat_no                = endf_obj.get_mat_no();
  Real            mat_data              = endf_obj.get_ZA();
  Real            mass                  = endf_obj.get_AWR();
  vector<Integer> sensitivity_parameter = endf_obj.get_MP_NDIR();
  vector<Integer> sensitivity_type_mf   = endf_obj.get_MFSEN_NDIR();
  vector<Integer> sensitivity_type_mt   = endf_obj.get_MTSEN_NDIR();
  vector<Integer> sensitivity_data_no   = endf_obj.get_NC_NDIR();
  vector<Integer> mat_parameter         = endf_obj.get_MP_NCTAB();
  vector<Integer> sub_lib_no            = endf_obj.get_LIBF_NCTAB();
  vector<Integer> sub_mat_no            = endf_obj.get_MATF_NCTAB();
  vector<Integer> parameter_no          = endf_obj.get_MPF_NCTAB();
  
  /*Integer NP    = endf_obj.get_NP();
  Integer NDIR  = endf_obj.get_NDIR();
  Integer NCTAB = endf_obj.get_NCTAB();

  if( NP != NDIR + NCTAB )
  {
    string class_name = "MF30MT001Converter";
    string func_name  = "convert_endf_format_to_frendy( MF30MT001Parser& endf_obj, CovarianceGeneralDataContainer& frendy_obj )";

    ostringstream oss01, oss02, oss03;
    oss01 << NP;
    oss02 << NDIR;
    oss03 << NCTAB;
    string str_data01 = "NP    : " + oss01.str();
    string str_data02 = "NDIR  : " + oss02.str();
    string str_data03 = "NCTAB : " + oss03.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("NP is not equal to NDIR + NCTAB");
    err_com.push_back("Please check ENDF file or modify MF30MT001Converter class.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }*/

  //Set ENDF format data
  //frendy_obj.clear();
  //text
  frendy_obj.set_mat_no(mat_no);
  //mt_no
  frendy_obj.set_mat_data(mat_data);
  frendy_obj.set_mass(mass);
  frendy_obj.set_sensitivity_parameter(sensitivity_parameter);
  frendy_obj.set_sensitivity_type_mf(sensitivity_type_mf);
  frendy_obj.set_sensitivity_type_mt(sensitivity_type_mt);
  frendy_obj.set_sensitivity_data_no(sensitivity_data_no);
  frendy_obj.set_mat_parameter(mat_parameter);
  frendy_obj.set_sub_lib_no(sub_lib_no);
  frendy_obj.set_sub_mat_no(sub_mat_no);
  frendy_obj.set_parameter_no(parameter_no);

  //Clear declared data
  mat_no   = 0;
  mat_data = 0.0;
  mass     = 0.0;
  sensitivity_parameter.clear();
  sensitivity_type_mf.clear();
  sensitivity_type_mt.clear();
  sensitivity_data_no.clear();
  mat_parameter.clear();
  sub_lib_no.clear();
  sub_mat_no.clear();
  parameter_no.clear();
}

