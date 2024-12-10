#ifndef MF01MT458_WRITER_H
#define MF01MT458_WRITER_H

#include "EndfUtils/EndfFileWriter/EndfFileWriter.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF01MT458Parser.hpp"

namespace frendy
{
  class MF01MT458Writer
  {
    private:
      frendy::ErrorManager     err_obj;
      frendy::VectorClearer    clr_obj;
      frendy::EndfFileWriter   efw_obj;

      frendy::MF01MT458Parser  par_obj;
      vector<string>           text;

      static const Integer mf_no =   1;
      static const Integer mt_no = 458;

      void write_endf();

    public:
      //constructor
      MF01MT458Writer(void);

      //destructor
      virtual ~MF01MT458Writer(void);

      void clear();

      vector<string> get_endf_text_data(frendy::MF01MT458Parser& mf01mt458parser_obj);
  };
}

#endif // MF01MT458_WRITER_H
