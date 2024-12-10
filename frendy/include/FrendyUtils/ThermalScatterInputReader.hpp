#ifndef THERMAL_SCATTER_INPUT_READER_H
#define THERMAL_SCATTER_INPUT_READER_H

#include "CommonUtils/VectorClearer.hpp"
#include "EndfUtils/EndfFileReader/StringConverter.hpp"
#include "CommonUtils/FileCommentRemover.hpp"
#include "FrendyUtils/FrendyInputCommonUtils.hpp"

namespace frendy
{
  class ThermalScatterInputReader
  {
    private:
      frendy::ErrorManager           err_obj;
      frendy::VectorClearer          clr_obj;
      frendy::StringConverter        str_obj;
      frendy::FrendyInputCommonUtils frendy_utils;

#ifdef DEBUG_MODE
  public:
#endif
      int            print_set_data_flg, process_flg, write_pendf_flg;
      int            print_title_flg;

      int            set_max_thermal_ene_flg;

      vector<string> nucl_file_name;
      vector<string> pendf_file_name;
      vector<string> pendf_label_data;
      vector<string> comment_data;

      vector<string> nucl_file_name_tsl;
      Integer        equi_probable_angle_no;
      //Integer        inelastic_distribution_format;
      Integer        principal_atom_no;
      Integer        inelastic_reaction_type_no;
      Real           max_thermal_ene;
      Real           error;
      
      void set_nucl_file_name(vector<string> input_data);
      void set_pendf_label_data(vector<string> input_data);

      void set_nucl_file_name_tsl(vector<string> input_data);

      void set_equi_probable_angle_no(vector<string>& input_data);
      //void set_inelastic_distribution_format(vector<string>& input_data);
      void set_principal_atom_no(vector<string>& input_data);
      void set_inelastic_reaction_type_no(vector<string>& input_data);
      void set_max_thermal_ene(vector<string>& input_data);
      void set_error(vector<string>& input_data);

      void set_print_set_data_flg(vector<string>& input_data);
      void set_process_flg(vector<string>& input_data);
      void set_write_pendf_flg(vector<string>& input_data);

      void set_pendf_file_name(vector<string> input_data);

    public:

      //constructor
      ThermalScatterInputReader(void);

      //destructor
      virtual ~ThermalScatterInputReader(void);

      void clear();

      void read_input_data_from_input_file(string file_name);

      vector<int> read_input_data(vector<vector<string> >& input_data);
      int         read_input_data(vector<string>& input_type, vector<string>& input_data);
      int         read_input_data(string&         input_type, vector<string>& input_data);

      //Setter
      void set_print_set_data_flg(int int_val);
      void set_process_flg(int int_val);
      void set_write_pendf_flg(int int_val);
      void set_write_pendf_flg(int int_val, string file_name);
      void set_write_pendf_flg(int int_val, vector<string> file_name);

      void set_comment_data(vector<string> input_data);

      void set_nucl_file_name(string str_data);
      void set_pendf_file_name(string str_data);
      void set_pendf_label_data(string str_data);
      void set_equi_probable_angle_no(Integer int_data);
      //void set_inelastic_distribution_format(Integer int_data);
      void set_principal_atom_no(Integer int_data);
      void set_inelastic_reaction_type_no(Integer int_data);
      void set_max_thermal_ene(Real real_data);
      void set_error(Real real_data);


      //Getter
      int            get_print_set_data_flg();
      int            get_process_flg();
      int            get_write_pendf_flg();
      int            get_set_max_thermal_ene_flg();

      vector<string> get_nucl_file_name();
      vector<string> get_pendf_file_name();
      vector<string> get_pendf_label_data();
      vector<string> get_comment_data();

      vector<string> get_nucl_file_name_tsl();
      Integer        get_equi_probable_angle_no();
      //Integer        get_inelastic_distribution_format();
      Integer        get_principal_atom_no();
      Integer        get_inelastic_reaction_type_no();
      Real           get_max_thermal_ene();
      Real           get_error();
  }; 
}

#endif //THERMAL_SCATTER_INPUT_READER_H
