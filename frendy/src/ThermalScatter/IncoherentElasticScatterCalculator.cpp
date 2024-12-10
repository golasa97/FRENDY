#include "ThermalScatter/IncoherentElasticScatterCalculator.hpp"

using namespace frendy;

//constructor
IncoherentElasticScatterCalculator::IncoherentElasticScatterCalculator(void)
{
  clear();
}

//destructor
IncoherentElasticScatterCalculator::~IncoherentElasticScatterCalculator(void)
{
  clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void IncoherentElasticScatterCalculator::clear()
{
  calc_incoherent_elastic_scat_flg = 0;

  opt_elastic = no_calc;
  bin_no      = 0;
  bin_no_int  = 0;
  atom_no     = 0;
  bin_no_real = 0.0;
  bin_no_inv  = 0.0;
  ene_max     = 0.0;
  temp        = 0.0;

  sig_b               = 0.0;
  sig_coef            = 0.0;
  debye_waller_factor = 0.0;

  ene_grid.clear();
  scat_xs.clear();
  clr_obj.clear_vec_array2_real8(mu);
  clr_obj.clear_vec_array2_real8(mu_ave);

  nucl_data_obj.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void IncoherentElasticScatterCalculator::calc_incoherent_elastic_scatter()
{
  if( calc_incoherent_elastic_scat_flg == 0 )
  {
    preparation_for_incoherent_erastic_scatter();
  }
  scat_xs.clear();
  clr_obj.clear_vec_array2_real8(mu);
  clr_obj.clear_vec_array2_real8(mu_ave);

  int i_max = static_cast<int>(ene_grid.size());
  scat_xs.resize(i_max);
  mu.resize(i_max);
  mu_ave.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    if( ene_grid[i] < ene_max + min_ene_dif )
    {
      calc_average_incoherent_elastic_scatter(ene_grid[i], scat_xs[i], mu[i], mu_ave[i]);
    }
    else
    {
      scat_xs[i] = 0.0;
      mu[i].resize(bin_no_int);
      mu_ave[i].resize(bin_no_int);
      for(int j=0; j<bin_no_int; j++)
      {
        mu[i][j]     = 0.0;
        mu_ave[i][j] = 0.0;
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void IncoherentElasticScatterCalculator::calc_average_incoherent_elastic_scatter
                                          ( Real8& ene_data, Real8& xs_data, 
                                            vector<Real8>& mu_data, vector<Real8>& mu_ave_data )
{
  Real8 we         = 2.0 * debye_waller_factor * ene_data;
  Real8 we_inv     = 1.0 / we;
  Real8 exp_we     = exp(-2.0*we);

  xs_data = sig_coef * (1.0 - exp_we) * we_inv;

  Real8 mu_pre      = -1.0;
  Real8 mu_coef_pre =  exp(we*(mu_pre-1.0));
  Real8 mu_coef_cur =  0.0;
  Real8 mu_ave_coef =  bin_no_real * we_inv / (1.0 - exp_we);
  mu_data.clear();
  mu_ave_data.clear();
  mu_data.resize(bin_no_int);
  mu_ave_data.resize(bin_no_int);
  for(int i=0; i<bin_no_int; i++)
  {
    mu_data[i]     = 1.0 + we_inv*log( (1.0 - exp_we)*bin_no_inv + mu_coef_pre );
    mu_coef_cur    = exp(we*(mu_data[i]-1.0));
    mu_ave_data[i] = mu_ave_coef * ( mu_coef_cur*(we*mu_data[i]-1.0) - mu_coef_pre*(we*mu_pre-1.0) );
    mu_pre         = mu_data[i];
    mu_coef_pre    = mu_coef_cur;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void IncoherentElasticScatterCalculator::preparation_for_incoherent_erastic_scatter()
{
  calc_incoherent_elastic_scat_flg = 1;
  set_energy_grid();

  if( opt_elastic == use_nucl_data )
  {
    set_debye_waller_factor_by_nucl_data();
  }
  else if( opt_elastic == calc_polyethylene ||
           opt_elastic == calc_h_in_zrh     || opt_elastic == calc_zr_in_zrh )
  {
    set_debye_waller_factor();
  }
  else if( opt_elastic == no_calc )
  {
    return;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void IncoherentElasticScatterCalculator::check_set_data()
{
  vector<string> err_com;
  err_com.clear();

  if( opt_elastic != use_nucl_data     && opt_elastic != no_calc       &&
      opt_elastic != calc_polyethylene && opt_elastic != calc_h_in_zrh && opt_elastic != calc_zr_in_zrh )
  {
    ostringstream oss01, oss02, oss03, oss04, oss05, oss06;
    oss01 << opt_elastic;
    oss02 << use_nucl_data;
    oss03 << no_calc;
    oss04 << calc_polyethylene;
    oss05 << calc_h_in_zrh;
    oss06 << calc_zr_in_zrh;
    string str_data01 = "Elastic option " + oss01.str();
    string str_data02 = "Elastic option is not appropriate.";
    string str_data03 = "Available elastic option";
    string str_data04 = "  Calculate using nuclear data : " + oss02.str();
    string str_data05 = "  No calculation               : " + oss03.str();
    string str_data06 = "  Polyethylene                 : " + oss04.str();
    string str_data07 = "  H  in ZrH                    : " + oss05.str();
    string str_data08 = "  Zr in ZrH                    : " + oss06.str();
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back(str_data05);
    err_com.push_back(str_data06);
    err_com.push_back(str_data07);
    err_com.push_back(str_data08);
  }

  if( bin_no <= 0 )
  {
    ostringstream oss01;
    oss01 << bin_no;
    string str_data01 = "Bin number : " + oss01.str();
    err_com.push_back(str_data01);
    err_com.push_back("Bin number is not input or set inappropriate value.");
  }

  if( atom_no < min_value )
  {
    ostringstream oss01;
    oss01 << atom_no;
    string str_data01 = "Atom number : " + oss01.str();
    err_com.push_back(str_data01);
    err_com.push_back("Atom number is not input or set inappropriate value.");
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
    string class_name = "IncoherentElasticScatterCalculator";
    string func_name  = "check_set_data()";
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void IncoherentElasticScatterCalculator::set_energy_grid()
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

  //Add ene_top and ene_add_p
  ene_grid_ref = xs_data_obj.get_xs_ene_data();
  i_max        = static_cast<int>(ene_grid.size());
  ene_top = ene_grid_ref[static_cast<int>(ene_grid_ref.size()) - 1];
  if( ene_top > ene_grid[i_max-1] + min_ene_dif )
  {
    Real ene_add_p = digit_obj.get_adjusted_value(ene_max, sig_fig-2, +1.0);
    if( ene_top > ene_add_p + min_ene_dif )
    {
      ene_grid.push_back(ene_add_p);
      ene_grid.push_back(ene_top);
    }
    else
    {
      ene_grid.push_back(ene_top);
    }
  }
  ene_grid_ref.clear();

  if( reaction_type != xs_data_obj.get_reaction_type() || i_max == 0 )
  {
    string class_name = "IncoherentElasticScatterCalculator";
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

void IncoherentElasticScatterCalculator::set_debye_waller_factor_by_nucl_data()
{
  ThermalScatterDataContainer sab_data_obj = nucl_data_obj.get_thermal_scat_data_obj();
  sig_b               = 0.0;
  sig_coef            = 0.0;
  debye_waller_factor = 0.0;

  if( sab_data_obj.get_elastic_scat_flg() != 2 && sab_data_obj.get_elastic_scat_flg() != 3 )
  {
    string class_name = "IncoherentElasticScatterCalculator";
    string func_name  = "set_debye_waller_factor_by_nucl_data()";

    ostringstream oss01;
    oss01 << sab_data_obj.get_elastic_scat_flg();
    string str_data01 = "Elastic scatter flg (LTHR) : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("This elastic scatter flg can not treat in this program.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //Seb bound xs
  sig_b    = sab_data_obj.get_elastic_bound_xs();
  sig_coef = 0.5 * sig_b / static_cast<Real8>(atom_no);

  //Set debye-waller factor
  Real         temp_real = static_cast<Real>(temp);
  vector<Real> temp_vec  = sab_data_obj.get_elastic_debye_waller_temp_data();
  vector<Real> dw_vec    = sab_data_obj.get_elastic_debye_waller_data();
  int i_max = static_cast<int>(temp_vec.size());
  if( temp_real >= temp_vec[0] * 0.9 && temp_real <= temp_vec[i_max-1] * 1.1 )
  {
    if( temp_real < temp_vec[0] )
    {
      debye_waller_factor = dw_vec[0];
    }
    else if( temp_real > temp_vec[i_max-1] )
    {
      debye_waller_factor = dw_vec[i_max-1];
    }
    else
    {
      vector<Integer> int_vec   = sab_data_obj.get_elastic_debye_waller_int_data();
      vector<Integer> range_vec = sab_data_obj.get_elastic_debye_waller_range_data();
      ti_obj.interpolation_tab1(temp_real, debye_waller_factor, range_vec, int_vec, temp_vec, dw_vec);
      int_vec.clear();
      range_vec.clear();
    }
  }
  else
  {
    string class_name = "IncoherentElasticScatterCalculator";
    string func_name  = "set_debye_waller_factor_by_nucl_data()";

    ostringstream oss01, oss02, oss03;
    oss01 << temp_real;
    oss02 << temp_vec[0] * 0.9;
    oss03 << temp_vec[i_max-1] * 1.1;
    string str_data01 = "Input   temperature : " + oss01.str();
    string str_data02 = "Minimum temperature : " + oss02.str();
    string str_data03 = "Maximum temperature : " + oss03.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("The input temparature is out of temperature range.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
  sab_data_obj.clear();
  temp_vec.clear();
  dw_vec.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void IncoherentElasticScatterCalculator::set_debye_waller_factor()
{
  int     ele_no = 8;
  Integer order  = 3;
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

  sig_b               = 0.0;
  sig_coef            = 0.0;
  debye_waller_factor = 0.0;
  if( opt_elastic == calc_polyethylene )
  {
    sig_b = 162.88;
    //debye_waller_factor = 34.957+(temp-296.0)*(40.282-34.957)/(350.0-296.0);
    debye_waller_factor = 34.957+(temp-296.0)*9.8611111111111E-02;
  }
  else if( opt_elastic == calc_h_in_zrh )
  {
    sig_b = 81.44;
    debye_waller_vec[0] =  8.4795;
    debye_waller_vec[1] =  9.0854;
    debye_waller_vec[2] =  9.8196;
    debye_waller_vec[3] = 10.6760;
    debye_waller_vec[4] = 11.6250;
    debye_waller_vec[5] = 12.6430;
    debye_waller_vec[6] = 14.8220;
    debye_waller_vec[7] = 17.1250;
    debye_waller_factor = math_obj.lagrange_interpolation(temp, order, debye_waller_temp, debye_waller_vec);
  }
  else if( opt_elastic == calc_zr_in_zrh )
  {
    sig_b = 6.3366;
    debye_waller_vec[0] = 1.9957;
    debye_waller_vec[1] = 2.6546;
    debye_waller_vec[2] = 3.2946;
    debye_waller_vec[3] = 3.9380;
    debye_waller_vec[4] = 4.5835;
    debye_waller_vec[5] = 5.2302;
    debye_waller_vec[6] = 6.5260;
    debye_waller_vec[7] = 7.8236;
    debye_waller_factor = math_obj.lagrange_interpolation(temp, order, debye_waller_temp, debye_waller_vec);
  }
  debye_waller_vec.clear();
  debye_waller_temp.clear();

  sig_coef = sig_b / static_cast<Real8>(atom_no);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//Setter

void IncoherentElasticScatterCalculator::set_nucl_data_obj(NuclearDataObject& data_obj)
{
  calc_incoherent_elastic_scat_flg = 0;
  nucl_data_obj = data_obj;
}

void IncoherentElasticScatterCalculator::set_opt_elastic(Integer& int_data)
{
  calc_incoherent_elastic_scat_flg = 0;
  opt_elastic = int_data;
}

void IncoherentElasticScatterCalculator::set_bin_no(Integer& int_data)
{
  bin_no      = int_data;
  bin_no_int  = static_cast<int>(bin_no);
  bin_no_real = static_cast<Real8>(bin_no);
  bin_no_inv  = 1.0 / bin_no_real;
}

void IncoherentElasticScatterCalculator::set_atom_no(Integer& int_data)
{
  calc_incoherent_elastic_scat_flg = 0;
  atom_no = int_data;
}

void IncoherentElasticScatterCalculator::set_ene_max(Real8& real_data)
{
  calc_incoherent_elastic_scat_flg = 0;
  ene_max = real_data;
}

void IncoherentElasticScatterCalculator::set_temp(Real8& real_data)
{
  calc_incoherent_elastic_scat_flg = 0;
  temp = real_data;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//Getter

NuclearDataObject IncoherentElasticScatterCalculator::get_nucl_data_obj()
{
  calc_incoherent_elastic_scatter();

  ThermalScatterDataContainer sab_data_obj = nucl_data_obj.get_thermal_scat_data_obj();
  sab_data_obj.set_incoherent_elastic_ene_grid(ene_grid);
  sab_data_obj.set_incoherent_elastic_scat_xs(scat_xs);
  sab_data_obj.set_incoherent_elastic_scat_angle(mu);
  sab_data_obj.set_incoherent_elastic_average_scat_angle(mu_ave);
  nucl_data_obj.set_thermal_scat_data_obj(sab_data_obj);
  sab_data_obj.clear();

  GeneralDataContainer general_data_obj = nucl_data_obj.get_general_data_obj();
  general_data_obj.set_temp(temp);
  nucl_data_obj.set_general_data_obj(general_data_obj);
  general_data_obj.clear();

  return nucl_data_obj;
}

Integer IncoherentElasticScatterCalculator::get_opt_elastic()
{
  return opt_elastic;
}

Integer IncoherentElasticScatterCalculator::get_bin_no()
{
  return bin_no;
}

Integer IncoherentElasticScatterCalculator::get_atom_no()
{
  return atom_no;
}

Real8 IncoherentElasticScatterCalculator::get_ene_max()
{
  return ene_max;
}

Real8 IncoherentElasticScatterCalculator::get_temp()
{
  return temp;
}
