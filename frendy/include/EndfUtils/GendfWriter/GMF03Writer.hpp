#ifndef GMF03_WRITER_H
#define GMF03_WRITER_H

#include "EndfUtils/GendfParser/GMF03Parser.hpp"
#include "EndfUtils/GendfWriter/GMFxxWriterBase.hpp"

namespace frendy
{
  class GMF03Writer
  {
    private:

    public:
      //constructor
      GMF03Writer(void);

      //destructor
      virtual ~GMF03Writer(void);

      void clear();

      vector<string> get_gendf_text_data(GMF03Parser& parser_obj);
  };
}

#endif // GMF03_WRITER_H
