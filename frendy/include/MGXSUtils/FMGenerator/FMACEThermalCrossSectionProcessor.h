//-----------------------------------------------------
// FMACEThermalCrossSectionProcessor.h : process ACE thermal files 
//        
//-----------------------------------------------------

#pragma once
#include "MGXSUtils/FMGenerator/FMGenerator_global.h"
#include "MGXSUtils/FMGenerator/FMEneAngDist.h"
#include "MGXSUtils/FMGenerator/FMZlib.h"
#include "MGXSUtils/FMGenerator/FMPrinter.h"

namespace FMGen
{
	enum MTTypeThermal
	{
	};
	struct MCEDataThermal
	{
		int intt;
		REAL ein;
		int np;
		int max_pl;
		vector<REAL> eout;
		vector<vector<REAL> > data;		//data types (pdf, cdf, pl_coef), np
	};
	struct ITIEData
	{
		int				nin;
		vector<REAL>	ein;
		vector<REAL>	sigin;
	};
	struct ITCEData
	{
		int				nel;
		vector<REAL>	eel;
		vector<REAL>	p;
	};
	struct ITXEData
	{
		REAL			eout;
		REAL			pdf;
		REAL			cdf;
		vector<REAL>	mu;
	};
	struct ITCAData
	{
		vector<REAL>	mu;
	};
	struct ITXEProcessedData
	{
		REAL			eout_l;		//lower limit of this energy range
		REAL			eout_u;		//upper limit of this energy range
		REAL			pdf;		//pdf of this energy range
		REAL			eout;		//energy point for cdf
		REAL			cdf;		//cdf (0-1)
		vector<REAL>	coef;		//pl coefficients
	};

	class FMACEThermalCrossSectionProcessor
	{
	private:
		//ACE data
		vector<string>		title;
		vector<int>			izaw;
		vector<int>			nxs;
		vector<int>			jxs;
		vector<REAL>		xss;

		//data from ace
		ITIEData					itie_data;
		ITCEData					itce_data;
		vector<vector<ITXEData> >	itxe_data;
		vector<ITCAData>			itca_data;

		//processed data
		vector<vector<ITXEProcessedData> >	itxe_proc_data;
		vector<vector<REAL> >				itca_proc_data;
		vector<REAL>						bi_value;

		string	zaid;		// nuclide zaid
		int		za;			// nuclide id
		REAL	aw;			// mass
		REAL	temp_kelvin;// temperature in [K]
		string	file_name;	// ACE file name

		int		table_length;
		int		idpni;
		int		nil;
		int		nieb;
		int		idpnc;
		int		ncl;
		int		ifeng;

		REAL	eout_lower;
		REAL	eout_upper;
		REAL	eff_temperature;

	public:

