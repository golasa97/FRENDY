//#pragma once
#ifndef FRENDY_PARALLEL_RUNNER
#define FRENDY_PARALLEL_RUNNER

#include <omp.h>

#include "NuclearDataProcessor/NuclearDataProcessorByFrendyInput.hpp"

using namespace std;

namespace frendy
{
  class FrendyParallelRunner
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::StringUtils   str_obj;
      frendy::DigitAdjuster digit_obj;

      int    read_flg;
      string separation_record;

      //For <THREAD_NO>
      int thread_no;

      //For <FRENDY_EXE>
      string frendy_exe;

      //For <RESTART>
      int restart_opt;

      //For <TEMP_SET>
      vector<string> temp_case;
      vector<string> temp_data;
      vector<vector<string> > temp_data_vec;

      //For <BGXS_SET>
      vector<string> bgxs_case;
      vector<string> bgxs_data;

      //For <FRENDY_INPUT_TEMPLATE>
      vector<string> frendy_inp_case;
      vector<string> frendy_inp_data;

      //For <ENDF_DIR>, <ACE_DIR>, <TSL_DIR>
      string nucl_dir, tsl_dir;
      int    ace_data_flg;

      //For <OUT_DIR>, <OUT_DIR_INP>, <OUT_DIR_LOG>, <OUT_DIR_ACE>
      //    <OUT_DIR_GENDF>, <OUT_DIR_MATXS>
      string out_dir_inp, out_dir_log, out_dir_ace, out_dir_mg, out_dir_gendf, out_dir_matxs;

      //For <INP>, <INPUT_LIST>, <INPUT_DATA_LIST>
      vector<vector<string> > inp_list;

      //For calculation
      vector<string> nucl_list, tsl_list, inp_base_list, temp_list, bgxs_list, tsl_type_list,
                     frendy_inp_list, frendy_log_list, ace_list, ace_list_tsl, mg_list;
      vector<vector<string> > temp_vec_list;
      vector<string> skip_inp_list, skip_log_list, err_inp_list, err_log_list;

      void read_input_file(string input_name);
      void read_input_data(vector<vector<string> >& input_data);

      void read_thread_no(int& i, int& j, vector<vector<string> >& input_data);
      void read_frendy_exe(int& i, int& j, vector<vector<string> >& input_data);
      void read_restart_opt(int& i, int& j, vector<vector<string> >& input_data);
      void read_temp_data(int& i, int& j, vector<vector<string> >& input_data);
      void read_bgxs_data(int& i, int& j, vector<vector<string> >& input_data);
      void read_frendy_input_template(int& i, int& j, vector<vector<string> >& input_data);
      void read_nucl_dir(int& i, int& j, vector<vector<string> >& input_data);
      void read_tsl_dir(int& i, int& j, vector<vector<string> >& input_data);
      void read_out_dir(int& i, int& j, vector<vector<string> >& input_data);
      void read_out_dir_inp(int& i, int& j, vector<vector<string> >& input_data);
      void read_out_dir_log(int& i, int& j, vector<vector<string> >& input_data);
      void read_out_dir_ace(int& i, int& j, vector<vector<string> >& input_data);
      void read_out_dir_mg(int& i, int& j, vector<vector<string> >& input_data);
      void read_out_dir_gendf(int& i, int& j, vector<vector<string> >& input_data);
      void read_out_dir_matxs(int& i, int& j, vector<vector<string> >& input_data);
      void read_inp_list(int& i, int& j, vector<vector<string> >& input_data);

      void check_inp_data();
      void set_initial_data_list();
      void add_data_list(string nucl_each, string tsl_each, string base_inp_each,
                         vector<string> temp_each, string bgxs_each, string tsl_type_each,
                         string inp_name_each, string log_name_each,
                         string ace_name_nucl_each, string ace_name_tsl_each,
                         string mg_name_each);
      void output_data_list(int i);
      void make_data_list();

      vector<string> set_temp_tsl(string tsl_file_name);

      void set_thread_no();
      void run_frendy();

      void output_skip_list();
      void output_error_list();

      void run_frendy_each_file(int i);
      void make_frendy_inp(int i);

    public:
      //constructor
      FrendyParallelRunner();

      //destructor
      virtual ~FrendyParallelRunner();

      void clear();

      //For data mode
      static const int thread_no_mode     =  1;
      static const int frendy_exe_mode    =  2;
      static const int restart_mode       =  3;
      static const int temp_data_mode     = 11;
      static const int bgxs_data_mode     = 12;
      static const int frendy_inp_mode    = 13;
      static const int nucl_dir_mode      = 21;
      static const int tsl_dir_mode       = 22;
      static const int out_dir_mode       = 31;
      static const int out_dir_inp_mode   = 32;
      static const int out_dir_log_mode   = 33;
      static const int out_dir_ace_mode   = 34;
      static const int out_dir_mg_mode    = 35;
      static const int out_dir_gendf_mode = 36;
      static const int out_dir_matxs_mode = 37;
      static const int inp_list_mode      = 41;
      static const int non_related      =   -1;

      int check_read_mode(string mode_name);
      int check_frendy_log_file(string log_file_name);

      void run_frendy_parallel(string input_name);
  };
}


#endif // FRENDY_PARALLEL_RUNNER
