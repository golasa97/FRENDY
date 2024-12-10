#ifndef INTEGRATE_TAB_DATA_H
#define INTEGRATE_TAB_DATA_H

#include "CommonUtils/TabInterpolator.hpp"
#include "CommonUtils/ErrorManager.hpp"
#include "TabUtils/LinearizeTabData.hpp"

namespace frendy
{
  class IntegrateTabData
  {
    private:
      frendy::ErrorManager     err_obj;
      frendy::TabInterpolator  ti_obj;
      frendy::LinearizeTabData lin_obj;

      int generate_mode_flg;

#ifdef DEBUG_MODE
  public:
#endif
      Real integrate_data_const(  Real& x_m, Real& y_m, Real& x_p, Real& y_p, Real& x_min, Real& x_max);
      Real integrate_data_lin_lin(Real& x_m, Real& y_m, Real& x_p, Real& y_p, Real& x_min, Real& x_max);
      Real integrate_data_log_lin(Real& x_m, Real& y_m, Real& x_p, Real& y_p, Real& x_min, Real& x_max);
      Real integrate_data_lin_log(Real& x_m, Real& y_m, Real& x_p, Real& y_p, Real& x_min, Real& x_max);
      Real integrate_data_log_log(Real& x_m, Real& y_m, Real& x_p, Real& y_p, Real& x_min, Real& x_max);

      void integrate_for_ace_data_const(vector<Real>& x_vec, vector<Real>& y_vec, vector<Real>& y_integ);
      void integrate_for_ace_data_lin_lin(vector<Real>& x_vec, vector<Real>& y_vec, vector<Real>& y_integ);

    public:
      //constructor
      IntegrateTabData(void);

      //destructor
      virtual ~IntegrateTabData(void);

      static const int generate_default_mode = 0;
      static const int generate_njoy_mode    = 1;

      Real integrate_data(Real& x_m, Real& y_m, Real& x_p, Real& y_p, Integer int_val,
                          Real& x_min, Real& x_max);
      Real integrate_data(Real& x_m, Real& y_m, Real& x_p, Real& y_p, Integer int_val);

      Real integrate_tab1_data(vector<Integer>& range_data, vector<Integer>& int_data,
                               vector<Real>&    x_data,     vector<Real>&    y_data );
      Real integrate_tab1_data_without_data_check(vector<Integer>& range_data, vector<Integer>& int_data,
                                                  vector<Real>&    x_data,     vector<Real>&    y_data );

      Real integrate_tab1_data(vector<Integer>& range_data, vector<Integer>& int_data,
                               vector<Real>&    x_data,     vector<Real>&    y_data,
                               Real x_min, Real x_max );
      Real integrate_tab1_data_without_data_check(vector<Integer>& range_data, vector<Integer>& int_data,
                                                  vector<Real>&    x_data,     vector<Real>&    y_data,
                                                  Real x_min, Real x_max );

      void integrate_for_ace_data
             ( string& class_name, string& func_name,
               vector<Real>& x_vec, vector<Real>& y_vec, vector<Real>& y_integ, Integer int_val);
      void integrate_for_ace_data
             ( string& class_name, string& func_name,
               vector<Real>& x_vec, vector<Real>& y_vec, vector<Real>& y_integ, Integer int_val, Real& sum);
      void integrate_for_ace_data_no_normalize
             ( string& class_name, string& func_name,
               vector<Real>& x_vec, vector<Real>& y_vec, vector<Real>& y_integ, Integer int_val);

      void    modify_interpolation(string& class_name, string& func_name,
                                   vector<Integer>& range_data, vector<Integer>& int_data);
      Integer check_interpolation(string& class_name, string& func_name, Integer reaction_type,
                vector<int>& pos, vector<Integer>& range_data, vector<Integer>& int_data);
      Integer check_interpolation(string& class_name, string& func_name,
                                  vector<Integer>& range_data, vector<Integer>& int_data);
      Integer check_interpolation(string& class_name, string& func_name,
                                  vector<Integer>& range_data, vector<Integer>& int_data, Integer int_val);

      vector<Real> integrate_using_specified_grid_with_lin_lin
                      (vector<Real> grid_data, vector<Real>& x_data, vector<Real>& y_data);

      void set_generate_mode_flg(int int_val);
      int  get_generate_mode_flg();
  };
}

#endif //INTEGRATE_TAB_DATA_H
