#ifndef NUCLEAR_DATA_PROCESSOR_BY_NJOY_INPUT_H
#define NUCLEAR_DATA_PROCESSOR_BY_NJOY_INPUT_H

#include "ReconResonance/ResonanceXSReconstructorByNjoyInput.hpp"
#include "DopplerBroadening/DopplerCalculatorByNjoyInput.hpp"
#include "ThermalScatter/ThermalScatterCalculatorByNjoyInput.hpp"
#include "UnresoUtils/ProbabilityTableCalculatorByNjoyInput.hpp"
#include "GasProduction/GasProductionXSCalculatorByNjoyInput.hpp"
#include "ContinuousEnergyXSUtils/AceDataGenerator/AceDataGeneratorByNjoyInput.hpp"
#include "MGXSUtils/MGUtils/MultiGroupDataGeneratorByNjoyInput.hpp"
#include "NjoyUtils/GrouprInputReader.hpp"
#include "NjoyUtils/MatxsrInputReader.hpp"
#include "NuclearDataProcessor/NuclearDataProcessorCommonUtils.hpp"

namespace frendy
{
  class NuclearDataProcessorByNjoyInput
  {
    private:
      frendy::ErrorManager                           err_obj;
      frendy::TimeUtils                              time_obj;
      frendy::NuclearDataProcessorCommonUtils        common_obj;
      frendy::NjoyInputReader                        njoy_inp_obj;

      frendy::ResonanceXSReconstructorByNjoyInput    recon_obj;   //RECONR
      frendy::DopplerCalculatorByNjoyInput           dop_obj;     //BROADR
      frendy::ThermalScatterCalculatorByNjoyInput    sab_obj;     //THERMR
      frendy::ProbabilityTableCalculatorByNjoyInput  prob_obj;    //PURR
      frendy::GasProductionXSCalculatorByNjoyInput   gas_xs_obj;  //GASPR
      frendy::AceDataGeneratorByNjoyInput            ace_gen_obj; //ACER
      frendy::MultiGroupDataGeneratorByNjoyInput     mg_gen_obj;  //GROUPR & MATXSR

#ifdef DEBUG_MODE
  public:
#endif

    public:
      //constructor
      NuclearDataProcessorByNjoyInput(void);

      //destructor
      virtual ~NuclearDataProcessorByNjoyInput(void);

      void clear();

      void process_nucl_data(string input_file_name);
      void process_nucl_data_without_title_output(string input_file_name);
  };
}

#endif // NUCLEAR_DATA_PROCESSOR_BY_NJOY_INPUT_H
