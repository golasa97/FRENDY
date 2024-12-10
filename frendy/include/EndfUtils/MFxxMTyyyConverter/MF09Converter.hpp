#ifndef MF09_CONVERTER_H
#define MF09_CONVERTER_H

#include "EndfUtils/MFxxMTyyyParser/MF09Parser.hpp"
#include "NuclearDataUtils/NuclearDataContainer/RadioactiveProductDataContainer.hpp"

namespace frendy
{
  class MF09Converter
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

    public:
      //constructor
      MF09Converter(void);

      //destructor
      virtual ~MF09Converter(void);

      //RadioactiveProductDataContainer -> MF09Parser
      void convert_frendy_to_endf_format( frendy::RadioactiveProductDataContainer& frendy_obj,
                                          frendy::MF09Parser& endf_obj );

      //MF09Parser -> RadioactiveProductDataContainer
      void convert_endf_format_to_frendy( frendy::MF09Parser& endf_obj,
                                          frendy::RadioactiveProductDataContainer& frendy_obj );
  };
}

#endif //MF09_CONVERTER_H
