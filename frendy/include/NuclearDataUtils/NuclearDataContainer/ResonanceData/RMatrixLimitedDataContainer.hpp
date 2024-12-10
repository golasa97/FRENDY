#ifndef R_MATRIX_LIMITED_DATA_CONTAINER_H
#define R_MATRIX_LIMITED_DATA_CONTAINER_H

#include "CommonUtils/ErrorManager.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class RMatrixLimitedDataContainer
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

      Integer                        gam_width_flg;
      Integer                        r_matrix_calc_flg;
      Integer                        relativistic_flg;
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
      vector<Integer>                back_ground_r_matrix_flg;
      vector<Integer>                non_hard_sphere_flg;
      vector<vector<Real> >          particle_pair_no;
      vector<vector<Real> >          l_value;
      vector<vector<Real> >          spin_channel;
      vector<vector<Real> >          boundary_condition;
      vector<vector<Real> >          scat_radius_eff;
      vector<vector<Real> >          scat_radius_true;
      vector<vector<Real> >          ene_reso;
      vector<vector<vector<Real> > > gam_width;
      vector<Integer>                back_ground_r_matrix_index;
      vector<Integer>                back_ground_r_matrix_add_flg;
      vector<vector<Integer> >       complex_real_int_data;
      vector<vector<Integer> >       complex_real_range_data;
      vector<vector<Real> >          complex_real_ene_data;
      vector<vector<Real> >          complex_real_data;
      vector<vector<Integer> >       complex_imagin_int_data;
      vector<vector<Integer> >       complex_imagin_range_data;
      vector<vector<Real> >          complex_imagin_ene_data;
      vector<vector<Real> >          complex_imagin_data;
      vector<Real>                   sammy_logarithmic_data_r_com;
      vector<Real>                   sammy_logarithmic_data_s_com;
      vector<Real>                   sammy_logarithmic_data_r_lin;
      vector<Real>                   sammy_logarithmic_data_s_lin;
      vector<Real>                   sammy_logarithmic_data_r_q;
      vector<Real>                   sammy_logarithmic_data_e_up;
      vector<Real>                   sammy_logarithmic_data_e_down;
      vector<Real>                   frohner_data_rc;
      vector<Real>                   frohner_data_s;
      vector<Real>                   frohner_data_gam_r;
      vector<Real>                   frohner_data_e_up;
      vector<Real>                   frohner_data_e_down;
      vector<Integer>                non_hard_sphere_add_flg;
      vector<vector<Integer> >       phase_shift_real_int_data;
      vector<vector<Integer> >       phase_shift_real_range_data;
      vector<vector<Real> >          phase_shift_real_ene_data;
      vector<vector<Real> >          phase_shift_real_data;
      vector<vector<Integer> >       phase_shift_imagin_int_data;
      vector<vector<Integer> >       phase_shift_imagin_range_data;
      vector<vector<Real> >          phase_shift_imagin_ene_data;
      vector<vector<Real> >          phase_shift_imagin_data;

    public:
      //constructor
      RMatrixLimitedDataContainer(void);

      //destructor
      virtual ~RMatrixLimitedDataContainer(void);

      void clear();

      //Getter
      Integer                        get_gam_width_flg();
      Integer                        get_r_matrix_calc_flg();
      Integer                        get_relativistic_flg();
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
      vector<Integer>                get_back_ground_r_matrix_flg();
      vector<Integer>                get_non_hard_sphere_flg();
      vector<vector<Real> >          get_particle_pair_no();
      vector<vector<Real> >          get_l_value();
      vector<vector<Real> >          get_spin_channel();
      vector<vector<Real> >          get_boundary_condition();
      vector<vector<Real> >          get_scat_radius_eff();
      vector<vector<Real> >          get_scat_radius_true();
      vector<vector<Real> >          get_ene_reso();
      vector<vector<vector<Real> > > get_gam_width();
      vector<Integer>                get_back_ground_r_matrix_index();
      vector<Integer>                get_back_ground_r_matrix_add_flg();
      vector<vector<Integer> >       get_complex_real_int_data();
      vector<vector<Integer> >       get_complex_real_range_data();
      vector<vector<Real> >          get_complex_real_ene_data();
      vector<vector<Real> >          get_complex_real_data();
      vector<vector<Integer> >       get_complex_imagin_int_data();
      vector<vector<Integer> >       get_complex_imagin_range_data();
      vector<vector<Real> >          get_complex_imagin_ene_data();
      vector<vector<Real> >          get_complex_imagin_data();
      vector<Real>                   get_sammy_logarithmic_data_r_com();
      vector<Real>                   get_sammy_logarithmic_data_s_com();
      vector<Real>                   get_sammy_logarithmic_data_r_lin();
      vector<Real>                   get_sammy_logarithmic_data_s_lin();
      vector<Real>                   get_sammy_logarithmic_data_r_q();
      vector<Real>                   get_sammy_logarithmic_data_e_up();
      vector<Real>                   get_sammy_logarithmic_data_e_down();
      vector<Real>                   get_frohner_data_rc();
      vector<Real>                   get_frohner_data_s();
      vector<Real>                   get_frohner_data_gam_r();
      vector<Real>                   get_frohner_data_e_up();
      vector<Real>                   get_frohner_data_e_down();
      vector<Integer>                get_non_hard_sphere_add_flg();
      vector<vector<Integer> >       get_phase_shift_real_int_data();
      vector<vector<Integer> >       get_phase_shift_real_range_data();
      vector<vector<Real> >          get_phase_shift_real_ene_data();
      vector<vector<Real> >          get_phase_shift_real_data();
      vector<vector<Integer> >       get_phase_shift_imagin_int_data();
      vector<vector<Integer> >       get_phase_shift_imagin_range_data();
      vector<vector<Real> >          get_phase_shift_imagin_ene_data();
      vector<vector<Real> >          get_phase_shift_imagin_data();

      //Setter
      void set_gam_width_flg( Integer int_data );
      void set_r_matrix_calc_flg( Integer int_data );
      void set_relativistic_flg( Integer int_data );
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
      void set_back_ground_r_matrix_flg( vector<Integer> int_vec );
      void set_non_hard_sphere_flg( vector<Integer> int_vec );
      void set_particle_pair_no( vector<vector<Real> > real_vec );
      void set_l_value( vector<vector<Real> > real_vec );
      void set_spin_channel( vector<vector<Real> > real_vec );
      void set_boundary_condition( vector<vector<Real> > real_vec );
      void set_scat_radius_eff( vector<vector<Real> > real_vec );
      void set_scat_radius_true( vector<vector<Real> > real_vec );
      void set_ene_reso( vector<vector<Real> > real_vec );
      void set_gam_width( vector<vector<vector<Real> > > real_vec );
      void set_back_ground_r_matrix_index( vector<Integer> int_vec );
      void set_back_ground_r_matrix_add_flg( vector<Integer> int_vec );
      void set_complex_real_int_data( vector<vector<Integer> > int_vec );
      void set_complex_real_range_data( vector<vector<Integer> > int_vec );
      void set_complex_real_ene_data( vector<vector<Real> > real_vec );
      void set_complex_real_data( vector<vector<Real> > real_vec );
      void set_complex_imagin_int_data( vector<vector<Integer> > int_vec );
      void set_complex_imagin_range_data( vector<vector<Integer> > int_vec );
      void set_complex_imagin_ene_data( vector<vector<Real> > real_vec );
      void set_complex_imagin_data( vector<vector<Real> > real_vec );
      void set_sammy_logarithmic_data_r_com( vector<Real> real_vec );
      void set_sammy_logarithmic_data_s_com( vector<Real> real_vec );
      void set_sammy_logarithmic_data_r_lin( vector<Real> real_vec );
      void set_sammy_logarithmic_data_s_lin( vector<Real> real_vec );
      void set_sammy_logarithmic_data_r_q( vector<Real> real_vec );
      void set_sammy_logarithmic_data_e_up( vector<Real> real_vec );
      void set_sammy_logarithmic_data_e_down( vector<Real> real_vec );
      void set_frohner_data_rc( vector<Real> real_vec );
      void set_frohner_data_s( vector<Real> real_vec );
      void set_frohner_data_gam_r( vector<Real> real_vec );
      void set_frohner_data_e_up( vector<Real> real_vec );
      void set_frohner_data_e_down( vector<Real> real_vec );
      void set_non_hard_sphere_add_flg( vector<Integer> int_vec );
      void set_phase_shift_real_int_data( vector<vector<Integer> > int_vec );
      void set_phase_shift_real_range_data( vector<vector<Integer> > int_vec );
      void set_phase_shift_real_ene_data( vector<vector<Real> > real_vec );
      void set_phase_shift_real_data( vector<vector<Real> > real_vec );
      void set_phase_shift_imagin_int_data( vector<vector<Integer> > int_vec );
      void set_phase_shift_imagin_range_data( vector<vector<Integer> > int_vec );
      void set_phase_shift_imagin_ene_data( vector<vector<Real> > real_vec );
      void set_phase_shift_imagin_data( vector<vector<Real> > real_vec );
  };
}

#endif //R_MATRIX_LIMITED_DATA_CONTAINER_H
