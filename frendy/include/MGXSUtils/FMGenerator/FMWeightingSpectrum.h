//-----------------------------------------------------
// FMWeightingSpectrum.h : weighting spectrum
//        
//-----------------------------------------------------

#pragma once
#include "FMGenerator_global.h"
#include "FMZlib.h"

namespace FMGen
{
	enum
	{
		eSpectrumIE,
		eSpectrumIEFisMaxwell,
		eSpectrumInput,
		eSpectrumNotDefined
	};
	class FMWeightingSpectrum
	{
	private:
		int						spec_opt;
		int						max_ng;
		REAL					ene_upper;
		REAL					ene_lower;
		REAL					fission_spectrum_temperature;
		REAL					maxwell_temperature;
		REAL					thermal_cutoff;
		REAL					fission_spectrum_cutoff;
		vector<REAL>			ene_grid;		//energy in descending order
		vector<REAL>			flux;			//[max_ng]

	public:
		FMWeightingSpectrum()
		{
			clear();
		};
		~FMWeightingSpectrum()
		{
		};

		void clear()
		{
			spec_opt = eSpectrumNotDefined;
			max_ng = 0;
			ene_upper = 0.0;
			ene_lower = 0.0;
			fission_spectrum_temperature = 0.0;
			maxwell_temperature = 0.0;
			thermal_cutoff = 0.0;
			fission_spectrum_cutoff = 0.0;
			flux.clear();
			ene_grid.clear();
		};
		void setInputSpectrum(vector<REAL>& _ene_grid, vector<REAL>& _flux)
		{
			spec_opt = eSpectrumInput;

			max_ng = _flux.size();
			ene_grid.resize(max_ng);
			flux.resize(max_ng);

			if (_ene_grid[0] > _ene_grid.back())
			{
				for (int i = 0; i < max_ng; i++)
					ene_grid[i] = _ene_grid[i];
				for (int i = 0; i < max_ng; i++)
					flux[i] = _flux[i];
			}
			else
			{
				for (int i = 0; i < max_ng; i++)
					ene_grid[i] = _ene_grid[max_ng - 1 - i];
				for (int i = 0; i < max_ng; i++)
					flux[i] = _flux[max_ng - 1 - i];
			}
			ene_upper = ene_grid[0];
			ene_lower = ene_grid.back();

			checkSpectrum();
		}
		void setIEFisMaxwellSpectrum(REAL upper, REAL lower, REAL _fis_temp, REAL _maxwell_temp, REAL _fcut, REAL _tcut)
		{
			spec_opt = eSpectrumIEFisMaxwell;
			ene_upper = upper;
			ene_lower = lower;
			if (_fis_temp != 0.0)
				fission_spectrum_temperature = _fis_temp;
			else
				fission_spectrum_temperature = 1.6e+6;
			if (_maxwell_temp != 0.0)
				maxwell_temperature = _maxwell_temp;
			else
				maxwell_temperature = 300.0;
			if (_tcut != 0.0)
				thermal_cutoff = _tcut;
			else
				thermal_cutoff = 2.0 * BOLTZMANN_CONSTANT * maxwell_temperature * 2.0;
			if (_fcut != 0.0)
				fission_spectrum_cutoff = _fcut;
			else
				fission_spectrum_cutoff = 1.0e+6;

			checkSpectrum();
		}
		void setIESpectrum()
		{
			spec_opt = eSpectrumIE;
		}
		REAL getSpectrum(REAL ene)
		{
			switch (spec_opt)
			{
			case eSpectrumInput:
			{
				//user input
				if (ene > ene_upper)
				{
					REAL val = flux[0] * ene_upper / ene;
					return val;
				}
				if (ene < ene_lower)
				{
					REAL val = flux.back() * ene_lower / ene;
					return val;
				}

				if (ene_grid.size() <= 1) return flux[0];

				int ibase = -1;
				if (ene > ene_grid[0]) ibase = 0;
				else if (ene < ene_grid.back()) ibase = max_ng - 2;
				else
				{
					for (int i = 0; i < max_ng - 1; i++)
					{
						if (ene <= ene_grid[i] && ene >= ene_grid[i + 1])
						{
							ibase = i;
							break;
						}
					}
				}
				if (ibase < 0)
				{
					cout << " error in getSpectrum " << endl;
					exit(0);
				}
				REAL wgt = (ene - ene_grid[ibase + 1]) / (ene_grid[ibase] - ene_grid[ibase + 1]);
				REAL val = flux[ibase] * wgt + flux[ibase + 1] * (1.0 - wgt);

				if (val < 0.0) val = 0.0;

				return val;
				break;
			}
			case eSpectrumIE:
				//1/E
				return 1 / ene;
				break;
			case eSpectrumIEFisMaxwell:
			{
				if (ene > ene_upper)
				{
					REAL val = getSpectrum(ene_upper) * ene_upper / ene;
					return val;
				}
				if (ene < ene_lower)
				{
					REAL val = getSpectrum(ene_lower) * ene_lower / ene;
					return val;
				}

				//Fission specrum + 1/E + Maxwell
				REAL val0 = sqrt(fission_spectrum_cutoff) * exp(-fission_spectrum_cutoff / fission_spectrum_temperature);
				REAL val1 = 1 / fission_spectrum_cutoff;
				REAL val2 = thermal_cutoff * exp(-thermal_cutoff / maxwell_temperature / BOLTZMANN_CONSTANT);
				REAL val3 = 1 / thermal_cutoff;
				REAL fact0 = val1 / val0;
				REAL fact1 = val3 / val2;
				REAL val = 0.0;
				if (ene >= fission_spectrum_cutoff)
				{
					val = sqrt(ene) * exp(-ene / fission_spectrum_temperature) * fact0;
				}
				else if (ene < fission_spectrum_cutoff && ene >= thermal_cutoff)
				{
					val = 1 / ene;
				}
				else
				{
					val = ene * exp(-ene / maxwell_temperature / BOLTZMANN_CONSTANT) * fact1;
				}

				return val;
				break;
			}
			default:
				cout << " error in getSpectrum " << endl;
				exit(0);
			}

		}
		void checkSpectrum()
		{
			if (spec_opt == eSpectrumIE) return;

			const int div = 1000;
			for (int i = 0; i <= div; i++)
			{
				REAL ene = (log(ene_upper) - log(ene_lower)) / (REAL)div * (REAL)i + log(ene_lower);
				ene = exp(ene);
				REAL val = getSpectrum(ene);
				if (std::isfinite(val) == false)
				{
					cout << " Energy for weighting spectrum calculation : " << ene << endl;
					printError(" Weighting spectrum is inf/nan/nan(ind). Check input of weighting spectrum. Consider use default value (0.0) for thermal cutoff in default_spectrum");
				}
				if (val <= 0.0)
				{
					cout << " Energy for weighting spectrum calculation : " << ene << endl;
					printError(" Weighting spectrum is zero");
				}
			}
		}
		void test(vector<REAL> ene_boundary)
		{
			ofstream of;
			of.open("debug.txt");
			setIEFisMaxwellSpectrum(ene_boundary[0], ene_boundary.back(), 0.0, 600.0, 0.0, 0.0);
			for (int i = 0; i < static_cast<int>(ene_boundary.size()) - 1; i++)
			{
				REAL ene = (log(ene_boundary[i]) + log(ene_boundary[i + 1])) / 2.0;
				ene = exp(ene);
				REAL val = getSpectrum(ene);
				of << setw(15) << scientific << setprecision(4) << ene;
				of << setw(15) << scientific << setprecision(4) << val;
				of << endl;
			}
			of.close();

		}
	};
}
