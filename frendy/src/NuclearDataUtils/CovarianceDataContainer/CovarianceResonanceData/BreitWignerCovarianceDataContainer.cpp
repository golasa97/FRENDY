#include "NuclearDataUtils/CovarianceDataContainer/CovarianceResonanceData/BreitWignerCovarianceDataContainer.hpp"

using namespace frendy;

//constructor
BreitWignerCovarianceDataContainer::BreitWignerCovarianceDataContainer(void)
{
  clear();
}

//destructor
BreitWignerCovarianceDataContainer::~BreitWignerCovarianceDataContainer(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void BreitWignerCovarianceDataContainer::clear()
{
  scat_radius_uncertainty = 0.0;

  reso_parameter_no.clear();
  clr_obj.clear_vec_array2_real( ene_reso );
  clr_obj.clear_vec_array2_real( j_value_abs );
  clr_obj.clear_vec_array2_real( gam_width_tot );
  clr_obj.clear_vec_array2_real( gam_width_n );
  clr_obj.clear_vec_array2_real( gam_width_rad );
  clr_obj.clear_vec_array2_real( gam_width_fis );
  clr_obj.clear_vec_array3_real( cov_matrix_data );
  reso_parameter_type.clear();
  cov_pattern_flg.clear();
  clr_obj.clear_vec_array2_real( cov_table_ene );
  clr_obj.clear_vec_array3_real( cov_table_coef );
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Getter
Real BreitWignerCovarianceDataContainer::get_scat_radius_uncertainty()
{
  return scat_radius_uncertainty;
}

vector<Integer> BreitWignerCovarianceDataContainer::get_reso_parameter_no()
{
  return reso_parameter_no;
}

vector<vector<Real> > BreitWignerCovarianceDataContainer::get_ene_reso()
{
  return ene_reso;
}

vector<vector<Real> > BreitWignerCovarianceDataContainer::get_j_value_abs()
{
  return j_value_abs;
}

vector<vector<Real> > BreitWignerCovarianceDataContainer::get_gam_width_tot()
{
  return gam_width_tot;
}

vector<vector<Real> > BreitWignerCovarianceDataContainer::get_gam_width_n()
{
  return gam_width_n;
}

vector<vector<Real> > BreitWignerCovarianceDataContainer::get_gam_width_rad()
{
  return gam_width_rad;
}

vector<vector<Real> > BreitWignerCovarianceDataContainer::get_gam_width_fis()
{
  return gam_width_fis;
}

vector<vector<vector<Real> > > BreitWignerCovarianceDataContainer::get_cov_matrix_data()
{
  return cov_matrix_data;
}

vector<Integer> BreitWignerCovarianceDataContainer::get_reso_parameter_type()
{
  return reso_parameter_type;
}

vector<Integer> BreitWignerCovarianceDataContainer::get_cov_pattern_flg()
{
  return cov_pattern_flg;
}

vector<vector<Real> > BreitWignerCovarianceDataContainer::get_cov_table_ene()
{
  return cov_table_ene;
}

vector<vector<vector<Real> > > BreitWignerCovarianceDataContainer::get_cov_table_coef()
{
  return cov_table_coef;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void BreitWignerCovarianceDataContainer::set_scat_radius_uncertainty( Real real_data )
{
  scat_radius_uncertainty = real_data;
}

void BreitWignerCovarianceDataContainer::set_reso_parameter_no( vector<Integer> int_vec )
{
  reso_parameter_no = int_vec;
  int_vec.clear();
}

void BreitWignerCovarianceDataContainer::set_ene_reso( vector<vector<Real> > real_vec )
{
  ene_reso = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void BreitWignerCovarianceDataContainer::set_j_value_abs( vector<vector<Real> > real_vec )
{
  j_value_abs = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void BreitWignerCovarianceDataContainer::set_gam_width_tot( vector<vector<Real> > real_vec )
{
  gam_width_tot = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void BreitWignerCovarianceDataContainer::set_gam_width_n( vector<vector<Real> > real_vec )
{
  gam_width_n = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void BreitWignerCovarianceDataContainer::set_gam_width_rad( vector<vector<Real> > real_vec )
{
  gam_width_rad = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void BreitWignerCovarianceDataContainer::set_gam_width_fis( vector<vector<Real> > real_vec )
{
  gam_width_fis = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void BreitWignerCovarianceDataContainer::set_cov_matrix_data( vector<vector<vector<Real> > > real_vec )
{
  cov_matrix_data = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

void BreitWignerCovarianceDataContainer::set_reso_parameter_type( vector<Integer> int_vec )
{
  reso_parameter_type = int_vec;
  int_vec.clear();
}

void BreitWignerCovarianceDataContainer::set_cov_pattern_flg( vector<Integer> int_vec )
{
  cov_pattern_flg = int_vec;
  int_vec.clear();
}

void BreitWignerCovarianceDataContainer::set_cov_table_ene( vector<vector<Real> > real_vec )
{
  cov_table_ene = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void BreitWignerCovarianceDataContainer::set_cov_table_coef( vector<vector<vector<Real> > > real_vec )
{
  cov_table_coef = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

