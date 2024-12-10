#ifndef MF07MT451_WRITER_H
#define MF07MT451_WRITER_H

#include "EndfUtils/EndfFileWriter/EndfFileWriter.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF07MT451Parser.hpp"

namespace frendy
{
  class MF07MT451Writer
  {
    private:
      frendy::ErrorManager    err_obj;
      frendy::VectorClearer   clr_obj;
      frendy::EndfFileWriter  efw_obj;

      frendy::MF07MT451Parser par_obj;
      vector<string>          text;

      //Integer mat_no;
      static const Integer mf_no = 7;
      static const Integer mt_no = 451;

      void write_endf();

    public:
      //constructor
      MF07MT451Writer(void);

      //destructor
      virtual ~MF07MT451Writer(void);

      void clear();

      vector<string> get_endf_text_data(frendy::MF07MT451Parser& mf07mt451parser_obj);
  };
}

#endif // MF07MT451_WRITER_H

