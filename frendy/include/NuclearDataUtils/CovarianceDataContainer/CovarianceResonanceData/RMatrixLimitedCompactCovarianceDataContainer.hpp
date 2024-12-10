#ifndef R_MATRIX_LIMITED_COMPACT_COVARIANCE_DATA_CONTAINER_H
#define R_MATRIX_LIMITED_COMPACT_COVARIANCE_DATA_CONTAINER_H

#include "CommonUtils/ErrorManager.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class RMatrixLimitedCompactCovarianceDataContainer
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

      Integer                        gam_width_flg;
      vector<vector<Real> >          scat_radius_list_uncertainty;
      Integer                        j_pi_no;
      vector<Real>                   mass_a;
      vector<Real>                   mass_b;
      vector<Real>                   charge_a;
      vector<Real>                   charge_b;
      vector<Real>                   spin_a;
      vector<Real>                   spin_b;
      vector<Real>                   q_value;
      vector<Real>                   penetrability_calc_flg;
      vector<Real>                   shift_factor_calc_flg;
      vector<Real>                   reaction_type_flg;
      vector<Real>                   parity_a;
      vector<Real>                   parity_b;
      vector<Real>                   j_value_abs;
      vector<Real>                   parity;
      vector<vector<Real> >          particle_pair_no;
      vector<vector<Real> >          l_value;
      vector<vector<Real> >          spin_channel;
      vector<vector<Real> >          boundary_condition;
      vector<vector<Real> >          scat_radius_eff;
      vector<vector<Real> >          scat_radius_true;
      vector<vector<Real> >          ene_reso;
      vector<vector<vector<Real> > > gam_width;
      vector<vector<Real> >          ene_reso_uncertainty;
      vector<vector<vector<Real> > > gam_width_uncertainty;
      Integer                        cov_matrix_digit_no;
      Integer                        cov_param_no;
      vector<Integer>                cov_matrix_location_i;
      vector<Integer>                cov_matrix_location_j;
      vector<vector<Integer> >       cov_matrix_coef;

    public:
      //constructor
      RMatrixLimitedCompactCovarianceDataContainer(void);

      //destructor
      virtual ~RMatrixLimitedCompactCovarianceDataContainer(void);

      void clear();

      //Getter
      Integer                        get_gam_width_flg();
      vector<vector<Real> >          get_scat_radius_list_uncertainty();
      Integer                        get_j_pi_no();
      vector<Real>                   get_mass_a();
      vector<Real>                   get_mass_b();
      vector<Real>                   get_charge_a();
      vector<Real>                   get_charge_b();
      vector<Real>                   get_spin_a();
      vector<Real>                   get_spin_b();
      vector<Real>                   get_q_value();
      vector<Real>                   get_penetrability_calc_flg();
      vector<Real>                   get_shift_factor_calc_flg();
      vector<Real>                   get_reaction_type_flg();
      vector<Real>                   get_parity_a();
      vector<Real>                   get_parity_b();
      vector<Real>                   get_j_value_abs();
      vector<Real>                   get_parity();
      vector<vector<Real> >          get_particle_pair_no();
      vector<vector<Real> >          get_l_value();
      vector<vector<Real> >          get_spin_channel();
      vector<vector<Real> >          get_boundary_condition();
      vector<vector<Real> >          get_scat_radius_eff();
      vector<vector<Real> >          get_scat_radius_true();
      vector<vector<Real> >          get_ene_reso();
      vector<vector<vector<Real> > > get_gam_width();
      vector<vector<Real> >          get_ene_reso_uncertainty();
      vector<vector<vector<Real> > > get_gam_width_uncertainty();
      Integer                        get_cov_matrix_digit_no();
      Integer                        get_cov_param_no();
      vector<Integer>                get_cov_matrix_location_i();
      vector<Integer>                get_cov_matrix_location_j();
      vector<vector<Integer> >       get_cov_matrix_coef();

      //Setter
      void set_gam_width_flg( Integer int_data );
      void set_scat_radius_list_uncertainty( vector<vector<Real> > real_vec );
      void set_j_pi_no( Integer int_data );
      void set_mass_a( vector<Real> real_vec );
      void set_mass_b( vector<Real> real_vec );
      void set_charge_a( vector<Real> real_vec );
      void set_charge_b( vector<Real> real_vec );
      void set_spin_a( vector<Real> real_vec );
      void set_spin_b( vector<Real> real_vec );
      void set_q_value( vector<Real> real_vec );
      void set_penetrability_calc_flg( vector<Real> real_vec );
      void set_shift_factor_calc_flg( vector<Real> real_vec );
      void set_reaction_type_flg( vector<Real> real_vec );
      void set_parity_a( vector<Real> real_vec );
      void set_parity_b( vector<Real> real_vec );
      void set_j_value_abs( vector<Real> real_vec );
      void set_parity( vector<Real> real_vec );
      void set_particle_pair_no( vector<vector<Real> > real_vec );
      void set_l_value( vector<vector<Real> > real_vec );
      void set_spin_channel( vector<vector<Real> > real_vec );
      void set_boundary_condition( vector<vector<Real> > real_vec );
      void set_scat_radius_eff( vector<vector<Real> > real_vec );
      void set_scat_radius_true( vector<vector<Real> > real_vec );
      void set_ene_reso( vector<vector<Real> > real_vec );
      void set_gam_width( vector<vector<vector<Real> > > real_vec );
      void set_ene_reso_uncertainty( vector<vector<Real> > real_vec );
      void set_gam_width_uncertainty( vector<vector<vector<Real> > > real_vec );
      void set_cov_matrix_digit_no( Integer int_data );
      void set_cov_param_no( Integer int_data );
      void set_cov_matrix_location_i( vector<Integer> int_vec );
      void set_cov_matrix_location_j( vector<Integer> int_vec );
      void set_cov_matrix_coef( vector<vector<Integer> > int_vec );
  };
}

#endif //R_MATRIX_LIMITED_COMPACT_COVARIANCE_DATA_CONTAINER_H
