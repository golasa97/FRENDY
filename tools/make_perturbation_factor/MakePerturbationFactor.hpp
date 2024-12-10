//#pragma once
#ifndef MAKE_PERTURBATION_FACTOR
#define MAKE_PERTURBATION_FACTOR

#ifdef _WIN32
#include "Eigen"
#include <direct.h>
#else
#include "../tools/make_perturbation_factor/Eigen/Eigen"
#include <sys/stat.h>
#endif

#include <iostream>
#include <fstream>
#include <random>

#include "CommonUtils/StringUtils.hpp"

using namespace std;
using namespace Eigen;

class MakePerturbationFactor
{
private:
public:

	frendy::StringUtils str_obj;

	vector<vector<string> > input;


	int no_react;
	int no_nucl;
	int size_rel_cov;
	int sample_size_extra;
	int sample_size;
	int seed;
	int energy_grid_strc;


	MatrixXd             rel_cov;
	vector<double>       energy_grid;
	vector<vector<int> > reaction;
	vector<string>       nuclide;


	MatrixXd                perturbation_factors_matrix;
	vector<vector<double> > perturbation_factors;
	MatrixXd                ones_matrix;
	MatrixXd                random_matrix;
	MatrixXd                U, S, V, A;


	int         no_negative_values;
	int         no_negative_column;
	vector<int> pos_negative_column;
	int         negative_flg;


	//constructor
	MakePerturbationFactor();

	//destructor
	virtual ~MakePerturbationFactor();


	void process_make_perturbation_factor(string filename);

	
	void set_input(string filename);
	
	
	void set_parameter();
	void set_rel_cov(string filename);
	vector<vector<double> > get_2d_vec_from_csv(string filename);
	void erase_space_in_string_line(string& line);
	void check_parameter();
	
	
	void set_perturbation_factor();
	void set_random_matrix();
	void remove_negative_value();
	int check_int_in_vec1d(int n, vector<int> vector1d);
	
	
	void write_perturbation_factor();
	string get_file_name(string nuclide, int n);

};


#endif // MAKE_PERTURBATION_FACTOR
