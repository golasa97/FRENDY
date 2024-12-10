#ifndef FAST_ACE_DATA_GENERATOR_H
#define FAST_ACE_DATA_GENERATOR_H

#include <boost/math/special_functions/expint.hpp>
#include <boost/math/special_functions/gamma.hpp>

#include "NuclearDataUtils/NuclearDataObject.hpp"
#include "CommonUtils/VectorClearer.hpp"
#include "CommonUtils/DigitAdjuster.hpp"
#include "CommonUtils/TabInterpolator.hpp"
#include "CommonUtils/TabAdjuster.hpp"
#include "CommonUtils/TimeUtils.hpp"
#include "CommonUtils/VectorSizeChecker.hpp"
#include "MathUtils/MathUtils.hpp"
#include "TabUtils/LinearizeTabData.hpp"
#include "TabUtils/IntegrateTabData.hpp"
#include "ContinuousEnergyXSUtils/AceDataObject/FastAceDataObject.hpp"

namespace frendy
{
  class FastAceDataGenerator
  {
    private:
      frendy::ErrorManager      err_obj;
      frendy::VectorClearer     clr_obj;
      frendy::TabInterpolator   ti_obj;
      frendy::TabAdjuster       ta_obj;
      frendy::DigitAdjuster     digit_obj;
      frendy::VectorSizeChecker vec_size_check_obj;
      frendy::TimeUtils         time_obj;
      frendy::MathUtils         math_obj;
      frendy::LinearizeTabData  lin_tab_obj;
      frendy::IntegrateTabData  integ_obj;

      static const int max_zi_awr_pair_no = 16;
      static const int thinning_ene_no    =  3;

      static const int particle_production_data_no       = 4;
      static const int particle_production_reaction_type = 0;
      static const int particle_production_sub_lib_no    = 1;
      static const int particle_production_file_no       = 2;
      static const int particle_production_type          = 3;

      static const int particle_production_ene_data_no   = 6;

      static const int equal_prob_bin_no           = 64;
      static const int bin_no                      = 32;

      Integer react_n_h1_min,  react_n_h1_max, react_n_h2_min, react_n_h2_max,
              react_n_h3_min,  react_n_h3_max, react_n_he3_min, react_n_he3_max,
              react_n_he4_min, react_n_he4_max, react_n_2n_min, react_n_2n_max;

      string class_name;

      int generate_mode_flg;

#ifdef DEBUG_MODE
  public:
#endif
      Real8 ene_lower_limit; //= 1.0E-5;
      Real8 ene_upper_limit; //= 2.0E+7;
      Real8 angle_err_def;   //= 1.0E-3;

      Integer gen_fast_data_flg, nucl_data_set_flg, mat_set_flg, temp_set_flg;

      //Calc data
      int                                              reaction_type_no_int;
      vector<Integer>                                  reaction_type_list;
      frendy::FissionDataContainer                     fis_data_obj;
      vector<frendy::CrossSectionDataContainer>        xs_data_obj_vec;
      vector<frendy::EnergyAngularDataContainer>       ene_angle_data_obj_vec;
      vector<frendy::ProductDistributionDataContainer> prod_distr_data_obj_vec;
      vector<frendy::PhotonDataContainer>              photon_data_obj_vec;

      vector<frendy::ProductDistributionDataContainer> prod_distr_data_obj_mod_photon_vec;

      Integer         mt_16_flg,  mt_19_flg, mt_455_flg, mt_103_flg, mt_104_flg, mt_105_flg,
                      mt_106_flg, mt_107_flg;
      Integer         mf_6_data_no, mf_12_data_no, mf_13_data_no, mf_15_data_no;
      Integer         photon_prod_no,   redundant_react_no;   //ngmt, nf12s
      vector<Integer> photon_prod_type, redundant_react_type; //gmt,  mf12s

      Integer sub_lib_part, sub_lib_type; //izai, nlib
      Real    ene_max;

      vector<Real>             union_ene_grid, gamma_product_xs, photon_product_xs;

      vector<vector<Integer> > particle_production_data;
      vector<Real>             particle_production_ene_data;

      vector<vector<Real> >    photon_prod_yield_coef_direct, photon_prod_yield_coef_given;

      vector<Real>             photon_xs_ene_min, photon_prod_discon_ene_data;

      vector<vector<Real> >    equal_prob_data_ini;

