#ifndef MF31_WRITER_H
#define MF31_WRITER_H

#include "EndfUtils/EndfFileWriter/EndfFileWriter.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF31Parser.hpp"

namespace frendy
{
  class MF31Writer
  {
    private:
      frendy::ErrorManager    err_obj;
      frendy::VectorClearer   clr_obj;
      frendy::EndfFileWriter  efw_obj;

      frendy::MF31Parser      par_obj;
      vector<string>          text;

      static const Integer mf_no  =  31;

      void write_endf();
      void write_NC(int i, int j);
      void write_NI(int i, int j);
      void write_NI_lb00(int i, int j);
      void write_NI_lb05(int i, int j);
      void write_NI_lb06(int i, int j);

    public:
      //constructor
      MF31Writer(void);

      //destructor
      virtual ~MF31Writer(void);

      void clear();

      vector<string> get_endf_text_data(frendy::MF31Parser& MF31parser_obj);
  };
}

#endif // MF31_WRITER_H
