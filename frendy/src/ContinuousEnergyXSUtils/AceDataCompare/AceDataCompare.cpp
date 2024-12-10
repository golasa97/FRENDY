#include "ContinuousEnergyXSUtils/AceDataCompare/AceDataCompare.hpp"

using namespace frendy;

//Initialize static const value
const Real AceDataCompare::min_relative_dif  = 1.0E-20;

const Real AceDataCompare::tolerance_val_def = 1.0E-3;
const Real AceDataCompare::min_val_def       = 1.0E-30;

//constructor
AceDataCompare::AceDataCompare(void)
{
  clear();
}

//destructor
AceDataCompare::~AceDataCompare(void)
{
  clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataCompare::clear()
{
  class_name.clear();
  func_name.clear();
  data_name.clear();
  pos_data.clear();
  comment_data.clear();

  list_flg    = no_list_data_mode;
  tab_flg     = no_table_data_mode;
  data_no     = 0;
  data_no_max = 0;

  x_val       = 0.0;

  comp_data_flg = comp_all_data_mode;

  set_tolerance_val_def();
  set_min_val_def();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataCompare::output_information_data()
{
  cout << "Class name            : " << class_name << endl;
  cout << "Function name         : " << func_name  << endl;

  if( data_name.empty() == 0 )
  {
    cout << "Data name information : " << data_name << endl;
  }

  if( pos_data.empty() == 0 )
  {
    cout << "Index information     : " << pos_data << endl;
  }

  if( comment_data.empty() == 0 )
  {
    cout << "Other information     : " << comment_data << endl;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataCompare::comp_int_data(Integer int_val, Integer int_val_ref)
{
  if( int_val_ref != int_val )
  {
    if( tab_flg != no_table_data_mode && list_flg == list_data_mode )
    {
      if( int_val_ref == max_data_no || int_val == max_data_no )
      {
        return;
      }
    }

    output_information_data();
    if( tab_flg != no_table_data_mode )
    {
      if( list_flg == list_data_mode )
      {
        cout << "  The integer number of the table data is not identical." << endl;
        cout << "    Data position             : " << data_no+1 << " / " << data_no_max << endl;
      }
      else if( list_flg == list_data_no_mode )
      {
        cout << "  The table data number is not identical." << endl;
      }
    }
    else if( list_flg != no_list_data_mode )
    {
      if( list_flg == list_data_mode )
      {
        cout << "  The integer number of the list data is not identical." << endl;
        cout << "    Data position             : " << data_no+1 << " / " << data_no_max << endl;
      }
      else if( list_flg == list_data_no_mode )
      {
        cout << "  The list data number is not identical." << endl;
      }
    }
    else
    {
      cout << "  The integer number is not identical." << endl;
    }

    cout << "    Integer number (comp/ref) : " << int_val << " / " << int_val_ref << endl << endl;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataCompare::comp_real_data(Real real_val, Real real_val_ref)
{
  Real tolerance_val = tolerance_val_set;
  comp_real_data(real_val, real_val_ref, tolerance_val);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataCompare::comp_real8_data(Real8 real_val, Real8 real_val_ref)
{
  Real tolerance_val = tolerance_val_set;
  comp_real8_data(real_val, real_val_ref, tolerance_val);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

int AceDataCompare::check_dif_real_data(Real& real_val,      Real& real_val_ref,
                                        Real& tolerance_val, Real& dif_val)
{
  int zero_flg = 0;
  if( fabs(real_val) < min_val_set )
  {
    zero_flg = 1;
    real_val = 0.0;
  }

  int zero_flg_ref = 0;
  if( fabs(real_val_ref) < min_val_set )
  {
    zero_flg_ref = 1;
    real_val_ref = 0.0;
  }

  dif_val = fabs(real_val - real_val_ref);
  if( zero_flg_ref == 0 && zero_flg == 0 && fabs(real_val_ref) > min_relative_dif )
  {
    dif_val /= fabs(real_val_ref);
  }

  int  err_flg = 0;
  if( dif_val > tolerance_val )
  {
    err_flg = 1;
  }

  return err_flg;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataCompare::comp_real_data(Real real_val, Real real_val_ref, Real tolerance_val)
{
  Real dif_val = 0.0;
  if( check_dif_real_data(real_val, real_val_ref, tolerance_val, dif_val) > 0 )
  {
    cout.width(width_int);
    cout.precision(width_real);
    cout.setf(ios::scientific);
    cout.setf(ios::showpoint);
    cout.setf(ios::right);

    output_information_data();
    if( tab_flg != no_table_data_mode )
    {
      cout << "  The difference of the table data is larger than " << tolerance_val << "." << endl;
      cout << "    Data position          : " << data_no+1 << " / " << data_no_max << endl;
      cout << "    X value                : " << x_val << endl;
    }
    else if( list_flg != no_list_data_mode )
    {
      cout << "  The difference of the list data is larger than " << tolerance_val << "." << endl;
      cout << "    Data position          : " << data_no+1 << " / " << data_no_max << endl;
    }
    else
    {
      cout << "  The difference of the real number is larger than " << tolerance_val << "." << endl;
    }

    cout << "    Real number (comp/ref) : " << real_val << " / " << real_val_ref << endl;
    cout << "    Difference             : " << dif_val  << endl << endl;

    cout.unsetf(ios::scientific);
    cout.unsetf(ios::showpoint);
    cout.unsetf(ios::right);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

int AceDataCompare::check_dif_real8_data(Real8& real_val,      Real8& real_val_ref,
                                         Real8& tolerance_val, Real8& dif_val)
{
  int zero_flg = 0;
  if( fabs(real_val) < min_val_set )
  {
    zero_flg = 1;
    real_val = 0.0;
  }

  int zero_flg_ref = 0;
  if( fabs(real_val_ref) < min_val_set )
  {
    zero_flg_ref = 1;
    real_val_ref = 0.0;
  }

  dif_val = fabs(real_val - real_val_ref);
  if( zero_flg_ref == 0 && zero_flg == 0 && fabs(real_val_ref) > min_relative_dif )
  {
    dif_val /= fabs(real_val_ref);
  }

  int  err_flg = 0;
  if( dif_val > tolerance_val )
  {
    err_flg = 1;
  }

  return err_flg;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataCompare::comp_real8_data(Real8 real_val, Real8 real_val_ref, Real8 tolerance_val)
{
  Real dif_val = 0.0;
  if( check_dif_real8_data(real_val, real_val_ref, tolerance_val, dif_val) > 0 )
  {
    cout.width(width_int);
    cout.precision(width_real);
    cout.setf(ios::scientific);
    cout.setf(ios::showpoint);
    cout.setf(ios::right);

    output_information_data();
    if( tab_flg != no_table_data_mode )
    {
      cout << "  The difference of the table data is larger than " << tolerance_val << "." << endl;
      cout << "    Data position          : " << data_no+1 << " / " << data_no_max << endl;
      cout << "    X value                : " << x_val << endl;
    }
    else if( list_flg != no_list_data_mode )
    {
      cout << "  The difference of the list data is larger than " << tolerance_val << "." << endl;
      cout << "    Data position          : " << data_no+1 << " / " << data_no_max << endl;
    }
    else
    {
      cout << "  The difference of the real number is larger than " << tolerance_val << "." << endl;
    }

    cout << "    Real number (comp/ref) : " << real_val << " / " << real_val_ref << endl;
    cout << "    Difference             : " << dif_val  << endl << endl;

    cout.unsetf(ios::scientific);
    cout.unsetf(ios::showpoint);
    cout.unsetf(ios::right);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataCompare::comp_line_data(string str_data, string str_data_ref)
{
  if( strcmp( str_data.c_str(), str_data_ref.c_str() ) != 0 )
  {
    output_information_data();
    cout << "  The line data is not identical." << endl;
    cout << "    Line data (comp) : " << str_data     << endl;
    cout << "    Line data (ref)  : " << str_data_ref << endl << endl;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataCompare::comp_list_data(vector<Integer> list_vec, vector<Integer> list_vec_ref)
{
  int i_max_comp  = static_cast<int>(list_vec.size());
  int i_max       = static_cast<int>(list_vec_ref.size());
  list_flg = list_data_no_mode;

  if( comp_data_flg == comp_all_data_mode )
  {
    comp_int_data(i_max_comp, i_max);
  }

  if( i_max_comp != i_max )
  {
    output_information_data();
    ostringstream oss01, oss02;
    oss01 << i_max_comp;
    oss02 << i_max;

    vector<string> err_com;
    string str_data01 = "Data name               : " + data_name;
    err_com.push_back(str_data01);
    if( static_cast<int>(pos_data.size()) > 0 )
    {
      string str_data02 = "Position                : " + data_name;
      err_com.push_back(str_data02);
    }

    string str_data03 = "Element number for comp : " + oss01.str();
    string str_data04 = "Element number for ref  : " + oss02.str();
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back("");
    err_com.push_back("The element number is different.");
    err_com.push_back("Comparison of the list data process is skipped.");
    err_obj.output_caution(class_name, func_name, err_com);
  }
  else
  {
    list_flg    = list_data_mode;
    data_no_max = i_max;
    for(int i=0; i<i_max; i++)
    {
      data_no = i;
      comp_int_data(list_vec[i], list_vec_ref[i]);
    }
  }

  list_flg    = no_list_data_mode;
  data_no     = 0;
  data_no_max = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataCompare::comp_list_data_pointer(vector<Integer> list_vec, vector<Integer> list_vec_ref)
{
  int i_max     = static_cast<int>(list_vec.size());
  int i_max_ref = static_cast<int>(list_vec_ref.size());
  list_flg = list_data_no_mode;

  if( comp_data_flg == comp_all_data_mode )
  {
    comp_int_data(i_max, i_max_ref);
  }

  if( i_max == 0 )
  {
    return;
  }

  int dif_flg = 0;
  list_flg    = list_data_mode;
  data_no_max = i_max;
  for(int i=0; i<i_max; i++)
  {
    data_no = i;
    if( dif_flg == 0 )
    {
      comp_int_data(list_vec[i], list_vec_ref[i]);
    }
    else
    {
      comp_int_data(list_vec[i]-list_vec[i-1], list_vec_ref[i]-list_vec_ref[i-1]);
    }

    if( list_vec[i] != list_vec_ref[i] )
    {
      dif_flg = 1;
    }
  }

  list_flg    = no_list_data_mode;
  data_no     = 0;
  data_no_max = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataCompare::comp_list_data(vector<Real> list_vec, vector<Real> list_vec_ref)
{
  int i_max = static_cast<int>(list_vec_ref.size());

  vector<int> dif_chk_list;
  dif_chk_list.resize(i_max);
  for(int i=0; i<i_max ; i++)
  {
    dif_chk_list[i] = 1;
  }

  comp_list_data(list_vec, list_vec_ref, dif_chk_list);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataCompare::comp_list_data( vector<Real> list_vec, vector<Real> list_vec_ref,
                                     vector<int> dif_chk_list )
{
  int i_max_comp = static_cast<int>(list_vec.size());
  int i_max      = static_cast<int>(list_vec_ref.size());
  list_flg = list_data_no_mode;

  if( comp_data_flg == comp_all_data_mode )
  {
    comp_int_data(i_max_comp, i_max);
  }

  if( i_max_comp != i_max )
  {
    output_information_data();
    ostringstream oss01, oss02;
    oss01 << i_max_comp;
    oss02 << i_max;

    vector<string> err_com;
    string str_data01 = "Data name               : " + data_name;
    err_com.push_back(str_data01);
    if( static_cast<int>(pos_data.size()) > 0 )
    {
      string str_data02 = "Position                : " + data_name;
      err_com.push_back(str_data02);
    }

    string str_data03 = "Element number for comp : " + oss01.str();
    string str_data04 = "Element number for ref  : " + oss02.str();
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back("");
    err_com.push_back("The element number is different.");
    err_com.push_back("Comparison of the list data process is skipped.");
    err_obj.output_caution(class_name, func_name, err_com);
  }
  else
  {
    list_flg    = list_data_mode;
    data_no_max = i_max;
    for(int i=0; i<i_max; i++)
    {
      data_no = i;
        Real tolerance_val = tolerance_val_set;
      if( dif_chk_list[i] == 0 )
      {
        tolerance_val *= 2.0;
      }

      if( i > 0 )
      {
        if( list_vec_ref[i-1] > list_vec_ref[i] * 500.0 )
        {
          tolerance_val *= 100.0;
        }
        else if( list_vec_ref[i-1] > list_vec_ref[i] * 50.0 )
        {
          tolerance_val *= 50.0;
        }
      }

      comp_real_data(list_vec[i], list_vec_ref[i], tolerance_val);
    }
  }

  list_flg    = no_list_data_mode;
  data_no     = 0;
  data_no_max = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataCompare::comp_list_data_modify_small_value(vector<Real> list_vec, vector<Real> list_vec_ref)
{
  comp_list_data_modify_small_value(list_vec, list_vec_ref, min_ene_dif);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataCompare::comp_list_data_modify_small_value(vector<Real> list_vec, vector<Real> list_vec_ref,
                                                       Real min_val)
{
  modify_small_value(list_vec,     min_val);
  modify_small_value(list_vec_ref, min_val);

  comp_list_data(list_vec, list_vec_ref);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataCompare::modify_small_value(vector<Real>& list_vec, Real min_val)
{
  int i_max = static_cast<int>(list_vec.size());
  for(int i=0; i<i_max; i++)
  {
    if( fabs(list_vec[i]) < min_val )
    {
      list_vec[i] = 0.0;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataCompare::modify_initial_rise_region(vector<Real>& x_vec, vector<Real>& y_vec)
{
  Real dif_val = 1.0E-5;
  int  i_max   = static_cast<int>(x_vec.size());

  //int init_rise_flg = 0;
  for(int i=0; i<i_max-1; i++)
  {
    if( fabs(y_vec[i]) > min_value )
    {
      if( i == 0 || fabs(x_vec[i] - x_vec[i+1]) > fabs(dif_val * x_vec[i]) )
      {
        break;
      }

      //init_rise_flg = 1;
      if( y_vec[i+1] / y_vec[i] > 1.0 / dif_val )
      {
        y_vec[i] = 0.0;
      }

      break;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataCompare::comp_interpolation_data(vector<Integer> range_vec,     vector<Integer> int_vec,
                                             vector<Integer> range_vec_ref, vector<Integer> int_vec_ref)
{
  tab_flg = table_data_mode;

  int comment_flg = 0;
  if( comment_data.empty() != 0 )
  {
    comment_flg = 1;
  }

  if( comp_data_flg == comp_all_data_mode )
  {
    if( comment_flg > 0 )
    {
      comment_data = "comp_interpolation_data @ range_vec";
    }
    comp_list_data(range_vec, range_vec_ref);

    if( comment_flg > 0 )
    {
      comment_data = "comp_interpolation_data @ int_vec";
    }
    comp_list_data(int_vec, int_vec_ref);
  }

  if( comment_flg > 0 )
  {
    comment_data.clear();
  }
  tab_flg = no_table_data_mode;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataCompare::comp_table_data(vector<Real> x_vec,     vector<Real> y_vec,
                                     vector<Real> x_vec_ref, vector<Real> y_vec_ref)
{
  vector<Integer> range_vec, int_vec, range_vec_ref, int_vec_ref;
  range_vec.resize(1);
  int_vec.resize(1);
  range_vec_ref.resize(1);
  int_vec_ref.resize(1);

  range_vec[0] = static_cast<Integer>(x_vec.size());
  int_vec[0]   = int_lin_lin;

  range_vec_ref[0] = static_cast<Integer>(x_vec_ref.size());
  int_vec_ref[0]   = int_lin_lin;

  comp_table_data(range_vec, int_vec, x_vec, y_vec, range_vec_ref, int_vec_ref, x_vec_ref, y_vec_ref);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataCompare::comp_table_data(vector<Real> x_vec,     vector<Real> y_vec,
                                     vector<Real> y_vec_integ,
                                     vector<Real> x_vec_ref, vector<Real> y_vec_ref,
                                     vector<Real> y_vec_integ_ref,
                                     Real         initial_val)
{
  comp_table_data(int_lin_lin, x_vec,     y_vec,     y_vec_integ,
                  int_lin_lin, x_vec_ref, y_vec_ref, y_vec_integ_ref, initial_val);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataCompare::comp_table_data(vector<Real> x_vec,     vector<Real> y_vec,
                                     vector<Real> y_vec_integ,
                                     vector<Real> x_vec_ref, vector<Real> y_vec_ref,
                                     vector<Real> y_vec_integ_ref)
{
  comp_table_data(int_lin_lin, x_vec,     y_vec,     y_vec_integ,
                  int_lin_lin, x_vec_ref, y_vec_ref, y_vec_integ_ref);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataCompare::comp_table_data_no_integral
                      (vector<Real> x_vec,     vector<Real> y_vec,     vector<Real> y_vec_integ,
                       vector<Real> x_vec_ref, vector<Real> y_vec_ref, vector<Real> y_vec_integ_ref)
{
  comp_table_data_no_integral(int_lin_lin, x_vec,     y_vec,     y_vec_integ,
                              int_lin_lin, x_vec_ref, y_vec_ref, y_vec_integ_ref);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataCompare::comp_table_data_without_small_value
                      (vector<Real> x_vec,     vector<Real> y_vec,     vector<Real> y_vec_integ,
                       vector<Real> x_vec_ref, vector<Real> y_vec_ref, vector<Real> y_vec_integ_ref)
{
  comp_table_data_without_small_value(int_lin_lin, x_vec,     y_vec,     y_vec_integ,
                                      int_lin_lin, x_vec_ref, y_vec_ref, y_vec_integ_ref);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataCompare::comp_table_data(vector<Integer> range_vec,     vector<Integer> int_vec,
                                     vector<Real>    x_vec,         vector<Real>    y_vec,
                                     vector<Integer> range_vec_ref, vector<Integer> int_vec_ref,
                                     vector<Real>    x_vec_ref,     vector<Real>    y_vec_ref)
{
  int i_max_comp = static_cast<int>(x_vec.size());
  int i_max      = static_cast<int>(x_vec_ref.size());
  if( i_max != i_max_comp && (i_max_comp == 0 || i_max == 0) )
  {
    output_information_data();
    ostringstream oss01, oss02;
    oss01 << i_max_comp;
    oss02 << i_max;

    vector<string> err_com;
    string str_data01 = "Data name               : " + data_name;
    err_com.push_back(str_data01);
    if( static_cast<int>(pos_data.size()) > 0 )
    {
      string str_data02 = "Position                : " + data_name;
      err_com.push_back(str_data02);
    }

    string str_data03 = "Element number for comp : " + oss01.str();
    string str_data04 = "Element number for ref  : " + oss02.str();
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back("");
    err_com.push_back("The element number for comp or that for ref is 0.");
    err_com.push_back("Comparison of the table data process is skipped.");
    err_obj.output_caution(class_name, func_name, err_com);

    return;
  }

  x_dif_chk.clear();
  x_dif_chk.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    x_dif_chk[i] = 0;
  
    Real x_ref = x_vec_ref[i];
    Real x_dif = fabs(0.001 * x_ref);
    if( x_dif < min_ene_dif )
    {
      x_dif = min_ene_dif;
    }

    int j_max = static_cast<int>(x_vec.size());
    for(int j=0; j<j_max; j++)
    {
      if( fabs(x_vec[j] - x_ref) < x_dif )
      {
        x_dif_chk[i] = 1;
        break;
      }
    }
  }

  vector<Integer> range_vec_ori = range_vec;
  vector<Integer> int_vec_ori   = int_vec;
  vector<Real>    x_vec_ori     = x_vec;
  vector<Real>    y_vec_ori     = y_vec;

  Integer int_chk = 0;
  for(int i=0; i<static_cast<int>(int_vec.size()); i++)
  {
    if( int_vec[i] == int_const )
    {
      int_chk = 1;
      break;
    }
  }

  if( int_chk == 0 )
  {
    ta_obj.modify_x_grid(x_vec_ref, range_vec, int_vec, x_vec, y_vec);
    comp_interpolation_data(range_vec, int_vec, range_vec_ref, int_vec_ref);
  }
  else
  {
    vector<Integer> int_vec_comp   = int_vec;
    vector<Integer> range_vec_comp = range_vec;
    vector<Real>    x_vec_comp     = x_vec;
    vector<Real>    y_vec_comp     = y_vec;
    ta_obj.modify_x_grid(x_vec_ref, range_vec_comp, int_vec_comp, x_vec_comp, y_vec_comp);
    comp_interpolation_data(range_vec_comp, int_vec_comp, range_vec_ref, int_vec_ref);

    for(int i=0; i<static_cast<int>(int_vec.size()); i++)
    {
      if( int_vec[i] == int_const )
      {
        int_vec[i] = int_lin_lin;
      }
    }
    ta_obj.modify_x_grid(x_vec_ref, range_vec, int_vec, x_vec, y_vec);
  }

  //Check order
  Integer order_check = ta_obj.check_order(x_vec); //+1 : ascending order
                                                   //-1 : descending order

  tab_flg = table_data_mode;
  int comment_flg = 0;
  if( comment_data.empty() != 0 )
  {
    comment_flg = 1;
  }

  if( comment_flg > 0 )
  {
    comment_data = "comp_table_data @ y_vec";
  }

  data_no_max = i_max;
  for(int i=0; i<i_max; i++)
  {
    Real tolerance_val = tolerance_val_set;
    if( x_dif_chk[i] == 0 )
    {
      tolerance_val *= 2.0;
    }

    if( order_check > 0 && i > 0 )
    {
      if( fabs(x_vec_ref[i] - x_vec_ref[i-1]) < fabs(x_vec_ref[i]*min_ene_dif) )
      {
        continue;
      }

      if( y_vec_ref[i-1] > y_vec_ref[i]   * 500.0 || y_vec_ref[i-1] < y_vec_ref[i]   / 500.0 ||
          y_vec_ref[i]   > y_vec_ref[i+1] * 500.0 || y_vec_ref[i]   < y_vec_ref[i+1] / 500.0 )
      {
        tolerance_val *= 100.0;
      }
      else if( y_vec_ref[i-1] > y_vec_ref[i]   * 50.0 || y_vec_ref[i-1] < y_vec_ref[i]   / 50.0 ||
               y_vec_ref[i]   > y_vec_ref[i+1] * 50.0 || y_vec_ref[i]   < y_vec_ref[i+1] / 50.0 )
      {
        tolerance_val *= 50.0;
      }
      else if( y_vec_ref[i-1] > y_vec_ref[i]   * 20.0 || y_vec_ref[i-1] < y_vec_ref[i]   / 20.0 ||
               y_vec_ref[i]   > y_vec_ref[i+1] * 20.0 || y_vec_ref[i]   < y_vec_ref[i+1] / 20.0 )
      {
        tolerance_val *= 20.0;
      }
    }
    else if( order_check < 0 && i < i_max - 1 )
    {
      if( fabs(x_vec_ref[i] - x_vec_ref[i+1]) < fabs(x_vec_ref[i]*min_ene_dif) )
      {
        continue;
      }

      if( y_vec_ref[i+1] > y_vec_ref[i]   * 500.0 || y_vec_ref[i+1] < y_vec_ref[i]   / 500.0 ||
          y_vec_ref[i]   > y_vec_ref[i-1] * 500.0 || y_vec_ref[i]   < y_vec_ref[i-1] / 500.0 )
      {
        tolerance_val *= 100.0;
      }
      else if( y_vec_ref[i+1] > y_vec_ref[i]   * 50.0 || y_vec_ref[i+1] < y_vec_ref[i]   / 50.0 ||
               y_vec_ref[i]   > y_vec_ref[i-1] * 50.0 || y_vec_ref[i]   < y_vec_ref[i-1] / 50.0 )
      {
        tolerance_val *= 50.0;
      }
      else if( y_vec_ref[i+1] > y_vec_ref[i]   * 20.0 || y_vec_ref[i+1] < y_vec_ref[i]   / 20.0 ||
               y_vec_ref[i]   > y_vec_ref[i-1] * 20.0 || y_vec_ref[i]   < y_vec_ref[i-1] / 20.0 )
      {
        tolerance_val *= 20.0;
      }
    }

    int skip_flg = 0;
    if( fabs(y_vec_ref[i]) < min_value || fabs(y_vec[i]) < min_value )
    {
      if( i == 0 )
      {
        skip_flg = 1;
      }
      else
      {
        if( fabs(y_vec_ref[i-1]) < min_value || fabs(y_vec[i-1]) < min_value )
        {
          skip_flg = 1;
        }

        if( i < i_max-1 )
        {
          if( fabs(y_vec_ref[i+1]) < min_value || fabs(y_vec[i+1]) < min_value )
          {
            skip_flg = 1;
          }
        }
      }
    }

    if( skip_flg == 0 )
    {
      data_no = i;
      x_val   = x_vec_ref[i];

      Real dif_val = 0.0;
      if( check_dif_real_data(y_vec[i], y_vec_ref[i], tolerance_val, dif_val) > 0 )
      {
        Real x_m, x_p, y_m, y_p;
        x_m     = digit_obj.get_adjusted_value(x_vec_ref[i], sig_fig, -1.0);
        x_p     = digit_obj.get_adjusted_value(x_vec_ref[i], sig_fig, +1.0);
        y_m     = 0.0;
        y_p     = 0.0;

        if( i > 0 )
        {
          x_m = 0.5 * (x_vec_ref[i] + x_vec_ref[i-1]);
        }

        if( i < i_max - 1 )
        {
          x_p = 0.5 * (x_vec_ref[i] + x_vec_ref[i+1]);
        }

        ti_obj.interpolation_tab1(x_m, y_m, range_vec_ori, int_vec_ori, x_vec_ori, y_vec_ori);
        ti_obj.interpolation_tab1(x_p, y_p, range_vec_ori, int_vec_ori, x_vec_ori, y_vec_ori);

        if( check_dif_real_data(y_m, y_vec_ref[i], tolerance_val, dif_val) > 0 &&
            check_dif_real_data(y_p, y_vec_ref[i], tolerance_val, dif_val) > 0 )
        {
          comp_real_data(y_vec[i], y_vec_ref[i], tolerance_val);
        }
      }
    }
  }

  if( comment_flg > 0 )
  {
    comment_data.clear();
  }
  tab_flg = no_table_data_mode;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataCompare::comp_table_data(vector<Integer> range_vec,     vector<Integer> int_vec,
                                     vector<Real>    x_vec,         vector<Real>    y_vec,
                                     vector<Real>    y_vec_integ,
                                     vector<Integer> range_vec_ref, vector<Integer> int_vec_ref,
                                     vector<Real>    x_vec_ref,     vector<Real>    y_vec_ref,
                                     vector<Real>    y_vec_integ_ref,
                                     Real            initial_val)
{
  int i_max_comp = static_cast<int>(x_vec.size());
  int i_max      = static_cast<int>(x_vec_ref.size());
  if( i_max != i_max_comp && (i_max_comp == 0 || i_max == 0) )
  {
    output_information_data();
    ostringstream oss01, oss02;
    oss01 << i_max_comp;
    oss02 << i_max;

    vector<string> err_com;
    string str_data01 = "Data name               : " + data_name;
    err_com.push_back(str_data01);
    if( static_cast<int>(pos_data.size()) > 0 )
    {
      string str_data02 = "Position                : " + data_name;
      err_com.push_back(str_data02);
    }

    string str_data03 = "Element number for comp : " + oss01.str();
    string str_data04 = "Element number for ref  : " + oss02.str();
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back("");
    err_com.push_back("The element number for comp or that for ref is 0.");
    err_com.push_back("Comparison of the table data with integral value process is skipped.");
    err_obj.output_caution(class_name, func_name, err_com);

    return;
  }

  vector<Integer> range_vec_ori = int_vec;
  vector<Integer> int_vec_ori   = int_vec;
  vector<Real>    x_vec_ori     = x_vec;
  vector<Real>    y_vec_ori     = y_vec;

  ta_obj.modify_x_grid(x_vec_ref, range_vec, int_vec, x_vec, y_vec);

  string class_name = "AceDataCompare";
  string func_name  = "comp_table_data";

  if( fabs(initial_val) > min_value )
  {
    vector<Real> y_vec_mod;
    y_vec_integ.resize(i_max);
    for(int i=0; i<i_max; i++)
    {
      if( i == 0 )
      {
        y_vec_integ[i] = initial_val;
      }
      else
      {
        y_vec_integ[i] = y_vec_integ[i-1]
                       + integ_obj.integrate_data(x_vec[i-1], y_vec[i-1], x_vec[i], y_vec[i], int_vec[0]);
      }
    }
  }
  else
  {
    integ_obj.integrate_for_ace_data_no_normalize
      (class_name, func_name, x_vec, y_vec, y_vec_integ, int_vec[0]);
  }

  range_vec = range_vec_ori;
  int_vec   = int_vec_ori;
  x_vec     = x_vec_ori;
  y_vec     = y_vec_ori;
  comp_table_data(range_vec,     int_vec,     x_vec,     y_vec,
                  range_vec_ref, int_vec_ref, x_vec_ref, y_vec_ref);

  tab_flg = table_data_mode;

  int comment_flg = 0;
  if( comment_data.empty() != 0 )
  {
    comment_flg = 1;
    comment_data = "comp_table_data @ y_vec_integ";
  }

  for(int i=0; i<i_max; i++)
  {
    Real tolerance_val = tolerance_val_set;
    if( x_dif_chk[i] == 0 )
    {
      tolerance_val *= 2.0;
    }

    int  dif_chk = 0;
    Real dif_val = tolerance_val;
    if( fabs(y_vec_integ_ref[i]) > min_relative_dif )
    {
      dif_val *= fabs(y_vec_integ_ref[i]);
    }
    if( fabs(y_vec_integ[i] - y_vec_integ_ref[i]) < dif_val )
    {
      dif_chk++;
    }

    Real x_dif = min_ene_dif;
    if( fabs(x_vec_ref[i]) > min_relative_dif )
    {
      x_dif *= fabs(x_vec_ref[i]);
    }

    //Skip overlap integrate value comparison
    if( i > 0 )
    {
      if( fabs(x_vec_ref[i-1] - x_vec_ref[i]) < x_dif )
      {
        dif_val = tolerance_val;
        if( fabs(y_vec_integ_ref[i-1]) > min_relative_dif )
        {
          dif_val *= fabs(y_vec_integ_ref[i-1]);
        }
        if( fabs(y_vec_integ[i-1] - y_vec_integ_ref[i-1]) < dif_val )
        {
          dif_chk++;
        }

        if( dif_chk > 0 )
        {
          continue;
        }
      }
    }

    //Skip overlap integrate value comparison
    if( i < i_max - 1 )
    {
      if( fabs(x_vec_ref[i+1] - x_vec_ref[i]) < x_dif )
      {
        dif_val = tolerance_val;
        if( fabs(y_vec_integ_ref[i+1]) > min_relative_dif )
        {
          dif_val *= fabs(y_vec_integ_ref[i+1]);
        }
        if( fabs(y_vec_integ[i+1] - y_vec_integ_ref[i+1]) < dif_val )
        {
          dif_chk++;
        }

        if( dif_chk > 0 )
        {
          continue;
        }
      }
    }

    data_no = i;
    x_val   = x_vec_ref[i];
    comp_real_data(y_vec_integ[i], y_vec_integ_ref[i], tolerance_val);
  } 

  if( comment_flg > 0 )
  {
    comment_data.clear();
  }
  tab_flg = no_table_data_mode;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataCompare::comp_table_data(vector<Integer> range_vec,     vector<Integer> int_vec,
                                     vector<Real>    x_vec,         vector<Real>    y_vec,
                                     vector<Real>    y_vec_integ,
                                     vector<Integer> range_vec_ref, vector<Integer> int_vec_ref,
                                     vector<Real>    x_vec_ref,     vector<Real>    y_vec_ref,
                                     vector<Real>    y_vec_integ_ref)
{
  Real initial_val = 0.0;
  comp_table_data(range_vec,     int_vec,     x_vec,     y_vec,     y_vec_integ,
                  range_vec_ref, int_vec_ref, x_vec_ref, y_vec_ref, y_vec_integ_ref, initial_val);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataCompare::comp_table_data_no_integral
                      (vector<Integer> range_vec, vector<Integer> int_vec,
                       vector<Real> x_vec, vector<Real> y_vec, vector<Real> y_vec_integ,
                       vector<Integer> range_vec_ref, vector<Integer> int_vec_ref,
                       vector<Real> x_vec_ref, vector<Real> y_vec_ref, vector<Real> y_vec_integ_ref)
{
  vector<Integer> range_vec_ori = int_vec;
  vector<Integer> int_vec_ori   = int_vec;
  vector<Real>    x_vec_ori     = x_vec;
  vector<Real>    y_vec_ori     = y_vec;

  ta_obj.modify_x_grid(x_vec_ref, range_vec, int_vec, x_vec, y_vec);

  class_name = "AceDataCompare";
  func_name  = "comp_table_data";

  int i_max = static_cast<int>(y_vec.size());
  y_vec_integ.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    if( i == 0 )
    {
      y_vec_integ[i] = y_vec[i];
    }
    else
    {
      y_vec_integ[i] = y_vec_integ[i-1] + y_vec[i];
    }
  }

  range_vec = range_vec_ori;
  int_vec   = int_vec_ori;
  x_vec     = x_vec_ori;
  y_vec     = y_vec_ori;
  comp_table_data(range_vec,     int_vec,     x_vec,     y_vec,
                  range_vec_ref, int_vec_ref, x_vec_ref, y_vec_ref);

  tab_flg = table_data_mode;

  int comment_flg = 0;
  if( comment_data.empty() != 0 )
  {
    comment_flg = 1;
    comment_data = "comp_table_data @ y_vec_integ";
  }

  comp_list_data(y_vec_integ, y_vec_integ_ref, x_dif_chk);

  if( comment_flg > 0 )
  {
    comment_data.clear();
  }
  tab_flg = no_table_data_mode;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataCompare::comp_table_data_without_small_value
                      (vector<Integer> range_vec, vector<Integer> int_vec,
                       vector<Real> x_vec, vector<Real> y_vec, vector<Real> y_vec_integ,
                       vector<Integer> range_vec_ref, vector<Integer> int_vec_ref,
                       vector<Real> x_vec_ref, vector<Real> y_vec_ref, vector<Real> y_vec_integ_ref)
{
  int i_max = static_cast<int>(x_vec_ref.size());

  Real x_min = 0.0;
  for(int i=0; i<i_max; i++)
  {
    if( fabs(x_vec_ref[i]) > min_value )
    {
      x_min = x_vec_ref[i] * 0.9999;
      break;
    }
  }

  vector<Real> x_vec_new, y_vec_new;
  Integer skip_no = 0;
  i_max = static_cast<int>(x_vec.size());
  for(int i=0; i<i_max; i++)
  {
    if( fabs(x_vec[i]) < min_value )
    {
      x_vec_new.push_back(x_vec_ref[0]);
      y_vec_new.push_back(y_vec_ref[0]);
    }
    else if( x_vec[i] > x_min )
    {
      x_vec_new.push_back(x_vec[i]);
      y_vec_new.push_back(y_vec[i]);
    }
    else
    {
      skip_no++;
    }
  }
  x_vec = x_vec_new;
  y_vec = y_vec_new;

  i_max = static_cast<int>(range_vec.size());
  vector<Integer> range_vec_new, int_vec_new;
  for(int i=0; i<i_max; i++)
  {
    range_vec[i] -= skip_no;
    if( range_vec[i] >= 0 )
    {
      range_vec_new.push_back(range_vec[i]);
      int_vec_new.push_back(int_vec[i]);
    }
  }
  range_vec = range_vec_new;
  int_vec   = int_vec_new;

  comp_table_data(range_vec,     int_vec,     x_vec,     y_vec,     y_vec_integ,
                  range_vec_ref, int_vec_ref, x_vec_ref, y_vec_ref, y_vec_integ_ref);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataCompare::comp_table_data(Integer int_data,     vector<Real> x_vec,     vector<Real> y_vec,
                                     Integer int_data_ref, vector<Real> x_vec_ref, vector<Real> y_vec_ref)
{
  vector<Integer> range_vec, int_vec, range_vec_ref, int_vec_ref;
  range_vec.resize(1);
  int_vec.resize(1);
  range_vec_ref.resize(1);
  int_vec_ref.resize(1);

  range_vec[0]     = static_cast<Integer>(x_vec.size());
  range_vec_ref[0] = static_cast<Integer>(x_vec_ref.size());
  int_vec[0]       = int_data;
  int_vec_ref[0]   = int_data_ref;

  comp_table_data(range_vec,     int_vec,     x_vec,     y_vec,
                  range_vec_ref, int_vec_ref, x_vec_ref, y_vec_ref);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataCompare::comp_table_data(Integer int_data,     vector<Real> x_vec,     vector<Real> y_vec,
                                     vector<Real> y_vec_integ,
                                     Integer int_data_ref, vector<Real> x_vec_ref, vector<Real> y_vec_ref,
                                     vector<Real> y_vec_integ_ref,
                                     Real initial_val)
{
  vector<Integer> range_vec, int_vec, range_vec_ref, int_vec_ref;
  range_vec.resize(1);
  int_vec.resize(1);
  range_vec_ref.resize(1);
  int_vec_ref.resize(1);

  range_vec[0]     = static_cast<Integer>(x_vec.size());
  range_vec_ref[0] = static_cast<Integer>(x_vec_ref.size());
  int_vec[0]       = int_data;
  int_vec_ref[0]   = int_data_ref;

  comp_table_data(range_vec,     int_vec,     x_vec,     y_vec,     y_vec_integ,
                  range_vec_ref, int_vec_ref, x_vec_ref, y_vec_ref, y_vec_integ_ref, initial_val);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataCompare::comp_table_data(Integer int_data,     vector<Real> x_vec,     vector<Real> y_vec,
                                     vector<Real> y_vec_integ,
                                     Integer int_data_ref, vector<Real> x_vec_ref, vector<Real> y_vec_ref,
                                     vector<Real> y_vec_integ_ref)
{
  Real initial_val = 0.0;
  comp_table_data(int_data,     x_vec,     y_vec,     y_vec_integ,
                  int_data_ref, x_vec_ref, y_vec_ref, y_vec_integ_ref, initial_val);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataCompare::comp_table_data_no_integral
                     (Integer int_data,     vector<Real> x_vec,     vector<Real> y_vec,
                      vector<Real> y_vec_integ,
                      Integer int_data_ref, vector<Real> x_vec_ref, vector<Real> y_vec_ref,
                      vector<Real> y_vec_integ_ref)
{
  vector<Integer> range_vec, int_vec, range_vec_ref, int_vec_ref;
  range_vec.resize(1);
  int_vec.resize(1);
  range_vec_ref.resize(1);
  int_vec_ref.resize(1);

  range_vec[0]     = static_cast<Integer>(x_vec.size());
  range_vec_ref[0] = static_cast<Integer>(x_vec_ref.size());
  int_vec[0]       = int_data;
  int_vec_ref[0]   = int_data_ref;

  comp_table_data_no_integral(range_vec,     int_vec,     x_vec,     y_vec,     y_vec_integ,
                              range_vec_ref, int_vec_ref, x_vec_ref, y_vec_ref, y_vec_integ_ref);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataCompare::comp_table_data_without_small_value
                     (Integer int_data,     vector<Real> x_vec,     vector<Real> y_vec,
                      vector<Real> y_vec_integ,
                      Integer int_data_ref, vector<Real> x_vec_ref, vector<Real> y_vec_ref,
                      vector<Real> y_vec_integ_ref)
{
  vector<Integer> range_vec, int_vec, range_vec_ref, int_vec_ref;
  range_vec.resize(1);
  int_vec.resize(1);
  range_vec_ref.resize(1);
  int_vec_ref.resize(1);

  range_vec[0]     = static_cast<Integer>(x_vec.size());
  range_vec_ref[0] = static_cast<Integer>(x_vec_ref.size());
  int_vec[0]       = int_data;
  int_vec_ref[0]   = int_data_ref;

  comp_table_data_without_small_value(range_vec,     int_vec,     x_vec,     y_vec,     y_vec_integ,
                                      range_vec_ref, int_vec_ref, x_vec_ref, y_vec_ref, y_vec_integ_ref);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataCompare::comp_title_data(Real aw0, Real tz,
                                     string discriptive_data, vector<string> title_data,
                                     Real aw0_ref, Real tz_ref,
                                     string discriptive_data_ref, vector<string> title_data_ref)
{
  int comment_flg = 0;
  if( comment_data.empty() != 0 )
  {
    comment_flg = 1;
  }

  if( comment_flg > 0 )
  {
    comment_data = "comp_title_data @ aw0";
  }
  comp_real_data(aw0, aw0_ref);

  if( comment_flg > 0 )
  {
    comment_data = "comp_title_data @ tz";
  }
  comp_real_data(tz, tz_ref);

  if( comment_flg > 0 )
  {
    comment_data = "comp_title_data @ discriptive_data";
  }
  comp_line_data(discriptive_data, discriptive_data_ref);

  if( comment_flg > 0 )
  {
    comment_data = "comp_title_data @ title_data";
  }
  int i_max     = static_cast<int>(title_data.size());
  int i_max_ref = static_cast<int>(title_data_ref.size());
  list_flg = list_data_no_mode;
  comp_int_data(i_max, i_max_ref);
  list_flg = no_list_data_mode;
  for(int i=0; i<i_max; i++)
  {
    if( i != i_max - 2 )
    {
      comp_line_data(title_data[i], title_data_ref[i]);
    }
    else //processing date
    {
      if( comp_data_flg == comp_all_data_mode )
      {
        comp_line_data(title_data[i], title_data_ref[i]);
      }
      else //if( comp_data_flg == no_comp_data_number_mode )
      {
        continue;
      }
    }
  }

  if( comment_flg > 0 )
  {
    comment_data.clear();
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataCompare::comp_mat_data(vector<Integer> zi_vec,     vector<Real> awr_vec,
                                   vector<Integer> zi_vec_ref, vector<Real> awr_vec_ref)
{
  int comment_flg = 0;
  if( comment_data.empty() != 0 )
  {
    comment_flg = 1;
  }

  if( comment_flg > 0 )
  {
    comment_data = "comp_mat_data @ zi_vec";
  }
  comp_list_data(zi_vec, zi_vec_ref);

  if( comment_flg > 0 )
  {
    comment_data = "comp_mat_data @ awr_vec";
  }
  comp_list_data(awr_vec, awr_vec_ref);

  if( comment_flg > 0 )
  {
    comment_data.clear();
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataCompare::comp_pointer_data(vector<int> pointer_data, vector<int> pointer_data_ref)
{
  int comment_flg = 0;
  if( comment_data.empty() != 0 )
  {
    comment_flg = 1;
  }

  if( comment_flg > 0 )
  {
    comment_data = "comp_pointer_data";
  }
  comp_list_data_pointer(pointer_data, pointer_data_ref);

  if( comment_flg > 0 )
  {
    comment_data.clear();
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Integer AceDataCompare::check_list_data_order(vector<Real> list_data, Real& x_p, Real& x_m)
{
  Integer order_flg = 0;

  int i_max = static_cast<int>(list_data.size());
  if( i_max <= 1 )
  {
    return order_flg;
  }

  x_p = 0.0;
  x_m = 0.0;
  for(int i=1; i<i_max; i++)
  {
    if( fabs(list_data[i] - list_data[i-1]) < min_ene_dif )
    {
      continue;
    }

    if( list_data[i] > list_data[i-1] )
    {
      if( order_flg != 1 && order_flg != 0 )
      {
        x_m = list_data[i-1];
        x_p = list_data[i];
        order_flg *= -1;
        break;
      }
      order_flg = 1; //ascending order
    }
    else if( list_data[i] < list_data[i-1] )
    {
      if( order_flg != 2 && order_flg != 0 )
      {
        x_m = list_data[i-1];
        x_p = list_data[i];
        order_flg *= -1;
        break;
      }
      order_flg = 2; //descending order
    }
  }

  return order_flg;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////

Integer AceDataCompare::check_list_data_order(vector<Real> list_data)
{
  Real    x_p       = 0.0;
  Real    x_m       = 0.0;
  Integer order_flg = check_list_data_order(list_data, x_p, x_m);

  return order_flg;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataCompare::set_information_data(string class_data, string func_data)
{
  class_name = class_data;
  func_name  = func_data;

  data_name.clear();
  pos_data.clear();
  comment_data.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataCompare::set_comp_data_information(string data_name_str, string position_data)
{
  data_name = data_name_str;
  pos_data  = position_data;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataCompare::set_comp_data_information(string data_name_str)
{
  data_name = data_name_str;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataCompare::set_comp_data_position(string position_data)
{
  pos_data = position_data;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataCompare::set_comp_data_position(int pos_i)
{
  pos_data.clear();
  ostringstream oss01;
  oss01 << pos_i;

  pos_data = "(" + oss01.str() + ")";
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataCompare::set_comp_data_position(int pos_i, int pos_j)
{
  pos_data.clear();
  ostringstream oss01, oss02;
  oss01 << pos_i;
  oss02 << pos_j;

  pos_data = "(" + oss01.str() + ", " + oss02.str() + ")";
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataCompare::set_comp_data_position(int pos_i, int pos_j, int pos_k)
{
  pos_data.clear();
  ostringstream oss01, oss02, oss03;
  oss01 << pos_i;
  oss02 << pos_j;
  oss03 << pos_k;

  pos_data = "(" + oss01.str() + ", " + oss02.str() + ", " + oss03.str() + ")";
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataCompare::set_comp_data_position(int pos_i, int pos_j, int pos_k, int pos_l)
{
  pos_data.clear();
  ostringstream oss01, oss02, oss03, oss04;
  oss01 << pos_i;
  oss02 << pos_j;
  oss03 << pos_k;
  oss04 << pos_l;

  pos_data = "(" + oss01.str() + ", " + oss02.str() + ", " + oss03.str() + ", " + oss04.str() + ")";
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataCompare::set_comp_data_position(int pos_i, int pos_j, int pos_k, int pos_l, int pos_m)
{
  pos_data.clear();
  ostringstream oss01, oss02, oss03, oss04, oss05;
  oss01 << pos_i;
  oss02 << pos_j;
  oss03 << pos_k;
  oss04 << pos_l;
  oss05 << pos_m;

  pos_data = "(" + oss01.str() + ", " + oss02.str() + ", " + oss03.str() + ", "
                 + oss04.str() + ", " + oss05.str() + ")";
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataCompare::clear_comp_data_position()
{
  pos_data.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataCompare::set_tolerance_val_def()
{
  tolerance_val_set = tolerance_val_def;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataCompare::set_tolerance_val(Real tolerance_val)
{
  cout << "Tolerance value is changed from " << tolerance_val_set << " to " << tolerance_val << endl;
  tolerance_val_set = tolerance_val;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Real AceDataCompare::get_tolerance_val()
{
  return tolerance_val_set;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataCompare::set_min_val_def()
{
  min_val_set = min_val_def;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataCompare::set_min_val(Real min_val)
{
  min_val_set = min_val;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Real AceDataCompare::get_min_val()
{
  return min_val_set;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataCompare::set_comp_data_flg(int comp_flg)
{
  if( comp_flg != comp_all_data_mode && comp_flg != no_comp_data_number_mode )
  {
    class_name = "AceDataCompare";
    func_name  = "set_comp_data_flg(int comp_flg)";

    ostringstream oss01;
    oss01 << comp_flg;
    string str_data01 = "comp_flg : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("The available comp_flg is only 0 (comp_all_data_mode)");
    err_com.push_back(" or 1 (no_comp_data_number_mode).");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  comp_data_flg = comp_flg;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

int  AceDataCompare::get_comp_data_flg()
{
  return comp_data_flg;
}

