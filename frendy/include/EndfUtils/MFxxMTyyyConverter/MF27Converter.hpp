#ifndef MF27_CONVERTER_H
#define MF27_CONVERTER_H

#include "EndfUtils/MFxxMTyyyParser/MF27Parser.hpp"
#include "NuclearDataUtils/NuclearDataContainer/OtherNuclearDataContainer.hpp"

namespace frendy
{
  class MF27Converter
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

    public:
      //constructor
      MF27Converter(void);

      //destructor
      virtual ~MF27Converter(void);

      //OtherNuclearDataContainer -> MF27Parser
      void convert_frendy_to_endf_format( frendy::OtherNuclearDataContainer& frendy_obj,
                                          frendy::MF27Parser& endf_obj );

      //MF27Parser -> OtherNuclearDataContainer
      void convert_endf_format_to_frendy( frendy::MF27Parser& endf_obj,
                                          frendy::OtherNuclearDataContainer& frendy_obj );
  };
}

#endif //MF27_CONVERTER_H
