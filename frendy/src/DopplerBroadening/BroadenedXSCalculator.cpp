#include "DopplerBroadening/BroadenedXSCalculator.hpp"

using namespace frendy;

//Initialize static const value
const Real8 BroadenedXSCalculator::max_z_val = 10.0; //exp(-100) = 3.7e-44, erf(10) = 1.0;

//constructor
BroadenedXSCalculator::BroadenedXSCalculator(void)
{
  clear();
  
  pi_inv      = 1.0 / M_PI;
  rpi         = sqrt(M_PI);
  rpi_inv     = 1.0 / rpi;
  temp_ori    = -100.0;
  temp_dop    = -100.0;
  dop_ene_max = -100.0;
}

//destructor
BroadenedXSCalculator::~BroadenedXSCalculator(void)
{
  clear();
  pi_inv      = 0.0;
  rpi         = 0.0;
  rpi_inv     = 0.0;
  temp_ori    = 0.0;
  temp_dop    = 0.0;
  dop_ene_max = 0.0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

vector<Real8> BroadenedXSCalculator::calc_doppler_broadened_xs(Real8& ene_val)
{
  int minus_flg = 0;
  vector<Real8> sig_val;
  calc_doppler_broadened_xs(ene_val, sig_val, minus_flg);

  //The Doppler broadened cross section becomes minus value.
  //The cause of this problem is the rounding error.
  //To avoid this problem, the incident energy is slightly modified
  //when the Doppler broadened cross section is less than 0.0.
  Real mod_val = 1.0;
  while( minus_flg >= 0 && mod_val < 11.0 )
  {
    if( minus_flg >= 0 )
    {
      Real ene_val_mod = digit_obj.get_adjusted_value(ene_val, sig_fig, mod_val);
      calc_doppler_broadened_xs(ene_val_mod, sig_val, minus_flg);
    }

    if( minus_flg >= 0 )
    {
      Real ene_val_mod = digit_obj.get_adjusted_value(ene_val, sig_fig, -1.0*mod_val);
      calc_doppler_broadened_xs(ene_val_mod, sig_val, minus_flg);
    }

    mod_val += 1.0;
  }

  if( minus_flg >= 0 )
  {
    calc_doppler_broadened_xs(ene_val, sig_val, minus_flg);
  }

  for(int i=0; i<static_cast<int>(sig_val.size()); i++)
  {
    sig_val[i] = digit_obj.get_truncation_value(sig_val[i]);
  }

  return sig_val;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void BroadenedXSCalculator::calc_doppler_broadened_xs(Real8& ene_val, vector<Real8>& sig_val, int& minus_flg)
{
  calc_doppler_broadened_xs(ene_val, sig_val);

  minus_flg = -1;
  for(int i=0; i<mt_no; i++)
  {
    if( sig_val[i] < -1.0e-30 )
    {
      minus_flg = i;
      break;
    }
  }

  int i_m, i_p;
  ti_obj.search_neighbor_value(ene_val, ene_data, i_m, i_p);
  for(int i=0; i<mt_no; i++)
  {
    sig_val[i] = digit_obj.adjust_min_value(sig_val[i]);

    if( sig_data[i_m][i] < min_sig_val && sig_data[i_p][i] < min_sig_val )
    {
      sig_val[i] = 0.0;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void BroadenedXSCalculator::calc_doppler_broadened_xs(Real8& ene_val, vector<Real8>& sig_val)
{
  if( calc_doppler_xs_flg == 0 )
  {
    preparation_for_doppler_broadening();
  }

  //Skip calculation of doppler broadened xs when energy is larger than dop_ene_max
  if( ene_val > dop_ene_max )
  {
    return;
  }
 
  vector<Real8> sig_m;
  Real8 y_val;
  calc_y(ene_val, y_val);
  check_integral_range(y_val);
 
  xs_part_flg = 1;
  sig_val = calc_doppler_broadened_xs_part(y_val, int_rang_p_min, int_rang_p_max);
  
  if( int_rang_m_max != 0 )
  {
    xs_part_flg = -1;

    y_val *= -1.0;
    sig_m = calc_doppler_broadened_xs_part(y_val, int_rang_m_min, int_rang_m_max);
    
    for(int i=0; i<mt_no; i++)
    {
      sig_val[i] = sig_val[i] - sig_m[i];
    }
  }
  sig_m.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void BroadenedXSCalculator::check_integral_range(Real8& y_val)
{
  Real8 int_m_max_chk = integral_range_dop - y_val;
  Real8 int_p_min_chk = y_val              - integral_range_dop;
  Real8 int_p_max_chk = y_val              + integral_range_dop;
  
  int_rang_m_min =  0;
  int_rang_m_max = -1;
  int_rang_p_min = -1;
  int_rang_p_max = -1;
  
  int m_max_sta, p_min_sta, p_max_sta;
  if( y_val >= y_val_pre && y_val_pre > 0.0 )
  {
    m_max_sta = int_rang_m_max_pre;
    p_min_sta = int_rang_p_min_pre;
    p_max_sta = int_rang_p_max_pre;
  }
  else
  {
    m_max_sta = grid_no-2;
    p_min_sta = 0;
    p_max_sta = 0;
  }
  y_val_pre = y_val;

  //Serch int_m_max
  for(int i=m_max_sta; i>=0; i--)
  {
    if( int_m_max_chk > x_data[i] )
    {
      int_rang_m_max = i+1;
      break;
    }
  }
  if( int_rang_m_max == -1 )
  {
    int_rang_m_max = 0;
  }
  int_rang_m_max_pre = int_rang_m_max;

  //Serch int_p_min
  for(int i=p_min_sta; i<grid_no; i++)
  {
    if( int_p_min_chk < x_data[i] )
    {
      if( i == 0 )
      {
        int_rang_p_min = 0;
      }
      else
      {
        int_rang_p_min = i-1;
      }
      break;
    }
  }
  if( int_rang_p_min == -1 )
  {
    int_rang_p_min = grid_no-1;
  }
  int_rang_p_min_pre = int_rang_p_min;

  //Serch int_p_max
  if( p_min_sta > p_max_sta )
  {
    p_max_sta = p_min_sta;
  }
  for(int i=p_max_sta; i<grid_no; i++)
  {
    if( int_p_max_chk < x_data[i] )
    {
      int_rang_p_max = i;
      break;
    }
  }
  if( int_rang_p_max == -1 )
  {
    int_rang_p_max = grid_no-1;
  }
  int_rang_p_max_pre = int_rang_p_max;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

vector<Real8> BroadenedXSCalculator::calc_doppler_broadened_xs_part
                                       (Real8& y_val, int int_min, int int_max)
{
  vector<Real8> sig_val;
  Real8 f_a, f_c;
  Real8 h_n[5], f_n_pre[5];
  Real8 inte_sta, inte_fin;

  Real8 y1 = y_val;
  Real8 y2 = y1*y1;
  Real8 y3 = y2*y1;
  Real8 y4 = y3*y1;

  Real8 coef_a1 = 2.0*y1;
  Real8 coef_a2 =     y2;
  Real8 coef_c1 = 4.0*y1;
  Real8 coef_c2 = 6.0*y2;
  Real8 coef_c3 = 4.0*y3;
  Real8 coef_c4 =     y4;
  
  //Calculation of initial f_n value
  if( int_min != 0 )
  {
    inte_sta = x_data[int_min-1] - y_val;
  }
  else
  {
    inte_sta = x_zero - y_val;
  }
  calc_f_n(inte_sta, f_n_pre);
  
  sig_val.resize(mt_no);
  for(int i=0; i<mt_no; i++)
  {
    sig_val[i] = 0.0;
  }
  
  for(int i=int_min; i<=int_max; i++)
  {
    inte_fin = x_data[i] - y_val;
    if( inte_fin > inte_sta )
    {
      calc_h_n(inte_sta, inte_fin, h_n, f_n_pre);
      
      f_a = h_n[2] + coef_a1*h_n[1] + coef_a2*h_n[0];
      f_c = h_n[4] + coef_c1*h_n[3] + coef_c2*h_n[2] + coef_c3*h_n[1] + coef_c4*h_n[0];

      for(int j=0; j<mt_no; j++)
      {
        Real8 sig_add = f_a*a_vec[i][j] + f_c*c_vec[i][j];
        if( sig_add > 0.0 )
        {
          sig_val[j] += sig_add;
        }
        //sig_val[j] += f_a*a_vec[i][j] + f_c*c_vec[i][j];
      }
    }
  }
  
  for(int i=0; i<mt_no; i++)
  {
    sig_val[i] = sig_val[i] / y2;
  }
  return sig_val;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void BroadenedXSCalculator::calc_h_n(Real8& inte_sta, Real8& inte_fin, Real8 h_n[5], Real8 f_n_sta[5])
{
  Real8 f_n_fin[5]; //, h_n_tayler;

  calc_f_n(inte_fin, f_n_fin);
  
  if( inte_sta < max_z_val || inte_fin < max_z_val )
  {
    for(int i=0; i<5; i++)
    {
      h_n[i] = 0.5*(f_n_fin[i] - f_n_sta[i]);
      /*
      if( fabs(h_n[i]) > min_tayler_val )
      {
        if( fabs(h_n[i]) <= fabs(tayler_calc_condition*f_n_sta[i]) )
        {
          calc_h_n_by_tayler_ex(i, inte_sta, inte_fin, h_n_tayler);
          if( fabs(h_n_tayler) < fabs(f_n_sta[i]) + fabs(f_n_fin[i]) )
          {
            h_n[i] = h_n_tayler;
          }
        }
      }
      // */
      f_n_sta[i] = f_n_fin[i];
    }
  }
  else
  {
    for(int i=0; i<5; i++)
    {
      h_n[i] = 0.0;
    }
  }
  inte_sta = inte_fin;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void BroadenedXSCalculator::calc_f_n(Real8& inte_val, Real8 f_n[5])
{
  if( inte_val < max_z_val )
  {
    Real8 inte_val_sq = inte_val*inte_val;
    Real8 exp_inte_sq = exp(-1.0*inte_val_sq);
    Real8 multi_val   = rpi_inv*inte_val*exp_inte_sq;
    Real8 erf_val     = math_obj.calc_erf(inte_val);

    f_n[0] = erf_val;
    f_n[1] = rpi_inv * (1.0 - exp_inte_sq);
    f_n[2] = 0.5*erf_val - multi_val;
    f_n[3] =     f_n[1]  - multi_val * inte_val;
    f_n[4] = 1.5*f_n[2]  - multi_val * inte_val_sq;
  }
  else
  {
    f_n[0] = 1.0;
    f_n[1] = rpi_inv;
    f_n[2] = 0.5;
    f_n[3] = rpi_inv;
    f_n[4] = 0.75;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void BroadenedXSCalculator::calc_h_n_by_tayler_ex(int& n, Real8& inte_sta, Real8& inte_fin, Real8& h_n)
{
  Real8 inte_sta_abs = fabs(inte_sta);
  Real8 inte_fin_abs = fabs(inte_fin);

  if( inte_sta_abs >= max_z_val )
  {
    h_n = 0.0;
    return;
  }

  int ele_max = max_ex_order+n+1;
  int pow_max = ele_max - 1;
  
  Real8 min_limit = min_tayler_val;
  Real8 max_limit = 1.0 / min_tayler_val;
  
  Real8 *coef_x, *pow_x;
  coef_x = new Real8[ele_max];
  pow_x  = new Real8[ele_max];
  coef_x[0] = 0.0;
  pow_x[0]  = 1.0;
  for(int i=1; i<ele_max; i++)
  {
    coef_x[i] = 0.0;
    pow_x[i]  = pow_x[i-1] * inte_sta_abs;
    if( pow_x[i] < min_limit || pow_x[i] > max_limit )
    {
      if( i < ele_max-1 )
      {
        pow_x[i+1] = pow_x[i] * inte_sta_abs;
        pow_max = i+1;
      }
      else
      {
        pow_max = ele_max-1;
      }
      break;
    }
  }

  Real8 ene_dif = inte_fin_abs - inte_sta_abs;
  Real8 coef_g  = ene_dif;
  Real8 sign = 1.0;
  if( ene_dif < 0.0 )
  {
    sign = -1.0;
  }
  if( inte_fin < 0.0 && n%2 != 0 )
  {
    sign *= -1.0;
  }
  
  coef_x[n] = 1.0;
  if( n > pow_max )
  {
    h_n = 0.0;
    delete [] coef_x;
    delete [] pow_x;
    return;
  }
  
  //expansion order:1
  Real8 h_n_part;
  Real8 i_real, j_real;
  h_n     = coef_g * pow_x[n];
  i_real  = 1.0;
  for(int i=1; i<max_ex_order; i++)
  {
    int j_min = n-i;//-1;
    int j_max = n+i;//+1;
    if( j_min < 0 )
    {
      if( j_min%2 == 0 )
      {
        j_min = 0;
      }
      else
      {
        j_min = 1;
      }
    }
    if( j_max > pow_max )
    {
      j_max = pow_max;
    }
    
    j_real = static_cast<Real8>(j_min+1); 
    coef_x[j_min] = coef_x[j_min+1] * j_real;
    if( j_min != 0 )
    {
      coef_x[j_min] += -2.0*coef_x[j_min-1];
    }
    for(int j=j_min+2; j<=j_max; j+=2)
    {
      j_real   += 2.0;
      coef_x[j] = coef_x[j+1]*j_real - 2.0*coef_x[j-1];
    }
    coef_x[j_max] = -2.0*coef_x[j_max-1];
    if( j_max != pow_max )
    {
      coef_x[j_max] += coef_x[j_max+1] * j_real;
    }
    
    h_n_part = 0.0;
    for(int j=j_min; j<=j_max; j+=2)
    {
      h_n_part += coef_x[j] * pow_x[j];
    }
    i_real   += 1.0;
    coef_g   *= ene_dif / i_real;
    h_n_part *= coef_g;
    h_n      += h_n_part;

    if( fabs(h_n_part) < fabs(min_ene_dif*h_n) )
    {
      break;
    }
  }
  h_n *= sign * rpi_inv * exp(-1.0*pow_x[2]);

  delete [] coef_x;
  delete [] pow_x;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void BroadenedXSCalculator::preparation_for_doppler_broadening()
{
  calc_doppler_xs_flg = 1;

  if( ( temp_ori < 0.0 ) || ( temp_dop < 0.0 ) || ( dop_ene_max < 0.0 ) || ( mt_no == 0 ) )
  {
    string class_name = "BroadenedXSCalculator";
    string func_name  = "preparation_for_doppler_broadening()";

    ostringstream oss01, oss02, oss03, oss04;
    oss01 << mt_no;
    oss02 << temp_ori;
    oss03 << temp_dop;
    oss04 << dop_ene_max;
    string str_data01 = "Section number (MT)      : " + oss01.str();
    string str_data02 = "Initial temperature      : " + oss02.str();
    string str_data03 = "Doppler temperature      : " + oss03.str();
    string str_data04 = "Maximum broadened energy : " + oss04.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    if( mt_no == 0 )
    {
      err_com.push_back("The MT number is 0. Please check the program file.");
    }
    if( temp_ori < 0.0 )
    {
      err_com.push_back("The initial temperature is not set in BroadenedXSCalculator class.");
    }
    if( temp_dop < 0.0 )
    {
      err_com.push_back("The doppler temperature is not set in BroadenedXSCalculator class.");
    }
    if( dop_ene_max < 0.0 )
    {
      err_com.push_back("The maximum energy for broeder is not set in BroadenedXSCalculator class.");
    }
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //Calc base information
  awr     = nucl_data_obj.get_general_data_obj().get_mass();
  alpha   = awr / (boltzmann_const * (temp_dop - temp_ori));
  alpha_r = sqrt(alpha);
  v_coef  = 1.0;

  //Prepare coefficients for doppler calculation
  Real inte_zero = 0.0;
  calc_x(inte_zero, x_zero);
  
  x_data.clear();
  vector<Real> e_int, sig_tab;
  for(int i=0; i<mt_no; i++)
  {
    //Calculation of x_data and check the energy grid number
    e_int = xs_data_obj[i].get_xs_ene_data();
    if( i == 0 )
    {
      cp_vec.copy_vec_array1_real8(ene_data, e_int);
      
      grid_no = static_cast<int>(ene_data.size());
      sig_data.resize(grid_no);
      x_data.resize(grid_no);
      for(int j=0; j<grid_no; j++)
      {
        sig_data[j].resize(mt_no);
        calc_x(ene_data[j], x_data[j]);
      }
    }
    else
    {
      if( grid_no != static_cast<int>(e_int.size()) )
      {
        string class_name = "BroadenedXSCalculator";
        string func_name  = "preparation_for_doppler_broadening()";

        ostringstream oss00, oss01, oss02, oss03, oss04;
        oss00 << xs_data_obj[i].get_reaction_type();
        oss01 << i;
        oss02 << mt_no;
        oss03 << grid_no;
        oss04 << static_cast<int>(e_int.size());
        string str_data01 = "Section number (MT)         : " + oss00.str();
               str_data01+= " (" + oss01.str() + " / " + oss02.str() + " )";
        string str_data02 = "Size of energy grid at MT=1 : " + oss03.str();
        string str_data03 = "Size of energy grid at MT=" + oss01.str() + " : " + oss04.str();

        vector<string> err_com;
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back("Energy grid number is different to each MT number.");
        err_obj.output_runtime_error(class_name, func_name, err_com);
      }
    }
    e_int.clear();
    
    //Copy cross section data
    Real ene_top    = dop_ene_max * (1.0 - min_ene_dif);
    Real sig_xs_top = -1.0;
    Real coef_top   = -1.0; //xs = coef_top / sqrt(E) -> coef_top = xs * sqrt(E)
    sig_tab = xs_data_obj[i].get_xs_data();
    for(int j=0; j<grid_no; j++)
    {
      sig_data[j][i] = static_cast<Real8>(sig_tab[j]);

      //Cross section is modified when the incident energy is larger than dop_ene_max.
      //This modification is required to avoid using the averaged cross section
      //in the unresolve resonance region.
      //The cross section in the unresolved resonance region must not be used
      //the average cross section and must be used the cross section calculated
      //by 1/v low.
      if( ene_data[j] > ene_top )
      {
         if( sig_xs_top < 0 )
         {
           if( j==0 )
           {
             sig_xs_top = sig_data[j][i];
             coef_top = sig_xs_top * sqrt(ene_data[j]);
           }
           else
           {
             sig_xs_top = sig_data[j-1][i];
             coef_top = sig_xs_top * sqrt(ene_data[j-1]);
           }
         }

         sig_data[j][i] = coef_top / sqrt(ene_data[j]);
         if( sig_data[j][i] < min_value )
         {
            sig_data[j][i] = 0.0;
         }
      }
    }
    sig_tab.clear();
  }
  
  //Calculation of a_vec and c_vec (or s)
  calc_coef();
}


//////////////////////////////////////////////////////////////////////////////////////////////////////

//Calculation of a_vec and c_vec
void BroadenedXSCalculator::calc_coef()
{
  a_vec.resize(grid_no);
  c_vec.resize(grid_no);
  
  if( grid_no > 1 )
  {
    Real8         x_m, x_p;
    vector<Real8> sig_m, sig_p;
    sig_m.resize(mt_no);
    sig_p.resize(mt_no);
    x_m = 0.0;
    x_p = 0.0;
    
    Integer int_val = int_lin_lin;
    for(int i=0; i<mt_no; i++)
    {
      x_m      = 0.0;
      sig_m[i] = 0.0;
      
      ti_obj.interpolation_1d(int_val, x_m, sig_m[i], x_data[0], sig_data[0][i], x_data[1], sig_data[1][i]);
      x_p      = x_m;
      sig_p[i] = sig_m[i];
    }
    
    Real8 x_m_sq, x_p_sq, den;
    for(int i=0; i<grid_no; i++)
    {
      x_m    = x_p;
      x_p    = x_data[i];
      x_m_sq = x_m * x_m;
      x_p_sq = x_p * x_p;
      den    = 1.0 / (x_p_sq - x_m_sq);
      
      a_vec[i].resize(mt_no);
      c_vec[i].resize(mt_no);
      for(int j=0; j<mt_no; j++)
      {
        sig_m[j]    = sig_p[j];
        sig_p[j]    = sig_data[i][j];
        
        a_vec[i][j] = den*(sig_m[j]*x_p_sq - sig_p[j]*x_m_sq);
        c_vec[i][j] = den*(sig_p[j] - sig_m[j]);
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void BroadenedXSCalculator::calc_x(Real8& ene_val, Real8& x_val)
{
  x_val = alpha_r * sqrt(v_coef * ene_val);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void BroadenedXSCalculator::calc_y(Real8& ene_val, Real8& y_val)
{
  y_val = alpha_r * sqrt(v_coef * ene_val);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void BroadenedXSCalculator::clear()
{
  calc_doppler_xs_flg = 0;
  xs_part_flg         = 0;
  
  nucl_data_obj.clear();

  vector<CrossSectionDataContainer>().swap(xs_data_obj);
  //int i_max = static_cast<int>(xs_data_obj.size());
  //for(int i=0; i<i_max; i++)
  //{
  //  xs_data_obj[i].clear();
  //}
  //xs_data_obj.resize(0);
  
  mt_no              =  0;
  grid_no            =  0;
  
  awr                =  0.0;
  alpha              =  0.0;
  alpha_r            =  0.0;
  beta               =  0.0;
  beta_r             =  0.0;
  v_coef             =  0.0;
  v_t_sq             =  0.0;
  v_t_inv            =  0.0;

  y_val_pre          = -1.0;
  int_rang_m_min     =  0;
  int_rang_m_max     =  0;
  int_rang_p_min     =  0;
  int_rang_p_max     =  0;
  int_rang_m_min_pre = -1;
  int_rang_m_max_pre = -1;
  int_rang_p_min_pre = -1;
  int_rang_p_max_pre = -1;

  x_zero             = 0.0;
  
  ene_data.clear();
  x_data.clear();
  
  VectorClearer clr_obj;
  clr_obj.clear_vec_array2_real8(sig_data);
  clr_obj.clear_vec_array2_real8(a_vec);
  clr_obj.clear_vec_array2_real8(c_vec);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void BroadenedXSCalculator::calc_doppler_broadened_xs_from_xs_table
                              (Real temp_val_ori, Real temp_val_new, Real awr, vector<Integer>& mt_list,
                               vector<vector<Real> >& ene_vec, vector<vector<Real> >& xs_vec)
{
  clear();

  dop_ene_max = 1.0E+6; //The maximum doppler energy is 1 MeV.
  temp_ori    = temp_val_ori;
  temp_dop    = temp_val_new;

  if( fabs(temp_val_new - temp_val_ori) < 0.01*(1.0 + temp_val_ori) )
  {
    return;
  }
  else if( temp_val_new - temp_val_ori < min_value )
  {
    string class_name = "BroadenedXSCalculator";
    string func_name  = "calc_doppler_broadened_xs_from_xs_table";

    ostringstream oss01, oss02;
    oss01 << setw(8) << std::showpoint << temp_val_ori;
    oss02 << setw(8) << std::showpoint << temp_val_new;
    string str_data01 = "Temperature (original) : " + oss01.str();
    string str_data02 = "Temperature (new)      : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("Original temperature is larger than new temperature.");
    err_com.push_back("Please check the tempearture data.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //Check MT number
  int i_max   = static_cast<int>(mt_list.size());
  int tsl_flg = -1;
  for(int i=0; i<i_max; i++)
  {
    if( mt_list[i] >= 221 && mt_list[i] <= 250 )
    {
      tsl_flg = 1;
      break;
    }
  }
  if( tsl_flg > 0 )
  {
    string class_name = "BroadenedXSCalculator";
    string func_name  = "calc_doppler_broadened_xs_from_xs_table";

    ostringstream oss01, oss02;
    oss01 << setw(8) << std::showpoint << temp_val_ori;
    oss02 << setw(8) << std::showpoint << temp_val_new;
    string str_data01 = "Temperature (original) : " + oss01.str();
    string str_data02 = "Temperature (new)      : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("MT=221-250 is found in the MT list.");
    err_com.push_back("This data may be thermal scattering law data.");
    err_com.push_back("Doppler broadening calculation is skipped.");
    err_com.push_back("");
    err_com.push_back("MT list is as follows:");
    for(int i=0; i<i_max; i++)
    {
      ostringstream oss03;
      oss03 << mt_list[i]; 
      string str_data03 = "  " + oss03.str();
      if( mt_list[i] >= 221 && mt_list[i] <= 250 )
      {
        str_data03 = str_data03 + " *";
      }
      err_com.push_back(str_data03);
    }
    err_obj.output_caution(class_name, func_name, err_com);

    return;
  }

  //Set GeneralDataContainer
  GeneralDataContainer gen_data_obj;
  gen_data_obj.clear();

  gen_data_obj.set_mass(awr);

  nucl_data_obj.set_general_data_obj(gen_data_obj);


  //Check cross section data
  if( static_cast<int>(ene_vec.size()) != i_max ||
      static_cast<int>(xs_vec.size())  != i_max )
  {
    string class_name = "BroadenedXSCalculator";
    string func_name  = "calc_doppler_broadened_xs_from_xs_table";

    ostringstream oss01, oss02, oss03;
    oss01 << i_max;
    oss02 << static_cast<int>(ene_vec.size());
    oss03 << static_cast<int>(xs_vec.size());
    string str_data01 = "Reaction type number      : " + oss01.str();
    string str_data02 = "Energy data number        : " + oss02.str();
    string str_data03 = "Cross section data number : " + oss03.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("The reaction type number must be equal to the energy data number");
    err_com.push_back("and the cross section data number.");
    err_com.push_back("The cross section data list may be incorrect.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
  else if( i_max == 0 )
  {
    return;
  }

  for(int i=0; i<i_max; i++)
  {
    if( static_cast<int>(xs_vec[i].size()) == 0 )
    {
      continue;
    }

    if( static_cast<int>(ene_vec[i].size()) != static_cast<int>(xs_vec[i].size()) )
    {
      string class_name = "BroadenedXSCalculator";
      string func_name  = "calc_doppler_broadened_xs_from_xs_table";

      ostringstream oss01, oss02, oss03;
      oss01 << mt_list[i];
      oss02 << static_cast<int>(ene_vec[i].size());
      oss03 << static_cast<int>(xs_vec[i].size());
      string str_data01 = "Reaction type             : " + oss01.str();
      string str_data02 = "Energy grid number        : " + oss02.str();
      string str_data03 = "Cross section grid number : " + oss03.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back("The energy grid number must be equal to the cross section grid number.");
      err_com.push_back("The cross section data of this table may be incorrect.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }

  //Generate unified energy grid (ene_uni)
  TabAdjuster tab_ad_obj;
  vector<Real> ene_uni = ene_vec[0];
  for(int i=1; i<i_max; i++)
  {
    tab_ad_obj.add_grid_data(ene_uni, ene_vec[i]);
  }

  //Modify cross section data using unified energy grid (ene_uni)
  int ene_no = static_cast<int>(ene_uni.size());
  vector<Integer> nbt_vec, int_vec;
  nbt_vec.resize(1);
  int_vec.resize(1);
  nbt_vec[0] = ene_no;
  int_vec[0] = int_lin_lin;

  vector<vector<Real> > xs_vec_mod;
  xs_vec_mod.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    xs_vec_mod[i].clear();
    if( static_cast<int>(xs_vec[i].size()) > 0 )
    {
      xs_vec_mod[i].resize(ene_no);
      for(int j=0; j<ene_no; j++)
      {
        ti_obj.interpolation_1d(int_lin_lin, ene_uni[j], xs_vec_mod[i][j], ene_vec[i], xs_vec[i]);
      }
    }
  }

  //Set CrossSectionDataContainer
  //Add cross section data to xs_data_obj;
  vector<int> dop_calc_mt_list;
  dop_calc_mt_list.resize(i_max);
  vector<CrossSectionDataContainer>().swap(xs_data_obj);

  for(int i=0; i<i_max; i++)
  {
    dop_calc_mt_list[i] = -1;
    if( static_cast<int>(xs_vec_mod[i].size()) > 0 )
    {
      if( mt_list[i] < 1000 || mt_list[i] > 10000 )
      {
        //Skip Doppler broadening when xs_data is nu value or MF=9 data
        CrossSectionDataContainer xs_obj;
        xs_obj.set_reaction_type(mt_list[i]);
        xs_obj.set_xs_ene_data(ene_uni);
        xs_obj.set_xs_data(xs_vec_mod[i]);
        xs_obj.set_xs_range_data(nbt_vec);
        xs_obj.set_xs_int_data(int_vec);

        xs_data_obj.push_back(xs_obj);
        xs_obj.clear();

        dop_calc_mt_list[i] = static_cast<int>(xs_data_obj.size()) -1;
      }
    }
  }

  if( i_max > 0 )
  {
    cout << endl;
    cout << "  Doppler broadened MT list" << endl;
    for(int i=0; i<i_max; i++)
    {
      if( dop_calc_mt_list[i] >= 0 )
      {
        cout << "    " << mt_list[i] << endl;
      }
      else if( static_cast<int>(xs_vec_mod[i].size()) > 0 )
      {
        cout << "    " << mt_list[i] << "  **skip Doppler broadening**" << endl;
      }
    }
    cout << endl;
  }

  NuclearReactionDataContainer react_obj;
  react_obj.set_xs_data_obj(xs_data_obj);
  nucl_data_obj.set_nucl_reaction_data_obj(react_obj);
  react_obj.clear();

  mt_no = static_cast<int>(xs_data_obj.size());

  //Doppler broadening calculation
  for(int j=0; j<ene_no; j++)
  {
    if( ene_uni[j] < dop_ene_max )
    {
      vector<Real> xs_dop = calc_doppler_broadened_xs(ene_uni[j]);

      for(int i=0; i<i_max; i++)
      {
        if( dop_calc_mt_list[i] >= 0 )
        {
          //Skip nu values and MF=9 data
          xs_vec_mod[i][j] = xs_dop[dop_calc_mt_list[i]];
        }
      }
    }
  }

  for(int i=0; i<i_max; i++)
  {
    ene_vec[i] = ene_uni;
    xs_vec[i]  = xs_vec_mod[i];
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void BroadenedXSCalculator::set_nucl_data_obj(NuclearDataObject& data_obj)
{
  clear();

  nucl_data_obj = data_obj;

  xs_data_obj = nucl_data_obj.get_nucl_reaction_data_obj().get_xs_data_obj_assigned();

  mt_no = static_cast<int>(xs_data_obj.size()); 
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void BroadenedXSCalculator::set_temp_ori(Real8 real_val)
{
  calc_doppler_xs_flg = 0;
  temp_ori = real_val;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void BroadenedXSCalculator::set_temp_dop(Real8 real_val)
{
  calc_doppler_xs_flg = 0;
  temp_dop = real_val;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void BroadenedXSCalculator::set_dop_ene_max(Real8 real_val)
{
  calc_doppler_xs_flg = 0;
  dop_ene_max = real_val;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//Getter

Real8 BroadenedXSCalculator::get_temp_ori()
{
  return temp_ori;
}

Real8 BroadenedXSCalculator::get_temp_dop()
{
  return temp_dop;
}

Real8 BroadenedXSCalculator::get_dop_ene_max()
{
  return dop_ene_max;
}

NuclearDataObject BroadenedXSCalculator::get_nucl_data_obj()
{
  NuclearReactionDataContainer  nucl_reaction_data_obj = nucl_data_obj.get_nucl_reaction_data_obj();
  nucl_reaction_data_obj.add_xs_data_obj(xs_data_obj);
  nucl_data_obj.set_nucl_reaction_data_obj(nucl_reaction_data_obj);
  nucl_reaction_data_obj.clear();

  return nucl_data_obj;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

