#include "NuclearDataUtils/CovarianceDataContainer/CovarianceCrossSectionDataContainer.hpp"

using namespace frendy;

//constructor
CovarianceCrossSectionDataContainer::CovarianceCrossSectionDataContainer(void)
{
  clear();
}

//destructor
CovarianceCrossSectionDataContainer::~CovarianceCrossSectionDataContainer(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void CovarianceCrossSectionDataContainer::clear()
{
  reaction_type        = unassigned_mt_no;
  reaction_type_target = 0;

  target_second_file_no.clear();
  target_second_excited_state.clear();
  target_second_mat_no.clear();
  target_second_reaction_type.clear();
  clr_obj.clear_vec_array2_int( cov_matrix_flg );
  clr_obj.clear_vec_array2_real( xs_ene_range_low );
  clr_obj.clear_vec_array2_real( xs_ene_range_high );
  clr_obj.clear_vec_array3_real( xs_contribute_coef );
  clr_obj.clear_vec_array3_real( xs_contribute_reaction_type );
  clr_obj.clear_vec_array2_int( relevant_mat_no );
  clr_obj.clear_vec_array2_int( relevant_reaction_type );
  clr_obj.clear_vec_array2_real( relevant_file_no );
  clr_obj.clear_vec_array2_real( relevant_level_no );
  clr_obj.clear_vec_array3_real( relevant_ene_data );
  clr_obj.clear_vec_array3_real( relevant_weight );
  clr_obj.clear_vec_array2_int( cov_matrix_data_flg );
  clr_obj.clear_vec_array2_int( symmetric_coef_flg );
  clr_obj.clear_vec_array3_real( cov_matrix_ene_k );
  clr_obj.clear_vec_array4_real( cov_matrix_coef_k );
  clr_obj.clear_vec_array3_real( cov_matrix_ene_l );
  clr_obj.clear_vec_array4_real( cov_matrix_coef_l );
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Getter
Integer CovarianceCrossSectionDataContainer::get_reaction_type()
{
  return reaction_type;
}

Integer CovarianceCrossSectionDataContainer::get_reaction_type_target()
{
  return reaction_type_target;
}

vector<Real> CovarianceCrossSectionDataContainer::get_target_second_file_no()
{
  return target_second_file_no;
}

vector<Real> CovarianceCrossSectionDataContainer::get_target_second_excited_state()
{
  return target_second_excited_state;
}

vector<Integer> CovarianceCrossSectionDataContainer::get_target_second_mat_no()
{
  return target_second_mat_no;
}

vector<Integer> CovarianceCrossSectionDataContainer::get_target_second_reaction_type()
{
  return target_second_reaction_type;
}

vector<vector<Integer> > CovarianceCrossSectionDataContainer::get_cov_matrix_flg()
{
  return cov_matrix_flg;
}

vector<vector<Real> > CovarianceCrossSectionDataContainer::get_xs_ene_range_low()
{
  return xs_ene_range_low;
}

vector<vector<Real> > CovarianceCrossSectionDataContainer::get_xs_ene_range_high()
{
  return xs_ene_range_high;
}

vector<vector<vector<Real> > > CovarianceCrossSectionDataContainer::get_xs_contribute_coef()
{
  return xs_contribute_coef;
}

vector<vector<vector<Real> > > CovarianceCrossSectionDataContainer::get_xs_contribute_reaction_type()
{
  return xs_contribute_reaction_type;
}

vector<vector<Integer> > CovarianceCrossSectionDataContainer::get_relevant_mat_no()
{
  return relevant_mat_no;
}

vector<vector<Integer> > CovarianceCrossSectionDataContainer::get_relevant_reaction_type()
{
  return relevant_reaction_type;
}

vector<vector<Real> > CovarianceCrossSectionDataContainer::get_relevant_file_no()
{
  return relevant_file_no;
}

vector<vector<Real> > CovarianceCrossSectionDataContainer::get_relevant_level_no()
{
  return relevant_level_no;
}

vector<vector<vector<Real> > > CovarianceCrossSectionDataContainer::get_relevant_ene_data()
{
  return relevant_ene_data;
}

vector<vector<vector<Real> > > CovarianceCrossSectionDataContainer::get_relevant_weight()
{
  return relevant_weight;
}

vector<vector<Integer> > CovarianceCrossSectionDataContainer::get_cov_matrix_data_flg()
{
  return cov_matrix_data_flg;
}

vector<vector<Integer> > CovarianceCrossSectionDataContainer::get_symmetric_coef_flg()
{
  return symmetric_coef_flg;
}

vector<vector<vector<Real> > > CovarianceCrossSectionDataContainer::get_cov_matrix_ene_k()
{
  return cov_matrix_ene_k;
}

vector<vector<vector<vector<Real> > > > CovarianceCrossSectionDataContainer::get_cov_matrix_coef_k()
{
  return cov_matrix_coef_k;
}

vector<vector<vector<Real> > > CovarianceCrossSectionDataContainer::get_cov_matrix_ene_l()
{
  return cov_matrix_ene_l;
}

vector<vector<vector<vector<Real> > > > CovarianceCrossSectionDataContainer::get_cov_matrix_coef_l()
{
  return cov_matrix_coef_l;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void CovarianceCrossSectionDataContainer::set_reaction_type( Integer int_data )
{
  reaction_type = int_data;
}

void CovarianceCrossSectionDataContainer::set_reaction_type_target( Integer int_data )
{
  reaction_type_target = int_data;
}

void CovarianceCrossSectionDataContainer::set_target_second_file_no( vector<Real> real_vec )
{
  target_second_file_no = real_vec;
  real_vec.clear();
}

void CovarianceCrossSectionDataContainer::set_target_second_excited_state( vector<Real> real_vec )
{
  target_second_excited_state = real_vec;
  real_vec.clear();
}

void CovarianceCrossSectionDataContainer::set_target_second_mat_no( vector<Integer> int_vec )
{
  target_second_mat_no = int_vec;
  int_vec.clear();
}

void CovarianceCrossSectionDataContainer::set_target_second_reaction_type( vector<Integer> int_vec )
{
  target_second_reaction_type = int_vec;
  int_vec.clear();
}

void CovarianceCrossSectionDataContainer::set_cov_matrix_flg( vector<vector<Integer> > int_vec )
{
  cov_matrix_flg = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void CovarianceCrossSectionDataContainer::set_xs_ene_range_low( vector<vector<Real> > real_vec )
{
  xs_ene_range_low = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void CovarianceCrossSectionDataContainer::set_xs_ene_range_high( vector<vector<Real> > real_vec )
{
  xs_ene_range_high = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void CovarianceCrossSectionDataContainer::set_xs_contribute_coef( vector<vector<vector<Real> > > real_vec )
{
  xs_contribute_coef = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

void CovarianceCrossSectionDataContainer::set_xs_contribute_reaction_type( vector<vector<vector<Real> > > real_vec )
{
  xs_contribute_reaction_type = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

void CovarianceCrossSectionDataContainer::set_relevant_mat_no( vector<vector<Integer> > int_vec )
{
  relevant_mat_no = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void CovarianceCrossSectionDataContainer::set_relevant_reaction_type( vector<vector<Integer> > int_vec )
{
  relevant_reaction_type = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void CovarianceCrossSectionDataContainer::set_relevant_file_no( vector<vector<Real> > real_vec )
{
  relevant_file_no = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void CovarianceCrossSectionDataContainer::set_relevant_level_no( vector<vector<Real> > real_vec )
{
  relevant_level_no = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void CovarianceCrossSectionDataContainer::set_relevant_ene_data( vector<vector<vector<Real> > > real_vec )
{
  relevant_ene_data = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

void CovarianceCrossSectionDataContainer::set_relevant_weight( vector<vector<vector<Real> > > real_vec )
{
  relevant_weight = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

void CovarianceCrossSectionDataContainer::set_cov_matrix_data_flg( vector<vector<Integer> > int_vec )
{
  cov_matrix_data_flg = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void CovarianceCrossSectionDataContainer::set_symmetric_coef_flg( vector<vector<Integer> > int_vec )
{
  symmetric_coef_flg = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void CovarianceCrossSectionDataContainer::set_cov_matrix_ene_k( vector<vector<vector<Real> > > real_vec )
{
  cov_matrix_ene_k = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

void CovarianceCrossSectionDataContainer::set_cov_matrix_coef_k( vector<vector<vector<vector<Real> > > > real_vec )
{
  cov_matrix_coef_k = real_vec;
  clr_obj.clear_vec_array4_real( real_vec );
}

void CovarianceCrossSectionDataContainer::set_cov_matrix_ene_l( vector<vector<vector<Real> > > real_vec )
{
  cov_matrix_ene_l = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

void CovarianceCrossSectionDataContainer::set_cov_matrix_coef_l( vector<vector<vector<vector<Real> > > > real_vec )
{
  cov_matrix_coef_l = real_vec;
  clr_obj.clear_vec_array4_real( real_vec );
}

