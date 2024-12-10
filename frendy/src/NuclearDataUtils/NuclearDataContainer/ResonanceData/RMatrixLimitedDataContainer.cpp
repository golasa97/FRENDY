#include "NuclearDataUtils/NuclearDataContainer/ResonanceData/RMatrixLimitedDataContainer.hpp"

using namespace frendy;

//constructor
RMatrixLimitedDataContainer::RMatrixLimitedDataContainer(void)
{
  clear();
}

//destructor
RMatrixLimitedDataContainer::~RMatrixLimitedDataContainer(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void RMatrixLimitedDataContainer::clear()
{
  gam_width_flg     = 0;
  r_matrix_calc_flg = 0;
  relativistic_flg  = 0;

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
  back_ground_r_matrix_flg.clear();
  non_hard_sphere_flg.clear();
  clr_obj.clear_vec_array2_real( particle_pair_no );
  clr_obj.clear_vec_array2_real( l_value );
  clr_obj.clear_vec_array2_real( spin_channel );
  clr_obj.clear_vec_array2_real( boundary_condition );
  clr_obj.clear_vec_array2_real( scat_radius_eff );
  clr_obj.clear_vec_array2_real( scat_radius_true );
  clr_obj.clear_vec_array2_real( ene_reso );
  clr_obj.clear_vec_array3_real( gam_width );
  back_ground_r_matrix_index.clear();
  back_ground_r_matrix_add_flg.clear();
  clr_obj.clear_vec_array2_int( complex_real_int_data );
  clr_obj.clear_vec_array2_int( complex_real_range_data );
  clr_obj.clear_vec_array2_real( complex_real_ene_data );
  clr_obj.clear_vec_array2_real( complex_real_data );
  clr_obj.clear_vec_array2_int( complex_imagin_int_data );
  clr_obj.clear_vec_array2_int( complex_imagin_range_data );
  clr_obj.clear_vec_array2_real( complex_imagin_ene_data );
  clr_obj.clear_vec_array2_real( complex_imagin_data );
  sammy_logarithmic_data_r_com.clear();
  sammy_logarithmic_data_s_com.clear();
  sammy_logarithmic_data_r_lin.clear();
  sammy_logarithmic_data_s_lin.clear();
  sammy_logarithmic_data_r_q.clear();
  sammy_logarithmic_data_e_up.clear();
  sammy_logarithmic_data_e_down.clear();
  frohner_data_rc.clear();
  frohner_data_s.clear();
  frohner_data_gam_r.clear();
  frohner_data_e_up.clear();
  frohner_data_e_down.clear();
  non_hard_sphere_add_flg.clear();
  clr_obj.clear_vec_array2_int( phase_shift_real_int_data );
  clr_obj.clear_vec_array2_int( phase_shift_real_range_data );
  clr_obj.clear_vec_array2_real( phase_shift_real_ene_data );
  clr_obj.clear_vec_array2_real( phase_shift_real_data );
  clr_obj.clear_vec_array2_int( phase_shift_imagin_int_data );
  clr_obj.clear_vec_array2_int( phase_shift_imagin_range_data );
  clr_obj.clear_vec_array2_real( phase_shift_imagin_ene_data );
  clr_obj.clear_vec_array2_real( phase_shift_imagin_data );
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Getter
Integer RMatrixLimitedDataContainer::get_gam_width_flg()
{
  return gam_width_flg;
}

Integer RMatrixLimitedDataContainer::get_r_matrix_calc_flg()
{
  return r_matrix_calc_flg;
}

Integer RMatrixLimitedDataContainer::get_relativistic_flg()
{
  return relativistic_flg;
}

vector<Real> RMatrixLimitedDataContainer::get_mass_a()
{
  return mass_a;
}

vector<Real> RMatrixLimitedDataContainer::get_mass_b()
{
  return mass_b;
}

vector<Real> RMatrixLimitedDataContainer::get_charge_a()
{
  return charge_a;
}

vector<Real> RMatrixLimitedDataContainer::get_charge_b()
{
  return charge_b;
}

vector<Real> RMatrixLimitedDataContainer::get_spin_a()
{
  return spin_a;
}

vector<Real> RMatrixLimitedDataContainer::get_spin_b()
{
  return spin_b;
}

vector<Real> RMatrixLimitedDataContainer::get_q_value()
{
  return q_value;
}

vector<Real> RMatrixLimitedDataContainer::get_penetrability_calc_flg()
{
  return penetrability_calc_flg;
}

vector<Real> RMatrixLimitedDataContainer::get_shift_factor_calc_flg()
{
  return shift_factor_calc_flg;
}

vector<Real> RMatrixLimitedDataContainer::get_reaction_type_flg()
{
  return reaction_type_flg;
}

vector<Real> RMatrixLimitedDataContainer::get_parity_a()
{
  return parity_a;
}

vector<Real> RMatrixLimitedDataContainer::get_parity_b()
{
  return parity_b;
}

vector<Real> RMatrixLimitedDataContainer::get_j_value_abs()
{
  return j_value_abs;
}

vector<Real> RMatrixLimitedDataContainer::get_parity()
{
  return parity;
}

vector<Integer> RMatrixLimitedDataContainer::get_back_ground_r_matrix_flg()
{
  return back_ground_r_matrix_flg;
}

vector<Integer> RMatrixLimitedDataContainer::get_non_hard_sphere_flg()
{
  return non_hard_sphere_flg;
}

vector<vector<Real> > RMatrixLimitedDataContainer::get_particle_pair_no()
{
  return particle_pair_no;
}

vector<vector<Real> > RMatrixLimitedDataContainer::get_l_value()
{
  return l_value;
}

vector<vector<Real> > RMatrixLimitedDataContainer::get_spin_channel()
{
  return spin_channel;
}

vector<vector<Real> > RMatrixLimitedDataContainer::get_boundary_condition()
{
  return boundary_condition;
}

vector<vector<Real> > RMatrixLimitedDataContainer::get_scat_radius_eff()
{
  return scat_radius_eff;
}

vector<vector<Real> > RMatrixLimitedDataContainer::get_scat_radius_true()
{
  return scat_radius_true;
}

vector<vector<Real> > RMatrixLimitedDataContainer::get_ene_reso()
{
  return ene_reso;
}

vector<vector<vector<Real> > > RMatrixLimitedDataContainer::get_gam_width()
{
  return gam_width;
}

vector<Integer> RMatrixLimitedDataContainer::get_back_ground_r_matrix_index()
{
  return back_ground_r_matrix_index;
}

vector<Integer> RMatrixLimitedDataContainer::get_back_ground_r_matrix_add_flg()
{
  return back_ground_r_matrix_add_flg;
}

vector<vector<Integer> > RMatrixLimitedDataContainer::get_complex_real_int_data()
{
  return complex_real_int_data;
}

vector<vector<Integer> > RMatrixLimitedDataContainer::get_complex_real_range_data()
{
  return complex_real_range_data;
}

vector<vector<Real> > RMatrixLimitedDataContainer::get_complex_real_ene_data()
{
  return complex_real_ene_data;
}

vector<vector<Real> > RMatrixLimitedDataContainer::get_complex_real_data()
{
  return complex_real_data;
}

vector<vector<Integer> > RMatrixLimitedDataContainer::get_complex_imagin_int_data()
{
  return complex_imagin_int_data;
}

vector<vector<Integer> > RMatrixLimitedDataContainer::get_complex_imagin_range_data()
{
  return complex_imagin_range_data;
}

vector<vector<Real> > RMatrixLimitedDataContainer::get_complex_imagin_ene_data()
{
  return complex_imagin_ene_data;
}

vector<vector<Real> > RMatrixLimitedDataContainer::get_complex_imagin_data()
{
  return complex_imagin_data;
}

vector<Real> RMatrixLimitedDataContainer::get_sammy_logarithmic_data_r_com()
{
  return sammy_logarithmic_data_r_com;
}

vector<Real> RMatrixLimitedDataContainer::get_sammy_logarithmic_data_s_com()
{
  return sammy_logarithmic_data_s_com;
}

vector<Real> RMatrixLimitedDataContainer::get_sammy_logarithmic_data_r_lin()
{
  return sammy_logarithmic_data_r_lin;
}

vector<Real> RMatrixLimitedDataContainer::get_sammy_logarithmic_data_s_lin()
{
  return sammy_logarithmic_data_s_lin;
}

vector<Real> RMatrixLimitedDataContainer::get_sammy_logarithmic_data_r_q()
{
  return sammy_logarithmic_data_r_q;
}

vector<Real> RMatrixLimitedDataContainer::get_sammy_logarithmic_data_e_up()
{
  return sammy_logarithmic_data_e_up;
}

vector<Real> RMatrixLimitedDataContainer::get_sammy_logarithmic_data_e_down()
{
  return sammy_logarithmic_data_e_down;
}

vector<Real> RMatrixLimitedDataContainer::get_frohner_data_rc()
{
  return frohner_data_rc;
}

vector<Real> RMatrixLimitedDataContainer::get_frohner_data_s()
{
  return frohner_data_s;
}

vector<Real> RMatrixLimitedDataContainer::get_frohner_data_gam_r()
{
  return frohner_data_gam_r;
}

vector<Real> RMatrixLimitedDataContainer::get_frohner_data_e_up()
{
  return frohner_data_e_up;
}

vector<Real> RMatrixLimitedDataContainer::get_frohner_data_e_down()
{
  return frohner_data_e_down;
}

vector<Integer> RMatrixLimitedDataContainer::get_non_hard_sphere_add_flg()
{
  return non_hard_sphere_add_flg;
}

vector<vector<Integer> > RMatrixLimitedDataContainer::get_phase_shift_real_int_data()
{
  return phase_shift_real_int_data;
}

vector<vector<Integer> > RMatrixLimitedDataContainer::get_phase_shift_real_range_data()
{
  return phase_shift_real_range_data;
}

vector<vector<Real> > RMatrixLimitedDataContainer::get_phase_shift_real_ene_data()
{
  return phase_shift_real_ene_data;
}

vector<vector<Real> > RMatrixLimitedDataContainer::get_phase_shift_real_data()
{
  return phase_shift_real_data;
}

vector<vector<Integer> > RMatrixLimitedDataContainer::get_phase_shift_imagin_int_data()
{
  return phase_shift_imagin_int_data;
}

vector<vector<Integer> > RMatrixLimitedDataContainer::get_phase_shift_imagin_range_data()
{
  return phase_shift_imagin_range_data;
}

vector<vector<Real> > RMatrixLimitedDataContainer::get_phase_shift_imagin_ene_data()
{
  return phase_shift_imagin_ene_data;
}

vector<vector<Real> > RMatrixLimitedDataContainer::get_phase_shift_imagin_data()
{
  return phase_shift_imagin_data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void RMatrixLimitedDataContainer::set_gam_width_flg( Integer int_data )
{
  gam_width_flg = int_data;
}

void RMatrixLimitedDataContainer::set_r_matrix_calc_flg( Integer int_data )
{
  r_matrix_calc_flg = int_data;
}

void RMatrixLimitedDataContainer::set_relativistic_flg( Integer int_data )
{
  relativistic_flg = int_data;
}

void RMatrixLimitedDataContainer::set_mass_a( vector<Real> real_vec )
{
  mass_a = real_vec;
  real_vec.clear();
}

void RMatrixLimitedDataContainer::set_mass_b( vector<Real> real_vec )
{
  mass_b = real_vec;
  real_vec.clear();
}

void RMatrixLimitedDataContainer::set_charge_a( vector<Real> real_vec )
{
  charge_a = real_vec;
  real_vec.clear();
}

void RMatrixLimitedDataContainer::set_charge_b( vector<Real> real_vec )
{
  charge_b = real_vec;
  real_vec.clear();
}

void RMatrixLimitedDataContainer::set_spin_a( vector<Real> real_vec )
{
  spin_a = real_vec;
  real_vec.clear();
}

void RMatrixLimitedDataContainer::set_spin_b( vector<Real> real_vec )
{
  spin_b = real_vec;
  real_vec.clear();
}

void RMatrixLimitedDataContainer::set_q_value( vector<Real> real_vec )
{
  q_value = real_vec;
  real_vec.clear();
}

void RMatrixLimitedDataContainer::set_penetrability_calc_flg( vector<Real> real_vec )
{
  penetrability_calc_flg = real_vec;
  real_vec.clear();
}

void RMatrixLimitedDataContainer::set_shift_factor_calc_flg( vector<Real> real_vec )
{
  shift_factor_calc_flg = real_vec;
  real_vec.clear();
}

void RMatrixLimitedDataContainer::set_reaction_type_flg( vector<Real> real_vec )
{
  reaction_type_flg = real_vec;
  real_vec.clear();
}

void RMatrixLimitedDataContainer::set_parity_a( vector<Real> real_vec )
{
  parity_a = real_vec;
  real_vec.clear();
}

void RMatrixLimitedDataContainer::set_parity_b( vector<Real> real_vec )
{
  parity_b = real_vec;
  real_vec.clear();
}

void RMatrixLimitedDataContainer::set_j_value_abs( vector<Real> real_vec )
{
  j_value_abs = real_vec;
  real_vec.clear();
}

void RMatrixLimitedDataContainer::set_parity( vector<Real> real_vec )
{
  parity = real_vec;
  real_vec.clear();
}

void RMatrixLimitedDataContainer::set_back_ground_r_matrix_flg( vector<Integer> int_vec )
{
  back_ground_r_matrix_flg = int_vec;
  int_vec.clear();
}

void RMatrixLimitedDataContainer::set_non_hard_sphere_flg( vector<Integer> int_vec )
{
  non_hard_sphere_flg = int_vec;
  int_vec.clear();
}

void RMatrixLimitedDataContainer::set_particle_pair_no( vector<vector<Real> > real_vec )
{
  particle_pair_no = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void RMatrixLimitedDataContainer::set_l_value( vector<vector<Real> > real_vec )
{
  l_value = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void RMatrixLimitedDataContainer::set_spin_channel( vector<vector<Real> > real_vec )
{
  spin_channel = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void RMatrixLimitedDataContainer::set_boundary_condition( vector<vector<Real> > real_vec )
{
  boundary_condition = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void RMatrixLimitedDataContainer::set_scat_radius_eff( vector<vector<Real> > real_vec )
{
  scat_radius_eff = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void RMatrixLimitedDataContainer::set_scat_radius_true( vector<vector<Real> > real_vec )
{
  scat_radius_true = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void RMatrixLimitedDataContainer::set_ene_reso( vector<vector<Real> > real_vec )
{
  ene_reso = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void RMatrixLimitedDataContainer::set_gam_width( vector<vector<vector<Real> > > real_vec )
{
  gam_width = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

void RMatrixLimitedDataContainer::set_back_ground_r_matrix_index( vector<Integer> int_vec )
{
  back_ground_r_matrix_index = int_vec;
  int_vec.clear();
}

void RMatrixLimitedDataContainer::set_back_ground_r_matrix_add_flg( vector<Integer> int_vec )
{
  back_ground_r_matrix_add_flg = int_vec;
  int_vec.clear();
}

void RMatrixLimitedDataContainer::set_complex_real_int_data( vector<vector<Integer> > int_vec )
{
  complex_real_int_data = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void RMatrixLimitedDataContainer::set_complex_real_range_data( vector<vector<Integer> > int_vec )
{
  complex_real_range_data = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void RMatrixLimitedDataContainer::set_complex_real_ene_data( vector<vector<Real> > real_vec )
{
  complex_real_ene_data = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void RMatrixLimitedDataContainer::set_complex_real_data( vector<vector<Real> > real_vec )
{
  complex_real_data = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void RMatrixLimitedDataContainer::set_complex_imagin_int_data( vector<vector<Integer> > int_vec )
{
  complex_imagin_int_data = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void RMatrixLimitedDataContainer::set_complex_imagin_range_data( vector<vector<Integer> > int_vec )
{
  complex_imagin_range_data = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void RMatrixLimitedDataContainer::set_complex_imagin_ene_data( vector<vector<Real> > real_vec )
{
  complex_imagin_ene_data = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void RMatrixLimitedDataContainer::set_complex_imagin_data( vector<vector<Real> > real_vec )
{
  complex_imagin_data = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void RMatrixLimitedDataContainer::set_sammy_logarithmic_data_r_com( vector<Real> real_vec )
{
  sammy_logarithmic_data_r_com = real_vec;
  real_vec.clear();
}

void RMatrixLimitedDataContainer::set_sammy_logarithmic_data_s_com( vector<Real> real_vec )
{
  sammy_logarithmic_data_s_com = real_vec;
  real_vec.clear();
}

void RMatrixLimitedDataContainer::set_sammy_logarithmic_data_r_lin( vector<Real> real_vec )
{
  sammy_logarithmic_data_r_lin = real_vec;
  real_vec.clear();
}

void RMatrixLimitedDataContainer::set_sammy_logarithmic_data_s_lin( vector<Real> real_vec )
{
  sammy_logarithmic_data_s_lin = real_vec;
  real_vec.clear();
}

void RMatrixLimitedDataContainer::set_sammy_logarithmic_data_r_q( vector<Real> real_vec )
{
  sammy_logarithmic_data_r_q = real_vec;
  real_vec.clear();
}

void RMatrixLimitedDataContainer::set_sammy_logarithmic_data_e_up( vector<Real> real_vec )
{
  sammy_logarithmic_data_e_up = real_vec;
  real_vec.clear();
}

void RMatrixLimitedDataContainer::set_sammy_logarithmic_data_e_down( vector<Real> real_vec )
{
  sammy_logarithmic_data_e_down = real_vec;
  real_vec.clear();
}

void RMatrixLimitedDataContainer::set_frohner_data_rc( vector<Real> real_vec )
{
  frohner_data_rc = real_vec;
  real_vec.clear();
}

void RMatrixLimitedDataContainer::set_frohner_data_s( vector<Real> real_vec )
{
  frohner_data_s = real_vec;
  real_vec.clear();
}

void RMatrixLimitedDataContainer::set_frohner_data_gam_r( vector<Real> real_vec )
{
  frohner_data_gam_r = real_vec;
  real_vec.clear();
}

void RMatrixLimitedDataContainer::set_frohner_data_e_up( vector<Real> real_vec )
{
  frohner_data_e_up = real_vec;
  real_vec.clear();
}

void RMatrixLimitedDataContainer::set_frohner_data_e_down( vector<Real> real_vec )
{
  frohner_data_e_down = real_vec;
  real_vec.clear();
}

void RMatrixLimitedDataContainer::set_non_hard_sphere_add_flg( vector<Integer> int_vec )
{
  non_hard_sphere_add_flg = int_vec;
  int_vec.clear();
}

void RMatrixLimitedDataContainer::set_phase_shift_real_int_data( vector<vector<Integer> > int_vec )
{
  phase_shift_real_int_data = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void RMatrixLimitedDataContainer::set_phase_shift_real_range_data( vector<vector<Integer> > int_vec )
{
  phase_shift_real_range_data = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void RMatrixLimitedDataContainer::set_phase_shift_real_ene_data( vector<vector<Real> > real_vec )
{
  phase_shift_real_ene_data = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void RMatrixLimitedDataContainer::set_phase_shift_real_data( vector<vector<Real> > real_vec )
{
  phase_shift_real_data = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void RMatrixLimitedDataContainer::set_phase_shift_imagin_int_data( vector<vector<Integer> > int_vec )
{
  phase_shift_imagin_int_data = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void RMatrixLimitedDataContainer::set_phase_shift_imagin_range_data( vector<vector<Integer> > int_vec )
{
  phase_shift_imagin_range_data = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void RMatrixLimitedDataContainer::set_phase_shift_imagin_ene_data( vector<vector<Real> > real_vec )
{
  phase_shift_imagin_ene_data = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void RMatrixLimitedDataContainer::set_phase_shift_imagin_data( vector<vector<Real> > real_vec )
{
  phase_shift_imagin_data = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

