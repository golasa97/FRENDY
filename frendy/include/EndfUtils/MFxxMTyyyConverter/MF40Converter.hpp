#ifndef MF40_CONVERTER_H
#define MF40_CONVERTER_H

#include "EndfUtils/MFxxMTyyyParser/MF40Parser.hpp"
#include "NuclearDataUtils/CovarianceDataContainer/CovarianceRadioactiveProductDataContainer.hpp"

namespace frendy
{
  class MF40Converter
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

    public:
      //constructor
      MF40Converter(void);

      //destructor
      virtual ~MF40Converter(void);

      //CovarianceRadioactiveProductDataContainer -> MF40Parser
      void convert_frendy_to_endf_format( frendy::CovarianceRadioactiveProductDataContainer& frendy_obj,
                                          frendy::MF40Parser& endf_obj );

      //MF40Parser -> CovarianceRadioactiveProductDataContainer
      void convert_endf_format_to_frendy( frendy::MF40Parser& endf_obj,
                                          frendy::CovarianceRadioactiveProductDataContainer& frendy_obj );
  };
}

#endif //MF40_CONVERTER_H
