#ifndef MF01MT456_WRITER_H
#define MF01MT456_WRITER_H

#include "EndfUtils/EndfFileWriter/EndfFileWriter.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF01MT456Parser.hpp"

namespace frendy
{
  class MF01MT456Writer
  {
    private:
      frendy::ErrorManager     err_obj;
      frendy::VectorClearer    clr_obj;
      frendy::EndfFileWriter   efw_obj;

      frendy::MF01MT456Parser  par_obj;
      vector<string>           text;

      static const Integer mf_no =   1;
      static const Integer mt_no = 456;

      void write_endf();

    public:
      //constructor
      MF01MT456Writer(void);

      //destructor
      virtual ~MF01MT456Writer(void);

      void clear();

      vector<string> get_endf_text_data(frendy::MF01MT456Parser& mf01mt456parser_obj);
  };
}

#endif // MF01MT456_WRITER_H
