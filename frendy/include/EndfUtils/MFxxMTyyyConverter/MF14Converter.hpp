#ifndef MF14_CONVERTER_H
#define MF14_CONVERTER_H

#include "EndfUtils/MFxxMTyyyParser/MF14Parser.hpp"
#include "NuclearDataUtils/NuclearDataContainer/PhotonDataContainer.hpp"

namespace frendy
{
  class MF14Converter
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

    public:
      //constructor
      MF14Converter(void);

      //destructor
      virtual ~MF14Converter(void);

      //PhotonDataContainer -> MF14Parser
      void convert_frendy_to_endf_format( frendy::PhotonDataContainer& frendy_obj,
                                          frendy::MF14Parser& endf_obj );

      //MF14Parser -> PhotonDataContainer
      void convert_endf_format_to_frendy( frendy::MF14Parser& endf_obj,
                                          frendy::PhotonDataContainer& frendy_obj );
  };
}

#endif //MF14_CONVERTER_H
