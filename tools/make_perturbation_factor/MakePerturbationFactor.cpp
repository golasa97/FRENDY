#include "../tools/make_perturbation_factor/MakePerturbationFactor.hpp"

//constructor
MakePerturbationFactor::MakePerturbationFactor()
{
	//cout << "START" << endl;
}

//destructor
MakePerturbationFactor::~MakePerturbationFactor()
{
	//cout << "END" << endl;
}


///////////////////////////////////////////////////////////////////////////

void MakePerturbationFactor::process_make_perturbation_factor(string filename)
{
	set_input(filename);
	set_parameter();
	set_perturbation_factor();
	write_perturbation_factor();
}

///////////////////////////////////////////////////////////////////////////

void MakePerturbationFactor::set_input(string file_name)
{
	str_obj.set_file_name(file_name);
	input = str_obj.get_div_string_vec_all();
}

///////////////////////////////////////////////////////////////////////////

void MakePerturbationFactor::set_parameter()
{
	for (size_t i = 0; i < static_cast<size_t>(input.size()); i++)
	{
		if (input[i][0] == "<sample_size>")
		{
			sample_size       = stoi(input[i+1][0]);
			sample_size_extra = sample_size * 5; // To remove negative perturbation factor
		}
		else if (input[i][0] == "<seed>")
		{
			seed = stoi(input[i + 1][0]);
		}
		else if (input[i][0] == "<nuclide>")
		{   
			no_nucl = 0;
			nuclide.resize(static_cast<int>(input[i + 1].size()));
			for (size_t j = 0; j < static_cast<size_t>(nuclide.size()); j++)
			{
				nuclide[j] = input[i + 1][j];
				no_nucl++;
			}
		}
		else if (input[i][0] == "<reaction>")
		{
			no_react = 0;
			reaction.resize(static_cast<int>(nuclide.size()));
			for (size_t j = 0; j < static_cast<size_t>(reaction.size()); j++)
			{
				reaction[j].resize(static_cast<int>(input[i + j + 1].size()));
				for (size_t k = 0; k < static_cast<size_t>(reaction[j].size()); k++)
				{
					reaction[j][k] = stoi(input[i + j + 1][k]);
					no_react++;
				}
			}
		}
		else if (input[i][0] == "<relative_covariance>")
		{
			string rel_cov_file_name = input[i + 1][0];
			set_rel_cov(rel_cov_file_name);
		}
		else if (input[i][0] == "<energy_grid>")
		{
			energy_grid.resize(static_cast<int>(input[i + 1].size()));
			for (size_t j = 0; j < static_cast<size_t>(energy_grid.size()); j++)
			{
				energy_grid[j] = stod(input[i + 1][j]);
			}
			energy_grid_strc = static_cast<int> (energy_grid.size()) - 1;
		}
	}
	check_parameter();
}

///////////////////////////////////////////////////////////////////////////

void MakePerturbationFactor::set_rel_cov(string filename)
{
	vector<vector<double> > rel_cov_vec = get_2d_vec_from_csv(filename);

	rel_cov.resize(static_cast<int>(rel_cov_vec.size()), static_cast<int>(rel_cov_vec[0].size()));

	for (int i = 0; i < static_cast<int>(rel_cov_vec.size()); i++)
	{
		for (int j = 0; j < static_cast<int>(rel_cov_vec[i].size()); j++)
		{
			rel_cov(i, j) = rel_cov_vec[i][j];
		}
	}
	size_rel_cov = static_cast<int>(rel_cov_vec.size());
}

///////////////////////////////////////////////////////////////////////////

