#include "NuclearDataUtils/NuclearDataContainer/GeneralDataContainer.hpp"

using namespace frendy;

//constructor
GeneralDataContainer::GeneralDataContainer(void)
{
  clear();
}

//destructor
GeneralDataContainer::~GeneralDataContainer(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GeneralDataContainer::clear()
{
  mat_no                  = unassigned_mat_no;
  mat_data                = 0.0;
  mass                    = 0.0;

  reso_flg                = 0;
  fis_flg                 = 0;
  lib_identifier          = 0;
  lib_mod_no              = 0;
  excitation_ene          = 0.0;
  stability_flg_target    = 0;
  state_no                = 0;
  iso_state_no            = 0;
  lib_format              = 0;
  mass_projectile         = 0.0;
  upper_ene_limit         = 0.0;
  lib_release_no          = 0;
  sub_lib_no              = 0;
  lib_ver                 = 0;
  temp                    = 0.0;
  error_value             = 0.0;
  special_derived_mat_flg = 0;
  state_no_target         = 0;
  state_no_target_iso     = 0;
  stability_flg           = 0;
  half_life               = 0.0;
  half_life_uncertainty   = 0.0;
  spin_target             = 0.0;
  parity_target           = 0.0;

  brief_explain_word.clear();
  evaluated_institute.clear();
  evaluated_date.clear();
  evaluated_author.clear();
  evaluated_ref.clear();
  evaluated_date_ori.clear();
  evaluated_date_rev.clear();
  evaluated_date_end.clear();
  evaluated_data_specification.clear();

  clr_obj.clear_vec_array2_int( file_section_data_list );
  clr_obj.clear_vec_array1_str( comment_data );
  decay_ene.clear();
  decay_ene_uncertainty.clear();
  decay_type.clear();
  daughter_iso_flg.clear();
  decay_ene_tot.clear();
  decay_ene_tot_uncertainty.clear();
  branching_ratio.clear();
  branching_ratio_uncertainty.clear();
  radiation_type.clear();
  con_spectrum_flg.clear();
  discrete_spectrum_factor.clear();
  discrete_spectrum_factor_uncertainty.clear();
  discrete_ene_ave.clear();
  discrete_ene_ave_uncertainty.clear();
  cont_spectrum_factor.clear();
  cont_spectrum_factor_uncertainty.clear();
  clr_obj.clear_vec_array2_real( discrete_ene );
  clr_obj.clear_vec_array2_real( discrete_ene_uncertainty );
  clr_obj.clear_vec_array2_real( discrete_intensity );
  clr_obj.clear_vec_array2_real( discrete_intensity_uncertainty );
  clr_obj.clear_vec_array2_real( decay_type_each_ene );
  clr_obj.clear_vec_array2_real( transition_type );
  clr_obj.clear_vec_array2_real( internal_pair_form_coef );
  clr_obj.clear_vec_array2_real( internal_pair_form_coef_uncertainty );
  clr_obj.clear_vec_array2_real( conv_coef_tot );
  clr_obj.clear_vec_array2_real( conv_coef_tot_uncertainty );
  clr_obj.clear_vec_array2_real( conv_coef_k );
  clr_obj.clear_vec_array2_real( conv_coef_k_uncertainty );
  clr_obj.clear_vec_array2_real( conv_coef_l );
  clr_obj.clear_vec_array2_real( conv_coef_l_uncertainty );
  decay_type_each_rad.clear();
  cont_spectrum_cov_flg.clear();
  clr_obj.clear_vec_array2_int( cont_spectrum_cov_int_data );
  clr_obj.clear_vec_array2_int( cont_spectrum_cov_range_data );
  clr_obj.clear_vec_array2_real( cont_spectrum_cov_ene_data );
  clr_obj.clear_vec_array2_real( cont_spectrum_cov_data );
  cont_spectrum_cov_matrix_data_flg.clear();
  clr_obj.clear_vec_array2_real( cont_spectrum_cov_ek_table );
  clr_obj.clear_vec_array2_real( cont_spectrum_cov_fk_table );
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Getter
Integer GeneralDataContainer::get_mat_no()
{
  return mat_no;
}

Real GeneralDataContainer::get_mat_data()
{
  return mat_data;
}

Real GeneralDataContainer::get_mass()
{
  return mass;
}

Integer GeneralDataContainer::get_reso_flg()
{
  return reso_flg;
}

Integer GeneralDataContainer::get_fis_flg()
{
  return fis_flg;
}

Integer GeneralDataContainer::get_lib_identifier()
{
  return lib_identifier;
}

Integer GeneralDataContainer::get_lib_mod_no()
{
  return lib_mod_no;
}

Real GeneralDataContainer::get_excitation_ene()
{
  return excitation_ene;
}

Integer GeneralDataContainer::get_stability_flg_target()
{
  return stability_flg_target;
}

Integer GeneralDataContainer::get_state_no()
{
  return state_no;
}

Integer GeneralDataContainer::get_iso_state_no()
{
  return iso_state_no;
}

Integer GeneralDataContainer::get_lib_format()
{
  return lib_format;
}

Real GeneralDataContainer::get_mass_projectile()
{
  return mass_projectile;
}

Real GeneralDataContainer::get_upper_ene_limit()
{
  return upper_ene_limit;
}

Integer GeneralDataContainer::get_lib_release_no()
{
  return lib_release_no;
}

Integer GeneralDataContainer::get_sub_lib_no()
{
  return sub_lib_no;
}

Integer GeneralDataContainer::get_lib_ver()
{
  return lib_ver;
}

Real GeneralDataContainer::get_temp()
{
  return temp;
}

Real GeneralDataContainer::get_error_value()
{
  return error_value;
}

Integer GeneralDataContainer::get_special_derived_mat_flg()
{
  return special_derived_mat_flg;
}

string GeneralDataContainer::get_brief_explain_word()
{
  return brief_explain_word;
}

string GeneralDataContainer::get_evaluated_institute()
{
  return evaluated_institute;
}

string GeneralDataContainer::get_evaluated_date()
{
  return evaluated_date;
}

string GeneralDataContainer::get_evaluated_author()
{
  return evaluated_author;
}

string GeneralDataContainer::get_evaluated_ref()
{
  return evaluated_ref;
}

string GeneralDataContainer::get_evaluated_date_ori()
{
  return evaluated_date_ori;
}

string GeneralDataContainer::get_evaluated_date_rev()
{
  return evaluated_date_rev;
}

string GeneralDataContainer::get_evaluated_date_end()
{
  return evaluated_date_end;
}

string GeneralDataContainer::get_evaluated_data_specification()
{
  return evaluated_data_specification;
}

vector<vector<Integer> > GeneralDataContainer::get_file_section_data_list()
{
  return file_section_data_list;
}

vector<string> GeneralDataContainer::get_comment_data()
{
  return comment_data;
}

Integer GeneralDataContainer::get_state_no_target()
{
  return state_no_target;
}

Integer GeneralDataContainer::get_state_no_target_iso()
{
  return state_no_target_iso;
}

Integer GeneralDataContainer::get_stability_flg()
{
  return stability_flg;
}

Real GeneralDataContainer::get_half_life()
{
  return half_life;
}

Real GeneralDataContainer::get_half_life_uncertainty()
{
  return half_life_uncertainty;
}

vector<Real> GeneralDataContainer::get_decay_ene()
{
  return decay_ene;
}

vector<Real> GeneralDataContainer::get_decay_ene_uncertainty()
{
  return decay_ene_uncertainty;
}

Real GeneralDataContainer::get_spin_target()
{
  return spin_target;
}

Real GeneralDataContainer::get_parity_target()
{
  return parity_target;
}

vector<Real> GeneralDataContainer::get_decay_type()
{
  return decay_type;
}

vector<Real> GeneralDataContainer::get_daughter_iso_flg()
{
  return daughter_iso_flg;
}

vector<Real> GeneralDataContainer::get_decay_ene_tot()
{
  return decay_ene_tot;
}

vector<Real> GeneralDataContainer::get_decay_ene_tot_uncertainty()
{
  return decay_ene_tot_uncertainty;
}

vector<Real> GeneralDataContainer::get_branching_ratio()
{
  return branching_ratio;
}

vector<Real> GeneralDataContainer::get_branching_ratio_uncertainty()
{
  return branching_ratio_uncertainty;
}

vector<Real> GeneralDataContainer::get_radiation_type()
{
  return radiation_type;
}

vector<Integer> GeneralDataContainer::get_con_spectrum_flg()
{
  return con_spectrum_flg;
}

vector<Real> GeneralDataContainer::get_discrete_spectrum_factor()
{
  return discrete_spectrum_factor;
}

vector<Real> GeneralDataContainer::get_discrete_spectrum_factor_uncertainty()
{
  return discrete_spectrum_factor_uncertainty;
}

vector<Real> GeneralDataContainer::get_discrete_ene_ave()
{
  return discrete_ene_ave;
}

vector<Real> GeneralDataContainer::get_discrete_ene_ave_uncertainty()
{
  return discrete_ene_ave_uncertainty;
}

vector<Real> GeneralDataContainer::get_cont_spectrum_factor()
{
  return cont_spectrum_factor;
}

vector<Real> GeneralDataContainer::get_cont_spectrum_factor_uncertainty()
{
  return cont_spectrum_factor_uncertainty;
}

vector<vector<Real> > GeneralDataContainer::get_discrete_ene()
{
  return discrete_ene;
}

vector<vector<Real> > GeneralDataContainer::get_discrete_ene_uncertainty()
{
  return discrete_ene_uncertainty;
}

vector<vector<Real> > GeneralDataContainer::get_discrete_intensity()
{
  return discrete_intensity;
}

vector<vector<Real> > GeneralDataContainer::get_discrete_intensity_uncertainty()
{
  return discrete_intensity_uncertainty;
}

vector<vector<Real> > GeneralDataContainer::get_decay_type_each_ene()
{
  return decay_type_each_ene;
}

vector<vector<Real> > GeneralDataContainer::get_transition_type()
{
  return transition_type;
}

vector<vector<Real> > GeneralDataContainer::get_internal_pair_form_coef()
{
  return internal_pair_form_coef;
}

vector<vector<Real> > GeneralDataContainer::get_internal_pair_form_coef_uncertainty()
{
  return internal_pair_form_coef_uncertainty;
}

vector<vector<Real> > GeneralDataContainer::get_conv_coef_tot()
{
  return conv_coef_tot;
}

vector<vector<Real> > GeneralDataContainer::get_conv_coef_tot_uncertainty()
{
  return conv_coef_tot_uncertainty;
}

vector<vector<Real> > GeneralDataContainer::get_conv_coef_k()
{
  return conv_coef_k;
}

vector<vector<Real> > GeneralDataContainer::get_conv_coef_k_uncertainty()
{
  return conv_coef_k_uncertainty;
}

vector<vector<Real> > GeneralDataContainer::get_conv_coef_l()
{
  return conv_coef_l;
}

vector<vector<Real> > GeneralDataContainer::get_conv_coef_l_uncertainty()
{
  return conv_coef_l_uncertainty;
}

vector<Real> GeneralDataContainer::get_decay_type_each_rad()
{
  return decay_type_each_rad;
}

vector<Integer> GeneralDataContainer::get_cont_spectrum_cov_flg()
{
  return cont_spectrum_cov_flg;
}

vector<vector<Integer> > GeneralDataContainer::get_cont_spectrum_cov_int_data()
{
  return cont_spectrum_cov_int_data;
}

vector<vector<Integer> > GeneralDataContainer::get_cont_spectrum_cov_range_data()
{
  return cont_spectrum_cov_range_data;
}

vector<vector<Real> > GeneralDataContainer::get_cont_spectrum_cov_ene_data()
{
  return cont_spectrum_cov_ene_data;
}

vector<vector<Real> > GeneralDataContainer::get_cont_spectrum_cov_data()
{
  return cont_spectrum_cov_data;
}

vector<Integer> GeneralDataContainer::get_cont_spectrum_cov_matrix_data_flg()
{
  return cont_spectrum_cov_matrix_data_flg;
}

vector<vector<Real> > GeneralDataContainer::get_cont_spectrum_cov_ek_table()
{
  return cont_spectrum_cov_ek_table;
}

vector<vector<Real> > GeneralDataContainer::get_cont_spectrum_cov_fk_table()
{
  return cont_spectrum_cov_fk_table;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void GeneralDataContainer::set_mat_no( Integer int_data )
{
  mat_no = int_data;
}

void GeneralDataContainer::set_mat_data( Real real_data )
{
  mat_data = real_data;
}

void GeneralDataContainer::set_mass( Real real_data )
{
  mass = real_data;
}

void GeneralDataContainer::set_reso_flg( Integer int_data )
{
  reso_flg = int_data;
}

void GeneralDataContainer::set_fis_flg( Integer int_data )
{
  fis_flg = int_data;
}

void GeneralDataContainer::set_lib_identifier( Integer int_data )
{
  lib_identifier = int_data;
}

void GeneralDataContainer::set_lib_mod_no( Integer int_data )
{
  lib_mod_no = int_data;
}

void GeneralDataContainer::set_excitation_ene( Real real_data )
{
  excitation_ene = real_data;
}

void GeneralDataContainer::set_stability_flg_target( Integer int_data )
{
  stability_flg_target = int_data;
}

void GeneralDataContainer::set_state_no( Integer int_data )
{
  state_no = int_data;
}

void GeneralDataContainer::set_iso_state_no( Integer int_data )
{
  iso_state_no = int_data;
}

void GeneralDataContainer::set_lib_format( Integer int_data )
{
  lib_format = int_data;
}

void GeneralDataContainer::set_mass_projectile( Real real_data )
{
  mass_projectile = real_data;
}

void GeneralDataContainer::set_upper_ene_limit( Real real_data )
{
  upper_ene_limit = real_data;
}

void GeneralDataContainer::set_lib_release_no( Integer int_data )
{
  lib_release_no = int_data;
}

void GeneralDataContainer::set_sub_lib_no( Integer int_data )
{
  sub_lib_no = int_data;
}

void GeneralDataContainer::set_lib_ver( Integer int_data )
{
  lib_ver = int_data;
}

void GeneralDataContainer::set_temp( Real real_data )
{
  temp = real_data;
}

void GeneralDataContainer::set_error_value( Real real_data )
{
  error_value = real_data;
}

void GeneralDataContainer::set_special_derived_mat_flg( Integer int_data )
{
  special_derived_mat_flg = int_data;
}

void GeneralDataContainer::set_brief_explain_word( string str_data )
{
  brief_explain_word = str_data;
}

void GeneralDataContainer::set_evaluated_institute( string str_data )
{
  evaluated_institute = str_data;
}

void GeneralDataContainer::set_evaluated_date( string str_data )
{
  evaluated_date = str_data;
}

void GeneralDataContainer::set_evaluated_author( string str_data )
{
  evaluated_author = str_data;
}

void GeneralDataContainer::set_evaluated_ref( string str_data )
{
  evaluated_ref = str_data;
}

void GeneralDataContainer::set_evaluated_date_ori( string str_data )
{
  evaluated_date_ori = str_data;
}

void GeneralDataContainer::set_evaluated_date_rev( string str_data )
{
  evaluated_date_rev = str_data;
}

void GeneralDataContainer::set_evaluated_date_end( string str_data )
{
  evaluated_date_end = str_data;
}

void GeneralDataContainer::set_evaluated_data_specification( string str_data )
{
  evaluated_data_specification = str_data;
}

void GeneralDataContainer::set_file_section_data_list( vector<vector<Integer> > int_vec )
{
  file_section_data_list = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void GeneralDataContainer::set_comment_data( vector<string> str_vec )
{
  comment_data = str_vec;
  clr_obj.clear_vec_array1_str( str_vec );
}

void GeneralDataContainer::set_state_no_target( Integer int_data )
{
  state_no_target = int_data;
}

void GeneralDataContainer::set_state_no_target_iso( Integer int_data )
{
  state_no_target_iso = int_data;
}

void GeneralDataContainer::set_stability_flg( Integer int_data )
{
  stability_flg = int_data;
}

void GeneralDataContainer::set_half_life( Real real_data )
{
  half_life = real_data;
}

void GeneralDataContainer::set_half_life_uncertainty( Real real_data )
{
  half_life_uncertainty = real_data;
}

void GeneralDataContainer::set_decay_ene( vector<Real> real_vec )
{
  decay_ene = real_vec;
  real_vec.clear();
}

void GeneralDataContainer::set_decay_ene_uncertainty( vector<Real> real_vec )
{
  decay_ene_uncertainty = real_vec;
  real_vec.clear();
}

void GeneralDataContainer::set_spin_target( Real real_data )
{
  spin_target = real_data;
}

void GeneralDataContainer::set_parity_target( Real real_data )
{
  parity_target = real_data;
}

void GeneralDataContainer::set_decay_type( vector<Real> real_vec )
{
  decay_type = real_vec;
  real_vec.clear();
}

void GeneralDataContainer::set_daughter_iso_flg( vector<Real> real_vec )
{
  daughter_iso_flg = real_vec;
  real_vec.clear();
}

void GeneralDataContainer::set_decay_ene_tot( vector<Real> real_vec )
{
  decay_ene_tot = real_vec;
  real_vec.clear();
}

void GeneralDataContainer::set_decay_ene_tot_uncertainty( vector<Real> real_vec )
{
  decay_ene_tot_uncertainty = real_vec;
  real_vec.clear();
}

void GeneralDataContainer::set_branching_ratio( vector<Real> real_vec )
{
  branching_ratio = real_vec;
  real_vec.clear();
}

void GeneralDataContainer::set_branching_ratio_uncertainty( vector<Real> real_vec )
{
  branching_ratio_uncertainty = real_vec;
  real_vec.clear();
}

void GeneralDataContainer::set_radiation_type( vector<Real> real_vec )
{
  radiation_type = real_vec;
  real_vec.clear();
}

void GeneralDataContainer::set_con_spectrum_flg( vector<Integer> int_vec )
{
  con_spectrum_flg = int_vec;
  int_vec.clear();
}

void GeneralDataContainer::set_discrete_spectrum_factor( vector<Real> real_vec )
{
  discrete_spectrum_factor = real_vec;
  real_vec.clear();
}

void GeneralDataContainer::set_discrete_spectrum_factor_uncertainty( vector<Real> real_vec )
{
  discrete_spectrum_factor_uncertainty = real_vec;
  real_vec.clear();
}

void GeneralDataContainer::set_discrete_ene_ave( vector<Real> real_vec )
{
  discrete_ene_ave = real_vec;
  real_vec.clear();
}

void GeneralDataContainer::set_discrete_ene_ave_uncertainty( vector<Real> real_vec )
{
  discrete_ene_ave_uncertainty = real_vec;
  real_vec.clear();
}

void GeneralDataContainer::set_cont_spectrum_factor( vector<Real> real_vec )
{
  cont_spectrum_factor = real_vec;
  real_vec.clear();
}

void GeneralDataContainer::set_cont_spectrum_factor_uncertainty( vector<Real> real_vec )
{
  cont_spectrum_factor_uncertainty = real_vec;
  real_vec.clear();
}

void GeneralDataContainer::set_discrete_ene( vector<vector<Real> > real_vec )
{
  discrete_ene = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void GeneralDataContainer::set_discrete_ene_uncertainty( vector<vector<Real> > real_vec )
{
  discrete_ene_uncertainty = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void GeneralDataContainer::set_discrete_intensity( vector<vector<Real> > real_vec )
{
  discrete_intensity = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void GeneralDataContainer::set_discrete_intensity_uncertainty( vector<vector<Real> > real_vec )
{
  discrete_intensity_uncertainty = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void GeneralDataContainer::set_decay_type_each_ene( vector<vector<Real> > real_vec )
{
  decay_type_each_ene = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void GeneralDataContainer::set_transition_type( vector<vector<Real> > real_vec )
{
  transition_type = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void GeneralDataContainer::set_internal_pair_form_coef( vector<vector<Real> > real_vec )
{
  internal_pair_form_coef = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void GeneralDataContainer::set_internal_pair_form_coef_uncertainty( vector<vector<Real> > real_vec )
{
  internal_pair_form_coef_uncertainty = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void GeneralDataContainer::set_conv_coef_tot( vector<vector<Real> > real_vec )
{
  conv_coef_tot = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void GeneralDataContainer::set_conv_coef_tot_uncertainty( vector<vector<Real> > real_vec )
{
  conv_coef_tot_uncertainty = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void GeneralDataContainer::set_conv_coef_k( vector<vector<Real> > real_vec )
{
  conv_coef_k = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void GeneralDataContainer::set_conv_coef_k_uncertainty( vector<vector<Real> > real_vec )
{
  conv_coef_k_uncertainty = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void GeneralDataContainer::set_conv_coef_l( vector<vector<Real> > real_vec )
{
  conv_coef_l = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void GeneralDataContainer::set_conv_coef_l_uncertainty( vector<vector<Real> > real_vec )
{
  conv_coef_l_uncertainty = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void GeneralDataContainer::set_decay_type_each_rad( vector<Real> real_vec )
{
  decay_type_each_rad = real_vec;
  real_vec.clear();
}

void GeneralDataContainer::set_cont_spectrum_cov_flg( vector<Integer> int_vec )
{
  cont_spectrum_cov_flg = int_vec;
  int_vec.clear();
}

void GeneralDataContainer::set_cont_spectrum_cov_int_data( vector<vector<Integer> > int_vec )
{
  cont_spectrum_cov_int_data = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void GeneralDataContainer::set_cont_spectrum_cov_range_data( vector<vector<Integer> > int_vec )
{
  cont_spectrum_cov_range_data = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void GeneralDataContainer::set_cont_spectrum_cov_ene_data( vector<vector<Real> > real_vec )
{
  cont_spectrum_cov_ene_data = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void GeneralDataContainer::set_cont_spectrum_cov_data( vector<vector<Real> > real_vec )
{
  cont_spectrum_cov_data = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void GeneralDataContainer::set_cont_spectrum_cov_matrix_data_flg( vector<Integer> int_vec )
{
  cont_spectrum_cov_matrix_data_flg = int_vec;
  int_vec.clear();
}

void GeneralDataContainer::set_cont_spectrum_cov_ek_table( vector<vector<Real> > real_vec )
{
  cont_spectrum_cov_ek_table = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void GeneralDataContainer::set_cont_spectrum_cov_fk_table( vector<vector<Real> > real_vec )
{
  cont_spectrum_cov_fk_table = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

Integer GeneralDataContainer::get_izaid_ace()
{
  Integer izaid = static_cast<int>(round(mat_data));

  //Check meta-stable data
  if( iso_state_no > 0 )
  {
    Integer izaid_ori = izaid;
    Integer izaid_add = 300 + iso_state_no * 100;
    izaid += izaid_add;

    Integer awr_id = izaid_ori%1000 + izaid_add;

    string class_name = "GeneralDataContainer";
    string func_name  = "get_izaid_ace()";
    vector<string> err_com;
    if( awr_id < 1000 )
    {
      ostringstream oss01, oss02;
      oss01 << izaid_ori;
      oss02 << izaid;
      string str_data01 = "ZA ID number is changed from " + oss01.str() + " to " + oss02.str() + ".";

      err_com.push_back("This nuclide is meta-stable.");
      err_com.push_back("ZA ID of meta-stable nuclide is changed to distinguish grand state nuclide.");
      err_com.push_back(str_data01);
      err_obj.output_caution(class_name, func_name, err_com);
    }
    else //if( awr_id >= 1000 )
    {
      izaid = izaid_ori;

      err_com.push_back("This nuclide is meta-stable.");
      err_com.push_back("The ZA ID number is identical to grand state nuclide since");
      err_com.push_back("the number of stable state is so large.");
      err_com.push_back("Please modify ZA ID number if you want to distinguish grand state nuclide.");
      err_obj.output_caution(class_name, func_name, err_com);
    }
  }

  return izaid;
}

