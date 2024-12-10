#ifndef BROADENED_XS_CALCULATOR_WITH_NJOY_FORMULA_H
#define BROADENED_XS_CALCULATOR_WITH_NJOY_FORMULA_H

#include "DopplerBroadening/BroadenedXSCalculator.hpp"

namespace frendy
{
  class BroadenedXSCalculatorWithNjoyFormula : public BroadenedXSCalculator
  {
    private:

#ifdef DEBUG_MODE
  public:
#endif

      vector<vector<Real8> > s1_vec, s2_vec;
      
      virtual vector<Real8> calc_doppler_broadened_xs_part(Real8& y_val, int int_min, int int_max);
      virtual void          calc_h_n(Real8& inte_sta, Real8& inte_fin, Real8 h_n[5], Real8 f_n_sta[5]);
      virtual void          calc_f_n(Real8& inte_val, Real8 f_n[5]);
      virtual void          calc_coef();
      
    public:
      //constructor
      BroadenedXSCalculatorWithNjoyFormula(void);

      //destructor
      virtual ~BroadenedXSCalculatorWithNjoyFormula(void);

      virtual void clear();
  };
}

#endif //BROADENED_XS_CALCULATOR_WITH_NJOY_FORMULA_H
