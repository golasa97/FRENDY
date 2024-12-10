#ifndef RECON_RESONANCE_INPUT_READER_H
#define RECON_RESONANCE_INPUT_READER_H

#include "CommonUtils/VectorClearer.hpp"
#include "EndfUtils/EndfFileReader/StringConverter.hpp"
#include "CommonUtils/FileCommentRemover.hpp"
#include "FrendyUtils/FrendyInputCommonUtils.hpp"

namespace frendy
{
  class ReconResonanceInputReader
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
      int            print_title_flg, set_error_max_flg, set_error_integral_flg;

      vector<string> nucl_file_name;
      vector<string> pendf_file_name;
      vector<string> pendf_label_data;
      vector<string> comment_data;

      Real           error;
      Real           error_max;
      Real           error_integral;
      
      vector<Real>   add_grid_data;

      void set_nucl_file_name(vector<string> input_data);
      void set_pendf_label_data(vector<string> input_data);

      void set_error(vector<string>& input_data);
      void set_error_max(vector<string>& input_data);
      void set_error_integral(vector<string>& input_data);
      void set_add_grid_data(vector<string>& input_data);

      void set_print_set_data_flg(vector<string>& input_data);
      void set_process_flg(vector<string>& input_data);
      void set_write_pendf_flg(vector<string>& input_data);

      void set_pendf_file_name(vector<string> input_data);

    public:

      //constructor
      ReconResonanceInputReader(void);

      //destructor
      virtual ~ReconResonanceInputReader(void);

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
      void set_error(Real real_data);
      void set_error_max(Real real_data);
      void set_error_integral(Real real_data);
      void set_add_grid_data(vector<Real> real_vec);


      //Getter
      int            get_print_set_data_flg();
      int            get_process_flg();
      int            get_write_pendf_flg();

      vector<string> get_nucl_file_name();
      vector<string> get_pendf_file_name();
      vector<string> get_pendf_label_data();
      vector<string> get_comment_data();

      Real           get_error();
      Real           get_error_max();
      Real           get_error_integral();
      
      vector<Real>   get_add_grid_data();
  }; 
}

#endif //RECON_RESONANCE_INPUT_READER_H
