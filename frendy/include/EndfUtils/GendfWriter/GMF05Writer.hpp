#ifndef GMF05_WRITER_H
#define GMF05_WRITER_H

#include "EndfUtils/GendfParser/GMF05Parser.hpp"
#include "EndfUtils/GendfWriter/GMFxxWriterBase.hpp"

namespace frendy
{
  class GMF05Writer
  {
    private:

    public:
      //constructor
      GMF05Writer(void);

      //destructor
      virtual ~GMF05Writer(void);

      void clear();

      vector<string> get_gendf_text_data(GMF05Parser& parser_obj);
  };
}

#endif // GMF05_WRITER_H
