#include "ReconResonance/RmatrixLimited/endf/Interp1.h"
#include "ReconResonance/RmatrixLimited/numeric/Interp.h"

#include <iostream>
#include <cstdlib>
#include <cmath>
#include "ReconResonance/RmatrixLimited/numeric/Approx.h"

/* __________ One-dimensional interpolation __________ */



namespace ENDF {

double Interp1( const double& xa, const double& ya, const double& xb, const double& yb, const int& interpcode, const double& x ) {

  return Numeric::Interp( xa,ya,xb,yb, interpcode, x );

}

double Interp1( const Numeric::Datum& a, const Numeric::Datum& b, const int& interpcode, const double& x ) {

  return Numeric::Interp( a,b, interpcode, x );

}



bool Satisfied( const double& xa, const double& ya, const double& xb, const double& yb, const double& xc, const double& yc, const int& interpcode, const double& eps ) {

  return Numeric::Satisfied( xa,ya,xb,yb,xc,yc, interpcode, eps );

}

bool Satisfied( const Numeric::Datum& a, const Numeric::Datum& b, const Numeric::Datum& c, const int& interpcode, const double& eps ) {

  return Numeric::Satisfied( a,b,c, interpcode, eps );

}






/* Integral */

double Integral1( const double& x1, const double& y1, const double& x2, const double& y2, const int& interpcode ) {

  return Numeric::I( x1,y1,x2,y2, interpcode );

}

double Integral1( const Numeric::Datum& a, const Numeric::Datum& b, const int& interpcode ) {

  return Numeric::I( a,b, interpcode );

}


/* Average */

double Average1( const double& x1, const double& y1, const double& x2, const double& y2, const int& interpcode ) {

  return Numeric::eq(x1,x2) ? 0.0 : Integral1(x1,y1,x2,y2,interpcode)/(x2-x1);

}

double Average1( const Numeric::Datum& a, const Numeric::Datum& b, const int& interpcode ) {

  return Numeric::eq(a.X(),b.X()) ? 0.0 : Integral1(a,b,interpcode)/(b.X()-a.X());

}

};
