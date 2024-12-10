#ifndef ENDF_UTILS_H
#define ENDF_UTILS_H

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <string>
#include <math.h>

#include "CommonUtils/ErrorManager.hpp"

namespace frendy
{
  template<typename T> T numeric_string_cast(std::string str)
  {
    std::string lowStr = boost::to_lower_copy(str);
    boost::trim(lowStr);
    if(lowStr.empty())
    {
      return static_cast<T>(0.0);
    }

    std::string::size_type pos    = lowStr.find_first_of("+- ", 1);
    std::string::size_type pos_pm = lowStr.find_first_of("+-", 1);
    if(pos == std::string::npos)
    {
      return boost::lexical_cast<T>(lowStr);
    }

    std::string mantissa_str = lowStr.substr(0, pos);
    std::string exponent_str = lowStr.substr(pos);

    std::string::size_type char_pos = mantissa_str.find_first_of(" ed");
    while( char_pos != std::string::npos )
    {
      mantissa_str.erase(char_pos, 1);
      char_pos = mantissa_str.find_first_of(" ed");
    }

    char_pos = exponent_str.find_first_of(" ed");
    while( char_pos != std::string::npos )
    {
      exponent_str.erase(char_pos, 1);
      char_pos = exponent_str.find_first_of(" ed");
    }

    T   mantissa = boost::lexical_cast<T>(mantissa_str);
    int exponent = boost::lexical_cast<int>(exponent_str);

    if(pos != std::string::npos && pos_pm == std::string::npos)
    {
      frendy::ErrorManager err_obj;
      std::string class_name = "EndfUtils";
      std::string func_name  = "numeric_string_cast(std::string str)";

      std::ostringstream oss;
      oss.precision(15);
      oss.setf(ios::showpoint);
      oss.setf(ios::scientific);
      oss << mantissa*static_cast<T>(pow(10, exponent));

      std::string str_data01 = "Data             : " + lowStr;
      std::string str_data02 = "Mantissa of data : " + mantissa_str;
      std::string str_data03 = "Exponent of data : " + exponent_str;
      std::string str_data04 = "Read data value  : " + oss.str();

      std::vector<std::string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back(str_data04);
      err_com.push_back("");
      err_com.push_back("This data may inappropriate value.");
      err_com.push_back("Please check that this data is appropriate or not.");
      err_obj.output_caution(class_name, func_name, err_com);
    }

    return mantissa*static_cast<T>(pow(10, exponent));
  }
}

#endif //ENDF_UTILS_H
