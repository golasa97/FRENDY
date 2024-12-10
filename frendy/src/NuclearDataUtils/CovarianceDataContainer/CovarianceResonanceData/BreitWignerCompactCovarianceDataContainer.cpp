#include "NuclearDataUtils/CovarianceDataContainer/CovarianceResonanceData/BreitWignerCompactCovarianceDataContainer.hpp"

using namespace frendy;

//constructor
BreitWignerCompactCovarianceDataContainer::BreitWignerCompactCovarianceDataContainer(void)
{
  clear();
}

//destructor
BreitWignerCompactCovarianceDataContainer::~BreitWignerCompactCovarianceDataContainer(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void BreitWignerCompactCovarianceDataContainer::clear()
{
  scat_radius_uncertainty = 0.0;
  q_value                 = 0.0;
  competitive_width_flg   = 0;
  cov_matrix_digit_no     = 0;
  cov_param_no            = 0;

  ene_reso.clear();
  j_value_abs.clear();
  gam_width_tot.clear();
  gam_width_n.clear();
  gam_width_rad.clear();
  gam_width_fis.clear();
  ene_reso_uncertainty.clear();
  gam_width_n_uncertainty.clear();
  gam_width_rad_uncertainty.clear();
  gam_width_fis_uncertainty.clear();
  cov_matrix_location_i.clear();
  cov_matrix_location_j.clear();
  clr_obj.clear_vec_array2_int( cov_matrix_coef );
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Getter
Real BreitWignerCompactCovarianceDataContainer::get_scat_radius_uncertainty()
{
  return scat_radius_uncertainty;
}

Real BreitWignerCompactCovarianceDataContainer::get_q_value()
{
  return q_value;
}

Integer BreitWignerCompactCovarianceDataContainer::get_competitive_width_flg()
{
  return competitive_width_flg;
}

vector<Real> BreitWignerCompactCovarianceDataContainer::get_ene_reso()
{
  return ene_reso;
}

vector<Real> BreitWignerCompactCovarianceDataContainer::get_j_value_abs()
{
  return j_value_abs;
}

vector<Real> BreitWignerCompactCovarianceDataContainer::get_gam_width_tot()
{
  return gam_width_tot;
}

vector<Real> BreitWignerCompactCovarianceDataContainer::get_gam_width_n()
{
  return gam_width_n;
}

vector<Real> BreitWignerCompactCovarianceDataContainer::get_gam_width_rad()
{
  return gam_width_rad;
}

vector<Real> BreitWignerCompactCovarianceDataContainer::get_gam_width_fis()
{
  return gam_width_fis;
}

vector<Real> BreitWignerCompactCovarianceDataContainer::get_ene_reso_uncertainty()
{
  return ene_reso_uncertainty;
}

vector<Real> BreitWignerCompactCovarianceDataContainer::get_gam_width_n_uncertainty()
{
  return gam_width_n_uncertainty;
}

vector<Real> BreitWignerCompactCovarianceDataContainer::get_gam_width_rad_uncertainty()
{
  return gam_width_rad_uncertainty;
}

vector<Real> BreitWignerCompactCovarianceDataContainer::get_gam_width_fis_uncertainty()
{
  return gam_width_fis_uncertainty;
}

Integer BreitWignerCompactCovarianceDataContainer::get_cov_matrix_digit_no()
{
  return cov_matrix_digit_no;
}

Integer BreitWignerCompactCovarianceDataContainer::get_cov_param_no()
{
  return cov_param_no;
}

vector<Integer> BreitWignerCompactCovarianceDataContainer::get_cov_matrix_location_i()
{
  return cov_matrix_location_i;
}

vector<Integer> BreitWignerCompactCovarianceDataContainer::get_cov_matrix_location_j()
{
  return cov_matrix_location_j;
}

vector<vector<Integer> > BreitWignerCompactCovarianceDataContainer::get_cov_matrix_coef()
{
  return cov_matrix_coef;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void BreitWignerCompactCovarianceDataContainer::set_scat_radius_uncertainty( Real real_data )
{
  scat_radius_uncertainty = real_data;
}

void BreitWignerCompactCovarianceDataContainer::set_q_value( Real real_data )
{
  q_value = real_data;
}

void BreitWignerCompactCovarianceDataContainer::set_competitive_width_flg( Integer int_data )
{
  competitive_width_flg = int_data;
}

void BreitWignerCompactCovarianceDataContainer::set_ene_reso( vector<Real> real_vec )
{
  ene_reso = real_vec;
  real_vec.clear();
}

void BreitWignerCompactCovarianceDataContainer::set_j_value_abs( vector<Real> real_vec )
{
  j_value_abs = real_vec;
  real_vec.clear();
}

void BreitWignerCompactCovarianceDataContainer::set_gam_width_tot( vector<Real> real_vec )
{
  gam_width_tot = real_vec;
  real_vec.clear();
}

void BreitWignerCompactCovarianceDataContainer::set_gam_width_n( vector<Real> real_vec )
{
  gam_width_n = real_vec;
  real_vec.clear();
}

void BreitWignerCompactCovarianceDataContainer::set_gam_width_rad( vector<Real> real_vec )
{
  gam_width_rad = real_vec;
  real_vec.clear();
}

void BreitWignerCompactCovarianceDataContainer::set_gam_width_fis( vector<Real> real_vec )
{
  gam_width_fis = real_vec;
  real_vec.clear();
}

void BreitWignerCompactCovarianceDataContainer::set_ene_reso_uncertainty( vector<Real> real_vec )
{
  ene_reso_uncertainty = real_vec;
  real_vec.clear();
}

void BreitWignerCompactCovarianceDataContainer::set_gam_width_n_uncertainty( vector<Real> real_vec )
{
  gam_width_n_uncertainty = real_vec;
  real_vec.clear();
}

void BreitWignerCompactCovarianceDataContainer::set_gam_width_rad_uncertainty( vector<Real> real_vec )
{
  gam_width_rad_uncertainty = real_vec;
  real_vec.clear();
}

void BreitWignerCompactCovarianceDataContainer::set_gam_width_fis_uncertainty( vector<Real> real_vec )
{
  gam_width_fis_uncertainty = real_vec;
  real_vec.clear();
}

void BreitWignerCompactCovarianceDataContainer::set_cov_matrix_digit_no( Integer int_data )
{
  cov_matrix_digit_no = int_data;
}

void BreitWignerCompactCovarianceDataContainer::set_cov_param_no( Integer int_data )
{
  cov_param_no = int_data;
}

void BreitWignerCompactCovarianceDataContainer::set_cov_matrix_location_i( vector<Integer> int_vec )
{
  cov_matrix_location_i = int_vec;
  int_vec.clear();
}

void BreitWignerCompactCovarianceDataContainer::set_cov_matrix_location_j( vector<Integer> int_vec )
{
  cov_matrix_location_j = int_vec;
  int_vec.clear();
}

void BreitWignerCompactCovarianceDataContainer::set_cov_matrix_coef( vector<vector<Integer> > int_vec )
{
  cov_matrix_coef = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

