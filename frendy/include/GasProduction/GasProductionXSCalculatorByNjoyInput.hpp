#ifndef GAS_PRODUCTION_XS_CALCULATOR_BY_NJOY_H
#define GAS_PRODUCTION_XS_CALCULATOR_BY_NJOY_H

#include <boost/timer/timer.hpp>

#include "CommonUtils/TimeUtils.hpp"
#include "EndfUtils/Endf6Converter/Endf6Converter.hpp"
#include "EndfUtils/Endf6Writer/Endf6Writer.hpp"
#include "EndfUtils/OtherUtils/EndfTapeDivider.hpp"
#include "NjoyUtils/GasprInputReader.hpp"
#include "NuclearDataUtils/OtherUtils/Endf6FileStore.hpp"
#include "GasProduction/GasProductionXSCalculator.hpp"

namespace frendy
{
  class GasProductionXSCalculatorByNjoyInput
  {
    private:
      frendy::VectorClearer  clr_obj;
      frendy::ErrorManager   err_obj;
      frendy::TimeUtils      time_obj;
      frendy::Endf6Converter conv_obj;
      frendy::Endf6FileStore store_obj;

      frendy::GasProductionXSCalculator gas_prod_xs_obj;
      frendy::Endf6Writer               wri_obj;

      frendy::NuclearDataObject         nucl_data_obj_ori;
      vector<vector<frendy::NuclearDataObject> >  nucl_data_obj_gas;

      string                            input_file_name_njoy;
      int                               start_line_no;

      string                            endf_file_name, pendf_input_name, pendf_output_name;
      
      Integer calc_flg, set_nucl_data_obj_flg;
      
      //For time measurement
      Real time_total;
      
      void calc_gas_product_xs();
      
      void set_input_data();
      
      void output_input_file_name();
    
    public:
      //constructor
      GasProductionXSCalculatorByNjoyInput(void);

      //destructor
      virtual ~GasProductionXSCalculatorByNjoyInput(void);

      void clear();
      
      void set_njoy_input_file_name(string file_name);
      void set_njoy_input_file_name(string file_name, int line_no);

      void write_pendf_file();

      void set_nucl_data_obj_ori(frendy::NuclearDataObject& data_obj);

      string                    get_njoy_input_file_name();
      string                    get_endf_file_name();
      string                    get_pendf_input_name();
      string                    get_pendf_output_name();
      
      //frendy::NuclearDataObject get_nucl_data_obj_ori();
      //vector<vector<frendy::NuclearDataObject> > get_nucl_data_obj_gas();
      
      Real                      get_time_total();
  };
}

#endif //GAS_PRODUCTION_XS_CALCULATOR_BY_NJOY_H
