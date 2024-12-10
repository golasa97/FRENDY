//----------------------------------------------------------------
// global constants for multi-group xs processing
//
//----------------------------------------------------------------

#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>
#include <numeric>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <cassert>
#include <limits>
#include <float.h>

using namespace std;

namespace FMGen
{
#define		_FM_EXTEND_MAXIMUM_OUTGOING_ENERGY_FOR_LAW_
#define		_FM_DOUBLE_PRECISION_

#ifdef _FM_DOUBLE_PRECISION_
	typedef double	REAL;
#else
	typedef float	REAL;
#endif

	typedef double	DOUBLE;

	const int MAX_PL = 7;
	//Note: when MAX_PL is changed, please also change the folloiwngs;
	// PL_COEFA[n] = (2n+1)/(n+1), PL_COEFB[n] = n/(n+1).
	// Be careful these should be REAL.
	const REAL PL_COEFA[MAX_PL + 1] = { (2. * 0 + 1) / 1,(2. * 1 + 1) / 2, (2. * 2 + 1) / 3, (2. * 3 + 1) / 4, (2. * 4 + 1) / 5, (2. * 5 + 1) / 6, (2. * 6 + 1) / 7, (2. * 7 + 1) / 8 };
	const REAL PL_COEFB[MAX_PL + 1] = { 0. / 1, 1. / 2, 2. / 3, 3. / 4, 4. / 5, 5. / 6, 6. / 7, 7. / 8 };

	const int MAX_MU_DIV = 256;
	const int MAX_MU_DIV_LAW66 = 32;
	const int MAX_EOUT_DIV_ELASTIC = 64;
	const int MAX_EOUT_DIV_LAW66 = 10;
	const REAL XS_SMALL_RATIO = 1.0e-12;
	const REAL XS_SMALL_RATIO_PL = 1.0e-5;
	const REAL BOLTZMANN_CONSTANT = 8.617333262145e-5;  //[ev/K]
	const REAL NEUTRON_MASS = 1.674927471e-27; //[kg]
	const REAL EV2J = 1.602176634e-19; //[J]
	const REAL RESO_UPSCAT_EMAX = 250.0;	//[eV]
	const REAL RESO_UPSCAT_EMIN = 1.0;		//[eV]
	const REAL THERMAL_CUTOFF_MAX_DEFAULT = 10.0;
	const REAL THERMAL_SAB_INTEGRATE_TORELANCE = 1.0e-2;
	const REAL THERMAL_SAB_INTEGRATE_MIN_DELTA_LETHARGY = 1.0e-4;
	const REAL PI = 3.1415926535897932385;

	//#define		_FM_USE_ILF_UNR_
	//#define		_FM_USE_IOA_UNR_

	enum CoordinateType
	{
		eCenterOfMassSystem,
		eLaboratorySystem
	};

	enum FMMTType
	{
		eMTTotalCurrentWeight = -1,
		eMTTotal = 1,
		eMTElasticScattering = 2,
		eMTInelasticScatteringTotal = 4,
		eMTN2n = 16,
		eMTN3n = 17,
		eMTFission = 18,
		eMTFirstChanceFission = 19,
		eMTSecondChanceFission = 20,
		eMTThirdChanceFission = 21,
		eMTFourthChanceFission = 38,
		eMTInelasticScatteringBegin = 51,
		eMTInelasticScatteringEnd = 91,
		eMTDisappearance = 101,		//sum of capture, (n, alpha), (n, p), .... not equivalent to absorption since fission is not included
		eMTNGamma = 102,
		eMT117 = 117,
		eMT152 = 152,
		eMT200 = 200,
		eMTThermalFreeGas = 221,
		eMTThermalKernelUpper = 250,
		eMTAverageMubar = 251,
		eMTSlowingDownXi = 252,
		eMTSlowingDownGamma = 253,
		eMTAverageLethargy = 258,
		eMTAverageInverseVerocity = 259,
		eMTHeating = 301,
		eMTKerma = 443,
		eMTDamage = 444,
		eMTNuTotal = 452,
		eMTNuDelayed = 455,
		eMTNuPrompt = 456,
		eMTEnergyDependentNeutronEmission = 100000,
		eMTChiTotal = 1000452,
		eMTChiDelayed = 1000455,
		eMTChiPrompt = 1000456,
		eMTNWT0 = 1001001,
		eMTNWT1 = 1001002,
		eMTMaximum = 10000000,
	};
}