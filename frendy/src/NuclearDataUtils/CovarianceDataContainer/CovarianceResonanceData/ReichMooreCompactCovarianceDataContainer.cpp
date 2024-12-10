#include "NuclearDataUtils/CovarianceDataContainer/CovarianceResonanceData/ReichMooreCompactCovarianceDataContainer.hpp"

using namespace frendy;

//constructor
ReichMooreCompactCovarianceDataContainer::ReichMooreCompactCovarianceDataContainer(void)
{
  clear();
}

//destructor
ReichMooreCompactCovarianceDataContainer::~ReichMooreCompactCovarianceDataContainer(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ReichMooreCompactCovarianceDataContainer::clear()
{
  angular_distr_calc_flg = 0;
  scat_radius_l          = 0.0;
  cov_matrix_digit_no    = 0;
  cov_param_no           = 0;

  scat_radius_uncertainty.clear();
  ene_reso.clear();
  j_value_abs.clear();
  gam_width_tot.clear();
  gam_width_n.clear();
  gam_width_fis_a.clear();
  gam_width_fis_b.clear();
  ene_reso_uncertainty.clear();
  gam_width_n_uncertainty.clear();
  gam_width_rad_uncertainty.clear();
  gam_width_fis_a_uncertainty.clear();
  gam_width_fis_b_uncertainty.clear();
  cov_matrix_location_i.clear();
  cov_matrix_location_j.clear();
  clr_obj.clear_vec_array2_int( cov_matrix_coef );
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Getter
Integer ReichMooreCompactCovarianceDataContainer::get_angular_distr_calc_flg()
{
  return angular_distr_calc_flg;
}

vector<Real> ReichMooreCompactCovarianceDataContainer::get_scat_radius_uncertainty()
{
  return scat_radius_uncertainty;
}

Real ReichMooreCompactCovarianceDataContainer::get_scat_radius_l()
{
  return scat_radius_l;
}

vector<Real> ReichMooreCompactCovarianceDataContainer::get_ene_reso()
{
  return ene_reso;
}

vector<Real> ReichMooreCompactCovarianceDataContainer::get_j_value_abs()
{
  return j_value_abs;
}

vector<Real> ReichMooreCompactCovarianceDataContainer::get_gam_width_tot()
{
  return gam_width_tot;
}

vector<Real> ReichMooreCompactCovarianceDataContainer::get_gam_width_n()
{
  return gam_width_n;
}

vector<Real> ReichMooreCompactCovarianceDataContainer::get_gam_width_fis_a()
{
  return gam_width_fis_a;
}

vector<Real> ReichMooreCompactCovarianceDataContainer::get_gam_width_fis_b()
{
  return gam_width_fis_b;
}

vector<Real> ReichMooreCompactCovarianceDataContainer::get_ene_reso_uncertainty()
{
  return ene_reso_uncertainty;
}

vector<Real> ReichMooreCompactCovarianceDataContainer::get_gam_width_n_uncertainty()
{
  return gam_width_n_uncertainty;
}

vector<Real> ReichMooreCompactCovarianceDataContainer::get_gam_width_rad_uncertainty()
{
  return gam_width_rad_uncertainty;
}

vector<Real> ReichMooreCompactCovarianceDataContainer::get_gam_width_fis_a_uncertainty()
{
  return gam_width_fis_a_uncertainty;
}

vector<Real> ReichMooreCompactCovarianceDataContainer::get_gam_width_fis_b_uncertainty()
{
  return gam_width_fis_b_uncertainty;
}

Integer ReichMooreCompactCovarianceDataContainer::get_cov_matrix_digit_no()
{
  return cov_matrix_digit_no;
}

Integer ReichMooreCompactCovarianceDataContainer::get_cov_param_no()
{
  return cov_param_no;
}

vector<Integer> ReichMooreCompactCovarianceDataContainer::get_cov_matrix_location_i()
{
  return cov_matrix_location_i;
}

vector<Integer> ReichMooreCompactCovarianceDataContainer::get_cov_matrix_location_j()
{
  return cov_matrix_location_j;
}

vector<vector<Integer> > ReichMooreCompactCovarianceDataContainer::get_cov_matrix_coef()
{
  return cov_matrix_coef;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void ReichMooreCompactCovarianceDataContainer::set_angular_distr_calc_flg( Integer int_data )
{
  angular_distr_calc_flg = int_data;
}

void ReichMooreCompactCovarianceDataContainer::set_scat_radius_uncertainty( vector<Real> real_vec )
{
  scat_radius_uncertainty = real_vec;
  real_vec.clear();
}

void ReichMooreCompactCovarianceDataContainer::set_scat_radius_l( Real real_data )
{
  scat_radius_l = real_data;
}

void ReichMooreCompactCovarianceDataContainer::set_ene_reso( vector<Real> real_vec )
{
  ene_reso = real_vec;
  real_vec.clear();
}

void ReichMooreCompactCovarianceDataContainer::set_j_value_abs( vector<Real> real_vec )
{
  j_value_abs = real_vec;
  real_vec.clear();
}

void ReichMooreCompactCovarianceDataContainer::set_gam_width_tot( vector<Real> real_vec )
{
  gam_width_tot = real_vec;
  real_vec.clear();
}

void ReichMooreCompactCovarianceDataContainer::set_gam_width_n( vector<Real> real_vec )
{
  gam_width_n = real_vec;
  real_vec.clear();
}

void ReichMooreCompactCovarianceDataContainer::set_gam_width_fis_a( vector<Real> real_vec )
{
  gam_width_fis_a = real_vec;
  real_vec.clear();
}

void ReichMooreCompactCovarianceDataContainer::set_gam_width_fis_b( vector<Real> real_vec )
{
  gam_width_fis_b = real_vec;
  real_vec.clear();
}

void ReichMooreCompactCovarianceDataContainer::set_ene_reso_uncertainty( vector<Real> real_vec )
{
  ene_reso_uncertainty = real_vec;
  real_vec.clear();
}

void ReichMooreCompactCovarianceDataContainer::set_gam_width_n_uncertainty( vector<Real> real_vec )
{
  gam_width_n_uncertainty = real_vec;
  real_vec.clear();
}

void ReichMooreCompactCovarianceDataContainer::set_gam_width_rad_uncertainty( vector<Real> real_vec )
{
  gam_width_rad_uncertainty = real_vec;
  real_vec.clear();
}

void ReichMooreCompactCovarianceDataContainer::set_gam_width_fis_a_uncertainty( vector<Real> real_vec )
{
  gam_width_fis_a_uncertainty = real_vec;
  real_vec.clear();
}

void ReichMooreCompactCovarianceDataContainer::set_gam_width_fis_b_uncertainty( vector<Real> real_vec )
{
  gam_width_fis_b_uncertainty = real_vec;
  real_vec.clear();
}

void ReichMooreCompactCovarianceDataContainer::set_cov_matrix_digit_no( Integer int_data )
{
  cov_matrix_digit_no = int_data;
}

void ReichMooreCompactCovarianceDataContainer::set_cov_param_no( Integer int_data )
{
  cov_param_no = int_data;
}

void ReichMooreCompactCovarianceDataContainer::set_cov_matrix_location_i( vector<Integer> int_vec )
{
  cov_matrix_location_i = int_vec;
  int_vec.clear();
}

void ReichMooreCompactCovarianceDataContainer::set_cov_matrix_location_j( vector<Integer> int_vec )
{
  cov_matrix_location_j = int_vec;
  int_vec.clear();
}

void ReichMooreCompactCovarianceDataContainer::set_cov_matrix_coef( vector<vector<Integer> > int_vec )
{
  cov_matrix_coef = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

