#include "MathUtils/ErrorFunctionCalculatorWithPolynomialExpansion.hpp"

using namespace frendy;

//constructor
ErrorFunctionCalculatorWithPolynomialExpansion::ErrorFunctionCalculatorWithPolynomialExpansion(void)
{
  //For single precision (float)
  alpha_f = static_cast<float>(9.2088871045460211E+00);
  beta_f  = static_cast<float>(5.0725473171624327E+00);
  a_f[0]  = static_cast<float>(3.8664221739686797E-01);
  a_f[1]  = static_cast<float>(1.5243017675919252E-01);
  a_f[2]  = static_cast<float>(2.3814912488843075E-02);
  a_f[3]  = static_cast<float>(1.3022729124288807E-03);
  b_f[0]  = static_cast<float>(1.1638196508217325E-01);
  b_f[1]  = static_cast<float>(1.0475380173789841E+00);
  b_f[2]  = static_cast<float>(2.9213215631713289E+00);
  b_f[3]  = static_cast<float>(6.0260843416158831E+00);

  //For double precision (double)
  alpha_d = 1.269748999651156838985811E+01;
  beta_d  = 6.103997330986881994334338E+00;
  a_d[0]  = 2.963168851992273778336357E-01;
  a_d[1]  = 1.815811251346370699640955E-01;
  a_d[2]  = 6.818664514249394930148282E-02;
  a_d[3]  = 1.569075431619667090378092E-02;
  a_d[4]  = 2.212901166815175728291522E-03;
  a_d[5]  = 1.913958130987428643791697E-04;
  a_d[6]  = 9.710132840105516234434841E-06;
  a_d[7]  = 1.666424471743077527468010E-07;
  b_d[0]  = 6.121586444955387580549294E-02;
  b_d[1]  = 5.509427800560020848936831E-01;
  b_d[2]  = 1.530396620587703969527527E+00;
  b_d[3]  = 2.999579523113006340465739E+00;
  b_d[4]  = 4.958677771282467011450533E+00;
  b_d[5]  = 7.414712510993354068147575E+00;
  b_d[6]  = 1.047651043565452375901435E+01;
  b_d[7]  = 1.484555573455979566646185E+01;
}

//destructor
ErrorFunctionCalculatorWithPolynomialExpansion::~ErrorFunctionCalculatorWithPolynomialExpansion(void)
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ErrorFunctionCalculatorWithPolynomialExpansion::calc_erfc(float x, float x_sq, float exp_x_sq_inv, float& erfc_x)
{
  //In the doppler broadening calculation, x_sq and exp(-x_sq) are already calculated.
  //Therefore, to reduce the calculation time, this function is developed.
 
  float tmp = 0.0;
  for(int i=0; i<n_f; i++)
  {
    tmp += a_f[i] / (x_sq + b_f[i]);
  }
  erfc_x = x*exp_x_sq_inv*tmp;

  if( x < beta_f )
  {
    erfc_x += static_cast<float>(2.0 / (1.0+exp(alpha_f*x)));
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ErrorFunctionCalculatorWithPolynomialExpansion::calc_erf(float x, float x_sq, float exp_x_sq_inv, float& erf_x)
{
  calc_erfc(x, x_sq, exp_x_sq_inv, erf_x);
  erf_x = static_cast<float>(1.0 - erf_x);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

float ErrorFunctionCalculatorWithPolynomialExpansion::erfc(float x)
{
  float erfc_x;
  float x_sq         = x*x;
  float exp_x_sq_inv = static_cast<float>(exp(-1.0*x_sq));

  calc_erfc(x, x_sq, exp_x_sq_inv, erfc_x);

  return erfc_x;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

float ErrorFunctionCalculatorWithPolynomialExpansion::erf(float x)
{
  float erf_x;
  float x_sq         = x*x;
  float exp_x_sq_inv = static_cast<float>(exp(-1.0*x_sq));

  calc_erf(x, x_sq, exp_x_sq_inv, erf_x);

  return erf_x;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ErrorFunctionCalculatorWithPolynomialExpansion::calc_erfc(double x, double x_sq, double exp_x_sq_inv, double& erfc_x)
{
  //In the doppler broadening calculation, x_sq and exp(-x_sq) are already calculated.
  //Therefore, to reduce the calculation time, this function is developed.

  double tmp = 0.0;
  for(int i=0; i<n_d; i++)
  {
    tmp += a_d[i] / (x_sq + b_d[i]);
  }
  erfc_x = x*exp_x_sq_inv*tmp;

  if( x < beta_d )
  {
    erfc_x += 2.0 / (1.0+exp(alpha_d*x));
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ErrorFunctionCalculatorWithPolynomialExpansion::calc_erf(double x, double x_sq, double exp_x_sq_inv, double& erf_x)
{
  calc_erfc(x, x_sq, exp_x_sq_inv, erf_x);
  erf_x = 1.0 - erf_x;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

double ErrorFunctionCalculatorWithPolynomialExpansion::erfc(double x)
{
  double erfc_x;
  double x_sq         = x*x;
  double exp_x_sq_inv = exp(-1.0*x_sq);

  calc_erfc(x, x_sq, exp_x_sq_inv, erfc_x);

  return erfc_x;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

double ErrorFunctionCalculatorWithPolynomialExpansion::erf(double x)
{
  double erf_x;
  double x_sq         = x*x;
  double exp_x_sq_inv = exp(-1.0*x_sq);

  calc_erf(x, x_sq, exp_x_sq_inv, erf_x);

  return erf_x;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

