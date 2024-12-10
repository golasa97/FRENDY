#ifndef LINEARIZE_TAB_DATA_H
#define LINEARIZE_TAB_DATA_H

#include "CommonUtils/ErrorManager.hpp"
#include "CommonUtils/TabInterpolator.hpp"
#include "CommonUtils/TabAdjuster.hpp"
#include "CommonUtils/DigitAdjuster.hpp"
#include "MathUtils/MathUtils.hpp"

namespace frendy
{
  class LinearizeTabData
  {
    private:
      frendy::ErrorManager    err_obj;
      frendy::TabInterpolator ti_obj;
      frendy::TabAdjuster     ta_obj;
      frendy::DigitAdjuster   digit_obj;
      frendy::MathUtils       math_obj;

      static int essential_fig;

#ifdef DEBUG_MODE
  public:
#endif
      Real err_relative_def, err_min_def;

      Integer comp_interpolation_value( int& ele_no, Integer& int_val,
                                        vector<Real>& x_data, vector<Real>& y_data,
                                        Real& mid_y, Real& mid_x, Real err_relative, Real err_min );
      void    renewal_interpolation_scheme_list( vector<Integer>& range_data, vector<Integer>& int_data,
                                                 vector<Real>&    x_data,     vector<Real>&    new_x );
      void    modify_range_and_int_data( vector<Integer>& range_data, vector<Integer>& int_data,
                                         vector<Real>&    x_data );

      void    modify_tab_data( vector<Integer>& range_data, vector<Integer>& int_data,
                               vector<Real>&    x_data,     vector<Real>&    y_data );
      Integer check_int_data( vector<Integer>& range_data, vector<Integer>& int_data,
                              vector<Real>&    x_data );

      void    linearize_list_data_by_legendre_polynomial_add_mid_point
                (vector<Real>& list_data, vector<Real8>& x_vec, vector<Real8>& y_vec, vector<Real8>& y_int);
      void    linearize_list_data_by_legendre_polynomial_delete_extra_point
                (vector<Real8>& x_vec, vector<Real8>& y_vec, vector<Real8>& y_int);

    public:
      //constructor
      LinearizeTabData(void);

      //destructor
      virtual ~LinearizeTabData(void);

      static const int essential_fig_default = 0;

      void linearize_data(Integer int_val, vector<Real>& x_data, vector<Real>& y_data);
      void linearize_data(Integer int_val, vector<Real>& x_data, vector<Real>& y_data,
                          Real err_relative, Real err_min );

      void linearize_tab1_data(vector<Integer>& range_data, vector<Integer>& int_data,
                               vector<Real>&    x_data,     vector<Real>&    y_data);
      void linearize_tab1_data(vector<Integer>& range_data, vector<Integer>& int_data,
                               vector<Real>&    x_data,     vector<Real>&    y_data,
                               Real err_relative );
      void linearize_tab1_data(vector<Integer>& range_data, vector<Integer>& int_data,
                               vector<Real>&    x_data,     vector<Real>&    y_data,
                               Real err_relative, Real err_min );
      void linearize_tab1_data_without_data_check(vector<Integer>& range_data, vector<Integer>& int_data,
                                                  vector<Real>&    x_data,     vector<Real>&    y_data,
                                                  Real err_relative, Real err_min );

      void normalize_tab1_data(Integer& int_val, vector<Real>& x_data, vector<Real>& y_data);
      void normalize_tab1_data(vector<Integer>& range_data, vector<Integer>& int_data,
                               vector<Real>&    x_data,     vector<Real>&    y_data);

      void normalize_tab1_data_without_data_check(vector<Integer>& range_data, vector<Integer>& int_data,
                                                  vector<Real>&    x_data,     vector<Real>&    y_data);

      void check_tab1_data( vector<Integer>& range_data, vector<Integer>& int_data,
                            vector<Real>&    x_data,     vector<Real>&    y_data );

      void check_legendre_polynomial_list_data(string class_name, string func_name, Integer reaction_type,
                                               int i, int j, int k, int l, vector<Real>& list_data);

      void linearize_list_data_by_legendre_polynomial
             (vector<Real>& list_data, vector<Real>& x_vec, vector<Real>& y_vec);
      void linearize_list_data_by_legendre_polynomial
             (vector<Real>& list_data, vector<Real>& x_vec, vector<Real>& y_vec, vector<Real>& y_vec_int);
      void linearize_list_data_by_legendre_polynomial
             (vector<Real>& list_data, vector<Real>& x_vec, vector<Real>& y_vec, vector<Real>& y_vec_int,
              Real& sum);

      Real8 calc_legendre_expansion(Real8& x_val, Integer order, vector<Real8>& coef_vec);

      void insert_middle_x_data( int ele_no, vector<Real>& x_data, vector<Real>& y_data,
                                 Real& mid_x, Real& mid_y );

      void add_x_and_y_data( vector<Real>& new_y,      vector<Real>& new_x,
                             vector<Real>& new_y_part, vector<Real>& new_x_part );


      void calc_equal_probability_table_by_tabulated_probability_data
             ( int int_val, int bin_no, Real& sum_ave,
               vector<Real>& x_data, vector<Real>& y_data );
      void calc_equal_probability_table_by_tabulated_probability_data_const
             ( int bin_no, Real& sum_ave, vector<Real>& x_data, vector<Real>& y_data );
      void calc_equal_probability_table_by_tabulated_probability_data_lin_lin
             ( int bin_no, Real& sum_ave, vector<Real>& x_data, vector<Real>& y_data );
      void calc_equal_probability_table_by_tabulated_probability_data_lin_log
             ( int bin_no, Real& sum_ave, vector<Real>& x_data, vector<Real>& y_data );


      int  get_essential_fig();
      void set_essential_fig(int int_value);
  };
}

#endif //LINEARIZE_TAB_DATA_H
