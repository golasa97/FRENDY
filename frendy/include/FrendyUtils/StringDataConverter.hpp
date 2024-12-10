#ifndef STRING_DATA_CONVERTER_H
#define STRING_DATA_CONVERTER_H

#include "EndfUtils/EndfFileReader/StringConverter.hpp"
#include "CommonUtils/StringUtils.hpp"

namespace frendy
{
  class StringDataConverter
  {
    private:
      frendy::StringUtils     str_util;
      frendy::StringConverter str_obj;

    public:
      //constructor
      StringDataConverter(void);

      //destructor
      virtual ~StringDataConverter(void);


      vector<Integer> get_int_data_list(vector<string> str_vec);
      void            sort_int_data_list(vector<Integer>& int_vec);
  };
}

#endif //STRING_DATA_CONVERTER_H

