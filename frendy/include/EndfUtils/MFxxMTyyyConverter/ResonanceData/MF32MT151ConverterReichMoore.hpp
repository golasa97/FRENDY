#ifndef MF32MT151_CONVERTER_REICH_MOORE_H
#define MF32MT151_CONVERTER_REICH_MOORE_H

#include "EndfUtils/MFxxMTyyyParser/MF32MT151Parser.hpp"
#include "NuclearDataUtils/CovarianceDataContainer/CovarianceResonanceData/ReichMooreCovarianceDataContainer.hpp"

namespace frendy
{
  class MF32MT151ConverterReichMoore
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

    public:
      //constructor
      MF32MT151ConverterReichMoore(void);

      //destructor
      virtual ~MF32MT151ConverterReichMoore(void);

      //ReichMooreCovarianceDataContainer -> MF32MT151Parser
      void convert_frendy_to_endf_format( int& i, int& i_max, int& j, vector<int>& j_max,
        frendy::ReichMooreCovarianceDataContainer& frendy_obj, frendy::MF32MT151Parser& endf_obj );

      //MF32MT151Parser -> ReichMooreCovarianceDataContainer
      void convert_endf_format_to_frendy( int& i, int& j,
        frendy::MF32MT151Parser& endf_obj, frendy::ReichMooreCovarianceDataContainer& frendy_obj );
  };
}

#endif //MF32MT151_CONVERTER_REICH_MOORE_H
