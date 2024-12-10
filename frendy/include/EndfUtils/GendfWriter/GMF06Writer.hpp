#ifndef GMF06_WRITER_H
#define GMF06_WRITER_H

#include "EndfUtils/GendfParser/GMF06Parser.hpp"
#include "EndfUtils/GendfWriter/GMFxxWriterBase.hpp"

namespace frendy
{
  class GMF06Writer
  {
    private:

    public:
      //constructor
      GMF06Writer(void);

      //destructor
      virtual ~GMF06Writer(void);

      void clear();

      vector<string> get_gendf_text_data(GMF06Parser& parser_obj);
  };
}

#endif // GMF06_WRITER_H
