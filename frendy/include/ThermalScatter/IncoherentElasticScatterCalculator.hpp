#ifndef INCOHERENT_ELASTIC_SCATTER_CALCULATOR_H
#define INCOHERENT_ELASTIC_SCATTER_CALCULATOR_H

#include "NuclearDataUtils/NuclearDataObject.hpp"
#include "CommonUtils/VectorCopier.hpp"
#include "CommonUtils/TabInterpolator.hpp"
#include "CommonUtils/DigitAdjuster.hpp"
#include "MathUtils/MathUtils.hpp"
#include "ThermalScatter/IncoherentInelasticScatterCalculator.hpp"

namespace frendy
{
  class IncoherentElasticScatterCalculator
  {
    private:
      frendy::ErrorManager    err_obj;
      frendy::VectorClearer   clr_obj;
      frendy::TabInterpolator ti_obj;
      frendy::DigitAdjuster   digit_obj;
      frendy::MathUtils       math_obj;

#ifdef DEBUG_MODE
  public:
#endif

      frendy::NuclearDataObject nucl_data_obj;

      int     bin_no_int;
      Integer calc_incoherent_elastic_scat_flg, opt_elastic, bin_no, atom_no;
      Real8   ene_max, temp, bin_no_real, bin_no_inv;

      Real8   sig_b, sig_coef, debye_waller_factor;

      vector<Real8>          ene_grid, scat_xs;
      vector<vector<Real8> > mu, mu_ave;

      void calc_average_incoherent_elastic_scatter( Real8& ene_data, Real8& xs_data,
                                                    vector<Real8>& mu_data, vector<Real8>& mu_ave_data );

      void preparation_for_incoherent_erastic_scatter();
      void check_set_data();
      void set_energy_grid();
      void set_debye_waller_factor_by_nucl_data();
      void set_debye_waller_factor();

    public:
      //constructor
      IncoherentElasticScatterCalculator(void);

      //destructor
      virtual ~IncoherentElasticScatterCalculator(void);

      static const Integer no_calc           =  0;
      static const Integer use_nucl_data     = 10;
      static const Integer calc_polyethylene = 11;
      static const Integer calc_h_in_zrh     = 12;
      static const Integer calc_zr_in_zrh    = 13;

      void clear();

      void calc_incoherent_elastic_scatter();

      //Setter
      void set_nucl_data_obj(frendy::NuclearDataObject& data_obj);
      void set_opt_elastic(Integer& int_data);
      void set_bin_no(Integer& int_data);
      void set_atom_no(Integer& int_data);
      void set_ene_max(Real8& real_data);
      void set_temp(Real8& real_data);

      //Getter
      frendy::NuclearDataObject get_nucl_data_obj();
      Integer                   get_opt_elastic();
      Integer                   get_bin_no();
      Integer                   get_atom_no();
      Real8                     get_ene_max();
      Real8                     get_temp();
  };
}

#endif //INCOHERENT_ELASTIC_SCATTER_CALCULATOR_H
