#ifndef PROBABILITY_TABLE_CALCULATOR_H
#define PROBABILITY_TABLE_CALCULATOR_H

#include <boost/timer/timer.hpp>

#include "CommonUtils/DigitAdjuster.hpp"
#include "CommonUtils/TabAdjuster.hpp"
#include "MathUtils/MathUtils.hpp"
#include "MathUtils/RandomNumberGenerator.hpp"
#include "MathUtils/RandomNumberGeneratorWithNjoyFormula.hpp"
#include "MathUtils/Bootstrap.hpp"
#include "NuclearDataUtils/NuclearDataObject.hpp"
#include "ReconResonance/ResonanceXSCalculator.hpp"

namespace frendy
{
  class ProbabilityTableCalculator
  {
    private:
      frendy::ErrorManager    err_obj;
      frendy::VectorClearer   clr_obj;
      frendy::VectorCopier    cp_obj;
      frendy::DigitAdjuster   digit_obj;
      frendy::TabInterpolator ti_obj;
      frendy::TabAdjuster     ta_obj;
 
      frendy::ResonanceXSCalculator reso_calc_obj;

      static int   time_print_opt;
      vector<Real> time_each_ene;

      ofstream     fout_debug_reso, fout_debug_ave_xs;

#ifdef DEBUG_MODE
  public:
#endif

      frendy::MathUtils math_obj;
      frendy::Bootstrap boot_obj;

#ifdef NJOY_MODE
      frendy::RandomNumberGeneratorWithNjoyFormula rand_obj;
#else
      frendy::RandomNumberGenerator                rand_obj;
#endif

      static const Integer random_seed_ini          = 12345;
      static const int     sample_no_ini            = 10000;
      static const int     bin_no_ini               =    15;
      static const int     bondarenko_table_data_no =     5;
      static const int     bondarenko_xs_data_no    =     5;
      static const Real8   level_spacing_min_ini;    //=   500.0;
      static const Real8   ene_range_ini;            //=   900.0;
      static const Real8   ene_low_ini;              //=    10.0;
      static const Real8   cumulative_distr_cauchy;  //=    31.83;
      static const Real8   adjust_scat_xs_val;       //=     1.0E-6;
      static const Real8   max_unreso_ene;           //=     1.0E+6;
      static const Real8   min_xs_coef;              //=     1.0E-2;
      static const Real8   min_temp_value;           //=     1.0E-10;

      static const int     calc_statistical_error_interval =    10;
      static const int     sample_no_bootstrap             = 10000;

      Integer inela_comp_flg, abs_comp_flg, comp_flg; //inelastic / absorption competition flag

      Real8 pi, pi_sq, pi_root, pi_root_inv, sample_no_real, sample_no_real_inv;
      Real8 k_part, third, temp_ref, coef_boltz;
      int   sample_no;

      Integer       random_seed, calc_prob_flg, unreso_data_flg, nucl_data_set_flg;

      Integer       ladder_no,     bin_no,     ene_grid_no;
      int           ladder_no_int, bin_no_int, bin_no_skip, bin_no_sta, ene_grid_no_int,
                    temp_no_int,   sig_zero_no_int;
      Real8         ladder_no_inv, temp_no_inv;
      vector<int>   bin_no_add;
      vector<Real8> temp_data, sig_zero_data;

      frendy::NuclearDataObject             nucl_data_obj;
      frendy::ProbabilityDataContainer      prob_data_obj;

      //Resonance data for unresolved resonance region
      vector<vector<frendy::UnresolvedResonanceDataContainer> > unreso_data_obj;
      frendy::UnresolvedResonanceDataContainer                  unreso_data_obj_each;
      vector<Real8>                     ene_grid_unreso;
      vector<Real8>                     xs_data_unreso;

      Integer                           unreso_int_data, self_shielding_flg_ori;
      Real8                             xs_potential;
      vector<Real8>                     abundance, xs_potential_vec;
      vector<Integer>                   fis_width_flg;
      vector<vector<Integer> >          xs_formula_flg, scat_radius_ene_dependence_flg, radius_calc_flg,
                                        self_shielding_flg;
      vector<vector<Real8> >            reso_ene_low, reso_ene_high, spin_data, scat_radius;
      vector<vector<vector<Integer> > > scat_radius_tab_int_data, scat_radius_tab_range_data, l_value;
      vector<vector<vector<Real8> > >   scat_radius_tab_ene_data, scat_radius_tab_data,
                                        mass, wave_no_part, chan_rad;

