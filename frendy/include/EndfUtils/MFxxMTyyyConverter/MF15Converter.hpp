#ifndef MF15_CONVERTER_H
#define MF15_CONVERTER_H

#include "EndfUtils/MFxxMTyyyParser/MF15Parser.hpp"
#include "NuclearDataUtils/NuclearDataContainer/PhotonDataContainer.hpp"

namespace frendy
{
  class MF15Converter
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

    public:
      //constructor
      MF15Converter(void);

      //destructor
      virtual ~MF15Converter(void);

      //PhotonDataContainer -> MF15Parser
      void convert_frendy_to_endf_format( frendy::PhotonDataContainer& frendy_obj,
                                          frendy::MF15Parser& endf_obj );

      //MF15Parser -> PhotonDataContainer
      void convert_endf_format_to_frendy( frendy::MF15Parser& endf_obj,
                                          frendy::PhotonDataContainer& frendy_obj );
  };
}

#endif //MF15_CONVERTER_H
