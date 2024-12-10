#ifndef MF30MT002_WRITER_H
#define MF30MT002_WRITER_H

#include "EndfUtils/EndfFileWriter/EndfFileWriter.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF30MT002Parser.hpp"

namespace frendy
{
  class MF30MT002Writer
  {
    private:
      frendy::ErrorManager     err_obj;
      frendy::VectorClearer    clr_obj;
      frendy::EndfFileWriter   efw_obj;

      frendy::MF30MT002Parser  par_obj;
      vector<string>           text;

      static const Integer mf_no =  30;
      static const Integer mt_no =   2;

      void write_endf();

    public:
      //constructor
      MF30MT002Writer(void);

      //destructor
      virtual ~MF30MT002Writer(void);

      void clear();

      vector<string> get_endf_text_data(frendy::MF30MT002Parser& MF30MT002parser_obj);
  };
}

#endif // MF30MT002_WRITER_H
