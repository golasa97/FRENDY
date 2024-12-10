#ifndef PROB_DATA_CONVERTER_H
#define PROB_DATA_CONVERTER_H

#include "Config/FrendyTypes.hpp"
#include "NuclearDataUtils/NuclearDataObject.hpp"
#include "CommonUtils/ErrorManager.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class ProbDataConverter
  {
    private:
      frendy::ErrorManager    err_obj;
      frendy::VectorClearer   clr_obj;

    public:
      //constructor
      ProbDataConverter(void);

      //destructor
      virtual ~ProbDataConverter(void);

      void clear();

      void conv_prob_data_container_to_unreso_xs_data
             ( int temp_no,
               frendy::ProbabilityDataContainer&            prob_data_obj,
               frendy::UnresolvedCrossSectionDataContainer& unreso_xs_data_obj );

      void conv_prob_data_container_to_unreso_prob_data
             ( int temp_no,
               frendy::ProbabilityDataContainer&           prob_data_obj,
               frendy::UnresolvedProbabilityDataContainer& unreso_prob_data_obj );
  };
}

#endif // PROB_DATA_CONVERTER_H
