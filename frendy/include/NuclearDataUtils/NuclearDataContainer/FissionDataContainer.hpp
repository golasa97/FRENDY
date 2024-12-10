#ifndef FISSION_DATA_CONTAINER_H
#define FISSION_DATA_CONTAINER_H

#include "CommonUtils/ErrorManager.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class FissionDataContainer
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

      Integer                  nu_bar_repr_flg;
      vector<Real>             nu_bar_polynomial_coef;
      vector<Integer>          nu_bar_int_data;
      vector<Integer>          nu_bar_range_data;
      vector<Real>             nu_bar_ene_data;
      vector<Real>             nu_bar_data;

      Integer                  nu_d_bar_repr_flg;
      vector<Real>             nu_d_bar_polynomial_coef;
      vector<Integer>          nu_d_bar_int_data;
      vector<Integer>          nu_d_bar_range_data;
      vector<Real>             nu_d_bar_ene_data;
      vector<Real>             nu_d_bar_data;
      vector<Real>             nu_d_ene_data;
      vector<Integer>          nu_d_decay_int_data;
      vector<Integer>          nu_d_decay_range_data;
      vector<vector<Real> >    nu_d_decay_constant;
      vector<vector<Real> >    nu_d_delayed_group_abundance;

      Integer                  nu_p_bar_repr_flg;
      vector<Real>             nu_p_bar_polynomial_coef;
      vector<Integer>          nu_p_bar_int_data;
      vector<Integer>          nu_p_bar_range_data;
      vector<Real>             nu_p_bar_ene_data;
      vector<Real>             nu_p_bar_data;

      Integer                  fis_ene_repr_flg;
      vector<Real>             fis_ene_tot;
      vector<Real>             fis_ene_fp;
      vector<Real>             fis_ene_n_p;
      vector<Real>             fis_ene_n_d;
      vector<Real>             fis_ene_gam_p;
      vector<Real>             fis_ene_gam_d;
      vector<Real>             fis_ene_beta_d;
      vector<Real>             fis_ene_neutrino;
      vector<Real>             fis_ene_non_neutrino;
      vector<Real>             fis_ene_tot_uncertainty;
      vector<Real>             fis_ene_fp_uncertainty;
      vector<Real>             fis_ene_n_p_uncertainty;
      vector<Real>             fis_ene_n_d_uncertainty;
      vector<Real>             fis_ene_gam_p_uncertainty;
      vector<Real>             fis_ene_gam_d_uncertainty;
      vector<Real>             fis_ene_beta_d_uncertainty;
      vector<Real>             fis_ene_neutrino_uncertainty;
      vector<Real>             fis_ene_non_neutrino_uncertainty;
      vector<Integer>          fis_ene_index;
      vector<Integer>          fis_ene_evaluation_flg;
      vector<vector<Integer> > fis_ene_table_int_data;
      vector<vector<Integer> > fis_ene_table_range_data;
      vector<vector<Real> >    fis_ene_table_ene_data;
      vector<vector<Real> >    fis_ene_table_data;

      Integer                  photon_d_repr_flg;
      vector<Real>             photon_d_ene;
      vector<vector<Integer> > photon_d_int_data;
      vector<vector<Integer> > photon_d_range_data;
      vector<vector<Real> >    photon_d_time_data;
      vector<vector<Real> >    photon_d_data;
      vector<Real>             photon_d_precursor_decay_const;

      vector<vector<Real> >    fp_data_independent;
      vector<vector<Real> >    state_designator_fp_independent;
      vector<vector<Real> >    yield_independent;
      vector<vector<Real> >    yield_independent_uncertainty;
      vector<Real>             incident_ene_independent;
      vector<Integer>          ene_int_data_independent;
      vector<vector<Real> >    fp_data_cumulative;
      vector<vector<Real> >    state_designator_fp_cumulative;
      vector<vector<Real> >    yield_cumulative;
      vector<vector<Real> >    yield_cumulative_uncertainty;
      vector<Real>             incident_ene_cumulative;
      vector<Integer>          ene_int_data_cumulative;

    public:
      //constructor
      FissionDataContainer(void);

      //destructor
      virtual ~FissionDataContainer(void);

      void clear();

      //Getter
      Integer                  get_nu_bar_repr_flg();
      vector<Real>             get_nu_bar_polynomial_coef();
      vector<Integer>          get_nu_bar_int_data();
      vector<Integer>          get_nu_bar_range_data();
      vector<Real>             get_nu_bar_ene_data();
      vector<Real>             get_nu_bar_data();
      Integer                  get_nu_d_bar_repr_flg();
      vector<Real>             get_nu_d_bar_polynomial_coef();
      vector<Integer>          get_nu_d_bar_int_data();
      vector<Integer>          get_nu_d_bar_range_data();
      vector<Real>             get_nu_d_bar_ene_data();
      vector<Real>             get_nu_d_bar_data();
      vector<Real>             get_nu_d_ene_data();
      vector<Integer>          get_nu_d_decay_int_data();
      vector<Integer>          get_nu_d_decay_range_data();
      vector<vector<Real> >    get_nu_d_decay_constant();
      vector<vector<Real> >    get_nu_d_delayed_group_abundance();
      Integer                  get_nu_p_bar_repr_flg();
      vector<Real>             get_nu_p_bar_polynomial_coef();
      vector<Integer>          get_nu_p_bar_int_data();
      vector<Integer>          get_nu_p_bar_range_data();
      vector<Real>             get_nu_p_bar_ene_data();
      vector<Real>             get_nu_p_bar_data();
      Integer                  get_fis_ene_repr_flg();
      vector<Real>             get_fis_ene_tot();
      vector<Real>             get_fis_ene_fp();
      vector<Real>             get_fis_ene_n_p();
      vector<Real>             get_fis_ene_n_d();
      vector<Real>             get_fis_ene_gam_p();
      vector<Real>             get_fis_ene_gam_d();
      vector<Real>             get_fis_ene_beta_d();
      vector<Real>             get_fis_ene_neutrino();
      vector<Real>             get_fis_ene_non_neutrino();
      vector<Real>             get_fis_ene_tot_uncertainty();
      vector<Real>             get_fis_ene_fp_uncertainty();
      vector<Real>             get_fis_ene_n_p_uncertainty();
      vector<Real>             get_fis_ene_n_d_uncertainty();
      vector<Real>             get_fis_ene_gam_p_uncertainty();
      vector<Real>             get_fis_ene_gam_d_uncertainty();
      vector<Real>             get_fis_ene_beta_d_uncertainty();
      vector<Real>             get_fis_ene_neutrino_uncertainty();
      vector<Real>             get_fis_ene_non_neutrino_uncertainty();
      vector<Integer>          get_fis_ene_index();
      vector<Integer>          get_fis_ene_evaluation_flg();
      vector<vector<Integer> > get_fis_ene_table_int_data();
      vector<vector<Integer> > get_fis_ene_table_range_data();
      vector<vector<Real> >    get_fis_ene_table_ene_data();
      vector<vector<Real> >    get_fis_ene_table_data();
      Integer                  get_photon_d_repr_flg();
      vector<Real>             get_photon_d_ene();
      vector<vector<Integer> > get_photon_d_int_data();
      vector<vector<Integer> > get_photon_d_range_data();
      vector<vector<Real> >    get_photon_d_time_data();
      vector<vector<Real> >    get_photon_d_data();
      vector<Real>             get_photon_d_precursor_decay_const();
      vector<vector<Real> >    get_fp_data_independent();
      vector<vector<Real> >    get_state_designator_fp_independent();
      vector<vector<Real> >    get_yield_independent();
      vector<vector<Real> >    get_yield_independent_uncertainty();
      vector<Real>             get_incident_ene_independent();
      vector<Integer>          get_ene_int_data_independent();
      vector<vector<Real> >    get_fp_data_cumulative();
      vector<vector<Real> >    get_state_designator_fp_cumulative();
      vector<vector<Real> >    get_yield_cumulative();
      vector<vector<Real> >    get_yield_cumulative_uncertainty();
      vector<Real>             get_incident_ene_cumulative();
      vector<Integer>          get_ene_int_data_cumulative();

      //Setter
      void set_nu_bar_repr_flg( Integer int_data );
      void set_nu_bar_polynomial_coef( vector<Real> real_vec );
      void set_nu_bar_int_data( vector<Integer> int_vec );
      void set_nu_bar_range_data( vector<Integer> int_vec );
      void set_nu_bar_ene_data( vector<Real> real_vec );
      void set_nu_bar_data( vector<Real> real_vec );
      void set_nu_d_bar_repr_flg( Integer int_data );
      void set_nu_d_bar_polynomial_coef( vector<Real> real_vec );
      void set_nu_d_bar_int_data( vector<Integer> int_vec );
      void set_nu_d_bar_range_data( vector<Integer> int_vec );
      void set_nu_d_bar_ene_data( vector<Real> real_vec );
      void set_nu_d_bar_data( vector<Real> real_vec );
      void set_nu_d_ene_data( vector<Real> real_vec );
      void set_nu_d_decay_int_data( vector<Integer> int_vec );
      void set_nu_d_decay_range_data( vector<Integer> int_vec );
      void set_nu_d_decay_constant( vector<vector<Real> > real_vec );
      void set_nu_d_delayed_group_abundance( vector<vector<Real> > real_vec );
      void set_nu_p_bar_repr_flg( Integer int_data );
      void set_nu_p_bar_polynomial_coef( vector<Real> real_vec );
      void set_nu_p_bar_int_data( vector<Integer> int_vec );
      void set_nu_p_bar_range_data( vector<Integer> int_vec );
      void set_nu_p_bar_ene_data( vector<Real> real_vec );
      void set_nu_p_bar_data( vector<Real> real_vec );
      void set_fis_ene_repr_flg( Integer int_data );
      void set_fis_ene_tot( vector<Real> real_vec );
      void set_fis_ene_fp( vector<Real> real_vec );
      void set_fis_ene_n_p( vector<Real> real_vec );
      void set_fis_ene_n_d( vector<Real> real_vec );
      void set_fis_ene_gam_p( vector<Real> real_vec );
      void set_fis_ene_gam_d( vector<Real> real_vec );
      void set_fis_ene_beta_d( vector<Real> real_vec );
      void set_fis_ene_neutrino( vector<Real> real_vec );
      void set_fis_ene_non_neutrino( vector<Real> real_vec );
      void set_fis_ene_tot_uncertainty( vector<Real> real_vec );
      void set_fis_ene_fp_uncertainty( vector<Real> real_vec );
      void set_fis_ene_n_p_uncertainty( vector<Real> real_vec );
      void set_fis_ene_n_d_uncertainty( vector<Real> real_vec );
      void set_fis_ene_gam_p_uncertainty( vector<Real> real_vec );
      void set_fis_ene_gam_d_uncertainty( vector<Real> real_vec );
      void set_fis_ene_beta_d_uncertainty( vector<Real> real_vec );
      void set_fis_ene_neutrino_uncertainty( vector<Real> real_vec );
      void set_fis_ene_non_neutrino_uncertainty( vector<Real> real_vec );
      void set_fis_ene_index( vector<Integer> int_vec );
      void set_fis_ene_evaluation_flg( vector<Integer> int_vec );
      void set_fis_ene_table_int_data( vector<vector<Integer> > int_vec );
      void set_fis_ene_table_range_data( vector<vector<Integer> > int_vec );
      void set_fis_ene_table_ene_data( vector<vector<Real> > real_vec );
      void set_fis_ene_table_data( vector<vector<Real> > real_vec );
      void set_photon_d_repr_flg( Integer int_data );
      void set_photon_d_ene( vector<Real> real_vec );
      void set_photon_d_int_data( vector<vector<Integer> > int_vec );
      void set_photon_d_range_data( vector<vector<Integer> > int_vec );
      void set_photon_d_time_data( vector<vector<Real> > real_vec );
      void set_photon_d_data( vector<vector<Real> > real_vec );
      void set_photon_d_precursor_decay_const( vector<Real> real_vec );
      void set_fp_data_independent( vector<vector<Real> > real_vec );
      void set_state_designator_fp_independent( vector<vector<Real> > real_vec );
      void set_yield_independent( vector<vector<Real> > real_vec );
      void set_yield_independent_uncertainty( vector<vector<Real> > real_vec );
      void set_incident_ene_independent( vector<Real> real_vec );
      void set_ene_int_data_independent( vector<Integer> int_vec );
      void set_fp_data_cumulative( vector<vector<Real> > real_vec );
      void set_state_designator_fp_cumulative( vector<vector<Real> > real_vec );
      void set_yield_cumulative( vector<vector<Real> > real_vec );
      void set_yield_cumulative_uncertainty( vector<vector<Real> > real_vec );
      void set_incident_ene_cumulative( vector<Real> real_vec );
      void set_ene_int_data_cumulative( vector<Integer> int_vec );
  };
}

#endif //FISSION_DATA_CONTAINER_H
