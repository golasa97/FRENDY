#ifndef MF01MT452_CONVERTER_H
#define MF01MT452_CONVERTER_H

#include "EndfUtils/MFxxMTyyyParser/MF01MT452Parser.hpp"
#include "NuclearDataUtils/NuclearDataContainer/FissionDataContainer.hpp"

namespace frendy
{
  class MF01MT452Converter
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

    public:
      //constructor
      MF01MT452Converter(void);

      //destructor
      virtual ~MF01MT452Converter(void);

      //FissionDataContainer -> MF01MT452Parser
      void convert_frendy_to_endf_format( frendy::FissionDataContainer& frendy_obj,
                                          frendy::MF01MT452Parser& endf_obj );

      //MF01MT452Parser -> FissionDataContainer
      void convert_endf_format_to_frendy( frendy::MF01MT452Parser& endf_obj,
                                          frendy::FissionDataContainer& frendy_obj );
  };
}

#endif //MF01MT452_CONVERTER_H