      //Cross section for all region
      vector<int>              xs_skip;
      vector<Real8>            xs_data_back;
      vector<vector<Integer> > xs_int_data, xs_range_data;
      vector<vector<Real8> >   xs_ene_data, xs_data;

      //Parameters for probability table
      Integer                                    nrest;
      Real8                                      level_spacing_min, level_spacing_inv;
      vector<vector<vector<Real8> > >            coef_prob_table, cos2phi, sin2phi;
      vector<vector<vector<vector<Real8> > > >   coef_gamma, level_spacing, width_n, width_rad, width_fis,
                                                 width_comp, width_tot;
      vector<vector<vector<vector<Integer> > > > freedom_n, freedom_fis, freedom_comp;

      //Result of all ladder data
      vector<Real8>                   ene_grid_prob, xs_tot_min, xs_tot_max,
                                      xs_inf_ave_all, xs_inf_var_all;
      vector<vector<Real8> >          xs_tot_table, xs_inf_ave, xs_inf_var;
      vector<vector<Integer> >        prob_table_sample_no;
      vector<vector<Real8> >          prob_heat;
      vector<vector<vector<Real8> > > prob_table, bondarenko_table, bondarenko_xs, bondarenko_data;
      Integer                         set_xs_tot_table_data_flg;
      vector<vector<vector<Real8> > > xs_tot_table_all;
      vector<Real8>                   xs_tot_table_ene;

      //Each ladder data
      vector<Real8>                   ene_grid_each_ladder;
      vector<vector<vector<Real8> > > xs_prob;
      int                             ene_reso_loc_no_int;
      Real8                           cos2phi_prob, sin2phi_prob, coef_gamma_prob; 
      vector<Real8>                   ene_reso_loc, xs_inf, width_tot_prob, width_n_prob,
                                      width_fis_prob, width_comp_prob, width_rad_prob;

      //For statistical error calculation
      Real8 static_err;
      vector<vector<vector<Real8> > >          p_tab_stat_each_temp;    //temp, lad_no, bin_no
      vector<vector<vector<vector<Real8> > > > p_tab_xs_stat_each_temp; //temp, lad_no, bin_no, xs_type
      vector<vector<vector<vector<Real8> > > > xs_stat_each_temp;       //temp, lad_no, bin_no, xs_type

      void set_unreso_data();
      void check_self_shielding_flg();
      void set_unreso_int_data(vector<vector<Integer> >& reso_region_flg);
      void set_unreso_parameter(int i, int j, frendy::ResonanceDataContainer& reso_data_obj);
      void set_unreso_ene_grid(vector<vector<vector<Real8> > > ene_data, int i, int j,
                               ResonanceDataContainer& reso_data_obj);
      void adjust_unreso_ene_grid(vector<Real8>& ene_data);

      void set_xs_data();
      void set_back_ground_xs_data(int i);
      void set_competition_flg(int xs_residual_flg);

      //Calculation of unresolved resonance cross section
      void calc_unreso_xs(Real8& ene_val, vector<Real8>& xs_val);
      void search_minimum_level_spacing(vector<vector<Real8> >& level_spacing_vec);
      void calc_unreso_xs_a(int i, int j, Real8& ene_val, vector<Real8>& xs_val);
      void calc_unreso_xs_c(int i, int j, Real8& ene_val, vector<Real8>& xs_val);
      void calc_rho(int i, int j, int k, Real8& ene, Real8& wave_no, Real8& rho, Real8& rho_h);
      void set_unreso_data_for_probability_table();
      void init_unreso_data_for_probability_table();

      //Calculation of probability and bondarenko table
      void calc_probability_and_bondarenko_table(int ene_no, vector<Real8>& xs_unreso,
                                                             vector<Real8>& xs_back_ground);
      void set_probability_table_parameter_all_ladder();
      void set_energy_grid_each_ladder(Real8& ene_min, Real8& ene_max);
      void init_probability_table_parameter_each_ene();
      void set_gamma_width(int i, int j, int k, int l, Real8& ene_low, Real8& ene_high);
      void calc_unreso_xs_with_doppler(Real8 coef_temp_prob);
      void search_ene_pos(int& ene_sta, int& ene_end, Real8 ene_min, Real8 ene_max);
      void adjust_unreso_xs_with_doppler(vector<Real8>& xs_back_ground);
      void calc_infinite_dilution_xs();
      void calc_infinite_dilution_xs_each_ladder(vector<Real8>& xs_back_ground);
      void set_xs_tot_table(int i, vector<vector<Real8> >& xs_val);
      void check_xs_tot_table(int ene_no, int i);
      void calc_probability_and_bondarenko_table_data(int ene_no, int i, int lad_no,
                                                      vector<Real8>& xs_back_ground);
      void add_probability_table_data(int i, vector<vector<Real8> >& xs_val, vector<int>& pos);
      void add_bondarenko_data(int i, vector<vector<Real8> >& xs_val);
      void calc_bondarenko_table();
      void calc_bondarenko_xs();
      void calc_probability_table_data(vector<Real8>& xs_unreso);
      void adjust_probability_table_data(vector<Real8>& xs_unreso);
      void copy_probability_table_data(int ene_no, vector<Real8>& xs_unreso, vector<Real8>& xs_back_ground);
      void mod_probability_and_bondarenko_table(vector<Real8>& xs_unreso,
                                                vector<vector<vector<Real8> > >& p_tab_mod,
                                                vector<vector<vector<Real8> > >& b_tab_mod );

