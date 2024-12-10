//-----------------------------------------------------
// FMZlib.h : library of various calculations
//        
//-----------------------------------------------------
#pragma once

#include "FMGenerator_global.h"

namespace FMGen
{
	enum
	{
		eExtraporationLinear,
		eExtraporationConst,
		eExtraporationZero,
	};

	struct GaussLegendreQuadrature
	{
		REAL x1[1] = { 0.0 };
		REAL w1[1] = { 2.0 };
		REAL x2[2] = { -sqrt(1.0 / 3.0), +sqrt(1.0 / 3.0) };
		REAL w2[2] = { 1.0, 1.0 };
		REAL x3[3] = { -sqrt(3.0 / 5.0), 0.0, +sqrt(3.0 / 5.0) };
		REAL w3[3] = { 5.0 / 9.0, 8.0 / 9.0, 5.0 / 9.0 };
		REAL x4[4] = { -sqrt((3.0 + 2.0*sqrt(6.0 / 5.0)) / 7.0), -sqrt((3.0 - 2.0*sqrt(6.0 / 5.0)) / 7.0),
						sqrt((3.0 - 2.0*sqrt(6.0 / 5.0)) / 7.0),  sqrt((3.0 + 2.0*sqrt(6.0 / 5.0)) / 7.0) };
		REAL w4[4] = { (18.0 - sqrt(30.0)) / 36.0, (18.0 + sqrt(30.0)) / 36.0, 
					   (18.0 + sqrt(30.0)) / 36.0, (18.0 - sqrt(30.0)) / 36.0 };
		REAL x5[5] = { -1.0 / 3.0*sqrt(5.0 + 2.0*sqrt(10.0 / 7.0)), -1.0 / 3.0*sqrt(5.0 - 2.0*sqrt(10.0 / 7.0)), 0.0,
						1.0 / 3.0*sqrt(5.0 - 2.0*sqrt(10.0 / 7.0)),  1.0 / 3.0*sqrt(5.0 + 2.0*sqrt(10.0 / 7.0)) };
		REAL w5[5] = { (322.0 - 13.0*sqrt(70.0)) / 900.0, (322.0 + 13.0*sqrt(70.0)) / 900.0, 128.0 / 225.0,
					   (322.0 + 13.0*sqrt(70.0)) / 900.0, (322.0 - 13.0*sqrt(70.0)) / 900.0 };
	};
	struct GaussLobattoQuadrature
	{
		REAL x3[3] = { -1.0, 0.0, +1.0 };
		REAL w3[3] = { 1.0 / 3.0, 4.0 / 3.0, 1.0 / 3.0 };
		REAL x4[4] = { -1.0, -sqrt(1.0 / 5.0), sqrt(1.0 / 5.0), 1.0 };
		REAL w4[4] = { 1.0 / 6.0, 5.0 / 6.0, 5.0 / 6.0, 1.0 / 6.0 };
		REAL x5[5] = { -1.0, -sqrt(3.0 / 7.0), 0.0, sqrt(3.0 / 7.0), 1.0 };
		REAL w5[5] = { 1.0 / 10.0, 49.0 / 90.0, 32.0 / 45.0, 49.0 / 90.0, 1.0 / 10.0 };
		REAL x6[6] = { -1.0, -sqrt(1.0 / 3.0 + 2.0*sqrt(7.0) / 21.0), -sqrt(1.0 / 3.0 - 2.0*sqrt(7.0) / 21.0),
			sqrt(1.0 / 3.0 - 2.0*sqrt(7.0) / 21.0),  sqrt(1.0 / 3.0 + 2.0*sqrt(7.0) / 21.0), 1.0 };
		REAL w6[6] = { 1.0 / 15.0, (14.0 - sqrt(7.0)) / 30.0, (14.0 + sqrt(7.0)) / 30.0,
			(14.0 + sqrt(7.0)) / 30.0, (14.0 - sqrt(7.0)) / 30.0, 1.0 / 15.0 };
	};
	struct UniformQuadrature
	{
		REAL x1[1] = { 0.0 };
		REAL w1[1] = { 2.0 };
		REAL x2[2] = { -0.5, 0.5 };
		REAL w2[2] = { 1.0, 1.0 };
		REAL x3[3] = { -2.0/3.0, 0.0, 2.0/3.0 };
		REAL w3[3] = { 2.0/3.0, 2.0/3.0, 2.0/3.0 };
		REAL x4[4] = { -0.75, -0.25, 0.25, 0.75 };
		REAL w4[4] = { 0.5, 0.5, 0.5, 0.5};
		REAL x5[5] = { -0.8, -0.4, 0.0, 0.4, 0.8 };
		REAL w5[5] = { 0.4, 0.4, 0.4, 0.4, 0.4 };
	};

	inline bool compareString(string s1, string s2, int len=0)
	{
		transform(s1.begin(), s1.end(), s1.begin(), (int(*)(int)) toupper);
		transform(s2.begin(), s2.end(), s2.begin(), (int(*)(int)) toupper);
		if (len <= 0)
		{
			if (s1 == s2) return true;
			else return false;
		}
		else
		{
			if ( len > static_cast<int>(s1.length()) || len > static_cast<int>(s2.length()) )
				return false;

			string::iterator it1, it2;
			it1 = s1.begin();
			it2 = s2.begin();
			for (int i = 0; i < len; i++)
				if (it1[i] != it2[i]) return false;

			return true;
		}
	}
	inline void splitToToken(string& buf, vector<string>& buf_vec)
	{
		buf_vec.clear();

		// delete space at the end of line
		int bufsize = buf.size() - 1;
		for (int i = bufsize; i >= 0; i--)
		{
			if (buf[i] != ' ')
				break;
			else
				buf.erase(i, 1);
		}

		// split into token
		istringstream strin(buf);
		while (!strin.eof())
		{
			string wk;
			strin >> wk;
			if (wk.size() != 0)
				buf_vec.push_back(wk);
		}
	}

