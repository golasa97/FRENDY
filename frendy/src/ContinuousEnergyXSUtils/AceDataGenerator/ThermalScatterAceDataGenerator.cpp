#include "ContinuousEnergyXSUtils/AceDataGenerator/ThermalScatterAceDataGenerator.hpp"

using namespace frendy;

//Initialize static const value
const Real8 ThermalScatterAceDataGenerator::min_second_ene_dif_abs = ThermalScatterAceDataObject::min_second_ene_dif_abs;

//constructor
ThermalScatterAceDataGenerator::ThermalScatterAceDataGenerator(void)
{
  third = 1.0 / 3.0;
  clear();
}

//destructor
ThermalScatterAceDataGenerator::~ThermalScatterAceDataGenerator(void)
{
  clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterAceDataGenerator::clear()
{
  clear_calc_data();
  clear_ace_data();

  gen_th_scat_data_flg = 0;
  nucl_data_set_flg    = 0;
  mat_set_flg          = 0;
  temp_set_flg         = 0;

  nucl_data_obj.clear();

  mat           = 0;
  temp          = 0.0;

  mt_inelastic  = 0;
  mt_elastic    = 0;
  elastic_flg   = 0;
  atom_no_th    = 0;
  opt_weight    = 0;
  suffix_za_id  = 0.0;
  ene_max_th    = 0.0;
  zi_vec.clear();
  awr_vec.clear();
  mod_za.clear();

  mcnpx_mode_flg = 0;
  thermal_za_id_name.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterAceDataGenerator::clear_calc_data()
{
  clr_obj.clear_vec_array1_str(title_data);

  xs_data_inelastic.clear();
  xs_data_elastic.clear();
  prod_distr_data_inelastic.clear();
  prod_distr_data_elastic.clear();
  zi_vec.clear();
  awr_vec.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterAceDataGenerator::clear_ace_data()
{
  aw0 = 0.0;
  tz  = 0.0;
  clr_obj.clear_vec_array1_str(title_data);
  discriptive_data.clear();

  coh_elastic_ene_data.clear();
  coh_elastic_e_xs_data.clear();
  incoh_elastic_ene_data.clear();
  incoh_elastic_xs_data.clear();
  clr_obj.clear_vec_array2_real(incoh_elastic_scat_angle);

  inelastic_ene_data.clear();
  inelastic_xs_data.clear();
  clr_obj.clear_vec_array2_real(inelastic_second_ene_cal);
  clr_obj.clear_vec_array2_real(inelastic_scat_xs_int_cal);
  clr_obj.clear_vec_array2_real(inelastic_weight);
  clr_obj.clear_vec_array3_real(inelastic_scat_xs_weight);

  clear_ace_pointer_data();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterAceDataGenerator::clear_ace_pointer_data()
{
  len2  = 0;
  idpni = 0;
  nil   = 0;
  nieb  = 0;
  idpnc = 0;
  ncl   = 0;
  ifeng = 0;
  itie  = 0;
  itix  = 0;
  itxe  = 0;
  itce  = 0;
  itcx  = 0;
  itca  = 0;
  nie   = 0;
  nee   = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterAceDataGenerator::copy_thermal_scat_ace_data(ThermalScatterAceDataObject& ace_data_obj)
{
  ace_data_obj.clear();
  
  ace_data_obj.set_mcnpx_mode_flg(mcnpx_mode_flg);

  ace_data_obj.set_aw0(aw0);
  ace_data_obj.set_tz(tz);
  ace_data_obj.set_title_data(title_data);
  ace_data_obj.set_discriptive_data(discriptive_data);

  ace_data_obj.set_mod_za(mod_za);

  int vec_no = static_cast<int>(zi_vec.size());
  for(int i=0; i<3-vec_no; i++)
  {
    zi_vec.push_back(0);
    awr_vec.push_back(0.0);
  }
  zi_vec[0] = mod_za[0];
  zi_vec[1] = mod_za[1];
  zi_vec[2] = mod_za[2];
  if( zi_vec[0] == static_cast<Integer>(round(nucl_data_obj.get_general_data_obj().get_mat_data())) )
  {
    zi_vec[0] = nucl_data_obj.get_general_data_obj().get_izaid_ace();
  }
  ace_data_obj.set_zi_vec(zi_vec);
  ace_data_obj.set_awr_vec(awr_vec);

  //For elastic
  ace_data_obj.set_coh_elastic_ene_data(coh_elastic_ene_data);
  ace_data_obj.set_coh_elastic_e_xs_data(coh_elastic_e_xs_data);
  ace_data_obj.set_incoh_elastic_ene_data(incoh_elastic_ene_data);
  ace_data_obj.set_incoh_elastic_xs_data(incoh_elastic_xs_data);
  ace_data_obj.set_incoh_elastic_scat_angle(incoh_elastic_scat_angle);

  //For inelastic
  ace_data_obj.set_inelastic_ene_data(inelastic_ene_data);
  ace_data_obj.set_inelastic_xs_data(inelastic_xs_data);
  ace_data_obj.set_inelastic_second_ene(inelastic_second_ene_cal);
  ace_data_obj.set_inelastic_scat_xs_int(inelastic_scat_xs_int_cal);
  ace_data_obj.set_inelastic_weight(inelastic_weight);
  ace_data_obj.set_inelastic_scat_xs_weight(inelastic_scat_xs_weight);

  //For pointer data
  ace_data_obj.set_len2(len2);
  ace_data_obj.set_idpni(idpni);
  ace_data_obj.set_nil(nil);
  ace_data_obj.set_nieb(nieb);
  ace_data_obj.set_idpnc(idpnc);
  ace_data_obj.set_ncl(ncl);
  ace_data_obj.set_ifeng(ifeng);
  ace_data_obj.set_itie(itie);
  ace_data_obj.set_itix(itix);
  ace_data_obj.set_itxe(itxe);
  ace_data_obj.set_itce(itce);
  ace_data_obj.set_itcx(itcx);
  ace_data_obj.set_itca(itca);
  ace_data_obj.set_nie(nie);
  ace_data_obj.set_nee(nee);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterAceDataGenerator::generate_ace_data()
{
  if( gen_th_scat_data_flg != 0 )
  {
    return;
  }
  gen_th_scat_data_flg = 1;

  clear_calc_data();
  check_set_data();

  vector<Real> prod_ene_inelastic = prod_distr_data_inelastic.get_incident_ene();

  int i_max = static_cast<int>(prod_ene_inelastic.size());
  if( i_max <= 1 )
  {
    string class_name = "ThermalScatterAceDataGenerator";
    string func_name  = "generate_ace_data()";
    vector<string> err_com;

    ostringstream oss01;
    oss01 << i_max;
    string str_data01 = "The number of energy grid for inelastic scattering (MF=6) : " + oss01.str();
    err_com.push_back(str_data01);

    for(int i=0; i<i_max; i++)
    {
      ostringstream oss02, oss03;
      oss02 << i+1;
      oss03 << prod_ene_inelastic[i];
      string str_data02 = "  " + oss02.str() + " : " + oss03.str() + " [eV]";
      err_com.push_back(str_data02);
    }

    err_com.push_back("The number of energy grid for inelastic scattering is so small.");
    err_com.push_back("Please check the inelastic scattering cross section data.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }


  Real e_max_xs = prod_ene_inelastic[i_max-1];
  if( i_max > 2 && xs_data_inelastic.get_xs_data()[i_max-1] < min_sig_val )
  {
    e_max_xs = prod_ene_inelastic[i_max-2];
  }

  if( ene_max_th > e_max_xs )
  {
    string class_name = "ThermalScatterAceDataGenerator";
    string func_name  = "generate_ace_data()";

    ostringstream oss01, oss02;
    oss01 << ene_max_th;
    oss02 << e_max_xs;
    string str_data01 = "Maximum thermal scattering energy from input          : "  + oss01.str() + " [eV]";
    string str_data02 = "Maximum thermal scattering energy from XS data (MF=6) : "  + oss02.str() + " [eV]";
    string str_data03 = "The maximum thermal scattering energy is reset to " + oss02.str() + " eV.";

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("The maximum thermal scattering energy from input file is larger than MF=6 data.");
    err_com.push_back(str_data03);
    err_obj.output_caution(class_name, func_name, err_com);

    ene_max_th = e_max_xs;
  }
  else
  {
    Real ene_max_th_pre = ene_max_th;

    int i_m = 0;
    int i_p = 0;
    ti_obj.search_neighbor_value(ene_max_th, prod_ene_inelastic, i_m, i_p);
    ene_max_th = prod_ene_inelastic[i_p];

    if( fabs(ene_max_th_pre - ene_max_th) > fabs(ene_max_th_pre + min_ene_dif) * 1.0E-2 )
    {
      string class_name = "ThermalScatterAceDataGenerator";
      string func_name  = "generate_ace_data()";

      ostringstream oss01, oss02;
      oss01 << ene_max_th_pre;
      oss02 << ene_max_th;
      string str_data01 = "Maximum thermal scattering energy from input   : " + oss01.str() + " [eV]";
      string str_data02 = "Modified maximum thermal scattering energy     : " + oss02.str() + " [eV]";

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back("The maximum thermal scattering energy from input file is modified");
      err_com.push_back("to fit the energy grid of MF=6 data.");
      err_obj.output_caution(class_name, func_name, err_com);
    }
  }
  prod_ene_inelastic.clear();

  if( mt_elastic > 0 )
  {
    if( elastic_flg == 0 ) //coherent
    {
      generate_coherent_elastic_scatter_data();
    }
    else if( elastic_flg == 1 ) //incoherent
    {
      generate_incoherent_elastic_scatter_data();
    }
    else if( elastic_flg == 2 ) //mixed (coherent and incoherent)
    {
      generate_coherent_elastic_scatter_data();
      generate_incoherent_elastic_scatter_data();
    }
  }

  generate_inelastic_scatter_data();

  modify_calc_data();

  //Comparing elastic scattering xs from ENDF and incoherent inelastic scattering xs from TSL
  comp_scat_xs_tot();


  aw0 = nucl_data_obj.get_general_data_obj().get_mass();
  tz  = nucl_data_obj.get_general_data_obj().get_temp() * boltzmann_const * unit_micro;

  calc_ace_header_file_data();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterAceDataGenerator::generate_coherent_elastic_scatter_data()
{
  vector<Real> xs_ene_coh = xs_data_elastic.get_xs_ene_data();
  vector<Real> xs_coh     = xs_data_elastic.get_xs_data();

  Real e_xs_pre, e_xs_cur;
  int  i_max = static_cast<int>(xs_ene_coh.size());
  e_xs_pre   = 0.0;
  for(int i=0; i<i_max; i++)
  {
    if( xs_ene_coh[i] > ene_max_th + min_ene_dif )
    {
      break;
    }

    e_xs_cur = xs_ene_coh[i] * xs_coh[i];
    if( fabs(e_xs_cur - e_xs_pre) > (e_xs_pre + 1.0)*1.0E-6 )
    {
      coh_elastic_ene_data.push_back(xs_ene_coh[i]);
      coh_elastic_e_xs_data.push_back(e_xs_cur);
      e_xs_pre = e_xs_cur;
    }
  }
  xs_ene_coh.clear();
  xs_coh.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterAceDataGenerator::generate_incoherent_elastic_scatter_data()
{
  CrossSectionDataContainer        xs_data_incoh         = xs_data_elastic;
  ProductDistributionDataContainer prod_distr_data_incoh = prod_distr_data_elastic;
  if( elastic_flg == 2 )
  {
    int mt_incoh = mt_elastic+1;
    xs_data_incoh
      = nucl_data_obj.get_nucl_reaction_data_obj().get_xs_data_obj(mt_incoh);
    prod_distr_data_incoh
      = nucl_data_obj.get_nucl_reaction_data_obj().get_product_distr_data_obj(mt_incoh);
  }

  vector<Real>    xs_ene_incoh   = xs_data_incoh.get_xs_ene_data();
  vector<Real>    xs_incoh       = xs_data_incoh.get_xs_data();
  vector<Integer> xs_int_incoh   = xs_data_incoh.get_xs_int_data();
  vector<Integer> xs_range_incoh = xs_data_incoh.get_xs_range_data();

  incoh_elastic_ene_data   = prod_distr_data_incoh.get_incident_ene();
  incoh_elastic_scat_angle = prod_distr_data_incoh.get_incoherent_elastic_scat_angle();

  int i_max = static_cast<int>(incoh_elastic_ene_data.size());
  incoh_elastic_xs_data.resize(i_max);

  vector<int> pos_vec;
  for(int i=0; i<i_max; i++)
  {
    if( incoh_elastic_ene_data[i] > ene_max_th + min_ene_dif )
    {
      break;
    }

    pos_vec.push_back(i);

    //Calculate elastic scattering xs at E=incoh_elastic_ene_data[i]
    ti_obj.interpolation_tab1( incoh_elastic_ene_data[i], incoh_elastic_xs_data[i],
                               xs_range_incoh, xs_int_incoh, xs_ene_incoh, xs_incoh );
  }
  xs_ene_incoh.clear();
  xs_incoh.clear();
  xs_int_incoh.clear();
  xs_range_incoh.clear();

  if( i_max != static_cast<int>(pos_vec.size()) )
  {
    remove_unnecessary_energy_grid_incoherent_elastic_data(pos_vec);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterAceDataGenerator::remove_unnecessary_energy_grid_incoherent_elastic_data
                                       (vector<int>& pos_vec)
{
  vector<Real>          incoh_elastic_ene_data_new, incoh_elastic_xs_data_new;
  vector<vector<Real> > incoh_elastic_scat_angle_new;

  int i_max = static_cast<int>(pos_vec.size());
  incoh_elastic_ene_data_new.resize(i_max);
  incoh_elastic_xs_data_new.resize(i_max);
  incoh_elastic_scat_angle_new.resize(i_max);

  for(int i=0; i<i_max; i++)
  {
    incoh_elastic_ene_data_new[i]   = incoh_elastic_ene_data[pos_vec[i]];
    incoh_elastic_xs_data_new[i]    = incoh_elastic_xs_data[pos_vec[i]];
    incoh_elastic_scat_angle_new[i] = incoh_elastic_scat_angle[pos_vec[i]]; 
  }

  incoh_elastic_ene_data   = incoh_elastic_ene_data_new;
  incoh_elastic_xs_data    = incoh_elastic_xs_data_new;
  incoh_elastic_scat_angle = incoh_elastic_scat_angle_new;

  incoh_elastic_ene_data_new.clear();
  incoh_elastic_xs_data_new.clear();
  clr_obj.clear_vec_array2_real(incoh_elastic_scat_angle_new);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterAceDataGenerator::generate_inelastic_scatter_data()
{
  vector<Real8>                  weight_vec = set_weight();
  vector<Real>                   xs_ene_inelastic, xs_inelastic;
  vector<Integer>                xs_int_inelastic, xs_range_inelastic;
  vector<vector<Real> >          second_ene, scat_xs_integrate;
  vector<vector<vector<Real> > > scat_xs_weight;

  inelastic_ene_data = prod_distr_data_inelastic.get_incident_ene(); 

  xs_ene_inelastic   = xs_data_inelastic.get_xs_ene_data();
  xs_inelastic       = xs_data_inelastic.get_xs_data();
  xs_int_inelastic   = xs_data_inelastic.get_xs_int_data();
  xs_range_inelastic = xs_data_inelastic.get_xs_range_data();
  second_ene         = prod_distr_data_inelastic.get_second_ene();
  scat_xs_integrate  = prod_distr_data_inelastic.get_incoherent_inelastic_scat_xs_integrate();
  scat_xs_weight     = prod_distr_data_inelastic.get_incoherent_inelastic_scat_xs_weight();

  int  i_max = static_cast<int>(inelastic_ene_data.size());
  inelastic_xs_data.resize(i_max);
  inelastic_second_ene_cal.resize(i_max);
  inelastic_weight.resize(i_max);
  inelastic_scat_xs_weight.resize(i_max);
  if( opt_weight > 1 )
  {
    inelastic_scat_xs_int_cal.resize(i_max);
  }

  if( i_max > 0 )
  {
    Real e_min = 1.0E-6 + 1.0E-12; //eV
    if( inelastic_ene_data[0] < e_min )
    {
      inelastic_ene_data[0] = e_min; 
    }
  }

  vector<int>  pos_vec;
  for(int i=0; i<i_max; i++)
  {
    if( inelastic_ene_data[i] > ene_max_th + min_ene_dif )
    {
      break;
    }
    else if( static_cast<int>(second_ene[i].size()) < 2 )
    {
      continue;
    }

    pos_vec.push_back(i);
    
    //Calculate inelastic scattering xs at E=inelastic_ene_data[i]
    ti_obj.interpolation_tab1( inelastic_ene_data[i], inelastic_xs_data[i],
                               xs_range_inelastic, xs_int_inelastic, xs_ene_inelastic, xs_inelastic );

    //Calculate integrate data of incoherent inelastic scattering xs
    calc_second_energy_data(i, weight_vec, second_ene[i], scat_xs_integrate[i], scat_xs_weight[i]);
    
    //Normarize for tabulated distribution
    if( opt_weight > 1 )
    {
      Real weight_tot = 0.0;
      int j_max = static_cast<int>(inelastic_second_ene_cal[i].size());
      for(int j=0; j<j_max; j++)
      {
        weight_tot             += inelastic_weight[i][j];
        inelastic_weight[i][j]  = weight_tot;
      }

      for(int j=0; j<j_max; j++)
      {
        inelastic_scat_xs_int_cal[i][j] /= weight_tot;
        inelastic_weight[i][j]          /= weight_tot;
      }
    }
  }
  xs_ene_inelastic.clear();
  xs_inelastic.clear();
  xs_int_inelastic.clear();
  xs_range_inelastic.clear();
  clr_obj.clear_vec_array2_real(second_ene);
  clr_obj.clear_vec_array2_real(scat_xs_integrate);
  clr_obj.clear_vec_array3_real(scat_xs_weight);

  if( i_max != static_cast<int>(pos_vec.size()) )
  {
    remove_unnecessary_energy_grid_inelastic_data(pos_vec);
  }

  //For debug
  //if( opt_weight > 1 )
  //{
  //  cout << "generate_inelastic_scatter_data()" << endl;
  //  cout << endl;
  //  output_inelastic_ene_out_grid();
  //  cout << endl;
  //  cout << "======================================================================" << endl;
  //  cout << endl;
  //}
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<Real8> ThermalScatterAceDataGenerator::set_weight()
{
  vector<Real8> weight;
  weight.resize(bin_no_int);

  Real8 weight_ori = 1.0;
  if( opt_weight == 0 )
  {
    weight_ori = 1.0 / (static_cast<Real8>(bin_no - 3));
    for(int i=0; i<bin_no_int; i++)
    {
      if( i==0 || i==bin_no_int-1 )
      {
        weight[i] = 0.1*weight_ori;
      }
      else if( i==1 || i==bin_no_int-2 )
      {
        weight[i] = 0.4*weight_ori;
      }
      else
      {
        weight[i] = weight_ori;
      }
    }
  }
  else //opt_weight = 1 or 2
  {
    if( opt_weight == 1 )
    {
      weight_ori = 1.0 / (static_cast<Real8>(bin_no));
    }

    for(int i=0; i<bin_no_int; i++)
    {
      weight[i] = weight_ori;
    }
  }

  return weight;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterAceDataGenerator::calc_second_energy_data( int i, vector<Real8>& weight_vec,
                                       vector<Real>& second_ene, vector<Real>& scat_xs_integrate,
                                       vector<vector<Real> >& scat_xs_weight )
{
  int j_max = static_cast<int>(second_ene.size());
  if( j_max < 2 )
  {
    return;
  }
  
  //Declare variable and set initial value
  int    bin_count   = 0;
  int    bin_end_flg = 0;
  Real8  second_ene_pre, second_ene_cur, scat_xs_int_pre, scat_xs_int_cur,
         second_ene_dif, scat_xs_int_dif, second_ene_cal, scat_xs_int_cal, second_ene_ave,
         scat_xs_tot_part, scat_xs_tot, grall, scat_xs_tot_all;
  grall           = 0.0;
  scat_xs_tot     = 0.0;

  if( opt_weight <= 1 )
  {
    scat_xs_tot_all = weight_vec[bin_count];
  }
  else
  {
    scat_xs_tot_all = 1.0;
  }
  
  //modify the first and the last data
  int k_max = static_cast<int>(scat_xs_weight[0].size());
  for(int k=0; k<k_max; k++)
  {
    scat_xs_weight[0][k]          = scat_xs_weight[1][k];
    scat_xs_weight[j_max-1][k]    = scat_xs_weight[j_max-2][k];
  }

  int init_flg    = 0;
  second_ene_pre  = static_cast<Real8>(second_ene[0]);
  scat_xs_int_pre = static_cast<Real8>(scat_xs_integrate[0]);
  for(int j=1; j<j_max; j++)
  {
    second_ene_cur  = static_cast<Real8>(second_ene[j]);
    scat_xs_int_cur = static_cast<Real8>(scat_xs_integrate[j]);
    second_ene_dif  = second_ene_cur - second_ene_pre;
    scat_xs_int_dif = scat_xs_int_cur - scat_xs_int_pre;
    if( fabs(second_ene_dif) < fabs(min_ene_dif * second_ene_cur) ||
        fabs(second_ene_dif) < 1.0E-8 ) //1.0E-8eV -> 1.0E-14MeV
    {
      continue;
    }

    second_ene_cal = 0.0;
    while( second_ene_cal - second_ene_cur < -1.0*min_ene_dif )
    {
      scat_xs_tot_part = 0.5 * (scat_xs_int_cur + scat_xs_int_pre) * second_ene_dif;

      if( opt_weight <= 1 && j==j_max-1 && bin_count == bin_no_int-1 )
      {
        second_ene_cal = second_ene_cur;
        bin_count++;
      }
      else if( opt_weight > 1 && ( init_flg==0 || j==j_max-1 ) )
      {
        init_flg        = 1;
        second_ene_cal  = second_ene_cur;
        scat_xs_tot_all = scat_xs_tot + scat_xs_tot_part;
        bin_count++;
      }
      else
      {
        if( opt_weight > 1 )
        {
          if( scat_xs_tot + scat_xs_tot_part > 1.0E-6 )
          {
            scat_xs_tot_all = scat_xs_tot + scat_xs_tot_part;
          }
        }

        if( scat_xs_tot + scat_xs_tot_part < scat_xs_tot_all * 0.9999 )
        {
          scat_xs_tot += scat_xs_tot_part;
          grall += 0.5*(scat_xs_int_pre - scat_xs_int_dif*second_ene_pre/second_ene_dif)
                 * (second_ene_cur*second_ene_cur - second_ene_pre*second_ene_pre)
                 + third * (scat_xs_int_dif/second_ene_dif)
                 * ( second_ene_cur*second_ene_cur*second_ene_cur
                   - second_ene_pre*second_ene_pre*second_ene_pre );
          break;
        }
        else
        {
          bin_count++;
          if( scat_xs_tot + scat_xs_tot_part < scat_xs_tot_all * 1.0001 )
          {
            second_ene_cal = second_ene_cur;
          }
          else if( fabs(scat_xs_int_dif) > (scat_xs_int_cur + scat_xs_int_pre)*1.0E-5 )
          {
            Real8 grad     = scat_xs_int_dif / second_ene_dif;
            Real8 grad_inv = 1.0 / grad;
            Real8 disc     = (scat_xs_int_pre * grad_inv)*(scat_xs_int_pre * grad_inv)
                           + 2.0*(scat_xs_tot_all - scat_xs_tot)*grad_inv;
            if( disc < 0.0 )
            {
              disc *= -1.0;
            } 

            Real8 sign = 1.0;
            if( grad < 0.0 )
            {
              sign = -1.0;
            }
            second_ene_cal = second_ene_pre - (scat_xs_int_pre*grad_inv) + sign*sqrt(disc);
            if( second_ene_cal <= second_ene_pre || second_ene_cal > second_ene_cur )
            {
              output_error_calc_second_energy_data
                (i, j, j_max, second_ene_cal, second_ene_pre, second_ene_cur, 1);
            }
          }
          else
          {
            second_ene_cal = second_ene_pre + (scat_xs_tot_all - scat_xs_tot) / scat_xs_int_pre;
            if( second_ene_cal > second_ene_cur )
            {
              second_ene_cal = second_ene_cur;
            }
            else
            {
              if( second_ene_cal <= second_ene_pre )
              {
                output_error_calc_second_energy_data
                  (i, j, j_max, second_ene_cal, second_ene_pre, second_ene_cur, 2);
              }
            }
          }
        }
      }

      scat_xs_int_cal = scat_xs_int_pre
                      + scat_xs_int_dif*(second_ene_cal - second_ene_pre)/second_ene_dif;
      scat_xs_tot    += 0.5*(scat_xs_int_cal + scat_xs_int_pre) * (second_ene_cal - second_ene_pre);
      grall          += 0.5*(scat_xs_int_pre - scat_xs_int_dif*second_ene_pre/second_ene_dif)
                      * (second_ene_cal*second_ene_cal - second_ene_pre*second_ene_pre)
                      + third * (scat_xs_int_dif/second_ene_dif)
                      * ( second_ene_cal*second_ene_cal*second_ene_cal
                        - second_ene_pre*second_ene_pre*second_ene_pre );
      second_ene_ave  = grall / scat_xs_tot;

      //Copy calculation data to ACE data
      int  ele_no = j_max - 1;
      Real second_ene_tmp = static_cast<Real>(second_ene_ave);
      for(int k=1; k<j_max; k++)
      {
        if( second_ene_tmp < second_ene[k] - min_value )
        {
          ele_no = k;
          break;
        }
      }

      if( opt_weight > 1 )
      {
        inelastic_second_ene_cal[i].push_back(static_cast<Real>(second_ene_cal));
        inelastic_scat_xs_int_cal[i].push_back(static_cast<Real>(scat_xs_int_cal));
      }
      else
      {
        inelastic_second_ene_cal[i].push_back(second_ene_tmp);
      }

      Real coef_real = 1.0 / (second_ene[ele_no] - second_ene[ele_no-1]);
      if( opt_weight <= 1 )
      {
        coef_real *= second_ene_tmp - second_ene[ele_no-1];
      }
      else
      {
        coef_real *= second_ene_cal - second_ene[ele_no-1];
      }

      k_max = static_cast<int>(scat_xs_weight[j].size());
      vector<Real> xs_weight_tmp;
      xs_weight_tmp.resize(k_max);
      for(int k=0; k<k_max; k++)
      {
        xs_weight_tmp[k] = scat_xs_weight[ele_no-1][k]
                         + (scat_xs_weight[ele_no][k] - scat_xs_weight[ele_no-1][k])*coef_real;

        if( xs_weight_tmp[k] < -1.0 )
        {
          xs_weight_tmp[k] = -1.0;
        }
        else if( xs_weight_tmp[k] > 1.0 )
        {
          xs_weight_tmp[k] =  1.0;
        }
      }

      inelastic_scat_xs_weight[i].push_back(xs_weight_tmp);
      xs_weight_tmp.clear();

      inelastic_weight[i].push_back(static_cast<Real>(scat_xs_tot_all));

      if( (opt_weight <= 1 && bin_count == bin_no_int) || j+1 == j_max )
      {
        bin_end_flg = 1;
        break;
      }

      grall           = 0.0;
      scat_xs_tot     = 0.0;
      if( opt_weight <= 1 )
      {
        scat_xs_tot_all = weight_vec[bin_count];
      }
      else
      {
        scat_xs_tot_all = 1.0;
      }
      second_ene_pre  = second_ene_cal;
      scat_xs_int_pre = scat_xs_int_cal;
      second_ene_dif  = second_ene_cur - second_ene_pre;
      scat_xs_int_dif = scat_xs_int_cur - scat_xs_int_pre;
    }

    second_ene_pre  = second_ene_cur;
    scat_xs_int_pre = scat_xs_int_cur;
    if( bin_end_flg > 0 )
    {
      break;
    }
  }

  if( bin_end_flg == 0 )
  {
    string class_name = "ThermalScatterAceDataGenerator";
    string func_name  = "calc_second_energy_data()";

    ostringstream oss01, oss02, oss03;
    oss01 << i+1;
    oss02 << bin_no_int;
    oss03 << bin_count;
    string str_data01 = "Energy grid number                                  : " + oss01.str();
    string str_data02 = "Bin number for incoherent scattering in input       : " + oss02.str();
    string str_data03 = "Bin number for incoherent scattering in curret grid : " + oss03.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("Bin number for incoherent scattering in curret grid");
    err_com.push_back("is less than that in input.");
    err_com.push_back("The all zero data is added for dummy data.");
    err_com.push_back("The calculation results of the neutronics calculation");
    err_com.push_back("may not be appropriate.");
    err_com.push_back("To avoid this problem, please use more fine tolerance value.");
    err_obj.output_caution(class_name, func_name, err_com);

    int k_max = static_cast<int>(inelastic_scat_xs_weight[0][0].size());
    vector<Real> xs_weight_tmp;
    xs_weight_tmp.resize(k_max);
    for(int k=0; k<k_max; k++)
    {
      xs_weight_tmp[k] = 0.0;
    }

    for(int j=bin_count; j<bin_no_int; j++)
    {
      inelastic_second_ene_cal[i].push_back(0.0);
      inelastic_weight[i].push_back(0.0);
      inelastic_scat_xs_weight[i].push_back(xs_weight_tmp);

      if( opt_weight > 1 )
      {
        inelastic_scat_xs_int_cal[i].push_back(0.0);
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterAceDataGenerator::remove_unnecessary_energy_grid_inelastic_data(vector<int>& pos_vec)
{
  vector<Real>                   inelastic_ene_data_new, inelastic_xs_data_new;
  vector<vector<Real> >          inelastic_second_ene_cal_new, inelastic_scat_xs_int_cal_new,
                                 inelastic_weight_new;
  vector<vector<vector<Real> > > inelastic_scat_xs_weight_new;

  int i_max = static_cast<int>(pos_vec.size());
  int ele_no = static_cast<int>(inelastic_scat_xs_int_cal.size());

  inelastic_ene_data_new.resize(i_max);
  inelastic_xs_data_new.resize(i_max);
  inelastic_second_ene_cal_new.resize(i_max);
  inelastic_weight_new.resize(i_max);
  inelastic_scat_xs_weight_new.resize(i_max);

  if( ele_no > 0 )
  {
    inelastic_scat_xs_int_cal_new.resize(i_max);
  }

  for(int i=0; i<i_max; i++)
  {
    inelastic_ene_data_new[i]       = inelastic_ene_data[pos_vec[i]];
    inelastic_xs_data_new[i]        = inelastic_xs_data[pos_vec[i]];
    inelastic_second_ene_cal_new[i] = inelastic_second_ene_cal[pos_vec[i]];
    inelastic_weight_new[i]         = inelastic_weight[pos_vec[i]];
    inelastic_scat_xs_weight_new[i] = inelastic_scat_xs_weight[pos_vec[i]];

    if( ele_no > 0 )
    {
      inelastic_scat_xs_int_cal_new[i] = inelastic_scat_xs_int_cal[pos_vec[i]];
    }
  }

  inelastic_ene_data       = inelastic_ene_data_new;
  inelastic_xs_data        = inelastic_xs_data_new;
  inelastic_second_ene_cal = inelastic_second_ene_cal_new;
  inelastic_weight         = inelastic_weight_new;
  inelastic_scat_xs_weight = inelastic_scat_xs_weight_new;

  if( ele_no > 0 )
  {
    inelastic_scat_xs_int_cal = inelastic_scat_xs_int_cal_new;
  } 

  pos_vec.clear();
  inelastic_ene_data_new.clear();
  inelastic_xs_data_new.clear();
  clr_obj.clear_vec_array2_real(inelastic_second_ene_cal_new);
  clr_obj.clear_vec_array2_real(inelastic_scat_xs_int_cal_new);
  clr_obj.clear_vec_array2_real(inelastic_weight_new);
  clr_obj.clear_vec_array3_real(inelastic_scat_xs_weight_new);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterAceDataGenerator::output_error_calc_second_energy_data
                                       ( int i, int j, int j_max,
                                         Real8 second_ene_cal, Real8 second_ene_pre, Real8 second_ene_cur,
                                         int pos )
{
  string class_name = "ThermalScatterAceDataGenerator";
  string func_name  = "generate_inelastic_scatter_data()";
  ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07;
  oss01 << i+1;
  oss02 << j+1;
  oss03 << j_max;
  oss04 << second_ene_cal;
  oss05 << second_ene_pre;
  oss06 << second_ene_cur;
  oss07 << pos;

  string str_data01 = "Position i = " + oss01.str();
  string str_data02 = "Position j = " + oss02.str() + " / " + oss03.str();
  string str_data03 = "second_ene_cal value : " + oss04.str();
  string str_data04 = "Lower second energy  : " + oss05.str();
  string str_data05 = "Higher second energy : " + oss06.str();
  string str_data06 = "second_ene_cal value is out of range. (point " + oss07.str() + ")";

  vector<string> err_com;
  err_com.push_back(str_data01);
  err_com.push_back(str_data02);
  err_com.push_back(str_data03);
  err_com.push_back(str_data04);
  err_com.push_back(str_data05);
  err_com.push_back(str_data06);
  err_obj.output_runtime_error(class_name, func_name, err_com);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterAceDataGenerator::modify_calc_data()
{
  string        str_tmp;
  ostringstream oss01, oss02;
  title_data.resize(3);

  //Copy thermal_za_id_name and suffix_za_id
  int i_max = 6;
  str_tmp = thermal_za_id_name.substr(0,i_max);
  int str_length = static_cast<int>(str_tmp.length());
  if( str_length == 0 )
  {
    ostringstream oss;
    oss << nucl_data_obj.get_general_data_obj().get_izaid_ace();
    str_tmp    = oss.str();
    str_length = static_cast<int>(str_tmp.length());
  }

  for(int i=str_length; i<i_max; i++)
  {
    str_tmp = " " + str_tmp;
  }
  
  i_max = 3;
  if( mcnpx_mode_flg == 0 )
  {
    i_max = 2;
  }

  oss01.precision(i_max);
  oss01 << fixed << suffix_za_id;
  string str_za_id = oss01.str();
  if( static_cast<int>(str_za_id.find_first_of("0.")) == 0 )
  {
    str_za_id = str_za_id.substr(1);
  }
  else
  {
    str_tmp = str_tmp.substr(0,5);
  }

  if( mcnpx_mode_flg == 0 )
  {
    title_data[0] = str_tmp + str_za_id + "t";
  }
  else
  {
    title_data[0] = str_tmp + str_za_id + "nt ";
  }

  //Copy date
  str_tmp       = time_obj.get_current_date_no_slash();
  title_data[1] = "  " + str_tmp;

  //Copy material data
  mat = nucl_data_obj.get_general_data_obj().get_mat_no();
  oss02 << setw(4) << setiosflags(ios::right) << mat;
  title_data[2] = "   mat" + oss02.str();

  //Modify coherent elastic data
       i_max     = static_cast<int>(coh_elastic_ene_data.size());
  Real coef_real = unit_micro / static_cast<Real>(atom_no_th);
  for(int i=0; i<i_max; i++)
  {
    coh_elastic_ene_data[i]  *= unit_micro;
    coh_elastic_e_xs_data[i] *= coef_real;
  }

  //Modify incoherent elastic data
  i_max     = static_cast<int>(incoh_elastic_ene_data.size());
  coef_real = 1.0 / static_cast<Real>(atom_no_th);
  for(int i=0; i<i_max; i++)
  {
    incoh_elastic_ene_data[i] *= unit_micro;
    incoh_elastic_xs_data[i]  *= coef_real;
  }

  //Modify incoherent inelastic data
  i_max     = static_cast<int>(inelastic_ene_data.size());
  coef_real = 1.0 / static_cast<Real>(atom_no_th);
  for(int i=0; i<i_max; i++)
  {
    inelastic_ene_data[i] *= unit_micro;
    inelastic_xs_data[i]  *= coef_real;

    int j_max = static_cast<int>(inelastic_second_ene_cal[i].size());
    for(int j=0; j<j_max; j++)
    {
      inelastic_second_ene_cal[i][j] *= unit_micro;
      if( opt_weight > 1 )
      {
        inelastic_scat_xs_int_cal[i][j] *= unit_mega;
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterAceDataGenerator::calc_ace_header_file_data()
{
  idpni = 3;
  ifeng = 0;
  if( opt_weight == 0 )
  {
    ifeng = 1;
  }
  else if( opt_weight == 2 )
  {
    ifeng = 2;
  }

  Integer nea = 0;
  nie   = static_cast<Integer>(inelastic_ene_data.size());
  nee   = 0;
  if( static_cast<Integer>(coh_elastic_ene_data.size()) > 0 )
  {
    nee = static_cast<Integer>(coh_elastic_ene_data.size());
  }
  else if( static_cast<Integer>(incoh_elastic_ene_data.size()) > 0 )
  {
    nee = static_cast<Integer>(incoh_elastic_ene_data.size());

    string class_name = "ThermalScatterAceDataGenerator";
    string func_name  = "calc_ace_header_file_data()";
    nea = vec_size_check_obj.vec_size_check_array2_real(class_name, func_name, incoh_elastic_scat_angle);
  }
  itie  = 1;
  itix  = itie + 1 + nie;
  itxe  = itix + nie;
  itce  = 0;
  itcx  = 0;

  nieb  = bin_no;

  nil   = 0;
  idpnc = 0;
  ncl   = 0;
  if( nee != 0 )
  {
    idpnc =  4;
    ncl   = -1;
    if( static_cast<int>(incoh_elastic_scat_angle.size()) != 0 )
    {
      if( static_cast<int>(incoh_elastic_scat_angle[0].size()) > 0 )
      {
        idpnc = 3;
        ncl   = static_cast<int>(incoh_elastic_scat_angle[0].size()) - 1;
      }
    }
  }

  if( nie != 0 )
  {
    if( static_cast<int>(inelastic_scat_xs_weight[0].size()) > 0 )
    {
      nil = static_cast<int>(inelastic_scat_xs_weight[0][0].size());
    }
  }
  if( ifeng <= 1 )
  {
    nil--;
  }
  else
  {
    nil++;
  }

  len2 = itxe - 1;
  int i_max = static_cast<int>(inelastic_ene_data.size());
  for(int i=0; i<i_max; i++)
  {
    if( opt_weight <= 1 )
    {
      int j_max = static_cast<int>(inelastic_second_ene_cal[i].size());
      len2 += j_max; //inelastic_second_ene_cal
      for(int j=0; j<j_max; j++)
      {
        len2 += static_cast<Integer>(inelastic_scat_xs_weight[i][j].size());
      }
    }
    else
    {
      len2 += 2; //index, inelastic_second_ene_cal

      int j_max = static_cast<int>(inelastic_second_ene_cal[i].size());
      len2 += 3*j_max; //inelastic_second_ene_cal, inelastic_scat_xs_int, inelastic_weight
      for(int j=0; j<j_max; j++)
      {
        len2 += static_cast<Integer>(inelastic_scat_xs_weight[i][j].size());
      }
    }
  }

  //if( ifeng > 1 )
  //{
  //  len2 += 2*nie;
  //}
  if( nee > 0 )
  {
    itce = len2 + 1;
    itcx = itce + nee + 1;
    len2 = itcx + nee - 1;  
  }

  itca = 0;
  if( nee > 0 && nea > 0 )
  {
    itca = itcx + nee;
    len2 = itca + nee*nea - 1;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterAceDataGenerator::output_ace_data()
{
  output_ace_data_title();
  
  if( static_cast<int>(inelastic_ene_data.size()) > 0 )
  {
    output_ace_data_inelastic();
  }
  
  if( static_cast<int>(coh_elastic_ene_data.size()) > 0 )
  {
    output_ace_data_coherent_elastic();
  }
  else if( static_cast<int>(incoh_elastic_ene_data.size()) > 0 )
  {
    output_ace_data_incoherent_elastic();
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterAceDataGenerator::output_ace_data_title()
{
  calc_ace_header_file_data();

  cout << setiosflags(ios::right);
  cout << "1" << endl << endl << endl << endl << endl << endl << endl;
  cout << "                                      zaid " << title_data[0] << endl;
  cout << "                                       awr"  << setw(10) << aw0 << endl;
  cout << "                                      temp"  << setw(10)
                                                        << setiosflags(ios::scientific)
                                                        << tz << endl
                                                        << resetiosflags(ios::scientific);
  cout << "                                      date"  << title_data[1] << endl;
  cout << "                                       mat"  << title_data[2] << endl;
  cout << "      ***********************" << endl;
  cout << "      *                     *         len2" << setw(10) << len2  << endl;
  cout << "      *       thermal       *        idpni" << setw(10) << idpni << endl;
  cout << "      *                     *          nil" << setw(10) << nil   << endl;
  cout << "      *   ace format file   *         nieb" << setw(10) << nieb  << endl;
  cout << "      *                     *        idpnc" << setw(10) << idpnc << endl;
  cout << "      *     processed by    *          ncl" << setw(10) << ncl   << endl;
  cout << "      *                     *        ifeng" << setw(10) << ifeng << endl;
  cout << "      *        frendy       *" << endl;
  cout << "      *                     *         itie" << setw(10) << itie  << endl;
  cout << "      ***********************         itix" << setw(10) << itix  << endl;
  cout << "                                      itxe" << setw(10) << itxe  << endl;
  cout << "                                      itce" << setw(10) << itce  << endl;
  cout << "                                      itcx" << setw(10) << itcx  << endl;
  cout << "                                      itca" << setw(10) << itca  << endl;
  cout << "                                       nie" << setw(10) << nie   << endl;
  cout << "                                       nee" << setw(10) << nee   << endl;
  cout << endl << endl;
  cout << "hk---" << discriptive_data << endl;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterAceDataGenerator::output_ace_data_inelastic()
{
  //Print inelastic data
  cout << setiosflags(ios::right);

  Integer inelastic_data_no = 0;
  int i_max = static_cast<int>(inelastic_ene_data.size());
  for(int i=0; i<i_max; i++)
  {
    inelastic_data_no += static_cast<Integer>(inelastic_second_ene_cal.size())
                       + static_cast<Integer>(inelastic_scat_xs_int_cal.size())
                       + static_cast<Integer>(inelastic_weight.size());
    int j_max = static_cast<int>(inelastic_scat_xs_weight[i].size());
    for(int j=0; j<j_max; j++)
    {
      inelastic_data_no += static_cast<Integer>(inelastic_scat_xs_weight[i][j].size());
    }
  }
  
  i_max = static_cast<int>(inelastic_ene_data.size());
  int line_no = 0;
  for(int i=0; i<i_max; i++)
  {
    int int_val01 = static_cast<int>(inelastic_scat_xs_weight[0][0].size());
    int int_val02 = bin_no_int;
    if( opt_weight <= 1 )
    {
      int_val01++;
    }
    else
    {
      int_val01--;
      int_val02 = static_cast<int>(inelastic_data_no)*(i+1) / (int_val01 + 3);
    }
    int_val01 = int_val02 * ((int_val01 + 7)/8);
 
    if( i==0 )
    {
      cout << endl;
      cout << " inelastic data - equally probable angles" << endl;
      cout << "----------------------------------------"  << endl; 
      cout << endl;
      line_no += 4;
    }
    else if( line_no + int_val01 + 4 > 58 )
    {
      cout << "1" << endl;
      line_no = 1;
    }

    cout << endl;
    cout << "      incident energy = " << setw(12) << setiosflags(ios::scientific) << inelastic_ene_data[i]
         << "        cross section = " << inelastic_xs_data[i] << resetiosflags(ios::scientific) << endl;
    if( opt_weight <= 1 )
    {
      cout << endl;
      cout << "         exit energy     cosines" << endl;
      cout << "         -----------  ";
      cout << "--------------------------------------------------------------------------------" << endl;
    }
    else
    {
      cout << endl;
      cout << "         exit energy        pdf           cdf     cosines" << endl;
      cout << "         -----------  ----------   ------------  ";
      cout << "--------------------------------------------------------------------------------" << endl;
    }
    line_no += 4;

    for(int j=0; j<bin_no_int; j++)
    {
      if( opt_weight <= 1 )
      {
        cout << "       " << setw(12) << setiosflags(ios::scientific) << inelastic_second_ene_cal[i][j]
             << "  " << resetiosflags(ios::scientific);
        int lf_pos = 0;
        for(int k=0; k<static_cast<int>(inelastic_scat_xs_weight[i][j].size()); k++)
        {
          if( lf_pos >= 8 )
          {
            cout << endl << "                                               ";
            lf_pos = 0;
            line_no++;
          }
          cout << " " << setw(9) << inelastic_scat_xs_weight[i][j][k];
          lf_pos++;
        }
        cout << endl;
        line_no++;
      }
      else
      {
        cout << "       " << setw(12) << setiosflags(ios::scientific) << inelastic_second_ene_cal[i][j]
             << " " << setw(12) << inelastic_scat_xs_int_cal[i][j]
             << " " << setw(14) << inelastic_weight[i][j]
             << "  " << resetiosflags(ios::scientific);
        int lf_pos = 0;
        for(int k=0; k<static_cast<int>(inelastic_scat_xs_weight[i][j].size()); k++)
        {
          if( lf_pos >= 8 )
          {
            cout << endl << "                                               ";
            lf_pos = 0;
            line_no++;
          }
          cout << " " << setw(9) << inelastic_scat_xs_weight[i][j][k];
          lf_pos++;
        }
        cout << endl;
        line_no++;
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterAceDataGenerator::output_ace_data_coherent_elastic()
{
  //Print coherent elastic data
  cout << setiosflags(ios::right);
  
  //int i_max = static_cast<int>(coh_elastic_ene_data.size());
  cout << "1" << endl;
  cout << " coherent elastic data - bragg edges and cumulative intensity" << endl;
  cout << " ------------------------------------------------------------" << endl;

  int each_line_no =  4;
  int skip_no      = 50;
  int nee  = static_cast<int>(coh_elastic_ene_data.size());
  int ncol = (nee+49) / skip_no;
  int npg  = (ncol+3) / each_line_no;

  vector<Real> ene_vec, e_xs_vec;
  ene_vec.resize(each_line_no);
  e_xs_vec.resize(each_line_no);

  for(int i=0; i<npg; i++)
  {
    int pos = 1+200*(i);

    if( i > 0 )
    {
      cout << "1" << endl;
    }
    int mcol = ncol;
    if( mcol > each_line_no )
    {
      mcol = each_line_no;
    }
    ncol -= mcol;

    for(int j=0; j<mcol; j++)
    {
      cout << "         bragg edge     e*cross ";
    }
    cout << endl;

    for(int j=0; j<mcol; j++)
    {
      cout << "     i     energy       section ";
    }
    cout << endl;

    for(int j=0; j<mcol; j++)
    {
      cout << "                                ";
    }
    cout << endl;

    for(int j=0; j<each_line_no; j++)
    {
      ene_vec[0]  = 0.0;
      e_xs_vec[0] = 0.0;
    }

    int j_max  = skip_no;
    for(int j=0; j<j_max; j++)
    {
      ene_vec[0]  = coh_elastic_ene_data[pos];
      e_xs_vec[0] = coh_elastic_e_xs_data[pos];

      if( mcol > 1 )
      {
        ene_vec[1]  = coh_elastic_ene_data[pos+skip_no];
        e_xs_vec[1] = coh_elastic_e_xs_data[pos+skip_no];
        if( mcol > 2 )
        {
          ene_vec[2]  = coh_elastic_ene_data[pos+2*skip_no];
          e_xs_vec[2] = coh_elastic_e_xs_data[pos+2*skip_no];
          if( mcol > 2 )
          {
            ene_vec[3]  = coh_elastic_ene_data[pos+3*skip_no];
            e_xs_vec[3] = coh_elastic_e_xs_data[pos+3*skip_no];
          }
        }
      }

      string line_data;
      for(int k=0; k<mcol; k++)
      {
        ostringstream oss01, oss02, oss03;
        oss01.width(6);
        oss01 << setiosflags(ios::right) << pos;

        oss02.width(13);
        oss02.precision(4);
        oss02 << setiosflags(ios::scientific) << setiosflags(ios::right) << setiosflags(ios::showpoint)
              << ene_vec[k];

        oss03.width(13);
        oss03.precision(4);
        oss03 << setiosflags(ios::scientific) << setiosflags(ios::right) << setiosflags(ios::showpoint)
              << e_xs_vec[k];

        line_data = line_data + oss01.str() + oss02.str() + oss03.str();
      }
      pos++;

      if( i >= npg-1 )
      {
        if( pos + (mcol-1)*skip_no > nee )
        {
          mcol--;
        }
        if( mcol == 0 )
        {
          break;
        }
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterAceDataGenerator::output_ace_data_incoherent_elastic()
{
  //Print incoherent elastic data
  cout << setiosflags(ios::right);

  cout << "1" << endl;
  cout << " incoherent elastic data - equally probable angles" << endl;
  cout << " -------------------------------------------------" << endl << endl;
  cout << endl;
  cout << "         incident         cross" << endl;
  cout << "    i     energy         section                         angles" << endl;
  int line_no = 7;

  int int_val = static_cast<int>(incoh_elastic_scat_angle[0].size());
      int_val = (int_val + 8) / 9;

  int i_max = static_cast<int>(incoh_elastic_ene_data.size());
  for(int i=0; i<i_max; i++)
  {
    if( line_no + int_val > 58 )
    {
      cout << "1" << endl;
      cout << endl;
      cout << "         incident         cross" << endl;
      cout << "    i     energy         section                         angles" << endl;
      line_no = 4;
    }

    cout << "  "  << setw(3)  << i+1
         << " "   << setw(12) << setiosflags(ios::scientific) << incoh_elastic_ene_data[i]
         << "   " << setw(12) << setiosflags(ios::scientific) << incoh_elastic_xs_data[i]
         << "  "  << resetiosflags(ios::scientific); 
    int lf_pos = 0;
    for(int j=0; j<static_cast<int>(incoh_elastic_scat_angle[i].size()); j++)
    {
      if( lf_pos >= 8 )
      {
        cout << endl << "                                   ";
        lf_pos = 0;
        line_no++;
      }
      cout << " " << setw(9) << incoh_elastic_scat_angle[i][j];
      lf_pos++;
    }
    cout << endl;
    line_no++;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterAceDataGenerator::check_set_data()
{
  string class_name = "ThermalScatterAceDataGenerator";
  string func_name  = "check_set_data()";

  if( nucl_data_set_flg == 0 )
  {
    vector<string> err_com;
    err_com.push_back("The NuclearDataObject data is not set.");
    err_com.push_back("Please set the NuclearDataObject data using set_nucl_data_obj() function.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  if( temp_set_flg > 0 )
  {
    Real8 temp_ref = static_cast<Real8>(nucl_data_obj.get_general_data_obj().get_temp());
    Real8 temp_dif = (temp - temp_ref);
    if( temp_ref > min_value )
    {
      temp_dif /= temp_ref;
    }

    if( fabs(temp_dif) > 1.0E-5 )
    {
      ostringstream oss01, oss02;
      oss01 << temp;
      oss02 << temp_ref;

      string str_data01 = "Set temperature data                  : " + oss01.str();
      string str_data02 = "Temperature data in NuclearDataObject : " + oss02.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);

      if( fabs(temp_dif) > 1.0E-2 )
      {
        err_com.push_back("The set temperature data is not identical to temperature in NuclearDataObject.");
        err_com.push_back("Please check the set temperature data or NuclearDataObject data.");
        err_obj.output_runtime_error(class_name, func_name, err_com);
      }
      else
      {
        err_com.push_back("The difference between set temp. data and NuclearDataObject's temp.");
        err_com.push_back("is not larger than 1.0E-5.");
        err_com.push_back("The set temperature data may not be appropriate.");
        err_obj.output_caution(class_name, func_name, err_com);
      }
    }
  }

  if( mat_set_flg > 0 )
  {
    Integer mat_ref = nucl_data_obj.get_general_data_obj().get_mat_no();
    if( mat != mat_ref )
    {
      ostringstream oss01, oss02;
      oss01 << mat;
      oss02 << mat_ref;

      string str_data01 = "Set material number                  : " + oss01.str();
      string str_data02 = "Material number in NuclearDataObject : " + oss02.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back("The set material number is not identical to that in NuclearDataObject.");
      err_com.push_back("Please check the set material number or NuclearDataObject data.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }

  if( mt_inelastic > 0 )
  {
    xs_data_inelastic
      = nucl_data_obj.get_nucl_reaction_data_obj().get_xs_data_obj(mt_inelastic);
    prod_distr_data_inelastic
      = nucl_data_obj.get_nucl_reaction_data_obj().get_product_distr_data_obj(mt_inelastic);
  }
  else
  {
    ostringstream oss01;
    oss01 << mt_inelastic;

    string str_data01 = "MT number for incoherent inelastic scatter : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("The MT number for incoherent inelastic scatter must be larger than 0.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  if( mt_elastic > 0 )
  {
    xs_data_elastic
      = nucl_data_obj.get_nucl_reaction_data_obj().get_xs_data_obj(mt_elastic);
    prod_distr_data_elastic
      = nucl_data_obj.get_nucl_reaction_data_obj().get_product_distr_data_obj(mt_elastic);
  }

  if( elastic_flg != 0 && elastic_flg != 1 && elastic_flg != 2 )
  {
    ostringstream oss01;
    oss01 << elastic_flg;

    string str_data01 = "Elastic scattering type : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("The elastic scattering type is only available for");
    err_com.push_back("0 (coherent), 1 (incoherent), or 2 (mixed, coherent + incoherent).");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
  else if( mt_elastic > 0 )
  {
    int ielas_from_nucl = -1;
    int ref_frame_flg   = prod_distr_data_elastic.get_ref_frame_flg();
    if( ref_frame_flg == 7 ) //For coherent elastic scatter cross section
    {
      ielas_from_nucl = 0;
    }
    else if( ref_frame_flg == 6 ) //For incoherent elastic scatter cross section
    {
      ielas_from_nucl = 1;
    }

    if( ref_frame_flg == 7 && elastic_flg == 2 )
    {
      int mt_incoh = mt_elastic+1;
      int ref_frame_flg_incoh = nucl_data_obj.get_nucl_reaction_data_obj().get_product_distr_data_obj(mt_incoh).get_ref_frame_flg();
      if( ref_frame_flg_incoh == 6 )
      {
        ielas_from_nucl = 2;
      }
    }

    if( ielas_from_nucl != elastic_flg )
    {
      ostringstream oss01, oss02;
      oss01 << elastic_flg;
      oss02 << ielas_from_nucl;

      string str_data01 = "Elastic scattering type from input        : " + oss01.str();
      string str_data02 = "Elastic scattering type from nuclear data : " + oss02.str();
      string str_data03 = "(0:coherent, 1:incoherent, -1:unknown format)";

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back("");
      err_com.push_back("The elastic scattering type from input is not identical");
      err_com.push_back("to that from nuclear data.");
      err_com.push_back("The elastic scattering type from input data may be incorrect.");
      err_com.push_back("Please check the input data.");
      err_obj.output_caution(class_name, func_name, err_com);
    }
  }

  if( opt_weight != 0 && opt_weight != 1 && opt_weight != 2 )
  {
    ostringstream oss01;
    oss01 << opt_weight;

    string str_data01 = "Weighting option : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("The weighting option is only available for 0 (variable),");
    err_com.push_back("1 (constant) or 2 (tabulated).");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  if( atom_no_th <= 0 )
  {
    ostringstream oss01;
    oss01 << atom_no_th;

    string str_data01 = "Number of atom types in mixed moderator : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("The Number of atom types in mixed moderator must be larger than 0.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  if( static_cast<int>(mod_za.size()) > mod_za_no )
  {
    ostringstream oss01;
    oss01 << static_cast<int>(mod_za.size());

    string str_data01 = "Number of moderator component za value : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("The number of moderator component za value must be less than or equal to 3.");
    err_com.push_back("Please check the number of moderator component za value or set mod_za data.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
  else if( static_cast<int>(mod_za.size()) != mod_za_no )
  {
    int i_max = mod_za_no - static_cast<int>(mod_za.size());
    for(int i=0; i<i_max; i++)
    {
      mod_za.push_back(0);
    }
  }

  if( round(mod_za[0]/1000.0) != nucl_data_obj.get_general_data_obj().get_mat_no()/100 )
  {
    if( round(mod_za[0]/1000.0) < 100 )
    {
      ostringstream oss01, oss02;
      oss01 << nucl_data_obj.get_general_data_obj().get_mat_no()/100;
      oss02 << round(mod_za[0]/1000.0);

      string str_data01 = "  Proton number from nuclear data file      : " + oss01.str();
      string str_data02 = "  Proton number from moderator component za : " + oss02.str();

      vector<string> err_com;
      err_com.push_back("Proton number from nuclear data file is not identical to that from");
      err_com.push_back("moderator component za.");
      err_com.push_back("Please check your input file or nuclear data file.");
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }

  class_name.clear();
  func_name.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterAceDataGenerator::output_inelastic_ene_out_grid()
{
  int i_max = static_cast<int>(inelastic_second_ene_cal.size());
  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(inelastic_second_ene_cal[i].size());

    Real8 e_min = inelastic_second_ene_cal[i][0];
    Real8 e_max = inelastic_second_ene_cal[i][j_max-1];

    Real8 ene_dis_rela_min = 1.0E+10;
    Real8 ene_dis_rela_max = 0.0;
    Real8 ene_dis_abs_min  = 1.0E+10;
    Real8 ene_dis_abs_max  = 0.0;

    for(int j=1; j<j_max; j++)
    {
      Real8 diff_abs  = inelastic_second_ene_cal[i][j] - inelastic_second_ene_cal[i][j-1];
      Real8 diff_rela = diff_abs / (inelastic_second_ene_cal[i][j]);

      if( diff_rela > ene_dis_rela_max )
      {
        ene_dis_rela_max = diff_rela;
      }
      if( diff_rela < ene_dis_rela_min )
      {
        ene_dis_rela_min = diff_rela;
      }

      if( diff_abs > ene_dis_abs_max )
      {
        ene_dis_abs_max = diff_abs;
      }
      if( diff_abs < ene_dis_abs_min )
      {
        ene_dis_abs_min = diff_abs;
      }
    }

    cout.precision(8);
    cout.setf(ios::showpoint);
    cout.setf(ios::scientific);
    cout << "Ein " << inelastic_ene_data[i] << " : Eout-min " << e_min << " : Eout-max " << e_max
         << " : Eout-dis-min_abs "  << ene_dis_abs_min  << " : Eout-dis-max_abs "  << ene_dis_abs_max
         << " : Eout-dis-min_rela " << ene_dis_rela_min << " : Eout-dis-max_rela " << ene_dis_rela_max
         << " : Eout-no " << j_max;

    //cout << " : ";
    //for(int j=0; j<j_max; j++)
    //{
    //  cout << inelastic_second_ene_cal[i][j] << " ";
    //}
    cout << endl;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterAceDataGenerator::comp_scat_xs_tot()
{
  CrossSectionDataContainer xs_data_obj
                               = nucl_data_obj.get_nucl_reaction_data_obj().get_xs_data_obj(2);

  vector<Integer> int_vec_sc   = xs_data_obj.get_xs_int_data();
  vector<Integer> range_vec_sc = xs_data_obj.get_xs_range_data();
  vector<Real>    ene_vec_sc   = xs_data_obj.get_xs_ene_data();
  vector<Real>    xs_vec_sc    = xs_data_obj.get_xs_data();

  if( static_cast<int>(xs_vec_sc.size()) == 0 )
  {
    return;
  }


  int i_max  = static_cast<int>(inelastic_ene_data.size());
  if( i_max == 0 )
  {
    return;
  }

  int ele_no = 0;
  for(int i=i_max-1; i>=0; i--)
  {
    if( inelastic_xs_data[i] > min_sig_val * 1.1 )
    {
      ele_no = i;
      break;
    }
  }

  Real8 xs_sc  = 0.0;
  Real8 ene_sc = inelastic_ene_data[ele_no] * 1.0E+6;
  ti_obj.interpolation_tab1(ene_sc, xs_sc, range_vec_sc, int_vec_sc, ene_vec_sc, xs_vec_sc);

  Real8 dif_rela = fabs((xs_sc - inelastic_xs_data[ele_no])/inelastic_xs_data[ele_no]);
  if( dif_rela > 0.1 )
  {
    Real xs_ori      = inelastic_xs_data[ele_no] * static_cast<Real>(atom_no_th);
    Real atom_no_mod = 1.0;
    if( fabs(xs_sc) > min_value )
    {
      atom_no_mod = static_cast<Integer>(round(xs_ori / xs_sc));
    }
    Real xs_mod  = xs_ori / static_cast<Real>(atom_no_mod);
    Real dif_mod = fabs((xs_sc - xs_mod) / xs_mod);


    string class_name = "ThermalScatterAceDataGenerator";
    string func_name  = "comp_scat_xs_tot()";

    vector<string> err_com;
    err_com.push_back("The difference between elastic scattering cross section from ENDF file");
    err_com.push_back("and incoherent inelastic scattering cross section from S(a,b) data at");
    err_com.push_back("the miximum energy of incoherent inelastic scattering is larger than 10%.");
    err_com.push_back("The input option (atom_type_no or nmix for acer) or nuclear data may be");
    err_com.push_back("inappropriate.");
    err_com.push_back("");

    ostringstream oss01, oss02, oss03, oss04, oss05;
    oss01.precision(8);
    oss01.setf(ios::showpoint);
    oss01.setf(ios::scientific);
    oss02.precision(8);
    oss02.setf(ios::showpoint);
    oss02.setf(ios::scientific);
    oss03.precision(8);
    oss03.setf(ios::showpoint);
    oss03.setf(ios::scientific);
    oss04.precision(8);
    oss04.setf(ios::showpoint);
    oss04.setf(ios::scientific);
    oss05.precision(8);
    oss05.setf(ios::showpoint);
    oss05.setf(ios::scientific);
 
    oss01 << ene_sc;
    oss02 << inelastic_xs_data[ele_no];
    oss03 << xs_sc;
    oss04 << dif_rela;
    oss05 << inelastic_xs_data[ele_no] / xs_sc;

    string str_data01 = "  Maximum energy of incoherent inelastic scattering [eV] : " + oss01.str();
    string str_data02 = "  Incoherent inelastic scattering cross section          : " + oss02.str();
    string str_data03 = "  Elastic scattering cross section from ENDF file        : " + oss03.str();
    string str_data04 = "  Relative difference of scattering cross section        : " + oss04.str();
    string str_data05 = "  Incoherent inelastic scat XS / Elastic scat XS         : " + oss05.str();
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back(str_data05);

    if( fabs(xs_sc) > min_value && dif_mod < dif_rela )
    {
      ostringstream oss11, oss12;
      oss11 << atom_no_th;
      oss12 << atom_no_mod;
      string str_data11 = "  Original atom_type_no                                  : " + oss11.str();
      string str_data12 = "  Recommended atom_type_no                               : " + oss12.str();
      err_com.push_back("");
//      err_com.push_back("The atom_type_no is modified from original atom_type_no to recommended atom_type_no.");
//      err_com.push_back("The incoherent/coherent scattering cross sections are re-modified using recommended atom_type_no.");
      err_com.push_back(str_data11);
      err_com.push_back(str_data12);

//       modify_scat_xs(atom_no_mod);
    }

    err_obj.output_caution(class_name, func_name, err_com);
  } 
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterAceDataGenerator::modify_scat_xs(Integer atom_no_mod)
{
  Real coef_real = static_cast<Real>(atom_no_th) / static_cast<Real>(atom_no_mod);

  //Modify coherent elastic data
  int i_max = static_cast<int>(coh_elastic_e_xs_data.size());
  for(int i=0; i<i_max; i++)
  {
    coh_elastic_e_xs_data[i] *= coef_real;
  }

  //Modify incoherent elastic data
  i_max = static_cast<int>(incoh_elastic_xs_data.size());
  for(int i=0; i<i_max; i++)
  {
    incoh_elastic_xs_data[i]  *= coef_real;
  }

  //Modify incoherent inelastic data
  i_max = static_cast<int>(inelastic_xs_data.size());
  for(int i=0; i<i_max; i++)
  {
    inelastic_xs_data[i]  *= coef_real;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//Setter

void ThermalScatterAceDataGenerator::set_nucl_data_obj(NuclearDataObject& data_obj)
{
  gen_th_scat_data_flg = 0;
  nucl_data_set_flg    = 1;
  nucl_data_obj        = data_obj;
}

void ThermalScatterAceDataGenerator::set_mat(Integer int_val)
{
  gen_th_scat_data_flg = 0;
  mat_set_flg          = 1;
  mat                  = int_val;
}

void ThermalScatterAceDataGenerator::set_temp(Real real_val)
{
  gen_th_scat_data_flg = 0;
  temp_set_flg         = 1;
  temp                 = real_val;
}

void ThermalScatterAceDataGenerator::set_mt_inelastic(Integer int_val)
{
  gen_th_scat_data_flg = 0;
  mt_inelastic         = int_val;
}

void ThermalScatterAceDataGenerator::set_bin_no(Integer int_val)
{
  gen_th_scat_data_flg = 0;
  bin_no               = int_val;
  bin_no_int           = static_cast<int>(bin_no);
}

void ThermalScatterAceDataGenerator::set_mt_elastic(Integer int_val)
{
  gen_th_scat_data_flg = 0;
  mt_elastic           = int_val;
}

void ThermalScatterAceDataGenerator::set_elastic_flg(Integer int_val)
{
  gen_th_scat_data_flg = 0;
  elastic_flg          = int_val;
}

void ThermalScatterAceDataGenerator::set_atom_no_th(Integer int_val)
{
  gen_th_scat_data_flg = 0;
  atom_no_th           = int_val;
}

void ThermalScatterAceDataGenerator::set_opt_weight(Integer int_val)
{
  gen_th_scat_data_flg = 0;
  opt_weight           = int_val;
}

void ThermalScatterAceDataGenerator::set_suffix_za_id(Real real_val)
{
  gen_th_scat_data_flg = 0;
  suffix_za_id         = real_val;
}

void ThermalScatterAceDataGenerator::set_ene_max_th(Real real_val)
{
  gen_th_scat_data_flg = 0;
  ene_max_th           = real_val;
}

void ThermalScatterAceDataGenerator::set_zi_awr_pair( vector<Integer> int_vec_zi,
                                                      vector<Real>    real_vec_awr )
{
  if( static_cast<int>(int_vec_zi.size()) != static_cast<int>(real_vec_awr.size()) )
  {
    string class_name = "ThermalScatterAceDataGenerator";
    string func_name  = "set_zi_awr_pair(vector<Integer> int_vec_zi, vector<Real> real_vec_awr)";

    ostringstream oss01, oss02;
    oss01 << static_cast<int>(int_vec_zi.size());
    oss02 << static_cast<int>(real_vec_awr.size());

    string str_data01 = "Number of zi  array data : " + oss01.str();
    string str_data02 = "Number of awr array data : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("Number of zi array data and that of awr array data is not identical.");
    err_com.push_back("Please check the set data.");
    err_obj.output_runtime_error(class_name, func_name, err_com);   
  }

  int i_max = static_cast<int>(int_vec_zi.size());
  if( i_max > max_zi_awr_pair_no )
  {
    string class_name = "ThermalScatterAceDataGenerator";
    string func_name  = "set_zi_awr_pair(vector<Integer> int_vec_zi, vector<Real> real_vec_awr)";

    ostringstream oss01;
    oss01 << i_max;
    string str_data01 = "Number of zi and awr pair data : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    for(int i=0; i<i_max; i++)
    {
      ostringstream oss02, oss03, oss04;
      oss02 << i+1;
      oss03 << int_vec_zi[i];
      oss04 << real_vec_awr[i];
      string str_data02 = "  zi and awr data at " + oss02.str() + " / " + oss01.str() + " : "
                        + oss03.str() + ", " + oss04.str();
      if( i >= max_zi_awr_pair_no )
      {
        str_data02 + " * not used";
      }
      err_com.push_back(str_data02);
    }
    ostringstream oss05;
    oss05 << max_zi_awr_pair_no;
    string str_data03 = "Zi and awr data array must be less than or equal to " + oss05.str() + ".";
    err_com.push_back("So, some data in zi and awr pair is not used.");
    err_obj.output_caution(class_name, func_name, err_com);
  }

  zi_vec  = int_vec_zi;
  awr_vec = real_vec_awr;

  int_vec_zi.clear();
  real_vec_awr.clear();
}

void ThermalScatterAceDataGenerator::set_mod_za(vector<Integer> int_vec)
{
  gen_th_scat_data_flg = 0;
  mod_za = int_vec;
  int_vec.clear();
}

void ThermalScatterAceDataGenerator::set_mcnpx_mode_flg(Integer int_val)
{
  gen_th_scat_data_flg = 0;
  mcnpx_mode_flg       = int_val;
}

void ThermalScatterAceDataGenerator::set_discriptive_data(string str_data)
{
  gen_th_scat_data_flg = 0;
  discriptive_data     = str_data;
  str_data.clear();
}

void ThermalScatterAceDataGenerator::set_thermal_za_id_name(string str_data)
{
  gen_th_scat_data_flg = 0;
  thermal_za_id_name   = str_data;
  str_data.clear();
}


//////////////////////////////////////////////////////////////////////////////////////////////////////
//Getter
ThermalScatterAceDataObject ThermalScatterAceDataGenerator::get_ace_data_obj()
{
  generate_ace_data();

  ThermalScatterAceDataObject ace_data_obj;
  copy_thermal_scat_ace_data(ace_data_obj);

  return ace_data_obj;
}

NuclearDataObject ThermalScatterAceDataGenerator::get_nucl_data_obj()
{
  return nucl_data_obj;
}

Integer           ThermalScatterAceDataGenerator::get_mat()
{
  return mat;
}

Real              ThermalScatterAceDataGenerator::get_temp()
{
  return temp;
}

Integer           ThermalScatterAceDataGenerator::get_mt_inelastic()
{
  return mt_inelastic;
}

Integer           ThermalScatterAceDataGenerator::get_bin_no()
{
  return bin_no;
}

Integer           ThermalScatterAceDataGenerator::get_mt_elastic()
{
  return mt_elastic;
}

Integer           ThermalScatterAceDataGenerator::get_elastic_flg()
{
  return elastic_flg;
}

Integer           ThermalScatterAceDataGenerator::get_atom_no_th()
{
  return atom_no_th;
}

Integer           ThermalScatterAceDataGenerator::get_opt_weight()
{
  return opt_weight;
}

Real              ThermalScatterAceDataGenerator::get_suffix_za_id()
{
  return suffix_za_id;
}

Real              ThermalScatterAceDataGenerator::get_ene_max_th()
{
  return ene_max_th;
}

vector<Integer>   ThermalScatterAceDataGenerator::get_zi_vec()
{
  return zi_vec;
}

vector<Real>      ThermalScatterAceDataGenerator::get_awr_vec()
{
  return awr_vec;
}

vector<Integer>   ThermalScatterAceDataGenerator::get_mod_za()
{
  return mod_za;
}


Integer           ThermalScatterAceDataGenerator::get_mcnpx_mode_flg()
{
  return mcnpx_mode_flg;
}

string            ThermalScatterAceDataGenerator::get_discriptive_data()
{
  return discriptive_data;
}

string            ThermalScatterAceDataGenerator::get_thermal_za_id_name()
{
  return thermal_za_id_name;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

