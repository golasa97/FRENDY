#include "CommonUtils/TabInterpolator.hpp"

using namespace frendy;

//constructor
TabInterpolator::TabInterpolator(void)
{
}

//destructor
TabInterpolator::~TabInterpolator(void)
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

/*
void TabInterpolator::interpolation_tab1(Real8& x, Real8& y,
                                          vector<Integer>& nbt_data, vector<Integer>& int_data,
                                          vector<Real>& x_data, vector<Real>& y_data)
{
  //search neighbir value (x_data[i_m] < x < x_data[i_p])
  int i_m, i_p;
  int i_max = static_cast<int>(x_data.size());
  vector<Real8> x_data_real;
  x_data_real.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    x_data_real[i] = static_cast<Real8>(x_data[i]);
  }
  search_neighbor_value(x, x_data_real, i_m, i_p);

  if( check_boundary_data(x, y, i_m, i_p, x_data, y_data) > 0 )
  {
    return;
  }

  Real8 x_m = static_cast<Real8>(x_data[i_m]);
  Real8 x_p = static_cast<Real8>(x_data[i_p]);
  Real8 y_m = static_cast<Real8>(y_data[i_m]);
  Real8 y_p = static_cast<Real8>(y_data[i_p]);

  //search interporation method
  Integer int_val = search_interpolation_range(nbt_data, int_data, i_p);

  //Interpolation
  interpolation_1d(int_val, x, y, x_m, y_m, x_p, y_p);
}
*/

//////////////////////////////////////////////////////////////////////////////////////////////////////

