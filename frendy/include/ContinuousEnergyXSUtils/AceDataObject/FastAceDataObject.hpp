#ifndef FAST_ACE_DATA_OBJECT_H
#define FAST_ACE_DATA_OBJECT_H

#include "Config/CommonData.hpp"
#include "CommonUtils/VectorClearer.hpp"
#include "CommonUtils/TabInterpolator.hpp"
#include "CommonUtils/ErrorManager.hpp"

namespace frendy
{
  class FastAceDataObject
  {
    private:
      void clear_calc_data();
      void clear_ace_data();
      void clear_ace_base_data();
      void clear_ace_ene_angular_distr_data();
      void clear_ace_prod_distr_data();
      void clear_ace_photon_data();
      void clear_ace_particle_data();
      void clear_ace_pointer_data();
  
      frendy::VectorClearer clr_obj;

      //For ACE data
      Integer mcnpx_mode_flg;
      Integer mat;
      Real    temp;
      Integer sub_lib_part, sub_lib_type; //izai, nlib
      Real    ene_max;

      vector<Integer> zi_vec;
      vector<Real>    awr_vec;

      vector<Real>             union_ene_grid, gamma_product_xs, photon_product_xs;

      vector<vector<Integer> > particle_production_data;
      vector<Real>             particle_production_ene_data;

      vector<vector<Real> >    photon_prod_yield_coef_direct, photon_prod_yield_coef_given;

      vector<Real>             photon_xs_ene_min, photon_prod_discon_ene_data;

      vector<vector<Real> >    equal_prob_data_ini;

      Real            aw0, tz; 
      int             izaid;
      vector<string>  title_data;
      string          discriptive_data;

      int             ntr, nr, mtntr, mtnr;
      Integer         nu_bar_repr_flg, nu_d_bar_repr_flg, nu_p_bar_repr_flg;
      vector<Integer> nu_int_data, nu_range_data, nu_d_int_data, nu_d_range_data,
                      nu_p_int_data, nu_p_range_data; 
      vector<Real>    nu_data, nu_ene_data, nu_d_data, nu_d_ene_data, nu_p_data, nu_p_ene_data,
                      nu_d_decay_constant;

      vector<Integer>       react_type_list, react_type_flg, react_type_ene_sta;
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

////////////////////////////////////////////////////////////////////////////////////////////////////

    public:
      //constructor
      FastAceDataObject(void);

      //destructor
      virtual ~FastAceDataObject(void);

      void clear();

      void                  get_bondarenko_xs(Real background_xs, vector<Real>& ene_vec,
                                              vector<vector<Real> >& xs_vec);
      vector<vector<Real> > get_bondarenko_xs(Real background_xs);
      Real                  get_xs_data(int mt_no, Real ene_val);
      void                  get_xs_data(int mt_no, vector<Real>& ene_vec, vector<Real>& xs_vec);
      void                  get_mt4_data(vector<Real>& ene_vec, vector<Real>& xs_vec);
      void                  get_chi_data(vector<Real>& ene_vec, vector<Real>& xs_vec);

////////////////////////////////////////////////////////////////////////////////////////////////////

      //Setter
      void set_mcnpx_mode_flg(Integer int_val);
      void set_mat(Integer int_val);
      void set_temp(Real real_val);
      void set_zi_vec(vector<Integer> int_vec);
      void set_awr_vec(vector<Real> real_vec);
      void set_sub_lib_part(Integer int_val);
      void set_sub_lib_type(Integer int_val);
      void set_ene_max(Real real_val);

      void set_union_ene_grid(vector<Real> real_vec);
      void set_gamma_product_xs(vector<Real> real_vec);
      void set_photon_product_xs(vector<Real> real_vec);

      void set_particle_production_data(vector<vector<Integer> > int_vec);
      void set_particle_production_ene_data(vector<Real> real_vec);

      void set_photon_prod_yield_coef_direct(vector<vector<Real> > real_vec);
      void set_photon_prod_yield_coef_given(vector<vector<Real> > real_vec);

      void set_photon_xs_ene_min(vector<Real> real_vec);
      void set_photon_prod_discon_ene_data(vector<Real> real_vec);

      void set_equal_prob_data_ini(vector<vector<Real> > real_vec);

      void set_aw0(Real real_val); 
      void set_tz(Real real_val); 
      void set_title_data(vector<string> str_vec);
      void set_discriptive_data(string str_data);

      void set_ntr(int int_val);
      void set_nr(int int_val);
      void set_mtntr(int int_val);
      void set_mtnr(int int_val);
      void set_nu_bar_repr_flg(Integer int_val);
      void set_nu_d_bar_repr_flg(Integer int_val);
      void set_nu_p_bar_repr_flg(Integer int_val);
      void set_nu_int_data(vector<Integer> int_vec);
      void set_nu_range_data(vector<Integer> int_vec);
      void set_nu_d_int_data(vector<Integer> int_vec);
      void set_nu_d_range_data(vector<Integer> int_vec);
      void set_nu_p_int_data(vector<Integer> int_vec);
      void set_nu_p_range_data(vector<Integer> int_vec);
      void set_nu_data(vector<Real> real_vec);
      void set_nu_ene_data(vector<Real> real_vec);
      void set_nu_d_data(vector<Real> real_vec);
      void set_nu_d_ene_data(vector<Real> real_vec);
      void set_nu_p_data(vector<Real> real_vec);
      void set_nu_p_ene_data(vector<Real> real_vec);
      void set_nu_d_decay_constant(vector<Real> real_vec);