      //For heat xs
      void         calc_probability_heat(int ene_no, vector<Real8> xs_unreso_mod);
      int          check_heat_xs();
      vector<Real> calc_heat_xs(int ene_no);
      void         mod_probability_heat(int ene_no);

      //For debug
      void output_resonance_structure_each_ladder(int ene_no, int i, int lad_no, vector<vector<Real8> >& xs_val);
      void output_average_xs_value_each_ladder(int ene_no, int i, int lad_no, vector<vector<Real8> >& xs_val,
                                       vector<int>& pos);

      //For statistical error calculation
      void calc_probability_table_for_statistical_error
             (vector<vector<Real8> >& xs_val, vector<int>& pos, vector<Real8>& p_tab_stat,
              vector<vector<Real8> >& p_tab_xs_stat, vector<vector<Real8> >& xs_stat);
      void calc_probability_table_and_average_xs_value_each_ladder
             (vector<vector<Real8> >& xs_val, vector<int>& pos, vector<Real8>& p_tab_each,
              vector<vector<Real8> >& xs_ave, vector<vector<vector<Real8> > >& xs_each);
      int  check_statistical_error(int ene_no, int lad_no);
      void output_statistical_error(string method_name_str, int ene_no, int lad_no, int temp_no, int xs_no,
                                    vector<Real8> ave_data, vector<Real8> err_data,
                                    Real8 err_ave, Real8 err_max); //for debug

      vector<vector<Real8> >          calc_prob_table_sample_no_ratio();

      void set_base_data();
      void check_set_data();

      void clear_unreso_data();
      void clear_xs_data();
      void clear_unreso_data_for_probability_table();
      void clear_probability_table_parameter_each_ladder();
      void clear_probability_table_parameter_all_ladder();

    public:
      //constructor
      ProbabilityTableCalculator(void);

      //destructor
      virtual ~ProbabilityTableCalculator(void);

      static const Integer heat_tot = 301;
      static const Integer heat_ela = 302;
      static const Integer heat_fis = 318;
      static const Integer heat_rad = 402;

      void calc_probability_table();
      void output_set_data_information();
      void output_xs_potential_data();

      void clear();

      //setter
      void set_nucl_data_obj(frendy::NuclearDataObject& data_obj);
      void set_sample_no(int int_data);
      void set_random_seed(Integer int_data);
      void set_ladder_no(Integer int_data);
      void set_bin_no(Integer int_data);
      void set_ene_grid_no(Integer int_data);
      void set_temp_data(Real8 real_data);
      void set_temp_data(vector<Real8> real_vec);
      void set_sig_zero_data(vector<Real8> real_vec);
      void set_xs_tot_table_data(vector<vector<vector<Real8> > >& real_vec); //for debug
      void set_xs_tot_table_data(vector<vector<vector<Real8> > >& real_vec_xs,
                                 vector<Real8>&                   real_vec_ene); //for debug
      void set_static_err(Real8 real_data);
      void set_static_err_percent(Real8 real_data);

      //getter
      frendy::NuclearDataObject get_nucl_data_obj();
      int                       get_sample_no();
      Integer                   get_random_seed();
      Integer                   get_ladder_no();
      Integer                   get_bin_no();
      Integer                   get_ene_grid_no();
      vector<Real8>             get_temp_data();
      vector<Real8>             get_sig_zero_data();
      vector<Real8>             get_xs_potential_data();

      //For time print option
      static const int print_time_data    = 0;
      static const int no_print_time_data = 1;
      void         set_time_print_opt(int int_value);
      int          get_time_print_opt();
      vector<Real> get_time_each_ene();
      Real8        get_static_err();
      Real8        get_static_err_percent();
  };
}

#endif // PROBABILITY_TABLE_CALCULATOR_H
