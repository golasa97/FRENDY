#include "NuclearDataUtils/NuclearDataContainer/EnergyAngularDataContainer.hpp"

using namespace frendy;

//constructor
EnergyAngularDataContainer::EnergyAngularDataContainer(void)
{
  clear();
}

//destructor
EnergyAngularDataContainer::~EnergyAngularDataContainer(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void EnergyAngularDataContainer::clear()
{
  reaction_type             = unassigned_mt_no;
  angular_repr_flg          = 0;
  isotropic_flg             = 0;
  ref_frame_flg             = 0;
  transformation_matrix_flg = 0;

  transformation_matrix.clear();
  angular_int_data_polynomial.clear();
  angular_range_data_polynomial.clear();
  clr_obj.clear_vec_array2_real( angular_data_polynomial );
  temp_target_polynomial.clear();
  angular_probability_ene_polynomial.clear();
  temp_target_dependence_flg_polynomial.clear();
  angular_int_data_tab.clear();
  angular_range_data_tab.clear();
  clr_obj.clear_vec_array2_int( angular_probability_int_data_tab );
  clr_obj.clear_vec_array2_int( angular_probability_range_data_tab );
  clr_obj.clear_vec_array2_real( angular_probability_cos_tab );
  clr_obj.clear_vec_array2_real( angular_probability_data_tab );
  temp_target_tab.clear();
  angular_probability_ene_tab.clear();
  temp_target_dependence_flg_tab.clear();
  upper_ene_limit.clear();
  clr_obj.clear_vec_array2_int( temp_eff_int_data );
  clr_obj.clear_vec_array2_int( temp_eff_range_data );
  clr_obj.clear_vec_array2_real( temp_eff_ene_data );
  clr_obj.clear_vec_array2_real( temp_eff_data );
  ene_repr_flg.clear();
  clr_obj.clear_vec_array2_int( xs_part_int_data );
  clr_obj.clear_vec_array2_int( xs_part_range_data );
  clr_obj.clear_vec_array2_real( xs_part_ene_data );
  clr_obj.clear_vec_array2_real( xs_part_data );
  clr_obj.clear_vec_array2_real( incident_ene );
  clr_obj.clear_vec_array2_int( ene_int_data );
  clr_obj.clear_vec_array2_int( ene_range_data );
  clr_obj.clear_vec_array3_int( ene_part_int_data );
  clr_obj.clear_vec_array3_int( ene_part_range_data );
  clr_obj.clear_vec_array3_real( ene_part_ene_data );
  clr_obj.clear_vec_array3_real( ene_part_data );
  clr_obj.clear_vec_array2_int( watt_a_int_data );
  clr_obj.clear_vec_array2_int( watt_a_range_data );
  clr_obj.clear_vec_array2_real( watt_a_ene_data );
  clr_obj.clear_vec_array2_real( watt_a_data );
  clr_obj.clear_vec_array2_int( watt_b_int_data );
  clr_obj.clear_vec_array2_int( watt_b_range_data );
  clr_obj.clear_vec_array2_real( watt_b_ene_data );
  clr_obj.clear_vec_array2_real( watt_b_data );
  lower_ene_limit_fis_n.clear();
  upper_ene_limit_fis_n.clear();
  clr_obj.clear_vec_array2_int( temp_max_int_data );
  clr_obj.clear_vec_array2_int( temp_max_range_data );
  clr_obj.clear_vec_array2_real( temp_max_ene_data );
  clr_obj.clear_vec_array2_real( temp_max_data );
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Getter
Integer EnergyAngularDataContainer::get_reaction_type()
{
  return reaction_type;
}

Integer EnergyAngularDataContainer::get_angular_repr_flg()
{
  return angular_repr_flg;
}

Integer EnergyAngularDataContainer::get_isotropic_flg()
{
  return isotropic_flg;
}

Integer EnergyAngularDataContainer::get_ref_frame_flg()
{
  return ref_frame_flg;
}

Integer EnergyAngularDataContainer::get_transformation_matrix_flg()
{
  return transformation_matrix_flg;
}

vector<Real> EnergyAngularDataContainer::get_transformation_matrix()
{
  return transformation_matrix;
}

vector<Integer> EnergyAngularDataContainer::get_angular_int_data_polynomial()
{
  return angular_int_data_polynomial;
}

vector<Integer> EnergyAngularDataContainer::get_angular_range_data_polynomial()
{
  return angular_range_data_polynomial;
}

vector<vector<Real> > EnergyAngularDataContainer::get_angular_data_polynomial()
{
  return angular_data_polynomial;
}

vector<Real> EnergyAngularDataContainer::get_temp_target_polynomial()
{
  return temp_target_polynomial;
}

vector<Real> EnergyAngularDataContainer::get_angular_probability_ene_polynomial()
{
  return angular_probability_ene_polynomial;
}

vector<Integer> EnergyAngularDataContainer::get_temp_target_dependence_flg_polynomial()
{
  return temp_target_dependence_flg_polynomial;
}

vector<Integer> EnergyAngularDataContainer::get_angular_int_data_tab()
{
  return angular_int_data_tab;
}

vector<Integer> EnergyAngularDataContainer::get_angular_range_data_tab()
{
  return angular_range_data_tab;
}

vector<vector<Integer> > EnergyAngularDataContainer::get_angular_probability_int_data_tab()
{
  return angular_probability_int_data_tab;
}

vector<vector<Integer> > EnergyAngularDataContainer::get_angular_probability_range_data_tab()
{
  return angular_probability_range_data_tab;
}

vector<vector<Real> > EnergyAngularDataContainer::get_angular_probability_cos_tab()
{
  return angular_probability_cos_tab;
}

vector<vector<Real> > EnergyAngularDataContainer::get_angular_probability_data_tab()
{
  return angular_probability_data_tab;
}

vector<Real> EnergyAngularDataContainer::get_temp_target_tab()
{
  return temp_target_tab;
}

vector<Real> EnergyAngularDataContainer::get_angular_probability_ene_tab()
{
  return angular_probability_ene_tab;
}

vector<Integer> EnergyAngularDataContainer::get_temp_target_dependence_flg_tab()
{
  return temp_target_dependence_flg_tab;
}

vector<Real> EnergyAngularDataContainer::get_upper_ene_limit()
{
  return upper_ene_limit;
}

vector<vector<Integer> > EnergyAngularDataContainer::get_temp_eff_int_data()
{
  return temp_eff_int_data;
}

vector<vector<Integer> > EnergyAngularDataContainer::get_temp_eff_range_data()
{
  return temp_eff_range_data;
}

vector<vector<Real> > EnergyAngularDataContainer::get_temp_eff_ene_data()
{
  return temp_eff_ene_data;
}

vector<vector<Real> > EnergyAngularDataContainer::get_temp_eff_data()
{
  return temp_eff_data;
}

vector<Integer> EnergyAngularDataContainer::get_ene_repr_flg()
{
  return ene_repr_flg;
}

vector<vector<Integer> > EnergyAngularDataContainer::get_xs_part_int_data()
{
  return xs_part_int_data;
}

vector<vector<Integer> > EnergyAngularDataContainer::get_xs_part_range_data()
{
  return xs_part_range_data;
}

vector<vector<Real> > EnergyAngularDataContainer::get_xs_part_ene_data()
{
  return xs_part_ene_data;
}

vector<vector<Real> > EnergyAngularDataContainer::get_xs_part_data()
{
  return xs_part_data;
}

vector<vector<Real> > EnergyAngularDataContainer::get_incident_ene()
{
  return incident_ene;
}

vector<vector<Integer> > EnergyAngularDataContainer::get_ene_int_data()
{
  return ene_int_data;
}

vector<vector<Integer> > EnergyAngularDataContainer::get_ene_range_data()
{
  return ene_range_data;
}

vector<vector<vector<Integer> > > EnergyAngularDataContainer::get_ene_part_int_data()
{
  return ene_part_int_data;
}

vector<vector<vector<Integer> > > EnergyAngularDataContainer::get_ene_part_range_data()
{
  return ene_part_range_data;
}

vector<vector<vector<Real> > > EnergyAngularDataContainer::get_ene_part_ene_data()
{
  return ene_part_ene_data;
}

vector<vector<vector<Real> > > EnergyAngularDataContainer::get_ene_part_data()
{
  return ene_part_data;
}

vector<vector<Integer> > EnergyAngularDataContainer::get_watt_a_int_data()
{
  return watt_a_int_data;
}

vector<vector<Integer> > EnergyAngularDataContainer::get_watt_a_range_data()
{
  return watt_a_range_data;
}

vector<vector<Real> > EnergyAngularDataContainer::get_watt_a_ene_data()
{
  return watt_a_ene_data;
}

vector<vector<Real> > EnergyAngularDataContainer::get_watt_a_data()
{
  return watt_a_data;
}

vector<vector<Integer> > EnergyAngularDataContainer::get_watt_b_int_data()
{
  return watt_b_int_data;
}

vector<vector<Integer> > EnergyAngularDataContainer::get_watt_b_range_data()
{
  return watt_b_range_data;
}

vector<vector<Real> > EnergyAngularDataContainer::get_watt_b_ene_data()
{
  return watt_b_ene_data;
}

vector<vector<Real> > EnergyAngularDataContainer::get_watt_b_data()
{
  return watt_b_data;
}

vector<Real> EnergyAngularDataContainer::get_lower_ene_limit_fis_n()
{
  return lower_ene_limit_fis_n;
}

vector<Real> EnergyAngularDataContainer::get_upper_ene_limit_fis_n()
{
  return upper_ene_limit_fis_n;
}

vector<vector<Integer> > EnergyAngularDataContainer::get_temp_max_int_data()
{
  return temp_max_int_data;
}

vector<vector<Integer> > EnergyAngularDataContainer::get_temp_max_range_data()
{
  return temp_max_range_data;
}

vector<vector<Real> > EnergyAngularDataContainer::get_temp_max_ene_data()
{
  return temp_max_ene_data;
}

vector<vector<Real> > EnergyAngularDataContainer::get_temp_max_data()
{
  return temp_max_data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void EnergyAngularDataContainer::set_reaction_type( Integer int_data )
{
  reaction_type = int_data;
}

void EnergyAngularDataContainer::set_angular_repr_flg( Integer int_data )
{
  angular_repr_flg = int_data;
}

void EnergyAngularDataContainer::set_isotropic_flg( Integer int_data )
{
  isotropic_flg = int_data;
}

void EnergyAngularDataContainer::set_ref_frame_flg( Integer int_data )
{
  ref_frame_flg = int_data;
}

void EnergyAngularDataContainer::set_transformation_matrix_flg( Integer int_data )
{
  transformation_matrix_flg = int_data;
}

void EnergyAngularDataContainer::set_transformation_matrix( vector<Real> real_vec )
{
  transformation_matrix = real_vec;
  real_vec.clear();
}

void EnergyAngularDataContainer::set_angular_int_data_polynomial( vector<Integer> int_vec )
{
  angular_int_data_polynomial = int_vec;
  int_vec.clear();
}

void EnergyAngularDataContainer::set_angular_range_data_polynomial( vector<Integer> int_vec )
{
  angular_range_data_polynomial = int_vec;
  int_vec.clear();
}

void EnergyAngularDataContainer::set_angular_data_polynomial( vector<vector<Real> > real_vec )
{
  angular_data_polynomial = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void EnergyAngularDataContainer::set_temp_target_polynomial( vector<Real> real_vec )
{
  temp_target_polynomial = real_vec;
  real_vec.clear();
}

void EnergyAngularDataContainer::set_angular_probability_ene_polynomial( vector<Real> real_vec )
{
  angular_probability_ene_polynomial = real_vec;
  real_vec.clear();
}

void EnergyAngularDataContainer::set_temp_target_dependence_flg_polynomial( vector<Integer> int_vec )
{
  temp_target_dependence_flg_polynomial = int_vec;
  int_vec.clear();
}

void EnergyAngularDataContainer::set_angular_int_data_tab( vector<Integer> int_vec )
{
  angular_int_data_tab = int_vec;
  int_vec.clear();
}

void EnergyAngularDataContainer::set_angular_range_data_tab( vector<Integer> int_vec )
{
  angular_range_data_tab = int_vec;
  int_vec.clear();
}

void EnergyAngularDataContainer::set_angular_probability_int_data_tab( vector<vector<Integer> > int_vec )
{
  angular_probability_int_data_tab = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void EnergyAngularDataContainer::set_angular_probability_range_data_tab( vector<vector<Integer> > int_vec )
{
  angular_probability_range_data_tab = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void EnergyAngularDataContainer::set_angular_probability_cos_tab( vector<vector<Real> > real_vec )
{
  angular_probability_cos_tab = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void EnergyAngularDataContainer::set_angular_probability_data_tab( vector<vector<Real> > real_vec )
{
  angular_probability_data_tab = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void EnergyAngularDataContainer::set_temp_target_tab( vector<Real> real_vec )
{
  temp_target_tab = real_vec;
  real_vec.clear();
}

void EnergyAngularDataContainer::set_angular_probability_ene_tab( vector<Real> real_vec )
{
  angular_probability_ene_tab = real_vec;
  real_vec.clear();
}

void EnergyAngularDataContainer::set_temp_target_dependence_flg_tab( vector<Integer> int_vec )
{
  temp_target_dependence_flg_tab = int_vec;
  int_vec.clear();
}

void EnergyAngularDataContainer::set_upper_ene_limit( vector<Real> real_vec )
{
  upper_ene_limit = real_vec;
  real_vec.clear();
}

void EnergyAngularDataContainer::set_temp_eff_int_data( vector<vector<Integer> > int_vec )
{
  temp_eff_int_data = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void EnergyAngularDataContainer::set_temp_eff_range_data( vector<vector<Integer> > int_vec )
{
  temp_eff_range_data = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void EnergyAngularDataContainer::set_temp_eff_ene_data( vector<vector<Real> > real_vec )
{
  temp_eff_ene_data = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void EnergyAngularDataContainer::set_temp_eff_data( vector<vector<Real> > real_vec )
{
  temp_eff_data = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void EnergyAngularDataContainer::set_ene_repr_flg( vector<Integer> int_vec )
{
  ene_repr_flg = int_vec;
  int_vec.clear();
}

void EnergyAngularDataContainer::set_xs_part_int_data( vector<vector<Integer> > int_vec )
{
  xs_part_int_data = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void EnergyAngularDataContainer::set_xs_part_range_data( vector<vector<Integer> > int_vec )
{
  xs_part_range_data = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void EnergyAngularDataContainer::set_xs_part_ene_data( vector<vector<Real> > real_vec )
{
  xs_part_ene_data = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void EnergyAngularDataContainer::set_xs_part_data( vector<vector<Real> > real_vec )
{
  xs_part_data = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void EnergyAngularDataContainer::set_incident_ene( vector<vector<Real> > real_vec )
{
  incident_ene = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void EnergyAngularDataContainer::set_ene_int_data( vector<vector<Integer> > int_vec )
{
  ene_int_data = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void EnergyAngularDataContainer::set_ene_range_data( vector<vector<Integer> > int_vec )
{
  ene_range_data = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void EnergyAngularDataContainer::set_ene_part_int_data( vector<vector<vector<Integer> > > int_vec )
{
  ene_part_int_data = int_vec;
  clr_obj.clear_vec_array3_int( int_vec );
}

void EnergyAngularDataContainer::set_ene_part_range_data( vector<vector<vector<Integer> > > int_vec )
{
  ene_part_range_data = int_vec;
  clr_obj.clear_vec_array3_int( int_vec );
}

void EnergyAngularDataContainer::set_ene_part_ene_data( vector<vector<vector<Real> > > real_vec )
{
  ene_part_ene_data = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

void EnergyAngularDataContainer::set_ene_part_data( vector<vector<vector<Real> > > real_vec )
{
  ene_part_data = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

void EnergyAngularDataContainer::set_watt_a_int_data( vector<vector<Integer> > int_vec )
{
  watt_a_int_data = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void EnergyAngularDataContainer::set_watt_a_range_data( vector<vector<Integer> > int_vec )
{
  watt_a_range_data = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void EnergyAngularDataContainer::set_watt_a_ene_data( vector<vector<Real> > real_vec )
{
  watt_a_ene_data = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void EnergyAngularDataContainer::set_watt_a_data( vector<vector<Real> > real_vec )
{
  watt_a_data = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void EnergyAngularDataContainer::set_watt_b_int_data( vector<vector<Integer> > int_vec )
{
  watt_b_int_data = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void EnergyAngularDataContainer::set_watt_b_range_data( vector<vector<Integer> > int_vec )
{
  watt_b_range_data = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void EnergyAngularDataContainer::set_watt_b_ene_data( vector<vector<Real> > real_vec )
{
  watt_b_ene_data = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void EnergyAngularDataContainer::set_watt_b_data( vector<vector<Real> > real_vec )
{
  watt_b_data = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void EnergyAngularDataContainer::set_lower_ene_limit_fis_n( vector<Real> real_vec )
{
  lower_ene_limit_fis_n = real_vec;
  real_vec.clear();
}

void EnergyAngularDataContainer::set_upper_ene_limit_fis_n( vector<Real> real_vec )
{
  upper_ene_limit_fis_n = real_vec;
  real_vec.clear();
}

void EnergyAngularDataContainer::set_temp_max_int_data( vector<vector<Integer> > int_vec )
{
  temp_max_int_data = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void EnergyAngularDataContainer::set_temp_max_range_data( vector<vector<Integer> > int_vec )
{
  temp_max_range_data = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void EnergyAngularDataContainer::set_temp_max_ene_data( vector<vector<Real> > real_vec )
{
  temp_max_ene_data = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void EnergyAngularDataContainer::set_temp_max_data( vector<vector<Real> > real_vec )
{
  temp_max_data = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

