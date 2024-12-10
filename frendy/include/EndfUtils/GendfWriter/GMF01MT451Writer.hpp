#ifndef GMF01MT451_WRITER_H
#define GMF01MT451_WRITER_H

#include "EndfUtils/GendfParser/GMF01MT451Parser.hpp"
#include "EndfUtils/EndfFileWriter/EndfFileWriter.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class GMF01MT451Writer
  {
    private:
      frendy::ErrorManager    err_obj;
      frendy::EndfFileWriter  efw_obj;

      frendy::GMF01MT451Parser  par_obj;
      vector<string>            text;

      static const Integer mf_no =   1;
      static const Integer mt_no = 451;

      void write_gendf();

    public:
      //constructor
      GMF01MT451Writer(void);

      //destructor
      virtual ~GMF01MT451Writer(void);

      void clear();

      vector<string> get_gendf_text_data(frendy::GMF01MT451Parser& parser_obj);
  };
}

#endif // GMF01MT451_WRITER_H
