#ifndef THERMAL_SCATTER_CALCULATOR_BY_FRENDY_INPUT_H
#define THERMAL_SCATTER_CALCULATOR_BY_FRENDY_INPUT_H

#include "CommonUtils/TimeUtils.hpp"
#include "FrendyUtils/ThermalScatterInputReader.hpp"
#include "ThermalScatter/ThermalScatterCalculator.hpp"
#include "ThermalScatter/ThermalScatterDataConverter.hpp"

namespace frendy
{
  class ThermalScatterCalculatorByFrendyInput
  {
    private:
      frendy::ErrorManager    err_obj;
      frendy::VectorClearer   clr_obj;
      frendy::TimeUtils       time_obj;
#ifdef DEBUG_MODE
  public:
#endif
      frendy::NuclearDataObject           nucl_data_obj, nucl_data_obj_tsl;

      frendy::ThermalScatterCalculator    scat_calc_obj;
      frendy::ThermalScatterDataConverter scat_conv_obj;
      frendy::ThermalScatterInputReader   frendy_inp_obj;

      Integer calc_flg, set_frendy_inp_obj_flg,
              set_nucl_data_obj_flg, set_nucl_data_obj_tsl_flg;

      Integer opt_elastic, opt_inelastic;

      //For time measurement
      Real time_total;

      void calc_thermal_scatter();
      void check_set_data_flg();

      Real set_max_thermal_ene();

    public:
      //constructor
      ThermalScatterCalculatorByFrendyInput(void);

      //destructor
      virtual ~ThermalScatterCalculatorByFrendyInput(void);

      void clear();

      void set_frendy_inp_obj(frendy::ThermalScatterInputReader inp_obj);
      void set_nucl_data_obj(frendy::NuclearDataObject data_obj);
      void set_nucl_data_obj_tsl(frendy::NuclearDataObject data_obj);

      frendy::ThermalScatterInputReader get_frendy_inp_obj();
      frendy::NuclearDataObject         get_nucl_data_obj();
      frendy::NuclearDataObject         get_nucl_data_obj_without_tsl();

      frendy::NuclearDataObject         get_nucl_data_obj_tsl();

      Real get_time_total();
      Real get_calc_time();
  };
}

#endif //THERMAL_SCATTER_CALCULATOR_BY_FRENDY_INPUT_H
