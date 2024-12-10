//--------------------------------------------------------------------------
// FMDataContainer.h : data container for multi-group xs processing 
//
//--------------------------------------------------------------------------

#pragma once

#include "FMGenerator_global.h"
#include "FMInputData.h"
#include "FMACECrossSectionProcessor.h"
#include "FMACEThermalCrossSectionProcessor.h"
#include "FMWeightingSpectrum.h"
#include "FMUFGFixedSource.h"
#include "FMPotentialXSDatabase.h"
#include "FMElementNameConverter.h"
#include "FMEffectiveTemperature.h"
#include "FMCompressedMatrix.h"
#include "FMZlib.h"
#include <fstream>

namespace FMGen
{
	enum
	{
		eFMEquiEnergyDivision,
		eFMEquiLethagyDivision
	};
	enum
	{
		eFMSlowingDownCalc,
		eFMNarrowResonanceCalc
	};
	enum
	{
		eFMRUC1D,
		eFMRUCAll
	};
	enum
	{
		eFMThermalFreegasSabExplicitIntegral,
		eFMThermalFreegasSabLinearInterpolation,
		eFMThermalFreegasSabQuadraticInterpolation,
	};
	enum
	{
		eEditOptionAll,
		eEditOption1DXS,
		eEditOption2DXS,
		eEditOptionNuChi,
		eEditOptionMGFlux,
		eEditOptionUFG,
		eEditOptionUFG1DXS,
		eEditOptionUFGInputGrid1DXS,
		eEditOptionRUC,
		eEditOptionKRAMXSMicro,
		eEditOptionKRAMXSMacro,
		eEditOptionMATXS,
		eEditOptionSimpleMATXS,
		eEditOptionFullMATXS,
		eEditOptionGENDF,
		eEditOptionSimpleGENDF,
		eEditOptionFullGENDF,
		eEditOptionNoCheckResults,
		eEditOptionSkipPrintout,
		eEditOptionDebug
	};
	struct UFRegionData
	{
		string					reg_name;		//currently not used
		int						xs_id;			//currently not used
		int						num_nucl;		//number of nuclides
		vector<REAL>			nuc_dens;		//[num_nucl] nuclide density
		vector<string>			nuc_name;		//[num_nucl] nuclide name (zaid in ACE)
		vector<REAL>			bgxs_homo;		//[num_nucl] background cross section considering materials in this region
		vector<string>			sab_name;		//[num_nucl] nuclide name (zaid of S(a,b) in ACE)
		vector<string>			sab_type;		//[num_nucl] S(a,b) type, e.g., hh2o
		REAL					nuc_dens_sum;
		REAL					mac_potential_xs;	//macroscopic potential scattering xs
		vector<FMACECrossSectionProcessor*>		ace_xs_pointer;
		vector<REAL>			alpha;			//alpha value for each nuclide
		vector<vector<int>*>	upper_fg;		//[num_nucl] used for slowing down calc		
		vector<int>* upper_fg_bg;				// used for slowing down calc ... background nuclide
		vector<vector<REAL> >	macst;			//[ib][ufg] total macro xs
		vector<vector<vector<REAL> > >	micsc;	//[ib][num_nucl][nfg] elastic scattering micro xs
		vector<REAL>			macst_macsb;	//[ufg] total macro xs + background macro xs
		vector<int>				ruc_index;		//index to resonance up-scattering treatment (no res. upscat for -1)

