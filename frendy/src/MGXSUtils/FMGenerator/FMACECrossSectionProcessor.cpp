#pragma once
#include"MGXSUtils/FMGenerator/FMGenerator.h"
#include"MGXSUtils/FMGenerator/FMACECrossSectionProcessor.h"
#include <fstream>
#include <sstream>

using namespace FMGen;

void FMACECrossSectionProcessor::readHeaderData(string fname)
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
	skipACE20XHeader(fin);
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
void FMACECrossSectionProcessor::processHeaderData( )
{
	//title part
	vector<string> buf_vec;
	splitToToken(title[0], buf_vec);
	zaid = buf_vec[0];
	aw = my_stod(buf_vec[1]);
	temp_kelvin = my_stod(buf_vec[2])*1.0e+6 / BOLTZMANN_CONSTANT;

	//NXS array
	za = nxs[1];
	nes = nxs[2];
	ntr = nxs[3];
	nr = nxs[4];

	print2ndHeader(" Contents of ACE file ");
	cout << scientific << setprecision(7);
	cout << " File name                                                     : " << file_name << endl;
	cout << " ZA                                                            : " << za << endl;
	cout << " ZAID                                                          : " << zaid << endl;
	cout << " AW                                                            : " << aw << endl;
	cout << " Temperature[K]                                                : " << temp_kelvin << endl;
	cout << " Processed date                                                : " << buf_vec[3] << endl;
	cout << " Energy grid points                                            : " << nes << endl;
	cout << endl;
	cout << scientific << setprecision(5);

	//allocate array
	ene_grid.resize(nes);
}
void FMACECrossSectionProcessor::readXSData()
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
	skipACE20XHeader(fin);
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
void FMACECrossSectionProcessor::processXSData()
{
	//set energy grid
	ene_grid.resize(nes);
	for (int ie = 0; ie < nes; ie++)
		ene_grid[ie] = getACEEnergyGrid(ie) * 1.0e6;

	//mt values
	int offset = jxs[2] - 1;
	mt_values.resize(ntr);
	for (int i = 0; i < ntr; i++)
		mt_values[i] = rtoi(xss[offset + i]);

	//lsig values
	offset = jxs[5] - 1;
	lsig.resize(ntr);
	for (int i = 0; i < ntr; i++)
		lsig[i] = rtoi(xss[offset + i]);

	//nu-values (prompt/total)
	nu_total.resize(nes);
	vector<REAL> nu_prompt(nes);
	for (int i = 0; i < nes; i++)
	{
		nu_total[i] = 0.0;
		nu_prompt[i] = 0.0;
	}
	bool prompt_and_total = false;
	if (isNuTotal())
	{
		REAL val = xss[jxs[1] - 1];
		if (val < 0.0)
		{
			//prompt
			offset = jxs[1];
			setNuData(offset, nu_prompt);

			//total
			offset = jxs[1] + abs(rtoi(val));
			setNuData(offset, nu_total);

			prompt_and_total = true;
		}
		else
		{
			//total only
			offset = jxs[1] - 1;
			setNuData(offset, nu_total);
		}
	}

	//delayed nu values
	nu_delayed.resize(nes);
	for (int i = 0; i < nes; i++)
		nu_delayed[i] = 0.0;
	if (isNuDelayed())
	{
		offset = jxs[23] - 1;
		setNuData(offset, nu_delayed);
	}
	else
	{
		if (prompt_and_total)
		{
			for (int i = 0; i < nes; i++)
				nu_delayed[i] = nu_total[i] - nu_prompt[i];
		}
	}

	//set land arrays
	land.resize(nr + 1);
	offset = jxs[7] - 1;
	for (int i = 0; i < nr + 1; i++)
		land[i] = rtoi(xss[offset + i]);

	//set mt_value list having secondary neutron
	mt_values_angular.push_back(eMTElasticScattering);
	for (int i = 0; i < ntr; i++)
	{
		int mt = mt_values[i];
		if (getTYValue(mt) != 0) mt_values_angular.push_back(mt);
	}
	if (static_cast<int>(mt_values_angular.size()) != nr + 1)
	{
		cout << " -----------------------------------------------------" << endl;
		cout << " Inconsistency detected in ace file " << endl;
		cout << " -----------------------------------------------------" << endl;
		cout << " (1) Number of reactions having secondary neutron in ace file (NR)      : " << nr << endl;
		cout << " (2) Number of reactions having secondary neutron in ace file (TY block): " << mt_values_angular.size() - 1 << endl;
		cout << " The above (1) and (2) should be identical. Possible cause is inconsistency in nuclear data file. "  << endl;
		cout << endl;
		cout << " Number of emitted neutrons in TY block of ace file" << endl;
		cout << endl;
		cout << "           mt    number of emitted neutrons (TY block)" << endl;
		cout << " -----------------------------------------------------" << endl;
		for (int i = 0; i < ntr; i++)
		{
			int mt = mt_values[i];
			cout << setw(3) << i;
			cout << setw(10) << mt;
			cout << setw(10) << abs(getTYValue(mt)) << endl;
		}
		cout << endl;

		//exit(0);
	}
}
void FMACECrossSectionProcessor::setNuData(int offset, vector<REAL>& _nu)
{
	int lnu = rtoi(xss[offset]);
	if (lnu == 1)
	{
		offset += 1;
		int nc = rtoi(xss[offset]);
		vector<REAL> coef(nc);
		offset += 1;
		for (int i = 0; i < nc; i++)
			coef[i] = xss[offset + i];
		for (int i = 0; i < nes; i++)
		{
			_nu[i] = 0.0;
			for (int j = 0; j < nc; j++)
			{
				REAL ene = ene_grid[i] * 1.0e-6;
				_nu[i] += coef[j] * pow(ene, j);
			}
		}
	}
	else
	{
		offset += 1;
		int _nr = rtoi(xss[offset]);
		vector<int> nbtt(_nr);
		vector<int> intt(_nr);
		offset += 1;
		for (int i = 0; i < _nr; i++)
			nbtt[i] = rtoi(xss[offset + i]);
		offset += _nr;
		for (int i = 0; i < _nr; i++)
			intt[i] = rtoi(xss[offset + i]);
		offset += _nr;
		int ne = rtoi(xss[offset]);
		vector<REAL> nuegrid(ne);
		vector<REAL> nuval(ne);
		offset += 1;
		for (int i = 0; i < ne; i++)
			nuegrid[i] = xss[offset + i];
		offset += ne;
		for (int i = 0; i < ne; i++)
			nuval[i] = xss[offset + i];
		for (int i = 0; i < nes; i++)
		{
			REAL ene = ene_grid[i] * 1.0e-6;
			_nu[i] = endfInterpolator(_nr, nbtt, intt, nuegrid, nuval, ene);
		}
	}

}
REAL FMACECrossSectionProcessor::getXS(int type, REAL ene, REAL bgxs)
{
	if (isMT(type) == false) return 0.0;

	if (ene > ene_grid[0] || ene < ene_grid[nes-1])
	{
		return 0.0;
	}

	//lookup
	for (;;)
	{
		REAL val = 0.0;
		if (ene <= ene_grid[current] && ene >= ene_grid[current + 1])
		{
			REAL y0 = getXS(type, current, bgxs);
			REAL y1 = getXS(type, current + 1, bgxs);
			REAL x0 = ene_grid[current];
			REAL x1 = ene_grid[current + 1];
			val = (y1 - y0) / (x1 - x0)*(ene - x0) + y0;
			return val;
		}
		else if (ene > ene_grid[current])
		{
			current--;
			if (current < 0)
			{
				cout << " out of range " << endl;
				exit(0);
			}
		}
		else
		{
			current++;
			if (current >= nes-1)
			{
				cout << " out of range " << endl;
				exit(0);
			}
		}
	}
}
REAL FMACECrossSectionProcessor::getFissionXS(REAL ene, REAL bgxs)
{
	REAL val = 0.0;

	if (isMT(eMTFission))
	{
		val = getXS(eMTFission, ene, bgxs);
	}
	else if (isMT(eMTFirstChanceFission))
	{
		val = getXS(eMTFirstChanceFission, ene, bgxs);
		val += getXS(eMTSecondChanceFission, ene, bgxs);
		val += getXS(eMTThirdChanceFission, ene, bgxs);
		val += getXS(eMTFourthChanceFission, ene, bgxs);
	}

	return val;
}
REAL FMACECrossSectionProcessor::getNu(int type, REAL ene)
{
	if (ene > ene_grid[0] || ene < ene_grid[nes - 1])
	{
		return 0.0;
	}

	//lookup
	for (;;)
	{
		REAL val = 0.0;
		if (ene <= ene_grid[current] && ene >= ene_grid[current + 1])
		{
			REAL y0, y1;
			if (type == eNuTotal)
			{
				y0 = getNuTotal(current);
				y1 = getNuTotal(current + 1);
			}
			else if (type == eNuDelayed)
			{
				y0 = getNuDelayed(current);
				y1 = getNuDelayed(current + 1);
			}
			else
			{
				y0 = getNuTotal(current) - getNuDelayed(current);
				y1 = getNuTotal(current + 1) - getNuDelayed(current + 1);
			}
			REAL x0 = ene_grid[current];
			REAL x1 = ene_grid[current + 1];
			val = (y1 - y0) / (x1 - x0) * (ene - x0) + y0;
			return val;
		}
		else if (ene > ene_grid[current])
		{
			current--;
			if (current < 0)
			{
				cout << " out of range " << endl;
				exit(0);
			}
		}
		else
		{
			current++;
			if (current >= nes - 1)
			{
				cout << " out of range " << endl;
				exit(0);
			}
		}
	}
}
int FMACECrossSectionProcessor::getLocb(int mt)
{
	bool find = false;
	for (int ir = 0; ir < static_cast<int>(mt_values_angular.size()); ir++)
	{
		if (mt_values_angular[ir] != mt) continue;
		find = true;
		//int offset = jxs[8] - 1;
		int locb = land[ir];
		return locb;
	}

	if (find == false)
	{
		cout << " mt not found in getLocb " << mt << endl;
		exit(0);
	}
	return 99999;
}
int FMACECrossSectionProcessor::getMaxTablePointsInAngularPDF(int mt)
{
	//read AND block
	int ir = getIRfromMTValuesAngular(mt);
	int offset = jxs[8] - 1;
	int locb = land[ir];

	int ne = rtoi(xss[offset + locb - 1]);

	int max_num = 0;

	if (locb > 0)
	{
		for (int j = 0; j < ne; j++)
		{
			int num = getMaxTablePointsInAngularPDF(mt, j);
			if (num > max_num) max_num = num;
		}
	}
	else
		max_num = 0;

	return max_num;
}
int FMACECrossSectionProcessor::getMaxTablePointsInAngularPDF(int mt, REAL ein)
{
	vector<REAL>& egrid = angular_dist_egrid[mt];

	int ne = egrid.size();
	int e0;
	int max_num = 0;

	if (ne > 1)
	{
		e0 = getInterval(egrid, ein, true);
		int num0 = getMaxTablePointsInAngularPDF(mt, e0);
		int num1 = getMaxTablePointsInAngularPDF(mt, e0+1);
		if (max_num < num0) max_num = num0;
		if (max_num < num1) max_num = num1;
	}

	return max_num;
}
int FMACECrossSectionProcessor::getMaxTablePointsInAngularPDF(int mt, int e0)
{
	//read AND block
	int ir = getIRfromMTValuesAngular(mt);
	int offset = jxs[8] - 1;
	int locb = land[ir];

	int ne = rtoi(xss[offset + locb - 1]);
	int lc = rtoi(xss[offset + locb + ne + e0]);

	int max_num = 0;

	if (locb > 0)
	{
		for (int j = 0; j < ne; j++)
		{
			if (lc > 0)
			{
				if (max_num < 33) max_num = 33;
			}
			else if (lc < 0)
			{
				offset = jxs[8] - 1 + abs(lc) - 1;
				int np = rtoi(xss[offset + 1]);
				if (max_num < np) max_num = np;
			}
		}
	}
	else
		max_num = 0;

	return max_num;
}
void FMACECrossSectionProcessor::prepAngularPDF(int mt)
{
	//if data already exist or not
	if (angular_dist_mu.find(mt) != angular_dist_mu.end()) return;

	//get maximum number of angular table points
	int max_num = getMaxTablePointsInAngularPDF(mt);
	if (max_num < MAX_MU_DIV) max_num = MAX_MU_DIV;

	//set mu-boundary
	vector<REAL> mu_boundary;
	mu_boundary.resize(max_num + 1);
	mu_boundary[0] = -1.0;

	for (int i = 0; i < max_num; i++)
	{
		REAL delta_mu = (1.0 - mu_boundary[0]) / (REAL)max_num;
		mu_boundary[i + 1] = mu_boundary[i] + delta_mu;
	}

	//assign default pdf (=0.5, isotropic scattering)
	vector<REAL> pdf;
	pdf.resize(mu_boundary.size());
	for (int i = 0; i < static_cast<int>(mu_boundary.size()); i++)
	pdf[i] = 1.0 / (1.0 - mu_boundary[0]);

	//reset number of angle division
	int ndiv = pdf.size();

	vector<REAL> mu;
	mu.resize(ndiv);
	for (int i = 0; i < ndiv; i++)
		mu[i] = mu_boundary[i];
	
	//read AND block
	int ir = getIRfromMTValuesAngular(mt);
	int offset = jxs[8]-1;
	int locb = land[ir];

	if (locb > 0)
	{
		//angular distribution is given
		int ne = rtoi(xss[offset + locb - 1]);
		vector<REAL> egrid(ne);
		for (int j = 0; j < ne; j++)
			egrid[j] = xss[offset + locb + j]*1.0e6;
		angular_dist_egrid.insert(make_pair(mt, egrid));

		vector<vector<REAL> > pdf_vec(ne);
		for (int j = 0; j < ne; j++)
		{
			getAngularPDF(ir, j, mu, pdf);
			pdf_vec[j] = pdf;
		}
		angular_dist_pdf.insert(make_pair(mt, pdf_vec));
	}
	else
	{
		vector<vector<REAL> > pdf_vec(1);
		pdf_vec[0] = pdf;
		angular_dist_pdf.insert(make_pair(mt, pdf_vec));
	}

	angular_dist_mu.insert(make_pair(mt, mu));
	angular_dist_locb.insert(make_pair(mt, locb));
}
void FMACECrossSectionProcessor::getAngularDistribution(int mt, REAL ein, vector<REAL>& mu_boundary, vector<REAL>& pdf, int& coord)
{
	//set mu-boundary
	int ndiv = angular_dist_mu[mt].size();
	mu_boundary.resize(ndiv);
	for (int i = 0; i < ndiv; i++)
		mu_boundary[i] = angular_dist_mu[mt][i];

	//assign default pdf (=0.5)
	pdf.resize(mu_boundary.size());

	int locb = angular_dist_locb[mt];

	if (locb > 0)
	{
		//angular distribution is given
		vector<REAL>& egrid = angular_dist_egrid[mt];

		int ne = egrid.size();
		int e0, e1;
		REAL w0, w1;

		if (ne > 1)
		{
			if (ein < egrid[0])
			{
				e0 = getInterval(egrid, ein, true);
				e1 = e0 + 1;
				w0 = 1.0;
				w1 = 0.0;
			}
			else if (ein < egrid.back())
			{
				e0 = getInterval(egrid, ein, true);
				e1 = e0 + 1;
				w1 = (ein - egrid[e0]) / (egrid[e1] - egrid[e0]);
				w0 = 1.0 - w1;
			}
			else
			{
				e0 = getInterval(egrid, ein, true);
				e1 = e0 + 1;
				w0 = 0.0;
				w1 = 1.0;
			}
		}
		else
		{
			e0 = 0;
			e1 = 0;
			w0 = 1.0;
			w1 = 0.0;
		}
		getAngularPDFwithInterpolation(mt, e0, e1, w0, w1, pdf);
	}
	else
	{
		pdf = angular_dist_pdf[mt][0];
	}

	bool conv_to_lab = false;
	if (mt == eMTElasticScattering)
	{
		conv_to_lab = true;
	}
	else
	{
		if (getTYValue(mt) < 0)
			conv_to_lab = true;
	}

	coord = eLaboratorySystem;
	if (conv_to_lab) coord = eCenterOfMassSystem;

	//nomarize pdf
	DOUBLE sum = 0.0;
	ndiv = pdf.size();

	for (int i = 0; i < ndiv - 1; i++)
		sum += (pdf[i + 1] + pdf[i]) / 2.0 * (mu_boundary[i + 1] - mu_boundary[i]);
	for (int i = 0; i < ndiv; i++)
		pdf[i] = pdf[i] / sum;

}
void FMACECrossSectionProcessor::getAngularPDFwithInterpolation(int mt, int e0, int e1, REAL w0, REAL w1, vector<REAL>& pdf)
{

	vector<REAL>& pdf0 = angular_dist_pdf[mt][e0];
	vector<REAL>& pdf1 = angular_dist_pdf[mt][e1];

	for (int ii = 0; ii < static_cast<int>(pdf.size()); ii++)
		pdf[ii] = w0*pdf0[ii] + w1*pdf1[ii];
}
void FMACECrossSectionProcessor::getAngularPDF(int ir, int e0, vector<REAL>& cs, vector<REAL>& pdf)
{
	int offset = jxs[8] - 1;
	int locb = land[ir];
	int ne = rtoi(xss[offset + locb - 1]);
	vector<int> lc(ne);
	for (int j = 0; j < ne; j++)
		lc[j] = rtoi(xss[offset + locb + ne + j]);

	if (lc[e0] > 0)
	{
		vector<REAL> cs_wk(33);
		vector<REAL> pdf_wk(33);
		offset = jxs[8] - 1 + lc[e0];
		for (int ii = 0; ii < 33; ii++)
			cs_wk[ii] = xss[offset + ii - 1];
		for (int ii = 0; ii < 33; ii++)
			pdf_wk[ii] = 2.0/32.0;

		for (int i = 0; i < static_cast<int>(cs.size()); i++)
		{
			if (cs[i] <= cs_wk[0])
				pdf[i] = pdf_wk[0];
			else if (cs[i] >= cs_wk.back())
				pdf[i] = pdf_wk.back();
			else
			{
				for (int ii = 0; ii < static_cast<int>(cs_wk.size()) - 1; ii++)
				{
					if (cs[i] >= cs_wk[ii] && cs[i] <= cs_wk[ii + 1])
					{
						REAL w0, w1;
						w1 = (cs[i] - cs_wk[ii]) / (cs_wk[ii + 1] - cs_wk[ii]);
						w0 = 1.0 - w1;
						pdf[i] = w0*pdf_wk[ii] + w1*pdf_wk[ii + 1];
						break;
					}
				}
			}
		}
#if 1
		cout << " check FMACECrossSectionProcessor::getAngularPDF for lc[e0] > 0 " << endl;
		exit(0);
#endif
	}
	else if (lc[e0] < 0)
	{
		offset = jxs[8] - 1 + abs(lc[e0]) - 1;
		int jj = rtoi(xss[offset]);
		int np = rtoi(xss[offset + 1]);
		vector<REAL> cs_wk(np);
		vector<REAL> pdf_wk(np);
		for (int i = 0; i < np; i++)
		{
			cs_wk[i] = xss[offset + 2 + i];
			pdf_wk[i] = xss[offset + 2 + np + i];
		}
		for (int i = 0; i < static_cast<int>(cs.size()); i++)
		{
			if (cs[i] <= cs_wk[0])
				pdf[i] = pdf_wk[0];
			else if (cs[i] >= cs_wk.back())
				pdf[i] = pdf_wk.back();
			else
			{
				for (int ii = 0; ii < static_cast<int>(cs_wk.size())-1; ii++)
				{
					if (cs[i] >= cs_wk[ii] && cs[i] <= cs_wk[ii+1])
					{
						REAL w0, w1;
						if (jj == 1)
						{
							w0 = 1.0;
							w1 = 0.0;
						}
						else if (jj == 2)
						{
							w1 = (cs[i] - cs_wk[ii]) / (cs_wk[ii + 1] - cs_wk[ii]);
							w0 = 1.0 - w1;
						}
						else
						{
							cout << " Error in FMACECrossSectionProcessor::getAngularPDF ";
							exit(0);
						}
						pdf[i] = w0*pdf_wk[ii] + w1*pdf_wk[ii+1];
						break;
					}
				}
			}
		}
	}
	else
	{
		pdf.resize(cs.size());
		for (int ii = 0; ii < static_cast<int>(cs.size()); ii++)
			pdf[ii] = 1.0 / 2.0 / (REAL)cs.size();
	}

	//nomarize pdf
	DOUBLE sum = 0.0;
	int ndiv = pdf.size();

	for (int i = 0; i < ndiv - 1; i++)
		sum += (pdf[i + 1] + pdf[i]) / 2.0 * (cs[i + 1] - cs[i]);
	for (int i = 0; i < ndiv; i++)
		pdf[i] = pdf[i] / sum;
}
void FMACECrossSectionProcessor::getDLW(int ir, int mt,bool delayed)
{
	//read DLW block
	vector<DLW> dlw_vec;
	DLW dlw_wk;
	int ldlw, locc, jed, offset;
	if (delayed == false)
	{
		ldlw = jxs[9] - 1;
		locc = rtoi(xss[ldlw + ir - 1]);
		jed = jxs[10] - 1;
		offset = jed + locc - 1;
	}
	else
	{
		ldlw = jxs[25] - 1;
		locc = rtoi(xss[ldlw + ir - 1]);
		jed = jxs[26] - 1;
		offset = jed + locc - 1;
	}
	dlw_vec.clear();
	for (;;)
	{
		dlw_wk.clear();
		dlw_wk.lnw = rtoi(xss[offset]);
		dlw_wk.law = rtoi(xss[offset+1]);
		dlw_wk.idat = rtoi(xss[offset+2]);
		dlw_wk.nr = rtoi(xss[offset+3]);
		if (dlw_wk.nr != 0)
		{
			dlw_wk.nbtt.resize(dlw_wk.nr);
			dlw_wk.intt.resize(dlw_wk.nr);
		}
		offset += 4 + 2 * dlw_wk.nr;
		dlw_wk.ne = rtoi(xss[offset]);
		dlw_wk.etab.resize(dlw_wk.ne);
		dlw_wk.ptab.resize(dlw_wk.ne);
		offset += 1;
		for (int i = 0; i < dlw_wk.ne; i++)
		{
			dlw_wk.etab[i] = xss[offset + i];
			dlw_wk.ptab[i] = xss[offset + dlw_wk.ne + i];
		}
			
		//read ldat
		int offset_ldat = jed + dlw_wk.idat - 1;
		int ldat_len, ldat_nr, ldat_ne;
		int ldat_nrb, ldat_neb;
		vector<int> ldat_loc;
		switch (dlw_wk.law)
		{
		case 3:
		case 66:
			ldat_len = 2;
			break;
		case 4:
		case 44:
		case 61:
			ldat_nr = rtoi(xss[offset_ldat]);
			offset_ldat += 1 + 2 * ldat_nr;
			ldat_ne = rtoi(xss[offset_ldat]);
			offset_ldat += 1 + ldat_ne;
			ldat_loc.resize(ldat_ne);
			for (int i = 0; i < ldat_ne; i++)
				ldat_loc[i] = rtoi(xss[offset_ldat + i]);
			ldat_len = 2 + 2 * ldat_nr + 2 * ldat_ne;
			offset_ldat = jed + dlw_wk.idat - 1;
			break;
		case 7:
		case 9:
			ldat_nr = rtoi(xss[offset_ldat]);
			ldat_ne = rtoi(xss[offset_ldat + 1 + 2 * ldat_nr]);
			ldat_len = 2 + 2 * ldat_nr + 2 * ldat_ne + 1;
			break;
		case 11:
			ldat_nr = rtoi(xss[offset_ldat]);
			ldat_ne = rtoi(xss[offset_ldat + 1 + 2 * ldat_nr]);
			ldat_nrb = rtoi(xss[offset_ldat + 2 + 2*(ldat_nr+ldat_ne)]);
			ldat_neb = rtoi(xss[offset_ldat + 2 + 2 * (ldat_nr + ldat_ne) + 1 + 2* ldat_nrb]);
			ldat_len = 2 + 2 * ldat_nr + 2 * ldat_ne + 3 + 2 * ldat_nrb + 2 * ldat_neb;
			break;
		default:
			cout << " this law in DLW block has not been implemented " << dlw_wk.law << endl;
			exit(0);
			break;
		}
		dlw_wk.ldat.resize(ldat_len);
		for (int i = 0; i < ldat_len; i++)
			dlw_wk.ldat[i] = xss[offset_ldat + i];

		//energy dependent neutron yield
		if (abs(getTYValue(mt)) > 100)
		{
			int ky = jxs[10] - 1 + abs(getTYValue(mt)) - 101;
			dlw_wk.nr_ed = rtoi(xss[ky]);
			dlw_wk.nbtt_ed.resize(dlw_wk.nr_ed);
			dlw_wk.intt_ed.resize(dlw_wk.nr_ed);
			for (int i = 0; i < dlw_wk.nr_ed; i++)
			{
				dlw_wk.nbtt[i] = rtoi(xss[ky + 1 + i]);
				dlw_wk.intt[i] = rtoi(xss[ky + 1 + dlw_wk.nr_ed + i]);
			}
			dlw_wk.ne_ed = rtoi(xss[ky + 1 + 2 * dlw_wk.nr_ed]);
			dlw_wk.etab_ed.resize(dlw_wk.ne_ed);
			dlw_wk.ytab.resize(dlw_wk.ne_ed);
			for (int i = 0; i < dlw_wk.ne_ed; i++)
			{
				dlw_wk.etab_ed[i] = xss[ky + 2 + 2 * dlw_wk.nr_ed + i];
				dlw_wk.ytab[i] = xss[ky + 2 + 2 * dlw_wk.nr_ed + dlw_wk.ne_ed + i];
			}
		}

		dlw_vec.push_back(dlw_wk);

		if (dlw_wk.lnw == 0) break;

		offset = jed + dlw_wk.lnw-1;
	}

	if (delayed == false)
		dlw.insert(make_pair(mt, dlw_vec));
	else
		dlw_delayed.insert(make_pair(mt, dlw_vec));

}
void FMACECrossSectionProcessor::getDelayedPrecursorDist()
{
	DLW dlw_wk;
	int offset = jxs[24] - 1;
	int num_delayed_group = nxs[7];
	for (int ir = 0;ir < num_delayed_group; ir++)
	{
		dlw_wk.clear();
		dlw_wk.dec = xss[offset];
		dlw_wk.nr = rtoi(xss[offset + 1]);
		if (dlw_wk.nr != 0)
		{
			dlw_wk.nbtt.resize(dlw_wk.nr);
			dlw_wk.intt.resize(dlw_wk.nr);
			for (int i = 0; i < dlw_wk.nr; i++)
			{
				dlw_wk.nbtt[i] = rtoi(xss[offset + 2 + i]);
				dlw_wk.intt[i] = rtoi(xss[offset + 2 + dlw_wk.nr + i]);
			}
		}
		offset += 2 + 2 * dlw_wk.nr;
		dlw_wk.ne = rtoi(xss[offset]);
		dlw_wk.etab.resize(dlw_wk.ne);
		dlw_wk.ptab.resize(dlw_wk.ne);
		offset += 1;
		for (int i = 0; i < dlw_wk.ne; i++)
		{
			dlw_wk.etab[i] = xss[offset + i];
			dlw_wk.ptab[i] = xss[offset + dlw_wk.ne + i];
		}
		offset += 2 * dlw_wk.ne;
		delayed_precursor_distribution.insert(make_pair(ir+1, dlw_wk));
	}
}
void FMACECrossSectionProcessor::getIncidentEnergyGridInDLW(int mt, vector<REAL>& ene_boundary, vector<REAL>& add_boundary, bool delayed)
{
	add_boundary.clear();

	DLW* dlw_wk;
	if (delayed == false)
	{
		if (dlw.find(mt) == dlw.end()) return;
		dlw_wk = &dlw[mt][0];
	}
	else
	{
		if (dlw_delayed.find(mt) == dlw_delayed.end()) return;
		dlw_wk = &dlw_delayed[mt][0];
	}

	int law = dlw_wk->law;
	if (law == 1 || law == 4 || law == 5 || law == 7 ||
		law == 9 || law == 44 || law == 61)
	{
		int _nr = rtoi(dlw_wk->ldat[0]);
		int ne = rtoi(dlw_wk->ldat[1 + 2 * _nr]);

		//incident energy grid
		for (int i = 0; i < ne; i++)
			add_boundary.push_back(dlw_wk->ldat[2 * _nr + 2 + i] * 1.0e6);
	}

	switch (law)
	{
	case 7:
	case 9:
	{
		//energy grid for lower energy groups
		int _nr = rtoi(dlw_wk->ldat[0]);
		int ne = rtoi(dlw_wk->ldat[1 + 2 * _nr]);
		REAL u = dlw_wk->ldat[2 * _nr + 2 * ne + 2];
		for (int i = 0; i < static_cast<int>(ene_boundary.size()); i++)
		{
			REAL val = ene_boundary[i] + u*1.0e6;
			if (val < ene_boundary[0])
				add_boundary.push_back(val);
		}
		break;
	}
	default:
		break;
	}
}
void FMACECrossSectionProcessor::getEnergyAngleDistribution(int mt, REAL ein, FMEneAngDist& eadist, FMEneAngDist& ead_wk)
{
	if (isEmissionReaction(mt) == false)
		return;

	vector<REAL> mu, mu_boundary, pdf;
	int coord;

	//set angular distribution (file=4) or default isotropic value (may be file 6)
	getAngularDistribution(mt, ein, mu_boundary, pdf, coord);

#if 0
	getEnergyDistributionElasticDebug();
#endif

	if (mt == eMTElasticScattering)
		getEnergyDistributionElastic(mt, ein, mu_boundary, pdf, eadist, coord);
	else
		getEnergyDistributionwithDLW(mt, ein, mu_boundary, pdf, eadist, ead_wk, coord);

}

