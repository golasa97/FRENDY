#include "ReconResonance/ResonanceXSCalculatorByInterpolation.hpp"

using namespace frendy;

//constructor
ResonanceXSCalculatorByInterpolation::ResonanceXSCalculatorByInterpolation(void)
{
  clear();

  unreso_ene_base.clear();
  unreso_ene_base.resize(78);
  unreso_ene_base[ 0] = 1.00e+1;
  unreso_ene_base[ 1] = 1.25e+1;
  unreso_ene_base[ 2] = 1.50e+1;
  unreso_ene_base[ 3] = 1.70e+1;
  unreso_ene_base[ 4] = 2.00e+1;
  unreso_ene_base[ 5] = 2.50e+1;
  unreso_ene_base[ 6] = 3.00e+1;
  unreso_ene_base[ 7] = 3.50e+1;
  unreso_ene_base[ 8] = 4.00e+1;
  unreso_ene_base[ 9] = 5.00e+1;
  unreso_ene_base[10] = 6.00e+1;
  unreso_ene_base[11] = 7.20e+1;
  unreso_ene_base[12] = 8.50e+1;
  unreso_ene_base[13] = 1.00e+2;
  unreso_ene_base[14] = 1.25e+2;
  unreso_ene_base[15] = 1.50e+2;
  unreso_ene_base[16] = 1.70e+2;
  unreso_ene_base[17] = 2.00e+2;
  unreso_ene_base[18] = 2.50e+2;
  unreso_ene_base[19] = 3.00e+2;
  unreso_ene_base[20] = 3.50e+2;
  unreso_ene_base[21] = 4.00e+2;
  unreso_ene_base[22] = 5.00e+2;
  unreso_ene_base[23] = 6.00e+2;
  unreso_ene_base[24] = 7.20e+2;
  unreso_ene_base[25] = 8.50e+2;
  unreso_ene_base[26] = 1.00e+3;
  unreso_ene_base[27] = 1.25e+3;
  unreso_ene_base[28] = 1.50e+3;
  unreso_ene_base[29] = 1.70e+3;
  unreso_ene_base[30] = 2.00e+3;
  unreso_ene_base[31] = 2.50e+3;
  unreso_ene_base[32] = 3.00e+3;
  unreso_ene_base[33] = 3.50e+3;
  unreso_ene_base[34] = 4.00e+3;
  unreso_ene_base[35] = 5.00e+3;
  unreso_ene_base[36] = 6.00e+3;
  unreso_ene_base[37] = 7.20e+3;
  unreso_ene_base[38] = 8.50e+3;
  unreso_ene_base[39] = 1.00e+4;
  unreso_ene_base[40] = 1.25e+4;
  unreso_ene_base[41] = 1.50e+4;
  unreso_ene_base[42] = 1.70e+4;
  unreso_ene_base[43] = 2.00e+4;
  unreso_ene_base[44] = 2.50e+4;
  unreso_ene_base[45] = 3.00e+4;
  unreso_ene_base[46] = 3.50e+4;
  unreso_ene_base[47] = 4.00e+4;
  unreso_ene_base[48] = 5.00e+4;
  unreso_ene_base[49] = 6.00e+4;
  unreso_ene_base[50] = 7.20e+4;
  unreso_ene_base[51] = 8.50e+4;
  unreso_ene_base[52] = 1.00e+5;
  unreso_ene_base[53] = 1.25e+5;
  unreso_ene_base[54] = 1.50e+5;
  unreso_ene_base[55] = 1.70e+5;
  unreso_ene_base[56] = 2.00e+5;
  unreso_ene_base[57] = 2.50e+5;
  unreso_ene_base[58] = 3.00e+5;
  unreso_ene_base[59] = 3.50e+5;
  unreso_ene_base[60] = 4.00e+5;
  unreso_ene_base[61] = 5.00e+5;
  unreso_ene_base[62] = 6.00e+5;
  unreso_ene_base[63] = 7.20e+5;
  unreso_ene_base[64] = 8.50e+5;
  unreso_ene_base[65] = 1.00e+6;
  unreso_ene_base[66] = 1.25e+6;
  unreso_ene_base[67] = 1.50e+6;
  unreso_ene_base[68] = 1.70e+6;
  unreso_ene_base[69] = 2.00e+6;
  unreso_ene_base[70] = 2.50e+6;
  unreso_ene_base[71] = 3.00e+6;
  unreso_ene_base[72] = 3.50e+6;
  unreso_ene_base[73] = 4.00e+6;
  unreso_ene_base[74] = 5.00e+6;
  unreso_ene_base[75] = 6.00e+6;
  unreso_ene_base[76] = 7.20e+6;
  unreso_ene_base[77] = 8.50e+6;
}

