#include "ThermalScatter/IncoherentInelasticScatterCalculator.hpp"

using namespace frendy;

//Initialize static const value
const Real8 IncoherentInelasticScatterCalculator::min_sab_index_number = -225.0;
const Real8 IncoherentInelasticScatterCalculator::min_sab_value        = 1.0E-225;
const Real8 IncoherentInelasticScatterCalculator::beta_max_warning_val = 5.0;
const Real8 IncoherentInelasticScatterCalculator::alpha_min_val        = 1.0E-6;

//constructor
IncoherentInelasticScatterCalculator::IncoherentInelasticScatterCalculator(void)
{
  lagrange_interpolation_flg = no_interpolation_mode;
  //ene_grid_flg               = use_nucl_ene_grid;
  ene_grid_flg               = linearize_ene_grid;

  min_inelastic_xs_val       = min_sig_val;
  conv_th_ene_inv            = 1.0 / conv_th_ene;
  third                      = 1.0 / 3.0;

  ene_in_incoherent_inelastic.resize(118);
  ene_in_incoherent_inelastic[  0] = 1.0000e-5;
  ene_in_incoherent_inelastic[  1] = 1.7800e-5;
  ene_in_incoherent_inelastic[  2] = 2.5000e-5;
  ene_in_incoherent_inelastic[  3] = 3.5000e-5;
  ene_in_incoherent_inelastic[  4] = 5.0000e-5;
  ene_in_incoherent_inelastic[  5] = 7.0000e-5;
  ene_in_incoherent_inelastic[  6] = 1.0000e-4;
  ene_in_incoherent_inelastic[  7] = 1.2600e-4;
  ene_in_incoherent_inelastic[  8] = 1.6000e-4;
  ene_in_incoherent_inelastic[  9] = 2.0000e-4;
  ene_in_incoherent_inelastic[ 10] = 0.0002530;
  ene_in_incoherent_inelastic[ 11] = 0.0002970;
  ene_in_incoherent_inelastic[ 12] = 0.0003500;
  ene_in_incoherent_inelastic[ 13] = 0.0004200;
  ene_in_incoherent_inelastic[ 14] = 0.0005060;
  ene_in_incoherent_inelastic[ 15] = 0.0006150;
  ene_in_incoherent_inelastic[ 16] = 0.0007500;
  ene_in_incoherent_inelastic[ 17] = 0.0008700;
  ene_in_incoherent_inelastic[ 18] = 0.0010120;
  ene_in_incoherent_inelastic[ 19] = 0.0012300;
  ene_in_incoherent_inelastic[ 20] = 0.0015000;
  ene_in_incoherent_inelastic[ 21] = 0.0018000;
  ene_in_incoherent_inelastic[ 22] = 0.0020300;
  ene_in_incoherent_inelastic[ 23] = 0.0022770;
  ene_in_incoherent_inelastic[ 24] = 0.0026000;
  ene_in_incoherent_inelastic[ 25] = 0.0030000;
  ene_in_incoherent_inelastic[ 26] = 0.0035000;
  ene_in_incoherent_inelastic[ 27] = 0.0040480;
  ene_in_incoherent_inelastic[ 28] = 0.0045000;
  ene_in_incoherent_inelastic[ 29] = 0.0050000;
  ene_in_incoherent_inelastic[ 30] = 0.0056000;
  ene_in_incoherent_inelastic[ 31] = 0.0063250;
  ene_in_incoherent_inelastic[ 32] = 0.0072000;
  ene_in_incoherent_inelastic[ 33] = 0.0081000;
  ene_in_incoherent_inelastic[ 34] = 0.0091080;
  ene_in_incoherent_inelastic[ 35] = 0.0100000;
  ene_in_incoherent_inelastic[ 36] = 0.0106300;
  ene_in_incoherent_inelastic[ 37] = 0.0115000;
  ene_in_incoherent_inelastic[ 38] = 0.0123970;
  ene_in_incoherent_inelastic[ 39] = 0.0133000;
  ene_in_incoherent_inelastic[ 40] = 0.0141700;
  ene_in_incoherent_inelastic[ 41] = 0.0150000;
  ene_in_incoherent_inelastic[ 42] = 0.0161920;
  ene_in_incoherent_inelastic[ 43] = 0.0182000;
  ene_in_incoherent_inelastic[ 44] = 0.0199000;
  ene_in_incoherent_inelastic[ 45] = 0.0204930;
  ene_in_incoherent_inelastic[ 46] = 0.0215000;
  ene_in_incoherent_inelastic[ 47] = 0.0228000;
  ene_in_incoherent_inelastic[ 48] = 0.0253000;
  ene_in_incoherent_inelastic[ 49] = 0.0280000;
  ene_in_incoherent_inelastic[ 50] = 0.0306130;
  ene_in_incoherent_inelastic[ 51] = 0.0338000;
  ene_in_incoherent_inelastic[ 52] = 0.0365000;
  ene_in_incoherent_inelastic[ 53] = 0.0395000;
  ene_in_incoherent_inelastic[ 54] = 0.0427570;
  ene_in_incoherent_inelastic[ 55] = 0.0465000;
  ene_in_incoherent_inelastic[ 56] = 0.0500000;
  ene_in_incoherent_inelastic[ 57] = 0.0569250;
  ene_in_incoherent_inelastic[ 58] = 0.0625000;
  ene_in_incoherent_inelastic[ 59] = 0.0690000;
  ene_in_incoherent_inelastic[ 60] = 0.0750000;
  ene_in_incoherent_inelastic[ 61] = 0.0819720;
  ene_in_incoherent_inelastic[ 62] = 0.0900000;
  ene_in_incoherent_inelastic[ 63] = 0.0960000;
  ene_in_incoherent_inelastic[ 64] = 0.1035000;
  ene_in_incoherent_inelastic[ 65] = 0.1115730;
  ene_in_incoherent_inelastic[ 66] = 0.1200000;
  ene_in_incoherent_inelastic[ 67] = 0.1280000;
  ene_in_incoherent_inelastic[ 68] = 0.1355000;
  ene_in_incoherent_inelastic[ 69] = 0.1457280;
  ene_in_incoherent_inelastic[ 70] = 0.1600000;
  ene_in_incoherent_inelastic[ 71] = 0.1720000;
  ene_in_incoherent_inelastic[ 72] = 0.1844370;
  ene_in_incoherent_inelastic[ 73] = 0.2000000;
  ene_in_incoherent_inelastic[ 74] = 0.2277000;
  ene_in_incoherent_inelastic[ 75] = 0.2510392;
  ene_in_incoherent_inelastic[ 76] = 0.2705304;
  ene_in_incoherent_inelastic[ 77] = 0.2907501;
  ene_in_incoherent_inelastic[ 78] = 0.3011332;
  ene_in_incoherent_inelastic[ 79] = 0.3206421;
  ene_in_incoherent_inelastic[ 80] = 0.3576813;
  ene_in_incoherent_inelastic[ 81] = 0.3900000;
  ene_in_incoherent_inelastic[ 82] = 0.4170351;
  ene_in_incoherent_inelastic[ 83] = 0.4500000;
  ene_in_incoherent_inelastic[ 84] = 0.5032575;
  ene_in_incoherent_inelastic[ 85] = 0.5600000;
  ene_in_incoherent_inelastic[ 86] = 0.6250000;
  ene_in_incoherent_inelastic[ 87] = 0.7000000;
  ene_in_incoherent_inelastic[ 88] = 0.7800000;
  ene_in_incoherent_inelastic[ 89] = 0.8600000;
  ene_in_incoherent_inelastic[ 90] = 0.9500000;
  ene_in_incoherent_inelastic[ 91] = 1.0500000;
  ene_in_incoherent_inelastic[ 92] = 1.1600000;
  ene_in_incoherent_inelastic[ 93] = 1.2800000;
  ene_in_incoherent_inelastic[ 94] = 1.4200000;
  ene_in_incoherent_inelastic[ 95] = 1.5500000;
  ene_in_incoherent_inelastic[ 96] = 1.7000000;
  ene_in_incoherent_inelastic[ 97] = 1.8550000;
  ene_in_incoherent_inelastic[ 98] = 2.0200000;
  ene_in_incoherent_inelastic[ 99] = 2.1800000;
  ene_in_incoherent_inelastic[100] = 2.3600000;
  ene_in_incoherent_inelastic[101] = 2.5900000;
  ene_in_incoherent_inelastic[102] = 2.8550000;
  ene_in_incoherent_inelastic[103] = 3.1200000;
  ene_in_incoherent_inelastic[104] = 3.4200000;
  ene_in_incoherent_inelastic[105] = 3.7500000;
  ene_in_incoherent_inelastic[106] = 4.0700000;
  ene_in_incoherent_inelastic[107] = 4.4600000;
  ene_in_incoherent_inelastic[108] = 4.9000000;
  ene_in_incoherent_inelastic[109] = 5.3500000;
  ene_in_incoherent_inelastic[110] = 5.8500000;
  ene_in_incoherent_inelastic[111] = 6.4000000;
  ene_in_incoherent_inelastic[112] = 7.0000000;
  ene_in_incoherent_inelastic[113] = 7.6500000;
  ene_in_incoherent_inelastic[114] = 8.4000000;
  ene_in_incoherent_inelastic[115] = 9.1500000;
  ene_in_incoherent_inelastic[116] = 9.8500000;
  ene_in_incoherent_inelastic[117] = 10.000000;

  clear();
}