void FMACECrossSectionProcessor::getEnergyDistributionElastic(int mt, REAL ein, vector<REAL>& mu_boundary, vector<REAL>& pdf,
	FMEneAngDist& eadist, int coord, bool delayed)
{
	if (delayed == true) return;

	eadist.setZero();

	//elastic
	//minimum energy
	REAL e_min = getEoutAfterElasticScattering(ein, -1.0);
	REAL e_max = getEoutAfterElasticScattering(ein, +1.0);

	//singular energy point for hydrogen (minimum mu in lab system)
	REAL e_singular = 0.0;
	if (aw < 1.0) e_singular = getEoutAfterElasticScattering(ein, -aw);

	for (int ig = 0; ig < eadist.max_ng; ig++)
	{
		//set upper and lower energy range for e_out
		REAL e_upper = eadist.ene_boundary[ig];
		REAL e_lower = eadist.ene_boundary[ig + 1];

		if (e_max < e_lower) continue;
		if (e_min > e_upper) continue;
		if (e_min > e_lower && e_min < e_upper) e_lower = e_min;
		if (ig == (eadist.max_ng - 1) && e_min < eadist.ene_boundary.back()) e_lower = e_min;
		if (ig == (eadist.max_ng - 1) && e_min < 1.0e-20)                    e_lower = eadist.ene_boundary.back(); //prevent zero energy boundary to avoid nan
		if (e_max > e_lower && e_max < e_upper) e_upper = e_max;

		//set division for e_out
		int ndiv = MAX_EOUT_DIV_ELASTIC;
		int num_table_points = getMaxTablePointsInAngularPDF(mt, ein);
		if (ndiv < num_table_points) ndiv = num_table_points;

		vector<REAL> eout_boundary;
		if (e_singular > e_lower && e_singular < e_upper)
		{
			eout_boundary.resize(2 * ndiv + 1);
			for (int i = 0; i <= ndiv; i++)
			{
				REAL eowk = (log(e_singular) - log(e_lower)) / (REAL)ndiv*(REAL)i + log(e_lower);
				eout_boundary[i] = exp(eowk);
			}
			for (int i = 1; i <= ndiv; i++)
			{
				REAL eowk = (log(e_upper) - log(e_singular)) / (REAL)ndiv*(REAL)i + log(e_singular);
				eout_boundary[i + ndiv] = exp(eowk);
			}
		}
		else
		{
			eout_boundary.resize(ndiv + 1);
			for (int i = 0; i <= ndiv; i++)
			{
				REAL eowk = (log(e_upper) - log(e_lower)) / (REAL)ndiv*(REAL)i + log(e_lower);
				eout_boundary[i] = exp(eowk);
			}
		}
		ndiv = eout_boundary.size() - 1;

		vector<REAL> pdfwk, mulwk, delta_mul;
		pdfwk.resize(ndiv);
		mulwk.resize(ndiv);
		delta_mul.resize(ndiv);
		for (int i = 0; i < ndiv; i++)
		{
			REAL eoutave = sqrt(eout_boundary[i + 1]*eout_boundary[i]);

			//muc
			REAL wkmcl = getMucAfterElasticScattering(ein, eout_boundary[i]);
			REAL wkmcave = getMucAfterElasticScattering(ein, eoutave);
			REAL wkmcu = getMucAfterElasticScattering(ein, eout_boundary[i + 1]);
			//mul
			REAL wkmll = convertCMtoLabDirectionCosine(wkmcl);
			REAL wkmlave = convertCMtoLabDirectionCosine(wkmcave);
			REAL wkmlu = convertCMtoLabDirectionCosine(wkmcu);
			//pdf interporation
			REAL wkp;
			if (coord == eCenterOfMassSystem)
			{
				wkp = interporatePdf(mu_boundary, pdf, wkmcave);
				wkp = convertCMtoLabPDF(wkp, wkmcave);
			}
			else
			{
				wkp = interporatePdf(mu_boundary, pdf, wkmlave);
			}
			mulwk[i] = wkmlave;
			pdfwk[i] = wkp;
			delta_mul[i] = wkmlu - wkmll;
		}
		vector<REAL> coef;

		//Integrated pdf
		REAL pdfsum = 0.0;
		for (int i = 0; i < ndiv; i++)
			pdfsum += pdfwk[i] * delta_mul[i];
		eadist.pdf[ig] = pdfsum;

		//Legendre coefficients
		calcPlCoefficient(mulwk, delta_mul, pdfwk, coef, eadist.max_pl);
		for (int il = 0; il <= eadist.max_pl; il++)
			eadist.pl_coef[ig][il] = coef[il];
	}

	//normalize
	eadist.normalize();
}
void FMACECrossSectionProcessor::getEnergyDistributionElasticDebug()
{
	REAL ein = 1.0e+2;
	this->aw = 1.000001;

	//elastic
	//minimum energy
	REAL e_min = getEoutAfterElasticScattering(ein, -1.0);
	REAL e_max = getEoutAfterElasticScattering(ein, +1.0);

	//singular energy point for hydrogen (minimum mu in lab system)
	REAL e_singular = 0.0;
	if (aw < 1.0) e_singular = getEoutAfterElasticScattering(ein, -aw);

	//set upper and lower energy range for e_out
	REAL e_upper = e_max;
	REAL e_lower = e_min;

	//set division for e_out
	int ndiv = 100;

	vector<REAL> eout_wk, eout_wk_log;
	if (e_singular > e_lower && e_singular < e_upper)
	{
		eout_wk_log.resize(2 * ndiv + 1);
		eout_wk.resize(2 * ndiv + 1);
		for (int i = 0; i <= ndiv; i++)
		{
			REAL eowk = (log(e_singular) - log(e_lower)) / (REAL)ndiv * (REAL)i + log(e_lower);
			eout_wk_log[i] = exp(eowk);
			eowk = (e_singular - e_lower) / (REAL)ndiv * (REAL)i + e_lower;
			eout_wk[i] = eowk;
		}
		for (int i = 1; i <= ndiv; i++)
		{
			REAL eowk = (log(e_upper) - log(e_singular)) / (REAL)ndiv * (REAL)i + log(e_singular);
			eout_wk_log[i + ndiv] = exp(eowk);
			eowk = (e_upper - e_singular) / (REAL)ndiv * (REAL)i + e_singular;
			eout_wk[i + ndiv] = eowk;
		}
	}
	else
	{
		eout_wk.resize(ndiv + 1);
		eout_wk_log.resize(ndiv + 1);
		for (int i = 0; i <= ndiv; i++)
		{
			REAL eowk = (log(e_upper) - log(e_lower)) / (REAL)ndiv * (REAL)i + log(e_lower);
			eout_wk_log[i] = exp(eowk);
			eowk = (e_upper - e_lower) / (REAL)ndiv * (REAL)i + e_lower;
			eout_wk[i] = eowk;
		}
	}

	for (int i = 0; i < (int)eout_wk_log.size(); i++)
	{
		REAL wkmcave = getMucAfterElasticScattering(ein, eout_wk_log[i]);
		REAL wkmlave = convertCMtoLabDirectionCosine(wkmcave);
		cout << scientific << setprecision(5);
		cout << setw(15) << eout_wk_log[i];
		cout << setw(15) << wkmlave << endl;
	}
	cout << endl;

	for (int i = 0; i < (int)eout_wk.size(); i++)
	{
		REAL wkmcave = getMucAfterElasticScattering(ein, eout_wk[i]);
		REAL wkmlave = convertCMtoLabDirectionCosine(wkmcave);
		cout << scientific << setprecision(5);
		cout << setw(15) << eout_wk[i];
		cout << setw(15) << wkmlave << endl;
	}
}

