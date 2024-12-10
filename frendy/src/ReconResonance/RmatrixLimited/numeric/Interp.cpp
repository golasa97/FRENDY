#include "ReconResonance/RmatrixLimited/numeric/Interp.h"

// integral
double Numeric::I( const double& x1, const double& y1, const double& x2, const double& y2, const int& interpcode ) {

  if( eq(x1,x2) ) return 0.0;

  if( x1 > x2 ) {

    cerr << "!! Integral1 -> x2 should be larger than x1" << endl;
    cerr << "x1 = " << x1 << endl;
    cerr << "x2 = " << x2 << endl;

    return 0.0;

  }

  switch( interpcode ) {

    double a,b,z;

    case 1:

      return y1 * ( x2-x1 );

    case 2:

      b = (y2-y1)/(x2-x1);  a = y1-b*x1;

      return (x2-x1)*( a+0.5*b*(x2+x1) );

    case 3:

      z = (x2-x1)/x1;  b = (y2-y1)/log(x2/x1);

      return ( fabs(z) <= 0.15 ) ? (x2-x1)*y1 + 0.5*b*x1*z*z * ( 1.+z*( -1./3.+z*(1./6.-0.1*z) ) )
                                 : (x2-x1)*y1 + b*x1 * ( 1.+x2/x1*( log(x2/x1)-1. ) );

    case 4:

      b = log(y2/y1)/(x2-x1);  a = log(y1) -b*x1;  z = (x2-x1)*b;

      return ( fabs(z) <= 0.1 ) ? exp(a+b*x1)*(x2-x1) * ( 1.+z*( 0.5+1./6.*z ) )
                                : 1./b * exp(a+b*x1) * ( exp(z)-1. );

    case 5:

      a = log(x2/x1);  b = log(y2/y1)/a;  z = (b+1.) * a;

      return ( fabs(z) <= 0.1 ) ? y1*x1*a * ( 1.+z*( 0.5+1./6.*z ) )
                                : 1./(b+1.) * y1*x1 * ( pow(x2/x1,b+1.) -1. );

    default:

      cerr << "!! Integrate -> not allowed interpcode = " << interpcode << " (changed to interpcode=2)" << endl;

      return I( x1,y1,x2,y2, 2 );

  }

  return 0.0;

}

