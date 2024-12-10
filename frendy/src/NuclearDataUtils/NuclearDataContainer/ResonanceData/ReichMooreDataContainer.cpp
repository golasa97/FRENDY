#include "NuclearDataUtils/NuclearDataContainer/ResonanceData/ReichMooreDataContainer.hpp"

using namespace frendy;

//constructor
ReichMooreDataContainer::ReichMooreDataContainer(void)
{
  clear();
}

//destructor
ReichMooreDataContainer::~ReichMooreDataContainer(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ReichMooreDataContainer::clear()
{
  angular_distr_calc_flg = 0;
  l_no_conv_calc         = 0;

  scat_radius_l.clear();
  clr_obj.clear_vec_array2_real( ene_reso );
  clr_obj.clear_vec_array2_real( j_value_abs );
  clr_obj.clear_vec_array2_real( gam_width_n );
  clr_obj.clear_vec_array2_real( gam_width_rad );
  clr_obj.clear_vec_array2_real( gam_width_fis_a );
  clr_obj.clear_vec_array2_real( gam_width_fis_b );
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Getter
Integer ReichMooreDataContainer::get_angular_distr_calc_flg()
{
  return angular_distr_calc_flg;
}

Integer ReichMooreDataContainer::get_l_no_conv_calc()
{
  return l_no_conv_calc;
}

vector<Real> ReichMooreDataContainer::get_scat_radius_l()
{
  return scat_radius_l;
}

vector<vector<Real> > ReichMooreDataContainer::get_ene_reso()
{
  return ene_reso;
}

vector<vector<Real> > ReichMooreDataContainer::get_j_value_abs()
{
  return j_value_abs;
}

vector<vector<Real> > ReichMooreDataContainer::get_gam_width_n()
{
  return gam_width_n;
}

vector<vector<Real> > ReichMooreDataContainer::get_gam_width_rad()
{
  return gam_width_rad;
}

vector<vector<Real> > ReichMooreDataContainer::get_gam_width_fis_a()
{
  return gam_width_fis_a;
}

vector<vector<Real> > ReichMooreDataContainer::get_gam_width_fis_b()
{
  return gam_width_fis_b;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void ReichMooreDataContainer::set_angular_distr_calc_flg( Integer int_data )
{
  angular_distr_calc_flg = int_data;
}

void ReichMooreDataContainer::set_l_no_conv_calc( Integer int_data )
{
  l_no_conv_calc = int_data;
}

void ReichMooreDataContainer::set_scat_radius_l( vector<Real> real_vec )
{
  scat_radius_l = real_vec;
  real_vec.clear();
}

void ReichMooreDataContainer::set_ene_reso( vector<vector<Real> > real_vec )
{
  ene_reso = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void ReichMooreDataContainer::set_j_value_abs( vector<vector<Real> > real_vec )
{
  j_value_abs = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void ReichMooreDataContainer::set_gam_width_n( vector<vector<Real> > real_vec )
{
  gam_width_n = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void ReichMooreDataContainer::set_gam_width_rad( vector<vector<Real> > real_vec )
{
  gam_width_rad = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void ReichMooreDataContainer::set_gam_width_fis_a( vector<vector<Real> > real_vec )
{
  gam_width_fis_a = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void ReichMooreDataContainer::set_gam_width_fis_b( vector<vector<Real> > real_vec )
{
  gam_width_fis_b = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

