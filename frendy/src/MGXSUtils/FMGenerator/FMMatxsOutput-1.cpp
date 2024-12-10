#pragma once

#include "MGXSUtils/FMGenerator/FMMatxsOutput.h"

using namespace FMGen;

void FMMatxsOutput::outputHeader()
{
	//check thermal scattering exists
	ntype = 2;
	if (dc->isThermalScattering(zaid) == false) ntype = 1;

	//calculate output block number
	calcBlockNumber();

	//output 0v
	of << " 0v   matxs *frendy/mg       *     1" << endl;

	//output 1d
	if (ntype == 1)
	{
		of << " 1d        1     1     9     1";
		of << setw(6) << MAXW;
		of << setw(6) << matxs_block_num.back() << endl;
	}
	else
	{
		of << " 1d        1     2     9     1";
		of << setw(6) << MAXW;
		of << setw(6) << matxs_block_num.back() << endl;
	}

	//output 2d
	of << " 2d" << endl;
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

	of << zaid;
	of << " : generated by frendy/mg at " << setfill('0') << setw(4) << year << "/"
		<< setw(2) << month << "/"
		<< setw(2) << day << " "
		<< setw(2) << hour << ":"
		<< setw(2) << minute << ":"
		<< setw(2) << second << endl;
	of << setfill(' ');

	//output 3d
	if (ntype == 2)
		of << " 3d     n       nscat   ntherm  ";
	else
		of << " 3d     n       nscat   ";
	za = dc->ace_xs_data[zaid].getZa();
	int iz = za / 1000;
	int ia = za - iz * 1000;
	FMElementNameConverter fenc;
	hmatn = fenc.getName(iz) + my_to_string(ia);
	transform(hmatn.begin(), hmatn.end(), hmatn.begin(), (int(*)(int)) tolower);
	of << hmatn << endl;

	//number of submaterials
	int ngrp = dc->mg_max_num_energy;
	of << setw(6) << ngrp;
	for (int i = 0; i < ntype; i++)
		of << setw(6) << 1;
	for (int i = 0; i < ntype; i++)
		of << setw(6) << 1;
	of << setw(6) << nsubm;
	of << setw(6) << 0;
	of << endl;

	//output 4d
	output4d7d9d10d(4, dc->mg_energy_boundary);
}
void FMMatxsOutput::calcBlockNumber()
{
	//number of submaterials
	nsubm = dc->background_xs_set.size() + ntype - 1;

	//set output xs mt
	dc->setOutputCrossSectionMT(zaid, xs1d_infdil, xs1d_shield, xs2d_infdil, xs2d_shield, xs2d_plorder, "matxs");

	//calculate block number (locs in matxs file)
	matxs_block_num.clear();
	bool thermal = false;
	int blknum_vec, blknum_mat;
	int numib = dc->background_xs_set.size();
	matxs_block_num.push_back(0);
	for (int ib = 0; ib < numib; ib++)
	{
		outputVectorData(thermal, ib, false, blknum_vec);
		outputMatrixData(thermal, ib, false, blknum_mat);
		int wk = blknum_vec + blknum_mat + matxs_block_num.back();
		matxs_block_num.push_back(wk);
	}

	if (ntype <= 1) return;

	//set thermal cross section
	xs_thermal.clear();
	map<int, vector<FMCompressedMatrix> >::iterator it2d;
	for (it2d = dc->xs_mg_2d_matrix[zaid].begin(); it2d != dc->xs_mg_2d_matrix[zaid].end(); it2d++)
	{
		if (isThermalMT(it2d->first) && it2d->first != eMTThermalFreeGas)
			xs_thermal.push_back(it2d->first);
	}
	if (xs_thermal.size() == 0) xs_thermal.push_back(eMTThermalFreeGas);

	//set block number for matxs file (locs for thermal cross section)
	thermal = true;
	int ib_infdil = 0;
	outputVectorData(thermal, ib_infdil, false, blknum_vec);
	outputMatrixData(thermal, ib_infdil, false, blknum_mat);
	int wk = blknum_vec + blknum_mat + matxs_block_num.back();
	matxs_block_num.push_back(wk);
}
void FMMatxsOutput::outputMaterialControl()
{
	int numib = dc->background_xs_set.size();

	//5d output infinite dilusion & shielded cases
	of << " 5d ";
	of << setw(8) << std::left << hmatn;
	of << scientific << setprecision(5);
	of << setw(12) << std::right << dc->ace_xs_data[zaid].getAW() << endl;
	of << setw(12) << std::right << dc->ace_xs_data[zaid].getKelvin();
	of << setw(12) << std::right << dc->background_xs_set[0];
	of << setw(6) << std::right << 1;
	of << setw(6) << std::right << xs1d_infdil.size();
	of << setw(6) << std::right << xs2d_infdil.size();
	of << setw(6) << std::right << matxs_block_num[0];
	of << endl;

	for (int ib = 1; ib < numib; ib++)
	{
		of << setw(12) << std::right << dc->ace_xs_data[zaid].getKelvin();
		of << setw(12) << std::right << dc->background_xs_set[ib];
		of << setw(6) << std::right << 1;
		of << setw(6) << xs1d_shield.size();
		of << setw(6) << std::right << xs2d_shield.size();
		of << setw(6) << std::right << matxs_block_num[ib];
		of << endl;
	}

	if (ntype <= 1) return;

	//5d output thermal cases
	of << setw(12) << std::right << dc->ace_xs_data[zaid].getKelvin();
	of << setw(12) << std::right << dc->background_xs_set[0];
	of << setw(6) << std::right << 2;
	of << setw(6) << std::right << xs_thermal.size();
	of << setw(6) << std::right << xs_thermal.size();
	of << setw(6) << std::right << matxs_block_num[numib];
	of << endl;
}
void FMMatxsOutput::outputVectorMatrix()
{
	int numib = dc->background_xs_set.size();	//ordinary cross section

	bool thermal = false;
	int blknum_vec, blknum_mat;
	for (int ib = 0; ib < numib; ib++)
	{
		outputVectorData(thermal, ib, true, blknum_vec);
		outputMatrixData(thermal, ib, true, blknum_mat);
	}

	if (ntype <= 1) return;

	thermal = true;
	int ib_infdil = 0;
	outputVectorData(thermal, ib_infdil, true, blknum_vec);
	outputMatrixData(thermal, ib_infdil, true, blknum_mat);

}
void FMMatxsOutput::outputVectorData(bool thermal, int ib, bool output, int& block_num)
{
	vector<int> nfgnlg;
	vector<vector<REAL> > vps_vec;
	vector<REAL> vps;
	vector<int>* xs1d_vec;

	if (thermal)
		xs1d_vec = &xs_thermal;
	else
	{
		if (ib == 0)
			xs1d_vec = &xs1d_infdil;
		else
			xs1d_vec = &xs1d_shield;
	}
	int n1d = xs1d_vec->size();

	nfgnlg.resize(n1d*2);

	vps.clear();
	vps_vec.clear();

	//6d
	int offset = 0;

	for (int i = 0; i < n1d; i++)
	{
		int mt = (*xs1d_vec)[i];
		vector<REAL> vec;
		vec.resize(dc->mg_max_num_energy);
		for (int ii = 0; ii < dc->mg_max_num_energy; ii++)
		{
			int ib_infdil = 0;
			if (ib == 0)
			{
				if (mt == eMTNWT0)
					vec[ii] = dc->flux_mg_1d_vector[1][ib][ii];
				else if (mt == eMTNWT1)
					vec[ii] = dc->flux_mg_1d_vector[-1][ib][ii];
				else if (mt == eMTNuTotal || mt == eMTNuDelayed || mt == eMTNuPrompt || mt == eMTChiDelayed)
					vec[ii] = dc->nuchi_mg_1d_vector[zaid][mt][ii];
				else if (dc->xs_mg_1d_vector[zaid].find(mt) != dc->xs_mg_1d_vector[zaid].end())
					vec[ii] = dc->xs_mg_1d_vector[zaid][mt][ib][ii];
				else
					vec[ii] = 0.0;
			}
			else
			{
				if (mt == eMTNWT0)
					vec[ii] = dc->flux_mg_1d_vector[1][ib][ii];
				else if (mt == eMTNWT1)
					vec[ii] = dc->flux_mg_1d_vector[-1][ib][ii];
				else if (dc->xs_mg_1d_vector[zaid].find(mt) != dc->xs_mg_1d_vector[zaid].end())
					vec[ii] = dc->xs_mg_1d_vector[zaid][mt][ib][ii] - dc->xs_mg_1d_vector[zaid][mt][ib_infdil][ii];
				else
					vec[ii] = 0.0;
			}
		}
		compressVectorData(vec, nfgnlg[i], nfgnlg[i+n1d]);

		int delta = nfgnlg[i + n1d] - nfgnlg[i] + 1;
		if (offset + delta + 1 > MAXW)
		{
			vps_vec.push_back(vps);
			vps.clear();
			offset = 0;
		}
		for (int ii = nfgnlg[i]; ii <= nfgnlg[i + n1d]; ii++)
			vps.push_back(vec[ii]);

		if (i == n1d - 1) vps_vec.push_back(vps);

		offset += delta;
	}

	block_num = 1 + vps_vec.size();

	if (output == false) return;

	of << " 6d     ";
	for (int i = 0; i < n1d; i++)
	{
		int mt = (*xs1d_vec)[i];
		of << setw(8) << std::left << convertMT2MatxsName(mt);
		if ((i + 2) % 9 == 0) of << endl;
	}
	if (n1d == 8) of << endl;				//this statement is necessary to be consistent with NJOY '(8X,8a8/(9a8))' format in fortran
	if ((n1d + 1) % 9 != 0) of << endl;

	for (int i = 0; i < n1d * 2; i++)
	{
		of << setw(6) << std::right << nfgnlg[i]+1;
		if ((i + 1) % 12 == 0) of << endl;
	}
	if ((n1d * 2) % 12 != 0) of << endl;

	//7d
	for (int i = 0; i < static_cast<int>(vps_vec.size()); i++)
		output4d7d9d10d(7, vps_vec[i]);

}
void FMMatxsOutput::outputMatrixData(bool thermal, int ib, bool output, int& block_num)
{
	vector<int>* xs2d_vec;
	if (thermal)
		xs2d_vec = &xs_thermal;
	else
	{
		if (ib == 0)
			xs2d_vec = &xs2d_infdil;
		else
			xs2d_vec = &xs2d_shield;
	}
	int n2d = xs2d_vec->size();

	int pl_order = dc->max_pl;
	vector<vector<vector<REAL> > > matrix;
	matrix.resize(dc->mg_max_num_energy);
	for (int i = 0; i < dc->mg_max_num_energy; i++)
	{
		matrix[i].resize(dc->mg_max_num_energy);
		for (int ii = 0; ii < dc->mg_max_num_energy; ii++)
			matrix[i][ii].resize(pl_order + 1);
	}

	block_num = 0;

	for (int i = 0; i < n2d; i++)
	{
		int mt = (*xs2d_vec)[i];
		if (dc->xs_mg_2d_matrix[zaid].find(mt) == dc->xs_mg_2d_matrix[zaid].end()) continue;

		vector<int> ijj, jband, jbandijj;
		int ib_infdil = 0;
		for (int j = 0; j < dc->mg_max_num_energy; j++)
			for (int ii = 0; ii < dc->mg_max_num_energy; ii++)
				for (int il = 0; il <= pl_order; il++)
				{
					if (ib == 0)
						matrix[j][ii][il] = dc->xs_mg_2d_matrix[zaid][mt][ib].get(j,ii,il);
					else
					{
						matrix[j][ii][il] = dc->xs_mg_2d_matrix[zaid][mt][ib].get(j,ii,il)
							- dc->xs_mg_2d_matrix[zaid][mt][ib_infdil].get(j,ii,il);
					}
				}

		//set maximum pl order for fission cross sections
		int pl_order_output = pl_order;
		if (xs2d_plorder.find(mt) != xs2d_plorder.end()) pl_order_output = xs2d_plorder[mt];

		vector<vector<REAL> > cmp_vec;
		compressMatrixData(pl_order_output, matrix, jband, ijj, cmp_vec);

		jbandijj.resize(dc->mg_max_num_energy * 2);
		for (int ii = 0; ii < dc->mg_max_num_energy; ii++)
		{
			jbandijj[ii] = jband[ii];
			jbandijj[ii+ dc->mg_max_num_energy] = ijj[ii] + 1;
		}
		
		block_num += 1 + cmp_vec.size();

		if (output == false) continue;

		of << " 8d     ";
		of << setw(8) << std::left << convertMT2MatxsName(mt);
		of << endl;
		of << setw(6) << std::right << pl_order_output + 1;	//lord
		of << setw(6) << std::right << 0;				//jconst .. constant vector is not used
		for (int ii = 0; ii < dc->mg_max_num_energy*2; ii++)
		{
			of << setw(6) << std::right << jbandijj[ii];
			if ((ii + 3) % 12 == 0) of << endl;
		}
		if ((dc->mg_max_num_energy * 2 + 2) % 12 != 0) of << endl;

		//9d
		for (int ii = 0; ii < static_cast<int>(cmp_vec.size()); ii++)
			output4d7d9d10d(9, cmp_vec[ii]);
	}
}
void FMMatxsOutput::compressVectorData(vector<REAL>& vec, int& sta, int& end)
{
	sta = 0;
	end = dc->mg_max_num_energy-1;

	for (int ig = 0; ig < dc->mg_max_num_energy; ig++)
	{
		sta = ig;
		if (fabs(vec[ig]) > 0.0) break;
	}
	for (int ig = dc->mg_max_num_energy-1; ig >= 0; ig--)
	{
		end = ig;
		if (fabs(vec[ig]) > 0.0) break;
	}

	if (sta > end)
	{
		//all elements are zero
		sta = 0;
		end = 0;
	}
}
void FMMatxsOutput::compressMatrixData(int pl_order, vector<vector<vector<REAL> > >& matrix, vector<int>& jband, vector<int>& ijj, vector<vector<REAL> >& cmp_vec)
{
	jband.resize(dc->mg_max_num_energy);
	ijj.resize(dc->mg_max_num_energy);

	//check total number of non-zero matrix elements
	int total_num = 0;

	//find ijj and jband in each group
	for (int iig = 0; iig < dc->mg_max_num_energy; iig++)
	{
		ijj[iig] = 0;
		jband[iig] = 0;
		for (int ig = dc->mg_max_num_energy - 1; ig >= 0; ig--)
		{
			for (int pl = 0; pl <= pl_order; pl++)
			{
				if (fabs(matrix[ig][iig][pl]) > 0.0)
				{
					if (ijj[iig] < ig) ijj[iig] = ig;
					int band = abs(ig - ijj[iig]) + 1;
					if (jband[iig] < band) jband[iig] = band;
				}
			}
		}
		total_num += jband[iig] * (pl_order + 1);
	}

	cmp_vec.clear();
	vector<REAL> wk;
	wk.clear();

	//encode cross section matrix to 1d vector
	int offset = 0;
	for (int iig = 0; iig < dc->mg_max_num_energy; iig++)
	{
		if (offset + jband[iig]*(pl_order+1) + 1 > MAXW)
		{
			cmp_vec.push_back(wk);
			offset = 0;
			wk.clear();
		}
		for (int pl = 0; pl <= pl_order; pl++)
		{
			int lower = ijj[iig];
			int upper = lower - jband[iig] + 1;
			for (int ig = lower; ig >= upper; ig--)
				wk.push_back(matrix[ig][iig][pl]);
			offset += lower - upper + 1;
		}
		if (iig == dc->mg_max_num_energy - 1) cmp_vec.push_back(wk);
	}

	int sum = 0;
	for (int i = 0; i < static_cast<int>(cmp_vec.size()); i++)
		sum += cmp_vec[i].size();

	if (sum != total_num)
		printError(" error in FMMatxsOutput::compressMatrixData");

}
void FMMatxsOutput::output4d7d9d10d(int name, vector<REAL>& vec)
{
	if (name == 4)
		of << " 4d         ";
	else if (name == 7)
		of << " 7d         ";
	else if (name == 9)
		of << " 9d         ";
	else if (name == 10)
		of << "10d         ";
	else
		return;

	of << scientific << setprecision(5);
	for (int i = 0; i < static_cast<int>(vec.size()); i++)
	{
		of << setw(12) << std::right << vec[i];
		if (i == 4) of << endl;
		if (i > 4 && (i + 2) % 6 == 0) of << endl;
	}
	if ((vec.size() + 1) % 6 != 0) of << endl;
}
