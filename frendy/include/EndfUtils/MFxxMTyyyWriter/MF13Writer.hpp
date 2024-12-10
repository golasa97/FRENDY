#ifndef MF13_WRITER_H
#define MF13_WRITER_H

#include "EndfUtils/EndfFileWriter/EndfFileWriter.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF13Parser.hpp"

namespace frendy
{
  class MF13Writer
  {
    private:
      frendy::ErrorManager    err_obj;
      frendy::VectorClearer   clr_obj;
      frendy::EndfFileWriter  efw_obj;

      frendy::MF13Parser      par_obj;
      vector<string>          text;

      static const Integer mf_no  =  13;

      void write_endf();

    public:
      //constructor
      MF13Writer(void);

      //destructor
      virtual ~MF13Writer(void);

      void clear();

      vector<string> get_endf_text_data(frendy::MF13Parser& mf13parser_obj);
  };
}

#endif // MF13_WRITER_H
