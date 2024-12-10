#ifndef MF01MT460_WRITER_H
#define MF01MT460_WRITER_H

#include "EndfUtils/EndfFileWriter/EndfFileWriter.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF01MT460Parser.hpp"

namespace frendy
{
  class MF01MT460Writer
  {
    private:
      frendy::ErrorManager     err_obj;
      frendy::VectorClearer    clr_obj;
      frendy::EndfFileWriter   efw_obj;

      frendy::MF01MT460Parser  par_obj;
      vector<string>           text;

      static const Integer mf_no =   1;
      static const Integer mt_no = 460;

      void write_endf();

    public:
      //constructor
      MF01MT460Writer(void);

      //destructor
      virtual ~MF01MT460Writer(void);

      void clear();

      vector<string> get_endf_text_data(frendy::MF01MT460Parser& mf01mt460parser_obj);
  };
}

#endif // MF01MT460_WRITER_H
