#ifndef ERROR_FUNCTION_BY_POLYNOMIAL_H
#define ERROR_FUNCTION_BY_POLYNOMIAL_H

#include "Config/FrendyTypes.hpp"

namespace frendy
{
  class ErrorFunctionCalculatorWithPolynomialExpansion
  {
    private:
      //For single precision (float)
      static const int n_f = 4;
      float alpha_f, beta_f, a_f[n_f], b_f[n_f];

      //For double precision (double)
      static const int n_d = 8;
      double alpha_d, beta_d, a_d[n_d], b_d[n_d];

    public:
      //constructor
      ErrorFunctionCalculatorWithPolynomialExpansion(void);

      //destructor
      virtual ~ErrorFunctionCalculatorWithPolynomialExpansion(void);

      void  calc_erfc(float x, float x_sq, float exp_x_sq_inv, float& erfc_x);
      void  calc_erf( float x, float x_sq, float exp_x_sq_inv, float& erf_x);
      float erfc(float x);
      float erf(float  x);

      void   calc_erfc(double x, double x_sq, double exp_x_sq_inv, double& erfc_x);
      void   calc_erf( double x, double x_sq, double exp_x_sq_inv, double& erf_x);
      double erfc(double x);
      double erf(double  x);
  };
}

#endif // ERROR_FUNCTION_BY_POLYNOMIAL_H
