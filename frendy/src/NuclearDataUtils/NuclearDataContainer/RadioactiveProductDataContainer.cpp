#include "NuclearDataUtils/NuclearDataContainer/RadioactiveProductDataContainer.hpp"

using namespace frendy;

//constructor
RadioactiveProductDataContainer::RadioactiveProductDataContainer(void)
{
  clear();
}

//destructor
RadioactiveProductDataContainer::~RadioactiveProductDataContainer(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void RadioactiveProductDataContainer::clear()
{
  reaction_type                = unassigned_mt_no;
  state_no_target              = 0;
  state_no_target_iso          = 0;
  decay_chain_flg              = 0;
  xs_state_no_target           = 0;
  multiplicity_state_no_target = 0;

  mat_data_produced.clear();
  contain_data_list.clear();
  state_no_product.clear();
  excitation_ene.clear();
  clr_obj.clear_vec_array2_real( half_life );
  clr_obj.clear_vec_array2_real( decay_type );
  clr_obj.clear_vec_array2_real( mat_data_daughter );
  clr_obj.clear_vec_array2_real( branching_ratio_daughter );
  clr_obj.clear_vec_array2_real( endpoint_ene_daughter );
  clr_obj.clear_vec_array2_real( chain_terminator_daughter );
  multiplicity_state_no_product.clear();
  multiplicity_q_value_mass.clear();
  multiplicity_q_value.clear();
  multiplicity_mat_data_product.clear();
  clr_obj.clear_vec_array2_int( multiplicity_int_data );
  clr_obj.clear_vec_array2_int( multiplicity_range_data );
  clr_obj.clear_vec_array2_real( multiplicity_ene_data );
  clr_obj.clear_vec_array2_real( multiplicity_data );
  xs_state_no_product.clear();
  xs_q_value_mass.clear();
  xs_q_value.clear();
  xs_mat_data_product.clear();
  clr_obj.clear_vec_array2_int( xs_int_data );
  clr_obj.clear_vec_array2_int( xs_range_data );
  clr_obj.clear_vec_array2_real( xs_ene_data );
  clr_obj.clear_vec_array2_real( xs_data );
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Getter
Integer RadioactiveProductDataContainer::get_reaction_type()
{
  return reaction_type;
}

vector<Real> RadioactiveProductDataContainer::get_mat_data_produced()
{
  return mat_data_produced;
}

vector<Integer> RadioactiveProductDataContainer::get_contain_data_list()
{
  return contain_data_list;
}

Integer RadioactiveProductDataContainer::get_state_no_target()
{
  return state_no_target;
}

Integer RadioactiveProductDataContainer::get_state_no_target_iso()
{
  return state_no_target_iso;
}

vector<Integer> RadioactiveProductDataContainer::get_state_no_product()
{
  return state_no_product;
}

vector<Real> RadioactiveProductDataContainer::get_excitation_ene()
{
  return excitation_ene;
}

Integer RadioactiveProductDataContainer::get_decay_chain_flg()
{
  return decay_chain_flg;
}

vector<vector<Real> > RadioactiveProductDataContainer::get_half_life()
{
  return half_life;
}

vector<vector<Real> > RadioactiveProductDataContainer::get_decay_type()
{
  return decay_type;
}

vector<vector<Real> > RadioactiveProductDataContainer::get_mat_data_daughter()
{
  return mat_data_daughter;
}

vector<vector<Real> > RadioactiveProductDataContainer::get_branching_ratio_daughter()
{
  return branching_ratio_daughter;
}

vector<vector<Real> > RadioactiveProductDataContainer::get_endpoint_ene_daughter()
{
  return endpoint_ene_daughter;
}

vector<vector<Real> > RadioactiveProductDataContainer::get_chain_terminator_daughter()
{
  return chain_terminator_daughter;
}

Integer RadioactiveProductDataContainer::get_multiplicity_state_no_target()
{
  return multiplicity_state_no_target;
}

vector<Integer> RadioactiveProductDataContainer::get_multiplicity_state_no_product()
{
  return multiplicity_state_no_product;
}

vector<Real> RadioactiveProductDataContainer::get_multiplicity_q_value_mass()
{
  return multiplicity_q_value_mass;
}

vector<Real> RadioactiveProductDataContainer::get_multiplicity_q_value()
{
  return multiplicity_q_value;
}

vector<Integer> RadioactiveProductDataContainer::get_multiplicity_mat_data_product()
{
  return multiplicity_mat_data_product;
}

vector<vector<Integer> > RadioactiveProductDataContainer::get_multiplicity_int_data()
{
  return multiplicity_int_data;
}

vector<vector<Integer> > RadioactiveProductDataContainer::get_multiplicity_range_data()
{
  return multiplicity_range_data;
}

vector<vector<Real> > RadioactiveProductDataContainer::get_multiplicity_ene_data()
{
  return multiplicity_ene_data;
}

vector<vector<Real> > RadioactiveProductDataContainer::get_multiplicity_data()
{
  return multiplicity_data;
}

Integer RadioactiveProductDataContainer::get_xs_state_no_target()
{
  return xs_state_no_target;
}

vector<Integer> RadioactiveProductDataContainer::get_xs_state_no_product()
{
  return xs_state_no_product;
}

vector<Real> RadioactiveProductDataContainer::get_xs_q_value_mass()
{
  return xs_q_value_mass;
}

vector<Real> RadioactiveProductDataContainer::get_xs_q_value()
{
  return xs_q_value;
}

vector<Integer> RadioactiveProductDataContainer::get_xs_mat_data_product()
{
  return xs_mat_data_product;
}

vector<vector<Integer> > RadioactiveProductDataContainer::get_xs_int_data()
{
  return xs_int_data;
}

vector<vector<Integer> > RadioactiveProductDataContainer::get_xs_range_data()
{
  return xs_range_data;
}

vector<vector<Real> > RadioactiveProductDataContainer::get_xs_ene_data()
{
  return xs_ene_data;
}

vector<vector<Real> > RadioactiveProductDataContainer::get_xs_data()
{
  return xs_data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void RadioactiveProductDataContainer::set_reaction_type( Integer int_data )
{
  reaction_type = int_data;
}

void RadioactiveProductDataContainer::set_mat_data_produced( vector<Real> real_vec )
{
  mat_data_produced = real_vec;
  real_vec.clear();
}

void RadioactiveProductDataContainer::set_contain_data_list( vector<Integer> int_vec )
{
  contain_data_list = int_vec;
  int_vec.clear();
}

void RadioactiveProductDataContainer::set_state_no_target( Integer int_data )
{
  state_no_target = int_data;
}

void RadioactiveProductDataContainer::set_state_no_target_iso( Integer int_data )
{
  state_no_target_iso = int_data;
}

void RadioactiveProductDataContainer::set_state_no_product( vector<Integer> int_vec )
{
  state_no_product = int_vec;
  int_vec.clear();
}

void RadioactiveProductDataContainer::set_excitation_ene( vector<Real> real_vec )
{
  excitation_ene = real_vec;
  real_vec.clear();
}

void RadioactiveProductDataContainer::set_decay_chain_flg( Integer int_data )
{
  decay_chain_flg = int_data;
}

void RadioactiveProductDataContainer::set_half_life( vector<vector<Real> > real_vec )
{
  half_life = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void RadioactiveProductDataContainer::set_decay_type( vector<vector<Real> > real_vec )
{
  decay_type = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void RadioactiveProductDataContainer::set_mat_data_daughter( vector<vector<Real> > real_vec )
{
  mat_data_daughter = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void RadioactiveProductDataContainer::set_branching_ratio_daughter( vector<vector<Real> > real_vec )
{
  branching_ratio_daughter = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void RadioactiveProductDataContainer::set_endpoint_ene_daughter( vector<vector<Real> > real_vec )
{
  endpoint_ene_daughter = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void RadioactiveProductDataContainer::set_chain_terminator_daughter( vector<vector<Real> > real_vec )
{
  chain_terminator_daughter = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void RadioactiveProductDataContainer::set_multiplicity_state_no_target( Integer int_data )
{
  multiplicity_state_no_target = int_data;
}

void RadioactiveProductDataContainer::set_multiplicity_state_no_product( vector<Integer> int_vec )
{
  multiplicity_state_no_product = int_vec;
  int_vec.clear();
}

void RadioactiveProductDataContainer::set_multiplicity_q_value_mass( vector<Real> real_vec )
{
  multiplicity_q_value_mass = real_vec;
  real_vec.clear();
}

void RadioactiveProductDataContainer::set_multiplicity_q_value( vector<Real> real_vec )
{
  multiplicity_q_value = real_vec;
  real_vec.clear();
}

void RadioactiveProductDataContainer::set_multiplicity_mat_data_product( vector<Integer> int_vec )
{
  multiplicity_mat_data_product = int_vec;
  int_vec.clear();
}

void RadioactiveProductDataContainer::set_multiplicity_int_data( vector<vector<Integer> > int_vec )
{
  multiplicity_int_data = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void RadioactiveProductDataContainer::set_multiplicity_range_data( vector<vector<Integer> > int_vec )
{
  multiplicity_range_data = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void RadioactiveProductDataContainer::set_multiplicity_ene_data( vector<vector<Real> > real_vec )
{
  multiplicity_ene_data = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void RadioactiveProductDataContainer::set_multiplicity_data( vector<vector<Real> > real_vec )
{
  multiplicity_data = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void RadioactiveProductDataContainer::set_xs_state_no_target( Integer int_data )
{
  xs_state_no_target = int_data;
}

void RadioactiveProductDataContainer::set_xs_state_no_product( vector<Integer> int_vec )
{
  xs_state_no_product = int_vec;
  int_vec.clear();
}

void RadioactiveProductDataContainer::set_xs_q_value_mass( vector<Real> real_vec )
{
  xs_q_value_mass = real_vec;
  real_vec.clear();
}

void RadioactiveProductDataContainer::set_xs_q_value( vector<Real> real_vec )
{
  xs_q_value = real_vec;
  real_vec.clear();
}

void RadioactiveProductDataContainer::set_xs_mat_data_product( vector<Integer> int_vec )
{
  xs_mat_data_product = int_vec;
  int_vec.clear();
}

void RadioactiveProductDataContainer::set_xs_int_data( vector<vector<Integer> > int_vec )
{
  xs_int_data = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void RadioactiveProductDataContainer::set_xs_range_data( vector<vector<Integer> > int_vec )
{
  xs_range_data = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void RadioactiveProductDataContainer::set_xs_ene_data( vector<vector<Real> > real_vec )
{
  xs_ene_data = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void RadioactiveProductDataContainer::set_xs_data( vector<vector<Real> > real_vec )
{
  xs_data = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

