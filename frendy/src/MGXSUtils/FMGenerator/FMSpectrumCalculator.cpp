#pragma once

#include "MGXSUtils/FMGenerator/FMSpectrumCalculator.h"

using namespace FMGen;

FMSpectrumCalculator::FMSpectrumCalculator(FMDataContainer* _data_container)
{
	dc = _data_container;
}
void FMSpectrumCalculator::reportUFData()
{
	dc->dumpUFFlux();
	dc->dumpUFSlowingdownSource();
	dc->dumpUFTotalSource();
	dc->dumpUFSigTotal();
}
void FMSpectrumCalculator::calcUFSpectrumHomo( )
{
	//source option
	bool slowing_down = true;
	if (dc->sld_calc_option == eFMNarrowResonanceCalc) slowing_down = false;

	//alpha for bg cross sections
	REAL aw = dc->moderator_aw;
	REAL alpha_b = (aw - 1)*(aw - 1) / ((aw + 1)*(aw + 1));

	string bgaw = my_to_string(dc->moderator_aw);
	vector<int>& upper_fg_bg = dc->uf_slowdown_upper_group[bgaw];

	//set background xs
	vector<REAL> bg_xs = dc->background_xs_set;

	//flux calculations
	UFRegionData& ufr = dc->uf_region_data;
	for (int ib = 0; ib < static_cast<int>(bg_xs.size()); ib++)
	{
		REAL sfg_prev=0.0, sfg=0.0;
		for (int ie = 0; ie < dc->uf_max_num_energy; ie++)
		{

			REAL ene = dc->uf_energy_midpoint[ie];

			//source 
			REAL src, src_nr;
			REAL sigb = bg_xs[ib] * dc->uf_region_data.nuc_dens_sum;
			if (slowing_down)
			{
#if 1
				//using recurrent formula (Handbook of Nuclear Engineering, Chap.9, Eq.(199)
				calcSlowingDownSource(ufr.micsc[ib], bg_xs[ib], ufr.nuc_dens, ufr.nuc_dens_sum, ufr.alpha,
					alpha_b, ufr.upper_fg, upper_fg_bg, dc->uf_flux[ib], sfg_prev, sfg, ie);	//elastic scattering
				sfg_prev = sfg;
				src = sfg + dc->fixed_source.getChiUFG(ie);	//fission source
				dc->uf_flux[ib][ie] = calcFlux(ufr.macst[ib][ie], sigb, src);
				dc->uf_sld_source[ib][ie] = sfg;
				dc->uf_source[ib][ie] = src;
				ufr.macst_macsb[ie] = ufr.macst[ib][ie] + sigb;
#else
				//using slowing down formula (Handbook of Nuclear Engineering, Chap.9, Eq.(191)
				sfg = dc->uf_sld_source[ib][ie];
				src = sfg + dc->fixed_source.getChiUFG(ie);	//fission source
				dc->uf_flux[ib][ie] = calcFlux(ufr.macst[ib][ie], sigb, src);
				dc->uf_source[ib][ie] = src;
				ufr.macst_macsb[ie] = ufr.macst[ib][ie] + sigb;
				calcSlowingDownSourceAlternative(dc->uf_sld_source[ib], ufr.micsc[ib], bg_xs[ib], ufr.nuc_dens, ufr.nuc_dens_sum,
					ufr.alpha, alpha_b, ufr.upper_fg, upper_fg_bg, dc->uf_flux[ib], sfg_prev, sfg, ie);	//elastic scattering
#endif
			}
			//NR approximation ... always calculate
#if 0
			src_nr = bg_xs[ib] * ufr.nuc_dens_sum / ene;
#else
			src_nr = bg_xs[ib] * ufr.nuc_dens_sum * dc->weighting_spectrum.getSpectrum(ene);
#endif
			ufr.macst_macsb[ie] = ufr.macst[ib][ie] + sigb;
			dc->uf_flux_nr[ib][ie] = calcFlux(ufr.macst[ib][ie], sigb, src_nr);
			if (slowing_down == false)
			{
				dc->uf_source[ib][ie] = src_nr;
				dc->uf_flux[ib][ie] = dc->uf_flux_nr[ib][ie];
			}
		}

		normalizeFlux(dc->uf_flux[ib]);
		normalizeFlux(dc->uf_flux_nr[ib]);
		for (int ie = 0; ie < static_cast<int>(ufr.macst_macsb.size()); ie++)
			dc->uf_sig_total_sigb[ib][ie] = ufr.macst_macsb[ie];
	}
	for (int ib = 0; ib < static_cast<int>(ufr.macst.size()); ib++)
		for (int ie = 0; ie < static_cast<int>(ufr.macst[ib].size()); ie++)
			dc->uf_sig_total[ib][ie] = ufr.macst[ib][ie];
}
void FMSpectrumCalculator::calcSlowingDownSource(vector<vector<REAL> >& micsc, REAL& sig_b,
	vector<REAL>& nuc_dens, REAL& nuc_dens_sum,
	vector<REAL>& alpha, REAL& alpha_b,
	vector<vector<int>*>& upper_fg, vector<int>& upper_fg_bg,
	vector<REAL>& flux, REAL& sfg_prev, REAL& sfg, int& ie)
{
	//1st energy group
	sfg = 0.0;
	if (ie == 0) return;

	//from 2nd to last energy groups using recurrent relation
	sfg = sfg_prev;

	//actual nuclides
	for (int in = 0; in < static_cast<int>(nuc_dens.size()); in++)
	{
		//addition from previous fine group
		int j = ie - 1;
		if ((*upper_fg[in])[ie] <= j)
		{
			REAL val = micsc[in][j] * nuc_dens[in] * flux[j] * dc->uf_energy_delta[j];
			val /= ((1.0 - alpha[in]) * dc->uf_energy_midpoint[j]);
			sfg += val;
		}
		int jsta, jend;
		jsta = (*upper_fg[in])[ie - 1];
		jend = (*upper_fg[in])[ie];
		for (int j = jsta; j < jend; j++)
		{
			REAL val = micsc[in][j] * nuc_dens[in] * flux[j] * dc->uf_energy_delta[j];
			val /= ((1.0 - alpha[in]) * dc->uf_energy_midpoint[j]);
			sfg -= val;
		}
	}

	if (sig_b == 0.0) return;

	//background cross section
	//addition from previous fine group
	int j = ie - 1;
	if (upper_fg_bg[ie] <= j)
	{
		REAL val = sig_b * nuc_dens_sum * flux[j] * dc->uf_energy_delta[j];
		val /= ((1.0 - alpha_b) * dc->uf_energy_midpoint[j]);
		sfg += val;
	}
	int jsta, jend;
	jsta = upper_fg_bg[ie - 1];
	jend = upper_fg_bg[ie];
	for (int j = jsta; j < jend; j++)
	{
		REAL val = sig_b * nuc_dens_sum * flux[j] * dc->uf_energy_delta[j];
		val /= ((1.0 - alpha_b) * dc->uf_energy_midpoint[j]);
		sfg -= val;
	}

}
void FMSpectrumCalculator::calcSlowingDownSourceAlternative(vector<REAL>& sld_src, vector<vector<REAL> >& micsc, REAL& sig_b,
	vector<REAL>& nuc_dens, REAL& nuc_dens_sum,
	vector<REAL>& alpha, REAL& alpha_b,
	vector<vector<int>*>& upper_fg, vector<int>& upper_fg_bg,
	vector<REAL>& flux, REAL& sfg_prev, REAL& sfg, int& ie)
{
	if (ie >= dc->uf_max_num_energy-1) return;

	//actual nuclides
	for (int in = 0; in < static_cast<int>(nuc_dens.size()); in++)
	{
		REAL val = micsc[in][ie] * nuc_dens[in] * flux[ie] * dc->uf_energy_delta[ie];
		REAL ecur = dc->uf_energy_midpoint[ie];
		REAL elow = alpha[in] * ecur;
		for (int j = ie + 1; j < dc->uf_max_num_energy; j++)
		{
			if (dc->uf_energy_midpoint[j] > elow)
				sld_src[j] += val / (ecur - elow);
		}
	}

	if (sig_b == 0.0) return;

	//background cross section
	REAL val = sig_b * nuc_dens_sum * flux[ie] * dc->uf_energy_delta[ie];
	REAL ecur = dc->uf_energy_midpoint[ie];
	REAL elow = alpha_b * ecur;
	for (int j = ie + 1; j < dc->uf_max_num_energy; j++)
	{
		if (dc->uf_energy_midpoint[j] > elow)
			sld_src[j] += val / (ecur - elow);
	}
}
void FMSpectrumCalculator::normalizeFlux(vector<REAL>& flux)
{
	DOUBLE sum = 0.0;
	for (int ie = 0; ie < dc->uf_max_num_energy; ie++)
		sum += flux[ie] * dc->uf_energy_delta[ie];
	for (int ie = 0; ie < dc->uf_max_num_energy; ie++)
		flux[ie] /= sum;
}
