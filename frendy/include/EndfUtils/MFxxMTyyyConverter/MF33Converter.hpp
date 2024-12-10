#ifndef MF33_CONVERTER_H
#define MF33_CONVERTER_H

#include "EndfUtils/MFxxMTyyyParser/MF33Parser.hpp"
#include "NuclearDataUtils/CovarianceDataContainer/CovarianceCrossSectionDataContainer.hpp"

namespace frendy
{
  class MF33Converter
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

    public:
      //constructor
      MF33Converter(void);

      //destructor
      virtual ~MF33Converter(void);

      //CovarianceCrossSectionDataContainer -> MF33Parser
      void convert_frendy_to_endf_format( frendy::CovarianceCrossSectionDataContainer& frendy_obj,
                                          frendy::MF33Parser& endf_obj );

      //MF33Parser -> CovarianceCrossSectionDataContainer
      void convert_endf_format_to_frendy( frendy::MF33Parser& endf_obj,
                                          frendy::CovarianceCrossSectionDataContainer& frendy_obj );
  };
}

#endif //MF33_CONVERTER_H