		void setUfgArraySize(int num_bgxs, int ufg)
		{
			macst.resize(num_bgxs);
			micsc.resize(num_bgxs);

			for (int ib = 0; ib < num_bgxs; ib++)
			{
				macst[ib].resize(ufg);
				micsc[ib].resize(num_nucl);
				for (int i = 0; i < num_nucl; i++)
					micsc[ib][i].resize(ufg);
				macst_macsb.resize(ufg);
			}

			for (int ib = 0; ib < static_cast<int>(macst.size()); ib++)
			{
				for (int i = 0; i < static_cast<int>(macst[ib].size()); i++)
				{
					macst[ib][i] = 0.0;
					macst_macsb[i] = 0.0;
				}
				for (int j = 0; j < num_nucl; j++)
					for (int i = 0; i < static_cast<int>(micsc[ib][j].size()); i++)
						micsc[ib][j][i] = 0.0;
			}
		}
		void initialize()
		{
			reg_name = "";
			xs_id = 0;
			num_nucl = 0;
			nuc_dens.clear();
			nuc_name.clear();
			bgxs_homo.clear();
			sab_name.clear();
			sab_type.clear();
			nuc_dens_sum = 0.0;
			ace_xs_pointer.clear();
			alpha.clear();
			upper_fg.clear();
			upper_fg_bg = NULL;
			macst.clear();
			micsc.clear();
			macst_macsb.clear();
			ruc_index.clear();
		}
	};
	struct RUCKernelValue
	{
		REAL p0;
		REAL p1;
	};
	struct RUCKernelData
	{
		int		uf_upper_group;
		int		uf_lower_group;
		int		uf_in_group;
		REAL	ein;
		REAL	eout_upper;
		REAL	eout_lower;
		vector<REAL>	egrid;
		vector<REAL>	kernel_p0;
		vector<REAL>	kernel_p1;
		RUCKernelData& operator = (const RUCKernelData& _p)
		{
			uf_upper_group = _p.uf_upper_group;
			uf_lower_group = _p.uf_lower_group;
			uf_in_group = _p.uf_in_group;
			ein = _p.ein;
			eout_upper = _p.eout_upper;
			eout_lower = _p.eout_lower;
			int size = egrid.size();
			egrid.resize(size);
			kernel_p0.resize(size);
			kernel_p1.resize(size);
			for (int i = 0; i < (int)egrid.size(); i++)
			{
				egrid[i] = _p.egrid[i];
				kernel_p0[i] = _p.kernel_p0[i];
				kernel_p1[i] = _p.kernel_p1[i];
			}
			return *this;
		}
		void initialize(int num)
		{
			uf_upper_group = 0;
			uf_lower_group = 0;
			uf_in_group = 0;
			ein = 0.0;
			eout_upper = 0.0;
			eout_lower = 0.0;
			egrid.resize(num);
			kernel_p0.resize(num);
			kernel_p1.resize(num);
		}
		RUCKernelValue getValue(REAL eout)
		{
			RUCKernelValue val;
			val.p0 = 0.0;
			val.p1 = 0.0;
			if (eout > eout_upper || eout < eout_lower) return val;

			int e0 = getInterval(egrid, eout);
			val.p0 = (kernel_p0[e0 + 1] - kernel_p0[e0]) / (egrid[e0 + 1] - egrid[e0]) * (eout - egrid[e0]) + kernel_p0[e0];
			val.p1 = (kernel_p1[e0 + 1] - kernel_p1[e0]) / (egrid[e0 + 1] - egrid[e0]) * (eout - egrid[e0]) + kernel_p1[e0];

			return val;
		}
		REAL getValueP0(REAL eout)
		{
			REAL val;
			val = 0.0;
			if (eout > eout_upper || eout < eout_lower) return val;

			int e0 = getInterval(egrid, eout);
			val = (kernel_p0[e0 + 1] - kernel_p0[e0]) / (egrid[e0 + 1] - egrid[e0]) * (eout - egrid[e0]) + kernel_p0[e0];

			return val;
		}
	};

	class FMDataContainer
	{
	private:
	public:
		FMInputData* input_data;
		map<int, vector<int> >	edit_option;

		int			uf_max_num_energy;
		int			uf_max_num_energy_input;
		int			mg_max_num_energy;
		int			max_num_region;

		vector<REAL>	uf_energy_boundary;
		vector<REAL>	uf_energy_delta;
		vector<REAL>	uf_energy_midpoint;
		vector<REAL>	uf_energy_boundary_input;
		vector<REAL>	uf_energy_delta_input;
		vector<REAL>	uf_energy_midpoint_input;
		vector<REAL>	mg_energy_boundary;

		vector<int>		uf_to_mg_group;
		vector<int>		uf_to_mg_group_input;
		vector<int>		ufnum_in_mg_group;
		vector<int>		uf_offset_for_mg_group;
		map<string, vector<int> >		uf_slowdown_upper_group;

		FMUFGFixedSource	fixed_source;

		UFRegionData		uf_region_data;

