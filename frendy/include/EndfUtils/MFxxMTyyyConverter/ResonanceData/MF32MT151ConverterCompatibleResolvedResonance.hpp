#ifndef MF32MT151_CONVERTER_COMPATIBLE_RESOLVED_RESONANCE_H
#define MF32MT151_CONVERTER_COMPATIBLE_RESOLVED_RESONANCE_H

#include "EndfUtils/MFxxMTyyyParser/MF32MT151Parser.hpp"
#include "NuclearDataUtils/CovarianceDataContainer/CovarianceResonanceData/CompatibleResolvedResonanceDataContainer.hpp"

namespace frendy
{
  class MF32MT151ConverterCompatibleResolvedResonance
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

    public:
      //constructor
      MF32MT151ConverterCompatibleResolvedResonance(void);

      //destructor
      virtual ~MF32MT151ConverterCompatibleResolvedResonance(void);

      //CompatibleResolvedResonanceDataContainer -> MF32MT151Parser
      void convert_frendy_to_endf_format( int& i, int& i_max, int& j, vector<int>& j_max,
        frendy::CompatibleResolvedResonanceDataContainer& frendy_obj, frendy::MF32MT151Parser& endf_obj );

      //MF32MT151Parser -> CompatibleResolvedResonanceDataContainer
      void convert_endf_format_to_frendy( int& i, int& j,
        frendy::MF32MT151Parser& endf_obj, frendy::CompatibleResolvedResonanceDataContainer& frendy_obj );
  };
}

#endif //MF32MT151_CONVERTER_COMPATIBLE_RESOLVED_RESONANCE_H
