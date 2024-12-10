#include "TabUtils/IntegrateTabData.hpp"

using namespace frendy;

//constructor
IntegrateTabData::IntegrateTabData(void)
{
  generate_mode_flg = generate_default_mode;

#ifdef NJOY_MODE
  generate_mode_flg = generate_njoy_mode;
#endif //NJOY_MODE
}

//destructor
IntegrateTabData::~IntegrateTabData(void)
{
  generate_mode_flg = generate_default_mode;

#ifdef NJOY_MODE
  generate_mode_flg = generate_njoy_mode;
#endif //NJOY_MODE
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Real IntegrateTabData::integrate_tab1_data( vector<Integer>& range_data, vector<Integer>& int_data,
                                            vector<Real>&    x_data,     vector<Real>&    y_data )
{
  lin_obj.check_tab1_data(range_data, int_data, x_data, y_data);

  return integrate_tab1_data_without_data_check(range_data, int_data, x_data, y_data);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Real IntegrateTabData::integrate_tab1_data_without_data_check
                         ( vector<Integer>& range_data, vector<Integer>& int_data,
                           vector<Real>&    x_data,     vector<Real>&    y_data )
{
  int     i_max      = static_cast<int>(x_data.size());
  int     ele_no     = 0;
  int     ele_no_max = static_cast<int>(range_data.size());
  Real8   sum        = 0.0;
  Integer int_val    = int_data[0];
  for(int i=1; i<i_max; i++)
  {
    while( range_data[ele_no] <= static_cast<Integer>(i) )
    {
      ele_no++;
      if( ele_no < ele_no_max )
      {
        int_val = int_data[ele_no];
      }
      else
      {
        ele_no--;
      }
    }

    sum += static_cast<Real8>(integrate_data(x_data[i-1], y_data[i-1], x_data[i], y_data[i], int_val));
  }

  return static_cast<Real>(sum);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Real IntegrateTabData::integrate_tab1_data( vector<Integer>& range_data, vector<Integer>& int_data,
                                            vector<Real>&    x_data,     vector<Real>&    y_data,
                                            Real x_min, Real x_max )
{
  lin_obj.check_tab1_data(range_data, int_data, x_data, y_data);

  return integrate_tab1_data_without_data_check(range_data, int_data, x_data, y_data, x_min, x_max);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Real IntegrateTabData::integrate_tab1_data_without_data_check
                         ( vector<Integer>& range_data, vector<Integer>& int_data,
                           vector<Real>&    x_data,     vector<Real>&    y_data,
                           Real x_min, Real x_max )
{
  int x_no = static_cast<int>(x_data.size());
  if( x_no <= 1 )
  {
    string class_name = "IntegrateTabData";
    string func_name  = "integrate_tab1_data_without_data_check";
    string str_data01 = "The number of x array is less than 1.";
    vector<string> err_com;
    err_com.push_back(str_data01);
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
  else if( x_min > x_max - min_value )
  {
    string class_name = "IntegrateTabData";
    string func_name  = "integrate_tab1_data_without_data_check";
    ostringstream oss01, oss02;
    oss01 << setw(10) << x_min;
    oss02 << setw(10) << x_max;
    string str_data01 = "Start point of integration (x_min) : " + oss01.str();
    string str_data02 = "End point of integration   (x_max) : " + oss02.str();
    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("x_min is larger than x_max.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
  else if( x_min < x_data[0] || x_max > x_data[x_no-1] )
  {
    string class_name = "IntegrateTabData";
    string func_name  = "integrate_tab1_data_without_data_check";
    ostringstream oss01, oss02, oss03, oss04;
    oss01 << setw(10) << x_data[0];
    oss02 << setw(10) << x_data[x_no-1];
    oss03 << setw(10) << x_min;
    oss04 << setw(10) << x_max;
    string str_data01 = "Start point of x array             : " + oss01.str();
    string str_data02 = "End point of x_array               : " + oss02.str();
    string str_data03 = "Start point of integration (x_min) : " + oss03.str();
    string str_data04 = "End point of integration   (x_max) : " + oss04.str();
    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back("Start point or end point of integration is out of range of x array");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  int pos_min, pos_max, pos_tmp;
  ti_obj.search_neighbor_value(x_min, x_data, pos_min, pos_tmp);
  ti_obj.search_neighbor_value(x_max, x_data, pos_tmp, pos_max);

  Real    sum     = 0.0;
  Integer int_val = 0;
  if( pos_max == pos_min+1 )
  {
    int_val = ti_obj.search_interpolation_range(range_data, int_data, pos_min);
    sum     = integrate_data(x_data[pos_min], y_data[pos_min], x_data[pos_max], y_data[pos_max],
                             int_val, x_min, x_max);
  }
  else
  {
    int_val  = ti_obj.search_interpolation_range(range_data, int_data, pos_min);
    sum      = integrate_data(x_data[pos_min], y_data[pos_min], x_data[pos_min+1], y_data[pos_min+1],
                              int_val, x_min, x_data[pos_min+1]);

    int_val  = ti_obj.search_interpolation_range(range_data, int_data, pos_max-1);
    sum     += integrate_data(x_data[pos_max-1], y_data[pos_max-1], x_data[pos_max], y_data[pos_max],
                              int_val, x_data[pos_max-1], x_max);
    for(int i=pos_min+1; i<pos_max-1; i++)
    {
      int_val  = ti_obj.search_interpolation_range(range_data, int_data, i);
      sum     += integrate_data(x_data[i], y_data[i], x_data[i+1], y_data[i+1], int_val);
    }
  }

  return sum;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Real IntegrateTabData::integrate_data(Real& x_m, Real& y_m, Real& x_p, Real& y_p, Integer int_val)
{
  return integrate_data(x_m, y_m, x_p, y_p, int_val, x_m, x_p);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Real IntegrateTabData::integrate_data(Real& x_m, Real& y_m, Real& x_p, Real& y_p, Integer int_val,
                                      Real& x_min, Real& x_max)
{
  Real integrate_val = 0.0;
  if( fabs(x_min - x_max) < fabs(x_max*1.0E-5) )
  {
    return integrate_val;
  }
  else if( x_min > x_max - min_value )
  {
    string class_name = "IntegrateTabData";
    string func_name  = "integrate_data";
    ostringstream oss01, oss02;
    oss01 << setw(10) << std::showpoint << std::scientific << x_min;
    oss02 << setw(10) << std::showpoint << std::scientific << x_max;
    string str_data01 = "Start point of integration (x_min) : " + oss01.str();
    string str_data02 = "End point of integration   (x_max) : " + oss02.str();
    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("Start point of integration is larger than end point.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  if( x_m > x_p - min_value )
  {
    string class_name = "IntegrateTabData";
    string func_name  = "integrate_data";
    ostringstream oss01, oss02, oss03, oss04;
    oss01 << setw(10) << x_m;
    oss02 << setw(10) << x_p;
    oss03 << setw(10) << y_m;
    oss04 << setw(10) << y_p;
    string str_data01 = "x_m : " + oss01.str();
    string str_data02 = "x_p : " + oss02.str();
    string str_data03 = "y_m : " + oss03.str();
    string str_data04 = "y_p : " + oss04.str();
    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back("x_m is larger than or equal to x_p.");
    err_com.push_back("Please check the x_m, x_p, y_m and y_p");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  switch( int_val )
  {
    case int_const:
      integrate_val = integrate_data_const(x_m, y_m, x_p, y_p, x_min, x_max);
      break;
    case int_lin_lin:
      integrate_val = integrate_data_lin_lin(x_m, y_m, x_p, y_p, x_min, x_max);
      break;
    case int_log_lin:
      integrate_val = integrate_data_log_lin(x_m, y_m, x_p, y_p, x_min, x_max);
      break;
    case int_lin_log:
      integrate_val = integrate_data_lin_log(x_m, y_m, x_p, y_p, x_min, x_max);
      break;
    case int_log_log:
      integrate_val = integrate_data_log_log(x_m, y_m, x_p, y_p, x_min, x_max);
      break;
    default:
      string class_name = "IntegrateTabData";
      string func_name  = "integrate_data(Real& x_m, Real& y_m, Real& x_p, Real& y_p, Integer int_val)";

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

  return integrate_val;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Real IntegrateTabData::integrate_data_const(Real& x_m, Real& y_m, Real& x_p, Real& y_p,
                                            Real& x_min, Real& x_max)
{
  //y = a
  Real   integrate_val = y_m * (x_max - x_min);
  return integrate_val;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Real IntegrateTabData::integrate_data_lin_lin(Real& x_m, Real& y_m, Real& x_p, Real& y_p,
                                              Real& x_min, Real& x_max)
{
  //y = a*x + b
  Real coef_a = (y_p - y_m) / (x_p - x_m);
  Real coef_b = y_m - coef_a*x_m;

  Real   integrate_val = (x_max - x_min) * (coef_b + 0.5*coef_a*(x_max + x_min));
  return integrate_val;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Real IntegrateTabData::integrate_data_log_lin(Real& x_m, Real& y_m, Real& x_p, Real& y_p,
                                              Real& x_min, Real& x_max)
{
  //y = a*ln(x) + b
  Real   integrate_val = 0.0;

  if( x_m <= min_value || x_p <= min_value )
  {
    integrate_val = integrate_data_lin_lin(x_m, y_m, x_p, y_p, x_min, x_max);
  }
  else
  {
    Real coef_a = (y_p - y_m) / (log(x_p/x_m));
    Real coef_z = (x_max - x_min) / x_min;
    if( fabs(coef_z) <= 0.1 )
    {
      integrate_val = 0.5 * (x_max - x_min)
                          * ( y_m + coef_a*log(x_min/x_m)
                                  + coef_a*x_min*coef_z*coef_z*(1.0+coef_z)
                                  * (-1.0/3.0 + coef_z*(1.0/6.0 - coef_z*0.1)) );
    }
    else
    {
      integrate_val = (x_max - x_min)*( y_m + coef_a*log(x_min/x_m) 
                                            + coef_a*x_min*(1.0 + (x_max/x_min))
                                            * (log(x_max/x_min)) - 1.0 );
    }
  }

  return integrate_val;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Real IntegrateTabData::integrate_data_lin_log(Real& x_m, Real& y_m, Real& x_p, Real& y_p,
                                              Real& x_min, Real& x_max)
{
  //ln(y) = a*x + b
  Real integrate_val = 0.0;

  if( y_m < min_value || y_p < min_value )
  {
    integrate_val = integrate_data_lin_lin(x_m, y_m, x_p, y_p, x_min, x_max);
  }
  else
  {
    Real coef_a = (log(y_p/y_m)) / (x_p - x_m);
    Real coef_b = log(y_m) - coef_a*x_m;
    Real coef_z = (x_max - x_min)*coef_a;
    if( fabs(coef_z) <= 0.1 )
    {
      integrate_val = exp(coef_b + coef_a*x_min) * (x_max - x_min)*(1.0 + coef_z*(0.5 + coef_z/6.0));
    }
    else
    {
      integrate_val = exp(coef_b + coef_a*x_min) * (exp(coef_z) - 1.0) / coef_a;
    }
  }

  return integrate_val;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Real IntegrateTabData::integrate_data_log_log(Real& x_m, Real& y_m, Real& x_p, Real& y_p,
                                              Real& x_min, Real& x_max)
{
  Real integrate_val = 0.0;

  if( x_m <= min_value || x_p <= min_value )
  {
    integrate_val = integrate_data_lin_log(x_m, y_m, x_p, y_p, x_min, x_max);
  }
  else if( y_m <= min_value || y_p <= min_value )
  {
    integrate_val = integrate_data_log_lin(x_m, y_m, x_p, y_p, x_min, x_max);
  }
  else
  {
    Real coef_a = (log(y_p/y_m)) / (log(x_p/x_m));
    Real coef_z = (coef_a + 1.0) * log(x_max/x_min);
    if( fabs(coef_z) <= 0.1 )
    {
      integrate_val = y_m*x_min * (pow((x_min/x_m),coef_a))
                                * log(x_max/x_min) * (1.0 + coef_z*(0.5 + coef_z/6.0));
    }
    else
    {
      integrate_val = y_m*x_min * (pow((x_min/x_m),coef_a))
                                * (( pow((x_min/x_m),(coef_a + 1.0)) ) - 1.0) / (coef_a + 1.0);
    }
  }

  return integrate_val;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void IntegrateTabData::integrate_for_ace_data
                         (string& class_name, string& func_name,
                          vector<Real>& x_vec, vector<Real>& y_vec, vector<Real>& y_integ, Integer int_val)
{
  Real sum = 0.0;
  integrate_for_ace_data(class_name, func_name, x_vec, y_vec, y_integ, int_val, sum);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void IntegrateTabData::integrate_for_ace_data
                         (string& class_name, string& func_name, vector<Real>& x_vec, vector<Real>& y_vec,
                          vector<Real>& y_integ, Integer int_val, Real& sum)
{
  integrate_for_ace_data_no_normalize(class_name, func_name, x_vec, y_vec, y_integ, int_val);

  int i_max = static_cast<int>(y_integ.size());
       sum  =  y_integ[i_max-1];

  if( fabs(sum) > min_value )
  {
    Real sum_inv = 1.0 / sum;
    for(int i=0; i<i_max; i++)
    {
      y_vec[i]   *= sum_inv;
      y_integ[i] *= sum_inv;
    }
  }
  else
  {
    sum = 1.0;
  }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////

void IntegrateTabData::integrate_for_ace_data_no_normalize
                         (string& class_name, string& func_name, vector<Real>& x_vec, vector<Real>& y_vec,
                          vector<Real>& y_integ, Integer int_val)
{
  if( int_val == int_const )
  {
    integrate_for_ace_data_const(x_vec, y_vec, y_integ);
  }
  else if( int_val == int_lin_lin )
  {
    integrate_for_ace_data_lin_lin(x_vec, y_vec, y_integ);
  }
  else
  {
    ostringstream oss01;
    oss01 << int_val;
    string str_data01 = "Interpolation type : " + oss01.str();
    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("This interpolation type is not available.");
    err_com.push_back("Available interpolation type is constant and linear-linear.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void IntegrateTabData::integrate_for_ace_data_const
                         (vector<Real>& x_vec, vector<Real>& y_vec, vector<Real>& y_integ)
{
  int i_max = static_cast<int>(x_vec.size());
  y_integ.resize(i_max);
  y_integ[0] = 0.0;
  for(int i=1; i<i_max; i++)
  {
    y_integ[i] = y_integ[i-1] + y_vec[i-1] * (x_vec[i] - x_vec[i-1]);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void IntegrateTabData::integrate_for_ace_data_lin_lin
                         (vector<Real>& x_vec, vector<Real>& y_vec, vector<Real>& y_integ)
{
  int i_max = static_cast<int>(x_vec.size());
  y_integ.resize(i_max);
  y_integ[0] = 0.0;
  for(int i=1; i<i_max; i++)
  {
    y_integ[i] = y_integ[i-1] + 0.5 * (y_vec[i] + y_vec[i-1]) * (x_vec[i] - x_vec[i-1]);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void IntegrateTabData::modify_interpolation(string& class_name, string& func_name,
                                            vector<Integer>& range_data, vector<Integer>& int_data)
{
//!!! Japanese comment !!!//
//int, rangeの値チェック(同じ内挿タイプが入っているかどうかを確認)。
//ここの関数はint, rangeの編集をしようとしている模様。
//とりあえず今のところ不要らしい。

  Integer int_chk_flg = check_interpolation(class_name, func_name, range_data, int_data, int_lin_lin);

  if( int_chk_flg == -1 )
  {
    return;
  }

  if( int_chk_flg == 0 )
  {
    return;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Integer IntegrateTabData::check_interpolation
                            (string& class_name, string& func_name, Integer reaction_type,
                             vector<int>& pos, vector<Integer>& range_data, vector<Integer>& int_data)
{
  Integer chk_val = check_interpolation(class_name, func_name, range_data, int_data);

  Integer int_val     = -1;
  Integer chk_val_mod =  1;
  int i_max = static_cast<int>(int_data.size());
  if( i_max > 0 )
  {
    int_val = int_data[0];

    if( chk_val != 0 && generate_mode_flg == generate_default_mode )
    {
      if( range_data[0] <= 2 && i_max >= 2 )
      {
        chk_val_mod = 0;
        int_val     = int_data[1];
        for(int i=2; i<i_max-1; i++)
        {
          if( int_data[1] != int_data[i] )
          {
            chk_val_mod = 1;
            break;
          }
        }
      }
    }
  }


  if( chk_val != 0 )
  {
    vector<string> err_com;

    ostringstream oss01;
    oss01 << reaction_type;
    string str_data01 = "Reaction type : " + oss01.str();
    err_com.push_back(str_data01);

     i_max = static_cast<int>(pos.size());
    if( i_max > 0 )
    { 
      string str_data02 = "Position      : ";
      for(int i=0; i<i_max; i++)
      {
        ostringstream oss02;
        oss02 << pos[i] + 1;
        str_data02 = str_data02 + oss02.str();
        if( i < i_max - 1 )
        {
          str_data02 = str_data02 + ", ";
        }
      }
      err_com.push_back(str_data02);
    }

    if( chk_val > 0 )
    {
      i_max = static_cast<int>(int_data.size());
      for(int i=0; i<i_max; i++)
      {
        ostringstream oss11, oss12, oss13;
        oss11 << i+1;
        oss12 << range_data[i];
        oss13 << int_data[i];
        string str_data11 = "Interpolation data @" + oss11.str() + " : " + oss12.str() + ", " + oss13.str();
        err_com.push_back(str_data11);
      }
      err_com.push_back("Interpolation value is not identical.");
      err_com.push_back("This program can not treat not identical interpolation type.");

      if( chk_val_mod != 0 )
      {
        err_com.push_back("Please check the nuclear data or program.");
      }
    }
    else if( chk_val == -1 )
    {
      err_com.push_back("Interpolation data number is 0.");
    }
    else if( chk_val == -2 )
    {
      err_com.push_back("Range data number is 0.");
    }

    if( chk_val > 0 )
    {
      if( generate_mode_flg == generate_default_mode )
      {
        if( chk_val_mod != 0 )
        {
          err_obj.output_runtime_error(class_name, func_name, err_com);
        }
        else //if( chk_val_mod == 0 )
        {
          err_com.push_back("Since the initial interpolation type is only available for x(1),");
          err_com.push_back("this interpolation type is dummy data.");
          err_com.push_back("The second interpolation type can be used for all regions.");
          err_com.push_back("So, the second interpolation type is considered as the");
          err_com.push_back("interpolation type in this program.");
          err_obj.output_caution(class_name, func_name, err_com);
        }
      }
      else //if( generate_mode_flg == generate_njoy_mode )
      {
        err_obj.output_caution(class_name, func_name, err_com);
      }
    }
    else if( chk_val < 0 )
    {
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }

  return int_val;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Integer IntegrateTabData::check_interpolation(string& class_name, string& func_name,
                                              vector<Integer>& range_data, vector<Integer>& int_data)
{
  if( static_cast<int>(int_data.size()) == 0 )
  {
    return -1;
  }

  Integer int_val     = int_data[0];
  Integer int_chk_flg = check_interpolation(class_name, func_name, range_data, int_data, int_val);

  return int_chk_flg;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Integer IntegrateTabData::check_interpolation(string& class_name, string& func_name,
                                              vector<Integer>& range_data, vector<Integer>& int_data,
                                              Integer int_val)
{
  if( static_cast<int>(range_data.size()) == 0 )
  {
    return -2;
  }

  if( static_cast<int>(range_data.size()) != static_cast<int>(int_data.size()) )
  {
    ostringstream oss01, oss02;
    oss01 << static_cast<int>(range_data.size());
    oss02 << static_cast<int>(int_data.size());
    string str_data01 = "Number of data in range_data : " + oss01.str();
    string str_data02 = "Number of data in int_data   : " + oss02.str();
    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("Number of data in range_data is not identical to that in int_data.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  int i_max = static_cast<int>(int_data.size());
  for(int i=0; i<i_max; i++)
  {
    if( int_data[i] != int_val )
    {
      return 1;
    }
  }

  return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

vector<Real> IntegrateTabData::integrate_using_specified_grid_with_lin_lin
                                 (vector<Real>  grid_data, vector<Real>& x_data, vector<Real>& y_data)
{
  int i_max = static_cast<int>(grid_data.size());
  int j_max = static_cast<int>(x_data.size());

  if( i_max <= 1 || j_max <= 1 )
  {
    string class_name = "IntegrateTabData";
    string func_name  = "integrate_using_specified_grid";
    ostringstream oss01, oss02;
    oss01 << i_max;
    oss02 << j_max;
    string str_data01 = "Number of integrated grid data : " + oss01.str();
    string str_data02 = "Number of x_data               : " + oss02.str();
    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("Number of integrated grid data or that of x_data must be larger than 1.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  int j = 1;
  Real x_min = x_data[0];
  Real x_max = x_data[j_max-1];
  Real res_x = x_min;
  Real res_y = y_data[0];

  vector<Real> integ_data;
  integ_data.resize(i_max-1);
  for(int i=0; i<i_max-1; i++)
  {
    integ_data[i] = 0.0;
  }

  for(int i=0; i<i_max-1; i++)
  {
    if( grid_data[i+1] - x_min < min_ene_dif )
    {
      continue;
    } 
    else if( j == j_max - 1 && grid_data[i+1] - x_max > min_ene_dif )
    {
      integ_data[i] += 0.5 * (x_max - res_x) * (y_data[j_max-1] + res_y);
      break;
    }

    while( j < j_max - 1 && grid_data[i+1] > x_data[j] )
    {
      integ_data[i] += 0.5 * (x_data[j] - res_x) * (y_data[j] + res_y);

      res_x = x_data[j];
      res_y = y_data[j];
      j++;

      if( j >= j_max )
      {
        break;
      }
    }

    if( grid_data[i+1] < x_data[j] * (1.0 + min_ene_dif) )
    {
      Real y_val = 0.0;
      ti_obj.interpolation_linear_linear(grid_data[i+1], y_val, x_data[j-1], y_data[j-1], x_data[j], y_data[j]);
      integ_data[i] += 0.5 * (grid_data[i+1] - res_x) * (y_val + res_y);

      res_x = grid_data[i+1];
      res_y = y_val;
    }
  }

  return integ_data;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void IntegrateTabData::set_generate_mode_flg(int int_val)
{
  generate_mode_flg = int_val;
}

int IntegrateTabData::get_generate_mode_flg()
{
  return generate_mode_flg;
}

