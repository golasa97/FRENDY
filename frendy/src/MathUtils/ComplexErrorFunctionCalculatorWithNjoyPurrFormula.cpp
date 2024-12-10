#include "MathUtils/ComplexErrorFunctionCalculatorWithNjoyPurrFormula.hpp"

using namespace frendy;

//Initialize static const value
const Real8 ComplexErrorFunctionCalculatorWithNjoyPurrFormula::eps = 1.0E-7;

const Real8 ComplexErrorFunctionCalculatorWithNjoyPurrFormula::c1  = 0.5641895835;
const Real8 ComplexErrorFunctionCalculatorWithNjoyPurrFormula::c2  = 0.2752551000;
const Real8 ComplexErrorFunctionCalculatorWithNjoyPurrFormula::c3  = 2.7247450000;
const Real8 ComplexErrorFunctionCalculatorWithNjoyPurrFormula::c4  = 0.5124242000;
const Real8 ComplexErrorFunctionCalculatorWithNjoyPurrFormula::c5  = 0.0517653600;

const Real8 ComplexErrorFunctionCalculatorWithNjoyPurrFormula::d1  = 0.4613135000;
const Real8 ComplexErrorFunctionCalculatorWithNjoyPurrFormula::d2  = 0.1901635000;
const Real8 ComplexErrorFunctionCalculatorWithNjoyPurrFormula::d3  = 0.0999921600;
const Real8 ComplexErrorFunctionCalculatorWithNjoyPurrFormula::d4  = 1.7844927000;
const Real8 ComplexErrorFunctionCalculatorWithNjoyPurrFormula::d5  = 0.0028838940;
const Real8 ComplexErrorFunctionCalculatorWithNjoyPurrFormula::d6  = 5.5253437000;

const Real8 ComplexErrorFunctionCalculatorWithNjoyPurrFormula::brk1 = 1.2500000;
const Real8 ComplexErrorFunctionCalculatorWithNjoyPurrFormula::brk2 = 5.0000000;
const Real8 ComplexErrorFunctionCalculatorWithNjoyPurrFormula::brk3 = 1.8636360;
const Real8 ComplexErrorFunctionCalculatorWithNjoyPurrFormula::brk4 = 4.1000000;
const Real8 ComplexErrorFunctionCalculatorWithNjoyPurrFormula::brk5 = 1.7100000;
const Real8 ComplexErrorFunctionCalculatorWithNjoyPurrFormula::brk6 = 2.8900000;
const Real8 ComplexErrorFunctionCalculatorWithNjoyPurrFormula::brk7 = 1.1800000;
const Real8 ComplexErrorFunctionCalculatorWithNjoyPurrFormula::brk8 = 5.7600000;
const Real8 ComplexErrorFunctionCalculatorWithNjoyPurrFormula::brk9 = 1.5000000;

//constructor
ComplexErrorFunctionCalculatorWithNjoyPurrFormula::ComplexErrorFunctionCalculatorWithNjoyPurrFormula(void)
{
  rpi     = sqrt(M_PI);
  rpi_inv = 1.0 / rpi;

  clear();
  
  calc_w_table_all();
}

