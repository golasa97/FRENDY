//-----------------------------------------------------
// Multi-group cross section generator from ACE file
//-----------------------------------------------------

#include <string>
#include "MGXSUtils/FMGenerator/FMGenerator.h"
#include "MGXSUtils/FMGenerator/FMDefaultInputGenerator.h"

using namespace std;

int main(int argc, char* argv[])
{
	string input_file = argv[1];

	string option;
	if (argc >= 3) option = argv[2];

	FMGen::FMGenerator fm_gen;

	if (option == "ace" || option == "ACE")
	{
		//set and default input data .. test purpose
		map<string, vector<string> > alternate_input_data;
		alternate_input_data.clear();

		FMGen::FMDefaultInputGenerator fm_inp_gen;
		fm_inp_gen.prepreDefaultInput(input_file, alternate_input_data);
		input_file.clear();

		fm_gen.readAndProcessInputData(alternate_input_data);

		fm_gen.run();
	}
	else if (option == "test")
	{
		//test purpose
		//fm_gen.readAndProcessInputData(input_file);

		fm_gen.test_independent();
	}
	else if (option == "frendy")
	{
		//stab for frendy integration
		map<string, vector<string> > input_data;
		fm_gen.readInputData(input_data);

		//repeat the following for necessary times. set data for fast and thermal ace files
		{
			string zaid;
			vector<string> _title;
			vector<int> _izaw;
			vector<int> _nxs;
			vector<int> _jxs;
			vector<double> _xss;
			fm_gen.data_container.setACEFileData(zaid, _title, _izaw, _nxs, _jxs, _xss);
		}

		fm_gen.data_container.checkACEFiles();
		fm_gen.data_container.readAndSetUFEnergyGroupStructure();
		fm_gen.data_container.doInitialize();

		fm_gen.run();

		map<string, string>::iterator it;
		for (it = fm_gen.data_container.output_list_data.begin(); it != fm_gen.data_container.output_list_data.end(); it++)
		{
			string wk = it->first;
			if (wk.substr(0, 7) == "FMMatxs")
			{
				fm_gen.data_container.output_list_data[wk];		// this is data of matxs file;
			}
			if (wk.substr(0, 7) == "FMGENDF")
			{
				fm_gen.data_container.output_list_data[wk];		// this is data of GENDF file;
			}
		}

	}
	else
	{
		//stand alone normal processing
		fm_gen.readAndProcessInputData(input_file);

		fm_gen.run();
	}


}
