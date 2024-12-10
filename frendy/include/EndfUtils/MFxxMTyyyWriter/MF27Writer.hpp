#ifndef MF27_WRITER_H
#define MF27_WRITER_H

#include "EndfUtils/EndfFileWriter/EndfFileWriter.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF27Parser.hpp"

namespace frendy
{
  class MF27Writer
  {
    private:
      frendy::ErrorManager    err_obj;
      frendy::VectorClearer   clr_obj;
      frendy::EndfFileWriter  efw_obj;

      frendy::MF27Parser      par_obj;
      vector<string>          text;

      static const Integer mf_no  =  27;

      void write_endf();

    public:
      //constructor
      MF27Writer(void);

      //destructor
      virtual ~MF27Writer(void);

      void clear();

      vector<string> get_endf_text_data(frendy::MF27Parser& MF27parser_obj);
  };
}

#endif // MF27_WRITER_H
