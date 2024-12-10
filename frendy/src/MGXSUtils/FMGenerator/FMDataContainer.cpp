#pragma once

#include "MGXSUtils/FMGenerator/FMDataContainer.h"

using namespace FMGen;

void FMDataContainer::readInput(FMInputData* _input_data)
{
	print1stHeader(" Read input data ");

	input_data = _input_data;

	vector<string> buf_vec;

	//set multigroup structure---------------------------------------------------------------
	input_data->findBlock("multi_group", 0);

	mg_energy_boundary.clear();
	input_data->getData(buf_vec);
	if (compareString(buf_vec[0], "auto"))
	{
		vector<REAL>   e_bd;
		vector<int>    e_num;
		vector<string> e_opt;
		for (;;)
		{

			input_data->getData(buf_vec);
			if (input_data->isEndOfBlock(buf_vec[0])) break;
			e_bd.push_back(my_stod(buf_vec[0]));
			if (buf_vec.size() != 1)
			{
				e_num.push_back(my_stoi(buf_vec[1]));
				e_opt.push_back(buf_vec[2]);
			}
		}
		for (int i = 0; i < static_cast<int>(e_num.size()); i++)
		{
			int ediv = eFMEquiLethagyDivision;
			if (compareString(e_opt[i], "EE"))	ediv = eFMEquiEnergyDivision;
			for (int j = 0; j < e_num[i]; j++)
			{
				if (ediv == eFMEquiEnergyDivision)
				{
					REAL delta = (e_bd[i] - e_bd[i + 1]) / REAL(e_num[i]);
					REAL wk = e_bd[i] - delta * REAL(j);
					mg_energy_boundary.push_back(wk);
				}
				else
				{
					REAL delta = log(e_bd[i] / e_bd[i + 1]) / REAL(e_num[i]);
					REAL wk = e_bd[i] / exp(delta * REAL(j));
					mg_energy_boundary.push_back(wk);
				}
			}
		}
		mg_energy_boundary.push_back(e_bd.back());
	}
	else
	{
		input_data->prev();
		for (;;)
		{

			input_data->getData(buf_vec);
			if (input_data->isEndOfBlock(buf_vec[0])) break;
			for (int i = 0; i < static_cast<int>(buf_vec.size()); i++)
				mg_energy_boundary.push_back(my_stod(buf_vec[i]));
		}
	}

	sort(mg_energy_boundary.begin(), mg_energy_boundary.end());
	reverse(mg_energy_boundary.begin(), mg_energy_boundary.end());
	mg_max_num_energy = mg_energy_boundary.size() - 1;

	//default spectrum--------------------------------------------------------------------------
	weighting_spectrum.setIESpectrum();		//default value;
	input_data->findBlock("default_spectrum", 0);
	vector<REAL> ene_grid_wk, flux_wk;
	ene_grid_wk.clear();
	flux_wk.clear();
	input_data->getData(buf_vec);
	if (compareString(buf_vec[0], "input"))
	{
		for (;;)
		{
			input_data->getData(buf_vec);
			if (input_data->isEndOfBlock(buf_vec[0])) break;
			ene_grid_wk.push_back(my_stod(buf_vec[0]));
			flux_wk.push_back(my_stod(buf_vec[1]));
		}
		weighting_spectrum.setInputSpectrum(ene_grid_wk, flux_wk);
	}
	else if (compareString(buf_vec[0], "1/E"))
	{
		weighting_spectrum.setIESpectrum();
	}
	else if (compareString(buf_vec[0], "Fission+1/E+Maxwell"))
	{
		input_data->getData(buf_vec);
		REAL upper, lower, fis_temp, maxwell_temp, fcut, tcut;
		if (input_data->isEndOfBlock(buf_vec[0]))
		{
			upper = 2.0e+7;		//[eV]
			lower = 1.0e-5;		//[eV]
			fis_temp = 0.0;		//[eV]
			maxwell_temp = 0.0;	//[K]
			fcut = 0.0;			//[eV]
			tcut = 0.0;			//[eV]
		}
		else
		{
			if (buf_vec.size() < 6) printError(" Number of input data (parameters) in default_spectrum should be 6");
			upper = my_stod(buf_vec[0]);
			lower = my_stod(buf_vec[1]);
			fis_temp = my_stod(buf_vec[2]);
			maxwell_temp = my_stod(buf_vec[3]);
			fcut = my_stod(buf_vec[4]);
			tcut = my_stod(buf_vec[5]);
			if (upper < lower) printError(" upper energy input in default_spectrum is smaller than lower energy");
		}
		weighting_spectrum.setIEFisMaxwellSpectrum(upper, lower, fis_temp, maxwell_temp, fcut, tcut);
	}
	else
	{
		cout << " error in default_spectrum. option not found " << buf_vec[0] << endl;
		exit(0);
	}

	//material------------------------------------------------------------------------------------
	input_data->findBlock("material", 0);
	for (;;)
	{
		input_data->getData(buf_vec);
		if (input_data->isEndOfBlock(buf_vec[0])) break;
		if (buf_vec.size() == 2)
		{
			uf_region_data.nuc_name.push_back(buf_vec[0]);
			uf_region_data.sab_name.push_back("");
			uf_region_data.sab_type.push_back("");
			uf_region_data.nuc_dens.push_back(my_stod(buf_vec[1]));
		}
		else if (buf_vec.size() == 4)
		{
			uf_region_data.nuc_name.push_back(buf_vec[0]);
			uf_region_data.sab_name.push_back(buf_vec[1]);
			uf_region_data.sab_type.push_back(buf_vec[2]);
			uf_region_data.nuc_dens.push_back(my_stod(buf_vec[3]));
		}
		else
		{
			cout << " error in material. number of input data is not correct " << endl;
			exit(0);
		}

		if (checkAcceptedThermalSabName(uf_region_data.sab_type.back()) == false)
		{
			cout << "  Input S(a,b) : " << uf_region_data.sab_type.back() << endl;
			printError(" The above input S(a,b) cannot be processed in FRENDY/MG ");
		}
	}


	uf_region_data.num_nucl = uf_region_data.nuc_name.size();
	for (int i = 0; i < uf_region_data.num_nucl; i++)
		uf_region_data.nuc_dens_sum += uf_region_data.nuc_dens[i];
	
	//endf id------------------------------------------------------------------------------------
	if (input_data->findBlock("endf_id", 0))
	{
		endf_id_list.clear();
		for (;;)
		{
			input_data->getData(buf_vec);
			if (input_data->isEndOfBlock(buf_vec[0])) break;
			int wk = my_stoi(buf_vec[1]);
			endf_id_list.insert(make_pair(buf_vec[0], wk));
		}
	}

	//set maximum pl order-------------------------------------------------------------------------
	input_data->findBlock("max_pl", 0);
	input_data->getData(buf_vec);
	max_pl = my_stoi(buf_vec[0]);
	if (max_pl > MAX_PL)
	{
		cout << " Increase MAX_PL in FMGenerator_global.h " << endl;
		exit(0);
	}

	//set potential scattering xs------------------------------------------------------------------
	input_data->findBlock("potential_xs", 0);
	for (;;)
	{
		input_data->getData(buf_vec);
		if (input_data->isEndOfBlock(buf_vec[0])) break;
		if (potential_xs.find(buf_vec[0]) == potential_xs.end())
			potential_xs.insert(make_pair(buf_vec[0], my_stod(buf_vec[1])));
		else
			potential_xs[buf_vec[0]] = my_stod(buf_vec[1]);
	}

	//set calculation options--------------------------------------------------------------------
	input_data->findBlock("calc_cond", 0);
	input_data->getData(buf_vec);
	if (compareString(buf_vec[0], "SLD")) sld_calc_option = eFMSlowingDownCalc;
	else if (compareString(buf_vec[0], "NR")) sld_calc_option = eFMNarrowResonanceCalc;
	else
	{
		cout << " calc_cond is invalid in FMDataContainer::readInput " << endl;
		exit(0);
	}

	if (buf_vec.size() >= 2)
		moderator_aw = my_stod(buf_vec[1]);
	else
		moderator_aw = 0.999167;			//default value for hydrogen

	if (buf_vec.size() >= 3)
		e_upper_slowingdown_spectrum_input = my_stod(buf_vec[2]);
	else
		e_upper_slowingdown_spectrum_input = 1.0e+4;
	if (buf_vec.size() >= 4)
		e_lower_slowingdown_spectrum_input = my_stod(buf_vec[3]);
	else
		e_lower_slowingdown_spectrum_input = 1.0;
	if (e_upper_slowingdown_spectrum_input < e_lower_slowingdown_spectrum_input)
	{
		cout << " error in calc_cond " << endl;
		exit(0);
	}
	if (e_upper_slowingdown_spectrum_input > mg_energy_boundary[0])
	{
		cout << " error in calc_cond " << endl;
		exit(0);
	}
	if (e_lower_slowingdown_spectrum_input < mg_energy_boundary.back())
	{
		cout << " error in calc_cond " << endl;
		exit(0);
	}
	calc_thermal_xs = true;
	use_sct_option = false;
	for (;;)
	{
		input_data->getData(buf_vec);
		if (input_data->isEndOfBlock(buf_vec[0])) break;
		if (compareString(buf_vec[0], "NoThermalXS")) calc_thermal_xs = false;

		if (compareString(buf_vec[0], "UseSCT")) use_sct_option = true;
	}

	//set resonance up-scattering options----------------------------------------------------------
	if (input_data->findBlock("reso_upscat", 0))
	{
		ruc_zaid.clear();
		ruc_file_name.clear();
		ruc_option.clear();
		for (;;)
		{
			input_data->getData(buf_vec);
			if (input_data->isEndOfBlock(buf_vec[0])) break;
			if (buf_vec.size() < 2 || buf_vec.size() >= 4)
				printError(" Number of input data is not correct in reso_upscat");
			ruc_zaid.push_back(buf_vec[0]);
			ruc_file_name.push_back(buf_vec[1]);
			if (buf_vec.size() == 3 && compareString(buf_vec[2], "1D") == true)
				ruc_option.insert(make_pair(buf_vec[0], eFMRUC1D));
			else
				ruc_option.insert(make_pair(buf_vec[0], eFMRUCAll));
		}

		//read elastic scattering xs at 0K
		print2ndHeader(" Resonance up-scattering correction");
		cout << "  Elastic scattering cross section at 0 K " << endl << endl;
		cout << "      Zaid   Temperature (K)   Max. energy(eV)   Number of points   File name" << endl;
		cout << "  --------------------------------------------------------------------------------------- " << endl;
		ruc_ene_grid.resize(ruc_zaid.size());
		ruc_scat_xs.resize(ruc_zaid.size());
		for (int i = 0; i < (int)ruc_zaid.size(); i++)
		{
			//check file contents
			ifstream fin;
			fin.open(ruc_file_name[i]);
			if (!fin)
			{
				cout << " File name ";
				cout << ruc_file_name[i] << endl;;
				printError(" File specified in reso_upscat (see above) does not exist ");
			}
			string zaid;
			fin >> zaid;
			if (checkZaidForRUC(ruc_zaid[i], zaid) == false)
				printError(" zaid provided in reso_upscat is not consistent with zaid in the provided file ");
			REAL temp;
			fin >> temp;
			for (;;)
			{
				REAL val;
				fin >> val;
				if (fin.eof()) break;
				ruc_ene_grid[i].push_back(val);
				fin >> val;
				if (fin.eof()) break;
				ruc_scat_xs[i].push_back(val);
			}
			fin.close();

			cout << setw(11) << ruc_zaid[i];
			cout << fixed << setprecision(3) << setw(13) << temp;
			cout << scientific << setprecision(4);
			cout << setw(19) << ruc_ene_grid[i].back();
			cout << setw(19) << ruc_ene_grid[i].size();
			cout << "      " << ruc_file_name[i];
			cout << endl;
		}
		cout << endl;

		//set correspondance to uf_region_data
		uf_region_data.ruc_index.resize(uf_region_data.num_nucl);
		for (int i = 0; i < uf_region_data.num_nucl; i++)
		{
			int order = -1;
			for (int j = 0; j < (int)ruc_zaid.size(); j++)
			{
				if (compareString(ruc_zaid[j], uf_region_data.nuc_name[i]))
				{
					order = j;
					break;
				}
			}
			uf_region_data.ruc_index[i] = order;
		}
	}
	else
	{
		//no resonance up-scattering correction
		uf_region_data.ruc_index.resize(uf_region_data.num_nucl);
		for (int i = 0; i < uf_region_data.num_nucl; i++)
		{
			int order = -1;
			uf_region_data.ruc_index[i] = order;
		}
	}

	//set thermal cutoff---------------------------------------------------------------------------
	thermal_cutoff_ein = 0.0;
	input_data->findBlock("thermal_cutoff", 0);
	input_data->getData(buf_vec);
	if (buf_vec.size() == 1)
	{
		thermal_cutoff_ein = my_stod(buf_vec[0]);
		thermal_cutoff_eout = THERMAL_CUTOFF_MAX_DEFAULT;
	}
	else
	{
		thermal_cutoff_ein = my_stod(buf_vec[0]);
		thermal_cutoff_eout = my_stod(buf_vec[1]);
	}

	if (thermal_cutoff_ein < mg_energy_boundary[mg_max_num_energy-1])
	{
		cout << " Thermal cut-off (incident energy, eV) is low thus s(a,b) calculation skipped " << endl;
		cout << endl;
		calc_thermal_xs = false;
	}

	if (calc_thermal_xs)
	{
		if (thermal_cutoff_ein < mg_energy_boundary.back() || thermal_cutoff_ein > mg_energy_boundary[0])
		{
			cout << scientific;
			cout << " Thermal cut-off (incident energy, eV): " << thermal_cutoff_ein << endl;
			cout << " Highest energy of group structure    : " << mg_energy_boundary[0] << endl;
			cout << " Lowest  energy of group structure    : " << mg_energy_boundary.back() << endl;
			printError(" Thermal cut-off energy should be set within highest and lowest energy boundaries");
		}

		//adjust thermal cut-off for incoming energy to multi-group boundary
		REAL diff_min = 1.0e+10;
		int mg_min = mg_max_num_energy - 1;
		for (int i = 0; i <= mg_max_num_energy; i++)
		{
			REAL diff = abs(log(mg_energy_boundary[i]) - log(thermal_cutoff_ein));
			if (diff < diff_min)
			{
				diff_min = diff;
				mg_min = i;
			}
		}

		const REAL THEMAL_CUTOFF_MAX = 250.0;	//maximum value of thermal scattering treatment (eV)
		if (mg_energy_boundary[mg_min] < THEMAL_CUTOFF_MAX)
		{
			print2ndHeader(" Adjustment of thermal-cutoff");
			cout << scientific << setprecision(4);
			cout << " thermal cut-off is adjust from " << thermal_cutoff_ein << " [eV] to " << mg_energy_boundary[mg_min] << " [eV]";
			cout << " to be consistent with energy boundary. Nearest energy boundary is selected." << endl;
			cout << endl;
			thermal_cutoff_ein = mg_energy_boundary[mg_min];
		}
		else
		{
			cout << scientific;
			cout << " Thermal cut-off (incident energy, eV): " << thermal_cutoff_ein << endl;
			cout << " Maximum energy for thermal treatment : " << THEMAL_CUTOFF_MAX << endl;
			printError(" Thermal cut-off energy should be set less than maximum energy for thermal treatment.");
		}
	}

	//set thermal s(a,b) option for debug purpose --------------------------------------------------
	thermal_sab_torelance = THERMAL_SAB_INTEGRATE_TORELANCE;
	thermal_freegas_sab_option = eFMThermalFreegasSabExplicitIntegral;
	if (input_data->findBlock("thermal_sab", 0))
	{
		input_data->getData(buf_vec);
		if (buf_vec.size() == 1)
		{
			thermal_sab_torelance = my_stod(buf_vec[0]);
		}
		else
		{
			thermal_sab_torelance = my_stod(buf_vec[0]);
			if (compareString(buf_vec[1], "explicit")) thermal_freegas_sab_option = eFMThermalFreegasSabExplicitIntegral;
			if (compareString(buf_vec[1], "linear")) thermal_freegas_sab_option = eFMThermalFreegasSabLinearInterpolation;
			if (compareString(buf_vec[1], "quadratic")) thermal_freegas_sab_option = eFMThermalFreegasSabQuadraticInterpolation;
		}
	}

	//set background cross section sets---------------------------------------------------------------
	input_data->findBlock("bg_xs_set", 0);
	background_xs_set.clear();
	vector<REAL> background_xs_wk;
	input_data->getData(buf_vec);

	//default values
	auto_background_xs_setting = false;
	auto_background_xs_bg_eps = 1.0e-2;
	auto_background_xs_bg_maxnum = 30;
	auto_background_xs_bg_min = 1.0e-3;
	auto_background_xs_use_rr = false;
	auto_background_xs_cubic_int = true;
	auto_background_xs_bg_min_energy = 1.0;		//[eV]
	auto_background_xs_bg_max_energy = 1.0e+8;	//[eV]

	if (compareString(buf_vec[0], "auto") == true)
	{
		auto_background_xs_setting = true;
		if (buf_vec.size() >= 2)
			auto_background_xs_bg_eps = my_stod(buf_vec[1]);
		if (buf_vec.size() >= 3)
			auto_background_xs_bg_maxnum = my_stoi(buf_vec[2]);
		if (buf_vec.size() >= 4)
			auto_background_xs_bg_min = my_stod(buf_vec[3]);
		if (buf_vec.size() >= 5)
		{
			if (compareString(buf_vec[4], "rr") == true)
				auto_background_xs_use_rr = true;
		}
		if (buf_vec.size() >= 6)
		{
			if (compareString(buf_vec[5], "linear") == true)
				auto_background_xs_cubic_int = false;
		}
		if (buf_vec.size() >= 7)
			auto_background_xs_bg_min_energy = my_stod(buf_vec[6]);
		if (buf_vec.size() >= 8)
			auto_background_xs_bg_max_energy = my_stod(buf_vec[7]);
	}
	else
	{
		input_data->prev();
		for (;;)
		{
			input_data->getData(buf_vec);
			if (input_data->isEndOfBlock(buf_vec[0])) break;
			for (int i = 0; i < static_cast<int>(buf_vec.size()); i++)
				background_xs_wk.push_back(my_stod(buf_vec[i]));
		}
		sort(background_xs_wk.begin(), background_xs_wk.end());
		int n = background_xs_wk.size();
		for (int i = 0; i < n; i++)
			background_xs_set.push_back(background_xs_wk[n - 1 - i]);
		if (background_xs_set[0] < 9.9e+9)
		{
			cout << " maximum value of background cross section should be larger than or equal to 1.0e+10" << endl;
			exit(0);
		}
	}

	//add file name-------------------------------------------------------------------------------------
	file_add_name_ = "";
	_file_add_name = "";
	if(input_data->findBlock("file_add_name", 0) == true)
	{
		input_data->getData(buf_vec);
		file_add_name_ = buf_vec[0] + "_";
		_file_add_name = "_" + buf_vec[0];
	}

	//set edit cross sections----------------------------------------------------------------------------
	if (input_data->findBlock("edit_xs", 0) == false)
	{
		//default values
		vector<int> work;
		work.clear();
		edit_option.clear();
		work.push_back(0);
		work.push_back(-eMTMaximum);
		edit_option[eEditOption1DXS] = work;
		edit_option[eEditOption2DXS] = work;
		work.clear();
		edit_option[eEditOptionNuChi] = work;
		edit_option[eEditOptionMGFlux] = work;
		edit_option[eEditOptionKRAMXSMicro] = work;
		edit_option[eEditOptionKRAMXSMacro] = work;
		kram_current_weight_total = false;
		edit_option[eEditOptionMATXS] = work;
		edit_option[eEditOptionGENDF] = work;
	}
	else
	{
		for (;;)
		{
			input_data->getData(buf_vec);
			if (input_data->isEndOfBlock(buf_vec[0])) break;
			vector<int> work;
			work.clear();
			map<int, vector<int> >::iterator it;

			if (compareString(buf_vec[0], "All"))
			{
				work.clear();
				edit_option.clear();
				work.push_back(0);
				work.push_back(-eMTMaximum);
				edit_option[eEditOption1DXS] = work;
				edit_option[eEditOption2DXS] = work;
				edit_option[eEditOptionUFG1DXS] = work;
				edit_option[eEditOptionUFGInputGrid1DXS] = work;
				work.clear();
				edit_option[eEditOptionNuChi] = work;
				edit_option[eEditOptionMGFlux] = work;
				edit_option[eEditOptionUFG] = work;
				edit_option[eEditOptionRUC] = work;
				edit_option[eEditOptionKRAMXSMicro] = work;
				edit_option[eEditOptionKRAMXSMacro] = work;
				kram_current_weight_total = false;
				edit_option[eEditOptionMATXS] = work;
				edit_option[eEditOptionGENDF] = work;
			}
			else if (compareString(buf_vec[0], "Default"))
			{
				work.clear();
				edit_option.clear();
				work.push_back(0);
				work.push_back(-eMTMaximum);
				edit_option[eEditOption1DXS] = work;
				edit_option[eEditOption2DXS] = work;
				work.clear();
				edit_option[eEditOptionNuChi] = work;
				edit_option[eEditOptionMGFlux] = work;
				edit_option[eEditOptionKRAMXSMicro] = work;
				edit_option[eEditOptionKRAMXSMacro] = work;
				kram_current_weight_total = false;
				edit_option[eEditOptionMATXS] = work;
				edit_option[eEditOptionGENDF] = work;
			}
			else if (compareString(buf_vec[0], "1DXS"))
			{
				work.clear();
				if (buf_vec.size() == 1)
				{
					work.push_back(0);
					work.push_back(-eMTMaximum);
				}
				else
				{
					for (int i = 1; i < static_cast<int>(buf_vec.size()); i++)
						work.push_back(my_stoi(buf_vec[i]));
				}
				edit_option[eEditOption1DXS] = work;
			}
			else if (compareString(buf_vec[0], "-1DXS"))
			{
				it = edit_option.find(eEditOption1DXS);
				if (it != edit_option.end())
					edit_option.erase(it);
			}
			else if (compareString(buf_vec[0], "2DXS"))
			{
				work.clear();
				if (buf_vec.size() == 1)
				{
					work.push_back(0);
					work.push_back(-eMTMaximum);
				}
				else
				{
					for (int i = 1; i < static_cast<int>(buf_vec.size()); i++)
						work.push_back(my_stoi(buf_vec[i]));
				}
				edit_option[eEditOption2DXS] = work;
			}
			else if (compareString(buf_vec[0], "-2DXS"))
			{
				it = edit_option.find(eEditOption2DXS);
				if (it != edit_option.end())
					edit_option.erase(it);
			}
			else if (compareString(buf_vec[0], "UFG1DXS"))
			{
				work.clear();
				if (buf_vec.size() == 1)
				{
					work.push_back(0);
					work.push_back(-eMTMaximum);
				}
				else
				{
					for (int i = 1; i < static_cast<int>(buf_vec.size()); i++)
						work.push_back(my_stoi(buf_vec[i]));
				}
				edit_option[eEditOptionUFG1DXS] = work;
			}
			else if (compareString(buf_vec[0], "-UFG1DXS"))
			{
				it = edit_option.find(eEditOptionUFG1DXS);
				if (it != edit_option.end())
					edit_option.erase(it);
			}
			else if (compareString(buf_vec[0], "UFG1DXSInputGrid"))
			{
			work.clear();
			if (buf_vec.size() == 1)
			{
				work.push_back(0);
				work.push_back(-eMTMaximum);
			}
			else
			{
				for (int i = 1; i < static_cast<int>(buf_vec.size()); i++)
					work.push_back(my_stoi(buf_vec[i]));
			}
			edit_option[eEditOptionUFGInputGrid1DXS] = work;
			}
			else if (compareString(buf_vec[0], "-UFG1DXSInputGrid"))
			{
			it = edit_option.find(eEditOptionUFGInputGrid1DXS);
			if (it != edit_option.end())
				edit_option.erase(it);
			}
			else if (compareString(buf_vec[0], "RUC"))
			{
				work.clear();
				edit_option[eEditOptionRUC] = work;
			}
			else if (compareString(buf_vec[0], "-RUC"))
			{
				it = edit_option.find(eEditOptionRUC);
				if (it != edit_option.end())
					edit_option.erase(it);
			}
			else if (compareString(buf_vec[0], "NuChi"))
			{
				edit_option[eEditOptionNuChi] = work;
			}
			else if (compareString(buf_vec[0], "-NuChi"))
			{
				it = edit_option.find(eEditOptionNuChi);
				if (it != edit_option.end())
					edit_option.erase(it);
			}
			else if (compareString(buf_vec[0], "MGFlux"))
			{
				edit_option[eEditOptionMGFlux] = work;
			}
			else if (compareString(buf_vec[0], "-MGFlux"))
			{
				it = edit_option.find(eEditOptionMGFlux);
				if (it != edit_option.end())
					edit_option.erase(it);
			}
			else if (compareString(buf_vec[0], "UFG"))
			{
				edit_option[eEditOptionUFG] = work;
			}
			else if (compareString(buf_vec[0], "-UFG"))
			{
				it = edit_option.find(eEditOptionUFG);
				if (it != edit_option.end())
					edit_option.erase(it);
			}
			else if (compareString(buf_vec[0], "KRAMXS"))
			{
				//reset options
				it = edit_option.find(eEditOptionKRAMXSMicro);
				if (it != edit_option.end())
					edit_option.erase(it);
				it = edit_option.find(eEditOptionKRAMXSMacro);
				if (it != edit_option.end())
					edit_option.erase(it);
				kram_current_weight_total = false;

				if (buf_vec.size() == 1)
				{
					edit_option[eEditOptionKRAMXSMicro] = work;
					edit_option[eEditOptionKRAMXSMacro] = work;
				}
				else
				{
					for (int ii = 1; ii < (int)buf_vec.size(); ii++)
					{
						if (compareString(buf_vec[ii],"Micro"))
							edit_option[eEditOptionKRAMXSMicro] = work;
						else if (compareString(buf_vec[ii], "Macro"))
							edit_option[eEditOptionKRAMXSMacro] = work;
						else if (compareString(buf_vec[ii], "CurrentWeightTotalXS"))
							kram_current_weight_total = true;
					}
					if (edit_option.find(eEditOptionKRAMXSMicro) == edit_option.end() &&
						edit_option.find(eEditOptionKRAMXSMacro) == edit_option.end())
					{
						edit_option[eEditOptionKRAMXSMicro] = work;
						edit_option[eEditOptionKRAMXSMacro] = work;
					}
				}
			}
			else if (compareString(buf_vec[0], "-KRAMXS"))
			{
				it = edit_option.find(eEditOptionKRAMXSMicro);
				if (it != edit_option.end())
					edit_option.erase(it);
				it = edit_option.find(eEditOptionKRAMXSMacro);
				if (it != edit_option.end())
					edit_option.erase(it);
			}
			else if (compareString(buf_vec[0], "MATXS"))
			{
				edit_option[eEditOptionMATXS] = work;
			}
			else if (compareString(buf_vec[0], "-MATXS"))
			{
				it = edit_option.find(eEditOptionMATXS);
				if (it != edit_option.end())
					edit_option.erase(it);
			}
			else if (compareString(buf_vec[0], "FULLMATXS"))
			{
				edit_option[eEditOptionFullMATXS] = work;
			}
			else if (compareString(buf_vec[0], "-FULLMATXS"))
			{
				it = edit_option.find(eEditOptionFullMATXS);
				if (it != edit_option.end())
					edit_option.erase(it);
			}
			else if (compareString(buf_vec[0], "SIMPLEMATXS"))
			{
				edit_option[eEditOptionSimpleMATXS] = work;
			}
			else if (compareString(buf_vec[0], "-SIMPLEMATXS"))
			{
				it = edit_option.find(eEditOptionSimpleMATXS);
				if (it != edit_option.end())
					edit_option.erase(it);
			}
			else if (compareString(buf_vec[0], "GENDF"))
			{
				edit_option[eEditOptionGENDF] = work;
			}
			else if (compareString(buf_vec[0], "-GENDF"))
			{
				it = edit_option.find(eEditOptionGENDF);
				if (it != edit_option.end())
					edit_option.erase(it);
			}
			else if (compareString(buf_vec[0], "FULLGENDF"))
			{
				edit_option[eEditOptionFullGENDF] = work;
			}
			else if (compareString(buf_vec[0], "-FULLGENDF"))
			{
				it = edit_option.find(eEditOptionFullGENDF);
				if (it != edit_option.end())
					edit_option.erase(it);
			}
			else if (compareString(buf_vec[0], "SIMPLEGENDF"))
			{
				edit_option[eEditOptionSimpleGENDF] = work;
			}
			else if (compareString(buf_vec[0], "-SIMPLEGENDF"))
			{
				it = edit_option.find(eEditOptionSimpleGENDF);
				if (it != edit_option.end())
					edit_option.erase(it);
			}
			else if (compareString(buf_vec[0], "Debug"))
			{
				edit_option[eEditOptionDebug] = work;
			}
			else if (compareString(buf_vec[0], "SkipPrintout"))
			{
				edit_option[eEditOptionSkipPrintout] = work;
			}
			else if (compareString(buf_vec[0], "NoCheckResults"))
			{
				edit_option[eEditOptionNoCheckResults] = work;
			}
			else
			{
				print1stHeader(" Following edit_xs option do not match input data. Ignored.");
				cout << buf_vec[0];
			}
		}

		if (edit_option.size() == 0)
			printError(" No edit will be performed. Specify at least one edit item, e.g., MATXS");
	}

}
void FMDataContainer::readACEFiles( )
{
	vector<string> buf_vec;

	//set ace data--------------------------------------------------------------------------
	input_data->findBlock("ace_file", 0);
	for (;;)
	{
		input_data->getData(buf_vec);
		if (input_data->isEndOfBlock(buf_vec[0])) break;
		string fname = buf_vec[0];
		FMACECrossSectionProcessor        acexs;
		FMACEThermalCrossSectionProcessor acetxs;
		int id = readIZAWFromACEFile(fname);

		if (id == 0)
		{
			//ordinally ace file
			acexs.readHeaderData(fname);
			acexs.processHeaderData();
			string zaid = acexs.getZaid();
			if (ace_xs_data.find(zaid) != ace_xs_data.end())
			{
				cout << " zaid " << zaid << " already exist " << endl;
				exit(0);
			}
			ace_xs_data.insert(make_pair(zaid, acexs));
			ace_xs_data[zaid].readXSData();
			ace_xs_data[zaid].processXSData();
			ace_xs_data[zaid].getDLW();
		}
		else
		{
			//thermal ace file
			acetxs.readHeaderData(fname);
			acetxs.processHeaderData();
			string zaid = acetxs.getZaid();
			if (ace_thermal_xs_data.find(zaid) != ace_thermal_xs_data.end())
			{
				cout << " zaid " << zaid << " already exist " << endl;
				exit(0);
			}
			ace_thermal_xs_data.insert(make_pair(zaid, acetxs));
			ace_thermal_xs_data[zaid].readXSData();
			ace_thermal_xs_data[zaid].processXSData();

			//effective temperature for short collision time approximation
			REAL temp = ace_thermal_xs_data[zaid].getKelvin();
			ace_thermal_xs_data[zaid].setEffectiveTemperature(temp);
			FMEffectiveTemperature fm_eff_temp;
			for (int in = 0; in < static_cast<int>(uf_region_data.sab_name.size()); in++)
			{
				if (zaid == uf_region_data.sab_name[in])
				{
					if (this->use_sct_option == true)
					{
						REAL eff_temp = fm_eff_temp.getEffectiveTemperature(uf_region_data.sab_type[in], temp);
						ace_thermal_xs_data[zaid].setEffectiveTemperature(eff_temp);
					}
				}
			}

			ace_thermal_xs_data[zaid].setEoutUpperLowerInelastic(thermal_cutoff_eout, mg_energy_boundary.back());
			ace_thermal_xs_data[zaid].prepPlCoefIncoherentInelastic(max_pl);
			ace_thermal_xs_data[zaid].prepPlCoefIncoherentElastic(max_pl);
			ace_thermal_xs_data[zaid].prepPlCoefCoherentElastic(max_pl);
#if 0
			ace_thermal_xs_data[zaid].dumpIncoherentInelasticData();
#endif
		}
	}

}
void FMDataContainer::checkACEFiles()
{
	//check all materials exist in ace file
	for (int i = 0; i < static_cast<int>(uf_region_data.nuc_name.size()); i++)
	{
		if (ace_xs_data.find(uf_region_data.nuc_name[i]) == ace_xs_data.end())
		{
			cout << " Nuclide id " << uf_region_data.nuc_name[i] << " in input not found in ace file(s)" << endl;
			cout << " Nuclide id in ace file(s) are:" << endl;
			map<string, FMACECrossSectionProcessor>::iterator it;
			for (it = ace_xs_data.begin(); it != ace_xs_data.end(); it++)
				cout << it->first << endl;
			exit(0);
		}
	}

	//check all s(a,b) exist
	for (int i = 0; i < static_cast<int>(uf_region_data.sab_name.size()); i++)
	{
		if (uf_region_data.sab_name[i] == "") continue;
		if (ace_thermal_xs_data.find(uf_region_data.sab_name[i]) == ace_thermal_xs_data.end())
		{
			cout << " S(a,b) id " << uf_region_data.sab_name[i] << " in input not found in ace file(s)" << endl;
			cout << " S(a,b) id in ace file(s) are:" << endl;
			map<string, FMACEThermalCrossSectionProcessor>::iterator it;
			for (it = ace_thermal_xs_data.begin(); it != ace_thermal_xs_data.end(); it++)
				cout << it->first << endl;
			exit(0);
		}
		int inc_iel, inc_el, coh_el;
		this->convertThermalMaterialNameToMt(uf_region_data.sab_type[i], uf_region_data.sab_name[i], inc_iel, inc_el, coh_el);
	}

	//check consistency with resonance upscattering data
	for (int i = 0; i < (int)ruc_zaid.size(); i++)
	{
		if (ace_xs_data.find(ruc_zaid[i]) == ace_xs_data.end())
			printError(" zaid specified in reso_upscat does not exist in ace_files");
	}
}
void FMDataContainer::readAndSetUFEnergyGroupStructure()
{
	vector<REAL>   e_bd;
	vector<int>    e_num;
	vector<string> e_opt;
	vector<string> buf_vec;

	print1stHeader(" Setting ultra-fine energy group structure ");

	input_data->findBlock("ultra_fine_group", 0);
	//from input data
	for (;;)
	{

		input_data->getData(buf_vec);
		if (input_data->isEndOfBlock(buf_vec[0])) break;
		e_bd.push_back(my_stod(buf_vec[0]));
		if (buf_vec.size() != 1)
		{
			e_num.push_back(my_stoi(buf_vec[1]));
			e_opt.push_back(buf_vec[2]);
		}
	}

#if 1
	//adjust maximum and minimum energy to be consistent with multi-group boundary
	if (e_bd[0] > mg_energy_boundary[0]) e_bd[0] = mg_energy_boundary[0];
	if (e_bd.back() < mg_energy_boundary.back()) e_bd[e_bd.size()-1] = mg_energy_boundary.back();

	//check uf energy boundary (within multi-group energy boundary?)
	for (int i = 0; i < static_cast<int>(e_bd.size()); i++)
	{
		if (e_bd[i] < mg_energy_boundary.back() || e_bd[i] > mg_energy_boundary[0])
		{
			printError(" Ultra-fine group energy boundary shound be within multi-group boundary");
		}
	}
#endif

	uf_energy_boundary.clear();
	uf_energy_midpoint.clear();
	for (int i = 0; i < static_cast<int>(e_num.size()); i++)
	{
		int ediv = eFMEquiLethagyDivision;
		if (compareString(e_opt[i], "EE"))	ediv = eFMEquiEnergyDivision;
		for (int j = 0; j < e_num[i]; j++)
		{
			if (ediv == eFMEquiEnergyDivision)
			{
				REAL delta = (e_bd[i] - e_bd[i + 1]) / REAL(e_num[i]);
				REAL wk = e_bd[i] - delta * REAL(j);
				uf_energy_boundary.push_back(wk);
			}
			else
			{
				REAL delta = log(e_bd[i] / e_bd[i + 1]) / REAL(e_num[i]);
				REAL wk = e_bd[i] / exp(delta * REAL(j));
				uf_energy_boundary.push_back(wk);
			}
		}
	}
	uf_energy_boundary.push_back(e_bd.back());
	std::sort(uf_energy_boundary.begin(), uf_energy_boundary.end(), std::greater<REAL>());

	print2ndHeader(" Ultra-fine energy group structure from input ");
	reportUFEnergyGroupStructure();

	//add multi-group boundary
	for (int i = 0; i < mg_max_num_energy; i++)
		uf_energy_boundary.push_back(mg_energy_boundary[i]);

	//sort energy grid
	std::sort(uf_energy_boundary.begin(), uf_energy_boundary.end(), std::greater<REAL>());

	//save input energy grid
	uf_energy_boundary_input.clear();
	uf_energy_boundary_input = uf_energy_boundary;

	//add energy grid from point-wise cross sections if ufg group structure is not sufficient
	REAL uf_energy_boundary_upper = uf_energy_boundary[0];
	REAL uf_energy_boundary_lower = uf_energy_boundary.back();
	for (int i = 0; i < uf_region_data.num_nucl; i++)
	{
		std::sort(uf_energy_boundary.begin(), uf_energy_boundary.end(), std::greater<REAL>());

		string nuc_name = uf_region_data.nuc_name[i];
		FMACECrossSectionProcessor& acexs = ace_xs_data[nuc_name];
		int uf_num = uf_energy_boundary.size();
		int ie = 0;
		int je = 0;
		int ace_ng_num = acexs.getMaxNg();
		vector<REAL> add_energy;
		add_energy.clear();
		for(;;)
		{
			REAL e = acexs.getPointwiseEnergy(je);
			if (ie > uf_num - 2) break;
			if (je > ace_ng_num - 1) break;
			if (e >= uf_energy_boundary[ie])
			{
				je++;
				continue;
			}
			else if (e < uf_energy_boundary[ie] && e > uf_energy_boundary[ie + 1])
			{
				add_energy.push_back(e);
				je++;
			}
			else if (e <= uf_energy_boundary[ie + 1])
			{
				if (add_energy.size() > 1)
				{
					for (int j = 0; j < static_cast<int>(add_energy.size()); j++)
					{
						if (add_energy[j] > uf_energy_boundary_lower && add_energy[j] < uf_energy_boundary_upper)
							uf_energy_boundary.push_back(add_energy[j]);
					}
				}
				ie++;
				add_energy.clear();
			}
		}
	}

	//add energy grid at Bragg-edge to capture steep change of cross section
	for (int i = 0; i < uf_region_data.num_nucl; i++)
	{
		string sab_name = uf_region_data.sab_name[i];
		if (sab_name != "")
		{
			if (ace_thermal_xs_data[sab_name].isElasticScattering())
			{
				vector<REAL> add_energy;
				ace_thermal_xs_data[sab_name].getElasticEnergyGrids(add_energy);
				for (int j = 0; j < static_cast<int>(add_energy.size()); j++)
				{
					REAL val = add_energy[j] * 1.0e6;
					if (val > uf_energy_boundary_lower && val < uf_energy_boundary_upper)
						uf_energy_boundary.push_back(val);
				}
			}
		}
	}

	//delete thin energy groups
	deleteThinInterval(uf_energy_boundary);
	deleteThinInterval(uf_energy_boundary_input);

	print2ndHeader(" Modified ultra-fine energy group structure  using ACE energy grid ");
	reportUFEnergyGroupStructure();

	//automatically adjusted UFG energy grid
	uf_max_num_energy = uf_energy_boundary.size() - 1;

	uf_energy_midpoint.clear();
	uf_energy_delta.clear();

	//calculate midpoint of uf groups in lethagy
	for (int i = 0; i < uf_max_num_energy; i++)
	{
		REAL wk = sqrt(uf_energy_boundary[i]*uf_energy_boundary[i + 1]);
		uf_energy_midpoint.push_back(wk);
	}

	//calculate delta energy
	for (int i = 0; i < uf_max_num_energy; i++)
	{
		REAL delta = uf_energy_boundary[i] - uf_energy_boundary[i + 1];
		uf_energy_delta.push_back(delta);
	}

	//input UFG energy grid
	uf_max_num_energy_input = uf_energy_boundary_input.size() - 1;

	uf_energy_midpoint_input.clear();
	uf_energy_delta_input.clear();

	//calculate midpoint of uf groups in lethagy
	for (int i = 0; i < uf_max_num_energy_input; i++)
	{
		REAL wk = sqrt(uf_energy_boundary_input[i] * uf_energy_boundary_input[i + 1]);
		uf_energy_midpoint_input.push_back(wk);
	}

	//calculate delta energy
	for (int i = 0; i < uf_max_num_energy_input; i++)
	{
		REAL delta = uf_energy_boundary_input[i] - uf_energy_boundary_input[i + 1];
		uf_energy_delta_input.push_back(delta);
	}

}
void FMDataContainer::reportUFEnergyGroupStructure()
{
	vector<REAL> eb;
	eb.clear();
	REAL wk = 1.0e-5;
	eb.push_back(uf_energy_boundary[0]);
	eb.push_back(uf_energy_boundary.back());
	for (int i = 0; i <= 14; i++)
	{
		if (wk < uf_energy_boundary[0] && wk > uf_energy_boundary.back())
			eb.push_back(wk);
		wk *= 10.0;
	}
	sort(eb.begin(), eb.end(), std::greater<REAL>());

	vector<REAL> de_ave, du_ave, de_min, de_max, du_min, du_max;
	vector<int> numg;

	for (int i = 0; i < static_cast<int>(eb.size()) - 1; i++)
	{
		REAL deave = 0.0;
		REAL duave = 0.0;
		REAL demin = 1.0e+10;
		REAL demax = 0.0;
		REAL dumin = 1.0e+10;
		REAL dumax = 0.0;
		int n = 0;
		for (int ie = 0; ie < static_cast<int>(uf_energy_boundary.size()) - 1; ie++)
		{
			if (uf_energy_boundary[ie] > eb[i]) continue;
			if (uf_energy_boundary[ie] < eb[i + 1]) continue;
			REAL de = uf_energy_boundary[ie] - uf_energy_boundary[ie + 1];
			REAL du = log(uf_energy_boundary[ie] / uf_energy_boundary[ie + 1]);
			n++;
			deave += de;
			duave += du;
			if (de < demin) demin = de;
			if (de > demax) demax = de;
			if (du < dumin) dumin = du;
			if (du > dumax) dumax = du;
		}
		numg.push_back(n);
		de_ave.push_back(deave / (REAL)n);
		du_ave.push_back(duave / (REAL)n);
		de_min.push_back(demin);
		de_max.push_back(demax);
		du_min.push_back(dumin);
		du_max.push_back(dumax);
	}
	cout << scientific << setprecision(5);
	cout << "    E-upper        E-lower      Number of UFG    Ave Delta-E    Min Delta-E    Max Delta-E  Ave Delta-leth  Min Delta-leth Max Delta-leth" << endl;
	int totn = 0;
	for (int i = 0; i < static_cast<int>(eb.size()) - 1; i++)
	{
		cout << setw(15) << eb[i];
		cout << setw(15) << eb[i + 1];
		cout << setw(15) << numg[i];
		cout << setw(15) << de_ave[i];
		cout << setw(15) << de_min[i];
		cout << setw(15) << de_max[i];
		cout << setw(15) << du_ave[i];
		cout << setw(15) << du_min[i];
		cout << setw(15) << du_max[i];
		cout << endl;
		totn += numg[i];
	}
	cout << "           Number of total UFG" << setw(15) << totn << endl;
	cout << endl;
}
int FMDataContainer::getUFgroup(REAL ene)
{
	if (ene > uf_energy_boundary[0] || ene < uf_energy_boundary.back())
	{
		cout << " out of range in FMDataContainer::getUFgroup" << endl;
		exit(0);
	}

	static int current_pos = 0;
	if (current_pos < 0 || current_pos >= static_cast<int>(uf_energy_boundary.size())) current_pos = 0;

	//lookup
	for (;;)
	{
		//REAL val = 0.0;
		if (ene <= uf_energy_boundary[current_pos] && ene >= uf_energy_boundary[current_pos + 1])
		{
			return current_pos;
		}
		else if (ene > uf_energy_boundary[current_pos])
		{
			current_pos--;
			if (current_pos < 0)
			{
				cout << " out of range in FMDataContainer::getUFgroup " << endl;
				exit(0);
			}
		}
		else
		{
			current_pos++;
			if (current_pos > static_cast<int>(uf_energy_boundary.size()))
			{
				cout << " out of range in FMDataContainer::getUFgroup " << endl;
				exit(0);
			}
		}
	}
}
int FMDataContainer::getMGgroup(REAL ene, bool extend)
{
	if (extend)
	{
		if (ene >= mg_energy_boundary[0]) return 0;
		if (ene <= mg_energy_boundary.back()) return mg_energy_boundary.size() - 2;
	}

	for (int ie = 0; ie < mg_max_num_energy; ie++)
	{
		if (ene < mg_energy_boundary[ie] && ene > mg_energy_boundary[ie + 1])
			return ie;
	}

	cout << " error in FMDataContainer::getMGgroup";
	exit(0);
}
REAL FMDataContainer::getUFSpectrum(REAL ene, int ib, int pl, int opt)
{
	REAL val;
	int ie = getUFgroup(ene);
	val = uf_flux_nr[ib][ie];
	if (opt == eFMSlowingDownCalc)
	{
		if (ene <= e_upper_slowingdown_spectrum && ene >= e_lower_slowingdown_spectrum)
		{
			val = uf_flux[ib][ie];
		}
	}

	//factor for pl current
	REAL fact = 1.0;
	REAL totxs = uf_sig_total_sigb[ib][ie];
	for (int il = 0; il < pl; il++)
		fact /= totxs;

	val *= fact;

	return val;
}
REAL FMDataContainer::getUFSpectrum(int ie, int ib, int pl)
{
	REAL val;
	REAL ene = uf_energy_midpoint[ie];
	val = uf_flux_nr[ib][ie];
	if (ene <= e_upper_slowingdown_spectrum && ene >= e_lower_slowingdown_spectrum)
	{
		val = uf_flux[ib][ie];
	}

	//factor for pl current
	REAL fact = 1.0;
	REAL totxs = uf_sig_total_sigb[ib][ie];
	for (int il = 0; il < pl; il++)
		fact /= totxs;

	val *= fact;

	return val;
}

