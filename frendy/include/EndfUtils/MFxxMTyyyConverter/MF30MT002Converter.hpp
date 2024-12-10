#ifndef MF30MT002_CONVERTER_H
#define MF30MT002_CONVERTER_H

#include "EndfUtils/MFxxMTyyyParser/MF30MT002Parser.hpp"
#include "NuclearDataUtils/CovarianceDataContainer/CovarianceGeneralDataContainer.hpp"

namespace frendy
{
  class MF30MT002Converter
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

    public:
      //constructor
      MF30MT002Converter(void);

      //destructor
      virtual ~MF30MT002Converter(void);

      //CovarianceGeneralDataContainer -> MF30MT002Parser
      void convert_frendy_to_endf_format( frendy::CovarianceGeneralDataContainer& frendy_obj,
                                          frendy::MF30MT002Parser& endf_obj );

      //MF30MT002Parser -> CovarianceGeneralDataContainer
      void convert_endf_format_to_frendy( frendy::MF30MT002Parser& endf_obj,
                                          frendy::CovarianceGeneralDataContainer& frendy_obj );
  };
}

#endif //MF30MT002_CONVERTER_H