//destructor
ResonanceXSCalculatorByInterpolation::~ResonanceXSCalculatorByInterpolation(void)
{
  clear();
  unreso_ene_base.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ResonanceXSCalculatorByInterpolation::calc_reso_xs_unreso_a
                                             (int i, int j, Real8& ene_val, vector<Real8>& sig_val)
{
  if( unreso_int_flg == direct_calc_mode )
  {
    ResonanceXSCalculator::calc_reso_xs_unreso_a(i, j, ene_val, sig_val);
  }
  else
  {
    calc_reso_xs_unreso_interpolation(i, j, ene_val, sig_val);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ResonanceXSCalculatorByInterpolation::calc_reso_xs_unreso_c
                                             (int i, int j, Real8& ene_val, vector<Real8>& sig_val)
{
  if( unreso_int_flg == direct_calc_mode )
  {
    ResonanceXSCalculator::calc_reso_xs_unreso_c(i, j, ene_val, sig_val);
  }
  else
  {
    calc_reso_xs_unreso_interpolation(i, j, ene_val, sig_val);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ResonanceXSCalculatorByInterpolation::calc_reso_xs_unreso_interpolation
                                             (int i, int j, Real8& ene_val, vector<Real8>& sig_val)
{
  int pos_m, pos_p;
  ti_obj.search_neighbor_value(ene_val, unreso_ene_grid, pos_m, pos_p);

  Integer int_val = unreso_int_data[pos_p];
  Real8   ene_m   = unreso_ene_grid[pos_m];
  Real8   ene_p   = unreso_ene_grid[pos_p];
  sig_val.resize(xs_type_no);

  //Calculation of scatter, fission and radiation cross sections by interpolation
  for(int k=1; k<xs_type_no; k++) 
  {
    if( unreso_sig_data[pos_m][k] < min_sig_val && unreso_sig_data[pos_p][k] < min_sig_val )
    {
      sig_val[k] = 0.0;
      continue;
    }

    ti_obj.interpolation_1d(int_val, ene_val, sig_val[k], ene_m, unreso_sig_data[pos_m][k],
                                                          ene_p, unreso_sig_data[pos_p][k]);
    if( sig_val[k] < min_sig_val )
    {
      sig_val[k] = 0.0;
    }
  }

  //Calculation of total cross section by sum of scatter, fission and radiation cross sections
  sig_val[total_xs] = sig_val[scatter_xs] + sig_val[fission_xs] + sig_val[radiation_xs];
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ResonanceXSCalculatorByInterpolation::set_multi_array_data_unreso_a(int i, int j)
{
  ResonanceXSCalculator::set_multi_array_data_unreso_a(i, j);

  calc_reso_xs_unreso_base(i, j);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ResonanceXSCalculatorByInterpolation::set_multi_array_data_unreso_c(int i, int j)
{
  ResonanceXSCalculator::set_multi_array_data_unreso_c(i, j);

  calc_reso_xs_unreso_base(i, j);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ResonanceXSCalculatorByInterpolation::calc_reso_xs_unreso_base(int i, int j)
{
  set_unreso_ene_grid(i, j);
  set_unreso_int_val(i, j);

  unreso_int_flg = direct_calc_mode;

  int k_max = static_cast<int>(unreso_ene_grid.size());
  clr_obj.clear_vec_array2_real8(unreso_sig_data);
  unreso_sig_data.resize(k_max);
  if( xs_formula_flg_multi == 1 )
  {
    for(int k=0; k<k_max; k++)
    {
      //For Case A and B
      unreso_sig_data[k].resize(xs_type_no);
      for(int l=0; l<xs_type_no; l++)
      {
        unreso_sig_data[k][l] = 0.0;
      }
      calc_reso_xs_unreso_a(i, j, unreso_ene_grid[k], unreso_sig_data[k]);
    }
  }
  else
  {
    for(int k=0; k<k_max; k++)
    {
      //For Case C
      unreso_sig_data[k].resize(xs_type_no);
      for(int l=0; l<xs_type_no; l++)
      {
        unreso_sig_data[k][l] = 0.0;
      }
      calc_reso_xs_unreso_c(i, j, unreso_ene_grid[k], unreso_sig_data[k]);
    }
  }

  unreso_int_flg = interpolation_mode;
} 

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ResonanceXSCalculatorByInterpolation::set_unreso_ene_grid(int i, int j)
{
  vector<Real8> ene_new = unreso_ene_base;

  int   i_max  = static_cast<int>(ene_array[i][j].size());
  Real8 el_val = ene_array[i][j][0];
  Real8 eh_val = ene_array[i][j][i_max-1];

  
  if( xs_formula_flg_multi == 1 && fis_width_flg[i] == 0 )
  {
    //Case A
  }
  else
  {
    i_max = static_cast<int>(es_multi.size());
    for(int i=0; i<i_max; i++)
    {
      int j_max = static_cast<int>(es_multi[i].size());
      for(int j=0; j<j_max; j++)
      {
        int k_max = static_cast<int>(es_multi[i][j].size());
        for(int k=0; k<k_max; k++)
        {
          ene_new.push_back(es_multi[i][j][k]);
        }
      }
    }
    sort(ene_new.begin(), ene_new.end());
  }

  int ele_no = 0;
  unreso_ene_grid.clear();
  unreso_ene_grid.push_back(el_val);

  i_max = static_cast<int>(ene_new.size());
  Real8 ene_min = el_val*(1.0+min_ene_dif);
  Real8 ene_max = eh_val*(1.0-min_ene_dif);
  for(int i=0; i<i_max; i++)
  {
    if( ene_new[i] > ene_min && ene_new[i] < ene_max )
    {
      if( (ene_new[i] - unreso_ene_grid[ele_no]) > min_ene_dif*ene_new[i] )
      {
        unreso_ene_grid.push_back(ene_new[i]);
        ele_no++;
      }
    }
    else if( ene_new[i] >= ene_max )
    {
      break;
    }
  }
  unreso_ene_grid.push_back(eh_val);
  ene_new.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ResonanceXSCalculatorByInterpolation::set_unreso_int_val(int i, int j)
{
  Integer int_val = 0;
  int     k_max   = static_cast<int>(unreso_ene_grid.size());
  unreso_int_data.resize(k_max);
  
  if( int_mode_flg == recomended_int_mode )
  {
    int_val = int_lin_lin; //Recomended by ENDF-6 Format Manual
  }
  else
  {
    int_val = int_log_log; //Used by NJOY99
  }
  for(int k=0; k<k_max; k++)
  {
    unreso_int_data[k] = int_val;
  }

  if( xs_formula_flg_multi != 1 )
  {
    //For Case C
    vector<vector<Integer> > int_data_nucl = reso_data_obj.get_unreso_data_obj(i,j).get_unreso_int_data();
    int l_max = static_cast<int>(int_data_nucl.size());

    if( l_max > 0 )
    {
      if( int_mode_flg == recomended_int_mode )
      {
        int ele_no = 0;
        for(int l=0; l<l_max; l++)
        {
          int m_max = static_cast<int>(int_data_nucl[l].size());
          for(int m=0; m<m_max; m++)
          {
            int   ene_no  = static_cast<int>(es_multi[l][m].size());
            Real8 el_val  = es_multi[l][m][0];
            Real8 eh_val  = es_multi[l][m][ene_no-1];
            int_val       = int_data_nucl[l][m];
            while( unreso_ene_grid[ele_no] < el_val )
            {
              ele_no++;
              if( ele_no == k_max )
              {
                break;
              }
            }
            while( unreso_ene_grid[ele_no] < eh_val*(1.0+min_ene_dif) )
            {
              unreso_int_data[ele_no] = int_val;
              ele_no++;
              if( ele_no == k_max )
              {
                break;
              }
            }
            if( ele_no == k_max )
            {
              break;
            }
          }
          if( ele_no == k_max )
          {
            break;
          }
        }
      }
      else
      {
        //NJOY99 uses int_data_nucl[l_max-1][m_max-1] as the interpolation scheme for all energy grid
        int m_max = static_cast<int>(int_data_nucl[l_max-1].size());
        if( m_max > 0 )
        {
          int_val = int_data_nucl[l_max-1][m_max-1];
          for(int k=0; k<k_max; k++)
          {
            unreso_int_data[k] = int_val;
          }
        }
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ResonanceXSCalculatorByInterpolation::clear()
{
  ResonanceXSCalculator::clear();
  clear_multi_array_data();

  int_mode_flg   = recomended_int_mode;
  unreso_int_flg = interpolation_mode;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ResonanceXSCalculatorByInterpolation::clear_multi_array_data()
{
  ResonanceXSCalculator::clear_multi_array_data();
  
  unreso_int_data.clear();
  unreso_ene_grid.clear();
  clr_obj.clear_vec_array2_real8(unreso_sig_data);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

