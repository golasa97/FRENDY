#pragma once
#include"MGXSUtils/FMGenerator/FMGenerator.h"
#include"MGXSUtils/FMGenerator/FMACEThermalCrossSectionProcessor.h"
#include <fstream>
#include <sstream>

using namespace FMGen;

void FMACEThermalCrossSectionProcessor::readHeaderData(string fname)
{
	file_name = fname;

	//open ACE file
	ifstream fin;
	fin.open(file_name.c_str());
	if (!fin)
	{
		cout << " Error while open ACE file " << file_name << endl;
		exit(0);
	}

	//read title part
	string buf;
	vector<string> buf_vec;
	for (int i = 0; i < 2; i++)
	{
		getline(fin, buf);
		title.push_back(buf);
	}

	//read izaw array
	for (int j = 0; j < 4; j++)
	{
		getline(fin, buf);
		splitToToken(buf, buf_vec);
		for (int i = 0; i < static_cast<int>(buf_vec.size()); i++)
			izaw.push_back(my_stoi(buf_vec[i]));
	}

	//read NXS array
	for (int j = 0; j < 2; j++)
	{
		getline(fin, buf);
		splitToToken(buf, buf_vec);
		for (int i = 0; i < static_cast<int>(buf_vec.size()); i++)
			nxs.push_back(my_stoi(buf_vec[i]));
	}

	//read JXS array
	vector<int> jxs_array;
	for (int i = 0; i < 4; i++)
	{
		getline(fin, buf);
		splitToToken(buf, buf_vec);
		for (int j = 0; j < static_cast<int>(buf_vec.size()); j++)
			jxs.push_back(my_stoi(buf_vec[j]));
	}

	fin.close();
}
void FMACEThermalCrossSectionProcessor::processHeaderData( )
{
	//title part
	vector<string> buf_vec;
	splitToToken(title[0], buf_vec);
	zaid = buf_vec[0];
	za = izaw[0];
	aw = my_stod(buf_vec[1]);
	temp_kelvin = my_stod(buf_vec[2])*1.0e+6 / BOLTZMANN_CONSTANT;

	//NXS array
	table_length = nxs[0];
	idpni = nxs[1];
	nil   = nxs[2];
	nieb  = nxs[3];
	idpnc = nxs[4];
	ncl   = nxs[5];
	ifeng = nxs[6];

	print2ndHeader(" Contents of ACE file (thermal s(a,b))");
	cout << scientific << setprecision(7);
	cout << " File name                                                     : " << file_name << endl;
	cout << " ZA                                                            : " << za << endl;
	cout << " ZAID                                                          : " << zaid << endl;
	cout << " AW                                                            : " << aw << endl;
	cout << " Temperature[K]                                                : " << temp_kelvin << endl;
	cout << " Length of table                                               : " << table_length << endl;
	cout << " Inelastic scattering mode(IDPNI)                              : " << idpni << endl;
	cout << " Inelastic dimensioning parameter(NIL)                         : " << nil << endl;
	cout << " Number of inelastic exting energies(NIEB)                     : " << nieb << endl;
	cout << " Elastic scattering mode (coherent=4, incoherent!=4)(IDPNC)    : " << idpnc << endl;
	cout << " Elastic dimensioning parameter (NCL)                          : " << ncl << endl;
	cout << " Secondary energy mode(IFENG)                                  : " << ifeng << endl;
	cout << " Coherent elastic scattering data (0/1=No/Yes)                 : " << isCoherentElasticScattering() << endl;
	cout << " Incoherent elastic scattering data (0/1=No/Yes)               : " << isIncoherentElasticScattering() << endl;
	cout << " Processed date                                                : " << buf_vec[3] << endl;
	cout << endl;
	cout << scientific << setprecision(5);
}
void FMACEThermalCrossSectionProcessor::readXSData()
{
	//conventional version
	//open ACE file
	ifstream fin;
	fin.open(file_name.c_str());
	if (!fin)
	{
		cout << " Error while open ACE file " << file_name << endl;
		exit(0);
	}

	string buf;
	vector<string> buf_vec;

	//skip first lines
	for (int i = 0; i < 12; i++)
		getline(fin, buf);

	//read xss large array
	for (;;)
	{
		REAL val;
		fin >> val;
		if (fin.eof()) break;
		xss.push_back(val);
	}
}
void FMACEThermalCrossSectionProcessor::processXSData()
{
	int offset;
	//ITIE blocl
	offset = jxs[0] - 1;
	itie_data.nin = rtoi(xss[offset]);
	itie_data.ein.resize(itie_data.nin);
	itie_data.sigin.resize(itie_data.nin);
	for (int i = 0; i < itie_data.nin; i++)
	{
		itie_data.ein[i] = xss[offset + 1 + i];
		itie_data.sigin[i] = xss[offset + 1 + itie_data.nin + i];
	}

	//ITCE block
	offset = jxs[3] - 1;
	if (jxs[3] != 0)
	{
		itce_data.nel = rtoi(xss[offset]);
		itce_data.eel.resize(itce_data.nel);
		itce_data.p.resize(itce_data.nel);
		for (int i = 0; i < itce_data.nel; i++)
		{
			itce_data.eel[i] = xss[offset + 1 + i];
			itce_data.p[i] = xss[offset + 1 + itce_data.nel + i];
		}
	}
	
	//ITXE block
	itxe_data.resize(itie_data.nin);
	if (ifeng < 2)
	{
		offset = jxs[2] - 1;
		int nmu = nil + 1;
		for (int in = 0; in < itie_data.nin; in++)
		{
			itxe_data[in].resize(nieb);
			for (int out = 0; out < nieb; out++)
			{
				itxe_data[in][out].mu.resize(nmu);
				itxe_data[in][out].eout = xss[offset];
				for (int i = 0; i < nmu; i++)
					itxe_data[in][out].mu[i] = xss[offset + 1 + i];
				offset += nmu + 1;
			}

			//set pdf & cdf
			for (int out = 0; out < nieb; out++)
			{
				if (ifeng == 0)
					itxe_data[in][out].pdf = 1.0;
				else
				{
					itxe_data[in][out].pdf = 10.0;
					if (out == 0) itxe_data[in][out].pdf = 1.0;
					if (out == 1) itxe_data[in][out].pdf = 4.0;
					if (out == nieb - 2) itxe_data[in][out].pdf = 4.0;
					if (out == nieb - 1) itxe_data[in][out].pdf = 1.0;
				}
			}
			REAL sum = 0.0;
			for (int out = 0; out < nieb; out++)
				sum += itxe_data[in][out].pdf;
			if (sum != 0.0)
			{
				for (int out = 0; out < nieb; out++)
					itxe_data[in][out].pdf /= sum;
			}
			for (int out = 0; out < nieb; out++)
			{
				if (out == 0)
					itxe_data[in][out].cdf = itxe_data[in][out].pdf;
				else
					itxe_data[in][out].cdf = itxe_data[in][out].pdf + itxe_data[in][out-1].cdf;
			}
		}
	}
	else
	{
		int jxs2 = jxs[2] - 1;
		int nmu = nil - 1;
		for (int in = 0; in < itie_data.nin; in++)
		{
			offset = rtoi(xss[jxs2 + in]);
			int nout = rtoi(xss[jxs2 + itie_data.nin + in]);
			itxe_data[in].resize(nout);
			for (int out = 0; out < nout; out++)
			{
				itxe_data[in][out].mu.resize(nmu);
				itxe_data[in][out].eout = xss[offset];
				itxe_data[in][out].pdf = xss[offset+1];
				itxe_data[in][out].cdf = xss[offset+2];
				for (int i = 0; i < nmu; i++)
					itxe_data[in][out].mu[i] = xss[offset + 3 + i];
				offset += nmu + 3;
			}
		}
	}

	//ITCA block
	offset = jxs[5] - 1;
	int nmu = ncl + 1;
	if (jxs[3] != 0 && ncl != -1)
	{
		itca_data.resize(itce_data.nel);
		for (int n = 0; n < itce_data.nel; n++)
		{
			itca_data[n].mu.resize(nmu);
			for (int i = 0; i < nmu; i++)
				itca_data[n].mu[i] = xss[offset + i];
			offset += nmu;
		}
	}
}
REAL FMACEThermalCrossSectionProcessor::getIncoherentInelasticXS(REAL ein)
{
	ein *= 1.0e-6;
	int ind = getInterval(itie_data.ein, ein);
	int intt = 2;
	REAL val = endfInterpolator2Point(intt, itie_data.ein[ind], itie_data.ein[ind + 1],
		itie_data.sigin[ind], itie_data.sigin[ind + 1], ein, eExtraporationZero);

	return val;
}
REAL FMACEThermalCrossSectionProcessor::getElasticXS(REAL ein)
{
	REAL val = 0.0;

	if (isIncoherentElasticScattering())
		val = getIncoherentElasticXS(ein);

	if (isCoherentElasticScattering())
		val = getCoherentElasticXS(ein);

	return val;
}
REAL FMACEThermalCrossSectionProcessor::getIncoherentElasticXS(REAL ein)
{
	if (isIncoherentElasticScattering() == false) return 0.0;

	ein *= 1.0e-6;
	int ind = getInterval(itce_data.eel, ein);

	int intt = 2;
	REAL val = endfInterpolator2Point(intt, itce_data.eel[ind], itce_data.eel[ind + 1],
		itce_data.p[ind], itce_data.p[ind + 1], ein, eExtraporationZero);

	return val;
}
REAL FMACEThermalCrossSectionProcessor::getCoherentElasticXS(REAL ein)
{
	if (isCoherentElasticScattering() == false) return 0.0;

	ein *= 1.0e-6;
	int ind = getInterval(itce_data.eel, ein);

	REAL val;
	if (ein < itce_data.eel[0])
		val = 0.0;
	else if (ein >= itce_data.eel.back())
		val = itce_data.p.back() / ein;
	else
		val = itce_data.p[ind] / ein;

	return val;
}
void FMACEThermalCrossSectionProcessor::prepPlCoefIncoherentInelastic(int max_pl)
{
	itxe_proc_data.resize(itie_data.nin);
	for (int i = 0; i < itie_data.nin; i++)
	{
		int nout = itxe_data[i].size();
		itxe_proc_data[i].resize(nout);

		//initial setting of energy boundary for each interval
		vector<REAL> eout_l(nout), eout_u(nout), wgt_l(nout), wgt_u(nout);
		for (int j = 0; j < nout; j++)
		{
			if (j == 0)
			{
				eout_l[j] = itxe_data[i][j].eout * 1e6;
				eout_u[j] = (itxe_data[i][j].eout + itxe_data[i][j + 1].eout) / 2.0 * 1e6;
			}
			else if (j == nout - 1)
			{
				eout_l[j] = (itxe_data[i][j - 1].eout + itxe_data[i][j].eout) / 2.0 * 1e6;
				eout_u[j] = itxe_data[i][j].eout * 1e6;
			}
			else
			{
				eout_l[j] = (itxe_data[i][j - 1].eout + itxe_data[i][j].eout) / 2.0 * 1e6;
				eout_u[j] = (itxe_data[i][j].eout + itxe_data[i][j + 1].eout) / 2.0 * 1e6;
			}
		}

		for (int j = 0; j < nout; j++)
		{
			if (j > nout-4)
			{
				wgt_l[j] = itxe_data[i][nout-4].pdf;
				wgt_u[j] = itxe_data[i][nout-4].pdf;
			}
			else
			{
				wgt_l[j] = itxe_data[i][j].pdf;
				wgt_u[j] = itxe_data[i][j].pdf;
			}
		}

		for (int j = 0; j < nout; j++)
		{
			if (j == 0)
			{
				itxe_proc_data[i][j].eout_l = itxe_data[i][j].eout * 1e6;
				itxe_proc_data[i][j].eout_u = (itxe_data[i][j].eout*wgt_l[j + 1] + itxe_data[i][j + 1].eout*wgt_u[j]) /
					(wgt_u[j] + wgt_l[j + 1]) * 1e6;
			}
			else if (j == nout - 1)
			{
				itxe_proc_data[i][j].eout_l = (itxe_data[i][j - 1].eout*wgt_l[j] + itxe_data[i][j].eout*wgt_u[j - 1]) /
					(wgt_u[j - 1] + wgt_l[j])* 1.e6;
				itxe_proc_data[i][j].eout_u = itxe_data[i][j].eout * 1e6;
			}
			else
			{
				itxe_proc_data[i][j].eout_l = (itxe_data[i][j - 1].eout*wgt_l[j] + itxe_data[i][j].eout*wgt_u[j - 1]) /
					(wgt_u[j - 1] + wgt_l[j]) * 1e6;
				itxe_proc_data[i][j].eout_u = (itxe_data[i][j].eout*wgt_l[j + 1] + itxe_data[i][j + 1].eout*wgt_u[j]) /
					(wgt_u[j] + wgt_l[j + 1]) * 1e6;
			}
		}

		for (int j = 0; j < nout; j++)
		{
			//setting of pdf
			if (ifeng < 2)
			{
				itxe_proc_data[i][j].pdf = itxe_data[i][j].pdf;
				itxe_proc_data[i][j].cdf = itxe_data[i][j].cdf;
				itxe_proc_data[i][j].eout = itxe_data[i][j].eout * 1.0e+6;
			}
			else
			{
				itxe_proc_data[i][j].pdf = itxe_data[i][j].pdf/1.0e6;
				itxe_proc_data[i][j].cdf = itxe_data[i][j].cdf;
				itxe_proc_data[i][j].eout = itxe_data[i][j].eout*1.0e+6;
			}

			//pl coefficients
			itxe_proc_data[i][j].coef.resize(max_pl + 1);
			for (int il = 0; il <= max_pl; il++)
				itxe_proc_data[i][j].coef[il] = 0.0;

			int nmu = itxe_data[i][j].mu.size();
			REAL wgt = 1.0 / (REAL)nmu;
			for (int n = 0; n < nmu; n++)
			{
				REAL p[MAX_PL + 1];
				for (int il = 0; il <= max_pl; il++)
					p[il] = 0.0;
				REAL mu = itxe_data[i][j].mu[n];
				Pl(max_pl, mu, p);
				for (int il = 0; il <= max_pl; il++)
					itxe_proc_data[i][j].coef[il] += p[il] * wgt;
			}
			for (int il = 0; il <= max_pl; il++)
				itxe_proc_data[i][j].coef[il] /= itxe_proc_data[i][j].coef[0];
		}
	}
}
void FMACEThermalCrossSectionProcessor::getPlCoefIncoherentInelasticIFENG1(int nin, REAL _eout_upper, REAL _eout_lower, vector<REAL>& coef)
{
	int max_pl = coef.size() - 1;
	for (int il = 0; il <= max_pl; il++)
		coef[il] = 0.0;

	int nout = itxe_proc_data[nin].size();

#if 1
	//use continuous outgoing energy assuming exp(-E/kt) or erf(E/kt) for pdf
	REAL kt    = BOLTZMANN_CONSTANT*temp_kelvin;
	//REAL kteff = BOLTZMANN_CONSTANT*eff_temperature;
	for (int i = 0; i < nout; i++)
	{
		if (itxe_proc_data[nin][i].eout_l > _eout_upper || itxe_proc_data[nin][i].eout_u < _eout_lower) continue;
		REAL eu = _eout_upper;
		REAL el = _eout_lower;
		if (itxe_proc_data[nin][i].eout_u < eu) eu = itxe_proc_data[nin][i].eout_u;
		if (itxe_proc_data[nin][i].eout_l > el) el = itxe_proc_data[nin][i].eout_l;
		REAL fact = 1.0;
		if (el > itie_data.ein[nin]*1.0e6)
		{
			//up scattering
			REAL val1 = integrateKernelForThermalUpscattering(itxe_proc_data[nin][i].eout_l, itxe_proc_data[nin][i].eout_u, kt);
			REAL val2 = integrateKernelForThermalUpscattering(el, eu, kt);
			if (val1 != 0.0) fact = val2 / val1;
		}
		else
		{
			//down scattering
			REAL val1 = integrateKernelForThermalDownscattering(itxe_proc_data[nin][i].eout_l, itxe_proc_data[nin][i].eout_u, kt);
			REAL val2 = integrateKernelForThermalDownscattering(el, eu, kt);
			if (val1 != 0.0) fact = val2 / val1;
		}
		REAL pdf = itxe_proc_data[nin][i].pdf * fact;
		for (int il = 0; il <= max_pl; il++)
			coef[il] += itxe_proc_data[nin][i].coef[il] * pdf;
	}
#endif
#if 0
	//use continuous outgoing energy assuming constant pdf in itxe_data output energy
	for (int i = 0; i < nout; i++)
	{
		if (itxe_proc_data[nin][i].eout_l > _eout_upper || itxe_proc_data[nin][i].eout_u < _eout_lower) continue;
		REAL eu = _eout_upper;
		REAL el = _eout_lower;
		if (itxe_proc_data[nin][i].eout_u < eu) eu = itxe_proc_data[nin][i].eout_u;
		if (itxe_proc_data[nin][i].eout_l > el) el = itxe_proc_data[nin][i].eout_l;
		REAL de = itxe_proc_data[nin][i].eout_u - itxe_proc_data[nin][i].eout_l;
		REAL pdf = itxe_proc_data[nin][i].pdf / de * (eu - el);
		for (int il = 0; il <= max_pl; il++)
			coef[il] += itxe_proc_data[nin][i].coef[il] * pdf;
}
#endif
#if 0
	//use discrete outgoing energy
	for (int i = 0; i < nout; i++)
	{
		if (itxe_data[nin][i].eout*1.0e6 > _eout_upper || itxe_data[nin][i].eout*1.0e6 < _eout_lower) continue;
		for (int il = 0; il <= max_pl; il++)
			coef[il] += itxe_data[nin][i].pdf;
	}
#endif
}
void FMACEThermalCrossSectionProcessor::getPlCoefIncoherentInelasticIFENG2(int nin, REAL _eout_upper, REAL _eout_lower, vector<REAL>& coef)
{
	int max_pl = coef.size() - 1;
	vector<REAL> coefl(max_pl + 1), coefu(max_pl + 1);
	REAL cdfl = 0.0;
	REAL cdfu = 1.0;
	for (int il = 0; il <= max_pl; il++)
	{
		coef[il] = 0.0;
		coefl[il] = 0.0;
		coefu[il] = 0.0;
	}

	int nout = itxe_proc_data[nin].size();

	for (int i = 0; i < nout-1; i++)
	{
		if (itxe_proc_data[nin][i].eout > _eout_upper || itxe_proc_data[nin][i+1].eout < _eout_lower) continue;
		bool elin = false;
		bool euin = false;
		if (itxe_proc_data[nin][i].eout <= _eout_lower && itxe_proc_data[nin][i+1].eout >= _eout_lower) elin = true;
		if (itxe_proc_data[nin][i].eout <= _eout_upper && itxe_proc_data[nin][i+1].eout >= _eout_upper) euin = true;

		if (elin)
		{
			cdfl = endfInterpolator2Point(2, itxe_proc_data[nin][i].eout, itxe_proc_data[nin][i+1].eout,
				itxe_proc_data[nin][i].cdf, itxe_proc_data[nin][i+1].cdf, _eout_lower, eExtraporationConst);
			REAL wgt = 0.0;
			if (_eout_lower < itxe_proc_data[nin][i].eout)
				wgt = 0.0;
			else if (_eout_lower > itxe_proc_data[nin][i+1].eout)
				wgt = 1.0;
			else
				wgt = (_eout_lower - itxe_proc_data[nin][i].eout)/(itxe_proc_data[nin][i + 1].eout - itxe_proc_data[nin][i].eout);

			for (int il = 0; il <= max_pl; il++)
				coefl[il] = wgt*itxe_proc_data[nin][i+1].coef[il] + (1.0-wgt)*itxe_proc_data[nin][i].coef[il];
		}
		if (euin)
		{
			cdfu = endfInterpolator2Point(2, itxe_proc_data[nin][i].eout, itxe_proc_data[nin][i + 1].eout,
				itxe_proc_data[nin][i].cdf, itxe_proc_data[nin][i + 1].cdf, _eout_upper, eExtraporationConst);
			REAL wgt = 0.0;
			if (_eout_upper < itxe_proc_data[nin][i].eout)
				wgt = 0.0;
			else if (_eout_upper > itxe_proc_data[nin][i + 1].eout)
				wgt = 1.0;
			else
				wgt = (_eout_upper - itxe_proc_data[nin][i].eout) / (itxe_proc_data[nin][i + 1].eout - itxe_proc_data[nin][i].eout);

			for (int il = 0; il <= max_pl; il++)
				coefu[il] = wgt*itxe_proc_data[nin][i + 1].coef[il] + (1.0 - wgt)*itxe_proc_data[nin][i].coef[il];
		}
	}
	
	for (int il = 0; il <= max_pl; il++)
			coef[il] += (coefu[il] + coefl[il]) / 2.0 * (cdfu - cdfl);
}
void FMACEThermalCrossSectionProcessor::getPlCoefIncoherentInelastic(REAL ein, REAL _eout_upper, REAL _eout_lower, vector<REAL>& coef)
{
	int max_pl = coef.size() - 1;

	ein *= 1.0e-6;

	vector<REAL> coef0(max_pl + 1);
	vector<REAL> coef1(max_pl + 1);
	for (int il = 0; il <= max_pl; il++)
	{
		coef0[il] = 0.0;
		coef1[il] = 0.0;
	}

	int nin = getInterval(itie_data.ein, ein);
	REAL ein1 = itie_data.ein[nin];
	REAL ein2 = itie_data.ein[nin+1];
	REAL eou_wk1 = ein1 / ein * _eout_upper;
	REAL eol_wk1 = ein1 / ein * _eout_lower;
	REAL eou_wk2 = ein2 / ein * _eout_upper;
	REAL eol_wk2 = ein2 / ein * _eout_lower;

	if (ifeng < 2)
	{
		getPlCoefIncoherentInelasticIFENG1(nin,     eou_wk1, eol_wk1, coef0);
		getPlCoefIncoherentInelasticIFENG1(nin + 1, eou_wk2, eol_wk2, coef1);
	}
	else
	{
		getPlCoefIncoherentInelasticIFENG2(nin,     eou_wk1, eol_wk1, coef0);
		getPlCoefIncoherentInelasticIFENG2(nin + 1, eou_wk2, eol_wk2, coef1);
	}

	//interpolation
	int intt = 2;
	for (int il = 0; il <= max_pl; il++)
	{
		coef[il] = endfInterpolator2Point(intt, ein1, ein2, coef0[il], coef1[il], ein);
	}
}
void FMACEThermalCrossSectionProcessor::getPlCoefElastic(REAL ein, vector<REAL>& coef)
{
	if (isCoherentElasticScattering())
		getPlCoefCoherentElastic(ein, coef);

	if (isIncoherentElasticScattering())
		getPlCoefIncoherentElastic(ein, coef);

}
void FMACEThermalCrossSectionProcessor::prepPlCoefIncoherentElastic(int max_pl)
{
	if (isIncoherentElasticScattering() == false)	return;

	int nin = itca_data.size();
	itca_proc_data.resize(nin);

	for (int i = 0; i < nin; i++)
	{
		itca_proc_data[i].resize(max_pl + 1);
		for (int il = 0; il <= max_pl; il++)
			itca_proc_data[i][il] = 0.0;

		for (int n = 0; n < ncl + 1; n++)
		{
			REAL p[MAX_PL + 1];
			for (int j = 0; j <= max_pl; j++)
				p[j] = 0.0;
			REAL mu = itca_data[i].mu[n];
			REAL wgt = 1.0 / ((REAL)ncl + 1);
			Pl(max_pl, mu, p);
			for (int il = 0; il <= max_pl; il++)
				itca_proc_data[i][il] += p[il] * wgt;
		}
	}
}
void FMACEThermalCrossSectionProcessor::getPlCoefIncoherentElastic(REAL ein, vector<REAL>& coef)
{
	int max_pl = coef.size()-1;
	for (int il = 0; il <= max_pl; il++)
		coef[il] = 0.0;

	if (isIncoherentElasticScattering() == false)	return;

	ein *= 1.0e-6;
	int ind = getInterval(itce_data.eel, ein);

	//interpolation
	int intt = 2;
	for (int il = 0; il <= max_pl; il++)
	{
		coef[il] = endfInterpolator2Point(intt, itce_data.eel[ind], itce_data.eel[ind + 1],
			itca_proc_data[ind][il], itca_proc_data[ind+1][il], ein);
	}

	//normalize
	REAL fact = coef[0];
	if (fact != 0.0)
	{
		for (int il = 0; il <= max_pl; il++)
			coef[il] /= fact;
	}
}
void FMACEThermalCrossSectionProcessor::prepPlCoefCoherentElastic(int max_pl)
{
	if (isCoherentElasticScattering() == false)	return;

	int nin = itce_data.eel.size();
	bi_value.resize(nin);
	vector<REAL>	bi_sum(nin);

	for (int i = 0; i < nin; i++)
	{
		REAL ein = itce_data.eel[i];
		ein *= (1.0 + 1.0e-10);
		REAL xs = getCoherentElasticXS(ein*1.0e6);
		bi_sum[i] = ein * xs;
	}
	for (int i = 0; i < nin; i++)
	{
		if (i == 0) 
			bi_value[i] = bi_sum[i];
		else
			bi_value[i] = bi_sum[i] - bi_sum[i - 1];
	}
}
void FMACEThermalCrossSectionProcessor::getPlCoefCoherentElastic(REAL ein, vector<REAL>& coef)
{
	int max_pl = coef.size() - 1;
	for (int il = 0; il <= max_pl; il++)
		coef[il] = 0.0;

	if (isCoherentElasticScattering() == false)	return;

	ein *= 1.0e-6;
	int ind = -1;
	for (int i = 0; i < static_cast<int>(itce_data.eel.size()); i++)
	{
		if (ein > itce_data.eel[i])
			ind++;
		else
			break;
	}

	for (int i = 0; i <= ind; i++)
	{
		REAL mu = 1.0 - 2.0 * itce_data.eel[i] / ein;
		if (mu < -1.0 || mu > 1.0) continue;

		REAL p[MAX_PL + 1];
		for (int j = 0; j <= max_pl; j++)
			p[j] = 0.0;
		Pl(max_pl, mu, p);
		for (int il = 0; il <= max_pl; il++)
			coef[il] += p[il] * bi_value[i] / ein;
	}

	//normalize
	REAL fact = coef[0];
	if (fact != 0.0)
	{
		for (int il = 0; il <= max_pl; il++)
			coef[il] /= fact;
	}
}
void FMACEThermalCrossSectionProcessor::dumpIncoherentInelasticData()
{
	ofstream of;
	of.open("FMThermalIncoherentInelasticScatteringData.txt");
	of << scientific << setprecision(5);
	for (int i = 0; i < itie_data.nin; i++)
	{
		of << setw(6) << i;
		of << setw(15) << itie_data.ein[i]*1.0e6;
		of << setw(15) << itie_data.sigin[i];

		for (int out = 0; out < static_cast<int>(itxe_data[i].size()); out++)
			of << setw(15) << itxe_data[i][out].eout*1.0e6;
		of << endl;

		of << setw(36) << " ";
		for (int out = 0; out < static_cast<int>(itxe_data[i].size()); out++)
		{
			if (ifeng < 2)
				of << setw(15) << itxe_proc_data[i][out].pdf / ((itxe_proc_data[i][out].eout_u - itxe_proc_data[i][out].eout_l));
			else
				of << setw(15) << itxe_proc_data[i][out].pdf;
		}
		of << endl;
	}

	of.close();
}
