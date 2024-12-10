#ifndef THERMAL_SCATTER_CALCULATOR_H
#define THERMAL_SCATTER_CALCULATOR_H

#include "EndfUtils/Endf6Converter/Endf6Converter.hpp"
#include "ThermalScatter/IncoherentInelasticScatterCalculatorByInterpolation.hpp"
#include "ThermalScatter/CoherentElasticScatterCalculator.hpp"
#include "ThermalScatter/IncoherentElasticScatterCalculator.hpp"
#include "FrendyUtils/FrendyInputCommonUtils.hpp"

namespace frendy
{
  class ThermalScatterCalculator
  {
    private:
      frendy::ErrorManager err_obj;

#ifdef NJOY_MODE
      frendy::IncoherentInelasticScatterCalculatorByInterpolation incoh_inela_calc_obj;
#else
      frendy::IncoherentInelasticScatterCalculator                incoh_inela_calc_obj;
#endif

      frendy::CoherentElasticScatterCalculator                    coh_ela_calc_obj;
      frendy::IncoherentElasticScatterCalculator                  incoh_ela_calc_obj;

      static const Integer use_nucl_data_default = 1;

#ifdef DEBUG_MODE
  public:
#endif
      frendy::NuclearDataObject nucl_data_obj;
      string   nucl_data_name;
      Integer  calc_thermal_scat_flg, elastic_scat_flg, nucl_data_set_flg;

      Integer opt_inelastic, opt_elastic, bin_no, atom_no;
      Real8   err, ene_max, temp;

      void calc_incoherent_inelastic_scatter();
      void calc_coherent_elastic_scatter();
      void calc_incoherent_elastic_scatter();

      void check_opt_elastic();
      void check_set_data();

    public:
      //constructor
      ThermalScatterCalculator(void);

      //destructor
      virtual ~ThermalScatterCalculator(void);

      void calc_thermal_scatter();
      void output_set_data_information();

      void clear();

      Real get_max_thermal_ene_endf();

      //Setter
      void set_nucl_data_name(string& str_data);
      void set_nucl_data_obj(frendy::NuclearDataObject& data_obj);
      void set_opt_inelastic(Integer int_data);
      void set_opt_elastic(Integer int_data);
      void set_bin_no(Integer int_data);
      void set_atom_no(Integer int_data);
      void set_err(Real8 real_data);
      void set_ene_max(Real8 real_data);
      void set_temp(Real8 real_data);

      //Getter
      string                    get_nucl_data_name();
      frendy::NuclearDataObject get_nucl_data_obj();
      Integer                   get_opt_inelastic();
      Integer                   get_opt_elastic();
      Integer                   get_bin_no();
      Integer                   get_atom_no();
      Real8                     get_err();
      Real8                     get_ene_max();
      Real8                     get_temp();
  };
}

#endif //THERMAL_SCATTER_CALCULATOR_H
