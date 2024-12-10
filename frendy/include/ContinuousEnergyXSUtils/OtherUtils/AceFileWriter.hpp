#ifndef ACE_FILE_WRITER_H
#define ACE_FILE_WRITER_H

#include <limits>

#include "CommonUtils/VectorClearer.hpp"
#include "CommonUtils/ErrorManager.hpp"

namespace frendy
{
  class AceFileWriter
  {
    private:
      frendy::ErrorManager    err_obj;
      frendy::VectorClearer   clr_obj;

#ifdef DEBUG_MODE
  public:
#endif
      int output_data_opt;

      static const int data_no_each_line  =  4;
      static const int width_int          = 20;
      static const int width_real         = 11;
      static const int max_zi_awr_pair_no = 16;

      ofstream       fout;
      string         file_name;
      int            set_file_name_flg;
      int            data_count;
      int            data_count_total;
      vector<string> text_data;
      vector<string> text_data_all;
      vector<double> xss_data;

      void check_data_count();
      void fout_check();

    public:
      //constructor
      AceFileWriter(void);

      //destructor
      virtual ~AceFileWriter(void);

      static const int write_file_mode   = 0; //default
      static const int string_data_mode  = 1;
      static const int pointer_calc_mode = 2;
      static const int real_vec_mode     = 3;

      void clear();
      void clear_data_count_total();

      void output_storage_data();

      void close_file();

      //writer
      void set_int_data(Integer int_val);
      void set_real_data(Real real_val);
      void set_real8_data(Real8 real_val);
      void set_line_data(string str_data);
      void set_int_data(Integer int_val, int& ele_no);
      void set_real_data(Real real_val, int& ele_no);
      void set_real8_data(Real8 real_val, int& ele_no);
      void set_line_data(string str_data, int& ele_no);

      void set_list_data(vector<Integer>& list_vec);
      void set_list_data_without_data_no(vector<Integer>& list_vec);
      void set_list_data(vector<Real>& list_vec);
      void set_list_data_without_data_no(vector<Real>& list_vec);

      void set_interpolation_data(vector<Integer>& range_vec, vector<Integer>& int_vec);

      void set_table_data(vector<Real>& x_vec, vector<Real>& y_vec);
      void set_table_data(vector<Real>& x_vec, vector<Real>& y_vec, vector<Real>& y_vec_integ);
      void set_table_data(vector<Integer>& range_vec, vector<Integer>& int_vec,
                          vector<Real>&    x_vec,     vector<Real>&    y_vec);
      void set_table_data(vector<Integer>& range_vec, vector<Integer>& int_vec,
                          vector<Real>& x_vec, vector<Real>& y_vec, vector<Real>& y_vec_integ);

      int  get_ace_ver(vector<string>& title_data);

      void set_title_data(Integer& mcnpx_mode_flg, Real& aw0, Real& tz,
                          string& discriptive_data, vector<string>& title_data);
      void set_title_data_legacy_ver(Integer& mcnpx_mode_flg, Real& aw0, Real& tz,
                                     string& discriptive_data, vector<string>& title_data);
      void set_title_data_new_ver(Integer& mcnpx_mode_flg, Real& aw0, Real& tz,
                                  string& discriptive_data, vector<string>& title_data);
      void add_space_data(int width, string& line_data);

      void set_mat_data(vector<Integer>& zi_vec, vector<Real>& awr_vec);
      void set_pointer_data(vector<int>& pointer_data);

      //Setter
      void set_file_name(string& str_data);

      //getter
      string         get_file_name();
      int            get_data_count();
      int            get_data_count_total();
      vector<string> get_output_data();
      vector<double> get_xss_data();

      //For output option
      void set_output_data_opt(int int_value);
      int  get_output_data_opt();
  };
}

#endif //ACE_FILE_WRITER_H
