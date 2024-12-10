#ifndef MF34_WRITER_H
#define MF34_WRITER_H

#include "EndfUtils/EndfFileWriter/EndfFileWriter.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF34Parser.hpp"

namespace frendy
{
  class MF34Writer
  {
    private:
      frendy::ErrorManager    err_obj;
      frendy::VectorClearer   clr_obj;
      frendy::EndfFileWriter  efw_obj;

      frendy::MF34Parser      par_obj;
      vector<string>          text;

      static const Integer mf_no  =  34;

      void write_endf();
      void write_NSS(int i);
      void write_lb00(int i, int j, int k, int l);
      void write_lb05(int i, int j, int k, int l);
      void write_lb06(int i, int j, int k, int l);

    public:
      //constructor
      MF34Writer(void);

      //destructor
      virtual ~MF34Writer(void);

      void clear();

      vector<string> get_endf_text_data(frendy::MF34Parser& MF34parser_obj);
  };
}

#endif // MF34_WRITER_H
