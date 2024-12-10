#include "ReconResonance/ReconstructXSMerger.hpp"

using namespace frendy;

//constructor
ReconstructXSMerger::ReconstructXSMerger(void)
{
  clear();

  //for mt = 103 : (z,p) - Total of proton level cross sections (600-649)
  proton_xs_min = mt_p_min_endf6;
  proton_xs_max = mt_p_max_endf6;

  //for mt = 104 : (z,d) - Total of deuteron level cross sections (650-699)
  deuteron_xs_min = mt_d_min_endf6;
  deuteron_xs_max = mt_d_max_endf6;

  //for mt = 105 : (z,t) - Total of triton level cross sections (700-749)
  triton_xs_min = mt_t_min_endf6;
  triton_xs_max = mt_t_max_endf6;

  //for mt = 106 : (z,3He) - Total of 3He level cross sections (750-799)
  he_xs_min = mt_he3_min_endf6;
  he_xs_max = mt_he3_max_endf6;

  //for mt = 107 : (z,alpha) - Total of alpha level cross sections (800-849)
  alpha_xs_min = mt_a_min_endf6;
  alpha_xs_max = mt_a_max_endf6;
}

//destructor
ReconstructXSMerger::~ReconstructXSMerger(void)
{
  clear();

  proton_xs_min   = 0;
  proton_xs_max   = 0;
  deuteron_xs_min = 0;
  deuteron_xs_max = 0;
  triton_xs_min   = 0;
  triton_xs_max   = 0;
  he_xs_min       = 0;
  he_xs_max       = 0;
  alpha_xs_min    = 0;
  alpha_xs_max    = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ReconstructXSMerger::merge_non_reso_and_reso_xs()
{
  merge_xs_flg = 1;
  check_set_data();

  get_base_grid();
  calc_non_reso_xs_on_unified_grid();
  if( inelastic_scat_xs_flg == 1 )
  {
    calc_total_inelastic_scat_xs();
  }

  if( reso_flg == 1 )
  {
    add_reso_xs();
    delete_unnecessary_xs();
#ifdef NJOY_MODE
    delete_el_and_eh();
#else
    add_el_and_eh();
#endif
  }

  check_minus_xs();
  
  if( static_cast<int>(nucl_data_obj.get_reso_data_obj().get_unreso_xs_data_obj().get_unreso_ene().size()) > 0 )
  {
    //If MF=2, MT=152 is exsit, i.e., XS is already reconstructed before this process,
    //skip update_xs function
  }
  else
  {
    update_xs_tot_sc_fis_rad();
    update_xs_other();

    mod_first_chance_fission_xs();

    mod_tot_prod_xs();

    mod_non_elastic_xs();
  }

  add_mf10_mt102_data();

  remove_non_linearize_xs_data();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ReconstructXSMerger::get_base_grid()
{
  ene_merge.clear();
  
  int i_max = static_cast<int>(ene_reso.size());
  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(ene_reso[i].size());
    for(int j=0; j<j_max; j++)
    {
      ta_obj.add_grid_data(ene_merge, ene_reso[i][j]);
    }
  }
  
  ta_obj.add_grid_data(ene_merge, ene_non_reso);

  i_max = static_cast<int>(ene_merge.size());
  if( i_max == 0 )
  {
    string class_name = "ReconstructXSMerger";
    string func_name  = "get_base_grid()";

    ostringstream oss01;
    oss01 << static_cast<int>(ene_merge.size());
    string str_data01 = "Data size of energy grid : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("The energy grid size is 0.");
    err_com.push_back("Please check energy grid.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ReconstructXSMerger::calc_non_reso_xs_on_unified_grid()
{
  NonResonanceEnergyGridLinearizer nrl_obj;
  vector<Real8> sig_tmp;

  int i_max = static_cast<int>(ene_merge.size());
  sig_merge.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    sig_merge[i].resize(xs_type_no);
    for(int j=0; j<xs_type_no; j++)
    {
      sig_merge[i][j] = 0.0;
    }
  }

  vector<Integer>          nbt_e, int_e;
  vector<Real>             ene_data, xs_data;
  vector<vector<Integer> > nbt_e_array, int_e_array;
  vector<vector<Real> >    ene_data_array, xs_data_array;

  vector<CrossSectionDataContainer>       xs_data_obj;
  vector<RadioactiveProductDataContainer> radio_product_data_obj;
  vector<PhotonDataContainer>             photon_data_obj;
  xs_data_obj            = nucl_reaction_data_obj.get_xs_data_obj();
  radio_product_data_obj = nucl_reaction_data_obj.get_radio_product_data_obj();
  photon_data_obj        = nucl_reaction_data_obj.get_photon_data_obj();

  //Check library format
  if( nucl_data_obj.get_general_data_obj().get_lib_format() < 6 ) //For ENDF-5 format
  {
    string class_name = "ReconstructXSMerger";
    string func_name  = "calc_non_reso_xs_on_unified_grid()";

    ostringstream oss01;
    oss01 << nucl_data_obj.get_general_data_obj().get_lib_format();
    string str_data01 = "Library format for original nuclear data : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("The library format is not equal to 6.");
    err_com.push_back("MT number of (n,p), (n,d), (n,t), (n,He3), and (n,alpha) are modified");
    err_com.push_back("from MT=600-849 to MT=700-799.");
    err_com.push_back("This modification affects the processing results and the processing");
    err_com.push_back("results may be incorrect.");
    err_com.push_back("Please check the processing results.");
    err_obj.output_caution(class_name, func_name, err_com);

    proton_xs_min   = mt_p_min_endf5;
    proton_xs_max   = mt_p_max_endf5;
    deuteron_xs_min = mt_d_min_endf5;
    deuteron_xs_max = mt_d_max_endf5;
    triton_xs_min   = mt_t_min_endf5;
    triton_xs_max   = mt_t_max_endf5;
    he_xs_min       = mt_he3_min_endf5;
    he_xs_max       = mt_he3_max_endf5;
    alpha_xs_min    = mt_a_min_endf5;
    alpha_xs_max    = mt_a_max_endf5;
  }

  for(int i=0; i<reaction_type_no; i++)
  {
    Integer mt_no = reaction_type[i];

    //Reaction cross section (CrossSectionDataContainer, MF=03)
    if( xs_data_obj[i].get_reaction_type() == mt_no )
    {
      if( nrl_obj.check_mf_mt(3, mt_no,
                              inelastic_scat_xs_flg, fission_xs_flg, photoelectric_xs_flg) == 0 )
      {
        nbt_e = xs_data_obj[i].get_xs_range_data();
        if( static_cast<int>(nbt_e.size()) > 0 )
        {
          int_e    = xs_data_obj[i].get_xs_int_data();
          ene_data = xs_data_obj[i].get_xs_ene_data();
          xs_data  = xs_data_obj[i].get_xs_data();
  
          calc_non_reso_xs( 3, mt_no, sig_tmp, nbt_e, int_e, ene_data, xs_data );

          xs_data_obj[i].set_xs_range_data(nbt_e);
          xs_data_obj[i].set_xs_int_data(int_e);
          xs_data_obj[i].set_xs_ene_data(ene_data);
          xs_data_obj[i].set_xs_data(xs_data);

          //Add total, elastic scatter, fission, radiation cross sections 
          vector<int> add_xs_type = check_add_xs(reaction_type[i]);
          for(int j=0; j<static_cast<int>(add_xs_type.size()); j++)
          {
            add_non_reso_xs(sig_tmp, add_xs_type[j]);
          }
        }
        sig_tmp.clear();
        nbt_e.clear();
        int_e.clear();
        ene_data.clear();
        xs_data.clear();
      }
    }

    //Cross section for production of radioactive nuclides (RadioactiveProductDataContainer, MF=10)
    if( nrl_obj.check_mf_mt(10, mt_no, inelastic_scat_xs_flg, fission_xs_flg, photoelectric_xs_flg) == 0 &&
        radio_product_data_obj[i].get_reaction_type() == mt_no )
    {
      nbt_e_array = radio_product_data_obj[i].get_xs_range_data();
      if( static_cast<int>(nbt_e_array.size()) > 0 )
      {
        int_e_array    = radio_product_data_obj[i].get_xs_int_data();
        ene_data_array = radio_product_data_obj[i].get_xs_ene_data();
        xs_data_array  = radio_product_data_obj[i].get_xs_data();

        for(int j=0; j<static_cast<int>(nbt_e_array.size()); j++)
        {
          calc_non_reso_xs( 10, mt_no, sig_tmp, nbt_e_array[j], int_e_array[j], ene_data_array[j], xs_data_array[j] );
        }

        radio_product_data_obj[i].set_xs_range_data(nbt_e_array);
        radio_product_data_obj[i].set_xs_int_data(int_e_array);
        radio_product_data_obj[i].set_xs_ene_data(ene_data_array);
        radio_product_data_obj[i].set_xs_data(xs_data_array);
      }
      sig_tmp.clear();
      clr_obj.clear_vec_array2_int(nbt_e_array);
      clr_obj.clear_vec_array2_int(int_e_array);
      clr_obj.clear_vec_array2_real(ene_data_array);
      clr_obj.clear_vec_array2_real(xs_data_array);
    }

    if( photon_data_obj[i].get_reaction_type() == mt_no )
    {
      //Photon production (PhotonDataContainer, MF=12)
      if( nrl_obj.check_mf_mt(12, mt_no,
                              inelastic_scat_xs_flg, fission_xs_flg, photoelectric_xs_flg) == 0 )
      {
        nbt_e = photon_data_obj[i].get_multiplicity_tot_range_data();
        if( static_cast<int>(nbt_e.size()) > 0 )
        {
          int_e    = photon_data_obj[i].get_multiplicity_tot_int_data();
          ene_data = photon_data_obj[i].get_multiplicity_tot_ene_data();
          xs_data  = photon_data_obj[i].get_multiplicity_tot_data();

          calc_non_reso_xs( 12, mt_no, sig_tmp, nbt_e, int_e, ene_data, xs_data );

          photon_data_obj[i].set_multiplicity_tot_range_data(nbt_e);
          photon_data_obj[i].set_multiplicity_tot_int_data(int_e);
          photon_data_obj[i].set_multiplicity_tot_ene_data(ene_data);
          photon_data_obj[i].set_multiplicity_tot_data(xs_data);

          if( static_cast<int>(photon_data_obj[i].get_multiplicity_binding_ene_flg().size()) == 1 )
          {
            nbt_e_array.push_back(nbt_e);
            int_e_array.push_back(int_e);
            ene_data_array.push_back(ene_data);
            xs_data_array.push_back(xs_data);
            photon_data_obj[i].set_multiplicity_range_data(nbt_e_array);
            photon_data_obj[i].set_multiplicity_int_data(int_e_array);
            photon_data_obj[i].set_multiplicity_ene_data(ene_data_array);
            photon_data_obj[i].set_multiplicity_data(xs_data_array);

            clr_obj.clear_vec_array2_int(nbt_e_array);
            clr_obj.clear_vec_array2_int(int_e_array);
            clr_obj.clear_vec_array2_real(ene_data_array);
            clr_obj.clear_vec_array2_real(xs_data_array);
          }
        }
        sig_tmp.clear();
        nbt_e.clear();
        int_e.clear();
        ene_data.clear();
        xs_data.clear();
      }

      //Photon production cross section (PhotonDataContainer, MF=13)
      if( nrl_obj.check_mf_mt(13, mt_no,
                              inelastic_scat_xs_flg, fission_xs_flg, photoelectric_xs_flg) == 0 )
      {
        nbt_e = photon_data_obj[i].get_photon_production_xs_tot_range_data();
        if( static_cast<int>(nbt_e.size()) > 0 )
        {
          int_e    = photon_data_obj[i].get_photon_production_xs_tot_int_data();
          ene_data = photon_data_obj[i].get_photon_production_xs_tot_ene_data();
          xs_data  = photon_data_obj[i].get_photon_production_xs_tot_data();

          calc_non_reso_xs( 13, mt_no, sig_tmp, nbt_e, int_e, ene_data, xs_data );

          photon_data_obj[i].set_photon_production_xs_tot_range_data(nbt_e);
          photon_data_obj[i].set_photon_production_xs_tot_int_data(int_e);
          photon_data_obj[i].set_photon_production_xs_tot_ene_data(ene_data);
          photon_data_obj[i].set_photon_production_xs_tot_data(xs_data);
        }
        sig_tmp.clear();
        nbt_e.clear();
        int_e.clear();
        ene_data.clear();
        xs_data.clear();
      }

      //Smooth photon interaction cross section (PhotonDataContainer, MF=23)
      if( nrl_obj.check_mf_mt(23, mt_no,
                              inelastic_scat_xs_flg, fission_xs_flg, photoelectric_xs_flg) == 0 )
      {
        nbt_e = photon_data_obj[i].get_photon_interaction_xs_range_data();
        if( static_cast<int>(nbt_e.size()) > 0 )
        {
          int_e    = photon_data_obj[i].get_photon_interaction_xs_int_data();
          ene_data = photon_data_obj[i].get_photon_interaction_xs_ene_data();
          xs_data  = photon_data_obj[i].get_photon_interaction_xs_data();

          calc_non_reso_xs( 23, mt_no, sig_tmp, nbt_e, int_e, ene_data, xs_data );

          photon_data_obj[i].set_photon_interaction_xs_range_data(nbt_e);
          photon_data_obj[i].set_photon_interaction_xs_int_data(int_e);
          photon_data_obj[i].set_photon_interaction_xs_ene_data(ene_data);
          photon_data_obj[i].set_photon_interaction_xs_data(xs_data);

          //Add total and elastic scatter cross sections
          vector<int> add_xs_type = check_add_photon_interaction_xs(reaction_type[i]);
          for(int j=0; j<static_cast<int>(add_xs_type.size()); j++)
          {
            add_non_reso_xs(sig_tmp, add_xs_type[j]);
          }
        }
        sig_tmp.clear();
        nbt_e.clear();
        int_e.clear();
        ene_data.clear();
        xs_data.clear();
      }
    }
  }
  nrl_obj.clear();

  nucl_reaction_data_obj.set_xs_data_obj(xs_data_obj);
  nucl_reaction_data_obj.set_radio_product_data_obj(radio_product_data_obj);
  nucl_reaction_data_obj.set_photon_data_obj(photon_data_obj);

  vector<CrossSectionDataContainer>().swap(xs_data_obj);
  vector<RadioactiveProductDataContainer>().swap(radio_product_data_obj);
  vector<PhotonDataContainer>().swap(photon_data_obj);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

vector<int> ReconstructXSMerger::check_add_xs(Integer mt)
{
  vector<int> chk_flg;
  chk_flg.clear();

  if( mt == unassigned_mt_no )
  {
    return chk_flg;
  }

  if( mt == 2 || mt == 19 || mt == 20 || mt == 21 || mt == 38 || mt == 102 )
  {
    chk_flg.push_back(static_cast<int>(total_xs));
    if( mt == 2 ) //mt = 2 : (z, elastic) - Elastic scattering cross section
    {
      chk_flg.push_back(static_cast<int>(scatter_xs));
    }
    else if( fission_xs_flg == 1 && (mt == 19 || mt == 20 || mt == 21 || mt == 38) ) //fission
    {
       //mt = 19 : (z,  f) - 1st chance fission cross section
       //mt = 20 : (z, nf) - 2nd chance fission cross section
       //mt = 21 : (z,2nf) - 3rd chance fission cross section
       //mt = 38 : (z,3nf) - 4th chance fission cross section
       chk_flg.push_back(static_cast<int>(fission_xs));
    }
    else if( mt == 102 ) 
    {
      //mt = 102 : (z,gam) - Radiation cross section
      chk_flg.push_back(static_cast<int>(radiation_xs));
    }
  }
  else if( fission_xs_flg == 0 && mt == 18 )
  {
    //mt = 18 : (z,f) - Total of fission cross section
    chk_flg.push_back(static_cast<int>(total_xs));
    chk_flg.push_back(static_cast<int>(fission_xs));
  }
  else if( mt == 10 )
  {
    //mt = 10 : (z,continuum)
  }
  else if( mt >= 46 && mt <= 49 )
  {
    //mt = 46-49 : Unassigned
  }
  else if( mt > 200 && mt < proton_xs_min )
  {
    //mt = 200 - 599 : Other data
  }
  else if (proton_xs_flg == 1 && mt >= proton_xs_min && mt <= proton_xs_max)
  {
  }
  else if (deuteron_xs_flg == 1 && mt >= deuteron_xs_min && mt <= deuteron_xs_max)
  {
  }
  else if (triton_xs_flg == 1 && mt >= triton_xs_min && mt <= triton_xs_max)
  {
  }
  else if (he_xs_flg == 1 && mt >= he_xs_min && mt <= he_xs_max)
  {
  }
  else if (alpha_xs_flg == 1 && mt >= alpha_xs_min && mt <= alpha_xs_max)
  {
  }
  else
  {
    chk_flg.push_back(static_cast<int>(total_xs));
  }
  return chk_flg;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

vector<int> ReconstructXSMerger::check_add_photon_interaction_xs(Integer mt)
{
  vector<int> chk_flg;
  chk_flg.clear();

  if( photon_interaction_xs_flg == 1 )
  {
    if( mt != 515 && mt != 517 )
    {
      //mt = 515 : Pair production, electron field
      //mt = 517 : Pair production
      chk_flg.push_back(static_cast<int>(total_xs));
    }
    if( mt >= 534 && mt <= 572 )
    {
      //mt = 534-572 : Various subshell photoelectric cross sections
      chk_flg.push_back(static_cast<int>(scatter_xs));
    }
  }
  return chk_flg;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ReconstructXSMerger::calc_non_reso_xs( vector<Real8>&   sig_data,
                                            vector<Integer>& nbt_e,    vector<Integer>& int_e, 
                                            vector<Real>&    ene_data, vector<Real>&    xs_data )

{
  calc_non_reso_xs( 0, 0, sig_data, nbt_e, int_e, ene_data, xs_data );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ReconstructXSMerger::calc_non_reso_xs( int mf_no, vector<Real8>&   sig_data,
                                            vector<Integer>& nbt_e,    vector<Integer>& int_e, 
                                            vector<Real>&    ene_data, vector<Real>&    xs_data )
{
  calc_non_reso_xs( mf_no, 0, sig_data, nbt_e, int_e, ene_data, xs_data );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ReconstructXSMerger::calc_non_reso_xs( int mf_no, int mt_no, vector<Real8>&   sig_data,
                                            vector<Integer>& nbt_e,    vector<Integer>& int_e, 
                                            vector<Real>&    ene_data, vector<Real>&    xs_data )
{
  int   i_max  = static_cast<int>(ene_data.size());
  Real8 el_val = static_cast<Real8>(ene_data[0]);
  Real8 eh_val = static_cast<Real8>(ene_data[i_max-1]);
  el_val = digit_obj.get_adjusted_value(el_val, sig_fig, -1.0);
  Real8 el_dif = -1.0 * min_ene_dif*el_val;
  Real8 eh_dif = -1.0 * min_ene_dif*eh_val;

  vector<Real> ene_new, sig_new;
  ene_new.clear();
  sig_new.clear();

  int     ele_no    = 1;
  int     ele_max   = static_cast<int>(ene_data.size());
  int     range     = 0;
  int     range_max = static_cast<int>(nbt_e.size());
  Integer int_val   = int_e[0];
  Real8   ene_pre, ene_cur, sig_pre, sig_cur;
  
  vector<Real> ene_remove, sig_remove;
  Real8        ene_val, ene_dif;
  ene_remove.clear();
  sig_remove.clear();

  i_max = static_cast<int>(ene_merge.size());
  sig_data.clear();
  sig_data.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    ene_val = ene_merge[i];
    ene_dif = ene_val*(1.0 - min_ene_dif);
    if( (ene_val - el_val) >= el_dif && (eh_val - ene_val) >= eh_dif )
    {
      //Search neightbor energy grid. (ene_data[ele_no-1] <= ene_val < ene_data[ele_no])
      while( ene_data[ele_no] <= ene_dif )
      {
        ele_no += 1;
        if( ele_no >= ele_max )
        {
          ele_no = ele_max - 1;
          break;
        }
      }
      ene_pre = static_cast<Real8>(ene_data[ele_no-1]);
      ene_cur = static_cast<Real8>(ene_data[ele_no]);
      sig_pre = static_cast<Real8>(xs_data[ele_no-1]);
      sig_cur = static_cast<Real8>(xs_data[ele_no]);

      //Search interpolation scheme
      while( nbt_e[range] < ele_no+1 )
      {
        range++;
        if( range >= range_max )
        {
          int_val = int_e[range_max-1];
          break;
        }
        else
        {
          int_val = int_e[range];
        }
      }

      ti_obj.interpolation_1d(int_val, ene_merge[i], sig_data[i], ene_pre, sig_pre, ene_cur, sig_cur);
      if( sig_data[i] < 0.0 && mf_no != 3 )
      {
        ene_remove.push_back(static_cast<Real>(ene_merge[i]));
        sig_remove.push_back(static_cast<Real>(sig_data[i]));
  
        sig_data[i] = 0.0;
      }

      ene_new.push_back(static_cast<Real>(ene_merge[i]));
      sig_new.push_back(static_cast<Real>(sig_data[i]));
    }
    else
    {
      sig_data[i] = 0.0;
    }
  }

  //Output warning message if minus cross sections are observed
  if( static_cast<int>(ene_remove.size()) > 0 )
  {
    string class_name = "ReconstructXSMerger";
    string func_name  = "calc_non_reso_xs";

    vector<string> err_com;
    ostringstream oss01, oss02;
    oss01 << mf_no;
    oss02 << mt_no;
    string str_data01 = "MF / MT : " + oss01.str() + " / " + oss02.str();
    string str_data02 = "  Minus cross sections are found.";
    string str_data03 = "  This cross section is modified to 0.0 barn.";
    string str_data04 = "  Minus cross section and its energy grid point (ene, sig)";
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);

    for(int j=0; j<static_cast<int>(ene_remove.size()); j++)
    {
      ostringstream oss03, oss04, oss05;
      oss04.precision(7);
      oss05.precision(7);
      oss04.setf(ios::showpoint);
      oss05.setf(ios::showpoint);
      oss04.setf(ios::scientific);
      oss05.setf(ios::scientific);

      oss03 << j+1;
      oss04 << ene_remove[j];
      oss05 << sig_remove[j];
      string str_data05 = "    " + oss03.str() + " : " + oss04.str() + ", " + oss05.str();
      err_com.push_back(str_data05);
    }
    err_obj.output_caution(class_name, func_name, err_com);
  }

  //Update ene_data and xs_data
  ene_data = ene_new;
  xs_data  = sig_new;

  //Reset interpolation scheme (all interpolation scheme is linear-linear)
  nbt_e.clear();
  int_e.clear();
  nbt_e.push_back(static_cast<Integer>(ene_new.size()));
  int_e.push_back(int_lin_lin); //linear-linear
  ene_new.clear();
  sig_new.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ReconstructXSMerger::add_non_reso_xs(vector<Real8>& sig_tmp, int xs_type)
{
  int i_max = static_cast<int>(ene_merge.size());
  for(int i=0; i<i_max; i++)
  {
    sig_merge[i][xs_type] += sig_tmp[i];
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ReconstructXSMerger::calc_total_inelastic_scat_xs()
{
  Integer         tot_inelastic_no  = -1;
  Integer         mod_inelastic_flg = -1;
  vector<Real>    ene_data, xs_data, ene_data_tmp, xs_data_tmp;

  int grid_no_max = static_cast<int>(ene_merge.size());
  ene_data = ene_merge;
  xs_data.resize(grid_no_max);
  for(int i=0; i<grid_no_max; i++)
  {
    xs_data[i]  = 0.0;
  }

  vector<CrossSectionDataContainer> xs_data_obj = nucl_reaction_data_obj.get_xs_data_obj();
  for(int i=0; i<reaction_type_no; i++)
  {
    if( reaction_type[i] == 4 )
    {
      //reaction_type = 4 : (z,n) - total of inelastic scattering xs (51-91)
      tot_inelastic_no = i;
    }
    else if( reaction_type[i] >= 51 && reaction_type[i] <= 91 )
    {
      mod_inelastic_flg = 1;

      //reaction_type = 51-91 : (z,n[n]) - excitation of n-th excited state
      ene_data_tmp = xs_data_obj[i].get_xs_ene_data();
      xs_data_tmp  = xs_data_obj[i].get_xs_data();

      int ele_no     = 0;
      int ele_no_max = static_cast<int>(xs_data_tmp.size());
      for(int j=0; j<grid_no_max; j++)
      {
        if( fabs(ene_data_tmp[ele_no] - ene_data[j]) < min_ene_dif*ene_data[j] )
        {
          xs_data[j] += xs_data_tmp[ele_no]; 
          ele_no++;
        }
      }
      if( ele_no != ele_no_max )
      {
        string class_name = "ReconstructXSMerger";
        string func_name  = "calc_total_inelastic_scat_xs()";

        vector<string> err_com;
        err_com.push_back("The energy grid of inelastic scatter xs is not unit.");

        err_obj.output_runtime_error(class_name, func_name, err_com);
      }
      ene_data_tmp.clear();
      xs_data_tmp.clear();
    }
  }

  if( mod_inelastic_flg >= 0 )
  {
    //Modify total inelastic scattering cross section
    vector<Integer> nbt_e_new, int_e_new;
    vector<Real>    ene_data_new, xs_data_new;
    ene_data_new = ene_data;
    xs_data_new  = xs_data;

    Integer nbt_val = static_cast<Integer>(ene_data_new.size());
    Integer int_val = int_lin_lin; //linear-linear
    nbt_e_new.push_back(nbt_val);
    int_e_new.push_back(int_val);

    ta_obj.remove_descending_order_data(nbt_e_new, int_e_new, ene_data_new, xs_data_new);
    ta_obj.remove_zero_data(nbt_e_new, int_e_new, ene_data_new, xs_data_new);

    if( tot_inelastic_no >= 0 )
    {
      xs_data_obj[tot_inelastic_no].set_xs_range_data(nbt_e_new);
      xs_data_obj[tot_inelastic_no].set_xs_int_data(int_e_new);
      xs_data_obj[tot_inelastic_no].set_xs_ene_data(ene_data_new);
      xs_data_obj[tot_inelastic_no].set_xs_data(xs_data_new);

      nucl_reaction_data_obj.set_xs_data_obj(reaction_type[tot_inelastic_no], xs_data_obj[tot_inelastic_no]);
    }
    else
    {
      CrossSectionDataContainer xs_data_obj_new;
      xs_data_obj_new.clear();

      xs_data_obj_new.set_reaction_type(4);

      xs_data_obj_new.set_xs_range_data(nbt_e_new);
      xs_data_obj_new.set_xs_int_data(int_e_new);
      xs_data_obj_new.set_xs_ene_data(ene_data_new);
      xs_data_obj_new.set_xs_data(xs_data_new);

      nucl_reaction_data_obj.set_xs_data_obj(xs_data_obj_new);
      xs_data_obj_new.clear();
    }
    nbt_e_new.clear();
    int_e_new.clear();
    ene_data_new.clear();
    xs_data_new.clear();
  }
  ene_data.clear();
  xs_data.clear();

  vector<CrossSectionDataContainer>().swap(xs_data_obj);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ReconstructXSMerger::add_reso_xs()
{
  vector<vector<Real> > el = nucl_data_obj.get_reso_data_obj().get_lower_ene_limit();
  vector<vector<Real> > eh = nucl_data_obj.get_reso_data_obj().get_upper_ene_limit();
  vector<vector<Integer> > reso_region_flg = nucl_data_obj.get_reso_data_obj().get_reso_region_flg();
  vector<vector<Integer> > self_shielding_flg;
  int i_max = static_cast<int>(reso_region_flg.size());
  self_shielding_flg.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(reso_region_flg[i].size());
    self_shielding_flg[i].resize(j_max);
    for(int j=0; j<j_max; j++)
    {
      self_shielding_flg[i][j] = 0;
      if( reso_region_flg[i][j] == 2 )
      {
        self_shielding_flg[i][j]
          = nucl_data_obj.get_reso_data_obj().get_unreso_data_obj(i,j).get_self_shielding_flg();
      }
    }
  }

  unify_reso_xs();
  int reso_max = static_cast<int>(ene_reso_uni.size());
      i_max    = static_cast<int>(ene_merge.size());

  if( reso_max <= 0 )
  {
    return;
  }

  vector<vector<Real> > sig_reso_uni_mod;
  int react_no = static_cast<int>(react_type_list_reso_uni.size());
  sig_reso_uni_mod.resize(react_no);
  for(int j=0; j<react_no; j++)
  {
    sig_reso_uni_mod[j].resize(reso_max);
    for(int i=0; i<reso_max; i++)
    {
      sig_reso_uni_mod[j][i] = sig_reso_uni[i][j];
    }
  }

  Real ene_reso_min = ene_reso_uni[0]          * (1.0 - min_ene_dif);
  Real ene_reso_max = ene_reso_uni[reso_max-1] * (1.0 + min_ene_dif);
  for(int i=0; i<i_max; i++)
  {
    if( ene_merge[i] < ene_reso_min )
    {
      continue;
    }
    if( ene_merge[i] > ene_reso_max )
    {
      break;
    }

    int reso_add_flg = 0;
    for(int p=0; p<static_cast<int>(reso_region_flg.size()); p++)
    {
      for(int q=0; q<static_cast<int>(reso_region_flg[p].size()); q++)
      {
        if( el[p][q] <= ene_merge[i] && ene_merge[i] <= eh[p][q] )
        {
          reso_add_flg = 1;
          if( self_shielding_flg[p][q] != 0 )
          {
            reso_add_flg = 0;
          }
        }
      }
    }
    if( reso_add_flg == 0 )
    {
      continue;
    }

    for(int j=0; j<react_no; j++)
    {
      Real sig_add = 0.0;
      ti_obj.interpolation_1d_in_range(int_lin_lin, ene_merge[i], sig_add,
                                       ene_reso_uni, sig_reso_uni_mod[j]);
      if( react_type_list_reso_uni[j] == 1 )
      {
        sig_merge[i][total_xs] += sig_add;
      }
      else if( react_type_list_reso_uni[j] == 2 )
      {
        sig_merge[i][scatter_xs] += sig_add;
      }
      else if( react_type_list_reso_uni[j] == 18 )
      {
        sig_merge[i][fission_xs] += sig_add;
      }
      else if( react_type_list_reso_uni[j] == 102 )
      {
        sig_merge[i][radiation_xs] += sig_add;
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ReconstructXSMerger::unify_reso_xs()
{
  vector<vector<Integer> > reso_region_flg = nucl_data_obj.get_reso_data_obj().get_reso_region_flg();
  vector<vector<Real> >    el              = nucl_data_obj.get_reso_data_obj().get_lower_ene_limit();
  vector<vector<Real> >    eh              = nucl_data_obj.get_reso_data_obj().get_upper_ene_limit();
  
  vector<Integer> ene_chk_el, ene_chk_eh;

  vector<Real8>          ene_data_tmp;
  vector<vector<Real8> > sig_data_tmp;

  unify_react_type_list();
  int react_type_no = static_cast<int>(react_type_list_reso_uni.size());
  
  ene_reso_uni.clear();
  clr_obj.clear_vec_array2_real8(sig_reso_uni);
  ene_data_tmp.clear();
  clr_obj.clear_vec_array2_real8(sig_data_tmp);
 
  int ele_min, ele_max, i_max;
  ele_min  = 0;
  i_max    = static_cast<int>(reso_region_flg.size());

  vector<vector<Integer> > self_shielding_flg;
  self_shielding_flg.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(reso_region_flg[i].size());
    self_shielding_flg[i].resize(j_max);
    for(int j=0; j<j_max; j++)
    {
      self_shielding_flg[i][j] = 0;
      if( reso_region_flg[i][j] == 2 )
      {
        self_shielding_flg[i][j]
          = nucl_data_obj.get_reso_data_obj().get_unreso_data_obj(i,j).get_self_shielding_flg();
      }

      if( reso_region_flg[i][j] == 2 && self_shielding_flg[i][j] == 1 )
      {
        continue;
      }

      ta_obj.add_grid_data(ene_reso_uni, ene_reso[i][j]);
    }
  }

  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(reso_region_flg[i].size());
    energy_bound_check(ene_chk_el, ene_chk_eh, el[i], eh[i], reso_region_flg[i], self_shielding_flg[i]);
    for(int j=0; j<j_max; j++)
    {
      if( reso_region_flg[i][j] == 2 && self_shielding_flg[i][j] == 1 )
      {
        continue;
      }

      int k_min = 0;
      int k_max = static_cast<int>(ene_reso[i][j].size());
      if( k_max > 0 )
      {
        Real8 el_dif = fabs((ene_reso[i][j][0]       - el[i][j])/el[i][j]);
        Real8 eh_dif = fabs((ene_reso[i][j][k_max-1] - eh[i][j])/eh[i][j]);

        if( ene_chk_el[j] < 0 && el_dif<=min_ene_dif )
        {
          k_min = 1;
        }
        if( ene_chk_eh[j] < 0 && eh_dif<=min_ene_dif )
        {
          k_max--;
        }
    
        vector<vector<Real8> > sig_mod = modify_sig_reso_with_unify_react_type_list
                                           (sig_reso[i][j], react_type_list_reso[i][j]);
        for(int k=k_min; k<k_max; k++)
        {
          ene_data_tmp.push_back(ene_reso[i][j][k]);
          sig_data_tmp.push_back(sig_mod[k]);
        }
        sig_mod.clear();
    
        if( ene_chk_el[j] > 0 && el_dif<=min_ene_dif )
        {
          for(int l=0; l<react_type_no; l++)
          {
            sig_data_tmp[ele_min][l] = 0.5*sig_data_tmp[ele_min][l];
          }
        }
        ele_max = static_cast<int>(sig_data_tmp.size()) - 1;
        if( ene_chk_eh[j] > 0 && eh_dif<=min_ene_dif )
        {
          for(int l=0; l<react_type_no; l++)
          {
            sig_data_tmp[ele_max][l] = 0.5*sig_data_tmp[ele_max][l];
          }
        }
        ele_min = ele_max + 1;
      }
    }

    if( static_cast<int>(ene_reso_uni.size()) != static_cast<int>(ene_data_tmp.size()) )
    {
      string class_name = "ReconstructXSMerger";
      string func_name  = "unify_reso_xs()";

      ostringstream oss01, oss02, oss03, oss04;
      oss01 << i+1;
      oss02 << static_cast<int>(reso_region_flg.size());
      oss03 << ene_reso_uni.size();
      oss04 << ene_data_tmp.size();
      string str_data01 = "Number of isotopes (NIS)  : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "Energy grid number        : " + oss03.str();
      string str_data03 = "Energy grid number at i=" + oss01.str() + " : " + oss04.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back("Resonance energy grid number is different in each isotope.");
      err_obj.output_caution(class_name, func_name, err_com);

      vector<Real8>          sig_data_tmp_add;
      vector<vector<Real8> > sig_data_tmp_mod;

      sig_data_tmp_add.resize(react_type_no);
      for(int j=0; j<react_type_no; j++)
      {
        sig_data_tmp_add[j] = 0.0;
      }

      int ele_no  = 0;
      ele_max = static_cast<int>(ene_data_tmp.size());
      j_max   = static_cast<int>(ene_reso_uni.size());
      sig_data_tmp_mod.resize(j_max);
      for(int j=0; j<j_max; j++)
      {
        sig_data_tmp_mod[j] = sig_data_tmp_add;

        if( ele_no < ele_max )
        {
          while( fabs(ene_data_tmp[ele_no] - ene_reso_uni[j]) < min_ene_dif * ene_reso_uni[j] )
          {
            for(int k=0; k<react_type_no; k++)
            {
              sig_data_tmp_mod[j][k] += sig_data_tmp[ele_no][k];
            }
            ele_no++;

            if( ele_no == ele_max )
            {
              break;
            }
          } 
        } 
      }
      ene_data_tmp = ene_reso_uni;
      sig_data_tmp = sig_data_tmp_mod;
      sig_data_tmp_add.clear();
      clr_obj.clear_vec_array2_real8(sig_data_tmp_mod);
    }

    if( static_cast<int>(sig_reso_uni.size()) == 0 )
    {
      sig_reso_uni = sig_data_tmp;
      ene_data_tmp.clear();
      clr_obj.clear_vec_array2_real8(sig_data_tmp);
      continue;
    }

    j_max = static_cast<int>(ene_data_tmp.size());
    for(int j=0; j<j_max; j++)
    {
      if( fabs(ene_reso_uni[j] - ene_data_tmp[j]) > min_ene_dif*ene_reso_uni[j] )
      {
        string class_name = "ReconstructXSMerger";
        string func_name  = "unify_reso_xs()";

        ostringstream oss01, oss02, oss03, oss04, oss05, oss06;
        oss01 << i+1;
        oss02 << static_cast<int>(reso_region_flg.size());
        oss03 << j+1;
        oss04 << static_cast<int>(ene_data_tmp.size());
        oss05 << ene_reso_uni[j];
        oss06 << ene_data_tmp[j];
        string str_data01 = "Number of isotopes (NIS) : " + oss01.str() + " / " + oss02.str();
        string str_data02 = "Grid number              : " + oss03.str() + " / " + oss04.str();
        string str_data03 = "Energy at i=0            : " + oss05.str();
        string str_data04 = "Energy at i=" + oss01.str() + " : " + oss06.str();

        vector<string> err_com;
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back(str_data04);
        err_com.push_back("Resonance energy is different in each isotope.");

        err_obj.output_runtime_error(class_name, func_name, err_com);
      }

      for(int k=0; k<react_type_no; k++)
      {
        sig_reso_uni[j][k] += sig_data_tmp[j][k];
      }
    }
    ene_data_tmp.clear();
    clr_obj.clear_vec_array2_real8(sig_data_tmp);
  }

  clr_obj.clear_vec_array2_int(reso_region_flg);
  clr_obj.clear_vec_array2_int(self_shielding_flg);
  clr_obj.clear_vec_array2_real(el);
  clr_obj.clear_vec_array2_real(eh);
  ene_chk_el.clear();
  ene_chk_eh.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ReconstructXSMerger::unify_react_type_list()
{
  int i_max = static_cast<int>(react_type_list_reso.size());
  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(react_type_list_reso[i].size());
    for(int j=0; j<j_max; j++)
    {
      if( i==0 && j==0 )
      {
        react_type_list_reso_uni = react_type_list_reso[i][j];
        q_val_reso_uni           = q_val_reso[i][j];
        continue;
      }

      int k_max = static_cast<int>(react_type_list_reso[i][j].size());
      int l_max = static_cast<int>(react_type_list_reso_uni.size());
      for(int k=0; k<k_max; k++)
      {
        Integer add_flg   = 0;
        Integer react_val = react_type_list_reso[i][j][k];
        for(int l=0; l<l_max; l++)
        {
          if( react_type_list_reso_uni[l] == react_val )
          {
            add_flg = 1;
            break;
          }
        }

        if( add_flg == 0 )
        {
          react_type_list_reso_uni.push_back(react_val);
          q_val_reso_uni.push_back(q_val_reso[i][j][k]);
        }
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ReconstructXSMerger::energy_bound_check(vector<Integer>& ene_chk_el, vector<Integer>& ene_chk_eh,
                            vector<Real>&    el,              vector<Real>&    eh,
                            vector<Integer>& reso_region_flg, vector<Integer>& self_shielding_flg)
{
  Real ene_val;

  int i_max = static_cast<int>(eh.size());
  ene_chk_el.resize(i_max);
  ene_chk_eh.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    ene_chk_el[i] = 0;
    ene_chk_eh[i] = 0;
  }

  for(int i=0; i<i_max; i++)
  {
    ene_val = eh[i];
    for(int ii=i+1; ii<i_max; ii++)
    {
      if( fabs(ene_val - el[ii]) <= min_ene_dif*ene_val )
      {
        if( reso_region_flg[i] == 0 || reso_region_flg[i] == 1 )
        {
          if( reso_region_flg[ii] == 0 || reso_region_flg[ii] == 1 )
          {
            ene_chk_eh[i]++;
            ene_chk_el[ii]++;
          }
          else if( reso_region_flg[ii] == 2 )
          {
            if( self_shielding_flg[ii] == 0 )
            {
              ene_chk_el[ii]--;
            }
          }
        }
        else if(reso_region_flg[i] == 2 )
        {
          if( self_shielding_flg[i] == 0 )
          {
            if( reso_region_flg[ii] == 0 || reso_region_flg[ii] == 1 )
            {
              ene_chk_eh[i]--;
            }
            else if( reso_region_flg[ii] == 2 )
            {
              if( self_shielding_flg[ii] == 0 )
              {
                ene_chk_eh[i]++;
                ene_chk_el[ii]++;
              }
            }
          }
        }
      
        if( el[ii] - ene_val < -1.0e-5*ene_val)
        {
          string class_name = "ReconstructXSMerger";
          string func_name  = "energy_bound_check(vector<Integer>& ene_chk_el, vector<Integer>& ene_chk_eh, ";
                 func_name += "vector<Real>& el, vector<Real>& eh, ";
                 func_name += "vector<Integer>& reso_region_flg, vector<Integer>& self_shielding_flg)";

          ostringstream oss01, oss02, oss03, oss04, oss05, oss06;
          oss01 << i;
          oss02 << static_cast<int>(eh.size());
          oss03 << ene_val;
          oss04 << ii;
          oss05 << el[ii];
          string str_data01 = "Resonance region number  : " + oss01.str() + " / " + oss02.str();
          string str_data02 = "Upper energy grid at i=" + oss01.str() + " : " + oss03.str();
          string str_data03 = "Lower energy grid at i=" + oss04.str() + " : " + oss05.str();

          vector<string> err_com;
          err_com.push_back(str_data01);
          err_com.push_back(str_data02);
          err_com.push_back(str_data03);
          err_com.push_back("Resonance regions were overlaped.");
          err_com.push_back("Please check nuclear data.");

          err_obj.output_runtime_error(class_name, func_name, err_com);
        }
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

vector<vector<Real8> > ReconstructXSMerger::modify_sig_reso_with_unify_react_type_list
                                     (vector<vector<Real8> >& sig_data, vector<Integer>& react_type_data)
{
  int ene_no           = static_cast<int>(sig_data.size());
  int type_list_no_uni = static_cast<int>(react_type_list_reso_uni.size());
  int type_list_no     = static_cast<int>(react_type_data.size());

  vector<vector<Real8> > sig_mod;
  sig_mod.clear();
  if( ene_no == 0 )
  {
    return sig_mod;
  }

  sig_mod.resize(ene_no);
  for(int i=0; i<ene_no; i++)
  {
    sig_mod[i].resize(type_list_no_uni);
    for(int j=0; j<type_list_no_uni; j++)
    {
      sig_mod[i][j] = 0.0;
    }
  }

  for(int i=0; i<type_list_no_uni; i++)
  {
    Integer react_val = react_type_list_reso_uni[i];
    for(int j=0; j<type_list_no; j++)
    {
      if( react_type_data[j] == react_val )
      {
        for(int k=0; k<ene_no; k++)
        {
          sig_mod[k][i] = sig_data[k][j];
        }
        break;
      }
    }
  }

  return sig_mod;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ReconstructXSMerger::delete_unnecessary_xs()
{
  vector<Real8>          ene_data;
  vector<vector<Real8> > sig_data;
  ene_data.clear();
  clr_obj.clear_vec_array2_real8(sig_data);

  int i_max = static_cast<int>(ene_merge.size());
  Integer sig_chk_flg;
  for(int i=0; i<i_max-1; i++)
  {
    sig_chk_flg = 0;
    if( fabs(ene_merge[i+1] - ene_merge[i]) <= min_ene_dif*ene_merge[i+1] )
    {
      if( sig_merge[i][total_xs] < min_sig_val || sig_merge[i][scatter_xs] < min_sig_val )
      {
        sig_chk_flg = -1;
      }
    }

    if( sig_chk_flg == 0 )
    {
      ene_data.push_back(ene_merge[i]);
      sig_data.push_back(sig_merge[i]);
    }
  }

  //Check last energy group
  if( fabs(ene_merge[i_max-1] - ene_merge[i_max-2]) > min_ene_dif*ene_merge[i_max-1] )
  {
    if( sig_merge[i_max-1][total_xs] > min_sig_val && sig_merge[i_max-1][scatter_xs] > min_sig_val )
    {
      ene_data.push_back(ene_merge[i_max-1]);
      sig_data.push_back(sig_merge[i_max-1]);
    }
  }
  ene_merge.clear();
  clr_obj.clear_vec_array2_real8(sig_merge);

  ene_merge = ene_data;
  sig_merge = sig_data;
  ene_data.clear();
  clr_obj.clear_vec_array2_real8(sig_data);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ReconstructXSMerger::delete_el_and_eh()
{
  //In NonResonanceEnergyGridLinearizer class, lower and upper energy limit (el and eh) was deleted.
  //Therefore, resonance cross section in el-ene_reso[0] and ene_reso[max]-eh is not appropriate value.
  //For these reasons, el-ene_reso[0] and ene_reso[max]-eh is not added in this class.

  vector<Real8>          ene_data;
  vector<vector<Real8> > sig_data;
  ene_data.clear();
  clr_obj.clear_vec_array2_real8(sig_data);

  vector<vector<Real> > el = nucl_data_obj.get_reso_data_obj().get_lower_ene_limit();
  vector<vector<Real> > eh = nucl_data_obj.get_reso_data_obj().get_upper_ene_limit();

  vector<Real8> ene_skip_min, ene_skip_max;
  int i_max = static_cast<int>(el.size());
  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(el[i].size());
    for(int j=0; j<j_max; j++)
    {
      ene_skip_min.push_back(static_cast<Real8>(el[i][j]) - min_ene_dif);
      ene_skip_max.push_back(static_cast<Real8>(el[i][j]) + min_ene_dif);

      ene_skip_min.push_back(static_cast<Real8>(eh[i][j]) - min_ene_dif);
      ene_skip_max.push_back(static_cast<Real8>(eh[i][j]) + min_ene_dif);
    }
  }

          i_max    = static_cast<int>(ene_merge.size());
  int     skip_max = static_cast<int>(ene_skip_min.size());
  Integer skip_flg;
  for(int i=0; i<i_max; i++)
  {
    skip_flg = 0;
    if( i != 0 && i != i_max-1 )
    {
      for(int j=0; j<skip_max; j++)
      {
        if( ene_merge[i] >= ene_skip_min[j] && ene_merge[i] <= ene_skip_max[j] )
        {
          skip_flg = -1;
          break;
        }
      }
    }

    if( skip_flg == 0 )
    {
      ene_data.push_back(ene_merge[i]);
      sig_data.push_back(sig_merge[i]);
    }
  }
  ene_merge.clear();
  clr_obj.clear_vec_array2_real8(sig_merge);

  ene_merge = ene_data;
  sig_merge = sig_data;

  clr_obj.clear_vec_array2_real(el);
  clr_obj.clear_vec_array2_real(eh);
  ene_data.clear();
  clr_obj.clear_vec_array2_real8(sig_data);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ReconstructXSMerger::add_el_and_eh()
{
  vector<Real8>          ene_data;
  vector<vector<Real8> > sig_data;
  ene_data.clear();
  clr_obj.clear_vec_array2_real8(sig_data);

  vector<vector<Real> > el = nucl_data_obj.get_reso_data_obj().get_lower_ene_limit();
  vector<vector<Real> > eh = nucl_data_obj.get_reso_data_obj().get_upper_ene_limit();

  vector<Real8> ene_add_el, ene_add_el_min, ene_add_el_max,
                ene_add_eh, ene_add_eh_min, ene_add_eh_max;
  Real          ene_resolve_eh = nucl_data_obj.get_reso_data_obj().get_eh_reso();
  Real          ene_unreso_el  = nucl_data_obj.get_reso_data_obj().get_el_unreso();
  int i_max = static_cast<int>(el.size());
  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(el[i].size());
    for(int j=0; j<j_max; j++)
    {
      ene_add_el.push_back(el[i][j]);
      ene_add_el_min.push_back(static_cast<Real8>(el[i][j]) - min_ene_dif);
      ene_add_el_max.push_back(static_cast<Real8>(el[i][j]) + min_ene_dif);

      ene_add_eh.push_back(eh[i][j]);
      ene_add_eh_min.push_back(static_cast<Real8>(eh[i][j]) - min_ene_dif);
      ene_add_eh_max.push_back(static_cast<Real8>(eh[i][j]) + min_ene_dif);
    }
  }

          i_max   = static_cast<int>(ene_merge.size());
  int     add_max = static_cast<int>(ene_add_el_min.size());
  Integer add_flg          = -1;
  Integer add_boundary_flg = -1;
  Real8 ene_add_el_pre     = 0.0;
  Real8 ene_add_eh_pre     = 0.0;
  for(int i=0; i<i_max; i++)
  {
    add_flg          = -1;
    add_boundary_flg = -1;
    if( i != 0 && i != i_max-1 )
    {
      for(int j=0; j<add_max; j++)
      {
        if( (ene_merge[i] >= ene_add_el_min[j] && ene_merge[i] <= ene_add_el_max[j]) ||
            (ene_merge[i] >= ene_add_eh_min[j] && ene_merge[i] <= ene_add_eh_max[j]) )
        {
          add_flg = j;

          if( ene_merge[i] >= ene_add_eh_min[j] && ene_merge[i] <= ene_add_eh_max[j]    &&
              fabs(ene_add_eh[j] - ene_resolve_eh) < fabs(min_ene_dif * ene_resolve_eh) &&
              fabs(ene_add_eh[j] - ene_unreso_el)  < fabs(min_ene_dif * ene_unreso_el) )
          {
            add_boundary_flg = j;
          }
          break;
        }
      }
    }

    if( add_flg < 0 )
    {
      ene_data.push_back(ene_merge[i]);
      sig_data.push_back(sig_merge[i]);
    }
    else if( add_boundary_flg >= 0 )
    {
      //Add boundary of resolved and unresolved resonance region
      //Add highest energy at resolved resonance region
      ene_data.push_back(ene_resolve_eh);
      if( i <= 1 )
      {
        sig_data.push_back(sig_merge[i]);
      }
      else
      {
        int k_max = static_cast<int>(sig_merge[i].size());
        vector<Real8> sig_new;
        sig_new.resize(k_max);
        for(int k=0; k<k_max; k++)
        {
          ti_obj.interpolation_1d(int_lin_lin, ene_resolve_eh, sig_new[k],
                                  ene_merge[i-2], sig_merge[i-2][k],
                                  ene_merge[i-1], sig_merge[i-1][k]);
        }
        sig_data.push_back(sig_new);
        sig_new.clear();
      }

      //Add lowest energy at unresolved resonance region
      ene_data.push_back(ene_unreso_el);
      if( i >= i_max-2 )
      {
        sig_data.push_back(sig_merge[i+1]);
      }
      else
      {
        int k_max = static_cast<int>(sig_merge[i].size());
        vector<Real8> sig_new;
        sig_new.resize(k_max);
        for(int k=0; k<k_max; k++)
        {
          ti_obj.interpolation_1d(int_lin_lin, ene_unreso_el, sig_new[k],
                                  ene_merge[i+1], sig_merge[i+1][k],
                                  ene_merge[i+2], sig_merge[i+2][k]);
        }
        sig_data.push_back(sig_new);
        sig_new.clear();
      }
    }
    else
    {
      if( ene_merge[i] >= ene_add_eh_min[add_flg] &&
          ene_merge[i] <= ene_add_eh_max[add_flg] )
      {
        if( fabs(ene_add_eh[add_flg] - ene_add_eh_pre) < fabs(min_ene_dif*ene_add_eh_pre) )
        {
          continue;
        }
        ene_add_eh_pre = ene_add_eh[add_flg];

        ene_data.push_back(ene_add_eh[add_flg]);
        if( i <= 1 )
        {
          sig_data.push_back(sig_merge[i]);
        }
        else
        {
          int k_max = static_cast<int>(sig_merge[i].size());
          vector<Real8> sig_new;
          sig_new.resize(k_max);
          for(int k=0; k<k_max; k++)
          {
            ti_obj.interpolation_1d(int_lin_lin, ene_add_eh[add_flg], sig_new[k],
                                    ene_merge[i-2], sig_merge[i-2][k],
                                    ene_merge[i-1], sig_merge[i-1][k]);
          }
          sig_data.push_back(sig_new);
          sig_new.clear();
        }
      }

      if( ( ene_merge[i] >= ene_add_el_min[add_flg] &&
            ene_merge[i] <= ene_add_el_max[add_flg] ) ||
          ( ene_merge[i] >= ene_add_eh_min[add_flg] &&
            ene_merge[i] <= ene_add_eh_max[add_flg] && add_flg == add_max - 1 ) )
      {
        Real8 ene_add_val = ene_add_el[add_flg];
        if( ene_merge[i] >= ene_add_eh_min[add_flg] &&
            ene_merge[i] <= ene_add_eh_max[add_flg] && add_flg == add_max - 1 )
        {
          ene_add_val = ene_add_eh[add_flg];
        }

        if( fabs(ene_add_val - ene_add_el_pre) < fabs(min_ene_dif*ene_add_el_pre) )
        {
          continue;
        }
        ene_add_el_pre = ene_add_val;

        ene_data.push_back(ene_add_val);

        if( i >= i_max-2 )
        {
          sig_data.push_back(sig_merge[i+1]);
        }
        else
        {
          int k_max = static_cast<int>(sig_merge[i].size());
          vector<Real8> sig_new;
          sig_new.resize(k_max);
          for(int k=0; k<k_max; k++)
          {
            ti_obj.interpolation_1d(int_lin_lin, ene_add_val, sig_new[k],
                                    ene_merge[i+1], sig_merge[i+1][k],
                                    ene_merge[i+2], sig_merge[i+2][k]);
          }
          sig_data.push_back(sig_new);
          sig_new.clear();
        }
      }
    }
  }
  ene_merge.clear();
  clr_obj.clear_vec_array2_real8(sig_merge);

  ene_merge = ene_data;
  sig_merge = sig_data;

  clr_obj.clear_vec_array2_real(el);
  clr_obj.clear_vec_array2_real(eh);
  ene_data.clear();
  clr_obj.clear_vec_array2_real8(sig_data);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ReconstructXSMerger::mod_first_chance_fission_xs()
{
// If first chance fission cross section (MT=19) is exsit and cross section value is 0.0,
// cross section is changed to cross section of MT=18.

  vector<CrossSectionDataContainer> xs_data_obj = nucl_reaction_data_obj.get_xs_data_obj();

  int i_max   = static_cast<int>(xs_data_obj.size());
  int mod_flg = -1;
  int second_fis_flg = -1;
  int third_fis_flg  = -1;
  int forth_fis_flg  = -1;
  for(int i=0; i<i_max; i++)
  {
    int react_no = xs_data_obj[i].get_reaction_type();
    if( react_no == 19 )
    {
      mod_flg = i;
    }
    else if( react_no == 20 || react_no == 21 || react_no == 38 )
    {
      vector<Real> xs_vec = xs_data_obj[i].get_xs_data();

      int xs_flg = -1;
      int j_max = static_cast<int>(xs_vec.size());
      for(int j=0; j<j_max; j++)
      {
        if( xs_vec[j] > min_value )
        {
          xs_flg = j;
          break;
        }
      }
      xs_vec.clear();

      if( xs_flg < 0 )
      {
        continue;
      }

      if( react_no == 20 )
      {
        second_fis_flg = i;
      }
      else if( react_no == 21 )
      {
        third_fis_flg = i;
      }
      else if( react_no == 38 )
      {
        forth_fis_flg = i;
      }
    }
  }

  for(int i=0; i<static_cast<int>(react_type_list_reso_uni.size()); i++)
  {
    if( react_type_list_reso_uni[i] == 19 )
    {
      mod_flg = -1;
    }
  }

  if( mod_flg < 0 )
  {
    return;
  }

  int other_fis_flg = second_fis_flg;
  if( second_fis_flg < 0 && third_fis_flg >= 0 )
  {
    other_fis_flg = third_fis_flg;
  }
  else if( second_fis_flg < 0 && third_fis_flg < 0 && forth_fis_flg >= 0 )
  {
    other_fis_flg = forth_fis_flg;
  }

  for(int i=0; i<i_max; i++)
  {
    if( xs_data_obj[i].get_reaction_type() == 18 )
    {
      CrossSectionDataContainer xs_data_obj_fis_1st = xs_data_obj[mod_flg];
      vector<Integer> xs_int_data_fis_1st   = xs_data_obj_fis_1st.get_xs_int_data();
      vector<Integer> xs_range_data_fis_1st = xs_data_obj_fis_1st.get_xs_range_data();
      vector<Real>    xs_ene_data_fis_1st   = xs_data_obj_fis_1st.get_xs_ene_data();
      vector<Real>    xs_data_fis_1st       = xs_data_obj_fis_1st.get_xs_data();

      if( other_fis_flg < 0 )
      {
        xs_int_data_fis_1st   = xs_data_obj[i].get_xs_int_data();
        xs_range_data_fis_1st = xs_data_obj[i].get_xs_range_data();
        xs_ene_data_fis_1st   = xs_data_obj[i].get_xs_ene_data();
        xs_data_fis_1st       = xs_data_obj[i].get_xs_data();
      }
      else
      {
        CrossSectionDataContainer xs_data_obj_fis_1st = xs_data_obj[mod_flg];
        vector<Integer> xs_int_data_fis_1st   = xs_data_obj_fis_1st.get_xs_int_data();
        vector<Integer> xs_range_data_fis_1st = xs_data_obj_fis_1st.get_xs_range_data();
        vector<Real>    xs_ene_data_fis_1st   = xs_data_obj_fis_1st.get_xs_ene_data();
        vector<Real>    xs_data_fis_1st       = xs_data_obj_fis_1st.get_xs_data();

        vector<Real> xs_ene_other = xs_data_obj[other_fis_flg].get_xs_ene_data();
        vector<Real> xs_other     = xs_data_obj[other_fis_flg].get_xs_data();

        Real mod_ene = -1.0;
        int j_max = static_cast<int>(xs_other.size());
        for(int j=0; j<j_max; j++)
        {
          if( xs_other[j] > min_value )
          {
            mod_ene = xs_ene_other[j];
            break;
          }
        }

        if( mod_ene > 0.0 )
        {
          vector<Real> xs_ene_data_mod = xs_data_obj[i].get_xs_ene_data();
          vector<Real> xs_data_mod     = xs_data_obj[i].get_xs_data();

          j_max = static_cast<int>(xs_ene_data_mod.size());
          for(int j=0; j<j_max; j++)
          {
            if( xs_ene_data_mod[j] > mod_ene - min_ene_dif )
            {
              ti_obj.interpolation_tab1_in_range(xs_ene_data_mod[j],    xs_data_mod[j],
                                                 xs_range_data_fis_1st, xs_int_data_fis_1st,
                                                 xs_ene_data_fis_1st,   xs_data_fis_1st);
            }
          }

          xs_int_data_fis_1st.resize(1);
          xs_range_data_fis_1st.resize(1);
          xs_int_data_fis_1st[0]   = int_lin_lin;
          xs_range_data_fis_1st[0] = j_max;
          xs_ene_data_fis_1st      = xs_ene_data_mod;
          xs_data_fis_1st          = xs_data_mod;
        }

        xs_data_obj_fis_1st.set_xs_int_data(xs_int_data_fis_1st);
        xs_data_obj_fis_1st.set_xs_range_data(xs_range_data_fis_1st);
        xs_data_obj_fis_1st.set_xs_ene_data(xs_ene_data_fis_1st);
        xs_data_obj_fis_1st.set_xs_data(xs_data_fis_1st);

        xs_data_obj[mod_flg] = xs_data_obj_fis_1st;
        xs_int_data_fis_1st.clear();
        xs_range_data_fis_1st.clear();
        xs_ene_data_fis_1st.clear();
        xs_data_fis_1st.clear();
        xs_other.clear();
      }
    }
  }

  nucl_reaction_data_obj.set_xs_data_obj(xs_data_obj);
  vector<CrossSectionDataContainer>().swap(xs_data_obj);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ReconstructXSMerger::mod_tot_prod_xs()
{
  int tot_prod_mt_no = 5; //proton, deuteron, triton, he-3, alpha
  vector<vector<Integer> >          mt_list_tot_prod;
  vector<Integer>                   tot_prod_xs_flg;
  vector<CrossSectionDataContainer> xs_obj_tot_prod, xs_obj_tot_prod_ori;
  vector<int>                       part_flg, tot_flg;

  //For initialization
  vector<Integer> int_vec, nbt_vec;
  vector<Real>    ene_vec, xs_vec;
  ene_vec = nucl_reaction_data_obj.get_xs_data_obj(1).get_xs_ene_data();

  int ene_no = static_cast<int>(ene_vec.size());
  int_vec.resize(1);
  nbt_vec.resize(1);
  int_vec[0] = int_lin_lin;
  nbt_vec[0] = ene_no;

  xs_vec.resize(ene_no);
  for(int i=0; i<ene_no; i++)
  {
    xs_vec[i] = 0.0;
  }

  mt_list_tot_prod.resize(tot_prod_mt_no);
  tot_prod_xs_flg.resize(tot_prod_mt_no);
  xs_obj_tot_prod.resize(tot_prod_mt_no);
  xs_obj_tot_prod_ori.resize(tot_prod_mt_no);
  part_flg.resize(tot_prod_mt_no);
  tot_flg.resize(tot_prod_mt_no);
  for(int i=0; i<tot_prod_mt_no; i++)
  {
    part_flg[i] = 0;
    tot_flg[i]  = 0;

    mt_list_tot_prod[i].clear();
    xs_obj_tot_prod[i].clear();
    xs_obj_tot_prod_ori[i].clear();

    int mt_tot_prod = 103; //i==0
    if( i==1 )
    {
      mt_tot_prod = 104;
    }
    else if( i==2 )
    {
      mt_tot_prod = 105;
    }
    else if( i==3 )
    {
      mt_tot_prod = 106;
    }
    else if( i==4 )
    {
      mt_tot_prod = 107;
    }
    xs_obj_tot_prod[i].set_reaction_type(mt_tot_prod);
    xs_obj_tot_prod_ori[i].set_reaction_type(mt_tot_prod);

    xs_obj_tot_prod[i].set_xs_int_data(int_vec);
    xs_obj_tot_prod[i].set_xs_range_data(nbt_vec);
    xs_obj_tot_prod[i].set_xs_ene_data(ene_vec);
    xs_obj_tot_prod[i].set_xs_data(xs_vec);
  }

  tot_prod_xs_flg[0] = proton_xs_flg;
  tot_prod_xs_flg[1] = deuteron_xs_flg;
  tot_prod_xs_flg[2] = triton_xs_flg;
  tot_prod_xs_flg[3] = he_xs_flg;
  tot_prod_xs_flg[4] = alpha_xs_flg;

  //Copy total production xs and sum of partial production xs
  vector<CrossSectionDataContainer> xs_data_obj = nucl_reaction_data_obj.get_xs_data_obj();
  int xs_obj_no = static_cast<int>(xs_data_obj.size());
  for(int i=0; i<xs_obj_no; i++)
  {
    Integer mt = xs_data_obj[i].get_reaction_type();
    for(int j=0; j<tot_prod_mt_no; j++)
    {
      if( mt == xs_obj_tot_prod_ori[j].get_reaction_type() )
      {
        tot_flg[j]++;
        xs_obj_tot_prod_ori[j] = xs_data_obj[i];
      }
    }

    if (mt >= proton_xs_min && mt <= proton_xs_max)
    {
      part_flg[0]++;
      sum_part_xs(xs_obj_tot_prod[0], xs_data_obj[i]);
    }
    else if (mt >= deuteron_xs_min && mt <= deuteron_xs_max)
    {
      part_flg[1]++;
      sum_part_xs(xs_obj_tot_prod[1], xs_data_obj[i]);
    }
    else if (mt >= triton_xs_min && mt <= triton_xs_max)
    {
      part_flg[2]++;
      sum_part_xs(xs_obj_tot_prod[2], xs_data_obj[i]);
    }
    else if (mt >= he_xs_min && mt <= he_xs_max)
    {
      part_flg[3]++;
      sum_part_xs(xs_obj_tot_prod[3], xs_data_obj[i]);
    }
    else if (mt >= alpha_xs_min && mt <= alpha_xs_max)
    {
      part_flg[4]++;
      sum_part_xs(xs_obj_tot_prod[4], xs_data_obj[i]);
    }
  }
  vector<CrossSectionDataContainer>().swap(xs_data_obj);

  //Comparison of total production xs and sum of partial production xs
  for(int i=0; i<tot_prod_mt_no; i++)
  {
    if( part_flg[i] > 0 )
    {
      if( tot_flg[i] > 0 && tot_prod_xs_flg[i] == 1 )
      {
        comp_tot_prod_xs_and_mod_tot_xs(xs_obj_tot_prod[i], xs_obj_tot_prod_ori[i]);
      }

      nucl_reaction_data_obj.set_xs_data_obj(xs_obj_tot_prod[i]);
    }
  }
  vector<CrossSectionDataContainer>().swap(xs_obj_tot_prod);
  vector<CrossSectionDataContainer>().swap(xs_obj_tot_prod_ori);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ReconstructXSMerger::sum_part_xs(CrossSectionDataContainer& xs_data_obj_tot_prod,
                                      CrossSectionDataContainer& xs_data_obj)
{
  vector<Integer> int_vec = xs_data_obj.get_xs_int_data();
  vector<Integer> nbt_vec = xs_data_obj.get_xs_range_data();
  vector<Real>    ene_vec = xs_data_obj.get_xs_ene_data();
  vector<Real>    xs_vec  = xs_data_obj.get_xs_data();

  vector<Real>    ene_vec_tot_prod = xs_data_obj_tot_prod.get_xs_ene_data();
  vector<Real>    xs_vec_tot_prod  = xs_data_obj_tot_prod.get_xs_data();

  int i_max = static_cast<int>(ene_vec_tot_prod.size());
  for(int i=0; i<i_max; i++)
  {
    Real8 sig_val = 0.0;
    ti_obj.interpolation_tab1_in_range(ene_vec_tot_prod[i], sig_val, nbt_vec, int_vec, ene_vec, xs_vec);

    xs_vec_tot_prod[i] += sig_val;
  }

  xs_data_obj_tot_prod.set_xs_data(xs_vec_tot_prod);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ReconstructXSMerger::comp_tot_prod_xs_and_mod_tot_xs
                            ( CrossSectionDataContainer& xs_data_obj_tot_prod,
                              CrossSectionDataContainer& xs_data_obj_tot_prod_ori )
{
  //For modification of total cross section
  CrossSectionDataContainer xs_data_obj_tot = nucl_reaction_data_obj.get_xs_data_obj(1);
  vector<Real>              xs_vec_tot      = xs_data_obj_tot.get_xs_data();


  //Comparison of total production xs and sum of partial production xs
  //Original total production xs (from nuclear data)
  vector<Integer> int_vec = xs_data_obj_tot_prod_ori.get_xs_int_data();
  vector<Integer> nbt_vec = xs_data_obj_tot_prod_ori.get_xs_range_data();
  vector<Real>    ene_vec = xs_data_obj_tot_prod_ori.get_xs_ene_data();
  vector<Real>    xs_vec  = xs_data_obj_tot_prod_ori.get_xs_data();

  //sum of partial production xs 
  vector<Real>    ene_vec_cal = xs_data_obj_tot_prod.get_xs_ene_data();
  vector<Real>    xs_vec_cal  = xs_data_obj_tot_prod.get_xs_data();

  int          i_max      = static_cast<int>(ene_vec_cal.size());
  int          xs_mod_flg = 0;
  vector<Real> xs_mod;
  xs_mod.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    if( i > 0 )
    {
      if( fabs(ene_vec_cal[i] - ene_vec_cal[i-1]) < fabs(min_value * ene_vec_cal[i]) )
      {
        continue;
      }
    }

   if( i < i_max - 1 )
   {
      if( fabs(ene_vec_cal[i] - ene_vec_cal[i+1]) < fabs(min_value * ene_vec_cal[i]) )
      {
        continue;
      }
   }

    Real8 sig_val = 0.0;
    ti_obj.interpolation_tab1_in_range(ene_vec_cal[i], sig_val, nbt_vec, int_vec, ene_vec, xs_vec);

    xs_mod[i] = xs_vec_cal[i] - sig_val; 
    xs_vec_tot[i] += xs_mod[i];
    if( fabs(xs_mod[i] / sig_val) > 0.05 )
    {
      xs_mod_flg++;
    }
  }

  if( xs_mod_flg > 0 )
  {
    string class_name = "ReconstructXSMerger";
    string func_name  = "comp_tot_prod_xs_and_mod_tot_xs";

    int mt_no = xs_data_obj_tot_prod_ori.get_reaction_type();

    ostringstream oss01, oss02, oss03;
    oss01 << mt_no;
    if( mt_no == 103 )
    {
      oss02 << proton_xs_min;
      oss03 << proton_xs_max;
    }
    else if( mt_no == 104 )
    {
      oss02 << deuteron_xs_min;
      oss03 << deuteron_xs_max;
    }
    else if( mt_no == 105 )
    {
      oss02 << triton_xs_min;
      oss03 << triton_xs_max;
    }
    else if( mt_no == 106 )
    {
      oss02 << he_xs_min;
      oss03 << he_xs_max;
    }
    else if( mt_no == 107 )
    {
      oss02 << alpha_xs_min;
      oss03 << alpha_xs_max;
    }

    string str_data01 = "Reaction type : " + oss01.str();
    string str_data02 = "The large difference is observed between following cross sections";
    string str_data03 = "  Total production cross section from nuclear data (MT=" + oss01.str() + ")";
    string str_data04 = "  Sum of partial prodction cross section (MT="
                         + oss02.str() + "-" + oss03.str() + ")";

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("");
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back("");
    err_com.push_back("The original total production cross section or partial production");
    err_com.push_back("cross section from nuclear data may not be appropriate.");
    err_com.push_back("");
    err_com.push_back("Note that this program substitute from total production cross section");
    err_com.push_back("to sum of partial production cross section.");
    err_obj.output_caution(class_name, func_name, err_com);
  }

  //Copy total cross section
  xs_data_obj_tot.set_xs_data(xs_vec_tot);
  nucl_reaction_data_obj.set_xs_data_obj(xs_data_obj_tot);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ReconstructXSMerger::mod_non_elastic_xs()
{
  //Modify non-elastic cross section (MT=3 = Total - Elastic)
  int xs_tot_pos     = -1;
  int xs_ela_pos     = -1;
  int xs_non_ela_pos = -1;

  vector<CrossSectionDataContainer> xs_data_obj = nucl_reaction_data_obj.get_xs_data_obj();
  int xs_obj_no = static_cast<int>(xs_data_obj.size());
  for(int i=0; i<xs_obj_no; i++)
  {
    int mt_no = xs_data_obj[i].get_reaction_type();
    if( mt_no == 1 )
    {
      xs_tot_pos = i;
    }
    else if( mt_no == 2 )
    {
      xs_ela_pos = i;
    }
    else if( mt_no == 3 )
    {
      xs_non_ela_pos = i;
    }

    if( xs_tot_pos >= 0 && xs_ela_pos >= 0 && xs_non_ela_pos >= 0 )
    {
      break;
    }
  }

  if( xs_tot_pos < 0 || xs_ela_pos < 0 || xs_non_ela_pos < 0 )
  {
    return;
  }

  vector<Real> ene_vec_non_ela, xs_vec_non_ela;
  ene_vec_non_ela = xs_data_obj[xs_non_ela_pos].get_xs_ene_data();
  xs_vec_non_ela  = xs_data_obj[xs_non_ela_pos].get_xs_data();
  if( static_cast<int>(ene_vec_non_ela.size()) == 0 )
  {
    string class_name = "ReconstructXSMerger";
    string func_name  = "mod_non_elastic_xs()";

    vector<string> err_com;
    err_com.push_back("Though MT=3 data is found in the CrossSectionDataContainer (MF=3),");
    err_com.push_back("the size of the cross section data is zero.");
    err_com.push_back("");
    err_com.push_back("Modification of the non elastic cross section process is skipped.");
    err_obj.output_caution(class_name, func_name, err_com);

    return;
  }

  vector<Real>    ene_vec_tot = xs_data_obj[xs_tot_pos].get_xs_ene_data();
  vector<Real>    xs_vec_tot  = xs_data_obj[xs_tot_pos].get_xs_data();

  vector<Integer> int_vec_ela = xs_data_obj[xs_ela_pos].get_xs_int_data();
  vector<Integer> nbt_vec_ela = xs_data_obj[xs_ela_pos].get_xs_range_data();
  vector<Real>    ene_vec_ela = xs_data_obj[xs_ela_pos].get_xs_ene_data();
  vector<Real>    xs_vec_ela  = xs_data_obj[xs_ela_pos].get_xs_data();

  ene_vec_non_ela = ene_vec_tot;
  int ene_no = static_cast<int>(ene_vec_tot.size());

  xs_vec_non_ela.resize(ene_no);
  for(int i=0; i<ene_no; i++)
  {
    Real xs_tmp = 0.0;
    ti_obj.interpolation_tab1_in_range(ene_vec_non_ela[i], xs_tmp,
                                       nbt_vec_ela, int_vec_ela, ene_vec_ela, xs_vec_ela);
    xs_vec_non_ela[i] = xs_vec_tot[i] - xs_tmp;
  }

  vector<Integer> int_vec_non_ela, nbt_vec_non_ela;
  int_vec_non_ela.resize(1);
  nbt_vec_non_ela.resize(1);
  int_vec_non_ela[0] = int_lin_lin;
  nbt_vec_non_ela[0] = static_cast<Integer>(ene_no);

  xs_data_obj[xs_non_ela_pos].set_xs_int_data(int_vec_non_ela);
  xs_data_obj[xs_non_ela_pos].set_xs_range_data(nbt_vec_non_ela);
  xs_data_obj[xs_non_ela_pos].set_xs_ene_data(ene_vec_non_ela);
  xs_data_obj[xs_non_ela_pos].set_xs_data(xs_vec_non_ela);

  nucl_reaction_data_obj.set_xs_data_obj(xs_data_obj[xs_non_ela_pos]);
  vector<CrossSectionDataContainer>().swap(xs_data_obj);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ReconstructXSMerger::check_minus_xs()
{
  int     i_max = static_cast<int>(ene_merge.size());
  Integer minus_xs_flg;
  Real8   sig_res, sig_mod, sig_mod_dif;
  for(int i=0; i<i_max; i++)
  {
    minus_xs_flg = 0;
    sig_res      = 0.0;
    for(int j=1; j<xs_type_no; j++)
    {
      sig_mod     = digit_obj.adjust_min_value(sig_merge[i][j]);
      sig_mod_dif = sig_mod - sig_merge[i][j];
      if( fabs(sig_mod_dif) > min_sig_dif )
      {
        minus_xs_flg     = -1;
        sig_res         += sig_mod_dif;
        sig_merge[i][j]  = sig_mod;
      }
    }
    if( minus_xs_flg < 0 )
    {
      sig_merge[i][total_xs] += sig_res;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ReconstructXSMerger::update_xs_tot_sc_fis_rad()
{
  vector<CrossSectionDataContainer> xs_data_obj = nucl_reaction_data_obj.get_xs_data_obj();

  for(int i=0; i<static_cast<int>(xs_data_obj.size()); i++)
  {
    Integer reaction_type_value = xs_data_obj[i].get_reaction_type();
    if( reaction_type_value == 1 )
    {
      //Update total cross section (reaction_type = 1)
      update_each_xs(total_xs, xs_data_obj[i]);
    }
    else if( reaction_type_value == 2 )
    {
      //Update inelastic scatter cross section (reaction_type = 2)
      update_each_xs(scatter_xs, xs_data_obj[i]);
    }
    else if( reaction_type_value == 18 )
    {
      //Update fission cross section (reaction_type = 18)
      update_each_xs(fission_xs, xs_data_obj[i]);
    }
    else if( reaction_type_value == 102 )
    {
      //Update radiation cross section (reaction_type = 102)
      update_each_xs(radiation_xs, xs_data_obj[i]);
    }
  }

  nucl_reaction_data_obj.set_xs_data_obj(xs_data_obj);
  vector<CrossSectionDataContainer>().swap(xs_data_obj);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ReconstructXSMerger::update_each_xs(int xs_type, CrossSectionDataContainer& data_obj)
{
  vector<Integer> nbt_xs,   int_xs;
  vector<Real>    ene_data, xs_data;

  int i_max = static_cast<int>(ene_merge.size());
  ene_data.resize(i_max);
  xs_data.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    ene_data[i] = static_cast<Real>(ene_merge[i]);
    xs_data[i]  = static_cast<Real>(sig_merge[i][xs_type]);
  }
  
  //Reset interpolation scheme (all interpolation scheme is linear-linear)
  nbt_xs.resize(1);
  int_xs.resize(1);
  nbt_xs[0] = static_cast<Integer>(i_max);
  int_xs[0] = int_lin_lin; //linear-linear
  
  data_obj.set_xs_range_data(nbt_xs);
  data_obj.set_xs_int_data(int_xs);
  data_obj.set_xs_ene_data(ene_data);
  data_obj.set_xs_data(xs_data);

  nbt_xs.clear();
  int_xs.clear();
  ene_data.clear();
  xs_data.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ReconstructXSMerger::update_xs_other()
{
  vector<CrossSectionDataContainer> xs_data_obj = nucl_reaction_data_obj.get_xs_data_obj();
  vector<CrossSectionDataContainer> xs_data_obj_add;
  xs_data_obj_add.clear();

  int xs_obj_no = static_cast<int>(xs_data_obj.size());
  int react_no  = static_cast<int>(react_type_list_reso_uni.size());

  for(int i=0; i<react_no; i++)
  {
    Integer r_val = react_type_list_reso_uni[i];
    if( r_val == 1 || r_val == 2 || r_val == 18 || r_val == 102 )
    {
      continue;
    }

    int merge_flg = 0;
    for(int j=0; j<xs_obj_no; j++)
    {
      if( xs_data_obj[j].get_reaction_type() == r_val )
      {
        merge_flg = 1;
        merge_xs_other(i, xs_data_obj[j]);
        break;
      }
    }

    if( merge_flg == 0 )
    {
      string class_name = "ReconstructXSMerger";
      string func_name  = "update_xs_other()";

      ostringstream oss01;
      oss01 << react_type_list_reso_uni[react_no];

      string str_data01 = "Reaction type : " + oss01.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back("This reaction type does not find in the cross section data.");
      err_com.push_back("The nuclear data object may not be appropriate.");
      err_com.push_back("");
      err_com.push_back("The new cross section data is added from the resonance data.");
      err_com.push_back("Since the mass difference Q value is not obtained from resonance data,");
      err_com.push_back("this data is identical to reaction Q value from resonance data.");
      err_obj.output_caution(class_name, func_name, err_com);

      xs_data_obj_add.push_back(add_new_xs_data_obj(i));
    }
  }

  //Add total reaction from partial reaction
  vector<int> add_react_type_pos_reso, add_react_type_pos_xs_obj;
  check_add_total_reaction(xs_data_obj, add_react_type_pos_reso, add_react_type_pos_xs_obj);
  for(int i=0; i<static_cast<int>(add_react_type_pos_reso.size()); i++)
  {
    merge_xs_other(add_react_type_pos_reso[i], xs_data_obj[ add_react_type_pos_xs_obj[i] ]);
  }

  //Replace cross section data object
  nucl_reaction_data_obj.set_xs_data_obj(xs_data_obj);
  vector<CrossSectionDataContainer>().swap(xs_data_obj);

  //Add cross section data object
  int i_max = static_cast<int>(xs_data_obj_add.size());
  for(int i=0; i<i_max; i++)
  {
    nucl_reaction_data_obj.set_xs_data_obj(xs_data_obj_add[i]);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ReconstructXSMerger::check_add_total_reaction( vector<CrossSectionDataContainer>& xs_data_obj,
                                                    vector<int>& add_react_type_pos_reso,
                                                    vector<int>& add_react_type_pos_xs_obj )
{
  add_react_type_pos_reso.clear();
  add_react_type_pos_xs_obj.clear();

  int xs_obj_no = static_cast<int>(xs_data_obj.size());
  int react_no  = static_cast<int>(react_type_list_reso_uni.size());
  for(int i=0; i<react_no; i++)
  {
    Integer add_flg = 0;
    Integer mt      = react_type_list_reso_uni[i];
    Integer mt_tot  = 0;
    if ( mt >= 50 && mt <= 91 )
    {
      add_flg =   1;
      mt_tot  =   4;
    }
    else if ( mt == 19 || mt == 20 || mt == 21 || mt == 38 )
    {
      add_flg =   1;
      mt_tot  =  18;
    }
    else if ( mt >= proton_xs_min && mt <= proton_xs_max )
    {
      add_flg =   1;
      mt_tot  = 103;
    }
    else if ( mt >= deuteron_xs_min && mt <= deuteron_xs_max )
    {
      add_flg =   1;
      mt_tot  = 104;
    }
    else if ( mt >= triton_xs_min && mt <= triton_xs_max )
    {
      add_flg =   1;
      mt_tot  = 105;
    }
    else if ( mt >= he_xs_min && mt <= he_xs_max )
    {
      add_flg =   1;
      mt_tot  = 106;
    }
    else if ( mt >= alpha_xs_min && mt <= alpha_xs_max )
    {
      add_flg =   1;
      mt_tot  = 107;
    }

    if( add_flg == 1 )
    {
      for(int j=0; j<react_no; j++)
      {
        if( react_type_list_reso_uni[j] == mt_tot )
        {
          add_flg = 0;
          break;
        }
      }
    }

    if( add_flg == 1 )
    {
      int merge_flg = 0;
      for(int j=0; j<xs_obj_no; j++)
      {
        if( xs_data_obj[j].get_reaction_type() == mt_tot )
        {
          merge_flg = 1;
          add_react_type_pos_reso.push_back(i);
          add_react_type_pos_xs_obj.push_back(j);
          break;
        }
      }

      if( merge_flg == 0 )
      {
        string class_name = "ReconstructXSMerger";
        string func_name  = "check_add_total_reaction";

        ostringstream oss01, oss02;
        oss01 << mt;
        oss02 << mt_tot;

        string str_data01 = "Reaction type (partial) : " + oss01.str();
        string str_data02 = "Reaction type (total)   : " + oss02.str();

        vector<string> err_com;
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back("The partial reaction is found in resonance cross section.");
        err_com.push_back("However, xs data object does not contain the total reaction.");
        err_com.push_back("The calculation of total reaction cross section is skipped.");
        err_obj.output_caution(class_name, func_name, err_com);
      }
    }
  }  
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ReconstructXSMerger::merge_xs_other(int react_no, frendy::CrossSectionDataContainer& data_obj)
{
  vector<Integer> int_data   = data_obj.get_xs_int_data();
  vector<Integer> range_data = data_obj.get_xs_range_data();
  vector<Real8>   ene_data   = data_obj.get_xs_ene_data();
  vector<Real8>   sig_data   = data_obj.get_xs_data();

  Real8           q_val_mass = data_obj.get_q_value_mass();
  Real8           q_val      = data_obj.get_q_value();

  if( fabs((q_val_reso_uni[react_no] - q_val)/q_val) > 0.01 )
  {
    string class_name = "ReconstructXSMerger";
    string func_name  = "merge_xs_other";

    ostringstream oss01, oss02, oss03;
    oss02.precision(8);
    oss03.precision(8);
    oss02.setf(ios::showpoint);
    oss03.setf(ios::showpoint);
    oss01 << react_type_list_reso_uni[react_no];
    oss02 << q_val;
    oss03 << q_val_reso_uni[react_no];

    string str_data01 = "Reaction type                   : " + oss01.str();
    string str_data02 = "Q value from cross section data : " + oss02.str();
    string str_data03 = "Q value from resonance data     : " + oss03.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("Q value from cross section data is different to that from resonance data.");
    err_com.push_back("Q value from resonance data is set in the new nucelar data object.");
    err_com.push_back("(Mass difference Q value is obtained from cross section data.)");
    err_obj.output_caution(class_name, func_name, err_com);
  }

  int ene_no_ori  = static_cast<int>(ene_data.size());
  int ene_no_reso = static_cast<int>(ene_reso_uni.size());
  if( ene_no_reso == 0 )
  {
    return;
  }
  else if( ene_no_ori == 0 )
  {
    data_obj = add_new_xs_data_obj(react_no);
  }

  vector<Real8> ene_new, sig_new;
  for(int j=0; j<ene_no_reso; j++)
  {
    Real8 sig_val = 0.0;
    ti_obj.interpolation_tab1_in_range(ene_reso_uni[j], sig_val, range_data, int_data, ene_data, sig_data);

    sig_val += sig_reso_uni[j][react_no];
    if( sig_val > 0.0 )
    {
      ene_new.push_back(ene_reso_uni[j]);
      sig_new.push_back(sig_val);
    }
  }

  if( ene_reso_uni[ene_no_reso-1] < ene_data[ene_no_ori-1] )
  {
    int j_m, j_p;
    ti_obj.search_neighbor_value(ene_reso_uni[ene_no_reso-1], ene_data, j_m, j_p);

    for(int j=j_p; j<ene_no_ori; j++)
    {
      ene_new.push_back(ene_data[j]);
      sig_new.push_back(sig_data[j]);
    }
  }

  int_data.resize(1);
  range_data.resize(1);
  int_data[0]   = int_lin_lin;
  range_data[0] = static_cast<Integer>(ene_new.size());

  data_obj.set_xs_int_data(int_data);
  data_obj.set_xs_range_data(range_data);
  data_obj.set_xs_ene_data(ene_new);
  data_obj.set_xs_data(sig_new);
  data_obj.set_q_value_mass(q_val_mass);
  data_obj.set_q_value(q_val);

  int_data.clear();
  range_data.clear();
  ene_data.clear();
  sig_data.clear();
  ene_new.clear();
  sig_new.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

CrossSectionDataContainer ReconstructXSMerger::add_new_xs_data_obj(int react_no)
{
  int ene_no_reso = static_cast<int>(ene_reso_uni.size());
  int q_val_flg   = -1;
  vector<Real8> ene_new, sig_new;
  for(int j=0; j<ene_no_reso; j++)
  {
    if( sig_reso_uni[j][react_no] > 0.0 )
    {
      if( q_val_flg < 0 )
      {
        q_val_flg = j;
        if( j != 0 )
        {
          ene_new.push_back(ene_reso_uni[j-1]);
          sig_new.push_back(0.0);
        }
      }

      ene_new.push_back(ene_reso_uni[j]);
      sig_new.push_back(sig_reso_uni[j][react_no]);
    }
  }

  vector<Integer> int_data, range_data;
  int_data.resize(1);
  range_data.resize(1);
  int_data[0]   = int_lin_lin;
  range_data[0] = static_cast<Integer>(ene_new.size());

  CrossSectionDataContainer xs_data_obj_new;
  xs_data_obj_new.set_reaction_type(react_type_list_reso_uni[react_no]);
  xs_data_obj_new.set_q_value_mass(q_val_reso_uni[react_no]);
  xs_data_obj_new.set_q_value(q_val_reso_uni[react_no]);
  xs_data_obj_new.set_xs_int_data(int_data);
  xs_data_obj_new.set_xs_range_data(range_data);
  xs_data_obj_new.set_xs_ene_data(ene_new);
  xs_data_obj_new.set_xs_data(sig_new);

  int_data.clear();
  range_data.clear();
  ene_new.clear();
  sig_new.clear();

  return xs_data_obj_new;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ReconstructXSMerger::add_mf10_mt102_data()
{
  vector<CrossSectionDataContainer>       xs_data_obj;
  vector<RadioactiveProductDataContainer> radio_product_data_obj;
  xs_data_obj            = nucl_reaction_data_obj.get_xs_data_obj();
  radio_product_data_obj = nucl_reaction_data_obj.get_radio_product_data_obj();

  reaction_type = nucl_reaction_data_obj.get_reaction_type();
  int i_max    = static_cast<int>(reaction_type.size());
  for(int i=0; i<i_max; i++)
  {
    if( reaction_type[i] != 102 )
    {
      continue;
    }

    if( xs_data_obj[i].get_reaction_type()            == reaction_type[i] &&
        radio_product_data_obj[i].get_reaction_type() == reaction_type[i] )
    {
      if( static_cast<int>(radio_product_data_obj[i].get_multiplicity_ene_data().size()) > 0 )
      {
        NonResonanceEnergyGridLinearizer nrl_obj;
        nrl_obj.add_radio_product_data(xs_data_obj[i], radio_product_data_obj[i]);
        nucl_reaction_data_obj.set_radio_product_data_obj(radio_product_data_obj[i]);
        break;
      }
    }
  }

  vector<CrossSectionDataContainer>().swap(xs_data_obj);
  vector<RadioactiveProductDataContainer>().swap(radio_product_data_obj);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ReconstructXSMerger::remove_non_linearize_xs_data()
{
  vector<CrossSectionDataContainer>       xs_data_obj,            xs_data_obj_mod;
  vector<RadioactiveProductDataContainer> radio_product_data_obj, radio_product_data_obj_mod;
  vector<PhotonDataContainer>             photon_data_obj,        photon_data_obj_mod;
  xs_data_obj              = nucl_reaction_data_obj.get_xs_data_obj();
  radio_product_data_obj   = nucl_reaction_data_obj.get_radio_product_data_obj();
  photon_data_obj          = nucl_reaction_data_obj.get_photon_data_obj();

  reaction_type = nucl_reaction_data_obj.get_reaction_type();

  int i_max = static_cast<int>(reaction_type.size());
  for(int i=0; i<i_max; i++)
  {
    if( xs_data_obj[i].get_reaction_type() == reaction_type[i] )
    {
      if( check_interpolation_type(xs_data_obj[i].get_xs_int_data()) == 0 )
      {
        xs_data_obj_mod.push_back(xs_data_obj[i]);
      }
    }

    if( radio_product_data_obj[i].get_reaction_type() == reaction_type[i] )
    {
      Integer int_check_radio = 0;

      vector<vector<Integer> > int_array = radio_product_data_obj[i].get_xs_int_data();
      for(int j=0; j<static_cast<int>(int_array.size()); j++)
      {
        if( check_interpolation_type(int_array[j]) != 0 )
        {
          int_check_radio = 1;
          break;
        }
      }

      if( int_check_radio == 0 )
      {
        radio_product_data_obj_mod.push_back(radio_product_data_obj[i]);
      }
    }

    if( photon_data_obj[i].get_reaction_type() == reaction_type[i] )
    {
      if( check_interpolation_type(photon_data_obj[i].get_multiplicity_tot_int_data())         == 0 ||
          check_interpolation_type(photon_data_obj[i].get_photon_production_xs_tot_int_data()) == 0 ||
          check_interpolation_type(photon_data_obj[i].get_photon_interaction_xs_int_data())    == 0 )
      {
        photon_data_obj_mod.push_back(photon_data_obj[i]);
      }
    }
  }

  nucl_reaction_data_obj.set_xs_data_obj(xs_data_obj_mod);
  //nucl_reaction_data_obj.set_radio_product_data_obj(radio_product_data_obj_mod);
  //nucl_reaction_data_obj.set_photon_data_obj(photon_data_obj_mod);

  vector<CrossSectionDataContainer>().swap(xs_data_obj);
  vector<CrossSectionDataContainer>().swap(xs_data_obj_mod);
  vector<RadioactiveProductDataContainer>().swap(radio_product_data_obj);
  vector<RadioactiveProductDataContainer>().swap(radio_product_data_obj_mod);
  vector<PhotonDataContainer>().swap(photon_data_obj);
  vector<PhotonDataContainer>().swap(photon_data_obj_mod);
  
  reaction_type    = nucl_reaction_data_obj.get_reaction_type();
  reaction_type_no = static_cast<int>(reaction_type.size());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

int ReconstructXSMerger::check_interpolation_type(vector<Integer> int_vec)
{
  int int_type_flg = 0;

  int i_max = static_cast<int>(int_vec.size());
  if( i_max == 0 )
  {
    int_type_flg = -1;
  }

  for(int i=0; i<i_max; i++)
  {
    if( int_vec[i] != int_lin_lin )
    {
      int_type_flg = 1;
      break;
    }
  }

  return int_type_flg;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ReconstructXSMerger::check_set_data()
{
  int nis = static_cast<int>(nucl_data_obj.get_reso_data_obj().get_reso_region_flg().size());
  if( (nucl_data_flg == 0) || (reso_grid_flg == 0) || (reso_xs_flg == 0) || (non_reso_grid_flg == 0) ||
      (static_cast<int>(ene_reso.size()) != nis && reso_flg == 1 ) ||
      (static_cast<int>(sig_reso.size()) != nis && reso_flg == 1 ) ||
      (static_cast<int>(ene_non_reso.size()) == 0) )
  {
    string class_name = "ReconstructXSMerger";
    string func_name  = "check_set_data()";

    ostringstream oss01, oss02, oss03, oss04;
    oss01 << nis;
    oss02 << static_cast<Integer>(ene_reso.size());
    oss03 << static_cast<Integer>(sig_reso.size());
    oss04 << static_cast<int>(ene_non_reso.size());

    string str_data01 = "Number of isotopes (NIS)                    : " + oss01.str();
    string str_data02 = "Size of energy grid at resonance region     : " + oss02.str();
    string str_data03 = "Size of cross section at resonance region   : " + oss03.str();
    string str_data04 = "Size of energy grid at non-resonance region : " + oss04.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);

    //Check the all data was set or not
    if( nucl_data_flg == 0 )
    {
      err_com.push_back("NuclDataObject class is not set. Please check the program.");
    }
    if( reso_grid_flg == 0 )
    {
      err_com.push_back("Resonance energy grid is not set. Please check the program.");
    }
    if( reso_xs_flg == 0 )
    {
      err_com.push_back("Resonance cross section is not set. Please check the program.");
    }
    if( non_reso_grid_flg == 0 )
    {
      err_com.push_back("Non resonance energy grid is not set. Please check the program.");
    }

    //Check the energy grid and cross section array size
    if( reso_flg == 1 )
    {
      if( static_cast<int>(ene_reso.size()) != nis )
      {
        err_com.push_back("The array size of resonance energy grid is different to NIS in MF02MT151.");
      }
      if( static_cast<int>(sig_reso.size()) != nis )
      {
        err_com.push_back("The array size of resonance cross section is different to NIS in MF02MT151.");
      }
    }

    if( static_cast<int>(ene_non_reso.size()) == 0 )
    {
      err_com.push_back("The array size of non resonance energy grid is 0.");
    }
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
  
  if( reso_flg == 1 )
  {
    for(int i=0; i<nis; i++)
    {
      int ner = static_cast<int>(nucl_data_obj.get_reso_data_obj().get_reso_region_flg()[i].size());
      if( static_cast<int>(ene_reso[i].size()) != ner || static_cast<int>(sig_reso[i].size()) != ner )
      {
        string class_name = "ReconstructXSMerger";
        string func_name  = "check_set_data()";

        ostringstream oss01, oss02, oss03, oss04, oss05;
        oss01 << i;
        oss02 << nis;
        oss03 << ner;
        oss04 << static_cast<int>(ene_reso[i].size());
        oss05 << static_cast<int>(sig_reso[i].size());

        string str_data01 = "Number of isotope (NIS)                     : " + oss01.str() + " / "
                                                                             + oss02.str();
        string str_data02 = "Number of resonance energy range (NER)      : " + oss03.str();
        string str_data03 = "Size of energy grid at resonance region     : " + oss04.str();
        string str_data04 = "Size of cross section at resonance region   : " + oss05.str();

        vector<string> err_com;
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back(str_data04);
        if( static_cast<int>(ene_reso[i].size()) != ner )
        {
          err_com.push_back("The array size of resonance energy grid is different to NER in MF02MT151.");
        }
        else if( static_cast<int>(sig_reso[i].size()) != ner )
        {
          err_com.push_back("The array size of resonance cross section is different to NER in MF02MT151.");
        }
        err_obj.output_runtime_error(class_name, func_name, err_com);
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ReconstructXSMerger::check_total_xs_data()
{
  vector<CrossSectionDataContainer> xs_data_obj = nucl_reaction_data_obj.get_xs_data_obj();

  //XS data check
  int xs_no = static_cast<int>(xs_data_obj.size());

  Integer mt_data_check  = 0;
  Integer tot_data_check = 0;
  for(int i=0; i<xs_no; i++)
  {
    if( xs_data_obj[i].get_reaction_type() == 1 )
    {
      mt_data_check  = 1;
      tot_data_check = 1;
      break;
    }
    else if( xs_data_obj[i].get_reaction_type() != unassigned_mt_no )
    {
      mt_data_check = 1;
    }
  }

  if( mt_data_check == 0 )
  {
    string class_name = "ReconstructXSMerger";
    string func_name  = "check_total_xs_data";

    vector<string> err_com;
    err_com.push_back("There is no cross section data.");
    err_com.push_back("This nuclear data may not be appropriate.");
    err_obj.output_caution(class_name, func_name, err_com);
  }
  else if( tot_data_check == 0 )
  {
    //Make dummy total xs data (sigma_tot = 0.0)
    vector<Integer> int_vec, range_vec;
    vector<Real>    ene_vec, xs_vec;
    for(int i=0; i<xs_no; i++)
    {
      if( xs_data_obj[i].get_reaction_type() != unassigned_mt_no )
      {
        ene_vec = xs_data_obj[i].get_xs_ene_data();
        break;
      }
    }

    int j_max = static_cast<int>(ene_vec.size());
    xs_vec.resize(j_max);
    for(int j=0; j<j_max; j++)
    {
      xs_vec[j] = min_sig_val;
    }
    int_vec.resize(1);
    range_vec.resize(1);
    int_vec[0]   = int_lin_lin;
    range_vec[0] = static_cast<Integer>(j_max);

    CrossSectionDataContainer xs_tot_dummy;
    xs_tot_dummy.set_reaction_type(1);
    xs_tot_dummy.set_xs_int_data(int_vec);
    xs_tot_dummy.set_xs_range_data(range_vec);
    xs_tot_dummy.set_xs_ene_data(ene_vec);
    xs_tot_dummy.set_xs_data(xs_vec);

    //Set dummy total xs data
    nucl_reaction_data_obj.set_xs_data_obj(xs_tot_dummy);

    //Clear dummy data
    xs_tot_dummy.clear();
    int_vec.clear();
    range_vec.clear();
    ene_vec.clear();
    xs_vec.clear();
  }

  vector<CrossSectionDataContainer>().swap(xs_data_obj);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ReconstructXSMerger::clear()
{
  clear_parser_data();

  nucl_data_flg     = 0;
  reso_grid_flg     = 0;
  reso_xs_flg       = 0;
  non_reso_grid_flg = 0;
  
  ene_merge.clear();
  clr_obj.clear_vec_array2_real8(sig_merge);
  
  ene_non_reso.clear();

  react_type_list_reso_uni.clear();
  clr_obj.clear_vec_array3_int(react_type_list_reso);
  clr_obj.clear_vec_array4_real8(sig_reso);
  clr_obj.clear_vec_array3_real8(ene_reso);
  ene_reso_uni.clear();
  clr_obj.clear_vec_array2_real8(sig_reso_uni);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ReconstructXSMerger::clear_parser_data()
{
  merge_xs_flg = 0;

  nucl_data_obj.clear();
  nucl_reaction_data_obj.clear();
  reaction_type.clear();

  reaction_type_no          = 0;
  inelastic_scat_xs_flg     = 0;
  fission_xs_flg            = 0;
  proton_xs_flg             = 0;
  deuteron_xs_flg           = 0;
  triton_xs_flg             = 0;
  he_xs_flg                 = 0;
  alpha_xs_flg              = 0;
  photon_interaction_xs_flg = 0;
  photoelectric_xs_flg      = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ReconstructXSMerger::set_nucl_data_obj(NuclearDataObject& data_obj)
{
  clear_parser_data();
  nucl_data_flg = 1;

  nucl_data_obj          = data_obj;
  reso_flg               = nucl_data_obj.get_general_data_obj().get_reso_flg();
  nucl_reaction_data_obj = nucl_data_obj.get_nucl_reaction_data_obj();
  check_total_xs_data();

  reaction_type    = nucl_reaction_data_obj.get_reaction_type();
  reaction_type_no = static_cast<int>(reaction_type.size());

  vector<Real> real_vec;
  for(int i=0; i<reaction_type_no; i++)
  {
    //Check cross sections
    real_vec = nucl_reaction_data_obj.get_xs_data_obj()[i].get_xs_data();
    if( static_cast<int>(real_vec.size()) > 0 )
    {
      if( reaction_type[i] >= 51 && reaction_type[i] <= 91 )
      {
        //reaction_type = 51-91 : (z,n[n]) - Excitation of n-th excited state 
        inelastic_scat_xs_flg = 1;
      }
      else if( reaction_type[i] == 19 )
      {
        //reaction_type = 19 : (n,f) - 1st chance fission
        fission_xs_flg = 1;
      }
      else if( reaction_type[i] == 103 )
      {
        //reaction_type = 103 : (z,p) - Total of proton level cross sections (600-649)
        proton_xs_flg = 1;
      }
      else if( reaction_type[i] == 104 )
      {
        //reaction_type = 104 : (z,d) - Total of deuteron level cross sections (650-699)
        deuteron_xs_flg = 1;
      }
      else if( reaction_type[i] == 105 )
      {
        //reaction_type = 105 : (z,t) - Total of triton level cross sections (700-749)
        triton_xs_flg = 1;
      }
      else if( reaction_type[i] == 106 )
      {
        //reaction_type = 106 : (z,3He) - Total of 3He level cross sections (750-799)
        he_xs_flg = 1;
      }
      else if( reaction_type[i] == 107 )
      {
        //reaction_type = 107 : (z,alpha) - Total of alpha level cross sections (800-849)
        alpha_xs_flg = 1;
      }
    }

    //Check photon interaction cross sections
    real_vec = nucl_reaction_data_obj.get_photon_data_obj()[i].get_photon_interaction_xs_data();
    if( static_cast<int>(real_vec.size()) > 0 )
    {
      photon_interaction_xs_flg = 1;

      //reaction_type = 534-572 : Various subshell photoelectric cross sections
      if( reaction_type[i] >= 534 && reaction_type[i] <= 572 )
      {
        photoelectric_xs_flg = 1;
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ReconstructXSMerger::set_resonance_react_type_list(vector<vector<vector<Integer> > >& int_vec)
{
  reso_grid_flg = 1;
  merge_xs_flg  = 0;
  react_type_list_reso = int_vec;
}

void ReconstructXSMerger::set_resonance_q_val(vector<vector<vector<Real8> > >& real_vec)
{
  reso_grid_flg = 1;
  merge_xs_flg  = 0;
  q_val_reso = real_vec;
}

void ReconstructXSMerger::set_resonance_grid(vector<vector<vector<Real8> > >& real_vec)
{
  reso_grid_flg = 1;
  merge_xs_flg  = 0;
  ene_reso      = real_vec;
}

void ReconstructXSMerger::set_resonance_xs(vector<vector<vector<vector<Real8> > > >& real_vec)
{
  reso_xs_flg  = 1;
  merge_xs_flg = 0;
  sig_reso     = real_vec;
}

void ReconstructXSMerger::set_non_resonance_grid(vector<Real8>& real_vec)
{
  non_reso_grid_flg = 1;
  merge_xs_flg      = 0;
  ene_non_reso      = real_vec;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

NuclearDataObject ReconstructXSMerger::get_nucl_data_obj()
{
  if( merge_xs_flg == 0 )
  {
    merge_non_reso_and_reso_xs();
  }

  nucl_data_obj.set_nucl_reaction_data_obj(nucl_reaction_data_obj);

  return nucl_data_obj;
}

vector<vector<vector<Integer> > > ReconstructXSMerger::get_resonance_react_type_list()
{
  return react_type_list_reso;
}

vector<vector<vector<Real8> > > ReconstructXSMerger::get_resonance_q_val()
{
  return q_val_reso;
}

vector<Integer> ReconstructXSMerger::get_resonance_react_type_list_uni()
{
  return react_type_list_reso_uni;
}

vector<Real8> ReconstructXSMerger::get_resonance_q_val_uni()
{
  return q_val_reso_uni;
}

vector<vector<vector<Real8> > > ReconstructXSMerger::get_resonance_grid()
{
  return ene_reso;
}

vector<vector<vector<vector<Real8> > > > ReconstructXSMerger::get_resonance_xs()
{
  return sig_reso;
}

vector<Real8> ReconstructXSMerger::get_non_resonance_grid()
{
  return ene_non_reso;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

vector<vector<Real8> > ReconstructXSMerger::get_merge_xs()
{
  if( merge_xs_flg == 0 )
  {
    merge_non_reso_and_reso_xs();
  }
  return sig_merge;
}

vector<Real8> ReconstructXSMerger::get_merge_grid()
{
  if( merge_xs_flg == 0 )
  {
    merge_non_reso_and_reso_xs();
  }
  return ene_merge;
}

