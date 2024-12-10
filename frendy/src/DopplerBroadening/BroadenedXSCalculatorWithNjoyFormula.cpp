#include "DopplerBroadening/BroadenedXSCalculatorWithNjoyFormula.hpp"

using namespace frendy;

//constructor
BroadenedXSCalculatorWithNjoyFormula::BroadenedXSCalculatorWithNjoyFormula(void)
{
  clear();
}

//destructor
BroadenedXSCalculatorWithNjoyFormula::~BroadenedXSCalculatorWithNjoyFormula(void)
{
  clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

vector<Real8> BroadenedXSCalculatorWithNjoyFormula::calc_doppler_broadened_xs_part
                                                      (Real8& y_val, int int_min, int int_max)
{
  vector<Real8> sig_val;
  Real8 f_a, f_b;
  Real8 h_n[5], f_n_pre[5];
  Real8 inte_sta, inte_sta_tmp, inte_fin;
  Real8 y1, y2, y1_inv, y2_inv;
  y1 = y_val;
  y2 = y1*y1;
  y1_inv = 1.0 / y1;
  y2_inv = y1_inv * y1_inv;

  //Calculation of initial f_n value
  inte_sta_tmp = 0.0;
  if( int_min != 0 )
  {
    inte_sta = x_data[int_min-1] - y_val;
    calc_f_n(inte_sta, f_n_pre);
  }
  else
  {
    inte_sta = x_zero - y_val;

    inte_sta_tmp = y_val - x_data[0];
    if( xs_part_flg < 0 )
    {
      inte_sta_tmp = 0.0 - y_val;
      //inte_sta_tmp = x_data[int_max] - y_val;
    }
    calc_f_n(inte_sta_tmp, f_n_pre);
  }

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
      if( i > 0 )
      {
        calc_h_n(inte_sta, inte_fin, h_n, f_n_pre);
        f_a = y2_inv*h_n[2] + 2.0*y1_inv*h_n[1] +     h_n[0];
        f_b = y2_inv*h_n[4] + 4.0*y1_inv*h_n[3] + 6.0*h_n[2] + 4.0*y1*h_n[1] + y2*h_n[0];
      
        for(int j=0; j<mt_no; j++)
        {
          sig_val[j] += f_a*s1_vec[i][j] + f_b*s2_vec[i][j];
        }
      }
      else
      {
        if( xs_part_flg > 0 )
        {
          Real8 inte_fin_zero = y_val;
          calc_h_n(inte_sta_tmp, inte_fin_zero, h_n, f_n_pre);
        }
        else
        {
          Real8 inte_fin_zero = x_data[i] - y_val;
          calc_h_n(inte_sta_tmp, inte_fin_zero, h_n, f_n_pre);
        }

        for(int j=0; j<mt_no; j++)
        {
          if( xs_part_flg > 0 )
          {
            sig_val[j] -= sig_data[i][j]*x_data[i]*(y2_inv*h_n[1] - y1_inv*h_n[0]);
          }
          else
          {
            sig_val[j] += sig_data[i][j]*x_data[i]*(y2_inv*h_n[1] + y1_inv*h_n[0]);
          }
        }
        inte_sta = x_data[i] - y_val;
        calc_f_n(inte_sta, f_n_pre);
      }
    }
    else
    {
      inte_sta_tmp = x_data[i] - y_val;
      calc_f_n(inte_sta_tmp, f_n_pre);
    }
  }

  return sig_val;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void BroadenedXSCalculatorWithNjoyFormula::calc_h_n(Real8& inte_sta, Real8& inte_fin,
                                                    Real8 h_n[5], Real8 f_n_sta[5])
{
  Real8 f_n_fin[5]; //, h_n_tayler;
  calc_f_n(inte_fin, f_n_fin);
  
  if( inte_sta < max_z_val || inte_fin < max_z_val )
  {
    for(int i=0; i<5; i++)
    {
      h_n[i] = f_n_sta[i] - f_n_fin[i];
      /*
      if( fabs(h_n[i]) > min_tayler_val )
      {
        if( fabs(h_n[i]) <= fabs(tayler_calc_condition*f_n_fin[i]) )
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

void BroadenedXSCalculatorWithNjoyFormula::calc_f_n(Real8& inte_val, Real8 f_n[5])
{
  if( inte_val < max_z_val )
  {
    Real8 inte_val_sq = inte_val*inte_val;
    Real8 exp_inte_sq = exp(-1.0*inte_val_sq);
    Real8 multi_val   = rpi_inv*inte_val*exp_inte_sq;
    Real8 erf_val     = math_obj.calc_erf(inte_val);
    f_n[0] = 0.5*(1.0 - erf_val);
    f_n[1] = 0.5*rpi_inv * exp_inte_sq;
    f_n[2] = 0.5*(f_n[0]  + multi_val);
    f_n[3] = 0.5*(2.0*f_n[1]  + multi_val * inte_val);
    f_n[4] = 0.5*(3.0*f_n[2]  + multi_val * inte_val_sq);
  }
  else
  {
    f_n[0] = 0.0;
    f_n[1] = 0.0;
    f_n[2] = 0.0;
    f_n[3] = 0.0;
    f_n[4] = 0.0;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

//Calculation of s
void BroadenedXSCalculatorWithNjoyFormula::calc_coef()
{
  s1_vec.resize(grid_no);
  s2_vec.resize(grid_no);
  
  if( grid_no > 1 )
  {
    Integer       int_val = int_lin_lin; 
    Real8         x_m, x_p;
    vector<Real8> sig_m, sig_p;
    sig_m.resize(mt_no);
    sig_p.resize(mt_no);
    x_m = 0.0;
    x_p = 0.0;
    
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
      
      s1_vec[i].resize(mt_no);
      s2_vec[i].resize(mt_no);
      for(int j=0; j<mt_no; j++)
      {
        sig_m[j] = sig_p[j];
        sig_p[j] = sig_data[i][j];
        
        s2_vec[i][j] = (sig_p[j] - sig_m[j])*den;
        s1_vec[i][j] = (sig_m[j] - s2_vec[i][j]*x_m_sq);
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void BroadenedXSCalculatorWithNjoyFormula::clear()
{
  BroadenedXSCalculator::clear();

  VectorClearer clr_obj;
  clr_obj.clear_vec_array2_real8(s1_vec);
  clr_obj.clear_vec_array2_real8(s2_vec);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

