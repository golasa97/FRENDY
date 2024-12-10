#include "ContinuousEnergyXSUtils/AceDataParser/FastAceDataParser.hpp"

using namespace frendy;

//constructor
FastAceDataParser::FastAceDataParser(void)
{ 
  clear();
}

//destructor
FastAceDataParser::~FastAceDataParser(void)
{
  clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataParser::clear()
{
  ace_read_obj.clear();
  set_data_flg = 0;

  file_name.clear();

  clear_calc_data();
  clear_ace_data();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataParser::clear_calc_data()
{
  mcnpx_mode_flg = 0;

  sub_lib_part   = 0;
  sub_lib_type   = 0;
  ene_max        = 0.0;

  zi_vec.clear();
  awr_vec.clear();

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

void FastAceDataParser::clear_ace_data()
{
  clear_ace_base_data();
  clear_ace_ene_angular_distr_data();
  clear_ace_prod_distr_data();
  clear_ace_photon_data();
  clear_ace_particle_data();

  clear_ace_pointer_data();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataParser::clear_ace_base_data()
{
  aw0   = 0.0;
  tz    = 0.0;
  izaid = 0;
  clr_obj.clear_vec_array1_str(title_data);
  discriptive_data.clear();

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

void FastAceDataParser::clear_ace_ene_angular_distr_data()
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

void FastAceDataParser::clear_ace_prod_distr_data()
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

void FastAceDataParser::clear_ace_photon_data()
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

void FastAceDataParser::clear_ace_particle_data()
{
  particle_prod_flg.clear();
  particle_prod_count.clear();
  particle_prod_ene_sta.clear();
  particle_prod_ene_no.clear();
  clr_obj.clear_vec_array2_int(particle_prod_file_no);
  clr_obj.clear_vec_array2_int(particle_prod_frame_flg);
  clr_obj.clear_vec_array2_int(particle_prod_reaction_type);
  clr_obj.clear_vec_array2_int(particle_prod_reaction_type_all);
  clr_obj.clear_vec_array2_real(particle_prod_xs);
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

void FastAceDataParser::clear_ace_pointer_data()
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

void FastAceDataParser::copy_fast_ace_data(FastAceDataObject& ace_data_obj)
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

void FastAceDataParser::copy_fast_ace_base_data(FastAceDataObject& ace_data_obj)
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

void FastAceDataParser::copy_fast_ace_ene_angular_distr_data(FastAceDataObject& ace_data_obj)
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

void FastAceDataParser::copy_fast_ace_prod_distr_data(FastAceDataObject& ace_data_obj)
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

void FastAceDataParser::copy_fast_ace_photon_data(FastAceDataObject& ace_data_obj)
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

void FastAceDataParser::copy_fast_ace_particle_data(FastAceDataObject& ace_data_obj)
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

void FastAceDataParser::copy_fast_ace_pointer_data(FastAceDataObject& ace_data_obj)
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

void FastAceDataParser::parse_ace_format()
{
  if( set_data_flg != 0 )
  {
    return;
  }
  set_data_flg = 1;

  //cout << endl;
  //cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
  //cout << endl;
  //cout << "File name : " << file_name << endl;
  //cout << endl;
  //cout << "parse_ace_format_header" << endl;

  parse_ace_format_header();
  parse_ace_format_base_data();
  parse_ace_format_angular_distribution_data();
  parse_ace_format_energy_distribution_data();
  parse_ace_format_unreso_prob_table_data();
  parse_ace_format_nu_d_data();
  parse_ace_format_gamma_production_xs();
  parse_ace_format_photon_production_data();
  parse_ace_format_photon_energy_distr_data();
  parse_ace_format_particle_production_data();

  //cout << endl;
  //cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
  //cout << endl;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataParser::parse_ace_format_header()
{
  //cout << "parse_ace_format_header" << endl;
  //cout << "parse_ace_format_header : " << ace_read_obj.get_line_no() << endl;
  ace_read_obj.get_title_data(mcnpx_mode_flg, aw0, tz, discriptive_data, title_data);

  ace_read_obj.get_mat_data(zi_vec, awr_vec);

  int nxsd_no = 8;
  int jxsd_no = 2;
  nxsd.resize(nxsd_no);
  jxsd.resize(jxsd_no);

  int         pointer_data_no = 38 + nxsd_no + jxsd_no; //=48
  vector<int> pointer_vec;
  ace_read_obj.get_pointer_data(pointer_data_no, pointer_vec);

  len2  = pointer_vec[0];
  izaid = pointer_vec[1];
  nes   = pointer_vec[2];
  ntr   = pointer_vec[3];
  nr    = pointer_vec[4];
  ntrp  = pointer_vec[5];
  ntype = pointer_vec[6];
  ndnf  = pointer_vec[7];

  int ele_no = 8;
  for(int i=0; i<nxsd_no; i++)
  {
    nxsd[i] = pointer_vec[ele_no];
    ele_no++;
  }

  esz   = pointer_vec[ele_no];
  nu    = pointer_vec[ele_no+ 1];
  mtr   = pointer_vec[ele_no+ 2];
  lqr   = pointer_vec[ele_no+ 3];
  tyr   = pointer_vec[ele_no+ 4];
  lsig  = pointer_vec[ele_no+ 5];
  sig   = pointer_vec[ele_no+ 6];
  land  = pointer_vec[ele_no+ 7];
  andi  = pointer_vec[ele_no+ 8];
  ldlw  = pointer_vec[ele_no+ 9];
  dlw   = pointer_vec[ele_no+10];
  gpd   = pointer_vec[ele_no+11];
  mtrp  = pointer_vec[ele_no+12];
  lsigp = pointer_vec[ele_no+13];
  sigp  = pointer_vec[ele_no+14];
  landp = pointer_vec[ele_no+15];
  andp  = pointer_vec[ele_no+16];
  ldlwp = pointer_vec[ele_no+17];
  dlwp  = pointer_vec[ele_no+18];
  yp    = pointer_vec[ele_no+19];
  fis   = pointer_vec[ele_no+20];
  endi  = pointer_vec[ele_no+21];
  iurpt = pointer_vec[ele_no+22];
  nud   = pointer_vec[ele_no+23];
  dndat = pointer_vec[ele_no+24];
  ldnd  = pointer_vec[ele_no+25];
  dnd   = pointer_vec[ele_no+26];

  ele_no += 27;
  for(int i=0; i<jxsd_no; i++)
  {
    jxsd[i] = pointer_vec[ele_no];
    ele_no++;
  }

  ptype = pointer_vec[ele_no];
  ntro  = pointer_vec[ele_no+ 1];
  ploct = pointer_vec[ele_no+ 2];
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataParser::parse_ace_format_base_data()
{
  //cout << "parse_ace_format_base_data" << endl;
  //cout << "parse_ace_format_base_data: " << ace_read_obj.get_line_no() << endl;

  ace_read_obj.get_list_data_without_data_no(nes, union_ene_grid);
  ace_read_obj.get_list_data_without_data_no(nes, react_xs_tot);
  ace_read_obj.get_list_data_without_data_no(nes, react_xs_cap);
  ace_read_obj.get_list_data_without_data_no(nes, react_xs_sc);
  ace_read_obj.get_list_data_without_data_no(nes, react_xs_heat);

  if( nu != 0 )
  {
    Integer data_no = ace_read_obj.get_int_data();
    if( data_no < 0 )
    {
      nu_p_bar_repr_flg = ace_read_obj.get_int_data();

      if( nu_p_bar_repr_flg == 1 )
      {
        ace_read_obj.get_list_data(nu_p_data);
      }
      else
      {
        ace_read_obj.get_table_data(nu_p_range_data, nu_p_int_data, nu_p_ene_data, nu_p_data);
      }
    }
    else
    {
      string class_name = "FastAceDataParser";
      string func_name  = "parse_ace_format_base_data()";

      vector<string> err_com;
      err_com.push_back("The data number of nu value is larger than 0.");
      err_com.push_back("In this case, FRENDY cannot distinguish this data is nu_prompt or nu_tot.");
      err_com.push_back("The current version of FRENDY considers that this data is nu_tot.");
      err_com.push_back("Please check this ACE file and corresponding ENDF file.");
      err_obj.output_caution(class_name, func_name, err_com);
    }

    nu_bar_repr_flg = data_no;
    if( nu_bar_repr_flg < 0 )
    {
      nu_bar_repr_flg = ace_read_obj.get_int_data();
    }

    if( nu_bar_repr_flg == 1 )
    {
      ace_read_obj.get_list_data(nu_data);
    }
    else
    {
      ace_read_obj.get_table_data(nu_range_data, nu_int_data, nu_ene_data, nu_data);
    }
  }

  if( ntr != 0 )
  {
    ace_read_obj.get_list_data_without_data_no(ntr, react_type_list);
    ace_read_obj.get_list_data_without_data_no(ntr, react_q_value);
    ace_read_obj.get_list_data_without_data_no(ntr, react_type_flg);

    for(int i=0; i<ntr; i++)
    {
      Integer int_tmp;
      ace_read_obj.get_int_data(int_tmp);
    }

    int ene_no_uni = static_cast<int>(union_ene_grid.size());
    react_xs.resize(ntr);
    for(int i=0; i<ntr; i++)
    {
      int ene_sta = 0;
      ace_read_obj.get_int_data(ene_sta); //0 (Read unnecessary data)
      ace_read_obj.get_list_data(react_xs[i]);

      int ene_no = static_cast<int>(react_xs[i].size());
      if( ene_sta + ene_no - 1 != ene_no_uni )
      {
        string class_name = "FastAceDataParser";
        string func_name  = "parse_ace_format_base_data()";

        ostringstream oss01, oss02, oss03, oss04;
        oss01 << react_type_list[i];
        oss02 << ene_no_uni;
        oss03 << ene_sta;
        oss04 << ene_no;
        string str_data01 = "Reaction type                               : " + oss01.str();
        string str_data02 = "Energy grid number of union grid (ESZ)      : " + oss02.str();
        string str_data03 = "Start energy grid number (IE)               : " + oss03.str();
        string str_data04 = "Energy grid number of this reaction XS (NE) : " + oss04.str();

        vector<string> err_com;
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back(str_data04);
        err_com.push_back("IE + NE - 1 != ESZ");
        err_com.push_back("The cross section data is modified (adding zero cross section data).");

        err_obj.output_caution(class_name, func_name, err_com);

        int ene_no_mod = ene_no_uni - ene_sta + 1;
        for(int j=ene_no; j<ene_no_mod; j++)
        {
          react_xs[i].push_back(0.0);
        }
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataParser::parse_ace_format_angular_distribution_data()
{
  //cout << "parse_ace_format_angular_distribution_data " << nr << endl;
  //cout << "parse_ace_format_angular_distribution_data : " << ace_read_obj.get_line_no() << endl;

  int i_max = nr + 1;
  ace_read_obj.get_list_data_without_data_no(i_max, angular_distr_type_flg);

  angular_distr_ene_data.resize(i_max);
  angular_distr_pointer.resize(i_max);
  angular_distr_int_data.resize(i_max);
  angular_distr_cos_data.resize(i_max);
  angular_distr_data.resize(i_max);
  angular_distr_data_integ.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    if( angular_distr_type_flg[i] <= 0 )
    {
      continue;
    }

    ace_read_obj.get_list_data(angular_distr_ene_data[i]);

    int j_max = static_cast<int>(angular_distr_ene_data[i].size());
    ace_read_obj.get_list_data_without_data_no(j_max, angular_distr_pointer[i]);

    angular_distr_int_data[i].resize(j_max);
    angular_distr_cos_data[i].resize(j_max);
    angular_distr_data[i].resize(j_max);
    angular_distr_data_integ[i].resize(j_max);
    for(int j=0; j<j_max; j++)
    {
      if( angular_distr_pointer[i][j] < 0 )
      {
        angular_distr_int_data[i][j] = ace_read_obj.get_int_data();
        ace_read_obj.get_table_data(angular_distr_cos_data[i][j], angular_distr_data[i][j],
                                    angular_distr_data_integ[i][j]);
      }
      else if( angular_distr_pointer[i][j] > 0 )
      {
        angular_distr_int_data[i][j] = int_lin_lin;
        ace_read_obj.get_list_data_without_data_no(33, angular_distr_cos_data[i][j]);
        angular_distr_data[i][j].resize(33);
        angular_distr_data_integ[i][j].resize(33);
        for(int k=0; k<33; k++)
        {
          angular_distr_data[i][j][k]       = 1.0 / 32.0;
          angular_distr_data_integ[i][j][k] = static_cast<Real>(k) / 32.0;
        }
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataParser::parse_ace_format_energy_distribution_data()
{
  int i_max = nr;
  if( nr == 0 )
  {
    return;
  }
  //cout << "parse_ace_format_energy_distribution_data " << nr << endl;
  //cout << "parse_ace_format_energy_distribution_data : " << ace_read_obj.get_line_no() << endl;

  ace_read_obj.get_list_data_without_data_no(i_max, ene_distr_pointer);

  resize_energy_distribution_data(i_max);

  for(int i=0; i<i_max; i++)
  {
    if( abs(react_type_flg[i]) > 100 )
    {
      ace_read_obj.get_table_data(prod_yield_tot_range_data[i], prod_yield_tot_int_data[i],
                                  prod_yield_tot_ene_data[i],   prod_yield_tot_data[i]);
    }

    Integer pointer_data_end = 1;
    while( pointer_data_end != 0 )
    {
              pointer_data_end = ace_read_obj.get_int_data();
      Integer ene_repr_flg     = ace_read_obj.get_int_data();
      Integer pointer_data     = ace_read_obj.get_int_data();

      ene_distr_ene_repr_end_pointer[i].push_back(pointer_data_end);
      ene_distr_ene_repr_flg[i].push_back(ene_repr_flg);
      ene_distr_ene_repr_pointer[i].push_back(pointer_data);

      vector<Integer> xs_part_range_vec, xs_part_int_vec;
      vector<Real>    xs_part_ene_vec,   xs_part_vec;
      ace_read_obj.get_table_data(xs_part_range_vec, xs_part_int_vec, xs_part_ene_vec, xs_part_vec);
      ene_distr_xs_part_range_data[i].push_back(xs_part_range_vec);
      ene_distr_xs_part_int_data[i].push_back(xs_part_int_vec);
      ene_distr_xs_part_ene_data[i].push_back(xs_part_ene_vec);
      ene_distr_xs_part_data[i].push_back(xs_part_vec);
      xs_part_range_vec.clear();
      xs_part_int_vec.clear();
      xs_part_ene_vec.clear();
      xs_part_vec.clear();

      Real    q_coef             = 0.0;
      Real    mass_coef          = 0.0;
      Real    upper_ene_limit    = 0.0;
      Real    n_body_mass        = 0.0;
      Integer n_body_particle_no = 0;
      Integer prob_data_no       = 0;
      vector<int>              ene_in_pointer;
      vector<vector<int> >     ene_out_pointer;
      vector<Integer>          ene_in_int_vec, ene_in_range_vec, ene_out_int_vec,
                               temp_eff_range_vec, temp_eff_int_vec,
                               watt_a_range_vec, watt_a_int_vec, watt_b_range_vec, watt_b_int_vec,
                               prob_ene_in_range_vec, prob_ene_in_int_vec, prob_ene_out_int_vec;
      vector<Real>             ene_in_vec, temp_eff_ene_vec, temp_eff_vec,
                               watt_a_ene_vec, watt_a_vec, watt_b_ene_vec, watt_b_vec, prob_ene_in_vec;
      vector<vector<Integer> > prob_mu_int_vec;
      vector<vector<Real> >    ene_out_ene_vec, ene_out_vec, ene_out_vec_integ,
                               prob_ene_out_vec, prob_mu_vec, prob_mu_vec_integ,
                               prob_coef_a_vec, prob_coef_b_vec, prob_vec, prob_vec_integ;
      vector<vector<vector<Integer> > > prob_int_array;
      vector<vector<vector<Real> > >    prob_mu_array, prob_array, prob_array_integ, prob_ene_out_array;

      if( ene_repr_flg == 1 )
      {
        //This flag is not available in this program
      }
      else if( ene_repr_flg == 3 )
      {
        q_coef    = ace_read_obj.get_real_data();
        mass_coef = ace_read_obj.get_real_data();
      }
      else if( ene_repr_flg == 4 )
      {
        ace_read_obj.get_interpolation_data(ene_in_range_vec, ene_in_int_vec);
        ace_read_obj.get_list_data(ene_in_vec);

        int k_max = static_cast<int>(ene_in_vec.size());
        ace_read_obj.get_list_data_without_data_no(k_max, ene_in_pointer);

        ene_out_int_vec.resize(k_max);
        ene_out_ene_vec.resize(k_max);
        ene_out_vec.resize(k_max);
        ene_out_vec_integ.resize(k_max);
        for(int k=0; k<k_max; k++)
        {
          ene_out_int_vec[k] = ace_read_obj.get_int_data();
          ace_read_obj.get_table_data(ene_out_ene_vec[k], ene_out_vec[k], ene_out_vec_integ[k]);
        }
      }
      else if( ene_repr_flg == 5 )
      {
        //This flag is not available in this program
      }
      else if( ene_repr_flg == 7 || ene_repr_flg == 9 )
      {
        ace_read_obj.get_table_data(temp_eff_range_vec, temp_eff_int_vec, temp_eff_ene_vec, temp_eff_vec);

        upper_ene_limit = ace_read_obj.get_real_data();
      }
      else if( ene_repr_flg == 11 )
      {
        ace_read_obj.get_table_data(watt_a_range_vec, watt_a_int_vec, watt_a_ene_vec, watt_a_vec);
        ace_read_obj.get_table_data(watt_b_range_vec, watt_b_int_vec, watt_b_ene_vec, watt_b_vec);
        upper_ene_limit = ace_read_obj.get_real_data();
      }
      else if( ene_repr_flg == 44 || ene_repr_flg == 61 )
      {
        ace_read_obj.get_interpolation_data(prob_ene_in_range_vec, prob_ene_in_int_vec);
        ace_read_obj.get_list_data(prob_ene_in_vec);

        int k_max = static_cast<int>(prob_ene_in_vec.size());
        ace_read_obj.get_list_data_without_data_no(k_max, ene_in_pointer);

        prob_ene_out_int_vec.resize(k_max);
        prob_ene_out_vec.resize(k_max);
        prob_mu_vec.resize(k_max);
        prob_mu_vec_integ.resize(k_max);
        if( ene_repr_flg == 44 )
        {
          prob_coef_a_vec.resize(k_max);
          prob_coef_b_vec.resize(k_max);
        }
        else if( ene_repr_flg == 61 )
        {
          ene_out_pointer.resize(k_max);
          prob_int_array.resize(k_max);
          prob_mu_array.resize(k_max);
          prob_array.resize(k_max);
          prob_array_integ.resize(k_max);
        }
        for(int k=0; k<k_max; k++)
        {
          prob_ene_out_int_vec[k] = ace_read_obj.get_int_data();
          ace_read_obj.get_table_data(prob_ene_out_vec[k], prob_mu_vec[k], prob_mu_vec_integ[k]);

          int l_max = static_cast<int>(prob_ene_out_vec[k].size());
          if( ene_repr_flg == 44 )
          {
            ace_read_obj.get_list_data_without_data_no(l_max, prob_coef_a_vec[k]);
            ace_read_obj.get_list_data_without_data_no(l_max, prob_coef_b_vec[k]);
          }
          else if( ene_repr_flg == 61 )
          {
            ace_read_obj.get_list_data_without_data_no(l_max, ene_out_pointer[k]);

            prob_int_array[k].resize(l_max);
            prob_mu_array[k].resize(l_max);
            prob_array[k].resize(l_max);
            prob_array_integ[k].resize(l_max);
            for(int l=0; l<l_max; l++)
            {
              prob_int_array[k][l].resize(1);
              prob_int_array[k][l][0] = ace_read_obj.get_int_data();
              ace_read_obj.get_table_data(prob_mu_array[k][l], prob_array[k][l], prob_array_integ[k][l]);
            }
          }
        }
      }
      else if( ene_repr_flg == 66 )
      {
        n_body_particle_no = ace_read_obj.get_int_data();
        n_body_mass        = ace_read_obj.get_real_data();
        prob_data_no       = ace_read_obj.get_int_data();

        prob_mu_vec.resize(1);
        prob_vec.resize(1);
        prob_vec_integ.resize(1);
        ace_read_obj.get_table_data(prob_mu_vec[0], prob_vec[0], prob_vec_integ[0]);
      }
      else if( ene_repr_flg == 67 )
      {
        ace_read_obj.get_interpolation_data(prob_ene_in_range_vec, prob_ene_in_int_vec);
        ace_read_obj.get_list_data(prob_ene_in_vec);

        int k_max = static_cast<int>(prob_ene_in_vec.size());
        ace_read_obj.get_list_data_without_data_no(k_max, ene_in_pointer);

        ene_out_pointer.resize(k_max);
        prob_mu_int_vec.resize(k_max);
        prob_mu_vec.resize(k_max);
        prob_int_array.resize(k_max);
        prob_ene_out_array.resize(k_max);
        prob_array.resize(k_max);
        prob_array_integ.resize(k_max);
        for(int k=0; k<k_max; k++)
        {
          prob_mu_int_vec[k].resize(1);
          prob_mu_int_vec[k][0] = ace_read_obj.get_int_data();
          ace_read_obj.get_list_data(prob_mu_vec[k]);

          int l_max = static_cast<int>(prob_mu_vec[k].size());
          ace_read_obj.get_list_data_without_data_no(l_max, ene_out_pointer[k]);

          prob_int_array[k].resize(l_max);
          prob_ene_out_array[k].resize(l_max);
          prob_array[k].resize(l_max);
          prob_array_integ[k].resize(l_max);
          for(int l=0; l<l_max; l++)
          {
            prob_int_array[k][l].resize(1);
            prob_int_array[k][l][0] = ace_read_obj.get_int_data();
            ace_read_obj.get_table_data(prob_ene_out_array[k][l], prob_array[k][l], prob_array_integ[k][l]);
          }
        }
      }

      ene_distr_ene_in_pointer[i].push_back(ene_in_pointer);
      ene_distr_ene_out_pointer[i].push_back(ene_out_pointer);

      ene_distr_q_coef[i].push_back(q_coef);
      ene_distr_mass_coef[i].push_back(mass_coef);
      ene_distr_ene_in_range_data[i].push_back(ene_in_range_vec);
      ene_distr_ene_in_int_data[i].push_back(ene_in_int_vec);
      ene_distr_ene_in_data[i].push_back(ene_in_vec);
      ene_distr_ene_out_int_data[i].push_back(ene_out_int_vec);
      ene_distr_ene_out_ene_data[i].push_back(ene_out_ene_vec);
      ene_distr_ene_out_data[i].push_back(ene_out_vec);
      ene_distr_ene_out_data_integ[i].push_back(ene_out_vec_integ);
      ene_distr_temp_eff_range_data[i].push_back(temp_eff_range_vec);
      ene_distr_temp_eff_int_data[i].push_back(temp_eff_int_vec);
      ene_distr_temp_eff_ene_data[i].push_back(temp_eff_ene_vec);
      ene_distr_temp_eff_data[i].push_back(temp_eff_vec);
      ene_distr_upper_ene_limit[i].push_back(upper_ene_limit);
      ene_distr_watt_a_range_data[i].push_back(watt_a_range_vec);
      ene_distr_watt_a_int_data[i].push_back(watt_a_int_vec);
      ene_distr_watt_a_ene_data[i].push_back(watt_a_ene_vec);
      ene_distr_watt_a_data[i].push_back(watt_a_vec);
      ene_distr_watt_b_range_data[i].push_back(watt_b_range_vec);
      ene_distr_watt_b_int_data[i].push_back(watt_b_int_vec);
      ene_distr_watt_b_ene_data[i].push_back(watt_b_ene_vec);
      ene_distr_watt_b_data[i].push_back(watt_b_vec);
      prod_distr_prob_ene_in_range_data[i].push_back(prob_ene_in_range_vec);
      prod_distr_prob_ene_in_int_data[i].push_back(prob_ene_in_int_vec);
      prod_distr_prob_ene_in_data[i].push_back(prob_ene_in_vec);
      prod_distr_prob_ene_out_int_data[i].push_back(prob_ene_out_int_vec);
      prod_distr_prob_ene_out_data[i].push_back(prob_ene_out_vec);
      prod_distr_prob_mu_data[i].push_back(prob_mu_vec);
      prod_distr_prob_mu_data_integ[i].push_back(prob_mu_vec_integ);
      prod_distr_prob_coef_a[i].push_back(prob_coef_a_vec);
      prod_distr_prob_coef_b[i].push_back(prob_coef_b_vec);
      prod_distr_prob_int_vec[i].push_back(prob_int_array);
      prod_distr_prob_mu_vec[i].push_back(prob_mu_array);
      prod_distr_prob_vec[i].push_back(prob_array);
      prod_distr_prob_vec_integ[i].push_back(prob_array_integ);
      prod_distr_n_body_mass[i].push_back(n_body_mass);
      prod_distr_n_body_particle_no[i].push_back(n_body_particle_no);
      prod_distr_prob_data_no[i].push_back(prob_data_no);
      prod_distr_prob_data[i].push_back(prob_vec);
      prod_distr_prob_data_integ[i].push_back(prob_vec_integ);
      prod_distr_prob_mu_int_data[i].push_back(prob_mu_int_vec);
      prod_distr_prob_ene_out_vec[i].push_back(prob_ene_out_array);

      ene_in_pointer.clear();
      clr_obj.clear_vec_array2_int(ene_out_pointer);

      ene_in_int_vec.clear();
      ene_in_range_vec.clear();
      ene_out_int_vec.clear();
      temp_eff_range_vec.clear();
      temp_eff_int_vec.clear();
      watt_a_range_vec.clear();
      watt_a_int_vec.clear();
      watt_b_range_vec.clear();
      watt_b_int_vec.clear();
      prob_ene_in_range_vec.clear();
      prob_ene_in_int_vec.clear();
      prob_ene_out_int_vec.clear();
      ene_in_vec.clear();
      temp_eff_ene_vec.clear();
      temp_eff_vec.clear();
      watt_a_ene_vec.clear();
      watt_a_vec.clear();
      watt_b_ene_vec.clear();
      watt_b_vec.clear();
      prob_ene_in_vec.clear();
      clr_obj.clear_vec_array2_int(prob_mu_int_vec);
      clr_obj.clear_vec_array2_real(ene_out_ene_vec);
      clr_obj.clear_vec_array2_real(ene_out_vec);
      clr_obj.clear_vec_array2_real(ene_out_vec_integ);
      clr_obj.clear_vec_array2_real(prob_ene_out_vec);
      clr_obj.clear_vec_array2_real(prob_mu_vec);
      clr_obj.clear_vec_array2_real(prob_mu_vec_integ);
      clr_obj.clear_vec_array2_real(prob_coef_a_vec);
      clr_obj.clear_vec_array2_real(prob_coef_b_vec);
      clr_obj.clear_vec_array2_real(prob_vec);
      clr_obj.clear_vec_array2_real(prob_vec_integ);
      clr_obj.clear_vec_array3_int(prob_int_array);
      clr_obj.clear_vec_array3_real(prob_mu_array);
      clr_obj.clear_vec_array3_real(prob_array);
      clr_obj.clear_vec_array3_real(prob_array_integ);
      clr_obj.clear_vec_array3_real(prob_ene_out_array);
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataParser::parse_ace_format_unreso_prob_table_data()
{
  if( iurpt == 0 )
  {
    return;
  }
  //cout << "parse_ace_format_unreso_prob_table_data " << iurpt << endl;
  //cout << "parse_ace_format_unreso_prob_table_data : " << ace_read_obj.get_line_no() << endl;

  Integer table_no                   = ace_read_obj.get_int_data();
  Integer bin_no                     = ace_read_obj.get_int_data();

  unreso_prob_tab_int_data           = ace_read_obj.get_int_data();
  unreso_prob_tab_inela_comp_flg     = ace_read_obj.get_int_data();
  unreso_prob_tab_abs_comp_flg       = ace_read_obj.get_int_data();
  unreso_prob_tab_self_shielding_flg = ace_read_obj.get_int_data();

  int i_max = static_cast<int>(table_no);
  int j_max = static_cast<int>(bin_no);
  ace_read_obj.get_list_data_without_data_no(i_max, unreso_prob_tab_ene);

  unreso_prob_tab_heat.resize(i_max);
  unreso_prob_tab_sample_no.resize(i_max);
  unreso_prob_tab_table.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    ace_read_obj.get_list_data_without_data_no(j_max, unreso_prob_tab_sample_no[i]);

    unreso_prob_tab_table[i].resize(xs_type_no);
    for(int k=0; k<xs_type_no; k++)
    {
      ace_read_obj.get_list_data_without_data_no(j_max, unreso_prob_tab_table[i][k]);
    }
    ace_read_obj.get_list_data_without_data_no(j_max, unreso_prob_tab_heat[i]);
  }

  //Check the order of total probability table
  for(int i=0; i<i_max; i++)
  {
    int k_max = static_cast<int>(unreso_prob_tab_table[i][total_xs].size());
    for(int k=1; k<k_max; k++)
    {
      if( unreso_prob_tab_table[i][total_xs][k] - unreso_prob_tab_table[i][total_xs][k-1] < 0.0 )
      {
        string class_name = "FastAceDataParser";
        string func_name  = "parse_ace_format_unreso_prob_table_data()";

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

        err_obj.output_caution(class_name, func_name, err_com);
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataParser::parse_ace_format_nu_d_data()
{
  if( ndnf == 0 )
  {
    return;
  }
  //cout << "parse_ace_format_nu_d_data " << ndnf << endl;
  //cout << "parse_ace_format_nu_d_data : " << ace_read_obj.get_line_no() << endl;

  int i_max = ndnf;
  nu_d_bar_repr_flg = ace_read_obj.get_int_data();
  ace_read_obj.get_table_data(nu_d_range_data, nu_d_int_data, nu_d_ene_data, nu_d_data);

  nu_d_decay_constant.resize(i_max);
  nu_d_xs_part_range_data.resize(i_max);
  nu_d_xs_part_int_data.resize(i_max);
  nu_d_xs_part_ene_data.resize(i_max);
  nu_d_xs_part_data.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    nu_d_decay_constant[i] = ace_read_obj.get_real_data();
    ace_read_obj.get_table_data(nu_d_xs_part_range_data[i], nu_d_xs_part_int_data[i],
                                nu_d_xs_part_ene_data[i],   nu_d_xs_part_data[i]);
  }

  ace_read_obj.get_list_data_without_data_no(i_max, nu_d_pointer);

  nu_d_ene_min.resize(i_max);
  nu_d_ene_max.resize(i_max);
  nu_d_ene_in_range_data.resize(i_max);
  nu_d_ene_in_int_data.resize(i_max);
  nu_d_ene_in_data.resize(i_max);
  nu_d_ene_in_pointer.resize(i_max);
  nu_d_ene_out_int_data.resize(i_max);
  nu_d_ene_out_data.resize(i_max);
  nu_d_ene_distr_data.resize(i_max);
  nu_d_ene_distr_data_integ.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    ace_read_obj.get_int_data(); //0
    ace_read_obj.get_int_data(); //4
    ace_read_obj.get_int_data(); //nu_d_pointer[i] + 9
    ace_read_obj.get_int_data(); //0
    ace_read_obj.get_int_data(); //2

    nu_d_ene_min[i] = ace_read_obj.get_real_data();
    nu_d_ene_max[i] = ace_read_obj.get_real_data();
                      ace_read_obj.get_real_data(); //1.0
                      ace_read_obj.get_real_data(); //1.0
    ace_read_obj.get_interpolation_data(nu_d_ene_in_range_data[i], nu_d_ene_in_int_data[i]);
    ace_read_obj.get_list_data(nu_d_ene_in_data[i]);

    int j_max = static_cast<int>(nu_d_ene_in_data[i].size());
    ace_read_obj.get_list_data_without_data_no(j_max, nu_d_ene_in_pointer[i]);

    nu_d_ene_out_int_data[i].resize(j_max);
    nu_d_ene_out_data[i].resize(j_max);
    nu_d_ene_distr_data[i].resize(j_max);
    nu_d_ene_distr_data_integ[i].resize(j_max);
    for(int j=0; j<j_max; j++)
    {
      ace_read_obj.get_int_data(nu_d_ene_out_int_data[i][j]);
      ace_read_obj.get_table_data(nu_d_ene_out_data[i][j], nu_d_ene_distr_data[i][j],
                                                           nu_d_ene_distr_data_integ[i][j]);
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataParser::parse_ace_format_gamma_production_xs()
{
  if( gpd == 0 )
  {
    return;
  }
  //cout << "parse_ace_format_gamma_production_xs " << gpd << endl;
  //cout << "parse_ace_format_gamma_production_xs : " << ace_read_obj.get_line_no() << endl;

  int i_max = nes;
  ace_read_obj.get_list_data_without_data_no(i_max, gamma_product_xs);

  //For gendf data file
  //Modify multigroup photon data in GENDF file.
  //The GENDF file is not available in FRENDY.
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataParser::parse_ace_format_photon_production_data()
{
  if( ntrp == 0 )
  {
    return;
  }
  //cout << "parse_ace_format_photon_production_data " << ntrp << endl;
  //cout << "parse_ace_format_photon_production_data : " << ace_read_obj.get_line_no() << endl;

  int i_max = ntrp;
  ace_read_obj.get_list_data_without_data_no(i_max, photon_prod_reaction_type_all);
  ace_read_obj.get_list_data_without_data_no(i_max, photon_prod_pointer);

  photon_prod_file_no.resize(i_max);
  photon_prod_xs_non_zero_pos.resize(i_max);
  photon_prod_xs_data.resize(i_max);
  photon_prod_reaction_type.resize(i_max);
  photon_prod_multiplicity_range_data.resize(i_max);
  photon_prod_multiplicity_int_data.resize(i_max);
  photon_prod_multiplicity_ene_data.resize(i_max);
  photon_prod_multiplicity_data.resize(i_max);
  photon_prod_distr_range_data.resize(i_max);
  photon_prod_distr_int_data.resize(i_max);
  photon_prod_distr_ene_data.resize(i_max);
  photon_prod_distr_data.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    photon_prod_file_no[i] = ace_read_obj.get_int_data();

    if( photon_prod_file_no[i] != 12 && photon_prod_file_no[i] != 16 )
    {
      photon_prod_xs_non_zero_pos[i].resize(2);
      photon_prod_xs_non_zero_pos[i][0] = ace_read_obj.get_int_data();
      photon_prod_xs_non_zero_pos[i][1] = ace_read_obj.get_int_data();

      int j_max = static_cast<int>(photon_prod_xs_non_zero_pos[i][1]);
      ace_read_obj.get_list_data_without_data_no(j_max, photon_prod_xs_data[i]);
    }
    else
    {
      photon_prod_reaction_type[i] = ace_read_obj.get_int_data();
      if( photon_prod_file_no[i] == 12 )
      {
        ace_read_obj.get_table_data(photon_prod_multiplicity_range_data[i],
                                    photon_prod_multiplicity_int_data[i],
                                    photon_prod_multiplicity_ene_data[i],
                                    photon_prod_multiplicity_data[i]);
      }
      else
      {
        ace_read_obj.get_table_data(photon_prod_distr_range_data[i],
                                    photon_prod_distr_int_data[i],
                                    photon_prod_distr_ene_data[i],
                                    photon_prod_distr_data[i]);
      }
    }
  }

  i_max = ntrp;
  ace_read_obj.get_list_data_without_data_no(i_max, photon_angular_pointer);

  photon_angular_distr_ene_data.resize(i_max);
  photon_angular_ene_pointer.resize(i_max);
  photon_angular_distr_prob_cos_data.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    if( photon_angular_pointer[i] <= 0 )
    {
      continue;
    }

    ace_read_obj.get_list_data(photon_angular_distr_ene_data[i]);

    int j_max = static_cast<int>(photon_angular_distr_ene_data[i].size());
    ace_read_obj.get_list_data_without_data_no(j_max, photon_angular_ene_pointer[i]);

    photon_angular_distr_prob_cos_data[i].resize(j_max);
    for(int j=0; j<j_max; j++)
    {
      if( photon_angular_ene_pointer[i][j] > 0 )
      {
        ace_read_obj.get_list_data_without_data_no(33, photon_angular_distr_prob_cos_data[i][j]);
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataParser::parse_ace_format_photon_energy_distr_data()
{
  if( ntrp == 0 )
  {
    return;
  }
  //cout << "parse_ace_format_photon_energy_distr_data " << ntrp << endl;
  //cout << "parse_ace_format_photon_energy_distr_data : " << ace_read_obj.get_line_no() << endl;

  int i_max = ntrp;
  ace_read_obj.get_list_data_without_data_no(i_max, photon_ene_pointer);

  photon_energy_distr_flg.resize(i_max);
  photon_ene_distr_pointer.resize(i_max);
  photon_energy_distr_range_data.resize(i_max);
  photon_energy_distr_int_data.resize(i_max);
  photon_energy_distr_ene_data.resize(i_max);
  photon_energy_distr_prob_data.resize(i_max);
  photon_energy_distr_ene_flg.resize(i_max);
  photon_energy_distr_binding_ene_data.resize(i_max);
  photon_energy_distr_ene_in_range_data.resize(i_max);
  photon_energy_distr_ene_in_int_data.resize(i_max);
  photon_energy_distr_ene_in_data.resize(i_max);
  photon_ene_weight_pointer.resize(i_max);
  photon_energy_distr_weight_int_data.resize(i_max);
  photon_energy_distr_weight_ene_data.resize(i_max);
  photon_energy_distr_weight_data.resize(i_max);
  photon_energy_distr_weight_data_integ.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
                                  ace_read_obj.get_int_data();
    photon_energy_distr_flg[i]  = ace_read_obj.get_int_data();
    photon_ene_distr_pointer[i] = ace_read_obj.get_int_data();
    ace_read_obj.get_table_data(photon_energy_distr_range_data[i], photon_energy_distr_int_data[i],
                                photon_energy_distr_ene_data[i],   photon_energy_distr_prob_data[i]);

    if( photon_energy_distr_flg[i] == 1 )
    {
      //This flag is not available in this program
    }
    else if( photon_energy_distr_flg[i] == 2 )
    {
      photon_energy_distr_ene_flg[i]          = ace_read_obj.get_int_data();
      photon_energy_distr_binding_ene_data[i] = ace_read_obj.get_real_data();
    }
    else if( photon_energy_distr_flg[i] == 4 || photon_energy_distr_flg[i] == 44 )
    {
      ace_read_obj.get_interpolation_data(photon_energy_distr_ene_in_range_data[i],
                                          photon_energy_distr_ene_in_int_data[i]);
      ace_read_obj.get_list_data(photon_energy_distr_ene_in_data[i]);

      int j_max = static_cast<int>(photon_energy_distr_ene_in_data[i].size());
      ace_read_obj.get_list_data_without_data_no(j_max, photon_ene_weight_pointer[i]);

      photon_energy_distr_weight_int_data[i].resize(j_max);
      photon_energy_distr_weight_ene_data[i].resize(j_max);
      photon_energy_distr_weight_data[i].resize(j_max);
      photon_energy_distr_weight_data_integ[i].resize(j_max);
      for(int j=0; j<j_max; j++)
      {
        photon_energy_distr_weight_int_data[i][j] = ace_read_obj.get_int_data();
        ace_read_obj.get_table_data(photon_energy_distr_weight_ene_data[i][j],
                                    photon_energy_distr_weight_data[i][j],
                                    photon_energy_distr_weight_data_integ[i][j]);
      }
    }
  }

  ace_read_obj.get_list_data(photon_prod_reaction_type_without_xs);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataParser::parse_ace_format_particle_production_data()
{
  if( ntype == 0 )
  {
    return;
  }
  //cout << "parse_ace_format_particle_production_data " << ntype << endl;
  //cout << "parse_ace_format_particle_production_data : " << ace_read_obj.get_line_no() << endl;

  int i_max = ntype;
  ace_read_obj.get_list_data_without_data_no(i_max, particle_prod_flg);
  ace_read_obj.get_list_data_without_data_no(i_max, particle_prod_count);

  int case_no = 10;
  particle_prod_pointer.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    particle_prod_pointer[i].resize(case_no);
    ace_read_obj.get_list_data_without_data_no(case_no, particle_prod_pointer[i]);
  }

  resize_particle_production_data(i_max);
  for(int i=0; i<i_max; i++)
  {
    particle_prod_ene_sta[i] = ace_read_obj.get_int_data();
    particle_prod_ene_no[i]  = ace_read_obj.get_int_data();

    int j_max = static_cast<int>(particle_prod_ene_no[i]);
    ace_read_obj.get_list_data_without_data_no(j_max, particle_prod_xs[i]);
    ace_read_obj.get_list_data_without_data_no(j_max, particle_prod_heat[i]);

    j_max = static_cast<int>(particle_prod_count[i]);
    ace_read_obj.get_list_data_without_data_no(j_max, particle_prod_reaction_type_all[i]);
    ace_read_obj.get_list_data_without_data_no(j_max, particle_prod_frame_flg[i]);
    ace_read_obj.get_list_data_without_data_no(j_max, particle_prod_distr_pointer[i]);

    particle_prod_file_no[i].resize(j_max);
    particle_prod_reaction_type[i].resize(j_max);
    particle_prod_distr_range_data[i].resize(j_max);
    particle_prod_distr_int_data[i].resize(j_max);
    particle_prod_distr_ene_data[i].resize(j_max);
    particle_prod_distr_data[i].resize(j_max);
    for(int j=0; j<j_max; j++)
    {
      particle_prod_file_no[i][j]       = ace_read_obj.get_int_data();
      particle_prod_reaction_type[i][j] = ace_read_obj.get_int_data();

      ace_read_obj.get_table_data(particle_prod_distr_range_data[i][j], particle_prod_distr_int_data[i][j],
                                  particle_prod_distr_ene_data[i][j],   particle_prod_distr_data[i][j]);
    }

    ace_read_obj.get_list_data_without_data_no(j_max, particle_prod_angular_pointer[i]);

    particle_prod_angular_ene_data[i].resize(j_max);
    particle_prod_angular_ene_pointer[i].resize(j_max);
    particle_prod_angular_int_data[i].resize(j_max);
    particle_prod_angular_cos_data[i].resize(j_max);
    particle_prod_angular_distr_data[i].resize(j_max);
    particle_prod_angular_distr_data_integ[i].resize(j_max);
    for(int j=0; j<j_max; j++)
    {
      if( particle_prod_angular_pointer[i][j] <= 0 )
      {
        continue;
      }

      ace_read_obj.get_list_data(particle_prod_angular_ene_data[i][j]);

      int k_max = static_cast<int>(particle_prod_angular_ene_data[i][j].size());
      ace_read_obj.get_list_data_without_data_no(k_max, particle_prod_angular_ene_pointer[i][j]);

      particle_prod_angular_int_data[i][j].resize(k_max);
      particle_prod_angular_cos_data[i][j].resize(k_max);
      particle_prod_angular_distr_data[i][j].resize(k_max);
      particle_prod_angular_distr_data_integ[i][j].resize(k_max);
      for(int k=0; k<k_max; k++)
      {
        particle_prod_angular_int_data[i][j][k] = ace_read_obj.get_int_data();
        ace_read_obj.get_table_data(particle_prod_angular_cos_data[i][j][k],
                                    particle_prod_angular_distr_data[i][j][k],
                                    particle_prod_angular_distr_data_integ[i][j][k]);
      }
    }

    ace_read_obj.get_list_data_without_data_no(j_max, particle_prod_ene_pointer[i]);

    resize_particle_production_data(i, j_max);
    for(int j=0; j<j_max; j++)
    {
      if( particle_prod_ene_pointer[i][j] <= 0 )
      {
        continue;
      }

      ace_read_obj.get_int_data(); //0 (Read unnecessary data)

      particle_prod_ene_flg[i][j]        = ace_read_obj.get_int_data();
      particle_prod_ene_in_pointer[i][j] = ace_read_obj.get_int_data();
      ace_read_obj.get_table_data(particle_prod_ene_range_data[i][j], particle_prod_ene_int_data[i][j],
                                  particle_prod_ene_data[i][j],       particle_prod_ene_prob_data[i][j]);
 
      if( particle_prod_ene_flg[i][j] ==  4 || particle_prod_ene_flg[i][j] == 44 ||
          particle_prod_ene_flg[i][j] == 61)
      {
        ace_read_obj.get_interpolation_data(particle_prod_ene_in_range_data[i][j],
                                            particle_prod_ene_in_int_data[i][j]);
        ace_read_obj.get_list_data(particle_prod_ene_in_data[i][j]);

        int k_max = static_cast<int>(particle_prod_ene_in_data[i][j].size());
        ace_read_obj.get_list_data_without_data_no(k_max, particle_prod_a_pointer[i][j]);

        particle_prod_a_int_data[i][j].resize(k_max);
        particle_prod_a_data[i][j].resize(k_max);
        particle_prod_a_distr_data[i][j].resize(k_max);
        particle_prod_a_distr_data_integ[i][j].resize(k_max);
        if( particle_prod_ene_flg[i][j] ==  44 )
        {
          particle_prod_ene_out_coef_a[i][j].resize(k_max);
          particle_prod_ene_out_coef_b[i][j].resize(k_max);
        }
        else if( particle_prod_ene_flg[i][j] ==  61 )
        {
          particle_prod_b_pointer[i][j].resize(k_max);
          particle_prod_b_int_data[i][j].resize(k_max);
          particle_prod_b_data[i][j].resize(k_max);
          particle_prod_b_prob_data[i][j].resize(k_max);
          particle_prod_b_prob_data_integ[i][j].resize(k_max);
        }

        for(int k=0; k<k_max; k++)
        {
          particle_prod_a_int_data[i][j][k] = ace_read_obj.get_int_data();
          ace_read_obj.get_table_data(particle_prod_a_data[i][j][k],
                                      particle_prod_a_distr_data[i][j][k],
                                      particle_prod_a_distr_data_integ[i][j][k]);

          int l_max = static_cast<int>(particle_prod_a_data[i][j][k].size());
          if( particle_prod_ene_flg[i][j] ==  44 )
          {
            ace_read_obj.get_list_data_without_data_no(l_max, particle_prod_ene_out_coef_a[i][j][k]);
            ace_read_obj.get_list_data_without_data_no(l_max, particle_prod_ene_out_coef_b[i][j][k]);
          }
          else if( particle_prod_ene_flg[i][j] ==  61 )
          {
            ace_read_obj.get_list_data_without_data_no(l_max, particle_prod_b_pointer[i][j][k]);

            particle_prod_b_int_data[i][j][k].resize(l_max);
            particle_prod_b_data[i][j][k].resize(l_max);
            particle_prod_b_prob_data[i][j][k].resize(l_max);
            particle_prod_b_prob_data_integ[i][j][k].resize(l_max);
            for(int l=0; l<l_max; l++)
            {
              particle_prod_b_int_data[i][j][k][l] = ace_read_obj.get_int_data();
              ace_read_obj.get_table_data(particle_prod_b_data[i][j][k][l],
                                          particle_prod_b_prob_data[i][j][k][l],
                                          particle_prod_b_prob_data_integ[i][j][k][l]);
            }
          }
        }
      }
      else if( particle_prod_ene_flg[i][j] == 33 )
      {
        particle_prod_q_value[i][j]   = ace_read_obj.get_real_data();
        particle_prod_mass_coef[i][j] = ace_read_obj.get_real_data();
      }
      else if( particle_prod_ene_flg[i][j] == 66 )
      {
        particle_prod_q_value[i][j]   = static_cast<Real>(ace_read_obj.get_int_data());
        particle_prod_mass_coef[i][j] = ace_read_obj.get_real_data();

        particle_prod_a_int_data[i][j].resize(1);
        particle_prod_a_data[i][j].resize(1);
        particle_prod_a_distr_data[i][j].resize(1);
        particle_prod_a_distr_data_integ[i][j].resize(1);
        particle_prod_a_int_data[i][j][0] = ace_read_obj.get_int_data();
        ace_read_obj.get_table_data(particle_prod_a_data[i][j][0],
                                    particle_prod_a_distr_data[i][j][0],
                                    particle_prod_a_distr_data_integ[i][j][0]);
      }
      else if( particle_prod_ene_flg[i][j] == 67 )
      {
        int k_max = static_cast<int>(particle_prod_ene_data[i][j].size());
        particle_prod_a_int_data[i][j].resize(k_max);
        particle_prod_a_data[i][j].resize(k_max);
        particle_prod_b_int_data[i][j].resize(k_max);
        particle_prod_b_data[i][j].resize(k_max);
        particle_prod_b_prob_data[i][j].resize(k_max);
        particle_prod_b_prob_data_integ[i][j].resize(k_max);
        for(int k=0; k<k_max; k++)
        {
          particle_prod_a_int_data[i][j][k] = ace_read_obj.get_int_data();
          ace_read_obj.get_list_data(particle_prod_a_data[i][j][k]);

          int l_max = static_cast<int>(particle_prod_a_data[i][j][k].size());
          for(int l=0; l<l_max; l++)
          {
            ace_read_obj.get_int_data(); //pointer
          }

          particle_prod_b_int_data[i][j][k].resize(l_max);
          particle_prod_b_data[i][j][k].resize(l_max);
          particle_prod_b_prob_data[i][j][k].resize(l_max);
          particle_prod_b_prob_data_integ[i][j][k].resize(l_max);
          for(int l=0; l<l_max; l++)
          {
            particle_prod_b_int_data[i][j][k][l] = ace_read_obj.get_int_data();
            ace_read_obj.get_table_data(particle_prod_b_data[i][j][k][l],
                                        particle_prod_b_prob_data[i][j][k][l],
                                        particle_prod_b_prob_data_integ[i][j][k][l]);
          }
        }
      }
    }

    vector<Integer> int_vec;
    ace_read_obj.get_list_data(int_vec);

     //Check particle_prod_reaction_type at yh block
    int particle_prod_reaction_type_no_flg = 0;
    int particle_prod_reaction_type_flg    = 0;
    if( static_cast<int>(int_vec.size()) != static_cast<int>(particle_prod_reaction_type[i].size()) )
    {
      particle_prod_reaction_type_no_flg = 1;
    }
    else
    {
      for(int j=0; j<static_cast<int>(particle_prod_reaction_type[i].size()); j++)
      {
        if( int_vec[j] != particle_prod_reaction_type[i][j] )
        {
          particle_prod_reaction_type_flg = 1;
          break;
        }
      }
    }

    if( particle_prod_reaction_type_no_flg > 0 || particle_prod_reaction_type_flg > 0 )
    {
      string class_name = "FastAceDataParser";
      string func_name  = "parse_ace_format_particle_production_data()";

      vector<string> err_com;
      ostringstream oss_i, oss_ntype;
      oss_i     << i+1;
      oss_ntype << i_max;
      string str_data_pos = "Position : " + oss_i.str() + " / " + oss_ntype.str();
      err_com.push_back(str_data_pos);
      err_com.push_back("");

      if( particle_prod_reaction_type_no_flg > 0 )
      {
        err_com.push_back("The number of reaction type (particle_prod_reaction_type) in mtrh block");
        err_com.push_back("is different to that of yh block.");

        ostringstream oss01, oss02;
        oss01 << static_cast<int>(particle_prod_reaction_type[i].size());
        oss02 << static_cast<int>(int_vec.size());
        string str_data01 = "  reaction type no in mtrh block : " + oss01.str();
        err_com.push_back(str_data01);
        for(int j=0; j<static_cast<int>(particle_prod_reaction_type[i].size()); j++)
        {
          ostringstream oss_mt01, oss_mt02, oss_mt03;
          oss_mt01 << j+1;
          oss_mt02 << static_cast<int>(particle_prod_reaction_type[i].size());
          oss_mt03 << particle_prod_reaction_type[i][j];
          string str_data_mt = "    " + oss_mt01.str() + " / " + oss_mt02.str() + " : " + oss_mt03.str();
          err_com.push_back(str_data_mt);
        }
        string str_data02 = "  reaction type no in yh block   : " + oss02.str();
        err_com.push_back(str_data02);
        for(int j=0; j<static_cast<int>(int_vec.size()); j++)
        {
          ostringstream oss_mt01, oss_mt02, oss_mt03;
          oss_mt01 << j+1;
          oss_mt02 << static_cast<int>(int_vec.size());
          oss_mt03 << int_vec[j];
          string str_data_mt = "    " + oss_mt01.str() + " / " + oss_mt02.str() + " : " + oss_mt03.str();
          err_com.push_back(str_data_mt);
        }
      }
      else
      {
        err_com.push_back("The reaction type (particle_prod_reaction_type) in mtrh block is different");
        err_com.push_back("to that of yh block");
        err_com.push_back("  Position : reaction type in mtrh block / reaction type in yh block");
        for(int j=0; j<static_cast<int>(particle_prod_reaction_type[i].size()); j++)
        {
          ostringstream oss_mt01, oss_mt02, oss_mt03, oss_mt04;
          oss_mt01 << j+1;
          oss_mt02 << static_cast<int>(particle_prod_reaction_type[i].size());
          oss_mt03 << particle_prod_reaction_type[i][j];
          oss_mt04 << int_vec[j];
          string str_data_mt = "  " + oss_mt01.str() + " / " + oss_mt02.str() + " : "
                             + oss_mt03.str() + " / " + oss_mt04.str();
          err_com.push_back(str_data_mt);
        }
      }
      err_com.push_back("");
      err_com.push_back("This ACE file (ldlwh, dlwh, and yh block) may be inappropriate");
      err_com.push_back("Please check this ACE file.");
      err_obj.output_caution(class_name, func_name, err_com);
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataParser::resize_energy_distribution_data(int i_max)
{
  prod_yield_tot_range_data.resize(i_max);
  prod_yield_tot_int_data.resize(i_max);
  prod_yield_tot_ene_data.resize(i_max);
  prod_yield_tot_data.resize(i_max);

  ene_distr_ene_repr_end_pointer.resize(i_max);
  ene_distr_ene_repr_pointer.resize(i_max);
  ene_distr_ene_repr_flg.resize(i_max);
  ene_distr_xs_part_range_data.resize(i_max);
  ene_distr_xs_part_int_data.resize(i_max);
  ene_distr_xs_part_ene_data.resize(i_max);
  ene_distr_xs_part_data.resize(i_max);
  ene_distr_q_coef.resize(i_max);
  ene_distr_mass_coef.resize(i_max);
  ene_distr_ene_in_range_data.resize(i_max);
  ene_distr_ene_in_int_data.resize(i_max);
  ene_distr_ene_in_data.resize(i_max);
  ene_distr_ene_in_pointer.resize(i_max);
  ene_distr_ene_out_pointer.resize(i_max);
  ene_distr_ene_out_int_data.resize(i_max);
  ene_distr_ene_out_ene_data.resize(i_max);
  ene_distr_ene_out_data.resize(i_max);
  ene_distr_ene_out_data_integ.resize(i_max);
  ene_distr_temp_eff_range_data.resize(i_max);
  ene_distr_temp_eff_int_data.resize(i_max);
  ene_distr_temp_eff_ene_data.resize(i_max);
  ene_distr_temp_eff_data.resize(i_max);
  ene_distr_upper_ene_limit.resize(i_max);
  ene_distr_watt_a_range_data.resize(i_max);
  ene_distr_watt_a_int_data.resize(i_max);
  ene_distr_watt_a_ene_data.resize(i_max);
  ene_distr_watt_a_data.resize(i_max);
  ene_distr_watt_b_range_data.resize(i_max);
  ene_distr_watt_b_int_data.resize(i_max);
  ene_distr_watt_b_ene_data.resize(i_max);
  ene_distr_watt_b_data.resize(i_max);
  prod_distr_prob_ene_in_range_data.resize(i_max);
  prod_distr_prob_ene_in_int_data.resize(i_max);
  prod_distr_prob_ene_in_data.resize(i_max);
  prod_distr_prob_ene_out_int_data.resize(i_max);
  prod_distr_prob_ene_out_data.resize(i_max);
  prod_distr_prob_mu_data.resize(i_max);
  prod_distr_prob_mu_data_integ.resize(i_max);
  prod_distr_prob_coef_a.resize(i_max);
  prod_distr_prob_coef_b.resize(i_max);
  prod_distr_prob_int_vec.resize(i_max);
  prod_distr_prob_mu_vec.resize(i_max);
  prod_distr_prob_vec.resize(i_max);
  prod_distr_prob_vec_integ.resize(i_max);
  prod_distr_n_body_mass.resize(i_max);
  prod_distr_n_body_particle_no.resize(i_max);
  prod_distr_prob_data_no.resize(i_max);
  prod_distr_prob_data.resize(i_max);
  prod_distr_prob_data_integ.resize(i_max);
  prod_distr_prob_mu_int_data.resize(i_max);
  prod_distr_prob_ene_out_vec.resize(i_max);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataParser::resize_particle_production_data(int i_max)
{
  particle_prod_ene_sta.resize(i_max);
  particle_prod_ene_no.resize(i_max);
  particle_prod_xs.resize(i_max);
  particle_prod_heat.resize(i_max);
  particle_prod_reaction_type_all.resize(i_max);
  particle_prod_frame_flg.resize(i_max);
  particle_prod_distr_pointer.resize(i_max);
  particle_prod_file_no.resize(i_max);
  particle_prod_reaction_type.resize(i_max);
  particle_prod_distr_range_data.resize(i_max);
  particle_prod_distr_int_data.resize(i_max);
  particle_prod_distr_ene_data.resize(i_max);
  particle_prod_distr_data.resize(i_max);
  particle_prod_angular_pointer.resize(i_max);
  particle_prod_angular_ene_data.resize(i_max);
  particle_prod_angular_ene_pointer.resize(i_max);
  particle_prod_angular_int_data.resize(i_max);
  particle_prod_angular_cos_data.resize(i_max);
  particle_prod_angular_distr_data.resize(i_max);
  particle_prod_angular_distr_data_integ.resize(i_max);
  particle_prod_ene_pointer.resize(i_max);
  particle_prod_ene_flg.resize(i_max);
  particle_prod_ene_in_pointer.resize(i_max);
  particle_prod_ene_range_data.resize(i_max);
  particle_prod_ene_int_data.resize(i_max);
  particle_prod_ene_data.resize(i_max);
  particle_prod_ene_prob_data.resize(i_max);
  particle_prod_ene_in_range_data.resize(i_max);
  particle_prod_ene_in_int_data.resize(i_max);
  particle_prod_ene_in_data.resize(i_max);
  particle_prod_q_value.resize(i_max);
  particle_prod_mass_coef.resize(i_max);
  particle_prod_a_pointer.resize(i_max);
  particle_prod_a_int_data.resize(i_max);
  particle_prod_a_data.resize(i_max);
  particle_prod_a_distr_data.resize(i_max);
  particle_prod_a_distr_data_integ.resize(i_max);
  particle_prod_b_pointer.resize(i_max);
  particle_prod_b_int_data.resize(i_max);
  particle_prod_b_data.resize(i_max);
  particle_prod_b_prob_data.resize(i_max);
  particle_prod_b_prob_data_integ.resize(i_max);
  particle_prod_ene_out_coef_a.resize(i_max);
  particle_prod_ene_out_coef_b.resize(i_max);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataParser::resize_particle_production_data(int i, int j_max)
{
  particle_prod_ene_flg[i].resize(j_max);
  particle_prod_ene_in_pointer[i].resize(j_max);
  particle_prod_ene_range_data[i].resize(j_max);
  particle_prod_ene_int_data[i].resize(j_max);
  particle_prod_ene_data[i].resize(j_max);
  particle_prod_ene_prob_data[i].resize(j_max);
  particle_prod_ene_in_range_data[i].resize(j_max);
  particle_prod_ene_in_int_data[i].resize(j_max);
  particle_prod_ene_in_data[i].resize(j_max);
  particle_prod_q_value[i].resize(j_max);
  particle_prod_mass_coef[i].resize(j_max);
  particle_prod_a_pointer[i].resize(j_max);
  particle_prod_a_int_data[i].resize(j_max);
  particle_prod_a_data[i].resize(j_max);
  particle_prod_a_distr_data[i].resize(j_max);
  particle_prod_a_distr_data_integ[i].resize(j_max);
  particle_prod_b_pointer[i].resize(j_max);
  particle_prod_b_int_data[i].resize(j_max);
  particle_prod_b_data[i].resize(j_max);
  particle_prod_b_prob_data[i].resize(j_max);
  particle_prod_b_prob_data_integ[i].resize(j_max);
  particle_prod_ene_out_coef_a[i].resize(j_max);
  particle_prod_ene_out_coef_b[i].resize(j_max);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataParser::set_file_name(string& str_data)
{
  set_data_flg = 0;

  file_name = str_data;

  ace_read_obj.clear();
  ace_read_obj.set_file_name(file_name);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataParser::set_text_data(vector<string>& str_vec)
{
  set_data_flg = 0;

  ace_read_obj.clear();
  ace_read_obj.set_text_data(str_vec);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

FastAceDataObject FastAceDataParser::get_ace_data_obj()
{
  if( set_data_flg == 0 )
  {
    parse_ace_format();
  }

  FastAceDataObject ace_data_obj;
  copy_fast_ace_data(ace_data_obj);

  return ace_data_obj;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

string FastAceDataParser::get_file_name()
{
  return file_name;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

