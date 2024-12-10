#ifndef MF05_WRITER_H
#define MF05_WRITER_H

#include "EndfUtils/EndfFileWriter/EndfFileWriter.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF05Parser.hpp"

namespace frendy
{
  class MF05Writer
  {
    private:
      frendy::ErrorManager   err_obj;
      frendy::VectorClearer  clr_obj;
      frendy::EndfFileWriter efw_obj;

      frendy::MF05Parser     par_obj;
      vector<string>         text;

      static const Integer mf_no = 5;

      void write_endf();
      void write_lf01(int i);
      void write_lf05(int i);
      void write_lf07(int i);

    public:
      //constructor
      MF05Writer(void);

      //destructor
      virtual ~MF05Writer(void);

      void clear();

      vector<string> get_endf_text_data(frendy::MF05Parser& MF05parser_obj);
  };
}

#endif // MF05_WRITER_H
