#ifndef GMFxxWriterBase_H
#define GMFxxWriterBase_H

#include "EndfUtils/GendfParser/GMFxxParserBase.hpp"
#include "EndfUtils/EndfFileWriter/EndfFileWriter.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class GMFxxWriterBase
  {
    private:
      frendy::ErrorManager    err_obj;
      frendy::EndfFileWriter  efw_obj;

      frendy::GMFxxParserBase par_obj;
      vector<string>          text;

      void write_gendf();

    public:
      //constructor
      GMFxxWriterBase(void);

      //destructor
      virtual ~GMFxxWriterBase(void);

      void clear();

      vector<string> get_gendf_text_data(frendy::GMFxxParserBase parser_obj);
  };
}

#endif // GMFxxWriterBase_H
