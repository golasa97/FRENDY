#ifndef GMF16_WRITER_H
#define GMF16_WRITER_H

#include "EndfUtils/GendfParser/GMF16Parser.hpp"
#include "EndfUtils/GendfWriter/GMFxxWriterBase.hpp"

namespace frendy
{
  class GMF16Writer
  {
    private:

    public:
      //constructor
      GMF16Writer(void);

      //destructor
      virtual ~GMF16Writer(void);

      void clear();

      vector<string> get_gendf_text_data(GMF16Parser& parser_obj);
  };
}

#endif // GMF16_WRITER_H
