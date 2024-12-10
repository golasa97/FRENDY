#ifndef BREIT_WIGNER_COMPACT_COVARIANCE_DATA_CONTAINER_H
#define BREIT_WIGNER_COMPACT_COVARIANCE_DATA_CONTAINER_H

#include "CommonUtils/ErrorManager.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class BreitWignerCompactCovarianceDataContainer
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

      Real                     scat_radius_uncertainty;
      Real                     q_value;
      Integer                  competitive_width_flg;
      vector<Real>             ene_reso;
      vector<Real>             j_value_abs;
      vector<Real>             gam_width_tot;
      vector<Real>             gam_width_n;
      vector<Real>             gam_width_rad;
      vector<Real>             gam_width_fis;
      vector<Real>             ene_reso_uncertainty;
      vector<Real>             gam_width_n_uncertainty;
      vector<Real>             gam_width_rad_uncertainty;
      vector<Real>             gam_width_fis_uncertainty;
      Integer                  cov_matrix_digit_no;
      Integer                  cov_param_no;
      vector<Integer>          cov_matrix_location_i;
      vector<Integer>          cov_matrix_location_j;
      vector<vector<Integer> > cov_matrix_coef;

    public:
      //constructor
      BreitWignerCompactCovarianceDataContainer(void);

      //destructor
      virtual ~BreitWignerCompactCovarianceDataContainer(void);

      void clear();

      //Getter
      Real                     get_scat_radius_uncertainty();
      Real                     get_q_value();
      Integer                  get_competitive_width_flg();
      vector<Real>             get_ene_reso();
      vector<Real>             get_j_value_abs();
      vector<Real>             get_gam_width_tot();
      vector<Real>             get_gam_width_n();
      vector<Real>             get_gam_width_rad();
      vector<Real>             get_gam_width_fis();
      vector<Real>             get_ene_reso_uncertainty();
      vector<Real>             get_gam_width_n_uncertainty();
      vector<Real>             get_gam_width_rad_uncertainty();
      vector<Real>             get_gam_width_fis_uncertainty();
      Integer                  get_cov_matrix_digit_no();
      Integer                  get_cov_param_no();
      vector<Integer>          get_cov_matrix_location_i();
      vector<Integer>          get_cov_matrix_location_j();
      vector<vector<Integer> > get_cov_matrix_coef();

      //Setter
      void set_scat_radius_uncertainty( Real real_data );
      void set_q_value( Real real_data );
      void set_competitive_width_flg( Integer int_data );
      void set_ene_reso( vector<Real> real_vec );
      void set_j_value_abs( vector<Real> real_vec );
      void set_gam_width_tot( vector<Real> real_vec );
      void set_gam_width_n( vector<Real> real_vec );
      void set_gam_width_rad( vector<Real> real_vec );
      void set_gam_width_fis( vector<Real> real_vec );
      void set_ene_reso_uncertainty( vector<Real> real_vec );
      void set_gam_width_n_uncertainty( vector<Real> real_vec );
      void set_gam_width_rad_uncertainty( vector<Real> real_vec );
      void set_gam_width_fis_uncertainty( vector<Real> real_vec );
      void set_cov_matrix_digit_no( Integer int_data );
      void set_cov_param_no( Integer int_data );
      void set_cov_matrix_location_i( vector<Integer> int_vec );
      void set_cov_matrix_location_j( vector<Integer> int_vec );
      void set_cov_matrix_coef( vector<vector<Integer> > int_vec );
  };
}

#endif //BREIT_WIGNER_COMPACT_COVARIANCE_DATA_CONTAINER_H
