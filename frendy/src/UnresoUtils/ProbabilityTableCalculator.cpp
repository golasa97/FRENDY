#include "UnresoUtils/ProbabilityTableCalculator.hpp"

using namespace frendy;

//Initialize static const value
const Real8 ProbabilityTableCalculator::level_spacing_min_ini   = 100000.0;
const Real8 ProbabilityTableCalculator::ene_range_ini           = 900.0;
const Real8 ProbabilityTableCalculator::ene_low_ini             = 10.0;
const Real8 ProbabilityTableCalculator::cumulative_distr_cauchy = 31.83;
const Real8 ProbabilityTableCalculator::adjust_scat_xs_val      = 1.0E-6;
const Real8 ProbabilityTableCalculator::max_unreso_ene          = 1.0E+8;
const Real8 ProbabilityTableCalculator::min_xs_coef             = 1.0E-2;
const Real8 ProbabilityTableCalculator::min_temp_value          = 1.0E-10;

int ProbabilityTableCalculator::time_print_opt = no_print_time_data;

//constructor
ProbabilityTableCalculator::ProbabilityTableCalculator(void)
{
  clear();

  pi          = M_PI;
  pi_sq       = pi*pi;
  pi_root     = sqrt(pi);
  pi_root_inv = 1.0 / pi_root;

  temp_ref = 300.0;
  third    = 1.0/3.0;
  k_part   = (sqrt(2.0*amu_n*amu*ev)*1.0e-12)/h_bar;

  if( fabs(temp_ref) > min_ene_val )
  {
    coef_boltz = sqrt(0.25/(boltzmann_const*fabs(temp_ref)));
  }
  else
  {
    coef_boltz = sqrt(0.25/boltzmann_const);
  }

  set_base_data();
}

