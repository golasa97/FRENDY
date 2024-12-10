#ifndef GAS_PRODUCTION_XS_CALCULATOR_BY_FRENDY_H
#define GAS_PRODUCTION_XS_CALCULATOR_BY_FRENDY_H

#include <boost/timer/timer.hpp>

#include "CommonUtils/TimeUtils.hpp"
#include "FrendyUtils/GasProductionInputReader.hpp"
#include "NuclearDataUtils/NuclearDataObject.hpp"
#include "GasProduction/GasProductionXSCalculator.hpp"

namespace frendy
{
  class GasProductionXSCalculatorByFrendyInput
  {
    private:
      frendy::VectorClearer  clr_obj;
      frendy::ErrorManager   err_obj;
      frendy::TimeUtils      time_obj;

      frendy::NuclearDataObject         nucl_data_obj, nucl_data_obj_ori;

      frendy::GasProductionXSCalculator gas_prod_xs_obj;
      frendy::GasProductionInputReader  frendy_inp_obj;
      
      Integer calc_flg, set_frendy_inp_obj_flg, set_nucl_data_obj_flg, set_nucl_data_obj_ori_flg;
      
      //For time measurement
      Real time_total;
      
      void calc_gas_product_xs();
      void check_set_data_flg();
    
    public:
      //constructor
      GasProductionXSCalculatorByFrendyInput(void);

      //destructor
      virtual ~GasProductionXSCalculatorByFrendyInput(void);

      void clear();
      
      void set_frendy_inp_obj(frendy::GasProductionInputReader inp_obj);
      void set_nucl_data_obj(frendy::NuclearDataObject data_obj);
      void set_nucl_data_obj_ori(frendy::NuclearDataObject data_obj);

      frendy::GasProductionInputReader get_frendy_inp_obj();
      frendy::NuclearDataObject        get_nucl_data_obj();
      frendy::NuclearDataObject        get_nucl_data_obj_ori();

      Real get_time_total();
      Real get_calc_time();
  };
}

#endif //GAS_PRODUCTION_XS_CALCULATOR_BY_FRENDY_H
