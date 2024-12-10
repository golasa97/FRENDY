#include "NuclearDataUtils/CovarianceDataContainer/CovarianceGeneralDataContainer.hpp"

using namespace frendy;

//constructor
CovarianceGeneralDataContainer::CovarianceGeneralDataContainer(void)
{
  clear();
}

//destructor
CovarianceGeneralDataContainer::~CovarianceGeneralDataContainer(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void CovarianceGeneralDataContainer::clear()
{
  mat_no   = unassigned_mat_no;
  mat_data = 0.0;
  mass     = 0.0;

  sensitivity_parameter.clear();
  sensitivity_type_mf.clear();
  sensitivity_type_mt.clear();
  sensitivity_data_no.clear();
  mat_parameter.clear();
  sub_lib_no.clear();
  sub_mat_no.clear();
  parameter_no.clear();
  relative_cov_parameter.clear();
  clr_obj.clear_vec_array2_real( relative_cov );
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Getter
Integer CovarianceGeneralDataContainer::get_mat_no()
{
  return mat_no;
}

Real CovarianceGeneralDataContainer::get_mat_data()
{
  return mat_data;
}

Real CovarianceGeneralDataContainer::get_mass()
{
  return mass;
}

vector<Integer> CovarianceGeneralDataContainer::get_sensitivity_parameter()
{
  return sensitivity_parameter;
}

vector<Integer> CovarianceGeneralDataContainer::get_sensitivity_type_mf()
{
  return sensitivity_type_mf;
}

vector<Integer> CovarianceGeneralDataContainer::get_sensitivity_type_mt()
{
  return sensitivity_type_mt;
}

vector<Integer> CovarianceGeneralDataContainer::get_sensitivity_data_no()
{
  return sensitivity_data_no;
}

vector<Integer> CovarianceGeneralDataContainer::get_mat_parameter()
{
  return mat_parameter;
}

vector<Integer> CovarianceGeneralDataContainer::get_sub_lib_no()
{
  return sub_lib_no;
}

vector<Integer> CovarianceGeneralDataContainer::get_sub_mat_no()
{
  return sub_mat_no;
}

vector<Integer> CovarianceGeneralDataContainer::get_parameter_no()
{
  return parameter_no;
}

vector<Real> CovarianceGeneralDataContainer::get_relative_cov_parameter()
{
  return relative_cov_parameter;
}

vector<vector<Real> > CovarianceGeneralDataContainer::get_relative_cov()
{
  return relative_cov;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void CovarianceGeneralDataContainer::set_mat_no( Integer real_data )
{
  mat_no = real_data;
}

void CovarianceGeneralDataContainer::set_mat_data( Real real_data )
{
  mat_data = real_data;
}

void CovarianceGeneralDataContainer::set_mass( Real real_data )
{
  mass = real_data;
}

void CovarianceGeneralDataContainer::set_sensitivity_parameter( vector<Integer> int_vec )
{
  sensitivity_parameter = int_vec;
  int_vec.clear();
}

void CovarianceGeneralDataContainer::set_sensitivity_type_mf( vector<Integer> int_vec )
{
  sensitivity_type_mf = int_vec;
  int_vec.clear();
}

void CovarianceGeneralDataContainer::set_sensitivity_type_mt( vector<Integer> int_vec )
{
  sensitivity_type_mt = int_vec;
  int_vec.clear();
}

void CovarianceGeneralDataContainer::set_sensitivity_data_no( vector<Integer> int_vec )
{
  sensitivity_data_no = int_vec;
  int_vec.clear();
}

void CovarianceGeneralDataContainer::set_mat_parameter( vector<Integer> int_vec )
{
  mat_parameter = int_vec;
  int_vec.clear();
}

void CovarianceGeneralDataContainer::set_sub_lib_no( vector<Integer> int_vec )
{
  sub_lib_no = int_vec;
  int_vec.clear();
}

void CovarianceGeneralDataContainer::set_sub_mat_no( vector<Integer> int_vec )
{
  sub_mat_no = int_vec;
  int_vec.clear();
}

void CovarianceGeneralDataContainer::set_parameter_no( vector<Integer> int_vec )
{
  parameter_no = int_vec;
  int_vec.clear();
}

void CovarianceGeneralDataContainer::set_relative_cov_parameter( vector<Real> real_vec )
{
  relative_cov_parameter = real_vec;
  real_vec.clear();
}

void CovarianceGeneralDataContainer::set_relative_cov( vector<vector<Real> > real_vec )
{
  relative_cov = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