//destructor
ProbabilityTableCalculator::~ProbabilityTableCalculator(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::set_base_data()
{
  if( random_seed >= 0 )
  {
    rand_obj.set_seed(random_seed);
  }
  else
  {
    rand_obj.set_seed_time();
  }

  sample_no_real     = static_cast<Real8>(sample_no);
  sample_no_real_inv = 1.0 / sample_no_real;

  bin_no_int  = static_cast<int>(bin_no);
  bin_no_skip = static_cast<int>(sample_no / (bin_no_int - 8.24));
  bin_no_sta  = static_cast<int>(bin_no_skip / 200);

  ene_grid_no_int = static_cast<int>(ene_grid_no);
  if( ene_grid_no > 1 )
  {
    ene_grid_no_int--;
  } 

  ladder_no_int = static_cast<int>(ladder_no);
  ladder_no_inv = 1.0 / static_cast<Real8>(ladder_no);

  temp_no_int = static_cast<int>(temp_data.size());
  if( temp_no_int > 0 )
  {
    temp_no_inv = 1.0 / static_cast<Real8>(temp_no_int);
  }
  else
  {
    temp_no_inv = 0.0;
  }

  sig_zero_no_int = static_cast<int>(sig_zero_data.size());

  bin_no_add.resize(bin_no_int);
  for(int i=0; i<bin_no_int; i++)
  {
    bin_no_add[i] = bin_no_skip;
  }
  if( bin_no_int > 7 )
  {
    bin_no_add[0]            /= 40;
    bin_no_add[1]            /= 10;
    bin_no_add[2]            /=  4;
    bin_no_add[3]            /=  2;
    bin_no_add[bin_no_int-6] /=  2;
    bin_no_add[bin_no_int-5] /=  4;
    bin_no_add[bin_no_int-4] /= 10;
    bin_no_add[bin_no_int-3] /= 40;
  }

  //For equal probability bins
  //bin_no_skip = static_cast<int>(sample_no / bin_no_int);
  //bin_no_sta  = bin_no_skip;
  //for(int i=0; i<bin_no_int; i++)
  //{
  //  bin_no_add[i] = bin_no_skip;
  //}
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::clear()
{
  inela_comp_flg = 0;
  abs_comp_flg   = 0;
  comp_flg       = 0;

  sample_no   = sample_no_ini;
  random_seed = random_seed_ini;
  bin_no      = bin_no_ini;

  reso_calc_obj.clear();
  math_obj.clear();

  nucl_data_obj.clear();
  prob_data_obj.clear();

  calc_prob_flg             = 0;
  nucl_data_set_flg         = 0;
  set_xs_tot_table_data_flg = 0;

  ladder_no          = 1;
  ladder_no_int      = 1;
  bin_no_int         = 0;
  bin_no_skip        = 0;
  bin_no_sta         = 0;
  ene_grid_no        = 0;
  ene_grid_no_int    = 0;
  temp_no_int        = 0;
  sig_zero_no_int    = 0;

  ladder_no_inv      = 0.0;
  temp_no_inv        = 0.0;

  static_err         = -1.0;

  bin_no_add.clear();

  temp_data.clear();
  sig_zero_data.clear();

  xs_tot_table_ene.clear();
  clr_obj.clear_vec_array3_real8(xs_tot_table_all);

  xs_potential_vec.clear();

  clear_unreso_data();
  clear_xs_data();
  clear_unreso_data_for_probability_table();
  clear_probability_table_parameter_each_ladder();
  clear_probability_table_parameter_all_ladder();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::clear_unreso_data()
{
  unreso_data_flg = 0;

  time_each_ene.clear();
  ene_grid_prob.clear();

  vector<vector<UnresolvedResonanceDataContainer> >().swap(unreso_data_obj);
  //for(int i=0; i<static_cast<int>(unreso_data_obj.size()); i++)
  //{
  //  for(int j=0; j<static_cast<int>(unreso_data_obj[i].size()); j++)
  //  {
  //    unreso_data_obj[i][j].clear();
  //  }
  //  unreso_data_obj[i].clear();
  //}
  //unreso_data_obj.clear();
  unreso_data_obj_each.clear();

  ene_grid_unreso.clear();

  fis_width_flg.clear();
  abundance.clear();

  unreso_int_data        = int_log_log;
  self_shielding_flg_ori = 0;

  xs_potential = 0.0;

  clr_obj.clear_vec_array2_int(xs_formula_flg);
  clr_obj.clear_vec_array2_int(scat_radius_ene_dependence_flg);
  clr_obj.clear_vec_array2_int(radius_calc_flg);
  clr_obj.clear_vec_array2_int(self_shielding_flg);

  clr_obj.clear_vec_array2_real8(reso_ene_low);
  clr_obj.clear_vec_array2_real8(reso_ene_high);
  clr_obj.clear_vec_array2_real8(spin_data);
  clr_obj.clear_vec_array2_real8(scat_radius);

  clr_obj.clear_vec_array3_int(scat_radius_tab_int_data);
  clr_obj.clear_vec_array3_int(scat_radius_tab_range_data);
  clr_obj.clear_vec_array3_int(l_value);
  clr_obj.clear_vec_array3_real8(scat_radius_tab_ene_data);
  clr_obj.clear_vec_array3_real8(scat_radius_tab_data);

  clr_obj.clear_vec_array3_real8(mass);
  clr_obj.clear_vec_array3_real8(wave_no_part);
  clr_obj.clear_vec_array3_real8(chan_rad);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::clear_xs_data()
{
  xs_skip.clear();
  xs_data_unreso.clear();
  xs_data_back.clear();

  clr_obj.clear_vec_array2_int(xs_int_data);
  clr_obj.clear_vec_array2_int(xs_range_data);
  clr_obj.clear_vec_array2_real8(xs_ene_data);
  clr_obj.clear_vec_array2_real8(xs_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::clear_unreso_data_for_probability_table()
{
  nrest             = 0;
  level_spacing_min = 0.0;
  level_spacing_inv = 0.0;

  clr_obj.clear_vec_array3_real8(coef_prob_table);
  clr_obj.clear_vec_array3_real8(cos2phi);
  clr_obj.clear_vec_array3_real8(sin2phi);

  clr_obj.clear_vec_array4_real8(coef_gamma);
  clr_obj.clear_vec_array4_real8(level_spacing);
  clr_obj.clear_vec_array4_real8(width_n);
  clr_obj.clear_vec_array4_real8(width_rad);
  clr_obj.clear_vec_array4_real8(width_fis);
  clr_obj.clear_vec_array4_real8(width_comp);
  clr_obj.clear_vec_array4_real8(width_tot);

  clr_obj.clear_vec_array4_int(freedom_n);
  clr_obj.clear_vec_array4_int(freedom_fis);
  clr_obj.clear_vec_array4_int(freedom_comp);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::clear_probability_table_parameter_all_ladder()
{
  ene_grid_each_ladder.clear();
  xs_inf.clear();
  clr_obj.clear_vec_array3_real8(xs_prob);

  xs_tot_min.clear();
  xs_tot_max.clear();
  clr_obj.clear_vec_array2_real8(xs_tot_table);

  clr_obj.clear_vec_array2_real8(xs_inf_ave);
  clr_obj.clear_vec_array2_real8(xs_inf_var);

  clr_obj.clear_vec_array2_int(prob_table_sample_no);
  clr_obj.clear_vec_array2_real8(prob_heat);
  clr_obj.clear_vec_array3_real8(prob_table);
  clr_obj.clear_vec_array3_real8(bondarenko_table);
  clr_obj.clear_vec_array3_real8(bondarenko_xs);
  clr_obj.clear_vec_array3_real8(bondarenko_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::clear_probability_table_parameter_each_ladder()
{
  ene_reso_loc_no_int = 0;
  cos2phi_prob        = 0.0;
  sin2phi_prob        = 0.0;
  coef_gamma_prob     = 0.0;

  ene_reso_loc.clear();
  width_tot_prob.clear();
  width_n_prob.clear();
  width_fis_prob.clear();
  width_comp_prob.clear();
  width_rad_prob.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::calc_probability_table()
{
  if( calc_prob_flg == 1 )
  {
    return;
  }
  calc_prob_flg = 1;

  set_base_data();
  check_set_data();

  //For unresolved resonance
  set_unreso_data();
  if( unreso_data_flg > 0 )
  {
    return;
  }

  ta_obj.delete_overlap_grid(ene_grid_unreso);
  int i_max = static_cast<int>(ene_grid_unreso.size());
  if( i_max <= 1 )
  {
    string class_name = "ProbabilityTableCalculator";
    string func_name  = "calc_probability_table()";

    vector<string> err_com;
    ostringstream  oss;
    oss << i_max;
    string str_data = "Number of energy grid in unresolved resonance region : " + oss.str();
    err_com.push_back(str_data);
    err_com.push_back("The number of energy grid is less than or equal to 1.");
    err_com.push_back("The nuclear data in unresolved resonance region may not be appropriate.");
    err_com.push_back("The calculation of probability table is skipped.");
    err_obj.output_caution(class_name, func_name, err_com);

    return;
  }

  //For back ground cross section
  set_xs_data();

  //Calculation of resonance cross section
  int ene_no_skip = 1;
  if( ene_grid_no_int > 0 )
  {
    ene_no_skip = i_max / ene_grid_no_int;
    i_max       = ene_grid_no_int + 1;
  }
  prob_data_obj.set_prob_table_ene_no(i_max); //For probability table
  time_each_ene.resize(i_max);
  ene_grid_prob.resize(i_max);
  xs_potential_vec.resize(i_max);
  set_unreso_data_for_probability_table();
  set_probability_table_parameter_all_ladder();

  vector<Real8> xs_residual;
  xs_residual.resize(xs_type_no);
  for(int i=0; i<xs_type_no; i++)
  {
    xs_residual[i] = 0.0;
  }

  DigitAdjuster digit_obj;
  int digit_no_i = digit_obj.get_digit_number(i_max) + 2;
  int digit_no_e = digit_obj.get_digit_number(ene_grid_unreso[i_max-1]) + 2;

  int xs_residual_flg = -1;

  int ele_no = 0;
  for(int i=0; i<i_max; i++)
  {
    boost::timer::cpu_timer timer_ene;
    ene_grid_prob[i] = ene_grid_unreso[ele_no];
    if( i > 0 )
    {
      if( ene_grid_prob[i] - ene_grid_prob[i-1] < 0.0 )
      {
        string class_name = "ProbabilityTableCalculator";
        string func_name  = "calc_probability_table()";

        vector<string> err_com;
        ostringstream  oss01, oss02, oss03, oss04, oss05, oss06;
        oss05.precision(8);
        oss05.setf(ios::scientific);
        oss05.setf(ios::showpoint);
        oss06.precision(8);
        oss06.setf(ios::scientific);
        oss06.setf(ios::showpoint);
        oss01 << i+1;
        oss02 << i_max;
        oss03 << ele_no+1;
        oss04 << static_cast<int>(ene_grid_unreso.size());
        oss05 << ene_grid_prob[i-1];
        oss06 << ene_grid_prob[i];
        string str_data01 = "Position (i)          : " + oss01.str() + " / " + oss02.str();
        string str_data02 = "Number of energy grid : " + oss03.str() + " / " + oss04.str();
        string str_data03 = "Energy [i] / [i-1]    : " + oss05.str() + " / " + oss06.str();
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back("The energy at i-1 is larger than i.");
        err_com.push_back("This energy grid is not appropriate.");
        err_obj.output_runtime_error(class_name, func_name, err_com);
      }
    }

    set_back_ground_xs_data(i);
    calc_unreso_xs(ene_grid_unreso[ele_no], xs_data_unreso);
    xs_potential_vec[i] = xs_potential;

    xs_residual[total_xs] = xs_data_back[total_xs] - xs_data_back[scatter_xs] - xs_data_back[fission_xs]
                                                   - xs_data_back[radiation_xs];
    if( xs_residual[total_xs] < 1.0E-5 )
    {
      xs_residual[total_xs] = 0.0;
    }
    else if( xs_residual_flg < 0 )
    {
      xs_residual_flg = i;
    }

    if( self_shielding_flg_ori > 0 ) //MF=3 contains the entire dilute cross section
    {                                //for the unresolved resonance region.
      calc_probability_and_bondarenko_table(i, xs_data_unreso, xs_residual);
    }
    else //File 3 contains partial back ground cross sections, to be added to
    {    //the average average unresolved cross section.
      calc_probability_and_bondarenko_table(i, xs_data_unreso, xs_data_back);
    }

    time_each_ene[i] = static_cast<Real>(timer_ene.elapsed().wall * 1.0E-9);
    if( time_print_opt == print_time_data )
    {
      int digit_no_t = digit_obj.get_digit_number(time_each_ene[i]) + 2;
      if( digit_no_t < digit_no_e )
      {
        digit_no_t = digit_no_e;
      }

      cout << "    Calculation time of energy ";
      cout << "(" << setw(digit_no_i) << ele_no+1 << "/" << setw(digit_no_i) << i_max << ") :"
           << setw(digit_no_e) << ene_grid_unreso[ele_no] << " [eV] :"
           << setw(digit_no_t) << time_each_ene[i] << " [s]" << endl;
    }
    ele_no += ene_no_skip;
  }
  cout << endl;
  xs_residual.clear();

  set_competition_flg(xs_residual_flg);

  clear_probability_table_parameter_all_ladder();

  //output_xs_potential_data();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::set_unreso_data()
{
  clear_unreso_data();

  ResonanceDataContainer   reso_data_obj   = nucl_data_obj.get_reso_data_obj();
  vector<vector<Integer> > reso_region_flg = reso_data_obj.get_reso_region_flg();

  int i_max = static_cast<int>(reso_region_flg.size());
  unreso_data_flg = 1;
  if( i_max == 0 )
  {
    unreso_data_flg = 10;
  }
  else if( static_cast<int>(reso_region_flg[0].size()) > 0 )
  {
    if( reso_region_flg[0][0] == 0 )
    {
      unreso_data_flg = 100;
    }
  }

  unreso_data_obj.resize(i_max);
  xs_formula_flg.resize(i_max);
  fis_width_flg.resize(i_max);
  scat_radius_ene_dependence_flg.resize(i_max);
  radius_calc_flg.resize(i_max);
  self_shielding_flg.resize(i_max);
  abundance.resize(i_max);
  reso_ene_low.resize(i_max);
  reso_ene_high.resize(i_max);
  spin_data.resize(i_max);
  scat_radius.resize(i_max);
  scat_radius_tab_int_data.resize(i_max);
  scat_radius_tab_range_data.resize(i_max);
  scat_radius_tab_ene_data.resize(i_max);
  scat_radius_tab_data.resize(i_max);
  mass.resize(i_max);
  l_value.resize(i_max);
  wave_no_part.resize(i_max);
  chan_rad.resize(i_max);

  vector<vector<vector<Real8> > > ene_grid_tmp;
  for(int i=0; i<i_max; i++)
  {
    int ele_no       = 0;
    fis_width_flg[i] = reso_data_obj.get_fis_width_flg()[i];
    abundance[i]     = reso_data_obj.get_abundance_isotope()[i];

    int j_max = static_cast<int>(reso_region_flg[i].size());
    for(int j=0; j<j_max; j++)
    {
      if( reso_region_flg[i][j] == 2 )
      {
        unreso_data_flg = 0;

        //Set parameters in unresolved resonance region
        set_unreso_parameter(i, j, reso_data_obj);

        //Set energy grid in unresolved resonance region
        set_unreso_ene_grid(unreso_data_obj[i][ele_no].get_ene_unreso(), i, j, reso_data_obj);

        ele_no++;
      }
    }
  }

  set_unreso_int_data(reso_region_flg);
  prob_data_obj.set_unreso_int_data(unreso_int_data);

  reso_data_obj.clear();
  clr_obj.clear_vec_array2_int(reso_region_flg);

  if( unreso_data_flg > 0 )
  {
    string class_name = "ProbabilityTableCalculator";
    string func_name  = "set_unreso_data()";

    vector<string> err_com;
    if( unreso_data_flg == 10 )
    {
      err_com.push_back("This material has no resonance data.");
    }
    else
    {
      if( unreso_data_flg == 100 )
      {
        err_com.push_back("The resonance data in this material is only the scattering radius.");
      }
      err_com.push_back("This material has no unresolved resonance data.");
    }
    err_com.push_back("The probability table calculation is skipped.");
    err_obj.output_caution(class_name, func_name, err_com);

    return;
  }
 
  check_self_shielding_flg();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::check_self_shielding_flg()
{
  int i_max = static_cast<int>(self_shielding_flg.size());
  if( i_max > 0 )
  {
    self_shielding_flg_ori = unassigned_data_val;
    for(int i=0; i<i_max; i++)
    {
      int j_max = static_cast<int>(self_shielding_flg[i].size());
      if( j_max > 0 )
      {
        if( self_shielding_flg_ori == unassigned_data_val )
        {
          self_shielding_flg_ori = self_shielding_flg[i][0];
        }

        for(int j=0; j<j_max; j++)
        {
          if( self_shielding_flg_ori != self_shielding_flg[i][j] )
          {
            string class_name = "ProbabilityTableCalculator";
            string func_name  = "check_self_shielding_flg()";

            ostringstream oss01, oss02, oss03, oss04, oss05, oss06;
            oss01 << i;
            oss02 << i_max;
            oss03 << j;
            oss04 << j_max;
            oss05 << self_shielding_flg_ori;
            oss06 << self_shielding_flg[i][j];
            string str_data01 = "i                           : " + oss01.str() + " / " + oss02.str();
            string str_data02 = "j                           : " + oss03.str() + " / " + oss04.str();
            string str_data03 = "First self shielding flag   : " + oss05.str();
            string str_data04 = "Current self shielding flag : " + oss06.str();

            vector<string> err_com;
            err_com.push_back("The self shielding flag is different in each unresolved resonance region.");
            err_com.push_back("The first self shielding flag is used for all unresolved resonance region.");
            err_com.push_back(str_data01);
            err_com.push_back(str_data02);
            err_com.push_back(str_data03);
            err_com.push_back(str_data04);
            err_obj.output_caution(class_name, func_name, err_com);
          }
        }
      }
    }
  }

  prob_data_obj.set_self_shielding_flg(self_shielding_flg_ori);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::set_unreso_int_data(vector<vector<Integer> >& reso_region_flg)
{
  unreso_int_data = int_log_log;

  int ele_no      = 0;
  int i_max       = static_cast<int>(reso_region_flg.size());
  vector<Integer> int_vec;
  vector<int>     pos_i, pos_j, pos_k, pos_l;
  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(reso_region_flg[i].size());
    for(int j=0; j<j_max; j++)
    {
      if( reso_region_flg[i][j] == 2 )
      {
        if( unreso_data_obj[i][ele_no].get_xs_formula_flg() == 2 )
        {
          vector<vector<Integer> > unreso_int_vec = unreso_data_obj[i][ele_no].get_unreso_int_data();
          int k_max = static_cast<int>(unreso_int_vec.size());
          for(int k=0; k<k_max; k++)
          {
            int l_max = static_cast<int>(unreso_int_vec[k].size());
            for(int l=0; l<l_max; l++)
            {
              int_vec.push_back(unreso_int_vec[k][l]);
              pos_i.push_back(i);
              pos_j.push_back(j);
              pos_k.push_back(k);
              pos_l.push_back(l);
            }
          }
        }
        ele_no++;
      }
    }
  }

  int data_no = static_cast<int>(int_vec.size());
  if( data_no == 0 )
  {
    return;
  }

  unreso_int_data = int_vec[0];

  //Check interpolation scheme
  vector<int> pos_data;
  for(int i=1; i<data_no; i++)
  {
    if( int_vec[0] != int_vec[i] )
    {
      pos_data.push_back(i);
    }
  }

  //Output caution when interpolation scheme is not identical in all energy region
  int pos_data_no = static_cast<int>(pos_data.size());
  if( pos_data_no > 0 )
  {
    string class_name = "ProbabilityTableCalculator";
    string func_name  = "set_unreso_data(vector<vector<Integer> >& reso_region_flg)";

    vector<string> err_com;
    err_com.push_back("The interpolation scheme is different in each energy region.");
    err_com.push_back("However, only first interpolation scheme is copied and other");
    err_com.push_back("interpolation sceme is reglected.");
    err_com.push_back("");

    for(int i=0; i<pos_data_no; i++)
    {
      ostringstream oss01, oss02, oss03, oss04, oss05, oss06;
      oss01 << pos_i[ pos_data[i] ];
      oss02 << pos_j[ pos_data[i] ];
      oss03 << pos_k[ pos_data[i] ];
      oss04 << pos_l[ pos_data[i] ];
      oss05 << int_vec[0];
      oss06 << int_vec[ pos_data[i]];
      string str_data01 = "Position (NIS / NER / NJS / NE ) : ( " + oss01.str() + " / " + oss02.str()
                                                                  + oss03.str() + " / " + oss04.str() + " )";
      string str_data02 = "First interpolation scheme       : " + oss05.str();
      string str_data03 = "Interpolation scheme             : " + oss06.str();

      err_com.push_back("");
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
    }

    err_obj.output_caution(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::set_unreso_parameter(int i, int j, ResonanceDataContainer& reso_data_obj)
{
  unreso_data_obj[i].push_back(reso_data_obj.get_unreso_data_obj()[i][j]);

  xs_formula_flg[i].push_back(reso_data_obj.get_xs_formula_flg()[i][j]);
  scat_radius_ene_dependence_flg[i].push_back(reso_data_obj.get_scat_radius_ene_dependence_flg()[i][j]);
  radius_calc_flg[i].push_back(reso_data_obj.get_radius_calc_flg()[i][j]);
  self_shielding_flg[i].push_back(reso_data_obj.get_unreso_data_obj()[i][j].get_self_shielding_flg());

  reso_ene_low[i].push_back(reso_data_obj.get_lower_ene_limit()[i][j]);
  reso_ene_high[i].push_back(reso_data_obj.get_upper_ene_limit()[i][j]);
  spin_data[i].push_back(reso_data_obj.get_spin_data()[i][j]);

  scat_radius[i].push_back(reso_data_obj.get_scat_radius()[i][j]);
  scat_radius_tab_int_data[i].push_back(reso_data_obj.get_scat_radius_tab_int_data()[i][j]);
  scat_radius_tab_range_data[i].push_back(reso_data_obj.get_scat_radius_tab_range_data()[i][j]);
  scat_radius_tab_ene_data[i].push_back(reso_data_obj.get_scat_radius_tab_ene_data()[i][j]);
  scat_radius_tab_data[i].push_back(reso_data_obj.get_scat_radius_tab_data()[i][j]);

  l_value[i].push_back(reso_data_obj.get_l_value()[i][j]);

  //Set const value for resonance calculation
  vector<Real8> wave_no_tmp, chan_rad_tmp;
  vector<Real8> mass_tmp = reso_data_obj.get_mass_isotope()[i][j];
  int k_max = static_cast<int>(mass_tmp.size());
  wave_no_tmp.resize(k_max);
  chan_rad_tmp.resize(k_max);
  for(int k=0; k<k_max; k++)
  {
    wave_no_tmp[k]  = k_part*mass_tmp[k]/(mass_tmp[k]+1.0);
    chan_rad_tmp[k] = 0.123 * pow(mass_tmp[k]*amu_n,third)+0.08;
  }
  mass[i].push_back(mass_tmp);
  wave_no_part[i].push_back(wave_no_tmp);
  chan_rad[i].push_back(chan_rad_tmp);
  mass_tmp.clear();
  wave_no_tmp.clear();
  chan_rad_tmp.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::set_unreso_ene_grid(vector<vector<vector<Real8> > > ene_data,
                                                     int i, int j, ResonanceDataContainer& reso_data_obj)
{
  vector<Real8> ene_tmp;

  Real8 e_l = reso_data_obj.get_lower_ene_limit()[i][j];
  Real8 e_h = reso_data_obj.get_upper_ene_limit()[i][j];

  if( digit_obj.get_adjusted_value(e_h, sig_fig, +1.0) > max_unreso_ene )
  {
    string class_name = "ProbabilityTableCalculator";
    string func_name  = "set_unreso_ene_grid";

    ostringstream oss01, oss02, oss03, oss04;
    oss01 << i+1;
    oss02 << j+1;

    oss03.precision(sig_fig);
    oss03.setf(ios::showpoint);
    oss03.setf(ios::scientific);
    oss03 << e_h;

    oss04.precision(sig_fig);
    oss04.setf(ios::showpoint);
    oss04.setf(ios::scientific);
    oss04 << max_unreso_ene;
    string str_data01 = "Number of istopes (NIS)        : " + oss01.str();
    string str_data02 = "Number of energy range (NER)   : " + oss02.str();
    string str_data03 = "Upperlimit of resonance energy : " + oss03.str();
    string str_data04 = "Maximum energy of this code    : " + oss04.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back("The upper limit of resonance energy is higher than the mixium energy of this code.");
    err_com.push_back("The generation of probability tables when the energy range is larger than");
    err_com.push_back("the maximum energy of this code is skipped.");

    err_obj.output_caution(class_name, func_name, err_com);
  }

  //Real8 el_m = digit_obj.get_adjusted_value(e_l, sig_fig, -1.0);
  Real8 el_p = digit_obj.get_adjusted_value(e_l, sig_fig,  1.0);
  Real8 eh_m = digit_obj.get_adjusted_value(e_h, sig_fig, -1.0);
  //Real8 eh_p = digit_obj.get_adjusted_value(e_h, sig_fig,  1.0);

  //ene_tmp.push_back(el_m);
  ene_tmp.push_back(el_p);
  ene_tmp.push_back(eh_m);
  //ene_tmp.push_back(eh_p);

  int k_max = static_cast<int>(ene_data.size());
  for(int k=0; k<k_max; k++)
  {
    int l_max = static_cast<int>(ene_data[k].size());
    for(int l=0; l<l_max; l++)
    {
      int m_max = static_cast<int>(ene_data[k][l].size());
      for(int m=0; m<m_max; m++)
      {
        if( ene_data[k][l][m] > e_l && ene_data[k][l][m] < e_h )
        {
          ene_tmp.push_back(ene_data[k][l][m]);
        }
      }
    }
  }
  clr_obj.clear_vec_array3_real8(ene_data);

  adjust_unreso_ene_grid(ene_tmp);

  k_max = static_cast<int>(ene_tmp.size());
  for(int k=0; k<k_max; k++)
  {
    ene_grid_unreso.push_back(ene_tmp[k]);
  }
  ene_tmp.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::adjust_unreso_ene_grid(vector<Real8>& ene_data)
{
  int i_max = static_cast<int>(ene_data.size());
  if( i_max <= 1 )
  {
    return;
  }

  //Delete overlapped energy grid
  ta_obj.delete_overlap_grid(ene_data);

  //Add energy grid
  vector<Real8> add_ene_grid;
      i_max = static_cast<int>(round(digit_obj.get_digit_number(max_unreso_ene) -1.0));
  int j_max = 13;
  add_ene_grid.resize(i_max*j_max);
  add_ene_grid[ 0] = 10.0;
  add_ene_grid[ 1] = 12.5;
  add_ene_grid[ 2] = 15.0;
  add_ene_grid[ 3] = 17.0;
  add_ene_grid[ 4] = 20.0;
  add_ene_grid[ 5] = 25.0;
  add_ene_grid[ 6] = 30.0;
  add_ene_grid[ 7] = 35.0;
  add_ene_grid[ 8] = 40.0;
  add_ene_grid[ 9] = 50.0;
  add_ene_grid[10] = 60.0;
  add_ene_grid[11] = 72.0;
  add_ene_grid[12] = 85.0;

  int ele_no = j_max;
  for(int i=1; i<i_max; i++)
  {
    for(int j=0; j<j_max; j++)
    {
      add_ene_grid[ele_no] = 10.0*add_ene_grid[ele_no-j_max];
      ele_no++;
    }
  }

  Real8 ene_pre, ene_cur;
  vector<Real8> ene_grid_tmp;
  i_max          = static_cast<int>(ene_data.size());
  int ele_no_max = static_cast<int>(add_ene_grid.size());
  ele_no  = 0;
  ene_pre = ene_data[0];
  ene_grid_tmp.push_back(ene_pre);
  for(int i=1; i<i_max; i++)
  {
    ene_cur = ene_data[i];
    if( ene_cur > 1.0E+6 )
    {
      if( (1.0E+6 - ene_pre) > ene_pre * min_ene_dif )
      {
        ene_grid_tmp.push_back(1.0E+6);
      }
    }

    if( ene_cur > ene_pre*1.26 )
    {
      while( add_ene_grid[ele_no] < ene_pre + min_ene_dif && ele_no < ele_no_max)
      {
        ele_no++;
      }

      while( add_ene_grid[ele_no] < ene_cur - min_ene_dif && ele_no < ele_no_max)
      {
        while( add_ene_grid[ele_no+1] < ene_pre*1.01 && ele_no < ele_no_max - 1 )
        {
          ele_no++;
        }

        ene_grid_tmp.push_back(add_ene_grid[ele_no]);
        ele_no++;
        if( ene_cur <= add_ene_grid[ele_no-1]*1.26 )
        {
          break;
        }
      }
    }
    ene_grid_tmp.push_back(ene_cur);
    ene_pre = ene_cur;
  }
  ene_data.clear();

  //Delete overlapped energy grid
  ta_obj.delete_overlap_grid(ene_grid_tmp);

  ene_data = ene_grid_tmp;
  ene_grid_tmp.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::set_xs_data()
{
  clear_xs_data();

  CrossSectionDataContainer xs_data_obj;
  Integer                   type_no, reaction_type;

  xs_skip.resize(xs_type_no);
  xs_data_back.resize(xs_type_no);

  xs_int_data.resize(xs_type_no);
  xs_range_data.resize(xs_type_no);
  xs_ene_data.resize(xs_type_no);
  xs_data.resize(xs_type_no);

  type_no = 0;
  for(int i=0; i<xs_type_no; i++)
  {
    xs_skip[i] = -1;
    if( i == total_xs )
    {
      type_no = 1;
    }
    else if( i == scatter_xs )
    {
      type_no = 2;
    }
    else if( i == fission_xs )
    {
      type_no = 18;
    }
    else if( i == radiation_xs )
    {
      type_no = 102;
    }
    
    xs_data_obj   = nucl_data_obj.get_nucl_reaction_data_obj().get_xs_data_obj(type_no);
    reaction_type = xs_data_obj.get_reaction_type();
    if( reaction_type != unassigned_mt_no )
    {
      xs_skip[i]       = 1;
      xs_int_data[i]   = xs_data_obj.get_xs_int_data();
      xs_range_data[i] = xs_data_obj.get_xs_range_data();
      xs_ene_data[i]   = xs_data_obj.get_xs_ene_data();
      xs_data[i]       = xs_data_obj.get_xs_data();
      xs_data_obj.clear();
    }
    else if( i == total_xs )
    {
      string class_name = "ProbabilityTableCalculator";
      string func_name  = "set_xs_data()";
  
      vector<string> err_com;
      err_com.push_back("There is no total cross section data.");
      err_com.push_back("Please check the NuclearDataObject.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
    xs_data_obj.clear();
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::set_back_ground_xs_data(int i)
{
  for(int j=0; j<xs_type_no; j++)
  {
    if( xs_skip[j] > 0 )
    {
      ti_obj.interpolation_tab1(ene_grid_unreso[i], xs_data_back[j],
                                xs_range_data[j], xs_int_data[j], xs_ene_data[j], xs_data[j]);
    }
    else
    {
      xs_data_back[j] = 0.0;
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::set_competition_flg(int xs_residual_flg)
{
  inela_comp_flg = -1; //inelastic  competition flag
  abs_comp_flg   = -1; //absorption competition flag
  comp_flg       =  0;
  if( xs_residual_flg < 0 )
  {
    prob_data_obj.set_comp_flg(comp_flg);
    prob_data_obj.set_comp_flg_inela(inela_comp_flg);
    prob_data_obj.set_comp_flg_abs(abs_comp_flg);
    return;
  }

  vector<CrossSectionDataContainer> xs_data_obj
                                      = nucl_data_obj.get_nucl_reaction_data_obj().get_xs_data_obj();

  int i_max = static_cast<int>(ene_grid_unreso.size());
  Real unreso_ene_max = ene_grid_unreso[i_max - 1];

  i_max = static_cast<int>(xs_data_obj.size());
  for(int i=0; i<i_max; i++)
  {
    Integer react_val = xs_data_obj[i].get_reaction_type();
    if( (react_val >=  4 && react_val <   6) || (react_val >  10 && react_val <  12) ||
        (react_val >  15 && react_val <  43) || (react_val >  43 && react_val <  46) ||
        (react_val >  49 && react_val <  92) || (react_val > 100 && react_val < 110) ||
        (react_val > 110 && react_val < 118) || (react_val > 150 && react_val <= 200) ||
        (react_val >= 600 && react_val <= 891) )
    {
      if( react_val > 4 && react_val != 18 && react_val != 19 && react_val != 102 )
      {
        Real8 ene_min = unreso_ene_max * 100.0;
        int j_max = static_cast<int>(xs_data_obj[i].get_xs_ene_data().size());
        for(int j=0; j<j_max; j++)
        {
          if( xs_data_obj[i].get_xs_data()[j] > min_sig_val )
          {
            if( j > 0 )
            {
              ene_min = xs_data_obj[i].get_xs_ene_data()[j-1];
            }
            else
            {
              ene_min = xs_data_obj[i].get_xs_ene_data()[j];
            }
            break;
          }
        }

        if( ene_min * 1.001 < unreso_ene_max )
        {
          string space_str = " ";
          if( react_val < 100 )
          {
            space_str = "  ";
            if( react_val < 10 )
            {
              space_str = "   ";
            }
          }
          cout.precision(7);
          cout.setf(ios::showpoint);
          cout.setf(ios::scientific);
          cout << "    unresolved resonance competes with MT =" << space_str << react_val
               << " (Emin of xs : " << ene_min << ", Emax of p-table : " << unreso_ene_max << ")" << endl;
          if( react_val >= 51 && react_val <= 91 )
          {
            if( inela_comp_flg < 0 )
            {
              inela_comp_flg = react_val;
            }
            else
            {
              inela_comp_flg = 4;
            }
          }
          else
          {
            if( abs_comp_flg < 0 )
            {
              abs_comp_flg = react_val;
            }
            else
            {
              abs_comp_flg = 0;
            }
          }
        }
      }
    }
  }

  cout << "    inelastic competition flag set to "  << inela_comp_flg << endl;
  cout << "    absorption competition flag set to " << abs_comp_flg   << endl;
  cout << endl;

  prob_data_obj.set_comp_flg(comp_flg);
  prob_data_obj.set_comp_flg_inela(inela_comp_flg);
  prob_data_obj.set_comp_flg_abs(abs_comp_flg);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::set_unreso_data_for_probability_table()
{
  clear_unreso_data_for_probability_table();

  int i_max = static_cast<int>(xs_formula_flg.size());
  coef_prob_table.resize(i_max);
  cos2phi.resize(i_max);
  sin2phi.resize(i_max);

  coef_gamma.resize(i_max);
  level_spacing.resize(i_max);
  width_n.resize(i_max);
  width_rad.resize(i_max);
  width_fis.resize(i_max);
  width_comp.resize(i_max);
  width_tot.resize(i_max);

  freedom_n.resize(i_max);
  freedom_fis.resize(i_max);
  freedom_comp.resize(i_max);

  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(xs_formula_flg[i].size());
    coef_prob_table[i].resize(j_max);
    cos2phi[i].resize(j_max);
    sin2phi[i].resize(j_max);

    coef_gamma[i].resize(j_max);
    level_spacing[i].resize(j_max);
    width_n[i].resize(j_max);
    width_rad[i].resize(j_max);
    width_fis[i].resize(j_max);
    width_comp[i].resize(j_max);
    width_tot[i].resize(j_max);

    freedom_n[i].resize(j_max);
    freedom_fis[i].resize(j_max);
    freedom_comp[i].resize(j_max);
    for(int j=0; j<j_max; j++)
    {
      int l_max = static_cast<int>(l_value[i][j].size());
      coef_prob_table[i][j].resize(l_max);
      cos2phi[i][j].resize(l_max);
      sin2phi[i][j].resize(l_max);

      coef_gamma[i][j].resize(l_max);
      level_spacing[i][j].resize(l_max);
      width_n[i][j].resize(l_max);
      width_rad[i][j].resize(l_max);
      width_fis[i][j].resize(l_max);
      width_comp[i][j].resize(l_max);
      width_tot[i][j].resize(l_max);

      freedom_n[i][j].resize(l_max);
      freedom_fis[i][j].resize(l_max);
      freedom_comp[i][j].resize(l_max);
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::init_unreso_data_for_probability_table()
{
  level_spacing_min = level_spacing_min_ini;
  level_spacing_inv = 0.0;

  int i_max = static_cast<int>(xs_formula_flg.size());
  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(xs_formula_flg[i].size());
    for(int j=0; j<j_max; j++)
    {
      int l_max = static_cast<int>(l_value[i][j].size());
      for(int l=0; l<l_max; l++)
      {
        coef_prob_table[i][j][l] = 0.0;
        cos2phi[i][j][l]         = 0.0;
        sin2phi[i][j][l]         = 0.0;

        coef_gamma[i][j][l].clear();
        level_spacing[i][j][l].clear();
        width_n[i][j][l].clear();
        width_rad[i][j][l].clear();
        width_fis[i][j][l].clear();
        width_comp[i][j][l].clear();
        width_tot[i][j][l].clear();

        freedom_n[i][j][l].clear();
        freedom_fis[i][j][l].clear();
        freedom_comp[i][j][l].clear();
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::calc_unreso_xs(Real8& ene_val, vector<Real8>& xs_val)
{
  init_unreso_data_for_probability_table();

  xs_val.clear();

  vector<Real8> xs_tmp;
  xs_val.resize(xs_type_no);
  xs_tmp.resize(xs_type_no);
  for(int i=0; i<xs_type_no; i++)
  {
    xs_val[i] = 0.0;
    xs_tmp[i] = 0.0;
  }

  xs_potential = 0.0;

  int i_max = static_cast<int>(scat_radius_ene_dependence_flg.size());
  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(scat_radius_ene_dependence_flg[i].size());
    for(int j=0; j<j_max; j++)
    {
      if( scat_radius_ene_dependence_flg[i][j] == 0 && scat_radius[i][j] < 0.0)
      {
        string class_name = "ProbabilityTableCalculator";
        string func_name  = "calc_unreso_xs(Real8& ene_val, vector<Real8>& xs_val)";

        ostringstream oss01, oss02, oss03, oss04;
        oss01 << i;
        oss02 << i_max;
        oss03 << scat_radius_ene_dependence_flg[i][j];
        oss04 << scat_radius[i][j];
        string str_data01 = "Number of istopes (NIS)              : " + oss01.str() + " / " + oss02.str();
        string str_data02 = "scat_radius_ene_dependence_flg (NRO) : " + oss03.str();
        string str_data03 = "scat_radius (AP)                     : " + oss04.str();

        vector<string> err_com;
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back("scat_radius(AP) at reso_region_flg(LRU)=2 is less than 0.0.");
        err_com.push_back("scat_radius(AP) or scat_radius_ene_dependence_flg(NRO) value is not appropriate.");

        err_obj.output_runtime_error(class_name, func_name, err_com);
      }

      unreso_data_obj_each.clear();
      unreso_data_obj_each = unreso_data_obj[i][j];

      if( xs_formula_flg[i][j] == 1 ) //For Case A and B
      {
        calc_unreso_xs_a(i, j, ene_val, xs_tmp);
      }
      else //For Case C
      {
        calc_unreso_xs_c(i, j, ene_val, xs_tmp);
      }

      for(int k=0; k<xs_type_no; k++)
      {
        xs_val[k] += xs_tmp[k];
        xs_tmp[k]  = 0.0;
      }

      //Search minimum value of the level spacing
      search_minimum_level_spacing(level_spacing[i][j]);
    }
  }
  xs_tmp.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::search_minimum_level_spacing(vector<vector<Real8> >& level_spacing_vec)
{
  for(int i=0; i<static_cast<int>(level_spacing_vec.size()); i++)
  {
    for(int j=0; j<static_cast<int>(level_spacing_vec[i].size()); j++)
    {
      Real8 tmp_real = level_spacing_vec[i][j];
      level_spacing_inv += 1.0 / tmp_real;
      if( level_spacing_min > tmp_real )
      {
        level_spacing_min = tmp_real;
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::calc_unreso_xs_a(int i, int j, Real8& ene_val, vector<Real8>& xs_val)
{
  Real8   e_root, wave_no, wave_no_inv, const_val, den, coef_gamma_tmp, abn,
          rho, rho_h, vl, phi, sph, spot, ene_coef;
  Real8   dx, aj, amun, gnox, ggx, gfx, gj, gnx, gx;
  Integer fis_width_flg_val, l_val;
  Integer muf;
  int mu, nu, lamda;
  vector<Real8>   xs_tmp;
  vector<Real>    es, gf;
  vector<Integer> nbt_gf, int_gf;

  gx    = 0.0;
  lamda = 1;
  
  xs_tmp.resize(xs_type_no); //total, scatter, fission, capture
  
  vector<vector<vector<Real8> > > ene_unreso = unreso_data_obj_each.get_ene_unreso();
  int k_max = static_cast<int>(ene_unreso.size());
  es.resize(k_max);
  for(int k=0; k<k_max; k++)
  {
    es[k] = ene_unreso[k][0][0];
  }
  clr_obj.clear_vec_array3_real8(ene_unreso);

  nbt_gf.resize(1);
  int_gf.resize(1);
  nbt_gf[0] = k_max;
  int_gf[0] = int_lin_lin; //linear-linear
  
  fis_width_flg_val = fis_width_flg[i];
  
  e_root         = sqrt(fabs(ene_val));
  wave_no        = wave_no_part[i][j][0] * e_root;
  wave_no_inv    = 1.0 / wave_no;
  const_val      = 2.0*pi_sq * wave_no_inv * wave_no_inv;
  den            = 1.0/(4.0*spin_data[i][j]+2.0);
  ene_coef       = coef_boltz / e_root;
  abn            = abundance[i];
  coef_gamma_tmp = abn * 4.0 * pi * den * wave_no_inv * wave_no_inv;
  
  int l_max = static_cast<int>(l_value[i][j].size());
  for(int l=0; l<l_max; l++)
  {
    l_val = l_value[i][j][l];
    calc_rho(i, j, l, ene_val, wave_no, rho, rho_h);
    reso_calc_obj.calc_phase_shift(l_val, rho_h, phi);
    sph = sin(phi);

    //Set parameters for probability table
    coef_prob_table[i][j][l] = ene_coef * sqrt(mass[i][j][0]); 
    cos2phi[i][j][l]         = cos(2.0*phi);
    sin2phi[i][j][l]         = sin(2.0*phi);
    
    vector<Real8> aj_vec = unreso_data_obj_each.get_j_value_abs()[l];
    int m_max = static_cast<int>(aj_vec.size());
    coef_gamma[i][j][l].resize(m_max);
    level_spacing[i][j][l].resize(m_max);
    width_n[i][j][l].resize(m_max);
    width_rad[i][j][l].resize(m_max);
    width_fis[i][j][l].resize(m_max);
    width_comp[i][j][l].resize(m_max);
    width_tot[i][j][l].resize(m_max);
    freedom_n[i][j][l].resize(m_max);
    freedom_fis[i][j][l].resize(m_max);
    freedom_comp[i][j][l].resize(m_max);
    for(int m=0; m<m_max; m++)
    {
      dx   = unreso_data_obj_each.get_level_spacing()[l][m][0];
      aj   = aj_vec[m];
      amun = unreso_data_obj_each.get_freedom_n()[l][m];
      gnox = unreso_data_obj_each.get_ave_gam_width_n()[l][m][0];
      ggx  = unreso_data_obj_each.get_ave_gam_width_rad()[l][m][0];
      
      if( fis_width_flg_val == 0 ) //Case A
      {
        muf  = 1;
        gfx  = 0.0;
      }
      else //Case B
      {
        muf = unreso_data_obj_each.get_freedom_fis_int()[l][m];
        gf  = unreso_data_obj_each.get_ave_gam_width_fis()[l][m];
        ti_obj.interpolation_tab1(ene_val, gfx, nbt_gf, int_gf, es, gf);
      }

      reso_calc_obj.calc_penetrability_factor(l_val, rho, amun, vl);
      vl  = vl*e_root;
      gnx = gnox * vl;
      gj  = abn * const_val*gnx*(2.0*aj + 1.0) * den / dx;
      
      mu    = static_cast<int>(round(amun));
      nu    = static_cast<int>(muf);
      reso_calc_obj.calc_width_fluctuation_factor(gnx, gfx, ggx, mu, nu, lamda, xs_tmp, gx);

      xs_val[scatter_xs]   += xs_tmp[scatter_xs]  *gj*gnx - 2.0*gj*sph*sph;
      xs_val[fission_xs]   += xs_tmp[fission_xs]  *gj*gfx;
      xs_val[radiation_xs] += xs_tmp[radiation_xs]*gj*ggx;

      //Set parameters for probability table
      coef_gamma[i][j][l][m]    = (2.0*aj + 1.0) * coef_gamma_tmp;
      level_spacing[i][j][l][m] = dx;
      width_n[i][j][l][m]       = gnx;
      width_rad[i][j][l][m]     = ggx;
      width_fis[i][j][l][m]     = gfx;
      width_comp[i][j][l][m]    = gx;
      width_tot[i][j][l][m]     = gnx + ggx + gfx + gx;
      freedom_n[i][j][l][m]     = mu;
      freedom_fis[i][j][l][m]   = nu;
      freedom_comp[i][j][l][m]  = lamda;
    }
    aj_vec.clear();

    spot = sph * wave_no_inv;
    spot = abn * 4.0*pi*(2.0*static_cast<Real8>(l_val) + 1.0) * spot*spot;
    xs_potential += spot;
  }
  xs_val[total_xs] = xs_val[scatter_xs] + xs_val[fission_xs] + xs_val[radiation_xs];
  
  xs_tmp.clear();
  es.clear();
  gf.clear();
  nbt_gf.clear();
  int_gf.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::calc_unreso_xs_c(int i, int j, Real8& ene_val, vector<Real8>& xs_val)
{
  Real8   e_root, wave_no, wave_no_inv, const_val, den, coef_gamma_tmp, abn,
          rho, rho_h, vl, phi, sph, spot, ene_coef;
  Real8   aj, amux, amun, amuf, gj, gnx;
  Real8   es_m, es_p, d_m, d_val, d_p, gx_m, gx, gx_p, gn_m, gn, gn_p, gg_m, gg, gg_p, gf_m, gf, gf_p;
  Integer l_val;
  int mu, nu, lamda, es_pos;

  Integer int_val = unreso_int_data;
  
  vector<Real8>          xs_tmp;
  vector<vector<Real8> > es_vec;

  xs_tmp.resize(xs_type_no); //total, scatter, fission, capture
  
  e_root         = sqrt(fabs(ene_val));
  wave_no        = wave_no_part[i][j][0] * e_root;
  wave_no_inv    = 1.0 / wave_no;
  const_val      = 2.0*pi_sq * wave_no_inv * wave_no_inv;
  den            = 1.0/(4.0*spin_data[i][j]+2.0);
  ene_coef       = coef_boltz / e_root;
  abn            = abundance[i];
  coef_gamma_tmp = abn * 4.0 * pi * den * wave_no_inv * wave_no_inv;
  
  int l_max = static_cast<int>(l_value[i][j].size());
  for(int l=0; l<l_max; l++)
  {
    l_val = l_value[i][j][l];
    calc_rho(i, j, l, ene_val, wave_no, rho, rho_h);
    reso_calc_obj.calc_phase_shift(l_val, rho_h, phi);
    sph = sin(phi);

    //Set parameters for probability table
    coef_prob_table[i][j][l] = ene_coef * sqrt(mass[i][j][0]);
    cos2phi[i][j][l]         = cos(2.0*phi);
    sin2phi[i][j][l]         = sin(2.0*phi);
   
    es_vec = unreso_data_obj_each.get_ene_unreso()[l];
    int m_max = static_cast<int>(es_vec.size());
    coef_gamma[i][j][l].resize(m_max);
    level_spacing[i][j][l].resize(m_max);
    width_n[i][j][l].resize(m_max);
    width_rad[i][j][l].resize(m_max);
    width_fis[i][j][l].resize(m_max);
    width_comp[i][j][l].resize(m_max);
    width_tot[i][j][l].resize(m_max);
    freedom_n[i][j][l].resize(m_max);
    freedom_fis[i][j][l].resize(m_max);
    freedom_comp[i][j][l].resize(m_max);
    for(int m=0; m<m_max; m++)
    {
      int_val = unreso_data_obj_each.get_unreso_int_data()[l][m];
      aj      = unreso_data_obj_each.get_j_value_abs()[l][m];
      amux    = unreso_data_obj_each.get_freedom_comp()[l][m];
      amun    = unreso_data_obj_each.get_freedom_n()[l][m];
      amuf    = unreso_data_obj_each.get_freedom_fis()[l][m];
      
      int n_max = static_cast<int>(es_vec[m].size());
      es_pos = -1;
      for(int n=1; n<n_max; n++)
      {
        if( es_vec[m][n] > ene_val )
        {
          es_pos = n;
          break;
        }
      }
      if( es_pos < 0 )
      {
        es_pos = n_max - 1;
      }
      
      es_m = es_vec[m][es_pos-1];
      es_p = es_vec[m][es_pos];
      d_m  = unreso_data_obj_each.get_level_spacing()[l][m][es_pos-1];
      d_p  = unreso_data_obj_each.get_level_spacing()[l][m][es_pos];
      gx_m = unreso_data_obj_each.get_ave_gam_width_comp()[l][m][es_pos-1];
      gx_p = unreso_data_obj_each.get_ave_gam_width_comp()[l][m][es_pos];
      gn_m = unreso_data_obj_each.get_ave_gam_width_n()[l][m][es_pos-1];
      gn_p = unreso_data_obj_each.get_ave_gam_width_n()[l][m][es_pos];
      gg_m = unreso_data_obj_each.get_ave_gam_width_rad()[l][m][es_pos-1];
      gg_p = unreso_data_obj_each.get_ave_gam_width_rad()[l][m][es_pos];
      gf_m = unreso_data_obj_each.get_ave_gam_width_fis()[l][m][es_pos-1];
      gf_p = unreso_data_obj_each.get_ave_gam_width_fis()[l][m][es_pos];

      //Modify es, d, gx, gn, gg and gf
      if( es_m < min_value )
      {
        es_m = 1.0E-12;
      }
      if( es_p < min_value )
      {
        es_p = 1.0E-12;
      }
      if( d_m < min_value )
      {
        d_m = 1.0E-12;
      }
      if( d_p < min_value )
      {
        d_p = 1.0E-12;
      }
      if( gx_m < min_value )
      {
        gx_m = 1.0E-12;
      }
      if( gx_p < min_value )
      {
        gx_p = 1.0E-12;
      }
      if( gn_m < min_value )
      {
        gn_m = 1.0E-12;
      }
      if( gn_p < min_value )
      {
        gn_p = 1.0E-12;
      }
      if( gg_m < min_value )
      {
        gg_m = 1.0E-12;
      }
      if( gg_p < min_value )
      {
        gg_p = 1.0E-12;
      }
      if( gf_m < min_value )
      {
        gf_m = 1.0E-12;
      }
      if( gf_p < min_value )
      {
        gf_p = 1.0E-12;
      }
      
      ti_obj.interpolation_1d(int_val, ene_val, d_val, es_m, d_m,  es_p, d_p);
      ti_obj.interpolation_1d(int_val, ene_val, gn,    es_m, gn_m, es_p, gn_p);
      ti_obj.interpolation_1d(int_val, ene_val, gg,    es_m, gg_m, es_p, gg_p);
      ti_obj.interpolation_1d(int_val, ene_val, gx,    es_m, gx_m, es_p, gx_p);
      ti_obj.interpolation_1d(int_val, ene_val, gf,    es_m, gf_m, es_p, gf_p);

      if( gx < 1.0e-8 )
      {
        gx = 0.0;
      }
      if( gf < 1.0e-8 )
      {
        gf = 0.0;
      }
      
      reso_calc_obj.calc_penetrability_factor(l_val, rho, amun, vl);
      vl  = vl*e_root;
      gnx = gn * vl;
      gj  = abn * const_val*gnx*(2.0*aj + 1.0) * den / d_val;
      
      mu    = static_cast<int>(round(amun));
      nu    = static_cast<int>(round(amuf));
      lamda = static_cast<int>(round(amux));
      reso_calc_obj.calc_width_fluctuation_factor(gnx, gf, gg, mu, nu, lamda, xs_tmp, gx);
      
      xs_val[scatter_xs]   += xs_tmp[scatter_xs]  *gj*gnx - 2.0*gj*sph*sph;
      xs_val[fission_xs]   += xs_tmp[fission_xs]  *gj*gf;
      xs_val[radiation_xs] += xs_tmp[radiation_xs]*gj*gg;

      //Set parameters for probability table
      coef_gamma[i][j][l][m]    = (2.0*aj + 1.0) * coef_gamma_tmp;
      level_spacing[i][j][l][m] = d_val;
      width_n[i][j][l][m]       = gnx;
      width_rad[i][j][l][m]     = gg;
      width_fis[i][j][l][m]     = gf;
      width_comp[i][j][l][m]    = gx;
      width_tot[i][j][l][m]     = gnx + gg + gf + gx;
      freedom_n[i][j][l][m]     = mu;
      freedom_fis[i][j][l][m]   = nu;
      freedom_comp[i][j][l][m]  = lamda;
    }
    clr_obj.clear_vec_array2_real8(es_vec);

    spot = sph * wave_no_inv;
    spot = abn * 4.0*pi*(2.0*static_cast<Real8>(l_val) + 1.0) * spot*spot;
    xs_potential += spot;
  }
  xs_tmp.clear();

  xs_val[total_xs] = xs_val[scatter_xs] + xs_val[fission_xs] + xs_val[radiation_xs];
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::calc_rho(int i, int j, int k,
                                          Real8& ene, Real8& wave_no, Real8& rho, Real8& rho_h)
{
  if( scat_radius_ene_dependence_flg[i][j] == 0 )
  {
    rho_h = wave_no * scat_radius[i][j];
    
    if( radius_calc_flg[i][j] == 0 )
    {
      rho = wave_no * chan_rad[i][j][k];
    }
    else
    {
      rho = rho_h;
    }
  }
  else
  {
    ti_obj.interpolation_tab1( ene, rho_h,
                               scat_radius_tab_range_data[i][j], scat_radius_tab_int_data[i][j],
                               scat_radius_tab_ene_data[i][j], scat_radius_tab_data[i][j] );
    rho_h *= wave_no;
    
    if( radius_calc_flg[i][j] == 0 )
    {
      rho = wave_no * chan_rad[i][j][k];
    }
    else if( radius_calc_flg[i][j] == 1 )
    {
      if( scat_radius[i][j] > 0.0 )
      {
        rho = scat_radius[i][j];
      }
      else
      {
        rho = rho_h;
      }
    }
    else
    {
      rho = wave_no * scat_radius[i][j];
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::calc_probability_and_bondarenko_table(int ene_no,
                                                                       vector<Real8>& xs_unreso,
                                                                       vector<Real8>& xs_back_ground)
{
  Real8   ene_range = ene_range_ini * level_spacing_min;
  Real8   ene_low  = ene_low_ini;
  Real8   ene_high = ene_low  + ene_range;
  Real8   ene_min  = ene_low  + 300.0/level_spacing_inv;
  Real8   ene_max  = ene_high - 300.0/level_spacing_inv;

  nrest = static_cast<Integer>(round(ene_range*level_spacing_inv)) - 600;

  p_tab_stat_each_temp.resize(temp_no_int);
  p_tab_xs_stat_each_temp.resize(temp_no_int);
  xs_stat_each_temp.resize(temp_no_int);
  for(int i=0; i<temp_no_int; i++)
  {
    p_tab_stat_each_temp[i].resize(ladder_no_int);
    p_tab_xs_stat_each_temp[i].resize(ladder_no_int);
    xs_stat_each_temp[i].resize(ladder_no_int);
  }
  
  init_probability_table_parameter_each_ene();
  for(int lad_no=0; lad_no<ladder_no_int; lad_no++)
  {
    set_energy_grid_each_ladder(ene_min, ene_max);
    for(int i=0; i<temp_no_int; i++)
    {
      for(int j=0; j<sample_no; j++)
      {
        for(int k=0; k<xs_type_no; k++)
        {
          xs_prob[i][j][k] = 0.0;
        }
        xs_prob[i][j][scatter_xs] = xs_potential;
      }
    }

    int i_max = static_cast<int>(freedom_n.size());
    for(int i=0; i<i_max; i++)
    {
      int j_max = static_cast<int>(freedom_n[i].size());
      for(int j=0; j<j_max; j++)
      {
        int k_max = static_cast<int>(freedom_n[i][j].size());
        for(int k=0; k<k_max; k++)
        {
          int l_max = static_cast<int>(freedom_n[i][j][k].size());
          for(int l=0; l<l_max; l++)
          {
            set_gamma_width(i, j, k, l, ene_low, ene_high);
            calc_unreso_xs_with_doppler(coef_prob_table[i][j][k]);
          }
        }
      }
    }

    
    adjust_unreso_xs_with_doppler(xs_back_ground);
    calc_infinite_dilution_xs_each_ladder(xs_back_ground);
    for(int i=0; i<temp_no_int; i++)
    {
      /*
      if( lad_no == 0 )
      {
        if( set_xs_tot_table_data_flg == 0 )
        {
          set_xs_tot_table(i, xs_back_ground);
        }
        else
        {
          check_xs_tot_table(ene_no, i);
        }
      }
      */
      calc_probability_and_bondarenko_table_data(ene_no, i, lad_no, xs_back_ground);
    }
    clear_probability_table_parameter_each_ladder();

    if( check_statistical_error(ene_no, lad_no) > 0 )
    {
      break;
    }
  }
  calc_bondarenko_table();
  calc_probability_table_data(xs_unreso);
  calc_bondarenko_xs();
  calc_infinite_dilution_xs();

  copy_probability_table_data(ene_no, xs_unreso, xs_back_ground);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::set_probability_table_parameter_all_ladder()
{
  clear_probability_table_parameter_all_ladder();

  ene_grid_each_ladder.resize(sample_no);
  xs_inf.resize(xs_type_no);

  xs_tot_min.resize(temp_no_int);
  xs_tot_max.resize(temp_no_int);
  xs_tot_table.resize(temp_no_int);
  xs_prob.resize(temp_no_int);
  xs_inf_ave.resize(temp_no_int);
  xs_inf_var.resize(temp_no_int);
  prob_table_sample_no.resize(temp_no_int);
  prob_table.resize(temp_no_int);
  bondarenko_table.resize(temp_no_int);
  bondarenko_xs.resize(temp_no_int);
  bondarenko_data.resize(temp_no_int);
  for(int i=0; i<temp_no_int; i++)
  {
    xs_tot_table[i].resize(bin_no_int);
    xs_prob[i].resize(sample_no);
    for(int j=0; j<sample_no; j++)
    {
      xs_prob[i][j].resize(xs_type_no);
    }

    xs_inf_ave[i].resize(xs_type_no);
    xs_inf_var[i].resize(xs_type_no);

    prob_table_sample_no[i].resize(bin_no_int);
    prob_table[i].resize(bin_no_int);
    for(int j=0; j<bin_no_int; j++)
    {
      prob_table[i][j].resize(xs_type_no);
    }

    bondarenko_table[i].resize(sig_zero_no_int);
    bondarenko_xs[i].resize(sig_zero_no_int);
    bondarenko_data[i].resize(sig_zero_no_int);
    for(int j=0; j<sig_zero_no_int; j++)
    {
      bondarenko_table[i][j].resize(bondarenko_table_data_no);
      bondarenko_xs[i][j].resize(bondarenko_xs_data_no);
      bondarenko_data[i][j].resize(bondarenko_table_data_no+2);
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::set_energy_grid_each_ladder(Real8& ene_min, Real8& ene_max)
{
  Real8 ene_span = fabs(ene_max - ene_min);
  for(int i=0; i<sample_no; i++)
  {
    ene_grid_each_ladder[i] = ene_min + ene_span*rand_obj.uniform_distribution();
  }
  sort(ene_grid_each_ladder.begin(), ene_grid_each_ladder.end());
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::init_probability_table_parameter_each_ene()
{
  for(int i=0; i<temp_no_int; i++)
  {
    for(int j=0; j<sample_no; j++)
    {
      for(int k=0; k<xs_type_no; k++)
      {
        xs_prob[i][j][k] = 0.0;
      }
    }

    for(int j=0; j<xs_type_no; j++)
    {
      xs_inf_ave[i][j] = 0.0;
      xs_inf_var[i][j] = 0.0;
    }

    xs_tot_min[i] = 0.0;
    xs_tot_max[i] = 0.0;
    for(int j=0; j<bin_no_int; j++)
    {
      xs_tot_table[i][j]         = 0.0;
      prob_table_sample_no[i][j] = 0;
      for(int k=0; k<xs_type_no; k++)
      {
        prob_table[i][j][k] = 0.0;
      }
    }

    for(int j=0; j<sig_zero_no_int; j++)
    {
      for(int k=0; k<bondarenko_table_data_no; k++)
      {
        bondarenko_table[i][j][k] = 0.0;
      }
      for(int k=0; k<bondarenko_table_data_no+2; k++)
      {
        bondarenko_data[i][j][k] = 0.0;
      }

      for(int k=0; k<bondarenko_xs_data_no; k++)
      {
        bondarenko_xs[i][j][k] = 0.0;
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::set_gamma_width(int i, int j, int k, int l,
                                                 Real8& ene_low, Real8& ene_high)
{
  cos2phi_prob    = cos2phi[i][j][k];
  sin2phi_prob    = sin2phi[i][j][k];
  coef_gamma_prob = coef_gamma[i][j][k][l];

  Real8 ene_dist         = level_spacing[i][j][k][l];
  Real8 width_n_ave      = width_n[i][j][k][l];
  Real8 width_rad_ave    = width_rad[i][j][k][l];
  Real8 width_fis_ave    = width_fis[i][j][k][l];
  Real8 width_comp_ave   = width_comp[i][j][k][l];
  Real8 freedom_n_ave    = static_cast<Real8>(freedom_n[i][j][k][l]);
  Real8 freedom_fis_ave  = static_cast<Real8>(freedom_fis[i][j][k][l]);
  Real8 freedom_comp_ave = static_cast<Real8>(freedom_comp[i][j][k][l]);

  if( freedom_n[i][j][k][l] > 0 )
  {
    width_n_ave = width_n_ave / freedom_n_ave;
  }

  int fis_cal_flg = -1;
  if( fabs(width_fis_ave) > min_value && fabs(freedom_fis_ave) > min_value )
  {
    fis_cal_flg = 0;

    if( freedom_fis[i][j][k][l] > 0 )
    {
      width_fis_ave = width_fis_ave / freedom_fis_ave;
    }
  }

  int comp_cal_flg = -1;
  if( fabs(width_comp_ave) > min_value && fabs(freedom_comp_ave) > min_value )
  {
    comp_cal_flg = 0;

    if( freedom_comp[i][j][k][l] > 0 )
    {
      width_comp_ave = width_comp_ave / freedom_comp_ave;
    }
  }

  ene_reso_loc.clear(); //Resonance energy location in each resonance
  width_tot_prob.clear();
  width_n_prob.clear();
  width_fis_prob.clear();
  width_comp_prob.clear();
  width_rad_prob.clear();

  Real8 ene_val         = ene_low + ene_dist * rand_obj.uniform_distribution();
  Real8 width_tot_rand  = 0.0;
  Real8 width_n_rand    = 0.0;
  Real8 width_fis_rand  = 0.0;
  Real8 width_comp_rand = 0.0;
  Real8 width_rad_rand  = 0.0;
  while( ene_val <= ene_high )
  {
    width_n_rand = width_n_ave * rand_obj.chi_square_distribution(freedom_n_ave);
    if( fis_cal_flg == 0 )
    {
      width_fis_rand = width_fis_ave * rand_obj.chi_square_distribution(freedom_fis_ave);
    }
    if( comp_cal_flg == 0 )
    {
      width_comp_rand = width_comp_ave * rand_obj.chi_square_distribution(freedom_comp_ave);
    }
    width_rad_rand = width_rad_ave;

    width_tot_rand   = width_n_rand + width_fis_rand + width_comp_rand + width_rad_rand;
    width_n_rand    /= width_tot_rand;
    width_fis_rand  /= width_tot_rand;
    width_comp_rand /= width_tot_rand;
    width_rad_rand  /= width_tot_rand;

    ene_reso_loc.push_back(ene_val);
    width_tot_prob.push_back(width_tot_rand);
    width_n_prob.push_back(width_n_rand);
    width_fis_prob.push_back(width_fis_rand);
    width_comp_prob.push_back(width_comp_rand);
    width_rad_prob.push_back(width_rad_rand);

    Real8 ene_add = ene_dist*rand_obj.wigner_distribution();
    //while( ene_add < min_value )
    while( ene_add < min_ene_dif )
    {
      ene_add = ene_dist*rand_obj.wigner_distribution();
    }
    ene_val += ene_add;
  }

  ene_reso_loc_no_int = static_cast<int>(ene_reso_loc.size());
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::calc_unreso_xs_with_doppler(Real8 coef_temp_prob)
{
  int   ene_sta, ene_end;
  Real8 width_all, h_val, x_val, phi, chi, coef_temp_prob_cal, coef_temp_prob_cal_inv,
        coef_gamma_dop, cos2phi_dop, sin2phi_dop, coef_width_rad, coef_width_fis;

  for(int i=0; i<temp_no_int; i++)
  {
    Real temp_val = temp_data[i];
    if( temp_val < min_temp_value )
    { 
      temp_val = min_temp_value; //1.0E-10
    }

    coef_temp_prob_cal      = coef_temp_prob * sqrt(temp_ref / temp_val);
    coef_temp_prob_cal_inv  = 1.0 / coef_temp_prob_cal;
  
    for(int j=0; j<ene_reso_loc_no_int; j++)
    {
      if( width_tot_prob[j] > coef_temp_prob_cal_inv )
      {
        width_all = width_tot_prob[j];
      }
      else
      {
        width_all = coef_temp_prob_cal_inv;
      }
      width_all = 2.0*cumulative_distr_cauchy*fabs(width_all);

      search_ene_pos(ene_sta, ene_end, ene_reso_loc[j] - width_all, ene_reso_loc[j] + width_all);

      if( ene_sta < ene_end )
      {
        h_val          = 0.5 * coef_temp_prob_cal * width_tot_prob[j];
        coef_gamma_dop = coef_gamma_prob * width_n_prob[j];
        cos2phi_dop    = coef_gamma_dop * (cos2phi_prob - 1.0 + width_n_prob[j]);
        sin2phi_dop    = coef_gamma_dop *  sin2phi_prob;
        coef_width_rad = coef_gamma_dop *  width_rad_prob[j];
        coef_width_fis = coef_gamma_dop *  width_fis_prob[j];

        math_obj.set_h_val(h_val);
        for(int k=ene_sta; k<=ene_end; k++)
        {
          x_val = coef_temp_prob_cal * (ene_grid_each_ladder[k] - ene_reso_loc[j]);
          math_obj.calc_doppler_broadening_function(x_val, phi, chi);

          xs_prob[i][k][scatter_xs]   += cos2phi_dop*phi + sin2phi_dop*chi;
          xs_prob[i][k][fission_xs]   += coef_width_fis*phi;
          xs_prob[i][k][radiation_xs] += coef_width_rad*phi;
        }
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::search_ene_pos(int& ene_sta, int& ene_end,
                                                Real8 ene_min, Real8 ene_max)
{
  if( ene_max < ene_grid_each_ladder[0] )
  {
    ene_sta = 0;
    ene_end = 0;
    return;
  }
  else if( ene_min > ene_grid_each_ladder[sample_no - 1] )
  {
    ene_sta = sample_no - 1;
    ene_end = sample_no - 1;
    return;
  }

  vector<double>::iterator pos;
  pos = upper_bound(ene_grid_each_ladder.begin(), ene_grid_each_ladder.end(), ene_min);
  ene_sta = distance(ene_grid_each_ladder.begin(), pos) - 1;
  if (ene_sta < 0)
  {
    ene_sta = 0;
  }

  pos = upper_bound(ene_grid_each_ladder.begin(), ene_grid_each_ladder.end(), ene_max);
  ene_end = distance(ene_grid_each_ladder.begin(), pos);
  if (ene_end >= sample_no)
  {
    ene_end = sample_no - 1;
  }

  if( ene_sta == ene_end )
  {
    if( ene_sta != 0 && ene_end != sample_no - 1 )
    {
      ene_end++;
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::adjust_unreso_xs_with_doppler(vector<Real8>& xs_back_ground)
{
  Real8 scat_xs_bg = -1.0 * xs_back_ground[scatter_xs];

  for(int i=0; i<temp_no_int; i++)
  {
    for(int j=0; j<sample_no; j++)
    {
      if( xs_prob[i][j][scatter_xs] < scat_xs_bg )
      {
        xs_prob[i][j][scatter_xs] = scat_xs_bg + adjust_scat_xs_val;
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::calc_infinite_dilution_xs()
{
  for(int i=0; i<temp_no_int; i++)
  {
    for(int j=0; j<xs_type_no; j++)
    {
      xs_inf_ave[i][j] = xs_inf_ave[i][j] * ladder_no_inv;
      xs_inf_var[i][j] = xs_inf_var[i][j] * ladder_no_inv
                       - xs_inf_ave[i][j] * xs_inf_ave[i][j];

      if( xs_inf_var[i][j] < 0.0 )
      {
        xs_inf_var[i][j] = 0.0;
      }
      else
      {
        xs_inf_var[i][j] = sqrt(xs_inf_var[i][j]);
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::calc_infinite_dilution_xs_each_ladder(vector<Real8>& xs_back_ground)
{
  for(int i=0; i<temp_no_int; i++)
  {
    for(int j=0; j<xs_type_no; j++)
    {
      xs_inf[j] = 0.0;
    }

    for(int j=0; j<sample_no; j++)
    {
      xs_prob[i][j][total_xs] = xs_prob[i][j][scatter_xs] + xs_prob[i][j][fission_xs]
                              + xs_prob[i][j][radiation_xs];

      for(int k=0; k<xs_type_no; k++)
      {
        xs_inf[k] += xs_prob[i][j][k];
      }
    }

    for(int j=0; j<xs_type_no; j++)
    {
      xs_inf[j]         = xs_inf[j] * sample_no_real_inv + xs_back_ground[j];
      xs_inf_ave[i][j] += xs_inf[j];
      xs_inf_var[i][j] += xs_inf[j] * xs_inf[j];
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::set_xs_tot_table(int i, vector<vector<Real8> >& xs_val )
{
  vector<Real8> xs_tot_tmp;
  xs_tot_tmp.resize(sample_no);
  for(int j=0; j<sample_no; j++)
  {
    xs_tot_tmp[j] = xs_val[j][total_xs];
  }
  sort(xs_tot_tmp.begin(), xs_tot_tmp.end());

  xs_tot_min[i] = xs_tot_tmp[0];
  xs_tot_max[i] = xs_tot_tmp[sample_no - 1];

  xs_tot_table[i][0]        = digit_obj.get_adjusted_value(xs_tot_tmp[bin_no_sta], sig_fig, -1.0);
  xs_tot_table[i][bin_no-1] = static_cast<Real8>(1.0E6);
  if( xs_tot_table[i][0] < xs_tot_min[i] + min_sig_val )
  {
    xs_tot_table[i][0] = digit_obj.get_adjusted_value(xs_tot_tmp[bin_no_sta], sig_fig, +1.0);
  }

  int   ele_no              = bin_no_sta + bin_no_add[0];
  Real8 xs_tot_pre          = xs_tot_tmp[bin_no_sta];
  for(int j=1; j<bin_no_int-1; j++)
  {
    xs_tot_table[i][j] = digit_obj.get_adjusted_value(xs_tot_tmp[ele_no], sig_fig, -1.0);
    if( xs_tot_table[i][j] <= xs_tot_pre * 1.001 )
    {
      xs_tot_table[i][j] = 1.001 * xs_tot_pre;
    }
    xs_tot_pre = xs_tot_table[i][j];
    ele_no += bin_no_add[j];
  }
  xs_tot_tmp.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::check_xs_tot_table(int ene_no, int i)
{
  int ele_no     = ene_no;
  int ene_no_max = static_cast<int>(ene_grid_unreso.size());
  if( set_xs_tot_table_data_flg == 1 )
  {
    if( ele_no == 0 && static_cast<int>(xs_tot_table_all.size()) != ene_no_max )
    {
      string class_name = "ProbabilityTableCalculator";
      string func_name  = "check_xs_tot_table(int ene_no, int i)";

      ostringstream oss01,oss02;
      oss01 << ene_no_max;
      oss02 << static_cast<int>(xs_tot_table_all.size());
      string str_data01 = "Energy grid number                 : " + oss01.str();
      string str_data02 = "Energy grid number in xs_tot_table : " + oss02.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back("Energy grid number is not identical.");
      err_com.push_back("Please check the xs_tot_table data.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }
  else
  {
    ene_no_max = static_cast<int>(xs_tot_table_ene.size());

    Real8 ene_dif     = 0.0;
    Real8 ene_ref     = ene_grid_prob[ene_no];
    Real8 dif_min     = 1.0E+10;
    int   dif_min_pos = 0;

    if( ene_ref < min_value )
    {
      ene_ref = min_value;
    }

    ele_no = -1;
    for(int i=0; i<ene_no_max; i++)
    {
      ene_dif = fabs((xs_tot_table_ene[i] - ene_ref)/ene_ref);
      if( ene_dif < min_ene_dif )
      {
        ele_no = i;
        break;
      }
      else if( dif_min > ene_dif )
      {
        dif_min     = ene_dif;
        dif_min_pos = i;
      }
    }

    if( ele_no == -1 )
    {
      string class_name = "ProbabilityTableCalculator";
      string func_name  = "check_xs_tot_table(int ene_no, int i)";

      ostringstream oss01,oss02,oss03,oss04,oss05;
      oss01 << ene_no;
      oss02 << ene_ref;
      oss03 << dif_min_pos;
      oss04 << xs_tot_table_ene[dif_min_pos];
      oss05 << dif_min;
      string str_data01 = "Energy grid number                 : " + oss01.str();
      string str_data02 = "Energy [eV]                        : " + oss02.str();
      string str_data03 = "Energy grid number in xs_tot_table : " + oss03.str();
      string str_data04 = "Energy [eV]        in xs_tot_table : " + oss04.str();
      string str_data05 = "Relative difference                : " + oss05.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back(str_data04);
      err_com.push_back(str_data05);

      if( dif_min < 1.0E-3 )
      {
        ele_no = dif_min_pos;
        err_com.push_back("Relative difference is larger than min_ene_dif.");
        err_com.push_back("This calculation may be not appropriate.");
        err_obj.output_caution(class_name, func_name, err_com);
      }
      else
      {
        err_com.push_back("Relative difference is absolutely large.");
        err_com.push_back("Please check the xs_tot_table data.");
        err_obj.output_runtime_error(class_name, func_name, err_com);
      }
    }
  }

  xs_tot_table = xs_tot_table_all[ele_no];
  if( i == 0 && static_cast<int>(xs_tot_table.size()) != temp_no_int )
  {
    string class_name = "ProbabilityTableCalculator";
    string func_name  = "check_xs_tot_table(int ene_no, int i)";

    ostringstream oss01,oss02,oss03,oss04;
    oss01 << ele_no;
    oss02 << ene_no_max;
    oss03 << temp_no_int;
    oss04 << static_cast<int>(xs_tot_table.size());
    string str_data01 = "Energy grid number : " + oss01.str() + "/" + oss02.str();
    string str_data02 = "  Temperature data number                 : " + oss03.str();
    string str_data03 = "  Temperature data number in xs_tot_table : " + oss04.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("Temperature data number is not identical.");
    err_com.push_back("Please check the xs_tot_table data.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  if( static_cast<int>(xs_tot_table[i].size()) != bin_no_int )
  {
    string class_name = "ProbabilityTableCalculator";
    string func_name  = "check_xs_tot_table(int ele_no, int i)";

    ostringstream oss01,oss02,oss03,oss04,oss05,oss06;
    oss01 << ele_no;
    oss02 << ene_no_max;
    oss03 << i;
    oss04 << temp_no_int;
    oss05 << bin_no_int;
    oss06 << static_cast<int>(xs_tot_table[i].size());
    string str_data01 = "Energy grid number : " + oss01.str() + "/" + oss02.str();
    string str_data02 = "Temperature number : " + oss03.str() + "/" + oss04.str();
    string str_data03 = "  Bin number                 : " + oss05.str();
    string str_data04 = "  Bin number in xs_tot_table : " + oss06.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back("Bin number is not identical.");
    err_com.push_back("Please check the xs_tot_table data.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  sort(xs_tot_table[i].begin(), xs_tot_table[i].end());

  xs_tot_min[i] = xs_tot_table[i][0];
  xs_tot_max[i] = xs_tot_table[i][bin_no_int - 1];
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::calc_probability_and_bondarenko_table_data
                                   (int ene_no, int i, int lad_no, vector<Real8>& xs_back_ground)
{
  int                   pos_m;
  vector<int>           pos_p;
  vector<vector<Real> > xs_val;
  pos_p.resize(sample_no);
  xs_val.resize(sample_no);

  int fis_flg = 0;
  for(int j=0; j<sample_no; j++)
  {
    if( xs_prob[i][j][fission_xs] > min_sig_val * 1.1 )
    {
      fis_flg = 1;
      break;
    }
  }

  Real8 xs_tot_table_min = xs_tot_table[i][0] + min_value;
  for(int j=0; j<sample_no; j++)
  {
    xs_val[j].resize(xs_type_no);
    for(int k=0; k<xs_type_no; k++)
    {
      xs_val[j][k]   = xs_prob[i][j][k] + xs_back_ground[k];
      if( xs_val[j][k] < min_sig_val )
      {
        xs_val[j][k] = min_sig_val;
        if( k == fission_xs && fis_flg == 0 )
        {
          xs_val[j][k] = 0.0;
        }
      }
    }
  }

  if( lad_no == 0 )
  {
    if( set_xs_tot_table_data_flg == 0 )
    {
      set_xs_tot_table(i, xs_val);
    }
    else
    {
      check_xs_tot_table(ene_no, i);
    }
  }

  for(int j=0; j<sample_no; j++)
  {
    if( xs_val[j][total_xs] > xs_tot_table_min )
    {
      ti_obj.search_neighbor_value(xs_val[j][total_xs], xs_tot_table[i], pos_m, pos_p[j]);
      if( pos_m == 0 )
      {
        if( xs_val[j][total_xs] < xs_tot_table[i][0] )
        {
          pos_p[j] = 0;
        }
      }
    }
    else
    {
      pos_p[j] = 0;
      pos_m    = 0;
      if( xs_tot_min[i] > xs_val[j][total_xs] )
      {
        xs_tot_min[i] = xs_val[j][total_xs];
      }
    }

    if( xs_tot_max[i] < xs_val[j][total_xs] )
    {
      xs_tot_max[i] = xs_val[j][total_xs];
    }
  }

  //For calculation of bondarenko table and xs
  add_probability_table_data(i, xs_val, pos_p);

  //For calculation of bondarenko table and xs
  add_bondarenko_data(i, xs_val);

  //For debug
  //output_resonance_structure_each_ladder(ene_no, i, lad_no, xs_val);
  //output_average_xs_value_each_ladder(ene_no, i, lad_no, xs_val, pos_p);

  //For error calculation
  if( lad_no >= 0 ) //To skip test calculation of ProbabilityTableCalculatorTest.cpp
  {
    vector<Real8>  p_tab_stat;
    vector<vector<Real8> > p_tab_xs_stat, xs_stat;
    calc_probability_table_for_statistical_error(xs_val, pos_p,
                                                 p_tab_stat, p_tab_xs_stat, xs_stat);
    p_tab_stat_each_temp[i][lad_no]    = p_tab_stat;    //temp, lad_no, bin_no, xs_type
    p_tab_xs_stat_each_temp[i][lad_no] = p_tab_xs_stat; //temp, lad_no, bin_no, xs_type
    xs_stat_each_temp[i][lad_no]       = xs_stat;       //temp, lad_no, bin_no, xs_type

    p_tab_stat.clear();
    clr_obj.clear_vec_array2_real8(p_tab_xs_stat);
    clr_obj.clear_vec_array2_real8(xs_stat);
  }

  pos_p.clear();
  clr_obj.clear_vec_array2_real8(xs_val);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::output_resonance_structure_each_ladder
                                   ( int ene_no, int i, int lad_no, vector<vector<Real8> >& xs_val )
{
  if( ene_no < 0 || lad_no < 0 )
  {
    return;
  }
  
  int precision_no_temp = 2;
  int precision_no      = 6;

  //Open output file
  if( lad_no == 0 )
  {
    if( i==0 )
    {
      ostringstream oss_ene_no;
      oss_ene_no << ene_no+1;

      string debug_file_name = "reso_each_ladder_e";
      if( ene_no+1 < 10 )
      {
        debug_file_name += "0";
      }

      debug_file_name += oss_ene_no.str() + ".txt";
      fout_debug_reso.open(debug_file_name.c_str());

      fout_debug_reso.setf(ios::showpoint);
      fout_debug_reso.setf(ios::scientific);
    }
  }

  fout_debug_reso.precision(precision_no_temp);
  fout_debug_reso << "temp: " << temp_data[i] << ", lad: " << lad_no+1 << endl;

  fout_debug_reso.precision(precision_no);
  for(int j=0; j<sample_no; j++)
  {
    string space_data = "";
    if( j+1 < 10000 )
    {
      space_data = " ";
      if( j+1 < 1000 )
      {
        space_data = "  ";
        if( j+1 < 100 )
        {
          space_data = "   ";
          if( j+1 < 10 )
          {
            space_data = "    ";
          }
        }
      }
    }

    fout_debug_reso << "  " << space_data << j+1 << "  " << ene_grid_each_ladder[j];
    for(int k=0; k<xs_type_no; k++)
    {
      //fout_debug_reso << "  " <<  xs_val[j][k];
      fout_debug_reso << "  " <<  xs_prob[i][j][k];
    }
    fout_debug_reso << endl;
  }
  fout_debug_reso << endl;

  //Close output file
  if( lad_no+1 == ladder_no_int )
  {
    fout_debug_reso.close();
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::output_average_xs_value_each_ladder
                                   ( int ene_no, int i, int lad_no, vector<vector<Real8> >& xs_val,
                                     vector<int>& pos )
{
  if( ene_no < 0 || lad_no < 0 )
  {
    return;
  }
  
  //int precision_no_temp = 2;
  int precision_no      = 6;

  //Open output file
  if( lad_no == 0 )
  {
    if( i==0 )
    {
      ostringstream oss_ene_no;
      oss_ene_no << ene_no+1;

      string debug_file_name = "ave_xs_each_ladder_e";
      if( ene_no+1 < 10 )
      {
        debug_file_name += "0";
      }

      //debug_file_name += oss_ene_no.str() + ".txt";
      debug_file_name += oss_ene_no.str() + ".csv";
      fout_debug_ave_xs.open(debug_file_name.c_str());

      fout_debug_ave_xs.setf(ios::showpoint);
      fout_debug_ave_xs.setf(ios::scientific);
    }
  }


  //Calculation of average xs value in each energy bin
  vector<Real8>                   p_tab_each;
  vector<vector<Real8> >          xs_ave;
  vector<vector<vector<Real8> > > xs_each_bin;
  calc_probability_table_and_average_xs_value_each_ladder
    ( xs_val, pos, p_tab_each, xs_ave, xs_each_bin );

  // Output pobability and average cross section in each energy bin (start) //
  fout_debug_ave_xs.precision(precision_no);
  if( lad_no == 0 && i==0 )
  {
    for(int j=0; j<bin_no; j++)
    {
      ostringstream oss_bin_no;
      oss_bin_no << j+1;
      if( j+1 < 10 )
      {
        //fout_debug_ave_xs << "prob_bin_0" << oss_bin_no.str() << ", xs_ave_bin_0" << oss_bin_no.str() << ", ";
        fout_debug_ave_xs << "prob_bin_0" << oss_bin_no.str() << ", ";
      }
      else
      {
        //fout_debug_ave_xs << "prob_bin_"  << oss_bin_no.str() << ", xs_ave_bin_"  << oss_bin_no.str() << ", ";
        fout_debug_ave_xs << "prob_bin_"  << oss_bin_no.str() << ", ";
      }
    }

    for(int j=0; j<bin_no; j++)
    {
      ostringstream oss_bin_no;
      oss_bin_no << j+1;
      if( j+1 < 10 )
      {
        fout_debug_ave_xs << "xs_ave_bin_0" << oss_bin_no.str() << ", ";
      }
      else
      {
        fout_debug_ave_xs << "xs_ave_bin_"  << oss_bin_no.str() << ", ";
      }
    }
    fout_debug_ave_xs << endl;
  }

  if( i==0 )
  {
    for(int j=0; j<bin_no; j++)
    {
      //fout_debug_ave_xs << p_tab_each[j] << ", " << xs_ave[j][total_xs] << ", ";
      fout_debug_ave_xs << p_tab_each[j] << ", ";
    }

    for(int j=0; j<bin_no; j++)
    {
      fout_debug_ave_xs << xs_ave[j][total_xs] << ", ";
    }
    fout_debug_ave_xs << endl;
  }
  // Output pobability and average cross section in each energy bin (end) //


/*
  // Output average xs and xs at each sample (start) //
  if( lad_no == 0 )
  {
    if( i==0 )
    {
      fout_debug_ave_xs << "total_temp_no: "  << temp_no_int   << "  total_bin_no: " << bin_no
                 << "  total_lad_no: " << ladder_no_int << "  sample_no: "    << sample_no << endl;
    }

    fout_debug_ave_xs.precision(precision_no_temp);
    fout_debug_ave_xs << "  temp: " << temp_data[i] << endl;

    fout_debug_ave_xs << "  xs_boundary:";
    fout_debug_ave_xs.precision(precision_no);
    for(int j=0; j<bin_no-1; j++)
    {
      fout_debug_ave_xs << " " << xs_tot_table[i][j];
    }
    fout_debug_ave_xs << endl;
  }

  //Output ladder number and temperature
  fout_debug_ave_xs.precision(precision_no_temp);
  fout_debug_ave_xs << "    " << "lad_no: " << lad_no << "  temp: " << temp_data[i] << endl;

  //Output data number in each energy bin
  fout_debug_ave_xs << "      " << "data_no:";
  for(int j=0; j<bin_no; j++)
  {
    fout_debug_ave_xs << " " << static_cast<int>(xs_each_bin[j][total_xs].size());
  }
  fout_debug_ave_xs << endl;

  //Output average cross section in each energy bin
  fout_debug_ave_xs.precision(precision_no);
  fout_debug_ave_xs << "      " << "xs_ave:";
  for(int j=0; j<bin_no; j++)
  {
    fout_debug_ave_xs << " " << xs_ave[j][total_xs];
  }
  fout_debug_ave_xs << endl;

  for(int j=0; j<bin_no; j++)
  {
    fout_debug_ave_xs << "       ";
    for(int k=0; k<static_cast<int>(xs_each_bin[j][total_xs].size()); k++)
    {
      fout_debug_ave_xs << " " << xs_each_bin[j][total_xs][k];
    }
    fout_debug_ave_xs << endl;
  }
  fout_debug_ave_xs << endl;
  // Output average xs and xs at each sample (end) //
*/

  //Close output file
  if( lad_no+1 == ladder_no_int )
  {
    fout_debug_ave_xs.close();
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::calc_probability_table_for_statistical_error
                                   ( vector<vector<Real8> >& xs_val, vector<int>& pos,
                                     vector<Real8>& p_tab_stat,
                                     vector<vector<Real8> >& p_tab_xs_stat,
                                     vector<vector<Real8> >& xs_stat)
{
  vector<Real8>                   p_tab_each;
  vector<vector<Real8> >          xs_ave;
  vector<vector<vector<Real8> > > xs_each;
  calc_probability_table_and_average_xs_value_each_ladder(xs_val, pos, p_tab_each, xs_ave, xs_each);

  clr_obj.clear_vec_array2_real8(p_tab_xs_stat);

  int i_max = static_cast<int>(xs_ave.size()); //bin_no
  p_tab_xs_stat.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(xs_ave[i].size()); //xs_type_no
    p_tab_xs_stat[i].resize(j_max);
    for(int j=0; j<j_max; j++)
    {
      p_tab_xs_stat[i][j] = p_tab_each[i] * xs_ave[i][j];
    }
  }

  p_tab_stat = p_tab_each;
  xs_stat    = xs_ave; 

  p_tab_each.clear();
  clr_obj.clear_vec_array2_real8(xs_ave);
  clr_obj.clear_vec_array3_real8(xs_each);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::calc_probability_table_and_average_xs_value_each_ladder
                                   ( vector<vector<Real8> >& xs_val, vector<int>& pos,
                                     vector<Real8>&                   p_tab_each,
                                     vector<vector<Real8> >&          xs_ave, 
                                     vector<vector<vector<Real8> > >& xs_each)
{
  xs_ave.resize(bin_no);
  xs_each.resize(bin_no);
  for(int j=0; j<bin_no; j++)
  {
    xs_ave[j].resize(xs_type_no);
    xs_each[j].resize(xs_type_no);
    for(int k=0; k<xs_type_no; k++)
    {
      xs_ave[j][k] = 0.0;
    }
  }

  for(int j=0; j<sample_no; j++)
  {
    int ele_no = pos[j];
    for(int k=0; k<xs_type_no; k++)
    {
      xs_ave[ele_no][k] += xs_val[j][k];
      xs_each[ele_no][k].push_back(xs_val[j][k]);
    }
  }

  for(int j=0; j<bin_no; j++)
  {
    if( static_cast<int>(xs_each[j][total_xs].size()) > 0 )
    {
      for(int k=0; k<xs_type_no; k++)
      {
        xs_ave[j][k] /= static_cast<Real8>(xs_each[j][total_xs].size());
      }
    }
  }

  p_tab_each.resize(bin_no);
  for(int j=0; j<bin_no; j++)
  {
    p_tab_each[j] = static_cast<Real8>(xs_each[j][total_xs].size()) * sample_no_real_inv;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int ProbabilityTableCalculator::check_statistical_error(int ene_no, int lad_no)
{
  int lad_no_cur = lad_no+1;
  if( (lad_no_cur)%calc_statistical_error_interval != 0 )
  {
    return -1;
  }
  else if( static_err < min_value )
  {
    return -2;
  }

  int calc_err_mode = 12;
  //  0: uncertainty of p_tab using bootstrap method
  //  1: uncertainty of p_tab using jacknife method
  //  2: uncertainty of p_tab using central limit theorem (clt) method
  // 10: uncertainty of p_tab * xs using bootstrap method
  // 11: uncertainty of p_tab * xs using jacknife method
  // 12: uncertainty of p_tab * xs using central limit theorem (clt) method
  // 20: uncertainty of xs using bootstrap method
  // 21: uncertainty of xs using jacknife method
  // 22: uncertainty of xs using central limit theorem (clt) method
  //100: all cases (debug mode)

  for(int t=0; t<temp_no_int; t++)
  {
    for(int i=0; i<xs_type_no; i++)
    {
      int zero_data_flg = 0;
      vector<vector<Real8> > p_tab_stat, p_tab_xs_stat, xs_stat; //lad_no, bin_no
      p_tab_stat.resize(lad_no_cur);
      p_tab_xs_stat.resize(lad_no_cur);
      xs_stat.resize(lad_no_cur);
      for(int j=0; j<lad_no_cur; j++)
      {
        p_tab_stat[j].resize(bin_no);
        p_tab_xs_stat[j].resize(bin_no);
        xs_stat[j].resize(bin_no);
        for(int k=0; k<bin_no; k++)
        {
          //p_tab_stat_each_temp; //temp, lad_no, bin_no, xs_type
          p_tab_stat[j][k]    = p_tab_stat_each_temp[t][j][k];
          p_tab_xs_stat[j][k] = p_tab_xs_stat_each_temp[t][j][k][i];
          xs_stat[j][k]       = xs_stat_each_temp[t][j][k][i];

          if( zero_data_flg == 0 && fabs(p_tab_xs_stat[j][k]) > min_value )
          {
            zero_data_flg = 1;
          }
        }
      }

      //Skip all zero data, e.g., fission xs of non-fissile nuclide
      if( zero_data_flg == 0 )
      {
        continue;
      }

      vector<Real8> ave_data, err_data;
      Real8         err_ave,  err_max;

      //For p_tab
      if( calc_err_mode == 0 || calc_err_mode == 100 )
      {
        boot_obj.calc_bootstrap_with_ave_and_max
          (sample_no_bootstrap, p_tab_stat, ave_data, err_data, err_ave, err_max);
        string name_str_bootstrap = "p_tab by bootstrap";
        output_statistical_error(name_str_bootstrap, ene_no, lad_no_cur, t, i,
                                 ave_data, err_data, err_ave, err_max);
      }

      if( calc_err_mode == 1 || calc_err_mode == 100 )
      {
        boot_obj.calc_jack_knife_with_ave_and_max
          (p_tab_stat, ave_data, err_data, err_ave, err_max);
        string name_str_jacknife = "p_tab by jacknife";
        output_statistical_error(name_str_jacknife, ene_no, lad_no_cur, t, i,
                                 ave_data, err_data, err_ave, err_max);
      }

      if( calc_err_mode == 2 || calc_err_mode == 100 )
      {
        boot_obj.calc_average_and_error_clt_with_ave_and_max
          (p_tab_stat, ave_data, err_data, err_ave, err_max);
        string name_str_clt = "p_tab by clt";
        output_statistical_error(name_str_clt, ene_no, lad_no_cur, t, i,
                                 ave_data, err_data, err_ave, err_max);
      }

      //For p_tab * xs
      if( calc_err_mode == 10 || calc_err_mode == 100 )
      {
        boot_obj.calc_bootstrap_with_ave_and_max
          (sample_no_bootstrap, p_tab_xs_stat, ave_data, err_data, err_ave, err_max);
        string name_str_bootstrap = "p_tab * xs by bootstrap";
        output_statistical_error(name_str_bootstrap, ene_no, lad_no_cur, t, i,
                                 ave_data, err_data, err_ave, err_max);
      }

      if( calc_err_mode == 11 || calc_err_mode == 100 )
      {
        boot_obj.calc_jack_knife_with_ave_and_max
          (p_tab_xs_stat, ave_data, err_data, err_ave, err_max);
        string name_str_jacknife = "p_tab * xs by jacknife";
        output_statistical_error(name_str_jacknife, ene_no, lad_no_cur, t, i,
                                 ave_data, err_data, err_ave, err_max);
      }

      if( calc_err_mode == 12 || calc_err_mode == 100 )
      {
        boot_obj.calc_average_and_error_clt_with_ave_and_max
          (p_tab_xs_stat, ave_data, err_data, err_ave, err_max);
        string name_str_clt = "p_tab * xs by clt";
        output_statistical_error(name_str_clt, ene_no, lad_no_cur, t, i,
                                 ave_data, err_data, err_ave, err_max);
      }

      //For xs
      if( calc_err_mode == 20 || calc_err_mode == 100 )
      {
        boot_obj.calc_bootstrap_with_ave_and_max
          (sample_no_bootstrap, xs_stat, ave_data, err_data, err_ave, err_max);
        string name_str_bootstrap = "xs by bootstrap";
        output_statistical_error(name_str_bootstrap, ene_no, lad_no_cur, t, i,
                                 ave_data, err_data, err_ave, err_max);
      }

      if( calc_err_mode == 21 || calc_err_mode == 100 )
      {
        boot_obj.calc_jack_knife_with_ave_and_max
          (xs_stat, ave_data, err_data, err_ave, err_max);
        string name_str_jacknife = "xs by jacknife";
        output_statistical_error(name_str_jacknife, ene_no, lad_no_cur, t, i,
                                 ave_data, err_data, err_ave, err_max);
      }

      if( calc_err_mode == 22 || calc_err_mode == 100 )
      {
        boot_obj.calc_average_and_error_clt_with_ave_and_max
          (xs_stat, ave_data, err_data, err_ave, err_max);
        string name_str_clt = "xs by clt";
        output_statistical_error(name_str_clt, ene_no, lad_no_cur, t, i,
                                 ave_data, err_data, err_ave, err_max);
      }

      ave_data.clear();
      err_data.clear();
      clr_obj.clear_vec_array2_real8(p_tab_stat);
      clr_obj.clear_vec_array2_real8(p_tab_xs_stat);
      clr_obj.clear_vec_array2_real8(xs_stat);

      if( err_max > static_err )
      {
        return 0; //probability table is not converged
      }
    }
  }

  //return 0; //For debug
  return 1; //probability table is converged
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::output_statistical_error
                                   (string method_name_str, int ene_no, int lad_no, int temp_no, int xs_no,
                                    vector<Real8> ave_data, vector<Real8> err_data,
                                    Real8 err_ave, Real8 err_max)
{
  cout.precision(6);
  cout.setf(ios::showpoint);

  string space_ene_str = "";
  if( ene_no+1 < 100 )
  {
    space_ene_str = space_ene_str + " ";
    if( ene_no+1 < 10 )
    {
      space_ene_str = space_ene_str + " ";
    }
  }

  string space_lad_str = "";
  if( lad_no < 10000 )
  {
    space_lad_str = space_lad_str + " ";
    if( lad_no < 1000 )
    {
      space_lad_str = space_lad_str + " ";
      if( lad_no < 100 )
      {
        space_lad_str = space_lad_str + " ";
        if( lad_no < 10 )
        {
          space_lad_str = space_lad_str + " ";
        }
      }
    }
  }

  cout << "      "
//       << "ene_no =" << space_ene_str << ene_no+1 << ", "
       << "temp = "  << temp_data[temp_no] << ", "
       << "lad_no =" << space_lad_str << lad_no << " : ";

  cout << "statistical error of " << method_name_str;
  if( xs_no == total_xs )
  {
    cout << " (tot)";
  }
  else if( xs_no == scatter_xs )
  {
    cout << " (ela)";
  }
  else if( xs_no == fission_xs )
  {
    cout << " (fis)";
  }
  else if( xs_no == radiation_xs )
  {
    cout << " (rad)";
  }

  cout.precision(3);
  cout.setf(ios::showpoint);
  cout.setf(ios::scientific);
  cout << " = " << err_ave << " / " << err_max << " (ave / max)" << endl;

//  int i_max = static_cast<int>(ave_data.size());
//  for(int i=0; i<i_max; i++)
//  {
//    string space_err_str = "    " + method_name_str + " :";
//    if( i+1 < 100 )
//    {
//      space_err_str = space_err_str + " ";
//      if( i+1 < 10 )
//      {
//        space_err_str = space_err_str + " ";
//      }
//    }
//
//    cout << space_err_str << i+1 << " / " << i_max << " : " << ave_data[i] << " / " << err_data[i] << endl;
//  }

  cout.unsetf(ios::showpoint);
  cout.unsetf(ios::scientific);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::add_probability_table_data( int i, vector<vector<Real8> >& xs_val,
                                                             vector<int>& pos )
{
  for(int j=0; j<sample_no; j++)
  {
    int ele_no = pos[j];
    prob_table_sample_no[i][ele_no]++;
    for(int k=0; k<xs_type_no; k++)
    {
      prob_table[i][ele_no][k] += xs_val[j][k];
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::calc_probability_table_data(vector<Real8>& xs_unreso)
{
  for(int i=0; i<temp_no_int; i++)
  {
    for(int j=0; j<bin_no_int; j++)
    {
      if( prob_table_sample_no[i][j] > 0 )
      {
        Real8 sample_no_inv = 1.0 / static_cast<Real8>(prob_table_sample_no[i][j]);
        for(int k=0; k<xs_type_no; k++)
        {
          prob_table[i][j][k] *= sample_no_inv;
        }
      }
    }
  }

  //adjust_probability_table_data(xs_unreso);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::adjust_probability_table_data(vector<Real8>& xs_unreso)
{
  vector<Real8> adjust_vec;
  adjust_vec.resize(xs_type_no);
  for(int i=0; i<xs_type_no; i++)
  {
    adjust_vec[i] = xs_unreso[i] - bondarenko_table[0][0][i];
  }

  for(int i=0; i<temp_no_int; i++)
  {
    xs_tot_min[i] += adjust_vec[total_xs];
    for(int j=0; j<bin_no_int; j++)
    {
      for(int k=0; k<xs_type_no; k++)
      {
        prob_table[i][j][k] -= adjust_vec[k];
      }
    }
  }
  adjust_vec.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::add_bondarenko_data(int i, vector<vector<Real8> >& xs_val)
{
  Real8 coef_sig_zero, coef_sig_zero_p1, coef_sig_zero_sq;
  for(int j=0; j<sample_no; j++)
  {
    Real8 xs_tot  = xs_val[j][total_xs];
    Real8 xs_scat = xs_val[j][scatter_xs];
    Real8 xs_fis  = xs_val[j][fission_xs];
    Real8 xs_rad  = xs_val[j][radiation_xs];

    //Modify small cross section data to appropriately calculate P1 bondarenko cross section
    //When the back ground cross section and sampled total cross section are so small,
    //this small total cross section affects p1 total Bondarenko self-shilding cross section.
    //To avoid such problem, small cross section is modified.
    Real8 xs_tot_p1 = xs_tot;
    if( xs_tot_p1 < xs_data_back[total_xs] * min_xs_coef )
    {
      xs_tot_p1 = xs_data_back[total_xs] * min_xs_coef;
    }

    for(int k=0; k<sig_zero_no_int; k++)
    {
      coef_sig_zero    = sig_zero_data[k] / (sig_zero_data[k] + xs_tot);
      coef_sig_zero_p1 = sig_zero_data[k] / (sig_zero_data[k] + xs_tot_p1);
      coef_sig_zero_sq = coef_sig_zero_p1 * coef_sig_zero_p1;
      bondarenko_data[i][k][0] += xs_tot    * coef_sig_zero;
      bondarenko_data[i][k][1] += xs_scat   * coef_sig_zero;
      bondarenko_data[i][k][2] += xs_fis    * coef_sig_zero;
      bondarenko_data[i][k][3] += xs_rad    * coef_sig_zero;
      bondarenko_data[i][k][4] += xs_tot_p1 * coef_sig_zero_sq;
      bondarenko_data[i][k][5] += coef_sig_zero;
      bondarenko_data[i][k][6] += coef_sig_zero_sq;
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::calc_bondarenko_table()
{
  for(int i=0; i<temp_no_int; i++)
  {
    for(int j=0; j<sig_zero_no_int; j++)
    {
      Real8 tmp_inv = 1.0 / bondarenko_data[i][j][5];
      bondarenko_table[i][j][0] = bondarenko_data[i][j][0] * tmp_inv;
      bondarenko_table[i][j][1] = bondarenko_data[i][j][1] * tmp_inv;
      bondarenko_table[i][j][2] = bondarenko_data[i][j][2] * tmp_inv;
      bondarenko_table[i][j][3] = bondarenko_data[i][j][3] * tmp_inv;
      bondarenko_table[i][j][4] = bondarenko_data[i][j][4] / bondarenko_data[i][j][6];
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::calc_bondarenko_xs()
{
  vector<Real8> bondarenko_xs_data;
  bondarenko_xs_data.resize(bondarenko_xs_data_no+2);

  vector<vector<Real8> > sample_no_ratio =  calc_prob_table_sample_no_ratio();
  Real8 tmp_inv, tmp_inv_sq;
  for(int i=0; i<temp_no_int; i++)
  {
    for(int j=0; j<sig_zero_no_int; j++)
    {
      for(int k=0; k<bondarenko_xs_data_no+2; k++)
      {
        bondarenko_xs_data[k] = 0.0;
      }

      for(int k=0; k<bin_no_int; k++)
      {
        if( fabs(prob_table[i][k][total_xs]) > min_value )
        {
          tmp_inv       = sig_zero_data[j] / (sig_zero_data[j] + prob_table[i][k][total_xs]);
          tmp_inv_sq    = tmp_inv * tmp_inv;

          tmp_inv      *= sample_no_ratio[i][k];
          tmp_inv_sq   *= sample_no_ratio[i][k];

          bondarenko_xs_data[0] += prob_table[i][k][total_xs]     * tmp_inv;
          bondarenko_xs_data[1] += prob_table[i][k][scatter_xs]   * tmp_inv;
          bondarenko_xs_data[2] += prob_table[i][k][fission_xs]   * tmp_inv;
          bondarenko_xs_data[3] += prob_table[i][k][radiation_xs] * tmp_inv;
          bondarenko_xs_data[4] += prob_table[i][k][total_xs]     * tmp_inv_sq;
          bondarenko_xs_data[5] += tmp_inv;
          bondarenko_xs_data[6] += tmp_inv_sq;
        }
      }

      tmp_inv = 1.0 / bondarenko_xs_data[5];
      bondarenko_xs[i][j][0] = bondarenko_xs_data[0] * tmp_inv;
      bondarenko_xs[i][j][1] = bondarenko_xs_data[1] * tmp_inv;
      bondarenko_xs[i][j][2] = bondarenko_xs_data[2] * tmp_inv;
      bondarenko_xs[i][j][3] = bondarenko_xs_data[3] * tmp_inv;
      bondarenko_xs[i][j][4] = bondarenko_xs_data[4] / bondarenko_xs_data[6];
    }
  }
  bondarenko_xs_data.clear();
  clr_obj.clear_vec_array2_real8(sample_no_ratio);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::copy_probability_table_data( int ene_no, vector<Real8>& xs_unreso,
                                                              vector<Real8>& xs_back_ground )
{
  //Calculation of xs in unresolved resonance region
  vector<Real8> xs_unreso_mod  = xs_unreso;
  xs_unreso_mod[total_xs]      = xs_unreso[scatter_xs] + xs_unreso[fission_xs] + xs_unreso[radiation_xs]
                               + xs_back_ground[total_xs]   + xs_potential;
  xs_unreso_mod[scatter_xs]   += xs_back_ground[scatter_xs] + xs_potential;
  xs_unreso_mod[fission_xs]   += xs_back_ground[fission_xs];
  xs_unreso_mod[radiation_xs] += xs_back_ground[radiation_xs];

  //Calculation of heat probability
  calc_probability_heat(ene_no, xs_unreso_mod);
  mod_probability_heat(ene_no);

  //Copy data to ProbabilityTableDataContainer
  ProbabilityTableDataContainer prob_table_data_obj;

  prob_table_data_obj.set_ene_grid(ene_grid_prob[ene_no]);
  prob_table_data_obj.set_nrest(nrest);

  prob_table_data_obj.set_temp(temp_data);
  prob_table_data_obj.set_sig_zero(sig_zero_data);

  prob_table_data_obj.set_xs_unreso(xs_unreso_mod);

  prob_table_data_obj.set_xs_back(xs_back_ground);

  prob_table_data_obj.set_xs_tot_min(xs_tot_min);
  prob_table_data_obj.set_xs_tot_max(xs_tot_max);
  for(int i=0; i<temp_no_int; i++)
  {
    xs_tot_table[i][bin_no-1] = xs_tot_max[i];
  }
  prob_table_data_obj.set_xs_tot_table(xs_tot_table);

  prob_table_data_obj.set_xs_inf_ave(xs_inf_ave);
  prob_table_data_obj.set_xs_inf_var(xs_inf_var);

  prob_table_data_obj.set_prob_table_sample_no(calc_prob_table_sample_no_ratio());

  prob_table_data_obj.set_prob_heat(prob_heat);

  prob_table_data_obj.set_prob_table(prob_table);
  prob_table_data_obj.set_bondarenko_xs_direct(bondarenko_table);
  prob_table_data_obj.set_bondarenko_xs_prob(bondarenko_xs);

  //Modify probability table for PENDF file
  vector<vector<vector<Real8> > > prob_table_mod       = prob_table;
  vector<vector<vector<Real8> > > bondarenko_table_mod = bondarenko_table; //direct sampling
  //vector<vector<vector<Real8> > > bondarenko_table_mod = bondarenko_xs;    //using probability table
  mod_probability_and_bondarenko_table(xs_unreso_mod, prob_table_mod, bondarenko_table_mod);
  prob_table_data_obj.set_bondarenko_table(bondarenko_table_mod);
  prob_table_data_obj.set_prob_table_mod(prob_table_mod);
  clr_obj.clear_vec_array3_real8(bondarenko_table_mod);
  clr_obj.clear_vec_array3_real8(prob_table_mod);

  prob_data_obj.set_prob_table_data_obj(ene_no, prob_table_data_obj);
  prob_table_data_obj.clear();
  xs_unreso_mod.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::mod_probability_and_bondarenko_table
                                   ( vector<Real8>& xs_unreso,
                                     vector<vector<vector<Real8> > >& p_tab_mod,
                                     vector<vector<vector<Real8> > >& b_tab_mod )
{
  vector<vector<vector<Real8> > > b_tab_ori = b_tab_mod;
  vector<Real8> xs_unreso_coef = xs_unreso;
  xs_unreso_coef.push_back(xs_unreso[0]);
  for(int i=0; i<temp_no_int; i++)
  {
    //Modify probability table
    for(int k=0; k<xs_type_no; k++)
    {
      Real8 coef_p_tab = 1.0;
      if( fabs(b_tab_ori[i][0][k]) > min_value )
      {
        coef_p_tab = xs_unreso[k] / b_tab_ori[i][0][k];
      }

      for(int j=0; j<bin_no_int; j++)
      {
        p_tab_mod[i][j][k] *= coef_p_tab;
      }
    }

    //Modify bondarenko table
    for(int k=0; k<bondarenko_table_data_no; k++)
    {
      Real8 coef_b_tab = 1.0;
      if( fabs(b_tab_ori[i][0][k]) > min_value )
      {
        coef_b_tab = xs_unreso_coef[k] / b_tab_ori[i][0][k];
      }

      for(int j=0; j<sig_zero_no_int; j++)
      {
        b_tab_mod[i][j][k] *= coef_b_tab;
      }
    }
  }
  clr_obj.clear_vec_array3_real8(b_tab_ori);
  xs_unreso_coef.clear();

  //Modified prob_table deviding by bondarenko table (SigZero=S0(infinity))
  //when the self shieldinf flg (LSSF) is equal to 1.
  //(File 3 contains the entire dilute cross section for the unresolved resonance region)
  if( self_shielding_flg_ori == 1 )
  {
    for(int i=0; i<temp_no_int; i++)
    {
      for(int k=0; k<xs_type_no; k++)
      {
        Real8 coef_real = b_tab_mod[i][0][k];
        if( fabs(coef_real) > min_value )
        {
          coef_real = 1.0 / coef_real;
          for(int j=0; j<bin_no_int; j++)
          {
            p_tab_mod[i][j][k] *= coef_real;
          }
        }
        else
        {
          for(int j=0; j<bin_no_int; j++)
          {
            p_tab_mod[i][j][k] = 1.0;
          }
        }
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::calc_probability_heat(int ene_no, vector<Real8> xs_unreso_mod)
{
  prob_heat.resize(temp_no_int);
  for(int i=0; i<temp_no_int; i++)
  {
    prob_heat[i].resize(bin_no_int);
    for(int j=0; j<bin_no_int; j++)
    {
      prob_heat[i][j] = 0.0;
    }
  }

  int check_heat_xs_flg = check_heat_xs();
  if( check_heat_xs_flg <= 0 )
  {
    for(int i=0; i<temp_no_int; i++)
    {
      for(int j=0; j<bin_no_int; j++)
      {
        prob_heat[i][j] = 1.0;
      }
    }

    return;
  }

  vector<Real> heat_xs = calc_heat_xs(ene_no);

  if( check_heat_xs_flg == 1 )
  {
    if( self_shielding_flg_ori == 1 )
    {
      for(int i=0; i<temp_no_int; i++)
      {
        for(int j=0; j<bin_no_int; j++)
        {
          prob_heat[i][j] = 1.0;
        }
      }
    }
    else
    {
      for(int i=0; i<temp_no_int; i++)
      {
        for(int j=0; j<bin_no_int; j++)
        {
          prob_heat[i][j] = heat_xs[total_xs] / bondarenko_xs[i][0][total_xs];
        }
      }
    }
  }
  else if( check_heat_xs_flg == 2 )
  {
    vector<vector<vector<Real8> > > prob_table_mod    = prob_table;
    vector<vector<vector<Real8> > > bondarenko_xs_mod = bondarenko_xs;
    mod_probability_and_bondarenko_table(xs_unreso_mod, prob_table_mod, bondarenko_xs_mod);
    clr_obj.clear_vec_array3_real8(bondarenko_xs_mod);

    for(int i=0; i<temp_no_int; i++)
    {
      for(int j=0; j<bin_no_int; j++)
      {
        prob_heat[i][j] = heat_xs[total_xs]
                        - heat_xs[scatter_xs] - heat_xs[fission_xs] - heat_xs[radiation_xs];

        for(int k=1; k<xs_type_no; k++)
        {
          Real heat_xs_add = heat_xs[k] * prob_table_mod[i][j][k];
          if( self_shielding_flg_ori != 1 && fabs(bondarenko_xs[i][0][k]) > min_value )
          {
            heat_xs_add /= bondarenko_xs[i][0][k];
          }
          prob_heat[i][j] += heat_xs_add;
        }

        if( fabs(prob_table_mod[i][j][total_xs]) > min_value )
        {
          prob_heat[i][j] /= prob_table_mod[i][j][total_xs];
        }

        if( self_shielding_flg_ori == 1 )
        {
          prob_heat[i][j] /= heat_xs[total_xs];
        }
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int ProbabilityTableCalculator::check_heat_xs()
{
  int check_heat_xs_flg = 0;

  vector<CrossSectionDataContainer> xs_data_obj
                                      = nucl_data_obj.get_nucl_reaction_data_obj().get_xs_data_obj();

  int heat_tot_flg = -1;
  int heat_ela_flg = -1;
  int heat_fis_flg = -1;
  int heat_rad_flg = -1;
  for(int i=0; i<static_cast<int>(xs_data_obj.size()); i++)
  {
    if( xs_data_obj[i].get_reaction_type() == heat_tot )
    {
      heat_tot_flg = 1;
    }
    else if( xs_data_obj[i].get_reaction_type() == heat_ela )
    {
      heat_ela_flg = 1;
    }
    else if( xs_data_obj[i].get_reaction_type() == heat_fis )
    {
      heat_fis_flg = 1;
    }
    else if( xs_data_obj[i].get_reaction_type() == heat_rad )
    {
      heat_rad_flg = 1;
    }
  }

  if( heat_tot_flg > 0 )
  {
    check_heat_xs_flg = 1;
  }

  if( heat_ela_flg > 0 || heat_fis_flg > 0 || heat_rad_flg > 0 )
  {
    check_heat_xs_flg = 2;
  }

  return check_heat_xs_flg;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<Real> ProbabilityTableCalculator::calc_heat_xs(int ene_no)
{
  vector<Real> heat_xs;
  heat_xs.resize(xs_type_no);
  for(int i=0; i<xs_type_no; i++)
  {
    heat_xs[i] = 0.0;
  }

  vector<CrossSectionDataContainer> xs_data_obj
                                      = nucl_data_obj.get_nucl_reaction_data_obj().get_xs_data_obj();

  for(int i=0; i<static_cast<int>(xs_data_obj.size()); i++)
  {
    Integer reaction_type = xs_data_obj[i].get_reaction_type();
    if( reaction_type == heat_tot || reaction_type == heat_ela ||
        reaction_type == heat_fis || reaction_type == heat_rad )
    {
      int xs_type = total_xs;
      if( xs_data_obj[i].get_reaction_type() == heat_ela )
      {
        xs_type = scatter_xs;
      }
      else if( xs_data_obj[i].get_reaction_type() == heat_fis )
      {
        xs_type = fission_xs;
      }
      else if( xs_data_obj[i].get_reaction_type() == heat_rad )
      {
        xs_type = radiation_xs;
      }

      vector<Integer> xs_range_data = xs_data_obj[i].get_xs_range_data();
      vector<Integer> xs_int_data   = xs_data_obj[i].get_xs_int_data();
      vector<Real>    xs_ene_data   = xs_data_obj[i].get_xs_ene_data();
      vector<Real>    xs_data       = xs_data_obj[i].get_xs_data();

      ti_obj.interpolation_tab1(ene_grid_prob[ene_no], heat_xs[xs_type],
                                xs_range_data, xs_int_data, xs_ene_data, xs_data);
    }
  }

  return heat_xs;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::mod_probability_heat(int ene_no)
{
  int skip_mod_probability_heat_flg = 0;
  for(int i=0; i<temp_no_int; i++)
  {
    for(int j=0; j<bin_no_int; j++)
    {
      if( fabs(prob_heat[i][j]) > min_value )
      {
        skip_mod_probability_heat_flg = 1;
        break;
      }
    }
  }

  if( skip_mod_probability_heat_flg == 0 )
  {
    return;
  }

  vector<int>  prob_heat_check_flg;
  prob_heat_check_flg.resize(temp_no_int);
  for(int i=0; i<temp_no_int; i++)
  {
    prob_heat_check_flg[i] = 0;

    for(int j=0; j<bin_no_int; j++)
    {
      if( prob_heat[i][j] < min_value )
      {
        prob_heat_check_flg[i] = 1;
        break;
      }
    }
  }

  int output_err_flg = 0;
  for(int i=0; i<temp_no_int; i++)
  {
    if( prob_heat_check_flg[i] > 0 && output_err_flg == 0 )
    {
      output_err_flg = 1; //Skip other temperature

      string class_name = "ProbabilityTableCalculator";
      string func_name  = "mod_probability_heat(int ene_no)";

      vector<string> err_com;

      stringstream oss_e;
      oss_e.precision(8);
      oss_e.setf(ios::showpoint);
      oss_e.setf(ios::scientific);
      oss_e << ene_grid_prob[ene_no];

      string str_data_ene = "Energy grid : " + oss_e.str();

      err_com.push_back(str_data_ene);
      err_com.push_back("");
      err_com.push_back("Probability heat is less than 0.0 at following bin numbers.");
      err_com.push_back("Since Probability heat must be larger than 0.0, heat cross section");
      err_com.push_back("may not be appropriate.");
      err_com.push_back("Probability heat is modified to 1.0.");
      err_com.push_back("");
      for(int j=0; j<bin_no_int; j++)
      {
        ostringstream  oss01, oss02, oss03;
        oss01 << j+1;
        oss02 << bin_no_int;
        oss03.precision(8);
        oss03.setf(ios::showpoint);
        oss03.setf(ios::scientific);
        oss03 << prob_heat[i][j];
      
        string str_data = "  ";
        if( j+1 < 10 )
        {
          str_data = str_data + " ";
        }
        str_data = str_data + oss01.str() + " / " + oss02.str() + " : " + oss03.str();
        err_com.push_back(str_data);
      }
 
      err_obj.output_caution(class_name, func_name, err_com);
    }

    if( prob_heat_check_flg[i] > 0 )
    {
      for(int j=0; j<bin_no_int; j++)
      {
        prob_heat[i][j] = 1.0;
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<vector<Real8> > ProbabilityTableCalculator::calc_prob_table_sample_no_ratio()
{
  vector<Real8>          sample_no_tot;
  vector<vector<Real8> > sample_no_ratio;
  sample_no_tot.resize(temp_no_int);
  sample_no_ratio.resize(temp_no_int);
  
  for(int i=0; i<temp_no_int; i++)
  {
    sample_no_tot[i] = 0.0;
    sample_no_ratio[i].resize(bin_no_int);
    for(int j=0; j<bin_no_int; j++)
    {
      Real8 real_val = static_cast<Real8>(prob_table_sample_no[i][j]);

      sample_no_tot[i]      += real_val;
      sample_no_ratio[i][j]  = real_val;
    }
  }

  for(int i=0; i<temp_no_int; i++)
  {
    sample_no_tot[i] = 1.0 / sample_no_tot[i];
    for(int j=0; j<bin_no_int; j++)
    {
      sample_no_ratio[i][j] *= sample_no_tot[i];
    }
  }
  sample_no_tot.clear();

  return sample_no_ratio;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::check_set_data()
{
  vector<string> err_com;
  if( nucl_data_set_flg != 1 )
  {
    err_com.push_back("There is no NuclearDataObject.");
    err_com.push_back("Please set nuclear data object using set_nucl_data_obj function");
    err_com.push_back("");
  }

  if( sample_no <= 10 )
  {
    ostringstream oss;
    oss << sample_no;
    string str_data = "sample_no : " + oss.str();
    err_com.push_back(str_data);
    err_com.push_back("Sample number is so small.");
    err_com.push_back("Sample number must be larger than 10.");
    err_com.push_back("Please check the sample number.");
    err_com.push_back("");
  }

  if( ladder_no <= 0 )
  {
    ostringstream oss;
    oss << ladder_no;
    string str_data = "ladder_no : " + oss.str();
    err_com.push_back(str_data);
    err_com.push_back("Ladder number must be larger than 10..");
    err_com.push_back("Please check the ladder number.");
    err_com.push_back("");
  }

  if( bin_no <= 0 )
  {
    ostringstream oss;
    oss << bin_no;
    string str_data = "bin_no : " + oss.str();
    err_com.push_back(str_data);
    err_com.push_back("Bin number must be larger than 0.");
    err_com.push_back("Please check the bin number.");
    err_com.push_back("");
  }

  if( ene_grid_no < 0 )
  {
    ostringstream oss;
    oss << bin_no;
    string str_data = "ene_grid_no : " + oss.str();
    err_com.push_back(str_data);
    err_com.push_back("Energy grid number must be larger than or equal to 0.");
    err_com.push_back("(0 means set all grid)");
    err_com.push_back("Please check the energy grid number.");
    err_com.push_back("");
  }

  if( temp_no_int <= 0 )
  {
    ostringstream oss;
    oss << temp_no_int;
    string str_data = "temp_no : " + oss.str();
    err_com.push_back(str_data);
    err_com.push_back("Number of temperature data must be larger than 0.");
    err_com.push_back("Please check the temperature data.");
    err_com.push_back("");
  }
  else
  {
    for(int i=0; i<temp_no_int; i++)
    {
      if( temp_data[i] < -1.0*min_value )
      {
        ostringstream oss01, oss02, oss03;
        oss01 << i+1;
        oss02 << temp_no_int;
        oss03 << temp_data[i];
        string str_data01 = "temp_no : " + oss01.str() + " / " + oss02.str();
        string str_data02 = "temp    : " + oss03.str();
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back("Temperature must be larger than or equal to 0 [K].");
        err_com.push_back("Please check the temperature data.");
        err_com.push_back("");
      }
      else if( temp_data[i] < min_temp_value ) //1.0E-10
      {
        string class_name = "ProbabilityTableCalculator";
        string func_name  = "check_set_data()";

        vector<string> err_text;
        ostringstream oss01, oss02, oss03, oss04;
        oss03.setf(ios::showpoint);
        oss03.setf(ios::scientific);
        oss03.width(8);
        oss04.setf(ios::showpoint);
        oss04.setf(ios::scientific);
        oss04.width(8);
        oss01 << i+1;
        oss02 << temp_no_int;
        oss03 << temp_data[i];
        oss04 << min_temp_value;
        string str_data01 = "temp_no : " + oss01.str() + " / " + oss02.str();
        string str_data02 = "temp    : " + oss03.str();
        string str_data03 = "Temperature is less than " + oss04.str() + " [K].";
        string str_data04 = "Temperature is modified to " + oss04.str() + " [K] for Doppler broadened";
        string str_data05 = "calculation in probability table generation.";
        err_text.push_back(str_data01);
        err_text.push_back(str_data02);
        err_text.push_back(str_data03);
        err_text.push_back(str_data04);
        err_text.push_back(str_data05);
        err_obj.output_caution(class_name, func_name, err_text);
      }
    }
  }

  if( sig_zero_no_int <= 0 )
  {
    ostringstream oss;
    oss << sig_zero_no_int;
    string str_data = "sig_zero_no : " + oss.str();
    err_com.push_back(str_data);
    err_com.push_back("Number of Sig0 data must be larger than 0.");
    err_com.push_back("Please check Sig0 data.");
    err_com.push_back("");
  }

  if( static_cast<Integer>(err_com.size()) > 0 )
  {
    string class_name = "ProbabilityTableCalculator";
    string func_name  = "check_set_data()";
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::output_set_data_information()
{
  cout << "=== Nuclear data information ===" << endl;
  cout << "  Material No.       : " << nucl_data_obj.get_general_data_obj().get_mat_no()      << endl;
  cout << "  Material Data (ZA) : " << nucl_data_obj.get_general_data_obj().get_mat_data()    << endl;
  cout << "  Mass               : " << nucl_data_obj.get_general_data_obj().get_mass()        << endl;
  //cout << "  Temperature        : " << nucl_data_obj.get_general_data_obj().get_temp()        << endl;
  //cout << "  Error              : " << nucl_data_obj.get_general_data_obj().get_error_value() << endl;
  cout << endl;
  cout << "=== Set data information ===" << endl;
  cout << "  Sample No.           :";
  cout.width(7);
  cout                               << sample_no     << " (Energy grid No. per ladder)" << endl;
  cout << "  Seed of Random No.   :";
  cout.width(7);
  cout                               << random_seed   << endl;
  cout << "  Ladder No.           :";
  cout.width(7);
  cout                               << ladder_no     << endl;
  if( static_err > min_value )
  {
    cout << "  Error                :";
    cout.width(7);
    cout                               << static_err    << endl;
  }
  cout << "  Bin No.              :";
  cout.width(7);
  cout                               << bin_no        << endl;
  cout << "  Energy Grid No.      :";
  cout.width(7);
  cout                               << ene_grid_no   << endl;

  int i_max = static_cast<int>(temp_data.size());
  cout << "  Temperature" << endl;
  cout << "    ";
  for(int i=0; i<i_max; i++)
  {
    cout << temp_data[i] << " ";
  }
  cout << endl;

  i_max = static_cast<int>(sig_zero_data.size());
  if( i_max > 0 )
  {
    cout << "  Sigma Zero Data" << endl;
    cout << "  ";
    for(int i=0; i<i_max; i++)
    {
      cout << "  " << sig_zero_data[i];
    }
    cout << endl;
  }
  else
  {
    cout << "  No Sigma Zero Data" << endl;
  }
  cout << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::output_xs_potential_data()
{
  Real za_data     = nucl_data_obj.get_general_data_obj().get_mat_data();
  Real mass_data   = nucl_data_obj.get_general_data_obj().get_mass();
  int  za_no       = static_cast<int>(round(za_data));
  int  space_no_za = 8 - digit_obj.get_digit_number(za_no);
  if( space_no_za < 1 )
  {
    space_no_za = 2;
  }
  string space_za = "";
  for(int i=0; i<space_no_za; i++)
  {
    space_za += " ";
  }

  string   out_name = "output_xs_poteintial_data.dat";
  ofstream fout_xs_pot;
  fout_xs_pot.open(out_name.c_str());
  fout_xs_pot.precision(10);
  fout_xs_pot.setf(ios::showpoint);
  fout_xs_pot.setf(ios::scientific);

  int i_max = static_cast<int>(xs_potential_vec.size());
  for(int i=0; i<i_max; i++)
  {
    fout_xs_pot << za_no << space_za << mass_data << "  "
                << ene_grid_prob[i] << "  " << xs_potential_vec[i] << endl;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::set_nucl_data_obj(NuclearDataObject& data_obj)
{
  calc_prob_flg     = 0;
  nucl_data_set_flg = 1;

  nucl_data_obj = data_obj;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::set_sample_no(int int_data)
{
  calc_prob_flg = 0;
  sample_no     = int_data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::set_random_seed(Integer int_data)
{
  calc_prob_flg = 0;
  random_seed   = int_data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::set_ladder_no(Integer int_data)
{
  calc_prob_flg = 0;
  ladder_no     = int_data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::set_bin_no(Integer int_data)
{
  calc_prob_flg = 0;
  bin_no        = int_data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::set_ene_grid_no(Integer int_data)
{
  calc_prob_flg = 0;
  ene_grid_no   = int_data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::set_temp_data(Real8 real_data)
{
  calc_prob_flg = 0;

  temp_data.clear();
  temp_data.resize(1);
  temp_data[0] = real_data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::set_temp_data(vector<Real8> real_vec)
{
  calc_prob_flg = 0;
  temp_data     = real_vec;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::set_sig_zero_data(vector<Real8> real_vec)
{
  calc_prob_flg = 0;

  sig_zero_data = real_vec;
  sort( sig_zero_data.begin(), sig_zero_data.end(), greater<Real8>() );
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::set_xs_tot_table_data(vector<vector<vector<Real8> > >& real_vec)
{
  set_xs_tot_table_data_flg = 1;
  xs_tot_table_all          = real_vec;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::set_xs_tot_table_data( vector<vector<vector<Real8> > >& real_vec_xs,
                                                        vector<Real8>&                   real_vec_ene )
{
  set_xs_tot_table_data_flg = 2;
  xs_tot_table_all          = real_vec_xs;
  xs_tot_table_ene          = real_vec_ene;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::set_static_err(Real8 real_data)
{
  calc_prob_flg = 0;

  static_err = real_data;

  if( real_data < min_value || real_data > 0.1 )
  {
    string class_name = "ProbabilityTableCalculator";
    string func_name  = "set_static_err(Real8 real_data)";

    ostringstream oss;
    oss << real_data;
    string str_data = "static_err : " + oss.str();

    vector<string> err_com;
    err_com.push_back(str_data);

    if( real_data < min_value )
    {
      err_com.push_back("The statistical error value is less than or equal to 0.0.");
      err_com.push_back("This value is not used as the convergence criteria.");
    }
    else //if( real_data > 0.1 )
    {
      err_com.push_back("The statistical error value is larger than 0.1 (10%).");
      err_com.push_back("This statistical error value may not in appropriate.");
    }

    err_obj.output_caution(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::set_static_err_percent(Real8 real_data)
{
  real_data *= 0.01;
  set_static_err(real_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

NuclearDataObject ProbabilityTableCalculator::get_nucl_data_obj()
{
  calc_probability_table();
  nucl_data_obj.set_prob_data_obj(prob_data_obj);

  return nucl_data_obj;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int ProbabilityTableCalculator::get_sample_no()
{
  return sample_no;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Integer ProbabilityTableCalculator::get_random_seed()
{
  return random_seed;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Integer ProbabilityTableCalculator::get_ladder_no()
{
  return ladder_no;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Integer ProbabilityTableCalculator::get_bin_no()
{
  return bin_no;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Integer ProbabilityTableCalculator::get_ene_grid_no()
{
  return ene_grid_no;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<Real8> ProbabilityTableCalculator::get_temp_data()
{
  return temp_data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<Real8> ProbabilityTableCalculator::get_sig_zero_data()
{
  return sig_zero_data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<Real8> ProbabilityTableCalculator::get_xs_potential_data()
{
  return xs_potential_vec;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculator::set_time_print_opt(int int_value)
{
  calc_prob_flg = 0;

  if( int_value == print_time_data )
  {
    time_print_opt = print_time_data;
  }
  else if( int_value == no_print_time_data )
  {
    time_print_opt = no_print_time_data;
  }
  else
  {
    string class_name = "ProbabilityTableCalculator";
    string func_name  = "set_time_print_opt(int int_value)";

    ostringstream oss;
    oss << int_value;
    string str_data = "Timpe print option : " + oss.str();

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("This time print option is not available.");
    err_com.push_back("Please check the time print option.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int ProbabilityTableCalculator::get_time_print_opt()
{
  return time_print_opt;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<Real> ProbabilityTableCalculator::get_time_each_ene()
{
  return time_each_ene;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Real8 ProbabilityTableCalculator::get_static_err()
{
  return static_err;
}

Real8 ProbabilityTableCalculator::get_static_err_percent()
{
  return static_err * 100.0;
}

