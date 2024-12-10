#ifndef NU_BAR_CALCULATOR_H
#define NU_BAR_CALCULATOR_H

#include "Config/FrendyTypes.hpp"
#include "CommonUtils/TabInterpolator.hpp"
#include "NuclearDataUtils/NuclearDataObject.hpp"

namespace frendy
{
  class NuBarCalculator
  {
    private:
      frendy::TabInterpolator ti_obj;
      Real8 calc_polynomial_expansion(vector<Real>& coef, Real8& ene_val);
    
    public:
      //constructor
      NuBarCalculator(void);

      //destructor
      virtual ~NuBarCalculator(void);

      Real8 calc_nu_bar(  frendy::NuclearDataObject& nucl_data_obj, Real8 ene_val);
      Real8 calc_nu_d_bar(frendy::NuclearDataObject& nucl_data_obj, Real8 ene_val);
      Real8 calc_nu_p_bar(frendy::NuclearDataObject& nucl_data_obj, Real8 ene_val);
  };
}

#endif // NU_BAR_CALCULATOR_H
