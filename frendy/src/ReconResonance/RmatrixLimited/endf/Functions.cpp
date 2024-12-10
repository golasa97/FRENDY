#include "ReconResonance/RmatrixLimited/endf/Functions.h"

using namespace std;

namespace ENDF {

/*
inline double sign( const double x ) {

  return ( eq(x,0.0) ) ? 1.0 : x/fabs(x);

}
*/
/*
double BreitWigner( const double x, const double xc, const double g0, const double g1, const double g2 ) {

  return ( g1*g2/ ( (x-xc)*(x-xc) + 0.25*g0*g0 ) );

}
*/
/*
double WaveNumber( const double m1, const double m2, const double ecm ) {
// calcuate wave number in unit of 1/fm
// m1  : particle mass (amu)
// m2  : nucleus  mass (amu)
// ecm : energy in c.m. (eV)

  return sqrt( 2.0*m1*m2/(m1+m2)*amu *fabs(ecm) )/( hbar* c*1.e+15 );

}
*/

/*
double WaveNumber( const double m1, const double m2, const double elab ) {
// calcuate wave number in unit of 1/fm
// m1   : particle mass (amu)
// m2   : nucleus  mass (amu)
// elab : energy in lab. system (eV)

  return sqrt( 2.0*m1*amu*fabs(elab) ) *m2/(m1+m2) / ( hbar* c*1.e+15 );

}
*/


double CoulombParameter( const int z1, const int z2, const double m1, const double elab ) {
// dimensionless Coulomb parameter

  return z1*z2* alpha_fine_structure * sqrt( amu*m1/2./elab );

}

double sigma_cd( const int z1, const double m1, const int z2, const double m2, const double elab, const double mu ) {
// differential Coulomb scattering cross section the center-of-mass system for distinguishable particles (barns/sr)
// m1   : particle mass (amu)
// z1   : particle charge
// m2   : nucleus  mass (amu)
// z2   : nucleus charge
// elab : energy in lab. system (eV)
// mu   : cosine angle in center-of-mass frame

  double wk  = WaveNumber      (       m1,m2,elab );
  double eta = CoulombParameter( z1,z2,m1,   elab );

  // 1 barn = 100 fm^2

  return 0.01 * ( eta*eta/wk/wk/(1.-mu)/(1.-mu) );

}

double sigma_ci( const int z1, const double m1, const double s, const double elab, const double mu ) {
// differential Coulomb scattering cross section the center-of-mass system for identical particles (barns/sr)
// m1   : particle mass (amu)
// z1   : particle charge
// s    : particle spin
// elab : energy in lab. system (eV)
// mu   : cosine angle in center-of-mass frame

  double wk  = WaveNumber      (       m1,m1,elab );
  double eta = CoulombParameter( z1,z1,m1,   elab );

  int pm = int(2*s)%2==0 ? +1:-1;

  // 1 barn = 100 fm^2

  return 0.01 * ( 2*eta*eta/wk/wk/(1-mu*mu) )
              * ( (1+mu*mu)/(1-mu*mu) + pm/(2*s+1) * cos( eta*log((1+mu)/(1-mu)) ) );

}


double sigma_c( const int z1, const double m1, const int z2, const double m2, const double s, const double elab, const double mu ) {

  return ( z1==z2 && eq(m1,m2) ) ? sigma_ci( z1,m1,s,elab,mu ) : sigma_cd( z1,m1,z2,m2,elab,mu );

}

/*
double Penetration( const int l, const double rho ) {

  switch( l ) {

    case 0:  return rho;
    case 1:  return pow(rho,3)/( 1.0 + pow(rho,2) );
    case 2:  return pow(rho,5)/( 9.0 + 3.0*pow(rho,2) + pow(rho,4) );
    case 3:  return pow(rho,7)/( 225.0 + 45.0*pow(rho,2) + 6.0*pow(rho,4) + pow(rho,6) );

    default:
      cerr << " l should be less than 4 " << endl;  exit(1);

  }

}

double ShiftFactor( const int l, const double rho ) {

  switch( l ) {

    case 0:  return 0.0;
    case 1:  return -1.0/( 1.0 + pow(rho,2) );
    case 2:  return -1.0*( 18.0 + 3.0*pow(rho,2) )/( 9.0 + 3.0*pow(rho,2) + pow(rho,4) );
    case 3:  return -1.0*( 675.0 + 90.0*pow(rho,2)
                    + 6.0*pow(rho,4) )/( 225.0 + 45.0*pow(rho,2) + 6.0*pow(rho,4) + pow(rho,6) );
    default:
      cerr << " l should be less than 4 " << endl;  exit(1);

  }

}

double HardSpherePhaseShift( const int l, const double rho ) {

  switch( l ) {

    case 0:  return rho;
    case 1:  return rho - atan(rho);
    case 2:  return rho - atan( 3.0*rho/(3.0-rho*rho) );
    case 3:  return rho - atan( rho*(15.0-rho*rho)/(15.0-6.0*rho*rho) );

    default:
      cerr << " l should be less than 4 " << endl;  exit(1);

  }

}
*/


double P_Legendre( const int l, const double x ) {


  double xx = x;
  //cout << x << endl;
  //if( x == 1.0 ) cout << "kuni" << endl;
  if( x >= +1.0 ) xx =  1.0;
  if( x <= -1.0 ) xx = -1.0;

    cerr << "Function P_Legendre was faild :"
         << " l = " << l
         << " x = " << xx
         << endl;

    exit(1);

}


double Kalbach( const double ealab, const double epsb, const double f0, const double r, const double mu,
                const int ZA_Projectile, const int ZA_Target, const int ZA_Product,
                const double Mass_Projectile, const double Mass_Target, const double Mass_Product ) {

  // elab  : incident energy in Lab. (eV)
  // epsb  : outgoing energy in C.M. (eV)
  // f0    : total prob.
  // r     : pre-compound frac.
  // mu    : angle (cosine)
  // Mass_ : Mass in the neutron mass unit

  const double C1(4.0e-2), C2(1.8e-6), C3(6.7e-7);
  const double Et1(130.0), Et3(41.0);

  double M,m,Ia,Ib;

  switch( ZA_Projectile ) {

    case    0:  M = 1.0;  Ia =  0.00;  break;  // to be checked !
    case    1:  M = 1.0;  Ia =  0.00;  break;
    case 1001:  M = 1.0;  Ia =  0.00;  break;
    case 1002:  M = 1.0;  Ia =  2.22;  break;
    case 1003:  M = 1.0;  Ia =  8.48;  break;
    case 2003:  M = 1.0;  Ia =  7.72;  break;
    case 2004:  M = 0.0;  Ia = 28.30;  break;

    default:

      cerr << "In Finction Kalbach, invalid ZA_Projectile = " << ZA_Projectile << endl;
      exit(1);

  }

  switch( ZA_Product ) {

    case    1:  m = 0.5;  Ib =  0.00;  break;
    case 1001:  m = 1.0;  Ib =  0.00;  break;
    case 1002:  m = 1.0;  Ib =  2.22;  break;
    case 1003:  m = 1.0;  Ib =  8.48;  break;
    case 2003:  m = 1.0;  Ib =  7.72;  break;
    case 2004:  m = 2.0;  Ib = 28.30;  break;

    default:

      cerr << "In Finction Kalbach, invalid ZA_Product = " << ZA_Product << endl;
      exit(1);

  }


  double AA, AB, AC, ZA, ZB, ZC, NA, NB, NC;
  double Sa, Sb;

    AA = (double) ( ( ZA_Target                              ) % 1000 );
    AB = (double) ( ( ZA_Target + ZA_Projectile - ZA_Product ) % 1000 );
    AC = (double) ( ( ZA_Target + ZA_Projectile              ) % 1000 );

    ZA = (double) ( ( ZA_Target                              ) / 1000 );
    ZB = (double) ( ( ZA_Target + ZA_Projectile - ZA_Product ) / 1000 );
    ZC = (double) ( ( ZA_Target + ZA_Projectile              ) / 1000 );

    NA = AA - ZA;
    NB = AB - ZB;
    NC = AC - ZC;

      Sa = 15.68*(AC-AA) - 28.07*( pow(NC-ZC,2)/AC - pow(NA-ZA,2)/AA )
         - 18.56*( pow(AC,2.0/3.0) - pow(AA,2.0/3.0) ) 
         + 33.22*( pow(NC-ZC,2)/pow(AC,4.0/3.0) - pow(NA-ZA,2)/pow(AA,4.0/3.0) )
         - 0.717*( pow(ZC,2)/pow(AC,1.0/3.0) - pow(ZA,2)/pow(AA,1.0/3.0) )
         + 1.211*( pow(ZC,2)/AC - pow(ZA,2)/AA ) - Ia;

      Sb = 15.68*(AC-AB) - 28.07*( pow(NC-ZC,2)/AC - pow(NB-ZB,2)/AB )
         - 18.56*( pow(AC,2.0/3.0) - pow(AB,2.0/3.0) ) 
         + 33.22*( pow(NC-ZC,2)/pow(AC,4.0/3.0) - pow(NB-ZB,2)/pow(AB,4.0/3.0) )
         - 0.717*( pow(ZC,2)/pow(AC,1.0/3.0) - pow(ZB,2)/pow(AB,1.0/3.0) )
         + 1.211*( pow(ZC,2)/AC - pow(ZB,2)/AB ) - Ib;


  double ea, eb, R1, R3, X1, X3, a;

    ea = 1.0e-6 * ealab * ( Mass_Target/(Mass_Target+Mass_Projectile) ) + Sa;

      R1 = min( ea, Et1 );
      R3 = min( ea, Et3 );

      eb = epsb * 1.0e-6 + Sb;
      X1 = R1*eb/ea;
      X3 = R3*eb/ea;
      a  = C1*X1 + C2*pow(X1,3) + C3*M*m*pow(X3,4);


  // for incident particles

  if( ZA_Projectile > 0 ) return 0.5 * f0 * ( a * ( cosh(a*mu) + r*sinh(a*mu) ) /sinh(a) );

  // for incident photons

    a *= sqrt(0.5*1.e-6*ealab) * min( 4., max( 1., 9.3/sqrt(1.e-6*epsb) ) );

    //cerr << ealab << "  " << a << "  " <<  sinh(a) << endl;

    return 0.5 * f0 * ( (1.-r) + r*a*exp(a*mu)/sinh(a) );


/*
cout << R1 << endl;
cout << R3 << endl;
cout << eb << endl;
cout << X1 << endl;
cout << X3 << endl;
cout << a << endl;
cout << 0.5 * f0 * ( a * ( cosh(a*mu) + r*sinh(a*mu) ) /sinh(a) ) << endl;
*/


}




/*
double& Element( double* a, const int& n, const int& i, const int& j ) {

  return a[ n*i+j ];

}
*/

};
