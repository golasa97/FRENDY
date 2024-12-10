#include "TabUtils/LinearizeTabData.hpp"

using namespace frendy;

int LinearizeTabData::essential_fig = essential_fig_default;

//constructor
LinearizeTabData::LinearizeTabData(void)
{
  err_relative_def = 1.0E-3;
  err_min_def      = err_relative_def * 1.0E-3;
}

//destructor
LinearizeTabData::~LinearizeTabData(void)
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void LinearizeTabData::linearize_data(Integer int_val, vector<Real>& x_data, vector<Real>& y_data)
{
  linearize_data(int_val, x_data, y_data, err_relative_def, err_min_def);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void LinearizeTabData::linearize_data(Integer int_val, vector<Real>& x_data, vector<Real>& y_data,
                                      Real err_relative, Real err_min)
{
  int data_no = static_cast<int>(x_data.size());

  vector<Integer> range_vec, int_vec;
  range_vec.resize(1);
  int_vec.resize(1);

  range_vec[0] = data_no;
  int_vec[0]   = int_val;

  linearize_tab1_data(range_vec, int_vec, x_data, y_data, err_relative, err_min);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void LinearizeTabData::linearize_tab1_data( vector<Integer>& range_data, vector<Integer>& int_data,
                                            vector<Real>&    x_data,     vector<Real>&    y_data)
{
  linearize_tab1_data(range_data, int_data, x_data, y_data, err_relative_def, err_min_def);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void LinearizeTabData::linearize_tab1_data( vector<Integer>& range_data, vector<Integer>& int_data,
                                            vector<Real>&    x_data,     vector<Real>&    y_data,
                                            Real err_relative )
{
  Real err_min = err_relative * 1.0E-3;
  linearize_tab1_data(range_data, int_data, x_data, y_data, err_relative, err_min);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void LinearizeTabData::linearize_tab1_data( vector<Integer>& range_data, vector<Integer>& int_data,
                                            vector<Real>&    x_data,     vector<Real>&    y_data,
                                            Real err_relative, Real err_min )
{
  check_tab1_data(range_data, int_data, x_data, y_data);

  Integer lin_chk_flg = check_int_data(range_data, int_data, x_data);
  if( lin_chk_flg == 0 )
  {
    return;
  }

  linearize_tab1_data_without_data_check(range_data, int_data, x_data, y_data, err_relative, err_min);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void LinearizeTabData::linearize_tab1_data_without_data_check
                         ( vector<Integer>& range_data, vector<Integer>& int_data,
                           vector<Real>&    x_data,     vector<Real>&    y_data,
                           Real err_relative, Real err_min )
{
  Real         mid_x, mid_y;
  vector<Real> new_x, new_y, new_x_part, new_y_part;
  new_x.clear();
  new_y.clear();
  new_x_part.clear();
  new_y_part.clear();

  int     j;
  int     i_max     = static_cast<int>(x_data.size());
  int     range     = 0;
  int     range_max = static_cast<int>(range_data.size());
  if( i_max == 0 || range_max == 0 )
  {
    return;
  }

  Integer int_val   = int_data[0];
  Integer int_chk;

  Real x_val, y_val;
  x_val = digit_obj.get_truncation_value(x_data[0]);
  ti_obj.interpolation_tab1(x_val, y_val, range_data, int_data, x_data, y_data);
  
  new_x.push_back(x_val);
  new_y.push_back(y_val);
  while( range_data[range] < 1 )
  {
    range++;
    if( range >= range_max )
    {
      int_val = int_data[range_max-1];
      break;
    }
    else
    {
      int_val = int_data[range];
    }
  }

  for(int i=1; i<i_max; i++)
  {
    while( range_data[range] < i+1 )
    {
      range++;
      if( range >= range_max )
      {
        int_val = int_data[range_max-1];
        break;
      }
      else
      {
        int_val = int_data[range];
      }
    }

    if( int_val != int_const )
    {
      x_val = digit_obj.get_truncation_value(x_data[i-1]);
      ti_obj.interpolation_tab1(x_val, y_val, range_data, int_data, x_data, y_data);
      new_x_part.push_back(x_val);
      new_y_part.push_back(y_val);

      x_val = digit_obj.get_truncation_value(x_data[i]);
      ti_obj.interpolation_tab1(x_val, y_val, range_data, int_data, x_data, y_data);
      new_x_part.push_back(x_val);
      new_y_part.push_back(y_val);

      j = 1;
      int_chk = comp_interpolation_value(j, int_val, new_x_part, new_y_part,
                                         mid_x, mid_y, err_relative, err_min);
      while( int_chk < 0 || j < static_cast<int>(new_x_part.size()-1))
      {
        if( int_chk == 0 )
        {
          j++;
        }
        else
        {
          insert_middle_x_data(j, new_x_part, new_y_part, mid_x, mid_y);
        }
        int_chk = comp_interpolation_value(j, int_val, new_x_part, new_y_part,
                                           mid_x, mid_y, err_relative, err_min);
      }
    }
    else //if( int_val == int_const )
    {
      Real x_p = digit_obj.get_adjusted_value(x_data[i], sig_fig, -1.0); 
      new_x_part.push_back(x_data[i-1]);
      new_y_part.push_back(y_data[i-1]);
      new_x_part.push_back(x_p);
      new_y_part.push_back(y_data[i-1]);
      new_x_part.push_back(x_data[i]);
      new_y_part.push_back(y_data[i]);
    }
    add_x_and_y_data(new_x, new_y, new_x_part, new_y_part);
  }

  //Renewal range and int data
  renewal_interpolation_scheme_list(range_data, int_data, x_data, new_x);
  modify_range_and_int_data(range_data, int_data, new_x);

  x_data = new_x;
  y_data = new_y;
  new_x.clear();
  new_y.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Integer LinearizeTabData::comp_interpolation_value( int& ele_no, Integer& int_val,
                                                    vector<Real>& x_data, vector<Real>& y_data,
                                                    Real& mid_x, Real& mid_y,
                                                    Real err_relative, Real err_min )
{
  Integer chk_flg = 0;

  mid_x = 0.5*(x_data[ele_no] + x_data[ele_no-1]);
  mid_x = digit_obj.get_truncation_value(mid_x);
  if( fabs(mid_x - x_data[ele_no])   < min_ene_dif * mid_x ||
      fabs(mid_x - x_data[ele_no-1]) < min_ene_dif * mid_x )
  {
    chk_flg = 0;
    return chk_flg;
  }

  //Interpolation which specified by evaluated nuclear data file
  ti_obj.interpolation_1d(int_val, mid_x, mid_y,
                          x_data[ele_no-1], y_data[ele_no-1], x_data[ele_no], y_data[ele_no]);
  mid_y = digit_obj.get_truncation_value(mid_y);

  if( int_val > 2 )
  {
    //Interpolation by linear-linear
    Real    mid_y_line   = 0.0;
    Integer int_val_line = int_lin_lin;
    ti_obj.interpolation_1d(int_val_line, mid_x, mid_y_line,
                            x_data[ele_no-1], y_data[ele_no-1], x_data[ele_no], y_data[ele_no]);
    mid_y_line = digit_obj.get_truncation_value(mid_y_line);

    Real delta_y = fabs(mid_y - mid_y_line);
    Real err     = fabs(err_relative*mid_y);
    if( err < err_min )
    {
      err = err_min;
    }

    if( delta_y > err )
    {
      chk_flg = -1;
    }
  }

  return chk_flg;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void LinearizeTabData::insert_middle_x_data( int ele_no, vector<Real>& x_data, vector<Real>& y_data,
                                             Real& mid_x, Real& mid_y )
{
  ta_obj.add_table_data_at_given_position(x_data, y_data, mid_x, mid_y, ele_no);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void LinearizeTabData::add_x_and_y_data( vector<Real>& new_x,      vector<Real>& new_y,
                                         vector<Real>& new_x_part, vector<Real>& new_y_part )
{
  int k_max = static_cast<int>(new_x_part.size());
  for(int k=1; k<k_max; k++)
  {
    new_x.push_back(new_x_part[k]);
    new_y.push_back(new_y_part[k]);
  }
  new_x_part.clear();
  new_y_part.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void LinearizeTabData::renewal_interpolation_scheme_list
                         ( vector<Integer>& range_data, vector<Integer>& int_data,
                           vector<Real>&    x_data,     vector<Real>&    new_x )
{
  vector<Integer> new_range, new_int;
  new_range.clear();
  new_int.clear();

  int   ele_no  = 0;
  int   ele_max = static_cast<int>(new_x.size());
  int   i_max   = static_cast<int>(range_data.size());
  Real8 x_max;
  for(int i=0; i<i_max; i++)
  {
    x_max = x_data[static_cast<int>(range_data[i]-1)];

    while( new_x[ele_no] <= x_max && ele_no < ele_max )
    {
      ele_no++;
    }
    new_range.push_back(static_cast<Integer>(ele_no));

    new_int.push_back(int_lin_lin);
  }
  range_data = new_range;
  int_data = new_int;
  new_range.clear();
  new_int.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void LinearizeTabData::modify_range_and_int_data(vector<Integer>& range_data, vector<Integer>& int_data,
                                                 vector<Real>&    x_data)
{
  int i_max = static_cast<int>(int_data.size());
  if( i_max <= 1 )
  {
    return;
  }

  Integer int_ori = int_data[0];
  Integer int_chk = 0;
  for(int i=1; i<i_max; i++)
  {
    if( int_data[i] != int_ori )
    {
      int_chk = 1;
      break;
    }
  }

  if( int_chk == 0 )
  {
    int_data.clear();
    range_data.clear();

    Integer x_data_no = static_cast<int>(x_data.size());
    int_data.resize(1);
    range_data.resize(1);

    int_data[0]   = int_ori;
    range_data[0] = x_data_no;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void LinearizeTabData::normalize_tab1_data(Integer& int_val, vector<Real>& x_data, vector<Real>& y_data)
{
  vector<Integer> range_data, int_data;
  range_data.resize(1);
  int_data.resize(1);
  range_data[0] = static_cast<Integer>(x_data.size());
  int_data[0]   = int_val;

  normalize_tab1_data(range_data, int_data, x_data, y_data);

  int_val = int_data[0];
  range_data.clear();
  int_data.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void LinearizeTabData::normalize_tab1_data
                         (vector<Integer>& range_data, vector<Integer>& int_data,
                          vector<Real>&    x_data,     vector<Real>&    y_data)
{
  check_tab1_data(range_data, int_data, x_data, y_data);

  Integer lin_chk_flg = check_int_data(range_data, int_data, x_data);
  if( lin_chk_flg == 1 )
  {
#ifdef NJOY_MODE

    //skip linearlization process output caution
    string class_name = "LinearizeTabData";
    string func_name  = "normalize_tab1_data";

    vector<string> err_com;
    err_com.push_back("Interpolation scheme (i+1 / i_max : range_data[i] : int_data[i])");
    for(int i=0; i<static_cast<int>(int_data.size()); i++)
    {
      ostringstream oss01, oss02, oss03, oss04;
      oss01 << i+1;
      oss02 << static_cast<int>(int_data.size());
      oss03 << range_data[i];
      oss04 << int_data[i];

      string str_data = "  " + oss01.str() + " / " + oss02.str() + " : "
                        + oss03.str() + " : " + oss04.str();
      err_com.push_back(str_data);
    }


    err_com.push_back("");
    err_com.push_back("This program processes ACE file collectly only when the interpolation scheme is as follows:");
    err_com.push_back("  INT = 1 : constant");
    err_com.push_back("  INT = 2 : linear-linear");
    err_obj.output_caution(class_name, func_name, err_com);

#else //ifndef NJOY_MODE

    //Linearization of table data before normalization
    Real error_relative = 1.0E-3;
    Real error_min      = error_relative * 1.0E-3; //1.0E-6
    linearize_tab1_data_without_data_check(range_data, int_data, x_data, y_data,
                                           error_relative, error_min);
#endif //NJOY_MODE
  }

  normalize_tab1_data_without_data_check(range_data, int_data, x_data, y_data);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void LinearizeTabData::normalize_tab1_data_without_data_check
                         (vector<Integer>& range_data, vector<Integer>& int_data,
                          vector<Real>&    x_data,     vector<Real>&    y_data)
{
  int i_max = static_cast<int>(y_data.size());
  if( i_max <= 1 )
  {
    return;
  }

  int non_zero_flg = 0;
  for(int i=0; i<i_max; i++)
  {
    if( fabs(y_data[i]) > min_value )
    {
      non_zero_flg = 1;
      break;
    }
  }
  if( non_zero_flg == 0 )
  {
    string class_name = "LinearizeTabData";
    string func_name  = "normalize_tab1_data_without_data_check";

    vector<string> err_com;
    err_com.push_back("All y data is zero.");
    err_com.push_back("The normarization process is skipped.");
    err_com.push_back("  i / i_max : x_data[i], y_data[i]");
    for(int i=0; i<i_max; i++)
    {
      ostringstream oss01, oss02, oss03, oss04;
      oss01 << i+1;
      oss02 << i_max;
      oss03 << setw(8) << std::showpoint << std::scientific << x_data[i];
      oss04 << setw(8) << std::showpoint << std::scientific << y_data[i];
      string str_data01 = "  " + oss01.str() + " / " + oss02.str() + " : " + oss03.str() + ", " + oss04.str();
      err_com.push_back(str_data01);
    }

    err_com.push_back("");
    err_com.push_back("This table data may be wrong.");
    err_obj.output_caution(class_name, func_name, err_com);
    return;
  }

  modify_tab_data(range_data, int_data, x_data, y_data);

  Real8 integrate_val = 0.0;
  for(int i=1; i<i_max; i++)
  {
    integrate_val += static_cast<Real8>(0.5*(x_data[i] - x_data[i-1]) * (y_data[i] + y_data[i-1]));
  }

  Real integrate_inv = 1.0 / static_cast<Real>(integrate_val);
  for(int i=0; i<i_max; i++)
  {
    y_data[i] *= integrate_inv;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void LinearizeTabData::check_tab1_data( vector<Integer>& range_data, vector<Integer>& int_data,
                                        vector<Real>& x_data,        vector<Real>& y_data )
{
  int i_max = static_cast<int>(int_data.size());
  if( i_max != static_cast<int>(range_data.size()) )
  {
    string class_name = "LinearizeTabData";
    string func_name  = "check_tab1_data";
    ostringstream oss01, oss02;
    oss01 << i_max;
    oss02 << static_cast<int>(range_data.size());

    string str_data01 = "Number of interpolation data : " + oss01.str();
    string str_data02 = "Number of range data         : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("Number of interpolation data is not identical to that of range data.");
    err_com.push_back("Please check the tab1 data.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
  else if( i_max == 0 )
  {
    string class_name = "LinearizeTabData";
    string func_name  = "check_tab1_data";
    vector<string> err_com;
    err_com.push_back("Number of interpolation and range data is zero.");
    err_com.push_back("Please check the tab1 data.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  int range_max, range_pre;
  range_max = static_cast<int>(range_data[i_max-1]);
  if( i_max > 1 )
  {
    range_pre = static_cast<int>(range_data[i_max-2]);
  }
  else
  {
    range_pre = 0;
  }

  i_max = static_cast<int>(x_data.size());
  if( i_max != static_cast<int>(y_data.size()) )
  {
    string class_name = "LinearizeTabData";
    string func_name  = "check_tab1_data";
    ostringstream oss01, oss02;
    oss01 << i_max;
    oss02 << static_cast<int>(y_data.size());

    string str_data01 = "Number of x data : " + oss01.str();
    string str_data02 = "Number of y data : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("Number of x data is not identical to that of y data.");
    err_com.push_back("Please check the tab1 data.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
  else if( i_max == 0 )
  {
    string class_name = "LinearizeTabData";
    string func_name  = "check_tab1_data";
    vector<string> err_com;
    err_com.push_back("Number of x and y data is zero.");
    err_com.push_back("Please check the tab1 data.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
  else if( i_max > range_max )
  {
    string class_name = "LinearizeTabData";
    string func_name  = "check_tab1_data";
    ostringstream oss01, oss02;
    oss01 << i_max;
    oss02 << range_max;

    string str_data01 = "Number of x and y data : " + oss01.str();
    string str_data02 = "Maximum range          : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("Number of x and y data is larger than maximum range data");
    err_com.push_back("The tab1 data may not be appropriate.");
    err_com.push_back("The maximum range data is modified.");
    err_obj.output_caution(class_name, func_name, err_com);

    //Modify range data
    int pos = static_cast<int>(int_data.size());
    range_data[pos-1] = static_cast<Integer>(i_max);
  }
  else if( i_max < range_max )
  {
    if( i_max < range_pre )
    {
      string class_name = "LinearizeTabData";
      string func_name  = "check_tab1_data";
      ostringstream oss01, oss02, oss03;
      oss01 << i_max;
      oss02 << range_max;
      oss03 << range_pre;

      string str_data01 = "Number of x and y data : " + oss01.str();
      string str_data02 = "Maximum range          : " + oss02.str() + " - " + oss03.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back("The maximum range is out of range of x and y data.");
      err_com.push_back("The tab1 data may not be appropriate.");
      err_com.push_back("The maximum range data is modified.");
      err_obj.output_caution(class_name, func_name, err_com);
    }
    else
    {
      //Modify range data 
      int pos = static_cast<int>(range_data.size());
      range_data[pos-1] = static_cast<Integer>(i_max);
    }
  }

  for(int i=1; i<i_max; i++)
  {
    if( x_data[i] < x_data[i-1] - min_value )
    {
      string class_name = "LinearizeTabData";
      string func_name  = "check_tab1_data";
      ostringstream oss01, oss02, oss03, oss04, oss05;

      oss01 << i_max;
      oss02 << i-1;
      oss03 << i;
      oss04 << setw(8) << std::showpoint << std::scientific << x_data[i-1];
      oss05 << setw(8) << std::showpoint << std::scientific << x_data[i];

      string str_data01 = "Number of x and y data : " + oss01.str();
      string str_data02 = "x_data at i-1 = " + oss02.str() + " : " + oss04.str();
      string str_data03 = "x_data at i   = " + oss03.str() + " : " + oss05.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);

      if( fabs(x_data[i-1] - x_data[i]) < 1.0e-5 * fabs(x_data[i]) )
      {
        digit_obj.get_adjusted_value(x_data[i], sig_fig, +1.0);

        err_com.push_back("x data at i is identical to that at i-1.");
        err_com.push_back("x data at i is modified.");
        err_obj.output_caution(class_name, func_name, err_com);
      }
      else
      {
        err_com.push_back("The x data is not permutation layout.");
        err_com.push_back("Please check the tab1 data.");
        err_obj.output_runtime_error(class_name, func_name, err_com);
      }
    }
  }

  modify_tab_data(range_data, int_data, x_data, y_data);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void LinearizeTabData::modify_tab_data( vector<Integer>& range_data, vector<Integer>& int_data,
                                        vector<Real>&    x_data,     vector<Real>&    y_data )
{
  int i_max = static_cast<int>(x_data.size());
  if( i_max != 2 )
  {
    return;
  }

  //Check interpolation scheme
  int int_check = 0;
  for(int i=0; i<static_cast<int>(int_data.size()); i++)
  {
    if( int_data[i] != int_lin_lin )
    {
      int_check = 1;
      break;
    }
  }
  if( int_check == 0 )
  {
    return;
  }

  //Add element data from 2 to 3
  //This function is only available for element number = 2.

  vector<Real> x_data_new, y_data_new;

  i_max++; //i_max = 3;
  x_data_new.resize(i_max);
  y_data_new.resize(i_max);
  x_data_new[0] = x_data[0];
  x_data_new[2] = x_data[1];
  y_data_new[0] = y_data[0];
  y_data_new[2] = y_data[1];

  x_data_new[1] = 0.5*(x_data[0] + x_data[1]);
  ti_obj.interpolation_tab1(x_data_new[1], y_data_new[1], range_data, int_data, x_data, y_data);

  x_data = x_data_new;
  y_data = y_data_new;
  x_data_new.clear();
  y_data_new.clear();

  range_data[0] = static_cast<Integer>(i_max);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Integer LinearizeTabData::check_int_data( vector<Integer>& range_data, vector<Integer>& int_data,
                                          vector<Real>&    x_data )
{
  Integer lin_chk_flg = 0;

  //Check interpolation type
  int i_max = static_cast<int>(int_data.size());
  for(int i=0; i<i_max; i++)
  {
    if( int_data[i] != int_lin_lin )
    {
      lin_chk_flg = 1;
      break;
    }
  }

  if( lin_chk_flg == 0 )
  {
    modify_range_and_int_data(range_data, int_data, x_data);
  }

  return lin_chk_flg;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void LinearizeTabData::linearize_list_data_by_legendre_polynomial
                         (vector<Real>& list_data, vector<Real>& x_vec, vector<Real>& y_vec)
{
  vector<Real8> y_int;
  Real          sum = 0.0;
  linearize_list_data_by_legendre_polynomial(list_data, x_vec, y_vec, y_int, sum);
  y_int.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void LinearizeTabData::linearize_list_data_by_legendre_polynomial
                         (vector<Real>& list_data, vector<Real>& x_vec, vector<Real>& y_vec,
                          vector<Real>& y_int)
{
  Real sum = 0.0;
  linearize_list_data_by_legendre_polynomial(list_data, x_vec, y_vec, y_int, sum);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void LinearizeTabData::check_legendre_polynomial_list_data
                         (string class_name, string func_name, Integer reaction_type,
                          int i, int j, int k, int l, vector<Real>& list_data)
{
  int minus_val_chk = 0;
  int ele_no = static_cast<int>(list_data.size());
  for(int ii=0; ii<ele_no; ii++)
  {
    if( list_data[ii] < -1.0 * min_value )
    {
      minus_val_chk = 1;
      break;
    }
  }

  if( minus_val_chk != 0 )
  {
    ostringstream oss01, oss02, oss03, oss04, oss05;
    oss01 << reaction_type;
    oss02 << i+1;
    oss03 << j+1;
    oss04 << k+1;
    oss05 << l+1;

    vector<string> err_com;
    string str_data01 = "Reaction type : " + oss01.str();
    err_com.push_back(str_data01);
    if( i >= 0 )
    {
      string str_data02 = "Position (i)  : " + oss02.str();
      err_com.push_back(str_data02);
    }
    if( j >= 0 )
    {
      string str_data02 = "Position (j)  : " + oss03.str();
      err_com.push_back(str_data02);
    }
    if( k >= 0 )
    {
      string str_data02 = "Position (k)  : " + oss04.str();
      err_com.push_back(str_data02);
    }
    if( l >= 0 )
    {
      string str_data02 = "Position (l)  : " + oss05.str();
      err_com.push_back(str_data02);
    }

    err_com.push_back("The list data for Legendre polynomial has some minus data.");
    err_com.push_back("This list data may not be appropriate.");
    err_com.push_back("Using this list data, the angular distribution may not be appropriate.");
    err_obj.output_caution(class_name, func_name, err_com);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void LinearizeTabData::linearize_list_data_by_legendre_polynomial
                         (vector<Real>& list_data, vector<Real>& x_vec, vector<Real>& y_vec,
                          vector<Real>& y_int, Real& sum)
{
  vector<Real8> x_vec_r8, y_vec_r8;
  //Linearize list data
  linearize_list_data_by_legendre_polynomial_add_mid_point(list_data, x_vec_r8, y_vec_r8, y_int);

  //Delete extra (unnecessary) points
  linearize_list_data_by_legendre_polynomial_delete_extra_point(x_vec_r8, y_vec_r8, y_int);

  //Normalize y_vec
  int   i_max         = static_cast<int>(y_vec_r8.size());
  Real8 y_int_max_inv = y_int[i_max-1];
        sum           = 1.0;
  if( fabs(y_int_max_inv) < min_value )
  {
    y_int_max_inv = 1.0;
  }
  else
  {
    sum           = static_cast<Real>(y_int[i_max-1]);
    y_int_max_inv = 1.0 / y_int_max_inv;
  }

  x_vec.resize(i_max);
  y_vec.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    x_vec[i]  = static_cast<Real>(x_vec_r8[i]);
    y_vec[i]  = static_cast<Real>(y_vec_r8[i] * y_int_max_inv);
    y_int[i] *= y_int_max_inv;
  }
  x_vec_r8.clear();
  y_vec_r8.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void LinearizeTabData::linearize_list_data_by_legendre_polynomial_add_mid_point
                         ( vector<Real>& list_data, vector<Real8>& x_vec, vector<Real8>& y_vec,
                           vector<Real8>& y_int)
{
  Real8   err_min          = 1.0E-3;
  Integer list_data_no     = static_cast<Integer>(list_data.size());
  int     list_data_no_int = static_cast<int>(list_data_no);

  vector<Real8> coef_vec;
  if( list_data_no_int == 0 )
  {
    list_data_no_int = 1;
    coef_vec.resize(list_data_no_int);
    coef_vec[0] = 0.0;
  }
  else
  {
    coef_vec.resize(list_data_no_int);
    for(int i=0; i<list_data_no_int; i++)
    {
      coef_vec[i] = static_cast<Real8>(list_data[i]);
    }
  }

  int i_max = 101;
  x_vec.resize(i_max);
  y_vec.resize(i_max);
  Real8 x_sta =  1.0;
  Real8 x_end = -1.0;
  Real8 x_dif =  (x_sta - x_end) / (static_cast<Real8>(i_max - 1));
  for(int i=0; i<i_max; i++)
  {
    x_vec[i] = x_sta - static_cast<Real8>(i) * x_dif;
    y_vec[i] = calc_legendre_expansion(x_vec[i], list_data_no, coef_vec);
  }

  int ele_no = i_max - 1;
  while( ele_no > 0 )
  {
    Real8 delta_x =      x_vec[ele_no-1] - x_vec[ele_no];
    Real8 mid_x   = 0.5*(x_vec[ele_no-1] + x_vec[ele_no]);
    if( essential_fig > 0 )
    {
      mid_x = digit_obj.get_truncation_value(mid_x, essential_fig);
    }
    else
    {
      mid_x = digit_obj.get_truncation_value(mid_x);
    }

    if( x_vec[ele_no] < mid_x && mid_x < x_vec[ele_no-1] )
    {
      //Real8 mid_y_lin = 0.5*(y_vec[ele_no] + y_vec[ele_no-1]);
      Real8 mid_y_lin = 0.0;
      ti_obj.interpolation_1d(int_lin_lin, mid_x, mid_y_lin,
                              x_vec[ele_no-1], y_vec[ele_no-1],
                              x_vec[ele_no],   y_vec[ele_no]);
      Real8 mid_y_cal = calc_legendre_expansion(mid_x, list_data_no, coef_vec);
            mid_y_cal = digit_obj.get_truncation_value(mid_y_cal);
      Real8 mid_y_dif = fabs(mid_y_lin - mid_y_cal);

      if( delta_x > 0.01 || mid_y_dif > err_min*fabs(mid_y_cal) + min_ene_dif ||
         (fabs(mid_y_lin) > min_value && mid_y_cal/mid_y_lin > 5.0) ||
         (fabs(mid_y_lin) > min_value && mid_y_cal/mid_y_lin < 0.2) )
      {
        insert_middle_x_data(ele_no, x_vec, y_vec, mid_x, mid_y_cal); 
        ele_no++;
      }
      else
      {
        ele_no--;
      }
    }
    else
    {
      ele_no--;
    }
  }

  vector<Real8> x_new, y_new;
  i_max = static_cast<int>(y_vec.size());
  x_new.resize(i_max);
  y_new.resize(i_max);
  y_int.resize(i_max);
  y_int[0] = 0.0;
  for(int i=0; i<i_max; i++)
  {
    x_new[i] = x_vec[i_max-i-1];
    y_new[i] = y_vec[i_max-i-1];

    if( i > 0 )
    {
      y_int[i] = y_int[i-1] + 0.5*(x_new[i] - x_new[i-1])*(y_new[i] + y_new[i-1]);
    }

  }
  x_vec = x_new;
  y_vec = y_new;
  x_new.clear();
  y_new.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void LinearizeTabData::linearize_list_data_by_legendre_polynomial_delete_extra_point
                         ( vector<Real8>& x_vec, vector<Real8>& y_vec, vector<Real8>& y_int)
{
  Real delta_x_min = 0.50;

  vector<Real> x_new, y_new, y_int_new;
  int i_max  = static_cast<int>(x_vec.size());
  int i      = 0;
  int ele_no = 0;
  x_new.push_back(x_vec[i]);
  y_new.push_back(y_vec[i]);
  y_int_new.push_back(y_int[i]);
  while( i < i_max-1 )
  {
    int   j               = i;
    int   j_pos           = 0;
    Real8 delta_x         = 0.0; 
    Real8 diff_y_internal = 0.0;
    while( j < i_max && delta_x < delta_x_min && diff_y_internal < min_value )
    {
      j_pos = j;
      j++;
      if( j >= i_max )
      {
        continue;
      }

      delta_x = x_vec[j] - x_vec[i];
      if( delta_x < delta_x_min )
      {
        int k           = i;
        diff_y_internal = 0.0;
        while( k < j-1 && diff_y_internal < min_value )
        {
          k++;
          Real8 coef_int   = (x_vec[j] - x_vec[k]) / delta_x;
          Real8 y_internal = coef_int * y_vec[i] + (1.0-coef_int) * y_vec[j];
          diff_y_internal  = fabs(y_internal - y_vec[k]) - 0.001 * y_vec[k];

          if( diff_y_internal < min_value )
          {
            diff_y_internal  = fabs(y_internal - y_vec[k]) - 0.001 * y_internal;
          }
        }
      }
    }

    if( diff_y_internal > min_value || delta_x > delta_x_min* 0.99 )
    {
      i = j_pos;

      if( i < i_max-1 )
      {
        ele_no++;
        x_new.push_back(x_vec[i]);
        y_new.push_back(y_vec[i]);
  
        Real8 y_int_tmp = y_int_new[ele_no-1]
                        + 0.5*(x_new[ele_no] - x_new[ele_no-1])*(y_new[ele_no] + y_new[ele_no-1]);
        y_int_new.push_back(y_int_tmp);
      }
    }
    else
    {
      break;
    }
  }
  x_new.push_back(x_vec[i_max-1]);
  y_new.push_back(y_vec[i_max-1]);

  ele_no++;
  Real8 y_int_tmp = y_int_new[ele_no-1]
                  + 0.5*(x_new[ele_no] - x_new[ele_no-1])*(y_new[ele_no] + y_new[ele_no-1]);
  y_int_new.push_back(y_int_tmp);

  x_vec = x_new;
  y_vec = y_new;
  y_int = y_int_new;
  x_new.clear();
  y_new.clear();
  y_int_new.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Real8 LinearizeTabData::calc_legendre_expansion(Real8& x_val, Integer order, vector<Real8>& coef_vec)
{
  vector<Real8> legendre_vec = math_obj.legendre_expansion(x_val, order+1);

  Real8 y_val     = 0.5;
  Real8 coef_val  = 1.5;
  for(int i=0; i<static_cast<int>(order); i++)
  {
    y_val    += coef_val*coef_vec[i]*legendre_vec[i+1];
    coef_val += 1.0;
  }
  legendre_vec.clear();

  if( y_val < min_value )
  {
    y_val = min_value;
  }

  return y_val;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void LinearizeTabData::calc_equal_probability_table_by_tabulated_probability_data
                         ( int int_val, int bin_no, Real& sum_val,
                           vector<Real>& x_data, vector<Real>& y_data )
{
  Real sum_ave = sum_val / static_cast<Real>(bin_no);
  
  if( int_val == int_const )
  {
    calc_equal_probability_table_by_tabulated_probability_data_const(bin_no, sum_ave, x_data, y_data);
  }
  else if( int_val == int_lin_lin )
  {
    calc_equal_probability_table_by_tabulated_probability_data_lin_lin(bin_no, sum_ave, x_data, y_data);
  }
  else if( int_val == int_lin_log )
  {
    calc_equal_probability_table_by_tabulated_probability_data_lin_log(bin_no, sum_ave, x_data, y_data);
  }
  else
  {
    string class_name = "LinearizeTabData";
    string func_name  = "calc_equal_probability_table_by_tabulated_probability_data";
    ostringstream oss01;
    oss01 << int_val;
    string str_data01 = "Interpolation type : " + oss01.str();
    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("This interpolation type is not available.");
    err_com.push_back("Available interpolation type is constant, linear-linear or linear-log.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void LinearizeTabData::calc_equal_probability_table_by_tabulated_probability_data_const
                         ( int bin_no, Real& sum_ave, vector<Real>& x_data, vector<Real>& y_data )
{
  vector<Real> x_ori, y_ori, x_new;
  x_ori = x_data;
  y_ori = y_data;
  x_new.resize(bin_no+1);

  int  i_max    = static_cast<int>(x_data.size());
  int  ele_no   = 1;
  Real area     = 0.0;
  Real sum      = 0.0;
  Real residual = sum_ave;

  x_new[0]      = x_data[0];
  x_new[bin_no] = x_data[i_max-1];
  for(int i=0; i<i_max-1; i++)
  {
    area = y_data[i]*(x_data[i+1] - x_data[i]);
    while( area > residual && ele_no < bin_no )
    {
      if( y_data[i] < min_value )
      {
        if( i > 0 )
        {
          y_data[i] = y_data[i-1] * 1.0E-3;
        }
        else
        {
          y_data[i] = min_value;
        }
      }
      x_new[ele_no] = (residual / y_data[i]) + x_data[i];
      x_data[i]     = x_new[ele_no];

      area     = y_data[i]*(x_data[i+1] - x_data[i]);
      sum      = 0.0;
      residual = sum_ave;
      ele_no++;
    }

    sum      += area;
    residual -= area;
    if( ele_no == 1 && sum < 1.0E-10 )
    {
      x_new[ele_no] = x_data[i+1];
    }
  }

  vector<Real> y_new;
  y_new.resize(bin_no+1);
  for(int i=0; i<bin_no+1; i++)
  {
    ti_obj.interpolation_1d(int_const, x_new[i], y_new[i], x_ori, y_ori);
  }

  x_data = x_new;
  y_data = y_new;
  x_new.clear();
  y_new.clear();
  x_ori.clear();
  y_ori.clear();

  if( fabs(sum) > 1.0E-5 )
  {
    if( fabs(sum - sum_ave) > fabs(sum_ave)*1.0E-5 )
    {
      string class_name = "LinearizeTabData";
      string func_name  = "calc_equal_probability_table_by_tabulated_probability_data_const";

      ostringstream oss;
      oss << setw(10) << sum;
      string str_data = "Integrated area of distribution : " + oss.str();

      vector<string> err_com;
      err_com.push_back(str_data);
      err_com.push_back("The integrated area has large residual data.");
      err_com.push_back("This calculation may be wrong.");
      err_obj.output_caution(class_name, func_name, err_com);
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void LinearizeTabData::calc_equal_probability_table_by_tabulated_probability_data_lin_lin
                         ( int bin_no, Real& sum_ave, vector<Real>& x_data, vector<Real>& y_data )
{
  vector<Real> x_ori, y_ori, x_new;
  x_ori = x_data;
  y_ori = y_data;
  x_new.resize(bin_no+1);

  int  i_max    = static_cast<int>(x_data.size());
  int  ele_no   = 1;
  Real area     = 0.0;
  Real sum      = 0.0;
  Real residual = sum_ave;
  Real min_val  = min_sig_val;
  Real slope    = 0.0;

  x_new[0]      = x_data[0];
  x_new[bin_no] = x_data[i_max-1];
  for(int i=0; i<i_max-1; i++)
  {
    area = 0.5*(y_data[i+1] + y_data[i])*(x_data[i+1] - x_data[i]);
    while( area > residual && ele_no < bin_no )
    {
      if( residual < min_value )
      {
        x_new[ele_no] = x_data[i] + residual/y_data[i];
      }
      else
      {
        slope = (y_data[i+1] - y_data[i])/(x_data[i+1] - x_data[i]);
        if( fabs(slope) < min_val || fabs(slope) > 1.0 / min_val )
        {
          if( y_data[i] < min_value )
          {
            if( i > 0 )
            {
              y_data[i] = y_data[i-1] * 1.0E-3;
            }
            else
            {
              y_data[i] = min_value;
            }
          }
          x_new[ele_no] = (residual / y_data[i]) + x_data[i];
        }
        else
        {
          Real coef_b   = (slope * x_data[i]) - y_data[i];
          Real sqrt_val = y_data[i]*y_data[i] + 2.0*slope*residual;

          if( sqrt_val < -1.0*min_value )
          {
            sqrt_val = 0.0;

            string class_name = "LinearizeTabData";
            string func_name  = "calc_equal_probability_table_by_tabulated_probability_data_lin_lin";

            Real coef_a   = 0.5*slope;
            Real coef_c   = (0.5*slope*x_data[i] - y_data[i]) * x_data[i] - residual;

            ostringstream oss01, oss02, oss03, oss04;
            oss01 << setw(10) << coef_a;
            oss02 << setw(10) << -1.0 * coef_b;
            oss03 << setw(10) << coef_c;
            oss04 << setw(10) << sqrt_val;
            string str_data01 = "Coefficient a                   : " + oss01.str();
            string str_data02 = "Coefficient b                   : " + oss02.str();
            string str_data03 = "Coefficient c                   : " + oss03.str();
            string str_data04 = "Square root value (b*b - 4*a*c) : " + oss04.str();

            vector<string> err_com;
            err_com.push_back("Imaginary number is observed.");
            err_com.push_back(str_data01);
            err_com.push_back(str_data02);
            err_com.push_back(str_data03);
            err_com.push_back(str_data04);
            err_com.push_back("This calculation may be wrong.");
            err_obj.output_caution(class_name, func_name, err_com);
          }
          else if( sqrt_val < min_value )
          {
            sqrt_val = 0.0;
          }

          Real slope_inv = 1.0 / slope;
          sqrt_val = sqrt(sqrt_val);
          Real x_p = (coef_b + sqrt_val) * slope_inv;
          Real x_m = (coef_b - sqrt_val) * slope_inv;
          if( x_p < x_m ) //When slope < 0.0
          {
            x_m = (coef_b + sqrt_val) * slope_inv;
            x_p = (coef_b - sqrt_val) * slope_inv;
          }

          if( x_data[i] < x_p && x_p <= x_data[i+1] )
          {
            x_new[ele_no] = x_p;
          }
          else //if( x_data[i] < x_m && x_m <= x_data[i+1] )
          {
            x_new[ele_no] = x_m;
          }
        }
      }

      y_data[i] = y_data[i] + slope*(x_new[ele_no] - x_data[i]);
      x_data[i] = x_new[ele_no];

      area     = 0.5*(y_data[i+1] + y_data[i])*(x_data[i+1] - x_data[i]);
      sum      = 0.0;
      residual = sum_ave;
      ele_no++;
    }

    sum      += area;
    residual -= area;
    if( ele_no == 1 && sum < 1.0E-10 )
    {
      x_new[ele_no] = x_data[i+1];
    }
  }

  vector<Real> y_new;
  y_new.resize(bin_no+1);
  for(int i=0; i<bin_no+1; i++)
  {
    ti_obj.interpolation_1d(int_lin_lin, x_new[i], y_new[i], x_ori, y_ori);
  }

  x_data = x_new;
  y_data = y_new;
  x_new.clear();
  y_new.clear();
  x_ori.clear();
  y_ori.clear();

  if( fabs(sum) > 1.0E-3 )
  {
    if( fabs(sum - sum_ave) > fabs(sum_ave)*1.0E-3 )
    {
      string class_name = "LinearizeTabData";
      string func_name  = "calc_equal_probability_table_by_tabulated_probability_data_lin_lin";

      ostringstream oss;
      oss << setw(10) << sum;
      string str_data = "Integrated area of distribution : " + oss.str();

      vector<string> err_com;
      err_com.push_back(str_data);
      err_com.push_back("The integrated area has large residual data.");
      err_com.push_back("This calculation may be wrong.");
      err_obj.output_caution(class_name, func_name, err_com);
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void LinearizeTabData::calc_equal_probability_table_by_tabulated_probability_data_lin_log
                         ( int bin_no, Real& sum_ave, vector<Real>& x_data, vector<Real>& y_data )
{
  vector<Real> x_ori, y_ori, x_new;
  x_ori = x_data;
  y_ori = y_data;
  x_new.resize(bin_no+1);

  int  i_max    = static_cast<int>(x_data.size());
  int  ele_no   = 1;
  Real coef_a   = 0.0;
  Real area     = 0.0;
  Real mu_mid   = 0.0;
  Real sum      = 0.0;
  Real residual = sum_ave;

  x_new[0]      = x_data[0];
  x_new[bin_no] = x_data[i_max-1];
  for(int i=0; i<i_max-1; i++)
  {
    coef_a = log(y_data[i+1]/y_data[i]) / (x_data[i+1] - x_data[i]);
    if( fabs(coef_a) < 1.0E-5 )
    {
      area = y_data[i] * (x_data[i+1] - x_data[i]);
    }
    else
    {
      area = y_data[i] * (exp(coef_a*(x_data[i+1] - x_data[i])) - 1.0)/coef_a;
    }

    while( area > residual && ele_no < bin_no )
    {
      if( fabs(coef_a) < 1.0E-5 )
      {
        mu_mid = residual/y_data[i] + x_data[i];
      }
      else
      {
        mu_mid = log(coef_a*residual/y_data[i] + 1.0)/coef_a + x_data[i];
      }

      y_data[i]     = y_data[i]*exp(coef_a*(mu_mid - x_data[i]));
      x_new[ele_no] = mu_mid;
      x_data[i]     = mu_mid;

      coef_a = log(y_data[i+1]/y_data[i]) / (x_data[i+1] - x_data[i]);
      if( fabs(coef_a) < 1.0E-5 )
      {
        area = y_data[i] * (x_data[i+1] - x_data[i]);
      }
      else
      {
        area = y_data[i] * (exp(coef_a*(x_data[i+1] - x_data[i])) - 1.0)/coef_a;
      }
      sum      = 0.0;
      residual = sum_ave;
      ele_no++;
    }

    sum      += area;
    residual -= area;
    if( ele_no == 1 && sum < 1.0E-10 )
    {
      x_new[ele_no] = x_data[i+1];
    }
  }

  vector<Real> y_new;
  y_new.resize(bin_no+1);
  for(int i=0; i<bin_no+1; i++)
  {
    ti_obj.interpolation_1d(int_lin_log, x_new[i], y_new[i], x_ori, y_ori);
  }

  x_data = x_new;
  y_data = y_new;
  x_new.clear();
  y_new.clear();
  x_ori.clear();
  y_ori.clear();

  if( fabs(sum) > 1.0E-5 )
  {
    if( fabs(sum - sum_ave) > fabs(sum_ave)*1.0E-5 )
    {
      string class_name = "LinearizeTabData";
      string func_name  = "calc_equal_probability_table_by_tabulated_probability_data_lin_log";

      ostringstream oss;
      oss << setw(10) << sum;
      string str_data = "Integrated area of distribution : " + oss.str();

      vector<string> err_com;
      err_com.push_back(str_data);
      err_com.push_back("The integrated area has large residual data.");
      err_com.push_back("This calculation may be wrong.");
      err_obj.output_caution(class_name, func_name, err_com);
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

int  LinearizeTabData::get_essential_fig()
{
  return essential_fig;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void LinearizeTabData::set_essential_fig(int int_value)
{
  if( int_value < 0 )
  {
    int_value = 0;
  }

  essential_fig = int_value;
}

