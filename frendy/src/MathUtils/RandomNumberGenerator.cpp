#include "MathUtils/RandomNumberGenerator.hpp"

using namespace frendy;

//Initialize static const value
const Real8 RandomNumberGenerator::dist_uni_min = 0.0;
const Real8 RandomNumberGenerator::dist_uni_max = 1.0;

//constructor
RandomNumberGenerator::RandomNumberGenerator(void)
{
  clear();
}

//destructor
RandomNumberGenerator::~RandomNumberGenerator(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void RandomNumberGenerator::initialization()
{
  normal_distribution_flg = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void RandomNumberGenerator::clear()
{
  frendy::Integer seed_val = seed_ori;
  set_seed(seed_val);

  third        = 1.0 / 3.0;
  chi_beta     = 2.0;

  normal_rand1 = 0.0;
  normal_rand2 = 0.0;

  set_gamma_alpha(1.0);
  set_chi_freedom(1.0);

  fix_random_flg = random_mode;
  fix_random_val = 0.0;

  coef_wigner_distr = 2.0/sqrt(M_PI);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Real8 RandomNumberGenerator::uniform_distribution()
{
  if( fix_random_flg == fix_random_mode )
  {
    return fix_random_val;
  }

#ifdef MERSENNE_MODE
  return uniform_distribution_boost(); //Using Mersenne Twister
#else
  return uniform_distribution_mcg();   //Using mixed congruential generator
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef MERSENNE_MODE
Real8 RandomNumberGenerator::uniform_distribution_boost()
{
  if( fix_random_flg == fix_random_mode )
  {
    return fix_random_val;
  }

  static boost::uniform_real<Real8> dist_uni(dist_uni_min, dist_uni_max);

  return dist_uni(gen_uni);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

#else
Real8 RandomNumberGenerator::uniform_distribution_mcg()
{
  if( fix_random_flg == fix_random_mode )
  {
    return fix_random_val;
  }

  rand_pre_mcg = (mcg_multiplier*rand_pre_mcg + mcg_increment)%mcg_cycle;

  return static_cast<Real8>(rand_pre_mcg) / static_cast<Real8>(mcg_cycle);
}
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////

Real8 RandomNumberGenerator::normal_distribution(Real8& mu, Real8& sigma)
{
  Real8 rand_normal = mu + sigma*standard_normal_distribution();
  return rand_normal;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Real8 RandomNumberGenerator::standard_normal_distribution()
{
  //The Polar method is used for the algorithm

  //mu=0.0, sigma=1.0
  Real8 rand_normal = 0.0;

  if( normal_distribution_flg == 0 )
  {
    Real8 rand_tot = 100.0;
    Real8 rand1    = 0.0;
    Real8 rand2    = 0.0;

    while( rand_tot > 1.0 - min_value || fabs(rand_tot) < min_value )
    {
      rand1 = uniform_distribution();
      rand2 = uniform_distribution();
      rand1 = 2.0*rand1 - 1.0;
      rand2 = 2.0*rand2 - 1.0;
      rand_tot = rand1*rand1 + rand2*rand2;
    }

    Real8 w_val = sqrt(-2.0*log(rand_tot)/rand_tot);
    normal_rand1 = w_val * rand1;
    normal_rand2 = w_val * rand2;

    normal_distribution_flg = 1;
    rand_normal = normal_rand1;
  }
  else
  {
    normal_distribution_flg = 0;
    rand_normal = normal_rand2;
  }

  return rand_normal;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Real8 RandomNumberGenerator::exponential_distribution(Real8& theta)
{
  //The inverse function method is used for the algorithm
  Real8 rand_exp = 0.0;
  if( theta > 0.0 )
  {
    Real8 rand_uni = uniform_distribution();
    while( fabs(1.0 - rand_uni) < min_value )
    {
      rand_uni = uniform_distribution();
    }

    rand_exp = -1.0 * theta * log(1.0 - rand_uni);
  }
  else
  {
    string class_name = "RandomNumberGenerator";
    string func_name  = "exponential_distribution(Real8& theta)";

    ostringstream oss;
    oss << theta;
    string str_data = "Theta of exponential distribution : " + oss.str();

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("Theta of exponential distribution must be larger than 0.0.");
    err_com.push_back("Please check the Theta of exponential distribution.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  return rand_exp;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Real8 RandomNumberGenerator::gamma_distribution(Real8& alpha, Real8& beta)
{
  set_gamma_alpha(alpha);
  return gamma_distribution(beta);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Real8 RandomNumberGenerator::gamma_distribution(Real8& beta)
{
  //The compress  method is used for the algorithm
  //G. Marsaglia and W. W. Tsang, "A Simple method for generating gamma variables,"
  //ACM Transaction on Mathematical Software, vol. 26[3], pp.1-11, 2000.
  
  if(gamma_distribution_flg == gamma_alpha_equal_one)
  {
    return exponential_distribution(beta);
  }

  Real8 rand_gamma   = 0.0;
  Real8 rand_uni     = 0.0;
  Real8 rand_normal  = 0.0;
  Real8 rand_normal2 = 0.0;
  Real8 rand_normal4 = 0.0;

  Real8 v_val        = -100.0;
  Real8 w_val        = 0.0;
  Real8 y_val        = 0.0;

  frendy::Integer loop_flg = 0;
  while( loop_flg == 0 )
  {
    v_val = -100.0;
    while( v_val < min_value )
    {
      rand_normal = standard_normal_distribution();
      v_val = 1.0 + gamma_val1*rand_normal; 
    }

    w_val = v_val*v_val*v_val;
    y_val = gamma_val2*w_val;

    rand_uni = uniform_distribution();
    while( fabs(rand_uni) < min_value )
    {
      rand_uni = uniform_distribution();
    }

    rand_normal2 = rand_normal *rand_normal;
    rand_normal4 = rand_normal2*rand_normal2;

    if( rand_uni <= 1.0 - 0.0331*rand_normal4 )
    {
      loop_flg = 1;
    }
    else if( 0.5*rand_normal2 + gamma_val2*log(w_val) - y_val + gamma_val2 >= log(rand_uni) )
    {
      loop_flg = 1;
    }
  }

  rand_gamma = beta*y_val;

  if( gamma_distribution_flg == gamma_alpha_smaller_one )
  {
    rand_uni = uniform_distribution();
    while( fabs(rand_uni) < min_value )
    {
      rand_uni = uniform_distribution();
    }

    rand_gamma *= pow(rand_uni, gamma_alpha_inv);
  }

  return rand_gamma;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Real8 RandomNumberGenerator::chi_square_distribution(Real8& freedom)
{
  set_chi_freedom(freedom);
  return chi_square_distribution();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Real8 RandomNumberGenerator::chi_square_distribution()
{
  Real8 rand_chi_square = gamma_distribution(chi_beta);

  if( chi_freedom_flg == chi_freedom_one )
  {
    Real8 rand_uni   = uniform_distribution();
    rand_chi_square *= rand_uni*rand_uni;
  }

  return rand_chi_square;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Real8 RandomNumberGenerator::cauchy_distribution(Real8& mu, Real8& theta)
{
  Real8 rand_cauchy = standard_cauchy_distribution();
  rand_cauchy = mu + rand_cauchy * theta;

  return rand_cauchy;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Real8 RandomNumberGenerator::standard_cauchy_distribution()
{
  Real8 rand_cauchy = standard_normal_distribution(); 
  Real8 rand_norm   = standard_normal_distribution(); 
  while( fabs(rand_norm) < min_value )
  {
    rand_norm = standard_normal_distribution(); 
  }

  rand_cauchy /= rand_norm;
  return rand_cauchy;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Real8 RandomNumberGenerator::cauchy_distribution_abs(Real8& mu, Real8& theta)
{
  Real8 rand_cauchy = fabs(cauchy_distribution(mu, theta));

  return rand_cauchy;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Real8 RandomNumberGenerator::standard_cauchy_distribution_abs()
{
  Real8 rand_cauchy = fabs(standard_cauchy_distribution());

  return rand_cauchy;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Real8 RandomNumberGenerator::wigner_distribution()
{
  //Wigner distribution P(x)
  //  P(x) = pi/2 * x * exp(-pi/4 * x^2)
  //
  //Cumulative distribution function of Wigner distribution F(x)
  //  F(x) = integral(p(x) dx) from 0 to y
  //       = 1 - exp(-pi/4 * y^2)
  //
  //Inverse function of F(x)^-1
  //  F(x)^-1 = 2/sqrt(pi) * log( (1/1-y)^0.5 )
  //          = 2/sqrt(pi) * sqrt( -1.0 * log(1-y) )
  //          = 2/sqrt(pi) * sqrt( -1.0 * log( y ) )


  Real8 rand_wigner = uniform_distribution();
  rand_wigner = coef_wigner_distr * sqrt(-1.0*log(rand_wigner));

  return rand_wigner;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void RandomNumberGenerator::set_seed(frendy::Integer seed_val)
{
  frendy::RandomNumberGenerator::initialization();

  seed = seed_val;

#ifdef MERSENNE_MODE
  gen_uni.seed(seed);
#else
  rand_pre_mcg = static_cast<unsigned long int>(seed);
#endif

}

void RandomNumberGenerator::set_seed_time()
{
  frendy::Integer seed_val = static_cast<frendy::Integer>(time(0));

  set_seed(seed_val);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void RandomNumberGenerator::set_gamma_alpha(Real8 alpha)
{
  gamma_alpha     = alpha;
  gamma_alpha_inv = 1.0 / gamma_alpha;

  Real8 alpha_cal = gamma_alpha;
  if( gamma_alpha > 1.0 + min_ene_val )
  {
    gamma_distribution_flg = gamma_alpha_larger_one;
  }
  else if( gamma_alpha + min_ene_val > 1.0 ) //gamma_alpha == 1.0 
  {
    gamma_distribution_flg = gamma_alpha_equal_one;
  }
  else if( gamma_alpha > 0.0 )
  {
    gamma_distribution_flg = gamma_alpha_smaller_one;
    alpha_cal += 1.0;
  }
  else
  {
    string class_name = "RandomNumberGenerator";
    string func_name  = "set_gamma_alpha(Real8 alpha)";

    ostringstream oss;
    oss << chi_freedom;
    string str_data = "Alpha of gamma distribution : " + oss.str();

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("Alpha of gamma distribution must be larger than 0.0.");
    err_com.push_back("Please check the alpha of gamma distribution.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  gamma_val2 = alpha_cal - third;
  gamma_val1 = third / sqrt(gamma_val2);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void RandomNumberGenerator::set_chi_freedom(Real8 freedom)
{
  chi_freedom      = freedom;
  chi_freedom_half = freedom * 0.5;

  if( chi_freedom > 1.0 + min_ene_val )
  {
    chi_alpha       = chi_freedom_half;
    chi_freedom_flg = chi_freedom_multi;
  }
  else if( chi_freedom + min_ene_val > 1.0 ) //chi_freedom == 1.0
  {
    chi_alpha       = 1.5;
    chi_freedom_flg = chi_freedom_one;
  }
  else
  {
    string class_name = "RandomNumberGenerator";
    string func_name  = "set_chi_freedom(Real8 freedom)";

    ostringstream oss;
    oss << chi_freedom;
    string str_data = "Freedom of chi-square distribution : " + oss.str();

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("Freedom of chi-square distribution must be larger than or equal to 1.0.");
    err_com.push_back("Please check the freedom of chi-square distribution.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  set_gamma_alpha(chi_alpha);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void RandomNumberGenerator::set_fix_random_val(Real8 random_val)
{
  fix_random_flg = fix_random_mode;
  fix_random_val = random_val;

  string class_name = "RandomNumberGenerator";
  string func_name  = "set_fix_random_val(Real8 random_val)";

  ostringstream oss;
  oss << random_val;
  string str_data = "Fixed raondom value  : " + oss.str();

  vector<string> err_com;
  err_com.push_back(str_data);

  if( dist_uni_min < fix_random_val && dist_uni_max > fix_random_val )
  {
    err_com.push_back("");
    err_com.push_back("Since set_fix_random_val function was called, the uniform random value is");
    err_com.push_back("not random but fixed the above value.");
    err_com.push_back("This member function is only used for debug or check.");
    err_com.push_back("This member function is only prepared for test the program without the");
    err_com.push_back("difference of random number generation.");
    err_com.push_back("");
    err_com.push_back("If you want to use actual random value, you must not use this member function.");

    err_obj.output_caution(class_name, func_name, err_com);
  }
  else
  {
    ostringstream oss01, oss02;
    oss01 << dist_uni_min;
    oss02 << dist_uni_max;
    string str_data01 = "Minimum random value : " + oss01.str();
    string str_data02 = "Maximum random value : " + oss01.str();
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);

    err_com.push_back("The fixed rundom value is smaller than minimum random value or");
    err_com.push_back("larger than maximum random value.");
    err_com.push_back("Please check the fixed random value.");
    err_com.push_back("");
    err_com.push_back("Note that the uniform random value is not random but fixed the above value");
    err_com.push_back("When set_fix_random_val function was called.");
    err_com.push_back("This member function is only used for debug or check.");
    err_com.push_back("This member function is only prepared for test the program without the");
    err_com.push_back("difference of random number generation.");
    err_com.push_back("");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  VectorClearer clr_obj;
  clr_obj.clear_vec_array1_str(err_com);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

frendy::Integer RandomNumberGenerator::get_seed()
{
  return seed;
}

Real8 RandomNumberGenerator::get_fix_random_val()
{
  return fix_random_val;
}
