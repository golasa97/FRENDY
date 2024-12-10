#ifndef _Functions
#define _Functions

#include <iostream>
#include <cstdlib>
#include <cmath>
//#include "Kinematics.h"
#include "ReconResonance/RmatrixLimited/endf/Numeric.h"
#include "ReconResonance/RmatrixLimited/numeric/Constant.h"
#include "ReconResonance/RmatrixLimited/numeric/Approx.h"

using namespace Constant;
using namespace Numeric;

namespace ENDF {

//inline double sign( const double x );


inline double sign( const double& x ) {

  return ( eq(x,0.0) ) ? 1.0 : x/fabs(x);

}

inline double BreitWigner( const double& x, const double& xc, const double& g0, const double& g1, const double& g2 ) {

  return ( g1*g2/ ( (x-xc)*(x-xc) + 0.25*g0*g0 ) );

}

inline double WaveNumber( const double& m1, const double& m2, const double& elab ) {
// calcuate wave number in unit of 1/fm
// m1   : particle mass (amu)
// m2   : nucleus  mass (amu)
// elab : energy in lab. system (eV)

  //return sqrt( 2.0*m1*amu*fabs(elab) ) *m2/(m1+m2) / ( hbar* c_speed_of_light *1.e+15 );

  return sqrt( 2.0*m1*amu*fabs(elab) ) *m2/ ( (m1+m2) * ( hbar* c_speed_of_light *1.e+15 ) );

}

//double BreitWigner( const double, const double, const double, const double, const double );
//double WaveNumber( const double m1, const double m2, const double ecm  );
//double WaveNumber( const double m1, const double m2, const double elab );

double CoulombParameter( const int z1, const int z2, const double m1, const double elab );
double sigma_cd( const int z1, const double m1, const int z2, const double m2, const double elab, const double mu );
double sigma_ci( const int z1, const double m1, const double s, const double elab, const double mu );
double sigma_c ( const int z1, const double m1, const int z2, const double m2, const double s, const double elab, const double mu );
//double sigma_c ( const Kinematics* system, const double s, const double mu );


inline double Penetration( const int l, const double rho ) {

  if( l == 0 ) return rho;

  double rho2 = rho*rho;
  double rho3 = rho*rho2;

  switch( l ) {

    case 1:  return rho3/( 1.0 + rho2 );
    case 2:  return rho2*rho3/( 9.0 + 3.0*rho2 + rho2*rho2 );
    case 3:  return rho3*rho3*rho/( 225.0 + 45.0*rho2 + 6.0*rho2*rho2 + rho3*rho3 );
    case 4:  return rho3*rho3*rho3/( 11025.0 + 1575.0*rho2 + 135.0*rho2*rho2 + 10.0*rho3*rho3 + rho3*rho3*rho2 );

    default:
      cerr << " l should be less than 5 " << endl;  exit(1);

  }

/*
  switch( l ) {

    case 0:  return rho;
    case 1:  return pow(rho,3.)/( 1.0 + pow(rho,2.) );
    case 2:  return pow(rho,5.)/( 9.0 + 3.0*pow(rho,2.) + pow(rho,4.) );
    case 3:  return pow(rho,7.)/( 225.0 + 45.0*pow(rho,2.) + 6.0*pow(rho,4.) + pow(rho,6.) );

    default:
      cerr << " l should be less than 4 " << endl;  exit(1);

  }
*/

}

inline double ShiftFactor( const int l, const double rho ) {

  if( l == 0 ) return 0.0;

  double rho2 = rho*rho;

  switch( l ) {

    case 1:  return -1.0/( 1.0 + rho2 );
    case 2:  return -1.0*( 18.0 + 3.0*rho2 )/( 9.0 + 3.0*rho2 + rho2*rho2 );
    case 3:  return -1.0*( 675.0 + 90.0*rho2
                    + 6.0*rho2*rho2 )/( 225.0 + 45.0*rho2 + 6.0*rho2*rho2 + rho2*rho2*rho2 );
    case 4:  return -1.0*( 44100.0 + 4725.0*rho2 + 270*rho2*rho2 + 10.0*rho2*rho2*rho2 )
                    /( 11025.0 + 1575.0*rho2 + 135.0*rho2*rho2 + 10.0*rho2*rho2*rho2 + rho2*rho2*rho2*rho2 );

    default:
      cerr << " l should be less than 5 " << endl;  exit(1);

  }

/*
  switch( l ) {

    case 0:  return 0.0;
    case 1:  return -1.0/( 1.0 + pow(rho,2.) );
    case 2:  return -1.0*( 18.0 + 3.0*pow(rho,2.) )/( 9.0 + 3.0*pow(rho,2.) + pow(rho,4.) );
    case 3:  return -1.0*( 675.0 + 90.0*pow(rho,2.)
                    + 6.0*pow(rho,4.) )/( 225.0 + 45.0*pow(rho,2.) + 6.0*pow(rho,4.) + pow(rho,6.) );

    default:
      cerr << " l should be less than 4 " << endl;  exit(1);

  }
*/

}

inline double HardSpherePhaseShift( const int l, const double rho ) {

  switch( l ) {

    case 0:  return rho;
    case 1:  return rho - atan(rho);
    case 2:  return rho - atan( 3.0*rho/(3.0-rho*rho) );
    case 3:  return rho - atan( rho*(15.0-rho*rho)/(15.0-6.0*rho*rho) );
    case 4:  return rho - atan( rho*(105.0-10.0*rho*rho)/(105.0-45.0*rho*rho +rho*rho*rho*rho) );

    default:
      cerr << " l should be less than 5 " << endl;  exit(1);

  }

}


/*
double Penetration( const int, const double );
double ShiftFactor( const int, const double );
double HardSpherePhaseShift( const int, const double );
*/

double P_Legendre( const int, const double );

double Kalbach( const double, const double, const double, const double, const double,
                const int, const int, const int,
                const double, const double, const double );

};


#endif
