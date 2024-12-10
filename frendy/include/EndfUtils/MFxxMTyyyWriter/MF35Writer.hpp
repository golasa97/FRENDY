#ifndef MF35_WRITER_H
#define MF35_WRITER_H

#include "EndfUtils/EndfFileWriter/EndfFileWriter.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF35Parser.hpp"

namespace frendy
{
  class MF35Writer
  {
    private:
      frendy::ErrorManager    err_obj;
      frendy::VectorClearer   clr_obj;
      frendy::EndfFileWriter  efw_obj;

      frendy::MF35Parser      par_obj;
      vector<string>          text;

      static const Integer mf_no  =  35;

      void write_endf();
      void write_lb00(int i);
      void write_lb05(int i);
      void write_lb06(int i);

    public:
      //constructor
      MF35Writer(void);

      //destructor
      virtual ~MF35Writer(void);

      void clear();

      vector<string> get_endf_text_data(frendy::MF35Parser& MF35parser_obj);
  };
}

#endif // MF35_WRITER_H