void TabInterpolator::interpolation_tab1(Real8& x, Real8& y,
                                         vector<Integer>& nbt_data, vector<Integer>& int_data,
                                          vector<Real8>& x_data, vector<Real8>& y_data)
{
  //search neighbir value (x_data[i_m] < x < x_data[i_p])
  int i_m, i_p;
  search_neighbor_value(x, x_data, i_m, i_p);

  if( check_boundary_data(x, y, i_m, i_p, x_data, y_data) > 0 )
  {
    return;
  }

  //search interporation method
  Integer int_val = search_interpolation_range(nbt_data, int_data, i_p);

  //Interpolation
  interpolation_1d(int_val, x, y, x_data[i_m], y_data[i_m], x_data[i_p], y_data[i_p]);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void TabInterpolator::mod_rounding_error(Real8& x, Real8& y, int i_m, int i_p,
                                         vector<Real8>& x_data, vector<Real8>& y_data)
{
  //Modify rounding error
  int i_sta = i_m - 1;
  int i_end = i_p + 1;
  if( i_sta < 0 )
  {
    i_sta = 0;
  }
  if( i_end >= static_cast<int>(y_data.size()) )
  {
    i_end = i_p;
  }

  //Check out of range
//  if( x < digit_obj.get_adjusted_value(x_data[i_sta], sig_fig, -1.0) || 
//      x > digit_obj.get_adjusted_value(x_data[i_end], sig_fig, +1.0)  )
  if( x < x_data[i_sta] * 0.999999999 || x > x_data[i_end] * 1.000000001 )
  {
    return;
  }

  int m_flg = 0;
  int p_flg = 0;
  for(int i=i_sta; i<=i_end; i++)
  {
    if( y_data[i] > min_value )
    {
      p_flg++;
    }
    else if( y_data[i] < -1.0*min_value )
    {
      m_flg++;
    }
  }

  if( (m_flg == 0 && p_flg > 0 && y < 0.0) ||
      (p_flg == 0 && m_flg > 0 && y > 0.0) )
  {
    y = 0.0;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

int TabInterpolator::check_boundary_data(Real8& x, Real8& y, int i_m, int i_p,
                                         vector<Real8>& x_data, vector<Real8>& y_data)
{
  int boundary_flg = -1;
  if( (x_data.size()) > 0 && static_cast<int>(y_data.size()) > 0 )
  {
    if( i_m == 0 )
    {
      //(10000000.1 - 10000000.1) / 10000000.0 = 1.0e-8
      if( fabs(x - x_data[i_m]) < x_data[i_m]*1.1e-8 )
      {
        y = y_data[i_m];
        boundary_flg = 1;
      }
    }
    else if( i_p == static_cast<int>(x_data.size()) - 1 )
    {
      if( fabs(x - x_data[i_p]) < x_data[i_p]*1.1e-8 )
      {
        y = y_data[i_p];
        boundary_flg = 1;
      }
    }
  }

  return boundary_flg;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void TabInterpolator::interpolation_tab1_in_range(Real8& x, Real8& y,
                                                  vector<Integer>& nbt_data, vector<Integer>& int_data,
                                                   vector<Real8>& x_data, vector<Real8>& y_data)
{
  //Interpolation is only available in x_data range (x_data[0] - x_data[i_max-1])
  //When x is smaller than x_data[0] or larger than x_data[i_max-1], y is 0.0.

  int i_max = static_cast<int>(x_data.size());
  if( i_max == 0 )
  {
    y = 0.0;
  }
  else if( x*1.000000001 < x_data[0] )
  {
    y = 0.0;
  }
  else if( x > x_data[i_max-1]*1.000000001 )
  {
    y = 0.0;
  }
  else
  {
    interpolation_tab1(x, y, nbt_data, int_data, x_data, y_data);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void TabInterpolator::interpolation_1d(Integer int_val, Real8& x, Real8& y, 
                                       vector<Real8>& x_data, vector<Real8>& y_data)
{
  //search neighbir value (x_data[i_m] < x < x_data[i_p])
  int i_m, i_p;
  search_neighbor_value(x, x_data, i_m, i_p);

  if( check_boundary_data(x, y, i_m, i_p, x_data, y_data) > 0 )
  {
    return;
  }

  //Interpolation
  interpolation_1d(int_val, x, y, x_data[i_m], y_data[i_m], x_data[i_p], y_data[i_p]);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void TabInterpolator::interpolation_1d_in_range(Integer int_val, Real8& x, Real8& y, 
                                                vector<Real8>& x_data, vector<Real8>& y_data)
{
  //Interpolation is only available in x_data range (x_data[0] - x_data[i_max-1])
  //When x is smaller than x_data[0] or larger than x_data[i_max-1], y is 0.0.

  int i_max = static_cast<int>(x_data.size());
  if( i_max == 0 )
  {
    y = 0.0;
  }
  else if( x*1.00001 < x_data[0] )
  {
    y = 0.0;
  }
  else if( x > x_data[i_max-1]*1.00001 )
  {
    y = 0.0;
  }
  else
  {
    interpolation_1d(int_val, x, y, x_data, y_data);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void TabInterpolator::interpolation_1d(Integer int_val, Real8& x, Real8& y, 
                                        Real8& x_m, Real8& y_m, Real8& x_p, Real8& y_p)
{
  if( fabs(x_m - x_p) < fabs(x_m*min_ene_dif)  )
  {
    if( x > x_p || fabs(x - x_p) < fabs(x_p*min_ene_dif) )
    {
      y = y_p;
    }
    else
    {
      y = y_m;
    }
    return;
  }

  if( fabs(x_m - x) <= fabs(x_m*min_ene_dif)  )
  {
    y = y_m;
    return;
  }
  else if( fabs(x_p - x) <= fabs(x_p*min_ene_dif)  )
  {
    y = y_p;
    return;
  }

  if( int_val == int_lin_lin )
  {
    interpolation_linear_linear(x, y, x_m, y_m, x_p, y_p);
  }
  else
  {
    switch( int_val )
    {
      case int_const:
        interpolation_const(x, y, x_m, y_m, x_p, y_p);
        break;
      case int_log_lin:
        interpolation_log_linear(x, y, x_m, y_m, x_p, y_p);
        break;
      case int_lin_log:
        interpolation_linear_log(x, y, x_m, y_m, x_p, y_p);
        break;
      case int_log_log:
        interpolation_log_log(x, y, x_m, y_m, x_p, y_p);
        break;
      default:
        string class_name = "TabInterpolator";
        string func_name  = "interpolation_1d(Integer& int_val, Real8& x, Real8& y, ";
               func_name += "Real8& x_m, Real8& y_m, Real8& x_p, Real8& y_p)";

        ostringstream oss;
        oss << int_val;
        string str_data = "Interpolation scheme number : " + oss.str();

        vector<string> err_com;
        err_com.push_back(str_data);
        err_com.push_back("This interpolation scheme number is not available.");
        err_com.push_back("Please check the interpolation scheme number.");

        err_obj.output_runtime_error(class_name, func_name, err_com);
        break;
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

/*
void TabInterpolator::interpolation_tab1(Real8& x, Real8& y,
                                         vector<Integer>& nbt_data, vector<Integer>& int_data,
                                         vector<Real>& x_data, vector<Real>& y_data, Real& q, Real& thrx)
{
  //search neighbir value (x_data[i_m] < x < x_data[i_p])
  int i_m, i_p;
  int i_max = static_cast<int>(x_data.size());
  vector<Real8> x_data_real;
  x_data_real.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    x_data_real[i] = static_cast<Real8>(x_data[i]);
  }
  search_neighbor_value(x, x_data_real, i_m, i_p);

  Real8 x_m = static_cast<Real8>(x_data[i_m]);
  Real8 x_p = static_cast<Real8>(x_data[i_p]);
  Real8 y_m = static_cast<Real8>(y_data[i_m]);
  Real8 y_p = static_cast<Real8>(y_data[i_p]);

  Real8 q_r    = static_cast<Real8>(q);
  Real8 thrx_r = static_cast<Real8>(thrx);

  //search interporation method
  Integer int_val = search_interpolation_range(nbt_data, int_data, i_p);

  //Interpolation
  interpolation_1d(int_val, x, y, x_m, y_m, x_p, y_p, q_r, thrx_r);

  if( fabs(y) > min_value )
  {
    check_boundary_data(x, y, i_m, i_p, x_data, y_data);
  }
}
*/

////////////////////////////////////////////////////////////////////////////////////////////////////

void TabInterpolator::interpolation_tab1(Real8& x, Real8& y,
                                         vector<Integer>& nbt_data, vector<Integer>& int_data,
                                         vector<Real8>& x_data, vector<Real8>& y_data, Real8& q, Real8& thrx)
{
  //search neighbir value (x_data[i_m] < x < x_data[i_p])
  int i_m, i_p;
  search_neighbor_value(x, x_data, i_m, i_p);

  //search interporation method
  Integer int_val = search_interpolation_range(nbt_data, int_data, i_p);

  //Interpolation
  interpolation_1d(int_val, x, y, x_data[i_m], y_data[i_m], x_data[i_p], y_data[i_p], q, thrx);

  if( fabs(y) > min_value )
  {
    check_boundary_data(x, y, i_m, i_p, x_data, y_data);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void TabInterpolator::interpolation_tab1_in_range
                        (Real8& x, Real8& y, vector<Integer>& nbt_data, vector<Integer>& int_data,
                         vector<Real8>& x_data, vector<Real8>& y_data, Real8& q, Real8& thrx)
{
  //Interpolation is only available in x_data range (x_data[0] - x_data[i_max-1])
  //When x is smaller than x_data[0] or larger than x_data[i_max-1], y is 0.0.

  int i_max = static_cast<int>(x_data.size());
  if( i_max == 0 )
  {
    y = 0.0;
  }
  else if( x*1.00001 < x_data[0] )
  {
    y = 0.0;
  }
  else if( x > x_data[i_max-1]*1.00001 )
  {
    y = 0.0;
  }
  else
  {
    interpolation_tab1(x, y, nbt_data, int_data, x_data, y_data, q, thrx);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void TabInterpolator::interpolation_1d(Integer int_val, Real8& x, Real8& y, 
                                       vector<Real8>& x_data, vector<Real8>& y_data, Real8& q, Real8& thrx )
{
  //search neighbir value (x_data[i_m] < x < x_data[i_p])
  int i_m, i_p;
  search_neighbor_value(x, x_data, i_m, i_p);

  //Interpolation
  interpolation_1d(int_val, x, y, x_data[i_m], y_data[i_m], x_data[i_p], y_data[i_p], q, thrx);

  if( fabs(y) > min_value )
  {
    check_boundary_data(x, y, i_m, i_p, x_data, y_data);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void TabInterpolator::interpolation_1d_in_range(Integer int_val, Real8& x, Real8& y, 
                                                vector<Real8>& x_data, vector<Real8>& y_data,
                                                Real8& q, Real8& thrx )
{
  //Interpolation is only available in x_data range (x_data[0] - x_data[i_max-1])
  //When x is smaller than x_data[0] or larger than x_data[i_max-1], y is 0.0.

  int i_max = static_cast<int>(x_data.size());
  if( i_max == 0 )
  {
    y = 0.0;
  }
  else if( x*1.00001 < x_data[0] )
  {
    y = 0.0;
  }
  else if( x > x_data[i_max-1]*1.00001 )
  {
    y = 0.0;
  }
  else
  {
    interpolation_1d(int_val, x, y, x_data, y_data, q, thrx);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void TabInterpolator::interpolation_1d(Integer int_val, Real8& x, Real8& y,
                                       Real8& x_m, Real8& y_m, Real8& x_p, Real8& y_p, Real8& q, Real8& thrx)
{
  if( fabs(x_m - x_p) < x_m*min_value  )
  {
    if( x > x_p )
    {
      y = y_p;
    }
    else
    {
      y = y_m;
    }
    return;
  }

  if( fabs(x_m - x) < x_m*min_value  )
  {
    y = y_m;
    return;
  }
  else if( fabs(x_p - x) < x_p*min_value  )
  {
    y = y_p;
    return;
  }

  if( int_val == int_lin_lin )
  {
    interpolation_linear_linear(x, y, x_m, y_m, x_p, y_p);
  }
  else
  {
    switch( int_val )
    {
      case int_const:
        interpolation_const(x, y, x_m, y_m, x_p, y_p);
        break;
      case int_log_lin:
        interpolation_log_linear(x, y, x_m, y_m, x_p, y_p);
        break;
      case int_lin_log:
        interpolation_linear_log(x, y, x_m, y_m, x_p, y_p);
        break;
      case int_log_log:
        interpolation_log_log(x, y, x_m, y_m, x_p, y_p);
        break;
      case int_special_1d:
        interpolation_special_1d_law(x, y, x_m, y_m, x_p, y_p, q, thrx);
        break;
      default:
        string class_name = "TabInterpolator";
        string func_name  = "interpolation_1d(Integer& int_val, Real8& x, Real8& y, "; 
               func_name += "Real8& x_m, Real8& y_m, Real8& x_p, Real8& y_p, Real8& q, Real8& thrx)";

        ostringstream oss;
        oss << int_val;
        string str_data = "Interpolation scheme number : " + oss.str();

        vector<string> err_com;
        err_com.push_back(str_data);
        err_com.push_back("This interpolation scheme number is not available.");
        err_com.push_back("Please check the interpolation scheme number.");

        err_obj.output_runtime_error(class_name, func_name, err_com);
        break;
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void TabInterpolator::interpolation_tab1(Real8& x, Real8& y,
                                         vector<Integer>& nbt_data, vector<Integer>& int_data,
                                         vector<Real8>& x_data, vector<Real8>& y_data, Real8& threshold)
{
  //search neighbir value (x_data[i_m] < x < x_data[i_p])
  int i_m, i_p;
  search_neighbor_value(x, x_data, i_m, i_p);

  //search interporation method
  Integer int_val = search_interpolation_range(nbt_data, int_data, i_p);

  //Interpolation
  interpolation_1d(int_val, x, y, x_data[i_m], y_data[i_m], x_data[i_p], y_data[i_p], threshold);

  if( fabs(y) > min_value )
  {
    check_boundary_data(x, y, i_m, i_p, x_data, y_data);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void TabInterpolator::interpolation_tab1_in_range
                        (Real8& x, Real8& y, vector<Integer>& nbt_data, vector<Integer>& int_data,
                         vector<Real8>& x_data, vector<Real8>& y_data, Real8& threshold)
{
  //Interpolation is only available in x_data range (x_data[0] - x_data[i_max-1])
  //When x is smaller than x_data[0] or larger than x_data[i_max-1], y is 0.0.

  int i_max = static_cast<int>(x_data.size());
  if( i_max == 0 )
  {
    y = 0.0;
  }
  else if( x*1.00001 < x_data[0] )
  {
    y = 0.0;
  }
  else if( x > x_data[i_max-1]*1.00001 )
  {
    y = 0.0;
  }
  else
  {
    interpolation_tab1(x, y, nbt_data, int_data, x_data, y_data, threshold);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void TabInterpolator::interpolation_1d(Integer int_val, Real8& x, Real8& y, 
                                       vector<Real8>& x_data, vector<Real8>& y_data, Real8& threshold )
{
  //search neighbir value (x_data[i_m] < x < x_data[i_p])
  int i_m, i_p;
  search_neighbor_value(x, x_data, i_m, i_p);

  //Interpolation
  interpolation_1d(int_val, x, y, x_data[i_m], y_data[i_m], x_data[i_p], y_data[i_p], threshold);

  if( fabs(y) > min_value )
  {
    check_boundary_data(x, y, i_m, i_p, x_data, y_data);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void TabInterpolator::interpolation_1d_in_range(Integer int_val, Real8& x, Real8& y, 
                                                vector<Real8>& x_data, vector<Real8>& y_data, Real8& threshold )
{
  //Interpolation is only available in x_data range (x_data[0] - x_data[i_max-1])
  //When x is smaller than x_data[0] or larger than x_data[i_max-1], y is 0.0.

  int i_max = static_cast<int>(x_data.size());
  if( i_max == 0 )
  {
    y = 0.0;
  }
  else if( x*1.00001 < x_data[0] )
  {
    y = 0.0;
  }
  else if( x > x_data[i_max-1]*1.00001 )
  {
    y = 0.0;
  }
  else
  {
    interpolation_1d(int_val, x, y, x_data, y_data, threshold);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void TabInterpolator::interpolation_1d(Integer int_val, Real8& x, Real8& y,
                                       Real8& x_m, Real8& y_m, Real8& x_p, Real8& y_p, Real8& threshold)
{
  if( x < threshold )
  {
    y = 0.0;
    return;
  }

  if( fabs(x_m - x_p) < x_m*min_value  )
  {
    if( x > x_p )
    {
      y = y_p;
    }
    else
    {
      y = y_m;
    }
    return;
  }

  if( fabs(x_m - x) < x_m*min_value  )
  {
    y = y_m;
    return;
  }
  else if( fabs(x_p - x) < x_p*min_value  )
  {
    y = y_p;
    return;
  }

  if( int_val == int_lin_lin )
  {
    interpolation_linear_linear(x, y, x_m, y_m, x_p, y_p);
  }
  else
  {
    switch( int_val )
    {
      case int_const:
        interpolation_const(x, y, x_m, y_m, x_p, y_p);
        break;
      case int_log_lin:
        interpolation_log_linear(x, y, x_m, y_m, x_p, y_p);
        break;
      case int_lin_log:
        interpolation_linear_log(x, y, x_m, y_m, x_p, y_p);
        break;
      case int_log_log:
        interpolation_log_log(x, y, x_m, y_m, x_p, y_p);
        break;
      default:
        string class_name = "TabInterpolator";
        string func_name  = "interpolation_1d(Integer& int_val, Real8& x, Real8& y, "; 
               func_name += "Real8& x_m, Real8& y_m, Real8& x_p, Real8& threshold)";

        ostringstream oss;
        oss << int_val;
        string str_data = "Interpolation scheme number : " + oss.str();

        vector<string> err_com;
        err_com.push_back(str_data);
        err_com.push_back("This interpolation scheme number is not available.");
        err_com.push_back("Please check the interpolation scheme number.");

        err_obj.output_runtime_error(class_name, func_name, err_com);
        break;
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void TabInterpolator::search_neighbor_value(Real8& x_real, vector<Real8>& x_data, int& i_m, int& i_p)
{
  int   x_min     = 0;
  int   x_max     = static_cast<int>(x_data.size()) - 1;
  //int   x_max_ori = x_max;
  int   x_mid     = (x_min + x_max) / 2;
  Real8 x_dif     = x_real*(1.0 - min_ene_dif);
  if( x_max < 0 )
  {
    string class_name = "TabInterpolator";
    string func_name  = "search_neighbor_value(Real8& x_real, vector<Real8>& x_data, int& i_m, int& i_p)";
    vector<string> err_com;
    err_com.push_back("There is no data in x_data.(The element number of x_data is zero.)");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  while( x_max - x_min >= 2 )
  {
    //(x_real - x_data[x_mid])/x_real > pow(0.1, sig_fig+1)
    if( x_data[x_mid] < x_dif )
    {
      x_min = x_mid;
    }
    else
    {
      x_max = x_mid;
    }
    x_mid = (x_min + x_max) / 2;
  }

  i_p   = -1;
  for(int i=x_min; i<=x_max; i++)
  {
    //(x_real - x_data[i])/x_real < pow(0.1, sig_fig+1)
    if( x_data[i] > x_dif )
    {
      i_p = i;
      break;
    }
  }
  if( i_p < 0 )
  {
    i_p = x_max;
    //cout << "!!! C A U T I O N !!!" << endl;
    //cout << "  Extrapolation worning was occured at table interpolation." << endl;
    //cout << "  The x value is larger than max value of x[i]." << endl;
    //cout << "  x[i_max] : " << x_data[x_max-1] << endl;
    //cout << "  x        : " << x_real         << endl;
    //cout << endl;
  }

  if( i_p > 0 )
  {
    i_m = i_p - 1;
  }
  else
  {
    i_p = 1;
    i_m = 0;
    if( i_p > x_max )
    {
      i_p = x_max;
    }

    //cout << "!!! C A U T I O N !!!" << endl;
    //cout << "  Extrapolation worning was occured at table interpolation." << endl;
    //cout << "  The x value is smaller than minmum value of x[i]." << endl;
    //cout << "  x[0]     : " << x_data[0] << endl;
    //cout << "  x        : " << x_real   << endl;
    //cout << endl;
  }

/*
  if( i_p < x_max_ori )
  {
    if( fabs(x_data[i_p] - x_data[i_p+1]) < fabs(min_ene_dif*x_data[i_p]) )
    {
      string class_name = "TabInterpolator";
      string func_name  = "search_neighbor_value";
      ostringstream oss01, oss02, oss03, oss04;
      oss03.setf(ios::showpoint);
      oss03.setf(ios::scientific);
      oss04.setf(ios::showpoint);
      oss04.setf(ios::scientific);
      oss01 << i_p;
      oss02 << x_max_ori;
      oss03 << setw(10) << x_data[i_p];
      oss04 << setw(10) << x_data[i_p+1];
      string str_data01 = "position (i_p) : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "x_data[i_p]    : " + oss03.str();
      string str_data03 = "x_data[i_p+1]  : " + oss04.str();
      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back("The neighbor value is identical.");
      err_com.push_back("FRENDY uses x_data[i_p] for upper side value.");
      err_obj.output_caution(class_name, func_name, err_com);
    }
  }

  if( i_m != 0 )
  {
    if( fabs(x_data[i_m] - x_data[i_m-1]) < fabs(min_ene_dif*x_data[i_m]) )
    {
      string class_name = "TabInterpolator";
      string func_name  = "search_neighbor_value";
      ostringstream oss01, oss02, oss03, oss04;
      oss03.setf(ios::showpoint);
      oss03.setf(ios::scientific);
      oss04.setf(ios::showpoint);
      oss04.setf(ios::scientific);
      oss01 << i_p;
      oss02 << x_max_ori;
      oss03 << setw(10) << x_data[i_m];
      oss04 << setw(10) << x_data[i_m-1];
      string str_data01 = "position (i_m) : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "x_data[i_m]    : " + oss03.str();
      string str_data03 = "x_data[i_m-1]  : " + oss04.str();
      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back("The neighbor value is identical.");
      err_com.push_back("FRENDY uses x_data[i_m] for lower side value.");
      err_obj.output_caution(class_name, func_name, err_com);
    }
  }
*/
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Integer TabInterpolator::search_interpolation_range(vector<Integer>& nbt_data, vector<Integer>& int_data, 
                                                    int i_pos)
{
  int nbt_pos = get_interpolation_range_pos(nbt_data, int_data, i_pos);

  return int_data[nbt_pos];
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int TabInterpolator::get_interpolation_range_pos(vector<Integer>& nbt_data, vector<Integer>& int_data, 
                                                 int i_pos)
{
  int nbt_max = static_cast<int>(nbt_data.size());
  if( nbt_max <= 0 )
  {
    string class_name = "TabInterpolator";
    string func_name  = "get_interpolation_range_pos(vector<Integer>& nbt_data, vector<Integer>& int_data, ";
           func_name  = func_name + "int i_pos)";
    vector<string> err_com;
    err_com.push_back("There is no data in nbt_data.(The element number of nbt_data is zero.)");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  int nbt_pos = -1;
  for(int i=0; i<nbt_max; i++)
  {
    if( i_pos < nbt_data[i] )
    {
      nbt_pos = i;
      break;
    }
  }
  if( nbt_pos < 0 )
  {
    nbt_pos = nbt_max - 1;
  }
  return nbt_pos;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void TabInterpolator::interpolation_const(Real8& x, Real8& y,
                                          Real8& x_m, Real8& y_m, Real8& x_p, Real8& y_p)
{
  if( x < x_p )
  {
    //y = a
    y = y_m;
  }
  else
  {
    y = y_p;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void TabInterpolator::interpolation_linear_linear(Real8& x, Real8& y,
                                                  Real8& x_m, Real8& y_m, Real8& x_p, Real8& y_p)
{
  //y = a*x + b
  Real8 a;
  a = (y_p - y_m) / (x_p - x_m);

  y = a*(x - x_m) + y_m;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void TabInterpolator::get_interpolation_linear_linear_coef(Real8& a_val, Real8& b_val,
                                                           Real8& x_m, Real8& y_m, Real8& x_p, Real8& y_p)
{
  //y = a*x + b
  a_val = (y_p - y_m) / (x_p - x_m);

  b_val = y_m - a_val*x_m;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void TabInterpolator::interpolation_linear_log(Real8& x, Real8& y,
                                               Real8& x_m, Real8& y_m, Real8& x_p, Real8& y_p)
{
  //ln(y) = a*x + b
  if( y_m < min_value || y_p < min_value ) 
  {
    y = 0.0;
  }
  else
  {
    Real8 a, y_ln;
    a = (log(y_p/y_m)) / (x_p - x_m);

    y_ln = a*(x - x_m);
    y    = y_m*exp(y_ln);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void TabInterpolator::interpolation_log_linear(Real8& x, Real8& y,
                                               Real8& x_m, Real8& y_m, Real8& x_p, Real8& y_p)
{
  //y = a*ln(x) + b
  Real8 a;
  a = (y_p - y_m) / (log(x_p/x_m));

  y = a*(log(x/x_m)) + y_m;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void TabInterpolator::interpolation_log_log(Real8& x, Real8& y,
                                            Real8& x_m, Real8& y_m, Real8& x_p, Real8& y_p)
{
  if( y_m < min_value || y_p < min_value ) 
  {
    y = 0.0;
  }
  else if( fabs(y_m - y_p) < min_value )
  {
    y = y_p;
  }
  else
  {
    //ln(y) = a*ln(x) + b
    Real8 a, y_ln;
    a = (log(y_p/y_m)) / (log(x_p/x_m));

    y_ln = a*(log(x/x_m));
    y    = y_m*exp(y_ln);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void TabInterpolator::interpolation_special_1d_law(Real8& x, Real8& y, 
                                                   Real8& x_m, Real8& y_m, Real8& x_p, Real8& y_p, 
                                                   Real8& q, Real8& thrx)
{
  Real8 t_val, a, b;
  if( q > 0.0 || thrx < 0.0 )
  {
    t_val = 0.0;
  }
  else
  {
    t_val = thrx;
  }

  Real8 xy_m  = y_m * x_m;
  Real8 xy_p  = y_p * x_p;
  Real8 tmp_m = sqrt(x_m - t_val);
  Real8 tmp_p = sqrt(x_p - t_val);

  b = log(xy_p/xy_m) / ( (1.0/tmp_m) - (1.0/tmp_p) );
  a = exp(b/tmp_m) * xy_m;
  
  y = (a/x) * exp(-b/sqrt(x - t_val));
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void TabInterpolator::interpolation_2d(Integer int_val, Real8& x, vector<Integer>& range_vec,
       vector<Integer>& int_vec, vector<Real8>& y, vector<Real8>& z, Real8& x_m, Real8& x_p,
       vector<Integer>& range_m, vector<Integer>& int_m, vector<Real8>& y_m, vector<Real8>& z_m,
       vector<Integer>& range_p, vector<Integer>& int_p, vector<Real8>& y_p, vector<Real8>& z_p)
{
  y.clear();
  z.clear();
  if( fabs(x_m - x_p) < x_m*min_value  )
  {
    if( x > x_p )
    {
      range_vec = range_p;
      int_vec   = int_p;
      y         = y_p;
      z         = z_p;
    }
    else
    {
      range_vec = range_m;
      int_vec   = int_m;
      y         = y_m;
      z         = z_m;
    }
    return;
  }

  if( fabs(x_m - x) < x_m*min_value  )
  {
    range_vec = range_m;
    int_vec   = int_m;
    y         = y_m;
    z         = z_m;
    return;
  }
  else if( fabs(x_p - x) < x_p*min_value  )
  {
    range_vec = range_p;
    int_vec   = int_p;
    y         = y_p;
    z         = z_p;
    return;
  }

  vector<Real8> z_main, y_sub, z_sub;
  Real8         x_main, x_sub;
  if( fabs(x - x_m) < fabs(x - x_p) )
  {
    range_vec = range_m;
    int_vec   = int_m;
    x_main    = x_m;
    z_main    = z_m;
    x_sub     = x_p;
    y_sub     = y_p;
    z_sub     = z_p;
    mod_grid_data(y_m, z_main, range_p, int_p, y_sub, z_sub);
  }
  else
  {
    range_vec = range_p;
    int_vec   = int_p;
    x_main    = x_p;
    z_main    = z_p;
    x_sub     = x_m;
    y_sub     = y_m;
    z_sub     = z_m;
    mod_grid_data(y_p, z_main, range_m, int_m, y_sub, z_sub);
  }
  y = y_sub;

  int i_max = static_cast<int>(z_main.size());
  z.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    if( x_main < x_sub )
    {
      interpolation_1d(int_val, x, z[i], x_main, z_main[i], x_sub, z_sub[i]);
    }
    else
    {
      interpolation_1d(int_val, x, z[i], x_sub, z_sub[i], x_main, z_main[i]);
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void TabInterpolator::interpolation_2d(Real8& x, Real8& y, Real8& z, 
       vector<Integer>& range_x, vector<Integer>& int_x, vector<Real8>& x_grid,
       vector<vector<Integer> >& range_y, vector<vector<Integer> >& int_y,
       vector<vector<Real8> >& y_grid, vector<vector<Real8> >& y_data)
{
  int i_max = static_cast<int>(x_grid.size());
  if( static_cast<int>(y_grid.size()) != i_max )
  {
    string class_name = "TabInterpolator";
    string func_name  = "interpolation_2d(Real8& x, Real8& y, Real8& z, ";
           func_name += "vector<Integer>& range_x, vector<Integer>& int_x, vector<Real8>& x_grid, ";
           func_name += "vector<vector<Integer> >& range_y, vector<vector<Integer> >& int_y, ";
           func_name += "vector<vector<Real8> >& y_grid, vector<vector<Real8> >& y_data)";

    ostringstream oss01, oss02;
    oss01 << i_max;
    oss02 << static_cast<int>(y_grid.size());
    string str_data01 = "Grid number of x-axis : " + oss01.str();
    string str_data02 = "Grid number of y-axis : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("Grid number of x-axis and y-axis is not identical");
    err_com.push_back("This program can not treat such data.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  int i_m, i_p, jm_m, jm_p, jp_m, jp_p;
  search_neighbor_value(x, x_grid, i_m, i_p);
  search_neighbor_value(y, y_grid[i_m], jm_m, jm_p);
  search_neighbor_value(y, y_grid[i_p], jp_m, jp_p);

  Integer int_val = search_interpolation_range(range_x, int_x, i_p);
  Integer int_ym  = search_interpolation_range(range_y[i_m], int_y[i_m], jm_p);
  Integer int_yp  = search_interpolation_range(range_y[i_p], int_y[i_p], jp_p);

  Real z_m, z_p;
  interpolation_1d(int_ym, y, z_m,
                   y_grid[i_m][jm_m], y_data[i_m][jm_m], y_grid[i_m][jm_p], y_data[i_m][jm_p]);
  interpolation_1d(int_yp, y, z_p,
                   y_grid[i_p][jp_m], y_data[i_p][jp_m], y_grid[i_p][jp_p], y_data[i_p][jp_p]);

  interpolation_1d(int_val, x, z, x_grid[i_m], z_m, x_grid[i_p], z_p);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void TabInterpolator::mod_grid_data(vector<Real8>& grid_main, vector<Real8>& data_main,
                                    vector<Integer>& range_sub, vector<Integer>& int_sub,
                                    vector<Real8>& grid_sub, vector<Real8>& data_sub)
{
  int i_max  = static_cast<int>(grid_main.size());
  int ele_no = 0;
  vector<Real8> data_sub_mod;
  data_sub_mod.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    while( grid_main[i] - min_value > grid_sub[ele_no] )
    {
      ele_no++;
    }
    interpolation_tab1(grid_main[i], data_sub_mod[i], range_sub, int_sub, grid_sub, data_sub);
  }
  grid_sub.clear();
  data_sub.clear();
  grid_sub = grid_main;
  data_sub = data_sub_mod;
  data_sub_mod.clear();
}

