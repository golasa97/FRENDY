#include "CommonUtils/TimeUtils.hpp"

using namespace frendy;

//constructor
TimeUtils::TimeUtils(void)
{
}

//destructor
TimeUtils::~TimeUtils(void)
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

string TimeUtils::convert_int_to_string(int int_data)
{
  ostringstream oss_data;
  oss_data << int_data;

  string str_data;
  if( int_data < 10 )
  {
    str_data= "0" + oss_data.str();
  }
  else
  {
    str_data = oss_data.str();
  }

  return str_data;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

string TimeUtils::get_current_date()
{
  struct tm *date_info;
  time_t current_time;

  time(&current_time);

  date_info = localtime(&current_time);

  string str_yy, str_mm, str_dd;
  str_yy  = convert_int_to_string(date_info->tm_year + 1900);
  str_mm  = convert_int_to_string(date_info->tm_mon  + 1);
  str_dd  = convert_int_to_string(date_info->tm_mday);

  string str_data = str_yy + "/" + str_mm + "/" + str_dd;
  return str_data;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

string TimeUtils::get_current_date_no_slash()
{
  struct tm *date_info;
  time_t current_time;

  time(&current_time);

  date_info = localtime(&current_time);

  string str_yy, str_mm, str_dd;
  str_yy  = convert_int_to_string(date_info->tm_year + 1900);
  str_mm  = convert_int_to_string(date_info->tm_mon  + 1);
  str_dd  = convert_int_to_string(date_info->tm_mday);

  string str_data = str_yy + str_mm  + str_dd;
  return str_data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

string TimeUtils::get_current_date_dd_mmm_yyyy()
{
  struct tm *date_info;
  time_t current_time;

  time(&current_time);

  date_info = localtime(&current_time);

  string str_yy, str_mm, str_dd, str_hh, str_min, str_sec;
  str_yy  = convert_int_to_string(date_info->tm_year + 1900);
  str_dd  = convert_int_to_string(date_info->tm_mday);

  int int_mm  = date_info->tm_mon  + 1;
  switch( int_mm )
  {
    case 1:
      str_mm = "Jan";
      break;
    case 2:
      str_mm = "Feb";
      break;
    case 3:
      str_mm = "Mar";
      break;
    case 4:
      str_mm = "Apr";
      break;
    case 5:
      str_mm = "May";
      break;
    case 6:
      str_mm = "Jun";
      break;
    case 7:
      str_mm = "Jul";
      break;
    case 8:
      str_mm = "Aug";
      break;
    case 9:
      str_mm = "Sep";
      break;
    case 10:
      str_mm = "Oct";
      break;
    case 11:
      str_mm = "Nov";
      break;
    case 12:
      str_mm = "Dec";
      break;
    default:
      str_mm = "   ";
      break;
  }

  string str_data = str_dd + "/" + str_mm + "/" + str_yy;
  return str_data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

string TimeUtils::get_current_time()
{
  struct tm *date_info;
  time_t current_time;

  time(&current_time);

  date_info = localtime(&current_time);

  string str_yy, str_mm, str_dd, str_hh, str_min, str_sec;
  str_yy  = convert_int_to_string(date_info->tm_year + 1900);
  str_mm  = convert_int_to_string(date_info->tm_mon  + 1);
  str_dd  = convert_int_to_string(date_info->tm_mday);
  str_hh  = convert_int_to_string(date_info->tm_hour);
  str_min = convert_int_to_string(date_info->tm_min);
  str_sec = convert_int_to_string(date_info->tm_sec);

  string str_data = str_yy + "/" + str_mm + "/" + str_dd + " "
                  + str_hh + ":" + str_min + ":" + str_sec;
  return str_data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void TimeUtils::output_current_date()
{
  string data = get_current_date();
  cout << "FRENDY calculation date : " << data << endl << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void TimeUtils::output_current_time()
{
  string data = get_current_time();
  cout << "FRENDY calculation date : " << data << endl << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