      //For ACE data
      Real           aw0,  tz;
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
      vector<vector<Real> >             particle_prod_xs, particle_prod_heat, particle_prod_xs_each;
      vector<Real>                      particle_prod_xs_each_emin;
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


      //Set data
      frendy::NuclearDataObject nucl_data_obj;

      Integer         mat, new_cummulative_angle_distr_flg, detailed_photon_flg;
      Real            temp;
      vector<Real>    thinning_ene;
      //Integer         thinning_ene_opt;

      Real            suffix_za_id;
      vector<Integer> zi_vec;
      vector<Real>    awr_vec;

      //For output
      Integer         mcnpx_mode_flg;
      string          discriptive_data;

      void set_general_data();
      void check_reaction_type();
      void check_mt_flg(int i, Integer react_val);
      void check_mf_flg(int i, Integer react_val);

      void    check_particle_production_xs(int i, Integer react_val);
      void    check_particle_production_prod_distr(int i, Integer react_val);
      Integer check_particle_production_data(vector<Integer> particle_prod_tmp);
      void    sort_particle_production();
      void    delete_overlap_particle_production();


      //For linearize number of neutrons per fission
      void linearize_number_of_neutrons_per_fission();


      //Convert photon transition probability arrays to photon yields.
      //Modify photon angular distribution data.
      //Modify product energy-angle distribution data (ProductDistributionDataContainer).
      void modify_photon_production_data();
      void check_photon_data_reaction_type_list();
      void adjust_photon_production_ene_data(int i);
      void adjust_photon_production_ene_data
             ( vector<Integer>&          tot_range, vector<Integer>&          tot_int,
               vector<Real>&             tot_ene,   vector<Real>&             tot_data,
               vector<vector<Integer> >& tab_range, vector<vector<Integer> >& tab_int,
               vector<vector<Real> >&    tab_ene,   vector<vector<Real> >&    tab_data);
      void modify_transition_probability_array(int i, Integer& react_type_pre, vector<Real>& ene_vec);
      void set_ene_data_for_transition_probability_array
             (int i, Integer& react_type_cur, Integer& react_type_pre,
              vector<Real>& ene_vec, Real8& xs_ene_min);
      void calc_photon_production_multiplicity_data( int ele_no, vector<Real>& ene_vec, Real& xs_ene_min,
                                                     frendy::PhotonDataContainer& photon_data_obj );
      void convert_calc_data_to_photon_data_obj
             ( frendy::PhotonDataContainer& photon_data_obj,
               Real& xs_ene_min, Real8& y_sum, vector<Real>& y_vec,
               vector<Real>& multi_ene_level, vector<Real>& multi_photon_ene );
      void modify_photon_angular_distribution_data_obj(int i);

      void modify_photon_production_data_in_product_distr_data();
      void copy_modified_photon_production_data_in_prod_distr_data
             (int i, int mod_data_no, vector<int>& mod_data_list, vector<Real>& e_gam_vec);


      //Set unionized energy grid and all energy grid in CrossSectionDataContainer is
      //changed to unionized energy grid.
      //Discontinuities are removed by add and move the energy grid at the discontinuity.
      void modify_xs_data();
      void modify_xs_data_total_ene_grid();
      void set_xs_data_union_ene_grid();
      void add_elastic_prod_distr_ene_grid();
      void adjust_ene_grid();
      void modify_xs_data_obj();
      Integer check_modify_xs_data_obj(int i);


      //Modify EnergyAngularDataContainer and ProductDistributionDataContainer.
      //Some table and list data are changed to equal probability bin (hisotgram).
      //In ProductDistributionDataContainer, the Legendre or tabulated data (LAW=1)
      //is converted to angle-energy form (LAW=7).
      //Furtheremore, angle-energy form data is integrated and set new table data,
      //i.e., lab_integrate_data.
      void modify_prod_distribution_data();
      void modify_prod_distr_data();
      void modify_prod_distr_data_continuum_ene_angle_to_lab
             (frendy::ProductDistributionDataContainer& prod_data_obj);
      void change_prod_distr_data_center_of_mass_to_lab
             (Real& csn, Real& drv, Real& ene_a, Real& ene_b, Real& mu_val);
      Real calc_func_mu(Integer angular_repr_flg, Real& mu_val, vector<Real>& cont_data);
      void modify_prod_distr_data_lab_to_continuum_ene_angle
             (int i, frendy::ProductDistributionDataContainer& prod_data_obj);
      void modify_prod_distr_data_two_body_scatter
             (int i, frendy::ProductDistributionDataContainer& prod_data_obj);
      void modify_prod_distr_data_lab
             (int i, frendy::ProductDistributionDataContainer& prod_data_obj);

