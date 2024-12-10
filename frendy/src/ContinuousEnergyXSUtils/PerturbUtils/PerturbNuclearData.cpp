#include "ContinuousEnergyXSUtils/PerturbUtils/PerturbNuclearData.hpp"
#ifdef _WIN32
#include <direct.h>
#endif
using namespace frendy;

PerturbNuclearData::PerturbNuclearData()
{

}

PerturbNuclearData::~PerturbNuclearData()
{

}

//Main process
////////////////////////////////////////////////////////////////////////////////////////////////////

void PerturbNuclearData::process_perturbed_nucl_data(string ace_file, string perturbation_file)
{
	set_ace_obj(ace_file);

	set_perturbation_input_file(perturbation_file);

	set_mt_list_input();

	set_ace_parameters();

	check_input_mt_list();


	perturb_nuclear_data();

	set_perturbed_ace_obj();

	write_ace_file_test();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PerturbNuclearData::process_perturbed_nucl_data_for_rs(string ace_file, string perturbation_file_list_file)
{
	set_ace_obj_org(ace_file);

	set_perturbation_file_list(perturbation_file_list_file);

// maruyama-b
	sample_flg = 0;
// maruyama-e

	for (size_t i = 0; i < static_cast<size_t>(sample_size_extra); i++)
	{
		copy_ace_obj_org();

		set_perturbation_input_file(perturbation_file_list[i]);

		set_mt_list_input();

		set_ace_parameters();

		check_input_mt_list();

		perturb_nuclear_data();

		set_perturbed_ace_obj();

		write_ace_file();

// maruyama-b
        sample_flg++;
// maruyama-e

	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PerturbNuclearData::set_ace_obj(string ace_file)
{
	ace_file_name = ace_file;

	cout << "Reading ACE file ......... " << endl;
	cout << "  ACE file name         : " << ace_file_name << endl;

	read_obj.set_file_name(ace_file_name);
	ace_obj = read_obj.get_ace_data_obj();
	read_obj.clear();

	cout << "finish." << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PerturbNuclearData::set_ace_obj_org(string ace_file)
{
	ace_file_name = ace_file;

	cout << "Reading ACE file ......... " << endl;
	cout << "  ACE file name         : " << ace_file_name << endl;

	read_obj.set_file_name(ace_file_name);
	ace_obj_org = read_obj.get_ace_data_obj();
	read_obj.clear();

	cout << "finish." << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PerturbNuclearData::copy_ace_obj_org()
{
        ace_obj = ace_obj_org;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PerturbNuclearData::set_perturbation_file_list(string perturbation_file_list_file)
{
	perturbation_file_list = get_1d_vec_s(perturbation_file_list_file);

	sample_size_extra = static_cast<int> (perturbation_file_list.size());
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PerturbNuclearData::set_perturbation_input_file(string perturbation_file)
{
	perturbation_file_name = perturbation_file;

	cout << "Perturbation file name : " << perturbation_file_name << endl;

	//perturbation_input = get_2d_vec_d(perturbation_file);

	str_obj.set_file_name(perturbation_file_name);
	vector<vector<string>> perturbation_input_str = str_obj.get_div_string_vec_all();
	perturbation_input.resize(static_cast<int>(perturbation_input_str.size()) / 4);
	for (size_t i = 0; i < static_cast<size_t>(perturbation_input_str.size()); i+=4)
	{
		perturbation_input[i/4].resize(4);
		for (size_t j = 0; j < 4; j++)
		{
			perturbation_input[i / 4][j] = stod(perturbation_input_str[i + j][0]);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PerturbNuclearData::set_ace_parameters()
{
	cout << "Setting parameters ... " << endl;

	//cross sections
	union_ene_grid = ace_obj.get_union_ene_grid();
	react_xs_tot = ace_obj.get_react_xs_tot();
	react_xs_sc = ace_obj.get_react_xs_sc();
	react_xs_cap = ace_obj.get_react_xs_cap();
	react_xs = ace_obj.get_react_xs();
	react_type_list = ace_obj.get_react_type_list();
	set_reaxt_xs_filled_with_zero();

        //probability table
        p_tab_int = ace_obj.get_unreso_prob_tab_int_data();
        p_tab_self_shielding_flg = ace_obj.get_unreso_prob_tab_self_shielding_flg();
        p_tab_ene = ace_obj.get_unreso_prob_tab_ene();
        p_tab_heat = ace_obj.get_unreso_prob_tab_heat();
        p_tab_sample_no = ace_obj.get_unreso_prob_tab_sample_no();
        p_tab = ace_obj.get_unreso_prob_tab_table();

	//nu_bar
	nu_bar_repr_flg = ace_obj.get_nu_bar_repr_flg();
	nu_int_data = ace_obj.get_nu_int_data();
	nu_range_data = ace_obj.get_nu_range_data();
	nu_data = ace_obj.get_nu_data();
	nu_ene_data = ace_obj.get_nu_ene_data();

	nu_d_bar_repr_flg = ace_obj.get_nu_d_bar_repr_flg();
	nu_d_int_data = ace_obj.get_nu_d_int_data();
	nu_d_range_data = ace_obj.get_nu_d_range_data();
	nu_d_data = ace_obj.get_nu_d_data();
	nu_d_ene_data = ace_obj.get_nu_d_ene_data();

	nu_p_bar_repr_flg = ace_obj.get_nu_p_bar_repr_flg();
	nu_p_int_data = ace_obj.get_nu_p_int_data();
	nu_p_range_data = ace_obj.get_nu_p_range_data();
	nu_p_data = ace_obj.get_nu_p_data();
	nu_p_ene_data = ace_obj.get_nu_p_ene_data();


	//energy distribution (fission spectrum)
	ene_distr_ene_repr_flg = ace_obj.get_ene_distr_ene_repr_flg();

	//ene_distr_ene_repr_flg=4 and (LF=1 or LF=12)
	ene_distr_ene_in_int_data = ace_obj.get_ene_distr_ene_in_int_data();
	ene_distr_ene_in_range_data = ace_obj.get_ene_distr_ene_in_range_data();
	ene_distr_ene_in_data = ace_obj.get_ene_distr_ene_in_data();

	ene_distr_ene_out_int_data = ace_obj.get_ene_distr_ene_out_int_data();
	ene_distr_ene_out_ene_data = ace_obj.get_ene_distr_ene_out_ene_data();
	ene_distr_ene_out_data = ace_obj.get_ene_distr_ene_out_data();
	ene_distr_ene_out_data_integ = ace_obj.get_ene_distr_ene_out_data_integ();

	//ene_distr_ene_repr_flg=7 and LF=7
	ene_distr_upper_ene_limit = ace_obj.get_ene_distr_upper_ene_limit();
	ene_distr_temp_eff_int_data = ace_obj.get_ene_distr_temp_eff_int_data();
	ene_distr_temp_eff_range_data = ace_obj.get_ene_distr_temp_eff_range_data();
	ene_distr_temp_eff_ene_data = ace_obj.get_ene_distr_temp_eff_ene_data();
	ene_distr_temp_eff_data = ace_obj.get_ene_distr_temp_eff_data();

// maruyama-b

        //scatering angle distribution
        angular_distr_pointer = ace_obj.get_angular_distr_pointer();
        angular_distr_type_flg = ace_obj.get_angular_distr_type_flg();
        angular_distr_int_data = ace_obj.get_angular_distr_int_data();
        angular_distr_ene_data = ace_obj.get_angular_distr_ene_data();
        angular_distr_cos_data = ace_obj.get_angular_distr_cos_data();
        angular_distr_data = ace_obj.get_angular_distr_data();
        angular_distr_data_integ = ace_obj.get_angular_distr_data_integ();

// maruyama-e

	cout << "finish." << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PerturbNuclearData::set_mt_list_input()
{
	mt_list.resize(static_cast<int>(perturbation_input.size()));
	for (int i = 0; i < static_cast<int>(perturbation_input.size()); i++)
	{
		mt_list[i] = (Integer)(perturbation_input[i][0] + 0.1);
                if( mt_list[i] == 19 )
                {
                  mt_list[i] = 18;
                }
	}
	mt_list_input.resize(static_cast<int>(mt_list.size()));
	mt_list_input = mt_list;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PerturbNuclearData::check_input_mt_list()
{
	remove_same_value_1d_vec_i(mt_list);

	check_mt_input();

	set_mt_list_perturbation();

	remove_mt_not_react_type_list();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PerturbNuclearData::check_mt_input()
{
	Integer invalid_mt_flg = 1;

	check_mt_invalid_pair(invalid_mt_flg);

	check_mt_invalid(invalid_mt_flg);

	if (invalid_mt_flg == 0)
	{
		exit(0);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PerturbNuclearData::check_mt_invalid_pair(Integer &invalid_mt_flg)
{
	vector<vector<Integer>> invalid_pairs(0);
	vector<Integer> invalid_pair(2);
	for (size_t i = 0; i < static_cast<size_t> (group_MT_all_xs.size()); i++)
	{
		if (check_same_value_1d_vec_i(group_MT_all_xs[i][0][0], mt_list) == 1)
		{
			for (size_t j = 0; j < static_cast<size_t>(group_MT_all_xs[i][1].size()); j++)
			{
				if (check_same_value_1d_vec_i(group_MT_all_xs[i][1][j], mt_list) == 1)
				{
					invalid_pair = { group_MT_all_xs[i][0][0],group_MT_all_xs[i][1][j] };
					invalid_pairs.push_back(invalid_pair);
				}
			}
		}
	}

	if (check_same_value_1d_vec_i(group_nu_values[0][0], mt_list) == 1)
	{
		for (size_t k = 0; k < static_cast<size_t>(group_nu_values[1].size()); k++)
		{
			if (check_same_value_1d_vec_i(group_nu_values[1][k], mt_list) == 1)
			{
				invalid_pair = { group_nu_values[0][0],group_nu_values[1][k] };
				invalid_pairs.push_back(invalid_pair);
			}
		}
	}

	if (static_cast<int> (invalid_pairs.size()) != 0)
	{
		cout << "Invalid MT pairs : ";
		for (size_t m = 0; m < static_cast<size_t> (invalid_pairs.size()); m++)
		{
			cout << "(" << invalid_pairs[m][0] << "," << invalid_pairs[m][1] << "),";
		}
		cout << endl;
		cout << "Cannot perturb these MTs at the same time." << endl;
		invalid_mt_flg = 0;
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PerturbNuclearData::check_mt_invalid(Integer &invalid_mt_flg)
{
	vector<Integer> mt_invalid(0);
	for (int i = 0; i < static_cast<int>(mt_list.size()); i++)
	{
		int flg = 0;
		if (mt_list[i] == 452 || mt_list[i] == 455 || mt_list[i] == 456)// nu_total:452, delayed:455, prompt:456
		{
			flg = 1;
		}
		else if (mt_list[i] == 1018)//fission spectrum
		{
			flg = 1;
		}
// maruyama-b
		if (mt_list[i] == 251) // elastic scattering angle distribution
		{
			flg = 1;
		}
// maruyama-e
		else
		{
			for (int j = 0; j < static_cast<int>(group_MT_all_xs.size()); j++)
			{
				if (flg == 1) { break; }
				for (int k = 0; k < static_cast<int>(group_MT_all_xs[j].size()); k++)
				{
					if (flg == 1) { break; }
					for (int l = 0; l < static_cast<int>(group_MT_all_xs[j][k].size()); l++)
					{
						if (mt_list[i] == group_MT_all_xs[j][k][l])
						{
							flg = 1;
							break;
						}
					}
				}
			}
		}
		if (flg != 1)
		{
			mt_invalid.push_back(mt_list[i]);
		}
	}

	if (static_cast<int>(mt_invalid.size()) > 0)
	{
		cout << "Following MT numbers do not exist as Cross Section." << endl;
		for (int m = 0; m < static_cast<int>(mt_invalid.size()); m++)
		{
			cout << " / " << mt_invalid[m];
		}
		cout << endl;
		invalid_mt_flg = 0;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PerturbNuclearData::set_mt_list_perturbation()
{
	mt_list_perturbation = vector<vector<vector<Integer>>>
		(static_cast<int>(mt_list.size()), vector<vector<Integer>>(3, vector<Integer>(0)));
	for (int i = 0; i < static_cast<int>(mt_list.size()); i++)
	{
		mt_list_perturbation[i][0].push_back(mt_list[i]);
		////lower
		for (int j = 0; j < static_cast<int>(group_MT_all_xs.size()); j++)
		{
			if (mt_list[i] == group_MT_all_xs[j][0][0])
			{
				mt_list_perturbation[i][1].resize(static_cast<int>(group_MT_all_xs[j][1].size()));
				mt_list_perturbation[i][1] = group_MT_all_xs[j][1];
				for (int k = 0; k < static_cast<int>(mt_list_perturbation[i][1].size()); k++)
				{
					for (int l = 0; l < static_cast<int>(group_MT_all_xs.size()); l++)
					{
						if (mt_list_perturbation[i][1][k] == group_MT_all_xs[l][0][0])
						{
							mt_list_perturbation[i][1].insert(mt_list_perturbation[i][1].end(),
								group_MT_all_xs[l][1].begin(), group_MT_all_xs[l][1].end());
							break;
						}
					}
				}
				break;
			}
		}


		//upper
		for (int m = 0; m < static_cast<int>(group_MT_all_xs.size()); m++)
		{
			//cout << m << endl;
			if (check_same_value_1d_vec_i(mt_list[i], group_MT_all_xs[m][1]) == 1)
			{
				mt_list_perturbation[i][2].push_back(group_MT_all_xs[m][0][0]);
				for (int n = 0; n < static_cast<int>(mt_list_perturbation[i][2].size()); n++)
				{
					//cout << n << endl;

					for (int o = 0; o < static_cast<int>(group_MT_all_xs.size()); o++)
					{
						//cout << o << endl;
						if (check_same_value_1d_vec_i(mt_list_perturbation[i][2][n], group_MT_all_xs[o][1]) == 1)
						{
							mt_list_perturbation[i][2].push_back(group_MT_all_xs[o][0][0]);
							break;
						}
					}
				}
				break;
			}

		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PerturbNuclearData::remove_mt_not_react_type_list()
{
	vector<vector<vector<Integer>>> mt_list_perturbation_new = vector<vector<vector<Integer>>>
		(static_cast<int>(mt_list_perturbation.size()), vector<vector<Integer>>(3, vector<Integer>(0)));
	for (int i = 0; i < static_cast<int>(mt_list_perturbation.size()); i++)
	{
		mt_list_perturbation_new[i][0].push_back(mt_list_perturbation[i][0][0]);

		//lower
		for (int j = 0; j < static_cast<int>(mt_list_perturbation[i][1].size()); j++)
		{
			if (check_same_value_1d_vec_i(mt_list_perturbation[i][1][j], react_type_list) == 1
				|| mt_list_perturbation[i][1][j] == 2 || mt_list_perturbation[i][1][j] == 101)
			{
				mt_list_perturbation_new[i][1].push_back(mt_list_perturbation[i][1][j]);
			}
		}
		mt_list_perturbation[i][1].resize(static_cast<int>(mt_list_perturbation_new[i][1].size()));
		mt_list_perturbation[i][1] = mt_list_perturbation_new[i][1];

		//upper
		for (int k = 0; k < static_cast<int>(mt_list_perturbation[i][2].size()); k++)
		{
			if (check_same_value_1d_vec_i(mt_list_perturbation[i][2][k], react_type_list) == 1
				|| mt_list_perturbation[i][2][k] == 2 || mt_list_perturbation[i][2][k] == 101)
			{
				mt_list_perturbation_new[i][2].push_back(mt_list_perturbation[i][2][k]);
			}
		}
		mt_list_perturbation[i][2].resize(static_cast<int>(mt_list_perturbation_new[i][2].size()));
		mt_list_perturbation[i][2] = mt_list_perturbation_new[i][2];
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PerturbNuclearData::set_reaxt_xs_filled_with_zero()
{
	react_xs_filled_with_zero.resize(static_cast<int>(react_xs.size()));
	for (int i = 0; i < static_cast<int>(react_xs.size()); i++)
	{
		react_xs_filled_with_zero[i].resize(static_cast<int>(union_ene_grid.size()));
		//react_xs_filled_with_zero[i] = react_xs[i];
		for (int j = 0; j < static_cast<int>(react_xs[i].size()); j++)
		{
			react_xs_filled_with_zero[i][j + static_cast<int>(union_ene_grid.size()) - static_cast<int>(react_xs[i].size())]
				= react_xs[i][j];
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////


//Perturbation
////////////////////////////////////////////////////////////////////////////////////////////////////

void PerturbNuclearData::perturb_nuclear_data()
{
	cout << "Perturbation start." << endl;

	nu_flg = 0;
	chi_flg = 0;
// maruyama-b
        elsct_ang_flg = 0;
// maruyama-e        

	for (int i = 0; i < static_cast<int>(perturbation_input.size()); i++)
	{
		//cout << "Perturbation processing : " << i + 1 << " / " << static_cast<int>(perturbation_input.size()) << endl;
		set_each_input(perturbation_input[i]);
                if( MT == 19 )
                {
                  MT = 18;
                }

		if (MT == 452 || MT == 455 || MT == 456)
		{
			perturb_nu();
		}

		else if (MT == 1018)
		{
			perturb_chi();
		}

// maruyama-b
		else if (MT == 251)
		{
			if( angular_distr_type_flg[0] == 1 )
			{
				perturb_elsct_ang_distr();
			}
			else
			{
				if (sample_flg == 0 && elsct_ang_flg == 0)
				{
					cout << "Perturbations for MT=251 is ignored. Please confirm LOCB_1 in ACE file." << endl;
				}
				continue;
			}
		}
// maruyama-e

		else
		{
			perturb_xs();
			if( MT == 1 || MT == 2 || MT == 18 || MT == 102 )
			{
				perturb_p_table();
			}
		}
	}

	cout << "Perturbation finished." << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PerturbNuclearData::set_ene_pos(vector<Real> energy_grid)
{
	int i_m = 0;
	int i_p = 0;
	//TabInterpolator tab_obj;

	Real ene_grid_min = energy_grid[0];
	Real ene_grid_max = energy_grid[static_cast<int> (energy_grid.size()) - 1];

	tab_obj.search_neighbor_value(Emin, energy_grid, i_m, i_p);
	if (Emin <= energy_grid[0])
	{
		//Exception with Tabinterpolator for minimum energy
		pos_Emin = 0;

                if( Emin <= energy_grid[0]*0.999 )
		{
			//Output warning message
			string class_name = "PerturbNuclearData";
			string func_name  = "set_ene_pos(vector<Real> energy_grid)";

			vector<string> err_com;
			ostringstream oss01, oss02;
			oss01.precision(10);
			oss01.setf(ios::showpoint);
			oss01.setf(ios::scientific);
			oss02.precision(10);
			oss02.setf(ios::showpoint);
			oss02.setf(ios::scientific);

			if( Emax > ene_grid_min )
			{
				oss01 << Emin;
				oss02 << ene_grid_min;

				string str_data01 = "Minimum energy from input file : " + oss01.str();
				string str_data02 = "Minimum energy from ace file   : " + oss02.str();
				string str_data03 = "Minimum energy is modified from " + oss01.str()
       		 	                          + " to " + oss02.str() + ".";
				err_com.push_back(str_data01);
				err_com.push_back(str_data02);
				err_com.push_back("The minimum energy from input file is smaller than");
				err_com.push_back("that from ace file.");
				err_com.push_back(str_data03);
			}
			else
			{
				oss01 << Emax;
				oss02 << ene_grid_min;

				string str_data01 = "Maximum energy from input file : " + oss01.str();
				string str_data02 = "Minimum energy from ace file   : " + oss02.str();
				err_com.push_back(str_data01);
				err_com.push_back(str_data02);
				err_com.push_back("The maximum energy from input file is smaller than");
				err_com.push_back("the minimum energy from ace file.");
				err_com.push_back("The perturbation is skipped.");
			}
			err_obj.output_caution(class_name, func_name, err_com);
		}
	}
	else
	{
		pos_Emin = i_p;
		if( fabs(Emin - energy_grid[i_m]) < fabs(min_ene_dif * Emin) &&
		    fabs(Emin - energy_grid[i_p]) > fabs(min_ene_dif * Emin) )
		{
			pos_Emin = i_m;
		}
	}

	tab_obj.search_neighbor_value(Emax, energy_grid, i_m, i_p);
	if (Emax >= energy_grid[static_cast<int> (energy_grid.size()) - 1])
	{
		//Exception with Tabinterpolator for maximum energy
		pos_Emax = static_cast<int> (energy_grid.size()) - 1;

		if (Emax > energy_grid[static_cast<int> (energy_grid.size()) - 1] * 1.001)
		{
			//Output warning message
			string class_name = "PerturbNuclearData";
			string func_name  = "set_ene_pos(vector<Real> energy_grid)";

			vector<string> err_com;
			ostringstream oss01, oss02;
			oss01.precision(10);
			oss01.setf(ios::showpoint);
			oss01.setf(ios::scientific);
			oss02.precision(10);
			oss02.setf(ios::showpoint);
			oss02.setf(ios::scientific);

			if( Emin < ene_grid_max )
			{
				oss01 << Emax;
				oss02 << ene_grid_max;

				string str_data01 = "Maximum energy from input file : " + oss01.str();
				string str_data02 = "Maximum energy from ace file   : " + oss02.str();
				string str_data03 = "Maximum energy is modified from " + oss01.str()
       		                           + " to " + oss02.str() + ".";
				err_com.push_back(str_data01);
				err_com.push_back(str_data02);
				err_com.push_back("The maximum energy from input file is smaller than");
				err_com.push_back("that from ace file.");
				err_com.push_back(str_data03);
			}
			else
			{
				oss01 << Emin;
				oss02 << ene_grid_max;

				string str_data01 = "Minimum energy from input file : " + oss01.str();
				string str_data02 = "Maximum energy from ace file   : " + oss02.str();
				err_com.push_back(str_data01);
				err_com.push_back(str_data02);
				err_com.push_back("The minimum energy from input file is smaller than");
				err_com.push_back("the maximum energy from ace file.");
				err_com.push_back("The perturbation is skipped.");
			}
	
			err_obj.output_caution(class_name, func_name, err_com);
		}
	}
	else
	{
		pos_Emax = i_m;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PerturbNuclearData::set_each_input(vector<Real> each_input)
{
	MT = (Integer)(each_input[0] + 0.1);
	if (each_input[1] < each_input[2])
	{
		Emin = each_input[1];
		Emax = each_input[2];
	}
	else
	{
		Emin = each_input[2];
		Emax = each_input[1];
	}
	multiplier = each_input[3];
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Pertubation Xs
////////////////////////////////////////////////////////////////////////////////////////////////////

void PerturbNuclearData::perturb_xs()
{
	set_ene_pos(union_ene_grid);
	vector<Real> vec_deviation;
	for (int i = 0; i < static_cast<int>(mt_list_perturbation.size()); i++)
	{
		if (MT == mt_list_perturbation[i][0][0])
		{
			if (check_same_value_1d_vec_i(MT, react_type_list) == 1 || MT == 2 || MT == 101)
			{
				vector<Real> vec_target_xs = get_vec_target_xs(MT);
				//make deviation
				vec_deviation = get_vec_deviation(vec_target_xs, union_ene_grid);
				//perturb target mt
				correct_xs_by_deviation(vec_deviation, MT);
				//lower
				for (int k = 0; k < static_cast<int>(mt_list_perturbation[i][1].size()); k++)
				{
					correct_xs_by_multiplier(multiplier, mt_list_perturbation[i][1][k]);
				}
				//upper
				for (int j = 0; j < static_cast<int>(mt_list_perturbation[i][2].size()); j++)
				{
					correct_xs_by_deviation(vec_deviation, mt_list_perturbation[i][2][j]);
				}
				//total
				correct_xs_by_deviation(vec_deviation, 1);
				correct_react_xs();
			}
			else
			{
				vector<Real> vec_deviation_sum(static_cast<int>(union_ene_grid.size()), 0);
				//lower
				for (int j = 0; j < static_cast<int>(mt_list_perturbation[i][1].size()); j++)
				{
					correct_xs_by_multiplier(multiplier, mt_list_perturbation[i][1][j]);
					vector<Real> vec_target_xs = get_vec_target_xs(mt_list_perturbation[i][1][j]);
					vec_deviation = get_vec_deviation(vec_target_xs, union_ene_grid);
					correct_vec_by_deviation(vec_deviation_sum, vec_deviation);
				}
				//upper
				for (int k = 0; k < static_cast<int>(mt_list_perturbation[i][2].size()); k++)
				{
					correct_xs_by_deviation(vec_deviation_sum, mt_list_perturbation[i][2][k]);
				}

				if (MT == 1)
				{
					//perturb target mt
					correct_xs_by_multiplier(multiplier, MT);
				}
				else
				{
					correct_xs_by_deviation(vec_deviation_sum, 1);
				}
				correct_react_xs();
			}

			break;
		}
	}
}

//Pertubation Xs
////////////////////////////////////////////////////////////////////////////////////////////////////

void PerturbNuclearData::perturb_p_table()
{
	if( p_tab_self_shielding_flg != 0 )
	{
		return;
	}

	//For p_tab_self_shielding_flg (lssf/iff) = 0 case
	//(The tabulations in the probability tables are cross sections.)
	int i_max = static_cast<int>(p_tab_ene.size());
	if( i_max == 0 )
	{
		return;
	}
	if( Emax < p_tab_ene[0]       * (1.0 + min_ene_dif) ||
            Emin > p_tab_ene[i_max-1] * (1.0 - min_ene_dif) )
	{
		return;
	}

	//Add Emin and Emax
	vector<Real> p_tab_ene_merge = p_tab_ene;
	if( Emin > p_tab_ene[0] )
	{
          p_tab_ene_merge.push_back(Emin);
	}
	if( Emax < p_tab_ene[i_max-1] )
	{
          p_tab_ene_merge.push_back(Emax);
	}
	sort(p_tab_ene_merge.begin(), p_tab_ene_merge.end());

	int ele_no = 0;
	vector<Real> p_tab_ene_mod;
	p_tab_ene_mod.push_back(p_tab_ene_merge[0]);
	for(int i=1; i<static_cast<int>(p_tab_ene_merge.size()); i++)
	{
		if( fabs((p_tab_ene_mod[ele_no] - p_tab_ene_merge[i])/p_tab_ene_merge[i]) > min_ene_dif )
		{
			p_tab_ene_mod.push_back(p_tab_ene_merge[i]);
			ele_no++;
		}
	}
	p_tab_ene_merge.clear();

	//Devide probability table to add Emin and Emax
	int i_max_mod = static_cast<int>(p_tab_ene_mod.size());
	vector<vector<Real> >          p_tab_heat_mod, p_tab_sample_no_mod;
	vector<vector<vector<Real> > > p_tab_mod;
	p_tab_heat_mod.resize(i_max_mod);
	p_tab_sample_no_mod.resize(i_max_mod);
	p_tab_mod.resize(i_max_mod);

	ele_no = 0;
	for(int i=0; i<i_max_mod; i++)
	{
		int add_flg = 0;
		for(int j=ele_no; j<i_max; j++)
		{
			if( fabs((p_tab_ene_mod[i] - p_tab_ene[j])/p_tab_ene[j]) < min_ene_dif )
			{
				p_tab_ene_mod[i]       = p_tab_ene[j];
				p_tab_heat_mod[i]      = p_tab_heat[j];
				p_tab_sample_no_mod[i] = p_tab_sample_no[j];
				p_tab_mod[i]           = p_tab[j];
				ele_no = j+1;

				add_flg = 1;
				break;
			}
		}

		if( add_flg == 0 )
		{
			//Set additional energy grid
                        Real p_tab_ene_add;
                        vector<Real> p_tab_heat_add, p_tab_sample_no_add;
                        vector<vector<Real> > p_tab_add;
                        if( fabs((p_tab_ene_mod[i] - Emin)/Emin) < min_ene_dif )
                        {
                                p_tab_ene_add = Emin;
                        }
                        else if( fabs((p_tab_ene_mod[i] - Emax)/Emax) < min_ene_dif )
                        {
                                p_tab_ene_add = Emax;
                        }

			//Output warning message when energy grid of probability table is added
			string class_name = "PerturbNuclearData";
			string func_name  = "perturb_p_table()";

			vector<string> err_com;
			ostringstream  oss01, oss02, oss03;
			oss01.precision(10);
			oss01.setf(ios::showpoint);
			oss01.setf(ios::scientific);
			oss02.precision(10);
			oss02.setf(ios::showpoint);
			oss02.setf(ios::scientific);
			oss03.precision(10);
			oss03.setf(ios::showpoint);
			oss03.setf(ios::scientific);

			oss01 << p_tab_ene_add;
			string str_data01 = "Additional energy grid for perturbation : " + oss01.str();
			err_com.push_back(str_data01);
			err_com.push_back("");
			string str_data02 = "Nearest energy boundary for probability tables : ";
			if( ele_no > 0 && ele_no < i_max )
 			{
				oss02 << p_tab_ene[ele_no-1];
				oss03 << p_tab_ene[ele_no];
				str_data02 = str_data02 + oss02.str() + ", " + oss03.str();
			}
			else
			{
				oss02 << p_tab_ene[ele_no-1];
				str_data02 = str_data02 + oss02.str();
			}
			err_com.push_back(str_data02);
			err_com.push_back("");
			err_com.push_back("The additional energy grid is added in the probability table data.");
			err_com.push_back("This modification may affect the calculation results.");
			err_com.push_back("Modification of energy grid to use original energy grid of the probability table,");
			err_com.push_back("i.e., the nearest energy boundary for probability table, is recommended.");
			err_obj.output_caution(class_name, func_name, err_com);

			//Calculation of the probability table usint interpolation
			calc_p_table(p_tab_ene_add, p_tab_int, p_tab_ene, p_tab_heat, p_tab_sample_no, p_tab,
			             p_tab_heat_add, p_tab_sample_no_add, p_tab_add);

			p_tab_ene_mod[i]       = p_tab_ene_add;
			p_tab_heat_mod[i]      = p_tab_heat_add;
			p_tab_sample_no_mod[i] = p_tab_sample_no_add;
			p_tab_mod[i]           = p_tab_add;
		}

	}

	//Modify probability table
	for(int i=0; i<i_max_mod; i++)
	{
		int mod_flg = 0;
		if( fabs((p_tab_ene_mod[i] - Emin)/Emin) < min_ene_dif ||
                    fabs((p_tab_ene_mod[i] - Emax)/Emax) < min_ene_dif )
		{
			mod_flg = 1;
		}
		else if( Emin < p_tab_ene_mod[i] && p_tab_ene_mod[i] < Emax )
		{
			mod_flg = 1;
		}

		if( mod_flg > 0 )
		{
			for(int k=0; k<static_cast<int>(p_tab_mod[i][0].size()); k++)
			{
				if( MT == 1 )
				{
					p_tab_mod[i][scatter_xs][k]   *= multiplier;
					p_tab_mod[i][fission_xs][k]   *= multiplier;
					p_tab_mod[i][radiation_xs][k] *= multiplier;
				}
				else
				{
					if( MT == 2 )
					{
						p_tab_mod[i][scatter_xs][k] *= multiplier;
					}
					else if( MT == 18 )
					{
						p_tab_mod[i][fission_xs][k] *= multiplier;
					}
					else if( MT == 102 )
					{
						p_tab_mod[i][radiation_xs][k] *= multiplier;
					}
				}
				p_tab_mod[i][total_xs][k] = p_tab_mod[i][scatter_xs][k]
                                                          + p_tab_mod[i][fission_xs][k]
                                                          + p_tab_mod[i][radiation_xs][k];
			}
		}
	}

	p_tab_ene       = p_tab_ene_mod;
	p_tab_heat      = p_tab_heat_mod;
	p_tab_sample_no = p_tab_sample_no_mod;
	p_tab           = p_tab_mod;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PerturbNuclearData::calc_p_table
                           (Real ene_add, Integer int_val,
                            vector<Real>& ene_vec, vector<vector<Real> >& heat_vec, vector<vector<Real> >& no_vec,
                            vector<vector<vector<Real> > >& p_tab_vec,
                            vector<Real>& heat_add, vector<Real>& no_add, vector<vector<Real> >& p_tab_add)
{
	int pos   = 0;
	int i_max = static_cast<int>(ene_vec.size());
	for(int i=0; i<i_max-1; i++)
	{
		if( ene_add < ene_vec[i+1] )
		{
			pos = i;
			break;
		}
	}
	Real ene_m = ene_vec[pos];
	Real ene_p = ene_vec[pos+1];

	TabInterpolator int_obj;
	int j_max = static_cast<int>(heat_vec[pos].size());
	heat_add.resize(j_max);
	no_add.resize(j_max);
	p_tab_add.resize(xs_type_no);
	for(int k=0; k<xs_type_no; k++)
	{
	  p_tab_add[k].resize(j_max);
	}

	for(int j=0; j<j_max; j++)
	{
		int_obj.interpolation_1d
                  (int_val, ene_add, heat_add[j], ene_m, heat_vec[pos][j], ene_p, heat_vec[pos+1][j]);
		int_obj.interpolation_1d
                  (int_val, ene_add, no_add[j], ene_m, no_vec[pos][j], ene_p, no_vec[pos+1][j]);

		p_tab_add[total_xs][j] = 0.0; //Total cross section
		for(int k=1; k<xs_type_no; k++)
		{
			int_obj.interpolation_1d
                          (int_val, ene_add, p_tab_add[k][j], ene_m, p_tab_vec[pos][k][j],
                                                              ene_p, p_tab_vec[pos+1][k][j]);
			p_tab_add[total_xs][j] += p_tab_add[k][j];
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<Real> PerturbNuclearData::get_vec_target_xs(Integer MT)
{
	vector<Real> vec_target_xs;
	if (MT == 1)
	{
		vec_target_xs.resize(static_cast<int>(react_xs_tot.size()));
		vec_target_xs = react_xs_tot;
	}
	else if (MT == 2)
	{
		vec_target_xs.resize(static_cast<int>(react_xs_sc.size()));
		vec_target_xs = react_xs_sc;
	}
	else if (MT == 101)
	{
		vec_target_xs.resize(static_cast<int>(react_xs_cap.size()));
		vec_target_xs = react_xs_cap;
	}
	else
	{
		for (int i = 0; i < static_cast<int>(react_xs_filled_with_zero.size()); i++)
		{
			if (MT == react_type_list[i])
			{
				vec_target_xs.resize(static_cast<int>(react_xs_filled_with_zero[i].size()));
				vec_target_xs = react_xs_filled_with_zero[i];
			}
		}
	}
	return vec_target_xs;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<Real> PerturbNuclearData::get_vec_deviation(vector<Real> &vec_ori, vector<Real> &union_ene_grid)
{
	vector<Real> vec_deviation(static_cast<int>(union_ene_grid.size()), 0.0);

	for (int i = 0; i < pos_Emax - pos_Emin + 1; i++)
	{
		vec_deviation[i + pos_Emin] = vec_ori[i + pos_Emin] * (multiplier - 1.0);
	}

	return vec_deviation;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PerturbNuclearData::correct_xs_by_deviation(vector<Real> &vec_deviation, Integer MT)
{
	if (MT == 1)
	{
		correct_vec_by_deviation(react_xs_tot, vec_deviation);
	}
	else if (MT == 2)
	{
		correct_vec_by_deviation(react_xs_sc, vec_deviation);
	}
	else if (MT == 101)
	{
		correct_vec_by_deviation(react_xs_cap, vec_deviation);
	}
	else
	{
		Integer pos_MT = get_pos_in_react_xs(MT);
		correct_vec_by_deviation(react_xs_filled_with_zero[pos_MT], vec_deviation);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PerturbNuclearData::correct_vec_by_deviation(vector<Real>& vec_ori, vector<Real>& vec_deviation)
{
	for (int i = 0; i < static_cast<int>(vec_deviation.size()); i++)
	{
		vec_ori[i] += vec_deviation[i];
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PerturbNuclearData::correct_xs_by_multiplier(Real multiplier, Integer MT)
{
	if (MT == 1)
	{
		correct_vec_by_multiplier(react_xs_tot, multiplier);
	}
	else if (MT == 2)
	{
		correct_vec_by_multiplier(react_xs_sc, multiplier);
	}
	else if (MT == 101)
	{
		correct_vec_by_multiplier(react_xs_cap, multiplier);
	}
	else
	{
		Integer pos_MT = get_pos_in_react_xs(MT);
		correct_vec_by_multiplier(react_xs_filled_with_zero[pos_MT], multiplier);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PerturbNuclearData::correct_vec_by_multiplier(vector<Real>& vec_ori, Real multiplier)
{
	for (int i = 0; i < pos_Emax - pos_Emin + 1; i++)
	{
		//vec_ori[i] *= multiplier;
		vec_ori[i + pos_Emin] *= multiplier;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PerturbNuclearData::correct_react_xs()
{
	for (int i = 0; i < static_cast<int>(react_xs.size()); i++)
	{
		if (static_cast<int>(react_xs[i].size()) != static_cast<int>(react_xs_filled_with_zero[i].size()))
		{
			for (int j = 0; j < static_cast<int>(react_xs[i].size()); j++)
			{
				react_xs[i][j] = react_xs_filled_with_zero[i][j +
					static_cast<int>(react_xs_filled_with_zero[i].size()) - static_cast<int>(react_xs[i].size())];
			}
		}
		else
		{
			react_xs[i] = react_xs_filled_with_zero[i];
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Perturbation nu value
////////////////////////////////////////////////////////////////////////////////////////////////////

void PerturbNuclearData::linearize_nu()
{
	linearize_nu(nu_range_data, nu_int_data, nu_ene_data, nu_data, nu_bar_repr_flg);

	linearize_nu(nu_d_range_data, nu_d_int_data, nu_d_ene_data, nu_d_data, nu_d_bar_repr_flg);

	linearize_nu(nu_p_range_data, nu_p_int_data, nu_p_ene_data, nu_p_data, nu_p_bar_repr_flg);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PerturbNuclearData::set_nu_union_ene_grid()
{
	vector<Real> nu_union_ene_grid_log10(1);
	Real Emin_in_nu_ene_grid = union_ene_grid[0];
	Real Emax_in_nu_ene_grid = union_ene_grid[static_cast<int> (union_ene_grid.size() - 1)];

	nu_union_ene_grid_log10[0] = log10(Emin_in_nu_ene_grid);
	Real energy_width_log10 = 1.0 / nu_ene_points_at_each_order;
	while (nu_union_ene_grid_log10[static_cast<int> (nu_union_ene_grid_log10.size() - 1)] < log10(Emax_in_nu_ene_grid))
	{
		Real new_ene = nu_union_ene_grid_log10[static_cast<int> (nu_union_ene_grid_log10.size() - 1)] + energy_width_log10;
		nu_union_ene_grid_log10.push_back(new_ene);
	}
	nu_union_ene_grid.resize(static_cast<int> (nu_union_ene_grid_log10.size()));
	for (size_t i = 0; i < static_cast<size_t> (nu_union_ene_grid_log10.size()); i++)
	{
		nu_union_ene_grid[i] = pow(10, nu_union_ene_grid_log10[i]);
	}
	if (nu_union_ene_grid[static_cast<int> (nu_union_ene_grid.size() - 1)] > Emax_in_nu_ene_grid)
	{
		nu_union_ene_grid[static_cast<int> (nu_union_ene_grid.size() - 1)] = Emax_in_nu_ene_grid;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PerturbNuclearData::tabulate_nu_data_repr_flg_1(vector<Integer> &nu_range_data, vector<Integer> &nu_int_data,
	vector<Real> &nu_ene_data, vector<Real> &nu_data, Integer &nu_repr_flg)
{
	if (nu_repr_flg == 1)
	{
		nu_int_data.resize(1);
		nu_int_data[0] = int_lin_lin;

		nu_range_data.resize(1);
		nu_range_data[0] = static_cast<int>(nu_union_ene_grid.size());

		vector<Real> nu_data_new(0);
		for (size_t i = 0; i < static_cast<size_t> (nu_union_ene_grid.size()); i++)
		{
			Real nu_data_new_each = 0.0;
			for (size_t j = 0; j < static_cast<size_t> (nu_data.size()); j++)
			{
				nu_data_new_each += (nu_data[j] * (pow(nu_union_ene_grid[i], j)));
			}
			nu_data_new.push_back(nu_data_new_each);
		}

		nu_data.resize(static_cast<int> (nu_data_new.size()));
		nu_data = nu_data_new;
		nu_data_new.clear();

		nu_repr_flg = 2;

		nu_ene_data.resize(static_cast<int>(nu_union_ene_grid.size()));
		nu_ene_data = nu_union_ene_grid;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PerturbNuclearData::perturb_nu()
{
	if (nu_flg == 0)
	{
		set_nu_union_ene_grid();
		linearize_nu();
	}
	nu_flg++;

	set_ene_pos(nu_union_ene_grid);

	vector<Real> vec_dev;
	if (MT == 452 && nu_bar_repr_flg == 2)
	{
		correct_vec_by_multiplier(nu_data, multiplier);
		if (nu_d_bar_repr_flg == 2)
		{
			correct_vec_by_multiplier(nu_d_data, multiplier);
		}
		if (nu_p_bar_repr_flg == 2)
		{
			correct_vec_by_multiplier(nu_p_data, multiplier);
		}
	}
	else if (MT == 455 && nu_d_bar_repr_flg == 2)
	{
		vec_dev.resize(static_cast<int>(nu_union_ene_grid.size()));
		vec_dev = get_vec_deviation(nu_d_data, nu_union_ene_grid);
		correct_vec_by_multiplier(nu_d_data, multiplier);
		if (nu_bar_repr_flg == 2)
		{
			correct_vec_by_deviation(nu_data, vec_dev);
		}
		vec_dev.clear();
	}
	else if (MT == 456 && nu_p_bar_repr_flg == 2)
	{
		vec_dev.resize(static_cast<int>(nu_union_ene_grid.size()));
		vec_dev = get_vec_deviation(nu_p_data, nu_union_ene_grid);
		correct_vec_by_multiplier(nu_p_data, multiplier);
		if (nu_bar_repr_flg == 2)
		{
			correct_vec_by_deviation(nu_data, vec_dev);
		}
		vec_dev.clear();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PerturbNuclearData::linearize_nu(vector<Integer> &nu_range_data, vector<Integer> &nu_int_data,
	vector<Real> &nu_ene_data, vector<Real> &nu_data, Integer &nu_repr_flg)
{
	if (nu_repr_flg == 0)
	{
		return;
	}
	else if (nu_repr_flg == 1)
	{
		tabulate_nu_data_repr_flg_1(nu_range_data, nu_int_data, nu_ene_data, nu_data, nu_repr_flg);
	}
	else if (nu_repr_flg == 2)
	{
		lin_obj.linearize_tab1_data(nu_range_data, nu_int_data, nu_ene_data, nu_data, nu_err_relative, nu_err_min);
		interpolate_nu_union_ene_grid(nu_range_data, nu_int_data, nu_ene_data, nu_data);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PerturbNuclearData::interpolate_nu_union_ene_grid(vector<Integer> &nu_range_data, vector<Integer> &nu_int_data, vector<Real> &nu_ene_data, vector<Real> &nu_data)
{
	vector<Real> nu_data_new(0);
	for (size_t i = 0; i < static_cast<size_t>(nu_union_ene_grid.size()); i++)
	{
		int i_m = 0;
		int i_p = 0;
		tab_obj.search_neighbor_value(nu_union_ene_grid[i], nu_ene_data, i_m, i_p);

		Real nu_data_new_each = nu_data[i_m]
			+ (nu_union_ene_grid[i] - nu_ene_data[i_m])
			*(nu_data[i_p] - nu_data[i_m])
			/ (nu_ene_data[i_p] - nu_ene_data[i_m]);
		nu_data_new.push_back(nu_data_new_each);
	}

	nu_data.resize(static_cast<int>(nu_data_new.size()));
	nu_data = nu_data_new;
	nu_data_new.clear();

	nu_ene_data.resize(static_cast<int>(nu_union_ene_grid.size()));
	nu_ene_data = nu_union_ene_grid;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Perturbation fission spectrum
////////////////////////////////////////////////////////////////////////////////////////////////////

void PerturbNuclearData::perturb_chi()
{
	if (chi_flg == 0)
	{
		set_pos_chi_in_react_type_list();
		set_chi_law_list();
		set_chi_union_ene_grid();
		linearize_chi();
	}
	chi_flg++;
	perturb_pdf();


	if (chi_flg == get_number_of_int(1018, mt_list_input))
	{
		normalize_chi_pdf();
		set_chi_cdf();
		chi_union_ene_grid.clear();
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PerturbNuclearData::set_chi_union_ene_grid()
{
	vector<Real> chi_union_ene_grid_log10(1);
	Real Emin_in_chi_ene_grid = union_ene_grid[0];
	//Real Emax_in_chi_ene_grid = union_ene_grid[static_cast<int> (union_ene_grid.size() - 1)];
	Real Emax_in_chi_ene_grid = 30.0;

	chi_union_ene_grid_log10[0] = log10(Emin_in_chi_ene_grid);
	Real energy_width_log10 = 1.0 / chi_ene_points_at_each_order;
	while (chi_union_ene_grid_log10[static_cast<int> (chi_union_ene_grid_log10.size() - 1)] < log10(Emax_in_chi_ene_grid))
	{
		Real new_ene = chi_union_ene_grid_log10[static_cast<int> (chi_union_ene_grid_log10.size() - 1)] + energy_width_log10;
		chi_union_ene_grid_log10.push_back(new_ene);
	}
	chi_union_ene_grid.resize(static_cast<int> (chi_union_ene_grid_log10.size()));
	for (size_t i = 0; i < static_cast<size_t> (chi_union_ene_grid_log10.size()); i++)
	{
		chi_union_ene_grid[i] = pow(10, chi_union_ene_grid_log10[i]);
	}
	if (chi_union_ene_grid[static_cast<int> (chi_union_ene_grid.size() - 1)] > Emax_in_chi_ene_grid)
	{
		chi_union_ene_grid[static_cast<int> (chi_union_ene_grid.size() - 1)] = Emax_in_chi_ene_grid;
	}
	chi_union_ene_grid.insert(chi_union_ene_grid.begin(), 0.0);
	chi_union_ene_grid.push_back(31.0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////


void PerturbNuclearData::set_pos_chi_in_react_type_list()//FindFissionMTPlace
{
	pos_chi_in_react_type_list.resize(0);
	for (int i = 0; i < static_cast<int>(react_type_list.size()); i++)
	{
		if (react_type_list[i] == 18)
		{
			pos_chi_in_react_type_list.push_back(i);
			//break;
		}

		else
		{
			for (size_t j = 0; j < static_cast<size_t>(group_MT_18[1].size()); j++)
			{
				if (react_type_list[i] == group_MT_18[1][j])
				{
					pos_chi_in_react_type_list.push_back(i);
				}
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PerturbNuclearData::set_chi_law_list()//GetAceLaw
{
	chi_law_list.resize(static_cast<int>(pos_chi_in_react_type_list.size()));

	for (int i = 0; i < static_cast<int>(pos_chi_in_react_type_list.size()); i++)
	{
		chi_law_list[i].resize(static_cast<int>(ene_distr_ene_repr_flg[pos_chi_in_react_type_list[i]].size()));
		chi_law_list[i] = (ene_distr_ene_repr_flg[pos_chi_in_react_type_list[i]]);
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PerturbNuclearData::linearize_chi()
{
	for (size_t i = 0; i < static_cast<size_t> (pos_chi_in_react_type_list.size()); i++)// Number of fission MT
	{
		for (size_t j = 0; j < static_cast<size_t>(ene_distr_ene_repr_flg[pos_chi_in_react_type_list[i]].size()); j++)// Number of LAW
		{
			if (ene_distr_ene_repr_flg[pos_chi_in_react_type_list[i]][j] == 4)
			{
				for (size_t k = 0; k < static_cast<size_t> (ene_distr_ene_out_int_data[pos_chi_in_react_type_list[i]][j].size()); k++)
				{
					int INTT = ene_distr_ene_out_int_data[pos_chi_in_react_type_list[i]][j][k];

					interpolate_chi_union_ene_grid(INTT, chi_union_ene_grid,
						ene_distr_ene_out_ene_data[pos_chi_in_react_type_list[i]][j][k], ene_distr_ene_out_data[pos_chi_in_react_type_list[i]][j][k]);
				}
			}

			else if (ene_distr_ene_repr_flg[pos_chi_in_react_type_list[i]][j] == 7)
			{
				// LAW = 7 is converted to LAW = 4


				Real U = ene_distr_upper_ene_limit[pos_chi_in_react_type_list[i]][j];// Restriction energy 

				Integer ene_in_grid_size = static_cast<int>(ene_distr_temp_eff_ene_data[pos_chi_in_react_type_list[i]][j].size());
				ene_distr_ene_in_data[pos_chi_in_react_type_list[i]][j].resize(ene_in_grid_size);
				ene_distr_ene_out_int_data[pos_chi_in_react_type_list[i]][j].resize(ene_in_grid_size);
				ene_distr_ene_out_ene_data[pos_chi_in_react_type_list[i]][j].resize(ene_in_grid_size);
				ene_distr_ene_out_data[pos_chi_in_react_type_list[i]][j].resize(ene_in_grid_size);

				ene_distr_ene_in_data[pos_chi_in_react_type_list[i]][j] = ene_distr_temp_eff_ene_data[pos_chi_in_react_type_list[i]][j];

				for (size_t k = 0; k < static_cast<size_t>(ene_distr_temp_eff_ene_data[pos_chi_in_react_type_list[i]][j].size()); k++)
				{
					Real ene_in = ene_distr_temp_eff_ene_data[pos_chi_in_react_type_list[i]][j][k];
					Real theta = ene_distr_temp_eff_data[pos_chi_in_react_type_list[i]][j][k];
					Real Ein_U_theta = (ene_in - U) / theta;// (E-U)/theta
					Real I = 0.5 * pow(M_PI, 0.5) * pow(theta, 1.5) * erf(pow(Ein_U_theta, 0.5)) - pow(Ein_U_theta, 0.5) * exp(-1.0 * Ein_U_theta);

					ene_distr_ene_out_int_data[pos_chi_in_react_type_list[i]][j][k] = int_lin_lin;// INTT = 2

					ene_distr_ene_out_ene_data[pos_chi_in_react_type_list[i]][j][k].resize(static_cast<int>(chi_union_ene_grid.size()));
					ene_distr_ene_out_ene_data[pos_chi_in_react_type_list[i]][j][k] = chi_union_ene_grid;

					ene_distr_ene_out_data[pos_chi_in_react_type_list[i]][j][k].resize(static_cast<int>(chi_union_ene_grid.size()));
					for (size_t l = 0; l < static_cast<size_t>(ene_distr_ene_out_ene_data[pos_chi_in_react_type_list[i]][j][k].size()); l++)
					{
						if (l == static_cast<size_t>(ene_distr_ene_out_ene_data[pos_chi_in_react_type_list[i]][j][k].size() - 1))
						{
							ene_distr_ene_out_data[pos_chi_in_react_type_list[i]][j][k][l] = 0;
						}
						else
						{
							Real ene_out = ene_distr_ene_out_ene_data[pos_chi_in_react_type_list[i]][j][k][l];
							ene_distr_ene_out_data[pos_chi_in_react_type_list[i]][j][k][l] = exp(-1.0 * ene_out / theta) * pow(ene_out, 0.5) / I;
						}

					}
				}

				ene_distr_ene_in_int_data[pos_chi_in_react_type_list[i]][j].resize(1);
				ene_distr_ene_in_int_data[pos_chi_in_react_type_list[i]][j][0] = int_lin_lin;

				ene_distr_ene_in_range_data[pos_chi_in_react_type_list[i]][j].resize(1);
				ene_distr_ene_in_range_data[pos_chi_in_react_type_list[i]][j][0] = max_data_no;


				// LAW = 7 is erased
				ene_distr_ene_repr_flg[pos_chi_in_react_type_list[i]][j] = 4;

				ene_distr_upper_ene_limit[pos_chi_in_react_type_list[i]][j] = 0.0;

				ene_distr_temp_eff_int_data[pos_chi_in_react_type_list[i]].resize(1);
				ene_distr_temp_eff_int_data[pos_chi_in_react_type_list[i]][j].resize(0);

				ene_distr_temp_eff_range_data[pos_chi_in_react_type_list[i]].resize(1);
				ene_distr_temp_eff_range_data[pos_chi_in_react_type_list[i]][j].resize(0);

				ene_distr_temp_eff_ene_data[pos_chi_in_react_type_list[i]].resize(1);
				ene_distr_temp_eff_ene_data[pos_chi_in_react_type_list[i]][j].resize(0);

				ene_distr_temp_eff_data[pos_chi_in_react_type_list[i]].resize(1);
				ene_distr_temp_eff_data[pos_chi_in_react_type_list[i]][j].resize(0);

			}

			else if (ene_distr_ene_repr_flg[pos_chi_in_react_type_list[i]][j] == 11)
			{
				cout << "Available law of fission spectrum : [4, 7] " << endl;

				//ene_distr_ene_repr_flg[pos_chi_in_react_type_list[i]][j] = 4;
			}

			else if (ene_distr_ene_repr_flg[pos_chi_in_react_type_list[i]][j] == 61)
			{
				cout << "Available law of fission spectrum : [4, 7] " << endl;

				//ene_distr_ene_repr_flg[pos_chi_in_react_type_list[i]][j] = 4;
			}

			else
			{
				cout << "Available law of fission spectrum : [4, 7] " << endl;

			}
		}
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PerturbNuclearData::interpolate_chi_union_ene_grid(Integer& INTT, vector<Real> chi_union_ene_grid,
	vector<Real>& ene_distr_ene_out_ene_data_each, vector<Real>& ene_distr_ene_out_data_each)
{
	Real         ene_max = ene_distr_ene_out_ene_data_each.back();
	vector<Real> ene_distr_ene_out_ene_data_each_new;
        for(int i=0; i<static_cast<int>(chi_union_ene_grid.size()); i++)
        {
          if( (chi_union_ene_grid[i] - ene_max) < 1.0E-10 )
          {
            ene_distr_ene_out_ene_data_each_new.push_back(chi_union_ene_grid[i]);
          }
        }

	if (static_cast<int> (ene_distr_ene_out_ene_data_each.size()) >= static_cast<int>(ene_distr_ene_out_ene_data_each_new.size()))
	{
		return;
	}
	else
	{
		if (ene_distr_ene_out_ene_data_each_new[static_cast<int>(ene_distr_ene_out_ene_data_each_new.size()) - 1] < ene_distr_ene_out_ene_data_each[static_cast<int>(ene_distr_ene_out_ene_data_each.size()) - 1])
		{
			ene_distr_ene_out_ene_data_each_new.push_back(ene_distr_ene_out_ene_data_each[static_cast<int>(ene_distr_ene_out_ene_data_each.size()) - 1]);
		}
		vector<Real> ene_distr_ene_out_data_each_new(1, 0.0);
		if (INTT == 1 || INTT == 2)
		{
			for (size_t i = 1; i < static_cast<size_t>(ene_distr_ene_out_ene_data_each_new.size()); i++)
			{
				if (ene_distr_ene_out_ene_data_each_new[i] <= ene_distr_ene_out_ene_data_each[0])
				{
					ene_distr_ene_out_data_each_new.push_back(0.0);
				}
				else if (i == static_cast<size_t>(ene_distr_ene_out_ene_data_each_new.size()) - 1)
				{
					ene_distr_ene_out_data_each_new.push_back(0.0);
				}
				else
				{
					int i_m = 0;
					int i_p = 0;
					tab_obj.search_neighbor_value(ene_distr_ene_out_ene_data_each_new[i], ene_distr_ene_out_ene_data_each, i_m, i_p);
					if (INTT == 1)
					{
						ene_distr_ene_out_data_each_new.push_back(ene_distr_ene_out_data_each[i_m]);
					}
					else if (INTT == 2)
					{
						int i_m = 0;
						int i_p = 0;
						tab_obj.search_neighbor_value(ene_distr_ene_out_ene_data_each_new[i], ene_distr_ene_out_ene_data_each, i_m, i_p);
						Real out_data_new = ene_distr_ene_out_data_each[i_m]
							+ (ene_distr_ene_out_ene_data_each_new[i] - ene_distr_ene_out_ene_data_each[i_m])
							*(ene_distr_ene_out_data_each[i_p] - ene_distr_ene_out_data_each[i_m])
							/ (ene_distr_ene_out_ene_data_each[i_p] - ene_distr_ene_out_ene_data_each[i_m]);
						ene_distr_ene_out_data_each_new.push_back(out_data_new);
					}
				}
			}
		}
		else
		{
			cout << "INTT is not 1 or 2. See part of \"LAW = 4\"in ace format manual." << endl;
			exit(0);
		}
		ene_distr_ene_out_data_each.resize(static_cast<int>(ene_distr_ene_out_data_each_new.size()));
		ene_distr_ene_out_data_each = ene_distr_ene_out_data_each_new;
		ene_distr_ene_out_ene_data_each.resize(static_cast<int>(ene_distr_ene_out_ene_data_each_new.size()));
		ene_distr_ene_out_ene_data_each = ene_distr_ene_out_ene_data_each_new;
		ene_distr_ene_out_data_each_new.clear();
		ene_distr_ene_out_ene_data_each_new.clear();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PerturbNuclearData::normalize_chi_pdf()
{
	vector<Integer> pos_chi = pos_chi_in_react_type_list;

	for (size_t i = 0; i < static_cast<size_t> (pos_chi.size()); i++)// Number of fission MT
	{
		for (size_t j = 0; j < static_cast<size_t>(ene_distr_ene_repr_flg[pos_chi[i]].size()); j++)// Number of LAW
		{
			for (size_t k = 0; k < static_cast<size_t> (ene_distr_ene_out_int_data[pos_chi[i]][j].size()); k++)
			{
				Real integrate_pdf = 0.0;
				for (size_t l = 1; l < static_cast<size_t> (ene_distr_ene_out_ene_data[pos_chi[i]][j][k].size()); l++)
				{
					integrate_pdf += (ene_distr_ene_out_data[pos_chi[i]][j][k][l - 1] + ene_distr_ene_out_data[pos_chi[i]][j][k][l])
						* (ene_distr_ene_out_ene_data[pos_chi[i]][j][k][l] - ene_distr_ene_out_ene_data[pos_chi[i]][j][k][l - 1]) / 2.0;
				}
				for (size_t l = 0; l < static_cast<size_t> (ene_distr_ene_out_ene_data[pos_chi[i]][j][k].size()); l++)
				{
					ene_distr_ene_out_data[pos_chi[i]][j][k][l] /= integrate_pdf;
				}
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PerturbNuclearData::set_chi_cdf()
{
	vector<Integer> pos_chi = pos_chi_in_react_type_list;
	for (size_t i = 0; i < static_cast<size_t> (pos_chi.size()); i++)// Number of fission MT
	{
		ene_distr_ene_out_data_integ[pos_chi[i]].resize(static_cast<int> (ene_distr_ene_out_data[pos_chi[i]].size()));
		for (size_t j = 0; j < static_cast<size_t>(ene_distr_ene_repr_flg[pos_chi[i]].size()); j++)// Number of LAW
		{
			ene_distr_ene_out_data_integ[pos_chi[i]][j].resize(static_cast<int> (ene_distr_ene_out_data[pos_chi[i]][j].size()));
			for (size_t k = 0; k < static_cast<size_t> (ene_distr_ene_out_int_data[pos_chi[i]][j].size()); k++)
			{
				ene_distr_ene_out_data_integ[pos_chi[i]][j][k].resize(static_cast<int> (ene_distr_ene_out_data[pos_chi[i]][j][k].size()));
				ene_distr_ene_out_data_integ[pos_chi[i]][j][k][0] = ene_distr_ene_out_data[pos_chi[i]][j][k][0];
				for (size_t l = 1; l < static_cast<size_t> (ene_distr_ene_out_data[pos_chi[i]][j][k].size()); l++)
				{
					ene_distr_ene_out_data_integ[pos_chi[i]][j][k][l] = ene_distr_ene_out_data_integ[pos_chi[i]][j][k][l - 1]
						+ (ene_distr_ene_out_data[pos_chi[i]][j][k][l - 1] + ene_distr_ene_out_data[pos_chi[i]][j][k][l])
						* (ene_distr_ene_out_ene_data[pos_chi[i]][j][k][l] - ene_distr_ene_out_ene_data[pos_chi[i]][j][k][l - 1]) / 2.0;
				}
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Perturbation probability density
void PerturbNuclearData::perturb_pdf_each(vector<Real>& ene_distr_ene_out_ene_data_new_each, vector<Real>& ene_distr_ene_out_data_each)//PerturbationPDF
{
	set_ene_pos(ene_distr_ene_out_ene_data_new_each);

	if (pos_Emin >= 0 && pos_Emax >= 0)
	{
		for (int i = 0; i < pos_Emax - pos_Emin + 1; i++)
		{
			ene_distr_ene_out_data_each[i + pos_Emin] *= multiplier;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Perturbation all pdf
void PerturbNuclearData::perturb_pdf()//PerturbationAllPDF
{
	vector<Integer> pos_chi = pos_chi_in_react_type_list;
	{
		for (int i = 0; i < static_cast<int> (pos_chi.size()); i++)
		{
			for (size_t j = 0; j < static_cast<size_t>(ene_distr_ene_repr_flg[pos_chi[i]].size()); j++)
			{
				for (size_t k = 0; k < static_cast<size_t> (ene_distr_ene_out_int_data[pos_chi[i]][j].size()); k++)
				{
					perturb_pdf_each(ene_distr_ene_out_ene_data[pos_chi[i]][j][k], ene_distr_ene_out_data[pos_chi[i]][j][k]);
				}
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Make cumulative distribution function by pdf
void PerturbNuclearData::set_new_cdf()
{
	for (int i = 0; i < static_cast<int> (pos_chi_in_react_type_list.size()); i++)
	{
		for (int j = 0; j < static_cast<int> (ene_distr_ene_out_data[pos_chi_in_react_type_list[i]][0].size()); j++)
		{
			ene_distr_ene_out_data_integ[pos_chi_in_react_type_list[i]][0][j].clear();
			ene_distr_ene_out_data_integ[pos_chi_in_react_type_list[i]][0][j].resize(static_cast<int> (ene_distr_ene_out_data[pos_chi_in_react_type_list[i]][0][j].size()));
			ene_distr_ene_out_data_integ[pos_chi_in_react_type_list[i]][0][j][0] = ene_distr_ene_out_data[pos_chi_in_react_type_list[i]][0][j][0];
			for (int k = 1; k < static_cast<int> (ene_distr_ene_out_data[pos_chi_in_react_type_list[i]][0][j].size()); k++)
			{
				ene_distr_ene_out_data_integ[pos_chi_in_react_type_list[i]][0][j][k] = ene_distr_ene_out_data_integ[pos_chi_in_react_type_list[i]][0][j][k - 1]
					+ (ene_distr_ene_out_data[pos_chi_in_react_type_list[i]][0][j][k - 1] + ene_distr_ene_out_data[pos_chi_in_react_type_list[i]][0][j][k])
					* (ene_distr_ene_out_ene_data[i][0][j][k] - ene_distr_ene_out_ene_data[i][0][j][k - 1]) / 2.0;
			}
		}
	}
}

// maruyama-b
////////////////////////////////////////////////////////////////////////////////////////////////////
//Perturbation for scattering angle distribution
////////////////////////////////////////////////////////////////////////////////////////////////////

void PerturbNuclearData::write_test()
{
        for(size_t j=0; j<static_cast<size_t>(angular_distr_ene_data[0].size()); j++)
        {
                for(size_t k=0; k<static_cast<size_t>(angular_distr_data[0][j].size()); k++)
                {
                        cout << angular_distr_data[0][j][k] << " " ;
                }
                cout << endl;
        }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PerturbNuclearData::save_elsct_angle_distr_obj()
{
        angular_distr_int_data0 = angular_distr_int_data;
        angular_distr_ene_data0 = angular_distr_ene_data; 
        angular_distr_cos_data0 = angular_distr_cos_data; 
        angular_distr_data0 = angular_distr_data; 
        angular_distr_data_integ0 = angular_distr_data_integ;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PerturbNuclearData::load_elsct_angle_distr_obj()
{
        angular_distr_int_data = angular_distr_int_data0;
        angular_distr_ene_data = angular_distr_ene_data0;
        angular_distr_cos_data = angular_distr_cos_data0;
        angular_distr_data = angular_distr_data0;
        angular_distr_data_integ = angular_distr_data_integ0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PerturbNuclearData::perturb_elsct_ang_distr()
{
        if (sample_flg == 0 && elsct_ang_flg== 0)
        {
		set_elsct_ang_union_ene_grid();
		linearize_elsct_ang_distr();
		normalize_elsct_ang_distr_pdf();
		set_elsct_ang_distr_cdf();
		//write_test();
                linearize_elsct_ang_distr_ene();
		normalize_elsct_ang_distr_pdf();
		set_elsct_ang_distr_cdf();
		//write_test();
		set_parameters_for_root_finding();
		set_cutoffs();

		save_elsct_angle_distr_obj();
        }
	else if (sample_flg != 0 && elsct_ang_flg== 0)
	{
		load_elsct_angle_distr_obj();
	}

	perturb_pdf_elsct_ang();
	elsct_ang_flg++;

	if (elsct_ang_flg == get_number_of_int(251, mt_list_input))
	{
		normalize_elsct_ang_distr_pdf();
		set_elsct_ang_distr_cdf();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PerturbNuclearData::linearize_elsct_ang_distr()
{
	Real angle_width = M_PI / elsct_ang_cos_points_at_each_order;
	for(size_t j = 0; j < static_cast<size_t>(angular_distr_ene_data[0].size()); j++)
	{
                if( angular_distr_pointer[0][j] < 0 ) // tabulate
                {
			vector<Real> angular_distr_cos_data_new(static_cast<size_t>(angular_distr_cos_data[0][j].size()));
			vector<Real> angular_distr_data_new(static_cast<size_t>(angular_distr_data[0][j].size()));
                        for(size_t k = 0; k < static_cast<size_t>(angular_distr_data[0][j].size()); k++)
                        {
				angular_distr_cos_data_new[k] = angular_distr_cos_data[0][j][k];
                                angular_distr_data_new[k] = angular_distr_data[0][j][k];
                        }
			angular_distr_cos_data[0][j].resize(elsct_ang_cos_points_at_each_order + 1);
			angular_distr_data[0][j].resize(elsct_ang_cos_points_at_each_order + 1);
			for(size_t k = 0; k < static_cast<size_t>(angular_distr_data[0][j].size()); k++)			
			{
				angular_distr_cos_data[0][j][k] = cos( -M_PI + k * angle_width );
				int i_m=0;
				int i_p=0;
				search_neighbor_value(angular_distr_cos_data[0][j][k], angular_distr_cos_data_new, i_m, i_p);
				if( i_m < 0 )
				{
					angular_distr_data[0][j][k] = 0.0;
				}
				else if(i_p < 0)
				{
					if( fabs(angular_distr_cos_data[0][j][k] == angular_distr_cos_data_new[static_cast<size_t> (angular_distr_cos_data_new.size()-1)]) )
					{
						if (angular_distr_int_data[0][j] == 2)
						{
							angular_distr_data[0][j][k] = angular_distr_data_new[static_cast<size_t> (angular_distr_data_new.size()-1)];
						}
						else if (angular_distr_int_data[0][j] == 1)
						{
							angular_distr_data[0][j][k] = angular_distr_data_new[static_cast<size_t> (angular_distr_data_new.size()-2)];
						}
					}
					else
					{
						angular_distr_data[0][j][k] = 0.0;
					}
				}
				else
				{
					if (angular_distr_int_data[0][j] == 1)
					{
						angular_distr_data[0][j][k] = angular_distr_data_new[i_m];
					}
					else if (angular_distr_int_data[0][j] == 2)
					{
						angular_distr_data[0][j][k] = angular_distr_data_new[i_m] + (angular_distr_cos_data[0][j][k] - angular_distr_cos_data_new[i_m]) * (angular_distr_data_new[i_p] - angular_distr_data_new[i_m]) / (angular_distr_cos_data_new[i_p] - angular_distr_cos_data_new[i_m]);
					}
					else
					{
						cout << "JJ is not 1 or 2. Please confirm JJ parameter in ACE file" << endl;
						exit(0);
					}                  
				}
			}
			angular_distr_int_data[0][j] = 2;
                }
                else if ( angular_distr_pointer[0][j] > 0 ) // 32 equiprobable bin
                {
			vector<Real> angular_distr_cos_data_new(33);
                        vector<Real> angular_distr_data_new(33);
			angular_distr_cos_data_new[0] = angular_distr_cos_data[0][j][0];
			for(size_t k = 0; k < 32; k++)
			{
				angular_distr_cos_data_new[k+1] = angular_distr_cos_data[0][j][k+1];
				angular_distr_data_new[k] = 1.0/(32.0*(angular_distr_cos_data_new[k+1] - angular_distr_cos_data_new[k]));
			}
			angular_distr_data_new[32] = 1.0/(32.0*(angular_distr_cos_data[0][j][32] - angular_distr_cos_data[0][j][31]));

			angular_distr_cos_data[0][j].resize(elsct_ang_cos_points_at_each_order + 1);
			angular_distr_data[0][j].resize(elsct_ang_cos_points_at_each_order + 1);
			for(size_t k = 0; k < static_cast<size_t>(angular_distr_data[0][j].size()); k++)
			{
				angular_distr_cos_data[0][j][k] = cos( -M_PI + k * angle_width );
				int i_m=0;
				int i_p=0;
				search_neighbor_value(angular_distr_cos_data[0][j][k], angular_distr_cos_data_new, i_m, i_p);
				if( i_m < 0 )
				{
					angular_distr_data[0][j][k] = 0.0;
				}
				else if ( i_p < 0 )
				{
					if( fabs(angular_distr_cos_data[0][j][k] == angular_distr_cos_data_new[static_cast<size_t> (angular_distr_cos_data_new.size()-1)]) )
                                        {
                                                angular_distr_data[0][j][k] = angular_distr_data_new[static_cast<size_t> (angular_distr_data_new.size()-2)];
                                        }
                                        else
                                        {
                                                angular_distr_data[0][j][k] = 0.0;
                                        }
				}
				else
				{
					angular_distr_data[0][j][k] = angular_distr_data_new[i_m];
				}
			}
			angular_distr_int_data[0][j] = 2;
                }
                else if ( angular_distr_pointer[0][j] == 0 ) // isotropic
                {
			angular_distr_cos_data[0][j].resize(elsct_ang_cos_points_at_each_order + 1);
			angular_distr_data[0][j].resize(elsct_ang_cos_points_at_each_order + 1);
			for(size_t k = 0; k < static_cast<size_t>(angular_distr_data[0][j].size()); k++)
			{
				angular_distr_cos_data[0][j][k] = cos( -M_PI + k * angle_width );
				angular_distr_data[0][j][k] = 0.5; 
			}
			angular_distr_int_data[0][j] = 2;
                }
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PerturbNuclearData::search_neighbor_value(Real& x_real, vector<Real>& x_data, int& i_m, int& i_p)
{
	int x_min = 0;
	int x_max = static_cast<int>(x_data.size()) - 1;
	int x_mid = (x_min + x_max)/2;

	i_m = 0;
	i_p = 0;

	if( x_real >= x_data[x_max] )
	{
		i_p = -1;
	}
	else if( x_real < x_data[x_min] )
	{
		i_m = -1;
	}
	else
	{
		while( x_max - x_min >= 2)
		{
			if(x_data[x_mid] <= x_real )
			{
				x_min = x_mid;
			}
			else
			{
				x_max = x_mid;
			}
			x_mid = (x_min + x_max)/2;
		}
		i_m = x_min;
		i_p = x_max;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PerturbNuclearData::normalize_elsct_ang_distr_pdf()
{
	for (size_t j = 0; j < static_cast<size_t>(angular_distr_ene_data[0].size()); j++)
	{
		Real integrate_pdf = 0.0;
		for (size_t k = 1; k < static_cast<size_t> (angular_distr_data[0][j].size()); k++) 
		{
			integrate_pdf += (angular_distr_data[0][j][k-1] + angular_distr_data[0][j][k])
                                            * (angular_distr_cos_data[0][j][k] - angular_distr_cos_data[0][j][k-1]) / 2.0;
		}
		for (size_t k = 0; k < static_cast<size_t> (angular_distr_data[0][j].size()); k++)
		{
			angular_distr_data[0][j][k] /= integrate_pdf;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PerturbNuclearData::set_elsct_ang_distr_cdf()
{
	angular_distr_data_integ[0].resize(static_cast<size_t> (angular_distr_ene_data[0].size()));
	for (size_t j = 0; j < static_cast<size_t>(angular_distr_ene_data[0].size()); j++)
	{
		angular_distr_data_integ[0][j].resize(static_cast<size_t> (angular_distr_data[0][j].size()));
		angular_distr_data_integ[0][j][0] = 0.0;
		for (size_t k = 1; k < static_cast<size_t> (angular_distr_data_integ[0][j].size()); k++)
		{
			angular_distr_data_integ[0][j][k] = angular_distr_data_integ[0][j][k-1]
				+ (angular_distr_data[0][j][k-1] + angular_distr_data[0][j][k])
				* (angular_distr_cos_data[0][j][k] - angular_distr_cos_data[0][j][k-1]) / 2.0;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PerturbNuclearData::set_elsct_ang_union_ene_grid()
{
        vector<Real> elsct_ang_union_ene_grid_log10(1);
        Real Emin_in_elsct_ang_ene_grid = union_ene_grid[0];
        Real Emax_in_elsct_ang_ene_grid = union_ene_grid[static_cast<int> (union_ene_grid.size() - 1)];

	if (angular_distr_ene_data[0][0] < Emin_in_elsct_ang_ene_grid)
	{
		Emin_in_elsct_ang_ene_grid = angular_distr_ene_data[0][0];
	}
	if (angular_distr_ene_data[0][static_cast<int> (angular_distr_ene_data[0].size() - 1)] > Emax_in_elsct_ang_ene_grid)
	{ 
		Emax_in_elsct_ang_ene_grid = angular_distr_ene_data[0][static_cast<int> (angular_distr_ene_data[0].size() - 1)];
	}

        elsct_ang_union_ene_grid_log10[0] = log10(Emin_in_elsct_ang_ene_grid);
        Real energy_width_log10 = 1.0 / elsct_ang_ene_points_at_each_order;
        while (elsct_ang_union_ene_grid_log10[static_cast<int> (elsct_ang_union_ene_grid_log10.size() - 1)] < log10(Emax_in_elsct_ang_ene_grid))
        {
                Real new_ene = elsct_ang_union_ene_grid_log10[static_cast<int> (elsct_ang_union_ene_grid_log10.size() - 1)] + energy_width_log10;
                elsct_ang_union_ene_grid_log10.push_back(new_ene);
        }
        elsct_ang_union_ene_grid.resize(static_cast<int> (elsct_ang_union_ene_grid_log10.size()));
        for (size_t i = 0; i < static_cast<size_t> (elsct_ang_union_ene_grid_log10.size()); i++)
        {
                elsct_ang_union_ene_grid[i] = pow(10, elsct_ang_union_ene_grid_log10[i]);
        }
        if (elsct_ang_union_ene_grid[static_cast<int> (elsct_ang_union_ene_grid.size() - 1)] > Emax_in_elsct_ang_ene_grid)
        {
                elsct_ang_union_ene_grid[static_cast<int> (elsct_ang_union_ene_grid.size() - 1)] = Emax_in_elsct_ang_ene_grid;
        }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PerturbNuclearData::linearize_elsct_ang_distr_ene()
{
	vector<Real> angular_distr_ene_data_new(static_cast<size_t> (angular_distr_ene_data[0].size()));
	vector<vector<Real>> angular_distr_cos_data_new(static_cast<size_t> (angular_distr_cos_data[0].size()), vector<Real>(static_cast<size_t> (angular_distr_cos_data[0][0].size())));
	vector<vector<Real>> angular_distr_data_new(static_cast<size_t> (angular_distr_data[0].size()), vector<Real>(static_cast<size_t> (angular_distr_data[0][0].size())));
	for(size_t j = 0; j < static_cast<size_t>(angular_distr_ene_data[0].size()); j++)
	{
		angular_distr_ene_data_new[j] = angular_distr_ene_data[0][j];
		for(size_t k = 0; k < static_cast<size_t>(angular_distr_data[0][j].size()); k++)
		{
			angular_distr_cos_data_new[j][k] = angular_distr_cos_data[0][j][k];
			angular_distr_data_new[j][k] = angular_distr_data[0][j][k];
		}
	}
	angular_distr_int_data[0].resize(static_cast<size_t> (elsct_ang_union_ene_grid.size()));
	angular_distr_ene_data[0].resize(static_cast<size_t> (elsct_ang_union_ene_grid.size()));
	angular_distr_cos_data[0].resize(static_cast<size_t> (elsct_ang_union_ene_grid.size()));
	angular_distr_data[0].resize(static_cast<size_t> (elsct_ang_union_ene_grid.size()));
	for(size_t j = 0; j < static_cast<size_t>(elsct_ang_union_ene_grid.size()); j++)
	{
		angular_distr_cos_data[0][j].resize(static_cast<size_t> (elsct_ang_cos_points_at_each_order + 1) );
		angular_distr_data[0][j].resize(static_cast<size_t> (elsct_ang_cos_points_at_each_order + 1));
		for(size_t k = 0; k < static_cast<size_t>(elsct_ang_cos_points_at_each_order + 1); k++)
		{
			angular_distr_cos_data[0][j][k] = angular_distr_cos_data_new[0][k];
			int i_m=0;
			int i_p=0;
			search_neighbor_value(elsct_ang_union_ene_grid[j], angular_distr_ene_data_new, i_m, i_p);
			if( i_m < 0)
			{
				angular_distr_data[0][j][k] = angular_distr_data_new[0][k];
			}
			else if(i_p < 0)
			{
				angular_distr_data[0][j][k] = angular_distr_data_new[static_cast<size_t> (angular_distr_data_new.size()-1)][k];
			}
			else
			{
				angular_distr_data[0][j][k] = angular_distr_data_new[i_m][k] + (elsct_ang_union_ene_grid[j] - angular_distr_ene_data_new[i_m]) * (angular_distr_data_new[i_p][k] - angular_distr_data_new[i_m][k]) / (angular_distr_ene_data_new[i_p] - angular_distr_ene_data_new[i_m]);
			}	
		}
		angular_distr_int_data[0][j] = 2;
		angular_distr_ene_data[0][j] = elsct_ang_union_ene_grid[j];
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PerturbNuclearData::perturb_pdf_elsct_ang()
{
	set_ene_pos(angular_distr_ene_data[0]);
	if (pos_Emin >= 0 && pos_Emax >= 0)
        {
                for (size_t j = 0; j < static_cast<size_t> (pos_Emax - pos_Emin + 1); j++)
                {
                        mubar = mubar0[j + pos_Emin] * multiplier;
			pdf = angular_distr_data[0][j + pos_Emin];
			xi = xi0[j + pos_Emin];
			eta = eta0[j + pos_Emin];
			zeta = zeta0[j + pos_Emin];

			if (multiplier == 1.0)
			{
				continue;
			}
			else if (mubar <= lower)
			{
				angular_distr_data[0][j + pos_Emin][0] = 1.0;
				for (size_t k = 1; k < static_cast<size_t>(angular_distr_cos_data[0][j].size()); k++)	
				{
					angular_distr_data[0][j + pos_Emin][k] = 0.0;
				}

			}
			else if (mubar >= upper)
			{
				for (size_t k = 0; k < static_cast<size_t>(angular_distr_cos_data[0][j].size()-1); k++)
                                {
                                        angular_distr_data[0][j + pos_Emin][k] = 0.0;
                                }
				angular_distr_data[0][j + pos_Emin][static_cast<size_t>(angular_distr_cos_data[0][j].size()-1)] = 1.0;
			}
			else
			{
				solve_lambda();
				//cout << "mubar = " << mubar0[j + pos_Emin] << ", " << "mubar_i = " << mubar << ", " << "lambda = " << lambda << endl;
				for (size_t k = 0; k < static_cast<size_t>(angular_distr_cos_data[0][j].size()); k++)
                                {
					angular_distr_data[0][j + pos_Emin][k] = pdf[k] * exp(- lambda * eta[k] );
				}
			}
                }
        }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PerturbNuclearData::set_parameters_for_root_finding()
{
	mubar0.resize(angular_distr_ene_data[0].size());
	xi0.resize(angular_distr_ene_data[0].size());
	eta0.resize(angular_distr_ene_data[0].size());
	zeta0.resize(angular_distr_ene_data[0].size());
	for (size_t j = 0; j < static_cast<size_t>(angular_distr_ene_data[0].size()); j++)
	{
		vector<Real> mu = angular_distr_cos_data[0][j];
		vector<Real> mu_p = angular_distr_cos_data[0][j];
		vector<Real> mu_m = angular_distr_cos_data[0][j];
		mu_p.erase(mu_p.begin());
 		mu_p.push_back(mu_p[static_cast<size_t> (mu_p.size()-1)]);
		mu_m.pop_back();
		mu_m.insert(mu_m.begin(),mu_m[0]);
		xi0[j].resize(angular_distr_data[0][j].size());
		eta0[j].resize(angular_distr_data[0][j].size());
		zeta0[j].resize(angular_distr_data[0][j].size());
		mubar0[j] = 0.0;
		for (size_t k = 0; k < static_cast<size_t>(angular_distr_data[0][j].size()); k++)
		{
			Real temp1 = (mu_p[k] - mu_m[k])/2.0;
			Real temp2 = (mu_p[k] + mu[k] + mu_m[k])/3.0;
			Real temp3 = temp1*temp2;
			xi0[j][k] = temp1;
			eta0[j][k] = temp2;
			zeta0[j][k] = temp3;
			mubar0[j] += angular_distr_data[0][j][k]*temp3;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PerturbNuclearData::set_cutoffs()
{
	lower = (2.0 * angular_distr_cos_data[0][0][0] + angular_distr_cos_data[0][0][1])/3.0;
	upper = (2.0 * angular_distr_cos_data[0][0][static_cast<size_t> (angular_distr_cos_data[0][0].size()-1)] + angular_distr_cos_data[0][0][static_cast<size_t> (angular_distr_cos_data[0][0].size()-2)])/3.0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PerturbNuclearData::set_function(double const& x)
{
	Real f01 = 0.0;
	Real f02 = 0.0;
	Real f11 = 0.0;
	Real f12 = 0.0;
	Real f21 = 0.0;
	Real f22 = 0.0;
	for (size_t k=0; k < static_cast<size_t> (pdf.size()); k++)
	{
		f01 += zeta[k] * pdf[k] * exp(-x * eta[k]);	
		f02 += xi[k] * pdf[k] * exp(-x * eta[k]);
		f11 += -eta[k] * zeta[k] * pdf[k] * exp(-x * eta[k]);
		f12 += -eta[k] * xi[k] * pdf[k] * exp(-x * eta[k]);
		f21 += eta[k] * eta[k] * zeta[k] * pdf[k] * exp(-x * eta[k]);
		f22 += eta[k] * eta[k] * xi[k] * pdf[k] * exp(-x * eta[k]);
	}
	g0 = f01 - mubar * f02;
	g1 = f11 - mubar * f12;
	g2 = f21 - mubar * f22;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PerturbNuclearData::solve_lambda()
{
	const int max_value = log(numeric_limits<Real>::max()); // To avoid numerical overflow
	const int digits = std::numeric_limits<Real>::digits;
	Real guess = 0.0; 
	Real get_min = -max_value;
	Real get_max = max_value;
	int get_digits = static_cast<int>(digits * 0.4);    // Accuracy 
	uintmax_t maxit = 20;
 
	lambda = boost::math::tools::halley_iterate( [&](const double& x)
	{
		set_function(x);
		//cout << g0 << " " << g1 << " " << g2 << endl;
		return make_tuple(g0,g1,g2);
	},guess, get_min, get_max, get_digits, maxit );
}

// maruyama-e

////////////////////////////////////////////////////////////////////////////////////////////////////

// Tools
////////////////////////////////////////////////////////////////////////////////////////////////////

vector<vector<Real>> PerturbNuclearData::get_2d_vec_d(string filename)
{
	//cout << "Reading file        : " << filename << endl;
	ifstream file(filename);
	if (file.fail())
	{
		cout << "File name : " << filename << endl;
		cout << "This file name cannot be read." << endl;
		exit(0);
	}

	string                line;   //1 line
	string::size_type     words;
	vector<vector<double> > input_value; //Array of text data

	int blank_no = 0;
	while (getline(file, line)) //Read 1 line in input file
	{
		erase_space_in_string_line(line); //Remove space data before and after character
		if (static_cast<int>(line.size()) == 0)
		{
			blank_no++;
			if( blank_no > 100000000 )
			{
				cout << "File name : " << filename << endl;
				cout << "A huge number of blank line data is found." << endl;
				cout << "The file name may not be the directory name." << endl;
				cout << "Please check the file name is collect or not." << endl;
				cout << "This program recognizes that after // is comment line." << endl;
				cout << "Please check that the file name contains // or not." << endl;
				exit(0);
			}

			continue;
		}
		else
		{
			blank_no = 0;
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
	//cout << "Finish reading file : " << filename << endl;
	return input_value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> PerturbNuclearData::get_1d_vec_s(string filename)
{
	//cout << "Reading file        : " << filename << endl;
	ifstream file(filename);
	if (file.fail())
	{
		cout << "File name : " << filename << endl;
		cout << "This file name cannot be read." << endl;
		exit(0);
	}

	string                line;   //1 line
	string::size_type     words;
	vector<string> input_value; //Array of text data

	while (getline(file, line)) //Read 1 line in input file
	{
		erase_space_in_string_line(line); //Remove space data before and after character
		if (static_cast<int>(line.size()) == 0)
		{
			continue;
		}

		words = line.find(","); //Serach position of "," in each line
		while (words != string::npos)
		{
			string str_data = line.substr(0, words);               //Clip text data before ","
			input_value.push_back(str_data);
			//double value = stod(str_data); //Change string data to real data
			//line_value_vec.push_back(value);                       //Add clip data before","

			line = line.substr(words + 1);        //Remove string data before ","
			erase_space_in_string_line(line); //Remove space data before and after character
			words = line.find(",");               //Serach position of "," in each line
		}

		if (static_cast<int>(line.size()) > 0) //Add string data after ","
		{
			string str_data = line.substr(0, words);
			//double value = stod(str_data);
			input_value.push_back(str_data);
		}
	}
	//cout << "Finish reading file : " << filename << endl;
	return input_value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PerturbNuclearData::erase_space_in_string_line(string& line)
{
	for (size_t first_space = line.find_first_of(" "); first_space != string::npos;
		first_space = line.find_first_of(" "))
	{
		line.erase(first_space, 1);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PerturbNuclearData::remove_same_value_1d_vec_i(vector<Integer>& vec_1i)
{
	//sort(vec_1i.begin(), vec_1i.end());
	vector<Integer> vec_1i_new = { vec_1i[0] };
	for (int i = 1; i < static_cast<int>(vec_1i.size()); i++)
	{
		//if (vec_1i[i] != vec_1i[i - 1])
		if (check_same_value_1d_vec_i(vec_1i[i], vec_1i_new) == 0)
		{
			vec_1i_new.push_back(vec_1i[i]);
		}
	}
	vec_1i.resize(static_cast<int>(vec_1i_new.size()));
	vec_1i = vec_1i_new;
	vector<int>().swap(vec_1i_new);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Integer PerturbNuclearData::check_same_value_1d_vec_i(Integer value, vector<Integer> vec_1i)
{
	int flg;
	for (int i = 0; i < static_cast<int>(vec_1i.size()); i++)
	{
		if (vec_1i[i] == value)
		{
			flg = 1;
			break;
		}
		else
		{
			flg = 0;
		}
	}
	return flg;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Integer PerturbNuclearData::check_same_value_1d_vec_d(Real value, vector<Real> vec_1d)
{
	int flg;
	for (int i = 0; i < static_cast<int>(vec_1d.size()); i++)
	{
		if (vec_1d[i] == value)
		{
			flg = 1;
			break;
		}
		else
		{
			flg = 0;
		}
	}
	return flg;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<Real> PerturbNuclearData::get_vec_in_react_xs(Integer MT)
{
	for (int i = 0; i < static_cast<int>(react_type_list.size()); i++)
	{
		if (MT == react_type_list[i])
		{
			return react_xs[i];
		}
	}

  vector<Real> vec_void;
  return vec_void;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Integer PerturbNuclearData::get_pos_in_react_xs(Integer MT)
{
	for (int i = 0; i < static_cast<int>(react_type_list.size()); i++)
	{
		if (MT == react_type_list[i])
		{
			return i;
			break;
		}
	}
  return -1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Integer PerturbNuclearData::get_number_of_int(Integer number, vector<Integer>& vec)
{
	vector<Integer> vec_new = vec;
	Integer count = 0;
	for (size_t i = 0; i < static_cast<size_t>(vec.size()); i++)
	{
		if (vec_new[static_cast<int>(vec_new.size()) - 1] == number)
		{
			count++;
		}
		vec_new.pop_back();
	}

	return count;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Write new ace file
////////////////////////////////////////////////////////////////////////////////////////////////////

void PerturbNuclearData::set_perturbed_ace_obj()
{
	ace_obj.set_union_ene_grid(union_ene_grid);
	ace_obj.set_react_xs_tot(react_xs_tot);
	ace_obj.set_react_xs_cap(react_xs_cap);
	ace_obj.set_react_xs_sc(react_xs_sc);
	ace_obj.set_react_xs(react_xs);

        ace_obj.set_unreso_prob_tab_ene(p_tab_ene);
        ace_obj.set_unreso_prob_tab_heat(p_tab_heat);
        ace_obj.set_unreso_prob_tab_sample_no(p_tab_sample_no);
        ace_obj.set_unreso_prob_tab_table(p_tab);

	ace_obj.set_nu_data(nu_data);
	ace_obj.set_nu_ene_data(nu_ene_data);
	ace_obj.set_nu_int_data(nu_int_data);
	ace_obj.set_nu_range_data(nu_range_data);
	ace_obj.set_nu_bar_repr_flg(nu_bar_repr_flg);

	ace_obj.set_nu_d_data(nu_d_data);
	ace_obj.set_nu_d_ene_data(nu_d_ene_data);
	ace_obj.set_nu_d_int_data(nu_d_int_data);
	ace_obj.set_nu_d_range_data(nu_d_range_data);
	ace_obj.set_nu_d_bar_repr_flg(nu_d_bar_repr_flg);

	ace_obj.set_nu_p_data(nu_p_data);
	ace_obj.set_nu_p_ene_data(nu_p_ene_data);
	ace_obj.set_nu_p_int_data(nu_p_int_data);
	ace_obj.set_nu_p_range_data(nu_p_range_data);
	ace_obj.set_nu_p_bar_repr_flg(nu_p_bar_repr_flg);


	ace_obj.set_ene_distr_ene_repr_flg(ene_distr_ene_repr_flg);

	ace_obj.set_ene_distr_ene_in_int_data(ene_distr_ene_in_int_data);
	ace_obj.set_ene_distr_ene_in_range_data(ene_distr_ene_in_range_data);
	ace_obj.set_ene_distr_ene_in_data(ene_distr_ene_in_data);
	ace_obj.set_ene_distr_ene_out_int_data(ene_distr_ene_out_int_data);
	ace_obj.set_ene_distr_ene_out_ene_data(ene_distr_ene_out_ene_data);
	ace_obj.set_ene_distr_ene_out_data(ene_distr_ene_out_data);
	ace_obj.set_ene_distr_ene_out_data_integ(ene_distr_ene_out_data_integ);

	ace_obj.set_ene_distr_upper_ene_limit(ene_distr_upper_ene_limit);
	ace_obj.set_ene_distr_temp_eff_int_data(ene_distr_temp_eff_int_data);
	ace_obj.set_ene_distr_temp_eff_range_data(ene_distr_temp_eff_range_data);
	ace_obj.set_ene_distr_temp_eff_ene_data(ene_distr_temp_eff_ene_data);
	ace_obj.set_ene_distr_temp_eff_data(ene_distr_temp_eff_data);

// maruyama-b
	ace_obj.set_angular_distr_int_data(angular_distr_int_data);
	ace_obj.set_angular_distr_ene_data(angular_distr_ene_data);
	ace_obj.set_angular_distr_cos_data(angular_distr_cos_data);
	ace_obj.set_angular_distr_data(angular_distr_data);
	ace_obj.set_angular_distr_data_integ(angular_distr_data_integ);
// maruyama-e

}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PerturbNuclearData::write_ace_file_test()
{
	cout << "  Writing ACE file ..... " << endl;
	string output_ace_file_name = ace_file_name + ".test";
	string output_xs_dir_name = output_ace_file_name + ".xsdir";
	cout << "  ACE file name   : " << output_ace_file_name << endl;;
	cout << "  XSDIR file name : " << output_xs_dir_name << endl;;
	wri_obj.set_ace_file_name(output_ace_file_name);
	wri_obj.set_ace_data_obj(ace_obj);
	wri_obj.write_ace_format();
	wri_obj.write_dir_data(output_xs_dir_name);
	wri_obj.clear();
	ace_obj.clear();
	cout << "finished." << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PerturbNuclearData::write_ace_file()
{
	cout << "Writing ACE file ..... " << endl;

	//if (perturbation_file_name.find(".csv") != string::npos)
	//{
	//	int pos = perturbation_file_name.find(".csv");
	//	index = perturbation_file_name.substr(pos - 4, 4);
	//}
	//else
	//{
	//	cout << "Perturbation input file must be like \"ZZAAA_????csv\"" << endl;
	//	exit(0);
	//}

	index = perturbation_file_name.substr(perturbation_file_name.length() - 4, 4);

	string base_name = file_mod_obj.get_file_name(ace_file_name);

#ifdef _WIN32
	_mkdir(index.c_str());
	output_ace_file_name = index + "\/" + base_name + "_" + index; //0001/92235.710nc_0001
#else
	mkdir(index.c_str(), S_IRWXU);
	output_ace_file_name = index + "/" + base_name + "_" + index; //0001/92235.710nc_0001
#endif
	string output_xs_dir_name = output_ace_file_name + ".xsdir";

	cout << "  ACE file name   : " << output_ace_file_name << endl;;
	cout << "  XSDIR file name : " << output_xs_dir_name << endl;;

	wri_obj.set_ace_file_name(output_ace_file_name);
	wri_obj.set_ace_data_obj(ace_obj);
	wri_obj.write_ace_format();
	wri_obj.write_dir_data(output_xs_dir_name);
	wri_obj.clear();
	ace_obj.clear();
	cout << "finished." << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