      void set_react_type_list(vector<Integer> int_vec);
      void set_react_type_flg(vector<Integer> int_vec);
      void set_react_type_ene_sta(vector<Integer> int_vec);
      void set_react_q_value(vector<Real> real_vec);
      void set_react_xs_tot(vector<Real> real_vec);
      void set_react_xs_cap(vector<Real> real_vec);
      void set_react_xs_sc(vector<Real> real_vec);
      void set_react_xs_heat(vector<Real> real_vec);
      void set_react_xs(vector<vector<Real> > real_vec);

      void set_angular_distr_type_flg(vector<Integer> int_vec);
      void set_angular_distr_int_data(vector<vector<Integer> > int_vec);
      void set_angular_distr_ene_data(vector<vector<Real> > real_vec);
      void set_angular_distr_cos_data(vector<vector<vector<Real> > > real_vec);
      void set_angular_distr_data(vector<vector<vector<Real> > > real_vec);
      void set_angular_distr_data_integ(vector<vector<vector<Real> > > real_vec);

      void set_ene_distr_ene_repr_flg(vector<vector<Integer> > int_vec);
      void set_ene_distr_xs_part_int_data(vector<vector<vector<Integer> > > int_vec);
      void set_ene_distr_xs_part_range_data(vector<vector<vector<Integer> > > int_vec);
      void set_ene_distr_xs_part_ene_data(vector<vector<vector<Real> > > real_vec);
      void set_ene_distr_xs_part_data(vector<vector<vector<Real> > > real_vec);
      void set_ene_distr_q_coef(vector<vector<Real> > real_vec);
      void set_ene_distr_mass_coef(vector<vector<Real> > real_vec);
      void set_ene_distr_ene_in_int_data(vector<vector<vector<Integer> > > int_vec);
      void set_ene_distr_ene_in_range_data(vector<vector<vector<Integer> > > int_vec);
      void set_ene_distr_ene_in_data(vector<vector<vector<Real> > > real_vec);
      void set_ene_distr_ene_out_int_data(vector<vector<vector<Integer> > > int_vec);
      void set_ene_distr_ene_out_ene_data(vector<vector<vector<vector<Real> > > > real_vec);
      void set_ene_distr_ene_out_data(vector<vector<vector<vector<Real> > > > real_vec);
      void set_ene_distr_ene_out_data_integ(vector<vector<vector<vector<Real> > > > real_vec);
      void set_ene_distr_upper_ene_limit(vector<vector<Real> > real_vec);
      void set_ene_distr_temp_eff_int_data(vector<vector<vector<Integer> > > int_vec);
      void set_ene_distr_temp_eff_range_data(vector<vector<vector<Integer> > > int_vec);
      void set_ene_distr_watt_a_int_data(vector<vector<vector<Integer> > > int_vec);
      void set_ene_distr_watt_a_range_data(vector<vector<vector<Integer> > > int_vec);
      void set_ene_distr_watt_b_int_data(vector<vector<vector<Integer> > > int_vec);
      void set_ene_distr_watt_b_range_data(vector<vector<vector<Integer> > > int_vec);
      void set_ene_distr_temp_eff_ene_data(vector<vector<vector<Real> > > real_vec);
      void set_ene_distr_temp_eff_data(vector<vector<vector<Real> > > real_vec);
      void set_ene_distr_watt_a_ene_data(vector<vector<vector<Real> > > real_vec);
      void set_ene_distr_watt_a_data(vector<vector<vector<Real> > > real_vec);
      void set_ene_distr_watt_b_ene_data(vector<vector<vector<Real> > > real_vec);
      void set_ene_distr_watt_b_data(vector<vector<vector<Real> > > real_vec);