      void modify_ene_angle_data();
      void modify_angular_in_ene_angle_data(frendy::EnergyAngularDataContainer& ene_angle_data_obj);
      void check_ene_part_data_in_ene_angle_data(frendy::EnergyAngularDataContainer& ene_angle_data_obj);

      void init_equal_probability_bin();

      void calc_equal_probability_table_by_legendle_polynomial
             ( vector<Real>& list_data, vector<Integer>& tab_range_data, vector<Integer>& tab_int_data,
               vector<Real>& tab_mu_data, vector<Real>& tab_y_data );
      void check_legendle_polynomial_data
             ( vector<Real>& list_data, vector<Integer>& tab_range_data, vector<Integer>& tab_int_data,
               vector<Real>& tab_mu_data, vector<Real>& tab_y_data );
      void calc_mu_and_equivalent_prob_by_legendle_polynomial
             (vector<Real>& list_data, vector<Real>& mu_vec, vector<Real>& equivalent_prob,
              vector<Real>& prob_sum );

      void calc_equal_probability_table_by_tabulated_probability_data
             ( vector<Integer>& tab_range_data, vector<Integer>& tab_int_data,
               vector<Real>&    tab_mu_data,    vector<Real>&    tab_y_data );
      void calc_equal_probability_table_by_tabulated_probability_data
             ( vector<Integer>& tab_range_data, vector<Integer>& tab_int_data,
               vector<Real>&    tab_mu_data,    vector<Real>&    tab_y_data, Integer err_opt );
      void check_tabulated_probability_data
             ( vector<Integer>& tab_range_data, vector<Integer>& tab_int_data,
               vector<Real>&    tab_mu_data,    vector<Real>&    tab_y_data );
      void calc_equal_probability_table_by_tabulated_probability_data_const
             (Real& sum_ave, vector<Real>& tab_mu_data, vector<Real>& tab_y_data);
      void calc_equal_probability_table_by_tabulated_probability_data_lin_lin
             (Real& sum_ave, vector<Real>& tab_mu_data, vector<Real>& tab_y_data);
      void calc_equal_probability_table_by_tabulated_probability_data_lin_log
             (Real& sum_ave, vector<Real>& tab_mu_data, vector<Real>& tab_y_data);


      //Sum all gamma production cross section computed from
      //PhotonDataContainer * CrossSectionDataContainer.
      //To calculate cross section, unionized energy grid, that is
      //calculated in modify_xs_data function is used.
      void calc_total_gamma_product_xs();
      void add_multiplied_xs_data(frendy::CrossSectionDataContainer& xs_data_obj,
                                  vector<vector<Integer> >& range_vec, vector<vector<Integer> >& int_vec,
                                  vector<vector<Real> >&    ene_vec,   vector<vector<Real> >&    y_vec);
      void modify_photon_production_xs_data_by_union_grid(frendy::PhotonDataContainer& photon_data_obj);
      void modify_total_photon_production_xs_data(frendy::PhotonDataContainer& photon_data_obj);
 

      //The list and table data in photon angular distribution is convert to equal probaility table.
      //Modify multigroup photon data using GENDF file.
      //However, the GENDF file is not available in FRENDY.
      void calc_multigroup_photon_data();
      void modify_photon_angular_distribution_data_by_equal_probability_table();
      void modify_multigroup_photon_data();


      //Generate ACE data from NuclearDataObject
      void    generate_fast_ace_data_from_modified_nucl_data_obj();
      void    set_title_data();
      void    set_fission_nu_data();
      void    set_fission_nu_data_for_table( vector<Integer>& range_data, vector<Integer>& int_data,
                                             vector<Real>&    ene_data,   vector<Real>&    nu_bar );
      void    modify_fission_nu_data();

      void    check_cross_section_data_reaction_type();
      void    set_reaction_parameter();
      void    set_reaction_parameter_sc();
      Integer check_reaction_parameter_sc(Integer react_val);
      void    set_reaction_parameter_heat_cap();
      Integer check_reaction_parameter_heat_cap(Integer react_val);
      void    set_reaction_parameter_n_non_elastic_and_n_n();

