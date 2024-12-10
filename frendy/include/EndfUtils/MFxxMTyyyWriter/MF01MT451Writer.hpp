#ifndef MF01MT451_WRITER_H
#define MF01MT451_WRITER_H

#include "EndfUtils/EndfFileWriter/EndfFileWriter.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF01MT451Parser.hpp"

namespace frendy
{
  class MF01MT451Writer
  {
    private:
      frendy::ErrorManager     err_obj;
      frendy::VectorClearer    clr_obj;
      frendy::EndfFileWriter   efw_obj;

      frendy::MF01MT451Parser  par_obj;
      vector<string>           text;

      static const Integer mf_no =   1;
      static const Integer mt_no = 451;

      void write_endf();
      void mod_nc_data();

    public:
      //constructor
      MF01MT451Writer(void);

      //destructor
      virtual ~MF01MT451Writer(void);

      void clear();

      vector<string> get_endf_text_data(frendy::MF01MT451Parser& mf01mt451parser_obj);
  };
}

#endif // MF01MT451_WRITER_H
