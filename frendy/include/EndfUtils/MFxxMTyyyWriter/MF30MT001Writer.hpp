#ifndef MF30MT001_WRITER_H
#define MF30MT001_WRITER_H

#include "EndfUtils/EndfFileWriter/EndfFileWriter.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF30MT001Parser.hpp"

namespace frendy
{
  class MF30MT001Writer
  {
    private:
      frendy::ErrorManager     err_obj;
      frendy::VectorClearer    clr_obj;
      frendy::EndfFileWriter   efw_obj;

      frendy::MF30MT001Parser  par_obj;
      vector<string>           text;

      static const Integer mf_no =  30;
      static const Integer mt_no =   1;

      void write_endf();

    public:
      //constructor
      MF30MT001Writer(void);

      //destructor
      virtual ~MF30MT001Writer(void);

      void clear();

      vector<string> get_endf_text_data(frendy::MF30MT001Parser& MF30MT001parser_obj);
  };
}

#endif // MF30MT001_WRITER_H
