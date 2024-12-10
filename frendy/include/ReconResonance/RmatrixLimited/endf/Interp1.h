#ifndef _Interp1
#define _Interp1

#include <iostream>
#include <cstdlib>
#include <cmath>
#include "ReconResonance/RmatrixLimited/numeric/Approx.h"
#include "ReconResonance/RmatrixLimited/numeric/Datum.h"
#include "ReconResonance/RmatrixLimited/endf/Numeric.h"

using namespace std;
//using namespace ENDF;

/* One-dimensional interpolation */

namespace ENDF {

double Interp1( const double& xa, const double& ya, const double& xb, const double& yb, const int& interpcode, const double& x );
double Interp1( const Numeric::Datum& a, const Numeric::Datum& b, const int& interpcode, const double& x );

bool Satisfied( const double& xa, const double& ya, const double& xb, const double& yb, const double& xc, const double& yc, const int& interpcode, const double& eps );

bool Satisfied( const Numeric::Datum& a, const Numeric::Datum& b, const Numeric::Datum& c, const int& interpcode, const double& eps );

double Integral1( const double& xa, const double& ya, const double& xb, const double& yb, const int& interpcode );
double Integral1( const Numeric::Datum& a, const Numeric::Datum& b, const int& interpcode );

double Average1( const double& xa, const double& ya, const double& xb, const double& yb, const int& interpcode );
double Average1( const Numeric::Datum& a, const Numeric::Datum& b, const int& interpcode );

};

#endif

