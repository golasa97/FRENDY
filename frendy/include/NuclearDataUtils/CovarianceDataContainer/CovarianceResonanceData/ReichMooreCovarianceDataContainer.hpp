#ifndef REICH_MOORE_COVARIANCE_DATA_CONTAINER_H
#define REICH_MOORE_COVARIANCE_DATA_CONTAINER_H

#include "CommonUtils/ErrorManager.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class ReichMooreCovarianceDataContainer
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

      vector<Integer>                reso_parameter_no;
      vector<Real>                   scat_radius_uncertainty;
      vector<vector<Real> >          ene_reso;
      vector<vector<Real> >          j_value_abs;
      vector<vector<Real> >          gam_width_n;
      vector<vector<Real> >          gam_width_rad;
      vector<vector<Real> >          gam_width_fis_a;
      vector<vector<Real> >          gam_width_fis_b;
      vector<vector<vector<Real> > > cov_matrix_data;
      vector<Integer>                reso_parameter_type;
      vector<Integer>                cov_pattern_flg;
      vector<vector<Real> >          cov_table_ene;
      vector<vector<vector<Real> > > cov_table_coef;

    public:
      //constructor
      ReichMooreCovarianceDataContainer(void);

      //destructor
      virtual ~ReichMooreCovarianceDataContainer(void);

      void clear();

      //Getter
      vector<Integer>                get_reso_parameter_no();
      vector<Real>                   get_scat_radius_uncertainty();
      vector<vector<Real> >          get_ene_reso();
      vector<vector<Real> >          get_j_value_abs();
      vector<vector<Real> >          get_gam_width_n();
      vector<vector<Real> >          get_gam_width_rad();
      vector<vector<Real> >          get_gam_width_fis_a();
      vector<vector<Real> >          get_gam_width_fis_b();
      vector<vector<vector<Real> > > get_cov_matrix_data();
      vector<Integer>                get_reso_parameter_type();
      vector<Integer>                get_cov_pattern_flg();
      vector<vector<Real> >          get_cov_table_ene();
      vector<vector<vector<Real> > > get_cov_table_coef();

      //Setter
      void set_reso_parameter_no( vector<Integer> int_vec );
      void set_scat_radius_uncertainty( vector<Real> real_vec );
      void set_ene_reso( vector<vector<Real> > real_vec );
      void set_j_value_abs( vector<vector<Real> > real_vec );
      void set_gam_width_n( vector<vector<Real> > real_vec );
      void set_gam_width_rad( vector<vector<Real> > real_vec );
      void set_gam_width_fis_a( vector<vector<Real> > real_vec );
      void set_gam_width_fis_b( vector<vector<Real> > real_vec );
      void set_cov_matrix_data( vector<vector<vector<Real> > > real_vec );
      void set_reso_parameter_type( vector<Integer> int_vec );
      void set_cov_pattern_flg( vector<Integer> int_vec );
      void set_cov_table_ene( vector<vector<Real> > real_vec );
      void set_cov_table_coef( vector<vector<vector<Real> > > real_vec );
  };
}

#endif //REICH_MOORE_COVARIANCE_DATA_CONTAINER_H
