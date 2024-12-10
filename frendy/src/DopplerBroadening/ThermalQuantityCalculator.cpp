#include "DopplerBroadening/ThermalQuantityCalculator.hpp"

using namespace frendy;

//Initialize static const value
const Real8 ThermalQuantityCalculator::ene_reso = 0.5000;

//constructor
ThermalQuantityCalculator::ThermalQuantityCalculator(void)
{
  clear();
}

//destructor
ThermalQuantityCalculator::~ThermalQuantityCalculator(void)
{
  clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalQuantityCalculator::calc_thermal_quantity()
{
  if( calc_flg > 0 )
  {
    return;
  }
  calc_flg = 1;

  err_flg  = 0;

  if( check_temp(temp_ori) > 0 || check_nucl_data_obj(nucl_data_obj) > 0 )
  {
    return;
  }
  
  vector<Integer> nbt_fis, int_fis, nbt_cap, int_cap;
  vector<Real>    ene_fis, sig_fis, ene_cap, sig_cap;
  
  int i_max = static_cast<int>(xs_data_obj.size());
  fissile_flg = 1;
  for(int i=1; i<i_max; i++)
  {
    //mt =  18 : (z,f)     - Total of fission cross section
    //mt = 102 : (z,gamma) - Total of radiation cross section
    if( xs_data_obj[i].get_reaction_type() == 18 )
    {
      nbt_fis = xs_data_obj[i].get_xs_range_data();
      int_fis = xs_data_obj[i].get_xs_int_data();
      ene_fis = xs_data_obj[i].get_xs_ene_data();
      sig_fis = xs_data_obj[i].get_xs_data();
      if( static_cast<int>(ene_fis.size()) > 0 )
      {
        fissile_flg = 0;
      }
    }
    else if( xs_data_obj[i].get_reaction_type() == 102 )
    {
      nbt_cap = xs_data_obj[i].get_xs_range_data();
      int_cap = xs_data_obj[i].get_xs_int_data();
      ene_cap = xs_data_obj[i].get_xs_ene_data();
      sig_cap = xs_data_obj[i].get_xs_data();
    }
  }

  if( static_cast<int>(ene_cap.size()) == 0 )
  {
    string class_name = "ThermalQuantityCalculator";
    string func_name  = "calc_thermal_quantity()";
    ostringstream oss01, oss02, oss03;
    vector<string> err_com;
    err_com.push_back("The array size of radiation energy grid is zero.");
    err_com.push_back("The calculation of the thermal quantities calculation is skipped.");
    err_obj.output_caution(class_name, func_name, err_com);

    return;
  }
  
  check_xs_data(nbt_fis, int_fis, ene_fis, nbt_cap, int_cap, ene_cap);
  if( err_flg < 0 )
  {
    clear_thermal_quantity();
    return;
  }
  nbt_fis.clear();
  int_fis.clear();
  nbt_cap.clear();
  int_cap.clear();

  int ene_fis_sta, ene_fis_end;
  search_fission_energy_grid(ene_fis, ene_cap, ene_fis_sta, ene_fis_end);
  if( err_flg < 0 )
  {
    clear_thermal_quantity();
    return;
  }

  check_xs_data(nbt_fis, int_fis, ene_fis, nbt_cap, int_cap, ene_cap);
  if( err_flg < 0 )
  {
    clear_thermal_quantity();
    return;
  }
  
  calc_thermal_quantity(ene_cap, sig_fis, sig_cap, ene_fis_sta, ene_fis_end);
  ene_fis.clear();
  sig_fis.clear();
  ene_cap.clear();
  sig_cap.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Integer ThermalQuantityCalculator::check_temp(Real8 temp_val)
{
  Integer chk_temp_flg = 0;
  
  ene_ori = temp_val * boltzmann_const;
  
  if( fabs(ene_ori - conv_th_ene) > conv_th_ene * 0.001 )
  {
    chk_temp_flg = 1;
  }
  
  return chk_temp_flg;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Integer ThermalQuantityCalculator::check_nucl_data_obj(NuclearDataObject& data_obj)
{
  Integer chk_nucl_flg = 0;

  CrossSectionDataContainer xs_obj_fis = data_obj.get_nucl_reaction_data_obj().get_xs_data_obj(18); 
  if( xs_obj_fis.get_reaction_type() == 18 && static_cast<int>(xs_obj_fis.get_xs_data().size()) > 0 )
  {
    chk_nucl_flg = 1;
    if( data_obj.get_fis_data_obj().get_nu_bar_repr_flg() == 1 )
    { 
      if( static_cast<int>(data_obj.get_fis_data_obj().get_nu_bar_polynomial_coef().size()) > 0 )
      {
        chk_nucl_flg = 0;
      }
    }
    else
    {
      if( static_cast<int>(data_obj.get_fis_data_obj().get_nu_bar_data().size()) > 0 )
      {
        chk_nucl_flg = 0;
      }
    }
  }

  return chk_nucl_flg;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalQuantityCalculator::check_xs_data(vector<Integer>& nbt_fis, vector<Integer>& int_fis, 
                                              vector<Real>& ene_fis,
                                              vector<Integer>& nbt_cap, vector<Integer>& int_cap, 
                                              vector<Real>& ene_cap)
{
  if( ( nbt_fis.size() != int_fis.size() ) || ( nbt_cap.size() != int_cap.size() ) )
  {
    string class_name = "ThermalQuantityCalculator";
    string func_name  = "check_xs_data(vector<Integer>& nbt_fis, vector<Integer>& int_fis, ";
           func_name += "vector<Real>& ene_fis, vector<Integer>& nbt_cap, vector<Integer>& int_cap, ";
           func_name += "vector<Real>& ene_cap )";
    ostringstream oss01, oss02, oss03, oss04;
    oss01 << nbt_fis.size();
    oss02 << int_fis.size();
    oss03 << nbt_cap.size();
    oss04 << int_cap.size();
    string str_data01 = "Size of nbt_fis : " + oss01.str();
    string str_data02 = "Size of int_fis : " + oss02.str();
    string str_data03 = "Size of nbt_cap : " + oss03.str();
    string str_data04 = "Size of int_cap : " + oss04.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);

    if( nbt_fis.size() != int_fis.size() )
    {
      err_com.push_back("The array size of nbt_fis and int_fis is different.");
    }
    if( nbt_cap.size() != int_cap.size() )
    {
      err_com.push_back("The array size of nbt_cap and int_cap is different.");
    }
    err_com.push_back("The thermal quantities calculation may not be appropriate.");
    err_obj.output_caution(class_name, func_name, err_com);
  }
  
  //Check int scheme of fission xs
  int i_max = static_cast<int>(int_fis.size());
  for(int i=0; i<i_max; i++)
  {
    if( int_fis[i] != 2 )
    {
      string class_name = "ThermalQuantityCalculator";
      string func_name  = "check_xs_data(vector<Integer>& nbt_fis, vector<Integer>& int_fis, ";
             func_name += "vector<Real>& ene_fis, vector<Integer>& nbt_cap, vector<Integer>& int_cap, ";
             func_name += "vector<Real>& ene_cap )";
      ostringstream oss01, oss02, oss03;
      oss01 << i;
      oss02 << i_max;
      oss03 << int_cap[i];
      string str_data01 = "INT number : " + oss01.str() + " / " + oss02.str();;
      string str_data02 = "INT        : " + oss03.str();
      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back("The interpolation scheme of the fission cross section is not linear-linear.");
      err_com.push_back("Thermal quantity calculation is skipped.");
      err_obj.output_caution(class_name, func_name, err_com);

      err_flg = -1;
      return;
    }
  }
  
  
  //Check int scheme of capture xs
  i_max = static_cast<int>(int_cap.size());
  for(int i=0; i<i_max; i++)
  {
    if( int_cap[i] != 2 )
    {
      string class_name = "ThermalQuantityCalculator";
      string func_name  = "check_xs_data(vector<Integer>& nbt_fis, vector<Integer>& int_fis, ";
             func_name += "vector<Real>& ene_fis, vector<Integer>& nbt_cap, vector<Integer>& int_cap, ";
             func_name += "vector<Real>& ene_cap )";
      ostringstream oss01, oss02, oss03;
      oss01 << i;
      oss02 << i_max;
      oss03 << int_cap[i];
      string str_data01 = "INT number : " + oss01.str() + " / " + oss02.str();;
      string str_data02 = "INT        : " + oss03.str();
      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back("The interpolation scheme of the radiation cross section is not linear-linear.");
      err_com.push_back("Thermal quantity calculation is skipped.");
      err_obj.output_caution(class_name, func_name, err_com);

      err_flg = -1;
      return;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalQuantityCalculator::search_fission_energy_grid( vector<Real>& ene_fis, vector<Real>& ene_cap,
                                                            int& ene_fis_sta, int& ene_fis_end )
{
  //Check energy grid of fission and capture cross section
  int i_max = static_cast<int>(ene_fis.size());
  if( i_max > 0 )
  {
    if( i_max != static_cast<int>(ene_cap.size()) )
    {
      string class_name = "ThermalQuantityCalculator";
      string func_name  = "search_fission_energy_grid(vector<Real>& ene_fis, vector<Real>& ene_cap, ";
             func_name += "int& ene_fis_sta, int& ene_fis_end)";
      ostringstream oss01, oss02, oss03;
      oss01 << static_cast<int>(ene_fis.size());
      oss02 << static_cast<int>(ene_cap.size());
      string str_data01 = "Size of energy grid of fission : " + oss01.str();
      string str_data02 = "Size of energy grid of capture : " + oss02.str();
      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back("The array size of fission and radiation energy grid is different.");
      err_com.push_back("The thermal quantities calculation may not be appropriate.");
      err_obj.output_caution(class_name, func_name, err_com);
    }
//ene_fis[0] = 3.73294250;

    int j_max = static_cast<int>(ene_cap.size());
    Real8 ene_dif = fabs(ene_fis[0] * min_ene_dif);
    ene_fis_sta = -1;
    for(int j=0; j<j_max; j++)
    {
      if( fabs(ene_fis[0] - ene_cap[j]) < ene_dif )
      {
        ene_fis_sta = j;
      }
    }
    if( ene_fis_sta < 0 )
    {
      string class_name = "ThermalQuantityCalculator";
      string func_name  = "search_fission_energy_grid(vector<Real>& ene_fis, vector<Real>& ene_cap, ";
             func_name += "int& ene_fis_sta, int& ene_fis_end)";
      ostringstream oss01, oss02, oss03;
      oss01 << ene_fis[0];
      oss02 << ene_cap[0];
      oss03 << ene_cap[j_max-1];
      string str_data01  = "Minimum energy of fission : " + oss01.str();
      string str_data02  = "Minimum energy of capture : " + oss02.str();
      string str_data03  = "Maximum energy of capture : " + oss03.str();
      string str_data04  = "The first energy grid in the fission cross section is not found ";
             str_data04 += "in that in the capture cross section.";

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back(str_data04);
      err_com.push_back("Thermal quantity calculation is skipped.");
      err_obj.output_caution(class_name, func_name, err_com);

      err_flg = -1;
      return;
    }
    
    int ele_no = ene_fis_sta;
    for(int i=0; i<i_max; i++)
    {
      if( ele_no >= j_max )
      {
        string class_name = "ThermalQuantityCalculator";
        string func_name  = "search_fission_energy_grid(vector<Real>& ene_fis, vector<Real>& ene_cap, ";
               func_name += "int& ene_fis_sta, int& ene_fis_end)";
        ostringstream oss01, oss02, oss03, oss04, oss05, oss06;
        oss01 << i;
        oss02 << i_max;
        oss03 << ene_fis[i_max];
        oss04 << ene_fis[i_max-1];
        oss05 << j_max;
        oss06 << ene_cap[j_max-1];
        string str_data01 = "Energy grid of fission         : " + oss01.str() + " / " + oss02.str();
        string str_data02 = "Energy of fission              : " + oss03.str();
        string str_data03 = "Maximum Energy of fission      : " + oss04.str();
        string str_data04 = "Maximum Energy grid of capture : " + oss05.str();
        string str_data05 = "Maximum Energy of capture      : " + oss06.str();

        vector<string> err_com;
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back(str_data04);
        err_com.push_back(str_data05);
        err_com.push_back("The maximum energy of fission is higher than that of capture.");
        err_com.push_back("Thermal quantity calculation is skipped.");
        err_obj.output_caution(class_name, func_name, err_com);

        err_flg = -1;
	return;
      }
      else if( fabs(ene_fis[i] - ene_cap[ele_no]) > min_ene_dif*ene_fis[i] )
      {
        string class_name = "ThermalQuantityCalculator";
        string func_name  = "search_fission_energy_grid(vector<Real>& ene_fis, vector<Real>& ene_cap, ";
               func_name += "int& ene_fis_sta, int& ene_fis_end)";
        ostringstream oss01, oss02, oss03, oss04, oss05, oss06;
        oss01 << i;
        oss02 << i_max;
        oss03 << ene_fis[i];
        oss04 << ele_no;
        oss05 << j_max;
        oss06 << ene_cap[ele_no];
        string str_data01 = "Energy grid of fission : " + oss01.str() + " / " + oss02.str();
        string str_data02 = "Energy of fission      : " + oss03.str();
        string str_data03 = "Energy grid of capture : " + oss04.str() + " / " + oss05.str();
        string str_data04 = "Energy of capture      : " + oss06.str();

        vector<string> err_com;
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back(str_data04);
        err_com.push_back("The energy grid of fission and radiation cross section is different.");
        err_com.push_back("Thermal quantity calculation is skipped.");
        err_obj.output_caution(class_name, func_name, err_com);

        err_flg = -1;
	return;
      }
      ele_no++;
    }
    ene_fis_end = ele_no;
  }
  else
  {
    ene_fis_sta = 0;
    ene_fis_end = 0;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalQuantityCalculator::calc_thermal_quantity( vector<Real>& ene_vec,
                                                       vector<Real>& sig_fis, vector<Real>& sig_cap,
                                                       int& ene_fis_sta, int& ene_fis_end )
{
  if( static_cast<int>(ene_vec.size()) == 0 )
  {
    clear_thermal_quantity();
    return;
  }

  if( ene_fis_end - ene_fis_sta > 0 )
  {
    fissile_flg = 0;
  }
  else
  {
    fissile_flg = 1;
  }

  Integer int_val = int_lin_lin;
  
  Real8 ene_tmp = conv_th_ene;
  ti_obj.interpolation_1d(int_val, ene_tmp, sig_c_th, ene_vec, sig_cap);
  
  ti_obj.interpolation_1d(int_val, ene_ori, sig_c_ori, ene_vec, sig_cap);
  
  ene_tmp = ene_reso;
  ti_obj.interpolation_1d(int_val, ene_tmp, sig_c_reso, ene_vec, sig_cap);
  
  if( fissile_flg == 0 )
  {
    Real ene_fis_min = ene_vec[ene_fis_sta];
    Real ene_fis_max = ene_vec[ene_fis_end-1];
    vector<Real> ene_vec_fis;
    ene_vec_fis.resize(ene_fis_end - ene_fis_sta);
    int ele_no = 0; 
    for(int i=ene_fis_sta; i<ene_fis_end; i++)
    {
      ene_vec_fis[ele_no] = ene_vec[i];
      ele_no++;
    }

    sig_f_th   = 0.0;
    sig_f_ori  = 0.0;
    sig_f_reso = 0.0;

    ene_tmp   = conv_th_ene;
    nu_bar_th = nu_obj.calc_nu_bar(nucl_data_obj, ene_tmp);

    if( ene_tmp >= ene_fis_min && ene_tmp <= ene_fis_max )
    {
      ti_obj.interpolation_1d(int_val, ene_tmp, sig_f_th, ene_vec_fis, sig_fis);
    }

    nu_bar_ori = nu_obj.calc_nu_bar(nucl_data_obj, ene_ori);
    if( ene_ori >= ene_fis_min && ene_ori <= ene_fis_max )
    {
      ti_obj.interpolation_1d(int_val, ene_ori, sig_f_ori, ene_vec_fis, sig_fis);
    }

    ene_tmp = ene_reso;
    if( ene_tmp >= ene_fis_min && ene_tmp <= ene_fis_max )
    {
      ti_obj.interpolation_1d(int_val, ene_tmp, sig_f_reso, ene_vec_fis, sig_fis);
    }
  }
  
  calc_integral_value(ene_vec, sig_fis, sig_cap, ene_fis_sta, ene_fis_end);
  calc_resonance_integral_value(ene_vec, sig_fis, sig_cap, ene_fis_sta, ene_fis_end);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalQuantityCalculator::calc_integral_value( vector<Real>& ene_vec,
                                                     vector<Real>& sig_fis, vector<Real>& sig_cap,
                                                     int ene_fis_sta, int ene_fis_end )
{
  Integer   int_val = int_lin_lin;

  g_fac_fis = 0.0;
  inte_fis  = 0.0;
  g_fac_cap = 0.0;
  inte_cap  = 0.0;
  alpha     = 0.0;
  eta       = 0.0;
  k1        = 0.0;
  k1_eq     = 0.0;
  
  int i_max = static_cast<int>(ene_vec.size());
  if( i_max == 0 )
  {
    return;
  }
  
  Real  ene_fis_min, ene_fis_max;
  Real8 ene_max, ene_ori_inv, ene_dis;
  Real8 ene_pre, ene_cur, sig_f_cur, sig_f_pre, sig_c_cur, sig_c_pre, nu_cur, nu_pre, f_cur, f_pre;
  int   ele_no = 0;
  
  ene_fis_min  = 0.0;
  ene_fis_max  = 0.0;
  ene_max      = 1.0;
  ene_ori_inv  = -1.0/ene_ori;
  ene_pre      = ene_vec[ele_no];
  sig_c_pre    = sig_cap[ele_no];
  sig_f_pre    = 0.0;
  nu_pre       = 0.0;
  f_pre        = ene_pre * exp(ene_pre*ene_ori_inv);
  if( fissile_flg == 0 )
  {
    ene_fis_min = ene_vec[ene_fis_sta]   + min_ene_dif;
    ene_fis_max = ene_vec[ene_fis_end-1] + min_ene_dif;
    sig_f_pre   = 0.0;
    if( ele_no >= ene_fis_sta )
    {
      sig_f_pre = sig_fis[ele_no - ene_fis_sta];
    }
    nu_pre      = nu_obj.calc_nu_bar(nucl_data_obj, ene_pre);
  }
  while( ele_no < i_max-1 && ene_pre < ene_max )
  {
    if( ene_pre*1.01 > ene_vec[ele_no+1] )
    {
      ele_no++;
      ene_cur   = ene_vec[ele_no];
      sig_c_cur = sig_cap[ele_no];
    }
    else
    {
      ene_cur = ene_pre*1.01;
      ti_obj.interpolation_1d(int_val, ene_cur, sig_c_cur,
                              ene_vec[ele_no], sig_cap[ele_no], ene_vec[ele_no+1], sig_cap[ele_no+1]);
    }
    
    f_cur   = ene_cur * exp(ene_cur*ene_ori_inv);
    ene_dis = 0.5 * (ene_cur - ene_pre);
    
    inte_cap += (f_cur*sig_c_cur + f_pre*sig_c_pre) * ene_dis;
    
    if( fissile_flg == 0 )
    {
      nu_cur  = nu_obj.calc_nu_bar(nucl_data_obj, ene_cur);
      k1     -= ( f_cur*( sig_c_cur) + f_pre*( sig_c_pre) ) * ene_dis;
      if( ele_no >= ene_fis_sta && ene_cur < ene_fis_max )
      {
        int ele_no_fis = ele_no - ene_fis_sta;
        if( ene_pre*1.01 > ene_vec[ele_no+1] )
        {
          sig_f_cur = sig_fis[ele_no_fis];
        }
        else
        {
          ti_obj.interpolation_1d(int_val, ene_cur, sig_f_cur,
                             ene_vec[ele_no], sig_fis[ele_no_fis], ene_vec[ele_no+1], sig_fis[ele_no_fis+1]);
        }
 
        if( ene_cur > ene_fis_min )
        {
          inte_fis += (f_cur*sig_f_cur + f_pre*sig_f_pre) * ene_dis;
          k1       += ( f_cur*((nu_cur-1.0)*sig_f_cur) + f_pre*((nu_pre-1.0)*sig_f_pre) ) * ene_dis;
          //k1       += ( f_cur*((nu_cur-1.0)*sig_f_cur - sig_c_cur)
          //            + f_pre*((nu_pre-1.0)*sig_f_pre - sig_c_pre) ) * ene_dis;
        
          if( sig_f_cur > 0.0 && sig_f_pre > 0.0 )
          {
            alpha += (f_cur*sig_c_cur/sig_f_cur + f_pre*sig_c_pre/sig_f_pre) * ene_dis;
          }
          if( fabs(sig_f_cur + sig_c_cur) > 0.0 && fabs(sig_f_pre + sig_c_pre) > 0.0 )
          {
            eta += ( f_cur*nu_cur*sig_f_cur/(sig_f_cur+sig_c_cur)
                   + f_pre*nu_pre*sig_f_pre/(sig_f_pre+sig_c_pre) ) * ene_dis;
          }
        }
        sig_f_pre = sig_f_cur;
      }
      nu_pre    = nu_cur;
    }
    ene_pre   = ene_cur;
    sig_c_pre = sig_c_cur;
    f_pre     = f_cur;
  }
  
  ene_ori_inv = ene_ori_inv * ene_ori_inv; // = 1.0/(ene_ori*ene_ori)
  inte_cap   *= ene_ori_inv;
  g_fac_cap   = (2.0/sqrt(M_PI)) * inte_cap / sig_c_ori;
  
  if( fissile_flg == 0 )
  {
    inte_fis *= ene_ori_inv;
    alpha    *= ene_ori_inv;
    eta      *= ene_ori_inv;
    k1       *= ene_ori_inv;
    if( fabs(sig_f_ori) > min_sig_dif )
    {
      g_fac_fis = (2.0/sqrt(M_PI)) * inte_fis / sig_f_ori;
    }
    else
    {
      g_fac_fis = 0.0;
    }
    k1_eq     = (2.0/sqrt(M_PI)) * k1;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalQuantityCalculator::calc_resonance_integral_value( vector<Real>& ene_vec,
                                                               vector<Real>& sig_fis, vector<Real>& sig_cap,
                                                               int ene_fis_sta, int ene_fis_end )
{
  Integer int_val = int_lin_lin;
  inte_fis_reso   = 0.0;
  inte_cap_reso   = 0.0;
  
  int i_max = static_cast<int>(ene_vec.size());
  if( i_max == 0 )
  {
    return;
  }
  
  int ele_no = -100;
  for(int i=0; i<i_max; i++)
  {
    if(ene_vec[i] >= ene_reso)
    {
      ele_no = i-1;
      break;
    }
  }
  if( ele_no == -100 ) //Maximum energy grid is less than ene_reso.
  {
    return;
  }
  
  Real8 ene_pre, ene_cur, ene_dis, sig_f_cur, sig_f_pre, sig_c_cur, sig_c_pre;
  sig_f_pre = 0.0;
  if( ele_no >= 0 )
  {
    ene_pre   = ene_reso;
    sig_c_pre = sig_c_reso;
    if( fissile_flg == 0 )
    {
      if( ele_no >= ene_fis_sta && ele_no < ene_fis_end )
      {
        sig_f_pre = sig_f_reso;
      }
      else if( ele_no < ene_fis_sta )
      {
        sig_f_pre = sig_fis[0];
      }
      else
      {
        sig_f_pre = sig_fis[ene_fis_end - ene_fis_sta - 1];
      }
    }
  }
  else //Minimum energy grid is larger than ene_reso.
  {
    ele_no    = 0;
    ene_pre   = ene_vec[ele_no];
    sig_c_pre = sig_cap[ele_no];
    if( fissile_flg == 0 )
    {
      if( ele_no >= ene_fis_sta && ele_no < ene_fis_end )
      {
        sig_f_pre = sig_fis[ele_no - ene_fis_sta];
      }
      else if( ele_no < ene_fis_sta )
      {
        sig_f_pre = sig_fis[0];
      }
      else
      {
        sig_f_pre = sig_fis[ene_fis_end - ene_fis_sta - 1];
      }
    }
  }

  Real ene_fis_min, ene_fis_max;
  ene_fis_min = 0;
  ene_fis_max = 0;
  if( fissile_flg == 0 )
  {
    ene_fis_min = ene_vec[ene_fis_sta]   + min_ene_dif;
    ene_fis_max = ene_vec[ene_fis_end-1] + min_ene_dif;
  }
  while( ele_no < i_max-1 )
  {
    if( ene_pre*1.01 > ene_vec[ele_no+1] )
    {
      ele_no++;
      ene_cur   = ene_vec[ele_no];
      sig_c_cur = sig_cap[ele_no];
    }
    else
    {
      ene_cur = ene_pre*1.01;
      ti_obj.interpolation_1d(int_val, ene_cur, sig_c_cur,
                              ene_vec[ele_no], sig_cap[ele_no], ene_vec[ele_no+1], sig_cap[ele_no+1]);
    }
    ene_dis = 0.5 * (ene_cur - ene_pre);
    inte_cap_reso += (sig_c_cur/ene_cur + sig_c_pre/ene_pre) * ene_dis;
    
    if( fissile_flg == 0 && ele_no >= ene_fis_sta && ene_cur < ene_fis_max )
    {
      int ele_no_fis = ele_no - ene_fis_sta;
      if( ene_pre*1.01 > ene_vec[ele_no+1] )
      {
        sig_f_cur = sig_fis[ele_no_fis];
      }
      else
      {
        ti_obj.interpolation_1d(int_val, ene_cur, sig_f_cur,
                             ene_vec[ele_no], sig_fis[ele_no_fis], ene_vec[ele_no+1], sig_fis[ele_no_fis+1]);
      }
      if( ene_cur > ene_fis_min )
      {
        inte_fis_reso += (sig_f_cur/ene_cur + sig_f_pre/ene_pre) * ene_dis;
      }
      sig_f_pre = sig_f_cur;
    }
    ene_pre   = ene_cur;
    sig_c_pre = sig_c_cur;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalQuantityCalculator::clear()
{
  nucl_data_obj.clear();

  vector<CrossSectionDataContainer>().swap(xs_data_obj);
  //int i_max = static_cast<int>(xs_data_obj.size());
  //for(int i=0; i<i_max; i++)
  //{
  //  xs_data_obj[i].clear();
  //}
  //xs_data_obj.resize(0);

  temp_ori      = 0.0;

  err_flg       = 0;
  calc_flg      = 0;
  fissile_flg   = 0;

  ene_ori       = 0.0;

  clear_thermal_quantity();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalQuantityCalculator::clear_thermal_quantity()
{
  sig_f_th      = 0.0;
  sig_c_th      = 0.0;
  nu_bar_th     = 0.0;
  
  sig_f_ori     = 0.0;
  sig_c_ori     = 0.0;
  nu_bar_ori    = 0.0;
  
  sig_f_reso    = 0.0;
  sig_c_reso    = 0.0;
  
  g_fac_fis     = 0.0;
  g_fac_cap     = 0.0;
  inte_fis      = 0.0;
  inte_cap      = 0.0;
  inte_fis_reso = 0.0;
  inte_cap_reso = 0.0;
  alpha         = 0.0;
  eta           = 0.0;
  k1            = 0.0;
  k1_eq         = 0.0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalQuantityCalculator::set_nucl_data_obj(NuclearDataObject data_obj)
{
  clear();

  nucl_data_obj = data_obj;
  xs_data_obj   = nucl_data_obj.get_nucl_reaction_data_obj().get_xs_data_obj_assigned();

  data_obj.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalQuantityCalculator::set_temp_ori(Real8 real_val)
{
  calc_flg = 0;
  temp_ori = real_val;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//Getter

NuclearDataObject ThermalQuantityCalculator::get_nucl_data_obj()
{
  return nucl_data_obj;
}

Real8 ThermalQuantityCalculator::get_temp_ori()
{
  return temp_ori;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Integer ThermalQuantityCalculator::get_err_flg()
{
  return err_flg;
}

Integer ThermalQuantityCalculator::get_fissile_flg()
{
  calc_thermal_quantity();
  return fissile_flg;
}

Real8 ThermalQuantityCalculator::get_ene_ori()
{
  calc_thermal_quantity();
  return ene_ori;
}

Real8 ThermalQuantityCalculator::get_sig_f_th()
{
  calc_thermal_quantity();
  return sig_f_th;
}

Real8 ThermalQuantityCalculator::get_sig_c_th()
{
  calc_thermal_quantity();
  return sig_c_th;
}

Real8 ThermalQuantityCalculator::get_nu_bar_th()
{
  calc_thermal_quantity();
  return nu_bar_th;
}

Real8 ThermalQuantityCalculator::get_sig_f_ori()
{
  calc_thermal_quantity();
  return sig_f_ori;
}

Real8 ThermalQuantityCalculator::get_sig_c_ori()
{
  calc_thermal_quantity();
  return sig_c_ori;
}

Real8 ThermalQuantityCalculator::get_nu_bar_ori()
{
  calc_thermal_quantity();
  return nu_bar_ori;
}

Real8 ThermalQuantityCalculator::get_sig_f_reso()
{
  calc_thermal_quantity();
  return sig_f_reso;
}

Real8 ThermalQuantityCalculator::get_sig_c_reso()
{
  calc_thermal_quantity();
  return sig_c_reso;
}

Real8 ThermalQuantityCalculator::get_g_fac_fis()
{
  calc_thermal_quantity();
  return g_fac_fis;
}

Real8 ThermalQuantityCalculator::get_g_fac_cap()
{
  calc_thermal_quantity();
  return g_fac_cap;
}

Real8 ThermalQuantityCalculator::get_inte_fis()
{
  calc_thermal_quantity();
  return inte_fis;
}

Real8 ThermalQuantityCalculator::get_inte_cap()
{
  calc_thermal_quantity();
  return inte_cap;
}

Real8 ThermalQuantityCalculator::get_inte_fis_reso()
{
  calc_thermal_quantity();
  return inte_fis_reso;
}

Real8 ThermalQuantityCalculator::get_inte_cap_reso()
{
  calc_thermal_quantity();
  return inte_cap_reso;
}

Real8 ThermalQuantityCalculator::get_alpha()
{
  calc_thermal_quantity();
  return alpha;
}

Real8 ThermalQuantityCalculator::get_eta()
{
  calc_thermal_quantity();
  return eta;
}

Real8 ThermalQuantityCalculator::get_k1()
{
  calc_thermal_quantity();
  return k1;
}

Real8 ThermalQuantityCalculator::get_k1_eq()
{
  calc_thermal_quantity();
  return k1_eq;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

