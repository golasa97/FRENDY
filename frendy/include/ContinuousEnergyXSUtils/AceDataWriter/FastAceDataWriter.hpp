#ifndef FAST_ACE_DATA_WRITER_H
#define FAST_ACE_DATA_WRITER_H

#include "CommonUtils/ErrorManager.hpp"
#include "CommonUtils/VectorClearer.hpp"
#include "CommonUtils/DigitAdjuster.hpp"
#include "ContinuousEnergyXSUtils/AceDataObject/FastAceDataObject.hpp"
#include "ContinuousEnergyXSUtils/OtherUtils/AceFileWriter.hpp"

namespace frendy
{
  class FastAceDataWriter
  {
    private:
      frendy::ErrorManager      err_obj;
      frendy::VectorClearer     clr_obj;
      frendy::DigitAdjuster     ad_obj;
      frendy::AceFileWriter     ace_wri_obj;

      static const int output_ace_format_mode = 0;
      static const int calc_pointer_mode      = 1;
      static const int string_data_mode       = 2;
      static const int real_vec_mode          = 3;

#ifdef DEBUG_MODE
  public:
#endif
      Integer           pointer_data_count;
      Integer           set_data_flg, set_ace_data_obj_flg;
      Integer           new_cummulative_angle_distr_flg,
                        detailed_photon_flg;

      frendy::FastAceDataObject ace_data_obj;

      //For output
      Integer opt_out_type;
      string  ace_file_name;
      string  discriptive_data;

      Integer line_no_pre;

      //For ACE data
      Integer         mcnpx_mode_flg;
      Integer         sub_lib_part, sub_lib_type; //izai, nlib
      Real            ene_max;
      vector<Integer> zi_vec;
      vector<Real>    awr_vec;

      vector<Real>             union_ene_grid, gamma_product_xs, photon_product_xs;

      vector<vector<Integer> > particle_production_data;
      vector<Real>             particle_production_ene_data;

      vector<vector<Real> >    photon_prod_yield_coef_direct, photon_prod_yield_coef_given;

      vector<Real>             photon_xs_ene_min, photon_prod_discon_ene_data;

      vector<vector<Real> >    equal_prob_data_ini;

      Real           aw0, tz; 
      int            izaid;
      vector<string> title_data;

      int             ntr, nr, mtntr, mtnr;
      Integer         nu_bar_repr_flg, nu_d_bar_repr_flg, nu_p_bar_repr_flg;
      vector<Integer> nu_int_data, nu_range_data, nu_d_int_data, nu_d_range_data,
                      nu_p_int_data, nu_p_range_data; 
      vector<Real>    nu_data, nu_ene_data, nu_d_data, nu_d_ene_data, nu_p_data, nu_p_ene_data,
                      nu_d_decay_constant;

      vector<Integer>       react_type_list, react_type_flg, react_type_ene_sta, react_type_list_two_body;
      vector<Real>          react_q_value;
      vector<Real>          react_xs_tot, react_xs_cap, react_xs_sc, react_xs_heat;
      vector<vector<Real> > react_xs;

      vector<Integer>                angular_distr_type_flg;
      vector<vector<Integer> >       angular_distr_int_data;
      vector<vector<Real> >          angular_distr_ene_data;
      vector<vector<vector<Real> > > angular_distr_cos_data, angular_distr_data, angular_distr_data_integ;