void FMACECrossSectionProcessor::getEnergyDistributionwithDLW(int mt, REAL ein, vector<REAL>& mu_boundary, vector<REAL>& pdf,
	FMEneAngDist& eadist, FMEneAngDist& ead_wk, int coord, bool delayed)
{
	eadist.setZero();

	DLW* dlw_wk;
	REAL weight_sum = 0.0;
	int dlw_block_num;
	if (delayed == false) dlw_block_num = dlw[mt].size();
	else dlw_block_num = dlw_delayed[mt].size();

	for (int idw = 0; idw < dlw_block_num; idw++)
	{
		if (delayed == false) dlw_wk = &dlw[mt][idw];
		else dlw_wk = &dlw_delayed[mt][idw];

		REAL weight = endfInterpolator(dlw_wk->nr, dlw_wk->nbtt, dlw_wk->intt, dlw_wk->etab, dlw_wk->ptab, ein*1.0e-6);
		weight_sum += weight;

		ead_wk.setZero();

		int law = dlw_wk->law;
		switch (law)
		{
		case 3:
		{
			//law = 3
			getEnergyDistributionwithDLWLaw3(mt, ein, mu_boundary, pdf, coord, dlw_wk, ead_wk);
			break;
		}
		case 4:
		case 7:
		case 9:
		case 11:
		{
			//law = 4, 7, 9, 11 (file 5)
			getEnergyDistributionwithDLWLaw4Law7Law9Law11(mt, ein, mu_boundary, pdf, coord, dlw_wk, ead_wk, idw, delayed);
			break;
		}
		case 44:
		case 61:
		{
			//law = 44, 61 (file 6)
			getEnergyDistributionwithDLWLaw44Law61(mt, ein, mu_boundary, pdf, coord, dlw_wk, ead_wk, idw, delayed);
			break;
		}
		case 66:
		{
			getEnergyDistributionwithDLWLaw66(mt, ein, dlw_wk, ead_wk);
			break;
		}
		default:
			cout << " mt = " << mt << " this law is not implemented " << law << endl;
			exit(0);
		}
		eadist.add(weight, ead_wk);
	}

	//normalize
	eadist.normalize();
}
void FMACECrossSectionProcessor::getEnergyDistributionwithDLWLaw3(int mt, REAL ein, vector<REAL>& mu_boundary, vector<REAL>& pdf, int coord, DLW* dlw_wk, FMEneAngDist& ead_wk)
{
	//law = 3
	REAL ldat1 = dlw_wk->ldat[0] * 1.0e+6;	//in [eV]
	REAL ldat2 = dlw_wk->ldat[1];
	if (ein < ldat1) return;

	//minimum/maximum energy
	REAL e_min = getEoutAfterInElasticScattering(ein, -1.0, ldat1, ldat2);
	REAL e_max = getEoutAfterInElasticScattering(ein, +1.0, ldat1, ldat2);

	for (int ig = 0; ig < ead_wk.max_ng; ig++)
	{
		//set upper and lower energy range for e_out
		REAL e_upper = ead_wk.ene_boundary[ig];
		REAL e_lower = ead_wk.ene_boundary[ig + 1];

		if (e_max < e_lower) continue;
		if (e_min > e_upper) continue;
		if (e_min > e_lower&& e_min < e_upper) e_lower = e_min;
		if (e_max > e_lower&& e_max < e_upper) e_upper = e_max;

		//set division for e_out
		vector<REAL> eout_boundary;

		int ndiv = MAX_EOUT_DIV_ELASTIC;
		int num_table_points = getMaxTablePointsInAngularPDF(mt, ein);
		if (ndiv < num_table_points) ndiv = num_table_points;

		eout_boundary.resize(ndiv + 1);
		for (int i = 0; i <= ndiv; i++)
		{
			REAL eowk = (log(e_upper) - log(e_lower)) / (REAL)ndiv * (REAL)i + log(e_lower);
			eout_boundary[i] = exp(eowk);
		}

		vector<REAL> pdfwk, mulwk, delta_mul;
		pdfwk.resize(ndiv);
		mulwk.resize(ndiv);
		delta_mul.resize(ndiv);
		for (int i = 0; i < ndiv; i++)
		{
			REAL eoutave = sqrt(eout_boundary[i + 1] * eout_boundary[i]);

			//muc
			REAL wkmcl = getMucAfterInElasticScattering(ein, eout_boundary[i], ldat1, ldat2);
			REAL wkmcave = getMucAfterInElasticScattering(ein, eoutave, ldat1, ldat2);
			REAL wkmcu = getMucAfterInElasticScattering(ein, eout_boundary[i + 1], ldat1, ldat2);

			//mul
			REAL wkmll = convertCMtoLabDirectionCosineInelastic(wkmcl, ein, ldat1);
			REAL wkmlave = convertCMtoLabDirectionCosineInelastic(wkmcave, ein, ldat1);
			REAL wkmlu = convertCMtoLabDirectionCosineInelastic(wkmcu, ein, ldat1);

			//pdf interporation
			REAL wkp;
			if (coord == eCenterOfMassSystem)
			{
				wkp = interporatePdf(mu_boundary, pdf, wkmcave);
				wkp = convertCMtoLabPDFInelastic(wkp, wkmcave, ein, ldat1);
			}
			else
			{
				wkp = interporatePdf(mu_boundary, pdf, wkmlave);
			}
			mulwk[i] = wkmlave;
			pdfwk[i] = wkp;
			delta_mul[i] = wkmlu - wkmll;
		}
		vector<REAL> coef;

		//Integrated pdf
		REAL pdfsum = 0.0;
		for (int i = 0; i < ndiv; i++)
			pdfsum += pdfwk[i] * delta_mul[i];
		ead_wk.pdf[ig] = pdfsum;

		//Legendre coefficients
		calcPlCoefficient(mulwk, delta_mul, pdfwk, coef, ead_wk.max_pl);
		for (int il = 0; il <= ead_wk.max_pl; il++)
			ead_wk.pl_coef[ig][il] = coef[il];
	}
}
void FMACECrossSectionProcessor::getEnergyDistributionwithDLWLaw4Law7Law9Law11(int mt, REAL ein, vector<REAL>& mu_boundary, vector<REAL>& pdf, int coord, DLW* dlw_wk, FMEneAngDist& ead_wk, int idw, bool delayed)
{
	int law = dlw_wk->law;
	int ndiv = mu_boundary.size() - 1;
	vector<REAL> pdfwk, mulwk, delta_mul;
	pdfwk.resize(ndiv);
	mulwk.resize(ndiv);
	delta_mul.resize(ndiv);
	for (int i = 0; i < ndiv; i++)
	{
		//pdf interporation
		REAL wkmcl, wkmcave, wkmcu, wkmll, wkmlave, wkmlu;
		REAL wkp;
		if (coord == eCenterOfMassSystem)
		{
			REAL qval = abs(getQValue(mt)) * (aw + 1) / aw * 1.0e+6;
			if (ein >= qval)
			{
				wkmcl = mu_boundary[i];
				wkmcave = (mu_boundary[i] + mu_boundary[i + 1]) / 2.0;
				wkmcu = mu_boundary[i + 1];
				wkp = interporatePdf(mu_boundary, pdf, wkmcave);
				wkmll = convertCMtoLabDirectionCosineInelastic(wkmcl, ein, qval);
				wkmlave = convertCMtoLabDirectionCosineInelastic(wkmcave, ein, qval);
				wkmlu = convertCMtoLabDirectionCosineInelastic(wkmcu, ein, qval);
				wkp = convertCMtoLabPDFInelastic(wkp, wkmcave, ein, qval);
			}
			else
			{
				wkmll = mu_boundary[i];
				wkmlave = (mu_boundary[i] + mu_boundary[i + 1]) / 2.0;
				wkmlu = mu_boundary[i + 1];
				wkp = interporatePdf(mu_boundary, pdf, wkmlave);
			}
		}
		else
		{
			wkmll = mu_boundary[i];
			wkmlave = (mu_boundary[i] + mu_boundary[i + 1]) / 2.0;
			wkmlu = mu_boundary[i + 1];
			wkp = interporatePdf(mu_boundary, pdf, wkmlave);
		}
		mulwk[i] = wkmlave;
		pdfwk[i] = wkp;
		delta_mul[i] = wkmlu - wkmll;
	}
	vector<REAL> coef;

	//Legendre coefficients
	calcPlCoefficient(mulwk, delta_mul, pdfwk, coef, ead_wk.max_pl);

	int _nr = rtoi(dlw_wk->ldat[0]);
	vector<int> nbtt(_nr), intt(_nr);
	if (_nr != 0)
	{
		for (int i = 0; i < _nr; i++)
			nbtt[i] = rtoi(dlw_wk->ldat[i + 1]);
		for (int i = 0; i < _nr; i++)
			intt[i] = rtoi(dlw_wk->ldat[i + _nr + 1]);
	}
	int ne = rtoi(dlw_wk->ldat[2 * _nr + 1]);
	vector<REAL> egrid(ne);
	for (int j = 0; j < ne; j++)
		egrid[j] = dlw_wk->ldat[j + 2 * _nr + 2] * 1.0e6;

	int e0 = 0;
	int e1 = 0;

	if (ne > 1)
	{
		e0 = getInterval(egrid, ein, true);
		e1 = e0 + 1;
	}
	else
	{
		e0 = 0;
		e1 = 0;
	}

	if (law == 4)
	{
		vector<int> loc(ne);
		for (int j = 0; j < ne; j++)
			loc[j] = rtoi(dlw_wk->ldat[j + 2 * _nr + ne + 2]);

		MCEData mcedata0, mcedata1, mcedata;
		int key0 = getKeyValueForMCEDataStorage(mt, idw, e0);
		if (mcedata_temporary.find(key0) == mcedata_temporary.end())
		{
			mcedata0.max_pl = ead_wk.max_pl;
			mcedata0.ein = egrid[e0];
			getEnergyPDFLaw4(law, coord, loc[e0], mcedata0, delayed);
			mcedata_temporary.insert(make_pair(key0, mcedata0));
		}
		int key1 = getKeyValueForMCEDataStorage(mt, idw, e1);
		if (mcedata_temporary.find(key1) == mcedata_temporary.end())
		{
			mcedata1.max_pl = ead_wk.max_pl;
			mcedata1.ein = egrid[e1];
			getEnergyPDFLaw4(law, coord, loc[e1], mcedata1, delayed);
			mcedata_temporary.insert(make_pair(key1, mcedata1));
		}
		mcedata.ein = ein;
		mcedata.max_pl = ead_wk.max_pl;
		int inttval = getIntt(_nr, nbtt, intt, e0);
		if (inttval > 10)
		{
			cout << " intt > 10 not implemented in FMACECrossSectionProcessor::getEnergyDistribution " << endl;
			exit(0);
		}
#if 1
		//MCE interpolation
		doMCEInterporation(10, inttval, mcedata_temporary[key0], mcedata_temporary[key1], mcedata);
		convertMCEDataToAngDist(mcedata, ead_wk);
#else
		//ENDF interpolation
		FMEneAngDist eadwk0, eadwk1;
		eadwk0.resize(ead_wk.max_ng);
		eadwk1.resize(ead_wk.max_ng);
		eadwk0.resizePlCoef(ead_wk.max_pl);
		eadwk1.resizePlCoef(ead_wk.max_pl);
		eadwk0.setEnergyBoundary(ead_wk.ene_boundary);
		eadwk1.setEnergyBoundary(ead_wk.ene_boundary);
		eadwk0.setZero();
		eadwk1.setZero();
		convertMCEDataToAngDist(mcedata_temporary[key0], eadwk0);
		convertMCEDataToAngDist(mcedata_temporary[key1], eadwk1);
		doEneAngDistInterporation(inttval, egrid[e0], egrid[e1], ein, eadwk0, eadwk1, ead_wk);
#endif

	}
	else if (law == 7 || law == 9)
	{
		REAL theta0 = dlw_wk->ldat[e0 + 2 * _nr + ne + 2];
		//REAL theta1 = dlw_wk->ldat[e1 + 2 * nr + ne + 2];
		int inttval = getIntt(_nr, nbtt, intt, e0);
		if (inttval > 10)
		{
			cout << " intt > 10 not implemented in FMACECrossSectionProcessor::getEnergyDistribution " << endl;
			exit(0);
		}
		//REAL theta = endfInterpolator2Point(inttval, egrid[e0], egrid[e1], theta0, theta1, ein);
		REAL u = dlw_wk->ldat[2 * _nr + 2 * ne + 2];
		getEnergyPDFLaw7Law9(law, ein, theta0, u, ead_wk);
	}
	else if (law == 11)
	{
		vector<REAL> coef_a(ne);
		for (int j = 0; j < ne; j++)
		{
			REAL val = dlw_wk->ldat[j + 2 * _nr + 2 + ne];
			if (val > 1.0e+8)
				coef_a[j] = val / 1.0e12;	//temporary fix for bug of FRENDY/ACE
			else
				coef_a[j] = val;
		}

		int offset = 3 + 2 * (_nr + ne) - 1;
		int nrb = rtoi(dlw_wk->ldat[offset]);
		vector<int> nbttb(nrb), inttb(nrb);
		if (nrb != 0)
		{
			for (int i = 0; i < nrb; i++)
				nbttb[i] = rtoi(dlw_wk->ldat[offset + i + 1]);
			for (int i = 0; i < nrb; i++)
				inttb[i] = rtoi(dlw_wk->ldat[offset + i + nrb + 1]);
		}
		int neb = rtoi(dlw_wk->ldat[2 * _nr + 1]);
		vector<REAL> egridb(neb);
		for (int j = 0; j < neb; j++)
			egrid[j] = dlw_wk->ldat[offset + j + 2 * nrb + 2] * 1.0e6;
		vector<REAL> coef_b(neb);
		for (int j = 0; j < neb; j++)
			coef_b[j] = dlw_wk->ldat[offset + j + 2 * nrb + 2 + neb];
		REAL u = dlw_wk->ldat[offset + 2 * nrb + 2 + neb + neb];
		REAL aa = endfInterpolator(_nr, nbtt, intt, egrid, coef_a, ein);
		REAL bb = endfInterpolator(_nr, nbtt, intt, egrid, coef_b, ein);
		getEnergyPDFLaw11(ein, aa, bb, u, ead_wk);
	}
	else
	{
		cout << " error " << endl;
		exit(0);
	}

	//pl coefficients
	for (int ie = 0; ie < ead_wk.max_ng; ie++)
	{
		ead_wk.pl_coef[ie][0] = ead_wk.pdf[ie];
		REAL fact = ead_wk.pdf[ie] / coef[0];
		for (int il = 0; il <= ead_wk.max_pl; il++)
			ead_wk.pl_coef[ie][il] = fact * coef[il];
	}
}
void FMACECrossSectionProcessor::getEnergyDistributionwithDLWLaw44Law61(int mt, REAL ein, vector<REAL>& mu_boundary, vector<REAL>& pdf, int coord, DLW* dlw_wk, FMEneAngDist& ead_wk, int idw, bool delayed)
{
	int law = dlw_wk->law;
	int _nr = rtoi(dlw_wk->ldat[0]);
	vector<int> nbtt(_nr), intt(_nr);
	if (_nr != 0)
	{
		for (int i = 0; i < _nr; i++)
			nbtt[i] = rtoi(dlw_wk->ldat[i + 1]);
		for (int i = 0; i < _nr; i++)
			intt[i] = rtoi(dlw_wk->ldat[i + _nr + 1]);
	}
	int ne = rtoi(dlw_wk->ldat[2 * _nr + 1]);
	vector<REAL> egrid(ne);
	for (int j = 0; j < ne; j++)
		egrid[j] = dlw_wk->ldat[j + 2 * _nr + 2] * 1.0e6;

	int e0 = 0;
	int e1 = 0;

	if (ne > 1)
	{
		e0 = getInterval(egrid, ein, true);
		e1 = e0 + 1;
	}
	else
	{
		e0 = 0;
		e1 = 0;
	}

	vector<int> loc(ne);
	for (int j = 0; j < ne; j++)
		loc[j] = rtoi(dlw_wk->ldat[j + 2 * _nr + ne + 2]);

	//interporation
	int inttval = getIntt(_nr, nbtt, intt, e0);
	if (inttval > 10)
	{
		cout << " intt > 10 not implemented in FMACECrossSectionProcessor::getEnergyDistribution " << endl;
		exit(0);
	}

	//use endf interpolation after converting to multi-group
	int key0 = getKeyValueForMCEDataStorage(mt, idw, e0);
	if (eaddata_temporary.find(key0) == eaddata_temporary.end())
	{
		FMEneAngDist eadtmp;
		eadtmp.resize(ead_wk.max_ng+1);
		eadtmp.resizePlCoef(ead_wk.max_pl);

		vector<REAL> ene_boundary((int)ead_wk.ene_boundary.size());
		for (int i = 0; i < (int)ead_wk.ene_boundary.size(); i++)
			ene_boundary[i] = ead_wk.ene_boundary[i];
		ene_boundary.push_back(egrid[e0]);
		sort(ene_boundary.begin(), ene_boundary.end(), std::greater<REAL>());

		eadtmp.setEnergyBoundary(ene_boundary);
		eadtmp.setZero();
		getEnergyAnglePDFLaw44Law61(law, coord, loc[e0], egrid[e0], eadtmp);
		eaddata_temporary.insert(make_pair(key0, eadtmp));
	}

	int key1 = getKeyValueForMCEDataStorage(mt, idw, e1);
	if (eaddata_temporary.find(key1) == eaddata_temporary.end())
	{
		FMEneAngDist eadtmp;
		eadtmp.resize(ead_wk.max_ng+1);
		eadtmp.resizePlCoef(ead_wk.max_pl);

		vector<REAL> ene_boundary((int)ead_wk.ene_boundary.size());
		for (int i = 0; i < (int)ead_wk.ene_boundary.size(); i++)
			ene_boundary[i] = ead_wk.ene_boundary[i];
		ene_boundary.push_back(egrid[e1]);
		sort(ene_boundary.begin(), ene_boundary.end(), std::greater<REAL>());

		eadtmp.setEnergyBoundary(ene_boundary);
		eadtmp.setZero();
		getEnergyAnglePDFLaw44Law61(law, coord, loc[e1], egrid[e1], eadtmp);
		eaddata_temporary.insert(make_pair(key1, eadtmp));
	}

	//MCE interpolation
	MCEData md0, md1, md;
	convertAngDistToMCEData(inttval, egrid[e0], eaddata_temporary[key0], md0);
	convertAngDistToMCEData(inttval, egrid[e1], eaddata_temporary[key1], md1);
	md.ein = ein;
	md.max_pl = md0.max_pl;
	md.intt = inttval;
	ead_wk.setZero();
	if (md0.np == 0 && md1.np != 0)
	{
		convertMCEDataToAngDist(md1, ead_wk);
	}
	else if (md0.np != 0 && md1.np == 0)
	{
		convertMCEDataToAngDist(md0, ead_wk);
	}
	else if (md0.np != 0 && md1.np != 0)
	{
		doMCEInterporation(10, inttval, md0, md1, md);
		convertMCEDataToAngDist(md, ead_wk);
	}

}
void FMACECrossSectionProcessor::getEnergyDistributionwithDLWLaw66(int mt, REAL ein, DLW* dlw_wk, FMEneAngDist& ead_wk)
{
	//law = 66, N-body phase space distribution
	int  npsx = rtoi(dlw_wk->ldat[0]);
	REAL ap = dlw_wk->ldat[1];

	for (int ig = 0; ig < ead_wk.max_ng; ig++)
	{
		//set upper and lower energy range for e_out
		REAL e_upper = ead_wk.ene_boundary[ig];
		REAL e_lower = ead_wk.ene_boundary[ig + 1];

		if (ein < e_lower) continue;
		if (ein > e_lower && ein < e_upper) e_upper = ein;

		//set division for e_out
		vector<REAL> eout_boundary;

		int ediv = MAX_EOUT_DIV_LAW66;

		eout_boundary.resize(ediv + 1);
		for (int i = 0; i <= ediv; i++)
		{
			REAL eowk = (log(e_upper) - log(e_lower)) / (REAL)ediv * (REAL)i + log(e_lower);
			eout_boundary[i] = exp(eowk);
		}
		sort(eout_boundary.begin(), eout_boundary.end(), std::greater<REAL>());

		for (int i = 0; i < ediv; i++)
		{
			REAL eoutave = sqrt(eout_boundary[i + 1] * eout_boundary[i]);
			REAL eoutdelta = eout_boundary[i] - eout_boundary[i + 1];

			int mdiv = MAX_MU_DIV_LAW66;
			vector<REAL> pdfwk, mulwk, delta_mul;
			pdfwk.resize(mdiv);
			mulwk.resize(mdiv);
			delta_mul.resize(mdiv);

			for (int j = 0; j < mdiv; j++)
			{
				//mul
				REAL wkmll = 2.0*(REAL)j / (REAL)mdiv - 1.0;
				REAL wkmlu = 2.0*(REAL)(j+1) / (REAL)mdiv - 1.0;
				REAL wkmlave = (wkmll + wkmlu) / 2.0;

				//pdf calculation
				REAL q = getQValue(mt)*1.0e+6;
				REAL eimax = (ap - 1.0) / ap*(aw / (aw + 1)*ein + q);
				REAL wkp = 0.0;
				if (eimax > 0.0)
				{
					REAL cn = 0.0;
					if (npsx == 3)
						cn = 4.0 / PI / pow(eimax, 2.0);
					else if (npsx == 4)
						cn = 105.0 / 32.0 / pow(eimax, 3.5);
					else
						cn = 256.0 / 14.0 / PI / pow(eimax, 5.0);

					REAL es = ein * 1.0 / (aw + 1.0) / (aw + 1.0);
					REAL val = eimax - (es + eoutave - 2.0 * wkmlave * sqrt(es * eoutave));
					if (val < 0.0) val = 0.0;
					wkp = cn * sqrt(eoutave) * pow(val, 3.0 * (REAL)npsx / 2.0 - 4.0);
#if 0
					if (std::isnan(wkp))
					{
						cout << setw(15) << q;
						cout << setw(15) << eimax;
						cout << setw(15) << eoutave;
						cout << setw(15) << wkmlave;
						cout << setw(15) << cn;
						cout << setw(15) << es;
						cout << setw(15) << val;
						cout << endl;
					}
#endif
				}
				mulwk[j] = wkmlave;
				pdfwk[j] = wkp * eoutdelta;
				delta_mul[j] = wkmlu - wkmll;
			}

			//Integrated pdf
			REAL pdfsum = 0.0;
			for (int j = 0; j < mdiv; j++)
				pdfsum += pdfwk[j] * delta_mul[j];
			ead_wk.pdf[ig] += pdfsum;

			//Legendre coefficients
			vector<REAL> coef;
			calcPlCoefficient(mulwk, delta_mul, pdfwk, coef, ead_wk.max_pl);
			for (int il = 0; il <= ead_wk.max_pl; il++)
				ead_wk.pl_coef[ig][il] += coef[il];
		}
	}
}
void FMACECrossSectionProcessor::getEnergyPDFLaw4(int law, int coord, int offset, MCEData& md, bool delayed)
{
	offset--;
	int jed;
	if (delayed == false)
		jed = jxs[10] - 1;
	else
		jed = jxs[26] - 1;
	offset += jed;

	int intt = rtoi(xss[offset]);
	int np = rtoi(xss[offset + 1]);
	int max_pl = md.max_pl;

	md.intt = intt;
	md.np = np;
	md.eout.resize(np);
	md.data.resize(2 + max_pl + 1);
	for (int i = 0; i < static_cast<int>(md.data.size()); i++)
		md.data[i].resize(np);

	vector<REAL> aa(np), rr(np);
	vector<int> lc(np);
	for (int i = 0; i < np; i++)
		md.eout[i] = xss[offset + 2 + i] * 1.0e6;
	for (int i = 0; i < np; i++)
		md.data[0][i] = xss[offset + 2 + np + i];
	for (int i = 0; i < np; i++)
		md.data[1][i] = xss[offset + 2 + 2 * np + i];

	if (md.data[1].back() > 1.01 || md.data[1].back() < 0.99)
	{
		cout << " Maximum value of CDF = " << md.data[1].back() << endl;
		printError(" Maximum value of CDF in DLW block (law=4) is larger than/smaller than 1.0 ");
	}

	vector<REAL> pl_coef_wk;

	//calculate pl coefficients
	for (int i = 0; i < np; i++)
	{

		if (law == 4)
		{
			pl_coef_wk.resize(max_pl + 1);
			pl_coef_wk[0] = 1.0;
			for (int ii = 1; ii <= max_pl; ii++)
				pl_coef_wk[ii] = 0.0;
		}
		else
		{
			cout << " error in FMACECrossSectionProcessor::getEnergyPDFLaw4 " << endl;
			exit(0);
		}
		for (int ii = 0; ii <= max_pl; ii++)
			md.data[2 + ii][i] = pl_coef_wk[ii];
	}
}
void FMACECrossSectionProcessor::getEnergyPDFLaw7Law9(int law, REAL ein, REAL theta, REAL u, FMEneAngDist& eadistwk)
{
	if (ein*1.0e-6 < u) return;

	vector<REAL> e_boundary;
	e_boundary.resize(eadistwk.max_ng + 1);
	for (int i = 0; i <= eadistwk.max_ng; i++)
		e_boundary[i] = eadistwk.ene_boundary[i];
	if (u*1.0e6 >= e_boundary.back())
		e_boundary.push_back(u*1.0e6);
	if (ein - u*1.0e6 >= e_boundary.back())
		e_boundary.push_back(ein - u*1.0e6);
	sort(e_boundary.begin(), e_boundary.end());

	for (int i = 0; i < static_cast<int>(e_boundary.size()) - 1; i++)
	{
		REAL e0 = e_boundary[i]*1.0e-6;
		REAL e1 = e_boundary[i+1]*1.0e-6;
		REAL ene = (e0 + e1) / 2.0;
		if (ene > ein*1.0e-6-u) continue;
		REAL val0, val1;
		if (law == 7)
		{
			val0 = -theta*exp(-e0 / theta)*sqrt(e0) + 0.5*theta*sqrt(theta)*sqrt(PI)*erf(sqrt(e0 / theta));
			val1 = -theta*exp(-e1 / theta)*sqrt(e1) + 0.5*theta*sqrt(theta)*sqrt(PI)*erf(sqrt(e1 / theta));
		}
		else if (law == 9)
		{
			val0 = -theta * (theta + e0) * exp(-e0 / theta);
			val1 = -theta * (theta + e1) * exp(-e1 / theta);
		}
		else
		{
			cout << " error in FMACECrossSectionProcessor::getEnergyPDFLaw7Law9 " << endl;
			exit(0);
		}
		REAL val = val1 - val0;
		if (val < 0.0) val = 0.0;
		ene *= 1.0e6;
		int ie;
#ifdef _FM_EXTEND_MAXIMUM_OUTGOING_ENERGY_FOR_LAW_
		//tally fission spectrum for energy region > upper energy into the 1st group
		if (ene >= eadistwk.ene_boundary[0])
			ie = 0;
		else
			ie = eadistwk.getEnergyGroup(ene);
#else
		if (ene >= eadistwk.ene_boundary[0])
			continue;
		else
			ie = eadistwk.getEnergyGroup(ene);
#endif
		eadistwk.pdf[ie] += val;
	}
}
void FMACECrossSectionProcessor::getEnergyPDFLaw11(REAL ein, REAL aa, REAL bb, REAL u, FMEneAngDist& eadistwk)
{
	if (ein*1.0e-6 < u) return;

	vector<REAL> e_boundary;
	e_boundary.resize(eadistwk.max_ng + 1);
	for (int i = 0; i <= eadistwk.max_ng; i++)
		e_boundary[i] = eadistwk.ene_boundary[i];
	if (u*1.0e6 >= e_boundary.back())
		e_boundary.push_back(u*1.0e6);
	if (ein - u*1.0e6 >= e_boundary.back())
		e_boundary.push_back(ein - u*1.0e6);
	sort(e_boundary.begin(), e_boundary.end());

	for (int i = 0; i < static_cast<int>(e_boundary.size()) - 1; i++)
	{
		REAL e0 = e_boundary[i] * 1.0e-6;
		REAL e1 = e_boundary[i + 1] * 1.0e-6;
		REAL ene = (e0 + e1) / 2.0;
		if (ene > ein*1.0e-6 - u) continue;
		REAL val0 = integrationLAW11(aa, bb, e0);
		REAL val1 = integrationLAW11(aa, bb, e1);
		REAL val = val1 - val0;
		if (val < 0.0) val = 0.0;
		ene *= 1.0e6;
		int ie;
#ifdef _FM_EXTEND_MAXIMUM_OUTGOING_ENERGY_FOR_LAW_
		//tally fission spectrum for energy region > upper energy into the 1st group
		if (ene >= eadistwk.ene_boundary[0])
			ie = 0;
		else
			ie = eadistwk.getEnergyGroup(ene);
#else
		if (ene >= eadistwk.ene_boundary[0])
			continue;
		else
			ie = eadistwk.getEnergyGroup(ene);
#endif
		eadistwk.pdf[ie] += val;
	}
}
void FMACECrossSectionProcessor::getEnergyAnglePDFLaw44Law61(int law, int coord, int offset, REAL ein, FMEneAngDist& ead, bool delayed)
{
	offset--;
	int jed;
	if (delayed == false)
		jed = jxs[10] - 1;
	else
		jed = jxs[26] - 1;
	offset += jed;

	int intt = rtoi(xss[offset]);
	int np = rtoi(xss[offset + 1]);
	int max_pl = ead.max_pl;

	vector<REAL> eout_vec(np);
	vector<vector<REAL> > data(2);		//[np][pdf, cdf]
	for (int i = 0; i < static_cast<int>(data.size()); i++)
		data[i].resize(np);

	vector<REAL> aa(np), rr(np);
	vector<int> lc(np);

	for (int i = 0; i < np; i++)
		eout_vec[i] = xss[offset + 2 + i] * 1.0e6;
	for (int i = 0; i < np; i++)
		data[0][i] = xss[offset + 2 + np + i];	//pdf
	for (int i = 0; i < np; i++)
		data[1][i] = xss[offset + 2 + 2 * np + i];	//cdf

	if (law == 61)
	{
		for (int i = 0; i < np; i++)
			lc[i] = rtoi(xss[offset + 2 + 3 * np + i]);
	}
	else if (law == 44)
	{
		for (int i = 0; i < np; i++)
			rr[i] = xss[offset + 2 + 3 * np + i];
		for (int i = 0; i < np; i++)
			aa[i] = xss[offset + 2 + 4 * np + i];
	}
	else
	{
		cout << " error in FMACECrossSectionProcessor::getEnergyAnglePDFLaw4Law44Law61 " << endl;
		exit(0);
	}

	//set eout_vec max, min in CM system
	REAL eout_cm_max = eout_vec.back();

	//set eout_vec max, min in LAB system
	REAL val = sqrt(eout_cm_max / ein) + sqrt(1.0 / ((aw + 1.0) * (aw + 1.0)));
	REAL eout_lab_max = ein * val * val;
	//REAL eout_lab_max_wk = eout_cm_max + (ein + 2.0 * (aw + 1.0) * sqrt(ein * eout_cm_max)) / (aw + 1.0) / (aw + 1.0);

	//set eout_vec grid in LAB system
	for (int ig = 0; ig < ead.max_ng; ig++)
	{
		//set upper and lower energy range for e_out
		REAL e_upper = ead.ene_boundary[ig];
		REAL e_lower = ead.ene_boundary[ig + 1];

		if (eout_lab_max < e_lower) continue;
		if (eout_lab_max > e_lower&& eout_lab_max < e_upper) e_upper = eout_lab_max;

		//set division for e_out
		vector<REAL> eout_lab_boundary;

		//number of divisions for energy integration
		int ndiv = getNumberOfDivisionsInEnergyGroupDLWLaw44Law61(e_upper, e_lower);

		//number of divisions for angular integration
		int mu_div_min = 20;
		int mu_div = getMaxAngularPdfPointInLaw61(jed, lc);
		if (mu_div < mu_div_min) mu_div = mu_div_min;

		eout_lab_boundary.resize(ndiv + 1);
		for (int i = 0; i <= ndiv; i++)
		{
			REAL eowk = (log(e_upper) - log(e_lower)) / (REAL)ndiv * (REAL)i + log(e_lower);
			eout_lab_boundary[i] = exp(eowk);
		}

		//REAL pdfsum = 0.0;
		for (int i = 0; i < ndiv; i++)
		{
			REAL eout_lab_ave = sqrt(eout_lab_boundary[i + 1] * eout_lab_boundary[i]);
			REAL eout_lab_delta = eout_lab_boundary[i + 1] - eout_lab_boundary[i];

			//set c
			REAL awp1 = aw + 1.0;
			REAL c = 1.0 / awp1 * sqrt(ein / eout_lab_ave);

			//set minimum and maximum values of mul
			REAL mul_min;
			if (coord == eLaboratorySystem)
				mul_min = -1.0;
			else
			{
				mul_min = 1.0 / 2.0 / c * (1.0 + c * c - eout_cm_max / eout_lab_ave);
				if (mul_min < -1.0) mul_min = -1.0;
			}
			REAL mul_max = 1.0;

			//perform integration on mul from mul min to +1
			vector<REAL> pdfwk, mulwk, delta_mul;

			pdfwk.resize(mu_div);
			mulwk.resize(mu_div);
			delta_mul.resize(mu_div);

			vector<REAL> pl_coef;
			for (int j = 0; j < mu_div; j++)
			{
				REAL wkmll = (mul_max - mul_min) * (REAL)j / (REAL)mu_div + mul_min;
				REAL wkmlu = (mul_max - mul_min) * (REAL)(j + 1) / (REAL)mu_div + mul_min;
				REAL wkmlave = (wkmll + wkmlu) / 2.0;
				mulwk[j] = wkmlave;
				delta_mul[j] = wkmlu - wkmll;

				//set J (Jacobian)
				REAL J = 1.0 / sqrt(1.0 + c * c - 2.0 * c * wkmlave);

				//mu in CM system
				REAL wkmcave = J * (wkmlave - c);

				//set eout in CM system
				REAL eout_cm_ave = eout_lab_ave / (J * J);

				//interpolate table
				REAL eout_wk, wkmave;
				if (coord == eLaboratorySystem)
				{
					eout_wk = eout_lab_ave;
					wkmave = wkmlave;
					J = 1.0;
				}
				else
				{
					eout_wk = eout_cm_ave;
					wkmave = wkmcave;
				}
				int ind = getInterval(eout_vec, eout_wk);
				REAL pdf = endfInterpolator2Point(intt, eout_vec[ind], eout_vec[ind + 1], data[0][ind], data[0][ind + 1], eout_wk, eExtraporationZero);
				REAL pdfmu0, pdfmu1;
				switch (law)
				{
				case 44:
					pdfmu0 = getKalbach87(wkmave, rr[ind], aa[ind]);
					pdfmu1 = getKalbach87(wkmave, rr[ind+1], aa[ind+1]);
					break;
				case 61:
					pdfmu0 = interpolatePdfLaw61(jed + lc[ind] - 1, wkmave, data);
					pdfmu1 = interpolatePdfLaw61(jed + lc[ind + 1] - 1, wkmave, data);
					break;
				default:
					cout << " this law is not implemented in FMACECrossSectionProcessor::getEnergyAnglePDFLaw44Law61 " << endl;
					exit(0);
					break;
				}
				REAL pdfmu = endfInterpolator2Point(intt, eout_vec[ind], eout_vec[ind + 1], pdfmu0, pdfmu1, eout_wk);

				pdfwk[j] = pdf * pdfmu * J;
			}
			calcPlCoefficient(mulwk, delta_mul, pdfwk, pl_coef, max_pl);

			//Legendre coefficients
			for (int il = 0; il <= ead.max_pl; il++)
				ead.pl_coef[ig][il] += pl_coef[il] * eout_lab_delta * 1.0e-6;
		}
		ead.pdf[ig] = ead.pl_coef[ig][0];
	}
}
void FMACECrossSectionProcessor::doMCEInterporation(int ndiv, int intt, MCEData& md0, MCEData& md1, MCEData& md)
{
	vector<REAL> eowk0(ndiv + 1), eowk1(ndiv + 1), eowk(ndiv + 1), eoadd;

	vector<REAL> val(ndiv + 1);
	for (int i = 0; i <= ndiv; i++)
		val[i] = 1.0 / (REAL)ndiv * (REAL)i;

	for (int i = 0; i <= ndiv; i++)
	{
		eowk0[i] = getXboundaryValue(md0.eout, md0.data[1], val[i]);
		eowk1[i] = getXboundaryValue(md1.eout, md1.data[1], val[i]);
		eowk[i] = endfInterpolator2Point(intt, md0.ein, md1.ein, eowk0[i], eowk1[i], md.ein);
		eoadd.push_back(eowk[i]);
	}
	for (int i = 0; i < md0.np; i++)
	{
		int ii = getInterval(eowk0, md0.eout[i]);
		REAL eo = (md0.eout[i] - eowk0[ii]) / (eowk0[ii + 1] - eowk0[ii]) * (eowk[ii + 1] - eowk[ii]) + eowk[ii];
		if (eo < eowk[0]) eo = eowk[0];
		if (eo > eowk.back()) eo = eowk.back();
		eoadd.push_back(eo);
	}
	for (int i = 0; i < md1.np; i++)
	{
		int ii = getInterval(eowk1, md1.eout[i]);
		REAL eo = (md1.eout[i] - eowk1[ii]) / (eowk1[ii + 1] - eowk1[ii]) * (eowk[ii + 1] - eowk[ii]) + eowk[ii];
		if (eo < eowk[0]) eo = eowk[0];
		if (eo > eowk.back()) eo = eowk.back();
		eoadd.push_back(eo);
	}

	sort(eoadd.begin(), eoadd.end());
	md.eout.clear();
	md.eout.push_back(eoadd[0]);
	for (int i = 1; i < static_cast<int>(eoadd.size()); i++)
	{
		REAL eps = abs((eoadd[i] - md.eout.back()) / (eoadd[i] + md.eout.back()));
		if (eps > 1.0e-6) md.eout.push_back(eoadd[i]);
	}

	md.np = md.eout.size();
	md.data.resize(md0.data.size());
	for (int i = 0; i < static_cast<int>(md0.data.size()); i++)
		md.data[i].resize(md.np);

	if (abs(md0.ein - md.ein) > abs(md1.ein - md.ein)) md.intt = md1.intt;
	else md.intt = md0.intt;

	for (int i = 0; i < static_cast<int>(md.eout.size()); i++)
	{
		REAL eo = md.eout[i];
		int ii = getInterval(eowk, eo);
		REAL eo0 = (eo - eowk[ii]) / (eowk[ii + 1] - eowk[ii]) * (eowk0[ii + 1] - eowk0[ii]) + eowk0[ii];
		REAL eo1 = (eo - eowk[ii]) / (eowk[ii + 1] - eowk[ii]) * (eowk1[ii + 1] - eowk1[ii]) + eowk1[ii];

		//linear interporation for cdf
		REAL dwk0 = doInterporationFromVector(2, md0.eout, md0.data[1], eo0, eExtraporationConst);
		REAL dwk1 = doInterporationFromVector(2, md1.eout, md1.data[1], eo1, eExtraporationConst);
		REAL dwk = endfInterpolator2Point(intt, md0.ein, md1.ein, dwk0, dwk1, md.ein);
		md.data[1][i] = dwk;

		//interporation of other parameters
		REAL delta_eo0 = eowk0[ii + 1] - eowk0[ii];
		REAL delta_eo1 = eowk1[ii + 1] - eowk1[ii];
		REAL delta_eo  = eowk[ii + 1] - eowk[ii];

		for (int j = 0; j < static_cast<int>(md0.data.size()); j++)
		{
			//j=0, 1, 2, 3, .... -> pdf, cdf, pl[0], pl[1], ....

			if (j == 1) continue;	//skip interpolation of

			int opt = eExtraporationConst;
			if (j == 0) opt = eExtraporationZero;		//pdf is zero outside of outgoing energy range

			if (j != 0)
			{
				//intepolation without considering weight of delta-E
				dwk0 = doInterporationFromVector(md0.intt, md0.eout, md0.data[j], eo0, opt);
				dwk1 = doInterporationFromVector(md1.intt, md1.eout, md1.data[j], eo1, opt);
				dwk = endfInterpolator2Point(intt, md0.ein, md1.ein, dwk0, dwk1, md.ein);
			}
			else
			{
				//intepolation with considering weight of delta-E
				dwk0 = doInterporationFromVector(md0.intt, md0.eout, md0.data[j], eo0, opt);
				dwk0 *= delta_eo0;
				dwk1 = doInterporationFromVector(md1.intt, md1.eout, md1.data[j], eo1, opt);
				dwk1 *= delta_eo1;
				dwk = endfInterpolator2Point(intt, md0.ein, md1.ein, dwk0, dwk1, md.ein);
				dwk /= delta_eo;
			}

			md.data[j][i] = dwk;
		}
	}
#if 0
	//recalculate pdf from interporated cdf .. not good accuracy
	if (md.intt == 1)
	{
		for (int i = 0; i < md.eout.size() - 1; i++)
			md.data[0][i] = (md.data[1][i + 1] - md.data[1][i]) / (md.eout[i + 1] - md.eout[i]) * 1.0e+6;
		md.data[0][md.np - 1] = 0.0;
	}
	else
	{
		md.data[0][0] = 0.0;
		for (int i = 1; i < md.eout.size(); i++)
		{
			md.data[0][i] = (md.data[1][i] - md.data[1][i-1])/(md.eout[i] - md.eout[i-1]) * 1.0e+6 * 2.0 - md.data[0][i-1];
		}
		md.data[0][md.np - 1] = 0.0;
	}
#endif
}
void FMACECrossSectionProcessor::doENDFInterporation(int intt, MCEData& md0, MCEData& md1, MCEData& md)
{
	vector<REAL> eoadd;

	for (int i = 0; i < static_cast<int>(md0.eout.size()); i++)
		eoadd.push_back(md0.eout[i]);
	for (int i = 0; i < static_cast<int>(md1.eout.size()); i++)
	{
		REAL eps = 1.0;
		for (int ii = 0; ii < static_cast<int>(md0.eout.size()); ii++)
		{
			REAL val;
			if (md0.eout[ii] != 0.0)
			{
				val = abs((md1.eout[i] - md0.eout[ii]) / md0.eout[ii]);
				if (val < eps) eps = val;
			}
			else
			{
				val = abs(md1.eout[i] - md0.eout[ii]);
				if (val < eps) eps = val;
			}
		}
		if (eps > 1.0e-6) eoadd.push_back(md1.eout[i]);
	}

	sort(eoadd.begin(), eoadd.end());
	md.eout.clear();
	for (int i = 0; i < static_cast<int>(eoadd.size()); i++)
	{
		md.eout.push_back(eoadd[i]);
	}

	md.np = md.eout.size();
	md.data.resize(md0.data.size());
	for (int i = 0; i < static_cast<int>(md0.data.size()); i++)
		md.data[i].resize(md.np);

	if (abs(md0.ein - md.ein) > abs(md1.ein - md.ein)) md.intt = md1.intt;
	else md.intt = md0.intt;

	for (int i = 0; i < static_cast<int>(md.eout.size()); i++)
	{
		REAL eo = md.eout[i];

		for (int ii = 0; ii < static_cast<int>(md.data.size()); ii++)
		{
			REAL dwk0 = doInterporationFromVector(md0.intt, md0.eout, md0.data[ii], eo, eExtraporationConst);
			REAL dwk1 = doInterporationFromVector(md1.intt, md1.eout, md1.data[ii], eo, eExtraporationConst);
			REAL dwk = endfInterpolator2Point(intt, md0.ein, md1.ein, dwk0, dwk1, md.ein);
			md.data[ii][i] = dwk;
		}
	}
}
void FMACECrossSectionProcessor::doEneAngDistInterporation(int intt, REAL ein0, REAL ein1, REAL ein, FMEneAngDist& eadist0, FMEneAngDist& eadist1, FMEneAngDist& eadist)
{
	for (int ie = 0; ie < eadist.max_ng; ie++)
	{
		eadist.pdf[ie] = endfInterpolator2Point(intt, ein0, ein1, eadist0.pdf[ie], eadist1.pdf[ie], ein);
		for (int il = 0; il <= eadist.max_pl; il++)
			eadist.pl_coef[ie][il] = endfInterpolator2Point(intt, ein0, ein1, eadist0.pl_coef[ie][il], eadist1.pl_coef[ie][il], ein);
	}
}
void FMACECrossSectionProcessor::convertMCEDataToAngDist(MCEData& md, FMEneAngDist& ed)
{
	vector<REAL> eb;
	eb.resize(ed.max_ng + 1);
	for (int i = 0; i <= ed.max_ng; i++)
		eb[i] = ed.ene_boundary[i];
	for (int i = 0; i < md.np; i++)
	{
		//if (md.eout_vec[i] > ed.ene_boundary.back() && md.eout_vec[i] < ed.ene_boundary[0])
		if (md.eout[i] > ed.ene_boundary.back())
				eb.push_back(md.eout[i]);
	}
	sort(eb.begin(), eb.end());

	vector<REAL> pl_coef(ed.max_pl + 1);
	for (int i = 0; i < static_cast<int>(eb.size()) - 1; i++)
	{
		REAL ene = (eb[i] + eb[i + 1]) / 2.0;
		int ii = getInterval(md.eout, ene, true);

		REAL val = endfInterpolator2Point(md.intt, md.eout[ii], md.eout[ii + 1], 
			md.data[0][ii], md.data[0][ii + 1], ene, eExtraporationZero);

		val *= (eb[i + 1] - eb[i]) * 1.0e-6;
		int ie;
#ifdef _FM_EXTEND_MAXIMUM_OUTGOING_ENERGY_FOR_LAW_
		if (ene >= ed.ene_boundary[0])
			ie = 0;
		else
			ie = ed.getEnergyGroup(ene);
#else
		if (ene >= ed.ene_boundary[0])
			continue;
		else
			ie = ed.getEnergyGroup(ene);
#endif
		ed.pdf[ie] += val;
		for (int il = 0; il <= ed.max_pl; il++)
		{
			pl_coef[il] = endfInterpolator2Point(md.intt, md.eout[ii], md.eout[ii + 1],
				md.data[2+il][ii], md.data[2 + il][ii+1], ene);
			if (pl_coef[0] != 0.0)
				ed.pl_coef[ie][il] += pl_coef[il] * val / pl_coef[0];
		}
	}
}
void FMACECrossSectionProcessor::convertAngDistToMCEData(int intt, REAL ein, FMEneAngDist& ed, MCEData& md)
{
	//check pdf of input data
	REAL sum = 0.0;
	for (int i = 0; i < ed.max_ng; i++)
		sum += ed.pdf[i];

	if (sum == 0.0)
	{
		md.data.clear();
		md.eout.clear();
		md.np = 0;
		return;
	}

	//convert to MCE data
	md.eout.clear();
	int ista = 0;
	int iend = ed.max_ng - 1;
	for (int i = 0; i < ed.max_ng; i++)
	{
		if (ed.pdf[i] != 0.0)
		{
			ista = i;
			break;
		}
	}
	for (int i = ed.max_ng-1; i >= 0; i--)
	{
		if (ed.pdf[i] != 0.0)
		{
			iend = i;
			break;
		}
	}

	md.eout.push_back(ed.ene_boundary[iend + 1]);
	for (int i = iend; i >= ista; i--)
	{
		md.eout.push_back(ed.ene_boundary[i]);
		REAL delta = ed.ene_boundary[i] - ed.ene_boundary[i+1];
		if (i != ista)
		{
			REAL val = md.eout.back();
			md.eout.push_back(val + delta * 1.0e-4);
		}
	}

	md.intt = intt;
	md.ein = ein;
	md.max_pl = ed.max_pl;
	md.np = (int)md.eout.size();
	md.data.resize(2 + ed.max_pl + 1);					//pdf, cdf, pl_coef
	for (int i = 0; i < (int) md.data.size(); i++)
	{
		md.data[i].resize(md.np);
		for (int ii = 0; ii < (int)md.data[i].size(); ii++)
			md.data[i][ii] = 0.0;
	}

	REAL cdf = 0.0;
	int j = 0;
	for (int i = iend; i >= ista; i--)
	{
		REAL delta_e = (md.eout[j+1] - md.eout[j]) * 1.0e-6; //in MeV
		REAL pdf = ed.pdf[i];
		md.data[0][j] = pdf / delta_e;
		md.data[0][j+1] = pdf / delta_e;
		md.data[1][j] = cdf;
		for (int il = 0; il <= ed.max_pl; il++)
			md.data[2 + il][j] = ed.pl_coef[i][il];
		cdf += pdf;
		md.data[1][j + 1] = cdf;
		for (int il = 0; il <= ed.max_pl; il++)
			md.data[2 + il][j + 1] = ed.pl_coef[i][il];

		j += 2;
	}

	//normalize cdf
	if (md.data[1].back() != 0.0)
	{
		REAL fact = 1.0 / md.data[1].back();
		for (int i = 0; i < (int)md.data[0].size(); i++)
		{
			md.data[0][i] *= fact;
			md.data[1][i] *= fact;
		}
	}
}
void FMACECrossSectionProcessor::calcPlCoefLaw44(int coord, REAL r, REAL a, int max_pl, vector<REAL>& pl_coef)
{

	int ndiv = MAX_MU_DIV;
	vector<REAL> mu_boundary, pdfwk, mulwk, delta_mul;
	mu_boundary.resize(ndiv + 1);
	pdfwk.resize(ndiv);
	mulwk.resize(ndiv);
	delta_mul.resize(ndiv);
	for (int i = 0; i <= ndiv; i++)
		mu_boundary[i] = (REAL)i*2.0 / (REAL)ndiv - 1.0;

	for (int i = 0; i < ndiv; i++)
	{
		//pdf interporation
		REAL wkmcl, wkmcave, wkmcu, wkmll, wkmlave, wkmlu;
		REAL wkp;
		if (coord == eCenterOfMassSystem)
		{
			wkmcl = mu_boundary[i];
			wkmcave = (mu_boundary[i] + mu_boundary[i + 1]) / 2.0;
			wkmcu = mu_boundary[i + 1];
			wkp = getKalbach87(wkmcave, r, a);
			wkp = convertCMtoLabPDF(wkp, wkmcave);
			wkmll = convertCMtoLabDirectionCosine(wkmcl);
			wkmlave = convertCMtoLabDirectionCosine(wkmcave);
			wkmlu = convertCMtoLabDirectionCosine(wkmcu);
		}
		else
		{
			wkmll = mu_boundary[i];
			wkmlave = (mu_boundary[i] + mu_boundary[i + 1]) / 2.0;
			wkmlu = mu_boundary[i + 1];
			wkp = getKalbach87(wkmlave, r, a);
		}
		mulwk[i] = wkmlave;
		pdfwk[i] = wkp;
		delta_mul[i] = wkmlu - wkmll;
	}

	//Legendre coefficients
	calcPlCoefficient(mulwk, delta_mul, pdfwk, pl_coef, max_pl);

}
void FMACECrossSectionProcessor::calcPlCoefLaw61(int coord, int offset, int max_pl, vector<REAL>& pl_coef)
{
	//int jj = rtoi(xss[offset]);
	int np = rtoi(xss[offset + 1]);
	vector<REAL> cs(np), pdf(np), cdf(np);
	for (int i = 0; i < np; i++)
		cs[i] = xss[offset + 2 + i];
	for (int i = 0; i < np; i++)
		pdf[i] = xss[offset + 2 + np + i];
	for (int i = 0; i < np; i++)
		cdf[i] = xss[offset + 2 + 2 * np + i];

	int ndiv = MAX_MU_DIV;
	vector<REAL> mu_boundary, pdflwk, pdfcwk, mulwk, delta_mul;
	mu_boundary.resize(ndiv + 1);
	pdflwk.resize(ndiv);
	pdfcwk.resize(ndiv);
	mulwk.resize(ndiv);
	delta_mul.resize(ndiv);
	for (int i = 0; i <= ndiv; i++)
		mu_boundary[i] = (REAL)i*2.0 / (REAL)ndiv - 1.0;

	for (int i = 0; i < ndiv; i++)
	{
		//pdf interporation
		REAL wkmcl, wkmcave, wkmcu, wkmll, wkmlave, wkmlu;
		REAL wkp;
		if (coord == eCenterOfMassSystem)
		{
			wkmcl = mu_boundary[i];
			wkmcave = (mu_boundary[i] + mu_boundary[i + 1]) / 2.0;
			wkmcu = mu_boundary[i + 1];
			wkp = interporatePdf(cs, pdf, wkmcave);
			pdfcwk[i] = wkp;
			wkp = convertCMtoLabPDF(wkp, wkmcave);
			wkmll = convertCMtoLabDirectionCosine(wkmcl);
			wkmlave = convertCMtoLabDirectionCosine(wkmcave);
			wkmlu = convertCMtoLabDirectionCosine(wkmcu);
		}
		else
		{
			wkmll = mu_boundary[i];
			wkmlave = (mu_boundary[i] + mu_boundary[i + 1]) / 2.0;
			wkmlu = mu_boundary[i + 1];
			wkp = interporatePdf(cs, pdf, wkmlave);
			pdfcwk[i] = 0.0;
		}
		mulwk[i] = wkmlave;
		pdflwk[i] = wkp;
		delta_mul[i] = wkmlu - wkmll;
	}

	//Legendre coefficients
	calcPlCoefficient(mulwk, delta_mul, pdflwk, pl_coef, max_pl);

}
REAL FMACECrossSectionProcessor::interpolatePdfLaw61(int offset, REAL mu, vector<vector<REAL> >& data)
{
	int jj = rtoi(xss[offset]);
	int np = rtoi(xss[offset + 1]);
	REAL val = interporatePdf(&xss[offset + 2], &xss[offset + 2 + np], np, mu, jj);

	return val;
}
void FMACECrossSectionProcessor::setUNRBlock()
{
	if (jxs[22] == 0) return;

	int offset = jxs[22] - 1;
	unr_data.n = rtoi(xss[offset++]);
	unr_data.m = rtoi(xss[offset++]);
	unr_data.intt = rtoi(xss[offset++]);
	unr_data.ilf = rtoi(xss[offset++]);
	unr_data.ioa = rtoi(xss[offset++]);
	unr_data.iff = rtoi(xss[offset++]);
	unr_data.ene_grid.resize(unr_data.n);
	for (int i = 0; i < unr_data.n; i++)
		unr_data.ene_grid[i] = xss[offset++] * 1.0e6;

	unr_data.p.resize(unr_data.n);
	for (int i = 0; i < unr_data.n; i++)
	{
		unr_data.p[i].resize(6);
		for (int j = 0; j < 6; j++)
			unr_data.p[i][j].resize(unr_data.m);
	}

	for (int i = 0; i < unr_data.n; i++)
		for (int j = 0; j < 6; j++)
			for (int k = 0; k < unr_data.m; k++)
				unr_data.p[i][j][k] = xss[offset++];

}
void FMACECrossSectionProcessor::getUNRParamter(REAL ein, vector<vector<REAL> >& uwk)
{
	int base = getInterval(unr_data.ene_grid, ein);
	REAL e0 = unr_data.ene_grid[base];
	REAL e1 = unr_data.ene_grid[base+1];
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < unr_data.m; j++)
		{
			uwk[i][j] = endfInterpolator2Point(unr_data.intt, e0, e1, unr_data.p[base][i][j], unr_data.p[base + 1][i][j],
				ein);
		}
	}

	//change cdf -> pdf
	vector<REAL> wk(unr_data.m);
	for (int j = 0; j < unr_data.m; j++)
		wk[j] = uwk[0][j];

	for (int j = 0; j < unr_data.m; j++)
	{
		if (j == 0)
			uwk[0][j] = wk[j];
		else
			uwk[0][j] = wk[j] - wk[j - 1];
	}
	REAL sum = 0.0;
	for (int j = 0; j < unr_data.m; j++)
		sum += uwk[0][j];
	for (int j = 0; j < unr_data.m; j++)
		uwk[0][j] /= sum;
}
void FMACECrossSectionProcessor::prepUnresolvedResonanceUFGXSFactor(REAL bg_xs_homo, vector<REAL>& _bg_xs, vector<string>& fname, vector<string>& output_data, string add_name_)
{
	//no unresolved resonance data
	if (isUNRData() == false) return;

	//set background cross section
	unr_bg_xs.clear();
	for (int i = 0; i < static_cast<int>(_bg_xs.size()); i++)
		unr_bg_xs.push_back(_bg_xs[i]);

	//set incident energy grid, which is equal to point-wise cross section in ACE file
	int _nes = getMaxNg();
	REAL e_upper = unr_data.ene_grid.back();
	REAL e_lower = unr_data.ene_grid[0];
	vector<REAL> unr_energy_grid;
	for (int ie = 0; ie < _nes; ie++)
	{
		REAL ein = getACEEnergyGrid(ie) * 1.0e+6;
		if (ein < e_lower || ein > e_upper) continue;
		if (unr_energy_grid.size() == 0) unr_ie_upper_group = ie;
		unr_ie_lower_group = ie;
		unr_energy_grid.push_back(ein);
	}

	//allocate array
	int max_ene_grid = unr_energy_grid.size();
	unr_eff_xs_factor.resize(unr_bg_xs.size());
	for (int i = 0; i < static_cast<int>(unr_bg_xs.size()); i++)
	{
		unr_eff_xs_factor[i].resize(6);
		for (int j = 0; j < 6; j++)
		{
			unr_eff_xs_factor[i][j].resize(max_ene_grid);
			for (int ie = 0; ie < max_ene_grid; ie++)
				unr_eff_xs_factor[i][j][ie] = 0.0;
		}
	}

	//cout << setw(20) << getZaid() << " unresoved cross section : number of energy points " << setw(4) << max_ene_grid << endl;

	//effective cross sections for various back ground cross sections
	for (int ib = 0; ib < static_cast<int>(unr_bg_xs.size()); ib++)
	{
		for (int ie = 0; ie < static_cast<int>(unr_energy_grid.size()); ie++)
		{
			//incident energy
			REAL ein = unr_energy_grid[ie];

			//calculate effective cross sections
			REAL sigt_fw = 0.0;
			REAL sigt_cw = 0.0;
			REAL sigs = 0.0;
			REAL sigf = 0.0;
			REAL sigc = 0.0;
			REAL heat = 0.0;
			REAL flux = 0.0;
			REAL curr = 0.0;

			vector<vector<REAL> > uwk;
			uwk.resize(6);
			for (int ii = 0; ii < 6; ii++)
				uwk[ii].resize(unr_data.m);
			getUNRParamter(ein, uwk);

			//infinite dilute cross sections
			REAL sigt_xs = getXS(eMTTotal, ein);
			REAL sigs_xs = getXS(eMTElasticScattering, ein);
			REAL sigf_xs = getFissionXS(ein);
			REAL sigc_xs = getXS(eMTNGamma, ein);
			REAL heat_xs = getXS(eMTHeating, ein);
			REAL sigs_xs_add = 0.0;
			REAL sigc_xs_add = 0.0;

#ifdef _FM_USE_ILF_UNR_
			if (unr_data.ilf >= 0)
			{
				if (unr_data.ilf > 0)
					sigs_xs_add = getXS(unr_data.ilf, ein);
				else
				{
					// sum of all inelastic scattering
					for (int mt = eMTInelasticScatteringBegin; mt <= eMTInelasticScatteringEnd; mt++)
					{
						if (isMT(mt))
							sigs_xs_add += getXS(mt, ein);
					}
				}
			}
#endif
#ifdef _FM_USE_IOA_UNR_
			if (unr_data.ioa >= 0)
			{
				if (unr_data.ioa > 0)
					sigc_xs_add = getXS(unr_data.ioa, ein);
				else
				{
					// sum of all absorption except for fission
					for (int mt = 102; mt <= 117; mt++)
					{
						if (isMT(mt))
							sigc_xs_add += getXS(mt, ein);
					}
				}
			}
#endif

			for (int k = 0; k < unr_data.m; k++)
			{
				REAL val;
				REAL bgxs = unr_bg_xs[ib] + bg_xs_homo;
				if (unr_data.iff == 0)
					val = bgxs + uwk[1][k];
				else
					val = bgxs + uwk[1][k] * sigt_xs;
				REAL band_flux = uwk[0][k] / val;
				REAL band_current = uwk[0][k] / (val*val);
				sigt_fw += band_flux    * uwk[1][k];
				sigt_cw += band_current * uwk[1][k];
				sigs += band_flux * uwk[2][k];
				sigf += band_flux * uwk[3][k];
				sigc += band_flux * uwk[4][k];
				heat += band_flux * uwk[5][k];
				flux += band_flux;
				curr += band_current;
			}
			sigt_fw /= flux;
			sigt_cw /= curr;
			sigs /= flux;
			sigf /= flux;
			sigc /= flux;
			heat /= flux;

			// convert to factor when iff = 0
			if (unr_data.iff == 0)
			{
				if (sigt_xs != 0.0)
				{
					sigt_fw /= sigt_xs;
					sigt_cw /= sigt_xs;
				}
				if ((sigs_xs + sigs_xs_add) != 0.0)
					sigs /= (sigs_xs + sigs_xs_add);
				if (sigf_xs != 0.0)
					sigf /= sigf_xs;
				if ((sigc_xs + sigc_xs_add) != 0.0)
					sigc /= (sigc_xs + sigc_xs_add);
				if (heat_xs != 0.0)
					heat /= heat_xs;
			}
			unr_eff_xs_factor[ib][0][ie] = sigt_fw;
			unr_eff_xs_factor[ib][1][ie] = sigs;
			unr_eff_xs_factor[ib][2][ie] = sigf;
			unr_eff_xs_factor[ib][3][ie] = sigc;
			unr_eff_xs_factor[ib][4][ie] = heat;
			unr_eff_xs_factor[ib][5][ie] = sigt_cw;
		}
	}

	//normalize for infinite dilute cross sections
	for (int ib = unr_bg_xs.size() - 1; ib >= 0; ib--)
	{
		for (int ie = 0; ie < static_cast<int>(unr_energy_grid.size()); ie++)
		{
			for (int i = 0; i < 6; i++)
			{
				if (unr_eff_xs_factor[0][i][ie] != 0.0)
					unr_eff_xs_factor[ib][i][ie] = unr_eff_xs_factor[ib][i][ie] / unr_eff_xs_factor[0][i][ie];
			}
		}
	}

#if 0
	string zaid = getZaid();
	string file_name = "FMUnresolvedXSFactor_" + add_name_ + zaid + "_.txt";
	fname.push_back(file_name);
	stringstream of;

	of << "  IFF (if ==0 cross section, ==1 factors)                       " << unr_data.iff << endl;
	of << "  ILF (if >=0 scattering contains inelastic)                    " << unr_data.ilf << endl;
	of << "  IOA (if >=0 capture contains absorption other than fission)   " << unr_data.ioa << endl;
	of << endl;

	of << "         Total  (P0 weight)" << endl;
	of << setw(10) << " No. gr.";
	of << setw(15) << " Energy[eV]";
	for (int ib = 0; ib < unr_bg_xs.size(); ib++)
		of << setw(15) << setprecision(6) << scientific << unr_bg_xs[ib];
	of << endl;
	of << setw(25) << " ";
	for (int ib = 0; ib < unr_bg_xs.size(); ib++)
		of << setw(15) << setprecision(6) << scientific << unr_bg_xs[ib]+bg_xs_homo;
	of << endl;
	for (int ie = 0; ie < max_ene_grid; ie++)
	{
		of << setw(10) << ie;
		of << setw(15) << setprecision(6) << scientific << unr_energy_grid[ie];
		for (int ib = 0; ib < unr_bg_xs.size(); ib++)
			of << setw(15) << setprecision(6) << scientific << unr_eff_xs_factor[ib][0][ie];
		of << endl;
	}
	of << endl;

	of << "         Total  (P1 weight)" << endl;
	of << setw(10) << " No. gr.";
	of << setw(15) << " Energy[eV]";
	for (int ib = 0; ib < unr_bg_xs.size(); ib++)
		of << setw(15) << setprecision(6) << scientific << unr_bg_xs[ib];
	of << endl;
	of << setw(25) << " ";
	for (int ib = 0; ib < unr_bg_xs.size(); ib++)
		of << setw(15) << setprecision(6) << scientific << unr_bg_xs[ib] + bg_xs_homo;
	of << endl;
	for (int ie = 0; ie < max_ene_grid; ie++)
	{
		of << setw(10) << ie;
		of << setw(15) << setprecision(6) << scientific << unr_energy_grid[ie];
		for (int ib = 0; ib < unr_bg_xs.size(); ib++)
			of << setw(15) << setprecision(6) << scientific << unr_eff_xs_factor[ib][5][ie];
		of << endl;
	}
	of << endl;

	of << "         Scattering  " << endl;
	of << setw(10) << " No. gr.";
	of << setw(15) << " Energy[eV]";
	for (int ib = 0; ib < unr_bg_xs.size(); ib++)
		of << setw(15) << setprecision(6) << scientific << unr_bg_xs[ib];
	of << endl;
	of << setw(25) << " ";
	for (int ib = 0; ib < unr_bg_xs.size(); ib++)
		of << setw(15) << setprecision(6) << scientific << unr_bg_xs[ib] + bg_xs_homo;
	of << endl;
	for (int ie = 0; ie < max_ene_grid; ie++)
	{
		of << setw(10) << ie;
		of << setw(15) << setprecision(6) << scientific << unr_energy_grid[ie];
		for (int ib = 0; ib < unr_bg_xs.size(); ib++)
			of << setw(15) << setprecision(6) << scientific << unr_eff_xs_factor[ib][1][ie];
		of << endl;
	}
	of << endl;

	of << "         Fission  " << endl;
	of << setw(10) << " No. gr.";
	of << setw(15) << " Energy[eV]";
	for (int ib = 0; ib < unr_bg_xs.size(); ib++)
		of << setw(15) << setprecision(6) << scientific << unr_bg_xs[ib];
	of << endl;
	of << setw(25) << " ";
	for (int ib = 0; ib < unr_bg_xs.size(); ib++)
		of << setw(15) << setprecision(6) << scientific << unr_bg_xs[ib] + bg_xs_homo;
	of << endl;
	for (int ie = 0; ie < max_ene_grid; ie++)
	{
		of << setw(10) << ie;
		of << setw(15) << setprecision(6) << scientific << unr_energy_grid[ie];
		for (int ib = 0; ib < unr_bg_xs.size(); ib++)
			of << setw(15) << setprecision(6) << scientific << unr_eff_xs_factor[ib][2][ie];
		of << endl;
	}
	of << endl;

	of << "         Capture  " << endl;
	of << setw(10) << " No. gr.";
	of << setw(15) << " Energy[eV]";
	for (int ib = 0; ib < unr_bg_xs.size(); ib++)
		of << setw(15) << setprecision(6) << scientific << unr_bg_xs[ib];
	of << endl;
	of << setw(25) << " ";
	for (int ib = 0; ib < unr_bg_xs.size(); ib++)
		of << setw(15) << setprecision(6) << scientific << unr_bg_xs[ib] + bg_xs_homo;
	of << endl;
	for (int ie = 0; ie < max_ene_grid; ie++)
	{
		of << setw(10) << ie;
		of << setw(15) << setprecision(6) << scientific << unr_energy_grid[ie];
		for (int ib = 0; ib < unr_bg_xs.size(); ib++)
			of << setw(15) << setprecision(6) << scientific << unr_eff_xs_factor[ib][3][ie];
		of << endl;
	}
	of << endl;

	of << "         Heating  " << endl;
	of << setw(10) << " No. gr.";
	of << setw(15) << " Energy[eV]";
	for (int ib = 0; ib < unr_bg_xs.size(); ib++)
		of << setw(15) << setprecision(6) << scientific << unr_bg_xs[ib];
	of << endl;
	of << setw(25) << " ";
	for (int ib = 0; ib < unr_bg_xs.size(); ib++)
		of << setw(15) << setprecision(6) << scientific << unr_bg_xs[ib] + bg_xs_homo;
	of << endl;
	for (int ie = 0; ie < max_ene_grid; ie++)
	{
		of << setw(10) << ie;
		of << setw(15) << setprecision(6) << scientific << unr_energy_grid[ie];
		for (int ib = 0; ib < unr_bg_xs.size(); ib++)
			of << setw(15) << setprecision(6) << scientific << unr_eff_xs_factor[ib][4][ie];
		of << endl;
	}
	of << endl;
	output_data.push_back(of.str());

	file_name = "FMUnresolvedXS_" + add_name_ + zaid + "_.txt";
	fname.push_back(file_name);

	of.str("");
	of.clear();

	of << "  IFF (if ==0 cross section, ==1 factors)                       " << unr_data.iff << endl;
	of << "  ILF (if >=0 scattering contains inelastic)                    " << unr_data.ilf << endl;
	of << "  IOA (if >=0 capture contains absorption other than fission)   " << unr_data.ioa << endl;
	of << endl;

	of << "         Total  (P0 weight)" << endl;
	of << setw(10) << " No. gr.";
	of << setw(15) << " Energy[eV]";
	for (int ib = 0; ib < unr_bg_xs.size(); ib++)
		of << setw(15) << setprecision(6) << scientific << unr_bg_xs[ib];
	of << endl;
	of << setw(25) << " ";
	for (int ib = 0; ib < unr_bg_xs.size(); ib++)
		of << setw(15) << setprecision(6) << scientific << unr_bg_xs[ib] + bg_xs_homo;
	of << endl;
	for (int ie = 0; ie < max_ene_grid; ie++)
	{
		REAL ein = unr_energy_grid[ie];
		REAL sigt_xs = getXS(eMTTotal, ein);
		of << setw(10) << ie;
		of << setw(15) << setprecision(6) << scientific << unr_energy_grid[ie];
		for (int ib = 0; ib < unr_bg_xs.size(); ib++)
			of << setw(15) << setprecision(6) << scientific << unr_eff_xs_factor[ib][0][ie] * sigt_xs;
		of << endl;
	}
	of << endl;

	of << "         Total  (P1 weight)" << endl;
	of << setw(10) << " No. gr.";
	of << setw(15) << " Energy[eV]";
	for (int ib = 0; ib < unr_bg_xs.size(); ib++)
		of << setw(15) << setprecision(6) << scientific << unr_bg_xs[ib];
	of << endl;
	of << setw(25) << " ";
	for (int ib = 0; ib < unr_bg_xs.size(); ib++)
		of << setw(15) << setprecision(6) << scientific << unr_bg_xs[ib] + bg_xs_homo;
	of << endl;
	for (int ie = 0; ie < max_ene_grid; ie++)
	{
		REAL ein = unr_energy_grid[ie];
		REAL sigt_xs = getXS(eMTTotal, ein);
		of << setw(10) << ie;
		of << setw(15) << setprecision(6) << scientific << unr_energy_grid[ie];
		for (int ib = 0; ib < unr_bg_xs.size(); ib++)
			of << setw(15) << setprecision(6) << scientific << unr_eff_xs_factor[ib][5][ie] * sigt_xs;
		of << endl;
	}
	of << endl;

	of << "         Scattering  " << endl;
	of << setw(10) << " No. gr.";
	of << setw(15) << " Energy[eV]";
	for (int ib = 0; ib < unr_bg_xs.size(); ib++)
		of << setw(15) << setprecision(6) << scientific << unr_bg_xs[ib];
	of << endl;
	of << setw(25) << " ";
	for (int ib = 0; ib < unr_bg_xs.size(); ib++)
		of << setw(15) << setprecision(6) << scientific << unr_bg_xs[ib] + bg_xs_homo;
	of << endl;
	for (int ie = 0; ie < max_ene_grid; ie++)
	{
		REAL ein = unr_energy_grid[ie];
		REAL sigs_xs = getXS(eMTElasticScattering, ein);
		of << setw(10) << ie;
		of << setw(15) << setprecision(6) << scientific << unr_energy_grid[ie];
		for (int ib = 0; ib < unr_bg_xs.size(); ib++)
			of << setw(15) << setprecision(6) << scientific << unr_eff_xs_factor[ib][1][ie] * sigs_xs;
		of << endl;
	}
	of << endl;

	of << "         Fission  " << endl;
	of << setw(10) << " No. gr.";
	of << setw(15) << " Energy[eV]";
	for (int ib = 0; ib < unr_bg_xs.size(); ib++)
		of << setw(15) << setprecision(6) << scientific << unr_bg_xs[ib];
	of << endl;
	of << setw(25) << " ";
	for (int ib = 0; ib < unr_bg_xs.size(); ib++)
		of << setw(15) << setprecision(6) << scientific << unr_bg_xs[ib] + bg_xs_homo;
	of << endl;
	for (int ie = 0; ie < max_ene_grid; ie++)
	{
		REAL ein = unr_energy_grid[ie];
		REAL sigf_xs = getFissionXS(ein);
		of << setw(10) << ie;
		of << setw(15) << setprecision(6) << scientific << unr_energy_grid[ie];
		for (int ib = 0; ib < unr_bg_xs.size(); ib++)
			of << setw(15) << setprecision(6) << scientific << unr_eff_xs_factor[ib][2][ie] * sigf_xs;
		of << endl;
	}
	of << endl;

	of << "         Capture  " << endl;
	of << setw(10) << " No. gr.";
	of << setw(15) << " Energy[eV]";
	for (int ib = 0; ib < unr_bg_xs.size(); ib++)
		of << setw(15) << setprecision(6) << scientific << unr_bg_xs[ib];
	of << endl;
	of << setw(25) << " ";
	for (int ib = 0; ib < unr_bg_xs.size(); ib++)
		of << setw(15) << setprecision(6) << scientific << unr_bg_xs[ib] + bg_xs_homo;
	of << endl;
	for (int ie = 0; ie < max_ene_grid; ie++)
	{
		REAL ein = unr_energy_grid[ie];
		REAL sigc_xs = getXS(eMTNGamma, ein);
		of << setw(10) << ie;
		of << setw(15) << setprecision(6) << scientific << unr_energy_grid[ie];
		for (int ib = 0; ib < unr_bg_xs.size(); ib++)
			of << setw(15) << setprecision(6) << scientific << unr_eff_xs_factor[ib][3][ie] * sigc_xs;
		of << endl;
	}
	of << endl;

	of << "         Heating  " << endl;
	of << setw(10) << " No. gr.";
	of << setw(15) << " Energy[eV]";
	for (int ib = 0; ib < unr_bg_xs.size(); ib++)
		of << setw(15) << setprecision(6) << scientific << unr_bg_xs[ib];
	of << endl;
	of << setw(25) << " ";
	for (int ib = 0; ib < unr_bg_xs.size(); ib++)
		of << setw(15) << setprecision(6) << scientific << unr_bg_xs[ib] + bg_xs_homo;
	of << endl;
	for (int ie = 0; ie < max_ene_grid; ie++)
	{
		REAL ein = unr_energy_grid[ie];
		REAL heat_xs = getXS(eMTHeating, ein);
		of << setw(10) << ie;
		of << setw(15) << setprecision(6) << scientific << unr_energy_grid[ie];
		for (int ib = 0; ib < unr_bg_xs.size(); ib++)
			of << setw(15) << setprecision(6) << scientific << unr_eff_xs_factor[ib][4][ie] * heat_xs;
		of << endl;
	}
	of << endl;

	output_data.push_back(of.str());
#endif

}
REAL FMACECrossSectionProcessor::getUNRSelfShielingFactor(int mt, REAL ene, REAL bgxs)
{
	//is there UNR data?
	if (isUNRData() == false) return 1.0;

	if (ene > ene_grid[0] || ene < ene_grid[nes - 1])
		return 1.0;
	REAL e_upper = unr_data.ene_grid.back();
	REAL e_lower = unr_data.ene_grid[0];
	if (ene > e_upper || ene < e_lower)
		return 1.0;

	//lookup
	for (;;)
	{
		REAL val = 0.0;
		if (ene <= ene_grid[current] && ene >= ene_grid[current + 1])
		{
			REAL y0 = getUNRSelfShielingFactor(mt, current, bgxs);
			REAL y1 = getUNRSelfShielingFactor(mt, current + 1, bgxs);
			REAL x0 = ene_grid[current];
			REAL x1 = ene_grid[current + 1];
			val = (y1 - y0) / (x1 - x0) * (ene - x0) + y0;
			return val;
		}
		else if (ene > ene_grid[current])
		{
			current--;
			if (current < 0)
			{
				cout << " out of range " << endl;
				exit(0);
			}
		}
		else
		{
			current++;
			if (current >= nes - 1)
			{
				cout << " out of range " << endl;
				exit(0);
			}
		}
	}
}

