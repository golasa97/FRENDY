#ifndef MF07MT002_CONVERTER_H
#define MF07MT002_CONVERTER_H

#include "EndfUtils/MFxxMTyyyParser/MF07MT002Parser.hpp"
#include "NuclearDataUtils/NuclearDataContainer/ThermalScatterDataContainer.hpp"

namespace frendy
{
  class MF07MT002Converter
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

    public:
      //constructor
      MF07MT002Converter(void);

      //destructor
      virtual ~MF07MT002Converter(void);

      //ThermalScatterDataContainer -> MF07MT002Parser
      void convert_frendy_to_endf_format( frendy::ThermalScatterDataContainer& frendy_obj,
                                          frendy::MF07MT002Parser& endf_obj );

      //MF07MT002Parser -> ThermalScatterDataContainer
      void convert_endf_format_to_frendy( frendy::MF07MT002Parser& endf_obj,
                                          frendy::ThermalScatterDataContainer& frendy_obj );
  };
}

#endif //MF07MT002_CONVERTER_H
