#ifndef MF08MT454_CONVERTER_H
#define MF08MT454_CONVERTER_H

#include "EndfUtils/MFxxMTyyyParser/MF08MT454Parser.hpp"
#include "NuclearDataUtils/NuclearDataContainer/FissionDataContainer.hpp"

namespace frendy
{
  class MF08MT454Converter
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

    public:
      //constructor
      MF08MT454Converter(void);

      //destructor
      virtual ~MF08MT454Converter(void);

      //FissionDataContainer -> MF08MT454Parser
      void convert_frendy_to_endf_format( frendy::FissionDataContainer& frendy_obj,
                                          frendy::MF08MT454Parser& endf_obj );

      //MF08MT454Parser -> FissionDataContainer
      void convert_endf_format_to_frendy( frendy::MF08MT454Parser& endf_obj,
                                          frendy::FissionDataContainer& frendy_obj );
  };
}

#endif //MF08MT454_CONVERTER_H
