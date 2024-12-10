#ifndef PERTURB_NUCLEAR_DATA_H
#define PERTURB_NUCLEAR_DATA_H

#include "CommonUtils/TabInterpolator.hpp"
#include "ContinuousEnergyXSUtils/AceDataParser/FastAceDataParser.hpp"
#include "ContinuousEnergyXSUtils/AceDataWriter/FastAceDataWriter.hpp"
#include "TabUtils/LinearizeTabData.hpp"
#include "CommonUtils/FileCommentRemover.hpp"
#include "CommonUtils/TabAdjuster.hpp"
#include "CommonUtils/StringUtils.hpp"

#ifdef _WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#endif

// maruyama-b
#include <boost/math/tools/roots.hpp>
#include <limits>
#include <tuple>
#include <cmath>
#include <bits/stdc++.h>
// maruyama-e


namespace frendy
{
	class PerturbNuclearData
	{
	private:

	public:
		//constructor
		PerturbNuclearData();

		//destructor
		virtual ~PerturbNuclearData();

		frendy::ErrorManager	err_obj;


		//Flag
		Integer mt_check_flg;

// maruyama-b
  		Integer sample_flg;
                Integer elsct_ang_flg;
// maruyama-e

		//Input
		string                            ace_file_name;
		string                            perturbation_file_name;
		vector<vector<Real> >             perturbation_input;//Row(number of input), Column(4); 1:MT,2:Emin,3:Emax,4:perturbation quantity
		vector<Integer>                   mt_list_input;//MT list of input with doubling
		vector<Integer>		          mt_list;      //MT list of input without doubling
		vector<vector<vector<Integer> > > mt_list_perturbation;//1:mt_list, 2:{MT,lower MT list, upper MT list}

		frendy::FastAceDataParser  read_obj;
		frendy::FastAceDataObject  ace_obj;
		frendy::FastAceDataWriter  wri_obj;
		frendy::LinearizeTabData   lin_obj;
		frendy::TabInterpolator    tab_obj;
		frendy::TabAdjuster        ta_obj;
		frendy::StringUtils        str_obj;
		frendy::FileCommentRemover file_mod_obj;



		//Parameters
		vector<Real>          union_ene_grid;
		vector<Real>          react_xs_tot;//MT = 1
		vector<Real>          react_xs_sc;//MT  = 2
		vector<Real>          react_xs_cap;//MT = 101
		vector<vector<Real> > react_xs;
		vector<vector<Real> > react_xs_filled_with_zero;
		vector<Integer>       react_type_list;

		Integer                p_tab_int, p_tab_self_shielding_flg;
		vector<Real>           p_tab_ene;
		vector<vector<Real> >  p_tab_heat, p_tab_sample_no;
		vector<vector<vector<Real> > > p_tab;


		vector<Real>          nu_union_ene_grid;

		Integer               nu_bar_repr_flg;
		vector<Integer>       nu_int_data;
		vector<Integer>       nu_range_data;
		vector<Real>          nu_data;
		vector<Real>          nu_ene_data;

		Integer               nu_d_bar_repr_flg;
		vector<Integer>       nu_d_int_data;
		vector<Integer>       nu_d_range_data;
		vector<Real>          nu_d_data;
		vector<Real>          nu_d_ene_data;

		Integer               nu_p_bar_repr_flg;
		vector<Integer>       nu_p_int_data;
		vector<Integer>       nu_p_range_data;
		vector<Real>          nu_p_data;
		vector<Real>          nu_p_ene_data;

		Integer               nu_ene_points_at_each_order = 100;
		Real                  nu_err_min = 1.0E-4;
		Real                  nu_err_relative = 1.0E-5;
		Integer               nu_flg;


		vector<vector<Integer> >                  ene_distr_ene_repr_flg;

		vector<vector<vector<Integer> > >         ene_distr_ene_in_int_data;
		vector<vector<vector<Integer> > >         ene_distr_ene_in_range_data;
		vector<vector<vector<Real> > >            ene_distr_ene_in_data;

