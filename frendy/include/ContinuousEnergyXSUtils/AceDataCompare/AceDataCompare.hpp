#ifndef ACE_DATA_COMPARE_H
#define ACE_DATA_COMPARE_H

#include "CommonUtils/DigitAdjuster.hpp"
#include "CommonUtils/TabAdjuster.hpp"
#include "TabUtils/IntegrateTabData.hpp"

namespace frendy
{
  class AceDataCompare
  {
    private:
      frendy::ErrorManager     err_obj;
      frendy::DigitAdjuster    digit_obj;
      frendy::TabAdjuster      ta_obj;
      frendy::TabInterpolator  ti_obj;
      frendy::IntegrateTabData integ_obj;

      static const int width_int          = 20;
      static const int width_real         = 11;

      static const int no_list_data_mode  = 0;
      static const int list_data_mode     = 1;
      static const int list_data_no_mode  = 2;
      static const int no_table_data_mode = 0;
      static const int table_data_mode    = 1;
      static const int max_data_no        = 2147483647;

      static const Real min_relative_dif; //= 1.0E-20;

#ifdef DEBUG_MODE
  public:
#endif
      string class_name, func_name, data_name, pos_data, comment_data;
      int    list_flg, tab_flg;
      int    data_no, data_no_max;
      int    comp_data_flg;

      Real   x_val;
      Real   tolerance_val_set;
      Real   min_val_set;

      vector<int> x_dif_chk;

      void output_information_data();

      int check_dif_real_data(Real& real_val, Real& real_val_ref, Real& tolerance_val, Real& dif_val);
      int check_dif_real8_data(Real8& real_val, Real8& real_val_ref, Real8& tolerance_val, Real8& dif_val);

    public:
      static const int  comp_all_data_mode       = 0;
      static const int  no_comp_data_number_mode = 1;
      static const Real tolerance_val_def; // = 1.0E-3;
      static const Real min_val_def;       // = 1.0E-30;

      //constructor
      AceDataCompare(void);
 
      //destructor
      virtual ~AceDataCompare(void);

      void clear();

      void comp_int_data(Integer int_val, Integer int_val_ref);
      void comp_real_data(Real real_val, Real real_val_ref);
      void comp_real8_data(Real8 real_val, Real8 real_val_ref);
      void comp_real_data(Real real_val, Real real_val_ref, Real tolerance_val);
      void comp_real8_data(Real8 real_val, Real8 real_val_ref, Real8 tolerance_val);
      void comp_line_data(string str_data, string str_data_ref);

      void comp_list_data(vector<Integer> list_vec, vector<Integer> list_vec_ref);
      void comp_list_data_pointer(vector<Integer> list_vec, vector<Integer> list_vec_ref);
      void comp_list_data(vector<Real> list_vec, vector<Real> list_vec_ref);
      void comp_list_data(vector<Real> list_vec, vector<Real> list_vec_ref, vector<int> dif_chk_list);
      void comp_list_data_modify_small_value(vector<Real> list_vec, vector<Real> list_vec_ref);
      void comp_list_data_modify_small_value(vector<Real> list_vec, vector<Real> list_vec_ref, Real min_val);
      void modify_small_value(vector<Real>& list_vec, Real min_val);

      void modify_initial_rise_region(vector<Real>& x_vec, vector<Real>& y_vec);

      void comp_interpolation_data(vector<Integer> range_vec,     vector<Integer> int_vec,
                                   vector<Integer> range_vec_ref, vector<Integer> int_vec_ref);
      void comp_table_data(vector<Real> x_vec,     vector<Real> y_vec,
                           vector<Real> x_vec_ref, vector<Real> y_vec_ref);
      void comp_table_data(vector<Real> x_vec,     vector<Real> y_vec,     vector<Real> y_vec_integ,
                           vector<Real> x_vec_ref, vector<Real> y_vec_ref, vector<Real> y_vec_integ_ref,
                           Real initial_val);
      void comp_table_data(vector<Real> x_vec,     vector<Real> y_vec,     vector<Real> y_vec_integ,
                           vector<Real> x_vec_ref, vector<Real> y_vec_ref, vector<Real> y_vec_integ_ref);
      void comp_table_data_no_integral
            (vector<Real> x_vec,     vector<Real> y_vec,     vector<Real> y_vec_integ,
             vector<Real> x_vec_ref, vector<Real> y_vec_ref, vector<Real> y_vec_integ_ref);
      void comp_table_data_without_small_value
            (vector<Real> x_vec,     vector<Real> y_vec,     vector<Real> y_vec_integ,
             vector<Real> x_vec_ref, vector<Real> y_vec_ref, vector<Real> y_vec_integ_ref);

