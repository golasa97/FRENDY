#ifndef MF04_WRITER_H
#define MF04_WRITER_H

#include "EndfUtils/EndfFileWriter/EndfFileWriter.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF04Parser.hpp"

namespace frendy
{
  class MF04Writer
  {
    private:
      frendy::ErrorManager   err_obj;
      frendy::VectorClearer  clr_obj;
      frendy::EndfFileWriter efw_obj;

      frendy::MF04Parser     par_obj;
      vector<string>         text;

      static const Integer mf_no = 4;

      void write_endf();
      void write_ltt01();
      void write_ltt02();

    public:
      //constructor
      MF04Writer(void);

      //destructor
      virtual ~MF04Writer(void);

      void clear();

      vector<string> get_endf_text_data(frendy::MF04Parser& MF04parser_obj);
  };
}

#endif // MF04_WRITER_H
