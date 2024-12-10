#ifndef MF34_CONVERTER_H
#define MF34_CONVERTER_H

#include "EndfUtils/MFxxMTyyyParser/MF34Parser.hpp"
#include "NuclearDataUtils/CovarianceDataContainer/CovarianceEnergyAngularDataContainer.hpp"

namespace frendy
{
  class MF34Converter
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

    public:
      //constructor
      MF34Converter(void);

      //destructor
      virtual ~MF34Converter(void);

      //CovarianceEnergyAngularDataContainer -> MF34Parser
      void convert_frendy_to_endf_format( frendy::CovarianceEnergyAngularDataContainer& frendy_obj,
                                          frendy::MF34Parser& endf_obj );

      //MF34Parser -> CovarianceEnergyAngularDataContainer
      void convert_endf_format_to_frendy( frendy::MF34Parser& endf_obj,
                                          frendy::CovarianceEnergyAngularDataContainer& frendy_obj );
  };
}

#endif //MF34_CONVERTER_H
