#ifndef MF40_WRITER_H
#define MF40_WRITER_H

#include "EndfUtils/EndfFileWriter/EndfFileWriter.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF40Parser.hpp"

namespace frendy
{
  class MF40Writer
  {
    private:
      frendy::ErrorManager    err_obj;
      frendy::VectorClearer   clr_obj;
      frendy::EndfFileWriter  efw_obj;

      frendy::MF40Parser      par_obj;
      vector<string>          text;

      static const Integer mf_no  =  40;

      void write_endf();
      void write_NC(int i, int j, int k);
      void write_NI(int i, int j, int k);
      void write_NI_lb00(int i, int j, int k);
      void write_NI_lb05(int i, int j, int k);
      void write_NI_lb06(int i, int j, int k);

    public:
      //constructor
      MF40Writer(void);

      //destructor
      virtual ~MF40Writer(void);

      void clear();

      vector<string> get_endf_text_data(frendy::MF40Parser& MF40parser_obj);
  };
}

#endif // MF40_WRITER_H
