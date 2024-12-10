#ifndef MF01MT452_WRITER_H
#define MF01MT452_WRITER_H

#include "EndfUtils/EndfFileWriter/EndfFileWriter.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF01MT452Parser.hpp"

namespace frendy
{
  class MF01MT452Writer
  {
    private:
      frendy::ErrorManager     err_obj;
      frendy::VectorClearer    clr_obj;
      frendy::EndfFileWriter   efw_obj;

      frendy::MF01MT452Parser  par_obj;
      vector<string>           text;

      static const Integer mf_no =   1;
      static const Integer mt_no = 452;

      void write_endf();

    public:
      //constructor
      MF01MT452Writer(void);

      //destructor
      virtual ~MF01MT452Writer(void);

      void clear();

      vector<string> get_endf_text_data(frendy::MF01MT452Parser& mf01mt452parser_obj);
  };
}

#endif // MF01MT452_WRITER_H
