#ifndef DIGIT_ADJUSTER_H
#define DIGIT_ADJUSTER_H

//#include <stdio.h>
//#include <stdlib.h>

#include "ErrorManager.hpp"

namespace frendy
{
  class DigitAdjuster
  {
    private:
      char *char_data;
      char *mantissa;

      frendy::ErrorManager err_obj;

    public:
      //constructor
      DigitAdjuster(void);

      //destructor
      virtual ~DigitAdjuster(void);

      int get_precision_no(Real& real_val, int width);

      Integer get_digit_number(Real8 real_value);
      //Integer get_digit_number(Real  real_value);
      Integer get_digit_number(Integer int_value);

      Real8 get_adjusted_value(Real8 real_data, Integer adjust_digit, Real8 adjust_amount);

      Real8 get_truncation_value(Real8 real_data);
      Real8 get_truncation_value(Real8 real_data, int truncation_digit);

      Real  adjust_min_value(Real real_data);

      //If fabs(a_val) < 1.0E-30, a_val considerd as 0.0
      void adjust_data( vector<vector<vector<vector<vector<vector<Real> > > > > >& real_vec );
      void adjust_data( vector<vector<vector<vector<vector<Real> > > > >& real_vec );
      void adjust_data( vector<vector<vector<vector<Real> > > >& real_vec );
      void adjust_data( vector<vector<vector<Real> > >& real_vec );
      void adjust_data( vector<vector<Real> >& real_vec );
      void adjust_data( vector<Real>& real_vec );
      void adjust_data( Real& real_val );
  };
}

#endif // DIGIT_ADJUSTER_H
