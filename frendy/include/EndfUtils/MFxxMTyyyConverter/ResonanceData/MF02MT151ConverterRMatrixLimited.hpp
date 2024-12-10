#ifndef MF02MT151_CONVERTER_R_MATRIX_LIMITED_H
#define MF02MT151_CONVERTER_R_MATRIX_LIMITED_H

#include "EndfUtils/MFxxMTyyyParser/MF02MT151Parser.hpp"
#include "NuclearDataUtils/NuclearDataContainer/ResonanceData/RMatrixLimitedDataContainer.hpp"

namespace frendy
{
  class MF02MT151ConverterRMatrixLimited
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

    public:
      //constructor
      MF02MT151ConverterRMatrixLimited(void);

      //destructor
      virtual ~MF02MT151ConverterRMatrixLimited(void);

      //RMatrixLimitedDataContainer -> MF02MT151Parser
      void convert_frendy_to_endf_format( int& i, int& i_max, int& j, vector<int>& j_max,
        frendy::RMatrixLimitedDataContainer& frendy_obj, frendy::MF02MT151Parser& endf_obj );

      //MF02MT151Parser -> RMatrixLimitedDataContainer
      void convert_endf_format_to_frendy( int& i, int& j,
        frendy::MF02MT151Parser& endf_obj, frendy::RMatrixLimitedDataContainer& frendy_obj );
  };
}

#endif //MF02MT151_CONVERTER_R_MATRIX_LIMITED_H
