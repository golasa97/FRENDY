#ifndef _Interp_
#define _Interp_

#include "ReconResonance/RmatrixLimited/numeric/Datum.h"
#include "ReconResonance/RmatrixLimited/numeric/Approx.h"

namespace Numeric {

  inline double Lin_Lin( const double& xa, const double& ya, const double& xb, const double& yb, const double& xi ) {

    if( eq(xa,xb) ) return ya;

    return ya + (xi-xa)*(yb-ya)/(xb-xa);

  }

  inline double Log_Lin( const double& xa, const double& ya, const double& xb, const double& yb, const double& xi ) {

    if( xa <= 0.0 || xb <= 0.0 ) return Lin_Lin(xa,ya,xb,yb,xi);

    return ya + log(xi/xa)*(yb-ya)/log(xb/xa);

  }

  inline double Lin_Log( const double& xa, const double& ya, const double& xb, const double& yb, const double& xi ) {

    if( ya <= 0.0 || yb <= 0.0 ) return Lin_Lin(xa,ya,xb,yb,xi);

    return ya*exp( (xi-xa)*log(yb/ya)/(xb-xa) );

  }

  inline double Log_Log( const double& xa, const double& ya, const double& xb, const double& yb, const double& xi ) {

    if( xa <= 0.0 || xb <= 0.0 ) return Lin_Log(xa,ya,xb,yb,xi);
    if( ya <= 0.0 || yb <= 0.0 ) return Log_Lin(xa,ya,xb,yb,xi);
    if( xi <= 0.0 )              return Log_Lin(xa,ya,xb,yb,xi);

    return ya*exp( log(xi/xa)*log(yb/ya)/log(xb/xa) );

  }

  inline double Special( const double& xa, const double& ya, const double& xb, const double& yb, const double& xi,
                  const double& T ) {
    // special one-dimensional interpolation law, used for charged-particle cross sections only

    double B = log(xb*yb/xa/ya) / ( 1./sqrt(xa-T) - 1./sqrt(xb-T) );
    double A = exp(B/sqrt(xa-T)) * xa*ya;

    return A/xi * exp(-1.*B/sqrt(xi-T));

  }

  inline double Interp( const double& xa, const double& ya, const double& xb, const double& yb,
                 const int& interpcode, const double& x ) {

    if( eq(xa,xb) ) return ya;

    switch ( interpcode ) {

      case 1: return ya;
      case 2: return Lin_Lin( xa, ya, xb, yb, x );
      case 3: return Log_Lin( xa, ya, xb, yb, x );
      case 4: return Lin_Log( xa, ya, xb, yb, x );
      case 5: return Log_Log( xa, ya, xb, yb, x );

      default:

        cerr << "!! Interp : invalid interpolation scheme : " << interpcode << endl;  return 0.;

    }

  }

  inline double Interp( const Datum& a, const Datum& b, const int& interpcode, const double& x ) {

    return Interp( a.X(), a.Y(), b.X(), b.Y(), interpcode, x );

  }

  double I( const double& x1, const double& y1, const double& x2, const double& y2, const int& interpcode );

  inline double I( const Datum& a, const Datum& b, const int& interpcode ) {

    return I( a.X(), a.Y(), b.X(), b.Y(), interpcode );

  }


  inline bool Satisfied( const double& xa, const double& ya, const double& xb, const double& yb,
                  const double& xc, const double& yc, const int& interpcode, const double& eps ) {

    return le( fabs( Interp( xa,ya, xc,yc, interpcode, xb ) - yb ), eps * fabs( yb ) );

/*
    double I0 = I( xa,ya,xc,yc, interpcode );
    double I1 = I( xa,ya,xb,yb, interpcode )
              + I( xb,yb,xc,yc, interpcode );

    return eq( I0,I1, 1.e-6, 1.e-3 ) && le( fabs( Interp( xa,ya, xc,yc, interpcode, xb ) - yb ), eps * fabs( yb ) );
*/
  }

  inline bool Satisfied( const Datum& a, const Datum& b, const Datum& c, const int& interpcode, const double& eps ) {

    return Satisfied( a.X(), a.Y(), b.X(), b.Y(), c.X(), c.Y(), interpcode, eps );

    //return le( fabs( Interp( a, c, interpcode, b.X() ) - b.Y() ), eps * fabs( b.Y() ) );
/*
    double I0 = I( a,c, interpcode );
    double I1 = I( a,b, interpcode )
              + I( b,c, interpcode );

    return eq( I0,I1, 1.e-6, 1.e-1 ) && le( fabs( Interp( a, c, interpcode, b.X() ) - b.Y() ), eps * fabs( b.Y() ) );
*/
  }

};

#endif