REAL FMACECrossSectionProcessor::getUNRSelfShielingFactor(int mt, int ie, REAL bgxs)
{
	//is there UNR data?
	if (isUNRData() == false) return 1.0;
	if (unr_bg_xs.size() == 0) return 1.0;

	//infinite dilution?
	REAL bgxs_inf = unr_bg_xs[0] * (1.0 - 1.0e-6);
	if (bgxs >= bgxs_inf) return 1.0;

	//unresolved energy range?
	if (ie > unr_ie_lower_group || ie < unr_ie_upper_group) return 1.0;

	//get self shielding factor
	int ib = -1;
	if (bgxs == 0.0)
	{
		if (unr_bg_xs.back() == 0.0)
			ib = unr_bg_xs.size() - 1;
	}
	for (int i = 0; i < static_cast<int>(unr_bg_xs.size()); i++)
	{
		REAL diff = abs(bgxs - unr_bg_xs[i]) / bgxs;
		if (diff < 1.0e-5)
		{
			ib = i;
			break;
		}
	}
	if (ib < 0)
	{
		cout << " specified background xs does not exist " << bgxs << endl;
		exit(0);
	}

	int index = ie - unr_ie_upper_group;

	if (mt == eMTTotal)
	{
		return unr_eff_xs_factor[ib][0][index];
	}
	else if (mt == eMTTotalCurrentWeight)
	{
		return unr_eff_xs_factor[ib][5][index];
	}
	else if (mt == eMTDisappearance)
	{
#if 1
		cout << " cannot treat this mt in FMACECrossSectionProcessor::getUNRSelfShielingFactor " << mt << endl;
		exit(0);
#else
		return 1.0;
#endif
	}
	else if (mt == eMTElasticScattering)
	{
		return unr_eff_xs_factor[ib][1][index];
	}
	else if (mt == eMTFission)
	{
		return unr_eff_xs_factor[ib][2][index];
	}
	else if (mt == eMTFirstChanceFission)
	{
		return unr_eff_xs_factor[ib][2][index];
	}
	else if (mt == eMTSecondChanceFission)
	{
		return unr_eff_xs_factor[ib][2][index];
	}
	else if (mt == eMTThirdChanceFission)
	{
		return unr_eff_xs_factor[ib][2][index];
	}
	else if (mt == eMTFourthChanceFission)
	{
		return unr_eff_xs_factor[ib][2][index];
	}
	else if (mt == eMTNGamma)
	{
		return unr_eff_xs_factor[ib][3][index];
	}
	else if (mt == eMTHeating)
	{
		return unr_eff_xs_factor[ib][4][index];
	}

#if 0
	//do not self shield to inelastic scattering and other absorptions except for capture
	if (unr_data.ilf >= 0)
	{
		if (unr_data.ilf > 0)
		{
			// includes particular inelastic scattering
			if (mt == unr_data.ilf)
			{
				return unr_eff_xs_factor[ib][1][index];
			}
			else if (unr_data.ilf == eMTInelasticScatteringTotal && (mt >= eMTInelasticScatteringBegin && mt <= eMTInelasticScatteringEnd))
			{
				return unr_eff_xs_factor[ib][1][index];
			}
		}
		else
		{
			// includes all inelastic scattering
			if (mt >= eMTInelasticScatteringBegin && mt <= eMTInelasticScatteringEnd)
			{
				return unr_eff_xs_factor[ib][1][index];
			}
		}
	}
	if (unr_data.ioa >= 0)
	{
		if (unr_data.ioa > 0)
		{
			// includes particular absorption
			if (mt == unr_data.ioa)
			{
				return unr_eff_xs_factor[ib][3][index];
			}
			else if (unr_data.ioa == eMTDisappearance && (mt >= 102 && mt <= 117))
			{
				return unr_eff_xs_factor[ib][3][index];
			}
		}
		else
		{
			// includes all absorption
			if (mt >= 102 && mt <= 117)
			{
				return unr_eff_xs_factor[ib][3][index];
			}
		}
	}
#endif

	return 1.0;
}
void FMACECrossSectionProcessor::report(string fname)
{
	ofstream of;
	of.open(fname.c_str());

	of.close();
}
