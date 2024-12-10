#include "NuclearDataUtils/CovarianceDataContainer/CovarianceResonanceData/UnresolvedResonanceCovarianceDataContainer.hpp"

using namespace frendy;

//constructor
UnresolvedResonanceCovarianceDataContainer::UnresolvedResonanceCovarianceDataContainer(void)
{
  clear();
}

//destructor
UnresolvedResonanceCovarianceDataContainer::~UnresolvedResonanceCovarianceDataContainer(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void UnresolvedResonanceCovarianceDataContainer::clear()
{
  reso_parameter_no = 0;

  mass_isotope.clear();
  l_value.clear();
  clr_obj.clear_vec_array2_real( level_spacing );
  clr_obj.clear_vec_array2_real( j_value_abs );
  clr_obj.clear_vec_array2_real( ave_gam_width_n );
  clr_obj.clear_vec_array2_real( ave_gam_width_rad );
  clr_obj.clear_vec_array2_real( ave_gam_width_fis );
  clr_obj.clear_vec_array2_real( ave_gam_width_comp );
  clr_obj.clear_vec_array2_real( relative_cov_value );
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Getter
vector<Real> UnresolvedResonanceCovarianceDataContainer::get_mass_isotope()
{
  return mass_isotope;
}

vector<Integer> UnresolvedResonanceCovarianceDataContainer::get_l_value()
{
  return l_value;
}

vector<vector<Real> > UnresolvedResonanceCovarianceDataContainer::get_level_spacing()
{
  return level_spacing;
}

vector<vector<Real> > UnresolvedResonanceCovarianceDataContainer::get_j_value_abs()
{
  return j_value_abs;
}

vector<vector<Real> > UnresolvedResonanceCovarianceDataContainer::get_ave_gam_width_n()
{
  return ave_gam_width_n;
}

vector<vector<Real> > UnresolvedResonanceCovarianceDataContainer::get_ave_gam_width_rad()
{
  return ave_gam_width_rad;
}

vector<vector<Real> > UnresolvedResonanceCovarianceDataContainer::get_ave_gam_width_fis()
{
  return ave_gam_width_fis;
}

vector<vector<Real> > UnresolvedResonanceCovarianceDataContainer::get_ave_gam_width_comp()
{
  return ave_gam_width_comp;
}

Integer UnresolvedResonanceCovarianceDataContainer::get_reso_parameter_no()
{
  return reso_parameter_no;
}

vector<vector<Real> > UnresolvedResonanceCovarianceDataContainer::get_relative_cov_value()
{
  return relative_cov_value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void UnresolvedResonanceCovarianceDataContainer::set_mass_isotope( vector<Real> real_vec )
{
  mass_isotope = real_vec;
  real_vec.clear();
}

void UnresolvedResonanceCovarianceDataContainer::set_l_value( vector<Integer> int_vec )
{
  l_value = int_vec;
  int_vec.clear();
}

void UnresolvedResonanceCovarianceDataContainer::set_level_spacing( vector<vector<Real> > real_vec )
{
  level_spacing = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void UnresolvedResonanceCovarianceDataContainer::set_j_value_abs( vector<vector<Real> > real_vec )
{
  j_value_abs = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void UnresolvedResonanceCovarianceDataContainer::set_ave_gam_width_n( vector<vector<Real> > real_vec )
{
  ave_gam_width_n = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void UnresolvedResonanceCovarianceDataContainer::set_ave_gam_width_rad( vector<vector<Real> > real_vec )
{
  ave_gam_width_rad = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void UnresolvedResonanceCovarianceDataContainer::set_ave_gam_width_fis( vector<vector<Real> > real_vec )
{
  ave_gam_width_fis = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void UnresolvedResonanceCovarianceDataContainer::set_ave_gam_width_comp( vector<vector<Real> > real_vec )
{
  ave_gam_width_comp = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void UnresolvedResonanceCovarianceDataContainer::set_reso_parameter_no( Integer int_data )
{
  reso_parameter_no = int_data;
}

void UnresolvedResonanceCovarianceDataContainer::set_relative_cov_value( vector<vector<Real> > real_vec )
{
  relative_cov_value = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

