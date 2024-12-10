#ifndef MF32MT151_CONVERTER_REICH_MOORE_COMPACT_H
#define MF32MT151_CONVERTER_REICH_MOORE_COMPACT_H

#include "EndfUtils/MFxxMTyyyParser/MF32MT151Parser.hpp"
#include "NuclearDataUtils/CovarianceDataContainer/CovarianceResonanceData/ReichMooreCompactCovarianceDataContainer.hpp"

namespace frendy
{
  class MF32MT151ConverterReichMooreCompact
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

    public:
      //constructor
      MF32MT151ConverterReichMooreCompact(void);

      //destructor
      virtual ~MF32MT151ConverterReichMooreCompact(void);

      //ReichMooreCompactCovarianceDataContainer -> MF32MT151Parser
      void convert_frendy_to_endf_format( int& i, int& i_max, int& j, vector<int>& j_max,
        frendy::ReichMooreCompactCovarianceDataContainer& frendy_obj, frendy::MF32MT151Parser& endf_obj );

      //MF32MT151Parser -> ReichMooreCompactCovarianceDataContainer
      void convert_endf_format_to_frendy( int& i, int& j,
        frendy::MF32MT151Parser& endf_obj, frendy::ReichMooreCompactCovarianceDataContainer& frendy_obj );
  };
}

#endif //MF32MT151_CONVERTER_REICH_MOORE_COMPACT_H
