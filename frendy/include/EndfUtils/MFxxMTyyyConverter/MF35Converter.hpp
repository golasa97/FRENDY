#ifndef MF35_CONVERTER_H
#define MF35_CONVERTER_H

#include "EndfUtils/MFxxMTyyyParser/MF35Parser.hpp"
#include "NuclearDataUtils/CovarianceDataContainer/CovarianceEnergyAngularDataContainer.hpp"

namespace frendy
{
  class MF35Converter
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

    public:
      //constructor
      MF35Converter(void);

      //destructor
      virtual ~MF35Converter(void);

      //CovarianceEnergyAngularDataContainer -> MF35Parser
      void convert_frendy_to_endf_format( frendy::CovarianceEnergyAngularDataContainer& frendy_obj,
                                          frendy::MF35Parser& endf_obj );

      //MF35Parser -> CovarianceEnergyAngularDataContainer
      void convert_endf_format_to_frendy( frendy::MF35Parser& endf_obj,
                                          frendy::CovarianceEnergyAngularDataContainer& frendy_obj );
  };
}

#endif //MF35_CONVERTER_H
