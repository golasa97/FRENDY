#ifndef MF23_CONVERTER_H
#define MF23_CONVERTER_H

#include "EndfUtils/MFxxMTyyyParser/MF23Parser.hpp"
#include "NuclearDataUtils/NuclearDataContainer/PhotonDataContainer.hpp"

namespace frendy
{
  class MF23Converter
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

    public:
      //constructor
      MF23Converter(void);

      //destructor
      virtual ~MF23Converter(void);

      //PhotonDataContainer -> MF23Parser
      void convert_frendy_to_endf_format( frendy::PhotonDataContainer& frendy_obj,
                                          frendy::MF23Parser& endf_obj );

      //MF23Parser -> PhotonDataContainer
      void convert_endf_format_to_frendy( frendy::MF23Parser& endf_obj,
                                          frendy::PhotonDataContainer& frendy_obj );
  };
}

#endif //MF23_CONVERTER_H
