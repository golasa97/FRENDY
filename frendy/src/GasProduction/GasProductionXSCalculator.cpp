#include "GasProduction/GasProductionXSCalculator.hpp"

using namespace frendy;

//constructor
GasProductionXSCalculator::GasProductionXSCalculator(void)
{
  clear();
}

//destructor
GasProductionXSCalculator::~GasProductionXSCalculator(void)
{
  clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void GasProductionXSCalculator::clear()
{
  write_gas_no_flg           = 0;

  calc_gas_production_xs_flg = 0;
  nucl_data_ori_set_flg      = 0;
  nucl_data_dop_set_flg      = 0;

  nucl_data_obj_ori.clear();
  nucl_data_obj_dop.clear();

  xs_gas_any_flg = 0;
  xs_gas_tot_flg.clear();
  xs_gas_each_flg.clear();

  lib_format                  = 0;
  ene_max_reaction_type       = 0;
  min_threshold_reaction_type = 0;
  ene_max                     = 0.0;
  min_threshold_ene           = 0.0;

  base_grid.clear();
  clr_obj.clear_vec_array2_real(gas_prod_xs_data);

  mt_p_min   = mt_p_min_endf6;
  mt_p_max   = mt_p_max_endf6;
  mt_d_min   = mt_d_min_endf6;
  mt_d_max   = mt_d_max_endf6;
  mt_t_min   = mt_t_min_endf6;
  mt_t_max   = mt_t_max_endf6;
  mt_he3_min = mt_he3_min_endf6;
  mt_he3_max = mt_he3_max_endf6;
  mt_a_min   = mt_a_min_endf6;
  mt_a_max   = mt_a_max_endf6;

  mt_tot    =   1;
  mt_ela    =   2;
  mt_nonela =   3;
  mt_n      =   4;
  mt_any    =   5;
  mt_cont   =  10;
  mt_2nd    =  11;
  mt_2n     =  16;
  mt_3n     =  17;
  mt_f_tot  =  18;
  mt_f      =  19;
  mt_nf     =  20;
  mt_2nf    =  21;
  mt_na     =  22;
  mt_n3a    =  23;
  mt_2na    =  24;
  mt_3na    =  25;
  mt_abs    =  27;
  mt_np     =  28;
  mt_n2a    =  29;
  mt_2n2a   =  30;
  mt_nd     =  32;
  mt_nt     =  33;
  mt_nhe    =  34;
  mt_nd2a   =  35;
  mt_nt2a   =  36;
  mt_4n     =  37;
  mt_3nf    =  38;
  mt_2np    =  41;
  mt_3np    =  42;
  mt_n2p    =  44;
  mt_npa    =  45;
  mt_n0     =  50;
  mt_nc     =  91;
  mt_dis    = 101;
  mt_gam    = 102;
  mt_p      = 103;
  mt_d      = 104;
  mt_t      = 105;
  mt_he     = 106;
  mt_a      = 107;
  mt_2a     = 108;
  mt_3a     = 109;
  mt_2p     = 111;
  mt_pa     = 112;
  mt_t2a    = 113;
  mt_d2a    = 114;
  mt_pd     = 115;
  mt_pt     = 116;
  mt_da     = 117;
  mt_reso   = 151;
  mt_5n     = 152;
  mt_6n     = 153;
  mt_2nt    = 154;
  mt_ta     = 155;
  mt_4np    = 156;
  mt_3nd    = 157;
  mt_nda    = 158;
  mt_2npa   = 159;
  mt_7n     = 160;
  mt_8n     = 161;
  mt_5np    = 162;
  mt_6np    = 163;
  mt_7np    = 164;
  mt_4na    = 165;
  mt_5na    = 166;
  mt_6na    = 167;
  mt_7na    = 168;
  mt_4nd    = 169;
  mt_5nd    = 170;
  mt_6nd    = 171;
  mt_3nt    = 172;
  mt_4nt    = 173;
  mt_5nt    = 174;
  mt_6nt    = 175;
  mt_2nhe   = 176;
  mt_3nhe   = 177;
  mt_4nhe   = 178;
  mt_3n2p   = 179;
  mt_3n2a   = 180;
  mt_3npa   = 181;
  mt_dt     = 182;
  mt_npd    = 183;
  mt_npt    = 184;
  mt_ndt    = 185;
  mt_nphe   = 186;
  mt_ndhe   = 187;
  mt_nthe   = 188;
  mt_nta    = 189;
  mt_2n2p   = 190;
  mt_phe    = 191;
  mt_dhe    = 192;
  mt_ahe    = 193;
  mt_4n2p   = 194;
  mt_4n2a   = 195;
  mt_4npa   = 196;
  mt_3p     = 197;
  mt_n3p    = 198;
  mt_3n2pa  = 199;
  mt_5n2p   = 200;
  mt_xn     = 201;
  mt_xgam   = 202;
  mt_xp     = 203;
  mt_xd     = 204;
  mt_xt     = 205;
  mt_xhe    = 206;
  mt_xa     = 207;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void GasProductionXSCalculator::calc_gas_production_xs()
{
  if( calc_gas_production_xs_flg != 0 )
  {
    return;
  }
  calc_gas_production_xs_flg = 1;

  check_set_data();

  if( check_xs_data() < 0 )
  {
    return;
  }

  set_reaction_type();

  check_reaction_type();

  search_min_threshold_ene();
  modify_base_grid();

  calc_gas_production_reaction_xs();

  add_gas_prod_xs_to_nuclear_data_obj();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void GasProductionXSCalculator::check_set_data()
{
  if( nucl_data_ori_set_flg == 0 )
  {
    string class_name = "GasProductionXSCalculator";
    string func_name  = "check_set_data()";

    vector<string> err_com;
    err_com.push_back("There is no NuclearDataObject for original nuclear data.");
    err_com.push_back("Please set nuclear data object using set_nucl_data_obj_ori function.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  if( nucl_data_dop_set_flg == 0 )
  {
    string class_name = "GasProductionXSCalculator";
    string func_name  = "check_set_data()";

    vector<string> err_com;
    err_com.push_back("There is no NuclearDataObject for Doppler broadened nuclear data.");
    err_com.push_back("Please set nuclear data object using set_nucl_data_obj_dop function.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Integer GasProductionXSCalculator::check_xs_data()
{
  int no_xs_data_flg = -1;

  vector<CrossSectionDataContainer> xs_data_obj;
  xs_data_obj = nucl_data_obj_dop.get_nucl_reaction_data_obj().get_xs_data_obj_assigned();

  if( static_cast<int>(xs_data_obj.size()) > 0 )
  {
    no_xs_data_flg = 1;
  }
  else
  {
    string class_name = "GasProductionXSCalculator";
    string func_name  = "check_xs_data()";

    vector<string> err_com;
    err_com.push_back("There is no cross section data.");
    err_com.push_back("This nuclear data may not be appropriate.");
    err_com.push_back("Calculation of gas production cross section is skipped.");
    err_obj.output_caution(class_name, func_name, err_com);
  }
  vector<CrossSectionDataContainer>().swap(xs_data_obj);

  return no_xs_data_flg;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void GasProductionXSCalculator::set_reaction_type()
{
  lib_format = nucl_data_obj_ori.get_general_data_obj().get_lib_format();

  if( lib_format >= 6 )
  {
    mt_p_min   = mt_p_min_endf6;
    mt_p_max   = mt_p_max_endf6;
    mt_d_min   = mt_d_min_endf6;
    mt_d_max   = mt_d_max_endf6;
    mt_t_min   = mt_t_min_endf6;
    mt_t_max   = mt_t_max_endf6;
    mt_he3_min = mt_he3_min_endf6;
    mt_he3_max = mt_he3_max_endf6;
    mt_a_min   = mt_a_min_endf6;
    mt_a_max   = mt_a_max_endf6;
  }
  else
  {
    string class_name = "GasProductionXSCalculator";
    string func_name  = "set_reaction_type()";

    ostringstream oss01;
    oss01 << lib_format;
    string str_data01 = "Library format for original nuclear data : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("The library format is not equal to 6.");
    err_com.push_back("MT number of (n,p), (n,d), (n, t), (n,He3), and (n,alpha) are modified");
    err_com.push_back("from MT=600-849 to MT=700-798.");
    err_com.push_back("This modification affects the processing results and the processing");
    err_com.push_back("results may not be correct.");
    err_com.push_back("Please check the processing results.");
    err_obj.output_caution(class_name, func_name, err_com);

    mt_p_min   = mt_p_min_endf5;
    mt_p_max   = mt_p_max_endf5;
    mt_d_min   = mt_d_min_endf5;
    mt_d_max   = mt_d_max_endf5;
    mt_t_min   = mt_t_min_endf5;
    mt_t_max   = mt_t_max_endf5;
    mt_he3_min = mt_he3_min_endf5;
    mt_he3_max = mt_he3_max_endf5;
    mt_a_min   = mt_a_min_endf5;
    mt_a_max   = mt_a_max_endf5;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void GasProductionXSCalculator::check_reaction_type()
{
  vector<Integer>                          reaction_type_list;
  vector<CrossSectionDataContainer>        xs_data_obj;
  vector<ProductDistributionDataContainer> prod_distr_data_obj;

  reaction_type_list  = nucl_data_obj_dop.get_nucl_reaction_data_obj().get_reaction_type();
  xs_data_obj         = nucl_data_obj_dop.get_nucl_reaction_data_obj().get_xs_data_obj();

  prod_distr_data_obj = nucl_data_obj_ori.get_nucl_reaction_data_obj().get_product_distr_data_obj();
  
  xs_gas_any_flg = 0;
  xs_gas_tot_flg.resize(xs_gas_no);
  xs_gas_each_flg.resize(xs_gas_no);
  for(int i=0; i<xs_gas_no; i++)
  {
    xs_gas_tot_flg[i]  = 0;
    xs_gas_each_flg[i] = 0;
  }

  int i_max = static_cast<int>(reaction_type_list.size());
  for(int i=0; i<i_max; i++)
  {
    if( reaction_type_list[i] == mt_any )
    {
      for(int j=0; j<static_cast<int>(prod_distr_data_obj.size()); j++)
      {
        if( prod_distr_data_obj[j].get_reaction_type() == mt_any )
        {
          if( static_cast<int>(prod_distr_data_obj[j].get_mat_data_product().size()) > 0 )
          {
            xs_gas_any_flg = 1;
          }
          break;
        }
      }
    }

    if( reaction_type_list[i] == mt_p && xs_data_obj[i].get_reaction_type() == mt_p )
    {
      xs_gas_tot_flg[xs_gas_p] = 1;
    }
    else if( reaction_type_list[i] == mt_d && xs_data_obj[i].get_reaction_type() == mt_d )
    {
      xs_gas_tot_flg[xs_gas_d] = 1;
    }
    else if( reaction_type_list[i] == mt_t && xs_data_obj[i].get_reaction_type() == mt_t )
    {
      xs_gas_tot_flg[xs_gas_t] = 1;
    }
    else if( reaction_type_list[i] == mt_he && xs_data_obj[i].get_reaction_type() == mt_he )
    {
      xs_gas_tot_flg[xs_gas_he3] = 1;
    }
    else if( reaction_type_list[i] == mt_a && xs_data_obj[i].get_reaction_type() == mt_a )
    {
      xs_gas_tot_flg[xs_gas_a] = 1;
    }
    else if( reaction_type_list[i] >= mt_p_min && reaction_type_list[i] <= mt_p_max )
    {
      if( reaction_type_list[i] == xs_data_obj[i].get_reaction_type() )
      {
        xs_gas_each_flg[xs_gas_p] = 1;
      }
    }
    else if( reaction_type_list[i] >= mt_d_min && reaction_type_list[i] <= mt_d_max )
    {
      if( reaction_type_list[i] == xs_data_obj[i].get_reaction_type() )
      {
        xs_gas_each_flg[xs_gas_d] = 1;
      }
    }
    else if( reaction_type_list[i] >= mt_t_min && reaction_type_list[i] <= mt_t_max )
    {
      if( reaction_type_list[i] == xs_data_obj[i].get_reaction_type() )
      {
        xs_gas_each_flg[xs_gas_t] = 1;
      }
    }
    else if( reaction_type_list[i] >= mt_he3_min && reaction_type_list[i] <= mt_he3_max )
    {
      if( reaction_type_list[i] == xs_data_obj[i].get_reaction_type() )
      {
        xs_gas_each_flg[xs_gas_he3] = 1;
      }
    }
    else if( reaction_type_list[i] >= mt_a_min && reaction_type_list[i] <= mt_a_max )
    {
      if( reaction_type_list[i] == xs_data_obj[i].get_reaction_type() )
      {
        xs_gas_each_flg[xs_gas_a] = 1;
      }
    }
  }

  reaction_type_list.clear();
  vector<CrossSectionDataContainer>().swap(xs_data_obj);
  vector<ProductDistributionDataContainer>().swap(prod_distr_data_obj);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void GasProductionXSCalculator::search_min_threshold_ene()
{
  vector<Integer>                   reaction_type_list;
  vector<CrossSectionDataContainer> xs_data_obj;

  reaction_type_list = nucl_data_obj_dop.get_nucl_reaction_data_obj().get_reaction_type();
  xs_data_obj        = nucl_data_obj_dop.get_nucl_reaction_data_obj().get_xs_data_obj();

  ene_max_reaction_type       = 0;
  min_threshold_reaction_type = 0;
  ene_max                     = 0.0;
  min_threshold_ene           = 1.0E+10;

  vector<Real> prod_no_vec;

  Integer gas_prod_flg      = 0;
  Integer mat_data          = static_cast<Integer>(round(nucl_data_obj_dop.get_general_data_obj().get_mat_data()));
  Integer incident_particle = nucl_data_obj_dop.get_general_data_obj().get_sub_lib_no() / 10;
  Integer complex_mat_data  = mat_data + incident_particle;

  int i_max = static_cast<int>(reaction_type_list.size());
  for(int i=0; i<i_max; i++)
  {
    if(xs_data_obj[i].get_reaction_type() != reaction_type_list[i])
    {
      continue;
    }

    if( reaction_type_list[i] == mt_tot )
    {
      base_grid = xs_data_obj[i].get_xs_ene_data();
    }
    else if( reaction_type_list[i] == mt_any && xs_gas_any_flg == 1 )
    {
      vector<Real> ene_vec = xs_data_obj[i].get_xs_ene_data();
      int          ene_no  = static_cast<int>(ene_vec.size());
      if( ene_vec[0] < min_threshold_ene )
      {
        min_threshold_reaction_type = reaction_type_list[i];
        min_threshold_ene           = ene_vec[0];
      }
      if( ene_vec[ene_no-1] > ene_max )
      {
        ene_max_reaction_type = reaction_type_list[i];
        ene_max               = ene_vec[ene_no-1];
      }
    }
    else
    {
      gas_prod_flg = check_gas_production_reaction_type
                       (reaction_type_list[i], complex_mat_data,
                        xs_data_obj[i].get_reaction_flg(), prod_no_vec);
      if( gas_prod_flg > 0 )
      {
        vector<Real> ene_vec = xs_data_obj[i].get_xs_ene_data();
        int          ene_no  = static_cast<int>(ene_vec.size());
        if( ene_vec[0] < min_threshold_ene )
        {
          min_threshold_reaction_type = reaction_type_list[i];
          min_threshold_ene           = ene_vec[0];
        }
        if( ene_vec[ene_no-1] > ene_max )
        {
          ene_max_reaction_type = reaction_type_list[i];
          ene_max               = ene_vec[ene_no-1];
        }
      }
    }
  }
  reaction_type_list.clear();
  vector<CrossSectionDataContainer>().swap(xs_data_obj);

  //Compar min_threshold_ene and ene_max to energy grid of total reaction
  int ene_no = static_cast<int>(base_grid.size());
  if( min_threshold_ene*(1.0+min_ene_dif) < base_grid[0] || ene_max*(1.0-min_ene_dif) > base_grid[ene_no-1] )
  {
    string class_name = "GasProductionXSCalculator";
    string func_name  = "search_min_threshold_ene";

    ostringstream oss01, oss02, oss03, oss04, oss05, oss06;
    oss01.precision(8);
    oss01.setf(ios::showpoint);
    oss01.setf(ios::scientific);
    oss03.precision(8);
    oss03.setf(ios::showpoint);
    oss03.setf(ios::scientific);
    oss05.precision(8);
    oss05.setf(ios::showpoint);
    oss05.setf(ios::scientific);
    oss06.precision(8);
    oss06.setf(ios::showpoint);
    oss06.setf(ios::scientific);

    oss01 << min_threshold_ene;
    oss02 << min_threshold_reaction_type;
    oss03 << ene_max;
    oss04 << ene_max_reaction_type;
    oss05 << base_grid[0];
    oss06 << base_grid[ene_no-1];

    string str_data01 = "Minimum threshold energy (reaction type) : " + oss01.str()
                      + "(" + oss02.str() + ")";
    string str_data02 = "Maximum energy (reaction type)           : " + oss03.str()
                      + "(" + oss04.str() + ")";
    string str_data03 = "Minimum energy of total xs               : " + oss05.str();
    string str_data04 = "Maximum energy of total xs               : " + oss06.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    if( min_threshold_ene*(1.0+min_ene_dif) < base_grid[0] )
    {
      err_com.push_back("The minimum threshold energy grid of gas production xs is less than");
      err_com.push_back("the minimum energy grid of total cross section.");
    }
    if( ene_max*(1.0-min_ene_dif) > base_grid[ene_no-1] )
    {
      err_com.push_back("The maximum energy grid of gas production xs is larger than that of");
      err_com.push_back("total cross section.");
    }
    err_com.push_back("The nuclear data may not be appropriate.");
    err_com.push_back("Please check the nuclear data object.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void GasProductionXSCalculator::modify_base_grid()
{
  vector<Real> ene_grid_new;

  int i_max = static_cast<int>(base_grid.size());
  for(int i=0; i<i_max; i++)
  {
    if( base_grid[i] > min_threshold_ene * (1.0 - min_ene_dif) )
    {
      ene_grid_new.push_back(base_grid[i]);
    }
  }

  base_grid = ene_grid_new;
  ene_grid_new.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void GasProductionXSCalculator::calc_gas_production_reaction_xs()
{
  int ene_no = static_cast<int>(base_grid.size());
  gas_prod_xs_data.resize(xs_gas_no);
  for(int i=0; i<xs_gas_no; i++)
  {
    gas_prod_xs_data[i].resize(ene_no);
    for(int j=0; j<ene_no; j++)
    {
      gas_prod_xs_data[i][j] = 0.0;
    }
  }

  vector<Integer>                   reaction_type_list;
  vector<CrossSectionDataContainer> xs_data_obj;
  NuclearReactionDataContainer      nucl_react_obj_ori;

  reaction_type_list = nucl_data_obj_dop.get_nucl_reaction_data_obj().get_reaction_type();
  xs_data_obj        = nucl_data_obj_dop.get_nucl_reaction_data_obj().get_xs_data_obj();
  nucl_react_obj_ori = nucl_data_obj_ori.get_nucl_reaction_data_obj();

  vector<Real> prod_no_vec;

  write_gas_no_flg = 1;
  if( write_gas_no_flg > 0 )
  {
    cout << " pendf mt  mt203  mt204  mt205  mt206  mt207" << endl;
    cout << " -------- ------ ------ ------ ------ ------" << endl;
  }

  Integer gas_prod_flg      = 0;
  Integer mat_data          = static_cast<Integer>(round(nucl_data_obj_dop.get_general_data_obj().get_mat_data()));
  Integer incident_particle = nucl_data_obj_dop.get_general_data_obj().get_sub_lib_no() / 10;
  Integer complex_mat_data  = mat_data + incident_particle;

  int i_max = static_cast<int>(reaction_type_list.size());
  for(int i=0; i<i_max; i++)
  {
    if(xs_data_obj[i].get_reaction_type() != reaction_type_list[i])
    {
      continue;
    }

    if( reaction_type_list[i] == mt_any && xs_gas_any_flg == 1 )
    {
      calc_gas_prod_xs_using_product_distr_data_object
        (reaction_type_list[i], nucl_react_obj_ori.get_xs_data_obj(reaction_type_list[i]), xs_data_obj[i]);
    }
    else
    {
      gas_prod_flg = check_gas_production_reaction_type
                       (reaction_type_list[i], complex_mat_data,
                        xs_data_obj[i].get_reaction_flg(), prod_no_vec);
      if( gas_prod_flg > 0 )
      {
        add_gas_prod_xs(nucl_react_obj_ori.get_xs_data_obj(reaction_type_list[i]),
                        xs_data_obj[i], prod_no_vec);
      }
    }
  }
  if( write_gas_no_flg > 0 )
  {
    cout << endl;
    write_gas_no_flg = 0;
  }

  reaction_type_list.clear();
  vector<CrossSectionDataContainer>().swap(xs_data_obj);
  nucl_react_obj_ori.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void GasProductionXSCalculator::calc_gas_prod_xs_using_product_distr_data_object
                                  (int react_no, CrossSectionDataContainer  xs_data_obj_ori, 
                                                 CrossSectionDataContainer& xs_data_obj)
{
  ProductDistributionDataContainer prod_distr_data_obj;
  prod_distr_data_obj = nucl_data_obj_ori.get_nucl_reaction_data_obj().get_product_distr_data_obj(react_no);

  vector<Real> mat_data_product = prod_distr_data_obj.get_mat_data_product();

  int j_max = static_cast<int>(mat_data_product.size());
  for(int j=0; j<j_max; j++)
  {
    Integer mad_data_product_int = static_cast<Integer>(round(mat_data_product[j]));

    if( mad_data_product_int == 1001 )
    {
      add_gas_prod_xs_using_product_distr_data_object
        (xs_gas_p, xs_data_obj_ori, xs_data_obj,
         prod_distr_data_obj.get_product_distr_range_data()[j],
         prod_distr_data_obj.get_product_distr_int_data()[j],
         prod_distr_data_obj.get_product_distr_ene_data()[j],
         prod_distr_data_obj.get_product_distr_data()[j]);
    }
    else if( mad_data_product_int == 1002 )
    {
      add_gas_prod_xs_using_product_distr_data_object
        (xs_gas_d, xs_data_obj_ori, xs_data_obj,
         prod_distr_data_obj.get_product_distr_range_data()[j],
         prod_distr_data_obj.get_product_distr_int_data()[j],
         prod_distr_data_obj.get_product_distr_ene_data()[j],
         prod_distr_data_obj.get_product_distr_data()[j]);
    }
    else if( mad_data_product_int == 1003 )
    {
      add_gas_prod_xs_using_product_distr_data_object
        (xs_gas_t, xs_data_obj_ori, xs_data_obj,
         prod_distr_data_obj.get_product_distr_range_data()[j],
         prod_distr_data_obj.get_product_distr_int_data()[j],
         prod_distr_data_obj.get_product_distr_ene_data()[j],
         prod_distr_data_obj.get_product_distr_data()[j]);
    }
    else if( mad_data_product_int == 2003 )
    {
      add_gas_prod_xs_using_product_distr_data_object
        (xs_gas_he3, xs_data_obj_ori, xs_data_obj,
         prod_distr_data_obj.get_product_distr_range_data()[j],
         prod_distr_data_obj.get_product_distr_int_data()[j],
         prod_distr_data_obj.get_product_distr_ene_data()[j],
         prod_distr_data_obj.get_product_distr_data()[j]);
    }
    else if( mad_data_product_int == 2004 )
    {
      add_gas_prod_xs_using_product_distr_data_object
        (xs_gas_a, xs_data_obj_ori, xs_data_obj,
         prod_distr_data_obj.get_product_distr_range_data()[j],
         prod_distr_data_obj.get_product_distr_int_data()[j],
         prod_distr_data_obj.get_product_distr_ene_data()[j],
         prod_distr_data_obj.get_product_distr_data()[j]);
    }
  }

  prod_distr_data_obj.clear();
  mat_data_product.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void GasProductionXSCalculator::add_gas_prod_xs_using_product_distr_data_object
                                  (int react_no, CrossSectionDataContainer& xs_data_obj_ori,
                                                 CrossSectionDataContainer& xs_data_obj,
                                   vector<Integer> prod_range_vec, vector<Integer> prod_int_vec, 
                                   vector<Real>    prod_ene_vec,   vector<Real>    prod_vec) 
{
  check_interpolation(xs_data_obj.get_reaction_type(), xs_data_obj.get_xs_int_data());

  vector<Real> xs_ene_vec = xs_data_obj.get_xs_ene_data();
  vector<Real> xs_vec     = xs_data_obj.get_xs_data();

  vector<Integer> xs_range_vec_ori = xs_data_obj_ori.get_xs_range_data();
  vector<Integer> xs_int_vec_ori   = xs_data_obj_ori.get_xs_int_data();
  vector<Real>    xs_ene_vec_ori   = xs_data_obj_ori.get_xs_ene_data();
  vector<Real>    xs_vec_ori       = xs_data_obj_ori.get_xs_data();

  int  ene_no      = static_cast<int>(base_grid.size());
  Real prod_no     = 0.0;
  Real xs_ori      = 0.0;
  Real xs_dop      = 0.0;
  Real min_ene_val = xs_ene_vec[0];
  for(int i=0; i<ene_no; i++)
  {
    if( base_grid[i] > min_ene_val * (1.0 - min_ene_dif) )
    {
      ti_obj.interpolation_tab1(base_grid[i], prod_no,
                                prod_range_vec, prod_int_vec, prod_ene_vec, prod_vec);
      ti_obj.interpolation_tab1(base_grid[i], xs_ori,
                                xs_range_vec_ori, xs_int_vec_ori, xs_ene_vec_ori, xs_vec_ori);
      ti_obj.interpolation_1d_in_range(int_lin_lin, base_grid[i], xs_dop, xs_ene_vec, xs_vec);

      if( xs_ori > min_value )
      {
        gas_prod_xs_data[react_no][i] += prod_no * xs_dop;
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void GasProductionXSCalculator::add_gas_prod_xs(CrossSectionDataContainer  xs_data_obj_ori,
                                                CrossSectionDataContainer& xs_data_obj,
                                                vector<Real>& prod_no_vec)
{
  check_interpolation(xs_data_obj.get_reaction_type(), xs_data_obj.get_xs_int_data());

  Integer mt_ori = xs_data_obj_ori.get_reaction_type();
  Integer mt_dop = xs_data_obj.get_reaction_type();

  vector<Real> xs_ene_vec = xs_data_obj.get_xs_ene_data();
  vector<Real> xs_vec     = xs_data_obj.get_xs_data();

  vector<Integer> xs_range_vec_ori = xs_data_obj_ori.get_xs_range_data();
  vector<Integer> xs_int_vec_ori   = xs_data_obj_ori.get_xs_int_data();
  vector<Real>    xs_ene_vec_ori   = xs_data_obj_ori.get_xs_ene_data();
  vector<Real>    xs_vec_ori       = xs_data_obj_ori.get_xs_data();

  int  ene_no      = static_cast<int>(base_grid.size());
  Real xs_ori      = 0.0;
  Real xs_dop      = 0.0;
  Real min_ene_val = xs_ene_vec[0];
  for(int i=0; i<xs_gas_no; i++)
  {
    if( prod_no_vec[i] > min_value )
    {
      for(int j=0; j<ene_no; j++)
      {
        if( base_grid[j] > min_ene_val * (1.0 - min_ene_dif) )
        {
          ti_obj.interpolation_1d_in_range(int_lin_lin, base_grid[j], xs_dop, xs_ene_vec, xs_vec);

          if( mt_ori == mt_dop )
          {
            ti_obj.interpolation_tab1(base_grid[j], xs_ori,
                                      xs_range_vec_ori, xs_int_vec_ori, xs_ene_vec_ori, xs_vec_ori);
            if( xs_ori > min_value )
            {
              gas_prod_xs_data[i][j] += prod_no_vec[i] * xs_dop;
            }
          }
          else
          {
            if( xs_dop > min_value )
            {
              gas_prod_xs_data[i][j] += prod_no_vec[i] * xs_dop;
            }
          }
        }
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void GasProductionXSCalculator::check_interpolation(Integer reaction_type, vector<Integer> xs_int_vec)
{
  int i_max = static_cast<int>(xs_int_vec.size());
  for(int i=0; i<i_max; i++)
  {
    if( xs_int_vec[i] != int_lin_lin )
    {
      string class_name = "GasProductionXSCalculator";
      string func_name  = "check_interpolation";

      ostringstream oss01, oss02, oss03, oss04;
      oss01 << reaction_type;
      oss02 << i+1;
      oss03 << i_max;
      oss04 << xs_int_vec[i];

      string str_data01 = "Reaction type      : " + oss01.str();
      string str_data02 = "Position           : " + oss02.str() + " / " + oss03.str();
      string str_data03 = "Interpolation type : " + oss04.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back("The linear-linear interpolation is only available.");
      err_com.push_back("Please check the nuclear data object or run the resonance reconstruction");
      err_com.push_back("and Doppler broadening before run this program.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Integer GasProductionXSCalculator::check_gas_production_reaction_type
                                     (Integer mt_no, Integer mat_data, Integer reaction_flg,
                                      vector<Real>& prod_no_vec)
{
  Integer gas_prod_flg = 0;

  prod_no_vec.clear();
  prod_no_vec.resize(xs_gas_no);
  for(int i=0; i<xs_gas_no; i++)
  {
    prod_no_vec[i] = 0.0;
  }

  check_production_reaction(mt_no, reaction_flg, prod_no_vec);

  check_residual_material(mt_no, mat_data, reaction_flg, prod_no_vec);

  for(int i=0; i<xs_gas_no; i++)
  {
    if(prod_no_vec[i] > 0.0)
    {
      gas_prod_flg = 1;
      break;
    }
  }

  if( write_gas_no_flg > 0 && gas_prod_flg > 0 )
  {
    cout << setw(8) << right << mt_no;
    for(int i=0; i<xs_gas_no; i++)
    {
      cout << setw(7) << right << static_cast<int>(round(prod_no_vec[i]));
    }
    cout << endl;
  }

  return gas_prod_flg;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void GasProductionXSCalculator::check_production_reaction(Integer mt_no, Integer reaction_flg,
                                                          vector<Real>& prod_no_vec)
{
  //For 1H (proton)
  if( mt_no == mt_np   || mt_no == mt_2np || mt_no == mt_3np  || mt_no == mt_npa  || mt_no == mt_pa  ||
      mt_no == mt_pd   || mt_no == mt_pt  || mt_no == mt_4np  || mt_no == mt_2npa || mt_no == mt_5np ||
      mt_no == mt_6np  || mt_no == mt_7np || mt_no == mt_3npa || mt_no == mt_npd  || mt_no == mt_npt ||
      mt_no == mt_nphe || mt_no == mt_phe || mt_no == mt_4npa )
  {
    prod_no_vec[xs_gas_p] += 1.0;
  }
  else if( mt_no == mt_n2p  || mt_no == mt_2p    || mt_no == mt_3n2p || mt_no == mt_2n2p ||
           mt_no == mt_4n2p || mt_no == mt_3n2pa || mt_no == mt_5n2p )
  {
    prod_no_vec[xs_gas_p] += 2.0;
  }
  else if( mt_no == mt_3p || mt_no == mt_n3p )
  {
    prod_no_vec[xs_gas_p] += 3.0;
  }
  else if( mt_no == mt_p || (xs_gas_tot_flg[xs_gas_p] == 0 && mt_no >= mt_p_min && mt_no <= mt_p_max) )
  {
    prod_no_vec[xs_gas_p] += 1.0;
  }
  else if( mt_no > mt_n0 && mt_no <= mt_nc )
  {
    if( reaction_flg == mt_np )
    {
      prod_no_vec[xs_gas_p] += 1.0;
    }
  }

  //For 2H (deutron)
  if( mt_no == mt_2nd || mt_no == mt_nd  || mt_no == mt_nd2a || mt_no == mt_d2a || mt_no == mt_pd   ||
      mt_no == mt_da  || mt_no == mt_3nd || mt_no == mt_nda  || mt_no == mt_4nd || mt_no == mt_5nd  ||
      mt_no == mt_6nd || mt_no == mt_dt  || mt_no == mt_npd  || mt_no == mt_ndt || mt_no == mt_ndhe ||
      mt_no == mt_dhe )
  {
    prod_no_vec[xs_gas_d] += 1.0;
  }
  else if( mt_no == mt_d || (xs_gas_tot_flg[xs_gas_d] == 0 && mt_no >= mt_d_min && mt_no <= mt_d_max) )
  {
    prod_no_vec[xs_gas_d] += 1.0;
  }
  else if( mt_no > mt_n0 && mt_no <= mt_nc )
  {
    if( reaction_flg == mt_nd || reaction_flg == mt_nd2a )
    {
      prod_no_vec[xs_gas_d] += 1.0;
    }
  }

  //For 3H (triton)
  if( mt_no == mt_nt || mt_no == mt_nt2a || mt_no == mt_t2a || mt_no == mt_pt   || mt_no == mt_2nt ||
      mt_no == mt_ta || mt_no == mt_3nt  || mt_no == mt_4nt || mt_no == mt_5nt  || mt_no == mt_6nt ||
      mt_no == mt_dt || mt_no == mt_npt  || mt_no == mt_ndt || mt_no == mt_nthe || mt_no == mt_nta )
  {
    prod_no_vec[xs_gas_t] += 1.0;
  }
  else if( mt_no == mt_t || (xs_gas_tot_flg[xs_gas_t] == 0 && mt_no >= mt_t_min && mt_no <= mt_t_max) )
  {
    prod_no_vec[xs_gas_t] += 1.0;
  }
  else if( mt_no > mt_n0 && mt_no <= mt_nc )
  {
    if( reaction_flg == mt_nt || reaction_flg == mt_nt2a )
    {
      prod_no_vec[xs_gas_t] += 1.0;
    }
  }

  //For He3
  if( mt_no == mt_nhe  || mt_no == mt_2nhe || mt_no == mt_3nhe || mt_no == mt_4nhe || mt_no == mt_nphe ||
      mt_no == mt_ndhe || mt_no == mt_nthe || mt_no == mt_phe  || mt_no == mt_dhe  || mt_no == mt_ahe )
  {
    prod_no_vec[xs_gas_he3] += 1.0;
  }
  else if( mt_no == mt_he || (xs_gas_tot_flg[xs_gas_he3] == 0 && mt_no >= mt_he3_min && mt_no <= mt_he3_max) )
  {
    prod_no_vec[xs_gas_he3] += 1.0;
  }
  else if( mt_no > mt_n0 && mt_no <= mt_nc )
  {
    if( reaction_flg == mt_nhe )
    {
      prod_no_vec[xs_gas_he3] += 1.0;
    }
  }

  //For He4 (alpha)
  if( mt_no == mt_na  || mt_no == mt_2na  || mt_no == mt_3na   || mt_no == mt_npa  || mt_no == mt_pa  ||
      mt_no == mt_da  || mt_no == mt_ta   || mt_no == mt_nda   || mt_no == mt_2npa || mt_no == mt_4na ||
      mt_no == mt_5na || mt_no == mt_6na  || mt_no == mt_7na   || mt_no == mt_3npa || mt_no == mt_nta ||
      mt_no == mt_ahe || mt_no == mt_4npa || mt_no == mt_3n2pa )
  {
    prod_no_vec[xs_gas_a] += 1.0;
  }
  else if( mt_no == mt_n2a || mt_no == mt_2n2a || mt_no == mt_nd2a || mt_no == mt_nt2a || mt_no == mt_2a ||
           mt_no == mt_t2a || mt_no == mt_d2a  || mt_no == mt_3n2a || mt_no == mt_4n2a )
  {
    prod_no_vec[xs_gas_a] += 2.0;
  }
  else if( mt_no == mt_n3a || mt_no == mt_3a ) 
  {
    prod_no_vec[xs_gas_a] += 3.0;
  }
  else if( mt_no == mt_a || (xs_gas_tot_flg[xs_gas_a] == 0 && mt_no >= mt_a_min && mt_no <= mt_a_max) )
  {
    prod_no_vec[xs_gas_a] += 1.0;
  }
  else if( mt_no > mt_n0 && mt_no <= mt_nc )
  {
    if( reaction_flg == mt_na || reaction_flg == mt_2na || reaction_flg == mt_3na )
    {
      prod_no_vec[xs_gas_a] += 1.0;
    }
    else if( reaction_flg == mt_n2a || reaction_flg == mt_2n2a || reaction_flg == mt_nd2a ||
             reaction_flg == mt_nt2a )
    {
      prod_no_vec[xs_gas_a] += 2.0;
    }
    else if( reaction_flg == mt_n3a )
    {
      prod_no_vec[xs_gas_a] += 3.0;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void GasProductionXSCalculator::check_residual_material
                                  (Integer mt_no, Integer mat_data, Integer reaction_flg, 
                                   vector<Real>& prod_no_vec)
{
  Integer mat_data_prod = check_production_material(mt_no, reaction_flg, prod_no_vec);
  Integer mat_data_resi = mat_data - mat_data_prod;

  if( mat_data_prod == 0 && mt_no != mt_gam )
  {
    return;
  }

  if( mat_data_resi == 1001 )
  {
    prod_no_vec[xs_gas_p] += 1.0;
  }
  else if( mat_data_resi == 1002 )
  {
    prod_no_vec[xs_gas_d] += 1.0;
  }
  else if( mat_data_resi == 1003 )
  {
    prod_no_vec[xs_gas_t] += 1.0;
  }
  else if( mat_data_resi == 2003 )
  {
    prod_no_vec[xs_gas_he3] += 1.0;
  }
  else if( mat_data_resi == 2004 )
  {
    prod_no_vec[xs_gas_a] += 1.0;
  }
  else if( mat_data_resi == 4008 )
  {
    prod_no_vec[xs_gas_a] += 2.0;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Integer GasProductionXSCalculator::check_production_material(Integer mt_no, Integer reaction_flg,
                                                             vector<Real>& prod_no_vec)
{
  Real mat_data_prod = 0.0;
  mat_data_prod += prod_no_vec[xs_gas_p]   * 1001.0; //1H  = 1 proton + 1 neutrons = 1*1000 + 1 = 1001
  mat_data_prod += prod_no_vec[xs_gas_d]   * 1002.0; //2H  = 1 proton + 2 neutrons = 1*1000 + 2 = 1002
  mat_data_prod += prod_no_vec[xs_gas_t]   * 1003.0; //3H  = 1 proton + 3 neutrons = 1*1000 + 3 = 1003
  mat_data_prod += prod_no_vec[xs_gas_he3] * 2003.0; //3He = 2 proton + 3 neutrons = 2*1000 + 3 = 2003
  mat_data_prod += prod_no_vec[xs_gas_a]   * 2004.0; //4He = 2 proton + 4 neutrons = 2*1000 + 4 = 2004

  if( mt_no == mt_na   || mt_no == mt_n3a  || mt_no == mt_np   || mt_no == mt_n2a  || mt_no == mt_nd  ||
      mt_no == mt_nt   || mt_no == mt_nhe  || mt_no == mt_nd2a || mt_no == mt_nt2a || mt_no == mt_n2p ||
      mt_no == mt_npa  || mt_no == mt_nda  || mt_no == mt_npd  || mt_no == mt_npt  || mt_no == mt_ndt ||
      mt_no == mt_nphe || mt_no == mt_ndhe || mt_no == mt_nthe || mt_no == mt_nta  || mt_no == mt_n3p )
  {
    mat_data_prod += 1.0;
  }
  else if( mt_no == mt_2nd || mt_no == mt_2n  || mt_no == mt_2na  || mt_no == mt_2n2a ||
           mt_no == mt_2np || mt_no == mt_2nt || mt_no == mt_2npa || mt_no == mt_2nhe ||
           mt_no == mt_2n2p )
  {
    mat_data_prod += 2.0;
  }
  else if( mt_no == mt_3n   || mt_no == mt_3na  || mt_no == mt_3np  || mt_no == mt_3nd  ||
           mt_no == mt_3nt  || mt_no == mt_3nhe || mt_no == mt_3n2p || mt_no == mt_3n2a ||
           mt_no == mt_3npa || mt_no == mt_3n2pa )
  {
    mat_data_prod += 3.0;
  }
  else if( mt_no == mt_4n   || mt_no == mt_4np  || mt_no == mt_4na  || mt_no == mt_4nd  ||
           mt_no == mt_4nt  || mt_no == mt_4nhe || mt_no == mt_4n2p || mt_no == mt_4n2a ||
           mt_no == mt_4npa )
  {
    mat_data_prod += 4.0;
  }
  else if( mt_no == mt_5n  || mt_no == mt_5np || mt_no == mt_5na  || mt_no == mt_5nd ||
           mt_no == mt_5nt || mt_no == mt_5n2p )
  {
    mat_data_prod += 5.0;
  }
  else if( mt_no == mt_6n  || mt_no == mt_6np || mt_no == mt_6na  || mt_no == mt_6nd ||
           mt_no == mt_6nt )
  {
    mat_data_prod += 6.0;
  }
  else if( mt_no == mt_7n  || mt_no == mt_7np || mt_no == mt_7na )
  {
    mat_data_prod += 7.0;
  }
  else if( mt_no == mt_8n )
  {
    mat_data_prod += 8.0;
  }

  if( mt_no > mt_n0 && mt_no <= mt_nc )
  {
    if( reaction_flg == mt_2na || reaction_flg == mt_2n2a )
    {
      mat_data_prod += 2.0;
    }
    else if( reaction_flg == mt_3na )
    {
      mat_data_prod += 3.0;
    }
    else
    {
      mat_data_prod += 1.0;
    }
  }

  return static_cast<Integer>(round(mat_data_prod));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void GasProductionXSCalculator::add_gas_prod_xs_to_nuclear_data_obj()
{
  NuclearReactionDataContainer nucl_reaction_data_obj;
  nucl_reaction_data_obj = nucl_data_obj_dop.get_nucl_reaction_data_obj();

  TabAdjuster tab_adjust_obj;
  for(int i=0; i<xs_gas_no; i++)
  {
    Integer reaction_type = 0;
    if( i == xs_gas_p )
    {
      reaction_type = mt_xp;
    }
    else if( i == xs_gas_d )
    {
      reaction_type = mt_xd;
    }
    else if( i == xs_gas_t )
    {
      reaction_type = mt_xt;
    }
    else if( i == xs_gas_he3 )
    {
      reaction_type = mt_xhe;
    }
    else if( i == xs_gas_a )
    {
      reaction_type = mt_xa;
    }

    vector<Real>    xs_vec,       xs_ene_vec;
    vector<Integer> xs_range_vec, xs_int_vec;

    xs_vec     = gas_prod_xs_data[i];
    xs_ene_vec = base_grid;

    xs_range_vec.resize(1);
    xs_int_vec.resize(1);
    xs_range_vec[0] = static_cast<Integer>(xs_vec.size());
    xs_int_vec[0]   = int_lin_lin;

    tab_adjust_obj.remove_zero_data(xs_range_vec, xs_int_vec, xs_ene_vec, xs_vec);
    if( static_cast<int>(xs_vec.size()) == 0 )
    {
      continue;
    }

    int zero_xs_flg = 0;
    for(int j=0;j<static_cast<int>(xs_vec.size()); j++)
    {
      if( fabs(xs_vec[j]) > min_value )
      {
        zero_xs_flg = 1;
        break;
      }
    }
    if( zero_xs_flg == 0 )
    {
      continue;
    }

    CrossSectionDataContainer xs_data_obj;
    xs_data_obj.set_reaction_type(reaction_type);
    xs_data_obj.set_xs_range_data(xs_range_vec);
    xs_data_obj.set_xs_int_data(xs_int_vec);
    xs_data_obj.set_xs_ene_data(xs_ene_vec);
    xs_data_obj.set_xs_data(xs_vec);

    nucl_reaction_data_obj.set_xs_data_obj(xs_data_obj);
    xs_data_obj.clear();
  }

  nucl_data_obj_dop.set_nucl_reaction_data_obj(nucl_reaction_data_obj);
  nucl_reaction_data_obj.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void GasProductionXSCalculator::output_set_data_information()
{
  cout << "=== Nuclear data information (Original nuclear data) ===" << endl;
  cout << "  Material No.       : " << nucl_data_obj_ori.get_general_data_obj().get_mat_no()   << endl;
  cout << "  Material Data (ZA) : " << nucl_data_obj_ori.get_general_data_obj().get_mat_data() << endl;
  cout << "  Mass               : " << nucl_data_obj_ori.get_general_data_obj().get_mass()     << endl;
  cout << "  Temperature        : " << nucl_data_obj_ori.get_general_data_obj().get_temp()     << endl;
  cout << endl;
  cout << "=== Nuclear data information (Doppler broadened nuclear data) ===" << endl;
  cout << "  Material No.       : " << nucl_data_obj_dop.get_general_data_obj().get_mat_no()   << endl;
  cout << "  Material Data (ZA) : " << nucl_data_obj_dop.get_general_data_obj().get_mat_data() << endl;
  cout << "  Mass               : " << nucl_data_obj_dop.get_general_data_obj().get_mass()     << endl;
  cout << "  Temperature        : " << nucl_data_obj_dop.get_general_data_obj().get_temp()     << endl;
  cout << endl;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void GasProductionXSCalculator::set_nucl_data_obj_ori(NuclearDataObject data_obj)
{
  calc_gas_production_xs_flg = 0;
  nucl_data_ori_set_flg      = 1;
  nucl_data_obj_ori          = data_obj;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void GasProductionXSCalculator::set_nucl_data_obj_dop(NuclearDataObject data_obj)
{
  calc_gas_production_xs_flg = 0;
  nucl_data_dop_set_flg      = 1;
  nucl_data_obj_dop          = data_obj;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//Getter

NuclearDataObject GasProductionXSCalculator::get_nucl_data_obj_ori()
{
  return nucl_data_obj_ori;
}

NuclearDataObject GasProductionXSCalculator::get_nucl_data_obj()
{
  if( calc_gas_production_xs_flg == 0 )
  {
    calc_gas_production_xs();
  }

  return nucl_data_obj_dop;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

