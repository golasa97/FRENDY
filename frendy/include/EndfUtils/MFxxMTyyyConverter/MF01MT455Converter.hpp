#ifndef MF01MT455_CONVERTER_H
#define MF01MT455_CONVERTER_H

#include "EndfUtils/MFxxMTyyyParser/MF01MT455Parser.hpp"
#include "NuclearDataUtils/NuclearDataContainer/FissionDataContainer.hpp"

namespace frendy
{
  class MF01MT455Converter
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

    public:
      //constructor
      MF01MT455Converter(void);

      //destructor
      virtual ~MF01MT455Converter(void);

      //FissionDataContainer -> MF01MT455Parser
      void convert_frendy_to_endf_format( frendy::FissionDataContainer& frendy_obj,
                                          frendy::MF01MT455Parser& endf_obj );

      //MF01MT455Parser -> FissionDataContainer
      void convert_endf_format_to_frendy( frendy::MF01MT455Parser& endf_obj,
                                          frendy::FissionDataContainer& frendy_obj );
  };
}

#endif //MF01MT455_CONVERTER_H
