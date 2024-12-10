//----------------------------------------------------------------
// FMGenerator : generate multi-group cross sections from ACE cross section file
//
//----------------------------------------------------------------

#pragma once

#include "MGXSUtils/FMGenerator/FMGenerator_global.h"
#include "MGXSUtils/FMGenerator/FMDataContainer.h"
#include "MGXSUtils/FMGenerator/FMEneAngDist.h"
#include "MGXSUtils/FMGenerator/FMCalculationTime.h"
#include "MGXSUtils/FMGenerator/FMFreeGasSabIntegrator.h"
#include "MGXSUtils/FMGenerator/FMMatxsOutput.h"

namespace FMGen
{

	class FMGenerator
	{
	private:
		FMFreeGasSabIntegrator sab;
		FMInputData input_data;

		void reportBuildDate()
		{
			stringstream of;
			of << "   Build date       : " << __DATE__ << "  " << __TIME__ << endl;
#ifdef __INTEL_LLVM_COMPILER
			of << "   Complied by Intel Compiler " << __VERSION__ << endl;
#else
#ifdef _MSC_VER
			of << "   Complied by Visual C++ Compiler  version " << _MSC_FULL_VER << endl;
#endif
#endif
#ifdef __GNUC__
			of << "   Complied by GNU C/C++ " << __GNUC__ << "." << __GNUC_MINOR__ << "." << __GNUC_PATCHLEVEL__ << endl;
#endif
			data_container.output_list_data.insert(make_pair("FMBuildDate.txt", of.str()));
		};
	public:
		FMDataContainer data_container;

		FMGenerator( )
		{
			reportBuildDate();
			checkPL_COEF();
		};
		~FMGenerator()
		{
			data_container.clear();
		};
		void readAndProcessInputData(string input_file)
		{
			input_data.clear();
			input_data.readDataFromFile(input_file);

			data_container.readInput(&input_data);
			data_container.readACEFiles();
			data_container.checkACEFiles();
			data_container.readAndSetUFEnergyGroupStructure();
			data_container.doInitialize();
		};
		void readAndProcessInputData(map<string, vector<string> >& input_data_map)
		{
			input_data.clear();
			input_data.setDataFromMap(input_data_map);

			data_container.readInput(&input_data);
			data_container.readACEFiles();
			data_container.checkACEFiles();
			data_container.readAndSetUFEnergyGroupStructure();
			data_container.doInitialize();
		};
		void readInputData(map<string, vector<string> >& input_data_map)
		{
			input_data.clear();
			input_data.setDataFromMap(input_data_map);

			data_container.readInput(&input_data);
		};

		void test_independent();
		void run();

		void calcEnergyTransferMatrix(FMACECrossSectionProcessor& acexs, int mt, map<int, vector<FMCompressedMatrix> >& matrix_map,
			vector<vector<vector<vector<REAL> > > >& matrix);
		void calcThermalIncoherentInelastic(FMACECrossSectionProcessor& acexs, string sab_name, int mt, map<int, vector<FMCompressedMatrix> >& matrix_map, map<int, vector<REAL> >& ratio_map);
		void calcThermalIncoherentCoherentElastic(FMACECrossSectionProcessor& acexs, string sab_name, int mt, map<int, vector<FMCompressedMatrix> >& matrix_map, map<int, vector<REAL> >& ratio_map);
		void calcThermalFreeGasAdaptiveIntegration(int ig, int max_pl, REAL xs_base, REAL wgt, REAL ein, REAL e_upper, REAL e_lower, vector<REAL>& sum_matrix, vector<REAL>& sum_matrix_tcut, vector<vector<vector<vector<REAL> > > >& matrix);
		REAL calcThermalFreeGasNormalizationFactor(REAL ein, REAL aw, REAL temp, REAL e_upper, REAL e_lower, vector<REAL>& eout_boundary);
		void calcNuChi(FMACECrossSectionProcessor& acexs, vector<vector<vector<vector<REAL> > > >& fis_matrix,
			vector<REAL>& nu_t, vector<REAL>& nu_p, vector<REAL>& nu_d,
			vector<REAL>& chi_t, vector<REAL>& chi_p, vector<REAL>& chi_d,
			vector<vector<REAL> >& chi_d_independent, vector<REAL>& delayed_ratio,
			REAL& nu_prompt_sum, REAL& nu_delayed_sum);

		void getEnergyAngleDistribution(FMACECrossSectionProcessor& acexs, int mt, REAL ein, FMEneAngDist& eadist, FMEneAngDist& ead_wk);
	};
}

