#include "ReconResonance/RmatrixLimited/numeric/Legendre.h"
#include "ReconResonance/RmatrixLimited/numeric/Coupling.h"
#include <cstdlib>
//#include <gsl/gsl_sf_legendre.h>
//#include <gsl/gsl_sf_erf.h>

namespace Numeric {


/*

Taken from POD code

C     THIS FUNCTION CALCULATES THE LEGENDLE FUNCTIONS.
C     THE LEGENDLRE FUNCTION IS CALCULATED WITH THE FORMULAS
C     (6.8.7), (6.8.8), AND (6.8.9) OF REF.1).
C
C     REFERENCE
C     1)W.H.PRESS ET AL., "NUMERICAL RECIPES IN FORTRAN, 2-ND
C       EDITION", CAMBRIDGE, NEW YORK (1992).
C
C     INPUT
C     L     : ORBITAL ANGULAR MOMENTUM QUANTUM NUMBER
C     MXX   : MAGNETIC QUANTUM NUMBER
C     X     : ANGLE EXPRESSD IN COSINE (-1.GE.X.LE.+1)
C
C     OUTPUT
C     PLM   : THE LEGENGRE FUNCTION
*/
double Legendre_PLM( const int& L, const int& MXX, const double& X ) {

  //return gsl_sf_legendre_Plm( L,MXX,X );

      double PLM=0.0;

      double MBAR = MXX;

      if(MXX<0) MBAR=-MXX;
      if(MBAR<0 || MBAR>L || fabs(X)>1.0 ) return PLM;


      double PMM = 1.0, X2,FAC2;

      if( MBAR>0 ) {

        X2=sqrt((1.-X)*(1.+X));
        FAC2=1.;

        for( int I=1; I<=MBAR; I++ ) {

          PMM=-PMM*FAC2*X2;
          FAC2=FAC2+2.0;

        }

      }



      if( L==MBAR ) {

        PLM=PMM;

      }

      else {

        double AMBAR=double(MBAR);
        double PMMP1=X*(2.0*AMBAR+1.0)*PMM;

        if( L == MBAR+1 ) {

          PLM=PMMP1;

        }

        else {

          double ALL,PLL;
          ALL = 0.0;
          PLL = 0.0;

          for( int LL=MBAR+2; LL<=L; LL++ ) {

            ALL=double(LL);
            PLL=(X*(2.0*ALL-1.0)*PMMP1-(ALL+AMBAR-1.0)*PMM)/(ALL-AMBAR);
            PMM=PMMP1;
            PMMP1=PLL;

          }

          PLM=PLL;

        }

      }

      if(MXX<0) PLM= pow(-1.0,MBAR) *FC(L-MBAR)/FC(L+MBAR)*PLM;

  return PLM;

}



double Legendre_PL( const int& L, const double& X ) {

  return Legendre_PLM(L,0,X);

}


}
