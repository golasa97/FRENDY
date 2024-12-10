#ifndef MF10_WRITER_H
#define MF10_WRITER_H

#include "EndfUtils/EndfFileWriter/EndfFileWriter.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF10Parser.hpp"

namespace frendy
{
  class MF10Writer
  {
    private:
      frendy::ErrorManager    err_obj;
      frendy::VectorClearer   clr_obj;
      frendy::EndfFileWriter  efw_obj;

      frendy::MF10Parser      par_obj;
      vector<string>          text;

      static const Integer mf_no  =  10;

      void write_endf();

    public:
      //constructor
      MF10Writer(void);

      //destructor
      virtual ~MF10Writer(void);

      void clear();

      vector<string> get_endf_text_data(frendy::MF10Parser& mf10parser_obj);
  };
}

#endif // MF10_WRITER_H
