#include "EndfUtils/MFxxMTyyyConverter/MF30MT002Converter.hpp"

using namespace frendy;

//constructor
MF30MT002Converter::MF30MT002Converter(void)
{
}

//destructor
MF30MT002Converter::~MF30MT002Converter(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//CovarianceGeneralDataContainer -> MF30MT002Parser
void MF30MT002Converter::convert_frendy_to_endf_format( CovarianceGeneralDataContainer& frendy_obj, MF30MT002Parser& endf_obj )
{
  //Get frendy data
  vector<Real>          PARM  = frendy_obj.get_relative_cov_parameter();
  vector<vector<Real> > R_COV = frendy_obj.get_relative_cov();

  Integer NP = static_cast<Integer>(PARM.size());

  Integer mat_no = 0;
  if( NP == 0 && static_cast<int>(R_COV.size()) == 0 )
  {
    mat_no = unassigned_mat_no;
  }

  //Set ENDF format data
  endf_obj.clear();
  endf_obj.set_mat_no(mat_no);
  endf_obj.set_NP(NP);
  endf_obj.set_PARM(PARM);
  endf_obj.set_R_COV(R_COV);

  //Clear declared data
  PARM.clear();
  clr_obj.clear_vec_array2_real(R_COV);
  
  NP = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//MF30MT002Parser -> CovarianceGeneralDataContainer
void MF30MT002Converter::convert_endf_format_to_frendy( MF30MT002Parser& endf_obj, CovarianceGeneralDataContainer& frendy_obj )
{
  //Get frendy data
  vector<Real>          relative_cov_parameter = endf_obj.get_PARM();
  vector<vector<Real> > relative_cov           = endf_obj.get_R_COV();

  //Set ENDF format data
  //frendy_obj.clear();
  //text
  //mat_no
  //mt_no
  //ZA
  //AWR
  frendy_obj.set_relative_cov_parameter(relative_cov_parameter);
  frendy_obj.set_relative_cov(relative_cov);

  //Clear declared data
  relative_cov_parameter.clear();
  clr_obj.clear_vec_array2_real(relative_cov);
}