	inline int rtoi(REAL val)
	{
		if (val >= 0.0)
			return (int)(val + 0.1);
		else
			return (int)(val - 0.1);
	}
	inline int getIntt(int nr, vector<int>& nbtt, vector<int>& intt, int n)
	{
		if (nr == 0) return 2;
		if (n >= nbtt.back() - 1) return intt.back();
		for (int i = 0; i < nr; i++)
		{
			if (n < nbtt[i]-1)
				return intt[i];
		}
		cout << " error in int getIntt(int nr, vector<int>& nbtt, vector<int>& intt, int n) " << endl;
		exit(0);
	}
	inline REAL endfInterpolator2Point(int intt, REAL x0, REAL x1, REAL y0, REAL y1, REAL x, int extraporation=eExtraporationConst)
	{
		if (extraporation == eExtraporationConst)
		{
			if (x < x0) return y0;
			if (x > x1) return y1;
		}
		else if (extraporation == eExtraporationZero)
		{
			if (x < x0) return 0.0;
			if (x > x1) return 0.0;
		}
		if (x0 == x1)
			return y0;

		//change interporation mode to avoide [nan]
		if (intt == 4)
		{
			if (y1 <= 0.0 || y0 <= 0.0) intt = 2;
		}
		if (intt == 5)
		{
			if (y1 <= 0.0 || y0 <= 0.0)
			{
				if (x1 <= 0.0 || x0 <= 0.0)
					intt = 2;
				else
					intt = 3;
			}
			else
			{
				if (x1 <= 0.0 || x0 <= 0.0)
					intt = 4;
				else
					intt = 5;
			}
		}

		REAL val; //, wk0, wk1, wk2, wk3;
		switch (intt)
		{
		case 1:
			val = y0;
			break;
		case 0:
		case 2:
			val = (y1 - y0) / (x1 - x0) * (x - x0) + y0;
			break;
		case 3:
			val = (y1 - y0) / (log(x1) - log(x0)) * (log(x) - log(x0)) + y0;
			break;
		case 4:
			val = (log(y1) - log(y0)) / (x1 - x0) * (x - x0) + log(y0);
			val = exp(val);
			break;
		case 5:
			val = (log(y1) - log(y0)) / (log(x1) - log(x0)) * (log(x) - log(x0)) + log(y0);
			val = exp(val);
			break;
		default:
			cout << " not implemented in REAL endfInterpolator(int intt, REAL x0, REAL x1, REAL y0, REAL y1, REAL x)" << intt << endl;
			exit(0);
		}

		return val;
	}
	inline REAL endfInterpolator(int nr, vector<int>& nbtt, vector<int>& intt, vector<REAL>& x, vector<REAL>& y, REAL xval)
	{
		REAL yval = 0.0;

		if (x.size() <= 1 || x.size() != y.size())
		{
			cout << " error in inline REAL endfInterpolator " << endl;
			exit(0);
		}

		if (xval <= x[0])
		{
			yval = y[0];
		}
		else if (xval >= x.back())
		{
			yval = y.back();
		}
		else
		{
			for (int i = 0; i < static_cast<int>(x.size()) - 1; i++)
			{
				if (xval >= x[i] && xval <= x[i + 1])
				{
					int inttval = getIntt(nr, nbtt, intt, i);
					yval = endfInterpolator2Point(inttval, x[i], x[i + 1], y[i], y[i + 1], xval);
				}
			}
		}

		return yval;
	}
	inline REAL getXboundaryValue(vector<REAL>& x, vector<REAL>& c, REAL _cin)
	{
		if (_cin < c[0]) return x[0];
		if (_cin >= c.back()) return x.back();

		for (int i = 0; i < static_cast<int>(x.size()) - 1; i++)
		{
			if (_cin >= c[i] && _cin < c[i + 1])
			{
				REAL val;
				if ((c[i + 1] - c[i]) != 0.0)
					val = (_cin - c[i]) / (c[i + 1] - c[i])*(x[i + 1] - x[i]) + x[i];
				else
					val = (x[i + 1] + x[i]) / 2.0;
				return val;
			}
		}
		cout << " error in getXboundaryValue " << endl;
		exit(0);
	}
	inline int getInterval(vector<REAL>& x, REAL xval, bool useoutofrange=true)
	{
		int val = 0;

		if (x.size() < 2)
		{
			cout << " number of interval should be >= 2 " << endl;
			exit(0);
		}

		if (useoutofrange == false)
		{
			if (xval < x[0] || xval > x.back())
			{
				cout << " out of range in int getInterval " << endl;
				exit(0);
			}
		}

		if (xval < x[0]) val = 0;
		else if (xval >= x.back()) val = x.size()-2;
		else
		{
#if 0
			for (int i = 0; i < static_cast<int>(x.size()) - 1; i++)
			{
				if (xval >= x[i] && xval < x[i + 1])
					val = i;
			}
#else
			vector <REAL>::iterator it;
			it = upper_bound(x.begin(), x.end(), xval);
			if (it == x.begin()) it++;
			if (it == x.end()) it--;
			it--;
			val = it - x.begin();
#endif
		}

		return val;
	}
	inline int getIntervalQuadratic(vector<REAL>& x, REAL xval, bool useoutofrange = true)
	{
		int val = 0;

		if (x.size() < 3)
		{
			cout << " number of interval should be >= 3 " << endl;
			exit(0);
		}

		if (useoutofrange == false)
		{
			if (xval < x[0] || xval > x.back())
			{
				cout << " out of range in int getInterval " << endl;
				exit(0);
			}
		}
		else
		{
			if (xval < x[0]) val = 0;
			else if (xval > x[x.size()-3]) val = x.size() - 3;
			else
			{
				for (int i = 0; i < static_cast<int>(x.size()) - 2; i++)
				{
					if (xval >= x[i] && xval <= x[i + 1])
						val = i;
				}
			}
		}

		return val;
	}
	inline REAL do2ndLagrangeInterpolation(REAL x, REAL x0, REAL x1, REAL x2, REAL y0, REAL y1, REAL y2)
	{
		REAL dx0 = (x - x0);
		REAL dx1 = (x - x1);
		REAL dx2 = (x - x2);
		REAL dx01 = (x0 - x1);
		REAL dx02 = (x0 - x2);
		REAL dx12 = (x1 - x2);

		REAL y = dx1 * dx2 / (dx01 * dx02) * y0
			+ dx0 * dx2 / (-dx01 * dx12) * y1
			+ dx0 * dx1 / ( dx02 * dx12) * y2;

		return y;
	}
	inline REAL doInterporationFromVector(int intt, vector<REAL>& x, vector<REAL>& y, REAL xval, int extraporation)
	{
		REAL val;

		int ibase = getInterval(x, xval, true);
		if ((x[ibase + 1] + x[ibase]) == 0.0)
		{
			cout << " error in doInterporationFromVector " << endl;
			exit(0);
		}
		REAL eps = abs((x[ibase + 1] - x[ibase]) / (x[ibase + 1] + x[ibase]));
		if (eps < 1.0e-10) intt = 1;	//force to histgram interporation to prevent nan

		if (intt == 1)
			val = y[ibase];
		else if (intt == 2)
			val = (xval - x[ibase]) / (x[ibase + 1] - x[ibase])*(y[ibase + 1] - y[ibase]) + y[ibase];
		else
		{
			cout << " error in doInterporationFromVector " << endl;
			exit(0);
		}

		if (extraporation == eExtraporationConst)
		{
			if (xval < x[0]) val = y[0];
			if (xval > x.back()) val = y.back();
		}
		else if (extraporation == eExtraporationZero)
		{
			if (xval < x[0]) val = 0.0;
			if (xval > x.back()) val = 0.0;
		}

		return val;
	}
	inline REAL cubicHermiteSpline00(REAL t)
	{
		REAL val = 2.0 * t * t * t - 3.0 * t * t + 1.0;
		return val;
	}
	inline REAL cubicHermiteSpline10(REAL t)
	{
		REAL val = t * t * t - 2.0 * t * t + t;
		return val;
	}
	inline REAL cubicHermiteSpline01(REAL t)
	{
		REAL val = -2.0 * t * t * t + 3.0 * t * t;
		return val;
	}
	inline REAL cubicHermiteSpline11(REAL t)
	{
		REAL val = t * t * t - t * t;
		return val;
	}
	inline REAL doMonotoneCubicInterpolation(vector<REAL>& x, vector<REAL>& y, REAL xval)
	{
		int maxnum = x.size();
		vector<REAL> delta(maxnum);
		for (int i = 0; i < maxnum - 1; i++)
			delta[i] = (y[i + 1] - y[i]) / (x[i + 1] - x[i]);

		vector<REAL> m(maxnum);
		m[0] = delta[0];
		for (int i = 1; i < maxnum - 1; i++)
		{
			if (delta[i - 1] * delta[i] < 0.0)
				m[i] = 0.0;
			else
				m[i] = (delta[i - 1] + delta[i]) / 2.0;
		}
		m[maxnum - 1] = delta[maxnum - 2];

		for (int i = 1; i < maxnum - 1; i++)
		{
			if (delta[i] == 0.0)
			{
				m[i] = 0.0;
				m[i + 1] = 0.0;
			}
		}

		REAL alpha, beta;
		for (int i = 0; i < maxnum - 1; i++)
		{
			alpha = m[i] / delta[i];
			beta = m[i + 1] / delta[i];
			REAL val = alpha * alpha + beta * beta;
			if (val > 9.0)
			{
				REAL tau = 3.0 / sqrt(val);
				m[i] = tau * alpha * delta[i];
				m[i + 1] = tau * beta * delta[i];
			}
		}

		int k = getInterval(x, xval);
		REAL d = x[k + 1] - x[k];
		REAL t = (xval - x[k]) / d;
		REAL val = y[k] * cubicHermiteSpline00(t) + d * m[k] * cubicHermiteSpline10(t) + y[k + 1] * cubicHermiteSpline01(t) + d * m[k + 1] * cubicHermiteSpline11(t);

		return val;
	}
	inline void deleteThinInterval(vector<REAL>& vec)
	{
		std::sort(vec.begin(), vec.end(), std::greater<REAL>());
		vector<REAL> vec_wk;
		vec_wk.clear();
		for (int ie = 0; ie < static_cast<int>(vec.size()) - 1; ie++)
		{
			REAL eps = abs(vec[ie] - vec[ie + 1]) / (vec[ie] + vec[ie + 1]);
			if (eps > 1.0e-8)
				vec_wk.push_back(vec[ie]);
		}
		vec_wk.push_back(vec.back());
		vec.clear();
		for (int ie = 0; ie < static_cast<int>(vec_wk.size()); ie++)
			vec.push_back(vec_wk[ie]);
	}
	inline REAL calcThermalIncoherentScatteringXSFreeGasAngleIntegratedA1(REAL xsf, REAL ein, REAL eout, REAL temp)
	{
		REAL val = 0.0;
		REAL kt = BOLTZMANN_CONSTANT * temp;
		if (eout > ein)
		{
			val = exp((ein - eout) / kt) * erf(sqrt(ein / kt));
		}
		else
		{
			val = erf(sqrt(eout / kt));
		}

		val *= xsf / ein;

		return val;
	}
	inline void calcThermalIncoherentScatteringXSFreeGasAngleIntegratedP3(int pl, REAL xsf, REAL aw, REAL ein, REAL eout, REAL temp, vector<REAL>& coef)
	{
		for (int il = 0; il <= pl; il++)
			coef[il] = 0.0;

		REAL bfact = (aw + 1.0)*(aw + 1.0) / (aw*aw);

		REAL kt = BOLTZMANN_CONSTANT*temp;
		REAL akt = aw*kt;
		REAL a = (eout + ein) / akt;
		REAL b = 2.0*sqrt(eout*ein) / akt;
		REAL c = sqrt(eout / ein) / (2.0*kt*sqrt(4.0*PI));
		REAL bt = (eout - ein) / kt;

		if (b > a) b = a;
		REAL d1 = sqrt(a - b);
		REAL d2 = sqrt(a + b);
		REAL d7 = fabs(bt);
		REAL d20 = erf((d1 - aw*d2) / 2.0);
		REAL d21 = erf((d1 + aw*d2) / 2.0);
		REAL d22 = erf((d2 - aw*d1) / 2.0);
		REAL d23 = erf((d2 + aw*d1) / 2.0);
		//REAL d20md22wk = d20 - d22;
		//REAL d21md23wk = d21 - d23;
		REAL d20md22 = erf((d1 - aw*d2) / 2.0) - erf((d2 - aw*d1) / 2.0);
		REAL d21md23;
		if ((d1 + aw*d2) > 2.0 || (d2 + aw*d1) > 2.0)
			d21md23 = -(erfc((d1 + aw*d2) / 2.0) - erfc((d2 + aw*d1) / 2.0));
		else
			d21md23 =   erf((d1 + aw*d2) / 2.0) - erf((d2 + aw*d1) / 2.0);

		REAL fact = - c / b * sqrt(PI) * (d20md22 * exp((-bt - d7) / 2.0) + d21md23 * exp((-bt + d7) / 2.0));
		coef[0] = xsf * bfact * fact;

		if (pl == 0) return;

		REAL d3 = -((aw*aw + 1.0)*a - (aw*aw - 1.0)*b + 2.0*bt) / 4.0;
		d3 = exp(d3);
		REAL d4 = -((aw*aw + 1.0)*a + (aw*aw - 1.0)*b + 2.0*bt) / 4.0;
		d4 = exp(d4);
		REAL d5 = (-bt + d7)/2.0;
		d5 = exp(d5);
		REAL d6 = (-bt - d7) / 2.0;
		d6 = exp(d6);
		fact = (c*(4 * (d2*d3 - d1*d4) - ((d20 - d22)*d6*(-2 + a - d7) +
			(d21 - d23)*d5*(-2 + a + d7))*sqrt(PI))) / (b*b);
		coef[1] = xsf * bfact * fact;

		if (pl == 1) return;

		fact = (c*(12 * (-6 + a - b)*d2*d3 - 12 * (-6 + a + b)*d1*d4 +
			sqrt(PI)*(d21md23*d5*
			(-36 + b*b - 3 * bt*bt + 18 * d7 -
				3 * a*(-4 + a + 2 * d7)) +
				d20md22*d6*(b*b +
					3 * a*(4 - a + 2 * d7) -
					3 * (12 + bt*bt + 6 * d7))))) /
					(2.*b*b*b);
		coef[2] = xsf * bfact * fact;

		if (pl == 2) return;

		fact = (c*(-(d20md22*d6*sqrt(PI)*
			(3 * (-5 * (20 + (-6 + a)*a) + b*b)*d7 - 5 * d7*d7*d7 +
				6 * (b*b - 10 * (10 + d7*d7)) +
				a*(5 * (-6 + a)*a - 3 * b*b + 15 * (12 + d7*d7))))\
			- d21md23*d5*sqrt(PI)*
			(3 * (100 + 5 * (-6 + a)*a - b*b)*d7 + 5 * d7*d7*d7 +
				6 * (b*b - 10 * (10 + d7*d7)) +
				a*(5 * (-6 + a)*a - 3 * b*b + 15 * (12 + d7*d7))) +
			4 * (-(d1*d4*(5 * a*a + 5 * a*(-8 + b) + 2 * (-25 + b)*b +
				5 * (60 + d7*d7))) +
				d2*d3*(5 * a*a - 5 * a*(8 + b) + 2 * b*(25 + b) +
					5 * (60 + d7*d7))))) / (2.*b*b*b*b);

		coef[3] = xsf * bfact * fact;
	#if 0
		for (int il = 0; il <= pl; il++)
		{
			if (std::isnan(coef[il]) == true)
			{
				cout << il << endl;
				cout << setw(12) << scientific << setprecision(16) << a << endl;
				cout << setw(12) << scientific << setprecision(16) << b << endl;
				cout << setw(12) << scientific << setprecision(16) << c << endl;
				cout << setw(12) << scientific << setprecision(16) << bt << endl;
				cout << setw(12) << scientific << setprecision(16) << d1 << endl;
				cout << setw(12) << scientific << setprecision(16) << d2 << endl;
				cout << setw(12) << scientific << setprecision(16) << d3 << endl;
				cout << setw(12) << scientific << setprecision(16) << d4 << endl;
				cout << setw(12) << scientific << setprecision(16) << d5 << endl;
				cout << setw(12) << scientific << setprecision(16) << d6 << endl;
				cout << setw(12) << scientific << setprecision(16) << d7 << endl;
				cout << setw(12) << scientific << setprecision(16) << d20 << endl;
				cout << setw(12) << scientific << setprecision(16) << d21 << endl;
				cout << setw(12) << scientific << setprecision(16) << d22 << endl;
				cout << setw(12) << scientific << setprecision(16) << d23 << endl;
				cout << setw(12) << scientific << setprecision(16) << d20md22 << endl;
				cout << setw(12) << scientific << setprecision(16) << d21md23 << endl;
				cout << setw(12) << scientific << setprecision(16) << coef[il] << endl;
				exit(0);
			}
		}
	#endif

		return;
	}
	inline REAL getErfc(REAL a)
	{
		if (a > 26.0)
			return 0.0;		//to prevent underflow
		else
			return erfc(a);
	}
	inline REAL addErf(REAL a, REAL b)
	{
		//addition of error function value to prevent round-off error

		if (a * b >= 0.0)
		{
			REAL val = erf(a) + erf(b);
			return val;
		}
		else
		{
			REAL val = 0.0;
			if (a > 0.0)
				val = getErfc(-b) - getErfc(a);
			else
				val = getErfc(-a) - getErfc(b);
			return val;
		}
	}
	inline REAL calcThermalIncoherentScatteringXSFreeGasAngleIntegrated(REAL xsf, REAL aw, REAL ein, REAL eout, REAL temp)
	{
	#if 1
		REAL val = 0.0;
		REAL eta = (aw + 1.0) / (2.0*sqrt(aw));
		REAL xi  = (aw - 1.0) / (2.0*sqrt(aw));
		REAL kt = BOLTZMANN_CONSTANT * temp;
		REAL sei = sqrt(ein);
		REAL seo = sqrt(eout);
		REAL skt = sqrt(kt);
		REAL w1 = (eta * sei - xi * seo) / skt;
		REAL w2 = (eta * sei + xi * seo) / skt;
		REAL w3 = (eta * seo - xi * sei) / skt;
		REAL w4 = (eta * seo + xi * sei) / skt;

		if (eout > ein)
		{
			REAL wk12 = addErf(w1, w2);
			REAL wk34 = addErf(w3, -w4);
			if (wk12 == 0.0)
				val = wk34;
			else
				val = exp((ein - eout) / kt) * wk12 + wk34;
		}
		else
		{
			REAL wk12 = addErf(w1, -w2);
			REAL wk34 = addErf(w3, w4);
			if (wk12 == 0.0)
				val = wk34;
			else
				val = exp((ein - eout) / kt) * wk12 + wk34;
		}

		val *= xsf * eta * eta / (2.0*ein);
	#else
		vector<REAL> coef(1);
		calcThermalIncoherentScatteringXSFreeGasAngleIntegratedP3(0, xsf, aw, ein, eout, temp, coef);
		REAL val = coef[0];
	#endif

		return val;
	}
	inline REAL calcThermalIncoherentScatteringXSFreeGasAngleIntegratedAndEoutAveraged(REAL xsf, REAL aw, REAL ein, REAL eout_upper, REAL eout_lower, REAL temp)
	{
		REAL eout_ave = (eout_upper + eout_lower) / 2.0;
		REAL val0 = calcThermalIncoherentScatteringXSFreeGasAngleIntegrated(1.0, aw, ein, eout_lower, temp);
		REAL val1 = calcThermalIncoherentScatteringXSFreeGasAngleIntegrated(1.0, aw, ein, eout_upper, temp);
		REAL vala = calcThermalIncoherentScatteringXSFreeGasAngleIntegrated(1.0, aw, ein, eout_ave, temp);

		REAL du = log(eout_upper / eout_lower);

		//REAL eps_rel = 0.0;
		//if (vala != 0.0 && vala > XS_SMALL_RATIO)
		//	eps_rel = abs(((val0 + val1) / 2.0 - vala) / vala);
		REAL eps_dif = 0.0;
		eps_dif = abs((val0 + val1) / 2.0 - vala );

		REAL val;
		GaussLobattoQuadrature glq;
		if (eps_dif < THERMAL_SAB_INTEGRATE_TORELANCE * 0.1 || du < THERMAL_SAB_INTEGRATE_MIN_DELTA_LETHARGY)
		{
			val = glq.w3[0] * val0 + glq.w3[1] * vala + glq.w3[2] * val1;
			val /= 2.0;
		}
		else
		{
			val0 = calcThermalIncoherentScatteringXSFreeGasAngleIntegratedAndEoutAveraged(1.0, aw, ein, eout_ave, eout_lower, temp);
			val1 = calcThermalIncoherentScatteringXSFreeGasAngleIntegratedAndEoutAveraged(1.0, aw, ein, eout_upper, eout_ave, temp);
			val = (val0 + val1) / 2.0;
		}

		val *= xsf;

		return val;
	}
	inline REAL integrateKernelForThermalUpscattering(REAL el, REAL eu, REAL kt)
	{
		REAL val = (exp(-el / kt) - exp(-eu / kt)) * kt;

		return val;
	}
	inline REAL integrateEKernelForThermalUpscattering(REAL el, REAL eu, REAL kt)
	{
		REAL val = kt * (exp(-el / kt)*(el + kt) - exp(-eu / kt)*(eu + kt));

		return val;
	}
	inline REAL integrateKernelForThermalDownscattering(REAL el, REAL eu, REAL kt)
	{
		const GaussLegendreQuadrature gl;

		REAL val = 0.0;

		int NDIV = 5;

		REAL delta = (eu - el) / (REAL)NDIV;
		for (int i = 0; i < NDIV; i++)
		{
			REAL x0 = (eu - el) / (REAL)NDIV * (REAL)i + el;
			REAL x1 = x0 + delta;
			REAL a = (x1 - x0) / 2.0;
			REAL b = (x1 + x0) / 2.0;
			REAL wk = 0.0;
			for (int j = 0; j < 5; j++)
			{
				REAL x = a * gl.x5[j] + b;
				wk += gl.w5[j] * erf(sqrt(x / kt)) * a;
			}
			val += wk;
		}

		return val;
	}
	inline REAL integrateEKernelForThermalDownscattering(REAL el, REAL eu, REAL kt)
	{
		const GaussLegendreQuadrature gl;

		REAL val = 0.0;

		int NDIV = 5;

		REAL delta = (eu - el) / (REAL)NDIV;
		for (int i = 0; i < NDIV; i++)
		{
			REAL x0 = (eu - el) / (REAL)NDIV * (REAL)i + el;
			REAL x1 = x0 + delta;
			REAL a = (x1 - x0) / 2.0;
			REAL b = (x1 + x0) / 2.0;
			REAL wk = 0.0;
			for (int j = 0; j < 5; j++)
			{
				REAL x = a * gl.x5[j] + b;
				wk += gl.w5[j] * x * erf(sqrt(x / kt)) * a;
			}
			val += wk;
		}

		return val;
	}
	inline REAL integrationLAW11(REAL a, REAL b, REAL e)
	{
		REAL val =
			(pow(a, 1.5)*sqrt(b)*exp((a*b) / 4.)*
				sqrt(PI)*(-erf((a*sqrt(b) -
					2. * sqrt(e)) / (2.*sqrt(a))) +
					erf((a*sqrt(b) + 2. * sqrt(e)) /
					(2.*sqrt(a))))) / 4. -
						(a*sinh(sqrt(b)*sqrt(e))) / exp(e / a);

		return val;
	}
	inline bool isIndependentInelasticScattering(int mt)
	{
		if (mt >= 51 && mt <= 91) return true;
		else return false;
	}
	template<typename TYPE> void Pl(int l, TYPE x, TYPE* p)
	{
		p[0] = 1.0;
		if (l < 1) return;

		p[1] = x;
		if (l < 2) return;

		//TYPE dn;

		for (int n = 1; n < l; n++)
		{
			p[n + 1] = PL_COEFA[n] * x * p[n] - PL_COEFB[n] * p[n - 1];
		}
	}
	inline void checkPL_COEF()
	{
		for (int i = 0; i < MAX_PL + 1; i++)
		{
			REAL eps = fabs(PL_COEFA[i] - (2.0*(REAL)i + 1.) / ((REAL)i + 1.));
			eps += fabs(PL_COEFB[i] - (REAL)i / ((REAL)i + 1.));
			if (eps > 1.0e-10)
			{
				cout << " set PL_COEFA or PL_COEFB correctly in FMGenerator_global.h" << endl;
				exit(0);
			}
		}

	}
	inline REAL interporatePdf(vector<REAL>& mu_boundary, vector<REAL>& pdf, REAL muwk)
	{
		if (muwk < mu_boundary[0]) return 0.0;
		if (muwk > mu_boundary.back()) return 0.0;
		if (mu_boundary.size() <= 2) return (pdf[0]+pdf[1])/2.0;

		int ibase = 0;
#if 0
		for (int i = 0; i < static_cast<int>(mu_boundary.size()); i++)
		{
			if (muwk >= mu_boundary[i] && muwk <= mu_boundary[i + 1])
			{
				ibase = i;
				break;
			}
		}
		REAL wgt = (muwk - mu_boundary[ibase]) / (mu_boundary[ibase + 1] - mu_boundary[ibase]);
#else
		vector <REAL>::iterator it, it2;
		it = upper_bound(mu_boundary.begin(), mu_boundary.end(), muwk);
		if (it == mu_boundary.begin()) it++;
		if (it == mu_boundary.end()) it--;
		it2 = it;
		it2--;
		REAL wgt = (muwk - *it2) / (*it - *it2);
		ibase = it2 - mu_boundary.begin();
#endif
		REAL val = pdf[ibase] * (1.0 - wgt) + pdf[ibase + 1] * wgt;

		return val;
	}
	inline REAL interporatePdf(REAL* mu_boundary, REAL* pdf, int np, REAL muwk, int jj = 2)
	{
		if (muwk < mu_boundary[0]) return 0.0;
		if (muwk > mu_boundary[np-1]) return 0.0;
		if (np <= 2) return (pdf[0] + pdf[1]) / 2.0;

	#if 0
		static int ibase = 0;
		for (;;)
		{
			if (muwk >= mu_boundary[ibase] && muwk <= mu_boundary[ibase + 1])
				break;
			else if (muwk < mu_boundary[ibase])
				ibase--;
			else if (muwk > mu_boundary[ibase+1])
				ibase++;
			if (ibase < 0 || ibase > np - 2) return 0.0;
		}
	#else
		int ibase = 0;
		for (int i = 0; i < np-1; i++)
		{
			if (muwk >= mu_boundary[i] && muwk <= mu_boundary[i + 1])
			{
				ibase = i;
				break;
			}
		}
	#endif

		REAL wgt = (muwk - mu_boundary[ibase]) / (mu_boundary[ibase + 1] - mu_boundary[ibase]);

		//histgram interpolation when jj==1. Otherwise, linear interpolation
		if (jj == 1) wgt = 0.0;

		REAL val = pdf[ibase] * (1.0 - wgt) + pdf[ibase + 1] * wgt;

		return val;
	}
	inline void calcPlCoefficient(vector<REAL>& x, vector<REAL>& dx, vector<REAL>& y, vector<REAL>& coef, int max_pl)
	{
		coef.resize(max_pl+1);
		for (int i = 0; i <= max_pl; i++)
			coef[i] = 0.0;
		int mu_div = x.size();

		for (int ia = 0; ia < mu_div; ia++)
		{
			REAL p[MAX_PL + 1];
			for (int i = 0; i <= MAX_PL; i++)
				p[i] = 0.0;
			REAL mu = x[ia];
			Pl(max_pl, mu, p);
			for (int il = 0; il <= max_pl; il++)
				coef[il] += y[ia]* dx[ia] * p[il];
		}
	}
	inline REAL getKalbach87(REAL mu, REAL r, REAL a)
	{
		REAL val = 0.5 * (cosh(a*mu) + r*sinh(a*mu)) * a / sinh(a);
		return val;
	}
	inline void readMatrixFromDebugFile(string file_name, vector<vector<vector<REAL> > >& matrix, int max_ng, int max_pl)
	{
		//reset energy transfer matrix
		matrix.resize(max_ng);
		for (int ig = 0; ig < max_ng; ig++)
		{
			matrix[ig].resize(max_ng);
			for (int iig = 0; iig < max_ng; iig++)
			{
				matrix[ig][iig].resize(max_pl + 1);
				for (int il = 0; il <= max_pl; il++)
					matrix[ig][iig][il] = 0.0;
			}
		}

		ifstream ifs;
		ifs.open(file_name.c_str());
		string wk;
		ifs >> wk; ifs >> wk; ifs >> wk;
		ifs >> wk; ifs >> wk; ifs >> wk; ifs >> wk;
		for (int il = 0; il <= max_pl; il++)
		{
			ifs >> wk; ifs >> wk; ifs >> wk;
			for (int iig = 0; iig < max_ng; iig++)
			{
				int iwk;
				ifs >> iwk;
				for (int ig = 0; ig < max_ng; ig++)
					ifs >> matrix[ig][iig][il];
			}
		}
		ifs.close();
	}
	inline bool isFissionMT(int mt)
	{
		if (mt == eMTFission) return true;
		if (mt == eMTFirstChanceFission) return true;
		if (mt == eMTSecondChanceFission) return true;
		if (mt == eMTThirdChanceFission) return true;
		if (mt == eMTFourthChanceFission) return true;

		return false;
	}
	inline bool isThermalIncoherentInelastic(int mt)
	{
		switch (mt)
		{
		case 221:
		case 222:
		case 223:
		case 225:
		case 227:
		case 228:
		case 229:
		case 231:
		case 233:
		case 235:
		case 237:
		case 239:
		case 241:
		case 243:
		case 245:
		case 249:
			return true;
			break;

		default:
			return false;
		}
	}
	inline bool isThermalElastic(int mt)
	{
		switch (mt)
		{
			//incoherent elastic
		case 224:
		case 226:
		case 236:

			//coherent elastic
		case 230:
		case 232:
		case 234:
		case 238:
		case 240:
		case 242:
		case 244:
		case 246:

			//incoherent or coherent
		case 250:

			return true;
			break;

		default:
			return false;
		}
	}
	inline bool isThermalMT(int mt)
	{
		if (isThermalIncoherentInelastic(mt)) return true;
		if (isThermalElastic(mt)) return true;

		return false;
	}
	inline bool checkAcceptedThermalSabName(string type)
	{
		bool valid = true;
		if (compareString(type, "benz")) valid = false;
		if (compareString(type, "sio2",4)) valid = false;
		if (compareString(type, "beo")) valid = false;
		if (compareString(type, "c5o2h8")) valid = false;

		return valid;
	}
	inline string convertMT2MatxsName(int mt)
	{
		map<int, string> mt2name;

		mt2name[-1] = "ntot1";
		mt2name[ 1] = "ntot0";
		mt2name[ 2] = "nelas";
		mt2name[ 3] = "nnonel";
		mt2name[ 4] = "ninel";
		mt2name[ 5] = "nx";
		mt2name[ 6] = "n2n1";
		mt2name[ 7] = "n2n2";
		mt2name[ 8] = "n2n3";
		mt2name[ 9] = "n2n4";
		mt2name[16] = "n2n";
		mt2name[17] = "n3n";
		mt2name[18] = "nftot";
		mt2name[19] = "nf";
		mt2name[20] = "nnf";
		mt2name[21] = "n2nf";
		mt2name[22] = "nna";
		mt2name[23] = "nn3a";
		mt2name[24] = "n2na";
		mt2name[25] = "n3na";
		mt2name[26] = "n2ni";
		mt2name[28] = "nnp";
		mt2name[29] = "nn2a";
		mt2name[30] = "n2n2a";
		mt2name[32] = "nnd";
		mt2name[33] = "nnt";
		mt2name[34] = "nnh";
		mt2name[35] = "nnd2a";
		mt2name[36] = "nnt2a";
		mt2name[37] = "n4n";
		mt2name[38] = "n3nf";
		mt2name[41] = "n2np";
		mt2name[42] = "n3np";
		mt2name[44] = "nn2p";
		mt2name[45] = "nnpa";

		mt2name[51] = "n01";
		mt2name[52] = "n02";
		mt2name[53] = "n03";
		mt2name[54] = "n04";
		mt2name[55] = "n05";
		mt2name[56] = "n06";
		mt2name[57] = "n07";
		mt2name[58] = "n08";
		mt2name[59] = "n09";
		mt2name[60] = "n10";
		mt2name[61] = "n11";
		mt2name[62] = "n12";
		mt2name[63] = "n13";
		mt2name[64] = "n14";
		mt2name[65] = "n15";
		mt2name[66] = "n16";
		mt2name[67] = "n17";
		mt2name[68] = "n18";
		mt2name[69] = "n19";
		mt2name[70] = "n20";
		mt2name[71] = "n21";
		mt2name[72] = "n22";
		mt2name[73] = "n23";
		mt2name[74] = "n24";
		mt2name[75] = "n25";
		mt2name[76] = "n26";
		mt2name[77] = "n27";
		mt2name[78] = "n28";
		mt2name[79] = "n29";
		mt2name[80] = "n30";
		mt2name[81] = "n31";
		mt2name[82] = "n32";
		mt2name[83] = "n33";
		mt2name[84] = "n34";
		mt2name[85] = "n35";
		mt2name[86] = "n36";
		mt2name[87] = "n37";
		mt2name[88] = "n38";
		mt2name[89] = "n39";
		mt2name[90] = "n40";
		mt2name[91] = "ncn";

		mt2name[101] = "nabs";
		mt2name[102] = "ng";
		mt2name[103] = "np";
		mt2name[104] = "nd";
		mt2name[105] = "nt";
		mt2name[106] = "nh";
		mt2name[107] = "na";
		mt2name[108] = "n2a";
		mt2name[109] = "n3a";
		mt2name[111] = "n2p";
		mt2name[112] = "npa";
		mt2name[113] = "nt2a";
		mt2name[114] = "nd2a";
		mt2name[115] = "npd";
		mt2name[116] = "npt";
		mt2name[117] = "nda";

		mt2name[201] = "n.neut";
		mt2name[202] = "n.gam";
		mt2name[203] = "n.h1";
		mt2name[204] = "n.h2";
		mt2name[205] = "n.h3";
		mt2name[206] = "n.he3";
		mt2name[207] = "n.he4";

		mt2name[221] = "free";
		mt2name[222] = "hh2o";
		mt2name[223] = "poly";
		mt2name[224] = "poly$";
		mt2name[225] = "hzrh";
		mt2name[226] = "hzrh$";
		mt2name[227] = "benz";
		mt2name[228] = "dd2o";
		mt2name[229] = "graph";
		mt2name[230] = "graph$";
		mt2name[231] = "be";
		mt2name[232] = "be$";
		mt2name[233] = "bebeo";
		mt2name[234] = "bebeo$";
		mt2name[235] = "zrzrh";
		mt2name[236] = "zrzrh$";
		mt2name[237] = "obeo";
		mt2name[238] = "obeo$";
		mt2name[239] = "ouo2";
		mt2name[240] = "ouo2$";
		mt2name[241] = "uuo2";
		mt2name[242] = "uuo2$";
		mt2name[243] = "al";
		mt2name[244] = "al$";
		mt2name[245] = "fe";
		mt2name[246] = "fe$";
		mt2name[249] = "other";
		mt2name[250] = "other$";

		mt2name[251] = "mubar";
		mt2name[252] = "xi";
		mt2name[253] = "gamma";
		mt2name[258] = "mt258";		//average lethargy
		mt2name[259] = "invel";
		mt2name[301] = "heat";
		mt2name[443] = "kerma";
		mt2name[444] = "dame";

		mt2name[452] = "nutot";
		mt2name[455] = "nudel";
		mt2name[456] = "nupmt";
		mt2name[eMTChiTotal] = "chit";
		mt2name[eMTChiDelayed] = "chid";
		mt2name[eMTChiPrompt] = "chip";

		mt2name[eMTNWT0] = "nwt0";
		mt2name[eMTNWT1] = "nwt1";

		for (int i = 600; i < 649; i++)
		{
			stringstream ss;
			ss << "p" << setfill('0') << setw(2) << i - 600;
			mt2name[i] = ss.str();
		}
		mt2name[649] = "pcn";
		for (int i = 650; i < 699; i++)
		{
			stringstream ss;
			ss << "d" << setfill('0') << setw(2) << i - 650;
			mt2name[i] = ss.str();
		}
		mt2name[699] = "dcn";
		for (int i = 700; i < 749; i++)
		{
			stringstream ss;
			ss << "t" << setfill('0') << setw(2) << i - 700;
			mt2name[i] = ss.str();
		}
		mt2name[749] = "tcn";
		for (int i = 750; i < 799; i++)
		{
			stringstream ss;
			ss << "h" << setfill('0') << setw(2) << i - 750;
			mt2name[i] = ss.str();
		}
		mt2name[799] = "hcn";
		for (int i = 800; i < 849; i++)
		{
			stringstream ss;
			ss << "a" << setfill('0') << setw(2) << i - 800;
			mt2name[i] = ss.str();
		}
		mt2name[849] = "acn";
		for (int i = 875; i < 891; i++)
		{
			stringstream ss;
			ss << "2n" << setfill('0') << setw(2) << i - 875;
			mt2name[i] = ss.str();
		}
		mt2name[891] = "2ncn";

		if (mt2name.find(mt) == mt2name.end())
		{
			stringstream ss;
			ss << "mt";
			ss << setw(3) << mt;
			return ss.str();
		}

		return mt2name[mt];
	}
	inline void checkFloatMinMax(REAL& val)
	{
		if (val == 0.0) return;
		if (fabs(val) < FLT_MIN) val = FLT_MIN * val / fabs(val);
		if (fabs(val) > FLT_MAX) val = FLT_MAX * val / fabs(val);
		return;
	}
	inline bool cutSmallValueToTotal(REAL& val, REAL& total, REAL eps= XS_SMALL_RATIO)
	{
		bool cut = false;
		if (val == 0.0) return cut;
		if (total == 0.0) return cut;
		if (fabs(val) / fabs(total) < eps)
		{
			val = 0.0;
			cut = true;
		}
		return cut;
	}
	inline int getKeyValueForMCEDataStorage(int mt, int idw, int e)
	{
		if (e >= 100000)
		{
			cout << "number of energy grid to construct MCEData is too large" << endl;
			exit(0);
		}
		if (idw >= 10)
		{
			cout << "number of DLW set to construct MCEData is too large" << endl;
			exit(0);
		}
		int val = e + 100000 * idw + 1000000 * mt;
		return val;
	}
	inline int getNumberOfDivisionsInEnergyGroupDLWLaw44Law61(REAL eu, REAL el)
	{
		REAL du = 0.01;
		int n = (int) (log(eu / el) / du) + 1;

		const int MAX_DIV = 100;
		const int MIN_DIV = 5;
		if (n > MAX_DIV) n = MAX_DIV;
		if (n < MIN_DIV) n = MIN_DIV;

		return n;
	}
	inline int getNumberOfIntegrationPointsInEnergyGroup(REAL eh, REAL el, REAL du = 0.001)
	{
		const int MIN_NUM = 2;
		const int MAX_NUM = 1000;

		int num = (int)(log(eh / el) / du);

		if (num < MIN_NUM) num = MIN_NUM;
		if (num > MAX_NUM) num = MAX_NUM;

		return num;
	}
	inline int getNumberOfIntegrationPointsInEnergyGroupThermal(REAL eh, REAL el, REAL du = 0.001)
	{
		const int MIN_NUM_THERMAL = 10;
		const int MAX_NUM_THERMAL = 200;

		int num = (int)(log(eh / el) / du);

		if (num < MIN_NUM_THERMAL) num = MIN_NUM_THERMAL;
		if (num > MAX_NUM_THERMAL)
		{
			num = MAX_NUM_THERMAL;
		}

		return num;
	}
	inline void addEnergyBoundary(vector<REAL>& boundary, vector<REAL>& add_boundary)
	{
		std::sort(boundary.begin(), boundary.end(), std::greater<REAL>());
		REAL emax = boundary[0];
		REAL emin = boundary.back();
		for (int i = 0; i < static_cast<int>(add_boundary.size()); i++)
		{
			if (add_boundary[i] < emax && add_boundary[i] > emin)
				boundary.push_back(add_boundary[i]);
		}
		std::sort(boundary.begin(), boundary.end(), std::greater<REAL>());
	}
	inline void deleteNarrowEnergyBoundary(vector<REAL>& boundary, vector<REAL>& boundary_wk)
	{
		const REAL EPS_ENE = 1.0e-10;
		boundary.push_back(boundary_wk[0]);
		for (int i = 0; i < static_cast<int>(boundary_wk.size()) - 1; i++)
		{
			REAL eps = abs((boundary_wk[i + 1] - boundary_wk[i]) / boundary_wk[i]);
			if (eps > EPS_ENE)  boundary.push_back(boundary_wk[i + 1]);
		}
	}
	inline void subdivideEnergyBoundary(vector<REAL>& boundary, REAL du = 0.0)
	{
		int ebsize = boundary.size();
		for (int ie = 0; ie < ebsize - 1; ie++)
		{
			REAL e_upper = boundary[ie];
			REAL e_lower = boundary[ie + 1];
			int ndiv;

			if (du == 0.0)
				ndiv = getNumberOfIntegrationPointsInEnergyGroup(e_upper, e_lower);
			else
				ndiv = getNumberOfIntegrationPointsInEnergyGroup(e_upper, e_lower, du);

			for (int i = 1; i < ndiv; i++)
			{
				REAL eiwk = (log(e_upper) - log(e_lower)) / (REAL)ndiv*(REAL)i + log(e_lower);
				eiwk = exp(eiwk);
				boundary.push_back(eiwk);
			}
		}
		std::sort(boundary.begin(), boundary.end(), std::greater<REAL>());
	}
	inline int subdivideEnergyBoundaryThermal(vector<REAL>& boundary, REAL thermal_cutoff)
	{
		int ebsize = boundary.size();
		for (int ie = 0; ie < ebsize - 1; ie++)
		{
			REAL e_upper = boundary[ie];
			REAL e_lower = boundary[ie + 1];
			int ndiv = getNumberOfIntegrationPointsInEnergyGroupThermal(e_upper, e_lower);

			for (int i = 1; i < ndiv; i++)
			{
				REAL eiwk = (log(e_upper) - log(e_lower)) / (REAL)ndiv*(REAL)i + log(e_lower);
				eiwk = exp(eiwk);
				boundary.push_back(eiwk);
			}
		}
		std::sort(boundary.begin(), boundary.end(), std::greater<REAL>());

		//check sufficient division or not
		int num = 0;
		for (int i = 0; i < (int) boundary.size(); i++)
		{
			if (boundary[i] < thermal_cutoff) num++;
		}

		const int NUM_THERMAL_DIV = 3000;
		if (num < NUM_THERMAL_DIV)
		{
			int ndiv = NUM_THERMAL_DIV / num;
			if (ndiv < 2) ndiv = 2;
			ebsize = boundary.size();
			for (int ie = 0; ie < ebsize - 1; ie++)
			{
				REAL e_upper = boundary[ie];
				REAL e_lower = boundary[ie + 1];

				for (int i = 1; i < ndiv; i++)
				{
					REAL eiwk = (log(e_upper) - log(e_lower)) / (REAL)ndiv * (REAL)i + log(e_lower);
					eiwk = exp(eiwk);
					boundary.push_back(eiwk);
				}
			}
			std::sort(boundary.begin(), boundary.end(), std::greater<REAL>());
		}

		//recalculate number of integration points in thermal region
		num = 0;
		for (int i = 0; i < (int) boundary.size(); i++)
		{
			if (boundary[i] < thermal_cutoff) num++;
		}

		return num;

	}
	inline string my_to_string(int val)
	{
		std::ostringstream stm;
		stm << val;
		return stm.str();
	}
	inline string my_to_string(REAL val)
	{
		std::ostringstream stm;
		stm << val;
		return stm.str();
	}
	inline int my_stoi(string str)
	{
		std::istringstream stm(str);

		int val;
		stm >> val;
		if (!stm)
		{
			cout << " error in my_stoi " << endl;
			exit(0);
		}

		return val;
	}
	inline REAL my_stod(string str)
	{
		std::istringstream stm(str);

		REAL val;
		stm >> val;
		if (!stm)
		{
			cout << " error in my_stod " << endl;
			exit(0);
		}

		return val;
	}
	inline void skipACE20XHeader(ifstream& fin)
	{
		int sta = static_cast<int> (fin.tellg());
		string buf;
		vector<string> buf_vec;
		getline(fin, buf);
		if (compareString(buf, "2.", 2) == true)
		{
			//2.0.x style
			getline(fin, buf);
			splitToToken(buf, buf_vec);
			int wk = my_stoi(buf_vec[3]) - 2;
			for (int i = 0; i < wk; i++)
				getline(fin, buf);
		}
		else
		{
			fin.seekg(sta);
		}
		return;
	}
	inline int readIZAWFromACEFile(string fname)
	{
		//open ACE file
		ifstream fin;
		fin.open(fname.c_str());
		if (!fin)
		{
			cout << " Error while open ACE file " << fname << endl;
			exit(0);
		}

		//read title part
		string buf;
		vector<string> buf_vec;
		skipACE20XHeader(fin);
		for (int i = 0; i < 2; i++)
			getline(fin, buf);

		//read first part of izaw array
		getline(fin, buf);
		splitToToken(buf, buf_vec);
		int id = my_stoi(buf_vec[0]);

		fin.close();

		return id;
	}
	inline bool isMTIncluded(int mt, vector<int> mt_vec)
	{
		mt = abs(mt);

		for (int i = 0; i < static_cast<int>(mt_vec.size()); i++)
		{
			if (mt == mt_vec[i]) return true;
			if (i >= 1 && mt_vec[i] < 0)
			{
				if (mt >= abs(mt_vec[i - 1]) && mt <= abs(mt_vec[i])) return true;
			}
		}

		return false;
	}
	inline bool isZero1dXS(vector<REAL>& vec)
	{
		REAL sum = 0.0;
		for (int i = 0; i < static_cast<int>(vec.size()); i++)
			sum += vec[i];

		if (sum == 0.0)
			return true;
		else
			return false;
	}
	inline REAL calcFlux(REAL& st, REAL& sigb, REAL& src)
	{
		REAL val = src / (st + sigb);
		return val;
	}
	inline bool checkZaidForRUC(string zaid1, string zaid2)
	{
		for (int i = 0; i < (int) zaid1.length(); i++)
		{
			if (zaid1[i] == '.' && zaid2[i] == '.') return true;
			if (zaid1[i] != zaid2[i]) break;
		}
		return false;
	}
	inline REAL heaviside(REAL val)
	{
		if (val < 0.0) return 0.0;
		else if (val > 0.0) return 1.0;
		else return 0.5;
	}
	inline REAL calcGpRUC(REAL x, REAL y, REAL t)
	{
		REAL wk = (t + x) * (t + x);
		REAL val = exp(-wk) * (t + x - 2.0 * (y * y - t * t) * (t - x));
		return val;
	}
	inline REAL calcGmRUC(REAL x, REAL y, REAL t)
	{
		REAL wk = (t - x) * (t - x);
		REAL val = exp(-wk) * (t - x - 2.0 * (y * y - t * t) * (t + x));
		return val;
	}
	inline void calcPsiRUC(REAL t, REAL tp, REAL tm, REAL epsmax, REAL epsmin, REAL& p0, REAL& p1)
	{
		//p0
		REAL wk1 = t + epsmin;
		REAL wk2 = epsmax - t;
		REAL wk3 = t - epsmin;
		REAL wk4, wk5;

		if (wk1 * wk2 > 0)
			wk4 = erfc(wk2) - erfc(wk1);
		else
			wk4 = erf(wk1) - erf(wk2);

		if (wk1 * wk3 > 0)
			wk5 = erfc(wk3) - erfc(wk1);
		else
			wk5 = erf(wk1) - erf(wk3);

		p0 = heaviside(tp - t) * heaviside(t - tm) * wk4 + heaviside(t - tp) * wk5;

		//p1
		const REAL spi = sqrt(PI);
		const REAL spiinv = 1.0 / sqrt(PI);

		REAL emax2 = epsmax * epsmax;
		REAL emin2 = epsmin * epsmin;
		REAL t2 = t * t;
		REAL rho = spi * (emax2 + emin2 - 2.0 * t2 + 0.5 - 2.0 * (emax2 - t2) * (emin2 - t2));
		REAL gp = calcGpRUC(epsmin, epsmax, t);
		REAL gm1 = calcGmRUC(epsmax, epsmin, t);
		REAL gm2 = calcGmRUC(epsmin, epsmax, t);

		REAL wk6 = rho * p0;
		REAL wk7 = -heaviside(tp - t) * heaviside(t - tm) * (gp + gm1) - heaviside(t - tp) * (gp - gm2);
		p1 = 0.25 * spiinv / (epsmax * epsmin) * (wk6 + wk7);
	}

}
