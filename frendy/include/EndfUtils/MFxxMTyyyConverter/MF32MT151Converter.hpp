#ifndef MF32MT151_CONVERTER_H
#define MF32MT151_CONVERTER_H

#include "EndfUtils/MFxxMTyyyParser/MF32MT151Parser.hpp"
#include "NuclearDataUtils/CovarianceDataContainer/CovarianceResonanceDataContainer.hpp"
#include "EndfUtils/MFxxMTyyyConverter/ResonanceData/MF32MT151ConverterCompatibleResolvedResonance.hpp"
#include "EndfUtils/MFxxMTyyyConverter/ResonanceData/MF32MT151ConverterBreitWigner.hpp"
#include "EndfUtils/MFxxMTyyyConverter/ResonanceData/MF32MT151ConverterBreitWignerCompact.hpp"
#include "EndfUtils/MFxxMTyyyConverter/ResonanceData/MF32MT151ConverterReichMoore.hpp"
#include "EndfUtils/MFxxMTyyyConverter/ResonanceData/MF32MT151ConverterReichMooreCompact.hpp"
#include "EndfUtils/MFxxMTyyyConverter/ResonanceData/MF32MT151ConverterAdlerAdler.hpp"
#include "EndfUtils/MFxxMTyyyConverter/ResonanceData/MF32MT151ConverterRMatrixLimited.hpp"
#include "EndfUtils/MFxxMTyyyConverter/ResonanceData/MF32MT151ConverterRMatrixLimitedCompact.hpp"
#include "EndfUtils/MFxxMTyyyConverter/ResonanceData/MF32MT151ConverterUnresolvedResonance.hpp"

namespace frendy
{
  class MF32MT151Converter
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

    public:
      //constructor
      MF32MT151Converter(void);

      //destructor
      virtual ~MF32MT151Converter(void);

      //CovarianceResonanceDataContainer -> MF32MT151Parser
      void convert_frendy_to_endf_format( frendy::CovarianceResonanceDataContainer& frendy_obj,
                                          frendy::MF32MT151Parser& endf_obj );

      //MF32MT151Parser -> CovarianceResonanceDataContainer
      void convert_endf_format_to_frendy( frendy::MF32MT151Parser& endf_obj,
                                          frendy::CovarianceResonanceDataContainer& frendy_obj );
  };
}

#endif //MF32MT151_CONVERTER_H
