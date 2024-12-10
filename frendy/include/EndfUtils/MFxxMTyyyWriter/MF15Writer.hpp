#ifndef MF15_WRITER_H
#define MF15_WRITER_H

#include "EndfUtils/EndfFileWriter/EndfFileWriter.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF15Parser.hpp"

namespace frendy
{
  class MF15Writer
  {
    private:
      frendy::ErrorManager    err_obj;
      frendy::VectorClearer   clr_obj;
      frendy::EndfFileWriter  efw_obj;

      frendy::MF15Parser      par_obj;
      vector<string>          text;

      static const Integer mf_no  =  15;

      void write_endf();
      void write_lf01(int i);
      void write_lf05(int i);
      void write_lf07(int i);

    public:
      //constructor
      MF15Writer(void);

      //destructor
      virtual ~MF15Writer(void);

      void clear();

      vector<string> get_endf_text_data(frendy::MF15Parser& MF15parser_obj);
  };
}

#endif // MF15_WRITER_H
