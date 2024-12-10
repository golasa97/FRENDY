#ifndef FRENDY_INPUT_COMMON_UTILS_H
#define FRENDY_INPUT_COMMON_UTILS_H

#include "CommonUtils/ErrorManager.hpp"

namespace frendy
{
  class FrendyInputCommonUtils
  {
    private:
       frendy::ErrorManager err_obj;

    public:
      //constructor
      FrendyInputCommonUtils(void);

      //destructor
      virtual ~FrendyInputCommonUtils(void);

      void clear();

      //For FRENDY calculation mode
      static const int calc_mode_no     =    3; //5;
      static const int ace_fast_mode    =    0;
      static const int ace_therm_mode   =    1;
      static const int ace_dosi_mode    =    2;
      static const int mg_neutron_mode  =   10;
      static const int mg_tsl_mode      =   11;
      static const int mg_tsl_mode_fast =   12;
      static const int make_inp_mode    = 1000;
      static const int endf_modify_mode = 2000;
      static const int check_endf_mode  = 3000;
      static const int plot_mode        = 5000;
      static const int njoy_mode        = -999;
      static const int non_related      =   -1;
      int get_calc_mode_def();

      //For on/off flg
      static const Integer on            =  1;
      static const Integer off           = -1;

      //For print_set_data_flg
      static const int print_set_data    = 0; //default
      static const int no_print_set_data = 1;
      int get_print_set_data_flg_def();

      //For process_flg
      static const int process_data      = 0; //default
      static const int skip_process_data = 1;
      int get_process_flg_def();

      //For write_pendf_flg
      static const int write_pendf      =  0;
      static const int skip_write_pendf =  1; //default
      int get_write_pendf_flg_def();

      // **** Default value for CommonData ****
      string         get_input_file_name_def();
      vector<string> get_nucl_file_name_def();
      vector<string> get_pendf_file_name_def();
      vector<string> get_pendf_label_data_def();
      vector<string> get_comment_data_def();

      // **** Default value for ReconResonance ****
      Real         get_error_def();
      Real         get_error_max_def();
      Real         get_error_integral_def();
      vector<Real> get_add_grid_data_def();


      // *** Default value for DopplerBroadening ****
      Real get_temp_def();
      Real get_max_broadening_ene_def();

      // **** Default value for ProbabilityTable ****
      Integer      get_probability_bin_no_def();
      Integer      get_ladder_no_def();
      Real         get_err_p_tab_def();
      Integer      get_ene_grid_no_per_ladder_def();
      Integer      get_random_seed_def();
      vector<Real> get_sigma_zero_data_def();

      // **** Default value for ThermalScatter ****
      vector<string>  get_nucl_file_name_tsl_def();
      Integer get_equi_probable_angle_no_def();
      Integer get_equi_probable_angle_no_tsl_def();
      Integer get_inelastic_distribution_format_def();
      Integer get_principal_atom_no_def();
      Integer get_inelastic_reaction_type_no_def();
      Real    get_max_thermal_ene_in_def();
      Real    get_max_thermal_ene_out_def();

      // **** Default value for AceDataGenerator ****
      vector<string>        get_ace_file_name_def();
      vector<string>        get_ace_dir_file_name_def();
      Real                  get_suffix_id_def();
      vector<string>        get_ace_label_data_def();
      vector<vector<Real> > get_iz_aw_data_def();

      // **** Default value for FastAceDataGenerator ****
      static const Integer no_cumulative_angle_distribution_format  = 0;
      static const Integer use_cumulative_angle_distribution_format = 1; //default
      Integer get_cumulative_angle_distribution_format_def();

      // **** Default value for ThermalScatterAceDataGenerator ****
      static const Integer variable_weight   = 0; //default
      static const Integer constant_weight   = 1;
      static const Integer tabulated_weight  = 2;
      Integer get_weight_option_def();

      string          get_thermal_za_id_name_def();
      vector<Integer> get_moderator_za_data_def();
      Integer         get_atom_type_no_def();

      // **** Default value for MultiGroupGenerator ****
      static const int start_file_endf      =    1;
      static const int start_file_ace       =    2;

      int             get_mg_start_file_flg_def();
      int             get_ace_output_flg_def();
      vector<string>  get_mg_edit_mode_def();
      vector<string>  get_mg_flux_calc_mode_def();

      string          get_mg_start_file_mode_def();
      string          get_mg_weighting_spectrum_mode_def();

      Real            get_mg_weighting_spectrum_el_def();
      Real            get_mg_weighting_spectrum_eh_def();
      Real            get_mg_weighting_fission_temp_def();
      Real            get_mg_weighting_1e_el_def();
      Real            get_mg_weighting_1e_eh_def();

      vector<Real>    get_mg_structure_def();
      vector<Real>    get_mg_number_density_def();
      vector<Real>    get_mg_flux_calc_w_def();
      vector<Real>    get_mg_flux_calc_eh_def();
      vector<Real>    get_mg_flux_calc_el_def();

      vector<Integer> get_mg_weighting_spectrum_data_int_def();
      vector<Integer> get_mg_weighting_spectrum_data_nbt_def();

      Integer         get_mg_thermal_xs_treatment_def();
      Integer         get_legendre_order_def();

      //Check inut data
      void output_str_vec(vector<string>& err_com, vector<string>& str_vec);

      void error_input_type_size
             (string class_name, string func_name, vector<string> input_type);
      void error_input_data_size_is_zero
             (string class_name, string func_name, vector<string> input_data); 
      void error_input_data_size_is_larger_than_one
             (string class_name, string func_name, vector<string> input_data); 

      int read_print_set_data_flg(string class_name, string func_name, vector<string>& input_data);
      int read_process_flg(string class_name, string func_name, vector<string>& input_data);
      int read_write_pendf_flg(string class_name, string func_name, vector<string>& pendf_name,
                               vector<string>& input_data);

      void check_print_set_data_flg(string class_name, int int_val);
      void check_process_flg(string class_name, int int_val);
      void check_write_pendf_flg(string class_name, int int_val);
      void check_write_pendf_flg_no_str_data(string class_name, vector<string> pendf_name, int int_val);

      void write_pendf_data(vector<string>& pendf_file_name, vector<string>& pendf_label_data,
                            vector<string>& comment_data, int write_pendf_flg);
  };
}

#endif //FRENDY_INPUT_COMMON_UTILS_H
