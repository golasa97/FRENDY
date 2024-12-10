#ifndef RANDOM_NUMBER_GENERATOR_H
#define RANDOM_NUMBER_GENERATOR_H

#include <time.h>
#include <boost/random.hpp>

#include "Config/FrendyTypes.hpp"
#include "CommonUtils/ErrorManager.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class RandomNumberGenerator
  {
      //The algorithm used in this class is referred to
      //Tetsuaki Yotsuji, "Keisankisimyure-syonnotameno kakuritsubunpuransuuseiseihou
      //(The method of a random number of probabilistic distribution generation
      // for computational simulation)," Pureadesusyuppan, 2010 (in Japanese)

    private:
      static const Integer seed_ori                = 0;
      static const Integer gamma_alpha_larger_one  = 0;
      static const Integer gamma_alpha_equal_one   = 1;
      static const Integer gamma_alpha_smaller_one = 2;
      static const Integer chi_freedom_one         = 1;
      static const Integer chi_freedom_multi       = 2;
      static const Real8   dist_uni_min; // = 0.0;
      static const Real8   dist_uni_max; // = 1.0;

      static const unsigned long int mcg_cycle       = 9223372036854775807;
      static const unsigned long int mcg_multiplier  = 9219741426499971445;
      static const unsigned long int mcg_increment   = 1;

#ifdef MERSENNE_MODE
      boost::mt19937 gen_uni;
#endif

      Real8 coef_wigner_distr; //=2.0/sqrt(M_PI);

#ifdef DEBUG_MODE
  public:
#endif
      Integer seed;
      Integer normal_distribution_flg;
      Integer gamma_distribution_flg;
      Integer chi_freedom_flg;

      Real8   third;
      Real8   normal_rand1, normal_rand2;
      Real8   gamma_alpha, gamma_alpha_inv, gamma_val1, gamma_val2;
      Real8   chi_freedom, chi_freedom_half, chi_alpha, chi_beta;

      unsigned long int rand_pre_mcg;

    protected:
      static const Integer random_mode             = 0;
      static const Integer fix_random_mode         = 1;

      frendy::ErrorManager err_obj;

      Integer fix_random_flg;
      Real8   fix_random_val;

      void initialization();
      void clear();

    public:
      //constructor
      RandomNumberGenerator(void);

      //destructor
      virtual ~RandomNumberGenerator(void);

      //For uniform distribution
      Real8 uniform_distribution();
      Real8 uniform_distribution_boost(); //Using Mersenne Twister
      Real8 uniform_distribution_mcg();   //Using mixed congruential generator

      //For normal distribution
      Real8 normal_distribution(Real8& mu, Real8& sigma);
      Real8 standard_normal_distribution();

      //For exponential distribution
      Real8 exponential_distribution(Real8& theta);

      //For gamma distribution
      Real8 gamma_distribution(Real8& alpha, Real8& beta);
      Real8 gamma_distribution(Real8& beta);

      //For chi-square distribution
      Real8 chi_square_distribution(Real8& freedom);
      Real8 chi_square_distribution();

      //For Cauchy (Breit Wigner) distribution
      Real8 cauchy_distribution(Real8& mu, Real8& theta);
      Real8 standard_cauchy_distribution();
      Real8 cauchy_distribution_abs(Real8& mu, Real8& theta);
      Real8 standard_cauchy_distribution_abs();

      //For Wigner distribution (Using U3R formula)
      Real8 wigner_distribution();

      void set_seed(Integer seed_val);
      void set_seed_time();
      void set_gamma_alpha(Real8 alpha);
      void set_chi_freedom(Real8 freedom);
      void set_fix_random_val(Real8 random_val);

      Integer get_seed();
      Real8   get_fix_random_val();
  };
}

#endif // RANDOM_NUMBER_GENERATOR_H
