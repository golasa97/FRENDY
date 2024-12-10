#ifndef COMPLEX_ERROR_FUNCTION_CALCULATOR_WITH_NJOY_RECONR_FORMULA
#define COMPLEX_ERROR_FUNCTION_CALCULATOR_WITH_NJOY_RECONR_FORMULA

#include "Config/FrendyTypes.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class ComplexErrorFunctionCalculatorWithNjoyReconrFormula
  {
    private:
      static const Real8 break1; //=    36.0;
      static const Real8 break2; //=   144.0;
      static const Real8 break3; //= 10000.0;
      static const Real8 c1;     //= 0.2752551;
      static const Real8 c2;     //= 2.724745;
      static const Real8 c3;     //= 0.5124242;
      static const Real8 c4;     //= 0.05176536;
      static const Real8 c5;     //= 1.1283792;

#ifdef DEBUG_MODE
  public:
#endif
      Real8 h_val;

      static const int   t_no = 62;
      static const Real8 tr[t_no][t_no], ti[t_no][t_no];

      void wtab();
      
    public:
      //constructor
      ComplexErrorFunctionCalculatorWithNjoyReconrFormula(void);

      //destructor
      virtual ~ComplexErrorFunctionCalculatorWithNjoyReconrFormula(void);

      void clear();
      
      void cerfc(Real8 x, Real8 y, Real8& w_x, Real8& w_y);

      void cerfc(Real8 x, Real8& w_x, Real8& w_y);

      void  set_h_val(Real8 real_val);
      Real8 get_h_val();
  };
}

#endif // COMPLEX_ERROR_FUNCTION_CALCULATOR_WITH_NJOY_RECONR_FORMULA
