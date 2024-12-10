#ifndef MF01MT455_WRITER_H
#define MF01MT455_WRITER_H

#include "EndfUtils/EndfFileWriter/EndfFileWriter.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF01MT455Parser.hpp"

namespace frendy
{
  class MF01MT455Writer
  {
    private:
      frendy::ErrorManager     err_obj;
      frendy::VectorClearer    clr_obj;
      frendy::EndfFileWriter   efw_obj;

      frendy::MF01MT455Parser  par_obj;
      vector<string>           text;

      static const Integer mf_no =   1;
      static const Integer mt_no = 455;

      void write_endf();

    public:
      //constructor
      MF01MT455Writer(void);

      //destructor
      virtual ~MF01MT455Writer(void);

      void clear();

      vector<string> get_endf_text_data(frendy::MF01MT455Parser& mf01mt455parser_obj);
  };
}

#endif // MF01MT455_WRITER_H
