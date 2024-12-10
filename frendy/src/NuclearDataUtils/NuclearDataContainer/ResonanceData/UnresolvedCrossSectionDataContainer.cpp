#include "NuclearDataUtils/NuclearDataContainer/ResonanceData/UnresolvedCrossSectionDataContainer.hpp"

using namespace frendy;

//constructor
UnresolvedCrossSectionDataContainer::UnresolvedCrossSectionDataContainer(void)
{
  clear();
}

//destructor
UnresolvedCrossSectionDataContainer::~UnresolvedCrossSectionDataContainer(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void UnresolvedCrossSectionDataContainer::clear()
{
  self_shielding_flg = 0;
  unreso_opt_int     = 0;
  unreso_opt_a       = 0;
  unreso_opt_b       = 0;
  unreso_data_no     = 0;
  temp               = 0.0;

  unreso_ene.clear();
  unreso_sig_tot.clear();
  unreso_sig_scat.clear();
  unreso_sig_fis.clear();
  unreso_sig_rad.clear();
  sig_zero.clear();
  clr_obj.clear_vec_array3_real8(bondarenko_table);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Getter
Integer UnresolvedCrossSectionDataContainer::get_self_shielding_flg()
{
  return self_shielding_flg;
}

Integer UnresolvedCrossSectionDataContainer::get_unreso_opt_int()
{
  return unreso_opt_int;
}

Integer UnresolvedCrossSectionDataContainer::get_unreso_opt_a()
{
  return unreso_opt_a;
}

Integer UnresolvedCrossSectionDataContainer::get_unreso_opt_b()
{
  return unreso_opt_b;
}

Integer UnresolvedCrossSectionDataContainer::get_unreso_data_no()
{
  return unreso_data_no;
}

Real UnresolvedCrossSectionDataContainer::get_temp()
{
  return temp;
}

vector<Real> UnresolvedCrossSectionDataContainer::get_unreso_ene()
{
  return unreso_ene;
}

vector<Real> UnresolvedCrossSectionDataContainer::get_unreso_sig_tot()
{
  return unreso_sig_tot;
}

vector<Real> UnresolvedCrossSectionDataContainer::get_unreso_sig_scat()
{
  return unreso_sig_scat;
}

vector<Real> UnresolvedCrossSectionDataContainer::get_unreso_sig_fis()
{
  return unreso_sig_fis;
}

vector<Real> UnresolvedCrossSectionDataContainer::get_unreso_sig_rad()
{
  return unreso_sig_rad;
}

vector<Real> UnresolvedCrossSectionDataContainer::get_sig_zero()
{
  return sig_zero;
}

vector<vector<vector<Real> > > UnresolvedCrossSectionDataContainer::get_bondarenko_table()
{
  return bondarenko_table;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void UnresolvedCrossSectionDataContainer::set_self_shielding_flg( Integer int_data )
{
  self_shielding_flg = int_data;
}

void UnresolvedCrossSectionDataContainer::set_unreso_opt_int( Integer int_data )
{
  unreso_opt_int = int_data;
}

void UnresolvedCrossSectionDataContainer::set_unreso_opt_a( Integer int_data )
{
  unreso_opt_a = int_data;
}

void UnresolvedCrossSectionDataContainer::set_unreso_opt_b( Integer int_data )
{
  unreso_opt_b = int_data;
}

void UnresolvedCrossSectionDataContainer::set_unreso_data_no( Integer int_data )
{
  unreso_data_no = int_data;
}

void UnresolvedCrossSectionDataContainer::set_temp( Real real_data )
{
  temp = real_data;
}

void UnresolvedCrossSectionDataContainer::set_unreso_ene( vector<Real> real_vec )
{
  unreso_ene = real_vec;
  real_vec.clear();
}

void UnresolvedCrossSectionDataContainer::set_unreso_sig_tot( vector<Real> real_vec )
{
  unreso_sig_tot = real_vec;
  real_vec.clear();
}

void UnresolvedCrossSectionDataContainer::set_unreso_sig_scat( vector<Real> real_vec )
{
  unreso_sig_scat = real_vec;
  real_vec.clear();
}

void UnresolvedCrossSectionDataContainer::set_unreso_sig_fis( vector<Real> real_vec )
{
  unreso_sig_fis = real_vec;
  real_vec.clear();
}

void UnresolvedCrossSectionDataContainer::set_unreso_sig_rad( vector<Real> real_vec )
{
  unreso_sig_rad = real_vec;
  real_vec.clear();
}

void UnresolvedCrossSectionDataContainer::set_sig_zero( vector<Real> real_vec )
{
  sig_zero = real_vec;
  real_vec.clear();
}

void UnresolvedCrossSectionDataContainer::set_bondarenko_table( vector<vector<vector<Real> > > real_vec )
{
  bondarenko_table = real_vec;
  clr_obj.clear_vec_array3_real8(real_vec);
}

