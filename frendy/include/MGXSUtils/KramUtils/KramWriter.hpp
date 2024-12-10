#ifndef MATXS_WRITER_H
#define MATXS_WRITER_H

#include "CommonUtils/VectorClearer.hpp"
#include "CommonUtils/ErrorManager.hpp"
#include "CommonUtils/StringUtils.hpp"
#include "EndfUtils/EndfFileReader/EndfUtils.hpp"
#include "MGXSUtils/KramUtils/KramObject.hpp"

namespace frendy
{
  class KramWriter
  {
    private:
      frendy::ErrorManager err_obj;

#ifdef DEBUG_MODE
  public:
#endif
      frendy::KramCommonData kram_obj;

      string         file_name;
      vector<string> text;

      void write_kram();

    public:

      //constructor
      KramWriter(void);

      //destructor
      virtual ~KramWriter(void);

      void clear();

      void write_kram(string str_data);

      void set_file_name(string str_data);
      void set_kram_obj(frendy::KramCommonData data_obj);

      string                  get_file_name();
      vector<string>          get_text();
      frendy::KramCommonData  get_kram_obj();     
  }; 
}

#endif //MATXS_WRITER_H
