#ifndef GMF13_WRITER_H
#define GMF13_WRITER_H

#include "EndfUtils/GendfParser/GMF13Parser.hpp"
#include "EndfUtils/GendfWriter/GMFxxWriterBase.hpp"

namespace frendy
{
  class GMF13Writer
  {
    private:

    public:
      //constructor
      GMF13Writer(void);

      //destructor
      virtual ~GMF13Writer(void);

      void clear();

      vector<string> get_gendf_text_data(GMF13Parser& parser_obj);
  };
}

#endif // GMF13_WRITER_H
