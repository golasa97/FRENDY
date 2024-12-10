#ifndef MF01MT458_CONVERTER_H
#define MF01MT458_CONVERTER_H

#include "EndfUtils/MFxxMTyyyParser/MF01MT458Parser.hpp"
#include "NuclearDataUtils/NuclearDataContainer/FissionDataContainer.hpp"

namespace frendy
{
  class MF01MT458Converter
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

    public:
      //constructor
      MF01MT458Converter(void);

      //destructor
      virtual ~MF01MT458Converter(void);

      //FissionDataContainer -> MF01MT458Parser
      void convert_frendy_to_endf_format( frendy::FissionDataContainer& frendy_obj,
                                          frendy::MF01MT458Parser& endf_obj );

      //MF01MT458Parser -> FissionDataContainer
      void convert_endf_format_to_frendy( frendy::MF01MT458Parser& endf_obj,
                                          frendy::FissionDataContainer& frendy_obj );
  };
}

#endif //MF01MT458_CONVERTER_H
