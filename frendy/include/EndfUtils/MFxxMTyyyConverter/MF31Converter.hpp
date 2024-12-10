#ifndef MF31_CONVERTER_H
#define MF31_CONVERTER_H

#include "EndfUtils/MFxxMTyyyParser/MF31Parser.hpp"
#include "NuclearDataUtils/CovarianceDataContainer/CovarianceFissionDataContainer.hpp"

namespace frendy
{
  class MF31Converter
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

    public:
      //constructor
      MF31Converter(void);

      //destructor
      virtual ~MF31Converter(void);

      //CovarianceFissionDataContainer -> MF31Parser
      void convert_frendy_to_endf_format( frendy::CovarianceFissionDataContainer& frendy_obj,
                                          frendy::MF31Parser& endf_obj );

      //MF31Parser -> CovarianceFissionDataContainer
      void convert_endf_format_to_frendy( frendy::MF31Parser& endf_obj,
                                          frendy::CovarianceFissionDataContainer& frendy_obj );
  };
}

#endif //MF31_CONVERTER_H
