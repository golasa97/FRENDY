#ifndef PROB_TABLE_INPUT_READER_H
#define PROB_TABLE_INPUT_READER_H

#include "CommonUtils/VectorClearer.hpp"
#include "EndfUtils/EndfFileReader/StringConverter.hpp"
#include "CommonUtils/FileCommentRemover.hpp"
#include "FrendyUtils/FrendyInputCommonUtils.hpp"

namespace frendy
{
  class ProbTableInputReader
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

      vector<string> nucl_file_name;
      vector<string> pendf_file_name;
      vector<string> pendf_label_data;
      vector<string> comment_data;

      Integer        probability_bin_no;
      Integer        ladder_no, ene_grid_no_per_ladder;
      Real           err_p_tab;
      vector<Real>   sigma_zero_data;

      Integer        random_seed;
      
      void set_nucl_file_name(vector<string> input_data);
      void set_pendf_label_data(vector<string> input_data);
      void set_comment_data(vector<string> input_data);

      void set_probability_bin_no(vector<string>& input_data);
      void set_ladder_no(vector<string>& input_data);
      void set_err_p_tab(vector<string>& input_data);
      void set_ene_grid_no_per_ladder(vector<string>& input_data);
      void set_sigma_zero_data(vector<string>& input_data);

      void set_random_seed(vector<string>& input_data);

      void set_print_set_data_flg(vector<string>& input_data);
      void set_process_flg(vector<string>& input_data);
      void set_write_pendf_flg(vector<string>& input_data);

      void set_pendf_file_name(vector<string> input_data);

    public:

      //constructor
      ProbTableInputReader(void);

      //destructor
      virtual ~ProbTableInputReader(void);

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

      void set_nucl_file_name(string str_data);
      void set_pendf_file_name(string str_data);
      void set_pendf_label_data(string str_data);

      void set_probability_bin_no(Integer int_data);
      void set_ladder_no(Integer int_data);
      void set_err_p_tab(Real real_data);
      void set_ene_grid_no_per_ladder(Integer int_data);
      void set_sigma_zero_data(vector<Real> real_vec);
      void set_random_seed(Integer int_data);

      //Getter
      int            get_print_set_data_flg();
      int            get_process_flg();
      int            get_write_pendf_flg();

      vector<string> get_nucl_file_name();
      vector<string> get_pendf_file_name();
      vector<string> get_pendf_label_data();
      vector<string> get_comment_data();

      Integer        get_probability_bin_no();
      Integer        get_ladder_no();
      Real           get_err_p_tab();
      Integer        get_ene_grid_no_per_ladder();
      vector<Real>   get_sigma_zero_data();
      Integer        get_random_seed();
  }; 
}

#endif //PROB_TABLE_INPUT_READER_H
