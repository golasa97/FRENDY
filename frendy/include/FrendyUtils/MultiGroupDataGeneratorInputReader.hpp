#ifndef MULTI_GROUP_DATA_GENERATOR_INPUT_READER_H
#define MULTI_GROUP_DATA_GENERATOR_INPUT_READER_H

#include "CommonUtils/VectorClearer.hpp"
#include "EndfUtils/EndfFileReader/StringConverter.hpp"
#include "CommonUtils/FileCommentRemover.hpp"
#include "FrendyUtils/FrendyInputCommonUtils.hpp"
#include "NjoyUtils/GroupStructureNeutron.hpp"
#include "NjoyUtils/GroupStructureGamma.hpp"
#include "NjoyUtils/MultiGroupWeightFunction.hpp"

namespace frendy
{
  class MultiGroupDataGeneratorInputReader
  {
    private:
      frendy::ErrorManager           err_obj;
      frendy::VectorClearer          clr_obj;
      frendy::StringConverter        str_obj;
      frendy::FrendyInputCommonUtils frendy_utils;

#ifdef DEBUG_MODE
  public:
#endif
      int             process_tsl_mode_flg, process_gam_mode_flg, mg_start_file_flg,
                      print_set_data_flg, process_flg, print_title_flg, ace_output_flg;
      int             temp_set_flg, inp_check_skip_flg;
      int             iwt_no;
      string          input_file_name;

      vector<string>  nucl_file_name, nucl_file_name_tsl,
                      ace_file_name,  ace_file_name_tsl,
                      mg_file_name, mg_edit_mode, mg_process_reaction_name,
                      mg_ufg_div_mode, mg_tsl_data_type, mg_flux_calc_mode;

      vector<Integer> mg_print_reaction, mg_mat_list;

      string          mg_start_file_mode, mg_weighting_spectrum_mode,
                      mg_label_data;

      Real            mg_weighting_spectrum_el, mg_weighting_spectrum_eh,
                      mg_weighting_fission_temp, mg_weighting_1e_el, mg_weighting_1e_eh,
                      temp, max_thermal_ene_e_in, max_thermal_ene_e_out;
      vector<Real>    mg_weighting_spectrum_data_e, mg_weighting_spectrum_data_w,
                      sigma_zero_data, 
                      mg_structure, mg_structure_gam, mg_ufg_structure,
                      mg_number_density,
                      mg_flux_calc_w, mg_flux_calc_eh, mg_flux_calc_el,
                      potential_scat_xs;
      string          sigma_zero_data_auto;
      vector<string>  mg_structure_auto, reso_up_scat_0k_data;

      vector<Integer> mg_weighting_spectrum_data_nbt, mg_weighting_spectrum_data_int,
                      mg_process_data, mg_process_reaction, mg_ufg_div_no;

      Integer         legendre_order, mg_thermal_xs_treatment, reso_up_scat_mode;


      void check_set_data();
      void check_start_file_mode();
      void check_process_tsl_data();
      void check_process_gam_data();
      void check_mg_edit_mode();
      void check_common_input_output_file_name();
      void check_weighting_spectrum();
      void check_group_structure();
      void check_flux_calc_mode();
      void check_ufg_structure();

      void add_data_name_to_error_message(vector<string>& err_com, vector<string> str_vec);
      void set_mg_file_name_with_mg_edit_mode(vector<string>& file_mode);


      void set_print_set_data_flg(vector<string>& input_data);
      void set_process_flg(vector<string>& input_data);

      void set_nucl_file_name(vector<string>& input_data);
      void set_nucl_file_name_tsl(vector<string>& input_data);
      void set_ace_file_name(vector<string>& input_data);
      void set_ace_file_name_tsl(vector<string>& input_data);
      void set_ace_output_option(vector<string>& input_data);

      void set_mg_file_name(vector<string>& input_data);
      void set_mg_file_name(string input_data);
      void set_mg_edit_mode(vector<string>& input_data);
      void set_mg_print_reaction(vector<string>& input_data);
      void set_mg_mat_list(vector<string>& input_data);
      void set_mg_start_file_mode(vector<string>& input_data);