      void set_prod_yield_tot_int_data(vector<vector<Integer> > int_vec);
      void set_prod_yield_tot_range_data(vector<vector<Integer> > int_vec);
      void set_prod_yield_tot_ene_data(vector<vector<Real> > real_vec);
      void set_prod_yield_tot_data(vector<vector<Real> > real_vec);
      void set_prod_distr_func_flg(vector<vector<Integer> > int_vec);
      void set_prod_distr_n_body_mass(vector<vector<Real> > real_vec);
      void set_prod_distr_prob_data_no(vector<vector<Integer> > int_vec);
      void set_prod_distr_n_body_particle_no(vector<vector<Integer> > int_vec);
      void set_prod_distr_prob_ene_in_int_data(vector<vector<vector<Integer> > > int_vec);
      void set_prod_distr_prob_ene_in_range_data(vector<vector<vector<Integer> > > int_vec);
      void set_prod_distr_prob_ene_out_int_data(vector<vector<vector<Integer> > > int_vec);
      void set_prod_distr_prob_ene_in_data(vector<vector<vector<Real> > > real_vec);
      void set_prod_distr_prob_mu_int_data(vector<vector<vector<vector<Integer> > > > int_vec);
      void set_prod_distr_prob_mu_range_data(vector<vector<vector<vector<Integer> > > > int_vec);
      void set_prod_distr_prob_mu_data(vector<vector<vector<vector<Real> > > > real_vec);
      void set_prod_distr_prob_mu_data_integ(vector<vector<vector<vector<Real> > > > real_vec);
      void set_prod_distr_prob_data(vector<vector<vector<vector<Real> > > > real_vec);
      void set_prod_distr_prob_data_integ(vector<vector<vector<vector<Real> > > > real_vec);
      void set_prod_distr_prob_ene_out_data(vector<vector<vector<vector<Real> > > > real_vec);
      void set_prod_distr_prob_coef_a(vector<vector<vector<vector<Real> > > > real_vec);
      void set_prod_distr_prob_coef_b(vector<vector<vector<vector<Real> > > > real_vec);
      void set_prod_distr_prob_int_vec(vector<vector<vector<vector<vector<Integer> > > > > int_vec);
      void set_prod_distr_prob_range_vec(vector<vector<vector<vector<vector<Integer> > > > > int_vec);
      void set_prod_distr_prob_mu_vec(vector<vector<vector<vector<vector<Real> > > > > real_vec);
      void set_prod_distr_prob_ene_out_vec(vector<vector<vector<vector<vector<Real> > > > > real_vec);
      void set_prod_distr_prob_vec(vector<vector<vector<vector<vector<Real> > > > > real_vec);
      void set_prod_distr_prob_vec_integ(vector<vector<vector<vector<vector<Real> > > > > real_vec);

      void set_unreso_prob_tab_int_data(Integer int_val);
      void set_unreso_prob_tab_inela_comp_flg(Integer int_val);
      void set_unreso_prob_tab_abs_comp_flg(Integer int_val);
      void set_unreso_prob_tab_self_shielding_flg(Integer int_val);
      void set_unreso_prob_tab_ene(vector<Real> real_vec);
      void set_unreso_prob_tab_heat(vector<vector<Real> > real_vec);
      void set_unreso_prob_tab_sample_no(vector<vector<Real> > real_vec);
      void set_unreso_prob_tab_table(vector<vector<vector<Real> > > real_vec);

      void set_nu_d_ene_min(vector<Real> real_vec);
      void set_nu_d_ene_max(vector<Real> real_vec);
      void set_nu_d_xs_part_int_data(vector<vector<Integer> > int_vec);
      void set_nu_d_xs_part_range_data(vector<vector<Integer> > int_vec);
      void set_nu_d_xs_part_ene_data(vector<vector<Real> > real_vec);
      void set_nu_d_xs_part_data(vector<vector<Real> > real_vec);
      void set_nu_d_ene_in_int_data(vector<vector<Integer> > int_vec);
      void set_nu_d_ene_in_range_data(vector<vector<Integer> > int_vec);
      void set_nu_d_ene_out_int_data(vector<vector<Integer> > int_vec);
      void set_nu_d_ene_in_data(vector<vector<Real> > real_vec);
      void set_nu_d_ene_out_data(vector<vector<vector<Real> > > real_vec);
      void set_nu_d_ene_distr_data(vector<vector<vector<Real> > > real_vec);
      void set_nu_d_ene_distr_data_integ(vector<vector<vector<Real> > > real_vec);

      void set_photon_prod_file_no(vector<Integer> int_vec);
      void set_photon_prod_reaction_type(vector<Integer> int_vec);
      void set_photon_prod_reaction_type_all(vector<Integer> int_vec);
      void set_photon_prod_reaction_type_without_xs(vector<Integer> int_vec);
      void set_photon_prod_binding_ene(vector<Real> real_vec);
      void set_photon_prod_multiplicity_int_data(vector<vector<Integer> > int_vec);
      void set_photon_prod_multiplicity_range_data(vector<vector<Integer> > int_vec);
      void set_photon_prod_multiplicity_ene_data(vector<vector<Real> > real_vec);
      void set_photon_prod_multiplicity_data(vector<vector<Real> > real_vec);
      void set_photon_prod_xs_ene_no(vector<int> int_vec);
      void set_photon_prod_xs_non_zero_pos(vector<vector<int> > int_vec);
      void set_photon_prod_xs_data(vector<vector<Real> > real_vec);
      void set_photon_prod_distr_int_data(vector<vector<Integer> > int_vec);
      void set_photon_prod_distr_range_data(vector<vector<Integer> > int_vec);
      void set_photon_prod_distr_ene_data(vector<vector<Real> > real_vec);
      void set_photon_prod_distr_data(vector<vector<Real> > real_vec);

      void set_photon_angular_distr_ene_data(vector<vector<Real> > real_vec);
      void set_photon_angular_distr_prob_cos_data(vector<vector<vector<Real> > > real_vec);

