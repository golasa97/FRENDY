#include "ReconResonance/RmatrixLimited/numeric/Coupling.h"
//#include <gsl/gsl_errno.h>
//#include <gsl/gsl_sf_coupling.h>

//#define pm(l) ( (l)%2 == 0 ? 1 : -1 )

//using namespace std;

namespace Numeric {

/*
bool is_int( const double x, const double eps =1.e-10 ) {

  //return ( x - (int) x == 0.0 );

  return eq( x, round(x), eps );

}
*/
/* _____ 3-j coupling coefficient _____ */
/*
double W3j( double j1, double j2, double j3, double m1, double m2, double m3 ) {


  gsl_sf_result result;

  int status =
    gsl_sf_coupling_3j_e ( (int) 2*j1, (int) 2*j2, (int) 2*j3,
                           (int) 2*m1, (int) 2*m2, (int) 2*m3, &result );


  if( status ) {

    cerr << "!! W3j : " << gsl_strerror( status ) << endl;

    exit(1);

  }

  return result.val;

}
*/


/* _____ 6-j coupling coefficient _____ */
/*
double W6j( double j1, double j2, double j3, double j4, double j5, double j6 ) {


  gsl_sf_result result;

  int status =
    gsl_sf_coupling_6j_e ( (int) 2*j1, (int) 2*j2, (int) 2*j3,
                           (int) 2*j4, (int) 2*j5, (int) 2*j6, &result );


  if( status ) {

    cerr << "!! W6j : " << gsl_strerror( status ) << endl;

    exit(1);

  }

  return result.val;

}
*/


/* _____ Clebsch-Gordan Coefficient _____ */
/*
double Cleb( double j1, double j2, double j3, double m1, double m2, double m3 ) {

  if( ! is_int(j1-j2+m3) ) { cerr << "!! Cleb : Input error " << endl; exit(1); }

  return pm( (int) (j1-j2+m3) ) * sqrt( 2*j3 + 1.0 ) * W3j( j1, j2, j3, m1, m2, -1.0*m3 );

}
*/


/* _____ Racah Coefficient _____ */
/*
double Racah( double j1, double j2, double j5, double j4, double j3, double j6 ) {

  if( ! is_int(j1+j2+j4+j5) ) { cerr << "!! Cleb : Input error " << endl; exit(1); }

  return pm( (int) (j1+j2+j4+j5) ) * W6j(j1,j2,j3,j4,j5,j6);

}
*/





// calculate factorial
double FC( const int& n ) {

  double val = 1.;

    for( int i=1; i<=n; i++ ) val *= i;

  return val;

}

// calculate square factorial
double SFC( const int& n ) {

  double val = 1.;

    for( int i=1; i<=n; i++ ) val *= sqrt(i);

  return val;

}


/*

Taken from POD code

C     THIS SUBROUTINE CALCULATES THE CLEBSCH-GORDAN COEFFICIENTS.
C     THE CLEBSCH GOLDAN COEFFICIENTS ARE OBTAINED BY USING THE
C     FORMULA (27.9.1) OF ABRAMOWITZ.
C
C     REFERENCES
C     1) M.ABRAMOWITZ AND I.A.STEGUN, "HANDBOOK OF MATHEMATICAL
C     FUNCTIONS", DOVER, NEW YORK (1972).
C     2) M.E.ROSE, "ELEMENTARY THEORY OF ANGULAR MOMENTUM",
C     JOHN WILEY, NEW YORK (1957).
*/
double Cleb_POD( const double& J1, const double& M1,
                 const double& J2, const double& M2,
                 const double& J3, const double& M3 ) {

      double CLEB=0.0;

      if( J1 < -1.e-10 || J2 < -1.e-10 || J3 < -1.e-10 ) return 0.0;
      if( fabs(M3-M1-M2) > 1.e-10 ) return 0.0;


      double SUMJ=J1+J2+J3;

      if( fmod(SUMJ,1.0) > 1.e-10 ) return 0.0;

      if( J3 < fabs(J1-J2) || J3 > J1+J2 ) return 0.0;

      if( fabs(M1) > J1 || fabs(M2) > J2 || fabs(M3) > J3 ) return 0.0;

      if( fmod(J1-M1,1.0) > 1.e-10 ) return 0.0;
      if( fmod(J2-M2,1.0) > 1.e-10 ) return 0.0;
      if( fmod(J3-M3,1.0) > 1.e-10 ) return 0.0;

      if( fabs(M1) < 1.e-10 && fabs(M2) < 1.e-10 && SUMJ < 1.e-10 ) return 1.0;

      if( fabs(M1) < 1.e-10 && fabs(M2) < 1.e-10 && fmod(SUMJ,2.0) > 1.e-10 ) return 0.0;


      double AKMIN=max( max(-J3+J2-M1,-J3+J1+M2), 0.0 );
      double AKMAX=min( min(J1+J2-J3,J1-M1),J2+M2 );

      int KMIN =int(AKMIN+1.e-5);
      int KMAX =int(AKMAX+1.e-5);

      if(KMIN>KMAX) return 0.0;


      int I1,I2,I3,I5;
      double H,C1,C2,C3,C4,C5,CX;

      H =J1+J2-J3+1.e-5;
      I1=int(H);
      C1=SFC(I1);
      H =J3+J1-J2+1.e-5;
      I2=int(H);
      C2=SFC(I2);
      H =J3+J2-J1+1.e-5;
      I3=int(H);
      C3=SFC(I3);
      C4=sqrt(2.*J3+1.);
      H =SUMJ+1.+1.e-5;
      I5=int(H);
      C5=SFC(I5);
      CX=(C1/C5)*C2*C3*C4;


      int IA,IB,IC,ID,IE,IF;
      double CA,CB,CC,CD,CE,CF;

      H =J1+M1+1.e-5;
      IA=int(H);
      CA=SFC(IA);
      H =J1-M1+1.e-5;
      IB=int(H);
      CB=SFC(IB);
      H =J2+M2+1.e-5;
      IC=int(H);
      CC=SFC(IC);
      H =J2-M2+1.e-5;
      ID=int(H);
      CD=SFC(ID);
      H =J3+M3+1.e-5;
      IE=int(H);
      CE=SFC(IE);
      H =J3-M3+1.e-5;
      IF=int(H);
      CF=SFC(IF);


      int K1,K2,K3,K4,K5;
      double S,AK,D0,D1,D2,D3,D4,D5,X;

      S=0.0;

      for( int K=KMIN; K<=KMAX; K++ ) {

        AK=double(K);
        D0=FC(K);
        H =J1+J2-J3-AK+1.e-5;
        K1=int(H);
        D1=FC(K1);
        H =J1-M1-AK+1.e-5;
        K2=int(H);
        D2=FC(K2);
        H =J2+M2-AK+1.e-5;
        K3=int(H);
        D3=FC(K3);
        H =J3-J2+M1+AK+1.e-5;
        K4=int(H);
        D4=FC(K4);
        H =J3-J1-M2+AK+1.e-5;
        K5=int(H);
        D5=FC(K5);
        X=(CA/D0)*(CB/D1)*(CC/D2)*(CD/D3)*(CE/D4)*(CF/D5);
        S=S+pow(-1.0,K)*X;

      }

      CLEB=CX*S;


  return CLEB;

}


/*

Taken from POD code

C     THIS FUNCTION CALCULATES THE W COEFFICIENT OF RACAH WITH
C     THE FORMULAS (6.2.13) AND (6.3.7) OF EDMONDS.
C
C     REFERENCE
C     1) A.R.EDMONDS, "ANGULAR MOMENTUM IN QUANTUM MECHANICS",
C     PRINCETON, NEW JERSEY (1957).
*/
double Racah_POD( const double& A, const double& B, const double& C, const double& D, const double& E, const double& F ) {

      double RACAH=0.0;

      if( A<0. || B<0. || C<0. ) return 0.0;
      if( D<0. || E<0. || F<0. ) return 0.0;
      if( A+B-E<0. || A-B+E<0. || -A+B+E<0. ) return 0.0;
      if( A+C-F<0. || A-C+F<0. || -A+C+F<0. ) return 0.0;
      if( D+B-F<0. || D-B+F<0. || -D+B+F<0. ) return 0.0;
      if( D+C-E<0. || D-C+E<0. || -D+C+E<0. ) return 0.0;
      if( fmod(A+B-E,1.0) > 1.e-10 ) return 0.0;
      if( fmod(A+C-F,1.0) > 1.e-10 ) return 0.0;
      if( fmod(D+B-F,1.0) > 1.e-10 ) return 0.0;
      if( fmod(D+C-E,1.0) > 1.e-10 ) return 0.0;

      int IABE1,IABE2,IABE3,IABE4;
      double DABE;

      IABE1=int( A+B-E+1.e-10);
      IABE2=int( A-B+E+1.e-10);
      IABE3=int(-A+B+E+1.e-10);
      IABE4=int( A+B+E+1.e-10)+1;
      DABE =log(SFC(IABE1))+log(SFC(IABE2))+log(SFC(IABE3))-log(SFC(IABE4));
      DABE =exp(DABE);

      int IACF1,IACF2,IACF3,IACF4;
      double DACF;

      IACF1=int( A+C-F+1.e-10);
      IACF2=int( A-C+F+1.e-10);
      IACF3=int(-A+C+F+1.e-10);
      IACF4=int( A+C+F+1.e-10)+1;
      DACF =log(SFC(IACF1))+log(SFC(IACF2))+log(SFC(IACF3))-log(SFC(IACF4));
      DACF =exp(DACF);


      int IDBF1,IDBF2,IDBF3,IDBF4;
      double DDBF;

      IDBF1=int( D+B-F+1.e-10);
      IDBF2=int( D-B+F+1.e-10);
      IDBF3=int(-D+B+F+1.e-10);
      IDBF4=int( D+B+F+1.e-10)+1;
      DDBF =log(SFC(IDBF1))+log(SFC(IDBF2))+log(SFC(IDBF3))-log(SFC(IDBF4));
      DDBF =exp(DDBF);

      int IDCE1,IDCE2,IDCE3,IDCE4;
      double DDCE;

      IDCE1=int( D+C-E+1.e-10);
      IDCE2=int( D-C+E+1.e-10);
      IDCE3=int(-D+C+E+1.e-10);
      IDCE4=int( D+C+E+1.e-10)+1;
      DDCE =log(SFC(IDCE1))+log(SFC(IDCE2))+log(SFC(IDCE3))-log(SFC(IDCE4));
      DDCE =exp(DDCE);


      int I1,I2,I3,I4,IA,IB,IC;

      I1=int(A+B+E+1.e-10);
      I2=int(A+C+F+1.e-10);
      I3=int(D+B+F+1.e-10);
      I4=int(D+C+E+1.e-10);
      IA=int(A+B+C+D+1.e-10);
      IB=int(B+E+C+F+1.e-10);
      IC=int(E+A+F+D+1.e-10);


      int KMIN,KMAX;

      KMIN = max( max( max(I1,I2), I3), I4 );
      KMAX = min( min(IA,IB), IC );
      if( KMAX < KMIN ) return 0.0;

      for( int K=KMIN; K<=KMAX; K++ ) {

        RACAH=RACAH +pow(-1.0,K)
          *(FC(K+1)/FC(K-I1))/FC(K-I2)/FC(K-I3)
          *(DABE/FC(K-I4))*(DACF/FC(IA-K))
          *(DDBF/FC(IB-K))*(DDCE/FC(IC-K));

      }

      double EE;
      int IE;

      EE=A+B+C+D+1.e-10;
      IE=-int(EE);
      RACAH=pow(-1.0,IE)*RACAH;


  return RACAH;

}


}