      void    set_angular_distribution_data();
      void    set_angular_distr_data(int i, frendy::EnergyAngularDataContainer& ene_angle_data_obj);
      void    set_angular_distr_data(int i, frendy::ProductDistributionDataContainer& prod_distr_data_obj);
      Integer check_react_type_flg(Integer reaction_type, Integer frame_flg);
      void    set_angular_distr_data_scatter
                (int i, frendy::EnergyAngularDataContainer& ene_angle_data_obj);
      void    set_angular_distr_data_scatter
                (int i, frendy::ProductDistributionDataContainer& prod_distr_data_obj);
      void    integrate_angular_distr_data_scatter(int i);
      void    set_angular_distr_data_charged_particle_elastic_scatter
                (int i, frendy::ProductDistributionDataContainer& prod_distr_data_obj);
      void    linearize_charged_particle_elastic_scatter
                (int j, frendy::ProductDistributionDataContainer& prod_distr_data_obj);
      Real    calc_charged_particle_elastic_scatter
                (int j, Real& mu_val, frendy::ProductDistributionDataContainer& prod_distr_data_obj);
      Real    calc_charged_particle_elastic_scatter_part
                (int j, Real& mu_val, frendy::ProductDistributionDataContainer& prod_distr_data_obj,
                 Integer& charged_particle_flg, Integer& charged_particle_repr_flg, Real8& eta);
      void    thinning_charged_particle_elastic_scatter_data(vector<Real>& mu_vec, vector<Real>& scat_vec);
      void    adjust_total_scatter_xs_by_charged_particle_elastic_scatter
                (int i, frendy::ProductDistributionDataContainer& prod_distr_data_obj);

      void    set_energy_distribution_data();
      void    set_energy_distribution_resize_data(int i_max);
      void    set_energy_distr_data(int i, Integer react_val, Real& q_val);
      void    set_energy_distr_data_from_ene_angle_data_obj
                (int i, frendy::EnergyAngularDataContainer& ene_angle_data_obj, Real& q_val);
      void    set_energy_distr_data_from_ene_angle_data_obj_arbitary_table
                (int i, int j, frendy::EnergyAngularDataContainer& ene_angle_data_obj, Real& q_val);
      void    modify_prompt_xi_spectrum(int i, int j, int k);
      void    set_energy_distr_data_from_ene_angle_data_obj_maxwellian_or_evaporation_spectrum
                (int i, int j, frendy::EnergyAngularDataContainer& ene_angle_data_obj, Real& q_val);
      void    set_energy_distr_data_from_ene_angle_data_obj_watt_spectrum
                (int i, int j, frendy::EnergyAngularDataContainer& ene_angle_data_obj, Real& q_val);
      void    set_energy_distr_data_from_ene_angle_data_obj_ene_depend_spectrum
                (int i, int j, frendy::EnergyAngularDataContainer& ene_angle_data_obj, Real& q_val);
      void    calc_linearized_energy_depend_fission_spectrum
                ( vector<Real>& ene_part_ene_vec, vector<Real>& ene_part_vec,
                  Real& lower_ene_fis_n, Real& upper_ene_fis_n, Real& temp_max_data,
                  Real& temp_max_ene_min, Real& temp_max_ene_max );
      Real    calc_madland_nix_fis_spectrum
                (Real& second_ene_data, Real& lower_ene_fis_n, Real& upper_ene_fis_n, Real& temp_max_data);

