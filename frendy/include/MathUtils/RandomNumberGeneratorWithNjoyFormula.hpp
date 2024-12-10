#ifndef RANDOM_NUMBER_GENERATOR_WITH_NJOY_FORMULA_H
#define RANDOM_NUMBER_GENERATOR_WITH_NJOY_FORMULA_H

#include "MathUtils/RandomNumberGenerator.hpp"

namespace frendy
{
  class RandomNumberGeneratorWithNjoyFormula : public RandomNumberGenerator
  {
    //The algorithm used in this class is similar to PURR in NJOY99.
    //Note that the generation of the uniform random number is different to PURR. 

    private:
      static const int chi_sq_max_freedom =  4;
      static const int chi_sq_data_no     = 20;

#ifdef DEBUG_MODE
  public:
#endif
      vector<vector<Real8> > chi_sq_vec;

      Integer chi_freedom_no;

      virtual void clear();

    public:
      //constructor
      RandomNumberGeneratorWithNjoyFormula(void);

      //destructor
      virtual ~RandomNumberGeneratorWithNjoyFormula(void);

      //For chi-square distribution
      virtual Real8 chi_square_distribution(Real8& freedom);
      virtual Real8 chi_square_distribution();

      virtual void set_chi_freedom(Real8 freedom);
  };
}

#endif // RANDOM_NUMBER_GENERATOR_WITH_NJOY_FORMULA_H
