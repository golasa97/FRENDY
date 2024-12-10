#include "NuclearDataUtils/NuclearDataContainer/ResonanceData/UnresolvedProbabilityDataContainer.hpp"

using namespace frendy;

//constructor
UnresolvedProbabilityDataContainer::UnresolvedProbabilityDataContainer(void)
{
  clear();
}

//destructor
UnresolvedProbabilityDataContainer::~UnresolvedProbabilityDataContainer(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void UnresolvedProbabilityDataContainer::clear()
{
  comp_flg_inela     = 0;
  comp_flg_abs       = 0;
  prob_int           = 0;
  prob_bin_no        = 0;
  self_shielding_flg = 0;
  comp_flg           = 0;
  prob_ene_no        = 0;

  temp = 0.0;

  prob_ene.clear();

  clr_obj.clear_vec_array2_real( prob_heat );
  clr_obj.clear_vec_array2_real( prob_table_sample_no );
  clr_obj.clear_vec_array3_real( prob_table );
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Getter
Integer UnresolvedProbabilityDataContainer::get_comp_flg_inela()
{
  return comp_flg_inela;
}

Integer UnresolvedProbabilityDataContainer::get_comp_flg_abs()
{
  return comp_flg_abs;
}

Integer UnresolvedProbabilityDataContainer::get_prob_int()
{
  return prob_int;
}

Integer UnresolvedProbabilityDataContainer::get_prob_bin_no()
{
  return prob_bin_no;
}

Integer UnresolvedProbabilityDataContainer::get_self_shielding_flg()
{
  return self_shielding_flg;
}

Integer UnresolvedProbabilityDataContainer::get_comp_flg()
{
  return comp_flg;
}

Integer UnresolvedProbabilityDataContainer::get_prob_ene_no()
{
  return prob_ene_no;
}

Real UnresolvedProbabilityDataContainer::get_temp()
{
  return temp;
}

vector<Real> UnresolvedProbabilityDataContainer::get_prob_ene()
{
  return prob_ene;
}

vector<vector<Real> > UnresolvedProbabilityDataContainer::get_prob_heat()
{
  return prob_heat;
}

vector<vector<Real> > UnresolvedProbabilityDataContainer::get_prob_table_sample_no()
{
  return prob_table_sample_no;
}

vector<vector<vector<Real> > > UnresolvedProbabilityDataContainer::get_prob_table()
{
  return prob_table;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void UnresolvedProbabilityDataContainer::set_comp_flg_inela( Integer int_data )
{
  comp_flg_inela = int_data;
}

void UnresolvedProbabilityDataContainer::set_comp_flg_abs( Integer int_data )
{
  comp_flg_abs = int_data;
}

void UnresolvedProbabilityDataContainer::set_prob_int( Integer int_data )
{
  prob_int = int_data;
}

void UnresolvedProbabilityDataContainer::set_prob_bin_no( Integer int_data )
{
  prob_bin_no = int_data;
}

void UnresolvedProbabilityDataContainer::set_self_shielding_flg( Integer int_data )
{
  self_shielding_flg = int_data;
}

void UnresolvedProbabilityDataContainer::set_comp_flg( Integer int_data )
{
  comp_flg = int_data;
}

void UnresolvedProbabilityDataContainer::set_prob_ene_no( Integer int_data )
{
  prob_ene_no = int_data;
}

void UnresolvedProbabilityDataContainer::set_temp( Real real_data )
{
  temp = real_data;
}

void UnresolvedProbabilityDataContainer::set_prob_ene( vector<Real> real_vec )
{
  prob_ene = real_vec;
  real_vec.clear();
}

void UnresolvedProbabilityDataContainer::set_prob_heat( vector<vector<Real> > real_vec )
{
  prob_heat = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void UnresolvedProbabilityDataContainer::set_prob_table_sample_no( vector<vector<Real> > real_vec )
{
  prob_table_sample_no = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void UnresolvedProbabilityDataContainer::set_prob_table( vector<vector<vector<Real> > > real_vec )
{
  prob_table = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