vector<vector<double> > MakePerturbationFactor::get_2d_vec_from_csv(string filename)
{
	cout << "Reading file : " << filename << ".....";
	ifstream file(filename);
	if (file.fail())
	{
		cout << endl;
		cout << "This file name cannot be read." << endl;
		exit(0);
	}

	string                line;   //1 line
	string::size_type     words;
	vector<vector<double> > input_value; //Array of text data

	while (getline(file, line)) //Read 1 line in input file
	{
		erase_space_in_string_line(line); //Remove space data before and after character
		if (static_cast<int>(line.size()) == 0)
		{
			continue;
		}

		vector<double> line_value_vec;

		words = line.find(","); //Serach position of "," in each line
		while (words != string::npos)
		{
			string str_data = line.substr(0, words);               //Clip text data before ","
			double value = stod(str_data); //Change string data to real data
			line_value_vec.push_back(value);                       //Add clip data before","

			line = line.substr(words + 1);        //Remove string data before ","
			erase_space_in_string_line(line); //Remove space data before and after character
			words = line.find(",");               //Serach position of "," in each line
		}

		if (static_cast<int>(line.size()) > 0) //Add string data after ","
		{
			string str_data = line.substr(0, words);
			double value = stod(str_data);
			line_value_vec.push_back(value);
		}

		if (static_cast<int>(line_value_vec.size()) > 0)
		{
			input_value.push_back(line_value_vec);
			line_value_vec.clear();
		}
	}
	cout << "finished" << endl;
	return input_value;
}

///////////////////////////////////////////////////////////////////////////

void MakePerturbationFactor::erase_space_in_string_line(string& line)
{
	for (size_t first_space = line.find_first_of(" "); first_space != string::npos;
		first_space = line.find_first_of(" "))
	{
		line.erase(first_space, 1);
	}
}

///////////////////////////////////////////////////////////////////////////

void MakePerturbationFactor::check_parameter()
{
	int cov_size = energy_grid_strc * no_react;
	if (cov_size != size_rel_cov)
	{
		cout << "!!! Parameter is not appropriate !!!" << endl;
		cout << "Covariance matrix size is      : " << size_rel_cov << endl;
		cout << "Energy group structure is      : " << energy_grid_strc << endl;
		cout << "Number of nuclides is          : " << no_nucl << endl;
		cout << "Number of reaction is          : " << no_react << endl;
		cout << "Covariance matrix size must be : " << cov_size << " x " << cov_size << endl;
		exit(0);
	}
}

///////////////////////////////////////////////////////////////////////////

void MakePerturbationFactor::set_perturbation_factor()
{
	negative_flg = 0;
	perturbation_factors_matrix.resize(size_rel_cov, sample_size_extra);


	cout << "Generating perturbation factors ..... " << endl;

	JacobiSVD<MatrixXd> svd(rel_cov, ComputeThinU | ComputeThinV);
	cout << endl;

	S = svd.singularValues();
	U = svd.matrixU();
	V = svd.matrixV();
	MatrixXd S_sqrt = S.array().sqrt();
	A = U * S_sqrt.asDiagonal();

	while (negative_flg == 0)
	{
		set_random_matrix();
		ones_matrix = MatrixXd::Ones(size_rel_cov, sample_size_extra);
		perturbation_factors_matrix = (A * random_matrix) + ones_matrix;

		perturbation_factors.resize(size_rel_cov);
		for (int i = 0; i < size_rel_cov; i++)
		{
			perturbation_factors[i].resize(sample_size_extra);
			for (int j = 0; j < sample_size_extra; j++)
			{
				perturbation_factors[i][j] = perturbation_factors_matrix(i, j);
			}
		}
		remove_negative_value();
	}
	cout << "Perturbation factor was generated." << endl;
	cout << endl;
}

///////////////////////////////////////////////////////////////////////////

void MakePerturbationFactor::set_random_matrix()
{
	random_matrix.resize(size_rel_cov, sample_size_extra);
	mt19937 engine(seed);
	normal_distribution<double> norm_dist(0.0, 1.0);

	for (int j = 0; j < sample_size_extra; j++)
	{
		for (int i = 0; i < size_rel_cov; i++)
		{
			random_matrix(i, j) = norm_dist(engine);
		}
	}
}

///////////////////////////////////////////////////////////////////////////

