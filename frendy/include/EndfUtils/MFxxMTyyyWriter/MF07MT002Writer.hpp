#ifndef MF07MT002_WRITER_H
#define MF07MT002_WRITER_H

#include "EndfUtils/EndfFileWriter/EndfFileWriter.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF07MT002Parser.hpp"

namespace frendy
{
  class MF07MT002Writer
  {
    private:
      frendy::ErrorManager    err_obj;
      frendy::VectorClearer   clr_obj;
      frendy::EndfFileWriter  efw_obj;

      frendy::MF07MT002Parser par_obj;
      vector<string>          text;

      //Integer mat_no;
      static const Integer mf_no = 7;
      static const Integer mt_no = 2;

      void write_endf();
      void write_lthr01(vector<string>& text);
      void write_lthr02(vector<string>& text);

    public:
      //constructor
      MF07MT002Writer(void);

      //destructor
      virtual ~MF07MT002Writer(void);

      void clear();

      vector<string> get_endf_text_data(frendy::MF07MT002Parser& mf07mt002parser_obj);
  };
}

#endif // MF07MT002_WRITER_H

