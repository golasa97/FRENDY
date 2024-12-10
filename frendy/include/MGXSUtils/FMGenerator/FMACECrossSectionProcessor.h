//-----------------------------------------------------
// FMACECrossSectionProcessor.h : process ACE files 
//        
//-----------------------------------------------------

#pragma once
#include "MGXSUtils/FMGenerator/FMGenerator_global.h"
#include "MGXSUtils/FMGenerator/FMEneAngDist.h"
#include "MGXSUtils/FMGenerator/FMZlib.h"
#include "MGXSUtils/FMGenerator/FMPrinter.h"

namespace FMGen
{
	enum NuValueType
	{
		eNuTotal,
		eNuPrompt,
		eNuDelayed
	};
	struct DLW
	{
		int lnw;
		int law;
		int idat;
		int nr;
		vector<int> nbtt;
		vector<int> intt;
		int ne;
		vector<REAL> etab;
		vector<REAL> ptab;
		vector<REAL> ldat;
		REAL	dec;	//decay constant for delayed neutron

		int nr_ed;		//energy dependent neutron yields
		vector<int> nbtt_ed;
		vector<int> intt_ed;
		int ne_ed;
		vector<REAL> etab_ed;
		vector<REAL> ytab;

		void clear()
		{
			lnw = 0;
			law = 0;
			idat = 0;
			nr = 0;
			nbtt.clear();
			intt.clear();
			ne = 0;
			etab.clear();
			ptab.clear();
			ldat.clear();
			dec = 0.0;

			nr_ed = 0;
			nbtt_ed.clear();
			intt_ed.clear();
			ne_ed = 0;
			etab_ed.clear();
			ytab.clear();
		};
	};
	struct MCEData
	{
		int intt;
		REAL ein;
		int np;
		int max_pl;
		vector<REAL> eout;
		vector<vector<REAL> > data;		//data types (pdf, cdf, pl_coef)  
	};
	struct UNRData
	{
		int n;
		int m;
		int intt;
		int ilf;
		int ioa;
		int iff;
		vector<REAL> ene_grid;
		vector<vector<vector<REAL> > > p;
		void clear()
		{
			n = 0;
			m = 0;
			intt = 0;
			ilf = 0;
			ene_grid.clear();
			for (int i = 0; i < static_cast<int>(p.size()); i++)
				for (int j = 0; j < static_cast<int>(p[i].size()); j++)
					p[i][j].clear();
		};
	};

	class FMACECrossSectionProcessor
	{
	private:
		//ACE data
		vector<string>		title;
		vector<int>			izaw;
		vector<int>			nxs;
		vector<int>			jxs;
		vector<REAL>		xss;

		//processed data from ace
		vector<int>			mt_values;			//mt in ACE
		vector<int>			mt_values_angular;	//mt with angular distribution
		vector<int>			lsig;				//location of xs
		vector<int>			land;				//location of angular distribution
		map<int, vector<REAL> >				angular_dist_egrid;	//angular distribution (incident energy grid)
		map<int, vector<vector<REAL> > >	angular_dist_pdf;	//angular distribution (pdf)
		map<int, vector<REAL> >				angular_dist_mu;	//angular distribution (mu)
		map<int, int>						angular_dist_locb;	//angular distribution (locb)
		map<int, vector<DLW> >	dlw;			//energy (or energy-angle) distribution
		map<int, vector<DLW> >	dlw_delayed;	//DLW for delayed neutrons
		map<int, MCEData>		mcedata_temporary;		//temporary storage for MCEData
		map<int, FMEneAngDist>	eaddata_temporary;		//temporary storage for EneAngDist
		map<int, DLW>		delayed_precursor_distribution;	//delayed neutron ratio
		vector<REAL>		nu_total;						//nu-total in unified energy grid
		vector<REAL>		nu_delayed;						//nu-delayed in unified energy grid
		UNRData				unr_data;						//unresolved xs data
		vector<REAL>		unr_bg_xs;						//background cross section for unresolved xs
		vector<vector<vector<REAL> > >	unr_eff_xs_factor;	//unresolved xs shielding factor table [ib][0:5][ie]
		int					unr_ie_upper_group;
		int					unr_ie_lower_group;

		int		nes;		// number of energy groupes
		int		ntr;		// number of reactions excluding elastic scattering
		int		nr;			// number of reactions having secondary neutrons excluding elastic scattering
		int		za;			// nuclide id
		int		current;	// current position for search xs
		string	zaid;		// nuclide zaid
		REAL	temp_kelvin;// temperature in [K]
		REAL	aw;			// target nuclide mass relative to a neutron
		string	file_name;	// ACE file name

