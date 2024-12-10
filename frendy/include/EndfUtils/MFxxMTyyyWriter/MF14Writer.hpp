#ifndef MF14_WRITER_H
#define MF14_WRITER_H

#include "EndfUtils/EndfFileWriter/EndfFileWriter.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF14Parser.hpp"

namespace frendy
{
  class MF14Writer
  {
    private:
      frendy::ErrorManager    err_obj;
      frendy::VectorClearer   clr_obj;
      frendy::EndfFileWriter  efw_obj;

      frendy::MF14Parser      par_obj;
      vector<string>          text;

      static const Integer mf_no  =  14;

      void write_endf();
      void write_ltt01();
      void write_ltt02();

    public:
      //constructor
      MF14Writer(void);

      //destructor
      virtual ~MF14Writer(void);

      void clear();

      vector<string> get_endf_text_data(frendy::MF14Parser& MF14parser_obj);
  };
}

#endif // MF14_WRITER_H
