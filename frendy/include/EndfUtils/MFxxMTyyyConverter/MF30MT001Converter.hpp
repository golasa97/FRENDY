#ifndef MF30MT001_CONVERTER_H
#define MF30MT001_CONVERTER_H

#include "EndfUtils/MFxxMTyyyParser/MF30MT001Parser.hpp"
#include "NuclearDataUtils/CovarianceDataContainer/CovarianceGeneralDataContainer.hpp"

namespace frendy
{
  class MF30MT001Converter
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

    public:
      //constructor
      MF30MT001Converter(void);

      //destructor
      virtual ~MF30MT001Converter(void);

      //CovarianceGeneralDataContainer -> MF30MT001Parser
      void convert_frendy_to_endf_format( frendy::CovarianceGeneralDataContainer& frendy_obj,
                                          frendy::MF30MT001Parser& endf_obj );

      //MF30MT001Parser -> CovarianceGeneralDataContainer
      void convert_endf_format_to_frendy( frendy::MF30MT001Parser& endf_obj,
                                          frendy::CovarianceGeneralDataContainer& frendy_obj );
  };
}

#endif //MF30MT001_CONVERTER_H
