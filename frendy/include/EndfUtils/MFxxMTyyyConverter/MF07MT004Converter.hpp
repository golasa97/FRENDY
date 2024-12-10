#ifndef MF07MT004_CONVERTER_H
#define MF07MT004_CONVERTER_H

#include "EndfUtils/MFxxMTyyyParser/MF07MT004Parser.hpp"
#include "NuclearDataUtils/NuclearDataContainer/ThermalScatterDataContainer.hpp"

namespace frendy
{
  class MF07MT004Converter
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

    public:
      //constructor
      MF07MT004Converter(void);

      //destructor
      virtual ~MF07MT004Converter(void);

      //ThermalScatterDataContainer -> MF07MT004Parser
      void convert_frendy_to_endf_format( frendy::ThermalScatterDataContainer& frendy_obj,
                                          frendy::MF07MT004Parser& endf_obj );

      //MF07MT004Parser -> ThermalScatterDataContainer
      void convert_endf_format_to_frendy( frendy::MF07MT004Parser& endf_obj,
                                          frendy::ThermalScatterDataContainer& frendy_obj );
  };
}

#endif //MF07MT004_CONVERTER_H