		vector<REAL>		ene_grid;	// unifie energy grid

	public:

		FMACECrossSectionProcessor()
		{
			clear();
		}
		~FMACECrossSectionProcessor()
		{
			clear();
		}
		void clear()
		{
			title.clear();
			izaw.clear();
			nxs.clear();
			jxs.clear();
			xss.clear();
			mt_values.clear();
			mt_values_angular.clear();
			lsig.clear();
			land.clear();
			angular_dist_egrid.clear();
			angular_dist_pdf.clear();
			angular_dist_mu.clear();
			angular_dist_locb.clear();
			dlw.clear();
			dlw_delayed.clear();
			mcedata_temporary.clear();
			eaddata_temporary.clear();
			nu_total.clear();
			nu_delayed.clear();
			delayed_precursor_distribution.clear();
			file_name.clear();
			ene_grid.clear();
			unr_data.clear();
			unr_bg_xs.clear();
			for (int i = 0; i < static_cast<int>(unr_eff_xs_factor.size()); i++)
				for (int j = 0; j < static_cast<int>(unr_eff_xs_factor[i].size()); j++)
					unr_eff_xs_factor[i][j].clear();
			nes = 0;
			ntr = 0;
			nr = 0;
			za = 0;
			current = 0;
			zaid.clear();
			aw = 0.0;
			temp_kelvin = 0.0;
			unr_ie_upper_group = 0;
			unr_ie_lower_group = 0;
		}

		//set ace data
		void setACEData(vector<string>& _title, vector<int>& _izaw, vector<int>& _nxs, vector<int>& _jxs,
			vector<REAL>& _xss)
		{
			//used for interface between FRENDY
			// acexs.setACEData( .... );
			// acexs.processHeaderData();
			// acexs.processXSData();
			// acexs.getDLW();

			title.resize(_title.size());
			for (int i = 0; i < static_cast<int>(_title.size()); i++)
				title[i] = _title[i];

			izaw.resize(_izaw.size());
			for (int i = 0; i < static_cast<int>(_izaw.size()); i++)
				izaw[i] = _izaw[i];

			nxs.resize(_nxs.size());
			for (int i = 0; i < static_cast<int>(_nxs.size()); i++)
				nxs[i] = _nxs[i];

			jxs.resize(_jxs.size());
			for (int i = 0; i < static_cast<int>(_jxs.size()); i++)
				jxs[i] = _jxs[i];

			xss.resize(_xss.size());
			for (int i = 0; i < static_cast<int>(_xss.size()); i++)
				xss[i] = _xss[i];

		}
		void readHeaderData(string fname);
		void processHeaderData();
		void readXSData();
		void processXSData();
		void setNuData(int offset, vector<REAL>& nu);

		//get various data
		REAL getACEEnergyGrid(int ie)
		{
			int iwk = nes - 1 - ie;
			return xss[iwk];
		}
		REAL getPointwiseEnergy(int i)
		{
			return ene_grid[i];
		}
		REAL getKelvin()
		{
			return temp_kelvin;
		}
		int getMaxNg()
		{
			return nes;
		}
		int getZa()
		{
			return za;
		}
		string getZaid()
		{
			return zaid;
		}
		REAL getAW()
		{
			return aw;
		}

		REAL getNu(int type, REAL ene);
		REAL getNuTotal(int ie)
		{
			return nu_total[ie];
		}
		REAL getNuDelayed(int ie)
		{
			return nu_delayed[ie];
		}
		int getNumDelayedNeutronGroups()
		{
			return nxs[7];
		}

