#ifndef MF09_WRITER_H
#define MF09_WRITER_H

#include "EndfUtils/EndfFileWriter/EndfFileWriter.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF09Parser.hpp"

namespace frendy
{
  class MF09Writer
  {
    private:
      frendy::ErrorManager   err_obj;
      frendy::VectorClearer  clr_obj;
      frendy::EndfFileWriter efw_obj;

      frendy::MF09Parser     par_obj;
      vector<string>         text;

      static const Integer mf_no = 9;

      void write_endf();

    public:
      //constructor
      MF09Writer(void);

      //destructor
      virtual ~MF09Writer(void);

      void clear();

      vector<string> get_endf_text_data(frendy::MF09Parser& mf09parser_obj);
  };
}

#endif // MF09_WRITER_H
