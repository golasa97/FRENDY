#ifndef MF08MT454_WRITER_H
#define MF08MT454_WRITER_H

#include "EndfUtils/EndfFileWriter/EndfFileWriter.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF08MT454Parser.hpp"

namespace frendy
{
  class MF08MT454Writer
  {
    private:
      frendy::ErrorManager     err_obj;
      frendy::VectorClearer    clr_obj;
      frendy::EndfFileWriter   efw_obj;

      frendy::MF08MT454Parser  par_obj;
      vector<string>           text;

      static const Integer mf_no =   8;
      static const Integer mt_no = 454;

      void write_endf();

    public:
      //constructor
      MF08MT454Writer(void);

      //destructor
      virtual ~MF08MT454Writer(void);

      void clear();

      vector<string> get_endf_text_data(frendy::MF08MT454Parser& MF08mt454parser_obj);
  };
}

#endif // MF08MT454_WRITER_H
