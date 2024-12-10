#ifndef MF02MT152_CONVERTER_H
#define MF02MT152_CONVERTER_H

#include "EndfUtils/MFxxMTyyyParser/MF02MT152Parser.hpp"
#include "NuclearDataUtils/NuclearDataContainer/ResonanceData/UnresolvedCrossSectionDataContainer.hpp"

namespace frendy
{
  class MF02MT152Converter
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

    public:
      //constructor
      MF02MT152Converter(void);

      //destructor
      virtual ~MF02MT152Converter(void);

      //UnresolvedCrossSectionDataContainer -> MF02MT152Parser
      void convert_frendy_to_endf_format( frendy::UnresolvedCrossSectionDataContainer& frendy_obj,
                                          frendy::MF02MT152Parser& endf_obj );

      //MF02MT152Parser -> UnresolvedCrossSectionDataContainer
      void convert_endf_format_to_frendy( frendy::MF02MT152Parser& endf_obj,
                                          frendy::UnresolvedCrossSectionDataContainer& frendy_obj );
  };
}

#endif //MF02MT152_CONVERTER_H
