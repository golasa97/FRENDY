#ifndef MF02MT151_CONVERTER_REICH_MOORE_H
#define MF02MT151_CONVERTER_REICH_MOORE_H

#include "EndfUtils/MFxxMTyyyParser/MF02MT151Parser.hpp"
#include "NuclearDataUtils/NuclearDataContainer/ResonanceData/ReichMooreDataContainer.hpp"

namespace frendy
{
  class MF02MT151ConverterReichMoore
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

    public:
      //constructor
      MF02MT151ConverterReichMoore(void);

      //destructor
      virtual ~MF02MT151ConverterReichMoore(void);

      //ReichMooreDataContainer -> MF02MT151Parser
      void convert_frendy_to_endf_format( int& i, int& i_max, int& j, vector<int>& j_max,
        frendy::ReichMooreDataContainer& frendy_obj, frendy::MF02MT151Parser& endf_obj );

      //MF02MT151Parser -> ReichMooreDataContainer
      void convert_endf_format_to_frendy( int& i, int& j,
        frendy::MF02MT151Parser& endf_obj, frendy::ReichMooreDataContainer& frendy_obj );
  };
}

#endif //MF02MT151_CONVERTER_REICH_MOORE_H
