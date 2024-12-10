#ifndef MF08MT457_CONVERTER_H
#define MF08MT457_CONVERTER_H

#include "EndfUtils/MFxxMTyyyParser/MF08MT457Parser.hpp"
#include "NuclearDataUtils/NuclearDataContainer/GeneralDataContainer.hpp"

namespace frendy
{
  class MF08MT457Converter
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

    public:
      //constructor
      MF08MT457Converter(void);

      //destructor
      virtual ~MF08MT457Converter(void);

      //GeneralDataContainer -> MF08MT457Parser
      void convert_frendy_to_endf_format( frendy::GeneralDataContainer& frendy_obj,
                                          frendy::MF08MT457Parser& endf_obj );

      //MF08MT457Parser -> GeneralDataContainer
      void convert_endf_format_to_frendy( frendy::MF08MT457Parser& endf_obj,
                                          frendy::GeneralDataContainer& frendy_obj );
  };
}

#endif //MF08MT457_CONVERTER_H
