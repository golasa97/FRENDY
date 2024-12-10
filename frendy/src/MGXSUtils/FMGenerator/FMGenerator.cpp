#pragma once
#include "MGXSUtils/FMGenerator/FMGenerator.h"
#include "MGXSUtils/FMGenerator/FMGENDFOutput.h"
#include <algorithm>

using namespace FMGen;

void FMGenerator::run()
{
	//computation time
	FMCalculationTime timer;

	//ultra-fine group spectrum calculation
	print1stHeader(" Preparing ultra-fine group spectrum ");
	timer.startMeasure("Ultra fine group calculation");
	data_container.calcUFSpectrumHomo();

	//1d effective cross section calculations
	print1stHeader(" Processing 1d cross sections ");
	data_container.calcEffectiveMicroXS();
	timer.stopMeasure("Ultra fine group calculation");

	//allocate temporary energy transfer matrix
	int max_ng = data_container.mg_max_num_energy;
	int max_pl = data_container.max_pl;
	int num_bgxs = data_container.background_xs_set.size();
	vector<vector<vector<vector<REAL> > > > matrix;				//[ib][ig][iig][il]
	matrix.resize(num_bgxs);
	for (int ib = 0; ib < static_cast<int>(matrix.size()); ib++)
	{
		matrix[ib].resize(max_ng);
		for (int ig = 0; ig < max_ng; ig++)
		{
			matrix[ib][ig].resize(max_ng);
			for (int iig = 0; iig < max_ng; iig++)
			{
				matrix[ib][ig][iig].resize(max_pl + 1);
			}
		}
	}

	//energy transfer matrix and related processings
	int num_nucl = data_container.uf_region_data.num_nucl;
	for (int in = 0; in < num_nucl; in++)
	{
		FMACECrossSectionProcessor& acexs = (*data_container.uf_region_data.ace_xs_pointer[in]);

		vector<int> mt_values_angular;
		acexs.getMtValuesWithAngularDist(mt_values_angular);
		string zaid = acexs.getZaid();

		map<int, vector<FMCompressedMatrix> > matrix_map_wk;	//[mt][ib][ig][iig][il]
		matrix_map_wk.clear();
		data_container.xs_mg_2d_matrix.insert(make_pair(zaid, matrix_map_wk));
		map<int, vector<FMCompressedMatrix> >& matrix_map = data_container.xs_mg_2d_matrix[zaid];

		//fast groups
		timer.startMeasure("Energy transfer matrix: fast");
		print1stHeader(" Processing 2d energy transfer matrixes ");
		for (int i = 0; i < static_cast<int>(mt_values_angular.size()); i++)
		{
			int mt = mt_values_angular[i];
			calcEnergyTransferMatrix(acexs, mt, matrix_map, matrix);
		}

		//supplemental settings
		data_container.setMTFromOtherMTs(zaid, matrix_map);

		timer.stopMeasure("Energy transfer matrix: fast");

		//thermal cross sections
		if (data_container.calc_thermal_xs)
		{
			timer.startMeasure("Energy transfer matrix: thermal");
			print1stHeader(" Processing 2d energy transfer matrixes considering S(a,b)");
			map<int, vector<REAL> > ratio_map;
			ratio_map.clear();

			//set thermal mt number
			string zaid_thermal = data_container.uf_region_data.sab_name[in];
			int thermal_mt[3];		//incoherent inelastic, incoherent elastic, coherent elastic
			data_container.convertThermalMaterialNameToMt(data_container.uf_region_data.sab_type[in], zaid_thermal, thermal_mt[0], thermal_mt[1], thermal_mt[2]);
			int mt_inela = thermal_mt[0];

			calcThermalIncoherentInelastic(acexs, zaid_thermal, mt_inela, matrix_map, ratio_map);

			int mt_ela = 0;
			if (thermal_mt[1] != 0)
				mt_ela = thermal_mt[1];
			else if (thermal_mt[2] != 0)
				mt_ela = thermal_mt[2];
			calcThermalIncoherentCoherentElastic(acexs, zaid_thermal, mt_ela, matrix_map, ratio_map);

			data_container.xs_mg_thermal_cutoff_ratio.insert(make_pair(zaid, ratio_map));
			timer.stopMeasure("Energy transfer matrix: thermal");
		}

		//data_container.xs_mg_2d_matrix.insert(make_pair(zaid, matrix_map));

		//fission spectrum, nu
		timer.startMeasure("Fission spectrum & nu");
		vector<REAL> nu_t, nu_p, nu_d, chi_t, chi_p, chi_d, delayed_ratio;
		vector<vector<REAL> > chi_d_independent;
		map<int, vector<REAL> > nuchi_wk;
		nuchi_wk.clear();
		vector<REAL> nusum_wk;
		nusum_wk.clear();
		REAL nu_prompt_sum = 0.0;
		REAL nu_delayed_sum = 0.0;
		if (matrix_map.find(eMTFission) != matrix_map.end())
		{
			print1stHeader(" Processing Nu, fission spectrum ");
			vector<vector<vector<vector<REAL> > > > fission_matrix;
			fission_matrix.resize(matrix_map[eMTFission].size());
			for (int ib = 0; ib < (int)matrix_map[eMTFission].size(); ib++)
				matrix_map[eMTFission][ib].get(fission_matrix[ib]);

			calcNuChi(acexs, fission_matrix, nu_t, nu_p, nu_d, chi_t, chi_p, chi_d, chi_d_independent, delayed_ratio,
				nu_prompt_sum, nu_delayed_sum);
			nuchi_wk.insert(make_pair(eMTNuTotal, nu_t));
			nuchi_wk.insert(make_pair(eMTNuPrompt, nu_p));
			nuchi_wk.insert(make_pair(eMTNuDelayed, nu_d));
			nuchi_wk.insert(make_pair(eMTChiTotal, chi_t));
			nuchi_wk.insert(make_pair(eMTChiPrompt, chi_p));
			nuchi_wk.insert(make_pair(eMTChiDelayed, chi_d));
			data_container.nuchi_mg_1d_vector.insert(make_pair(zaid, nuchi_wk));
			data_container.delayed_ratio.insert(make_pair(zaid, delayed_ratio));
			data_container.chi_d_independent.insert(make_pair(zaid, chi_d_independent));
			nusum_wk.push_back(nu_prompt_sum);
			nusum_wk.push_back(nu_delayed_sum);
			data_container.nu_prompt_delayed_sum.insert(make_pair(zaid, nusum_wk));
		}
		timer.stopMeasure("Fission spectrum & nu");

		print1stHeader(" Doing normalization for energy transfer matrixes ");
		cout << " Summary of normalization factor " << endl;
		cout << "           zaid        mt            bgxs       num  average   stdev     max       min " << endl;
		cout << " --------------------------------------------------------------------------------------------- " << endl;
		for (int ib = 0; ib < static_cast<int>(data_container.background_xs_set.size()); ib++)
		{
			if (data_container.xs_mg_2d_matrix.find(zaid) == data_container.xs_mg_2d_matrix.end()) continue;
			map<int, vector<FMCompressedMatrix> >::iterator it;
			for (it = data_container.xs_mg_2d_matrix[zaid].begin(); it != data_container.xs_mg_2d_matrix[zaid].end(); it++)
				data_container.normalizeEnergyTransferMatrix(zaid, it->first, ib);
		}

		print1stHeader(" Checking multi-group cross sections ");
		for (int ib = 0; ib < static_cast<int>(data_container.background_xs_set.size()); ib++)
		{
			if (data_container.xs_mg_2d_matrix.find(zaid) == data_container.xs_mg_2d_matrix.end()) continue;
			if (data_container.edit_option.find(eEditOptionNoCheckResults) == data_container.edit_option.end())
				data_container.checkResults();
		}

		//add total inelastic cross sections for convenience
		data_container.setSumOfInelasticXS(zaid, matrix);		//set matrix of mt=4

		//set misc. parameters such as average inverse velocity
		data_container.setMisc1DParameters(zaid);

	}

	//edit list output data
	data_container.editOutputListData();

	//dump matxsfile
	for (int in = 0; in < num_nucl; in++)
	{
		if (data_container.edit_option.find(eEditOptionMATXS) == data_container.edit_option.end() &&
			data_container.edit_option.find(eEditOptionFullMATXS) == data_container.edit_option.end() &&
			data_container.edit_option.find(eEditOptionSimpleMATXS) == data_container.edit_option.end()) continue;
		FMACECrossSectionProcessor& acexs = (*data_container.uf_region_data.ace_xs_pointer[in]);
		string zaid = acexs.getZaid();
		FMMatxsOutput mxout(&data_container);
		mxout.openFile(zaid, data_container.file_add_name_);
		mxout.outputHeader();
		mxout.outputMaterialControl();
		mxout.outputVectorMatrix();
		mxout.closeFile();
	}

	//dump GENDF file
	for (int in = 0; in < num_nucl; in++)
	{
		if (data_container.edit_option.find(eEditOptionGENDF) == data_container.edit_option.end() &&
			data_container.edit_option.find(eEditOptionFullGENDF) == data_container.edit_option.end() &&
			data_container.edit_option.find(eEditOptionSimpleGENDF) == data_container.edit_option.end()) continue;
		FMACECrossSectionProcessor& acexs = (*data_container.uf_region_data.ace_xs_pointer[in]);
		string zaid = acexs.getZaid();
		FMGENDFOutput gendf(&data_container);
		gendf.openFile(zaid, data_container.file_add_name_);
		gendf.output();
		gendf.closeFile();
	}

	//breakdown of calculation time
	string calc_time_file_name = "FMCalculationTime" + data_container._file_add_name + ".txt";
	string calc_time_output_list;
	timer.editBreakdown(calc_time_output_list);
	data_container.output_list_data.insert(make_pair(calc_time_file_name, calc_time_output_list));

	//dump list data
	data_container.dumpOutputListData();
}
void FMGenerator::calcEnergyTransferMatrix(FMACECrossSectionProcessor& acexs, int mt, map<int, vector<FMCompressedMatrix> >& matrix_map, vector<vector<vector<vector<REAL> > > >& matrix)
{
	//set number of energy groups, order of anisotropic scattering
	int max_ng = data_container.mg_max_num_energy;
	int max_pl = data_container.max_pl;
	int num_bgxs = data_container.background_xs_set.size();

	//clear energy transfer matrix
	for (int ib = 0; ib < static_cast<int>(matrix.size()); ib++)
	{
		for (int ig = 0; ig < max_ng; ig++)
		{
			for (int iig = 0; iig < max_ng; iig++)
			{
				for (int il = 0; il <= max_pl; il++)
					matrix[ib][ig][iig][il] = 0.0;
			}
		}
	}

	//default spectrum
	//FMWeightingSpectrum& spectrum = data_container.weighting_spectrum;

	//set "panel" of incident energy
	vector<REAL> ein_boundary, ein_boundary_wk;
	for (int ig = 0; ig <= max_ng; ig++)
		ein_boundary_wk.push_back(data_container.mg_energy_boundary[ig]);

	for (int ig = 0; ig <= max_ng; ig++)
	{
		REAL eb = data_container.mg_energy_boundary[ig];
		REAL ebb;
		if (mt == eMTElasticScattering)
		{
			ebb = acexs.getEinBeforeElasticScattering(eb, -1.0);
			if (ebb < data_container.mg_energy_boundary[0] && ebb > data_container.mg_energy_boundary.back())
				ein_boundary_wk.push_back(ebb);
		}
		else if (isIndependentInelasticScattering(mt))
		{
			ebb = acexs.getEinBeforeInElasticScattering(eb, -1.0, mt);
			if (ebb < data_container.mg_energy_boundary[0] && ebb > data_container.mg_energy_boundary.back())
				ein_boundary_wk.push_back(ebb);
			ebb = acexs.getEinBeforeInElasticScattering(eb, +1.0, mt);
			if (ebb < data_container.mg_energy_boundary[0] && ebb > data_container.mg_energy_boundary.back())
				ein_boundary_wk.push_back(ebb);
		}
	}
	vector<REAL> add_ein_boundary;
	acexs.getIncidentEnergyGridInDLW(mt, data_container.mg_energy_boundary, add_ein_boundary);
	addEnergyBoundary(ein_boundary_wk, add_ein_boundary);
	deleteNarrowEnergyBoundary(ein_boundary, ein_boundary_wk);

	//set sub-division
	subdivideEnergyBoundary(ein_boundary);
	vector<REAL> ein_boundary_mid;
	for (int ie = 0; ie < static_cast<int>(ein_boundary.size())-1; ie++)
	{
		REAL val = sqrt(ein_boundary[ie] * ein_boundary[ie + 1]);
		ein_boundary_mid.push_back(val);
	}

	//calculate weight for each sub-division point
	vector<vector<vector<REAL> > >	xfde_from_ufg;
	vector<vector<vector<REAL> > >	fde_from_ufg;
	vector<REAL>					de_from_ufg;
	xfde_from_ufg.resize(num_bgxs);
	fde_from_ufg.resize(num_bgxs);
	for (int ib = 0; ib < num_bgxs; ib++)
	{
		xfde_from_ufg[ib].resize(ein_boundary_mid.size());
		fde_from_ufg[ib].resize(ein_boundary_mid.size());
		for (int ie = 0; ie < static_cast<int>(ein_boundary_mid.size()); ie++)
		{
			xfde_from_ufg[ib][ie].resize(max_pl + 1);
			fde_from_ufg[ib][ie].resize(max_pl + 1);
			for (int il = 0; il <= max_pl; il++)
			{
				xfde_from_ufg[ib][ie][il] = 0.0;
				fde_from_ufg[ib][ie][il] = 0.0;
			}
		}
	}
	de_from_ufg.resize(ein_boundary_mid.size());
	for (int ie = 0; ie < static_cast<int>(ein_boundary_mid.size()); ie++)
		de_from_ufg[ie] = 0.0;

	int ie = 0;
	for (int iuf = 0; iuf < data_container.uf_max_num_energy; iuf++)
	{
		REAL ene = data_container.uf_energy_midpoint[iuf];
		if (ene > ein_boundary[0]) ie = 0;
		else if (ene < ein_boundary.back()) ie = ein_boundary.size() - 2;
		else
		{
			for (;;)
			{
				if (ene < ein_boundary[ie + 1]) ie++;
				else break;
			}
		}

		REAL ty = abs(acexs.getTYValue(mt));
		if (abs(ty - 19.0) < 0.1)
			ty = acexs.getNu(eNuPrompt, ene);
		else if (ty > 100.0)
			ty = acexs.getEnergyDependentNeutronYieldInDLW(mt, ene);

		REAL de = data_container.uf_energy_delta[iuf];
		de_from_ufg[ie] += de;
		for (int ib = 0; ib < num_bgxs; ib++)
		{
			REAL bgxs = data_container.background_xs_set[ib];
			REAL xs = acexs.getXS(mt, ene, bgxs);
			for (int il = 0; il <= max_pl; il++)
			{
				REAL flx = data_container.getUFSpectrum(iuf, ib, il);
				xfde_from_ufg[ib][ie][il] += ty*xs*flx*de;
				fde_from_ufg[ib][ie][il] += flx*de;
			}
		}
	}

	for (ie = 0; ie < static_cast<int>(ein_boundary_mid.size()); ie++)
	{
		REAL de = ein_boundary[ie] - ein_boundary[ie + 1];
		if (de_from_ufg[ie] != 0.0)
		{
			REAL fact = de / de_from_ufg[ie];
			for (int ib = 0; ib < num_bgxs; ib++)
			{
				for (int il = 0; il <= max_pl; il++)
				{
					xfde_from_ufg[ib][ie][il] *= fact;
					fde_from_ufg[ib][ie][il] *= fact;
				}
			}
		}
		else
		{
			//set value if ultra-fine group is not sufficient to cover this energy range
			REAL ene = ein_boundary_mid[ie];
			REAL ty = abs(acexs.getTYValue(mt));
			if (abs(ty - 19.0) < 0.1)
				ty = acexs.getNu(eNuPrompt, ene);
			else if (ty > 100.0)
				ty = acexs.getEnergyDependentNeutronYieldInDLW(mt, ene);

			for (int ib = 0; ib < num_bgxs; ib++)
			{
				REAL bgxs = data_container.background_xs_set[ib];
				REAL xs = acexs.getXS(mt, ene, bgxs);
				for (int il = 0; il <= max_pl; il++)
				{
					REAL flx = data_container.getUFSpectrum(ene, ib, il);
					xfde_from_ufg[ib][ie][il] = ty*xs*flx*de;
					fde_from_ufg[ib][ie][il] = flx*de;
				}
				de_from_ufg[ie] = de;
			}
		}
	}

	//xsave ... group average cross section
	//weight ... flux*delta-E
	vector<vector<vector<REAL> > >	xsave, weight;
	xsave.resize(num_bgxs);
	weight.resize(num_bgxs);
	for (int ib = 0; ib < num_bgxs; ib++)
	{
		xsave[ib].resize(max_ng);
		weight[ib].resize(max_ng);
		for (int i = 0; i < max_ng; i++)
		{
			xsave[ib][i].resize(max_pl + 1);
			weight[ib][i].resize(max_pl + 1);
			for (int il = 0; il <= max_pl; il++)
			{
				xsave[ib][i][il] = 0.0;
				weight[ib][i][il] = 0.0;
			}
		}
	}

	cout << setw(20) << acexs.getZaid() << " mt =" << setw(4) << mt << "  number of energy panel used for integration " << setw(4) << ein_boundary.size() - 2 << endl;

	acexs.prepAngularPDF(mt);
	acexs.clearMCDDataTemporary();
	acexs.clearEADDataTemporary();

	//set temporay array to tally energy transfer probability
	FMEneAngDist eadist, ead_wk;
	eadist.resize(max_ng);
	eadist.resizePlCoef(max_pl);
	eadist.setEnergyBoundary(data_container.mg_energy_boundary);
	ead_wk.resize(max_ng);
	ead_wk.resizePlCoef(max_pl);
	ead_wk.setEnergyBoundary(data_container.mg_energy_boundary);

	map<int, REAL>::iterator it, it2;
	for (ie = 0; ie < static_cast<int>(ein_boundary_mid.size()); ie++)
	{
		//calculate energy transfer probability
		REAL ein = ein_boundary_mid[ie];
		int ig = data_container.getMGgroup(ein);

#if 0
		acexs.getEnergyAngleDistribution(mt, ein, eadist, ead_wk);
#else
		getEnergyAngleDistribution(acexs, mt, ein, eadist, ead_wk);
#endif
		for (int ib = 0; ib < num_bgxs; ib++)
		{
			vector<REAL> val(max_pl + 1);
			for (int il = 0; il <= max_pl; il++)
			{
				val[il] = xfde_from_ufg[ib][ie][il];
				weight[ib][ig][il] += fde_from_ufg[ib][ie][il];
				xsave[ib][ig][il] += val[il];
			}
#if 0
			if (mt == 16)
			{
				if (ein > 3.0e+6 && ein < 7.0e+6)
				{
					cout << scientific << setprecision(4);
					cout << setw(15) << ein;
					for (int iig = 0; iig < max_ng; iig++)
						cout << setw(15) << eadist.pl_coef[iig][0];
					cout << endl;
				}
			}
#endif
			vector<vector<REAL> >& matrix_wk = matrix[ib][ig];
			for (int iig = 0; iig < max_ng; iig++)
				for (int il = 0; il <= max_pl; il++)
					matrix_wk[iig][il] += eadist.pl_coef[iig][il] * val[il];
		}
	}
	for (int ig = 0; ig < max_ng; ig++)
	{
		for (int ib = 0; ib < num_bgxs; ib++)
		{
			for (int il = 0; il <= max_pl; il++)
			{
				if (weight[ib][ig][il] == 0.0) continue;
				xsave[ib][ig][il] /= weight[ib][ig][il];
				for (int iig = 0; iig < max_ng; iig++)
					matrix[ib][ig][iig][il] /= weight[ib][ig][il];
			}
		}
	}

	//save to the matrix_map
	vector<FMCompressedMatrix> fmc_vec;
	fmc_vec.resize(num_bgxs);
	for (int ib = 0; ib < num_bgxs; ib++)
		fmc_vec[ib].set(matrix[ib]);

	matrix_map.insert(make_pair(mt, fmc_vec));

}
void FMGenerator::getEnergyAngleDistribution(FMACECrossSectionProcessor& acexs, int mt, REAL ein, FMEneAngDist& eadist, FMEneAngDist& ead_wk)
{
	acexs.getEnergyAngleDistribution(mt, ein, eadist, ead_wk);

	if (mt != eMTElasticScattering) return;
	if (data_container.ruc_zaid.size() == 0) return;

	if (ein > RESO_UPSCAT_EMAX || ein < RESO_UPSCAT_EMIN) return;

	string zaid = acexs.getZaid();
	if (data_container.ruc_kernel_data.find(zaid) == data_container.ruc_kernel_data.end()) return;

	//resonance up-scattering data exists
	if (data_container.ruc_option[zaid] == eFMRUC1D) return;	//no correction on scattering matrix

	ead_wk.setZero();
	int ie = data_container.getUFgroup(ein);
	if (ie < data_container.ruc_uf_start_group || ie > data_container.ruc_uf_end_group) return;
	RUCKernelData& ruc_kernel = data_container.ruc_kernel_data[zaid][ie - data_container.ruc_uf_start_group];

	for (int i = 0; i < ead_wk.max_ng; i++)
	{
		if (ead_wk.ene_boundary[i + 1] > ruc_kernel.eout_upper) continue;
		if (ead_wk.ene_boundary[i] < ruc_kernel.eout_lower) continue;

		int ndiv = MAX_EOUT_DIV_ELASTIC;
		REAL e_upper = ead_wk.ene_boundary[i];
		REAL e_lower = ead_wk.ene_boundary[i + 1];
		for (int j = 0; j <= ndiv; j++)
		{
			REAL eol = (log(e_upper) - log(e_lower)) / (REAL)ndiv * (REAL)j + log(e_lower);
			REAL eou = (log(e_upper) - log(e_lower)) / (REAL)ndiv * (REAL)(j + 1) + log(e_lower);
			eol = exp(eol);
			eou = exp(eou);
			REAL eoa = sqrt(eol * eou);
			RUCKernelValue ker = ruc_kernel.getValue(eoa);
			ead_wk.pdf[i] += ker.p0 * (eou - eol);
			ead_wk.pl_coef[i][0] += ker.p0 * (eou - eol);
			for (int il = 1; il <= ead_wk.max_pl; il++)
			{
				if (il == 1)
					ead_wk.pl_coef[i][il] += ker.p1 * (eou - eol);
				else
					ead_wk.pl_coef[i][il] += 0.0;
			}
		}
	}
		
	//normalize transfer kernel
	ead_wk.normalize();

	//set to eadist
	for (int i = 0; i < ead_wk.max_ng; i++)
	{
		eadist.pdf[i] = ead_wk.pdf[i];
		for (int il = 0; il <= ead_wk.max_pl; il++)
			eadist.pl_coef[i][il] = ead_wk.pl_coef[i][il];
	}
}
void FMGenerator::calcThermalIncoherentCoherentElastic(FMACECrossSectionProcessor& acexs, string sab_name, int mt, map<int, vector<FMCompressedMatrix> >& matrix_map, map<int, vector<REAL> >& ratio_map)
{

	//set s(a,b) data
	FMACEThermalCrossSectionProcessor* acetxs = NULL;
	if (sab_name != "")
		acetxs = &data_container.ace_thermal_xs_data[sab_name];
	else
		return;

	if (acetxs->isElasticScattering() == false) return;

	//set number of energy groups, order of anisotropic scattering
	int max_ng = data_container.mg_max_num_energy;
	int max_pl = data_container.max_pl;

	//thermal cutoff energy
	REAL thermal_cutoff_ein = data_container.thermal_cutoff_ein;
	//REAL thermal_cutoff_eout = data_container.thermal_cutoff_eout;

	//relative target mass
	//REAL aw = acexs.getAW();
	//REAL temp = acexs.getKelvin();

	//check consistency
	if (acetxs != NULL)
	{
		if (acexs.getZa() != acetxs->getZa())
		{
			cout << " Nuclide id in fast and thermal ACE files are inconsistent " << endl;
			cout << " Fast    ACE : " << acexs.getZa() << endl;
			cout << " Thermal ACE : " << acetxs->getZa() << endl;
			exit(0);
		}
	}

	//reset energy transfer matrix
	vector<vector<vector<vector<REAL> > > > matrix;				//[ib][ig][iig][il]
	matrix.resize(1);		//only considers infinite dilute spectrum
	matrix[0].resize(max_ng);
	for (int ig = 0; ig < max_ng; ig++)
	{
		matrix[0][ig].resize(max_ng);
		for (int iig = 0; iig < max_ng; iig++)
		{
			matrix[0][ig][iig].resize(max_pl + 1);
			for (int il = 0; il <= max_pl; il++)
				matrix[0][ig][iig][il] = 0.0;
		}
	}

	//default spectrum
	//FMWeightingSpectrum& spectrum = data_container.weighting_spectrum;

	//set "panel" of incident energy
	vector<REAL> ein_boundary, ein_boundary_wk;
	for (int ig = 0; ig <= max_ng; ig++)
		ein_boundary_wk.push_back(data_container.mg_energy_boundary[ig]);

	//add Bragg-edges
	vector<REAL> add_ein_boundary;
	acetxs->getElasticEnergyGrids(add_ein_boundary);
	for (int i = 0; i < static_cast<int>(add_ein_boundary.size()); i++)
		add_ein_boundary[i] *= 1.0e6;
	addEnergyBoundary(ein_boundary_wk, add_ein_boundary);

	deleteNarrowEnergyBoundary(ein_boundary, ein_boundary_wk);

	//set sub-division
	int num_subdiv = subdivideEnergyBoundaryThermal(ein_boundary, thermal_cutoff_ein);

	vector<REAL> ein_boundary_mid;
	for (int ie = 0; ie < static_cast<int>(ein_boundary.size()) - 1; ie++)
	{
		REAL val = sqrt(ein_boundary[ie] * ein_boundary[ie + 1]);
		ein_boundary_mid.push_back(val);
	}

	//xsave ... group average cross section
	vector<REAL> xsave(max_ng);
	for (int i = 0; i < max_ng; i++)
		xsave[i] = 0.0;

	//weight ... flux*delta-E
	vector<REAL> weight(max_ng);
	for (int i = 0; i < max_ng; i++)
		weight[i] = 0.0;

	cout << endl;
	cout << setw(20) << acexs.getZaid() << " thermal incoherent/coherent  elastic scattering:  number of energy panel used for integration " << setw(4) << num_subdiv << endl;

	//upper and lower eint of s(a,b) table in ace file
	REAL sab_ein_upper, sab_ein_lower;
	if (acetxs != NULL) acetxs->getEinUpperLowerElastic(sab_ein_upper, sab_ein_lower);

	for (int ie = 0; ie < static_cast<int>(ein_boundary_mid.size()); ie++)
	{
		//REAL ein_upper = ein_boundary[ie];
		REAL ein_lower = ein_boundary[ie + 1];
		//consider actual thermal cutoff
		if (ein_lower >= thermal_cutoff_ein) continue;

		if (ie % 1000 == 0) cout << setw(20) << acexs.getZaid() << " doing integlation for ie = " << ie << endl;

		REAL ein = ein_boundary_mid[ie];
		REAL delta_ein = ein_boundary[ie] - ein_boundary[ie + 1];

		//calculate energy transfer probability
		int ig = data_container.getMGgroup(ein);

		REAL flx = data_container.getUFSpectrum(ein, 0, 0);		//P0 infinite dilute spectrum
		weight[ig] += flx * delta_ein;

		REAL xs_base = acetxs->getElasticXS(ein);
		xsave[ig] += xs_base * flx * delta_ein;

		vector<REAL> coef(max_pl+1);
		acetxs->getPlCoefElastic(ein, coef);

		for (int il = 0; il <= max_pl; il++)
			matrix[0][ig][ig][il] += coef[il] * xs_base * flx * delta_ein;
	}

	vector<REAL> ratio;
	ratio.resize(max_ng);
	for (int ig = 0; ig < max_ng; ig++)
		ratio[ig] = 1.0;

	for (int ig = 0; ig < max_ng; ig++)
	{
		if (weight[ig] == 0.0) continue;
		xsave[ig] /= weight[ig];
		for (int il = 0; il <= max_pl; il++)
			matrix[0][ig][ig][il] /= weight[ig];
	}

	//normalize
	for (int ig = 0; ig < max_ng; ig++)
	{
		if (xsave[ig] == 0.0) continue;
		REAL fact = xsave[ig] / matrix[0][ig][ig][0];
		for (int il = 0; il <= max_pl; il++)
			matrix[0][ig][ig][il] *= fact;
	}

	//save data
	if (mt != 0)
	{
		vector<FMCompressedMatrix> fmc_vec;
		fmc_vec.clear();
		fmc_vec.resize(matrix.size());
		for (int ib = 0; ib < (int)matrix.size(); ib++)
			fmc_vec[ib].set(matrix[ib]);

		matrix_map.insert(make_pair(mt, fmc_vec));
		ratio_map.insert(make_pair(mt, ratio));
	}

}
void FMGenerator::calcThermalIncoherentInelastic(FMACECrossSectionProcessor& acexs, string sab_name, int mt, map<int, vector<FMCompressedMatrix> >& matrix_map, map<int, vector<REAL> >& ratio_map)
{
	//set number of energy groups, order of anisotropic scattering
	int max_ng = data_container.mg_max_num_energy;
	int max_pl = data_container.max_pl;

	//thermal cutoff energy
	REAL thermal_cutoff_ein = data_container.thermal_cutoff_ein;
	REAL thermal_cutoff_eout = data_container.thermal_cutoff_eout;

	//relative target mass
	REAL aw = acexs.getAW();
	REAL temp = acexs.getKelvin();

	sab.initialize(max_pl, aw, temp, data_container.thermal_sab_torelance);
	if (data_container.thermal_freegas_sab_option == eFMThermalFreegasSabLinearInterpolation ||
		data_container.thermal_freegas_sab_option == eFMThermalFreegasSabQuadraticInterpolation)
		sab.prepSabFactorTable(thermal_cutoff_eout, data_container.mg_energy_boundary.back());

	//set s(a,b) data if necessary
	FMACEThermalCrossSectionProcessor* acetxs = NULL;
	sab.setEffectiveTemperature(temp);
	bool use_sct_approximation = false;
	if (sab_name != "")
	{
		acetxs = &data_container.ace_thermal_xs_data[sab_name];
		REAL teff = acetxs->getEffectiveTemperature();
		sab.setEffectiveTemperature(teff);
		if (data_container.use_sct_option == true) use_sct_approximation = true;
	}

	//check consistency
	if (acetxs != NULL)
	{
		if (acexs.getZa() != acetxs->getZa())
		{
			cout << " Nuclide id in fast and thermal ACE files are inconsistent " << endl;
			cout << " Fast    ACE : " << acexs.getZa() << endl;
			cout << " Thermal ACE : " << acetxs->getZa() << endl;
			exit(0);
		}
	}

	//reset energy transfer matrix
	vector<vector<vector<vector<REAL> > > > matrix;				//[ib][ig][iig][il]
	matrix.resize(1);		//only considers infinite dilute spectrum
	matrix[0].resize(max_ng);
	for (int ig = 0; ig < max_ng; ig++)
	{
		matrix[0][ig].resize(max_ng);
		for (int iig = 0; iig < max_ng; iig++)
		{
			matrix[0][ig][iig].resize(max_pl + 1);
			for (int il = 0; il <= max_pl; il++)
				matrix[0][ig][iig][il] = 0.0;
		}
	}

	//default spectrum
	//FMWeightingSpectrum& spectrum = data_container.weighting_spectrum;

	//set "panel" of incident energy
	vector<REAL> ein_boundary, ein_boundary_wk;
	vector<REAL> eout_boundary, eout_boundary_wk;
	for (int ig = 0; ig <= max_ng; ig++)
	{
		ein_boundary_wk.push_back(data_container.mg_energy_boundary[ig]);
		eout_boundary_wk.push_back(data_container.mg_energy_boundary[ig]);
	}
	vector<REAL> add_ein_boundary;
	vector<REAL> add_eout_boundary;
	add_eout_boundary.push_back(thermal_cutoff_eout);
	addEnergyBoundary(eout_boundary_wk, add_eout_boundary);
	addEnergyBoundary(ein_boundary_wk, add_ein_boundary);

	//add lowest boundary (below lowest energy boundary of multi-group energy structure)
	//the lowest boundary is assumed as 0.1*(lowest multi-group boundary)
	REAL lowest_energy = eout_boundary_wk.back() * 0.1;	
	eout_boundary_wk.push_back(lowest_energy);

	deleteNarrowEnergyBoundary(ein_boundary, ein_boundary_wk);
	deleteNarrowEnergyBoundary(eout_boundary, eout_boundary_wk);

	//set sub-division
	int num_subdiv = subdivideEnergyBoundaryThermal(ein_boundary, thermal_cutoff_ein);

	vector<REAL> ein_boundary_mid;
	for (int ie = 0; ie < static_cast<int>(ein_boundary.size()) - 1; ie++)
	{
		REAL val = sqrt(ein_boundary[ie] * ein_boundary[ie + 1]);
		ein_boundary_mid.push_back(val);
	}

	//calculate weight for each sub-division point
	vector<REAL> xfde_from_ufg;
	vector<REAL> fde_from_ufg;
	vector<REAL> de_from_ufg;
	xfde_from_ufg.resize(ein_boundary_mid.size());
	fde_from_ufg.resize(ein_boundary_mid.size());
	de_from_ufg.resize(ein_boundary_mid.size());
	for (int ie = 0; ie < static_cast<int>(ein_boundary_mid.size()); ie++)
	{
		de_from_ufg[ie] = 0.0;
		xfde_from_ufg[ie] = 0.0;
		fde_from_ufg[ie] = 0.0;
	}

	int ie = 0;
	vector<REAL> xs_temp;
	for (int iuf = 0; iuf < data_container.uf_max_num_energy; iuf++)
	{
		REAL ene = data_container.uf_energy_midpoint[iuf];
		if (ene > ein_boundary[0]) ie = 0;
		else if (ene < ein_boundary.back()) ie = ein_boundary.size() - 2;
		else
		{
			for (;;)
			{
				if (ene < ein_boundary[ie + 1]) ie++;
				else break;
			}
		}
		REAL de = data_container.uf_energy_delta[iuf];
		de_from_ufg[ie] += de;
		REAL xs = acexs.getXS(eMTElasticScattering, ene);
		if (acetxs != NULL)
		{
			REAL xst = acetxs->getIncoherentInelasticXS(ene);
			if (xst != 0.0) xs = xst;
		}

		//use only P0 flux since infinite dilute spectrum is used
		REAL flx = data_container.getUFSpectrum(iuf, 0);
		xfde_from_ufg[ie] += xs * flx * de;
		fde_from_ufg[ie] += flx * de;
	}

	for (ie = 0; ie < static_cast<int>(ein_boundary_mid.size()); ie++)
	{
		REAL de = ein_boundary[ie] - ein_boundary[ie + 1];
		if (de_from_ufg[ie] != 0.0)
		{
			REAL fact = de / de_from_ufg[ie];
			xfde_from_ufg[ie] *= fact;
			fde_from_ufg[ie] *= fact;
		}
		else
		{
			//set value if ultra-fine group is not sufficient to cover this energy range
			REAL ene = ein_boundary_mid[ie];
			REAL xs = acexs.getXS(eMTElasticScattering, ene);
			if (acetxs != NULL)
			{
				REAL xst = acetxs->getIncoherentInelasticXS(ene);
				if (xst != 0.0) xs = xst;
			}
			REAL flx = data_container.getUFSpectrum(ene, 0);
			xfde_from_ufg[ie] = xs * flx * de;
			fde_from_ufg[ie] = flx * de;
			de_from_ufg[ie] = de;
		}
	}


	//xsave ... group average cross section
	vector<REAL> xsave(max_ng);
	for (int i = 0; i < max_ng; i++)
		xsave[i] = 0.0;

	//sum_matrix      ... sum of matrix without consideration of thermal cutoff
	//sum_matrix_tcut ... sum of matrix with consideration of thermal cutoff
	vector<REAL> sum_matrix(max_ng);
	vector<REAL> sum_matrix_tcut(max_ng);
	for (int i = 0; i < max_ng; i++)
	{
		sum_matrix[i] = 0.0;
		sum_matrix_tcut[i] = 0.0;
	}

	//weight ... flux*delta-E
	vector<REAL> weight(max_ng);
	for (int i = 0; i < max_ng; i++)
		weight[i] = 0.0;

	cout << setw(20) << acexs.getZaid() << " thermal incoherent inelastic scattering        :  number of energy panel used for integration " << setw(5) << num_subdiv << endl;

	sab.resetNumIntegral();
	REAL num_integral = 0;

	//upper and lower eint of s(a,b) table in ace file
	REAL sab_ein_upper = 0.0;
	REAL sab_ein_lower = 0.0;
	if (acetxs != NULL) acetxs->getEinUpperLowerInelastic(sab_ein_upper, sab_ein_lower);

	for (ie = 0; ie < static_cast<int>(ein_boundary_mid.size()); ie++)
	{
		//REAL ein_upper = ein_boundary[ie];
		REAL ein_lower = ein_boundary[ie + 1];
		//consider actual thermal cutoff
		if (ein_lower >= thermal_cutoff_ein) continue;

		if (ie % 1000 == 0) cout << setw(20) << acexs.getZaid() << " doing integlation for ie = " << ie << endl;

		REAL ein = ein_boundary_mid[ie];
		//REAL delta_ein = ein_boundary[ie] - ein_boundary[ie + 1];

		//calculate energy transfer probability
		int ig = data_container.getMGgroup(ein);

		REAL wgt = fde_from_ufg[ie];	//infinite dilute spectrum
		weight[ig] += wgt;
		REAL xs_base = xfde_from_ufg[ie] / fde_from_ufg[ie];
		xsave[ig] += xs_base * wgt;

		//upper lower limit of s(a,b) in ace file
		REAL sab_eout_upper = 0.0;
		REAL sab_eout_lower = 0.0;
		if (acetxs != NULL) acetxs->getEoutUpperLowerInelastic(ein, sab_eout_upper, sab_eout_lower);

		//calculate probability distribution of outgoing energy
		for (int iie = 0; iie < static_cast<int>(eout_boundary.size()) - 1; iie++)
		{
			REAL eout_upper = eout_boundary[iie];
			REAL eout_lower = eout_boundary[iie + 1];
			if (eout_upper > thermal_cutoff_eout) continue;

			REAL du = 0.005;
			int iigwk = data_container.getMGgroup((eout_upper + eout_lower) / 2.0, true);
			if (abs(ig - iigwk) <= 1) du = 0.001;
			int ndiv = getNumberOfIntegrationPointsInEnergyGroupThermal(eout_upper, eout_lower, du);

			for (int j = 0; j < ndiv; j++)
			{
#if 1
				//direct integration
				//outgoing energy
				REAL eowk1 = (log(eout_upper) - log(eout_lower)) / (REAL)ndiv * (REAL)j + log(eout_lower);
				REAL eowk2 = (log(eout_upper) - log(eout_lower)) / (REAL)ndiv * (REAL)(j + 1) + log(eout_lower);
				REAL eout = exp((eowk1 + eowk2) / 2.0);
				eowk1 = exp(eowk1);
				eowk2 = exp(eowk2);
				REAL delta_eout = eowk2 - eowk1;

				int iig = data_container.getMGgroup(eout, true);
				vector<REAL> coef(max_pl + 1);

				if (acetxs != NULL &&
					ein >= sab_ein_lower && ein <= sab_ein_upper &&
					eowk1 >= sab_eout_lower && eowk2 <= sab_eout_upper)
				{
					acetxs->getPlCoefIncoherentInelastic(ein, eowk2, eowk1, coef);
					for (int il = 0; il <= max_pl; il++)
						coef[il] *= (xs_base/delta_eout);
				}
				else
				{
#if 0
					//previous adaptive integration method
					if (data_container.thermal_freegas_sab_option == eFMThermalFreegasSabExplicitIntegral)
						sab.getPlCoefOld(ein, eout, coef, false, use_sct_approximation);
#endif
#if 0
					//analytic solution up to P3, but suffered from severe numerical round off error
					if (data_container.thermal_freegas_sab_option == eFMThermalFreegasSabExplicitIntegral)
						calcThermalIncoherentScatteringXSFreeGasAngleIntegratedP3(max_pl, 1.0, aw, ein, eout, temp, coef);
#endif
#if 1
					//new adaptive integration method
					if (data_container.thermal_freegas_sab_option == eFMThermalFreegasSabExplicitIntegral)
						sab.getPlCoef(ein, eout, coef, false, use_sct_approximation);
#endif
					if (data_container.thermal_freegas_sab_option == eFMThermalFreegasSabLinearInterpolation)
						sab.getPlCoefUsingTableLinear(ein, eout, coef);
					if (data_container.thermal_freegas_sab_option == eFMThermalFreegasSabQuadraticInterpolation)
						sab.getPlCoefUsingTableQuadratic(ein, eout, coef);

					//normalize to analytically integrated value of P0 component
					REAL val = xs_base;
					if (coef[0] != 0.0)
					{
						REAL fact = calcThermalIncoherentScatteringXSFreeGasAngleIntegratedAndEoutAveraged(1.0, aw, ein, eowk2, eowk1, temp);
							if (use_sct_approximation == false)
								val = val * fact / coef [0];
					}

					for (int il = 0; il <= max_pl; il++)
						coef[il] *= val;
			}

				if (eout > ein && eout > thermal_cutoff_eout)
				{
					sum_matrix[ig] += coef[0] * wgt * delta_eout;
				}
				else
				{
					sum_matrix[ig] += coef[0] * wgt * delta_eout;
					sum_matrix_tcut[ig] += coef[0] * wgt * delta_eout;
					for (int il = 0; il <= max_pl; il++)
						matrix[0][ig][iig][il] += coef[il] * wgt * delta_eout;
				}
#else
				//use adaptive integration ... accurate but time consuming
				REAL e_lower = (log(eout_upper) - log(eout_lower)) / (REAL)ndiv * (REAL)j + log(eout_lower);
				REAL e_upper = (log(eout_upper) - log(eout_lower)) / (REAL)ndiv * (REAL)(j + 1) + log(eout_lower);
				e_lower = exp(e_lower);
				e_upper = exp(e_upper);
				calcThermalFreeGasAdaptiveIntegration(ig, max_pl, xs_base, wgt, ein, e_upper, e_lower, sum_matrix, sum_matrix_tcut, matrix);
#endif
			}
		}
	}

	cout << setw(20) << acexs.getZaid() << " thermal scattering : total number of angle integrations " << scientific << setprecision(3) << sab.getNumIntegral() << " " << num_integral << endl;

	for (int ig = 0; ig < max_ng; ig++)
	{
		if (weight[ig] == 0.0) continue;
		xsave[ig] /= weight[ig];
		for (int iig = 0; iig < max_ng; iig++)
		{
			for (int il = 0; il <= max_pl; il++)
				matrix[0][ig][iig][il] /= weight[ig];
		}
	}

	//sum of scattering considering tcut / that without considering tcut
	vector<REAL> ratio;
	ratio.resize(max_ng);
	for (int ig = 0; ig < max_ng; ig++)
	{
		ratio[ig] = 0.0;
		if (sum_matrix[ig] != 0.0) ratio[ig] = sum_matrix_tcut[ig] / sum_matrix[ig];
	}

	//normalize scattering matrix
	for (int ig = 0; ig < max_ng; ig++)
	{
		REAL sum = 0.0;
		for (int iig = 0; iig < max_ng; iig++)
			sum += matrix[0][ig][iig][0];
		if (sum != 0.0)
		{
			REAL fact = xsave[ig] * ratio[ig] / sum;
			for (int iig = 0; iig < max_ng; iig++)
			{
				for (int il = 0; il <= max_pl; il++)
					matrix[0][ig][iig][il] *= fact;
			}
		}
	}

	//save data
	vector<FMCompressedMatrix> fmc_vec;
	fmc_vec.resize(matrix.size());
	for (int ib = 0; ib < (int)matrix.size(); ib++)
		fmc_vec[ib].set(matrix[ib]);

	matrix_map.insert(make_pair(mt, fmc_vec));
	ratio_map.insert(make_pair(mt, ratio));


	if (data_container.edit_option.find(eEditOptionDebug) != data_container.edit_option.end())
	{
		ofstream of;
		of.open("FMThermalScatteringMatrixDebugInelastic.txt");
		of << scientific << setprecision(5);
		of << setw(6) << " ";
		of << setw(15) << " ";
		for (int iig = 92; iig < max_ng; iig++)
			of << setw(15) << sqrt(data_container.mg_energy_boundary[iig] * data_container.mg_energy_boundary[iig + 1]);
		of << endl;

		for (int ig = 92; ig < max_ng; ig++)
		{
			REAL sum = 0.0;
			for (int iig = 0; iig < max_ng; iig++)
				sum += matrix[0][ig][iig][0];

			of << setw(6) << ig;
			of << setw(15) << sqrt(data_container.mg_energy_boundary[ig] * data_container.mg_energy_boundary[ig + 1]);
			for (int iig = 92; iig < max_ng; iig++)
				of << setw(15) << matrix[0][ig][iig][0] / sum / (data_container.mg_energy_boundary[iig] - data_container.mg_energy_boundary[iig + 1]);
			of << endl;
		}
		of.close();
	}

}
REAL FMGenerator::calcThermalFreeGasNormalizationFactor(REAL ein, REAL aw, REAL temp, REAL e_upper, REAL e_lower, vector<REAL>& eout_boundary)
{
	int ig = data_container.getMGgroup(ein);

	REAL sum = 0.0;

	for (int iie = 0; iie < static_cast<int>(eout_boundary.size()) - 1; iie++)
	{
		REAL eout_upper = eout_boundary[iie];
		REAL eout_lower = eout_boundary[iie + 1];
		if (eout_upper > e_upper) continue;

		REAL du = 0.005;
		int iigwk = data_container.getMGgroup((eout_upper + eout_lower) / 2.0);
		if (abs(ig - iigwk) <= 1) du = 0.001;
		int ndiv = getNumberOfIntegrationPointsInEnergyGroupThermal(eout_upper, eout_lower, du);

		for (int j = 0; j < ndiv; j++)
		{
			//outgoing energy
			REAL eowk1 = (log(eout_upper) - log(eout_lower)) / (REAL)ndiv * (REAL)j + log(eout_lower);
			REAL eowk2 = (log(eout_upper) - log(eout_lower)) / (REAL)ndiv * (REAL)(j + 1) + log(eout_lower);
			//REAL eout = exp((eowk1 + eowk2) / 2.0);
			eowk1 = exp(eowk1);
			eowk2 = exp(eowk2);
			REAL delta_eout = eowk2 - eowk1;
			REAL fact = calcThermalIncoherentScatteringXSFreeGasAngleIntegratedAndEoutAveraged(1.0, aw, ein, eowk2, eowk1, temp);
			sum += fact * delta_eout;
		}
	}

	return sum;
}
void FMGenerator::calcThermalFreeGasAdaptiveIntegration(int ig, int max_pl, REAL xs_base, REAL wgt, REAL ein, REAL e_upper, REAL e_lower, vector<REAL>& sum_matrix, vector<REAL>& sum_matrix_tcut, vector<vector<vector<vector<REAL> > > >& matrix)
{

	//outgoing energy
	REAL eave = (e_upper + e_lower) / 2.0;
	REAL delta_eout = (e_upper - e_lower) / 2.0;


	//adaptive integration of s(a,b)
	vector<REAL> coef0, coef1, coefa;
	coef0.clear(); coef1.clear(); coefa.clear();
	coef0.resize(max_pl + 1);
	coef1.resize(max_pl + 1);
	coefa.resize(max_pl + 1);
	if (data_container.thermal_freegas_sab_option == eFMThermalFreegasSabExplicitIntegral)
	{
		sab.getPlCoef(ein, e_upper, coef0, true, false);
		sab.getPlCoef(ein, eave, coefa, true, false);
		sab.getPlCoef(ein, e_lower, coef1, true, false);
	}
	if (data_container.thermal_freegas_sab_option == eFMThermalFreegasSabLinearInterpolation)
	{
		sab.getPlCoefUsingTableLinear(ein, e_upper, coef0);
		sab.getPlCoefUsingTableLinear(ein, eave, coefa);
		sab.getPlCoefUsingTableLinear(ein, e_lower, coef1);
	}
	if (data_container.thermal_freegas_sab_option == eFMThermalFreegasSabQuadraticInterpolation)
	{
		sab.getPlCoefUsingTableQuadratic(ein, e_upper, coef0);
		sab.getPlCoefUsingTableQuadratic(ein, eave, coefa);
		sab.getPlCoefUsingTableQuadratic(ein, e_lower, coef1);
	}

	//check interpolation accuracy
	REAL ave = (coef0[0] + coef1[0]) / 2.0;
	REAL eps_rel = 0.0;
	REAL eps_dif = abs(ave - coefa[0]);
	REAL du = log(e_upper / e_lower);
	if (coefa[0] != 0.0) eps_rel = abs((ave - coefa[0]) / coefa[0]);
	if (eps_rel < data_container.thermal_sab_torelance || du < THERMAL_SAB_INTEGRATE_MIN_DELTA_LETHARGY ||
		eps_dif < data_container.thermal_sab_torelance*1.0e-3)
	{
		REAL val = xs_base;
		val = sab.checkEPS(val);
		for (int il = 0; il <= max_pl; il++)
		{
			coef0[il] *= val;
			coefa[il] *= val;
			coef1[il] *= val;
		}

		REAL eout0 = (e_upper + eave) / 2.0;
		REAL eout1 = (eave + e_lower) / 2.0;
		int iig0 = data_container.getMGgroup(eout0);
		int iig1 = data_container.getMGgroup(eout1);
		REAL thermal_cutoff_eout = data_container.thermal_cutoff_eout;
		if (eout0 > ein && eout0 > thermal_cutoff_eout)
		{
			sum_matrix[ig] += (coef0[0] + 2.0 * coefa[0]) / 3.0 * wgt * delta_eout;
			sum_matrix[ig] += (2.0 * coefa[0] + coef1[0]) / 3.0 * wgt * delta_eout;
		}
		else
		{
			sum_matrix[ig] += (coef0[0] + 2.0 * coefa[0]) / 3.0 * wgt * delta_eout;
			sum_matrix[ig] += (2.0 * coefa[0] + coef1[0]) / 3.0 * wgt * delta_eout;
			sum_matrix_tcut[ig] += (coef0[0] + 2.0 * coefa[0]) / 3.0 * wgt * delta_eout;
			sum_matrix_tcut[ig] += (2.0 * coefa[0] + coef1[0]) / 3.0 * wgt * delta_eout;
			for (int il = 0; il <= max_pl; il++)
			{
				matrix[0][ig][iig0][il] += (coef0[il] + 2.0 * coefa[il]) / 3.0 * wgt * delta_eout;
				matrix[0][ig][iig1][il] += (2.0 * coefa[il] + coef1[il]) / 3.0 * wgt * delta_eout;
			}
		}
	}
	else
	{
		calcThermalFreeGasAdaptiveIntegration(ig, max_pl, xs_base, wgt, ein, e_upper, eave, sum_matrix, sum_matrix_tcut, matrix);
		calcThermalFreeGasAdaptiveIntegration(ig, max_pl, xs_base, wgt, ein, eave, e_lower, sum_matrix, sum_matrix_tcut, matrix);
	}
}
void  FMGenerator::calcNuChi(FMACECrossSectionProcessor& acexs, vector<vector<vector<vector<REAL> > > >& fis_matrix,
	vector<REAL>& nu_t, vector<REAL>& nu_p, vector<REAL>& nu_d,
	vector<REAL>& chi_t, vector<REAL>& chi_p, vector<REAL>& chi_d,
	vector<vector<REAL> >& chi_d_independent, vector<REAL>& delayed_ratio,
	REAL& nu_prompt_sum, REAL& nu_delayed_sum)
{
	//set number of energy groups, order of anisotropic scattering
	int max_ng = data_container.mg_max_num_energy;

	//number of delayed neutron groups
	int num_dn_group = acexs.getNumDelayedNeutronGroups();

	//reset nu, chi
	nu_t.resize(max_ng);
	nu_p.resize(max_ng);
	nu_d.resize(max_ng);
	chi_t.resize(max_ng);
	chi_p.resize(max_ng);
	chi_d.resize(max_ng);
	chi_d_independent.resize(num_dn_group);
	delayed_ratio.resize(num_dn_group);
	for (int i = 0; i < num_dn_group; i++)
		chi_d_independent[i].resize(max_ng);

	for (int ig = 0; ig < max_ng; ig++)
	{
		nu_t[ig] = 0.0;
		nu_p[ig] = 0.0;
		nu_d[ig] = 0.0;
		chi_t[ig] = 0.0;
		chi_p[ig] = 0.0;
		chi_d[ig] = 0.0;
		for (int i = 0; i < num_dn_group; i++)
			chi_d_independent[i][ig] = 0.0;
	}
	for (int i = 0; i < num_dn_group; i++)
		delayed_ratio[i] = 0.0;

	//sig-f
	vector<REAL> sigf(max_ng);
	for (int ig = 0; ig < max_ng; ig++)
		sigf[ig] = 0.0;

	if (acexs.isNuTotal() == false) return;

	//set "panel" of incident energy
	vector<REAL> ein_boundary, ein_boundary_wk;
	for (int ig = 0; ig <= max_ng; ig++)
		ein_boundary_wk.push_back(data_container.mg_energy_boundary[ig]);
	vector<REAL> add_ein_boundary;
	for (int mt = 1; mt <= num_dn_group; mt++)
	{
		acexs.getIncidentEnergyGridInDLW(mt, data_container.mg_energy_boundary, add_ein_boundary, true);
		addEnergyBoundary(ein_boundary_wk, add_ein_boundary);
	}

	deleteNarrowEnergyBoundary(ein_boundary, ein_boundary_wk);

	//set sub-division
	//use coarser group sub-division since sub-division is insensitive to fission spectrum
	subdivideEnergyBoundary(ein_boundary, 0.01);
	vector<REAL> ein_boundary_mid;
	for (int ie = 0; ie < static_cast<int>(ein_boundary.size()) - 1; ie++)
	{
		REAL val = sqrt(ein_boundary[ie] * ein_boundary[ie + 1]);
		ein_boundary_mid.push_back(val);
	}

	//calculate weight for each sub-division point
	vector<vector<REAL> > nxfde_from_ufg;
	vector<REAL>		de_from_ufg;
	de_from_ufg.resize(ein_boundary_mid.size());
	for (int ie = 0; ie < static_cast<int>(ein_boundary_mid.size()); ie++)
		de_from_ufg[ie] = 0.0;
	nxfde_from_ufg.resize(num_dn_group);
	for (int i = 0; i < num_dn_group; i++)
	{
		nxfde_from_ufg[i].resize(ein_boundary_mid.size());
		for (int ie = 0; ie < static_cast<int>(ein_boundary_mid.size()); ie++)
			nxfde_from_ufg[i][ie] = 0.0;
	}

	int ie = 0;
	for (int iuf = 0; iuf < data_container.uf_max_num_energy; iuf++)
	{
		REAL ene = data_container.uf_energy_midpoint[iuf];
		if (ene > ein_boundary[0]) ie = 0;
		else if (ene < ein_boundary.back()) ie = ein_boundary.size() - 2;
		else
		{
			for (;;)
			{
				if (ene < ein_boundary[ie + 1]) ie++;
				else break;
			}
		}
		REAL de = data_container.uf_energy_delta[iuf];
		REAL xs = acexs.getFissionXS(ene);
		REAL nud = acexs.getNu(eNuDelayed, ene);
		REAL flx = data_container.getUFSpectrum(iuf, 0);		//use infinite dilute spectrum
		de_from_ufg[ie] += de;
		for (int idn = 0; idn < num_dn_group; idn++)
		{
			REAL ratio = acexs.getDelayedNeutronGroupRatio(idn+1, ene);
			nxfde_from_ufg[idn][ie] += nud * xs * de * flx * ratio;
		}
	}

	for (ie = 0; ie < static_cast<int>(ein_boundary_mid.size()); ie++)
	{
		REAL de = ein_boundary[ie] - ein_boundary[ie + 1];
		if (de_from_ufg[ie] != 0.0)
		{
			REAL fact = de / de_from_ufg[ie];
			for (int idn = 0; idn < num_dn_group; idn++)
				nxfde_from_ufg[idn][ie] *= fact;
		}
		else
		{
			//set value if ultra-fine group is not sufficient to cover this energy range
			REAL ene = ein_boundary_mid[ie];
			REAL xs = acexs.getFissionXS(ene);
			REAL nud = acexs.getNu(eNuDelayed, ene);
			REAL flx = data_container.getUFSpectrum(ene, 0, 0, eFMNarrowResonanceCalc);
			for (int idn = 0; idn < num_dn_group; idn++)
			{
				REAL ratio = acexs.getDelayedNeutronGroupRatio(idn + 1, ene);
				nxfde_from_ufg[idn][ie] = nud * xs * de * flx * ratio;
			}
		}
	}

	//weight ... flux*delta-E, xs*flux*delta-E, or nu*xs*flux*delta-E

	//assign isotropic scattering
	vector<REAL> mu, mu_boundary, pdf;
	int coord = eLaboratorySystem;
	mu_boundary.resize(MAX_MU_DIV + 1);
	mu_boundary[0] = -1.0;
	for (int i = 0; i < MAX_MU_DIV; i++)
	{
		REAL delta_mu = (1.0 - mu_boundary[0]) / (REAL)MAX_MU_DIV;
		mu_boundary[i + 1] = mu_boundary[i] + delta_mu;
	}
	//assign default pdf (=0.5)
	pdf.resize(mu_boundary.size());
	for (int i = 0; i < static_cast<int>(mu_boundary.size()); i++)
		pdf[i] = 1.0 / (1.0 - mu_boundary[0]);

	//clear temporary storage for MCEData
	acexs.clearMCDDataTemporary();
	acexs.clearEADDataTemporary();

	//calculation of delayed neutron spectrum, nu-total, nu-prompt, nu-delayed
	cout << setw(20) << acexs.getZaid() << " nu, chi : number of energy panel " << setw(4) << ein_boundary.size() - 2 << endl;

	//set temporay array to tally energy transfer probability
	FMEneAngDist eadist, ead_wk;
	eadist.resize(max_ng);
	eadist.resizePlCoef(0);
	eadist.setEnergyBoundary(data_container.mg_energy_boundary);
	ead_wk.resize(max_ng);
	ead_wk.resizePlCoef(0);
	ead_wk.setEnergyBoundary(data_container.mg_energy_boundary);

	//delayed neutrons spectrum, delayed neutron ratio
	for (ie = 0; ie < static_cast<int>(ein_boundary_mid.size()); ie++)
	{
		REAL ein = ein_boundary_mid[ie];
		//int ig = data_container.getMGgroup(ein);

		//calculate energy transfer probability
		for (int idn = 1; idn <= num_dn_group; idn++)
		{
			acexs.getEnergyDistributionwithDLW(idn, ein, mu_boundary, pdf, eadist, ead_wk, coord, true);

			REAL val = nxfde_from_ufg[idn - 1][ie];
			for (int iig = 0; iig < max_ng; iig++)
			{
				chi_d[iig] += eadist.pdf[iig] * val;
				chi_d_independent[idn-1][iig] += eadist.pdf[iig] * val;
			}
		}
	}
	REAL sum = 0.0;
	for (int i = 0; i < num_dn_group; i++)
		for (int ig = 0; ig < max_ng; ig++)
			delayed_ratio[i] += chi_d_independent[i][ig];
	for (int i = 0; i < num_dn_group; i++)
		sum += delayed_ratio[i];
	for (int i = 0; i < num_dn_group; i++)
	{
		if (sum != 0.0) delayed_ratio[i] /= sum;
	}

	sum = 0.0;
	for (int ig = 0; ig < max_ng; ig++)
		sum += chi_d[ig];
	for (int ig = 0; ig < max_ng; ig++)
	{
		if (sum != 0.0)
			chi_d[ig] /= sum;
	}
	for (int i = 0; i < num_dn_group; i++)
	{
		sum = 0.0;
		for (int ig = 0; ig < max_ng; ig++)
			sum += chi_d_independent[i][ig];
		for (int ig = 0; ig < max_ng; ig++)
		{
			if (sum != 0.0)
				chi_d_independent[i][ig] /= sum;
		}
	}

	//total, prompt, and delayed nu, sigf
	vector<REAL> wgt_fde(max_ng);
	vector<REAL> wgt_xfde(max_ng);
	for (int i = 0; i < max_ng; i++)
	{
		wgt_fde[i] = 0.0;
		wgt_xfde[i] = 0.0;
	}
	for (int iuf = 0; iuf < data_container.uf_max_num_energy; iuf++)
	{
		REAL ein = data_container.uf_energy_midpoint[iuf];
		REAL de = data_container.uf_energy_delta[iuf];

		int ig = data_container.getMGgroup(ein);
		REAL xs = acexs.getFissionXS(ein);
		REAL nut = acexs.getNu(eNuTotal, ein);
		REAL nud = acexs.getNu(eNuDelayed, ein);
		REAL flx = data_container.getUFSpectrum(ein, 0, 0, eFMNarrowResonanceCalc);
		REAL wgt_fde_wk = de * flx;
		REAL wgt_xfde_wk = xs * de * flx;
		wgt_fde[ig] += wgt_fde_wk;
		wgt_xfde[ig] += wgt_xfde_wk;

		nu_d[ig] += nud * wgt_xfde_wk;
		nu_t[ig] += nut * wgt_xfde_wk;
		nu_p[ig] += (nut - nud) * wgt_xfde_wk;
		sigf[ig] += wgt_xfde_wk;
	}

	sum = 0.0;
	for (int ig = 0; ig < max_ng; ig++)
	{
		if (wgt_xfde[ig] != 0.0)
		{
			nu_d[ig] /= wgt_xfde[ig];
			nu_t[ig] /= wgt_xfde[ig];
			nu_p[ig] /= wgt_xfde[ig];
		}
		if (wgt_fde[ig] != 0.0)
			sigf[ig] /= wgt_fde[ig];
	}

	//calculation of prompt chi
	int ib = 0;		//use infinite dilute cross sections
	REAL sumtot = 0.0;
	for (int ig = 0; ig < max_ng; ig++)
	{
		for (int iig = 0; iig < max_ng; iig++)
			sumtot += fis_matrix[ib][ig][iig][0] * wgt_fde[ig];
	}
	for (int ig = 0; ig < max_ng; ig++)
	{
		sum = 0.0;
		for (int iig = 0; iig < max_ng; iig++)
			sum += fis_matrix[ib][iig][ig][0] * wgt_fde[iig];
		if (sumtot != 0.0)
			chi_p[ig] = sum / sumtot;
	}
	vector<REAL> nu_p_wk(max_ng);
	for (int ig = 0; ig < max_ng; ig++)
	{
		sum = 0.0;
		for (int iig = 0; iig < max_ng; iig++)
			sum += fis_matrix[ib][ig][iig][0];
		if (sigf[ig] != 0.0)
			nu_p_wk[ig] = sum / sigf[ig];
	}

	//calculation of total chi
	nu_prompt_sum = 0.0;
	nu_delayed_sum = 0.0;
	for (int ig = 0; ig < max_ng; ig++)
	{
		for (int iig = 0; iig < max_ng; iig++)
			nu_prompt_sum += fis_matrix[ib][ig][iig][0] * wgt_fde[ig];
	}
	for (int ig = 0; ig < max_ng; ig++)
	{
		nu_delayed_sum += nu_d[ig] * sigf[ig] * wgt_fde[ig];
	}
	REAL nu_total_sum = nu_prompt_sum + nu_delayed_sum;

	for (int ig = 0; ig < max_ng; ig++)
	{
		sum = 0.0;
		for (int iig = 0; iig < max_ng; iig++)
			sum += chi_d[ig] * nu_d[iig] * sigf[iig] * wgt_fde[iig];
		for (int iig = 0; iig < max_ng; iig++)
			sum += fis_matrix[ib][iig][ig][0] * wgt_fde[iig];

		if (nu_total_sum != 0.0)
			chi_t[ig] = sum / nu_total_sum;
	}

	//normalize chi-p & chi-t
	DOUBLE sump = 0.0;
	DOUBLE sumt = 0.0;
	for (int ig = 0; ig < max_ng; ig++)
	{
		sump += chi_p[ig];
		sumt += chi_t[ig];
	}
	for (int ig = 0; ig < max_ng; ig++)
	{
		if (sump != 0.0)
			chi_p[ig] /= sump;
		if (sumt != 0.0)
			chi_t[ig] /= sumt;
	}
}

void FMGenerator::test_independent()
{
}