      void    set_energy_distr_data_from_prod_distr_data_obj
                (int i, frendy::ProductDistributionDataContainer& prod_distr_data_obj, Real& q_val);
      void     calc_product_yield(int i, frendy::ProductDistributionDataContainer& prod_distr_data_obj,
                                  vector<int>& mat_data_pos);
      void     check_product_yield(frendy::ProductDistributionDataContainer& prod_distr_data_obj,
                                   Integer& yield_flg, vector<int>& mat_data_pos, Real& yield_ene_max);
      void     modify_product_yield(frendy::ProductDistributionDataContainer& prod_distr_data_obj);
      void     set_product_yield(int i, frendy::ProductDistributionDataContainer& prod_distr_data_obj,
                                 Integer& yield_flg, vector<int>& mat_data_pos, Real& yield_ene_max);
      void     copy_product_yield(int i, frendy::ProductDistributionDataContainer& prod_distr_data_obj,
                                  Integer& yield_flg, vector<int>& mat_data_pos);
      void     set_n_body_phase_space_distr_data
                 (int i, int j, int pos, frendy::ProductDistributionDataContainer& prod_distr_data_obj);
      void     calc_n_body_phase_space_distr_data(Integer& n_body_particle_no,
                 vector<Real>& mu_vec, vector<Real>& prob_vec, vector<Real>& prob_integ_vec);
      void     set_other_ene_angle_distr_data
                 (int i, int j, int pos, frendy::ProductDistributionDataContainer& prod_distr_data_obj,
                  Real& q_val);
      void     set_other_ene_angle_distr_common_data
                 (int i, int j, int pos, frendy::ProductDistributionDataContainer& prod_distr_data_obj);
      void     set_continuum_ene_angle_distr_data
                 (int i, int j, int pos, frendy::ProductDistributionDataContainer& prod_distr_data_obj,
                  Real& q_val);
      int      check_continuum_ene_angle_distr_data
                 (Real& ene_a, Real& ene_b, int l, int l_max, Integer react_tyoe, Real& q_val);
      void     extend_low_histogram
                 (int i, int j, int k, int pos, frendy::ProductDistributionDataContainer& prod_distr_data_obj);
      void     extend_low_histogram_by_log(Real& ene_val,  vector<Real>& ene_vec,
                                           vector<vector<Real> >& cont_vec, vector<string>& com_vec);
      void     extend_low_histogram_by_lin(Real& ene_val,  vector<Real>& ene_vec,
                                           vector<vector<Real> >& cont_vec, vector<string>& com_vec);
      void     calc_kalbach_angle_distr(int i, int j, int k, int l, Integer react_type, Integer ang_repr_flg,
                                        Real& ene_in, Real& ene_out, vector<Real>& cont_data);
      void     calc_kalbach_angle_distr_old
                 (int i, int j, int k, int l, Integer react_type, Integer ang_repr_flg,
                  Real& ene_in, Real& ene_out, vector<Real>& cont_data);
      void     calc_kalbach_angle_distr_new_cummulative_angle_distr
                 (int i, int j, int k, int l, Integer react_type, Integer ang_repr_flg,
                  Real& ene_in, Real& ene_out, vector<Real>& cont_data);
      Real     calc_kalbach_mann_parameter(Integer mat_data_a, Integer mat_data_b, Real& ene_in, Real& ene_out);
      void     check_mat_data_for_kalbach_mann_parameter(Integer& mat_data_base);
      void     calc_kalbach_angle_distr_by_ave_data(Integer react_type, Real& coef_a, Real& coef_b,
                                                    Real& f_even, Real& f_odd, Real& ene_in, Real& ene_out);
      void     calc_kalbach_angle_distr_by_table_data(Integer react_type, Real& coef_a, Real& coef_b,
                                                      Real& tab_a, Real& tab_b, Real& tab_c, Real& tab_d,
                                                      Real& ene_in, Real& ene_out);
      void     set_lab_ene_angle_distr_data
                 (int i, int j, int pos, frendy::ProductDistributionDataContainer& prod_distr_data_obj);

      void     set_prob_table();
      void     set_delayed_neutron_data();
      void     set_delayed_neutron_data_common(int& pos);
      void     set_delayed_neutron_data_table(int i, frendy::EnergyAngularDataContainer& ene_angle_data_obj);
      void     set_delayed_neutron_data_spectrum(int i, frendy::EnergyAngularDataContainer& ene_angle_data_obj);
      void     modify_delayed_neutron_data(int i, vector<Real>& x_vec, vector<Real>& y_vec);
      void     set_photon_production_xs();

      void     set_detailed_photon_production_data();
      void     set_detailed_photon_production_data_multiplicity
                 (Integer file_no, Integer reaction_type, int pos);
      void     set_detailed_photon_production_data_xs(Integer file_no, Integer reaction_type, int pos);
      void     set_detailed_photon_production_data_ene_angle_distr();
      void     set_photon_enegy_distr_by_discrete_ene(Real photon_ene_min, Real photon_ene_max,
                                                      Integer photon_ene_flg, Real binding_ene);
      void     set_photon_enegy_distr_by_continuous_photon_ene_spectra(int pos, int j);
      void     set_photon_enegy_distr_by_ene_angle_distr(int pos);
      void     set_photon_enegy_distr_by_ene_angle_distr_common_ace_data(int pos);
      void     set_photon_enegy_distr_by_ene_angle_distr_common_data(int pos, vector<Real>& gam_prob_ene_data);
      void     set_photon_enegy_distr_by_ene_angle_distr_common_data
                 (int pos, Integer distr_func_flg,
                   vector<Real>& ene_vec, vector<Integer>& ene_data_flg, vector<vector<Real> >& prob_ene_vec,
                   vector<Real>& gam_prob_ene_data);
      void     set_photon_enegy_distr_by_ene_angle_distr_prob_data
                 (int pos, vector<Real>& gam_prob_ene_data, 
                  vector<vector<Real> >& gam_prob_ene_data_tot, vector<vector<Real> >& gam_prob_data_tot);
      void     set_photon_enegy_distr_by_ene_angle_distr_weight_data
                 (int pos, vector<Real>& gam_prob_ene_data,
                  vector<vector<Real> >& gam_prob_ene_data_tot, vector<vector<Real> >& gam_prob_data_tot);

