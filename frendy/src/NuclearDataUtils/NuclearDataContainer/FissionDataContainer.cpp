#include "NuclearDataUtils/NuclearDataContainer/FissionDataContainer.hpp"

using namespace frendy;

//constructor
FissionDataContainer::FissionDataContainer(void)
{
  clear();
}

//destructor
FissionDataContainer::~FissionDataContainer(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void FissionDataContainer::clear()
{
  nu_bar_repr_flg   = 0;
  nu_d_bar_repr_flg = 0;
  nu_p_bar_repr_flg = 0;
  photon_d_repr_flg = 0;

  nu_bar_polynomial_coef.clear();
  nu_bar_int_data.clear();
  nu_bar_range_data.clear();
  nu_bar_ene_data.clear();
  nu_bar_data.clear();

  nu_d_bar_polynomial_coef.clear();
  nu_d_bar_int_data.clear();
  nu_d_bar_range_data.clear();
  nu_d_bar_ene_data.clear();
  nu_d_bar_data.clear();
  nu_d_ene_data.clear();
  nu_d_decay_int_data.clear();
  nu_d_decay_range_data.clear();
  clr_obj.clear_vec_array2_real( nu_d_decay_constant );
  clr_obj.clear_vec_array2_real( nu_d_delayed_group_abundance );

  nu_p_bar_polynomial_coef.clear();
  nu_p_bar_int_data.clear();
  nu_p_bar_range_data.clear();
  nu_p_bar_ene_data.clear();
  nu_p_bar_data.clear();

  fis_ene_repr_flg = 0;
  fis_ene_tot.clear();
  fis_ene_fp.clear();
  fis_ene_n_p.clear();
  fis_ene_n_d.clear();
  fis_ene_gam_p.clear();
  fis_ene_gam_d.clear();
  fis_ene_beta_d.clear();
  fis_ene_neutrino.clear();
  fis_ene_non_neutrino.clear();
  fis_ene_tot_uncertainty.clear();
  fis_ene_fp_uncertainty.clear();
  fis_ene_n_p_uncertainty.clear();
  fis_ene_n_d_uncertainty.clear();
  fis_ene_gam_p_uncertainty.clear();
  fis_ene_gam_d_uncertainty.clear();
  fis_ene_beta_d_uncertainty.clear();
  fis_ene_neutrino_uncertainty.clear();
  fis_ene_non_neutrino_uncertainty.clear();
  fis_ene_index.clear();
  fis_ene_evaluation_flg.clear();
  clr_obj.clear_vec_array2_int( fis_ene_table_int_data );
  clr_obj.clear_vec_array2_int( fis_ene_table_range_data );
  clr_obj.clear_vec_array2_real( fis_ene_table_ene_data );
  clr_obj.clear_vec_array2_real( fis_ene_table_data );

  photon_d_ene.clear();
  clr_obj.clear_vec_array2_int( photon_d_int_data );
  clr_obj.clear_vec_array2_int( photon_d_range_data );
  clr_obj.clear_vec_array2_real( photon_d_time_data );
  clr_obj.clear_vec_array2_real( photon_d_data );
  photon_d_precursor_decay_const.clear();

  clr_obj.clear_vec_array2_real( fp_data_independent );
  clr_obj.clear_vec_array2_real( state_designator_fp_independent );
  clr_obj.clear_vec_array2_real( yield_independent );
  clr_obj.clear_vec_array2_real( yield_independent_uncertainty );
  incident_ene_independent.clear();
  ene_int_data_independent.clear();
  clr_obj.clear_vec_array2_real( fp_data_cumulative );
  clr_obj.clear_vec_array2_real( state_designator_fp_cumulative );
  clr_obj.clear_vec_array2_real( yield_cumulative );
  clr_obj.clear_vec_array2_real( yield_cumulative_uncertainty );
  incident_ene_cumulative.clear();
  ene_int_data_cumulative.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Getter
Integer FissionDataContainer::get_nu_bar_repr_flg()
{
  return nu_bar_repr_flg;
}

vector<Real> FissionDataContainer::get_nu_bar_polynomial_coef()
{
  return nu_bar_polynomial_coef;
}

vector<Integer> FissionDataContainer::get_nu_bar_int_data()
{
  return nu_bar_int_data;
}

vector<Integer> FissionDataContainer::get_nu_bar_range_data()
{
  return nu_bar_range_data;
}

vector<Real> FissionDataContainer::get_nu_bar_ene_data()
{
  return nu_bar_ene_data;
}

vector<Real> FissionDataContainer::get_nu_bar_data()
{
  return nu_bar_data;
}

Integer FissionDataContainer::get_nu_d_bar_repr_flg()
{
  return nu_d_bar_repr_flg;
}

vector<Real> FissionDataContainer::get_nu_d_bar_polynomial_coef()
{
  return nu_d_bar_polynomial_coef;
}

vector<Integer> FissionDataContainer::get_nu_d_bar_int_data()
{
  return nu_d_bar_int_data;
}

vector<Integer> FissionDataContainer::get_nu_d_bar_range_data()
{
  return nu_d_bar_range_data;
}

vector<Real> FissionDataContainer::get_nu_d_bar_ene_data()
{
  return nu_d_bar_ene_data;
}

vector<Real> FissionDataContainer::get_nu_d_bar_data()
{
  return nu_d_bar_data;
}

vector<Real> FissionDataContainer::get_nu_d_ene_data()
{
  return nu_d_ene_data;
}

vector<Integer> FissionDataContainer::get_nu_d_decay_int_data()
{
  return nu_d_decay_int_data;
}

vector<Integer> FissionDataContainer::get_nu_d_decay_range_data()
{
  return nu_d_decay_range_data;
}

vector<vector<Real> > FissionDataContainer::get_nu_d_decay_constant()
{
  return nu_d_decay_constant;
}

vector<vector<Real> > FissionDataContainer::get_nu_d_delayed_group_abundance()
{
  return nu_d_delayed_group_abundance;
}

Integer FissionDataContainer::get_nu_p_bar_repr_flg()
{
  return nu_p_bar_repr_flg;
}

vector<Real> FissionDataContainer::get_nu_p_bar_polynomial_coef()
{
  return nu_p_bar_polynomial_coef;
}

vector<Integer> FissionDataContainer::get_nu_p_bar_int_data()
{
  return nu_p_bar_int_data;
}

vector<Integer> FissionDataContainer::get_nu_p_bar_range_data()
{
  return nu_p_bar_range_data;
}

vector<Real> FissionDataContainer::get_nu_p_bar_ene_data()
{
  return nu_p_bar_ene_data;
}

vector<Real> FissionDataContainer::get_nu_p_bar_data()
{
  return nu_p_bar_data;
}

Integer FissionDataContainer::get_fis_ene_repr_flg()
{
  return fis_ene_repr_flg;
}

vector<Real> FissionDataContainer::get_fis_ene_tot()
{
  return fis_ene_tot;
}

vector<Real> FissionDataContainer::get_fis_ene_fp()
{
  return fis_ene_fp;
}

vector<Real> FissionDataContainer::get_fis_ene_n_p()
{
  return fis_ene_n_p;
}

vector<Real> FissionDataContainer::get_fis_ene_n_d()
{
  return fis_ene_n_d;
}

vector<Real> FissionDataContainer::get_fis_ene_gam_p()
{
  return fis_ene_gam_p;
}

vector<Real> FissionDataContainer::get_fis_ene_gam_d()
{
  return fis_ene_gam_d;
}

vector<Real> FissionDataContainer::get_fis_ene_beta_d()
{
  return fis_ene_beta_d;
}

vector<Real> FissionDataContainer::get_fis_ene_neutrino()
{
  return fis_ene_neutrino;
}

vector<Real> FissionDataContainer::get_fis_ene_non_neutrino()
{
  return fis_ene_non_neutrino;
}

vector<Real> FissionDataContainer::get_fis_ene_tot_uncertainty()
{
  return fis_ene_tot_uncertainty;
}

vector<Real> FissionDataContainer::get_fis_ene_fp_uncertainty()
{
  return fis_ene_fp_uncertainty;
}

vector<Real> FissionDataContainer::get_fis_ene_n_p_uncertainty()
{
  return fis_ene_n_p_uncertainty;
}

vector<Real> FissionDataContainer::get_fis_ene_n_d_uncertainty()
{
  return fis_ene_n_d_uncertainty;
}

vector<Real> FissionDataContainer::get_fis_ene_gam_p_uncertainty()
{
  return fis_ene_gam_p_uncertainty;
}

vector<Real> FissionDataContainer::get_fis_ene_gam_d_uncertainty()
{
  return fis_ene_gam_d_uncertainty;
}

vector<Real> FissionDataContainer::get_fis_ene_beta_d_uncertainty()
{
  return fis_ene_beta_d_uncertainty;
}

vector<Real> FissionDataContainer::get_fis_ene_neutrino_uncertainty()
{
  return fis_ene_neutrino_uncertainty;
}

vector<Real> FissionDataContainer::get_fis_ene_non_neutrino_uncertainty()
{
  return fis_ene_non_neutrino_uncertainty;
}

vector<Integer> FissionDataContainer::get_fis_ene_index()
{
  return fis_ene_index;
}

vector<Integer> FissionDataContainer::get_fis_ene_evaluation_flg()
{
  return fis_ene_evaluation_flg;
}

vector<vector<Integer> > FissionDataContainer::get_fis_ene_table_int_data()
{
  return fis_ene_table_int_data;
}

vector<vector<Integer> > FissionDataContainer::get_fis_ene_table_range_data()
{
  return fis_ene_table_range_data;
}

vector<vector<Real> > FissionDataContainer::get_fis_ene_table_ene_data()
{
  return fis_ene_table_ene_data;
}

vector<vector<Real> > FissionDataContainer::get_fis_ene_table_data()
{
  return fis_ene_table_data;
}

Integer FissionDataContainer::get_photon_d_repr_flg()
{
  return photon_d_repr_flg;
}

vector<Real> FissionDataContainer::get_photon_d_ene()
{
  return photon_d_ene;
}

vector<vector<Integer> > FissionDataContainer::get_photon_d_int_data()
{
  return photon_d_int_data;
}

vector<vector<Integer> > FissionDataContainer::get_photon_d_range_data()
{
  return photon_d_range_data;
}

vector<vector<Real> > FissionDataContainer::get_photon_d_time_data()
{
  return photon_d_time_data;
}

vector<vector<Real> > FissionDataContainer::get_photon_d_data()
{
  return photon_d_data;
}

vector<Real> FissionDataContainer::get_photon_d_precursor_decay_const()
{
  return photon_d_precursor_decay_const;
}

vector<vector<Real> > FissionDataContainer::get_fp_data_independent()
{
  return fp_data_independent;
}

vector<vector<Real> > FissionDataContainer::get_state_designator_fp_independent()
{
  return state_designator_fp_independent;
}

vector<vector<Real> > FissionDataContainer::get_yield_independent()
{
  return yield_independent;
}

vector<vector<Real> > FissionDataContainer::get_yield_independent_uncertainty()
{
  return yield_independent_uncertainty;
}

vector<Real> FissionDataContainer::get_incident_ene_independent()
{
  return incident_ene_independent;
}

vector<Integer> FissionDataContainer::get_ene_int_data_independent()
{
  return ene_int_data_independent;
}

vector<vector<Real> > FissionDataContainer::get_fp_data_cumulative()
{
  return fp_data_cumulative;
}

vector<vector<Real> > FissionDataContainer::get_state_designator_fp_cumulative()
{
  return state_designator_fp_cumulative;
}

vector<vector<Real> > FissionDataContainer::get_yield_cumulative()
{
  return yield_cumulative;
}

vector<vector<Real> > FissionDataContainer::get_yield_cumulative_uncertainty()
{
  return yield_cumulative_uncertainty;
}

vector<Real> FissionDataContainer::get_incident_ene_cumulative()
{
  return incident_ene_cumulative;
}

vector<Integer> FissionDataContainer::get_ene_int_data_cumulative()
{
  return ene_int_data_cumulative;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void FissionDataContainer::set_nu_bar_repr_flg( Integer int_data )
{
  nu_bar_repr_flg = int_data;
}

void FissionDataContainer::set_nu_bar_polynomial_coef( vector<Real> real_vec )
{
  nu_bar_polynomial_coef = real_vec;
  real_vec.clear();
}

void FissionDataContainer::set_nu_bar_int_data( vector<Integer> int_vec )
{
  nu_bar_int_data = int_vec;
  int_vec.clear();
}

void FissionDataContainer::set_nu_bar_range_data( vector<Integer> int_vec )
{
  nu_bar_range_data = int_vec;
  int_vec.clear();
}

void FissionDataContainer::set_nu_bar_ene_data( vector<Real> real_vec )
{
  nu_bar_ene_data = real_vec;
  real_vec.clear();
}

void FissionDataContainer::set_nu_bar_data( vector<Real> real_vec )
{
  nu_bar_data = real_vec;
  real_vec.clear();
}

void FissionDataContainer::set_nu_d_bar_repr_flg( Integer int_data )
{
  nu_d_bar_repr_flg = int_data;
}

void FissionDataContainer::set_nu_d_bar_polynomial_coef( vector<Real> real_vec )
{
  nu_d_bar_polynomial_coef = real_vec;
  real_vec.clear();
}

void FissionDataContainer::set_nu_d_bar_int_data( vector<Integer> int_vec )
{
  nu_d_bar_int_data = int_vec;
  int_vec.clear();
}

void FissionDataContainer::set_nu_d_bar_range_data( vector<Integer> int_vec )
{
  nu_d_bar_range_data = int_vec;
  int_vec.clear();
}

void FissionDataContainer::set_nu_d_bar_ene_data( vector<Real> real_vec )
{
  nu_d_bar_ene_data = real_vec;
  real_vec.clear();
}

void FissionDataContainer::set_nu_d_bar_data( vector<Real> real_vec )
{
  nu_d_bar_data = real_vec;
  real_vec.clear();
}

void FissionDataContainer::set_nu_d_ene_data( vector<Real> real_vec )
{
  nu_d_ene_data = real_vec;
  real_vec.clear();
}

void FissionDataContainer::set_nu_d_decay_int_data( vector<Integer> int_vec )
{
  nu_d_decay_int_data = int_vec;
  int_vec.clear();
}

void FissionDataContainer::set_nu_d_decay_range_data( vector<Integer> int_vec )
{
  nu_d_decay_range_data = int_vec;
  int_vec.clear();
}

void FissionDataContainer::set_nu_d_decay_constant( vector<vector<Real> > real_vec )
{
  nu_d_decay_constant = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void FissionDataContainer::set_nu_d_delayed_group_abundance( vector<vector<Real> > real_vec )
{
  nu_d_delayed_group_abundance = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void FissionDataContainer::set_nu_p_bar_repr_flg( Integer int_data )
{
  nu_p_bar_repr_flg = int_data;
}

void FissionDataContainer::set_nu_p_bar_polynomial_coef( vector<Real> real_vec )
{
  nu_p_bar_polynomial_coef = real_vec;
  real_vec.clear();
}

void FissionDataContainer::set_nu_p_bar_int_data( vector<Integer> int_vec )
{
  nu_p_bar_int_data = int_vec;
  int_vec.clear();
}

void FissionDataContainer::set_nu_p_bar_range_data( vector<Integer> int_vec )
{
  nu_p_bar_range_data = int_vec;
  int_vec.clear();
}

void FissionDataContainer::set_nu_p_bar_ene_data( vector<Real> real_vec )
{
  nu_p_bar_ene_data = real_vec;
  real_vec.clear();
}

void FissionDataContainer::set_nu_p_bar_data( vector<Real> real_vec )
{
  nu_p_bar_data = real_vec;
  real_vec.clear();
}

void FissionDataContainer::set_fis_ene_repr_flg( Integer int_data )
{
  fis_ene_repr_flg = int_data;
}

void FissionDataContainer::set_fis_ene_tot( vector<Real> real_vec )
{
  fis_ene_tot = real_vec;
  real_vec.clear();
}

void FissionDataContainer::set_fis_ene_fp( vector<Real> real_vec )
{
  fis_ene_fp = real_vec;
  real_vec.clear();
}

void FissionDataContainer::set_fis_ene_n_p( vector<Real> real_vec )
{
  fis_ene_n_p = real_vec;
  real_vec.clear();
}

void FissionDataContainer::set_fis_ene_n_d( vector<Real> real_vec )
{
  fis_ene_n_d = real_vec;
  real_vec.clear();
}

void FissionDataContainer::set_fis_ene_gam_p( vector<Real> real_vec )
{
  fis_ene_gam_p = real_vec;
  real_vec.clear();
}

void FissionDataContainer::set_fis_ene_gam_d( vector<Real> real_vec )
{
  fis_ene_gam_d = real_vec;
  real_vec.clear();
}

void FissionDataContainer::set_fis_ene_beta_d( vector<Real> real_vec )
{
  fis_ene_beta_d = real_vec;
  real_vec.clear();
}

void FissionDataContainer::set_fis_ene_neutrino( vector<Real> real_vec )
{
  fis_ene_neutrino = real_vec;
  real_vec.clear();
}

void FissionDataContainer::set_fis_ene_non_neutrino( vector<Real> real_vec )
{
  fis_ene_non_neutrino = real_vec;
  real_vec.clear();
}

void FissionDataContainer::set_fis_ene_tot_uncertainty( vector<Real> real_vec )
{
  fis_ene_tot_uncertainty = real_vec;
  real_vec.clear();
}

void FissionDataContainer::set_fis_ene_fp_uncertainty( vector<Real> real_vec )
{
  fis_ene_fp_uncertainty = real_vec;
  real_vec.clear();
}

void FissionDataContainer::set_fis_ene_n_p_uncertainty( vector<Real> real_vec )
{
  fis_ene_n_p_uncertainty = real_vec;
  real_vec.clear();
}

void FissionDataContainer::set_fis_ene_n_d_uncertainty( vector<Real> real_vec )
{
  fis_ene_n_d_uncertainty = real_vec;
  real_vec.clear();
}

void FissionDataContainer::set_fis_ene_gam_p_uncertainty( vector<Real> real_vec )
{
  fis_ene_gam_p_uncertainty = real_vec;
  real_vec.clear();
}

void FissionDataContainer::set_fis_ene_gam_d_uncertainty( vector<Real> real_vec )
{
  fis_ene_gam_d_uncertainty = real_vec;
  real_vec.clear();
}

void FissionDataContainer::set_fis_ene_beta_d_uncertainty( vector<Real> real_vec )
{
  fis_ene_beta_d_uncertainty = real_vec;
  real_vec.clear();
}

void FissionDataContainer::set_fis_ene_neutrino_uncertainty( vector<Real> real_vec )
{
  fis_ene_neutrino_uncertainty = real_vec;
  real_vec.clear();
}

void FissionDataContainer::set_fis_ene_non_neutrino_uncertainty( vector<Real> real_vec )
{
  fis_ene_non_neutrino_uncertainty = real_vec;
  real_vec.clear();
}

void FissionDataContainer::set_fis_ene_index( vector<Integer> int_vec )
{
  fis_ene_index = int_vec;
  int_vec.clear();
}

void FissionDataContainer::set_fis_ene_evaluation_flg( vector<Integer> int_vec )
{
  fis_ene_evaluation_flg = int_vec;
  int_vec.clear();
}

void FissionDataContainer::set_fis_ene_table_int_data( vector<vector<Integer> > int_vec )
{
  fis_ene_table_int_data = int_vec;
  clr_obj.clear_vec_array2_int( int_vec);
}
  
void FissionDataContainer::set_fis_ene_table_range_data( vector<vector<Integer> > int_vec )
{
  fis_ene_table_range_data = int_vec;
  clr_obj.clear_vec_array2_int( int_vec);
}

void FissionDataContainer::set_fis_ene_table_ene_data( vector<vector<Real> > real_vec )
{
  fis_ene_table_ene_data = real_vec;
  clr_obj.clear_vec_array2_real( real_vec);
}

void FissionDataContainer::set_fis_ene_table_data( vector<vector<Real> > real_vec )
{
  fis_ene_table_data = real_vec;
  clr_obj.clear_vec_array2_real( real_vec);
}


void FissionDataContainer::set_photon_d_repr_flg( Integer int_data )
{
  photon_d_repr_flg = int_data;
}

void FissionDataContainer::set_photon_d_ene( vector<Real> real_vec )
{
  photon_d_ene = real_vec;
  real_vec.clear();
}

void FissionDataContainer::set_photon_d_int_data( vector<vector<Integer> > int_vec )
{
  photon_d_int_data = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void FissionDataContainer::set_photon_d_range_data( vector<vector<Integer> > int_vec )
{
  photon_d_range_data = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void FissionDataContainer::set_photon_d_time_data( vector<vector<Real> > real_vec )
{
  photon_d_time_data = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void FissionDataContainer::set_photon_d_data( vector<vector<Real> > real_vec )
{
  photon_d_data = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void FissionDataContainer::set_photon_d_precursor_decay_const( vector<Real> real_vec )
{
  photon_d_precursor_decay_const = real_vec;
  real_vec.clear();
}

void FissionDataContainer::set_fp_data_independent( vector<vector<Real> > real_vec )
{
  fp_data_independent = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void FissionDataContainer::set_state_designator_fp_independent( vector<vector<Real> > real_vec )
{
  state_designator_fp_independent = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void FissionDataContainer::set_yield_independent( vector<vector<Real> > real_vec )
{
  yield_independent = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void FissionDataContainer::set_yield_independent_uncertainty( vector<vector<Real> > real_vec )
{
  yield_independent_uncertainty = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void FissionDataContainer::set_incident_ene_independent( vector<Real> real_vec )
{
  incident_ene_independent = real_vec;
  real_vec.clear();
}

void FissionDataContainer::set_ene_int_data_independent( vector<Integer> int_vec )
{
  ene_int_data_independent = int_vec;
  int_vec.clear();
}

void FissionDataContainer::set_fp_data_cumulative( vector<vector<Real> > real_vec )
{
  fp_data_cumulative = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void FissionDataContainer::set_state_designator_fp_cumulative( vector<vector<Real> > real_vec )
{
  state_designator_fp_cumulative = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void FissionDataContainer::set_yield_cumulative( vector<vector<Real> > real_vec )
{
  yield_cumulative = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void FissionDataContainer::set_yield_cumulative_uncertainty( vector<vector<Real> > real_vec )
{
  yield_cumulative_uncertainty = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void FissionDataContainer::set_incident_ene_cumulative( vector<Real> real_vec )
{
  incident_ene_cumulative = real_vec;
  real_vec.clear();
}

void FissionDataContainer::set_ene_int_data_cumulative( vector<Integer> int_vec )
{
  ene_int_data_cumulative = int_vec;
  int_vec.clear();
}