void FMDataContainer::doInitialize()
{
	//set fixed source
	fixed_source.init(uf_energy_boundary, uf_energy_midpoint);

	//set slowing down group range for actual nuclides
	map<string, FMACECrossSectionProcessor>::iterator it;
	vector<int> tmp(uf_max_num_energy);
	for (it = ace_xs_data.begin(); it != ace_xs_data.end(); it++)
	{
		REAL aw = it->second.getAW();
		REAL alpha = (aw - 1.0)*(aw - 1.0) / ((aw + 1.0)*(aw + 1.0));
		int je_sta = 0;
		for (int ie = 0; ie < uf_max_num_energy; ie++)
		{
			REAL e_upper = 1.0e+10;
			if (alpha != 0.0) e_upper = uf_energy_midpoint[ie] / alpha;
			if (ie != 0) je_sta = tmp[ie - 1];
			for (int je = je_sta; je < uf_max_num_energy; je++)
			{
				if (e_upper > uf_energy_midpoint[je])
				{
					tmp[ie] = je;
					break;
				}
			}
		}
		string nuc_name = it->first;
		uf_slowdown_upper_group.insert(make_pair(nuc_name, tmp));
	}

	//set slowing down group range for background nuclide
	REAL aw = moderator_aw;
	REAL alpha = (aw - 1.0)*(aw - 1.0) / ((aw + 1.0)*(aw + 1.0));
	int je_sta = 0;
	for (int ie = 0; ie < uf_max_num_energy; ie++)
	{
		REAL e_upper = 1.0e+10;
		if (alpha != 0.0) e_upper = uf_energy_midpoint[ie] / alpha;
		if (ie != 0) je_sta = tmp[ie - 1];
		for (int je = je_sta; je < uf_max_num_energy; je++)
		{
			if (e_upper > uf_energy_midpoint[je])
			{
				tmp[ie] = je;
				break;
			}
		}
	}
	string nuc_name = my_to_string(moderator_aw);
	uf_slowdown_upper_group.insert(make_pair(nuc_name, tmp));

	//correspondance between uf and mg groups
	uf_to_mg_group.resize(uf_max_num_energy);
	for (int ie = 0; ie < uf_max_num_energy; ie++)
		uf_to_mg_group[ie] = getMGgroup(uf_energy_midpoint[ie]);

	//correspondance between uf and mg groups (input UFG energy grid)
	uf_to_mg_group_input.resize(uf_max_num_energy_input);
	for (int ie = 0; ie < uf_max_num_energy_input; ie++)
		uf_to_mg_group_input[ie] = getMGgroup(uf_energy_midpoint_input[ie]);

	//set number of ultra-fine energy groups in a multi-group
	ufnum_in_mg_group.resize(mg_max_num_energy);
	for (int mg = 0; mg < mg_max_num_energy; mg++)
		ufnum_in_mg_group[mg] = 0;
	for (int ie = 0; ie < uf_max_num_energy; ie++)
	{
		int mg = uf_to_mg_group[ie];
		ufnum_in_mg_group[mg]++;
	}

	//set misc. data used for cross section collapsing
	REAL val = 0.0;
	for (int ig = 0; ig < static_cast<int>(mg_energy_boundary.size()) - 1; ig++)
	{
		if (e_upper_slowingdown_spectrum_input <= mg_energy_boundary[ig] && e_upper_slowingdown_spectrum_input >= mg_energy_boundary[ig + 1])
		{
			val = mg_energy_boundary[ig];
			break;
		}
	}
	e_upper_slowingdown_spectrum = val;
	for (int ig = 0; ig < static_cast<int>(mg_energy_boundary.size()) - 1; ig++)
	{
		if (e_lower_slowingdown_spectrum_input <= mg_energy_boundary[ig] && e_lower_slowingdown_spectrum_input >= mg_energy_boundary[ig + 1])
		{
			val = mg_energy_boundary[ig + 1];
			break;
		}
	}
	e_lower_slowingdown_spectrum = val;


	if (sld_calc_option == eFMSlowingDownCalc)
	{
		print1stHeader(" Adjusting enegy range of slowing down calculation results used for effective cross section calc. ");
		cout << " Upper energy [eV] to use ultra-fine group slowing down spectrum is adjusted to : " << scientific << setprecision(5) << e_upper_slowingdown_spectrum << endl;
		cout << " Lower energy [eV] to use ultra-fine group slowing down spectrum is adjusted to : " << scientific << setprecision(5) << e_lower_slowingdown_spectrum << endl;
	}

	//set background cross sections in uf_region_data
	setBGXSInUFRegionData();

	//set misc data in uf_region_data
	setMiscDataInUFRegionData();

	//set UNR data
	for (it = ace_xs_data.begin(); it != ace_xs_data.end(); it++)
	{
		if (it->second.isUNRData() == false) continue;
		it->second.setUNRBlock();
	}

	//set additional file name to ace, ace_thermal, and matxs output
	autoSetBackgroundXS();

	//prepare unresolved self-shielding data in ACE cross sections
	print1stHeader(" Processing unresolved data ");
	for (it = ace_xs_data.begin(); it != ace_xs_data.end(); it++)
	{
		if (it->second.isUNRData() == false) continue;
		string zaid = it->first;
		REAL bg_xs_homo = 0.0;
		for (int in = 0; in < uf_region_data.num_nucl; in++)
		{
			if (compareString(zaid, uf_region_data.nuc_name[in]) == true)
			{
				bg_xs_homo = uf_region_data.bgxs_homo[in];
				break;
			}
		}
		vector<string> fname_unr, output_data_unr;
		fname_unr.clear(); output_data_unr.clear();

		it->second.prepUnresolvedResonanceUFGXSFactor(bg_xs_homo, background_xs_set, fname_unr, output_data_unr, file_add_name_);

		for (int i = 0; i < static_cast<int>(fname_unr.size()); i++)
			output_list_data.insert(make_pair(fname_unr[i], output_data_unr[i]));
	}

	//set UFG cross sections in uf_region_data
	setUFGXSInUFRegionData();

	//allocate arrays
	int num_bgxs = background_xs_set.size();
	uf_flux.resize(num_bgxs);
	uf_flux_nr.resize(num_bgxs);
	uf_sld_source.resize(num_bgxs);
	uf_source.resize(num_bgxs);
	uf_sig_total_sigb.resize(num_bgxs);
	uf_sig_total.resize(num_bgxs);
	for (int i = 0; i < num_bgxs; i++)
	{
		uf_flux[i].resize(uf_max_num_energy);
		uf_flux_nr[i].resize(uf_max_num_energy);
		uf_sld_source[i].resize(uf_max_num_energy);
		uf_source[i].resize(uf_max_num_energy);
		uf_sig_total_sigb[i].resize(uf_max_num_energy);
		uf_sig_total[i].resize(uf_max_num_energy);
	}

}
void FMDataContainer::setBGXSInUFRegionData()
{
	int num_nucl = uf_region_data.num_nucl;
	//int num_bgxs = static_cast<int>(background_xs_set.size());

	uf_region_data.bgxs_homo.resize(num_nucl);

	//set default potential cross section if necessary
	FMPotentialXSDatabase pxsd;
	for (int in = 0; in < num_nucl; in++)
	{
		string zaid = uf_region_data.nuc_name[in];
		if (potential_xs.find(zaid) == potential_xs.end())
		{
			int za = ace_xs_data[zaid].getZa();

			//use database
			REAL potxs = pxsd.getPotentialXS(za);

			//if not found in the database, use ENDF simplified formula
			if (potxs == 0.0)
			{
				REAL aw = ace_xs_data[zaid].getAW();
				REAL a = 0.123 * pow(aw, 1.0 / 3.0) + 0.08;		//scattering radius, [10^-12 cm]
				potxs = 4.0 * PI * a * a;						//potential xs [barn]
			}
			potential_xs.insert(make_pair(zaid, potxs));
		}
	}

	//macroscopic potential scattering cross section
	uf_region_data.mac_potential_xs = 0.0;
	for (int in = 0; in < num_nucl; in++)
	{
		string zaid = uf_region_data.nuc_name[in];
		if (potential_xs.find(zaid) == potential_xs.end())
		{
			cout << " potential xs of " << zaid << " is not provided." << endl;
			exit(0);
		}
		uf_region_data.mac_potential_xs += potential_xs[zaid] * uf_region_data.nuc_dens[in];
	}


	if (num_nucl == 1)
	{
		uf_region_data.bgxs_homo[0] = 0.0;
		return;
	}

	for (int in = 0; in < num_nucl; in++)
	{
		REAL sum = 0.0;
		for (int iin = 0; iin < num_nucl; iin++)
		{
			if (iin == in) continue;
			string zaid = uf_region_data.nuc_name[iin];
			sum += potential_xs[zaid] * uf_region_data.nuc_dens[iin];
		}
		if (uf_region_data.nuc_dens[in] == 0.0)
			uf_region_data.bgxs_homo[in] = 1.0e+10;
		else
			uf_region_data.bgxs_homo[in] = sum / uf_region_data.nuc_dens[in];
	}

	print1stHeader(" Potential scattering cross section (PotXS) and background cross section in homogeneous medium (BGXS)");
	cout << "      ZAID     PotXS [barn]  ND[1/barn/cm] BGXS[barn]" << endl;
	for (int in = 0; in < num_nucl; in++)
	{
		string zaid = uf_region_data.nuc_name[in];
		cout << setw(12) << zaid;
		cout << scientific << setprecision(5);
		cout << setw(14) << potential_xs[zaid];
		cout << setw(14) << uf_region_data.nuc_dens[in];
		cout << setw(14) << uf_region_data.bgxs_homo[in];
		cout << endl;
	}
}
void FMDataContainer::setMiscDataInUFRegionData()
{
	int num_nucl = uf_region_data.num_nucl;
	//int num_bgxs = background_xs_set.size();

	//set ace xs pointer
	uf_region_data.ace_xs_pointer.clear();
	for (int i = 0; i < num_nucl; i++)
	{
		string nuc_name = uf_region_data.nuc_name[i];
		uf_region_data.ace_xs_pointer.push_back(&ace_xs_data[nuc_name]);
	}

	//alpha = (A-1)^2/(A+1)^2
	REAL aw;
	uf_region_data.alpha.clear();
	for (int i = 0; i < num_nucl; i++)
	{
		aw = uf_region_data.ace_xs_pointer[i]->getAW();
		REAL alpha = (aw - 1)*(aw - 1) / ((aw + 1)*(aw + 1));
		uf_region_data.alpha.push_back(alpha);
	}

	//set pointer to upper fg
	uf_region_data.upper_fg.clear();
	for (int i = 0; i < num_nucl; i++)
	{
		string nuc_name = uf_region_data.nuc_name[i];
		uf_region_data.upper_fg.push_back(&uf_slowdown_upper_group[nuc_name]);
	}
}
void FMDataContainer::setUFGXSInUFRegionData()
{
	int num_nucl = uf_region_data.num_nucl;
	int num_bgxs = background_xs_set.size();

	uf_region_data.setUfgArraySize(num_bgxs, uf_max_num_energy);

	//macroscopic total cross section & elastic scattering cross section
	for (int ib = 0; ib < num_bgxs; ib++)
	{
		for (int ie = 0; ie < uf_max_num_energy; ie++)
		{
			REAL ene = uf_energy_midpoint[ie];

			//microscopic elastic scattering & macroscopic total cross section
			uf_region_data.macst[ib][ie] = 0.0;
			for (int in = 0; in < num_nucl; in++)
			{
				REAL bgxs = background_xs_set[ib];
#if 1
				REAL sc = uf_region_data.ace_xs_pointer[in]->getXS(eMTElasticScattering, ene, bgxs);
				REAL st = uf_region_data.ace_xs_pointer[in]->getXS(eMTTotal, ene, bgxs);
#else
				REAL sc = uf_region_data.ace_xs_pointer[in]->getXS(eMTElasticScattering, ene);
				REAL st = uf_region_data.ace_xs_pointer[in]->getXS(eMTTotal, ene);
#endif
				uf_region_data.micsc[ib][in][ie] = sc;
				uf_region_data.macst[ib][ie] += uf_region_data.nuc_dens[in] * st;
			}
		}
	}
}
void FMDataContainer::autoSetBackgroundXS()
{
	if (auto_background_xs_setting == false) return;

	print1stHeader(" Automatically setting of background cross sections ");

	//initial background xs setting
	int BGXS_INIT_GRID = 10;
	REAL BGXS_MIN = auto_background_xs_bg_min;
	REAL BGXS_MAX = 1.0e+10;
	int BGXS_NUM_MIN = 2;

	//number of nuclides
	int num_nucl = uf_region_data.num_nucl;

	//slowing down calculation option
	bool slowdown = false;
	if (sld_calc_option == eFMSlowingDownCalc) slowdown = true;

	//number of ultra-fine group spectrum calculations
	int num_ufg_calc = 0;

	//definition of variables
	struct BGXSSET
	{
		vector<vector<REAL> >	mg_xs;	//[mt][ng]
		vector<REAL>			rr;
		REAL bgxs;
		bool conv;
		BGXSSET()
		{
			mg_xs.clear();
			rr.clear();
			bgxs = 0.0;
			conv = false;
		};
	};
	map<REAL,BGXSSET> bgxs_set;
	vector<REAL> flux_mg;
	//UFRegionData& ufr = uf_region_data;

	//ufg micro cross section array
	vector<vector<vector<REAL> > > ufg_xs;		//num_nucl, mt, uf_max_energy
	ufg_xs.resize(num_nucl);
	for (int in = 0; in < num_nucl; in++)
	{
		ufg_xs[in].resize(4);	//mt=1, 2, 18, 102
		for (int i = 0; i < 4; i++)
		{
			ufg_xs[in][i].resize(uf_max_num_energy);
			for (int ie = 0; ie < uf_max_num_energy; ie++)
				ufg_xs[in][i][ie] = 0.0;
		}
	}

	//set infinite dilute "nuclide-wise macro" cross sections
	for (int in = 0; in < num_nucl; in++)
	{
		string nuc_name = uf_region_data.nuc_name[in];
		REAL nd = uf_region_data.nuc_dens[in];
		for (int ie = 0; ie < uf_max_num_energy; ie++)
		{
			REAL ene = uf_energy_midpoint[ie];
			REAL st = ace_xs_data[nuc_name].getXS(eMTTotal, ene);
			REAL ss = ace_xs_data[nuc_name].getXS(eMTElasticScattering, ene);
			REAL sf = ace_xs_data[nuc_name].getXS(eMTFission, ene);
			REAL sc = ace_xs_data[nuc_name].getXS(eMTNGamma, ene);
			ufg_xs[in][0][ie] = nd * st;
			ufg_xs[in][1][ie] = nd * ss;
			ufg_xs[in][2][ie] = nd * sf;
			ufg_xs[in][3][ie] = nd * sc;
		}
	}

	//set potential scattering cross section
	REAL mac_pot_xs = uf_region_data.mac_potential_xs;

	//calculate initial grid of background cross sections
	for (int ib = 0; ib < BGXS_INIT_GRID + 1; ib++)
	{
		BGXSSET wk;
		REAL val = (log(BGXS_MAX) - log(BGXS_MIN)) / (REAL)BGXS_INIT_GRID * (REAL)ib + log(BGXS_MIN);
		val = exp(val);

		wk.mg_xs.resize(4);
		for (int i = 0; i < 4; i++)
			wk.mg_xs[i].resize(mg_max_num_energy);
		for (int i = 0; i < 4; i++)
			for (int ig = 0; ig < mg_max_num_energy; ig++)
				wk.mg_xs[i][ig] = 0.0;

		bgxs_set.insert(make_pair(val, wk));
	}

	//set unresolved self-shielding factor table
	vector<REAL> bgxs_vec;
	map<REAL, BGXSSET>::iterator it;
	for (it = bgxs_set.begin(); it != bgxs_set.end(); it++)
		bgxs_vec.push_back(it->first);
	sort(bgxs_vec.begin(), bgxs_vec.end(), std::greater<REAL>());

	map<string, FMACECrossSectionProcessor>::iterator itace;
	for (itace = ace_xs_data.begin(); itace != ace_xs_data.end(); itace++)
	{
		if (itace->second.isUNRData() == false) continue;
		string zaid = itace->first;
		REAL bg_xs_homo = 0.0;
		for (int in = 0; in < uf_region_data.num_nucl; in++)
		{
			if (compareString(zaid, uf_region_data.nuc_name[in]) == true)
			{
				bg_xs_homo = uf_region_data.bgxs_homo[in];
				break;
			}
		}
		vector<string> fname_unr, output_data_unr;
		fname_unr.clear(); output_data_unr.clear();

		itace->second.prepUnresolvedResonanceUFGXSFactor(bg_xs_homo, bgxs_vec, fname_unr, output_data_unr, file_add_name_);
	}

	//calculate effective cross sections
	flux_mg.resize(mg_max_num_energy);
	map<REAL, BGXSSET>::iterator it0, it1;

	for (it =bgxs_set.begin(); it != bgxs_set.end(); it++)
	{
		REAL bgxs = it->first;
		calcEffectiveXSForAutoSetBGXS(bgxs, ufg_xs, mac_pot_xs, it->second.mg_xs, it->second.rr, slowdown);
		num_ufg_calc++;
	}

	//eliminate background cross sections that can be interpolated
	for (;;)
	{
		REAL min_err = 1.0e+10;
		map<REAL, BGXSSET>::iterator min_err_pos;

		for (it = bgxs_set.begin(); it != bgxs_set.end(); it++)
		{
			map<REAL, BGXSSET>::iterator itend = bgxs_set.end(); itend--;
			if (it == bgxs_set.begin() || it == itend) continue;

			REAL max_err_wk = 0.0;
			if (auto_background_xs_use_rr == false)
			{
				for (int ig = 0; ig < mg_max_num_energy; ig++)
				{
					if (mg_energy_boundary[ig] > auto_background_xs_bg_max_energy) continue;
					if (mg_energy_boundary[ig + 1] < auto_background_xs_bg_min_energy) continue;

					for (int i = 0; i < 4; i++)
					{
						REAL xs = it->second.mg_xs[i][ig];
						if (xs == 0.0) continue;
						vector<REAL> x;
						vector<REAL> y;
						for (it0 = bgxs_set.begin(); it0 != bgxs_set.end(); it0++)
						{
							if (it0 != it)
							{
								x.push_back(log(it0->first));
								y.push_back(it0->second.mg_xs[i][ig]);
							}
						}
						REAL logbg = log(it->first);
						REAL val = 0.0;
						if (auto_background_xs_cubic_int)
							val = doMonotoneCubicInterpolation(x, y, logbg);
						else
							val = doInterporationFromVector(2, x, y, logbg, eExtraporationConst);

						REAL eps = abs((val - xs) / xs);
						if (eps > max_err_wk) max_err_wk = eps;
					}
				}
			}
			else
			{
				for (int i = 0; i < 4; i++)
				{
					REAL rr = it->second.rr[i];
					if (rr == 0.0) continue;
					vector<REAL> x;
					vector<REAL> y;
					for (it0 = bgxs_set.begin(); it0 != bgxs_set.end(); it0++)
					{
						if (it0 != it)
						{
							x.push_back(log(it0->first));
							y.push_back(it0->second.rr[i]);
						}
					}
					REAL logbg = log(it->first);
					REAL val = 0.0;
					if (auto_background_xs_cubic_int)
						val = doMonotoneCubicInterpolation(x, y, logbg);
					else
						val = doInterporationFromVector(2, x, y, logbg, eExtraporationConst);

					REAL eps = abs((val - rr) / rr);
					if (eps > max_err_wk) max_err_wk = eps;
				}
			}
			if (max_err_wk < min_err)
			{
				min_err = max_err_wk;
				min_err_pos = it;
			}
		}
		
		//convergence check
		if (min_err > auto_background_xs_bg_eps) break;

		//minimum number of points 
		bgxs_set.erase(min_err_pos);
		if (static_cast<int>(bgxs_set.size()) <= BGXS_NUM_MIN) break;
	}


	//insert background cross sections that cannot be linearly interpolated
	//bool loop_break = false;
	map<REAL, BGXSSET> bgxs_set_add;
	REAL max_err;
	for (;;)
	{
		bgxs_set_add.clear();

		max_err = 0.0;

		vector<REAL> x;
		it = bgxs_set.begin();
		for (it = bgxs_set.begin(); it != bgxs_set.end(); it++)
			x.push_back(log(it->first));

		for (it = bgxs_set.begin(); it != bgxs_set.end(); it++)
		{
			map<REAL, BGXSSET>::iterator itend = bgxs_set.end(); itend--;
			if (it == itend) continue;

			it0 = it;
			it1 = it; it1++;

			vector<BGXSSET> wk(3);
			for (int ii = 0; ii < 3; ii++)
			{
				wk[ii].mg_xs.resize(4);
				for (int i = 0; i < 4; i++)
					wk[ii].mg_xs[i].resize(mg_max_num_energy);
				for (int i = 0; i < 4; i++)
					for (int ig = 0; ig < mg_max_num_energy; ig++)
						wk[ii].mg_xs[i][ig] = 0.0;
			}

			//prepare unresolved resonance self-shielding factor table
			bgxs_vec.clear();
			bgxs_vec.push_back(BGXS_MAX);
			for (int ii = 0; ii < 3; ii++)
			{
				REAL val = 0.25 * (REAL)(ii+1);
				REAL bgxs = pow(it0->first, val) * pow(it1->first, 1.0 - val);
				bgxs_vec.push_back(bgxs);
			}

			for (itace = ace_xs_data.begin(); itace != ace_xs_data.end(); itace++)
			{
				if (itace->second.isUNRData() == false) continue;
				string zaid = itace->first;
				REAL bg_xs_homo = 0.0;
				for (int in = 0; in < uf_region_data.num_nucl; in++)
				{
					if (compareString(zaid, uf_region_data.nuc_name[in]) == true)
					{
						bg_xs_homo = uf_region_data.bgxs_homo[in];
						break;
					}
				}
				vector<string> fname_unr, output_data_unr;
				fname_unr.clear(); output_data_unr.clear();

				itace->second.prepUnresolvedResonanceUFGXSFactor(bg_xs_homo, bgxs_vec, fname_unr, output_data_unr, file_add_name_);
			}

			REAL max_err_wk = 0.0;

			//check interpolation accuracy
			for (int ii = 0; ii < 3; ii++)
			{
				wk[ii].bgxs = bgxs_vec[ii+1];
				calcEffectiveXSForAutoSetBGXS(wk[ii].bgxs, ufg_xs, mac_pot_xs, wk[ii].mg_xs, wk[ii].rr, slowdown);
				num_ufg_calc++;

				if (auto_background_xs_use_rr == false)
				{
					//consider self-shielding factor
					for (int ig = 0; ig < mg_max_num_energy; ig++)
					{
						if (mg_energy_boundary[ig] > auto_background_xs_bg_max_energy) continue;
						if (mg_energy_boundary[ig + 1] < auto_background_xs_bg_min_energy) continue;

						for (int i = 0; i < 4; i++)
						{
							REAL xs = wk[ii].mg_xs[i][ig];
							if (xs == 0.0) continue;
							vector<REAL> y;
							for (it0 = bgxs_set.begin(); it0 != bgxs_set.end(); it0++)
							{
								y.push_back(it0->second.mg_xs[i][ig]);
							}
							REAL val = 0.0;
							if (auto_background_xs_cubic_int)
								val = doMonotoneCubicInterpolation(x, y, log(wk[ii].bgxs));
							else
								val = doInterporationFromVector(2, x, y, log(wk[ii].bgxs), eExtraporationConst);

							REAL eps = abs((val - xs) / xs);
							if (eps > max_err_wk) max_err_wk = eps;
							if (eps > max_err) max_err = eps;
						}
					}
				}
				else
				{
					//consider reaction rate
					for (int i = 0; i < 4; i++)
					{
						REAL rr = wk[ii].rr[i];
						if (rr == 0.0) continue;
						vector<REAL> y;
						for (it0 = bgxs_set.begin(); it0 != bgxs_set.end(); it0++)
						{
							y.push_back(it0->second.rr[i]);
						}
						REAL val = 0.0;
						if (auto_background_xs_cubic_int)
							val = doMonotoneCubicInterpolation(x, y, log(wk[ii].bgxs));
						else
							val = doInterporationFromVector(2, x, y, log(wk[ii].bgxs), eExtraporationConst);

						REAL eps = abs((val - rr) / rr);
						if (eps > max_err_wk) max_err_wk = eps;
						if (eps > max_err) max_err = eps;
					}

				}
			}
			if (max_err_wk > auto_background_xs_bg_eps)
				bgxs_set_add.insert(make_pair(-max_err_wk, wk[1]));
			else
				it->second.conv = true;

		}

		//convergence check
		if (bgxs_set_add.size() == 0) break;

		//add background cross sections
		for (it = bgxs_set_add.begin(); it != bgxs_set_add.end(); it++)
		{
			bgxs_set.insert(make_pair(it->second.bgxs, it->second));
			if (static_cast<int>(bgxs_set.size()) >= auto_background_xs_bg_maxnum) break;
		}
		if (static_cast<int>(bgxs_set.size()) >= auto_background_xs_bg_maxnum) break;
	}

	//set background cross section to the data container
	background_xs_set.clear();
	int bgnum = bgxs_set.size();
	background_xs_set.resize(bgnum);
	for (it = bgxs_set.begin(); it != bgxs_set.end(); it++)
	{
		bgnum--;
		background_xs_set[bgnum] = it->first;
	}

	cout << endl;
	cout << "   No.   bg_xs (barn)" << endl;
	int num = 0;
	for (int i = 0; i < static_cast<int>(background_xs_set.size()); i++)
	{
		cout << setw(5) << num;
		cout << setw(15) << scientific << setprecision(5) << background_xs_set[i];
		cout << endl;
		num++;
	}
	cout << endl;
	cout << "   Considered energy range (highest) [eV]                          : " << scientific << setprecision(2) << auto_background_xs_bg_max_energy << endl;
	cout << "   Considered energy range (lowest)  [eV]                          : " << scientific << setprecision(2) << auto_background_xs_bg_min_energy << endl;
	if (auto_background_xs_cubic_int)
		cout << "   Interpolation method of self-shielding factor                   : monotone cubic interpolation " << endl;
	else
		cout << "   Interpolation method of self-shielding factor                   : linear interpolation " << endl;
	cout << "   Target property                                                 : ";
	if (auto_background_xs_use_rr) cout << "reaction rate " << endl;
	else cout << "self-shielding factor " << endl;
	cout << "   Input torelance of interpolation error of self-shielding factor : " << scientific << setprecision(2) << auto_background_xs_bg_eps << endl;
	cout << "   Estimated  maximum interpolation error of self-shielding factor : " << scientific << setprecision(2) << max_err << endl;
	cout << "   Number of ultra-fine group calculations                         : " << num_ufg_calc << endl;
	cout << "   Ultra-fine group calculation method                             : ";
	if (slowdown) cout << "slowing down calculation " << endl;
	else cout << "narrow resonance approximation " << endl;
	cout << endl;


#if 0
	for (int i = 0; i < 4; i++)
	{
		cout << " Reaction type " << i << endl;
		for (it = bgxs_set.begin(); it != bgxs_set.end(); it++)
			cout << setw(15) << scientific << setprecision(4) << it->first;
		cout << endl;

		int ib_max = bgxs_set.size() - 1;
		for (int mg = 0; mg < mg_max_num_energy; mg++)
		{
			cout << setw(5) << mg;
			map<REAL, BGXSSET>::iterator itend = bgxs_set.end(); itend--;
			for (it = bgxs_set.begin(); it != bgxs_set.end(); it++)
				cout << setw(15) << scientific << setprecision(4) << it->second.mg_xs[i][mg] / itend->second.mg_xs[i][mg];
			cout << endl;
		}
	}
	exit(0);
#endif
}
void FMDataContainer::calcEffectiveXSForAutoSetBGXS(REAL bgxs,vector< vector<vector<REAL> > >& ufg_xs, REAL mac_pot_xs, vector<vector<REAL> >& mg_xs, vector<REAL>& rr,bool slowdown)
{
	//initialize temporary array
	vector<REAL> flux_mg(mg_max_num_energy);
	vector<REAL> flux_mg_infdil(mg_max_num_energy);
	int num_nucl = uf_region_data.num_nucl;

	for (int ig = 0; ig < mg_max_num_energy; ig++)
	{
		flux_mg[ig] = 0.0;
		flux_mg_infdil[ig] = 0.0;
		for (int i = 0; i < 4; i++)
			mg_xs[i][ig] = 0.0;
	}

	//set ace xs pointer
	vector<int> mt_vec = { 1, 2, 18, 102 };
	vector<FMACECrossSectionProcessor*> ace_xs_pointer(num_nucl);
	for (int in = 0; in < num_nucl; in++)
	{
		string nuc_name = uf_region_data.nuc_name[in];
		ace_xs_pointer[in] = &ace_xs_data[nuc_name];
	}

	//ultra-fine group calculation
	REAL sfg_prev = 0.0, sfg = 0.0;
	REAL aw = moderator_aw;
	REAL alpha_b = (aw - 1) * (aw - 1) / ((aw + 1) * (aw + 1));
	string bgaw = my_to_string(moderator_aw);
	vector<int>& upper_fg_bg = uf_slowdown_upper_group[bgaw];
	vector<vector<REAL> > micsc(num_nucl);

	//initialize ultra-fine group cross sections and flux
	for (int i = 0; i < num_nucl; i++)
		micsc[i].resize(uf_max_num_energy);
	vector<REAL> macst(uf_max_num_energy);
	vector<REAL> flux(uf_max_num_energy);
	vector<REAL> flux_nr(uf_max_num_energy);
	for (int ie = 0; ie < uf_max_num_energy; ie++)
	{
		macst[ie] = 0.0;
		flux[ie] = 0.0;
		flux_nr[ie] = 0.0;
		REAL ene = uf_energy_midpoint[ie];
		for (int in = 0; in < num_nucl; in++)
		{
			REAL fact_st = ace_xs_pointer[in]->getUNRSelfShielingFactor(mt_vec[0], ene, bgxs);
			REAL fact_sc = ace_xs_pointer[in]->getUNRSelfShielingFactor(mt_vec[1], ene, bgxs);
			macst[ie] += ufg_xs[in][0][ie] * fact_st;
			micsc[in][ie] = ufg_xs[in][1][ie] * fact_sc;
		}
	}

	for (int ie = 0; ie < uf_max_num_energy; ie++)
	{

		REAL ene = uf_energy_midpoint[ie];
		int mg = uf_to_mg_group[ie];

		//source 
		REAL src, src_nr;
		REAL sigb = bgxs * uf_region_data.nuc_dens_sum;
		src_nr = (bgxs * uf_region_data.nuc_dens_sum + uf_region_data.mac_potential_xs) * weighting_spectrum.getSpectrum(ene);
		if (slowdown)
		{
			//using recurrent formula (Handbook of Nuclear Engineering, Chap.9, Eq.(199)
			calcSlowingDownSourceRecurrent(micsc, bgxs, uf_region_data.nuc_dens, uf_region_data.nuc_dens_sum, uf_region_data.alpha,
				alpha_b, uf_region_data.upper_fg, upper_fg_bg, flux, sfg_prev, sfg, ie);	//elastic scattering
			sfg_prev = sfg;
			src = sfg + fixed_source.getChiUFG(ie);	//fission source
			flux[ie] = calcFlux(macst[ie], sigb, src);
		}
		else
		{
			//narrow resonance approximation
			flux[ie] = calcFlux(macst[ie], sigb, src_nr);
		}

		flux_nr[ie] = calcFlux(macst[ie], sigb, src_nr);

		REAL wgt_infdil = weighting_spectrum.getSpectrum(ene);
		REAL wgt = flux_nr[ie];
		if (slowdown)
		{
			if (ene <= e_upper_slowingdown_spectrum && ene >= e_lower_slowingdown_spectrum) wgt = flux[ie];
		}

		flux_mg[mg] += wgt * uf_energy_delta[ie];					//flux at self-shielded condition
		flux_mg_infdil[mg] += wgt_infdil * uf_energy_delta[ie];		//flux at infinite-dilute condition (used for reaction rate calculation)
		for (int i = 0; i < 4; i++)
		{
			for (int in = 0; in < num_nucl; in++)
			{
				REAL fact = ace_xs_pointer[in]->getUNRSelfShielingFactor(mt_vec[i], ene, bgxs);
				mg_xs[i][mg] += ufg_xs[in][i][ie] * fact * wgt * uf_energy_delta[ie];
			}
		}
	}

	//effective cross section
	for (int mg = 0; mg < mg_max_num_energy; mg++)
	{
		if (flux_mg[mg] != 0.0)
		{
			for (int i = 0; i < 4; i++)
				mg_xs[i][mg] /= flux_mg[mg];
		}
	}

	//reaction rate calculations
	rr.resize(4);
	for (int i = 0; i < 4; i++)
	{
		rr[i] = 0.0;
		for (int ig = 0; ig < mg_max_num_energy; ig++)
		{
			if (mg_energy_boundary[ig] > auto_background_xs_bg_max_energy) continue;
			if (mg_energy_boundary[ig + 1] < auto_background_xs_bg_min_energy) continue;
			rr[i] += mg_xs[i][ig] * flux_mg_infdil[ig];		//flux is energy integrated value
		}
	}
#if 0
	cout << setw(12) << scientific << setprecision(3) << bgxs;
	for (int i = 0; i < 4; i++)
		cout << setw(14) << scientific << setprecision(5) << rr[i];
	cout << endl;
#endif
}
void FMDataContainer::calcEffectiveMicroXS( )
{
	//number of nuclides
	int num_nucl = uf_region_data.num_nucl;

	//number of background cross sections
	int num_bgxs = background_xs_set.size();

	xs_mg_1d_vector.clear();

	//UFRegionData& ufr = uf_region_data;

	for (int in = 0; in < num_nucl; in++)
	{
		vector<vector<REAL> > eff_xs_mg;
		vector<vector<REAL> > flux_mg;
		vector<vector<REAL> > flux_nr_mg;
		vector<int> mt_values;
		mt_values.clear();
		string nuc_name = uf_region_data.nuc_name[in];
		ace_xs_data[nuc_name].getMtValues(mt_values);
		mt_values.push_back(eMTTotal);
		mt_values.push_back(eMTElasticScattering);
		mt_values.push_back(-1);					//used for current weight total cross section
		mt_values.push_back(eMTHeating);
		mt_values.push_back(eMTThermalFreeGas);
#if 0
		mt_values.push_back(eMTDisappearance);		//only for debug purpose. if enable this sentence, absorption xs may be double
#endif
		string sab_name = uf_region_data.sab_name[in];
		if (sab_name != "")
		{
			vector<int> thermal_mt(3);
			string sab_type = uf_region_data.sab_type[in];
			this->convertThermalMaterialNameToMt(sab_type, sab_name, thermal_mt[0], thermal_mt[1], thermal_mt[2]);
			for (int i = 0; i < static_cast<int>(thermal_mt.size()); i++)
			{
				if (thermal_mt[i] != 0) mt_values.push_back(thermal_mt[i]);
			}
		}
		sort(mt_values.begin(), mt_values.end());

		eff_xs_mg.resize(num_bgxs);
		flux_mg.resize(num_bgxs);
		flux_nr_mg.resize(num_bgxs);
		for (int ib = 0; ib < num_bgxs; ib++)
		{
			eff_xs_mg[ib].resize(mg_max_num_energy);
			flux_mg[ib].resize(mg_max_num_energy);
			flux_nr_mg[ib].resize(mg_max_num_energy);
		}

		map<int, vector<vector<REAL> > >	eff_xs_mg_array;
		eff_xs_mg_array.clear();

		for (int im = 0; im < static_cast<int>(mt_values.size()); im++)
		{
			int mt = mt_values[im];

			for (int ib = 0; ib < num_bgxs; ib++)
				for (int ie = 0; ie < mg_max_num_energy; ie++)
				{
					eff_xs_mg[ib][ie] = 0.0;
					flux_mg[ib][ie] = 0.0;
					flux_nr_mg[ib][ie] = 0.0;
				}

			for (int ib = 0; ib < num_bgxs; ib++)
			{
				REAL bgxs = background_xs_set[ib];
				vector<REAL> uf_energy_delta_sum(mg_max_num_energy);
				for (int mg = 0; mg < mg_max_num_energy; mg++)
					uf_energy_delta_sum[mg] = 0.0;

				for (int ie = 0; ie < uf_max_num_energy; ie++)
				{
					int mg = uf_to_mg_group[ie];
					REAL ene = uf_energy_midpoint[ie];
					REAL val_uf = getUFSpectrum(ie, ib);
					REAL val_nr_uf = uf_flux_nr[ib][ie];
					if (mt < 0)
					{
						val_uf /= (uf_region_data.macst[ib][ie] + bgxs * uf_region_data.nuc_dens_sum);		//current weight
						val_nr_uf /= (uf_region_data.macst[ib][ie] + bgxs * uf_region_data.nuc_dens_sum);		//current weight
					}
					val_uf *= uf_energy_delta[ie];
					val_nr_uf *= uf_energy_delta[ie];
					uf_energy_delta_sum[mg] += uf_energy_delta[ie];
					flux_mg[ib][mg] += val_uf;
					flux_nr_mg[ib][mg] += val_nr_uf;
					REAL xs = 0.0;

					if (isThermalMT(mt))
					{
						if (mt == eMTThermalFreeGas)
							xs = ace_xs_data[nuc_name].getXS(eMTElasticScattering, ene, bgxs);
						else if (isThermalIncoherentInelastic(mt))
						{
							xs = ace_thermal_xs_data[sab_name].getIncoherentInelasticXS(ene);
							if (xs == 0.0)
								xs = ace_xs_data[nuc_name].getXS(eMTElasticScattering, ene, bgxs);
						}
						else if (isThermalElastic(mt))
							xs = ace_thermal_xs_data[sab_name].getElasticXS(ene);

						if (ene > thermal_cutoff_ein) xs = 0.0;
					}
					else
						xs = ace_xs_data[nuc_name].getXS(mt, ene, bgxs);

					eff_xs_mg[ib][mg] += xs * val_uf;
				}
				for (int mg = 0; mg < mg_max_num_energy; mg++)
				{
					if (flux_mg[ib][mg] != 0.0)
						eff_xs_mg[ib][mg] /= flux_mg[ib][mg];
				}

				//normalize flux
				for (int mg = 0; mg < mg_max_num_energy; mg++)
				{
					if (uf_energy_delta_sum[mg] != 0.0)
						flux_nr_mg[ib][mg] *= (mg_energy_boundary[mg] - mg_energy_boundary[mg+1])/ uf_energy_delta_sum[mg];
				}

				REAL sum = 0.0;
				for (int mg = 0; mg < mg_max_num_energy; mg++)
					sum += flux_nr_mg[ib][mg];

				if (sum != 0.0)
				{
					for (int mg = 0; mg < mg_max_num_energy; mg++)
						flux_nr_mg[ib][mg] /= sum;
				}
			}
			eff_xs_mg_array.insert(make_pair(mt, eff_xs_mg));

			if (mt == -1 || mt == 1)
				flux_mg_1d_vector.insert(make_pair(mt, flux_nr_mg));

			cout << setw(20) << nuc_name << " mt =" << setw(4) << mt << " completed" << endl;
		}

		//energy dependent neutron emission number, including nu-prompt and nu-delayed
		vector<int> emission_mt;
		vector<int> sigwk;
		emission_mt.clear();
		sigwk.clear();
		if (ace_xs_data[nuc_name].isMT(eMTFission) == true || ace_xs_data[nuc_name].isMT(eMTFirstChanceFission) == true)
		{
			emission_mt.push_back(eMTNuTotal);
			emission_mt.push_back(eMTNuDelayed);
			sigwk.push_back(eMTFission);
			sigwk.push_back(eMTFission);
		}
		for (int i = 0; i < static_cast<int>(mt_values.size()); i++)
		{
			int mt = mt_values[i];
			int ty = abs(ace_xs_data[nuc_name].getTYValue(mt));
			if (ty > 100)
			{
				emission_mt.push_back(mt + eMTEnergyDependentNeutronEmission);
				sigwk.push_back(mt);
			}
		}

		for (int i = 0; i < static_cast<int>(sigwk.size()); i++)
		{
			for (int ib = 0; ib < num_bgxs; ib++)
				for (int ie = 0; ie < mg_max_num_energy; ie++)
				{
					eff_xs_mg[ib][ie] = 0.0;
				}
			for (int ib = 0; ib < num_bgxs; ib++)
			{
				REAL bgxs = background_xs_set[ib];
				vector<REAL> wgt_uf(mg_max_num_energy);
				for (int mg = 0; mg < mg_max_num_energy; mg++)
				{
					wgt_uf[mg] = 0.0;
				}
				for (int ie = 0; ie < uf_max_num_energy; ie++)
				{
					int mg = uf_to_mg_group[ie];
					REAL ene = uf_energy_midpoint[ie];
					REAL val_uf = getUFSpectrum(ie, ib);
					REAL sig = 0.0;
					if (sigwk[i] != eMTFission)
						sig = ace_xs_data[nuc_name].getXS(sigwk[i], ene, bgxs);
					else
						sig = ace_xs_data[nuc_name].getFissionXS(ene, bgxs);

					val_uf *= sig;
					val_uf *= uf_energy_delta[ie];
					wgt_uf[mg] += val_uf;
					REAL emission = 0.0;
					if (emission_mt[i] == eMTNuTotal)
						emission = ace_xs_data[nuc_name].getNu(eNuTotal, ene);
					else if (emission_mt[i] == eMTNuDelayed)
						emission = ace_xs_data[nuc_name].getNu(eNuDelayed, ene);
					else
						emission = ace_xs_data[nuc_name].getEnergyDependentNeutronYieldInDLW(sigwk[i], ene);
					eff_xs_mg[ib][mg] += emission * val_uf;
				}
				for (int mg = 0; mg < mg_max_num_energy; mg++)
				{
					if (wgt_uf[mg] != 0.0)
						eff_xs_mg[ib][mg] /= wgt_uf[mg];
				}
			}
			eff_xs_mg_array.insert(make_pair(emission_mt[i], eff_xs_mg));
		}

		//misc parameters ... set zero values here
		//actual values are set in FMDataContainer::setMisc1DParameters
		for (int ib = 0; ib < num_bgxs; ib++)
			for (int ie = 0; ie < mg_max_num_energy; ie++)
				eff_xs_mg[ib][ie] = 0.0;
		eff_xs_mg_array.insert(make_pair(eMTAverageLethargy, eff_xs_mg));
		eff_xs_mg_array.insert(make_pair(eMTAverageMubar, eff_xs_mg));
		eff_xs_mg_array.insert(make_pair(eMTSlowingDownXi, eff_xs_mg));
		eff_xs_mg_array.insert(make_pair(eMTSlowingDownGamma, eff_xs_mg));
		eff_xs_mg_array.insert(make_pair(eMTAverageInverseVerocity, eff_xs_mg));

		xs_mg_1d_vector.insert(make_pair(nuc_name, eff_xs_mg_array));
	}
}
void FMDataContainer::calcUFSpectrumHomo()
{
	if (ruc_zaid.size() == 0)
		calcUFSpectrumHomoAsymptotic();
	else
		calcUFSpectrumHomoResoUpscat();
}
void FMDataContainer::calcUFSpectrumHomoAsymptotic()
{
	//source option
	bool slowing_down = true;
	if (sld_calc_option == eFMNarrowResonanceCalc) slowing_down = false;

	//alpha for bg cross sections
	REAL aw = moderator_aw;
	REAL alpha_b = (aw - 1) * (aw - 1) / ((aw + 1) * (aw + 1));

	string bgaw = my_to_string(moderator_aw);
	vector<int>& upper_fg_bg = uf_slowdown_upper_group[bgaw];

	//set background xs
	vector<REAL> bg_xs = background_xs_set;

	//flux calculations
	UFRegionData& ufr = uf_region_data;
	for (int ib = 0; ib < static_cast<int>(bg_xs.size()); ib++)
	{
		REAL sfg_prev = 0.0, sfg = 0.0;
		for (int ie = 0; ie < uf_max_num_energy; ie++)
		{

			REAL ene = uf_energy_midpoint[ie];

			//source 
			REAL src, src_nr;
			REAL sigb = bg_xs[ib] * uf_region_data.nuc_dens_sum;
			if (slowing_down)
			{
				//using recurrent formula (Handbook of Nuclear Engineering, Chap.9, Eq.(199)
				calcSlowingDownSourceRecurrent(ufr.micsc[ib], bg_xs[ib], ufr.nuc_dens, ufr.nuc_dens_sum, ufr.alpha,
					alpha_b, ufr.upper_fg, upper_fg_bg, uf_flux[ib], sfg_prev, sfg, ie);	//elastic scattering
				sfg_prev = sfg;
				src = sfg + fixed_source.getChiUFG(ie);	//fission source
				uf_flux[ib][ie] = calcFlux(ufr.macst[ib][ie], sigb, src);
				uf_sld_source[ib][ie] = sfg;
				uf_source[ib][ie] = src;
				ufr.macst_macsb[ie] = ufr.macst[ib][ie] + sigb;
			}
			//NR approximation ... always calculate
			src_nr = (bg_xs[ib] * ufr.nuc_dens_sum + ufr.mac_potential_xs) * weighting_spectrum.getSpectrum(ene);
			ufr.macst_macsb[ie] = ufr.macst[ib][ie] + sigb;
			uf_flux_nr[ib][ie] = calcFlux(ufr.macst[ib][ie], sigb, src_nr);
			if (slowing_down == false)
			{
				uf_source[ib][ie] = src_nr;
				uf_flux[ib][ie] = uf_flux_nr[ib][ie];
			}
		}

		//check calculated flux is finite value
		bool finite = true;
		for (int ie = 0; ie < uf_max_num_energy; ie++)
		{
			if (std::isfinite(uf_flux[ib][ie]) == false)
			{
				finite = false;
				break;
			}
		}
		if (finite == false)
		{
			cout << endl;
			cout << " Flux value is not finite in the slowing down calculation. NR flux is used instead." << endl;
			cout << " Background cross section :" << scientific << setprecision(4) << setw(15) << bg_xs[ib] << endl;
			for (int ie = 0; ie < uf_max_num_energy; ie++)
				uf_flux[ib][ie] = uf_flux_nr[ib][ie];
		}

		//normalize flux
		normalizeFlux(uf_flux[ib]);
		normalizeFlux(uf_flux_nr[ib]);
		for (int ie = 0; ie < static_cast<int>(ufr.macst_macsb.size()); ie++)
			uf_sig_total_sigb[ib][ie] = ufr.macst_macsb[ie];
	}
	for (int ib = 0; ib < static_cast<int>(ufr.macst.size()); ib++)
		for (int ie = 0; ie < static_cast<int>(ufr.macst[ib].size()); ie++)
			uf_sig_total[ib][ie] = ufr.macst[ib][ie];
}
void FMDataContainer::calcUFSpectrumHomoResoUpscat()
{
	//source option
	if (sld_calc_option == eFMNarrowResonanceCalc)
		printError(" Resonance up-scattering correction can be used only with slowind down calculation option");

	//alpha for bg cross sections
	REAL aw = moderator_aw;
	REAL alpha_b = (aw - 1) * (aw - 1) / ((aw + 1) * (aw + 1));

	string bgaw = my_to_string(moderator_aw);
	vector<int>& upper_fg_bg = uf_slowdown_upper_group[bgaw];

	//set background xs
	vector<REAL> bg_xs = background_xs_set;

	//prepare resonance up-scattering kernel
	prepResoUpscatKernel(uf_region_data);

	//flux calculations
	UFRegionData& ufr = uf_region_data;
	vector<REAL> uf_flux_wk;
	uf_flux_wk.resize(uf_max_num_energy);
	vector<REAL> uf_sld_source_wk;
	uf_sld_source_wk.resize(uf_max_num_energy);
	vector<REAL> uf_sld_source_original;
	uf_sld_source_original.resize(uf_max_num_energy);
	vector<vector<REAL> > micsc_zero;
	micsc_zero.resize(ufr.num_nucl);
	for (int i = 0; i < ufr.num_nucl; i++)
		micsc_zero[i].resize(uf_max_num_energy);

	REAL bg_xs_zero = 0.0;
	for (int ib = 0; ib < static_cast<int>(bg_xs.size()); ib++)
	{
		//set partially zero scattering cross section (zero for E < RESO_UPSCAT_EMAX)
		for (int i = 0; i < ufr.num_nucl; i++)
		{
			for (int j = 0; j < uf_max_num_energy; j++)
			{
				REAL ene = uf_energy_midpoint[j];
				if (ene > RESO_UPSCAT_EMAX)
					micsc_zero[i][j] = ufr.micsc[ib][i][j];
				else
					micsc_zero[i][j] = 0.0;
			}
		}

		//once perform slowing down calculation to obtain initial uf-flux
		REAL sfg_prev = 0.0, sfg = 0.0;
		for (int ie = 0; ie < uf_max_num_energy; ie++)
		{
			//source 
			REAL src;
			REAL sigb = bg_xs[ib] * uf_region_data.nuc_dens_sum;

			//using recurrent formula (Handbook of Nuclear Engineering, Chap.9, Eq.(199)
			calcSlowingDownSourceRecurrent(ufr.micsc[ib], bg_xs[ib], ufr.nuc_dens, ufr.nuc_dens_sum, ufr.alpha,
				alpha_b, ufr.upper_fg, upper_fg_bg, uf_flux[ib], sfg_prev, sfg, ie);	//elastic scattering
			sfg_prev = sfg;
			uf_sld_source_original[ie] = sfg;
			src = sfg + fixed_source.getChiUFG(ie);	//fission source
			uf_flux[ib][ie] = calcFlux(ufr.macst[ib][ie], sigb, src);

			//NR approximation ... always calculate
			REAL ene = uf_energy_midpoint[ie];
			REAL src_nr = (bg_xs[ib] * ufr.nuc_dens_sum + ufr.mac_potential_xs) * weighting_spectrum.getSpectrum(ene);
			uf_flux_nr[ib][ie] = calcFlux(ufr.macst[ib][ie], sigb, src_nr);

			ufr.macst_macsb[ie] = ufr.macst[ib][ie] + sigb;
		}

		//save previous flux
		for (int ie = 0; ie < uf_max_num_energy; ie++)
			uf_flux_wk[ie] = uf_flux[ib][ie];

		//calculate slowing down source. Zero scattering xs for E < RESO_UPSCAT_EMAX
		for (int ie = 0; ie < uf_max_num_energy; ie++)
		{
			REAL ene = uf_energy_midpoint[ie];

			//using recurrent formula (Handbook of Nuclear Engineering, Chap.9, Eq.(199)
			if (ene > RESO_UPSCAT_EMAX)
			{
				calcSlowingDownSourceRecurrent(ufr.micsc[ib], bg_xs[ib], ufr.nuc_dens, ufr.nuc_dens_sum, ufr.alpha,
					alpha_b, ufr.upper_fg, upper_fg_bg, uf_flux[ib], sfg_prev, sfg, ie);	//elastic scattering
			}
			else
			{
				calcSlowingDownSourceRecurrent(micsc_zero, bg_xs_zero, ufr.nuc_dens, ufr.nuc_dens_sum, ufr.alpha,
					alpha_b, ufr.upper_fg, upper_fg_bg, uf_flux[ib], sfg_prev, sfg, ie);	//elastic scattering
			}

			sfg_prev = sfg;
			uf_sld_source_wk[ie] = sfg;
		}

		//recalculate uf-spectra for specific energy range (E < RESO_UPSCAT_EMAX)
		//calculate upscatter/slowing down source in this energy range

		int MAX_ITE = 2;
#if 0
		vector<vector<REAL> > uf_flux_output;
		uf_flux_output.resize(MAX_ITE);
		for (int i = 0; i < MAX_ITE; i++)
			uf_flux_output[i].resize(uf_max_num_energy);
#endif
		for (int i = 0; i < MAX_ITE; i++)
		{
			//reset slowing down source to zero
			for (int ie = 0; ie < uf_max_num_energy; ie++)
				uf_sld_source[ib][ie] = 0.0;

			for (int ie = 0; ie < uf_max_num_energy; ie++)
			{
				REAL ene = uf_energy_midpoint[ie];
				if (ene > RESO_UPSCAT_EMAX) continue;

				if (ene < RESO_UPSCAT_EMIN)
				{
					//use asympotic when ene < RESO_UPSCAT_EMIN
					calcSlowingDownSourceAsymptotic(uf_sld_source[ib], ufr.micsc[ib], bg_xs[ib], ufr.nuc_dens, ufr.nuc_dens_sum,
						ufr.alpha, alpha_b, uf_flux[ib], ie);
				}
				else
				{
					//consider resonance up-scatter for RESO_UPSCAT_EMIN < ene < RESO_UPSCAT_EMAX
					calcSlowingDownSourceResoUpscat(uf_sld_source[ib], uf_sld_source_wk, ib, ufr.micsc[ib], bg_xs[ib], ufr.nuc_dens, ufr.nuc_dens_sum,
						ufr.alpha, alpha_b, ufr, uf_flux[ib], ie);
				}

				REAL sigb = bg_xs[ib] * uf_region_data.nuc_dens_sum;

				//calculate flux
				sfg = uf_sld_source[ib][ie] + uf_sld_source_wk[ie];
				REAL src = sfg + fixed_source.getChiUFG(ie);	//fission source
				uf_flux[ib][ie] = calcFlux(ufr.macst[ib][ie], sigb, src);
				uf_source[ib][ie] = src;
			}
#if 0
			for (int ie = 0; ie < uf_max_num_energy; ie++)
				uf_flux_output[i][ie] = uf_flux[ib][ie];
#endif
		}

#if 0
		ofstream of;
		of.open("debug.txt");
		for (int ie = 0; ie < uf_max_num_energy; ie ++)
		{
			REAL ene = uf_energy_midpoint[ie];
			if (ene > 250.0 || ene < 1.0) continue;
			of << scientific << setprecision(5);
			of << setw(10) << ie;
			of << setw(15) << uf_energy_midpoint[ie];
			//for (int i = 0; i < MAX_ITE; i++)
			//	of << setw(15) << uf_flux_output[i][ie];
			of << setw(15) << uf_flux[ib][ie];
			of << setw(15) << uf_flux_wk[ie];
			of << endl;
		}
		of.close();
#endif

		normalizeFlux(uf_flux[ib]);
		normalizeFlux(uf_flux_nr[ib]);
		for (int ie = 0; ie < static_cast<int>(ufr.macst_macsb.size()); ie++)
			uf_sig_total_sigb[ib][ie] = ufr.macst_macsb[ie];
	}
	for (int ib = 0; ib < static_cast<int>(ufr.macst.size()); ib++)
		for (int ie = 0; ie < static_cast<int>(ufr.macst[ib].size()); ie++)
			uf_sig_total[ib][ie] = ufr.macst[ib][ie];
#if 0
	ofstream of;
	of.open("debug.txt");
	for (int ie = 0; ie < uf_max_num_energy; ie++)
	{
		if (uf_energy_midpoint[ie] > 250.0) continue;
		of << setw(10) << ie;
		of << scientific << setprecision(5);
		of << setw(15) << uf_energy_midpoint[ie];
		for (int ib = 0; ib < (int)background_xs_set.size(); ib++)
		{
			of << setw(15) << uf_flux[ib][ie];
			of << setw(15) << uf_flux_wk[ie];
		}
		of << endl;
	}
	of.close();
#endif
}
void FMDataContainer::prepResoUpscatKernel(UFRegionData& ufr)
{

	print2ndHeader(" Preparing resonance up-scattering kernel");

	for (int in = 0; in < (int) ufr.nuc_dens.size(); in++)
	{
		int nuc = ufr.ruc_index[in];
		if (nuc < 0) continue;			//asymptotic treatment if nuc < 0 (== -1)

		string zaid = ufr.ace_xs_pointer[in]->getZaid();
		REAL aw = ufr.ace_xs_pointer[in]->getAW();
		REAL temp = ufr.ace_xs_pointer[in]->getKelvin();

		REAL kt = BOLTZMANN_CONSTANT * temp;
		const int NUM_DIV = 20;
		RUCKernelData ruc_wk;
		ruc_wk.initialize(2*NUM_DIV+1);
		vector<RUCKernelData> ruc_vec;
		ruc_vec.clear();
		ruc_uf_start_group = -1;
		ruc_uf_end_group = -1;

		for (int ie = 0; ie < uf_max_num_energy; ie++)
		{
			REAL ein = uf_energy_midpoint[ie];
			if (ein > RESO_UPSCAT_EMAX) continue;
			if (ruc_uf_start_group < 0) ruc_uf_start_group = ie;
			if (ein < RESO_UPSCAT_EMIN) continue;
			ruc_uf_end_group = ie;

			if ((ie- ruc_uf_start_group) % 1000 == 0)
			{
				cout << "  Doing processing :";
				cout << setw(15) << zaid;
				cout << " : incident energy (eV) :";
				cout << fixed << setprecision(3) << setw(10) << ein;
				cout << " : no. of energy grid :";
				cout << setw(7) << ie - ruc_uf_start_group;
				cout << endl;
			}

			REAL eo_h = ein;
			REAL eo_l = ein;

			//set upper energy limit
			REAL eps = 1.0e-4;
			REAL de_up = kt / aw * (sqrt(aw * ein / kt) + 1.0) * (sqrt(aw * ein / kt) + 1.0) - ein;
			RUCKernelValue sc_self = calcResoUpscatKernel(ein, ein, aw, temp, nuc);
			for (int i = 1; i < 10; i++)
			{
				eo_h = ein + de_up * (REAL)i;
				RUCKernelValue val = calcResoUpscatKernel(ein, eo_h, aw, temp, nuc);
				if (abs(val.p0 / sc_self.p0) < eps) break;
			}

			//set lower energy limit
			REAL de_dn = ein * (1.0 - ufr.alpha[in]) / 2.0;
			for (int i = 1; i < 10; i++)
			{
				eo_l = ein - de_dn * (REAL)i;
				RUCKernelValue val = calcResoUpscatKernel(ein, eo_l, aw, temp, nuc);
				if (abs(val.p0 / sc_self.p0) < eps) break;
			}

			ruc_wk.ein = ein;
			ruc_wk.eout_upper = eo_h;
			ruc_wk.eout_lower = eo_l;
			ruc_wk.uf_upper_group = getUFgroup(eo_h);
			ruc_wk.uf_lower_group = getUFgroup(eo_l);
			ruc_wk.uf_in_group = ie;

			//calculate scattering kernel
			for (int i = 0; i <= NUM_DIV; i++)
			{
				ruc_wk.egrid[i] = eo_l + (ein - eo_l) * (REAL)i / (REAL)NUM_DIV;
				RUCKernelValue sc = calcResoUpscatKernel(ein, ruc_wk.egrid[i], aw, temp, nuc);
				ruc_wk.kernel_p0[i] = sc.p0;
				ruc_wk.kernel_p1[i] = sc.p1;
			}
			for (int i = 1; i <= NUM_DIV; i++)
			{
				ruc_wk.egrid[i + NUM_DIV] = ein + (eo_h - ein) * (REAL)i / (REAL)NUM_DIV;
				RUCKernelValue sc = calcResoUpscatKernel(ein, ruc_wk.egrid[i + NUM_DIV], aw, temp, nuc);
				ruc_wk.kernel_p0[i + NUM_DIV] = sc.p0;
				ruc_wk.kernel_p1[i + NUM_DIV] = sc.p1;
			}

			//normalize
			REAL sum = 0.0;
			for (int i = 0; i < (int)ruc_wk.kernel_p0.size() - 1; i++)
				sum += (ruc_wk.kernel_p0[i + 1] + ruc_wk.kernel_p0[i]) / 2.0 * (ruc_wk.egrid[i + 1] - ruc_wk.egrid[i]);

			for (int i = 0; i < (int)ruc_wk.kernel_p0.size(); i++)
			{
				ruc_wk.kernel_p0[i] /= sum;
				ruc_wk.kernel_p1[i] /= sum;
			}

			ruc_vec.push_back(ruc_wk);

		}
		ruc_kernel_data.insert(make_pair(zaid, ruc_vec));

		cout << setw(15) << zaid;
		cout << " : total number of energy grid : " << ruc_vec.size() << endl;
	}
}
void FMDataContainer::calcSlowingDownSourceRecurrent(vector<vector<REAL> >& micsc, REAL& sig_b,
	vector<REAL>& nuc_dens, REAL& nuc_dens_sum,
	vector<REAL>& alpha, REAL& alpha_b,
	vector<vector<int>*>& upper_fg, vector<int>& upper_fg_bg,
	vector<REAL>& flux, REAL& sfg_prev, REAL& sfg, int& ie)
{
	//1st energy group
	sfg = 0.0;
	if (ie == 0) return;

	//from 2nd to last energy groups using recurrent relation
	sfg = sfg_prev;

	//actual nuclides
	for (int in = 0; in < static_cast<int>(nuc_dens.size()); in++)
	{
		//addition from previous fine group
		int j = ie - 1;
		if ((*upper_fg[in])[ie] <= j)
		{
			REAL val = micsc[in][j] * nuc_dens[in] * flux[j] * uf_energy_delta[j];
			val /= ((1.0 - alpha[in]) * uf_energy_midpoint[j]);
			sfg += val;
		}
		int jsta, jend;
		jsta = (*upper_fg[in])[ie - 1];
		jend = (*upper_fg[in])[ie];
		for (int k = jsta; k < jend; k++)
		{
			REAL val = micsc[in][k] * nuc_dens[in] * flux[k] * uf_energy_delta[k];
			val /= ((1.0 - alpha[in]) * uf_energy_midpoint[k]);
			sfg -= val;
		}
	}

	if (sig_b == 0.0) return;

	//background cross section
	//addition from previous fine group
	int j = ie - 1;
	if (upper_fg_bg[ie] <= j)
	{
		REAL val = sig_b * nuc_dens_sum * flux[j] * uf_energy_delta[j];
		val /= ((1.0 - alpha_b) * uf_energy_midpoint[j]);
		sfg += val;
	}
	int jsta, jend;
	jsta = upper_fg_bg[ie - 1];
	jend = upper_fg_bg[ie];
	for (int k = jsta; k < jend; k++)
	{
		REAL val = sig_b * nuc_dens_sum * flux[k] * uf_energy_delta[k];
		val /= ((1.0 - alpha_b) * uf_energy_midpoint[k]);
		sfg -= val;
	}

}
void FMDataContainer::calcSlowingDownSourceAsymptotic(vector<REAL>& sld_src, vector<vector<REAL> >& micsc, REAL& sig_b,
	vector<REAL>& nuc_dens, REAL& nuc_dens_sum,
	vector<REAL>& alpha, REAL& alpha_b,
	vector<REAL>& flux, int& ie)
{
	if (ie >= uf_max_num_energy - 1) return;

	//actual nuclides
	for (int in = 0; in < static_cast<int>(nuc_dens.size()); in++)
	{
		REAL val = micsc[in][ie] * nuc_dens[in] * flux[ie] * uf_energy_delta[ie];
		REAL ecur = uf_energy_midpoint[ie];
		REAL elow = alpha[in] * ecur;
		for (int j = ie + 1; j < uf_max_num_energy; j++)
		{
			if (uf_energy_midpoint[j] > elow)
				sld_src[j] += val / (ecur - elow);
		}
	}

	if (sig_b == 0.0) return;

	//background cross section
	REAL val = sig_b * nuc_dens_sum * flux[ie] * uf_energy_delta[ie];
	REAL ecur = uf_energy_midpoint[ie];
	REAL elow = alpha_b * ecur;
	for (int j = ie + 1; j < uf_max_num_energy; j++)
	{
		if (uf_energy_midpoint[j] > elow)
			sld_src[j] += val / (ecur - elow);
	}
}
void FMDataContainer::calcSlowingDownSourceResoUpscat(vector<REAL>& sld_src, vector<REAL>& sld_src_wk, int& ib, vector<vector<REAL> >& micsc, REAL& sig_b,
	vector<REAL>& nuc_dens, REAL& nuc_dens_sum,
	vector<REAL>& alpha, REAL& alpha_b, UFRegionData& ufr,
	vector<REAL>& flux, int& ie)
{
	if (ie >= uf_max_num_energy - 1) return;

	//actual nuclides
	for (int in = 0; in < static_cast<int>(nuc_dens.size()); in++)
	{
		int nuc = ufr.ruc_index[in];

		if (nuc < 0)
		{
			//asymptotic treatment if nuc < 0 (== -1)
			REAL val = micsc[in][ie] * nuc_dens[in] * flux[ie] * uf_energy_delta[ie];
			REAL ecur = uf_energy_midpoint[ie];
			REAL elow = alpha[in] * ecur;
			REAL fact = 1.0 / (ecur - elow);
			for (int j = ie + 1; j < uf_max_num_energy; j++)
			{
				if (uf_energy_midpoint[j] > elow)
					sld_src[j] += val * fact;
			}
		}
		else
		{
			//resonance upscattering treatment
			//up-scattering source
			string zaid = ufr.nuc_name[in];
			vector<RUCKernelData>& rkd_vec = ruc_kernel_data[zaid];
			REAL eout = uf_energy_midpoint[ie];
			for (int j = ie+1; j < ruc_uf_end_group; j++)
			{
				REAL val = micsc[in][j] * nuc_dens[in] * flux[j] * uf_energy_delta[j];
				REAL ker = rkd_vec[j - ruc_uf_start_group].getValueP0(eout);
				sld_src[ie] += val*ker;
			}

			//calculate flux before down scattering source calculation
			REAL src = sld_src[ie] + sld_src_wk[ie] + fixed_source.getChiUFG(ie);	//fission source
			REAL macsigb = background_xs_set[ib] * uf_region_data.nuc_dens_sum;
			REAL flux_wk =  calcFlux(ufr.macst[ib][ie], macsigb, src);

			//down-scattering source
#if 0
			REAL val = micsc[in][ie] * nuc_dens[in] * flux[ie] * uf_energy_delta[ie];		//Jacobi iteration
#else
			REAL val = micsc[in][ie] * nuc_dens[in] * flux_wk * uf_energy_delta[ie];	//Gauss-Seidel iteration (faster)
#endif
			for (int j = ie + 1; j < uf_max_num_energy; j++)
			{
				REAL eout = uf_energy_midpoint[j];
				REAL elow = rkd_vec[ie - ruc_uf_start_group].eout_lower;
				if (eout < elow) break;
				REAL ker = rkd_vec[ie - ruc_uf_start_group].getValueP0(eout);
				sld_src[j] += val*ker;
			}
		}
	}

	if (sig_b == 0.0) return;

	//background cross section
	REAL ecur = uf_energy_midpoint[ie];
	REAL elow = alpha_b * ecur;
	REAL val = sig_b * nuc_dens_sum * flux[ie] * uf_energy_delta[ie];
	REAL fact = 1.0 / (ecur - elow);
	val *= fact;
	for (int j = ie + 1; j < uf_max_num_energy; j++)
	{
		if (uf_energy_midpoint[j] > elow)
			sld_src[j] += val;
	}
}
RUCKernelValue FMDataContainer::calcResoUpscatKernel(REAL ein, REAL eout, REAL aw, REAL temp, int nuc)
{
	REAL beta = (aw + 1.0) / aw;
	REAL kt = BOLTZMANN_CONSTANT * temp;
	REAL emax = ein;
	if (eout > ein) emax = eout;
	REAL emin = ein;
	if (eout < ein) emin = eout;
	REAL epsmax = sqrt((aw + 1.0) * emax / kt);
	REAL epsmin = sqrt((aw + 1.0) * emin / kt);
	REAL tp = (epsmax + epsmin) / 2.0;
	REAL tm = (epsmax - epsmin) / 2.0;

	//search range of integral: sqrt(beta) * (sqrt(aw * ein / kt) +/- 10)
	const REAL eps = 1.0e-5;
	REAL t_in = sqrt(beta) * sqrt(aw * ein / kt);
	REAL t_max = t_in;
	REAL t_min = t_in;
	RUCKernelValue val_max;
	val_max.p0 = 0.0;
	val_max.p1 = 0.0;
	vector<REAL> val_wk(21);
	for (int i = -10; i <= 10; i++)
	{
		REAL t = t_in + sqrt(beta) * (REAL)i;
		RUCKernelValue val = calcResoUpscatIntegrand(nuc, t, ein, beta, kt, aw, tp, tm, epsmax, epsmin);
		val_wk[10+i] = val.p0;
		if (val.p0 > val_max.p0) val_max.p0 = val.p0;
	}
	for (int i = -10; i < 0; i++)
	{
		REAL t = t_in + sqrt(beta) * (REAL)i;
		if (val_wk[10+i] > val_max.p0*eps)
		{
			t_min = t - sqrt(beta);
			break;
		}
	}
	for (int i = 10; i >= 0; i--)
	{
		REAL t = t_in + sqrt(beta) * (REAL)i;
		if (val_wk[10+i] > val_max.p0*eps)
		{
			t_max = t + sqrt(beta);
			break;
		}
	}

	RUCKernelValue sum;
	sum.p0 = 0.0;
	sum.p1 = 0.0;

	//adaptive integration
#if 1
	int num_div = 5;
	for (int i = 0; i < num_div; i++)
	{
		REAL tpe = tp * (1.0 - 1.0e-6);
		REAL t0 = (tpe - t_min) / (REAL)num_div * (REAL)i + t_min;
		REAL t1 = (tpe - t_min) / (REAL)num_div * (REAL)(i+1) + t_min;
		REAL dt = tpe - t_min;
		RUCKernelValue val0 = calcResoUpscatIntegrand(nuc, t0, ein, beta, kt, aw, tp, tm, epsmax, epsmin);
		RUCKernelValue val1 = calcResoUpscatIntegrand(nuc, t1, ein, beta, kt, aw, tp, tm, epsmax, epsmin);
		RUCKernelValue val = doAdaptiveIntegrationResoUpscat(nuc, t0, t1, dt, val_max, val0, val1, ein, beta, kt, aw, tp, tm, epsmax, epsmin);
		sum.p0 += val.p0;
		sum.p1 += val.p1;
	}
	for (int i = 0; i < num_div; i++)
	{
		REAL tpe = tp * (1.0 + 1.0e-6);
		REAL t0 = (t_max - tpe) / (REAL)num_div * (REAL)i + tpe;
		REAL t1 = (t_max - tpe) / (REAL)num_div * (REAL)(i + 1) + tpe;
		REAL dt = t_max - tpe;
		RUCKernelValue val0 = calcResoUpscatIntegrand(nuc, t0, ein, beta, kt, aw, tp, tm, epsmax, epsmin);
		RUCKernelValue val1 = calcResoUpscatIntegrand(nuc, t1, ein, beta, kt, aw, tp, tm, epsmax, epsmin);
		RUCKernelValue val = doAdaptiveIntegrationResoUpscat(nuc, t0, t1, dt, val_max, val0, val1, ein, beta, kt, aw, tp, tm, epsmax, epsmin);
		sum.p0 += val.p0;
		sum.p1 += val.p1;
	}
#else
	int num_div = 1000;
	for (int i = 0; i < num_div; i++)
	{
		REAL t = (tp - t_min) / (REAL)num_div * ((REAL)i + 0.5) + t_min;
		REAL dt = (tp - t_min)/(REAL) num_div;
		RUCKernelValue val = calcResoUpscatIntegrand(nuc, t, ein, beta, kt, aw, tp, tm, epsmax, epsmin);
		sum.p0 += val.p0 * dt;
		sum.p1 += val.p1 * dt;
	}
	for (int i = 0; i < num_div; i++)
	{
		REAL t = (t_max - tp) / (REAL)num_div * ((REAL)i + 0.5) + tp;
		REAL dt = (t_max - tp)/(REAL)num_div;
		RUCKernelValue val = calcResoUpscatIntegrand(nuc, t, ein, beta, kt, aw, tp, tm, epsmax, epsmin);
		sum.p0 += val.p0 * dt;
		sum.p1 += val.p1 * dt;
	}
#endif

	REAL beta2 = beta * beta;
	sum.p0 *= beta2 * beta2 * sqrt(beta) / 4.0 / ein;
	sum.p1 *= beta2 * beta2 * sqrt(beta) / 4.0 / ein;

	return sum;
}
void FMDataContainer::normalizeFlux(vector<REAL>& flux)
{
	DOUBLE sum = 0.0;
	for (int ie = 0; ie < uf_max_num_energy; ie++)
		sum += flux[ie] * uf_energy_delta[ie];
	for (int ie = 0; ie < uf_max_num_energy; ie++)
		flux[ie] /= sum;
}
void FMDataContainer::setMisc1DParameters(string zaid)
{
	//number of background cross sections
	int num_bgxs = background_xs_set.size();

	//misc parameters
	//average lethargy
	REAL ezero = 1.0e+7;	//Upper energy defined in NJOPY2016
	for (int ib = 0; ib < num_bgxs; ib++)
		for (int ie = 0; ie < mg_max_num_energy; ie++)
			xs_mg_1d_vector[zaid][eMTAverageLethargy][ib][ie] = log(ezero/sqrt(mg_energy_boundary[ie]*mg_energy_boundary[ie + 1]));

	//Mu-bar (average scattering cosine, sig-s(p1)/sig-s(p0))
	//Slowingdown Xi, Gamma
	REAL alf = getAlpha(zaid);
	REAL aw  = getAW(zaid);
	REAL eps = 0.0;
	if (alf != 0.0)
		eps = -log(alf);
	else
		eps = 1.0e+20;	//sufficiently large value

	for (int ib = 0; ib < num_bgxs; ib++)
	{
		for (int mg = 0; mg < mg_max_num_energy; mg++)
		{
			if (max_pl > 0)
			{
				REAL valp0 = 0.0;
				REAL valp1 = 0.0;
				for (int iig = 0; iig < mg_max_num_energy; iig++)
				{
					valp0 += xs_mg_2d_matrix[zaid][eMTElasticScattering][ib].get(mg,iig,0);
					valp1 += xs_mg_2d_matrix[zaid][eMTElasticScattering][ib].get(mg,iig,1);
				}
				if (valp0 != 0.0)
					xs_mg_1d_vector[zaid][eMTAverageMubar][ib][mg] = valp1 / valp0;
			}
			
			//these fomulas are approximation. taken from J. Nucl. Sci. Technol. 9[11], pp.662-669 (1972). 
			//(A.6), (A.7), (A.9) are used while (A.8) is not used.
			//(8.37) in K. Kobayashi's "Gensiro-butsuri" is used instead of (A.8).
			REAL x0 = 1.0 - alf * eps / (1.0 - alf);
			REAL g0 = 1.0 - (1.0 - x0) * eps / 2.0 / x0;
			REAL mubar_l = xs_mg_1d_vector[zaid][eMTAverageMubar][ib][mg];
			REAL mubar_c = (mubar_l - 2.0/3.0/aw) / (1.0 - 3.0 / 5.0 / aw / aw);
			REAL b = ((alf * x0 + 2.0 * x0 * g0) / (1 - alf) - 0.5) / (x0 / (1.0 - alf) - 0.5);
			REAL x = x0 * (1 - mubar_c);
			REAL g = x0 * g0 * (1.0 - mubar_c * b) / x;
			xs_mg_1d_vector[zaid][eMTSlowingDownXi][ib][mg] = x;
			xs_mg_1d_vector[zaid][eMTSlowingDownGamma][ib][mg] = g;
		}
	}

	//Average inverse velocity
	for (int ib = 0; ib < num_bgxs; ib++)
	{
		vector<REAL> wgt_uf(mg_max_num_energy);
		for (int mg = 0; mg < mg_max_num_energy; mg++)
		{
			wgt_uf[mg] = 0.0;
		}

		for (int ie = 0; ie < uf_max_num_energy; ie++)
		{
			int mg = uf_to_mg_group[ie];
			REAL ene = uf_energy_midpoint[ie];
			REAL val_uf = getUFSpectrum(ie, ib);
			REAL vel = sqrt(2.0*ene*EV2J / NEUTRON_MASS); //[m/s]
			val_uf *= uf_energy_delta[ie];
			xs_mg_1d_vector[zaid][eMTAverageInverseVerocity][ib][mg] += 1.0 / vel * val_uf;
			wgt_uf[mg] += val_uf;
		}
		for (int mg = 0; mg < mg_max_num_energy; mg++)
		{
			if (wgt_uf[mg] != 0.0)
				xs_mg_1d_vector[zaid][eMTAverageInverseVerocity][ib][mg] /= wgt_uf[mg];
		}
	}
}
void FMDataContainer::normalizeEnergyTransferMatrix(string zaid, int mt, int ib)
{
	if (xs_mg_2d_matrix.find(zaid) == xs_mg_2d_matrix.end())
		return;

	if (xs_mg_2d_matrix[zaid].find(mt) == xs_mg_2d_matrix[zaid].end())
		return;

	if (ib >= static_cast<int>(xs_mg_2d_matrix[zaid][mt].size()))
		return;

	if (xs_mg_1d_vector.find(zaid) == xs_mg_1d_vector.end())
		return;

	int mt_1d_vector = mt;
	if (xs_mg_1d_vector[zaid].find(mt_1d_vector) == xs_mg_1d_vector[zaid].end())
		return;
	
	vector<vector<REAL> >& xs1d = xs_mg_1d_vector[zaid][mt_1d_vector];
	vector<REAL> ratio(mg_max_num_energy);
	for (int ig = 0; ig < mg_max_num_energy; ig++)
		ratio[ig] = 1.0;
	if (xs_mg_thermal_cutoff_ratio.find(zaid) != xs_mg_thermal_cutoff_ratio.end())
	{
		if (xs_mg_thermal_cutoff_ratio[zaid].find(mt) != xs_mg_thermal_cutoff_ratio[zaid].end())
		{
			for (int ig = 0; ig < mg_max_num_energy; ig++)
				ratio[ig] = xs_mg_thermal_cutoff_ratio[zaid][mt][ig];
		}
	}

	//cout << endl;
	//cout << " Normarization factor for marix mt " << setw(5) << mt << " background xs point " << ib << endl;
	cout << setw(15) << zaid;
	cout << setw(10) << mt;
	cout << scientific << setprecision(5);
	cout << setw(15) << background_xs_set[ib];

	if (mt == eMTFission)
	{
		//calculate normalization factor for fission cross sections (mt=18) in order to handle mt=19, 20, 21, 38
		//for mt=19, 20, 21, 38, normalization factor for mt=18 is applied
		xs_mg_2d_mt18_norm_factor.clear();
		xs_mg_2d_mt18_norm_factor.resize(mg_max_num_energy);
		FMCompressedMatrix& xs_mg_2d_matrix_wk = xs_mg_2d_matrix[zaid][eMTFission][ib];
		for (int ig = 0; ig < mg_max_num_energy; ig++)
		{
			xs_mg_2d_mt18_norm_factor[ig] = 1.0;
			REAL sum = 0.0;
			for (int iig = 0; iig < mg_max_num_energy; iig++)
				sum += xs_mg_2d_matrix_wk.get(ig,iig,0);

			if (sum != 0.0)
			{
				REAL val = nuchi_mg_1d_vector[zaid][eMTNuPrompt][ig];
				xs_mg_2d_mt18_norm_factor[ig] = xs_mg_1d_vector[zaid][eMTFission][ib][ig] * val * ratio[ig] / sum;
			}
		}
	}

	vector<REAL> norm_factor;
	norm_factor.clear();

	FMCompressedMatrix& xs_mg_2d_matrix_wk = xs_mg_2d_matrix[zaid][mt][ib];
	for (int ig = 0; ig < mg_max_num_energy; ig++)
	{
		//sum of p0 component
		REAL sum = 0.0;
		for (int iig = 0; iig < mg_max_num_energy; iig++)
			sum += xs_mg_2d_matrix_wk.get(ig,iig,0);

		if (sum != 0.0)
		{
			REAL fact = 1.0;
			if (mt == eMTFission || mt == eMTFirstChanceFission || mt == eMTSecondChanceFission
				|| mt == eMTThirdChanceFission || mt == eMTFourthChanceFission)
				fact = xs_mg_2d_mt18_norm_factor[ig];
			else
			{
				REAL val = getNumNeutronScattering(zaid, mt, ig);
				fact = xs1d[ib][ig] * val * ratio[ig] / sum;
			}

			//cout << setw(5) << ig;
			//cout << setw(15) << fixed << setprecision(6) << fact << endl;
			norm_factor.push_back(fact);

			for (int iig = 0; iig < mg_max_num_energy; iig++)
			{
				int max_pl = xs_mg_2d_matrix[zaid][mt][ib].getMaxPl();
				for (int il = 0; il < max_pl+1; il++)
					xs_mg_2d_matrix_wk.multiply(ig,iig,il,fact);
			}
		}
	}

	cout << setw(10) << norm_factor.size();

	if (norm_factor.size() < 1)
	{
		cout << endl;
	}
	else if (norm_factor.size() == 1)
	{
		cout << fixed << setprecision(6);
		cout << setw(10) << norm_factor[0];
		cout << endl;
	}
	else
	{
		REAL aveval = 0.0;
		REAL stdval = 0.0;
		REAL maxval = -10.0;
		REAL minval = 10.0;
		for (int i = 0; i < static_cast<int>(norm_factor.size()); i++)
		{
			aveval += norm_factor[i];
			stdval += norm_factor[i] * norm_factor[i];
			if (maxval < norm_factor[i]) maxval = norm_factor[i];
			if (minval > norm_factor[i]) minval = norm_factor[i];
		}
		aveval /= (REAL)norm_factor.size();
		stdval = stdval / ((REAL)norm_factor.size() - 1.0) - aveval * aveval * (REAL)norm_factor.size() / ((REAL)norm_factor.size() - 1.0);
		if (stdval >= 0.0)
			stdval = sqrt(stdval);
		else
			stdval = 0.0;

		cout << fixed << setprecision(6);
		cout << setw(10) << aveval;
		cout << setw(10) << stdval;
		cout << setw(10) << maxval;
		cout << setw(10) << minval;
		cout << endl;
	}

	if (edit_option.find(eEditOptionDebug) != edit_option.end())
	{
		for (int i = 0; i < static_cast<int>(norm_factor.size()); i++)
		{
			cout << setw(5) << i;
			cout << setw(15) << fixed << setprecision(6) << norm_factor[i] << endl;
		}
	}

}
void FMDataContainer::setSumOfInelasticXS(string zaid, vector<vector<vector<vector<REAL> > > >& matrix)
{
	int max_ng = mg_max_num_energy;
	//FMACECrossSectionProcessor& acexs = ace_xs_data[zaid];

	//allocate temporary matrix
	int num_bg_xs = background_xs_set.size();
	for (int ib = 0; ib < num_bg_xs; ib++)
	{
		for (int ig = 0; ig < max_ng; ig++)
		{
			for (int iig = 0; iig < max_ng; iig++)
			{
				for (int il = 0; il <= max_pl; il++)
					matrix[ib][ig][iig][il] = 0.0;
			}
		}
	}

	bool is_inelastic = false;
	for (int ib = 0; ib < num_bg_xs; ib++)
	{
		for (int mt = eMTInelasticScatteringBegin; mt <= eMTInelasticScatteringEnd; mt++)
		{
			if (xs_mg_2d_matrix[zaid].find(mt) == xs_mg_2d_matrix[zaid].end()) continue;
			if (ib >= static_cast<int>(xs_mg_2d_matrix[zaid][mt].size())) continue;

			is_inelastic = true;

			FMCompressedMatrix& xs_mg_2d_matrix_wk = xs_mg_2d_matrix[zaid][mt][ib];
			for (int ig = 0; ig < max_ng; ig++)
			{
				vector<vector<REAL> >& matrix_wk = matrix[ib][ig];
				for (int iig = 0; iig < max_ng; iig++)
				{
					for (int il = 0; il <= max_pl; il++)
						matrix_wk[iig][il] += xs_mg_2d_matrix_wk.get(ig,iig,il);
				}
			}
		}
	}

	vector<FMCompressedMatrix> fmc_vec;
	fmc_vec.resize(num_bg_xs);
	for (int ib = 0; ib < num_bg_xs; ib++)
		fmc_vec[ib].set(matrix[ib]);

	if (is_inelastic)
	{
		//2d matrix
		xs_mg_2d_matrix[zaid].insert(make_pair(eMTInelasticScatteringTotal, fmc_vec));

		//1d 
		if (xs_mg_1d_vector[zaid].find(eMTInelasticScatteringTotal) == xs_mg_1d_vector[zaid].end())
		{
			vector<vector<REAL> > vec;
			vec.resize(num_bg_xs);
			for (int ib = 0; ib < num_bg_xs; ib++)
				vec[ib].resize(max_ng);
			for (int ib = 0; ib < num_bg_xs; ib++)
			{
				int il = 0;
				for (int ig = 0; ig < max_ng; ig++)
				{
					REAL val = 0.0;
					for (int iig = 0; iig < max_ng; iig++)
						val += xs_mg_2d_matrix[zaid][eMTInelasticScatteringTotal][ib].get(ig, iig, il);
					vec[ib][ig] = val;
				}
			}
			xs_mg_1d_vector[zaid].insert(make_pair(eMTInelasticScatteringTotal, vec));
		}
	}
}
void FMDataContainer::setMT18FromMT19(string zaid, vector<vector<vector<vector<REAL> > > >& matrix, map<int, vector<vector<vector<vector<REAL> > > > >& matrix_map)
{
	matrix.clear();

	//set mt18 data from mt19, 20, 21, and 38

	//vector
	if (xs_mg_1d_vector[zaid].find(eMTFirstChanceFission) != xs_mg_1d_vector[zaid].end() &&
		xs_mg_1d_vector[zaid].find(eMTFission) == xs_mg_1d_vector[zaid].end())
	{

		cout << "          " + zaid + ": mt=18 (total fission) 1d cross section is reconstructed from mt19, 20, 21, 38" << endl;

		//mt18 = mt19 + mt20 + mt21 + mt38
		vector<vector<REAL> > vec;

		int max_ng = mg_max_num_energy;
		int num_bgxs = background_xs_set.size();

		//allocate temporary array
		vec.resize(num_bgxs);
		{
			for (int ib = 0; ib < static_cast<int>(vec.size()); ib++)
			{
				vec[ib].resize(max_ng);
				for (int ig = 0; ig < max_ng; ig++)
					vec[ib][ig] = 0.0;
			}
		}

		for (int ib = 0; ib < static_cast<int>(vec.size()); ib++)
		{
			for (int ig = 0; ig < max_ng; ig++)
			{
				vec[ib][ig] = xs_mg_1d_vector[zaid][eMTFirstChanceFission][ib][ig];
				if (xs_mg_1d_vector[zaid].find(eMTSecondChanceFission) != xs_mg_1d_vector[zaid].end())
					vec[ib][ig] += xs_mg_1d_vector[zaid][eMTSecondChanceFission][ib][ig];
				if (xs_mg_1d_vector[zaid].find(eMTThirdChanceFission) != xs_mg_1d_vector[zaid].end())
					vec[ib][ig] += xs_mg_1d_vector[zaid][eMTThirdChanceFission][ib][ig];
				if (xs_mg_1d_vector[zaid].find(eMTFourthChanceFission) != xs_mg_1d_vector[zaid].end())
					vec[ib][ig] += xs_mg_1d_vector[zaid][eMTFourthChanceFission][ib][ig];
			}
		}

		xs_mg_1d_vector[zaid].insert(make_pair(eMTFission, vec));
	}

	//process matrix
	if (matrix_map.find(eMTFirstChanceFission) != matrix_map.end() &&
		matrix_map.find(eMTFission) == matrix_map.end())
	{
		cout << "          " + zaid + ": mt=18 (total fission) 2d cross section is reconstructed from mt19, 20, 21, 38" << endl;

		//mt18 = mt19 + mt20 + mt21 + mt38
		int max_ng = this->mg_max_num_energy;
		int num_bgxs = background_xs_set.size();

		//allocate temporary array
		matrix.resize(num_bgxs);
		{
			for (int ib = 0; ib < static_cast<int>(matrix.size()); ib++)
			{
				matrix[ib].resize(max_ng);
				for (int ig = 0; ig < max_ng; ig++)
				{
					matrix[ib][ig].resize(max_ng);
					for (int iig = 0; iig < max_ng; iig++)
					{
						matrix[ib][ig][iig].resize(max_pl + 1);
						for (int il = 0; il <= max_pl; il++)
							matrix[ib][ig][iig][il] = 0.0;
					}
				}
			}
		}

		for (int ib = 0; ib < static_cast<int>(matrix.size()); ib++)
		{
			for (int ig = 0; ig < max_ng; ig++)
			{
				for (int iig = 0; iig < max_ng; iig++)
				{
					for (int il = 0; il <= max_pl; il++)
					{
						matrix[ib][ig][iig][il]  = matrix_map[eMTFirstChanceFission][ib][ig][iig][il];
						if (matrix_map.find(eMTSecondChanceFission) != matrix_map.end())
							matrix[ib][ig][iig][il] += matrix_map[eMTSecondChanceFission][ib][ig][iig][il];
						if (matrix_map.find(eMTThirdChanceFission) != matrix_map.end())
							matrix[ib][ig][iig][il] += matrix_map[eMTThirdChanceFission][ib][ig][iig][il];
						if (matrix_map.find(eMTFourthChanceFission) != matrix_map.end())
							matrix[ib][ig][iig][il] += matrix_map[eMTFourthChanceFission][ib][ig][iig][il];
					}
				}
			}
		}
	}
}
void FMDataContainer::setMTFromOtherMTs(string zaid, map<int, vector<FMCompressedMatrix> >& matrix_map)
{
	int to_mt;
	vector<int> from_mt;

	vector<FMCompressedMatrix> fmc_vec;
	int num_bg_xs = background_xs_set.size();
	fmc_vec.resize(num_bg_xs);

	vector<vector<vector<vector<REAL> > > > matrix;				//[ib][ig][iig][il]

	//fission
	to_mt = 18;
	from_mt.clear();
	from_mt.push_back(19); from_mt.push_back(20); from_mt.push_back(21); from_mt.push_back(38);
	setMTFromOtherMTs(zaid, to_mt, from_mt, matrix, matrix_map);
	if (matrix.size() != 0)
	{
		for (int ib = 0; ib < num_bg_xs; ib++)
			fmc_vec[ib].set(matrix[ib]);
		matrix_map.insert(make_pair(to_mt, fmc_vec));
	}

	//np
	to_mt = 103;
	from_mt.clear();
	for (int i = 600; i <= 649; i++)
		from_mt.push_back(i);
	setMTFromOtherMTs(zaid, to_mt, from_mt, matrix, matrix_map);
	if (matrix.size() != 0)
	{
		for (int ib = 0; ib < num_bg_xs; ib++)
			fmc_vec[ib].set(matrix[ib]);
		matrix_map.insert(make_pair(to_mt, fmc_vec));
	}

	//nd
	to_mt = 104;
	from_mt.clear();
	for (int i = 650; i <= 699; i++)
		from_mt.push_back(i);
	setMTFromOtherMTs(zaid, to_mt, from_mt, matrix, matrix_map);
	if (matrix.size() != 0)
	{
		for (int ib = 0; ib < num_bg_xs; ib++)
			fmc_vec[ib].set(matrix[ib]);
		matrix_map.insert(make_pair(to_mt, fmc_vec));
	}

	//nt
	to_mt = 105;
	from_mt.clear();
	for (int i = 700; i <= 749; i++)
		from_mt.push_back(i);
	setMTFromOtherMTs(zaid, to_mt, from_mt, matrix, matrix_map);
	if (matrix.size() != 0)
	{
		for (int ib = 0; ib < num_bg_xs; ib++)
			fmc_vec[ib].set(matrix[ib]);
		matrix_map.insert(make_pair(to_mt, fmc_vec));
	}

	//nh
	to_mt = 106;
	from_mt.clear();
	for (int i = 750; i <= 799; i++)
		from_mt.push_back(i);
	setMTFromOtherMTs(zaid, to_mt, from_mt, matrix, matrix_map);
	if (matrix.size() != 0)
	{
		for (int ib = 0; ib < num_bg_xs; ib++)
			fmc_vec[ib].set(matrix[ib]);
		matrix_map.insert(make_pair(to_mt, fmc_vec));
	}

	//na
	to_mt = 107;
	from_mt.clear();
	for (int i = 800; i <= 849; i++)
		from_mt.push_back(i);
	setMTFromOtherMTs(zaid, to_mt, from_mt, matrix, matrix_map);
	if (matrix.size() != 0)
	{
		for (int ib = 0; ib < num_bg_xs; ib++)
			fmc_vec[ib].set(matrix[ib]);
		matrix_map.insert(make_pair(to_mt, fmc_vec));
	}

}
void FMDataContainer::setMTFromOtherMTs(string zaid, int to_mt, vector<int> from_mt, vector<vector<vector<vector<REAL> > > >& matrix, map<int, vector<FMCompressedMatrix> >& matrix_map)
{
	matrix.clear();

	if (from_mt.size() < 1) return;

	//vector
	if (xs_mg_1d_vector[zaid].find(from_mt[0]) != xs_mg_1d_vector[zaid].end() &&
		xs_mg_1d_vector[zaid].find(to_mt) == xs_mg_1d_vector[zaid].end())
	{
		cout << "          " + zaid + ": mt=";
		cout << to_mt;
		cout << " 1d cross section is reconstructed from mt=";
		for (int i = 0; i < static_cast<int>(from_mt.size()); i++)
		{
			if (xs_mg_1d_vector[zaid].find(from_mt[i]) != xs_mg_1d_vector[zaid].end())
				cout << setw(4) << from_mt[i];
		}
		cout << endl;

		vector<vector<REAL> > vec;

		int max_ng = mg_max_num_energy;
		int num_bgxs = background_xs_set.size();

		//allocate temporary array
		vec.resize(num_bgxs);
		{
			for (int ib = 0; ib < static_cast<int>(vec.size()); ib++)
			{
				vec[ib].resize(max_ng);
				for (int ig = 0; ig < max_ng; ig++)
					vec[ib][ig] = 0.0;
			}
		}

		for (int ib = 0; ib < static_cast<int>(vec.size()); ib++)
		{
			for (int ig = 0; ig < max_ng; ig++)
			{
				vec[ib][ig] = xs_mg_1d_vector[zaid][from_mt[0]][ib][ig];
				for (int i = 1; i < static_cast<int>(from_mt.size()); i++)
				{
					if (xs_mg_1d_vector[zaid].find(from_mt[i]) != xs_mg_1d_vector[zaid].end())
						vec[ib][ig] += xs_mg_1d_vector[zaid][from_mt[i]][ib][ig];
				}
			}
		}

		xs_mg_1d_vector[zaid].insert(make_pair(to_mt, vec));
	}

	//process matrix
	if (matrix_map.find(from_mt[0]) != matrix_map.end() &&
		matrix_map.find(to_mt) == matrix_map.end())
	{
		cout << "          " + zaid + ": mt=";
		cout << to_mt;
		cout << " 2d cross section is reconstructed from mt=";
		for (int i = 0; i < static_cast<int>(from_mt.size()); i++)
		{
			if (matrix_map.find(from_mt[i]) != matrix_map.end())
				cout << setw(4) << from_mt[i];
		}
		cout << endl;

		int max_ng = this->mg_max_num_energy;
		int num_bgxs = background_xs_set.size();

		//allocate temporary array
		matrix.resize(num_bgxs);
		{
			for (int ib = 0; ib < static_cast<int>(matrix.size()); ib++)
			{
				matrix[ib].resize(max_ng);
				for (int ig = 0; ig < max_ng; ig++)
				{
					matrix[ib][ig].resize(max_ng);
					for (int iig = 0; iig < max_ng; iig++)
					{
						matrix[ib][ig][iig].resize(max_pl + 1);
						for (int il = 0; il <= max_pl; il++)
							matrix[ib][ig][iig][il] = 0.0;
					}
				}
			}
		}

		for (int ib = 0; ib < static_cast<int>(matrix.size()); ib++)
		{
			for (int ig = 0; ig < max_ng; ig++)
			{
				for (int iig = 0; iig < max_ng; iig++)
				{
					for (int il = 0; il <= max_pl; il++)
					{
						matrix[ib][ig][iig][il] = matrix_map[from_mt[0]][ib].get(ig,iig,il);
						for (int i = 1; i < static_cast<int>(from_mt.size()); i++)
						{
							if (matrix_map.find(from_mt[i]) != matrix_map.end())
								matrix[ib][ig][iig][il] += matrix_map[from_mt[i]][ib].get(ig,iig,il);
						}
					}
				}
			}
		}
	}
}
void FMDataContainer::convertThermalMaterialNameToMt(string sab_name, string zaid_thermal, int& inc_iel, int& inc_el, int& coh_el)
{
	inc_iel = 0;
	inc_el = 0;
	coh_el = 0;

	if (sab_name == "")
	{
		inc_iel = 221;
	}
	if (compareString(sab_name, "free"))
	{
		inc_iel = 221;
	}
	if (compareString(sab_name, "hh2o"))
	{
		inc_iel = 222;
	}
	if (compareString(sab_name, "poly"))
	{
		inc_iel = 223;
		inc_el = 224;
	}
	if (compareString(sab_name, "hzrh"))
	{
		inc_iel = 225;
		inc_el = 226;
	}
	if (compareString(sab_name, "benz"))
	{
		inc_iel = 227;
	}
	if (compareString(sab_name, "dd2o"))
	{
		inc_iel = 228;
	}
	if (compareString(sab_name, "graph"))
	{
		inc_iel = 229;
		coh_el = 230;
	}
	if (compareString(sab_name, "be"))
	{
		inc_iel = 231;
		coh_el = 232;
	}
	if (compareString(sab_name, "bebeo"))
	{
		inc_iel = 233;
		coh_el = 234;
	}
	if (compareString(sab_name, "zrzrh"))
	{
		inc_iel = 235;
		inc_el = 236;
	}
	if (compareString(sab_name, "obeo"))
	{
		inc_iel = 237;
		coh_el = 238;
	}
	if (compareString(sab_name, "ouo2"))
	{
		inc_iel = 239;
		coh_el = 240;
	}
	if (compareString(sab_name, "uuo2"))
	{
		inc_iel = 241;
		coh_el = 242;
	}
	if (compareString(sab_name, "al"))
	{
		inc_iel = 243;
		coh_el = 244;
	}
	if (compareString(sab_name, "fe"))
	{
		inc_iel = 245;
		coh_el = 246;
	}

	if (inc_iel == 0)
	{
		if (ace_thermal_xs_data.find(zaid_thermal) == ace_thermal_xs_data.end())
		{
			cout << zaid_thermal << endl;
			printError(" the above zaid is not found in the ace files");
		}
		else
		{
			inc_iel = 249;
			if (ace_thermal_xs_data[zaid_thermal].isIncoherentElasticScattering()) inc_el = 250;
			if (ace_thermal_xs_data[zaid_thermal].isCoherentElasticScattering()) coh_el = 250;
		}
	}
}
void FMDataContainer::dumpOutputListData()
{
	if (edit_option.find(eEditOptionSkipPrintout) != edit_option.end()) return;

	map<string, string>::iterator it;

	for (it = output_list_data.begin(); it != output_list_data.end(); it++)
	{
		ofstream of;
		of.open(it->first);
		of << it->second;
		of.close();
	}
}
void FMDataContainer::setOutputCrossSectionMT(string zaid, vector<int>& xs1d_infdil, vector<int>& xs1d_shield, vector<int>& xs2d_infdil, vector<int>& xs2d_shield, map<int, int>& xs2d_plorder, string opt)
{
	//set 1d cross section for base (infinite dilusion) case
	xs1d_infdil.clear();
	xs1d_infdil.push_back(eMTNWT0);
	xs1d_infdil.push_back(eMTNWT1);
	xs1d_infdil.push_back(eMTTotal);
	xs1d_infdil.push_back(eMTTotalCurrentWeight);
	map<int, vector<vector<REAL> > >::iterator it1d;
	for (it1d = xs_mg_1d_vector[zaid].begin(); it1d != xs_mg_1d_vector[zaid].end(); it1d++)
	{
		if (it1d->first > eMT117 && it1d->first < 201) continue;
		if (it1d->first > 207 && it1d->first < eMTHeating) continue;
		if (it1d->first > eMTHeating && it1d->first < eMTKerma) continue;
		if (it1d->first > eMTDamage && it1d->first < 600) continue;
		if (it1d->first > 891) continue;
		if (it1d->first == eMTTotal) continue;
		if (it1d->first == eMTTotalCurrentWeight) continue;
		if (isZero1dXS(it1d->second[0])) continue;
		xs1d_infdil.push_back(it1d->first);
	}

	//add nutot(452), nud(455), nup(456), chid(eMTChiDelayed), average mu (251), slowing down xi (252), slowing down gamma (253)
	//ave. leth. (258), ave. 1/v (259), flux (nwt0), current (nwt1)
	xs1d_infdil.push_back(eMTAverageLethargy);
	xs1d_infdil.push_back(eMTAverageInverseVerocity);
	xs1d_infdil.push_back(eMTAverageMubar);
	xs1d_infdil.push_back(eMTSlowingDownXi);
	xs1d_infdil.push_back(eMTSlowingDownGamma);
	if (nuchi_mg_1d_vector[zaid].find(eMTNuTotal) != nuchi_mg_1d_vector[zaid].end())
		xs1d_infdil.push_back(eMTNuTotal);
	if (nuchi_mg_1d_vector[zaid].find(eMTNuDelayed) != nuchi_mg_1d_vector[zaid].end())
		xs1d_infdil.push_back(eMTNuDelayed);
	if (nuchi_mg_1d_vector[zaid].find(eMTChiDelayed) != nuchi_mg_1d_vector[zaid].end())
	{
		DOUBLE sum = 0.0;
		for (int ig = 0; ig < (int)nuchi_mg_1d_vector[zaid][eMTChiDelayed].size(); ig++)
			sum += nuchi_mg_1d_vector[zaid][eMTChiDelayed][ig];
		if (sum != 0.0)
			xs1d_infdil.push_back(eMTChiDelayed);
	}
	if (nuchi_mg_1d_vector[zaid].find(eMTNuPrompt) != nuchi_mg_1d_vector[zaid].end())
		xs1d_infdil.push_back(eMTNuPrompt);

	//set 2d cross section for infinite dilusion case
	xs2d_infdil.clear();
	map<int, vector<FMCompressedMatrix> >::iterator it2d;
	for (it2d = xs_mg_2d_matrix[zaid].begin(); it2d != xs_mg_2d_matrix[zaid].end(); it2d++)
	{
		if (it2d->first > eMT117 && it2d->first < 875) continue;
		if (it2d->first > 891) continue;
		if (it2d->first == eMTInelasticScatteringTotal) continue;
		if (it2d->second[0].isZero2dXS()) continue;
		xs2d_infdil.push_back(it2d->first);
	}

	//set and output shielded cases
	bool full_edit = false;
	bool simple_edit = false;
	if (compareString(opt, "matxs") == true)
	{
		if (edit_option.find(eEditOptionFullMATXS) != edit_option.end()) full_edit = true;
		if (edit_option.find(eEditOptionSimpleMATXS) != edit_option.end()) simple_edit = true;
	}
	if (compareString(opt, "gendf") == true)
	{
		if (edit_option.find(eEditOptionFullGENDF) != edit_option.end()) full_edit = true;
		if (edit_option.find(eEditOptionSimpleGENDF) != edit_option.end()) simple_edit = true;
	}

	//set maximum pl order for fission matrix (mt=18, 19, 20, 21, 38)
	xs2d_plorder.clear();
	if (full_edit != true)
	{
		xs2d_plorder.insert(make_pair(eMTFission, 0));
		xs2d_plorder.insert(make_pair(eMTFirstChanceFission, 0));
		xs2d_plorder.insert(make_pair(eMTSecondChanceFission, 0));
		xs2d_plorder.insert(make_pair(eMTThirdChanceFission, 0));
		xs2d_plorder.insert(make_pair(eMTFourthChanceFission, 0));
	}

	xs1d_shield.clear();
	xs2d_shield.clear();
	if (background_xs_set.size() > 1)
	{
		xs1d_shield.push_back(eMTNWT0);
		xs1d_shield.push_back(eMTNWT1);
		xs1d_shield.push_back(eMTTotal);
		xs1d_shield.push_back(eMTTotalCurrentWeight);
		if (full_edit == false)
		{
			if (xs_mg_1d_vector[zaid].find(eMTElasticScattering) != xs_mg_1d_vector[zaid].end()) xs1d_shield.push_back(eMTElasticScattering);
			if (xs_mg_1d_vector[zaid].find(eMTFission) != xs_mg_1d_vector[zaid].end()) xs1d_shield.push_back(eMTFission);
			if (xs_mg_1d_vector[zaid].find(eMTFirstChanceFission) != xs_mg_1d_vector[zaid].end()) xs1d_shield.push_back(eMTFirstChanceFission);
			if (xs_mg_1d_vector[zaid].find(eMTSecondChanceFission) != xs_mg_1d_vector[zaid].end()) xs1d_shield.push_back(eMTSecondChanceFission);
			if (xs_mg_1d_vector[zaid].find(eMTThirdChanceFission) != xs_mg_1d_vector[zaid].end()) xs1d_shield.push_back(eMTThirdChanceFission);
			if (xs_mg_1d_vector[zaid].find(eMTFourthChanceFission) != xs_mg_1d_vector[zaid].end()) xs1d_shield.push_back(eMTFourthChanceFission);
			if (xs_mg_1d_vector[zaid].find(eMTInelasticScatteringBegin) != xs_mg_1d_vector[zaid].end()) xs1d_shield.push_back(eMTInelasticScatteringBegin);
			if (xs_mg_1d_vector[zaid].find(eMTNGamma) != xs_mg_1d_vector[zaid].end()) xs1d_shield.push_back(eMTNGamma);
		}
		else
		{
			for (it1d = xs_mg_1d_vector[zaid].begin(); it1d != xs_mg_1d_vector[zaid].end(); it1d++)
			{
				if (it1d->first > eMT117 && it1d->first < 600) continue;
				if (it1d->first > 891) continue;
				if (it1d->first == eMTTotal) continue;
				if (it1d->first == eMTTotalCurrentWeight) continue;
				if (isZero1dXS(it1d->second[0])) continue;
				xs1d_shield.push_back(it1d->first);
			}

			//add nutot(452), nud(455), nup(456), chid(eMTChiDelayed), average mu (251)
			if (nuchi_mg_1d_vector[zaid].find(eMTNuTotal) != nuchi_mg_1d_vector[zaid].end())
				xs1d_shield.push_back(eMTNuTotal);
			if (nuchi_mg_1d_vector[zaid].find(eMTNuDelayed) != nuchi_mg_1d_vector[zaid].end())
				xs1d_shield.push_back(eMTNuDelayed);
			if (nuchi_mg_1d_vector[zaid].find(eMTChiDelayed) != nuchi_mg_1d_vector[zaid].end())
				xs1d_shield.push_back(eMTChiDelayed);
			if (nuchi_mg_1d_vector[zaid].find(eMTNuPrompt) != nuchi_mg_1d_vector[zaid].end())
				xs1d_shield.push_back(eMTNuPrompt);
		}

		if (full_edit == true)
		{
			for (it2d = xs_mg_2d_matrix[zaid].begin(); it2d != xs_mg_2d_matrix[zaid].end(); it2d++)
			{
				if (it2d->first > eMT117 && it2d->first < 875) continue;
				if (it2d->first > 891) continue;
				if (it2d->first == eMTInelasticScatteringTotal) continue;
				if (it2d->second[0].isZero2dXS()) continue;
				xs2d_shield.push_back(it2d->first);
			}
		}
		else if (full_edit == false && simple_edit == true)
		{
			if (xs_mg_2d_matrix[zaid].find(eMTElasticScattering) != xs_mg_2d_matrix[zaid].end()) xs2d_shield.push_back(eMTElasticScattering);
		}
		else
		{
			if (xs_mg_2d_matrix[zaid].find(eMTElasticScattering) != xs_mg_2d_matrix[zaid].end()) xs2d_shield.push_back(eMTElasticScattering);
			if (xs_mg_2d_matrix[zaid].find(eMTFission) != xs_mg_2d_matrix[zaid].end()) xs2d_shield.push_back(eMTFission);
		}

	}

}
void FMDataContainer::editOutputListData()
{
	print1stHeader(" Dump calculation results ");

	if (edit_option.size() == 0)
	{
		cout << " no editing is specified in input data " << endl;
		return;
	}

	//ultra-fine group spectrum calculations
	if (edit_option.find(eEditOptionUFG) != edit_option.end())
	{
		cout << "   Dumping UFG related data" << endl;
		dumpUFFlux();
		dumpUFSlowingdownSource();
		dumpUFTotalSource();
		dumpUFSigTotal();
	}

	//multi-group flux
	if (edit_option.find(eEditOptionMGFlux) != edit_option.end())
	{
		cout << "   Dumping multi-group flux data" << endl;
		dumpMGFlux();
	}

	int num_nucl = uf_region_data.num_nucl;

	for (int in = 0; in < num_nucl; in++)
	{
		FMACECrossSectionProcessor& acexs = *uf_region_data.ace_xs_pointer[in];
		string zaid = acexs.getZaid();

		cout << "   Dumping data for nuclide " << setw(10) << zaid << endl;

		map<int, vector<vector<REAL> > >::iterator it1d;
		if (edit_option.find(eEditOption1DXS) != edit_option.end())
		{
			cout << "     1d cross sections"  << endl;
			for (it1d = xs_mg_1d_vector[zaid].begin(); it1d != xs_mg_1d_vector[zaid].end(); it1d++)
			{
				int mt = it1d->first;
				if (isMTIncluded(mt, edit_option[eEditOption1DXS]) == false) continue;
				dumpMGXS1d(zaid, mt);
			}

			if (isMTIncluded(2, edit_option[eEditOption1DXS]) == true || isMTIncluded(4, edit_option[eEditOption1DXS]) == true)
			{
				cout << "     Total scattering" << endl;
				dumpMGTotalScatteringXS(zaid);
			}
		}

		int num_bgxs = background_xs_set.size();
		map<int, vector<FMCompressedMatrix> >::iterator it2d;
		if (edit_option.find(eEditOption2DXS) != edit_option.end())
		{
			cout << "     2d cross sections" << endl;
			for (it2d = xs_mg_2d_matrix[zaid].begin(); it2d != xs_mg_2d_matrix[zaid].end(); it2d++)
			{
				int mt = it2d->first;
				if (isMTIncluded(mt, edit_option[eEditOption2DXS]) == false) continue;
				for (int ib = 0; ib < num_bgxs; ib++)
				{
					dumpMGXS2d(zaid, mt, ib);
				}
			}
		}

		if (edit_option.find(eEditOptionUFG1DXS) != edit_option.end())
		{
			cout << "     UFG 1d cross sections" << endl;
			for (it1d = xs_mg_1d_vector[zaid].begin(); it1d != xs_mg_1d_vector[zaid].end(); it1d++)
			{
				int mt = it1d->first;
				if (isMTIncluded(mt, edit_option[eEditOptionUFG1DXS]) == false) continue;
				dumpUFGXS1d(zaid, mt);
			}
		}

		if (edit_option.find(eEditOptionUFGInputGrid1DXS) != edit_option.end())
		{
			cout << "     UFG 1d cross sections using input UFG energy grid" << endl;
			for (it1d = xs_mg_1d_vector[zaid].begin(); it1d != xs_mg_1d_vector[zaid].end(); it1d++)
			{
				int mt = it1d->first;
				if (isMTIncluded(mt, edit_option[eEditOptionUFGInputGrid1DXS]) == false) continue;
				dumpUFGXS1dInputUFGGrid(zaid, mt);
			}
		}

		if (edit_option.find(eEditOptionRUC) != edit_option.end())
		{
			cout << "     1d elastic scattering cross sections (used for resonance upscattering correction"<< endl;
			dumpRUCXS1d(zaid);
		}

		if (edit_option.find(eEditOptionNuChi) != edit_option.end())
		{
			cout << "     Nu and fission spectrum" << endl;
			dumpMGNuChi(zaid);
		}

		if (edit_option.find(eEditOptionKRAMXSMicro) != edit_option.end() ||
			edit_option.find(eEditOptionKRAMXSMacro) != edit_option.end())
		{
			if (edit_option.find(eEditOptionKRAMXSMicro) != edit_option.end())
				cout << "     Microscopic cross section in kram format" << endl;
			for (int ib = 0; ib < num_bgxs; ib++)
			{
				dumpEffectiveMicroXSinKramFormat(zaid, ib);
			}
		}

	}

	if (edit_option.find(eEditOptionKRAMXSMacro) != edit_option.end())
	{
		cout << "   Dumping macroscopic cross section in kram format "  << endl;
		int num_bgxs = background_xs_set.size();
		for (int ib = 0; ib < num_bgxs; ib++)
			dumpEffectiveMacroXSinKramFormat(ib);
	}
}
void FMDataContainer::dumpEffectiveMicroXSinKramFormat(string zaid, int ib)
{
	vector<vector<REAL> > micxs1d;
	micxs1d.resize(5);
	for (int i = 0; i < 5; i++)
	{
		micxs1d[i].resize(mg_max_num_energy);
		for (int ig = 0; ig < mg_max_num_energy; ig++)
			micxs1d[i][ig] = 0.0;
	}

	//check thermal cross section except for free gas (mt=221) exist or not
	vector<int> sabmt;
	sabmt.clear();
	map<int, vector<vector<REAL> > >::iterator it1d;
	for (it1d = xs_mg_1d_vector[zaid].begin(); it1d != xs_mg_1d_vector[zaid].end(); it1d++)
	{
		if (isThermalMT(it1d->first) && it1d->first != eMTThermalFreeGas)
			sabmt.push_back(it1d->first);
	}
	
	//total cross section
	int mt = 1;
	if (kram_current_weight_total) mt = -1;

	for (int ig = 0; ig < mg_max_num_energy; ig++)
	{
		REAL st = getXSMG1DVectorUF(zaid, mt, ib, ig);
		if (sabmt.size() != 0)
		{
			REAL sab_sum = 0.0;
			int inf_dil_ib = 0;

			for (int i = 0; i < static_cast<int>(sabmt.size()); i++)
			{
				sab_sum += getXSMG2DMatrixSum(zaid, sabmt[i], inf_dil_ib, ig);
			}
			if (sab_sum != 0.0)
				st += sab_sum - getXSMG2DMatrixSum(zaid, eMTElasticScattering, inf_dil_ib, ig);
		}
		micxs1d[0][ig] = st;
	}

	//absorption cross section
	vector<int> mt_list_1d_xs;
	getMTinXSMG1DVector(zaid, mt_list_1d_xs);

	for (int ig = 0; ig < mg_max_num_energy; ig++)
	{
		for (int ii = 0; ii < static_cast<int>(mt_list_1d_xs.size()); ii++)
		{
			mt = mt_list_1d_xs[ii];
			REAL val = getNumNeutronAbsorption(zaid, mt, ig);
			if (val == 0.0) continue;
			micxs1d[1][ig] += getXSMG1DVectorUF(zaid, mt, ib, ig) * val;
		}
	}

	//fission & production cross section
	for (int ig = 0; ig < mg_max_num_energy; ig++)
	{
		mt = eMTFission;
		micxs1d[2][ig] = getXSMG1DVectorUF(zaid, mt, ib, ig) * getNuChiMG1DVector(zaid, eMTNuTotal, ig);
		micxs1d[3][ig] = getXSMG1DVectorUF(zaid, mt, ib, ig);
	}

	//fission spectrum
	for (int ig = 0; ig < mg_max_num_energy; ig++)
		micxs1d[4][ig] = getNuChiMG1DVector(zaid, eMTChiTotal, ig);

	vector<vector<vector<REAL> > > micxs2d;
	micxs2d.resize(mg_max_num_energy);
	for (int ig = 0; ig < mg_max_num_energy; ig++)
	{
		micxs2d[ig].resize(mg_max_num_energy);
		for (int iig = 0; iig < mg_max_num_energy; iig++)
		{
			micxs2d[ig][iig].resize(max_pl+1);
			for (int il = 0; il <= max_pl; il++)
				micxs2d[ig][iig][il] = 0.0;
		}
	}

	//scattering matrix
	vector<int> mt_list_2d_xs;
	getMTinXSMG2DMatrix(zaid, mt_list_2d_xs);

	for (int ii = 0; ii < static_cast<int>(mt_list_2d_xs.size()); ii++)
	{
		mt = mt_list_2d_xs[ii];

		//skip mt=4 since it is duplicate
		if (mt == eMTInelasticScatteringTotal) continue;

		vector<FMCompressedMatrix>& matrix = xs_mg_2d_matrix[zaid][mt];
		vector<FMCompressedMatrix>& matrix_elas = xs_mg_2d_matrix[zaid][eMTElasticScattering];

		for (int ig = 0; ig < mg_max_num_energy; ig++)
		{
			REAL val = getNumNeutronScattering(zaid, mt, ig);
			if (val == 0.0) continue;

			REAL val3 = 0.0;
			for (int iig = 0; iig < mg_max_num_energy; iig++)
				val3 += getXSMG2DMatrix(matrix, ib, ig, iig, 0);

			vector<vector<REAL> >& micxs2d_wk = micxs2d[ig];
			for (int iig = 0; iig < mg_max_num_energy; iig++)
			{
				for (int il = 0; il <= max_pl; il++)
				{
					REAL val2 = getXSMG2DMatrix(matrix, ib, ig, iig, il);
					REAL val4 = micxs2d_wk[iig][il];
					if (isThermalIncoherentInelastic(mt) && val3 != 0.0)
					{
						val4 += (val2 - getXSMG2DMatrix(matrix_elas, 0, ig, iig, il));
					}
					else
						val4 += val2;

					//to avoid negative P0 scattering cross section
					if (il == 0 && val4 < 0.0)
					{
						val4 = micxs2d_wk[iig][il];
						val4 *= val2 / getXSMG2DMatrix(matrix_elas, 0, ig, iig, il);
					}
					micxs2d_wk[iig][il] = val4;

				}
			}
		}
	}

	//store data for later processing
	string idname = zaid + my_to_string(ib);
	kram_micxs1d.insert(make_pair(idname, micxs1d));
	FMCompressedMatrix fmc;
	fmc.set(micxs2d);
	kram_micxs2d.insert(make_pair(idname, fmc));

	
	if (edit_option.find(eEditOptionKRAMXSMicro) == edit_option.end()) return;

	//output ... kram format
	stringstream of;
	string file_name = "FMKRAMXS_" + file_add_name_ + zaid + "_bg" + my_to_string(ib) + ".txt";

	of << " XSN 1" << endl;
	of << scientific << setprecision(6);
	//p0 scattering
	for (int iig = 0; iig < mg_max_num_energy; iig++)
	{
		for (int ig = 0; ig < mg_max_num_energy; ig++)
			of << setw(15) << micxs2d[ig][iig][0];
		of << endl;
	}
	//production
	for (int ig = 0; ig < mg_max_num_energy; ig++)
		of << setw(15) << micxs1d[2][ig];
	of << endl;
	//absorption
	for (int ig = 0; ig < mg_max_num_energy; ig++)
		of << setw(15) << micxs1d[1][ig];
	of << endl;
	//total
	for (int ig = 0; ig < mg_max_num_energy; ig++)
		of << setw(15) << micxs1d[0][ig];
	of << endl;
	//fission
	for (int ig = 0; ig < mg_max_num_energy; ig++)
		of << setw(15) << micxs1d[3][ig];
	of << endl;

	of << " FSP 1" << endl;
	for (int ig = 0; ig < mg_max_num_energy; ig++)
		of << setw(15) << micxs1d[4][ig];
	of << endl;

	of << " ASC 1" << endl;
	of << setw(10) << max_pl << endl;
	for (int il = 1; il <= max_pl; il++)
	{
		for (int iig = 0; iig < mg_max_num_energy; iig++)
		{
			for (int ig = 0; ig < mg_max_num_energy; ig++)
				of << setw(15) << micxs2d[ig][iig][il];
			of << endl;
		}
	}

	output_list_data.insert(make_pair(file_name, of.str()));

}
void FMDataContainer::dumpEffectiveMacroXSinKramFormat(int ib)
{
	vector<vector<REAL> > macxs1d;
	macxs1d.resize(5);
	for (int i = 0; i < 5; i++)
	{
		macxs1d[i].resize(mg_max_num_energy);
		for (int ig = 0; ig < mg_max_num_energy; ig++)
			macxs1d[i][ig] = 0.0;
	}

	vector<vector<vector<REAL> > > macxs2d;
	macxs2d.resize(mg_max_num_energy);
	for (int ig = 0; ig < mg_max_num_energy; ig++)
	{
		macxs2d[ig].resize(mg_max_num_energy);
		for (int iig = 0; iig < mg_max_num_energy; iig++)
		{
			macxs2d[ig][iig].resize(max_pl + 1);
			for (int il = 0; il <= max_pl; il++)
				macxs2d[ig][iig][il] = 0.0;
		}
	}

	int num_nucl = uf_region_data.num_nucl;
	vector<REAL> weight;
	weight.resize(num_nucl);

	//calculate fission rate using default spectrum
	for (int in = 0; in < num_nucl; in++)
	{
		string idname = uf_region_data.nuc_name[in] + my_to_string(ib);
		weight[in] = 0.0;
		for (int ig = 0; ig < mg_max_num_energy; ig++)
			weight[in] += kram_micxs1d[idname][2][ig] * uf_region_data.nuc_dens[in] * flux_mg_1d_vector[1][ib][ig];
	}

	for (int in = 0; in < num_nucl; in++)
	{
		string idname = uf_region_data.nuc_name[in] + my_to_string(ib);
		for (int i = 0; i < 5; i++)
		{
			for (int ig = 0; ig < mg_max_num_energy; ig++)
			{
				if (i != 4)
					macxs1d[i][ig] += kram_micxs1d[idname][i][ig] * uf_region_data.nuc_dens[in];
				else
					macxs1d[i][ig] += kram_micxs1d[idname][i][ig] * weight[in];
			}
		}
	}

	//normalize fission spectrum
	REAL sum = 0.0;
	for (int ig = 0; ig < mg_max_num_energy; ig++)
		sum += macxs1d[4][ig];
	if (sum != 0.0)
	{
		for (int ig = 0; ig < mg_max_num_energy; ig++)
			macxs1d[4][ig] /= sum;
	}

	for (int in = 0; in < num_nucl; in++)
	{
		string idname = uf_region_data.nuc_name[in] + my_to_string(ib);
		for (int ig = 0; ig < mg_max_num_energy; ig++)
		{
			for (int iig = 0; iig < mg_max_num_energy; iig++)
			{
				for (int il = 0; il <= max_pl; il++)
					macxs2d[ig][iig][il] += kram_micxs2d[idname].get(ig,iig,il) * uf_region_data.nuc_dens[in];
			}
		}
	}

	stringstream of;
	string file_name = "FMKRAMXS_" + file_add_name_ + "MACRO" + "_bg" + my_to_string(ib) + ".txt";

	of << " XSN 1" << endl;
	of << scientific << setprecision(6);
	//p0 scattering
	for (int iig = 0; iig < mg_max_num_energy; iig++)
	{
		for (int ig = 0; ig < mg_max_num_energy; ig++)
			of << setw(15) << macxs2d[ig][iig][0];
		of << endl;
	}
	//production
	for (int ig = 0; ig < mg_max_num_energy; ig++)
		of << setw(15) << macxs1d[2][ig];
	of << endl;
	//absorption
	for (int ig = 0; ig < mg_max_num_energy; ig++)
		of << setw(15) << macxs1d[1][ig];
	of << endl;
	//total
	for (int ig = 0; ig < mg_max_num_energy; ig++)
		of << setw(15) << macxs1d[0][ig];
	of << endl;
	//fission
	for (int ig = 0; ig < mg_max_num_energy; ig++)
		of << setw(15) << macxs1d[3][ig];
	of << endl;

	of << " FSP 1" << endl;
	for (int ig = 0; ig < mg_max_num_energy; ig++)
		of << setw(15) << macxs1d[4][ig];
	of << endl;

	of << " ASC 1" << endl;
	of << setw(10) << max_pl << endl;
	for (int il = 1; il <= max_pl; il++)
	{
		for (int iig = 0; iig < mg_max_num_energy; iig++)
		{
			for (int ig = 0; ig < mg_max_num_energy; ig++)
				of << setw(15) << macxs2d[ig][iig][il];
			of << endl;
		}
	}

	output_list_data.insert(make_pair(file_name, of.str()));
}
void FMDataContainer::dumpMGFlux( )
{
	int num_bgxs = background_xs_set.size();

	map<int, vector<vector<REAL> > >::iterator it;

	for (it = flux_mg_1d_vector.begin(); it != flux_mg_1d_vector.end(); it++)
	{
		int mt = it->first;

		string file_name;
		if (mt == -1)
			file_name = "FMMGCurrent" + _file_add_name + ".txt";
		else if (mt == 1)
			file_name = "FMMGFlux" + _file_add_name + ".txt";
		else
		{
			cout << " error in FMDataContainer::dumpMGFlux(int mt) " << endl;
			exit(0);
		}

		stringstream of;
		of << "   NG    E-upper[eV]    E-lower[eV]   E-middle[eV]    Values" << endl;
		of << "                                   <Background XS>";
		for (int ib = 0; ib < num_bgxs; ib++)
			of << setw(15) << setprecision(5) << scientific << background_xs_set[ib];
		of << endl;

		for (int mg = 0; mg < mg_max_num_energy; mg++)
		{
			of << setw(5) << mg;
			of << setw(15) << setprecision(5) << scientific << mg_energy_boundary[mg];
			of << setw(15) << setprecision(5) << scientific << mg_energy_boundary[mg + 1];
			of << setw(15) << setprecision(5) << scientific << sqrt(mg_energy_boundary[mg] * mg_energy_boundary[mg + 1]);
			for (int ib = 0; ib < num_bgxs; ib++)
				of << setw(15) << setprecision(5) << scientific << it->second[ib][mg];
			of << endl;
		}
		output_list_data.insert(make_pair(file_name, of.str()));
	}
}
void FMDataContainer::dumpMGXS1d(string zaid, int mt)
{
	if (xs_mg_1d_vector[zaid].find(mt) == xs_mg_1d_vector[zaid].end()) return;

	int num_bgxs = background_xs_set.size();
	FMACECrossSectionProcessor& acexs = ace_xs_data[zaid];

	string file_name = "FMMicXS1d_";
	file_name += file_add_name_;
	file_name += zaid;
	file_name += "_MT";
	file_name += my_to_string(mt);
	file_name += ".txt";
	
	stringstream of;
	of << "   NG    E-upper[eV]    E-lower[eV]   E-middle[eV]    Values" << endl;
	of << "                                   <Background XS>";
	for (int ib = 0; ib < num_bgxs; ib++)
		of << setw(15) << setprecision(6) << scientific << background_xs_set[ib];
	of << endl;
	of << "                                     <Temperature>";
	for (int ib = 0; ib < num_bgxs; ib++)
		of << setw(15) << setprecision(6) << scientific << acexs.getKelvin();
	of << endl;

	for (int mg = 0; mg < mg_max_num_energy; mg++)
	{
		of << setw(5) << mg;
		of << setw(15) << setprecision(6) << scientific << mg_energy_boundary[mg];
		of << setw(15) << setprecision(6) << scientific << mg_energy_boundary[mg + 1];
		of << setw(15) << setprecision(6) << scientific << sqrt(mg_energy_boundary[mg] * mg_energy_boundary[mg + 1]);
		for (int ib = 0; ib < num_bgxs; ib++)
			of << setw(15) << setprecision(6) << scientific << xs_mg_1d_vector[zaid][mt][ib][mg];
		of << endl;
	}

	output_list_data.insert(make_pair(file_name, of.str()));
}
void FMDataContainer::dumpUFGXS1d(string zaid, int mt)
{
	FMACECrossSectionProcessor& acexs = ace_xs_data[zaid];
	if (acexs.isMT(mt) == false) return;

	string file_name = "FMUFGMicXS1d_";
	file_name += file_add_name_;
	file_name += zaid;
	file_name += "_MT";
	file_name += my_to_string(mt);
	file_name += ".txt";

	stringstream of;
	of << "Background cross section:";
	for (int i = 0; i < static_cast<int>(background_xs_set.size()); i++)
		of << setw(15) << setprecision(5) << scientific << background_xs_set[i];
	of << endl;
	of << "Temperature             :";
	for (int i = 0; i < static_cast<int>(background_xs_set.size()); i++)
		of << setw(15) << setprecision(5) << scientific << acexs.getKelvin();
	of << endl;
	of << "     IE   NG  E-middle[eV]  Values[barn]" << endl;

	for (int ie = 0; ie < uf_max_num_energy; ie++)
	{
		int mg = uf_to_mg_group[ie];
		REAL ene = uf_energy_midpoint[ie];
		//REAL bgxs = 1.0e+10;
		of << setw(7) << ie;
		of << setw(5) << mg;
		of << setw(14) << scientific << setprecision(6) << ene;
		for (int i = 0; i < static_cast<int>(background_xs_set.size()); i++)
			of << setw(15) << scientific << setprecision(6) << ace_xs_data[zaid].getXS(mt, ene, background_xs_set[i]);
		of << endl;
	}

	output_list_data.insert(make_pair(file_name, of.str()));
}
void FMDataContainer::dumpUFGXS1dInputUFGGrid(string zaid, int mt)
{
	FMACECrossSectionProcessor& acexs = ace_xs_data[zaid];
	if (acexs.isMT(mt) == false) return;

	string file_name = "FMUFGInputGridMicXS1d_";
	file_name += file_add_name_;
	file_name += zaid;
	file_name += "_MT";
	file_name += my_to_string(mt);
	file_name += ".txt";

	stringstream of;
	of << "Background cross section:";
	for (int i = 0; i < static_cast<int>(background_xs_set.size()); i++)
		of << setw(15) << setprecision(5) << scientific << background_xs_set[i];
	of << endl;
	of << "Temperature             :";
	for (int i = 0; i < static_cast<int>(background_xs_set.size()); i++)
		of << setw(15) << setprecision(5) << scientific << acexs.getKelvin();
	of << endl;
	of << "     IE   NG  E-middle[eV]  Values[barn]" << endl;

	for (int ie = 0; ie < uf_max_num_energy_input; ie++)
	{
		int mg = uf_to_mg_group_input[ie];
		REAL ene = uf_energy_midpoint_input[ie];
		//REAL bgxs = 1.0e+10;
		of << setw(7) << ie;
		of << setw(5) << mg;
		of << setw(14) << scientific << setprecision(6) << ene;
		for (int i = 0; i < static_cast<int>(background_xs_set.size()); i++)
			of << setw(15) << scientific << setprecision(6) << ace_xs_data[zaid].getXS(mt, ene, background_xs_set[i]);
		of << endl;
	}

	output_list_data.insert(make_pair(file_name, of.str()));
}
void FMDataContainer::dumpRUCXS1d(string zaid)
{
	int mt = eMTElasticScattering;

	FMACECrossSectionProcessor& acexs = ace_xs_data[zaid];
	if (acexs.isMT(mt) == false) return;
	if (acexs.getKelvin() > 0.11)
	{
		print2ndHeader(" Cross section edit for resonance upscattering is skipped since temperature is higher than 0.1 K");
		return;
	}

	string file_name = "FMRUCMicXS1d_";
	file_name += file_add_name_;
	file_name += zaid;
	file_name += "_MT";
	file_name += my_to_string(mt);
	file_name += ".txt";

	stringstream of;
	of << setw(15) << zaid;
	of << setw(15) << setprecision(5) << scientific << acexs.getKelvin();
	of << endl;

	for (int ie = uf_max_num_energy-1; ie >= 0; ie--)
	{
		REAL ene = uf_energy_midpoint[ie];
		of << setw(15) << scientific << setprecision(6) << ene;
		of << setw(15) << scientific << setprecision(6) << ace_xs_data[zaid].getXS(mt, ene, background_xs_set[0]);
		of << endl;
		if (ene > RESO_UPSCAT_EMAX) break;
	}

	output_list_data.insert(make_pair(file_name, of.str()));
}
void FMDataContainer::dumpMGTotalScatteringXS(string zaid)
{
	int max_ng = mg_max_num_energy;
	FMACECrossSectionProcessor& acexs = ace_xs_data[zaid];

	int num_bgxs = background_xs_set.size();

	//elastic
	if (xs_mg_2d_matrix[zaid].find(eMTElasticScattering) != xs_mg_2d_matrix[zaid].end())
	{
		for (int il = 0; il <= max_pl; il++)
		{
			string file_name = "FMMicXS1d_";
			file_name += file_add_name_;
			file_name += zaid;
			file_name += "_MT2_PL";
			file_name += my_to_string(il);
			file_name += ".txt";

			stringstream of;
			of << "   NG    E-upper[eV]    E-lower[eV]   E-middle[eV]    Values" << endl;
			of << "                                   <Background XS>";
			for (int ib = 0; ib < num_bgxs; ib++)
				of << setw(15) << setprecision(6) << scientific << background_xs_set[ib];
			of << endl;
			of << "                                     <Temperature>";
			for (int ib = 0; ib < num_bgxs; ib++)
				of << setw(15) << setprecision(6) << scientific << acexs.getKelvin();
			of << endl;

			for (int mg = 0; mg < mg_max_num_energy; mg++)
			{
				of << setw(5) << mg;
				of << setw(15) << setprecision(6) << scientific << mg_energy_boundary[mg];
				of << setw(15) << setprecision(6) << scientific << mg_energy_boundary[mg + 1];
				of << setw(15) << setprecision(6) << scientific << sqrt(mg_energy_boundary[mg] * mg_energy_boundary[mg + 1]);
				for (int ib = 0; ib < num_bgxs; ib++)
				{
					REAL val = 0.0;
					for (int iig = 0; iig < max_ng; iig++)
						val += xs_mg_2d_matrix[zaid][eMTElasticScattering][ib].get(mg,iig,il);
					of << setw(15) << setprecision(6) << scientific << val;
				}
				of << endl;
			}
			output_list_data.insert(make_pair(file_name, of.str()));
		}
	}

	//total inelastic
	if (xs_mg_2d_matrix[zaid].find(eMTInelasticScatteringTotal) != xs_mg_2d_matrix[zaid].end())
	{
		for (int il = 0; il <= max_pl; il++)
		{
			string file_name = "FMMicXS1d_";
			file_name += file_add_name_;
			file_name += zaid;
			file_name += "_MT4_PL";
			file_name += my_to_string(il);
			file_name += ".txt";

			stringstream of;
			of.str("");
			of.clear();
			of << "   NG    E-upper[eV]    E-lower[eV]   E-middle[eV]    Values" << endl;
			of << "                                   <Background XS>";
			for (int ib = 0; ib < num_bgxs; ib++)
				of << setw(15) << setprecision(6) << scientific << background_xs_set[ib];
			of << endl;
			of << "                                     <Temperature>";
			for (int ib = 0; ib < num_bgxs; ib++)
				of << setw(15) << setprecision(6) << scientific << acexs.getKelvin();
			of << endl;

			for (int mg = 0; mg < mg_max_num_energy; mg++)
			{
				of << setw(5) << mg;
				of << setw(15) << setprecision(6) << scientific << mg_energy_boundary[mg];
				of << setw(15) << setprecision(6) << scientific << mg_energy_boundary[mg + 1];
				of << setw(15) << setprecision(6) << scientific << sqrt(mg_energy_boundary[mg] * mg_energy_boundary[mg + 1]);
				for (int ib = 0; ib < num_bgxs; ib++)
				{
					REAL val = 0.0;
					for (int iig = 0; iig < max_ng; iig++)
						val += xs_mg_2d_matrix[zaid][eMTInelasticScatteringTotal][ib].get(mg,iig,il);
					of << setw(15) << setprecision(6) << scientific << val;
				}
				of << endl;
			}
			output_list_data.insert(make_pair(file_name, of.str()));
		}
	}

	//independent inelastic
	for (int il = 0; il <= max_pl; il++)
	{
		string file_name = "FMMicXS1d_";
		file_name += file_add_name_;
		file_name += zaid;
		file_name += "_Inelastic_PL";
		file_name += my_to_string(il);
		file_name += ".txt";

		stringstream of;
		of.str("");
		of.clear();
		of << "   NG    E-upper[eV]    E-lower[eV]   E-middle[eV]    Values" << endl;
		of << "                                   <Background XS>";
		for (int ib = 0; ib < 1; ib++)
			of << setw(15) << setprecision(6) << scientific << background_xs_set[ib];
		of << endl;
		of << "                                     <Temperature>";
		for (int ib = 0; ib < 1; ib++)
			of << setw(15) << setprecision(6) << scientific << acexs.getKelvin();
		of << endl;
		of << "                                                  ";
		map<int, vector<vector<REAL> > >::iterator it1d;
		for (it1d = xs_mg_1d_vector[zaid].begin(); it1d != xs_mg_1d_vector[zaid].end(); it1d++)
		{
			if (isIndependentInelasticScattering(it1d->first) == false) continue;
			if (xs_mg_2d_matrix[zaid].find(it1d->first) == xs_mg_2d_matrix[zaid].end()) continue;
			of << setw(15) << it1d->first;
		}
		of << endl;

		for (int mg = 0; mg < mg_max_num_energy; mg++)
		{
			of << setw(5) << mg;
			of << setw(15) << setprecision(6) << scientific << mg_energy_boundary[mg];
			of << setw(15) << setprecision(6) << scientific << mg_energy_boundary[mg + 1];
			of << setw(15) << setprecision(6) << scientific << sqrt(mg_energy_boundary[mg] * mg_energy_boundary[mg + 1]);
			int ib = 0;
			for (it1d = xs_mg_1d_vector[zaid].begin(); it1d != xs_mg_1d_vector[zaid].end(); it1d++)
			{
				if (isIndependentInelasticScattering(it1d->first) == false) continue;
				if (xs_mg_2d_matrix[zaid].find(it1d->first) == xs_mg_2d_matrix[zaid].end()) continue;
				REAL val = 0.0;
				for (int iig = 0; iig < max_ng; iig++)
					val += xs_mg_2d_matrix[zaid][it1d->first][ib].get(mg,iig,il);
				of << setw(15) << setprecision(6) << scientific << val;
			}
			of << endl;
		}
		output_list_data.insert(make_pair(file_name, of.str()));
	}
}
void FMDataContainer::dumpMGXS2d(string zaid, int mt, int ib)
{
	int max_ng = mg_max_num_energy;
	FMACECrossSectionProcessor& acexs = ace_xs_data[zaid];

	if (xs_mg_2d_matrix[zaid].find(mt) == xs_mg_2d_matrix[zaid].end()) return;
	if (ib >= static_cast<int>(xs_mg_2d_matrix[zaid][mt].size())) return;

	string file_name = "FMMicXS2d_" + file_add_name_ + zaid + "_MT" + my_to_string(mt) + "_bg" + my_to_string(ib) + ".txt";
	stringstream of;
	of << scientific << setprecision(6);
	of << " Temperature   = " << setw(15) << acexs.getKelvin() << endl;
	of << " Background XS = " << setw(15) << background_xs_set[ib] << endl;
	of << endl;

	for (int il = 0; il <= max_pl; il++)
	{
		of << " PL = " << il << endl;
		for (int iig = 0; iig < max_ng; iig++)
		{
			of << setw(5) << iig;
			for (int ig = 0; ig < max_ng; ig++)
				of << setw(15) << setprecision(6) << scientific << xs_mg_2d_matrix[zaid][mt][ib].get(ig,iig,il);
			of << endl;
		}
		of << endl;
	}

	output_list_data.insert(make_pair(file_name, of.str()));

}
void FMDataContainer::dumpMGNuChi(string zaid)
{
	//check fissionable or not
	if (xs_mg_2d_matrix[zaid].find(eMTFission) == xs_mg_2d_matrix[zaid].end()) return;

	//set number of energy groups, order of anisotropic scattering
	int max_ng = mg_max_num_energy;

	//number of delayed neutron groups
	FMACECrossSectionProcessor& acexs = ace_xs_data[zaid];
	int num_dn_group = acexs.getNumDelayedNeutronGroups();

	string file_name = "FMNuChi_" + file_add_name_ + zaid + ".txt";
	stringstream of;
	REAL sumtot = nu_prompt_delayed_sum[zaid][0] + nu_prompt_delayed_sum[zaid][1];
	REAL sumdelayed = nu_prompt_delayed_sum[zaid][1];

	of << " delayed neutron fraction (sum of all delayed neutron groups)" << endl;
	of << setw(15) << setprecision(6) << scientific << sumdelayed / sumtot << endl;
	of << " delayed neutron ratio of each delayed neutron group(sum = 1.0)" << endl;
	for (int i = 0; i < num_dn_group; i++)
	{
		of << setw(15) << setprecision(6) << scientific << delayed_ratio[zaid][i];
	}
	of << endl;
	of << " delayed neutron decay constant of each delayed neutron group (1/s)" << endl;
	for (int i = 1; i <= num_dn_group; i++)
	{
		of << setw(15) << setprecision(6) << scientific << acexs.getDelayedNeutronDecayConstant(i);
	}
	of << endl << endl;

	of << "   NG    E-upper[eV]    E-lower[eV]   E-middle[eV]    nu-total       nu-prompt      nu_delayed     chi_total      chi_propmt     chi_delayed    ---------------------------chi_delayed_independent-----------------------------------" << endl;
	for (int ig = 0; ig < max_ng; ig++)
	{
		of << setw(5) << ig;
		of << setw(15) << setprecision(6) << scientific << mg_energy_boundary[ig];
		of << setw(15) << setprecision(6) << scientific << mg_energy_boundary[ig + 1];
		of << setw(15) << setprecision(6) << scientific << sqrt(mg_energy_boundary[ig] * mg_energy_boundary[ig + 1]);
		of << setw(15) << setprecision(6) << scientific << nuchi_mg_1d_vector[zaid][eMTNuTotal][ig];
		of << setw(15) << setprecision(6) << scientific << nuchi_mg_1d_vector[zaid][eMTNuPrompt][ig];
		of << setw(15) << setprecision(6) << scientific << nuchi_mg_1d_vector[zaid][eMTNuDelayed][ig];
		of << setw(15) << setprecision(6) << scientific << nuchi_mg_1d_vector[zaid][eMTChiTotal][ig];
		of << setw(15) << setprecision(6) << scientific << nuchi_mg_1d_vector[zaid][eMTChiPrompt][ig];
		of << setw(15) << setprecision(6) << scientific << nuchi_mg_1d_vector[zaid][eMTChiDelayed][ig];
		for (int i = 0; i < num_dn_group; i++)
		{
			of << setw(15) << setprecision(6) << scientific << chi_d_independent[zaid][i][ig];
		}
		of << endl;
	}
	of << endl;

	output_list_data.insert(make_pair(file_name, of.str()));
}
void FMDataContainer::dumpUFFlux()
{
	stringstream of;
	string name;
	name = "FMUFGFlux" + _file_add_name + ".txt";

	of << "Background cross section (barn)          :";
	for (int i = 0; i < static_cast<int>(background_xs_set.size()); i++)
		of << setw(15) << setprecision(5) << scientific << background_xs_set[i];
	of << endl;
	of << "Background cross section (1/cm)          :";
	for (int i = 0; i < static_cast<int>(background_xs_set.size()); i++)
		of << setw(15) << setprecision(5) << scientific << background_xs_set[i]*uf_region_data.nuc_dens_sum;
	of << endl;
	of << "No(UFG) (MG)     Energy[eV]    Delta-E[eV]    Flux" << endl;

	for (int i = 0; i < uf_max_num_energy; i++)
	{
		of << setw(7) << i;
		of << setw(5) << uf_to_mg_group[i];
		of << setw(15) << setprecision(5) << scientific << uf_energy_midpoint[i];
		of << setw(15) << setprecision(5) << scientific << uf_energy_delta[i];
		for (int j = 0; j < static_cast<int>(uf_flux.size()); j++)
		{
			of << setw(15) << setprecision(5) << scientific << uf_flux[j][i];
			//of << setw(15) << setprecision(5) << scientific << getUFSpectrum(i, j);
		}
		of << endl;
	}

	output_list_data.insert(make_pair(name, of.str()));

}
void FMDataContainer::dumpUFTotalSource( )
{
	stringstream of;
	string name;
	name = "FMUFGTotalSource" + _file_add_name + ".txt";

	of << "Background cross section (barn)          :";
	for (int i = 0; i < static_cast<int>(background_xs_set.size()); i++)
		of << setw(15) << setprecision(5) << scientific << background_xs_set[i];
	of << endl;
	of << "Background cross section (1/cm)          :";
	for (int i = 0; i < static_cast<int>(background_xs_set.size()); i++)
		of << setw(15) << setprecision(5) << scientific << background_xs_set[i] * uf_region_data.nuc_dens_sum;
	of << endl;
	of << "No(UFG) (MG)     Energy[eV]    Delta-E[eV]    Slowing down source + fission source" << endl;

	for (int i = 0; i < uf_max_num_energy; i++)
	{
		of << setw(7) << i;
		of << setw(5) << uf_to_mg_group[i];
		of << setw(15) << setprecision(5) << scientific << uf_energy_midpoint[i];
		of << setw(15) << setprecision(5) << scientific << uf_energy_delta[i];
		for (int j = 0; j < static_cast<int>(uf_flux.size()); j++)
			of << setw(15) << setprecision(5) << scientific << uf_source[j][i];
		of << endl;
	}

	output_list_data.insert(make_pair(name, of.str()));

}
void FMDataContainer::dumpUFSlowingdownSource()
{
	stringstream of;
	string name;
	name = "FMUFGSlowingdownSource" + _file_add_name + ".txt";

	of << "Background cross section (barn)          :";
	for (int i = 0; i < static_cast<int>(background_xs_set.size()); i++)
		of << setw(15) << setprecision(5) << scientific << background_xs_set[i];
	of << endl;
	of << "Background cross section (1/cm)          :";
	for (int i = 0; i < static_cast<int>(background_xs_set.size()); i++)
		of << setw(15) << setprecision(5) << scientific << background_xs_set[i] * uf_region_data.nuc_dens_sum;
	of << endl;
	of << "No(UFG) (MG)     Energy[eV]    Delta-E[eV]    Slowing down source" << endl;

	for (int i = 0; i < uf_max_num_energy; i++)
	{
		of << setw(7) << i;
		of << setw(5) << uf_to_mg_group[i];
		of << setw(15) << setprecision(5) << scientific << uf_energy_midpoint[i];
		of << setw(15) << setprecision(5) << scientific << uf_energy_delta[i];
		for (int j = 0; j < static_cast<int>(uf_flux.size()); j++)
			of << setw(15) << setprecision(5) << scientific << uf_sld_source[j][i];
		of << endl;
	}

	output_list_data.insert(make_pair(name, of.str()));
}
void FMDataContainer::dumpUFSigTotal( )
{
	stringstream of;
	string name;
	name = "FMUFGSigTotal" + _file_add_name + ".txt";

	of << "Background cross section (barn)          :";
	for (int i = 0; i < static_cast<int>(background_xs_set.size()); i++)
		of << setw(15) << setprecision(5) << scientific << background_xs_set[i];
	of << endl;
	of << "Background cross section (1/cm)          :";
	for (int i = 0; i < static_cast<int>(background_xs_set.size()); i++)
		of << setw(15) << setprecision(5) << scientific << background_xs_set[i] * uf_region_data.nuc_dens_sum;
	of << endl;
	of << "No(UFG) (MG)     Energy[eV]    Delta-E[eV]    Macro sigma-total[1/cm]" << endl;

	for (int i = 0; i < uf_max_num_energy; i++)
	{
		of << setw(7) << i;
		of << setw(5) << uf_to_mg_group[i];
		of << setw(15) << setprecision(5) << scientific << uf_energy_midpoint[i];
		of << setw(15) << setprecision(5) << scientific << uf_energy_delta[i];
		for (int j = 0; j < static_cast<int>(background_xs_set.size()); j++)
			of << setw(15) << setprecision(5) << scientific << uf_sig_total[j][i];
		of << endl;
	}

	output_list_data.insert(make_pair(name, of.str()));

}
void  FMDataContainer::checkResults( )
{

	map<string, map<int, vector<FMCompressedMatrix> > >::iterator itz;
	map<int, vector<FMCompressedMatrix> >::iterator itm;
	for (itz = xs_mg_2d_matrix.begin(); itz != xs_mg_2d_matrix.end(); itz++)
	{
		string zaid = itz->first;
		for (itm = itz->second.begin(); itm != itz->second.end(); itm++)
		{
			for (int ib = 0; ib < static_cast<int>(itm->second.size()); ib++)
			{
				int ng = itm->second[ib].getMaxNG();
				int pl = itm->second[ib].getMaxPl();
				REAL* val = NULL;
				bool thereisnan = false;
				for (int k = 0; k < ng; k++)
					for (int j = 0; j < ng; j++)
					{
						for (int i = 0; i <= pl; i++)
						{
							val = itm->second[ib].getPointer(k, j, i);
							if (val != NULL)
							{
								if (std::isnan(*val) && thereisnan == false)
								{
									cout << " element(s) of energy transfer matrix is nan " << endl;
									cout << " zaid " << itz->first << " mt " << itm->first << endl;
									cout << " from " << k << " to " << j << " pl " << i << " ib " << ib << endl;
									thereisnan = true;
									break;
								}
								checkFloatMinMax(*val);
							}
						}
						if (isFissionMT(itm->first)) continue;
						val = itm->second[ib].getPointer(k, j, 0);
						if (val != NULL)
						{
							bool cut = cutSmallValueToTotal(*val, xs_mg_1d_vector[zaid][eMTTotal][0][k]);
							if (cut)
							{
								for (int i = 1; i <= pl; i++)
								{
									REAL* val2 = itm->second[ib].getPointer(k, j, i);
									if (val2 != NULL) *val2 = 0.0;
								}
							}
							else
							{
								for (int i = 1; i <= pl; i++)
								{
									REAL* val2 = itm->second[ib].getPointer(k, j, i);
									if (val2 != NULL) cutSmallValueToTotal(*val2, *val, XS_SMALL_RATIO_PL);
								}
							}
						}
					}
			}
		}
	}

	map<string, map<int, vector<vector<REAL> > > >::iterator itz1;
	map<int, vector<vector<REAL> > >::iterator itm1;
	for (itz1 = xs_mg_1d_vector.begin(); itz1 != xs_mg_1d_vector.end(); itz1++)
	{
		string zaid = itz1->first;
		for (itm1 = itz1->second.begin(); itm1 != itz1->second.end(); itm1++)
		{
			bool cut_small = false;
			vector<vector<REAL> >& vec = itm1->second;
			for (int j = 0; j < static_cast<int>(vec.size()); j++)
				for (int i = 0; i < static_cast<int>(vec[j].size()); i++)
				{
					if (std::isnan(vec[j][i]))
					{
						cout << " element(s) of xs mg vector is nan " << endl;
						cout << " zaid " << itz1->first << " mt " << itm1->first << endl;
						//thereisnan = true;
						break;
					}
					checkFloatMinMax(vec[j][i]);
					bool wk = cutSmallValueToTotal(vec[j][i], xs_mg_1d_vector[zaid][eMTTotal][0][i]);
					if (wk) cut_small = true;
				}
			if (cut_small)
			{
				cout << "   zaid= ";
				cout << setw(12) << zaid;
				cout << " mt= ";
				cout << setw(5) << itm1->first;
				cout << ": part of mg cross sections are set to zero due to small fraction(";
				cout << scientific << setw(10) << setprecision(2) << XS_SMALL_RATIO;
				cout << ") to total cross section " << endl;
			}
		}
	}

	map<string, map<int, vector<REAL> > >::iterator itz2;
	map<int, vector<REAL> >::iterator itm2;
	for (itz2 = xs_mg_thermal_cutoff_ratio.begin(); itz2 != xs_mg_thermal_cutoff_ratio.end(); itz2++)
	{
		for (itm2 = itz2->second.begin(); itm2 != itz2->second.end(); itm2++)
		{
			vector<REAL>& vec = itm2->second;
			for (int i = 0; i < static_cast<int>(vec.size()); i++)
			{
				if (std::isnan(vec[i]))
				{
					cout << " element(s) of thermal cutoff ratio vector is nan " << endl;
					cout << " zaid " << itz1->first << " mt " << itm2->first << endl;
					//thereisnan = true;
					break;
				}
				checkFloatMinMax(vec[i]);
			}
		}
	}
	for (itz2 = nuchi_mg_1d_vector.begin(); itz2 != nuchi_mg_1d_vector.end(); itz2++)
	{
		for (itm2 = itz2->second.begin(); itm2 != itz2->second.end(); itm2++)
		{
			vector<REAL>& vec = itm2->second;
			for (int i = 0; i < static_cast<int>(vec.size()); i++)
			{
				if (std::isnan(vec[i]))
				{
					cout << " element(s) of nu, chi vector is nan " << endl;
					cout << " zaid " << itz1->first << " mt " << itm2->first << endl;
					//thereisnan = true;
					break;
				}
				checkFloatMinMax(vec[i]);
			}
		}
	}

	map<string, vector<vector<REAL> > >::iterator itz3;
	for (itz3 = chi_d_independent.begin(); itz3 != chi_d_independent.end(); itz3++)
	{
		vector<vector<REAL> >& vec = itz3->second;
		for (int j = 0; j < static_cast<int>(vec.size()); j++)
			for (int i = 0; i < static_cast<int>(vec[j].size()); i++)
			{
				if (std::isnan(vec[j][i]))
				{
					cout << " element(s) of chi delayed independent vector (nr) is nan " << endl;
					cout << " zaid " << itz3->first<< endl;
					//thereisnan = true;
					break;
				}
				checkFloatMinMax(vec[j][i]);
			}
	}

	map<string, vector<REAL> >::iterator itz4;
	for (itz4 = delayed_ratio.begin(); itz4 != delayed_ratio.end(); itz4++)
	{
		vector<REAL>& vec = itz4->second;
		for (int i = 0; i < static_cast<int>(vec.size()); i++)
		{
			if (std::isnan(vec[i]))
			{
				cout << " element(s) of chi delayed ratio vector (nr) is nan " << endl;
				cout << " zaid " << itz3->first << endl;
				//thereisnan = true;
				break;
			}
			checkFloatMinMax(vec[i]);
		}
	}

#if 0
	if (thereisnan)
	{
		exit(0);
	}
#endif
}
