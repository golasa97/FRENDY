#ifndef MF26_WRITER_H
#define MF26_WRITER_H

#include "EndfUtils/EndfFileWriter/EndfFileWriter.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF26Parser.hpp"

namespace frendy
{
  class MF26Writer
  {
    private:
      frendy::ErrorManager    err_obj;
      frendy::VectorClearer   clr_obj;
      frendy::EndfFileWriter  efw_obj;

      frendy::MF26Parser      par_obj;
      vector<string>          text;

      static const Integer mf_no  =  26;

      void write_endf();
      void write_law01(int i);
      void write_law02(int i);
      void write_law08(int i);

    public:
      //constructor
      MF26Writer(void);

      //destructor
      virtual ~MF26Writer(void);

      void clear();

      vector<string> get_endf_text_data(frendy::MF26Parser& MF26parser_obj);
  };
}

#endif // MF26_WRITER_H
