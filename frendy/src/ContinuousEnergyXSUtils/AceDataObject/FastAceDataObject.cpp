#include "ContinuousEnergyXSUtils/AceDataObject/FastAceDataObject.hpp"

using namespace frendy;

//constructor
FastAceDataObject::FastAceDataObject(void)
{ 
  clear();
}

//destructor
FastAceDataObject::~FastAceDataObject(void)
{
  clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataObject::clear()
{
  clear_calc_data();
  clear_ace_data();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataObject::clear_calc_data()
{
  mcnpx_mode_flg = 0;
  mat            = 0;
  temp           = 0.0;
  sub_lib_part   = 0;
  sub_lib_type   = 0;
  ene_max        = 0.0;

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

void FastAceDataObject::clear_ace_data()
{
  clear_ace_base_data();
  clear_ace_ene_angular_distr_data();
  clear_ace_prod_distr_data();
  clear_ace_photon_data();
  clear_ace_particle_data();

  clear_ace_pointer_data();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataObject::clear_ace_base_data()
{
  zi_vec.clear();
  awr_vec.clear();

  aw0 = 0.0;
  tz  = 0.0;
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

void FastAceDataObject::clear_ace_ene_angular_distr_data()
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

void FastAceDataObject::clear_ace_prod_distr_data()
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

void FastAceDataObject::clear_ace_photon_data()
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

void FastAceDataObject::clear_ace_particle_data()
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

void FastAceDataObject::clear_ace_pointer_data()
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


////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataObject::get_bondarenko_xs(Real background_xs,
                                          vector<Real>& ene_vec, vector<vector<Real> >& xs_vec)
{
  ene_vec = unreso_prob_tab_ene;
  xs_vec  = get_bondarenko_xs(background_xs);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<vector<Real> > FastAceDataObject::get_bondarenko_xs(Real background_xs)
{
  int iff = unreso_prob_tab_self_shielding_flg;

  vector<Real>          band_flux;
  vector<vector<Real> > bondarenko_xs;

  int ene_no = static_cast<int>(unreso_prob_tab_table.size());
  band_flux.resize(ene_no);
  bondarenko_xs.resize(ene_no);
  for(int i=0; i<ene_no; i++)
  {
    band_flux[i] = 0.0;
    bondarenko_xs[i].resize(xs_type_no);
    for(int j=0; j<xs_type_no; j++)
    {
      bondarenko_xs[i][j] = 0.0;
    }

    int bin_no = static_cast<int>(unreso_prob_tab_sample_no[i].size());
    vector<Real>          prob_each;
    vector<vector<Real> > xs_each_prob;
    prob_each.resize(bin_no);
    xs_each_prob.resize(bin_no);
    for(int j=0; j<bin_no; j++)
    {
      if( j == 0 )
      {
        prob_each[j] = unreso_prob_tab_sample_no[i][j];
      }
      else
      {
        prob_each[j] = unreso_prob_tab_sample_no[i][j] - unreso_prob_tab_sample_no[i][j-1];
      }

      xs_each_prob[j].resize(xs_type_no);
      for(int k=0; k<xs_type_no; k++)
      {
        if( iff == 0 ) //probability table is cross section
        {
          xs_each_prob[j][k] = unreso_prob_tab_table[i][k][j];
        }
        else //if( iff == 1 ) //probability table is factor
        {
          int mt_no = 0;
          if     ( k==total_xs )      mt_no =   1;
          else if( k==scatter_xs )    mt_no =   2;
          else if( k==fission_xs )    mt_no =  18;
          else if( k==radiation_xs )  mt_no = 102;

          Real xs_val = get_xs_data(mt_no, unreso_prob_tab_ene[i]);
          xs_each_prob[j][k] = unreso_prob_tab_table[i][k][j] * xs_val;
        }
      }
    }

    for(int j=0; j<bin_no; j++)
    {
      Real band_flux_each = prob_each[j] 
                          / (xs_each_prob[j][total_xs] + background_xs);
      band_flux[i] += band_flux_each;
      for(int k=0; k<xs_type_no; k++)
      {
        bondarenko_xs[i][k] += band_flux_each * xs_each_prob[j][k];
      }
    }

    for(int j=0; j<xs_type_no; j++)
    {
      bondarenko_xs[i][j] = bondarenko_xs[i][j] / band_flux[i];
    }
  }

  return bondarenko_xs;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Real FastAceDataObject::get_xs_data(int mt_no, Real ene_val)
{
  Real xs_val = 0.0;

  vector<Real> ene_vec, xs_vec;
  get_xs_data(mt_no, ene_vec, xs_vec);

  if( static_cast<int>(xs_vec.size()) == 0 )
  {
    return 0.0;
  }

  TabInterpolator ti_obj;
  int int_val = int_lin_lin;
  ti_obj.interpolation_1d(int_val, ene_val, xs_val, ene_vec, xs_vec);

  return xs_val;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataObject::get_xs_data(int mt_no, vector<Real>& ene_vec, vector<Real>& xs_vec)
{
  xs_vec.clear();
  ene_vec.clear();

  if( mt_no == 1 )
  {
    ene_vec = union_ene_grid;
    xs_vec  = react_xs_tot;
  }
  else if( mt_no == 2 )
  {
    ene_vec = union_ene_grid;
    xs_vec  = react_xs_sc;
  }
  else if( mt_no == 101 )
  {
    ene_vec = union_ene_grid;
    xs_vec  = react_xs_cap;
  }
  else if( mt_no == 4 )
  {
    get_mt4_data(ene_vec, xs_vec);
  }
  else if( mt_no == 1018 )
  {
    get_chi_data(ene_vec, xs_vec);
  }
  else
  {
    int i_max  = static_cast<int>(react_type_list.size());
    int mt_pos = -1;
    for(int i=0; i<i_max; i++)
    {
      if( mt_no == react_type_list[i] )
      {
        mt_pos = i;
        break;
      }
    }

    //MT=18 data in the ACE file may be removed.
    //MT=18 is modified to MT=19 in the ACE file generation process.
    if( mt_pos < 0 && (mt_no == 18 || mt_no == 19) )
    {
      int mt_no_mod = 19;
      if( mt_no == 19 )
      {
        mt_no_mod = 18;
      }

      for(int i=0; i<i_max; i++)
      {
        if( mt_no_mod == react_type_list[i] )
        {
          mt_pos = i;
          break;
        }
      }
    }

    if( mt_pos < 0 )
    {
      string class_name = "FastAceDataObject";
      string func_name  = "get_xs_data(int mt_no, vector<Real>& ene_vec, vector<Real>& xs_vec)";

      vector<string> err_com;
      ostringstream  oss_mt;
      oss_mt << mt_no;
      string str_data01 = "Requested MT number : " + oss_mt.str();
      string str_data02 = "MT number in ACE file";
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);

      int skip_no = 10;
      for(int i=0; i<i_max; i+=skip_no)
      {
        string str_data03 = "";
        for(int j=0; j<skip_no; j++)
        {
          int ele_no = i + j;
          if( ele_no >= i_max )
          {
            break;
          }

          ostringstream oss_mt_ace;
          oss_mt_ace << react_type_list[ele_no];

          string space_str = "  ";
          if( react_type_list[ele_no] < 100 )
          {
            space_str = space_str + " ";
            if( react_type_list[ele_no] < 10 )
            {
              space_str = space_str + " ";
            }
          }

          str_data03 = str_data03 + space_str + oss_mt_ace.str();
        }
        err_com.push_back(str_data03);
      }
      
      err_com.push_back("The requested MT number cannot found in the ACE file data.");
      err_com.push_back("Please check MT number or ACE file.");

      ErrorManager  err_obj;
      err_obj.output_caution(class_name, func_name, err_com);

      xs_vec.clear();
      ene_vec.clear();
      return;
    }

    xs_vec = react_xs[mt_pos];
    int j_max  = static_cast<int>(xs_vec.size());
    int ele_no = static_cast<int>(union_ene_grid.size()) - j_max;
    ene_vec.resize(j_max);
    for(int j=0; j<j_max; j++)
    {
      ene_vec[j] = union_ene_grid[ele_no + j];
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataObject::get_mt4_data(vector<Real>& ene_vec, vector<Real>& xs_vec)
{
  ene_vec = union_ene_grid;

  int ene_no = static_cast<int>(ene_vec.size());
  xs_vec.resize(ene_no);
  for(int i=0; i<ene_no; i++)
  {
    xs_vec[i] = 0.0;
  }

  int mt4_flg = 0;
  int i_max   = static_cast<int>(react_type_list.size());
  for(int i=0; i<i_max; i++)
  {
    if( react_type_list[i] == 4 )
    {
      mt4_flg = 1;

      int j_max = static_cast<int>(react_xs[i].size());
      int ele_no = static_cast<int>(union_ene_grid.size()) - j_max;
      for(int j=0; j<j_max; j++)
      {
        xs_vec[ele_no+j] = react_xs[i][j];
      }

      break;
    }
  }

  if( mt4_flg == 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      if( react_type_list[i] >= 50 && react_type_list[i] <= 91 )
      {
        vector<Real> xs_vec_add = react_xs[i];

        int j_max = static_cast<int>(xs_vec_add.size());
        int ele_no = static_cast<int>(union_ene_grid.size()) - j_max;
        for(int j=0; j<j_max; j++)
        {
          xs_vec[ele_no+j] += xs_vec_add[j];
        }
      }
    }
  }

  int ene_sta = 0;
  for(int i=0; i<ene_no; i++)
  {
    if( xs_vec[i] > min_value )
    {
      ene_sta = i;
      break;
    }
  }

  i_max = ene_no - ene_sta;
  vector<Real> xs_vec_new, ene_vec_new;
  xs_vec_new.resize(i_max);
  ene_vec_new.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    xs_vec_new[i]  = xs_vec[i+ene_sta];
    ene_vec_new[i] = ene_vec[i+ene_sta];
  }
  xs_vec  = xs_vec_new;
  ene_vec = ene_vec_new;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataObject::get_chi_data(vector<Real>& ene_vec, vector<Real>& xs_vec)
{
  ene_vec.clear();
  xs_vec.clear();

  vector<Integer> react_type_list_sort = react_type_list;
  sort(react_type_list_sort.begin(), react_type_list_sort.end());

  int pos_chi = -1;
  int zn_flg  =  0;
  for(int i=0; i<static_cast<int>(react_type_list_sort.size()); i++)
  {
    if( react_type_list_sort[i] == 4 )
    {
      zn_flg = 1;
    }

    if( react_type_list_sort[i] == 18 || react_type_list_sort[i] == 19 ||
        react_type_list_sort[i] == 21 || react_type_list_sort[i] == 38 )
    {
      pos_chi = i - zn_flg;
      break;
    }
  }

  if( pos_chi < 0 )
  {
    return;
  }

  for(int i=0; i<static_cast<int>(ene_distr_ene_repr_flg[pos_chi].size()); i++)
  {
    if( ene_distr_ene_repr_flg[pos_chi][i] == 4 )
    {
      vector<Real>          ene_in  = ene_distr_ene_in_data[pos_chi][i];
      vector<vector<Real> > ene_tab = ene_distr_ene_out_ene_data[pos_chi][i];
      vector<vector<Real> > chi_tab = ene_distr_ene_out_data[pos_chi][i];
      for(int j=0; j<static_cast<int>(ene_tab.size()); j++)
      {
        ene_vec.push_back(-1000.0);
        xs_vec.push_back(ene_in[j]);
        for(int k=0; k<static_cast<int>(ene_tab[j].size()); k++)
        {
          ene_vec.push_back(ene_tab[j][k]);
          xs_vec.push_back(chi_tab[j][k]);
        }
      }
    }
    //else if( ene_distr_ene_repr_flg[pos_chi] == 7 )
    //{
    //}
    else
    {
      string class_name = "FastAceDataObject";
      string func_name  = "get_chi_data(vector<Real>& ene_vec, vector<Real>& xs_vec)";

      vector<string> err_com;
      ostringstream  oss01, oss02, oss03, oss04;
      oss01 << react_type_list_sort[pos_chi];
      oss02 << i+1;
      oss03 << static_cast<int>(ene_distr_ene_repr_flg[pos_chi].size());
      oss04 << ene_distr_ene_repr_flg[pos_chi][i];
      string str_data01 = "Reaction type          : " + oss01.str();
      string str_data02 = "position               : " + oss02.str() + " / " + oss03.str();
      string str_data03 = "ene_distr_ene_repr_flg : " + oss04.str();
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back("");
      //err_com.push_back("Available ene_distr_ene_repr_flg (law) of fission spectrum is 4 or 7.");
      err_com.push_back("Available ene_distr_ene_repr_flg (law) of fission spectrum is 4.");
      err_com.push_back("This chi-spectrum data is skipped.");
      err_com.push_back("");

      ErrorManager  err_obj;
      err_obj.output_caution(class_name, func_name, err_com);
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void FastAceDataObject::set_mcnpx_mode_flg(Integer int_val)
{
  mcnpx_mode_flg = int_val;
}

void FastAceDataObject::set_mat(Integer int_val)
{
  mat = int_val;
}

void FastAceDataObject::set_temp(Real real_val)
{
  temp = real_val;
}

void FastAceDataObject::set_zi_vec(vector<Integer> int_vec)
{
  zi_vec = int_vec;
  int_vec.clear();
}

void FastAceDataObject::set_awr_vec(vector<Real> real_vec)
{
  awr_vec = real_vec;
  real_vec.clear();
}

void FastAceDataObject::set_sub_lib_part(Integer int_val)
{
  sub_lib_part = int_val;
}

void FastAceDataObject::set_sub_lib_type(Integer int_val)
{
  sub_lib_type = int_val;
}

void FastAceDataObject::set_ene_max(Real real_val)
{
  ene_max = real_val;
}


void FastAceDataObject::set_union_ene_grid(vector<Real> real_vec)
{
  union_ene_grid = real_vec;
  real_vec.clear();
}

void FastAceDataObject::set_gamma_product_xs(vector<Real> real_vec)
{
  gamma_product_xs = real_vec;
  real_vec.clear();
}

void FastAceDataObject::set_photon_product_xs(vector<Real> real_vec)
{
  photon_product_xs = real_vec;
  real_vec.clear();
}


void FastAceDataObject::set_particle_production_data(vector<vector<Integer> > int_vec)
{
  particle_production_data = int_vec;
  clr_obj.clear_vec_array2_int(int_vec);
}

void FastAceDataObject::set_particle_production_ene_data(vector<Real> real_vec)
{
  particle_production_ene_data = real_vec;
  real_vec.clear();
}


void FastAceDataObject::set_photon_prod_yield_coef_direct(vector<vector<Real> > real_vec)
{
  photon_prod_yield_coef_direct = real_vec;
  clr_obj.clear_vec_array2_real(real_vec);
}

void FastAceDataObject::set_photon_prod_yield_coef_given(vector<vector<Real> > real_vec)
{
  photon_prod_yield_coef_given = real_vec;
  clr_obj.clear_vec_array2_real(real_vec);
}


void FastAceDataObject::set_photon_xs_ene_min(vector<Real> real_vec)
{
  photon_xs_ene_min = real_vec;
  real_vec.clear();
}

void FastAceDataObject::set_photon_prod_discon_ene_data(vector<Real> real_vec)
{
  photon_prod_discon_ene_data = real_vec;
  real_vec.clear();
}


void FastAceDataObject::set_equal_prob_data_ini(vector<vector<Real> > real_vec)
{
  equal_prob_data_ini = real_vec;
  clr_obj.clear_vec_array2_real(real_vec);
}


void FastAceDataObject::set_aw0(Real real_val)
{
  aw0 = real_val;
}

void FastAceDataObject::set_tz(Real real_val)
{
  tz = real_val;
}

void FastAceDataObject::set_izaid(int int_val)
{
  izaid = int_val;
}

void FastAceDataObject::set_title_data(vector<string> str_vec)
{
  title_data = str_vec;
  clr_obj.clear_vec_array1_str(str_vec);
}

void FastAceDataObject::set_discriptive_data(string str_data)
{
  discriptive_data = str_data;
  str_data.clear();
}


void FastAceDataObject::set_ntr(int int_val)
{
  ntr = int_val;
}

void FastAceDataObject::set_nr(int int_val)
{
  nr = int_val;
}

void FastAceDataObject::set_mtntr(int int_val)
{
  mtntr = int_val;
}

void FastAceDataObject::set_mtnr(int int_val)
{
  mtnr = int_val;
}

void FastAceDataObject::set_nu_bar_repr_flg(Integer int_val)
{
  nu_bar_repr_flg = int_val;
}

void FastAceDataObject::set_nu_d_bar_repr_flg(Integer int_val)
{
  nu_d_bar_repr_flg = int_val;
}

void FastAceDataObject::set_nu_p_bar_repr_flg(Integer int_val)
{
  nu_p_bar_repr_flg = int_val;
}

void FastAceDataObject::set_nu_int_data(vector<Integer> int_vec)
{
  nu_int_data = int_vec;
  int_vec.clear();
}

void FastAceDataObject::set_nu_range_data(vector<Integer> int_vec)
{
  nu_range_data = int_vec;
  int_vec.clear();
}

void FastAceDataObject::set_nu_d_int_data(vector<Integer> int_vec)
{
  nu_d_int_data = int_vec;
  int_vec.clear();
}

void FastAceDataObject::set_nu_d_range_data(vector<Integer> int_vec)
{
  nu_d_range_data = int_vec;
  int_vec.clear();
}

void FastAceDataObject::set_nu_p_int_data(vector<Integer> int_vec)
{
  nu_p_int_data = int_vec;
  int_vec.clear();
}

void FastAceDataObject::set_nu_p_range_data(vector<Integer> int_vec)
{
  nu_p_range_data = int_vec;
  int_vec.clear();
}

void FastAceDataObject::set_nu_data(vector<Real> real_vec)
{
  nu_data = real_vec;
  real_vec.clear();
}

void FastAceDataObject::set_nu_ene_data(vector<Real> real_vec)
{
  nu_ene_data = real_vec;
  real_vec.clear();
}

void FastAceDataObject::set_nu_d_data(vector<Real> real_vec)
{
  nu_d_data = real_vec;
  real_vec.clear();
}

void FastAceDataObject::set_nu_d_ene_data(vector<Real> real_vec)
{
  nu_d_ene_data = real_vec;
  real_vec.clear();
}

void FastAceDataObject::set_nu_p_data(vector<Real> real_vec)
{
  nu_p_data = real_vec;
  real_vec.clear();
}

void FastAceDataObject::set_nu_p_ene_data(vector<Real> real_vec)
{
  nu_p_ene_data = real_vec;
  real_vec.clear();
}

void FastAceDataObject::set_nu_d_decay_constant(vector<Real> real_vec)
{
  nu_d_decay_constant = real_vec;
  real_vec.clear();
}


void FastAceDataObject::set_react_type_list(vector<Integer> int_vec)
{
  react_type_list = int_vec;
  int_vec.clear();
}

void FastAceDataObject::set_react_type_flg(vector<Integer> int_vec)
{
  react_type_flg = int_vec;
  int_vec.clear();
}

void FastAceDataObject::set_react_type_ene_sta(vector<Integer> int_vec)
{
  react_type_ene_sta = int_vec;
  int_vec.clear();
}

void FastAceDataObject::set_react_q_value(vector<Real> real_vec)
{
  react_q_value = real_vec;
  real_vec.clear();
}

void FastAceDataObject::set_react_xs_tot(vector<Real> real_vec)
{
  react_xs_tot = real_vec;
  real_vec.clear();
}

void FastAceDataObject::set_react_xs_cap(vector<Real> real_vec)
{
  react_xs_cap = real_vec;
  real_vec.clear();
}

void FastAceDataObject::set_react_xs_sc(vector<Real> real_vec)
{
  react_xs_sc = real_vec;
  real_vec.clear();
}

void FastAceDataObject::set_react_xs_heat(vector<Real> real_vec)
{
  react_xs_heat = real_vec;
  real_vec.clear();
}

void FastAceDataObject::set_react_xs(vector<vector<Real> > real_vec)
{
  react_xs = real_vec;
  clr_obj.clear_vec_array2_real(real_vec);
}


void FastAceDataObject::set_angular_distr_type_flg(vector<Integer> int_vec)
{
  angular_distr_type_flg = int_vec;
  int_vec.clear();
}

void FastAceDataObject::set_angular_distr_int_data(vector<vector<Integer> > int_vec)
{
  angular_distr_int_data = int_vec;
  clr_obj.clear_vec_array2_int(int_vec);
}

void FastAceDataObject::set_angular_distr_ene_data(vector<vector<Real> > real_vec)
{
  angular_distr_ene_data = real_vec;
  clr_obj.clear_vec_array2_real(real_vec);
}

void FastAceDataObject::set_angular_distr_cos_data(vector<vector<vector<Real> > > real_vec)
{
  angular_distr_cos_data = real_vec;
  clr_obj.clear_vec_array3_real(real_vec);
}

void FastAceDataObject::set_angular_distr_data(vector<vector<vector<Real> > > real_vec)
{
  angular_distr_data = real_vec;
  clr_obj.clear_vec_array3_real(real_vec);
}

void FastAceDataObject::set_angular_distr_data_integ(vector<vector<vector<Real> > > real_vec)
{
  angular_distr_data_integ = real_vec;
  clr_obj.clear_vec_array3_real(real_vec);
}


void FastAceDataObject::set_ene_distr_ene_repr_flg(vector<vector<Integer> > int_vec)
{
  ene_distr_ene_repr_flg = int_vec;
  clr_obj.clear_vec_array2_int(int_vec);
}

void FastAceDataObject::set_ene_distr_xs_part_int_data(vector<vector<vector<Integer> > > int_vec)
{
  ene_distr_xs_part_int_data = int_vec;
  clr_obj.clear_vec_array3_int(int_vec);
}

void FastAceDataObject::set_ene_distr_xs_part_range_data(vector<vector<vector<Integer> > > int_vec)
{
  ene_distr_xs_part_range_data = int_vec;
  clr_obj.clear_vec_array3_int(int_vec);
}

void FastAceDataObject::set_ene_distr_xs_part_ene_data(vector<vector<vector<Real> > > real_vec)
{
  ene_distr_xs_part_ene_data = real_vec;
  clr_obj.clear_vec_array3_real(real_vec);
}

void FastAceDataObject::set_ene_distr_xs_part_data(vector<vector<vector<Real> > > real_vec)
{
  ene_distr_xs_part_data = real_vec;
  clr_obj.clear_vec_array3_real(real_vec);
}

void FastAceDataObject::set_ene_distr_q_coef(vector<vector<Real> > real_vec)
{
  ene_distr_q_coef = real_vec;
  clr_obj.clear_vec_array2_real(real_vec);
}

void FastAceDataObject::set_ene_distr_mass_coef(vector<vector<Real> > real_vec)
{
  ene_distr_mass_coef = real_vec;
  clr_obj.clear_vec_array2_real(real_vec);
}

void FastAceDataObject::set_ene_distr_ene_in_int_data(vector<vector<vector<Integer> > > int_vec)
{
  ene_distr_ene_in_int_data = int_vec;
  clr_obj.clear_vec_array3_int(int_vec);
}

void FastAceDataObject::set_ene_distr_ene_in_range_data(vector<vector<vector<Integer> > > int_vec)
{
  ene_distr_ene_in_range_data = int_vec;
  clr_obj.clear_vec_array3_int(int_vec);
}

void FastAceDataObject::set_ene_distr_ene_in_data(vector<vector<vector<Real> > > real_vec)
{
  ene_distr_ene_in_data = real_vec;
  clr_obj.clear_vec_array3_real(real_vec);
}

void FastAceDataObject::set_ene_distr_ene_out_int_data(vector<vector<vector<Integer> > > int_vec)
{
  ene_distr_ene_out_int_data = int_vec;
  clr_obj.clear_vec_array3_int(int_vec);
}

void FastAceDataObject::set_ene_distr_ene_out_ene_data(vector<vector<vector<vector<Real> > > > real_vec)
{
  ene_distr_ene_out_ene_data = real_vec;
  clr_obj.clear_vec_array4_real(real_vec);
}

void FastAceDataObject::set_ene_distr_ene_out_data(vector<vector<vector<vector<Real> > > > real_vec)
{
  ene_distr_ene_out_data = real_vec;
  clr_obj.clear_vec_array4_real(real_vec);
}

void FastAceDataObject::set_ene_distr_ene_out_data_integ(vector<vector<vector<vector<Real> > > > real_vec)
{
  ene_distr_ene_out_data_integ = real_vec;
  clr_obj.clear_vec_array4_real(real_vec);
}

void FastAceDataObject::set_ene_distr_upper_ene_limit(vector<vector<Real> > real_vec)
{
  ene_distr_upper_ene_limit = real_vec;
  clr_obj.clear_vec_array2_real(real_vec);
}

void FastAceDataObject::set_ene_distr_temp_eff_int_data(vector<vector<vector<Integer> > > int_vec)
{
  ene_distr_temp_eff_int_data = int_vec;
  clr_obj.clear_vec_array3_int(int_vec);
}

void FastAceDataObject::set_ene_distr_temp_eff_range_data(vector<vector<vector<Integer> > > int_vec)
{
  ene_distr_temp_eff_range_data = int_vec;
  clr_obj.clear_vec_array3_int(int_vec);
}

void FastAceDataObject::set_ene_distr_watt_a_int_data(vector<vector<vector<Integer> > > int_vec)
{
  ene_distr_watt_a_int_data = int_vec;
  clr_obj.clear_vec_array3_int(int_vec);
}

void FastAceDataObject::set_ene_distr_watt_a_range_data(vector<vector<vector<Integer> > > int_vec)
{
  ene_distr_watt_a_range_data = int_vec;
  clr_obj.clear_vec_array3_int(int_vec);
}

void FastAceDataObject::set_ene_distr_watt_b_int_data(vector<vector<vector<Integer> > > int_vec)
{
  ene_distr_watt_b_int_data = int_vec;
  clr_obj.clear_vec_array3_int(int_vec);
}

void FastAceDataObject::set_ene_distr_watt_b_range_data(vector<vector<vector<Integer> > > int_vec)
{
  ene_distr_watt_b_range_data = int_vec;
  clr_obj.clear_vec_array3_int(int_vec);
}

void FastAceDataObject::set_ene_distr_temp_eff_ene_data(vector<vector<vector<Real> > > real_vec)
{
  ene_distr_temp_eff_ene_data = real_vec;
  clr_obj.clear_vec_array3_real(real_vec);
}

void FastAceDataObject::set_ene_distr_temp_eff_data(vector<vector<vector<Real> > > real_vec)
{
  ene_distr_temp_eff_data = real_vec;
  clr_obj.clear_vec_array3_real(real_vec);
}

void FastAceDataObject::set_ene_distr_watt_a_ene_data(vector<vector<vector<Real> > > real_vec)
{
  ene_distr_watt_a_ene_data = real_vec;
  clr_obj.clear_vec_array3_real(real_vec);
}

void FastAceDataObject::set_ene_distr_watt_a_data(vector<vector<vector<Real> > > real_vec)
{
  ene_distr_watt_a_data = real_vec;
  clr_obj.clear_vec_array3_real(real_vec);
}

void FastAceDataObject::set_ene_distr_watt_b_ene_data(vector<vector<vector<Real> > > real_vec)
{
  ene_distr_watt_b_ene_data = real_vec;
  clr_obj.clear_vec_array3_real(real_vec);
}

void FastAceDataObject::set_ene_distr_watt_b_data(vector<vector<vector<Real> > > real_vec)
{
  ene_distr_watt_b_data = real_vec;
  clr_obj.clear_vec_array3_real(real_vec);
}


void FastAceDataObject::set_prod_yield_tot_int_data(vector<vector<Integer> > int_vec)
{
  prod_yield_tot_int_data = int_vec;
  clr_obj.clear_vec_array2_int(int_vec);
}

void FastAceDataObject::set_prod_yield_tot_range_data(vector<vector<Integer> > int_vec)
{
  prod_yield_tot_range_data = int_vec;
  clr_obj.clear_vec_array2_int(int_vec);
}

void FastAceDataObject::set_prod_yield_tot_ene_data(vector<vector<Real> > real_vec)
{
  prod_yield_tot_ene_data = real_vec;
  clr_obj.clear_vec_array2_real(real_vec);
}

void FastAceDataObject::set_prod_yield_tot_data(vector<vector<Real> > real_vec)
{
  prod_yield_tot_data = real_vec;
  clr_obj.clear_vec_array2_real(real_vec);
}

void FastAceDataObject::set_prod_distr_func_flg(vector<vector<Integer> > int_vec)
{
  prod_distr_func_flg = int_vec;
  clr_obj.clear_vec_array2_int(int_vec);
}

void FastAceDataObject::set_prod_distr_n_body_mass(vector<vector<Real> > real_vec)
{
  prod_distr_n_body_mass = real_vec;
  clr_obj.clear_vec_array2_real(real_vec);
}

void FastAceDataObject::set_prod_distr_prob_data_no(vector<vector<Integer> > int_vec)
{
  prod_distr_prob_data_no = int_vec;
  clr_obj.clear_vec_array2_int(int_vec);
}

void FastAceDataObject::set_prod_distr_n_body_particle_no(vector<vector<Integer> > int_vec)
{
  prod_distr_n_body_particle_no = int_vec;
  clr_obj.clear_vec_array2_int(int_vec);
}

void FastAceDataObject::set_prod_distr_prob_ene_in_int_data(vector<vector<vector<Integer> > > int_vec)
{
  prod_distr_prob_ene_in_int_data = int_vec;
  clr_obj.clear_vec_array3_int(int_vec);
}

void FastAceDataObject::set_prod_distr_prob_ene_in_range_data(vector<vector<vector<Integer> > > int_vec)
{
  prod_distr_prob_ene_in_range_data = int_vec;
  clr_obj.clear_vec_array3_int(int_vec);
}

void FastAceDataObject::set_prod_distr_prob_ene_out_int_data(vector<vector<vector<Integer> > > int_vec)
{
  prod_distr_prob_ene_out_int_data = int_vec;
  clr_obj.clear_vec_array3_int(int_vec);
}

void FastAceDataObject::set_prod_distr_prob_ene_in_data(vector<vector<vector<Real> > > real_vec)
{
  prod_distr_prob_ene_in_data = real_vec;
  clr_obj.clear_vec_array3_real(real_vec);
}

void FastAceDataObject::set_prod_distr_prob_mu_int_data(vector<vector<vector<vector<Integer> > > > int_vec)
{
  prod_distr_prob_mu_int_data = int_vec;
  clr_obj.clear_vec_array4_int(int_vec);
}

void FastAceDataObject::set_prod_distr_prob_mu_range_data(vector<vector<vector<vector<Integer> > > > int_vec)
{
  prod_distr_prob_mu_range_data = int_vec;
  clr_obj.clear_vec_array4_int(int_vec);
}

void FastAceDataObject::set_prod_distr_prob_mu_data(vector<vector<vector<vector<Real> > > > real_vec)
{
  prod_distr_prob_mu_data = real_vec;
  clr_obj.clear_vec_array4_real(real_vec);
}

void FastAceDataObject::set_prod_distr_prob_mu_data_integ(vector<vector<vector<vector<Real> > > > real_vec)
{
  prod_distr_prob_mu_data_integ = real_vec;
  clr_obj.clear_vec_array4_real(real_vec);
}

void FastAceDataObject::set_prod_distr_prob_data(vector<vector<vector<vector<Real> > > > real_vec)
{
  prod_distr_prob_data = real_vec;
  clr_obj.clear_vec_array4_real(real_vec);
}

void FastAceDataObject::set_prod_distr_prob_data_integ(vector<vector<vector<vector<Real> > > > real_vec)
{
  prod_distr_prob_data_integ = real_vec;
  clr_obj.clear_vec_array4_real(real_vec);
}

void FastAceDataObject::set_prod_distr_prob_ene_out_data(vector<vector<vector<vector<Real> > > > real_vec)
{
  prod_distr_prob_ene_out_data = real_vec;
  clr_obj.clear_vec_array4_real(real_vec);
}

void FastAceDataObject::set_prod_distr_prob_coef_a(vector<vector<vector<vector<Real> > > > real_vec)
{
  prod_distr_prob_coef_a = real_vec;
  clr_obj.clear_vec_array4_real(real_vec);
}

void FastAceDataObject::set_prod_distr_prob_coef_b(vector<vector<vector<vector<Real> > > > real_vec)
{
  prod_distr_prob_coef_b = real_vec;
  clr_obj.clear_vec_array4_real(real_vec);
}

void FastAceDataObject::set_prod_distr_prob_int_vec(vector<vector<vector<vector<vector<Integer> > > > > int_vec)
{
  prod_distr_prob_int_vec = int_vec;
  clr_obj.clear_vec_array5_int(int_vec);
}

void FastAceDataObject::set_prod_distr_prob_range_vec(vector<vector<vector<vector<vector<Integer> > > > > int_vec)
{
  prod_distr_prob_range_vec = int_vec;
  clr_obj.clear_vec_array5_int(int_vec);
}

void FastAceDataObject::set_prod_distr_prob_mu_vec(vector<vector<vector<vector<vector<Real> > > > > real_vec)
{
  prod_distr_prob_mu_vec = real_vec;
  clr_obj.clear_vec_array5_real(real_vec);
}

void FastAceDataObject::set_prod_distr_prob_ene_out_vec(vector<vector<vector<vector<vector<Real> > > > > real_vec)
{
  prod_distr_prob_ene_out_vec = real_vec;
  clr_obj.clear_vec_array5_real(real_vec);
}

void FastAceDataObject::set_prod_distr_prob_vec(vector<vector<vector<vector<vector<Real> > > > > real_vec)
{
  prod_distr_prob_vec = real_vec;
  clr_obj.clear_vec_array5_real(real_vec);
}

void FastAceDataObject::set_prod_distr_prob_vec_integ(vector<vector<vector<vector<vector<Real> > > > > real_vec)
{
  prod_distr_prob_vec_integ = real_vec;
  clr_obj.clear_vec_array5_real(real_vec);
}


void FastAceDataObject::set_unreso_prob_tab_int_data(Integer int_val)
{
  unreso_prob_tab_int_data = int_val;
}

void FastAceDataObject::set_unreso_prob_tab_inela_comp_flg(Integer int_val)
{
  unreso_prob_tab_inela_comp_flg = int_val;
}

void FastAceDataObject::set_unreso_prob_tab_abs_comp_flg(Integer int_val)
{
  unreso_prob_tab_abs_comp_flg = int_val;
}

void FastAceDataObject::set_unreso_prob_tab_self_shielding_flg(Integer int_val)
{
  unreso_prob_tab_self_shielding_flg = int_val;
}

void FastAceDataObject::set_unreso_prob_tab_ene(vector<Real> real_vec)
{
  unreso_prob_tab_ene = real_vec;
}

void FastAceDataObject::set_unreso_prob_tab_heat(vector<vector<Real> > real_vec)
{
  unreso_prob_tab_heat = real_vec;
  clr_obj.clear_vec_array2_real(real_vec);
}

void FastAceDataObject::set_unreso_prob_tab_sample_no(vector<vector<Real> > real_vec)
{
  unreso_prob_tab_sample_no = real_vec;
  clr_obj.clear_vec_array2_real(real_vec);
}

void FastAceDataObject::set_unreso_prob_tab_table(vector<vector<vector<Real> > > real_vec)
{
  unreso_prob_tab_table = real_vec;
  clr_obj.clear_vec_array3_real(real_vec);
}


void FastAceDataObject::set_nu_d_ene_min(vector<Real> real_vec)
{
  nu_d_ene_min = real_vec;
  real_vec.clear();
}

void FastAceDataObject::set_nu_d_ene_max(vector<Real> real_vec)
{
  nu_d_ene_max = real_vec;
  real_vec.clear();
}

void FastAceDataObject::set_nu_d_xs_part_int_data(vector<vector<Integer> > int_vec)
{
  nu_d_xs_part_int_data = int_vec;
  clr_obj.clear_vec_array2_int(int_vec);
}

void FastAceDataObject::set_nu_d_xs_part_range_data(vector<vector<Integer> > int_vec)
{
  nu_d_xs_part_range_data = int_vec;
  clr_obj.clear_vec_array2_int(int_vec);
}

void FastAceDataObject::set_nu_d_xs_part_ene_data(vector<vector<Real> > real_vec)
{
  nu_d_xs_part_ene_data = real_vec;
  clr_obj.clear_vec_array2_real(real_vec);
}

void FastAceDataObject::set_nu_d_xs_part_data(vector<vector<Real> > real_vec)
{
  nu_d_xs_part_data = real_vec;
  clr_obj.clear_vec_array2_real(real_vec);
}

void FastAceDataObject::set_nu_d_ene_in_int_data(vector<vector<Integer> > int_vec)
{
  nu_d_ene_in_int_data = int_vec;
  clr_obj.clear_vec_array2_int(int_vec);
}

void FastAceDataObject::set_nu_d_ene_in_range_data(vector<vector<Integer> > int_vec)
{
  nu_d_ene_in_range_data = int_vec;
  clr_obj.clear_vec_array2_int(int_vec);
}

void FastAceDataObject::set_nu_d_ene_out_int_data(vector<vector<Integer> > int_vec)
{
  nu_d_ene_out_int_data = int_vec;
  clr_obj.clear_vec_array2_int(int_vec);
}

void FastAceDataObject::set_nu_d_ene_in_data(vector<vector<Real> > real_vec)
{
  nu_d_ene_in_data = real_vec;
  clr_obj.clear_vec_array2_real(real_vec);
}

void FastAceDataObject::set_nu_d_ene_out_data(vector<vector<vector<Real> > > real_vec)
{
  nu_d_ene_out_data = real_vec;
  clr_obj.clear_vec_array3_real(real_vec);
}

void FastAceDataObject::set_nu_d_ene_distr_data(vector<vector<vector<Real> > > real_vec)
{
  nu_d_ene_distr_data = real_vec;
  clr_obj.clear_vec_array3_real(real_vec);
}

void FastAceDataObject::set_nu_d_ene_distr_data_integ(vector<vector<vector<Real> > > real_vec)
{
  nu_d_ene_distr_data_integ = real_vec;
  clr_obj.clear_vec_array3_real(real_vec);
}


void FastAceDataObject::set_photon_prod_file_no(vector<Integer> int_vec)
{
  photon_prod_file_no = int_vec;
  int_vec.clear();
}

void FastAceDataObject::set_photon_prod_reaction_type(vector<Integer> int_vec)
{
  photon_prod_reaction_type = int_vec;
  int_vec.clear();
}

void FastAceDataObject::set_photon_prod_reaction_type_all(vector<Integer> int_vec)
{
  photon_prod_reaction_type_all = int_vec;
  int_vec.clear();
}

void FastAceDataObject::set_photon_prod_reaction_type_without_xs(vector<Integer> int_vec)
{
  photon_prod_reaction_type_without_xs = int_vec;
  int_vec.clear();
}

void FastAceDataObject::set_photon_prod_binding_ene(vector<Real> real_vec)
{
  photon_prod_binding_ene = real_vec;
  real_vec.clear();
}

void FastAceDataObject::set_photon_prod_multiplicity_int_data(vector<vector<Integer> > int_vec)
{
  photon_prod_multiplicity_int_data = int_vec;
  clr_obj.clear_vec_array2_int(int_vec);
}

void FastAceDataObject::set_photon_prod_multiplicity_range_data(vector<vector<Integer> > int_vec)
{
  photon_prod_multiplicity_range_data = int_vec;
  clr_obj.clear_vec_array2_int(int_vec);
}

void FastAceDataObject::set_photon_prod_multiplicity_ene_data(vector<vector<Real> > real_vec)
{
  photon_prod_multiplicity_ene_data = real_vec;
  clr_obj.clear_vec_array2_real(real_vec);
}

void FastAceDataObject::set_photon_prod_multiplicity_data(vector<vector<Real> > real_vec)
{
  photon_prod_multiplicity_data = real_vec;
  clr_obj.clear_vec_array2_real(real_vec);
}

void FastAceDataObject::set_photon_prod_xs_ene_no(vector<int> int_vec)
{
  photon_prod_xs_ene_no = int_vec;
  int_vec.clear();
}

void FastAceDataObject::set_photon_prod_xs_non_zero_pos(vector<vector<int> > int_vec)
{
  photon_prod_xs_non_zero_pos = int_vec;
  clr_obj.clear_vec_array2_int(int_vec);
}

void FastAceDataObject::set_photon_prod_xs_data(vector<vector<Real> > real_vec)
{
  photon_prod_xs_data = real_vec;
  clr_obj.clear_vec_array2_real(real_vec);
}

void FastAceDataObject::set_photon_prod_distr_int_data(vector<vector<Integer> > int_vec)
{
  photon_prod_distr_int_data = int_vec;
  clr_obj.clear_vec_array2_int(int_vec);
}

void FastAceDataObject::set_photon_prod_distr_range_data(vector<vector<Integer> > int_vec)
{
  photon_prod_distr_range_data = int_vec;
  clr_obj.clear_vec_array2_int(int_vec);
}

void FastAceDataObject::set_photon_prod_distr_ene_data(vector<vector<Real> > real_vec)
{
  photon_prod_distr_ene_data = real_vec;
  clr_obj.clear_vec_array2_real(real_vec);
}

void FastAceDataObject::set_photon_prod_distr_data(vector<vector<Real> > real_vec)
{
  photon_prod_distr_data = real_vec;
  clr_obj.clear_vec_array2_real(real_vec);
}


void FastAceDataObject::set_photon_angular_distr_ene_data(vector<vector<Real> > real_vec)
{
  photon_angular_distr_ene_data = real_vec;
  clr_obj.clear_vec_array2_real(real_vec);
}

void FastAceDataObject::set_photon_angular_distr_prob_cos_data(vector<vector<vector<Real> > > real_vec)
{
  photon_angular_distr_prob_cos_data = real_vec;
  clr_obj.clear_vec_array3_real(real_vec);
}


void FastAceDataObject::set_photon_energy_distr_flg(vector<Integer> int_vec)
{
  photon_energy_distr_flg = int_vec;
  int_vec.clear();
}

void FastAceDataObject::set_photon_energy_distr_ene_flg(vector<Integer> int_vec)
{
  photon_energy_distr_ene_flg = int_vec;
  int_vec.clear();
}

void FastAceDataObject::set_photon_energy_distr_binding_ene_data(vector<Real> real_vec)
{
  photon_energy_distr_binding_ene_data = real_vec;
  real_vec.clear();
}

void FastAceDataObject::set_photon_energy_distr_int_data(vector<vector<Integer> > int_vec)
{
  photon_energy_distr_int_data = int_vec;
  clr_obj.clear_vec_array2_int(int_vec);
}

void FastAceDataObject::set_photon_energy_distr_range_data(vector<vector<Integer> > int_vec)
{
  photon_energy_distr_range_data = int_vec;
  clr_obj.clear_vec_array2_int(int_vec);
}

void FastAceDataObject::set_photon_energy_distr_ene_data(vector<vector<Real> > real_vec)
{
  photon_energy_distr_ene_data = real_vec;
  clr_obj.clear_vec_array2_real(real_vec);
}

void FastAceDataObject::set_photon_energy_distr_prob_data(vector<vector<Real> > real_vec)
{
  photon_energy_distr_prob_data = real_vec;
  clr_obj.clear_vec_array2_real(real_vec);
}

void FastAceDataObject::set_photon_energy_distr_ene_in_int_data(vector<vector<Integer> > int_vec)
{
  photon_energy_distr_ene_in_int_data = int_vec;
  clr_obj.clear_vec_array2_int(int_vec);
}

void FastAceDataObject::set_photon_energy_distr_ene_in_range_data(vector<vector<Integer> > int_vec)
{
  photon_energy_distr_ene_in_range_data = int_vec;
  clr_obj.clear_vec_array2_int(int_vec);
}

void FastAceDataObject::set_photon_energy_distr_ene_in_data(vector<vector<Real> > real_vec)
{
  photon_energy_distr_ene_in_data = real_vec;
  clr_obj.clear_vec_array2_real(real_vec);
}

void FastAceDataObject::set_photon_energy_distr_weight_int_data(vector<vector<Integer> > int_vec)
{
  photon_energy_distr_weight_int_data = int_vec;
  clr_obj.clear_vec_array2_int(int_vec);
}

void FastAceDataObject::set_photon_energy_distr_weight_ene_data(vector<vector<vector<Real> > > real_vec)
{
  photon_energy_distr_weight_ene_data = real_vec;
  clr_obj.clear_vec_array3_real(real_vec);
}

void FastAceDataObject::set_photon_energy_distr_weight_data(vector<vector<vector<Real> > > real_vec)
{
  photon_energy_distr_weight_data = real_vec;
  clr_obj.clear_vec_array3_real(real_vec);
}

void FastAceDataObject::set_photon_energy_distr_weight_data_integ(vector<vector<vector<Real> > > real_vec)
{
  photon_energy_distr_weight_data_integ = real_vec;
  clr_obj.clear_vec_array3_real(real_vec);
}

void FastAceDataObject::set_photon_energy_distr_gamma_mass_product(vector<Real> real_vec)
{
  photon_energy_distr_gamma_mass_product = real_vec;
  real_vec.clear();
}


void FastAceDataObject::set_particle_prod_flg(vector<Integer> int_vec)
{
  particle_prod_flg = int_vec;
  int_vec.clear();
}

void FastAceDataObject::set_particle_prod_count(vector<Integer> int_vec)
{
  particle_prod_count = int_vec;
  int_vec.clear();
}

void FastAceDataObject::set_particle_prod_ene_sta(vector<Integer> int_vec)
{
  particle_prod_ene_sta = int_vec;
  int_vec.clear();
}

void FastAceDataObject::set_particle_prod_ene_no(vector<Integer> int_vec)
{
  particle_prod_ene_no = int_vec;
  int_vec.clear();
}

void FastAceDataObject::set_particle_prod_file_no(vector<vector<Integer> > int_vec)
{
  particle_prod_file_no = int_vec;
  clr_obj.clear_vec_array2_int(int_vec);
}

void FastAceDataObject::set_particle_prod_frame_flg(vector<vector<Integer> > int_vec)
{
  particle_prod_frame_flg = int_vec;
  clr_obj.clear_vec_array2_int(int_vec);
}

void FastAceDataObject::set_particle_prod_reaction_type(vector<vector<Integer> > int_vec)
{
  particle_prod_reaction_type = int_vec;
  clr_obj.clear_vec_array2_int(int_vec);
}

void FastAceDataObject::set_particle_prod_reaction_type_all(vector<vector<Integer> > int_vec)
{
  particle_prod_reaction_type_all = int_vec;
  clr_obj.clear_vec_array2_int(int_vec);
}

void FastAceDataObject::set_particle_prod_xs(vector<vector<Real> > real_vec)
{
  particle_prod_xs = real_vec;
  clr_obj.clear_vec_array2_real(real_vec);
}

void FastAceDataObject::set_particle_prod_heat(vector<vector<Real> > real_vec)
{
  particle_prod_heat = real_vec;
  clr_obj.clear_vec_array2_real(real_vec);
}

void FastAceDataObject::set_particle_prod_distr_int_data(vector<vector<vector<Integer> > > int_vec)
{
  particle_prod_distr_int_data = int_vec;
  clr_obj.clear_vec_array3_int(int_vec);
}

void FastAceDataObject::set_particle_prod_distr_range_data(vector<vector<vector<Integer> > > int_vec)
{
  particle_prod_distr_range_data = int_vec;
  clr_obj.clear_vec_array3_int(int_vec);
}

void FastAceDataObject::set_particle_prod_distr_ene_data(vector<vector<vector<Real> > > real_vec)
{
  particle_prod_distr_ene_data = real_vec;
  clr_obj.clear_vec_array3_real(real_vec);
}

void FastAceDataObject::set_particle_prod_distr_data(vector<vector<vector<Real> > > real_vec)
{
  particle_prod_distr_data = real_vec;
  clr_obj.clear_vec_array3_real(real_vec);
}

void FastAceDataObject::set_particle_prod_angular_int_data(vector<vector<vector<Integer> > > int_vec)
{
  particle_prod_angular_int_data = int_vec;
  clr_obj.clear_vec_array3_int(int_vec);
}

void FastAceDataObject::set_particle_prod_angular_ene_data(vector<vector<vector<Real> > > real_vec)
{
  particle_prod_angular_ene_data = real_vec;
  clr_obj.clear_vec_array3_real(real_vec);
}

void FastAceDataObject::set_particle_prod_angular_cos_data(vector<vector<vector<vector<Real> > > > real_vec)
{
  particle_prod_angular_cos_data = real_vec;
  clr_obj.clear_vec_array4_real(real_vec);
}

void FastAceDataObject::set_particle_prod_angular_distr_data(vector<vector<vector<vector<Real> > > > real_vec)
{
  particle_prod_angular_distr_data = real_vec;
  clr_obj.clear_vec_array4_real(real_vec);
}

void FastAceDataObject::set_particle_prod_angular_distr_data_integ(vector<vector<vector<vector<Real> > > > real_vec)
{
  particle_prod_angular_distr_data_integ = real_vec;
  clr_obj.clear_vec_array4_real(real_vec);
}


void FastAceDataObject::set_particle_prod_ene_flg(vector<vector<Integer> > int_vec)
{
  particle_prod_ene_flg = int_vec;
  clr_obj.clear_vec_array2_int(int_vec);
}

void FastAceDataObject::set_particle_prod_q_value(vector<vector<Real> > real_vec)
{
  particle_prod_q_value = real_vec;
  clr_obj.clear_vec_array2_real(real_vec);
}

void FastAceDataObject::set_particle_prod_mass_coef(vector<vector<Real> > real_vec)
{
  particle_prod_mass_coef = real_vec;
  clr_obj.clear_vec_array2_real(real_vec);
}

void FastAceDataObject::set_particle_prod_ene_int_data(vector<vector<vector<Integer> > > int_vec)
{
  particle_prod_ene_int_data = int_vec;
  clr_obj.clear_vec_array3_int(int_vec);
}

void FastAceDataObject::set_particle_prod_ene_range_data(vector<vector<vector<Integer> > > int_vec)
{
  particle_prod_ene_range_data = int_vec;
  clr_obj.clear_vec_array3_int(int_vec);
}

void FastAceDataObject::set_particle_prod_ene_data(vector<vector<vector<Real> > > real_vec)
{
  particle_prod_ene_data = real_vec;
  clr_obj.clear_vec_array3_real(real_vec);
}

void FastAceDataObject::set_particle_prod_ene_prob_data(vector<vector<vector<Real> > > real_vec)
{
  particle_prod_ene_prob_data = real_vec;
  clr_obj.clear_vec_array3_real(real_vec);
}


//For distr_func_flg = 1 : second energy, distr_func_flg = 7 : angle (mu)
void FastAceDataObject::set_particle_prod_ene_in_int_data(vector<vector<vector<Integer> > > int_vec)
{
  particle_prod_ene_in_int_data = int_vec;
  clr_obj.clear_vec_array3_int(int_vec);
}

void FastAceDataObject::set_particle_prod_ene_in_range_data(vector<vector<vector<Integer> > > int_vec)
{
  particle_prod_ene_in_range_data = int_vec;
  clr_obj.clear_vec_array3_int(int_vec);
}

void FastAceDataObject::set_particle_prod_ene_in_data(vector<vector<vector<Real> > > real_vec)
{
  particle_prod_ene_in_data = real_vec;
  clr_obj.clear_vec_array3_real(real_vec);
}

void FastAceDataObject::set_particle_prod_a_int_data(vector<vector<vector<Integer> > > int_vec)
{
  particle_prod_a_int_data = int_vec;
  clr_obj.clear_vec_array3_int(int_vec);
}

void FastAceDataObject::set_particle_prod_a_data(vector<vector<vector<vector<Real> > > > real_vec)
{
  particle_prod_a_data = real_vec;
  clr_obj.clear_vec_array4_real(real_vec);
}

void FastAceDataObject::set_particle_prod_a_distr_data(vector<vector<vector<vector<Real> > > > real_vec)
{
  particle_prod_a_distr_data = real_vec;
  clr_obj.clear_vec_array4_real(real_vec);
}

void FastAceDataObject::set_particle_prod_a_distr_data_integ(vector<vector<vector<vector<Real> > > > real_vec)
{
  particle_prod_a_distr_data_integ = real_vec;
  clr_obj.clear_vec_array4_real(real_vec);
}

void FastAceDataObject::set_particle_prod_ene_out_coef_a(vector<vector<vector<vector<Real> > > > real_vec)
{
  particle_prod_ene_out_coef_a = real_vec;
  clr_obj.clear_vec_array4_real(real_vec);
}

void FastAceDataObject::set_particle_prod_ene_out_coef_b(vector<vector<vector<vector<Real> > > > real_vec)
{
  particle_prod_ene_out_coef_b = real_vec;
  clr_obj.clear_vec_array4_real(real_vec);
}


//For distr_func_flg = 1 : angle (mu), distr_func_flg = 7 : second energy
void FastAceDataObject::set_particle_prod_b_int_data(vector<vector<vector<vector<Integer> > > > int_vec)
{
  particle_prod_b_int_data = int_vec;
  clr_obj.clear_vec_array4_int(int_vec);
}

void FastAceDataObject::set_particle_prod_b_data(vector<vector<vector<vector<vector<Real> > > > > real_vec)
{
  particle_prod_b_data = real_vec;
  clr_obj.clear_vec_array5_real(real_vec);
}

void FastAceDataObject::set_particle_prod_b_prob_data(vector<vector<vector<vector<vector<Real> > > > > real_vec)
{
  particle_prod_b_prob_data = real_vec;
  clr_obj.clear_vec_array5_real(real_vec);
}

void FastAceDataObject::set_particle_prod_b_prob_data_integ(vector<vector<vector<vector<vector<Real> > > > > real_vec)
{
  particle_prod_b_prob_data_integ = real_vec;
  clr_obj.clear_vec_array5_real(real_vec);
}



//For pointer data
void FastAceDataObject::set_len2(int int_val)
{
  len2 = int_val;
}

void FastAceDataObject::set_nes(int int_val)
{
  nes = int_val;
}

void FastAceDataObject::set_ntrp(int int_val)
{
  ntrp = int_val;
}

void FastAceDataObject::set_ntype(int int_val)
{
  ntype = int_val;
}

void FastAceDataObject::set_ndnf(int int_val)
{
  ndnf = int_val;
}

void FastAceDataObject::set_esz(int int_val)
{
  esz = int_val;
}

void FastAceDataObject::set_nu(int int_val)
{
  nu = int_val;
}

void FastAceDataObject::set_mtr(int int_val)
{
  mtr = int_val;
}

void FastAceDataObject::set_lqr(int int_val)
{
  lqr = int_val;
}

void FastAceDataObject::set_tyr(int int_val)
{
  tyr = int_val;
}

void FastAceDataObject::set_lsig(int int_val)
{
  lsig = int_val;
}

void FastAceDataObject::set_sig(int int_val)
{
  sig = int_val;
}

void FastAceDataObject::set_land(int int_val)
{
  land = int_val;
}

void FastAceDataObject::set_andi(int int_val)
{
  andi = int_val;
}

void FastAceDataObject::set_ldlw(int int_val)
{
  ldlw = int_val;
}

void FastAceDataObject::set_dlw(int int_val)
{
  dlw = int_val;
}

void FastAceDataObject::set_gpd(int int_val)
{
  gpd = int_val;
}

void FastAceDataObject::set_mtrp(int int_val)
{
  mtrp = int_val;
}

void FastAceDataObject::set_lsigp(int int_val)
{
  lsigp = int_val;
}

void FastAceDataObject::set_sigp(int int_val)
{
  sigp = int_val;
}

void FastAceDataObject::set_landp(int int_val)
{
  landp = int_val;
}

void FastAceDataObject::set_andp(int int_val)
{
  andp = int_val;
}

void FastAceDataObject::set_ldlwp(int int_val)
{
  ldlwp = int_val;
}

void FastAceDataObject::set_dlwp(int int_val)
{
  dlwp = int_val;
}

void FastAceDataObject::set_yp(int int_val)
{
  yp = int_val;
}

void FastAceDataObject::set_fis(int int_val)
{
  fis = int_val;
}

void FastAceDataObject::set_endi(int int_val)
{
  endi = int_val;
}

void FastAceDataObject::set_iurpt(int int_val)
{
  iurpt = int_val;
}

void FastAceDataObject::set_nud(int int_val)
{
  nud = int_val;
}

void FastAceDataObject::set_dndat(int int_val)
{
  dndat = int_val;
}

void FastAceDataObject::set_ldnd(int int_val)
{
  ldnd = int_val;
}

void FastAceDataObject::set_dnd(int int_val)
{
  dnd = int_val;
}

void FastAceDataObject::set_ptype(int int_val)
{
  ptype = int_val;
}

void FastAceDataObject::set_ntro(int int_val)
{
  ntro = int_val;
}

void FastAceDataObject::set_ploct(int int_val)
{
  ploct = int_val;
}


void FastAceDataObject::set_ene_distr_pointer(vector<int> int_vec)
{
  ene_distr_pointer = int_vec;
  int_vec.clear();
}

void FastAceDataObject::set_nu_d_pointer(vector<int> int_vec)
{
  nu_d_pointer = int_vec;
  int_vec.clear();
}

void FastAceDataObject::set_photon_prod_pointer(vector<int> int_vec)
{
  photon_prod_pointer = int_vec;
  int_vec.clear();
}

void FastAceDataObject::set_photon_angular_pointer(vector<int> int_vec)
{
  photon_angular_pointer = int_vec;
  int_vec.clear();
}

void FastAceDataObject::set_photon_ene_pointer(vector<int> int_vec)
{
  photon_ene_pointer = int_vec;
  int_vec.clear();
}

void FastAceDataObject::set_photon_ene_distr_pointer(vector<int> int_vec)
{
  photon_ene_distr_pointer = int_vec;
  int_vec.clear();
}

void FastAceDataObject::set_angular_distr_pointer(vector<vector<int> > int_vec)
{
  angular_distr_pointer = int_vec;
  clr_obj.clear_vec_array2_int(int_vec);
}

void FastAceDataObject::set_ene_distr_ene_repr_end_pointer(vector<vector<int> > int_vec)
{
  ene_distr_ene_repr_end_pointer = int_vec;
  clr_obj.clear_vec_array2_int(int_vec);
}

void FastAceDataObject::set_ene_distr_ene_repr_pointer(vector<vector<int> > int_vec)
{
  ene_distr_ene_repr_pointer = int_vec;
  clr_obj.clear_vec_array2_int(int_vec);
}

void FastAceDataObject::set_nu_d_ene_in_pointer(vector<vector<int> > int_vec)
{
  nu_d_ene_in_pointer = int_vec;
  clr_obj.clear_vec_array2_int(int_vec);
}

void FastAceDataObject::set_photon_angular_ene_pointer(vector<vector<int> > int_vec)
{
  photon_angular_ene_pointer = int_vec;
  clr_obj.clear_vec_array2_int(int_vec);
}

void FastAceDataObject::set_photon_ene_weight_pointer(vector<vector<int> > int_vec)
{
  photon_ene_weight_pointer = int_vec;
  clr_obj.clear_vec_array2_int(int_vec);
}

void FastAceDataObject::set_particle_prod_pointer(vector<vector<int> > int_vec)
{
  particle_prod_pointer = int_vec;
  clr_obj.clear_vec_array2_int(int_vec);
}

void FastAceDataObject::set_particle_prod_distr_pointer(vector<vector<int> > int_vec)
{
  particle_prod_distr_pointer = int_vec;
  clr_obj.clear_vec_array2_int(int_vec);
}

void FastAceDataObject::set_particle_prod_angular_pointer(vector<vector<int> > int_vec)
{
  particle_prod_angular_pointer = int_vec;
  clr_obj.clear_vec_array2_int(int_vec);
}

void FastAceDataObject::set_particle_prod_ene_pointer(vector<vector<int> > int_vec)
{
  particle_prod_ene_pointer = int_vec;
  clr_obj.clear_vec_array2_int(int_vec);
}

void FastAceDataObject::set_particle_prod_ene_in_pointer(vector<vector<int> > int_vec)
{
  particle_prod_ene_in_pointer = int_vec;
  clr_obj.clear_vec_array2_int(int_vec);
}

void FastAceDataObject::set_ene_distr_ene_in_pointer(vector<vector<vector<int> > > int_vec)
{
  ene_distr_ene_in_pointer = int_vec;
  clr_obj.clear_vec_array3_int(int_vec);
}

void FastAceDataObject::set_particle_prod_angular_ene_pointer(vector<vector<vector<int> > > int_vec)
{
  particle_prod_angular_ene_pointer = int_vec;
  clr_obj.clear_vec_array3_int(int_vec);
}

void FastAceDataObject::set_particle_prod_a_pointer(vector<vector<vector<int> > > int_vec)
{
  particle_prod_a_pointer = int_vec;
  clr_obj.clear_vec_array3_int(int_vec);
}

void FastAceDataObject::set_ene_distr_ene_out_pointer(vector<vector<vector<vector<int> > > > int_vec)
{
  ene_distr_ene_out_pointer = int_vec;
  clr_obj.clear_vec_array4_int(int_vec);
}

void FastAceDataObject::set_particle_prod_b_pointer(vector<vector<vector<vector<int> > > > int_vec)
{
  particle_prod_b_pointer = int_vec;
  clr_obj.clear_vec_array4_int(int_vec);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//Getter
Integer FastAceDataObject::get_mcnpx_mode_flg()
{
  return mcnpx_mode_flg;
}

Integer FastAceDataObject::get_mat()
{
  return mat;
}

Real    FastAceDataObject::get_temp()
{
  if( fabs(temp) < min_value && fabs(tz) > min_value )
  {
    temp = tz;
  }
  return temp;
}

Real    FastAceDataObject::get_temp_ev()
{
  return get_temp() * 1.0E6;
}

Real    FastAceDataObject::get_temp_kelvin()
{
  Real temp_ev = get_temp_ev();
  return temp_ev / boltzmann_const;
}


vector<Integer> FastAceDataObject::get_zi_vec()
{
  return zi_vec;
}

vector<Real> FastAceDataObject::get_awr_vec()
{
  return awr_vec;
}


Integer FastAceDataObject::get_sub_lib_part()
{
  return sub_lib_part;
}

Integer FastAceDataObject::get_sub_lib_type()
{
  return sub_lib_type;
}

Real    FastAceDataObject::get_ene_max()
{
  return ene_max;
}


vector<Real>             FastAceDataObject::get_union_ene_grid()
{
  return union_ene_grid;
}

vector<Real>             FastAceDataObject::get_gamma_product_xs()
{
  return gamma_product_xs;
}

vector<Real>             FastAceDataObject::get_photon_product_xs()
{
  return photon_product_xs;
}


vector<vector<Integer> > FastAceDataObject::get_particle_production_data()
{
  return particle_production_data;
}

vector<Real>             FastAceDataObject::get_particle_production_ene_data()
{
  return particle_production_ene_data;
}


vector<vector<Real> >    FastAceDataObject::get_photon_prod_yield_coef_direct()
{
  return photon_prod_yield_coef_direct;
}

vector<vector<Real> >    FastAceDataObject::get_photon_prod_yield_coef_given()
{
  return photon_prod_yield_coef_given;
}


vector<Real>             FastAceDataObject::get_photon_xs_ene_min()
{
  return photon_xs_ene_min;
}

vector<Real>             FastAceDataObject::get_photon_prod_discon_ene_data()
{
  return photon_prod_discon_ene_data;
}


vector<vector<Real> >    FastAceDataObject::get_equal_prob_data_ini()
{
  return equal_prob_data_ini;
}


Real           FastAceDataObject::get_aw0()
{
  return aw0;
}
 
Real           FastAceDataObject::get_tz()
{
  return tz;
}

int            FastAceDataObject::get_izaid()
{
  return izaid;
}

 
vector<string> FastAceDataObject::get_title_data()
{
  return title_data;
}

string FastAceDataObject::get_discriptive_data()
{
  return discriptive_data;
}


int             FastAceDataObject::get_ntr()
{
  return ntr;
}

int             FastAceDataObject::get_nr()
{
  return nr;
}

int             FastAceDataObject::get_mtntr()
{
  return mtntr;
}

int             FastAceDataObject::get_mtnr()
{
  return mtnr;
}

Integer         FastAceDataObject::get_nu_bar_repr_flg()
{
  return nu_bar_repr_flg;
}

Integer         FastAceDataObject::get_nu_d_bar_repr_flg()
{
  return nu_d_bar_repr_flg;
}

Integer         FastAceDataObject::get_nu_p_bar_repr_flg()
{
  return nu_p_bar_repr_flg;
}

vector<Integer> FastAceDataObject::get_nu_int_data()
{
  return nu_int_data;
}

vector<Integer> FastAceDataObject::get_nu_range_data()
{
  return nu_range_data;
}

vector<Integer> FastAceDataObject::get_nu_d_int_data()
{
  return nu_d_int_data;
}

vector<Integer> FastAceDataObject::get_nu_d_range_data()
{
  return nu_d_range_data;
}

vector<Integer> FastAceDataObject::get_nu_p_int_data()
{
  return nu_p_int_data;
}

vector<Integer> FastAceDataObject::get_nu_p_range_data()
{
  return nu_p_range_data;
}

vector<Real>    FastAceDataObject::get_nu_data()
{
  return nu_data;
}

vector<Real>    FastAceDataObject::get_nu_ene_data()
{
  return nu_ene_data;
}

vector<Real>    FastAceDataObject::get_nu_d_data()
{
  return nu_d_data;
}

vector<Real>    FastAceDataObject::get_nu_d_ene_data()
{
  return nu_d_ene_data;
}

vector<Real>    FastAceDataObject::get_nu_p_data()
{
  return nu_p_data;
}

vector<Real>    FastAceDataObject::get_nu_p_ene_data()
{
  return nu_p_ene_data;
}

vector<Real>    FastAceDataObject::get_nu_d_decay_constant()
{
  return nu_d_decay_constant;
}


vector<Integer>       FastAceDataObject::get_react_type_list()
{
  return react_type_list;
}

vector<Integer>       FastAceDataObject::get_react_type_flg()
{
  return react_type_flg;
}

vector<Integer>       FastAceDataObject::get_react_type_ene_sta()
{
  return react_type_ene_sta;
}

vector<Real>          FastAceDataObject::get_react_q_value()
{
  return react_q_value;
}

vector<Real>          FastAceDataObject::get_react_xs_tot()
{
  return react_xs_tot;
}

vector<Real>          FastAceDataObject::get_react_xs_cap()
{
  return react_xs_cap;
}

vector<Real>          FastAceDataObject::get_react_xs_sc()
{
  return react_xs_sc;
}

vector<Real>          FastAceDataObject::get_react_xs_heat()
{
  return react_xs_heat;
}

vector<vector<Real> > FastAceDataObject::get_react_xs()
{
  return react_xs;
}


vector<Integer>                FastAceDataObject::get_angular_distr_type_flg()
{
  return angular_distr_type_flg;
}

vector<vector<Integer> >       FastAceDataObject::get_angular_distr_int_data()
{
  return angular_distr_int_data;
}

vector<vector<Real> >          FastAceDataObject::get_angular_distr_ene_data()
{
  return angular_distr_ene_data;
}

vector<vector<vector<Real> > > FastAceDataObject::get_angular_distr_cos_data()
{
  return angular_distr_cos_data;
}

vector<vector<vector<Real> > > FastAceDataObject::get_angular_distr_data()
{
  return angular_distr_data;
}

vector<vector<vector<Real> > > FastAceDataObject::get_angular_distr_data_integ()
{
  return angular_distr_data_integ;
}


vector<vector<Integer> >                FastAceDataObject::get_ene_distr_ene_repr_flg()
{
  return ene_distr_ene_repr_flg;
}

vector<vector<vector<Integer> > >       FastAceDataObject::get_ene_distr_xs_part_int_data()
{
  return ene_distr_xs_part_int_data;
}

vector<vector<vector<Integer> > >       FastAceDataObject::get_ene_distr_xs_part_range_data()
{
  return ene_distr_xs_part_range_data;
}

vector<vector<vector<Real> > >          FastAceDataObject::get_ene_distr_xs_part_ene_data()
{
  return ene_distr_xs_part_ene_data;
}

vector<vector<vector<Real> > >          FastAceDataObject::get_ene_distr_xs_part_data()
{
  return ene_distr_xs_part_data;
}

vector<vector<Real> >                   FastAceDataObject::get_ene_distr_q_coef()
{
  return ene_distr_q_coef;
}

vector<vector<Real> >                   FastAceDataObject::get_ene_distr_mass_coef()
{
  return ene_distr_mass_coef;
}

vector<vector<vector<Integer> > >       FastAceDataObject::get_ene_distr_ene_in_int_data()
{
  return ene_distr_ene_in_int_data;
}

vector<vector<vector<Integer> > >       FastAceDataObject::get_ene_distr_ene_in_range_data()
{
  return ene_distr_ene_in_range_data;
}

vector<vector<vector<Real> > >          FastAceDataObject::get_ene_distr_ene_in_data()
{
  return ene_distr_ene_in_data;
}

vector<vector<vector<Integer> > >       FastAceDataObject::get_ene_distr_ene_out_int_data()
{
  return ene_distr_ene_out_int_data;
}

vector<vector<vector<vector<Real> > > > FastAceDataObject::get_ene_distr_ene_out_ene_data()
{
  return ene_distr_ene_out_ene_data;
}

vector<vector<vector<vector<Real> > > > FastAceDataObject::get_ene_distr_ene_out_data()
{
  return ene_distr_ene_out_data;
}

vector<vector<vector<vector<Real> > > > FastAceDataObject::get_ene_distr_ene_out_data_integ()
{
  return ene_distr_ene_out_data_integ;
}

vector<vector<Real> >                   FastAceDataObject::get_ene_distr_upper_ene_limit()
{
  return ene_distr_upper_ene_limit;
}

vector<vector<vector<Integer> > >       FastAceDataObject::get_ene_distr_temp_eff_int_data()
{
  return ene_distr_temp_eff_int_data;
}

vector<vector<vector<Integer> > >       FastAceDataObject::get_ene_distr_temp_eff_range_data()
{
  return ene_distr_temp_eff_range_data;
}

vector<vector<vector<Integer> > >       FastAceDataObject::get_ene_distr_watt_a_int_data()
{
  return ene_distr_watt_a_int_data;
}

vector<vector<vector<Integer> > >       FastAceDataObject::get_ene_distr_watt_a_range_data()
{
  return ene_distr_watt_a_range_data;
}

vector<vector<vector<Integer> > >       FastAceDataObject::get_ene_distr_watt_b_int_data()
{
  return ene_distr_watt_b_int_data;
}

vector<vector<vector<Integer> > >       FastAceDataObject::get_ene_distr_watt_b_range_data()
{
  return ene_distr_watt_b_range_data;
}

vector<vector<vector<Real> > >          FastAceDataObject::get_ene_distr_temp_eff_ene_data()
{
  return ene_distr_temp_eff_ene_data;
}

vector<vector<vector<Real> > >          FastAceDataObject::get_ene_distr_temp_eff_data()
{
  return ene_distr_temp_eff_data;
}

vector<vector<vector<Real> > >          FastAceDataObject::get_ene_distr_watt_a_ene_data()
{
  return ene_distr_watt_a_ene_data;
}

vector<vector<vector<Real> > >          FastAceDataObject::get_ene_distr_watt_a_data()
{
  return ene_distr_watt_a_data;
}

vector<vector<vector<Real> > >          FastAceDataObject::get_ene_distr_watt_b_ene_data()
{
  return ene_distr_watt_b_ene_data;
}

vector<vector<vector<Real> > >          FastAceDataObject::get_ene_distr_watt_b_data()
{
  return ene_distr_watt_b_data;
}


vector<vector<Integer> >                            FastAceDataObject::get_prod_yield_tot_int_data()
{
  return prod_yield_tot_int_data;
}

vector<vector<Integer> >                            FastAceDataObject::get_prod_yield_tot_range_data()
{
  return prod_yield_tot_range_data;
}

vector<vector<Real> >                               FastAceDataObject::get_prod_yield_tot_ene_data()
{
  return prod_yield_tot_ene_data;
}

vector<vector<Real> >                               FastAceDataObject::get_prod_yield_tot_data()
{
  return prod_yield_tot_data;
}

vector<vector<Integer> >                            FastAceDataObject::get_prod_distr_func_flg()
{
  return prod_distr_func_flg;
}

vector<vector<Real> >                               FastAceDataObject::get_prod_distr_n_body_mass()
{
  return prod_distr_n_body_mass;
}

vector<vector<Integer> >                            FastAceDataObject::get_prod_distr_prob_data_no()
{
  return prod_distr_prob_data_no;
}

vector<vector<Integer> >                            FastAceDataObject::get_prod_distr_n_body_particle_no()
{
  return prod_distr_n_body_particle_no;
}

vector<vector<vector<Integer> > >                   FastAceDataObject::get_prod_distr_prob_ene_in_int_data()
{
  return prod_distr_prob_ene_in_int_data;
}

vector<vector<vector<Integer> > >                   FastAceDataObject::get_prod_distr_prob_ene_in_range_data()
{
  return prod_distr_prob_ene_in_range_data;
}

vector<vector<vector<Integer> > >                   FastAceDataObject::get_prod_distr_prob_ene_out_int_data()
{
  return prod_distr_prob_ene_out_int_data;
}

vector<vector<vector<Real> > >                      FastAceDataObject::get_prod_distr_prob_ene_in_data()
{
  return prod_distr_prob_ene_in_data;
}

vector<vector<vector<vector<Integer> > > >          FastAceDataObject::get_prod_distr_prob_mu_int_data()
{
  return prod_distr_prob_mu_int_data;
}

vector<vector<vector<vector<Integer> > > >          FastAceDataObject::get_prod_distr_prob_mu_range_data()
{
  return prod_distr_prob_mu_range_data;
}

vector<vector<vector<vector<Real> > > >             FastAceDataObject::get_prod_distr_prob_mu_data()
{
  return prod_distr_prob_mu_data;
}

vector<vector<vector<vector<Real> > > >             FastAceDataObject::get_prod_distr_prob_mu_data_integ()
{
  return prod_distr_prob_mu_data_integ;
}

vector<vector<vector<vector<Real> > > >             FastAceDataObject::get_prod_distr_prob_data()
{
  return prod_distr_prob_data;
}

vector<vector<vector<vector<Real> > > >             FastAceDataObject::get_prod_distr_prob_data_integ()
{
  return prod_distr_prob_data_integ;
}

vector<vector<vector<vector<Real> > > >             FastAceDataObject::get_prod_distr_prob_ene_out_data()
{
  return prod_distr_prob_ene_out_data;
}

vector<vector<vector<vector<Real> > > >             FastAceDataObject::get_prod_distr_prob_coef_a()
{
  return prod_distr_prob_coef_a;
}

vector<vector<vector<vector<Real> > > >             FastAceDataObject::get_prod_distr_prob_coef_b()
{
  return prod_distr_prob_coef_b;
}

vector<vector<vector<vector<vector<Integer> > > > > FastAceDataObject::get_prod_distr_prob_int_vec()
{
  return prod_distr_prob_int_vec;
}

vector<vector<vector<vector<vector<Integer> > > > > FastAceDataObject::get_prod_distr_prob_range_vec()
{
  return prod_distr_prob_range_vec;
}

vector<vector<vector<vector<vector<Real> > > > >    FastAceDataObject::get_prod_distr_prob_mu_vec()
{
  return prod_distr_prob_mu_vec;
}

vector<vector<vector<vector<vector<Real> > > > >    FastAceDataObject::get_prod_distr_prob_ene_out_vec()
{
  return prod_distr_prob_ene_out_vec;
}

vector<vector<vector<vector<vector<Real> > > > >    FastAceDataObject::get_prod_distr_prob_vec()
{
  return prod_distr_prob_vec;
}

vector<vector<vector<vector<vector<Real> > > > >    FastAceDataObject::get_prod_distr_prob_vec_integ()
{
  return prod_distr_prob_vec_integ;
}


Integer                        FastAceDataObject::get_unreso_prob_tab_int_data()
{
  return unreso_prob_tab_int_data;
}

Integer                        FastAceDataObject::get_unreso_prob_tab_inela_comp_flg()
{
  return unreso_prob_tab_inela_comp_flg;
}

Integer                        FastAceDataObject::get_unreso_prob_tab_abs_comp_flg()
{
  return unreso_prob_tab_abs_comp_flg;
}

Integer                        FastAceDataObject::get_unreso_prob_tab_self_shielding_flg()
{
  return unreso_prob_tab_self_shielding_flg;
}

vector<Real>                   FastAceDataObject::get_unreso_prob_tab_ene()
{
  return unreso_prob_tab_ene;
}

vector<vector<Real> >          FastAceDataObject::get_unreso_prob_tab_heat()
{
  return unreso_prob_tab_heat;
}

vector<vector<Real> >          FastAceDataObject::get_unreso_prob_tab_sample_no()
{
  return unreso_prob_tab_sample_no;
}

vector<vector<vector<Real> > > FastAceDataObject::get_unreso_prob_tab_table()
{
  return unreso_prob_tab_table;
}


vector<Real>                   FastAceDataObject::get_nu_d_ene_min()
{
  return nu_d_ene_min;
}

vector<Real>                   FastAceDataObject::get_nu_d_ene_max()
{
  return nu_d_ene_max;
}

vector<vector<Integer> >       FastAceDataObject::get_nu_d_xs_part_int_data()
{
  return nu_d_xs_part_int_data;
}

vector<vector<Integer> >       FastAceDataObject::get_nu_d_xs_part_range_data()
{
  return nu_d_xs_part_range_data;
}

vector<vector<Real> >          FastAceDataObject::get_nu_d_xs_part_ene_data()
{
  return nu_d_xs_part_ene_data;
}

vector<vector<Real> >          FastAceDataObject::get_nu_d_xs_part_data()
{
  return nu_d_xs_part_data;
}

vector<vector<Integer> >       FastAceDataObject::get_nu_d_ene_in_int_data()
{
  return nu_d_ene_in_int_data;
}

vector<vector<Integer> >       FastAceDataObject::get_nu_d_ene_in_range_data()
{
  return nu_d_ene_in_range_data;
}

vector<vector<Integer> >       FastAceDataObject::get_nu_d_ene_out_int_data()
{
  return nu_d_ene_out_int_data;
}

vector<vector<Real> >          FastAceDataObject::get_nu_d_ene_in_data()
{
  return nu_d_ene_in_data;
}

vector<vector<vector<Real> > > FastAceDataObject::get_nu_d_ene_out_data()
{
  return nu_d_ene_out_data;
}

vector<vector<vector<Real> > > FastAceDataObject::get_nu_d_ene_distr_data()
{
  return nu_d_ene_distr_data;
}

vector<vector<vector<Real> > > FastAceDataObject::get_nu_d_ene_distr_data_integ()
{
  return nu_d_ene_distr_data_integ;
}


vector<Integer>          FastAceDataObject::get_photon_prod_file_no()
{
  return photon_prod_file_no;
}

vector<Integer>          FastAceDataObject::get_photon_prod_reaction_type()
{
  return photon_prod_reaction_type;
}

vector<Integer>          FastAceDataObject::get_photon_prod_reaction_type_all()
{
  return photon_prod_reaction_type_all;
}

vector<Integer>          FastAceDataObject::get_photon_prod_reaction_type_without_xs()
{
  return photon_prod_reaction_type_without_xs;
}

vector<Real>             FastAceDataObject::get_photon_prod_binding_ene()
{
  return photon_prod_binding_ene;
}

vector<vector<Integer> > FastAceDataObject::get_photon_prod_multiplicity_int_data()
{
  return photon_prod_multiplicity_int_data;
}

vector<vector<Integer> > FastAceDataObject::get_photon_prod_multiplicity_range_data()
{
  return photon_prod_multiplicity_range_data;
}

vector<vector<Real> >    FastAceDataObject::get_photon_prod_multiplicity_ene_data()
{
  return photon_prod_multiplicity_ene_data;
}

vector<vector<Real> >    FastAceDataObject::get_photon_prod_multiplicity_data()
{
  return photon_prod_multiplicity_data;
}

vector<int>              FastAceDataObject::get_photon_prod_xs_ene_no()
{
  return photon_prod_xs_ene_no;
}

vector<vector<int> >     FastAceDataObject::get_photon_prod_xs_non_zero_pos()
{
  return photon_prod_xs_non_zero_pos;
}

vector<vector<Real> >    FastAceDataObject::get_photon_prod_xs_data()
{
  return photon_prod_xs_data;
}

vector<vector<Integer> > FastAceDataObject::get_photon_prod_distr_int_data()
{
  return photon_prod_distr_int_data;
}

vector<vector<Integer> > FastAceDataObject::get_photon_prod_distr_range_data()
{
  return photon_prod_distr_range_data;
}

vector<vector<Real> >    FastAceDataObject::get_photon_prod_distr_ene_data()
{
  return photon_prod_distr_ene_data;
}

vector<vector<Real> >    FastAceDataObject::get_photon_prod_distr_data()
{
  return photon_prod_distr_data;
}


vector<vector<Real> >          FastAceDataObject::get_photon_angular_distr_ene_data()
{
  return photon_angular_distr_ene_data;
}

vector<vector<vector<Real> > > FastAceDataObject::get_photon_angular_distr_prob_cos_data()
{
  return photon_angular_distr_prob_cos_data;
}


vector<Integer>                   FastAceDataObject::get_photon_energy_distr_flg()
{
  return photon_energy_distr_flg;
}

vector<Integer>                   FastAceDataObject::get_photon_energy_distr_ene_flg()
{
  return photon_energy_distr_ene_flg;
}

vector<Real>                      FastAceDataObject::get_photon_energy_distr_binding_ene_data()
{
  return photon_energy_distr_binding_ene_data;
}

vector<vector<Integer> >          FastAceDataObject::get_photon_energy_distr_int_data()
{
  return photon_energy_distr_int_data;
}

vector<vector<Integer> >          FastAceDataObject::get_photon_energy_distr_range_data()
{
  return photon_energy_distr_range_data;
}

vector<vector<Real> >             FastAceDataObject::get_photon_energy_distr_ene_data()
{
  return photon_energy_distr_ene_data;
}

vector<vector<Real> >             FastAceDataObject::get_photon_energy_distr_prob_data()
{
  return photon_energy_distr_prob_data;
}

vector<vector<Integer> >          FastAceDataObject::get_photon_energy_distr_ene_in_int_data()
{
  return photon_energy_distr_ene_in_int_data;
}

vector<vector<Integer> >          FastAceDataObject::get_photon_energy_distr_ene_in_range_data()
{
  return photon_energy_distr_ene_in_range_data;
}

vector<vector<Real> >             FastAceDataObject::get_photon_energy_distr_ene_in_data()
{
  return photon_energy_distr_ene_in_data;
}

vector<vector<Integer> >          FastAceDataObject::get_photon_energy_distr_weight_int_data()
{
  return photon_energy_distr_weight_int_data;
}

vector<vector<vector<Real> > >    FastAceDataObject::get_photon_energy_distr_weight_ene_data()
{
  return photon_energy_distr_weight_ene_data;
}

vector<vector<vector<Real> > >    FastAceDataObject::get_photon_energy_distr_weight_data()
{
  return photon_energy_distr_weight_data;
}

vector<vector<vector<Real> > >    FastAceDataObject::get_photon_energy_distr_weight_data_integ()
{
  return photon_energy_distr_weight_data_integ;
}

vector<Real>                      FastAceDataObject::get_photon_energy_distr_gamma_mass_product()
{
  return photon_energy_distr_gamma_mass_product;
}


vector<Integer>                          FastAceDataObject::get_particle_prod_flg()
{
  return particle_prod_flg;
}

vector<Integer>                          FastAceDataObject::get_particle_prod_count()
{
  return particle_prod_count;
}

vector<Integer>                          FastAceDataObject::get_particle_prod_ene_sta()
{
  return particle_prod_ene_sta;
}

vector<Integer>                          FastAceDataObject::get_particle_prod_ene_no()
{
  return particle_prod_ene_no;
}

vector<vector<Integer> >                 FastAceDataObject::get_particle_prod_file_no()
{
  return particle_prod_file_no;
}

vector<vector<Integer> >                 FastAceDataObject::get_particle_prod_frame_flg()
{
  return particle_prod_frame_flg;
}

vector<vector<Integer> >                 FastAceDataObject::get_particle_prod_reaction_type()
{
  return particle_prod_reaction_type;
}

vector<vector<Integer> >                 FastAceDataObject::get_particle_prod_reaction_type_all()
{
  return particle_prod_reaction_type_all;
}

vector<vector<Real> >                    FastAceDataObject::get_particle_prod_xs()
{
  return particle_prod_xs;
}

vector<vector<Real> >                    FastAceDataObject::get_particle_prod_heat()
{
  return particle_prod_heat;
}

vector<vector<vector<Integer> > >        FastAceDataObject::get_particle_prod_distr_int_data()
{
  return particle_prod_distr_int_data;
}

vector<vector<vector<Integer> > >        FastAceDataObject::get_particle_prod_distr_range_data()
{
  return particle_prod_distr_range_data;
}

vector<vector<vector<Real> > >           FastAceDataObject::get_particle_prod_distr_ene_data()
{
  return particle_prod_distr_ene_data;
}

vector<vector<vector<Real> > >           FastAceDataObject::get_particle_prod_distr_data()
{
  return particle_prod_distr_data;
}

vector<vector<vector<Integer> > >        FastAceDataObject::get_particle_prod_angular_int_data()
{
  return particle_prod_angular_int_data;
}

vector<vector<vector<Real> > >           FastAceDataObject::get_particle_prod_angular_ene_data()
{
  return particle_prod_angular_ene_data;
}

vector<vector<vector<vector<Real> > > >  FastAceDataObject::get_particle_prod_angular_cos_data()
{
  return particle_prod_angular_cos_data;
}

vector<vector<vector<vector<Real> > > >  FastAceDataObject::get_particle_prod_angular_distr_data()
{
  return particle_prod_angular_distr_data;
}

vector<vector<vector<vector<Real> > > >  FastAceDataObject::get_particle_prod_angular_distr_data_integ()
{
  return particle_prod_angular_distr_data_integ;
}


vector<vector<Integer> >          FastAceDataObject::get_particle_prod_ene_flg()
{
  return particle_prod_ene_flg;
}

vector<vector<Real> >             FastAceDataObject::get_particle_prod_q_value()
{
  return particle_prod_q_value;
}

vector<vector<Real> >             FastAceDataObject::get_particle_prod_mass_coef()
{
  return particle_prod_mass_coef;
}

vector<vector<vector<Integer> > > FastAceDataObject::get_particle_prod_ene_int_data()
{
  return particle_prod_ene_int_data;
}

vector<vector<vector<Integer> > > FastAceDataObject::get_particle_prod_ene_range_data()
{
  return particle_prod_ene_range_data;
}

vector<vector<vector<Real> > >    FastAceDataObject::get_particle_prod_ene_data()
{
  return particle_prod_ene_data;
}

vector<vector<vector<Real> > >    FastAceDataObject::get_particle_prod_ene_prob_data()
{
  return particle_prod_ene_prob_data;
}


//For distr_func_flg = 1 : second energy, distr_func_flg = 7 : angle (mu)
vector<vector<vector<Integer> > >          FastAceDataObject::get_particle_prod_ene_in_int_data()
{
  return particle_prod_ene_in_int_data;
}

vector<vector<vector<Integer> > >          FastAceDataObject::get_particle_prod_ene_in_range_data()
{
  return particle_prod_ene_in_range_data;
}

vector<vector<vector<Real> > >             FastAceDataObject::get_particle_prod_ene_in_data()
{
  return particle_prod_ene_in_data;
}

vector<vector<vector<Integer> > >          FastAceDataObject::get_particle_prod_a_int_data()
{
  return particle_prod_a_int_data;
}

vector<vector<vector<vector<Real> > > >    FastAceDataObject::get_particle_prod_a_data()
{
  return particle_prod_a_data;
}

vector<vector<vector<vector<Real> > > >    FastAceDataObject::get_particle_prod_a_distr_data()
{
  return particle_prod_a_distr_data;
}

vector<vector<vector<vector<Real> > > >    FastAceDataObject::get_particle_prod_a_distr_data_integ()
{
  return particle_prod_a_distr_data_integ;
}

vector<vector<vector<vector<Real> > > >    FastAceDataObject::get_particle_prod_ene_out_coef_a()
{
  return particle_prod_ene_out_coef_a;
}

vector<vector<vector<vector<Real> > > >    FastAceDataObject::get_particle_prod_ene_out_coef_b()
{
  return particle_prod_ene_out_coef_b;
}


//For distr_func_flg = 1 : angle (mu), distr_func_flg = 7 : second energy
vector<vector<vector<vector<Integer> > > >       FastAceDataObject::get_particle_prod_b_int_data()
{
  return particle_prod_b_int_data;
}

vector<vector<vector<vector<vector<Real> > > > > FastAceDataObject::get_particle_prod_b_data()
{
  return particle_prod_b_data;
}

vector<vector<vector<vector<vector<Real> > > > > FastAceDataObject::get_particle_prod_b_prob_data()
{
  return particle_prod_b_prob_data;
}

vector<vector<vector<vector<vector<Real> > > > > FastAceDataObject::get_particle_prod_b_prob_data_integ()
{
  return particle_prod_b_prob_data_integ;
}



//For pointer data
int         FastAceDataObject::get_len2()
{
  return len2;
}

int         FastAceDataObject::get_nes()
{
  return nes;
}

int         FastAceDataObject::get_ntrp()
{
  return ntrp;
}

int         FastAceDataObject::get_ntype()
{
  return ntype;
}

int         FastAceDataObject::get_ndnf()
{
  return ndnf;
}

int         FastAceDataObject::get_esz()
{
  return esz;
}

int         FastAceDataObject::get_nu()
{
  return nu;
}

int         FastAceDataObject::get_mtr()
{
  return mtr;
}

int         FastAceDataObject::get_lqr()
{
  return lqr;
}

int         FastAceDataObject::get_tyr()
{
  return tyr;
}

int         FastAceDataObject::get_lsig()
{
  return lsig;
}

int         FastAceDataObject::get_sig()
{
  return sig;
}

int         FastAceDataObject::get_land()
{
  return land;
}

int         FastAceDataObject::get_andi()
{
  return andi;
}

int         FastAceDataObject::get_ldlw()
{
  return ldlw;
}

int         FastAceDataObject::get_dlw()
{
  return dlw;
}

int         FastAceDataObject::get_gpd()
{
  return gpd;
}

int         FastAceDataObject::get_mtrp()
{
  return mtrp;
}

int         FastAceDataObject::get_lsigp()
{
  return lsigp;
}

int         FastAceDataObject::get_sigp()
{
  return sigp;
}

int         FastAceDataObject::get_landp()
{
  return landp;
}

int         FastAceDataObject::get_andp()
{
  return andp;
}

int         FastAceDataObject::get_ldlwp()
{
  return ldlwp;
}

int         FastAceDataObject::get_dlwp()
{
  return dlwp;
}

int         FastAceDataObject::get_yp()
{
  return yp;
}

int         FastAceDataObject::get_fis()
{
  return fis;
}

int         FastAceDataObject::get_endi()
{
  return endi;
}

int         FastAceDataObject::get_iurpt()
{
  return iurpt;
}

int         FastAceDataObject::get_nud()
{
  return nud;
}

int         FastAceDataObject::get_dndat()
{
  return dndat;
}

int         FastAceDataObject::get_ldnd()
{
  return ldnd;
}

int         FastAceDataObject::get_dnd()
{
  return dnd;
}

int         FastAceDataObject::get_ptype()
{
  return ptype;
}

int         FastAceDataObject::get_ntro()
{
  return ntro;
}

int         FastAceDataObject::get_ploct()
{
  return ploct;
}


vector<int>                            FastAceDataObject::get_ene_distr_pointer()
{
  return ene_distr_pointer;
}

vector<int>                            FastAceDataObject::get_nu_d_pointer()
{
  return nu_d_pointer;
}

vector<int>                            FastAceDataObject::get_photon_prod_pointer()
{
  return photon_prod_pointer;
}

vector<int>                            FastAceDataObject::get_photon_angular_pointer()
{
  return photon_angular_pointer;
}

vector<int>                            FastAceDataObject::get_photon_ene_pointer()
{
  return photon_ene_pointer;
}

vector<int>                            FastAceDataObject::get_photon_ene_distr_pointer()
{
  return photon_ene_distr_pointer;
}

vector<vector<int> >                   FastAceDataObject::get_angular_distr_pointer()
{
  return angular_distr_pointer;
}

vector<vector<int> >                   FastAceDataObject::get_ene_distr_ene_repr_end_pointer()
{
  return ene_distr_ene_repr_end_pointer;
}

vector<vector<int> >                   FastAceDataObject::get_ene_distr_ene_repr_pointer()
{
  return ene_distr_ene_repr_pointer;
}

vector<vector<int> >                   FastAceDataObject::get_nu_d_ene_in_pointer()
{
  return nu_d_ene_in_pointer;
}

vector<vector<int> >                   FastAceDataObject::get_photon_angular_ene_pointer()
{
  return photon_angular_ene_pointer;
}

vector<vector<int> >                   FastAceDataObject::get_photon_ene_weight_pointer()
{
  return photon_ene_weight_pointer;
}

vector<vector<int> >                   FastAceDataObject::get_particle_prod_pointer()
{
  return particle_prod_pointer;
}

vector<vector<int> >                   FastAceDataObject::get_particle_prod_distr_pointer()
{
  return particle_prod_distr_pointer;
}

vector<vector<int> >                   FastAceDataObject::get_particle_prod_angular_pointer()
{
  return particle_prod_angular_pointer;
}

vector<vector<int> >                   FastAceDataObject::get_particle_prod_ene_pointer()
{
  return particle_prod_ene_pointer;
}

vector<vector<int> >                   FastAceDataObject::get_particle_prod_ene_in_pointer()
{
  return particle_prod_ene_in_pointer;
}

vector<vector<vector<int> > >          FastAceDataObject::get_ene_distr_ene_in_pointer()
{
  return ene_distr_ene_in_pointer;
}

vector<vector<vector<int> > >          FastAceDataObject::get_particle_prod_angular_ene_pointer()
{
  return particle_prod_angular_ene_pointer;
}

vector<vector<vector<int> > > FastAceDataObject::get_particle_prod_a_pointer()
{
  return particle_prod_a_pointer;
}

vector<vector<vector<vector<int> > > > FastAceDataObject::get_ene_distr_ene_out_pointer()
{
  return ene_distr_ene_out_pointer;
}

vector<vector<vector<vector<int> > > > FastAceDataObject::get_particle_prod_b_pointer()
{
  return particle_prod_b_pointer;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