      vector<vector<Integer> >                ene_distr_ene_repr_flg;
      vector<vector<vector<Integer> > >       ene_distr_xs_part_int_data, ene_distr_xs_part_range_data;
      vector<vector<vector<Real> > >          ene_distr_xs_part_ene_data, ene_distr_xs_part_data;
      vector<vector<Real> >                   ene_distr_q_coef, ene_distr_mass_coef;
      vector<vector<vector<Integer> > >       ene_distr_ene_in_int_data, ene_distr_ene_in_range_data;
      vector<vector<vector<Real> > >          ene_distr_ene_in_data;
      vector<vector<vector<Integer> > >       ene_distr_ene_out_int_data;
      vector<vector<vector<vector<Real> > > > ene_distr_ene_out_ene_data, ene_distr_ene_out_data,
                                              ene_distr_ene_out_data_integ;
      vector<vector<Real> >                   ene_distr_upper_ene_limit;
      vector<vector<vector<Integer> > >       ene_distr_temp_eff_int_data, ene_distr_temp_eff_range_data,
                                              ene_distr_watt_a_int_data,   ene_distr_watt_a_range_data,
                                              ene_distr_watt_b_int_data,   ene_distr_watt_b_range_data;
      vector<vector<vector<Real> > >          ene_distr_temp_eff_ene_data, ene_distr_temp_eff_data,
                                              ene_distr_watt_a_ene_data,   ene_distr_watt_a_data,
                                              ene_distr_watt_b_ene_data,   ene_distr_watt_b_data;

      vector<vector<Integer> >                   prod_yield_tot_int_data, prod_yield_tot_range_data;
      vector<vector<Real> >                      prod_yield_tot_ene_data, prod_yield_tot_data;
      vector<vector<Integer> >                   prod_distr_func_flg;
      vector<vector<Integer> >                   prod_distr_n_body_particle_no, prod_distr_prob_data_no;
      vector<vector<Real> >                      prod_distr_n_body_mass;
      vector<vector<vector<Integer> > >          prod_distr_prob_ene_in_int_data,
                                                 prod_distr_prob_ene_in_range_data,
                                                 prod_distr_prob_ene_out_int_data;
      vector<vector<vector<Real> > >             prod_distr_prob_ene_in_data;
      vector<vector<vector<vector<Integer> > > > prod_distr_prob_mu_int_data, prod_distr_prob_mu_range_data;
      vector<vector<vector<vector<Real> > > >    prod_distr_prob_mu_data, prod_distr_prob_mu_data_integ,
                                                 prod_distr_prob_data,    prod_distr_prob_data_integ,
                                                 prod_distr_prob_ene_out_data,
                                                 prod_distr_prob_coef_a, prod_distr_prob_coef_b;
      vector<vector<vector<vector<vector<Integer> > > > > prod_distr_prob_int_vec, prod_distr_prob_range_vec;
      vector<vector<vector<vector<vector<Real> > > > >    prod_distr_prob_mu_vec, prod_distr_prob_ene_out_vec,
                                                          prod_distr_prob_vec, prod_distr_prob_vec_integ;

      Integer                        unreso_prob_tab_int_data,
                                     unreso_prob_tab_inela_comp_flg, unreso_prob_tab_abs_comp_flg,
                                     unreso_prob_tab_self_shielding_flg;
      vector<Real>                   unreso_prob_tab_ene;
      vector<vector<Real> >          unreso_prob_tab_heat, unreso_prob_tab_sample_no;
      vector<vector<vector<Real> > > unreso_prob_tab_table;

      vector<Real>                   nu_d_ene_min, nu_d_ene_max;
      vector<vector<Integer> >       nu_d_xs_part_int_data, nu_d_xs_part_range_data;
      vector<vector<Real> >          nu_d_xs_part_ene_data, nu_d_xs_part_data;
      vector<vector<Integer> >       nu_d_ene_in_int_data, nu_d_ene_in_range_data, nu_d_ene_out_int_data;
      vector<vector<Real> >          nu_d_ene_in_data;
      vector<vector<vector<Real> > > nu_d_ene_out_data, nu_d_ene_distr_data, nu_d_ene_distr_data_integ;

      vector<Integer>          photon_prod_file_no, photon_prod_reaction_type,
                               photon_prod_reaction_type_all,
                               photon_prod_reaction_type_without_xs;
      vector<Real>             photon_prod_binding_ene;
      vector<vector<Integer> > photon_prod_multiplicity_int_data, photon_prod_multiplicity_range_data;
      vector<vector<Real> >    photon_prod_multiplicity_ene_data, photon_prod_multiplicity_data;
      vector<int>              photon_prod_xs_ene_no;
      vector<vector<int> >     photon_prod_xs_non_zero_pos;
      vector<vector<Real> >    photon_prod_xs_data;
      vector<vector<Integer> > photon_prod_distr_int_data, photon_prod_distr_range_data;
      vector<vector<Real> >    photon_prod_distr_ene_data, photon_prod_distr_data;

