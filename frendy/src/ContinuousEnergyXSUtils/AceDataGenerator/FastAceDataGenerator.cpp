#include "ContinuousEnergyXSUtils/AceDataGenerator/FastAceDataGenerator.hpp"

using namespace frendy;

//constructor
FastAceDataGenerator::FastAceDataGenerator(void)
{ 
  clear();
  class_name = "FastAceDataGenerator";
}

//destructor
FastAceDataGenerator::~FastAceDataGenerator(void)
{
  clear();
  class_name.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::clear()
{
  ene_lower_limit = 1.0E-5;
  ene_upper_limit = 2.0E+7;
  angle_err_def   = 1.0E-3;

  react_n_h1_min  = mt_p_min_endf6;
  react_n_h1_max  = mt_p_max_endf6;
  react_n_h2_min  = mt_d_min_endf6;
  react_n_h2_max  = mt_d_max_endf6;
  react_n_h3_min  = mt_t_min_endf6;
  react_n_h3_max  = mt_t_max_endf6;
  react_n_he3_min = mt_he3_min_endf6;
  react_n_he3_max = mt_he3_max_endf6;
  react_n_he4_min = mt_a_min_endf6;
  react_n_he4_max = mt_a_max_endf6;
  react_n_2n_min  = mt_n2n_min_endf6;
  react_n_2n_max  = mt_n2n_max_endf6;

  generate_mode_flg = generate_default_mode;
#ifdef NJOY_MODE
  generate_mode_flg = generate_njoy_mode;
#endif //NJOY_MODE

  integ_obj.set_generate_mode_flg(generate_mode_flg);

  clear_input_data();
  clear_calc_data();
  clear_ace_data();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::clear_input_data()
{
  gen_fast_data_flg = 0;
  nucl_data_set_flg = 0;
  mat_set_flg       = 0;
  temp_set_flg      = 0;

  nucl_data_obj.clear();

  mat                             = 0;
  new_cummulative_angle_distr_flg = 0;
  detailed_photon_flg             = 0;
  temp                            = 0.0;
  thinning_ene.clear();

  zi_vec.clear();
  awr_vec.clear();

  mcnpx_mode_flg = 0;
  discriptive_data.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::clear_calc_data()
{
  fis_data_obj.clear();

  vector<CrossSectionDataContainer>().swap(xs_data_obj_vec);
  vector<EnergyAngularDataContainer>().swap(ene_angle_data_obj_vec);
  vector<ProductDistributionDataContainer>().swap(prod_distr_data_obj_vec);
  vector<PhotonDataContainer>().swap(photon_data_obj_vec);
  //for(int i=0; i<reaction_type_no_int; i++)
  //{
  //  xs_data_obj_vec[i].clear();
  //  ene_angle_data_obj_vec[i].clear();
  //  prod_distr_data_obj_vec[i].clear();
  //  photon_data_obj_vec[i].clear();
  //}
  //xs_data_obj_vec.resize(0);
  //ene_angle_data_obj_vec.resize(0);
  //prod_distr_data_obj_vec.resize(0);
  //photon_data_obj_vec.resize(0);

  reaction_type_no_int = 0;
  reaction_type_list.clear();

  vector<ProductDistributionDataContainer>().swap(prod_distr_data_obj_mod_photon_vec);
  //int i_max = static_cast<int>(prod_distr_data_obj_mod_photon_vec.size());
  //for(int i=0; i<i_max; i++)
  //{
  //  prod_distr_data_obj_mod_photon_vec[i].clear();
  //}
  //prod_distr_data_obj_mod_photon_vec.resize(0);

  mt_16_flg     = 0;
  mt_19_flg     = 0;
  mt_455_flg    = 0;
  mt_103_flg    = 0;
  mt_104_flg    = 0;
  mt_105_flg    = 0;
  mt_106_flg    = 0;
  mt_107_flg    = 0;

  mf_6_data_no  = 0;
  mf_12_data_no = 0;
  mf_13_data_no = 0;
  mf_15_data_no = 0;

  photon_prod_no     = 0;
  redundant_react_no = 0;
  photon_prod_type.clear();
  redundant_react_type.clear();

  sub_lib_part = 0;
  sub_lib_type = 0;
  ene_max      = 0.0;

  union_ene_grid.clear();
  gamma_product_xs.clear();

  clr_obj.clear_vec_array2_int(particle_production_data);
  particle_production_ene_data.clear();

  clr_obj.clear_vec_array2_real(photon_prod_yield_coef_direct);
  clr_obj.clear_vec_array2_real(photon_prod_yield_coef_given);

  photon_xs_ene_min.clear();
  photon_prod_discon_ene_data.clear();

  clr_obj.clear_vec_array2_real(equal_prob_data_ini);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::clear_ace_data()
{
  clear_ace_base_data();
  clear_ace_ene_angular_distr_data();
  clear_ace_prod_distr_data();
  clear_ace_photon_data();
  clear_ace_particle_data();

  clear_ace_pointer_data();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::clear_ace_base_data()
{
  aw0   = 0.0;
  tz    = 0.0;
  izaid = 0;
  clr_obj.clear_vec_array1_str(title_data);

  ntr   = 0;
  nr    = 0;
  mtntr = 0;
  mtnr  = 0;

  nu_bar_repr_flg   = 0;
  nu_d_bar_repr_flg = 0;
  nu_p_bar_repr_flg = 0;

  nu_int_data.clear();
  nu_range_data.clear();
  nu_d_int_data.clear();
  nu_d_range_data.clear();
  nu_p_int_data.clear();
  nu_p_range_data.clear();

  nu_data.clear();
  nu_ene_data.clear();
  nu_d_data.clear();
  nu_d_ene_data.clear();
  nu_p_data.clear();
  nu_p_ene_data.clear();

  react_type_list.clear();
  react_type_flg.clear();
  react_type_ene_sta.clear();
  react_type_list_two_body.clear();
  react_q_value.clear();
  react_xs_tot.clear();
  react_xs_cap.clear();
  react_xs_sc.clear();
  react_xs_heat.clear();
  clr_obj.clear_vec_array2_real(react_xs);

  unreso_prob_tab_int_data           = 0;
  unreso_prob_tab_inela_comp_flg     = 0;
  unreso_prob_tab_abs_comp_flg       = 0;
  unreso_prob_tab_self_shielding_flg = 0;

  unreso_prob_tab_ene.clear();
  clr_obj.clear_vec_array2_real(unreso_prob_tab_heat);
  clr_obj.clear_vec_array2_real(unreso_prob_tab_sample_no);
  clr_obj.clear_vec_array3_real(unreso_prob_tab_table);

  nu_d_ene_min.clear();
  nu_d_ene_max.clear();
  clr_obj.clear_vec_array2_int(nu_d_xs_part_int_data);
  clr_obj.clear_vec_array2_int(nu_d_xs_part_range_data);
  clr_obj.clear_vec_array2_real(nu_d_xs_part_ene_data);
  clr_obj.clear_vec_array2_real(nu_d_xs_part_data);
  clr_obj.clear_vec_array2_int(nu_d_ene_in_int_data);
  clr_obj.clear_vec_array2_int(nu_d_ene_in_range_data);
  clr_obj.clear_vec_array2_int(nu_d_ene_out_int_data);
  clr_obj.clear_vec_array2_real(nu_d_ene_in_data);
  clr_obj.clear_vec_array3_real(nu_d_ene_out_data);
  clr_obj.clear_vec_array3_real(nu_d_ene_distr_data);
  clr_obj.clear_vec_array3_real(nu_d_ene_distr_data_integ);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::clear_ace_ene_angular_distr_data()
{
  angular_distr_type_flg.clear();

  clr_obj.clear_vec_array2_int(angular_distr_int_data);
  clr_obj.clear_vec_array2_real(angular_distr_ene_data);
  clr_obj.clear_vec_array3_real(angular_distr_cos_data);
  clr_obj.clear_vec_array3_real(angular_distr_data);
  clr_obj.clear_vec_array3_real(angular_distr_data_integ);

  clr_obj.clear_vec_array2_int(ene_distr_ene_repr_flg);
  clr_obj.clear_vec_array3_int(ene_distr_xs_part_int_data);
  clr_obj.clear_vec_array3_int(ene_distr_xs_part_range_data);
  clr_obj.clear_vec_array3_real(ene_distr_xs_part_ene_data);
  clr_obj.clear_vec_array3_real(ene_distr_xs_part_data);
  clr_obj.clear_vec_array2_real(ene_distr_q_coef);
  clr_obj.clear_vec_array2_real(ene_distr_mass_coef);
  clr_obj.clear_vec_array3_int(ene_distr_ene_in_int_data);
  clr_obj.clear_vec_array3_int(ene_distr_ene_in_range_data);
  clr_obj.clear_vec_array3_real(ene_distr_ene_in_data);
  clr_obj.clear_vec_array3_int(ene_distr_ene_out_int_data);
  clr_obj.clear_vec_array4_real(ene_distr_ene_out_ene_data);
  clr_obj.clear_vec_array4_real(ene_distr_ene_out_data);
  clr_obj.clear_vec_array4_real(ene_distr_ene_out_data_integ);
  clr_obj.clear_vec_array2_real(ene_distr_upper_ene_limit);
  clr_obj.clear_vec_array3_int(ene_distr_temp_eff_int_data);
  clr_obj.clear_vec_array3_int(ene_distr_temp_eff_range_data);
  clr_obj.clear_vec_array3_int(ene_distr_watt_a_int_data);
  clr_obj.clear_vec_array3_int(ene_distr_watt_a_range_data);
  clr_obj.clear_vec_array3_int(ene_distr_watt_b_int_data);
  clr_obj.clear_vec_array3_int(ene_distr_watt_b_range_data);
  clr_obj.clear_vec_array3_real(ene_distr_temp_eff_ene_data);
  clr_obj.clear_vec_array3_real(ene_distr_temp_eff_data);
  clr_obj.clear_vec_array3_real(ene_distr_watt_a_ene_data);
  clr_obj.clear_vec_array3_real(ene_distr_watt_a_data);
  clr_obj.clear_vec_array3_real(ene_distr_watt_b_ene_data);
  clr_obj.clear_vec_array3_real(ene_distr_watt_b_data);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::clear_ace_prod_distr_data()
{
  clr_obj.clear_vec_array2_int(prod_yield_tot_int_data);
  clr_obj.clear_vec_array2_int(prod_yield_tot_range_data);
  clr_obj.clear_vec_array2_real(prod_yield_tot_ene_data);
  clr_obj.clear_vec_array2_real(prod_yield_tot_data);
  clr_obj.clear_vec_array2_int(prod_distr_func_flg);
  clr_obj.clear_vec_array2_real(prod_distr_n_body_mass);
  clr_obj.clear_vec_array2_int(prod_distr_prob_data_no);
  clr_obj.clear_vec_array2_int(prod_distr_n_body_particle_no);
  clr_obj.clear_vec_array3_int(prod_distr_prob_ene_in_int_data);
  clr_obj.clear_vec_array3_int(prod_distr_prob_ene_in_range_data);
  clr_obj.clear_vec_array3_int(prod_distr_prob_ene_out_int_data);
  clr_obj.clear_vec_array3_real(prod_distr_prob_ene_in_data);
  clr_obj.clear_vec_array4_int(prod_distr_prob_mu_int_data);
  clr_obj.clear_vec_array4_int(prod_distr_prob_mu_range_data);
  clr_obj.clear_vec_array4_real(prod_distr_prob_mu_data);
  clr_obj.clear_vec_array4_real(prod_distr_prob_mu_data_integ);
  clr_obj.clear_vec_array4_real(prod_distr_prob_data);
  clr_obj.clear_vec_array4_real(prod_distr_prob_data_integ);
  clr_obj.clear_vec_array4_real(prod_distr_prob_ene_out_data);
  clr_obj.clear_vec_array4_real(prod_distr_prob_coef_a);
  clr_obj.clear_vec_array4_real(prod_distr_prob_coef_b);
  clr_obj.clear_vec_array5_int(prod_distr_prob_int_vec);
  clr_obj.clear_vec_array5_int(prod_distr_prob_range_vec);
  clr_obj.clear_vec_array5_real(prod_distr_prob_mu_vec);
  clr_obj.clear_vec_array5_real(prod_distr_prob_ene_out_vec);
  clr_obj.clear_vec_array5_real(prod_distr_prob_vec);
  clr_obj.clear_vec_array5_real(prod_distr_prob_vec_integ);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::clear_ace_photon_data()
{
  photon_prod_file_no.clear();
  photon_prod_reaction_type.clear();
  photon_prod_reaction_type_without_xs.clear();
  photon_prod_reaction_type_all.clear();
  photon_prod_binding_ene.clear();
  clr_obj.clear_vec_array2_int(photon_prod_multiplicity_int_data);
  clr_obj.clear_vec_array2_int(photon_prod_multiplicity_range_data);
  clr_obj.clear_vec_array2_real(photon_prod_multiplicity_ene_data);
  clr_obj.clear_vec_array2_real(photon_prod_multiplicity_data);
  photon_prod_xs_ene_no.clear();
  clr_obj.clear_vec_array2_int(photon_prod_xs_non_zero_pos);
  clr_obj.clear_vec_array2_real(photon_prod_xs_data);
  clr_obj.clear_vec_array2_int(photon_prod_distr_int_data);
  clr_obj.clear_vec_array2_int(photon_prod_distr_range_data);
  clr_obj.clear_vec_array2_real(photon_prod_distr_ene_data);
  clr_obj.clear_vec_array2_real(photon_prod_distr_data);

  clr_obj.clear_vec_array2_real(photon_angular_distr_ene_data);
  clr_obj.clear_vec_array3_real(photon_angular_distr_prob_cos_data);

  photon_energy_distr_flg.clear();
  photon_energy_distr_ene_flg.clear();
  photon_energy_distr_binding_ene_data.clear();
  clr_obj.clear_vec_array2_int(photon_energy_distr_int_data);
  clr_obj.clear_vec_array2_int(photon_energy_distr_range_data);
  clr_obj.clear_vec_array2_real(photon_energy_distr_ene_data);
  clr_obj.clear_vec_array2_real(photon_energy_distr_prob_data);
  clr_obj.clear_vec_array2_int(photon_energy_distr_ene_in_int_data);
  clr_obj.clear_vec_array2_int(photon_energy_distr_ene_in_range_data);
  clr_obj.clear_vec_array2_real(photon_energy_distr_ene_in_data);
  clr_obj.clear_vec_array2_int(photon_energy_distr_weight_int_data);
  clr_obj.clear_vec_array3_real(photon_energy_distr_weight_ene_data);
  clr_obj.clear_vec_array3_real(photon_energy_distr_weight_data);
  clr_obj.clear_vec_array3_real(photon_energy_distr_weight_data_integ);
  photon_energy_distr_gamma_mass_product.clear();
  
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::clear_ace_particle_data()
{
  particle_prod_flg.clear();
  particle_prod_count.clear();
  particle_prod_ene_sta.clear();
  particle_prod_ene_no.clear();
  clr_obj.clear_vec_array2_int(particle_prod_file_no);
  clr_obj.clear_vec_array2_int(particle_prod_frame_flg);
  clr_obj.clear_vec_array2_int(particle_prod_reaction_type);
  clr_obj.clear_vec_array2_int(particle_prod_reaction_type_all);
  particle_prod_xs_each_emin.clear();
  clr_obj.clear_vec_array2_real(particle_prod_xs);
  clr_obj.clear_vec_array2_real(particle_prod_xs_each);
  clr_obj.clear_vec_array2_real(particle_prod_heat);
  clr_obj.clear_vec_array3_int(particle_prod_distr_int_data);
  clr_obj.clear_vec_array3_int(particle_prod_distr_range_data);
  clr_obj.clear_vec_array3_real(particle_prod_distr_ene_data);
  clr_obj.clear_vec_array3_real(particle_prod_distr_data);
  clr_obj.clear_vec_array3_int(particle_prod_angular_int_data);
  clr_obj.clear_vec_array3_real(particle_prod_angular_ene_data);
  clr_obj.clear_vec_array4_real(particle_prod_angular_cos_data);
  clr_obj.clear_vec_array4_real(particle_prod_angular_distr_data);
  clr_obj.clear_vec_array4_real(particle_prod_angular_distr_data_integ);


  clr_obj.clear_vec_array2_int(particle_prod_ene_flg);
  clr_obj.clear_vec_array2_real(particle_prod_q_value);
  clr_obj.clear_vec_array2_real(particle_prod_mass_coef);
  clr_obj.clear_vec_array3_int(particle_prod_ene_int_data);
  clr_obj.clear_vec_array3_int(particle_prod_ene_range_data);
  clr_obj.clear_vec_array3_real(particle_prod_ene_data);
  clr_obj.clear_vec_array3_real(particle_prod_ene_prob_data);

  clr_obj.clear_vec_array3_int(particle_prod_ene_in_int_data);
  clr_obj.clear_vec_array3_int(particle_prod_ene_in_range_data);
  clr_obj.clear_vec_array3_real(particle_prod_ene_in_data);
  clr_obj.clear_vec_array3_int(particle_prod_a_int_data);
  clr_obj.clear_vec_array4_real(particle_prod_a_data);
  clr_obj.clear_vec_array4_real(particle_prod_a_distr_data);
  clr_obj.clear_vec_array4_real(particle_prod_a_distr_data_integ);
  clr_obj.clear_vec_array4_real(particle_prod_ene_out_coef_a);
  clr_obj.clear_vec_array4_real(particle_prod_ene_out_coef_b);

  clr_obj.clear_vec_array4_int(particle_prod_b_int_data);
  clr_obj.clear_vec_array5_real(particle_prod_b_data);
  clr_obj.clear_vec_array5_real(particle_prod_b_prob_data);
  clr_obj.clear_vec_array5_real(particle_prod_b_prob_data_integ);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::clear_ace_pointer_data()
{
  len2  = 0;
  nes   = 0;
  ntrp  = 0;
  ntype = 0;
  ndnf  = 0;
  esz   = 0;
  nu    = 0;
  mtr   = 0;
  lqr   = 0;
  tyr   = 0;
  lsig  = 0;
  sig   = 0;
  land  = 0;
  andi  = 0;
  ldlw  = 0;
  dlw   = 0;
  gpd   = 0;
  mtrp  = 0;
  lsigp = 0;
  sigp  = 0;
  landp = 0;
  andp  = 0;
  ldlwp = 0;
  dlwp  = 0;
  yp    = 0;
  fis   = 0;
  endi  = 0;
  iurpt = 0;
  nud   = 0;
  dndat = 0;
  ldnd  = 0;
  dnd   = 0;
  ptype = 0;
  ntro  = 0;
  ploct = 0;

  ene_distr_pointer.clear();
  nu_d_pointer.clear();
  photon_prod_pointer.clear();
  photon_angular_pointer.clear();
  photon_ene_pointer.clear();
  photon_ene_distr_pointer.clear();

  clr_obj.clear_vec_array2_int(angular_distr_pointer);
  clr_obj.clear_vec_array2_int(ene_distr_ene_repr_end_pointer);
  clr_obj.clear_vec_array2_int(ene_distr_ene_repr_pointer);
  clr_obj.clear_vec_array2_int(nu_d_ene_in_pointer);
  clr_obj.clear_vec_array2_int(photon_angular_ene_pointer);
  clr_obj.clear_vec_array2_int(photon_ene_weight_pointer);
  clr_obj.clear_vec_array2_int(particle_prod_pointer);
  clr_obj.clear_vec_array2_int(particle_prod_distr_pointer);
  clr_obj.clear_vec_array2_int(particle_prod_angular_pointer);
  clr_obj.clear_vec_array2_int(particle_prod_ene_pointer);
  clr_obj.clear_vec_array2_int(particle_prod_ene_in_pointer);
  clr_obj.clear_vec_array3_int(ene_distr_ene_in_pointer);
  clr_obj.clear_vec_array3_int(particle_prod_angular_ene_pointer);
  clr_obj.clear_vec_array3_int(particle_prod_a_pointer);
  clr_obj.clear_vec_array4_int(ene_distr_ene_out_pointer);
  clr_obj.clear_vec_array4_int(particle_prod_b_pointer);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::generate_ace_data()
{
  if( gen_fast_data_flg != 0 )
  {
    return;
  }
  gen_fast_data_flg = 1;

  clear_calc_data();
  check_set_data();

  set_general_data();

  linearize_number_of_neutrons_per_fission();

  modify_photon_production_data();
  modify_photon_production_data_in_product_distr_data();

  modify_xs_data();

  modify_prod_distribution_data();

  if( photon_prod_no != 0 )
  {
    calc_total_gamma_product_xs();

    calc_multigroup_photon_data();
  }

  generate_fast_ace_data_from_modified_nucl_data_obj();

  calc_ace_header_file_data();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_general_data()
{
  reaction_type_list      = nucl_data_obj.get_nucl_reaction_data_obj().get_reaction_type();
  reaction_type_no_int    = static_cast<int>(reaction_type_list.size());

  fis_data_obj            = nucl_data_obj.get_fis_data_obj();
  xs_data_obj_vec         = nucl_data_obj.get_nucl_reaction_data_obj().get_xs_data_obj();
  ene_angle_data_obj_vec  = nucl_data_obj.get_nucl_reaction_data_obj().get_ene_angular_data_obj();
  prod_distr_data_obj_vec = nucl_data_obj.get_nucl_reaction_data_obj().get_product_distr_data_obj();
  photon_data_obj_vec     = nucl_data_obj.get_nucl_reaction_data_obj().get_photon_data_obj();

  sub_lib_part  = nucl_data_obj.get_general_data_obj().get_sub_lib_no();
  sub_lib_type  = sub_lib_part%10;
  sub_lib_part /= 10;

  if( sub_lib_part != 1 )
  {
    string func_name  = "read_general_data()";

    ostringstream oss01, oss02;
    oss01 << sub_lib_part;
    oss02 << sub_lib_type;
    string str_data01 = "Sub-library name (IPART) : " + oss01.str();
    string str_data02 = "Sub-library name (ITYPE) : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("The sub-library name (IPART) is not equal to 1.");
    err_com.push_back("This neutron data may not be appropriate.");
    err_obj.output_caution(class_name, func_name, err_com);
  }

  react_n_h1_min  = mt_p_min_endf6;
  react_n_h1_max  = mt_p_max_endf6;
  react_n_h2_min  = mt_d_min_endf6;
  react_n_h2_max  = mt_d_max_endf6;
  react_n_h3_min  = mt_t_min_endf6;
  react_n_h3_max  = mt_t_max_endf6;
  react_n_he3_min = mt_he3_min_endf6;
  react_n_he3_max = mt_he3_max_endf6;
  react_n_he4_min = mt_a_min_endf6;
  react_n_he4_max = mt_a_max_endf6;
  react_n_2n_min  = mt_n2n_min_endf6;
  react_n_2n_max  = mt_n2n_max_endf6;

  if( nucl_data_obj.get_general_data_obj().get_lib_format() < 6 ) //For ENDF-5 format
  {
    string class_name = "FastAceDataGenerator";
    string func_name  = "set_general_data";

    ostringstream oss01;
    oss01 << nucl_data_obj.get_general_data_obj().get_lib_format();
    string str_data01 = "Library format for original nuclear data : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("The library format is not equal to 6.");
    err_com.push_back("MT number of (n,p), (n,d), (n,t), (n,He3), and (n,alpha) are modified");
    err_com.push_back("from MT=600-849 to MT=700-799.");
    err_com.push_back("This modification affects the processing results and the processing");
    err_com.push_back("results may be incorrect.");
    err_com.push_back("Please check the processing results.");
    err_obj.output_caution(class_name, func_name, err_com);

    react_n_h1_min  = mt_p_min_endf5;
    react_n_h1_max  = mt_p_max_endf5;
    react_n_h2_min  = mt_d_min_endf5;
    react_n_h2_max  = mt_d_max_endf5;
    react_n_h3_min  = mt_t_min_endf5;
    react_n_h3_max  = mt_t_max_endf5;
    react_n_he3_min = mt_he3_min_endf5;
    react_n_he3_max = mt_he3_max_endf5;
    react_n_he4_min = mt_a_min_endf5;
    react_n_he4_max = mt_a_max_endf5;
    react_n_2n_min  = mt_n2n_min_endf5;
    react_n_2n_max  = mt_n2n_max_endf5;
  }

  check_reaction_type();

  ene_max = nucl_data_obj.get_general_data_obj().get_upper_ene_limit();
  if( ene_max < ene_upper_limit )
  {
    ene_max = ene_upper_limit;
  }

  //Modify energy limit (upper/lower)
  ene_upper_limit = ene_max;
  ene_lower_limit = 1.0E-5;
  vector<Real> ene_vec =  nucl_data_obj.get_nucl_reaction_data_obj().get_xs_data_obj(1).get_xs_ene_data();
  if( static_cast<int>(ene_vec.size()) > 0 )
  {
    if( ene_lower_limit > ene_vec[0] )
    {
      ene_lower_limit = ene_vec[0];
    }
  }
  ene_vec.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::check_reaction_type()
{
  for(int i=0; i<reaction_type_no_int; i++)
  {
    Integer react_val = reaction_type_list[i];
    check_mt_flg(i, react_val);
    check_mf_flg(i, react_val);
  }

  particle_production_ene_data.resize(particle_production_ene_data_no);
  for(int i=0; i<particle_production_ene_data_no; i++)
  {
    particle_production_ene_data[i] = 1.0E10;
  }

  if( new_cummulative_angle_distr_flg != 0 )
  {
    for(int i=0; i<reaction_type_no_int; i++)
    {
      check_particle_production_xs(i, reaction_type_list[i]);
    }

    for(int i=0; i<reaction_type_no_int; i++)
    {
      check_particle_production_prod_distr(i, reaction_type_list[i]);
    }

    sort_particle_production();
    delete_overlap_particle_production();
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::check_mt_flg(int i, Integer react_val)
{
  if( react_val >= 875 && react_val <= 891 )
  {
    mt_16_flg = 1;
  }

  if( react_val == 19 )
  {
    if( ene_angle_data_obj_vec[i].get_reaction_type() == react_val )
    {
      mt_19_flg = 1;
    }
  }

  if( react_val == 455 )
  {
    if( ene_angle_data_obj_vec[i].get_reaction_type() == react_val )
    {
      if( static_cast<int>(ene_angle_data_obj_vec[i].get_ene_repr_flg().size()) > 0 )
      {
        mt_455_flg = 1;
      }
    }
  }

  if( react_val < 5 || react_val == 13 )
  {
    if( photon_data_obj_vec[i].get_reaction_type() == react_val )
    {
      if( static_cast<int>(photon_data_obj_vec[i].get_multiplicity_ene_level().size()) > 0 ||
          static_cast<int>(photon_data_obj_vec[i].get_trans_ene_level().size()) > 0 )
      {
        redundant_react_no++;
        redundant_react_type.push_back(react_val);
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::check_mf_flg(int i, Integer react_val)
{
  if( detailed_photon_flg != 0 )
  {
    if( photon_data_obj_vec[i].get_reaction_type() == react_val )
    {
      if( static_cast<int>(photon_data_obj_vec[i].get_multiplicity_ene_level().size()) > 0 ||
          static_cast<int>(photon_data_obj_vec[i].get_trans_ene_level().size()) > 0 )
      {
        mf_12_data_no++;
        if( react_val != 460 )
        {
          photon_prod_no++;
          photon_prod_type.push_back(12000 + react_val);
        }
      }
      if( static_cast<int>(photon_data_obj_vec[i].get_photon_ene().size()) > 0 )
      {
        mf_13_data_no++;
        photon_prod_no++;
        photon_prod_type.push_back(13000 + react_val);
      }
      if( static_cast<int>(photon_data_obj_vec[i].get_ene_distr_law_no().size()) > 0 )
      {
        mf_15_data_no++;
      }
    }
  }

  if( prod_distr_data_obj_vec[i].get_reaction_type() == react_val )
  {
    if( static_cast<int>(prod_distr_data_obj_vec[i].get_mat_data_product().size()) > 0 )
    {
      photon_prod_no++;
      mf_6_data_no++;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::check_particle_production_xs(int i, Integer react_val)
{
  Integer mf_flg      = 0;
  Integer sub_lib_mod = sub_lib_part
                      + static_cast<Integer>(round(nucl_data_obj.get_general_data_obj().get_mat_data()));

  if( react_val == 102 && sub_lib_part == 1 && sub_lib_mod <= 2004 )
  {
    if( xs_data_obj_vec[i].get_reaction_type() == react_val )
    {
      mf_flg = 3;
    }
  }
  else if( react_val == 2 || ( react_val >= react_n_h1_min && react_val < react_n_he4_max ) )
  {
    if( react_val != react_n_h1_max && react_val != react_n_h2_max &&
        react_val != react_n_h3_max && react_val != react_n_he3_max )
    {
      if( ene_angle_data_obj_vec[i].get_reaction_type() == react_val )
      {
        if( ene_angle_data_obj_vec[i].get_ref_frame_flg() > 0 )
        {
          mf_flg = 4;
        }
      }
    }
  }

  if( mf_flg != 0 )
  {
    Integer mt_flg01 = 0;
    Integer mt_flg02 = 0;
    Integer mt_flg03 = 0;
    Integer mt_flg04 = 0;
    Integer mt_flg05 = 0;

    if( react_val == 2 )
    {
      sub_lib_mod -= sub_lib_part;
    }
    else if( react_val >= react_n_h1_min && react_val <= react_n_h1_max )
    {
      sub_lib_mod -= 1001;
      mt_flg01     = 1;
    }
    else if( react_val >= react_n_h2_min && react_val <= react_n_h2_max )
    {
      sub_lib_mod -= 1002;
      mt_flg02     = 1;
    }
    else if( react_val >= react_n_h3_min && react_val <= react_n_h3_max )
    {
      sub_lib_mod -= 1003;
      mt_flg03     = 1;
    }
    else if( react_val >= react_n_he3_min && react_val <= react_n_he3_max )
    {
      sub_lib_mod -= 2003;
      mt_flg04     = 1;
    }
    else if( react_val >= react_n_he4_min && react_val <= react_n_he4_max )
    {
      sub_lib_mod -= 2004;
      mt_flg05     = 1;
    }

    Real ene_data_min = 1.0E10;
    if( static_cast<int>(xs_data_obj_vec[i].get_xs_ene_data().size()) > 0 )
    {
      ene_data_min = xs_data_obj_vec[i].get_xs_ene_data()[0];
    }

    vector<Integer> particle_prod_tmp;
    particle_prod_tmp.resize(particle_production_data_no);
    particle_prod_tmp[particle_production_reaction_type] = react_val;
    particle_prod_tmp[particle_production_file_no]       = mf_flg;
    particle_prod_tmp[particle_production_type]          = 0;
    if( (mt_flg01 > 0 || sub_lib_mod == 1001) && sub_lib_part != 1001 )
    {
      particle_prod_tmp[particle_production_sub_lib_no] = 1001;
      particle_production_data.push_back(particle_prod_tmp);

      if( react_val > 2 && ene_data_min < particle_production_ene_data[1] )
      {
        particle_production_ene_data[1] = ene_data_min;
      }
    }
    else if( (mt_flg02 > 0 || sub_lib_mod == 1002) && sub_lib_part != 1002 )
    {
      particle_prod_tmp[particle_production_sub_lib_no] = 1002;
      particle_production_data.push_back(particle_prod_tmp);

      if( react_val > 2 && ene_data_min < particle_production_ene_data[2] )
      {
        particle_production_ene_data[2] = ene_data_min;
      }
    }
    else if( (mt_flg03 > 0 || sub_lib_mod == 1003) && sub_lib_part != 1003 )
    {
      particle_prod_tmp[particle_production_sub_lib_no] = 1003;
      particle_production_data.push_back(particle_prod_tmp);

      if( react_val > 2 && ene_data_min < particle_production_ene_data[3] )
      {
        particle_production_ene_data[3] = ene_data_min;
      }
    }
    else if( (mt_flg04 > 0 || sub_lib_mod == 2003) && sub_lib_part != 2003 )
    {
      particle_prod_tmp[particle_production_sub_lib_no] = 2003;
      particle_production_data.push_back(particle_prod_tmp);

      if( react_val > 2 && ene_data_min < particle_production_ene_data[4] )
      {
        particle_production_ene_data[4] = ene_data_min;
      }
    }
    else if( (mt_flg05 > 0 || sub_lib_mod == 2004 || sub_lib_mod == 4008) && sub_lib_part != 2004 )
    {
      particle_prod_tmp[particle_production_sub_lib_no] = 2004;
      particle_production_data.push_back(particle_prod_tmp);

      if( react_val > 2 && ene_data_min < particle_production_ene_data[5] )
      {
        particle_production_ene_data[5] = ene_data_min;
      }
    }
    particle_prod_tmp.clear();
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::check_particle_production_prod_distr(int i, Integer react_val)
{
  if( prod_distr_data_obj_vec[i].get_reaction_type() == react_val )
  {
    Real xs_ene_data_min = 0.0;
    if( static_cast<int>(xs_data_obj_vec[i].get_xs_ene_data().size()) > 0 )
    {
      xs_ene_data_min = xs_data_obj_vec[i].get_xs_ene_data()[0];
    }

    Integer               distr_func_check_flg = 0;
    vector<Integer>       distr_func_flg       = prod_distr_data_obj_vec[i].get_distr_func_flg();
    vector<Real>          mat_data_prod        = prod_distr_data_obj_vec[i].get_mat_data_product();
    vector<vector<Real> > prod_distr_ene_data  = prod_distr_data_obj_vec[i].get_product_distr_ene_data();
    //vector<vector<Real> > prod_distr_data      = prod_distr_data_obj_vec[i].get_product_distr_data();
    int i_max = static_cast<int>(distr_func_flg.size());
    for(int i=0; i<i_max; i++)
    {
      if( distr_func_check_flg == 0 )
      {
        if( distr_func_flg[i] == 2 || distr_func_flg[i] == 3 )
        {
          react_type_list_two_body.push_back(react_val);
          distr_func_check_flg = 1;
        }
      }

      Real ene_thresh = prod_distr_ene_data[i][0];
      if( xs_ene_data_min > ene_thresh )
      {
        ene_thresh = xs_ene_data_min;
      }

      Integer mat_data_prod_int = static_cast<Integer>(round(mat_data_prod[i]));

      vector<Integer> particle_prod_tmp;
      particle_prod_tmp.resize(particle_production_data_no);
      particle_prod_tmp[particle_production_reaction_type] = react_val;
      particle_prod_tmp[particle_production_file_no]       = 6;
      particle_prod_tmp[particle_production_type]          = i+1;

      if( mat_data_prod_int == 1 && sub_lib_part != 1 )
      {
        particle_prod_tmp[particle_production_sub_lib_no] = 1;
        if( check_particle_production_data(particle_prod_tmp) == 0 )
        {
          particle_production_data.push_back(particle_prod_tmp);
        }

        if( ene_thresh < particle_production_ene_data[0] )
        {
          particle_production_ene_data[0] = ene_thresh;
        }
      }
      else if( mat_data_prod_int == 1001 && sub_lib_part != 1001 )
      {
        particle_prod_tmp[particle_production_sub_lib_no] = 1001;
        if( check_particle_production_data(particle_prod_tmp) == 0 )
        {
          particle_production_data.push_back(particle_prod_tmp);
        }

        if( ene_thresh < particle_production_ene_data[1] )
        {
          particle_production_ene_data[1] = ene_thresh;
        }
      }
      else if( mat_data_prod_int == 1002 && sub_lib_part != 1002 )
      {
        particle_prod_tmp[particle_production_sub_lib_no] = 1002;
        if( check_particle_production_data(particle_prod_tmp) == 0 )
        {
          particle_production_data.push_back(particle_prod_tmp);
        }

        if( ene_thresh < particle_production_ene_data[2] )
        {
          particle_production_ene_data[2] = ene_thresh;
        }
      }
      else if( mat_data_prod_int == 1003 && sub_lib_part != 1003 )
      {
        particle_prod_tmp[particle_production_sub_lib_no] = 1003;
        if( check_particle_production_data(particle_prod_tmp) == 0 )
        {
          particle_production_data.push_back(particle_prod_tmp);
        }

        if( ene_thresh < particle_production_ene_data[3] )
        {
          particle_production_ene_data[3] = ene_thresh;
        }
      }
      else if( mat_data_prod_int == 2003 && sub_lib_part != 2003 )
      {
        particle_prod_tmp[particle_production_sub_lib_no] = 2003;
        if( check_particle_production_data(particle_prod_tmp) == 0 )
        {
          particle_production_data.push_back(particle_prod_tmp);
        }

        if( ene_thresh < particle_production_ene_data[4] )
        {
          particle_production_ene_data[4] = ene_thresh;
        }
      }
      else if( mat_data_prod_int == 2004 && sub_lib_part != 2004 )
      {
        particle_prod_tmp[particle_production_sub_lib_no] = 2004;
        if( check_particle_production_data(particle_prod_tmp) == 0 )
        {
          particle_production_data.push_back(particle_prod_tmp);
        }

        if( ene_thresh < particle_production_ene_data[5] )
        {
          particle_production_ene_data[5] = ene_thresh;
        }
      }
      particle_prod_tmp.clear();
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Integer FastAceDataGenerator::check_particle_production_data(vector<Integer> particle_prod_tmp)
{
  Integer add_particle_pruduction_data_flg = 0; //add particle_production_data

  Integer react_type = particle_prod_tmp[particle_production_reaction_type];
  Integer sub_lib_no = particle_prod_tmp[particle_production_sub_lib_no];
  Integer file_no    = particle_prod_tmp[particle_production_file_no];

  int i_max = static_cast<int>(particle_production_data.size());
  for(int i=0; i<i_max; i++)
  {
    if( particle_production_data[i][particle_production_reaction_type] == react_type &&
        particle_production_data[i][particle_production_sub_lib_no]    == sub_lib_no &&
        particle_production_data[i][particle_production_file_no]       != file_no    )
    {
      add_particle_pruduction_data_flg = 1; //skip add particle_production_data
    }
  }

  return add_particle_pruduction_data_flg;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::sort_particle_production()
{
  vector<Integer> mt_list_ori, mt_list_mod;

  int i_max = static_cast<int>(particle_production_data.size());
  mt_list_ori.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    mt_list_ori[i] = 100000 * particle_production_data[i][particle_production_reaction_type]
                   +     10 * particle_production_data[i][particle_production_sub_lib_no]
                   +          particle_production_data[i][particle_production_type];
  }

  mt_list_mod = mt_list_ori;
  sort(mt_list_mod.begin(), mt_list_mod.end());

  vector<vector<Integer> > particle_prod_data_mod;
  particle_prod_data_mod.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    Integer mt_val = mt_list_mod[i];
    for(int j=0; j<i_max; j++)
    {
      if( mt_val == mt_list_ori[j] )
      {
        particle_prod_data_mod[i] = particle_production_data[j];
      }
    }
  }

  particle_production_data = particle_prod_data_mod;

  clr_obj.clear_vec_array2_int(particle_prod_data_mod);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::delete_overlap_particle_production()
{
  Integer overlap_flg = 0;

  int i_max = static_cast<int>(particle_production_data.size());
  for(int i=0; i<i_max; i++)
  {
    if( particle_production_data[i][particle_production_file_no] == 6 )
    {
      overlap_flg = 1;
      break;
    }
  }

  if( overlap_flg == 0 )
  {
    return;
  }

  vector<vector<Integer> > particle_prod_data_mod;
  particle_prod_data_mod.push_back(particle_production_data[0]);
  for(int i=1; i<i_max; i++)
  {
    if( particle_production_data[i][particle_production_reaction_type]
          == particle_production_data[i-1][particle_production_reaction_type]
     && particle_production_data[i][particle_production_sub_lib_no]
          == particle_production_data[i-1][particle_production_sub_lib_no]
     && particle_production_data[i][particle_production_file_no]
          != particle_production_data[i-1][particle_production_file_no] )
    {
      continue;
    }
    else
    {
      particle_prod_data_mod.push_back(particle_production_data[i]);
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::linearize_number_of_neutrons_per_fission()
{
  vector<Integer> nu_int_data, nu_range_data;
  vector<Real>    nu_ene_data, nu_data;
  Real            error_relative = angle_err_def;
  Real            error_min      = angle_err_def * 1.0E-3;

  if( fis_data_obj.get_nu_bar_repr_flg() == 2 )
  {
    nu_int_data   = fis_data_obj.get_nu_bar_int_data();
    nu_range_data = fis_data_obj.get_nu_bar_range_data();
    nu_ene_data   = fis_data_obj.get_nu_bar_ene_data();
    nu_data       = fis_data_obj.get_nu_bar_data();

    lin_tab_obj.linearize_tab1_data(nu_range_data,  nu_int_data, nu_ene_data, nu_data,
                                    error_relative, error_min);

    fis_data_obj.set_nu_bar_int_data(nu_int_data);
    fis_data_obj.set_nu_bar_range_data(nu_range_data);
    fis_data_obj.set_nu_bar_ene_data(nu_ene_data);
    fis_data_obj.set_nu_bar_data(nu_data);
  }

  if( fis_data_obj.get_nu_d_bar_repr_flg() == 2 )
  {
    nu_int_data   = fis_data_obj.get_nu_d_bar_int_data();
    nu_range_data = fis_data_obj.get_nu_d_bar_range_data();
    nu_ene_data   = fis_data_obj.get_nu_d_bar_ene_data();
    nu_data       = fis_data_obj.get_nu_d_bar_data();

    lin_tab_obj.linearize_tab1_data(nu_range_data,  nu_int_data, nu_ene_data, nu_data,
                                    error_relative, error_min);

    fis_data_obj.set_nu_d_bar_int_data(nu_int_data);
    fis_data_obj.set_nu_d_bar_range_data(nu_range_data);
    fis_data_obj.set_nu_d_bar_ene_data(nu_ene_data);
    fis_data_obj.set_nu_d_bar_data(nu_data);
  }

  if( fis_data_obj.get_nu_p_bar_repr_flg() == 2 )
  {
    nu_int_data   = fis_data_obj.get_nu_p_bar_int_data();
    nu_range_data = fis_data_obj.get_nu_p_bar_range_data();
    nu_ene_data   = fis_data_obj.get_nu_p_bar_ene_data();
    nu_data       = fis_data_obj.get_nu_p_bar_data();

    lin_tab_obj.linearize_tab1_data(nu_range_data,  nu_int_data, nu_ene_data, nu_data,
                                    error_relative, error_min);

    fis_data_obj.set_nu_p_bar_int_data(nu_int_data);
    fis_data_obj.set_nu_p_bar_range_data(nu_range_data);
    fis_data_obj.set_nu_p_bar_ene_data(nu_ene_data);
    fis_data_obj.set_nu_p_bar_data(nu_data);
  }

  nu_int_data.clear();
  nu_range_data.clear();
  nu_ene_data.clear();
  nu_data.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::modify_photon_production_data()
{
  if( mf_12_data_no == 0 && mf_13_data_no == 0 )
  {
    return;
  }

  check_photon_data_reaction_type_list();

  vector<Real> ene_vec;
  Integer react_type_pre = 0;
  Integer trans_prog_flg = 0;
  int     i_max          = static_cast<int>(photon_data_obj_vec.size());
  if( mf_12_data_no > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      if( reaction_type_list[i] != 460 && photon_data_obj_vec[i].get_reaction_type() == reaction_type_list[i] )
      {
        if( static_cast<int>(photon_data_obj_vec[i].get_multiplicity_ene_level().size()) > 0 )
        {
          adjust_photon_production_ene_data(i);
        }
        else if( static_cast<int>(photon_data_obj_vec[i].get_trans_ene_level().size()) > 0 )
        {
          trans_prog_flg = 1;
          modify_transition_probability_array(i, react_type_pre, ene_vec);
        }
      }
    }
  }
  else
  { 
    for(int i=0; i<i_max; i++)
    {
      if( photon_data_obj_vec[i].get_reaction_type() == reaction_type_list[i] )
      {
        if( static_cast<int>(photon_data_obj_vec[i].get_photon_ene().size()) > 0 )
        {
          adjust_photon_production_ene_data(i);
        }
      }
    }
  }

  if( trans_prog_flg == 1 )
  {
    for(int i=0; i<i_max; i++)
    {
      Integer react_val = reaction_type_list[i];
      if( reaction_type_list[i] != 460 && photon_data_obj_vec[i].get_reaction_type() == react_val )
      {
        if( static_cast<int>(photon_data_obj_vec[i].get_angular_ene_level().size()) > 0 )
        {
          modify_photon_angular_distribution_data_obj(i);
        }
      }
    }
  }

  ta_obj.delete_overlap_grid(photon_xs_ene_min);
  ta_obj.delete_overlap_grid(photon_prod_discon_ene_data);

  i_max = static_cast<int>(photon_prod_discon_ene_data.size());
  if( i_max > 0 )
  {
    cout << "Energy discontinuities found in gamma files" << endl;
    for(int i=0; i<i_max; i++)
    {
      cout << "          " << i+1 << " / " << i_max << " : " << photon_prod_discon_ene_data[i] << endl;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::check_photon_data_reaction_type_list()
{
  if( mf_12_data_no == 0 )
  {
    return;
  }

  int i_max = 50;
  photon_prod_yield_coef_direct.resize(i_max);
  photon_prod_yield_coef_given.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    photon_prod_yield_coef_direct[i].resize(i_max);
    photon_prod_yield_coef_given[i].resize(i_max);
    for(int j=0; j<i_max; j++)
    {
      photon_prod_yield_coef_direct[i][j] = 0.0;
      photon_prod_yield_coef_given[i][j]  = 0.0;
    }
    photon_prod_yield_coef_given[i][i] = 1.0;
  }

          i_max  = static_cast<int>(photon_data_obj_vec.size());
  Integer mt_cur = 0;
  for(int i=0; i<i_max; i++)
  {
    Integer react_val = reaction_type_list[i];
    if( photon_data_obj_vec[i].get_reaction_type() == react_val )
    {
      if( static_cast<int>(photon_data_obj_vec[i].get_multiplicity_ene_level().size()) > 0 ||
          static_cast<int>(photon_data_obj_vec[i].get_trans_ene_level().size()) > 0 )
      {
        if( react_val ==  51 || react_val == 601 || react_val == 651 || react_val == 701 ||
            react_val == 751 || react_val == 801 || react_val == 876 )
        {
          mt_cur = react_val;
        }
        else if( (react_val >  51 && react_val <  91)
              || (react_val > 601 && react_val < 648) || (react_val > 651 && react_val < 698)
              || (react_val > 701 && react_val < 748) || (react_val > 751 && react_val < 798)
              || (react_val > 801 && react_val < 848) || (react_val > 876 && react_val < 890) )
        {
          if( react_val != mt_cur + 1 )
          {
            string func_name  = "check_photon_data_reaction_type_list()";

            ostringstream oss01;
            oss01 << react_val - 1;
            string err_com = "MF=12, MT=" + oss01.str() +" may be missing.";
            err_obj.output_caution(class_name, func_name, err_com);
          }
          mt_cur = react_val;
        }
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::adjust_photon_production_ene_data(int i)
{
  PhotonDataContainer photon_obj = photon_data_obj_vec[i];

  vector<Integer>          tot_int, tot_range;
  vector<Real>             tot_ene, tot_data;
  vector<vector<Integer> > tab_int, tab_range;
  vector<vector<Real> >    tab_ene, tab_data;
  if( mf_12_data_no > 0 )
  {
    tot_int   = photon_obj.get_multiplicity_tot_int_data();
    tot_range = photon_obj.get_multiplicity_tot_range_data();
    tot_ene   = photon_obj.get_multiplicity_tot_ene_data();
    tot_data  = photon_obj.get_multiplicity_tot_data();
    tab_int   = photon_obj.get_multiplicity_int_data();
    tab_range = photon_obj.get_multiplicity_range_data();
    tab_ene   = photon_obj.get_multiplicity_ene_data();
    tab_data  = photon_obj.get_multiplicity_data();
  }
  else
  {
    tot_int   = photon_obj.get_photon_production_xs_tot_int_data();
    tot_range = photon_obj.get_photon_production_xs_tot_range_data();
    tot_ene   = photon_obj.get_photon_production_xs_tot_ene_data();
    tot_data  = photon_obj.get_photon_production_xs_tot_data();
    tab_int   = photon_obj.get_photon_production_xs_int_data();
    tab_range = photon_obj.get_photon_production_xs_range_data();
    tab_ene   = photon_obj.get_photon_production_xs_ene_data();
    tab_data  = photon_obj.get_photon_production_xs_data();

    if( static_cast<int>(tot_ene.size()) > 0 )
    {
      photon_xs_ene_min.push_back(tot_ene[0]);
    }
  }

  adjust_photon_production_ene_data( tot_range, tot_int, tot_ene, tot_data,
                                     tab_range, tab_int, tab_ene, tab_data );
  if( mf_12_data_no > 0 )
  {
    photon_obj.set_multiplicity_tot_int_data(tot_int);
    photon_obj.set_multiplicity_tot_range_data(tot_range);
    photon_obj.set_multiplicity_tot_ene_data(tot_ene);
    photon_obj.set_multiplicity_tot_data(tot_data);
    photon_obj.set_multiplicity_int_data(tab_int);
    photon_obj.set_multiplicity_range_data(tab_range);
    photon_obj.set_multiplicity_ene_data(tab_ene);
    photon_obj.set_multiplicity_data(tab_data);
  }
  else
  {
    photon_obj.set_photon_production_xs_tot_int_data(tot_int);
    photon_obj.set_photon_production_xs_tot_range_data(tot_range);
    photon_obj.set_photon_production_xs_tot_ene_data(tot_ene);
    photon_obj.set_photon_production_xs_tot_data(tot_data);
    photon_obj.set_photon_production_xs_int_data(tab_int);
    photon_obj.set_photon_production_xs_range_data(tab_range);
    photon_obj.set_photon_production_xs_ene_data(tab_ene);
    photon_obj.set_photon_production_xs_data(tab_data);
  }

  photon_data_obj_vec[i] = photon_obj;
  photon_obj.clear();

  tot_int.clear();
  tot_range.clear();
  tot_ene.clear();
  tot_data.clear();
  clr_obj.clear_vec_array2_int(tab_int);
  clr_obj.clear_vec_array2_int(tab_range);
  clr_obj.clear_vec_array2_real(tab_ene);
  clr_obj.clear_vec_array2_real(tab_data);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::adjust_photon_production_ene_data
                             (vector<Integer>&          tot_range, vector<Integer>&          tot_int,
                              vector<Real>&             tot_ene,   vector<Real>&             tot_data,
                              vector<vector<Integer> >& tab_range, vector<vector<Integer> >& tab_int,
                              vector<vector<Real> >&    tab_ene,   vector<vector<Real> >&    tab_data)
{
  vector<Real> discontinuity_ene_data;

  int i_max = static_cast<int>(tab_ene.size());
  if( i_max == 0 )
  {
    i_max = static_cast<int>(tot_ene.size());
    for(int i=1; i<i_max; i++)
    {
      Real dif_val = static_cast<Real>(min_ene_dif);
      if( fabs(tot_ene[i]) > min_value )
      {
        dif_val = fabs(dif_val*tot_ene[i]);
      }

      if( fabs(tot_ene[i-1] - tot_ene[i]) < dif_val )
      {
        discontinuity_ene_data.push_back(tot_ene[i]);
      }
    }
  }
  else
  {
    vector<Real> tot_ene_new, tot_data_new;
    i_max = static_cast<int>(tot_ene.size());
    tot_ene_new.resize(i_max);
    tot_data_new.resize(i_max);
    tot_ene_new[0] = tot_ene[0];
    tot_data_new[0] = tot_data[0];
    for(int i=1; i<i_max; i++)
    {
      Real dif_val = static_cast<Real>(min_ene_dif);
      if( fabs(tot_ene[i]) > min_value )
      {
        dif_val = fabs(dif_val*tot_ene[i]);
      }

      if( fabs(tot_ene[i-1] - tot_ene[i]) < dif_val )
      {
        discontinuity_ene_data.push_back(tot_ene[i]);
        tot_ene_new[i-1] = digit_obj.get_adjusted_value(tot_ene[i], sig_fig, -1.0);
        tot_ene_new[i]   = digit_obj.get_adjusted_value(tot_ene[i], sig_fig, +1.0);

        ti_obj.interpolation_tab1( tot_ene_new[i-1], tot_data_new[i-1],
                                   tot_range, tot_int, tot_ene, tot_data );
        ti_obj.interpolation_tab1( tot_ene_new[i], tot_data_new[i],
                                   tot_range, tot_int, tot_ene, tot_data );
      }
      else
      {
        tot_ene_new[i]  = tot_ene[i];
        tot_data_new[i] = tot_data[i];
      }
    }
    tot_ene = tot_ene_new;

    int j_max = static_cast<int>(tab_ene.size());
    for(int i=0; i<i_max; i++)
    {
      Real tot_ene_tmp   = tot_ene[i];
      Real tot_data_part = 0.0;
      tot_data[i]        = 0.0;
      for(int j=0; j<j_max; j++)
      {
        ti_obj.interpolation_tab1( tot_ene_tmp, tot_data_part,
                                   tab_range[j], tab_int[j], tab_ene[j], tab_data[j] );
        tot_data[i] += tot_data_part;
      }

      if( fabs(tot_data_new[i]) > min_value )
      {
        Real dif_val = fabs((tot_data[i] - tot_data_new[i]) / tot_data_new[i]);
        if( dif_val > 1.0E-3 )
        {
          string func_name  = "adjust_photon_production_ene_data";

          ostringstream oss01, oss02, oss03, oss04, oss05;
          oss01 << i;
          oss02 << i_max;
          oss03 << tot_data[i];
          oss04 << tot_data_new[i];
          oss05 << dif_val;
          string str_data01 = "i = " + oss01.str() + " / " + oss02.str();
          string str_data02 = "Total data from tot_data          : " + oss03.str();
          string str_data03 = "Total data from total of tab_data : " + oss04.str();
          string str_data04 = "Relative difference               : " + oss05.str();

          vector<string> err_com;
          err_com.push_back(str_data01);
          err_com.push_back(str_data02);
          err_com.push_back(str_data03);
          err_com.push_back(str_data04);
          err_com.push_back("The difference between tot_data and total data of tab_data is");
          err_com.push_back("larger than 1.0E-3.");
          err_obj.output_caution(class_name, func_name, err_com);
        }
      }
    }
  }

  i_max = static_cast<int>(discontinuity_ene_data.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      photon_prod_discon_ene_data.push_back(discontinuity_ene_data[i]);
    }
    discontinuity_ene_data.clear();
  }

}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::modify_transition_probability_array(int i, Integer& react_type_pre,
                                                               vector<Real>& ene_vec)
{
  PhotonDataContainer photon_obj = photon_data_obj_vec[i];

  Real         xs_ene_min     = 0.0;
  Integer      react_type_cur = 0;
  set_ene_data_for_transition_probability_array(i, react_type_cur, react_type_pre, ene_vec, xs_ene_min);

  Integer react_val = reaction_type_list[i];
  int     ele_no    = static_cast<int>(react_val - react_type_cur);
  ene_vec[ele_no] = photon_obj.get_ene_level_max();

  for(int j=ele_no-1; j>=0; j--)
  {
    vector<Real> trans_ene_level = photon_obj.get_trans_ene_level();
    int k_max         = static_cast<int>(trans_ene_level.size());
    int trans_ene_pos = -1;
    for(int k=0; k<k_max; k++)
    {
      if( fabs(trans_ene_level[k]) < min_value && fabs(ene_vec[j]) < min_value )
      {
        trans_ene_pos = k;
        break;
      }
      else if( fabs(trans_ene_level[k]) > min_value &&
               fabs((ene_vec[j] - trans_ene_level[k]) / trans_ene_level[k]) < 1.0E-4 )
      {
        trans_ene_pos = k;
        break; 
      }
    }
    trans_ene_level.clear();

    if( trans_ene_pos < 0 )
    {
      photon_prod_yield_coef_direct[j][ele_no] = 0.0;
      photon_prod_yield_coef_given[j][ele_no]  = 0.0;
    }
    else
    {
      Real8 tp = photon_obj.get_direct_trans_probability()[trans_ene_pos];
      Real8 gp = 1.0;
      if( static_cast<int>(photon_obj.get_photon_trans_probability().size()) > 0 )
      {
        gp = photon_obj.get_photon_trans_probability()[trans_ene_pos];
      }
      photon_prod_yield_coef_direct[j][ele_no] = tp * gp;
      photon_prod_yield_coef_given[j][ele_no]  = tp;
    }

    if( j != ele_no-1 )
    {
      for(int k=j+1; k<ele_no; k++)
      {
        photon_prod_yield_coef_given[j][ele_no] += 
          photon_prod_yield_coef_given[k][ele_no] * photon_prod_yield_coef_direct[j][k];
      }
    }
  }

  calc_photon_production_multiplicity_data(ele_no, ene_vec, xs_ene_min, photon_obj);
  photon_data_obj_vec[i] = photon_obj;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_ene_data_for_transition_probability_array
                             ( int i, Integer& react_type_cur, Integer& react_type_pre,
                               vector<Real>& ene_vec, Real& xs_ene_min)
{
  Integer react_val = reaction_type_list[i];
  if( react_val >= 51 && react_val <= 90 )
  {
    react_type_cur = 50;
  }
  else if( react_val > react_n_h1_min && react_val <= react_n_h1_max )
  {
    react_type_cur = react_n_h1_min;
  }
  else if( react_val > react_n_h2_min && react_val <= react_n_h2_max )
  {
    react_type_cur = react_n_h2_min;
  }
  else if( react_val > react_n_h3_min && react_val <= react_n_h3_max )
  {
    react_type_cur = react_n_h3_min;
  }
  else if( react_val > react_n_he3_min && react_val <= react_n_he3_max )
  {
    react_type_cur = react_n_he3_min;
  }
  else if( react_val > react_n_he4_min && react_val <= react_n_he4_max )
  {
    react_type_cur = react_n_he4_min;
  }
  else if( react_val > 875 && react_val <= 891 )
  {
    react_type_cur = 875;
  }

  xs_ene_min = 0.0;
  for(int j=0; j<reaction_type_no_int; j++)
  {
    if( xs_data_obj_vec[i].get_reaction_type() == reaction_type_list[j] )
    {
      if( static_cast<int>(xs_data_obj_vec[j].get_xs_ene_data().size()) > 0 )
      {
        xs_ene_min = xs_data_obj_vec[j].get_xs_ene_data()[0];
        break;
      }
    }
  }

  if( react_type_pre == react_type_cur )
  {
    return;
  }

  react_type_pre = react_type_cur;
  Integer mt_sta = react_type_cur+1;
  Integer mt_end = 0;
  if( react_type_cur == 50 )
  {
    mt_end = 91;
  }
  else if( react_type_cur != 875 )
  {
    mt_end = mt_sta + 48;
  }
  else
  {
    mt_end = mt_sta + 17;
  }

  int j_max = static_cast<int>(mt_end - mt_sta + 2);
  ene_vec.clear();
  ene_vec.resize(j_max);
  for(int j=0; j<j_max; j++)
  {
    ene_vec[j] = 0.0;
  }

  Real mass_coef = nucl_data_obj.get_general_data_obj().get_mass();
       mass_coef = mass_coef / (mass_coef + 1.0);
  for(int j=0; j<reaction_type_no_int; j++)
  {
    if( reaction_type_list[j] >= mt_sta && reaction_type_list[j] <= mt_end &&
         xs_data_obj_vec[j].get_reaction_type() == reaction_type_list[j] )
    {
      if( static_cast<int>(xs_data_obj_vec[j].get_xs_ene_data().size()) > 0 )
      {
        int ele_no = static_cast<int>(reaction_type_list[j] - mt_sta + 1);
        ene_vec[ele_no] = xs_data_obj_vec[j].get_xs_ene_data()[0] * mass_coef;
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::calc_photon_production_multiplicity_data
                             ( int ele_no, vector<Real>& ene_vec, Real& xs_ene_min,
                               PhotonDataContainer& photon_data_obj )
{
  Real         y_sum = 0.0;
  vector<Real> y_vec, multi_ene_level, multi_photon_ene;
  for(int i=1; i<=ele_no; i++)
  {
    int  ele_base = ele_no+1 - i;
    Real ene_base = ene_vec[ele_base];
    for(int j=0; j<ele_no; j++)
    {
      int  ele_each = ele_no - j - 1;
      Real ene_each = ene_vec[ele_each];
      Real y_val = photon_prod_yield_coef_direct[ele_each][ele_base]
                 * photon_prod_yield_coef_given[ele_base][ele_no];
      if( fabs(y_val) > min_value )
      {
        y_sum += y_val;
        y_vec.push_back(y_val);

        multi_ene_level.push_back(ene_base);
        multi_photon_ene.push_back(ene_base - ene_each);
      }
    }
  }

  //Sort multiplicity photon energy data(multi_photon_ene)
  int i_max = static_cast<int>(multi_photon_ene.size());
  if( i_max > 1 )
  {
    vector<Real> multi_ene_level_new, multi_photon_ene_new, y_vec_new;
    multi_photon_ene_new = multi_photon_ene;
    sort(multi_photon_ene_new.begin(), multi_photon_ene_new.end(),std::greater<Real>());

    vector<int> overlap_chk;
    multi_ene_level_new.resize(i_max);
    y_vec_new.resize(i_max);
    for(int i=0; i<i_max; i++)
    {
      Real multi_photon_ene_tmp = multi_photon_ene_new[i];
      Real multi_photon_ene_dif = fabs(multi_photon_ene_new[i] * min_ene_dif);
      for(int j=0; j<i_max; j++)
      {
        if( fabs(multi_photon_ene[j] - multi_photon_ene_tmp) < multi_photon_ene_dif )
        {
          int skip_flg = -1;
          for(int k=0; k<static_cast<int>(overlap_chk.size()); k++)
          {
            if( j == overlap_chk[k] )
            {
              skip_flg = 1;
            }
          }
 
          if( skip_flg < 0 )
          {
            overlap_chk.push_back(j);

            multi_ene_level_new[i] = multi_ene_level[j];
            y_vec_new[i]           = y_vec[j];
            break;
          }
        }
      }
    }
    y_vec            = y_vec_new;
    multi_ene_level  = multi_ene_level_new;
    multi_photon_ene = multi_photon_ene_new;
    y_vec_new.clear();
    multi_ene_level_new.clear();
    multi_photon_ene_new.clear();
  }

  convert_calc_data_to_photon_data_obj( photon_data_obj, xs_ene_min, y_sum,
                                        y_vec, multi_ene_level, multi_photon_ene );
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::convert_calc_data_to_photon_data_obj
                             ( PhotonDataContainer& photon_data_obj, Real8& xs_ene_min, Real8& y_sum,
                               vector<Real>& y_vec,
                               vector<Real>& multi_ene_level, vector<Real>& multi_photon_ene )
{
  int i_max = static_cast<int>(y_vec.size());

  //Convert calculation data to PhotonDataContainer
  if( i_max > 1 )
  {
    vector<Integer>          multi_tot_int_data, multi_tot_range_data;
    vector<Real>             multi_tot_ene_data, multi_tot_data;
    multi_tot_int_data.resize(1);
    multi_tot_range_data.resize(1);
    multi_tot_ene_data.resize(2);
    multi_tot_data.resize(2);

    multi_tot_int_data[0]   = 2;
    multi_tot_range_data[0] = 2;
    multi_tot_ene_data[0]   = xs_ene_min;
    multi_tot_ene_data[1]   = ene_upper_limit;
    multi_tot_data[0]       = y_sum;
    multi_tot_data[1]       = y_sum;

    photon_data_obj.set_multiplicity_tot_int_data(multi_tot_int_data);
    photon_data_obj.set_multiplicity_tot_range_data(multi_tot_range_data);
    photon_data_obj.set_multiplicity_tot_ene_data(multi_tot_ene_data);
    photon_data_obj.set_multiplicity_tot_data(multi_tot_data);
    multi_tot_int_data.clear();
    multi_tot_range_data.clear();
    multi_tot_ene_data.clear();
    multi_tot_data.clear();
  }

  vector<Integer>          multi_photon_ene_flg, multi_distr_law_no;
  vector<vector<Integer> > multi_int_data,       multi_range_data;
  vector<vector<Real> >    multi_ene_data,       multi_data;
  multi_photon_ene_flg.resize(i_max);
  multi_distr_law_no.resize(i_max);
  multi_int_data.resize(i_max);
  multi_range_data.resize(i_max);
  multi_ene_data.resize(i_max);
  multi_data.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    multi_photon_ene_flg[i] = 0;
    multi_distr_law_no[i]   = 2;

    multi_int_data[i].resize(1);
    multi_range_data[i].resize(1);
    multi_ene_data[i].resize(2);
    multi_data[i].resize(2);

    multi_int_data[i][0]   = 2;
    multi_range_data[i][0] = 2;
    multi_ene_data[i][0]   = xs_ene_min;
    multi_ene_data[i][1]   = ene_upper_limit;
    multi_data[i][0]       = y_vec[i];
    multi_data[i][1]       = y_vec[i];
  }

  //Clear PhotonDataContainer
  Integer level_no_max         = 0;
  Integer trans_photon_ene_flg = 0;
  Real    ene_level_max        = 0.0;
  vector<Real> trans_ene_level, direct_trans_probability, photon_trans_probability;
  trans_ene_level.clear();
  direct_trans_probability.clear();
  photon_trans_probability.clear();
  photon_data_obj.set_level_no_max(level_no_max);
  photon_data_obj.set_trans_photon_ene_flg(trans_photon_ene_flg);
  photon_data_obj.set_ene_level_max(ene_level_max);
  photon_data_obj.set_trans_ene_level(trans_ene_level);
  photon_data_obj.set_direct_trans_probability(direct_trans_probability);
  photon_data_obj.set_photon_trans_probability(photon_trans_probability);

  //Copy the convert data to PhotonDataContainer
  photon_data_obj.set_multiplicity_ene_level(multi_ene_level);
  photon_data_obj.set_multiplicity_binding_ene(multi_photon_ene);
  photon_data_obj.set_multiplicity_binding_ene_flg(multi_photon_ene_flg);
  photon_data_obj.set_multiplicity_distr_law_no(multi_distr_law_no);
  photon_data_obj.set_multiplicity_int_data(multi_int_data);
  photon_data_obj.set_multiplicity_range_data(multi_range_data);
  photon_data_obj.set_multiplicity_ene_data(multi_ene_data);
  photon_data_obj.set_multiplicity_data(multi_data);

  multi_ene_level.clear();
  multi_photon_ene.clear();
  multi_photon_ene_flg.clear();
  multi_distr_law_no.clear();
  clr_obj.clear_vec_array2_int(multi_int_data);
  clr_obj.clear_vec_array2_int(multi_range_data);
  clr_obj.clear_vec_array2_real(multi_ene_data);
  clr_obj.clear_vec_array2_real(multi_data);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::modify_photon_angular_distribution_data_obj(int i)
{
  Integer react_val = reaction_type_list[i];

  if( (react_val >=  50 && react_val <=  90)
   || (react_val >= react_n_h1_min  && react_val < react_n_h1_max)
   || (react_val >= react_n_h2_min  && react_val < react_n_h2_max)
   || (react_val >= react_n_h3_min  && react_val < react_n_h3_max)
   || (react_val >= react_n_he3_min && react_val < react_n_he3_max)
   || (react_val >= react_n_he4_min && react_val < react_n_he4_max) )
  {
    //Clear PhotonDataContainer
    Integer isotropic_flg         = 0;
    Integer angular_repr_flg      = 0;
    Integer iso_photon_angular_no = 0;
    vector<Real>                      angular_ene_level, angular_photon_ene;
    vector<vector<Integer> >          angular_ene_int_data, angular_ene_range_data;
    vector<vector<Real> >             angular_ene_data;
    vector<vector<vector<Integer> > > angular_probability_int_data, angular_probability_range_data;
    vector<vector<vector<Real> > >    angular_legendre_coef_data, angular_probability_cos_data,
                                      angular_probability_data;
    angular_ene_level.clear();
    angular_photon_ene.clear();
    clr_obj.clear_vec_array2_int(angular_ene_int_data);
    clr_obj.clear_vec_array2_int(angular_ene_range_data);
    clr_obj.clear_vec_array2_real(angular_ene_data);
    clr_obj.clear_vec_array3_int(angular_probability_int_data);
    clr_obj.clear_vec_array3_int(angular_probability_range_data);
    clr_obj.clear_vec_array3_real(angular_legendre_coef_data);
    clr_obj.clear_vec_array3_real(angular_probability_cos_data);
    clr_obj.clear_vec_array3_real(angular_probability_data);

    //Create new PhotonDataContainer
    isotropic_flg = 1;

    //Copy the new data to PhotonDataContainer
    photon_data_obj_vec[i].set_isotropic_flg(isotropic_flg);
    photon_data_obj_vec[i].set_angular_repr_flg(angular_repr_flg);
    photon_data_obj_vec[i].set_iso_photon_angular_no(iso_photon_angular_no);
    photon_data_obj_vec[i].set_angular_ene_level(angular_ene_level);
    photon_data_obj_vec[i].set_angular_photon_ene(angular_photon_ene);
    photon_data_obj_vec[i].set_angular_ene_int_data(angular_ene_int_data);
    photon_data_obj_vec[i].set_angular_ene_range_data(angular_ene_range_data);
    photon_data_obj_vec[i].set_angular_ene_data(angular_ene_data);
    photon_data_obj_vec[i].set_angular_probability_int_data(angular_probability_int_data);
    photon_data_obj_vec[i].set_angular_probability_range_data(angular_probability_range_data);
    photon_data_obj_vec[i].set_angular_legendre_coef_data(angular_legendre_coef_data);
    photon_data_obj_vec[i].set_angular_probability_cos_data(angular_probability_cos_data);
    photon_data_obj_vec[i].set_angular_probability_data(angular_probability_data);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::modify_photon_production_data_in_product_distr_data()
{
  if( mf_6_data_no == 0 )
  {
    return;
  }

  for(int i=0; i<reaction_type_no_int; i++)
  {
    Integer react_val = reaction_type_list[i];

    if( prod_distr_data_obj_vec[i].get_prompt_fis_n_flg() > 0 ||
        prod_distr_data_obj_vec[i].get_prompt_fis_p_flg() > 0 )
    {
      continue;
    }

    if( prod_distr_data_obj_vec[i].get_reaction_type() == react_val )
    {
      int          mod_prod_distr_no = 0;
      vector<int>  mod_prod_distr_list;
      vector<Real> e_gam_vec;

      int j_max = static_cast<int>(prod_distr_data_obj_vec[i].get_mat_data_product().size());
      mod_prod_distr_list.resize(j_max);
      e_gam_vec.resize(j_max);
      for(int j=0; j<j_max; j++)
      {
        mod_prod_distr_list[j] = 0;
        e_gam_vec[j]           = 0.0;
        if( fabs(prod_distr_data_obj_vec[i].get_mat_data_product()[j]) < min_value )
        {
          if( prod_distr_data_obj_vec[i].get_distr_func_flg()[j] == 2 )
          {
            e_gam_vec[j] = prod_distr_data_obj_vec[i].get_mass_product()[j];

            string func_name  = "modify_product_distr_data()";
            string err_com    = "Discrete anisotropic photon is treated as simple primary photon.";
            err_obj.output_caution(class_name, func_name, err_com);
          }

          mod_prod_distr_no++;
          mod_prod_distr_list[j] = 1;
        }
      }

      if( mod_prod_distr_no > 0 )
      {
        copy_modified_photon_production_data_in_prod_distr_data
          (i, mod_prod_distr_no, mod_prod_distr_list, e_gam_vec);
      }
      mod_prod_distr_list.clear();
      e_gam_vec.clear();
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::copy_modified_photon_production_data_in_prod_distr_data
                             (int i, int mod_data_no, vector<int>& mod_data_list, vector<Real>& e_gam_vec)
{
  //In the NJOY program, this modification is carried out by the convr subroutine.
  //To modify the photon production data, MF=16 data is newly constructed and output the other PENDF file.
  //Since the number of significant figures in the PENDF file has limited to 11.
  //So, the effect of the rounding error is not small.
  //If you want to compare the calculation result of FRENDY and that of NJOY, or if you found some
  //differences between FRENDY and NJOY, please consider or check the rounding error.

  if( mod_data_no > 1 )
  {
    ostringstream oss01, oss02;
    oss01 << prod_distr_data_obj_vec[i].get_reaction_type();
    oss02 << mod_data_no;
    string func_name = "copy_modified_photon_production_data_in_prod_distr_data";
    vector<string> err_com;
    string str_data01 = "Reaction type    : " + oss01.str();
    string str_data02 = "Modified data no : " + oss02.str();
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("The data number, which the product identifier (ZAP) is equal to zero,");
    err_com.push_back("is larger than 1.");
    err_com.push_back("The nuclear data may not be appropriate.");
    err_obj.output_caution(class_name, func_name, err_com);
  }

  ProductDistributionDataContainer prod_distr_obj = prod_distr_data_obj_vec[i];

  //Declare and resize data for ProductDistributionDataContainer class
  //For common data
  Integer                  ref_frame_flg = prod_distr_obj.get_ref_frame_flg();
  vector<Real>             mat_data_product, mass_product;
  vector<Integer>          product_mod_flg,  distr_func_flg;
  vector<vector<Integer> > product_distr_int_data, product_distr_range_data;
  vector<vector<Real> >    product_distr_ene_data, product_distr_data;
  mat_data_product.resize(mod_data_no);
  mass_product.resize(mod_data_no);
  product_mod_flg.resize(mod_data_no);
  distr_func_flg.resize(mod_data_no);
  product_distr_int_data.resize(mod_data_no);
  product_distr_range_data.resize(mod_data_no);
  product_distr_ene_data.resize(mod_data_no);
  product_distr_data.resize(mod_data_no);

  //For distr_func_flg (LAW) = 1
  vector<Integer>                         angular_repr_flg, second_ene_int_data;
  vector<vector<Integer> >                cont_int_data, cont_range_data, discrete_ene_no;
  vector<vector<Real> >                   cont_ene_a;
  vector<vector<vector<Real> > >          cont_ene_b;
  vector<vector<vector<vector<Real> > > > cont_data;
  angular_repr_flg.resize(mod_data_no);
  second_ene_int_data.resize(mod_data_no);
  cont_int_data.resize(mod_data_no);
  cont_range_data.resize(mod_data_no);
  discrete_ene_no.resize(mod_data_no);
  cont_ene_a.resize(mod_data_no);
  cont_ene_b.resize(mod_data_no);
  cont_data.resize(mod_data_no);

  //For distr_func_flg (LAW) = 2
  vector<vector<Integer> >       two_body_repr_flg, two_body_int_data, two_body_range_data;
  vector<vector<Real> >          two_body_ene_data;
  vector<vector<vector<Real> > > two_body_legendre_coef, two_body_cos, two_body_prob;
  two_body_repr_flg.resize(mod_data_no);
  two_body_int_data.resize(mod_data_no);
  two_body_range_data.resize(mod_data_no);
  two_body_ene_data.resize(mod_data_no);
  two_body_legendre_coef.resize(mod_data_no);
  two_body_cos.resize(mod_data_no);
  two_body_prob.resize(mod_data_no);

  //For distr_func_flg (LAW) = 5
  vector<Real>                   spin_particle;
  vector<Integer>                charged_particle_flg;
  vector<vector<Integer> >       charged_particle_repr_flg,
                                 charged_particle_int_data, charged_particle_range_data;
  vector<vector<Real> >          charged_particle_ene_data;
  vector<vector<vector<Real> > > charged_particle_coef_b,  charged_particle_coef_r,
                                 charged_particle_coef_i,  charged_particle_coef_c,
                                 charged_particle_coef_mu, charged_particle_coef_p;
  spin_particle.resize(mod_data_no);
  charged_particle_flg.resize(mod_data_no);
  charged_particle_repr_flg.resize(mod_data_no);
  charged_particle_int_data.resize(mod_data_no);
  charged_particle_range_data.resize(mod_data_no);
  charged_particle_ene_data.resize(mod_data_no);
  charged_particle_coef_b.resize(mod_data_no);
  charged_particle_coef_r.resize(mod_data_no);
  charged_particle_coef_i.resize(mod_data_no);
  charged_particle_coef_c.resize(mod_data_no);
  charged_particle_coef_mu.resize(mod_data_no);
  charged_particle_coef_p.resize(mod_data_no);

  //Copy and modify ProductDistributionDataContainer data
  int  j_max     = static_cast<int>(mod_data_list.size());
  int  ele_no    = 0;
  Real mass_coef = nucl_data_obj.get_general_data_obj().get_mass();
       mass_coef = mass_coef / (mass_coef + 1.0);
  for(int j=0; j<j_max; j++)
  {
    Real e_gam_val = e_gam_vec[j];
    int  e_gam_flg = 0;
    if( fabs(e_gam_val) > min_value )
    {
      e_gam_flg = 1;
    }

    if( mod_data_list[j] != 0 )
    {
      //Copy common data
      mat_data_product[ele_no]         = prod_distr_obj.get_mat_data_product()[j];
      mass_product[ele_no]             = prod_distr_obj.get_mass_product()[j];
      product_mod_flg[ele_no]          = prod_distr_obj.get_product_mod_flg()[j];
      distr_func_flg[ele_no]           = prod_distr_obj.get_distr_func_flg()[j];
      product_distr_int_data[ele_no]   = prod_distr_obj.get_product_distr_int_data()[j];
      product_distr_range_data[ele_no] = prod_distr_obj.get_product_distr_range_data()[j];
      product_distr_ene_data[ele_no]   = prod_distr_obj.get_product_distr_ene_data()[j];
      product_distr_data[ele_no]       = prod_distr_obj.get_product_distr_data()[j];

      //For distr_func_flg (LAW) = 1
      angular_repr_flg[ele_no]    = prod_distr_obj.get_angular_repr_flg()[j];
      second_ene_int_data[ele_no] = prod_distr_obj.get_second_ene_int_data()[j];
      cont_int_data[ele_no]       = prod_distr_obj.get_cont_int_data()[j];
      cont_range_data[ele_no]     = prod_distr_obj.get_cont_range_data()[j];
      discrete_ene_no[ele_no]     = prod_distr_obj.get_discrete_ene_no()[j];
      cont_ene_a[ele_no]          = prod_distr_obj.get_cont_ene_a()[j];
      cont_ene_b[ele_no]          = prod_distr_obj.get_cont_ene_b()[j];
      cont_data[ele_no]           = prod_distr_obj.get_cont_data()[j];
 
      //For distr_func_flg (LAW) = 2
      two_body_repr_flg[ele_no]      = prod_distr_obj.get_two_body_repr_flg()[j]; 
      two_body_int_data[ele_no]      = prod_distr_obj.get_two_body_int_data()[j];
      two_body_range_data[ele_no]    = prod_distr_obj.get_two_body_range_data()[j];
      two_body_ene_data[ele_no]      = prod_distr_obj.get_two_body_ene_data()[j];
      two_body_legendre_coef[ele_no] = prod_distr_obj.get_two_body_legendre_coef()[j];
      two_body_cos[ele_no]           = prod_distr_obj.get_two_body_cos()[j];
      two_body_prob[ele_no]          = prod_distr_obj.get_two_body_prob()[j];
 
      //For distr_func_flg (LAW) = 5
      spin_particle[ele_no]               = prod_distr_obj.get_spin_particle()[j];
      charged_particle_flg[ele_no]        = prod_distr_obj.get_charged_particle_flg()[j];
      charged_particle_repr_flg[ele_no]   = prod_distr_obj.get_charged_particle_repr_flg()[j];
      charged_particle_int_data[ele_no]   = prod_distr_obj.get_charged_particle_int_data()[j];
      charged_particle_range_data[ele_no] = prod_distr_obj.get_charged_particle_range_data()[j];
      charged_particle_ene_data[ele_no]   = prod_distr_obj.get_charged_particle_ene_data()[j];
      charged_particle_coef_b[ele_no]     = prod_distr_obj.get_charged_particle_coef_b()[j];
      charged_particle_coef_r[ele_no]     = prod_distr_obj.get_charged_particle_coef_r()[j];
      charged_particle_coef_i[ele_no]     = prod_distr_obj.get_charged_particle_coef_i()[j];
      charged_particle_coef_c[ele_no]     = prod_distr_obj.get_charged_particle_coef_c()[j];
      charged_particle_coef_mu[ele_no]    = prod_distr_obj.get_charged_particle_coef_mu()[j];
      charged_particle_coef_p[ele_no]     = prod_distr_obj.get_charged_particle_coef_p()[j];

      if( distr_func_flg[ele_no] == 1 && e_gam_flg != 0 )
      {
        int k_max = static_cast<int>(cont_ene_b[ele_no].size());
        for(int k=0; k<k_max; k++)
        {
          discrete_ene_no[ele_no][k] = 1;

          Real e_gam_mod = e_gam_val + mass_coef * cont_ene_a[ele_no][k];
          cont_ene_b[ele_no][k].resize(1);
          cont_data[ele_no][k].resize(1);
          cont_data[ele_no][k][0].resize(1);
          cont_ene_b[ele_no][k][0]   = e_gam_mod;
          cont_data[ele_no][k][0][0] = 1.0;
        }
      }
      else if( distr_func_flg[ele_no] == 2 && e_gam_flg != 0 )
      {
        int k_max = static_cast<int>(two_body_cos[ele_no].size());
        for(int k=0; k<k_max; k++)
        {
          two_body_repr_flg[ele_no][k] = 1;

          Real e_gam_mod = e_gam_val + mass_coef * two_body_ene_data[ele_no][k];
          two_body_cos[ele_no][k].resize(1);
          two_body_prob[ele_no][k].resize(1);
          two_body_cos[ele_no][k][0]  = e_gam_mod;
          two_body_prob[ele_no][k][0] = 1.0;
        }
      }
      else if( distr_func_flg[ele_no] == 5 && e_gam_flg != 0 )
      {
        int k_max = static_cast<int>(charged_particle_coef_b[ele_no].size());
        for(int k=0; k<k_max; k++)
        {
          charged_particle_repr_flg[ele_no][k] = 1;

          Real e_gam_mod = e_gam_val + mass_coef * charged_particle_ene_data[ele_no][k];
          charged_particle_coef_b[ele_no][k].resize(1);
          charged_particle_coef_r[ele_no][k].resize(1);
          charged_particle_coef_b[ele_no][k][0] = e_gam_mod;
          charged_particle_coef_r[ele_no][k][0] = 1.0;
        }
      }
      ele_no++;
    }
  }

  //Set ProductDistributionDataContainer data
  prod_distr_obj.clear();

  //For common data
  prod_distr_obj.set_reaction_type(reaction_type_list[i]);
  prod_distr_obj.set_ref_frame_flg(ref_frame_flg);
  prod_distr_obj.set_mat_data_product(mat_data_product);
  prod_distr_obj.set_mass_product(mass_product);
  prod_distr_obj.set_product_mod_flg(product_mod_flg);
  prod_distr_obj.set_distr_func_flg(distr_func_flg);
  prod_distr_obj.set_product_distr_int_data(product_distr_int_data);
  prod_distr_obj.set_product_distr_range_data(product_distr_range_data);
  prod_distr_obj.set_product_distr_ene_data(product_distr_ene_data);
  prod_distr_obj.set_product_distr_data(product_distr_data);

  //For distr_func_flg (LAW) = 1
  prod_distr_obj.set_angular_repr_flg(angular_repr_flg);
  prod_distr_obj.set_second_ene_int_data(second_ene_int_data);
  prod_distr_obj.set_cont_int_data(cont_int_data);
  prod_distr_obj.set_cont_range_data(cont_range_data);
  prod_distr_obj.set_discrete_ene_no(discrete_ene_no);
  prod_distr_obj.set_cont_ene_a(cont_ene_a);
  prod_distr_obj.set_cont_ene_b(cont_ene_b);
  prod_distr_obj.set_cont_data(cont_data);

  //For distr_func_flg (LAW) = 2
  prod_distr_obj.set_two_body_repr_flg(two_body_repr_flg);
  prod_distr_obj.set_two_body_int_data(two_body_int_data);
  prod_distr_obj.set_two_body_range_data(two_body_range_data);
  prod_distr_obj.set_two_body_ene_data(two_body_ene_data);
  prod_distr_obj.set_two_body_legendre_coef(two_body_legendre_coef);
  prod_distr_obj.set_two_body_cos(two_body_cos);
  prod_distr_obj.set_two_body_prob(two_body_prob);

  //For distr_func_flg (LAW) = 5
  prod_distr_obj.set_spin_particle(spin_particle);
  prod_distr_obj.set_charged_particle_flg(charged_particle_flg);
  prod_distr_obj.set_charged_particle_repr_flg(charged_particle_repr_flg);
  prod_distr_obj.set_charged_particle_int_data(charged_particle_int_data);
  prod_distr_obj.set_charged_particle_range_data(charged_particle_range_data);
  prod_distr_obj.set_charged_particle_ene_data(charged_particle_ene_data);
  prod_distr_obj.set_charged_particle_coef_b(charged_particle_coef_b);
  prod_distr_obj.set_charged_particle_coef_r(charged_particle_coef_r);
  prod_distr_obj.set_charged_particle_coef_i(charged_particle_coef_i);
  prod_distr_obj.set_charged_particle_coef_c(charged_particle_coef_c);
  prod_distr_obj.set_charged_particle_coef_mu(charged_particle_coef_mu);
  prod_distr_obj.set_charged_particle_coef_p(charged_particle_coef_p);

  prod_distr_data_obj_mod_photon_vec.push_back(prod_distr_obj);
  prod_distr_obj.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::modify_xs_data()
{
  if( sub_lib_part == 1 )
  {
    UnresolvedProbabilityDataContainer unreso_prob_obj;
    unreso_prob_obj = nucl_data_obj.get_reso_data_obj().get_unreso_prob_data_obj();

    if( static_cast<int>(unreso_prob_obj.get_prob_ene().size()) > 0 )
    {
      //FRENDY can not treat heat production cross sections and radiation damage energy
      //production for specified reactions.
      //This if statement required other calculation, i.e., HEATR.
    }
    unreso_prob_obj.clear();

    modify_xs_data_total_ene_grid();
  }
  else
  {
    set_xs_data_union_ene_grid();
    add_elastic_prod_distr_ene_grid();
    adjust_ene_grid();
  }

  modify_xs_data_obj();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::modify_xs_data_total_ene_grid()
{
  vector<Integer> xs_range_data_tot, xs_int_data_tot;

  union_ene_grid.clear();
  for(int i=0; i<reaction_type_no_int; i++)
  {
    if( reaction_type_list[i] == 1 )
    {
      union_ene_grid    = xs_data_obj_vec[i].get_xs_ene_data();
      xs_range_data_tot = xs_data_obj_vec[i].get_xs_range_data();
      xs_int_data_tot   = xs_data_obj_vec[i].get_xs_int_data();
      break;
    }
  }

  int i_max  = static_cast<int>(union_ene_grid.size());
  if( i_max == 0 )
  {
    string func_name  = "modify_xs_data_total_ene_grid";
    string err_com    = "The energy grid no of total cross section is zero.";
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  vector<Real> ene_new;
  for(int i=0; i<i_max; i++)
  {
    if( ti_obj.search_interpolation_range(xs_range_data_tot, xs_int_data_tot, i) == 1 )
    {
      ene_new.push_back(digit_obj.get_adjusted_value(union_ene_grid[i], sig_fig, -1.0));
      ene_new.push_back(digit_obj.get_adjusted_value(union_ene_grid[i], sig_fig, +1.0));
    }
    else
    {
      ene_new.push_back(union_ene_grid[i]);
    }
  }

  sort(ene_new.begin(), ene_new.end());
  i_max = static_cast<int>(ene_new.size());
  Real xs_ene_tot_min = ene_new[0]       + min_ene_dif;
  Real xs_ene_tot_max = ene_new[i_max-1] - min_ene_dif;

  i_max = static_cast<int>(photon_prod_discon_ene_data.size());
  for(int i=0; i<i_max; i++)
  {
    Real dis_ene_val = photon_prod_discon_ene_data[i];
    if( dis_ene_val > xs_ene_tot_min && dis_ene_val < xs_ene_tot_max )
    {
      ene_new.push_back(digit_obj.get_adjusted_value(dis_ene_val, sig_fig, -1.0));
      ene_new.push_back(digit_obj.get_adjusted_value(dis_ene_val, sig_fig, +1.0));
    }
  }

  ta_obj.delete_overlap_grid(ene_new);
  union_ene_grid = ene_new;
  ene_new.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_xs_data_union_ene_grid()
{
  union_ene_grid.clear();
  for(int i=0; i<reaction_type_no_int; i++)
  {
    if( reaction_type_list[i] == xs_data_obj_vec[i].get_reaction_type() )
    {
      vector<Real> xs_ene_vec = xs_data_obj_vec[i].get_xs_ene_data();
      int j_max = static_cast<int>(xs_ene_vec.size());
      for(int j=0; j<j_max; j++)
      {
        union_ene_grid.push_back(xs_ene_vec[j]);
      }
    }
  }

  ta_obj.delete_overlap_grid(union_ene_grid);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::add_elastic_prod_distr_ene_grid()
{
  int ele_no = -1;
  for(int i=0; i<reaction_type_no_int; i++)
  {
    if( reaction_type_list[i] == 2 && reaction_type_list[i] == prod_distr_data_obj_vec[i].get_reaction_type() )
    {
      ele_no = i;
      break;
    }
  }

  if( ele_no < 0 )
  {
    return;
  }

  vector<Integer> distr_func_flg = prod_distr_data_obj_vec[ele_no].get_distr_func_flg();

  int i_max = static_cast<int>(distr_func_flg.size());
  for(int i=0; i<i_max; i++)
  {
    vector<Real> prod_ene_vec;
    if( distr_func_flg[i] == 1 )
    {
      prod_ene_vec = prod_distr_data_obj_vec[ele_no].get_cont_ene_a()[i];
    }
    else if( distr_func_flg[i] == 2 )
    {
      prod_ene_vec = prod_distr_data_obj_vec[ele_no].get_two_body_ene_data()[i];
    }
    else if( distr_func_flg[i] == 5 )
    {
      prod_ene_vec = prod_distr_data_obj_vec[ele_no].get_charged_particle_ene_data()[i];
    }
    else if( distr_func_flg[i] == 7 )
    {
      prod_ene_vec = prod_distr_data_obj_vec[ele_no].get_lab_ene()[i];
    }

    int j_max = static_cast<int>(prod_ene_vec.size());
    for(int j=0; j<j_max; j++)
    {
      union_ene_grid.push_back(prod_ene_vec[j]);
    }
    prod_ene_vec.clear();
  }
  ta_obj.delete_overlap_grid(union_ene_grid);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::adjust_ene_grid()
{
  vector<Real> ene_grid_new;

  int i_max = static_cast<int>(union_ene_grid.size());
  if( i_max == 0 )
  {
    return;
  }

  Real ene_pre = union_ene_grid[0];
  ene_grid_new.push_back(ene_pre);
  for(int i=1; i<i_max; i++)
  {
    Real ene_cur = union_ene_grid[i];
    while( ene_cur > 1.2*ene_pre )
    {
      ene_pre *= 1.2;
      ene_grid_new.push_back(ene_pre);
    }
    ene_grid_new.push_back(ene_cur);
    ene_pre = ene_cur;
  }

  union_ene_grid = ene_grid_new;
  ta_obj.delete_overlap_grid(union_ene_grid);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::modify_xs_data_obj()
{
  int j_max = static_cast<int>(union_ene_grid.size());

  for(int i=0; i<reaction_type_no_int; i++)
  {
    Integer react_val = reaction_type_list[i];
    if( react_val == xs_data_obj_vec[i].get_reaction_type() )
    {
      Integer modify_xs_data_flg = check_modify_xs_data_obj(i);
      if( modify_xs_data_flg == 0 )
      {
        xs_data_obj_vec[i].clear();
        continue;
      }

      if( react_val == 103 )
      {
        mt_103_flg = 1;
      }
      if( react_val == 104 )
      {
        mt_104_flg = 1;
      }
      if( react_val == 105 )
      {
        mt_105_flg = 1;
      }
      if( react_val == 106 )
      {
        mt_106_flg = 1;
      }
      if( react_val == 107 )
      {
        mt_107_flg = 1;
      }

      vector<Real>    xs_data_ori, xs_data_new, xs_ene_data_ori, xs_ene_data_new;
      vector<Integer> xs_int_data_ori, xs_int_data_new, xs_range_data_ori, xs_range_data_new;
      xs_data_ori       = xs_data_obj_vec[i].get_xs_data();
      xs_ene_data_ori   = xs_data_obj_vec[i].get_xs_ene_data();
      xs_int_data_ori   = xs_data_obj_vec[i].get_xs_int_data();
      xs_range_data_ori = xs_data_obj_vec[i].get_xs_range_data();

      Real min_ene_val = xs_ene_data_ori[0] - min_value;
      if(react_val <= 3 || react_val == 102 || react_val == 301 ||
                           react_val == 443 || react_val == 444 ) 
      {
        min_ene_val = ene_lower_limit - min_value;
      }

      for(int j=0; j<j_max; j++)
      {
        if( union_ene_grid[j] < min_ene_val )
        {
          continue;
        }

        Real8 xs_val = 0.0;
        ti_obj.interpolation_tab1(union_ene_grid[j], xs_val,
                                  xs_range_data_ori, xs_int_data_ori, xs_ene_data_ori, xs_data_ori);
        xs_data_new.push_back(xs_val);
        xs_ene_data_new.push_back(union_ene_grid[j]);
      }

      xs_int_data_new.resize(1);
      xs_range_data_new.resize(1);
      xs_int_data_new[0]   = int_lin_lin;
      xs_range_data_new[0] = static_cast<Integer>(xs_data_new.size());

      xs_data_obj_vec[i].set_xs_data(xs_data_new);
      xs_data_obj_vec[i].set_xs_ene_data(xs_ene_data_new);
      xs_data_obj_vec[i].set_xs_int_data(xs_int_data_new);
      xs_data_obj_vec[i].set_xs_range_data(xs_range_data_new);
      xs_data_new.clear();
      xs_ene_data_new.clear();
      xs_int_data_new.clear();
      xs_range_data_new.clear();
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Integer FastAceDataGenerator::check_modify_xs_data_obj(int i)
{
  Integer modify_xs_data_flg = 0;
  Integer react_val          = reaction_type_list[i];

  if( react_val == 3 || (react_val == 4 && sub_lib_part == 1) )
  {
    modify_xs_data_flg = 0;

    if( react_val == photon_data_obj_vec[i].get_reaction_type() )
    {
      if( static_cast<int>(photon_data_obj_vec[i].get_multiplicity_ene_level().size()) > 0 ||
          static_cast<int>(photon_data_obj_vec[i].get_trans_ene_level().size()) > 0 )
      {
        modify_xs_data_flg = 1;
      }
    }

    if( react_val == prod_distr_data_obj_vec[i].get_reaction_type() )
    {
      if( static_cast<int>(prod_distr_data_obj_vec[i].get_product_mod_flg().size()) > 0 )
      {
        modify_xs_data_flg = 1;
      }
    }

    if( react_val == 4 )
    {
      Integer comp_flg = nucl_data_obj.get_reso_data_obj().get_unreso_prob_data_obj().get_comp_flg();
      if( comp_flg % 1000 == 4 )
      {
        modify_xs_data_flg = 1;
      }
    }
  }
  else
  {
    modify_xs_data_flg = 1;
    if( (mt_19_flg == 1 &&  react_val == 18) ||
        (mt_19_flg == 0 && (react_val == 19 || react_val ==  20 || react_val ==  21 || react_val == 38)) ||
         react_val == 26 || react_val == 27 || react_val == 101 || react_val == 120 || react_val == 151  ||
        (react_val > 207 && react_val < 600 && react_val != 301 && react_val != 443 && react_val != 444) ||
        (react_val >= 851 && react_val <= 870 ) || react_val > 900 )
    {
      modify_xs_data_flg = 0;
    }

    if( react_val == 10 )
    {
      modify_xs_data_flg = 0;
    }
  }

  vector<Real> ene_vec = xs_data_obj_vec[i].get_xs_ene_data();
  int j_max = static_cast<int>(ene_vec.size());
  if( j_max == 0 )
  {
    modify_xs_data_flg = 0;
    return modify_xs_data_flg;
  }

  Real mass            = nucl_data_obj.get_general_data_obj().get_mass();
  Real mass_projectile = nucl_data_obj.get_general_data_obj().get_mass_projectile();
  Real mass_coef       = (mass + mass_projectile) / mass;
  Real threshold       = -1.0 * mass_coef * xs_data_obj_vec[i].get_q_value();
  Real ene_vec_min     = ene_vec[0];
  if( threshold < min_value )
  {
    threshold = 0.0;
  }
  else if( ene_vec_min * 1.0001 < threshold )
  {
    string func_name  = "check_modify_xs_data_obj(int i)";
    ostringstream oss01, oss02, oss03;
    oss01 << react_val;
    oss02 << threshold;
    oss03 << ene_vec_min;
    string str_data01 = "Reaction type               : " + oss01.str();
    string str_data02 = "Threshold                   : " + oss02.str();
    string str_data03 = "Minimum enegy in table data : " + oss03.str();
    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("Threshold is less than minimum energy in table data.");
    err_obj.output_caution(class_name, func_name, err_com);
  }

  return modify_xs_data_flg;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::modify_prod_distribution_data()
{
  init_equal_probability_bin();

  if( sub_lib_part == 1 )
  {
    modify_ene_angle_data();
  }
  modify_prod_distr_data();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::modify_prod_distr_data()
{
  for(int i=0; i<reaction_type_no_int; i++)
  {
    Integer react_val = reaction_type_list[i];
    if( (mt_19_flg == 1 && react_val == 18) ||
        (mt_19_flg == 0 && (react_val == 19 || react_val == 20 || react_val == 21 || react_val == 38)) ||
        react_val == 10 )
    {
      continue;
    }

    if( react_val == prod_distr_data_obj_vec[i].get_reaction_type() )
    {
      ProductDistributionDataContainer prod_data_obj = prod_distr_data_obj_vec[i];

      if( new_cummulative_angle_distr_flg == 0 )
      {
        vector<Real>    mat_data_product = prod_data_obj.get_mat_data_product();
        vector<Integer> distr_func_flg   = prod_data_obj.get_distr_func_flg();
        vector<Integer> angular_repr_flg = prod_data_obj.get_angular_repr_flg();
        int j_max        = static_cast<int>(mat_data_product.size());
        int lab_mode_flg = 0;
        for(int j=0; j<j_max; j++)
        {
          if( mat_data_product[j] < 1.0E-3 && distr_func_flg[j] == 1 && angular_repr_flg[j] != 2 )
          {
            lab_mode_flg = 1;
            break;
          }
        }
        if( lab_mode_flg == 1 )
        {
          modify_prod_distr_data_continuum_ene_angle_to_lab(prod_data_obj);
        }
      }

      vector<Integer> distr_func_flg = prod_data_obj.get_distr_func_flg();
      for(int j=0; j<static_cast<int>(distr_func_flg.size()); j++)
      {
        if( new_cummulative_angle_distr_flg == 1 && distr_func_flg[j] == 7 )
        {
          modify_prod_distr_data_lab_to_continuum_ene_angle(j, prod_data_obj);
        }
        else if( distr_func_flg[j] == 2 )
        {
          modify_prod_distr_data_two_body_scatter(j, prod_data_obj);
        }
        else if( distr_func_flg[j] == 7 )
        {
          modify_prod_distr_data_lab(j, prod_data_obj);
        }
      }

      prod_distr_data_obj_vec[i] = prod_data_obj;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::modify_prod_distr_data_continuum_ene_angle_to_lab
                             (ProductDistributionDataContainer& prod_data_obj)
{
  //General data
  Integer                                 ref_frame_flg            = prod_data_obj.get_ref_frame_flg();
  vector<Integer>                         distr_func_flg           = prod_data_obj.get_distr_func_flg();

  //Continuum Energy-Angle Distributions data (LAW=1)
  vector<Integer>                         angular_repr_flg    = prod_data_obj.get_angular_repr_flg();
  vector<Integer>                         second_ene_int_data = prod_data_obj.get_second_ene_int_data();
  vector<vector<Integer> >                cont_int_data       = prod_data_obj.get_cont_int_data();
  vector<vector<Integer> >                cont_range_data     = prod_data_obj.get_cont_range_data();
  vector<vector<Integer> >                discrete_ene_no     = prod_data_obj.get_discrete_ene_no();
  vector<vector<Real> >                   cont_ene_a          = prod_data_obj.get_cont_ene_a();
  vector<vector<vector<Real> > >          cont_ene_b          = prod_data_obj.get_cont_ene_b();
  vector<vector<vector<vector<Real> > > > cont_data           = prod_data_obj.get_cont_data();

  //Laboratory Angle-Energy Law (LAW=7)
  vector<vector<Real> >                      lab_ene;
  vector<vector<Integer> >                   lab_ene_int_data, lab_ene_range_data;
  vector<vector<vector<Real> > >             lab_cos;
  vector<vector<vector<Integer> > >          lab_cos_int_data, lab_cos_range_data;
  vector<vector<vector<vector<Integer> > > > lab_int_data, lab_range_data;
  vector<vector<vector<vector<Real> > > >    lab_ene_sec_data, lab_data;


  //Convert Continuum Energy-Angle Distributions data to Laboratory Angle-Energy Law
  int i_max = static_cast<int>(distr_func_flg.size());
  lab_ene.resize(i_max);
  lab_ene_int_data.resize(i_max);
  lab_ene_range_data.resize(i_max);
  lab_cos.resize(i_max);
  lab_cos_int_data.resize(i_max);
  lab_cos_range_data.resize(i_max);
  lab_int_data.resize(i_max);
  lab_range_data.resize(i_max);
  lab_ene_sec_data.resize(i_max);
  lab_data.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    if( distr_func_flg[i] != 1 )
    {
      continue;
    }

    distr_func_flg[i]     = 7;
    lab_ene[i]            = cont_ene_a[i];
    lab_ene_int_data[i]   = cont_int_data[i];
    lab_ene_range_data[i] = cont_range_data[i];

    int j_max = static_cast<int>(cont_ene_a[i].size());
    lab_cos[i].resize(j_max);
    lab_cos_int_data[i].resize(j_max);
    lab_cos_range_data[i].resize(j_max);
    lab_int_data[i].resize(j_max);
    lab_range_data[i].resize(j_max);
    lab_ene_sec_data[i].resize(j_max);
    lab_data[i].resize(j_max);
    for(int j=0; j<j_max; j++)
    {
      int          k_max   = bin_no+1;
      Real         mu_coef = 2.0 / static_cast<Real>(bin_no);
      vector<Real> mu_ini;
      mu_ini.resize(k_max);
      for(int k=0; k<k_max; k++)
      {
        mu_ini[k] = -1.0 + static_cast<Real>(k) * mu_coef;
      }

      if( static_cast<int>(cont_data[i][j][0].size()) == 0 )
      {
        k_max = 2;
        mu_ini.resize(k_max);
        mu_ini[0] = -1.0;
        mu_ini[1] =  1.0;
      }

      lab_cos_int_data[i][j].resize(1);
      lab_cos_range_data[i][j].resize(1);
      lab_cos_int_data[i][j][0]   = 2;
      lab_cos_range_data[i][j][0] = static_cast<Integer>(k_max);

      lab_cos[i][j].resize(k_max);
      lab_int_data[i][j].resize(k_max);
      lab_range_data[i][j].resize(k_max);
      lab_ene_sec_data[i][j].resize(k_max);
      lab_data[i][j].resize(k_max);

      Real lab_ene_sec_pre = 0.0;
      for(int k=0; k<k_max; k++)
      {
        lab_cos[i][j][k] = mu_ini[k];

        int l_max = static_cast<int>(cont_ene_b[i][j].size());
        for(int l=0; l<l_max; l++)
        {
          Real mu_val = mu_ini[k];
          Real drv    = 1.0;
          if( ref_frame_flg != 1 )
          {
            Real mu_chk = -1.0;
            if( k < k_max-1 )
            {
              mu_chk = mu_ini[k+1];
            }
            change_prod_distr_data_center_of_mass_to_lab
              (mu_val, drv, cont_ene_a[i][j],  cont_ene_b[i][j][l], mu_chk);
          }

          Real func_mu = calc_func_mu(angular_repr_flg[i], mu_val, cont_data[i][j][l]);
          if( l==0 || cont_ene_b[i][j][l] > lab_ene_sec_pre )
          {
            lab_ene_sec_data[i][j][k].push_back(cont_ene_b[i][j][l]);
            lab_data[i][j][k].push_back(func_mu*drv);
            lab_ene_sec_pre = cont_ene_b[i][j][l];
          }
        }

        lab_int_data[i][j][k].resize(1);
        lab_range_data[i][j][k].resize(1);
        lab_int_data[i][j][k][0]   = second_ene_int_data[i];
        lab_range_data[i][j][k][0] = static_cast<Integer>(lab_data[i][j][k].size());

        if( lab_range_data[i][j][k][0] == 1 )
        {
          lab_range_data[i][j][k][0] = 2;
          lab_ene_sec_data[i][j][k].push_back(2.0*lab_ene_sec_data[i][j][k][0]);
          lab_data[i][j][k].push_back(0.0);
        }
      }
    }
  }

  //Set general data
  ref_frame_flg = 1;
  prod_data_obj.set_ref_frame_flg(ref_frame_flg);
  prod_data_obj.set_distr_func_flg(distr_func_flg);

  //Set Laboratory Angle-Energy Law (LAW=7)
  prod_data_obj.set_lab_ene(lab_ene);
  prod_data_obj.set_lab_ene_int_data(lab_ene_int_data);
  prod_data_obj.set_lab_ene_range_data(lab_ene_range_data);
  prod_data_obj.set_lab_cos(lab_cos);
  prod_data_obj.set_lab_cos_int_data(lab_cos_int_data);
  prod_data_obj.set_lab_cos_range_data(lab_cos_range_data);
  prod_data_obj.set_lab_int_data(lab_int_data);
  prod_data_obj.set_lab_range_data(lab_range_data);
  prod_data_obj.set_lab_ene_sec_data(lab_ene_sec_data);
  prod_data_obj.set_lab_data(lab_data);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::change_prod_distr_data_center_of_mass_to_lab
                             (Real& csn, Real& drv, Real& ene_a, Real& ene_b, Real& mu_chk)
{
  Real awl = nucl_data_obj.get_general_data_obj().get_mass() + 1.0;
  Real qq  = 1.0 - awl*awl*ene_b / ene_a;
  Real cmn = -1.0;
  if( qq > min_value )
  {
    cmn = sqrt(qq);
  }

  Real clb = csn;
  if( clb < cmn )
  {
    clb = cmn;
    if( mu_chk > 0.0 && mu_chk <= cmn )
    {
      drv = 0.0;
    }
  }

  qq = ene_b - ene_a*(1.0 - clb*clb)/(awl*awl);
  if( qq < min_value )
  {
    qq = 0.0;
  }
  Real elb = clb*sqrt(ene_a)/awl + sqrt(qq);
  elb = elb*elb;

  if( ene_b > min_value )
  {
    csn = clb*sqrt(elb/ene_b) - sqrt(ene_a/ene_b)/awl;
  }

  if( csn < -1.0 )
  {
    csn = -1.0;
  }
  else if( csn > 1.0 )
  {
    csn = 1.0;
  }

  if( fabs(ene_b) > min_value )
  {
    drv *= sqrt(elb/ene_b);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Real FastAceDataGenerator::calc_func_mu(Integer angular_repr_flg, Real& mu_val, vector<Real>& cont_data)
{
  Real func_mu = 0.0;

  if( angular_repr_flg <= 10 )
  {
    func_mu = lin_tab_obj.calc_legendre_expansion(mu_val, static_cast<Integer>(cont_data.size()), cont_data);
  }
  else
  {
    int l_max = static_cast<int>(cont_data.size()) - 2;
    for(int l=1; l<l_max; l+=2)
    {
      if( cont_data[l] <= mu_val && mu_val <= cont_data[l+2] )
      {
        Integer int_val = angular_repr_flg - 10;
        ti_obj.interpolation_1d(int_val, mu_val, func_mu, cont_data[l],   cont_data[l+1],
                                                          cont_data[l+2], cont_data[l+3]);
        break;
      }
    }
  }

  return func_mu;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::modify_prod_distr_data_lab_to_continuum_ene_angle
                             (int i, ProductDistributionDataContainer& prod_data_obj)
{
  //General data
  vector<Integer> distr_func_flg = prod_data_obj.get_distr_func_flg();

  //Continuum Energy-Angle Distributions data (LAW=1)
  vector<Integer>                         angular_repr_flg    = prod_data_obj.get_angular_repr_flg();
  vector<Integer>                         second_ene_int_data = prod_data_obj.get_second_ene_int_data();
  vector<vector<Integer> >                cont_int_data       = prod_data_obj.get_cont_int_data();
  vector<vector<Integer> >                cont_range_data     = prod_data_obj.get_cont_range_data();
  vector<vector<Integer> >                discrete_ene_no     = prod_data_obj.get_discrete_ene_no();
  vector<vector<Real> >                   cont_ene_a          = prod_data_obj.get_cont_ene_a();
  vector<vector<vector<Real> > >          cont_ene_b          = prod_data_obj.get_cont_ene_b();
  vector<vector<vector<vector<Real> > > > cont_data           = prod_data_obj.get_cont_data();

  //Laboratory Angle-Energy data (LAW=7)
  vector<vector<Real> >                      lab_ene            = prod_data_obj.get_lab_ene();
  vector<vector<Integer> >                   lab_ene_int_data   = prod_data_obj.get_lab_ene_int_data();
  vector<vector<Integer> >                   lab_ene_range_data = prod_data_obj.get_lab_ene_range_data();
  vector<vector<vector<Real> > >             lab_cos            = prod_data_obj.get_lab_cos();
  vector<vector<vector<Integer> > >          lab_cos_int_data   = prod_data_obj.get_lab_cos_int_data();
  vector<vector<vector<Integer> > >          lab_cos_range_data = prod_data_obj.get_lab_cos_range_data();
  vector<vector<vector<vector<Integer> > > > lab_int_data       = prod_data_obj.get_lab_int_data();
  vector<vector<vector<vector<Integer> > > > lab_range_data     = prod_data_obj.get_lab_range_data();
  vector<vector<vector<vector<Real> > > >    lab_ene_sec_data   = prod_data_obj.get_lab_ene_sec_data();
  vector<vector<vector<vector<Real> > > >    lab_data           = prod_data_obj.get_lab_data();

  int j_max = static_cast<int>(lab_ene[i].size());
  if( j_max == 0 )
  {
    return;
  }

  if( static_cast<int>(lab_cos_int_data[i][0].size()) == 0 )
  {
    return;
  }

  Integer int_cos     = lab_cos_int_data[i][0][0];
  Integer int_sec_ene = lab_int_data[i][0][0][0];

  j_max = static_cast<int>(lab_cos_int_data[i].size());
  for(int j=0; j<j_max; j++)
  {
    int k_max = static_cast<int>(lab_cos_int_data[i][j].size());
    for(int k=0; k<k_max; k++)
    {
      if( int_cos != lab_cos_int_data[i][j][k] )
      {
        string func_name  = "modify_prod_distr_data_lab_to_continuum_ene_angle";
        ostringstream oss01, oss02, oss03, oss04, oss05;
        oss01 << i;
        oss02 << j;
        oss03 << k;
        oss04 << int_cos;
        oss05 << lab_cos_int_data[i][j][k];
        string str_data01 = "lab_cos_int_data (" + oss01.str() + ", " + oss02.str() + ", 0) : " + oss04.str();
        string str_data02 = "lab_cos_int_data (" + oss01.str() + ", " + oss02.str() + ", " + oss03.str()
                          + ") : " + oss05.str();
        vector<string> err_com;
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back("Interpolation data is not identical.");
        err_com.push_back("Only the first interpolation data is used.");
        err_obj.output_caution(class_name, func_name, err_com);
      }

      int l_max = static_cast<int>(lab_int_data[i][j][k].size());
      for(int l=0; l<l_max; l++)
      {
        if( int_sec_ene != lab_int_data[i][j][k][l] )
        {
          string func_name  = "modify_prod_distr_data_lab_to_continuum_ene_angle";
          ostringstream oss01, oss02, oss03, oss04, oss05, oss06;
          oss01 << i;
          oss02 << j;
          oss03 << k;
          oss04 << l;
          oss05 << int_sec_ene;
          oss06 << lab_int_data[i][j][k][l];
          string str_data01 = "lab_int_data (" + oss01.str() + ", " + oss02.str() + ", " + oss03.str()
                            + ", 0) : " + oss05.str();
          string str_data02 = "lab_int_data (" + oss01.str() + ", " + oss02.str() + ", " + oss03.str()
                            + oss04.str() + ") : " + oss06.str();
          vector<string> err_com;
          err_com.push_back(str_data01);
          err_com.push_back(str_data02);
          err_com.push_back("Interpolation data is not identical.");
          err_com.push_back("Only the first interpolation data is used.");
          err_obj.output_caution(class_name, func_name, err_com);
        }
      }
    }
  }

  angular_repr_flg[i]    = 10 + int_cos;
  second_ene_int_data[i] = int_sec_ene;
  cont_int_data[i]       = lab_ene_int_data[i];
  cont_range_data[i]     = lab_ene_range_data[i];

  cont_ene_a[i] = lab_ene[i];

  j_max = static_cast<int>(lab_data[i].size());
  discrete_ene_no[i].clear();
  cont_ene_b[i].clear();
  cont_data[i].clear();
  discrete_ene_no[i].resize(j_max);
  cont_ene_b[i].resize(j_max);
  cont_data[i].resize(j_max);
  for(int j=0; j<j_max; j++)
  {
    discrete_ene_no[i][j] = 0;

    vector<Real> lab_ene_sec_data_all;
    for(int k=0; k<static_cast<int>(lab_ene_sec_data[i][j].size()); k++)
    {
      for(int l=0; l<static_cast<int>(lab_ene_sec_data[i][j][k].size()); l++)
      {
        lab_ene_sec_data_all.push_back(lab_ene_sec_data[i][j][k][l]);
      }
    }
    ta_obj.delete_overlap_grid(lab_ene_sec_data_all);

    int k_max = static_cast<int>(lab_ene_sec_data_all.size());
    int l_max = static_cast<int>(lab_ene_sec_data[i][j].size());
    cont_ene_b[i][j] = lab_ene_sec_data_all;
    cont_data[i][j].resize(k_max);
    for(int k=0; k<k_max; k++)
    {
      cont_data[i][j][k].resize(2*l_max);
      for(int l=0; l<l_max; l++)
      {
        cont_data[i][j][k][2*l] = lab_cos[i][j][l];
        ti_obj.interpolation_tab1_in_range
          (cont_ene_b[i][j][k], cont_data[i][j][k][2*l+1], lab_range_data[i][j][l], lab_int_data[i][j][l],
                                                           lab_ene_sec_data[i][j][l], lab_data[i][j][l]);
      }
 
      //Calculate the integrate value
      Real integrate_cont_data = 0.0;
      for(int l=1; l<l_max; l++)
      {
        Real mu_delta = lab_cos[i][j][l] - lab_cos[i][j][l-1];
        if( int_cos == 1 )
        {
          integrate_cont_data += mu_delta * cont_data[i][j][k][2*l-1];
        }
        else
        {
          integrate_cont_data += 0.5*mu_delta*(cont_data[i][j][k][2*l+1] + cont_data[i][j][k][2*l-1]);
        }
      }

      //Normalize cont_data
      if( fabs(integrate_cont_data) > min_value )
      {
        Real integrate_cont_data_inv = 1.0 / integrate_cont_data;
        for(int l=0; l<l_max; l++)
        {
          cont_data[i][j][k][2*l+1] *= integrate_cont_data_inv;
        }
      }
      else
      {
        for(int l=0; l<l_max; l++)
        {
          cont_data[i][j][k][2*l+1] = 0.5;
        }
      }

      //Add the integrate value at initial of cont_data
      vector<Real> cont_data_tmp;
      cont_data_tmp.resize(2*l_max+1);
      cont_data_tmp[0] = integrate_cont_data;
      for(int l=0; l<2*l_max; l++)
      {
        cont_data_tmp[l+1] = cont_data[i][j][k][l];
      }
      cont_data[i][j][k] = cont_data_tmp;
    }
  }
  

  //Set general data
  distr_func_flg[i] = 1;
  prod_data_obj.set_distr_func_flg(distr_func_flg);

  //Set Continuum Energy-Angle Distributions data (LAW=1)
  prod_data_obj.set_angular_repr_flg(angular_repr_flg);
  prod_data_obj.set_second_ene_int_data(second_ene_int_data);
  prod_data_obj.set_cont_int_data(cont_int_data);
  prod_data_obj.set_cont_range_data(cont_range_data);
  prod_data_obj.set_discrete_ene_no(discrete_ene_no);
  prod_data_obj.set_cont_ene_a(cont_ene_a);
  prod_data_obj.set_cont_ene_b(cont_ene_b);
  prod_data_obj.set_cont_data(cont_data);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::modify_prod_distr_data_two_body_scatter
                             (int i, ProductDistributionDataContainer& prod_data_obj)
{
  //Get Two-Body Scattering data (LAW=2)
  string func_name = "modify_prod_distr_data_two_body_scatter";
  vector<vector<Integer> >       two_body_repr_flg      = prod_data_obj.get_two_body_repr_flg();
  vector<vector<vector<Real> > > two_body_legendre_coef = prod_data_obj.get_two_body_legendre_coef();
  vector<vector<vector<Real> > > two_body_cos           = prod_data_obj.get_two_body_cos();
  vector<vector<vector<Real> > > two_body_prob          = prod_data_obj.get_two_body_prob();

  int j_max = static_cast<int>(two_body_repr_flg[i].size());
  if( static_cast<int>(two_body_cos[i].size()) != j_max )
  {
    two_body_cos[i].resize(j_max);
  }
  if( static_cast<int>(two_body_prob[i].size()) != j_max )
  {
    two_body_prob[i].resize(j_max);
  }

  for(int j=0; j<j_max; j++)
  {
    vector<Integer> tab_range_data, tab_int_data;
    if( two_body_repr_flg[i][j] == 0 )
    {
      calc_equal_probability_table_by_legendle_polynomial
        ( two_body_legendre_coef[i][j], tab_range_data, tab_int_data,
          two_body_cos[i][j], two_body_prob[i][j] );
    }
    else
    {
      tab_range_data.resize(1);
      tab_int_data.resize(1);
      tab_range_data[0] = static_cast<Integer>(two_body_cos[i][j].size());
      tab_int_data[0]   = two_body_repr_flg[i][j] - 10;
      if( new_cummulative_angle_distr_flg == 0 )
      {
        calc_equal_probability_table_by_tabulated_probability_data
          (tab_range_data, tab_int_data, two_body_cos[i][j], two_body_prob[i][j]);
        two_body_repr_flg[i][j] = int_const + 10;
      }
      else
      {
        two_body_repr_flg[i][j] = int_lin_lin + 10;

        if( tab_int_data[0] != int_lin_lin )
        {
          if( generate_mode_flg == generate_default_mode )
          {
            //Linearize table data
            Real error_relative = angle_err_def;
            Real error_min      = min_value;
            lin_tab_obj.linearize_tab1_data(tab_range_data, tab_int_data,
                                            two_body_cos[i][j], two_body_prob[i][j],
                                            error_relative, error_min);
            two_body_repr_flg[i][j] = tab_int_data[0] + 10;

            if( tab_int_data[0] == int_const )
            {
              ostringstream oss01, oss02, oss03, oss04, oss05;
              oss01 << prod_data_obj.get_reaction_type();
              oss02 << i+1;
              oss03 << j+1;
              oss04 << j_max;
              oss05 << two_body_repr_flg[i][j];
              string str_data01 = "Reaction type : " + oss01.str();
              string str_data02 = "Position i    : " + oss02.str();
              string str_data03 = "Position j    : " + oss03.str() + " / " + oss04.str();
              string str_data04 = "Flag of interpolation (MF=6, LAW=2)  : " + oss05.str();
              vector<string> err_com;
              err_com.push_back(str_data01);
              err_com.push_back(str_data02);
              err_com.push_back(str_data03);
              err_com.push_back(str_data04);
              err_com.push_back("Flag of interpolation is constant.");
              err_com.push_back("MCNP may not appropriately use this interpolation option.");
              err_obj.output_caution(class_name, func_name, err_com);
            }
          }
          else //if( generate_mode_flg == generate_njoy_mode )
          {
            ostringstream oss01, oss02, oss03, oss04, oss05;
            oss01 << prod_data_obj.get_reaction_type();
            oss02 << i+1;
            oss03 << j+1;
            oss04 << j_max;
            oss05 << two_body_repr_flg[i][j];
            string str_data01 = "Reaction type : " + oss01.str();
            string str_data02 = "Position i    : " + oss02.str();
            string str_data03 = "Position j    : " + oss03.str() + " / " + oss04.str();
            string str_data04 = "Flag of interpolation (MF=6, LAW=2)  : " + oss05.str();
            vector<string> err_com;
            err_com.push_back(str_data01);
            err_com.push_back(str_data02);
            err_com.push_back(str_data03);
            err_com.push_back(str_data04);
            err_com.push_back("Flag of interpolation is not identical to 12 (linear-linear).");
            err_com.push_back("This program considered that interpolation type is linear-linear.");
            err_com.push_back("The angular distribution in ACE file is not appropriate.");
            err_com.push_back("If you want to use appropriate value, please set");
            err_com.push_back("new_cummulative_angle_distr_flg = 1.");
            err_obj.output_caution(class_name, func_name, err_com);
          }
        }
      }
    }
    tab_range_data.clear();
    tab_int_data.clear();
  }

  //Get Two-Body Scattering data (LAW=2)
  prod_data_obj.set_two_body_repr_flg(two_body_repr_flg);
  prod_data_obj.set_two_body_legendre_coef(two_body_legendre_coef);
  prod_data_obj.set_two_body_cos(two_body_cos);
  prod_data_obj.set_two_body_prob(two_body_prob);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::modify_prod_distr_data_lab
                             (int i, ProductDistributionDataContainer& prod_data_obj)
{
  //Laboratory Angle-Energy data (LAW=7)
  vector<vector<Real> >                      lab_ene            = prod_data_obj.get_lab_ene();
  vector<vector<Integer> >                   lab_ene_int_data   = prod_data_obj.get_lab_ene_int_data();
  vector<vector<Integer> >                   lab_ene_range_data = prod_data_obj.get_lab_ene_range_data();
  vector<vector<vector<Real> > >             lab_cos            = prod_data_obj.get_lab_cos();
  vector<vector<vector<Integer> > >          lab_cos_int_data   = prod_data_obj.get_lab_cos_int_data();
  vector<vector<vector<Integer> > >          lab_cos_range_data = prod_data_obj.get_lab_cos_range_data();
  vector<vector<vector<vector<Integer> > > > lab_int_data       = prod_data_obj.get_lab_int_data();
  vector<vector<vector<vector<Integer> > > > lab_range_data     = prod_data_obj.get_lab_range_data();
  vector<vector<vector<vector<Real> > > >    lab_ene_sec_data   = prod_data_obj.get_lab_ene_sec_data();
  vector<vector<vector<vector<Real> > > >    lab_data           = prod_data_obj.get_lab_data();

  //Special data for Laboratory Angle-Energy data (LAW=7)
  vector<vector<vector<Integer> > > lab_integrate_int_data   = prod_data_obj.get_lab_integrate_int_data();
  vector<vector<vector<Integer> > > lab_integrate_range_data = prod_data_obj.get_lab_integrate_range_data();
  vector<vector<vector<Real> > >    lab_integrate_cos_data   = prod_data_obj.get_lab_integrate_cos_data();
  vector<vector<vector<Real> > >    lab_integrate_data       = prod_data_obj.get_lab_integrate_data();
  lab_integrate_int_data[i].clear();
  lab_integrate_range_data[i].clear();
  lab_integrate_cos_data[i].clear();
  lab_integrate_data[i].clear();

  int j_max = static_cast<int>(lab_data[i].size());
  lab_integrate_int_data[i].resize(j_max);
  lab_integrate_range_data[i].resize(j_max);
  lab_integrate_cos_data[i].resize(j_max);
  lab_integrate_data[i].resize(j_max);
  for(int j=0; j<j_max; j++)
  {
    int k_max = static_cast<int>(lab_data[i][j].size());
    lab_integrate_data[i][j].resize(k_max);
    lab_integrate_int_data[i][j]   = lab_cos_int_data[i][j];
    lab_integrate_range_data[i][j] = lab_cos_range_data[i][j];
    lab_integrate_cos_data[i][j]   = lab_cos[i][j];
    for(int k=0; k<k_max; k++)
    {
      Real ene_min_lab = 0.0;
      Real ene_max_lab = 1.0E+9;

      Real integrate_lab_data = integ_obj.integrate_tab1_data
                                            ( lab_range_data[i][j][k],   lab_int_data[i][j][k],
                                              lab_ene_sec_data[i][j][k], lab_data[i][j][k] );

      if( ene_min_lab + min_ene_dif < lab_ene_sec_data[i][j][k][0] )
      {
        integrate_lab_data += integ_obj.integrate_data
                                          ( lab_ene_sec_data[i][j][k][0], lab_data[i][j][k][0],
                                            lab_ene_sec_data[i][j][k][1], lab_data[i][j][k][1],
                                            int_lin_lin, ene_min_lab, lab_ene_sec_data[i][j][k][0] );
      }

      int l_max = static_cast<int>(lab_ene_sec_data[i][j][k].size());
      if( lab_ene_sec_data[i][j][k][l_max-1] + min_ene_dif < ene_max_lab )
      {
        integrate_lab_data += integ_obj.integrate_data
                                          ( lab_ene_sec_data[i][j][k][l_max-2], lab_data[i][j][k][l_max-2],
                                            lab_ene_sec_data[i][j][k][l_max-1], lab_data[i][j][k][l_max-1],
                                            int_const, lab_ene_sec_data[i][j][k][l_max-1], ene_max_lab );
      }

      lab_integrate_data[i][j][k] = integrate_lab_data;

      integrate_lab_data = 1.0/integrate_lab_data;
      for(int l=0; l<l_max; l++)
      {
        lab_data[i][j][k][l] *= 1.0/integrate_lab_data;
      }
    }

    if( new_cummulative_angle_distr_flg == 0 )
    {
      calc_equal_probability_table_by_tabulated_probability_data
        ( lab_integrate_range_data[i][j], lab_integrate_int_data[i][j],
          lab_integrate_cos_data[i][j],   lab_integrate_data[i][j] );
    }
  }

  //Set Laboratory Angle-Energy Law (LAW=7)
  prod_data_obj.set_lab_ene(lab_ene);
  prod_data_obj.set_lab_ene_int_data(lab_ene_int_data);
  prod_data_obj.set_lab_ene_range_data(lab_ene_range_data);
  prod_data_obj.set_lab_cos(lab_cos);
  prod_data_obj.set_lab_integrate_int_data(lab_integrate_int_data);
  prod_data_obj.set_lab_integrate_range_data(lab_integrate_range_data);
  prod_data_obj.set_lab_integrate_cos_data(lab_integrate_cos_data);
  prod_data_obj.set_lab_integrate_data(lab_integrate_data);
  prod_data_obj.set_lab_cos_int_data(lab_cos_int_data);
  prod_data_obj.set_lab_cos_range_data(lab_cos_range_data);
  prod_data_obj.set_lab_int_data(lab_int_data);
  prod_data_obj.set_lab_range_data(lab_range_data);
  prod_data_obj.set_lab_ene_sec_data(lab_ene_sec_data);
  prod_data_obj.set_lab_data(lab_data);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::modify_ene_angle_data()
{
  for(int i=0; i<reaction_type_no_int; i++)
  {
    Integer react_val = reaction_type_list[i];
    if( (mt_19_flg == 1 && react_val == 18) ||
        (mt_19_flg == 0 && (react_val == 19 || react_val == 20 || react_val == 21 || react_val == 38)) )
    {
      continue;
    }

    if( react_val == ene_angle_data_obj_vec[i].get_reaction_type() )
    {
      //For angular distributions of secondarty particles (MF=4)
      if( static_cast<int>(ene_angle_data_obj_vec[i].get_temp_target_polynomial().size()) > 0 ||
          static_cast<int>(ene_angle_data_obj_vec[i].get_temp_target_tab().size()) > 0 )
      {
        if( new_cummulative_angle_distr_flg != 1 )
        {
          modify_angular_in_ene_angle_data(ene_angle_data_obj_vec[i]);
        }
      }

      //For energy distributions of secondarty particles (MF=5)
      if( static_cast<int>(ene_angle_data_obj_vec[i].get_ene_repr_flg().size()) > 0 )
      {
        if(react_val <= 900 )
        {
          check_ene_part_data_in_ene_angle_data(ene_angle_data_obj_vec[i]);
        }
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::modify_angular_in_ene_angle_data(EnergyAngularDataContainer& ene_angle_data_obj)
{
  //General data
  Integer      angular_repr_flg, isotropic_flg;

  //Legendre polynomial coefficients
  vector<Integer>       angular_int_data_polynomial, angular_range_data_polynomial;
  vector<vector<Real> > angular_data_polynomial;
  vector<Real>          temp_target_polynomial, angular_probability_ene_polynomial;
  vector<Integer>       temp_target_dependence_flg_polynomial;

  //Tabulated probability distributions
  vector<Integer>          angular_int_data_tab, angular_range_data_tab;
  vector<vector<Integer> > angular_probability_int_data_tab, angular_probability_range_data_tab;
  vector<vector<Real> >    angular_probability_cos_tab, angular_probability_data_tab;
  vector<Real>             temp_target_tab, angular_probability_ene_tab;
  vector<Integer>          temp_target_dependence_flg_tab;

  //Copy parameters in EnergyAngularDataContainer
  //General data
  angular_repr_flg                      = ene_angle_data_obj.get_angular_repr_flg();
  isotropic_flg                         = ene_angle_data_obj.get_isotropic_flg();

  //Legendre polynomial coefficients
  angular_int_data_polynomial           = ene_angle_data_obj.get_angular_int_data_polynomial();
  angular_range_data_polynomial         = ene_angle_data_obj.get_angular_range_data_polynomial();
  angular_data_polynomial               = ene_angle_data_obj.get_angular_data_polynomial();
  temp_target_polynomial                = ene_angle_data_obj.get_temp_target_polynomial();
  angular_probability_ene_polynomial    = ene_angle_data_obj.get_angular_probability_ene_polynomial();
  temp_target_dependence_flg_polynomial = ene_angle_data_obj.get_temp_target_dependence_flg_polynomial();

  //Tabulated probability distributions
  angular_int_data_tab                  = ene_angle_data_obj.get_angular_int_data_tab();
  angular_range_data_tab                = ene_angle_data_obj.get_angular_range_data_tab();
  angular_probability_int_data_tab      = ene_angle_data_obj.get_angular_probability_int_data_tab();
  angular_probability_range_data_tab    = ene_angle_data_obj.get_angular_probability_range_data_tab();
  angular_probability_cos_tab           = ene_angle_data_obj.get_angular_probability_cos_tab();
  angular_probability_data_tab          = ene_angle_data_obj.get_angular_probability_data_tab();
  temp_target_tab                       = ene_angle_data_obj.get_temp_target_tab();
  angular_probability_ene_tab           = ene_angle_data_obj.get_angular_probability_ene_tab();
  temp_target_dependence_flg_tab        = ene_angle_data_obj.get_temp_target_dependence_flg_tab();

  //Modify parameters in EnergyAngularDataContainer
  angular_repr_flg = 2;
  if( isotropic_flg != 1 )
  {
    int i_max  = static_cast<int>(angular_int_data_polynomial.size());
    int ele_no = i_max + static_cast<int>(angular_int_data_tab.size());
    vector<Integer>          angle_range_data, angle_int_data, temp_target_flg;
    vector<Real>             temp_target, angular_probability_ene;
    vector<vector<Real> >    tab_mu_data, tab_y_data;
    vector<vector<Integer> > tab_range_data, tab_int_data;
    angle_range_data.resize(ele_no);
    angle_int_data.resize(ele_no);
    temp_target_flg.resize(ele_no);
    temp_target.resize(ele_no);
    angular_probability_ene.resize(ele_no);
    tab_mu_data.resize(ele_no);
    tab_y_data.resize(ele_no);
    tab_range_data.resize(ele_no);
    tab_int_data.resize(ele_no);

    ele_no = 0;
    for(int i=0; i<i_max; i++)
    {
      calc_equal_probability_table_by_legendle_polynomial
        (angular_data_polynomial[i], tab_range_data[ele_no], tab_int_data[ele_no],
                                     tab_mu_data[ele_no],    tab_y_data[ele_no]);
      angle_range_data[ele_no]        = angular_range_data_polynomial[i];
      angle_int_data[ele_no]          = angular_int_data_polynomial[i];
      temp_target_flg[ele_no]         = temp_target_dependence_flg_polynomial[i];
      temp_target[ele_no]             = temp_target_polynomial[i];
      angular_probability_ene[ele_no] = angular_probability_ene_polynomial[i];
      ele_no++;
    }

    i_max   = static_cast<int>(angular_int_data_tab.size());
    for(int i=0; i<i_max; i++)
    {
      calc_equal_probability_table_by_tabulated_probability_data
        ( angular_probability_range_data_tab[i], angular_probability_int_data_tab[i],
          angular_probability_cos_tab[i],        angular_probability_data_tab[i], 1 );
      angle_range_data[ele_no]        = angular_range_data_tab[i];
      angle_int_data[ele_no]          = angular_int_data_tab[i];
      temp_target_flg[ele_no]         = temp_target_dependence_flg_tab[i];
      temp_target[ele_no]             = temp_target_tab[i];
      angular_probability_ene[ele_no] = angular_probability_ene_tab[i];
      tab_range_data[ele_no]          = angular_probability_range_data_tab[i];
      tab_int_data[ele_no]            = angular_probability_int_data_tab[i];
      tab_mu_data[ele_no]             = angular_probability_cos_tab[i];
      tab_y_data[ele_no]              = angular_probability_data_tab[i];
      ele_no++;
    }
    angular_range_data_tab             = angle_range_data;
    angular_int_data_tab               = angle_int_data;
    temp_target_dependence_flg_tab     = temp_target_flg;
    temp_target_tab                    = temp_target;
    angular_probability_ene_tab        = angular_probability_ene;
    angular_probability_range_data_tab = tab_range_data;
    angular_probability_int_data_tab   = tab_int_data;
    angular_probability_cos_tab        = tab_mu_data;
    angular_probability_data_tab       = tab_y_data;
  }

  //Set parameters to EnergyAngularDataContainer
  ene_angle_data_obj.set_angular_repr_flg(angular_repr_flg);
  ene_angle_data_obj.set_angular_int_data_polynomial(angular_int_data_polynomial);
  ene_angle_data_obj.set_angular_range_data_polynomial(angular_range_data_polynomial);
  ene_angle_data_obj.set_angular_data_polynomial(angular_data_polynomial);
  ene_angle_data_obj.set_angular_int_data_tab(angular_int_data_tab);
  ene_angle_data_obj.set_angular_range_data_tab(angular_range_data_tab);
  ene_angle_data_obj.set_angular_probability_int_data_tab(angular_probability_int_data_tab);
  ene_angle_data_obj.set_angular_probability_range_data_tab(angular_probability_range_data_tab);
  ene_angle_data_obj.set_angular_probability_cos_tab(angular_probability_cos_tab);
  ene_angle_data_obj.set_angular_probability_data_tab(angular_probability_data_tab);
  ene_angle_data_obj.set_temp_target_tab(temp_target_tab);
  ene_angle_data_obj.set_angular_probability_ene_tab(angular_probability_ene_tab);
  ene_angle_data_obj.set_temp_target_dependence_flg_tab(temp_target_dependence_flg_tab);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::check_ene_part_data_in_ene_angle_data(EnergyAngularDataContainer& ene_angle_data_obj)
{
  vector<Integer>                   ene_repr_flg        = ene_angle_data_obj.get_ene_repr_flg();
  vector<vector<vector<Integer> > > ene_part_range_data = ene_angle_data_obj.get_ene_part_range_data();
  vector<vector<vector<Integer> > > ene_part_int_data   = ene_angle_data_obj.get_ene_part_int_data();
  vector<vector<vector<Real> > >    ene_part_ene_data   = ene_angle_data_obj.get_ene_part_ene_data();
  vector<vector<vector<Real> > >    ene_part_data       = ene_angle_data_obj.get_ene_part_data();

  vector<int> pos_data;
  pos_data.resize(2);

  int i_max = static_cast<int>(ene_repr_flg.size());
  for(int i=0; i<i_max; i++)
  {
    if( ene_repr_flg[i] != 1 )
    {
      continue;
    }

    pos_data[0] = i;

    int j_max = static_cast<int>(ene_part_data[i].size());
    for(int j=0; j<j_max; j++)
    {
      pos_data[1] = j;

      int k_max    = static_cast<int>(ene_part_data[i][j].size());
      int zero_flg = -1;
      for(int k=0; k<k_max; k++)
      {
        if( fabs(ene_part_data[i][j][k]) > min_value )
        {
          zero_flg = k;
          break;
        }
      }

      if( zero_flg >= 0 )
      {
        zero_flg = 0; //Not remove zero value data.
                      //If zero_flg > 0, the integrate value is also varied.
                      //Integration range is varied from 0.0 to x_vec[zero_flg].

        //Modify x and y data
        k_max -= zero_flg;
        vector<Real> x_vec, y_vec;
        x_vec.resize(k_max);
        y_vec.resize(k_max);

        int ele_no = zero_flg;
        for(int k=0; k<k_max; k++)
        {
          x_vec[k] = ene_part_ene_data[i][j][ele_no];
          y_vec[k] = ene_part_data[i][j][ele_no];
          ele_no++;
        }

        //Modify interpolation data
        vector<Integer> range_vec, int_vec;
        k_max = static_cast<int>(ene_part_range_data[i][j].size());
        for(int k=0; k<k_max; k++)
        {
          if( ene_part_range_data[i][j][k] > zero_flg )
          {
            range_vec.push_back(ene_part_range_data[i][j][k] - zero_flg);
            int_vec.push_back(ene_part_int_data[i][j][k]);
          }
        }

        //Check interpolation
        if( generate_mode_flg == generate_default_mode )
        {
          //Linearize table data
          Real error_relative = angle_err_def;
          Real error_min      = min_value;
          lin_tab_obj.linearize_tab1_data(range_vec, int_vec, x_vec, y_vec, error_relative, error_min);
        }

        //Copy modified data
        ene_part_range_data[i][j] = range_vec;
        ene_part_int_data[i][j]   = int_vec;
        ene_part_ene_data[i][j] = x_vec;
        ene_part_data[i][j]     = y_vec;
        range_vec.clear();
        int_vec.clear();
        x_vec.clear();
        y_vec.clear();
      }
      else if( zero_flg < 0 )
      {
        string func_name  = "modify_energy_in_ene_angle_data";
        ostringstream oss01, oss02, oss03, oss04;
        oss01 << i+1;
        oss02 << i_max;
        oss03 << j+1;
        oss04 << j_max;
        string str_data01 = "Position i : " + oss01.str() + " / " + oss02.str();
        string str_data02 = "Position j : " + oss03.str() + " / " + oss04.str();
        vector<string> err_com;
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back("All g(Ej->E'k) is equal to zero.");
        err_com.push_back("The nuclear data may not be appropriate.");
        err_obj.output_runtime_error(class_name, func_name, err_com);
      }
    }
  }

  ene_angle_data_obj.set_ene_part_range_data(ene_part_range_data);
  ene_angle_data_obj.set_ene_part_int_data(ene_part_int_data);
  ene_angle_data_obj.set_ene_part_ene_data(ene_part_ene_data);
  ene_angle_data_obj.set_ene_part_data(ene_part_data);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::init_equal_probability_bin()
{
  int i_max = equal_prob_bin_no;
  equal_prob_data_ini.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    int j_max = 1 + (i+1)/2;
    equal_prob_data_ini[i].resize(j_max);
    for(int j=0; j<j_max; j++)
    {
      equal_prob_data_ini[i][j] = 0.0;
    }
  }

  Real afac  =  1.0;
  Real asign = -1.0;
  for(int i=0; i<i_max; i++)
  {
    int  i_no = i+1;

    Real cf   = 1.0;
    Real aa   = static_cast<Real>(i_no) + 0.5;
    int  ist  = 0;
    int  ifi  = 1;
    int  jfi  = 1;
    int  ivar = 2;

    if( i > 0 )
    {
      afac *= 2.0 - 1.0 / static_cast<Real>(i_no);
    }

    int  j_max = static_cast<int>(equal_prob_data_ini[i].size());
    equal_prob_data_ini[i][0] = cf*afac*aa/static_cast<Real>(i_no+jfi);
    for(int j=1; j<j_max; j++)
    {
      Real b, c, d;

      jfi -= 2;
      b    = static_cast<Real>((i_no-ist) * (i_no-ifi));
      c    = static_cast<Real>(ivar*(2*i_no - ifi));
      d    = static_cast<Real>(i_no+jfi);
      cf  *= asign*b/c;

      equal_prob_data_ini[i][j] = cf*afac*aa/d;

      ist  += 2;
      ifi  += 2;
      ivar += 2;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::calc_equal_probability_table_by_legendle_polynomial
                             ( vector<Real>& list_data,
                               vector<Integer>& tab_range_data, vector<Integer>& tab_int_data,
                               vector<Real>& tab_mu_data, vector<Real>& tab_y_data )
{
  check_legendle_polynomial_data(list_data, tab_range_data, tab_int_data, tab_mu_data, tab_y_data);
  if( static_cast<int>(tab_mu_data.size()) > 0 )
  {
    return;
  }

  vector<Real> mu_vec, equivalent_prob, prob_sum;
  calc_mu_and_equivalent_prob_by_legendle_polynomial(list_data, mu_vec, equivalent_prob, prob_sum);

  vector<Real> mu_vec_new;
  mu_vec_new.resize(bin_no);
  int  ele_no        = 0;
  int  ele_no_max    = static_cast<int>(prob_sum.size());
  Real mu_val        = 0.0;
  Real prob_val      = 0.0;
  Real prob_residual = 0.0;
  Real prob_ave      = prob_sum[ele_no_max-1] / static_cast<Real>(bin_no);
  for(int i=0; i<bin_no; i++)
  {
    mu_val        = mu_vec[ele_no+1];
    prob_val      = prob_sum[ele_no];
    prob_residual = prob_val - prob_ave*static_cast<Real>(i+1);

    while( prob_residual < min_value && ele_no < ele_no_max - 1 )
    {
      ele_no++;
      mu_val        = mu_vec[ele_no+1];
      prob_val      = prob_sum[ele_no];
      prob_residual = prob_val - prob_ave*static_cast<Real>(i+1);
    }

    if( fabs(prob_residual) < min_value && ele_no < ele_no_max - 1 )
    {
      mu_vec_new[i] = mu_val;
      ele_no++;
    }
    else if( ele_no == ele_no_max )
    {
      mu_vec_new[i] = mu_vec[ele_no];
    }
    else
    {
      Real prob_sum_tot = prob_ave*static_cast<Real>(i+1);
      Real prob_dif     = prob_sum_tot     - prob_sum[ele_no-1];
      Real prob_delta   = prob_sum[ele_no] - prob_sum[ele_no-1];
      Real mu_delta     = mu_vec[ele_no+1] - mu_vec[ele_no];

      mu_val        = mu_vec[ele_no] + (prob_dif*mu_delta/prob_delta);
      mu_vec_new[i] = mu_val;
    }
  }

  //Modify mu_vec and equivalent_prob
  mu_vec.clear();
  equivalent_prob.clear();
  mu_vec.resize(bin_no+1);
  equivalent_prob.resize(bin_no+1);

  mu_vec[0] = -1.0;
  for(int i=0; i<bin_no; i++)
  {
    mu_vec[i+1]        = mu_vec_new[i];
    equivalent_prob[i] = prob_ave / (mu_vec[i+1] - mu_vec[i]);
  }
  equivalent_prob[bin_no] = 0.0;
  mu_vec_new.clear();
  
  //Modify table data
  tab_range_data.resize(1);
  tab_int_data.resize(1);
  tab_range_data[0] = static_cast<Integer>(bin_no+1);
  tab_int_data[0]   = int_const;
  tab_mu_data       = mu_vec;
  tab_y_data        = equivalent_prob;

  mu_vec.clear();
  equivalent_prob.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::check_legendle_polynomial_data
                             ( vector<Real>& list_data,
                               vector<Integer>& tab_range_data, vector<Integer>& tab_int_data,
                               vector<Real>& tab_mu_data, vector<Real>& tab_y_data )
{
  tab_range_data.clear();
  tab_int_data.clear();
  tab_mu_data.clear();
  tab_y_data.clear();

  int i_max        = static_cast<int>(list_data.size());
  int zero_chk_flg = 0;
  for(int i=0; i<i_max; i++)
  {
    if( fabs(list_data[i]) > min_value )
    {
      zero_chk_flg = 1;
      break;
    }
  }

  if( zero_chk_flg == 0 )
  {
    tab_range_data.resize(1);
    tab_int_data.resize(1);
    tab_mu_data.resize(2);
    tab_y_data.resize(2);

    tab_range_data[0] = 2;
    tab_int_data[0]   = int_lin_lin;
    tab_mu_data[0]    = -1.0;
    tab_mu_data[1]    =  1.0;
    tab_y_data[0]     =  0.5;
    tab_y_data[1]     =  0.5;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::calc_mu_and_equivalent_prob_by_legendle_polynomial
                             (vector<Real>& list_data, vector<Real>& mu_vec, vector<Real>& equivalent_prob,
                              vector<Real>& prob_sum)
{
  int  mu_no      =  100;
  int  mu_no_fine = 1000;
  int  list_no    = static_cast<int>(list_data.size());

  vector<Real> coef_list;
  coef_list.resize(list_no+1);

  //For i = 0 (To devide 100 data)
  Real mu_delta  = 0.02; //(1.0 - -1.0) / mu_no
  equivalent_prob.resize(mu_no);
  prob_sum.resize(mu_no);
  mu_vec.resize(mu_no+1); 
  mu_vec[0] = -1.0;
  for(int i=1; i<=mu_no; i++)
  {
    mu_vec[i] = mu_vec[i-1] + mu_delta;
  }

  int  case_no      = 2;
  Real prob_sum_tot = 0.0;
  for(int i=0; i<case_no; i++)
  {
    int  mu_mid_pos    = 0;
    Real prob_coef_pre = 0.0;
    Real prob_coef_cur = 0.0;

    prob_sum_tot = 0.0;
    for(int j=0; j<static_cast<int>(prob_sum.size()); j++)
    {
      prob_sum[j] = 0.0;
    }

    for(int j=0; j<static_cast<int>(mu_vec.size()); j++)
    {
      Real mu_var  = mu_vec[j];
      coef_list[0] = mu_var;
      for(int k=1; k<=list_no; k++)
      {
        coef_list[k] = coef_list[k-1] * mu_var;
        if( fabs(coef_list[k]) < 1.0E-50 )
        {
          coef_list[k] = 0.0;
        }
      }

      prob_coef_cur = 0.5*mu_var;
      for(int k=0; k<list_no; k++)
      {
        int  l_max    = 1 + (k+1)/2;
        int  list_pos = k+1;
        Real list_val = list_data[k];
        for(int l=0; l<l_max; l++)
        {
          prob_coef_cur += equal_prob_data_ini[k][l] * coef_list[list_pos] * list_val;
          list_pos -= 2;
        }
      }

      if( j > 0 )
      {
        mu_mid_pos++;
        equivalent_prob[j-1] = prob_coef_cur - prob_coef_pre;

        //Search middle point
        prob_sum_tot += equivalent_prob[j-1];
        prob_sum[j-1] = prob_sum_tot;
        if( i==0 && prob_sum_tot > 0.5 )
        {
          break;
        }
        else if( i>0 && prob_sum[j-1] < 0.0 )
        {
          string func_name  = "calc_mu_and_equivalent_prob_by_legendle_polynomial";
      
          ostringstream oss01, oss02;
          oss01.setf(ios::showpoint);
          oss01.setf(ios::scientific);
          oss01 << setw(10) << equivalent_prob[j-1];
          oss01 << mu_vec[j];
          oss02.setf(ios::showpoint);
          oss02.setf(ios::scientific);
          oss02 << setw(10) << equivalent_prob[j-1];
          string str_data01 = "Mu value                     : " + oss01.str();
          string str_data02 = "Equivalent probability value : " + oss02.str();

          vector<string> err_com;
          err_com.push_back(str_data01);
          err_com.push_back(str_data02);
          err_com.push_back("Equivalent probability value by legendle polynomial is less than 0.0.");
          err_obj.output_caution(class_name, func_name, err_com);
        }
      }
      prob_coef_pre = prob_coef_cur;
    }

    if( i == 0 )
    {
      //For i = 1 (To devide 1,000 data)
      Real mu_mid = mu_vec[mu_mid_pos];
      Real mu_fine_mid = 0.5 * static_cast<Real>(mu_no_fine);

      mu_delta = (mu_mid + 1.0) / mu_fine_mid;

      mu_mid_pos--;
      equivalent_prob.clear();
      prob_sum.clear();

      mu_vec.resize(mu_no_fine+1);
      equivalent_prob.resize(mu_no_fine);
      prob_sum.resize(mu_no_fine);
      mu_vec[0] = -1.0;
      int j_max = static_cast<int>(mu_fine_mid);
      for(int j=1; j<=j_max; j++)
      {
        mu_vec[j] = mu_vec[j-1] + mu_delta;
      }

      mu_delta = (1.0 - mu_mid) / mu_fine_mid;
      int j_min = j_max+1;
      for(int j=j_min; j<=mu_no_fine; j++)
      {
        mu_vec[j] = mu_vec[j-1] + mu_delta;
      }
    }
  }

  //Check sum value
  if( fabs(prob_sum_tot - 1.0) > 1.0E-5 )
  {
    string func_name  = "calc_mu_and_equivalent_prob_by_legendle_polynomial";

    ostringstream oss;
    oss.setf(ios::showpoint);
    oss.setf(ios::scientific);
    oss << setw(10) << prob_sum_tot;
    string str_data = "Sum of probability table : " + oss.str();

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("Sum of probability table by legendle polynomial is not equal to 1.0.");
    err_obj.output_caution(class_name, func_name, err_com);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::calc_equal_probability_table_by_tabulated_probability_data
                             ( vector<Integer>& tab_range_data, vector<Integer>& tab_int_data,
                               vector<Real>&    tab_mu_data,    vector<Real>&    tab_y_data )
{
  calc_equal_probability_table_by_tabulated_probability_data
    (tab_range_data, tab_int_data, tab_mu_data, tab_y_data, 0);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::calc_equal_probability_table_by_tabulated_probability_data
                             ( vector<Integer>& tab_range_data, vector<Integer>& tab_int_data,
                               vector<Real>& tab_mu_data, vector<Real>& tab_y_data, Integer err_opt )
{
  check_tabulated_probability_data(tab_range_data, tab_int_data, tab_mu_data, tab_y_data);
  if( static_cast<int>(tab_mu_data.size()) == 2 )
  {
    if( fabs(tab_y_data[0] - tab_y_data[1]) < min_value )
    {
      return;
    }
  }
  else if( static_cast<int>(tab_int_data.size()) == 0 )
  {
    return;
  }

  Real sum_val = integ_obj.integrate_tab1_data(tab_range_data, tab_int_data, tab_mu_data, tab_y_data);

  Real sum_ave = sum_val / static_cast<Real>(bin_no);

  Integer int_val = tab_int_data[0];
  lin_tab_obj.calc_equal_probability_table_by_tabulated_probability_data
                ( int_val, bin_no, sum_val, tab_mu_data, tab_y_data );

/*
  if( int_val == int_const )
  {
    calc_equal_probability_table_by_tabulated_probability_data_const(sum_ave, tab_mu_data, tab_y_data);
  }
  else if( int_val == int_lin_lin )
  {
    calc_equal_probability_table_by_tabulated_probability_data_lin_lin(sum_ave, tab_mu_data, tab_y_data);
  }
  else if( int_val == int_lin_log )
  {
    calc_equal_probability_table_by_tabulated_probability_data_lin_log(sum_ave, tab_mu_data, tab_y_data);
  }
  else
  {
    string func_name  = "calc_equal_probability_table_by_tabulated_probability_data";
    ostringstream oss01;
    oss01 << int_val;
    string str_data01 = "Interpolation type : " + oss01.str();
    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("This interpolation type is not available.");
    err_com.push_back("Available interpolation type is constant, linear-linear or linear-log.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
*/

  //Modify tab_y_data
  tab_y_data.clear();
  tab_y_data.resize(bin_no);
  for(int i=0; i<bin_no; i++)
  {
    tab_y_data[i] = sum_ave / (tab_mu_data[i+1] - tab_mu_data[i]);
  }

  if( err_opt > 0 )
  {
    if( fabs(tab_mu_data[bin_no] - 1.0) > min_value )
    {
      string func_name  = "calc_equal_probability_table_by_tabulated_probability_data";
      ostringstream oss;
      oss << setw(10) << tab_mu_data[bin_no];
      string str_data = "Maximum value of x data : " + oss.str();

      vector<string> err_com;
      err_com.push_back(str_data);
      err_com.push_back("The maximum value of x data is not equal to 1.0.");
      err_com.push_back("This calculation may be wrong.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }
  tab_mu_data.pop_back();

  //Modify int and range data
  tab_range_data.resize(1);
  tab_int_data.resize(1);
  tab_range_data[0] = static_cast<Integer>(bin_no);
  tab_int_data[0]   = int_const;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::check_tabulated_probability_data
                             ( vector<Integer>& tab_range_data, vector<Integer>& tab_int_data,
                               vector<Real>&    tab_mu_data,    vector<Real>&    tab_y_data )
{
  int i_max = static_cast<int>(tab_range_data.size());
  if( i_max == 1 )
  {
    if( tab_int_data[0] == int_log_lin || tab_int_data[0] == int_log_log )
    {
      string func_name  = "check_tabulated_probability_data";
      ostringstream oss;
      oss << tab_int_data[0];

      string str_data = "Interpolation type : " + oss.str();

      vector<string> err_com;
      err_com.push_back(str_data);
      err_com.push_back("Interpoltion type is only available for 1 (constant), 2 (linear-linear)");
      err_com.push_back("or 4 (linear-log).");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
    return;
  }
  else if( i_max > 2 )
  {
    string func_name  = "check_tabulated_probability_data";
    ostringstream oss;
    oss << i_max;

    string str_data = "Number of range : " + oss.str();

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("Number of range must be smaller than or equal to 2.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  if( tab_range_data[0] + 1 != tab_range_data[1] )
  {
    string func_name  = "check_tabulated_probability_data";
    ostringstream oss01, oss02;
    oss01 << tab_range_data[0];
    oss02 << tab_range_data[1];
    string str_data01 = "Range data at 1/2 : " + oss01.str();
    string str_data02 = "Range data at 2/2 : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("Range data at 2/2 must be [Range data at 1/2] + 1.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  if( tab_int_data[0] != int_const )
  {
    string func_name  = "check_tabulated_probability_data";
    ostringstream oss01, oss02;
    oss01 << tab_int_data[0];
    oss02 << tab_int_data[1];
    string str_data01 = "Interpolation type at 1/2 : " + oss01.str();
    string str_data02 = "Interpolation type at 2/2 : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("Interpolation type at 1/2 must be 1 (constant).");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  i_max = static_cast<int>(tab_mu_data.size());
  if( i_max < 2 )
  {
    string func_name  = "check_tabulated_probability_data";
    ostringstream oss01;
    oss01 << i_max;
    string str_data01 = "Data number of tab_mu_data : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("Data number of tab_mu_data must be larger than or equal to 2.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  if( fabs(tab_mu_data[i_max-1]) > min_value ||
      fabs(tab_mu_data[i_max-1] - tab_mu_data[i_max-2]) > fabs(min_value*tab_mu_data[i_max-1]) ||
      fabs(tab_y_data[i_max-1] - tab_y_data[i_max-2]) > fabs(min_value*tab_y_data[i_max-1]) )
  {
    string func_name  = "check_tabulated_probability_data";
    ostringstream oss01, oss02, oss03, oss04, oss05;
    oss01 << i_max;
    oss02 << tab_mu_data[i_max-1];
    oss03 << tab_mu_data[i_max-2];
    oss03 << tab_y_data[i_max-1];
    oss04 << tab_y_data[i_max-2];
    string str_data01 = "Data number of tab_mu_data (i_max) : " + oss01.str();
    string str_data02 = "tab_mu_data[i_max-1]               : " + oss02.str();
    string str_data03 = "tab_mu_data[i_max-2]               : " + oss03.str();
    string str_data04 = "tab_y_data[i_max-1]                : " + oss04.str();
    string str_data05 = "tab_y_data[i_max-2]                : " + oss05.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back(str_data05);
    if( fabs(tab_mu_data[i_max-1]) > min_value )
    {
      err_com.push_back("tab_mu_data[i_max-1] must be 0.0.");
    }
    if( fabs(tab_mu_data[i_max-1] - tab_mu_data[i_max-2]) > fabs(min_value*tab_mu_data[i_max-1]) )
    {
      err_com.push_back("tab_mu_data[i_max-2] must be equal to tab_mu_data[i_max-2].");
    }
    if( fabs(tab_y_data[i_max-1] - tab_y_data[i_max-2]) > fabs(min_value*tab_y_data[i_max-1]) )
    {
      err_com.push_back("tab_y_data[i_max-2] must be equal to tab_y_data[i_max-2].");
    }
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::calc_equal_probability_table_by_tabulated_probability_data_const
                             ( Real& sum_ave, vector<Real>& tab_mu_data, vector<Real>& tab_y_data )
{
  vector<Real> tab_mu_new;
  tab_mu_new.resize(bin_no+1);

  int  i_max    = static_cast<int>(tab_mu_data.size());
  int  ele_no   = 1;
  Real area     = 0.0;
  Real sum      = 0.0;
  Real residual = sum_ave;

  tab_mu_new[0]      = tab_mu_data[0];
  tab_mu_new[bin_no] = tab_mu_data[i_max-1];
  for(int i=0; i<i_max-1; i++)
  {
    area = tab_y_data[i]*(tab_mu_data[i+1] - tab_mu_data[i]);
    while( area > residual && ele_no < bin_no )
    {
      if( tab_y_data[i] < min_value )
      {
        if( i > 0 )
        {
          tab_y_data[i] = tab_y_data[i-1] * 1.0E-3;
        }
        else
        {
          tab_y_data[i] = min_value;
        }
      }
      tab_mu_new[ele_no] = (residual / tab_y_data[i]) + tab_mu_data[i];
      tab_mu_data[i]     = tab_mu_new[ele_no];

      area     = tab_y_data[i]*(tab_mu_data[i+1] - tab_mu_data[i]);
      sum      = 0.0;
      residual = sum_ave;
      ele_no++;
    }

    sum      += area;
    residual -= area;
    if( ele_no == 1 && sum < 1.0E-10 )
    {
      tab_mu_new[ele_no] = tab_mu_data[i+1];
    }
  }

  tab_mu_data = tab_mu_new;
  tab_mu_new.clear();

  if( fabs(sum) > 1.0E-5 )
  {
    string func_name  = "calc_equal_probability_table_by_tabulated_probability_data_const";

    ostringstream oss;
    oss << setw(10) << sum;
    string str_data = "Integrated area of distribution : " + oss.str();

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("The integrated area has large residual data.");
    err_com.push_back("This calculation may be wrong.");
    err_obj.output_caution(class_name, func_name, err_com);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::calc_equal_probability_table_by_tabulated_probability_data_lin_lin
                             ( Real& sum_ave, vector<Real>& tab_mu_data, vector<Real>& tab_y_data )
{
  vector<Real> tab_mu_new;
  tab_mu_new.resize(bin_no+1);

  int  i_max    = static_cast<int>(tab_mu_data.size());
  int  ele_no   = 1;
  Real area     = 0.0;
  Real sum      = 0.0;
  Real residual = sum_ave;
  Real min_val  = 1.0E-5;
  Real slope    = 0.0;

  tab_mu_new[0]      = tab_mu_data[0];
  tab_mu_new[bin_no] = tab_mu_data[i_max-1];
  for(int i=0; i<i_max-1; i++)
  {
    area = 0.5*(tab_y_data[i+1] + tab_y_data[i])*(tab_mu_data[i+1] - tab_mu_data[i]);
    while( area > residual && ele_no < bin_no )
    {
      if( residual < min_value )
      {
        tab_mu_new[ele_no] = tab_mu_data[i] + residual/tab_y_data[i];
      }
      else
      {
        slope = (tab_y_data[i+1] - tab_y_data[i])/(tab_mu_data[i+1] - tab_mu_data[i]);
        if( fabs(slope) < min_val )
        {
          if( tab_y_data[i] < min_value )
          {
            if( i > 0 )
            {
              tab_y_data[i] = tab_y_data[i-1] * 1.0E-3;
            }
            else
            {
              tab_y_data[i] = min_value;
            }
          }
          tab_mu_new[ele_no] = (residual / tab_y_data[i]) + tab_mu_data[i]; 
        }
        else
        {
          Real coef_a   = 0.5*slope;
          Real coef_b   = tab_y_data[i] - (slope * tab_mu_data[i]);
          Real coef_c   = (0.5*slope*tab_mu_data[i] - tab_y_data[i]) * tab_mu_data[i] - residual;
          Real sqrt_val = coef_b*coef_b - 4.0*coef_a*coef_c;
          if( sqrt_val < -1.0*min_value )
          {
            sqrt_val = 0.0;

            string func_name  = "calc_equal_probability_table_by_tabulated_probability_data_lin_lin";

            ostringstream oss01, oss02, oss03, oss04;
            oss01 << setw(10) << coef_a;
            oss02 << setw(10) << coef_b;
            oss03 << setw(10) << coef_c;
            oss04 << setw(10) << sqrt_val;
            string str_data01 = "Coefficient a                   : " + oss01.str();
            string str_data02 = "Coefficient b                   : " + oss02.str();
            string str_data03 = "Coefficient c                   : " + oss03.str();
            string str_data04 = "Square root value (b*b - 4*a*c) : " + oss04.str();

            vector<string> err_com;
            err_com.push_back("Imaginary number is observed.");
            err_com.push_back(str_data01);
            err_com.push_back(str_data02);
            err_com.push_back(str_data03);
            err_com.push_back(str_data04);
            err_com.push_back("This calculation may be wrong.");
            err_obj.output_caution(class_name, func_name, err_com);
          }
          else if( sqrt_val < min_value )
          {
            sqrt_val = 0.0;
          }

          sqrt_val = sqrt(sqrt_val);
          Real x_p = 0.5 * (-1.0*coef_b + sqrt_val) / coef_a;
          Real x_m = 0.5 * (-1.0*coef_b - sqrt_val) / coef_a;
          if( tab_mu_data[i] < x_p && x_p <= tab_mu_data[i+1] )
          {
            tab_mu_new[ele_no] = x_p;
          }
          if( tab_mu_data[i] < x_m && x_m <= tab_mu_data[i+1] )
          {
            tab_mu_new[ele_no] = x_m;
          }
        }
      }
      tab_y_data[i]  = tab_y_data[i] + slope*(tab_mu_new[ele_no] - tab_mu_data[i]);
      tab_mu_data[i] = tab_mu_new[ele_no];

      area     = 0.5*(tab_y_data[i+1] + tab_y_data[i])*(tab_mu_data[i+1] - tab_mu_data[i]);
      sum      = 0.0;
      residual = sum_ave;
      ele_no++;
    }

    sum      += area;
    residual -= area;
    if( ele_no == 1 && sum < 1.0E-10 )
    {
      tab_mu_new[ele_no] = tab_mu_data[i+1];
    }
  }

  tab_mu_data = tab_mu_new;
  tab_mu_new.clear();

  if( fabs(sum) > 1.0E-5 )
  {
    string func_name  = "calc_equal_probability_table_by_tabulated_probability_data_lin_lin";

    ostringstream oss;
    oss << setw(10) << sum;
    string str_data = "Integrated area of distribution : " + oss.str();

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("The integrated area has large residual data.");
    err_com.push_back("This calculation may be wrong.");
    err_obj.output_caution(class_name, func_name, err_com);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::calc_equal_probability_table_by_tabulated_probability_data_lin_log
                             ( Real& sum_ave, vector<Real>& tab_mu_data, vector<Real>& tab_y_data )
{
  vector<Real> tab_mu_new;
  tab_mu_new.resize(bin_no+1);

  int  i_max    = static_cast<int>(tab_mu_data.size());
  int  ele_no   = 1;
  Real coef_a   = 0.0;
  Real area     = 0.0;
  Real mu_mid   = 0.0;
  Real sum      = 0.0;
  Real residual = sum_ave;

  tab_mu_new[0]      = tab_mu_data[0];
  tab_mu_new[bin_no] = tab_mu_data[i_max-1];
  for(int i=0; i<i_max-1; i++)
  {
    coef_a = log(tab_y_data[i+1]/tab_y_data[i]) / (tab_mu_data[i+1] - tab_mu_data[i]);
    if( fabs(coef_a) < 1.0E-5 )
    {
      area = tab_y_data[i] * (tab_mu_data[i+1] - tab_mu_data[i]);
    }
    else
    {
      area = tab_y_data[i] * (exp(coef_a*(tab_mu_data[i+1] - tab_mu_data[i])) - 1.0)/coef_a;
    }

    while( area > residual && ele_no < bin_no )
    {
      if( fabs(coef_a) < 1.0E-5 )
      {
        mu_mid = residual/tab_y_data[i] + tab_mu_data[i];
      }
      else
      {
        mu_mid = log(coef_a*residual/tab_y_data[i] + 1.0)/coef_a + tab_mu_data[i];
      }

      tab_y_data[i]      = tab_y_data[i]*exp(coef_a*(mu_mid - tab_mu_data[i]));
      tab_mu_new[ele_no] = mu_mid;
      tab_mu_data[i]     = mu_mid;

      coef_a = log(tab_y_data[i+1]/tab_y_data[i]) / (tab_mu_data[i+1] - tab_mu_data[i]);
      if( fabs(coef_a) < 1.0E-5 )
      {
        area = tab_y_data[i] * (tab_mu_data[i+1] - tab_mu_data[i]);
      }
      else
      {
        area = tab_y_data[i] * (exp(coef_a*(tab_mu_data[i+1] - tab_mu_data[i])) - 1.0)/coef_a;
      }
      sum      = 0.0;
      residual = sum_ave;
      ele_no++;
    }

    sum      += area;
    residual -= area;
    if( ele_no == 1 && sum < 1.0E-10 )
    {
      tab_mu_new[ele_no] = tab_mu_data[i+1];
    }
  }

  tab_mu_data = tab_mu_new;
  tab_mu_new.clear();

  if( fabs(sum) > 1.0E-5 )
  {
    string func_name  = "calc_equal_probability_table_by_tabulated_probability_data_lin_log";

    ostringstream oss;
    oss << setw(10) << sum;
    string str_data = "Integrated area of distribution : " + oss.str();

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("The integrated area has large residual data.");
    err_com.push_back("This calculation may be wrong.");
    err_obj.output_caution(class_name, func_name, err_com);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::calc_total_gamma_product_xs()
{
  gamma_product_xs.clear();
  int i_max = static_cast<int>(union_ene_grid.size());
  gamma_product_xs.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    gamma_product_xs[i] = 0.0;
  }

  vector<CrossSectionDataContainer> xs_data_obj_vec_ori;
  xs_data_obj_vec_ori = nucl_data_obj.get_nucl_reaction_data_obj().get_xs_data_obj();

  vector<vector<Integer> > gam_int_vec, gam_range_vec;
  vector<vector<Real> >    gam_ene_vec, gam_data_vec;
  if( mf_12_data_no > 0 )
  {
    vector<Integer> react_vec;
    for(int i=0; i<reaction_type_no_int; i++)
    {
      react_vec.clear();
      react_vec.resize(1);

      react_vec[0] = photon_data_obj_vec[i].get_reaction_type();
      if( react_vec[0] == 460 || react_vec[0] != reaction_type_list[i] )
      {
        continue;
      }

      if( react_vec[0] == 3 )
      {
        react_vec.resize(2);
        react_vec[0] = 1;
        react_vec[1] = 2;
      }

      gam_int_vec   = photon_data_obj_vec[i].get_multiplicity_int_data();
      gam_range_vec = photon_data_obj_vec[i].get_multiplicity_range_data();
      gam_ene_vec   = photon_data_obj_vec[i].get_multiplicity_ene_data();
      gam_data_vec  = photon_data_obj_vec[i].get_multiplicity_data();

      int j_max = static_cast<int>(react_vec.size());
      for(int j=0; j<j_max; j++)
      {
        for(int k=0; k<reaction_type_no_int; k++)
        {
          if( reaction_type_list[k] == react_vec[j] )
          {
            if( reaction_type_list[k] == xs_data_obj_vec_ori[k].get_reaction_type() )
            {
              add_multiplied_xs_data
                (xs_data_obj_vec_ori[k], gam_range_vec, gam_int_vec, gam_ene_vec, gam_data_vec);
            }
            break;
          }
        }
      }
    }
  }

  for(int i=0; i<static_cast<int>(prod_distr_data_obj_mod_photon_vec.size()); i++)
  {
    gam_int_vec   = prod_distr_data_obj_mod_photon_vec[i].get_product_distr_int_data();
    gam_range_vec = prod_distr_data_obj_mod_photon_vec[i].get_product_distr_range_data();
    gam_ene_vec   = prod_distr_data_obj_mod_photon_vec[i].get_product_distr_ene_data();
    gam_data_vec  = prod_distr_data_obj_mod_photon_vec[i].get_product_distr_data();

    if( static_cast<int>(gam_int_vec.size()) > 0 )
    {
      Integer react_val = prod_distr_data_obj_mod_photon_vec[i].get_reaction_type();
      for(int j=0; j<reaction_type_no_int; j++)
      {
        if( react_val == xs_data_obj_vec_ori[j].get_reaction_type() )
        {
          add_multiplied_xs_data
            (xs_data_obj_vec_ori[j], gam_range_vec, gam_int_vec, gam_ene_vec, gam_data_vec);
          break;
        }
      }
    }
  }
  clr_obj.clear_vec_array2_int(gam_int_vec);
  clr_obj.clear_vec_array2_int(gam_range_vec);
  clr_obj.clear_vec_array2_real(gam_ene_vec);
  clr_obj.clear_vec_array2_real(gam_data_vec);

  vector<CrossSectionDataContainer>().swap(xs_data_obj_vec_ori);

  if( mf_13_data_no > 0 )
  {
    for(int i=0; i<reaction_type_no_int; i++)
    {
      if( reaction_type_list[i] == photon_data_obj_vec[i].get_reaction_type() )
      {
        modify_photon_production_xs_data_by_union_grid(photon_data_obj_vec[i]);
      }
    }

    for(int i=0; i<reaction_type_no_int; i++)
    {
      if( photon_data_obj_vec[i].get_reaction_type() == 1 )
      {
        modify_total_photon_production_xs_data(photon_data_obj_vec[i]);
        break;
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::add_multiplied_xs_data(CrossSectionDataContainer& xs_data_obj,
                             vector<vector<Integer> >& range_vec, vector<vector<Integer> >& int_vec,
                             vector<vector<Real> >&    ene_vec,   vector<vector<Real> >&    y_vec)
{
  int i_max = static_cast<int>(ene_vec.size());
  if( i_max == 0 )
  {
    return;
  }

  Integer         react_val    = xs_data_obj.get_reaction_type();
  vector<Integer> xs_int_vec   = xs_data_obj.get_xs_int_data();
  vector<Integer> xs_range_vec = xs_data_obj.get_xs_range_data();
  vector<Real>    xs_ene_vec   = xs_data_obj.get_xs_ene_data();
  vector<Real>    xs_vec       = xs_data_obj.get_xs_data();
  if( static_cast<int>(xs_ene_vec.size()) == 0 )
  {
    return;
  }

  Real ene_min = xs_ene_vec[0];
  int  j_max   = static_cast<int>(union_ene_grid.size());
  for(int i=0; i<i_max; i++)
  {
    if( static_cast<int>(ene_vec[i].size()) == 0 )
    {
      continue;
    }

    for(int j=0; j<j_max; j++)
    {
      Real uni_ene = union_ene_grid[j];
      if( uni_ene >= ene_min * (1.0-min_ene_dif) )
      {
        if( j == 0 )
        {
          uni_ene *= 1.0+min_ene_dif;
        }
        else if( j == j_max-1 )
        {
          uni_ene *= 1.0-min_ene_dif;
        }

        Real xs_val = 0.0;
        Real y_val  = 0.0;
        ti_obj.interpolation_tab1_in_range(uni_ene, xs_val, xs_range_vec, xs_int_vec, xs_ene_vec, xs_vec);
        ti_obj.interpolation_tab1_in_range(uni_ene, y_val,  range_vec[i], int_vec[i], ene_vec[i], y_vec[i]);

        if( j == 0 || uni_ene > ene_min * (1.0+min_ene_dif) )
        {
          if( react_val == 2 )
          {
            gamma_product_xs[j] -= xs_val*y_val;
          }
          else
          {
            gamma_product_xs[j] += xs_val*y_val;
          }
        }
      }
    }
  }
  xs_int_vec.clear();
  xs_range_vec.clear();
  xs_ene_vec.clear();
  xs_vec.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::modify_photon_production_xs_data_by_union_grid(PhotonDataContainer& photon_data_obj)
{
  vector<vector<Integer> > range_vec = photon_data_obj.get_photon_production_xs_range_data();
  vector<vector<Integer> > int_vec   = photon_data_obj.get_photon_production_xs_int_data();
  vector<vector<Real> >    ene_vec   = photon_data_obj.get_photon_production_xs_ene_data();
  vector<vector<Real> >    y_vec     = photon_data_obj.get_photon_production_xs_data();

  int i_max = static_cast<int>(ene_vec.size());
  if( i_max == 0 )
  {
    if( static_cast<int>(photon_data_obj.get_photon_production_xs_tot_ene_data().size()) == 0 )
    {
      return;
    }

    i_max = 1;
    range_vec.resize(i_max);
    int_vec.resize(i_max);
    ene_vec.resize(i_max);
    y_vec.resize(i_max);

    range_vec[0] = photon_data_obj.get_photon_production_xs_tot_range_data();
    int_vec[0]   = photon_data_obj.get_photon_production_xs_tot_int_data();
    ene_vec[0]   = photon_data_obj.get_photon_production_xs_tot_ene_data();
    y_vec[0]     = photon_data_obj.get_photon_production_xs_tot_data();
  }

  vector<vector<Integer> > range_vec_new, int_vec_new;
  vector<vector<Real> >    ene_vec_new,   y_vec_new;
  if( detailed_photon_flg != 0 )
  {
    range_vec_new.resize(i_max);
    int_vec_new.resize(i_max);
    ene_vec_new.resize(i_max);
    y_vec_new.resize(i_max);
  }

  int j_max = static_cast<int>(union_ene_grid.size());
  for(int i=0; i<i_max; i++)
  {
    if( static_cast<int>(ene_vec[i].size()) == 0 )
    {
      continue;
    }

    Real ene_min = ene_vec[i][0];
    for(int j=0; j<j_max; j++)
    {
      Real uni_ene = union_ene_grid[j];
      if( uni_ene >= ene_min * (1.0-min_ene_dif) )
      {
        if( j == 0 )
        {
          uni_ene *= 1.0+min_ene_dif;
        }
        else if( j == j_max-1 )
        {
          uni_ene *= 1.0-min_ene_dif;
        }

        Real y_val = 0.0;
        ti_obj.interpolation_tab1_in_range(uni_ene, y_val, range_vec[i], int_vec[i], ene_vec[i], y_vec[i]);

        if( j > 0 && uni_ene <= ene_min * (1.0+min_ene_dif) )
        {
          y_val = 0.0;
        }

        gamma_product_xs[j] += y_val;

        if( detailed_photon_flg != 0 )
        {
          ene_vec_new[i].push_back(uni_ene);
          y_vec_new[i].push_back(y_val);
        }
      }
    }

    if( detailed_photon_flg != 0 )
    {
      range_vec_new[i].resize(1);
      int_vec_new[i].resize(1);
      range_vec_new[i][0] = static_cast<Integer>(ene_vec_new[i].size());
      int_vec_new[i][0]   = int_lin_lin;
    }
  }

  photon_data_obj.set_photon_production_xs_range_data(range_vec_new);
  photon_data_obj.set_photon_production_xs_int_data(int_vec_new);
  photon_data_obj.set_photon_production_xs_ene_data(ene_vec_new);
  photon_data_obj.set_photon_production_xs_data(y_vec_new);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::modify_total_photon_production_xs_data(PhotonDataContainer& photon_data_obj)
{
  vector<Integer> xs_range_vec, xs_int_vec;
  xs_range_vec.resize(1);
  xs_int_vec.resize(1);
  xs_range_vec[0] = static_cast<int>(union_ene_grid.size());
  xs_int_vec[0]   = int_lin_lin;

  photon_data_obj.set_photon_production_xs_tot_int_data(xs_int_vec);
  photon_data_obj.set_photon_production_xs_tot_range_data(xs_range_vec);
  photon_data_obj.set_photon_production_xs_tot_ene_data(union_ene_grid);
  photon_data_obj.set_photon_production_xs_tot_data(gamma_product_xs);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::calc_multigroup_photon_data()
{
  if( mf_12_data_no == 0 && mf_13_data_no == 0 )
  {
    return;
  }

  modify_photon_angular_distribution_data_by_equal_probability_table();

  //For gendf data file
  //Modify multigroup photon data in GENDF file.
  //The GENDF file is not available in FRENDY.
  modify_multigroup_photon_data();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::modify_photon_angular_distribution_data_by_equal_probability_table()
{
  for(int i=0; i<reaction_type_no_int; i++)
  {
    if( reaction_type_list[i] == photon_data_obj_vec[i].get_reaction_type() )
    {
      if( photon_data_obj_vec[i].get_isotropic_flg() == 0 )
      {
        if( photon_data_obj_vec[i].get_angular_repr_flg() == 2 )
        {
          vector<vector<vector<Integer> > > tab_range_data, tab_int_data;
          vector<vector<vector<Real> > >    tab_mu_data, tab_y_data;
          tab_range_data = photon_data_obj_vec[i].get_angular_probability_range_data();
          tab_int_data   = photon_data_obj_vec[i].get_angular_probability_int_data();
          tab_mu_data    = photon_data_obj_vec[i].get_angular_probability_cos_data();
          tab_y_data     = photon_data_obj_vec[i].get_angular_probability_data();
          int j_max = static_cast<int>(tab_mu_data.size());
          for(int j=0; j<j_max; j++)
          {
            int k_max = static_cast<int>(tab_mu_data[j].size());
            for(int k=0; k<k_max; k++)
            {
              calc_equal_probability_table_by_tabulated_probability_data
                (tab_range_data[j][k], tab_int_data[j][k], tab_mu_data[j][k], tab_y_data[j][k]);
            }
          }
          photon_data_obj_vec[i].set_angular_probability_range_data(tab_range_data);
          photon_data_obj_vec[i].set_angular_probability_int_data(tab_int_data);
          photon_data_obj_vec[i].set_angular_probability_cos_data(tab_mu_data);
          photon_data_obj_vec[i].set_angular_probability_data(tab_y_data);
        }
        else
        {
          vector<vector<vector<Integer> > > tab_range_data, tab_int_data;
          vector<vector<vector<Real> > >    tab_mu_data, tab_y_data, list_data;
          list_data = photon_data_obj_vec[i].get_angular_legendre_coef_data();
          int j_max = static_cast<int>(list_data.size());
          tab_range_data.resize(j_max);
          tab_int_data.resize(j_max);
          tab_mu_data.resize(j_max);
          tab_y_data.resize(j_max);
          for(int j=0; j<j_max; j++)
          {
            int k_max = static_cast<int>(list_data[j].size());
            tab_range_data[j].resize(k_max);
            tab_int_data[j].resize(k_max);
            tab_mu_data[j].resize(k_max);
            tab_y_data[j].resize(k_max);
            for(int k=0; k<k_max; k++)
            {
              calc_equal_probability_table_by_legendle_polynomial
                (list_data[j][k], tab_range_data[j][k], tab_int_data[j][k],
                                  tab_mu_data[j][k],    tab_y_data[j][k]);
            }
          }
          photon_data_obj_vec[i].set_angular_probability_range_data(tab_range_data);
          photon_data_obj_vec[i].set_angular_probability_int_data(tab_int_data);
          photon_data_obj_vec[i].set_angular_probability_cos_data(tab_mu_data);
          photon_data_obj_vec[i].set_angular_probability_data(tab_y_data);
        }
      }
    }
  } 
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::modify_multigroup_photon_data()
{
  //For groupwise endf data
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::generate_fast_ace_data_from_modified_nucl_data_obj()
{
  set_fission_nu_data();

  check_cross_section_data_reaction_type();
  set_reaction_parameter();

  set_angular_distribution_data();
  set_energy_distribution_data();

  set_prob_table();
  set_delayed_neutron_data();
  set_photon_production_xs();

  if( detailed_photon_flg != 0 )
  {
    set_detailed_photon_production_data();
    set_photon_angular_distr();
  }

  int i_max = static_cast<int>(union_ene_grid.size());
  for(int i=0; i<i_max; i++)
  {
    union_ene_grid[i] *= unit_micro;
  }

  set_particle_production();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_title_data()
{
  ostringstream oss01, oss02;
  title_data.resize(3);

  //Copy suffix_za_id
  if( mcnpx_mode_flg == 0 )
  {
    oss01.width(9);
    oss01.precision(2);
    oss01 << fixed << suffix_za_id + izaid;
    if( sub_lib_part == 1 )
    {
      title_data[0] = oss01.str() + "c";
    }
    else if( sub_lib_part == 1001 )
    {
      title_data[0] = oss01.str() + "h";
    }
    else if( sub_lib_part == 1002 )
    {
      title_data[0] = oss01.str() + "o";
    }
    else if( sub_lib_part == 1003 )
    {
      title_data[0] = oss01.str() + "r";
    }
    else if( sub_lib_part == 2003 )
    {
      title_data[0] = oss01.str() + "s";
    }
    else if( sub_lib_part == 2004 )
    {
      title_data[0] = oss01.str() + "a";
    }
  }
  else
  {
    oss01.width(10);
    oss01.precision(3);
    oss01 << fixed << suffix_za_id + izaid;
    if( sub_lib_part == 0 )
    {
      title_data[0] = oss01.str() + "pc";
    }
    else if( sub_lib_part == 1 )
    {
      title_data[0] = oss01.str() + "nc";
    }
    else if( sub_lib_part == 1001 )
    {
      title_data[0] = oss01.str() + "hc";
    }
    else if( sub_lib_part == 1002 )
    {
      title_data[0] = oss01.str() + "dc";
    }
    else if( sub_lib_part == 1003 )
    {
      title_data[0] = oss01.str() + "tc";
    }
    else if( sub_lib_part == 2003 )
    {
      title_data[0] = oss01.str() + "sc";
    }
    else if( sub_lib_part == 2004 )
    {
      title_data[0] = oss01.str() + "ac";
    }
  }

  //Copy date
  string str_tmp = time_obj.get_current_date_no_slash();
  title_data[1]  = "  " + str_tmp;

  //Copy material data
  mat = nucl_data_obj.get_general_data_obj().get_mat_no();
  oss02 << setw(4) << setiosflags(ios::right) << mat;
  title_data[2] = "   mat" + oss02.str();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_fission_nu_data()
{
  //For number of neutrons per fission
  nu_bar_repr_flg = fis_data_obj.get_nu_bar_repr_flg();
  if( nu_bar_repr_flg == 1 )
  {
    nu_data = fis_data_obj.get_nu_bar_polynomial_coef();
    int i_max = static_cast<int>(nu_data.size());
    for(int i=1; i<i_max; i++)
    {
      nu_data[i] *= pow(unit_mega, i);
    }
  }
  else
  {
    nu_int_data   = fis_data_obj.get_nu_bar_int_data();
    nu_range_data = fis_data_obj.get_nu_bar_range_data();
    nu_ene_data   = fis_data_obj.get_nu_bar_ene_data();
    nu_data       = fis_data_obj.get_nu_bar_data();
    set_fission_nu_data_for_table(nu_range_data, nu_int_data, nu_ene_data, nu_data);
  }

  //For number of delayed neutrons per fission
  nu_d_bar_repr_flg = fis_data_obj.get_nu_d_bar_repr_flg();
  if( nu_d_bar_repr_flg == 1 )
  {
    vector<Real> nu_bar_poly = fis_data_obj.get_nu_d_bar_polynomial_coef();

    nu_d_bar_repr_flg = 2;
    nu_d_range_data.resize(1);
    nu_d_int_data.resize(1);
    nu_d_ene_data.resize(2);
    nu_d_data.resize(2);

    nu_d_range_data[0] = 2;
    nu_d_int_data[0]   = int_lin_lin;

    nu_d_ene_data[0] = ene_lower_limit * unit_micro;
    nu_d_ene_data[1] = ene_upper_limit * unit_micro;
    nu_d_data[0]     = nu_bar_poly[0];
    nu_d_data[1]     = nu_bar_poly[0];

    int i_max = static_cast<int>(nu_bar_poly.size());
    if( i_max > 0 )
    {
      string func_name  = "set_fission_nu_data()";
      ostringstream oss01, oss02;
      oss01 << i_max;
      oss02 << nu_bar_poly[0];
      string str_data01 = "Number of delayed neutrons per fission data (i_max) : " + oss01.str();
      string str_data02 = "Number of delayed neutrons per fission at i=0       : " + oss02.str();
      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back("The only first delayed neutron data is available in FRENDY.");
      err_obj.output_caution(class_name, func_name, err_com);
    }
  }
  else
  {
    nu_d_int_data   = fis_data_obj.get_nu_d_bar_int_data();
    nu_d_range_data = fis_data_obj.get_nu_d_bar_range_data();
    nu_d_ene_data   = fis_data_obj.get_nu_d_bar_ene_data();
    nu_d_data       = fis_data_obj.get_nu_d_bar_data();
    set_fission_nu_data_for_table(nu_d_range_data, nu_d_int_data, nu_d_ene_data, nu_d_data);
  }

  //For number of prompt neutrons per fission
  nu_p_bar_repr_flg = fis_data_obj.get_nu_p_bar_repr_flg();
  if( nu_p_bar_repr_flg == 1 )
  {
    nu_p_data = fis_data_obj.get_nu_p_bar_polynomial_coef();

    int i_max = static_cast<int>(nu_p_data.size());
    for(int i=1; i<i_max; i++)
    {
      nu_p_data[i] *= pow(unit_mega, i);
    }
  }
  else
  {
    nu_p_int_data   = fis_data_obj.get_nu_p_bar_int_data();
    nu_p_range_data = fis_data_obj.get_nu_p_bar_range_data();
    nu_p_ene_data   = fis_data_obj.get_nu_p_bar_ene_data();
    nu_p_data       = fis_data_obj.get_nu_p_bar_data();
    set_fission_nu_data_for_table(nu_p_range_data, nu_p_int_data, nu_p_ene_data, nu_p_data);
  }

  if( static_cast<int>(nu_data.size()) > 0 && static_cast<int>(nu_d_data.size()) > 0 &&
      static_cast<int>(nu_p_data.size()) > 0 )
  {
    if( nu_bar_repr_flg != 1 && nu_d_bar_repr_flg != 1 && nu_p_bar_repr_flg != 1 )
    {
      modify_fission_nu_data();
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_fission_nu_data_for_table
                             ( vector<Integer>& range_data, vector<Integer>& int_data,
                               vector<Real>&    ene_data,   vector<Real>&    nu_bar )
{
  string func_name = "set_fission_nu_data_for_table";

  //Check interpolation;
  Integer int_chk = integ_obj.check_interpolation(class_name, func_name, range_data, int_data, int_lin_lin);

  int i_max = static_cast<int>(ene_data.size());
  for(int i=0; i<i_max; i++)
  {
    ene_data[i] *= unit_micro;
  }

  if( int_chk == 0 )
  {
    range_data.resize(1);
    int_data.resize(1);
    range_data[0] = i_max;
    int_data[0]   = int_lin_lin;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::modify_fission_nu_data()
{
  vector<Integer> nu_range_mod = nu_range_data;
  vector<Integer> nu_int_mod   = nu_int_data;
  vector<Real>    nu_ene_mod   = nu_ene_data;
  vector<Real>    nu_mod       = nu_data;

  vector<Integer> nu_d_range_mod = nu_d_range_data;
  vector<Integer> nu_d_int_mod   = nu_d_int_data;
  vector<Real>    nu_d_ene_mod   = nu_d_ene_data;
  vector<Real>    nu_d_mod       = nu_d_data;

  vector<Integer> nu_p_range_mod = nu_p_range_data;
  vector<Integer> nu_p_int_mod   = nu_p_int_data;
  vector<Real>    nu_p_ene_mod   = nu_p_ene_data;
  vector<Real>    nu_p_mod       = nu_p_data;

  vector<Real> nu_ene_uni = nu_ene_mod;
  ta_obj.add_grid_data(nu_ene_uni, nu_d_ene_mod);
  ta_obj.add_grid_data(nu_ene_uni, nu_p_ene_mod);

  int i_max = static_cast<int>(nu_ene_uni.size());

  ta_obj.modify_x_grid(nu_ene_uni, nu_range_mod,   nu_int_mod,   nu_ene_mod,   nu_mod);
  ta_obj.modify_x_grid(nu_ene_uni, nu_d_range_mod, nu_d_int_mod, nu_d_ene_mod, nu_d_mod);
  ta_obj.modify_x_grid(nu_ene_uni, nu_p_range_mod, nu_p_int_mod, nu_p_ene_mod, nu_p_mod);

  int mod_flg = 0;
  vector<int>  mod_pos;
  vector<Real> nu_ori = nu_mod;

  mod_pos.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    mod_pos[i] = 0;
    if( nu_d_mod[i] > min_value )
    {
      if( fabs(nu_mod[i] - nu_p_mod[i]) < min_ene_dif ||
          fabs(nu_mod[i] - (nu_p_mod[i] + nu_d_mod[i])) > min_ene_dif )
      {
        nu_mod[i] = nu_p_mod[i] + nu_d_mod[i];

        mod_flg++;
        mod_pos[i] = 1;
      }
    }
  }

  if( mod_flg > 0 )
  {
    nu_range_data = nu_range_mod;
    nu_int_data   = nu_int_mod;
    nu_ene_data   = nu_ene_mod;
    nu_data       = nu_mod;

    string func_name  = "modify_fission_nu_data()";
    vector<string> err_com;
    err_com.push_back("nu_t != nu_p + nu_d");
    err_com.push_back("The number of neutron per fission (nu_t) is modified.");
    err_com.push_back("");
    err_com.push_back("i / i_max : ene : nu_d  nu_p  nu_t(ori) -> nu_t(mod)");

    for(int i=0; i<i_max; i++)
    {
      ostringstream oss01, oss02, oss_e, oss_d, oss_p, oss_t_o, oss_t_m;
      oss01 << i+1;
      oss02 << i_max;
      oss_e.setf(ios::showpoint);
      oss_e.setf(ios::scientific);
      oss_e.precision(8);
      oss_d.setf(ios::showpoint);
      oss_d.setf(ios::scientific);
      oss_d.precision(8);
      oss_p.setf(ios::showpoint);
      oss_p.setf(ios::scientific);
      oss_p.precision(8);
      oss_t_o.setf(ios::showpoint);
      oss_t_o.setf(ios::scientific);
      oss_t_o.precision(8);
      oss_t_m.setf(ios::showpoint);
      oss_t_m.setf(ios::scientific);
      oss_t_m.precision(8);
      oss_e   << nu_ene_mod[i];
      oss_d   << nu_d_mod[i];
      oss_p   << nu_p_mod[i];
      oss_t_o << nu_ori[i];
      oss_t_m << nu_mod[i];

      string str_data = oss01.str() + " / " + oss02.str() + " : " + oss_e.str() + " : "
                      + oss_d.str() + "  " + oss_p.str() + "  " + oss_t_o.str() + " -> " + oss_t_m.str(); 
      if( mod_pos[i] > 0 )
      {
        str_data = str_data + "  ***";
      }
      err_com.push_back(str_data);
    }

    err_obj.output_caution(class_name, func_name, err_com);
  }

  nu_range_mod.clear();
  nu_int_mod.clear();
  nu_ene_mod.clear();
  nu_mod.clear();
  nu_d_range_mod.clear();
  nu_d_int_mod.clear();
  nu_d_ene_mod.clear();
  nu_d_mod.clear();
  nu_p_range_mod.clear();
  nu_p_int_mod.clear();
  nu_p_ene_mod.clear();
  nu_p_mod.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::check_cross_section_data_reaction_type()
{
  ntr   = 0;
  nr    = 0;
  mtntr = 0;
  mtnr  = 0;
  for(int i=0; i<reaction_type_no_int; i++)
  {
    Integer react_val = reaction_type_list[i];
    if( react_val == xs_data_obj_vec[i].get_reaction_type() )
    {
      mtntr = react_val;
  
      if( react_val == 1 || react_val == 2 )
      {
        continue;
      }

      vector<Real> xs_vec = xs_data_obj_vec[i].get_xs_data();
      int j_max = static_cast<int>(xs_vec.size());
      if( j_max == 0 )
      {
        continue;
      }

      int zero_xs_flg = 0;
      for(int j=0; j<j_max; j++)
      {
        if( xs_vec[j] > min_value )
        {
          zero_xs_flg = 1;
          break;
        }
      }
      if( zero_xs_flg == 0 )
      {
        continue;
      }

      if( sub_lib_part == 1 )
      {
        if( react_val == 301 )
        {
          continue;
        }

        if( (react_val >=   5 && react_val <=  91) || (react_val >= 152 && react_val <= 154) ||
            (react_val >= 156 && react_val <= 181) || (react_val >= 183 && react_val <= 190) ||
            (react_val >= 194 && react_val <= 196) || (react_val >= 198 && react_val <= 200) ||
            (react_val >= 875 && react_val <= 899) )
        {
          nr++;
          if( mt_16_flg > 0 && react_val == 16 )
          {
            nr--;
          }
          mtnr = react_val;
        }
      }
      else if( sub_lib_part == 1001 )
      {
        if( react_val ==   5 || react_val ==  28 || react_val ==  41 || react_val ==  42 ||
            react_val ==  44 || react_val ==  45 || react_val == 103 || react_val == 111 ||
            react_val == 112 || react_val == 115 || react_val == 116 || react_val == 156 ||
            react_val == 159 || react_val == 162 || react_val == 163 || react_val == 164 ||
            react_val == 179 || react_val == 181 || react_val == 183 || react_val == 184 ||
            react_val == 186 || react_val == 190 || react_val == 191 || react_val == 194 ||
            react_val == 196 || react_val == 197 || react_val == 198 || react_val == 199 ||
            react_val == 200 || (react_val >= react_n_h1_min && react_val <= react_n_h1_max) )
        {
          nr++;
          mtnr = react_val;
        }
      }
      else if( sub_lib_part == 1002 )
      {
        if( react_val ==   5 || react_val ==  11 || react_val ==  32 || react_val ==  35 ||
            react_val == 104 || react_val == 114 || react_val == 115 || react_val == 117 ||
            react_val == 157 || react_val == 158 || react_val == 169 || react_val == 170 ||
            react_val == 171 || react_val == 182 || react_val == 183 || react_val == 185 ||
            react_val == 187 || react_val == 192 ||
           (react_val >= react_n_h2_min && react_val <= react_n_h2_max) )
        {
          nr++;
          mtnr = react_val;
        }
      }
      else if( sub_lib_part == 1003 )
      {
        if ( react_val ==   5 || react_val ==  33 || react_val ==  36 || react_val == 105 ||
             react_val == 113 || react_val == 116 || react_val == 154 || react_val == 155 ||
             react_val == 172 || react_val == 173 || react_val == 174 || react_val == 175 ||
             react_val == 182 || react_val == 184 || react_val == 185 || react_val == 188 ||
             react_val == 189 || (react_val >= react_n_h3_min && react_val <= react_n_h3_max) )
        {
          nr++;
          mtnr = react_val;
        }
      }
      else if( sub_lib_part == 2003 )
      {
        if ( react_val ==   5 || react_val ==  34 || react_val == 106 || react_val == 176 ||
             react_val == 177 || react_val == 178 || react_val == 186 || react_val == 187 ||
             react_val == 188 || react_val == 191 || react_val == 192 || react_val == 193 ||
             (react_val >= react_n_he3_min && react_val <= react_n_he3_max) )
        {
          nr++;
          mtnr = react_val;
        }
      }
      else if( sub_lib_part == 2004 )
      {
        if ( react_val ==   5 || (react_val >= 22 && react_val <= 25) || 
             react_val ==  29 || react_val ==  30 || react_val ==  35 || react_val ==  36 ||
             react_val ==  45 || react_val == 107 || react_val == 108 || react_val == 109 ||
             react_val == 112 || react_val == 113 || react_val == 114 || react_val == 117 ||
             react_val == 155 || react_val == 158 || react_val == 159 || react_val == 165 ||
             react_val == 166 || react_val == 167 || react_val == 168 || react_val == 180 ||
             react_val == 181 || react_val == 189 || react_val == 193 || react_val == 195 || 
             react_val == 196 || react_val == 199 ||
            (react_val >= react_n_he4_min && react_val <= react_n_he4_max) )
        {
          nr++;
          mtnr = react_val;
        }
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_reaction_parameter()
{
  react_type_list.clear();
  react_q_value.clear();
  react_type_ene_sta.clear();
  react_xs_tot.clear();
  react_xs_sc.clear();
  react_xs_heat.clear();
  react_xs_cap.clear();
  clr_obj.clear_vec_array2_real(react_xs);

  int ene_no = static_cast<int>(union_ene_grid.size());
  react_xs_tot.resize(ene_no);
  react_xs_sc.resize(ene_no);
  react_xs_heat.resize(ene_no);
  react_xs_cap.resize(ene_no);
  for(int i=0; i<ene_no; i++)
  {
    react_xs_tot[i]   = 0.0;
    react_xs_sc[i]    = 0.0;
    react_xs_heat[i]  = 0.0;
    react_xs_cap[i]   = 0.0;
  }

  set_reaction_parameter_sc();
  set_reaction_parameter_heat_cap();
  set_reaction_parameter_n_non_elastic_and_n_n();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_reaction_parameter_sc()
{
  int ene_no    = static_cast<int>(union_ene_grid.size());
  int react_flg = 0;
  for(int i=0; i<reaction_type_no_int; i++)
  {
    Integer react_val = reaction_type_list[i];
    if( react_val == xs_data_obj_vec[i].get_reaction_type() )
    {
      Integer skip_flg = check_reaction_parameter_sc(react_val);
      if( (react_flg > 0 && react_val > mtnr) || skip_flg != 0 )
      {
        continue;
      }
      react_flg++;

      Real            q_val    = xs_data_obj_vec[i].get_q_value() * unit_micro;
      vector<Integer> xs_range = xs_data_obj_vec[i].get_xs_range_data();
      vector<Integer> xs_int   = xs_data_obj_vec[i].get_xs_int_data();
      vector<Real>    xs_ene   = xs_data_obj_vec[i].get_xs_ene_data();
      vector<Real>    xs_data  = xs_data_obj_vec[i].get_xs_data();

      ta_obj.remove_zero_data(xs_range, xs_int, xs_ene, xs_data);
      if( static_cast<int>(xs_ene.size()) <= 2 )
      {
        if( static_cast<int>(xs_ene.size()) == 0 )
        {
          continue;
        }
        else if( static_cast<int>(xs_ene.size()) == 1 && xs_data[0] < min_value )
        {
          continue;
        }
        else if( static_cast<int>(xs_ene.size()) == 2 &&
                 xs_data[0] < min_value && xs_data[1] < min_value )
        {
          continue;
        }
      }

      int          ene_sta = -1;
      Real         ene_min = xs_ene[0];
      vector<Real> xs_tmp;
      xs_tmp.clear();
      for(int j=0; j<ene_no; j++)
      {
        if( ene_min > (1.0+min_ene_dif) * union_ene_grid[j] )
        {
          ene_sta = j;
          continue;
        }

        Real xs_val;
        ti_obj.interpolation_tab1(union_ene_grid[j], xs_val, xs_range, xs_int, xs_ene, xs_data);
        if( react_val == 2 )
        {
          react_xs_sc[j]   = xs_val;
          react_xs_tot[j] += xs_val;
        }
        else
        {
          if( (react_val >= 6 && react_val <= 9) || (react_val >= 46 && react_val <= 49) )
          {
            xs_val *= 0.5;
          }
          xs_tmp.push_back(xs_val);

          if( react_val >= 5 )
          {
            react_xs_tot[j] += xs_val;
          }
        }
      }

      if( react_val != 2 )
      {
        react_type_list.push_back(react_val);
        react_q_value.push_back(q_val);
        react_xs.push_back(xs_tmp);
        react_type_ene_sta.push_back(static_cast<Integer>(ene_sta + 1));
      }
    }
  }

  //update ntr
  ntr = static_cast<int>(react_type_list.size());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Integer FastAceDataGenerator::check_reaction_parameter_sc(Integer react_val)
{
  Integer skip_flg = 1;
  if( react_val == 1 )
  {
    return skip_flg;
  }

  if( sub_lib_part == 1 )
  {
    skip_flg = 0;
    if ( (react_val ==   3 || react_val ==   4) || (react_val  >  91 && react_val <= 151) ||
         (react_val == 155 || react_val == 182  ||  react_val == 191) ||
         (react_val == 192 || react_val == 193  ||  react_val == 197) ||
         (react_val >  200 && react_val <= 849) || (mt_16_flg > 0 && react_val == 16) )
    {
      skip_flg = 1;
    }
  }
  else if( sub_lib_part == 1001 )
  {
    if( react_val ==   2 || react_val ==   5 || react_val ==  28 || react_val ==  41 ||
        react_val ==  42 || react_val ==  44 || react_val ==  45 || react_val == 103 ||
        react_val == 111 || react_val == 112 || react_val == 115 || react_val == 116 ||
        react_val == 156 || react_val == 159 || react_val == 162 || react_val == 163 ||
        react_val == 164 || react_val == 179 || react_val == 181 || react_val == 183 ||
        react_val == 184 || react_val == 186 || react_val == 190 || react_val == 191 ||
        react_val == 194 || react_val == 196 || react_val == 197 || react_val == 198 ||
        react_val == 199 || react_val == 200 ||
        (react_val >= react_n_h1_min && react_val <= react_n_h1_max) )
    {
      skip_flg = 0;
    }
  }
  else if( sub_lib_part == 1002 )
  {
    if( react_val ==   2 || react_val ==   5 || react_val ==  32 || react_val ==  35 ||
        react_val == 104 || react_val == 114 || react_val == 115 || react_val == 117 ||
        react_val == 157 || react_val == 158 || react_val == 169 || react_val == 170 ||
        react_val == 171 || react_val == 182 || react_val == 183 || react_val == 185 ||
        react_val == 187 || react_val == 192 ||
       (react_val >= react_n_h2_min && react_val <= react_n_h2_max) )
    {
      skip_flg = 0;
    }
  }
  else if( sub_lib_part == 1003 )
  {
    if( react_val ==   2 || react_val ==   5 || react_val ==  33 || react_val ==  36 || 
        react_val == 105 || react_val == 113 || react_val == 116 || react_val == 154 ||
        react_val == 155 || react_val == 172 || react_val == 173 || react_val == 174 ||
        react_val == 175 || react_val == 182 || react_val == 184 || react_val == 185 ||
        react_val == 188 || react_val == 189 ||
       (react_val >= react_n_h3_min && react_val <= react_n_h3_max) )
    {
      skip_flg = 0;
    }
  }
  else if( sub_lib_part == 2003 )
  {
    if( react_val ==   2 || react_val ==   5 || react_val ==  34 || react_val == 106 ||
        react_val == 177 || react_val == 178 || react_val == 176 || react_val == 186 ||
        react_val == 187 || react_val == 188 || react_val == 191 || react_val == 192 ||
        react_val == 193 || (react_val >= react_n_he3_min && react_val <= react_n_he3_max) )
    {
      skip_flg = 0;
    }
  }
  else if( sub_lib_part == 2004 )
  {
    if( react_val ==   2 || react_val ==   5 || (react_val >= 22 && react_val <= 25) ||
        react_val ==  29 || react_val ==  30 || react_val ==  35 || react_val ==  36 ||
        react_val ==  45 || react_val == 107 || react_val == 108 || react_val == 109 ||
        react_val == 112 || react_val == 113 || react_val == 114 || react_val == 117 ||
        react_val == 155 || react_val == 158 || react_val == 159 || react_val == 165 ||
        react_val == 166 || react_val == 167 || react_val == 168 || react_val == 180 ||
        react_val == 181 || react_val == 189 || react_val == 193 || react_val == 195 ||
        react_val == 196 || react_val == 199 ||
       (react_val >= react_n_he4_min && react_val <= react_n_he4_max) )
    {
      skip_flg = 0;
    }
  }

  return skip_flg;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_reaction_parameter_heat_cap()
{
  int ene_no    = static_cast<int>(union_ene_grid.size());
  int react_flg = 0;
  for(int i=0; i<reaction_type_no_int; i++)
  {
    Integer react_val = reaction_type_list[i];
    if( react_val == xs_data_obj_vec[i].get_reaction_type() )
    {
      Integer skip_flg = check_reaction_parameter_heat_cap(react_val);
      if( (react_flg > 0 && react_val > mtntr) || skip_flg != 0 )
      {
        continue;
      }
      react_flg++;

      Real            q_val    = xs_data_obj_vec[i].get_q_value() * unit_micro;
      vector<Integer> xs_range = xs_data_obj_vec[i].get_xs_range_data();
      vector<Integer> xs_int   = xs_data_obj_vec[i].get_xs_int_data();
      vector<Real>    xs_ene   = xs_data_obj_vec[i].get_xs_ene_data();
      vector<Real>    xs_data  = xs_data_obj_vec[i].get_xs_data();

      ta_obj.remove_zero_data(xs_range, xs_int, xs_ene, xs_data);
      if( static_cast<int>(xs_ene.size()) <= 2 )
      {
        if( static_cast<int>(xs_ene.size()) == 0 )
        {
          continue;
        }
        else if( static_cast<int>(xs_ene.size()) == 1 && xs_data[0] < min_value )
        {
          continue;
        }
        else if( static_cast<int>(xs_ene.size()) == 2 &&
                 xs_data[0] < min_value && xs_data[1] < min_value )
        {
          continue;
        }
      }

      int          ene_sta = -1;
      Real         ene_min = xs_ene[0];
      vector<Real> xs_tmp;
      xs_tmp.clear();
      for(int j=0; j<ene_no; j++)
      {
        if( ene_min > (1.0+min_ene_dif) * union_ene_grid[j] )
        {
          ene_sta = j;
          continue;
        }

        Real xs_val;
        ti_obj.interpolation_tab1(union_ene_grid[j], xs_val, xs_range, xs_int, xs_ene, xs_data);
        if( react_val == 301 )
        {
          if( fabs(react_xs_tot[j]) < min_value )
          {
            react_xs_heat[j] = 0.0;
          }
          else
          {
            react_xs_heat[j] = xs_val * unit_micro / react_xs_tot[j];
          }
        }
        else
        {
          if( react_val == 444 )
          {
            xs_val *= unit_micro;
          }
          else if( react_val == 443 )
          {
            if( fabs(react_xs_tot[j]) < min_value )
            {
              xs_val = 0.0;
            }
            else
            {
              xs_val *= unit_micro / react_xs_tot[j];
            }
          }
          xs_tmp.push_back(xs_val);

          if( sub_lib_part == 1 )
          {
            if( (react_val >= 102 && react_val <= 150) || react_val == 155 || react_val == 182 ||
                 react_val == 191 || react_val == 192  || react_val == 193 || react_val == 197 ||
                (mt_103_flg ==  0 && react_val >= react_n_h1_min  && react_val <= react_n_h1_max)  ||
                (mt_104_flg ==  0 && react_val >= react_n_h2_min  && react_val <= react_n_h2_max)  ||
                (mt_105_flg ==  0 && react_val >= react_n_h3_min  && react_val <= react_n_h3_max)  ||
                (mt_106_flg ==  0 && react_val >= react_n_he3_min && react_val <= react_n_he3_max) ||
                (mt_107_flg ==  0 && react_val >= react_n_he4_min && react_val <= react_n_he4_max) )
            {
              react_xs_tot[j] += xs_val;
              react_xs_cap[j] += xs_val;
            }
            else if( (react_val >= 5 && react_val <= 150) || (react_val >= 152 && react_val <= 200) )
            {
              react_xs_tot[j] += xs_val;
            }
          }
          else
          {
            if( react_val <= 200 || react_val >= react_n_h1_min )
            {
              react_xs_tot[j] += xs_val;
              react_xs_cap[j] += xs_val;
            }
          }
        }
      }

      if( react_val != 301 )
      {
        react_type_list.push_back(react_val);
        react_q_value.push_back(q_val);
        react_xs.push_back(xs_tmp);
        react_type_ene_sta.push_back(static_cast<Integer>(ene_sta + 1));
      }
    }
  }

  //update ntr
  ntr = static_cast<int>(react_type_list.size());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Integer FastAceDataGenerator::check_reaction_parameter_heat_cap(Integer react_val)
{
  Integer skip_flg = 1;
  if( react_val == 1 )
  {
    return skip_flg;
  }

  skip_flg = 0; 
  if( sub_lib_part == 1 )
  {
    skip_flg = 1;
    if( (react_val > 91 && react_val < 152)   || react_val == 155 || react_val == 182 ||
         react_val == 191 || react_val == 192 || react_val == 193 || react_val == 197 ||
        (react_val > 200 && react_val < 850)  || (mt_16_flg > 0 && react_val == 16) )
    {
      skip_flg = 0;
    }
  }
  else if( sub_lib_part == 1001 )
  {
    if( react_val ==   2 || react_val ==   5 || react_val ==  28 || react_val ==  41 ||
        react_val ==  42 || react_val ==  44 || react_val ==  45 || react_val == 103 ||
        react_val == 111 || react_val == 112 || react_val == 115 || react_val == 116 ||
        react_val == 156 || react_val == 159 || react_val == 162 || react_val == 163 ||
        react_val == 164 || react_val == 179 || react_val == 181 || react_val == 183 ||
        react_val == 184 || react_val == 186 || react_val == 190 || react_val == 191 ||
        react_val == 194 || react_val == 196 || react_val == 197 || react_val == 198 ||
        react_val == 199 || react_val == 200 ||
        (react_val >= react_n_h1_min && react_val <= react_n_h1_max) )
    {
      skip_flg = 1;
    }
  }
  else if( sub_lib_part == 1002 )
  {
    if( react_val ==   2 || react_val ==   5 || react_val ==  11 || react_val ==  32 ||
        react_val ==  35 || react_val == 104 || react_val == 114 || react_val == 115 ||
        react_val == 117 || react_val == 157 || react_val == 158 || react_val == 169 ||
        react_val == 170 || react_val == 171 || react_val == 182 || react_val == 183 ||
        react_val == 185 || react_val == 187 || react_val == 192 ||
        (react_val >= react_n_h2_min && react_val <= react_n_h2_max) )
    {
      skip_flg = 1;
    }
  }
  else if( sub_lib_part == 1003 )
  {
    if( react_val ==   2 || react_val ==   5 || react_val ==  33 || react_val ==  36 ||
        react_val == 105 || react_val == 113 || react_val == 116 || react_val == 154 ||
        react_val == 155 || react_val == 172 || react_val == 173 || react_val == 174 ||
        react_val == 175 || react_val == 182 || react_val == 184 || react_val == 185 ||
        react_val == 188 || react_val == 189 ||
       (react_val >= react_n_h3_min && react_val <= react_n_h3_max) )
    {
      skip_flg = 1;
    }
  }
  else if( sub_lib_part == 2003 )
  {
    if( react_val ==   2 || react_val ==   5 || react_val ==  34 || react_val == 106 ||
        react_val == 176 || react_val == 177 || react_val == 178 || react_val == 186 ||
        react_val == 187 || react_val == 188 || react_val == 191 || react_val == 192 ||
        react_val == 193 || (react_val >= react_n_he3_min && react_val <= react_n_he3_max) )
    {
      skip_flg = 1;
    }
  }
  else if( sub_lib_part == 2004 )
  {
    if( react_val ==   2 || react_val ==   5 || (react_val >= 22 && react_val <= 25) ||
        react_val ==  29 || react_val ==  30 || react_val ==  35 || react_val ==  36 ||
        react_val ==  45 || react_val == 107 || react_val == 108 || react_val == 109 ||
        react_val == 112 || react_val == 113 || react_val == 114 || react_val == 117 ||
        react_val == 155 || react_val == 158 || react_val == 159 || react_val == 165 ||
        react_val == 166 || react_val == 167 || react_val == 168 || react_val == 180 ||
        react_val == 181 || react_val == 189 || react_val == 193 || react_val == 195 ||
        react_val == 196 || react_val == 199 ||
       (react_val >= react_n_he4_min && react_val <= react_n_he4_max) )
    {
      skip_flg = 1;
    }
  }
  return skip_flg;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_reaction_parameter_n_non_elastic_and_n_n()
{
  int ene_no = static_cast<int>(union_ene_grid.size());

  vector<CrossSectionDataContainer> xs_data_obj_vec_ori;
  xs_data_obj_vec_ori = nucl_data_obj.get_nucl_reaction_data_obj().get_xs_data_obj();

  for(int i=0; i<reaction_type_no_int; i++)
  {
    Integer react_val = reaction_type_list[i];
    if(react_val == 3 || (react_val == 4 && sub_lib_part == 1) )
    {
      if( react_val == xs_data_obj_vec_ori[i].get_reaction_type() )
      {
        Real            q_val;
        vector<Integer> xs_range, xs_int;
        vector<Real>    xs_ene,   xs_data;

        if( react_val == xs_data_obj_vec[i].get_reaction_type() )
        {
          q_val    = xs_data_obj_vec[i].get_q_value() * unit_micro;
          xs_range = xs_data_obj_vec[i].get_xs_range_data();
          xs_int   = xs_data_obj_vec[i].get_xs_int_data();
          xs_ene   = xs_data_obj_vec[i].get_xs_ene_data();
          xs_data  = xs_data_obj_vec[i].get_xs_data();
        }
        else if( nucl_data_obj.get_reso_data_obj().get_unreso_prob_data_obj().get_comp_flg_inela() == 4 ||
                 nucl_data_obj.get_reso_data_obj().get_unreso_prob_data_obj().get_comp_flg()%1000  == 4 )
        {
          q_val    = xs_data_obj_vec_ori[i].get_q_value() * unit_micro;
          xs_range = xs_data_obj_vec_ori[i].get_xs_range_data();
          xs_int   = xs_data_obj_vec_ori[i].get_xs_int_data();
          xs_ene   = xs_data_obj_vec_ori[i].get_xs_ene_data();
          xs_data  = xs_data_obj_vec_ori[i].get_xs_data();
        }
        else
        {
          continue;
        }

        ta_obj.remove_zero_data(xs_range, xs_int, xs_ene, xs_data);
        if( static_cast<int>(xs_ene.size()) <= 2 )
        {
          if( static_cast<int>(xs_ene.size()) == 0 )
          {
            continue;
          }
          else if( static_cast<int>(xs_ene.size()) == 1 && xs_data[0] < min_value )
          {
            continue;
          }
          else if( static_cast<int>(xs_ene.size()) == 2 &&
                   xs_data[0] < min_value && xs_data[1] < min_value )
          {
            continue;
          }
        }

        int          ene_sta = -1;
        Real         ene_min = xs_ene[0];
        vector<Real> xs_tmp;
        xs_tmp.clear();
        for(int j=0; j<ene_no; j++)
        {
          if( ene_min > (1.0+min_ene_dif) * union_ene_grid[j] )
          {
            ene_sta = j;
            continue;
          }
  
          Real xs_val;
          ti_obj.interpolation_tab1(union_ene_grid[j], xs_val, xs_range, xs_int, xs_ene, xs_data);
          xs_tmp.push_back(xs_val);
        }

        react_type_list.push_back(react_val);
        react_q_value.push_back(q_val);
        react_xs.push_back(xs_tmp);
        react_type_ene_sta.push_back(static_cast<Integer>(ene_sta + 1));
      }
    }
  }

  //update ntr
  ntr = static_cast<int>(react_type_list.size());

  vector<CrossSectionDataContainer>().swap(xs_data_obj_vec_ori);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_angular_distribution_data()
{
  int i_max = static_cast<int>(react_type_list.size());
  react_type_flg.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    react_type_flg[i] = 0;
  }

  i_max = nr+1;
  vector<Integer> react_type_list_mod;
  react_type_list_mod.resize(i_max);
  angular_distr_type_flg.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    angular_distr_type_flg[i] = 0;
    if( i == 0 )
    {
      react_type_list_mod[i] = 2;
    }
    else
    {
      react_type_list_mod[i] = react_type_list[i-1];
    }
  }

  angular_distr_int_data.resize(i_max);
  angular_distr_ene_data.resize(i_max);
  angular_distr_cos_data.resize(i_max);
  angular_distr_data.resize(i_max);
  angular_distr_data_integ.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    Integer react_val_mod = react_type_list_mod[i];
    for(int j=0; j<reaction_type_no_int; j++)
    {
      Integer react_val = reaction_type_list[j];
      if( react_val == react_val_mod )
      {
        if( react_val == ene_angle_data_obj_vec[j].get_reaction_type() )
        {
          if( ene_angle_data_obj_vec[j].get_angular_repr_flg() != 0 ||
              ene_angle_data_obj_vec[j].get_isotropic_flg()    != 0 ||
              ene_angle_data_obj_vec[j].get_ref_frame_flg()    != 0 )
          {
            angular_distr_type_flg[i] = 1;
            set_angular_distr_data(i, ene_angle_data_obj_vec[j]);
          }
        }

        if( react_val == prod_distr_data_obj_vec[j].get_reaction_type() )
        {
          angular_distr_type_flg[i] = 1;
          set_angular_distr_data(i, prod_distr_data_obj_vec[j]);
        }

        break;
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_angular_distr_data(int i, EnergyAngularDataContainer& ene_angle_data_obj)
{
  if( i > 0 )
  {
    react_type_flg[i-1] = check_react_type_flg( ene_angle_data_obj.get_reaction_type(),
                                                ene_angle_data_obj.get_ref_frame_flg() );
  }

  Integer iso_flg = ene_angle_data_obj.get_isotropic_flg();
  if( iso_flg == 1 )
  {
    angular_distr_type_flg[i] = 0;
  }
  else
  {
    if( sub_lib_part == 1 )
    {
      set_angular_distr_data_scatter(i, ene_angle_data_obj);
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_angular_distr_data
                             (int i, ProductDistributionDataContainer& prod_distr_data_obj)
{
  if( static_cast<int>(prod_distr_data_obj.get_distr_func_flg().size()) == 0 )
  {
    return;
  }

  if( i > 0 )
  {
    react_type_flg[i-1] = check_react_type_flg( prod_distr_data_obj.get_reaction_type(),
                                                prod_distr_data_obj.get_ref_frame_flg() );
  }

  if( prod_distr_data_obj.get_prompt_fis_n_flg() > 0 ||
      prod_distr_data_obj.get_prompt_fis_p_flg() > 0 )
  {
    angular_distr_type_flg[i] = 0;
    return;
  }

  Integer func_flg = prod_distr_data_obj.get_distr_func_flg()[0];
  if( func_flg == 1 || func_flg == 6 )
  {
    angular_distr_type_flg[i] = -1;
  }
  else if( func_flg == 3 )
  {
    angular_distr_type_flg[i] = 0;
  }
  else
  {
    if( sub_lib_part == 1 )
    {
      set_angular_distr_data_scatter(i, prod_distr_data_obj);
    }
    else
    {
      set_angular_distr_data_charged_particle_elastic_scatter(i, prod_distr_data_obj);
      adjust_total_scatter_xs_by_charged_particle_elastic_scatter(i, prod_distr_data_obj);
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Integer FastAceDataGenerator::check_react_type_flg(Integer reaction_type, Integer frame_flg)
{
  Integer react_flg = 0;
  if( reaction_type == 2 || reaction_type > 91 )
  {
    return react_flg;
  }

  react_flg = 1;
  if( (reaction_type >=  6 && reaction_type <=  9) || 
       reaction_type ==  0 || reaction_type == 11  ||  reaction_type == 16 || reaction_type == 24 ||
       reaction_type == 26 || reaction_type == 41  || (reaction_type >= 46 && reaction_type <= 49) )
  {
    react_flg = 2;
  }
  else if( reaction_type == 17 || reaction_type == 25 || reaction_type == 42 )
  {
    react_flg = 3;
  }
  else if( reaction_type == 37 )
  {
    react_flg = 4;
  }
  else if( (reaction_type >= 18 && reaction_type <= 21) || reaction_type == 38 )
  {
    react_flg = 19;
  }

  if( reaction_type != 18 && frame_flg >= 2 )
  {
    react_flg *= -1;
  }

  return react_flg;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_angular_distr_data_scatter
                            (int i, EnergyAngularDataContainer& ene_angle_data_obj)
{
  if( ene_angle_data_obj.get_angular_repr_flg() == 2 )
  {
    angular_distr_ene_data[i] = ene_angle_data_obj.get_angular_probability_ene_tab();
  }
  else
  {
    angular_distr_ene_data[i] = ene_angle_data_obj.get_angular_probability_ene_polynomial();
  }

  int j_max = static_cast<int>(angular_distr_ene_data[i].size());
  angular_distr_int_data[i].resize(j_max);
  angular_distr_cos_data[i].resize(j_max);
  angular_distr_data[i].resize(j_max);
  if( ene_angle_data_obj.get_angular_repr_flg() == 2 )
  {
    for(int j=0; j<j_max; j++)
    {
      vector<Integer> range_vec    = ene_angle_data_obj.get_angular_probability_range_data_tab()[j];
      vector<Integer> int_vec      = ene_angle_data_obj.get_angular_probability_int_data_tab()[j];
      angular_distr_int_data[i][j] = int_lin_lin;
      angular_distr_cos_data[i][j] = ene_angle_data_obj.get_angular_probability_cos_tab()[j];
      angular_distr_data[i][j]     = ene_angle_data_obj.get_angular_probability_data_tab()[j];
      lin_tab_obj.normalize_tab1_data(range_vec, int_vec,
                                      angular_distr_cos_data[i][j], angular_distr_data[i][j]);
    }
  }
  else //if( ene_angle_data_obj.get_angular_repr_flg() == 1 or 3 )
  {
    for(int j=0; j<j_max; j++)
    {
      vector<Real> list_vec = ene_angle_data_obj.get_angular_data_polynomial()[j];
      //string func_name = "set_angular_distr_data_scatter";
      //lin_tab_obj.check_legendre_polynomial_list_data
      //  (class_name, func_name, ene_angle_data_obj.get_reaction_type(),
      //   i, j, -1, -1, list_vec);

      if( generate_mode_flg == generate_default_mode )
      {
        lin_tab_obj.linearize_list_data_by_legendre_polynomial
                      (list_vec, angular_distr_cos_data[i][j], angular_distr_data[i][j]);
      }
      else //if( generate_mode_flg == generate_njoy_mode )
      {
        //Significant digits of intermediate point are limited to triple digits.
        lin_tab_obj.set_essential_fig(3);
        lin_tab_obj.linearize_list_data_by_legendre_polynomial
                      (list_vec, angular_distr_cos_data[i][j], angular_distr_data[i][j]);
        lin_tab_obj.set_essential_fig(lin_tab_obj.essential_fig_default);
      }

      angular_distr_int_data[i][j] = int_lin_lin;
    }
  }

  if( ene_angle_data_obj.get_angular_repr_flg() == 3 )
  {
    //Add table data for high energy region
    vector<Real> angular_distr_ene_data_high = ene_angle_data_obj.get_angular_probability_ene_tab();
    int ene_no_high = static_cast<int>(angular_distr_ene_data_high.size());
    int ene_no_tot  = j_max + ene_no_high;
    
    angular_distr_ene_data[i].resize(ene_no_tot);
    angular_distr_int_data[i].resize(ene_no_tot);
    angular_distr_cos_data[i].resize(ene_no_tot);
    angular_distr_data[i].resize(ene_no_tot);
    for(int j=j_max; j<ene_no_tot; j++)
    {
      int ele_no = j - j_max;
      angular_distr_ene_data[i][j] = angular_distr_ene_data_high[ele_no];

      vector<Integer> range_vec    = ene_angle_data_obj.get_angular_probability_range_data_tab()[ele_no];
      vector<Integer> int_vec      = ene_angle_data_obj.get_angular_probability_int_data_tab()[ele_no];
      angular_distr_int_data[i][j] = int_lin_lin;
      angular_distr_cos_data[i][j] = ene_angle_data_obj.get_angular_probability_cos_tab()[ele_no];
      angular_distr_data[i][j]     = ene_angle_data_obj.get_angular_probability_data_tab()[ele_no];
      lin_tab_obj.normalize_tab1_data(range_vec, int_vec,
                                      angular_distr_cos_data[i][j], angular_distr_data[i][j]);
    }
  }

  integrate_angular_distr_data_scatter(i);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_angular_distr_data_scatter
                             (int i, ProductDistributionDataContainer& prod_distr_data_obj)
{
  vector<Integer> func_flg = prod_distr_data_obj.get_distr_func_flg();
  if( static_cast<int>(func_flg.size()) == 0 )
  {
    return;
  }

  if( new_cummulative_angle_distr_flg != 0 && func_flg[0] != 7 )
  {
    vector<Integer> repr_flg;
    if( func_flg[0] == 2 )
    {
      repr_flg                  = prod_distr_data_obj.get_two_body_repr_flg()[0];
      angular_distr_ene_data[i] = prod_distr_data_obj.get_two_body_ene_data()[0];

      int j_max = static_cast<int>(repr_flg.size());
      angular_distr_int_data[i].resize(j_max);
      angular_distr_cos_data[i].resize(j_max);
      angular_distr_data[i].resize(j_max);
      for(int j=0; j<j_max; j++)
      {
        angular_distr_int_data[i][j] = 0;
        if( repr_flg[j] == 0 )
        {
          angular_distr_int_data[i][j] = int_lin_lin;
          vector<Real> legendre_coef = prod_distr_data_obj.get_two_body_legendre_coef()[0][j];

          //string func_name = "set_angular_distr_data_scatter";
          //lin_tab_obj.check_legendre_polynomial_list_data
          //  (class_name, func_name, prod_distr_data_obj.get_reaction_type(),
          //   i, j, -1, -1, legendre_coef);
          lin_tab_obj.linearize_list_data_by_legendre_polynomial
                        (legendre_coef, angular_distr_cos_data[i][j], angular_distr_data[i][j]);
        }
        else
        {
          angular_distr_int_data[i][j] = repr_flg[j]-10;
          angular_distr_cos_data[i][j] = prod_distr_data_obj.get_two_body_cos()[0][j];
          angular_distr_data[i][j]     = prod_distr_data_obj.get_two_body_prob()[0][j];
          lin_tab_obj.normalize_tab1_data
                       (angular_distr_int_data[i][j], angular_distr_cos_data[i][j], angular_distr_data[i][j]);
        }
      }
    }
    else if( func_flg[0] == 5 )
    {
      repr_flg                  = prod_distr_data_obj.get_charged_particle_repr_flg()[0];
      angular_distr_ene_data[i] = prod_distr_data_obj.get_charged_particle_ene_data()[0];

      int j_max = static_cast<int>(repr_flg.size());
      angular_distr_int_data[i].resize(j_max);
      angular_distr_cos_data[i].resize(j_max);
      angular_distr_data[i].resize(j_max);
      for(int j=0; j<j_max; j++)
      {
        angular_distr_int_data[i][j] = 0;
        if( repr_flg[j] > 2 )
        {
          angular_distr_int_data[i][j] = repr_flg[j]-10;
          angular_distr_cos_data[i][j] = prod_distr_data_obj.get_charged_particle_coef_mu()[0][j];
          angular_distr_data[i][j]     = prod_distr_data_obj.get_charged_particle_coef_p()[0][j];
          lin_tab_obj.normalize_tab1_data
                       (angular_distr_int_data[i][j], angular_distr_cos_data[i][j], angular_distr_data[i][j]);
        }
      }
    }
  }

  integrate_angular_distr_data_scatter(i);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::integrate_angular_distr_data_scatter(int i)
{
  int j_max = static_cast<int>(angular_distr_data[i].size());
  angular_distr_data_integ[i].resize(j_max);
  for(int j=0; j<j_max; j++)
  {
    angular_distr_ene_data[i][j] *= unit_micro;
    int k_max = static_cast<int>(angular_distr_data[i][j].size());
    for(int k=0; k<k_max; k++)
    {
      if( angular_distr_data[i][j][k] < min_value )
      {
        angular_distr_data[i][j][k] = 0.0;
      }
    }

    if( k_max <= 1 )
    {
      continue;
    }

    //Calculate integrated data
    string func_name  = "integrate_angular_distr_data_scatter";
    integ_obj.integrate_for_ace_data(class_name, func_name,
                                     angular_distr_cos_data[i][j],   angular_distr_data[i][j],
                                     angular_distr_data_integ[i][j], angular_distr_int_data[i][j]);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_angular_distr_data_charged_particle_elastic_scatter
                             (int i, ProductDistributionDataContainer& prod_distr_data_obj)
{
  vector<Integer> func_flg = prod_distr_data_obj.get_distr_func_flg();
  if( static_cast<int>(func_flg.size()) == 0 )
  {
    return;
  }
  else if( func_flg[0] != 5 )
  {
    string func_name  = "set_angular_distr_data_charged_particle_elastic_scatter";
    ostringstream oss01, oss02;
    oss01 << i+1;
    oss02 << func_flg[0];
    string str_data01 = "Position (i) : " + oss01.str();
    string str_data02 = "func_flg[0]  : " + oss02.str();
    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("This function is only available for the first LAW case.");
    err_com.push_back("func_flg (LAW) = 5 is only available");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  Real mass_coef     = nucl_data_obj.get_general_data_obj().get_mass()
                     / prod_distr_data_obj.get_mass_product()[0];
  Real mass_coef_inv = 1.0 / ((1.0 + mass_coef) * (1.0 + mass_coef));

  vector<vector<Real> > charged_particle_mass_data;
  angular_distr_ene_data[i]       = prod_distr_data_obj.get_charged_particle_ene_data()[0];
  charged_particle_mass_data      = prod_distr_data_obj.get_charged_particle_mass_data();

  int j_max = static_cast<int>(angular_distr_ene_data[i].size());
  charged_particle_mass_data[0].resize(j_max);
  angular_distr_int_data[i].resize(j_max);
  angular_distr_cos_data[i].resize(j_max);
  angular_distr_data[i].resize(j_max);
  angular_distr_data_integ[i].resize(j_max);
  for(int j=0; j<j_max; j++)
  {
    angular_distr_int_data[i][j] = int_lin_lin;

    linearize_charged_particle_elastic_scatter(j, prod_distr_data_obj);

    int  k_max   = static_cast<int>(union_ene_grid.size());
    int  ele_no  = -1;
    Real ene_val = angular_distr_ene_data[i][j];
    for(int k=1; k<k_max; k++)
    {
      if( ene_val <= union_ene_grid[k] )
      {
        ele_no = k;
        break;
      }
    }

    if( ele_no < 0 && ene_val < ene_max )
    {
      ele_no = k_max - 1;
    }

    if( ele_no < 0 )
    {
      string func_name  = "set_angular_distr_data_charged_particle_elastic_scatter";
      ostringstream oss01, oss02, oss03, oss04, oss05;
      oss01 << i+1;
      oss02 << j+1;
      oss03 << j_max;
      oss04 << ene_max;
      oss05 << angular_distr_ene_data[i][j];
      string str_data01 = "Position (i)                 : " + oss01.str();
      string str_data02 = "Position (j)                 : " + oss02.str() + " / " + oss03.str();
      string str_data03 = "Max union energy grid        : " + oss04.str();
      string str_data04 = "angular_distr_ene_data[i][j] : " + oss05.str();
      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back(str_data04);
      err_com.push_back("The union energy grid is less than angular_distr_ene_data[i][j].");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    Real ene_ratio = (union_ene_grid[ele_no]-ene_val) / (union_ene_grid[ele_no]-union_ene_grid[ele_no-1]);
    Real scat_xs   = react_xs_sc[ele_no-1]*ene_ratio + react_xs_sc[ele_no]*(1.0-ene_ratio);

    vector<Real> coef_mu = prod_distr_data_obj.get_charged_particle_coef_mu()[0][j];
    vector<Real> coef_p  = prod_distr_data_obj.get_charged_particle_coef_p()[0][j];
    k_max = static_cast<int>(coef_mu.size());

    Real sig_integ = 0.0;
    Real mu_pre    = 0.0;
    Real sig_pre   = 0.0;
    Real signi     = 0.0;
    Real sigc      = 0.0;
    Real sigc_pre  = 0.0;
    Real ratr      = 0.0;
    Real ratr_pre  = 0.0;
    Real eht       = 0.0;
    int  iterp     = 0;
    for(int k=0; k<k_max; k++)
    {
      Real    mu_val = coef_mu[k];
      Real    p_val  = coef_p[k];
      Integer loop_one = 0;
      while( loop_one == 0 )
      {
        Integer loop_two = 0;
        while( loop_two == 0 )
        {
          Integer charged_particle_flg, charged_particle_repr_flg;
          Real8   eta;
          sigc = calc_charged_particle_elastic_scatter_part
                   (j, mu_val, prod_distr_data_obj, charged_particle_flg, charged_particle_repr_flg, eta);
          if( charged_particle_repr_flg < 12 )
          {
            p_val -= sigc;
          }

          if( iterp == 1 )
          {
            signi = (ratr - 1.0) * sigc;
          }
          else
          {
            signi = p_val * scat_xs;
            if( signi < -1.0*sigc )
            {
              signi = -1.0*sigc;
            }
          }
          ratr = (sigc + signi) / sigc;

          loop_two = 1;
          if( k > 0 && iterp == 0 && sigc > fabs(signi) + min_value && sigc > (2.0*sigc_pre) )
          {
            iterp  = 1;
            mu_val = 0.5 * (mu_pre   + mu_val);
            ratr   = 0.5 * (ratr_pre + ratr);
            loop_two = 0;
          }
        }

        if( k > 0 )
        {
          sig_integ += 0.5 * (mu_val - mu_pre) * (signi + sigc + sig_pre);
          eht       += 0.5 * (mu_val - mu_pre) * ((1.0 - mu_val)*(signi + sigc) + (1.0-mu_pre)*sig_pre);
        }
        angular_distr_cos_data[i][j].push_back(mu_val);
        angular_distr_data[i][j].push_back(signi+sigc);
        angular_distr_data_integ[i][j].push_back(sig_integ);

        mu_pre   = mu_val;
        sigc_pre = sigc;
        sig_pre  = sigc + signi;
        ratr_pre = ratr;

        loop_one = 1;
        if( iterp == 1 )
        {
          iterp    = 0;
          loop_one = 0;
        }
      }
    }

    if( sub_lib_part != static_cast<Integer>(round(nucl_data_obj.get_general_data_obj().get_mat_data())) )
    {
      charged_particle_mass_data[0][j] = 4.0*mass_coef * ene_val*unit_micro * eht * M_PI * mass_coef_inv;
    }
    else
    {
      charged_particle_mass_data[0][j] = 0.0;
    }

    angular_distr_ene_data[i][j] *= unit_micro;
    k_max     = static_cast<int>(angular_distr_data[i][j].size());
    sig_integ = 1.0 / sig_integ;
    for(int k=0; k<k_max; k++)
    {
      angular_distr_data[i][j][k]       *= sig_integ;
      angular_distr_data_integ[i][j][k] *= sig_integ;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::linearize_charged_particle_elastic_scatter
                             (int j, ProductDistributionDataContainer& prod_distr_data_obj)
{
  Real err_min =  1.0E-3;
  Real mu_min  = -1.00;
  Real mu_max  =  0.96;
  if( static_cast<Integer>(round(nucl_data_obj.get_general_data_obj().get_mat_data())) == sub_lib_part )
  {
    mu_min = -1.0 * mu_max;
  }

  vector<Real> mu_vec, scat_vec;
  mu_vec.resize(2);
  scat_vec.resize(2);
  mu_vec[0]   = mu_max;
  mu_vec[1]   = mu_min;
  scat_vec[0] = calc_charged_particle_elastic_scatter(j, mu_vec[0], prod_distr_data_obj);
  scat_vec[1] = calc_charged_particle_elastic_scatter(j, mu_vec[1], prod_distr_data_obj);

  int ele_no = 1;
  while( ele_no > 0 )
  {
    Real delta_mu = mu_vec[ele_no-1] - mu_vec[ele_no];
    Real mid_mu   = 0.5 * (mu_vec[ele_no-1] + mu_vec[ele_no]);
    if( generate_mode_flg == generate_njoy_mode )
    {
      mid_mu = digit_obj.get_truncation_value(mid_mu, 3);
    }

    if( mid_mu > (1.0+err_min) * mu_vec[ele_no] && mid_mu < (1.0-err_min) * mu_vec[ele_no-1] )
    {
      Real mid_scat_lin = 0.5*(scat_vec[ele_no] + scat_vec[ele_no-1]);
      Real mid_scat_cal = calc_charged_particle_elastic_scatter(j, mid_mu, prod_distr_data_obj);
      Real mid_scat_dif = fabs(mid_scat_lin - mid_scat_cal);

      if( delta_mu > 0.01 || mid_scat_dif > err_min*fabs(mid_scat_cal) + min_ene_dif ||
         (fabs(mid_scat_lin) > min_value && mid_scat_cal/mid_scat_lin > 5.0) ||
         (fabs(mid_scat_lin) > min_value && mid_scat_cal/mid_scat_lin < 0.2) )
      {
        lin_tab_obj.insert_middle_x_data(ele_no-1, mu_vec, scat_vec, mid_mu, mid_scat_cal);
        ele_no++;
      }
      else
      {
        ele_no--;
      }
    }

    if( ele_no >= 20 )
    {
      break;
    }
  }

  //Reverse the order of mu_vec and scat_vec
  vector<Real8> mu_new, scat_new;
  int k_max = static_cast<int>(scat_vec.size());
  mu_new.resize(k_max);
  scat_new.resize(k_max);
  for(int k=0; k<k_max; k++)
  {
    mu_new[k]   = mu_vec[k_max-k-1];
    scat_new[k] = scat_vec[k_max-k-1];
  }
  mu_vec   = mu_new;
  scat_vec = scat_new;
  mu_new.clear();
  scat_new.clear();

  //Modify data to thin the distribution to a coarser tolerance
  thinning_charged_particle_elastic_scatter_data(mu_vec, scat_vec);

  //Copy new mu and scat data to prod_distr_data_obj
  vector<vector<vector<Real> > > charged_particle_coef_mu, charged_particle_coef_p;
  charged_particle_coef_mu = prod_distr_data_obj.get_charged_particle_coef_mu();
  charged_particle_coef_p  = prod_distr_data_obj.get_charged_particle_coef_p();
  charged_particle_coef_mu[0][j] = mu_vec;
  charged_particle_coef_p[0][j]  = scat_vec;
  prod_distr_data_obj.set_charged_particle_coef_mu(charged_particle_coef_mu);
  prod_distr_data_obj.set_charged_particle_coef_p(charged_particle_coef_p);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Real FastAceDataGenerator::calc_charged_particle_elastic_scatter
                             (int j, Real& mu_val, ProductDistributionDataContainer& prod_distr_data_obj)
{
  Integer charged_particle_flg, charged_particle_repr_flg;
  Real8   eta;
  Real    sigc     = calc_charged_particle_elastic_scatter_part
                       (j, mu_val, prod_distr_data_obj, charged_particle_flg, charged_particle_repr_flg, eta);

  Real  scat_val = 0.0;
  Real8 sigr     = 0.0;
  Real8 sigi     = 0.0;
  if( charged_particle_repr_flg == 1 )
  {
    vector<Real>  charged_particle_coef_b = prod_distr_data_obj.get_charged_particle_coef_b()[0][j];
    vector<Real>  charged_particle_coef_r = prod_distr_data_obj.get_charged_particle_coef_r()[0][j];
    vector<Real>  charged_particle_coef_i = prod_distr_data_obj.get_charged_particle_coef_i()[0][j];
    Integer       order                   = 2 * static_cast<Integer>(charged_particle_coef_r.size());
    vector<Real8> legendre_coef           = math_obj.legendre_expansion(mu_val, order);

    int ele_no = static_cast<int>(order/2);
    sigr = 0.5*charged_particle_coef_b[0];

    complex<Real8> carg1 = complex<Real8>(0.0, 1.0) * eta * log(0.5*(1.0-mu_val));
    complex<Real8> cs1   = 0.5*complex<Real8>(charged_particle_coef_r[0], charged_particle_coef_i[0]);
    for(int k=1; k<ele_no; k++)
    {
      cs1 += 0.5 * static_cast<Real>(2*k+1) * legendre_coef[k]
           * complex<Real8>(charged_particle_coef_r[k], charged_particle_coef_i[k]);
    }

    if( charged_particle_flg == 0 )
    {
      for(int k=1; k<ele_no*2; k++)
      {
        sigr += 0.5 * static_cast<Real8>(2*k+1) * legendre_coef[k] * charged_particle_coef_b[k];
      }

      cs1 *= exp(carg1);
      sigi = (-2.0*eta/(1.0-mu_val)) * cs1.real();
    }
    else if( charged_particle_flg == 1 )
    {
      for(int k=1; k<ele_no; k++)
      {
        sigr += 0.5 * static_cast<Real8>(4*k+1) * legendre_coef[2*k] * charged_particle_coef_b[k];
      }

      Real8          sgn = -1.0;
      complex<Real8> carg2 = complex<Real8>(0.0, 1.0) * eta * log(0.5*(1.0+mu_val));
      complex<Real8> cs2   = 0.5*complex<Real8>(charged_particle_coef_r[0], charged_particle_coef_i[0]);
      for(int k=1; k<ele_no; k++)
      {
        cs2 += 0.5 * sgn * static_cast<Real>(2*k+1) * legendre_coef[k]
             * complex<Real8>(charged_particle_coef_r[k], charged_particle_coef_i[k]);
        sgn *= -1.0;
      }

      cs1 *= (1.0+mu_val) * exp(carg1);
      cs2 *= (1.0-mu_val) * exp(carg2);
      sigi = (-2.0*eta/(1.0-mu_val*mu_val)) * cs1.real() * cs2.real();
    }
  }
  else if( charged_particle_repr_flg == 2 )
  {
    vector<Real>  charged_particle_coef_c = prod_distr_data_obj.get_charged_particle_coef_c()[0][j];
    Integer       order                   = 2 * static_cast<Integer>(charged_particle_coef_c.size());
    vector<Real8> legendre_coef           = math_obj.legendre_expansion(mu_val, order);

    sigr = 0.5 * charged_particle_coef_c[0];
    if( charged_particle_flg != 1 )
    {
      int ele_no = static_cast<int>(order);
      for(int k=1; k<ele_no; k++)
      {
        sigr += 0.5 * static_cast<Real>(2*k+1) * legendre_coef[k] * charged_particle_coef_c[k];
      }
    }
    else
    {
      int ele_no = static_cast<int>(order/2);
      for(int k=1; k<ele_no; k++)
      {
        sigr += 0.5 * static_cast<Real>(4*k+1) * legendre_coef[2*k] * charged_particle_coef_c[k];
      }
    }
  }

  scat_val = sigc + static_cast<Real>(sigr + sigi);

  return scat_val;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Real FastAceDataGenerator::calc_charged_particle_elastic_scatter_part
                             (int j, Real& mu_val, ProductDistributionDataContainer& prod_distr_data_obj,
                              Integer& charged_particle_flg, Integer& charged_particle_repr_flg, Real8& eta)
{
  charged_particle_flg      = prod_distr_data_obj.get_charged_particle_flg()[0];
  charged_particle_repr_flg = prod_distr_data_obj.get_charged_particle_repr_flg()[0][j];

  Real    ene_val             = prod_distr_data_obj.get_charged_particle_ene_data()[0][j];
  Real    mass_projectile_amu = nucl_data_obj.get_general_data_obj().get_mass_projectile() * amu_n;
  Real    mass_amu            = nucl_data_obj.get_general_data_obj().get_mass() * amu_n;
  Integer sub_lib_part_val    = sub_lib_part / 1000;
  Integer mat_data_val
            = static_cast<Integer>(round(nucl_data_obj.get_general_data_obj().get_mat_data())) / 1000;
  Real8 spin_no               = 2.0 * prod_distr_data_obj.get_spin_particle()[0];

  Real8 h_bar_sq_inv = 1.0 / h_bar*h_bar;
  Real8 cc1 = 2.0*amu*ev*1.0E-24 * h_bar_sq_inv;
  Real8 cc2 = (ev*1.0E-6)*light_speed;
        cc2 = 0.5 * cc2*cc2*cc2*cc2 * amu * h_bar_sq_inv / ev;
        eta = static_cast<Real8>(sub_lib_part_val*mat_data_val)*sqrt(cc2*mass_projectile_amu/ene_val);
  Real8 wn  = mass_amu*sqrt(cc1*mass_projectile_amu*ene_val) / (mass_projectile_amu + mass_amu);

  Real8 sigc = 0.0;
  if( charged_particle_flg == 0 )
  {
    sigc = (eta*eta/wn*wn)/((1.0-mu_val)*(1.0-mu_val));
  }
  else if( charged_particle_flg == 1 )
  {
    Real8 mu_sq = mu_val*mu_val;
    sigc = ((2.0*eta*eta/wn*wn) / (1.0-mu_sq))
         * ((1.0+mu_sq)/(1.0-mu_sq)
         + pow(-1.0,spin_no) * cos(eta*log((1.0+mu_val)/(1.0-mu_val)))/(2.0*spin_no+1.0));
  }

  Real sigc_real = static_cast<Real>(sigc);
  return sigc_real;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::thinning_charged_particle_elastic_scatter_data
                             (vector<Real>& mu_vec, vector<Real>& scat_vec)
{
  int i_max = static_cast<int>(mu_vec.size());

  vector<Real> mu_new, scat_new;
  for(int i=0; i<i_max-2; i++)
  {
    int  jj       = 0;
    Real check    = 0.0;
    Real delta_mu = 0.0;
    for(int j=i+2; j<i_max; j++)
    {
      jj       = j-1;
      delta_mu = mu_vec[j] - mu_vec[i];
      if( delta_mu <= 0.5 )
      {
        for(int k=i+1; k<j; k++)
        {
          Real coef_mu = (mu_vec[j] - mu_vec[k]) / delta_mu;
          check = fabs(coef_mu*scat_vec[i] + (1.0 - coef_mu)*scat_vec[j] - scat_vec[k])
                - 1.0E-2*fabs(scat_vec[k]);
          if( check > min_value )
          {
            break;
          }
        }
      }

      if( delta_mu > 0.5 || check > min_value )
      {
        break;
      }
    }

    if( delta_mu > 0.5 || check > min_value )
    {
      mu_new.push_back(mu_vec[jj]);
      scat_new.push_back(scat_vec[jj]);
    }
  }
  mu_new.push_back(mu_vec[i_max-1]);
  scat_new.push_back(scat_vec[i_max-1]);

  mu_vec   = mu_new;
  scat_vec = scat_new;
  mu_new.clear();
  scat_new.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::adjust_total_scatter_xs_by_charged_particle_elastic_scatter
                             (int i, ProductDistributionDataContainer& prod_distr_data_obj)
{
  vector<Real>    x_vec, y_vec;
  vector<Integer> range_vec, int_vec;
  int j_max = static_cast<int>(angular_distr_ene_data[i].size());
  x_vec.resize(j_max);
  y_vec.resize(j_max);
  for(int j=0; j<j_max; j++)
  {
    int k_max = static_cast<int>(angular_distr_data_integ[i][j].size());
    x_vec[j] = angular_distr_ene_data[i][j] * unit_mega;
    y_vec[j] = angular_distr_data_integ[i][j][k_max-1] * 2.0*M_PI;
  }
  range_vec.resize(1);
  int_vec.resize(1);
  range_vec[0] = static_cast<Integer>(j_max);
  int_vec[0]   = int_log_log;

  vector<Real> mass_ene_data = prod_distr_data_obj.get_charged_particle_ene_data()[0];
  vector<Real> mass_data     = prod_distr_data_obj.get_charged_particle_mass_data()[0];
  vector<Integer> mass_range_data, mass_int_data;
  mass_range_data.resize(1);
  mass_int_data.resize(1);
  mass_range_data[0] = static_cast<Integer>(mass_ene_data.size());
  mass_int_data[0]   = int_log_log;


  j_max = static_cast<int>(union_ene_grid.size());
  for(int j=0; j<j_max; j++)
  {
    Real ene_val = union_ene_grid[j];
    Real xs_scat = react_xs_sc[j];
    react_xs_tot[j] -= xs_scat;
 
    ti_obj.interpolation_tab1(ene_val, xs_scat, range_vec, int_vec, x_vec, y_vec);
    react_xs_tot[j] += xs_scat;
    react_xs_sc[j]   = xs_scat;

    Real xs_heat = 0.0;
    if( sub_lib_part > 2004 )
    {
      ti_obj.interpolation_tab1_in_range(ene_val, xs_heat,
                                         mass_range_data, mass_int_data, mass_ene_data, mass_data);
      xs_heat /= react_xs_tot[j];
    }
    react_xs_heat[j] = xs_heat;
  }  
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_energy_distribution_data()
{
  int i_max = nr;
  if( nr <= 0 )
  {
    return;
  }

  vector<Integer> react_type_list_mod;
  react_type_list_mod.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    react_type_list_mod[i] = react_type_list[i];
  }

  set_energy_distribution_resize_data(i_max);

  for(int i=0; i<i_max; i++)
  {
    for(int j=0; j<reaction_type_no_int; j++)
    {
      Integer react_val = reaction_type_list[j];
      if( react_val == react_type_list_mod[i] )
      {
        Real q_val = xs_data_obj_vec[j].get_q_value() * unit_micro;
 
        Integer set_energy_flg = 0;
        if( react_val == ene_angle_data_obj_vec[j].get_reaction_type() )
        {
          if( static_cast<int>(ene_angle_data_obj_vec[j].get_ene_repr_flg().size()) > 0 )
          {
            set_energy_flg = 1;
            set_energy_distr_data_from_ene_angle_data_obj(i, ene_angle_data_obj_vec[j], q_val);
          }
        }

        if( react_val == prod_distr_data_obj_vec[j].get_reaction_type() )
        {
          int distr_func_check_flg = 0;
          for(int k=0; k<static_cast<int>(react_type_list_two_body.size()); k++)
          {
            if( react_type_list_two_body[k] == react_val )
            {
              distr_func_check_flg = 1;
              break;
            }
          }

          if( distr_func_check_flg == 0 )
          {
            set_energy_flg = 2;
            set_energy_distr_data_from_prod_distr_data_obj(i, prod_distr_data_obj_vec[j], q_val);
          }
        }

        if( set_energy_flg == 0 )
        {
          set_energy_distr_data(i, react_val, q_val);
        }

        break;
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_energy_distribution_resize_data(int i_max)
{
  ene_distr_ene_repr_flg.resize(i_max);
  ene_distr_xs_part_int_data.resize(i_max);
  ene_distr_xs_part_range_data.resize(i_max);
  ene_distr_xs_part_ene_data.resize(i_max);
  ene_distr_xs_part_data.resize(i_max);

  prod_yield_tot_int_data.resize(i_max);
  prod_yield_tot_range_data.resize(i_max);
  prod_yield_tot_ene_data.resize(i_max);
  prod_yield_tot_data.resize(i_max);
  prod_distr_n_body_mass.resize(i_max);
  prod_distr_n_body_particle_no.resize(i_max);
  prod_distr_prob_data_no.resize(i_max);
  prod_distr_prob_ene_in_int_data.resize(i_max);
  prod_distr_prob_ene_in_range_data.resize(i_max);
  prod_distr_prob_ene_out_int_data.resize(i_max);
  prod_distr_prob_ene_in_data.resize(i_max);
  prod_distr_prob_ene_out_data.resize(i_max);
  prod_distr_prob_coef_a.resize(i_max);
  prod_distr_prob_coef_b.resize(i_max);
  prod_distr_prob_mu_int_data.resize(i_max);
  prod_distr_prob_mu_range_data.resize(i_max);
  prod_distr_prob_mu_data.resize(i_max);
  prod_distr_prob_mu_data_integ.resize(i_max);
  prod_distr_prob_data.resize(i_max);
  prod_distr_prob_data_integ.resize(i_max);
  prod_distr_prob_mu_vec.resize(i_max);
  prod_distr_prob_ene_out_vec.resize(i_max);
  prod_distr_prob_vec.resize(i_max);
  prod_distr_prob_vec_integ.resize(i_max);
  prod_distr_prob_int_vec.resize(i_max);
  prod_distr_prob_range_vec.resize(i_max);

  ene_distr_q_coef.resize(i_max);
  ene_distr_mass_coef.resize(i_max);
  ene_distr_ene_in_int_data.resize(i_max);
  ene_distr_ene_in_range_data.resize(i_max);
  ene_distr_ene_in_data.resize(i_max);
  ene_distr_ene_out_int_data.resize(i_max);
  ene_distr_ene_out_ene_data.resize(i_max);
  ene_distr_ene_out_data.resize(i_max);
  ene_distr_ene_out_data_integ.resize(i_max);
  ene_distr_temp_eff_int_data.resize(i_max);
  ene_distr_temp_eff_range_data.resize(i_max);
  ene_distr_temp_eff_ene_data.resize(i_max);
  ene_distr_temp_eff_data.resize(i_max);
  ene_distr_watt_a_int_data.resize(i_max);
  ene_distr_watt_a_range_data.resize(i_max);
  ene_distr_watt_a_ene_data.resize(i_max);
  ene_distr_watt_a_data.resize(i_max);
  ene_distr_watt_b_int_data.resize(i_max);
  ene_distr_watt_b_range_data.resize(i_max);
  ene_distr_watt_b_ene_data.resize(i_max);
  ene_distr_watt_b_data.resize(i_max);
  ene_distr_upper_ene_limit.resize(i_max);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_energy_distr_data(int i, Integer react_val, Real& q_val)
{
  ene_distr_ene_repr_flg[i].resize(1);
  ene_distr_xs_part_int_data[i].resize(1);
  ene_distr_xs_part_range_data[i].resize(1);
  ene_distr_xs_part_ene_data[i].resize(1);
  ene_distr_xs_part_data[i].resize(1);
  ene_distr_q_coef[i].resize(1);
  ene_distr_mass_coef[i].resize(1);

  ene_distr_ene_repr_flg[i][0] = 3;

  vector<Integer> int_vec, range_vec;
  int_vec.resize(1);
  range_vec.resize(1);
  int_vec[0]   = int_lin_lin;
  range_vec[0] = 2;

  vector<Real> ene_vec, distr_vec;
  ene_vec.resize(2);
  distr_vec.resize(2);
  int ene_no = static_cast<int>(union_ene_grid.size());
  if( react_val == 2 ) //For reaction type = 2
  {
    ene_vec[0] = union_ene_grid[0] * unit_micro;
  }
  else
  {
    ene_vec[0] = union_ene_grid[react_type_ene_sta[i]] * unit_micro;
  }
  ene_vec[1]   = union_ene_grid[ene_no-1] * unit_micro;
  distr_vec[0] = 1.0;
  distr_vec[1] = 1.0;
 
  ene_distr_xs_part_int_data[i][0]   = int_vec;
  ene_distr_xs_part_range_data[i][0] = range_vec;
  ene_distr_xs_part_ene_data[i][0]   = ene_vec;
  ene_distr_xs_part_data[i][0]       = distr_vec;

  Real mass_val = nucl_data_obj.get_general_data_obj().get_mass();
       mass_val = (mass_val + 1.0)/mass_val;

  ene_distr_q_coef[i][0]    = -1.0 * mass_val * q_val;
  ene_distr_mass_coef[i][0] = 1.0 / (mass_val*mass_val);
  if( ene_distr_q_coef[i][0] > ene_vec[0] )
  {
    ene_distr_q_coef[i][0] = ene_vec[0] * 0.999998;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_energy_distr_data_from_ene_angle_data_obj
                             (int i, EnergyAngularDataContainer& ene_angle_data_obj, Real& q_val)
{
  ene_distr_ene_repr_flg[i]       = ene_angle_data_obj.get_ene_repr_flg();
  ene_distr_xs_part_int_data[i]   = ene_angle_data_obj.get_xs_part_int_data();
  ene_distr_xs_part_range_data[i] = ene_angle_data_obj.get_xs_part_range_data();
  ene_distr_xs_part_ene_data[i]   = ene_angle_data_obj.get_xs_part_ene_data();
  ene_distr_xs_part_data[i]       = ene_angle_data_obj.get_xs_part_data();

  int j_max = static_cast<int>(ene_distr_xs_part_ene_data[i].size());
  for(int j=0; j<j_max; j++)
  {
    int k_max = static_cast<int>(ene_distr_xs_part_ene_data[i][j].size());
    for(int k=0; k<k_max; k++)
    {
      ene_distr_xs_part_ene_data[i][j][k] *= unit_micro;
    }
  }

  j_max = static_cast<int>(ene_distr_ene_repr_flg[i].size());
  //For ene_repr_flg = 1
  ene_distr_ene_in_int_data[i].resize(j_max);
  ene_distr_ene_in_range_data[i].resize(j_max);
  ene_distr_ene_in_data[i].resize(j_max);
  ene_distr_ene_out_int_data[i].resize(j_max);
  ene_distr_ene_out_ene_data[i].resize(j_max);
  ene_distr_ene_out_data[i].resize(j_max);
  ene_distr_ene_out_data_integ[i].resize(j_max);
  ene_distr_temp_eff_int_data[i].resize(j_max);
  ene_distr_temp_eff_range_data[i].resize(j_max);
  ene_distr_temp_eff_ene_data[i].resize(j_max);
  ene_distr_temp_eff_data[i].resize(j_max);
  ene_distr_watt_a_int_data[i].resize(j_max);
  ene_distr_watt_a_range_data[i].resize(j_max);
  ene_distr_watt_a_ene_data[i].resize(j_max);
  ene_distr_watt_a_data[i].resize(j_max);
  ene_distr_watt_b_int_data[i].resize(j_max);
  ene_distr_watt_b_range_data[i].resize(j_max);
  ene_distr_watt_b_ene_data[i].resize(j_max);
  ene_distr_watt_b_data[i].resize(j_max);
  ene_distr_upper_ene_limit[i].resize(j_max);

  for(int j=0; j<j_max; j++)
  {
    Integer ene_repr_flg = ene_distr_ene_repr_flg[i][j];
    if( ene_repr_flg == 1 )
    {
      ene_distr_ene_repr_flg[i][j] = 4;
      set_energy_distr_data_from_ene_angle_data_obj_arbitary_table(i, j, ene_angle_data_obj, q_val);
    }
    else if( ene_repr_flg == 7 || ene_repr_flg == 9 )
    {
      set_energy_distr_data_from_ene_angle_data_obj_maxwellian_or_evaporation_spectrum
        (i, j, ene_angle_data_obj, q_val);
    }
    else if( ene_repr_flg == 11 )
    {
      set_energy_distr_data_from_ene_angle_data_obj_watt_spectrum(i, j, ene_angle_data_obj, q_val);
    }
    else if( ene_repr_flg == 12 )
    {
      ene_distr_ene_repr_flg[i][j] = 4;
      set_energy_distr_data_from_ene_angle_data_obj_ene_depend_spectrum(i, j, ene_angle_data_obj, q_val);
    }
    else
    {
      string func_name  = "set_energy_distr_data_from_ene_angle_data_obj";
      ostringstream oss01, oss02;
      oss01 << ene_angle_data_obj.get_reaction_type();
      oss02 << ene_repr_flg;
      string str_data01 = "Reaction type              : " + oss01.str();
      string str_data02 = "Energy representation flag : " + oss02.str();
      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back("Energy representation flag is only available for 1, 7, 9, 11 and 12.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

//For ene_repr_flg = 1 (Tabulated Distributions)
//Note that ene_repr_flg is changed to 4 in ACE format.
void FastAceDataGenerator::set_energy_distr_data_from_ene_angle_data_obj_arbitary_table
                             (int i, int j, EnergyAngularDataContainer& ene_angle_data_obj, Real& q_val)
{
  string func_name  = "set_energy_distr_data_from_ene_angle_data_obj_arbitary_table";

  ene_distr_ene_in_int_data[i][j]   = ene_angle_data_obj.get_ene_int_data()[j];
  ene_distr_ene_in_range_data[i][j] = ene_angle_data_obj.get_ene_range_data()[j];
  ene_distr_ene_in_data[i][j]       = ene_angle_data_obj.get_incident_ene()[j];
  ene_distr_ene_out_ene_data[i][j]  = ene_angle_data_obj.get_ene_part_ene_data()[j];
  ene_distr_ene_out_data[i][j]      = ene_angle_data_obj.get_ene_part_data()[j];

  int k_max = static_cast<int>(ene_distr_ene_in_int_data[i][j].size());
  for(int k=0; k<k_max; k++)
  {
    if( ene_distr_ene_in_int_data[i][j][k] > 10 )
    {
      ene_distr_ene_in_int_data[i][j][k] = ene_distr_ene_in_int_data[i][j][k]%10;
    }
  }

  vector<int> pos_data;
  pos_data.resize(3);
  pos_data[0] = i;
  pos_data[1] = j;
  Integer reaction_type = ene_angle_data_obj.get_reaction_type();
          k_max         = static_cast<int>(ene_distr_ene_in_data[i][j].size());
  ene_distr_ene_out_int_data[i][j].resize(k_max);
  ene_distr_ene_out_data_integ[i][j].resize(k_max);
  for(int k=0; k<k_max; k++)
  {
    ene_distr_ene_in_data[i][j][k] *= unit_micro;

    pos_data[2] = k;
    vector<Integer> range_data = ene_angle_data_obj.get_ene_part_range_data()[j][k];
    vector<Integer> int_data   = ene_angle_data_obj.get_ene_part_int_data()[j][k];
    ene_distr_ene_out_int_data[i][j][k]
      = integ_obj.check_interpolation(class_name, func_name, reaction_type, pos_data, range_data, int_data);

    if( ene_angle_data_obj.get_reaction_type() == 18 && ene_distr_ene_out_int_data[i][j][k] == int_lin_lin )
    {
      modify_prompt_xi_spectrum(i, j, k);
    }

    int l_max = static_cast<int>(ene_distr_ene_out_ene_data[i][j][k].size());
    for(int l=0; l<l_max; l++)
    {
      ene_distr_ene_out_ene_data[i][j][k][l] *= unit_micro;
      ene_distr_ene_out_data[i][j][k][l]     *= unit_mega;
      if( ene_distr_ene_out_data[i][j][k][l] < min_value )
      {
        ene_distr_ene_out_data[i][j][k][l] = 0.0;
      }

      if( ene_distr_ene_out_ene_data[i][j][k][l] > ene_distr_ene_in_data[i][j][k] &&
          q_val < -1.0*min_value )
      {
        Real ene_part_ene_mod = ene_distr_ene_in_data[i][j][k] - static_cast<Real>((l_max-l-1))*1.0E-3;

        ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07, oss08, oss09;
        oss01 << i+1;
        oss02 << j+1;
        oss03 << k+1;
        oss04 << l+1;
        oss05 << l_max;
        oss06 << q_val;
        oss07 << ene_distr_ene_in_data[i][j][k];
        oss08 << ene_distr_ene_out_ene_data[i][j][k][l];
        oss09 << ene_part_ene_mod;
        string str_data01 = "Element i                 : " + oss01.str();
        string str_data02 = "Element j                 : " + oss02.str();
        string str_data03 = "Element k                 : " + oss03.str();
        string str_data04 = "Element l                 : " + oss04.str() + " / " + oss05.str();
        string str_data05 = "Q value                   : " + oss06.str();
        string str_data06 = "Incident energy           : " + oss07.str();
        string str_data07 = "Secondary energy          : " + oss08.str();
        string str_data08 = "Modified secondary energy : " + oss09.str();
        vector<string> err_com;
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back(str_data04);
        err_com.push_back(str_data05);
        err_com.push_back(str_data06);
        err_com.push_back(str_data07);
        err_com.push_back(str_data08);
        err_com.push_back("Incident energy is less than secondary energy and q_value is less than 0.0.");
        err_com.push_back("Secondary energy is modified.");
        err_obj.output_caution(class_name, func_name, err_com);

        ene_distr_ene_out_ene_data[i][j][k][l] = ene_part_ene_mod;
      }
    }

    Real sum = 0.0;
    integ_obj.integrate_for_ace_data(class_name, func_name,
                ene_distr_ene_out_ene_data[i][j][k],   ene_distr_ene_out_data[i][j][k],
                ene_distr_ene_out_data_integ[i][j][k], ene_distr_ene_out_int_data[i][j][k], sum);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::modify_prompt_xi_spectrum(int i, int j, int k)
{
  int         l_max = static_cast<int>(ene_distr_ene_out_ene_data[i][j][k].size());
  vector<int> modify_pos_vec;

  modify_pos_vec.clear();
  for(int l=0; l<l_max-1; l++)
  {
    if( ene_distr_ene_out_ene_data[i][j][k][l] < 9.99E+6 )
    {
      continue;
    }

    if( ene_distr_ene_out_ene_data[i][j][k][l+1] - ene_distr_ene_out_ene_data[i][j][k][l] > 2.0E+5 )
    {
      modify_pos_vec.push_back(l);
    }
  }

  int mod_pos_no = static_cast<int>(modify_pos_vec.size());
  if( mod_pos_no == 0 )
  {
    return;
  }

  int     add_no  = 4;
  Integer int_ori = int_lin_lin;
  if( generate_mode_flg == generate_default_mode )
  {
    return;
  }
  else //if( generate_mode_flg == generate_njoy_mode )
  {
    int_ori = int_lin_log;
  }
  
  string func_name = "modify_prompt_xi_spectrum";
  ostringstream oss01, oss02, oss03;
  oss01 << i+1;
  oss02 << j+1;
  oss03 << k+1;
  string str_data01 = "Element i : " + oss01.str();
  string str_data02 = "Element j : " + oss02.str();
  string str_data03 = "Element k : " + oss03.str();
  vector<string> err_com;
  err_com.push_back(str_data01);
  err_com.push_back(str_data02);
  err_com.push_back(str_data03);
  err_com.push_back("The prompt xi spectrum grid above 10MeV has large energy grid distance.");
  err_com.push_back("(Energy grid distance is larger than 200keV.)");
  err_com.push_back("The prompt xi spectrum grid may not be appropriate.");

  if( generate_mode_flg == generate_njoy_mode )
  {
    err_com.push_back("The prompt xi spectrum grid above 10MeV is modified using exponential shape,");
    err_com.push_back("if energy grid distance is larger than 200keV.)");
  }
  err_obj.output_caution(class_name, func_name, err_com);

  //Add energy grid
  vector<Real> ene_out_ene_vec, ene_out_vec, ene_out_ene_vec_new, ene_out_vec_new;
  ene_out_ene_vec = ene_distr_ene_out_ene_data[i][j][k];
  ene_out_vec     = ene_distr_ene_out_data[i][j][k];

  int     ele_no         = l_max + add_no*mod_pos_no;
  ene_out_ene_vec_new.resize(ele_no);
  ene_out_vec_new.resize(ele_no);

       ele_no         = 0;
  int  l              = 0;
  Real delta_ene_coef = 1.0 / static_cast<Real>(add_no+1);
  for(int m=0; m<mod_pos_no; m++)
  {
    while( l <= modify_pos_vec[m] )
    {
      ene_out_ene_vec_new[ele_no] = ene_out_ene_vec[l];
      ene_out_vec_new[ele_no]     = ene_out_vec[l];
      ele_no++;
      l++;
    }

    Real    delta_ene = delta_ene_coef * (ene_out_ene_vec[l] - ene_out_ene_vec[l-1]);
    Integer int_val   = int_ori;
    if( ene_out_vec[l] < min_value || ene_out_vec[l-1] < min_value )
    {
      int_val = int_lin_lin;
    }

    for(int n=0; n<add_no; n++)
    {
      ene_out_ene_vec_new[ele_no] = ene_out_ene_vec[l-1] + static_cast<Real>(n+1) * delta_ene;
      ti_obj.interpolation_1d(int_val, ene_out_ene_vec_new[ele_no], ene_out_vec_new[ele_no],
                              ene_out_ene_vec, ene_out_vec);
      ele_no++;
    }
  }

  while( l < l_max )
  {
    ene_out_ene_vec_new[ele_no] = ene_out_ene_vec[l];
    ene_out_vec_new[ele_no]     = ene_out_vec[l];
    ele_no++;
    l++;
  }

  ene_distr_ene_out_ene_data[i][j][k] = ene_out_ene_vec_new;
  ene_distr_ene_out_data[i][j][k]     = ene_out_vec_new;

  ene_out_ene_vec.clear();
  ene_out_vec.clear();
  ene_out_ene_vec_new.clear();
  ene_out_vec_new.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

//For ene_repr_flg = 7 or 9 (Simple Maxwellian Fission Spectrum or Evaporation Spectrum)
void FastAceDataGenerator::set_energy_distr_data_from_ene_angle_data_obj_maxwellian_or_evaporation_spectrum
                             (int i, int j, EnergyAngularDataContainer& ene_angle_data_obj, Real& q_val)
{
  ene_distr_upper_ene_limit[i][j]     = ene_angle_data_obj.get_upper_ene_limit()[j] * unit_micro;
  ene_distr_temp_eff_int_data[i][j]   = ene_angle_data_obj.get_temp_eff_int_data()[j];
  ene_distr_temp_eff_range_data[i][j] = ene_angle_data_obj.get_temp_eff_range_data()[j];
  ene_distr_temp_eff_ene_data[i][j]   = ene_angle_data_obj.get_temp_eff_ene_data()[j];
  ene_distr_temp_eff_data[i][j]       = ene_angle_data_obj.get_temp_eff_data()[j];

  int k_max = static_cast<int>(ene_distr_temp_eff_ene_data[i][j].size());
  for(int k=0; k<k_max; k++)
  {
    ene_distr_temp_eff_ene_data[i][j][k] *= unit_micro;
    ene_distr_temp_eff_data[i][j][k]     *= unit_micro;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

//For ene_repr_flg = 11 (Energy-Dependent Watt Spectrum)
void FastAceDataGenerator::set_energy_distr_data_from_ene_angle_data_obj_watt_spectrum
                             (int i, int j, EnergyAngularDataContainer& ene_angle_data_obj, Real& q_val)
{
  ene_distr_upper_ene_limit[i][j]   = ene_angle_data_obj.get_upper_ene_limit()[j] * unit_micro;
  ene_distr_watt_a_int_data[i][j]   = ene_angle_data_obj.get_watt_a_int_data()[j];
  ene_distr_watt_a_range_data[i][j] = ene_angle_data_obj.get_watt_a_range_data()[j];
  ene_distr_watt_a_ene_data[i][j]   = ene_angle_data_obj.get_watt_a_ene_data()[j];
  ene_distr_watt_a_data[i][j]       = ene_angle_data_obj.get_watt_a_data()[j];
  ene_distr_watt_b_int_data[i][j]   = ene_angle_data_obj.get_watt_b_int_data()[j];
  ene_distr_watt_b_range_data[i][j] = ene_angle_data_obj.get_watt_b_range_data()[j];
  ene_distr_watt_b_ene_data[i][j]   = ene_angle_data_obj.get_watt_b_ene_data()[j];
  ene_distr_watt_b_data[i][j]       = ene_angle_data_obj.get_watt_b_data()[j];

  int k_max = static_cast<int>(ene_distr_watt_a_ene_data[i][j].size());
  for(int k=0; k<k_max; k++)
  {
    ene_distr_watt_a_ene_data[i][j][k] *= unit_micro;
    ene_distr_watt_a_data[i][j][k]     *= unit_micro;
  }

  k_max = static_cast<int>(ene_distr_watt_b_ene_data[i][j].size());
  for(int k=0; k<k_max; k++)
  {
    ene_distr_watt_b_ene_data[i][j][k] *= unit_micro;
    ene_distr_watt_b_data[i][j][k]     *= unit_mega;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

//For ene_repr_flg = 12 (Energy-Dependent Fission Neutron Spectrum (Madland and Nix))
void FastAceDataGenerator::set_energy_distr_data_from_ene_angle_data_obj_ene_depend_spectrum
                             (int i, int j, EnergyAngularDataContainer& ene_angle_data_obj, Real& q_val)
{
  ene_distr_ene_in_int_data[i][j].resize(1);
  ene_distr_ene_in_range_data[i][j].resize(1);
  ene_distr_ene_in_int_data[i][j][0]   = int_lin_lin;
  ene_distr_ene_in_range_data[i][j][0] = 1;
  ene_distr_ene_in_data[i][j]          = ene_angle_data_obj.get_temp_max_ene_data()[j];

  int k_max = static_cast<int>(ene_distr_ene_in_data[i][j].size());
  ene_distr_ene_out_int_data[i][j].resize(k_max);
  ene_distr_ene_out_ene_data[i][j].resize(k_max);
  ene_distr_ene_out_data[i][j].resize(k_max);
  ene_distr_ene_out_data_integ[i][j].resize(k_max);

  Real lower_ene_fis_n  = ene_angle_data_obj.get_lower_ene_limit_fis_n()[j];
  Real upper_ene_fis_n  = ene_angle_data_obj.get_upper_ene_limit_fis_n()[j];
  Real temp_max_ene_min = ene_distr_ene_in_data[i][j][0];
  Real temp_max_ene_max = ene_distr_ene_in_data[i][j][k_max-1];

  for(int k=0; k<k_max; k++)
  {
    ene_distr_ene_out_int_data[i][j][k]  = int_lin_lin;
    ene_distr_ene_in_data[i][j][k]      *= unit_micro;

    vector<Real> ene_part_ene_vec, ene_part_vec;
    Real         temp_max_data = ene_angle_data_obj.get_temp_max_data()[j][k];
    calc_linearized_energy_depend_fission_spectrum(ene_part_ene_vec, ene_part_vec,
                                                   lower_ene_fis_n, upper_ene_fis_n, temp_max_data,
                                                   temp_max_ene_min, temp_max_ene_max);

    int          l_max = static_cast<int>(ene_part_ene_vec.size());
    vector<Real> ene_part_vec_integ;
    ene_part_vec_integ.resize(l_max);
    ene_part_vec_integ[0] = 0.0;
    for(int l=1; l<l_max; l++)
    {
      ene_part_vec_integ[l] = ene_part_vec_integ[l-1]
                            + 0.5 * (ene_part_ene_vec[l] - ene_part_ene_vec[l-1])
                                  * (ene_part_vec[l]     + ene_part_vec[l-1]);
    }
    Real normalized_factor = 1.0 / ene_part_vec_integ[l_max-1];

    for(int l=0; l<l_max; l++)
    {
      ene_part_ene_vec[l]   *= unit_micro;
      ene_part_vec[l]       *= unit_mega * normalized_factor;
      ene_part_vec_integ[l] *= normalized_factor;
    }

    ene_distr_ene_out_ene_data[i][j][k]   = ene_part_ene_vec;
    ene_distr_ene_out_data[i][j][k]       = ene_part_vec;
    ene_distr_ene_out_data_integ[i][j][k] = ene_part_vec_integ;
    ene_part_ene_vec.clear();
    ene_part_vec.clear();
    ene_part_vec_integ.clear();
  }
} 

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::calc_linearized_energy_depend_fission_spectrum
                             ( vector<Real>& ene_part_ene_vec, vector<Real>& ene_part_vec,
                               Real& lower_ene_fis_n, Real& upper_ene_fis_n, Real& temp_max_data,
                               Real& temp_max_ene_min, Real& temp_max_ene_max )
{
  Real err_min  = 0.01;

  ene_part_ene_vec.resize(3);
  ene_part_vec.resize(3);
  ene_part_ene_vec[0] = temp_max_ene_min;
  ene_part_ene_vec[1] = 1.0E6;
  ene_part_ene_vec[2] = temp_max_ene_max;
  ene_part_vec[0] = calc_madland_nix_fis_spectrum
                      (ene_part_ene_vec[0], lower_ene_fis_n, upper_ene_fis_n, temp_max_data);
  ene_part_vec[1] = calc_madland_nix_fis_spectrum
                      (ene_part_ene_vec[1], lower_ene_fis_n, upper_ene_fis_n, temp_max_data);
  ene_part_vec[2] = calc_madland_nix_fis_spectrum
                      (ene_part_ene_vec[2], lower_ene_fis_n, upper_ene_fis_n, temp_max_data);

  Real         ene_part_ene_mid, ene_part_mid, ene_part_mid_cal, delta_y;
  vector<Real> ene_part_ene_vec_new, ene_part_vec_new;
  ene_part_ene_vec_new = ene_part_ene_vec;
  ene_part_vec_new     = ene_part_vec;
  int ele_no       = 1;
  ene_part_ene_mid = 0.5*(ene_part_ene_vec_new[ele_no-1] + ene_part_ene_vec_new[ele_no]);
  ene_part_mid     = 0.5*(ene_part_vec_new[ele_no-1]     + ene_part_vec_new[ele_no]);
  ene_part_mid_cal = calc_madland_nix_fis_spectrum
                       (ene_part_ene_mid, lower_ene_fis_n, upper_ene_fis_n, temp_max_data);
  delta_y          = fabs(ene_part_mid - ene_part_mid_cal);

  while( delta_y > fabs(ene_part_mid_cal) * err_min ||
         ele_no < static_cast<int>(ene_part_ene_vec_new.size())  )
  {
    if( delta_y < fabs(ene_part_mid_cal) * err_min )
    {
      ele_no++;
      if( ele_no == static_cast<int>(ene_part_ene_vec_new.size()) )
      {
        break;
      }
    }
    else
    {
      lin_tab_obj.insert_middle_x_data(ele_no, ene_part_ene_vec_new, ene_part_vec_new,
                                       ene_part_ene_mid, ene_part_mid_cal);
    }

    ene_part_ene_mid = 0.5*(ene_part_ene_vec_new[ele_no-1] + ene_part_ene_vec_new[ele_no]);
    ene_part_mid     = 0.5*(ene_part_vec_new[ele_no-1]     + ene_part_vec_new[ele_no]);
    ene_part_mid_cal = calc_madland_nix_fis_spectrum
                         (ene_part_ene_mid, lower_ene_fis_n, upper_ene_fis_n, temp_max_data);
    delta_y          = fabs(ene_part_mid - ene_part_mid_cal);
  }
  ene_part_ene_vec = ene_part_ene_vec_new;
  ene_part_vec     = ene_part_vec_new;
  ene_part_ene_vec_new.clear();
  ene_part_vec_new.clear();

  if( static_cast<int>(ene_part_ene_vec.size()) > 200 )
  {
    string func_name  = "calc_linearized_energy_depend_fission_spectrum";
    ostringstream oss01;
    oss01 << ene_part_ene_vec.size();
    string str_data01 = "Element number : " + oss01.str();
    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("The element number is larger than 200.");
    err_com.push_back("Some neutron calculation code may not be able to read this data.");
    err_obj.output_caution(class_name, func_name, err_com);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Real FastAceDataGenerator::calc_madland_nix_fis_spectrum
                             ( Real& second_ene_data, Real& lower_ene_fis_n, Real& upper_ene_fis_n,
                               Real& temp_max_data )
{
  //expint             : exponential integral En(x)
  //tgamma_lower(a, z) : full (non-normalised) lower incomplete gamma function of a and z

  Real three_half   = 1.5;
  Real sec_ene_sq   = sqrt(second_ene_data);
  Real lower_ene_sq = sqrt(lower_ene_fis_n);
  Real upper_ene_sq = sqrt(upper_ene_fis_n);
  Real temp_max_sq  = sqrt(temp_max_data);
  Real temp_max_inv = 1.0 / temp_max_data;

  Real u1, u2, g1, g2;
  u1 = (sec_ene_sq - lower_ene_sq) * (sec_ene_sq - lower_ene_sq) * temp_max_inv;
  u2 = (sec_ene_sq + lower_ene_sq) * (sec_ene_sq + lower_ene_sq) * temp_max_inv;
  g1 = ( pow(u2,three_half) * boost::math::expint(1,u2) - pow(u1,three_half) * boost::math::expint(1,u1)
       + boost::math::tgamma_lower(three_half, u2)      - boost::math::tgamma_lower(three_half, u1) )
       / ( 3.0 * lower_ene_sq * temp_max_sq );
  
  u1 = (sec_ene_sq - upper_ene_sq) * (sec_ene_sq - upper_ene_sq) * temp_max_inv;
  u2 = (sec_ene_sq + upper_ene_sq) * (sec_ene_sq + upper_ene_sq) * temp_max_inv;
  g2 = ( pow(u2,three_half) * boost::math::expint(1,u2) - pow(u1,three_half) * boost::math::expint(1,u1)
       + boost::math::tgamma_lower(three_half, u2)      - boost::math::tgamma_lower(three_half, u1) )
       / ( 3.0 * upper_ene_sq * temp_max_sq );

  return 0.5 * (g1 + g2);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_energy_distr_data_from_prod_distr_data_obj
                             (int i, ProductDistributionDataContainer& prod_distr_data_obj, Real& q_val)
{
  vector<int> mat_data_pos;
  calc_product_yield(i, prod_distr_data_obj, mat_data_pos);

  int j_max = static_cast<int>(mat_data_pos.size());
  prod_distr_n_body_mass[i].resize(j_max);
  prod_distr_n_body_particle_no[i].resize(j_max);
  prod_distr_prob_data_no[i].resize(j_max);
  prod_distr_prob_ene_in_int_data[i].resize(j_max);
  prod_distr_prob_ene_in_range_data[i].resize(j_max);
  prod_distr_prob_ene_out_int_data[i].resize(j_max);
  prod_distr_prob_ene_in_data[i].resize(j_max);
  prod_distr_prob_ene_out_data[i].resize(j_max);
  prod_distr_prob_coef_a[i].resize(j_max);
  prod_distr_prob_coef_b[i].resize(j_max);
  prod_distr_prob_mu_int_data[i].resize(j_max);
  prod_distr_prob_mu_range_data[i].resize(j_max);
  prod_distr_prob_mu_data[i].resize(j_max);
  prod_distr_prob_mu_data_integ[i].resize(j_max);
  prod_distr_prob_data[i].resize(j_max);
  prod_distr_prob_data_integ[i].resize(j_max);
  prod_distr_prob_mu_vec[i].resize(j_max);
  prod_distr_prob_ene_out_vec[i].resize(j_max);
  prod_distr_prob_vec[i].resize(j_max);
  prod_distr_prob_vec_integ[i].resize(j_max);
  prod_distr_prob_int_vec[i].resize(j_max);
  prod_distr_prob_range_vec[i].resize(j_max);

  for(int j=0; j<j_max; j++)
  {
    int pos = mat_data_pos[j];
    if( prod_distr_data_obj.get_distr_func_flg()[pos] == 6 )
    {
      set_n_body_phase_space_distr_data(i, j, pos, prod_distr_data_obj);
    }
    else
    {
      set_other_ene_angle_distr_data(i, j, pos, prod_distr_data_obj, q_val);
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::calc_product_yield
                             ( int i, ProductDistributionDataContainer& prod_distr_data_obj,
                               vector<int>& mat_data_pos )
{
  if( prod_distr_data_obj.get_prompt_fis_n_flg() == 2 )
  {
    return;
  }

  Integer     yield_flg     = 0;
  Real        yield_ene_max = 0.0;

  check_product_yield( prod_distr_data_obj, yield_flg, mat_data_pos, yield_ene_max);
  modify_product_yield( prod_distr_data_obj );
  if( prod_distr_data_obj.get_prompt_fis_n_flg() == 1 )
  {
    return;
  }

  set_product_yield(i, prod_distr_data_obj, yield_flg, mat_data_pos, yield_ene_max);

  int j_max = static_cast<int>(mat_data_pos.size());
  ene_distr_ene_repr_flg[i].resize(j_max);
  for(int j=0; j<j_max; j++)
  {
    Integer distr_func_flg = prod_distr_data_obj.get_distr_func_flg()[mat_data_pos[j]];
    if( distr_func_flg == 1 )
    {
      ene_distr_ene_repr_flg[i][j] = 44;
    }
    else if( distr_func_flg == 7 )
    {
      ene_distr_ene_repr_flg[i][j] = 67;
    }
    else
    {
      ene_distr_ene_repr_flg[i][j] = 66;
    }
  }

  copy_product_yield(i, prod_distr_data_obj, yield_flg, mat_data_pos);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::check_product_yield( ProductDistributionDataContainer& prod_distr_data_obj,
                                                Integer& yield_flg, vector<int>& mat_data_pos,
                                                Real& yield_ene_max )
{
  vector<Real> mat_data_product     = prod_distr_data_obj.get_mat_data_product();
  Integer      mat_data_product_int = 0;
  int          i_max                = static_cast<int>(mat_data_product.size());

  Integer prompt_fis_n_flg = prod_distr_data_obj.get_prompt_fis_n_flg();
  if( prompt_fis_n_flg == 1 )
  {
    i_max = 1;
  }

  yield_flg     = 0;
  yield_ene_max = 0.0;
  mat_data_pos.clear();
  for(int i=0; i<i_max; i++)
  {
    mat_data_product_int = static_cast<Integer>(round(mat_data_product[i]));
    if( mat_data_product_int == 0 || mat_data_product_int > sub_lib_part )
    {
      break;
    }
    else if( mat_data_product_int != sub_lib_part )
    {
      continue;
    }

    Integer distr_func_flg   = prod_distr_data_obj.get_distr_func_flg()[i];
    if( prompt_fis_n_flg != 1 && distr_func_flg != 1 && distr_func_flg != 6 && distr_func_flg != 7 )
    {
      string func_name  = "check_product_yield";
      ostringstream oss01, oss02, oss03, oss04;
      oss01 << static_cast<int>(prod_distr_data_obj.get_reaction_type());
      oss02 << i+1;
      oss03 << i_max;
      oss04 << static_cast<int>(distr_func_flg);
      string str_data01 = "Reaction type              : " + oss01.str();
      string str_data02 = "Subsection number          : " + oss02.str() + " / " + oss03.str();
      string str_data03 = "Distribution function flag : " + oss04.str();
      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back("Distribution function flag must be 1, 6 or 7.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    //Check product yield data
    vector<Real> product_distr_data = prod_distr_data_obj.get_product_distr_data()[i];
    int j_max = static_cast<int>(product_distr_data.size());

    vector<Integer> product_distr_int_data = prod_distr_data_obj.get_product_distr_int_data()[i];
    int k_max = static_cast<int>(product_distr_int_data.size());
    if( product_distr_int_data[k_max - 1] == 1 )
    {
      j_max--;
    }
    yield_ene_max = prod_distr_data_obj.get_product_distr_ene_data()[i][j_max-1];

    for(int j=1; j<j_max; j++)
    {
      if( fabs(product_distr_data[j] - product_distr_data[j-1]) > min_value )
      {
        yield_flg = 1;
        break;
      }
    }

    if( yield_flg == 0 )
    {
      if( fabs(product_distr_data[0] - round(product_distr_data[0])) > 1.0E-3 )
      {
        yield_flg = 2;
      }
    }

    mat_data_pos.push_back(i);
  }

  if( static_cast<int>(mat_data_pos.size()) > 1 )
  {
    string func_name  = "check_product_yield";
    ostringstream oss01, oss02;
    oss01 << static_cast<int>(prod_distr_data_obj.get_reaction_type());
    oss02 << static_cast<int>(mat_data_pos.size());
    string str_data01 = "Reaction type          : " + oss01.str();
    string str_data02 = "Target material number : " + oss02.str();
    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("More than one target material is found.");
    err_com.push_back("This nuclear data may not be appropriate.");
    err_com.push_back("Please check product identfier (ZAP) in MF=6.");
    err_obj.output_caution(class_name, func_name, err_com);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::modify_product_yield( ProductDistributionDataContainer& prod_distr_data_obj )
{
  vector<vector<Real> > ene_vec = prod_distr_data_obj.get_product_distr_ene_data();

  int i_max = static_cast<int>(ene_vec.size());
  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(ene_vec[i].size());
    if( j_max > 0 )
    {
      ta_obj.adjust_overlap_grid(ene_vec[i]);
    }
  }

  prod_distr_data_obj.set_product_distr_ene_data(ene_vec);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_product_yield( int i, ProductDistributionDataContainer& prod_distr_data_obj,
                                              Integer& yield_flg, vector<int>& mat_data_pos,
                                              Real& yield_ene_max )
{
  int j_max = static_cast<int>(mat_data_pos.size());

  Integer react_type_coef = prod_distr_data_obj.get_ref_frame_flg();
  if( react_type_coef > 2 )
  {
    react_type_coef = 2;
  }

  if( yield_flg == 0 )
  {
    Real yield_tot = 0.0;
    for(int j=0; j<j_max; j++)
    {
      yield_tot += prod_distr_data_obj.get_product_distr_data()[mat_data_pos[j]][0];
    }

    Integer yield_tot_int = static_cast<Integer>(round(yield_tot));
    Integer reaction_type = prod_distr_data_obj.get_reaction_type();
    if( (reaction_type >= 6 && reaction_type <= 9) || (reaction_type >= 46 && reaction_type <= 49) )
    {
      yield_tot_int *= 2;
    }
    else if( reaction_type == 18 )
    {
      yield_tot_int = 19;

      //forces lab system for fission
      //This modification also affects set_other_ene_angle_distr_common_data function.
      react_type_coef = 1;
    }

    //Check distr_func_flg in each subsection
    Integer distr_func_chk_flg = 0;
    vector<Integer> distr_func_flg = prod_distr_data_obj.get_distr_func_flg();
    for(int j=1; j<j_max; j++)
    {
      if( distr_func_flg[mat_data_pos[j]] != distr_func_flg[mat_data_pos[j-1]] )
      {
        distr_func_chk_flg = 1;
        break;
      }
    }

    if( reaction_type != 2 )
    {
      react_type_flg[i] = (3-2*react_type_coef) * yield_tot_int;

      if( j_max > 0 )
      {
        if( prod_distr_data_obj.get_distr_func_flg()[mat_data_pos[j_max-1]] == 6 )
        {
          react_type_flg[i] = -1 * yield_tot_int;
          if( distr_func_chk_flg != 0 )
          {
            string func_name  = "set_product_yield";
            ostringstream oss01;
            oss01 << static_cast<int>(prod_distr_data_obj.get_reaction_type());
            string str_data01 = "Reaction type : " + oss01.str();
            vector<string> err_com;
            err_com.push_back(str_data01);
            err_com.push_back("The distribution flag in each subsection is different.");
            err_com.push_back("The react_type_flg value is modified since last");
            err_com.push_back("distribution flag is 6.");
            err_com.push_back("If you don't intend such processing, please check the");
            err_com.push_back("nuclear data file or this program.");
            err_obj.output_caution(class_name, func_name, err_com);
          }
        }
      }
    }
  }
  else
  {
    //react_type_flg is modified in the FastAceDataWriter class
    //(output_ace_format_energy_distribution_data function)
    react_type_flg[i] = 10000 * (3-2*react_type_coef);
 
    Real ene_last_min = ene_upper_limit * 1.0E3;
    for(int j=0; j<j_max; j++)
    {
      vector<Real> prod_distr_ene_data = prod_distr_data_obj.get_product_distr_ene_data()[mat_data_pos[j]];
      int k_max = static_cast<int>(prod_distr_ene_data.size());
      if( ene_last_min > prod_distr_ene_data[k_max - 1] )
      {
        ene_last_min = prod_distr_ene_data[k_max - 1];
      }
    }

    for(int j=0; j<j_max; j++)
    {
      int pos = mat_data_pos[j];
      vector<Integer> prod_distr_int_data   = prod_distr_data_obj.get_product_distr_int_data()[pos];
      vector<Integer> prod_distr_range_data = prod_distr_data_obj.get_product_distr_range_data()[pos];
      vector<Real>    prod_distr_ene_data   = prod_distr_data_obj.get_product_distr_ene_data()[pos];
      vector<Real>    prod_distr_data       = prod_distr_data_obj.get_product_distr_data()[pos];

      if( j==0 )
      {
        if( generate_mode_flg == generate_default_mode )
        {
          //Linearize table data
          Real error_relative = angle_err_def;
          Real error_min      = angle_err_def * 1.0E-3;
          lin_tab_obj.linearize_tab1_data(prod_distr_range_data, prod_distr_int_data,
                                          prod_distr_ene_data,   prod_distr_data,
                                          error_relative,        error_min);
        }

        prod_yield_tot_ene_data[i] = prod_distr_ene_data;
        prod_yield_tot_data[i]     = prod_distr_data;
        int k_max = static_cast<int>(prod_yield_tot_ene_data[i].size());
        for(int k=0; k<k_max; k++)
        {
          prod_yield_tot_ene_data[i][k] *= unit_micro;
        }
      }
      else
      {
        int k_max = static_cast<int>(prod_yield_tot_ene_data[i].size());
        for(int k=0; k<k_max; k++)
        {
          Real ene_val   = prod_yield_tot_ene_data[i][k] * unit_mega;
          Real yield_val = 0.0;
  
          ti_obj.interpolation_tab1_in_range(ene_val, yield_val, prod_distr_range_data, prod_distr_int_data,
                                             prod_distr_ene_data,   prod_distr_data);

          prod_yield_tot_data[i][k] += yield_val;
        }
      }
    }

    Integer ele_no = static_cast<Integer>(prod_yield_tot_ene_data[i].size());
    if( ele_no > 0 )
    {
      prod_yield_tot_int_data[i].resize(1);
      prod_yield_tot_range_data[i].resize(1);
      prod_yield_tot_int_data[i][0]   = int_lin_lin;
      prod_yield_tot_range_data[i][0] = ele_no;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::copy_product_yield( int i, ProductDistributionDataContainer& prod_distr_data_obj,
                                               Integer& yield_flg, vector<int>& mat_data_pos )
{
  int j_max = static_cast<int>(mat_data_pos.size());
  ene_distr_xs_part_int_data[i].resize(j_max);
  ene_distr_xs_part_range_data[i].resize(j_max);
  ene_distr_xs_part_ene_data[i].resize(j_max);
  ene_distr_xs_part_data[i].resize(j_max);

  int k_max = static_cast<int>(prod_yield_tot_data[i].size());
  vector<Real> yield_ene_vec = prod_yield_tot_ene_data[i];
  vector<Real> yield_tot_vec = prod_yield_tot_data[i];

  if( yield_flg != 0 )
  {
    if( k_max == 0 )
    {
      string func_name  = "copy_product_yield";
      ostringstream oss01, oss02;
      oss01 << prod_distr_data_obj.get_reaction_type();
      oss02 << i+1;
      string str_data01 = "Reaction type       : " + oss01.str();
      string str_data02 = "Position            : " + oss02.str();
      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back("The array number of the total yield data is zero.");
      err_com.push_back("The yield data may not be appropriate");
      err_obj.output_caution(class_name, func_name, err_com);
    }
    else
    {
      for(int k=0; k<k_max; k++)
      {
        yield_ene_vec[k] *= unit_mega;
      }

      Real yield_ene_min = yield_ene_vec[0]       * 1.00001;
      Real yield_ene_max = yield_ene_vec[k_max-1] / 1.00001;
      Real yield_tot_min = 0.0;
      Real yield_tot_max = 0.0;
      ti_obj.interpolation_1d(int_lin_lin, yield_ene_min, yield_tot_min, yield_ene_vec, yield_tot_vec);
      ti_obj.interpolation_1d(int_lin_lin, yield_ene_max, yield_tot_max, yield_ene_vec, yield_tot_vec);

      yield_ene_vec[0]       = yield_ene_min;
      yield_ene_vec[k_max-1] = yield_ene_max;
      yield_tot_vec[0]       = yield_tot_min;
      yield_tot_vec[k_max-1] = yield_tot_max;
    }
  }

  Real yield_inv = 0.0;
  vector<vector<Real> > prod_data_vec = prod_distr_data_obj.get_product_distr_data(); 
  for(int j=0; j<j_max; j++)
  {
    int pos   = mat_data_pos[j];
        k_max = static_cast<int>(prod_data_vec[pos].size());

    if( k_max == 0 )
    {
      continue;
    }

    Real yield_ori = prod_data_vec[pos][0];
    for(int k=1; k<k_max; k++)
    {
      if( fabs(prod_data_vec[pos][k] - yield_ori) > min_value )
      {
        string func_name  = "copy_product_yield";
        ostringstream oss01, oss02, oss03, oss04, oss05, oss06;
        oss01 << prod_distr_data_obj.get_reaction_type();
        oss02 << pos+1;
        oss03 << static_cast<int>(prod_data_vec.size());
        oss04 << prod_distr_data_obj.get_product_distr_ene_data()[pos][k];
        oss05 << yield_ori;
        oss06 << prod_data_vec[pos][k];
        string str_data01 = "Reaction type       : " + oss01.str();
        string str_data02 = "Position            : " + oss02.str() + " / " + oss03.str();
        string str_data03 = "Energy              : " + oss04.str();
        string str_data04 = "Initial yield value : " + oss05.str();
        string str_data05 = "Current yield value : " + oss06.str();
        vector<string> err_com;
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back(str_data04);
        err_com.push_back(str_data05);
        err_com.push_back("The yield value is varied with energy.");
        err_com.push_back("This program is only available for initial yield value.");
        //if( generate_mode_flg == generate_default_mode )
        //{
        //  err_obj.output_runtime_error(class_name, func_name, err_com);
        //}
        //else
        //{
          err_obj.output_caution(class_name, func_name, err_com);
        //}
      }
    }
    yield_inv += yield_ori;
  }
  yield_inv = 1.0 / yield_inv;
  
  for(int j=0; j<j_max; j++)
  {
    int pos = mat_data_pos[j];
    vector<Integer> prod_int_data   = prod_distr_data_obj.get_product_distr_int_data()[pos];
    vector<Integer> prod_range_data = prod_distr_data_obj.get_product_distr_range_data()[pos];
    vector<Real>    prod_ene_data   = prod_distr_data_obj.get_product_distr_ene_data()[pos];
    vector<Real>    prod_data       = prod_data_vec[pos];

    if( yield_flg == 0 )
    {
      ene_distr_xs_part_int_data[i][j]   = prod_int_data;
      ene_distr_xs_part_range_data[i][j] = prod_range_data;
      ene_distr_xs_part_ene_data[i][j]   = prod_ene_data;
      ene_distr_xs_part_data[i][j]       = prod_data;

      k_max = static_cast<int>(prod_ene_data.size());
      for(int k=0; k<k_max; k++)
      {
        ene_distr_xs_part_ene_data[i][j][k] *= unit_micro;
        ene_distr_xs_part_data[i][j][k]     *= yield_inv;
      }
    }
    else
    {
      k_max = static_cast<int>(prod_yield_tot_data[i].size());
      if( k_max > 0 )
      {
        ene_distr_xs_part_int_data[i][j].push_back(int_lin_lin);
        ene_distr_xs_part_range_data[i][j].push_back(k_max);
 
        ene_distr_xs_part_ene_data[i][j] = prod_yield_tot_ene_data[i];
        ene_distr_xs_part_data[i][j].resize(k_max);
        for(int k=0; k<k_max; k++)
        {
          ene_distr_xs_part_data[i][j][k] = 0.0;
          ti_obj.interpolation_tab1_in_range(yield_ene_vec[k], ene_distr_xs_part_data[i][j][k],
                                             prod_range_data, prod_int_data, prod_ene_data, prod_data);
          if( yield_tot_vec[k] > min_value )
          {
            ene_distr_xs_part_data[i][j][k] /= yield_tot_vec[k];
          }
        }     
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_n_body_phase_space_distr_data
                             (int i, int j, int pos, ProductDistributionDataContainer& prod_distr_data_obj)
{
  prod_distr_n_body_mass[i][j]        = prod_distr_data_obj.get_n_body_mass()[pos];
  prod_distr_n_body_particle_no[i][j] = prod_distr_data_obj.get_n_body_particle_no()[pos];

  prod_distr_prob_data_no[i][j] = 2;

  vector<Real> mu_vec, prob_vec, prob_integ_vec;
  calc_n_body_phase_space_distr_data(prod_distr_n_body_particle_no[i][j], mu_vec, prob_vec, prob_integ_vec);

  prod_distr_prob_mu_data[i][j].resize(1);
  prod_distr_prob_data[i][j].resize(1);
  prod_distr_prob_data_integ[i][j].resize(1);
  prod_distr_prob_mu_data[i][j][0]    = mu_vec;
  prod_distr_prob_data[i][j][0]       = prob_vec;
  prod_distr_prob_data_integ[i][j][0] = prob_integ_vec;
  mu_vec.clear();
  prob_vec.clear();
  prob_integ_vec.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::calc_n_body_phase_space_distr_data
                             (Integer& n_body_particle_no, vector<Real>& mu_vec, vector<Real>& prob_vec,
                              vector<Real>& prob_integ_vec)
{
  Real mu_min     = 1.0E-5;
  Real step1      = pow(10.0, 0.2);
  Real step2      = 0.02;
  Real test1      = 1.0 + 1.0E-5;
  Real test2      = 0.1 - 1.0E-6;
  Real test3      = 1.0 - 1.0E-4;

  Real index_val  = 1.5 * static_cast<Real>(n_body_particle_no) - 4.0;
  Real mu_pre     = 0.0;
  Real prob_pre   = 0.0;
  Real prob_integ = 0.0;

  mu_vec.push_back(mu_pre);
  prob_vec.push_back(prob_pre);
  prob_integ_vec.push_back(prob_integ);

  Real mu_cur   = mu_min;
  Real prob_cur = 0.0;
  while( mu_cur < test1 )
  {
    if( mu_cur > test3 )
    {
      mu_cur  = 1.0;
      prob_cur = 0.0;
    }
    else
    {
      prob_cur = sqrt(mu_cur) * pow((1.0 - mu_cur), index_val);
    }

    prob_integ += 0.5 * (mu_cur - mu_pre) * (prob_cur + prob_pre);
    mu_vec.push_back(mu_cur);
    prob_vec.push_back(prob_cur);
    prob_integ_vec.push_back(prob_integ);

    mu_pre   = mu_cur;
    prob_pre = prob_cur;
    if( mu_cur < test2 )
    {
      mu_cur *= step1;
    }
    else
    {
      mu_cur += step2;
    }
  }

  int  k_max    = static_cast<int>(mu_vec.size());
  Real prob_sum = prob_integ_vec[k_max-1];
  for(int k=0; k<k_max; k++)
  {
    prob_vec[k]       /= prob_sum;
    prob_integ_vec[k] /= prob_sum;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_other_ene_angle_distr_data
                             (int i, int j, int pos, ProductDistributionDataContainer& prod_distr_data_obj,
                              Real& q_val)
{
  set_other_ene_angle_distr_common_data(i, j, pos, prod_distr_data_obj);

  Integer distr_func_flg = prod_distr_data_obj.get_distr_func_flg()[pos];
  if( distr_func_flg == 1 )
  {
    set_continuum_ene_angle_distr_data(i, j, pos, prod_distr_data_obj, q_val);
  }
  else //distr_func_flg == 7
  {
    set_lab_ene_angle_distr_data(i, j, pos, prod_distr_data_obj);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_other_ene_angle_distr_common_data
                             (int i, int j, int pos, ProductDistributionDataContainer& prod_distr_data_obj)
{
  Integer distr_func_flg = prod_distr_data_obj.get_distr_func_flg()[pos];
  if( distr_func_flg != 1 && distr_func_flg != 7 )  
  {
    if( prod_distr_data_obj.get_prompt_fis_n_flg() > 0 ||
        prod_distr_data_obj.get_prompt_fis_p_flg() > 0 )
    {
      return;
    }
    else
    {
      string func_name  = "set_other_ene_angle_distr_common_data";
      ostringstream oss01, oss02, oss03;
      oss01 << i+1;
      oss02 << j+1;
      oss03 << distr_func_flg;
      string str_data01 = "Position                   : " + oss01.str() + ", " + oss02.str();
      string str_data02 = "Distribution function flag : " + oss03.str();
      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back("Distribution function flag must be 1, 6 or 7.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }

  Integer ang_repr_flg = 0;
  if( distr_func_flg == 1 )
  {
    ang_repr_flg = prod_distr_data_obj.get_angular_repr_flg()[pos];
    if( ang_repr_flg < 1 || (ang_repr_flg > 2 && ang_repr_flg < 11) || ang_repr_flg > 13 )
    {
      string func_name  = "set_other_ene_angle_distr_common_data";
      ostringstream oss01, oss02, oss03;
      oss01 << i+1;
      oss02 << j+1;
      oss03 << ang_repr_flg;
      string str_data01 = "Position                    : " + oss01.str() + ", " + oss02.str();
      string str_data02 = "Angular representation flag : " + oss03.str();
      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back("The angular representation flag is only available for 1, 2 or 11-13.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }

  if( distr_func_flg == 1 && ang_repr_flg != 2 )
  {
    if( new_cummulative_angle_distr_flg == 0 )
    { 
      if( i > 0 && prod_distr_data_obj.get_ref_frame_flg() >= 2 )
      {
        if( prod_distr_data_obj.get_reaction_type() != 18 )
        {
          //converting to kalbach
          react_type_flg[i-1] = -1 * abs(react_type_flg[i-1]);
        }
      }
    }
    else if( new_cummulative_angle_distr_flg == 1 )
    {
      ene_distr_ene_repr_flg[i][j] = 61;
    }
  }

  vector<Integer> int_vec, range_vec;
  if( distr_func_flg == 1 )
  {
    int_vec   = prod_distr_data_obj.get_cont_int_data()[pos];
    range_vec = prod_distr_data_obj.get_cont_range_data()[pos];
  }
  else //distr_func_flg == 7
  {
    int_vec   = prod_distr_data_obj.get_lab_ene_int_data()[pos];
    range_vec = prod_distr_data_obj.get_lab_ene_range_data()[pos];
  }

  int k_max = static_cast<int>(int_vec.size());
  for(int k=0; k<k_max; k++)
  {
    int_vec[k] = int_vec[k]%10;
    if( int_vec[k] != int_const && int_vec[k] != int_lin_lin )
    {
      string func_name  = "set_other_ene_angle_distr_common_data";
      ostringstream oss01, oss02, oss03, oss04, oss05;
      oss01 << i+1;
      oss02 << j+1;
      oss03 << k+1;
      oss04 << k_max;
      oss05 << int_vec[k];
      string str_data01 = "Position           : " + oss01.str() + ", " + oss02.str();
      string str_data02 = "k = " + oss03.str() + " / " + oss04.str();
      string str_data03 = "Interpolation type : " + oss05.str();
      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back("This interpolation type may not be available.");
      err_com.push_back("Available interpolation type is constant and linear-linear.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }

  prod_distr_prob_ene_in_int_data[i][j]   = int_vec;
  prod_distr_prob_ene_in_range_data[i][j] = range_vec;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_continuum_ene_angle_distr_data
                             (int i, int j, int pos, ProductDistributionDataContainer& prod_distr_data_obj,
                              Real& q_val)
{
  Integer      react_type          = prod_distr_data_obj.get_reaction_type();
  Integer      ang_repr_flg        = prod_distr_data_obj.get_angular_repr_flg()[pos];
  Integer      second_ene_int_data = prod_distr_data_obj.get_second_ene_int_data()[pos];
  Integer      mat_data_product
                 = static_cast<Integer>(round(prod_distr_data_obj.get_mat_data_product()[pos]));
  vector<Real> ene_a_vec           = prod_distr_data_obj.get_cont_ene_a()[pos];

  if( second_ene_int_data != int_const && second_ene_int_data != int_lin_lin )
  {
    string func_name  = "set_continuum_ene_angle_distr_data";
    ostringstream oss01, oss02, oss03, oss04;
    oss01 << i+1;
    oss02 << j+1;
    oss03 << react_type;
    oss04 << second_ene_int_data;
    string str_data01 = "Position                         : " + oss01.str() + ", " + oss02.str();
    string str_data02 = "Reaction type                    : " + oss03.str();
    string str_data03 = "Second energy interpolation type : " + oss04.str();
    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("This interpolation type is not available.");
    err_com.push_back("Available interpolation type is constant and linear-linear.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  int k_max = static_cast<int>(ene_a_vec.size());
  prod_distr_prob_ene_out_int_data[i][j].resize(k_max);
  prod_distr_prob_ene_out_data[i][j].resize(k_max);
  prod_distr_prob_coef_a[i][j].resize(k_max);
  prod_distr_prob_coef_b[i][j].resize(k_max);
  prod_distr_prob_mu_data[i][j].resize(k_max);
  prod_distr_prob_mu_data_integ[i][j].resize(k_max);
  prod_distr_prob_mu_vec[i][j].resize(k_max);
  prod_distr_prob_vec[i][j].resize(k_max);
  prod_distr_prob_vec_integ[i][j].resize(k_max);
  prod_distr_prob_int_vec[i][j].resize(k_max);
  prod_distr_prob_range_vec[i][j].resize(k_max);

  prod_distr_prob_ene_in_data[i][j] = ene_a_vec;
  for(int k=0; k<k_max; k++)
  {
    prod_distr_prob_ene_in_data[i][j][k] *= unit_micro;

    Integer discrete_ene_no = prod_distr_data_obj.get_discrete_ene_no()[pos][k];
    prod_distr_prob_ene_out_int_data[i][j][k] = second_ene_int_data + 10*discrete_ene_no;
    if( ang_repr_flg == 2 && mat_data_product == 1 && discrete_ene_no == 0 )
    {
      //This correction might not be required for FRENDY
      extend_low_histogram(i, j, k, pos, prod_distr_data_obj);
    }

    vector<Real> ene_b_vec = prod_distr_data_obj.get_cont_ene_b()[pos][k];
    int          l_max     = static_cast<int>(ene_b_vec.size());
    prod_distr_prob_ene_out_data[i][j][k].resize(l_max);
    prod_distr_prob_coef_a[i][j][k].resize(l_max);
    prod_distr_prob_coef_b[i][j][k].resize(l_max);
    prod_distr_prob_mu_data[i][j][k].resize(l_max);
    prod_distr_prob_mu_data_integ[i][j][k].resize(l_max);
    prod_distr_prob_mu_vec[i][j][k].resize(l_max);
    prod_distr_prob_vec[i][j][k].resize(l_max);
    prod_distr_prob_vec_integ[i][j][k].resize(l_max);
    prod_distr_prob_int_vec[i][j][k].resize(l_max);
    prod_distr_prob_range_vec[i][j][k].resize(l_max);

    int cont_chk_cur = 0;
    int cont_chk_pre = 0;
    for(int l=0; l<l_max; l++)
    {
      cont_chk_pre = cont_chk_cur;
      cont_chk_cur = check_continuum_ene_angle_distr_data
                       (ene_a_vec[k], ene_b_vec[l], l, l_max, react_type, q_val);
      if( cont_chk_pre == 1 && ene_b_vec[l] < ene_b_vec[l-1] + min_ene_dif )
      {
        ene_b_vec[l] = ene_a_vec[k] - static_cast<Real>(l_max - l - 1) / 1000.0;
        cont_chk_cur = 1;
      }

      prod_distr_prob_ene_out_data[i][j][k][l] = ene_b_vec[l]*unit_micro;
      prod_distr_prob_mu_data[i][j][k][l]      = prod_distr_data_obj.cont_data[pos][k][l][0];
      if( l >= discrete_ene_no )
      {
        prod_distr_prob_mu_data[i][j][k][l] *= unit_mega;
      }

      if( prod_distr_prob_mu_data[i][j][k][l] > 0.0 && prod_distr_prob_mu_data[i][j][k][l] < min_value )
      {
        prod_distr_prob_mu_data[i][j][k][l] = min_value;
      }

      if( l > 0 )
      {
        if( l < discrete_ene_no )
        {
          prod_distr_prob_mu_data_integ[i][j][k][l] = prod_distr_prob_mu_data_integ[i][j][k][l-1]
                                                    + prod_distr_prob_mu_data[i][j][k][l];
        }
        else if( l == discrete_ene_no )
        {
          prod_distr_prob_mu_data_integ[i][j][k][l] = prod_distr_prob_mu_data_integ[i][j][k][l-1];
        }
        else if( l > discrete_ene_no && second_ene_int_data == int_const )
        {
          prod_distr_prob_mu_data_integ[i][j][k][l] = prod_distr_prob_mu_data_integ[i][j][k][l-1]
            +  prod_distr_prob_mu_data[i][j][k][l-1]
            * ( prod_distr_prob_ene_out_data[i][j][k][l] - prod_distr_prob_ene_out_data[i][j][k][l-1] );
        }
        else if( l > discrete_ene_no && second_ene_int_data == int_lin_lin )
        {
          prod_distr_prob_mu_data_integ[i][j][k][l] = prod_distr_prob_mu_data_integ[i][j][k][l-1]
            + 0.5 * (prod_distr_prob_mu_data[i][j][k][l]      + prod_distr_prob_mu_data[i][j][k][l-1])
                  * (prod_distr_prob_ene_out_data[i][j][k][l] - prod_distr_prob_ene_out_data[i][j][k][l-1]);
        }
      }
      else
      {
        prod_distr_prob_mu_data_integ[i][j][k][l] = 0.0;
      }

      calc_kalbach_angle_distr(i, j, k, l, react_type, ang_repr_flg, ene_a_vec[k], ene_b_vec[l],
                               prod_distr_data_obj.cont_data[pos][k][l]);
    }

    //Normalize prod_distr_prob_mu_data and prod_distr_prob_mu_data_integ
    Real sum = prod_distr_prob_mu_data_integ[i][j][k][l_max - 1];
    if( fabs(sum) < min_value )
    {
      sum = 1.0;
    }
    else
    {
      sum = 1.0 / sum;
    }

    for(int l=0; l<l_max; l++)
    {
      prod_distr_prob_mu_data[i][j][k][l]       *= sum;
      prod_distr_prob_mu_data_integ[i][j][k][l] *= sum;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

int FastAceDataGenerator::check_continuum_ene_angle_distr_data
                            (Real& ene_a, Real& ene_b, int l, int l_max, Integer react_type, Real& q_val)
{
  int caution_flg = 0;
  if( react_type != 5 && q_val < 0.0 )
  {
    if( ene_b > 0.999*ene_a && l < l_max-1 )
    {
      caution_flg = 1;
    }
    else if( ene_b > ene_a && l == l_max-1 )
    {
      caution_flg = 1;
    }

    if( caution_flg == 1 )
    {
      ene_b = ene_a - static_cast<Real>(l_max - l - 1) / 1000.0;
    }

  }
  else if( ene_b > ene_a * 1.05 && react_type == 5 )
  {
    caution_flg = 2;
  }

  if( caution_flg != 0 )
  {
    string func_name  = "check_continuum_ene_angle_distr_data";
    ostringstream oss01, oss02, oss03, oss04, oss05, oss06;
    oss01 << l+1;
    oss02 << l_max;
    oss03 << react_type;
    oss04 << q_val;
    oss05 << ene_a;
    oss06 << ene_b;
    string str_data01 = "Position (l)  : " + oss01.str() + " / " + oss02.str();
    string str_data02 = "Reaction type : " + oss03.str();
    string str_data03 = "Q value       : " + oss04.str();
    string str_data04 = "E             : " + oss05.str();
    string str_data05 = "Ep            : " + oss06.str();
    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back(str_data05);

    if( caution_flg == 1 )
    {
      err_com.push_back("Ep is greater than E with negative Q value.");
    }
    else if( caution_flg == 2 )
    {
      err_com.push_back("Ep is greater than E in (z, anythint) reaction.");
    }
    err_obj.output_caution(class_name, func_name, err_com);
  }

  return caution_flg;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::extend_low_histogram
                             ( int i, int j, int k, int pos,
                               ProductDistributionDataContainer& prod_distr_data_obj )
{
#if 0
  //!!! Japanese comment !!!/
  //この調整っているか？FRENDYの本質にそぐわないのでは？
#endif
  Integer               second_ene_int_data = prod_distr_data_obj.get_second_ene_int_data()[pos];
  Real                  ene_val             = prod_distr_data_obj.get_cont_ene_a()[pos][k];
  vector<Real>          ene_b_vec           = prod_distr_data_obj.get_cont_ene_b()[pos][k];
  vector<vector<Real> > cont_data           = prod_distr_data_obj.get_cont_data()[pos][k];

  int ele_no = static_cast<int>(ene_b_vec.size());
  if( ele_no <= 1 )
  {
    return;
  }

  Integer extend_ene_flg = 0;
  if( second_ene_int_data == 1 )
  {
    extend_ene_flg = 1;
  }
  else if( second_ene_int_data == 2 && ele_no > 3 )
  {
    extend_ene_flg = 2;
  }

  if( extend_ene_flg > 0 )
  {
    //Output caution
    ostringstream oss01, oss02, oss03, oss04;
    oss01 << i+1;
    oss02 << j+1;
    oss03 << k+1;
    oss04 << second_ene_int_data;
    string str_data01 = "Position                         : " + oss01.str() + ", " + oss02.str()
                                                                            + ", " + oss03.str();
    string str_data02 = "Second energy interpolation type : " + oss04.str();
    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("Angular representation flg       : 2");
    err_com.push_back("Product identifier (1000*Z+A)    : 1");
    err_com.push_back("Number of discrete energy        : 0");
    err_com.push_back(str_data02);

    if( extend_ene_flg == 1 )
    {
      //extend low histogram bins as sqrt(e) using log energy scale
      //only do this for outgoing neutrons with law=1, lang=2
      //only do this if there are no discrete data
      extend_low_histogram_by_log(ene_val, ene_b_vec, cont_data, err_com);
    }
    else if( extend_ene_flg == 2 )
    {
      //extend to lower energy as sqrt(e) using linear interpol
      //only do this for outgoing neutrons with law=1, lang=2
      //only do this if there are no discrete data
      extend_low_histogram_by_lin(ene_val, ene_b_vec, cont_data, err_com);
    }
    clr_obj.clear_vec_array1_str(err_com);

    //Modify prod_distr_data_obj data
    vector<vector<vector<Real> > >          ene_b_vec_new = prod_distr_data_obj.get_cont_ene_b();
    vector<vector<vector<vector<Real> > > > cont_data_new = prod_distr_data_obj.get_cont_data();
    ene_b_vec_new[pos][k] = ene_b_vec;
    cont_data_new[pos][k] = cont_data;
    prod_distr_data_obj.set_cont_ene_b(ene_b_vec_new);
    prod_distr_data_obj.set_cont_data(cont_data_new);
    clr_obj.clear_vec_array3_real(ene_b_vec_new);
    clr_obj.clear_vec_array4_real(cont_data_new);
  }

  ene_b_vec.clear();
  clr_obj.clear_vec_array2_real(cont_data);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::extend_low_histogram_by_log
                             (Real& ene_val, vector<Real>& ene_vec,
                              vector<vector<Real> >& cont_vec, vector<string>& com_vec)
{
  Real ene_ex_min = 40.0;
  Real fix_val    =  0.8409;

  int ene_no = static_cast<int>(ene_vec.size());

  if( generate_mode_flg == generate_njoy_mode )
  {
    int i       = 0;
    Real cx_pre = ene_vec[i+1] * cont_vec[i][0];
    while( ene_no - i > 2 )
    {
      Real cx_cur = cx_pre + cont_vec[i+1][0] * (ene_vec[i+2] - ene_vec[i+1]);
      if( fabs(cx_cur/pow(ene_vec[i+2], 1.5) - cx_pre/pow(ene_vec[i+1], 1.5)) >
          0.02*cx_pre/pow(ene_vec[i+1], 1.5) )
      {
        break;
      }

      cont_vec[0][0] = ( cont_vec[0][0] * ene_vec[i+1]
                       + cont_vec[i+1][0] * (ene_vec[i+2] - ene_vec[i+1]) ) / ene_vec[i+2];
      cx_pre = cx_cur;
      i++;
    }

    if( i != 0 )
    {
      string func_name  = "extend_low_histogram_by_log";
      ostringstream oss01, oss02;
      oss01 << ene_vec[0]*unit_micro;
      oss02 << ene_vec[i]*unit_micro;
      string str_data01 = "Energy range : " + oss01.str() + " - " + oss02.str() + " [MeV]";
      vector<string> err_com = com_vec;
      err_com.push_back(str_data01);
      err_com.push_back("The nuclear data in the above energy range may not be appropriate.");
      err_com.push_back("The nuclear data in the above energy range is removed.");
      err_obj.output_caution(class_name, func_name, err_com);

      vector<Real>          ene_vec_mod;
      vector<vector<Real> > cont_vec_mod;

      ene_vec_mod.push_back(ene_vec[0]);
      cont_vec_mod.push_back(cont_vec[0]);
      for(int j=i+1; j<ene_no; j++)
      {
        ene_vec_mod.push_back(ene_vec[j]);
        cont_vec_mod.push_back(cont_vec[j]);
      }

      ene_vec  = ene_vec_mod;
      cont_vec = cont_vec_mod;
      ene_vec_mod.clear();
      clr_obj.clear_vec_array2_real(cont_vec_mod);

      ene_no = static_cast<int>(ene_vec.size());
    }
  }

  vector<Real>          ene_vec_new,  ene_vec_ex;
  vector<vector<Real> > cont_vec_new, cont_vec_ex;
  ene_vec_new.push_back(ene_vec[0]);
  cont_vec_new.push_back(cont_vec[0]);
  ene_vec_ex.push_back(ene_vec[1]);
  cont_vec_ex.push_back(cont_vec[1]);
  
  if( ene_vec[1] > ene_ex_min )
  {
    string func_name  = "extend_low_histogram_by_log";
    ostringstream oss01, oss02, oss03, oss04;
    oss01 << ene_vec[1]*unit_micro;
    oss02 << ene_ex_min*unit_micro;
    oss03 << ene_vec[0]*unit_micro;
    string str_data01 = "Minimum energy : " + oss01.str() + " MeV ";
    string str_data02 = "Minimum energy is less than " + oss02.str() + " MeV.";
    string str_data03 = "Extending histograms as sqrt(E) below " + oss03.str()
                      + " MeV for E= " + oss01.str() + " MeV";
    com_vec.push_back(str_data01);
    com_vec.push_back(str_data02);
    com_vec.push_back(str_data03);
    err_obj.output_caution(class_name, func_name, com_vec);

    int i_max = 1;
    while( ene_vec_ex[i_max-1] > ene_ex_min )
    {
      ene_vec_ex.push_back(ene_vec_ex[i_max-1]*fix_val);
      cont_vec_ex.push_back(cont_vec_ex[i_max-1]);
      i_max++;

      Real cont_val = cont_vec_new[0][0];
      cont_vec_new[0][0] *= sqrt(fix_val);
      cont_vec_ex[i_max-1][0] = (1.0 - fix_val*sqrt(fix_val)) * cont_val / (1.0 - fix_val);
      cont_vec_ex[i_max-1][1] = cont_vec_new[0][1];
    }

    for(int i=i_max-1; i>=0; i--)
    {
      ene_vec_new.push_back(ene_vec_ex[i]);
      cont_vec_new.push_back(cont_vec_ex[i]);
    }
    ene_vec_ex.clear();
    clr_obj.clear_vec_array2_real(cont_vec_ex);

    for(int i=2; i<ene_no; i++)
    {
      ene_vec_new.push_back(ene_vec[i]);
      cont_vec_new.push_back(cont_vec[i]);
    }

    ene_vec  = ene_vec_new;
    cont_vec = cont_vec_new;
    ene_vec_new.clear();
    clr_obj.clear_vec_array2_real(cont_vec_new);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::extend_low_histogram_by_lin
                             (Real& ene_val, vector<Real>& ene_vec,
                              vector<vector<Real> >& cont_vec, vector<string>& com_vec)
{
  Real ene_ex_min = 40.0;
  Real fix_val    =  0.5;

  int ene_no = static_cast<int>(ene_vec.size());
  vector<Real>          ene_vec_new;
  vector<vector<Real> > cont_vec_new;
  if( ene_vec[0] > ene_ex_min )
  {
    string func_name  = "extend_low_histogram_by_lin";
    ostringstream oss01, oss02;
    oss01 << ene_vec[0]*unit_micro;
    oss02 << ene_val*unit_micro;
    string str_data01 = "Extending lin-lin as sqrt(E) below " + oss01.str()
                      + " MeV for E= " + oss02.str() + " MeV";
    com_vec.push_back(str_data01);
    err_obj.output_caution(class_name, func_name, com_vec);

    int j_max = static_cast<int>(cont_vec[0].size());
    ene_vec_new.resize(ene_no+1);
    cont_vec_new.resize(ene_no+1);
    ene_vec_new[0] = 0.0;
    cont_vec_new[0].resize(j_max);
    for(int j=0; j<j_max; j++)
    {
      cont_vec_new[0][j] = 0.0;
    }

    for(int i=0; i<ene_no; i++)
    {
      ene_vec_new[i+1]  = ene_vec[i];
      cont_vec_new[i+1] = cont_vec[i];
    }

    ene_vec  = ene_vec_new;
    cont_vec = cont_vec_new;
    ene_vec_new.clear();
    clr_obj.clear_vec_array2_real(cont_vec_new);
  }

  int add_ene_flg = 0;
  ene_no = static_cast<int>(ene_vec.size());
  ene_vec_new  = ene_vec;
  cont_vec_new = cont_vec;
  while( ene_vec_new[1] > ene_ex_min )
  {
    add_ene_flg++;
    ene_no++;
    ene_vec_new.push_back(ene_vec_new[ene_no-2]);
    cont_vec_new.push_back(cont_vec_new[ene_no-2]);
    for(int i=ene_no-2; i>=2; i--)
    {
      ene_vec_new[i]  = ene_vec_new[i-1];
      cont_vec_new[i] = cont_vec_new[i-1];
    }
    ene_vec_new[1] *= fix_val;

    int j_max = static_cast<int>(cont_vec[1].size());
    for(int j=0; j<j_max; j++)
    {
      cont_vec_new[1][j] *= sqrt(fix_val);
    }
  }
  ene_vec  = ene_vec_new;
  cont_vec = cont_vec_new;
  ene_vec_new.clear();
  clr_obj.clear_vec_array2_real(cont_vec_new);

  ene_no = static_cast<int>(ene_vec.size());
  if( add_ene_flg > 0 )
  {
    Real cx_val = 0.0;
    for(int i=0; i<ene_no-1; i++)
    {
      cx_val += 0.5 * (ene_vec[i+1] - ene_vec[i]) * (cont_vec[i+1][0] + cont_vec[i][0]);
    }

    if( fabs(cx_val) > min_value )
    {
      cx_val = 1.0/cx_val;
      for(int i=0; i<ene_no; i++)
      {
        cont_vec[i][0] *= cx_val;
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::calc_kalbach_angle_distr
                             ( int i, int j, int k, int l, Integer react_type, Integer ang_repr_flg,
                               Real& ene_in, Real& ene_out, vector<Real>& cont_data )
{
  if( ang_repr_flg == 2 )
  {
    //For Kalbach-Mann systematics
    prod_distr_prob_coef_a[i][j][k][l] = cont_data[1];

    if( static_cast<int>(cont_data.size()) == 3 )
    {
      prod_distr_prob_coef_b[i][j][k][l] = cont_data[2];
    }
    else
    {
      prod_distr_prob_coef_b[i][j][k][l] = calc_kalbach_mann_parameter(1, 1, ene_in, ene_out);
    }
  }
  else if( new_cummulative_angle_distr_flg != 1 )
  {
    calc_kalbach_angle_distr_old(i, j, k, l, react_type, ang_repr_flg, ene_in, ene_out, cont_data);
  }
  else
  {
    calc_kalbach_angle_distr_new_cummulative_angle_distr( i, j, k, l, react_type, ang_repr_flg,
                                                          ene_in, ene_out, cont_data );
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::calc_kalbach_angle_distr_old
                             ( int i, int j, int k, int l, Integer react_type, Integer ang_repr_flg,
                               Real& ene_in, Real& ene_out, vector<Real>& cont_data )
{
  int m_max = static_cast<int>(cont_data.size());

  if( ang_repr_flg == 1 ) //For Legendre coefficient
  {
    //Convert legendre distribution to Kalbach form
    int cont_data_flg = 1;
    for(int m=1; m<m_max; m++)
    {
      if( fabs(cont_data[m]) > min_value )
      {
        cont_data_flg = 0;
        break;
      }
    }

    if( fabs(prod_distr_prob_mu_data[i][j][k][l] * unit_micro) < min_value )
    {
      cont_data_flg = 1;
    }

    if( cont_data_flg != 0 )
    {
      prod_distr_prob_coef_a[i][j][k][l] = 0.0;
      prod_distr_prob_coef_b[i][j][k][l] = 1.0E-5;
    }
    else
    {
      Real f_even = 0.5;
      Real f_odd  = 0.0;
      Real coef_f = 1.0 / (2.0 * prod_distr_prob_mu_data[i][j][k][l] * unit_micro);
      for(int m=1; m<m_max; m++)
      {
        Real f_part = static_cast<Real>(2*m+1) * cont_data[m] * coef_f;

        if( m%2 == 0 )
        {
          f_even += f_part;
        }
        else
        {
          f_odd  += 2.0*f_part;
        }
      }

      calc_kalbach_angle_distr_by_ave_data
        ( react_type, prod_distr_prob_coef_a[i][j][k][l], prod_distr_prob_coef_b[i][j][k][l],
          f_even, f_odd, ene_in, ene_out );
    }
  }
  else if( ang_repr_flg > 2 ) //For tabulated angular distribution
  {
    //Convert tabulated distribution to Kalbach form
    if( fabs(cont_data[1] + 1.0) >= 1.0E-3 || fabs(cont_data[m_max-2] + 1.0) >= 1.0E-3 )
    {
      calc_kalbach_angle_distr_by_table_data
        ( react_type, prod_distr_prob_coef_a[i][j][k][l], prod_distr_prob_coef_b[i][j][k][l],
          cont_data[2], cont_data[m_max-1], cont_data[1], cont_data[m_max-2],
          ene_in, ene_out );
    }
    else
    {
      Real f_even = (cont_data[m_max-1] + cont_data[2]) * 0.5;
      Real f_odd  = (cont_data[m_max-1] - cont_data[2]);
      calc_kalbach_angle_distr_by_ave_data
        ( react_type, prod_distr_prob_coef_a[i][j][k][l], prod_distr_prob_coef_b[i][j][k][l],
          f_even, f_odd, ene_in, ene_out );
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::calc_kalbach_angle_distr_new_cummulative_angle_distr
                             ( int i, int j, int k, int l, Integer reaction_type, Integer ang_repr_flg,
                               Real& ene_in, Real& ene_out, vector<Real>& cont_data )
{
  int m_max = static_cast<int>(cont_data.size());

  if( ang_repr_flg == 1 ) //For Legendre coefficient
  {
    vector<Real> list_data;
    list_data.resize(m_max-1);
    if( fabs(cont_data[0]) > 0.0 )
    {
      for(int m=1; m<m_max; m++)
      {
        list_data[m-1] = cont_data[m]/cont_data[0];
      }
    }
    else
    {
      for(int m=0; m<m_max-1; m++)
      {
        list_data[m] = 0.0;
      }
    }

    //string func_name = "calc_kalbach_angle_distr_new_cummulative_angle_distr";
    //lin_tab_obj.check_legendre_polynomial_list_data
    //  (class_name, func_name, reaction_type, i, j, k, l, list_data);

    lin_tab_obj.linearize_list_data_by_legendre_polynomial
      (list_data, prod_distr_prob_mu_vec[i][j][k][l], prod_distr_prob_vec[i][j][k][l],
                                                      prod_distr_prob_vec_integ[i][j][k][l]);
    prod_distr_prob_vec_integ[i][j][k][l][0] = 0.0;

    Integer ele_no = static_cast<Integer>(prod_distr_prob_vec_integ[i][j][k][l].size());
    prod_distr_prob_int_vec[i][j][k][l].resize(1);
    prod_distr_prob_range_vec[i][j][k][l].resize(1);
    prod_distr_prob_int_vec[i][j][k][l][0]   = int_lin_lin;
    prod_distr_prob_range_vec[i][j][k][l][0] = ele_no;
  }
  else if( ang_repr_flg > 2 ) //For tabulated angular distribution
  {
    int     ele_no  = (m_max - 1) / 2;
    Integer int_val = ang_repr_flg - 10;

    prod_distr_prob_int_vec[i][j][k][l].resize(1);
    prod_distr_prob_range_vec[i][j][k][l].resize(1);
    prod_distr_prob_int_vec[i][j][k][l][0]   = int_val;
    prod_distr_prob_range_vec[i][j][k][l][0] = static_cast<int>(ele_no);

    prod_distr_prob_mu_vec[i][j][k][l].resize(ele_no);
    prod_distr_prob_vec[i][j][k][l].resize(ele_no);
    prod_distr_prob_vec_integ[i][j][k][l].resize(ele_no);
    for(int m=0; m<ele_no; m++)
    {
      prod_distr_prob_mu_vec[i][j][k][l][m] = cont_data[2*m+1];
      prod_distr_prob_vec[i][j][k][l][m]    = cont_data[2*m+2];
    }

    Real   sum        = 0.0;
    string func_name  = "calc_kalbach_angle_distr_new_cummulative_angle_distr";
    integ_obj.integrate_for_ace_data(class_name, func_name, 
                                     prod_distr_prob_mu_vec[i][j][k][l],    prod_distr_prob_vec[i][j][k][l],
                                     prod_distr_prob_vec_integ[i][j][k][l], int_val, sum);
  } 
  else //if( ang_repr_flg == 2 || ang_repr_flg <= 0 )
  {
    string func_name = "calc_kalbach_angle_distr_new_cummulative_angle_distr";
    ostringstream oss01, oss02, oss03, oss04, oss05;
    oss01 << i+1;
    oss02 << j+1;
    oss03 << k+1;
    oss04 << l+1;
    oss05 << ang_repr_flg;
    string str_data01 = "Position     : " + oss01.str() + ", " + oss02.str() + ", "
                                          + oss03.str() + ", " + oss04.str();
    string str_data02 = "ang_repr_flg : " + oss05.str();
    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("This ang_repr_flg is not available in this program.");
    err_com.push_back("Please check the program or ang_repr_flg.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Real FastAceDataGenerator::calc_kalbach_mann_parameter
                             (Integer mat_data_a, Integer mat_data_b, Real& ene_in, Real& ene_out)
{
  //Refferences of the calculation formula
  //C. Kalbach, "Systematics of continuum angular distributions: Extensions to higher energies,"
  //Phys. Rev. C, 37, pp.2350-2370 (1988).
  //A. Trkov, M. Herman, D. A. Brown, "ENDF-6 Formats Manual," BNL-90365-2009 Rev.2

  Integer mat_data_base = static_cast<Integer>(round(nucl_data_obj.get_general_data_obj().get_mat_data()));
  Real    one_third     = 1.0 / 3.0;

  int mat_data_flg = 0;
  if( mat_data_a == 0 )
  {
    mat_data_flg = 1;
    mat_data_a   = 1;
  }

  check_mat_data_for_kalbach_mann_parameter(mat_data_base);

  Real a_a = static_cast<Real>(mat_data_base%1000);
  Real z_a = static_cast<Real>(mat_data_base/1000);
  Real a_c = a_a + static_cast<Real>(mat_data_a%1000);
  Real z_c = z_a + static_cast<Real>(mat_data_a/1000);
  Real a_b = a_c - static_cast<Real>(mat_data_b%1000);
  Real z_b = z_c - static_cast<Real>(mat_data_b/1000);
  Real n_a = round(a_a - z_a);
  Real n_b = round(a_b - z_b);
  Real n_c = round(a_c - z_c);

  Real coef_a   = (n_a - z_a) * (n_a - z_a) / a_a;
  Real coef_b   = (n_b - z_b) * (n_b - z_b) / a_b;
  Real coef_c   = (n_c - z_c) * (n_c - z_c) / a_c;
  Real coef_a_a = pow(a_a, one_third);
  Real coef_a_b = pow(a_b, one_third);
  Real coef_a_c = pow(a_c, one_third);
  Real z_a_sq   = z_a * z_a;
  Real z_b_sq   = z_b * z_b;
  Real z_c_sq   = z_c * z_c;

  Real s_a = 15.68*(a_c - a_a) - 28.07*(coef_c - coef_a)  - 18.56*(coef_a_c*coef_a_c - coef_a_a*coef_a_a)
           + 33.22*(coef_c/coef_a_c - coef_a/coef_a_a)    - 0.717*(z_c_sq/coef_a_c  - z_a_sq/coef_a_a)
           + 1.211*(z_c_sq/a_c - z_a_sq/a_a);
  Real s_b = 15.68*(a_c - a_b) - 28.07*(coef_c - coef_b)  - 18.56*(coef_a_c*coef_a_c - coef_a_b*coef_a_b)
           + 33.22*(coef_c/coef_a_c - coef_b/coef_a_b)    - 0.717*(z_c_sq/coef_a_c  - z_b_sq/coef_a_b)
           + 1.211*(z_c_sq/a_c - z_b_sq/a_b);

  if( mat_data_a == 1002 )
  {
    s_a -= 2.22;
  }
  else if( mat_data_a == 1003 )
  {
    s_a -= 8.48;
  }
  else if( mat_data_a == 2003 )
  {
    s_a -= 7.72;
  }
  else if( mat_data_a == 2004 )
  {
    s_a -= 28.3;
  }

  if( mat_data_b == 1002 )
  {
    s_b -= 2.22;
  }
  else if( mat_data_b == 1003 )
  {
    s_b -= 8.48;
  }
  else if( mat_data_b == 2003 )
  {
    s_b -= 7.72;
  }
  else if( mat_data_b == 2004 )
  {
    s_b -= 28.3;
  }

  Real ene_a = (a_a * ene_in  * unit_micro / a_c) + s_a;
  Real ene_b = (a_c * ene_out * unit_micro / a_b) + s_b;

  Real x_1 = ene_b;
  Real x_3 = ene_b;
  if( ene_a > 130.0 )
  {
    x_1 = 130.0 * ene_b/ene_a;
  }
  if( ene_a > 41.0 )
  {
    x_3 = 41.0 * ene_b/ene_a;
  }

  Real f_a = 1.0;
  Real f_b = 1.0;
  if( mat_data_a == 2004 )
  {
    f_a = 0.0;
  }
  if( mat_data_b == 1 )
  {
    f_b = 0.5;
  }
  else if( mat_data_b == 2004 )
  {
    f_b = 2.0;
  }

  Real kalbach_mann_factor = 0.04*x_1 + 1.8E-6*(x_1*x_1*x_1) + 6.7E-7*f_a*f_b*(x_3*x_3*x_3*x_3);
  if( mat_data_flg  > 0 )
  {
    Real coef_ene = 9.3;
    if( fabs(ene_out) > min_value )
    {
      coef_ene /= sqrt(ene_out);
    }

    if( coef_ene < 1.0 )
    {
      coef_ene = 1.0;
    }
    else if( coef_ene > 4.0 )
    {
      coef_ene = 4.0;
    }

    Real emc_sq = unit_micro * amu_n * amu * light_speed * light_speed * 1.0E4 / ev;
    kalbach_mann_factor *= sqrt(ene_in/(2.0*emc_sq)) * coef_ene;
  } 

  return kalbach_mann_factor;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::check_mat_data_for_kalbach_mann_parameter(Integer& mat_data_base)
{
  switch( mat_data_base )
  {
    case  6000:
      mat_data_base =  6012;
      break;
    case 12000:
      mat_data_base = 12024;
      break;
    case 14000:
      mat_data_base = 14028;
      break;
    case 16000:
      mat_data_base = 16032;
      break;
    case 17000:
      mat_data_base = 17035;
      break;
    case 19000:
      mat_data_base = 19039;
      break;
    case 20000:
      mat_data_base = 20040;
      break;
    case 22000:
      mat_data_base = 22048;
      break;
    case 23000:
      mat_data_base = 23051;
      break;
    case 24000:
      mat_data_base = 24052;
      break;
    case 26000:
      mat_data_base = 26056;
      break;
    case 28000:
      mat_data_base = 28058;
      break;
    case 29000:
      mat_data_base = 29063;
      break;
    case 31000:
      mat_data_base = 31069;
      break;
    case 40000:
      mat_data_base = 40090;
      break;
    case 42000:
      mat_data_base = 42096;
      break;
    case 48000:
      mat_data_base = 48112;
      break;
    case 49000:
      mat_data_base = 49115;
      break;
    case 50000:
      mat_data_base = 50120;
      break;
    case 63000:
      mat_data_base = 63151;
      break;
    case 72000:
      mat_data_base = 72178;
      break;
    case 74000:
      mat_data_base = 74184;
      break;
    case 82000:
      mat_data_base = 82208;
      break;
    default:
      if( mat_data_base%1000 == 0 )
      {
        string func_name  = "check_mat_data_for_kalbach_mann_parameter";
        ostringstream oss01;
        oss01 << mat_data_base;
        string str_data01 = "Material data : " + oss01.str();
        vector<string> err_com;
        err_com.push_back(str_data01);
        err_com.push_back("This material data is not available.");
        err_com.push_back("Please check the program or material data.");
        err_obj.output_runtime_error(class_name, func_name, err_com);
      }
    break;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::calc_kalbach_angle_distr_by_ave_data
                             ( Integer react_type, Real& coef_a, Real& coef_b, Real& f_even, Real& f_odd,
                               Real& ene_in, Real& ene_out )
{
  if( f_odd < 0.0 )
  {
    f_odd = 0.0;

    string func_name  = "calc_kalbach_angle_distr_by_ave_data";
    ostringstream oss01, oss02, oss03, oss04;
    oss01 << react_type;
    oss02 << ene_in;
    oss03 << ene_out;
    oss04 << f_odd;
    string str_data01 = "Reaction type          : " + oss01.str();
    string str_data02 = "Input energy           : " + oss02.str();
    string str_data03 = "Output energy          : " + oss03.str();
    string str_data04 = "Converted distribution : " + oss04.str();
    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back("Converted distribution is negative.");
    err_com.push_back("Converted distribution is modified to 0.0.");
    err_obj.output_caution(class_name, func_name, err_com);
  }

  coef_a = 2.0*f_even*(1.0 - 4.0*f_even*f_even/3.0);

  int count    = 0;
  int conv_flg = 0;
  while( count < 30 )
  {
    Real coef_val = coef_a/tanh(coef_a) - 2.0*f_even;
    if( fabs(coef_val) < min_ene_dif )
    {
      conv_flg = 1;
      break;
    }

    Real sinh_2a = sinh(2.0*coef_a);
    Real cosh_2a = cosh(2.0*coef_a);
    Real delta_a = (2.0*f_even*(cosh_2a - 1.0) - coef_a*sinh_2a) / (sinh_2a - 2.0*coef_a);

    coef_a = fabs(coef_a + delta_a);
    count++;
  }

  coef_b = 0.0;
  if( conv_flg == 0 )
  {
    coef_a = 1.0E-5;

    string func_name  = "calc_kalbach_angle_distr_by_ave_data";
    ostringstream oss01, oss02, oss03;
    oss01 << react_type;
    oss02 << ene_in;
    oss03 << ene_out;
    string str_data01 = "Reaction type          : " + oss01.str();
    string str_data02 = "Input energy           : " + oss02.str();
    string str_data03 = "Output energy          : " + oss03.str();
    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("Kalbach coefficient is not converged.");
    err_com.push_back("Kalbach coefficient is modified to 1.0E-5.");
    err_obj.output_caution(class_name, func_name, err_com);
  }
  else
  {
    if( coef_a < 0.0 ) //For count = 0 case
    {
      coef_a = 1.0E-5;

      string func_name  = "calc_kalbach_angle_distr_by_ave_data";
      ostringstream oss01, oss02, oss03;
      oss01 << react_type;
      oss02 << ene_in;
      oss03 << ene_out;
      string str_data01 = "Reaction type          : " + oss01.str();
      string str_data02 = "Input energy           : " + oss02.str();
      string str_data03 = "Output energy          : " + oss03.str();
      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back("Kalbach coefficient is negative.");
      err_com.push_back("Kalbach coefficient is modified to 1.0E-5.");
      err_obj.output_caution(class_name, func_name, err_com);
    }
    else
    {
      if( coef_a > min_value )
      {
        coef_b = f_odd / coef_a;
      }

      if( coef_b < 0.0 || coef_b > 1.0 )
      {
        if( coef_b < 0.0 )
        {
          coef_b = 0.0;
        }
        else
        {
          coef_b = 1.0;
        }

        string func_name  = "calc_kalbach_angle_distr_by_ave_data";
        ostringstream oss01, oss02, oss03;
        oss01 << react_type;
        oss02 << ene_in;
        oss03 << ene_out;
        string str_data01 = "Reaction type          : " + oss01.str();
        string str_data02 = "Input energy           : " + oss02.str();
        string str_data03 = "Output energy          : " + oss03.str();
        vector<string> err_com;
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back("Kalbach coefficient is unreasonable.");
        err_com.push_back("Kalbach coefficient is modified.");
        err_obj.output_caution(class_name, func_name, err_com);
      }

      if( coef_a < 1.0E-5 )
      {
        coef_a = 1.0E-5;
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::calc_kalbach_angle_distr_by_table_data
                             ( Integer react_type, Real& coef_a, Real& coef_b, Real& tab_a, Real& tab_b,
                               Real& tab_c, Real& tab_d, Real& ene_in, Real& ene_out )
{
  string func_name  = "calc_kalbach_angle_distr_by_table_data";
  ostringstream oss01, oss02, oss03;
  oss01 << react_type;
  oss02 << ene_in;
  oss03 << ene_out;
  string str_data01 = "Reaction type          : " + oss01.str();
  string str_data02 = "Input energy           : " + oss02.str();
  string str_data03 = "Output energy          : " + oss03.str();
  vector<string> err_com;
  err_com.push_back(str_data01);
  err_com.push_back(str_data02);
  err_com.push_back(str_data03);
  err_com.push_back("Tabulated angular distribution does not extend over entire cosine range");
  err_obj.output_caution(class_name, func_name, err_com);

  int count    = 0;
  int conv_flg = 0;

  Real f_val     = tab_b + tab_a;
  Real tab_delta = tab_d - tab_c;

  Real cosh_a, cosh_a_m, cosh_a_p, cosh_a_d, sinh_a, sinh_a_m, sinh_a_p, sinh_a_d;
  coef_a = f_val * ( 1.0 - pow(f_val,2.0/3.0) );
  while( count < 30 )
  {
    cosh_a   = cosh(coef_a);
    cosh_a_m = cosh(coef_a*tab_c);
    cosh_a_p = cosh(coef_a*tab_d);
    cosh_a_d = cosh(coef_a*tab_delta);
    sinh_a   = sinh(coef_a);
    sinh_a_m = sinh(coef_a*tab_c);
    sinh_a_p = sinh(coef_a*tab_d);
    sinh_a_d = sinh(coef_a*tab_delta);

    Real coef_val = tab_b*sinh_a_m - tab_a*sinh_a_p + coef_a*sinh_a_d / (2.0*sinh_a);
    if( fabs(coef_val) < min_ene_dif )
    {
      conv_flg = 1;
      break;
    }

    Real coef_delta_a = sinh_a_d*(sinh_a - coef_a*cosh_a) + coef_a*tab_delta*cosh_a_d*sinh_a
                      + 2.0*sinh_a*sinh_a*(tab_b*tab_c*cosh_a_m - tab_a*tab_d*cosh_a_p);
    coef_a += ( 2.0*sinh_a*(tab_a*sinh_a_p - tab_b*sinh_a_m) - coef_a*sinh_a_d ) * sinh_a/coef_delta_a;
  }

  coef_b = 0.0;
  if( conv_flg == 0 )
  {
    coef_a = 1.0E-5;

    string func_name  = "calc_kalbach_angle_distr_by_table_data";
    vector<string> err_com;
    err_com.push_back("Kalbach coefficient is not converged.");
    err_com.push_back("Kalbach coefficient is modified to 1.0E-5.");
    err_obj.output_caution(class_name, func_name, err_com);
  }
  else
  {
    if( coef_a < 0.0 ) //For count = 0 case
    {
      coef_a = 1.0E-5;

      string func_name  = "calc_kalbach_angle_distr_by_table_data";
      vector<string> err_com;
      err_com.push_back("Kalbach coefficient is negative.");
      err_com.push_back("Kalbach coefficient is modified to 1.0E-5.");
      err_obj.output_caution(class_name, func_name, err_com);
    }
    else
    {
      if( coef_a > min_value )
      {
        Real sinh_2a = sinh(2.0*coef_a);
        coef_b = 2.0*sinh_a*(tab_b*cosh_a_m - tab_a*cosh_a_p) / (coef_a*sinh_2a);
      }

      if( coef_b < 0.0 || coef_b > 1.0 )
      {
        if( coef_b < 0.0 )
        {
          coef_b = 0.0;
        }
        else
        {
          coef_b = 1.0;
        }

        string func_name  = "calc_kalbach_angle_distr_by_table_data";
        err_com.push_back("Kalbach coefficient is unreasonable.");
        err_com.push_back("Kalbach coefficient is modified.");
        err_obj.output_caution(class_name, func_name, err_com);
      }

      if( coef_a < 1.0E-5 )
      {
        coef_a = 1.0E-5;
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_lab_ene_angle_distr_data
                             (int i, int j, int pos, ProductDistributionDataContainer& prod_distr_data_obj)
{
  prod_distr_prob_ene_in_data[i][j]   = prod_distr_data_obj.get_lab_ene()[pos];
  prod_distr_prob_mu_int_data[i][j]   = prod_distr_data_obj.get_lab_cos_int_data()[pos];
  prod_distr_prob_mu_range_data[i][j] = prod_distr_data_obj.get_lab_cos_range_data()[pos];
  prod_distr_prob_mu_data[i][j]       = prod_distr_data_obj.get_lab_cos()[pos];
  prod_distr_prob_ene_out_vec[i][j]   = prod_distr_data_obj.get_lab_ene_sec_data()[pos];
  prod_distr_prob_vec[i][j]           = prod_distr_data_obj.get_lab_data()[pos];
  prod_distr_prob_int_vec[i][j]       = prod_distr_data_obj.get_lab_int_data()[pos];
  prod_distr_prob_range_vec[i][j]     = prod_distr_data_obj.get_lab_range_data()[pos];

  int k_max = static_cast<int>(prod_distr_prob_ene_out_vec[i][j].size());
  prod_distr_prob_vec_integ[i][j].resize(k_max);
  for(int k=0; k<k_max; k++)
  {
    int l_max = static_cast<int>(prod_distr_prob_ene_out_vec[i][j][k].size());
    prod_distr_prob_vec_integ[i][j][k].resize(l_max);
    for(int l=0; l<l_max; l++)
    {
      vector<Integer> int_vec   = prod_distr_prob_int_vec[i][j][k][l];
      vector<Integer> range_vec = prod_distr_prob_range_vec[i][j][k][l];

      //Calculatio of integration value
      int m_max = static_cast<int>(prod_distr_prob_ene_out_vec[i][j][k][l].size());
      prod_distr_prob_vec_integ[i][j][k][l].resize(m_max);
      prod_distr_prob_vec_integ[i][j][k][l][0] = 0.0;
      for(int m=0; m<m_max; m++)
      {
        if( m != 0 )
        {
          Integer int_val = ti_obj.search_interpolation_range(range_vec, int_vec, m);
          prod_distr_prob_vec_integ[i][j][k][l][m] = prod_distr_prob_vec_integ[i][j][k][l][m-1]
            + integ_obj.integrate_data(prod_distr_prob_ene_out_vec[i][j][k][l][m-1],
                                       prod_distr_prob_vec[i][j][k][l][m-1],
                                       prod_distr_prob_ene_out_vec[i][j][k][l][m],
                                       prod_distr_prob_vec[i][j][k][l][m],
                                       int_val);

          if( int_val == int_const )
          {
          }
          else if( int_val == int_lin_lin )
          {
          }
          else
          {
            string func_name  = "set_lab_ene_angle_distr_data";
            ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07;
            oss01 << prod_distr_data_obj.get_reaction_type();
            oss02 << i+1;
            oss03 << j+1;
            oss04 << k+1;
            oss05 << l+1;
            oss06 << m+1;
            oss07 << int_val;
            string str_data01 = "Reaction type      : " + oss01.str();
            string str_data02 = "Position           : " + oss02.str() + ", " + oss03.str() + ", "
                                                        + oss04.str() + ", " + oss05.str() + ", "
                                                        + oss06.str();
            string str_data03 = "Interpolation type : " + oss07.str();
            vector<string> err_com;
            err_com.push_back(str_data01);
            err_com.push_back(str_data02);
            err_com.push_back(str_data03);
            err_com.push_back("This interpolation type may not be available.");
            err_com.push_back("Available interpolation type is constant and linear-linear.");
            err_obj.output_runtime_error(class_name, func_name, err_com);
          }
        }
      }

      //Normalization of probability values
      if( m_max > 0 )
      {
        Real sum_inv = 1.0 / prod_distr_prob_vec_integ[i][j][k][l][m_max-1];
        for(int m=0; m<m_max; m++)
        {
          prod_distr_prob_ene_out_vec[i][j][k][l][m] *= unit_micro;
          prod_distr_prob_vec[i][j][k][l][m]         *= sum_inv;
          prod_distr_prob_vec_integ[i][j][k][l][m]   *= sum_inv;
        }
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_prob_table()
{
  UnresolvedProbabilityDataContainer unreso_prob_obj;
  unreso_prob_obj = nucl_data_obj.get_reso_data_obj().get_unreso_prob_data_obj();

  //unreso_prob_tab_int_data = 2; //int_lin_lin
  unreso_prob_tab_int_data = unreso_prob_obj.get_prob_int();

  unreso_prob_tab_inela_comp_flg = unreso_prob_obj.get_comp_flg_inela();
  unreso_prob_tab_abs_comp_flg   = unreso_prob_obj.get_comp_flg_abs();

  if( unreso_prob_tab_inela_comp_flg == 0 )
  {
    Integer comp_flg = unreso_prob_obj.get_comp_flg();
    unreso_prob_tab_inela_comp_flg = comp_flg%1000;
    unreso_prob_tab_abs_comp_flg   = comp_flg/1000;
    if( unreso_prob_tab_inela_comp_flg == 0 )
    {
      unreso_prob_tab_inela_comp_flg = -1;
    }
    if( unreso_prob_tab_abs_comp_flg == 0 )
    {
      unreso_prob_tab_abs_comp_flg = -1;
    }
  }

  unreso_prob_tab_self_shielding_flg = unreso_prob_obj.get_self_shielding_flg();
  unreso_prob_tab_ene                = unreso_prob_obj.get_prob_ene();
  unreso_prob_tab_heat               = unreso_prob_obj.get_prob_heat();
  unreso_prob_tab_sample_no          = unreso_prob_obj.get_prob_table_sample_no();
  unreso_prob_tab_table              = unreso_prob_obj.get_prob_table();

  int i_max = static_cast<int>(unreso_prob_tab_ene.size());
  for(int i=0; i<i_max; i++)
  {
    unreso_prob_tab_ene[i] *= unit_micro;
    if( unreso_prob_tab_self_shielding_flg == 0 )
    {
      int j_max = static_cast<int>(unreso_prob_tab_heat[i].size());
      for(int j=0; j<j_max; j++)
      {
        unreso_prob_tab_heat[i][j] *= unit_micro;
      }
    }


    int fis_flg = 0;
    int j_max = static_cast<int>(unreso_prob_tab_sample_no[i].size()); //bin_no
    for(int j=0; j<j_max; j++)
    {
      if( unreso_prob_tab_table[i][fission_xs][j] > min_sig_val * 1.1 )
      {
        fis_flg = 1;
        break;
      }
    }

    for(int j=1; j<j_max; j++)
    {
      unreso_prob_tab_sample_no[i][j] += unreso_prob_tab_sample_no[i][j-1];
    }
    unreso_prob_tab_sample_no[i][j_max-1] = 1.0; //To correct rounding error

    vector<Real8> xs_tot_vec;
    xs_tot_vec.resize(j_max);
    for(int j=0; j<j_max; j++)
    {
      xs_tot_vec[j] = 0.0;
    }

    j_max = static_cast<int>(unreso_prob_tab_table[i].size()); //xs_type_no
    for(int j=0; j<j_max; j++)
    {
      int k_max = static_cast<int>(unreso_prob_tab_table[i][j].size()); //bin_no
      for(int k=0; k<k_max; k++)
      {
        if( unreso_prob_tab_table[i][j][k] < min_sig_val )
        {
          if( fabs(unreso_prob_tab_table[i][j][k]) > min_sig_val )
          {
            string func_name  = "set_prob_table";
            ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07;
            oss01 << i+1;
            oss02 << i_max;
            oss03 << j+1;
            oss04 << j_max;
            oss05 << k+1;
            oss06 << k_max;

            oss07.precision(8);
            oss07.setf(ios::showpoint);
            oss07.setf(ios::scientific);
            oss07 << unreso_prob_tab_table[i][j][k];

            string str_data01 = "position               : " + oss01.str() + " / " + oss02.str() + ", "
                              + oss03.str() + " / " + oss04.str() + ", "  + oss05.str() + " / " + oss06.str();
            string str_data02 = "probability table data : " + oss07.str();

            vector<string> err_com;
            err_com.push_back(str_data01);
            err_com.push_back(str_data02);
            err_com.push_back("");
            err_com.push_back("Probability table data is less than 0.0.");
            err_com.push_back("Probability table data is modified to 1.0E-40.");
            err_obj.output_caution(class_name, func_name, err_com);
          }

          unreso_prob_tab_table[i][j][k] = min_sig_val;
          if( j == fission_xs && fis_flg == 0 )
          {
            unreso_prob_tab_table[i][j][k] = 0.0;
          }
        }
      }


      if( j == total_xs )
      {
        //Check the order of total probability table
        for(int k=1; k<k_max; k++)
        {
          if( unreso_prob_tab_table[i][total_xs][k] - unreso_prob_tab_table[i][total_xs][k-1] < 0.0 )
          {
            string func_name  = "set_prob_table";

            ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07, oss08;
            oss03.precision(8);
            oss06.precision(8);
            oss07.precision(8);
            oss03.setf(ios::showpoint);
            oss06.setf(ios::showpoint);
            oss07.setf(ios::showpoint);
            oss03.setf(ios::scientific);
            oss06.setf(ios::scientific);
            oss07.setf(ios::scientific);
            oss01 << i+1;
            oss02 << i_max;
            oss03 << unreso_prob_tab_ene[i];
            oss04 << k+1;
            oss05 << k_max;
            oss06 << unreso_prob_tab_table[i][total_xs][k-1];
            oss07 << unreso_prob_tab_table[i][total_xs][k];
            string str_data01 = "Position of energy           : " + oss01.str() + " / " + oss02.str();
            string str_data02 = "Energy [MeV]                 : " + oss03.str();
            string str_data03 = "Position of probability bin  : " + oss04.str() + " / " + oss05.str();
            string str_data04 = "Probability table (total)    : " + oss06.str() + " - " + oss07.str();
            string str_data05 = "                                (p_table_tot[i] - p_table_tot[i-1])";

            vector<string> err_com;
            err_com.push_back(str_data01);
            err_com.push_back(str_data02);
            err_com.push_back(str_data03);
            err_com.push_back(str_data04);
            err_com.push_back("The order of the total probability table must be ascending order.");
            err_com.push_back("However, this probability table is not ascending order.");
            err_com.push_back("This probability table may be incorrect.");
            err_com.push_back("");
            err_com.push_back("  Order of total probability table");
            for(int l=0; l<k_max; l++)
            {
              ostringstream oss11;
              oss11.precision(8);
              oss11.setf(ios::showpoint);
              oss11.setf(ios::scientific);
              oss11 << unreso_prob_tab_table[i][total_xs][l];
              string str_data11 = "    " + oss11.str();
              if( l == k )
              {
                str_data11 = str_data11 + " ***";
              }
              err_com.push_back(str_data11);
            }

            //Modify total probability table
            if( unreso_prob_tab_sample_no[i][k] - unreso_prob_tab_sample_no[i][k-1] < min_value )
            {
              err_com.push_back("");
              err_com.push_back("The probability table at this energy grid is modified.");
              err_com.push_back("(p_table_tot[i] = p_table_tot[i-1])");
              for(int j=0; j<xs_type_no; j++)
              {
                unreso_prob_tab_table[i][j][k] = unreso_prob_tab_table[i][j][k-1];
              }
            }

            err_obj.output_caution(class_name, func_name, err_com);
          }
        }
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_delayed_neutron_data()
{
  if( mt_455_flg == 0 )
  {
    if( static_cast<int>(fis_data_obj.get_nu_d_ene_data().size()) != 0 )
    {
      string func_name  = "set_delayed_neutron_data";
      vector<string> err_com;
      err_com.push_back("The delayed neutron data is found.");
      err_com.push_back("But delayed neutron spectra is not found.");
      err_com.push_back("The delayed neutron data process is skipped.");
      err_obj.output_caution(class_name, func_name, err_com);
    }
    return;
  }

  int pos = 0;
  set_delayed_neutron_data_common(pos);

  vector<Integer> ene_repr_flg = ene_angle_data_obj_vec[pos].get_ene_repr_flg();

  int i_max = static_cast<int>(ene_repr_flg.size());
  nu_d_ene_in_int_data.resize(i_max);
  nu_d_ene_in_range_data.resize(i_max);
  nu_d_ene_in_data.resize(i_max);
  nu_d_ene_out_int_data.resize(i_max);
  nu_d_ene_out_data.resize(i_max);
  nu_d_ene_distr_data.resize(i_max);
  nu_d_ene_distr_data_integ.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    if(ene_repr_flg[i] == 1)
    {
      set_delayed_neutron_data_table(i, ene_angle_data_obj_vec[pos]);
    }
    else if(ene_repr_flg[i] == 5)
    {
      set_delayed_neutron_data_spectrum(i, ene_angle_data_obj_vec[pos]);
    }
  } 
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_delayed_neutron_data_common(int& pos)
{
  vector<vector<Real> > decay_constant = fis_data_obj.get_nu_d_decay_constant();
  if( static_cast<int>(decay_constant.size()) != 1 )
  {
    string func_name  = "set_delayed_neutron_data_common";
    ostringstream oss01;
    oss01 << static_cast<int>(decay_constant.size());
    string str_data01 = "Number of energy data for decay constant : " + oss01.str();
    vector<string> err_com;
    err_com.push_back(str_data01);
    if( static_cast<int>(decay_constant.size()) > 1 )
    {
      err_com.push_back("The delayed neutron decay constant is energy dependent.");
      err_com.push_back("This decay constant can not be treated in this program.");
    }
    else
    {
      err_com.push_back("There is no decay constant data.");
    }
    err_obj.output_runtime_error(class_name, func_name, err_com);
  } 

  nu_d_decay_constant = decay_constant[0];

  pos = 0;
  for(int i=0; i<static_cast<int>(ene_angle_data_obj_vec.size()); i++)
  {
    if( ene_angle_data_obj_vec[i].get_reaction_type() == 455 )
    {
      pos = i;
      break;
    }
  }

  nu_d_xs_part_int_data    = ene_angle_data_obj_vec[pos].get_xs_part_int_data();
  nu_d_xs_part_range_data  = ene_angle_data_obj_vec[pos].get_xs_part_range_data();
  nu_d_xs_part_ene_data    = ene_angle_data_obj_vec[pos].get_xs_part_ene_data();
  nu_d_xs_part_data        = ene_angle_data_obj_vec[pos].get_xs_part_data();

  int i_max = static_cast<int>(nu_d_xs_part_ene_data.size());
  if( i_max != static_cast<int>(nu_d_decay_constant.size()) )
  {
    string func_name  = "set_delayed_neutron_data_common";
    ostringstream oss01, oss02, oss03;
    oss01 << ene_angle_data_obj_vec[pos].get_reaction_type();
    oss02 << static_cast<int>(nu_d_decay_constant.size());
    oss03 << i_max;
    string str_data01 = "Reaction type                                                : " + oss01.str();
    string str_data02 = "Number of decay constant                                     : " + oss02.str();
    string str_data03 = "Number of energy data for decay constant energy distribution : " + oss03.str();
    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("The number of energy data is not identical.");
    err_com.push_back("");
    err_com.push_back("Decay data of delayed neutron may be in appropriate.");
    err_com.push_back("Please check the number of energy grid of nu_d_decay_constant");
    err_com.push_back("(ramda in MF=1, MT=455) and number of energy distributions (NK in MF=5, MT=455).");
    if( static_cast<int>(nu_d_decay_constant.size()) != 1 )
    {
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
    else
    {
      ostringstream oss_nu_d;
      oss_nu_d.setf(ios::showpoint);
      oss_nu_d.setf(ios::scientific);
      oss_nu_d << setw(8) << nu_d_decay_constant[0];
      string str_data_nu_d = "( " + oss_nu_d.str() + " )";

      err_com.push_back("");
      err_com.push_back("The number of decay constant is modified.");
      err_com.push_back("All decay constant data is identical to nu_d_decay_constant[0]");
      err_com.push_back(str_data_nu_d);
      err_obj.output_caution(class_name, func_name, err_com);

      Real nu_d_decay_constant_tmp = nu_d_decay_constant[0];
      nu_d_decay_constant.resize(i_max);
      for(int i=0; i<i_max; i++)
      {
        nu_d_decay_constant[i] = nu_d_decay_constant_tmp;
      }
    }
  }

  nu_d_ene_min.resize(i_max);
  nu_d_ene_max.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    nu_d_decay_constant[i] *= 1.0E-8;

    int j_max = static_cast<int>(nu_d_xs_part_ene_data[i].size());
    for(int j=0; j<j_max; j++)
    {
      nu_d_xs_part_ene_data[i][j] *= unit_micro;
    }
    nu_d_ene_min[i] = nu_d_xs_part_ene_data[i][0];
    nu_d_ene_max[i] = nu_d_xs_part_ene_data[i][j_max-1];
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_delayed_neutron_data_table
                             (int i, EnergyAngularDataContainer& ene_angle_data_obj)
{
  string func_name  = "set_delayed_neutron_data_table";

  nu_d_ene_in_data[i]       = ene_angle_data_obj.get_incident_ene()[i];
  nu_d_ene_in_int_data[i]   = ene_angle_data_obj.get_ene_int_data()[i];
  nu_d_ene_in_range_data[i] = ene_angle_data_obj.get_ene_range_data()[i];
  nu_d_ene_out_data[i]      = ene_angle_data_obj.get_ene_part_ene_data()[i];
  nu_d_ene_distr_data[i]    = ene_angle_data_obj.get_ene_part_data()[i];

  int j_max = static_cast<int>(nu_d_ene_in_data[i].size());
  nu_d_ene_out_int_data[i].resize(j_max);
  nu_d_ene_distr_data_integ[i].resize(j_max);
  for(int j=0; j<j_max; j++)
  {
    nu_d_ene_in_data[i][j] *= unit_micro;

    vector<Integer> int_vec   = ene_angle_data_obj.get_ene_part_int_data()[i][j];
    vector<Integer> range_vec = ene_angle_data_obj.get_ene_part_range_data()[i][j];
    nu_d_ene_out_int_data[i][j] = int_vec[0];

    int int_flg = 0;
    int k_max   = static_cast<int>(int_vec.size());
    for(int k=1; k<k_max; k++)
    {
      if(int_vec[k] != int_vec[0])
      {
        int_flg = 1;

        ostringstream oss01, oss02, oss03, oss04, oss05;
        oss01 << i+1;
        oss02 << j+1;
        oss03 << k+1;
        oss04 << int_vec[0];
        oss05 << int_vec[k];
        string str_data01 = "Position                    : " + oss01.str() + ", "
                                                             + oss02.str() + ", " + oss03.str();
        string str_data02 = "Interpolation type at k = 0 : " + oss04.str();
        string str_data03 = "Interpolation type at k = " + oss03.str() + " : " + oss05.str();
        vector<string> err_com;
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back("Interpolation data is not identical.");
        err_com.push_back("The TAB1 data is linearized before processing.");
        err_obj.output_caution(class_name, func_name, err_com);

        break;
      }
    }
    if( int_flg != 0 )
    {
      nu_d_ene_out_int_data[i][j] = int_lin_lin;

      //Linearization of delayed neutron data before processing
      lin_tab_obj.linearize_tab1_data(range_vec, int_vec,
                                      nu_d_ene_out_data[i][j], nu_d_ene_distr_data[i][j]);
      
    }

    Real sum = 0.0;
    integ_obj.integrate_for_ace_data(class_name, func_name,
                                     nu_d_ene_out_data[i][j], nu_d_ene_distr_data[i][j],
                                     nu_d_ene_distr_data_integ[i][j], int_vec[0], sum);

    k_max = static_cast<int>(nu_d_ene_out_data[i][j].size());
    nu_d_ene_distr_data_integ[i][j].resize(k_max);
    for(int k=0; k<k_max; k++)
    {
      nu_d_ene_out_data[i][j][k]   *= unit_micro;
      nu_d_ene_distr_data[i][j][k] *= unit_mega;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_delayed_neutron_data_spectrum
                             (int i, EnergyAngularDataContainer& ene_angle_data_obj)
{
  string func_name  = "set_delayed_neutron_data_table";

  nu_d_ene_in_data[i].resize(2);
  nu_d_ene_in_int_data[i].resize(1);
  nu_d_ene_in_range_data[i].resize(1);

  nu_d_ene_in_data[i][0]       = nu_d_ene_min[i];
  nu_d_ene_in_data[i][1]       = nu_d_ene_max[i];
  nu_d_ene_in_int_data[i][0]   = int_lin_lin;
  nu_d_ene_in_range_data[i][0] = 2;

  vector<Integer> int_vec   = ene_angle_data_obj.get_ene_part_int_data()[i][0];
  vector<Integer> range_vec = ene_angle_data_obj.get_ene_part_range_data()[i][0];

  int int_flg = 0;
  int j_max   = static_cast<int>(int_vec.size());
  for(int j=1; j<j_max; j++)
  {
    if(int_vec[j] != int_vec[0])
    {
      int_flg = 1;

      ostringstream oss01, oss02, oss03, oss04;
      oss01 << i+1;
      oss02 << j+1;
      oss03 << int_vec[0];
      oss04 << int_vec[j];
      string str_data01 = "Position                    : " + oss01.str() + ", " + oss02.str();
      string str_data02 = "Interpolation type at j = 0 : " + oss03.str();
      string str_data03 = "Interpolation type at j = " + oss02.str() + " : " + oss04.str();
      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back("Interpolation data is not identical.");
      err_com.push_back("The TAB1 data is linearized before processing.");
      err_com.push_back("Please check the nuclear data or modify the program.");
      err_obj.output_caution(class_name, func_name, err_com);

      break;
    }
  }

  vector<Real> x_vec = ene_angle_data_obj.get_ene_part_ene_data()[i][0];
  vector<Real> y_vec = ene_angle_data_obj.get_ene_part_data()[i][0];
  if( int_flg != 0 )
  {
    //Linearization of delayed neutron data before processing
    lin_tab_obj.linearize_tab1_data(range_vec, int_vec, x_vec, y_vec);
  }

  if( int_vec[0] == 1 )
  {
    modify_delayed_neutron_data(i, x_vec, y_vec);
  }

  Real sum = 0.0;
  vector<Real> y_integ;
  integ_obj.integrate_for_ace_data(class_name, func_name, x_vec, y_vec, y_integ, int_vec[0], sum);

  j_max = static_cast<int>(y_vec.size());
  for(int j=0; j<j_max; j++)
  {
    x_vec[j] *= unit_micro;
    y_vec[j] *= unit_mega;
  }

  nu_d_ene_out_int_data[i].resize(2);
  nu_d_ene_out_data[i].resize(2);
  nu_d_ene_distr_data[i].resize(2);
  nu_d_ene_distr_data_integ[i].resize(2);

  nu_d_ene_out_int_data[i][0]     = int_vec[0];
  nu_d_ene_out_int_data[i][1]     = int_vec[0];
  nu_d_ene_out_data[i][0]         = x_vec;
  nu_d_ene_out_data[i][1]         = x_vec;
  nu_d_ene_distr_data[i][0]       = y_vec;
  nu_d_ene_distr_data[i][1]       = y_vec;
  nu_d_ene_distr_data_integ[i][0] = y_integ;
  nu_d_ene_distr_data_integ[i][1] = y_integ;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::modify_delayed_neutron_data(int i, vector<Real>& x_vec, vector<Real>& y_vec)
{
  Real ex     = 40.0;
  int  j_max  = static_cast<int>(x_vec.size());
  if( j_max <= 1 )
  {
    return;
  }
  else if( x_vec[1] <= ex )
  {
    return;
  }

  string func_name = "modify_delayed_neutron_data";

  ostringstream oss01, oss02;
  oss01 << i+1;
  oss02 << x_vec[1];
  string str_data01 = "Position                           : " + oss01.str();
  string str_data02 = "Lowest delayed neutron energy grid : " + oss02.str();
  vector<string> err_com;
  err_com.push_back(str_data01);
  err_com.push_back(str_data02);
  err_com.push_back("The lowest delayed neutron energy grid is larger than 40.0 eV.");
  err_com.push_back("This delayed neutron energy grid may not be appropriate.");
  if( generate_mode_flg == generate_njoy_mode )
  {
    err_com.push_back("The lowest energy grid is interpolated using sqrt(E).");
  }
  err_obj.output_caution(class_name, func_name, err_com);


  if( generate_mode_flg == generate_default_mode )
  {
    return;
  }

  Real fx       = 0.8409;
  Real fx_coef1 = sqrt(fx);
  Real fx_coef2 = (1.0 - fx*fx_coef1) / (1.0 - fx);

  vector<Real> x_vec_add, y_vec_add;
  x_vec_add.push_back(x_vec[1]);
  y_vec_add.push_back(y_vec[1]);

  int ele_no = 0;
  while( x_vec_add[ele_no] > ex )
  {
    x_vec_add.push_back(fx       * x_vec_add[ele_no]);
    y_vec_add.push_back(fx_coef2 * y_vec[0]);

    y_vec[0] *= fx_coef1;

    ele_no++;
  }

  if( ele_no > 0 )
  {
    vector<Real> x_vec_new, y_vec_new;
    x_vec_new.push_back(x_vec[0]);
    y_vec_new.push_back(y_vec[0]);

    for(int j=ele_no; j>0; j--)
    {
      x_vec_new.push_back(x_vec_add[j]);
      y_vec_new.push_back(y_vec_add[j]);
    }
    x_vec_add.clear();
    y_vec_add.clear();

    for(int j=1; j<j_max; j++)
    {
      x_vec_new.push_back(x_vec[j]);
      y_vec_new.push_back(y_vec[j]);
    }
    x_vec = x_vec_new;
    y_vec = y_vec_new;
    x_vec_new.clear();
    y_vec_new.clear();
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_photon_production_xs()
{
  if( mf_12_data_no != 0 || mf_13_data_no != 0 || mf_6_data_no != 0 )
  {
    int i_max = static_cast<int>(reaction_type_list.size());
    int pos   = 0;
    for(int i=0; i<i_max; i++)
    {
      if( reaction_type_list[i] == 1 )
      {
        pos = i;
        break;
     }
    }

    if( photon_data_obj_vec[pos].get_reaction_type() != 1 )
    {
      return;
    }

    i_max = static_cast<int>(union_ene_grid.size());
    photon_product_xs.resize(i_max);
    vector<Integer> xs_tot_int_data   = photon_data_obj_vec[pos].get_photon_production_xs_tot_int_data();
    vector<Integer> xs_tot_range_data = photon_data_obj_vec[pos].get_photon_production_xs_tot_range_data();
    vector<Real>    xs_tot_ene_data   = photon_data_obj_vec[pos].get_photon_production_xs_tot_ene_data();
    vector<Real>    xs_tot_data       = photon_data_obj_vec[pos].get_photon_production_xs_tot_data();
    for(int i=0; i<i_max; i++)
    {
      ti_obj.interpolation_tab1(union_ene_grid[i], photon_product_xs[i],
                                xs_tot_range_data, xs_tot_int_data, xs_tot_ene_data, xs_tot_data);
    }

    //For gendf data file
    //Modify multigroup photon data in GENDF file.
    //The GENDF file is not available in FRENDY.
    /*if( mf_15_data_no != 0 )
    {
      if( static_cast<int>(photon_data_obj_vec[pos].get_ene_distr_law_no().size()) > 0 )
      {
        vector<Real> ene_in = photon_data_obj_vec[pos].get_incident_ene();
        int j_max = static_cast<int>(ene_in.size());
        if( j_max != 30 )
        {
          string func_name  = "set_photon_production_xs";
          ostringstream oss01, oss02;
          oss01 << reaction_type[pos];
          oss02 << j_max;
          string str_data01 = "Reaction type             : " + oss01.str();
          string str_data02 = "Number of incident energy : " + oss02.str();
          vector<string> err_com;
          err_com.push_back(str_data01);
          err_com.push_back(str_data02);
          err_com.push_back("Number of incident energy for ACE file must be 30.");
          err_com.push_back("Please check the neutron data library.");
          err_obj.output_runtime_error(class_name, func_name, err_com);
        }

        for(int j=0; j<j_max; j++)
        {
        }
      }
    }*/
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_detailed_photon_production_data()
{
  int i_max = static_cast<int>(photon_prod_type.size());
  for(int i=0; i<i_max; i++)
  {
    Integer file_no       = photon_prod_type[i]/1000;
    Integer reaction_type = photon_prod_type[i]%1000;

    int j_max = static_cast<int>(photon_data_obj_vec.size());
    int pos   = 0;
    for(int j=0; j<j_max; j++)
    {
      if( reaction_type == photon_data_obj_vec[j].get_reaction_type() )
      {
        pos = j;
        break;
      }
    }

    if( file_no == 12 )
    {
      //For Photon Production Multiplicities and Transition Probability Arrays
      set_detailed_photon_production_data_multiplicity(file_no, reaction_type, pos);
    }
  }

  for(int i=0; i<i_max; i++)
  {
    Integer file_no       = photon_prod_type[i]/1000;
    Integer reaction_type = photon_prod_type[i]%1000;

    int j_max = static_cast<int>(photon_data_obj_vec.size());
    int pos   = 0;
    for(int j=0; j<j_max; j++)
    {
      if( reaction_type == photon_data_obj_vec[j].get_reaction_type() )
      {
        pos = j;
        break;
      }
    }
    
    if( file_no != 12 )
    {
      //For Photon Production Cross Sections
      set_detailed_photon_production_data_xs(file_no, reaction_type, pos);
    }
  }

  //For Product Energy-Angle Distributions
  set_detailed_photon_production_data_ene_angle_distr();

  Integer react_type_cur = 0;
  Integer react_type_old = 0;
  i_max = static_cast<int>(photon_prod_reaction_type_all.size());
  for(int i=0; i<i_max; i++)
  {
    react_type_cur = photon_prod_reaction_type_all[i] / 1000;
    if( photon_prod_file_no[i] != 13 && react_type_old != react_type_cur )
    {
      photon_prod_reaction_type_without_xs.push_back(react_type_cur);
      react_type_old = react_type_cur;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_detailed_photon_production_data_multiplicity
                             (Integer file_no, Integer reaction_type, int pos)
{
  vector<Integer>          reaction_type_vec;
  vector<Real>             binding_ene_vec = photon_data_obj_vec[pos].get_multiplicity_binding_ene();
  vector<vector<Integer> > int_vec   = photon_data_obj_vec[pos].get_multiplicity_int_data();
  vector<vector<Integer> > range_vec = photon_data_obj_vec[pos].get_multiplicity_range_data();
  vector<vector<Real> >    ene_vec   = photon_data_obj_vec[pos].get_multiplicity_ene_data();
  vector<vector<Real> >    tab_vec   = photon_data_obj_vec[pos].get_multiplicity_data();

  Integer reaction_type_all = reaction_type*1000;
  int     j_max             = static_cast<int>(ene_vec.size());
  reaction_type_vec.resize(j_max);
  for(int j=0; j<j_max; j++)
  {
    int k_max = static_cast<int>(ene_vec[j].size());
    for(int k=0; k<k_max; k++)
    {
      ene_vec[j][k] *= unit_micro;
    }

    if( photon_data_obj_vec[pos].get_multiplicity_distr_law_no()[j] != 1 )
    {
      Integer photon_ene_flg = photon_data_obj_vec[pos].get_multiplicity_binding_ene_flg()[j];
      set_photon_enegy_distr_by_discrete_ene
        (ene_vec[j][0], ene_vec[j][k_max-1], photon_ene_flg, binding_ene_vec[j]);
    }
    else
    {
      set_photon_enegy_distr_by_continuous_photon_ene_spectra(pos, j);
    }
    reaction_type_all++;
    reaction_type_vec[j] = reaction_type_all;
  }

  j_max = static_cast<int>(reaction_type_vec.size());
  for(int j=0; j<j_max; j++)
  {
    photon_prod_file_no.push_back(file_no);
    photon_prod_reaction_type.push_back(reaction_type);
    photon_prod_reaction_type_all.push_back(reaction_type_vec[j]);
    photon_prod_binding_ene.push_back(binding_ene_vec[j] * unit_micro);
    photon_prod_multiplicity_int_data.push_back(int_vec[j]);
    photon_prod_multiplicity_range_data.push_back(range_vec[j]);
    photon_prod_multiplicity_ene_data.push_back(ene_vec[j]);
    photon_prod_multiplicity_data.push_back(tab_vec[j]);

    //Set dummy void data
    vector<Integer> int_vec_voi;
    vector<Real>    real_vec_voi;
    int_vec_voi.clear();
    real_vec_voi.clear();
    photon_prod_xs_ene_no.push_back(0);
    photon_prod_xs_non_zero_pos.push_back(int_vec_voi);
    photon_prod_xs_data.push_back(real_vec_voi);
    photon_prod_distr_int_data.push_back(int_vec_voi);
    photon_prod_distr_range_data.push_back(int_vec_voi);
    photon_prod_distr_ene_data.push_back(real_vec_voi);
    photon_prod_distr_data.push_back(real_vec_voi);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_detailed_photon_production_data_xs
                             (Integer file_no, Integer reaction_type, int pos)
{
  vector<Integer>          reaction_type_vec;
  vector<Real>             binding_ene_vec = photon_data_obj_vec[pos].get_binding_ene();
  vector<int>              ene_no_vec;
  vector<vector<int> >     non_zero_pos_vec;
  vector<vector<Real> >    xs_vec_new;
  vector<vector<Integer> > int_vec   = photon_data_obj_vec[pos].get_photon_production_xs_int_data();
  vector<vector<Integer> > range_vec = photon_data_obj_vec[pos].get_photon_production_xs_range_data();
  vector<vector<Real> >    ene_vec   = photon_data_obj_vec[pos].get_photon_production_xs_ene_data();
  vector<vector<Real> >    xs_vec    = photon_data_obj_vec[pos].get_photon_production_xs_data();

  int     tot_ene_no        = static_cast<int>(union_ene_grid.size());
  int     j_max             = static_cast<int>(ene_vec.size());
  Integer reaction_type_all = reaction_type*1000;
  reaction_type_vec.resize(j_max);
  ene_no_vec.resize(j_max);
  non_zero_pos_vec.resize(j_max);
  xs_vec_new.resize(j_max);
  for(int j=0; j<j_max; j++)
  {
    ene_no_vec[j] = 0;
    non_zero_pos_vec[j].resize(2);
    non_zero_pos_vec[j][0] = 0; //first point at non zero xs data
    non_zero_pos_vec[j][1] = 0; //number of non zero xs data

    for(int k=0; k<tot_ene_no; k++)
    {
      if( fabs(ene_vec[j][0] - union_ene_grid[k]) < union_ene_grid[k]*min_ene_dif )
      {
        ene_no_vec[j] = k+1;
        break;
      }
    }

    int  zero_xs_flg    = 0;
    Real xs_val         = 0.0;
    Real photon_ene_min = 0.0;
    Real photon_ene_max = 0.0;
    for(int k=ene_no_vec[j]-1; k<tot_ene_no; k++)
    {
      Real ene_val = union_ene_grid[k];
      ti_obj.interpolation_tab1(ene_val, xs_val, range_vec[j], int_vec[j], ene_vec[j], xs_vec[j]);

      if( non_zero_pos_vec[j][1] == 0 )
      {
        if( xs_val < fabs(min_value) )
        {
          photon_ene_min = ene_val;
          non_zero_pos_vec[j][0] = k+1;
        }
        else if( k == ene_no_vec[j]-1 )
        {
          non_zero_pos_vec[j][0] = k+1; //ene_no_vec[j]
        }
      }

      if( xs_val >= min_value )
      {
        photon_ene_max = ene_val;
        non_zero_pos_vec[j][1]++;
        if( non_zero_pos_vec[j][1] == 1 && k != ene_no_vec[j]-1 )
        {
          non_zero_pos_vec[j][1]++;
          xs_vec_new[j].push_back(0.0);
        }
        xs_vec_new[j].push_back(xs_val);
      }
      else if( non_zero_pos_vec[j][1] > 0 )
      {
        zero_xs_flg++;
      }
    }

    if( zero_xs_flg > 0 )
    {
      non_zero_pos_vec[j][1]++;
      xs_vec_new[j].push_back(0.0);
    }

    if( photon_data_obj_vec[pos].get_distr_law_no()[j] != 1 )
    {
      Integer photon_ene_flg = photon_data_obj_vec[pos].get_binding_ene_flg()[j];
      Real    binding_ene    = photon_data_obj_vec[pos].get_binding_ene()[j];
      set_photon_enegy_distr_by_discrete_ene(photon_ene_min, photon_ene_max, photon_ene_flg, binding_ene);
    }
    else
    {
      set_photon_enegy_distr_by_continuous_photon_ene_spectra(pos, j);
    }

    reaction_type_all++;
    reaction_type_vec[j] = reaction_type_all;
  }

  j_max = static_cast<int>(reaction_type_vec.size());
  for(int j=0; j<j_max; j++)
  {
    photon_prod_file_no.push_back(file_no);
    photon_prod_reaction_type.push_back(reaction_type);
    photon_prod_reaction_type_all.push_back(reaction_type_vec[j]);
    photon_prod_binding_ene.push_back(binding_ene_vec[j] * unit_micro);
    photon_prod_xs_ene_no.push_back(ene_no_vec[j]);
    photon_prod_xs_non_zero_pos.push_back(non_zero_pos_vec[j]);
    photon_prod_xs_data.push_back(xs_vec_new[j]);

    //Set dummy void data
    vector<Integer> int_vec_voi;
    vector<Real>    real_vec_voi;
    int_vec_voi.clear();
    real_vec_voi.clear();
    photon_prod_multiplicity_int_data.push_back(int_vec_voi);
    photon_prod_multiplicity_range_data.push_back(int_vec_voi);
    photon_prod_multiplicity_ene_data.push_back(real_vec_voi);
    photon_prod_multiplicity_data.push_back(real_vec_voi);
    photon_prod_distr_int_data.push_back(int_vec_voi);
    photon_prod_distr_range_data.push_back(int_vec_voi);
    photon_prod_distr_ene_data.push_back(real_vec_voi);
    photon_prod_distr_data.push_back(real_vec_voi);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_detailed_photon_production_data_ene_angle_distr()
{
  //For Product Energy-Angle Distributions
  int i_max = static_cast<int>(prod_distr_data_obj_mod_photon_vec.size());
  for(int i=0; i<i_max; i++)
  {
    Integer file_no       = 16;
    Integer reaction_type = prod_distr_data_obj_mod_photon_vec[i].get_reaction_type();

    vector<Integer>          reaction_type_vec;
    vector<vector<Integer> > int_vec   = prod_distr_data_obj_mod_photon_vec[i].get_product_distr_int_data();
    vector<vector<Integer> > range_vec = prod_distr_data_obj_mod_photon_vec[i].get_product_distr_range_data();
    vector<vector<Real> >    ene_vec   = prod_distr_data_obj_mod_photon_vec[i].get_product_distr_ene_data();
    vector<vector<Real> >    tab_vec   = prod_distr_data_obj_mod_photon_vec[i].get_product_distr_data();

    Integer reaction_type_all = reaction_type*1000;
    int     j_max             = static_cast<int>(ene_vec.size());
    for(int j=0; j<j_max; j++)
    {
      int k_max = static_cast<int>(ene_vec[j].size());
      for(int k=0; k<k_max; k++)
      {
        ene_vec[j][k] *= unit_micro;
      }

      reaction_type_all++;

      photon_prod_file_no.push_back(file_no);
      photon_prod_reaction_type.push_back(reaction_type);
      photon_prod_distr_int_data.push_back(int_vec[j]);
      photon_prod_distr_range_data.push_back(range_vec[j]);
      photon_prod_distr_ene_data.push_back(ene_vec[j]);
      photon_prod_distr_data.push_back(tab_vec[j]);
      photon_prod_reaction_type_all.push_back(reaction_type_all);

      //Set dummy void data
      vector<Integer> int_vec_voi;
      vector<Real>    real_vec_voi;
      int_vec_voi.clear();
      real_vec_voi.clear();
      photon_prod_binding_ene.push_back(0.0);
      photon_prod_multiplicity_int_data.push_back(int_vec_voi);
      photon_prod_multiplicity_range_data.push_back(int_vec_voi);
      photon_prod_multiplicity_ene_data.push_back(real_vec_voi);
      photon_prod_multiplicity_data.push_back(real_vec_voi);
      photon_prod_xs_ene_no.push_back(0);
      photon_prod_xs_non_zero_pos.push_back(int_vec_voi);
      photon_prod_xs_data.push_back(real_vec_voi);
    }

    set_photon_enegy_distr_by_ene_angle_distr(i);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_photon_enegy_distr_by_discrete_ene
                             (Real photon_ene_min, Real photon_ene_max, Integer photon_ene_flg, Real binding_ene)
{
  Integer ene_distr_flg = 2;
  photon_energy_distr_flg.push_back(ene_distr_flg);

  binding_ene *= unit_micro;
  photon_energy_distr_ene_flg.push_back(photon_ene_flg);
  photon_energy_distr_binding_ene_data.push_back(binding_ene);

  vector<Integer> int_vec, range_vec;
  vector<Real>    ene_vec, prob_vec;
  int_vec.resize(1);
  range_vec.resize(1);
  ene_vec.resize(2);
  prob_vec.resize(2);

  int_vec[0]   = int_lin_lin;
  range_vec[0] = 2;
  ene_vec[0]   = photon_ene_min;
  ene_vec[1]   = photon_ene_max;
  prob_vec[0]  = 1.0;
  prob_vec[1]  = 1.0;

  photon_energy_distr_int_data.push_back(int_vec);
  photon_energy_distr_range_data.push_back(range_vec);
  photon_energy_distr_ene_data.push_back(ene_vec);
  photon_energy_distr_prob_data.push_back(prob_vec);

  //Set dummy void data
  vector<vector<Real> > real_vec2;
  clr_obj.clear_vec_array2_real(real_vec2); 
  int_vec.clear();
  ene_vec.clear();
  photon_energy_distr_ene_in_int_data.push_back(int_vec);
  photon_energy_distr_ene_in_range_data.push_back(int_vec);
  photon_energy_distr_ene_in_data.push_back(ene_vec);
  photon_energy_distr_weight_int_data.push_back(int_vec);
  photon_energy_distr_weight_ene_data.push_back(real_vec2);
  photon_energy_distr_weight_data.push_back(real_vec2);
  photon_energy_distr_weight_data_integ.push_back(real_vec2);
  photon_energy_distr_gamma_mass_product.push_back(0.0);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_photon_enegy_distr_by_continuous_photon_ene_spectra(int pos, int j)
{
  PhotonDataContainer photon_obj = photon_data_obj_vec[pos];

  Integer ene_distr_flg = 4;
  photon_energy_distr_flg.push_back(ene_distr_flg);

  int j_max = static_cast<int>(photon_obj.get_ene_distr_weight_int_data().size());
  if( j >= j_max )
  {
    j = 0;
  }

  vector<Integer> int_vec   = photon_obj.get_ene_distr_weight_int_data()[j];
  vector<Integer> range_vec = photon_obj.get_ene_distr_weight_range_data()[j];
  vector<Real>    x_vec     = photon_obj.get_ene_distr_weight_ene_data()[j];
  vector<Real>    y_vec     = photon_obj.get_ene_distr_weight_data()[j];

  int k_max = static_cast<int>(x_vec.size());
  for(int k=0; k<k_max; k++)
  {
    x_vec[k] *= unit_micro;
  }
  photon_energy_distr_int_data.push_back(int_vec);
  photon_energy_distr_range_data.push_back(range_vec);
  photon_energy_distr_ene_data.push_back(x_vec);
  photon_energy_distr_prob_data.push_back(y_vec);

  int_vec   = photon_obj.get_ene_distr_int_data()[j];
  range_vec = photon_obj.get_ene_distr_range_data()[j];
  photon_energy_distr_ene_in_int_data.push_back(int_vec);
  photon_energy_distr_ene_in_range_data.push_back(range_vec);

  string func_name  = "set_photon_enegy_distr_by_continuous_photon_ene_spectra";
  vector<Real>          ene_in_vec    = photon_obj.get_incident_ene()[j];
  vector<vector<Real> > ene_out_x_vec = photon_obj.get_ene_distr_nomalized_ene_data()[j];
  vector<vector<Real> > ene_out_y_vec = photon_obj.get_ene_distr_nomalized_data()[j];
  vector<vector<Real> > ene_out_integ_vec;
  vector<Integer>       ene_out_int_vec;

  vector<int> pos_data;
  pos_data.resize(2);
  pos_data[0] = j;
  Integer reaction_type = photon_obj.get_reaction_type();
          k_max         = static_cast<int>(ene_in_vec.size());
  ene_out_integ_vec.resize(k_max);
  ene_out_int_vec.resize(k_max);
  for(int k=0; k<k_max; k++)
  {
    ene_in_vec[k] *= unit_micro;

    pos_data[1] = k;
    int_vec     = photon_obj.get_ene_distr_nomalized_int_data()[j][k];
    range_vec   = photon_obj.get_ene_distr_nomalized_range_data()[j][k];
    ene_out_int_vec[k] = integ_obj.check_interpolation(class_name, func_name, reaction_type, pos_data,
                                                       range_vec, int_vec);

    Real sum = 0.0;
    integ_obj.integrate_for_ace_data(class_name, func_name, ene_out_x_vec[k], ene_out_y_vec[k],
                                     ene_out_integ_vec[k], ene_out_int_vec[k], sum);
    int l_max = static_cast<int>(ene_out_integ_vec[k].size());
    for(int l=0; l<l_max; l++)
    {
      ene_out_x_vec[k][l] *= unit_micro;
      ene_out_y_vec[k][l] *= unit_mega;
    }
  }
  int_vec.clear();
  range_vec.clear();
  x_vec.clear();
  y_vec.clear();

  photon_energy_distr_ene_in_data.push_back(ene_in_vec);
  ene_in_vec.clear();

  photon_energy_distr_weight_int_data.push_back(ene_out_int_vec);
  ene_out_int_vec.clear();

  photon_energy_distr_weight_ene_data.push_back(ene_out_x_vec);
  photon_energy_distr_weight_data.push_back(ene_out_y_vec);
  photon_energy_distr_weight_data_integ.push_back(ene_out_integ_vec);
  clr_obj.clear_vec_array2_real(ene_out_x_vec);
  clr_obj.clear_vec_array2_real(ene_out_y_vec);
  clr_obj.clear_vec_array2_real(ene_out_integ_vec);

  //Set dummy void data
  photon_energy_distr_ene_flg.push_back(0);
  photon_energy_distr_binding_ene_data.push_back(0.0);
  photon_energy_distr_gamma_mass_product.push_back(0.0);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_photon_enegy_distr_by_ene_angle_distr(int pos)
{
  set_photon_enegy_distr_by_ene_angle_distr_common_ace_data(pos);

  vector<Real> gam_prob_ene_data;
  set_photon_enegy_distr_by_ene_angle_distr_common_data(pos, gam_prob_ene_data);

  vector<vector<Real> > gam_prob_ene_data_tot, gam_prob_data_tot;
  set_photon_enegy_distr_by_ene_angle_distr_prob_data(pos, gam_prob_ene_data,
                                                      gam_prob_ene_data_tot,  gam_prob_data_tot);

  set_photon_enegy_distr_by_ene_angle_distr_weight_data(pos, gam_prob_ene_data,
                                                        gam_prob_ene_data_tot, gam_prob_data_tot);

  //Set dummy void data
  photon_energy_distr_ene_flg.push_back(0);
  photon_energy_distr_binding_ene_data.push_back(0.0);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_photon_enegy_distr_by_ene_angle_distr_common_ace_data(int pos)
{
  Integer ene_distr_flg = 4;
  photon_energy_distr_flg.push_back(ene_distr_flg);
  vector<Integer> int_vec, range_vec;
  vector<Real>    ene_vec, prob_vec;
  vector<Real> product_distr_ene_data
                 = prod_distr_data_obj_mod_photon_vec[pos].get_product_distr_ene_data()[0];
  int i_max = static_cast<int>(product_distr_ene_data.size());

  int_vec.resize(1);
  range_vec.resize(1);
  ene_vec.resize(2);
  prob_vec.resize(2);
  int_vec[0]   = int_lin_lin;
  range_vec[0] = 2;
  ene_vec[0]   = product_distr_ene_data[0]       * unit_micro;
  ene_vec[1]   = product_distr_ene_data[i_max-1] * unit_micro;
  prob_vec[0]  = 1.0;
  prob_vec[1]  = 1.0;
  photon_energy_distr_int_data.push_back(int_vec);
  photon_energy_distr_range_data.push_back(range_vec);
  photon_energy_distr_ene_data.push_back(ene_vec);
  photon_energy_distr_prob_data.push_back(prob_vec);
  int_vec.clear();
  range_vec.clear();
  ene_vec.clear();
  prob_vec.clear();

  Integer distr_func_flg = prod_distr_data_obj_mod_photon_vec[pos].get_distr_func_flg()[0];
  Real    gam_val        = 0.0;
  if( distr_func_flg == 1 )
  {
    int_vec   = prod_distr_data_obj_mod_photon_vec[pos].get_cont_int_data()[0];
    range_vec = prod_distr_data_obj_mod_photon_vec[pos].get_cont_range_data()[0];
    ene_vec   = prod_distr_data_obj_mod_photon_vec[pos].get_cont_ene_a()[0];
  }
  else if( distr_func_flg == 2 )
  {
    gam_val   = prod_distr_data_obj_mod_photon_vec[pos].get_mass_product()[0];
    int_vec   = prod_distr_data_obj_mod_photon_vec[pos].get_two_body_int_data()[0];
    range_vec = prod_distr_data_obj_mod_photon_vec[pos].get_two_body_range_data()[0];
    ene_vec   = prod_distr_data_obj_mod_photon_vec[pos].get_two_body_ene_data()[0];
  }
  photon_energy_distr_gamma_mass_product.push_back(gam_val);
  photon_energy_distr_ene_in_int_data.push_back(int_vec);
  photon_energy_distr_ene_in_range_data.push_back(range_vec);
  int_vec.clear();
  range_vec.clear();

  i_max = static_cast<int>(ene_vec.size());
  for(int i=0; i<i_max; i++)
  {
    ene_vec[i] *= unit_micro;
  }
  photon_energy_distr_ene_in_data.push_back(ene_vec);
  ene_vec.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_photon_enegy_distr_by_ene_angle_distr_common_data
                             (int pos, vector<Real>& gam_prob_ene_data)
{
  Integer distr_func_flg = prod_distr_data_obj_mod_photon_vec[pos].get_distr_func_flg()[0];
  vector<Integer>       ene_data_flg;
  vector<Real>          ene_vec;
  vector<vector<Real> > prob_ene_vec;

  if( distr_func_flg == 1 )
  {
    ene_vec      = prod_distr_data_obj_mod_photon_vec[pos].get_cont_ene_a()[0];
    ene_data_flg = prod_distr_data_obj_mod_photon_vec[pos].get_discrete_ene_no()[0];
    prob_ene_vec = prod_distr_data_obj_mod_photon_vec[pos].get_cont_ene_b()[0];

    //Check cont data
    vector<vector<vector<Real> > > cont_data = prod_distr_data_obj_mod_photon_vec[pos].get_cont_data()[0];
    int i_max = static_cast<int>(cont_data.size());
    for(int i=0; i<i_max; i++)
    {
      int j_max = static_cast<int>(cont_data[i].size());
      for(int j=0; j<j_max; j++)
      {
        if( static_cast<int>(cont_data[i][j].size()) > 1 )
        {
          string func_name  = "set_photon_enegy_distr_by_ene_angle_distr_common_data";
          ostringstream oss01, oss02, oss03, oss04, oss05, oss06;
          oss01 << prod_distr_data_obj_mod_photon_vec[pos].get_reaction_type();
          oss02 << i+1;
          oss03 << i_max;
          oss04 << j+1;
          oss05 << j_max;
          oss06 << static_cast<int>(cont_data[j].size());
          string str_data01 = "Reaction type : " + oss01.str();
          string str_data02 = "Position      : " + oss02.str() + " / " + oss03.str()
                                          + ", " + oss04.str() + " / " + oss05.str();
          string str_data03 = "Array number  : " + oss06.str();
          vector<string> err_com;
          err_com.push_back(str_data01);
          err_com.push_back(str_data02);
          err_com.push_back(str_data03);
          err_com.push_back("Array number must be 1.");
          err_com.push_back("Please check the program or the neutron data library.");
          err_obj.output_runtime_error(class_name, func_name, err_com);
        }
      }
    }

    set_photon_enegy_distr_by_ene_angle_distr_common_data
      (pos, distr_func_flg, ene_vec, ene_data_flg, prob_ene_vec, gam_prob_ene_data);
  }
  else if( distr_func_flg == 2 )
  {
    ene_vec       = prod_distr_data_obj_mod_photon_vec[pos].get_two_body_ene_data()[0];
    ene_data_flg  = prod_distr_data_obj_mod_photon_vec[pos].get_two_body_repr_flg()[0];
    prob_ene_vec  = prod_distr_data_obj_mod_photon_vec[pos].get_two_body_cos()[0];

    set_photon_enegy_distr_by_ene_angle_distr_common_data
      (pos, distr_func_flg, ene_vec, ene_data_flg, prob_ene_vec, gam_prob_ene_data);
  }
  else
  {
    string func_name  = "set_photon_enegy_distr_by_ene_angle_distr_common_data";
    ostringstream oss01, oss02, oss03, oss04, oss05, oss06;
    oss01 << prod_distr_data_obj_mod_photon_vec[pos].get_reaction_type();
    oss02 << distr_func_flg;
    string str_data01 = "Reaction type              : " + oss01.str();
    string str_data02 = "Distribution function flag : " + oss02.str();
    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("Distribution function flag is only available");
    err_com.push_back("for continuum energy-angle distribution (1)");
    err_com.push_back("and two-body reaction angular distribution (2).");
    err_com.push_back("Please check the program or the neutron data library.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_photon_enegy_distr_by_ene_angle_distr_common_data
                             (int pos, Integer distr_func_flg,
                              vector<Real>&          ene_vec,      vector<Integer>& ene_data_flg,
                              vector<vector<Real> >& prob_ene_vec, vector<Real>&    gam_prob_ene_data)
{
  Real mass      = nucl_data_obj.get_general_data_obj().get_mass();
  Real mass_coef = mass/(mass + 1.0);
  gam_prob_ene_data.clear();

  int i_max = static_cast<int>(ene_vec.size());
  for(int i=0; i<i_max; i++)
  {
    if( ene_data_flg[i] <= 0 )
    {
      continue;
    }

    Real ene_coef = ene_vec[i]*mass_coef;
    int  j_max    = static_cast<int>(ene_data_flg[i]);
    for(int j=0; j<j_max; j++)
    {
      Real ene_val  = prob_ene_vec[i][j];
      if( fabs(ene_val) < min_value )
      {
        string func_name  = "set_photon_enegy_distr_by_ene_angle_distr_common_data";
        ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07;
        oss01 << prod_distr_data_obj_mod_photon_vec[pos].get_reaction_type();
        oss02 << i+1;
        oss03 << i_max;
        oss04 << j+1;
        oss05 << j_max;
        oss06 << ene_val;
        oss07 << union_ene_grid[0];
        string str_data01 = "Reaction type        : " + oss01.str();
        string str_data02 = "Position             : " + oss02.str() + " / " + oss03.str() + ", "
                                                      + oss04.str() + " / " + oss05.str();
        string str_data03 = "photon energy        : " + oss06.str();
        string str_data04 = "Minimum energy value : " + oss07.str();
        vector<string> err_com;
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back("Discrete photon energy must be not equal to 0.0 eV.");
        err_com.push_back("The photon energy is reset to the minimum energy value.");
        err_obj.output_caution(class_name, func_name, err_com);

        ene_val = union_ene_grid[0];
      }

      if( distr_func_flg == 2 )
      {
        ene_val -= ene_coef;
      }

      if( j > 0 )
      {
        if( fabs(ene_val - prob_ene_vec[i][j-1]) < min_value )
        {
          ene_val *= 1.00002;
        }
      }

      if( static_cast<int>(gam_prob_ene_data.size()) == 0 )
      {
        gam_prob_ene_data.push_back(ene_val);
      }
      else
      {
        int add_flg = 1;
        int k_max   = static_cast<int>(gam_prob_ene_data.size());
        for(int k=0; k<k_max; k++)
        {
          if( fabs(ene_val - gam_prob_ene_data[k]) < fabs(min_ene_dif*gam_prob_ene_data[k]) )
          {
            add_flg = 0;
            break;
          }
        }

        if( add_flg != 0 )
        {
          ta_obj.add_grid_data(gam_prob_ene_data, ene_val);
        }
      }
    }
  }

  i_max = static_cast<int>(gam_prob_ene_data.size());
  vector<Real> gam_prob_ene_data_m, gam_prob_ene_data_p;
  for(int i=0; i<i_max; i++)
  {
    if( gam_prob_ene_data[i] >= 0.0 )
    {
      gam_prob_ene_data_p.push_back(gam_prob_ene_data[i]);
    }
    else
    {
      gam_prob_ene_data_m.push_back(gam_prob_ene_data[i]);
    }
  }

  //Sorting gam_prob_ene_data in descending order of the absolute value
  int m_max = static_cast<int>(gam_prob_ene_data_m.size());
  sort(gam_prob_ene_data_m.begin(), gam_prob_ene_data_m.end());

  int p_max = static_cast<int>(gam_prob_ene_data_p.size());
  sort(gam_prob_ene_data_p.begin(), gam_prob_ene_data_p.end(), std::greater<Real>());

  if( p_max > 0 && m_max > 0 )
  {
    string func_name  = "set_photon_enegy_distr_by_ene_angle_distr_common_data";
    ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07;
    oss01 << prod_distr_data_obj_mod_photon_vec[pos].get_reaction_type();
    oss02 << m_max;
    oss03 << p_max;
    string str_data01 = "Reaction type                  : " + oss01.str();
    string str_data02 = "  m_max                        : " + oss02.str();
    string str_data03 = "  p_max                        : " + oss03.str();

    oss04.precision(8);
    oss05.precision(8);
    oss06.precision(8);
    oss07.precision(8);
    oss04.setf(ios::showpoint);
    oss05.setf(ios::showpoint);
    oss06.setf(ios::showpoint);
    oss07.setf(ios::showpoint);
    oss04.setf(ios::scientific);
    oss05.setf(ios::scientific);
    oss06.setf(ios::scientific);
    oss07.setf(ios::scientific);

    oss04 << gam_prob_ene_data_m[0];
    oss05 << gam_prob_ene_data_m[m_max-1];
    oss06 << gam_prob_ene_data_p[0];
    oss07 << gam_prob_ene_data_p[p_max-1];

    string str_data04 = "  gam_prob_ene_data_m[0]       : " + oss04.str();
    string str_data05 = "  gam_prob_ene_data_m[m_max-1] : " + oss05.str();
    string str_data06 = "  gam_prob_ene_data_p[0]       : " + oss06.str();
    string str_data07 = "  gam_prob_ene_data_p[p_max-1] : " + oss07.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back(str_data05);
    err_com.push_back(str_data06);
    err_com.push_back(str_data07);

    int ele_no      = 0;
    int err_flg_gam = 0;
    if( fabs(gam_prob_ene_data_m[m_max-1]) > gam_prob_ene_data_p[0] )
    {
      for(int i=0; i<m_max; i++)
      {
        gam_prob_ene_data[ele_no] = gam_prob_ene_data_m[i];
        ele_no++;
      }

      for(int i=0; i<p_max; i++)
      {
        gam_prob_ene_data[ele_no] = gam_prob_ene_data_p[i];
        ele_no++;
      }
    }
    else if( fabs(gam_prob_ene_data_m[0]) < gam_prob_ene_data_p[p_max-1] )
    {
      for(int i=0; i<p_max; i++)
      {
        gam_prob_ene_data[ele_no] = gam_prob_ene_data_p[i];
        ele_no++;
      }

      for(int i=0; i<m_max; i++)
      {
        gam_prob_ene_data[ele_no] = gam_prob_ene_data_m[i];
        ele_no++;
      }
    }
    //else if( fabs(gam_prob_ene_data_m[0])       < gam_prob_ene_data_p[0] &&
    //         fabs(gam_prob_ene_data_m[m_max-1]) < gam_prob_ene_data_p[p_max-1] &&
    //{
    //}
    //else if( fabs(gam_prob_ene_data_m[0])       > gam_prob_ene_data_p[0] &&
    //         fabs(gam_prob_ene_data_m[m_max-1]) > gam_prob_ene_data_p[p_max-1] &&
    //{
    //}
    else
    {
      err_flg_gam = 1;
      err_com.push_back("The energy rang of gam_prob_ene_data_m and gam_prob_ene_data_p is duplicated.");
      err_com.push_back("The energy range of gamp_prob_ene_data_m or gam_prob_ene_data_p may be incorrect.");
      err_com.push_back("Please check the ENDF file or modify this program.");
      err_obj.output_caution(class_name, func_name, err_com);
    }

    if( err_flg_gam == 0 )
    {
      err_com.push_back("The gam_prob_ene_data has both");
      err_com.push_back("minus (primary gamma) and plus (other gamma) value.");
      err_com.push_back("This program may not appropriately treat such kind of data.");
      err_com.push_back("Please check the ACE file whether the processing results are appropriate or not.");
      //err_obj.output_caution(class_name, func_name, err_com);
    }
  }
  else if( p_max == 0 )
  {
    gam_prob_ene_data = gam_prob_ene_data_m;
  }
  else if( m_max == 0 )
  {
    gam_prob_ene_data = gam_prob_ene_data_p;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_photon_enegy_distr_by_ene_angle_distr_prob_data
                             (int pos, vector<Real>& gam_prob_ene_data,
                              vector<vector<Real> >& gam_prob_ene_data_tot,
                              vector<vector<Real> >& gam_prob_data_tot)
{
  Integer distr_func_flg = prod_distr_data_obj_mod_photon_vec[pos].get_distr_func_flg()[0];
  Real    mass           = nucl_data_obj.get_general_data_obj().get_mass();
  Real    mass_coef      = mass/(mass + 1.0);

  vector<Real>    ene_in_vec;
  vector<Integer> ene_data_flg;
  vector<vector<Real> > ene_vec;
  if( distr_func_flg == 1 )
  {
    ene_in_vec   = prod_distr_data_obj_mod_photon_vec[pos].get_cont_ene_a()[0];
    ene_vec      = prod_distr_data_obj_mod_photon_vec[pos].get_cont_ene_b()[0];
    ene_data_flg = prod_distr_data_obj_mod_photon_vec[pos].get_discrete_ene_no()[0];
  }
  else
  {
    ene_in_vec   = prod_distr_data_obj_mod_photon_vec[pos].get_two_body_ene_data()[0];
    ene_vec      = prod_distr_data_obj_mod_photon_vec[pos].get_two_body_cos()[0];
    ene_data_flg = prod_distr_data_obj_mod_photon_vec[pos].get_two_body_repr_flg()[0];
  }

  int i_max = static_cast<int>(ene_in_vec.size());
  gam_prob_ene_data_tot.resize(i_max);
  gam_prob_data_tot.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    int j_max            = static_cast<int>(gam_prob_ene_data.size());
    int ene_data_flg_int = static_cast<int>(ene_data_flg[i]);
    int ele_no           = static_cast<int>(ene_vec[i].size());

    vector<Real> prob_ene_vec, prob_ene_vec_ori, prob_data_vec, prob_data_vec_ori;
    prob_ene_vec_ori.resize(ele_no);
    prob_data_vec_ori.resize(ele_no);
    for(int j=0; j<ele_no; j++)
    {
      prob_ene_vec_ori[j]  = ene_vec[i][j];
      prob_data_vec_ori[j] = 0.0;

      if( j < ene_data_flg_int )
      {
        if( fabs(ene_vec[i][j]) < min_value )
        {
          ene_vec[i][j] = union_ene_grid[0];
        }

        prob_ene_vec_ori[j] = ene_vec[i][j];
        if( j > 0 )
        {
          if( fabs(prob_ene_vec_ori[j] - prob_ene_vec_ori[j-1]) < min_value )
          {
            prob_ene_vec_ori[j-1] *= 1.00002;
          }
        }
      }

      if( distr_func_flg == 1 )
      {
        prob_data_vec_ori[j] = prod_distr_data_obj_mod_photon_vec[pos].get_cont_data()[0][i][j][0];
      }
      else
      {
        prob_data_vec_ori[j] = prod_distr_data_obj_mod_photon_vec[pos].get_two_body_prob()[0][i][j];
      }
    }

    prob_ene_vec  = prob_ene_vec_ori;
    prob_data_vec = prob_data_vec_ori;
    if( j_max == 0 )
    {
      gam_prob_ene_data_tot[i] = prob_ene_vec;
      gam_prob_data_tot[i]     = prob_data_vec;
      continue;
    }

    if( ene_data_flg_int == j_max && j_max > 0 )
    {
      for(int j=0; j<j_max; j++)
      {
        if( distr_func_flg == 1 && prob_ene_vec[j] < min_value)
        {
          prob_ene_vec[j] = mass_coef*ene_in_vec[i] - prob_ene_vec[j];
        }
      }
    }
    else //if( ene_data_flg_int != j_max )
    {
      if( ene_data_flg_int == 0 )
      {
        prob_ene_vec.resize(j_max + ele_no);
        prob_data_vec.resize(j_max + ele_no);
        for(int j=0; j<j_max; j++)
        {
          prob_ene_vec[j]  = gam_prob_ene_data[j];
          prob_data_vec[j] = 0.0;
          if( distr_func_flg == 1 && prob_ene_vec[j] < min_value )
          {
            prob_ene_vec[j] = mass_coef*ene_in_vec[i] - prob_ene_vec[j];
          }
          else if( distr_func_flg == 2 )
          {
            prob_ene_vec[j] += mass_coef*ene_in_vec[i];
          }
        }

        for(int j=j_max; j<j_max + ele_no; j++)
        {
          prob_ene_vec[j]  = prob_ene_vec_ori[j-j_max];
          prob_data_vec[j] = prob_data_vec_ori[j-j_max];
        }
      }
      else
      {
        prob_ene_vec.resize(j_max  + ele_no - ene_data_flg_int);
        prob_data_vec.resize(j_max + ele_no - ene_data_flg_int);
        for(int j=0; j<j_max; j++)
        {
          prob_ene_vec[j]  = gam_prob_ene_data[j];
          prob_data_vec[j] = 0.0;
          if( distr_func_flg == 1 && prob_ene_vec[j] < min_value )
          {
            prob_ene_vec[j] = mass_coef*ene_in_vec[i] - prob_ene_vec[j];
          }
          else if( distr_func_flg == 2 )
          {
            prob_ene_vec[j] += mass_coef*ene_in_vec[i];
          }

          for(int k=0; k<ene_data_flg_int; k++)
          {
            if( fabs(prob_ene_vec_ori[k] - gam_prob_ene_data[j]) < fabs(min_ene_dif*gam_prob_ene_data[j]) )
            {
              prob_data_vec[j] = prob_data_vec_ori[k];
              break;
            }
          }
        }

        for(int j=j_max; j<j_max + ele_no - ene_data_flg_int; j++)
        {
          prob_ene_vec[j]  = prob_ene_vec_ori[j-j_max+ene_data_flg_int];
          prob_data_vec[j] = prob_data_vec_ori[j-j_max+ene_data_flg_int];
        }
      }
    }

    gam_prob_ene_data_tot[i] = prob_ene_vec;
    gam_prob_data_tot[i]     = prob_data_vec;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_photon_enegy_distr_by_ene_angle_distr_weight_data
                 (int pos, vector<Real>& gam_prob_ene_data,
                  vector<vector<Real> >& gam_prob_ene_data_tot, vector<vector<Real> >& gam_prob_data_tot)
{
  Integer distr_func_flg = prod_distr_data_obj_mod_photon_vec[pos].get_distr_func_flg()[0];

  vector<Integer>       int_vec;
  vector<vector<Real> > weight_ene_data, weight_data, weight_data_integ;
  weight_ene_data = gam_prob_ene_data_tot;
  weight_data     = gam_prob_data_tot;

  Integer int_val = 0;
  if( distr_func_flg == 1 )
  {
    int_val = prod_distr_data_obj_mod_photon_vec[pos].get_second_ene_int_data()[0];
  }

  int i_max            = static_cast<int>(gam_prob_ene_data_tot.size());
  int ene_data_flg_int = static_cast<int>(gam_prob_ene_data.size());

  int_vec.resize(i_max);
  weight_data_integ.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    int_vec[i] = int_val + 10 * static_cast<Integer>(ene_data_flg_int);

    int j_max = static_cast<int>(weight_ene_data[i].size());
    if( j_max == 0 )
    {
      continue;
    }

    weight_data_integ[i].resize(j_max);
    weight_data_integ[i][0] = 0.0;
    for(int j=0; j<j_max; j++)
    {
      weight_ene_data[i][j] *= unit_micro;

      //Modify weight_data
      if( j >= ene_data_flg_int )
      {
        weight_data[i][j] *= unit_mega;
      }
      if( weight_data[i][j] < min_value )
      {
        weight_data[i][j] = 0.0;
      }

      if( ene_data_flg_int > 0 )
      {
        if( j == 0 )
        {
          weight_data_integ[i][j] = weight_data[i][j];
        }
        else if( j < ene_data_flg_int )
        {
          weight_data_integ[i][j] = weight_data_integ[i][j-1] + weight_data[i][j];
        }
        else if( j == ene_data_flg_int )
        {
          weight_data_integ[i][j] = weight_data_integ[i][j-1];
        }
      }

      if( j > ene_data_flg_int )
      {
        Real ene_dif = (weight_ene_data[i][j-1] - weight_ene_data[i][j]) * unit_mega;
        if( fabs(ene_dif) < min_ene_dif )
        {
          weight_data_integ[i][j] = weight_data_integ[i][j-1];
        }
        else
        {
          weight_data_integ[i][j] = weight_data_integ[i][j-1]
            + integ_obj.integrate_data(weight_ene_data[i][j-1], weight_data[i][j-1],
                                       weight_ene_data[i][j],   weight_data[i][j], int_val);
 
          if( int_val != int_const && int_val != int_lin_lin )
          {
            string func_name  = "set_photon_enegy_distr_by_ene_angle_distr_weight_data";
            ostringstream oss01, oss02, oss03;
            oss01 << prod_distr_data_obj_mod_photon_vec[pos].get_reaction_type();
            oss02 << distr_func_flg;
            oss03 << int_val;
            string str_data01 = "Reaction type              : " + oss01.str();
            string str_data02 = "Distribution function flag : " + oss02.str();
            string str_data03 = "Interpolation type         : " + oss03.str();
            vector<string> err_com;
            err_com.push_back(str_data01);
            err_com.push_back(str_data02);
            err_com.push_back(str_data03);
            err_com.push_back("This interpolation type is not available.");
            err_com.push_back("Available interpolation type is constant and linear-linear.");
            err_obj.output_runtime_error(class_name, func_name, err_com);
          }
        }
      }
    }

    Real sum_inv = 1.0;
    if( fabs(weight_data_integ[i][j_max-1]) > min_value )
    {
      sum_inv /= weight_data_integ[i][j_max-1];
    }
    for(int j=0; j<j_max; j++)
    {
      weight_data[i][j]       *= sum_inv;
      weight_data_integ[i][j] *= sum_inv;
    }
  }

  photon_energy_distr_weight_int_data.push_back(int_vec);
  int_vec.clear();

  photon_energy_distr_weight_ene_data.push_back(weight_ene_data);
  photon_energy_distr_weight_data.push_back(weight_data);
  photon_energy_distr_weight_data_integ.push_back(weight_data_integ);
  clr_obj.clear_vec_array2_real(weight_ene_data);
  clr_obj.clear_vec_array2_real(weight_data);
  clr_obj.clear_vec_array2_real(weight_data_integ);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_photon_angular_distr()
{
  int i_max = static_cast<int>(photon_prod_file_no.size());
  photon_angular_distr_ene_data.resize(i_max);
  photon_angular_distr_prob_cos_data.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    photon_angular_distr_ene_data[i].clear();
    photon_angular_distr_prob_cos_data[i].clear();

    Integer reaction_type = photon_prod_reaction_type[i];

    int j_max = static_cast<int>(photon_data_obj_vec.size());
    int pos   = 0;
    for(int j=0; j<j_max; j++)
    {
      if( reaction_type == photon_data_obj_vec[j].get_reaction_type() )
      {
        pos = j;
        break;
      }
    }

    Integer isotropic_flg = photon_data_obj_vec[pos].get_isotropic_flg();
    if( isotropic_flg != 0 )
    {
      continue;
    }

    int iso_photon_angular_no = static_cast<int>(photon_data_obj_vec[pos].get_iso_photon_angular_no());

    vector<Real>                      angular_photon_ene;
    vector<vector<Real> >             angular_ene_data;
    vector<vector<vector<Real> > >    prob_cos_data;
    angular_photon_ene = photon_data_obj_vec[pos].get_angular_photon_ene();
    angular_ene_data   = photon_data_obj_vec[pos].get_angular_ene_data();
    prob_cos_data      = photon_data_obj_vec[pos].get_angular_probability_cos_data();

        j_max  = static_cast<int>(angular_ene_data.size());
    for(int j=iso_photon_angular_no; j<j_max; j++)
    {
      angular_photon_ene[j] *= unit_micro;
      if( fabs(angular_photon_ene[j] - photon_prod_binding_ene[i]) > photon_prod_binding_ene[i]*1.0E-7 )
      {
        continue;
      }

      int k_max = static_cast<int>(angular_ene_data[j].size());
      for(int k=0; k<k_max; k++)
      {
        angular_ene_data[j][k] *= unit_micro;

        int l_max = static_cast<int>(prob_cos_data[j][k].size());
        if( l_max == 2 )
        {
          prob_cos_data[j][k].resize(0);
        }
        else if( l_max != 33 && l_max != 2 )
        {
          string func_name  = "set_photon_angular_distr";
          ostringstream oss01, oss02, oss03, oss04, oss05, oss06;
          oss01 << reaction_type;
          oss02 << j+1;
          oss03 << j_max;
          oss04 << k+1;
          oss05 << k_max;
          oss06 << l_max;
          string str_data01 = "Reaction type                    : " + oss01.str();
          string str_data02 = "Position                         : " + oss02.str() + " / " + oss03.str()
                                                             + ", " + oss04.str() + " / " + oss05.str();
          string str_data03 = "Array number of probatility data : " + oss06.str();
          vector<string> err_com;
          err_com.push_back(str_data01);
          err_com.push_back(str_data02);
          err_com.push_back(str_data03);
          err_com.push_back("Array number of probability data is 2 or 33.");
          err_com.push_back("Please check the program or the neutron data library.");
          err_obj.output_runtime_error(class_name, func_name, err_com);
        }
      }

      photon_angular_distr_ene_data[i]      = angular_ene_data[j];
      photon_angular_distr_prob_cos_data[i] = prob_cos_data[j];
    }
    angular_photon_ene.clear();
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_particle_production()
{
  int prod_flg = set_particle_production_flg();
  if( prod_flg != 0 )
  {
    return;
  }

  set_particle_production_calc_data();

  if( sub_lib_part > 1 )
  {
    set_charged_particle_production();
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

int FastAceDataGenerator::set_particle_production_flg()
{
  if( particle_production_ene_data[0] < 1.0E10 && sub_lib_part != 1 )
  {
    particle_prod_flg.push_back(1);
  }

  if( particle_production_ene_data[1] < 1.0E10 && sub_lib_part != 1001 )
  {
    particle_prod_flg.push_back(9);
  }

  if( particle_production_ene_data[2] < 1.0E10 && sub_lib_part != 1002 )
  {
    particle_prod_flg.push_back(31);
  }

  if( particle_production_ene_data[3] < 1.0E10 && sub_lib_part != 1003 )
  {
    particle_prod_flg.push_back(32);
  }
    
  if( particle_production_ene_data[4] < 1.0E10 && sub_lib_part != 2003 )
  {
    particle_prod_flg.push_back(33);
  }

  if( particle_production_ene_data[5] < 1.0E10 && sub_lib_part != 2004 )
  {
    particle_prod_flg.push_back(34);
  }

  int i_max = static_cast<int>(particle_prod_flg.size());
  if( i_max == 0 )
  {
    return -1;
  }

  return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_particle_production_calc_data()
{
  int i_max = static_cast<int>(particle_prod_flg.size());
  set_particle_production_resize_data(i_max);

  int particle_prod_data_no = static_cast<int>(particle_production_data.size());
  int react_type_no         = static_cast<int>(react_type_list.size());

  for(int i=0; i<i_max; i++)
  {
    Integer particle_prod_val = 0;
    set_particle_production_set_base_data(i, particle_prod_val);

    Integer count = 0;
    for(int j=0; j<particle_prod_data_no; j++)
    {
      if( particle_production_data[j][particle_production_sub_lib_no] == particle_prod_val )
      {
        Integer reaction_type = particle_production_data[j][particle_production_reaction_type];
        if( particle_production_data[j][particle_production_file_no] >  0 )
        {
          int pos = -1;
          for(int k=0; k<react_type_no; k++)
          {
            if( react_type_list[k] == reaction_type )
            {
              pos = k;
              break;
            }
          }

          if( pos >= 0 )
          {
            set_particle_production_xs_data(i, j, pos, reaction_type);
            set_particle_production_angular_data(i, j, pos, reaction_type);
            set_particle_production_ene_data(i, j, pos, reaction_type);

            particle_prod_reaction_type_all[i].push_back(reaction_type);
            particle_prod_file_no[i].push_back(12);
            particle_prod_reaction_type[i].push_back(reaction_type);
            count++;
          }
        }
      }
    }
    mod_particle_prod_heat(i, particle_prod_val);
    particle_prod_count[i] = count;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_particle_production_resize_data(int i_max)
{
  particle_prod_reaction_type_all.resize(i_max);

  particle_prod_count.resize(i_max);
  particle_prod_ene_sta.resize(i_max);
  particle_prod_ene_no.resize(i_max);
  particle_prod_file_no.resize(i_max);
  particle_prod_reaction_type.resize(i_max);
  particle_prod_frame_flg.resize(i_max);
  particle_prod_xs_each_emin.resize(i_max);
  particle_prod_xs.resize(i_max);
  particle_prod_xs_each.resize(i_max);
  particle_prod_heat.resize(i_max);

  particle_prod_distr_int_data.resize(i_max);
  particle_prod_distr_range_data.resize(i_max);
  particle_prod_distr_ene_data.resize(i_max);
  particle_prod_distr_data.resize(i_max);

  particle_prod_angular_ene_data.resize(i_max);
  particle_prod_angular_int_data.resize(i_max);
  particle_prod_angular_cos_data.resize(i_max);
  particle_prod_angular_distr_data.resize(i_max);
  particle_prod_angular_distr_data_integ.resize(i_max);

  particle_prod_ene_flg.resize(i_max);
  particle_prod_q_value.resize(i_max);
  particle_prod_mass_coef.resize(i_max);
  particle_prod_ene_int_data.resize(i_max);
  particle_prod_ene_range_data.resize(i_max);
  particle_prod_ene_data.resize(i_max);
  particle_prod_ene_prob_data.resize(i_max);

  //For distr_func_flg = 1 : second energy, distr_func_flg = 7 : angle (mu)
  particle_prod_ene_in_int_data.resize(i_max);
  particle_prod_ene_in_range_data.resize(i_max);
  particle_prod_ene_in_data.resize(i_max);
  particle_prod_a_int_data.resize(i_max);
  particle_prod_a_data.resize(i_max);
  particle_prod_a_distr_data.resize(i_max);
  particle_prod_a_distr_data_integ.resize(i_max);
  particle_prod_ene_out_coef_a.resize(i_max);
  particle_prod_ene_out_coef_b.resize(i_max);

  //For distr_func_flg = 1 : second energy, distr_func_flg = 7 : angle (mu)
  particle_prod_b_int_data.resize(i_max);
  particle_prod_b_data.resize(i_max);
  particle_prod_b_prob_data.resize(i_max);
  particle_prod_b_prob_data_integ.resize(i_max);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_particle_production_set_base_data(int i, Integer& particle_prod_val)
{
  particle_prod_val = 0;
  Real thresh_ene   = 0.0;
  if( particle_prod_flg[i] == 1 )
  {
    particle_prod_val = 1;
    thresh_ene        = particle_production_ene_data[0] * unit_micro;
  }
  else if( particle_prod_flg[i] == 9 )
  {
    particle_prod_val = 1001;
    thresh_ene        = particle_production_ene_data[1] * unit_micro;
  }
  else if( particle_prod_flg[i] == 31 )
  {
    particle_prod_val = 1002;
    thresh_ene        = particle_production_ene_data[2] * unit_micro;
  }
  else if( particle_prod_flg[i] == 32 )
  {
    particle_prod_val = 1003;
    thresh_ene        = particle_production_ene_data[3] * unit_micro;
  }
  else if( particle_prod_flg[i] == 33 )
  {
    particle_prod_val = 2003;
    thresh_ene        = particle_production_ene_data[4] * unit_micro;
  }
  else if( particle_prod_flg[i] == 34 )
  {
    particle_prod_val = 2004;
    thresh_ene        = particle_production_ene_data[5] * unit_micro;
  }

  int     j_max         = static_cast<int>(union_ene_grid.size());
  Integer union_ene_sta = -1;
  for(int j=0; j<j_max; j++)
  {
    if( union_ene_grid[j] >= thresh_ene * (1.0 - 1.0E-10) )
    {
      union_ene_sta = j+1;
      break;
    }
  }
  if( union_ene_sta < 0 )
  {
    union_ene_sta = j_max + 1;
  }

  particle_prod_ene_sta[i] = union_ene_sta;
  particle_prod_ene_no[i]  = j_max - union_ene_sta + 1;

  particle_prod_xs_each_emin[i] = -100.0;

  int union_ene_grid_no = static_cast<int>(union_ene_grid.size());
  particle_prod_xs[i].resize(union_ene_grid_no);
  particle_prod_xs_each[i].resize(union_ene_grid_no);
  particle_prod_heat[i].resize(union_ene_grid_no);
  for(int j=0; j<union_ene_grid_no; j++)
  {
    particle_prod_xs[i][j]        = 0.0;
    particle_prod_xs_each[i][j]   = 0.0;
    particle_prod_heat[i][j]      = 0.0;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_particle_production_xs_data(int i, int j, int pos, Integer reaction_type)
{
  vector<Integer> int_vec, range_vec;
  vector<Real>    ene_vec, distr_vec;

  if( (reaction_type == 102 && sub_lib_part == 1) ||
      particle_production_data[j][particle_production_file_no] == 4 )
  {
    set_particle_production_xs_data_by_angle_data(i, j, pos, reaction_type,
                                                  range_vec, int_vec, ene_vec, distr_vec);
  }
  else
  {
    set_particle_production_xs_data_by_ene_angle_data(i, j, pos, reaction_type,
                                                      range_vec, int_vec, ene_vec, distr_vec);
  }

  particle_prod_distr_int_data[i].push_back(int_vec);
  particle_prod_distr_range_data[i].push_back(range_vec);
  particle_prod_distr_ene_data[i].push_back(ene_vec);
  particle_prod_distr_data[i].push_back(distr_vec);

  int_vec.clear();
  range_vec.clear();
  distr_vec.clear();
  ene_vec.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_particle_production_xs_data_by_angle_data
                             (int i, int j, int pos, Integer reaction_type,
                              vector<Integer>& range_vec, vector<Integer>& int_vec,
                              vector<Real>& ene_vec,      vector<Real>& distr_vec)
{
  Integer ref_frame_flg = -1;
  if( reaction_type == 102 )
  {
    ref_frame_flg = 1;
  }
  particle_prod_frame_flg[i].push_back(ref_frame_flg);

  int union_ene_grid_no = static_cast<int>(union_ene_grid.size());
  int ene_sta           = 0;
  if( reaction_type != 2 )
  {
    ene_sta = static_cast<int>(react_type_ene_sta[pos]);
  }

  int ele_no  = 0;
  for(int k=ene_sta; k<union_ene_grid_no; k++)
  {
    if( reaction_type == 2 )
    {
      particle_prod_xs[i][k] = react_xs_sc[k];
    }
    else
    {
      particle_prod_xs[i][k] += react_xs[pos][ele_no];
      ele_no++;
    }
  }

  int_vec.resize(1);
  range_vec.resize(1);
  ene_vec.resize(2);
  distr_vec.resize(2);

  int_vec[0]   = int_lin_lin;
  range_vec[0] = 2;

  ene_sta      = static_cast<int>(particle_prod_ene_sta[i] - 1);
  ene_vec[0]   = union_ene_grid[ene_sta];
  ene_vec[1]   = union_ene_grid[union_ene_grid_no-1];
  distr_vec[0] = 1.0;
  distr_vec[1] = 1.0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_particle_production_xs_data_by_ene_angle_data
                             (int i, int j, int pos, Integer reaction_type,
                              vector<Integer>& range_vec, vector<Integer>& int_vec,
                              vector<Real>& ene_vec,      vector<Real>& distr_vec)
{
  int k_max    = static_cast<int>(prod_distr_data_obj_vec.size());
  int react_no = -1;
  for(int k=0; k<k_max; k++)
  {
    if( prod_distr_data_obj_vec[k].get_reaction_type() == reaction_type )
    {
      react_no = k;
      break;
    }
  }
  if( react_no < 0 )
  {
    string func_name  = "set_particle_production_xs_data_by_ene_angle_data";
    ostringstream oss01;
    oss01 << reaction_type;
    string str_data01 = "Reaction type                    : " + oss01.str();
    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("There is no reaction type in prod_distr_data_obj_vec.");
    err_com.push_back("Please check the program or the neutron data library.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  ProductDistributionDataContainer prod_obj = prod_distr_data_obj_vec[react_no];

  Integer ref_frame_flg = -1;
  if( prod_obj.get_ref_frame_flg() == 1 )
  {
    ref_frame_flg = 1;
  }
  particle_prod_frame_flg[i].push_back(ref_frame_flg);

  int prod_type = static_cast<int>(particle_production_data[j][particle_production_type] - 1);
  int_vec   = prod_obj.get_product_distr_int_data()[prod_type];
  range_vec = prod_obj.get_product_distr_range_data()[prod_type];
  ene_vec   = prod_obj.get_product_distr_ene_data()[prod_type];
  distr_vec = prod_obj.get_product_distr_data()[prod_type];
  prod_obj.clear();

  int union_ene_grid_no = static_cast<int>(union_ene_grid.size());
  int ene_sta           = 0;
  int skip_flg          = 0;
  if( reaction_type != 2 )
  {
    ene_sta = static_cast<int>(react_type_ene_sta[pos]);
  }

  int ele_no  = 0;
  for(int k=ene_sta; k<union_ene_grid_no; k++)
  {
    Real ene_val = union_ene_grid[k] * unit_mega;
    Real y_val  = 0.0;
    ti_obj.interpolation_tab1_in_range(ene_val, y_val, range_vec, int_vec, ene_vec, distr_vec);
    if( y_val < min_value )
    {
      y_val = 0.0;
    }

    Real xs_val  = 0.0;
    if( reaction_type == 2 )
    {
      xs_val = react_xs_sc[k];
    }
    else
    {
      xs_val = react_xs[pos][ele_no];
      ele_no++;
    }

    if( reaction_type >= 203 && reaction_type <= 207 ) //(z,Xp), (z,Xd), (z,Xt), (z,XHe3), (z,Xalpha)
    {
      if( particle_prod_xs_each[i][k] < min_value )
      {
        particle_prod_xs[i][k] += y_val * xs_val;
      }
      else
      {
        if( skip_flg == 0 )
        {
          skip_flg = 1;
          particle_prod_xs_each_emin[i] = union_ene_grid[k];

          string func_name  = "set_particle_production_xs_data_by_ene_angle_data";
          ostringstream oss01, oss02, oss03;
          oss01 << reaction_type;
          oss02 << particle_production_data[j][particle_production_sub_lib_no];
          oss03 << setw(8) << std::showpoint << std::scientific << union_ene_grid[k];
          string str_data01 = "Reaction type       : " + oss01.str();
          string str_data02 = "Particle type       : " + oss02.str();
          string str_data03 = "Lowest energy [MeV] : " + oss03.str();
          vector<string> err_com;
          err_com.push_back(str_data01);
          err_com.push_back(str_data02);
          err_com.push_back("                     (1001=p, 1002=d, 1003=h, 2003=He-3, 2004=alpha)");
          err_com.push_back(str_data03);
          err_com.push_back("");
          err_com.push_back("The particle production cross section from this energy is not added");
          err_com.push_back("to the total particle production cross section in the HPD block.");
          err_com.push_back("");
          err_com.push_back("The gas production cross section in the SIG Block is modified to zero");
          err_com.push_back("when the energy grid is larger than the lowest energy.");
          err_com.push_back("");
          err_com.push_back("Please check the program or the neutron data library.");
          err_obj.output_caution(class_name, func_name, err_com);

          Integer mod_reaction_type = unassigned_mt_no;
          if( particle_production_data[j][particle_production_sub_lib_no] == 1001 )
          {
            mod_reaction_type = 203;
          }
          else if( particle_production_data[j][particle_production_sub_lib_no] == 1002 )
          {
            mod_reaction_type = 204;
          }
          else if( particle_production_data[j][particle_production_sub_lib_no] == 1003 )
          {
            mod_reaction_type = 205;
          }
          else if( particle_production_data[j][particle_production_sub_lib_no] == 2003 )
          {
            mod_reaction_type = 206;
          }
          else if( particle_production_data[j][particle_production_sub_lib_no] == 2004 )
          {
            mod_reaction_type = 207;
          }
          mod_gas_production_xs(mod_reaction_type, particle_prod_xs_each_emin[i]);
        }
      }
    }
    else
    {
      particle_prod_xs[i][k]      += y_val * xs_val;
      particle_prod_xs_each[i][k] += y_val * xs_val;
    }
  }
 
  k_max = static_cast<int>(ene_vec.size());
  for(int k=0; k<k_max; k++)
  {
    ene_vec[k] *= unit_micro;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::mod_gas_production_xs(Integer mod_reaction_type, Real mod_e_min)
{
  if( mod_e_min < min_value )
  {
    return;
  }

  int i_max = static_cast<int>(react_type_list.size());
  for(int i=0; i<i_max; i++)
  {
    if( react_type_list[i] == mod_reaction_type )
    {
      Real mod_e_min_val = digit_obj.get_adjusted_value(mod_e_min, sig_fig, -0.5);

      int ene_no_each = static_cast<int>(react_xs[i].size());
      int ene_no_uni  = static_cast<int>(union_ene_grid.size());
      int ene_sta     = ene_no_uni - ene_no_each;
      for(int j=ene_sta; j<ene_no_uni; j++)
      {
        if( union_ene_grid[j] > mod_e_min_val )
        {
          react_xs[i][j-ene_sta] = 0.0;
        }
      }

      break;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_particle_production_angular_data(int i, int j, int pos, Integer reaction_type)
{
  Integer file_no = particle_production_data[j][particle_production_file_no];
  if( reaction_type == 2 )
  {
    set_particle_production_angular_data_elastic(i);
  }
  else if( reaction_type == 102 && sub_lib_part == 1 )
  {
    set_particle_production_angular_data_capture(i, pos);
  }
  else if( file_no == 4 )
  {
    set_particle_production_angular_data_by_angle_data(i, j, pos, reaction_type);
  }
  else //if( file_no == 6 )
  {
    set_particle_production_angular_data_by_ene_angle_data(i, j, pos, reaction_type);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_particle_production_angular_data_elastic(int i)
{
  string func_name  = "set_particle_production_angular_data_elastic";

  particle_prod_angular_ene_data[i].push_back(angular_distr_ene_data[0]);
  particle_prod_angular_int_data[i].push_back(angular_distr_int_data[0]);

  Real mass_data = nucl_data_obj.get_general_data_obj().get_mass()
                 / nucl_data_obj.get_general_data_obj().get_mass_projectile();
  Real mass_coef = 2.0 * mass_data / ((1.0 + mass_data) * (1.0 + mass_data));

  int k_max = static_cast<int>(angular_distr_ene_data[0].size());
  vector<Real>          mass_vec;
  vector<vector<Real> > cos_vec, distr_vec, distr_integ_vec;
  mass_vec.resize(k_max);
  cos_vec.resize(k_max);
  distr_vec.resize(k_max);
  distr_integ_vec.resize(k_max);
  for(int k=0; k<k_max; k++)
  {
    int l_max = static_cast<int>(angular_distr_cos_data[0][k].size());
    cos_vec[k].resize(l_max);
    distr_vec[k].resize(l_max);
    for(int l=0; l<l_max; l++)
    {
      int ele_no = l_max - 1 - l;
      cos_vec[k][ele_no]   =  -1.0 * angular_distr_cos_data[0][k][l];
      distr_vec[k][ele_no] =         angular_distr_data[0][k][l];
    }

    Integer int_val = angular_distr_int_data[0][k];
    Real    sum     = 0.0;
    integ_obj.integrate_for_ace_data(class_name, func_name, cos_vec[k], distr_vec[k], distr_integ_vec[k],
                                     int_val, sum);

    Real cos_coef = set_particle_production_calc_cos_coef(int_val, cos_vec[k], distr_vec[k]);
    mass_vec[k]   = mass_coef * angular_distr_ene_data[0][k] * (1.0 + cos_coef);
  }
  particle_prod_angular_cos_data[i].push_back(cos_vec);
  particle_prod_angular_distr_data[i].push_back(distr_vec);
  particle_prod_angular_distr_data_integ[i].push_back(distr_integ_vec);

      k_max  = static_cast<int>(particle_prod_ene_no[i]);
  int ene_no = static_cast<int>(particle_prod_ene_sta[i] - 1);
  for(int k=0; k<k_max; k++)
  {
    Real heat_val = 0.0;
    ti_obj.interpolation_1d_in_range(int_log_log, union_ene_grid[ene_no], heat_val,
                                     angular_distr_ene_data[0], mass_vec);

    particle_prod_heat[i][ene_no] += heat_val * particle_prod_xs[i][ene_no];
    ene_no++;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_particle_production_angular_data_capture(int i, int pos)
{
  vector<Integer>       int_vec;
  vector<Real>          ene_vec;
  vector<vector<Real> > cos_vec, distr_vec, distr_integ_vec;

  int union_ene_grid_no = static_cast<int>(union_ene_grid.size());
  int ene_sta           = static_cast<int>(react_type_ene_sta[pos]);
  if( ene_sta > 0 )
  {
    ene_sta--;
  }
  ene_vec.resize(2);
  ene_vec[0] = union_ene_grid[ene_sta];
  ene_vec[1] = union_ene_grid[union_ene_grid_no - 1];
  particle_prod_angular_ene_data[i].push_back(ene_vec);

  int k_max = static_cast<int>(ene_vec.size());
  int_vec.resize(k_max);
  cos_vec.resize(k_max);
  distr_vec.resize(k_max);
  distr_integ_vec.resize(k_max);
  for(int k=0; k<k_max; k++)
  {
    int_vec[k] = int_lin_lin;

    int l_max = 3;
    cos_vec[k].resize(l_max);
    distr_vec[k].resize(l_max);
    distr_integ_vec[k].resize(l_max);
    cos_vec[k][0]         =  -1.00;
    cos_vec[k][1]         =   0.99;
    cos_vec[k][2]         =   1.00;
    distr_vec[k][0]       =   0.00;
    distr_vec[k][1]       =   0.00;
    distr_vec[k][2]       = 200.00;
    distr_integ_vec[k][0] =   0.00;
    distr_integ_vec[k][1] =   0.00;
    distr_integ_vec[k][2] =   1.00;
  }
  particle_prod_angular_int_data[i].push_back(int_vec);
  particle_prod_angular_cos_data[i].push_back(cos_vec);
  particle_prod_angular_distr_data[i].push_back(distr_vec);
  particle_prod_angular_distr_data_integ[i].push_back(distr_integ_vec);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_particle_production_angular_data_by_angle_data
                                          (int i, int j, int pos, Integer reaction_type)
{
  Real coef2 = 1.0;
  if( reaction_type >= react_n_h1_min && reaction_type <= react_n_h1_max )
  {
    coef2 = 0.99862;
  }
  else if( reaction_type >= react_n_h2_min && reaction_type <= react_n_h2_max )
  {
    coef2 = 1.99626;
  }
  else if( reaction_type >= react_n_h3_min && reaction_type <= react_n_h3_max )
  {
    coef2 = 2.98960;
  }
  else if( reaction_type >= react_n_he3_min && reaction_type <= react_n_he3_max )
  {
    coef2 = 2.98903;
  }
  else if( reaction_type >= react_n_he4_min && reaction_type <= react_n_he4_max )
  {
    coef2 = 3.96713;
  }
  Real coef1  = nucl_data_obj.get_general_data_obj().get_mass()
              / nucl_data_obj.get_general_data_obj().get_mass_projectile();
       coef2 /= nucl_data_obj.get_general_data_obj().get_mass_projectile();

  vector<Real> mass_coef;
  mass_coef.resize(3);
  mass_coef[0] = (1.0 + coef1) * react_q_value[pos] / coef1;
  mass_coef[1] = coef1 * (1.0 + coef1 - coef2) / coef2;
  mass_coef[2] = coef2 / ((1.0 + coef1) * (1.0 + coef1));

  int k_max    = static_cast<int>(ene_angle_data_obj_vec.size());
  int react_no = -1;
  for(int k=0; k<k_max; k++)
  {
    if( ene_angle_data_obj_vec[k].get_reaction_type() == reaction_type )
    {
      react_no = k;
      break;
    }
  }
  if( react_no < 0 )
  {
    string func_name  = "set_particle_production_angular_data_by_angle_data";
    ostringstream oss01;
    oss01 << reaction_type;
    string str_data01 = "Reaction type : " + oss01.str();
    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("There is no reaction type in ene_angle_data_obj_vec.");
    err_com.push_back("Please check the program or the neutron data library.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  Integer angular_repr_flg = ene_angle_data_obj_vec[react_no].get_angular_repr_flg();
  if( angular_repr_flg == 0 )
  {
    //Angular representation flag = 0 means isotropic distribution.
    //Set dummy data and skip expansion of angular distribution data
    vector<Integer>       int_vec;
    vector<Real>          real_vec;
    vector<vector<Real> > real_vec2;
    int_vec.resize(0);
    real_vec.resize(0);
    clr_obj.clear_vec_array2_real(real_vec2);

    particle_prod_angular_ene_data[i].push_back(real_vec);
    particle_prod_angular_int_data[i].push_back(int_vec);
    particle_prod_angular_cos_data[i].push_back(real_vec2);
    particle_prod_angular_distr_data[i].push_back(real_vec2);
    particle_prod_angular_distr_data_integ[i].push_back(real_vec2);
  }
  else if( angular_repr_flg == 1 )
  {
    set_particle_production_angular_data_by_angle_data_legendre(i, j, pos, react_no, mass_coef);
  }
  else if( angular_repr_flg == 2 )
  {
    set_particle_production_angular_data_by_angle_data_table(i, j, pos, react_no, mass_coef);
  }
  else
  {
    string func_name  = "set_particle_production_angular_data_by_angle_data";
    ostringstream oss01, oss02;
    oss01 << reaction_type;
    oss02 << angular_repr_flg;
    string str_data01 = "Reaction type               : " + oss01.str();
    string str_data02 = "Angular representation flag : " + oss02.str();
    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("The angular representation flag is only available for");
    err_com.push_back("0 (for isotropic) or 1 (for legendre polynomial) or 2 (for table).");
    err_com.push_back("Please check the program or the neutron data library.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
    //err_com.push_back("This program may not be able to appropriately process");
    //err_com.push_back("the particle production angular data.");
    //err_obj.output_caution(class_name, func_name, err_com);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_particle_production_angular_data_by_angle_data_legendre
                             (int i, int j, int pos, int react_no, vector<Real>& mass_coef)
{
  vector<Real> ene_vec = ene_angle_data_obj_vec[react_no].get_angular_probability_ene_polynomial();

  vector<Integer>       int_vec;
  vector<Real>          mass_vec;
  vector<vector<Real> > list_vec, x_vec, y_vec, y_integ_vec;
  int k_max = static_cast<int>(ene_vec.size());
  int_vec.resize(k_max);
  mass_vec.resize(k_max);
  list_vec.resize(k_max);
  x_vec.resize(k_max);
  y_vec.resize(k_max);
  y_integ_vec.resize(k_max);
  for(int k=0; k<k_max; k++)
  {
    ene_vec[k] *= unit_micro;
    int_vec[k]  = int_lin_lin;

    Real         sum = 0.0;
    list_vec[k] = ene_angle_data_obj_vec[react_no].get_angular_data_polynomial()[k];

    //string func_name = "set_particle_production_angular_data_by_angle_data_legendre";
    //lin_tab_obj.check_legendre_polynomial_list_data
    //  (class_name, func_name, ene_angle_data_obj_vec[react_no].get_reaction_type(),
    //   i, j, k, -1, list_vec[k]);

    lin_tab_obj.linearize_list_data_by_legendre_polynomial
                  (list_vec[k], x_vec[k], y_vec[k], y_integ_vec[k], sum);

    Real cos_coef = set_particle_production_calc_cos_coef(int_vec[k], x_vec[k], y_vec[k]);
    Real mass_val = mass_coef[1] * (1.0 + mass_coef[0]/ene_vec[k]);
    if( mass_val < min_value )
    {
      mass_val = 0.0;
    }

    mass_vec[k] = ene_vec[k] * mass_coef[2] * (mass_val + 1.0 + 2.0*cos_coef*sqrt(mass_val));

    int l_max = static_cast<int>(y_vec[k].size());
    sum = 1.0 / sum;
    for(int l=0; l<l_max; l++)
    {
      y_vec[k][l] *= sum;
    }
  }
  particle_prod_angular_ene_data[i].push_back(ene_vec);
  particle_prod_angular_int_data[i].push_back(int_vec);
  particle_prod_angular_cos_data[i].push_back(x_vec);
  particle_prod_angular_distr_data[i].push_back(y_vec);
  particle_prod_angular_distr_data_integ[i].push_back(y_integ_vec);

      k_max  = static_cast<int>(particle_prod_ene_no[i]);
  int ene_no = static_cast<int>(particle_prod_ene_sta[i] - 1);
  int ele_no = ene_no - react_type_ene_sta[pos];
  for(int k=0; k<k_max; k++)
  {
    if( ene_no >= react_type_ene_sta[pos] )
    {
      Real heat_val = 0.0;
      ti_obj.interpolation_1d_in_range(int_lin_lin, union_ene_grid[ene_no], heat_val, ene_vec, mass_vec);
      particle_prod_heat[i][ene_no] += heat_val * react_xs[pos][ele_no];
    }
    ene_no++;
    ele_no++;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_particle_production_angular_data_by_angle_data_table
                             (int i, int j, int pos, int react_no, vector<Real>& mass_coef)
{
  string func_name  = "set_particle_production_angular_data_by_angle_data_table";

  vector<Real> ene_vec = ene_angle_data_obj_vec[react_no].get_angular_probability_ene_tab();

  vector<Integer>       int_vec;
  vector<Real>          mass_vec;
  vector<vector<Real> > x_vec, y_vec, y_integ_vec;

  vector<int> pos_data;
  pos_data.resize(1);
  Integer reaction_type = ene_angle_data_obj_vec[react_no].get_reaction_type();
  int     k_max         = static_cast<int>(ene_vec.size());
  int_vec.resize(k_max);
  mass_vec.resize(k_max);
  y_integ_vec.resize(k_max);
  x_vec = ene_angle_data_obj_vec[react_no].get_angular_probability_cos_tab();
  y_vec = ene_angle_data_obj_vec[react_no].get_angular_probability_data_tab();
  for(int k=0; k<k_max; k++)
  {
    ene_vec[k] *= unit_micro;

    vector<Integer> int_chk, range_chk;
    pos_data[0] = k;
    int_chk     = ene_angle_data_obj_vec[react_no].get_angular_probability_int_data_tab()[k];
    range_chk   = ene_angle_data_obj_vec[react_no].get_angular_probability_range_data_tab()[k];
    int_vec[k]  = integ_obj.check_interpolation(class_name, func_name, reaction_type, pos_data,
                                                range_chk, int_chk);

    lin_tab_obj.normalize_tab1_data(int_vec[k], x_vec[k], y_vec[k]);

    Real sum = 0.0;
    integ_obj.integrate_for_ace_data
      (class_name, func_name, x_vec[k], y_vec[k], y_integ_vec[k], int_vec[k], sum);

    Real cos_coef = set_particle_production_calc_cos_coef(int_vec[k], x_vec[k], y_vec[k]);
    mass_vec[k]   = mass_coef[1] * (1.0 + mass_coef[0]/ene_vec[k]);
    if( mass_vec[k] < min_value )
    {
      mass_vec[k] = 0.0;
    }
    mass_vec[k] = ene_vec[k] * mass_coef[2] * (mass_vec[k] + 1.0 + 2.0*cos_coef*sqrt(mass_vec[k]));
  }
  particle_prod_angular_ene_data[i].push_back(ene_vec);
  particle_prod_angular_int_data[i].push_back(int_vec);
  particle_prod_angular_cos_data[i].push_back(x_vec);
  particle_prod_angular_distr_data[i].push_back(y_vec);
  particle_prod_angular_distr_data_integ[i].push_back(y_integ_vec);

      k_max  = static_cast<int>(particle_prod_ene_no[i]);
  int ene_no = static_cast<int>(particle_prod_ene_sta[i] - 1);
  int ele_no = ene_no - react_type_ene_sta[pos];
  for(int k=0; k<k_max; k++)
  {
    if( ene_no >= react_type_ene_sta[pos] )
    {
      Real heat_val = 0.0;
      ti_obj.interpolation_1d_in_range(int_lin_lin, union_ene_grid[ene_no], heat_val, ene_vec, mass_vec);
      particle_prod_heat[i][ene_no] += heat_val * react_xs[pos][ele_no];
    }
    ene_no++;
    ele_no++;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_particle_production_angular_data_by_ene_angle_data
                                          (int i, int j, int pos, Integer reaction_type)
{
  int k_max    = static_cast<int>(prod_distr_data_obj_vec.size());
  int react_no = -1;
  for(int k=0; k<k_max; k++)
  {
    if( prod_distr_data_obj_vec[k].get_reaction_type() == reaction_type )
    {
      react_no = k;
      break;
    }
  }
  if( react_no < 0 )
  {
    string func_name  = "set_particle_production_angular_data_by_ene_angle_data";
    ostringstream oss01;
    oss01 << reaction_type;
    string str_data01 = "Reaction type : " + oss01.str();
    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("There is no reaction type in ene_angle_data_obj_vec.");
    err_com.push_back("Please check the program or the neutron data library.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  ProductDistributionDataContainer prod_obj = prod_distr_data_obj_vec[react_no];
  Integer         sub_lib_no_part  = particle_production_data[j][particle_production_sub_lib_no];
  Real            mass_product     = 0.0;
  vector<Real>    mat_data_product = prod_obj.get_mat_data_product();
  vector<Integer> distr_func_flg   = prod_obj.get_distr_func_flg();
  int             production_type  = particle_production_data[j][particle_production_type] - 1;
                  k_max            = static_cast<int>(distr_func_flg.size());
  for(int k=0; k<k_max; k++)
  {
    if( k == production_type )
    {
      mass_product =  prod_obj.get_mass_product()[k];
      if( distr_func_flg[k] == 4 )
      {
        Integer mat_data_product_int = static_cast<Integer>(round(mat_data_product[k]));
        if( mat_data_product_int == sub_lib_no_part && distr_func_flg[0] == 2 )
        {
          set_particle_production_angular_data_by_ene_angle_data_by_two_body_scat
            (i, j, 0, pos, react_no, mass_product, -1);
        }
      }
      else if( distr_func_flg[k] == 2 )
      {
        set_particle_production_angular_data_by_ene_angle_data_by_two_body_scat
          (i, j, k, pos, react_no, mass_product, 1);
      }
      else if( distr_func_flg[k] == 7 )
      {
        set_particle_production_angular_data_by_ene_angle_data_by_lab(i, j, k, pos, react_no);
      }
      else
      {
        vector<Integer>       int_vec;
        vector<Real>          real_vec;
        vector<vector<Real> > real_vec2;
        int_vec.resize(0);
        real_vec.resize(0);
        clr_obj.clear_vec_array2_real(real_vec2);

        particle_prod_angular_ene_data[i].push_back(real_vec);
        particle_prod_angular_int_data[i].push_back(int_vec);
        particle_prod_angular_cos_data[i].push_back(real_vec2);
        particle_prod_angular_distr_data[i].push_back(real_vec2);
        particle_prod_angular_distr_data_integ[i].push_back(real_vec2);
      }

      break;
    }
  }
  prod_obj.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_particle_production_angular_data_by_ene_angle_data_by_two_body_scat
                             (int i, int j, int k, int pos, int react_no, Real& mass_product, Integer sign_coef)
{
  string func_name  = "set_particle_production_angular_data_by_ene_angle_data_by_two_body_scat";

  ProductDistributionDataContainer prod_obj = prod_distr_data_obj_vec[react_no];
  vector<Real> ene_vec = prod_obj.get_two_body_ene_data()[k];

  Real coef1  = nucl_data_obj.get_general_data_obj().get_mass()
              / nucl_data_obj.get_general_data_obj().get_mass_projectile();
  Real coef2  = mass_product / nucl_data_obj.get_general_data_obj().get_mass_projectile();

  vector<Real> mass_coef;
  mass_coef.resize(3);
  mass_coef[0] = (1.0 + coef1) * react_q_value[pos] / coef1;
  mass_coef[1] = coef1 * (1.0 + coef1 - coef2) / coef2;
  mass_coef[2] = coef2 / ((1.0 + coef1) * (1.0 + coef1));

  vector<Integer>       int_vec;
  vector<Real>          mass_vec;
  vector<vector<Real> > x_vec, y_vec, y_integ_vec;
  int l_max = static_cast<int>(ene_vec.size());
  int_vec.resize(l_max);
  mass_vec.resize(l_max);
  x_vec.resize(l_max);
  y_vec.resize(l_max);
  y_integ_vec.resize(l_max);
  for(int l=0; l<l_max; l++)
  {
    ene_vec[l] *= unit_micro;

    Integer two_body_repr_flg = prod_obj.get_two_body_repr_flg()[k][l];
    Real    sum               = 0.0;
    if( two_body_repr_flg == 0 )
    {
      int_vec[l] = int_lin_lin;

      vector<Real> list_vec = prod_obj.get_two_body_legendre_coef()[k][l];
      if( sign_coef < 0 )
      {
        for(int m=0; m<static_cast<int>(list_vec.size()); m+=2)
        {
          list_vec[m] *= -1.0;
        }
      }

      //lin_tab_obj.check_legendre_polynomial_list_data
      //  (class_name, func_name, prod_obj.get_reaction_type(),
      //   i, j, k, -1, list_vec);

      lin_tab_obj.linearize_list_data_by_legendre_polynomial
                    (list_vec, x_vec[l], y_vec[l], y_integ_vec[l], sum);
    }
    else
    {
      int_vec[l] = two_body_repr_flg - 10;

      x_vec[l] = prod_obj.get_two_body_cos()[k][l];
      y_vec[l] = prod_obj.get_two_body_prob()[k][l];
      lin_tab_obj.normalize_tab1_data(int_vec[l], x_vec[l], y_vec[l]);
      integ_obj.integrate_for_ace_data
        (class_name, func_name, x_vec[l], y_vec[l], y_integ_vec[l], int_vec[l], sum);
    }

    Real cos_coef = set_particle_production_calc_cos_coef(int_vec[l], x_vec[l], y_vec[l]);
    mass_vec[l]   = mass_coef[1] * (1.0 + mass_coef[0]/ene_vec[l]);
    if( mass_vec[l] < min_value )
    {
      mass_vec[l] = 0.0;
    }
    mass_vec[l] = ene_vec[l] * mass_coef[2] * (mass_vec[l] + 1.0 + 2.0*cos_coef*sqrt(mass_vec[l]));
  }
  prod_obj.clear();

  particle_prod_angular_ene_data[i].push_back(ene_vec);
  particle_prod_angular_int_data[i].push_back(int_vec);
  particle_prod_angular_cos_data[i].push_back(x_vec);
  particle_prod_angular_distr_data[i].push_back(y_vec);
  particle_prod_angular_distr_data_integ[i].push_back(y_integ_vec);

      l_max  = static_cast<int>(particle_prod_ene_no[i]);
  int ene_no = static_cast<int>(particle_prod_ene_sta[i] - 1);
  int ele_no = ene_no - react_type_ene_sta[pos];
  for(int l=0; l<l_max; l++)
  {
    if( ene_no >= react_type_ene_sta[pos] )
    {
      Real heat_val = 0.0;
      ti_obj.interpolation_1d_in_range(int_lin_lin, union_ene_grid[ene_no], heat_val, ene_vec, mass_vec);
      particle_prod_heat[i][ene_no] += heat_val * react_xs[pos][ele_no];
    }
    ene_no++;
    ele_no++;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_particle_production_angular_data_by_ene_angle_data_by_lab
                             (int i, int j, int k, int pos, int react_no)
{
  string func_name  = "set_particle_production_angular_data_by_ene_angle_data_by_lab";

  ProductDistributionDataContainer prod_obj = prod_distr_data_obj_vec[react_no];
  vector<Real> ene_vec = prod_obj.get_lab_ene()[k];

  vector<Integer>       int_vec;
  vector<vector<Real> > x_vec, y_vec, y_integ_vec;

  vector<int> pos_data;
  pos_data.resize(2);
  pos_data[0] = k;
  Integer reaction_type = prod_obj.get_reaction_type();
  int     l_max         = static_cast<int>(ene_vec.size());
  int_vec.resize(l_max);
  x_vec.resize(l_max);
  y_vec.resize(l_max);
  y_integ_vec.resize(l_max);
  for(int l=0; l<l_max; l++)
  {
    ene_vec[l] *= unit_micro;

    vector<Integer> int_chk, range_chk;
    pos_data[1] = l;
    int_chk     = prod_obj.get_lab_integrate_int_data()[k][l];
    range_chk   = prod_obj.get_lab_integrate_range_data()[k][l];
    int_vec[l]  = integ_obj.check_interpolation(class_name, func_name, reaction_type, pos_data,
                                                range_chk, int_chk);

    x_vec[l] = prod_obj.get_lab_integrate_cos_data()[k][l];
    y_vec[l] = prod_obj.get_lab_integrate_data()[k][l];
    int m_max = static_cast<int>(y_vec[l].size());
    for(int m=0; m<m_max; m++)
    {
      if( y_vec[l][m] < min_value )
      {
        y_vec[l][m] = 0.0;
      }
    }

    Real sum = 0.0;
    integ_obj.integrate_for_ace_data
      (class_name, func_name, x_vec[l], y_vec[l], y_integ_vec[l], int_vec[l], sum);
  }
  prod_obj.clear();

  particle_prod_angular_ene_data[i].push_back(ene_vec);
  particle_prod_angular_int_data[i].push_back(int_vec);
  particle_prod_angular_cos_data[i].push_back(x_vec);
  particle_prod_angular_distr_data[i].push_back(y_vec);
  particle_prod_angular_distr_data_integ[i].push_back(y_integ_vec);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Real FastAceDataGenerator::set_particle_production_calc_cos_coef
                             (Integer int_val, vector<Real>& x_vec, vector<Real>& y_vec)
{
  Real cos_coef = 0.0;

  int i_max = static_cast<int>(x_vec.size());
  if( int_val == int_const )
  {
    for(int i=1; i<i_max; i++)
    {
      cos_coef += y_vec[i-1] * (x_vec[i] - x_vec[i-1]) + 0.5 * (x_vec[i] + x_vec[i-1]);
    }
  }
  else if( int_val == int_lin_lin )
  {
    for(int i=1; i<i_max; i++)
    {
      cos_coef += 0.25 * (y_vec[i] + y_vec[i-1]) * (x_vec[i] - x_vec[i-1]) * (x_vec[i] + x_vec[i-1]);
    }
  }
  else
  {
    cos_coef = -1.0;
  }

  return cos_coef;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_particle_production_ene_data(int i, int j, int pos, Integer reaction_type)
{
  if( reaction_type == 2 )
  {
    return;
  }
  else if( reaction_type == 102 && sub_lib_part == 1 )
  {
    //For capture reaction
    set_particle_production_ene_data_by_capture(i, j);
  }
  else if( particle_production_data[j][particle_production_file_no] == 4 )
  {
    //For Angular Distributions
    set_particle_production_ene_data_by_angle_data(i, j, pos, reaction_type);
  }
  else
  {
    //For Product Energy-Angle Distributions
    set_particle_production_ene_data_by_ene_angle_data(i, j, pos, reaction_type);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_particle_production_ene_data_by_capture(int i, int j)
{
  particle_prod_ene_flg[i].push_back(33);

  Real q_val           = 0.0;
  Real mass_val        = nucl_data_obj.get_general_data_obj().get_mass();
  Real mass_projectile = nucl_data_obj.get_general_data_obj().get_mass_projectile();
  Real mass_coef       = mass_projectile / (mass_val + mass_projectile);
  particle_prod_q_value[i].push_back(q_val);
  particle_prod_mass_coef[i].push_back(mass_coef);

  vector<Integer> int_vec, range_vec;
  vector<Real>    ene_vec, prob_vec;
  int_vec.resize(1);
  range_vec.resize(1);
  ene_vec.resize(2);
  prob_vec.resize(2);
  int_vec[0]   = int_lin_lin;
  range_vec[0] = static_cast<Integer>(ene_vec.size());
  particle_prod_ene_int_data[i].push_back(int_vec);
  particle_prod_ene_range_data[i].push_back(range_vec);

  int union_ene_grid_no = static_cast<int>(union_ene_grid.size());
  int ene_sta           = static_cast<int>(particle_prod_ene_sta[i] - 1);
  ene_vec[0]  = union_ene_grid[ene_sta];
  ene_vec[1]  = union_ene_grid[union_ene_grid_no - 1];
  prob_vec[0] = 1.0;
  prob_vec[1] = 1.0;
  particle_prod_ene_data[i].push_back(ene_vec);
  particle_prod_ene_prob_data[i].push_back(prob_vec);

  int k_max  = static_cast<int>(particle_prod_ene_no[i]);
  int ene_no = ene_sta;
  for(int k=0; k<k_max; k++)
  {
    particle_prod_heat[i][ene_no] += mass_coef*particle_prod_xs[i][ene_no]*union_ene_grid[ene_no];
    ene_no++;
  }

  set_particle_production_ene_data_add_void_data(i);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_particle_production_ene_data_by_angle_data
                             (int i, int j, int pos, Integer reaction_type)
{
  particle_prod_ene_flg[i].push_back(33);

  int k_max    = static_cast<int>(ene_angle_data_obj_vec.size());
  int react_no = -1;
  for(int k=0; k<k_max; k++)
  {
    if( ene_angle_data_obj_vec[k].get_reaction_type() == reaction_type )
    {
      react_no = k;
      break;
    }
  }

  Real mass_val        = nucl_data_obj.get_general_data_obj().get_mass();
  Real mass_projectile = nucl_data_obj.get_general_data_obj().get_mass_projectile();
  Real mass_tmp        = 1.0;
  if( reaction_type >= react_n_h1_min && reaction_type <= react_n_h1_max )
  {
    mass_tmp = 0.99862;
  }
  else if( reaction_type >= react_n_h2_min && reaction_type <= react_n_h2_max )
  {
    mass_tmp = 1.99626;
  }
  else if( reaction_type >= react_n_h3_min && reaction_type <= react_n_h3_max )
  {
    mass_tmp = 2.98960;
  }
  else if( reaction_type >= react_n_he3_min && reaction_type <= react_n_he3_max )
  {
    mass_tmp = 2.98903;
  }
  else if( reaction_type >= react_n_he4_min && reaction_type <= react_n_he4_max )
  {
    mass_tmp = 3.96713;
  }
  Real mass_coef1 = mass_val / mass_projectile;
  Real mass_coef2 = mass_tmp / mass_projectile;
  Real q_val      = (1.0 + mass_coef1) * (-1.0 * react_q_value[pos]) / mass_coef1;
  Real mass_coef  = mass_coef1 * (mass_coef1 - mass_coef2 + 1.0) / ((1.0 + mass_coef1) * (1.0 + mass_coef1));
  particle_prod_q_value[i].push_back(q_val);
  particle_prod_mass_coef[i].push_back(mass_coef);

  vector<Integer> int_vec, range_vec;
  vector<Real>    ene_vec, prob_vec;
  int_vec.resize(1);
  range_vec.resize(1);
  ene_vec.resize(2);
  prob_vec.resize(2);
  int_vec[0]   = int_lin_lin;
  range_vec[0] = static_cast<Integer>(ene_vec.size());
  ene_vec[0]   = 0.0;
  ene_vec[1]   = 0.0;
  prob_vec[0]  = 0.0;
  prob_vec[1]  = 0.0;
  particle_prod_ene_int_data[i].push_back(int_vec);
  particle_prod_ene_range_data[i].push_back(range_vec);
  particle_prod_ene_data[i].push_back(ene_vec);
  particle_prod_ene_prob_data[i].push_back(prob_vec);

  if( ene_angle_data_obj_vec[react_no].get_angular_repr_flg() == 0 )
  {
        k_max  = static_cast<int>(particle_prod_ene_no[i]);
    int ene_no = static_cast<int>(particle_prod_ene_sta[i] - 1);
    int ele_no = ene_no - react_type_ene_sta[pos];
    for(int k=0; k<k_max; k++)
    {
      if( ene_no >= react_type_ene_sta[pos] )
      {
        particle_prod_heat[i][ene_no] += mass_coef*(union_ene_grid[ene_no] - q_val)*react_xs[pos][ele_no];
      }
      ene_no++;
      ele_no++;
    }
  }

  set_particle_production_ene_data_add_void_data(i);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_particle_production_ene_data_by_ene_angle_data
                             (int i, int j, int pos, Integer reaction_type)
{
  int k_max    = static_cast<int>(prod_distr_data_obj_vec.size());
  int react_no = -1;
  for(int k=0; k<k_max; k++)
  {
    if( prod_distr_data_obj_vec[k].get_reaction_type() == reaction_type )
    {
      react_no = k;
      break;
    }
  }

  int         partial_ene_no    = static_cast<int>(particle_production_data[j][particle_production_type] - 1);
  Integer     distr_func_flg    = prod_distr_data_obj_vec[react_no].get_distr_func_flg()[partial_ene_no];
  vector<Real> mat_data_product = prod_distr_data_obj_vec[react_no].get_mat_data_product();

  k_max = static_cast<int>(mat_data_product.size());
  for(int k=0; k<k_max; k++)
  {
    Integer mat_data_product_int = static_cast<Integer>(round(mat_data_product[k]));
    if( mat_data_product_int == particle_production_data[j][particle_production_sub_lib_no] )
    {
      if( reaction_type == 102 )
      {
        //For capture reaction
        set_particle_production_ene_data_by_capture(i, j);
      }
      else if( k == partial_ene_no )
      {
        if( distr_func_flg == 1 )
        {
          //For continuum energy-angle distributions
          set_particle_production_ene_data_by_ene_angle_data_continuum(i, j, k, pos, react_no);
        }
        else if( distr_func_flg == 2 || distr_func_flg == 3 || distr_func_flg == 4 )
        {
          set_particle_production_ene_data_by_ene_angle_data_other(i, j, k, pos, react_no, distr_func_flg);
        }
        else if( distr_func_flg == 6 )
        {
          //For N-nody phase-space distributions
          set_particle_production_ene_data_by_ene_angle_data_phase_space(i, j, k, pos, react_no);
        }
        else if( distr_func_flg == 7 )
        {
          //For laboratory angle-energy law
          set_particle_production_ene_data_by_ene_angle_data_lab(i, j, k, pos, react_no);
        }
        else
        {
          //Set dummy data
          set_particle_production_ene_data_by_ene_angle_data_void(i);
        }
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_particle_production_ene_data_by_ene_angle_data_void(int i)
{
  vector<Integer> int_vec;
  vector<Real>    real_vec;
  int_vec.clear();
  real_vec.clear();
  particle_prod_ene_flg[i].push_back(-1);
  particle_prod_ene_range_data[i].push_back(int_vec);
  particle_prod_ene_int_data[i].push_back(int_vec);
  particle_prod_ene_data[i].push_back(real_vec);
  particle_prod_ene_prob_data[i].push_back(real_vec);

  set_particle_production_ene_data_add_void_data(i);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_particle_production_ene_data_by_ene_angle_data_continuum
                             (int i, int j, int k, int pos, int react_no)
{
  ProductDistributionDataContainer prod_obj = prod_distr_data_obj_vec[react_no];

  vector<Real> ene_vec;
  Integer      angular_repr_flg = prod_obj.get_angular_repr_flg()[k];
  Integer      ene_flg          = 0;
  set_particle_production_ene_data_by_ene_angle_data_continuum_set_ene_flg
    (i, k, react_no, angular_repr_flg, ene_flg);
  set_particle_production_ene_data_by_ene_angle_data_continuum_set_base_data(i, k, react_no, ene_vec);

  int l_max = static_cast<int>(ene_vec.size());
  vector<Integer>       ene_out_int_vec;
  vector<vector<Real> > ene_out_vec, ene_out_distr_vec, ene_out_distr_integ_vec;
  ene_out_int_vec.resize(l_max);
  ene_out_vec = prod_obj.get_cont_ene_b()[k];
  ene_out_distr_vec.resize(l_max);
  ene_out_distr_integ_vec.resize(l_max);

  Integer second_ene_int_data = prod_obj.get_second_ene_int_data()[k];
  if( second_ene_int_data != int_const && second_ene_int_data != int_lin_lin )
  {
    string func_name  = "set_particle_production_ene_data_by_ene_angle_data_continuum";
    ostringstream oss01, oss02, oss03, oss04, oss05;
    oss01 << i+1;
    oss02 << j+1;
    oss03 << k+1;
    oss04 << prod_obj.get_reaction_type();
    oss05 << second_ene_int_data;
    string str_data01 = "Position                         : " + oss01.str() + ", " + oss02.str() + ", "
                                                              + oss03.str();
    string str_data02 = "Reaction type                    : " + oss04.str();
    string str_data03 = "Second energy interpolation type : " + oss05.str();
    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("This interpolation type is not available.");
    err_com.push_back("Available interpolation type is constant and linear-linear.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  vector<Integer>                discrete_ene_no = prod_obj.get_discrete_ene_no()[k];
  vector<vector<vector<Real> > > cont_data       = prod_obj.get_cont_data()[k];
  for(int l=0; l<l_max; l++)
  {
    if( ene_flg == 4 )
    {
      ene_out_int_vec[l] = second_ene_int_data;
    }
    else
    {
      ene_out_int_vec[l] = second_ene_int_data + 10 * discrete_ene_no[l];
    }

    int m_max = static_cast<int>(ene_out_vec[l].size());
    ene_out_distr_vec[l].resize(m_max);
    ene_out_distr_integ_vec[l].resize(m_max);
    for(int m=0; m<m_max; m++)
    {
      if( ene_out_vec[l][m] < -1.0 * min_value )
      {
        string func_name  = "set_particle_production_ene_data_by_ene_angle_data_continuum";
        ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07;
        oss07.precision(8);
        oss07.setf(ios::showpoint);
        oss07.setf(ios::scientific);
        oss01 << i+1;
        oss02 << j+1;
        oss03 << k+1;
        oss04 << prod_obj.get_reaction_type();
        oss05 << l+1;
        oss06 << m+1;
        oss07 << ene_out_vec[l][m];
        string str_data01 = "Position                     : " + oss01.str() + ", " + oss02.str() + ", "
                                                              + oss03.str();
        string str_data02 = "Reaction type                : " + oss04.str();
        string str_data03 = "Position of incident energy  : " + oss05.str();
        string str_data04 = "Position of second energy    : " + oss06.str();
        string str_data05 = "Second energy [eV]           : " + oss07.str();
        vector<string> err_com;
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back(str_data04);
        err_com.push_back(str_data05);
        err_com.push_back("Secondary energy of Kalbachmann is less than 0 eV.");
        err_com.push_back("Secondary energy is modified to 0.0 eV");
        err_obj.output_caution(class_name, func_name, err_com);

        ene_out_vec[l][m] = 0.0;
      }

      ene_out_vec[l][m]       *= unit_micro;
      ene_out_distr_vec[l][m]  = cont_data[l][m][0] * unit_mega;

      if( ene_out_distr_vec[l][m] > 0.0 && ene_out_distr_vec[l][m] < min_value )
      {
        ene_out_distr_vec[l][m] = min_value;
      }

      if( m < discrete_ene_no[l] )
      {
        ene_out_distr_integ_vec[l][m] = ene_out_distr_vec[l][m];
      }
      else if( m > 0 )
      {
        if( m == discrete_ene_no[l] )
        {
          ene_out_distr_integ_vec[l][m] = ene_out_distr_integ_vec[l][m-1];
        }
        else
        {
          if( second_ene_int_data == int_const )
          {
            ene_out_distr_integ_vec[l][m] = ene_out_distr_integ_vec[l][m-1]
              + ene_out_distr_vec[l][m-1] * (ene_out_vec[l][m] - ene_out_vec[l][m-1]);
          }
          else if( second_ene_int_data == int_lin_lin )
          {
            ene_out_distr_integ_vec[l][m] = ene_out_distr_integ_vec[l][m-1]
                                          + 0.5 * (ene_out_distr_vec[l][m] + ene_out_distr_vec[l][m-1])
                                                * (ene_out_vec[l][m]       - ene_out_vec[l][m-1]);
          }
        } 
      }
      else
      {
        ene_out_distr_integ_vec[l][m] = 0.0;
      }
    }
    
    Real sum_inv = 1.0 / ene_out_distr_integ_vec[l][m_max - 1];
    for(int m=0; m<m_max; m++)
    {
      ene_out_distr_vec[l][m]       *= sum_inv;
      ene_out_distr_integ_vec[l][m] *= sum_inv;
    }
  }
  prod_obj.clear();
  discrete_ene_no.clear();
  cont_data.clear();

  particle_prod_a_int_data[i].push_back(ene_out_int_vec);
  particle_prod_a_data[i].push_back(ene_out_vec);
  particle_prod_a_distr_data[i].push_back(ene_out_distr_vec);
  particle_prod_a_distr_data_integ[i].push_back(ene_out_distr_integ_vec);
  
  vector<vector<Real> > kalbach_coef_a, kalbach_coef_b;
  if( angular_repr_flg == 2 )
  {
    //For Kalbach-Mann systematics
    set_particle_production_ene_data_by_ene_angle_data_continuum_calc_kalbach_data
      (i, k, react_no, ene_vec, ene_out_vec, kalbach_coef_a, kalbach_coef_b);
  }
  else
  {
    //Set dummy data to kalbach_coef
    //for set_particle_production_ene_data_by_ene_angle_data_continuum_calc_heat_data function.
    kalbach_coef_a.resize(l_max);
    kalbach_coef_b.resize(l_max);
    for(int l=0; l<l_max; l++)
    {
      int m_max = static_cast<int>(ene_out_vec[l].size());
      kalbach_coef_a[l].resize(m_max);
      kalbach_coef_b[l].resize(m_max);
      for(int m=0; m<m_max; m++)
      {
        kalbach_coef_a[l][m] = 0.0;
        kalbach_coef_b[l][m] = 0.0;
      }
    }
    
    if( ene_flg == 61 )
    {
      set_particle_production_ene_data_by_ene_angle_data_continuum_calc_mu_data
        (i, k, react_no, angular_repr_flg);
      particle_prod_ene_out_coef_a[i].push_back(kalbach_coef_a);
      particle_prod_ene_out_coef_b[i].push_back(kalbach_coef_b);
    }
    else
    {
      vector<vector<Real> > real_vec2;
      clr_obj.clear_vec_array2_real(real_vec2);
      particle_prod_ene_out_coef_a[i].push_back(real_vec2);
      particle_prod_ene_out_coef_b[i].push_back(real_vec2);

      set_particle_production_angle_data_add_void_data(i);
    }
  }
 
  set_particle_production_ene_data_by_ene_angle_data_continuum_calc_heat_data
    (i, k, pos, react_no, ene_vec, ene_out_vec, ene_out_distr_vec, kalbach_coef_a, kalbach_coef_b);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_particle_production_ene_data_by_ene_angle_data_continuum_set_ene_flg
                             (int i, int k, int react_no, Integer angular_repr_flg, Integer& ene_flg)
{
  Integer angle_no_flg = 1;
  vector<vector<vector<Real> > > cont_data
                                   = prod_distr_data_obj_vec[react_no].get_cont_data()[k];
  for(int l=0; l<static_cast<int>(cont_data.size()); l++)
  {
    for(int m=0; m<static_cast<int>(cont_data[l].size()); m++)
    {
      if( static_cast<int>(cont_data[l][m].size()) > 1 )
      {
        angle_no_flg = 0;
        break;
      }
    }

    if( angle_no_flg == 0 )
    {
      break;
    }
  }
  clr_obj.clear_vec_array3_real(cont_data);

  
  ene_flg = 0;
  if( angular_repr_flg == 1 )
  {
    if( angle_no_flg == 0 )
    {
      ene_flg = 61;
    }
    else if( angle_no_flg == 1 )
    {
      ene_flg = 4;
    }
  }
  else if( angular_repr_flg == 2 )
  {
    ene_flg = 44;
  }
  else if( angular_repr_flg >= 11 )
  {
    ene_flg = 61;
  }
  else
  {
    string func_name  = "set_particle_production_ene_data_by_ene_angle_data_continuum_set_ene_flg";
    ostringstream oss01, oss02, oss03;
    oss01 << prod_distr_data_obj_vec[react_no].get_reaction_type();
    oss02 << k;
    oss03 << angular_repr_flg;
    string str_data01 = "Reaction type              : " + oss01.str();
    string str_data02 = "Partial energy number      : " + oss02.str();
    string str_data03 = "Angular representation flg : " + oss03.str();
    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("This angular representation flg can not treat in this program.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
  particle_prod_ene_flg[i].push_back(ene_flg);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_particle_production_ene_data_by_ene_angle_data_continuum_set_base_data
                             (int i, int k, int react_no, vector<Real>& ene_vec)
{
  particle_prod_q_value[i].push_back(0.0);
  particle_prod_mass_coef[i].push_back(0.0);

  ene_vec = prod_distr_data_obj_vec[react_no].get_cont_ene_a()[k];

  int l_max = static_cast<int>(ene_vec.size());
  for(int l=0; l<l_max; l++)
  {
    ene_vec[l]  *= unit_micro;
  }

  vector<Real> ene_vec_tmp, prob_vec;
  ene_vec_tmp.resize(2);
  prob_vec.resize(2);
  ene_vec_tmp[0] = ene_vec[0];
  ene_vec_tmp[1] = ene_vec[l_max-1];
  prob_vec[0]    = 1.0;
  prob_vec[1]    = 1.0;
  particle_prod_ene_data[i].push_back(ene_vec_tmp);
  particle_prod_ene_prob_data[i].push_back(prob_vec);

  vector<Integer> int_vec, range_vec;
  int_vec.resize(1);
  range_vec.resize(1);
  prob_vec.resize(2);
  int_vec[0]   = int_lin_lin;
  range_vec[0] = 2;
  particle_prod_ene_int_data[i].push_back(int_vec);
  particle_prod_ene_range_data[i].push_back(range_vec);

  range_vec[0] = static_cast<Integer>(l_max);
  particle_prod_ene_in_int_data[i].push_back(int_vec);
  particle_prod_ene_in_range_data[i].push_back(range_vec);
  particle_prod_ene_in_data[i].push_back(ene_vec);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_particle_production_ene_data_by_ene_angle_data_continuum_calc_kalbach_data
                             (int i, int k, int react_no,
                              vector<Real>& ene_vec, vector<vector<Real> >& ene_out_vec,
                              vector<vector<Real> >& kalbach_coef_a, vector<vector<Real> >& kalbach_coef_b)
{
  ProductDistributionDataContainer prod_obj = prod_distr_data_obj_vec[react_no];

  //For Kalbach-Mann systematics
  Integer mat_data_product
            = static_cast<Integer>(round(prod_obj.get_mat_data_product()[k]));

  int l_max = static_cast<int>(ene_vec.size());
  kalbach_coef_a.resize(l_max);
  kalbach_coef_b.resize(l_max);
  for(int l=0; l<l_max; l++)
  {
    Real ene_in = ene_vec[l] * unit_mega;

    int m_max = static_cast<int>(ene_out_vec[l].size());
    kalbach_coef_a[l].resize(m_max);
    kalbach_coef_b[l].resize(m_max);
    for(int m=0; m<m_max; m++)
    {
      Real ene_out = ene_out_vec[l][m] * unit_mega;

      kalbach_coef_a[l][m] = prod_obj.get_cont_data()[k][l][m][1];

      if( static_cast<int>(prod_obj.get_cont_data()[k][l][m].size()) == 3 )
      {
        kalbach_coef_b[l][m] = prod_obj.get_cont_data()[k][l][m][2];
      }
      else
      {
        kalbach_coef_b[l][m] = calc_kalbach_mann_parameter(sub_lib_part, mat_data_product, ene_in, ene_out);
      }
    }
  }
  prod_obj.clear();

  particle_prod_ene_out_coef_a[i].push_back(kalbach_coef_a);
  particle_prod_ene_out_coef_b[i].push_back(kalbach_coef_b);

  vector<vector<Integer> >       mu_int_data;
  vector<vector<vector<Real> > > mu_data, mu_prob_data, mu_prob_data_integ;
  clr_obj.clear_vec_array2_int(mu_int_data);
  clr_obj.clear_vec_array3_real(mu_data);
  clr_obj.clear_vec_array3_real(mu_prob_data);
  clr_obj.clear_vec_array3_real(mu_prob_data_integ);
  particle_prod_b_int_data[i].push_back(mu_int_data);
  particle_prod_b_data[i].push_back(mu_data);
  particle_prod_b_prob_data[i].push_back(mu_prob_data);
  particle_prod_b_prob_data_integ[i].push_back(mu_prob_data_integ);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_particle_production_ene_data_by_ene_angle_data_continuum_calc_mu_data
                             (int i, int k, int react_no, Integer angular_repr_flg)
{
  string func_name  = "set_particle_production_ene_data_by_ene_angle_data_continuum_calc_mu_data";

  vector<vector<vector<Real> > > cont_data = prod_distr_data_obj_vec[react_no].get_cont_data()[k];
  
  vector<vector<Integer> >       mu_int_data;
  vector<vector<vector<Real> > > mu_data, mu_prob_data, mu_prob_data_integ;
  int l_max = static_cast<int>(cont_data.size());
  mu_int_data.resize(l_max);
  mu_data.resize(l_max);
  mu_prob_data.resize(l_max);
  mu_prob_data_integ.resize(l_max);
  for(int l=0; l<l_max; l++)
  {
    int m_max = static_cast<int>(cont_data[l].size());
    mu_int_data[l].resize(m_max);
    mu_data[l].resize(m_max);
    mu_prob_data[l].resize(m_max);
    mu_prob_data_integ[l].resize(m_max);
    for(int m=0; m<m_max; m++)
    {
      int n_max = static_cast<int>(cont_data[l][m].size()) - 1;
      if( angular_repr_flg == 1 )
      {
        //For Legendre polynomial
        mu_int_data[l][m] = int_lin_lin;

        vector<Real> list_data;
        list_data.resize(n_max);
        if( fabs(cont_data[l][m][0]) > min_value )
        {
          for(int n=0; n<n_max; n++)
          {
            list_data[n] = cont_data[l][m][n+1] / cont_data[l][m][0];
          }
        }
        //lin_tab_obj.check_legendre_polynomial_list_data
        //  (class_name, func_name, prod_distr_data_obj_vec[react_no].get_reaction_type(),
        //   i, k, l, m, list_data);
        lin_tab_obj.linearize_list_data_by_legendre_polynomial(list_data, mu_data[l][m], mu_prob_data[l][m]);
      }
      else
      {
        mu_int_data[l][m] = angular_repr_flg - 10;

        n_max /= 2;
        mu_data[l][m].resize(n_max);
        mu_prob_data[l][m].resize(n_max);
        int ele_no = 1;
        for(int n=0; n<n_max; n++)
        {
          mu_data[l][m][n]      = cont_data[l][m][ele_no];
          mu_prob_data[l][m][n] = cont_data[l][m][ele_no+1];
          ele_no+=2;
        }
      }

      Real sum = 0.0;
      integ_obj.integrate_for_ace_data
            (class_name, func_name, mu_data[l][m], mu_prob_data[l][m], mu_prob_data_integ[l][m],
                                    mu_int_data[l][m], sum);
    }
  }
  particle_prod_b_int_data[i].push_back(mu_int_data);
  particle_prod_b_data[i].push_back(mu_data);
  particle_prod_b_prob_data[i].push_back(mu_prob_data);
  particle_prod_b_prob_data_integ[i].push_back(mu_prob_data_integ);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_particle_production_ene_data_by_ene_angle_data_continuum_calc_heat_data
                             (int i, int k, int pos, int react_no, vector<Real>& ene_vec,
                              vector<vector<Real> >& ene_out_vec, vector<vector<Real> >& ene_out_distr_vec,
                              vector<vector<Real> >& kalbach_coef_a, vector<vector<Real> >& kalbach_coef_b)
                              
{
  ProductDistributionDataContainer prod_obj = prod_distr_data_obj_vec[react_no];

  Integer second_ene_int_data = prod_obj.get_second_ene_int_data()[k];

  //1.0E4 : m2/s -> cm2/s
  Real light_speed_coef = amu_n * amu * light_speed * light_speed * unit_micro * 1.0E4 / ev;
  Real mass_val         = nucl_data_obj.get_general_data_obj().get_mass();
  Real mass_projectile  = nucl_data_obj.get_general_data_obj().get_mass_projectile();
  Real mass_coef1       = prod_obj.get_mass_product()[k] * light_speed_coef;

  int l_max = static_cast<int>(ene_vec.size());
  vector<Real> distr_integ;
  distr_integ.resize(l_max);
  for(int l=0; l<l_max; l++)
  {
    Real mass_coef2 =  mass_projectile * sqrt(2.0 * ene_vec[l] / (light_speed_coef*mass_projectile))
                    / (mass_projectile + mass_val);

    int  m_max = static_cast<int>(ene_out_vec[l].size());
    Real ene_cur, ene_pre, ene_ave_cur, ene_ave_pre, ene_coef, ene_delta, distr_tmp;
    distr_integ[l] = 0.0;
    ene_pre        = ene_out_vec[l][0];
    ene_ave_pre    = 0.0;
    for(int m=1; m<m_max; m++)
    {
      ene_cur = ene_out_vec[l][m];

      int n_max = static_cast<int>(prod_obj.cont_data[k][l][m].size()) - 1;
      if( n_max == 0 )
      {
        ene_ave_cur = ene_cur;
      }
      else
      {
        ene_coef = sqrt(2.0*ene_cur / mass_coef1);

        Real fi1 = 4.0;
        Real fi2 = 0.0;
        if( fabs(kalbach_coef_b[l][m]) > min_value )
        {
          Real kalbach_val   = kalbach_coef_b[l][m];
          Real kalbach_exp_p = exp(kalbach_val);
          Real kalbach_exp_m = exp(-1.0*kalbach_val);
          fi1 = (kalbach_exp_p - kalbach_exp_m) / kalbach_val;
          fi2 = (kalbach_exp_p + kalbach_exp_m - fi1) / kalbach_val;
        }

        ene_ave_cur = mass_coef1 * ( 0.5*(ene_coef*ene_coef + mass_coef2*mass_coef2)
                                     + (kalbach_coef_a[l][m] * ene_coef*mass_coef2*fi2/fi1) );
      }
      ene_delta = ene_cur - ene_pre;

      if( second_ene_int_data == 1 )
      {
        distr_tmp = 0.5*(ene_ave_pre + ene_ave_cur) * ene_out_distr_vec[l][m-1];
      }
      else
      {
        distr_tmp = 0.5*(ene_ave_pre*ene_out_distr_vec[l][m-1] + ene_ave_cur*ene_out_distr_vec[l][m]);
      }
      distr_integ[l] += distr_tmp*ene_delta;

      ene_pre     = ene_cur;
      ene_ave_pre = ene_ave_cur;
    }
  }

  vector<Integer> product_distr_int_data, product_distr_range_data;
  vector<Real>    product_distr_ene_data, product_distr_data;
  product_distr_int_data   = prod_obj.get_product_distr_int_data()[k];
  product_distr_range_data = prod_obj.get_product_distr_range_data()[k];
  product_distr_ene_data   = prod_obj.get_product_distr_ene_data()[k];
  product_distr_data       = prod_obj.get_product_distr_data()[k];
  prod_obj.clear();

      l_max  = static_cast<int>(particle_prod_ene_no[i]);
  int ene_no = static_cast<int>(particle_prod_ene_sta[i] - 1);
  int ele_no = ene_no - react_type_ene_sta[pos];
  for(int l=0; l<l_max; l++)
  {
    if( ene_no >= react_type_ene_sta[pos] )
    {
      Real ene_val, h_val, y_val;
      ene_val = union_ene_grid[ene_no];
      ti_obj.interpolation_1d_in_range(int_lin_lin, ene_val, h_val, ene_vec, distr_integ);

      ene_val *= unit_mega;
      ti_obj.interpolation_tab1_in_range(ene_val, y_val, product_distr_range_data, product_distr_int_data,
                                                         product_distr_ene_data,   product_distr_data);
      particle_prod_heat[i][ene_no] += h_val*y_val*react_xs[pos][ele_no];
    }
    ene_no++;
    ele_no++;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_particle_production_ene_data_by_ene_angle_data_other
                             (int i, int j, int k, int pos, int react_no, Integer distr_func_flg)
{
  particle_prod_ene_flg[i].push_back(33);

  Real mass_val        = nucl_data_obj.get_general_data_obj().get_mass();
  Real mass_projectile = nucl_data_obj.get_general_data_obj().get_mass_projectile();
  Real mass_tmp        = prod_distr_data_obj_vec[react_no].get_mass_product()[k];
  Real mass_coef1      = mass_val / mass_projectile;
  Real mass_coef2      = mass_tmp / mass_projectile;
  Real q_val           = (1.0 + mass_coef1) * (-1.0 * react_q_value[pos]) / mass_coef1;
  Real mass_coef       = mass_coef1 * (mass_coef1 - mass_coef2 + 1.0)
                       / ((1.0 + mass_coef1) * (1.0 + mass_coef1));
  particle_prod_q_value[i].push_back(q_val);
  particle_prod_mass_coef[i].push_back(mass_coef);

  vector<Integer> int_vec, range_vec;
  vector<Real>    ene_vec, prob_vec;
  int_vec.resize(1);
  range_vec.resize(1);
  ene_vec.resize(2);
  prob_vec.resize(2);
  int_vec[0]   = int_lin_lin;
  range_vec[0] = static_cast<Integer>(ene_vec.size());
  particle_prod_ene_int_data[i].push_back(int_vec);
  particle_prod_ene_range_data[i].push_back(range_vec);

  if( distr_func_flg == 2 )
  {
    vector<Real> two_body_ene_data = prod_distr_data_obj_vec[react_no].get_two_body_ene_data()[k];
    int ene_no = static_cast<int>(two_body_ene_data.size());
    ene_vec[0]  = two_body_ene_data[0]          * unit_micro;
    ene_vec[1]  = two_body_ene_data[ene_no - 1] * unit_micro;
    prob_vec[0] = 1.0;
    prob_vec[1] = 1.0;
  }
  else if( distr_func_flg == 3 || distr_func_flg == 4 )
  {
    ene_vec[0]  = 0.0;
    ene_vec[1]  = 0.0;
    prob_vec[0] = 0.0;
    prob_vec[1] = 0.0;

    if( distr_func_flg == 3 )
    {
      int l_max  = static_cast<int>(particle_prod_ene_no[i]);
      int ene_no = static_cast<int>(particle_prod_ene_sta[i] - 1);
      int ele_no = ene_no - react_type_ene_sta[pos];
      for(int l=0; l<l_max; l++)
      {
        if( ene_no >= react_type_ene_sta[pos] )
        {
          particle_prod_heat[i][ene_no] += mass_coef * (union_ene_grid[ene_no] - q_val)
                                                     * react_xs[pos][ele_no];
        }
        ene_no++;
        ele_no++;
      }
    }
  }
  particle_prod_ene_data[i].push_back(ene_vec);
  particle_prod_ene_prob_data[i].push_back(prob_vec);

  set_particle_production_ene_data_add_void_data(i);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_particle_production_ene_data_by_ene_angle_data_phase_space
                             (int i, int j, int k, int pos, int react_no)
{
  particle_prod_ene_flg[i].push_back(66);

  Integer n_body_particle_no = prod_distr_data_obj_vec[react_no].get_n_body_particle_no()[k];
  Real    n_body_mass        = prod_distr_data_obj_vec[react_no].get_n_body_mass()[k];
  particle_prod_q_value[i].push_back(n_body_particle_no);
  particle_prod_mass_coef[i].push_back(n_body_mass);

  vector<Integer> int_vec, range_vec;
  vector<Real>    ene_vec, prob_vec;
  int_vec.resize(1);
  range_vec.resize(1);
  ene_vec.resize(2);
  prob_vec.resize(2);
  int_vec[0]   = int_lin_lin;
  range_vec[0] = static_cast<Integer>(ene_vec.size());
  ene_vec[0]   = 0.0;
  ene_vec[1]   = 0.0;
  prob_vec[0]  = 0.0;
  prob_vec[1]  = 0.0;
  particle_prod_ene_int_data[i].push_back(int_vec);
  particle_prod_ene_range_data[i].push_back(range_vec);
  particle_prod_ene_data[i].push_back(ene_vec);
  particle_prod_ene_prob_data[i].push_back(prob_vec);

  vector<Integer>       ene_out_int_data;
  vector<vector<Real> > ene_out_data, ene_out_distr_data, ene_out_distr_data_integ;
  ene_out_int_data.resize(1);
  ene_out_data.resize(1);
  ene_out_distr_data.resize(1);
  ene_out_distr_data_integ.resize(1);
  ene_out_int_data[0] = int_lin_lin;

  calc_n_body_phase_space_distr_data(n_body_particle_no, ene_out_data[0], ene_out_distr_data[0],
                                                                          ene_out_distr_data_integ[0]);

  particle_prod_a_int_data[i].push_back(ene_out_int_data);
  particle_prod_a_data[i].push_back(ene_out_data);
  particle_prod_a_distr_data[i].push_back(ene_out_distr_data);
  particle_prod_a_distr_data_integ[i].push_back(ene_out_distr_data_integ);

  //Set dummy data to Kalbach coef and mu data
  vector<vector<Integer> >       int_vec2;
  vector<vector<Real> >          real_vec2;
  vector<vector<vector<Real> > > real_vec3;

  clr_obj.clear_vec_array2_int(int_vec2);
  clr_obj.clear_vec_array2_real(real_vec2);
  clr_obj.clear_vec_array3_real(real_vec3);

  particle_prod_ene_out_coef_a[i].push_back(real_vec2);
  particle_prod_ene_out_coef_b[i].push_back(real_vec2);
  particle_prod_b_int_data[i].push_back(int_vec2);
  particle_prod_b_data[i].push_back(real_vec3);
  particle_prod_b_prob_data[i].push_back(real_vec3);
  particle_prod_b_prob_data_integ[i].push_back(real_vec3);

  set_particle_production_ene_data_by_ene_angle_data_phase_space_calc_heat_data
    (i, j, k, pos, react_no, n_body_mass, ene_out_data[0], ene_out_distr_data[0]);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_particle_production_ene_data_by_ene_angle_data_phase_space_calc_heat_data
                             (int i, int j, int k, int pos, int react_no, Real& n_body_mass,
                              vector<Real>& x_vec, vector<Real>& y_vec)
{
  vector<Integer> product_distr_int_data, product_distr_range_data;
  vector<Real>    product_distr_ene_data, product_distr_data;
  product_distr_int_data   = prod_distr_data_obj_vec[react_no].get_product_distr_int_data()[k];
  product_distr_range_data = prod_distr_data_obj_vec[react_no].get_product_distr_range_data()[k];
  product_distr_ene_data   = prod_distr_data_obj_vec[react_no].get_product_distr_ene_data()[k];
  product_distr_data       = prod_distr_data_obj_vec[react_no].get_product_distr_data()[k];

  Real mass_val        = nucl_data_obj.get_general_data_obj().get_mass();
  Real mass_projectile = nucl_data_obj.get_general_data_obj().get_mass_projectile();
  Real mass_tmp        = prod_distr_data_obj_vec[react_no].get_mass_product()[k];
  Real mass_coef_inv   = 1.0 / (mass_val + mass_projectile);
  Real mass_coef1      = (mass_projectile * mass_tmp) * mass_coef_inv * mass_coef_inv;
  Real mass_coef2      = mass_val * mass_coef_inv;
  Real mass_coef3      = (n_body_mass - mass_tmp) / n_body_mass;

  int l_max  = static_cast<int>(particle_prod_ene_no[i]);
  int n_max  = static_cast<int>(x_vec.size());
  int ene_no = static_cast<int>(particle_prod_ene_sta[i] - 1);
  int ele_no = ene_no - react_type_ene_sta[pos];

  Real sum_pre       = 0.0;
  Real check_val_pre = 0.0;
  for(int l=0; l<l_max; l++)
  {
    if( ene_no >= react_type_ene_sta[pos] )
    {
      Real delta_mu       =  0.2;
      Real mu_val         = -1.0;
      Real ene_val        = union_ene_grid[ene_no];
      Real ene_coef1      =  ene_val * mass_coef1;
      Real ene_coef2      = (ene_val * mass_coef2 + react_q_value[pos]) * mass_coef3;
      Real ene_coef1_root = sqrt(ene_coef1);
      Real ene_coef2_inv  = 1.0 / ene_coef2;
      Real h_val          = 0.0;
      Real h_val_mod      = 0.0;
      for(int m=0; m<11; m++)
      {
        Real mu_sq         = mu_val*mu_val;
        Real e_val1_pre    = 0.0;
        Real e_val2_pre    = 0.0;
        Real prob_val1_pre = 0.0;
        Real prob_val2_pre = 0.0;
        Real sum           = 0.0;
        Real check_val     = 0.0;
        for(int n=0; n<n_max; n++)
        {
          Real x_tmp = x_vec[n] * ene_coef2;
          Real y_tmp = y_vec[n] * ene_coef2_inv;

          Real disc = x_tmp - ene_coef1 * (1.0 - mu_sq);
          if( disc >= 0.0 )
          {
            Real disc_sq  = sqrt(disc);
            Real mu_coef1 = mu_val * ene_coef1_root + disc_sq;
            Real mu_coef2 = mu_val * ene_coef1_root - disc_sq;
            Real e_val1   = mu_coef1*mu_coef1;
            Real e_val2   = mu_coef2*mu_coef2;
            if( mu_coef2 < 0.0 )
            {
              e_val2 *= -1.0;
            }

            Real prob_val1 = 0.0;
            Real prob_val2 = 0.0;
            if( x_tmp > 0.0 )
            {
              prob_val1 = y_tmp*fabs(mu_coef1) / sqrt(x_tmp);
              if( mu_coef2 > 0.0 )
              {
                prob_val2 = y_tmp*mu_coef2 / sqrt(x_tmp);
              }
            }

            if( e_val1_pre >= min_value )
            {
              Real e_val1_delta = fabs(e_val1 - e_val1_pre);
              sum       += 0.5 * e_val1_delta * (e_val1*prob_val1 + e_val1_pre*prob_val1_pre);
              check_val += 0.5 * e_val1_delta * (       prob_val1 +            prob_val1_pre);
              if( e_val2 > 0.0 && e_val2_pre > 0.0 )
              {
                Real e_val2_delta = fabs(e_val2 - e_val2_pre);
                sum       += 0.5 * e_val2_delta * (e_val2*prob_val2 + e_val2_pre*prob_val2_pre);
                check_val += 0.5 * e_val2_delta * (       prob_val2 +            prob_val2_pre);
              }
            }
            e_val1_pre    = e_val1;
            e_val2_pre    = e_val2;
            prob_val1_pre = prob_val1;
            prob_val2_pre = prob_val2;
          }
        }

        if( m > 0 )
        {
          h_val     += 0.1 * (sum       + sum_pre);
          h_val_mod += 0.1 * (check_val + check_val_pre);
        }
        sum_pre       = sum;
        check_val_pre = check_val;
        mu_val += delta_mu;
      }

      if( h_val_mod > 0.0 )
      {
        h_val /= h_val_mod;
      }

      Real y_val    = 0.0;
           ene_val *= unit_mega;
      ti_obj.interpolation_tab1_in_range(ene_val, y_val, product_distr_range_data, product_distr_int_data,
                                                         product_distr_ene_data,   product_distr_data);
      particle_prod_heat[i][ene_no] += h_val*y_val*react_xs[pos][ele_no];
    }
    ene_no++;
    ele_no++;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_particle_production_ene_data_by_ene_angle_data_lab
                             (int i, int j, int k, int pos, int react_no)
{
  string func_name  = "set_particle_production_ene_data_by_ene_angle_data_lab";

  ProductDistributionDataContainer prod_obj = prod_distr_data_obj_vec[react_no];

  particle_prod_ene_flg[i].push_back(67);

  vector<Real> ene_vec = prod_obj.get_lab_ene()[k];
  int l_max = static_cast<int>(ene_vec.size());
  vector<Real> prob_vec;
  prob_vec.resize(l_max);
  for(int l=0; l<l_max; l++)
  {
    ene_vec[l]  *= unit_micro;
    prob_vec[l]  = -1.0;
  }
  particle_prod_ene_data[i].push_back(ene_vec);
  particle_prod_ene_prob_data[i].push_back(prob_vec);

  vector<Integer> int_vec, range_vec;
  int_vec.resize(1);
  range_vec.resize(1);
  prob_vec.resize(2);
  int_vec[0]   = int_lin_lin;
  range_vec[0] = static_cast<Integer>(l_max);
  particle_prod_ene_int_data[i].push_back(int_vec);
  particle_prod_ene_range_data[i].push_back(range_vec);

  vector<Integer>                mu_int_data;
  vector<vector<Real> >          mu_data, mu_distr_data, ene_out_prob_data_sum;
  vector<vector<Integer> >       ene_out_int_data;
  vector<vector<vector<Real> > > ene_out_data, ene_out_prob_data, ene_out_prob_data_integ;
  mu_data           = prod_obj.get_lab_cos()[k];
  ene_out_data      = prod_obj.get_lab_ene_sec_data()[k];
  ene_out_prob_data = prod_obj.get_lab_data()[k];

  vector<int> pos_data1, pos_data2;
  pos_data1.resize(2);
  pos_data2.resize(3);
  pos_data1[0] = k;
  pos_data2[0] = k;
  Integer reaction_type = prod_obj.get_reaction_type();

  mu_int_data.resize(l_max);
  mu_distr_data.resize(l_max);
  ene_out_int_data.resize(l_max);
  ene_out_prob_data_integ.resize(l_max);
  ene_out_prob_data_sum.resize(l_max);
  for(int l=0; l<l_max; l++)
  {
    pos_data1[1] = l;
    pos_data2[1] = l;
    int_vec     = prod_obj.get_lab_cos_int_data()[k][l];
    range_vec   = prod_obj.get_lab_cos_range_data()[k][l];
    mu_int_data[l] = integ_obj.check_interpolation(class_name, func_name, reaction_type, pos_data1,
                                                   range_vec, int_vec);

    int m_max = static_cast<int>(mu_data[l].size());
    mu_distr_data[l].resize(m_max);
    ene_out_int_data[l].resize(m_max);
    ene_out_prob_data_integ[l].resize(m_max);
    ene_out_prob_data_sum[l].resize(m_max);
    for(int m=0; m<m_max; m++)
    {
      mu_distr_data[l][m] = -1.0;

      pos_data2[2]           = m;
      int_vec                = prod_obj.get_lab_int_data()[k][l][m];
      range_vec              = prod_obj.get_lab_range_data()[k][l][m];
      ene_out_int_data[l][m] = integ_obj.check_interpolation(class_name, func_name, reaction_type,
                                                             pos_data2, range_vec, int_vec);
      int  n_max = static_cast<int>(ene_out_data[l][m].size());
      for(int n=0; n<n_max; n++)
      {
        ene_out_data[l][m][n]      *= unit_micro;
        ene_out_prob_data[l][m][n] *= unit_mega;
      }

      ene_out_prob_data_sum[l][m] = 0.0;
      Integer int_val = ene_out_int_data[l][m];
      integ_obj.integrate_for_ace_data(class_name, func_name, ene_out_data[l][m], ene_out_prob_data[l][m],
                                       ene_out_prob_data_integ[l][m], int_val, ene_out_prob_data_sum[l][m]);
      for(int n=0; n<n_max; n++)
      {
        ene_out_data[l][m][n]      *= unit_micro;
        ene_out_prob_data[l][m][n] *= unit_mega;
      }
    }
  }
  prod_obj.clear();

  particle_prod_a_int_data[i].push_back(mu_int_data);
  particle_prod_a_data[i].push_back(mu_data);
  particle_prod_a_distr_data[i].push_back(mu_distr_data);
  particle_prod_b_int_data[i].push_back(ene_out_int_data);
  particle_prod_b_data[i].push_back(ene_out_data);
  particle_prod_b_prob_data[i].push_back(ene_out_prob_data);
  particle_prod_b_prob_data_integ[i].push_back(ene_out_prob_data_integ);

  //Set dummy data to Kalbach coef and mu data
  vector<vector<Real> > real_vec2;
  clr_obj.clear_vec_array2_real(real_vec2);
  particle_prod_a_distr_data_integ[i].push_back(real_vec2);
  particle_prod_ene_out_coef_a[i].push_back(real_vec2);
  particle_prod_ene_out_coef_b[i].push_back(real_vec2);

  set_particle_production_ene_data_by_ene_angle_data_lab_calc_heat_data
    (i, j, k, pos, react_no, ene_out_int_data);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_particle_production_ene_data_by_ene_angle_data_lab_calc_heat_data
                             (int i, int j, int k, int pos, int react_no, vector<vector<Integer> >& int_vec)
{
  vector<Integer>                product_distr_int_data, product_distr_range_data;
  vector<Real>                   product_distr_ene_data, product_distr_data;
  vector<Real>                   ene_vec, y_vec;
  vector<vector<Integer> >       lab_int_data, lab_range_data;
  vector<vector<Real> >          lab_cos_data, lab_data, cos_data, sum_ene_ave;
  vector<vector<vector<Real> > > ene_out_data, ene_out_prob_data;

  product_distr_int_data   = prod_distr_data_obj_vec[react_no].get_product_distr_int_data()[k];
  product_distr_range_data = prod_distr_data_obj_vec[react_no].get_product_distr_range_data()[k];
  product_distr_ene_data   = prod_distr_data_obj_vec[react_no].get_product_distr_ene_data()[k];
  product_distr_data       = prod_distr_data_obj_vec[react_no].get_product_distr_data()[k];

  ene_vec           = prod_distr_data_obj_vec[react_no].get_lab_ene()[k];
  lab_int_data      = prod_distr_data_obj_vec[react_no].get_lab_integrate_int_data()[k];
  lab_range_data    = prod_distr_data_obj_vec[react_no].get_lab_integrate_range_data()[k];
  lab_cos_data      = prod_distr_data_obj_vec[react_no].get_lab_integrate_cos_data()[k];
  lab_data          = prod_distr_data_obj_vec[react_no].get_lab_integrate_data()[k];
  cos_data          = prod_distr_data_obj_vec[react_no].get_lab_cos()[k];
  ene_out_data      = prod_distr_data_obj_vec[react_no].get_lab_ene_sec_data()[k];
  ene_out_prob_data = prod_distr_data_obj_vec[react_no].get_lab_data()[k];

  //For incident energy loop
  int l_max = static_cast<int>(ene_out_data.size());
  y_vec.resize(l_max);
  sum_ene_ave.resize(l_max);
  for(int l=0; l<l_max; l++)
  {
    Real ene_ave_integ_val = 0.0;

    //For angle (mu) loop
    int m_max = static_cast<int>(ene_out_data[l].size());
    sum_ene_ave[l].resize(m_max);
    for(int m=0; m<m_max; m++)
    {
      //For second energy loop
      int n_max = static_cast<int>(ene_out_data[l][m].size());
      for(int n=0; n<n_max; n++)
      {
        ene_out_data[l][m][n]      *= unit_micro;
        ene_out_prob_data[l][m][n] *= unit_mega;
      }

      sum_ene_ave[l][m] = 0.0;
      if( int_vec[l][m] == int_const )
      {
        for(int n=1; n<n_max; n++)
        {
          sum_ene_ave[l][m] += 0.5 * ene_out_prob_data[l][m][n-1]
                                   * (ene_out_data[l][m][n] - ene_out_data[l][m][n-1])
                                   * (ene_out_data[l][m][n] + ene_out_data[l][m][n-1]);
        }
      }
      else if( int_vec[l][m] == int_lin_lin )
      {
        for(int n=1; n<n_max; n++)
        {
          sum_ene_ave[l][m] += 0.5 * (ene_out_prob_data[l][m][n-1]*ene_out_data[l][m][n-1]
                                        + ene_out_prob_data[l][m][n]*ene_out_data[l][m][n])
                                   * (ene_out_data[l][m][n] - ene_out_data[l][m][n-1]);
        }
      }
      else
      {
        string func_name  = "set_particle_production_ene_data_by_ene_angle_data_continuum";
        ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07;
        oss01 << i+1;
        oss02 << j+1;
        oss03 << k+1;
        oss04 << l+1;
        oss05 << m+1;
        oss06 << prod_distr_data_obj_vec[react_no].get_reaction_type();
        oss07 << int_vec[l][m];
        string str_data01 = "Position           : " + oss01.str() + ", " + oss02.str() + ", "
                                                    + oss03.str() + ", " + oss04.str() + ", "
                                                    + oss05.str();
        string str_data02 = "Reaction type      : " + oss06.str();
        string str_data03 = "Interpolation type : " + oss07.str();
        vector<string> err_com;
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back("This interpolation type is not available.");
        err_com.push_back("Available interpolation type is constant and linear-linear.");
        err_obj.output_runtime_error(class_name, func_name, err_com);
      }

      Real lab_integ_val = 0.0;
      ti_obj.interpolation_tab1_in_range(cos_data[l][m], lab_integ_val,
                                         lab_range_data[l], lab_int_data[l], lab_cos_data[l], lab_data[l]);
      sum_ene_ave[l][m] *= lab_integ_val;

      if( m > 0 )
      {
        ene_ave_integ_val += 0.5 * (cos_data[l][m] - cos_data[l][m-1])
                                 * (sum_ene_ave[l][m] + sum_ene_ave[l][m-1]);
      }
    }

    Real y_val = 0.0;
    ti_obj.interpolation_tab1_in_range(ene_vec[l], y_val, product_distr_range_data, product_distr_int_data,
                                                          product_distr_ene_data,   product_distr_data);
    ene_vec[l] *= unit_micro;
    y_vec[l]    = y_val * ene_ave_integ_val * unit_micro;
  }

      l_max  = static_cast<int>(particle_prod_ene_no[i]);
  int ene_no = static_cast<int>(particle_prod_ene_sta[i] - 1);
  int ele_no = 0;
  for(int l=0; l<l_max; l++)
  {
    if( ene_no >= react_type_ene_sta[pos] )
    {
      Real h_val   = 0.0;
      Real ene_val = union_ene_grid[ene_no] * unit_mega;
      ti_obj.interpolation_1d_in_range(int_lin_lin, ene_val, h_val, ene_vec, y_vec);
      particle_prod_heat[i][ene_no] += h_val * react_xs[pos][ele_no];
    }
    ene_no++;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_particle_production_ene_data_add_void_data(int i)
{
  vector<Integer>                int_vec1;
  vector<vector<Integer> >       int_vec2;
  vector<Real>                   real_vec1;
  vector<vector<Real> >          real_vec2;
  vector<vector<vector<Real> > > real_vec3;

  int_vec1.clear();
  real_vec1.clear();
  clr_obj.clear_vec_array2_int(int_vec2);
  clr_obj.clear_vec_array2_real(real_vec2);
  clr_obj.clear_vec_array3_real(real_vec3);

  //For distr_func_flg = 1 : second energy, distr_func_flg = 7 : angle (mu)
  particle_prod_ene_in_int_data[i].push_back(int_vec1);
  particle_prod_ene_in_range_data[i].push_back(int_vec1);
  particle_prod_ene_in_data[i].push_back(real_vec1);
  particle_prod_a_int_data[i].push_back(int_vec1);
  particle_prod_a_data[i].push_back(real_vec2);
  particle_prod_a_distr_data[i].push_back(real_vec2);
  particle_prod_a_distr_data_integ[i].push_back(real_vec2);
  particle_prod_ene_out_coef_a[i].push_back(real_vec2);
  particle_prod_ene_out_coef_b[i].push_back(real_vec2);

  //For distr_func_flg = 1 : second energy, distr_func_flg = 7 : angle (mu)
  set_particle_production_angle_data_add_void_data(i);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_particle_production_angle_data_add_void_data(int i)
{
  vector<vector<Integer> >       int_vec2;
  vector<vector<vector<Real> > > real_vec3;

  clr_obj.clear_vec_array2_int(int_vec2);
  clr_obj.clear_vec_array3_real(real_vec3);

  //For distr_func_flg = 1 : second energy, distr_func_flg = 7 : angle (mu)
  particle_prod_b_int_data[i].push_back(int_vec2);
  particle_prod_b_data[i].push_back(real_vec3);
  particle_prod_b_prob_data[i].push_back(real_vec3);
  particle_prod_b_prob_data_integ[i].push_back(real_vec3);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::mod_particle_prod_heat(int i, Integer particle_prod_val)
{
  int ene_sta = static_cast<int>(particle_prod_ene_sta[i] - 1);
  int ene_no  = ene_sta;
  int j_max   = static_cast<int>(particle_prod_ene_no[i]);

  vector<Real> xs_vec_new, heat_vec_new;
  xs_vec_new.resize(j_max);
  heat_vec_new.resize(j_max);
  for(int j=0; j<j_max; j++)
  {
    if( fabs(react_xs_tot[ene_no]) > min_value )
    {
      particle_prod_heat[i][ene_no] /= react_xs_tot[ene_no];
    }

    if( particle_prod_heat[i][ene_no] < min_ene_dif )
    {
      particle_prod_heat[i][ene_no] = 0.0;
    }
    else if( particle_prod_val == 1 )
    {
      particle_prod_heat[i][ene_no] = 0.0;
    }

    if( sub_lib_part > 1 )
    {
      react_xs_heat[ene_no] += particle_prod_heat[i][ene_no];
    }

    //Remove unnecessary zero data from particle_prod_xs and particle_prod_heat
    xs_vec_new[j]   = particle_prod_xs[i][ene_no];
    heat_vec_new[j] = particle_prod_heat[i][ene_no];
    ene_no++;
  }

  particle_prod_xs[i]   = xs_vec_new;
  particle_prod_heat[i] = heat_vec_new;
  xs_vec_new.clear();
  heat_vec_new.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_charged_particle_production()
{
  int i_max = static_cast<int>(prod_distr_data_obj_vec.size());
  for(int i=0; i<i_max; i++)
  {
    Integer reaction_type = prod_distr_data_obj_vec[i].get_reaction_type();
    if( reaction_type <= 2 )
    {
      continue;
    }

    int j_max = static_cast<int>(react_type_list.size());
    int pos   = -1;
    for(int j=0; j<j_max; j++)
    {
      if( reaction_type == react_type_list[j] )
      {
        pos = j;
        break;
      }
    }

    vector<Integer> distr_func_flg   = prod_distr_data_obj_vec[i].get_distr_func_flg();
    vector<Real>    mat_data_product = prod_distr_data_obj_vec[i].get_mat_data_product();

    j_max = static_cast<int>(distr_func_flg.size());
    for(int j=0; j<j_max; j++)
    {
      if( static_cast<int>(round(mat_data_product[j])) <= 2004 )
      {
        continue;
      }

      if( distr_func_flg[j] == 1 )
      {
        set_charged_particle_production_continuum(i, j, pos);
      }
      else if( distr_func_flg[j] == 4 )
      {
        set_charged_particle_production_two_body_recoil(i, j, pos);
      }
      else
      {
        string func_name = "set_charged_particle_production()";

        ostringstream oss01, oss02, oss03, oss04, oss05;
        oss01 << reaction_type;
        oss02 << j+1;
        oss03 << j_max;
        oss04 << distr_func_flg[j];
        oss04 << mat_data_product[j];
        string str_data01 = "Reaction type         : " + oss01.str();
        string str_data02 = "Position              : " + oss02.str() + " / " + oss03.str();
        string str_data03 = "Distribution function : " + oss04.str();
        string str_data04 = "Product identifier    : " + oss05.str();

        vector<string> err_com;
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back(str_data04);
        if( distr_func_flg[j] == 0 )
        {
          err_com.push_back("There is no heating information for recoil particle.");
          err_obj.output_caution(class_name, func_name, err_com);
        }
        else if( distr_func_flg[j] == 6 )
        {
          err_com.push_back("This distribution function is neglected for recoil particle.");
          err_obj.output_caution(class_name, func_name, err_com);
        }
        else
        {
          err_com.push_back("This distribution function is not available in this program.");
          err_com.push_back("The available distribution function is 0, 1, 4 and 6.");
          err_obj.output_runtime_error(class_name, func_name, err_com);
        }
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_charged_particle_production_continuum(int i, int j, int pos)
{
  vector<Integer>                product_distr_int_data, product_distr_range_data;
  vector<Real>                   product_distr_ene_data, product_distr_data, cont_ene_in;
  vector<vector<Real> >          cont_ene_out;
  vector<vector<vector<Real> > > cont_data;
  product_distr_int_data   = prod_distr_data_obj_vec[i].get_product_distr_int_data()[j];
  product_distr_range_data = prod_distr_data_obj_vec[i].get_product_distr_range_data()[j];
  product_distr_ene_data   = prod_distr_data_obj_vec[i].get_product_distr_ene_data()[j];
  product_distr_data       = prod_distr_data_obj_vec[i].get_product_distr_data()[j];
  cont_ene_in              = prod_distr_data_obj_vec[i].get_cont_ene_a()[j];
  cont_ene_out             = prod_distr_data_obj_vec[i].get_cont_ene_b()[j];
  cont_data                = prod_distr_data_obj_vec[i].get_cont_data()[j];

  vector<Real> y_vec;
  int k_max = static_cast<int>(cont_ene_in.size());
  y_vec.resize(k_max);
  for(int k=0; k<k_max; k++)
  {
    ti_obj.interpolation_tab1_in_range
      (cont_ene_in[k], y_vec[k], product_distr_range_data, product_distr_int_data,
                                 product_distr_ene_data,   product_distr_data);

    int  l_max = static_cast<int>(cont_ene_out[k].size());
    Real h_val = 0.0;
    for(int l=1; l<l_max; l++)
    {
      int m_max = static_cast<int>(cont_data[k][l].size());
      if( m_max != 1 )
      {
        string func_name = "set_charged_particle_production_continuum(int i, int j, int pos)";
        ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07;
        oss01 << prod_distr_data_obj_vec[i].get_reaction_type();
        oss02 << j+1;
        oss03 << k+1;
        oss04 << k_max;
        oss05 << l+1;
        oss06 << l_max;
        oss07 << m_max;
        string str_data01 = "Reaction type           : " + oss01.str();
        string str_data02 = "Position                : " + oss02.str() + ", "
                                                         + oss03.str() + " / " + oss04.str() + ", "
                                                         + oss05.str() + " / " + oss06.str() + ", ";
        string str_data03 = "Data number of b(E, E') : " + oss07.str();
        vector<string> err_com;
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_obj.output_runtime_error(class_name, func_name, err_com);
      }

      h_val += 0.5 * cont_data[k][l-1][0] * (cont_ene_out[k][l] - cont_ene_out[k][l-1])
                                          * (cont_ene_out[k][l] + cont_ene_out[k][l-1]);
    }
    y_vec[k] *= h_val;
  }


      k_max  = static_cast<int>(union_ene_grid.size());
  int ele_no = 0;
  for(int k=react_type_ene_sta[pos]-1; k<k_max; k++)
  {
    Real ene_val = union_ene_grid[k] * unit_mega;
    Real h_val   = 0.0;

    ti_obj.interpolation_1d_in_range(int_lin_lin, ene_val, h_val, cont_ene_in, y_vec);
    react_xs_heat[k] += h_val * unit_micro * react_xs[pos][ele_no] / react_xs_tot[k];
    ele_no++;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::set_charged_particle_production_two_body_recoil(int i, int j, int pos)
{
  vector<Real>          two_body_ene_data, y_vec;
  vector<vector<Real> > two_body_legendre_coef;
  two_body_ene_data      = prod_distr_data_obj_vec[i].get_two_body_ene_data()[j]; 
  two_body_legendre_coef = prod_distr_data_obj_vec[i].get_two_body_legendre_coef()[j];

  int  ene_no_max      = static_cast<int>(union_ene_grid.size());
  Real q_val           = react_q_value[pos];
  Real mass_val        = nucl_data_obj.get_general_data_obj().get_mass();
  Real mass_projectile = nucl_data_obj.get_general_data_obj().get_mass_projectile();
  Real mass_tmp        = prod_distr_data_obj_vec[i].get_mass_product()[j];
  Real mass_coef1      = mass_val / mass_projectile;
  Real mass_coef2      = mass_tmp / mass_projectile;

  Real q_coef   = q_val * (1.0 + mass_coef1) / mass_coef1;
  Real r_val1   = (1.0 + mass_coef1 - mass_coef2) * mass_coef1 / mass_coef2;
  Real r_val2   = (1.0 + mass_coef1 - mass_coef2) / ((1.0 + mass_coef1) * (1.0 + mass_coef1));
  Real beta_val = r_val1 * (1.0 + q_coef/union_ene_grid[ene_no_max-1]);
  if( beta_val < min_value )
  {
    beta_val = 0.0;
  }
  Real gam_val  = mass_coef2 / (1.0 + mass_coef1 - mass_coef2);
       gam_val  = gam_val*gam_val * beta_val;
  Real gam_root = sqrt(gam_val);

  int k_max = static_cast<int>(two_body_ene_data.size());
  y_vec.resize(k_max);
  for(int k=0; k<k_max; k++)
  {
    y_vec[k] = two_body_ene_data[k] * r_val2
             * (gam_val + 1.0 - 2.0*two_body_legendre_coef[k][0]*gam_root);
  }
  
  int ele_no = 0;
  for(int k=react_type_ene_sta[pos]-1; k<ene_no_max; k++)
  {
    Real ene_val = union_ene_grid[k] * unit_mega;
    Real h_val   = 0.0;

    ti_obj.interpolation_1d_in_range(int_lin_lin, ene_val, h_val, two_body_ene_data, y_vec);
    react_xs_heat[k] += h_val * unit_micro * react_xs[pos][ele_no] / react_xs_tot[k];
    ele_no++;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::check_set_data()
{
  string func_name  = "check_set_data()";

  if( nucl_data_set_flg == 0 )
  {
    vector<string> err_com;
    err_com.push_back("The NuclearDataObject data is not set.");
    err_com.push_back("Please set the NuclearDataObject data using set_nucl_data_obj() function.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  Real temp_ref = nucl_data_obj.get_general_data_obj().get_temp();
  if( temp_set_flg > 0 )
  {
    Real temp_dif = (temp - temp_ref);
    if( temp_ref > min_value )
    {
      temp_dif /= temp_ref;
    }

    if( fabs(temp_dif) > 1.0E-5 )
    {
      ostringstream oss01, oss02;
      oss01 << temp;
      oss02 << temp_ref;

      string str_data01 = "Set temperature data                  : " + oss01.str();
      string str_data02 = "Temperature data in NuclearDataObject : " + oss02.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);

      if( fabs(temp_dif) > 1.0E-2 )
      {
        err_com.push_back("The set temperature data is not identical to temperature in NuclearDataObject.");
        err_com.push_back("Please check the set temperature data or NuclearDataObject data.");
        err_obj.output_runtime_error(class_name, func_name, err_com);
      }
      else
      {
        err_com.push_back("The difference between set temp. data and NuclearDataObject's temp.");
        err_com.push_back("is not larger than 1.0E-5.");
        err_com.push_back("The set temperature data may not be appropriate.");
        err_obj.output_caution(class_name, func_name, err_com);
      }
    }
  }
  else
  {
    ostringstream oss01;
    oss01 << temp_ref;
    string str_data01 = "Temperature data in NuclearDataObject : " + oss01.str();
    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("The temperature data is not set.");
    err_com.push_back("Please check the temperature data in the nuclear data object is appropriate or not.");
    err_obj.output_caution(class_name, func_name, err_com);
  }

  Integer mat_ref = nucl_data_obj.get_general_data_obj().get_mat_no();
  if( mat_set_flg > 0 )
  {
    if( mat != mat_ref )
    {
      ostringstream oss01, oss02;
      oss01 << mat;
      oss02 << mat_ref;

      string str_data01 = "Set material number                  : " + oss01.str();
      string str_data02 = "Material number in NuclearDataObject : " + oss02.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back("The set material number is not identical to that in NuclearDataObject.");
      err_com.push_back("Please check the set material number or NuclearDataObject data.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }
  else
  {
    ostringstream oss01;
    oss01 << mat_ref;
    string str_data01 = "Material number in NuclearDataObject : " + oss01.str();
    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("The material number is not set.");
    err_com.push_back("Please check the material number in the nuclear data object is appropriate or not.");
    err_obj.output_caution(class_name, func_name, err_com);
  }

  if( new_cummulative_angle_distr_flg != 0 && new_cummulative_angle_distr_flg != 1 )
  {
    ostringstream oss01;
    oss01 << new_cummulative_angle_distr_flg;

    string str_data01 = "New cummulative angle distribution option : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("The new cummulative angle distribution option is only available for");
    err_com.push_back("0 (no) or 1 (yes).");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  if( detailed_photon_flg != 0 && detailed_photon_flg != 1 )
  {
    ostringstream oss01;
    oss01 << detailed_photon_flg;

    string str_data01 = "Detailed photon option : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("The detailed photon option is only available for");
    err_com.push_back("0 (no) or 1 (yes).");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  if( static_cast<int>(thinning_ene.size()) > thinning_ene_no + 1 )
  {
    ostringstream oss01;
    oss01 << static_cast<int>(thinning_ene.size());

    string str_data01 = "Number of thinning energy data : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("The number of thinning nergy data must be less than or equal to 3.");
    err_com.push_back("Please check the number of thinning energy data or set thinning_ene data.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
  else if( static_cast<int>(thinning_ene.size()) != thinning_ene_no )
  {
    for(int i=0; i<thinning_ene_no - static_cast<int>(thinning_ene.size()); i++)
    {
      thinning_ene.push_back(0.0);
    }
  }

  func_name.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::calc_ace_header_file_data()
{
  aw0 = nucl_data_obj.get_general_data_obj().get_mass();
  tz  = nucl_data_obj.get_general_data_obj().get_temp() * boltzmann_const * unit_micro;

  izaid = nucl_data_obj.get_general_data_obj().get_izaid_ace();

  set_title_data();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::copy_fast_ace_data(FastAceDataObject& ace_data_obj)
{
  ace_data_obj.clear();

  //For calc data
  ace_data_obj.set_sub_lib_part(sub_lib_part);
  ace_data_obj.set_sub_lib_type(sub_lib_type);
  ace_data_obj.set_ene_max(ene_max);

  ace_data_obj.set_zi_vec(zi_vec);
  ace_data_obj.set_awr_vec(awr_vec);

  ace_data_obj.set_union_ene_grid(union_ene_grid);
  ace_data_obj.set_gamma_product_xs(gamma_product_xs);

  ace_data_obj.set_particle_production_data(particle_production_data);
  ace_data_obj.set_particle_production_ene_data(particle_production_ene_data);

  ace_data_obj.set_photon_prod_yield_coef_direct(photon_prod_yield_coef_direct);
  ace_data_obj.set_photon_prod_yield_coef_given(photon_prod_yield_coef_given);

  ace_data_obj.set_photon_xs_ene_min(photon_xs_ene_min);
  ace_data_obj.set_photon_prod_discon_ene_data(photon_prod_discon_ene_data);

  //For ace data
  copy_fast_ace_base_data(ace_data_obj);
  copy_fast_ace_ene_angular_distr_data(ace_data_obj);
  copy_fast_ace_prod_distr_data(ace_data_obj);
  copy_fast_ace_photon_data(ace_data_obj);
  copy_fast_ace_particle_data(ace_data_obj);
  copy_fast_ace_pointer_data(ace_data_obj);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::copy_fast_ace_base_data(FastAceDataObject& ace_data_obj)
{
  ace_data_obj.set_mcnpx_mode_flg(mcnpx_mode_flg);

  ace_data_obj.set_aw0(aw0);
  ace_data_obj.set_tz(tz);
  ace_data_obj.set_izaid(izaid);
  ace_data_obj.set_title_data(title_data);
  ace_data_obj.set_discriptive_data(discriptive_data);

  ace_data_obj.set_ntr(ntr);
  ace_data_obj.set_nr(nr);
  ace_data_obj.set_mtntr(mtntr);
  ace_data_obj.set_mtnr(mtnr);

  ace_data_obj.set_nu_bar_repr_flg(nu_bar_repr_flg);
  ace_data_obj.set_nu_d_bar_repr_flg(nu_d_bar_repr_flg);
  ace_data_obj.set_nu_p_bar_repr_flg(nu_p_bar_repr_flg);

  ace_data_obj.set_nu_int_data(nu_int_data);
  ace_data_obj.set_nu_range_data(nu_range_data);
  ace_data_obj.set_nu_d_int_data(nu_d_int_data);
  ace_data_obj.set_nu_d_range_data(nu_d_range_data);
  ace_data_obj.set_nu_p_int_data(nu_p_int_data);
  ace_data_obj.set_nu_p_range_data(nu_p_range_data);

  ace_data_obj.set_nu_data(nu_data);
  ace_data_obj.set_nu_ene_data(nu_ene_data);
  ace_data_obj.set_nu_d_data(nu_d_data);
  ace_data_obj.set_nu_d_ene_data(nu_d_ene_data);
  ace_data_obj.set_nu_p_data(nu_p_data);
  ace_data_obj.set_nu_p_ene_data(nu_p_ene_data);

  ace_data_obj.set_react_type_list(react_type_list);
  ace_data_obj.set_react_type_flg(react_type_flg);
  ace_data_obj.set_react_type_ene_sta(react_type_ene_sta);
  ace_data_obj.set_react_q_value(react_q_value);
  ace_data_obj.set_react_xs_tot(react_xs_tot);
  ace_data_obj.set_react_xs_cap(react_xs_cap);
  ace_data_obj.set_react_xs_sc(react_xs_sc);
  ace_data_obj.set_react_xs_heat(react_xs_heat);
  ace_data_obj.set_react_xs(react_xs);

  ace_data_obj.set_unreso_prob_tab_int_data(unreso_prob_tab_int_data);
  ace_data_obj.set_unreso_prob_tab_inela_comp_flg(unreso_prob_tab_inela_comp_flg);
  ace_data_obj.set_unreso_prob_tab_abs_comp_flg(unreso_prob_tab_abs_comp_flg);
  ace_data_obj.set_unreso_prob_tab_self_shielding_flg(unreso_prob_tab_self_shielding_flg);

  ace_data_obj.set_unreso_prob_tab_ene(unreso_prob_tab_ene);
  ace_data_obj.set_unreso_prob_tab_heat(unreso_prob_tab_heat);
  ace_data_obj.set_unreso_prob_tab_sample_no(unreso_prob_tab_sample_no);
  ace_data_obj.set_unreso_prob_tab_table(unreso_prob_tab_table);

  ace_data_obj.set_nu_d_decay_constant(nu_d_decay_constant);
  ace_data_obj.set_nu_d_ene_min(nu_d_ene_min);
  ace_data_obj.set_nu_d_ene_max(nu_d_ene_max);
  ace_data_obj.set_nu_d_xs_part_int_data(nu_d_xs_part_int_data);
  ace_data_obj.set_nu_d_xs_part_range_data(nu_d_xs_part_range_data);
  ace_data_obj.set_nu_d_xs_part_ene_data(nu_d_xs_part_ene_data);
  ace_data_obj.set_nu_d_xs_part_data(nu_d_xs_part_data);
  ace_data_obj.set_nu_d_ene_in_int_data(nu_d_ene_in_int_data);
  ace_data_obj.set_nu_d_ene_in_range_data(nu_d_ene_in_range_data);
  ace_data_obj.set_nu_d_ene_out_int_data(nu_d_ene_out_int_data);
  ace_data_obj.set_nu_d_ene_in_data(nu_d_ene_in_data);
  ace_data_obj.set_nu_d_ene_out_data(nu_d_ene_out_data);
  ace_data_obj.set_nu_d_ene_distr_data(nu_d_ene_distr_data);
  ace_data_obj.set_nu_d_ene_distr_data_integ(nu_d_ene_distr_data_integ);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::copy_fast_ace_ene_angular_distr_data(FastAceDataObject& ace_data_obj)
{
  ace_data_obj.set_angular_distr_type_flg(angular_distr_type_flg);

  ace_data_obj.set_angular_distr_int_data(angular_distr_int_data);
  ace_data_obj.set_angular_distr_ene_data(angular_distr_ene_data);
  ace_data_obj.set_angular_distr_cos_data(angular_distr_cos_data);
  ace_data_obj.set_angular_distr_data(angular_distr_data);
  ace_data_obj.set_angular_distr_data_integ(angular_distr_data_integ);

  ace_data_obj.set_ene_distr_ene_repr_flg(ene_distr_ene_repr_flg);
  ace_data_obj.set_ene_distr_xs_part_int_data(ene_distr_xs_part_int_data);
  ace_data_obj.set_ene_distr_xs_part_range_data(ene_distr_xs_part_range_data);
  ace_data_obj.set_ene_distr_xs_part_ene_data(ene_distr_xs_part_ene_data);
  ace_data_obj.set_ene_distr_xs_part_data(ene_distr_xs_part_data);
  ace_data_obj.set_ene_distr_q_coef(ene_distr_q_coef);
  ace_data_obj.set_ene_distr_mass_coef(ene_distr_mass_coef);
  ace_data_obj.set_ene_distr_ene_in_int_data(ene_distr_ene_in_int_data);
  ace_data_obj.set_ene_distr_ene_in_range_data(ene_distr_ene_in_range_data);
  ace_data_obj.set_ene_distr_ene_in_data(ene_distr_ene_in_data);
  ace_data_obj.set_ene_distr_ene_out_int_data(ene_distr_ene_out_int_data);
  ace_data_obj.set_ene_distr_ene_out_ene_data(ene_distr_ene_out_ene_data);
  ace_data_obj.set_ene_distr_ene_out_data(ene_distr_ene_out_data);
  ace_data_obj.set_ene_distr_ene_out_data_integ(ene_distr_ene_out_data_integ);
  ace_data_obj.set_ene_distr_upper_ene_limit(ene_distr_upper_ene_limit);
  ace_data_obj.set_ene_distr_temp_eff_int_data(ene_distr_temp_eff_int_data);
  ace_data_obj.set_ene_distr_temp_eff_range_data(ene_distr_temp_eff_range_data);
  ace_data_obj.set_ene_distr_watt_a_int_data(ene_distr_watt_a_int_data);
  ace_data_obj.set_ene_distr_watt_a_range_data(ene_distr_watt_a_range_data);
  ace_data_obj.set_ene_distr_watt_b_int_data(ene_distr_watt_b_int_data);
  ace_data_obj.set_ene_distr_watt_b_range_data(ene_distr_watt_b_range_data);
  ace_data_obj.set_ene_distr_temp_eff_ene_data(ene_distr_temp_eff_ene_data);
  ace_data_obj.set_ene_distr_temp_eff_data(ene_distr_temp_eff_data);
  ace_data_obj.set_ene_distr_watt_a_ene_data(ene_distr_watt_a_ene_data);
  ace_data_obj.set_ene_distr_watt_a_data(ene_distr_watt_a_data);
  ace_data_obj.set_ene_distr_watt_b_ene_data(ene_distr_watt_b_ene_data);
  ace_data_obj.set_ene_distr_watt_b_data(ene_distr_watt_b_data);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::copy_fast_ace_prod_distr_data(FastAceDataObject& ace_data_obj)
{
  ace_data_obj.set_prod_yield_tot_int_data(prod_yield_tot_int_data);
  ace_data_obj.set_prod_yield_tot_range_data(prod_yield_tot_range_data);
  ace_data_obj.set_prod_yield_tot_ene_data(prod_yield_tot_ene_data);
  ace_data_obj.set_prod_yield_tot_data(prod_yield_tot_data);
  ace_data_obj.set_prod_distr_func_flg(prod_distr_func_flg);
  ace_data_obj.set_prod_distr_n_body_mass(prod_distr_n_body_mass);
  ace_data_obj.set_prod_distr_prob_data_no(prod_distr_prob_data_no);
  ace_data_obj.set_prod_distr_n_body_particle_no(prod_distr_n_body_particle_no);
  ace_data_obj.set_prod_distr_prob_ene_in_int_data(prod_distr_prob_ene_in_int_data);
  ace_data_obj.set_prod_distr_prob_ene_in_range_data(prod_distr_prob_ene_in_range_data);
  ace_data_obj.set_prod_distr_prob_ene_out_int_data(prod_distr_prob_ene_out_int_data);
  ace_data_obj.set_prod_distr_prob_ene_in_data(prod_distr_prob_ene_in_data);
  ace_data_obj.set_prod_distr_prob_mu_int_data(prod_distr_prob_mu_int_data);
  ace_data_obj.set_prod_distr_prob_mu_range_data(prod_distr_prob_mu_range_data);
  ace_data_obj.set_prod_distr_prob_mu_data(prod_distr_prob_mu_data);
  ace_data_obj.set_prod_distr_prob_mu_data_integ(prod_distr_prob_mu_data_integ);
  ace_data_obj.set_prod_distr_prob_data(prod_distr_prob_data);
  ace_data_obj.set_prod_distr_prob_data_integ(prod_distr_prob_data_integ);
  ace_data_obj.set_prod_distr_prob_ene_out_data(prod_distr_prob_ene_out_data);
  ace_data_obj.set_prod_distr_prob_coef_a(prod_distr_prob_coef_a);
  ace_data_obj.set_prod_distr_prob_coef_b(prod_distr_prob_coef_b);
  ace_data_obj.set_prod_distr_prob_int_vec(prod_distr_prob_int_vec);
  ace_data_obj.set_prod_distr_prob_range_vec(prod_distr_prob_range_vec);
  ace_data_obj.set_prod_distr_prob_mu_vec(prod_distr_prob_mu_vec);
  ace_data_obj.set_prod_distr_prob_ene_out_vec(prod_distr_prob_ene_out_vec);
  ace_data_obj.set_prod_distr_prob_vec(prod_distr_prob_vec);
  ace_data_obj.set_prod_distr_prob_vec_integ(prod_distr_prob_vec_integ);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::copy_fast_ace_photon_data(FastAceDataObject& ace_data_obj)
{
  ace_data_obj.set_photon_prod_file_no(photon_prod_file_no);
  ace_data_obj.set_photon_prod_reaction_type(photon_prod_reaction_type);
  ace_data_obj.set_photon_prod_reaction_type_without_xs(photon_prod_reaction_type_without_xs);
  ace_data_obj.set_photon_prod_reaction_type_all(photon_prod_reaction_type_all);
  ace_data_obj.set_photon_prod_binding_ene(photon_prod_binding_ene);
  ace_data_obj.set_photon_prod_multiplicity_int_data(photon_prod_multiplicity_int_data);
  ace_data_obj.set_photon_prod_multiplicity_range_data(photon_prod_multiplicity_range_data);
  ace_data_obj.set_photon_prod_multiplicity_ene_data(photon_prod_multiplicity_ene_data);
  ace_data_obj.set_photon_prod_multiplicity_data(photon_prod_multiplicity_data);
  ace_data_obj.set_photon_prod_xs_ene_no(photon_prod_xs_ene_no);
  ace_data_obj.set_photon_prod_xs_non_zero_pos(photon_prod_xs_non_zero_pos);
  ace_data_obj.set_photon_prod_xs_data(photon_prod_xs_data);
  ace_data_obj.set_photon_prod_distr_int_data(photon_prod_distr_int_data);
  ace_data_obj.set_photon_prod_distr_range_data(photon_prod_distr_range_data);
  ace_data_obj.set_photon_prod_distr_ene_data(photon_prod_distr_ene_data);
  ace_data_obj.set_photon_prod_distr_data(photon_prod_distr_data);

  ace_data_obj.set_photon_angular_distr_ene_data(photon_angular_distr_ene_data);
  ace_data_obj.set_photon_angular_distr_prob_cos_data(photon_angular_distr_prob_cos_data);

  ace_data_obj.set_photon_energy_distr_flg(photon_energy_distr_flg);
  ace_data_obj.set_photon_energy_distr_ene_flg(photon_energy_distr_ene_flg);
  ace_data_obj.set_photon_energy_distr_binding_ene_data(photon_energy_distr_binding_ene_data);
  ace_data_obj.set_photon_energy_distr_int_data(photon_energy_distr_int_data);
  ace_data_obj.set_photon_energy_distr_range_data(photon_energy_distr_range_data);
  ace_data_obj.set_photon_energy_distr_ene_data(photon_energy_distr_ene_data);
  ace_data_obj.set_photon_energy_distr_prob_data(photon_energy_distr_prob_data);
  ace_data_obj.set_photon_energy_distr_ene_in_int_data(photon_energy_distr_ene_in_int_data);
  ace_data_obj.set_photon_energy_distr_ene_in_range_data(photon_energy_distr_ene_in_range_data);
  ace_data_obj.set_photon_energy_distr_ene_in_data(photon_energy_distr_ene_in_data);
  ace_data_obj.set_photon_energy_distr_weight_int_data(photon_energy_distr_weight_int_data);
  ace_data_obj.set_photon_energy_distr_weight_ene_data(photon_energy_distr_weight_ene_data);
  ace_data_obj.set_photon_energy_distr_weight_data(photon_energy_distr_weight_data);
  ace_data_obj.set_photon_energy_distr_weight_data_integ(photon_energy_distr_weight_data_integ);
  ace_data_obj.set_photon_energy_distr_gamma_mass_product(photon_energy_distr_gamma_mass_product);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::copy_fast_ace_particle_data(FastAceDataObject& ace_data_obj)
{
  ace_data_obj.set_particle_prod_flg(particle_prod_flg);
  ace_data_obj.set_particle_prod_count(particle_prod_count);
  ace_data_obj.set_particle_prod_ene_sta(particle_prod_ene_sta);
  ace_data_obj.set_particle_prod_ene_no(particle_prod_ene_no);
  ace_data_obj.set_particle_prod_file_no(particle_prod_file_no);
  ace_data_obj.set_particle_prod_frame_flg(particle_prod_frame_flg);
  ace_data_obj.set_particle_prod_reaction_type(particle_prod_reaction_type);
  ace_data_obj.set_particle_prod_reaction_type_all(particle_prod_reaction_type_all);
  ace_data_obj.set_particle_prod_xs(particle_prod_xs);
  ace_data_obj.set_particle_prod_heat(particle_prod_heat);
  ace_data_obj.set_particle_prod_distr_int_data(particle_prod_distr_int_data);
  ace_data_obj.set_particle_prod_distr_range_data(particle_prod_distr_range_data);
  ace_data_obj.set_particle_prod_distr_ene_data(particle_prod_distr_ene_data);
  ace_data_obj.set_particle_prod_distr_data(particle_prod_distr_data);
  ace_data_obj.set_particle_prod_angular_int_data(particle_prod_angular_int_data);
  ace_data_obj.set_particle_prod_angular_ene_data(particle_prod_angular_ene_data);
  ace_data_obj.set_particle_prod_angular_cos_data(particle_prod_angular_cos_data);
  ace_data_obj.set_particle_prod_angular_distr_data(particle_prod_angular_distr_data);
  ace_data_obj.set_particle_prod_angular_distr_data_integ(particle_prod_angular_distr_data_integ);

  ace_data_obj.set_particle_prod_ene_flg(particle_prod_ene_flg);
  ace_data_obj.set_particle_prod_q_value(particle_prod_q_value);
  ace_data_obj.set_particle_prod_mass_coef(particle_prod_mass_coef);
  ace_data_obj.set_particle_prod_ene_int_data(particle_prod_ene_int_data);
  ace_data_obj.set_particle_prod_ene_range_data(particle_prod_ene_range_data);
  ace_data_obj.set_particle_prod_ene_data(particle_prod_ene_data);
  ace_data_obj.set_particle_prod_ene_prob_data(particle_prod_ene_prob_data);

  ace_data_obj.set_particle_prod_ene_in_int_data(particle_prod_ene_in_int_data);
  ace_data_obj.set_particle_prod_ene_in_range_data(particle_prod_ene_in_range_data);
  ace_data_obj.set_particle_prod_ene_in_data(particle_prod_ene_in_data);
  ace_data_obj.set_particle_prod_a_int_data(particle_prod_a_int_data);
  ace_data_obj.set_particle_prod_a_data(particle_prod_a_data);
  ace_data_obj.set_particle_prod_a_distr_data(particle_prod_a_distr_data);
  ace_data_obj.set_particle_prod_a_distr_data_integ(particle_prod_a_distr_data_integ);
  ace_data_obj.set_particle_prod_ene_out_coef_a(particle_prod_ene_out_coef_a);
  ace_data_obj.set_particle_prod_ene_out_coef_b(particle_prod_ene_out_coef_b);

  ace_data_obj.set_particle_prod_b_int_data(particle_prod_b_int_data);
  ace_data_obj.set_particle_prod_b_data(particle_prod_b_data);
  ace_data_obj.set_particle_prod_b_prob_data(particle_prod_b_prob_data);
  ace_data_obj.set_particle_prod_b_prob_data_integ(particle_prod_b_prob_data_integ);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataGenerator::copy_fast_ace_pointer_data(FastAceDataObject& ace_data_obj)
{
  ace_data_obj.set_len2(len2);
  ace_data_obj.set_nes(nes);
  ace_data_obj.set_ntrp(ntrp);
  ace_data_obj.set_ntype(ntype);
  ace_data_obj.set_ndnf(ndnf);
  ace_data_obj.set_esz(esz);
  ace_data_obj.set_nu(nu);
  ace_data_obj.set_mtr(mtr);
  ace_data_obj.set_lqr(lqr);
  ace_data_obj.set_tyr(tyr);
  ace_data_obj.set_lsig(lsig);
  ace_data_obj.set_sig(sig);
  ace_data_obj.set_land(land);
  ace_data_obj.set_andi(andi);
  ace_data_obj.set_ldlw(ldlw);
  ace_data_obj.set_dlw(dlw);
  ace_data_obj.set_gpd(gpd);
  ace_data_obj.set_mtrp(mtrp);
  ace_data_obj.set_lsigp(lsigp);
  ace_data_obj.set_sigp(sigp);
  ace_data_obj.set_landp(landp);
  ace_data_obj.set_andp(andp);
  ace_data_obj.set_ldlwp(ldlwp);
  ace_data_obj.set_dlwp(dlwp);
  ace_data_obj.set_yp(yp);
  ace_data_obj.set_fis(fis);
  ace_data_obj.set_endi(endi);
  ace_data_obj.set_iurpt(iurpt);
  ace_data_obj.set_nud(nud);
  ace_data_obj.set_dndat(dndat);
  ace_data_obj.set_ldnd(ldnd);
  ace_data_obj.set_dnd(dnd);
  ace_data_obj.set_ptype(ptype);
  ace_data_obj.set_ntro(ntro);
  ace_data_obj.set_ploct(ploct);

  ace_data_obj.set_ene_distr_pointer(ene_distr_pointer);
  ace_data_obj.set_nu_d_pointer(nu_d_pointer);
  ace_data_obj.set_photon_prod_pointer(photon_prod_pointer);
  ace_data_obj.set_photon_angular_pointer(photon_angular_pointer);
  ace_data_obj.set_photon_ene_pointer(photon_ene_pointer);
  ace_data_obj.set_photon_ene_distr_pointer(photon_ene_distr_pointer);

  ace_data_obj.set_angular_distr_pointer(angular_distr_pointer);
  ace_data_obj.set_ene_distr_ene_repr_end_pointer(ene_distr_ene_repr_end_pointer);
  ace_data_obj.set_ene_distr_ene_repr_pointer(ene_distr_ene_repr_pointer);
  ace_data_obj.set_nu_d_ene_in_pointer(nu_d_ene_in_pointer);
  ace_data_obj.set_photon_angular_ene_pointer(photon_angular_ene_pointer);
  ace_data_obj.set_photon_ene_weight_pointer(photon_ene_weight_pointer);
  ace_data_obj.set_particle_prod_pointer(particle_prod_pointer);
  ace_data_obj.set_particle_prod_distr_pointer(particle_prod_distr_pointer);
  ace_data_obj.set_particle_prod_angular_pointer(particle_prod_angular_pointer);
  ace_data_obj.set_particle_prod_ene_pointer(particle_prod_ene_pointer);
  ace_data_obj.set_particle_prod_ene_in_pointer(particle_prod_ene_in_pointer);
  ace_data_obj.set_ene_distr_ene_in_pointer(ene_distr_ene_in_pointer);
  ace_data_obj.set_particle_prod_angular_ene_pointer(particle_prod_angular_ene_pointer);
  ace_data_obj.set_particle_prod_a_pointer(particle_prod_a_pointer);
  ace_data_obj.set_ene_distr_ene_out_pointer(ene_distr_ene_out_pointer);
  ace_data_obj.set_particle_prod_b_pointer(particle_prod_b_pointer);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//Setter

void FastAceDataGenerator::set_nucl_data_obj(NuclearDataObject& data_obj)
{
  gen_fast_data_flg = 0;
  nucl_data_set_flg = 1;
  nucl_data_obj     = data_obj;
}

void FastAceDataGenerator::set_mat(Integer int_val)
{
  gen_fast_data_flg = 0;
  mat_set_flg       = 1;
  mat               = int_val;
}

void FastAceDataGenerator::set_temp(Real real_val)
{
  gen_fast_data_flg = 0;
  temp_set_flg      = 1;
  temp              = real_val;
}

void FastAceDataGenerator::set_new_cummulative_angle_distr_flg(Integer int_val)
{
  gen_fast_data_flg               = 0;
  new_cummulative_angle_distr_flg = int_val;  
}

void FastAceDataGenerator::set_detailed_photon_flg(Integer int_val)
{
  gen_fast_data_flg   = 0;
  detailed_photon_flg = int_val;
}

void FastAceDataGenerator::set_thinning_ene(vector<Real> real_vec)
{
  gen_fast_data_flg = 0;
  thinning_ene      = real_vec;
  thinning_ene.clear();
}

void FastAceDataGenerator::set_suffix_za_id(Real real_val)
{
  gen_fast_data_flg = 0;
  suffix_za_id      = real_val;
}

void FastAceDataGenerator::set_zi_awr_pair( vector<Integer> int_vec_zi,
                                            vector<Real>    real_vec_awr )
{ 
  if( static_cast<int>(int_vec_zi.size()) != static_cast<int>(real_vec_awr.size()) )
  {
    string func_name  = "set_zi_awr_pair(vector<Integer> int_vec_zi, vector<Real> real_vec_awr)";

    ostringstream oss01, oss02;
    oss01 << static_cast<int>(int_vec_zi.size());
    oss02 << static_cast<int>(real_vec_awr.size());

    string str_data01 = "Number of zi  array data : " + oss01.str();
    string str_data02 = "Number of awr array data : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("Number of zi array data and that of awr array data is not identical.");
    err_com.push_back("Please check the set data.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  int i_max = static_cast<int>(int_vec_zi.size());
  if( i_max > max_zi_awr_pair_no )
  {
    string func_name  = "set_zi_awr_pair(vector<Integer> int_vec_zi, vector<Real> real_vec_awr)";

    ostringstream oss01;
    oss01 << i_max;
    string str_data01 = "Number of zi and awr pair data : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    for(int i=0; i<i_max; i++)
    {
      ostringstream oss02, oss03, oss04;
      oss02 << i+1;
      oss03 << int_vec_zi[i];
      oss04 << real_vec_awr[i];
      string str_data02 = "  zi and awr data at " + oss02.str() + " / " + oss01.str() + " : "
                        + oss03.str() + ", " + oss04.str();
      if( i >= max_zi_awr_pair_no )
      {
        str_data02 = str_data02 + " * not used";
      }
      err_com.push_back(str_data02);
    }
    ostringstream oss05;
    oss05 << max_zi_awr_pair_no;
    string str_data03 = "Zi and awr data array must be less than or equal to " + oss05.str() + ".";
    err_com.push_back("So, some data in zi and awr pair is not used.");
    err_obj.output_caution(class_name, func_name, err_com);
  }

  zi_vec  = int_vec_zi;
  awr_vec = real_vec_awr;

  int_vec_zi.clear();
  real_vec_awr.clear();
}

void FastAceDataGenerator::set_mcnpx_mode_flg(Integer int_val)
{
  gen_fast_data_flg = 0;
  mcnpx_mode_flg    = int_val;
}

void FastAceDataGenerator::set_discriptive_data(string str_data)
{
  gen_fast_data_flg = 0;
  discriptive_data  = str_data;
  str_data.clear();
}

void FastAceDataGenerator::set_generate_mode_flg(int int_val)
{
  int generate_mode_flg_old = generate_mode_flg;

  gen_fast_data_flg = 0;
  generate_mode_flg = int_val;

  if( generate_mode_flg != generate_default_mode && generate_mode_flg != generate_njoy_mode )
  {
    string func_name = "set_generate_mode_flg(int int_val)";
    ostringstream oss01;
    oss01 << generate_mode_flg;
    string str_data01 = "The generate_mode_flg : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("This generate_mode_flg is not available.");
    err_com.push_back("The generate_mode_flg is only available for generate_default_mode (0) or");
    err_com.push_back("generate_njoy_mode (1).");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
  else if( generate_mode_flg != generate_mode_flg_old )
  {
    string gen_mode_str     = "generate_default_mode";
    string gen_mode_str_old = "generate_default_mode";
    if( generate_mode_flg == generate_njoy_mode )
    {
      gen_mode_str = "generate_njoy_mode";
    }
    if( generate_mode_flg_old == generate_njoy_mode )
    {
      gen_mode_str_old = "generate_njoy_mode";
    }

    string func_name = "set_generate_mode_flg(int int_val)";
    ostringstream oss01;
    oss01 << generate_mode_flg;
    string str_data01 = "The generate_mode_flg is changed from " + gen_mode_str_old + " to " + gen_mode_str;

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_obj.output_caution(class_name, func_name, err_com);
  }

  integ_obj.set_generate_mode_flg(generate_mode_flg);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//Getter
FastAceDataObject FastAceDataGenerator::get_ace_data_obj()
{
  generate_ace_data();

  FastAceDataObject ace_data_obj;
  copy_fast_ace_data(ace_data_obj);

  return ace_data_obj;
}

NuclearDataObject FastAceDataGenerator::get_nucl_data_obj()
{
  return nucl_data_obj;
}

Integer           FastAceDataGenerator::get_mat()
{
  return mat;
}

Real              FastAceDataGenerator::get_temp()
{
  return temp;
}

Integer           FastAceDataGenerator::get_new_cummulative_angle_distr_flg()
{
  return new_cummulative_angle_distr_flg;
}

Integer           FastAceDataGenerator::get_detailed_photon_flg()
{
  return detailed_photon_flg;
}

vector<Real>      FastAceDataGenerator::get_thinning_ene()
{
  return thinning_ene;
}

Real              FastAceDataGenerator::get_suffix_za_id()
{
  return suffix_za_id;
}

vector<Integer>   FastAceDataGenerator::get_zi_vec()
{
  return zi_vec;
}

vector<Real>      FastAceDataGenerator::get_awr_vec()
{
  return awr_vec;
}

Integer           FastAceDataGenerator::get_mcnpx_mode_flg()
{
  return mcnpx_mode_flg;
}

string            FastAceDataGenerator::get_discriptive_data()
{
  return discriptive_data;
}

int               FastAceDataGenerator::get_generate_mode_flg()
{
  return generate_mode_flg;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

