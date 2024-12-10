#include "ThermalScatter/CoherentElasticScatterCalculator.hpp"

using namespace frendy;

//constructor
CoherentElasticScatterCalculator::CoherentElasticScatterCalculator(void)
{
  pi_sq          = M_PI*M_PI;
  third          = 1.0 / 3.0;
  tau_part       = 8.0 * ev * amu_n * amu / (h_bar * h_bar);
  tau_part_inv   = 1.0 / tau_part;
  legendre_order = 1;

  clear();
}

//destructor
CoherentElasticScatterCalculator::~CoherentElasticScatterCalculator(void)
{
  pi_sq          = 0.0;
  third          = 0.0;
  tau_part       = 0.0;
  tau_part_inv   = 0.0;
  legendre_order = 0;

  clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void CoherentElasticScatterCalculator::clear()
{
  calc_coherent_elastic_scat_flg = 0;
  opt_elastic                    = no_calc;


  bragg_edge_no  = 0;
  atom_no        = 0;
  err            = 0.0;
  ene_max        = 0.0;
  temp           = 0.0;
  ene_grid.clear();
  scat_xs_tot.clear();
  clr_obj.clear_vec_array2_real8(scat_xs);

  sig_c      = 0.0;
  tau_sq_max = 0.0;
  tau_sq.clear();
  form_factor.clear();
  structure_factor_ene_data.clear();
  structure_factor_data.clear();

  nucl_data_obj.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void CoherentElasticScatterCalculator::calc_coherent_elastic_scatter()
{
  if( calc_coherent_elastic_scat_flg == 0 )
  {
    preparation_for_coherent_erastic_scatter();
  }

  int i_max = static_cast<int>(ene_grid.size());
  clr_obj.clear_vec_array2_real8(scat_xs);
  scat_xs.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    calc_coherent_elastic_scatter(ene_grid[i], scat_xs[i]);
  }

  int                    j;
  Integer                int_chk;
  Real8                  mid_ene;
  vector<Real8>          mid_xs;
  vector<Real8>          new_ene, new_ene_part;
  vector<vector<Real8> > new_xs,  new_xs_part;
  mid_xs.clear();
  new_ene.clear();
  new_ene_part.clear();
  clr_obj.clear_vec_array2_real8(new_xs);
  clr_obj.clear_vec_array2_real8(new_xs_part);

  //Linearize elastic scattering cross section
  new_ene.push_back(ene_grid[0]);
  new_xs.push_back(scat_xs[0]);
  for(int i=1; i<i_max; i++)
  {
    new_ene_part.push_back(ene_grid[i-1]);
    new_xs_part.push_back(scat_xs[i-1]);
    new_ene_part.push_back(ene_grid[i]);
    new_xs_part.push_back(scat_xs[i]);

    j = 1;
    mid_ene = 0.5*(new_ene_part[j] + new_ene_part[j-1]);
    calc_coherent_elastic_scatter(mid_ene, mid_xs);
    int_chk = check_ene_grid( new_ene_part[j-1], new_ene_part[j], new_xs_part[j-1], new_xs_part[j],
                              mid_ene, mid_xs );
    while( int_chk < 0 || j < static_cast<int>(new_ene_part.size()-1) )
    {
      if( int_chk >= 0 )
      {
        j++;
      }
      else
      {
        //Add middle energy grid and cross section
       insert_middle_ene_grid(j, new_ene_part, new_xs_part, mid_ene, mid_xs);
      }
      mid_ene = 0.5*(new_ene_part[j] + new_ene_part[j-1]);
      calc_coherent_elastic_scatter(mid_ene, mid_xs);
      int_chk = check_ene_grid( new_ene_part[j-1], new_ene_part[j], new_xs_part[j-1], new_xs_part[j],
                                mid_ene, mid_xs );
    }
    add_xs_at_each_ene_grid(new_ene, new_xs, new_ene_part, new_xs_part);
  }
  ene_grid = new_ene;
  scat_xs  = new_xs;

  i_max = static_cast<int>(ene_grid.size());
  scat_xs_tot.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    scat_xs_tot[i] = scat_xs[i][0];
  }


  new_ene.clear();
  clr_obj.clear_vec_array2_real8(new_xs);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Integer CoherentElasticScatterCalculator::check_ene_grid( Real8& ene_pre, Real8& ene_cur,
                                                          vector<Real8>& xs_pre, vector<Real8>& xs_cur,
                                                          Real8& mid_ene, vector<Real8>& mid_xs)
{
  Integer chk_flg  = 1;
  Real8   delta_ene = fabs(ene_cur - ene_pre);
  if( delta_ene < mid_ene*3.0E-5 )
  {
    chk_flg = 10;
    return chk_flg;
  }

  Real8 xs_err = 0.0;
  for(int i=0; i<legendre_order; i++)
  {
    xs_err = err*fabs(mid_xs[i]);
    if( xs_err < 1.0E-6 )
    {
      xs_err = 1.0E-6;
    }

    if( fabs(mid_xs[i] - 0.5*(xs_pre[i] + xs_cur[i])) >= xs_err )
    {
      chk_flg = -100;
      return chk_flg;
    }
  }

  return chk_flg;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void CoherentElasticScatterCalculator::insert_middle_ene_grid( int& ele_no,
                                               vector<Real8>& ene_data, vector<vector<Real8> >& xs_data,
                                               Real8& mid_ene, vector<Real8>& mid_xs)
{
  ta_obj.add_table_data_at_given_position(ene_data, xs_data, mid_ene, mid_xs, ele_no);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void CoherentElasticScatterCalculator::add_xs_at_each_ene_grid
                                        ( vector<Real8>& new_ene,      vector<vector<Real8> >& new_xs,
                                          vector<Real8>& new_ene_part, vector<vector<Real8> >& new_xs_part )
{
  int i_max = static_cast<int>(new_ene_part.size());
  for(int i=1; i<i_max; i++)
  {
    new_ene.push_back(new_ene_part[i]);
    new_xs.push_back(new_xs_part[i]);
  }
  new_ene_part.clear();
  clr_obj.clear_vec_array2_real8(new_xs_part);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void CoherentElasticScatterCalculator::calc_coherent_elastic_scatter(Real8& ene_data, vector<Real8>& xs_data)
{
  if( opt_elastic == use_nucl_data )
  {
    //xs_data = xs_data / ene_data;
    calc_coherent_elastic_scatter_by_nuclear_data(ene_data, xs_data);
  }
  else if( opt_elastic == calc_graphite || opt_elastic == calc_be || opt_elastic == calc_be_o )
  {
    calc_coherent_elastic_scatter_by_form_factor(ene_data, xs_data);
  }
  else if( opt_elastic == no_calc )
  {
    return;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void CoherentElasticScatterCalculator::calc_coherent_elastic_scatter_by_nuclear_data
                                                             (Real8& ene_data, vector<Real8>& xs_data)
{
  xs_data.resize(legendre_order);
  for(int i=0; i<legendre_order; i++)
  {
    xs_data[i] = 0.0;
  }

  if( structure_factor_ene_data[0] >= ene_data )
  {
    return;
  }

  int i_max  = static_cast<int>(structure_factor_ene_data.size());
  int ele_no = -1;
  for(int i=1; i<i_max; i++)
  {
    if( structure_factor_ene_data[i] >= ene_data )
    {
      ele_no = i - 1;
      break;
    }
  }
  if( ele_no < 0 )
  {
    if( ene_data < ene_max )
    {
      ele_no = i_max - 1;
    }
    else
    {
      return;
    }
  }
  for(int i=0; i<=ele_no; i++)
  {
    legendre_expansion(ene_data, structure_factor_ene_data[i], structure_factor_data[i], xs_data);
  }

  Real8 ene_inv = 1.0 / ene_data;
  for(int i=0; i<legendre_order; i++)
  {
    xs_data[i] *= ene_inv;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void CoherentElasticScatterCalculator::calc_coherent_elastic_scatter_by_form_factor
                                                             (Real8& ene_data, vector<Real8>& xs_data)
{
  vector<Real8> ene_bragg_vec;
  Real8 ene_bragg     = 0.0;
  Real8 ene_bragg_pre = 0.0;

  xs_data.clear();
  xs_data.resize(legendre_order);
  for(int i=0; i<legendre_order; i++)
  {
    xs_data[i] = 0.0;
  }

  ene_bragg = tau_sq[0]*tau_part_inv;
  ene_bragg_vec.push_back(ene_bragg);
  if( ene_bragg >= ene_data )
  {
    return;
  }

  int i_max  = static_cast<int>(tau_sq.size());
  int ele_no = -1;
  for(int i=1; i<i_max; i++)
  {
    ene_bragg = tau_sq[i]*tau_part_inv;
    ene_bragg_vec.push_back(ene_bragg);
    if( ene_bragg >= ene_data )
    {
      ele_no    = i - 1;
      ene_bragg = ene_bragg_pre;
      break;
    }
    ene_bragg_pre = ene_bragg;
  }
  if( ele_no < 0 )
  {
    if( ene_data < ene_max )
    {
      ele_no = i_max - 1;
    }
    else
    {
      return;
    }
  }

  for(int i=0; i<=ele_no; i++)
  {
    legendre_expansion(ene_data, ene_bragg_vec[i], form_factor[i], xs_data);
  }
  ene_bragg_vec.clear();

  Real8 coef = sig_c / ene_data;
  for(int i=0; i<legendre_order; i++)
  {
    xs_data[i] *= coef;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void CoherentElasticScatterCalculator::legendre_expansion( Real8& ene_data, Real8& ene_bragg,
                                                           Real8& coef, vector<Real8>& xs_data )
{
  if( ene_data <= ene_max )
  {
    Real8         mu           = 1.0 - 2.0*ene_bragg / ene_data;
    vector<Real8> legendre_vec = math_obj.legendre_expansion(mu, legendre_order);

    for(int i=0; i<legendre_order; i++)
    {
      xs_data[i] += coef*legendre_vec[i];
    }
    legendre_vec.clear();
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void CoherentElasticScatterCalculator::preparation_for_coherent_erastic_scatter()
{
  calc_coherent_elastic_scat_flg = 1;
  check_set_data();
  set_energy_grid();

  if( opt_elastic == use_nucl_data )
  {
    set_structure_factor();
  }
  else if( opt_elastic == calc_graphite || opt_elastic == calc_be || opt_elastic == calc_be_o )
  {
    set_form_factor();
  }
  else if( opt_elastic == no_calc )
  {
    ene_grid.clear();
    return;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void CoherentElasticScatterCalculator::check_set_data()
{
  vector<string> err_com;
  err_com.clear();

  if( opt_elastic != use_nucl_data && opt_elastic != no_calc &&
      opt_elastic != calc_graphite && opt_elastic != calc_be && opt_elastic != calc_be_o )
  {
    ostringstream oss01, oss02, oss03, oss04, oss05, oss06;
    oss01 << opt_elastic;
    oss02 << use_nucl_data;
    oss03 << no_calc;
    oss04 << calc_graphite;
    oss05 << calc_be;
    oss06 << calc_be_o;
    string str_data01 = "Elastic option " + oss01.str();
    string str_data02 = "Elastic option is not appropriate.";
    string str_data03 = "Available elastic option";
    string str_data04 = "  Calculate using nuclear data : " + oss02.str();
    string str_data05 = "  No calculation               : " + oss03.str();
    string str_data06 = "  Glaphite                     : " + oss04.str();
    string str_data07 = "  Beryllium                    : " + oss05.str();
    string str_data08 = "  Beryllium oxide              : " + oss06.str();
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back(str_data05);
    err_com.push_back(str_data06);
    err_com.push_back(str_data07);
    err_com.push_back(str_data08);
  }

  if( atom_no < min_value )
  {
    ostringstream oss01;
    oss01 << atom_no;
    string str_data01 = "Atom number : " + oss01.str();
    err_com.push_back(str_data01);
    err_com.push_back("Atom number is not input or set inappropriate value.");
  }

  if( err < min_value )
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

  if( temp < min_value )
  {
    ostringstream oss01;
    oss01 << temp;
    string str_data01 = "Temperature : " + oss01.str();
    err_com.push_back(str_data01);
    err_com.push_back("Temperature is not input or set inappropriate value.");
  }

#ifdef DEBUG_MODE
  Real8 temp_nucl = static_cast<Real8>(nucl_data_obj.get_general_data_obj().get_temp());
  if( fabs(temp_nucl - temp) >= min_ene_dif*temp )
  {
    ostringstream oss01, oss02;
    oss01 << temp;
    oss02 << temp_nucl;
    string str_data01 = "Temperature (input)        : " + oss01.str();
    string str_data02 = "Temperature (nuclear data) : " + oss02.str();
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("The input temperature is not identical to the nuclear data.");
  }
#endif

  if( static_cast<int>(err_com.size()) > 0 )
  {
    string class_name = "CoherentElasticScatterCalculator";
    string func_name  = "check_set_data()";
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void CoherentElasticScatterCalculator::set_structure_factor()
{
  ThermalScatterDataContainer sab_data_obj = nucl_data_obj.get_thermal_scat_data_obj();
  structure_factor_ene_data.clear();
  structure_factor_data.clear();

  if( sab_data_obj.get_elastic_scat_flg() != 1 && sab_data_obj.get_elastic_scat_flg() != 3 )
  {
    string class_name = "CoherentElasticScatterCalculator";
    string func_name  = "set_structure_factor()";

    ostringstream oss01;
    oss01 << sab_data_obj.get_elastic_scat_flg();
    string str_data01 = "Elastic scatter flg (LTHR) : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("This elastic scatter flg can not treat in this program.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  cp_obj.copy_vec_array1_real8(structure_factor_ene_data,
                               sab_data_obj.get_elastic_structure_factor_ene_data());

  //Set Bragg edge number
  calc_bragg_edge_no(structure_factor_ene_data);

  //Merge energy grid and Bragg edge energy
  add_energy_grid(structure_factor_ene_data);

  Real temp_real    = static_cast<Real>(temp);
  Real temp_max     = temp_real * 1.1;
  Real temp_err     = 5.0 + temp_real*1.0E-3;
  Real temp_dif     = fabs(temp_real - sab_data_obj.get_elastic_temp_data_base());
  Real temp_dif_min = temp_dif;
  if( temp_dif < temp_err )
  {
    cp_obj.copy_vec_array1_real8(structure_factor_data,
                                   sab_data_obj.get_elastic_structure_factor_data_base());
  }

  vector<Real> temp_vec = sab_data_obj.get_elastic_temp_data();
  int i_max = static_cast<int>(temp_vec.size());
  for(int i=0; i<i_max; i++)
  {
    temp_dif = fabs(temp_real - temp_vec[i]);
    if( temp_dif < temp_err )
    {
      if( temp_dif < temp_dif_min )
      {
        cp_obj.copy_vec_array1_real8(structure_factor_data,
                                       sab_data_obj.get_elastic_structure_factor_data()[i]);
        temp_dif_min = temp_dif;
      }
    }
    else if( temp_max < temp_vec[i] )
    {
      break;
    }
  }
  temp_vec.clear();

  i_max = static_cast<int>(structure_factor_data.size());
  if( i_max > 1 )
  {
    Real8 structure_factor_pre, structure_factor_cur;
    structure_factor_pre = structure_factor_data[0];
    for(int i=1; i<i_max; i++)
    {
      structure_factor_cur     = structure_factor_data[i];
      structure_factor_data[i] = structure_factor_cur - structure_factor_pre;
      structure_factor_pre     = structure_factor_cur;
    }
  }
  
  if( temp_dif_min >= temp_err )
  {
    string class_name = "CoherentElasticScatterCalculator";
    string func_name  = "set_structure_factor()";

    ostringstream oss01, oss02, oss03;
    oss01 << temp_real;
    oss02 << temp_dif_min;
    oss03 << temp_err;
    string str_data01 = "Input temperature           : " + oss01.str();
    string str_data02 = "Minimum absolute difference : " + oss02.str();
    string str_data03 = "Acceptable error            : " + oss03.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("The difference of temperature is so large.");
    err_com.push_back("This input temperature is not available.");
    err_com.push_back("Please change the input temperature.");
    err_com.push_back("");
    err_com.push_back("The available temperature [K] is as follows:");

    ostringstream oss04;
    oss04 << sab_data_obj.get_elastic_temp_data_base();
    string str_data04 = "  " + oss04.str() + " (base)";
    err_com.push_back(str_data04);

    temp_vec = sab_data_obj.get_elastic_temp_data();
    i_max = static_cast<int>(temp_vec.size());
    for(int i=0; i<i_max; i++)
    {
      temp_dif = fabs(temp_real - temp_vec[i]);

      ostringstream oss11, oss12, oss13;
      oss11 << i+1;
      oss12 << i_max;
      oss13 << temp_vec[i];

      string str_data11 = "    " + oss11.str() + " / " + oss12.str() + " : " + oss13.str();
      err_com.push_back(str_data11);
    }
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
  sab_data_obj.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void CoherentElasticScatterCalculator::set_form_factor()
{
  Real8 coef_a, coef_c, mass, debye_waller;
  set_initial_value_for_form_factor(coef_a, coef_c, mass, debye_waller);

  Real8 coef_a_sq        = coef_a*coef_a;
  Real8 coef_tau1        = 4.0*third / coef_a_sq;
  Real8 coef_tau2        = 1.0 / (coef_c*coef_c);
  Real8 tau_sq_max       = tau_part * ene_max;
  Real8 form_factor_part = 0.5 * h_bar / (amu * mass);

  sig_c      *= 8.0*pi_sq*tau_part_inv / (coef_a_sq*coef_c*sqrt(3));
  tau_sq_max  = tau_part * ene_max;

  tau_sq.clear();
  form_factor.clear();
  Real8 tau_sq_val      = 0.0;
  Real8 form_factor_val = 0.0;
  Real8 phi             = 0.25 * tau_sq_max / pi_sq;
  int   i_max           = static_cast<int>(ceil(coef_a*sqrt(phi)));
  int   ele_no          = 0;
  for(int i=0; i<i_max; i++)
  {
    Real8 li    = static_cast<Real8>(i);
    int   j_max = static_cast<int>(ceil(0.5*li+sqrt(3.0*coef_a_sq*phi-li*li)));
    for(int j=i; j<j_max; j++)
    {
      Real8 lj    = static_cast<Real8>(j);
      Real8 x     = phi - coef_tau1*(li*li + lj*lj - li*lj);
      int   k_max = 1;
      if( x > 0 )
      {
        k_max = static_cast<int>(ceil(coef_c * sqrt(x)));
      }

      for(int k=0; k<k_max; k++)
      {
        Real8 lk     = static_cast<Real8>(k);
        Real8 weight = calc_form_factor_weight(i, j, k);

        for(int l=0; l<2; l++)
        {
          tau_sq_val = calc_tau_sq(coef_tau1, coef_tau2, li, lj, lk);
          if( tau_sq_val >= min_value && tau_sq_val <= tau_sq_max )
          {
            form_factor_val  = calc_crystallographis_structure_factor(li, lj, lk);
            form_factor_val *= exp(-1.0*tau_sq_val*form_factor_part*debye_waller)*weight/(sqrt(tau_sq_val));
  
            if( ele_no > 0 && tau_sq_val > tau_part*0.05 )
            {
              Integer form_factor_add_flg = -1;
              for(int m=0; m<ele_no; m++)
              {
                if( tau_sq_val >= tau_sq[m] && tau_sq_val < 1.05*tau_sq[m] )
                {
                  form_factor_add_flg = 1;
                  form_factor[m] += form_factor_val;
                  break;
                }
              }
              if( form_factor_add_flg < 0 )
              {
                tau_sq.push_back(tau_sq_val);
                form_factor.push_back(form_factor_val);
                ele_no++;
              }
            }
            else
            {
              tau_sq.push_back(tau_sq_val);
              form_factor.push_back(form_factor_val);
              ele_no++;
            }
          }
          lj *= -1.0;
        }
      }
    }
  }

  //Add maximum tau_sq
  form_factor_val = form_factor[ele_no-1];
  tau_sq.push_back(tau_sq_max);
  form_factor.push_back(form_factor_val);
  ele_no++;

  //Sort tau_sq and form_factor
  math_obj.simultaneous_vector_sort(tau_sq, form_factor);

  //Set Bragg edge number
  ele_no = static_cast<int>(tau_sq.size());
  vector<Real8> ene_vec;
  ene_vec.clear();
  Real8 ene_data = 0.0;
  for(int i=0; i<ele_no; i++)
  {
    ene_data = tau_sq[i]*tau_part_inv;
    if( ene_data <= ene_max )
    {
      ene_vec.push_back(ene_data);
    }
  }
  calc_bragg_edge_no(ene_vec);

  //Merge energy grid and Bragg edge energy
  structure_factor_ene_data = ene_vec;
  add_energy_grid(structure_factor_ene_data);
  ene_vec.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void CoherentElasticScatterCalculator::set_initial_value_for_form_factor
                                        (Real8& coef_a, Real8& coef_c, Real8& mass, Real8& debye_waller)
{
  coef_a = 0.0;
  coef_c = 0.0;

  int ele_no = 10;
  vector<Real8> debye_waller_vec, debye_waller_temp;
  debye_waller_vec.resize(ele_no);
  debye_waller_temp.resize(ele_no);
  debye_waller_temp[0] =  296.0;
  debye_waller_temp[1] =  400.0;
  debye_waller_temp[2] =  500.0;
  debye_waller_temp[3] =  600.0;
  debye_waller_temp[4] =  700.0;
  debye_waller_temp[5] =  800.0;
  debye_waller_temp[6] = 1000.0;
  debye_waller_temp[7] = 1200.0;
  debye_waller_temp[8] = 1600.0;
  debye_waller_temp[9] = 2000.0;

  mass = 0.0;
  if( opt_elastic == calc_graphite )
  {
    coef_a              =  2.4573E-8;
    coef_c              =  6.7000E-8;
    mass                =  1.2011E+1;
    sig_c               =  5.5000E+0 / static_cast<Real8>(atom_no);
    debye_waller_vec[0] =  2.1997;
    debye_waller_vec[1] =  2.7448;
    debye_waller_vec[2] =  3.2912;
    debye_waller_vec[3] =  3.8510;
    debye_waller_vec[4] =  4.4210;
    debye_waller_vec[5] =  4.9969;
    debye_waller_vec[6] =  6.1624;
    debye_waller_vec[7] =  7.3387;
    debye_waller_vec[8] =  9.6287;
    debye_waller_vec[9] = 11.9920;
  }
  else if( opt_elastic == calc_be )
  {
    coef_a              =  2.2856E-8;
    coef_c              =  3.5832E-8;
    mass                =  9.0100E+0;
    sig_c               =  7.5300E+0 / static_cast<Real8>(atom_no);
    debye_waller_vec[0] =  3.16663;
    debye_waller_vec[1] =  3.88842;
    debye_waller_vec[2] =  4.62944;
    debye_waller_vec[3] =  5.40517;
    debye_waller_vec[4] =  6.19880;
    debye_waller_vec[5] =  7.00420;
    debye_waller_vec[6] =  8.63665;
    debye_waller_vec[7] = 10.28650;
    debye_waller_vec[8] =  0.00000;
    debye_waller_vec[9] =  0.00000;
  }
  else if( opt_elastic == calc_be_o )
  {
    coef_a              = 2.695E-8;
    coef_c              = 4.390E-8;
    mass                = 1.250E+1;
    sig_c               = 1.000E+0 / static_cast<Real8>(atom_no);
    debye_waller_vec[0] = 2.1530;
    debye_waller_vec[1] = 2.6374;
    debye_waller_vec[2] = 3.1348;
    debye_waller_vec[3] = 3.6513;
    debye_waller_vec[4] = 4.1798;
    debye_waller_vec[5] = 4.7164;
    debye_waller_vec[6] = 5.8052;
    debye_waller_vec[7] = 6.9068;
    debye_waller_vec[8] = 0.0000;
    debye_waller_vec[9] = 0.0000;
  }
  else
  {
    string class_name = "CoherentElasticScatterCalculator";
    string func_name  = "calc_form_factor()";

    ostringstream oss01, oss02, oss03, oss04;
    oss01 << opt_elastic;
    oss02 << calc_graphite;
    oss03 << calc_be;
    oss04 << calc_be_o;
    string str_data01 = "Elastic option " + oss01.str();
    string str_data02 = "Elastic option is not appropriate.";
    string str_data03 = "Available elastic option";
    string str_data04 = "  Glaphite        : " + oss02.str();
    string str_data05 = "  Beryllium       : " + oss03.str();
    string str_data06 = "  Beryllium oxide : " + oss04.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back(str_data05);
    err_com.push_back(str_data06);
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  Integer order = 2;
  debye_waller  = math_obj.lagrange_interpolation(temp, order, debye_waller_temp, debye_waller_vec);
  debye_waller *= 6.58173E-16 * mass;

  debye_waller_temp.clear();
  debye_waller_vec.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Real8 CoherentElasticScatterCalculator::calc_form_factor_weight(int i, int j, int k)
{
  Real8 weight = 8.0;
  if( i == j || i == 0 || j == 0 )
  {
    if( i == 0 && j == 0 )
    {
        weight *= 0.125;
    }
    else if( i == j )
    {
      weight *= 0.5;
    }
    else
    {
      weight *= 0.5;
    }
  }

  if( k == 0 )
  {
    weight *= 0.5;
  }

  return weight;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Real8 CoherentElasticScatterCalculator::calc_tau_sq( Real8& coef_tau1, Real8& coef_tau2,
                                                     Real8& li, Real8& lj, Real8& lk )
{
  Real8  tau_sq = 4.0*pi_sq*(coef_tau1*(li*li + lj*lj + li*lj) + coef_tau2*lk*lk);
  return tau_sq;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Real8 CoherentElasticScatterCalculator::calc_crystallographis_structure_factor(Real8& li, Real8& lj, Real8& lk)
{
  Real8 crystallographis_structure_factor = 0.0;

  if( opt_elastic == calc_graphite )
  {
    int k = static_cast<int>(round(lk));
    if( k%2 != 0 )
    {
      crystallographis_structure_factor  = sin(M_PI*(li - lj)*third); 
      crystallographis_structure_factor *= crystallographis_structure_factor;
    }
    else
    {
      crystallographis_structure_factor = 1.5+2.5*cos(2.0*M_PI*(li - lj)*third);
    }
  }
  else if( opt_elastic == calc_be )
  {
    crystallographis_structure_factor = 1.0 + cos(M_PI*(2.0*li + 4.0*lj + 3.0*lk)*third);
  }
  else if( opt_elastic == calc_be_o )
  {
    crystallographis_structure_factor = (1.0 + cos(M_PI*(2.0*li + 4.0*lj + 3.0*lk)*third))
                                      * (11.78 + 11.31*cos(0.75*M_PI*lk));
  }

  return crystallographis_structure_factor;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void CoherentElasticScatterCalculator::calc_bragg_edge_no(vector<Real8>& ene_vec)
{
  bragg_edge_no = 0;
  int i_max = static_cast<int>(ene_vec.size());
  for(int i=0; i<i_max; i++)
 {
    if( ene_vec[i] > ene_max )
    {
      if( i > 0 )
      {
        if( fabs(ene_vec[i-1] - ene_max) >= min_ene_dif*ene_max )
        {
          bragg_edge_no++;
        }
      }
      break;
    }
    else if( i==0 )
    {
      bragg_edge_no++;
    }
    else if( fabs(ene_vec[i] - ene_vec[i-1]) > min_ene_dif*ene_vec[i-1])
    {
      bragg_edge_no++;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void CoherentElasticScatterCalculator::set_energy_grid()
{
  Integer reaction_type = 2; //MT=2
  CrossSectionDataContainer xs_data_obj
                              = nucl_data_obj.get_nucl_reaction_data_obj().get_xs_data_obj(reaction_type);
  vector<Real> ene_grid_ref = xs_data_obj.get_xs_ene_data();

  IncoherentInelasticScatterCalculator iis_obj;
  vector<Real> ene_grid_add = iis_obj.ene_in_incoherent_inelastic; //NJOY's original energy grid
  ene_grid_add.push_back(digit_obj.get_adjusted_value(ene_max, sig_fig-2, -1.0));
  ene_grid_add.push_back(ene_max);

  iis_obj.merge_energy_grid(ene_grid_ref, ene_grid_add);
  iis_obj.clear();
  ene_grid_add.clear();

  ene_grid.clear();
  int  i_max   = static_cast<int>(ene_grid_ref.size());
  Real ene_top = static_cast<Real>(ene_max + min_ene_dif);
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

  ene_grid.push_back(digit_obj.get_adjusted_value(ene_max, sig_fig-2, +1.0));
  ene_grid.push_back(ene_grid_ref[i_max-1]);
  ene_grid_ref.clear();

  i_max = static_cast<int>(ene_grid.size());
  if( reaction_type != xs_data_obj.get_reaction_type() || i_max == 0 )
  {
    string class_name = "CoherentElasticScatterCalculator";
    string func_name  = "set_energy_grid()";

    ostringstream oss01, oss02;
    vector<string> err_com;
    if( reaction_type != xs_data_obj.get_reaction_type() )
    {
      oss01 << reaction_type;
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
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void CoherentElasticScatterCalculator::add_energy_grid(vector<Real8>& ene_vec)
{
  vector<Real8> ene_grid_tmp = ene_grid;

  int i_max = static_cast<int>(ene_vec.size());
  for(int i=0; i<i_max; i++)
  {
    Real8 ene_val = ene_vec[i];
    if( ene_val <= ene_max )
    {
      ene_grid_tmp.push_back(digit_obj.get_adjusted_value(ene_val, sig_fig, -2.0));
      ene_grid_tmp.push_back(digit_obj.get_adjusted_value(ene_val, sig_fig, -1.0));
      //ene_grid_tmp.push_back(ene_val);
      ene_grid_tmp.push_back(digit_obj.get_adjusted_value(ene_val, sig_fig, +1.0));
      ene_grid_tmp.push_back(digit_obj.get_adjusted_value(ene_val, sig_fig, +2.0));
    }
  }
  ene_grid_tmp.push_back(ene_max);

  sort(ene_grid_tmp.begin(), ene_grid_tmp.end());

  ene_grid.clear();
  i_max = static_cast<int>(ene_grid_tmp.size());
  Real8 ene_pre, ene_cur;
  ene_pre = ene_grid_tmp[0];
  ene_grid.push_back(ene_pre);
  for(int i=1; i<i_max; i++)
  {
    ene_cur = ene_grid_tmp[i];
    if( ene_cur - ene_pre >= ene_cur*min_ene_dif )
    {
      ene_grid.push_back(ene_cur);
    }
    ene_pre = ene_cur;
  }
  ene_grid_tmp.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//Setter

void CoherentElasticScatterCalculator::set_nucl_data_obj(NuclearDataObject& data_obj)
{
  calc_coherent_elastic_scat_flg = 0;
  nucl_data_obj = data_obj;
}

void CoherentElasticScatterCalculator::set_opt_elastic(Integer& int_data)
{
  calc_coherent_elastic_scat_flg = 0;
  opt_elastic = int_data;
}

void CoherentElasticScatterCalculator::set_atom_no(Integer& int_data)
{
  calc_coherent_elastic_scat_flg = 0;
  atom_no = int_data;
}

void CoherentElasticScatterCalculator::set_err(Real8& real_data)
{
  err = real_data;
}

void CoherentElasticScatterCalculator::set_ene_max(Real8& real_data)
{
  calc_coherent_elastic_scat_flg = 0;
  ene_max = real_data;
}

void CoherentElasticScatterCalculator::set_temp(Real8& real_data)
{
  calc_coherent_elastic_scat_flg = 0;
  temp = real_data;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//Getter

NuclearDataObject CoherentElasticScatterCalculator::get_nucl_data_obj()
{
  calc_coherent_elastic_scatter();

  Integer bragg_no = static_cast<Integer>(bragg_edge_no);

  ThermalScatterDataContainer sab_data_obj = nucl_data_obj.get_thermal_scat_data_obj();
  sab_data_obj.set_coherent_elastic_bragg_no(bragg_no);
  sab_data_obj.set_coherent_elastic_ene_grid(ene_grid);
  sab_data_obj.set_coherent_elastic_scat_xs_tot(scat_xs_tot);
  sab_data_obj.set_coherent_elastic_scat_xs(scat_xs);
  nucl_data_obj.set_thermal_scat_data_obj(sab_data_obj);
  sab_data_obj.clear();

  GeneralDataContainer general_data_obj = nucl_data_obj.get_general_data_obj();
  general_data_obj.set_temp(temp);
  general_data_obj.set_error_value(err);
  nucl_data_obj.set_general_data_obj(general_data_obj);
  general_data_obj.clear();

  return nucl_data_obj;
}

Integer CoherentElasticScatterCalculator::get_opt_elastic()
{
  return opt_elastic;
}

Integer CoherentElasticScatterCalculator::get_atom_no()
{
  return atom_no;
}

Integer CoherentElasticScatterCalculator::get_bragg_edge_no()
{
  return static_cast<Integer>(bragg_edge_no);
}

Real8 CoherentElasticScatterCalculator::get_err()
{
  return err;
}

Real8 CoherentElasticScatterCalculator::get_ene_max()
{
  return ene_max;
}

Real8 CoherentElasticScatterCalculator::get_temp()
{
  return temp;
}

