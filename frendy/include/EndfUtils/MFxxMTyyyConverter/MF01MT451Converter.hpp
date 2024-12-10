#ifndef MF01MT451_CONVERTER_H
#define MF01MT451_CONVERTER_H

#include "EndfUtils/MFxxMTyyyParser/MF01MT451Parser.hpp"
#include "NuclearDataUtils/NuclearDataContainer/GeneralDataContainer.hpp"

namespace frendy
{
  class MF01MT451Converter
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

    public:
      //constructor
      MF01MT451Converter(void);

      //destructor
      virtual ~MF01MT451Converter(void);

      //GeneralDataContainer -> MF01MT451Parser
      void convert_frendy_to_endf_format( frendy::GeneralDataContainer& frendy_obj,
                                          frendy::MF01MT451Parser& endf_obj );

      //MF01MT451Parser -> GeneralDataContainer
      void convert_endf_format_to_frendy( frendy::MF01MT451Parser& endf_obj,
                                          frendy::GeneralDataContainer& frendy_obj );
  };
}

#endif //MF01MT451_CONVERTER_H
