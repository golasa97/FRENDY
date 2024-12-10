#ifndef COMPLEX_ERROR_FUNCTION_CALCULATOR_WITH_NJOY_PURR_FORMULA
#define COMPLEX_ERROR_FUNCTION_CALCULATOR_WITH_NJOY_PURR_FORMULA

#include "CommonUtils/ErrorManager.hpp"
#include "CommonUtils/VectorCopier.hpp"

namespace frendy
{
  class ComplexErrorFunctionCalculatorWithNjoyPurrFormula
  {
    //The algorithm used in this class is similar to PURR in NJOY99.
    //See subroutines ladr2, uwtab2 and uw2.

    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

      //Parameters for calculation of Doppler broadening function
      static const Integer tayler_mode     = 1;
      static const Integer asymptotic_mode = 2;

      static const Real8 eps; //= 1.0E-7;

      static const Real8 c1; //= 0.5641895835;
      static const Real8 c2; //= 0.2752551000;
      static const Real8 c3; //= 2.7247450000;
      static const Real8 c4; //= 0.5124242000;
      static const Real8 c5; //= 0.0517653600;

      static const Real8 d1; //= 0.4613135000;
      static const Real8 d2; //= 0.1901635000;
      static const Real8 d3; //= 0.0999921600;
      static const Real8 d4; //= 1.7844927000;
      static const Real8 d5; //= 0.0028838940;
      static const Real8 d6; //= 5.5253437000;

      static const Real8 brk1; //= 1.2500000;
      static const Real8 brk2; //= 5.0000000;
      static const Real8 brk3; //= 1.8636360;
      static const Real8 brk4; //= 4.1000000;
      static const Real8 brk5; //= 1.7100000;
      static const Real8 brk6; //= 2.8900000;
      static const Real8 brk7; //= 1.1800000;
      static const Real8 brk8; //= 5.7600000;
      static const Real8 brk9; //= 1.5000000;

      static const int ele_no_x = 41;
      static const int ele_no_y = 27;

#ifdef DEBUG_MODE
  public:
#endif
      Real8                  rpi, rpi_inv, h_val;
      vector<vector<Real8> > tr, ti, trs, tis;

      void calc_w_table_all();
      void calc_w_table(Real8& x_ini, Real8& y_ini, Real8& delta_x, Real8& delta_y,
                        vector<vector<Real8> >& w_r_vec, vector<vector<Real8> >& w_i_vec);
      void calc_complex_probability_integral(Real8& x, Real8& y, Real8& w_r, Real8& w_i);
      void calc_complex_probability_integral_by_tayler_expansion( Real8& x,    Real8& y,
                                                                  Real8& x_sq, Real8& y_sq,
                                                                  Real8& w_r,  Real8& w_i );
      void calc_complex_probability_integral_by_asymptotic_expansion( Real8& x,    Real8& y,
                                                                      Real8& x_sq, Real8& y_sq,
                                                                      Real8& w_r,  Real8& w_i );
      void calc_complex_probability_integral_coef( Real8& tempc, Real8& tempd, Real8& tempm, Real8& temel,
                                                   Real8& c, Real8& d, Real8& am, Real8& el,
                                                   Real8& ajp, Real8& temp4, Real8& ak, 
                                                   Real8& a, Real8& b, Real8& h, Real8& g );
      void clear_w_table();

      void cerfc_case01(Real8& x, Real8& y, Real8& w_r, Real8& w_i);
      void cerfc_case02(Real8& x, Real8& y, Real8& w_r, Real8& w_i);
      void cerfc_case03(Real8& x, Real8& y, Real8& w_r, Real8& w_i);
      void cerfc_case04(Real8& x, Real8& y, Real8& w_r, Real8& w_i);
      void cerfc_case05(Real8& x, Real8& y, Real8& w_r, Real8& w_i);

    public:
      //constructor
      ComplexErrorFunctionCalculatorWithNjoyPurrFormula(void);

      //destructor
      virtual ~ComplexErrorFunctionCalculatorWithNjoyPurrFormula(void);

      void clear();

      void cerfc(Real8 x, Real8  h, Real8& w_x, Real8& w_y);

      void cerfc(Real8 x, Real8& w_x, Real8& w_y);

      void  set_h_val(Real8 real_val);
      Real8 get_h_val();
  };
}

#endif // COMPLEX_ERROR_FUNCTION_CALCULATOR_WITH_NJOY_PURR_FORMULA
