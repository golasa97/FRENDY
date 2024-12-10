#pragma once

#include "MGXSUtils/FMGenerator/FMGENDFOutput.h"

using namespace FMGen;

void FMGENDFOutput::output()
{
	outputMF1();

	dc->setOutputCrossSectionMT(zaid, xs1d_infdil, xs1d_shield, xs2d_infdil, xs2d_shield, xs2d_plorder, "gendf");

	//add thermal MT
	if (dc->isThermalScattering(zaid) == true)
	{
		map<int, vector<vector<REAL> > >::iterator it1d;
		bool add = false;
		for (it1d = dc->xs_mg_1d_vector[zaid].begin(); it1d != dc->xs_mg_1d_vector[zaid].end(); it1d++)
		{
			if (isThermalMT(it1d->first) && it1d->first != eMTThermalFreeGas)
			{
				xs1d_infdil.push_back(it1d->first);
				add = true;
			}
		}
		if (add == false) xs1d_infdil.push_back(eMTThermalFreeGas);
		map<int, vector<FMCompressedMatrix> >::iterator it2d;
		add = false;
		for (it2d = dc->xs_mg_2d_matrix[zaid].begin(); it2d != dc->xs_mg_2d_matrix[zaid].end(); it2d++)
		{
			if (isThermalMT(it2d->first) && it2d->first != eMTThermalFreeGas)
			{
				xs2d_infdil.push_back(it2d->first);
				add = true;
			}
		}
		if (add == false) xs2d_infdil.push_back(eMTThermalFreeGas);
	}

	//sort mt number
	sort(xs1d_infdil.begin(), xs1d_infdil.end());
	sort(xs1d_shield.begin(), xs1d_shield.end());
	sort(xs2d_infdil.begin(), xs2d_infdil.end());
	sort(xs2d_shield.begin(), xs2d_shield.end());

	outputMF3();

	outputMF5();

	outputMF6();

	int line_no = 0;
	outputToFile(" ", 0, 0, 0, line_no);
	line_no = 0;
	outputToFile(" ", -1, 0, 0, line_no);


}
void FMGENDFOutput::outputMF1()
{
	//first line
	time_t now;
	int year, month, day;
	int hour, minute, second;
	struct tm date;
	time(&now);
#ifdef _MSC_VER
	localtime_s(&date, &now);
#else
	localtime_r(&now, &date);
#endif
	year = date.tm_year + 1900;
	month = date.tm_mon + 1;
	day = date.tm_mday;
	hour = date.tm_hour;
	minute = date.tm_min;
	second = date.tm_sec;

	stringstream ss;
	ss << zaid;
	ss << " : frendy/mg at " << setfill('0') << setw(4) << year << "/"
		<< setw(2) << month << "/"
		<< setw(2) << day << " "
		<< setw(2) << hour << ":"
		<< setw(2) << minute << ":"
		<< setw(2) << second;
	ss << setfill(' ');

	vector<string> data;
	endf_id = 0;
	int mf = 0;
	int mt = 0;
	int line_no = 0;
	outputToFile(ss.str(), endf_id, mf, mt, line_no);

	//second line
	za = dc->ace_xs_data[zaid].getZa();
	setDataREAL((REAL)za, data);
	aw = dc->ace_xs_data[zaid].getAW();
	setDataREAL(aw, data);
	setDataInt(0, data);
	int sigb_num = dc->background_xs_set.size();
	setDataInt(sigb_num, data);
	setDataInt(-1, data);
	int ntw = 1;
	setDataInt(ntw, data);
	endf_id = dc->endf_id_list[zaid];
	mf = 1;
	mt = 451;
	line_no = 1;
	outputToFile(data, endf_id, mf, mt, line_no);

	//third line
	temp = dc->ace_xs_data[zaid].getKelvin();
	setDataREAL(temp, data);
	setDataREAL(0.0, data);
	int mg_num = dc->mg_max_num_energy;
	setDataInt(mg_num, data);
	int ngg = 0;
	setDataInt(ngg, data);
	int nw = mg_num + 1 + sigb_num + 2;
	setDataInt(nw, data);
	setDataInt(0, data);
	outputToFile(data, endf_id, mf, mt, line_no);

	//title (assumed to be 0.0)
	setDataREAL(0.0, data);
	//sigb
	for (int i = 0; i < sigb_num; i++)
		setDataREAL(dc->background_xs_set[i], data);
	//mg energy boundary
	for (int i = 0; i <= mg_num; i++)
		setDataREAL(dc->mg_energy_boundary[mg_num - i], data);
	//gamma mg energy boundary
	setDataREAL(0.0, data);

	outputToFile(data, endf_id, mf, mt, line_no);

	//separation between mf = 1 and mf = 3
	mf = 0;
	mt = 0;
	line_no = 0;
	outputToFile(" ", endf_id, mf, mt, line_no);

}
void FMGENDFOutput::outputMF3()
{
	vector<string> data;
	int mf = 3;
	//int mt = 0;
	int line_no = 0;
	int mg_num = dc->mg_max_num_energy;
#if 0
	vector<REAL> flux(mg_num);
	vector<REAL> xsdata(mg_num);
	vector<REAL> nuchi(mg_num);
	for (int i = 0; i < mg_num; i++)
	{
		flux[i] = (REAL)i / 10.0;
		xsdata[i] = (REAL)i / 100.0;
		nuchi[i] = (REAL)i / 1.0;
	}
#endif

	for (int im = 0; im < static_cast<int>(xs1d_infdil.size()); im++)
	{
		int mt = xs1d_infdil[im];
		if (mt == eMTTotalCurrentWeight) continue;
		if (mt == eMTNWT0) continue;
		if (mt == eMTNWT1) continue;
		if (mt == eMTChiDelayed) continue;

		setDataREAL((REAL)za, data);
		setDataREAL(aw, data);

		int nl = 1;
		if (mt == eMTTotal) nl = 2;
		setDataInt(nl, data);

		int nz = dc->background_xs_set.size();
		if (is1dShieldXS(mt) == false) nz = 1;
		setDataInt(nz, data);

		int lrflag = 0;
		setDataInt(lrflag, data);

		setDataInt(mg_num, data);

		line_no = 1;
		outputToFile(data, endf_id, mf, mt, line_no);

		for (int ig = 0; ig < mg_num; ig++)
		{
			int igidx = mg_num - 1 - ig;
			setDataREAL(temp, data);
			setDataREAL(0.0, data);
			int ng2 = 2;
			if (mt == eMTAverageMubar) ng2 = 3;
			if (mt == eMTNuTotal) ng2 = 3;
			if (mt == eMTNuDelayed) ng2 = 3;
			if (mt == eMTNuPrompt) ng2 = 3;
			if (mt == eMTAverageMubar) ng2 = 3;
			if (mt == eMTSlowingDownXi) ng2 = 2;
			if (mt == eMTSlowingDownGamma) ng2 = 2;
			setDataInt(ng2, data);
			int ig2lo = 1;
			setDataInt(ig2lo, data);
			int nw = nl * nz * ng2;
			setDataInt(nw, data);
			setDataInt(ig+1, data);

			vector<string> data2;
			//flux
			for (int iz = 0; iz < nz; iz++)
			{
				REAL val = dc->flux_mg_1d_vector[1][iz][igidx];
				setDataREAL(val, data2);
				if (nl != 1)
				{
					val = dc->flux_mg_1d_vector[-1][iz][igidx];
					setDataREAL(val, data2);
				}
			}

			//cross sections
			REAL sum = 0.0;
			if (mt == eMTNuTotal || mt == eMTNuDelayed || mt == eMTNuPrompt)
			{
				REAL val;
				for (int iz = 0; iz < nz; iz++)
				{
					val = 0.0;
					if (dc->nuchi_mg_1d_vector[zaid].find(mt) != dc->nuchi_mg_1d_vector[zaid].end())
						val = dc->nuchi_mg_1d_vector[zaid][mt][igidx];
					setDataREAL(val, data2);
					sum += abs(val);
				}
				for (int iz = 0; iz < nz; iz++)
				{
					val = dc->xs_mg_1d_vector[zaid][eMTFission][iz][igidx];
					setDataREAL(val, data2);
				}
			}
			else if (mt == eMTAverageMubar)
			{
				REAL val;
				for (int iz = 0; iz < nz; iz++)
				{
					val = 0.0;
					if (dc->xs_mg_1d_vector[zaid].find(mt) != dc->xs_mg_1d_vector[zaid].end())
						val = dc->xs_mg_1d_vector[zaid][mt][iz][igidx];
					setDataREAL(val, data2);
					sum += abs(val);
				}
				for (int iz = 0; iz < nz; iz++)
				{
					val = dc->xs_mg_1d_vector[zaid][eMTElasticScattering][iz][igidx];
					setDataREAL(val, data2);
				}
			}
			else
			{
				for (int iz = 0; iz < nz; iz++)
				{
					REAL val = 0.0;
					if (dc->xs_mg_1d_vector[zaid].find(mt) != dc->xs_mg_1d_vector[zaid].end())
						val = dc->xs_mg_1d_vector[zaid][mt][iz][igidx];
					setDataREAL(val, data2);
					sum += abs(val);
					if (nl != 1)
					{
						val = dc->xs_mg_1d_vector[zaid][eMTTotalCurrentWeight][iz][igidx];
						setDataREAL(val, data2);
						sum += abs(val);
					}
				}
			}
#if 0
			for (int iz = 0; iz < nz; iz++)
			{
				REAL val = 0.0;
				if (mt == eMTNuTotal || mt == eMTNuDelayed || mt == eMTNuPrompt)
					val = dc->nuchi_mg_1d_vector[zaid][mt][igidx];
				else if (dc->xs_mg_1d_vector[zaid].find(mt) != dc->xs_mg_1d_vector[zaid].end())
					val = dc->xs_mg_1d_vector[zaid][mt][iz][igidx];
				setDataREAL(val, data2);
				sum += abs(val);
				if (nl != 1)
				{
					val = dc->xs_mg_1d_vector[zaid][eMTTotalCurrentWeight][iz][igidx];
					setDataREAL(val, data2);
					sum += abs(val);
				}
				if (mt == eMTAverageMubar)
				{
					val = dc->xs_mg_1d_vector[zaid][eMTElasticScattering][iz][igidx];
					setDataREAL(val, data2);
				}
				if (mt == eMTNuTotal || mt == eMTNuDelayed || mt == eMTNuPrompt)
				{
					val = dc->xs_mg_1d_vector[zaid][eMTFission][iz][igidx];
					setDataREAL(val, data2);
				}
			}
#endif
			if (sum != 0.0 || ig == mg_num - 1)
			{
				outputToFile(data,  endf_id, mf, mt, line_no);
				outputToFile(data2, endf_id, mf, mt, line_no);
			}
			else
			{
				data.clear();
				data2.clear();
			}
		}

		//terminate
		line_no = 99999;
		outputToFile(" ", endf_id, mf, 0, line_no);
	}
}
void FMGENDFOutput::outputMF5()
{
	if (dc->nuchi_mg_1d_vector[zaid].find(eMTChiDelayed) == dc->nuchi_mg_1d_vector[zaid].end())
	{
		return;
	}
	else
	{
		bool chi_d = false;
		for (int i = 0; i < (int)xs1d_infdil.size(); i++)
		{
			if (xs1d_infdil[i] == eMTChiDelayed)
			{
				chi_d = true;
				break;
			}
		}
		if (chi_d == false) return;
	}

	FMACECrossSectionProcessor& acexs = dc->ace_xs_data[zaid];
	int num_dn_group = acexs.getNumDelayedNeutronGroups();
	int mg_num = dc->mg_max_num_energy;

	int is = 0;
	int ie = mg_num - 1;

	for (int ig = mg_num-1; ig >= 0; ig--)
	{
		if (dc->nuchi_mg_1d_vector[zaid][eMTChiDelayed][ig] != 0.0)
		{
			ie = ig;
			break;
		}
	}

	for (int ig = 0; ig < mg_num; ig++)
	{
		if (dc->nuchi_mg_1d_vector[zaid][eMTChiDelayed][ig] != 0.0)
		{
			is = ig;
			break;
		}
	}

	int ig2lo = mg_num - 1 - ie + 1;
	int ng2 = ie - is + 1;

	vector<string> data;

	setDataREAL((REAL)za, data);
	setDataREAL(aw, data);
	setDataInt(num_dn_group, data);
	int nz = 1;
	setDataInt(nz, data);
	int lrflag = 0;
	setDataInt(lrflag, data);
	setDataInt(mg_num, data);

	int line_no = 1;
	int mf = 5;
	int mt = 455;
	outputToFile(data, endf_id, mf, mt, line_no);

	setDataREAL(temp, data);
	setDataREAL(0.0, data);
	setDataInt(ng2+1, data);
	setDataInt(ig2lo, data);
	int nw = num_dn_group * nz * (ng2+1);
	setDataInt(nw, data);
	setDataInt(mg_num, data);
	outputToFile(data, endf_id, mf, mt, line_no);

	for (int il = 0; il < num_dn_group; il++)
	{
		REAL lambda = acexs.getDelayedNeutronDecayConstant(il+1);
		setDataREAL(lambda, data);
	}
	for (int in = 0; in < ng2; in++)
	{
		int igidx = ig2lo - 1 + in;
		int ig = mg_num - 1 - igidx;
		for (int il = 0; il < num_dn_group; il++)
		{
			REAL chid = dc->chi_d_independent[zaid][il][ig];
			chid *= dc->delayed_ratio[zaid][il];
			setDataREAL(chid, data);
		}
	}
	outputToFile(data, endf_id, mf, mt, line_no);

	//terminate
	line_no = 99999;
	outputToFile(" ", endf_id, mf, 0, line_no);
}
void FMGENDFOutput::outputMF6()
{
	vector<string> data;
	int mf = 6;
	//int mt = 0;
	int line_no = 0;
	int mg_num = dc->mg_max_num_energy;
#if 0
	vector<REAL> flux(mg_num);
	vector<vector<REAL> > xsdata(mg_num);
	for (int i = 0; i < mg_num; i++)
	{
		flux[i] = (REAL)(i+1) / 10.0;
		xsdata[i].resize(mg_num);
		int is = i - 2;
		if (is < 0) is = 0;
		int ie = i + 2;
		if (ie >= mg_num) ie = mg_num;
		for (int j = 0; j < mg_num; j++)
			xsdata[i][j] = 0.0;
		for (int j = is; j < ie; j++)
		{
			xsdata[i][j] = (REAL)(1000 * (i+1) + (j+1));
		}
	}
#endif

	for (int im = 0; im < static_cast<int>(xs2d_infdil.size()); im++)
	{
		int mt = xs2d_infdil[im];

		setDataREAL((REAL)za, data);
		setDataREAL(aw, data);

		int nl = dc->max_pl+1;

		//set maximum pl order for fission cross sections
		if (xs2d_plorder.find(mt) != xs2d_plorder.end()) nl = xs2d_plorder[mt] + 1;

		setDataInt(nl, data);

		int nz = dc->background_xs_set.size();
		if (is2dShieldXS(mt) == false) nz = 1;
		setDataInt(nz, data);

		int lrflag = 0;
		setDataInt(lrflag, data);

		setDataInt(mg_num, data);

		line_no = 1;
		outputToFile(data, endf_id, mf, mt, line_no);

		vector<int> ng2;
		vector<int> ig2lo;
		getNG2IG2LO(mt, ng2, ig2lo);

		//output fission spectrum only for "SimpleGENDF" case, which corresponds to NJOY99
		if (mt == eMTFission)
		{
			setDataREAL(temp, data);
			setDataREAL(0.0, data);
			setDataInt(mg_num, data);
			setDataInt(1, data);
			setDataInt(mg_num, data);
			setDataInt(0, data);
			REAL sum = 0.0;
			for (int igg = 0; igg < mg_num; igg++)
			{
				REAL val = dc->getNuChiMG1DVector(zaid, eMTChiTotal, mg_num-igg-1);
				setDataREAL(val, data);
				sum += abs(val);
			}
			if (sum != 0.0)
				outputToFile(data, endf_id, mf, mt, line_no);
			else
				data.clear();
		}

		for (int ig = 0; ig < mg_num; ig++)
		{
			int igidx = mg_num - 1 - ig;
			setDataREAL(temp, data);
			setDataREAL(0.0, data);
			setDataInt(ng2[igidx], data);
			setDataInt(ig2lo[igidx], data);
			int nw = nl * nz * ng2[igidx];
			setDataInt(nw, data);
			setDataInt(ig+1, data);

			vector<string> data2;
			//flux
			for (int iz = 0; iz < nz; iz++)
			{
				REAL val = dc->flux_mg_1d_vector[1][iz][igidx];
				setDataREAL(val, data2);
				for (int il = 1; il < nl; il++)
				{
					val = dc->flux_mg_1d_vector[-1][iz][igidx];
					setDataREAL(val, data2);
				}
			}

			//cross sections
			REAL sum = 0.0;
			for (int igg = 0; igg < ng2[igidx]-1; igg++)
			{
				for (int iz = 0; iz < nz; iz++)
				{
					for (int il = 0; il < nl; il++)
					{
						int iggidx = mg_num - ig2lo[igidx] - igg;
						REAL val = dc->xs_mg_2d_matrix[zaid][mt][iz].get(igidx,iggidx,il);
						setDataREAL(val, data2);
						sum += abs(val);
					}
				}
			}
			if (sum != 0.0 || ig == mg_num - 1)
			{
				outputToFile(data, endf_id, mf, mt, line_no);
				outputToFile(data2, endf_id, mf, mt, line_no);
			}
			else
			{
				data.clear();
				data2.clear();
			}
		}

		//terminate
		line_no = 99999;
		outputToFile(" ", endf_id, mf, 0, line_no);
	}
}