		FMACEThermalCrossSectionProcessor()
		{
			clear();
		}
		~FMACEThermalCrossSectionProcessor()
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
			file_name.clear();
			zaid.clear();
			itxe_data.clear();
			itca_data.clear();
			itxe_proc_data.clear();
		}
		void setACEData(vector<string>& _title, vector<int>& _izaw, vector<int>& _nxs, vector<int>& _jxs,
			vector<REAL>& _xss)
		{
			//used for interface between FRENDY
			// acexs.setACEData( .... );
			// acexs.processHeaderData();
			// acexs.processXSData();

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

		REAL getKelvin()
		{
			return temp_kelvin;
		}
		void setEffectiveTemperature(REAL t)
		{
			eff_temperature = t;
		}
		REAL getEffectiveTemperature()
		{
			return eff_temperature;
		}
		string getZaid()
		{
			return zaid;
		}
		int getZa()
		{
			return za;
		}
		REAL getAW()
		{
			return aw;
		}
		bool isElasticScattering()
		{
			if (jxs[3] != 0)
				return true;
			else
				return false;
		}
		void setEoutUpperLowerInelastic(REAL eu, REAL el)
		{
			eout_upper = eu;
			eout_lower = el;
		}
		bool isIncoherentElasticScattering()
		{
			if (jxs[3] != 0 && idpnc != 4)
				return true;
			else
				return false;
		}
		bool isCoherentElasticScattering()
		{
			if (jxs[3] != 0 && idpnc == 4)
				return true;
			else
				return false;
		}

		void getEinUpperLowerElastic(REAL& eu, REAL& el)
		{
			el = itce_data.eel[0] * 1.0e+6;
			eu = itce_data.eel.back() * 1.0e+6;
		}
		void getEinUpperLowerInelastic(REAL& eu, REAL& el)
		{
			el = itie_data.ein[0] * 1.0e+6;
			eu = itie_data.ein.back() * 1.0e+6;
		}
		void getEoutUpperLowerInelastic(REAL ein, REAL& eu, REAL& el)
		{
			ein *= 1.0e-6;	//ev -> MeV
			int ind = getInterval(itie_data.ein, ein);

#if 0
			//may be consistent treatment with Monte-Carlo method
			el = itxe_proc_data[ind][0].eout_l;
			eu = itxe_proc_data[ind + 1].back().eout_u;
#else
			//limit range for s(a,b) treatment to cut non-physical tail for lower/upper scattering in the case of IFENG=2
			if (ifeng < 2)
			{
				el = itxe_proc_data[ind][0].eout;
				eu = itxe_proc_data[ind + 1].back().eout;
			}
			else
			{
				int len = (int)itxe_proc_data[ind + 1].size();
				if (len >= 3)
				{
					el = itxe_proc_data[ind][1].eout;
					eu = itxe_proc_data[ind + 1][len - 2].eout;
				}
				else
				{
					el = itxe_proc_data[ind][0].eout;
					eu = itxe_proc_data[ind + 1][len - 1].eout;
				}
			}
#endif
#if 0
			cout << scientific << setprecision(4);
			cout << setw(15) << "sab data";
			for (int i = 0; i < itie_data.ein.size(); i++)
				cout << setw(15) << itie_data.ein[i] << endl;
			cout << ind << endl;
			for (int i = 0; i < itxe_proc_data[ind].size(); i++)
			{
				cout << setw(15) << itxe_proc_data[ind][i].eout;
				cout << setw(15) << itxe_proc_data[ind][i].eout_l;
				cout << setw(15) << itxe_proc_data[ind][i].eout_u;
				cout << setw(15) << itxe_proc_data[ind][i].pdf;
				cout << setw(15) << itxe_proc_data[ind][i].cdf;
				cout << setw(15) << itxe_proc_data[ind][i].coef[0];
				cout << endl;
			}
#endif

		}
		REAL getIncoherentInelasticXS(REAL ein);
		REAL getIncoherentElasticXS(REAL ein);
		REAL getCoherentElasticXS(REAL ein);
		REAL getElasticXS(REAL ein);

		void getElasticEnergyGrids(vector<REAL>& egrid)
		{
			egrid.resize(itce_data.eel.size());
			for (int i = 0; i < static_cast<int>(itce_data.eel.size()); i++)
				egrid[i] = itce_data.eel[i];
		}

		void prepPlCoefIncoherentInelastic(int max_pl);
		void prepPlCoefIncoherentElastic(int max_pl);
		void prepPlCoefCoherentElastic(int max_pl);

		void getPlCoefIncoherentInelastic(REAL ein, REAL eout_upper, REAL eout_lower, vector<REAL>& coef);
		void getPlCoefIncoherentInelasticIFENG1(int nin, REAL eout_upper, REAL eout_lower, vector<REAL>& coef);
		void getPlCoefIncoherentInelasticIFENG2(int nin, REAL eout_upper, REAL eout_lower, vector<REAL>& coef);
		void getPlCoefIncoherentElastic(REAL ein, vector<REAL>& coef);
		void getPlCoefCoherentElastic(REAL ein, vector<REAL>& coef);
		void getPlCoefElastic(REAL ein, vector<REAL>& coef);

		void dumpIncoherentInelasticData();
	};
}
