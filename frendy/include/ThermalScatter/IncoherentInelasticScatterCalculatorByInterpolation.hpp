#ifndef INCOHERENT_INELASTIC_SCATTER_CALCULATOR_BY_INTERPOLATION_H
#define INCOHERENT_INELASTIC_SCATTER_CALCULATOR_BY_INTERPOLATION_H

#include "ThermalScatter/IncoherentInelasticScatterCalculator.hpp"

namespace frendy
{
  class IncoherentInelasticScatterCalculatorByInterpolation : public IncoherentInelasticScatterCalculator
  {
    private:
      static const Integer lagrange_order = 5;

#ifdef DEBUG_MODE
  public:
#endif

      vector<Real8> ene_base, ene_grid_scat_xs_tot;

      void calc_scat_xs_tot_by_lagrange_interpolation();

      virtual void set_energy_grid();

    public:
      //constructor
      IncoherentInelasticScatterCalculatorByInterpolation(void);

      //destructor
      virtual ~IncoherentInelasticScatterCalculatorByInterpolation(void);

      virtual void calc_incoherent_inelastic_scatter();

      //Getter
      virtual frendy::NuclearDataObject get_nucl_data_obj();
  };
}

#endif //INCOHERENT_INELASTIC_SCATTER_CALCULATOR_BY_INTERPOLATION_H
