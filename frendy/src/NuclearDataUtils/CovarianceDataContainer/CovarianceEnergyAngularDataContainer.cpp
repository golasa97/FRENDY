#include "NuclearDataUtils/CovarianceDataContainer/CovarianceEnergyAngularDataContainer.hpp"

using namespace frendy;

//constructor
CovarianceEnergyAngularDataContainer::CovarianceEnergyAngularDataContainer(void)
{
  clear();
}

//destructor
CovarianceEnergyAngularDataContainer::~CovarianceEnergyAngularDataContainer(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void CovarianceEnergyAngularDataContainer::clear()
{
  reaction_type    = unassigned_mt_no;
  angular_repr_flg = 0;

  mat_no_target.clear();
  reaction_type_target.clear();
  clr_obj.clear_vec_array3_int( legendre_coef_index );
  clr_obj.clear_vec_array3_int( legendre_coef_index_target );
  clr_obj.clear_vec_array3_int( ref_frame_flg );
  clr_obj.clear_vec_array4_int( symmetric_flg_angle );
  clr_obj.clear_vec_array4_int( cov_matrix_data_flg_angle );
  clr_obj.clear_vec_array5_real( cov_matrix_ene_angle_k );
  clr_obj.clear_vec_array6_real( cov_matrix_coef_angle_k );
  clr_obj.clear_vec_array5_real( cov_matrix_ene_angle_l );
  clr_obj.clear_vec_array6_real( cov_matrix_coef_angle_l );
  ene_range_low.clear();
  ene_range_high.clear();
  symmetric_flg_ene.clear();
  cov_matrix_data_flg_ene.clear();
  clr_obj.clear_vec_array2_real( cov_matrix_ene_data );
  clr_obj.clear_vec_array3_real( cov_matrix_data );
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Getter
Integer CovarianceEnergyAngularDataContainer::get_reaction_type()
{
  return reaction_type;
}

Integer CovarianceEnergyAngularDataContainer::get_angular_repr_flg()
{
  return angular_repr_flg;
}

vector<Integer> CovarianceEnergyAngularDataContainer::get_mat_no_target()
{
  return mat_no_target;
}

vector<Integer> CovarianceEnergyAngularDataContainer::get_reaction_type_target()
{
  return reaction_type_target;
}

vector<vector<vector<Integer> > > CovarianceEnergyAngularDataContainer::get_legendre_coef_index()
{
  return legendre_coef_index;
}

vector<vector<vector<Integer> > > CovarianceEnergyAngularDataContainer::get_legendre_coef_index_target()
{
  return legendre_coef_index_target;
}

vector<vector<vector<Integer> > > CovarianceEnergyAngularDataContainer::get_ref_frame_flg()
{
  return ref_frame_flg;
}

vector<vector<vector<vector<Integer> > > > CovarianceEnergyAngularDataContainer::get_symmetric_flg_angle()
{
  return symmetric_flg_angle;
}

vector<vector<vector<vector<Integer> > > > CovarianceEnergyAngularDataContainer::get_cov_matrix_data_flg_angle()
{
  return cov_matrix_data_flg_angle;
}

vector<vector<vector<vector<vector<Real> > > > > CovarianceEnergyAngularDataContainer::get_cov_matrix_ene_angle_k()
{
  return cov_matrix_ene_angle_k;
}

vector<vector<vector<vector<vector<vector<Real> > > > > > CovarianceEnergyAngularDataContainer::get_cov_matrix_coef_angle_k()
{
  return cov_matrix_coef_angle_k;
}

vector<vector<vector<vector<vector<Real> > > > > CovarianceEnergyAngularDataContainer::get_cov_matrix_ene_angle_l()
{
  return cov_matrix_ene_angle_l;
}

vector<vector<vector<vector<vector<vector<Real> > > > > > CovarianceEnergyAngularDataContainer::get_cov_matrix_coef_angle_l()
{
  return cov_matrix_coef_angle_l;
}

vector<Real> CovarianceEnergyAngularDataContainer::get_ene_range_low()
{
  return ene_range_low;
}

vector<Real> CovarianceEnergyAngularDataContainer::get_ene_range_high()
{
  return ene_range_high;
}

vector<Integer> CovarianceEnergyAngularDataContainer::get_symmetric_flg_ene()
{
  return symmetric_flg_ene;
}

vector<Integer> CovarianceEnergyAngularDataContainer::get_cov_matrix_data_flg_ene()
{
  return cov_matrix_data_flg_ene;
}

vector<vector<Real> > CovarianceEnergyAngularDataContainer::get_cov_matrix_ene_data()
{
  return cov_matrix_ene_data;
}

vector<vector<vector<Real> > > CovarianceEnergyAngularDataContainer::get_cov_matrix_data()
{
  return cov_matrix_data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void CovarianceEnergyAngularDataContainer::set_reaction_type( Integer int_data )
{
  reaction_type = int_data;
}

void CovarianceEnergyAngularDataContainer::set_angular_repr_flg( Integer int_data )
{
  angular_repr_flg = int_data;
}

void CovarianceEnergyAngularDataContainer::set_mat_no_target( vector<Integer> int_vec )
{
  mat_no_target = int_vec;
  int_vec.clear();
}

void CovarianceEnergyAngularDataContainer::set_reaction_type_target( vector<Integer> int_vec )
{
  reaction_type_target = int_vec;
  int_vec.clear();
}

void CovarianceEnergyAngularDataContainer::set_legendre_coef_index( vector<vector<vector<Integer> > > int_vec )
{
  legendre_coef_index = int_vec;
  clr_obj.clear_vec_array3_int( int_vec );
}

void CovarianceEnergyAngularDataContainer::set_legendre_coef_index_target( vector<vector<vector<Integer> > > int_vec )
{
  legendre_coef_index_target = int_vec;
  clr_obj.clear_vec_array3_int( int_vec );
}

void CovarianceEnergyAngularDataContainer::set_ref_frame_flg( vector<vector<vector<Integer> > > int_vec )
{
  ref_frame_flg = int_vec;
  clr_obj.clear_vec_array3_int( int_vec );
}

void CovarianceEnergyAngularDataContainer::set_symmetric_flg_angle( vector<vector<vector<vector<Integer> > > > int_vec )
{
  symmetric_flg_angle = int_vec;
  clr_obj.clear_vec_array4_int( int_vec );
}

void CovarianceEnergyAngularDataContainer::set_cov_matrix_data_flg_angle( vector<vector<vector<vector<Integer> > > > int_vec )
{
  cov_matrix_data_flg_angle = int_vec;
  clr_obj.clear_vec_array4_int( int_vec );
}

void CovarianceEnergyAngularDataContainer::set_cov_matrix_ene_angle_k( vector<vector<vector<vector<vector<Real> > > > > real_vec )
{
  cov_matrix_ene_angle_k = real_vec;
  clr_obj.clear_vec_array5_real( real_vec );
}

void CovarianceEnergyAngularDataContainer::set_cov_matrix_coef_angle_k( vector<vector<vector<vector<vector<vector<Real> > > > > > real_vec )
{
  cov_matrix_coef_angle_k = real_vec;
  clr_obj.clear_vec_array6_real( real_vec );
}

void CovarianceEnergyAngularDataContainer::set_cov_matrix_ene_angle_l( vector<vector<vector<vector<vector<Real> > > > > real_vec )
{
  cov_matrix_ene_angle_l = real_vec;
  clr_obj.clear_vec_array5_real( real_vec );
}

void CovarianceEnergyAngularDataContainer::set_cov_matrix_coef_angle_l( vector<vector<vector<vector<vector<vector<Real> > > > > > real_vec )
{
  cov_matrix_coef_angle_l = real_vec;
  clr_obj.clear_vec_array6_real( real_vec );
}

void CovarianceEnergyAngularDataContainer::set_ene_range_low( vector<Real> real_vec )
{
  ene_range_low = real_vec;
  real_vec.clear();
}

void CovarianceEnergyAngularDataContainer::set_ene_range_high( vector<Real> real_vec )
{
  ene_range_high = real_vec;
  real_vec.clear();
}

void CovarianceEnergyAngularDataContainer::set_symmetric_flg_ene( vector<Integer> int_vec )
{
  symmetric_flg_ene = int_vec;
  int_vec.clear();
}

void CovarianceEnergyAngularDataContainer::set_cov_matrix_data_flg_ene( vector<Integer> int_vec )
{
  cov_matrix_data_flg_ene = int_vec;
  int_vec.clear();
}

void CovarianceEnergyAngularDataContainer::set_cov_matrix_ene_data( vector<vector<Real> > real_vec )
{
  cov_matrix_ene_data = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void CovarianceEnergyAngularDataContainer::set_cov_matrix_data( vector<vector<vector<Real> > > real_vec )
{
  cov_matrix_data = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

