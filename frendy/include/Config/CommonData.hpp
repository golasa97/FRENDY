#ifndef COMMON_DATA_H
#define COMMON_DATA_H

#include "FrendyTypes.hpp"

namespace frendy
{
  static const Integer default_data_width = 11;
  static const Integer sig_fig = 7; //number of significant figures

  static const Integer unassigned_data_val = -99999;
  static const Integer unassigned_mat_no   = -99999;
  static const Integer unassigned_mt_no    = -99999;

  static const Real8 min_value    = 1.0e-60;
  static const Real8 min_sig_dif  = 1.0e-30;
  static const Real8 min_ene_dif  = 1.0e-10;

  static const Real8 min_ene_val  = 1.0e-15;
  static const Real8 min_sig_val  = 1.0e-40;

  static const int   total_xs     = 0;
  static const int   scatter_xs   = 1;
  static const int   fission_xs   = 2;
  static const int   radiation_xs = 3;
  static const int   xs_type_no   = 4; //total, scatter, fission and radiation

  static const Real8 boltzmann_const = 8.617333262145e-5; //[eV/K]
  static const Real8 amu_n           = 1.008664904; //mass of neutron[u]
  static const Real8 amu             = 1.660538921e-24; //unified atomic mass unit[u] (NJOY:1.6605402e-24)
  static const Real8 h_bar           = 1.054571726e-27; //h/2*pi[erg s] (NJOY:1.05457266e-27)
  static const Real8 ev              = 1.602176634e-12; //electron vold[erg] (NJOY:1.60217733e-12)

  static const Real8 light_speed     = 2.99792458E+8; //[m/s]

  static const Real8 unit_mega       = 1.0E+6;
  static const Real8 unit_kilo       = 1.0E+3;
  static const Real8 unit_mili       = 1.0E-3;
  static const Real8 unit_micro      = 1.0E-6;

  static const Real8 dop_ene_max_def       = 1.0e6;  //The default value of max doppler energy
  static const Real8 integral_range_dop    = 4.0;    //Integral range for doppler broadening calculation
  static const Real8 tayler_calc_condition = 1.0e-10;
  static const Real8 min_tayler_val        = 1.0e-30;

  static const Real8 conv_th_ene           = 0.0253; //conventional thermal energy is 0.0253[eV]

  static const Integer int_const      = 1; //For identification of interpolation scheme
  static const Integer int_lin_lin    = 2;
  static const Integer int_log_lin    = 3;
  static const Integer int_lin_log    = 4;
  static const Integer int_log_log    = 5;
  static const Integer int_special_1d = 6;

  //For EndfUtils/GendfParser/GendfInterpolator.cpp
  static const Integer int_quadratic  = 1001;     //Quadratic interpolation
  static const Integer int_monotone_cubic = 1002; //Monotone cubic interpolation

  //MT number list
  static const Integer mt_p_min_endf6   = 600;
  static const Integer mt_p_max_endf6   = 649;
  static const Integer mt_d_min_endf6   = 650;
  static const Integer mt_d_max_endf6   = 699;
  static const Integer mt_t_min_endf6   = 700;
  static const Integer mt_t_max_endf6   = 749;
  static const Integer mt_he3_min_endf6 = 750;
  static const Integer mt_he3_max_endf6 = 799;
  static const Integer mt_a_min_endf6   = 800;
  static const Integer mt_a_max_endf6   = 849;
  static const Integer mt_n2n_min_endf6 = 875;
  static const Integer mt_n2n_max_endf6 = 891;

  static const Integer mt_p_min_endf5   = 700;
  static const Integer mt_p_max_endf5   = 719;
  static const Integer mt_d_min_endf5   = 720;
  static const Integer mt_d_max_endf5   = 739;
  static const Integer mt_t_min_endf5   = 740;
  static const Integer mt_t_max_endf5   = 759;
  static const Integer mt_he3_min_endf5 = 760;
  static const Integer mt_he3_max_endf5 = 779;
  static const Integer mt_a_min_endf5   = 780;
  static const Integer mt_a_max_endf5   = 799;
  static const Integer mt_n2n_min_endf5 =   6;
  static const Integer mt_n2n_max_endf5 =   9;
}

#endif // COMMON_DATA_H
