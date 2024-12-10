#include "MathUtils/ComplexErrorFunctionCalculator.hpp"

using namespace frendy;

//Initialize static const value
const Real8 ComplexErrorFunctionCalculator::factor   = 1.12837916709551257388e+0;
const Real8 ComplexErrorFunctionCalculator::max_real = 0.5e+154;
const Real8 ComplexErrorFunctionCalculator::max_exp  = 708.503061461606e+0;
const Real8 ComplexErrorFunctionCalculator::max_goni = 3.53711887601422e+15;
const Real8 ComplexErrorFunctionCalculator::qrho_chk = 0.085264e+0;

//constructor
ComplexErrorFunctionCalculator::ComplexErrorFunctionCalculator(void)
{
  clear();
}

//destructor
ComplexErrorFunctionCalculator::~ComplexErrorFunctionCalculator(void)
{
  clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ComplexErrorFunctionCalculator::clear()
{
  h_val = 0.0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ComplexErrorFunctionCalculator::cerfc(Real8 xi, Real8 yi, Real8& w_x, Real8& w_y)
{
  Real8 x_abs = fabs(xi);
  Real8 y_abs = fabs(yi);
  Real8 x     = x_abs/6.3;
  Real8 y     = y_abs/4.4;

  if( ( x_abs > max_real ) || ( y_abs > max_real ) )
  {
    string class_name = "ComplexErrorFunctionCalculator";
    string func_name  = "cerfc(Real8 xi, Real8 yi, Real8& w_x, Real8& w_y)";

    ostringstream oss01, oss02, oss03;
    oss01 << x_abs;
    oss02 << y_abs;
    oss03 << max_real;
    string str_data01 = "The real part of the complex value      : " + oss01.str();
    string str_data02 = "The imaginary part of the complex value : " + oss02.str();
    string str_data03 = "Maximum value                           : " + oss03.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    if( x_abs > max_real )
    {
      err_com.push_back("The real part of the complex value is so mach large.");
    }
    if( y_abs > max_real )
    {
      err_com.push_back("The imaginary part of the complex value is so mach large.");
    }
    err_com.push_back("Please check the complex value.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  Real8 qrho    = x*x + y*y;
  Real8 x_quad  = x_abs*x_abs - y_abs*y_abs;
  Real8 y_quad  = 2.0*x_abs*y_abs;

  Real8 u1, v1, u2, v2;
  u2 = 0.0;
  v2 = 0.0;

  int   qrho_flg = 0;
  if( qrho < qrho_chk )
  {
    qrho_flg = 1;

    qrho = (1.0 - 0.85*y)*sqrt(qrho);
    Real8 n_real = round(6.0+72.0*qrho);
    Real8 j_real = 2.0*n_real + 1.0;

    Real8 x_sum = 1.0 / j_real;
    Real8 y_sum = 0.0;

    Real8 x_aux;
    Real8 i_real = n_real;
    int   n_int  = static_cast<int>(round(n_real));
    for(int i=n_int; i>0; i--)
    {
      Real8 i_inv = 1.0 / i_real;

      j_real -= 2.0;
      x_aux = (x_sum*x_quad - y_sum*y_quad)*i_inv;
      y_sum = (x_sum*y_quad + y_sum*x_quad)*i_inv;
      x_sum = x_aux + 1.0 / j_real;

      i_real -= 1.0;
    }

    Real8 d_aux;
    u1    = -1.0*factor*(x_sum*y_abs + y_sum*x_abs) + 1.0;
    v1    =      factor*(x_sum*x_abs - y_sum*y_abs);
    d_aux = exp(-1.0*x_quad);
    u2    =      d_aux*cos(y_quad);
    v2    = -1.0*d_aux*sin(y_quad);

    w_x = u1*u2 - v1*v2;
    w_y = u1*v2 + v1*u2;
  }
  else
  {
    Real8 h, h2, q_lambda, kapn_real, nu_real;
    int   h_flg = 0;
    if( qrho > 1.0 )
    {
      qrho      = sqrt(qrho);
      h         = 0.0;
      h2        = 0.0;
      kapn_real = 0.0;
      nu_real   = 3.0 + 1442.0/(26.0*qrho+77.0);
    }
    else
    {
      qrho      = (1.0-y)*sqrt(1.0-qrho);
      h         = 1.88*qrho;
      h2        = 2.00*h;
      kapn_real = round( 7.0 + 34.0*qrho);
      nu_real   = round(16.0 + 26.0*qrho);

      if( fabs(h) > min_value )
      {
        if( h < 0.0 )
        {
          h_flg = -1;
        }
        else
        {
          h_flg = 1;
        }
      }
    }

    int nu_int   = static_cast<int>(round(nu_real));
    int kapn_int = static_cast<int>(round(kapn_real));

    q_lambda = 0.0;
    if( h_flg > 0 )
    {
      q_lambda = pow(h2, kapn_real);
    }

    Real8 rx  = 0.0;
    Real8 ry  = 0.0;
    Real8 sx  = 0.0;
    Real8 sy  = 0.0;
    Real8 np1 = static_cast<Real8>(nu_int + 1);
    for(int n=nu_int; n>=0; n--)
    {
      Real8 tx  = y_abs + h + np1*rx;
      Real8 ty  = x_abs -     np1*ry;
      Real8 c   = 0.5/(tx*tx + ty*ty);
            rx  = c*tx;
            ry  = c*ty;

      if( h_flg > 0 && n <= kapn_int )
      {
        tx = q_lambda + sx;
        sx = rx*tx - ry*sy;
        sy = ry*tx + rx*sy;
        q_lambda = q_lambda/h2;
      }

      np1 -= 1.0;
    }

    if( h_flg == 0 )
    {
      w_x = factor*rx;
      w_y = factor*ry;
    }
    else
    {
      w_x = factor*sx;
      w_y = factor*sy;
    }

    if( y_abs == 0.0 )
    {
      w_x = exp(-1.0*x_abs*x_abs);
    }
  }

  if( yi < 0.0 )
  {
    if( qrho_flg > 0 )
    {
      u2 = 2.0*u2;
      v2 = 2.0*v2;
    }
    else
    {
      x_quad = -1.0*x_quad;

      if( y_quad > max_goni || x_quad > max_exp )
      {
        string class_name = "ComplexErrorFunctionCalculator";
        string func_name  = "cerfc(Real8 xi, Real8 yi, Real8& w_x, Real8& w_y)";

        ostringstream oss01, oss02, oss03, oss04;
        oss01 << x_quad;
        oss02 << max_exp;
        oss03 << y_quad;
        oss04 << max_goni;
        string str_data01 = "x_quad   : " + oss01.str();
        string str_data02 = "max_exp  : " + oss02.str();
        string str_data03 = "y_quad   : " + oss03.str();
        string str_data04 = "max_goni : " + oss04.str();

        vector<string> err_com;
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back(str_data04);
        err_com.push_back("The complex value is so mach large.");
        err_com.push_back(" Please check the complex value.");

        err_obj.output_runtime_error(class_name, func_name, err_com);
      }

      Real8 w1 =  2.0*exp(x_quad);
            u2 =      w1*cos(y_quad); 
            v2 = -1.0*w1*sin(y_quad); 
    }

    w_x = u2 - w_x;
    w_y = v2 - w_y;

    if( xi > 0.0 )
    {
      w_y = -1.0*w_y;
    }
  }
  else
  {
    if( xi < 0.0 )
    {
      w_y = -1.0*w_y;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ComplexErrorFunctionCalculator::cerfc(Real8 x, Real8& w_x, Real8& w_y)
{
  cerfc(x, h_val, w_x, w_y);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ComplexErrorFunctionCalculator::set_h_val(Real8 real_val)
{
  h_val = real_val;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Real8 ComplexErrorFunctionCalculator::get_h_val()
{
  return h_val;
}

