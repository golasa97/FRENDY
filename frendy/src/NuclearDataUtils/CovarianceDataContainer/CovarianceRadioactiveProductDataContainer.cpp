#include "NuclearDataUtils/CovarianceDataContainer/CovarianceRadioactiveProductDataContainer.hpp"

using namespace frendy;

//constructor
CovarianceRadioactiveProductDataContainer::CovarianceRadioactiveProductDataContainer(void)
{
  clear();
}

//destructor
CovarianceRadioactiveProductDataContainer::~CovarianceRadioactiveProductDataContainer(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void CovarianceRadioactiveProductDataContainer::clear()
{
  reaction_type   = unassigned_mt_no;
  state_no_target = 0;

  q_value_mass.clear();
  q_value.clear();
  mat_data_product.clear();
  state_no_product.clear();
  clr_obj.clear_vec_array2_real( target_second_file_no );
  clr_obj.clear_vec_array2_real( target_second_excited_state );
  clr_obj.clear_vec_array2_int( target_second_mat_no );
  clr_obj.clear_vec_array2_int( target_second_reaction_type );
  clr_obj.clear_vec_array3_int( cov_matrix_flg );
  clr_obj.clear_vec_array3_real( xs_ene_range_low );
  clr_obj.clear_vec_array3_real( xs_ene_range_high );
  clr_obj.clear_vec_array4_real( xs_contribute_coef );
  clr_obj.clear_vec_array4_real( xs_contribute_reaction_type );
  clr_obj.clear_vec_array3_int( relevant_mat_no );
  clr_obj.clear_vec_array3_int( relevant_reaction_type );
  clr_obj.clear_vec_array3_real( relevant_file_no );
  clr_obj.clear_vec_array3_real( relevant_level_no );
  clr_obj.clear_vec_array4_real( relevant_ene_data );
  clr_obj.clear_vec_array4_real( relevant_weight );
  clr_obj.clear_vec_array3_int( cov_matrix_data_flg );
  clr_obj.clear_vec_array3_int( symmetric_flg_angle );
  clr_obj.clear_vec_array4_real( cov_matrix_ene_k );
  clr_obj.clear_vec_array5_real( cov_matrix_coef_k );
  clr_obj.clear_vec_array4_real( cov_matrix_ene_l );
  clr_obj.clear_vec_array5_real( cov_matrix_coef_l );
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Getter
Integer CovarianceRadioactiveProductDataContainer::get_reaction_type()
{
  return reaction_type;
}

Integer CovarianceRadioactiveProductDataContainer::get_state_no_target()
{
  return state_no_target;
}

vector<Real> CovarianceRadioactiveProductDataContainer::get_q_value_mass()
{
  return q_value_mass;
}

vector<Real> CovarianceRadioactiveProductDataContainer::get_q_value()
{
  return q_value;
}

vector<Integer> CovarianceRadioactiveProductDataContainer::get_mat_data_product()
{
  return mat_data_product;
}

vector<Integer> CovarianceRadioactiveProductDataContainer::get_state_no_product()
{
  return state_no_product;
}

vector<vector<Real> > CovarianceRadioactiveProductDataContainer::get_target_second_file_no()
{
  return target_second_file_no;
}

vector<vector<Real> > CovarianceRadioactiveProductDataContainer::get_target_second_excited_state()
{
  return target_second_excited_state;
}

vector<vector<Integer> > CovarianceRadioactiveProductDataContainer::get_target_second_mat_no()
{
  return target_second_mat_no;
}

vector<vector<Integer> > CovarianceRadioactiveProductDataContainer::get_target_second_reaction_type()
{
  return target_second_reaction_type;
}

vector<vector<vector<Integer> > > CovarianceRadioactiveProductDataContainer::get_cov_matrix_flg()
{
  return cov_matrix_flg;
}

vector<vector<vector<Real> > > CovarianceRadioactiveProductDataContainer::get_xs_ene_range_low()
{
  return xs_ene_range_low;
}

vector<vector<vector<Real> > > CovarianceRadioactiveProductDataContainer::get_xs_ene_range_high()
{
  return xs_ene_range_high;
}

vector<vector<vector<vector<Real> > > > CovarianceRadioactiveProductDataContainer::get_xs_contribute_coef()
{
  return xs_contribute_coef;
}

vector<vector<vector<vector<Real> > > > CovarianceRadioactiveProductDataContainer::get_xs_contribute_reaction_type()
{
  return xs_contribute_reaction_type;
}

vector<vector<vector<Integer> > > CovarianceRadioactiveProductDataContainer::get_relevant_mat_no()
{
  return relevant_mat_no;
}

vector<vector<vector<Integer> > > CovarianceRadioactiveProductDataContainer::get_relevant_reaction_type()
{
  return relevant_reaction_type;
}

vector<vector<vector<Real> > > CovarianceRadioactiveProductDataContainer::get_relevant_file_no()
{
  return relevant_file_no;
}

vector<vector<vector<Real> > > CovarianceRadioactiveProductDataContainer::get_relevant_level_no()
{
  return relevant_level_no;
}

vector<vector<vector<vector<Real> > > > CovarianceRadioactiveProductDataContainer::get_relevant_ene_data()
{
  return relevant_ene_data;
}

vector<vector<vector<vector<Real> > > > CovarianceRadioactiveProductDataContainer::get_relevant_weight()
{
  return relevant_weight;
}

vector<vector<vector<Integer> > > CovarianceRadioactiveProductDataContainer::get_cov_matrix_data_flg()
{
  return cov_matrix_data_flg;
}

vector<vector<vector<Integer> > > CovarianceRadioactiveProductDataContainer::get_symmetric_flg_angle()
{
  return symmetric_flg_angle;
}

vector<vector<vector<vector<Real> > > > CovarianceRadioactiveProductDataContainer::get_cov_matrix_ene_k()
{
  return cov_matrix_ene_k;
}

vector<vector<vector<vector<vector<Real> > > > > CovarianceRadioactiveProductDataContainer::get_cov_matrix_coef_k()
{
  return cov_matrix_coef_k;
}

vector<vector<vector<vector<Real> > > > CovarianceRadioactiveProductDataContainer::get_cov_matrix_ene_l()
{
  return cov_matrix_ene_l;
}

vector<vector<vector<vector<vector<Real> > > > > CovarianceRadioactiveProductDataContainer::get_cov_matrix_coef_l()
{
  return cov_matrix_coef_l;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void CovarianceRadioactiveProductDataContainer::set_reaction_type( Integer int_data )
{
  reaction_type = int_data;
}

void CovarianceRadioactiveProductDataContainer::set_state_no_target( Integer int_data )
{
  state_no_target = int_data;
}

void CovarianceRadioactiveProductDataContainer::set_q_value_mass( vector<Real> real_vec )
{
  q_value_mass = real_vec;
  real_vec.clear();
}

void CovarianceRadioactiveProductDataContainer::set_q_value( vector<Real> real_vec )
{
  q_value = real_vec;
  real_vec.clear();
}

void CovarianceRadioactiveProductDataContainer::set_mat_data_product( vector<Integer> int_vec )
{
  mat_data_product = int_vec;
  int_vec.clear();
}

void CovarianceRadioactiveProductDataContainer::set_state_no_product( vector<Integer> int_vec )
{
  state_no_product = int_vec;
  int_vec.clear();
}

void CovarianceRadioactiveProductDataContainer::set_target_second_file_no( vector<vector<Real> > real_vec )
{
  target_second_file_no = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void CovarianceRadioactiveProductDataContainer::set_target_second_excited_state( vector<vector<Real> > real_vec )
{
  target_second_excited_state = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void CovarianceRadioactiveProductDataContainer::set_target_second_mat_no( vector<vector<Integer> > int_vec )
{
  target_second_mat_no = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void CovarianceRadioactiveProductDataContainer::set_target_second_reaction_type( vector<vector<Integer> > int_vec )
{
  target_second_reaction_type = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void CovarianceRadioactiveProductDataContainer::set_cov_matrix_flg( vector<vector<vector<Integer> > > int_vec )
{
  cov_matrix_flg = int_vec;
  clr_obj.clear_vec_array3_int( int_vec );
}

void CovarianceRadioactiveProductDataContainer::set_xs_ene_range_low( vector<vector<vector<Real> > > real_vec )
{
  xs_ene_range_low = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

void CovarianceRadioactiveProductDataContainer::set_xs_ene_range_high( vector<vector<vector<Real> > > real_vec )
{
  xs_ene_range_high = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

void CovarianceRadioactiveProductDataContainer::set_xs_contribute_coef( vector<vector<vector<vector<Real> > > > real_vec )
{
  xs_contribute_coef = real_vec;
  clr_obj.clear_vec_array4_real( real_vec );
}

void CovarianceRadioactiveProductDataContainer::set_xs_contribute_reaction_type( vector<vector<vector<vector<Real> > > > real_vec )
{
  xs_contribute_reaction_type = real_vec;
  clr_obj.clear_vec_array4_real( real_vec );
}

void CovarianceRadioactiveProductDataContainer::set_relevant_mat_no( vector<vector<vector<Integer> > > int_vec )
{
  relevant_mat_no = int_vec;
  clr_obj.clear_vec_array3_int( int_vec );
}

void CovarianceRadioactiveProductDataContainer::set_relevant_reaction_type( vector<vector<vector<Integer> > > int_vec )
{
  relevant_reaction_type = int_vec;
  clr_obj.clear_vec_array3_int( int_vec );
}

void CovarianceRadioactiveProductDataContainer::set_relevant_file_no( vector<vector<vector<Real> > > real_vec )
{
  relevant_file_no = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

void CovarianceRadioactiveProductDataContainer::set_relevant_level_no( vector<vector<vector<Real> > > real_vec )
{
  relevant_level_no = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

void CovarianceRadioactiveProductDataContainer::set_relevant_ene_data( vector<vector<vector<vector<Real> > > > real_vec )
{
  relevant_ene_data = real_vec;
  clr_obj.clear_vec_array4_real( real_vec );
}

void CovarianceRadioactiveProductDataContainer::set_relevant_weight( vector<vector<vector<vector<Real> > > > real_vec )
{
  relevant_weight = real_vec;
  clr_obj.clear_vec_array4_real( real_vec );
}

void CovarianceRadioactiveProductDataContainer::set_cov_matrix_data_flg( vector<vector<vector<Integer> > > int_vec )
{
  cov_matrix_data_flg = int_vec;
  clr_obj.clear_vec_array3_int( int_vec );
}

void CovarianceRadioactiveProductDataContainer::set_symmetric_flg_angle( vector<vector<vector<Integer> > > int_vec )
{
  symmetric_flg_angle = int_vec;
  clr_obj.clear_vec_array3_int( int_vec );
}

void CovarianceRadioactiveProductDataContainer::set_cov_matrix_ene_k( vector<vector<vector<vector<Real> > > > real_vec )
{
  cov_matrix_ene_k = real_vec;
  clr_obj.clear_vec_array4_real( real_vec );
}

void CovarianceRadioactiveProductDataContainer::set_cov_matrix_coef_k( vector<vector<vector<vector<vector<Real> > > > > real_vec )
{
  cov_matrix_coef_k = real_vec;
  clr_obj.clear_vec_array5_real( real_vec );
}

void CovarianceRadioactiveProductDataContainer::set_cov_matrix_ene_l( vector<vector<vector<vector<Real> > > > real_vec )
{
  cov_matrix_ene_l = real_vec;
  clr_obj.clear_vec_array4_real( real_vec );
}

void CovarianceRadioactiveProductDataContainer::set_cov_matrix_coef_l( vector<vector<vector<vector<vector<Real> > > > > real_vec )
{
  cov_matrix_coef_l = real_vec;
  clr_obj.clear_vec_array5_real( real_vec );
}

