#include "NuclearDataUtils/NuclearDataContainer/PhotonDataContainer.hpp"

using namespace frendy;

//constructor
PhotonDataContainer::PhotonDataContainer(void)
{
  clear();
}

//destructor
PhotonDataContainer::~PhotonDataContainer(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PhotonDataContainer::clear()
{
  reaction_type         = unassigned_mt_no;
  level_no_max          = 0;
  trans_photon_ene_flg  = 0;
  ene_level_max         = 0.0;
  ene_level_no          = 0;
  isotropic_flg         = 0;
  angular_repr_flg      = 0;
  iso_photon_angular_no = 0;
  binding_ene_subshell  = 0.0;
  fluorescence_yield    = 0.0;

  multiplicity_ene_level.clear();
  multiplicity_binding_ene.clear();
  multiplicity_tot_int_data.clear();
  multiplicity_tot_range_data.clear();
  multiplicity_tot_ene_data.clear();
  multiplicity_tot_data.clear();
  clr_obj.clear_vec_array2_int( multiplicity_int_data );
  clr_obj.clear_vec_array2_int( multiplicity_range_data );
  clr_obj.clear_vec_array2_real( multiplicity_ene_data );
  clr_obj.clear_vec_array2_real( multiplicity_data );
  multiplicity_binding_ene_flg.clear();
  multiplicity_distr_law_no.clear();
  trans_ene_level.clear();
  direct_trans_probability.clear();
  photon_trans_probability.clear();
  photon_ene.clear();
  binding_ene.clear();
  binding_ene_flg.clear();
  distr_law_no.clear();
  photon_production_xs_tot_int_data.clear();
  photon_production_xs_tot_range_data.clear();
  photon_production_xs_tot_ene_data.clear();
  photon_production_xs_tot_data.clear();
  clr_obj.clear_vec_array2_int( photon_production_xs_int_data );
  clr_obj.clear_vec_array2_int( photon_production_xs_range_data );
  clr_obj.clear_vec_array2_real( photon_production_xs_ene_data );
  clr_obj.clear_vec_array2_real( photon_production_xs_data );
  angular_ene_level.clear();
  angular_photon_ene.clear();
  clr_obj.clear_vec_array2_int( angular_ene_int_data );
  clr_obj.clear_vec_array2_int( angular_ene_range_data );
  clr_obj.clear_vec_array2_real( angular_ene_data );
  clr_obj.clear_vec_array3_real( angular_legendre_coef_data );
  clr_obj.clear_vec_array3_int( angular_probability_int_data );
  clr_obj.clear_vec_array3_int( angular_probability_range_data );
  clr_obj.clear_vec_array3_real( angular_probability_cos_data );
  clr_obj.clear_vec_array3_real( angular_probability_data );
  ene_distr_law_no.clear();
  clr_obj.clear_vec_array2_int( ene_distr_weight_int_data );
  clr_obj.clear_vec_array2_int( ene_distr_weight_range_data );
  clr_obj.clear_vec_array2_real( ene_distr_weight_ene_data );
  clr_obj.clear_vec_array2_real( ene_distr_weight_data );
  clr_obj.clear_vec_array2_int( ene_distr_int_data );
  clr_obj.clear_vec_array2_int( ene_distr_range_data );
  clr_obj.clear_vec_array2_real( incident_ene );
  clr_obj.clear_vec_array3_int( ene_distr_nomalized_int_data );
  clr_obj.clear_vec_array3_int( ene_distr_nomalized_range_data );
  clr_obj.clear_vec_array3_real( ene_distr_nomalized_ene_data );
  clr_obj.clear_vec_array3_real( ene_distr_nomalized_data );
  photon_interaction_xs_int_data.clear();
  photon_interaction_xs_range_data.clear();
  photon_interaction_xs_ene_data.clear();
  photon_interaction_xs_data.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Getter
Integer PhotonDataContainer::get_reaction_type()
{
  return reaction_type;
}

vector<Real> PhotonDataContainer::get_multiplicity_ene_level()
{
  return multiplicity_ene_level;
}

vector<Real> PhotonDataContainer::get_multiplicity_binding_ene()
{
  return multiplicity_binding_ene;
}

vector<Integer> PhotonDataContainer::get_multiplicity_tot_int_data()
{
  return multiplicity_tot_int_data;
}

vector<Integer> PhotonDataContainer::get_multiplicity_tot_range_data()
{
  return multiplicity_tot_range_data;
}

vector<Real> PhotonDataContainer::get_multiplicity_tot_ene_data()
{
  return multiplicity_tot_ene_data;
}

vector<Real> PhotonDataContainer::get_multiplicity_tot_data()
{
  return multiplicity_tot_data;
}

vector<vector<Integer> > PhotonDataContainer::get_multiplicity_int_data()
{
  return multiplicity_int_data;
}

vector<vector<Integer> > PhotonDataContainer::get_multiplicity_range_data()
{
  return multiplicity_range_data;
}

vector<vector<Real> > PhotonDataContainer::get_multiplicity_ene_data()
{
  return multiplicity_ene_data;
}

vector<vector<Real> > PhotonDataContainer::get_multiplicity_data()
{
  return multiplicity_data;
}

vector<Integer> PhotonDataContainer::get_multiplicity_binding_ene_flg()
{
  return multiplicity_binding_ene_flg;
}

vector<Integer> PhotonDataContainer::get_multiplicity_distr_law_no()
{
  return multiplicity_distr_law_no;
}

Integer PhotonDataContainer::get_level_no_max()
{
  return level_no_max;
}

Integer PhotonDataContainer::get_trans_photon_ene_flg()
{
  return trans_photon_ene_flg;
}

Real PhotonDataContainer::get_ene_level_max()
{
  return ene_level_max;
}

vector<Real> PhotonDataContainer::get_trans_ene_level()
{
  return trans_ene_level;
}


vector<Real> PhotonDataContainer::get_direct_trans_probability()
{
  return direct_trans_probability;
}

vector<Real> PhotonDataContainer::get_photon_trans_probability()
{
  return photon_trans_probability;
}

Integer PhotonDataContainer::get_ene_level_no()
{
  return ene_level_no;
}

vector<Real> PhotonDataContainer::get_photon_ene()
{
  return photon_ene;
}

vector<Real> PhotonDataContainer::get_binding_ene()
{
  return binding_ene;
}

vector<Integer> PhotonDataContainer::get_binding_ene_flg()
{
  return binding_ene_flg;
}

vector<Integer> PhotonDataContainer::get_distr_law_no()
{
  return distr_law_no;
}

vector<Integer> PhotonDataContainer::get_photon_production_xs_tot_int_data()
{
  return photon_production_xs_tot_int_data;
}

vector<Integer> PhotonDataContainer::get_photon_production_xs_tot_range_data()
{
  return photon_production_xs_tot_range_data;
}

vector<Real> PhotonDataContainer::get_photon_production_xs_tot_ene_data()
{
  return photon_production_xs_tot_ene_data;
}

vector<Real> PhotonDataContainer::get_photon_production_xs_tot_data()
{
  return photon_production_xs_tot_data;
}

vector<vector<Integer> > PhotonDataContainer::get_photon_production_xs_int_data()
{
  return photon_production_xs_int_data;
}

vector<vector<Integer> > PhotonDataContainer::get_photon_production_xs_range_data()
{
  return photon_production_xs_range_data;
}

vector<vector<Real> > PhotonDataContainer::get_photon_production_xs_ene_data()
{
  return photon_production_xs_ene_data;
}

vector<vector<Real> > PhotonDataContainer::get_photon_production_xs_data()
{
  return photon_production_xs_data;
}

Integer PhotonDataContainer::get_isotropic_flg()
{
  return isotropic_flg;
}

Integer PhotonDataContainer::get_angular_repr_flg()
{
  return angular_repr_flg;
}

Integer PhotonDataContainer::get_iso_photon_angular_no()
{
  return iso_photon_angular_no;
}

vector<Real> PhotonDataContainer::get_angular_ene_level()
{
  return angular_ene_level;
}

vector<Real> PhotonDataContainer::get_angular_photon_ene()
{
  return angular_photon_ene;
}

vector<vector<Integer> > PhotonDataContainer::get_angular_ene_int_data()
{
  return angular_ene_int_data;
}

vector<vector<Integer> > PhotonDataContainer::get_angular_ene_range_data()
{
  return angular_ene_range_data;
}

vector<vector<Real> > PhotonDataContainer::get_angular_ene_data()
{
  return angular_ene_data;
}

vector<vector<vector<Real> > > PhotonDataContainer::get_angular_legendre_coef_data()
{
  return angular_legendre_coef_data;
}

vector<vector<vector<Integer> > > PhotonDataContainer::get_angular_probability_int_data()
{
  return angular_probability_int_data;
}

vector<vector<vector<Integer> > > PhotonDataContainer::get_angular_probability_range_data()
{
  return angular_probability_range_data;
}

vector<vector<vector<Real> > > PhotonDataContainer::get_angular_probability_cos_data()
{
  return angular_probability_cos_data;
}

vector<vector<vector<Real> > > PhotonDataContainer::get_angular_probability_data()
{
  return angular_probability_data;
}

vector<Integer> PhotonDataContainer::get_ene_distr_law_no()
{
  return ene_distr_law_no;
}

vector<vector<Integer> > PhotonDataContainer::get_ene_distr_weight_int_data()
{
  return ene_distr_weight_int_data;
}

vector<vector<Integer> > PhotonDataContainer::get_ene_distr_weight_range_data()
{
  return ene_distr_weight_range_data;
}

vector<vector<Real> > PhotonDataContainer::get_ene_distr_weight_ene_data()
{
  return ene_distr_weight_ene_data;
}

vector<vector<Real> > PhotonDataContainer::get_ene_distr_weight_data()
{
  return ene_distr_weight_data;
}

vector<vector<Integer> > PhotonDataContainer::get_ene_distr_int_data()
{
  return ene_distr_int_data;
}

vector<vector<Integer> > PhotonDataContainer::get_ene_distr_range_data()
{
  return ene_distr_range_data;
}

vector<vector<Real> > PhotonDataContainer::get_incident_ene()
{
  return incident_ene;
}

vector<vector<vector<Integer> > > PhotonDataContainer::get_ene_distr_nomalized_int_data()
{
  return ene_distr_nomalized_int_data;
}

vector<vector<vector<Integer> > > PhotonDataContainer::get_ene_distr_nomalized_range_data()
{
  return ene_distr_nomalized_range_data;
}

vector<vector<vector<Real> > > PhotonDataContainer::get_ene_distr_nomalized_ene_data()
{
  return ene_distr_nomalized_ene_data;
}

vector<vector<vector<Real> > > PhotonDataContainer::get_ene_distr_nomalized_data()
{
  return ene_distr_nomalized_data;
}

Real PhotonDataContainer::get_binding_ene_subshell()
{
  return binding_ene_subshell;
}

Real PhotonDataContainer::get_fluorescence_yield()
{
  return fluorescence_yield;
}

vector<Integer> PhotonDataContainer::get_photon_interaction_xs_int_data()
{
  return photon_interaction_xs_int_data;
}

vector<Integer> PhotonDataContainer::get_photon_interaction_xs_range_data()
{
  return photon_interaction_xs_range_data;
}

vector<Real> PhotonDataContainer::get_photon_interaction_xs_ene_data()
{
  return photon_interaction_xs_ene_data;
}

vector<Real> PhotonDataContainer::get_photon_interaction_xs_data()
{
  return photon_interaction_xs_data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void PhotonDataContainer::set_reaction_type( Integer int_data )
{
  reaction_type = int_data;
}

void PhotonDataContainer::set_multiplicity_ene_level( vector<Real> real_vec )
{
  multiplicity_ene_level = real_vec;
  real_vec.clear();
}

void PhotonDataContainer::set_multiplicity_binding_ene( vector<Real> real_vec )
{
  multiplicity_binding_ene = real_vec;
  real_vec.clear();
}

void PhotonDataContainer::set_multiplicity_tot_int_data( vector<Integer> int_vec )
{
  multiplicity_tot_int_data = int_vec;
  int_vec.clear();
}

void PhotonDataContainer::set_multiplicity_tot_range_data( vector<Integer> int_vec )
{
  multiplicity_tot_range_data = int_vec;
  int_vec.clear();
}

void PhotonDataContainer::set_multiplicity_tot_ene_data( vector<Real> real_vec )
{
  multiplicity_tot_ene_data = real_vec;
  real_vec.clear();
}

void PhotonDataContainer::set_multiplicity_tot_data( vector<Real> real_vec )
{
  multiplicity_tot_data = real_vec;
  real_vec.clear();
}

void PhotonDataContainer::set_multiplicity_int_data( vector<vector<Integer> > int_vec )
{
  multiplicity_int_data = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void PhotonDataContainer::set_multiplicity_range_data( vector<vector<Integer> > int_vec )
{
  multiplicity_range_data = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void PhotonDataContainer::set_multiplicity_ene_data( vector<vector<Real> > real_vec )
{
  multiplicity_ene_data = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void PhotonDataContainer::set_multiplicity_data( vector<vector<Real> > real_vec )
{
  multiplicity_data = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void PhotonDataContainer::set_multiplicity_binding_ene_flg( vector<Integer> int_vec )
{
  multiplicity_binding_ene_flg = int_vec;
  int_vec.clear();
}

void PhotonDataContainer::set_multiplicity_distr_law_no( vector<Integer> int_vec )
{
  multiplicity_distr_law_no = int_vec;
  int_vec.clear();
}

void PhotonDataContainer::set_level_no_max( Integer int_data )
{
  level_no_max = int_data;
}

void PhotonDataContainer::set_trans_photon_ene_flg( Integer int_data )
{
  trans_photon_ene_flg = int_data;
}

void PhotonDataContainer::set_ene_level_max( Real real_data )
{
  ene_level_max = real_data;
}

void PhotonDataContainer::set_trans_ene_level( vector<Real> real_vec )
{
  trans_ene_level = real_vec;
  real_vec.clear();
}

void PhotonDataContainer::set_direct_trans_probability( vector<Real> real_vec )
{
  direct_trans_probability = real_vec;
  real_vec.clear();
}

void PhotonDataContainer::set_photon_trans_probability( vector<Real> real_vec )
{
  photon_trans_probability = real_vec;
  real_vec.clear();
}

void PhotonDataContainer::set_ene_level_no( Integer int_data )
{
  ene_level_no = int_data;
}

void PhotonDataContainer::set_photon_ene( vector<Real> real_vec )
{
  photon_ene = real_vec;
  real_vec.clear();
}

void PhotonDataContainer::set_binding_ene( vector<Real> real_vec )
{
  binding_ene = real_vec;
  real_vec.clear();
}

void PhotonDataContainer::set_binding_ene_flg( vector<Integer> int_vec )
{
  binding_ene_flg = int_vec;
  int_vec.clear();
}

void PhotonDataContainer::set_distr_law_no( vector<Integer> int_vec )
{
  distr_law_no = int_vec;
  int_vec.clear();
}

void PhotonDataContainer::set_photon_production_xs_tot_int_data( vector<Integer> int_vec )
{
  photon_production_xs_tot_int_data = int_vec;
  int_vec.clear();
}

void PhotonDataContainer::set_photon_production_xs_tot_range_data( vector<Integer> int_vec )
{
  photon_production_xs_tot_range_data = int_vec;
  int_vec.clear();
}

void PhotonDataContainer::set_photon_production_xs_tot_ene_data( vector<Real> real_vec )
{
  photon_production_xs_tot_ene_data = real_vec;
  real_vec.clear();
}

void PhotonDataContainer::set_photon_production_xs_tot_data( vector<Real> real_vec )
{
  photon_production_xs_tot_data = real_vec;
  real_vec.clear();
}

void PhotonDataContainer::set_photon_production_xs_int_data( vector<vector<Integer> > int_vec )
{
  photon_production_xs_int_data = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void PhotonDataContainer::set_photon_production_xs_range_data( vector<vector<Integer> > int_vec )
{
  photon_production_xs_range_data = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void PhotonDataContainer::set_photon_production_xs_ene_data( vector<vector<Real> > real_vec )
{
  photon_production_xs_ene_data = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void PhotonDataContainer::set_photon_production_xs_data( vector<vector<Real> > real_vec )
{
  photon_production_xs_data = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void PhotonDataContainer::set_isotropic_flg( Integer int_data )
{
  isotropic_flg = int_data;
}

void PhotonDataContainer::set_angular_repr_flg( Integer int_data )
{
  angular_repr_flg = int_data;
}

void PhotonDataContainer::set_iso_photon_angular_no( Integer int_data )
{
  iso_photon_angular_no = int_data;
}

void PhotonDataContainer::set_angular_ene_level( vector<Real> real_vec )
{
  angular_ene_level = real_vec;
  real_vec.clear();
}

void PhotonDataContainer::set_angular_photon_ene( vector<Real> real_vec )
{
  angular_photon_ene = real_vec;
  real_vec.clear();
}

void PhotonDataContainer::set_angular_ene_int_data( vector<vector<Integer> > int_vec )
{
  angular_ene_int_data = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void PhotonDataContainer::set_angular_ene_range_data( vector<vector<Integer> > int_vec )
{
  angular_ene_range_data = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void PhotonDataContainer::set_angular_ene_data( vector<vector<Real> > real_vec )
{
  angular_ene_data = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void PhotonDataContainer::set_angular_legendre_coef_data( vector<vector<vector<Real> > > real_vec )
{
  angular_legendre_coef_data = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

void PhotonDataContainer::set_angular_probability_int_data( vector<vector<vector<Integer> > > int_vec )
{
  angular_probability_int_data = int_vec;
  clr_obj.clear_vec_array3_int( int_vec );
}

void PhotonDataContainer::set_angular_probability_range_data( vector<vector<vector<Integer> > > int_vec )
{
  angular_probability_range_data = int_vec;
  clr_obj.clear_vec_array3_int( int_vec );
}

void PhotonDataContainer::set_angular_probability_cos_data( vector<vector<vector<Real> > > real_vec )
{
  angular_probability_cos_data = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

void PhotonDataContainer::set_angular_probability_data( vector<vector<vector<Real> > > real_vec )
{
  angular_probability_data = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

void PhotonDataContainer::set_ene_distr_law_no( vector<Integer> int_vec )
{
  ene_distr_law_no = int_vec;
  int_vec.clear();
}

void PhotonDataContainer::set_ene_distr_weight_int_data( vector<vector<Integer> > int_vec )
{
  ene_distr_weight_int_data = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void PhotonDataContainer::set_ene_distr_weight_range_data( vector<vector<Integer> > int_vec )
{
  ene_distr_weight_range_data = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void PhotonDataContainer::set_ene_distr_weight_ene_data( vector<vector<Real> > real_vec )
{
  ene_distr_weight_ene_data = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void PhotonDataContainer::set_ene_distr_weight_data( vector<vector<Real> > real_vec )
{
  ene_distr_weight_data = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void PhotonDataContainer::set_ene_distr_int_data( vector<vector<Integer> > int_vec )
{
  ene_distr_int_data = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void PhotonDataContainer::set_ene_distr_range_data( vector<vector<Integer> > int_vec )
{
  ene_distr_range_data = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void PhotonDataContainer::set_incident_ene( vector<vector<Real> > real_vec )
{
  incident_ene = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void PhotonDataContainer::set_ene_distr_nomalized_int_data( vector<vector<vector<Integer> > > int_vec )
{
  ene_distr_nomalized_int_data = int_vec;
  clr_obj.clear_vec_array3_int( int_vec );
}

void PhotonDataContainer::set_ene_distr_nomalized_range_data( vector<vector<vector<Integer> > > int_vec )
{
  ene_distr_nomalized_range_data = int_vec;
  clr_obj.clear_vec_array3_int( int_vec );
}

void PhotonDataContainer::set_ene_distr_nomalized_ene_data( vector<vector<vector<Real> > > real_vec )
{
  ene_distr_nomalized_ene_data = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

void PhotonDataContainer::set_ene_distr_nomalized_data( vector<vector<vector<Real> > > real_vec )
{
  ene_distr_nomalized_data = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

void PhotonDataContainer::set_binding_ene_subshell( Real real_data )
{
  binding_ene_subshell = real_data;
}

void PhotonDataContainer::set_fluorescence_yield( Real real_data )
{
  fluorescence_yield = real_data;
}

void PhotonDataContainer::set_photon_interaction_xs_int_data( vector<Integer> int_vec )
{
  photon_interaction_xs_int_data = int_vec;
  int_vec.clear();
}

void PhotonDataContainer::set_photon_interaction_xs_range_data( vector<Integer> int_vec )
{
  photon_interaction_xs_range_data = int_vec;
  int_vec.clear();
}

void PhotonDataContainer::set_photon_interaction_xs_ene_data( vector<Real> real_vec )
{
  photon_interaction_xs_ene_data = real_vec;
  real_vec.clear();
}

void PhotonDataContainer::set_photon_interaction_xs_data( vector<Real> real_vec )
{
  photon_interaction_xs_data = real_vec;
  real_vec.clear();
}

