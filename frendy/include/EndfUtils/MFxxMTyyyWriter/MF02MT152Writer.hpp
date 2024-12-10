#ifndef MF02MT152_WRITER_H
#define MF02MT152_WRITER_H

#include "EndfUtils/EndfFileWriter/EndfFileWriter.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF02MT152Parser.hpp"

namespace frendy
{
  class MF02MT152Writer
  {
    private:
      frendy::ErrorManager    err_obj;
      frendy::VectorClearer   clr_obj;
      frendy::EndfFileWriter  efw_obj;

      frendy::MF02MT152Parser par_obj;
      vector<string>          text;

      static const Integer mf_no =   2;
      static const Integer mt_no = 152;

      void write_endf();
      void write_endf_reconr_mode(vector<Real>& real_vec);
      void write_endf_purr_mode(vector<Real>& real_vec);

    public:
      //constructor
      MF02MT152Writer(void);

      //destructor
      virtual ~MF02MT152Writer(void);

      void clear();

      vector<string> get_endf_text_data(frendy::MF02MT152Parser& mf02mt152parser_obj);
  };
}

#endif // MF02MT152_WRITER_H