      void comp_table_data(vector<Integer> range_vec,     vector<Integer> int_vec,
                           vector<Real>    x_vec,         vector<Real>    y_vec,
                           vector<Integer> range_vec_ref, vector<Integer> int_vec_ref,
                           vector<Real>    x_vec_ref,     vector<Real>    y_vec_ref);
      void comp_table_data(vector<Integer> range_vec,     vector<Integer> int_vec,
                           vector<Real>    x_vec,         vector<Real>    y_vec,
                           vector<Real>    y_vec_integ,
                           vector<Integer> range_vec_ref, vector<Integer> int_vec_ref,
                           vector<Real>    x_vec_ref,     vector<Real>    y_vec_ref,
                           vector<Real>    y_vec_integ_ref, Real initial_val);
      void comp_table_data(vector<Integer> range_vec,     vector<Integer> int_vec,
                           vector<Real>    x_vec,         vector<Real>    y_vec,
                           vector<Real>    y_vec_integ,
                           vector<Integer> range_vec_ref, vector<Integer> int_vec_ref,
                           vector<Real>    x_vec_ref,     vector<Real>    y_vec_ref,
                           vector<Real>    y_vec_integ_ref);
      void comp_table_data_no_integral
             (vector<Integer> range_vec,     vector<Integer> int_vec,
              vector<Real>    x_vec,         vector<Real>    y_vec,       vector<Real>    y_vec_integ,
              vector<Integer> range_vec_ref, vector<Integer> int_vec_ref,
              vector<Real>    x_vec_ref,     vector<Real>    y_vec_ref,   vector<Real>    y_vec_integ_ref);
      void comp_table_data_without_small_value
             (vector<Integer> range_vec,     vector<Integer> int_vec,
              vector<Real>    x_vec,         vector<Real>    y_vec,       vector<Real>    y_vec_integ,
              vector<Integer> range_vec_ref, vector<Integer> int_vec_ref,
              vector<Real>    x_vec_ref,     vector<Real>    y_vec_ref,   vector<Real>    y_vec_integ_ref);

      void comp_table_data(Integer int_data,     vector<Real> x_vec,     vector<Real>    y_vec,
                           Integer int_data_ref, vector<Real> x_vec_ref, vector<Real>    y_vec_ref);
      void comp_table_data(Integer int_data,     vector<Real> x_vec,     vector<Real>    y_vec,
                           vector<Real> y_vec_integ,
                           Integer int_data_ref, vector<Real> x_vec_ref, vector<Real>    y_vec_ref,
                           vector<Real> y_vec_integ_ref, Real initial_val);
      void comp_table_data(Integer int_data,     vector<Real> x_vec,     vector<Real>    y_vec,
                           vector<Real> y_vec_integ,
                           Integer int_data_ref, vector<Real> x_vec_ref, vector<Real>    y_vec_ref,
                           vector<Real> y_vec_integ_ref);
      void comp_table_data_no_integral
           (Integer int_data,     vector<Real> x_vec,     vector<Real> y_vec,     vector<Real> y_vec_integ,
            Integer int_data_ref, vector<Real> x_vec_ref, vector<Real> y_vec_ref, vector<Real> y_vec_integ_ref);
      void comp_table_data_without_small_value
           (Integer int_data,     vector<Real> x_vec,     vector<Real> y_vec,     vector<Real> y_vec_integ,
            Integer int_data_ref, vector<Real> x_vec_ref, vector<Real> y_vec_ref, vector<Real> y_vec_integ_ref);


      void comp_title_data(Real aw0, Real tz,
                           string discriptive_data, vector<string> title_data,
                           Real aw0_ref, Real tz_ref,
                           string discriptive_data_ref, vector<string> title_data_ref);
      void comp_mat_data(vector<Integer> zi_vec,     vector<Real> awr_vec,
                         vector<Integer> zi_vec_ref, vector<Real> awr_vec_ref);
      void comp_pointer_data(vector<int> pointer_data, vector<int> pointer_data_ref);

      Integer check_list_data_order(vector<Real> list_data, Real& x_p, Real& x_m);
      Integer check_list_data_order(vector<Real> list_data);

      void set_information_data(string class_data, string func_data);
      void set_comp_data_information(string data_name_str, string position_data);
      void set_comp_data_information(string data_name_str);
      void set_comp_data_position(string position_data);
      void set_comp_data_position(int pos_i);
      void set_comp_data_position(int pos_i, int pos_j);
      void set_comp_data_position(int pos_i, int pos_j, int pos_k);
      void set_comp_data_position(int pos_i, int pos_j, int pos_k, int pos_l);
      void set_comp_data_position(int pos_i, int pos_j, int pos_k, int pos_l, int pos_m);
      void clear_comp_data_position();

      void set_tolerance_val_def();
      void set_tolerance_val(Real tolerance_val);
      Real get_tolerance_val();

      void set_min_val_def();
      void set_min_val(Real min_val);
      Real get_min_val();

      void set_comp_data_flg(int comp_flg);
      int  get_comp_data_flg();
  };
}

#endif //ACE_DATA_COMPARE_H

