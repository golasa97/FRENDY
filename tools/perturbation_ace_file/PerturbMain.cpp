#include "CommonUtils/TimeUtils.hpp"
#include "ContinuousEnergyXSUtils/PerturbUtils/PerturbNuclearData.hpp"

using namespace frendy;

int main(int argc, char *argv[])
{
	if (argc <= 1)
	{
		throw runtime_error("Please set ace file name.");
	}
	else if (argc <= 2)
	{
		throw runtime_error("Please set perturbation file name.");
	}

	TimeUtils time_obj;
	string date_str = time_obj.get_current_time();
	cout << "Date                  : " << date_str << endl;

	string ace_file_name = argv[1];

	PerturbNuclearData per_nucl_obj;
	
	//string perturbation_file_name = argv[2];
	//per_nucl_obj.process_perturbed_nucl_data(ace_file_name, perturbation_file_name);

	string perturbation_file_list_file = argv[2];
	per_nucl_obj.process_perturbed_nucl_data_for_rs(ace_file_name, perturbation_file_list_file);

	return 0;
}
