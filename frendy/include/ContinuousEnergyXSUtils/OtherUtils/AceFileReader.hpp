#ifndef ACE_FILE_READER_H
#define ACE_FILE_READER_H

#include "CommonUtils/VectorClearer.hpp"
#include "CommonUtils/ErrorManager.hpp"
#include "CommonUtils/StringUtils.hpp"
#include "EndfUtils/EndfFileReader/EndfUtils.hpp"

namespace frendy
{
  class AceFileReader
  {
    private:
      frendy::ErrorManager    err_obj;
      frendy::VectorClearer   clr_obj;
      frendy::StringUtils     str_obj;

#ifdef DEBUG_MODE
  public:
#endif
      //int output_data_opt;

      static const int max_data_no        = 2147483647;
      static const int data_no_each_line  =  4;
      static const int data_width         = 20;
      static const int max_zi_awr_pair_no = 16;

      string         file_name;
      int            data_count;
      int            data_count_total;
      int            line_no;
      vector<string> text_data;

    public:
      //constructor
      AceFileReader(void);

      //destructor
      virtual ~AceFileReader(void);

      static const int fast_data     =  1;
      static const int tsl_data      =  2;
      static const int dosi_data     =  3;
      static const int pa_data       =  4;
      static const int pn_data       =  5;
      static const int proton_data   =  6;
      static const int deuteron_data =  7;
      static const int triton_data   =  8;
      static const int he_data       =  9;
      static const int alpha_data    = 10;

      void clear();

      string get_string_data();

      //writer
      Integer get_int_data();
      Real    get_real_data();
      Real8   get_real8_data();
      string  get_line_data();

      void get_int_data(Integer& int_val);
      void get_real_data(Real& real_val);
      void get_real8_data(Real8& real_val);
      void get_line_data(string& str_data);

      void get_list_data(vector<Integer>& list_vec);
      void get_list_data_without_data_no(int data_no, vector<Integer>& list_vec);
      void get_list_data(vector<Real>& list_vec);
      void get_list_data_without_data_no(int data_no, vector<Real>& list_vec);

      void get_interpolation_data(vector<Integer>& range_vec, vector<Integer>& int_vec);

      void get_table_data(vector<Real>& x_vec, vector<Real>& y_vec);
      void get_table_data(vector<Real>& x_vec, vector<Real>& y_vec, vector<Real>& y_vec_integ);
      void get_table_data(vector<Integer>& range_vec, vector<Integer>& int_vec,
                          vector<Real>&    x_vec,     vector<Real>&    y_vec);
      void get_table_data(vector<Integer>& range_vec, vector<Integer>& int_vec,
                          vector<Real>& x_vec, vector<Real>& y_vec, vector<Real>& y_vec_integ);

      void get_title_data(Integer& mcnpx_mode_flg, Real& aw0, Real& tz,
                          string& discriptive_data, vector<string>& title_data);
      void get_title_data_legacy_ver
             (Integer& mcnpx_mode_flg, Real& aw0, Real& tz,
              string& discriptive_data, vector<string>& title_data);
      void check_comment_data
             (vector<string>& comment_end, Integer& mcnpx_mode_flg, Real& aw0, Real& tz,
              string& discriptive_data, vector<string>& title_data);
      void get_title_data_new_ver
             (Integer& mcnpx_mode_flg, Real& aw0, Real& tz,
              string& discriptive_data, vector<string>& title_data);
      void get_mat_data(vector<Integer>& zi_vec, vector<Real>& awr_vec);
      void get_pointer_data(int pointer_data_no, vector<int>& pointer_data);

      int  get_ace_file_version();
      int  get_ace_format_version(string str_data);

      //Setter
      void           set_file_name(string& str_data);
      void           set_text_data(vector<string>& str_vec);

      //getter
      string         get_file_name();
      vector<string> get_output_data();
      int            get_current_data_position(); //For debug or check
      int            get_data_position();         //For debug or check
      int            get_current_line_no();       //For debug or check
      int            get_line_no();               //For debug or check
      string         get_current_line_data();     //For debug or check

     int get_ace_data_type_from_ace_file(string ace_file_name);
     int get_ace_data_type(string ace_file_name);

     Real get_awr(string ace_file_name);
     Real get_temp(string ace_file_name);
  };
}

#endif //ACE_FILE_READER_H