		vector<vector<vector<Integer> > >         ene_distr_ene_out_int_data;
		vector<vector<vector<vector<Real> > > >   ene_distr_ene_out_ene_data;
		vector<vector<vector<vector<Real> > > >   ene_distr_ene_out_data;
		vector<vector<vector<vector<Real> > > >   ene_distr_ene_out_data_integ;

		vector<vector<Real> >                     ene_distr_upper_ene_limit;
		vector<vector<vector<Integer> > >         ene_distr_temp_eff_int_data;
		vector<vector<vector<Integer> > >         ene_distr_temp_eff_range_data;
		vector<vector<vector<Real> > >            ene_distr_temp_eff_ene_data;
		vector<vector<vector<Real> > >            ene_distr_temp_eff_data;

// maruyama-b
                vector<vector<Integer> >                  angular_distr_pointer;
                vector<Integer>                           angular_distr_type_flg;
                vector<vector<Integer> >                  angular_distr_int_data;
                vector<vector<Real> >                     angular_distr_ene_data;
                vector<vector<vector<Real> > >            angular_distr_cos_data;
                vector<vector<vector<Real> > >            angular_distr_data;
                vector<vector<vector<Real> > >            angular_distr_data_integ;

                vector<vector<Integer> >                  angular_distr_int_data0;
                vector<vector<Real> >                     angular_distr_ene_data0;
                vector<vector<vector<Real> > >            angular_distr_cos_data0;
                vector<vector<vector<Real> > >            angular_distr_data0;
                vector<vector<vector<Real> > >            angular_distr_data_integ0;

                vector<Real>                              elsct_ang_union_ene_grid;
                Integer                                   elsct_ang_ene_points_at_each_order = 100;

		vector<Real>                              elsct_ang_cos_grid;
                Integer                                   elsct_ang_cos_points_at_each_order = 100;

		vector<Real>                              mubar0;
		vector<vector<Real>>                      xi0;
		vector<vector<Real>>                      eta0;
		vector<vector<Real>>                      zeta0;

		Real                                      mubar;
		Real                                      lambda;
		Real                                      lower;
		Real                                      upper;
		vector<Real>                              pdf;
                vector<Real>                              xi;
                vector<Real>                              eta;
                vector<Real>                              zeta;

		Real                                      g0;
		Real                                      g1;
		Real                                      g2;
// maruyama-e

		vector<Real>                              chi_union_ene_grid;
		Integer                                   chi_ene_points_at_each_order = 100;

		Integer                                   chi_flg;
		vector<Integer>                           pos_chi_in_react_type_list;
		vector<vector<Integer> >                  chi_law_list;

		Integer               MT;
		Integer               pos_Emin;
		Integer               pos_Emax;
		Real                  Emin;
		Real                  Emax;
		Real                  multiplier;
		vector<Real>          each_input;


		string index;
		string output_ace_file_name;
		string output_xs_dir_name;


		//Main process
		void process_perturbed_nucl_data(string ace_file_name, string perturbaiton_file_name);

		//Random sampling
		Integer sample_size_extra;
		frendy::FastAceDataObject ace_obj_org;
		vector<string> perturbation_file_list;
		void set_ace_obj_org(string ace_file);
		void copy_ace_obj_org();
		void set_perturbation_file_list(string perturbation_file_list_file);
		void process_perturbed_nucl_data_for_rs(string ace_file, string perturbation_file_list_file);

		//General
		void check_mt_input();
		void check_mt_invalid_pair(Integer &invalid_mt_flg);
		void check_mt_invalid(Integer &invalid_mt_flg);
		void set_ace_obj(string ace_file);
		void set_perturbation_input_file(string perturbaiton_file);
		void set_ace_parameters();
		void set_mt_list_input();
		void set_ene_pos(vector<Real> energy_grid);
		void set_each_input(vector<Real> each_input);
		void perturb_nuclear_data();
		void set_perturbed_ace_obj();



