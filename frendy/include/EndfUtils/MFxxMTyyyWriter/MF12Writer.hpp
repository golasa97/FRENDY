#ifndef MF12_WRITER_H
#define MF12_WRITER_H

#include "EndfUtils/EndfFileWriter/EndfFileWriter.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF12Parser.hpp"

namespace frendy
{
  class MF12Writer
  {
    private:
      frendy::ErrorManager   err_obj;
      frendy::VectorClearer  clr_obj;
      frendy::EndfFileWriter efw_obj;

      frendy::MF12Parser     par_obj;
      vector<string>         text;

      static const Integer   mf_no  =  12;

      void write_endf();
      void write_lo01();
      void write_lo02();

    public:
      //constructor
      MF12Writer(void);

      //destructor
      virtual ~MF12Writer(void);

      void clear();

      vector<string> get_endf_text_data(frendy::MF12Parser& mf12parser_obj);
  };
}

#endif // MF12_WRITER_H
