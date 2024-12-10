#ifndef ERROR_MANAGER_H
#define ERROR_MANAGER_H

#include <stdexcept>

#include "Config/CommonData.hpp"

namespace frendy
{
  class ErrorManager
  {
    private:
      static int err_mes_opt;
      static int err_mes_format_opt;
      static int err_mes_nan_opt;

      int output_mode;
    
    public:
      //constructor
      ErrorManager(void);

      //destructor
      virtual ~ErrorManager(void);

      //For err_mes_opt
      static const int err_mes_default               = 0;
      static const int err_mes_debug                 = 1;
      static const int err_mes_skip_warning          = 2;

      static const int no_output_format_warning      = 0;
      static const int output_format_warning         = 1;

      //For output_mode
      static const int warning_on  = 0;
      static const int warning_off = 1;

      static const int warning_runtime_error  = 0;
      static const int warning_caution        = 1;
      static const int warning_default        = 0; //warning_runtime_error
    
      void output_runtime_error(string class_name, string function_name, vector<string> error_comment);
      void output_runtime_error(string class_name, string function_name, string error_comment);

      void output_caution_format(string class_name, string function_name, vector<string> error_comment);
      void output_caution(string class_name, string function_name, vector<string> error_comment);
      void output_caution(string class_name, string function_name, string error_comment);

      int  get_err_mes_opt();
      void set_err_mes_opt(int int_value);

      int  get_err_mes_format_opt();
      void set_err_mes_format_opt(int int_value);

      int  get_err_mes_nan_opt();
      void set_err_mes_nan_opt(int int_value);

      int  get_output_mode();
      void set_output_mode(int int_value);
  };
}

#endif // ERROR_MANAGER_H
