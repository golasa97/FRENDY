#ifndef MF13_CONVERTER_H
#define MF13_CONVERTER_H

#include "EndfUtils/MFxxMTyyyParser/MF13Parser.hpp"
#include "NuclearDataUtils/NuclearDataContainer/PhotonDataContainer.hpp"

namespace frendy
{
  class MF13Converter
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

    public:
      //constructor
      MF13Converter(void);

      //destructor
      virtual ~MF13Converter(void);

      //PhotonDataContainer -> MF13Parser
      void convert_frendy_to_endf_format( frendy::PhotonDataContainer& frendy_obj,
                                          frendy::MF13Parser& endf_obj );

      //MF13Parser -> PhotonDataContainer
      void convert_endf_format_to_frendy( frendy::MF13Parser& endf_obj,
                                          frendy::PhotonDataContainer& frendy_obj );
  };
}

#endif //MF13_CONVERTER_H
