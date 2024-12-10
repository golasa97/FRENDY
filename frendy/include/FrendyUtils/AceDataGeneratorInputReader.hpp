#ifndef ACE_DATA_GENERATOR_INPUT_READER_H
#define ACE_DATA_GENERATOR_INPUT_READER_H

#include "CommonUtils/VectorClearer.hpp"
#include "EndfUtils/EndfFileReader/StringConverter.hpp"
#include "CommonUtils/FileCommentRemover.hpp"
#include "FrendyUtils/FrendyInputCommonUtils.hpp"

namespace frendy
{
  class AceDataGeneratorInputReader
  {
    private:
      frendy::ErrorManager           err_obj;
      frendy::VectorClearer          clr_obj;
      frendy::StringConverter        str_obj;
      frendy::FrendyInputCommonUtils frendy_utils;

#ifdef DEBUG_MODE
  public:
#endif
      int             print_set_data_flg, process_flg;
      int             print_title_flg, mod_ace_file_name_flg, mod_ace_dir_file_name_flg;

      int             generation_mode;

      vector<string>  skip_nucl_name_tsl;

      vector<string>  nucl_file_name, nucl_file_name_tsl,
                      ace_file_name, ace_file_name_fast, ace_file_name_therm,
                      ace_dir_file_name, ace_dir_file_name_fast, ace_dir_file_name_therm,
                      ace_label_data;

      Real            suffix_id;
      vector<vector<Real> > iz_aw_data;

      //For FastAceDataGenerator
      int             cumulative_angle_distribution_format;

      //For ThermalScatterAceDataGenerator
      string          thermal_za_id_name;
      Integer         inelastic_reaction_type_no;
      vector<Integer> moderator_za_data;
      Integer         atom_type_no;
      Integer         equi_probable_angle_no;
      int             weight_option;
      Real            max_thermal_ene;
      
      void set_nucl_file_name(vector<string> input_data);
      void set_nucl_file_name_tsl(vector<string>& input_data);
      void set_ace_file_name(vector<string> input_data);
      void set_ace_dir_file_name(vector<string> input_data);

      void set_ace_label_data(vector<string> input_data);
      void set_suffix_id(vector<string>& input_data);
      void set_iz_aw_data(vector<string>& input_data);

      void set_cumulative_angle_distribution_format(vector<string>& input_data);

      void set_thermal_za_id_name(vector<string>& input_data);
      void set_inelastic_reaction_type_no(vector<string>& input_data);
      void set_moderator_za_data(vector<string>& input_data);
      void set_atom_type_no(vector<string>& input_data);
      void set_equi_probable_angle_no(vector<string>& input_data);
      void set_weight_option(vector<string>& input_data);
      void set_max_thermal_ene(vector<string>& input_data);

      void set_print_set_data_flg(vector<string>& input_data);
      void set_process_flg(vector<string>& input_data);

    public:

      //constructor
      AceDataGeneratorInputReader(void);

      //destructor
      virtual ~AceDataGeneratorInputReader(void);

      void clear();

      static const int inp_mode_common = 1000;
      static const int inp_mode_fast   = 1;
      static const int inp_mode_therm  = 2;
      static const int inp_mode_dosi   = 3;

      void read_input_data_from_input_file(string file_name);

      vector<int> read_input_data(vector<vector<string> >& input_data);
      int         read_input_data(vector<string>& input_type, vector<string>& input_data);
      int         read_input_data(string&         input_type, vector<string>& input_data);

      //Setter
      void set_print_set_data_flg(int int_val);
      void set_process_flg(int int_val);

      void set_generation_mode(int int_val);

      void set_nucl_file_name(string str_data);
      void set_nucl_file_name_tsl(string str_data);
      void set_ace_file_name(string str_data);
      void set_ace_dir_file_name(string str_data);

      void set_ace_label_data(string str_data);
      void set_suffix_id(Real real_data);
      void set_iz_aw_data(vector<vector<Real> > real_vec);

      //For FastAceDataGenerator
      void set_cumulative_angle_distribution_format(int int_data);

      //For ThermalScatterAceDataGenerator
      void set_thermal_za_id_name(string str_data);
      void set_inelastic_reaction_type_no(Integer int_data);
      void set_moderator_za_data(vector<Integer> int_vec);
      void set_atom_type_no(Integer int_data);
      void set_equi_probable_angle_no(Integer int_data);
      void set_weight_option(int int_data);
      void set_max_thermal_ene(Real real_data);


      //Getter
      int             get_print_set_data_flg();
      int             get_process_flg();

      int             get_generation_mode();

      vector<string>  get_nucl_file_name();
      vector<string>  get_nucl_file_name_tsl();
      vector<string>  get_ace_file_name();
      vector<string>  get_ace_file_name_fast();
      vector<string>  get_ace_file_name_therm();
      vector<string>  get_ace_dir_file_name();
      vector<string>  get_ace_dir_file_name_fast();
      vector<string>  get_ace_dir_file_name_therm();

      vector<string>  get_ace_label_data();
      Real            get_suffix_id();
      vector<vector<Real> > get_iz_aw_data();

      //For FastAceDataGenerator
      int             get_cumulative_angle_distribution_format();

      //For ThermalScatterAceDataGenerator
      string          get_thermal_za_id_name();
      Integer         get_inelastic_reaction_type_no();
      vector<Integer> get_moderator_za_data();
      Integer         get_atom_type_no();
      Integer         get_equi_probable_angle_no();
      int             get_weight_option();
      Real            get_max_thermal_ene();
  }; 
}

#endif //ACE_DATA_GENERATOR_INPUT_READER_H