      void set_photon_energy_distr_flg(vector<Integer> int_vec);
      void set_photon_energy_distr_ene_flg(vector<Integer> int_vec);
      void set_photon_energy_distr_binding_ene_data(vector<Real> real_vec);
      void set_photon_energy_distr_int_data(vector<vector<Integer> > int_vec);
      void set_photon_energy_distr_range_data(vector<vector<Integer> > int_vec);
      void set_photon_energy_distr_ene_data(vector<vector<Real> > real_vec);
      void set_photon_energy_distr_prob_data(vector<vector<Real> > real_vec);
      void set_photon_energy_distr_ene_in_int_data(vector<vector<Integer> > int_vec);
      void set_photon_energy_distr_ene_in_range_data(vector<vector<Integer> > int_vec);
      void set_photon_energy_distr_ene_in_data(vector<vector<Real> > real_vec);
      void set_photon_energy_distr_weight_int_data(vector<vector<Integer> > int_vec);
      void set_photon_energy_distr_weight_ene_data(vector<vector<vector<Real> > > real_vec);
      void set_photon_energy_distr_weight_data(vector<vector<vector<Real> > > real_vec);
      void set_photon_energy_distr_weight_data_integ(vector<vector<vector<Real> > > real_vec);
      void set_photon_energy_distr_gamma_mass_product(vector<Real> real_vec);

      void set_particle_prod_flg(vector<Integer> int_vec);
      void set_particle_prod_count(vector<Integer> int_vec);
      void set_particle_prod_ene_sta(vector<Integer> int_vec);
      void set_particle_prod_ene_no(vector<Integer> int_vec);
      void set_particle_prod_file_no(vector<vector<Integer> > int_vec);
      void set_particle_prod_frame_flg(vector<vector<Integer> > int_vec);
      void set_particle_prod_reaction_type(vector<vector<Integer> > int_vec);
      void set_particle_prod_reaction_type_all(vector<vector<Integer> > int_vec);
      void set_particle_prod_xs(vector<vector<Real> > real_vec);
      void set_particle_prod_heat(vector<vector<Real> > real_vec);
      void set_particle_prod_distr_int_data(vector<vector<vector<Integer> > > int_vec);
      void set_particle_prod_distr_range_data(vector<vector<vector<Integer> > > int_vec);
      void set_particle_prod_distr_ene_data(vector<vector<vector<Real> > > real_vec);
      void set_particle_prod_distr_data(vector<vector<vector<Real> > > real_vec);
      void set_particle_prod_angular_int_data(vector<vector<vector<Integer> > > int_vec);
      void set_particle_prod_angular_ene_data(vector<vector<vector<Real> > > real_vec);
      void set_particle_prod_angular_cos_data(vector<vector<vector<vector<Real> > > > real_vec);
      void set_particle_prod_angular_distr_data(vector<vector<vector<vector<Real> > > > real_vec);
      void set_particle_prod_angular_distr_data_integ(vector<vector<vector<vector<Real> > > > real_vec);

      void set_particle_prod_ene_flg(vector<vector<Integer> > int_vec);
      void set_particle_prod_q_value(vector<vector<Real> > real_vec);
      void set_particle_prod_mass_coef(vector<vector<Real> > real_vec);
      void set_particle_prod_ene_int_data(vector<vector<vector<Integer> > > int_vec);
      void set_particle_prod_ene_range_data(vector<vector<vector<Integer> > > int_vec);
      void set_particle_prod_ene_data(vector<vector<vector<Real> > > real_vec);
      void set_particle_prod_ene_prob_data(vector<vector<vector<Real> > > real_vec);

      //For distr_func_flg = 1 : second energy, distr_func_flg = 7 : angle (mu)
      void set_particle_prod_ene_in_int_data(vector<vector<vector<Integer> > > int_vec);
      void set_particle_prod_ene_in_range_data(vector<vector<vector<Integer> > > int_vec);
      void set_particle_prod_ene_in_data(vector<vector<vector<Real> > > real_vec);
      void set_particle_prod_a_int_data(vector<vector<vector<Integer> > > int_vec);
      void set_particle_prod_a_data(vector<vector<vector<vector<Real> > > > real_vec);
      void set_particle_prod_a_distr_data(vector<vector<vector<vector<Real> > > > real_vec);
      void set_particle_prod_a_distr_data_integ(vector<vector<vector<vector<Real> > > > real_vec);
      void set_particle_prod_ene_out_coef_a(vector<vector<vector<vector<Real> > > > real_vec);
      void set_particle_prod_ene_out_coef_b(vector<vector<vector<vector<Real> > > > real_vec);

      //For distr_func_flg = 1 : angle (mu), distr_func_flg = 7 : second energy
      void set_particle_prod_b_int_data(vector<vector<vector<vector<Integer> > > > int_vec);
      void set_particle_prod_b_data(vector<vector<vector<vector<vector<Real> > > > > real_vec);
      void set_particle_prod_b_prob_data(vector<vector<vector<vector<vector<Real> > > > > real_vec);
      void set_particle_prod_b_prob_data_integ(vector<vector<vector<vector<vector<Real> > > > > real_vec);


