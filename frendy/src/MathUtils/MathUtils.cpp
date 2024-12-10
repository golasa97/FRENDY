#include "MathUtils/MathUtils.hpp"

using namespace frendy;

//constructor
MathUtils::MathUtils(void)
{
  lagrange_interpolation_flg = sort_data;
  rpi                        = sqrt(M_PI);
  clear();
}

//destructor
MathUtils::~MathUtils(void)
{
  rpi = 0.0;
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MathUtils::clear()
{
  coef_dop_func  = 0.0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Real8 MathUtils::calc_erf(Real8 x)
{
  return erf(x);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Real8 MathUtils::calc_erfc(Real8 x)
{
  return erfc(x);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void MathUtils::calc_cerfc(Real8 xi, Real8 yi, Real8& w_x, Real8& w_y)
{
  cef_obj.cerfc(xi, yi, w_x, w_y);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MathUtils::calc_doppler_broadening_function(Real8 x, Real8 h, Real8& phi, Real8& chi)
{
  set_h_val(h);
  calc_doppler_broadening_function(x, phi, chi);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MathUtils::calc_doppler_broadening_function(Real8 x, Real8& phi, Real8& chi)
{
  cef_obj.cerfc(x, phi, chi);
  phi *= coef_dop_func;
  chi *= coef_dop_func;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MathUtils::set_h_val(Real8 real_val)
{
  coef_dop_func = rpi*real_val;

  cef_obj.set_h_val(real_val);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MathUtils::set_gamma_width(Real8 gam_r, Real8 gam_d)
{
  Real8 h = 0.5 * (gam_r / gam_d);
  set_h_val(h);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Real8 MathUtils::get_h_val()
{
  return cef_obj.get_h_val();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void MathUtils::calc_inv_comp_matrix_3x3(Real8 real_vec[3][3], Real8 imag_vec[3][3])
{
  complex<Real8> comp_vec[3][3];
  complex<Real8> det_vec, ele_data;
  complex<Real8> comp_val_11_22, comp_val_21_02, comp_val_01_12, 
                 comp_val_21_12, comp_val_11_02, comp_val_01_22;

  det_vec = complex<Real8>(0.0, 0.0);
  for(int i=0; i<3; i++)
  {
    for(int j=0; j<3; j++)
    {
      comp_vec[i][j] = complex<Real8>(real_vec[i][j], imag_vec[i][j]);
    }
  }

  comp_val_11_22 = comp_vec[1][1]*comp_vec[2][2];
  comp_val_21_02 = comp_vec[2][1]*comp_vec[0][2];
  comp_val_01_12 = comp_vec[0][1]*comp_vec[1][2];
  comp_val_21_12 = comp_vec[2][1]*comp_vec[1][2];
  comp_val_11_02 = comp_vec[1][1]*comp_vec[0][2];
  comp_val_01_22 = comp_vec[0][1]*comp_vec[2][2];
  
  det_vec = comp_vec[0][0]*comp_val_11_22
          + comp_vec[1][0]*comp_val_21_02
          + comp_vec[2][0]*comp_val_01_12
          - comp_vec[0][0]*comp_val_21_12
          - comp_vec[2][0]*comp_val_11_02
          - comp_vec[1][0]*comp_val_01_22;
  det_vec = 1.0/det_vec;
  
  if( det_vec == complex<Real8>(0.0, 0.0) )
  {
    string class_name = "MathUtils";
    string func_name  = "calc_inv_comp_matrix_3x3(Real8 real_vec[3][3], Real8 imag_vec[3][3])";

    ostringstream oss11, oss12, oss13, oss21, oss22, oss23, oss31, oss32, oss33;
    oss11 << comp_vec[0][0];
    oss12 << comp_vec[0][1];
    oss13 << comp_vec[0][2];
    oss21 << comp_vec[1][0];
    oss22 << comp_vec[1][1];
    oss23 << comp_vec[1][2];
    oss31 << comp_vec[2][0];
    oss32 << comp_vec[2][1];
    oss33 << comp_vec[2][2];
    string str_data11 = "Compex value at (1, 1) : " + oss11.str();
    string str_data12 = "Compex value at (1, 2) : " + oss12.str();
    string str_data13 = "Compex value at (1, 3) : " + oss13.str();
    string str_data21 = "Compex value at (2, 1) : " + oss21.str();
    string str_data22 = "Compex value at (2, 2) : " + oss22.str();
    string str_data23 = "Compex value at (2, 3) : " + oss23.str();
    string str_data31 = "Compex value at (3, 1) : " + oss31.str();
    string str_data32 = "Compex value at (3, 2) : " + oss32.str();
    string str_data33 = "Compex value at (3, 3) : " + oss33.str();

    vector<string> err_com;
    err_com.push_back(str_data11);
    err_com.push_back(str_data12);
    err_com.push_back(str_data13);
    err_com.push_back(str_data21);
    err_com.push_back(str_data22);
    err_com.push_back(str_data23);
    err_com.push_back(str_data31);
    err_com.push_back(str_data32);
    err_com.push_back(str_data33);
    err_com.push_back("Determinant is 0.0.");
    err_com.push_back("The inverse complex matrix can not calculate.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
  
  //i=0, j=0
  ele_data = det_vec * (comp_val_11_22 - comp_val_21_12);
  real_vec[0][0] = ele_data.real();
  imag_vec[0][0] = ele_data.imag();
  
  //i=0, j=1
  ele_data = det_vec * (comp_val_21_02 - comp_val_01_22);
  real_vec[0][1] = ele_data.real();
  imag_vec[0][1] = ele_data.imag();
  
  //i=0, j=2
  ele_data = det_vec * (comp_val_01_12 - comp_val_11_02);
  real_vec[0][2] = ele_data.real();
  imag_vec[0][2] = ele_data.imag();
  
  
  //i=1, j=0
  ele_data = det_vec * (comp_vec[1][2]*comp_vec[2][0] - comp_vec[1][0]*comp_vec[2][2]);
  real_vec[1][0] = ele_data.real();
  imag_vec[1][0] = ele_data.imag();
  
  //i=1, j=1
  ele_data = det_vec * (comp_vec[0][0]*comp_vec[2][2] - comp_vec[0][2]*comp_vec[2][0]);
  real_vec[1][1] = ele_data.real();
  imag_vec[1][1] = ele_data.imag();
  
  //i=1, j=2
  ele_data = det_vec * (comp_vec[0][2]*comp_vec[1][0] - comp_vec[0][0]*comp_vec[1][2]);
  real_vec[1][2] = ele_data.real();
  imag_vec[1][2] = ele_data.imag();
  
  
  //i=2, j=0
  ele_data = det_vec * (comp_vec[1][0]*comp_vec[2][1] - comp_vec[1][1]*comp_vec[2][0]);
  real_vec[2][0] = ele_data.real();
  imag_vec[2][0] = ele_data.imag();
  
  //i=2, j=1
  ele_data = det_vec * (comp_vec[0][1]*comp_vec[2][0] - comp_vec[0][0]*comp_vec[2][1]);
  real_vec[2][1] = ele_data.real();
  imag_vec[2][1] = ele_data.imag();
  
  //i=2, j=2
  ele_data = det_vec * (comp_vec[0][0]*comp_vec[1][1] - comp_vec[0][1]*comp_vec[1][0]);
  real_vec[2][2] = ele_data.real();
  imag_vec[2][2] = ele_data.imag();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<Real8> MathUtils::legendre_expansion(Real8& x, Integer order)
{
  vector<Real8> polynomial;

  int i_max = static_cast<int>(order);
  polynomial.resize(i_max);

  if( i_max > 0 )
  {
    polynomial[0] = 1;
  }
  if( i_max > 1 )
  {
    polynomial[1] = x;
  }
  
  Real8 i_real = 2.0;
  for(int i=2; i<i_max; i++)
  {
    polynomial[i] = ( (2*i_real-1.0)*x*polynomial[i-1] - (i_real-1.0)*polynomial[i-2] ) / i_real;
    i_real += 1.0;
  }

  return polynomial;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Real8 MathUtils::parabolic_interpolation(Real8& x_val, 
                                         Real8& x1, Real8& y1, Real8& x2, Real8& y2, Real8& x3, Real8& y3)
{
  Real8 y_val = 0.0;

  if( fabs(x_val - x1) < min_value )
  {
    return y1;
  }
  else if( fabs(x_val - x2) < min_value )
  {
    return y2;
  }
  else if( fabs(x_val - x3) < min_value )
  {
    return y3;
  }

  if( fabs(x3 - x1) < min_value || fabs(x2 - x1) < min_value || fabs(x3 - x2) < min_value)
  {
    string class_name = "MathUtils";
    string func_name  = "parabolic_interpolation(x_val, x1, y1, x2, y2, x3, y3)";

    ostringstream oss01, oss02, oss03;
    oss01 << x1;
    oss02 << x2;
    oss03 << x3;
    string str_data01 = "x1 : " + oss01.str();
    string str_data02 = "x2 : " + oss02.str();
    string str_data03 = "x3 : " + oss03.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);

    if( fabs(x3 - x1) < min_value )
    {
      err_com.push_back("x3 is identical to x1 is.");
    }
    if( fabs(x2 - x1) < min_value )
    {
      err_com.push_back("x2 is identical to x1.");
    }
    if( fabs(x3 - x2) < min_value )
    {
      err_com.push_back("x3 is identical to x2.");
    }
    err_com.push_back("Please check x1, x2 and x3.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  Real8 coef1 = (y3 - y1) / ( (x3 - x1)*(x3 - x2) );
  Real8 coef2 = (y2 - y1) / ( (x2 - x1)*(x3 - x2) );

  Real8 a = coef1 - coef2;
  Real8 b = coef2*(x3 + x1) - coef1*(x2 + x1);

  y_val = a*(x_val*x_val - x1*x1) + b*(x_val - x1) + y1;

  //NJOY99 version @ terpq in thermr.f
  //b = (y2-y1)*(x3-x1)/((x2-x1)*(x3-x2)) - (y3-y1)*(x2-x1)/((x3-x1)*(x3-x2));
  //a = (y3-y1)/((x3-x1)*(x3-x2)) - (y2-y1)/((x2-x1)*(x3-x2));
  //y_val = y1+b*(x_val-x1)+a*(x_val-x1)*(x_val-x1);

  return y_val;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Real8 MathUtils::quadratic_interpolation(Real8& x_val, 
                                         Real8& x1, Real8& y1, Real8& x2, Real8& y2, Real8& x3, Real8& y3)
{
  Real8 y_val = parabolic_interpolation(x_val, x1, y1, x2, y2, x3, y3);

  return y_val;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MathUtils::check_interpolation_data(vector<Real8>& x_vec, vector<Real8>& y_vec,
                                         vector<Real8>& x_vec_mod, vector<Real8>& y_vec_mod)
{
  int i_max = static_cast<int>(x_vec.size());
  vector<Real8> x_vec_tmp = x_vec;
  vector<Real8> y_vec_tmp = y_vec;
  simultaneous_vector_sort(x_vec_tmp, y_vec_tmp);

  x_vec_mod.clear();
  y_vec_mod.clear();
  x_vec_mod.push_back(x_vec[0]);
  y_vec_mod.push_back(y_vec[0]);
  for(int i=1; i<i_max; i++)
  {
    if( fabs(x_vec_tmp[i] - x_vec_tmp[i-1]) > min_ene_dif )
    {
      x_vec_mod.push_back(x_vec_tmp[i]);
      y_vec_mod.push_back(y_vec_tmp[i]);
    }
  }
  x_vec_tmp.clear();
  y_vec_tmp.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MathUtils::search_appropriate_interpolation_data(Real8& x_val, Integer& order,
                                                      vector<Real8>& x_vec, vector<Real8>& y_vec,
                                                      vector<Real8>& x_vec_use, vector<Real8>& y_vec_use)
{
  int i_max     = static_cast<int>(x_vec.size());
  int order_int = static_cast<int>(order);
  if( i_max < order_int )
  {
    order_int = i_max;
  }

  x_vec_use.clear();
  y_vec_use.clear();
  if( i_max == order_int )
  {
    x_vec_use = x_vec;
    y_vec_use = y_vec;
  }
  else
  {
    int x_low  = 0;
    int x_high = i_max - 1;
    int x_pos  = -1;
    if( x_val < x_vec[x_low] )
    {
      x_high = x_low + order_int - 1;
    }
    else if( x_val > x_vec[x_high] )
    {
      x_low = x_high - order_int + 1;
    }
    else
    {
      x_pos = -1;
      Real8 x_check = x_val - min_value;
      for(int i=0; i<i_max; i++)
      {
        if( x_vec[i] > x_check )
        {
          x_pos = i;
          break;
        }
      }
      if( x_pos < 0 )
      {
        x_pos = i_max - 1;
      }

      if( order_int%2 == 0 )
      {
        x_low  = x_pos - order_int/2;
      }
      else
      {
        x_low  = x_pos - (order_int-1)/2;
      }
      x_high = x_low + order_int - 1;
      if( x_low < 0 )
      {
        x_high = x_high - x_low;
        x_low  = 0;
      }
      else if( x_high > i_max - 1 )
      { 
        x_low  = i_max - order;
        x_high = i_max - 1;
      }
    }

    x_pos = 0;
    x_vec_use.resize(order_int);
    y_vec_use.resize(order_int);
    for(int i=x_low; i<=x_high; i++)
    {
      x_vec_use[x_pos] = x_vec[i];
      y_vec_use[x_pos] = y_vec[i];
      x_pos++;
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Real8 MathUtils::lagrange_interpolation(Real8& x_val, vector<Real8>& x_vec, vector<Real8>& y_vec)
{
  vector<Real8> x_vec_mod, y_vec_mod;
  if( lagrange_interpolation_flg == sort_data )
  {
    check_interpolation_data(x_vec, y_vec, x_vec_mod, y_vec_mod);
  }
  else
  {
    int ele_no = static_cast<int>(x_vec.size());
    x_vec_mod.resize(ele_no);
    y_vec_mod.resize(ele_no);
    for(int i=0; i<ele_no; i++)
    {
      x_vec_mod[i] = x_vec[i];
      y_vec_mod[i] = y_vec[i];
    }
  }


  int   i_max    = static_cast<int>(x_vec_mod.size());
  Real8 molecule_l = 1.0;
  Real8 min_dif    = x_val * min_ene_dif;
  for(int i=0; i<i_max; i++)
  {
    molecule_l *= (x_val - x_vec_mod[i]);
    if( fabs(x_val - x_vec_mod[i]) < min_dif )
    {
      return y_vec_mod[i];
    }
  }

  Real y_val = 0.0;
  for(int i=0; i<i_max; i++)
  {
    Real8 denominator_l = 1.0;
    for(int j=0; j<i_max; j++)
    {
      if( j != i )
      {
        denominator_l *= (x_vec_mod[i] - x_vec_mod[j]);
      }
    }
    y_val += y_vec_mod[i] * molecule_l / (denominator_l * (x_val - x_vec_mod[i]));
  }
  x_vec_mod.clear();
  y_vec_mod.clear();

  return y_val;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Real8 MathUtils::lagrange_interpolation(Real8& x_val, Integer& order, vector<Real8>& x_vec, vector<Real8>& y_vec)
{
  vector<Real8> x_vec_mod, y_vec_mod, x_vec_use, y_vec_use;
  check_interpolation_data(x_vec, y_vec, x_vec_mod, y_vec_mod);
  search_appropriate_interpolation_data(x_val, order, x_vec_mod, y_vec_mod, x_vec_use, y_vec_use);

  lagrange_interpolation_flg = no_sort_data;

  Real8 y_val = lagrange_interpolation(x_val, x_vec_use, y_vec_use);

  lagrange_interpolation_flg = sort_data;
  x_vec_mod.clear();
  y_vec_mod.clear();
  x_vec_use.clear();
  y_vec_use.clear();

  return y_val;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MathUtils::simultaneous_vector_sort(vector<Real8>& x_vec, vector<Real8>& y_vec)
{
  vector<pair<Real8,Real8> > data;

  int i_max = static_cast<int>(x_vec.size());
  if( i_max != static_cast<int>(y_vec.size()) )
  {
    string class_name = "MathUtils";
    string func_name  = "simultaneous_vector_sort(vector<Real8>& x_vec, vector<Real8>& y_vec)";

    ostringstream oss01, oss02;
    oss01 << i_max;
    oss02 << static_cast<int>(y_vec.size());
    string str_data01 = "Size of x_vec : " + oss01.str();
    string str_data02 = "Size of y_vec : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("Size of x is not identical to that of y.");
    err_com.push_back("Please check x_vec and y_vec");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  data.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    //data[i] = pair<Real8,Real8>(x_vec[i], y_vec[i]);
    data[i].first  = x_vec[i];
    data[i].second = y_vec[i];
  }
  sort(data.begin(), data.end());

  for(int i=0; i<i_max; i++)
  {
    x_vec[i] = data[i].first;
    y_vec[i] = data[i].second;
  }
  data.clear();
}
