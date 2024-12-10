#ifndef TIME_UTILS_H
#define TIME_UTILS_H

#include <time.h>
#include "Config/FrendyTypes.hpp"
#include "ErrorManager.hpp"

using namespace std;

namespace frendy
{
  class TimeUtils
  {
    private:
      ErrorManager err_obj;

      string convert_int_to_string(int int_data);

    public:
      //constructor
      TimeUtils(void);

      //destructor
      virtual ~TimeUtils(void);

      string get_current_date();
      string get_current_date_no_slash();
      string get_current_date_dd_mmm_yyyy();

      string get_current_time();

      void   output_current_date();
      void   output_current_time();
  };
}

#endif // TIME_UTILS_H
