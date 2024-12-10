#ifndef NUCLEAR_DATA_PLOTTER_INPUT_READER_H
#define NUCLEAR_DATA_PLOTTER_INPUT_READER_H

#include "CommonUtils/VectorClearer.hpp"
#include "EndfUtils/EndfFileReader/StringConverter.hpp"
#include "CommonUtils/FileCommentRemover.hpp"
#include "FrendyUtils/FrendyInputCommonUtils.hpp"
#include "FrendyUtils/StringDataConverter.hpp"

namespace frendy
{
  class NuclearDataPlotterInputReader
  {
    private:
      frendy::ErrorManager           err_obj;
      frendy::VectorClearer          clr_obj;
      frendy::StringConverter        str_obj;
      frendy::StringDataConverter    str_conv_obj;
      frendy::FrendyInputCommonUtils frendy_utils;

#ifdef DEBUG_MODE
  public:
#endif
      int print_set_data_flg, print_title_flg;

      int ref_flg, com_flg, file_no;

      vector<string>  nucl_file_name, nucl_file_name_tsl, ace_file_name,
                      pendf_file_name, gendf_file_name;

      Real            error, error_max, error_integral;
      
      string          input_file_name, output_file_name;

      vector<Integer> mf_list, mt_list;
      Integer         mat_no;
      Real            temp;

      int edit_flg;
      int  mg_flg;
      int  set_error_max_flg, set_error_integral_flg;

      void set_nucl_file_name(vector<string>& input_data);
      void set_nucl_file_name_tsl(vector<string>& input_data);
      void set_ace_file_name(vector<string>& input_data);
      void set_pendf_file_name(vector<string>& input_data);
      void set_gendf_file_name(vector<string>& input_data);
      void set_error(vector<string>& input_data);
      void set_error_max(vector<string>& input_data);
      void set_error_integral(vector<string>& input_data);
      void set_output_file_name(vector<string>& input_data);
      void set_edit_flg(vector<string>& input_data);
      void set_mf_list(vector<string>& input_data);
      void set_mt_list(vector<string>& input_data);
      void set_mat_no(vector<string>& input_data);
      void set_temp(vector<string>& input_data);

      void set_print_set_data_flg(vector<string>& input_data);

    public:
      static const int no_file    = -1;
      static const int endf_file  =  1;
      static const int ace_file   =  2;
      static const int pendf_file =  3;
      static const int gendf_file =  4;

      static const int histogram  = 1; //or two_point
      static const int two_point  = 1;
      static const int one_point  = 2;

      //constructor
      NuclearDataPlotterInputReader(void);

      //destructor
      virtual ~NuclearDataPlotterInputReader(void);

      void clear();

      void read_input_data_from_input_file(string file_name);

      vector<int> read_input_data(string inp_name, vector<vector<string> >& input_data);
      vector<int> read_input_data(vector<vector<string> >& input_data);
      int         read_input_data(vector<string>& input_type, vector<string>& input_data);
      int         read_input_data(string&         input_type, vector<string>& input_data);

      //Setter
      void set_input_file_name(string str_data);

      void set_error(Real real_data);
      void set_error_max(Real real_data);
      void set_error_integral(Real real_data);

      void set_output_file_name(string str_data);
      void set_edit_flg(string str_data);

      void set_print_set_data_flg(int int_val);

      //Getter
      int             get_ref_flg();
      int             get_com_flg();
      int             get_file_no();

      vector<string>  get_nucl_file_name();
//      vector<string>  get_nucl_file_name_tsl();
      vector<string>  get_ace_file_name();
      vector<string>  get_pendf_file_name();
      vector<string>  get_gendf_file_name();
      Real            get_error();
      Real            get_error_max();
      Real            get_error_integral();
      string          get_input_file_name();
      string          get_output_file_name();
      int             get_edit_flg();
      int             get_mg_flg();
      vector<Integer> get_mf_list();
      vector<Integer> get_mt_list();
      vector<Integer> get_xs_type_list();
      Integer         get_mat_no();
      Real            get_temp();

      int            get_print_set_data_flg();
  }; 
}

#endif //NUCLEAR_DATA_PLOTTER_INPUT_READER_H
