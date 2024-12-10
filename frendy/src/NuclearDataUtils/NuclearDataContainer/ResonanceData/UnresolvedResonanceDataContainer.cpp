#include "NuclearDataUtils/NuclearDataContainer/ResonanceData/UnresolvedResonanceDataContainer.hpp"

using namespace frendy;

//constructor
UnresolvedResonanceDataContainer::UnresolvedResonanceDataContainer(void)
{
  clear();
}

//destructor
UnresolvedResonanceDataContainer::~UnresolvedResonanceDataContainer(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void UnresolvedResonanceDataContainer::clear()
{
  fis_width_flg      = 0;
  xs_formula_flg     = 0;
  self_shielding_flg = 0;

  clr_obj.clear_vec_array3_real( level_spacing );
  clr_obj.clear_vec_array2_real( j_value_abs );
  clr_obj.clear_vec_array2_real( freedom_n );
  clr_obj.clear_vec_array3_real( ave_gam_width_n );
  clr_obj.clear_vec_array3_real( ave_gam_width_rad );
  clr_obj.clear_vec_array3_real( ene_unreso );
  clr_obj.clear_vec_array2_int( freedom_fis_int );
  clr_obj.clear_vec_array3_real( ave_gam_width_fis );
  clr_obj.clear_vec_array2_int( unreso_int_data );
  clr_obj.clear_vec_array2_real( freedom_comp );
  clr_obj.clear_vec_array2_real( freedom_rad );
  clr_obj.clear_vec_array2_real( freedom_fis );
  clr_obj.clear_vec_array3_real( ave_gam_width_comp );
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Getter
Integer UnresolvedResonanceDataContainer::get_fis_width_flg()
{
  return fis_width_flg;
}

Integer UnresolvedResonanceDataContainer::get_xs_formula_flg()
{
  return xs_formula_flg;
}

Integer UnresolvedResonanceDataContainer::get_self_shielding_flg()
{
  return self_shielding_flg;
}

vector<vector<vector<Real> > > UnresolvedResonanceDataContainer::get_level_spacing()
{
  return level_spacing;
}

vector<vector<Real> > UnresolvedResonanceDataContainer::get_j_value_abs()
{
  return j_value_abs;
}

vector<vector<Real> > UnresolvedResonanceDataContainer::get_freedom_n()
{
  return freedom_n;
}

vector<vector<vector<Real> > > UnresolvedResonanceDataContainer::get_ave_gam_width_n()
{
  return ave_gam_width_n;
}

vector<vector<vector<Real> > > UnresolvedResonanceDataContainer::get_ave_gam_width_rad()
{
  return ave_gam_width_rad;
}

vector<vector<vector<Real> > > UnresolvedResonanceDataContainer::get_ene_unreso()
{
  return ene_unreso;
}

vector<vector<Integer> > UnresolvedResonanceDataContainer::get_freedom_fis_int()
{
  return freedom_fis_int;
}

vector<vector<vector<Real> > > UnresolvedResonanceDataContainer::get_ave_gam_width_fis()
{
  return ave_gam_width_fis;
}

vector<vector<Integer> > UnresolvedResonanceDataContainer::get_unreso_int_data()
{
  return unreso_int_data;
}

vector<vector<Real> > UnresolvedResonanceDataContainer::get_freedom_comp()
{
  return freedom_comp;
}

vector<vector<Real> > UnresolvedResonanceDataContainer::get_freedom_rad()
{
  return freedom_rad;
}

vector<vector<Real> > UnresolvedResonanceDataContainer::get_freedom_fis()
{
  return freedom_fis;
}

vector<vector<vector<Real> > > UnresolvedResonanceDataContainer::get_ave_gam_width_comp()
{
  return ave_gam_width_comp;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void UnresolvedResonanceDataContainer::set_fis_width_flg( Integer int_data )
{
  fis_width_flg = int_data;
}

void UnresolvedResonanceDataContainer::set_xs_formula_flg( Integer int_data )
{
  xs_formula_flg = int_data;
}

void UnresolvedResonanceDataContainer::set_self_shielding_flg( Integer int_data )
{
  self_shielding_flg = int_data;
}

void UnresolvedResonanceDataContainer::set_level_spacing( vector<vector<vector<Real> > > real_vec )
{
  level_spacing = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

void UnresolvedResonanceDataContainer::set_j_value_abs( vector<vector<Real> > real_vec )
{
  j_value_abs = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void UnresolvedResonanceDataContainer::set_freedom_n( vector<vector<Real> > real_vec )
{
  freedom_n = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void UnresolvedResonanceDataContainer::set_ave_gam_width_n( vector<vector<vector<Real> > > real_vec )
{
  ave_gam_width_n = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

void UnresolvedResonanceDataContainer::set_ave_gam_width_rad( vector<vector<vector<Real> > > real_vec )
{
  ave_gam_width_rad = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

void UnresolvedResonanceDataContainer::set_ene_unreso( vector<vector<vector<Real> > > real_vec )
{
  ene_unreso = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

void UnresolvedResonanceDataContainer::set_freedom_fis_int( vector<vector<Integer> > int_vec )
{
  freedom_fis_int = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void UnresolvedResonanceDataContainer::set_ave_gam_width_fis( vector<vector<vector<Real> > > real_vec )
{
  ave_gam_width_fis = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

void UnresolvedResonanceDataContainer::set_unreso_int_data( vector<vector<Integer> > int_vec )
{
  unreso_int_data = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void UnresolvedResonanceDataContainer::set_freedom_comp( vector<vector<Real> > real_vec )
{
  freedom_comp = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void UnresolvedResonanceDataContainer::set_freedom_rad( vector<vector<Real> > real_vec )
{
  freedom_rad = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void UnresolvedResonanceDataContainer::set_freedom_fis( vector<vector<Real> > real_vec )
{
  freedom_fis = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void UnresolvedResonanceDataContainer::set_ave_gam_width_comp( vector<vector<vector<Real> > > real_vec )
{
  ave_gam_width_comp = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