      //For pointer data
      void set_len2(int int_val);
      void set_izaid(int int_val);
      void set_nes(int int_val);
      void set_ntrp(int int_val);
      void set_ntype(int int_val);
      void set_ndnf(int int_val);
      void set_esz(int int_val);
      void set_nu(int int_val);
      void set_mtr(int int_val);
      void set_lqr(int int_val);
      void set_tyr(int int_val);
      void set_lsig(int int_val);
      void set_sig(int int_val);
      void set_land(int int_val);
      void set_andi(int int_val);
      void set_ldlw(int int_val);
      void set_dlw(int int_val);
      void set_gpd(int int_val);
      void set_mtrp(int int_val);
      void set_lsigp(int int_val);
      void set_sigp(int int_val);
      void set_landp(int int_val);
      void set_andp(int int_val);
      void set_ldlwp(int int_val);
      void set_dlwp(int int_val);
      void set_yp(int int_val);
      void set_fis(int int_val);
      void set_endi(int int_val);
      void set_iurpt(int int_val);
      void set_nud(int int_val);
      void set_dndat(int int_val);
      void set_ldnd(int int_val);
      void set_dnd(int int_val);
      void set_ptype(int int_val);
      void set_ntro(int int_val);
      void set_ploct(int int_val);
      
      void set_ene_distr_pointer(vector<int> int_vec);
      void set_nu_d_pointer(vector<int> int_vec);
      void set_photon_prod_pointer(vector<int> int_vec);
      void set_photon_angular_pointer(vector<int> int_vec);
      void set_photon_ene_pointer(vector<int> int_vec);
      void set_photon_ene_distr_pointer(vector<int> int_vec);
      void set_angular_distr_pointer(vector<vector<int> > int_vec);
      void set_ene_distr_ene_repr_end_pointer(vector<vector<int> > int_vec);
      void set_ene_distr_ene_repr_pointer(vector<vector<int> > int_vec);
      void set_nu_d_ene_in_pointer(vector<vector<int> > int_vec);
      void set_photon_angular_ene_pointer(vector<vector<int> > int_vec);
      void set_photon_ene_weight_pointer(vector<vector<int> > int_vec);
      void set_particle_prod_pointer(vector<vector<int> > int_vec);
      void set_particle_prod_distr_pointer(vector<vector<int> > int_vec);
      void set_particle_prod_angular_pointer(vector<vector<int> > int_vec);
      void set_particle_prod_ene_pointer(vector<vector<int> > int_vec);
      void set_particle_prod_ene_in_pointer(vector<vector<int> > int_vec);
      void set_ene_distr_ene_in_pointer(vector<vector<vector<int> > > int_vec);
      void set_particle_prod_angular_ene_pointer(vector<vector<vector<int> > > int_vec);
      void set_particle_prod_a_pointer(vector<vector<vector<int> > > int_vec);
      void set_ene_distr_ene_out_pointer(vector<vector<vector<vector<int> > > > int_vec);
      void set_particle_prod_b_pointer(vector<vector<vector<vector<int> > > > int_vec);

////////////////////////////////////////////////////////////////////////////////////////////////////

      //Getter
      Integer get_mcnpx_mode_flg();
      Integer get_mat();
      Real    get_temp();
      Real    get_temp_ev();
      Real    get_temp_kelvin();

      vector<Integer> get_zi_vec();
      vector<Real>    get_awr_vec();
      
      Integer get_sub_lib_part();
      Integer get_sub_lib_type();
      Real    get_ene_max();

      vector<Real>             get_union_ene_grid();
      vector<Real>             get_gamma_product_xs();
      vector<Real>             get_photon_product_xs();

      vector<vector<Integer> > get_particle_production_data();
      vector<Real>             get_particle_production_ene_data();

      vector<vector<Real> >    get_photon_prod_yield_coef_direct();
      vector<vector<Real> >    get_photon_prod_yield_coef_given();

      vector<Real>             get_photon_xs_ene_min();
      vector<Real>             get_photon_prod_discon_ene_data();

      vector<vector<Real> >    get_equal_prob_data_ini();

      Real            get_aw0(); 
      Real            get_tz(); 
      vector<string>  get_title_data();
      string          get_discriptive_data();

      int             get_ntr();
      int             get_nr();
      int             get_mtntr();
      int             get_mtnr();
      Integer         get_nu_bar_repr_flg();
      Integer         get_nu_d_bar_repr_flg();
      Integer         get_nu_p_bar_repr_flg();
      vector<Integer> get_nu_int_data();
      vector<Integer> get_nu_range_data();
      vector<Integer> get_nu_d_int_data();
      vector<Integer> get_nu_d_range_data();
      vector<Integer> get_nu_p_int_data();
      vector<Integer> get_nu_p_range_data();
      vector<Real>    get_nu_data();
      vector<Real>    get_nu_ene_data();
      vector<Real>    get_nu_d_data();
      vector<Real>    get_nu_d_ene_data();
      vector<Real>    get_nu_p_data();
      vector<Real>    get_nu_p_ene_data();
      vector<Real>    get_nu_d_decay_constant();

