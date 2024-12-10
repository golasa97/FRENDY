#ifndef MF08_WRITER_H
#define MF08_WRITER_H

#include "EndfUtils/EndfFileWriter/EndfFileWriter.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF08Parser.hpp"

namespace frendy
{
  class MF08Writer
  {
    private:
      frendy::ErrorManager   err_obj;
      frendy::VectorClearer  clr_obj;
      frendy::EndfFileWriter efw_obj;

      frendy::MF08Parser     par_obj;
      vector<string>         text;

      static const Integer mf_no = 8;

      void write_endf();

    public:
      //constructor
      MF08Writer(void);

      //destructor
      virtual ~MF08Writer(void);

      void clear();

      vector<string> get_endf_text_data(frendy::MF08Parser& mf08parser_obj);
  };
}

#endif // MF08_WRITER_H
