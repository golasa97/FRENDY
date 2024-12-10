#include "NuclearDataUtils/CovarianceDataContainer/CovarianceResonanceData/AdlerAdlerCovarianceDataContainer.hpp"

using namespace frendy;

//constructor
AdlerAdlerCovarianceDataContainer::AdlerAdlerCovarianceDataContainer(void)
{
  clear();
}

//destructor
AdlerAdlerCovarianceDataContainer::~AdlerAdlerCovarianceDataContainer(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void AdlerAdlerCovarianceDataContainer::clear()
{
  scat_radius_uncertainty = 0.0;

  reso_parameter_no.clear();
  clr_obj.clear_vec_array2_real( ene_reso_tot );
  clr_obj.clear_vec_array2_real( ene_reso_fis );
  clr_obj.clear_vec_array2_real( ene_reso_rad );
  clr_obj.clear_vec_array2_real( gam_width_half_tot );
  clr_obj.clear_vec_array2_real( gam_width_half_fis );
  clr_obj.clear_vec_array2_real( gam_width_half_rad );
  clr_obj.clear_vec_array2_real( symmetrical_data_tot );
  clr_obj.clear_vec_array2_real( non_symmetrical_data_tot );
  clr_obj.clear_vec_array2_real( symmetrical_data_fis );
  clr_obj.clear_vec_array2_real( non_symmetrical_data_fis );
  clr_obj.clear_vec_array2_real( symmetrical_data_rad );
  clr_obj.clear_vec_array2_real( non_symmetrical_data_rad );
  clr_obj.clear_vec_array3_real( cov_matrix_data );
  reso_parameter_type.clear();
  cov_pattern_flg.clear();
  clr_obj.clear_vec_array2_real( cov_table_ene );
  clr_obj.clear_vec_array3_real( cov_table_coef );
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Getter
Real AdlerAdlerCovarianceDataContainer::get_scat_radius_uncertainty()
{
  return scat_radius_uncertainty;
}

vector<Integer> AdlerAdlerCovarianceDataContainer::get_reso_parameter_no()
{
  return reso_parameter_no;
}

vector<vector<Real> > AdlerAdlerCovarianceDataContainer::get_ene_reso_tot()
{
  return ene_reso_tot;
}

vector<vector<Real> > AdlerAdlerCovarianceDataContainer::get_ene_reso_fis()
{
  return ene_reso_fis;
}

vector<vector<Real> > AdlerAdlerCovarianceDataContainer::get_ene_reso_rad()
{
  return ene_reso_rad;
}

vector<vector<Real> > AdlerAdlerCovarianceDataContainer::get_gam_width_half_tot()
{
  return gam_width_half_tot;
}

vector<vector<Real> > AdlerAdlerCovarianceDataContainer::get_gam_width_half_fis()
{
  return gam_width_half_fis;
}

vector<vector<Real> > AdlerAdlerCovarianceDataContainer::get_gam_width_half_rad()
{
  return gam_width_half_rad;
}

vector<vector<Real> > AdlerAdlerCovarianceDataContainer::get_symmetrical_data_tot()
{
  return symmetrical_data_tot;
}

vector<vector<Real> > AdlerAdlerCovarianceDataContainer::get_non_symmetrical_data_tot()
{
  return non_symmetrical_data_tot;
}

vector<vector<Real> > AdlerAdlerCovarianceDataContainer::get_symmetrical_data_fis()
{
  return symmetrical_data_fis;
}

vector<vector<Real> > AdlerAdlerCovarianceDataContainer::get_non_symmetrical_data_fis()
{
  return non_symmetrical_data_fis;
}

vector<vector<Real> > AdlerAdlerCovarianceDataContainer::get_symmetrical_data_rad()
{
  return symmetrical_data_rad;
}

vector<vector<Real> > AdlerAdlerCovarianceDataContainer::get_non_symmetrical_data_rad()
{
  return non_symmetrical_data_rad;
}

vector<vector<vector<Real> > > AdlerAdlerCovarianceDataContainer::get_cov_matrix_data()
{
  return cov_matrix_data;
}

vector<Integer> AdlerAdlerCovarianceDataContainer::get_reso_parameter_type()
{
  return reso_parameter_type;
}

vector<Integer> AdlerAdlerCovarianceDataContainer::get_cov_pattern_flg()
{
  return cov_pattern_flg;
}

vector<vector<Real> > AdlerAdlerCovarianceDataContainer::get_cov_table_ene()
{
  return cov_table_ene;
}

vector<vector<vector<Real> > > AdlerAdlerCovarianceDataContainer::get_cov_table_coef()
{
  return cov_table_coef;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void AdlerAdlerCovarianceDataContainer::set_scat_radius_uncertainty( Real real_data )
{
  scat_radius_uncertainty = real_data;
}

void AdlerAdlerCovarianceDataContainer::set_reso_parameter_no( vector<Integer> int_vec )
{
  reso_parameter_no = int_vec;
  int_vec.clear();
}

void AdlerAdlerCovarianceDataContainer::set_ene_reso_tot( vector<vector<Real> > real_vec )
{
  ene_reso_tot = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void AdlerAdlerCovarianceDataContainer::set_ene_reso_fis( vector<vector<Real> > real_vec )
{
  ene_reso_fis = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void AdlerAdlerCovarianceDataContainer::set_ene_reso_rad( vector<vector<Real> > real_vec )
{
  ene_reso_rad = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void AdlerAdlerCovarianceDataContainer::set_gam_width_half_tot( vector<vector<Real> > real_vec )
{
  gam_width_half_tot = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void AdlerAdlerCovarianceDataContainer::set_gam_width_half_fis( vector<vector<Real> > real_vec )
{
  gam_width_half_fis = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void AdlerAdlerCovarianceDataContainer::set_gam_width_half_rad( vector<vector<Real> > real_vec )
{
  gam_width_half_rad = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void AdlerAdlerCovarianceDataContainer::set_symmetrical_data_tot( vector<vector<Real> > real_vec )
{
  symmetrical_data_tot = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void AdlerAdlerCovarianceDataContainer::set_non_symmetrical_data_tot( vector<vector<Real> > real_vec )
{
  non_symmetrical_data_tot = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void AdlerAdlerCovarianceDataContainer::set_symmetrical_data_fis( vector<vector<Real> > real_vec )
{
  symmetrical_data_fis = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void AdlerAdlerCovarianceDataContainer::set_non_symmetrical_data_fis( vector<vector<Real> > real_vec )
{
  non_symmetrical_data_fis = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void AdlerAdlerCovarianceDataContainer::set_symmetrical_data_rad( vector<vector<Real> > real_vec )
{
  symmetrical_data_rad = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void AdlerAdlerCovarianceDataContainer::set_non_symmetrical_data_rad( vector<vector<Real> > real_vec )
{
  non_symmetrical_data_rad = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void AdlerAdlerCovarianceDataContainer::set_cov_matrix_data( vector<vector<vector<Real> > > real_vec )
{
  cov_matrix_data = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

void AdlerAdlerCovarianceDataContainer::set_reso_parameter_type( vector<Integer> int_vec )
{
  reso_parameter_type = int_vec;
  int_vec.clear();
}

void AdlerAdlerCovarianceDataContainer::set_cov_pattern_flg( vector<Integer> int_vec )
{
  cov_pattern_flg = int_vec;
  int_vec.clear();
}

void AdlerAdlerCovarianceDataContainer::set_cov_table_ene( vector<vector<Real> > real_vec )
{
  cov_table_ene = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void AdlerAdlerCovarianceDataContainer::set_cov_table_coef( vector<vector<vector<Real> > > real_vec )
{
  cov_table_coef = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