      vector<Integer>       get_react_type_list();
      vector<Integer>       get_react_type_flg();
      vector<Integer>       get_react_type_ene_sta();
      vector<Real>          get_react_q_value();
      vector<Real>          get_react_xs_tot();
      vector<Real>          get_react_xs_cap();
      vector<Real>          get_react_xs_sc();
      vector<Real>          get_react_xs_heat();
      vector<vector<Real> > get_react_xs();

      vector<Integer>                get_angular_distr_type_flg();
      vector<vector<Integer> >       get_angular_distr_int_data();
      vector<vector<Real> >          get_angular_distr_ene_data();
      vector<vector<vector<Real> > > get_angular_distr_cos_data();
      vector<vector<vector<Real> > > get_angular_distr_data();
      vector<vector<vector<Real> > > get_angular_distr_data_integ();

      vector<vector<Integer> >                get_ene_distr_ene_repr_flg();
      vector<vector<vector<Integer> > >       get_ene_distr_xs_part_int_data();
      vector<vector<vector<Integer> > >       get_ene_distr_xs_part_range_data();
      vector<vector<vector<Real> > >          get_ene_distr_xs_part_ene_data();
      vector<vector<vector<Real> > >          get_ene_distr_xs_part_data();
      vector<vector<Real> >                   get_ene_distr_q_coef();
      vector<vector<Real> >                   get_ene_distr_mass_coef();
      vector<vector<vector<Integer> > >       get_ene_distr_ene_in_int_data();
      vector<vector<vector<Integer> > >       get_ene_distr_ene_in_range_data();
      vector<vector<vector<Real> > >          get_ene_distr_ene_in_data();
      vector<vector<vector<Integer> > >       get_ene_distr_ene_out_int_data();
      vector<vector<vector<vector<Real> > > > get_ene_distr_ene_out_ene_data();
      vector<vector<vector<vector<Real> > > > get_ene_distr_ene_out_data();
      vector<vector<vector<vector<Real> > > > get_ene_distr_ene_out_data_integ();
      vector<vector<Real> >                   get_ene_distr_upper_ene_limit();
      vector<vector<vector<Integer> > >       get_ene_distr_temp_eff_int_data();
      vector<vector<vector<Integer> > >       get_ene_distr_temp_eff_range_data();
      vector<vector<vector<Integer> > >       get_ene_distr_watt_a_int_data();
      vector<vector<vector<Integer> > >       get_ene_distr_watt_a_range_data();
      vector<vector<vector<Integer> > >       get_ene_distr_watt_b_int_data();
      vector<vector<vector<Integer> > >       get_ene_distr_watt_b_range_data();
      vector<vector<vector<Real> > >          get_ene_distr_temp_eff_ene_data();
      vector<vector<vector<Real> > >          get_ene_distr_temp_eff_data();
      vector<vector<vector<Real> > >          get_ene_distr_watt_a_ene_data();
      vector<vector<vector<Real> > >          get_ene_distr_watt_a_data();
      vector<vector<vector<Real> > >          get_ene_distr_watt_b_ene_data();
      vector<vector<vector<Real> > >          get_ene_distr_watt_b_data();

      vector<vector<Integer> >                            get_prod_yield_tot_int_data();
      vector<vector<Integer> >                            get_prod_yield_tot_range_data();
      vector<vector<Real> >                               get_prod_yield_tot_ene_data();
      vector<vector<Real> >                               get_prod_yield_tot_data();
      vector<vector<Integer> >                            get_prod_distr_func_flg();
      vector<vector<Real> >                               get_prod_distr_n_body_mass();
      vector<vector<Integer> >                            get_prod_distr_prob_data_no();
      vector<vector<Integer> >                            get_prod_distr_n_body_particle_no();
      vector<vector<vector<Integer> > >                   get_prod_distr_prob_ene_in_int_data();
      vector<vector<vector<Integer> > >                   get_prod_distr_prob_ene_in_range_data();
      vector<vector<vector<Integer> > >                   get_prod_distr_prob_ene_out_int_data();
      vector<vector<vector<Real> > >                      get_prod_distr_prob_ene_in_data();
      vector<vector<vector<vector<Integer> > > >          get_prod_distr_prob_mu_int_data();
      vector<vector<vector<vector<Integer> > > >          get_prod_distr_prob_mu_range_data();
      vector<vector<vector<vector<Real> > > >             get_prod_distr_prob_mu_data();
      vector<vector<vector<vector<Real> > > >             get_prod_distr_prob_mu_data_integ();
      vector<vector<vector<vector<Real> > > >             get_prod_distr_prob_data();
      vector<vector<vector<vector<Real> > > >             get_prod_distr_prob_data_integ();
      vector<vector<vector<vector<Real> > > >             get_prod_distr_prob_ene_out_data();
      vector<vector<vector<vector<Real> > > >             get_prod_distr_prob_coef_a();
      vector<vector<vector<vector<Real> > > >             get_prod_distr_prob_coef_b();
      vector<vector<vector<vector<vector<Integer> > > > > get_prod_distr_prob_int_vec();
      vector<vector<vector<vector<vector<Integer> > > > > get_prod_distr_prob_range_vec();
      vector<vector<vector<vector<vector<Real> > > > >    get_prod_distr_prob_mu_vec();
      vector<vector<vector<vector<vector<Real> > > > >    get_prod_distr_prob_ene_out_vec();
      vector<vector<vector<vector<vector<Real> > > > >    get_prod_distr_prob_vec();
      vector<vector<vector<vector<vector<Real> > > > >    get_prod_distr_prob_vec_integ();

