#ifndef MF33_WRITER_H
#define MF33_WRITER_H

#include "EndfUtils/EndfFileWriter/EndfFileWriter.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF33Parser.hpp"

namespace frendy
{
  class MF33Writer
  {
    private:
      frendy::ErrorManager    err_obj;
      frendy::VectorClearer   clr_obj;
      frendy::EndfFileWriter  efw_obj;

      frendy::MF33Parser      par_obj;
      vector<string>          text;

      static const Integer mf_no  =  33;

      void write_endf();
      void write_NC(int i, int j);
      void write_NI(int i, int j);
      void write_NI_lb00(int i, int j);
      void write_NI_lb05(int i, int j);
      void write_NI_lb06(int i, int j);

    public:
      //constructor
      MF33Writer(void);

      //destructor
      virtual ~MF33Writer(void);

      void clear();

      vector<string> get_endf_text_data(frendy::MF33Parser& MF33parser_obj);
  };
}

#endif // MF33_WRITER_H