		REAL getXS(int type, REAL ene, REAL bgxs = 1.0e+10);
		REAL getFissionXS(REAL ene, REAL bgxs = 1.0e+10);
		REAL getXS(int mt, int ie, REAL bgxs)
		{
			REAL unr_factor = 1.0;
			
			unr_factor = getUNRSelfShielingFactor(mt, ie, bgxs);

			if (mt == eMTTotal || mt == eMTTotalCurrentWeight)
			{
				int iwk = nes - 1 - ie;
				REAL val = unr_factor * xss[nes + iwk];
				return val;
			}
			else if (mt == eMTDisappearance)
			{
				int iwk = nes - 1 - ie;
				REAL val = unr_factor * xss[2 * nes + iwk];
				return val;
			}
			else if (mt == eMTElasticScattering)
			{
				int iwk = nes - 1 - ie;
				REAL val = unr_factor * xss[3 * nes + iwk];
				return val;
			}
			else if (mt == eMTHeating)
			{
				int iwk = nes - 1 - ie;
				REAL val = unr_factor * xss[4 * nes + iwk];
				val *= 1.0e+6;		//MeV -> eV
				return val;
			}

			int iwk = nes - 1 - ie;
			int sta, iee, nee;
			int offset = jxs[6] - 1;
			for (int i = 0; i < ntr; i++)
			{
				if (mt != mt_values[i]) continue;
				sta = offset + lsig[i] - 1;
				iee = (int)(xss[sta] + 0.1) - 1;
				nee = (int)(xss[sta + 1] + 0.1);
				if (iwk < iee) return 0.0;
				if (iwk >= iee + nee) return 0.0;
				REAL val = unr_factor * xss[sta + 2 + iwk - iee];
				if (mt == eMTKerma) val *= 1.0E+6; //MeV -> eV
				if (mt == eMTDamage) val *= 1.0E+6; //MeV -> eV
				return val;
			}
			cout << " MT not found " << mt << endl;
			exit(0);
		}

		REAL getUNRSelfShielingFactor(int mt, REAL ene, REAL bgxs);
		REAL getUNRSelfShielingFactor(int mt, int ie, REAL bgxs);
		void getUNREnergyRange(REAL& unr_upper, REAL& unr_lower)
		{
			unr_upper = 0.0;
			unr_lower = 0.0;
			if (isUNRData() == false) return;

			unr_lower = unr_data.ene_grid[0];
			unr_upper = unr_data.ene_grid.back();

			return;
		}
		REAL getQValue(int mt)
		{
			if (mt == eMTElasticScattering) return 0.0;

			for (int i = 0; i < ntr; i++)
			{
				if (mt_values[i] != mt) continue;
				int offset = jxs[3] - 1;
				return xss[offset + i];
			}
			cout << " QValue not found. mt=" << mt << endl;
			cout << " QValue is set to zero. " << endl;
			return 0.0;
		}
		int getTYValue(int mt)
		{
			if (mt == eMTElasticScattering) return 1;

			for (int i = 0; i < ntr; i++)
			{
				if (mt_values[i] != mt) continue;
				int offset = jxs[4] - 1;
				int ty = rtoi(xss[offset + i]);
				return ty;
			}

			return 0;
		}
		REAL getEnergyDependentNeutronYieldInDLW(int mt, REAL ein)
		{
			if (dlw.find(mt) == dlw.end()) return 0.0;

			if (dlw[mt][0].ne_ed == 0) return 0.0;

			ein *= 1.0e-6;	//eV -> MeV

			REAL val = endfInterpolator(dlw[mt][0].nr_ed, dlw[mt][0].nbtt_ed, dlw[mt][0].intt_ed, dlw[mt][0].etab_ed, dlw[mt][0].ytab, ein);

			return val;
		}
		void getMtValues(vector<int>& _mt_values)
		{
			_mt_values.clear();
			_mt_values.resize(mt_values.size());
			for (int i = 0; i < static_cast<int>(mt_values.size()); i++)
				_mt_values[i] = mt_values[i];
		}
		void getMtValuesWithAngularDist(vector<int>& _mt_values_angular)
		{
			_mt_values_angular.clear();
			_mt_values_angular.resize(mt_values_angular.size());
			for (int i = 0; i < static_cast<int>(mt_values_angular.size()); i++)
				_mt_values_angular[i] = mt_values_angular[i];
		}
		int getLocb(int mt);
		int getIRfromMTValuesAngular(int mt)
		{
			for (int ir = 0; ir < static_cast<int>(mt_values_angular.size()); ir++)
			{
				if (mt_values_angular[ir] == mt) return ir;
			}
			cout << " mt not found in getAngularDistribution " << mt << endl;
			exit(0);
		}