      Integer                        get_unreso_prob_tab_int_data();
      Integer                        get_unreso_prob_tab_inela_comp_flg();
      Integer                        get_unreso_prob_tab_abs_comp_flg();
      Integer                        get_unreso_prob_tab_self_shielding_flg();
      vector<Real>                   get_unreso_prob_tab_ene();
      vector<vector<Real> >          get_unreso_prob_tab_heat();
      vector<vector<Real> >          get_unreso_prob_tab_sample_no();
      vector<vector<vector<Real> > > get_unreso_prob_tab_table();

      vector<Real>                   get_nu_d_ene_min();
      vector<Real>                   get_nu_d_ene_max();
      vector<vector<Integer> >       get_nu_d_xs_part_int_data();
      vector<vector<Integer> >       get_nu_d_xs_part_range_data();
      vector<vector<Real> >          get_nu_d_xs_part_ene_data();
      vector<vector<Real> >          get_nu_d_xs_part_data();
      vector<vector<Integer> >       get_nu_d_ene_in_int_data();
      vector<vector<Integer> >       get_nu_d_ene_in_range_data();
      vector<vector<Integer> >       get_nu_d_ene_out_int_data();
      vector<vector<Real> >          get_nu_d_ene_in_data();
      vector<vector<vector<Real> > > get_nu_d_ene_out_data();
      vector<vector<vector<Real> > > get_nu_d_ene_distr_data();
      vector<vector<vector<Real> > > get_nu_d_ene_distr_data_integ();

      vector<Integer>          get_photon_prod_file_no();
      vector<Integer>          get_photon_prod_reaction_type();
      vector<Integer>          get_photon_prod_reaction_type_all();
      vector<Integer>          get_photon_prod_reaction_type_without_xs();
      vector<Real>             get_photon_prod_binding_ene();
      vector<vector<Integer> > get_photon_prod_multiplicity_int_data();
      vector<vector<Integer> > get_photon_prod_multiplicity_range_data();
      vector<vector<Real> >    get_photon_prod_multiplicity_ene_data();
      vector<vector<Real> >    get_photon_prod_multiplicity_data();
      vector<int>              get_photon_prod_xs_ene_no();
      vector<vector<int> >     get_photon_prod_xs_non_zero_pos();
      vector<vector<Real> >    get_photon_prod_xs_data();
      vector<vector<Integer> > get_photon_prod_distr_int_data();
      vector<vector<Integer> > get_photon_prod_distr_range_data();
      vector<vector<Real> >    get_photon_prod_distr_ene_data();
      vector<vector<Real> >    get_photon_prod_distr_data();

      vector<vector<Real> >          get_photon_angular_distr_ene_data();
      vector<vector<vector<Real> > > get_photon_angular_distr_prob_cos_data();

      vector<Integer>                   get_photon_energy_distr_flg();
      vector<Integer>                   get_photon_energy_distr_ene_flg();
      vector<Real>                      get_photon_energy_distr_binding_ene_data();
      vector<vector<Integer> >          get_photon_energy_distr_int_data();
      vector<vector<Integer> >          get_photon_energy_distr_range_data();
      vector<vector<Real> >             get_photon_energy_distr_ene_data();
      vector<vector<Real> >             get_photon_energy_distr_prob_data();
      vector<vector<Integer> >          get_photon_energy_distr_ene_in_int_data();
      vector<vector<Integer> >          get_photon_energy_distr_ene_in_range_data();
      vector<vector<Real> >             get_photon_energy_distr_ene_in_data();
      vector<vector<Integer> >          get_photon_energy_distr_weight_int_data();
      vector<vector<vector<Real> > >    get_photon_energy_distr_weight_ene_data();
      vector<vector<vector<Real> > >    get_photon_energy_distr_weight_data();
      vector<vector<vector<Real> > >    get_photon_energy_distr_weight_data_integ();
      vector<Real>                      get_photon_energy_distr_gamma_mass_product();

      vector<Integer>                          get_particle_prod_flg();
      vector<Integer>                          get_particle_prod_count();
      vector<Integer>                          get_particle_prod_ene_sta();
      vector<Integer>                          get_particle_prod_ene_no();
      vector<vector<Integer> >                 get_particle_prod_file_no();
      vector<vector<Integer> >                 get_particle_prod_frame_flg();
      vector<vector<Integer> >                 get_particle_prod_reaction_type();
      vector<vector<Integer> >                 get_particle_prod_reaction_type_all();
      vector<vector<Real> >                    get_particle_prod_xs();
      vector<vector<Real> >                    get_particle_prod_heat();
      vector<vector<vector<Integer> > >        get_particle_prod_distr_int_data();
      vector<vector<vector<Integer> > >        get_particle_prod_distr_range_data();
      vector<vector<vector<Real> > >           get_particle_prod_distr_ene_data();
      vector<vector<vector<Real> > >           get_particle_prod_distr_data();
      vector<vector<vector<Integer> > >        get_particle_prod_angular_int_data();
      vector<vector<vector<Real> > >           get_particle_prod_angular_ene_data();
      vector<vector<vector<vector<Real> > > >  get_particle_prod_angular_cos_data();
      vector<vector<vector<vector<Real> > > >  get_particle_prod_angular_distr_data();
      vector<vector<vector<vector<Real> > > >  get_particle_prod_angular_distr_data_integ();

