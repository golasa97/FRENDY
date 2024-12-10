#ifndef MF32MT151_CONVERTER_BREIT_WIGNER_H
#define MF32MT151_CONVERTER_BREIT_WIGNER_H

#include "EndfUtils/MFxxMTyyyParser/MF32MT151Parser.hpp"
#include "NuclearDataUtils/CovarianceDataContainer/CovarianceResonanceData/BreitWignerCovarianceDataContainer.hpp"

namespace frendy
{
  class MF32MT151ConverterBreitWigner
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

    public:
      //constructor
      MF32MT151ConverterBreitWigner(void);

      //destructor
      virtual ~MF32MT151ConverterBreitWigner(void);

      //BreitWignerCovarianceDataContainer -> MF32MT151Parser
      void convert_frendy_to_endf_format( int& i, int& i_max, int& j, vector<int>& j_max,
        frendy::BreitWignerCovarianceDataContainer& frendy_obj, frendy::MF32MT151Parser& endf_obj );

      //MF32MT151Parser -> BreitWignerCovarianceDataContainer
      void convert_endf_format_to_frendy( int& i, int& j,
        frendy::MF32MT151Parser& endf_obj, frendy::BreitWignerCovarianceDataContainer& frendy_obj );
  };
}

#endif //MF32MT151_CONVERTER_BREIT_WIGNER_H
