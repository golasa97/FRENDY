#ifndef INCLUDE_Constant_H
#define INCLUDE_Constant_H

#include <iostream>
#include <cmath>

using namespace std;

namespace Constant {


/* Minimum value of elab */
//const double elab0 = 1.e-5;

/* Fine structure constant (-) */
//const double alpha_fine_structure = 1./137.03599976;
const double alpha_fine_structure = 0.007297352533286;
//const double alpha_fine_structure = 1./137.035999139;  // <- IAEA test1a (deBoer)

/* Atomic mass unit (eV/c^2) */
const double amu   = 931.494013e+6;
//const double amu   = 931.4940954e+6;  // <- IAEA test1a (deBoer)

/* Planck's constant (eV*s) */
const double h_Planck = 4.13566727e-15;

/* Planck's constant /2pi (eV*s) */
const double hbar = 6.58211889e-16;

/* Boltzmann's constant (eV/K) */
const double k_Boltzmann = 8.617342e-5;

/* Speed of light (m/s) */
const double c_speed_of_light = 299792458.;

/* hbar * c (eV*fm) */
const double hbarc = hbar * c_speed_of_light * 1.e+15;
//const double hbarc = 197.3269788 * 1.e+6;  // <- IAEA test1a (deBoer)

/* Avogadro's number (1/mol) */
const double N_A = 6.02214199e+23;

/* Particle mass (amu)*/
//double mass( const int za = 1 );


inline double mass( const int za = 1 ) {

  switch( za ) {

    case    1 : return 1.00866491578;
    case 1001 : return 1.00727646688;
    case 1002 : return 2.01355321271;
    case 1003 : return 3.015500713;
    case 2003 : return 3.01493223469;
    case 2004 : return 4.0015061747;

    default:

      cerr << "!! constant::mass -> not given for za = " << za << endl;

  }

  return 0.0;

}


/*
const double HBARC = GSL_CONST_MKSA_PLANCKS_CONSTANT_HBAR * GSL_CONST_MKSA_SPEED_OF_LIGHT
                     / GSL_CONST_MKSA_ELECTRON_VOLT * 1.E+9;  // 197.327 *10^6 (eV*fm)

const double AMU = 931.5012;

const double ALPHA = GSL_CONST_NUM_FINE_STRUCTURE;  // 1./137.036 (non-dim)

const double CEK = 0.5*HBARC*HBARC/AMU;
*/


}

#endif
