#ifndef COVARIANCE_GENERAL_DATA_CONTAINER_H
#define COVARIANCE_GENERAL_DATA_CONTAINER_H

#include "CommonUtils/ErrorManager.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class CovarianceGeneralDataContainer
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

      Integer               mat_no;
      Real                  mat_data;
      Real                  mass;
      vector<Integer>       sensitivity_parameter;
      vector<Integer>       sensitivity_type_mf;
      vector<Integer>       sensitivity_type_mt;
      vector<Integer>       sensitivity_data_no;
      vector<Integer>       mat_parameter;
      vector<Integer>       sub_lib_no;
      vector<Integer>       sub_mat_no;
      vector<Integer>       parameter_no;
      vector<Real>          relative_cov_parameter;
      vector<vector<Real> > relative_cov;

    public:
      //constructor
      CovarianceGeneralDataContainer(void);

      //destructor
      virtual ~CovarianceGeneralDataContainer(void);

      void clear();

      //Getter
      Integer               get_mat_no();
      Real                  get_mat_data();
      Real                  get_mass();
      vector<Integer>       get_sensitivity_parameter();
      vector<Integer>       get_sensitivity_type_mf();
      vector<Integer>       get_sensitivity_type_mt();
      vector<Integer>       get_sensitivity_data_no();
      vector<Integer>       get_mat_parameter();
      vector<Integer>       get_sub_lib_no();
      vector<Integer>       get_sub_mat_no();
      vector<Integer>       get_parameter_no();
      vector<Real>          get_relative_cov_parameter();
      vector<vector<Real> > get_relative_cov();

      //Setter
      void set_mat_no( Integer int_data );
      void set_mat_data( Real real_data );
      void set_mass( Real real_data );
      void set_sensitivity_parameter( vector<Integer> int_vec );
      void set_sensitivity_type_mf( vector<Integer> int_vec );
      void set_sensitivity_type_mt( vector<Integer> int_vec );
      void set_sensitivity_data_no( vector<Integer> int_vec );
      void set_mat_parameter( vector<Integer> int_vec );
      void set_sub_lib_no( vector<Integer> int_vec );
      void set_sub_mat_no( vector<Integer> int_vec );
      void set_parameter_no( vector<Integer> int_vec );
      void set_relative_cov_parameter( vector<Real> real_vec );
      void set_relative_cov( vector<vector<Real> > real_vec );
  };
}

#endif //COVARIANCE_GENERAL_DATA_CONTAINER_H
