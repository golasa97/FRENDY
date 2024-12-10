#include "CommonUtils/TabAdjuster.hpp"

using namespace frendy;

//constructor
TabAdjuster::TabAdjuster(void)
{
}

//destructor
TabAdjuster::~TabAdjuster(void)
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void TabAdjuster:: modify_int_data(vector<Integer>& nbt_data, vector<Integer>& int_data)
{
  vector<Integer> nbt_mod, int_mod;

  int i_max = static_cast<int>(nbt_data.size());
  if( i_max == 0 )
  {
    string class_name = "TabAdjuster";
    string func_name  = "modify_int_data";
    vector<string> err_com;
    err_com.push_back("The data number of nbt_data is 0.");
    err_com.push_back("Please check nbt_data.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
  else if( i_max != static_cast<int>(int_data.size()) )
  {
    string class_name = "TabAdjuster";
    string func_name  = "modify_int_data";
    ostringstream oss01, oss02;
    oss01 << static_cast<int>(nbt_data.size());
    oss02 << static_cast<int>(int_data.size());
    string str_data01 = "The data number of nbt_data : " + oss01.str();
    string str_data02 = "The data number of int_data : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("The data number of nbt_data is not identical to that of int_data.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  int_mod.push_back(int_data[0]);

  Integer int_pre = int_data[0];
  Integer int_cur = -1;
  for(int i=1; i<i_max; i++)
  {
    int_cur = int_data[i];
    if( int_cur != int_pre )
    {
      int_mod.push_back(int_cur);
      nbt_mod.push_back(nbt_data[i-1]);
    }

    int_pre = int_cur;
  }
  nbt_mod.push_back(nbt_data[i_max-1]);

  nbt_data = nbt_mod;
  int_data = int_mod;
  nbt_mod.clear();
  int_mod.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void TabAdjuster::modify_x_grid(vector<Real>& x_ref,  vector<Integer>& nbt_data, vector<Integer>& int_data,
                                vector<Real>& x_data, vector<Real>& y_data)
{
  int i_max = static_cast<int>(x_ref.size());
  if( i_max == 0 )
  {
    string class_name = "TabAdjuster";
    string func_name  = "modify_x_grid";
    vector<string> err_com;
    err_com.push_back("The data number of reference x grid is 0.");
    err_com.push_back("Please check the reference x grid.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  vector<Integer> nbt_mod, int_mod;
  vector<Real>    x_mod,   y_mod;
  x_mod = x_ref;
  y_mod.resize(i_max);

  Real order_check_grid  = static_cast<Real>(check_order(x_mod));
  if( order_check_grid < 0.0 )
  {
    change_order_reverse_grid(x_mod);
  }

  Real order_check_table = static_cast<Real>(check_order(x_data));
  if( order_check_table < 0.0 )
  {
    change_order_reverse_table(nbt_data, int_data, x_data, y_data);
  }

  int     i_m     =  0;
  int     i_p     =  0;
  Integer int_cur = -1;
  Integer int_pre = -1;
  for(int i=0; i<i_max; i++)
  {
    //Adjust x_mod
    if( i > 0 )
    {
      if( x_mod[i] < x_mod[i-1] )
      {
        x_mod[i] = digit_obj.get_adjusted_value(x_mod[i-1], sig_fig, +1.0);
      }

      if( fabs(x_mod[i] - x_mod[i-1]) <= fabs(x_mod[i-1]*min_ene_dif) )
      {
        x_mod[i] = digit_obj.get_adjusted_value(x_mod[i], sig_fig, +1.0);
      }
    }

    //search neighbir value (x_data[i_m] < x < x_data[i_p])
    ti_obj.search_neighbor_value(x_mod[i], x_data, i_m, i_p);

    //search interporation method
    int_cur = ti_obj.search_interpolation_range(nbt_data, int_data, i_p);

    //Interpolation
    ti_obj.interpolation_1d(int_cur, x_mod[i], y_mod[i], x_data[i_m], y_data[i_m], x_data[i_p], y_data[i_p]);

    if( i == 0 )
    {
      int_mod.push_back(int_cur);
    }
    else if( int_cur != int_pre )
    {
      int_mod.push_back(int_cur);
      nbt_mod.push_back(static_cast<Integer>(i));
    }

    int_pre = int_cur;
  }
  nbt_mod.push_back(static_cast<Integer>(i_max));

  x_data   = x_mod;
  y_data   = y_mod;
  nbt_data = nbt_mod;
  int_data = int_mod;
  x_mod.clear();
  y_mod.clear();
  nbt_mod.clear();
  int_mod.clear();

  if( order_check_grid < 0.0 )
  {
    change_order_reverse_table(nbt_data, int_data, x_data, y_data);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void TabAdjuster::modify_x_grid_by_lin_lin(vector<Real>& x_ref,
                                           vector<Real>& x_data, vector<Real>& y_data)
{
  int i_max = static_cast<int>(x_ref.size());
  vector<Real> x_mod, y_mod;
  x_mod = x_ref;
  y_mod.resize(i_max);

  for(int i=0; i<i_max; i++)
  {
    //Adjust x_mod
    if( i > 0 )
    {
      if( x_mod[i] < x_mod[i-1] )
      {
        x_mod[i] = digit_obj.get_adjusted_value(x_mod[i-1], sig_fig, +1.0);
      }

      if( fabs(x_mod[i] - x_mod[i-1]) <= fabs(x_mod[i-1]*min_ene_dif) )
      {
        x_mod[i] = digit_obj.get_adjusted_value(x_mod[i], sig_fig, +1.0);
      }
    }

    ti_obj.interpolation_1d_in_range(int_lin_lin, x_mod[i], y_mod[i], x_data, y_data);
  }

  x_data = x_mod;
  y_data = y_mod;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Integer TabAdjuster::check_order(vector<Real>& grid_data)
{
  Integer order_check = 0;

  int i_max = static_cast<int>(grid_data.size());
  for(int i=1; i<i_max; i++)
  {
    if( fabs(grid_data[i] - grid_data[i-1]) > fabs(grid_data[i-1]*min_ene_dif) )
    {
      if( grid_data[i] > grid_data[i-1] )
      {
        order_check = +1; //ascending order
      }
      else //if( grid_data[i] < grid_data[i-1] )
      {
        order_check = -1; //descending order
      }
      break;
    }
  }

  return order_check;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void TabAdjuster::change_order_reverse_grid(vector<Real>& grid_data)
{
  int i_max = static_cast<int>(grid_data.size());

  vector<Real> grid_data_mod;
  grid_data_mod.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    grid_data_mod[i] = grid_data[i_max-i-1];
  }

  grid_data = grid_data_mod;

  grid_data_mod.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void TabAdjuster::change_order_reverse_grid(vector<Integer>& grid_data)
{
  int i_max = static_cast<int>(grid_data.size());

  vector<Integer> grid_data_mod;
  grid_data_mod.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    grid_data_mod[i] = grid_data[i_max-i-1];
  }

  grid_data = grid_data_mod;

  grid_data_mod.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void TabAdjuster::change_order_reverse_table(vector<Integer>& nbt_data, vector<Integer>& int_data,
                                             vector<Real>&    x_data,   vector<Real>&    y_data)
{
  change_order_reverse_grid(x_data);
  change_order_reverse_grid(y_data);

  int     i_max   = static_cast<int>(nbt_data.size());
  Integer grid_no = static_cast<Integer>(x_data.size());

  vector<Integer> nbt_mod;
  nbt_mod.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    if( i == 0 )
    {
      nbt_mod[i] = grid_no;
    }
    else
    {
      nbt_mod[i] = grid_no - nbt_data[i-1];
    }
  }
  nbt_data = nbt_mod;
  nbt_mod.clear();

  change_order_reverse_grid(nbt_data);
  change_order_reverse_grid(int_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void TabAdjuster::delete_overlap_grid(vector<Real>& x_grid)
{
  vector<Real> sorted_data;
  sorted_data.clear();

  int i_max = static_cast<int>(x_grid.size());
  if( i_max == 0 )
  {
    return;
  }

  sort(x_grid.begin(), x_grid.end());

  //For ENDF-6 format (Double precision -> 11 digit data)
  vector<Real> x_grid_mod = x_grid;
  for(int i=0; i<i_max; i++)
  {
    x_grid_mod[i] = digit_obj.get_truncation_value(x_grid_mod[i]);
  }

  int         mod_grid_no = 1;
  vector<int> overlap_flg;
  overlap_flg.resize(i_max);
  overlap_flg[0] = 1;

  Real x_pre, x_cur, x_pre_mod, x_cur_mod;
  x_pre     = x_grid[0];
  x_pre_mod = x_grid_mod[0];
  for(int i=1; i<i_max; i++)
  {
    overlap_flg[i] = 0;

    x_cur     = x_grid[i];
    x_cur_mod = x_grid_mod[i];

    Real dif_val = min_ene_dif;
    if( fabs(x_pre) > min_value )
    {
      dif_val *= fabs(x_pre);
    }

    if( x_cur - x_pre > dif_val && x_cur_mod - x_pre_mod > dif_val )
    {
      overlap_flg[i] = 1;
      mod_grid_no++;

      x_pre     = x_cur;
      x_pre_mod = x_cur_mod;
    }
  }

  vector<Real> x_mod;
  x_mod.resize(mod_grid_no);

  int ele_no = 0;
  for(int i=0; i<i_max; i++)
  {
    if( overlap_flg[i] > 0 )
    {
      x_mod[ele_no] = x_grid[i];
      ele_no++;
    }
  }

  x_grid = x_mod;
  x_mod.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void TabAdjuster::delete_overlap_grid(vector<Integer>& nbt_data, vector<Integer>& int_data,
                                      vector<Real>& x_data, vector<Real>& y_data)
{
  vector<Real> x_ref = x_data;
  delete_overlap_grid(x_ref);

  modify_x_grid(x_ref, nbt_data, int_data, x_data, y_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void TabAdjuster::adjust_overlap_grid(vector<Real>& x_grid)
{
  vector<Real> x_new = x_grid;

  int i_max = static_cast<int>(x_grid.size());
  if( i_max == 0 )
  {
    return;
  }

  //For ENDF-6 format (Double precision -> 11 digit data)
  vector<Real> x_grid_mod = x_grid;
  for(int i=0; i<i_max; i++)
  {
    x_grid_mod[i] = digit_obj.get_truncation_value(x_grid_mod[i]);
  }
  vector<Real> x_new_mod = x_grid_mod;

  Real x_pre, x_cur, x_pre_mod, x_cur_mod;
  x_pre     = x_grid[0];
  x_pre_mod = x_grid_mod[0];
  for(int i=1; i<i_max; i++)
  {
    x_cur     = x_grid[i];
    x_cur_mod = x_grid_mod[i];

    Real dif_val = min_ene_dif;
    if( fabs(x_pre) > min_value )
    {
      dif_val *= fabs(x_pre);
    }

    if( fabs(x_cur - x_pre) < dif_val || fabs(x_cur_mod - x_pre_mod) < dif_val )
    {
      x_new[i-1]     = digit_obj.get_adjusted_value(x_new[i-1], sig_fig, -1.0);
      x_new_mod[i-1] = digit_obj.get_adjusted_value(x_new_mod[i-1], sig_fig, -1.0);

      if( i-2 > 0 )
      {
        for(int j=i-2; j>0; j--)
        {
          if( fabs(x_new[j+1] - x_new[j]) < dif_val || fabs(x_new_mod[j+1] - x_new_mod[j]) < dif_val )
          {
            x_new[j]     = digit_obj.get_adjusted_value(x_new[j],     sig_fig, -1.0);
            x_new_mod[j] = digit_obj.get_adjusted_value(x_new_mod[j], sig_fig, -1.0);
          }
          else
          {
            break;
          }
        }
      }
    }
    x_pre     = x_cur;
    x_pre_mod = x_cur_mod;
  }

  x_grid = x_new;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void TabAdjuster::add_grid_data(vector<Real>& x_data, vector<Real>& add_data)
{
  int x_max   = static_cast<int>(x_data.size());
  int add_max = static_cast<int>(add_data.size());

  Real max_add_val = 0.0;
  if( x_max > 0 && add_max > 0 )
  {
    max_add_val = x_data[x_max-1] * 1.01;
    if( max_add_val < add_data[add_max-1] )
    {
      max_add_val = add_data[add_max-1] * 1.01;
    }
  }
  else if( x_max > 0 )
  {
    max_add_val = x_data[x_max-1] * 1.01;
  }
  else if( add_max > 0 )
  {
    max_add_val = add_data[add_max-1] * 1.01;
  }

  add_grid_data(x_data, add_data, max_add_val);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void TabAdjuster::add_grid_data(vector<Real>& x_data, vector<Real>& add_data, Real max_add_val)
{
  int add_no = static_cast<int>(add_data.size());
  if( add_no == 0 )
  {
    return;
  }

  vector<Real> add_data_mod = add_data;
  for(int i=0; i<add_no; i++)
  {
    if( add_data_mod[i] > max_add_val )
    {
      add_data_mod[i] = max_add_val;
    }
  }
  delete_overlap_grid(add_data_mod);
  
  int x_no = static_cast<int>(x_data.size());
  if( x_no == 0 )
  {
    x_data = add_data_mod;
    return;
  }

  add_no = 0;
  vector<int> pos_vec = search_add_grid_pos(x_data, add_data_mod, add_no);

  if( add_no == 0 )
  {
    return;
  }

  vector<Real> x_mod;
  x_mod.resize(x_no + add_no);

  int j      = 0;
  int j_max  = static_cast<int>(pos_vec.size());
  int ele_no = 0;
  for(int i=0; i<x_no; i++)
  {
    while( j < j_max && pos_vec[j] <= i )
    {
      if( pos_vec[j] >= 0 )
      {
        x_mod[ele_no] = add_data_mod[j];
        ele_no++;
      }
      j++;

      if( j >= j_max )
      {
        break;
      }
    }

    x_mod[ele_no] = x_data[i];
    ele_no++;
  }

  if( j < j_max )
  {
    for(int k=j; k<j_max; k++)
    {
      x_mod[ele_no] = add_data_mod[k];
      ele_no++;
    }
  }

  x_data = x_mod;
  x_mod.clear();
    
  delete_overlap_grid(x_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void TabAdjuster::add_grid_data(vector<Real>& x_data, Real& add_data, int& pos)
{
  int i_max = static_cast<int>(x_data.size());
  if( i_max == 0 )
  {
    pos = 0;
    x_data.push_back(add_data);
    return;
  }

  Real diff_val = fabs(min_ene_dif*add_data);
  if( diff_val < min_value )
  {
    diff_val = min_value;
  }

  pos = -10;
  if( add_data <= x_data[0] + min_ene_dif )
  {
    if( fabs(x_data[0] - add_data) > diff_val )
    {
      pos = 0;
      x_data.insert(x_data.begin(), add_data);
    }
  }
  else if( x_data[i_max-1] - min_ene_dif < add_data )
  {
    if( fabs(x_data[i_max-1] - add_data) > diff_val )
    {
      pos = i_max;
      pos = i_max;
      x_data.push_back(add_data);
    }
    else
    {
      pos -= i_max;
    } 
  }
  else
  {
    int i_m, i_p;
    ti_obj.search_neighbor_value(add_data, x_data, i_m, i_p);
    if( fabs(x_data[i_m] - add_data) > diff_val &&
        fabs(x_data[i_p] - add_data) > diff_val )
    {
      pos = i_p;
      x_data.insert(x_data.begin() + pos, add_data);
    }
    else
    {
      pos -= i_p;
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void TabAdjuster::add_grid_data(vector<Real>& x_data, Real& add_data)
{
  int pos = 0;
  add_grid_data(x_data, add_data, pos);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<int> TabAdjuster::search_add_grid_pos(vector<Real>& x_data, vector<Real>& add_data, int& add_no)
{
  vector<int> pos_vec;

  int  x_no  = static_cast<int>(x_data.size());
  Real x_min = x_data[0];
  Real x_max = x_data[x_no-1];

  int i_max  = static_cast<int>(add_data.size());

  add_no = 0;
  pos_vec.resize(i_max);
  for(int i=0; i<i_max ; i++)
  {
    pos_vec[i] = -1;
    if( add_data[i] < x_min )
    {
      if( fabs(add_data[i] - x_min) > fabs(min_ene_dif * x_min) )
      {
        pos_vec[i] = 0;
        add_no++;
      }
    }
    else if( add_data[i] > x_max )
    {
      if( fabs(add_data[i] - x_max) > fabs(min_ene_dif * x_max) )
      {
        pos_vec[i] = x_no;
        add_no++;
      }
    }
    else
    {
      int i_m, i_p;
      ti_obj.search_neighbor_value(add_data[i], x_data, i_m, i_p);
      if( fabs(add_data[i] - x_data[i_m]) > fabs(min_ene_dif * x_data[i_m] ) &&
          fabs(add_data[i] - x_data[i_p]) > fabs(min_ene_dif * x_data[i_p] ) )
      {
        pos_vec[i] = i_p;
        add_no++;
      }
    }
  }

  return pos_vec;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void TabAdjuster::add_table_data(vector<Real>& x_data, vector<Real>& y_data,
                                 Real& add_x_data,     Real& add_y_data)
{
  int i_max = static_cast<int>(y_data.size());
  if( static_cast<int>(x_data.size()) != i_max )
  {
    string class_name = "TabAdjuster";
    string func_name  = "add_table_data";
    ostringstream oss01, oss02;
    oss01 << static_cast<int>(x_data.size());
    oss02 << static_cast<int>(y_data.size());
    string str_data01 = "The data number of x_data : " + oss01.str();
    string str_data02 = "The data number of y_data : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("The data number of x_data is not identical to that of y_data.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  int pos = 0;
  add_grid_data(x_data, add_x_data, pos);
  add_grid_data_at_given_position(y_data, add_y_data, pos);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void TabAdjuster::add_table_data(vector<Real>& x_data, vector<vector<Real> >& y_data,
                                 Real& add_x_data,     vector<Real>& add_y_data)
{
  int i_max = static_cast<int>(y_data.size());
  if( static_cast<int>(x_data.size()) != i_max )
  {
    string class_name = "TabAdjuster";
    string func_name  = "add_table_data";
    ostringstream oss01, oss02;
    oss01 << static_cast<int>(x_data.size());
    oss02 << static_cast<int>(y_data.size());
    string str_data01 = "The data number of x_data : " + oss01.str();
    string str_data02 = "The data number of y_data : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("The data number of x_data is not identical to that of y_data.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  int pos = 0;
  add_grid_data(x_data, add_x_data, pos);
  add_grid_data_at_given_position(y_data, add_y_data, pos);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void TabAdjuster::add_grid_data_at_given_position(vector<Real>& x_data, Real& add_data, int pos)
{
  int i_max = static_cast<int>(x_data.size());

  if( pos >= i_max )
  {
    x_data.push_back(add_data);
  }
  else if( pos >= 0 )
  {
    x_data.insert(x_data.begin() + pos, add_data);
  }
  else
  {
    string class_name = "TabAdjuster";
    string func_name  = "add_grid_data_at_given_position";
    ostringstream oss01;
    oss01 << pos;
    string str_data01 = "The position data : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("The position data is less than 0.");
    err_com.push_back("This data is not added.");
    err_obj.output_caution(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void TabAdjuster::add_grid_data_at_given_position(vector<vector<Real> >& x_data, vector<Real>& add_data,
                                                  int pos)
{
  int i_max = static_cast<int>(x_data.size());

  if( pos >= i_max )
  {
    x_data.push_back(add_data);
  }
  else if( pos >= 0 )
  {
    x_data.insert(x_data.begin() + pos, add_data);
  }
  else
  {
    string class_name = "TabAdjuster";
    string func_name  = "add_grid_data_at_given_position";
    ostringstream oss01;
    oss01 << pos;
    string str_data01 = "The position data : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("The position data is less than 0.");
    err_com.push_back("This data is not added.");
    err_obj.output_caution(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void TabAdjuster::add_table_data_at_given_position(vector<Real>& x_data, vector<Real>& y_data,
                                                   Real& add_x_data, Real& add_y_data, int pos)
{
  int i_max = static_cast<int>(y_data.size());
  if( static_cast<int>(x_data.size()) != i_max )
  {
    string class_name = "TabAdjuster";
    string func_name  = "add_table_data_at_given_position";
    ostringstream oss01, oss02;
    oss01 << static_cast<int>(x_data.size());
    oss02 << static_cast<int>(y_data.size());
    string str_data01 = "The data number of x_data : " + oss01.str();
    string str_data02 = "The data number of y_data : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("The data number of x_data is not identical to that of y_data.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  add_grid_data_at_given_position(x_data, add_x_data, pos);
  add_grid_data_at_given_position(y_data, add_y_data, pos);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void TabAdjuster::add_table_data_at_given_position(vector<Real>& x_data, vector<vector<Real> >& y_data,
                                                   Real& add_x_data, vector<Real>& add_y_data, int pos)
{
  int i_max = static_cast<int>(y_data.size());
  if( static_cast<int>(x_data.size()) != i_max )
  {
    string class_name = "TabAdjuster";
    string func_name  = "add_table_data_at_given_position";
    ostringstream oss01, oss02;
    oss01 << static_cast<int>(x_data.size());
    oss02 << static_cast<int>(y_data.size());
    string str_data01 = "The data number of x_data : " + oss01.str();
    string str_data02 = "The data number of y_data : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("The data number of x_data is not identical to that of y_data.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  add_grid_data_at_given_position(x_data, add_x_data, pos);
  add_grid_data_at_given_position(y_data, add_y_data, pos);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void TabAdjuster::remove_zero_data(vector<Integer>& nbt_data, vector<Integer>& int_data,
                                   vector<Real>&    x_data,   vector<Real>&    y_data)
{
  //Check number of table data
  int i_max  = static_cast<int>(y_data.size());
  if( i_max == 0 )
  {
    nbt_data.clear();
    int_data.clear();
    x_data.clear();
    y_data.clear();
  }
  else if( i_max == 2 )
  {
    //Not need to modify table data
    return;
  }
  else if( i_max < 2 )
  {
    string class_name = "TabAdjuster";
    string func_name  = "remove_zero_xs_data";
    ostringstream oss01;
    oss01 << i_max;
    string str_data01 = "Data number : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("Data number is less than 2.");
    err_com.push_back("This data is not appropriate for table data.");
    err_obj.output_caution(class_name, func_name, err_com);

    return;
  }

  //Search less than zero data
  int remove_zero_data_flg = -1;
  for(int i=0; i<i_max; i++)
  {
    if( y_data[i] > min_value )
    {
      remove_zero_data_flg = i;
      break;
    }
  }

  if( remove_zero_data_flg == -1 )
  {
    if( i_max == 0 )
    {
      return;
    }

    nbt_data.resize(1);
    int_data.resize(1);
    int_data[0] = int_lin_lin;
    if( i_max == 1 )
    {
      nbt_data[0] = 1;
    }
    else
    {
      nbt_data[0] = 2;

      vector<Real> x_new, y_new;
      x_new.resize(2);
      y_new.resize(2);
      x_new[0] = x_data[0];
      x_new[1] = x_data[i_max-1];
      y_new[0] = y_data[0];
      y_new[1] = y_data[i_max-1];

      x_data = x_new;
      y_data = y_new;
      x_new.clear();
      y_new.clear();
    }
    return;
  }
  else if( remove_zero_data_flg <= 1 )
  {
    return;
  }

  //Modify table data
  vector<Integer> nbt_new, int_new;
  vector<Real>    x_new,   y_new;

  int ele_no = i_max - remove_zero_data_flg + 1;
  if( ele_no > 1 )
  {
    //Modify x and y data (remove zero data without first element)
    x_new.resize(ele_no);
    y_new.resize(ele_no);
    ele_no = 0;
    for(int i=remove_zero_data_flg-1; i<i_max; i++)
    {
      x_new[ele_no] =  x_data[i];
      y_new[ele_no] =  y_data[i];
      ele_no++;
    }

    //Modify nbt and int data
    Integer remove_data_no = static_cast<Integer>(remove_zero_data_flg);
    i_max = static_cast<int>(nbt_data.size());
    for(int i=0; i<i_max; i++)
    {
      if( nbt_data[i] > remove_data_no )
      {
        nbt_new.push_back(nbt_data[i] - remove_data_no + 1);
        int_new.push_back(int_data[i]);
      }
    }
  }
  else 
  {
    //Set dummy table data
    ele_no = 2;
    x_new.resize(ele_no);
    y_new.resize(ele_no);
    x_new[0] = x_data[0];
    x_new[1] = x_data[i_max-1];
    y_new[0] = 0.0;
    y_new[1] = 0.0;
  }

  if( static_cast<int>(nbt_new.size()) == 0 )
  {
    int int_max = static_cast<int>(int_data.size());
    nbt_new.resize(1);
    int_new.resize(1);
    nbt_new[0] = static_cast<Integer>(x_new.size());
    int_new[0] = int_data[int_max-1];
  }

  nbt_data = nbt_new;
  int_data = int_new;
  x_data   = x_new;
  y_data   = y_new;
  nbt_new.clear();
  int_new.clear();
  x_new.clear();
  y_new.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void TabAdjuster::remove_specified_grid(vector<Integer>& nbt_data, vector<Integer>& int_data,
                                        vector<Real>&    x_data,   vector<Real>&    y_data,
                                        int remove_grid_pos)
{
  int i_max = static_cast<int>(x_data.size());
  if( i_max == 0 )
  {
    //There is no grid data
    return;
  }

  if( remove_grid_pos < 0 || remove_grid_pos > i_max-1 )
  {
    //Out of range
    return;
  }

  //Modify x and y data
  vector<Real> x_new, y_new;
  x_new.resize(i_max - 1);
  y_new.resize(i_max - 1);

  int ele_no = 0;
  for(int i=0; i<i_max; i++)
  {
    if( remove_grid_pos == i )
    {
      continue;
    }

    x_new[ele_no] = x_data[i];
    y_new[ele_no] = y_data[i];
    ele_no++;
  }
  x_data = x_new;
  y_data = y_new;
  x_new.clear();
  y_new.clear();

  //Modify nbt and int data
  i_max = static_cast<int>(nbt_data.size());
  if( i_max == 0 )
  {
    return;
  }

  int overlap_flg = 0;
  for(int i=0; i<i_max; i++)
  {
    if( nbt_data[i] >= remove_grid_pos+1 )
    {
      nbt_data[i]--;
    }
    if( nbt_data[i] <= 0 )
    {
      overlap_flg++;
    }
    else if( i > 0 )
    {
      if( nbt_data[i] <= nbt_data[i-1] )
      {
        overlap_flg++;
      }
    }
  }

  //Remove overlapped data
  if( overlap_flg > 0 )
  {
    vector<Integer> nbt_new, int_new;
    for(int i=0; i<i_max; i++)
    {
      if( nbt_data[i] > 0 )
      {
        if( i==0 )
        {
          nbt_new.push_back(nbt_data[i]);
          int_new.push_back(int_data[i]);
        }
        else if( nbt_data[i] > nbt_data[i-1] )
        {
          nbt_new.push_back(nbt_data[i]);
          int_new.push_back(int_data[i]);
        }
      }
    }
    nbt_data = nbt_new;
    int_data = int_new;
    nbt_new.clear();
    int_new.clear();
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void TabAdjuster::remove_specified_grid(vector<Integer>& nbt_data, vector<Integer>& int_data,
                                        vector<Real>&    x_data,   vector<Real>&    y_data,
                                        vector<int> remove_grid_pos)
{
  //Sort remove_grid_pos and remove overlapped position
  int i_max = static_cast<int>(remove_grid_pos.size());
  sort(remove_grid_pos.begin(), remove_grid_pos.end());
  vector<int> remove_grid_pos_new;

  remove_grid_pos_new.push_back(remove_grid_pos[0]);
  int pos_pre = remove_grid_pos[0];
  for(int i=1; i<i_max; i++)
  {
    if( remove_grid_pos[i] != pos_pre )
    {
      remove_grid_pos_new.push_back(remove_grid_pos[i]);
      pos_pre = remove_grid_pos[i];
    }
  }
  remove_grid_pos = remove_grid_pos_new;

  //Remove specified grid
  i_max = static_cast<int>(remove_grid_pos.size());
  for(int i=0; i<i_max; i++)
  {
    remove_specified_grid(nbt_data, int_data, x_data, y_data, remove_grid_pos[i] - i);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void TabAdjuster::remove_descending_order_data(vector<Integer>& nbt_data, vector<Integer>& int_data,
                                               vector<Real>&    x_data,   vector<Real>&    y_data)
{
  int i_max = static_cast<int>(x_data.size());
  if( i_max <= 1 )
  {
    return;
  }

  vector<int> remove_element;
  remove_element.clear();

  Real x_pre = x_data[0];
  for(int i=1; i<i_max; i++)
  {
    if( x_data[i] < x_pre )
    {
      remove_element.push_back(i);
    }
    else
    {
      x_pre = x_data[i];
    }
  }

  if( static_cast<int>(remove_element.size()) > 0 )
  {
    remove_specified_grid(nbt_data, int_data, x_data, y_data, remove_element);
  }
}

