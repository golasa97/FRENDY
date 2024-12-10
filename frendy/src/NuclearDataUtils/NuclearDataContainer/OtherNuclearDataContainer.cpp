#include "NuclearDataUtils/NuclearDataContainer/OtherNuclearDataContainer.hpp"

using namespace frendy;

//constructor
OtherNuclearDataContainer::OtherNuclearDataContainer(void)
{
  clear();
}

//destructor
OtherNuclearDataContainer::~OtherNuclearDataContainer(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void OtherNuclearDataContainer::clear()
{
  reaction_type = unassigned_mt_no;
  atomic_no     = 0.0;

  scat_func_int_data.clear();
  scat_func_range_data.clear();
  scat_func_recoil_electron_data.clear();
  scat_func_data.clear();
  form_factor_int_data.clear();
  form_factor_range_data.clear();
  form_factor_ene_data.clear();
  form_factor_data.clear();
  first_subshell_type.clear();
  clr_obj.clear_vec_array2_real( second_subshell_type );
  clr_obj.clear_vec_array2_real( third_subshell_type );
  binding_ene_subshell.clear();
  electron_no.clear();
  clr_obj.clear_vec_array2_real( trans_probability );
  clr_obj.clear_vec_array2_real( trans_ene );
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Getter
Integer OtherNuclearDataContainer::get_reaction_type()
{
  return reaction_type;
}

Real OtherNuclearDataContainer::get_atomic_no()
{
  return atomic_no;
}

vector<Integer> OtherNuclearDataContainer::get_scat_func_int_data()
{
  return scat_func_int_data;
}

vector<Integer> OtherNuclearDataContainer::get_scat_func_range_data()
{
  return scat_func_range_data;
}

vector<Real> OtherNuclearDataContainer::get_scat_func_recoil_electron_data()
{
  return scat_func_recoil_electron_data;
}

vector<Real> OtherNuclearDataContainer::get_scat_func_data()
{
  return scat_func_data;
}

vector<Integer> OtherNuclearDataContainer::get_form_factor_int_data()
{
  return form_factor_int_data;
}

vector<Integer> OtherNuclearDataContainer::get_form_factor_range_data()
{
  return form_factor_range_data;
}

vector<Real> OtherNuclearDataContainer::get_form_factor_ene_data()
{
  return form_factor_ene_data;
}

vector<Real> OtherNuclearDataContainer::get_form_factor_data()
{
  return form_factor_data;
}

vector<Real> OtherNuclearDataContainer::get_first_subshell_type()
{
  return first_subshell_type;
}

vector<vector<Real> > OtherNuclearDataContainer::get_second_subshell_type()
{
  return second_subshell_type;
}

vector<vector<Real> > OtherNuclearDataContainer::get_third_subshell_type()
{
  return third_subshell_type;
}

vector<Real> OtherNuclearDataContainer::get_binding_ene_subshell()
{
  return binding_ene_subshell;
}

vector<Real> OtherNuclearDataContainer::get_electron_no()
{
  return electron_no;
}

vector<vector<Real> > OtherNuclearDataContainer::get_trans_probability()
{
  return trans_probability;
}

vector<vector<Real> > OtherNuclearDataContainer::get_trans_ene()
{
  return trans_ene;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void OtherNuclearDataContainer::set_reaction_type( Integer int_data )
{
  reaction_type = int_data;
}

void OtherNuclearDataContainer::set_atomic_no( Real real_data )
{
  atomic_no = real_data;
}

void OtherNuclearDataContainer::set_scat_func_int_data( vector<Integer> int_vec )
{
  scat_func_int_data = int_vec;
  int_vec.clear();
}

void OtherNuclearDataContainer::set_scat_func_range_data( vector<Integer> int_vec )
{
  scat_func_range_data = int_vec;
  int_vec.clear();
}

void OtherNuclearDataContainer::set_scat_func_recoil_electron_data( vector<Real> real_vec )
{
  scat_func_recoil_electron_data = real_vec;
  real_vec.clear();
}

void OtherNuclearDataContainer::set_scat_func_data( vector<Real> real_vec )
{
  scat_func_data = real_vec;
  real_vec.clear();
}

void OtherNuclearDataContainer::set_form_factor_int_data( vector<Integer> int_vec )
{
  form_factor_int_data = int_vec;
  int_vec.clear();
}

void OtherNuclearDataContainer::set_form_factor_range_data( vector<Integer> int_vec )
{
  form_factor_range_data = int_vec;
  int_vec.clear();
}

void OtherNuclearDataContainer::set_form_factor_ene_data( vector<Real> real_vec )
{
  form_factor_ene_data = real_vec;
  real_vec.clear();
}

void OtherNuclearDataContainer::set_form_factor_data( vector<Real> real_vec )
{
  form_factor_data = real_vec;
  real_vec.clear();
}

void OtherNuclearDataContainer::set_first_subshell_type( vector<Real> real_vec )
{
  first_subshell_type = real_vec;
  real_vec.clear();
}

void OtherNuclearDataContainer::set_second_subshell_type( vector<vector<Real> > real_vec )
{
  second_subshell_type = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void OtherNuclearDataContainer::set_third_subshell_type( vector<vector<Real> > real_vec )
{
  third_subshell_type = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void OtherNuclearDataContainer::set_binding_ene_subshell( vector<Real> real_vec )
{
  binding_ene_subshell = real_vec;
  real_vec.clear();
}

void OtherNuclearDataContainer::set_electron_no( vector<Real> real_vec )
{
  electron_no = real_vec;
  real_vec.clear();
}

void OtherNuclearDataContainer::set_trans_probability( vector<vector<Real> > real_vec )
{
  trans_probability = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void OtherNuclearDataContainer::set_trans_ene( vector<vector<Real> > real_vec )
{
  trans_ene = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

