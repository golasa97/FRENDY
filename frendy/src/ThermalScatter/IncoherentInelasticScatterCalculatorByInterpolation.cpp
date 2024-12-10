#include "ThermalScatter/IncoherentInelasticScatterCalculatorByInterpolation.hpp"

using namespace frendy;

//constructor
IncoherentInelasticScatterCalculatorByInterpolation::IncoherentInelasticScatterCalculatorByInterpolation(void)
{
  lagrange_interpolation_flg = interpolation_mode;
  
  ene_base.resize(118);
  ene_base[  0] = 1.000000000E-05;
  ene_base[  1] = 1.780000000E-05;
  ene_base[  2] = 2.500000000E-05;
  ene_base[  3] = 3.500000000E-05;
  ene_base[  4] = 5.000000000E-05;
  ene_base[  5] = 7.000000000E-05;
  ene_base[  6] = 1.000000000E-04;
  ene_base[  7] = 1.260000000E-04;
  ene_base[  8] = 1.600000000E-04;
  ene_base[  9] = 2.000000000E-04;
  ene_base[ 10] = 2.530000000E-04;
  ene_base[ 11] = 2.970000000E-04;
  ene_base[ 12] = 3.500000000E-04;
  ene_base[ 13] = 4.200000000E-04;
  ene_base[ 14] = 5.060000000E-04;
  ene_base[ 15] = 6.150000000E-04;
  ene_base[ 16] = 7.500000000E-04;
  ene_base[ 17] = 8.700000000E-04;
  ene_base[ 18] = 1.012000000E-03;
  ene_base[ 19] = 1.230000000E-03;
  ene_base[ 20] = 1.500000000E-03;
  ene_base[ 21] = 1.800000000E-03;
  ene_base[ 22] = 2.030000000E-03;
  ene_base[ 23] = 2.277000000E-03;
  ene_base[ 24] = 2.600000000E-03;
  ene_base[ 25] = 3.000000000E-03;
  ene_base[ 26] = 3.500000000E-03;
  ene_base[ 27] = 4.048000000E-03;
  ene_base[ 28] = 4.500000000E-03;
  ene_base[ 29] = 5.000000000E-03;
  ene_base[ 30] = 5.600000000E-03;
  ene_base[ 31] = 6.325000000E-03;
  ene_base[ 32] = 7.200000000E-03;
  ene_base[ 33] = 8.100000000E-03;
  ene_base[ 34] = 9.108000000E-03;
  ene_base[ 35] = 1.000000000E-02;
  ene_base[ 36] = 1.063000000E-02;
  ene_base[ 37] = 1.150000000E-02;
  ene_base[ 38] = 1.239700000E-02;
  ene_base[ 39] = 1.330000000E-02;
  ene_base[ 40] = 1.417000000E-02;
  ene_base[ 41] = 1.500000000E-02;
  ene_base[ 42] = 1.619200000E-02;
  ene_base[ 43] = 1.820000000E-02;
  ene_base[ 44] = 1.990000000E-02;
  ene_base[ 45] = 2.049300000E-02;
  ene_base[ 46] = 2.150000000E-02;
  ene_base[ 47] = 2.280000000E-02;
  ene_base[ 48] = 2.530000000E-02;
  ene_base[ 49] = 2.800000000E-02;
  ene_base[ 50] = 3.061300000E-02;
  ene_base[ 51] = 3.380000000E-02;
  ene_base[ 52] = 3.650000000E-02;
  ene_base[ 53] = 3.950000000E-02;
  ene_base[ 54] = 4.275700000E-02;
  ene_base[ 55] = 4.650000000E-02;
  ene_base[ 56] = 5.000000000E-02;
  ene_base[ 57] = 5.692500000E-02;
  ene_base[ 58] = 6.250000000E-02;
  ene_base[ 59] = 6.900000000E-02;
  ene_base[ 60] = 7.500000000E-02;
  ene_base[ 61] = 8.197200000E-02;
  ene_base[ 62] = 9.000000000E-02;
  ene_base[ 63] = 9.600000000E-02;
  ene_base[ 64] = 1.035000000E-01;
  ene_base[ 65] = 1.115730000E-01;
  ene_base[ 66] = 1.200000000E-01;
  ene_base[ 67] = 1.280000000E-01;
  ene_base[ 68] = 1.355000000E-01;
  ene_base[ 69] = 1.457280000E-01;
  ene_base[ 70] = 1.600000000E-01;
  ene_base[ 71] = 1.720000000E-01;
  ene_base[ 72] = 1.844370000E-01;
  ene_base[ 73] = 2.000000000E-01;
  ene_base[ 74] = 2.277000000E-01;
  ene_base[ 75] = 2.510390000E-01;
  ene_base[ 76] = 2.705300000E-01;
  ene_base[ 77] = 2.907500000E-01;
  ene_base[ 78] = 3.011330000E-01;
  ene_base[ 79] = 3.206420000E-01;
  ene_base[ 80] = 3.576810000E-01;
  ene_base[ 81] = 3.900000000E-01;
  ene_base[ 82] = 4.170350000E-01;
  ene_base[ 83] = 4.500000000E-01;
  ene_base[ 84] = 5.032580000E-01;
  ene_base[ 85] = 5.600000000E-01;
  ene_base[ 86] = 6.250000000E-01;
  ene_base[ 87] = 7.000000000E-01;
  ene_base[ 88] = 7.800000000E-01;
  ene_base[ 89] = 8.600000000E-01;
  ene_base[ 90] = 9.500000000E-01;
  ene_base[ 91] = 1.050000000E+00;
  ene_base[ 92] = 1.160000000E+00;
  ene_base[ 93] = 1.280000000E+00;
  ene_base[ 94] = 1.420000000E+00;
  ene_base[ 95] = 1.550000000E+00;
  ene_base[ 96] = 1.700000000E+00;
  ene_base[ 97] = 1.855000000E+00;
  ene_base[ 98] = 2.020000000E+00;
  ene_base[ 99] = 2.180000000E+00;
  ene_base[100] = 2.360000000E+00;
  ene_base[101] = 2.590000000E+00;
  ene_base[102] = 2.855000000E+00;
  ene_base[103] = 3.120000000E+00;
  ene_base[104] = 3.420000000E+00;
  ene_base[105] = 3.750000000E+00;
  ene_base[106] = 4.070000000E+00;
  ene_base[107] = 4.460000000E+00;
  ene_base[108] = 4.900000000E+00;
  ene_base[109] = 5.350000000E+00;
  ene_base[110] = 5.850000000E+00;
  ene_base[111] = 6.400000000E+00;
  ene_base[112] = 7.000000000E+00;
  ene_base[113] = 7.650000000E+00;
  ene_base[114] = 8.400000000E+00;
  ene_base[115] = 9.150000000E+00;
  ene_base[116] = 9.850000000E+01;
  ene_base[117] = 1.000000000E+01;
}

