#include "NuclearDataUtils/CovarianceDataContainer/CovarianceResonanceData/CompatibleResolvedResonanceDataContainer.hpp"

using namespace frendy;

//constructor
CompatibleResolvedResonanceDataContainer::CompatibleResolvedResonanceDataContainer(void)
{
  clear();
}

//destructor
CompatibleResolvedResonanceDataContainer::~CompatibleResolvedResonanceDataContainer(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void CompatibleResolvedResonanceDataContainer::clear()
{
  scat_radius_uncertainty = 0.0;

  l_value.clear();
  mass_isotope.clear();
  clr_obj.clear_vec_array2_real( ene_reso );
  clr_obj.clear_vec_array2_real( j_value_abs );
  clr_obj.clear_vec_array2_real( gam_width_tot );
  clr_obj.clear_vec_array2_real( gam_width_n );
  clr_obj.clear_vec_array2_real( gam_width_rad );
  clr_obj.clear_vec_array2_real( gam_width_fis );
  clr_obj.clear_vec_array2_real( ene_reso_variance );
  clr_obj.clear_vec_array2_real( gam_width_n_variance );
  clr_obj.clear_vec_array2_real( gam_width_n_rad_cov );
  clr_obj.clear_vec_array2_real( gam_width_rad_variance );
  clr_obj.clear_vec_array2_real( gam_width_n_rad_fis );
  clr_obj.clear_vec_array2_real( gam_width_rad_fis_cov );
  clr_obj.clear_vec_array2_real( gam_width_fis_variance );
  clr_obj.clear_vec_array2_real( gam_width_n_j_cov );
  clr_obj.clear_vec_array2_real( gam_width_rad_j_cov );
  clr_obj.clear_vec_array2_real( gam_width_fis_j_cov );
  clr_obj.clear_vec_array2_real( j_value_variance );
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Getter
Real CompatibleResolvedResonanceDataContainer::get_scat_radius_uncertainty()
{
  return scat_radius_uncertainty;
}

vector<Integer> CompatibleResolvedResonanceDataContainer::get_l_value()
{
  return l_value;
}

vector<Real> CompatibleResolvedResonanceDataContainer::get_mass_isotope()
{
  return mass_isotope;
}

vector<vector<Real> > CompatibleResolvedResonanceDataContainer::get_ene_reso()
{
  return ene_reso;
}

vector<vector<Real> > CompatibleResolvedResonanceDataContainer::get_j_value_abs()
{
  return j_value_abs;
}

vector<vector<Real> > CompatibleResolvedResonanceDataContainer::get_gam_width_tot()
{
  return gam_width_tot;
}

vector<vector<Real> > CompatibleResolvedResonanceDataContainer::get_gam_width_n()
{
  return gam_width_n;
}

vector<vector<Real> > CompatibleResolvedResonanceDataContainer::get_gam_width_rad()
{
  return gam_width_rad;
}

vector<vector<Real> > CompatibleResolvedResonanceDataContainer::get_gam_width_fis()
{
  return gam_width_fis;
}

vector<vector<Real> > CompatibleResolvedResonanceDataContainer::get_ene_reso_variance()
{
  return ene_reso_variance;
}

vector<vector<Real> > CompatibleResolvedResonanceDataContainer::get_gam_width_n_variance()
{
  return gam_width_n_variance;
}

vector<vector<Real> > CompatibleResolvedResonanceDataContainer::get_gam_width_n_rad_cov()
{
  return gam_width_n_rad_cov;
}

vector<vector<Real> > CompatibleResolvedResonanceDataContainer::get_gam_width_rad_variance()
{
  return gam_width_rad_variance;
}

vector<vector<Real> > CompatibleResolvedResonanceDataContainer::get_gam_width_n_rad_fis()
{
  return gam_width_n_rad_fis;
}

vector<vector<Real> > CompatibleResolvedResonanceDataContainer::get_gam_width_rad_fis_cov()
{
  return gam_width_rad_fis_cov;
}

vector<vector<Real> > CompatibleResolvedResonanceDataContainer::get_gam_width_fis_variance()
{
  return gam_width_fis_variance;
}

vector<vector<Real> > CompatibleResolvedResonanceDataContainer::get_gam_width_n_j_cov()
{
  return gam_width_n_j_cov;
}

vector<vector<Real> > CompatibleResolvedResonanceDataContainer::get_gam_width_rad_j_cov()
{
  return gam_width_rad_j_cov;
}

vector<vector<Real> > CompatibleResolvedResonanceDataContainer::get_gam_width_fis_j_cov()
{
  return gam_width_fis_j_cov;
}

vector<vector<Real> > CompatibleResolvedResonanceDataContainer::get_j_value_variance()
{
  return j_value_variance;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void CompatibleResolvedResonanceDataContainer::set_scat_radius_uncertainty( Real real_data )
{
  scat_radius_uncertainty = real_data;
}

void CompatibleResolvedResonanceDataContainer::set_l_value( vector<Integer> int_vec )
{
  l_value = int_vec;
  int_vec.clear();
}

void CompatibleResolvedResonanceDataContainer::set_mass_isotope( vector<Real> real_vec )
{
  mass_isotope = real_vec;
  real_vec.clear();
}

void CompatibleResolvedResonanceDataContainer::set_ene_reso( vector<vector<Real> > real_vec )
{
  ene_reso = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void CompatibleResolvedResonanceDataContainer::set_j_value_abs( vector<vector<Real> > real_vec )
{
  j_value_abs = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void CompatibleResolvedResonanceDataContainer::set_gam_width_tot( vector<vector<Real> > real_vec )
{
  gam_width_tot = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void CompatibleResolvedResonanceDataContainer::set_gam_width_n( vector<vector<Real> > real_vec )
{
  gam_width_n = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void CompatibleResolvedResonanceDataContainer::set_gam_width_rad( vector<vector<Real> > real_vec )
{
  gam_width_rad = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void CompatibleResolvedResonanceDataContainer::set_gam_width_fis( vector<vector<Real> > real_vec )
{
  gam_width_fis = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void CompatibleResolvedResonanceDataContainer::set_ene_reso_variance( vector<vector<Real> > real_vec )
{
  ene_reso_variance = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void CompatibleResolvedResonanceDataContainer::set_gam_width_n_variance( vector<vector<Real> > real_vec )
{
  gam_width_n_variance = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void CompatibleResolvedResonanceDataContainer::set_gam_width_n_rad_cov( vector<vector<Real> > real_vec )
{
  gam_width_n_rad_cov = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void CompatibleResolvedResonanceDataContainer::set_gam_width_rad_variance( vector<vector<Real> > real_vec )
{
  gam_width_rad_variance = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void CompatibleResolvedResonanceDataContainer::set_gam_width_n_rad_fis( vector<vector<Real> > real_vec )
{
  gam_width_n_rad_fis = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void CompatibleResolvedResonanceDataContainer::set_gam_width_rad_fis_cov( vector<vector<Real> > real_vec )
{
  gam_width_rad_fis_cov = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void CompatibleResolvedResonanceDataContainer::set_gam_width_fis_variance( vector<vector<Real> > real_vec )
{
  gam_width_fis_variance = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void CompatibleResolvedResonanceDataContainer::set_gam_width_n_j_cov( vector<vector<Real> > real_vec )
{
  gam_width_n_j_cov = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void CompatibleResolvedResonanceDataContainer::set_gam_width_rad_j_cov( vector<vector<Real> > real_vec )
{
  gam_width_rad_j_cov = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void CompatibleResolvedResonanceDataContainer::set_gam_width_fis_j_cov( vector<vector<Real> > real_vec )
{
  gam_width_fis_j_cov = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void CompatibleResolvedResonanceDataContainer::set_j_value_variance( vector<vector<Real> > real_vec )
{
  j_value_variance = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

