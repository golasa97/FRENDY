#include "NuclearDataUtils/CovarianceDataContainer/CovarianceResonanceData/RMatrixLimitedCompactCovarianceDataContainer.hpp"

using namespace frendy;

//constructor
RMatrixLimitedCompactCovarianceDataContainer::RMatrixLimitedCompactCovarianceDataContainer(void)
{
  clear();
}

//destructor
RMatrixLimitedCompactCovarianceDataContainer::~RMatrixLimitedCompactCovarianceDataContainer(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void RMatrixLimitedCompactCovarianceDataContainer::clear()
{
  gam_width_flg       = 0;
  j_pi_no             = 0;
  cov_matrix_digit_no = 0;
  cov_param_no        = 0;

  clr_obj.clear_vec_array2_real( scat_radius_list_uncertainty );
  mass_a.clear();
  mass_b.clear();
  charge_a.clear();
  charge_b.clear();
  spin_a.clear();
  spin_b.clear();
  q_value.clear();
  penetrability_calc_flg.clear();
  shift_factor_calc_flg.clear();
  reaction_type_flg.clear();
  parity_a.clear();
  parity_b.clear();
  j_value_abs.clear();
  parity.clear();
  clr_obj.clear_vec_array2_real( particle_pair_no );
  clr_obj.clear_vec_array2_real( l_value );
  clr_obj.clear_vec_array2_real( spin_channel );
  clr_obj.clear_vec_array2_real( boundary_condition );
  clr_obj.clear_vec_array2_real( scat_radius_eff );
  clr_obj.clear_vec_array2_real( scat_radius_true );
  clr_obj.clear_vec_array2_real( ene_reso );
  clr_obj.clear_vec_array3_real( gam_width );
  clr_obj.clear_vec_array2_real( ene_reso_uncertainty );
  clr_obj.clear_vec_array3_real( gam_width_uncertainty );
  cov_matrix_location_i.clear();
  cov_matrix_location_j.clear();
  clr_obj.clear_vec_array2_int( cov_matrix_coef );
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Getter
Integer RMatrixLimitedCompactCovarianceDataContainer::get_gam_width_flg()
{
  return gam_width_flg;
}

vector<vector<Real> > RMatrixLimitedCompactCovarianceDataContainer::get_scat_radius_list_uncertainty()
{
  return scat_radius_list_uncertainty;
}

Integer RMatrixLimitedCompactCovarianceDataContainer::get_j_pi_no()
{
  return j_pi_no;
}

vector<Real> RMatrixLimitedCompactCovarianceDataContainer::get_mass_a()
{
  return mass_a;
}

vector<Real> RMatrixLimitedCompactCovarianceDataContainer::get_mass_b()
{
  return mass_b;
}

vector<Real> RMatrixLimitedCompactCovarianceDataContainer::get_charge_a()
{
  return charge_a;
}

vector<Real> RMatrixLimitedCompactCovarianceDataContainer::get_charge_b()
{
  return charge_b;
}

vector<Real> RMatrixLimitedCompactCovarianceDataContainer::get_spin_a()
{
  return spin_a;
}

vector<Real> RMatrixLimitedCompactCovarianceDataContainer::get_spin_b()
{
  return spin_b;
}

vector<Real> RMatrixLimitedCompactCovarianceDataContainer::get_q_value()
{
  return q_value;
}

vector<Real> RMatrixLimitedCompactCovarianceDataContainer::get_penetrability_calc_flg()
{
  return penetrability_calc_flg;
}

vector<Real> RMatrixLimitedCompactCovarianceDataContainer::get_shift_factor_calc_flg()
{
  return shift_factor_calc_flg;
}

vector<Real> RMatrixLimitedCompactCovarianceDataContainer::get_reaction_type_flg()
{
  return reaction_type_flg;
}

vector<Real> RMatrixLimitedCompactCovarianceDataContainer::get_parity_a()
{
  return parity_a;
}

vector<Real> RMatrixLimitedCompactCovarianceDataContainer::get_parity_b()
{
  return parity_b;
}

vector<Real> RMatrixLimitedCompactCovarianceDataContainer::get_j_value_abs()
{
  return j_value_abs;
}

vector<Real> RMatrixLimitedCompactCovarianceDataContainer::get_parity()
{
  return parity;
}

vector<vector<Real> > RMatrixLimitedCompactCovarianceDataContainer::get_particle_pair_no()
{
  return particle_pair_no;
}

vector<vector<Real> > RMatrixLimitedCompactCovarianceDataContainer::get_l_value()
{
  return l_value;
}

vector<vector<Real> > RMatrixLimitedCompactCovarianceDataContainer::get_spin_channel()
{
  return spin_channel;
}

vector<vector<Real> > RMatrixLimitedCompactCovarianceDataContainer::get_boundary_condition()
{
  return boundary_condition;
}

vector<vector<Real> > RMatrixLimitedCompactCovarianceDataContainer::get_scat_radius_eff()
{
  return scat_radius_eff;
}

vector<vector<Real> > RMatrixLimitedCompactCovarianceDataContainer::get_scat_radius_true()
{
  return scat_radius_true;
}

vector<vector<Real> > RMatrixLimitedCompactCovarianceDataContainer::get_ene_reso()
{
  return ene_reso;
}

vector<vector<vector<Real> > > RMatrixLimitedCompactCovarianceDataContainer::get_gam_width()
{
  return gam_width;
}

vector<vector<Real> > RMatrixLimitedCompactCovarianceDataContainer::get_ene_reso_uncertainty()
{
  return ene_reso_uncertainty;
}

vector<vector<vector<Real> > > RMatrixLimitedCompactCovarianceDataContainer::get_gam_width_uncertainty()
{
  return gam_width_uncertainty;
}

Integer RMatrixLimitedCompactCovarianceDataContainer::get_cov_matrix_digit_no()
{
  return cov_matrix_digit_no;
}

Integer RMatrixLimitedCompactCovarianceDataContainer::get_cov_param_no()
{
  return cov_param_no;
}

vector<Integer> RMatrixLimitedCompactCovarianceDataContainer::get_cov_matrix_location_i()
{
  return cov_matrix_location_i;
}

vector<Integer> RMatrixLimitedCompactCovarianceDataContainer::get_cov_matrix_location_j()
{
  return cov_matrix_location_j;
}

vector<vector<Integer> > RMatrixLimitedCompactCovarianceDataContainer::get_cov_matrix_coef()
{
  return cov_matrix_coef;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void RMatrixLimitedCompactCovarianceDataContainer::set_gam_width_flg( Integer int_data )
{
  gam_width_flg = int_data;
}

void RMatrixLimitedCompactCovarianceDataContainer::set_scat_radius_list_uncertainty( vector<vector<Real> > real_vec )
{
  scat_radius_list_uncertainty = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void RMatrixLimitedCompactCovarianceDataContainer::set_j_pi_no( Integer int_data )
{
  j_pi_no = int_data;
}

void RMatrixLimitedCompactCovarianceDataContainer::set_mass_a( vector<Real> real_vec )
{
  mass_a = real_vec;
  real_vec.clear();
}

void RMatrixLimitedCompactCovarianceDataContainer::set_mass_b( vector<Real> real_vec )
{
  mass_b = real_vec;
  real_vec.clear();
}

void RMatrixLimitedCompactCovarianceDataContainer::set_charge_a( vector<Real> real_vec )
{
  charge_a = real_vec;
  real_vec.clear();
}

void RMatrixLimitedCompactCovarianceDataContainer::set_charge_b( vector<Real> real_vec )
{
  charge_b = real_vec;
  real_vec.clear();
}

void RMatrixLimitedCompactCovarianceDataContainer::set_spin_a( vector<Real> real_vec )
{
  spin_a = real_vec;
  real_vec.clear();
}

void RMatrixLimitedCompactCovarianceDataContainer::set_spin_b( vector<Real> real_vec )
{
  spin_b = real_vec;
  real_vec.clear();
}

void RMatrixLimitedCompactCovarianceDataContainer::set_q_value( vector<Real> real_vec )
{
  q_value = real_vec;
  real_vec.clear();
}

void RMatrixLimitedCompactCovarianceDataContainer::set_penetrability_calc_flg( vector<Real> real_vec )
{
  penetrability_calc_flg = real_vec;
  real_vec.clear();
}

void RMatrixLimitedCompactCovarianceDataContainer::set_shift_factor_calc_flg( vector<Real> real_vec )
{
  shift_factor_calc_flg = real_vec;
  real_vec.clear();
}

void RMatrixLimitedCompactCovarianceDataContainer::set_reaction_type_flg( vector<Real> real_vec )
{
  reaction_type_flg = real_vec;
  real_vec.clear();
}

void RMatrixLimitedCompactCovarianceDataContainer::set_parity_a( vector<Real> real_vec )
{
  parity_a = real_vec;
  real_vec.clear();
}

void RMatrixLimitedCompactCovarianceDataContainer::set_parity_b( vector<Real> real_vec )
{
  parity_b = real_vec;
  real_vec.clear();
}

void RMatrixLimitedCompactCovarianceDataContainer::set_j_value_abs( vector<Real> real_vec )
{
  j_value_abs = real_vec;
  real_vec.clear();
}

void RMatrixLimitedCompactCovarianceDataContainer::set_parity( vector<Real> real_vec )
{
  parity = real_vec;
  real_vec.clear();
}

void RMatrixLimitedCompactCovarianceDataContainer::set_particle_pair_no( vector<vector<Real> > real_vec )
{
  particle_pair_no = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void RMatrixLimitedCompactCovarianceDataContainer::set_l_value( vector<vector<Real> > real_vec )
{
  l_value = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void RMatrixLimitedCompactCovarianceDataContainer::set_spin_channel( vector<vector<Real> > real_vec )
{
  spin_channel = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void RMatrixLimitedCompactCovarianceDataContainer::set_boundary_condition( vector<vector<Real> > real_vec )
{
  boundary_condition = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void RMatrixLimitedCompactCovarianceDataContainer::set_scat_radius_eff( vector<vector<Real> > real_vec )
{
  scat_radius_eff = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void RMatrixLimitedCompactCovarianceDataContainer::set_scat_radius_true( vector<vector<Real> > real_vec )
{
  scat_radius_true = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void RMatrixLimitedCompactCovarianceDataContainer::set_ene_reso( vector<vector<Real> > real_vec )
{
  ene_reso = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void RMatrixLimitedCompactCovarianceDataContainer::set_gam_width( vector<vector<vector<Real> > > real_vec )
{
  gam_width = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

void RMatrixLimitedCompactCovarianceDataContainer::set_ene_reso_uncertainty( vector<vector<Real> > real_vec )
{
  ene_reso_uncertainty = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void RMatrixLimitedCompactCovarianceDataContainer::set_gam_width_uncertainty( vector<vector<vector<Real> > > real_vec )
{
  gam_width_uncertainty = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

void RMatrixLimitedCompactCovarianceDataContainer::set_cov_matrix_digit_no( Integer int_data )
{
  cov_matrix_digit_no = int_data;
}

void RMatrixLimitedCompactCovarianceDataContainer::set_cov_param_no( Integer int_data )
{
  cov_param_no = int_data;
}

void RMatrixLimitedCompactCovarianceDataContainer::set_cov_matrix_location_i( vector<Integer> int_vec )
{
  cov_matrix_location_i = int_vec;
  int_vec.clear();
}

void RMatrixLimitedCompactCovarianceDataContainer::set_cov_matrix_location_j( vector<Integer> int_vec )
{
  cov_matrix_location_j = int_vec;
  int_vec.clear();
}

void RMatrixLimitedCompactCovarianceDataContainer::set_cov_matrix_coef( vector<vector<Integer> > int_vec )
{
  cov_matrix_coef = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