		bool isEmissionReaction(int mt)
		{
			for (int ir = 0; ir < static_cast<int>(mt_values_angular.size()); ir++)
			{
				if (mt_values_angular[ir] == mt) return true;
			}
			return false;
		}
		bool isMT(int mt)
		{
			if (mt == eMTTotal) return true;
			if (mt == eMTTotalCurrentWeight) return true;
			if (mt == eMTDisappearance) return true;
			if (mt == eMTElasticScattering) return true;
			if (mt == eMTHeating) return true;

			for (int ir = 0; ir < static_cast<int>(mt_values.size()); ir++)
			{
				if (mt_values[ir] == mt) return true;
			}

			return false;
		}
		bool isNuTotal()
		{
			if (jxs[1] != 0) return true;
			else return false;
		}
		bool isNuDelayed()
		{
			if (jxs[23] != 0) return true;
			else return false;
		}
		bool isUNRData()
		{
			if (jxs[22] != 0) return true;
			else return false;
		}
		REAL convertCMtoLabDirectionCosine(REAL muc)
		{
			REAL val0 = 1.0 + aw * muc;
			REAL val1 = 1.0 + aw * aw + 2.0 * aw * muc;
			REAL mul = 0.0;
			if (val1 < 1.0e-10)
				mul = sqrt(fabs((1.0 + muc) / 2));
			else
				mul = val0 / sqrt(val1);

			if (mul < -1.0) mul = -1.0;
			else if (mul > 1.0) mul = 1.0;

			return mul;
		}
		REAL convertCMtoLabDirectionCosineInelastic(REAL muc, REAL ein, REAL ldat1)
		{
			REAL R = aw * sqrt(1.0 - ldat1 / ein);
			REAL mul = (1.0 + R * muc) / sqrt(1.0 + R * R + 2.0 * R * muc);
			return mul;
		}
		REAL convertCMtoLabPDF(REAL pdfc, REAL muc)
		{
			REAL val = aw * aw + 2.0 * aw * muc + 1.0;
			REAL wk = val * val * val;
			REAL pdfl = pdfc * sqrt(wk) / (aw * aw * (aw + muc));
			return pdfl;
		}
		REAL convertCMtoLabPDFInelastic(REAL pdfc, REAL muc, REAL ein, REAL ldat1)
		{
			REAL R = aw * sqrt(1.0 - ldat1 / ein);
			REAL val = R * R + 2.0 * R * muc + 1.0;
			REAL wk = val * val * val;
			REAL pdfl = pdfc * sqrt(wk) / (R * R * (R + muc));
			return pdfl;
		}

