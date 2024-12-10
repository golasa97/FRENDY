#ifndef MF28_WRITER_H
#define MF28_WRITER_H

#include "EndfUtils/EndfFileWriter/EndfFileWriter.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF28Parser.hpp"

namespace frendy
{
  class MF28Writer
  {
    private:
      frendy::ErrorManager    err_obj;
      frendy::VectorClearer   clr_obj;
      frendy::EndfFileWriter  efw_obj;

      frendy::MF28Parser      par_obj;
      vector<string>          text;

      static const Integer mf_no  =  28;

      void write_endf();

    public:
      //constructor
      MF28Writer(void);

      //destructor
      virtual ~MF28Writer(void);

      void clear();

      vector<string> get_endf_text_data(frendy::MF28Parser& MF28parser_obj);
  };
}

#endif // MF28_WRITER_H