		//Cross section
		void set_mt_list_perturbation();
		void set_reaxt_xs_filled_with_zero();
		void perturb_xs();
		void correct_xs_by_deviation(vector<Real> &vec_deviation, Integer MT);
		void correct_xs_by_multiplier(Real multiplier, Integer MT);


		//Probability table
		void perturb_p_table();
		void calc_p_table(Real ene_add, Integer int_val,
		       vector<Real>& ene_vec, vector<vector<Real> >& heat_vec, vector<vector<Real> >& no_vec,
		       vector<vector<vector<Real> > >& p_tab_vec,
		       vector<Real>& heat_add, vector<Real>& no_add, vector<vector<Real> >& p_tab_add);


		//Nu bar
		void linearize_nu();
		void tabulate_nu_data_repr_flg_1(vector<Integer> &nu_range_data, vector<Integer> &nu_int_data, vector<Real> &nu_ene_data, vector<Real> &nu_data, Integer &nu_repr_flg);
		void perturb_nu();
		void set_nu_union_ene_grid();
		void linearize_nu(vector<Integer> &nu_range_data, vector<Integer> &nu_int_data, vector<Real> &nu_ene_data, vector<Real> &nu_data, Integer &nu_repr_flg);
		void interpolate_nu_union_ene_grid(vector<Integer> &nu_range_data, vector<Integer> &nu_int_data, vector<Real> &nu_ene_data, vector<Real> &nu_data);

		//Energy distribution (fission spectrum)
		void linearize_chi();
		void set_chi_union_ene_grid();
		void perturb_chi();
		void set_pos_chi_in_react_type_list();
		void set_chi_law_list();
		void perturb_pdf_each(vector<Real>& ene_distr_ene_out_ene_data_new_each, vector<Real>& ene_distr_ene_out_data_each);
		void perturb_pdf();
		void set_new_cdf();
		void normalize_chi_pdf();
		void set_chi_cdf();
		void interpolate_chi_union_ene_grid(Integer& INTT, vector<Real> chi_union_ene_grid, vector<Real>& ene_distr_ene_out_ene_data_each, vector<Real>& ene_distr_ene_out_data);

// maruyama-b
                //Scattering angle distribution
		void save_elsct_angle_distr_obj();
		void load_elsct_angle_distr_obj();
		void write_test();
		void perturb_elsct_ang_distr();
		void linearize_elsct_ang_distr();
                void search_neighbor_value(Real& x_real, vector<Real>& x_data, int& i_m, int& i_p);
		void normalize_elsct_ang_distr_pdf();
		void set_elsct_ang_distr_cdf();
		void set_elsct_ang_union_ene_grid();
		void linearize_elsct_ang_distr_ene();
		void perturb_pdf_elsct_ang();
		void set_parameters_for_root_finding();
		void set_cutoffs();
		void set_function(double const& x);
		void solve_lambda();
		Real halley(Real guess, Real min, Real max, int digits, uintmax_t& max_iter); 
// maruyama-e


		vector<Real> get_vec_deviation(vector<Real> &vec_ori, vector<Real> &union_ene_grid);
		vector<Real> get_vec_in_react_xs(Integer MT);
		Integer      get_pos_in_react_xs(Integer MT);
		vector<Real> get_vec_target_xs(Integer MT);

		vector<vector<Real> > get_2d_vec_d(string filename);
		vector<string>        get_1d_vec_s(string filename);

		Integer check_same_value_1d_vec_i(Integer value, vector<Integer> vec_1i);
		Integer check_same_value_1d_vec_d(Real value, vector<Real> vec_1d);
		Integer get_number_of_int(Integer number, vector<Integer>& vec);

		void erase_space_in_string_line(string& line);
		void remove_same_value_1d_vec_i(vector<Integer>& vec_1i);
		void check_input_mt_list();
		void remove_mt_not_react_type_list();
		void correct_vec_by_deviation(vector<Real>& vec_ori, vector<Real>& vec_deviation);
		void correct_vec_by_multiplier(vector<Real>& vec_ori, Real multiplier);
		void correct_react_xs();
		void write_ace_file_test();
		void write_ace_file();


