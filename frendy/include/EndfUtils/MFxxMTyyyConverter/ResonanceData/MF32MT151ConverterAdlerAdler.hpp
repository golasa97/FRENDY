#ifndef MF32MT151_CONVERTER_ADLER_ADLER_H
#define MF32MT151_CONVERTER_ADLER_ADLER_H

#include "EndfUtils/MFxxMTyyyParser/MF32MT151Parser.hpp"
#include "NuclearDataUtils/CovarianceDataContainer/CovarianceResonanceData/AdlerAdlerCovarianceDataContainer.hpp"

namespace frendy
{
  class MF32MT151ConverterAdlerAdler
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

    public:
      //constructor
      MF32MT151ConverterAdlerAdler(void);

      //destructor
      virtual ~MF32MT151ConverterAdlerAdler(void);

      //AdlerAdlerCovarianceDataContainer -> MF32MT151Parser
      void convert_frendy_to_endf_format( int& i, int& i_max, int& j, vector<int>& j_max,
        frendy::AdlerAdlerCovarianceDataContainer& frendy_obj, frendy::MF32MT151Parser& endf_obj );

      //MF32MT151Parser -> AdlerAdlerCovarianceDataContainer
      void convert_endf_format_to_frendy( int& i, int& j,
        frendy::MF32MT151Parser& endf_obj, frendy::AdlerAdlerCovarianceDataContainer& frendy_obj );
  };
}

#endif //MF32MT151_CONVERTER_ADLER_ADLER_H
