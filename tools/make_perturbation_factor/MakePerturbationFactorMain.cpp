#include "../tools/make_perturbation_factor/MakePerturbationFactor.hpp"

//using namespace std;

int main(int argc, char *argv[])
{

	if (argc <= 0)
	{
		cout << "Please set input file name." << endl;
	}
	string input_file_name = argv[1];

	MakePerturbationFactor MPF;

	MPF.process_make_perturbation_factor(input_file_name);

	return 0;
}
