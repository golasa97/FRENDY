#ifndef MATXS_PARSER_H
#define MATXS_PARSER_H

#include "CommonUtils/VectorClearer.hpp"
#include "CommonUtils/ErrorManager.hpp"
#include "CommonUtils/StringUtils.hpp"
#include "EndfUtils/EndfFileReader/EndfUtils.hpp"
#include "MGXSUtils/KramUtils/KramObject.hpp"

namespace frendy
{
  class KramParser
  {
    private:
      frendy::ErrorManager err_obj;

#ifdef DEBUG_MODE
  public:
#endif
      frendy::KramCommonData kram_obj;

      string file_name;
      vector<string> text;

      void read_kram(int mg_no);

    public:

      //constructor
      KramParser(void);

      //destructor
      virtual ~KramParser(void);

      void clear();

      void set_file_name(string str_data, int mg_no);
      void set_text(vector<string>& text_data, int mg_no);

      string get_file_name();

      vector<string> get_text();

      frendy::KramCommonData get_kram_obj();     
  }; 
}

#endif //MATXS_PARSER_H
