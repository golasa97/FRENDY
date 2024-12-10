#ifndef MF03_CONVERTER_H
#define MF03_CONVERTER_H

#include "EndfUtils/MFxxMTyyyParser/MF03Parser.hpp"
#include "NuclearDataUtils/NuclearDataContainer/CrossSectionDataContainer.hpp"

namespace frendy
{
  class MF03Converter
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

    public:
      //constructor
      MF03Converter(void);

      //destructor
      virtual ~MF03Converter(void);

      //CrossSectionDataContainer -> MF03Parser
      void convert_frendy_to_endf_format( frendy::CrossSectionDataContainer& frendy_obj,
                                          frendy::MF03Parser& endf_obj );

      //MF03Parser -> CrossSectionDataContainer
      void convert_endf_format_to_frendy( frendy::MF03Parser& endf_obj,
                                          frendy::CrossSectionDataContainer& frendy_obj );
  };
}

#endif //MF03_CONVERTER_H
