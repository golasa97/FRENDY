#include "FrendyUtils/FrendyInputCommonUtils.hpp"

using namespace frendy;

//constructor
FrendyInputCommonUtils::FrendyInputCommonUtils(void)
{
  clear();
}

//destructor
FrendyInputCommonUtils::~FrendyInputCommonUtils(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void FrendyInputCommonUtils::clear()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

const int     FrendyInputCommonUtils::calc_mode_no;
const int     FrendyInputCommonUtils::ace_fast_mode;
const int     FrendyInputCommonUtils::ace_therm_mode;
const int     FrendyInputCommonUtils::ace_dosi_mode;
const int     FrendyInputCommonUtils::make_inp_mode;
const int     FrendyInputCommonUtils::mg_neutron_mode;
const int     FrendyInputCommonUtils::mg_tsl_mode;
const int     FrendyInputCommonUtils::mg_tsl_mode_fast;
const int     FrendyInputCommonUtils::endf_modify_mode;
const int     FrendyInputCommonUtils::check_endf_mode;
const int     FrendyInputCommonUtils::plot_mode;
const int     FrendyInputCommonUtils::njoy_mode;
const int     FrendyInputCommonUtils::non_related;

const Integer FrendyInputCommonUtils::on;
const Integer FrendyInputCommonUtils::off;

const int     FrendyInputCommonUtils::print_set_data;
const int     FrendyInputCommonUtils::no_print_set_data;

const int     FrendyInputCommonUtils::process_data;
const int     FrendyInputCommonUtils::skip_process_data;

const int     FrendyInputCommonUtils::write_pendf;
const int     FrendyInputCommonUtils::skip_write_pendf;

const Integer FrendyInputCommonUtils::no_cumulative_angle_distribution_format;
const Integer FrendyInputCommonUtils::use_cumulative_angle_distribution_format;

const Integer FrendyInputCommonUtils::variable_weight;
const Integer FrendyInputCommonUtils::constant_weight;
const Integer FrendyInputCommonUtils::tabulated_weight;

const int     FrendyInputCommonUtils::start_file_endf;
const int     FrendyInputCommonUtils::start_file_ace;

////////////////////////////////////////////////////////////////////////////////////////////////////

//For calc_mode
int FrendyInputCommonUtils::get_calc_mode_def()
{
  return ace_fast_mode;
}

//For print_set_data_flg
int FrendyInputCommonUtils::get_print_set_data_flg_def()
{
  return print_set_data;
}

//For process_flg
int FrendyInputCommonUtils::get_process_flg_def()
{
  return process_data;
}

//For write_pendf_flg
int FrendyInputCommonUtils::get_write_pendf_flg_def()
{
  return skip_write_pendf;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

// **** Default value for CommonData ****
string FrendyInputCommonUtils::get_input_file_name_def()
{
  return "";
}

vector<string> FrendyInputCommonUtils::get_nucl_file_name_def()
{
  vector<string> str_vec;
  str_vec.clear();

  return str_vec;
}

vector<string> FrendyInputCommonUtils::get_pendf_file_name_def()
{
  vector<string> str_vec;
  str_vec.clear();

  return str_vec;
}

vector<string> FrendyInputCommonUtils::get_pendf_label_data_def()
{
  vector<string> str_vec;
  str_vec.clear();

  return str_vec;
}

vector<string> FrendyInputCommonUtils::get_comment_data_def()
{
  vector<string> comment_data_def;
  vector<string>().swap(comment_data_def);
  return comment_data_def;
}

// **** Default value for ReconResonance ****
Real FrendyInputCommonUtils::get_error_def()
  {
  return 1.0E-3;
}

Real FrendyInputCommonUtils::get_error_max_def()
{
  return 1.0E-2; //error_def * 10.0
}

Real FrendyInputCommonUtils::get_error_integral_def()
{
  return 5.0E-8; //error_def / 20000.0
}

vector<Real> FrendyInputCommonUtils::get_add_grid_data_def()
{
  vector<Real> add_grid_data_def;
  vector<Real>().swap(add_grid_data_def);
  return add_grid_data_def;
}


// *** Default value for DopplerBroadening ****
Real FrendyInputCommonUtils::get_temp_def()
{
  return 293.6;
}

Real FrendyInputCommonUtils::get_max_broadening_ene_def()
{
  return 1.0E+6;
}

// **** Default value for UnresoUtils ****
Integer FrendyInputCommonUtils::get_probability_bin_no_def()
{
  return 20;
}

Integer FrendyInputCommonUtils::get_ladder_no_def()
{
  return 100;
}

Real    FrendyInputCommonUtils::get_err_p_tab_def()
{
  return 5.0E-2;
}

Integer FrendyInputCommonUtils::get_ene_grid_no_per_ladder_def()
{
  return 10000;
}

Integer FrendyInputCommonUtils::get_random_seed_def()
{
  return 12345;
}

vector<Real> FrendyInputCommonUtils::get_sigma_zero_data_def()
{
  //This sigma_zero value is identical to MATXSLIB-J40
  vector<Real> sigma_zero_data_def;
  sigma_zero_data_def.resize(10);
  sigma_zero_data_def[0] = 1.0E+10;
  sigma_zero_data_def[1] = 1.0E+04;
  sigma_zero_data_def[2] = 1000.0;
  sigma_zero_data_def[3] =  300.0;
  sigma_zero_data_def[4] =  100.0;
  sigma_zero_data_def[5] =   30.0;
  sigma_zero_data_def[6] =   10.0;
  sigma_zero_data_def[7] =    1.0;
  sigma_zero_data_def[8] =      0.1;
  sigma_zero_data_def[9] = 1.0E-05;
  sort( sigma_zero_data_def.begin(), sigma_zero_data_def.end(), greater<Real>() );

  return sigma_zero_data_def;
}

// **** Default value for ThermalScatter ****
vector<string> FrendyInputCommonUtils::get_nucl_file_name_tsl_def()
{
  vector<string> str_vec;
  str_vec.clear();

  return str_vec;
}

Integer FrendyInputCommonUtils::get_equi_probable_angle_no_def()
{
  return 80;
}

Integer FrendyInputCommonUtils::get_equi_probable_angle_no_tsl_def()
{
  return 30;
}

Integer FrendyInputCommonUtils::get_inelastic_distribution_format_def()
{
  return 1;
}

Integer FrendyInputCommonUtils::get_principal_atom_no_def()
{
  return -1;
}

Integer FrendyInputCommonUtils::get_inelastic_reaction_type_no_def()
{
  return 221;
}

Real FrendyInputCommonUtils::get_max_thermal_ene_in_def()
{
  return 10.0;
}

Real FrendyInputCommonUtils::get_max_thermal_ene_out_def()
{
  return 20.0;
}

// **** Default value for AceDataGenerator ****
vector<string> FrendyInputCommonUtils::get_ace_file_name_def()
{
  vector<string> str_vec;
  str_vec.clear();

  return str_vec;
}

vector<string> FrendyInputCommonUtils::get_ace_dir_file_name_def()
{
  vector<string> str_vec;
  str_vec.clear();

  return str_vec;
}

Real FrendyInputCommonUtils::get_suffix_id_def()
{
  return 0.0;
}

vector<string> FrendyInputCommonUtils::get_ace_label_data_def()
{
  vector<string> str_vec;
  str_vec.clear();

  return str_vec;
}

vector<vector<Real> > FrendyInputCommonUtils::get_iz_aw_data_def()
{
  vector<vector<Real> > iz_aw_data;
  vector<vector<Real> >().swap(iz_aw_data);

  return iz_aw_data;
}

// **** Default value for FastAceDataGenerator ****
Integer FrendyInputCommonUtils::get_cumulative_angle_distribution_format_def()
{
  return use_cumulative_angle_distribution_format;
}

// **** Default value for ThermalScatterAceDataGenerator ****
string FrendyInputCommonUtils::get_thermal_za_id_name_def()
{
  return "";
}

vector<Integer> FrendyInputCommonUtils::get_moderator_za_data_def()
{
  vector<Integer> moderator_za_data;
  moderator_za_data.clear();

    return moderator_za_data;
}

Integer FrendyInputCommonUtils::get_atom_type_no_def()
{
  return -1;
}

Integer FrendyInputCommonUtils::get_weight_option_def()
{
  return tabulated_weight;
}

// **** Default value for MultiGroupGenerator ****
int             FrendyInputCommonUtils::get_mg_start_file_flg_def()
{
  return start_file_endf;
}

int             FrendyInputCommonUtils::get_ace_output_flg_def()
{
  return on;
}

vector<string>  FrendyInputCommonUtils::get_mg_edit_mode_def()
{
  vector<string> str_vec;
  str_vec.resize(2);
  str_vec[0] = "gendf";
  str_vec[1] = "SkipPrintout";

  return str_vec;
}

vector<string>  FrendyInputCommonUtils::get_mg_flux_calc_mode_def()
{
  vector<string> str_vec;
  str_vec.resize(1);
  str_vec[0] = "sld";

  return str_vec;
}

string          FrendyInputCommonUtils::get_mg_start_file_mode_def()
{
  return "endf";
}

string          FrendyInputCommonUtils::get_mg_weighting_spectrum_mode_def()
{
  return "1/e";
}

Real            FrendyInputCommonUtils::get_mg_weighting_spectrum_el_def()
{
  return 1.0E-5;
}

Real            FrendyInputCommonUtils::get_mg_weighting_spectrum_eh_def()
{
  return 2.0E+7;
}

Real            FrendyInputCommonUtils::get_mg_weighting_fission_temp_def()
{
  return 0.0; //Use default value of FRENDY/MG
  //return 1.6E+6;
}

Real            FrendyInputCommonUtils::get_mg_weighting_1e_el_def()
{
  return 0.0; //Use default value of FRENDY/MG
  //return 0.625;
}

Real            FrendyInputCommonUtils::get_mg_weighting_1e_eh_def()
{
  return 0.0; //Use default value of FRENDY/MG
  //return 1.0E+6;
}

vector<Real>    FrendyInputCommonUtils::get_mg_structure_def()
{
  vector<Real> real_vec;
  real_vec.resize(173);
  real_vec[  0] = 1.9640300000E+01;
  real_vec[  1] = 1.7332500000E+01;
  real_vec[  2] = 1.4918200000E+01;
  real_vec[  3] = 1.3840300000E+01;
  real_vec[  4] = 1.1618300000E+01;
  real_vec[  5] = 1.0000000000E+01;
  real_vec[  6] = 8.1873100000E+00;
  real_vec[  7] = 6.7032000000E+00;
  real_vec[  8] = 6.0653100000E+00;
  real_vec[  9] = 5.4881200000E+00;
  real_vec[ 10] = 4.4932900000E+00;
  real_vec[ 11] = 3.6787900000E+00;
  real_vec[ 12] = 3.0119400000E+00;
  real_vec[ 13] = 2.4659700000E+00;
  real_vec[ 14] = 2.2313000000E+00;
  real_vec[ 15] = 2.0189700000E+00;
  real_vec[ 16] = 1.6529900000E+00;
  real_vec[ 17] = 1.3533500000E+00;
  real_vec[ 18] = 1.2245600000E+00;
  real_vec[ 19] = 1.1080300000E+00;
  real_vec[ 20] = 1.0025900000E+00;
  real_vec[ 21] = 9.0718000000E-01;
  real_vec[ 22] = 8.2085000000E-01;
  real_vec[ 23] = 6.0810100000E-01;
  real_vec[ 24] = 5.5023200000E-01;
  real_vec[ 25] = 4.9787100000E-01;
  real_vec[ 26] = 4.5049200000E-01;
  real_vec[ 27] = 4.0762200000E-01;
  real_vec[ 28] = 3.0197400000E-01;
  real_vec[ 29] = 2.7323700000E-01;
  real_vec[ 30] = 2.4723500000E-01;
  real_vec[ 31] = 1.8315600000E-01;
  real_vec[ 32] = 1.2277300000E-01;
  real_vec[ 33] = 1.1109000000E-01;
  real_vec[ 34] = 8.2297500000E-02;
  real_vec[ 35] = 6.7379500000E-02;
  real_vec[ 36] = 5.5165600000E-02;
  real_vec[ 37] = 4.0867700000E-02;
  real_vec[ 38] = 3.6978600000E-02;
  real_vec[ 39] = 2.9283000000E-02;
  real_vec[ 40] = 2.7394400000E-02;
  real_vec[ 41] = 2.4787500000E-02;
  real_vec[ 42] = 1.6615600000E-02;
  real_vec[ 43] = 1.5034400000E-02;
  real_vec[ 44] = 1.1137800000E-02;
  real_vec[ 45] = 9.1188200000E-03;
  real_vec[ 46] = 7.4658600000E-03;
  real_vec[ 47] = 5.5308400000E-03;
  real_vec[ 48] = 5.0045100000E-03;
  real_vec[ 49] = 3.5266200000E-03;
  real_vec[ 50] = 3.3546300000E-03;
  real_vec[ 51] = 2.2486700000E-03;
  real_vec[ 52] = 2.0346800000E-03;
  real_vec[ 53] = 1.5073300000E-03;
  real_vec[ 54] = 1.4338200000E-03;
  real_vec[ 55] = 1.2341000000E-03;
  real_vec[ 56] = 1.0103900000E-03;
  real_vec[ 57] = 9.1424200000E-04;
  real_vec[ 58] = 7.4851800000E-04;
  real_vec[ 59] = 6.7728700000E-04;
  real_vec[ 60] = 4.5399900000E-04;
  real_vec[ 61] = 3.7170300000E-04;
  real_vec[ 62] = 3.0432500000E-04;
  real_vec[ 63] = 2.0399500000E-04;
  real_vec[ 64] = 1.4862500000E-04;
  real_vec[ 65] = 1.3674200000E-04;
  real_vec[ 66] = 9.1660900000E-05;
  real_vec[ 67] = 7.5673600000E-05;
  real_vec[ 68] = 6.7904100000E-05;
  real_vec[ 69] = 5.5595100000E-05;
  real_vec[ 70] = 5.1578000000E-05;
  real_vec[ 71] = 4.8251600000E-05;
  real_vec[ 72] = 4.5517400000E-05;
  real_vec[ 73] = 4.0169000000E-05;
  real_vec[ 74] = 3.7266500000E-05;
  real_vec[ 75] = 3.3720100000E-05;
  real_vec[ 76] = 3.0511300000E-05;
  real_vec[ 77] = 2.7607700000E-05;
  real_vec[ 78] = 2.4980500000E-05;
  real_vec[ 79] = 2.2603300000E-05;
  real_vec[ 80] = 1.9454800000E-05;
  real_vec[ 81] = 1.5928300000E-05;
  real_vec[ 82] = 1.3709600000E-05;
  real_vec[ 83] = 1.1224500000E-05;
  real_vec[ 84] = 9.9055500000E-06;
  real_vec[ 85] = 9.1898100000E-06;
  real_vec[ 86] = 8.3152900000E-06;
  real_vec[ 87] = 7.5239800000E-06;
  real_vec[ 88] = 6.1601200000E-06;
  real_vec[ 89] = 5.3464300000E-06;
  real_vec[ 90] = 5.0434800000E-06;
  real_vec[ 91] = 4.1292500000E-06;
  real_vec[ 92] = 4.0000000000E-06;
  real_vec[ 93] = 3.3807500000E-06;
  real_vec[ 94] = 3.3000000000E-06;
  real_vec[ 95] = 2.7679200000E-06;
  real_vec[ 96] = 2.7200000000E-06;
  real_vec[ 97] = 2.6000000000E-06;
  real_vec[ 98] = 2.5500000000E-06;
  real_vec[ 99] = 2.3600000000E-06;
  real_vec[100] = 2.1300000000E-06;
  real_vec[101] = 2.1000000000E-06;
  real_vec[102] = 2.0200000000E-06;
  real_vec[103] = 1.9300000000E-06;
  real_vec[104] = 1.8400000000E-06;
  real_vec[105] = 1.7550000000E-06;
  real_vec[106] = 1.6700000000E-06;
  real_vec[107] = 1.5900000000E-06;
  real_vec[108] = 1.5000000000E-06;
  real_vec[109] = 1.4750000000E-06;
  real_vec[110] = 1.4449800000E-06;
  real_vec[111] = 1.3700000000E-06;
  real_vec[112] = 1.3375000000E-06;
  real_vec[113] = 1.3000000000E-06;
  real_vec[114] = 1.2350000000E-06;
  real_vec[115] = 1.1700000000E-06;
  real_vec[116] = 1.1500000000E-06;
  real_vec[117] = 1.1253500000E-06;
  real_vec[118] = 1.1100000000E-06;
  real_vec[119] = 1.0970000000E-06;
  real_vec[120] = 1.0710000000E-06;
  real_vec[121] = 1.0450000000E-06;
  real_vec[122] = 1.0350000000E-06;
  real_vec[123] = 1.0200000000E-06;
  real_vec[124] = 9.9600000000E-07;
  real_vec[125] = 9.8600000000E-07;
  real_vec[126] = 9.7200000000E-07;
  real_vec[127] = 9.5000000000E-07;
  real_vec[128] = 9.3000000000E-07;
  real_vec[129] = 9.1000000000E-07;
  real_vec[130] = 8.6000000000E-07;
  real_vec[131] = 8.5000000000E-07;
  real_vec[132] = 7.9000000000E-07;
  real_vec[133] = 7.8000000000E-07;
  real_vec[134] = 7.0500000000E-07;
  real_vec[135] = 6.2500000000E-07;
  real_vec[136] = 5.4000000000E-07;
  real_vec[137] = 5.0000000000E-07;
  real_vec[138] = 4.8500000000E-07;
  real_vec[139] = 4.3300000000E-07;
  real_vec[140] = 4.0000000000E-07;
  real_vec[141] = 3.9100000000E-07;
  real_vec[142] = 3.5000000000E-07;
  real_vec[143] = 3.2000000000E-07;
  real_vec[144] = 3.1450000000E-07;
  real_vec[145] = 3.0000000000E-07;
  real_vec[146] = 2.8000000000E-07;
  real_vec[147] = 2.4800000000E-07;
  real_vec[148] = 2.2000000000E-07;
  real_vec[149] = 1.8900000000E-07;
  real_vec[150] = 1.8000000000E-07;
  real_vec[151] = 1.6000000000E-07;
  real_vec[152] = 1.4000000000E-07;
  real_vec[153] = 1.3400000000E-07;
  real_vec[154] = 1.1500000000E-07;
  real_vec[155] = 1.0000100000E-07;
  real_vec[156] = 9.5000000000E-08;
  real_vec[157] = 8.0000000000E-08;
  real_vec[158] = 7.7000000000E-08;
  real_vec[159] = 6.7000000000E-08;
  real_vec[160] = 5.8000000000E-08;
  real_vec[161] = 5.0000000000E-08;
  real_vec[162] = 4.2000000000E-08;
  real_vec[163] = 3.5000000000E-08;
  real_vec[164] = 3.0000000000E-08;
  real_vec[165] = 2.5000000000E-08;
  real_vec[166] = 2.0000000000E-08;
  real_vec[167] = 1.5000000000E-08;
  real_vec[168] = 1.0000000000E-08;
  real_vec[169] = 6.9000000000E-09;
  real_vec[170] = 5.0000000000E-09;
  real_vec[171] = 3.0000000000E-09;
  real_vec[172] = 1.0000000000E-11;

  for(int i=0; i<static_cast<int>(real_vec.size()); i++)
  {
    real_vec[i] *= unit_mega; //MeV -> eV
  }

  return real_vec;
}

vector<Real>    FrendyInputCommonUtils::get_mg_number_density_def()
{
  vector<Real> real_vec;
  real_vec.resize(1);
  real_vec[0] = 1.0;

  return real_vec;
}

vector<Real>    FrendyInputCommonUtils::get_mg_flux_calc_w_def()
{
  vector<Real> real_vec;
  real_vec.clear();

  return real_vec;
}

vector<Real>    FrendyInputCommonUtils::get_mg_flux_calc_eh_def()
{
  vector<Real> real_vec;
  real_vec.clear();

  return real_vec;
}

vector<Real>    FrendyInputCommonUtils::get_mg_flux_calc_el_def()
{
  vector<Real> real_vec;
  real_vec.clear();

  return real_vec;
}

vector<Integer> FrendyInputCommonUtils::get_mg_weighting_spectrum_data_int_def()
{
  vector<Integer> int_vec;
  int_vec.resize(1);
  int_vec[0] = int_lin_lin;

  return int_vec;
}

vector<Integer> FrendyInputCommonUtils::get_mg_weighting_spectrum_data_nbt_def()
{
  vector<Integer> int_vec;
  int_vec.resize(1);
  int_vec[0] = static_cast<Integer>(1.0 / min_value);

  return int_vec;
}

Integer         FrendyInputCommonUtils::get_mg_thermal_xs_treatment_def()
{
  return on;
}

Integer         FrendyInputCommonUtils::get_legendre_order_def()
{
  return 3;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int FrendyInputCommonUtils::read_print_set_data_flg(string class_name, string func_name,
                                                    vector<string>& input_data)
{
  if( static_cast<int>(input_data.size()) > 1 )
  {
    error_input_data_size_is_larger_than_one(class_name, func_name, input_data);
  }

  string input_data_mod = input_data[0];
  transform(input_data_mod.begin(), input_data_mod.end(), input_data_mod.begin(), ::tolower);

  int print_set_data_flg = 0;
  if( input_data_mod == "on" || input_data_mod == "yes" || input_data_mod == "print" ||
      input_data_mod == "write" || input_data_mod == "output" )
  {
    print_set_data_flg = print_set_data;
  }
  else if( input_data_mod == "off" || input_data_mod == "no" || input_data_mod == "skip" )
  {
    print_set_data_flg = no_print_set_data;
  }
  else if( input_data_mod == "default" || input_data_mod == "def" )
  {
    print_set_data_flg = get_print_set_data_flg_def();
  }
  else
  {
    vector<string> err_com;
    string str_data01 = "print_set_data_flg : " + input_data[0];
    err_com.push_back(str_data01);
    err_com.push_back("The print_set_data_flg is not appripriate.");
    err_com.push_back("The print_set_data_flg is only available for");
    err_com.push_back("on / yes / print / write / print, off / no / skip or default / def.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  return print_set_data_flg;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int FrendyInputCommonUtils::read_process_flg(string class_name, string func_name,
                                             vector<string>& input_data)
{
  if( static_cast<int>(input_data.size()) > 1 )
  {
    error_input_data_size_is_larger_than_one(class_name, func_name, input_data);
  }

  string input_data_mod = input_data[0];
  transform(input_data_mod.begin(), input_data_mod.end(), input_data_mod.begin(), ::tolower);

  int process_flg = 0;
  if( input_data_mod == "on" || input_data_mod == "yes" || input_data_mod == "process" ||
      input_data_mod == "run" )
  {
    process_flg = process_data;
  }
  else if( input_data_mod == "off" || input_data_mod == "no" || input_data_mod == "skip" )
  {
    process_flg = skip_process_data;
  }
  else if( input_data_mod == "default" || input_data_mod == "def" )
  {
    process_flg = get_process_flg_def();
  }
  else
  {
    vector<string> err_com;
    string str_data01 = "process_flg : " + input_data[0];
    err_com.push_back(str_data01);
    err_com.push_back("The process_flg is not appripriate.");
    err_com.push_back("The process_flg is only available for");
    err_com.push_back("on / yes / process / run, off / no / skip or default / def.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  return process_flg;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int FrendyInputCommonUtils::read_write_pendf_flg(string class_name, string func_name,
                                                 vector<string>& pendf_name,
                                                 vector<string>& input_data)
{
  if( static_cast<int>(input_data.size()) == 0 )
  {
    error_input_data_size_is_zero(class_name, func_name, input_data);
  }

  string input_data_mod = input_data[0];
  transform(input_data_mod.begin(), input_data_mod.end(), input_data_mod.begin(), ::tolower);

  int write_pendf_flg = 0;
  if( input_data_mod == "on" || input_data_mod == "yes" || input_data_mod == "print" ||
      input_data_mod == "write" || input_data_mod == "output" )
  {
    write_pendf_flg = write_pendf;

    int i_max = static_cast<int>(input_data.size());
    if( i_max > 1 )
    {
      pendf_name.resize(i_max-1);
      for(int i=1; i<i_max; i++)
      {
        pendf_name[i-1] = input_data[i];
      }
    }
  }
  else if( input_data_mod == "off" || input_data_mod == "no" || input_data_mod == "skip" )
  {
    write_pendf_flg = skip_write_pendf;
  }
  else if( input_data_mod == "default" || input_data_mod == "def" )
  {
    write_pendf_flg = get_write_pendf_flg_def();
    pendf_name      = get_pendf_file_name_def();
  }
  else
  {
    write_pendf_flg = write_pendf;
    pendf_name      = input_data;
  }

  if( write_pendf_flg == write_pendf && static_cast<int>(pendf_name.size()) == 0 )
  {
    vector<string> err_com;
    err_com.push_back("Though the write_pendf_flg is set to write_pendf, the PENDF file name is not set.");
    err_com.push_back("This program can not output the PENDF file.");
    err_com.push_back("If you want to output PENDF file, please set the PENDF file name.");

    err_obj.output_caution(class_name, func_name, err_com);
  }

  return write_pendf_flg;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void FrendyInputCommonUtils::output_str_vec(vector<string>& err_com, vector<string>& str_vec)
{
  int i_max = static_cast<int>(str_vec.size());
  ostringstream oss01;
  oss01 << i_max;
  string str_data01 = "Data number : " + oss01.str();
  err_com.push_back(str_data01);
  for(int i=0; i<i_max; i++)
  {
    ostringstream oss02;
    oss02 << i+1;
    string str_data02 = "  " + oss02.str() + " / " + oss01.str() + " : " + str_vec[i];
    err_com.push_back(str_data02);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void FrendyInputCommonUtils::error_input_type_size
                               (string class_name, string func_name, vector<string> input_type)
{
  vector<string> err_com;
  output_str_vec(err_com, input_type);
  err_com.push_back("Please check the input_type.");

  err_obj.output_runtime_error(class_name, func_name, err_com);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void FrendyInputCommonUtils::error_input_data_size_is_zero
                               (string class_name, string func_name, vector<string> input_data) 
{
  vector<string> err_com;
  err_com.push_back("The data number of input_data must be larger than or equal to 1.");
  err_com.push_back("Please check the input_data.");

  err_obj.output_runtime_error(class_name, func_name, err_com);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void FrendyInputCommonUtils::error_input_data_size_is_larger_than_one
                               (string class_name, string func_name, vector<string> input_data) 
{
  vector<string> err_com;
  output_str_vec(err_com, input_data);
  err_com.push_back("The data number of input_data must be 1.");
  err_com.push_back("Please check the input_data.");

  err_obj.output_runtime_error(class_name, func_name, err_com);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FrendyInputCommonUtils::check_print_set_data_flg(string class_name, int int_val)
{
  if( int_val != print_set_data && int_val != no_print_set_data )
  {
    string func_name = "check_print_set_data_flg(string class_name, int int_val)";

    vector<string> err_com;
    ostringstream oss01;
    oss01 << int_val;
    string str_data01 = "print_set_data_flg : " + oss01.str();
    err_com.push_back(str_data01);
    err_com.push_back("The print_set_data_flg is not appripriate.");
    err_com.push_back("The print_set_data_flg is only available for");
    err_com.push_back("0 (print_set_data) or 1 (no_print_set_data)");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void FrendyInputCommonUtils::check_process_flg(string class_name, int int_val)
{
  if( int_val != process_data && int_val != skip_process_data )
  {
    string func_name = "check_process_flg(string class_name, int int_val)";

    vector<string> err_com;
    ostringstream oss01;
    oss01 << int_val;
    string str_data01 = "process_flg : " + oss01.str();
    err_com.push_back(str_data01);
    err_com.push_back("The process_flg is not appripriate.");
    err_com.push_back("The process_flg is only available for");
    err_com.push_back("0 (process_data) or 1 (skip_process_data)");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FrendyInputCommonUtils::check_write_pendf_flg(string class_name, int int_val)
{
  if( int_val != write_pendf && int_val != skip_write_pendf )
  {
    string func_name = "check_write_pendf_flg(string class_name, int int_val)";

    vector<string> err_com;
    ostringstream oss01;
    oss01 << int_val;
    string str_data01 = "write_pendf_flg : " + oss01.str();
    err_com.push_back(str_data01);
    err_com.push_back("The write_pendf_flg is not appripriate.");
    err_com.push_back("The write_pendf_flg is only available for");
    err_com.push_back("0 (write_pendf) or 1 (skip_write_pendf)");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FrendyInputCommonUtils::check_write_pendf_flg_no_str_data(string class_name,
                                                               vector<string> pendf_name, int int_val)
{
  check_write_pendf_flg(class_name, int_val);

  if( int_val == write_pendf && static_cast<int>(pendf_name.size()) == 0 )
  {
    string func_name = "check_write_pendf_flg_no_str_data(string class_name, int int_val)";

    vector<string> err_com;
    ostringstream oss01;
    oss01 << int_val;
    string str_data01 = "write_pendf_flg : " + oss01.str() + " (write_pendf)";
    err_com.push_back(str_data01);
    err_com.push_back("The PENDF file name is not set.");
    err_com.push_back("This program can not output the PENDF file.");
    err_com.push_back("If you want to output PENDF file, please set the PENDF file name using");
    err_com.push_back("set_write_pendf_flg(int int_val, vector<string> file_name) function.");

    err_obj.output_caution(class_name, func_name, err_com);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FrendyInputCommonUtils::write_pendf_data(vector<string>& pendf_file_name,
                                              vector<string>& pendf_label_data,
                                              vector<string>& comment_data, int write_pendf_flg)
{
  if( write_pendf_flg == skip_write_pendf )
  {
    return;
  }

  for(int i=0; i<static_cast<int>(pendf_file_name.size()); i++)
  {
    if( i==0 )
    {
      cout << "  pendf_file_name   : " << pendf_file_name[i] << endl;
    }
    else
    {
      cout << "                    : " << pendf_file_name[i] << endl;
    }
  }

  for(int i=0; i<static_cast<int>(pendf_label_data.size()); i++)
  {
    if( i==0 )
    {
      cout << "  pendf_label_data  : " << pendf_label_data[i] << endl;
    }
    else
    {
      cout << "                    : " << pendf_label_data[i] << endl;
    }
  }

  if( static_cast<int>(comment_data.size()) > 0 )
  {
    cout << "  comment_data" << endl;
    int i_max = static_cast<int>(comment_data.size());
    for(int i=0; i<i_max; i++)
    {
      cout << "    " << i+1 << " / " << i_max << " : " << comment_data[i] << endl;
    }
  }
}

