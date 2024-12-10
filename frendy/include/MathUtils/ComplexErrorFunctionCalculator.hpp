#ifndef COMPLEX_ERROR_FUNCTION_CALCULATOR_H
#define COMPLEX_ERROR_FUNCTION_CALCULATOR_H

#include "Config/FrendyTypes.hpp"
#include "CommonUtils/ErrorManager.hpp"

namespace frendy
{
  class ComplexErrorFunctionCalculator
  {
    // The calculation formula and coefficients are reffered from
    // G. P. M. Poppe, C. M. J. Wijers, “Algorithm 680: evaluation
    // of the complex error function,” ACM Transactions on Mathematical 
    // Software, 16 [1] p.47 (1990).

    private:
      static const Real8 factor;   // = 1.12837916709551257388e+0;
      static const Real8 max_real; // = 0.5e+154;
      static const Real8 max_exp;  // = 708.503061461606e+0;
      static const Real8 max_goni; // = 3.53711887601422e+15;
      static const Real8 qrho_chk; // = 0.085264e+0;

      frendy::ErrorManager err_obj;

      Real8 h_val;

    public:
      //constructor
      ComplexErrorFunctionCalculator(void);

      //destructor
      virtual ~ComplexErrorFunctionCalculator(void);

      void clear();

      void cerfc(Real8 x, Real8 y, Real8& w_x, Real8& w_y);

      void cerfc(Real8 x, Real8& w_x, Real8& w_y);

      void  set_h_val(Real8 real_val);
      Real8 get_h_val();
  };
}

#endif // COMPLEX_ERROR_FUNCTION_CALCULATOR_H