void MakePerturbationFactor::remove_negative_value()
{
	no_negative_values = 0;
	no_negative_column = 0;
	pos_negative_column.resize(0);
	vector<vector<double>> temp_perturbation_factors;
	temp_perturbation_factors = vector<vector<double>>(size_rel_cov, vector<double>(sample_size_extra, 0));
	temp_perturbation_factors = perturbation_factors;

	for (int j = 0; j < sample_size_extra; j++)
	{
		for (int i = 0; i < size_rel_cov; i++)
		{
			if (perturbation_factors[i][j] < 0.0)
			{
				pos_negative_column.push_back(j);
				//cout << j << endl;
				break;
			}
		}
	}
	cout << "Number of colums including negative value : " << static_cast<int>(pos_negative_column.size()) << endl;
	cout << "Input sample size       : " << sample_size << endl;
	cout << "Calculation sample size : " << sample_size_extra << endl;

	if (static_cast<int>(pos_negative_column.size()) > sample_size_extra - sample_size)
	{
		negative_flg = 0;
		sample_size_extra += 2 * (static_cast<int>(pos_negative_column.size()) - (sample_size_extra - sample_size));
		cout << "Number of negative perturbation factor is large." << endl;
		cout << "Recalculating perturbation factor." << endl;
	}
	else
	{
		negative_flg = 1;
		for (int i = 0; i < size_rel_cov; i++)
		{
			perturbation_factors[i].resize(0);
			for (int j = 0; j < sample_size_extra; j++)
			{
				if (check_int_in_vec1d(j, pos_negative_column) == 0)
				{
					perturbation_factors[i].push_back(temp_perturbation_factors[i][j]);
				}
				if (static_cast<int>(perturbation_factors[i].size()) == sample_size)
				{
					break;
				}
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////

int MakePerturbationFactor::check_int_in_vec1d(int n, vector<int> vector1d)
{
	int flg = 0;
	for (int i = 0; i < static_cast<int>(vector1d.size()); i++)
	{
		if (n == vector1d[i])
		{
			flg = 1;
		}
	}

	return flg;
}

///////////////////////////////////////////////////////////////////////////

void MakePerturbationFactor::write_perturbation_factor()
{
	cout << "Writing perturbation factors ..... ";
	for (int n = 0; n < no_nucl; n++)
	{
#ifdef _WIN32
		_mkdir(nuclide[n].c_str());
#else
		mkdir(nuclide[n].c_str(), S_IRWXU);
#endif

		for (int i = 0; i < sample_size; i++)
		{
			string filename = get_file_name(nuclide[n], i);

			ofstream output(filename);
			output.setf(ios::showpoint);   //show 0 (1. -> 1.000)
			output.setf(ios::scientific);  //scientific notification (100. -> 1.0E+3)

			for (int j = 0; j < static_cast<int>(reaction[n].size()); j++)
			{
				for (int k = 0; k < energy_grid_strc; k++)
				{
					//output.precision(0);
					//output << reaction[n][j] << ",";
					//output.precision(12);//Precision is 11 in ACE file
					//output << energy_grid[k] << "," << energy_grid[k+1] << ","
					//	<< perturbation_factors[(num_react * energy_grid_strc * n) + (energy_grid_strc* j) + k][i] << endl;
					output.precision(0);
					output << reaction[n][j] << "\t";
					output.precision(12);//Precision is 11 in ACE file

					output << energy_grid[k] << "\t" << energy_grid[k + 1] << "\t"
						<< perturbation_factors[(static_cast<int>(reaction[n].size()) * energy_grid_strc * n) + (energy_grid_strc* j) + k][i] << endl;

				}
			}

			output.close();
		}

	}
	cout << "finished" << endl;
}

///////////////////////////////////////////////////////////////////////////

string MakePerturbationFactor::get_file_name(string nuclide, int n)
{
	string filename;
	ostringstream oss;
	oss << n + 1;
	string index;
	if (n + 1 >= 1000)
	{
		index = oss.str();
	}
	else if (n + 1 >= 100)
	{
		index = "0" + oss.str();
	}
	else if (n + 1 >= 10)
	{
		index = "00" + oss.str();
	}
	else
	{
		index = "000" + oss.str();
	}

#ifdef _WIN32
	//filename = nuclide + "\\" + nuclide + "_" + index + ".csv";//"92235\\92235_1000.csv"
	filename = nuclide + "\\" + nuclide + "_" + index  + "";//"92235\\92235_1000.csv"
#else
	filename = nuclide + "/" + nuclide + "_" + index  + "";//"92235\\92235_1000.csv"
#endif
	
	return filename;
}

///////////////////////////////////////////////////////////////////////////