      vector<vector<Integer> >          get_particle_prod_ene_flg();
      vector<vector<Real> >             get_particle_prod_q_value();
      vector<vector<Real> >             get_particle_prod_mass_coef();
      vector<vector<vector<Integer> > > get_particle_prod_ene_int_data();
      vector<vector<vector<Integer> > > get_particle_prod_ene_range_data();
      vector<vector<vector<Real> > >    get_particle_prod_ene_data();
      vector<vector<vector<Real> > >    get_particle_prod_ene_prob_data();

      //For distr_func_flg = 1 : second energy, distr_func_flg = 7 : angle (mu)
      vector<vector<vector<Integer> > >          get_particle_prod_ene_in_int_data();
      vector<vector<vector<Integer> > >          get_particle_prod_ene_in_range_data();
      vector<vector<vector<Real> > >             get_particle_prod_ene_in_data();
      vector<vector<vector<Integer> > >          get_particle_prod_a_int_data();
      vector<vector<vector<vector<Real> > > >    get_particle_prod_a_data();
      vector<vector<vector<vector<Real> > > >    get_particle_prod_a_distr_data();
      vector<vector<vector<vector<Real> > > >    get_particle_prod_a_distr_data_integ();
      vector<vector<vector<vector<Real> > > >    get_particle_prod_ene_out_coef_a();
      vector<vector<vector<vector<Real> > > >    get_particle_prod_ene_out_coef_b();

      //For distr_func_flg = 1 : angle (mu), distr_func_flg = 7 : second energy
      vector<vector<vector<vector<Integer> > > >       get_particle_prod_b_int_data();
      vector<vector<vector<vector<vector<Real> > > > > get_particle_prod_b_data();
      vector<vector<vector<vector<vector<Real> > > > > get_particle_prod_b_prob_data();
      vector<vector<vector<vector<vector<Real> > > > > get_particle_prod_b_prob_data_integ();


      //For pointer data
      int         get_len2();
      int         get_izaid();
      int         get_nes();
      int         get_ntrp();
      int         get_ntype();
      int         get_ndnf();
      int         get_esz();
      int         get_nu();
      int         get_mtr();
      int         get_lqr();
      int         get_tyr();
      int         get_lsig();
      int         get_sig();
      int         get_land();
      int         get_andi();
      int         get_ldlw();
      int         get_dlw();
      int         get_gpd();
      int         get_mtrp();
      int         get_lsigp();
      int         get_sigp();
      int         get_landp();
      int         get_andp();
      int         get_ldlwp();
      int         get_dlwp();
      int         get_yp();
      int         get_fis();
      int         get_endi();
      int         get_iurpt();
      int         get_nud();
      int         get_dndat();
      int         get_ldnd();
      int         get_dnd();
      int         get_ptype();
      int         get_ntro();
      int         get_ploct();
      
      vector<int>                            get_ene_distr_pointer();
      vector<int>                            get_nu_d_pointer();
      vector<int>                            get_photon_prod_pointer();
      vector<int>                            get_photon_angular_pointer();
      vector<int>                            get_photon_ene_pointer();
      vector<int>                            get_photon_ene_distr_pointer();
      vector<vector<int> >                   get_angular_distr_pointer();
      vector<vector<int> >                   get_ene_distr_ene_repr_end_pointer();
      vector<vector<int> >                   get_ene_distr_ene_repr_pointer();
      vector<vector<int> >                   get_nu_d_ene_in_pointer();
      vector<vector<int> >                   get_photon_angular_ene_pointer();
      vector<vector<int> >                   get_photon_ene_weight_pointer();
      vector<vector<int> >                   get_particle_prod_pointer();
      vector<vector<int> >                   get_particle_prod_distr_pointer();
      vector<vector<int> >                   get_particle_prod_angular_pointer();
      vector<vector<int> >                   get_particle_prod_ene_pointer();
      vector<vector<int> >                   get_particle_prod_ene_in_pointer();
      vector<vector<vector<int> > >          get_ene_distr_ene_in_pointer();
      vector<vector<vector<int> > >          get_particle_prod_angular_ene_pointer();
      vector<vector<vector<int> > >          get_particle_prod_a_pointer();
      vector<vector<vector<vector<int> > > > get_ene_distr_ene_out_pointer();
      vector<vector<vector<vector<int> > > > get_particle_prod_b_pointer();
  };
}

#endif //FAST_ACE_DATA_OBJECT_H
