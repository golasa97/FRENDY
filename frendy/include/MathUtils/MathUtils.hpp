#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include <complex>

#include "Config/FrendyTypes.hpp"
#include "CommonUtils/ErrorManager.hpp"
#include "MathUtils/ComplexErrorFunctionCalculator.hpp"
#include "MathUtils/ComplexErrorFunctionCalculatorWithNjoyReconrFormula.hpp"
#include "MathUtils/ComplexErrorFunctionCalculatorWithNjoyPurrFormula.hpp"
#include "MathUtils/ComplexErrorFunctionCalculatorWithPadeApproximation.hpp"

namespace frendy
{
  class MathUtils
  {
    private:
      frendy::ErrorManager err_obj;

#ifdef A680_MODE
      ComplexErrorFunctionCalculator                      cef_obj;
#elif defined PADE_MODE
      ComplexErrorFunctionCalculatorWithPadeApproximation cef_obj;
#elif defined NJOY_MODE
      //ComplexErrorFunctionCalculatorWithNjoyReconrFormula cef_obj;
      ComplexErrorFunctionCalculatorWithNjoyPurrFormula   cef_obj;
#else
      //ComplexErrorFunctionCalculator                      cef_obj;
      ComplexErrorFunctionCalculatorWithPadeApproximation cef_obj;
#endif
      
      static const Integer sort_data    = 0;
      static const Integer no_sort_data = 1;
#ifdef DEBUG_MODE
  public:
#endif
      Integer lagrange_interpolation_flg;

      Real8 rpi, coef_dop_func;

      //For lagrange_interpolation
      void check_interpolation_data(vector<Real8>& x_vec, vector<Real8>& y_vec,
                                    vector<Real8>& x_vec_mod, vector<Real8>& y_vec_mod);
      void search_appropriate_interpolation_data(Real8& x_val, Integer& order,
                                                 vector<Real8>& x_vec, vector<Real8>& y_vec,
                                                 vector<Real8>& x_vec_use, vector<Real8>& y_vec_use);
      
    public:
      //constructor
      MathUtils(void);

      //destructor
      virtual ~MathUtils(void);

      void clear();

      //Error function (erfc = 1.0 - erf)
      Real8 calc_erf(Real8 x);
      Real8 calc_erfc(Real8 x);

      //Complex error function
      void calc_cerfc(Real8 x, Real8 y, Real8& w_x, Real8& w_y);

      //Calculation of DopplerBroadeingFunction which is used in Single-Level Breit-Wigner
      void calc_doppler_broadening_function(Real8 x, Real8 h, Real8& phi, Real8& chi);
      void calc_doppler_broadening_function(Real8 x, Real8& phi, Real8& chi);
      void set_h_val(Real8 real_val);
      void set_gamma_width(Real8 gam_r, Real8 gam_d);
      Real8 get_h_val();
      

      //Calculation of inverce complex matrix
      void calc_inv_comp_matrix_3x3(Real8 real_vec[3][3], Real8 imag_vec[3][3]);

      //Calculation of expansion
      vector<Real8> legendre_expansion(Real8& x, Integer order);

      //Calculation of interpolation
      Real8 parabolic_interpolation(Real8& x_val,
                                    Real8& x1, Real8& y1, Real8& x2, Real8& y2, Real8& x3, Real8& y3);
      Real8 quadratic_interpolation(Real8& x_val,
                                    Real8& x1, Real8& y1, Real8& x2, Real8& y2, Real8& x3, Real8& y3);
      Real8 lagrange_interpolation( Real8& x_val, Integer& order, vector<Real8>& x_vec, vector<Real8>& y_vec);
      Real8 lagrange_interpolation( Real8& x_val, vector<Real8>& x_vec, vector<Real8>& y_vec);

      void  simultaneous_vector_sort(vector<Real8>& x_vec, vector<Real8>& y_vec);
  };
}

#endif // MATH_UTILS_H
