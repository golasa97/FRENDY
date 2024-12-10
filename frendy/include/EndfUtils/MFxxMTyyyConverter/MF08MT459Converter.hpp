#ifndef MF08MT459_CONVERTER_H
#define MF08MT459_CONVERTER_H

#include "EndfUtils/MFxxMTyyyParser/MF08MT459Parser.hpp"
#include "NuclearDataUtils/NuclearDataContainer/FissionDataContainer.hpp"

namespace frendy
{
  class MF08MT459Converter
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

    public:
      //constructor
      MF08MT459Converter(void);

      //destructor
      virtual ~MF08MT459Converter(void);

      //FissionDataContainer -> MF08MT459Parser
      void convert_frendy_to_endf_format( frendy::FissionDataContainer& frendy_obj,
                                          frendy::MF08MT459Parser& endf_obj );

      //MF08MT459Parser -> FissionDataContainer
      void convert_endf_format_to_frendy( frendy::MF08MT459Parser& endf_obj,
                                          frendy::FissionDataContainer& frendy_obj );
  };
}

#endif //MF08MT459_CONVERTER_H
