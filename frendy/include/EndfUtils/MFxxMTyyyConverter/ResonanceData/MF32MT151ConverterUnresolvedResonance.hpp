#ifndef MF32MT151_CONVERTER_UNRESOLVED_RESONANCE_H
#define MF32MT151_CONVERTER_UNRESOLVED_RESONANCE_H

#include "EndfUtils/MFxxMTyyyParser/MF32MT151Parser.hpp"
#include "NuclearDataUtils/CovarianceDataContainer/CovarianceResonanceData/UnresolvedResonanceCovarianceDataContainer.hpp"

namespace frendy
{
  class MF32MT151ConverterUnresolvedResonance
  {
    private:
      ErrorManager  err_obj;
      VectorClearer clr_obj;

    public:
      //constructor
      MF32MT151ConverterUnresolvedResonance(void);

      //destructor
      virtual ~MF32MT151ConverterUnresolvedResonance(void);

      //UnresolvedResonanceCovarianceDataContainer -> MF32MT151Parser
      void convert_frendy_to_endf_format( int& i, int& i_max, int& j, vector<int>& j_max,
        frendy::UnresolvedResonanceCovarianceDataContainer& frendy_obj, frendy::MF32MT151Parser& endf_obj );

      //MF32MT151Parser -> UnresolvedResonanceCovarianceDataContainer
      void convert_endf_format_to_frendy( int& i, int& j,
        frendy::MF32MT151Parser& endf_obj, frendy::UnresolvedResonanceCovarianceDataContainer& frendy_obj );
  };
}

#endif //MF32MT151_CONVERTER_UNRESOLVED_RESONANCE_H
