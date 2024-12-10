#include "NuclearDataUtils/CovarianceDataContainer/CovarianceResonanceData/RMatrixLimitedCovarianceDataContainer.hpp"

using namespace frendy;

//constructor
RMatrixLimitedCovarianceDataContainer::RMatrixLimitedCovarianceDataContainer(void)
{
  clear();
}

//destructor
RMatrixLimitedCovarianceDataContainer::~RMatrixLimitedCovarianceDataContainer(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void RMatrixLimitedCovarianceDataContainer::clear()
{
  gam_width_flg = 0;

  clr_obj.clear_vec_array2_real( scat_radius_list_uncertainty );
  j_pi_no.clear();
  clr_obj.clear_vec_array3_real( ene_reso );
  clr_obj.clear_vec_array4_real( gam_width );
  clr_obj.clear_vec_array3_real( cov_matrix_data );
  reso_parameter_type.clear();
  cov_pattern_flg.clear();
  clr_obj.clear_vec_array2_real( cov_table_ene );
  clr_obj.clear_vec_array3_real( cov_table_coef );
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Getter
Integer RMatrixLimitedCovarianceDataContainer::get_gam_width_flg()
{
  return gam_width_flg;
}

vector<vector<Real> > RMatrixLimitedCovarianceDataContainer::get_scat_radius_list_uncertainty()
{
  return scat_radius_list_uncertainty;
}

vector<Integer> RMatrixLimitedCovarianceDataContainer::get_j_pi_no()
{
  return j_pi_no;
}

vector<vector<vector<Real> > > RMatrixLimitedCovarianceDataContainer::get_ene_reso()
{
  return ene_reso;
}

vector<vector<vector<vector<Real> > > > RMatrixLimitedCovarianceDataContainer::get_gam_width()
{
  return gam_width;
}

vector<vector<vector<Real> > > RMatrixLimitedCovarianceDataContainer::get_cov_matrix_data()
{
  return cov_matrix_data;
}

vector<Integer> RMatrixLimitedCovarianceDataContainer::get_reso_parameter_type()
{
  return reso_parameter_type;
}

vector<Integer> RMatrixLimitedCovarianceDataContainer::get_cov_pattern_flg()
{
  return cov_pattern_flg;
}

vector<vector<Real> > RMatrixLimitedCovarianceDataContainer::get_cov_table_ene()
{
  return cov_table_ene;
}

vector<vector<vector<Real> > > RMatrixLimitedCovarianceDataContainer::get_cov_table_coef()
{
  return cov_table_coef;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void RMatrixLimitedCovarianceDataContainer::set_gam_width_flg( Integer int_data )
{
  gam_width_flg = int_data;
}

void RMatrixLimitedCovarianceDataContainer::set_scat_radius_list_uncertainty( vector<vector<Real> > real_vec )
{
  scat_radius_list_uncertainty = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void RMatrixLimitedCovarianceDataContainer::set_j_pi_no( vector<Integer> int_vec )
{
  j_pi_no = int_vec;
  int_vec.clear();
}

void RMatrixLimitedCovarianceDataContainer::set_ene_reso( vector<vector<vector<Real> > > real_vec )
{
  ene_reso = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

void RMatrixLimitedCovarianceDataContainer::set_gam_width( vector<vector<vector<vector<Real> > > > real_vec )
{
  gam_width = real_vec;
  clr_obj.clear_vec_array4_real( real_vec );
}

void RMatrixLimitedCovarianceDataContainer::set_cov_matrix_data( vector<vector<vector<Real> > > real_vec )
{
  cov_matrix_data = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

void RMatrixLimitedCovarianceDataContainer::set_reso_parameter_type( vector<Integer> int_vec )
{
  reso_parameter_type = int_vec;
  int_vec.clear();
}

void RMatrixLimitedCovarianceDataContainer::set_cov_pattern_flg( vector<Integer> int_vec )
{
  cov_pattern_flg = int_vec;
  int_vec.clear();
}

void RMatrixLimitedCovarianceDataContainer::set_cov_table_ene( vector<vector<Real> > real_vec )
{
  cov_table_ene = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void RMatrixLimitedCovarianceDataContainer::set_cov_table_coef( vector<vector<vector<Real> > > real_vec )
{
  cov_table_coef = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

