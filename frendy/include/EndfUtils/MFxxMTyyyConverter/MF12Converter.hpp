#ifndef MF12_CONVERTER_H
#define MF12_CONVERTER_H

#include "EndfUtils/MFxxMTyyyParser/MF12Parser.hpp"
#include "NuclearDataUtils/NuclearDataContainer/PhotonDataContainer.hpp"

namespace frendy
{
  class MF12Converter
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

    public:
      //constructor
      MF12Converter(void);

      //destructor
      virtual ~MF12Converter(void);

      //PhotonDataContainer -> MF12Parser
      void convert_frendy_to_endf_format( frendy::PhotonDataContainer& frendy_obj,
                                          frendy::MF12Parser& endf_obj );

      //MF12Parser -> PhotonDataContainer
      void convert_endf_format_to_frendy( frendy::MF12Parser& endf_obj,
                                          frendy::PhotonDataContainer& frendy_obj );
  };
}

#endif //MF12_CONVERTER_H
