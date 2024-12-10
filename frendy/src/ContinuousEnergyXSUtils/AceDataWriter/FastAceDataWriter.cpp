#include "ContinuousEnergyXSUtils/AceDataWriter/FastAceDataWriter.hpp"

using namespace frendy;

//constructor
FastAceDataWriter::FastAceDataWriter(void)
{ 
  clear();
}

//destructor
FastAceDataWriter::~FastAceDataWriter(void)
{
  clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataWriter::clear()
{
  clear_ace_data();

  ace_wri_obj.clear();
  ace_data_obj.clear();

  pointer_data_count              = 0;
  set_data_flg                    = 0;
  set_ace_data_obj_flg            = 0;
  opt_out_type                    = ascii_mode;
  new_cummulative_angle_distr_flg = 1;
  detailed_photon_flg             = 1;

  line_no_pre                     = 0;

  ace_file_name.clear();
  discriptive_data.clear();

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

void FastAceDataWriter::clear_ace_data()
{
  clear_ace_base_data();
  clear_ace_ene_angular_distr_data();
  clear_ace_prod_distr_data();
  clear_ace_photon_data();
  clear_ace_particle_data();

  clear_ace_pointer_data();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataWriter::clear_ace_base_data()
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

void FastAceDataWriter::clear_ace_ene_angular_distr_data()
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

void FastAceDataWriter::clear_ace_prod_distr_data()
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

void FastAceDataWriter::clear_ace_photon_data()
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

void FastAceDataWriter::clear_ace_particle_data()
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

void FastAceDataWriter::clear_ace_pointer_data()
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

void FastAceDataWriter::copy_fast_ace_data()
{
  //For calc data
  sub_lib_part     = ace_data_obj.get_sub_lib_part();
  sub_lib_type     = ace_data_obj.get_sub_lib_type();
  ene_max          = ace_data_obj.get_ene_max();

  zi_vec           = ace_data_obj.get_zi_vec();
  awr_vec          = ace_data_obj.get_awr_vec();

  union_ene_grid   = ace_data_obj.get_union_ene_grid();
  gamma_product_xs = ace_data_obj.get_gamma_product_xs();

  particle_production_data      = ace_data_obj.get_particle_production_data();
  particle_production_ene_data  = ace_data_obj.get_particle_production_ene_data();

  photon_prod_yield_coef_direct = ace_data_obj.get_photon_prod_yield_coef_direct();
  photon_prod_yield_coef_given  = ace_data_obj.get_photon_prod_yield_coef_given();

  photon_xs_ene_min             = ace_data_obj.get_photon_xs_ene_min();
  photon_prod_discon_ene_data   = ace_data_obj.get_photon_prod_discon_ene_data();

  //For ace data
  copy_fast_ace_base_data();
  copy_fast_ace_ene_angular_distr_data();
  copy_fast_ace_prod_distr_data();
  copy_fast_ace_photon_data();
  copy_fast_ace_particle_data();
  copy_fast_ace_pointer_data();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataWriter::copy_fast_ace_base_data()
{
  mcnpx_mode_flg     = ace_data_obj.get_mcnpx_mode_flg();

  aw0                = ace_data_obj.get_aw0();
  tz                 = ace_data_obj.get_tz();
  izaid              = ace_data_obj.get_izaid();
  title_data         = ace_data_obj.get_title_data();
  discriptive_data   = ace_data_obj.get_discriptive_data();

  ntr                = ace_data_obj.get_ntr();
  nr                 = ace_data_obj.get_nr();
  mtntr              = ace_data_obj.get_mtntr();
  mtnr               = ace_data_obj.get_mtnr();

  nu_bar_repr_flg    = ace_data_obj.get_nu_bar_repr_flg();
  nu_d_bar_repr_flg  = ace_data_obj.get_nu_d_bar_repr_flg();
  nu_p_bar_repr_flg  = ace_data_obj.get_nu_p_bar_repr_flg();

  nu_int_data        = ace_data_obj.get_nu_int_data();
  nu_range_data      = ace_data_obj.get_nu_range_data();
  nu_d_int_data      = ace_data_obj.get_nu_d_int_data();
  nu_d_range_data    = ace_data_obj.get_nu_d_range_data();
  nu_p_int_data      = ace_data_obj.get_nu_p_int_data();
  nu_p_range_data    = ace_data_obj.get_nu_p_range_data();

  nu_data            = ace_data_obj.get_nu_data();
  nu_ene_data        = ace_data_obj.get_nu_ene_data();
  nu_d_data          = ace_data_obj.get_nu_d_data();
  nu_d_ene_data      = ace_data_obj.get_nu_d_ene_data();
  nu_p_data          = ace_data_obj.get_nu_p_data();
  nu_p_ene_data      = ace_data_obj.get_nu_p_ene_data();

  react_type_list    = ace_data_obj.get_react_type_list();
  react_type_flg     = ace_data_obj.get_react_type_flg();
  react_type_ene_sta = ace_data_obj.get_react_type_ene_sta();
  react_q_value      = ace_data_obj.get_react_q_value();
  react_xs_tot       = ace_data_obj.get_react_xs_tot();
  react_xs_cap       = ace_data_obj.get_react_xs_cap();
  react_xs_sc        = ace_data_obj.get_react_xs_sc();
  react_xs_heat      = ace_data_obj.get_react_xs_heat();
  react_xs           = ace_data_obj.get_react_xs();

  unreso_prob_tab_int_data           = ace_data_obj.get_unreso_prob_tab_int_data();
  unreso_prob_tab_inela_comp_flg     = ace_data_obj.get_unreso_prob_tab_inela_comp_flg();
  unreso_prob_tab_abs_comp_flg       = ace_data_obj.get_unreso_prob_tab_abs_comp_flg();
  unreso_prob_tab_self_shielding_flg = ace_data_obj.get_unreso_prob_tab_self_shielding_flg();

  unreso_prob_tab_ene       = ace_data_obj.get_unreso_prob_tab_ene();
  unreso_prob_tab_heat      = ace_data_obj.get_unreso_prob_tab_heat();
  unreso_prob_tab_sample_no = ace_data_obj.get_unreso_prob_tab_sample_no();
  unreso_prob_tab_table     = ace_data_obj.get_unreso_prob_tab_table();

  nu_d_decay_constant       = ace_data_obj.get_nu_d_decay_constant();
  nu_d_ene_min              = ace_data_obj.get_nu_d_ene_min();
  nu_d_ene_max              = ace_data_obj.get_nu_d_ene_max();
  nu_d_xs_part_int_data     = ace_data_obj.get_nu_d_xs_part_int_data();
  nu_d_xs_part_range_data   = ace_data_obj.get_nu_d_xs_part_range_data();
  nu_d_xs_part_ene_data     = ace_data_obj.get_nu_d_xs_part_ene_data();
  nu_d_xs_part_data         = ace_data_obj.get_nu_d_xs_part_data();
  nu_d_ene_in_int_data      = ace_data_obj.get_nu_d_ene_in_int_data();
  nu_d_ene_in_range_data    = ace_data_obj.get_nu_d_ene_in_range_data();
  nu_d_ene_out_int_data     = ace_data_obj.get_nu_d_ene_out_int_data();
  nu_d_ene_in_data          = ace_data_obj.get_nu_d_ene_in_data();
  nu_d_ene_out_data         = ace_data_obj.get_nu_d_ene_out_data();
  nu_d_ene_distr_data       = ace_data_obj.get_nu_d_ene_distr_data();
  nu_d_ene_distr_data_integ = ace_data_obj.get_nu_d_ene_distr_data_integ();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataWriter::copy_fast_ace_ene_angular_distr_data()
{
  angular_distr_type_flg        = ace_data_obj.get_angular_distr_type_flg();

  angular_distr_int_data        = ace_data_obj.get_angular_distr_int_data();
  angular_distr_ene_data        = ace_data_obj.get_angular_distr_ene_data();
  angular_distr_cos_data        = ace_data_obj.get_angular_distr_cos_data();
  angular_distr_data            = ace_data_obj.get_angular_distr_data();
  angular_distr_data_integ      = ace_data_obj.get_angular_distr_data_integ();

  ene_distr_ene_repr_flg        = ace_data_obj.get_ene_distr_ene_repr_flg();
  ene_distr_xs_part_int_data    = ace_data_obj.get_ene_distr_xs_part_int_data();
  ene_distr_xs_part_range_data  = ace_data_obj.get_ene_distr_xs_part_range_data();
  ene_distr_xs_part_ene_data    = ace_data_obj.get_ene_distr_xs_part_ene_data();
  ene_distr_xs_part_data        = ace_data_obj.get_ene_distr_xs_part_data();
  ene_distr_q_coef              = ace_data_obj.get_ene_distr_q_coef();
  ene_distr_mass_coef           = ace_data_obj.get_ene_distr_mass_coef();
  ene_distr_ene_in_int_data     = ace_data_obj.get_ene_distr_ene_in_int_data();
  ene_distr_ene_in_range_data   = ace_data_obj.get_ene_distr_ene_in_range_data();
  ene_distr_ene_in_data         = ace_data_obj.get_ene_distr_ene_in_data();
  ene_distr_ene_out_int_data    = ace_data_obj.get_ene_distr_ene_out_int_data();
  ene_distr_ene_out_ene_data    = ace_data_obj.get_ene_distr_ene_out_ene_data();
  ene_distr_ene_out_data        = ace_data_obj.get_ene_distr_ene_out_data();
  ene_distr_ene_out_data_integ  = ace_data_obj.get_ene_distr_ene_out_data_integ();
  ene_distr_upper_ene_limit     = ace_data_obj.get_ene_distr_upper_ene_limit();
  ene_distr_temp_eff_int_data   = ace_data_obj.get_ene_distr_temp_eff_int_data();
  ene_distr_temp_eff_range_data = ace_data_obj.get_ene_distr_temp_eff_range_data();
  ene_distr_watt_a_int_data     = ace_data_obj.get_ene_distr_watt_a_int_data();
  ene_distr_watt_a_range_data   = ace_data_obj.get_ene_distr_watt_a_range_data();
  ene_distr_watt_b_int_data     = ace_data_obj.get_ene_distr_watt_b_int_data();
  ene_distr_watt_b_range_data   = ace_data_obj.get_ene_distr_watt_b_range_data();
  ene_distr_temp_eff_ene_data   = ace_data_obj.get_ene_distr_temp_eff_ene_data();
  ene_distr_temp_eff_data       = ace_data_obj.get_ene_distr_temp_eff_data();
  ene_distr_watt_a_ene_data     = ace_data_obj.get_ene_distr_watt_a_ene_data();
  ene_distr_watt_a_data         = ace_data_obj.get_ene_distr_watt_a_data();
  ene_distr_watt_b_ene_data     = ace_data_obj.get_ene_distr_watt_b_ene_data();
  ene_distr_watt_b_data         = ace_data_obj.get_ene_distr_watt_b_data();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataWriter::copy_fast_ace_prod_distr_data()
{
  prod_yield_tot_int_data           = ace_data_obj.get_prod_yield_tot_int_data();
  prod_yield_tot_range_data         = ace_data_obj.get_prod_yield_tot_range_data();
  prod_yield_tot_ene_data           = ace_data_obj.get_prod_yield_tot_ene_data();
  prod_yield_tot_data               = ace_data_obj.get_prod_yield_tot_data();
  prod_distr_func_flg               = ace_data_obj.get_prod_distr_func_flg();
  prod_distr_n_body_mass            = ace_data_obj.get_prod_distr_n_body_mass();
  prod_distr_prob_data_no           = ace_data_obj.get_prod_distr_prob_data_no();
  prod_distr_n_body_particle_no     = ace_data_obj.get_prod_distr_n_body_particle_no();
  prod_distr_prob_ene_in_int_data   = ace_data_obj.get_prod_distr_prob_ene_in_int_data();
  prod_distr_prob_ene_in_range_data = ace_data_obj.get_prod_distr_prob_ene_in_range_data();
  prod_distr_prob_ene_out_int_data  = ace_data_obj.get_prod_distr_prob_ene_out_int_data();
  prod_distr_prob_ene_in_data       = ace_data_obj.get_prod_distr_prob_ene_in_data();
  prod_distr_prob_mu_int_data       = ace_data_obj.get_prod_distr_prob_mu_int_data();
  prod_distr_prob_mu_range_data     = ace_data_obj.get_prod_distr_prob_mu_range_data();
  prod_distr_prob_mu_data           = ace_data_obj.get_prod_distr_prob_mu_data();
  prod_distr_prob_mu_data_integ     = ace_data_obj.get_prod_distr_prob_mu_data_integ();
  prod_distr_prob_data              = ace_data_obj.get_prod_distr_prob_data();
  prod_distr_prob_data_integ        = ace_data_obj.get_prod_distr_prob_data_integ();
  prod_distr_prob_ene_out_data      = ace_data_obj.get_prod_distr_prob_ene_out_data();
  prod_distr_prob_coef_a            = ace_data_obj.get_prod_distr_prob_coef_a();
  prod_distr_prob_coef_b            = ace_data_obj.get_prod_distr_prob_coef_b();
  prod_distr_prob_int_vec           = ace_data_obj.get_prod_distr_prob_int_vec();
  prod_distr_prob_range_vec         = ace_data_obj.get_prod_distr_prob_range_vec();
  prod_distr_prob_mu_vec            = ace_data_obj.get_prod_distr_prob_mu_vec();
  prod_distr_prob_ene_out_vec       = ace_data_obj.get_prod_distr_prob_ene_out_vec();
  prod_distr_prob_vec               = ace_data_obj.get_prod_distr_prob_vec();
  prod_distr_prob_vec_integ         = ace_data_obj.get_prod_distr_prob_vec_integ();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataWriter::copy_fast_ace_photon_data()
{
  photon_prod_file_no                    = ace_data_obj.get_photon_prod_file_no();
  photon_prod_reaction_type              = ace_data_obj.get_photon_prod_reaction_type();
  photon_prod_reaction_type_without_xs   = ace_data_obj.get_photon_prod_reaction_type_without_xs();
  photon_prod_reaction_type_all          = ace_data_obj.get_photon_prod_reaction_type_all();
  photon_prod_binding_ene                = ace_data_obj.get_photon_prod_binding_ene();
  photon_prod_multiplicity_int_data      = ace_data_obj.get_photon_prod_multiplicity_int_data();
  photon_prod_multiplicity_range_data    = ace_data_obj.get_photon_prod_multiplicity_range_data();
  photon_prod_multiplicity_ene_data      = ace_data_obj.get_photon_prod_multiplicity_ene_data();
  photon_prod_multiplicity_data          = ace_data_obj.get_photon_prod_multiplicity_data();
  photon_prod_xs_ene_no                  = ace_data_obj.get_photon_prod_xs_ene_no();
  photon_prod_xs_non_zero_pos            = ace_data_obj.get_photon_prod_xs_non_zero_pos();
  photon_prod_xs_data                    = ace_data_obj.get_photon_prod_xs_data();
  photon_prod_distr_int_data             = ace_data_obj.get_photon_prod_distr_int_data();
  photon_prod_distr_range_data           = ace_data_obj.get_photon_prod_distr_range_data();
  photon_prod_distr_ene_data             = ace_data_obj.get_photon_prod_distr_ene_data();
  photon_prod_distr_data                 = ace_data_obj.get_photon_prod_distr_data();

  photon_angular_distr_ene_data          = ace_data_obj.get_photon_angular_distr_ene_data();
  photon_angular_distr_prob_cos_data     = ace_data_obj.get_photon_angular_distr_prob_cos_data();

  photon_energy_distr_flg                = ace_data_obj.get_photon_energy_distr_flg();
  photon_energy_distr_ene_flg            = ace_data_obj.get_photon_energy_distr_ene_flg();
  photon_energy_distr_binding_ene_data   = ace_data_obj.get_photon_energy_distr_binding_ene_data();
  photon_energy_distr_int_data           = ace_data_obj.get_photon_energy_distr_int_data();
  photon_energy_distr_range_data         = ace_data_obj.get_photon_energy_distr_range_data();
  photon_energy_distr_ene_data           = ace_data_obj.get_photon_energy_distr_ene_data();
  photon_energy_distr_prob_data          = ace_data_obj.get_photon_energy_distr_prob_data();
  photon_energy_distr_ene_in_int_data    = ace_data_obj.get_photon_energy_distr_ene_in_int_data();
  photon_energy_distr_ene_in_range_data  = ace_data_obj.get_photon_energy_distr_ene_in_range_data();
  photon_energy_distr_ene_in_data        = ace_data_obj.get_photon_energy_distr_ene_in_data();
  photon_energy_distr_weight_int_data    = ace_data_obj.get_photon_energy_distr_weight_int_data();
  photon_energy_distr_weight_ene_data    = ace_data_obj.get_photon_energy_distr_weight_ene_data();
  photon_energy_distr_weight_data        = ace_data_obj.get_photon_energy_distr_weight_data();
  photon_energy_distr_weight_data_integ  = ace_data_obj.get_photon_energy_distr_weight_data_integ();
  photon_energy_distr_gamma_mass_product = ace_data_obj.get_photon_energy_distr_gamma_mass_product();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataWriter::copy_fast_ace_particle_data()
{
  particle_prod_flg                      = ace_data_obj.get_particle_prod_flg();
  particle_prod_count                    = ace_data_obj.get_particle_prod_count();
  particle_prod_ene_sta                  = ace_data_obj.get_particle_prod_ene_sta();
  particle_prod_ene_no                   = ace_data_obj.get_particle_prod_ene_no();
  particle_prod_file_no                  = ace_data_obj.get_particle_prod_file_no();
  particle_prod_frame_flg                = ace_data_obj.get_particle_prod_frame_flg();
  particle_prod_reaction_type            = ace_data_obj.get_particle_prod_reaction_type();
  particle_prod_reaction_type_all        = ace_data_obj.get_particle_prod_reaction_type_all();
  particle_prod_xs                       = ace_data_obj.get_particle_prod_xs();
  particle_prod_heat                     = ace_data_obj.get_particle_prod_heat();
  particle_prod_distr_int_data           = ace_data_obj.get_particle_prod_distr_int_data();
  particle_prod_distr_range_data         = ace_data_obj.get_particle_prod_distr_range_data();
  particle_prod_distr_ene_data           = ace_data_obj.get_particle_prod_distr_ene_data();
  particle_prod_distr_data               = ace_data_obj.get_particle_prod_distr_data();
  particle_prod_angular_int_data         = ace_data_obj.get_particle_prod_angular_int_data();
  particle_prod_angular_ene_data         = ace_data_obj.get_particle_prod_angular_ene_data();
  particle_prod_angular_cos_data         = ace_data_obj.get_particle_prod_angular_cos_data();
  particle_prod_angular_distr_data       = ace_data_obj.get_particle_prod_angular_distr_data();
  particle_prod_angular_distr_data_integ = ace_data_obj.get_particle_prod_angular_distr_data_integ();

  particle_prod_ene_flg                  = ace_data_obj.get_particle_prod_ene_flg();
  particle_prod_q_value                  = ace_data_obj.get_particle_prod_q_value();
  particle_prod_mass_coef                = ace_data_obj.get_particle_prod_mass_coef();
  particle_prod_ene_int_data             = ace_data_obj.get_particle_prod_ene_int_data();
  particle_prod_ene_range_data           = ace_data_obj.get_particle_prod_ene_range_data();
  particle_prod_ene_data                 = ace_data_obj.get_particle_prod_ene_data();
  particle_prod_ene_prob_data            = ace_data_obj.get_particle_prod_ene_prob_data();

  particle_prod_ene_in_int_data          = ace_data_obj.get_particle_prod_ene_in_int_data();
  particle_prod_ene_in_range_data        = ace_data_obj.get_particle_prod_ene_in_range_data();
  particle_prod_ene_in_data              = ace_data_obj.get_particle_prod_ene_in_data();
  particle_prod_a_int_data               = ace_data_obj.get_particle_prod_a_int_data();
  particle_prod_a_data                   = ace_data_obj.get_particle_prod_a_data();
  particle_prod_a_distr_data             = ace_data_obj.get_particle_prod_a_distr_data();
  particle_prod_a_distr_data_integ       = ace_data_obj.get_particle_prod_a_distr_data_integ();
  particle_prod_ene_out_coef_a           = ace_data_obj.get_particle_prod_ene_out_coef_a();
  particle_prod_ene_out_coef_b           = ace_data_obj.get_particle_prod_ene_out_coef_b();

  particle_prod_b_int_data               = ace_data_obj.get_particle_prod_b_int_data();
  particle_prod_b_data                   = ace_data_obj.get_particle_prod_b_data();
  particle_prod_b_prob_data              = ace_data_obj.get_particle_prod_b_prob_data();
  particle_prod_b_prob_data_integ        = ace_data_obj.get_particle_prod_b_prob_data_integ();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataWriter::copy_fast_ace_pointer_data()
{
  len2  = ace_data_obj.get_len2();
  nes   = ace_data_obj.get_nes();
  ntrp  = ace_data_obj.get_ntrp();
  ntype = ace_data_obj.get_ntype();
  ndnf  = ace_data_obj.get_ndnf();
  esz   = ace_data_obj.get_esz();
  nu    = ace_data_obj.get_nu();
  mtr   = ace_data_obj.get_mtr();
  lqr   = ace_data_obj.get_lqr();
  tyr   = ace_data_obj.get_tyr();
  lsig  = ace_data_obj.get_lsig();
  sig   = ace_data_obj.get_sig();
  land  = ace_data_obj.get_land();
  andi  = ace_data_obj.get_andi();
  ldlw  = ace_data_obj.get_ldlw();
  dlw   = ace_data_obj.get_dlw();
  gpd   = ace_data_obj.get_gpd();
  mtrp  = ace_data_obj.get_mtrp();
  lsigp = ace_data_obj.get_lsigp();
  sigp  = ace_data_obj.get_sigp();
  landp = ace_data_obj.get_landp();
  andp  = ace_data_obj.get_andp();
  ldlwp = ace_data_obj.get_ldlwp();
  dlwp  = ace_data_obj.get_dlwp();
  yp    = ace_data_obj.get_yp();
  fis   = ace_data_obj.get_fis();
  endi  = ace_data_obj.get_endi();
  iurpt = ace_data_obj.get_iurpt();
  nud   = ace_data_obj.get_nud();
  dndat = ace_data_obj.get_dndat();
  ldnd  = ace_data_obj.get_ldnd();
  dnd   = ace_data_obj.get_dnd();
  ptype = ace_data_obj.get_ptype();
  ntro  = ace_data_obj.get_ntro();
  ploct = ace_data_obj.get_ploct();

  ene_distr_pointer                 = ace_data_obj.get_ene_distr_pointer();
  nu_d_pointer                      = ace_data_obj.get_nu_d_pointer();
  photon_prod_pointer               = ace_data_obj.get_photon_prod_pointer();
  photon_angular_pointer            = ace_data_obj.get_photon_angular_pointer();
  photon_ene_pointer                = ace_data_obj.get_photon_ene_pointer();
  photon_ene_distr_pointer          = ace_data_obj.get_photon_ene_distr_pointer();

  angular_distr_pointer             = ace_data_obj.get_angular_distr_pointer();
  ene_distr_ene_repr_end_pointer    = ace_data_obj.get_ene_distr_ene_repr_end_pointer();
  ene_distr_ene_repr_pointer        = ace_data_obj.get_ene_distr_ene_repr_pointer();
  nu_d_ene_in_pointer               = ace_data_obj.get_nu_d_ene_in_pointer();
  photon_angular_ene_pointer        = ace_data_obj.get_photon_angular_ene_pointer();
  photon_ene_weight_pointer         = ace_data_obj.get_photon_ene_weight_pointer();
  particle_prod_pointer             = ace_data_obj.get_particle_prod_pointer();
  particle_prod_distr_pointer       = ace_data_obj.get_particle_prod_distr_pointer();
  particle_prod_angular_pointer     = ace_data_obj.get_particle_prod_angular_pointer();
  particle_prod_ene_pointer         = ace_data_obj.get_particle_prod_ene_pointer();
  particle_prod_ene_in_pointer      = ace_data_obj.get_particle_prod_ene_in_pointer();
  ene_distr_ene_in_pointer          = ace_data_obj.get_ene_distr_ene_in_pointer();
  particle_prod_angular_ene_pointer = ace_data_obj.get_particle_prod_angular_ene_pointer();
  particle_prod_a_pointer           = ace_data_obj.get_particle_prod_a_pointer();
  ene_distr_ene_out_pointer         = ace_data_obj.get_ene_distr_ene_out_pointer();
  particle_prod_b_pointer           = ace_data_obj.get_particle_prod_b_pointer();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataWriter::copy_fast_ace_pointer_data(FastAceDataObject& fast_ace_data_obj)
{
  fast_ace_data_obj.set_ntr(ntr);
  fast_ace_data_obj.set_nr(nr);
  fast_ace_data_obj.set_mtntr(mtntr);
  fast_ace_data_obj.set_mtnr(mtnr);

  fast_ace_data_obj.set_len2(len2);
  fast_ace_data_obj.set_nes(nes);
  fast_ace_data_obj.set_ntrp(ntrp);
  fast_ace_data_obj.set_ntype(ntype);
  fast_ace_data_obj.set_ndnf(ndnf);
  fast_ace_data_obj.set_esz(esz);
  fast_ace_data_obj.set_nu(nu);
  fast_ace_data_obj.set_mtr(mtr);
  fast_ace_data_obj.set_lqr(lqr);
  fast_ace_data_obj.set_tyr(tyr);
  fast_ace_data_obj.set_lsig(lsig);
  fast_ace_data_obj.set_sig(sig);
  fast_ace_data_obj.set_land(land);
  fast_ace_data_obj.set_andi(andi);
  fast_ace_data_obj.set_ldlw(ldlw);
  fast_ace_data_obj.set_dlw(dlw);
  fast_ace_data_obj.set_gpd(gpd);
  fast_ace_data_obj.set_mtrp(mtrp);
  fast_ace_data_obj.set_lsigp(lsigp);
  fast_ace_data_obj.set_sigp(sigp);
  fast_ace_data_obj.set_landp(landp);
  fast_ace_data_obj.set_andp(andp);
  fast_ace_data_obj.set_ldlwp(ldlwp);
  fast_ace_data_obj.set_dlwp(dlwp);
  fast_ace_data_obj.set_yp(yp);
  fast_ace_data_obj.set_fis(fis);
  fast_ace_data_obj.set_endi(endi);
  fast_ace_data_obj.set_iurpt(iurpt);
  fast_ace_data_obj.set_nud(nud);
  fast_ace_data_obj.set_dndat(dndat);
  fast_ace_data_obj.set_ldnd(ldnd);
  fast_ace_data_obj.set_dnd(dnd);
  fast_ace_data_obj.set_ptype(ptype);
  fast_ace_data_obj.set_ntro(ntro);
  fast_ace_data_obj.set_ploct(ploct);

  fast_ace_data_obj.set_ene_distr_pointer(ene_distr_pointer);
  fast_ace_data_obj.set_nu_d_pointer(nu_d_pointer);
  fast_ace_data_obj.set_photon_prod_pointer(photon_prod_pointer);
  fast_ace_data_obj.set_photon_angular_pointer(photon_angular_pointer);
  fast_ace_data_obj.set_photon_ene_pointer(photon_ene_pointer);
  fast_ace_data_obj.set_photon_ene_distr_pointer(photon_ene_distr_pointer);

  fast_ace_data_obj.set_angular_distr_pointer(angular_distr_pointer);
  fast_ace_data_obj.set_ene_distr_ene_repr_end_pointer(ene_distr_ene_repr_end_pointer);
  fast_ace_data_obj.set_ene_distr_ene_repr_pointer(ene_distr_ene_repr_pointer);
  fast_ace_data_obj.set_nu_d_ene_in_pointer(nu_d_ene_in_pointer);
  fast_ace_data_obj.set_photon_angular_ene_pointer(photon_angular_ene_pointer);
  fast_ace_data_obj.set_photon_ene_weight_pointer(photon_ene_weight_pointer);
  fast_ace_data_obj.set_particle_prod_pointer(particle_prod_pointer);
  fast_ace_data_obj.set_particle_prod_distr_pointer(particle_prod_distr_pointer);
  fast_ace_data_obj.set_particle_prod_angular_pointer(particle_prod_angular_pointer);
  fast_ace_data_obj.set_particle_prod_ene_pointer(particle_prod_ene_pointer);
  fast_ace_data_obj.set_particle_prod_ene_in_pointer(particle_prod_ene_in_pointer);
  fast_ace_data_obj.set_ene_distr_ene_in_pointer(ene_distr_ene_in_pointer);
  fast_ace_data_obj.set_particle_prod_angular_ene_pointer(particle_prod_angular_ene_pointer);
  fast_ace_data_obj.set_particle_prod_a_pointer(particle_prod_a_pointer);
  fast_ace_data_obj.set_ene_distr_ene_out_pointer(ene_distr_ene_out_pointer);
  fast_ace_data_obj.set_particle_prod_b_pointer(particle_prod_b_pointer);

  fast_ace_data_obj.set_react_type_flg(react_type_flg);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Integer FastAceDataWriter::get_line_no()
{
  return (pointer_data_count + ace_wri_obj.get_data_count_total()) / 4;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataWriter::write_dir_data(string dir_name)
{
  ofstream fout_dir;
  fout_dir.open(dir_name.c_str());

  if( fout_dir.fail() )
  {
    string class_name = "FastAceDataWriter";
    string func_name  = "write_dir_data(string dir_name)";

    string str_data = "  Output xsdir file name : " + dir_name;

    vector<string> err_com;
    err_com.push_back("Output xsdir file can not be open.");
    err_com.push_back("Please check the file name, directory name or access authority.");
    err_com.push_back(str_data);

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  fout_dir << get_dir_data() << endl;
  fout_dir.close();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

string FastAceDataWriter::get_dir_data()
{
  if( set_data_flg != 1 )
  {
    check_set_data();
    copy_fast_ace_data();

    output_ace_format(calc_pointer_mode);
  }

  vector<string> line_data_vec;
  line_data_vec.resize(8);

  int ace_ver = ace_wri_obj.get_ace_ver(title_data);

  int width = 10;
  if( mcnpx_mode_flg != 0 )
  {
    width = 13;
  }
  if( ace_ver != 1 )
  {
    width = 24;
  }
  line_data_vec[0] = title_data[0].substr(0,width);

  ostringstream oss_aw0;
  oss_aw0.width(12);
  oss_aw0.precision(6);
  oss_aw0 << setiosflags(ios::right) << setiosflags(ios::showpoint) << fixed << aw0;
  line_data_vec[1] = oss_aw0.str();

  ostringstream oss_itype;
  oss_itype.width(2);
  oss_itype << setiosflags(ios::right) << opt_out_type;
  line_data_vec[2] = oss_itype.str();

  Integer irec1 = 1;
  if( line_no_pre != 0 )
  {
    irec1 = line_no_pre + 1;
  }
  int char_no_irec1 = ad_obj.get_digit_number(static_cast<Real8>(irec1)) + 1;
  ostringstream oss_irec1;
  oss_irec1.width(8);
  if( char_no_irec1 >= 8 )
  {
    oss_irec1.width(char_no_irec1+1);
  }
  oss_irec1 << setiosflags(ios::right) << irec1;
  line_data_vec[3] = oss_irec1.str();

  int char_no_len2 = ad_obj.get_digit_number(static_cast<Real8>(len2)) + 1;
  ostringstream oss_len2;
  oss_len2.width(8);
  if( char_no_len2 >= 8 )
  {
    oss_len2.width(char_no_len2+1);
  }
  oss_len2 << setiosflags(ios::right) << len2;
  line_data_vec[4] = oss_len2.str();

  Integer lrec = 0;
  ostringstream oss_lrec;
  oss_lrec.width(2);
  oss_lrec << setiosflags(ios::right) << lrec;
  line_data_vec[5] = oss_lrec.str();

  Integer nern = 0;
  ostringstream oss_nern;
  oss_nern.width(2);
  oss_nern << setiosflags(ios::right) << nern;
  line_data_vec[6] = oss_nern.str();

  ostringstream oss_tz;
  oss_tz.width(10);
  oss_tz.precision(3);
  oss_tz << setiosflags(ios::scientific) << setiosflags(ios::right) << setiosflags(ios::showpoint) << tz;
  line_data_vec[7] = oss_tz.str();

  string char_data = " filename route";
  if( mcnpx_mode_flg != 0 )
  {
    char_data = " file route";
  }

  string line_data = line_data_vec[0] + line_data_vec[1] + char_data         + line_data_vec[2]
                   + line_data_vec[3] + line_data_vec[4] + line_data_vec[5]  + line_data_vec[6]
                   + line_data_vec[7];
  clr_obj.clear_vec_array1_str(line_data_vec);

  if( iurpt > 0 )
  {
    line_data = line_data + " ptable";
  }

  return line_data;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataWriter::write_ace_format()
{
  if( set_data_flg == 1 )
  {
    return;
  }
  set_data_flg = 1;

  check_set_data();
  copy_fast_ace_data();

  //cout << endl;
  //cout << "----------------------------------------------------------------------------------------------------" << endl;
  //cout << endl;
  if( opt_out_type == ascii_mode )
  {
    output_ace_format(calc_pointer_mode);
  //cout << endl;
  //cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
  //cout << endl;
    output_ace_format(output_ace_format_mode);
  }
  else if( opt_out_type == binary_mode )
  {
    output_ace_format(calc_pointer_mode);
    output_ace_format_binary_mode();
  }
  //cout << endl;
  //cout << "----------------------------------------------------------------------------------------------------" << endl;
  //cout << endl;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> FastAceDataWriter::get_ace_text_data()
{
  vector<string> text_data;
  text_data.clear();

  if( set_data_flg == 1 )
  {
    return text_data;
  }
  set_data_flg = 1;

  check_set_data();
  copy_fast_ace_data();

  output_ace_format(calc_pointer_mode);
  output_ace_format(string_data_mode);

  text_data = ace_wri_obj.get_output_data();
  ace_wri_obj.clear();

  return text_data;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataWriter::get_ace_data_for_mg(vector<string>& title_vec, vector<int>& izaw_vec,
                                            vector<int>& nxs_vec, vector<int>& jxs_vec,
                                            vector<double>& xss_vec)
{
  if( set_data_flg == 1 )
  {
    return;
  }

  //Get xss_vec
  xss_vec = get_xss_data();

  //Get title_vec
  ace_wri_obj.set_output_data_opt(ace_wri_obj.string_data_mode);
  ace_wri_obj.set_title_data(mcnpx_mode_flg, aw0, tz, discriptive_data, title_data);

  title_vec = ace_wri_obj.get_output_data();
  ace_wri_obj.clear();

  //Get izaw_vec
  int i_max = static_cast<int>(zi_vec.size());
  izaw_vec.resize(i_max*2);
  for(int i=0; i<i_max; i++)
  {
    izaw_vec[2*i]   = zi_vec[i];
    izaw_vec[2*i+1] = awr_vec[i];
  }

  //Get nxs_vec
  nxs_vec.clear();
  nxs_vec.push_back(len2);
  nxs_vec.push_back(izaid);
  nxs_vec.push_back(nes);
  nxs_vec.push_back(ntr);
  nxs_vec.push_back(nr);
  nxs_vec.push_back(ntrp);
  nxs_vec.push_back(ntype);
  nxs_vec.push_back(ndnf);

  for(int i=0; i<8; i++)
  {
    nxs_vec.push_back(0);
  }

  //Get jxs_vec
  jxs_vec.clear();
  jxs_vec.push_back(esz);
  jxs_vec.push_back(nu);
  jxs_vec.push_back(mtr);
  jxs_vec.push_back(lqr);
  jxs_vec.push_back(tyr);
  jxs_vec.push_back(lsig);
  jxs_vec.push_back(sig);
  jxs_vec.push_back(land);
  jxs_vec.push_back(andi);
  jxs_vec.push_back(ldlw);
  jxs_vec.push_back(dlw);
  jxs_vec.push_back(gpd);
  jxs_vec.push_back(mtrp);
  jxs_vec.push_back(lsigp);
  jxs_vec.push_back(sigp);
  jxs_vec.push_back(landp);
  jxs_vec.push_back(andp);
  jxs_vec.push_back(ldlwp);
  jxs_vec.push_back(dlwp);
  jxs_vec.push_back(yp);
  jxs_vec.push_back(fis);
  jxs_vec.push_back(endi);
  jxs_vec.push_back(iurpt);
  jxs_vec.push_back(nud);
  jxs_vec.push_back(dndat);
  jxs_vec.push_back(ldnd);
  jxs_vec.push_back(dnd);

  for(int i=0; i<2; i++)
  {
    jxs_vec.push_back(0);
  }

  jxs_vec.push_back(ptype);
  jxs_vec.push_back(ntro);
  jxs_vec.push_back(ploct);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

vector<double> FastAceDataWriter::get_xss_data()
{
  vector<double> xss_data;
  xss_data.clear();

  if( set_data_flg == 1 )
  {
    return xss_data;
  }
  set_data_flg = 1;

  check_set_data();
  copy_fast_ace_data();

  output_ace_format(calc_pointer_mode);
  output_ace_format(real_vec_mode);

  xss_data = ace_wri_obj.get_xss_data();
  ace_wri_obj.clear();

  return xss_data;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataWriter::output_ace_format(int calc_mode)
{
  ace_wri_obj.clear();

  if( calc_mode == calc_pointer_mode )
  {
    ace_wri_obj.set_output_data_opt(ace_wri_obj.pointer_calc_mode);
    clear_ace_pointer_data();
  }
  else if( calc_mode == output_ace_format_mode )
  {
    ace_wri_obj.set_file_name(ace_file_name);
    ace_wri_obj.set_output_data_opt(ace_wri_obj.write_file_mode);
  }
  else if( calc_mode == string_data_mode )
  {
    ace_wri_obj.set_output_data_opt(ace_wri_obj.string_data_mode);
  }
  else if( calc_mode == real_vec_mode )
  {
    ace_wri_obj.set_output_data_opt(ace_wri_obj.real_vec_mode);
  }

  output_ace_format_header(calc_mode);

  pointer_data_count = ace_wri_obj.get_data_count_total();
  ace_wri_obj.clear_data_count_total();

  output_ace_format_base_data(calc_mode);
  output_ace_format_angular_distribution_data(calc_mode);
  output_ace_format_energy_distribution_data(calc_mode);
  output_ace_format_unreso_prob_table_data(calc_mode);
  output_ace_format_nu_d_data(calc_mode);
  output_ace_format_gamma_production_xs(calc_mode);
  output_ace_format_photon_production_data(calc_mode);
  output_ace_format_photon_energy_distr_data(calc_mode);
  output_ace_format_particle_production_data(calc_mode);

  //cout << endl;
  //cout << "Total line No. : " << get_line_no() << endl;

  if( calc_mode == calc_pointer_mode || calc_mode == output_ace_format_mode )
  {
    ace_wri_obj.close_file();
    if( calc_mode == calc_pointer_mode )
    {
      ace_wri_obj.set_output_data_opt(ace_wri_obj.write_file_mode);
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataWriter::output_ace_format_header(int calc_mode)
{
  //cout << "output_ace_format_header @ " << get_line_no() << endl;
  ace_wri_obj.set_title_data(mcnpx_mode_flg, aw0, tz, discriptive_data, title_data);

  ace_wri_obj.set_mat_data(zi_vec, awr_vec);

  //Output pointer data
  vector<int> pointer_vec;
  pointer_vec.push_back(len2);
  pointer_vec.push_back(izaid);
  pointer_vec.push_back(nes);
  pointer_vec.push_back(ntr);
  pointer_vec.push_back(nr);
  pointer_vec.push_back(ntrp);
  pointer_vec.push_back(ntype);
  pointer_vec.push_back(ndnf);

  for(int i=0; i<8; i++)
  {
    pointer_vec.push_back(0);
  }

  pointer_vec.push_back(esz);
  pointer_vec.push_back(nu);
  pointer_vec.push_back(mtr);
  pointer_vec.push_back(lqr);
  pointer_vec.push_back(tyr);
  pointer_vec.push_back(lsig);
  pointer_vec.push_back(sig);
  pointer_vec.push_back(land);
  pointer_vec.push_back(andi);
  pointer_vec.push_back(ldlw);
  pointer_vec.push_back(dlw);
  pointer_vec.push_back(gpd);
  pointer_vec.push_back(mtrp);
  pointer_vec.push_back(lsigp);
  pointer_vec.push_back(sigp);
  pointer_vec.push_back(landp);
  pointer_vec.push_back(andp);
  pointer_vec.push_back(ldlwp);
  pointer_vec.push_back(dlwp);
  pointer_vec.push_back(yp);
  pointer_vec.push_back(fis);
  pointer_vec.push_back(endi);
  pointer_vec.push_back(iurpt);
  pointer_vec.push_back(nud);
  pointer_vec.push_back(dndat);
  pointer_vec.push_back(ldnd);
  pointer_vec.push_back(dnd);

  for(int i=0; i<2; i++)
  {
    pointer_vec.push_back(0);
  }

  pointer_vec.push_back(ptype);
  pointer_vec.push_back(ntro);
  pointer_vec.push_back(ploct);

  ace_wri_obj.set_pointer_data(pointer_vec);
  pointer_vec.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataWriter::output_ace_format_base_data(int calc_mode)
{
  int i_max = static_cast<int>(union_ene_grid.size());
  if( i_max == 0 )
  {
    esz = 0;
    return;
  }
  //cout << "output_ace_format_base_data (ene_no = " << i_max <<  ") @ " << get_line_no() << endl;

  esz = 1;
  nes = i_max;

  ace_wri_obj.set_list_data_without_data_no(union_ene_grid);
  ace_wri_obj.set_list_data_without_data_no(react_xs_tot);
  ace_wri_obj.set_list_data_without_data_no(react_xs_cap);
  ace_wri_obj.set_list_data_without_data_no(react_xs_sc);
  ace_wri_obj.set_list_data_without_data_no(react_xs_heat);
  
  if( static_cast<int>(nu_p_data.size()) > 0 )
  {
    nu = ace_wri_obj.get_data_count_total();

    Integer data_no = static_cast<Integer>(nu_p_int_data.size() + nu_p_range_data.size()
                                             + nu_p_data.size() + nu_p_ene_data.size() + 1);
    if( nu_p_bar_repr_flg == 1 )
    {
      data_no++;  //adding number of list data
    }

    if( static_cast<int>(nu_data.size()) > 0 )
    {
      data_no *= -1;
      ace_wri_obj.set_int_data(data_no);
    }

    ace_wri_obj.set_int_data(nu_p_bar_repr_flg);
    if( nu_p_bar_repr_flg == 1 )
    {
      ace_wri_obj.set_list_data(nu_p_data);
    }
    else
    {
      ace_wri_obj.set_table_data(nu_p_range_data, nu_p_int_data, nu_p_ene_data, nu_p_data);
    }
  }

  if( static_cast<int>(nu_data.size()) > 0 )
  {
    if( nu == 0 )
    {
      nu = ace_wri_obj.get_data_count_total();
    }
    ace_wri_obj.set_int_data(nu_bar_repr_flg);
    if( nu_bar_repr_flg == 1 )
    {
      ace_wri_obj.set_list_data(nu_data);
    }
    else
    {
      ace_wri_obj.set_table_data(nu_range_data, nu_int_data, nu_ene_data, nu_data);
    }
  }

  mtr  = ace_wri_obj.get_data_count_total();
  lqr  = mtr  + ntr;
  tyr  = lqr  + ntr;
  lsig = tyr  + ntr;
  sig  = lsig + ntr;

  if( static_cast<int>(react_type_list.size()) > 0 )
  {
    ace_wri_obj.set_list_data_without_data_no(react_type_list);
    ace_wri_obj.set_list_data_without_data_no(react_q_value);
    ace_wri_obj.set_list_data_without_data_no(react_type_flg);

    i_max = static_cast<int>(react_xs.size());
    Integer ele_no = 1;
    for(int i=0; i<i_max; i++)
    {
      ace_wri_obj.set_int_data(ele_no);
      ele_no += static_cast<Integer>(react_xs[i].size()) + 2;
    }

    ele_no = 1;
    for(int i=0; i<i_max; i++)
    {
      if( react_type_list[i] == 18 )
      {
        fis = ace_wri_obj.get_data_count_total();
      }

      ele_no = static_cast<Integer>(union_ene_grid.size() - react_xs[i].size()) + 1;
      ace_wri_obj.set_int_data(ele_no);
      ace_wri_obj.set_list_data(react_xs[i]);
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataWriter::output_ace_format_angular_distribution_data(int calc_mode)
{
  land = ace_wri_obj.get_data_count_total();
  andi = land + nr + 1;

  int i_max = nr + 1;
  if( i_max == 0 )
  {
    return;
  }
  //cout << "output_ace_format_angular_distribution_data " << i_max << " @ " << get_line_no() << endl;

  if( calc_mode == calc_pointer_mode )
  {
    angular_distr_pointer.resize(i_max);
  }

  ace_wri_obj.set_list_data_without_data_no(angular_distr_type_flg);

  for(int i=0; i<i_max; i++)
  {
    if( angular_distr_type_flg[i] <= 0 )
    {
      continue;
    }

    if( i > 0 )
    {
      angular_distr_type_flg[i] = ace_wri_obj.get_data_count_total() - andi + 1;
    }
    else
    {
      angular_distr_type_flg[i] = 1;
    }

    ace_wri_obj.set_list_data(angular_distr_ene_data[i]);


    int j_max = static_cast<int>(angular_distr_ene_data[i].size());
    if( calc_mode == calc_pointer_mode )
    {
      angular_distr_pointer[i].resize(j_max);
      for(int j=0; j<j_max; j++)
      {
        angular_distr_pointer[i][j] = 0;
      }
    }
    ace_wri_obj.set_list_data_without_data_no(angular_distr_pointer[i]);

    for(int j=0; j<j_max; j++)
    {
      angular_distr_pointer[i][j] = ace_wri_obj.get_data_count_total() - andi + 1;
      if( new_cummulative_angle_distr_flg == 1 )
      {
        angular_distr_pointer[i][j] *= -1;

        ace_wri_obj.set_int_data(angular_distr_int_data[i][j]);
        ace_wri_obj.set_table_data(angular_distr_cos_data[i][j], angular_distr_data[i][j],
                                   angular_distr_data_integ[i][j]);
      }
      else
      {
        ace_wri_obj.set_list_data_without_data_no(angular_distr_cos_data[i][j]);
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataWriter::output_ace_format_energy_distribution_data(int calc_mode)
{
  ldlw = ace_wri_obj.get_data_count_total();
  dlw  = ldlw + nr;

  int i_max  = static_cast<int>(ene_distr_ene_repr_flg.size());
  if( i_max == 0 )
  {
    return;
  }
  //cout << "output_ace_format_energy_distribution_data " << i_max <<  " @ " << get_line_no() << endl;

  if( calc_mode == calc_pointer_mode )
  {
    ene_distr_pointer.resize(i_max);
    ene_distr_ene_repr_end_pointer.resize(i_max);
    ene_distr_ene_repr_pointer.resize(i_max);
    ene_distr_ene_in_pointer.resize(i_max);
    ene_distr_ene_out_pointer.resize(i_max);
    for(int i=0; i<i_max; i++)
    {
      ene_distr_pointer[i] = 0;
    }
  }
  ace_wri_obj.set_list_data_without_data_no(ene_distr_pointer);

  for(int i=0; i<i_max; i++)
  {
    if( calc_mode == calc_pointer_mode )
    {
      if( react_type_flg[i] >= 10000 || react_type_flg[i] <= -10000 )
      {
        Integer point_val  = ace_wri_obj.get_data_count_total() - dlw + 1;
                point_val += 100;
        Integer calc_chk = point_val * react_type_flg[i];
        calc_chk = calc_chk / 10000;
        if( react_type_flg[i] <= -10000 )
        {
          point_val *= -1;
        }
        react_type_flg[i] = point_val;
      }
    }

    if( static_cast<int>(prod_yield_tot_ene_data[i].size()) > 0 )
    {
      ace_wri_obj.set_table_data(prod_yield_tot_range_data[i], prod_yield_tot_int_data[i],
                                 prod_yield_tot_ene_data[i],   prod_yield_tot_data[i]);
    }

    if( calc_mode == calc_pointer_mode )
    {
      ene_distr_pointer[i] = ace_wri_obj.get_data_count_total() - dlw + 1;
    }

    int j_max = static_cast<int>(ene_distr_ene_repr_flg[i].size());
    if( calc_mode == calc_pointer_mode )
    {
      ene_distr_ene_repr_end_pointer[i].resize(j_max);
      ene_distr_ene_repr_pointer[i].resize(j_max);
      ene_distr_ene_in_pointer[i].resize(j_max);
      ene_distr_ene_out_pointer[i].resize(j_max);
      for(int j=0; j<j_max; j++)
      {
        ene_distr_ene_repr_end_pointer[i][j] = 0;
        ene_distr_ene_repr_pointer[i][j]     = 0;
      }
    }

    for(int j=0; j<j_max; j++)
    {
      if( calc_mode == calc_pointer_mode && j > 0 )
      {
        ene_distr_ene_repr_end_pointer[i][j-1] = ace_wri_obj.get_data_count_total() - dlw + 1;
      }

      ace_wri_obj.set_int_data(ene_distr_ene_repr_end_pointer[i][j]);
      ace_wri_obj.set_int_data(ene_distr_ene_repr_flg[i][j]);
      ace_wri_obj.set_int_data(ene_distr_ene_repr_pointer[i][j]);
      ace_wri_obj.set_table_data(ene_distr_xs_part_range_data[i][j], ene_distr_xs_part_int_data[i][j],
                                 ene_distr_xs_part_ene_data[i][j],   ene_distr_xs_part_data[i][j]);

      if( calc_mode == calc_pointer_mode )
      {
        ene_distr_ene_repr_pointer[i][j] = ace_wri_obj.get_data_count_total() - dlw + 1;
      }

      if( ene_distr_ene_repr_flg[i][j] == 1 )
      {
        //This flag is not available in this program
      }
      else if( ene_distr_ene_repr_flg[i][j] == 3 )
      {
        ace_wri_obj.set_real_data(ene_distr_q_coef[i][j]);
        ace_wri_obj.set_real_data(ene_distr_mass_coef[i][j]);
      }
      else if( ene_distr_ene_repr_flg[i][j] == 4 )
      {
        ace_wri_obj.set_interpolation_data(ene_distr_ene_in_range_data[i][j], ene_distr_ene_in_int_data[i][j]);
        ace_wri_obj.set_list_data(ene_distr_ene_in_data[i][j]);

        int k_max = static_cast<int>(ene_distr_ene_in_data[i][j].size());
        if( calc_mode == calc_pointer_mode )
        { 
          ene_distr_ene_in_pointer[i][j].resize(k_max);
          for(int k=0; k<k_max; k++)
          {
            ene_distr_ene_in_pointer[i][j][k] = 0;
          }
        }
        ace_wri_obj.set_list_data_without_data_no(ene_distr_ene_in_pointer[i][j]);

        for(int k=0; k<k_max; k++)
        {
          ene_distr_ene_in_pointer[i][j][k] = ace_wri_obj.get_data_count_total() - dlw + 1;

          ace_wri_obj.set_int_data(ene_distr_ene_out_int_data[i][j][k]);
          ace_wri_obj.set_table_data(ene_distr_ene_out_ene_data[i][j][k], ene_distr_ene_out_data[i][j][k],
                                     ene_distr_ene_out_data_integ[i][j][k]);
        }
      }
      else if( ene_distr_ene_repr_flg[i][j] == 5 )
      {
        //This flag is not available in this program
      }
      else if( ene_distr_ene_repr_flg[i][j] == 7 || ene_distr_ene_repr_flg[i][j] == 9 )
      {
        ace_wri_obj.set_table_data(ene_distr_temp_eff_range_data[i][j], ene_distr_temp_eff_int_data[i][j],
                                   ene_distr_temp_eff_ene_data[i][j],   ene_distr_temp_eff_data[i][j]);
        ace_wri_obj.set_real_data(ene_distr_upper_ene_limit[i][j]);
      }
      else if( ene_distr_ene_repr_flg[i][j] == 11 )
      {
        ace_wri_obj.set_table_data(ene_distr_watt_a_range_data[i][j], ene_distr_watt_a_int_data[i][j],
                                   ene_distr_watt_a_ene_data[i][j],   ene_distr_watt_a_data[i][j]);
        ace_wri_obj.set_table_data(ene_distr_watt_b_range_data[i][j], ene_distr_watt_b_int_data[i][j],
                                   ene_distr_watt_b_ene_data[i][j],   ene_distr_watt_b_data[i][j]);
        ace_wri_obj.set_real_data(ene_distr_upper_ene_limit[i][j]);
      }
      else if( ene_distr_ene_repr_flg[i][j] == 44 || ene_distr_ene_repr_flg[i][j] == 61 )
      {
        ace_wri_obj.set_interpolation_data(prod_distr_prob_ene_in_range_data[i][j],
                                           prod_distr_prob_ene_in_int_data[i][j]);
        ace_wri_obj.set_list_data(prod_distr_prob_ene_in_data[i][j]);

        int k_max = static_cast<int>(prod_distr_prob_ene_in_data[i][j].size());
        if( calc_mode == calc_pointer_mode )
        {
          ene_distr_ene_in_pointer[i][j].resize(k_max);
          ene_distr_ene_out_pointer[i][j].resize(k_max);
          for(int k=0; k<k_max; k++)
          {
            ene_distr_ene_in_pointer[i][j][k] = 0;
          }
        }
        ace_wri_obj.set_list_data_without_data_no(ene_distr_ene_in_pointer[i][j]);

        for(int k=0; k<k_max; k++)
        {
          ene_distr_ene_in_pointer[i][j][k] = ace_wri_obj.get_data_count_total() - dlw + 1;

          ace_wri_obj.set_int_data(prod_distr_prob_ene_out_int_data[i][j][k]);
          ace_wri_obj.set_table_data(prod_distr_prob_ene_out_data[i][j][k],
                                     prod_distr_prob_mu_data[i][j][k],
                                     prod_distr_prob_mu_data_integ[i][j][k]);

          if( ene_distr_ene_repr_flg[i][j] == 44 )
          {
            ace_wri_obj.set_list_data_without_data_no(prod_distr_prob_coef_a[i][j][k]);
            ace_wri_obj.set_list_data_without_data_no(prod_distr_prob_coef_b[i][j][k]);
          }
          else if( ene_distr_ene_repr_flg[i][j] == 61 )
          {
            int l_max = static_cast<int>(prod_distr_prob_ene_out_data[i][j][k].size());
            if( calc_mode == calc_pointer_mode )
            {
              ene_distr_ene_out_pointer[i][j][k].resize(l_max);
              for(int l=0; l<l_max; l++)
              {
                ene_distr_ene_out_pointer[i][j][k][l] = 0;
              }
            }
            ace_wri_obj.set_list_data_without_data_no(ene_distr_ene_out_pointer[i][j][k]);

            for(int l=0; l<l_max; l++)
            {
              ene_distr_ene_out_pointer[i][j][k][l] = ace_wri_obj.get_data_count_total() - dlw + 1;

              ace_wri_obj.set_int_data(prod_distr_prob_int_vec[i][j][k][l][0]);
              ace_wri_obj.set_table_data(prod_distr_prob_mu_vec[i][j][k][l],
                                         prod_distr_prob_vec[i][j][k][l],
                                         prod_distr_prob_vec_integ[i][j][k][l]);
            }
          }
        }
      }
      else if( ene_distr_ene_repr_flg[i][j] == 66 )
      {
        ace_wri_obj.set_int_data(prod_distr_n_body_particle_no[i][j]);
        ace_wri_obj.set_real_data(prod_distr_n_body_mass[i][j]);
        ace_wri_obj.set_int_data(prod_distr_prob_data_no[i][j]);
        ace_wri_obj.set_table_data(prod_distr_prob_mu_data[i][j][0],
                                   prod_distr_prob_data[i][j][0],
                                   prod_distr_prob_data_integ[i][j][0]);
      }
      else if( ene_distr_ene_repr_flg[i][j] == 67 )
      {
        ace_wri_obj.set_interpolation_data(prod_distr_prob_ene_in_range_data[i][j],
                                           prod_distr_prob_ene_in_int_data[i][j]);
        ace_wri_obj.set_list_data(prod_distr_prob_ene_in_data[i][j]);

        int k_max = static_cast<int>(prod_distr_prob_ene_in_data[i][j].size());
        if( calc_mode == calc_pointer_mode )
        {
          ene_distr_ene_in_pointer[i][j].resize(k_max);
          ene_distr_ene_out_pointer[i][j].resize(k_max);
          for(int k=0; k<k_max; k++)
          {
            ene_distr_ene_in_pointer[i][j][k] = 0;
          }
        }
        ace_wri_obj.set_list_data_without_data_no(ene_distr_ene_in_pointer[i][j]);

        for(int k=0; k<k_max; k++)
        {
          ene_distr_ene_in_pointer[i][j][k] = ace_wri_obj.get_data_count_total() - dlw + 1;

          ace_wri_obj.set_int_data(prod_distr_prob_mu_int_data[i][j][k][0]);
          ace_wri_obj.set_list_data(prod_distr_prob_mu_data[i][j][k]);

          int l_max = static_cast<int>(prod_distr_prob_mu_data[i][j][k].size());
          if( calc_mode == calc_pointer_mode )
          {
            ene_distr_ene_out_pointer[i][j][k].resize(l_max);
            for(int l=0; l<l_max; l++)
            {
              ene_distr_ene_out_pointer[i][j][k][l] = 0;
            }
          }
          ace_wri_obj.set_list_data_without_data_no(ene_distr_ene_out_pointer[i][j][k]);

          for(int l=0; l<l_max; l++)
          {
            ene_distr_ene_out_pointer[i][j][k][l] = ace_wri_obj.get_data_count_total() - dlw + 1;

            ace_wri_obj.set_int_data(prod_distr_prob_int_vec[i][j][k][l][0]);
            ace_wri_obj.set_table_data(prod_distr_prob_ene_out_vec[i][j][k][l],
                                       prod_distr_prob_vec[i][j][k][l],
                                       prod_distr_prob_vec_integ[i][j][k][l]);
          }
        }
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataWriter::output_ace_format_unreso_prob_table_data(int calc_mode)
{
  Integer table_no = static_cast<Integer>(unreso_prob_tab_table.size());
  if( table_no == 0 )
  {
    return;
  }
  //cout << "output_ace_format_unreso_prob_table_data " << table_no << " @ " << get_line_no() << endl;

  iurpt = ace_wri_obj.get_data_count_total();

  Integer bin_no = static_cast<Integer>(unreso_prob_tab_sample_no[0].size());
  ace_wri_obj.set_int_data(table_no);
  ace_wri_obj.set_int_data(bin_no);

  ace_wri_obj.set_int_data(unreso_prob_tab_int_data); //int_lin_lin?
  ace_wri_obj.set_int_data(unreso_prob_tab_inela_comp_flg);
  ace_wri_obj.set_int_data(unreso_prob_tab_abs_comp_flg);

  ace_wri_obj.set_int_data(unreso_prob_tab_self_shielding_flg);

  ace_wri_obj.set_list_data_without_data_no(unreso_prob_tab_ene);
  for(int i=0; i<static_cast<int>(table_no); i++)
  {
    ace_wri_obj.set_list_data_without_data_no(unreso_prob_tab_sample_no[i]);

    int j_max = static_cast<int>(unreso_prob_tab_table[i].size());
    if( j_max != xs_type_no )
    {
      string class_name = "FastAceDataWriter";
      string func_name  = "output_ace_format_unreso_prob_table_data";

      ostringstream oss01, oss02, oss03, oss04, oss05;
      oss01 << i+1;
      oss02 << table_no;
      oss03 << bin_no;
      oss04 << xs_type_no;
      oss05 << j_max;
      string str_data01 = "position                                : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "bin number                              : " + oss03.str();
      string str_data03 = "xs_type_no                              : " + oss04.str();
      string str_data04 = "Data number of unreso_prob_tab_table[i] : " + oss05.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back(str_data04);
      err_com.push_back("The data number of unreso_prob_tab_table[i] is not identical to xs_type_no.");
      err_com.push_back("This probability table data may be incorrect.");
      if( j_max == bin_no )
      {
        err_com.push_back("Bin number should be set as the data number of unreso_prob_tab_table[i][j].");
      }
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    //Check the order of total probability table
    int k_max = static_cast<int>(unreso_prob_tab_table[i][total_xs].size());
    for(int k=1; k<k_max; k++)
    {
      if( unreso_prob_tab_table[i][total_xs][k] - unreso_prob_tab_table[i][total_xs][k-1] < 0.0 )
      {
        string class_name = "FastAceDataWriter";
        string func_name  = "output_ace_format_unreso_prob_table_data";

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
        oss02 << table_no;
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

    for(int j=0; j<j_max; j++) //xs_type_no
    {
      ace_wri_obj.set_list_data_without_data_no(unreso_prob_tab_table[i][j]); //bin_no
    }
    ace_wri_obj.set_list_data_without_data_no(unreso_prob_tab_heat[i]);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataWriter::output_ace_format_nu_d_data(int calc_mode)
{
  int i_max = static_cast<int>(nu_d_decay_constant.size());
  if( i_max == 0 )
  {
    return;
  }
  //cout << "output_ace_format_nu_d_data " << i_max << "@ " << get_line_no() << endl;

  nud  = ace_wri_obj.get_data_count_total();
  ndnf = i_max;

  ace_wri_obj.set_int_data(nu_d_bar_repr_flg);
  ace_wri_obj.set_table_data(nu_d_range_data, nu_d_int_data, nu_d_ene_data, nu_d_data);

  dndat = ace_wri_obj.get_data_count_total();

  for(int i=0; i<i_max; i++)
  {
    ace_wri_obj.set_real_data(nu_d_decay_constant[i]);
    ace_wri_obj.set_table_data(nu_d_xs_part_range_data[i], nu_d_xs_part_int_data[i],
                               nu_d_xs_part_ene_data[i],   nu_d_xs_part_data[i]);
  }

  ldnd = ace_wri_obj.get_data_count_total();
  dnd  = ldnd + ndnf;

  if( calc_mode == calc_pointer_mode )
  {
    nu_d_pointer.resize(i_max);
    nu_d_ene_in_pointer.resize(i_max);
    for(int i=0; i<i_max; i++)
    {
      nu_d_pointer[i] = 0;
    }
  }
  ace_wri_obj.set_list_data_without_data_no(nu_d_pointer);

  for(int i=0; i<i_max; i++)
  {
    nu_d_pointer[i] = ace_wri_obj.get_data_count_total() - dnd + 1;

    ace_wri_obj.set_int_data(0);
    ace_wri_obj.set_int_data(4);
    ace_wri_obj.set_int_data(nu_d_pointer[i] + 9);
    ace_wri_obj.set_int_data(0);

    ace_wri_obj.set_int_data(2);
    ace_wri_obj.set_real_data(nu_d_ene_min[i]);
    ace_wri_obj.set_real_data(nu_d_ene_max[i]);
    ace_wri_obj.set_real_data(1.0);
    ace_wri_obj.set_real_data(1.0);

    ace_wri_obj.set_interpolation_data(nu_d_ene_in_range_data[i], nu_d_ene_in_int_data[i]);
    ace_wri_obj.set_list_data(nu_d_ene_in_data[i]);

    int j_max = static_cast<int>(nu_d_ene_in_data[i].size());
    if( calc_mode == calc_pointer_mode )
    {
      nu_d_ene_in_pointer[i].resize(j_max);
      for(int j=0; j<j_max; j++)
      {
        nu_d_ene_in_pointer[i][j] = 0;
      }
    }
    ace_wri_obj.set_list_data_without_data_no(nu_d_ene_in_pointer[i]);

    for(int j=0; j<j_max; j++)
    {
      nu_d_ene_in_pointer[i][j] = ace_wri_obj.get_data_count_total() - dnd + 1;

      ace_wri_obj.set_int_data(nu_d_ene_out_int_data[i][j]);
      ace_wri_obj.set_table_data(nu_d_ene_out_data[i][j], nu_d_ene_distr_data[i][j],
                                                          nu_d_ene_distr_data_integ[i][j]);
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataWriter::output_ace_format_gamma_production_xs(int calc_mode)
{
  if( detailed_photon_flg != 1 )
  {
    gpd = 0;

    if( calc_mode != calc_pointer_mode )
    {
      string class_name = "FastAceDataWriter";
      string func_name  = "output_ace_format_gamma_production_xs(int calc_mode)";
      vector<string> err_com;
      err_com.push_back("When the photon prodcution file is not observed in the ACE file,");
      err_com.push_back("MCNP read the gendf data file after gamma_product_xs.");
      err_com.push_back("To avoid this probrem, when the photon prodction file is not output,");
      err_com.push_back("i.e., detailed_photon_flg is 0, output of gpd block is skipped");
      err_obj.output_caution(class_name, func_name, err_com);
    }

    return;
  }

  int i_max = static_cast<int>(gamma_product_xs.size());
  if( i_max == 0 )
  {
    return;
  }
  //cout << "output_ace_format_gamma_product_xs " << i_max << " @ " << get_line_no() << endl;

  gpd = ace_wri_obj.get_data_count_total();

  ace_wri_obj.set_list_data_without_data_no(gamma_product_xs);

  //For gendf data file
  //Modify multigroup photon data in GENDF file.
  //The GENDF file is not available in FRENDY.
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataWriter::output_ace_format_photon_production_data(int calc_mode)
{
  int i_max = static_cast<int>(photon_prod_file_no.size());
  if( i_max == 0 )
  {
    return;
  }
  //cout << "output_ace_format_photon_production_data " << i_max << " @ " << get_line_no() << endl;

  mtrp  = ace_wri_obj.get_data_count_total();
  ntrp  = i_max;
  lsigp = mtrp  + ntrp;
  sigp  = lsigp + ntrp;

  ace_wri_obj.set_list_data_without_data_no(photon_prod_reaction_type_all);
  
  if( calc_mode == calc_pointer_mode )
  {
    photon_prod_pointer.resize(i_max);
    for(int i=0; i<i_max; i++)
    {
      photon_prod_pointer[i] = 0;
    }
  }
  ace_wri_obj.set_list_data_without_data_no(photon_prod_pointer);

  for(int i=0; i<i_max; i++)
  {
    photon_prod_pointer[i] = ace_wri_obj.get_data_count_total() - sigp + 1;

    ace_wri_obj.set_int_data(photon_prod_file_no[i]);

    if( photon_prod_file_no[i] != 12 && photon_prod_file_no[i] != 16 )
    {
      ace_wri_obj.set_int_data(photon_prod_xs_non_zero_pos[i][0]);
      ace_wri_obj.set_int_data(photon_prod_xs_non_zero_pos[i][1]);
      ace_wri_obj.set_list_data_without_data_no(photon_prod_xs_data[i]);
    }
    else
    {
      ace_wri_obj.set_int_data(photon_prod_reaction_type[i]);
      if( photon_prod_file_no[i] == 12 )
      {
        ace_wri_obj.set_table_data(photon_prod_multiplicity_range_data[i],
                                   photon_prod_multiplicity_int_data[i],
                                   photon_prod_multiplicity_ene_data[i],
                                   photon_prod_multiplicity_data[i]);
      }
      else
      {
        ace_wri_obj.set_table_data(photon_prod_distr_range_data[i],
                                   photon_prod_distr_int_data[i],
                                   photon_prod_distr_ene_data[i],
                                   photon_prod_distr_data[i]);
      }
    }
  }

  landp = ace_wri_obj.get_data_count_total();
  andp  = landp + ntrp;

  if( calc_mode == calc_pointer_mode )
  {
    photon_angular_pointer.resize(i_max);
    photon_angular_ene_pointer.resize(i_max);
    for(int i=0; i<i_max; i++)
    {
      photon_angular_pointer[i] = 0;
    }
  }
  ace_wri_obj.set_list_data_without_data_no(photon_angular_pointer);

  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(photon_angular_distr_ene_data[i].size());
    if( j_max == 0 )
    {
      continue;
    }

    photon_angular_pointer[i] = ace_wri_obj.get_data_count_total() - andp + 1;

    ace_wri_obj.set_list_data(photon_angular_distr_ene_data[i]);

    if( calc_mode == calc_pointer_mode )
    {
      photon_angular_ene_pointer[i].resize(j_max);
      for(int j=0; j<j_max; j++)
      {
        photon_angular_ene_pointer[i][j] = 0;
      }
    }
    ace_wri_obj.set_list_data_without_data_no(photon_angular_ene_pointer[i]);

    for(int j=0; j<j_max; j++)
    {
      if( static_cast<int>(photon_angular_distr_prob_cos_data[i][j].size()) > 0 )
      {
        photon_angular_ene_pointer[i][j] = ace_wri_obj.get_data_count_total() - andp + 1;
        ace_wri_obj.set_list_data_without_data_no(photon_angular_distr_prob_cos_data[i][j]);
      }
      else
      {
        photon_angular_ene_pointer[i][j] = 0;
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataWriter::output_ace_format_photon_energy_distr_data(int calc_mode)
{
  int i_max = static_cast<int>(photon_energy_distr_flg.size());
  if( i_max == 0 )
  {
    return;
  }
  //cout << "output_ace_format_photon_energy_distr_data " << i_max << " @ " << get_line_no() << endl;

  ldlwp = ace_wri_obj.get_data_count_total();
  dlwp  = ldlwp + i_max;

  if( calc_mode == calc_pointer_mode )
  {
    photon_ene_pointer.resize(i_max);
    photon_ene_distr_pointer.resize(i_max);
    photon_ene_weight_pointer.resize(i_max);
    for(int i=0; i<i_max; i++)
    {
      photon_ene_pointer[i] = 0;
      photon_ene_distr_pointer[i] = 0;
    }
  }
  ace_wri_obj.set_list_data_without_data_no(photon_ene_pointer);

  for(int i=0; i<i_max; i++)
  {
    photon_ene_pointer[i] = ace_wri_obj.get_data_count_total() - dlwp + 1;

    ace_wri_obj.set_int_data(0);
    ace_wri_obj.set_int_data(photon_energy_distr_flg[i]);
    ace_wri_obj.set_int_data(photon_ene_distr_pointer[i]);
    ace_wri_obj.set_table_data(photon_energy_distr_range_data[i], photon_energy_distr_int_data[i],
                               photon_energy_distr_ene_data[i],   photon_energy_distr_prob_data[i]);

    photon_ene_distr_pointer[i] = ace_wri_obj.get_data_count_total() - dlwp + 1;

    if( photon_energy_distr_flg[i] == 1 )
    {
      //This flag is not available in this program
    }
    else if( photon_energy_distr_flg[i] == 2 )
    {
      ace_wri_obj.set_int_data(photon_energy_distr_ene_flg[i]);
      ace_wri_obj.set_real_data(photon_energy_distr_binding_ene_data[i]);
    }
    else if( photon_energy_distr_flg[i] == 4 || photon_energy_distr_flg[i] == 44 )
    {
      ace_wri_obj.set_interpolation_data(photon_energy_distr_ene_in_range_data[i],
                                         photon_energy_distr_ene_in_int_data[i]);
      ace_wri_obj.set_list_data(photon_energy_distr_ene_in_data[i]);

      int j_max = static_cast<int>(photon_energy_distr_ene_in_data[i].size());
      if( calc_mode == calc_pointer_mode )
      {
        photon_ene_weight_pointer[i].resize(j_max);
        for(int j=0; j<j_max; j++)
        {
          photon_ene_weight_pointer[i][j] = 0;
        }
      }
      ace_wri_obj.set_list_data_without_data_no(photon_ene_weight_pointer[i]);

      for(int j=0; j<j_max; j++)
      {
        photon_ene_weight_pointer[i][j] = ace_wri_obj.get_data_count_total() - dlwp + 1;

        ace_wri_obj.set_int_data(photon_energy_distr_weight_int_data[i][j]);
        ace_wri_obj.set_table_data(photon_energy_distr_weight_ene_data[i][j],
                                   photon_energy_distr_weight_data[i][j],
                                   photon_energy_distr_weight_data_integ[i][j]);
      }
    }
  }

  yp = ace_wri_obj.get_data_count_total();
  ace_wri_obj.set_list_data(photon_prod_reaction_type_without_xs);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataWriter::output_ace_format_particle_production_data(int calc_mode)
{
  endi = ace_wri_obj.get_data_count_total() - 1;
  len2 = endi;

  int i_max = static_cast<int>(particle_prod_flg.size());
  if( i_max == 0 )
  {
    return;
  }
  //cout << "output_ace_format_particle_production_data " << i_max << " @ " << get_line_no() << endl;

  ptype = endi + 1;
  ntype = i_max;
  ntro  = ptype + ntype;
  ploct = ntro  + ntype;

  ace_wri_obj.set_list_data_without_data_no(particle_prod_flg);
  ace_wri_obj.set_list_data_without_data_no(particle_prod_count);

  int case_no = 10; //hpd, mtrh, tyrh, lsigh, sigh, landh, andh, ldlwh, dlwh, yh
  if( calc_mode == calc_pointer_mode )
  {
    particle_prod_pointer.resize(i_max);
    for(int i=0; i<i_max; i++)
    {
      particle_prod_pointer[i].resize(case_no);
      for(int n=0; n<case_no; n++)
      {
        particle_prod_pointer[i][n] = 0;
      }
    }

    particle_prod_distr_pointer.resize(i_max);
    particle_prod_angular_pointer.resize(i_max);
    particle_prod_angular_ene_pointer.resize(i_max);
    particle_prod_ene_pointer.resize(i_max);
    particle_prod_ene_in_pointer.resize(i_max);
    particle_prod_a_pointer.resize(i_max);
    particle_prod_b_pointer.resize(i_max);
  }
  for(int i=0; i<i_max; i++)
  {
    ace_wri_obj.set_list_data_without_data_no(particle_prod_pointer[i]);
  }

  for(int i=0; i<i_max; i++)
  {
    particle_prod_pointer[i][0] = ace_wri_obj.get_data_count_total(); //hpd

    ace_wri_obj.set_int_data(particle_prod_ene_sta[i]);
    ace_wri_obj.set_int_data(particle_prod_ene_no[i]);
    ace_wri_obj.set_list_data_without_data_no(particle_prod_xs[i]);
    ace_wri_obj.set_list_data_without_data_no(particle_prod_heat[i]);

    particle_prod_pointer[i][1] = ace_wri_obj.get_data_count_total();  //mtrh

    ace_wri_obj.set_list_data_without_data_no(particle_prod_reaction_type_all[i]);
    ace_wri_obj.set_list_data_without_data_no(particle_prod_frame_flg[i]);

    int j_max = static_cast<int>(particle_prod_reaction_type_all[i].size());
    particle_prod_pointer[i][2] = particle_prod_pointer[i][1] + j_max; //tyrh
    particle_prod_pointer[i][3] = particle_prod_pointer[i][2] + j_max; //lsigh
    particle_prod_pointer[i][4] = particle_prod_pointer[i][3] + j_max; //sigh

    if( calc_mode == calc_pointer_mode )
    {
      particle_prod_distr_pointer[i].resize(j_max);
      for(int j=0; j<j_max; j++)
      {
        particle_prod_distr_pointer[i][j] = 0;
      }
    }
    ace_wri_obj.set_list_data_without_data_no(particle_prod_distr_pointer[i]);

    for(int j=0; j<j_max; j++)
    {
      particle_prod_distr_pointer[i][j] = ace_wri_obj.get_data_count_total()
                                        - particle_prod_pointer[i][4] + 1;

      ace_wri_obj.set_int_data(particle_prod_file_no[i][j]);
      ace_wri_obj.set_int_data(particle_prod_reaction_type[i][j]);

      ace_wri_obj.set_table_data(particle_prod_distr_range_data[i][j], particle_prod_distr_int_data[i][j],
                                 particle_prod_distr_ene_data[i][j],   particle_prod_distr_data[i][j]);
    }

    particle_prod_pointer[i][5] = ace_wri_obj.get_data_count_total();  //landh
    particle_prod_pointer[i][6] = particle_prod_pointer[i][5] + j_max; //andh
    if( calc_mode == calc_pointer_mode )
    {
      particle_prod_angular_pointer[i].resize(j_max);
      particle_prod_angular_ene_pointer[i].resize(j_max);
      for(int j=0; j<j_max; j++)
      {
        particle_prod_angular_pointer[i][j] = 0;
      }
    }
    ace_wri_obj.set_list_data_without_data_no(particle_prod_angular_pointer[i]);

    for(int j=0; j<j_max; j++)
    {
      particle_prod_angular_pointer[i][j] = -1;
      if( particle_prod_ene_flg[i][j] == 4 )
      {
        particle_prod_angular_pointer[i][j] = 0;
      }
      else if( particle_prod_ene_flg[i][j] == 33 )
      {
        if( static_cast<int>(particle_prod_ene_data[i][j].size()) == 2 &&
            static_cast<int>(particle_prod_ene_prob_data[i][j].size()) == 2 )
        {
          if( fabs(particle_prod_ene_data[i][j][0])      < min_value &&
              fabs(particle_prod_ene_data[i][j][1])      < min_value &&
              fabs(particle_prod_ene_prob_data[i][j][0]) < min_value &&
              fabs(particle_prod_ene_prob_data[i][j][1]) < min_value ) 
          {
            particle_prod_angular_pointer[i][j] = 0;
          }
        }
      }

      if( static_cast<int>(particle_prod_angular_ene_data[i].size()) <= j )
      {
        continue;
      }
      else if( static_cast<int>(particle_prod_angular_ene_data[i][j].size()) == 0 )
      {
        continue;
      }

      particle_prod_angular_pointer[i][j] = ace_wri_obj.get_data_count_total()
                                          - particle_prod_pointer[i][6] + 1;

      ace_wri_obj.set_list_data(particle_prod_angular_ene_data[i][j]);

      int k_max = static_cast<int>(particle_prod_angular_ene_data[i][j].size());
      if( calc_mode == calc_pointer_mode )
      {
        particle_prod_angular_ene_pointer[i][j].resize(k_max);
        for(int k=0; k<k_max; k++)
        {
          particle_prod_angular_ene_pointer[i][j][k] = 0;
        }
      }
      ace_wri_obj.set_list_data_without_data_no(particle_prod_angular_ene_pointer[i][j]);

      for(int k=0; k<k_max; k++)
      {
        particle_prod_angular_ene_pointer[i][j][k] = -1 * (ace_wri_obj.get_data_count_total()
                                                        - particle_prod_pointer[i][6] + 1);

        ace_wri_obj.set_int_data(particle_prod_angular_int_data[i][j][k]);
        ace_wri_obj.set_table_data(particle_prod_angular_cos_data[i][j][k],
                                   particle_prod_angular_distr_data[i][j][k],
                                   particle_prod_angular_distr_data_integ[i][j][k]);
      }
    }

    particle_prod_pointer[i][7] = ace_wri_obj.get_data_count_total();  //ldlwh
    particle_prod_pointer[i][8] = particle_prod_pointer[i][7] + j_max; //dlwh
    if( calc_mode == calc_pointer_mode )
    {
      particle_prod_ene_pointer[i].resize(j_max);
      particle_prod_ene_in_pointer[i].resize(j_max);
      particle_prod_a_pointer[i].resize(j_max);
      particle_prod_b_pointer[i].resize(j_max);
      for(int j=0; j<j_max; j++)
      {
        particle_prod_ene_pointer[i][j]    = 0;
        particle_prod_ene_in_pointer[i][j] = 0;
      }
    }
    ace_wri_obj.set_list_data_without_data_no(particle_prod_ene_pointer[i]);

    for(int j=0; j<j_max; j++)
    {
      particle_prod_ene_pointer[i][j] = -1;
      if( static_cast<int>(particle_prod_ene_data[i].size()) == 0 )
      {
        continue;
      }
      else if( static_cast<int>(particle_prod_ene_data[i][j].size()) == 0 )
      {
        continue;
      }

      particle_prod_ene_pointer[i][j] = ace_wri_obj.get_data_count_total()
                                      - particle_prod_pointer[i][8] + 1;

      ace_wri_obj.set_int_data(0);
      ace_wri_obj.set_int_data(particle_prod_ene_flg[i][j]);
  
      ace_wri_obj.set_int_data(particle_prod_ene_in_pointer[i][j]);
      ace_wri_obj.set_table_data(particle_prod_ene_range_data[i][j], particle_prod_ene_int_data[i][j],
                                 particle_prod_ene_data[i][j],       particle_prod_ene_prob_data[i][j]);

      particle_prod_ene_in_pointer[i][j] = ace_wri_obj.get_data_count_total()
                                         - particle_prod_pointer[i][8] + 1;

      if( particle_prod_ene_flg[i][j] ==  4 || particle_prod_ene_flg[i][j] == 44 ||
          particle_prod_ene_flg[i][j] == 61)
      {
        ace_wri_obj.set_interpolation_data(particle_prod_ene_in_range_data[i][j],
                                           particle_prod_ene_in_int_data[i][j]);
        ace_wri_obj.set_list_data(particle_prod_ene_in_data[i][j]);

        int k_max = static_cast<int>(particle_prod_ene_in_data[i][j].size());
        if( calc_mode == calc_pointer_mode )
        {
          particle_prod_a_pointer[i][j].resize(k_max);
          particle_prod_b_pointer[i][j].resize(k_max);
          for(int k=0; k<k_max; k++)
          {
            particle_prod_a_pointer[i][j][k] = 0;
          }
        }
        ace_wri_obj.set_list_data_without_data_no(particle_prod_a_pointer[i][j]);

        for(int k=0; k<k_max; k++)
        {
          particle_prod_a_pointer[i][j][k] = ace_wri_obj.get_data_count_total()
                                           - particle_prod_pointer[i][8] + 1;
          ace_wri_obj.set_int_data(particle_prod_a_int_data[i][j][k]);
          ace_wri_obj.set_table_data(particle_prod_a_data[i][j][k],
                                     particle_prod_a_distr_data[i][j][k],
                                     particle_prod_a_distr_data_integ[i][j][k]);

          if( particle_prod_ene_flg[i][j] == 44 )
          {
            ace_wri_obj.set_list_data_without_data_no(particle_prod_ene_out_coef_a[i][j][k]);
            ace_wri_obj.set_list_data_without_data_no(particle_prod_ene_out_coef_b[i][j][k]);
          }
          else if( particle_prod_ene_flg[i][j] == 61 )
          {
            int l_max = static_cast<int>(particle_prod_a_data[i][j][k].size());
            if( calc_mode == calc_pointer_mode )
            {
              particle_prod_b_pointer[i][j][k].resize(l_max);
              for(int l=0; l<l_max; l++)
              {
                particle_prod_b_pointer[i][j][k][l] = 0;
              }
            }
            ace_wri_obj.set_list_data_without_data_no(particle_prod_b_pointer[i][j][k]);

            for(int l=0; l<l_max; l++)
            {
              particle_prod_b_pointer[i][j][k][l] = ace_wri_obj.get_data_count_total()
                                                  - particle_prod_pointer[i][8] + 1;

              ace_wri_obj.set_int_data(particle_prod_b_int_data[i][j][k][l]);
              ace_wri_obj.set_table_data(particle_prod_b_data[i][j][k][l],
                                         particle_prod_b_prob_data[i][j][k][l],
                                         particle_prod_b_prob_data_integ[i][j][k][l]);
            }
          }
        }
      }
      else if( particle_prod_ene_flg[i][j] == 33 )
      {
        ace_wri_obj.set_real_data(particle_prod_q_value[i][j]);
        ace_wri_obj.set_real_data(particle_prod_mass_coef[i][j]);
      }
      else if( particle_prod_ene_flg[i][j] == 66 )
      {
        Integer q_val_no = static_cast<Integer>(particle_prod_q_value[i][j]);
        ace_wri_obj.set_int_data(q_val_no);
        ace_wri_obj.set_real_data(particle_prod_mass_coef[i][j]);

        ace_wri_obj.set_int_data(particle_prod_a_int_data[i][j][0]);
        ace_wri_obj.set_table_data(particle_prod_a_data[i][j][0],
                                   particle_prod_a_distr_data[i][j][0],
                                   particle_prod_a_distr_data_integ[i][j][0]);
      }
      else if( particle_prod_ene_flg[i][j] == 67 )
      {
        int k_max = static_cast<int>(particle_prod_a_int_data[i][j].size());
        for(int k=0; k<k_max; k++)
        {
          ace_wri_obj.set_int_data(particle_prod_a_int_data[i][j][k]);
          ace_wri_obj.set_list_data(particle_prod_a_data[i][j][k]);

          int     l_max = static_cast<int>(particle_prod_a_data[i][j][k].size());
          Integer ele_no_mu = 0;
          for(int l=0; l<l_max; l++)
          {
            ace_wri_obj.set_int_data(ele_no_mu); //pointer
          }

          for(int l=0; l<l_max; l++)
          {
            ace_wri_obj.set_int_data(particle_prod_b_int_data[i][j][k][l]);
            ace_wri_obj.set_table_data(particle_prod_b_data[i][j][k][l],
                                       particle_prod_b_prob_data[i][j][k][l],
                                       particle_prod_b_prob_data_integ[i][j][k][l]);
          }
        }
      }
    }

    particle_prod_pointer[i][9] = ace_wri_obj.get_data_count_total();  //yh
    ace_wri_obj.set_list_data(particle_prod_reaction_type[i]);
  }

  len2 = ace_wri_obj.get_data_count_total() - 1;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataWriter::output_ace_format_binary_mode()
{
  //int data_no = 512;

  string class_name = "FastAceDataWriter";
  string func_name  = "output_ace_format_binary_mode()";
  vector<string> err_com;
  err_com.push_back("This function is not implemented.");
  err_com.push_back("Please use output_ace_format function.");
  err_obj.output_runtime_error(class_name, func_name, err_com);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataWriter::check_set_data()
{
  vector<string> err_com;
  err_com.clear();

  if( set_ace_data_obj_flg != 1 )
  {
    err_com.push_back("There is no FastAceDataObject.");
    err_com.push_back("Please set the FastAceDataObject by using set_ace_data_obj method.");
    err_com.push_back("");
  }

  if( new_cummulative_angle_distr_flg != 0 && new_cummulative_angle_distr_flg != 1 )
  {
    ostringstream oss;
    oss << new_cummulative_angle_distr_flg;
    string str_data = "Use new cummulative angle distributions option : " + oss.str();
    err_com.push_back(str_data);
    err_com.push_back("This new cummulative angle distribution option is not available.");
    err_com.push_back("The available new cummulative angle distribution option is 0 (no) or 1 (yes).");
    err_com.push_back("");
  }

  if( opt_out_type != ascii_mode && opt_out_type != binary_mode )
  {
    ostringstream oss;
    oss << opt_out_type;
    string str_data = "Print option : " + oss.str();
    err_com.push_back(str_data);
    err_com.push_back("This output type option is not available.");
    err_com.push_back("The available output type option is 1 (ascii mode) or 2 (binary mode).");
    err_com.push_back("");
  }

  if( static_cast<int>(err_com.size()) > 0 )
  {
    string class_name = "FastAceDataWriter";
    string func_name  = "check_set_data()";
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//Setter

void FastAceDataWriter::set_ace_data_obj(FastAceDataObject& data_obj)
{
  set_data_flg         = 0;
  set_ace_data_obj_flg = 1;
  ace_data_obj         = data_obj;
}

void FastAceDataWriter::set_new_cummulative_angle_distr_flg(Integer int_val)
{
  set_data_flg                    = 0;
  new_cummulative_angle_distr_flg = int_val;
}

void FastAceDataWriter::set_detailed_photon_flg(Integer int_val)
{
  set_data_flg        = 0;
  detailed_photon_flg = int_val;
}

void FastAceDataWriter::set_opt_out_type(Integer int_val)
{
  set_data_flg = 0;
  opt_out_type = int_val;
}

void FastAceDataWriter::set_ace_file_name(string str_data)
{
  set_data_flg  = 0;
  ace_file_name = str_data;
  str_data.clear();
}

void FastAceDataWriter::set_previous_line_no(Integer int_val)
{
  set_data_flg = 0;
  line_no_pre = int_val;

  if( line_no_pre < 0 )
  {
    string class_name = "FastAceDataWriter";
    string func_name  = "set_previous_line_no(Integer int_val)";
    ostringstream oss01;
    oss01 << line_no_pre;

    string str_data = "The previous line no : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("The previous line no must be larger than or equal to 0.");
    err_com.push_back("Please check the set value.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//Getter

FastAceDataObject FastAceDataWriter::get_ace_data_obj()
{
  if( set_data_flg == 0 && set_ace_data_obj_flg == 1 )
  {
    output_ace_format(calc_pointer_mode);
    copy_fast_ace_pointer_data(ace_data_obj);
  }

  return ace_data_obj;
}

Integer           FastAceDataWriter::get_opt_out_type()
{
  return opt_out_type;
}

Integer           FastAceDataWriter::get_new_cummulative_angle_distr_flg()
{
  return new_cummulative_angle_distr_flg;
}

Integer           FastAceDataWriter::get_detailed_photon_flg()
{
  return detailed_photon_flg;
}

string            FastAceDataWriter::get_ace_file_name()
{
  return ace_file_name;
}

Integer           FastAceDataWriter::get_previous_line_no()
{
  return line_no_pre;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

