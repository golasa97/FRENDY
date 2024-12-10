#ifndef MF03_WRITER_H
#define MF03_WRITER_H

#include "EndfUtils/EndfFileWriter/EndfFileWriter.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF03Parser.hpp"

namespace frendy
{
  class MF03Writer
  {
    private:
      frendy::ErrorManager   err_obj;
      frendy::VectorClearer  clr_obj;
      frendy::EndfFileWriter efw_obj;

      frendy::MF03Parser     par_obj;
      vector<string>         text;

      static const Integer mf_no = 3;

      void write_endf();

    public:
      //constructor
      MF03Writer(void);

      //destructor
      virtual ~MF03Writer(void);

      void clear();

      vector<string> get_endf_text_data(frendy::MF03Parser& mf03parser_obj);
  };
}

#endif // MF03_WRITER_H