		REAL getEoutAfterElasticScattering(REAL ein, REAL muc)
		{
			REAL alpha = (aw - 1.0) / (aw + 1.0);
			alpha = alpha * alpha;
			REAL eout = ((1.0 + alpha) + (1.0 - alpha) * muc) / 2.0 * ein;

			return eout;
		}
		REAL getEinBeforeElasticScattering(REAL eout, REAL muc)
		{
			REAL alpha = (aw - 1.0) / (aw + 1.0);
			alpha = alpha * alpha;
			REAL ein = 2.0 / ((1.0 + alpha) + (1.0 - alpha) * muc) * eout;
			return ein;
		}
		REAL getMucAfterElasticScattering(REAL ein, REAL eout)
		{
			REAL alpha = (aw - 1.0) / (aw + 1.0);
			alpha = alpha * alpha;
			REAL muc = (2.0 * eout / ein - (1.0 + alpha)) / (1.0 - alpha);
			REAL eps = 1.0e-3;
			if (muc < -1.0 - eps || muc > 1.0 + eps)
			{
				cout << " muc is not within [-1,1] in getMucAfterElasticScattering " << endl;
				cout << scientific << setprecision(6);
				cout << ein << endl;
				cout << eout << endl;
				cout << aw << endl;
				cout << alpha << endl;
				cout << muc << endl;
			}
			if (muc < -1.0) muc = -1.0;
			if (muc > 1.0) muc = 1.0;
			return muc;
		}
		REAL getEoutAfterInElasticScattering(REAL ein, REAL muc, REAL ldat1, REAL ldat2)
		{
			REAL eoutcm = ldat2 * (ein - ldat1);
			REAL val = aw + 1.0;
			REAL eoutlab = eoutcm + (ein + 2.0 * muc * val * sqrt(ein * eoutcm)) / val / val;
			return eoutlab;
		}
		REAL getEinBeforeInElasticScattering(REAL eout, REAL muc, REAL ldat1, REAL ldat2)
		{
			REAL val = aw + 1.0;
			REAL a1 = -ldat2 - 1.0 / val / val;
			REAL a2 = eout + ldat1 * ldat2;
			REAL a = a1 * a1 - 4.0 * muc * muc / val / val * ldat2;
			REAL b = 2.0 * a1 * a2 + 4.0 * muc * muc / val / val * ldat1 * ldat2;
			REAL c = a2 * a2;
			REAL wk = b * b - 4.0 * a * c;
			if (wk < 0.0) wk = 0.0;
			REAL e1 = (-b + sqrt(wk)) / (2.0 * a);
			REAL e2 = (-b - sqrt(wk)) / (2.0 * a);
			REAL e;

			//select solution
			if (muc > 0.0) e = e2;
			else e = e1;

			//ein is over threshold or not
			if (e < ldat1) return 0.0;

			else return e;
		}
		REAL getEinBeforeInElasticScattering(REAL eout, REAL muc, int mt)
		{
			if (isIndependentInelasticScattering(mt) == false)
			{
				cout << " error in getEinBeforeInElasticScattering(REAL eout, REAL muc, int mt) " << endl;
				exit(0);
			}

			if (dlw[mt][0].law != 3) return 0.0;

			//only applicable to law=3
			REAL ldat1 = dlw[mt][0].ldat[0] * 1.0e+6;	//in [eV]
			REAL ldat2 = dlw[mt][0].ldat[1];
			REAL ein = getEinBeforeInElasticScattering(eout, muc, ldat1, ldat2);
			return ein;
		}
		REAL getMucAfterInElasticScattering(REAL ein, REAL eout, REAL ldat1, REAL ldat2)
		{
#if 0
			//use equation in ACE manual
			REAL val = aw + 1.0;
			REAL eoutcm = ldat2 * (ein - ldat1);
			REAL muc = ((eout - eoutcm) * val * val - ein) / (2.0 * val * sqrt(ein * eoutcm));
			REAL eps = 1.0e-10;
			if (muc < -1.0 - eps || muc > 1.0 + eps)
			{
				cout << " error in getMucAfterInElasticScattering " << endl;
				exit(0);
			}
			if (muc < -1.0) muc = -1.0;
			if (muc > 1.0) muc = 1.0;
#else
			//use equation in NJOY2016 manual Eq.(315).
			REAL R = aw * sqrt(1.0 - ldat1 / ein);
			REAL muc = (eout * (1.0 + aw) * (1.0 + aw) - ein * (1.0 + R * R)) / (2.0 * R * ein);
			REAL eps = 1.0e-3;
			if (muc < -1.0 - eps || muc > 1.0 + eps)
			{
				cout << " muc is not within [-1,1] in getMucAfterInElasticScattering " << endl;
				cout << scientific << setprecision(6);
				cout << ein << endl;
				cout << eout << endl;
				cout << aw << endl;
				cout << ldat1 << endl;
				cout << muc << endl;
			}
			if (muc < -1.0) muc = -1.0;
			if (muc > 1.0) muc = 1.0;
#endif
			return muc;
		}

		void getAngularDistribution(int mt, REAL ein, vector<REAL>& mu_boundary, vector<REAL>& pdf, int& coord);
		void getAngularPDFwithInterpolation(int mt, int e0, int e1, REAL w0, REAL w1, vector<REAL>& pdf);
		void getAngularPDF(int ir, int e0, vector<REAL>& cs, vector<REAL>& pdf);
		void prepAngularPDF(int mt);
		int  getMaxTablePointsInAngularPDF(int mt);
		int  getMaxTablePointsInAngularPDF(int mt, int e0);
		int  getMaxTablePointsInAngularPDF(int mt, REAL ein);

