//----------------------------------------------------------------
// FMDefaultInputGenerator : generate default input
//
//----------------------------------------------------------------

#pragma once

#include "MGXSUtils/FMGenerator/FMGenerator_global.h"
#include "MGXSUtils/FMGenerator/FMZlib.h"

namespace FMGen
{
	class FMDefaultInputGenerator
	{
	private:
		ofstream of;

	public:
		FMDefaultInputGenerator( )
		{
		};
		~FMDefaultInputGenerator() {};
		void prepreDefaultInput(string ace_file, map<string, vector<string> >& default_input_data)
		{
			ifstream fin;
			fin.open(ace_file);
			if (!fin)
			{
				cout << " Error while open ACE file " << ace_file << endl;
				exit(0);
			}
			skipACE20XHeader(fin);
			string zaid;
			fin >> zaid;

			outputInputPart1(default_input_data);
			string wk = " " + zaid + "  1.0";
			vector<string> str_vec;
			str_vec.push_back(wk);
			default_input_data["material"] = str_vec;
			str_vec.clear();

			wk = " " + ace_file;
			str_vec.push_back(wk);
			default_input_data["ace_file"] = str_vec;

			outputInputPart2(default_input_data);

		};
		void outputInputPart1(map<string, vector<string> >& default_input_data)
		{
			string inp0[] =
			{
				" 1.964033e+07       10000  EL",
				" 52475.0            56000  EL",
				" 9118.8             12000  EL",
				" 4307.4             12000  EL",
				" 961.12              8000  EL",
				" 130.07             12000  EL",
				" 0.32242            10000  EL",
				" 1.0e-5",
			};
			string inp1[] =
			{
				" 1.000010e-05, 3.000000e-03, 5.000000e-03, 6.900000e-03, 1.000000e-02, 1.500000e-02, 2.000000e-02, 2.500000e-02,",
				" 3.000000e-02, 3.500000e-02, 4.200000e-02, 5.000000e-02, 5.800000e-02, 6.700000e-02, 7.700000e-02, 8.000000e-02,",
				" 9.500000e-02, 1.000000e-01, 1.150000e-01, 1.340000e-01, 1.400000e-01, 1.600000e-01, 1.800000e-01, 1.890000e-01,",
				" 2.200000e-01, 2.480000e-01, 2.800000e-01, 3.000000e-01, 3.145000e-01, 3.200000e-01, 3.500000e-01, 3.910000e-01,",
				" 4.000000e-01, 4.330000e-01, 4.850000e-01, 5.000000e-01, 5.400000e-01, 6.250000e-01, 7.050000e-01, 7.800000e-01,",
				" 7.900000e-01, 8.500000e-01, 8.600000e-01, 9.100000e-01, 9.300000e-01, 9.500000e-01, 9.720000e-01, 9.860000e-01,",
				" 9.960000e-01, 1.020000e+00, 1.035000e+00, 1.045000e+00, 1.071000e+00, 1.097000e+00, 1.110000e+00, 1.125400e+00,",
				" 1.150000e+00, 1.170000e+00, 1.235000e+00, 1.300000e+00, 1.337500e+00, 1.370000e+00, 1.445000e+00, 1.475000e+00,",
				" 1.500000e+00, 1.590000e+00, 1.670000e+00, 1.755000e+00, 1.840000e+00, 1.930000e+00, 2.020000e+00, 2.100000e+00,",
				" 2.130000e+00, 2.360000e+00, 2.550000e+00, 2.600000e+00, 2.720000e+00, 2.767920e+00, 3.300000e+00, 3.380750e+00,",
				" 4.000000e+00, 4.129250e+00, 5.043477e+00, 5.346430e+00, 6.160116e+00, 7.523983e+00, 8.315287e+00, 9.189814e+00,",
				" 9.905554e+00, 1.122446e+01, 1.370959e+01, 1.592827e+01, 1.945484e+01, 2.260329e+01, 2.498050e+01, 2.760773e+01,",
				" 3.051126e+01, 3.372015e+01, 3.726653e+01, 4.016900e+01, 4.551744e+01, 4.825160e+01, 5.157802e+01, 5.559513e+01,",
				" 6.790405e+01, 7.567357e+01, 9.166088e+01, 1.367420e+02, 1.486254e+02, 2.039950e+02, 3.043248e+02, 3.717032e+02,",
				" 4.539993e+02, 6.772874e+02, 7.485183e+02, 9.142423e+02, 1.010394e+03, 1.234098e+03, 1.433817e+03, 1.507331e+03,",
				" 2.034684e+03, 2.248673e+03, 3.354626e+03, 3.526622e+03, 5.004514e+03, 5.530844e+03, 7.465858e+03, 9.118820e+03,",
				" 1.113775e+04, 1.503439e+04, 1.661557e+04, 2.478752e+04, 2.739445e+04, 2.928300e+04, 3.697864e+04, 4.086771e+04,",
				" 5.516564e+04, 6.737947e+04, 8.229747e+04, 1.110900e+05, 1.227734e+05, 1.831564e+05, 2.472353e+05, 2.732372e+05,",
				" 3.019738e+05, 4.076220e+05, 4.504920e+05, 4.978707e+05, 5.502322e+05, 6.081006e+05, 8.208500e+05, 9.071795e+05,",
				" 1.002588e+06, 1.108032e+06, 1.224564e+06, 1.353353e+06, 1.652989e+06, 2.018965e+06, 2.231302e+06, 2.465970e+06,",
				" 3.011942e+06, 3.678794e+06, 4.493290e+06, 5.488116e+06, 6.065307e+06, 6.703200e+06, 8.187308e+06, 1.000000e+07,",
				" 1.1618343e+07,1.3840307e+07,1.4918247e+07,1.733253e+07, 1.964033e+07  //XMAS172 (njoy ign = 18)",
			};
			string inp2[] =
			{
				" 1/E",
			};

			vector<string> str_vec;
			for (int i = 0; i < 8; i++)
				str_vec.push_back(inp0[i]);
			default_input_data["ultra_fine_group"] = str_vec;
			str_vec.clear();

			for (int i = 0; i < 22; i++)
				str_vec.push_back(inp1[i]);
			default_input_data["multi_group"] = str_vec;
			str_vec.clear();

			for (int i = 0; i < 1; i++)
				str_vec.push_back(inp2[i]);
			default_input_data["default_spectrum"] = str_vec;
			str_vec.clear();

		};
		void outputInputPart2(map<string, vector<string> >& default_input_data)
		{
			string inp0[] =
			{
				" 4.0",
			};
			string inp1[] =
			{
				" NR    0.9996167 //  (NR or SLD)   atomic weight of bgxs",
				//" SLD    0.9996167 //  (NR or SLD)   atomic weight of bgxs",
			};
			string inp2[] =
			{
				" 1.0e+10 1.0e+3 1.0e+0",
//				" 1.0e+10 1.0e+5 1.0e+4 1.0e+3 1.0e+2 1.0e+1 1.0e+0 1.0e-1",
			};
			string inp3[] =
			{
				" 3",
			};
			string inp4[] =
			{
				" MATXS",
				" KRAMXS",
				//" Default",
			};

			vector<string> str_vec;
			for (int i = 0; i < 1; i++)
				str_vec.push_back(inp0[i]);
			default_input_data["thermal_cutoff"] = str_vec;
			str_vec.clear();

			for (int i = 0; i < 1; i++)
				str_vec.push_back(inp1[i]);
			default_input_data["calc_cond"] = str_vec;
			str_vec.clear();

			for (int i = 0; i < 1; i++)
				str_vec.push_back(inp2[i]);
			default_input_data["bg_xs_set"] = str_vec;
			str_vec.clear();

			for (int i = 0; i < 1; i++)
				str_vec.push_back(inp3[i]);
			default_input_data["max_pl"] = str_vec;
			str_vec.clear();

			for (int i = 0; i < 2; i++)
				str_vec.push_back(inp4[i]);
			default_input_data["edit_xs"] = str_vec;
			str_vec.clear();
		};
	};
}