      void set_mg_weighting_spectrum_mode(vector<string>& input_data);
      void set_mg_weighting_spectrum_el(vector<string>& input_data);
      void set_mg_weighting_spectrum_eh(vector<string>& input_data);
      void set_mg_weighting_fission_temp(vector<string>& input_data);
      void set_mg_weighting_1e_el(vector<string>& input_data);
      void set_mg_weighting_1e_eh(vector<string>& input_data);
      void set_mg_weighting_spectrum_data(vector<string>& input_data);
      void set_mg_weighting_spectrum_data_int(vector<string>& input_data);
      int  check_mg_weighting_spectrum_mode(string str_data);

      void set_legendre_order(vector<string>& input_data);

      void set_mg_label_data(vector<string>& input_data);

      void set_temp(vector<string>& input_data);
      void set_sigma_zero_data(vector<string>& input_data);
      void set_max_thermal_ene_e_in(vector<string>& input_data);
      void set_max_thermal_ene_e_out(vector<string>& input_data);

      void set_mg_structure(vector<string>& input_data);
      void set_mg_structure_gam(vector<string>& input_data);
      int  check_mg_structure_mode(string str_data);
      int  check_mg_structure_mode_gam(string str_data);

      void set_mg_process_data(vector<string>& input_data);
      void set_mg_process_reaction(vector<string>& input_data);
      void set_mg_process_reaction_name(vector<string>& input_data);

      void set_mg_ufg_structure(vector<string>& input_data);
      void set_mg_ufg_div_no(vector<string>& input_data);
      void set_mg_ufg_div_mode(vector<string>& input_data);

      void set_mg_number_density(vector<string>& input_data);

      void set_mg_tsl_data_type(vector<string>& input_data);

      void set_mg_flux_calc_mode(vector<string>& input_data);
      void set_mg_flux_calc_w_eh_el(vector<string>& input_data);
      void set_mg_flux_calc_w(vector<string>& input_data);
      void set_mg_flux_calc_eh(vector<string>& input_data);
      void set_mg_flux_calc_el(vector<string>& input_data);

      void set_mg_thermal_xs_treatment(vector<string>& input_data);

      void set_potential_scat_xs(vector<string>& input_data);

      void set_reso_up_scat(vector<string>& input_data);
      void set_reso_up_scat_mode(vector<string>& input_data);

    public:

      //constructor
      MultiGroupDataGeneratorInputReader(void);

      //destructor
      virtual ~MultiGroupDataGeneratorInputReader(void);

      void clear();

      static const int process_off          =    0;
      static const int process_on           =    1;

      static const int process_mode_common  = 1000;
      static const int process_mode_neutron =    1;
      static const int process_mode_tsl     =    2;
      static const int process_mode_gam     =    3;

      static const int reso_up_scat_1d      =    1;
      static const int reso_up_scat_2d      =    2; //def

      void        read_input_data_from_input_file(string file_name);
      void        read_input_data_from_input_file_without_data_check(string file_name);
      vector<int> read_input_data(string inp_name, vector<vector<string> >& input_data);
      vector<int> read_input_data(vector<vector<string> >& input_data);
      int         read_input_data(vector<string>& input_type, vector<string>& input_data);
      int         read_input_data(string& input_type, vector<string>& input_data);

      void get_ufg_data_def(vector<Real>& ufg_structure, vector<Integer>& ufg_div_no,
                            vector<string>& ufg_div_mode);

      void clear_ace_file_name();

      //Setter
      void set_process_tsl_mode_flg(int int_val);
      void set_process_gam_mode_flg(int int_val);

      void set_print_set_data_flg(int int_val);
      void set_process_flg(int int_val);
      void set_print_title_flg(int int_val);
      void set_ace_output_flg(int int_val);

      void set_input_file_name(string str_data);

      void set_mg_print_reaction(vector<Integer> int_vec);
      void set_mg_mat_list(vector<Integer> int_vec);

      void set_mg_start_file_mode(string str_data);
      void set_mg_weighting_spectrum_mode(string str_data);
      void set_mg_label_data(string str_data);

      void set_mg_weighting_spectrum_el(Real real_val);
      void set_mg_weighting_spectrum_eh(Real real_val);
      void set_mg_weighting_fission_temp(Real real_val);
      void set_mg_weighting_1e_el(Real real_val);
      void set_mg_weighting_1e_eh(Real real_val);
      void set_temp(Real real_val);
      void set_max_thermal_ene_e_in(Real real_val);
      void set_max_thermal_ene_e_out(Real real_val);

