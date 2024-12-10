#ifndef MF08_CONVERTER_H
#define MF08_CONVERTER_H

#include "EndfUtils/MFxxMTyyyParser/MF08Parser.hpp"
#include "NuclearDataUtils/NuclearDataContainer/RadioactiveProductDataContainer.hpp"

namespace frendy
{
  class MF08Converter
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

    public:
      //constructor
      MF08Converter(void);

      //destructor
      virtual ~MF08Converter(void);

      //RadioactiveProductDataContainer -> MF08Parser
      void convert_frendy_to_endf_format( frendy::RadioactiveProductDataContainer& frendy_obj,
                                          frendy::MF08Parser& endf_obj );

      //MF08Parser -> RadioactiveProductDataContainer
      void convert_endf_format_to_frendy( frendy::MF08Parser& endf_obj,
                                          frendy::RadioactiveProductDataContainer& frendy_obj );
  };
}

#endif //MF08_CONVERTER_H
