#ifndef MF08MT459_WRITER_H
#define MF08MT459_WRITER_H

#include "EndfUtils/EndfFileWriter/EndfFileWriter.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF08MT459Parser.hpp"

namespace frendy
{
  class MF08MT459Writer
  {
    private:
      frendy::ErrorManager     err_obj;
      frendy::VectorClearer    clr_obj;
      frendy::EndfFileWriter   efw_obj;

      frendy::MF08MT459Parser  par_obj;
      vector<string>           text;

      static const Integer mf_no =   8;
      static const Integer mt_no = 459;

      void write_endf();

    public:
      //constructor
      MF08MT459Writer(void);

      //destructor
      virtual ~MF08MT459Writer(void);

      void clear();

      vector<string> get_endf_text_data(frendy::MF08MT459Parser& MF08mt459parser_obj);
  };
}

#endif // MF08MT459_WRITER_H
