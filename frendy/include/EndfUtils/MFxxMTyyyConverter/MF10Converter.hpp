#ifndef MF10_CONVERTER_H
#define MF10_CONVERTER_H

#include "EndfUtils/MFxxMTyyyParser/MF10Parser.hpp"
#include "NuclearDataUtils/NuclearDataContainer/RadioactiveProductDataContainer.hpp"

namespace frendy
{
  class MF10Converter
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

    public:
      //constructor
      MF10Converter(void);

      //destructor
      virtual ~MF10Converter(void);

      //RadioactiveProductDataContainer -> MF10Parser
      void convert_frendy_to_endf_format( frendy::RadioactiveProductDataContainer& frendy_obj,
                                          frendy::MF10Parser& endf_obj );

      //MF10Parser -> RadioactiveProductDataContainer
      void convert_endf_format_to_frendy( frendy::MF10Parser& endf_obj,
                                          frendy::RadioactiveProductDataContainer& frendy_obj );
  };
}

#endif //MF10_CONVERTER_H
