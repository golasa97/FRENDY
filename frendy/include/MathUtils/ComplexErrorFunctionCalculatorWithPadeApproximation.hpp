#ifndef COMPLEX_ERROR_FUNCTION_CALCULATOR_WITH_PADE_APPROXIMATION_H
#define COMPLEX_ERROR_FUNCTION_CALCULATOR_WITH_PADE_APPROXIMATION_H

#include "Config/FrendyTypes.hpp"
#include "CommonUtils/ErrorManager.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class ComplexErrorFunctionCalculatorWithPadeApproximation
  {
    //The calculation formula and coefficients are reffered from following papers.
    //  <Calculation formula>
    //    O. Shcherbakov, H. Harada, “Resonance Self-Shielding Corrections for
    //    Activation Cross Section Measurements,” J. Nucl. Sci. Technol., 39, pp.548-553 (2002).
    //    R.S. Keshavamurthy, R. Harish “Use of Pade Approximations in the Analytical
    //    Evaluation of the J Function and Its Temperature Derivative,” Nucl. Sci. Eng.,
    //    115, pp.81-88, (1993).
    //  <Coefficients>
    //    P. Martin, G. Donoso, J. Zamudio-Cristi, “A modified asymptotic Pade method.
    //    Application to multipole approximation for the plasma dispersion function Z,”
    //    J. Math. Phys., 21, 2, pp.280-285 (1980).

    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

#ifdef DEBUG_MODE
  public:
#endif

      Real8                           pi, pi_sq, rpi, rpi_inv;
      vector<int>                     case_no_list;
      vector<vector<vector<Real8> > > coef_p, coef_q;
      vector<Real8>                   coef_r_num, coef_i_num, coef_den;

      int pole_no;

      void set_coef();

      void set_coef_p_q();
      void set_coef_p_q_two_pole();
      void set_coef_p_q_three_pole();
      void set_coef_p_q_four_pole();

      Real8 h_val;
      void set_coef_for_calc();
      void set_coef_for_calc_two_pole();
      void set_coef_for_calc_three_pole();
      void set_coef_for_calc_four_pole();

      void cerfc_two_pole(Real8 xi, Real8& w_x, Real8& w_y);
      void cerfc_three_pole(Real8 xi, Real8& w_x, Real8& w_y);
      void cerfc_four_pole(Real8 xi, Real8& w_x, Real8& w_y);

      void clear_all();
      void clear();

    public:
      //constructor
      ComplexErrorFunctionCalculatorWithPadeApproximation(void);

      //destructor
      virtual ~ComplexErrorFunctionCalculatorWithPadeApproximation(void);

      void cerfc(Real8 xi, Real8 yi, Real8& w_x, Real8& w_y);

      void cerfc(Real8 xi, Real8& w_x, Real8& w_y);
      void cerfc_with_specified_pole_no(Real8 xi, Real8& w_x, Real8& w_y);

      void  set_h_val(Real8 real_val);
      Real8 get_h_val();

      void set_pole_no(int int_val);
      int  get_pole_no();
  };
}

#endif // COMPLEX_ERROR_FUNCTION_CALCULATOR_WITH_PADE_APPROXIMATION_H
