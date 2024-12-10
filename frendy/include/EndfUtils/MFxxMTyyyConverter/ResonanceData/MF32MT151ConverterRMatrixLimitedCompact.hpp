#ifndef MF32MT151_CONVERTER_R_MATRIX_LIMITED_COMPACT_H
#define MF32MT151_CONVERTER_R_MATRIX_LIMITED_COMPACT_H

#include "EndfUtils/MFxxMTyyyParser/MF32MT151Parser.hpp"
#include "NuclearDataUtils/CovarianceDataContainer/CovarianceResonanceData/RMatrixLimitedCompactCovarianceDataContainer.hpp"

namespace frendy
{
  class MF32MT151ConverterRMatrixLimitedCompact
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

    public:
      //constructor
      MF32MT151ConverterRMatrixLimitedCompact(void);

      //destructor
      virtual ~MF32MT151ConverterRMatrixLimitedCompact(void);

      //RMatrixLimitedCompactCovarianceDataContainer -> MF32MT151Parser
      void convert_frendy_to_endf_format( int& i, int& i_max, int& j, vector<int>& j_max,
        frendy::RMatrixLimitedCompactCovarianceDataContainer& frendy_obj, frendy::MF32MT151Parser& endf_obj );

      //MF32MT151Parser -> RMatrixLimitedCompactCovarianceDataContainer
      void convert_endf_format_to_frendy( int& i, int& j,
        frendy::MF32MT151Parser& endf_obj, frendy::RMatrixLimitedCompactCovarianceDataContainer& frendy_obj );
  };
}

#endif //MF32MT151_CONVERTER_R_MATRIX_LIMITED_COMPACT_H