		vector<REAL>					background_xs_set;
		bool							auto_background_xs_setting;
		REAL							auto_background_xs_bg_eps;
		REAL							auto_background_xs_bg_min;
		int								auto_background_xs_bg_maxnum;
		bool							auto_background_xs_use_rr;
		bool							auto_background_xs_cubic_int;
		REAL							auto_background_xs_bg_min_energy;
		REAL							auto_background_xs_bg_max_energy;

		map<string, REAL>				potential_xs;
		map<string, FMACECrossSectionProcessor>			ace_xs_data;
		map<string, FMACEThermalCrossSectionProcessor>	ace_thermal_xs_data;
		map<string, int>				endf_id_list;

		int			sld_calc_option;
		REAL		moderator_aw;
		REAL		thermal_cutoff_ein;
		REAL		thermal_cutoff_eout;
		REAL		thermal_sab_torelance;
		int			thermal_freegas_sab_option;
		REAL		e_upper_slowingdown_spectrum_input;
		REAL		e_lower_slowingdown_spectrum_input;
		bool		calc_thermal_xs;
		bool		use_sct_option;
		bool		kram_current_weight_total;

		vector<string>	ruc_zaid;
		vector<string>	ruc_file_name;
		map<string,int>	ruc_option;
		vector<vector<REAL> > ruc_ene_grid;
		vector<vector<REAL> > ruc_scat_xs;
		int			ruc_uf_start_group;
		int			ruc_uf_end_group;
		map<string, vector<RUCKernelData> >		ruc_kernel_data;

		string		file_add_name_;
		string		_file_add_name;

		GaussLegendreQuadrature		gle_quad;
		GaussLobattoQuadrature		glo_quad;
		UniformQuadrature			uni_quad;

		int			max_pl;

		vector<string>			edit_xs_set;

		vector<vector<REAL> >	uf_flux;			//ultra finegroup spectrum
		vector<vector<REAL> >	uf_flux_nr;			//ultra finegroup spectrum by narrow resonance approximation
		vector<vector<REAL> >	uf_sld_source;		//ultra finegroup source (slowing down)
		vector<vector<REAL> >	uf_source;			//ultra finegroup source (slowing down + external)
		vector<vector<REAL> >	uf_sig_total_sigb;	//ultra finegroup macro total cross section including background xs
		vector<vector<REAL> >	uf_sig_total;		//ultra finegroup macro total cross section

		FMWeightingSpectrum		weighting_spectrum;

		REAL					e_upper_slowingdown_spectrum;
		REAL					e_lower_slowingdown_spectrum;

		map<string, map<int, vector<FMCompressedMatrix > > >				xs_mg_2d_matrix;			//[zaid][mt][ib][ig][iig][il]
		map<string, map<int, vector<vector<REAL> > > >						xs_mg_1d_vector;			//[zaid][mt][ib][ig]
		map<string, map<int, vector<REAL> > >								xs_mg_thermal_cutoff_ratio;	//[zaid][mt][ig]
		map<string, map<int, vector<REAL> > >								nuchi_mg_1d_vector;			//[zaid][mt][ig]
		map<string, vector<vector<REAL> > >									chi_d_independent;			//[zaid][dngr][ig]
		map<string, vector<REAL> >											delayed_ratio;				//[zaid][dngr]
		map<string, vector<REAL> >											nu_prompt_delayed_sum;		//[zaid] prompt, delayed
		map<int, vector<vector<REAL> > >									flux_mg_1d_vector;			//[1,-1][ib][ig], 1 ... scalar flux, -1 ... current, energy integrated
		vector<REAL>														xs_mg_2d_mt18_norm_factor;	//[ig]
		map<string, vector<vector<REAL> > >									kram_micxs1d;
		map<string, FMCompressedMatrix>										kram_micxs2d;

		map<string, string>		output_list_data;

