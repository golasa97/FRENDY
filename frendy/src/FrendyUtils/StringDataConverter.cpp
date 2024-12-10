#include "FrendyUtils/StringDataConverter.hpp"

using namespace frendy;

StringDataConverter::StringDataConverter(void)
{
}

StringDataConverter::~StringDataConverter(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<Integer> StringDataConverter::get_int_data_list(vector<string> str_vec)
{
  Integer data_sta =  1;
  vector<Integer> int_vec;
  int_vec.clear();

  str_vec = str_util.divide_minus_value(str_vec);

  int i_max = static_cast<int>(str_vec.size());
  if( i_max == 1 )
  {
    transform(str_vec[0].begin(), str_vec[0].end(), str_vec[0].begin(), ::tolower);

    if( static_cast<int>(str_vec[0].find("all")) == 0 )
    {
      //If str_vec[0] == "all", this functions returns void int_vec data.
      int_vec.clear();
      return int_vec;
    }
  }

  for(int i=0; i<i_max; i++)
  {
    str_vec[i] = str_util.trim_space(str_vec[i]);
    if( static_cast<int>(str_vec[i].length()) == 0 )
    {
      continue;
    }

    if( static_cast<int>(str_vec[i].length()) == 1 )
    {
      if( str_vec[i] == "-" || str_vec[i] == "_" )
      {
        i++;
        if( i >= i_max )
        {
          continue;
        }
        while( static_cast<int>(str_vec[i].length()) == 0 )
        {
          i++;
          if( i >= i_max )
          {
            continue;
          }
        }
        if( i >= i_max )
        {
          continue;
        }

        str_obj.string_check(str_vec[i]);
        Integer data_end = numeric_string_cast<Integer>(str_vec[i]);
        for(Integer j=0; j<(data_end - data_sta + 1); j++)
        {
          int_vec.push_back(data_sta + j);
        }
        data_sta = data_end + 1;
        continue;
      }
    }

    str_obj.string_check(str_vec[i]);
    Integer data_end = numeric_string_cast<Integer>(str_vec[i]);
    if( data_end > 0 )
    {
      int_vec.push_back(data_end);
    }
    else if( data_end < 0 )
    {
      data_end *= -1;
      for(Integer j=0; j<(data_end - data_sta + 1); j++)
      {
        int_vec.push_back(data_sta + j);
      }
    }
    data_sta = data_end + 1;
  }

  sort_int_data_list(int_vec);

  return int_vec;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void StringDataConverter::sort_int_data_list(vector<Integer>& int_vec)
{
  int i_max = static_cast<int>(int_vec.size());
  if( i_max <= 1 )
  {
    return;
  }

  sort(int_vec.begin(), int_vec.end());

  vector<Integer> int_vec_new;
  int_vec_new.push_back(int_vec[0]);

  for(int i=1; i<i_max; i++)
  {
    if( int_vec[i] != int_vec[i-1] )
    {
      int_vec_new.push_back(int_vec[i]);
    }
  }

  int_vec = int_vec_new;
  int_vec_new.clear();
}

