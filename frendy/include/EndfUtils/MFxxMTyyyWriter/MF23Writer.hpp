#ifndef MF23_WRITER_H
#define MF23_WRITER_H

#include "EndfUtils/EndfFileWriter/EndfFileWriter.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF23Parser.hpp"

namespace frendy
{
  class MF23Writer
  {
    private:
      frendy::ErrorManager    err_obj;
      frendy::VectorClearer   clr_obj;
      frendy::EndfFileWriter  efw_obj;

      frendy::MF23Parser      par_obj;
      vector<string>          text;

      static const Integer mf_no  =  23;

      void write_endf();

    public:
      //constructor
      MF23Writer(void);

      //destructor
      virtual ~MF23Writer(void);

      void clear();

      vector<string> get_endf_text_data(frendy::MF23Parser& mf23parser_obj);
  };
}

#endif // MF23_WRITER_H
