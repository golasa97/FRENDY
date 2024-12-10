#ifndef MF02MT153_WRITER_H
#define MF02MT153_WRITER_H

#include "EndfUtils/EndfFileWriter/EndfFileWriter.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF02MT153Parser.hpp"

namespace frendy
{
  class MF02MT153Writer
  {
    private:
      frendy::ErrorManager    err_obj;
      frendy::VectorClearer   clr_obj;
      frendy::EndfFileWriter  efw_obj;

      frendy::MF02MT153Parser par_obj;
      vector<string>          text;

      static const Integer mf_no =   2;
      static const Integer mt_no = 153;

      void write_endf();

    public:
      //constructor
      MF02MT153Writer(void);

      //destructor
      virtual ~MF02MT153Writer(void);

      void clear();

      vector<string> get_endf_text_data(frendy::MF02MT153Parser& mf02mt153parser_obj);
  };
}

#endif // MF02MT153_WRITER_H
