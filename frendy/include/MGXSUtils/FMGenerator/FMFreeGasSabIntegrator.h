//-----------------------------------------------------
// FMFreeGasSabIntegrator.h : numerical integration for free gas s(a,b)
//        
//-----------------------------------------------------

#pragma once

#include "MGXSUtils/FMGenerator/FMGenerator_global.h"
#include "MGXSUtils/FMGenerator/FMZlib.h"

namespace FMGen
{
	struct SABWK
	{
		vector<REAL>	coef;
		bool			converged;
	};

	class FMFreeGasSabIntegrator
	{
	private:
		const REAL	ALPHA_MIN = 1.0e-8;
		const REAL	EPS_SAB_FACTOR = 1.0e-10;
		const int	NUM_EOUT_MIN_GRID = 100;
		const int	NUM_EIN_GRID = 1000;

		REAL		aw;
		REAL		temperature;
		REAL		eff_temperature;
		REAL		kt;
		int			max_pl;
		REAL		torelance;
		REAL		num_integral;

		REAL		emax;
		REAL		emin;
		vector<REAL>			ein_grid;
		vector<vector<REAL> >	eout_grid;
		vector<vector<vector<REAL> > >	sab_factor_table;

	public:

		FMFreeGasSabIntegrator()
		{
		};
		~FMFreeGasSabIntegrator() {};

		void initialize(int _max_pl, REAL _aw, REAL _temp, REAL _torelance);
		void prepSabFactorTable(REAL _emax, REAL _emin);
		void resetNumIntegral()
		{
			num_integral = 0.0;
		}
		REAL getNumIntegral()
		{
			return num_integral;
		}
		void getPlCoefUsingTableLinear(REAL ein, REAL eout, vector<REAL>& coef);
		void getPlCoefUsingTableQuadratic(REAL ein, REAL eout, vector<REAL>& coef);
		void getPlCoefOld(REAL ein, REAL eout, vector<REAL>& coef, bool norm, bool sct, REAL torelance = 0.0);
		void getPlCoefAdaptiveMuIntegrationOld(REAL fact, REAL beta, REAL ein, REAL eout, REAL mu0, REAL mu1, bool sct, vector<REAL>& coef, REAL torelance);
		void getPlCoef(REAL ein, REAL eout, vector<REAL>& coef, bool norm, bool sct, REAL torelance = 0.0);
		void getPlCoefAdaptiveMuIntegration(REAL fact, REAL delta, REAL beta, REAL a, REAL b, REAL u0, REAL u1, REAL* fvp0, REAL* fvp1, bool sct, vector<REAL>& coef, REAL torelance);
		REAL checkEPS(REAL val)
		{
			if (abs(val) < EPS_SAB_FACTOR)
				return 0.0;
			else
				return val;
		}
		void setEffectiveTemperature(REAL teff)
		{
			eff_temperature = teff;
		}
	};
}
