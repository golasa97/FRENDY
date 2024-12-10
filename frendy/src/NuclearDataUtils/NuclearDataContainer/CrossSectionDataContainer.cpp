#include "NuclearDataUtils/NuclearDataContainer/CrossSectionDataContainer.hpp"

using namespace frendy;

//constructor
CrossSectionDataContainer::CrossSectionDataContainer(void)
{
  clear();
}

//destructor
CrossSectionDataContainer::~CrossSectionDataContainer(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void CrossSectionDataContainer::clear()
{
  reaction_type = unassigned_mt_no;
  reaction_flg  = 0;
  q_value_mass  = 0.0;
  q_value       = 0.0;

  xs_int_data.clear();
  xs_range_data.clear();
  xs_ene_data.clear();
  xs_data.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Getter
Integer CrossSectionDataContainer::get_reaction_type()
{
  return reaction_type;
}

Real CrossSectionDataContainer::get_q_value_mass()
{
  return q_value_mass;
}

Real CrossSectionDataContainer::get_q_value()
{
  return q_value;
}

Integer CrossSectionDataContainer::get_reaction_flg()
{
  return reaction_flg;
}

vector<Integer> CrossSectionDataContainer::get_xs_int_data()
{
  return xs_int_data;
}

vector<Integer> CrossSectionDataContainer::get_xs_range_data()
{
  return xs_range_data;
}

vector<Real> CrossSectionDataContainer::get_xs_ene_data()
{
  return xs_ene_data;
}

vector<Real> CrossSectionDataContainer::get_xs_data()
{
  return xs_data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void CrossSectionDataContainer::set_reaction_type( Integer int_data )
{
  reaction_type = int_data;
}

void CrossSectionDataContainer::set_q_value_mass( Real real_data )
{
  q_value_mass = real_data;
}

void CrossSectionDataContainer::set_q_value( Real real_data )
{
  q_value = real_data;
}

void CrossSectionDataContainer::set_reaction_flg( Integer int_data )
{
  reaction_flg = int_data;
}

void CrossSectionDataContainer::set_xs_int_data( vector<Integer> int_vec )
{
  xs_int_data = int_vec;
  int_vec.clear();
}

void CrossSectionDataContainer::set_xs_range_data( vector<Integer> int_vec )
{
  xs_range_data = int_vec;
  int_vec.clear();
}

void CrossSectionDataContainer::set_xs_ene_data( vector<Real> real_vec )
{
  xs_ene_data = real_vec;
  real_vec.clear();
}

void CrossSectionDataContainer::set_xs_data( vector<Real> real_vec )
{
  xs_data = real_vec;
  real_vec.clear();
}