//destructor
IncoherentInelasticScatterCalculator::~IncoherentInelasticScatterCalculator(void)
{
  conv_th_ene_inv = 0.0;
  third           = 0.0;

  ene_in_incoherent_inelastic.clear();

  clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void IncoherentInelasticScatterCalculator::clear()
{
  nucl_data_obj.clear();
  sab_data_obj.clear();

  bin_no_int        = -1;
  bin_no            = -1;
  opt_inelastic     = -1;
  atom_no           = -1;

  temp_tsl          = -1.0;
  temp_tsl_ev       = -1.0;
  temp_tsl_ev_inv   = -1.0;

  err               = -1.0;
  err_half          = -1.0;
  err_int           = -1.0;
  ene_max           = -1.0;
  temp_inp          = -1.0;
  bin_no_real       = -1.0;
  bin_no_inv        = -1.0;

  calc_incoherent_inelastic_scat_flg =    0;
  temp_flg                           = -100;
  symmetric_flg                      = -100;
  stored_form_flg                    = -100;

  clr_obj.clear_vec_array2_int( sab_range_data);
  clr_obj.clear_vec_array2_int( sab_int_data);
  clr_obj.clear_vec_array2_real(sab_alpha_data);
  clr_obj.clear_vec_array2_real(sab_data);
  beta.clear();
  beta_range_data.clear();
  beta_int_data.clear();
  sig_b.clear();
  mass_inv.clear();
  temp_eff.clear();
  temp_eff_ev.clear();
  temp_eff_ev_inv.clear();
  sab_chk         = 0.0;
  beta_min        = 0.0;
  beta_max        = 0.0;
  alpha_min.clear();
  alpha_max.clear();

  ene_out_min = 0.0;
  ene_grid.clear();
  ene_grid_prod_distr.clear();
  scat_xs_tot.clear();
  clr_obj.clear_vec_array2_real8(second_ene_grid);
  clr_obj.clear_vec_array2_real8(scat_xs_tot_second_ene);
  clr_obj.clear_vec_array3_real8(scat_angle);
  clr_obj.clear_vec_array3_real8(scat_xs);
  clr_obj.clear_vec_array3_real8(integrated_scat_angle);
  clr_obj.clear_vec_array3_real8(integrated_scat_xs);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void IncoherentInelasticScatterCalculator::calc_incoherent_inelastic_scatter()
{
  if( opt_inelastic == no_calc )
  {
    return;
  }

  if( calc_incoherent_inelastic_scat_flg == 0 )
  {
    preparation_for_incoherent_inerastic_scatter();
  }

  calc_scat_xs();
}


//////////////////////////////////////////////////////////////////////////////////////////////////////

void IncoherentInelasticScatterCalculator::calc_scat_xs()
{
  //For debug
  //if( ene_grid_flg == use_nucl_ene_grid )
  //{
  //  cout << "The PENDF energy grid is used as the energy grid of" << endl;
  //  cout << "the incoherent inelastic scattring cross section." << endl;
  //  cout << endl;
  //}
  //else if( ene_grid_flg == linearize_ene_grid )
  //{
  //  cout << "Linearization of the incoherent inelastic scattring cross section." << endl;
  //  cout << endl;
  //}

  int use_nucl_data_grid = 0;
  int use_specified_grid = 1;
  int calc_grid_flg      = use_nucl_data_grid;

  vector<Real8> ene_grid_cal = ene_grid;
  //if( njoy_mode_flg == njoy_mode_on || opt_inelastic == free_gas_mode )
  if( opt_inelastic == free_gas_mode )
  {
    calc_grid_flg = use_specified_grid;
    ene_grid_cal.clear();

    Real ene_top = ene_max + min_ene_dif;
    int  ene_no  = static_cast<int>(ene_in_incoherent_inelastic.size());
    for(int i=0; i<ene_no; i++)
    {
      ene_grid_cal.push_back(ene_in_incoherent_inelastic[i]);

      if( ene_in_incoherent_inelastic[i] > ene_top )
      {
        break;
      }
    }
  }

  int i_max = static_cast<int>(ene_grid_cal.size());
  scat_xs_tot.resize(i_max);
  second_ene_grid.resize(i_max);
  scat_xs_tot_second_ene.resize(i_max);
  scat_angle.resize(i_max);
  scat_xs.resize(i_max);
  integrated_scat_angle.resize(i_max);
  integrated_scat_xs.resize(i_max);

  for(int i=0; i<i_max; i++)
  {
    calc_scat_xs_each_ene(ene_grid_cal[i], scat_xs_tot[i],
                          scat_xs_tot_second_ene[i], second_ene_grid[i],
                          scat_angle[i], scat_xs[i],
                          integrated_scat_angle[i], integrated_scat_xs[i]);
  }

  if( ene_grid_flg == linearize_ene_grid )
  {
    linearize_scat_xs(ene_grid_cal);
  }

  ene_grid_prod_distr = ene_grid_cal;

  if( calc_grid_flg == use_specified_grid )
  {
    calc_scat_xs_tot_by_lagrange_interpolation(ene_grid_cal, scat_xs_tot);
  }

  if( opt_inelastic == free_gas_mode )
  {
    modify_scat_xs_tot(ene_grid_cal, scat_xs_tot);
  }

  //Comparing elastic scattering xs from ENDF and incoherent inelastic scattering xs from TSL
  comp_scat_xs_tot();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void IncoherentInelasticScatterCalculator::linearize_scat_xs(vector<Real>& ene_grid_cal)
{
  Real                   mid_ene_grid, mid_scat_xs_tot;
  vector<Real8>          mid_scat_xs_tot_second_ene_vec, mid_second_ene_grid_vec;
  vector<vector<Real8> > mid_scat_angle_vec, mid_scat_xs_vec,
                         mid_integrated_scat_angle_vec, mid_integrated_scat_xs_vec;

  vector<Real8>                   new_ene_grid, new_scat_xs_tot;
  vector<vector<Real8> >          new_second_ene_grid, new_scat_xs_tot_second_ene;
  vector<vector<vector<Real8> > > new_scat_angle, new_scat_xs,
                                  new_integrated_scat_angle, new_integrated_scat_xs;

  vector<Real8>                   new_ene_grid_part, new_scat_xs_tot_part;
  vector<vector<Real8> >          new_second_ene_grid_part, new_scat_xs_tot_second_ene_part;
  vector<vector<vector<Real8> > > new_scat_angle_part, new_scat_xs_part,
                                  new_integrated_scat_angle_part, new_integrated_scat_xs_part;

  new_ene_grid.clear();
  new_scat_xs_tot.clear();
  clr_obj.clear_vec_array2_real8(new_second_ene_grid);
  clr_obj.clear_vec_array2_real8(new_scat_xs_tot_second_ene);
  clr_obj.clear_vec_array3_real8(new_scat_angle);
  clr_obj.clear_vec_array3_real8(new_scat_xs);
  clr_obj.clear_vec_array3_real8(new_integrated_scat_angle);
  clr_obj.clear_vec_array3_real8(new_integrated_scat_xs);

  new_ene_grid_part.clear();
  new_scat_xs_tot_part.clear();
  clr_obj.clear_vec_array2_real8(new_second_ene_grid_part);
  clr_obj.clear_vec_array2_real8(new_scat_xs_tot_second_ene_part);
  clr_obj.clear_vec_array3_real8(new_scat_angle_part);
  clr_obj.clear_vec_array3_real8(new_scat_xs_part);
  clr_obj.clear_vec_array3_real8(new_integrated_scat_angle_part);
  clr_obj.clear_vec_array3_real8(new_integrated_scat_xs_part);

  int int_chk, j;
  int i_max     = static_cast<int>(scat_xs_tot.size());
  if( i_max == 0 )
  {
    return;
  }

  new_ene_grid.push_back(ene_grid_cal[0]);
  new_scat_xs_tot.push_back(scat_xs_tot[0]);
  new_second_ene_grid.push_back(second_ene_grid[0]);
  new_scat_xs_tot_second_ene.push_back(scat_xs_tot_second_ene[0]);
  new_scat_angle.push_back(scat_angle[0]);
  new_scat_xs.push_back(scat_xs[0]);
  new_integrated_scat_angle.push_back(integrated_scat_angle[0]);
  new_integrated_scat_xs.push_back(integrated_scat_xs[0]);
  for(int i=1; i<i_max; i++)
  {
    new_ene_grid_part.push_back(ene_grid_cal[i-1]);
    new_scat_xs_tot_part.push_back(scat_xs_tot[i-1]);
    new_second_ene_grid_part.push_back(second_ene_grid[i-1]);
    new_scat_xs_tot_second_ene_part.push_back(scat_xs_tot_second_ene[i-1]);
    new_scat_angle_part.push_back(scat_angle[i-1]);
    new_scat_xs_part.push_back(scat_xs[i-1]);
    new_integrated_scat_angle_part.push_back(integrated_scat_angle[i-1]);
    new_integrated_scat_xs_part.push_back(integrated_scat_xs[i-1]);

    new_ene_grid_part.push_back(ene_grid_cal[i]);
    new_scat_xs_tot_part.push_back(scat_xs_tot[i]);
    new_second_ene_grid_part.push_back(second_ene_grid[i]);
    new_scat_xs_tot_second_ene_part.push_back(scat_xs_tot_second_ene[i]);
    new_scat_angle_part.push_back(scat_angle[i]);
    new_scat_xs_part.push_back(scat_xs[i]);
    new_integrated_scat_angle_part.push_back(integrated_scat_angle[i]);
    new_integrated_scat_xs_part.push_back(integrated_scat_xs[i]);

    j = 1;
    int_chk = comp_interpolation_value(j, new_ene_grid_part, new_scat_xs_tot_part,
                                          new_second_ene_grid_part, new_scat_xs_tot_second_ene_part,
                                          new_scat_angle_part, new_scat_xs_part,
                                          new_integrated_scat_angle_part, new_integrated_scat_xs_part,
                                          mid_ene_grid, mid_scat_xs_tot,
                                          mid_scat_xs_tot_second_ene_vec, mid_second_ene_grid_vec,
                                          mid_scat_angle_vec, mid_scat_xs_vec,
                                          mid_integrated_scat_angle_vec, mid_integrated_scat_xs_vec);

    while( int_chk < 0 || j < static_cast<int>(new_ene_grid_part.size()-1))
    {
      if( int_chk == 0 )
      {
        j++;
      }
      else
      {
        insert_middle_scat_xs_data(j, new_ene_grid_part, new_scat_xs_tot_part,
                                      new_second_ene_grid_part, new_scat_xs_tot_second_ene_part,
                                      new_scat_angle_part, new_scat_xs_part,
                                      new_integrated_scat_angle_part, new_integrated_scat_xs_part,
                                      mid_ene_grid, mid_scat_xs_tot,
                                      mid_scat_xs_tot_second_ene_vec, mid_second_ene_grid_vec,
                                      mid_scat_angle_vec, mid_scat_xs_vec,
                                      mid_integrated_scat_angle_vec, mid_integrated_scat_xs_vec);
      }
      int_chk = comp_interpolation_value(j, new_ene_grid_part, new_scat_xs_tot_part,
                                            new_second_ene_grid_part, new_scat_xs_tot_second_ene_part,
                                            new_scat_angle_part, new_scat_xs_part,
                                            new_integrated_scat_angle_part, new_integrated_scat_xs_part,
                                            mid_ene_grid, mid_scat_xs_tot,
                                            mid_scat_xs_tot_second_ene_vec, mid_second_ene_grid_vec,
                                            mid_scat_angle_vec, mid_scat_xs_vec,
                                            mid_integrated_scat_angle_vec, mid_integrated_scat_xs_vec);
    }
    add_ene_and_scat_xs_data(new_ene_grid, new_scat_xs_tot,
                             new_second_ene_grid, new_scat_xs_tot_second_ene,
                             new_scat_angle, new_scat_xs,
                             new_integrated_scat_angle, new_integrated_scat_xs,
                             new_ene_grid_part, new_scat_xs_tot_part,
                             new_second_ene_grid_part, new_scat_xs_tot_second_ene_part,
                             new_scat_angle_part, new_scat_xs_part,
                             new_integrated_scat_angle_part, new_integrated_scat_xs_part);
  }

  //Copy linearized data
  ene_grid_cal           = new_ene_grid;
  ene_grid               = new_ene_grid;
  scat_xs_tot            = new_scat_xs_tot;
  second_ene_grid        = new_second_ene_grid;
  scat_xs_tot_second_ene = new_scat_xs_tot_second_ene;
  scat_angle             = new_scat_angle;
  scat_xs                = new_scat_xs;
  integrated_scat_angle  = new_integrated_scat_angle;
  integrated_scat_xs     = new_integrated_scat_xs;

  new_ene_grid.clear();
  new_scat_xs_tot.clear();
  clr_obj.clear_vec_array2_real8(new_second_ene_grid);
  clr_obj.clear_vec_array2_real8(new_scat_xs_tot_second_ene);
  clr_obj.clear_vec_array3_real8(new_scat_angle);
  clr_obj.clear_vec_array3_real8(new_scat_xs);
  clr_obj.clear_vec_array3_real8(new_integrated_scat_angle);
  clr_obj.clear_vec_array3_real8(new_integrated_scat_xs);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

int IncoherentInelasticScatterCalculator::comp_interpolation_value
                (int& ele_no, vector<Real8>& new_ene_grid_part,
                              vector<Real8>& new_scat_xs_tot_part,
                              vector<vector<Real8> >& new_second_ene_grid_part,
                              vector<vector<Real8> >& new_scat_xs_tot_second_ene_part,
                              vector<vector<vector<Real8> > >& new_scat_angle_part,
                              vector<vector<vector<Real8> > >& new_scat_xs_part,
                              vector<vector<vector<Real8> > >& new_integrated_scat_angle_part,
                              vector<vector<vector<Real8> > >& new_integrated_scat_xs_part,
                              Real& mid_ene_grid, Real& mid_scat_xs_tot,
                              vector<Real8>& mid_scat_xs_tot_second_ene_vec,
                              vector<Real8>& mid_second_ene_grid_vec,
                              vector<vector<Real8> >& mid_scat_angle_vec,
                              vector<vector<Real8> >& mid_scat_xs_vec,
                              vector<vector<Real8> >& mid_integrated_scat_angle_vec,
                              vector<vector<Real8> >& mid_integrated_scat_xs_vec)
{
  Integer chk_flg = 0;

  mid_ene_grid = 0.5*(new_ene_grid_part[ele_no] + new_ene_grid_part[ele_no-1]);
  mid_ene_grid = digit_obj.get_truncation_value(mid_ene_grid);
  if( fabs(mid_ene_grid - new_ene_grid_part[ele_no])   < min_ene_dif * mid_ene_grid ||
      fabs(mid_ene_grid - new_ene_grid_part[ele_no-1]) < min_ene_dif * mid_ene_grid )
  {
    chk_flg = 0;
    return chk_flg;
  }
  else if( mid_ene_grid > ene_max )
  {
    chk_flg = 0;
    return chk_flg;
  }

  calc_scat_xs_each_ene(mid_ene_grid, mid_scat_xs_tot,
                        mid_scat_xs_tot_second_ene_vec, mid_second_ene_grid_vec,
                        mid_scat_angle_vec, mid_scat_xs_vec,
                        mid_integrated_scat_angle_vec, mid_integrated_scat_xs_vec);
  mid_scat_xs_tot = digit_obj.get_truncation_value(mid_scat_xs_tot);

  //Interpolation by linear-linear
  Real mid_scat_xs_tot_lin = 0.0;
  ti_obj.interpolation_1d(int_lin_lin, mid_ene_grid, mid_scat_xs_tot_lin,
                          new_ene_grid_part[ele_no-1], new_scat_xs_tot_part[ele_no-1],
                          new_ene_grid_part[ele_no],   new_scat_xs_tot_part[ele_no]);
  mid_scat_xs_tot_lin = digit_obj.get_truncation_value(mid_scat_xs_tot_lin);

  Real delta_scat_xs_tot = fabs(mid_scat_xs_tot - mid_scat_xs_tot_lin);
  //Real err_value         = fabs(err*mid_scat_xs_tot);
  Real err_value         = fabs(err*mid_scat_xs_tot*0.2);
  //Real err_value         = fabs(err*mid_scat_xs_tot*0.1);
  if( err_value < min_ene_dif )
  {
    err_value = min_ene_dif;
  }

  if( delta_scat_xs_tot > err_value )
  {
    chk_flg = -1;
  }

  return chk_flg;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void IncoherentInelasticScatterCalculator::insert_middle_scat_xs_data
                (int& ele_no, vector<Real8>& new_ene_grid_part,
                              vector<Real8>& new_scat_xs_tot_part,
                              vector<vector<Real8> >& new_second_ene_grid_part,
                              vector<vector<Real8> >& new_scat_xs_tot_second_ene_part,
                              vector<vector<vector<Real8> > >& new_scat_angle_part,
                              vector<vector<vector<Real8> > >& new_scat_xs_part,
                              vector<vector<vector<Real8> > >& new_integrated_scat_angle_part,
                              vector<vector<vector<Real8> > >& new_integrated_scat_xs_part,
                              Real& mid_ene_grid, Real& mid_scat_xs_tot,
                              vector<Real8>& mid_scat_xs_tot_second_ene_vec,
                              vector<Real8>& mid_second_ene_grid_vec,
                              vector<vector<Real8> >& mid_scat_angle_vec,
                              vector<vector<Real8> >& mid_scat_xs_vec,
                              vector<vector<Real8> >& mid_integrated_scat_angle_vec,
                              vector<vector<Real8> >& mid_integrated_scat_xs_vec)
{
  int i_max = static_cast<int>(new_ene_grid_part.size());

  if( ele_no >= i_max )
  {
    new_ene_grid_part.push_back(mid_ene_grid);
    new_scat_xs_tot_part.push_back(mid_scat_xs_tot);
    new_scat_xs_tot_second_ene_part.push_back(mid_scat_xs_tot_second_ene_vec);
    new_second_ene_grid_part.push_back(mid_second_ene_grid_vec);
    new_scat_angle_part.push_back(mid_scat_angle_vec);
    new_scat_xs_part.push_back(mid_scat_xs_vec);
    new_integrated_scat_angle_part.push_back(mid_integrated_scat_angle_vec);
    new_integrated_scat_xs_part.push_back(mid_integrated_scat_xs_vec);
  }
  else if( ele_no >= 0 )
  {
    new_ene_grid_part.insert(new_ene_grid_part.begin()                             + ele_no, mid_ene_grid);
    new_scat_xs_tot_part.insert(new_scat_xs_tot_part.begin()                       + ele_no, mid_scat_xs_tot);
    new_scat_xs_tot_second_ene_part.insert(new_scat_xs_tot_second_ene_part.begin() + ele_no, mid_scat_xs_tot_second_ene_vec);
    new_second_ene_grid_part.insert(new_second_ene_grid_part.begin()               + ele_no, mid_second_ene_grid_vec);
    new_scat_angle_part.insert(new_scat_angle_part.begin()                         + ele_no, mid_scat_angle_vec);
    new_scat_xs_part.insert(new_scat_xs_part.begin()                               + ele_no, mid_scat_xs_vec);
    new_integrated_scat_angle_part.insert(new_integrated_scat_angle_part.begin()   + ele_no, mid_integrated_scat_angle_vec);
    new_integrated_scat_xs_part.insert(new_integrated_scat_xs_part.begin()         + ele_no, mid_integrated_scat_xs_vec);
  }
  else
  {
    string class_name = "IncoherentInelasticScatterCalculator";
    string func_name  = "insert_middle_scat_xs_data";
    ostringstream oss01;
    oss01 << ele_no;
    string str_data01 = "The position data : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("The position data is less than 0.");
    err_com.push_back("This data is not added.");
    err_obj.output_caution(class_name, func_name, err_com);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void IncoherentInelasticScatterCalculator::add_ene_and_scat_xs_data
                (vector<Real8>& new_ene_grid, vector<Real8>& new_scat_xs_tot,
                 vector<vector<Real8> >& new_second_ene_grid,
                 vector<vector<Real8> >& new_scat_xs_tot_second_ene,
                 vector<vector<vector<Real8> > >& new_scat_angle,
                 vector<vector<vector<Real8> > >& new_scat_xs,
                 vector<vector<vector<Real8> > >& new_integrated_scat_angle,
                 vector<vector<vector<Real8> > >& new_integrated_scat_xs,
                 vector<Real8>& new_ene_grid_part, vector<Real8>& new_scat_xs_tot_part,
                 vector<vector<Real8> >& new_second_ene_grid_part,
                 vector<vector<Real8> >& new_scat_xs_tot_second_ene_part,
                 vector<vector<vector<Real8> > >& new_scat_angle_part,
                 vector<vector<vector<Real8> > >& new_scat_xs_part,
                 vector<vector<vector<Real8> > >& new_integrated_scat_angle_part,
                 vector<vector<vector<Real8> > >& new_integrated_scat_xs_part)
{
  int k_max = static_cast<int>(new_ene_grid_part.size());
  for(int k=1; k<k_max; k++)
  {
    new_ene_grid.push_back(new_ene_grid_part[k]);
    new_scat_xs_tot.push_back(new_scat_xs_tot_part[k]);
    new_second_ene_grid.push_back(new_second_ene_grid_part[k]);
    new_scat_xs_tot_second_ene.push_back(new_scat_xs_tot_second_ene_part[k]);
    new_scat_angle.push_back(new_scat_angle_part[k]);
    new_scat_xs.push_back(new_scat_xs_part[k]);
    new_integrated_scat_angle.push_back(new_integrated_scat_angle_part[k]);
    new_integrated_scat_xs.push_back(new_integrated_scat_xs_part[k]);
  }

  new_ene_grid_part.clear();
  new_scat_xs_tot_part.clear();
  clr_obj.clear_vec_array2_real8(new_second_ene_grid_part);
  clr_obj.clear_vec_array2_real8(new_scat_xs_tot_second_ene_part);
  clr_obj.clear_vec_array3_real8(new_scat_angle_part);
  clr_obj.clear_vec_array3_real8(new_scat_xs_part);
  clr_obj.clear_vec_array3_real8(new_integrated_scat_angle_part);
  clr_obj.clear_vec_array3_real8(new_integrated_scat_xs_part);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void IncoherentInelasticScatterCalculator::calc_scat_xs_each_ene
                                             ( Real& ene_val, Real8& scat_xs_tot_val,
                                               vector<Real8>& scat_xs_tot_second_ene_vec,
                                               vector<Real8>& second_ene_grid_vec,
                                               vector<vector<Real8> >& scat_angle_vec,
                                               vector<vector<Real8> >& scat_xs_vec,
                                               vector<vector<Real8> >& integrated_scat_angle_vec,
                                               vector<vector<Real8> >& integrated_scat_xs_vec)
{
  if( ene_val > ene_max + min_ene_dif )
  {
    if( lagrange_interpolation_flg == no_interpolation_mode || opt_inelastic == free_gas_mode )
    {
      init_scat_data( ene_val, scat_xs_tot_val, scat_xs_tot_second_ene_vec, second_ene_grid_vec,
                      scat_angle_vec, scat_xs_vec, integrated_scat_angle_vec, integrated_scat_xs_vec);
      return;
    }
  }

  linearize_incoherent_inelastic_scatter_e_out
    ( ene_val, second_ene_grid_vec, scat_xs_tot_second_ene_vec, scat_angle_vec, scat_xs_vec,
      integrated_scat_angle_vec, integrated_scat_xs_vec );
  calc_scat_xs_tot(scat_xs_tot_val, scat_xs_tot_second_ene_vec, second_ene_grid_vec);

  //To save memory, scat_xs, scat_angle and integrated_scat_angle is cleared
  clr_obj.clear_vec_array2_real8(scat_xs_vec);
  clr_obj.clear_vec_array2_real8(scat_angle_vec);
  clr_obj.clear_vec_array2_real8(integrated_scat_angle_vec);

  //If fabs(a_val) < 1.0E-30, a_val considerd as 0.0
  adjust_xs_and_mu( scat_angle_vec, scat_xs_vec, integrated_scat_angle_vec, integrated_scat_xs_vec,
                    scat_xs_tot_val, scat_xs_tot_second_ene_vec );

  //modify xs_tot_ene_out and xs_data_int to meet the PENDF data format
  modify_second_xs_data(ene_val, scat_xs_tot_val, scat_xs_tot_second_ene_vec, integrated_scat_xs_vec);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void IncoherentInelasticScatterCalculator::init_scat_data
                                 ( Real8& ene_in_data, Real8& xs_tot_data, vector<Real8>& xs_tot_ene_out,
                                   vector<Real8>& ene_out_data,
                                   vector<vector<Real8> >& mu_data,     vector<vector<Real8> >& xs_data,
                                   vector<vector<Real8> >& mu_data_int, vector<vector<Real8> >& xs_data_int )
{
  xs_tot_data = 0.0;
  xs_tot_ene_out.clear();
  ene_out_data.clear();
  clr_obj.clear_vec_array2_real8(mu_data);
  clr_obj.clear_vec_array2_real8(xs_data);
  clr_obj.clear_vec_array2_real8(mu_data_int);
  clr_obj.clear_vec_array2_real8(xs_data_int);

  xs_tot_ene_out.push_back(0.0);
  ene_out_data.push_back(ene_in_data);
  mu_data.resize(1);
  xs_data.resize(1);
  mu_data_int.resize(1);
  xs_data_int.resize(1);

  mu_data[0].resize(bin_no_int);
  xs_data[0].resize(bin_no_int);
  mu_data_int[0].resize(bin_no_int);
  xs_data_int[0].resize(bin_no_int);
  for(int i=0; i<bin_no_int; i++)
  {
    mu_data[0][i]     = 0.0;
    xs_data[0][i]     = 0.0;
    mu_data_int[0][i] = 0.0;
    xs_data_int[0][i] = 0.0;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void IncoherentInelasticScatterCalculator::calc_scat_xs_tot( Real8& xs_tot_data, vector<Real8>& xs_tot_ene_out,
                                                             vector<Real8>& ene_out_data )
{
  xs_tot_data = 0.0;
  int i_max = static_cast<int>(ene_out_data.size());
  if( i_max == 0 )
  {
    return;
  }

  if( i_max == 1 )
  {
    xs_tot_data = xs_tot_ene_out[0];
    return;
  }

  Real8 ene_out_pre, ene_out_cur, scat_xs_pre, scat_xs_cur;
  ene_out_pre = 0.0;
  scat_xs_pre = 0.0;
  for(int i=0; i<i_max; i++)
  {
    ene_out_cur = ene_out_data[i];
    scat_xs_cur = xs_tot_ene_out[i];

    xs_tot_data += fabs(0.5*(scat_xs_cur + scat_xs_pre)*(ene_out_cur - ene_out_pre));

    ene_out_pre = ene_out_cur;
    scat_xs_pre = scat_xs_cur;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void IncoherentInelasticScatterCalculator::calc_scat_xs_mu_tot(Real8& xs_tot_data,
                                                               vector<Real8>& mu_data, vector<Real8>& xs_data)
{
  xs_tot_data = 0.0;
  int i_max = static_cast<int>(mu_data.size());
  if( i_max == 0 )
  {
    return;
  }

  Real8 mu_pre, mu_cur, xs_pre, xs_cur;
  mu_pre = mu_data[0];
  xs_pre = xs_data[0];
  if( i_max == 1 )
  {
    xs_tot_data = xs_pre;
    return;
  }

  for(int i=1; i<i_max; i++)
  {
    mu_cur = mu_data[i];
    xs_cur = xs_data[i];

    //xs_tot_data += fabs(0.5*(xs_cur + xs_pre)*(mu_cur - mu_pre));
    xs_tot_data += 0.5*(xs_cur + xs_pre)*(mu_cur - mu_pre);

    mu_pre = mu_cur;
    xs_pre = xs_cur;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void IncoherentInelasticScatterCalculator::adjust_xs_and_mu( vector<vector<Real8> >& mu_data,
                                                             vector<vector<Real8> >& xs_data,
                                                             vector<vector<Real8> >& mu_data_int,
                                                             vector<vector<Real8> >& xs_data_int,
                                                             Real8& xs_tot_data,
                                                             vector<Real8>& xs_tot_ene_out )
{
  digit_obj.adjust_data( mu_data );
  digit_obj.adjust_data( xs_data );
  digit_obj.adjust_data( mu_data_int );
  digit_obj.adjust_data( xs_data_int );
  digit_obj.adjust_data( xs_tot_data );
  digit_obj.adjust_data( xs_tot_ene_out );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void IncoherentInelasticScatterCalculator::modify_second_xs_data( Real8& ene_in_data, Real8& xs_tot_data,
                                                                  vector<Real8>& xs_tot_ene_out,
                                                                  vector<vector<Real8> >& xs_data_int )
{
  int i_max = static_cast<int>(xs_tot_ene_out.size());
  if( fabs(xs_tot_data) < min_sig_val )
  {
    ostringstream oss01, oss02;
    oss01 << ene_in_data;
    oss02 << xs_tot_data;
    string str_data01 = "Incoherent inelastic scatter cross section is zero.";
    string str_data02 = "Please check input data or nuclear data.";
    string str_data03 = "  Energy grid   : " + oss01.str();
    string str_data04 = "  Cross section : " + oss02.str();
    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    string class_name = "IncoherentInelasticScatterCalculator";
    string func_name  = "modify_second_xs_data(Real8& ene_in_data, Real8& xs_tot_data, vector<Real8>& xs_tot_ene_out, vector<vector<Real8> >& xs_data_int)";
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  Real8 xs_tot_inv = 1.0/xs_tot_data;
  for(int i=0; i<i_max; i++)
  {
    if( fabs(xs_tot_ene_out[i]) > min_sig_val )
    {
      Real8 xs_data_int_coef = bin_no_real/xs_tot_ene_out[i];
      for(int j=0; j<bin_no_int; j++)
      {
        xs_data_int[i][j] *= xs_data_int_coef;
      }
      xs_tot_ene_out[i] *= xs_tot_inv;
    }
    else
    {
      for(int j=0; j<bin_no_int; j++)
      {
        xs_data_int[i][j] = 0.0;
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void IncoherentInelasticScatterCalculator::modify_scat_xs_tot( vector<Real8>& ene_in_data,
                                                               vector<Real8>& xs_tot_data )
{
  CrossSectionDataContainer xs_data_obj
                              = nucl_data_obj.get_nucl_reaction_data_obj().get_xs_data_obj(xs_type_elastic);
  vector<Real> ene_grid_nucl  = xs_data_obj.get_xs_ene_data();
  vector<Real> xs_data_nucl   = xs_data_obj.get_xs_data();

  int ele_no  = 1;
  int ele_max = static_cast<int>(ene_grid_nucl.size());
  if( ele_max < 2 )
  {
    return;
  }

  int i_max = static_cast<int>(ene_in_data.size());
  xs_tot_data.clear();
  xs_tot_data.resize(i_max);

  Real ene_top = ene_max + min_ene_dif;
  Real ene_pre = ene_grid_nucl[ele_no-1];
  Real ene_cur = ene_grid_nucl[ele_no];
  Real xs_pre  = xs_data_nucl[ele_no-1];
  Real xs_cur  = xs_data_nucl[ele_no];
  for(int i=0; i<i_max; i++)
  {
    if( ene_in_data[i] > ene_top )
    {
      continue;
    }

    while( ene_in_data[i] > ene_cur - min_ene_dif )
    {
      ele_no++;
      if( ele_no >= ele_max )
      {
        break;
      }
      ene_pre = ene_cur;
      ene_cur = ene_grid_nucl[ele_no];
      xs_pre  = xs_cur;
      xs_cur  = xs_data_nucl[ele_no];
    }
    ti_obj.interpolation_1d(int_lin_lin, ene_in_data[i], xs_tot_data[i], ene_pre, xs_pre, ene_cur, xs_cur);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void IncoherentInelasticScatterCalculator::calc_scat_xs_tot_by_lagrange_interpolation
                                             ( vector<Real8>& ene_in_data, vector<Real8>& xs_tot_data )
{
  vector<Real8> ene_grid_ori, xs_tot_ori;
  ene_grid_ori = ene_grid;

  int     i_max   = static_cast<int>(ene_grid_ori.size());
  Real    ene_top = ene_max + min_ene_dif;
  Integer order   = 5;

  xs_tot_ori.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    if( ene_grid_ori[i] > ene_top )
    {
      if( lagrange_interpolation_flg == no_interpolation_mode || opt_inelastic == free_gas_mode )
      {
        xs_tot_ori[i] = 0.0;
        continue;
      }
    }

    xs_tot_ori[i] = math_obj.lagrange_interpolation(ene_grid_ori[i], order, ene_in_data, xs_tot_data);
  }

  ene_in_data = ene_grid;
  xs_tot_data = xs_tot_ori;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void IncoherentInelasticScatterCalculator::linearize_incoherent_inelastic_scatter_e_out
                                      (Real8& ene_in_data, vector<Real8>& ene_out_data,
                                       vector<Real8>& xs_data_tot,
                                       vector<vector<Real8> >& mu_data, vector<vector<Real8> >& xs_data,
                                       vector<vector<Real8> >& mu_data_int, vector<vector<Real8> >& xs_data_int)
{
  xs_data_tot.clear();
  clr_obj.clear_vec_array2_real8(mu_data);
  clr_obj.clear_vec_array2_real8(xs_data);
  clr_obj.clear_vec_array2_real8(mu_data_int);
  clr_obj.clear_vec_array2_real8(xs_data_int);

  set_ene_out_grid(ene_in_data, ene_out_data);

  int i_max = static_cast<int>(ene_out_data.size());
  xs_data_tot.resize(i_max);
  mu_data.resize(i_max);
  xs_data.resize(i_max);
  mu_data_int.resize(i_max);
  xs_data_int.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    linearize_incoherent_inelastic_scatter_mu(ene_in_data, ene_out_data[i], xs_data_tot[i],
                                              mu_data[i], xs_data[i],
                                              mu_data_int[i], xs_data_int[i]);
  }

  int                    j;
  Integer                int_chk;
  Real8                  mid_ene_out, mid_xs_tot;
  vector<Real8>          mid_mu, mid_xs, mid_mu_int, mid_xs_int;
  vector<Real8>          new_ene_out, new_ene_out_part, new_xs_tot, new_xs_tot_part;
  vector<vector<Real8> > new_mu, new_mu_part, new_xs, new_xs_part,
                         new_mu_int, new_mu_int_part, new_xs_int, new_xs_int_part;
  new_ene_out.clear();
  new_ene_out_part.clear();
  new_xs_tot.clear();
  new_xs_tot_part.clear();
  clr_obj.clear_vec_array2_real8(new_mu);
  clr_obj.clear_vec_array2_real8(new_mu_part);
  clr_obj.clear_vec_array2_real8(new_xs);
  clr_obj.clear_vec_array2_real8(new_xs_part);
  clr_obj.clear_vec_array2_real8(new_mu_int);
  clr_obj.clear_vec_array2_real8(new_mu_int_part);
  clr_obj.clear_vec_array2_real8(new_xs_int);
  clr_obj.clear_vec_array2_real8(new_xs_int_part);

  new_ene_out.push_back(ene_out_data[0]);
  new_xs_tot.push_back(xs_data_tot[0]);
  new_mu.push_back(mu_data[0]);
  new_xs.push_back(xs_data[0]);
  new_mu_int.push_back(mu_data_int[0]);
  new_xs_int.push_back(xs_data_int[0]);

  for(int i=1; i<i_max; i++)
  {
    new_ene_out_part.push_back(ene_out_data[i-1]);
    new_xs_tot_part.push_back(xs_data_tot[i-1]);
    new_mu_part.push_back(mu_data[i-1]);
    new_xs_part.push_back(xs_data[i-1]);
    new_mu_int_part.push_back(mu_data_int[i-1]);
    new_xs_int_part.push_back(xs_data_int[i-1]);

    new_ene_out_part.push_back(ene_out_data[i]);
    new_xs_tot_part.push_back(xs_data_tot[i]);
    new_mu_part.push_back(mu_data[i]);
    new_xs_part.push_back(xs_data[i]);
    new_mu_int_part.push_back(mu_data_int[i]);
    new_xs_int_part.push_back(xs_data_int[i]);

    j = 1;
    mid_ene_out = 0.5*(new_ene_out_part[j] + new_ene_out_part[j-1]);
    linearize_incoherent_inelastic_scatter_mu(ene_in_data, mid_ene_out, mid_xs_tot, 
                                              mid_mu, mid_xs, mid_mu_int, mid_xs_int);
    int_chk = check_ene_out_grid( new_ene_out_part[j-1], new_ene_out_part[j],
                                  new_xs_tot_part[j-1],  new_xs_tot_part[j], mid_xs_tot,
                                  new_xs_int_part[j-1],  new_xs_int_part[j], mid_xs_int);

    while( int_chk < 0 || j < static_cast<int>(new_mu_part.size()-1) )
    {
      if( int_chk >= 0 )
      {
        j++;
      }
      else
      {
        //Add middle mu grid and cross section
        insert_middle_ene_out_grid(j, new_ene_out_part, 
                                   new_xs_tot_part, new_mu_part, new_xs_part, new_mu_int_part, new_xs_int_part, 
                                   mid_ene_out, mid_xs_tot, mid_mu, mid_xs, mid_mu_int, mid_xs_int);
      }
      mid_ene_out = 0.5*(new_ene_out_part[j] + new_ene_out_part[j-1]);
      linearize_incoherent_inelastic_scatter_mu(ene_in_data, mid_ene_out, mid_xs_tot,
                                                mid_mu, mid_xs, mid_mu_int, mid_xs_int);
      int_chk = check_ene_out_grid( new_ene_out_part[j-1], new_ene_out_part[j],
                                    new_xs_tot_part[j-1],  new_xs_tot_part[j], mid_xs_tot,
                                    new_xs_int_part[j-1],  new_xs_int_part[j], mid_xs_int);
    }
    add_xs_at_each_ene_out_grid(new_ene_out,      new_xs_tot,
                                new_mu,      new_xs,      new_mu_int,      new_xs_int, 
                                new_ene_out_part, new_xs_tot_part,
                                new_mu_part, new_xs_part, new_mu_int_part, new_xs_int_part);
  }

  //Clear data
  ene_out_data.clear();
  xs_data_tot.clear();
  clr_obj.clear_vec_array2_real8(mu_data);
  clr_obj.clear_vec_array2_real8(xs_data);
  clr_obj.clear_vec_array2_real8(mu_data_int);
  clr_obj.clear_vec_array2_real8(xs_data_int);
  
  ene_out_data = new_ene_out;
  xs_data_tot  = new_xs_tot;
  mu_data      = new_mu;
  xs_data      = new_xs;
  mu_data_int  = new_mu_int;
  xs_data_int  = new_xs_int;
  new_ene_out.clear();
  new_xs_tot.clear();
  clr_obj.clear_vec_array2_real8(new_mu);
  clr_obj.clear_vec_array2_real8(new_xs);
  clr_obj.clear_vec_array2_real8(new_mu_int);
  clr_obj.clear_vec_array2_real8(new_xs_int);

  //Remove data when ene_in_data is identical to ene_out_data
  remove_unnecessary_ene_out_grid(ene_in_data, ene_out_data, xs_data_tot,
                                  mu_data, xs_data, mu_data_int, xs_data_int);

  //For debug
  //cout << "linearize_incoherent_inelastic_scatter_e_out" << endl;
  //cout << endl;
  //output_ene_out_grid(ene_in_data, ene_out_data);
  //cout << endl;
  //cout << "======================================================================" << endl;
  //cout << endl;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void IncoherentInelasticScatterCalculator::set_ene_out_grid(Real8& ene_in_data, vector<Real8>& ene_out_data)
{
  int   i_max    = static_cast<int>(beta.size());
  Real8 ene_in_m = digit_obj.get_adjusted_value(ene_in_data, sig_fig-2, -1.0); 
  Real8 ene_in_p = digit_obj.get_adjusted_value(ene_in_data, sig_fig-2, +1.0); 

  vector<Real8> ene_out_mod;
  ene_out_mod.push_back(0.0);
  ene_out_mod.push_back(ene_max);
  ene_out_mod.push_back(ene_out_min);
  ene_out_mod.push_back(ene_in_m);
  ene_out_mod.push_back(ene_in_p);

  if( temp_flg == const_temp_mode && opt_inelastic != free_gas_mode )
  {
    for(int i=0; i<i_max; i++)
    {
      ene_out_mod.push_back(ene_in_data + beta[i]*conv_th_ene);
      ene_out_mod.push_back(ene_in_data - beta[i]*conv_th_ene);
    }
  }
  else
  {
    for(int i=0; i<i_max; i++)
    {
      ene_out_mod.push_back(ene_in_data + beta[i]*temp_tsl_ev);
      ene_out_mod.push_back(ene_in_data - beta[i]*temp_tsl_ev);
    }
  }

  sort(ene_out_mod.begin(), ene_out_mod.end());

  i_max = static_cast<int>(ene_out_mod.size());
  Real8 ene_out_sta = ene_out_min;
  if( ene_out_sta < ene_in_p && ene_out_sta > ene_in_m)
  {
    ene_out_sta = ene_in_m;
  }

  Real8 ene_out_pre = ene_out_sta;
  ene_out_data.clear();
  ene_out_data.push_back(ene_out_pre);
  for(int i=0; i<i_max; i++)
  {
    if( ene_out_mod[i] > ene_out_sta )
    {
      if( ene_out_mod[i] - ene_out_pre > fabs(min_ene_dif*ene_out_pre) )
      {
        ene_out_pre = ene_out_mod[i];
        ene_out_data.push_back(ene_out_pre);
      }
    }
  }

  //For debug
  //cout << "set_ene_out_grid" << endl;
  //cout << endl;
  //output_ene_out_grid(ene_in_data, ene_out_data);
  //cout << endl;
  //cout << "======================================================================" << endl;
  //cout << endl;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void IncoherentInelasticScatterCalculator::output_ene_out_grid(Real8 ene_in_data, vector<Real8> ene_out_data)
{
  int i_max = static_cast<int>(ene_out_data.size());

  Real8 e_min = ene_out_data[0];
  Real8 e_max = ene_out_data[i_max-1];

  Real8 ene_dis_rela_min = 1.0E+10;
  Real8 ene_dis_rela_max = 0.0;
  Real8 ene_dis_abs_min  = 1.0E+10;
  Real8 ene_dis_abs_max  = 0.0;

  for(int i=1; i<i_max; i++)
  {
    Real8 diff_abs  = ene_out_data[i] - ene_out_data[i-1];
    Real8 diff_rela = diff_abs / (ene_out_data[i]);

    if( diff_rela > ene_dis_rela_max )
    {
      ene_dis_rela_max = diff_rela;
    }
    if( diff_rela < ene_dis_rela_min )
    {
      ene_dis_rela_min = diff_rela;
    }

    if( diff_abs > ene_dis_abs_max )
    {
      ene_dis_abs_max = diff_abs;
    }
    if( diff_abs < ene_dis_abs_min )
    {
      ene_dis_abs_min = diff_abs;
    }
  }

  cout.precision(8);
  cout.setf(ios::showpoint);
  cout.setf(ios::scientific);
  cout << "Ein " << ene_in_data << " : Eout-min " << e_min << " : Eout-max " << e_max
       << " : Eout-dis-min_abs "  << ene_dis_abs_min  << " : Eout-dis-max_abs "  << ene_dis_abs_max
       << " : Eout-dis-min_rela " << ene_dis_rela_min << " : Eout-dis-max_rela " << ene_dis_rela_max
       << " : Eout-no " << i_max;

  //cout << " : ";
  //for(int i=0; i<i_max; i++)
  //{
  //  cout << ene_out_data[i] << "  ";
  //}
  cout << endl;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void IncoherentInelasticScatterCalculator::remove_unnecessary_ene_out_grid
                                      (Real& ene_in_data,
                                       vector<Real8>& ene_out_data,         vector<Real8>& xs_data_tot,
                                       vector<vector<Real8> >& mu_data,     vector<vector<Real8> >& xs_data,
                                       vector<vector<Real8> >& mu_data_int, vector<vector<Real8> >& xs_data_int)
{
  vector<Real8>          ori_ene_out, ori_xs_tot;
  vector<vector<Real8> > ori_mu, ori_xs, ori_mu_int, ori_xs_int;

  ori_ene_out = ene_out_data;
  ori_xs_tot  = xs_data_tot;
  ori_mu      = mu_data;
  ori_xs      = xs_data;
  ori_mu_int  = mu_data_int;
  ori_xs_int  = xs_data_int;

  int i_max = static_cast<int>(ori_ene_out.size());
  vector<int>  ele_no_vec;
  ele_no_vec.clear();

  Real8 ene_dif = fabs(ene_in_data*min_ene_dif);
  for(int i=0; i<i_max; i++)
  {
    if( ori_xs_tot[i] < min_value )
    {
      int ele_m_flg = 0;
      int ele_p_flg = 0;
      if( i > 0 )
      {
        if( ori_xs_tot[i-1] < min_value )
        {
          ele_m_flg = 1;
        }
      }
      else
      {
        ele_m_flg = 1;
      }

      if( i < i_max - 1 )
      {
        if( ori_xs_tot[i+1] < min_value )
        {
          ele_p_flg = 1;
        }
      }
      else
      {
        ele_p_flg = 1;
      }

      if( ele_p_flg == 1 && ele_m_flg == 1 )
      {
        ele_no_vec.push_back(i);
        continue;
      }
    }

    if( fabs(ene_in_data - ori_ene_out[i]) < ene_dif )
    {
      ele_no_vec.push_back(i);
    }
  }
  ele_no_vec.push_back(i_max+1);

  int ele_no = static_cast<int>(ele_no_vec.size()) - 1;
  if( ele_no > 0 )
  {
    ene_out_data.resize(i_max-ele_no);
    xs_data_tot.resize(i_max-ele_no);
    mu_data.resize(i_max-ele_no);
    xs_data.resize(i_max-ele_no);
    mu_data_int.resize(i_max-ele_no);
    xs_data_int.resize(i_max-ele_no);

    int j = 0;
    for(int i=0; i<i_max; i++)
    {
      if( i == ele_no_vec[j] )
      {
        j++;
        continue;
      }
      ene_out_data[i-j] = ori_ene_out[i];
      xs_data_tot[i-j]  = ori_xs_tot[i];
      mu_data[i-j]      = ori_mu[i];
      xs_data[i-j]      = ori_xs[i];
      mu_data_int[i-j]  = ori_mu_int[i];
      xs_data_int[i-j]  = ori_xs_int[i];
    }
  }

  ori_ene_out.clear();
  ori_xs_tot.clear();
  clr_obj.clear_vec_array2_real8(ori_mu);
  clr_obj.clear_vec_array2_real8(ori_xs);
  clr_obj.clear_vec_array2_real8(ori_mu_int);
  clr_obj.clear_vec_array2_real8(ori_xs_int);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Integer IncoherentInelasticScatterCalculator::check_ene_out_grid
                                                ( Real8& ene_out_pre, Real8& ene_out_cur,
                                                  Real8& xs_tot_pre,  Real8& xs_tot_cur,  Real8& mid_xs_tot,
                                                  vector<Real8>& xs_int_pre, vector<Real8>& xs_int_cur,
                                                  vector<Real8>& mid_xs_int )
{
  Integer chk_flg = 1;

  if( fabs(ene_out_cur - ene_out_pre) < min_ene_dif )
  {
    chk_flg = 100;
    return chk_flg;
  }

  if( ( fabs(ene_out_cur - ene_out_pre) < 1.0E-6 ) &&
      ( 0.5 * fabs(ene_out_cur - ene_out_pre) * (xs_tot_cur + xs_tot_pre) < 1.0E-6 ) )
  {
    chk_flg = 10;
    return chk_flg;
  }

  Real8 err_value  = err;
  Real8 xs_tot_ave = 0.5*(xs_tot_cur + xs_tot_pre);
  if( fabs(xs_tot_ave) >= min_inelastic_xs_val )
  {
    if( fabs(mid_xs_tot - xs_tot_ave) >= err_value*(fabs(xs_tot_ave) + 1.0E-3) )
    {
      chk_flg = -100;
      return chk_flg;
    }
    //Following check is used for using the Legendre expansion
//    if( fabs(mid_xs_tot - xs_tot_ave ) >= fabs(2.0*err*xs_tot_ave)+1.0E-5 )
//    {
//      chk_flg = -200;
//      return chk_flg;
//    }
  }
  else
  {
    if( fabs(mid_xs_tot - xs_tot_ave) >= err_value )
    {
      chk_flg = -400;
      return chk_flg;
    }
  }

  return chk_flg;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void IncoherentInelasticScatterCalculator::insert_middle_ene_out_grid
                ( int& ele_no, vector<Real8>& ene_out_data,         vector<Real8>& xs_data_tot,
                               vector<vector<Real8> >& mu_data,     vector<vector<Real8> >& xs_data,
                               vector<vector<Real8> >& mu_data_int, vector<vector<Real8> >& xs_data_int,
                               Real8&                  mid_ene,     Real8&                  mid_xs_tot,
                               vector<Real8>&          mid_mu,      vector<Real8>&          mid_xs,
                               vector<Real8>&          mid_mu_int,  vector<Real8>&          mid_xs_int )
{
  ta_obj.add_grid_data_at_given_position(ene_out_data, mid_ene,    ele_no);

  ta_obj.add_grid_data_at_given_position(xs_data_tot,  mid_xs_tot, ele_no);
  ta_obj.add_grid_data_at_given_position(xs_data,      mid_xs,     ele_no);
  ta_obj.add_grid_data_at_given_position(xs_data_int,  mid_xs_int, ele_no);

  ta_obj.add_grid_data_at_given_position(mu_data,      mid_mu,     ele_no);
  ta_obj.add_grid_data_at_given_position(mu_data_int,  mid_mu_int, ele_no);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void IncoherentInelasticScatterCalculator::add_xs_at_each_ene_out_grid
                ( vector<Real8>&          new_ene_out,      vector<Real8>&          new_xs_tot,
                  vector<vector<Real8> >& new_mu,           vector<vector<Real8> >& new_xs,
                  vector<vector<Real8> >& new_mu_int,       vector<vector<Real8> >& new_xs_int,
                  vector<Real8>&          new_ene_out_part, vector<Real8>&          new_xs_tot_part,
                  vector<vector<Real8> >& new_mu_part,      vector<vector<Real8> >& new_xs_part,
                  vector<vector<Real8> >& new_mu_int_part,  vector<vector<Real8> >& new_xs_int_part )
{
  int i_max = static_cast<int>(new_ene_out_part.size());
  for(int i=1; i<i_max; i++)
  {
    new_ene_out.push_back(new_ene_out_part[i]);
    new_xs_tot.push_back(new_xs_tot_part[i]);
    new_mu.push_back(new_mu_part[i]);
    new_xs.push_back(new_xs_part[i]);
    new_mu_int.push_back(new_mu_int_part[i]);
    new_xs_int.push_back(new_xs_int_part[i]);
  }
  new_ene_out_part.clear();
  new_xs_tot_part.clear();
  clr_obj.clear_vec_array2_real8(new_mu_part);
  clr_obj.clear_vec_array2_real8(new_xs_part);
  clr_obj.clear_vec_array2_real8(new_mu_int_part);
  clr_obj.clear_vec_array2_real8(new_xs_int_part);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void IncoherentInelasticScatterCalculator::linearize_incoherent_inelastic_scatter_mu
                                             ( Real8& ene_in_data, Real8& ene_out_data, Real8& xs_data_tot,
                                               vector<Real8>& mu_data, vector<Real8>& xs_data,
                                               vector<Real8>& mu_data_int, vector<Real8>& xs_data_int )
{
  mu_data.clear();
  xs_data.clear();
  mu_data_int.clear();
  xs_data_int.clear();

  //If ene_in_data is identical to ene_out_data, this calculation was skipped.
  //(When ene_in_data is identical to ene_out_data, inelastic scatter cross section is zero.)
  if( fabs(ene_in_data - ene_out_data) < fabs(min_ene_dif * ene_in_data) )
  {
    mu_data.push_back(0.0);
    xs_data.push_back(0.0);
    mu_data_int.resize(bin_no_int);
    xs_data_int.resize(bin_no_int);
    for(int i=0; i<bin_no_int; i++)
    {
      mu_data_int[i] = -1.0 + 2.0*bin_no_inv*static_cast<Real8>(i);
      xs_data_int[i] = 0.0;
    }
    return;
  }

  int i_max = 29;
  mu_data.resize(i_max);
  mu_data[ 0] = -1.000000000000000; //theta = 180.0-degree
  mu_data[ 1] = -0.996194698091746; //theta = 175.0-degree
  mu_data[ 2] = -0.965925826289068; //theta = 165.0-degree
  mu_data[ 3] = -0.900000000000000; //theta = 154.2-degree
  mu_data[ 4] = -0.866025403784439; //theta = 160.0-degree
  mu_data[ 5] = -0.800000000000000; //theta = 143.1-degree
  mu_data[ 6] = -0.750000000000000; //theta = 138.6-degree
  mu_data[ 7] = -0.707106781186548; //theta = 135.0-degree
  mu_data[ 8] = -0.600000000000000; //theta = 126.9-degree
  mu_data[ 9] = -0.500000000000000; //theta = 120.0-degree
  mu_data[10] = -0.400000000000000; //theta = 113.6-degree
  mu_data[11] = -0.258819045102521; //theta = 105.0-degree
  mu_data[12] = -0.050000000000000; //theta =  92.9-degree
  mu_data[13] = -0.005000000000000; //theta =  90.3-degree
  mu_data[14] =  0.000000000000000; //theta =  90.0-degree
  mu_data[15] =  0.005000000000000; //theta =  89.7-degree
  mu_data[16] =  0.050000000000000; //theta =  87.1-degree
  mu_data[17] =  0.258819045102521; //theta =  75.0-degree
  mu_data[18] =  0.400000000000000; //theta =  66.4-degree
  mu_data[19] =  0.500000000000000; //theta =  60.0-degree
  mu_data[20] =  0.600000000000000; //theta =  53.1-degree
  mu_data[21] =  0.707106781186548; //theta =  45.0-degree
  mu_data[22] =  0.750000000000000; //theta =  41.4-degree
  mu_data[23] =  0.800000000000000; //theta =  36.9-degree
  mu_data[24] =  0.866025403784439; //theta =  30.0-degree
  mu_data[25] =  0.900000000000000; //theta =  25.8-degree
  mu_data[26] =  0.965925826289068; //theta =  15.0-degree
  mu_data[27] =  0.996194698091746; //theta =   5.0-degree
  mu_data[28] =  1.000000000000000; //theta =   0.0-degree

  Real8 max_xs_val = 1.0E-3;
  xs_data.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    calc_incoherent_inelastic_scatter(ene_in_data, ene_out_data, mu_data[i], xs_data[i]);

    if( max_xs_val < xs_data[i] )
    {
      max_xs_val = xs_data[i];
    }
  }
  Real8 min_xs_val = max_xs_val * 0.01;

  int           j;
  Integer       int_chk;
  Real8         mid_mu;
  Real8         mid_xs;
  vector<Real8> new_mu, new_mu_part, new_xs, new_xs_part;
  new_mu.clear();
  new_mu_part.clear();
  new_xs.clear();
  new_xs_part.clear();

  new_mu.push_back(mu_data[0]);
  new_xs.push_back(xs_data[0]);
  for(int i=1; i<i_max; i++)
  {
    new_mu_part.push_back(mu_data[i-1]);
    new_xs_part.push_back(xs_data[i-1]);
    new_mu_part.push_back(mu_data[i]);
    new_xs_part.push_back(xs_data[i]);

    j = 1;
    mid_mu  = 0.5*(new_mu_part[j] + new_mu_part[j-1]);
    calc_incoherent_inelastic_scatter(ene_in_data, ene_out_data, mid_mu, mid_xs);
    int_chk = check_mu_grid(new_mu_part[j-1], new_mu_part[j], new_xs_part[j-1], new_xs_part[j],
                            mid_xs, min_xs_val);
    while( int_chk < 0 || j < static_cast<int>(new_mu_part.size()-1) )
    {
      if( int_chk >= 0 )
      {
        j++;
      }
      else
      {
        //Add middle mu grid and cross section
        insert_middle_mu_grid(j, new_mu_part, new_xs_part, mid_mu, mid_xs);
      }
      mid_mu = 0.5*(new_mu_part[j] + new_mu_part[j-1]);
      calc_incoherent_inelastic_scatter(ene_in_data, ene_out_data, mid_mu, mid_xs);
      int_chk = check_mu_grid(new_mu_part[j-1], new_mu_part[j], new_xs_part[j-1], new_xs_part[j],
                              mid_xs, min_xs_val);
    }
    add_xs_at_each_mu_grid(new_mu, new_xs, new_mu_part, new_xs_part);
  }
  mu_data = new_mu;
  xs_data = new_xs;
  new_mu.clear();
  new_xs.clear();

  //Calculation of integrate value
  integrate_xs_at_mu_grid(mu_data, xs_data, mu_data_int, xs_data_int);
  integrate_xs_at_mu_grid_with_weight_mu(mu_data, xs_data, mu_data_int, xs_data_int);

  //Calculation of total scattering cross section
  calc_scat_xs_mu_tot(xs_data_tot, mu_data, xs_data);

  if( xs_data_tot < min_inelastic_xs_val )
  {
    xs_data_tot = 0.0;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Integer IncoherentInelasticScatterCalculator::check_mu_grid( Real8& mu_pre, Real8& mu_cur,
                                                             Real8& xs_pre, Real8& xs_cur,
                                                             Real8& mid_xs, Real8& min_xs_val )
{
  Integer chk_flg  = 1;
  Real8   delta_mu = fabs(mu_cur - mu_pre);
  if( delta_mu < 1.0E-7 )
  {
    chk_flg = 10;
    return chk_flg;
  }
  //else if( delta_mu > 0.5 )
  //{
  //  chk_flg = -10;
  //}

  Real8 ave_xs = 0.5*fabs(xs_pre + xs_cur);
  if( fabs(ave_xs) >= min_inelastic_xs_val )
  {
    if( fabs(mid_xs - ave_xs) >= err*(fabs(ave_xs) + min_xs_val) )
    {
      chk_flg = -100;
      return chk_flg;
    }

    if( fabs(xs_pre - xs_cur) >= fabs(ave_xs) )
    {
      chk_flg = -200;
      return chk_flg;
    }
  }
  else
  {
    if( fabs(mid_xs - ave_xs) >= err )
    {
      chk_flg = -300;
      return chk_flg;
    }
  }

  return chk_flg;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void IncoherentInelasticScatterCalculator::insert_middle_mu_grid
                                             ( int& ele_no, vector<Real8>& mu_data, vector<Real8>& xs_data,
                                               Real8& mid_mu, Real8& mid_xs )
{
  ta_obj.add_table_data_at_given_position(mu_data, xs_data, mid_mu, mid_xs, ele_no);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void IncoherentInelasticScatterCalculator::add_xs_at_each_mu_grid(vector<Real8>& new_mu, vector<Real8>& new_xs,
                                             vector<Real8>& new_mu_part, vector<Real8>& new_xs_part)
{
  int i_max = static_cast<int>(new_mu_part.size());
  for(int i=1; i<i_max; i++)
  {
    new_mu.push_back(new_mu_part[i]);
    new_xs.push_back(new_xs_part[i]);
  }
  new_mu_part.clear();
  new_xs_part.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void IncoherentInelasticScatterCalculator::integrate_xs_at_mu_grid
                                             ( vector<Real8>& mu_data,     vector<Real8>& xs_data,
                                               vector<Real8>& mu_data_int, vector<Real8>& xs_data_int )
{
  //trapezoidal integration
  int           i_max    = static_cast<int>(mu_data.size());
  Real8         xs_total = 0.0;
  vector<Real8> xs_total_vec;
  xs_total_vec.resize(i_max);
  for(int i=1; i<i_max; i++)
  {
    xs_total        += 0.5*fabs((xs_data[i] + xs_data[i-1])*(mu_data[i] - mu_data[i-1]));
    xs_total_vec[i]  = xs_total;
  }
  Real8 xs_part = xs_total * bin_no_inv;

  //Initialization of mu_data_int and xs_data_int
  mu_data_int.resize(bin_no_int);
  xs_data_int.resize(bin_no_int);
  for(int i=0; i<bin_no_int; i++)
  {
    mu_data_int[i] = 0.0;
    xs_data_int[i] = xs_part * static_cast<Real8>(i+1);
  }

  //Search mu_data_int
  int ele_no = 1;
  for(int i=0; i<bin_no_int; i++)
  {
    Real8 xs_data_int_val = xs_data_int[i];
    if( ele_no < i_max )
    {
      while( xs_data_int_val > xs_total_vec[ele_no] + min_value )
      {
        ele_no++;
        if( ele_no >= i_max - 1 )
        {
          ele_no = i_max -1;
          break;
        }
      }
    }

    if( ele_no >= i_max - 1 )
    {
      mu_data_int[i] = mu_data[i_max - 1];
    }
    else if( fabs( xs_data_int_val - xs_total_vec[ele_no] ) < xs_data_int_val*min_value )
    {
      mu_data_int[i] = mu_data[ele_no];
    }
    else
    {
      // xs = a*mu + b
      // residual_val = 0.5*a*mu_data[ele_no]^2 + b*mu_data[ele_no]
      //              - 0.5*a*mu^2 - b*mu
      // mu = (-B + sqrt(B^2-4*A*C))/(2*A) or (-B - sqrt(B^2-4*A*C))/(2*A)
      //    = (-B + sqrt(B^2-2*A'*C))/A'   or (-B - sqrt(B^2-2*A'*C))/A'
      // A' = 2*A = a
      // B  = b
      // C  = residual_val - 0.5*a*mu_data[ele_no]^2 - b*mu_data[ele_no]
      Real8 residual_val = xs_total_vec[ele_no] - xs_data_int_val;
      Real8 coef_a       = (xs_data[ele_no] - xs_data[ele_no-1]) / (mu_data[ele_no] - mu_data[ele_no-1]);
      Real8 coef_b       = xs_data[ele_no] - coef_a * mu_data[ele_no];
      Real8 coef_c       = residual_val - 0.5*coef_a*mu_data[ele_no]*mu_data[ele_no] - coef_b*mu_data[ele_no];

      if( fabs(coef_a) >= min_inelastic_xs_val + min_sig_dif )
      {
        Real8 part_a = -1.0*coef_b;
        Real8 part_b = coef_b*coef_b - 2.0*coef_a*coef_c;
        if( coef_b*coef_b - 2.0*coef_a*coef_c < min_value )
        {
          part_b = 0.0;
        }
        else
        {
          part_b = sqrt(part_b);
        }
        mu_data_int[i] = (part_a + part_b) / coef_a;
        if( mu_data_int[i] < mu_data[ele_no-1] || mu_data[ele_no] < mu_data_int[i] )
        {
          mu_data_int[i] = (part_a - part_b) / coef_a;
        }
      }
      else if( fabs(coef_b) < 1.0E-10 )
      {
        mu_data_int[i] = mu_data[ele_no];
      }
      else
      {
        mu_data_int[i] = mu_data[ele_no] - residual_val / coef_b;
      }
    }
  }
  xs_total_vec.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void IncoherentInelasticScatterCalculator::integrate_xs_at_mu_grid_with_weight_mu
                                             ( vector<Real8>& mu_data,     vector<Real8>& xs_data,
                                               vector<Real8>& mu_data_int, vector<Real8>& xs_data_int )
{
  int   ele_no     = 1;
  int   ele_no_max = static_cast<int>(mu_data.size());
  Real8 mu_pre = mu_data[0];
  Real8 mu_cur = mu_data[1];
  Real8 xs_pre = xs_data[0];
  Real8 xs_cur = xs_data[1];
  for(int i=0; i<bin_no_int; i++)
  {
    xs_data_int[i] = 0.0;
  }

  for(int i=0; i<bin_no_int; i++)
  {
    Real8 mu_data_int_val = mu_data_int[i];
    while( mu_data_int_val > mu_data[ele_no] - min_ene_dif )
    {
      xs_data_int[i] += third*(xs_cur - xs_pre)*(mu_cur*mu_cur + mu_cur*mu_pre + mu_pre*mu_pre)
                      + 0.5*(mu_cur*xs_pre - mu_pre*xs_cur)*(mu_cur + mu_pre);
//      Real8 coef_a    = (xs_cur - xs_pre) / (mu_cur - mu_pre);
//      Real8 coef_b    = xs_cur - mu_cur * coef_a;
//      xs_data_int[i] += third*coef_a*(mu_cur*mu_cur*mu_cur - mu_pre*mu_pre*mu_pre)
//                      + 0.5*coef_b*(mu_cur*mu_cur - mu_pre*mu_pre);
      ele_no++;
      if( ele_no >= ele_no_max )
      {
        break;
      }
      mu_pre = mu_cur;
      xs_pre = xs_cur;
      mu_cur = mu_data[ele_no];
      xs_cur = xs_data[ele_no];
    }
    if( ele_no >= ele_no_max )
    {
      break;
    }

    if( fabs( mu_data_int_val - mu_data[ele_no] ) > mu_data_int_val*min_value )
    {
      Real8 coef_a = (xs_cur - xs_pre) / (mu_cur - mu_pre);
      Real8 coef_b = xs_cur - mu_cur * coef_a;
      mu_cur = mu_data_int_val;
      xs_cur = coef_a*mu_cur + coef_b;
      xs_data_int[i] += third*(xs_cur - xs_pre)*(mu_cur*mu_cur + mu_cur*mu_pre + mu_pre*mu_pre)
                      + 0.5*(mu_cur*xs_pre - mu_pre*xs_cur)*(mu_cur + mu_pre);
//      xs_data_int[i] += third*coef_a*(mu_cur*mu_cur*mu_cur - mu_pre*mu_pre*mu_pre)
//                      + 0.5*coef_b*(mu_cur*mu_cur - mu_pre*mu_pre);
      mu_pre = mu_cur;
      xs_pre = xs_cur;
      mu_cur = mu_data[ele_no];
      xs_cur = xs_data[ele_no];
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void IncoherentInelasticScatterCalculator::calc_incoherent_inelastic_scatter
                                             (Real8& ene_in_data, Real8& ene_out_data, Real8& mu_data,
                                              Real8& xs_data)
{
  xs_data = 0.0;
  Real8 temp_tsl_ev_inv_data = temp_tsl_ev_inv;
  if( temp_flg == const_temp_mode && opt_inelastic != free_gas_mode )
  {
    temp_tsl_ev_inv_data = conv_th_ene_inv;
  }

  int   sct_flg = 0;
  Real8 sab     = 0.0;
  Real8 coef    = 0.5*temp_tsl_ev_inv*sqrt(ene_out_data/ene_in_data);
  Real8 alpha_data, beta_data, beta_data_temp;
  calc_alpha_beta(ene_in_data, ene_out_data, mu_data, temp_tsl_ev_inv_data, mass_inv[0], alpha_data, beta_data);
  calc_beta(ene_in_data, ene_out_data, temp_tsl_ev_inv, beta_data_temp);
  Integer alpha_beta_chk = check_alpha_beta_data(alpha_data, beta_data);

  sct_flg = 0;
  if( opt_inelastic == free_gas_mode || alpha_beta_chk == 0 )
  {
    sab = 0.0;
    if( opt_inelastic == free_gas_mode )
    {
      sab = 0.5*exp(-0.25*(alpha_data*alpha_data + beta_data*beta_data)/alpha_data) / sqrt(M_PI*alpha_data);
    }
    else
    {
      sab = calc_sab(alpha_data, beta_data, mass_inv[0]);
    }

    if( (njoy_mode_flg==njoy_mode_on || stored_form_flg==log_stored_mode) && opt_inelastic!=free_gas_mode )
    {
      if( sab > min_sab_index_number - 1.0 )
      {
        xs_data += sig_b[0]*coef*exp(-0.5*beta_data_temp+sab);
      }
      else
      {
        sct_flg = 1;
      }
    }
    else
    {
      if( sab > min_sab_index_number - 1.0 )
      {
        xs_data += sig_b[0]*coef*exp(-0.5*beta_data)*sab;
      }
      else
      {
        if( opt_inelastic!=free_gas_mode )
        {
          sct_flg = 1;
        }
      }
    }
  }
  else
  {
    sct_flg = 1;
  }

  //Short Collision Time (SCT) approximation
  if( sct_flg > 0 )
  {
    if( temp_flg == const_temp_mode )
    {
      alpha_data *= conv_th_ene * temp_tsl_ev_inv;
      beta_data  *= conv_th_ene * temp_tsl_ev_inv;
    }
    Real8 beta_abs  = fabs(beta_data);
    Real8 coef_temp = temp_tsl_ev*temp_eff_ev_inv[0];

    xs_data += 0.5*sig_b[0]*coef*sqrt(coef_temp/(M_PI*alpha_data))
           * exp( -0.25*coef_temp*(alpha_data - 2.0*beta_abs + beta_abs*beta_abs/alpha_data)
                  - 0.5*(beta_data+beta_abs) );

    int i_max = static_cast<int>(sig_b.size());
    if( i_max > 1 )
    {
      for(int i=1; i<i_max; i++)
      {
        if( sig_b[1] > min_sab_value )
        {
          alpha_data *= mass_inv[i] / mass_inv[i-1];
          coef_temp   = temp_tsl_ev*temp_eff_ev_inv[i];
          xs_data += 0.5*sig_b[1]*coef*sqrt(coef_temp/(M_PI*alpha_data))
                   * exp( -0.25*coef_temp*(alpha_data - 2.0*beta_abs + beta_abs*beta_abs/alpha_data)
                          - 0.5*(beta_data+beta_abs) );
        }
      }
    }
  }

  if( xs_data < min_inelastic_xs_val )
  {
    xs_data = 0.0;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Integer IncoherentInelasticScatterCalculator::check_alpha_beta_data(Real8& alpha_data, Real8& beta_data)
{
  Integer alpha_beta_chk = 0;
  if( opt_inelastic == free_gas_mode )
  {
    return alpha_beta_chk;
  }

  int beta_m, beta_p;
  ti_obj.search_neighbor_value(beta_data, beta, beta_m, beta_p);
  if( alpha_data > alpha_max[beta_m] && alpha_data > alpha_max[beta_p] )
  {
    alpha_beta_chk = 1;
    return alpha_beta_chk;
  }

  if( beta_data > beta_max || beta_data < beta_min )
  {
    alpha_beta_chk = 3;
    return alpha_beta_chk;
  }
  
  return alpha_beta_chk;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void IncoherentInelasticScatterCalculator::calc_alpha_beta
                                             (Real8& ene_in_data, Real8& ene_out_data, Real8& mu_data,
                                              Real8& temp_tsl_ev_inv_data, Real8& mass_inv_data,
                                              Real8& alpha_data, Real8& beta_data)
{
  alpha_data = (ene_out_data + ene_in_data - 2.0*mu_data*sqrt(ene_in_data*ene_out_data)) 
             * temp_tsl_ev_inv_data * mass_inv_data;
        
  //Adjust alpha value (to consit the alpha value which is obtained by NJOY).
  if( alpha_data < alpha_min_val )
  {
    if( temp_flg == const_temp_mode && opt_inelastic != free_gas_mode )
    {
      alpha_data = alpha_min_val*temp_tsl_ev*conv_th_ene_inv;
    }
    else
    {
      alpha_data = alpha_min_val;
    }
  }
 
  calc_beta(ene_in_data, ene_out_data, temp_tsl_ev_inv_data, beta_data);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void IncoherentInelasticScatterCalculator::calc_beta
                                             (Real8& ene_in_data, Real8& ene_out_data,
                                              Real8& temp_tsl_ev_inv_data, Real8& beta_data)
{
  beta_data = (ene_out_data - ene_in_data)*temp_tsl_ev_inv_data;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Real8 IncoherentInelasticScatterCalculator::calc_sab(Real8& alpha_data, Real8& beta_data, Real8& mass_inv_data)
{ 
  Real8 sab_val       = 0.0;
  Real8 beta_data_mod = beta_data;
  if( symmetric_flg == symmetric_mode ) //S is symmetric
  {
    beta_data_mod = fabs(beta_data);
  }

  if( njoy_mode_flg == njoy_mode_off )
  {
    ti_obj.interpolation_2d(beta_data_mod, alpha_data, sab_val, beta_range_data, beta_int_data, beta,
                            sab_range_data, sab_int_data, sab_alpha_data, sab_data);
  }
  else
  {
    if( fabs(sab_chk) > min_sab_value && alpha_data < sab_alpha_data[0][0] &&
        symmetric_flg == symmetric_mode && fabs(beta_data) <= 0.2 )
    {
      sab_val = sab_data[0][0] + 0.5*(log(sab_alpha_data[0][0]/alpha_data))
              - sab_chk*beta_data*beta_data/alpha_data;
      if( sab_val < min_sab_index_number )
      {
        sab_val = min_sab_index_number;
      }
      return sab_val;
    }

    int beta_adjust_flg = 0;
    int beta_m, beta_p;
    ti_obj.search_neighbor_value(beta_data_mod, beta, beta_m, beta_p);
    if( beta_p == static_cast<int>(beta.size()) - 1 )
    {
      beta_m--;
      beta_adjust_flg = 1;
    }

    if( beta_m < 0 )
    {
      ti_obj.interpolation_2d(beta_data_mod, alpha_data, sab_val, beta_range_data, beta_int_data, beta,
                              sab_range_data, sab_int_data, sab_alpha_data, sab_data);
      if( sab_val < min_sab_index_number )
      {
        sab_val = min_sab_index_number;
      }
      return sab_val;
    }

    int alpha_m0, alpha_m1, alpha_m2, alpha_p0, alpha_p1, alpha_p2;
    ti_obj.search_neighbor_value(alpha_data, sab_alpha_data[beta_m],   alpha_m0, alpha_p0);
    ti_obj.search_neighbor_value(alpha_data, sab_alpha_data[beta_m+1], alpha_m1, alpha_p1);
    ti_obj.search_neighbor_value(alpha_data, sab_alpha_data[beta_m+2], alpha_m2, alpha_p2);

    if( alpha_data/mass_inv_data >= 30.0 || fabs(beta_data) >= 30.0 )
    {
      if( beta_adjust_flg == 0 )
      {
        if( sab_data[beta_m  ][alpha_m0]   < min_sab_index_number ||
            sab_data[beta_m  ][alpha_m0+1] < min_sab_index_number ||
            sab_data[beta_m+1][alpha_m1]   < min_sab_index_number ||
            sab_data[beta_m+1][alpha_m1+1] < min_sab_index_number )
        {
          sab_val = min_sab_index_number - 5.0;
          return sab_val;
        }
      }
      else
      {
        if( sab_data[beta_m+1][alpha_m1]   < min_sab_index_number ||
            sab_data[beta_m+1][alpha_m1+1] < min_sab_index_number ||
            sab_data[beta_m+2][alpha_m2]   < min_sab_index_number ||
            sab_data[beta_m+2][alpha_m2+1] < min_sab_index_number )
        {
          sab_val = min_sab_index_number - 5.0;
          return sab_val;
        }
      }
    }

    if( alpha_p0 == static_cast<int>(sab_alpha_data[beta_m].size()) - 1 )
    {
      alpha_m0--;
    }
    if( alpha_p1 == static_cast<int>(sab_alpha_data[beta_m+1].size()) - 1 )
    {
      alpha_m1--;
    }
    if( alpha_p2 == static_cast<int>(sab_alpha_data[beta_m+2].size()) - 1 )
    {
      alpha_m2--;
    }
    if( alpha_m0 < 0 || alpha_m1 < 0 || alpha_m2 < 0 )
    {
      ti_obj.interpolation_2d(beta_data_mod, alpha_data, sab_val, beta_range_data, beta_int_data, beta,
                              sab_range_data, sab_int_data, sab_alpha_data, sab_data);
      if( sab_val < min_sab_index_number )
      {
        sab_val = min_sab_index_number;
      }
      return sab_val;
    }

    Real8 s0, s1, s2;
    s0 = quadratic_interpolation(alpha_data,
                                 sab_alpha_data[beta_m][alpha_m0],   sab_data[beta_m][alpha_m0],
                                 sab_alpha_data[beta_m][alpha_m0+1], sab_data[beta_m][alpha_m0+1],
                                 sab_alpha_data[beta_m][alpha_m0+2], sab_data[beta_m][alpha_m0+2]);
    s1 = quadratic_interpolation(alpha_data,
                                 sab_alpha_data[beta_m+1][alpha_m1],   sab_data[beta_m+1][alpha_m1],
                                 sab_alpha_data[beta_m+1][alpha_m1+1], sab_data[beta_m+1][alpha_m1+1],
                                 sab_alpha_data[beta_m+1][alpha_m1+2], sab_data[beta_m+1][alpha_m1+2]);
    s2 = quadratic_interpolation(alpha_data,
                                 sab_alpha_data[beta_m+2][alpha_m2],   sab_data[beta_m+2][alpha_m2],
                                 sab_alpha_data[beta_m+2][alpha_m2+1], sab_data[beta_m+2][alpha_m2+1],
                                 sab_alpha_data[beta_m+2][alpha_m2+2], sab_data[beta_m+2][alpha_m2+2]);

    sab_val = quadratic_interpolation(beta_data_mod, beta[beta_m], s0, beta[beta_m+1], s1, beta[beta_m+2], s2);
  }
  return sab_val;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Real8 IncoherentInelasticScatterCalculator::quadratic_interpolation(Real8& x_val, 
                                     Real8& x1, Real8& y1, Real8& x2, Real8& y2, Real8& x3, Real8& y3)
{
  Real8 y_val = 0.0;
  if( x_val < x1 )
  {
    if( y1 > y2 )
    {
      y_val = y1;
    }
    else
    {
      ti_obj.interpolation_1d(int_log_lin, x_val, y_val, x1, y1, x2, y2);
    }
  }
  else if( x_val > x3 )
  {
    if( y3 > y2 )
    {
      y_val = y3;
    }
    else
    {
      ti_obj.interpolation_1d(int_lin_lin, x_val, y_val, x2, y2, x3, y3);
    }
  }
  else if( fabs(y1 - y2) > 2.0 || fabs(y2 - y3) > 2.0 )
  {
    if( x_val < x2 )
    {
      ti_obj.interpolation_1d(int_lin_lin, x_val, y_val, x1, y1, x2, y2);
    }
    else
    {
      ti_obj.interpolation_1d(int_lin_lin, x_val, y_val, x2, y2, x3, y3);
    }
  }
  else
  {
    y_val = math_obj.quadratic_interpolation(x_val, x1, y1, x2, y2, x3, y3);
  }

  if( y_val < min_sab_index_number )
  {
    y_val = min_sab_index_number;
  }

  return y_val;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void IncoherentInelasticScatterCalculator::preparation_for_incoherent_inerastic_scatter()
{
  calc_incoherent_inelastic_scat_flg = 1; 
  temp_flg      = sab_data_obj.get_inelastic_temp_flg();
  symmetric_flg = sab_data_obj.get_inelastic_symmetric_flg();

  check_set_data();

  if( opt_inelastic != free_gas_mode )
  {
    search_sab_temp();
    search_temp_eff();
  }
  else
  {
    beta.resize(45);
    beta[ 0] =    0.0;
    beta[ 1] =    0.1;
    beta[ 2] =    2.0;
    beta[ 3] =    4.0;
    beta[ 4] =    6.0;
    beta[ 5] =    8.0;
    beta[ 6] =   10.0;
    beta[ 7] =   15.0;
    beta[ 8] =   25.0;
    beta[ 9] =   30.0;
    beta[10] =   35.0;
    beta[11] =   40.0;
    beta[12] =   45.0;
    beta[13] =   50.0;
    beta[14] =   55.0;
    beta[15] =   60.0;
    beta[16] =   65.0;
    beta[17] =   70.0;
    beta[18] =   75.0;
    beta[19] =   80.0;
    beta[20] =  100.0;
    beta[21] =  120.0;
    beta[22] =  140.0;
    beta[23] =  160.0;
    beta[24] =  180.0;
    beta[25] =  200.0;
    beta[26] =  250.0;
    beta[27] =  300.0;
    beta[28] =  350.0;
    beta[29] =  400.0;
    beta[30] =  500.0;
    beta[31] =  600.0;
    beta[32] =  700.0;
    beta[33] =  800.0;
    beta[34] =  900.0;
    beta[35] = 1000.0;
    beta[36] = 1250.0;
    beta[37] = 1500.0;
    beta[38] = 1750.0;
    beta[39] = 2000.0;
    beta[40] = 2250.0;
    beta[41] = 2500.0;
    beta[42] = 2750.0;
    beta[43] = 3000.0;
    beta[44] = 3500.0;
  }
  calc_bound_scattering_xs();
  set_energy_grid();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void IncoherentInelasticScatterCalculator::check_set_data()
{
  vector<string> err_com;
  err_com.clear();

  if( opt_inelastic != use_nucl_data && opt_inelastic != no_calc && opt_inelastic != free_gas_mode )
  {
    ostringstream oss01, oss02, oss03, oss04;
    oss01 << opt_inelastic;
    oss02 << no_calc;
    oss03 << free_gas_mode;
    oss04 << use_nucl_data;
    string str_data01 = "Inelastic option : " + oss01.str();
    string str_data02 = "Inelastic option is not appropriate.";
    string str_data03 = "Available elastic option";
    string str_data04 = "  No calculation               : " + oss02.str();
    string str_data05 = "  Calculate as a free gas      : " + oss03.str();
    string str_data06 = "  Calculate using nuclear data : " + oss04.str();
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back(str_data05);
    err_com.push_back(str_data06);
  }

  if( bin_no <= 0 )
  {
    ostringstream oss01;
    oss01 << bin_no;
    string str_data01 = "Bin number : " + oss01.str();
    err_com.push_back(str_data01);
    err_com.push_back("Bin number is not input or set inappropriate value.");
  }

  if( atom_no < min_value )
  {
    ostringstream oss01;
    oss01 << atom_no;
    string str_data01 = "Atom number : " + oss01.str();
    err_com.push_back(str_data01);
    err_com.push_back("Atom number is not input or set inappropriate value.");
  }

  if( err < min_value || err_half < min_value )
  {
    ostringstream oss01;
    oss01 << err;
    string str_data01 = "Error value : " + oss01.str();
    err_com.push_back(str_data01);
    err_com.push_back("Error value is not input or set inappropriate value.");
  }

  if( ene_max < min_value )
  {
    ostringstream oss01;
    oss01 << ene_max;
    string str_data01 = "Maximum energy : " + oss01.str();
    err_com.push_back(str_data01);
    err_com.push_back("Maximum energy is not input or set inappropriate value.");
  }

  if( temp_inp < min_value )
  {
    ostringstream oss01;
    oss01 << temp_inp;
    string str_data01 = "Temperature : " + oss01.str();
    err_com.push_back(str_data01);
    err_com.push_back("Temperature is not input or set inappropriate value.");
  }

#ifdef DEBUG_MODE
  Real8 temp_nucl = static_cast<Real8>(nucl_data_obj.get_general_data_obj().get_temp());
  if( fabs(temp_nucl - temp_inp) >= min_ene_dif*temp_inp )
  {
    ostringstream oss01, oss02;
    oss01 << temp_inp;
    oss02 << temp_nucl;
    string str_data01 = "Temperature (input)        : " + oss01.str();
    string str_data02 = "Temperature (nuclear data) : " + oss02.str();
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("The input temperature is not identical to the nuclear data.");
  }
#endif

  if( temp_flg != actual_temp_mode && temp_flg != const_temp_mode )
  {
    ostringstream oss01;
    oss01 << temp_flg;
    string str_data01 = "Temperature flg : " + oss01.str();
    err_com.push_back(str_data01);
    err_com.push_back("Temperature flg is not input or set inappropriate value.");
  }

  if( symmetric_flg != symmetric_mode && symmetric_flg != asymmetric_mode )
  {
    ostringstream oss01;
    oss01 << symmetric_flg;
    string str_data01 = "Symmetric flg : " + oss01.str();
    err_com.push_back(str_data01);
    err_com.push_back("Symmetric flg is not input or set inappropriate value.");
  }

  if( static_cast<int>(err_com.size()) > 0 )
  {
    string class_name = "IncoherentInelasticScatterCalculator";
    string func_name  = "check_set_data()";
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void IncoherentInelasticScatterCalculator::search_sab_temp()
{
  set_sab_data();
  set_sab_data_arbitrary_temperature();
  set_temp_tsl_ev(temp_tsl);

  set_beta_max();
  set_alpha_max_and_min();

  sab_chk = 0.0;
  if( njoy_mode_flg == njoy_mode_on && stored_form_flg == direct_stored_mode )
  {
    modify_sab_data();
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void IncoherentInelasticScatterCalculator::set_sab_data()
{
  beta.clear();
  beta_range_data.clear();
  beta_int_data.clear();
  clr_obj.clear_vec_array2_int( sab_range_data);
  clr_obj.clear_vec_array2_int( sab_int_data);
  clr_obj.clear_vec_array2_real(sab_alpha_data);
  cp_obj.copy_vec_array1_real8(beta, sab_data_obj.get_inelastic_beta_data());
  beta_range_data = sab_data_obj.get_inelastic_beta_range_data();
  beta_int_data   = sab_data_obj.get_inelastic_beta_int_data();
  sab_range_data  = sab_data_obj.get_inelastic_scat_law_range_data();
  sab_int_data    = sab_data_obj.get_inelastic_scat_law_int_data();
  cp_obj.copy_vec_array2_real8(sab_alpha_data,sab_data_obj.get_inelastic_scat_law_alpha_data());

  stored_form_flg = sab_data_obj.get_inelastic_stored_form_flg();
  if( stored_form_flg != direct_stored_mode && stored_form_flg != log_stored_mode  )
  {
    string class_name = "IncoherentInelasticScatterCalculator";
    string func_name  = "set_sab_data()";

    ostringstream oss01, oss02, oss03;
    oss01 << stored_form_flg;
    oss02 << direct_stored_mode;
    oss03 << log_stored_mode;
    string str_data01 = "S(a,b) stored form flg : " + oss01.str();
    string str_data02 = "S(a,b) stored form flg is not input or set inappropriate value.";
    string str_data03 = "Appropriate  S(a,b) stored form flg";
    string str_data04 = "  Direct stored mode   : " + oss02.str();
    string str_data05 = "  Log stored mode      : " + oss03.str();
    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back(str_data05);
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void IncoherentInelasticScatterCalculator::set_sab_data_arbitrary_temperature()
{
  Real temp_err = 2.0E-2; //1.0 / 50.0 = 2.0E-2;
  Real temp_war = 1.0E-4;
  //temp_err=2% is set by K. Tada.
  //This value is allows to process when the input temperature is 300 K and the nucluear data temperature
  //is 296 K.
  //However, FRENDY outputs the error message  when the input temperature is 300 K and the nuclear data
  //temperature is 293.6 K.
  //To divide the processing of these two temperatures, this value is used.


  Real temp_real = static_cast<Real>(temp_inp);
  Real temp_max  = temp_real * 1.1;
  temp_err  = static_cast<Real>(temp_inp*temp_err);
  temp_war  = static_cast<Real>(temp_inp*temp_war);

  temp_tsl = 0.0;
  clr_obj.clear_vec_array2_real(sab_data);

  int i_max      = static_cast<int>(sab_data_obj.get_inelastic_temp_data_base().size());
  int output_flg = 0;
  sab_data.resize(i_max);
  Real temp_dif_min_tot = 1.0E10;
  for(int i=0; i<i_max; i++)
  {
    Real temp_dif             = fabs(temp_real - sab_data_obj.get_inelastic_temp_data_base()[i]);
    Real temp_dif_min         = temp_dif;
    Real temp_dif_min_val     = sab_data_obj.get_inelastic_temp_data_base()[i];
    int  temp_dif_min_mod_flg = 0;
         temp_tsl             = sab_data_obj.get_inelastic_temp_data_base()[i];
    cp_obj.copy_vec_array1_real8(sab_data[i], sab_data_obj.get_inelastic_scat_law_data_base()[i]);

    vector<Real> temp_sab = sab_data_obj.get_inelastic_temp_data()[i];
    for(int j=0; j<static_cast<int>(temp_sab.size()); j++)
    {
      temp_dif = fabs(temp_real - temp_sab[j]);
      if( temp_dif < temp_dif_min )
      {
        temp_tsl = temp_sab[j];
        cp_obj.copy_vec_array1_real8(sab_data[i], sab_data_obj.get_inelastic_scat_law_data()[i][j]);
        temp_dif_min         = temp_dif;
        temp_dif_min_val     = temp_sab[j];
        if( temp_dif_min < temp_dif_min_tot - min_value )
        {
          temp_dif_min_tot     = temp_dif_min;
          temp_dif_min_mod_flg = 1;
        }
      }
      else if( temp_max < temp_sab[j] )
      {
        break;
      }
    }

    if( temp_dif_min > temp_war )
    {
      string class_name = "IncoherentInelasticScatterCalculator";
      string func_name  = "set_sab_data_arbitrary_temperature()";

      ostringstream oss01, oss02, oss03, oss04, oss05;
      oss01 << i+1;
      oss02 << i_max;
      oss03 << temp_dif_min;
      oss04 << temp_real;
      oss05 << temp_dif_min_val;
      string str_data01 = "i = " + oss01.str() + " / " + oss02.str();
      string str_data02 = "Relative difference              : " + oss03.str();
      string str_data03 = "Temperature (input)              : " + oss04.str();
      string str_data04 = "Closest temperature (S(a,b)data) : " + oss05.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back(str_data04);
      err_com.push_back("");
      err_com.push_back("The available temperature is as follows:");
      ostringstream oss10;
      oss10 << fixed << setprecision(3) << setw(8) << sab_data_obj.get_inelastic_temp_data_base()[i];
      string str_data10 = "  " + oss10.str();
      err_com.push_back(str_data10);

      for(int j=0; j<static_cast<int>(temp_sab.size()); j++)
      {
        ostringstream oss11;
        oss11 << fixed << setprecision(3) << setw(8) << temp_sab[j];
        string str_data11 = "  " + oss11.str();
        err_com.push_back(str_data11);
      }
      err_com.push_back("");

      if( temp_dif_min < temp_err )
      {
        if( output_flg == 0 || temp_dif_min_mod_flg > 0 )
        {
          ostringstream oss_err;
          oss_err << temp_war;
          string str_err = "Relative difference is larger than " + oss_err.str();
          err_com.push_back(str_err);
          err_obj.output_caution(class_name, func_name, err_com);
          output_flg++;
        }
      }
      else
      {
        ostringstream oss_err;
        oss_err << temp_err;
        string str_err = "Relative difference is larger than " + oss_err.str();
        err_com.push_back(str_err);
        err_obj.output_runtime_error(class_name, func_name, err_com);
      }
    }
    temp_sab.clear();
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void IncoherentInelasticScatterCalculator::set_beta_max()
{
  //Set maximum value of beta
  int i_max = static_cast<int>(beta.size());
  if( beta[i_max-1] > 0.0 )
  {
    beta_max = beta[i_max-1] * (1.0 + min_ene_dif);
  }
  else
  {
    beta_max = beta[i_max-1] * (1.0 - min_ene_dif);
  }

  //Set minimum value of beta
  if( symmetric_flg == symmetric_mode ) //S is symmetric
  {
    beta_min = -1.0*beta_max;
  }
  else //S is asymmetric
  {
    if( beta[0] > 0.0 )
    {
      beta_min = beta[0] * (1.0 - min_ene_dif);
    }
    else
    {
      beta_min = beta[0] * (1.0 + min_ene_dif);
    }
  }

  //Check beta_max
  Real8 beta_max_chk;
  if( temp_flg == const_temp_mode )
  {
    beta_max_chk = beta_max*conv_th_ene;
  }
  else
  {
    beta_max_chk = beta_max*temp_tsl_ev;
  }
  if( beta_max_chk < beta_max_warning_val )
  {
    string class_name = "IncoherentInelasticScatterCalculator";
    string func_name  = "set_beta_max()";

    ostringstream oss01, oss02;
    oss01 << beta_max;
    oss02 << beta_max_chk;
    string str_data01 = "Maximum value of beta  : " + oss01.str();
    string str_data02 = "The maximum value of beta limits the energy transfer.";
    string str_data03 = "The allowed energy transfer is from ene_in+" + oss02.str()
                      + " to ene_in-" + oss02.str() + " [eV] (ene_in : incident energy).";
    string str_data04 = "The short collision time (SCT) approximation will be used for transfers larger than "
                      + oss02.str() + " [eV].";
    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_obj.output_caution(class_name, func_name, err_com);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void IncoherentInelasticScatterCalculator::set_alpha_max_and_min()
{
  //Set maximum and minimum value of alpha
  int i_max = static_cast<int>(sab_alpha_data.size());
  alpha_min.resize(i_max);
  alpha_max.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(sab_alpha_data[i].size());
    if( sab_alpha_data[i][0] > 0.0 )
    {
      alpha_min[i] = sab_alpha_data[i][0] * (1.0 - min_ene_dif);
    }
    else
    {
      alpha_min[i] = sab_alpha_data[i][0] * (1.0 + min_ene_dif);
    }

    if( sab_alpha_data[i][j_max-1] > 0.0 )
    {
      alpha_max[i] = sab_alpha_data[i][j_max-1] * (1.0 + min_ene_dif);
    }
    else
    {
      alpha_max[i] = sab_alpha_data[i][j_max-1] * (1.0 - min_ene_dif);
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void IncoherentInelasticScatterCalculator::modify_sab_data()
{
  Integer sab_err_flg = 0;
  sab_chk = 0.0;

  int i_max = static_cast<int>(sab_data.size());
  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(sab_data[i].size());
    for(int j=0; j<j_max; j++)
    {
      if( sab_data[i][j] >= min_sab_value )
      {
        sab_data[i][j] = log(sab_data[i][j]);
      }
      else
      {
        sab_data[i][j] = min_sab_index_number - 5.0;
        sab_err_flg    = 1;
      }
    }
  }

  if( i_max > 1 && static_cast<int>(sab_data[0].size()) > 1 )
  {
    if( sab_data[0][0] > sab_data[0][1] )
    {
      //sab_chk is identical to cliq in NJOY
      sab_chk = (sab_data[0][0] - sab_data[1][0])
              * sab_alpha_data[0][0] / (beta[1] * beta[1]);
    }
  }

  if( sab_err_flg > 0 )
  {
    string class_name = "IncoherentInelasticScatterCalculator";
    string func_name  = "modify_sab_data()";

    Real8 sab_tmp = -2.0*(min_sab_index_number+5.0)*temp_tsl_ev;

    ostringstream oss01;
    oss01 << sab_tmp;
    string str_data01 = "S(a,b) contains very small value, i.e., less than 1.0e-225.";
    string str_data02 = "Calculation results may be bad for transfers larger than " + oss01.str() + "[eV].";
    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_obj.output_caution(class_name, func_name, err_com);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void IncoherentInelasticScatterCalculator::set_temp_tsl_ev(Real8 temp_val)
{
  temp_tsl_ev     = temp_val * boltzmann_const;
  temp_tsl_ev_inv = 1.0 / temp_tsl_ev;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void IncoherentInelasticScatterCalculator::search_temp_eff()
{
  vector<vector<Integer> > teff_range = sab_data_obj.get_inelastic_temp_eff_range_data();
  vector<vector<Integer> > teff_int   = sab_data_obj.get_inelastic_temp_eff_int_data();
  vector<vector<Real> >    teff_temp  = sab_data_obj.get_inelastic_temp_eff_temp_data();
  vector<vector<Real> >    teff_data  = sab_data_obj.get_inelastic_temp_eff_data();

  int i_max = static_cast<int>(teff_temp.size());
  temp_eff.resize(i_max);
  temp_eff_ev.resize(i_max);
  temp_eff_ev_inv.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(teff_temp[i].size());
    if( j_max == 0 )
    {
      temp_eff[i] = temp_tsl;
    }
    else
    {
      if( j_max == 1 )
      {
        if( fabs(teff_temp[i][0] - temp_tsl) > temp_tsl*0.1 )
        {
          string class_name = "IncoherentInelasticScatterCalculator";
          string func_name  = "search_temp_eff()";

          ostringstream oss01, oss02;
          oss01 << temp_tsl;
          oss02 << teff_temp[i][0];
          string str_data01 = "Temperature (from TSL data) : " + oss01.str();
          string str_data02 = "Effective temperature       : " + oss02.str();

          vector<string> err_com;
          err_com.push_back(str_data01);
          err_com.push_back(str_data02);
          err_com.push_back("The relative difference of temperature and the effective temperature.");
          err_com.push_back("is much larger.");
          err_com.push_back("Please check the input file or nuclear data.");
          err_obj.output_runtime_error(class_name, func_name, err_com);
        } 
      }
      else
      {
        if( temp_tsl < teff_temp[i][0]*0.9 || temp_tsl > teff_temp[i][j_max-1]*1.1 )
        {
          string class_name = "IncoherentInelasticScatterCalculator";
          string func_name  = "search_temp_eff()";

          ostringstream oss01, oss02, oss03;
          oss01 << temp_tsl;
          oss02 << teff_temp[i][0];
          oss03 << teff_temp[i][j_max-1];
          string str_data01 = "Temperature (from TSL data)   : " + oss01.str();
          string str_data02 = "Minimum effective temperature : " + oss02.str();
          string str_data03 = "Maximum effective temperature : " + oss03.str();
  
          vector<string> err_com;
          err_com.push_back(str_data01);
          err_com.push_back(str_data02);
          err_com.push_back(str_data03);
          if( temp_tsl < teff_temp[i][0]*0.9 )
          {
            err_com.push_back("The temperature is smaller than the minimum  effective temperature.");
          }
          else if( temp_tsl > teff_temp[i][j_max-1]*1.1 )
          {
            err_com.push_back("The temperature is larger than the maximum  effective temperature.");
          }
          err_com.push_back("Please check the input file or nuclear data.");
          err_obj.output_runtime_error(class_name, func_name, err_com);
        }
      }
      ti_obj.interpolation_tab1(temp_tsl, temp_eff[i], teff_range[i], teff_int[i], teff_temp[i], teff_data[i]);
    }

    temp_eff_ev[i]     = temp_eff[i] * boltzmann_const; 
    temp_eff_ev_inv[i] = 1.0 / temp_eff_ev[i];
  }
  clr_obj.clear_vec_array2_int(teff_int);
  clr_obj.clear_vec_array2_int(teff_range);
  clr_obj.clear_vec_array2_real(teff_temp);
  clr_obj.clear_vec_array2_real(teff_data);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void IncoherentInelasticScatterCalculator::calc_bound_scattering_xs()
{
  sig_b.clear();
  mass_inv.clear();

  Real mass_data     = 0.0; 
  Real mass_inv_data = 0.0; 
  if( opt_inelastic == free_gas_mode )
  {
    mass_data     = nucl_data_obj.get_general_data_obj().get_mass();
    mass_inv_data = 1.0 / mass_data;
    Real sb_tmp   = (mass_data + 1.0) * mass_inv_data;
    sb_tmp = sb_tmp * sb_tmp;
    sig_b.push_back(static_cast<Real8>(sb_tmp));
    mass_inv.push_back(static_cast<Real8>(mass_inv_data));
  }
  else
  {
    vector<Real> scat_law_coef = sab_data_obj.get_inelastic_scat_law_coef();
    int  i_max                 = static_cast<int>(scat_law_coef.size());
    Real sb_tmp                = 0.0;
    Real atom_no_inv           = 1.0 / static_cast<Real>(atom_no);
    if( i_max >= 5 )
    {
      mass_data     = scat_law_coef[2];
      mass_inv_data = 1.0 / mass_data;
      sb_tmp        = (mass_data + 1.0) * mass_inv_data;
      sb_tmp        = scat_law_coef[0] * sb_tmp * sb_tmp * atom_no_inv;
      sig_b.push_back(static_cast<Real8>(sb_tmp));
      mass_inv.push_back(static_cast<Real8>(mass_inv_data));

      if( atom_no != static_cast<Integer>(round(scat_law_coef[5])) )
      {
        string class_name = "IncoherentInelasticScatterCalculator";
        string func_name  = "calc_bound_scattering_xs()";

        ostringstream oss01, oss02;
        oss01 << atom_no;
        oss02 << static_cast<Integer>(scat_law_coef[5]);
        string str_data01 = "Principal atom number from input file        : " + oss01.str();
        string str_data02 = "(principal_atom_no or natom for thermr)";
        string str_data03 = "Principal atom number from nuclear data file : " + oss02.str();
        string str_data04 = "(B(4)=M0 of MF=7/MT=4 in the ENDF-6 format)";

        vector<string> err_com;
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back(str_data04);
        err_com.push_back("");
        err_com.push_back("The principal atom number from the input file is different to that from the nuclear data file.");
        err_com.push_back("The principal atom number may be incorrect.");
        err_com.push_back("Please check the principal atom number.");
        err_obj.output_caution(class_name, func_name, err_com);
      }
  
      int j=6;
      atom_no_inv = atom_no_inv * scat_law_coef[5];
      while( i_max >= j+5 )
      {
        if( fabs(scat_law_coef[j])  < min_value && fabs(scat_law_coef[j+2]) > min_value )
        {
          mass_data     = scat_law_coef[j+2];
          mass_inv_data = 1.0 / mass_data;
          sb_tmp        = (mass_data + 1.0) * mass_inv_data;
          sb_tmp = scat_law_coef[j+1] * sb_tmp * sb_tmp * atom_no_inv / scat_law_coef[j+5];
          sig_b.push_back(static_cast<Real8>(sb_tmp));
          mass_inv.push_back(static_cast<Real8>(mass_inv_data));

          if( static_cast<int>(scat_law_coef.size()) >= j+9 )
          {
            if( fabs(scat_law_coef[j+6])  < min_value && fabs(scat_law_coef[j+8]) > min_value )
            {
              string class_name = "IncoherentInelasticScatterCalculator";
              string func_name  = "calc_bound_scattering_xs()";

              vector<string> err_com;
              err_com.push_back("This nuclear data contains multiple SCT approximation data.");
              err_com.push_back("The SCT approximation only 2 set atoms.");
              err_com.push_back("(principal and one non-principal atom)");
              err_com.push_back("Please check the nuclear data.");
              err_obj.output_runtime_error(class_name, func_name, err_com);
            }
          }
        }
        j+=6;
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void IncoherentInelasticScatterCalculator::comp_scat_xs_tot()
{
  CrossSectionDataContainer xs_data_obj
                               = nucl_data_obj.get_nucl_reaction_data_obj().get_xs_data_obj(xs_type_elastic);
  vector<Integer> int_vec_sc   = xs_data_obj.get_xs_int_data();
  vector<Integer> range_vec_sc = xs_data_obj.get_xs_range_data();
  vector<Real>    ene_vec_sc   = xs_data_obj.get_xs_ene_data();
  vector<Real>    xs_vec_sc    = xs_data_obj.get_xs_data();
  if( static_cast<int>(xs_vec_sc.size()) == 0 )
  {
    string class_name = "IncoherentInelasticScatterCalculator";
    string func_name  = "comp_scat_xs_tot()";

    vector<string> err_com;
    err_com.push_back("Elastic scattring cross section data is not found.");
    err_com.push_back("Comparison of the elastic scattering cross section and incoherent inelastic");
    err_com.push_back("scattering cross section is skipped.");
    err_obj.output_caution(class_name, func_name, err_com);

    return;
  }

  int i_max  = static_cast<int>(ene_grid.size());
  int ele_no = 0;
  for(int i=i_max-1; i>=0; i--)
  {
    if( scat_xs_tot[i] > min_sig_val * 1.1 )
    {
      ele_no = i;
      break;
    } 
  }

  Real8 xs_sc  = 0.0;
  Real8 ene_sc = ene_grid[ele_no];
  ti_obj.interpolation_tab1(ene_sc, xs_sc, range_vec_sc, int_vec_sc, ene_vec_sc, xs_vec_sc);

  Real8 dif_rela = fabs((xs_sc - scat_xs_tot[ele_no])/scat_xs_tot[ele_no]);
  if( dif_rela > 0.1 )
  {
    string class_name = "IncoherentInelasticScatterCalculator";
    string func_name  = "comp_scat_xs_tot()";

    vector<string> err_com;
    err_com.push_back("The difference between elastic scattering cross section from ENDF file");
    err_com.push_back("and incoherent inelastic scattering cross section from S(a,b) data at");
    err_com.push_back("the miximum energy of incoherent inelastic scattering is larger than 10%.");
    err_com.push_back("The input option (principal_atom_no or natom for thermr) or nuclear data");
    err_com.push_back("may be incorrect.");
    err_com.push_back("");

    ostringstream oss01, oss02, oss03, oss04, oss05;
    oss01.precision(8);
    oss01.setf(ios::showpoint);
    oss01.setf(ios::scientific);
    oss02.precision(8);
    oss02.setf(ios::showpoint);
    oss02.setf(ios::scientific);
    oss03.precision(8);
    oss03.setf(ios::showpoint);
    oss03.setf(ios::scientific);
    oss04.precision(8);
    oss04.setf(ios::showpoint);
    oss04.setf(ios::scientific);
    oss05.precision(8);
    oss05.setf(ios::showpoint);
    oss05.setf(ios::scientific);

    oss01 << ene_sc;
    oss02 << scat_xs_tot[ele_no];
    oss03 << xs_sc;
    oss04 << dif_rela;
    oss05 << xs_sc / scat_xs_tot[ele_no];

    string str_data01 = "  Maximum energy of incoherent inelastic scattering : " + oss01.str();
    string str_data02 = "  Incoherent inelastic scattering cross section     : " + oss02.str();
    string str_data03 = "  Elastic scattering cross section from ENDF file   : " + oss03.str();
    string str_data04 = "  Relative difference of scattering cross section   : " + oss04.str();
    string str_data05 = "  Incoherent inelastic scat XS / Elastic scat XS    : " + oss05.str();
    
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back(str_data05);
    err_obj.output_caution(class_name, func_name, err_com);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void IncoherentInelasticScatterCalculator::set_energy_grid()
{
  CrossSectionDataContainer xs_data_obj
                              = nucl_data_obj.get_nucl_reaction_data_obj().get_xs_data_obj(xs_type_elastic);
  vector<Real> ene_grid_xs    = xs_data_obj.get_xs_ene_data();
  vector<Real> ene_grid_ref   = ene_grid_xs;
  if( ene_grid_flg == linearize_ene_grid )
  {
    //NJOY/THERMR energy grid data is used for the initial energy grid of the liniarization.
    ene_grid_ref = ene_in_incoherent_inelastic;
  }

  if( opt_inelastic != free_gas_mode && ene_grid_flg != linearize_ene_grid )
  {
    vector<Real> ene_grid_elastic;
    ene_grid_elastic = sab_data_obj.get_coherent_elastic_ene_grid();
    merge_energy_grid(ene_grid_ref, ene_grid_elastic);

    ene_grid_elastic = sab_data_obj.get_incoherent_elastic_ene_grid();
    merge_energy_grid(ene_grid_ref, ene_grid_elastic);
  }

  vector<Real> ene_grid_inelastic;
  ene_grid_inelastic = ene_in_incoherent_inelastic;
  ene_grid_inelastic.push_back(digit_obj.get_adjusted_value(ene_max, sig_fig-2, -1.0));
  ene_grid_inelastic.push_back(ene_max);
  merge_energy_grid(ene_grid_ref, ene_grid_inelastic);
  

  ene_grid.clear();
  int  i_max    = static_cast<int>(ene_grid_ref.size());
  Real ene_top  = static_cast<Real>(ene_max + min_ene_dif);
  for(int i=0; i<i_max; i++)
  {
    if( ene_grid_ref[i] < ene_top ) 
    {
      ene_grid.push_back(ene_grid_ref[i]);
    }
    else
    {
      break;
    }
  }

  i_max = static_cast<int>(ene_grid.size());
  if( xs_type_elastic != xs_data_obj.get_reaction_type() || i_max == 0 )
  {
    string class_name = "IncoherentInelasticScatterCalculator";
    string func_name  = "set_energy_grid()";
  
    ostringstream oss01, oss02;
    vector<string> err_com;
    if( xs_type_elastic != xs_data_obj.get_reaction_type() )
    {
      oss01 << xs_type_elastic;
      oss02 << xs_data_obj.get_reaction_type();
      string str_data01 = "Reaction type whch is needed in this program : " + oss01.str();
      string str_data02 = "Reaction type in the nuclear data            : " + oss02.str();
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back("There are no reaction type which is needed in this program.");
    }
    else
    {
      oss01 << i_max;
      string str_data01 = "The size of energy grid : " + oss01.str();
      err_com.push_back(str_data01);
    }
    err_com.push_back("Please check the nuclear data.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
  xs_data_obj.clear();

  //Add ene_top and ene_add_p
  ene_top = ene_grid_xs[static_cast<int>(ene_grid_xs.size()) - 1];
  if( ene_top > ene_grid[i_max-1] + min_ene_dif )
  {
    Real ene_add_p = digit_obj.get_adjusted_value(ene_max, sig_fig-2, +1.0);
    if( ene_top > ene_add_p + min_ene_dif )
    {
      ene_grid.push_back(ene_add_p);
      ene_grid.push_back(ene_top);
    }
    else
    {
      ene_grid.push_back(ene_top);
    }
  }
  ene_grid_ref.clear();

  //Set minimum value of ene_grid
  //ene_out_min = ene_grid[0];
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void IncoherentInelasticScatterCalculator::merge_energy_grid(vector<Real>& ene_grid_base,
                                                             vector<Real>& ene_grid_add)
{
  //Merge ene_grid_base and ene_grid_add
  int i_max = static_cast<int>(ene_grid_add.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      ene_grid_base.push_back(ene_grid_add[i]);
    }
  }
  ene_grid_add.clear();

  //Delete overlap grid
  vector<Real> sorted_data;
  sorted_data.clear();
  i_max = static_cast<int>(ene_grid_base.size());
  if( i_max > 0 )
  {
    sort(ene_grid_base.begin(), ene_grid_base.end());

    int ele_no = 0;
    Real8 ene_pre, ene_cur;
    for(int i=0; i<i_max; i++)
    {
      ene_pre = ene_grid_base[ele_no];
      if( ene_pre > min_ene_val )
      {
        sorted_data.push_back(ene_pre);
        break;
      }
      ele_no++;
    }

    for(int i=ele_no; i<i_max; i++)
    {
      ene_cur = ene_grid_base[i];
      if( ene_cur - ene_pre > ene_pre*min_ene_dif )
      {
        sorted_data.push_back(ene_cur);
        ene_pre = ene_cur;
      }
    }
    ene_grid_base = sorted_data;
    sorted_data.clear();
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void IncoherentInelasticScatterCalculator::calc_scat_xs_tot_with_free_gas_mode
                                             (NuclearDataObject& data_obj, 
                                              vector<Real>& ein_vec, vector<Real>& xs_vec_tot)
{
  ein_vec   = ene_in_incoherent_inelastic;
  int i_max = static_cast<int>(ein_vec.size());
  xs_vec_tot.clear();
  xs_vec_tot.resize(i_max);

  int  opt_inela_val = free_gas_mode;
  int  bin_no_val    = 10;
  int  atom_no_val   =  1;
  Real temp_val      = data_obj.get_general_data_obj().get_temp();
  Real err_val       = data_obj.get_general_data_obj().get_error_value();
  Real ene_max_val   = ein_vec[i_max-1];

  set_nucl_data_obj(data_obj);
  set_opt_inelastic(opt_inela_val);
  set_bin_no(bin_no_val);
  set_err(err_val);
  set_ene_max(ene_max_val);

  set_temp(temp_val);
  set_atom_no(atom_no_val);

  preparation_for_incoherent_inerastic_scatter();

  for(int i=0; i<i_max; i++)
  {
    vector<Real>          eout_vec, xs_vec_eout;
    vector<vector<Real> > mu_vec, xs_vec_mu, mu_vec_int, xs_vec_mu_int;
    linearize_incoherent_inelastic_scatter_e_out
      ( ein_vec[i], eout_vec, xs_vec_eout, mu_vec, xs_vec_mu, mu_vec_int, xs_vec_mu_int);

    xs_vec_tot[i] = 0.0;
    calc_scat_xs_tot(xs_vec_tot[i], xs_vec_eout, eout_vec);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//Setter

void IncoherentInelasticScatterCalculator::set_ene_grid_flg(int int_val)
{
  calc_incoherent_inelastic_scat_flg = 0;

  if( int_val != use_nucl_ene_grid && int_val != linearize_ene_grid )
  {
    string class_name = "IncoherentInelasticScatterCalculator";
    string func_name  = "set_ene_grid_flg(int int_val)";

    vector<string> err_com;
    string str_data = "ene_grid_flg : " + int_val;
    err_com.push_back(str_data);
    err_com.push_back("This ene_grid_flg value is not available.");
    err_com.push_back("");
    err_com.push_back("Available ene_grid_flg value is as follows:");
    err_com.push_back("  use_nucl_ene_grid  : 1");
    err_com.push_back("  linearize_ene_grid : 2");
    err_com.push_back("Please modify the source file.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  ene_grid_flg = int_val;
}

void IncoherentInelasticScatterCalculator::set_nucl_data_obj(NuclearDataObject& data_obj)
{
  calc_incoherent_inelastic_scat_flg = 0;
  nucl_data_obj = data_obj;
  sab_data_obj  = data_obj.get_thermal_scat_data_obj();
}

void IncoherentInelasticScatterCalculator::set_opt_inelastic(Integer& int_data)
{
  calc_incoherent_inelastic_scat_flg = 0;
  opt_inelastic = int_data;
}

void IncoherentInelasticScatterCalculator::set_bin_no(Integer& int_data)
{
  bin_no      = int_data;
  bin_no_int  = static_cast<int>(bin_no);
  bin_no_real = static_cast<Real8>(bin_no);
  bin_no_inv  = 1.0 / bin_no_real;
}

void IncoherentInelasticScatterCalculator::set_atom_no(Integer& int_data)
{
  calc_incoherent_inelastic_scat_flg = 0;
  atom_no = int_data;
}

void IncoherentInelasticScatterCalculator::set_err(Real8& real_data)
{
  err      = real_data;
  err_half = err*0.5;
  err_int  = err*0.00005;
}

void IncoherentInelasticScatterCalculator::set_ene_max(Real8& real_data)
{
  calc_incoherent_inelastic_scat_flg = 0;
  ene_max = real_data;
}

void IncoherentInelasticScatterCalculator::set_temp(Real8& real_data)
{
  calc_incoherent_inelastic_scat_flg = 0;
  temp_inp = real_data;

  set_temp_tsl_ev(temp_inp);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//Getter
int IncoherentInelasticScatterCalculator::get_ene_grid_flg()
{
  return ene_grid_flg;
}

NuclearDataObject IncoherentInelasticScatterCalculator::get_nucl_data_obj()
{
  calc_incoherent_inelastic_scatter();

  sab_data_obj.set_incoherent_inelastic_ene_grid(ene_grid_prod_distr);
  sab_data_obj.set_incoherent_inelastic_ene_grid_scat_xs_tot(ene_grid);
  sab_data_obj.set_incoherent_inelastic_scat_xs_tot(scat_xs_tot);
  sab_data_obj.set_incoherent_inelastic_second_ene_grid(second_ene_grid);
  sab_data_obj.set_incoherent_inelastic_scat_xs_tot_second_ene(scat_xs_tot_second_ene);
  sab_data_obj.set_incoherent_inelastic_scat_angle(scat_angle);
  sab_data_obj.set_incoherent_inelastic_scat_xs(scat_xs);
  sab_data_obj.set_incoherent_inelastic_integrated_scat_angle(integrated_scat_angle);
  sab_data_obj.set_incoherent_inelastic_integrated_scat_xs(integrated_scat_xs);
  nucl_data_obj.set_thermal_scat_data_obj(sab_data_obj);

  GeneralDataContainer general_data_obj = nucl_data_obj.get_general_data_obj();
  general_data_obj.set_temp(temp_inp);
  general_data_obj.set_error_value(err);
  nucl_data_obj.set_general_data_obj(general_data_obj);
  general_data_obj.clear();

  return nucl_data_obj;
}

Integer IncoherentInelasticScatterCalculator::get_opt_inelastic()
{
  return opt_inelastic;
}

Integer IncoherentInelasticScatterCalculator::get_bin_no()
{
  return bin_no;
}

Integer IncoherentInelasticScatterCalculator::get_atom_no()
{
  return atom_no;
}

Real8 IncoherentInelasticScatterCalculator::get_err()
{
  return err;
}

Real8 IncoherentInelasticScatterCalculator::get_ene_max()
{
  return ene_max;
}

Real8 IncoherentInelasticScatterCalculator::get_temp()
{
  return temp_inp;
}