//destructor
IncoherentInelasticScatterCalculatorByInterpolation::~IncoherentInelasticScatterCalculatorByInterpolation(void)
{
  ene_base.clear();
  ene_grid_scat_xs_tot.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void IncoherentInelasticScatterCalculatorByInterpolation::calc_incoherent_inelastic_scatter()
{
  if( opt_inelastic == no_calc )
  {
    return;
  }

  if( calc_incoherent_inelastic_scat_flg == 0 )
  {
    preparation_for_incoherent_inerastic_scatter();

    //Additional preparation for this subclass
    IncoherentInelasticScatterCalculator::set_energy_grid();
    ene_grid_scat_xs_tot = ene_grid;
    set_energy_grid();
  }

  calc_scat_xs();

  if( opt_inelastic != free_gas_mode )
  {
    calc_scat_xs_tot_by_lagrange_interpolation();
  }
  else
  {
    modify_scat_xs_tot(ene_grid_scat_xs_tot, scat_xs_tot);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void IncoherentInelasticScatterCalculatorByInterpolation::calc_scat_xs_tot_by_lagrange_interpolation()
{
  vector<Real8> scat_xs_tot_mod;

  int i_max = static_cast<int>(ene_grid_scat_xs_tot.size());
  scat_xs_tot_mod.resize(i_max);

  Integer order   = lagrange_order;
  Real    ene_top = static_cast<Real>(ene_max + min_ene_dif);
  for(int i=0; i<i_max; i++)
  {
    if( ene_grid_scat_xs_tot[i] > ene_top )
    {
      scat_xs_tot_mod[i] = 0.0;
    }
    else
    {
      scat_xs_tot_mod[i] = math_obj.lagrange_interpolation(ene_grid_scat_xs_tot[i],order,ene_grid,scat_xs_tot);
    }
  }

  scat_xs_tot = scat_xs_tot_mod;
  scat_xs_tot_mod.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void IncoherentInelasticScatterCalculatorByInterpolation::set_energy_grid()
{
  ene_grid.clear();
  Real ene_top = static_cast<Real>(ene_max + min_ene_dif);
  for(int i=0; i<static_cast<int>(ene_base.size()); i++)
  {
    ene_grid.push_back(ene_base[i]);
    if( ene_base[i] > ene_top ) 
    {
      break;
    }
  }

  if( temp_inp > 3000.0 )
  {
    Real8 ene_min     = ene_grid[0];
    Real8 coef1       = -1.0 * log(ene_min);
    Real8 coef2       = coef1 + log(temp_tsl_ev*conv_th_ene_inv);
    Real8 coef3       = 1.0 / (coef1 + log(ene_max));
    for(int i=1; i<static_cast<int>(ene_grid.size()); i++)
    {
      Real8 ene_log = log(ene_grid[i]);
      ene_grid[i]  = ene_min * exp((ene_log+coef1) * (ene_log+coef2) * coef3);
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

NuclearDataObject IncoherentInelasticScatterCalculatorByInterpolation::get_nucl_data_obj()
{
  calc_incoherent_inelastic_scatter();

  sab_data_obj.set_incoherent_inelastic_ene_grid(ene_grid);
  sab_data_obj.set_incoherent_inelastic_ene_grid_scat_xs_tot(ene_grid_scat_xs_tot);
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

