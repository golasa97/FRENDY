#ifndef DOPPLER_CALCULATOR_BY_FRENDY_H
#define DOPPLER_CALCULATOR_BY_FRENDY_H

#include <boost/timer/timer.hpp>

#include "CommonUtils/TimeUtils.hpp"
#include "FrendyUtils/DopplerBroadeningInputReader.hpp"
#include "NuclearDataUtils/NuclearDataObject.hpp"
#include "DopplerBroadening/DopplerCalculator.hpp"
#include "DopplerBroadening/ThermalQuantityCalculator.hpp"

namespace frendy
{
  class DopplerCalculatorByFrendyInput
  {
    private:
      frendy::VectorClearer  clr_obj;
      frendy::ErrorManager   err_obj;
      frendy::TimeUtils      time_obj;

      frendy::NuclearDataObject            nucl_data_obj, nucl_data_obj_ori;

      frendy::DopplerCalculator            dop_obj;
      frendy::ThermalQuantityCalculator    th_q_obj;
      frendy::DopplerBroadeningInputReader frendy_inp_obj;

      Integer calc_flg, set_frendy_inp_obj_flg, set_nucl_data_obj_flg, set_nucl_data_obj_ori_flg;
      
      //For time measurement
      Real time_total;
      
      void calc_doppler_broader();
      void calc_thermal_quantity();
      void check_set_data_flg();
      
    public:
      //constructor
      DopplerCalculatorByFrendyInput(void);

      //destructor
      virtual ~DopplerCalculatorByFrendyInput(void);

      void clear();
      
      void set_frendy_inp_obj(frendy::DopplerBroadeningInputReader inp_obj);
      void set_nucl_data_obj(frendy::NuclearDataObject data_obj);
      void set_nucl_data_obj_ori(frendy::NuclearDataObject data_obj);

      frendy::DopplerBroadeningInputReader get_frendy_inp_obj();
      frendy::NuclearDataObject            get_nucl_data_obj();
      frendy::NuclearDataObject            get_nucl_data_obj_ori();

      Real get_time_total();
      Real get_calc_time();
  };
}

#endif //DOPPLER_CALCULATOR_BY_FRENDY_H