      vector<vector<Real> >          photon_angular_distr_ene_data;
      vector<vector<vector<Real> > > photon_angular_distr_prob_cos_data;

      vector<Integer>                   photon_energy_distr_flg, photon_energy_distr_ene_flg;
      vector<Real>                      photon_energy_distr_binding_ene_data;
      vector<vector<Integer> >          photon_energy_distr_int_data, photon_energy_distr_range_data;
      vector<vector<Real> >             photon_energy_distr_ene_data, photon_energy_distr_prob_data;
      vector<vector<Integer> >          photon_energy_distr_ene_in_int_data,
                                        photon_energy_distr_ene_in_range_data;
      vector<vector<Real> >             photon_energy_distr_ene_in_data;
      vector<vector<Integer> >          photon_energy_distr_weight_int_data;
      vector<vector<vector<Real> > >    photon_energy_distr_weight_ene_data, photon_energy_distr_weight_data,
                                        photon_energy_distr_weight_data_integ;
      vector<Real>                      photon_energy_distr_gamma_mass_product;

      vector<Integer>                   particle_prod_flg, particle_prod_count,
                                        particle_prod_ene_sta, particle_prod_ene_no;
      vector<vector<Integer> >          particle_prod_file_no, particle_prod_frame_flg,
                                        particle_prod_reaction_type, particle_prod_reaction_type_all;
      vector<vector<Real> >             particle_prod_xs, particle_prod_heat;
      vector<vector<vector<Integer> > > particle_prod_distr_int_data, particle_prod_distr_range_data;
      vector<vector<vector<Real> > >    particle_prod_distr_ene_data, particle_prod_distr_data;
      vector<vector<vector<Integer> > > particle_prod_angular_int_data;
      vector<vector<vector<Real> > >    particle_prod_angular_ene_data;
      vector<vector<vector<vector<Real> > > >  particle_prod_angular_cos_data, particle_prod_angular_distr_data,
                                               particle_prod_angular_distr_data_integ;

      vector<vector<Integer> >          particle_prod_ene_flg;
      vector<vector<Real> >             particle_prod_q_value, particle_prod_mass_coef;
      vector<vector<vector<Integer> > > particle_prod_ene_int_data, particle_prod_ene_range_data;
      vector<vector<vector<Real> > >    particle_prod_ene_data,     particle_prod_ene_prob_data;

      //For distr_func_flg = 1 : second energy, distr_func_flg = 7 : angle (mu)
      vector<vector<vector<Integer> > >          particle_prod_ene_in_int_data, particle_prod_ene_in_range_data;
      vector<vector<vector<Real> > >             particle_prod_ene_in_data;
      vector<vector<vector<Integer> > >          particle_prod_a_int_data;
      vector<vector<vector<vector<Real> > > >    particle_prod_a_data, particle_prod_a_distr_data,
                                                 particle_prod_a_distr_data_integ;
      vector<vector<vector<vector<Real> > > >    particle_prod_ene_out_coef_a, particle_prod_ene_out_coef_b;

      //For distr_func_flg = 1 : angle (mu), distr_func_flg = 7 : second energy
      vector<vector<vector<vector<Integer> > > >       particle_prod_b_int_data;
      vector<vector<vector<vector<vector<Real> > > > > particle_prod_b_data,
                                                       particle_prod_b_prob_data,
                                                       particle_prod_b_prob_data_integ;