      void set_mg_weighting_spectrum_data_e(vector<Real> real_vec);
      void set_mg_weighting_spectrum_data_w(vector<Real> real_vec);
      void set_sigma_zero_data(vector<Real> real_vec);
      void set_mg_structure(vector<Real> real_vec);
      void set_mg_structure_gam(vector<Real> real_vec);
      void set_mg_ufg_structure(vector<Real> real_vec);
      void set_mg_number_density(vector<Real> real_vec);
      void set_mg_flux_calc_w(vector<Real> real_vec);
      void set_mg_flux_calc_eh(vector<Real> real_vec);
      void set_mg_flux_calc_el(vector<Real> real_vec);
      void set_potential_scat_xs(vector<Real> real_vec);

      void set_reso_up_scat_0k_data(vector<string> str_vec);
      void set_reso_up_scat_mode(Integer int_val);

      void set_mg_weighting_spectrum_data_int(vector<Integer> int_vec);
      void set_mg_weighting_spectrum_data_nbt(vector<Integer> int_vec);
      void set_mg_process_data(vector<Integer> int_vec);
      void set_mg_process_reaction(vector<Integer> int_vec);
      void set_mg_ufg_div_no(vector<Integer> int_vec);

      void set_legendre_order(Integer int_val);
      void set_mg_thermal_xs_treatment(Integer int_val);


      //Getter
      int             get_process_tsl_mode_flg();
      int             get_process_gam_mode_flg();
      int             get_mg_start_file_flg();

      int             get_print_set_data_flg();
      int             get_process_flg();
      int             get_print_title_flg();
      int             get_ace_output_flg();

      string          get_input_file_name();

      vector<string>  get_nucl_file_name();
      vector<string>  get_nucl_file_name_tsl();
      vector<string>  get_ace_file_name();
      vector<string>  get_ace_file_name_tsl();
      vector<string>  get_mg_file_name();
      vector<string>  get_mg_edit_mode();
      vector<string>  get_mg_process_reaction_name();
      vector<string>  get_mg_ufg_div_mode();
      vector<string>  get_mg_tsl_data_type();
      vector<string>  get_mg_flux_calc_mode();

      vector<Integer> get_mg_print_reaction();
      vector<Integer> get_mg_mat_list();

      string          get_mg_start_file_mode();
      string          get_mg_weighting_spectrum_mode();
      string          get_mg_label_data();

      Real            get_mg_weighting_spectrum_el();
      Real            get_mg_weighting_spectrum_eh();
      Real            get_mg_weighting_fission_temp();
      Real            get_mg_weighting_1e_el();
      Real            get_mg_weighting_1e_eh();
      Real            get_temp();
      Real            get_max_thermal_ene_e_in();
      Real            get_max_thermal_ene_e_out();
      vector<Real>    get_mg_weighting_spectrum_data_e();
      vector<Real>    get_mg_weighting_spectrum_data_w();
      vector<Real>    get_sigma_zero_data();
      vector<Real>    get_mg_structure();
      vector<Real>    get_mg_structure_gam();
      vector<Real>    get_mg_ufg_structure();
      vector<Real>    get_mg_number_density();
      vector<Real>    get_mg_flux_calc_w();
      vector<Real>    get_mg_flux_calc_eh();
      vector<Real>    get_mg_flux_calc_el();
      vector<Real>    get_potential_scat_xs();

      vector<string>  get_reso_up_scat_0k_data();
      Integer         get_reso_up_scat_mode();

      string          get_sigma_zero_data_auto();
      vector<string>  get_mg_structure_auto();

      vector<Integer> get_mg_weighting_spectrum_data_int();
      vector<Integer> get_mg_weighting_spectrum_data_nbt();
      vector<Integer> get_mg_process_data();
      vector<Integer> get_mg_process_reaction();
      vector<Integer> get_mg_ufg_div_no();

      Integer         get_legendre_order();
      Integer         get_mg_thermal_xs_treatment();
  }; 
}

#endif //MULTI_GROUP_DATA_GENERATOR_INPUT_READER_H
