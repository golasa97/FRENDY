#include "CommonUtils/ErrorManager.hpp"

using namespace frendy;

//constructor
ErrorManager::ErrorManager(void)
{
  output_mode = warning_on;
}

//destructor
ErrorManager::~ErrorManager(void)
{
  output_mode = warning_on;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

const int ErrorManager::warning_on;
const int ErrorManager::warning_off;

const int ErrorManager::err_mes_default;
const int ErrorManager::err_mes_debug;
const int ErrorManager::err_mes_skip_warning;

const int ErrorManager::no_output_format_warning;
const int ErrorManager::output_format_warning;

const int ErrorManager::warning_runtime_error;
const int ErrorManager::warning_caution;
const int ErrorManager::warning_default;

int       ErrorManager::err_mes_opt        = err_mes_default;
int       ErrorManager::err_mes_format_opt = no_output_format_warning;
int       ErrorManager::err_mes_nan_opt    = warning_runtime_error;

////////////////////////////////////////////////////////////////////////////////////////////////////

void ErrorManager::output_runtime_error(string class_name, string function_name, vector<string> error_comment)
{
  if( err_mes_opt != err_mes_debug )
  {
    cout << endl;
    cout << "*************************" << endl;
    cout << "*                       *" << endl;
    cout << "*  !!! FATAL ERROR !!!  *" << endl;
    cout << "*                       *" << endl;
    cout << "*************************" << endl;
    cout << endl;
    cout << "  <Class name>" << endl;
    cout << "    " << class_name << endl << endl;
    cout << "  <Function name>" << endl;
    cout << "    " << function_name << endl << endl;
    cout << "  <Error message>" << endl;

    int i_max = static_cast<int>(error_comment.size());
    if( i_max > 0 )
    {
      for(int i=0; i<i_max; i++)
      {
        cout << "    " << error_comment[i] << endl;
      }
    }
    cout << endl;
  }

  throw runtime_error("Runtime error. Please check your input file or source file.");
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ErrorManager::output_runtime_error(string class_name, string function_name, string error_comment)
{
  vector<string> error_vec;
  error_vec.clear();

  error_vec.push_back(error_comment);
  output_runtime_error(class_name, function_name, error_vec);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ErrorManager::output_caution_format
                     (string class_name, string function_name, vector<string> error_comment)
{
  if( err_mes_format_opt == output_format_warning )
  {
    output_caution(class_name, function_name, error_comment);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ErrorManager::output_caution(string class_name, string function_name, vector<string> error_comment)
{
  if( err_mes_opt == err_mes_default || (err_mes_opt == err_mes_skip_warning && output_mode == warning_on) )
  {
    cout << endl;
    cout << "=====================" << endl;
    cout << "=                   =" << endl;
    cout << "=  --- CAUTION ---  =" << endl;
    cout << "=                   =" << endl;
    cout << "=====================" << endl;
    cout << endl;
    cout << "  <Class name>" << endl;
    cout << "    " << class_name << endl << endl;
    cout << "  <Function name>" << endl;
    cout << "    " << function_name << endl << endl;
    cout << "  <Warning message>" << endl;

    int i_max = static_cast<int>(error_comment.size());
    if( i_max > 0 )
    {
      for(int i=0; i<i_max; i++)
      {
        cout << "    " << error_comment[i] << endl;
      }
    }
    cout << endl;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ErrorManager::output_caution(string class_name, string function_name, string error_comment)
{
  vector<string> error_vec;
  error_vec.clear();

  if( static_cast<int>(error_comment.size()) > 0 )
  {
    error_vec.push_back(error_comment);
  }
  output_caution(class_name, function_name, error_vec);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ErrorManager::set_err_mes_opt(int int_value)
{
  if( int_value == err_mes_default )
  {
    err_mes_opt = err_mes_default;
  }
  else if( int_value == err_mes_debug )
  {
    err_mes_opt = err_mes_debug;
  }
  else if( int_value == err_mes_skip_warning )
  {
    err_mes_opt = err_mes_skip_warning;
  }
  else
  {
    string class_name = "ErrorManager";
    string func_name  = "set_err_mes_opt(int int_value)";

    ostringstream oss;
    oss << int_value;
    string str_data = "Error message option : " + oss.str();

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("This error message option is not available.");
    err_com.push_back("Please check the error message option.");

    output_runtime_error(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int ErrorManager::get_err_mes_opt()
{
  return err_mes_opt;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ErrorManager::set_err_mes_format_opt(int int_value)
{
  if( int_value == no_output_format_warning )
  {
    err_mes_format_opt = no_output_format_warning;
  }
  else if( int_value == output_format_warning )
  {
    err_mes_format_opt = output_format_warning;
  }
  else
  {
    string class_name = "ErrorManager";
    string func_name  = "set_err_mes_format_opt(int int_value)";

    ostringstream oss;
    oss << int_value;
    string str_data = "Error message option for format : " + oss.str();

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("This error message option for format is not available.");
    err_com.push_back("Please check the error message option.");

    output_runtime_error(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int ErrorManager::get_err_mes_format_opt()
{
  return err_mes_format_opt;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ErrorManager::set_err_mes_nan_opt(int int_value)
{
  if( int_value == warning_runtime_error )
  {
    err_mes_nan_opt = warning_runtime_error;
  }
  else if( int_value == warning_caution )
  {
    err_mes_nan_opt = warning_caution;
  }
  else
  {
    string class_name = "ErrorManager";
    string func_name  = "set_err_mes_nan_opt(int int_value)";

    ostringstream oss;
    oss << int_value;
    string str_data = "Error message option for nan : " + oss.str();

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("This error message option for nan is not available.");
    err_com.push_back("Available option is as follows:");
    err_com.push_back("  runtime_error : 0 (default)");
    err_com.push_back("  caution       : 1");
    err_com.push_back("");
    err_com.push_back("Please check the error message option.");

    output_runtime_error(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int ErrorManager::get_err_mes_nan_opt()
{
  return err_mes_nan_opt;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ErrorManager::set_output_mode(int int_value)
{
  if( int_value == warning_on )
  {
    output_mode = warning_on;
  }
  else if( int_value == warning_off )
  {
    output_mode = warning_off;
  }
  else
  {
    string class_name = "ErrorManager";
    string func_name  = "set_output_mode(int int_value)";

    ostringstream oss;
    oss << int_value;
    string str_data = "Output message option : " + oss.str();

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("This output message option is not available.");
    err_com.push_back("Please check the error message option.");

    output_runtime_error(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int ErrorManager::get_output_mode()
{
  return output_mode;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

