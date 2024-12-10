#ifndef MF26_CONVERTER_H
#define MF26_CONVERTER_H

#include "EndfUtils/MFxxMTyyyParser/MF26Parser.hpp"
#include "NuclearDataUtils/NuclearDataContainer/ProductDistributionDataContainer.hpp"

namespace frendy
{
  class MF26Converter
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

    public:
      //constructor
      MF26Converter(void);

      //destructor
      virtual ~MF26Converter(void);

      //ProductDistributionDataContainer -> MF26Parser
      void convert_frendy_to_endf_format( frendy::ProductDistributionDataContainer& frendy_obj,
                                          frendy::MF26Parser& endf_obj );

      //MF26Parser -> ProductDistributionDataContainer
      void convert_endf_format_to_frendy( frendy::MF26Parser& endf_obj,
                                          frendy::ProductDistributionDataContainer& frendy_obj );
  };
}

#endif //MF26_CONVERTER_H
