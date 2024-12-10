#ifndef MATXS_PARSER_H
#define MATXS_PARSER_H

#include "CommonUtils/VectorClearer.hpp"
#include "CommonUtils/ErrorManager.hpp"
#include "CommonUtils/StringUtils.hpp"
#include "EndfUtils/EndfFileReader/EndfUtils.hpp"
#include "MGXSUtils/MatxsUtils/MatxsObject.hpp"

namespace frendy
{
  class MatxsParser
  {
    private:
      frendy::ErrorManager err_obj;

#ifdef DEBUG_MODE
  public:
#endif
      frendy::MatxsCommonData matxs_obj;

      string file_name;
      vector<string> text;

      void read_matxs();

    public:

      //constructor
      MatxsParser(void);

      //destructor
      virtual ~MatxsParser(void);

      void clear();

      void set_file_name(string str_data);
      void set_text(vector<string>& text_data);

      string get_file_name();

      vector<string> get_text();

      frendy::MatxsCommonData get_matxs_obj();     
  }; 
}

#endif //MATXS_PARSER_H