		static const int max_data_no = 2147483647;

		//ENDF/B VII.1 sum rules for cross section
		const vector<vector<Integer> > group_MT_1 = { {1}, { 2, 3 } };
		const vector<vector<Integer> > group_MT_3 = { { 3 },{ 4, 5, 11, 16, 17, 22, 23, 24, 25, 26, 27, 28, 29, 30,
			31,32,33,34,35,36,37,41,42,44,45,152,153,
			154,156,157,158,159,160,161,162,163,164,165,
			166,167,168,169,170,171,172,173,174,175,176,177,
			178,179,180,181,183,184,185,186,187,188,189,190,
			194,195,196,198,199,200 } };
		const vector<vector<Integer> > group_MT_4 = { { 4 },{ 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62,
			63,64,65,66,67,68,69,70,71,72,73,74,75,
			76,77,78,79,80,81,82,83,84,85,86,87,88,
			89,90,91 } };
		const vector<vector<Integer> > group_MT_16 = { { 16 },{ 875, 876, 877, 878, 879, 880, 881, 882, 883, 884,
			885,886,887,888,889,890,891 } };
		const vector<vector<Integer> > group_MT_18 = { { 18 },{ 19, 20, 21, 38 } };
		const vector<vector<Integer> > group_MT_27 = { { 27 },{ 18, 101 } };
		const vector<vector<Integer> > group_MT_101 = { { 101 },{ 102, 103, 104, 105, 106, 107, 108, 109, 110, 111,
			112,113,114,115,116,117,155,182,191,192,
			193,197 } };
		const vector<vector<Integer> > group_MT_103 = { { 103 },{ 600, 601, 602, 603, 604, 605, 606, 607, 608, 609,
			610,611,612,613,614,615,616,617,618,619,
			620,621,622,623,624,625,626,627,628,629,
			630,631,632,633,634,635,636,637,638,639,
			640,641,642,643,644,645,646,647,648,649 } };
		const vector<vector<Integer> > group_MT_104 = { { 104 },{ 650, 651, 652, 653, 654, 655, 656, 657, 658, 659,
			660,661,662,663,664,665,666,667,668,669,
			670,671,672,673,674,675,676,677,678,679,
			680,681,682,683,684,685,686,687,688,689,
			690,691,692,693,694,695,696,697,698,699 } };
		const vector<vector<Integer> > group_MT_105 = { { 105 },{ 700, 701, 702, 703, 704, 705, 706, 707, 708, 709,
			710,711,712,713,714,715,716,717,718,719,
			720,721,722,723,724,725,726,727,728,729,
			730,731,732,733,734,735,736,737,738,739,
			740,741,742,743,744,745,746,747,748,749 } };
		const vector<vector<Integer> > group_MT_106 = { { 106 },{ 750, 751, 752, 753, 754, 755, 756, 757, 758, 759,
			760,761,762,763,764,765,766,767,768,769,
			770,771,772,773,774,775,776,777,778,779,
			780,781,782,783,784,785,786,787,788,789,
			790,791,792,793,794,795,796,797,798,799 } };
		const vector<vector<Integer> > group_MT_107 = { { 107 },{ 800, 801, 802, 803, 804, 805, 806, 807, 808, 809,
			810,811,812,813,814,815,816,817,818,819,
			820,821,822,823,824,825,826,827,828,829,
			830,831,832,833,834,835,836,837,838,839,
			840,841,842,843,844,845,846,847,848,849 } };
		const vector<vector<vector<Integer> > > group_MT_all_xs = { group_MT_1,group_MT_3,group_MT_4,
			group_MT_16,group_MT_18,group_MT_27,
			group_MT_101,group_MT_103,group_MT_104,
			group_MT_105,group_MT_106,group_MT_107 };
		const vector<vector<Integer> > group_nu_values = { {452},{455,456} };
	};
}

#endif //PERTURB_NUCLEAR_DATA_H