      //For pointer data
      int         len2, nes, ntrp, ntype, ndnf, esz, nu, mtr, lqr, tyr, lsig, sig,
                  land, andi, ldlw, dlw, gpd, mtrp, lsigp, sigp, landp, andp, ldlwp, dlwp, yp, fis,
                  endi, iurpt, nud, dndat, ldnd, dnd, ptype, ntro, ploct;
      vector<int>                            ene_distr_pointer, nu_d_pointer, photon_prod_pointer,
                                             photon_angular_pointer, photon_ene_pointer,
                                             photon_ene_distr_pointer;
      vector<vector<int> >                   angular_distr_pointer, ene_distr_ene_repr_end_pointer,
                                             ene_distr_ene_repr_pointer,
                                             nu_d_ene_in_pointer, photon_angular_ene_pointer,
                                             photon_ene_weight_pointer, particle_prod_pointer,
                                             particle_prod_distr_pointer, particle_prod_angular_pointer,
                                             particle_prod_ene_pointer, particle_prod_ene_in_pointer;
      vector<vector<vector<int> > >          ene_distr_ene_in_pointer, particle_prod_angular_ene_pointer,
                                             particle_prod_a_pointer;
      vector<vector<vector<vector<int> > > > ene_distr_ene_out_pointer, particle_prod_b_pointer;

      void clear_ace_data();
      void clear_ace_base_data();
      void clear_ace_ene_angular_distr_data();
      void clear_ace_prod_distr_data();
      void clear_ace_photon_data();
      void clear_ace_particle_data();
      void clear_ace_pointer_data();

      void copy_fast_ace_data();
      void copy_fast_ace_base_data();
      void copy_fast_ace_ene_angular_distr_data();
      void copy_fast_ace_prod_distr_data();
      void copy_fast_ace_photon_data();
      void copy_fast_ace_particle_data();
      void copy_fast_ace_pointer_data();

      void copy_fast_ace_pointer_data(frendy::FastAceDataObject& fast_ace_data_obj);

      Integer get_line_no();

      //Output processing results on screen
      void output_ace_data();

      //Write ace file
      void output_ace_format(int calc_mode);
      void output_ace_format_header(int calc_mode);
      void output_ace_format_base_data(int calc_mode);
      void output_ace_format_angular_distribution_data(int calc_mode);
      void output_ace_format_energy_distribution_data(int calc_mode);
      void output_ace_format_unreso_prob_table_data(int calc_mode);
      void output_ace_format_nu_d_data(int calc_mode);
      void output_ace_format_gamma_production_xs(int calc_mode);
      void output_ace_format_photon_production_data(int calc_mode);
      void output_ace_format_photon_energy_distr_data(int calc_mode);
      void output_ace_format_particle_production_data(int calc_mode);

      void output_ace_format_binary_mode();

      void check_set_data();

    public:
      //constructor
      FastAceDataWriter(void);

      //destructor
      virtual ~FastAceDataWriter(void);

      static const Integer ascii_mode  = 1;
      static const Integer binary_mode = 2;

      void clear();

      void write_ace_format();
      vector<string> get_ace_text_data();
      void get_ace_data_for_mg(vector<string>& title_vec, vector<int>& izaw_vec,
                               vector<int>& nxs_vec, vector<int>& jxs_vec,
                               vector<double>& xss_vec);
      vector<double> get_xss_data();

      void   write_dir_data(string dir_name);
      string get_dir_data();

      //Setter
      void set_ace_data_obj(frendy::FastAceDataObject& data_obj);
      void set_opt_out_type(Integer int_val);
      void set_new_cummulative_angle_distr_flg(Integer int_val);
      void set_detailed_photon_flg(Integer int_val);
      void set_ace_file_name(string str_data);
      void set_previous_line_no(Integer int_val);

      //Getter
      frendy::FastAceDataObject get_ace_data_obj();
      Integer                   get_opt_out_type();
      Integer                   get_new_cummulative_angle_distr_flg();
      Integer                   get_detailed_photon_flg();
      string                    get_ace_file_name();
      Integer                   get_previous_line_no();
  };
}

#endif //FAST_ACE_DATA_WRITER_H
