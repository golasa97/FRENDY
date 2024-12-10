#ifndef MF05_CONVERTER_H
#define MF05_CONVERTER_H

#include "EndfUtils/MFxxMTyyyParser/MF05Parser.hpp"
#include "NuclearDataUtils/NuclearDataContainer/EnergyAngularDataContainer.hpp"

namespace frendy
{
  class MF05Converter
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

    public:
      //constructor
      MF05Converter(void);

      //destructor
      virtual ~MF05Converter(void);

      //EnergyAngularDataContainer -> MF05Parser
      void convert_frendy_to_endf_format( frendy::EnergyAngularDataContainer& frendy_obj,
                                          frendy::MF05Parser& endf_obj );

      //MF05Parser -> EnergyAngularDataContainer
      void convert_endf_format_to_frendy( frendy::MF05Parser& endf_obj,
                                          frendy::EnergyAngularDataContainer& frendy_obj );
  };
}

#endif //MF05_CONVERTER_H