		void getDLW(int ir, int mt, bool delayed = false);
		void getDelayedPrecursorDist();
		REAL getDelayedNeutronGroupRatio(int idg, REAL ein)
		{
			DLW& _dlw = delayed_precursor_distribution[idg];
			REAL val = endfInterpolator(_dlw.nr, _dlw.nbtt, _dlw.intt, _dlw.etab, _dlw.ptab, ein * 1.0e-6);
			return val;
		}
		REAL getDelayedNeutronDecayConstant(int idg)
		{
			DLW& _dlw = delayed_precursor_distribution[idg];
			REAL val = _dlw.dec * 1.0e+8;	//convert "shake" to "sec"
			return val;
		}
		void getDLW()
		{
			//neutron(s) emission
			for (int i = 0; i < static_cast<int>(mt_values.size()); i++)
			{
				int mt = mt_values[i];
				if (dlw.find(mt) != dlw.end()) continue;

				if (isEmissionReaction(mt) && mt != eMTElasticScattering)
				{
					for (int ir = 1; ir < static_cast<int>(mt_values_angular.size()); ir++)
					{
						if (mt_values_angular[ir] == mt)
							getDLW(ir, mt);
					}
				}
			}

			//delayed neutron specrum
			if (isNuDelayed())
			{
				int num_delayed_group = nxs[7];
				for (int ir = 1; ir <= num_delayed_group; ir++)
					getDLW(ir, ir, true);

				getDelayedPrecursorDist();
			}
		}
		void clearMCDDataTemporary()
		{
			mcedata_temporary.clear();
		}
		void clearEADDataTemporary()
		{
			eaddata_temporary.clear();
		}
		void getIncidentEnergyGridInDLW(int mt, vector<REAL>& ene_boundary, vector<REAL>& add_boundary, bool delayed = false);
		void getEnergyAngleDistribution(int mt, REAL ein, FMEneAngDist& eadist, FMEneAngDist& ead_wk);
		void getEnergyDistributionElastic(int mt, REAL ein, vector<REAL>& mu_boundary, vector<REAL>& pdf, FMEneAngDist& eadist, int coord, bool delayed = false);
		void getEnergyDistributionElasticDebug( );
		void getEnergyDistributionwithDLW(int mt, REAL ein, vector<REAL>& mu_boundary, vector<REAL>& pdf, FMEneAngDist& eadist, FMEneAngDist& ead_wk, int coord, bool delayed = false);
		void getEnergyDistributionwithDLWLaw3(int mt, REAL ein, vector<REAL>& mu_boundary, vector<REAL>& pdf, int coord, DLW* dlw_wk, FMEneAngDist& ead_wk);
		void getEnergyDistributionwithDLWLaw4Law7Law9Law11(int mt, REAL ein, vector<REAL>& mu_boundary, vector<REAL>& pdf, int coord, DLW* dlw_wk, FMEneAngDist& ead_wk, int idw, bool delayed);
		void getEnergyDistributionwithDLWLaw44Law61(int mt, REAL ein, vector<REAL>& mu_boundary, vector<REAL>& pdf, int coord, DLW* dlw_wk, FMEneAngDist& ead_wk, int idw, bool delayed);
		void getEnergyDistributionwithDLWLaw66(int mt, REAL ein, DLW* dlw_wk, FMEneAngDist& ead_wk);
		void getEnergyPDFLaw4(int law, int coord, int offset, MCEData& mcedata, bool delayed = false);
		void getEnergyPDFLaw7Law9(int law, REAL ein, REAL theta, REAL u, FMEneAngDist& eadistwk);
		void getEnergyPDFLaw11(REAL ein, REAL aa, REAL bb, REAL u, FMEneAngDist& eadistwk);
		void getEnergyAnglePDFLaw44Law61(int law, int coord, int offset, REAL ein, FMEneAngDist& ead, bool delayed = false);
		void calcPlCoefLaw44(int coord, REAL r, REAL a, int max_pl, vector<REAL>& pl_coef);
		void calcPlCoefLaw61(int coord, int offset, int max_pl, vector<REAL>& pl_coef);
		REAL interpolatePdfLaw61(int offset, REAL mu, vector<vector<REAL> >& data);
		int getMaxAngularPdfPointInLaw61(int jed, vector<int>& lc)
		{
			int npmax = 0;
			for (int i = 0; i < static_cast<int>(lc.size()); i++)
			{
				int offset = jed + lc[i] - 1;
				int np = rtoi(xss[offset + 1]);
				if (np > npmax) npmax = np;
			}

			return npmax;
		}

		void doMCEInterporation(int ndiv, int intt, MCEData& d0, MCEData& d1, MCEData& d);
		void doENDFInterporation(int intt, MCEData& d0, MCEData& d1, MCEData& d);
		void doEneAngDistInterporation(int intt, REAL ein0, REAL ein1, REAL ein, FMEneAngDist& eadist0, FMEneAngDist& eadist1, FMEneAngDist& eadist);
		void convertMCEDataToAngDist(MCEData& mcedata, FMEneAngDist& eadistwk);
		void convertAngDistToMCEData(int intt, REAL ein, FMEneAngDist& eadistwk, MCEData& mcedata);

		void setUNRBlock();
		void getUNRParamter(REAL ein, vector<vector<REAL> >& uwk);
		void prepUnresolvedResonanceUFGXSFactor(REAL bg_xs_homo, vector<REAL>& bg_xs, vector<string>& fname, vector<string>& output_data, string add_name_ = "");

		UNRData* getUNRBlockPointer()
		{
			return &unr_data;
		}

		void report(string fname);


	};
}
