#include "DopplerBroadening/DopplerCalculator.hpp"

using namespace frendy;

//Initialize static const value
const Real8 DopplerCalculator::min_distance = 1.0e-7;
const Real8 DopplerCalculator::max_ratio    = 3.0;

//constructor
DopplerCalculator::DopplerCalculator(void)
{
  clear();
}

//destructor
DopplerCalculator::~DopplerCalculator(void)
{
  clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DopplerCalculator::calc_doppler()
{
  if( calc_doppler_flg != 0 )
  {
    return;
  }
  calc_doppler_flg = 1;

  if( nucl_data_set_flg == 0 )
  {
    string class_name = "DopplerCalculator";
    string func_name  = "calc_doppler()";

    vector<string> err_com;
    err_com.push_back("There is no NuclearDataObject.");
    err_com.push_back("Please set nuclear data object using set_nucl_data_obj function.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
  check_set_data();
  check_int_scheme(xs_data_obj);
  
  search_dop_ene_max();
  
  calc_doppler_effect();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DopplerCalculator::check_set_data()
{
  if( ( temp_ori < 0.0 ) || ( temp_dop < 0.0 ) || ( error_value < 0.0 ) || ( error_max_value < 0.0 ) ||
      ( error_int_value < 0.0 ) || ( fabs(temp_nucl - temp_ori) > min_ene_dif ) )
  {
    string class_name = "DopplerCalculator";
    string func_name  = "check_set_data()";

    ostringstream oss01, oss02, oss03, oss04, oss05;
    oss01 << temp_ori;
    oss02 << temp_dop;
    oss03 << error_value;
    oss04 << error_max_value;
    oss05 << error_int_value;
    string str_data01 = "Initial temperature  : " + oss01.str();
    string str_data02 = "Doppler temperature  : " + oss02.str();
    string str_data03 = "Error value          : " + oss03.str();
    string str_data04 = "Maximum error value  : " + oss04.str();
    string str_data05 = "Integral error value : " + oss05.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back(str_data05);
    if( temp_ori < 0.0 )
    {
      err_com.push_back("The initial temperature is less than 0.0.");
      err_com.push_back("Please check temp_ori.");
    }
    if( temp_dop < 0.0 )
    {
      err_com.push_back("The doppler temperature is less than 0.0.");
      err_com.push_back("Please check temp_dop.");
    }
    if( error_value < 0.0 )
    {
      err_com.push_back("The error value is less than 0.0.");
      err_com.push_back("Please chek error_value.");
    }
    if( error_max_value < 0.0 )
    {
      err_com.push_back("The maximum error value is less than 0.0.");
      err_com.push_back("Please chek error_max_value.");
    }
    if( error_int_value < 0.0 )
    {
      err_com.push_back("The integral error value is less than 0.0.");
      err_com.push_back("Please chek error_int_value.");
    }

    if( fabs(temp_nucl - temp_ori) > min_ene_dif )
    {
      err_com.push_back("The base temperature is not equal to the temperature in the nuclear data file.");
    } 
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  if( fabs(temp_dop) < 1.0E-10 )
  {
    string class_name = "DopplerCalculator";
    string func_name  = "check_set_data()";

    ostringstream oss01;
    oss01 << temp_dop;
    string str_data01 = "Doppler temperature  : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("The doppler temperature is less than 1.0E-10 K.");
    err_com.push_back("The doppler temperature is modified to 1.0E-10 K.");
    err_obj.output_caution(class_name, func_name, err_com);

    temp_dop = 1.0E-10;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DopplerCalculator::check_int_scheme(vector<CrossSectionDataContainer>& xs_data_obj_ori)
{
  int i_max = static_cast<int>(xs_data_obj_ori.size());
  vector<Integer> nbt_e, int_e;
  vector<Real>    e_int, sig_tab;
  for(int i=0; i<i_max; i++)
  {
    nbt_e   = xs_data_obj_ori[i].get_xs_range_data();
    int_e   = xs_data_obj_ori[i].get_xs_int_data();
    e_int   = xs_data_obj_ori[i].get_xs_ene_data();
    sig_tab = xs_data_obj_ori[i].get_xs_data();
    
    //Check the interpolation scheme
    Integer ele_no = static_cast<Integer>(e_int.size());
    int     j_max  = static_cast<int>(int_e.size());
    if( ( e_int.size() != sig_tab.size() ) || ( static_cast<int>(nbt_e.size()) != j_max )
     || ( nbt_e[j_max-1] != ele_no ) )
    {
      string class_name = "DopplerCalculator";
      string func_name  = "check_int_scheme(vector<CrossSectionDataContainer>& xs_data_obj_ori)";

      Integer react_val = xs_data_obj_ori[i].get_reaction_type();
      if( react_val > mt_mod_coef )
      {
        react_val /= mt_mod_coef;
      }

      ostringstream oss00, oss01, oss02, oss03, oss04, oss05, oss06;
      oss00 << react_val;
      oss01 << e_int.size();
      oss02 << sig_tab.size();
      oss03 << nbt_e.size();
      oss04 << int_e.size();
      oss05 << nbt_e[j_max-1];
      string str_data00 = "Reaction type                  : " + oss00.str();
      string str_data01 = "Size of energy grid            : " + oss01.str();
      string str_data02 = "Size of cross section          : " + oss02.str();
      string str_data03 = "Size of NBT                    : " + oss03.str();
      string str_data04 = "Size of INT                    : " + oss04.str();
      string str_data05 = "The maximum data number in NBT : " + oss05.str();

      vector<string> err_com;
      err_com.push_back(str_data00);
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back(str_data04);
      err_com.push_back(str_data05);

      if( e_int.size() != sig_tab.size() )
      {
        err_com.push_back("The size of energy grid and cross section is different.");
      }
    
      if( static_cast<int>(nbt_e.size()) != j_max )
      {
        err_com.push_back("The size of NBT and INT is different.");
      }
      else if( nbt_e[j_max-1] != ele_no )
      {
        err_com.push_back("The maximum data number in NBT is not equal to the size of energy grid.");
      }
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
    
    for(int j=0; j<j_max; j++)
    {
      if( int_e[j] != int_lin_lin )
      {
        string class_name = "DopplerCalculator";
        string func_name  = "check_int_scheme(vector<CrossSectionDataContainer>& xs_data_obj_ori)";

        Integer react_val = xs_data_obj_ori[i].get_reaction_type();
        if( react_val > mt_mod_coef )
        {
          react_val /= mt_mod_coef;
        }

        ostringstream oss00, oss01, oss02, oss03;
        oss00 << react_val;
        oss01 << j;
        oss02 << static_cast<int>(int_e.size());
        oss03 << int_e[j];
        string str_data00 = "Reaction type  : " + oss00.str();
        string str_data01 = "INT number     : " + oss01.str() + " / " + oss02.str();
        string str_data02 = "INT            : " + oss03.str();

        vector<string> err_com;
        err_com.push_back(str_data00);
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back("Interpolation scheme is not linear-linear (INT != 2).");
        err_com.push_back("Doppler broadening is only applicable to linear-linear.");
        err_obj.output_runtime_error(class_name, func_name, err_com);
      }
    }
    
    //update xs data
    nbt_e.resize(1);
    int_e.resize(1);
    nbt_e[0] = ele_no;
    int_e[0] = 2;
    
    xs_data_obj_ori[i].set_xs_range_data(nbt_e);
    xs_data_obj_ori[i].set_xs_int_data(int_e);
    nbt_e.clear();
    int_e.clear();
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DopplerCalculator::search_dop_ene_max()
{
  //Copy from MakeInputFromFRENDYtoNJOY (search_thn_max())
  Real max_ene = min_ene_val;

  vector<vector<Integer> > reso_flg_base   = nucl_data_obj_base.get_reso_data_obj().get_reso_region_flg();
  vector<vector<Real> >    reso_eh_base    = nucl_data_obj_base.get_reso_data_obj().get_upper_ene_limit();
  int i_max = static_cast<int>(reso_eh_base.size());
  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(reso_eh_base[i].size());
    for(int j=0; j<j_max; j++)
    {
      if( max_ene < reso_eh_base[i][j] && reso_flg_base[i][j] == 1 )
      {
        max_ene = reso_eh_base[i][j];
      }
    }
  }

  vector<vector<Integer> > reso_flg   = nucl_data_obj.get_reso_data_obj().get_reso_region_flg();
  vector<vector<Real> >    reso_eh    = nucl_data_obj.get_reso_data_obj().get_upper_ene_limit();
  vector<Real>             unreso_ene = nucl_data_obj.get_reso_data_obj().get_unreso_xs_data_obj().get_unreso_ene();
  
  i_max = static_cast<int>(reso_eh.size());
  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(reso_eh[i].size());
    for(int j=0; j<j_max; j++)
    {
      if( max_ene < reso_eh[i][j] && (reso_flg[i][j] == 1 || reso_flg[i][j] == 0) )
      {
        max_ene = reso_eh[i][j];
      }
    }
  }
  clr_obj.clear_vec_array2_real8(reso_eh);
  
  i_max = static_cast<int>(unreso_ene.size());
  if( i_max > 0 )
  {
    if( max_ene < unreso_ene[0] )
    {
      max_ene = unreso_ene[0];
    }
  }
  unreso_ene.clear();

  //Modify dop_ene_max_inp if dop_ene_max_inp = 0.0.
  if( fabs(dop_ene_max_inp) < min_value )
  {
    string class_name = "DopplerCalculator";
    string func_name  = "search_dop_ene_max()";

    ostringstream oss01, oss02;
    oss01 << dop_ene_max_inp;
    oss02 << dop_ene_max_def;
    string str_data01 = "Maximum energy for broader and thinning (input)   : " + oss01.str();
    string str_data02 = "Maximum energy for broader and thinning (default) : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("Maximum energy for broader and thinning is equal to 0.0.");
    err_com.push_back("The maximum energy is modified to the default value.");
    err_obj.output_caution(class_name, func_name, err_com);

    dop_ene_max_inp = dop_ene_max_def;
  }
  
  //Maximum doppler consideration energy is less than or equal to 
  //uppler limit of unresolved resonance energy.
  Real dop_ene_max_inp_abs = fabs(dop_ene_max_inp);
  dop_ene_max_cal = dop_ene_max_inp_abs;
  if( max_ene > min_ene_val )
  {
    if( max_ene < dop_ene_max_inp_abs )
    {
      dop_ene_max_cal = static_cast<Real8>(max_ene);

      string class_name = "DopplerCalculator";
      string func_name  = "search_dop_ene_max()";

      ostringstream oss01, oss02;
      oss01 << dop_ene_max_inp_abs;
      oss02 << dop_ene_max_cal;
      string str_data01 = "Maximum energy for broader and thinning (input) : " + oss01.str();
      string str_data02 = "Upper limit of resolved resonance region        : " + oss02.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back("Maximum energy for broader and thinning is larger than");
      err_com.push_back("the upper limit of resolved resonance region.");
      err_com.push_back("The maximum energy is modified to the upper limit of the");
      err_com.push_back("resonance region.");
      err_obj.output_caution(class_name, func_name, err_com);
    }
    else if( max_ene > dop_ene_max_inp_abs )
    {
      dop_ene_max_cal = static_cast<Real8>(max_ene);

      string class_name = "DopplerCalculator";
      string func_name  = "search_dop_ene_max()";

      ostringstream oss01, oss02;
      oss01 << dop_ene_max_inp_abs;
      oss02 << dop_ene_max_cal;
      string str_data01 = "Maximum energy for broader and thinning (input) : " + oss01.str();
      string str_data02 = "Upper limit of resolved resonance region        : " + oss02.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back("Maximum energy for broader and thinning is smaller than");
      err_com.push_back("the upper limit of resolved resonance region.");
      err_com.push_back("The maximum energy is modified to the upper limit of the");
      err_com.push_back("resonance region.");
      err_obj.output_caution(class_name, func_name, err_com);
    }
  }

  //If maximum Doppler energy is set from input file, compariing
  //input data to nuclear data
  if( dop_ene_max_inp < 0.0 )
  {
    if( max_ene > dop_ene_max_inp_abs )
    {
      string class_name = "DopplerCalculator";
      string func_name  = "search_dop_ene_max()";

      ostringstream oss01, oss02;
      oss01 << dop_ene_max_inp_abs;
      oss02 << max_ene;
      string str_data01 = "Maximum energy for broader and thinning (input) : " + oss01.str();
      string str_data02 = "Upper limit of resolved resonance region        : " + oss02.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back("Maximum energy for broader and thinning is less than.");
      err_com.push_back("the upper limit of resolved resonance region.");
      err_com.push_back("This input data may not be appropriate.");
      err_obj.output_caution(class_name, func_name, err_com);

      dop_ene_max_cal = dop_ene_max_inp_abs;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DopplerCalculator::calc_doppler_effect()
{
  temp_dif = temp_dop - temp_ori;
  calc_xs_obj.set_temp_ori(temp_ori);
  calc_xs_obj.set_temp_dop(temp_dop);
  calc_xs_obj.set_dop_ene_max(dop_ene_max_cal);
  
  calc_doppler_effect_reaction_xs(xs_data_obj);
  calc_doppler_effect_radio_product_xs();
  //calc_doppler_effect_photon_production_xs();
  //calc_doppler_effect_photon_interaction_xs();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DopplerCalculator::calc_doppler_effect_reaction_xs(vector<CrossSectionDataContainer>& xs_data_obj_ori)
{
  vector<vector<CrossSectionDataContainer> > xs_data_obj_part;

  grouping_xs_data(xs_data_obj_ori, xs_data_obj_part);

  int i_max = static_cast<int>(xs_data_obj_part.size());
  for(int i=0; i<i_max; i++)
  {
    calc_doppler_effect_each_group(xs_data_obj_part[i]);
  }

  //Copy xs_data_obj_part to xs_data_obj and clear xs_data_obj_part
  merge_xs_data(xs_data_obj_ori, xs_data_obj_part);

  vector<vector<CrossSectionDataContainer> >().swap(xs_data_obj_part);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DopplerCalculator::calc_doppler_effect_radio_product_xs()
{
  vector<RadioactiveProductDataContainer> rad_data_obj;
  rad_data_obj = nucl_data_obj.get_nucl_reaction_data_obj().get_radio_product_data_obj();

  int i_max = static_cast<int>(rad_data_obj.size());
  vector<vector<int> >     pos_vec;
  vector<vector<Integer> > mt_list;
  vector<CrossSectionDataContainer> xs_data_obj_tmp;
  xs_data_obj_tmp.clear();

  int ele_no = 0;
  pos_vec.resize(i_max);
  mt_list.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(rad_data_obj[i].get_xs_data().size());
    pos_vec[i].resize(j_max);
    mt_list[i].resize(j_max);

    Integer mt_val = rad_data_obj[i].get_reaction_type();
    for(int j=0; j<j_max; j++)
    {
      pos_vec[i][j] = ele_no;
      mt_list[i][j] = mt_val*mt_mod_coef + j + 1;
      xs_data_obj_tmp.push_back(generate_xs_data_obj(mt_list[i][j],
                                                     rad_data_obj[i].get_xs_q_value_mass()[j],
                                                     rad_data_obj[i].get_xs_q_value()[j],
                                                     rad_data_obj[i].get_xs_range_data()[j],
                                                     rad_data_obj[i].get_xs_int_data()[j],
                                                     rad_data_obj[i].get_xs_ene_data()[j],
                                                     rad_data_obj[i].get_xs_data()[j]));
      ele_no++;
    }
  }

  check_int_scheme(xs_data_obj_tmp);
  calc_doppler_effect_reaction_xs(xs_data_obj_tmp);

  //Copy xs_data_obj_tmp to radio_product_data_obj
  i_max = static_cast<int>(mt_list.size());
  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(mt_list[i].size());
    if( j_max > 0 )
    {
      Integer react_val = mt_list[i][0] / mt_mod_coef;
      CrossSectionDataContainer xs_data_obj_ori
                                  = nucl_data_obj.get_nucl_reaction_data_obj().get_xs_data_obj(react_val);

      vector<vector<Integer> > xs_range_array, xs_int_array;
      vector<vector<Real> >    xs_ene_array,   xs_array;
      xs_range_array.resize(j_max);
      xs_int_array.resize(j_max);
      xs_ene_array.resize(j_max);
      xs_array.resize(j_max);
      for(int j=0; j<j_max; j++)
      {
        int pos = pos_vec[i][j];
        CrossSectionDataContainer xs_data_obj_mod = xs_data_obj_tmp[pos];
        if( xs_data_obj_ori.get_reaction_type() != unassigned_mt_no )
        {
          modify_broadened_xs(xs_data_obj_ori, xs_data_obj_mod);
        }
        else
        {
          modify_broadened_xs(xs_data_obj_tmp[pos], xs_data_obj_mod);
        }
        
        xs_range_array[j] = xs_data_obj_mod.get_xs_range_data();
        xs_int_array[j]   = xs_data_obj_mod.get_xs_int_data();
        xs_ene_array[j]   = xs_data_obj_mod.get_xs_ene_data();
        xs_array[j]       = xs_data_obj_mod.get_xs_data();
        xs_data_obj_mod.clear();
      }
      rad_data_obj[i].set_xs_range_data(xs_range_array);
      rad_data_obj[i].set_xs_int_data(xs_int_array);
      rad_data_obj[i].set_xs_ene_data(xs_ene_array);
      rad_data_obj[i].set_xs_data(xs_array);

      clr_obj.clear_vec_array2_int(xs_range_array);
      clr_obj.clear_vec_array2_int(xs_int_array);
      clr_obj.clear_vec_array2_real(xs_ene_array);
      clr_obj.clear_vec_array2_real(xs_array);
    }
  }

  //Clear xs_data_obj_tmp
  vector<CrossSectionDataContainer>().swap(xs_data_obj_tmp);

  //Copy radio production data container to nuclear data object
  NuclearReactionDataContainer nucl_reaction_data_obj = nucl_data_obj.get_nucl_reaction_data_obj();

  nucl_reaction_data_obj.set_radio_product_data_obj(rad_data_obj);
  vector<RadioactiveProductDataContainer>().swap(rad_data_obj);

  nucl_data_obj.set_nucl_reaction_data_obj(nucl_reaction_data_obj);
  nucl_reaction_data_obj.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DopplerCalculator::calc_doppler_effect_photon_production_xs()
{
  vector<PhotonDataContainer> photon_data_obj;
  photon_data_obj = nucl_data_obj.get_nucl_reaction_data_obj().get_photon_data_obj();

  int i_max = static_cast<int>(photon_data_obj.size());
  vector<int>              pos_vec_tot;
  vector<Integer>          mt_list_tot;
  vector<vector<int> >     pos_vec;
  vector<vector<Integer> > mt_list;
  vector<CrossSectionDataContainer> xs_data_obj_tmp;
  xs_data_obj_tmp.clear();

  int ele_no = 0;
  pos_vec_tot.resize(i_max);
  pos_vec.resize(i_max);
  mt_list_tot.resize(i_max);
  mt_list.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    Integer mt_val = photon_data_obj[i].get_reaction_type();
    mt_list_tot[i] = -1;
    pos_vec_tot[i] = -1;
    if( static_cast<int>(photon_data_obj[i].get_photon_production_xs_tot_data().size()) > 0 )
    {
      pos_vec_tot[i] = ele_no;
      mt_list_tot[i] = mt_val*mt_mod_coef;
      xs_data_obj_tmp.push_back(generate_xs_data_obj
                                  (mt_list_tot[i], 0.0, 0.0,
                                   photon_data_obj[i].get_photon_production_xs_tot_range_data(),
                                   photon_data_obj[i].get_photon_production_xs_tot_int_data(),
                                   photon_data_obj[i].get_photon_production_xs_tot_ene_data(),
                                   photon_data_obj[i].get_photon_production_xs_tot_data()));
      ele_no++;
    }

    int j_max = static_cast<int>(photon_data_obj[i].get_photon_production_xs_data().size());
    pos_vec[i].resize(j_max);
    mt_list[i].resize(j_max);
    for(int j=0; j<j_max; j++)
    {
      pos_vec[i][j] = ele_no;
      mt_list[i][j] = mt_val*mt_mod_coef + j + 1;
      xs_data_obj_tmp.push_back(generate_xs_data_obj
                                  (mt_list[i][j], 0.0, 0.0,
                                   photon_data_obj[i].get_photon_production_xs_range_data()[j],
                                   photon_data_obj[i].get_photon_production_xs_int_data()[j],
                                   photon_data_obj[i].get_photon_production_xs_ene_data()[j],
                                   photon_data_obj[i].get_photon_production_xs_data()[j]));
      ele_no++;
    }
  }

  check_int_scheme(xs_data_obj_tmp);
  calc_doppler_effect_reaction_xs(xs_data_obj_tmp);

  //Copy xs_data_obj_tmp to photon_data_obj
  i_max = static_cast<int>(mt_list.size());
  for(int i=0; i<i_max; i++)
  {
    if( mt_list_tot[i] > 0 )
    {
      Integer react_val = mt_list_tot[i] / mt_mod_coef;
      CrossSectionDataContainer xs_data_obj_ori
                                  = nucl_data_obj.get_nucl_reaction_data_obj().get_xs_data_obj(react_val);

      int pos = pos_vec_tot[i];
      CrossSectionDataContainer xs_data_obj_mod = xs_data_obj_tmp[pos];
      if( xs_data_obj_ori.get_reaction_type() != unassigned_mt_no )
      {
        modify_broadened_xs(xs_data_obj_ori, xs_data_obj_mod);
      }
      else
      {
        modify_broadened_xs(xs_data_obj_tmp[pos], xs_data_obj_mod);
      }

      photon_data_obj[i].set_photon_production_xs_tot_range_data(xs_data_obj_mod.get_xs_range_data());
      photon_data_obj[i].set_photon_production_xs_tot_int_data(xs_data_obj_mod.get_xs_int_data());
      photon_data_obj[i].set_photon_production_xs_tot_ene_data(xs_data_obj_mod.get_xs_ene_data());
      photon_data_obj[i].set_photon_production_xs_tot_data(xs_data_obj_mod.get_xs_data());
      xs_data_obj_mod.clear();
    }

    int j_max = static_cast<int>(mt_list[i].size());
    if( j_max > 0 )
    {
      Integer react_val = mt_list[i][0] / mt_mod_coef;
      CrossSectionDataContainer xs_data_obj_ori
                                  = nucl_data_obj.get_nucl_reaction_data_obj().get_xs_data_obj(react_val);

      vector<vector<Integer> > xs_range_array, xs_int_array;
      vector<vector<Real> >    xs_ene_array,   xs_array;
      xs_range_array.resize(j_max);
      xs_int_array.resize(j_max);
      xs_ene_array.resize(j_max);
      xs_array.resize(j_max);
      for(int j=0; j<j_max; j++)
      {
        int pos = pos_vec[i][j];
        CrossSectionDataContainer xs_data_obj_mod = xs_data_obj_tmp[pos];
        if( xs_data_obj_ori.get_reaction_type() != unassigned_mt_no )
        {
          modify_broadened_xs(xs_data_obj_ori, xs_data_obj_mod);
        }
        else
        {
          modify_broadened_xs(xs_data_obj_tmp[pos], xs_data_obj_mod);
        }

        xs_range_array[j] = xs_data_obj_mod.get_xs_range_data();
        xs_int_array[j]   = xs_data_obj_mod.get_xs_int_data();
        xs_ene_array[j]   = xs_data_obj_mod.get_xs_ene_data();
        xs_array[j]       = xs_data_obj_mod.get_xs_data();
        xs_data_obj_mod.clear();
      }
      photon_data_obj[i].set_photon_production_xs_range_data(xs_range_array);
      photon_data_obj[i].set_photon_production_xs_int_data(xs_int_array);
      photon_data_obj[i].set_photon_production_xs_ene_data(xs_ene_array);
      photon_data_obj[i].set_photon_production_xs_data(xs_array);

      clr_obj.clear_vec_array2_int(xs_range_array);
      clr_obj.clear_vec_array2_int(xs_int_array);
      clr_obj.clear_vec_array2_real(xs_ene_array);
      clr_obj.clear_vec_array2_real(xs_array);
    }
  }

  //Clear xs_data_obj_tmp
  vector<CrossSectionDataContainer>().swap(xs_data_obj_tmp);

  //Copy photon data container to nuclear data object
  NuclearReactionDataContainer nucl_reaction_data_obj = nucl_data_obj.get_nucl_reaction_data_obj();

  nucl_reaction_data_obj.set_photon_data_obj(photon_data_obj);
  vector<PhotonDataContainer>().swap(photon_data_obj);

  nucl_data_obj.set_nucl_reaction_data_obj(nucl_reaction_data_obj);
  nucl_reaction_data_obj.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DopplerCalculator::calc_doppler_effect_photon_interaction_xs()
{
  vector<PhotonDataContainer> photon_data_obj;
  photon_data_obj = nucl_data_obj.get_nucl_reaction_data_obj().get_photon_data_obj();

  int i_max = static_cast<int>(photon_data_obj.size());
  vector<int>     pos_vec;
  vector<Integer> mt_list;
  vector<CrossSectionDataContainer> xs_data_obj_tmp;
  xs_data_obj_tmp.clear();

  int ele_no = 0;
  pos_vec.resize(i_max);
  mt_list.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    Integer mt_val = photon_data_obj[i].get_reaction_type();
    mt_list[i] = -1;
    pos_vec[i] = -1;
    if( static_cast<int>(photon_data_obj[i].get_photon_interaction_xs_data().size()) > 0 )
    {
      pos_vec[i] = ele_no;
      mt_list[i] = mt_val*mt_mod_coef;
      xs_data_obj_tmp.push_back(generate_xs_data_obj
                                  (mt_list[i], 0.0, 0.0,
                                   photon_data_obj[i].get_photon_interaction_xs_range_data(),
                                   photon_data_obj[i].get_photon_interaction_xs_int_data(),
                                   photon_data_obj[i].get_photon_interaction_xs_ene_data(),
                                   photon_data_obj[i].get_photon_interaction_xs_data()));
      ele_no++;
    }
  }

  check_int_scheme(xs_data_obj_tmp);
  calc_doppler_effect_reaction_xs(xs_data_obj_tmp);

  //Copy xs_data_obj_tmp to photon_data_obj
  i_max = static_cast<int>(mt_list.size());
  for(int i=0; i<i_max; i++)
  {
    if( mt_list[i] > 0 )
    {
      Integer react_val = mt_list[i] / mt_mod_coef;
      CrossSectionDataContainer xs_data_obj_ori
                                  = nucl_data_obj.get_nucl_reaction_data_obj().get_xs_data_obj(react_val);

      int pos = pos_vec[i];
      CrossSectionDataContainer xs_data_obj_mod = xs_data_obj_tmp[pos];
      if( xs_data_obj_ori.get_reaction_type() != unassigned_mt_no )
      {
        modify_broadened_xs(xs_data_obj_ori, xs_data_obj_mod);
      }
      else
      {
        modify_broadened_xs(xs_data_obj_tmp[pos], xs_data_obj_mod);
      }

      photon_data_obj[i].set_photon_interaction_xs_range_data(xs_data_obj_mod.get_xs_range_data());
      photon_data_obj[i].set_photon_interaction_xs_int_data(xs_data_obj_mod.get_xs_int_data());
      photon_data_obj[i].set_photon_interaction_xs_ene_data(xs_data_obj_mod.get_xs_ene_data());
      photon_data_obj[i].set_photon_interaction_xs_data(xs_data_obj_mod.get_xs_data());
      xs_data_obj_mod.clear();
    }
  }

  //Clear xs_data_obj_tmp
  vector<CrossSectionDataContainer>().swap(xs_data_obj_tmp);

  //Copy photon data container to nuclear data object
  NuclearReactionDataContainer nucl_reaction_data_obj = nucl_data_obj.get_nucl_reaction_data_obj();

  nucl_reaction_data_obj.set_photon_data_obj(photon_data_obj);
  vector<PhotonDataContainer>().swap(photon_data_obj);

  nucl_data_obj.set_nucl_reaction_data_obj(nucl_reaction_data_obj);
  nucl_reaction_data_obj.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

CrossSectionDataContainer DopplerCalculator::generate_xs_data_obj
                                              (Integer reaction_type, Real q_val_mass, Real q_val,
                                               vector<Integer> xs_range_data, vector<Integer> xs_int_data,
                                               vector<Real>    xs_ene_data,   vector<Real>    xs_data)
{
  CrossSectionDataContainer xs_data_obj_tmp;
  xs_data_obj_tmp.set_reaction_type(reaction_type);
  xs_data_obj_tmp.set_q_value_mass(q_val_mass);
  xs_data_obj_tmp.set_q_value(q_val);
  xs_data_obj_tmp.set_xs_range_data(xs_range_data);
  xs_data_obj_tmp.set_xs_int_data(xs_int_data);
  xs_data_obj_tmp.set_xs_ene_data(xs_ene_data);
  xs_data_obj_tmp.set_xs_data(xs_data);

  return xs_data_obj_tmp;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DopplerCalculator::calc_doppler_effect_each_group(vector<CrossSectionDataContainer>& xs_data_obj_part)
{
  NuclearDataObject             nucl_data_obj_tmp = nucl_data_obj;
  NuclearReactionDataContainer  nucl_reaction_data_obj;
  
  unify_energy_grid(xs_data_obj_part);

  nucl_reaction_data_obj.clear();
  nucl_reaction_data_obj.add_xs_data_obj(xs_data_obj_part);
  nucl_data_obj_tmp.set_nucl_reaction_data_obj(nucl_reaction_data_obj);
    
  calc_xs_obj.set_nucl_data_obj(nucl_data_obj_tmp);

  vector<Integer>        nbt_vec, int_vec;
  vector<Real>           e_int, sig_tmp;
  vector<Real8>          ene_data;
  vector<vector<Real8> > sig_data;
    
  //Copy energy and cross section
  int mt_no_max = static_cast<int>(xs_data_obj_part.size());
  if( mt_no_max != 0 )
  {
    e_int = xs_data_obj_part[0].get_xs_ene_data();
    cp_vec.copy_vec_array1_real8(ene_data, e_int);
    e_int.clear();

    //For ENDF-6 format (Double precision -> 11 digit data)
    int i_max = static_cast<int>(ene_data.size());
    for(int i=0; i<i_max; i++)
    {
      ene_data[i] = digit_obj.get_truncation_value(ene_data[i]);
    }
    ta_obj.delete_overlap_grid(ene_data);
      
    i_max = static_cast<int>(ene_data.size());
    sig_data.resize(i_max);
    for(int i=0; i<i_max; i++)
    {
      sig_data[i].resize(mt_no_max);
    }

    for(int mt_no=0; mt_no<mt_no_max; mt_no++)
    {
      nbt_vec = xs_data_obj_part[mt_no].get_xs_range_data();
      int_vec = xs_data_obj_part[mt_no].get_xs_int_data();
      e_int   = xs_data_obj_part[mt_no].get_xs_ene_data();
      sig_tmp = xs_data_obj_part[mt_no].get_xs_data();
      for(int i=0; i<i_max; i++)
      {
        ti_obj.interpolation_tab1(ene_data[i], sig_data[i][mt_no], nbt_vec, int_vec, e_int, sig_tmp);
      }
      nbt_vec.clear();
      int_vec.clear();
      e_int.clear();
      sig_tmp.clear();
    }
  }
  else
  {
    return;
  }
 
  if( temp_dif > 0.0 )
  {
    //Calculation of doppler broadened cross section at original energy grid
    int i_max = static_cast<int>(ene_data.size());
    for(int i=0; i<i_max; i++)
    {
      if(ene_data[i] <= dop_ene_max_cal - min_ene_dif )
      {
        sig_data[i] = calc_xs_obj.calc_doppler_broadened_xs(ene_data[i]);
      }
    }

    //Add middle energy grid
    add_middle_energy_grid(ene_data, sig_data);
  }
  else
  {
    //Remove unnecessary energy grid
    remove_unnecessary_energy_grid(ene_data, sig_data);
  }

  //Copy energy grid and cross section to MF03Parser
  cp_vec.copy_vec_array1_real(e_int, ene_data);
  int grid_no = static_cast<int>(ene_data.size());
  sig_tmp.resize(grid_no);

  vector<Integer> nbt_e, int_e;
  nbt_e.resize(1);
  int_e.resize(1);
  nbt_e[0] = static_cast<Integer>(grid_no);
  int_e[0] = 2;

  for(int mt_no=0; mt_no<mt_no_max; mt_no++)
  {
    xs_data_obj_part[mt_no].set_xs_range_data(nbt_e);
    xs_data_obj_part[mt_no].set_xs_int_data(int_e);

    for(int i=0; i<grid_no; i++)
    {
      sig_tmp[i] = static_cast<Real>(sig_data[i][mt_no]);
    }
    xs_data_obj_part[mt_no].set_xs_ene_data(e_int);
    xs_data_obj_part[mt_no].set_xs_data(sig_tmp);
  }
  nbt_e.clear();
  int_e.clear();
  sig_tmp.clear();
  e_int.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DopplerCalculator::grouping_xs_data(vector<CrossSectionDataContainer>&          xs_data_obj_ori,
                                         vector<vector<CrossSectionDataContainer> >& xs_data_obj_part)
{
  vector<vector<CrossSectionDataContainer> > xs_data_obj_group;
  xs_data_obj_group.resize(6);
  
  int mt_no_max = static_cast<int>(xs_data_obj_ori.size());
  for(int mt_no=0; mt_no<mt_no_max; mt_no++)
  {
    Integer ele_no = static_cast<Integer>(xs_data_obj_ori[mt_no].get_xs_ene_data().size());
    if( ele_no == 0 )
    {
      continue;
    }

    Real ene_low = xs_data_obj_ori[mt_no].get_xs_ene_data()[0];
    if( ene_low >= dop_ene_max_cal - min_ene_dif )
    {
      continue;
    }
    
    if( ele_no >= 10000 )
    {
      xs_data_obj_group[0].push_back(xs_data_obj_ori[mt_no]);
    }
    else if( ele_no >= 5000 )
    {
      xs_data_obj_group[1].push_back(xs_data_obj_ori[mt_no]);
    }
    else if( ele_no >= 1000 )
    {
      xs_data_obj_group[2].push_back(xs_data_obj_ori[mt_no]);
    }
    else if( ele_no >= 500 )
    {
      xs_data_obj_group[3].push_back(xs_data_obj_ori[mt_no]);
    }
    else if( ele_no >= 100 )
    {
      xs_data_obj_group[4].push_back(xs_data_obj_ori[mt_no]);
    }
    else
    {
      xs_data_obj_group[5].push_back(xs_data_obj_ori[mt_no]);
    }
  }
  
  int i_max = static_cast<int>(xs_data_obj_group.size());
  for(int i=0; i<i_max; i++)
  {
    int mt_no_max = static_cast<int>(xs_data_obj_group[i].size());
    if( mt_no_max > 0 )
    {
      xs_data_obj_part.push_back(xs_data_obj_group[i]);
      for(int mt_no=0; mt_no<mt_no_max; mt_no++)
      {
        xs_data_obj_group[i][mt_no].clear();
      }
    }
    xs_data_obj_group[i].clear();
  }
  xs_data_obj_group.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DopplerCalculator::merge_xs_data(vector<CrossSectionDataContainer>&          xs_data_obj_ori,
                                      vector<vector<CrossSectionDataContainer> >& xs_data_obj_part)
{
  int mt_max = static_cast<int>(xs_data_obj_ori.size());
  vector<Integer> mt_list;
  mt_list.resize(mt_max);
  for(int i=0; i<mt_max; i++)
  {
    mt_list[i] = xs_data_obj_ori[i].get_reaction_type();
  }

  int i_max = static_cast<int>(xs_data_obj_part.size());
  for(int i=0; i<i_max; i++)
  {
    int ele_max = static_cast<int>(xs_data_obj_part[i].size());
    for(int j=0; j<ele_max; j++)
    {
      Integer mt_part = xs_data_obj_part[i][j].get_reaction_type();

      for(int k=0; k<mt_max; k++)
      {
        if( mt_list[k] == mt_part )
        {
          modify_broadened_xs( xs_data_obj_ori[k], xs_data_obj_part[i][j] );
          xs_data_obj_ori[k] = xs_data_obj_part[i][j];
          break;
        }
      }
    }
  }
  mt_list.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DopplerCalculator::modify_broadened_xs(CrossSectionDataContainer& xs_data_obj_ori,
                                            CrossSectionDataContainer& xs_data_obj_dop)
{
  vector<Integer> range_dop, int_dop;
  vector<Real>    ene_ori, sig_ori, ene_dop, sig_dop;
  ene_ori = xs_data_obj_ori.get_xs_ene_data();
  sig_ori = xs_data_obj_ori.get_xs_data();

  //Remove zero data
  range_dop = xs_data_obj_dop.get_xs_range_data();
  int_dop   = xs_data_obj_dop.get_xs_int_data();
  ene_dop   = xs_data_obj_dop.get_xs_ene_data();
  sig_dop   = xs_data_obj_dop.get_xs_data();
  ta_obj.remove_zero_data(range_dop, int_dop, ene_dop, sig_dop);

  //If both Doppler broadened xs and original xs are less than min_sig_chk,
  //Doppler broadened xs is considered as 0 barn.
  Real    min_sig_chk = min_sig_val*1.01;
  Integer int_val     = int_lin_lin;

  int i_max = static_cast<int>(ene_dop.size());
  for(int i=0; i<i_max; i++)
  {
    if( sig_dop[i] < min_sig_chk )
    {
      Real sig_tmp = sig_dop[i];
      ti_obj.interpolation_1d(int_val, ene_dop[i], sig_tmp, ene_ori, sig_ori);
      if( sig_tmp < min_sig_chk )
      {
        sig_dop[i] = 0.0;
      }
    }
  }

  //Copy xs data to xs_data_obj_dop
  xs_data_obj_dop.set_xs_range_data(range_dop);
  xs_data_obj_dop.set_xs_int_data(int_dop);
  xs_data_obj_dop.set_xs_ene_data(ene_dop);
  xs_data_obj_dop.set_xs_data(sig_dop);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DopplerCalculator::unify_energy_grid(vector<CrossSectionDataContainer>& xs_data_obj_part)
{
  vector<Integer> nbt_e;
  vector<Real>    e_int, sig_tab;
  vector<Real8>   ene_data, sig_data, unify_grid;
  
  //Make unify energy grid;
  int i_max = static_cast<int>(xs_data_obj_part.size());
  for(int i=0; i<i_max; i++)
  {
    e_int = xs_data_obj_part[i].get_xs_ene_data();
    
    int j_max = static_cast<int>(e_int.size());
    for(int j=0; j<j_max; j++)
    {
      unify_grid.push_back(static_cast<Real8>(e_int[j]));
    }
    e_int.clear();
  }
  sig_data.clear();
  
  ta_obj.delete_overlap_grid(unify_grid);
  
  //Modify (update) energy grid to mit the unify energy grid
  i_max = static_cast<int>(xs_data_obj_part.size());
  for(int i=0; i<i_max; i++)
  {
    nbt_e   = xs_data_obj_part[i].get_xs_range_data();
    e_int   = xs_data_obj_part[i].get_xs_ene_data();
    sig_tab = xs_data_obj_part[i].get_xs_data();
    cp_vec.copy_vec_array1_real8(ene_data, e_int);
    cp_vec.copy_vec_array1_real8(sig_data, sig_tab);
    
    modify_xs_to_adapt_unify_energy_grid(unify_grid, ene_data, sig_data);

    cp_vec.copy_vec_array1_real(e_int,   ene_data);
    cp_vec.copy_vec_array1_real(sig_tab, sig_data);
    nbt_e.resize(1);
    nbt_e[0] = static_cast<Integer>(e_int.size());
    xs_data_obj_part[i].set_xs_range_data(nbt_e);
    xs_data_obj_part[i].set_xs_ene_data(e_int);
    xs_data_obj_part[i].set_xs_data(sig_tab);
    
    ene_data.clear();
    sig_data.clear();
    nbt_e.clear();
    e_int.clear();
    sig_tab.clear();
  }
  unify_grid.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DopplerCalculator::modify_xs_to_adapt_unify_energy_grid(vector<Real8>& unify_grid, 
                                                             vector<Real8>& ene_data, vector<Real8>& sig_data)
{
  int  reso_bound_flg = 0;
  Real ene_resolve_eh = nucl_data_obj_base.get_reso_data_obj().get_eh_reso();
  Real ene_unreso_el  = nucl_data_obj_base.get_reso_data_obj().get_el_unreso();
  if( ene_resolve_eh > min_value && ene_unreso_el > min_value )
  {
    if( fabs(ene_unreso_el - ene_resolve_eh) < fabs(min_ene_dif * ene_resolve_eh) )
    {
      reso_bound_flg = 1;
    }
  }

  vector<Real8> new_ene, new_sig;
  
  Integer int_val = int_lin_lin;

  int ele_no     = 1;
  int ele_no_max = static_cast<int>(ene_data.size()) - 1;
  
  Real8 xm, xp, ym, yp;
  int i_max = static_cast<int>(unify_grid.size());
  new_ene.clear();
  new_sig.clear();
  for(int i=0; i<i_max; i++)
  {
    if( unify_grid[i] < ene_data[0] )
    {
      new_ene.push_back(unify_grid[i]);
      new_sig.push_back(0.0);
      continue;
    }
    else if( reso_bound_flg > 0 &&
             fabs(unify_grid[i] - ene_resolve_eh) < fabs(min_ene_dif * ene_resolve_eh) )
    {
      //Serch boundary position
      int j_pos_m = -1;
      int j_pos_p = -1;
      for(int j=ele_no_max-1; j>=0; j--)
      {
        if( fabs(ene_data[j] - ene_resolve_eh) < fabs(min_ene_dif * ene_resolve_eh) )
        {
          j_pos_m = j;
          j_pos_p = j;

          if( j > 0 && fabs(ene_data[j-1] - ene_resolve_eh) < fabs(min_ene_dif * ene_resolve_eh) )
          {
            j_pos_m = j-1;
          }
          break;
        }
      }

      if( j_pos_p >= 0 )
      {
        //Add boundary of resolved and unresolved resonance region
        //Add highest energy at resolved resonance region
        new_ene.push_back(ene_resolve_eh);
        if( j_pos_m <= 1 )
        {
          new_sig.push_back(sig_data[j_pos_m]);
        }
        else
        {
          Real sig_val = 0.0;
          ti_obj.interpolation_1d(int_lin_lin, ene_resolve_eh, sig_val,
                                  ene_data[j_pos_m-2], sig_data[j_pos_m-2],
                                  ene_data[j_pos_m-1], sig_data[j_pos_m-1]);
          new_sig.push_back(sig_val);
        }

        //Add lowest energy at unresolved resonance region
        new_ene.push_back(ene_unreso_el);
        if( j_pos_p >= ele_no_max-2 )
        {
          new_sig.push_back(sig_data[j_pos_p]);
        }
        else
        {
          Real sig_val = 0.0;
          ti_obj.interpolation_1d(int_lin_lin, ene_unreso_el, sig_val,
                                  ene_data[j_pos_p+1], sig_data[j_pos_p+1],
                                  ene_data[j_pos_p+2], sig_data[j_pos_p+2]);
          new_sig.push_back(sig_val);
        }


      }
      else
      {
        Real sig_val = 0.0;
        ti_obj.interpolation_1d(int_lin_lin, ene_resolve_eh, sig_val, ene_data, sig_data);
        new_ene.push_back(ene_resolve_eh);
        new_sig.push_back(sig_val);
        new_ene.push_back(ene_unreso_el);
        new_sig.push_back(sig_val);
      }
      reso_bound_flg = 0;
      continue;
    }

    if( ele_no < ele_no_max )
    {
      while( unify_grid[i] > ene_data[ele_no] )
      {
        ele_no++;
        if( ele_no >= ele_no_max )
        {
          break;
        }
      }
    }

    if( ele_no == 0 )
    {
      xm = ene_data[0];
      xp = ene_data[1];
      ym = sig_data[0];
      yp = sig_data[1];
    }
    else if( ele_no >= ele_no_max )
    {
      xm = ene_data[ele_no_max-1];
      xp = ene_data[ele_no_max];
      ym = sig_data[ele_no_max-1];
      yp = sig_data[ele_no_max];
    }
    else
    {
      xm = ene_data[ele_no-1];
      xp = ene_data[ele_no];
      ym = sig_data[ele_no-1];
      yp = sig_data[ele_no];
    }
    
    //Interpolate cross section 
    Real xs_val = 0.0;
    ti_obj.interpolation_1d(int_val, unify_grid[i], xs_val, xm, ym, xp, yp);
    new_ene.push_back(unify_grid[i]);
    new_sig.push_back(xs_val);
  }
  ene_data = new_ene;
  sig_data = new_sig;
  new_ene.clear();
  new_sig.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DopplerCalculator::remove_unnecessary_energy_grid( vector<Real8>& ene_data, 
                                                        vector<vector<Real8> >& sig_data )
{
  Real8                  ene_pre_pre;
  vector<Real8>          new_ene;
  vector<vector<Real8> > new_sig;
  int i_max = static_cast<int>(ene_data.size());
  if( i_max < 3 )
  {
    return;
  }

  Integer mid_ene_chk = 0;
  int     ele_no      = 0;
  new_ene.push_back(ene_data[0]);
  new_sig.push_back(sig_data[0]);
  for(int i=1; i<i_max-1; i++)
  {
    mid_ene_chk = 0;
    if(ene_data[i] <= dop_ene_max_cal - min_ene_dif )
    {
      if( ene_data[i] < 1.24*new_ene[ele_no] )
      {
        if( i > 1 )
        {
          ene_pre_pre = ene_data[i-2];
        }
        else
        {
          ene_pre_pre = -1.0;
        }
        mid_ene_chk = check_energy_grid_distance(ene_pre_pre, ene_data[i-1], ene_data[i+1],
                                                 sig_data[i-1], sig_data[i+1], ene_data[i], sig_data[i]);

        if( mid_ene_chk >= 0 )
        {
          if( ele_no > 0 )
          {
            ene_pre_pre = new_ene[ele_no-1];
          }
          else
          {
            ene_pre_pre = -1.0;
          }
          mid_ene_chk = check_energy_grid_distance(ene_pre_pre, new_ene[ele_no], ene_data[i+1],
                                                   new_sig[ele_no], sig_data[i+1], ene_data[i], sig_data[i]);
        }
      }
      else
      {
        mid_ene_chk = -10000;
      }
    }
    else
    {
      mid_ene_chk = -20000;
    }
    
    if( mid_ene_chk < 0 )
    {
      ele_no++;
      new_ene.push_back(ene_data[i]);
      new_sig.push_back(sig_data[i]);
    }
  }
  new_ene.push_back(ene_data[i_max-1]);
  new_sig.push_back(sig_data[i_max-1]);
  ene_data = new_ene;
  sig_data = new_sig;
  new_ene.clear();
  clr_obj.clear_vec_array2_real8(new_sig);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DopplerCalculator::add_middle_energy_grid( vector<Real8>& ene_data, vector<vector<Real8> >& sig_data )
{
  int i_max  = static_cast<int>(ene_data.size());
  if( i_max == 0 )
  {
    return;
  }

  int                    j;
  Integer                int_chk;
  Real8                  mid_ene, ene_pre_pre;
  vector<Real8>          mid_sig;
  vector<Real8>          new_ene, new_ene_part;
  vector<vector<Real8> > new_sig, new_sig_part;
  new_ene.clear();
  new_ene_part.clear();
  clr_obj.clear_vec_array2_real8(new_sig);
  clr_obj.clear_vec_array2_real8(new_sig_part);
  
  new_ene.push_back(ene_data[0]);
  new_sig.push_back(sig_data[0]);
  for(int i=1; i<i_max; i++)
  {
    new_ene_part.push_back(ene_data[i-1]);
    new_sig_part.push_back(sig_data[i-1]);
    new_ene_part.push_back(ene_data[i]);
    new_sig_part.push_back(sig_data[i]);

    if( ene_data[i] <= dop_ene_max_cal - min_ene_dif )
    {
      //Check energy grid and cross section
      int_chk = -1;
      if( i < i_max - 1 )
      {
        if( i > 1 )
        {
          ene_pre_pre = ene_data[i-2];
        }
        else
        {
          ene_pre_pre = -1.0;
        }
        int_chk = check_energy_grid_distance(ene_pre_pre, ene_data[i-1], ene_data[i+1],
                                             sig_data[i-1], sig_data[i+1], ene_data[i], sig_data[i]);
         if( int_chk >= 0 )
         {
           if( fabs(ene_data[i]   - ene_data[i-1]) > 50.0 * fabs(ene_data[i+1] - ene_data[i])   ||
               fabs(ene_data[i+1] - ene_data[i])   > 50.0 * fabs(ene_data[i]   - ene_data[i-1]) )
           {
             int_chk = -999;
           }
        }
      }

      if( int_chk < 0 )
      {
        j = 1;

        ene_pre_pre = -1.0;
        mid_ene = 0.5*(new_ene_part[j] + new_ene_part[j-1]);
        mid_ene = digit_obj.get_truncation_value(mid_ene);

        mid_sig = calc_xs_obj.calc_doppler_broadened_xs(mid_ene);
        int_chk = check_energy_grid_distance(ene_pre_pre, new_ene_part[j-1], new_ene_part[j],
                                             new_sig_part[j-1], new_sig_part[j], mid_ene, mid_sig);
        while( int_chk < 0 || j < static_cast<int>(new_ene_part.size()-1) )
        {
          if( int_chk >= 0 )
          {
            j++;
          }
          else
          {
            //Add middle energy grid and cross section
            insert_middle_energy_grid(j, new_ene_part, new_sig_part, mid_ene, mid_sig);
          }

          if( j > 1 )
          {
            ene_pre_pre = new_ene_part[j-2];
          }
          else
          {
            ene_pre_pre = -1.0;
          }
          mid_ene = 0.5*(new_ene_part[j] + new_ene_part[j-1]);
          mid_ene = digit_obj.get_truncation_value(mid_ene);
          mid_sig = calc_xs_obj.calc_doppler_broadened_xs(mid_ene);
          int_chk = check_energy_grid_distance(ene_pre_pre, new_ene_part[j-1], new_ene_part[j], 
                                               new_sig_part[j-1], new_sig_part[j], mid_ene, mid_sig);
        }
      }
    }
    add_xs_at_each_grid(new_ene, new_sig, new_ene_part, new_sig_part);
  }
  ene_data = new_ene;
  sig_data = new_sig;
  new_ene.clear();
  clr_obj.clear_vec_array2_real8(new_sig);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Integer DopplerCalculator::check_energy_grid_distance( Real8& ene_pre_pre, Real8& ene_pre, Real8& ene_cur,
                                                       vector<Real8>& sig_pre, vector<Real8>& sig_cur,
                                                       Real8& mid_ene, vector<Real8>& mid_sig )
{
  Integer       chk_flg = 0;
  Real8         err, err_max, err_int;

  Real8         delta_ene = fabs(ene_cur - ene_pre);
  vector<Real8> delta_sig;

  if( delta_ene < min_ene_dif )
  {
    return chk_flg;
  }

  //Check the energy grid distance
  //If energy distance is so small, add middle energy grid is skipped.
  if( fabs(ene_cur - mid_ene) <= min_distance*mid_ene ||
      fabs(mid_ene - ene_pre) <= min_distance*mid_ene )
  {
    return chk_flg;
  }

  if( ene_pre_pre > 0.0 )
  {
    //If energy grid distance is so large, middle energy grid is added.
    if( fabs(ene_pre - ene_pre_pre) > min_ene_dif )
    {
      if( delta_ene > 4.1*(ene_pre - ene_pre_pre) )
      {
        chk_flg = -50000;
        return chk_flg;
      }
    }
  }
  
  //Adjust error value
  err     = error_value;
  err_max = error_max_value;
  err_int = error_int_value;
  if( ene_cur < 0.5 )
  {
    //err     = 0.2 * error_value;
    //err_max = 0.2 * error_max_value;
    //err_int = 0.2 * error_int_value;
  }

  //Check cross section at middle energy grid
  int mt_no_max = static_cast<int>(mid_sig.size());
  delta_ene = fabs(ene_cur - ene_pre);
  delta_sig.resize(mt_no_max);
  for(int mt_no=0; mt_no<mt_no_max; mt_no++)
  {
    if( fabs(sig_cur[mt_no]) > min_ene_dif && fabs(sig_pre[mt_no]) > min_ene_dif )
    {
      //Ratio (sig[i]/sig[i-1]) check
      if( sig_cur[mt_no] / sig_pre[mt_no] > max_ratio )
      {
        chk_flg = -10000;
        return chk_flg;
      }
      else if( sig_pre[mt_no] / sig_cur[mt_no] > max_ratio )
      {
        chk_flg = -20000;
        return chk_flg;
      }
    }
    
    //delta_sig check
    Real8 ene_dis = ( mid_ene - ene_pre ) / delta_ene;
    delta_sig[mt_no] = fabs(mid_sig[mt_no] - (ene_dis*sig_cur[mt_no] + (1.0-ene_dis)*sig_pre[mt_no]));
    if( delta_sig[mt_no] < err * mid_sig[mt_no] )
    {
      chk_flg++;
    }
    else if( delta_sig[mt_no] < min_sig_val && mid_sig[mt_no] < min_sig_val )
    {
      chk_flg++;
    }
  }

  if( chk_flg != mt_no_max )
  {
    //chk_flg *= -1;
    if( chk_flg == 0 )
    {
      chk_flg = -30000;
      return chk_flg;
    }
    //return chk_flg;

    //Skip checking err_max and err_int
    for(int mt_no=0; mt_no<mt_no_max; mt_no++)
    {
      if( delta_sig[mt_no] > err * mid_sig[mt_no] )
      {
        if( delta_sig[mt_no] > err_max * mid_sig[mt_no] )
        {
          chk_flg = -1;
          return chk_flg;
        }
        else if( delta_sig[mt_no]*delta_ene >= 2.0*err_int*mid_ene )
        {
          chk_flg = -2;
          return chk_flg;
        }
      }
    }
  }
  return chk_flg;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DopplerCalculator::insert_middle_energy_grid( int& ele_no, 
                                                   vector<Real8>& ene_data, vector<vector<Real8> >& sig_data,
                                                   Real8& mid_ene, vector<Real8>& mid_sig )
{
  ta_obj.add_table_data_at_given_position(ene_data, sig_data, mid_ene, mid_sig, ele_no);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DopplerCalculator::add_xs_at_each_grid( vector<Real8>& new_ene,      vector<vector<Real8> >& new_sig, 
                                             vector<Real8>& new_ene_part, vector<vector<Real8> >& new_sig_part )
{
  int i_max = static_cast<int>(new_ene_part.size());
  for(int i=1; i<i_max; i++)
  {
    new_ene.push_back(new_ene_part[i]);
    new_sig.push_back(new_sig_part[i]);
  }
  new_ene_part.clear();
  clr_obj.clear_vec_array2_real8(new_sig_part);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DopplerCalculator::clear()
{
  calc_xs_obj.clear();

  clear_parser();
  
  temp_ori        =    0.0;
  temp_dop        = -100.0;
  temp_dif        =    0.0;
  temp_nucl       = -100.0;
  error_value     =   -1.0;
  error_max_value =   -1.0;
  error_int_value =   -1.0;
  dop_ene_max_inp = dop_ene_max_def;
  dop_ene_max_cal = dop_ene_max_def;

  nucl_data_obj_base.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DopplerCalculator::clear_parser()
{
  calc_doppler_flg  = 0;
  nucl_data_set_flg = 0;
  
  nucl_data_obj.clear();

  vector<CrossSectionDataContainer>().swap(xs_data_obj);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DopplerCalculator::set_nucl_data_obj_base(NuclearDataObject& data_obj)
{
  calc_doppler_flg = 0;

  nucl_data_obj_base = data_obj;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DopplerCalculator::set_nucl_data_obj(NuclearDataObject& data_obj)
{
  clear_parser();
  nucl_data_set_flg = 1;

  nucl_data_obj = data_obj;

  xs_data_obj = nucl_data_obj.get_nucl_reaction_data_obj().get_xs_data_obj_assigned();

  temp_nucl = static_cast<Real8>(nucl_data_obj.get_general_data_obj().get_temp());
  if( temp_nucl < 0.0 )
  {
    string class_name = "DopplerCalculator";
    string func_name  = "set_nucl_data_obj(NuclearDataObject& data_obj)";

    ostringstream oss01;
    oss01 << temp_nucl;
    string str_data01 = "Temperature in the nuclear data file : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("The temperature in the nuclear data file is less than 0[K].");
    err_com.push_back("Please check the nuclear data file.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////

void DopplerCalculator::output_set_data_information()
{
  cout << "=== Nuclear data information ===" << endl;
  cout << "  Material No.       : " << nucl_data_obj.get_general_data_obj().get_mat_no()      << endl;
  cout << "  Material Data (ZA) : " << nucl_data_obj.get_general_data_obj().get_mat_data()    << endl;
  cout << "  Mass               : " << nucl_data_obj.get_general_data_obj().get_mass()        << endl;
  cout << "  Error              : " << nucl_data_obj.get_general_data_obj().get_error_value() << endl;
  cout << endl;
  cout << "=== Set data information ===" << endl;
  cout << "  Start Temperature    : " << temp_ori        << endl;
  cout << "  Final Temperature    : " << temp_dop        << endl;
  cout << "  Input Maximum Energy : " << dop_ene_max_inp << endl;
  cout << "  Error                : " << error_value     << endl;
  cout << "  Integral Error       : " << error_int_value << endl;
  cout << "  Maximum Error        : " << error_max_value << endl;
  cout << endl;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DopplerCalculator::set_temp_ori(Real8 real_val)
{
  calc_doppler_flg = 0;
  temp_ori         = real_val;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DopplerCalculator::set_temp_dop(Real8 real_val)
{
  calc_doppler_flg = 0;
  temp_dop         = real_val;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DopplerCalculator::set_err(Real8 real_val)
{
  calc_doppler_flg = 0;
  error_value      = real_val;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DopplerCalculator::set_err_max(Real8 real_val)
{
  calc_doppler_flg = 0;
  error_max_value  = real_val;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DopplerCalculator::set_err_int(Real8 real_val)
{
  calc_doppler_flg = 0;
  error_int_value  = real_val;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DopplerCalculator::set_dop_ene_max(Real8 real_val)
{
  calc_doppler_flg = 0;
  dop_ene_max_inp  = real_val;
  dop_ene_max_cal  = real_val;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//Getter

Real8 DopplerCalculator::get_temp_ori()
{
  return temp_ori;
}

Real8 DopplerCalculator::get_temp_dop()
{
  return temp_dop;
}

Real8 DopplerCalculator::get_err()
{
  return error_value;
}

Real8 DopplerCalculator::get_err_max()
{
  return error_max_value;
}

Real8 DopplerCalculator::get_err_int()
{
  return error_int_value;
}

Real8 DopplerCalculator::get_dop_ene_max()
{
  return dop_ene_max_cal;
}

NuclearDataObject DopplerCalculator::get_nucl_data_obj_base()
{
  return nucl_data_obj_base;
}

NuclearDataObject DopplerCalculator::get_nucl_data_obj()
{
  if( calc_doppler_flg == 0 )
  {
    calc_doppler();
  }

  NuclearReactionDataContainer  nucl_reaction_data_obj = nucl_data_obj.get_nucl_reaction_data_obj();
  nucl_reaction_data_obj.set_xs_data_obj(xs_data_obj);
  nucl_data_obj.set_nucl_reaction_data_obj(nucl_reaction_data_obj);
  nucl_reaction_data_obj.clear();


  //Add temperature and error data in GeneralNuclearDataContainer
  Real temp_real = static_cast<Real>(temp_dop);
  Real err_real  = static_cast<Real>(error_value);

  GeneralDataContainer general_data_obj = nucl_data_obj.get_general_data_obj();
  general_data_obj.set_temp(temp_real);
  general_data_obj.set_error_value(err_real);
  nucl_data_obj.set_general_data_obj(general_data_obj);
  general_data_obj.clear();


  //Add temperature data in UnresolvedCrossSectionDataContainer
  ResonanceDataContainer              reso_data_obj      = nucl_data_obj.get_reso_data_obj();
  UnresolvedCrossSectionDataContainer unreso_xs_data_obj = reso_data_obj.get_unreso_xs_data_obj();
  unreso_xs_data_obj.set_temp(temp_real);
  reso_data_obj.set_unreso_xs_data_obj(unreso_xs_data_obj);
  nucl_data_obj.set_reso_data_obj(reso_data_obj);
  reso_data_obj.clear();
  unreso_xs_data_obj.clear();

  //Modify cross section data
  nucl_util_obj.modify_xs_data_without_caution(nucl_data_obj);

#ifndef DEBUG_MODE
  //For test calculation (DopplerCalculatorTest.cpp)
#else
  nucl_util_obj.check_total_product_xs(nucl_data_obj);
#endif

  return nucl_data_obj;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

