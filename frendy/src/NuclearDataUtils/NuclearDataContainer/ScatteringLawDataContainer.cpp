#include "NuclearDataUtils/NuclearDataContainer/ScatteringLawDataContainer.hpp"

using namespace frendy;

//constructor
ScatteringLawDataContainer::ScatteringLawDataContainer(void)
{
  clear();
}

//destructor
ScatteringLawDataContainer::~ScatteringLawDataContainer(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ScatteringLawDataContainer::clear()
{
  elastic_scat_flg           = 0;
  elastic_temp_ori           = 0.0;
  elastic_bound_xs           = 0.0;
  inelastic_temp_flg         = 0;
  inelastic_symmetric_flg    = 0;
  inelastic_stored_form_flg  = 0;
  non_principal_scat_type_no = 0;

  elastic_temp_target.clear();
  elastic_temp_int.clear();
  elastic_scat_law_int_data.clear();
  elastic_scat_law_range_data.clear();
  elastic_scat_law_ene_data.clear();
  elastic_scat_law_data_ori.clear();
  clr_obj.clear_vec_array2_real( elastic_scat_law_data_target );
  elastic_debye_waller_int_data.clear();
  elastic_debye_waller_range_data.clear();
  elastic_debye_waller_temp_data.clear();
  elastic_debye_waller_data.clear();
  inelastic_scat_law_coef.clear();
  clr_obj.clear_vec_array2_int( inelastic_temp_int );
  inelastic_beta_int_data.clear();
  inelastic_beta_range_data.clear();
  inelastic_temp_ori.clear();
  clr_obj.clear_vec_array2_real( inelastic_temp_target );
  inelastic_beta_data.clear();
  clr_obj.clear_vec_array2_int( inelastic_scat_law_int_data );
  clr_obj.clear_vec_array2_int( inelastic_scat_law_range_data );
  clr_obj.clear_vec_array2_real( inelastic_scat_law_alpha_data );
  clr_obj.clear_vec_array2_real( inelastic_scat_law_data_ori );
  clr_obj.clear_vec_array3_real( inelastic_scat_law_data_target );
  clr_obj.clear_vec_array2_int( inelastic_temp_eff_int_data );
  clr_obj.clear_vec_array2_int( inelastic_temp_eff_range_data );
  clr_obj.clear_vec_array2_real( inelastic_temp_eff_temp_data );
  clr_obj.clear_vec_array2_real( inelastic_temp_eff_data );
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Getter
Integer ScatteringLawDataContainer::get_elastic_scat_flg()
{
  return elastic_scat_flg;
}

Real ScatteringLawDataContainer::get_elastic_temp_ori()
{
  return elastic_temp_ori;
}

vector<Real> ScatteringLawDataContainer::get_elastic_temp_target()
{
  return elastic_temp_target;
}

vector<Integer> ScatteringLawDataContainer::get_elastic_temp_int()
{
  return elastic_temp_int;
}

vector<Integer> ScatteringLawDataContainer::get_elastic_scat_law_int_data()
{
  return elastic_scat_law_int_data;
}

vector<Integer> ScatteringLawDataContainer::get_elastic_scat_law_range_data()
{
  return elastic_scat_law_range_data;
}

vector<Real> ScatteringLawDataContainer::get_elastic_scat_law_ene_data()
{
  return elastic_scat_law_ene_data;
}

vector<Real> ScatteringLawDataContainer::get_elastic_scat_law_data_ori()
{
  return elastic_scat_law_data_ori;
}

vector<vector<Real> > ScatteringLawDataContainer::get_elastic_scat_law_data_target()
{
  return elastic_scat_law_data_target;
}

Real ScatteringLawDataContainer::get_elastic_bound_xs()
{
  return elastic_bound_xs;
}

vector<Integer> ScatteringLawDataContainer::get_elastic_debye_waller_int_data()
{
  return elastic_debye_waller_int_data;
}

vector<Integer> ScatteringLawDataContainer::get_elastic_debye_waller_range_data()
{
  return elastic_debye_waller_range_data;
}

vector<Real> ScatteringLawDataContainer::get_elastic_debye_waller_temp_data()
{
  return elastic_debye_waller_temp_data;
}

vector<Real> ScatteringLawDataContainer::get_elastic_debye_waller_data()
{
  return elastic_debye_waller_data;
}

Integer ScatteringLawDataContainer::get_inelastic_temp_flg()
{
  return inelastic_temp_flg;
}

Integer ScatteringLawDataContainer::get_inelastic_symmetric_flg()
{
  return inelastic_symmetric_flg;
}

Integer ScatteringLawDataContainer::get_inelastic_stored_form_flg()
{
  return inelastic_stored_form_flg;
}

Integer ScatteringLawDataContainer::get_non_principal_scat_type_no()
{
  return non_principal_scat_type_no;
}

vector<Real> ScatteringLawDataContainer::get_inelastic_scat_law_coef()
{
  return inelastic_scat_law_coef;
}

vector<vector<Integer> > ScatteringLawDataContainer::get_inelastic_temp_int()
{
  return inelastic_temp_int;
}

vector<Integer> ScatteringLawDataContainer::get_inelastic_beta_int_data()
{
  return inelastic_beta_int_data;
}

vector<Integer> ScatteringLawDataContainer::get_inelastic_beta_range_data()
{
  return inelastic_beta_range_data;
}

vector<Real> ScatteringLawDataContainer::get_inelastic_temp_ori()
{
  return inelastic_temp_ori;
}

vector<vector<Real> > ScatteringLawDataContainer::get_inelastic_temp_target()
{
  return inelastic_temp_target;
}

vector<Real> ScatteringLawDataContainer::get_inelastic_beta_data()
{
  return inelastic_beta_data;
}

vector<vector<Integer> > ScatteringLawDataContainer::get_inelastic_scat_law_int_data()
{
  return inelastic_scat_law_int_data;
}

vector<vector<Integer> > ScatteringLawDataContainer::get_inelastic_scat_law_range_data()
{
  return inelastic_scat_law_range_data;
}

vector<vector<Real> > ScatteringLawDataContainer::get_inelastic_scat_law_alpha_data()
{
  return inelastic_scat_law_alpha_data;
}

vector<vector<Real> > ScatteringLawDataContainer::get_inelastic_scat_law_data_ori()
{
  return inelastic_scat_law_data_ori;
}

vector<vector<vector<Real> > > ScatteringLawDataContainer::get_inelastic_scat_law_data_target()
{
  return inelastic_scat_law_data_target;
}

vector<vector<Integer> > ScatteringLawDataContainer::get_inelastic_temp_eff_int_data()
{
  return inelastic_temp_eff_int_data;
}

vector<vector<Integer> > ScatteringLawDataContainer::get_inelastic_temp_eff_range_data()
{
  return inelastic_temp_eff_range_data;
}

vector<vector<Real> > ScatteringLawDataContainer::get_inelastic_temp_eff_temp_data()
{
  return inelastic_temp_eff_temp_data;
}

vector<vector<Real> > ScatteringLawDataContainer::get_inelastic_temp_eff_data()
{
  return inelastic_temp_eff_data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void ScatteringLawDataContainer::set_elastic_scat_flg( Integer int_data )
{
  elastic_scat_flg = int_data;
}

void ScatteringLawDataContainer::set_elastic_temp_ori( Real real_data )
{
  elastic_temp_ori = real_data;
}

void ScatteringLawDataContainer::set_elastic_temp_target( vector<Real> real_vec )
{
  elastic_temp_target = real_vec;
  real_vec.clear();
}

void ScatteringLawDataContainer::set_elastic_temp_int( vector<Integer> int_vec )
{
  elastic_temp_int = int_vec;
  int_vec.clear();
}

void ScatteringLawDataContainer::set_elastic_scat_law_int_data( vector<Integer> int_vec )
{
  elastic_scat_law_int_data = int_vec;
  int_vec.clear();
}

void ScatteringLawDataContainer::set_elastic_scat_law_range_data( vector<Integer> int_vec )
{
  elastic_scat_law_range_data = int_vec;
  int_vec.clear();
}

void ScatteringLawDataContainer::set_elastic_scat_law_ene_data( vector<Real> real_vec )
{
  elastic_scat_law_ene_data = real_vec;
  real_vec.clear();
}

void ScatteringLawDataContainer::set_elastic_scat_law_data_ori( vector<Real> real_vec )
{
  elastic_scat_law_data_ori = real_vec;
  real_vec.clear();
}

void ScatteringLawDataContainer::set_elastic_scat_law_data_target( vector<vector<Real> > real_vec )
{
  elastic_scat_law_data_target = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void ScatteringLawDataContainer::set_elastic_bound_xs( Real real_data )
{
  elastic_bound_xs = real_data;
}

void ScatteringLawDataContainer::set_elastic_debye_waller_int_data( vector<Integer> int_vec )
{
  elastic_debye_waller_int_data = int_vec;
  int_vec.clear();
}

void ScatteringLawDataContainer::set_elastic_debye_waller_range_data( vector<Integer> int_vec )
{
  elastic_debye_waller_range_data = int_vec;
  int_vec.clear();
}

void ScatteringLawDataContainer::set_elastic_debye_waller_temp_data( vector<Real> real_vec )
{
  elastic_debye_waller_temp_data = real_vec;
  real_vec.clear();
}

void ScatteringLawDataContainer::set_elastic_debye_waller_data( vector<Real> real_vec )
{
  elastic_debye_waller_data = real_vec;
  real_vec.clear();
}

void ScatteringLawDataContainer::set_inelastic_temp_flg( Integer int_data )
{
  inelastic_temp_flg = int_data;
}

void ScatteringLawDataContainer::set_inelastic_symmetric_flg( Integer int_data )
{
  inelastic_symmetric_flg = int_data;
}

void ScatteringLawDataContainer::set_inelastic_stored_form_flg( Integer int_data )
{
  inelastic_stored_form_flg = int_data;
}

void ScatteringLawDataContainer::set_non_principal_scat_type_no( Integer int_data )
{
  non_principal_scat_type_no = int_data;
}

void ScatteringLawDataContainer::set_inelastic_scat_law_coef( vector<Real> real_vec )
{
  inelastic_scat_law_coef = real_vec;
  real_vec.clear();
}

void ScatteringLawDataContainer::set_inelastic_temp_int( vector<vector<Integer> > int_vec )
{
  inelastic_temp_int = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void ScatteringLawDataContainer::set_inelastic_beta_int_data( vector<Integer> int_vec )
{
  inelastic_beta_int_data = int_vec;
  int_vec.clear();
}

void ScatteringLawDataContainer::set_inelastic_beta_range_data( vector<Integer> int_vec )
{
  inelastic_beta_range_data = int_vec;
  int_vec.clear();
}

void ScatteringLawDataContainer::set_inelastic_temp_ori( vector<Real> real_vec )
{
  inelastic_temp_ori = real_vec;
  real_vec.clear();
}

void ScatteringLawDataContainer::set_inelastic_temp_target( vector<vector<Real> > real_vec )
{
  inelastic_temp_target = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void ScatteringLawDataContainer::set_inelastic_beta_data( vector<Real> real_vec )
{
  inelastic_beta_data = real_vec;
  real_vec.clear();
}

void ScatteringLawDataContainer::set_inelastic_scat_law_int_data( vector<vector<Integer> > int_vec )
{
  inelastic_scat_law_int_data = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void ScatteringLawDataContainer::set_inelastic_scat_law_range_data( vector<vector<Integer> > int_vec )
{
  inelastic_scat_law_range_data = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void ScatteringLawDataContainer::set_inelastic_scat_law_alpha_data( vector<vector<Real> > real_vec )
{
  inelastic_scat_law_alpha_data = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void ScatteringLawDataContainer::set_inelastic_scat_law_data_ori( vector<vector<Real> > real_vec )
{
  inelastic_scat_law_data_ori = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void ScatteringLawDataContainer::set_inelastic_scat_law_data_target( vector<vector<vector<Real> > > real_vec )
{
  inelastic_scat_law_data_target = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

void ScatteringLawDataContainer::set_inelastic_temp_eff_int_data( vector<vector<Integer> > int_vec )
{
  inelastic_temp_eff_int_data = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void ScatteringLawDataContainer::set_inelastic_temp_eff_range_data( vector<vector<Integer> > int_vec )
{
  inelastic_temp_eff_range_data = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void ScatteringLawDataContainer::set_inelastic_temp_eff_temp_data( vector<vector<Real> > real_vec )
{
  inelastic_temp_eff_temp_data = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void ScatteringLawDataContainer::set_inelastic_temp_eff_data( vector<vector<Real> > real_vec )
{
  inelastic_temp_eff_data = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

