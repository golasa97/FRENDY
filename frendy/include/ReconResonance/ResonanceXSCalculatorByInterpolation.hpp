#ifndef RESONANCE_XS_CALCULATOR_BY_INTERPOLATION_H
#define RESONANCE_XS_CALCULATOR_BY_INTERPOLATION_H

#include "ReconResonance/ResonanceXSCalculator.hpp"

namespace frendy
{
  class ResonanceXSCalculatorByInterpolation : public ResonanceXSCalculator
  {
    protected:
      static const int recomended_int_mode =  0;
      static const int njoy_int_mode       =  1;
      static const int interpolation_mode  = 10;
      static const int direct_calc_mode    = 11;

#ifdef DEBUG_MODE
  public:
#endif
      vector<Real8>    unreso_ene_base;

      int int_mode_flg, unreso_int_flg;
      virtual void calc_reso_xs_unreso_a(int i, int j, Real8& ene_val, vector<Real8>& sig_val);
      virtual void calc_reso_xs_unreso_c(int i, int j, Real8& ene_val, vector<Real8>& sig_val);
      void calc_reso_xs_unreso_interpolation(int i, int j, Real8& ene_val, vector<Real8>& sig_val);

      //For set_multi_array_data
      vector<Integer>          unreso_int_data;
      vector<Real8>            unreso_ene_grid;
      vector<vector<Real8> >   unreso_sig_data;
      virtual void set_multi_array_data_unreso_a(int i, int j);
      virtual void set_multi_array_data_unreso_c(int i, int j);

      void calc_reso_xs_unreso_base(int i, int j);
      void set_unreso_ene_grid(int i, int j);
      void set_unreso_int_val(int i, int j);

      virtual void clear_multi_array_data();

    public:
      //constructor
      ResonanceXSCalculatorByInterpolation(void);

      //destructor
      virtual ~ResonanceXSCalculatorByInterpolation(void);

      virtual void clear();
  };
}

#endif //RESONANCE_XS_CALCULATOR_BY_INTERPOLATION_H
