#ifndef MF08MT457_WRITER_H
#define MF08MT457_WRITER_H

#include "EndfUtils/EndfFileWriter/EndfFileWriter.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF08MT457Parser.hpp"

namespace frendy
{
  class MF08MT457Writer
  {
    private:
      frendy::ErrorManager     err_obj;
      frendy::VectorClearer    clr_obj;
      frendy::EndfFileWriter   efw_obj;

      frendy::MF08MT457Parser  par_obj;
      vector<string>           text;

      static const Integer mf_no =   8;
      static const Integer mt_no = 457;

      void write_endf();
      void write_nst00();
      void write_nst01();

    public:
      //constructor
      MF08MT457Writer(void);

      //destructor
      virtual ~MF08MT457Writer(void);

      void clear();

      vector<string> get_endf_text_data(frendy::MF08MT457Parser& MF08mt457parser_obj);
  };
}

#endif // MF08MT457_WRITER_H
