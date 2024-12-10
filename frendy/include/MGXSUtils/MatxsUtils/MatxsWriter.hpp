#ifndef MATXS_WRITER_H
#define MATXS_WRITER_H

#include "CommonUtils/VectorClearer.hpp"
#include "CommonUtils/ErrorManager.hpp"
#include "CommonUtils/StringUtils.hpp"
#include "EndfUtils/EndfFileReader/EndfUtils.hpp"
#include "MGXSUtils/MatxsUtils/MatxsObject.hpp"

namespace frendy
{
  class MatxsWriter
  {
    private:
      frendy::ErrorManager err_obj;

#ifdef DEBUG_MODE
  public:
#endif
      frendy::MatxsCommonData matxs_obj;

      string         file_name;
      vector<string> text;

      string         huse;
      vector<string> hsetid;

      int            huse_flg, hsetid_flg;


      void write_matxs();

    public:

      //constructor
      MatxsWriter(void);

      //destructor
      virtual ~MatxsWriter(void);

      void clear();

      void write_matxs(string str_data);

      void set_file_name(string str_data);
      void set_matxs_obj(frendy::MatxsCommonData data_obj);
      void set_huse(string str_data);
      void set_hsetid(vector<string> str_vec);

      string                  get_file_name();
      vector<string>          get_text();
      frendy::MatxsCommonData get_matxs_obj();     
      string                  get_huse();
      vector<string>          get_hsetid();
  }; 
}

#endif //MATXS_WRITER_H
