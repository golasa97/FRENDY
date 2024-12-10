#ifndef MF28_CONVERTER_H
#define MF28_CONVERTER_H

#include "EndfUtils/MFxxMTyyyParser/MF28Parser.hpp"
#include "NuclearDataUtils/NuclearDataContainer/OtherNuclearDataContainer.hpp"

namespace frendy
{
  class MF28Converter
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

    public:
      //constructor
      MF28Converter(void);

      //destructor
      virtual ~MF28Converter(void);

      //OtherNuclearDataContainer -> MF28Parser
      void convert_frendy_to_endf_format( frendy::OtherNuclearDataContainer& frendy_obj,
                                          frendy::MF28Parser& endf_obj );

      //MF28Parser -> OtherNuclearDataContainer
      void convert_endf_format_to_frendy( frendy::MF28Parser& endf_obj,
                                          frendy::OtherNuclearDataContainer& frendy_obj );
  };
}

#endif //MF28_CONVERTER_H
