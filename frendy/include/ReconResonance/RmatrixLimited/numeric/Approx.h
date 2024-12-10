#ifndef _Approx_
#define _Approx_

#include <cstdlib>
#include <cmath>
#include <complex>
#include <algorithm>

//#include <TObject.h>
//#define pm(l) ( (l)%2 == 0 ? 1 : -1 )

#define eps_default 1.e-13  // 2023.4.1 by S.K.
//#define eps_default 1.e-15
#define zero_default 1.e-38

using namespace std;

/**
* @namespace Numeric
* @brief The namespace includes a number of classes for the numerical calculation
*/
namespace Numeric {
/*
bool eq( const double a, const double b, const double eps =1.e-10 );
bool ne( const double a, const double b );
bool lt( const double a, const double b );
bool gt( const double a, const double b );
bool le( const double a, const double b );
bool ge( const double a, const double b );
*/


inline double max( const double& a, const double& b ) {

  return ( a > b ) ? a : b;

}

inline bool eq( const double& a, const double& b, const double eps = eps_default, const double zero = zero_default ) {

  if( fabs(a-b) < zero ) return true;

  return ( fabs(a-b)/max(fabs(a),fabs(b)) < eps );

}

inline bool ne( const double& a, const double& b, const double eps = eps_default, const double zero = zero_default ) {

  return !eq(a,b,eps,zero);

}

inline bool lt( const double& a, const double& b, const double eps = eps_default, const double zero = zero_default ) { return a<b && !eq(a,b,eps,zero); }
inline bool gt( const double& a, const double& b, const double eps = eps_default, const double zero = zero_default ) { return a>b && !eq(a,b,eps,zero); }

inline bool le( const double& a, const double& b, const double eps = eps_default, const double zero = zero_default ) { return eq(a,b,eps,zero) || lt(a,b,eps,zero); }
inline bool ge( const double& a, const double& b, const double eps = eps_default, const double zero = zero_default ) { return eq(a,b,eps,zero) || gt(a,b,eps,zero); }

inline bool eq( const complex<double>& a, const complex<double>& b, const double eps = eps_default, const double zero = zero_default ) {

  return eq( real(a), real(b), zero, eps ) && eq( imag(a), imag(b), eps,zero );

}

};

#endif
