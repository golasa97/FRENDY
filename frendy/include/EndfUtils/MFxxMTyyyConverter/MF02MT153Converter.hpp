#ifndef MF02MT153_CONVERTER_H
#define MF02MT153_CONVERTER_H

#include "EndfUtils/MFxxMTyyyParser/MF02MT153Parser.hpp"
#include "NuclearDataUtils/NuclearDataContainer/ResonanceData/UnresolvedProbabilityDataContainer.hpp"

namespace frendy
{
  class MF02MT153Converter
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

    public:
      //constructor
      MF02MT153Converter(void);

      //destructor
      virtual ~MF02MT153Converter(void);

      //UnresolvedProbabilityDataContainer -> MF02MT153Parser
      void convert_frendy_to_endf_format( frendy::UnresolvedProbabilityDataContainer& frendy_obj,
                                          frendy::MF02MT153Parser& endf_obj );

      //MF02MT153Parser -> UnresolvedProbabilityDataContainer
      void convert_endf_format_to_frendy( frendy::MF02MT153Parser& endf_obj,
                                          frendy::UnresolvedProbabilityDataContainer& frendy_obj );
  };
}

#endif //MF02MT153_CONVERTER_H