		FMDataContainer()
		{
			uf_region_data.initialize();
			output_list_data.clear();
		};
		~FMDataContainer()
		{
			clear();
		};
		void clear()
		{
			edit_option.clear();
			uf_energy_boundary.clear();
			uf_energy_delta.clear();
			uf_energy_midpoint.clear();
			mg_energy_boundary.clear();
			uf_to_mg_group.clear();
			ufnum_in_mg_group.clear();
			uf_offset_for_mg_group.clear();
			uf_slowdown_upper_group.clear();
			background_xs_set.clear();
			potential_xs.clear();
			ace_xs_data.clear();
			ace_thermal_xs_data.clear();
			endf_id_list.clear();
			edit_xs_set.clear();
			uf_flux.clear();
			uf_flux_nr.clear();
			uf_sld_source.clear();
			uf_source.clear();
			uf_sig_total_sigb.clear();
			uf_sig_total.clear();
			xs_mg_2d_matrix.clear();
			xs_mg_1d_vector.clear();
			xs_mg_thermal_cutoff_ratio.clear();
			nuchi_mg_1d_vector.clear();
			chi_d_independent.clear();
			delayed_ratio.clear();
			nu_prompt_delayed_sum.clear();
			flux_mg_1d_vector.clear();
			xs_mg_2d_mt18_norm_factor.clear();
			kram_micxs1d.clear();
			kram_micxs2d.clear();
			output_list_data.clear();
		}

