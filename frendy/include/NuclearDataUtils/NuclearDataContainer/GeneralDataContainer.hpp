#ifndef GENERAL_DATA_CONTAINER_H
#define GENERAL_DATA_CONTAINER_H

#include "CommonUtils/ErrorManager.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class GeneralDataContainer
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

      Integer                  mat_no;
      Real                     mat_data;
      Real                     mass;
      Integer                  reso_flg;
      Integer                  fis_flg;
      Integer                  lib_identifier;
      Integer                  lib_mod_no;
      Real                     excitation_ene;
      Integer                  stability_flg_target;
      Integer                  state_no;
      Integer                  iso_state_no;
      Integer                  lib_format;
      Real                     mass_projectile;
      Real                     upper_ene_limit;
      Integer                  lib_release_no;
      Integer                  sub_lib_no;
      Integer                  lib_ver;
      Real                     temp;
      Real                     error_value;
      Integer                  special_derived_mat_flg;
      string                   brief_explain_word;
      string                   evaluated_institute;
      string                   evaluated_date;
      string                   evaluated_author;
      string                   evaluated_ref;
      string                   evaluated_date_ori;
      string                   evaluated_date_rev;
      string                   evaluated_date_end;
      string                   evaluated_data_specification;
      vector<vector<Integer> > file_section_data_list;
      vector<string>           comment_data;
      Integer                  state_no_target;
      Integer                  state_no_target_iso;
      Integer                  stability_flg;
      Real                     half_life;
      Real                     half_life_uncertainty;
      vector<Real>             decay_ene;
      vector<Real>             decay_ene_uncertainty;
      Real                     spin_target;
      Real                     parity_target;
      vector<Real>             decay_type;
      vector<Real>             daughter_iso_flg;
      vector<Real>             decay_ene_tot;
      vector<Real>             decay_ene_tot_uncertainty;
      vector<Real>             branching_ratio;
      vector<Real>             branching_ratio_uncertainty;
      vector<Real>             radiation_type;
      vector<Integer>          con_spectrum_flg;
      vector<Real>             discrete_spectrum_factor;
      vector<Real>             discrete_spectrum_factor_uncertainty;
      vector<Real>             discrete_ene_ave;
      vector<Real>             discrete_ene_ave_uncertainty;
      vector<Real>             cont_spectrum_factor;
      vector<Real>             cont_spectrum_factor_uncertainty;
      vector<vector<Real> >    discrete_ene;
      vector<vector<Real> >    discrete_ene_uncertainty;
      vector<vector<Real> >    discrete_intensity;
      vector<vector<Real> >    discrete_intensity_uncertainty;
      vector<vector<Real> >    decay_type_each_ene;
      vector<vector<Real> >    transition_type;
      vector<vector<Real> >    internal_pair_form_coef;
      vector<vector<Real> >    internal_pair_form_coef_uncertainty;
      vector<vector<Real> >    conv_coef_tot;
      vector<vector<Real> >    conv_coef_tot_uncertainty;
      vector<vector<Real> >    conv_coef_k;
      vector<vector<Real> >    conv_coef_k_uncertainty;
      vector<vector<Real> >    conv_coef_l;
      vector<vector<Real> >    conv_coef_l_uncertainty;
      vector<Real>             decay_type_each_rad;
      vector<Integer>          cont_spectrum_cov_flg;
      vector<vector<Integer> > cont_spectrum_cov_int_data;
      vector<vector<Integer> > cont_spectrum_cov_range_data;
      vector<vector<Real> >    cont_spectrum_cov_ene_data;
      vector<vector<Real> >    cont_spectrum_cov_data;
      vector<Integer>          cont_spectrum_cov_matrix_data_flg;
      vector<vector<Real> >    cont_spectrum_cov_ek_table;
      vector<vector<Real> >    cont_spectrum_cov_fk_table;

    public:
      //constructor
      GeneralDataContainer(void);

      //destructor
      virtual ~GeneralDataContainer(void);

      void clear();

      //Getter
      Integer                  get_mat_no();
      Real                     get_mat_data();
      Real                     get_mass();
      Integer                  get_reso_flg();
      Integer                  get_fis_flg();
      Integer                  get_lib_identifier();
      Integer                  get_lib_mod_no();
      Real                     get_excitation_ene();
      Integer                  get_stability_flg_target();
      Integer                  get_state_no();
      Integer                  get_iso_state_no();
      Integer                  get_lib_format();
      Real                     get_mass_projectile();
      Real                     get_upper_ene_limit();
      Integer                  get_lib_release_no();
      Integer                  get_sub_lib_no();
      Integer                  get_lib_ver();
      Real                     get_temp();
      Real                     get_error_value();
      Integer                  get_special_derived_mat_flg();
      string                   get_brief_explain_word();
      string                   get_evaluated_institute();
      string                   get_evaluated_date();
      string                   get_evaluated_author();
      string                   get_evaluated_ref();
      string                   get_evaluated_date_ori();
      string                   get_evaluated_date_rev();
      string                   get_evaluated_date_end();
      string                   get_evaluated_data_specification();
      vector<vector<Integer> > get_file_section_data_list();
      vector<string>           get_comment_data();
      Integer                  get_state_no_target();
      Integer                  get_state_no_target_iso();
      Integer                  get_stability_flg();
      Real                     get_half_life();
      Real                     get_half_life_uncertainty();
      vector<Real>             get_decay_ene();
      vector<Real>             get_decay_ene_uncertainty();
      Real                     get_spin_target();
      Real                     get_parity_target();
      vector<Real>             get_decay_type();
      vector<Real>             get_daughter_iso_flg();
      vector<Real>             get_decay_ene_tot();
      vector<Real>             get_decay_ene_tot_uncertainty();
      vector<Real>             get_branching_ratio();
      vector<Real>             get_branching_ratio_uncertainty();
      vector<Real>             get_radiation_type();
      vector<Integer>          get_con_spectrum_flg();
      vector<Real>             get_discrete_spectrum_factor();
      vector<Real>             get_discrete_spectrum_factor_uncertainty();
      vector<Real>             get_discrete_ene_ave();
      vector<Real>             get_discrete_ene_ave_uncertainty();
      vector<Real>             get_cont_spectrum_factor();
      vector<Real>             get_cont_spectrum_factor_uncertainty();
      vector<vector<Real> >    get_discrete_ene();
      vector<vector<Real> >    get_discrete_ene_uncertainty();
      vector<vector<Real> >    get_discrete_intensity();
      vector<vector<Real> >    get_discrete_intensity_uncertainty();
      vector<vector<Real> >    get_decay_type_each_ene();
      vector<vector<Real> >    get_transition_type();
      vector<vector<Real> >    get_internal_pair_form_coef();
      vector<vector<Real> >    get_internal_pair_form_coef_uncertainty();
      vector<vector<Real> >    get_conv_coef_tot();
      vector<vector<Real> >    get_conv_coef_tot_uncertainty();
      vector<vector<Real> >    get_conv_coef_k();
      vector<vector<Real> >    get_conv_coef_k_uncertainty();
      vector<vector<Real> >    get_conv_coef_l();
      vector<vector<Real> >    get_conv_coef_l_uncertainty();
      vector<Real>             get_decay_type_each_rad();
      vector<Integer>          get_cont_spectrum_cov_flg();
      vector<vector<Integer> > get_cont_spectrum_cov_int_data();
      vector<vector<Integer> > get_cont_spectrum_cov_range_data();
      vector<vector<Real> >    get_cont_spectrum_cov_ene_data();
      vector<vector<Real> >    get_cont_spectrum_cov_data();
      vector<Integer>          get_cont_spectrum_cov_matrix_data_flg();
      vector<vector<Real> >    get_cont_spectrum_cov_ek_table();
      vector<vector<Real> >    get_cont_spectrum_cov_fk_table();

      //Setter
      void set_mat_no( Integer int_data );
      void set_mat_data( Real real_data );
      void set_mass( Real real_data );
      void set_reso_flg( Integer int_data );
      void set_fis_flg( Integer int_data );
      void set_lib_identifier( Integer int_data );
      void set_lib_mod_no( Integer int_data );
      void set_excitation_ene( Real real_data );
      void set_stability_flg_target( Integer int_data );
      void set_state_no( Integer int_data );
      void set_iso_state_no( Integer int_data );
      void set_lib_format( Integer int_data );
      void set_mass_projectile( Real real_data );
      void set_upper_ene_limit( Real real_data );
      void set_lib_release_no( Integer int_data );
      void set_sub_lib_no( Integer int_data );
      void set_lib_ver( Integer int_data );
      void set_temp( Real real_data );
      void set_error_value( Real real_data );
      void set_special_derived_mat_flg( Integer int_data );
      void set_brief_explain_word( string str_data );
      void set_evaluated_institute( string str_data );
      void set_evaluated_date( string str_data );
      void set_evaluated_author( string str_data );
      void set_evaluated_ref( string str_data );
      void set_evaluated_date_ori( string str_data );
      void set_evaluated_date_rev( string str_data );
      void set_evaluated_date_end( string str_data );
      void set_evaluated_data_specification( string str_data );
      void set_file_section_data_list( vector<vector<Integer> > int_vec );
      void set_comment_data( vector<string> str_vec );
      void set_state_no_target( Integer int_data );
      void set_state_no_target_iso( Integer int_data );
      void set_stability_flg( Integer int_data );
      void set_half_life( Real real_data );
      void set_half_life_uncertainty( Real real_data );
      void set_decay_ene( vector<Real> real_vec );
      void set_decay_ene_uncertainty( vector<Real> real_vec );
      void set_spin_target( Real real_data );
      void set_parity_target( Real real_data );
      void set_decay_type( vector<Real> real_vec );
      void set_daughter_iso_flg( vector<Real> real_vec );
      void set_decay_ene_tot( vector<Real> real_vec );
      void set_decay_ene_tot_uncertainty( vector<Real> real_vec );
      void set_branching_ratio( vector<Real> real_vec );
      void set_branching_ratio_uncertainty( vector<Real> real_vec );
      void set_radiation_type( vector<Real> real_vec );
      void set_con_spectrum_flg( vector<Integer> int_vec );
      void set_discrete_spectrum_factor( vector<Real> real_vec );
      void set_discrete_spectrum_factor_uncertainty( vector<Real> real_vec );
      void set_discrete_ene_ave( vector<Real> real_vec );
      void set_discrete_ene_ave_uncertainty( vector<Real> real_vec );
      void set_cont_spectrum_factor( vector<Real> real_vec );
      void set_cont_spectrum_factor_uncertainty( vector<Real> real_vec );
      void set_discrete_ene( vector<vector<Real> > real_vec );
      void set_discrete_ene_uncertainty( vector<vector<Real> > real_vec );
      void set_discrete_intensity( vector<vector<Real> > real_vec );
      void set_discrete_intensity_uncertainty( vector<vector<Real> > real_vec );
      void set_decay_type_each_ene( vector<vector<Real> > real_vec );
      void set_transition_type( vector<vector<Real> > real_vec );
      void set_internal_pair_form_coef( vector<vector<Real> > real_vec );
      void set_internal_pair_form_coef_uncertainty( vector<vector<Real> > real_vec );
      void set_conv_coef_tot( vector<vector<Real> > real_vec );
      void set_conv_coef_tot_uncertainty( vector<vector<Real> > real_vec );
      void set_conv_coef_k( vector<vector<Real> > real_vec );
      void set_conv_coef_k_uncertainty( vector<vector<Real> > real_vec );
      void set_conv_coef_l( vector<vector<Real> > real_vec );
      void set_conv_coef_l_uncertainty( vector<vector<Real> > real_vec );
      void set_decay_type_each_rad( vector<Real> real_vec );
      void set_cont_spectrum_cov_flg( vector<Integer> int_vec );
      void set_cont_spectrum_cov_int_data( vector<vector<Integer> > int_vec );
      void set_cont_spectrum_cov_range_data( vector<vector<Integer> > int_vec );
      void set_cont_spectrum_cov_ene_data( vector<vector<Real> > real_vec );
      void set_cont_spectrum_cov_data( vector<vector<Real> > real_vec );
      void set_cont_spectrum_cov_matrix_data_flg( vector<Integer> int_vec );
      void set_cont_spectrum_cov_ek_table( vector<vector<Real> > real_vec );
      void set_cont_spectrum_cov_fk_table( vector<vector<Real> > real_vec );

      Integer get_izaid_ace();
  };
}

#endif //GENERAL_DATA_CONTAINER_H