//destructor
ComplexErrorFunctionCalculatorWithNjoyPurrFormula::~ComplexErrorFunctionCalculatorWithNjoyPurrFormula(void)
{
  clear();

  clear_w_table();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ComplexErrorFunctionCalculatorWithNjoyPurrFormula::clear()
{
  h_val = 0.0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ComplexErrorFunctionCalculatorWithNjoyPurrFormula::calc_w_table_all()
{
  Real8 x_ini, y_ini, delta_x, delta_y;
  
  clear_w_table();
  
  //Table No.01
  x_ini   = -0.1;
  delta_x =  0.1;
  y_ini   =  0.4;
  delta_y =  delta_x;
  calc_w_table(x_ini, y_ini, delta_x, delta_y, tr,  ti);
  
  //Table No.02
  y_ini   = -0.02;
  delta_y =  0.02;
  calc_w_table(x_ini, y_ini, delta_x, delta_y, trs, tis);
}


////////////////////////////////////////////////////////////////////////////////////////////////////

void ComplexErrorFunctionCalculatorWithNjoyPurrFormula::calc_w_table
                                                           ( Real8& x_ini,   Real8& y_ini, 
                                                             Real8& delta_x, Real8& delta_y,
                                                             vector<vector<Real8> >& w_r_vec, 
                                                             vector<vector<Real8> >& w_i_vec )
{
  vector<Real8> ax, ay;
  ax.resize(ele_no_x); 
  ay.resize(ele_no_y);

  //Initialize w_r_vec and w_i_vec
  ax.resize(ele_no_x);
  w_r_vec.resize(ele_no_x);
  w_i_vec.resize(ele_no_x);
  for(int i=0; i<ele_no_x; i++)
  {
    w_r_vec[i].resize(ele_no_y);
    w_i_vec[i].resize(ele_no_y);
    for(int j=0; j<ele_no_y; j++)
    {
      w_r_vec[i][j] = 0.0;
      w_i_vec[i][j] = 0.0;
    }
  }

  //Set ax and ay
  ax[0] = x_ini; 
  for(int i=1; i<ele_no_x; i++)
  {
    ax[i] = ax[i-1] + delta_x;
  }

  ay[0] = y_ini;
  for(int i=1; i<ele_no_y; i++)
  {
    ay[i] = ay[i-1] + delta_y;
  }

  for(int i=1; i<ele_no_x; i++)
  {
    for(int j=0; j<ele_no_y; j++)
    {
      calc_complex_probability_integral(ax[i], ay[j], w_r_vec[i][j], w_i_vec[i][j]);
    }
  }
  
  for(int j=0; j<ele_no_y; j++)
  {
    w_r_vec[0][j] =        w_r_vec[2][j];
    w_i_vec[0][j] = -1.0 * w_i_vec[2][j];
    w_i_vec[1][j] =  0.0;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ComplexErrorFunctionCalculatorWithNjoyPurrFormula::calc_complex_probability_integral
                                                           ( Real8& x, Real8& y, Real8& w_r, Real8& w_i )
{
  //Real8 brk1 = 1.2500000;
  //Real8 brk2 = 5.0000000;
  //Real8 brk3 = 1.8636360;
  //Real8 brk4 = 4.1000000;
  //Real8 brk5 = 1.7100000;
  //Real8 brk6 = 2.8900000;
  //Real8 brk7 = 1.1800000;
  //Real8 brk8 = 5.7600000;
  //Real8 brk9 = 1.5000000;
  
  Real8 x_abs = fabs(x);
  Real8 y_abs = fabs(y);
  
  w_r = 0.0;
  w_i = 0.0;
  
  if( x_abs + y_abs == 0.0 )
  {
    w_r = 1.0;
    w_i = 0.0;
    return;
  }
  
  Integer calc_mode = tayler_mode;
  Real8   x_sq      = x * x;
  Real8   y_sq      = y * y;
  if( x_abs + brk1*y_abs - brk2 > 0.0 || x_abs + brk3*y_abs - brk4 > 0.0 ||
      ( x_sq + brk5*y_sq - brk6 >= 0.0 && x_sq + brk7*y_sq - brk8 < 0.0 && y_abs - brk9 >= 0.0 ) )
  {
    if( y > 0.0 )
    {
      calc_mode = asymptotic_mode;
    }
  }


  if( calc_mode == tayler_mode )
  {
    calc_complex_probability_integral_by_tayler_expansion(x, y, x_sq, y_sq, w_r, w_i);
  }
  else
  {
    calc_complex_probability_integral_by_asymptotic_expansion(x, y_abs, x_sq, y_sq, w_r, w_i);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ComplexErrorFunctionCalculatorWithNjoyPurrFormula::
       calc_complex_probability_integral_by_tayler_expansion( Real8& x,    Real8& y,
                                                              Real8& x_sq, Real8& y_sq,
                                                              Real8& w_r,  Real8& w_i )
{
  Real8 temp1    =  x_sq + y_sq;
  Real8 temp2    =  2.0*temp1*temp1;
  Real8 aj       = -1.0*(x_sq - y_sq) / temp2;
  Real8 ajsig    =  0.0;
  Real8 sigp     =  1.5;
  Real8 sig2p    =  2.0*sigp;
  
  Real8 tempc    =  0.0;
  Real8 tempd    =  0.0;
  Real8 tempm    =  0.0;
  Real8 temel    =  0.0;
  Real8 c        =  0.0;
  Real8 d        =  0.0;
  Real8 am       =  1.0;
  Real8 el       =  0.0;
  
  Real8 ak       =  2.0*x*y / temp2;
  Real8 a        =  1.0;
  Real8 b        =  0.0;
  Real8 g        =  0.0;
  Real8 h        =  0.0;
  
  Real8 exp_on   =  exp(temp2*aj);
  Real8 exp_cos  =        exp_on * cos(temp2*ak);
  Real8 exp_sin  = -1.0 * exp_on * sin(temp2*ak);
  
  Integer loop_flg  = 0;
  Real8   temp_coef = rpi_inv / temp1;
  while( loop_flg == 0 )
  { 
    Real8 aj4sig = 4.0 * ajsig;
    Real8 aj4sm1 = aj4sig - 1.0;
    Real8 temp3  = 1.0 / (aj4sm1 * (aj4sig + 3.0));
    Real8 tt4    = sig2p * (2.0*ajsig - 1.0);
    Real8 temp4  = tt4 / (aj4sm1 * (aj4sig+1.0) * (aj4sig-3.0) * aj4sm1);
    Real8 ajp    = aj + temp3;
    
    calc_complex_probability_integral_coef( tempc, tempd, tempm, temel, c, d, am, el,
                                            ajp, temp4, ak, a, b, h, g );
    
    ajsig += 1.0;
    sig2p  = 2.0*ajsig;
    
    Real8 w_r_pre   = w_r;
    Real8 w_i_pre   = w_i;
    Real8 coef_deno = temp_coef / (am*am + el*el);
    Real8 coef1     = c*am + d*el;
    Real8 coef2     = d*am - c*el;
    
    w_r = exp_cos - (coef1*y - coef2*x) * coef_deno;
    w_i = exp_sin - (coef2*y + coef1*x) * coef_deno;
    
    if( fabs(w_r - w_r_pre) < eps )
    {
      if( x == 0.0 )
      {
        loop_flg = 1;
        w_i      = 0.0;
      }
      else if( fabs(w_i - w_i_pre) < eps )
      {
        loop_flg = 1;
      }
   }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ComplexErrorFunctionCalculatorWithNjoyPurrFormula::
       calc_complex_probability_integral_by_asymptotic_expansion( Real8& x,    Real8& y,
                                                                  Real8& x_sq, Real8& y_sq,
                                                                  Real8& w_r,  Real8& w_i )
{
  static const Real8 coef = 1.1283792;
  
  Real8 rv     =  2.0*(x_sq - y_sq);
  Real8 ak     =  4.0*x*y;
  
  Real8 tempc  =  0.0;
  Real8 tempd  =  0.0;
  Real8 tempm  =  0.0;
  Real8 temel  =  0.0;
  Real8 c      = -1.0 * coef * y;
  Real8 d      =        coef * x;
  Real8 am     =  rv - 1.0;
  Real8 el     =  ak;
  
  Real8 a      =  0.0;
  Real8 b      =  0.0;
  Real8 h      =  0.0;
  Real8 g      =  1.0;
  
  Real8 aak    =  1.0;
  
  Integer loop_flg = 0;
  while( loop_flg == 0 )
  {
    Real8 ajtemp = 2.0*aak;
    Real8 temp4  = (1.0 - ajtemp)*ajtemp;
    Real8 ajp    = rv - (4.0*aak + 1.0);
    
    calc_complex_probability_integral_coef( tempc, tempd, tempm, temel, c, d, am, el,
                                            ajp, temp4, ak, a, b, h, g );
    aak += 1.0;
    
    Real8 w_r_pre = w_r;
    Real8 w_i_pre = w_i;
    Real8 w_deno  = 1.0 / (tempm*tempm + temel*temel);
    
    w_r = (tempc*tempm + tempd*temel) * w_deno;
    w_i = (tempd*tempm - tempc*temel) * w_deno;
    
    if( fabs(w_r - w_r_pre) < eps )
    {
      if( x == 0.0 )
      {
        loop_flg = 1;
        w_i      = 0.0;
      }
      else if( fabs(w_i - w_i_pre) < eps )
      {
        loop_flg = 1;
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ComplexErrorFunctionCalculatorWithNjoyPurrFormula::
       calc_complex_probability_integral_coef( Real8& tempc, Real8& tempd, Real8& tempm, Real8& temel,
                                               Real8& c, Real8& d, Real8& am, Real8& el,
                                               Real8& ajp, Real8& temp4, Real8& ak, 
                                               Real8& a, Real8& b, Real8& h, Real8& g )
                                                 
{
  static const Real8 up   = 1.0E+15;
  static const Real8 dn   = 1.0E-15;
  
  tempc = ajp*c  + temp4*a - ak*d;
  tempd = ajp*d  + temp4*b + ak*c;
  temel = ajp*el + temp4*h + ak*am;
  tempm = ajp*am + temp4*g - ak*el;
  
  a  = c;
  b  = d;
  g  = am;
  h  = el;
  c  = tempc;
  d  = tempd;
  am = tempm;
  el = temel;
  
  if( fabs(tempm) + fabs(temel) >= up )
  {
    tempc *= dn;
    tempd *= dn;
    tempm *= dn;
    temel *= dn;
    c     *= dn;
    d     *= dn;
    am    *= dn;
    el    *= dn;
  }
  else if( fabs(tempm) + fabs(temel) <= dn )
  {
    tempc *= up;
    tempd *= up;
    tempm *= up;
    temel *= up;
    c     *= up;
    d     *= up;
    am    *= up;
    el    *= up;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ComplexErrorFunctionCalculatorWithNjoyPurrFormula::clear_w_table()
{
  clr_obj.clear_vec_array2_real8(tr);
  clr_obj.clear_vec_array2_real8(ti);
  clr_obj.clear_vec_array2_real8(trs);
  clr_obj.clear_vec_array2_real8(tis);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ComplexErrorFunctionCalculatorWithNjoyPurrFormula::cerfc(Real8 x, Real8 h, Real8& w_x, Real8& w_y)
{
  set_h_val(h);
  cerfc(x, w_x, w_y);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ComplexErrorFunctionCalculatorWithNjoyPurrFormula::cerfc(Real8 x, Real8& w_x, Real8& w_y)
{
  if( h_val < 0.0 )
  {
    string class_name = "ComplexErrorFunctionCalculatorWithNjoyPurrFormula";
    string func_name  = "cerfc(Real8 x, Real8& w_x, Real8& w_y)";

    ostringstream oss01, oss02;
    oss01 << x;
    oss02 << h_val;
    string str_data01 = "x     : " + oss01.str();
    string str_data02 = "h_val : " + oss02.str();


    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("The value of h_val must be larger than or equal to 0.0.");
    err_com.push_back("Please check the value of h_val.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  if( h_val > 100.0 || x <= -100.0 || ( h_val > 6.0 && x > 100.0 ) || ( h_val > 3.0 && x > 100.0 ) )
  {
    cerfc_case01(x, h_val, w_x, w_y);
  }
  else if( h_val > 6.0 || x <= -6.0 || ( h_val > 3.0 && x > 6.0 ) )
  {
    cerfc_case02(x, h_val, w_x, w_y);
  }
  else if( h_val > 3.0 || x <= -3.9 )
  {
    cerfc_case03(x, h_val, w_x, w_y);
  }
  else if( x <= 3.9 )
  {
    if( h_val >= 0.5 )
    {
      cerfc_case04(x, h_val, w_x, w_y);
    }
    else
    {
      cerfc_case05(x, h_val, w_x, w_y);
    }
  }
  else if( x <= 6.0 )
  {
    cerfc_case03(x, h_val, w_x, w_y);
  }
  else if( x <= 100.0 )
  {
    cerfc_case02(x, h_val, w_x, w_y);
  }
  else
  {
    cerfc_case01(x, h_val, w_x, w_y);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ComplexErrorFunctionCalculatorWithNjoyPurrFormula::cerfc_case01
                                                          (Real8& x, Real8& y, Real8& w_r, Real8& w_i)
{
  Real8 coef = c1 / (x*x + y*y);
  
  w_r = coef * y;
  w_i = coef * x;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ComplexErrorFunctionCalculatorWithNjoyPurrFormula::cerfc_case02
                                                          (Real8& x, Real8& y, Real8& w_r, Real8& w_i)
{
  Real8 a1    = x*x - y*y;
  Real8 a2    = 2.0*x*y;
  Real8 a3    = a2*a2;
  Real8 a4    = a1 - c2;
  Real8 a5    = a1 - c3;
  Real8 f1    = c4 / (a4*a4 + a3);
  Real8 f2    = c5 / (a5*a5 + a3);
  Real8 temp1 = a2*x;
  Real8 temp2 = a2*y;
  
  w_r = f1*(temp1 - a4*y) + f2*(temp1 - a5*y);
  w_i = f1*(temp2 + a4*x) + f2*(temp2 + a5*x);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ComplexErrorFunctionCalculatorWithNjoyPurrFormula::cerfc_case03
                                                          (Real8& x, Real8& y, Real8& w_r, Real8& w_i)
{
  Real8 a1    = x*x - y*y;
  Real8 a2    = 2.0*x*y;
  Real8 a3    = a2*a2;
  Real8 a4    = a1 - d2;
  Real8 a5    = a1 - d4;
  Real8 a6    = a1 - d6;
  Real8 e1    = d1 / (a4*a4 + a3);
  Real8 e2    = d3 / (a5*a5 + a3);
  Real8 e3    = d5 / (a6*a6 + a3);
  Real8 temp1 = a2*x;
  Real8 temp2 = a2*y;
  
  w_r = e1*(temp1 - a4*y) + e2*(temp1 - a5*y) + e3*(temp1 - a6*y);
  w_i = e1*(temp2 + a4*x) + e2*(temp2 + a5*x) + e3*(temp2 + a6*x);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ComplexErrorFunctionCalculatorWithNjoyPurrFormula::cerfc_case04
                                                          (Real8& x, Real8& y, Real8& w_r, Real8& w_i)
{
  Real8 x_ten = 10.0*fabs(x);
  int ii = int(x_ten);
  int i  = ii + 1;
  Real8 x_ten_res         = x_ten - Real8(ii);
  Real8 x_ten_res_sq      = x_ten_res * x_ten_res;
  Real8 x_ten_res_half    = 0.5*x_ten_res;
  Real8 x_ten_res_sq_half = 0.5*x_ten_res_sq;
  
  Real8 y_ten = 10.0*y;
  int jj = int(y_ten);
  int j  = jj - 4;
  Real8 y_ten_res         = y_ten - Real8(jj);
  Real8 y_ten_res_sq      = y_ten_res * y_ten_res;
  Real8 y_ten_res_half    = 0.5*y_ten_res;
  Real8 y_ten_res_sq_half = 0.5*y_ten_res_sq;
  
  Real8 xy_res = x_ten_res * y_ten_res;
  
  Real8 a1 = y_ten_res_sq_half - y_ten_res_half;
  Real8 a2 = x_ten_res_sq_half - x_ten_res_half;
  Real8 a3 = 1.0 + xy_res - x_ten_res_sq - y_ten_res_sq;
  Real8 a4 = x_ten_res_sq_half - xy_res + x_ten_res_half;
  Real8 a5 = y_ten_res_sq_half - xy_res + y_ten_res_half;
  
  w_r = a1*tr[i][j-1] + a2*tr[i-1][j] + a3*tr[i][j] + a4*tr[i+1][j] + a5*tr[i][j+1] + xy_res*tr[i+1][j+1];
  w_i = a1*ti[i][j-1] + a2*ti[i-1][j] + a3*ti[i][j] + a4*ti[i+1][j] + a5*ti[i][j+1] + xy_res*ti[i+1][j+1];
  if( x < 0.0 )
  {
    w_i *= -1.0;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ComplexErrorFunctionCalculatorWithNjoyPurrFormula::cerfc_case05
                                                          (Real8& x, Real8& y, Real8& w_r, Real8& w_i)
{
  Real8 x_ten = 10.0*fabs(x);
  int ii = int(x_ten);
  int i  = ii + 1;
  Real8 x_ten_res         = x_ten - Real8(ii);
  Real8 x_ten_res_sq      = x_ten_res * x_ten_res;
  Real8 x_ten_res_half    = 0.5*x_ten_res;
  Real8 x_ten_res_sq_half = 0.5*x_ten_res_sq;
  
  Real8 y_fif = 50.0*y;
  int jj = int(y_fif);
  int j  = jj + 1;
  Real8 y_fif_res         = y_fif - Real8(jj);
  Real8 y_fif_res_sq      = y_fif_res * y_fif_res;
  Real8 y_fif_res_half    = 0.5*y_fif_res;
  Real8 y_fif_res_sq_half = 0.5*y_fif_res_sq;
  
  Real8 xy_res = x_ten_res * y_fif_res;
  
  Real8 a1 = y_fif_res_sq_half - y_fif_res_half;
  Real8 a2 = x_ten_res_sq_half - x_ten_res_half;
  Real8 a3 = 1.0 + xy_res - x_ten_res_sq - y_fif_res_sq;
  Real8 a4 = x_ten_res_sq_half - xy_res + x_ten_res_half;
  Real8 a5 = y_fif_res_sq_half - xy_res + y_fif_res_half;
  
  w_r = a1*trs[i][j-1] + a2*trs[i-1][j] + a3*trs[i][j] + a4*trs[i+1][j] + a5*trs[i][j+1] + xy_res*trs[i+1][j+1];
  w_i = a1*tis[i][j-1] + a2*tis[i-1][j] + a3*tis[i][j] + a4*tis[i+1][j] + a5*tis[i][j+1] + xy_res*tis[i+1][j+1];
  if( x < 0.0 )
  {
    w_i *= -1.0;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ComplexErrorFunctionCalculatorWithNjoyPurrFormula::set_h_val(Real8 real_val)
{
  h_val = real_val;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Real8 ComplexErrorFunctionCalculatorWithNjoyPurrFormula::get_h_val()
{
  return h_val;
}