		void readInput(FMInputData* _input_data);
		void readACEFiles();
		void setACEFileData(string zaid, vector<string>& _title, vector<int>& _izaw, vector<int>& _nxs, vector<int>& _jxs,
			vector<REAL>& _xss)
		{
			FMACECrossSectionProcessor        acexs;
			FMACEThermalCrossSectionProcessor acetxs;
			int id = _izaw[0];

			if (id == 0)
			{
				if (ace_xs_data.find(zaid) != ace_xs_data.end())
				{
					cout << " zaid " << zaid << " already exists " << endl;
					printError(" Error in DataContainer::setACEFileData");
				}
				acexs.setACEData(_title, _izaw, _nxs, _jxs,	_xss);
				ace_xs_data.insert(make_pair(zaid, acexs));
				ace_xs_data[zaid].processHeaderData();
				ace_xs_data[zaid].processXSData();
				ace_xs_data[zaid].getDLW();
			}
			else
			{
				if (ace_thermal_xs_data.find(zaid) != ace_thermal_xs_data.end())
				{
					cout << " zaid " << zaid << " already exists " << endl;
					printError(" Error in DataContainer::setACEFileData");
				}
				acetxs.setACEData(_title, _izaw, _nxs, _jxs, _xss);
				ace_thermal_xs_data.insert(make_pair(zaid, acetxs));
				ace_thermal_xs_data[zaid].processHeaderData();
				ace_thermal_xs_data[zaid].processXSData();

				//effective temperature for short collision time approximation
				REAL temp = ace_thermal_xs_data[zaid].getKelvin();
				ace_thermal_xs_data[zaid].setEffectiveTemperature(temp);
				FMEffectiveTemperature fm_eff_temp;
				for (int in = 0; in < static_cast<int>(uf_region_data.sab_name.size()); in++)
				{
					if (zaid == uf_region_data.sab_name[in])
					{
						if (this->use_sct_option == true)
						{
							REAL eff_temp = fm_eff_temp.getEffectiveTemperature(uf_region_data.sab_type[in], temp);
							ace_thermal_xs_data[zaid].setEffectiveTemperature(eff_temp);
						}
					}
				}

				ace_thermal_xs_data[zaid].setEoutUpperLowerInelastic(thermal_cutoff_eout, mg_energy_boundary.back());
				ace_thermal_xs_data[zaid].prepPlCoefIncoherentInelastic(max_pl);
				ace_thermal_xs_data[zaid].prepPlCoefIncoherentElastic(max_pl);
				ace_thermal_xs_data[zaid].prepPlCoefCoherentElastic(max_pl);
			}
		}
		void checkACEFiles();
		void readAndSetUFEnergyGroupStructure();
		void reportUFEnergyGroupStructure();
		void doInitialize();
		void setBGXSInUFRegionData();
		void setUFGXSInUFRegionData();
		void setMiscDataInUFRegionData();
		void autoSetBackgroundXS();
		void calcEffectiveXSForAutoSetBGXS(REAL bgxs, vector<vector<vector<REAL> > >& ufg_xs, REAL pot_sc_xs, vector<vector<REAL> >& mg_xs, vector<REAL>& rr, bool slowdown = false);
		void calcEffectiveMicroXS();
		void calcUFSpectrumHomo();
		void calcUFSpectrumHomoAsymptotic();
		void calcUFSpectrumHomoResoUpscat();
		void prepResoUpscatKernel(UFRegionData& ufr);
		inline RUCKernelValue calcResoUpscatIntegrand(int& nuc, REAL& t, REAL& ein, REAL& beta, REAL& kt, REAL& aw, REAL& tp, REAL& tm, REAL& epsmax, REAL& epsmin)
		{
			REAL val1 = t;

			REAL wk1 = beta * kt / aw * t * t;
			int e0 = getInterval(ruc_ene_grid[nuc], wk1, true);
			REAL val2 = endfInterpolator2Point(2, ruc_ene_grid[nuc][e0], ruc_ene_grid[nuc][e0 + 1],
				ruc_scat_xs[nuc][e0], ruc_scat_xs[nuc][e0 + 1], wk1);

			REAL wk2 = ein / kt - t * t / aw;
			REAL val3 = exp(wk2);

			REAL val4 = 0.0;
			REAL val5 = 0.0;
			calcPsiRUC(t, tp, tm, epsmax, epsmin, val4, val5);

			RUCKernelValue val;
			REAL val123 = val1 * val2 * val3;
			val.p0 = val123 * val4;
			val.p1 = val123 * val5;

			return val;
		}
		RUCKernelValue doAdaptiveIntegrationResoUpscat(int& nuc, REAL& t0, REAL& t1, REAL& dt, RUCKernelValue& val_max, RUCKernelValue& val0, RUCKernelValue& val1, REAL& ein, REAL& beta, REAL& kt, REAL& aw, REAL& tp, REAL& tm, REAL& epsmax, REAL& epsmin)
		{
			REAL ta = (t0 + t1) / 2.0;
			RUCKernelValue vala = calcResoUpscatIntegrand(nuc, ta, ein, beta, kt, aw, tp, tm, epsmax, epsmin);
			REAL dif = 0.0;
			if (val_max.p0 != 0.0) dif = abs(((val0.p0 + val1.p0) / 2.0 - vala.p0) / val_max.p0);
			RUCKernelValue sum;
			sum.p0 = 0.0; sum.p1 = 0.0;
			const REAL EPS = 1.0e-2;
			if (dif < EPS || t1 - t0 < dt * 0.01)	//prevent too small integration range
			{
				sum.p0 = (val0.p0 + 4.0 * vala.p0 + val1.p0) / 6.0 * (t1 - t0);
				sum.p1 = (val0.p1 + 4.0 * vala.p1 + val1.p1) / 6.0 * (t1 - t0);
			}
			else
			{
				RUCKernelValue sum1 = doAdaptiveIntegrationResoUpscat(nuc, t0, ta, dt, val_max, val0, vala, ein, beta, kt, aw, tp, tm, epsmax, epsmin);
				RUCKernelValue sum2 = doAdaptiveIntegrationResoUpscat(nuc, ta, t1, dt, val_max, vala, val1, ein, beta, kt, aw, tp, tm, epsmax, epsmin);
				sum.p0 = sum1.p0 + sum2.p0;
				sum.p1 = sum1.p1 + sum2.p1;
			}

			return sum;
		}
		void calcSlowingDownSourceRecurrent(vector<vector<REAL> >& micsc, REAL& sig_b,
			vector<REAL>& nuc_dens, REAL& nuc_dens_sum,
			vector<REAL>& alpha, REAL& alpha_b,
			vector<vector<int>*>& upper_fg, vector<int>& upper_fg_bg,
			vector<REAL>& flux, REAL& sfg_prev, REAL& sfg, int& ie);
		void calcSlowingDownSourceAsymptotic(vector<REAL>& sld_src, vector<vector<REAL> >& micsc, REAL& sig_b,
			vector<REAL>& nuc_dens, REAL& nuc_dens_sum,
			vector<REAL>& alpha, REAL& alpha_b,
			vector<REAL>& flux, int& ie);
		void calcSlowingDownSourceResoUpscat(vector<REAL>& sld_src, vector<REAL>& sld_src_wk, int& ib, vector<vector<REAL> >& micsc, REAL& sig_b,
			vector<REAL>& nuc_dens, REAL& nuc_dens_sum,
			vector<REAL>& alpha, REAL& alpha_b, UFRegionData& ufr,
			vector<REAL>& flux, int& ie);
		RUCKernelValue calcResoUpscatKernel(REAL ein, REAL eout, REAL aw, REAL temp, int nuc);
		void normalizeFlux(vector<REAL>& flux);
		void normalizeEnergyTransferMatrix(string zaid, int mt, int ib);
		int getUFgroup(REAL ene);
		int getMGgroup(REAL ene, bool extend = false);
		REAL getUFSpectrum(int ie, int ib, int pl = 0);
		REAL getUFSpectrum(REAL ene, int ib, int pl = 0, int opt = eFMSlowingDownCalc);
		void getMTinXSMG1DVector(string zaid, vector<int>& mt_list)
		{
			mt_list.clear();
			map<int, vector<vector<REAL> > >::iterator it;
			for (it = xs_mg_1d_vector[zaid].begin(); it != xs_mg_1d_vector[zaid].end(); it++)
				mt_list.push_back(it->first);
		}
		void getMTinXSMG2DMatrix(string zaid, vector<int>& mt_list)
		{
			mt_list.clear();
			map<int, vector<FMCompressedMatrix> >::iterator it;
			for (it = xs_mg_2d_matrix[zaid].begin(); it != xs_mg_2d_matrix[zaid].end(); it++)
				mt_list.push_back(it->first);
		}
		REAL getXSMG1DVectorUF(string zaid, int mt, int ib, int ig)
		{
			if (xs_mg_1d_vector.find(zaid) == xs_mg_1d_vector.end()) return 0.0;
			if (xs_mg_1d_vector[zaid].find(mt) == xs_mg_1d_vector[zaid].end()) return 0.0;

			return xs_mg_1d_vector[zaid][mt][ib][ig];
		}
		REAL getNuChiMG1DVector(string zaid, int mt, int ig)
		{
			if (nuchi_mg_1d_vector.find(zaid) == nuchi_mg_1d_vector.end()) return 0.0;
			if (nuchi_mg_1d_vector[zaid].find(mt) == nuchi_mg_1d_vector[zaid].end()) return 0.0;

			return nuchi_mg_1d_vector[zaid][mt][ig];
		}
		REAL getXSMG2DMatrix(string zaid, int mt, int ib, int ig, int iig, int il)
		{
			//return 0.0 if not found .. skip this check to increase speed
			//if (xs_mg_2d_matrix.find(zaid) == xs_mg_2d_matrix.end()) return 0.0;
			//if (xs_mg_2d_matrix[zaid].find(mt) == xs_mg_2d_matrix[zaid].end()) return 0.0;

			//return infinite dilute cross section if ib is greater than actual size
			if (ib >= static_cast<int>(xs_mg_2d_matrix[zaid][mt].size()))
				return xs_mg_2d_matrix[zaid][mt][0].get(ig, iig, il);

			return xs_mg_2d_matrix[zaid][mt][ib].get(ig, iig, il);
		}
		REAL getXSMG2DMatrix(vector<FMCompressedMatrix>& matrix, int ib, int ig, int iig, int il)
		{
			//return infinite dilute cross section if ib is greater than actual size
			if (ib >= static_cast<int>(matrix.size()))
				return matrix[0].get(ig, iig, il);

			return matrix[ib].get(ig, iig, il);
		}
		REAL getXSMG2DMatrixSum(string zaid, int mt, int ib, int ig, int il = 0)
		{
			//return 0.0 if not found
			if (xs_mg_2d_matrix.find(zaid) == xs_mg_2d_matrix.end()) return 0.0;
			if (xs_mg_2d_matrix[zaid].find(mt) == xs_mg_2d_matrix[zaid].end()) return 0.0;

			REAL sum = 0.0;
			if (ib >= static_cast<int>(xs_mg_2d_matrix[zaid][mt].size()))
			{
				for (int iig = 0; iig < mg_max_num_energy; iig++)
					sum += xs_mg_2d_matrix[zaid][mt][0].get(ig,iig,il);
			}
			else
			{
				for (int iig = 0; iig < mg_max_num_energy; iig++)
					sum += xs_mg_2d_matrix[zaid][mt][ib].get(ig,iig,il);

			}

			return sum;
		}
		REAL getAlpha(string zaid)
		{
			int num = uf_region_data.num_nucl;
			for (int i = 0; i < num; i++)
			{
				if (compareString(zaid, uf_region_data.nuc_name[i]) == true)
					return uf_region_data.alpha[i];
			}

			cout << zaid << endl;
			printError(" zaid not found in getAlpha ");

			return 0.0;
		}
		REAL getAW(string zaid)
		{
			int num = uf_region_data.num_nucl;
			for (int i = 0; i < num; i++)
			{
				if (compareString(zaid, uf_region_data.nuc_name[i]) == true)
				{
					REAL val = uf_region_data.ace_xs_pointer[i]->getAW();
					return val;
				}
			}

			cout << zaid << endl;
			printError(" zaid not found in getAW ");

			return 0.0;
		}
		void setSumOfInelasticXS(string zaid, vector<vector<vector<vector<REAL> > > >& matrix);
		void setMisc1DParameters(string zaid);
		void setMT18FromMT19(string zaid, vector<vector<vector<vector<REAL> > > >& matrix, map<int, vector<vector<vector<vector<REAL> > > > >& matrix_map);
		void setMTFromOtherMTs(string zaid, map<int, vector<FMCompressedMatrix> >& matrix_map);
		void setMTFromOtherMTs(string zaid, int to_mt, vector<int> from_mt, vector<vector<vector<vector<REAL> > > >& matrix, map<int, vector<FMCompressedMatrix> >& matrix_map);
		bool isThermalScattering(string zaid)
		{
			map<int, vector<FMCompressedMatrix> >::iterator it;
			for (it = xs_mg_2d_matrix[zaid].begin(); it != xs_mg_2d_matrix[zaid].end(); it++)
				if (isThermalMT(it->first)) return true;

			return false;
		}
		void convertThermalMaterialNameToMt(string sab_name, string zaid_thermal, int& inc_iel, int& inc_el, int& coh_el);
		REAL getNumNeutronScattering(string zaid, int mt, int ig)
		{
			if (xs_mg_1d_vector[zaid].find(mt + eMTEnergyDependentNeutronEmission) != xs_mg_1d_vector[zaid].end())
			{
				REAL val = getXSMG1DVectorUF(zaid, mt + eMTEnergyDependentNeutronEmission, 0, ig);
				return val;
			}
			bool isMTN2n = false;
			if (xs_mg_1d_vector[zaid].find(eMTN2n) != xs_mg_1d_vector[zaid].end()) isMTN2n = true;

			if (mt == 2) return 1.0;
			if (mt == 3) return 1.0;
			if (mt == 4) return 1.0;
			if (mt == 11) return 2.0;
			if (mt == 16) return 2.0;
			if (mt == 17) return 3.0;
			if (mt == 22) return 1.0;
			if (mt == 23) return 1.0;
			if (mt == 24) return 2.0;
			if (mt == 25) return 3.0;
			if (mt == 28) return 1.0;
			if (mt == 29) return 1.0;
			if (mt == 30) return 2.0;
			if (mt == 32) return 1.0;
			if (mt == 33) return 1.0;
			if (mt == 34) return 1.0;
			if (mt == 35) return 1.0;
			if (mt == 36) return 1.0;
			if (mt == 37) return 4.0;
			if (mt == 41) return 2.0;
			if (mt == 42) return 3.0;
			if (mt == 44) return 1.0;
			if (mt == 45) return 1.0;
			if (mt >= eMTInelasticScatteringBegin && mt <= eMTInelasticScatteringEnd) return 1.0;
			if (mt >= eMTThermalFreeGas && mt <= eMTThermalKernelUpper) return 1.0;
			if (isMTN2n == false)
			{
				if (mt == 6) return 2.0;
				if (mt == 7) return 2.0;
				if (mt == 8) return 2.0;
				if (mt == 9) return 2.0;
				if (mt >= 875 && mt <= 891) return 2.0;
			}
			else
			{
				//use mt=16 for (n,2n) reaction if mt=16 exists
				if (mt == 6) return 0.0;
				if (mt == 7) return 0.0;
				if (mt == 8) return 0.0;
				if (mt == 9) return 0.0;
				if (mt >= 875 && mt <= 891) return 0.0;
			}

			if (mt == 5 || (mt >= eMT152 && mt <= eMT200))
			{
				REAL ty = abs(ace_xs_data[zaid].getTYValue(mt));
				REAL val = ty;

				if (abs(ty - 19.0) < 0.1)
				{
					//fission
					val = 0.0;
				}
				else if (ty > 19.0)
				{
					//energy dependent case, which is treated by eMTEnergyDependentNeutronEmission
					cout << zaid << " mt = " << mt << " ty = " << ty << endl;
					printError("Error in getNumNeutronAbsorption");
				};

				return val;
			}

			return 0.0;
		}
		REAL getNumNeutronAbsorption(string zaid, int mt, int ig)
		{
			//number of absorped neutron per reaction
			//since n2n, n3n, n4n reactions are neutron emitting ones, negative values are given

			if (xs_mg_1d_vector[zaid].find(mt + eMTEnergyDependentNeutronEmission) != xs_mg_1d_vector[zaid].end())
			{
				REAL val = getXSMG1DVectorUF(zaid, mt + eMTEnergyDependentNeutronEmission, 0, ig);
				return 1.0 - val;
			}
			bool isMTN2n = false;
			if (xs_mg_1d_vector[zaid].find(eMTN2n) != xs_mg_1d_vector[zaid].end()) isMTN2n = true;

			if (mt == 11) return -1.0;
			if (mt == 16) return -1.0;
			if (mt == 17) return -2.0;
			if (mt == 18) return 1.0;
			if (mt == 24) return -1.0;
			if (mt == 25) return -2.0;
			if (mt == 27) return 1.0;
			if (mt == 30) return -1.0;
			if (mt == 37) return -3.0;
			if (mt == 41) return -1.0;
			if (mt == 42) return -2.0;
			if (mt == 101) return 1.0;
			if (mt >= 101 && mt <= 117) return 1.0;
			if (isMTN2n == false)
			{
				if (mt == 6) return -1.0;
				if (mt == 7) return -1.0;
				if (mt == 8) return -1.0;
				if (mt == 9) return -1.0;
				if (mt >= 875 && mt <= 891) return -1.0;
			}
			else
			{
				//use mt=16 for (n,2n) reaction if mt=16 exists
				if (mt == 6) return 0.0;
				if (mt == 7) return 0.0;
				if (mt == 8) return 0.0;
				if (mt == 9) return 0.0;
				if (mt >= 875 && mt <= 891) return 0.0;
			}

			if (mt == 5 || (mt >= eMT152 && mt <= eMT200))
			{
				REAL ty = abs(ace_xs_data[zaid].getTYValue(mt));
				REAL val = 1.0 - ty;

				if (abs(ty - 19.0) < 0.1)
				{
					//fission
					val = 0.0;
				}
				else if (ty > 19.0)
				{
					//energy dependent case, which is treated by eMTEnergyDependentNeutronEmission
					cout << zaid << " mt = " << mt << " ty = " << ty << endl;
					printError("Error in getNumNeutronAbsorption");
				};

				return val;
			}

			return 0.0;
		}

		void setOutputCrossSectionMT(string zaid, vector<int>& xs1d_infdil, vector<int>& xs1d_shield, vector<int>& xs2d_infdil, vector<int>& xs2d_shield, map<int, int>& xs2d_plorder, string opt);
		void dumpOutputListData();
		void editOutputListData();
		void dumpEffectiveMicroXSinKramFormat(string zaid, int ib);
		void dumpEffectiveMacroXSinKramFormat(int ib);
		void dumpMGFlux();
		void dumpMGXS1d(string zaid, int mt);
		void dumpMGTotalScatteringXS(string zaid);
		void dumpMGXS2d(string zaid, int mt, int ib);
		void dumpMGNuChi(string zaid);
		void dumpUFGXS1d(string zaid, int mt);
		void dumpUFGXS1dInputUFGGrid(string zaid, int mt);
		void dumpRUCXS1d(string zaid);
		void dumpUFFlux();
		void dumpUFTotalSource();
		void dumpUFSlowingdownSource();
		void dumpUFSigTotal();

		void checkResults();

	};
}
