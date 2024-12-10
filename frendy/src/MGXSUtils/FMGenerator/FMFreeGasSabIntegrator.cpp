#pragma once

#include "MGXSUtils/FMGenerator/FMFreeGasSabIntegrator.h"

using namespace FMGen;

void FMFreeGasSabIntegrator::initialize(int _max_pl, REAL _aw, REAL _temp, REAL _torelance)
{
	max_pl = _max_pl;
	aw = _aw;
	temperature = _temp;
	eff_temperature = _temp;
	kt = BOLTZMANN_CONSTANT * _temp;
	torelance = _torelance;

	return;
}
void FMFreeGasSabIntegrator::prepSabFactorTable(REAL _emax, REAL _emin)
{
	emax = _emax;
	emin = _emin;

	//construct ein-grid
	ein_grid.resize(NUM_EIN_GRID+1);
	for (int i = 0; i <= NUM_EIN_GRID; i++)
	{
		REAL val = (log(emax) - log(emin)) / (REAL)NUM_EIN_GRID * (REAL)i + log(emin);
		ein_grid[i] = exp(val);
	}

	//construct eout-grid and sab_factor_table
	eout_grid.resize(ein_grid.size());
	sab_factor_table.resize(ein_grid.size());
	resetNumIntegral();

	for (int ii = 0; ii < static_cast<int>(ein_grid.size()); ii++)
	{
		map<REAL, SABWK> sab_wk_map;
		sab_wk_map.clear();
		SABWK sab_wk;
		sab_wk.coef.resize(max_pl + 1);
		sab_wk.converged = false;

		//initial eout grid
		for (int io = 0; io <= NUM_EOUT_MIN_GRID; io++)
		{
			REAL val = (log(emax) - log(emin)) / (REAL)NUM_EOUT_MIN_GRID * (REAL)io + log(emin);
			sab_wk_map.insert(make_pair(exp(val), sab_wk));
		}

		map<REAL, SABWK>::iterator it, it2;
		//calculate s(a,b)-factor table ... (aw+1)^2/aw^2/2kt*sqrt(E'/E)exp(-beta/2)*s(a,b)
		for (it = sab_wk_map.begin(); it != sab_wk_map.end(); it++)
		{
			REAL ein = ein_grid[ii];
			REAL eout = it->first;
			it->second.coef.resize(max_pl + 1);
			getPlCoefOld(ein, eout, it->second.coef, true, false, torelance*0.1);
		}

		//confirm accuracy of linear interporation
		for (;;)
		{
#if 0
			//calculate s(a,b)-factor table ... (aw+1)^2/aw^2/2kt*sqrt(E'/E)exp(-beta/2)*s(a,b)
			for (it = sab_wk_map.begin(); it != sab_wk_map.end(); it++)
			{
				REAL ein = ein_grid[ii];
				REAL eout = it->first;
				it->second.coef.resize(max_pl + 1);
				getPlCoefOld(ein, eout, it->second.coef, true, false, torelance*0.1);
			}
#endif
			//check maximum value for coefficients
			REAL coef_max = 0.0;
			for (it = sab_wk_map.begin(); it != sab_wk_map.end(); it++)
			{
				if (coef_max < fabs(it->second.coef[0])) coef_max = fabs(it->second.coef[0]);
			}

			map<REAL, SABWK> add_table;
			add_table.clear();
			//REAL eps_max_rel = 0.0;
			//REAL eps_max_dif = 0.0;
			it2 = sab_wk_map.end();
			it2--;
			for (it = sab_wk_map.begin(); it != (--sab_wk_map.end()); it++)
			{
				if (it->second.converged == true) continue;

				REAL ein = ein_grid[ii];
#if 0
				//log-linear interpolation
				//REAL eout = sqrt(eout_grid[ii][io] * eout_grid[ii][io + 1]);
				//REAL val = (sab_wk[io + 1][0] - sab_wk[io][0]) / (log(eout_grid[ii][io + 1]) - log(eout_grid[ii][io]))*(log(eout) - log(eout_grid[ii][io])) + sab_wk[io][0];
#else
				//linear-linear interpolation
				it2 = it;
				it2++;
				REAL eout = (it->first + it2->first)/2.0;
				REAL val = (it2->second.coef[0] + it->second.coef[0]) / 2.0;
#endif
				getPlCoefOld(ein, eout, sab_wk.coef, true, false, torelance*0.1);

#if 0
				REAL eps_rel = 0.0;
				REAL eps_dif = 0.0;
				if ((val + sab_wk.coef[0]) != 0.0) eps_rel = abs((val - sab_wk.coef[0]) / (val + sab_wk.coef[0]) / 2.0);
				eps_dif = abs(val - sab_wk.coef[0]);
				if (eps_rel > eps_max_rel && eps_dif > EPS_SAB_FACTOR) eps_max_rel = eps_rel;
				if (eps_dif > eps_max_dif && eps_rel > eps_max_rel) eps_max_dif = eps_dif;
				REAL delta_eout_grid = fabs(it->first - it2->first) / (it->first + it2->first)*2.0;
				if (eps_rel > torelance && eps_dif > EPS_SAB_FACTOR*5.0 && delta_eout_grid > 1.0e-3)
				{
					it->second.converged = false;
					sab_wk.converged = false;
					add_table.insert(make_pair(eout, sab_wk));
				}
				else
				{
					it->second.converged = true;
					sab_wk.converged = true;
				}
#else
				REAL eps = 0.0;
				if (coef_max != 0.0) eps = abs((val - sab_wk.coef[0])) / coef_max;
				REAL delta = fabs(it->first / it2->first - 1.0);
				if (eps > torelance && delta > 0.01)
				{
					it->second.converged = false;
					sab_wk.converged = false;
					add_table.insert(make_pair(eout, sab_wk));
				}
				else
				{
					it->second.converged = true;
					sab_wk.converged = true;
				}
#endif
			}

			//check convergence
			if (add_table.size() == 0) break;
			//std::cout << ii << " " << ein_grid[ii] << " " << add_table.size() << endl;

			//add results
			for (it = add_table.begin(); it != add_table.end(); it++)
				sab_wk_map.insert(make_pair(it->first, it->second));
		}

		//add eout grid & s(a,b) table
		eout_grid[ii].resize(sab_wk_map.size());
		sab_factor_table[ii].resize(sab_wk_map.size());
		int io = 0;
		for (it = sab_wk_map.begin(); it != sab_wk_map.end(); it++)
		{
			eout_grid[ii][io] = it->first;
			sab_factor_table[ii][io] = it->second.coef;
			io++;
		}
	}


	int num_total = 0;
	cout << " Number of s(a,b) factor table in free gas thermal scattering " << endl;
	cout << setprecision(4) << scientific;
	cout << " No.     Eout grid      Number s(a,b) factor table " << endl;
	for (int ii = 0; ii < static_cast<int>(ein_grid.size()); ii++)
	{
		cout << setw(5) << ii;
		cout << setw(15) << setprecision(4) << scientific << ein_grid[ii];
		cout << setw(5) << setprecision(4) << scientific << eout_grid[ii].size() << endl;
		num_total += sab_factor_table[ii].size();
	}
	cout << " total number of s(a,b) factor table : " << num_total << endl << endl;
	cout << " total number of integration         : " << scientific << num_integral << endl;
}
void FMFreeGasSabIntegrator::getPlCoefUsingTableLinear(REAL ein, REAL eout, vector<REAL>& coef)
{
	int ii1, ii2, io1, io2;
	ii1 = getInterval(ein_grid, ein);
	ii2 = ii1 + 1;
	REAL eout1, eout2;
	eout1 = eout * (ein_grid[ii1] / ein);
	eout2 = eout * (ein_grid[ii2] / ein);
	io1 = getInterval(eout_grid[ii1], eout1);
	io2 = getInterval(eout_grid[ii2], eout2);

	vector<REAL> coefwk1(max_pl+1), coefwk2(max_pl + 1);

	for (int il = 0; il <= max_pl; il++)
	{
		coef[il] = 0.0;
		coefwk1[il] = 0.0;
		coefwk2[il] = 0.0;
	}

	for (int il = 0; il <= max_pl; il++)
	{
		coefwk1[il] = (sab_factor_table[ii1][io1 + 1][il] - sab_factor_table[ii1][io1][il]) / (eout_grid[ii1][io1 + 1] - eout_grid[ii1][io1])*(eout1 - eout_grid[ii1][io1]) + sab_factor_table[ii1][io1][il];
		coefwk2[il] = (sab_factor_table[ii2][io2 + 1][il] - sab_factor_table[ii2][io2][il]) / (eout_grid[ii2][io2 + 1] - eout_grid[ii2][io2])*(eout2 - eout_grid[ii2][io2]) + sab_factor_table[ii2][io2][il];
	}

	REAL fact = (ein - ein_grid[ii1]) / (ein_grid[ii2] - ein_grid[ii1]);
	for (int il = 0; il <= max_pl; il++)
		coef[il] = (1.0-fact)*coefwk1[il] + fact*coefwk2[il];
}
void FMFreeGasSabIntegrator::getPlCoefUsingTableQuadratic(REAL ein, REAL eout, vector<REAL>& coef)
{
	int ii1, ii2, ii3, io1, io2, io3;
	ii1 = getIntervalQuadratic(ein_grid, ein);
	ii2 = ii1 + 1;
	ii3 = ii1 + 2;
	REAL eout1, eout2, eout3;
	eout1 = eout*(ein_grid[ii1] / ein);
	eout2 = eout*(ein_grid[ii2] / ein);
	eout3 = eout*(ein_grid[ii3] / ein);
	io1 = getInterval(eout_grid[ii1], eout1);
	io2 = getInterval(eout_grid[ii2], eout2);
	io3 = getInterval(eout_grid[ii3], eout3);

	vector<REAL> coefwk1(max_pl + 1), coefwk2(max_pl + 1), coefwk3(max_pl + 1);

	for (int il = 0; il <= max_pl; il++)
	{
		coef[il] = 0.0;
		coefwk1[il] = 0.0;
		coefwk2[il] = 0.0;
		coefwk3[il] = 0.0;
	}

	for (int il = 0; il <= max_pl; il++)
	{
		coefwk1[il] = (sab_factor_table[ii1][io1 + 1][il] - sab_factor_table[ii1][io1][il]) / (eout_grid[ii1][io1 + 1] - eout_grid[ii1][io1]) * (eout1 - eout_grid[ii1][io1]) + sab_factor_table[ii1][io1][il];
		coefwk2[il] = (sab_factor_table[ii2][io2 + 1][il] - sab_factor_table[ii2][io2][il]) / (eout_grid[ii2][io2 + 1] - eout_grid[ii2][io2]) * (eout2 - eout_grid[ii2][io2]) + sab_factor_table[ii2][io2][il];
		coefwk3[il] = (sab_factor_table[ii3][io3 + 1][il] - sab_factor_table[ii3][io3][il]) / (eout_grid[ii3][io3 + 1] - eout_grid[ii3][io3]) * (eout3 - eout_grid[ii3][io3]) + sab_factor_table[ii3][io3][il];
	}

	for (int il = 0; il <= max_pl; il++)
		coef[il] = do2ndLagrangeInterpolation(ein, ein_grid[ii1], ein_grid[ii2], ein_grid[ii3],
			coefwk1[il], coefwk2[il], coefwk3[il]);

	//check consistency with linear interporation
	REAL fact;
	vector<REAL> coeflin(max_pl + 1);
	if (ein >= ein_grid[ii1] && ein <= ein_grid[ii2])
	{
		fact = (ein - ein_grid[ii1]) / (ein_grid[ii2] - ein_grid[ii1]);
		for (int il = 0; il <= max_pl; il++)
			coeflin[il] = (1.0 - fact) * coefwk1[il] + fact * coefwk2[il];
	}
	else
	{
		fact = (ein - ein_grid[ii2]) / (ein_grid[ii3] - ein_grid[ii2]);
		for (int il = 0; il <= max_pl; il++)
			coeflin[il] = (1.0 - fact) * coefwk2[il] + fact * coefwk3[il];
	}

	REAL eps = 0.0;
	if (coeflin[0] != 0.0) eps = abs((coeflin[0] - coef[0]) / coeflin[0]);
	if (eps > 0.1)
	{
		for (int il = 0; il <= max_pl; il++)
			coef[il] = coeflin[il];
	}
}
void FMFreeGasSabIntegrator::getPlCoefOld(REAL ein, REAL eout, vector<REAL>& coef, bool norm, bool sct, REAL _torelance)
{
	if (_torelance == 0.0) _torelance = torelance;

	for (int il = 0; il <= max_pl; il++)
		coef[il] = 0.0;
	REAL beta = (eout - ein) / kt;
	REAL fact = (aw + 1.0) * (aw + 1.0) / (aw * aw) / (2.0 * BOLTZMANN_CONSTANT * temperature) * sqrt(eout / ein);

	int num_div = 32;	//initial angular division
	for (int im = 0; im < num_div; im++)
	{
		REAL mu0 = 2.0 / (REAL)num_div * (REAL)im - 1.0;
		REAL mu1 = 2.0 / (REAL)num_div * (REAL)(im + 1) - 1.0;
		getPlCoefAdaptiveMuIntegrationOld(fact, beta, ein, eout, mu0, mu1, sct, coef, _torelance);
	}

	if (sct == false && norm == true)
	{
		//theoretical value only for P0. Normalize using the theoretical value
		REAL val = calcThermalIncoherentScatteringXSFreeGasAngleIntegrated(1.0, aw, ein, eout, temperature);
		if (coef[0] != 0.0)
		{
			REAL rat = val / coef[0];
			for (int il = 0; il <= max_pl; il++)
				coef[il] *= rat;
		}
	}
}
void FMFreeGasSabIntegrator::getPlCoefAdaptiveMuIntegrationOld(REAL fact, REAL beta, REAL ein, REAL eout, REAL mu0, REAL mu1, bool sct, vector<REAL>& coef, REAL _torelance)
{
	REAL mua = (mu0 + mu1) / 2.0;
	REAL alpha0 = (eout + ein - 2.0 * mu0 * sqrt(eout * ein)) / (aw * kt);
	if (alpha0 < ALPHA_MIN) alpha0 = ALPHA_MIN;
	REAL alpha1 = (eout + ein - 2.0 * mu1 * sqrt(eout * ein)) / (aw * kt);
	if (alpha1 < ALPHA_MIN) alpha1 = ALPHA_MIN;
	REAL alphaa = (eout + ein - 2.0 * mua * sqrt(eout * ein)) / (aw * kt);
	if (alphaa < ALPHA_MIN) alphaa = ALPHA_MIN;

	REAL val0, val1, valt, sab0, sab1, sabt;
	if (sct == false)
	{
		//free gas
		val0 = (alpha0 * alpha0 + beta * beta + 2.0 * alpha0 * beta) / (4.0 * alpha0);
		val1 = (alpha1 * alpha1 + beta * beta + 2.0 * alpha1 * beta) / (4.0 * alpha1);
		valt = (alphaa * alphaa + beta * beta + 2.0 * alphaa * beta) / (4.0 * alphaa);
		sab0 = 1.0 / sqrt(4.0 * PI * alpha0) * exp(-val0);
		sab1 = 1.0 / sqrt(4.0 * PI * alpha1) * exp(-val1);
		sabt = 1.0 / sqrt(4.0 * PI * alphaa) * exp(-valt);
	}
	else
	{
		//short collision time approximatin
		REAL tet = eff_temperature / temperature;
		val0 = (alpha0 - abs(beta))*(alpha0 - abs(beta)) / (4.0*alpha0*tet) + (beta + abs(beta)) / 2.0;
		val1 = (alpha1 - abs(beta))*(alpha1 - abs(beta)) / (4.0*alpha1*tet) + (beta + abs(beta)) / 2.0;
		valt = (alphaa - abs(beta))*(alphaa - abs(beta)) / (4.0*alphaa*tet) + (beta + abs(beta)) / 2.0;
		sab0 = 1.0 / sqrt(4.0 * PI * alpha0 * tet) * exp(-val0);
		sab1 = 1.0 / sqrt(4.0 * PI * alpha1 * tet) * exp(-val1);
		sabt = 1.0 / sqrt(4.0 * PI * alphaa * tet) * exp(-valt);
	}

	REAL fsab0 = checkEPS(sab0 * fact);
	REAL fsab1 = checkEPS(sab1 * fact);
	REAL fsabt = checkEPS(sabt * fact);
	REAL fsaba = (fsab0 + fsab1) / 2.0;

	REAL eps = 0.0;
#if 1
	if (fsabt != 0.0) eps = fabs((fsaba - fsabt) / fsabt);
#else
	if (fsabt != 0.0) eps = fabs((fsaba - fsabt) / fact);
#endif

	if (eps < _torelance)
	{
		REAL p1[MAX_PL + 1], p2[MAX_PL + 1];
		for (int i = 0; i <= max_pl; i++)
		{
			p1[i] = 0.0;
			p2[i] = 0.0;
		}
		Pl(max_pl, (mu0 + mua) / 2.0, p1);
		Pl(max_pl, (mua + mu1) / 2.0, p2);
		for (int il = 0; il <= max_pl; il++)
		{
			coef[il] += (fsab0 + fsabt) / 2.0 * p1[il] * (mu1 - mu0) / 2.0;
			coef[il] += (fsab1 + fsabt) / 2.0 * p2[il] * (mu1 - mu0) / 2.0;
		}
		num_integral += 2.0;
	}
	else
	{
		getPlCoefAdaptiveMuIntegrationOld(fact, beta, ein, eout, mu0, mua, sct, coef, _torelance);
		getPlCoefAdaptiveMuIntegrationOld(fact, beta, ein, eout, mua, mu1, sct, coef, _torelance);
	}
}
void FMFreeGasSabIntegrator::getPlCoef(REAL ein, REAL eout, vector<REAL>& coef, bool norm, bool sct, REAL _torelance)
{
	if (_torelance == 0.0) _torelance = torelance;

	for (int il = 0; il <= max_pl; il++)
		coef[il] = 0.0;
	REAL beta = (eout - ein) / kt;
	REAL _kt = BOLTZMANN_CONSTANT*temperature;
	REAL akt = aw*_kt;
	REAL a = (eout + ein) / akt;
	REAL b = 2.0*sqrt(eout*ein) / akt;
	if (b > a) b = a;
	REAL c = (aw + 1.0) * (aw + 1.0) / (aw * aw)*sqrt(eout / ein) / (2.0*_kt*sqrt(4.0*PI));
	REAL delta = sqrt(a + b) - sqrt(a - b);

	const int num_div = 32;	//initial angular division
	REAL fvp[num_div + 2][MAX_PL+1];

	//add u = sqrt(abs(beta)) as an interval boundary
	vector<REAL> u_vec_wk(num_div + 1);
	for (int im = 0; im <= num_div; im++)
		u_vec_wk[im] = delta / (REAL)num_div * (REAL)im + sqrt(a - b);

	REAL sqrt_beta = sqrt(abs(beta));
	if (sqrt_beta > sqrt(a - b) && sqrt_beta < sqrt(a + b))
		u_vec_wk.push_back(sqrt_beta);
	sort(u_vec_wk.begin(), u_vec_wk.end());

	//delete narrow interval(s)
	vector<REAL> u_vec;
	u_vec.push_back(u_vec_wk[0]);
	for (int im = 1; im < (int)u_vec_wk.size(); im++)
	{
		REAL dif = (u_vec_wk[im] - u_vec_wk[im - 1]) / (sqrt(a + b) + sqrt(a - b));
		dif = abs(dif);
		if (dif > 1.0e-6) u_vec.push_back(u_vec_wk[im]);
	}

	for (int im = 0; im < (int) u_vec.size(); im++)
	{
		REAL u = u_vec[im];
		if (u < delta * 1.0e-6) u = delta * 1.0e-6;
		REAL wk = (u + beta / u);
		REAL val = 2.0 / b * exp(-wk * wk / 4.0);
		if (sct)
		{
			//additional term for short collision approximation
			REAL r = temperature / eff_temperature;
			REAL wk2 = (u - fabs(beta) / u);
			val = 2.0 / b * exp(-wk * wk / 4.0 + (1.0 - r) * wk2 * wk2 / 4.0)*sqrt(r);
		}
		REAL fval = checkEPS(val * c);
		REAL plval[MAX_PL + 1];
		for (int i = 0; i <= max_pl; i++)
			plval[i] = 0.0;
		// http://dx.doi.org/10.1016/j.anucene.2015.07.031 Eq.(20), but a and b should be swapped.
		REAL mu = (a - u * u) / b;
		Pl(max_pl, mu, plval);
		for (int i = 0; i <= max_pl; i++)
		{
			fvp[im][i] = fval * plval[i];
			if (std::isfinite(fvp[im][i]) == false)
			{
				cout << " encounter infinite value during thermal xs integration FMFreeGasSabIntegrator::getPlCoef " << endl;
				cout << " val  " << val << endl;
				cout << " wk  " << wk << endl;
				cout << " beta  " << beta << endl;
				cout << " u  " << u << endl;
				cout << " b  " << b << endl;
				cout << " c  " << c << endl;
				cout << " sct  " << sct << endl;
				exit(0);
			}
		}
	}
	for (int im = 0; im < (int) u_vec.size()-1; im++)
	{
		REAL u0 = u_vec[im];
		REAL u1 = u_vec[im+1];
		if (u0 < delta*1.0e-6) u0 = delta*1.0e-6;
		getPlCoefAdaptiveMuIntegration(c, delta, beta, a, b, u0, u1, fvp[im], fvp[im+1], sct, coef, _torelance);
	}

	if (sct==false && norm==true)
	{
		//theoretical value only for P0. Normalize using the theoretical value
		REAL val = calcThermalIncoherentScatteringXSFreeGasAngleIntegrated(1.0, aw, ein, eout, temperature);
		if (coef[0] != 0.0)
		{
			REAL fact = val / coef[0];
			for (int il = 0; il <= max_pl; il++)
				coef[il] *= fact;
		}
	}
}
void FMFreeGasSabIntegrator::getPlCoefAdaptiveMuIntegration(REAL fact, REAL delta, REAL beta, REAL a, REAL b, REAL u0, REAL u1, REAL* fvp0, REAL* fvp1, bool sct, vector<REAL>& coef, REAL _torelance)
{
	REAL ua = (u0 + u1) / 2.0;

	REAL wkt, valt;
	//free gas
	wkt = (ua + beta / ua);
	valt = 2.0 / b*exp(-wkt*wkt / 4.0);
	if (sct)
	{
		//additional term for short collision approximation
		REAL r = temperature / eff_temperature;
		REAL wkt2 = (ua - fabs(beta) / ua);
		valt = 2.0 / b * exp(-wkt * wkt / 4.0 + (1.0 - r) * wkt2 * wkt2 / 4.0) * sqrt(r);
	}

	REAL fvalt = checkEPS(valt * fact);
	REAL fvala = (fvp0[0] + fvp1[0]) / 2.0;

	REAL eps = 0.0;
	if (fvalt != 0.0) eps = fabs((fvala - fvalt) / fvalt);

	REAL fvpt[MAX_PL + 1];
	REAL pa[MAX_PL + 1];
	for (int i = 0; i <= max_pl; i++)
		pa[i] = 0.0;
	REAL mua = (a - ua * ua) / b;
	Pl(max_pl, mua, pa);
	for (int il = 0; il <= max_pl; il++)
	{
		fvpt[il] = fvalt * pa[il];
#if 0
		if (std::isfinite(fvpt[il]) == false)
		{
			cout << " encounter infinite value during thermal xs integration FMFreeGasSabIntegrator::getPlCoefAdaptiveMuIntegration " << endl;
			cout << " valt  " << valt << endl;
			cout << " wkt  " << wkt << endl;
			cout << " beta  " << beta << endl;
			cout << " ua  " << ua << endl;
			cout << " b  " << b << endl;
			cout << " fact  " << fact << endl;
			cout << " sct  " << sct << endl;
			exit(0);
		}
#endif
	}

	if (eps < _torelance)
	{
		REAL dx = (u1 - u0) / 2.0;
		REAL wk = 1.0 / 3.0 * dx;
		for (int il = 0; il <= max_pl; il++)
		{
			//integration using Gauss-Lobatto quadrature 
			coef[il] += wk*(fvp0[il] + fvp1[il] + 4.0* fvpt[il]);
		}
		num_integral += 1.0;
	}
	else
	{
		getPlCoefAdaptiveMuIntegration(fact, delta, beta, a, b, u0, ua, fvp0, fvpt, sct, coef, _torelance);
		getPlCoefAdaptiveMuIntegration(fact, delta, beta, a, b, ua, u1, fvpt, fvp1, sct, coef, _torelance);
	}
}