      void     set_photon_angular_distr();

      void     set_particle_production();
      int      set_particle_production_flg();
      void     set_particle_production_calc_data();
      void     set_particle_production_resize_data(int i_max);
      void     set_particle_production_set_base_data(int i, Integer& particle_prod_val);
      void     set_particle_production_xs_data(int i, int j, int pos, Integer reaction_type);
      void     set_particle_production_xs_data_by_angle_data
                 (int i, int j, int pos, Integer reaction_type,
                  vector<Integer>& range_vec, vector<Integer>& int_vec,
                  vector<Real>& ene_vec,      vector<Real>& distr_vec);
      void     set_particle_production_xs_data_by_ene_angle_data
                 (int i, int j, int pos, Integer reaction_type,
                  vector<Integer>& range_vec, vector<Integer>& int_vec,
                  vector<Real>& ene_vec,      vector<Real>& distr_vec);
      void     mod_gas_production_xs(Integer mod_reaction_type, Real mod_e_min);

      void     set_particle_production_angular_data(int i, int j, int pos, Integer reaction_type);
      void     set_particle_production_angular_data_elastic(int i);
      void     set_particle_production_angular_data_capture(int i, int pos);
      void     set_particle_production_angular_data_by_angle_data
                (int i, int j, int pos, Integer reaction_type);
      void     set_particle_production_angular_data_by_angle_data_legendre
                (int i, int j, int pos, int react_no, vector<Real>& mass_coef);
      void     set_particle_production_angular_data_by_angle_data_table
                (int i, int j, int pos, int react_no, vector<Real>& mass_coef);
      void     set_particle_production_angular_data_by_ene_angle_data
                 (int i, int j, int pos, Integer reaction_type);
      void     set_particle_production_angular_data_by_ene_angle_data_by_two_body_scat
                (int i, int j, int k, int pos, int react_no, Real& mass_product, Integer sign_coef);
      void     set_particle_production_angular_data_by_ene_angle_data_by_lab
                (int i, int j, int k, int pos, int react_no);
      Real     set_particle_production_calc_cos_coef(Integer int_val, vector<Real>& x_vec, vector<Real>& y_vec);
      void     set_particle_production_ene_data(int i, int j, int pos, Integer reaction_type);
      void     set_particle_production_ene_data_by_capture(int i, int j);
      void     set_particle_production_ene_data_by_angle_data(int i, int j, int pos, Integer reaction_type);
      void     set_particle_production_ene_data_by_ene_angle_data(int i, int j, int pos, Integer reaction_type);
      void     set_particle_production_ene_data_by_ene_angle_data_void(int i);
      void     set_particle_production_ene_data_by_ene_angle_data_continuum
                 (int i, int j, int k, int pos, int react_no);
      void     set_particle_production_ene_data_by_ene_angle_data_continuum_set_ene_flg
                 (int i, int k, int react_no, Integer angular_repr_flg, Integer& ene_flg);
      void     set_particle_production_ene_data_by_ene_angle_data_continuum_set_base_data
                 (int i, int k, int react_no, vector<Real>& ene_vec);
      void     set_particle_production_ene_data_by_ene_angle_data_continuum_calc_kalbach_data
                 (int i, int k, int react_no, vector<Real>& ene_vec, vector<vector<Real> >& ene_out_vec,
                  vector<vector<Real> >& kalbach_coef_a, vector<vector<Real> >& kalbach_coef_b);
      void     set_particle_production_ene_data_by_ene_angle_data_continuum_calc_mu_data
                 (int i, int k, int react_no, Integer angular_repr_flg);
      void     set_particle_production_ene_data_by_ene_angle_data_continuum_calc_heat_data
                 (int i, int k, int pos, int react_no,vector<Real>& ene_vec,
                  vector<vector<Real> >& ene_out_vec,    vector<vector<Real> >& ene_out_distr_vec,
                  vector<vector<Real> >& kalbach_coef_a, vector<vector<Real> >& kalbach_coef_b);
      void     set_particle_production_ene_data_by_ene_angle_data_other
                 (int i, int j, int k, int pos, int react_no, Integer distr_func_flg);
      void     set_particle_production_ene_data_by_ene_angle_data_phase_space
                 (int i, int j, int k, int pos, int react_no);
      void     set_particle_production_ene_data_by_ene_angle_data_phase_space_calc_heat_data
                 (int i, int j, int k, int pos, int react_no, Real& n_body_mass,
                  vector<Real>& x_vec, vector<Real>& y_vec);
      void     set_particle_production_ene_data_by_ene_angle_data_lab
                 (int i, int j, int k, int pos, int react_no);
      void     set_particle_production_ene_data_by_ene_angle_data_lab_calc_heat_data
                 (int i, int j, int k, int pos, int react_no, vector<vector<Integer> >& int_vec);
      void     set_particle_production_ene_data_add_void_data(int i);
      void     set_particle_production_angle_data_add_void_data(int i);
      void     mod_particle_prod_heat(int i, Integer particle_prod_val);
      void     set_charged_particle_production();
      void     set_charged_particle_production_continuum(int i, int j, int pos);
      void     set_charged_particle_production_two_body_recoil(int i, int j, int pos);

