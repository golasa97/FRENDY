#ifndef STRING_CONVERTER_H
#define STRING_CONVERTER_H

#include <boost/variant.hpp>

#include "Config/FrendyTypes.hpp"
#include "CommonUtils/ErrorManager.hpp"
#include "EndfUtils/EndfFileReader/EndfUtils.hpp"

namespace frendy
{
  class StringConverter
  {
    private:
      static const int value_str_size = 15;
      static const int c_size         =  6;
      static const int m_size         =  4;

      frendy::ErrorManager   err_obj;
      vector<string>         value_str;

      int                    parse_pos;
      string                 buf_all;

      void cut_text(string& buf, vector<string>& strC, vector<string>& strM);
      void cut_text(string& buf, vector<string>& strC); //without MF, MT and Line No.

      void space_eraser(string& buf);
    
    public:
      //constructor
      StringConverter(void);

      //destructor
      virtual ~StringConverter(void);

      void string_check(string& buf);

      void read_line(string& buf, vector<Real>& C, vector<Integer>& M);
      void read_line(string& buf, vector<Real>& C); //without MF, MT and Line No.
  };
}

#endif // STRING_CONVERTER_H
