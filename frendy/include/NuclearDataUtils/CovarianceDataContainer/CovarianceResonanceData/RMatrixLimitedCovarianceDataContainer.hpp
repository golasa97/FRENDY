#ifndef R_MATRIX_LIMITED_COVARIANCE_DATA_CONTAINER_H
#define R_MATRIX_LIMITED_COVARIANCE_DATA_CONTAINER_H

#include "CommonUtils/ErrorManager.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class RMatrixLimitedCovarianceDataContainer
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

      Integer                                 gam_width_flg;
      vector<vector<Real> >                   scat_radius_list_uncertainty;
      vector<Integer>                         j_pi_no;
      vector<vector<vector<Real> > >          ene_reso;
      vector<vector<vector<vector<Real> > > > gam_width;
      vector<vector<vector<Real> > >          cov_matrix_data;
      vector<Integer>                         reso_parameter_type;
      vector<Integer>                         cov_pattern_flg;
      vector<vector<Real> >                   cov_table_ene;
      vector<vector<vector<Real> > >          cov_table_coef;

    public:
      //constructor
      RMatrixLimitedCovarianceDataContainer(void);

      //destructor
      virtual ~RMatrixLimitedCovarianceDataContainer(void);

      void clear();

      //Getter
      Integer                                 get_gam_width_flg();
      vector<vector<Real> >                   get_scat_radius_list_uncertainty();
      vector<Integer>                         get_j_pi_no();
      vector<vector<vector<Real> > >          get_ene_reso();
      vector<vector<vector<vector<Real> > > > get_gam_width();
      vector<vector<vector<Real> > >          get_cov_matrix_data();
      vector<Integer>                         get_reso_parameter_type();
      vector<Integer>                         get_cov_pattern_flg();
      vector<vector<Real> >                   get_cov_table_ene();
      vector<vector<vector<Real> > >          get_cov_table_coef();

      //Setter
      void set_gam_width_flg( Integer int_data );
      void set_scat_radius_list_uncertainty( vector<vector<Real> > real_vec );
      void set_j_pi_no( vector<Integer> int_vec );
      void set_ene_reso( vector<vector<vector<Real> > > real_vec );
      void set_gam_width( vector<vector<vector<vector<Real> > > > real_vec );
      void set_cov_matrix_data( vector<vector<vector<Real> > > real_vec );
      void set_reso_parameter_type( vector<Integer> int_vec );
      void set_cov_pattern_flg( vector<Integer> int_vec );
      void set_cov_table_ene( vector<vector<Real> > real_vec );
      void set_cov_table_coef( vector<vector<vector<Real> > > real_vec );
  };
}

#endif //R_MATRIX_LIMITED_COVARIANCE_DATA_CONTAINER_H
