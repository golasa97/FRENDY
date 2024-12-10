#ifndef MF02MT151_CONVERTER_H
#define MF02MT151_CONVERTER_H

#include "EndfUtils/MFxxMTyyyParser/MF02MT151Parser.hpp"
#include "NuclearDataUtils/NuclearDataContainer/ResonanceDataContainer.hpp"
#include "EndfUtils/MFxxMTyyyConverter/ResonanceData/MF02MT151ConverterBreitWigner.hpp"
#include "EndfUtils/MFxxMTyyyConverter/ResonanceData/MF02MT151ConverterReichMoore.hpp"
#include "EndfUtils/MFxxMTyyyConverter/ResonanceData/MF02MT151ConverterAdlerAdler.hpp"
#include "EndfUtils/MFxxMTyyyConverter/ResonanceData/MF02MT151ConverterRMatrixLimited.hpp"
#include "EndfUtils/MFxxMTyyyConverter/ResonanceData/MF02MT151ConverterUnresolved.hpp"

namespace frendy
{
  class MF02MT151Converter
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

    public:
      //constructor
      MF02MT151Converter(void);

      //destructor
      virtual ~MF02MT151Converter(void);

      //ResonanceDataContainer -> MF02MT151Parser
      void convert_frendy_to_endf_format( frendy::ResonanceDataContainer& frendy_obj,
                                          frendy::MF02MT151Parser& endf_obj );

      //MF02MT151Parser -> ResonanceDataContainer
      void convert_endf_format_to_frendy( frendy::MF02MT151Parser& endf_obj,
                                          frendy::ResonanceDataContainer& frendy_obj );
  };
}

#endif //MF02MT151_CONVERTER_H
