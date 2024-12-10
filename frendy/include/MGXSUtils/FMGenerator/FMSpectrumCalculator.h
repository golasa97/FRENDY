//-----------------------------------------------------
// FMSpectrumCalculator.h : perform ultra-fine group spectrum calc by NR or UFG
//        
//-----------------------------------------------------

#pragma once

#include "MGXSUtils/FMGenerator/FMDataContainer.h"

namespace FMGen
{
	class FMSpectrumCalculator
	{
	private:
		FMDataContainer* dc;

	public:

		FMSpectrumCalculator(FMDataContainer* _data_container);
		~FMSpectrumCalculator() {};

		void calcUFSpectrumHomo();

		void calcSlowingDownSource(vector<vector<REAL> >& micsc, REAL& sig_b,
			vector<REAL>& nuc_dens, REAL& nuc_dens_sum,
			vector<REAL>& alpha, REAL& alpha_b,
			vector<vector<int>*>& upper_fg, vector<int>& upper_fg_bg,
			vector<REAL>& flux, REAL& sfg_prev, REAL& sfg, int& ie);
		void calcSlowingDownSourceAlternative(vector<REAL>& sld_src, vector<vector<REAL> >& micsc, REAL& sig_b,
			vector<REAL>& nuc_dens, REAL& nuc_dens_sum,
			vector<REAL>& alpha, REAL& alpha_b,
			vector<vector<int>*>& upper_fg, vector<int>& upper_fg_bg,
			vector<REAL>& flux, REAL& sfg_prev, REAL& sfg, int& ie);
		REAL calcFlux(REAL& st, REAL& sigb, REAL& src)
		{
			REAL val = src / (st + sigb);
			return val;
		}
		void normalizeFlux(vector<REAL>& flux);
		void reportUFData();

	};
}

