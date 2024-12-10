#include "TabUtils/TwoDInterpolator.hpp"

using namespace frendy;

//constructor
TwoDInterpolator::TwoDInterpolator(void)
{
  clear();
}

//destructor
TwoDInterpolator::~TwoDInterpolator(void)
{
  clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void TwoDInterpolator::clear()
{
  clr_obj.clear_vec_array2_real(x1_array);
  clr_obj.clear_vec_array2_real(y1_array);
  clr_obj.clear_vec_array2_real(x2_array);
  clr_obj.clear_vec_array2_real(y2_array);

  data_no_each_bin.clear();

  x1_range_inv.clear();
  clr_obj.clear_vec_array2_real(x1_array_diff);
  clr_obj.clear_vec_array2_real(x1_array_ori);
  clr_obj.clear_vec_array2_real(x2_array_ori);
  clr_obj.clear_vec_array2_real(x_mce_array);
  clr_obj.clear_vec_array2_real(y_mce_array);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void TwoDInterpolator::make_array_data(int bin_no, vector<Real> x_vec, vector<Real> y_vec,
                                       vector<vector<Real> >& x_array,
                                       vector<vector<Real> >& y_array)
{
  //Integration of x_vec, y_vec
  vector<Integer> nbt_vec, int_vec;
  nbt_vec.resize(1);
  int_vec.resize(1);
  nbt_vec[0] = static_cast<Integer>(x_vec.size());
  int_vec[0] = int_lin_lin;

  int x_no = static_cast<int>(x_vec.size());
  if( x_no == 0 )
  {
    x_array.resize(bin_no);
    y_array.resize(bin_no);
    for(int i=0; i<bin_no; i++)
    {
      x_array[i].resize(2);
      y_array[i].resize(2);
      x_array[i][0] = -1.0E10;
      x_array[i][1] =  1.0E10;
      y_array[i][0] =  0.0;
      y_array[i][1] =  0.0;
    }
    return;
  }

  Real y_integ = integ_obj.integrate_tab1_data(nbt_vec, int_vec, x_vec, y_vec);

  //Remove zero data
  remove_zero_data(x_vec, y_vec);

  x_array.resize(bin_no);
  y_array.resize(bin_no);

  x_no = static_cast<int>(x_vec.size());
  if( x_no == 0 )
  {
    for(int i=0; i<bin_no; i++)
    {
      x_array[i].resize(2);
      y_array[i].resize(2);
      x_array[i][0] = -1.0E10;
      x_array[i][1] =  1.0E10;
      y_array[i][0] =  0.0;
      y_array[i][1] =  0.0;
    }
    return;
  }

  vector<Real> x_mod = x_vec;
  vector<Real> y_mod = y_vec;
  lin_obj.calc_equal_probability_table_by_tabulated_probability_data
            (int_lin_lin, bin_no, y_integ, x_mod, y_mod);

  vector<Real> x_max;
  x_max.resize(bin_no);
  for(int i=0; i<bin_no; i++)
  {
    x_max[i] = x_mod[i+1];

    ti_obj.interpolation_1d(int_lin_lin, x_max[i], y_mod[i], x_vec, y_vec);
  }

  int j_max = static_cast<int>(x_vec.size());
  int j=0;
  for(int i=0; i<bin_no; i++)
  {
    vector<Real> x_new, y_new;
    x_new.clear();
    y_new.clear();

    if( j < j_max )
    {
      if( i!=0 )
      {
        if( fabs(x_max[i-1] - x_vec[j]) > fabs(min_ene_dif * x_max[i-1]) )
        {
          x_new.push_back(x_max[i-1]);
          y_new.push_back(y_mod[i-1]);
        }
      }

      while( j < j_max && x_max[i] - x_vec[j] > fabs(min_ene_dif * x_max[i]) )
      {
        x_new.push_back(x_vec[j]);
        y_new.push_back(y_vec[j]);
        j++;

        if( j >= j_max )
        {
          break;
        }
      }
    }

    int ele_no = static_cast<int>(x_new.size());
    if( ele_no > 0 )
    {
      if( fabs(x_new[ele_no-1] - x_max[i]) > min_ene_dif * x_max[i] )
      {
        x_new.push_back(x_max[i]);
        y_new.push_back(y_mod[i]);
      }
    }
    else
    {
      x_new.resize(2);
      y_new.resize(2);
      x_new[0] = -1.0E10;
      x_new[1] =  1.0E10;
      y_new[0] =  0.0;
      y_new[1] =  0.0;
    }

    x_array[i] = x_new;
    y_array[i] = y_new;
    x_new.clear();
    y_new.clear();
  }
  nbt_vec.clear();
  int_vec.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void TwoDInterpolator::remove_zero_data(vector<Real>& x_vec, vector<Real>& y_vec)
{
  int i_max = static_cast<int>(x_vec.size());
  if( i_max == 0 )
  {
    return;
  }

  int x_min = 0;
  int x_max = i_max - 1;

  for(int i=0; i<i_max; i++)
  {
    if( fabs(y_vec[i]) > min_value )
    {
      if( i == 0 )
      {
        x_min = i;
      }
      else
      {
        x_min = i-1;
      }

      break;
    }
  }

  for(int i=i_max-1; i>=0; i--)
  {
    if( fabs(y_vec[i]) > min_value )
    {
      if( i == i_max-1 )
      {
        x_max = i;
      }
      else
      {
        x_max = i+1;
      }

      break;
    }
  }

  int x_no = x_max - x_min + 1;
  if( x_no != i_max )
  {
    vector<Real> x_new, y_new;
    x_new.resize(x_no);
    y_new.resize(x_no);

    for(int i=0; i<x_no; i++)
    {
      x_new[i] = x_vec[i+x_min];
      y_new[i] = y_vec[i+x_min];
    }

    x_vec = x_new;
    y_vec = y_new;
    x_new.clear();
    y_new.clear();
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void TwoDInterpolator::mce_interpolation_each_bin(Real z_val, int int_tab2,
                         vector<Real>& x1_vec, vector<Real>& y1_vec, Real z1_val,
                         vector<Real>& x2_vec, vector<Real>& y2_vec, Real z2_val,
                         vector<Real>& x_new,  vector<Real>& y_new)
{
  int x1_no = static_cast<int>(x1_vec.size());
  int x2_no = static_cast<int>(x2_vec.size());
  Real8 x1_range        = fabs(x1_vec[x1_no-1] - x1_vec[0]);
  Real8 x2_range        = fabs(x2_vec[x2_no-1] - x2_vec[0]);

  Real x_low, x_high;
  ti_obj.interpolation_1d(int_tab2, z_val, x_low,
                          z1_val, x1_vec[0], z2_val, x2_vec[0]);
  ti_obj.interpolation_1d(int_tab2, z_val, x_high,
                          z1_val, x1_vec[x1_no-1], z2_val, x2_vec[x2_no-1]);

  Real x_range          = fabs(x_high - x_low);
  Real x1_range_mod     = x_range / x1_range;
  Real x2_range_mod     = x_range / x2_range;
  Real x1_range_mod_inv = 1.0 / x1_range_mod;
  Real x2_range_mod_inv = 1.0 / x2_range_mod;

  vector<Real>  x1_mod = x1_vec;
  for(int i=0; i<x1_no; i++)
  {
    x1_mod[i] = (x1_vec[i] - x1_vec[0]) * x1_range_mod + x_low;
  }

  vector<Real>  x2_mod = x2_vec;
  for(int i=0; i<x2_no; i++)
  {
    x2_mod[i] = (x2_vec[i] - x2_vec[0]) * x2_range_mod + x_low;
  }

  //Generate union grid
  x_new = x1_mod;
  ta_obj.add_grid_data(x_new, x2_mod);

  //Modify y1_vec and y2_vec using same grid (x_new)
  int i_max = static_cast<int>(x_new.size());
  y_new.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    Real x_diff = x_new[i] - x_low;
    Real x1_val = x_diff * x1_range_mod_inv + x1_vec[0];
    Real x2_val = x_diff * x2_range_mod_inv + x2_vec[0];

    Real y1_val = 0.0;
    Real y2_val = 0.0;
    ti_obj.interpolation_1d(int_lin_lin, x1_val, y1_val, x1_vec, y1_vec);
    ti_obj.interpolation_1d(int_lin_lin, x2_val, y2_val, x2_vec, y2_vec);

    ti_obj.interpolation_1d(int_tab2, z_val, y_new[i], z1_val, y1_val, z2_val, y2_val);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void TwoDInterpolator::merge_array_data(vector<vector<Real> >& x_array,
                                        vector<vector<Real> >& y_array,
                                        vector<Real>& x_vec, vector<Real>& y_vec)
{
  int bin_no  = static_cast<int>(x_array.size());
  if( bin_no == 0 )
  {
    x_vec.clear();
    y_vec.clear();
    return;
  }
  else if( bin_no == 1 )
  {
    x_vec = x_array[0];
    y_vec = y_array[0];
    return;
  }

  x_vec.resize(data_no_total);
  y_vec.resize(data_no_total);

  int ele_no = 0;
  for(int i=0; i<bin_no; i++)
  {
    if( data_no_each_bin[i] > 0 && ele_no == 0 )
    {
      x_vec[ele_no] = x_array[i][0];
      y_vec[ele_no] = y_array[i][0];
      ele_no++;
    }

    for(int j=1; j<data_no_each_bin[i]; j++)
    {
      x_vec[ele_no] = x_array[i][j];
      y_vec[ele_no] = y_array[i][j];
      ele_no++;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

//  ########################################
//  ###  Method of corresponding energy  ###
//  ########################################

//Interpolation by MCE
void TwoDInterpolator::mce_interpolation
                         (Real z_val, int bin_no, int int_tab2,
                          vector<Integer>& nbt1_vec, vector<Integer>& int1_vec,
                          vector<Real>&    x1_vec,   vector<Real>&    y1_vec,   Real z1_val,
                          vector<Integer>& nbt2_vec, vector<Integer>& int2_vec,
                          vector<Real>&    x2_vec,   vector<Real>&    y2_vec,   Real z2_val,
                          vector<Integer>& nbt_new,  vector<Integer>& int_new,
                          vector<Real>&    x_new,    vector<Real>&    y_new)
{
  mce_interpolation(z_val, bin_no, int_tab2,
                    nbt1_vec, int1_vec, x1_vec, y1_vec, z1_val,
                    nbt2_vec, int2_vec, x2_vec, y2_vec, z2_val,
                    x_new,  y_new);

  nbt_new.resize(1);
  int_new.resize(1);
  nbt_new[0] = static_cast<Integer>(x_new.size());
  int_new[0] = int_lin_lin;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

//Interpolation law of (x_new, y_new) is linear-linear.
void TwoDInterpolator::mce_interpolation
                         (Real z_val, int bin_no, int int_tab2,
                          Integer int1_val, vector<Real>& x1_vec, vector<Real>& y1_vec, Real z1_val,
                          Integer int2_val, vector<Real>& x2_vec, vector<Real>& y2_vec, Real z2_val,
                          vector<Real>& x_new, vector<Real>& y_new)
{
  vector<Real>    x1_new   = x1_vec;
  vector<Real>    y1_new   = y1_vec;
  vector<Real>    x2_new   = x2_vec;
  vector<Real>    y2_new   = y2_vec;

  if( int1_val != int_lin_lin )
  {
    lin_obj.linearize_data(int1_val, x1_new, y1_new);
  }

  if( int2_val != int_lin_lin )
  {
    lin_obj.linearize_data(int2_val, x2_new, y2_new);
  }
  
  mce_interpolation(z_val, bin_no, int_tab2,
                    x1_new,  y1_new,  z1_val, x2_new,  y2_new, z2_val, x_new, y_new);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

//Interpolation law of (x_new, y_new) is linear-linear.
void TwoDInterpolator::mce_interpolation
                         (Real z_val, int bin_no, int int_tab2,
                          vector<Integer>& nbt1_vec, vector<Integer>& int1_vec,
                          vector<Real>&    x1_vec,   vector<Real>&    y1_vec,   Real z1_val, 
                          vector<Integer>& nbt2_vec, vector<Integer>& int2_vec,
                          vector<Real>&    x2_vec,   vector<Real>&    y2_vec,   Real z2_val,
                          vector<Real>&    x_new,    vector<Real>&    y_new)
{
  vector<Integer> nbt1_new = nbt1_vec;
  vector<Integer> int1_new = int1_vec;
  vector<Real>    x1_new   = x1_vec;
  vector<Real>    y1_new   = y1_vec;
  vector<Integer> nbt2_new = nbt2_vec;
  vector<Integer> int2_new = int2_vec;
  vector<Real>    x2_new   = x2_vec;
  vector<Real>    y2_new   = y2_vec;

  lin_obj.linearize_tab1_data(nbt1_new, int1_new, x1_new, y1_new);
  lin_obj.linearize_tab1_data(nbt2_new, int2_new, x2_new, y2_new);

  mce_interpolation(z_val, bin_no, int_tab2,
                    x1_new,  y1_new,  z1_val, x2_new,  y2_new, z2_val, x_new, y_new);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

//Interpolation law of (x1, y1), (x2, y2), (x_new, y_new) are linear-linear.
void TwoDInterpolator::mce_interpolation(Real z_val, int bin_no, int int_tab2,
                                         vector<Real>& x1_vec, vector<Real>& y1_vec, Real z1_val,
                                         vector<Real>& x2_vec, vector<Real>& y2_vec, Real z2_val,
                                         vector<Real>& x_new,  vector<Real>& y_new)
{
  if( static_cast<int>(x1_vec.size()) == 0 && static_cast<int>(x2_vec.size()) == 0 )
  {
    clr_obj.clear_vec_array2_real(x1_array);
    clr_obj.clear_vec_array2_real(y1_array);
    clr_obj.clear_vec_array2_real(x2_array);
    clr_obj.clear_vec_array2_real(y2_array);
    x_new.clear();
    y_new.clear();
    return;
  }

  set_array_data(bin_no, x1_vec, y1_vec, x2_vec, y2_vec);
  mce_interpolation_without_set_array(z_val, int_tab2, z1_val, z2_val, x_new, y_new);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void TwoDInterpolator::set_array_data
                         (int& bin_no, vector<Real>& x1_vec, vector<Real>& y1_vec,
                                       vector<Real>& x2_vec, vector<Real>& y2_vec)
{
  clr_obj.clear_vec_array2_real(x1_array);
  clr_obj.clear_vec_array2_real(y1_array);
  clr_obj.clear_vec_array2_real(x2_array);
  clr_obj.clear_vec_array2_real(y2_array);

  if( bin_no <= 0 )
  {
    string class_name = "TwoDInterpolator";
    string func_name  = "set_array_data";
    ostringstream oss01;
    oss01 << bin_no;
    string str_data01 = "bin_no : " + oss01.str();
    string str_data02 = "The bin number is less than or equal to 0.";

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("The bin number is less than or equal to 0.");
    err_com.push_back("The bin number is modified to 1.");
    err_com.push_back("(unit base interpolation)");
    err_obj.output_caution(class_name, func_name, err_com);

    bin_no = 1;
  }

  if( bin_no > 1 ) //For MCE
  {
    make_array_data(bin_no, x1_vec, y1_vec, x1_array, y1_array);
    make_array_data(bin_no, x2_vec, y2_vec, x2_array, y2_array);
  }
  else //if( bin_no == 1 ) //For unit base
  {
    x1_array.resize(1);
    x2_array.resize(1);
    y1_array.resize(1);
    y2_array.resize(1);

    x1_array[0] = x1_vec;
    x2_array[0] = x2_vec;
    y1_array[0] = y1_vec;
    y2_array[0] = y2_vec;

    remove_zero_data(x1_array[0], y1_array[0]);
    remove_zero_data(x2_array[0], y2_array[0]);
  }

  set_normarized_table_data(bin_no);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void TwoDInterpolator::set_normarized_table_data(int bin_no)
{
  x1_array_ori = x1_array;
  x2_array_ori = x2_array;

  data_no_total = 1;

  data_no_each_bin.resize(bin_no);
  x1_range_inv.resize(bin_no);
  x1_array_diff.resize(bin_no);
  x_mce_array.resize(bin_no);
  y_mce_array.resize(bin_no);
  for(int i=0; i<bin_no; i++)
  {
    int x1_no = static_cast<int>(x1_array[i].size());
    int x2_no = static_cast<int>(x2_array[i].size());
    Real8 x1_range        = fabs(x1_array[i][x1_no-1] - x1_array[i][0]);
    Real8 x2_range        = fabs(x2_array[i][x2_no-1] - x2_array[i][0]);
    x1_range_inv[i]       = 1.0 / x1_range;

    Real x1_low           = x1_array[i][0];
    Real x2_low           = x2_array[i][0];
    Real x2_range_mod     = x1_range / x2_range;
    Real x2_range_mod_inv = 1.0 / x2_range_mod;

    vector<Real> x1_union, x2_union;
    x2_union.resize(x2_no);
    for(int j=0; j<x2_no; j++)
    {
      x2_union[j] = (x2_array[i][j] - x2_array[i][0]) * x2_range_mod + x1_low;
    }

    //Generate union grid
    x1_union = x2_union;
    for(int j=0; j<x1_no; j++)
    {
      x1_union.push_back(x1_array[i][j]);
    }
    ta_obj.delete_overlap_grid(x1_union);

    int j_max = static_cast<int>(x1_union.size());
    x1_array_diff[i].resize(j_max);
    x2_union.resize(j_max);

    data_no_each_bin[i] = j_max;
    if( j_max > 0 )
    {
      data_no_total += j_max - 1;
    }

    vector<Real> y1_union, y2_union;
    y1_union.resize(j_max);
    y2_union.resize(j_max);
    x_mce_array[i].resize(j_max);
    y_mce_array[i].resize(j_max);
    for(int j=0; j<j_max; j++)
    {
      x1_array_diff[i][j] = x1_union[j] - x1_low;
      x2_union[j] = x1_array_diff[i][j] * x2_range_mod_inv + x2_low;

      ti_obj.interpolation_1d(int_lin_lin, x1_union[j], y1_union[j], x1_array[i], y1_array[i]);
      ti_obj.interpolation_1d(int_lin_lin, x2_union[j], y2_union[j], x2_array[i], y2_array[i]);

      x_mce_array[i][j] = 0.0;
      y_mce_array[i][j] = 0.0;
    }
    x1_array[i] = x1_union;
    y1_array[i] = y1_union;
    x2_array[i] = x2_union;
    y2_array[i] = y2_union;

    x1_union.clear();
    y1_union.clear();
    x2_union.clear();
    y2_union.clear();
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void TwoDInterpolator::mce_interpolation_without_set_array
                         (Real z_val, int int_tab2, Real z1_val, Real z2_val,
                          vector<Real>& x_new, vector<Real>& y_new)
{
  int bin_no = static_cast<int>(x1_array.size());
  if( bin_no == 0 && static_cast<int>(x2_array.size()) == 0 )
  {
    x_new.clear();
    y_new.clear();
    return;
  }

  
  int z1_flg = 0;
  int z2_flg = 0;
  if( z_val < z1_val && z_val < z2_val )
  {
    if( z1_val < z2_val ) // z_val < z1_val < z2_val
    {
      z1_flg = 1;
    }
    else
    {
      z2_flg = 1;
    }
  }
  else if( z_val > z1_val && z_val > z2_val )
  {
    if( z1_val > z2_val ) // z_val > z1_val > z2_val
    {
      z1_flg = 1;
    }
    else
    {
      z2_flg = 1;
    }
  }

  if( z1_flg > 0 )
  {
    merge_array_data(x1_array, y1_array, x_new, y_new);
    return;
  }
  else if( z2_flg > 0 )
  {
    merge_array_data(x2_array, y2_array, x_new, y_new);
    return;
  }

  for(int i=0; i<bin_no; i++)
  {
//    mce_interpolation_each_bin(z_val, int_tab2, x1_array[i], y1_array[i], z1_val,
//                                                x2_array[i], y2_array[i], z2_val,
//                                                x_mce_array[i], y_mce_array[i]);

    int x1_no = static_cast<int>(x1_array_ori[i].size());
    int x2_no = static_cast<int>(x2_array_ori[i].size());

    Integer int_tab_each = int_tab2%10; //21 -> 1
    Real x_low, x_high, x_range_mod;
    ti_obj.interpolation_1d(int_tab_each, z_val, x_low,
                            z1_val, x1_array_ori[i][0],       z2_val, x2_array_ori[i][0]);
    ti_obj.interpolation_1d(int_tab_each, z_val, x_high,
                            z1_val, x1_array_ori[i][x1_no-1], z2_val, x2_array_ori[i][x2_no-1]);
    x_range_mod = fabs(x_high - x_low) * x1_range_inv[i];

    if( int_tab_each != int_tab2 )
    {
      int_tab_each = int_tab2/10; //21 -> 2
    }

    int j_max = static_cast<int>(x1_array[i].size());
    for(int j=0; j<j_max; j++)
    {
      x_mce_array[i][j] = x1_array_diff[i][j] * x_range_mod + x_low;

      ti_obj.interpolation_1d(int_tab_each, z_val, y_mce_array[i][j],
                                            z1_val, y1_array[i][j], z2_val, y2_array[i][j]);
    }
  }
  
  merge_array_data(x_mce_array, y_mce_array, x_new, y_new);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

//Get y value using MCE interpolation
Real TwoDInterpolator::mce_interpolation
                         (Real z_val, Real x_val, int bin_no, int int_tab2,
                          vector<Integer>& nbt1_vec, vector<Integer>& int1_vec,
                          vector<Real>&    x1_vec,   vector<Real>&    y1_vec,   Real z1_val,
                          vector<Integer>& nbt2_vec, vector<Integer>& int2_vec,
                          vector<Real>&    x2_vec,   vector<Real>&    y2_vec,   Real z2_val)
{
  vector<Real> x_new, y_new;
  mce_interpolation(z_val, bin_no, int_tab2, 
                    nbt1_vec, int1_vec, x1_vec, y1_vec, z1_val,
                    nbt2_vec, int2_vec, x2_vec, y2_vec, z2_val, x_new, y_new);

  int  int_tab1 = int_lin_lin;
  Real y_val    = 0.0;
  ti_obj.interpolation_1d(int_tab1, x_val, y_val, x_new, y_new);

  return y_val;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

//Get y value using MCE interpolation
//Interpolation law of (x1, y1), (x2, y2), (x_new, y_new) are linear-linear.
Real TwoDInterpolator::mce_interpolation
                         (Real z_val, Real x_val, int bin_no, int int_tab2,
                          vector<Real>&    x1_vec,   vector<Real>&    y1_vec,  Real z1_val,
                          vector<Real>&    x2_vec,   vector<Real>&    y2_vec,  Real z2_val)
{
  vector<Real> x_new, y_new;
  mce_interpolation(z_val, bin_no, int_tab2, x1_vec, y1_vec, z1_val,
                                             x2_vec, y2_vec, z2_val, x_new, y_new);

  int  int_tab1 = int_lin_lin;
  Real y_val    = 0.0;
  ti_obj.interpolation_1d(int_tab1, x_val, y_val, x_new, y_new);  

  return y_val;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

//  #################################
//  ###  Unit base interpolation  ###
//  #################################

//Interpolation by unit base 
void TwoDInterpolator::unit_base_interpolation
                         (Real z_val, int int_tab2,
                          vector<Integer>& nbt1_vec, vector<Integer>& int1_vec,
                          vector<Real>&    x1_vec,   vector<Real>&    y1_vec,   Real z1_val,
                          vector<Integer>& nbt2_vec, vector<Integer>& int2_vec,
                          vector<Real>&    x2_vec,   vector<Real>&    y2_vec,   Real z2_val,
                          vector<Integer>& nbt_new,  vector<Integer>& int_new,
                          vector<Real>&    x_new,    vector<Real>&    y_new)
{
  int bin_no = 1;
  mce_interpolation(z_val, bin_no, int_tab2, 
                    nbt1_vec, int1_vec, x1_vec, y1_vec, z1_val,
                    nbt2_vec, int2_vec, x2_vec, y2_vec, z2_val,
                    nbt_new,  int_new,  x_new,  y_new);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

//Interpolation law of (x_new, y_new) is linear-linear.

void TwoDInterpolator::unit_base_interpolation
                         (Real z_val, int int_tab2,
                          Integer int1_val, vector<Real>& x1_vec, vector<Real>& y1_vec, Real z1_val,
                          Integer int2_val, vector<Real>& x2_vec, vector<Real>& y2_vec, Real z2_val,
                          vector<Real>& x_new, vector<Real>& y_new)
{
  int bin_no = 1;
  mce_interpolation(z_val, bin_no, int_tab2,
                    int1_val,  x1_vec,  y1_vec, z1_val,
                    int2_val,  x2_vec,  y2_vec, z2_val,
                    x_new,     y_new);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

//Interpolation law of (x_new, y_new) is linear-linear.
void TwoDInterpolator::unit_base_interpolation
                         (Real z_val, int int_tab2,
                          vector<Integer>& nbt1_vec, vector<Integer>& int1_vec,
                          vector<Real>&    x1_vec,   vector<Real>&    y1_vec,    Real z1_val,
                          vector<Integer>& nbt2_vec, vector<Integer>& int2_vec,
                          vector<Real>&    x2_vec,   vector<Real>&    y2_vec,    Real z2_val,
                          vector<Real>&    x_new,    vector<Real>&    y_new)
{
  int bin_no = 1;
  mce_interpolation(z_val, bin_no, int_tab2, 
                    nbt1_vec, int1_vec, x1_vec, y1_vec, z1_val,
                    nbt2_vec, int2_vec, x2_vec, y2_vec, z2_val,
                    x_new,  y_new);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

//Interpolation law of (x1, y1), (x2, y2), (x_new, y_new) are linear-linear.
void TwoDInterpolator::unit_base_interpolation
                         (Real z_val, int int_tab2,
                          vector<Real>&    x1_vec,   vector<Real>&    y1_vec, Real z1_val,
                          vector<Real>&    x2_vec,   vector<Real>&    y2_vec, Real z2_val,
                          vector<Real>&    x_new,    vector<Real>&    y_new)
{
  int bin_no = 1;
  mce_interpolation(z_val, bin_no, int_tab2, 
                    x1_vec, y1_vec, z1_val, x2_vec, y2_vec, z2_val, x_new,  y_new);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

//Get y value using unit base interpolation
Real TwoDInterpolator::unit_base_interpolation
                         (Real z_val, Real y_val, int int_tab2,
                          vector<Integer>& nbt1_vec, vector<Integer>& int1_vec,
                          vector<Real>&    x1_vec,   vector<Real>&    y1_vec,   Real z1_val,
                          vector<Integer>& nbt2_vec, vector<Integer>& int2_vec,
                          vector<Real>&    x2_vec,   vector<Real>&    y2_vec,   Real z2_val)
{
  int bin_no = 1;
  return mce_interpolation(z_val, y_val, bin_no, int_tab2, 
                           nbt1_vec, int1_vec, x1_vec, y1_vec, z1_val,
                           nbt2_vec, int2_vec, x2_vec, y2_vec, z2_val);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

//Get y value using unit base interpolation
//Interpolation law of (x1, y1), (x2, y2), (x_new, y_new) are linear-linear.
Real TwoDInterpolator::unit_base_interpolation
                         (Real z_val, Real y_val, int int_tab2,
                          vector<Real>&    x1_vec,   vector<Real>&    y1_vec, Real z1_val,
                          vector<Real>&    x2_vec,   vector<Real>&    y2_vec, Real z2_val)
{
  int bin_no = 1;
  return mce_interpolation(z_val, y_val, bin_no, int_tab2,
                           x1_vec, y1_vec, z1_val, x2_vec, y2_vec, z2_val);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

