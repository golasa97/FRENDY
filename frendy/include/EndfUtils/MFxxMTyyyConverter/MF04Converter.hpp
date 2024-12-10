#ifndef MF04_CONVERTER_H
#define MF04_CONVERTER_H

#include "EndfUtils/MFxxMTyyyParser/MF04Parser.hpp"
#include "NuclearDataUtils/NuclearDataContainer/EnergyAngularDataContainer.hpp"

namespace frendy
{
  class MF04Converter
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

    public:
      //constructor
      MF04Converter(void);

      //destructor
      virtual ~MF04Converter(void);

      //EnergyAngularDataContainer -> MF04Parser
      void convert_frendy_to_endf_format( frendy::EnergyAngularDataContainer& frendy_obj,
                                          frendy::MF04Parser& endf_obj );

      //MF04Parser -> EnergyAngularDataContainer
      void convert_endf_format_to_frendy( frendy::MF04Parser& endf_obj,
                                          frendy::EnergyAngularDataContainer& frendy_obj );
  };
}

#endif //MF04_CONVERTER_H
