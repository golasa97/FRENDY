#ifndef MF02MT151_CONVERTER_ADLER_ADLER_H
#define MF02MT151_CONVERTER_ADLER_ADLER_H

#include "EndfUtils/MFxxMTyyyParser/MF02MT151Parser.hpp"
#include "NuclearDataUtils/NuclearDataContainer/ResonanceData/AdlerAdlerDataContainer.hpp"

namespace frendy
{
  class MF02MT151ConverterAdlerAdler
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

    public:
      //constructor
      MF02MT151ConverterAdlerAdler(void);

      //destructor
      virtual ~MF02MT151ConverterAdlerAdler(void);

      //AdlerAdlerDataContainer -> MF02MT151Parser
      void convert_frendy_to_endf_format( int& i, int& i_max, int& j, vector<int>& j_max,
        frendy::AdlerAdlerDataContainer& frendy_obj, frendy::MF02MT151Parser& endf_obj );

      //MF02MT151Parser -> AdlerAdlerDataContainer
      void convert_endf_format_to_frendy( int& i, int& j,
        frendy::MF02MT151Parser& endf_obj, frendy::AdlerAdlerDataContainer& frendy_obj );
  };
}

#endif //MF02MT151_CONVERTER_ADLER_ADLER_H