      //Common method
      void clear_input_data();
      void clear_calc_data();
      void clear_ace_data();
      void clear_ace_base_data();
      void clear_ace_ene_angular_distr_data();
      void clear_ace_prod_distr_data();
      void clear_ace_photon_data();
      void clear_ace_particle_data();
      void clear_ace_pointer_data();

      void check_set_data();

      //Copy calculation results to FastAceDataObject
      void copy_fast_ace_data(frendy::FastAceDataObject& ace_data_obj);
      void copy_fast_ace_base_data(frendy::FastAceDataObject& ace_data_obj);
      void copy_fast_ace_ene_angular_distr_data(frendy::FastAceDataObject& ace_data_obj);
      void copy_fast_ace_prod_distr_data(frendy::FastAceDataObject& ace_data_obj);
      void copy_fast_ace_photon_data(frendy::FastAceDataObject& ace_data_obj);
      void copy_fast_ace_particle_data(frendy::FastAceDataObject& ace_data_obj);
      void copy_fast_ace_pointer_data(frendy::FastAceDataObject& ace_data_obj);

      void calc_ace_header_file_data();

    public:
      //constructor
      FastAceDataGenerator(void);

      //destructor
      virtual ~FastAceDataGenerator(void);

      static const int generate_default_mode = 0; //used for generate_mode_flg
      static const int generate_njoy_mode    = 1;

      void clear();

      void generate_ace_data();

      //Setter
      void set_nucl_data_obj(frendy::NuclearDataObject& data_obj);
      void set_mat(Integer int_val);
      void set_temp(Real  real_val);
      void set_new_cummulative_angle_distr_flg(Integer int_val);
      void set_detailed_photon_flg(Integer int_val);
      void set_thinning_ene(vector<Real> real_vec);

      void set_suffix_za_id(Real real_val);
      void set_zi_awr_pair(vector<Integer> int_vec_zi, vector<Real> real_vec_awr);

      void set_mcnpx_mode_flg(Integer int_val);
      void set_discriptive_data(string str_data);

      void set_generate_mode_flg(int int_val);

      //Getter
      frendy::FastAceDataObject get_ace_data_obj();

      frendy::NuclearDataObject get_nucl_data_obj();
      Integer                   get_mat();
      Real                      get_temp();
      Integer                   get_new_cummulative_angle_distr_flg();
      Integer                   get_detailed_photon_flg();
      vector<Real>              get_thinning_ene();

      Real                      get_suffix_za_id();
      vector<Integer>           get_zi_vec();
      vector<Real>              get_awr_vec();

      Integer                   get_mcnpx_mode_flg();
      string                    get_discriptive_data();

      int                       get_generate_mode_flg();
  };
}

#endif //FAST_ACE_DATA_GENERATOR_H
