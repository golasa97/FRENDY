#ifndef INCLUDE_Coupling_H
#define INCLUDE_Coupling_H

#include <iostream>
#include <cstdlib>
#include <cmath>
#include "ReconResonance/RmatrixLimited/numeric/Approx.h"

/* coupling constants */

namespace Numeric {

//double W3j( double j1, double j2, double j3, double m1, double m2, double m3 );
//double W6j( double j1, double j2, double j3, double j4, double j5, double j6 );

//double Cleb ( double j1, double j2, double j3, double m1, double m2, double m3 );
//double Racah( double j1, double j2, double j5, double j4, double j3, double j6 );

double FC ( const int& n );
double SFC( const int& n );

double Cleb_POD( const double& J1, const double& M1, const double& J2, const double& M2, const double& J3, const double& M3 );
double Racah_POD( const double& A, const double& B, const double& C, const double& D, const double& E, const double& F );

inline double C( const double j1, const double j2, const double m1, const double m2, const double j3, const double m3 ) {

  return Cleb_POD ( j1,m1,j2,m2,j3,m3 );  // < j1,j2,m1,m2 | j3,m3 > with POD

  //return Cleb (j1,j2,j3,m1,m2,m3);  // < j1,j2,m1,m2 | j3,m3 > with GSL

}

inline double W( const double j1, const double j2, const double j5, const double j4, const double j3, const double j6 ) {

  return Racah_POD(j1,j2,j5,j4,j3,j6);   // Racah's cefficient with POD

  //return Racah(j1,j2,j5,j4,j3,j6);  // Racah's cefficient with GSL

}

inline double H( const int l1, const double J1, const int l2, const double J2 ) {

  return sqrt( (2.*l1+1.)*(2.*l2+1.)*(2.*J1+1.)*(2.*J2+1.) );

}

inline double Z( const int l1, const double J1, const int l2, const double J2, const double s, const int L ) {

  return H(l1,J1,l2,J2)*C(l1,l2,0,0,L,0)*W(l1,J1,l2,J2,s,L);

}

}

#endif
