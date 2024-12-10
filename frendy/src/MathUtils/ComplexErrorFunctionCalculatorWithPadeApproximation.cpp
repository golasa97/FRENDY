#include "MathUtils/ComplexErrorFunctionCalculatorWithPadeApproximation.hpp"

using namespace frendy;

//constructor
ComplexErrorFunctionCalculatorWithPadeApproximation::ComplexErrorFunctionCalculatorWithPadeApproximation(void)
{
  clear_all();
}

//destructor
ComplexErrorFunctionCalculatorWithPadeApproximation::~ComplexErrorFunctionCalculatorWithPadeApproximation(void)
{
  clear_all();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ComplexErrorFunctionCalculatorWithPadeApproximation::clear_all()
{
  pole_no = 4;

  case_no_list.clear();
  clr_obj.clear_vec_array3_real8(coef_p);
  clr_obj.clear_vec_array3_real8(coef_q);

  coef_r_num.clear();
  coef_i_num.clear();
  coef_den.clear();

  set_coef();

  clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ComplexErrorFunctionCalculatorWithPadeApproximation::clear()
{
  h_val = 0.0;
  set_coef_for_calc();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ComplexErrorFunctionCalculatorWithPadeApproximation::set_coef()
{
  pi      = M_PI;
  pi_sq   = pi*pi;
  rpi     = sqrt(pi);
  rpi_inv = 1.0 / rpi;

  set_coef_p_q();

  coef_r_num.resize(4);
  coef_i_num.resize(4);
  coef_den.resize(5);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ComplexErrorFunctionCalculatorWithPadeApproximation::set_coef_p_q()
{
  int pole_no_max = 3; //2, 3 and 4
  case_no_list.resize(pole_no_max);
  //case_no_list[0] = 0; //for Z31
  case_no_list[0] = 1; //for Z22
  //case_no_list[0] = 2; //for Z13
  //case_no_list[1] = 0; //for Z51
  case_no_list[1] = 1; //for Z42
  //case_no_list[1] = 2; //for Z33
  case_no_list[2] = 0; //for Z53

  coef_p.resize(pole_no_max);
  coef_q.resize(pole_no_max);

  set_coef_p_q_two_pole();
  set_coef_p_q_three_pole();
  set_coef_p_q_four_pole();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ComplexErrorFunctionCalculatorWithPadeApproximation::set_coef_p_q_two_pole()
{
  //For 2-pole case
  int i       = 0;
  int case_no = 3;
  int coef_no = 2;
  coef_p[i].resize(case_no);
  coef_q[i].resize(case_no);
  for(int j=0; j<case_no; j++)
  {
    coef_p[i][j].resize(coef_no);
    coef_q[i][j].resize(coef_no);

    if( j == 0 ) //For Z31
    {
      coef_p[i][j][0] = rpi;
      coef_p[i][j][1] = (4.0 - pi) / (pi - 2.0);
      coef_q[i][j][0] = -1.0*rpi / (pi - 2.0);
      coef_q[i][j][1] = -1.0*coef_p[i][j][1];
    }
    else if( j == 1 ) //For Z22
    {
      coef_p[i][j][0] = rpi;
      coef_p[i][j][1] = pi - 2.0;
      coef_q[i][j][0] = -1.0*rpi;
      coef_q[i][j][1] = -1.0*coef_p[i][j][1];
    }
    else if( j == 2 ) //For Z13
    {
      coef_p[i][j][0] = rpi;
      coef_p[i][j][1] = 2.0;
      coef_q[i][j][0] = -1.0*rpi;
      coef_q[i][j][1] = -2.0;
    }
  }
}


////////////////////////////////////////////////////////////////////////////////////////////////////

void ComplexErrorFunctionCalculatorWithPadeApproximation::set_coef_p_q_three_pole()
{
  //For 3-pole case
  int i       = 1;
  int case_no = 3;
  int coef_no = 3;
  coef_p[i].resize(case_no);
  coef_q[i].resize(case_no);
  for(int j=0; j<case_no; j++)
  {
    coef_p[i][j].resize(coef_no);
    coef_q[i][j].resize(coef_no);

    if( j == 0 ) //For Z51
    {
      Real8 coef_tmp = 0.5 / (5.0*pi - 16.0);
      coef_p[i][j][0] = rpi;
      coef_p[i][j][1] = coef_tmp * (3.0*pi_sq - 30.0*pi + 64.0);
      coef_p[i][j][2] = rpi * coef_tmp * (9.0*pi - 28.0) / 3.0;
      coef_q[i][j][0] = rpi * coef_tmp * (-3.0*pi + 10.0);
      coef_q[i][j][1] = coef_tmp * (21.0*pi - 64.0) / 3.0;
      coef_q[i][j][2] = -1.0*coef_p[i][j][2];
    }
    else if( j == 1 ) //For Z42
    {
      Real8 coef_tmp = 1.0 / (3.0*(pi - 3.0));
      coef_p[i][j][0] = rpi;
      coef_p[i][j][1] = coef_tmp * ( 10.0 - 3.0*pi);
      coef_p[i][j][2] = coef_tmp * (-16.0 + 5.0*pi) * rpi_inv;
      coef_q[i][j][0] = coef_tmp * (  8.0 - 3.0*pi) * rpi_inv;
      coef_q[i][j][1] = -1.0*coef_p[i][j][1];
      coef_q[i][j][2] = -1.0*coef_p[i][j][2];
    }
    else if( j == 2 ) //For Z33
    {
      Real8 coef_tmp = 1.0 / (4.0 - pi);
      coef_p[i][j][0] = rpi;
      coef_p[i][j][1] = coef_tmp * (3.0*pi - 8.0);
      coef_p[i][j][2] = rpi * coef_tmp * (-2.0 * (pi - 3.0));
      coef_q[i][j][0] = -1.0 * rpi * coef_tmp;
      coef_q[i][j][1] = -1.0*coef_p[i][j][1];
      coef_q[i][j][2] = -1.0*coef_p[i][j][2];
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ComplexErrorFunctionCalculatorWithPadeApproximation::set_coef_p_q_four_pole()
{
  //For 4-pole case
  int i       = 2;
  int case_no = 1;
  int coef_no = 4;
  coef_p[i].resize(case_no);
  coef_q[i].resize(case_no);
  for(int j=0; j<case_no; j++)
  {
    coef_p[i][j].resize(coef_no);
    coef_q[i][j].resize(coef_no);
    if( j == 0 ) //For Z53
    {
      Real8 coef_tmp = 1.0 / (6.0*pi_sq - 29.0*pi + 32.0);
      coef_p[i][j][0] = rpi;
      coef_p[i][j][1] = coef_tmp * (-15.0*pi_sq + 88.0*pi - 128.0) * 0.5;
      coef_p[i][j][2] = rpi * coef_tmp * (33.0*pi - 104.0) / 6.0;
      coef_p[i][j][3] = coef_tmp * (-9.0*pi_sq + 69.0*pi - 128.0) / 3.0;
      coef_q[i][j][0] = rpi * coef_tmp * (-9.0*pi + 28.0) * 0.5;
      coef_q[i][j][1] = coef_tmp * (36.0*pi_sq - 195.0*pi + 256.0) / 6.0;
      coef_q[i][j][2] = -1.0*coef_p[i][j][2];
      coef_q[i][j][3] = -1.0*coef_p[i][j][3];
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ComplexErrorFunctionCalculatorWithPadeApproximation::set_coef_for_calc()
{
  if( pole_no == 4 )
  {
    set_coef_for_calc_four_pole();
  }
  else if( pole_no == 3 )
  {
    set_coef_for_calc_three_pole();
  }
  else if( pole_no == 2 )
  {
    set_coef_for_calc_two_pole();
  }
  else
  {
    string class_name = "ComplexErrorFunctionCalculatorWithPadeApproximation";
    string func_name  = "set_coef_for_calc()";

    ostringstream oss;
    oss << pole_no;
    string str_data = "Pole number of the Pade approximation : " + oss.str();

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("The pole number of the Pade approximation is only available for 2, 3 or 4.");
    err_com.push_back("Please check the pole number of the Pade approximation.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ComplexErrorFunctionCalculatorWithPadeApproximation::set_coef_for_calc_two_pole()
{
  int i       = 0;
  int case_no = case_no_list[i];

  Real8 p0 = coef_p[i][case_no][0];
  Real8 p1 = coef_p[i][case_no][1];
  Real8 q1 = coef_q[i][case_no][0];
  Real8 q2 = coef_q[i][case_no][1];

  Real8 coef1 = 1.0 - (q1 + q2*h_val)*h_val;
  Real8 coef2 = p0 + p1*h_val;
  Real8 coef3 = q1 + 2.0*q2*h_val;

  //Coefficions for numerator of real part of Z function
  coef_r_num[0] = p1*coef1 + coef2*coef3;
  coef_r_num[1] = p1*q2;
  coef_r_num[2] = 0.0;
  coef_r_num[3] = 0.0;

  //Coefficions for numerator of imaginary part of Z function
  coef_i_num[0] = coef2*coef1;
  coef_i_num[1] = q2*coef2 - p1*coef3;
  coef_i_num[2] = 0.0;
  coef_i_num[3] = 0.0;

  //Coefficions for denominator of Z function
  coef_den[0] = coef1*coef1;
  coef_den[1] = 2.0*q2*coef1 + coef3*coef3;
  coef_den[2] = q2*q2;
  coef_den[3] = 0.0;
  coef_den[4] = 0.0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ComplexErrorFunctionCalculatorWithPadeApproximation::set_coef_for_calc_three_pole()
{
  int i       = 1;
  int case_no = case_no_list[i];

  Real8 p0 = coef_p[i][case_no][0];
  Real8 p1 = coef_p[i][case_no][1];
  Real8 p2 = coef_p[i][case_no][2];
  Real8 q1 = coef_q[i][case_no][0];
  Real8 q2 = coef_q[i][case_no][1];
  Real8 q3 = coef_q[i][case_no][2];

  Real8 h2 = h_val * h_val;

  Real8 coef1 = p1 - 2.0*p2*h_val;
  Real8 coef2 = 1.0 - (q1 + q2*h_val - q3*h2)*h_val;
  Real8 coef3 = p0 + p1*h_val - p2*h2;
  Real8 coef4 = q1 + 2.0*q2*h_val - 3.0*q3*h2;
  Real8 coef5 = q2 - 3.0*q3*h_val;

  //Coefficions for numerator of real part of Z function
  coef_r_num[0] = coef1*coef2 + coef3*coef4;
  coef_r_num[1] = coef1*coef5 + q3*coef3 + p2*coef4;
  coef_r_num[2] = p2*q3;
  coef_r_num[3] = 0.0;

  //Coefficions for numerator of imaginary part of Z function
  coef_i_num[0] = coef3*coef2;
  coef_i_num[1] = coef3*coef5 + p2*coef2 - coef1*coef4;
  coef_i_num[2] = p2*coef5 - q3*coef1;
  coef_i_num[3] = 0.0;

  //Coefficions for denominator of Z function
  coef_den[0] = coef2*coef2;
  coef_den[1] = 2.0*coef2*coef5 + coef4*coef4;
  coef_den[2] = coef5*coef5 + 2.0*q3*coef4;
  coef_den[3] = q3*q3;
  coef_den[4] = 0.0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ComplexErrorFunctionCalculatorWithPadeApproximation::set_coef_for_calc_four_pole()
{
  int i       = 2;
  int case_no = case_no_list[i];

  Real8 p0 = coef_p[i][case_no][0];
  Real8 p1 = coef_p[i][case_no][1];
  Real8 p2 = coef_p[i][case_no][2];
  Real8 p3 = coef_p[i][case_no][3];
  Real8 q1 = coef_q[i][case_no][0];
  Real8 q2 = coef_q[i][case_no][1];
  Real8 q3 = coef_q[i][case_no][2];
  Real8 q4 = coef_q[i][case_no][3];

  Real8 h2 = h_val * h_val;

  Real8 coef1 = p1 - (2.0*p2 + 3.0*p3*h_val)*h_val;
  Real8 coef2 = 1.0 - (q1 + (q2 - q3*h_val - q4*h2)*h_val)*h_val;
  Real8 coef3 = p0 + (p1 - p2*h_val - p3*h2)*h_val;
  Real8 coef4 = q1 + (2.0*q2 - 3.0*q3*h_val - 4.0*q4*h2)*h_val;
  Real8 coef5 = q2 - 3.0*q3*h_val - 6.0*q4*h2;
  Real8 coef6 = q3 + 4.0*q4*h_val;
  Real8 coef7 = p2 + 3.0*p3*h_val;

  //Coefficions for numerator of real part of Z function
  coef_r_num[0] = coef1*coef2 + coef3*coef4;
  coef_r_num[1] = coef1*coef5 + p3*coef2 + coef3*coef6 + coef7*coef4;
  coef_r_num[2] = p3*coef5 + q4*coef1 + coef7*coef6;
  coef_r_num[3] = p3*q4;

  //Coefficions for numerator of imaginary part of Z function
  coef_i_num[0] = coef3*coef2;
  coef_i_num[1] = coef3*coef5 + coef7*coef2 - coef1*coef4;
  coef_i_num[2] = q4*coef3 + coef7*coef5 - coef1*coef6 - p3*coef4;
  coef_i_num[3] = q4*coef7 - p3*coef6;

  //Coefficions for denominator of Z function
  coef_den[0] = coef2*coef2;
  coef_den[1] = 2.0*coef2*coef5 + coef4*coef4;
  coef_den[2] = coef5*coef5 + 2.0*coef4*coef6 + 2.0*q4*coef2;
  coef_den[3] = 2.0*q4*coef5 + coef6*coef6;
  coef_den[4] = q4*q4;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ComplexErrorFunctionCalculatorWithPadeApproximation::cerfc(Real8 xi, Real8 yi, Real8& w_x, Real8& w_y)
{
  if( fabs(yi - h_val) >= fabs(min_ene_dif*h_val) )
  {
    set_h_val(yi);
  }

  cerfc(xi, w_x, w_y);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ComplexErrorFunctionCalculatorWithPadeApproximation::cerfc(Real8 xi, Real8& w_x, Real8& w_y)
{
  cerfc_four_pole(xi, w_x, w_y);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ComplexErrorFunctionCalculatorWithPadeApproximation::cerfc_with_specified_pole_no(Real8 xi, Real8& w_x, Real8& w_y)
{
  if( pole_no == 4 )
  {
    cerfc_four_pole(xi, w_x, w_y);
  }
  else if( pole_no == 3 )
  {
    cerfc_three_pole(xi, w_x, w_y);
  }
  else if( pole_no == 2 )
  {
    cerfc_two_pole(xi, w_x, w_y);
  }
  else
  {
    string class_name = "ComplexErrorFunctionCalculatorWithPadeApproximation";
    string func_name  = "cerfc(Real8 xi, Real8& w_x, Real8& w_y)";

    ostringstream oss;
    oss << pole_no;
    string str_data = "Pole number of the Pade approximation : " + oss.str();

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("The pole number of the Pade approximation is only available for 2, 3 or 4.");
    err_com.push_back("Please check the pole number of the Pade approximation.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ComplexErrorFunctionCalculatorWithPadeApproximation::cerfc_two_pole(Real8 xi, Real8& w_x, Real8& w_y)
{
  Real8 x2 = xi * xi;

  Real8 coef_val = rpi_inv / ( coef_den[0] + (coef_den[1] + coef_den[2]*x2)*x2 );

  w_x =        coef_val * (coef_i_num[0] + coef_i_num[1]*x2);
  w_y = -1.0 * coef_val * (coef_r_num[0] + coef_r_num[1]*x2) * xi;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ComplexErrorFunctionCalculatorWithPadeApproximation::cerfc_three_pole(Real8 xi, Real8& w_x, Real8& w_y)
{
  Real8 x2 = xi * xi;

  Real8 coef_val = rpi_inv / ( coef_den[0] + (coef_den[1] + (coef_den[2] + coef_den[3]*x2)*x2)*x2 );

  w_x =        coef_val * (coef_i_num[0] + (coef_i_num[1] + coef_i_num[2]*x2)*x2);
  w_y = -1.0 * coef_val * (coef_r_num[0] + (coef_r_num[1] + coef_r_num[2]*x2)*x2) * xi;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ComplexErrorFunctionCalculatorWithPadeApproximation::cerfc_four_pole(Real8 xi, Real8& w_x, Real8& w_y)
{
  Real8 x2 = xi * xi;
  Real8 x4 = x2 * x2;

  Real8 coef_val = rpi_inv
                 / ( coef_den[0] + coef_den[1]*x2 + (coef_den[2] + coef_den[3]*x2 + coef_den[4]*x4)*x4 );

  w_x =        coef_val * (coef_i_num[0] + (coef_i_num[1] + coef_i_num[2]*x2 + coef_i_num[3]*x4)*x2);
  w_y = -1.0 * coef_val * (coef_r_num[0] + (coef_r_num[1] + coef_r_num[2]*x2 + coef_r_num[3]*x4)*x2) * xi;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ComplexErrorFunctionCalculatorWithPadeApproximation::set_h_val(Real8 real_val)
{
  h_val = real_val;
  set_coef_for_calc();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Real8 ComplexErrorFunctionCalculatorWithPadeApproximation::get_h_val()
{
  return h_val;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ComplexErrorFunctionCalculatorWithPadeApproximation::set_pole_no(int int_val)
{
  pole_no = int_val;

  set_coef_for_calc(); 
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int ComplexErrorFunctionCalculatorWithPadeApproximation::get_pole_no()
{
  return pole_no;
}

