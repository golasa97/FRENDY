#ifndef MF06_CONVERTER_H
#define MF06_CONVERTER_H

#include "EndfUtils/MFxxMTyyyParser/MF06Parser.hpp"
#include "NuclearDataUtils/NuclearDataContainer/ProductDistributionDataContainer.hpp"

namespace frendy
{
  class MF06Converter
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

    public:
      //constructor
      MF06Converter(void);

      //destructor
      virtual ~MF06Converter(void);

      //ProductDistributionDataContainer -> MF06Parser
      void convert_frendy_to_endf_format( frendy::ProductDistributionDataContainer& frendy_obj,
                                          frendy::MF06Parser& endf_obj );

      //MF06Parser -> ProductDistributionDataContainer
      void convert_endf_format_to_frendy( frendy::MF06Parser& endf_obj,
                                          frendy::ProductDistributionDataContainer& frendy_obj );
  };
}

#endif //MF06_CONVERTER_H
