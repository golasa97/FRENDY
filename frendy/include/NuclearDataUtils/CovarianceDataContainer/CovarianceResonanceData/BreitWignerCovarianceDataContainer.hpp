#ifndef BREIT_WIGNER_COVARIANCE_DATA_CONTAINER_H
#define BREIT_WIGNER_COVARIANCE_DATA_CONTAINER_H

#include "CommonUtils/ErrorManager.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class BreitWignerCovarianceDataContainer
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

      Real                           scat_radius_uncertainty;
      vector<Integer>                reso_parameter_no;
      vector<vector<Real> >          ene_reso;
      vector<vector<Real> >          j_value_abs;
      vector<vector<Real> >          gam_width_tot;
      vector<vector<Real> >          gam_width_n;
      vector<vector<Real> >          gam_width_rad;
      vector<vector<Real> >          gam_width_fis;
      vector<vector<vector<Real> > > cov_matrix_data;
      vector<Integer>                reso_parameter_type;
      vector<Integer>                cov_pattern_flg;
      vector<vector<Real> >          cov_table_ene;
      vector<vector<vector<Real> > > cov_table_coef;

    public:
      //constructor
      BreitWignerCovarianceDataContainer(void);

      //destructor
      virtual ~BreitWignerCovarianceDataContainer(void);

      void clear();

      //Getter
      Real                           get_scat_radius_uncertainty();
      vector<Integer>                get_reso_parameter_no();
      vector<vector<Real> >          get_ene_reso();
      vector<vector<Real> >          get_j_value_abs();
      vector<vector<Real> >          get_gam_width_tot();
      vector<vector<Real> >          get_gam_width_n();
      vector<vector<Real> >          get_gam_width_rad();
      vector<vector<Real> >          get_gam_width_fis();
      vector<vector<vector<Real> > > get_cov_matrix_data();
      vector<Integer>                get_reso_parameter_type();
      vector<Integer>                get_cov_pattern_flg();
      vector<vector<Real> >          get_cov_table_ene();
      vector<vector<vector<Real> > > get_cov_table_coef();

      //Setter
      void set_scat_radius_uncertainty( Real real_data );
      void set_reso_parameter_no( vector<Integer> int_vec );
      void set_ene_reso( vector<vector<Real> > real_vec );
      void set_j_value_abs( vector<vector<Real> > real_vec );
      void set_gam_width_tot( vector<vector<Real> > real_vec );
      void set_gam_width_n( vector<vector<Real> > real_vec );
      void set_gam_width_rad( vector<vector<Real> > real_vec );
      void set_gam_width_fis( vector<vector<Real> > real_vec );
      void set_cov_matrix_data( vector<vector<vector<Real> > > real_vec );
      void set_reso_parameter_type( vector<Integer> int_vec );
      void set_cov_pattern_flg( vector<Integer> int_vec );
      void set_cov_table_ene( vector<vector<Real> > real_vec );
      void set_cov_table_coef( vector<vector<vector<Real> > > real_vec );
  };
}

#endif //BREIT_WIGNER_COVARIANCE_DATA_CONTAINER_H
