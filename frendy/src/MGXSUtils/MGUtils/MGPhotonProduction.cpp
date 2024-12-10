#include "MGXSUtils/MGUtils/MGPhotonProduction.hpp"

using namespace frendy;

// ***** MGPhotonProduction ***** //
//constructor
MGPhotonProduction::MGPhotonProduction(void)
{
  clear();
}

//destructor
MGPhotonProduction::~MGPhotonProduction(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MGPhotonProduction::clear()
{
  //add_pl_data_flg = 0; //skip additional pl data
  add_pl_data_flg = 1; //add pl data

  pl_no_ori = 0;

  add_mf13_data_flg = 0;//skip calculation of the MF=13 data
  //add_mf13_data_flg = 1;//calculation of the MF=13 data

  clear_calc_data();

  calc_dd_xs_flg = 0;
  egg_vec.clear();

  za_val  = 0;
  awr_val = 0.0;

  mt_list.clear();
  mt_list_pos.clear();
  emit_photon_no.clear();
  clr_obj.clear_vec_array2_real(transition_prob);
  clr_obj.clear_vec_array3_int(ddxs_multi_range);
  clr_obj.clear_vec_array3_int(ddxs_multi_int);
  clr_obj.clear_vec_array3_real(ddxs_multi_ene);
  clr_obj.clear_vec_array3_real(ddxs_multi_data);

  photon_xs_fine_ene.clear();
  clr_obj.clear_vec_array2_real(photon_xs_fine);

  clr_obj.clear_vec_array3_real(dd_xs_coef);
  clr_obj.clear_vec_array3_real(flux_ang);

  clr_obj.clear_vec_array3_real(photon_xs);
  clr_obj.clear_vec_array5_real(photon_dd_xs);
}

////////////////////////////////////////////////////////////////////////////////////////////////////


void MGPhotonProduction::clear_calc_data()
{
  mg_obj.clear();

  //Data from ACE file
  ace_ene_grid.clear();
  ace_xs_tot.clear();

  //Data from MTRP block
  mtrp_mt_list.clear();

  //Data from SIGP block
  sigp_file_no.clear();
  sigp_react_type.clear();

  //For MF = 13
  clr_obj.clear_vec_array2_int(sigp_pos);
  clr_obj.clear_vec_array2_real(sigp_xs);

  //For MF = 12
  clr_obj.clear_vec_array2_int(sigp_multi_range);
  clr_obj.clear_vec_array2_int(sigp_multi_int);
  clr_obj.clear_vec_array2_real(sigp_multi_ene);
  clr_obj.clear_vec_array2_real(sigp_multi_data);

  //For MF = 16
  clr_obj.clear_vec_array2_int(sigp_distr_range);
  clr_obj.clear_vec_array2_int(sigp_distr_int);
  clr_obj.clear_vec_array2_real(sigp_distr_ene);
  clr_obj.clear_vec_array2_real(sigp_distr_data);


  //Data from ANDP block
  clr_obj.clear_vec_array2_real(andp_ene_data);
  clr_obj.clear_vec_array3_real(andp_cos_data);

  //Data from DLWP block
  dlwp_distr_flg.clear();
  clr_obj.clear_vec_array2_int(dlwp_range);
  clr_obj.clear_vec_array2_int(dlwp_int);
  clr_obj.clear_vec_array2_real(dlwp_ene);
  clr_obj.clear_vec_array2_real(dlwp_prob);

  //DLWP Law = 2
  dlwp_ene_distr_flg.clear();
  dlwp_binding_ene.clear();

  //DLWP Law = 4
  clr_obj.clear_vec_array2_int(dlwp_ein_range);
  clr_obj.clear_vec_array2_int(dlwp_ein_int);
  clr_obj.clear_vec_array2_real(dlwp_ein_data);

  clr_obj.clear_vec_array2_int(dlwp_eout_int);
  clr_obj.clear_vec_array3_real(dlwp_eout_data);
  clr_obj.clear_vec_array3_real(dlwp_eout_weight);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MGPhotonProduction::copy_ace_data(FastAceDataObject& ace_obj)
{
  //Data from ACE file
  ace_ene_grid     = ace_obj.get_union_ene_grid();
  ace_xs_tot       = ace_obj.get_react_xs_tot();
  for(int i=0; i<static_cast<int>(ace_ene_grid.size()); i++)
  {
    ace_ene_grid[i] *= unit_mega;
  }

  //Data from MTRP block
  mtrp_mt_list     = ace_obj.get_photon_prod_reaction_type_all();

  //Data from SIGP block
  sigp_file_no     = ace_obj.get_photon_prod_file_no();
  sigp_react_type  = ace_obj.get_photon_prod_reaction_type();

  //For MF = 13
  sigp_pos         = ace_obj.get_photon_prod_xs_non_zero_pos();
  sigp_xs          = ace_obj.get_photon_prod_xs_data();

  //For MF = 12
  sigp_multi_range = ace_obj.get_photon_prod_multiplicity_range_data();
  sigp_multi_int   = ace_obj.get_photon_prod_multiplicity_int_data();
  sigp_multi_ene   = ace_obj.get_photon_prod_multiplicity_ene_data();
  sigp_multi_data  = ace_obj.get_photon_prod_multiplicity_data();
  for(int i=0; i<static_cast<int>(sigp_multi_ene.size()); i++)
  {
    for(int j=0; j<static_cast<int>(sigp_multi_ene[i].size()); j++)
    {
      sigp_multi_ene[i][j] *= unit_mega;
    }
  }

  //For MF = 16
  sigp_distr_range = ace_obj.get_photon_prod_distr_range_data();
  sigp_distr_int   = ace_obj.get_photon_prod_distr_int_data();
  sigp_distr_ene   = ace_obj.get_photon_prod_distr_ene_data();
  sigp_distr_data  = ace_obj.get_photon_prod_distr_data();
  for(int i=0; i<static_cast<int>(sigp_distr_ene.size()); i++)
  {
    for(int j=0; j<static_cast<int>(sigp_distr_ene[i].size()); j++)
    {
      sigp_distr_ene[i][j] *= unit_mega;
    }
  }

  //Data from ANDP block
  andp_ene_data = ace_obj.get_photon_angular_distr_ene_data();
  andp_cos_data = ace_obj.get_photon_angular_distr_prob_cos_data();
  for(int i=0; i<static_cast<int>(andp_ene_data.size()); i++)
  {
    for(int j=0; j<static_cast<int>(andp_ene_data[i].size()); j++)
    {
      andp_ene_data[i][j] *= unit_mega;
    }
  }

  //Data from DLWP block
  dlwp_distr_flg = ace_obj.get_photon_energy_distr_flg();
  dlwp_range     = ace_obj.get_photon_energy_distr_range_data();
  dlwp_int       = ace_obj.get_photon_energy_distr_int_data();
  dlwp_ene       = ace_obj.get_photon_energy_distr_ene_data();
  dlwp_prob      = ace_obj.get_photon_energy_distr_prob_data();
  for(int i=0; i<static_cast<int>(dlwp_ene.size()); i++)
  {
    for(int j=0; j<static_cast<int>(dlwp_ene[i].size()); j++)
    {
      dlwp_ene[i][j] *= unit_mega;
    }
  }

  //DLWP Law = 2
  dlwp_ene_distr_flg = ace_obj.get_photon_energy_distr_ene_flg();
  dlwp_binding_ene   = ace_obj.get_photon_energy_distr_binding_ene_data();  
  for(int i=0; i<static_cast<int>(dlwp_binding_ene.size()); i++)
  {
    dlwp_binding_ene[i] *= unit_mega;
  }


  //DLWP Law = 4
  dlwp_ein_range = ace_obj.get_photon_energy_distr_ene_in_range_data();
  dlwp_ein_int   = ace_obj.get_photon_energy_distr_ene_in_int_data();
  dlwp_ein_data  = ace_obj.get_photon_energy_distr_ene_in_data();
  for(int i=0; i<static_cast<int>(dlwp_ein_data.size()); i++)
  {
    for(int j=0; j<static_cast<int>(dlwp_ein_data[i].size()); j++)
    {
      dlwp_ein_data[i][j] *= unit_mega;
    }
  }

  dlwp_eout_int    = ace_obj.get_photon_energy_distr_weight_int_data();
  dlwp_eout_data   = ace_obj.get_photon_energy_distr_weight_ene_data();
  dlwp_eout_weight = ace_obj.get_photon_energy_distr_weight_data();
  for(int i=0; i<static_cast<int>(dlwp_eout_data.size()); i++)
  {
    for(int j=0; j<static_cast<int>(dlwp_eout_data[i].size()); j++)
    {
      int cont_sta_pos = dlwp_eout_int[i][j] / 10;
      for(int k=0; k<static_cast<int>(dlwp_eout_data[i][j].size()); k++)
      {
        dlwp_eout_data[i][j][k]   *= unit_mega;

        //dlwp_eout_weight is obtained from LDLWP block LAW=4 in the ACE file.
        //This value contains both continuous and discrete photon data.
        //The modification of the discrete photon data is skipped.
        if( k >= cont_sta_pos )
        {
          dlwp_eout_weight[i][j][k] *= unit_micro;
        }
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MGPhotonProduction::calc_photon_production_data
                           (FastAceDataObject& ace_obj, vector<Real> ene_vec,
                            vector<vector<Real> > flux_vec, vector<vector<Real> > sig_t_sig_bg,
                            vector<Real> mg_ein, vector<Real> mg_eout, int pl_no)
{
  clear();

  if( static_cast<int>(mg_eout.size()) == 0 )
  {
    cout << endl;
    cout << "The size of gamma group structure is zero." << endl;
    cout << "Calculation of multi-group generation for photon production reaction is skipped." << endl;
    cout << endl;
    return;
  }

  pl_no_ori = pl_no;
  pl_no     = 0;

  calc_dd_xs_flg = 1;
  egg_vec = mg_eout;
  za_val  = ace_obj.get_izaid();
  awr_val = ace_obj.get_aw0();

  copy_ace_data(ace_obj);

  modify_mg_ene_data(mg_ein);
  modify_mg_ene_data(mg_eout);
  modify_flux(ene_vec, flux_vec, sig_t_sig_bg);

  flux_ang = mg_obj.calc_angular_flux(flux_vec, sig_t_sig_bg, pl_no);

  mg_obj.set_awr_val(awr_val);

  int mtrp_no = static_cast<int>(mtrp_mt_list.size());
  if( mtrp_no == 0 )
  {
    clear_calc_data();

    cout << endl;
    cout << "The photon production data is not found." << endl;
    cout << "Calculation of multi-group generation for photon production reaction is skipped." << endl;
    cout << endl;
    return;
  }

  get_mt_list();

  boost::timer::cpu_timer time_tot;

  cout << endl;
  cout <<"======================================================================================================" << endl;
  cout << "  Calculation of multi-group generation for photon production reaction." << endl;
  cout <<"======================================================================================================" << endl;
  cout << endl;

  int mt_no = static_cast<int>(mt_list.size());
  photon_xs.resize(mt_no);
  photon_dd_xs.resize(mt_no);
  for(int i=0; i<mt_no; i++)
  {
    boost::timer::cpu_timer time_each_mt;

    calc_photon_production_data_each_mt(i, ace_obj, ene_vec, flux_vec, sig_t_sig_bg,
                                        mg_ein, mg_eout, pl_no);

    Real time_each_mt_val = static_cast<Real>(time_each_mt.elapsed().wall * 1.0E-9);
    int digit_no_t = digit_obj.get_digit_number(time_each_mt_val) + 2;
    cout << "    Calculation time of MT = " << mt_list[i] << " : "
         << setw(digit_no_t) << time_each_mt_val << " [s] ";
    if( emit_photon_no[i] < 0 )
    {
      cout << "(continuous distribution)" << endl;
    }
    else
    {
      cout << "(discrete distribution)" << endl;
    }
  }
  Real time_tot_val = static_cast<Real>(time_tot.elapsed().wall * 1.0E-9);
  int digit_no_t = digit_obj.get_digit_number(time_tot_val) + 2;
  cout << "  Total calculation time for photon production reaction : "
       << setw(digit_no_t) << time_tot_val << " [s]" << endl;
  cout << endl;

  clear_calc_data();

  merge_continuous_and_discrete_data();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MGPhotonProduction::modify_mg_ene_data(vector<Real>& mg_ene_data)
{
  int mg_no = static_cast<int>(mg_ene_data.size());
  if( mg_no <= 1 )
  {
    return;
  }

  if( mg_ene_data[0] < mg_ene_data[1] )
  {
    return;
  }

  sort(mg_ene_data.begin(), mg_ene_data.end());
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MGPhotonProduction::modify_flux
                           (vector<Real>& ene_vec,
                            vector<vector<Real> >& flux_vec, vector<vector<Real> >& sig_t_sig_bg)
{
  int b_no = static_cast<int>(flux_vec.size());
  if( b_no == 0 )
  {
    return;
  }

  int ene_no = static_cast<int>(ene_vec.size());
  for(int b=0; b<b_no; b++)
  {
    int ene_f = static_cast<int>(flux_vec[b].size());
    if( ene_no != ene_f )
    {
      flux_vec[b].resize(ene_no);
      sig_t_sig_bg[b].resize(ene_no);
      for(int i=ene_f; i<ene_no; i++)
      {
        flux_vec[b][i]     = flux_vec[b][i-1];
        sig_t_sig_bg[b][i] = sig_t_sig_bg[b][i-1];
      }
    }
  }

  vector<Real>          ene_ori          = ene_vec;
  vector<vector<Real> > flux_ori         = flux_vec;
  vector<vector<Real> > sig_t_sig_bg_ori = sig_t_sig_bg;
  if( ene_vec[0] > ene_vec[ene_no-1] )
  {
    for(int i=0; i<ene_no; i++)
    {
      ene_vec[i] = ene_ori[ene_no-i-1];
    }

    for(int b=0; b<b_no; b++)
    {
      for(int i=0; i<ene_no; i++)
      {
        flux_vec[b][i]     = flux_ori[b][ene_no-i-1];
        sig_t_sig_bg[b][i] = sig_t_sig_bg_ori[b][ene_no-i-1];
      }
    }
  }
  ene_ori.clear();
  clr_obj.clear_vec_array2_real(flux_ori);
  clr_obj.clear_vec_array2_real(sig_t_sig_bg_ori);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MGPhotonProduction::get_mt_list()
{
  int mtrp_no = static_cast<int>(mtrp_mt_list.size());

  mt_list.clear();
  emit_photon_no.clear();

  int ele_no        = -1;
  int mt_pre        =  0;
  int distr_flg_pre =  0;
  for(int i=0; i<mtrp_no; i++)
  {
    if( static_cast<int>(sigp_xs[i].size()) == 0 && static_cast<int>(sigp_multi_ene[i].size()) == 0 &&
        static_cast<int>(sigp_distr_data[i].size()) == 0 )
    {
      continue;
    }

    Integer mt_cur = mtrp_mt_list[i] / 1000;
    if( sigp_react_type[i] != mt_cur )
    {
      if( sigp_react_type[i] == 0 )
      {
        sigp_react_type[i] = mt_cur;
      }
      else
      {
        string class_name = "MGPhotonProduction";
        string func_name  = "get_mt_list()";

        ostringstream oss01, oss02, oss03, oss04;
        oss01 << i+1;
        oss02 << mtrp_no;
        oss03 << mtrp_mt_list[i];
        oss04 << sigp_react_type[i];
        string str_data01 = "Position of MTRP block                                 : " + oss01.str() + " / " + oss02.str();
        string str_data02 = "Reaction type number from MTRP block (mtrp_mt_list)    : " + oss03.str();
        string str_data03 = "Reaction type number from DLWP block (sigp_react_type) : " + oss04.str();

        vector<string> err_com;
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back("mtrp_mt_list/1000 != sigp_react_type.");
        err_com.push_back("Please check the reaction type number or modify this function.");

          err_obj.output_runtime_error(class_name, func_name, err_com);
      }
    }

    if( mt_cur != mt_pre )
    {
      mt_list.push_back(mt_cur);

      if( dlwp_distr_flg[i] == 2 )
      {
        emit_photon_no.push_back(1);
      }
      else if( dlwp_distr_flg[i] == 4 || dlwp_distr_flg[i] == 44 )
      {
        emit_photon_no.push_back(-1);
      }
      else
      {
        string class_name = "MGPhotonProduction";
        string func_name  = "get_mt_list()";

        ostringstream oss01, oss02;
        oss01 << mtrp_mt_list[i];
        oss02 << sigp_file_no[i];
        string str_data01 = "Reaction type number (mtrp_mt_list)      : " + oss01.str();
        string str_data02 = "LAW value in DLWP block (dlwp_distr_flg) : " + oss02.str();

        vector<string> err_com;
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back("The LAW value in DLWP block is 2, 4, and 44.");
        err_com.push_back("Please check the LAW value in DLWP block or modify this function.");

        err_obj.output_runtime_error(class_name, func_name, err_com);
      }

      ele_no++;
      mt_pre        = mt_cur;
      distr_flg_pre = dlwp_distr_flg[i];

      continue;
    }

    if( dlwp_distr_flg[i] == distr_flg_pre && distr_flg_pre == 2 )
    {
      emit_photon_no[ele_no]++;
    }
    else if( dlwp_distr_flg[i] == 4 || dlwp_distr_flg[i] == 44 )
    {
      mt_list.push_back(mt_cur);
      emit_photon_no.push_back(-1);

      ele_no++;
      mt_pre        = mt_cur;
      distr_flg_pre = dlwp_distr_flg[i];

      continue;
    }
    else
    {
      string class_name = "MGPhotonProduction";
      string func_name  = "get_mt_list()";

      ostringstream oss01, oss02;
      oss01 << mtrp_mt_list[i];
      oss02 << dlwp_distr_flg[i];
      string str_data01 = "Reaction type number (mtrp_mt_list)      : " + oss01.str();
      string str_data02 = "Law data for DLWP block (dlwp_distr_flg) : " + oss02.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back("The LAW value in DLWP block is 2, 4, and 44.");
      err_com.push_back("Please check the LAW value in DLWP block or modify this function.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }

  int mt_no = static_cast<int>(mt_list.size());
  mt_list_pos.resize(mt_no);
  transition_prob.resize(mt_no);
  ddxs_multi_range.resize(mt_no);
  ddxs_multi_int.resize(mt_no);
  ddxs_multi_ene.resize(mt_no);
  ddxs_multi_data.resize(mt_no);
  for(int i=0; i<mt_no; i++)
  {
    if( i==0 )
    {
      mt_list_pos[i] = 0;
    }
    else
    {
      int pos_add = 1;
      if( emit_photon_no[i-1] > 0 )
      {
        pos_add = emit_photon_no[i-1];
      }
      mt_list_pos[i] = mt_list_pos[i-1] + pos_add;
    }

    transition_prob[i].clear();
    ddxs_multi_range[i].clear();
    ddxs_multi_int[i].clear();
    ddxs_multi_ene[i].clear();
    ddxs_multi_data[i].clear();
    if( emit_photon_no[i] > 0 )
    {
      transition_prob[i].resize(emit_photon_no[i]);
      ddxs_multi_range[i].resize(emit_photon_no[i]);
      ddxs_multi_int[i].resize(emit_photon_no[i]);
      ddxs_multi_ene[i].resize(emit_photon_no[i]);
      ddxs_multi_data[i].resize(emit_photon_no[i]);
      for(int j=0; j<emit_photon_no[i]; j++)
      {
        transition_prob[i][j] = 1.0;
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MGPhotonProduction::calc_photon_production_data_each_mt
                           (int mt_pos, FastAceDataObject& ace_obj,
                            vector<Real>& ene_vec,
                            vector<vector<Real> >& flux_vec, vector<vector<Real> >& sig_t_sig_bg,
                            vector<Real>& mg_ein, vector<Real>& mg_eout, int pl_no)
{
  photon_xs_fine_ene.clear();
  clr_obj.clear_vec_array2_real(photon_xs_fine);
  clr_obj.clear_vec_array3_real(dd_xs_coef);

  //Calculation of cross section from SIGP block data
  calc_photon_production_xs(mt_pos, ace_obj, ene_vec, flux_vec, mg_ein);

  //Calculation of Legendre coefficients from ANDP block data
  int mt_pos_tot = mt_list_pos[mt_pos];
  calc_ddxs_coef(mt_pos_tot, ene_vec, pl_no);
  if( static_cast<int>(dd_xs_coef.size()) == 0 )
  {
    photon_dd_xs[mt_pos].clear();
    return;
  }

  if( emit_photon_no[mt_pos] < 0 )
  {
    //Calculation of double differential cross section from ANDP and DLWP block data
    //(LAW = 4: Continuous Tabular Distribution, LAW = 44: Kalbach-87 Formalism)
    calc_photon_production_dd_xs
      (mt_pos, ace_obj, ene_vec, flux_vec, sig_t_sig_bg, mg_ein, mg_eout, pl_no);
  }
  if( emit_photon_no[mt_pos] > 0 )
  {
    //Calculation of double differential cross section from ANDP and DLWP block data
    //(LAW = 2 : Discrete Photon Energy)
    calc_photon_production_dd_xs_with_discrete_ene
      (mt_pos, ace_obj, ene_vec, flux_vec, sig_t_sig_bg, mg_ein, mg_eout, pl_no);
  }

  photon_xs_fine_ene.clear();
  clr_obj.clear_vec_array2_real(photon_xs_fine);
  clr_obj.clear_vec_array3_real(dd_xs_coef);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MGPhotonProduction::calc_photon_production_xs
                           (int mt_pos, FastAceDataObject& ace_obj, 
                            vector<Real>& ene_vec, vector<vector<Real> >& flux_vec,
                            vector<Real>& mg_ein)
{
  int mt_pos_tot = mt_list_pos[mt_pos];

  //Calculation of cross section from SIGP block data
  vector<Real> ace_ene_grid_mod = ace_ene_grid;
  int ace_ene_no = static_cast<int>(ace_ene_grid_mod.size());
  vector<Real> ace_photon_xs_tot, ace_photon_xs_init, ddxs_multi_data_tot;
  ace_photon_xs_tot.resize(ace_ene_no);
  ace_photon_xs_init.resize(ace_ene_no);
  ddxs_multi_data_tot.resize(ace_ene_no);
  for(int i=0; i<ace_ene_no; i++)
  {
    ace_photon_xs_tot[i]   = 0.0;
    ace_photon_xs_init[i]  = 0.0;
    ddxs_multi_data_tot[i] = 0.0;
  }

  //Get neutron induced reaction cross section (MF=3)
  Integer mt_no = sigp_react_type[mt_pos_tot];
  vector<Real> ace_xs_ene, ace_xs_data;
  ace_obj.get_xs_data(mt_no, ace_xs_ene, ace_xs_data);
  int ace_xs_ene_no = static_cast<int>(ace_xs_ene.size());
  if( ace_xs_ene_no > 0 )
  {
    for(int i=0; i<ace_xs_ene_no; i++)
    {
      ace_xs_ene[i] *= unit_mega;
    }
  }

  if( sigp_file_no[mt_pos_tot] == 13 )
  {
    int j_max = 1;
    if( emit_photon_no[mt_pos] > 0 )
    {
      j_max = emit_photon_no[mt_pos];
    }
    for(int j=0; j<j_max; j++)
    {
      int ene_sta = sigp_pos[mt_pos_tot+j][0];
      int ene_no  = sigp_pos[mt_pos_tot+j][1];
      if( ene_sta == 0 )
      {
        ene_sta++;
      }
      if( ene_no > ace_ene_no )
      {
        ene_no = ace_ene_no;
      }

      for(int i=0; i<ene_no; i++)
      {
        if( sigp_xs[mt_pos_tot+j][i] > min_value )
        {
          ace_photon_xs_tot[ene_sta-1+i] += sigp_xs[mt_pos_tot+j][i];

          if( ace_photon_xs_init[ene_sta-1+i] < min_value )
          {
            ace_photon_xs_init[ene_sta-1+i] = sigp_xs[mt_pos_tot+j][i];
          }
        }
      }
    }

    int check_xs_flg = 0;
    for(int i=0; i<ace_ene_no; i++)
    {
      if( ace_photon_xs_tot[i] > min_value )
      {
        check_xs_flg = 1;
        break;
      }
    }

    for(int i=0; i<ace_ene_no; i++)
    {
      if( check_xs_flg == 0 && ace_xs_ene_no > 0 )
      {
        //If MF=13 data is not found and cross section data is only found in MF=3
        //the total photon production cross section is copied from MF=3.
        Real ace_photon_xs_val = 0.0;
        ti_obj.interpolation_1d(int_lin_lin, ace_ene_grid_mod[i], ace_photon_xs_val,
                                               ace_xs_ene, ace_xs_data);

        if( ace_photon_xs_val < min_value )
        {
          ace_photon_xs_val = 0.0;
        }
        ace_photon_xs_tot[i]   = ace_photon_xs_val;
      }

      ddxs_multi_data_tot[i] = 0.0;
      if( ace_photon_xs_init[i] > min_value )
      {
        //ddxs_multi_data_tot[i] = 1.0 / ace_photon_xs_init[i];
      }
      if( ace_photon_xs_tot[i] > min_value )
      {
        ddxs_multi_data_tot[i] = 1.0 / ace_photon_xs_tot[i];
      }
    }
  }
  else if( sigp_file_no[mt_pos_tot] == 12 || sigp_file_no[mt_pos_tot] == 16 )
  {
    if( ace_xs_ene_no == 0 )
    {
      string class_name = "MGPhotonProduction";
      string func_name  = "calc_photon_production_xs";

      ostringstream oss01, oss02;
      oss01 << mtrp_mt_list[mt_pos_tot];
      oss02 << mt_no;
      string str_data01 = "Reaction type number (mtrp_mt_list)        : " + oss01.str();
      string str_data02 = "Reaction type number for photon production : " + oss02.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back("This mt number is not found in the ACE file.");

      if( sigp_file_no[mt_pos_tot] == 12 )
      {
        err_com.push_back("Please check the ACE file.");
        err_obj.output_runtime_error(class_name, func_name, err_com);
      }
      else //if( sigp_file_no[mt_pos_tot] == 16 )
      {
        err_com.push_back("This ACE file may be incorrect.");
        err_obj.output_caution(class_name, func_name, err_com);
      }
    }

    if( sigp_file_no[mt_pos_tot] == 12 )
    {
      vector<Real> sigp_multi_data_mod = sigp_multi_data[mt_pos_tot];
      //Modify yield data for LO at MF=12 is 2 (Transition Probability Arrays)
      if( emit_photon_no[mt_pos] > 0 )
      {
        for(int j=0; j<static_cast<int>(sigp_multi_data_mod.size()); j++)
        {
          sigp_multi_data_mod[j] = 1.0;
        }

        //Copy transition probability of each photon
        for(int j=0; j<emit_photon_no[mt_pos]; j++)
        {
          if( static_cast<int>(sigp_multi_data[mt_pos_tot+j].size()) > 0 )
          {
            transition_prob[mt_pos][j]  = sigp_multi_data[mt_pos_tot+j][0];
            ddxs_multi_range[mt_pos][j] = sigp_multi_range[mt_pos_tot+j];
            ddxs_multi_int[mt_pos][j]   = sigp_multi_int[mt_pos_tot+j];
            ddxs_multi_ene[mt_pos][j]   = sigp_multi_ene[mt_pos_tot+j];
            ddxs_multi_data[mt_pos][j]  = sigp_multi_data[mt_pos_tot+j];
          }
        }
      }

      ace_photon_xs_tot = mg_obj.calc_part_xs_data(ace_ene_grid_mod, ace_xs_data,
                                 sigp_multi_range[mt_pos_tot], sigp_multi_int[mt_pos_tot],
                                 sigp_multi_ene[mt_pos_tot],   sigp_multi_data_mod);
    }
    else //if( sigp_file_no[mt_pos_tot] == 16 )
    {
      ace_photon_xs_tot = mg_obj.calc_part_xs_data(ace_ene_grid_mod, ace_xs_data,
                                 sigp_distr_range[mt_pos_tot], sigp_distr_int[mt_pos_tot],
                                 sigp_distr_ene[mt_pos_tot],   sigp_distr_data[mt_pos_tot]);
    }
  }
  else
  {
    string class_name = "MGPhotonProduction";
    string func_name  = "calc_photon_production_xs";

    ostringstream oss01, oss02;
    oss01 << mtrp_mt_list[mt_pos_tot];
    oss02 << sigp_file_no[mt_pos_tot];
    string str_data01 = "Reaction type number (mtrp_mt_list)      : " + oss01.str();
    string str_data02 = "File number in SIGP block (sigp_file_no) : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("The available file number in SIGP block is 12, 13, and 16.");
    err_com.push_back("Please check the file number in SIGP block or modify this function.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  int b_no = static_cast<int>(flux_vec.size());
  photon_xs[mt_pos].resize(b_no);
  photon_xs_fine.resize(b_no);

  photon_xs_fine_ene.clear();
  for(int b=0; b<b_no; b++)
  {
    mg_obj.calc_mg_xs(ene_vec, flux_vec[b], ace_ene_grid_mod, ace_photon_xs_tot,
                      mg_ein, photon_xs[mt_pos][b], photon_xs_fine_ene, photon_xs_fine[b]);
  }

  if( b_no > 0 )
  {
    if( sigp_file_no[mt_pos_tot] == 13 )
    {
      for(int j=0; j<emit_photon_no[mt_pos]; j++)
      {
        int ene_sta = sigp_pos[mt_pos_tot+j][0];
        int ene_no  = sigp_pos[mt_pos_tot+j][1];
        if( ene_sta == 0 )
        {
          ene_sta++;
        }
        if( ene_no > ace_ene_no )
        {
          ene_no = ace_ene_no;
        }

        vector<Real> ace_photon_xs_each;
        ace_photon_xs_each.resize(ace_ene_no);
        for(int k=0; k<ace_ene_no; k++)
        {
          ace_photon_xs_each[k] = 0.0;
        }
        for(int k=0; k<ene_no; k++)
        {
          ace_photon_xs_each[ene_sta-1+k] = sigp_xs[mt_pos_tot+j][k];
        }

        ddxs_multi_range[mt_pos][j].resize(1);
        ddxs_multi_int[mt_pos][j].resize(1);
        ddxs_multi_range[mt_pos][j][0] = ace_ene_no;
        ddxs_multi_int[mt_pos][j][0]   = int_lin_lin;

        ddxs_multi_ene[mt_pos][j] = ace_ene_grid;
        ddxs_multi_data[mt_pos][j].resize(ace_ene_no);
        for(int k=0; k<ace_ene_no; k++)
        {
          ddxs_multi_data[mt_pos][j][k] = 0.0;
          if( ace_photon_xs_each[k] > min_value )
          {
            ddxs_multi_data[mt_pos][j][k] = ace_photon_xs_each[k] * ddxs_multi_data_tot[k];
          }
        }
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MGPhotonProduction::calc_photon_production_dd_xs
                           (int mt_pos, FastAceDataObject& ace_obj, vector<Real>& ene_vec,
                            vector<vector<Real> >& flux_vec, vector<vector<Real> >& sig_t_sig_bg,
                            vector<Real>& mg_ein, vector<Real>& mg_eout, int pl_no)
{
  int mt_pos_tot = mt_list_pos[mt_pos];

  //Devide  discrete (disc) data and continuous (cont) data
  vector<Integer>       dlwp_eout_int_mod;
  vector<vector<Real> > dlwp_eout_data_disc, dlwp_eout_weight_disc, dlwp_eout_data_cont, dlwp_eout_weight_cont;
  modify_dlwp_eout_data(dlwp_eout_int[mt_pos_tot], dlwp_eout_data[mt_pos_tot], dlwp_eout_weight[mt_pos_tot],
                        dlwp_eout_int_mod, dlwp_eout_data_cont,  dlwp_eout_weight_cont,
                                           dlwp_eout_data_disc,  dlwp_eout_weight_disc);

  modify_dlwp_eout_data_threshold_ene(mt_pos_tot, dlwp_eout_data_cont,  dlwp_eout_weight_cont,
                                                  dlwp_eout_data_disc,  dlwp_eout_weight_disc);


  //Calculation of double differential cross section from DLWP block data
  photon_dd_xs[mt_pos] = mg_obj.calc_mg_dd_xs
                                  (dd_xs_coef, ene_vec, flux_ang, mg_ein, mg_eout,
                                   dlwp_ein_range[mt_pos_tot], dlwp_ein_int[mt_pos_tot],
                                   dlwp_ein_data[mt_pos_tot],  dlwp_eout_int_mod,
                                   dlwp_eout_data_cont, dlwp_eout_weight_cont,
                                   dlwp_eout_data_disc, dlwp_eout_weight_disc);

}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MGPhotonProduction::modify_dlwp_eout_data
                           (vector<Integer>& dlwp_eout_int_ori,
                            vector<vector<Real> >& dlwp_eout_data_ori,  vector<vector<Real> >& dlwp_eout_weight_ori,
                            vector<Integer>& dlwp_eout_int_mod,
                            vector<vector<Real> >& dlwp_eout_data_cont, vector<vector<Real> >& dlwp_eout_weight_cont,
                            vector<vector<Real> >& dlwp_eout_data_disc, vector<vector<Real> >& dlwp_eout_weight_disc)
{
  int i_max = static_cast<int>(dlwp_eout_int_ori.size());
  dlwp_eout_int_mod.resize(i_max);
  dlwp_eout_data_disc.resize(i_max);
  dlwp_eout_weight_disc.resize(i_max);
  dlwp_eout_data_cont.resize(i_max);
  dlwp_eout_weight_cont.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    dlwp_eout_data_disc[i].clear();
    dlwp_eout_weight_disc[i].clear();
    dlwp_eout_data_cont[i].clear();
    dlwp_eout_weight_cont[i].clear();

    if( dlwp_eout_int_ori[i] < 10 )
    {
      dlwp_eout_int_mod[i]     = dlwp_eout_int_ori[i];
      dlwp_eout_data_cont[i]   = dlwp_eout_data_ori[i];
      dlwp_eout_weight_cont[i] = dlwp_eout_weight_ori[i];
    }
    else
    {
      int j_max   = static_cast<int>(dlwp_eout_data_ori[i].size());
      int disc_no = dlwp_eout_int_ori[i] / 10;
      int cont_no = j_max - disc_no;

      dlwp_eout_int_mod[i] = dlwp_eout_int_ori[i]%10;

      dlwp_eout_data_disc[i].clear();
      dlwp_eout_weight_disc[i].clear();
      for(int j=0; j<disc_no; j++)
      {
        if( dlwp_eout_weight_ori[i][j] > min_value )
        {
          dlwp_eout_data_disc[i].push_back(dlwp_eout_data_ori[i][j]);
          dlwp_eout_weight_disc[i].push_back(dlwp_eout_weight_ori[i][j]);
        }
      }

      dlwp_eout_data_cont[i].resize(cont_no);
      dlwp_eout_weight_cont[i].resize(cont_no);
      for(int j=0; j<cont_no; j++)
      {
        dlwp_eout_data_cont[i][j]   = dlwp_eout_data_ori[i][j+disc_no];
        dlwp_eout_weight_cont[i][j] = dlwp_eout_weight_ori[i][j+disc_no];
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MGPhotonProduction::modify_dlwp_eout_data_threshold_ene
                           (int mt_pos_tot,
                            vector<vector<Real> >& dlwp_eout_data_cont, vector<vector<Real> >& dlwp_eout_weight_cont,
                            vector<vector<Real> >& dlwp_eout_data_disc, vector<vector<Real> >& dlwp_eout_weight_disc)
{
  int i_max = static_cast<int>(dlwp_ein_data[mt_pos_tot].size());
  if( i_max <= 1 )
  {
    return;
  }

  if( static_cast<int>(dlwp_eout_data_disc[0].size()) > 0 ||
      static_cast<int>(dlwp_eout_data_cont[0].size()) > 3 ||
      dlwp_ein_data[mt_pos_tot][0] < 1.0E-4 )
  {
    return;
  }

  int pos_data_no = 0;
  int j_max       = static_cast<int>(dlwp_eout_data_cont[0].size());
  for(int j=0; j<j_max; j++)
  {
    if( fabs(dlwp_eout_weight_cont[0][j]) > 0.1 )
    {
      pos_data_no++;
    }
  }

  if( pos_data_no <= 1 )
  {
    string class_name = "MGPhotonProduction";
    string func_name  = "modify_dlwp_eout_data_threshold_ene";

    ostringstream oss00, oss01, oss02, oss03, oss04, oss05;
    oss00 << mtrp_mt_list[mt_pos_tot];
    oss01 << setw(10) << setiosflags(ios::showpoint) << setiosflags(ios::scientific) << dlwp_ein_data[mt_pos_tot][0];
    oss02 << setw(10) << setiosflags(ios::showpoint) << setiosflags(ios::scientific) << dlwp_ein_data[mt_pos_tot][1];
    string str_data00 = "Section number (MT) : " + oss00.str();
    string str_data01 = "dlwp_ein_data[0]    : " + oss01.str();
    string str_data02 = "dlwp_ein_data[1]    : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data00);
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("This photon production data may be dummy data.");
    err_com.push_back("This photon data are substituted by the next positon data.");
    err_com.push_back("");

    err_com.push_back("Original data");
    int k_max = static_cast<int>(dlwp_eout_data_cont[0].size());
    for(int k=0; k<k_max; k++)
    {
      ostringstream oss10, oss11, oss12, oss13;
      oss10 << k+1;
      oss11 << k_max;
      oss12 << setw(10) << setiosflags(ios::showpoint) << setiosflags(ios::scientific) << dlwp_eout_data_cont[0][k];
      oss13 << setw(10) << setiosflags(ios::showpoint) << setiosflags(ios::scientific) << dlwp_eout_weight_cont[0][k];
      string str_data10 = "  " + oss10.str() + " / " + oss11.str() + " : " + oss12.str() + "  " + oss13.str();
      err_com.push_back(str_data10);
    }
    err_com.push_back("");

    dlwp_eout_data_cont[0]   = dlwp_eout_data_cont[1];
    dlwp_eout_weight_cont[0] = dlwp_eout_weight_cont[1];

    err_com.push_back("Modified data");
    k_max = static_cast<int>(dlwp_eout_data_cont[0].size());
    for(int k=0; k<k_max; k++)
    {
      ostringstream oss10, oss11, oss12, oss13;
      oss10 << k+1;
      oss11 << k_max;
      oss12 << setw(10) << setiosflags(ios::showpoint) << setiosflags(ios::scientific) << dlwp_eout_data_cont[0][k];
      oss13 << setw(10) << setiosflags(ios::showpoint) << setiosflags(ios::scientific) << dlwp_eout_weight_cont[0][k];
      string str_data10 = "  " + oss10.str() + " / " + oss11.str() + " : " + oss12.str() + "  " + oss13.str();
      err_com.push_back(str_data10);
    }
    err_com.push_back("");

    err_obj.output_caution(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MGPhotonProduction::calc_photon_production_dd_xs_with_discrete_ene
                           (int mt_pos, FastAceDataObject& ace_obj, vector<Real>& ene_vec,
                            vector<vector<Real> >& flux_vec, vector<vector<Real> >& sig_t_sig_bg,
                            vector<Real>& mg_ein, vector<Real>& mg_eout, int pl_no)
{
  for(int mt=0; mt<emit_photon_no[mt_pos]; mt++)
  {
    int mt_pos_tot = mt_list_pos[mt_pos] + mt;

    vector<vector<vector<vector<Real> > > > photon_dd_xs_tmp;
    photon_dd_xs_tmp = mg_obj.calc_mg_dd_xs_with_discrete_ene
                                    (dd_xs_coef, ene_vec, flux_ang, mg_ein, mg_eout,
                                     ddxs_multi_range[mt_pos][mt], ddxs_multi_int[mt_pos][mt],
                                     ddxs_multi_ene[mt_pos][mt], ddxs_multi_data[mt_pos][mt],
                                     dlwp_ene_distr_flg[mt_pos_tot], dlwp_binding_ene[mt_pos_tot]);

    Real coef_val = 1.0;
    //add_photon_dd_xs_data(mt_pos, transition_prob[mt_pos][mt], photon_dd_xs_tmp);
    add_photon_dd_xs_data(mt_pos, coef_val, photon_dd_xs_tmp);
    clr_obj.clear_vec_array4_real(photon_dd_xs_tmp);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void  MGPhotonProduction::add_photon_dd_xs_data(int mt_pos, Real coef,
                                                vector<vector<vector<vector<Real> > > >& photon_dd_xs_add)
{
  //Initialize photon_dd_xs data
  if( static_cast<int>(photon_dd_xs[mt_pos].size()) == 0 )
  {
    int e_in_no = static_cast<int>(photon_dd_xs_add.size());
    photon_dd_xs[mt_pos].resize(e_in_no);
    for(int i=0; i<e_in_no; i++)
    {
      int bg_no = static_cast<int>(photon_dd_xs_add[i].size());
      photon_dd_xs[mt_pos][i].resize(bg_no);
      for(int b=0; b<bg_no; b++)
      {
        int pl_no = static_cast<int>(photon_dd_xs_add[i][b].size());
        photon_dd_xs[mt_pos][i][b].resize(pl_no);
        for(int p=0; p<pl_no; p++)
        {
          int e_out_no = static_cast<int>(photon_dd_xs_add[i][b][p].size());
          photon_dd_xs[mt_pos][i][b][p].resize(e_out_no);
          for(int j=0; j<e_out_no; j++)
          {
            photon_dd_xs[mt_pos][i][b][p][j] = 0.0;
          }
        }
      }
    }
  }

  //Add photon_dd_xs_tmp data
  int e_in_no = static_cast<int>(photon_dd_xs[mt_pos].size());
  for(int i=0; i<e_in_no; i++)
  {
    int bg_no = static_cast<int>(photon_dd_xs[mt_pos][i].size());
    for(int b=0; b<bg_no; b++)
    {
      int pl_no = static_cast<int>(photon_dd_xs[mt_pos][i][b].size());
      for(int p=0; p<pl_no; p++)
      {
        int e_out_no = static_cast<int>(photon_dd_xs[mt_pos][i][b][p].size());
        for(int j=0; j<e_out_no; j++)
        {
          photon_dd_xs[mt_pos][i][b][p][j] += coef * photon_dd_xs_add[i][b][p][j];
        }
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void  MGPhotonProduction::calc_ddxs_coef(int mt_pos_tot, vector<Real>& ene_vec, int pl_no)
{
  vector<Real>          ang_coef_ene = andp_ene_data[mt_pos_tot];
  vector<vector<Real> > ang_coef;

  int andp_no = static_cast<int>(ang_coef_ene.size());
  ang_coef.resize(andp_no);
  if( andp_no > 0 )
  {
    for(int i=0; i<andp_no; i++)
    {
      if( static_cast<int>(andp_cos_data[mt_pos_tot][i].size()) !=  0 &&
          static_cast<int>(andp_cos_data[mt_pos_tot][i].size()) != 32 )
      {
        string class_name = "MGPhotonProduction";
        string func_name  = "calc_ddxs_coef";

        ostringstream oss01, oss02;
        oss01 << mtrp_mt_list[mt_pos_tot];
        oss02 <<  static_cast<int>(andp_cos_data[mt_pos_tot][i].size());
        string str_data01 = "Reaction type number (mtrp_mt_list)          : " + oss01.str();
        string str_data02 = "Number of angular distribution in ANDP block : " + oss02.str();

        vector<string> err_com;
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back("The number of angular distribution in ANDP block should be 32.");
        err_com.push_back("Please check the number of angular distribution in ANDP block or modify this function.");

        err_obj.output_caution(class_name, func_name, err_com);
      }

      ang_coef[i] = mg_obj.get_legendre_coef_from_equi_prob_data(andp_cos_data[mt_pos_tot][i], pl_no);
    }
  }
  else //if(andp_no==0)
  {
    ang_coef_ene.resize(1);
    ang_coef.resize(1);

    int ene_no = static_cast<int>(ene_vec.size());
    ang_coef_ene[0] = ene_vec[ene_no-1];

    ang_coef[0].resize(pl_no+1);
    ang_coef[0][0] = 1.0;
    for(int p=1; p<pl_no+1; p++)
    {
      ang_coef[0][p] = 0.0;
    }
  }

  dd_xs_coef = mg_obj.multiply_coef(photon_xs_fine_ene, photon_xs_fine, ang_coef_ene, ang_coef);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MGPhotonProduction::merge_continuous_and_discrete_data()
{
  int mt_no = static_cast<int>(mt_list.size());
  if( mt_no <= 1 )
  {
    return;
  }

  vector<int>                                      mt_list_new, mt_pos;
  vector<vector<vector<Real> > >                   photon_xs_new;
  vector<vector<vector<vector<vector<Real> > > > > photon_dd_xs_new;
  mt_list_new.push_back(mt_list[0]);
  photon_xs_new.push_back(photon_xs[0]);
  photon_dd_xs_new.push_back(photon_dd_xs[0]);

  int ele_no = 0;
  mt_pos.resize(mt_no);
  mt_pos[0] = 0;
  for(int i=1; i<mt_no; i++)
  {
    int add_flg = -1;
    for(int j=0; j<i; j++)
    {
      if( mt_list[i] == mt_list[j] )
      {
        add_flg = j;
        break;
      }
    }

    if( add_flg < 0 )
    {
        mt_pos[i] = ele_no + 1;
        mt_list_new.push_back(mt_list[i]);
        photon_xs_new.push_back(photon_xs[i]);
        photon_dd_xs_new.push_back(photon_dd_xs[i]);
        ele_no++;
        continue;
    }

    mt_pos[i] = mt_pos[add_flg];
    add_photon_xs_data(photon_xs_new[mt_pos[i]], photon_xs[i]);
    add_photon_dd_xs_data(photon_dd_xs_new[mt_pos[i]], photon_dd_xs[i]);
  }

  mt_list      = mt_list_new;
  photon_xs    = photon_xs_new;
  photon_dd_xs = photon_dd_xs_new;
  mt_list_new.clear();
  clr_obj.clear_vec_array3_real(photon_xs_new);
  clr_obj.clear_vec_array5_real(photon_dd_xs_new);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MGPhotonProduction::add_photon_xs_data(vector<vector<Real> >& photon_xs_new,
                                            vector<vector<Real> >& photon_xs_add)
{
  int i_max = static_cast<int>(photon_xs_add.size());
  for(int i=0; i<i_max; i++) //bg(number of backgrouund cross sections)
  {
    int j_max = static_cast<int>(photon_xs_add[i].size());
    for(int j=0; j<j_max; j++) //mg(number of multi-group energies)
    {
      photon_xs_new[i][j] += photon_xs_add[i][j];
    }
  }
}


////////////////////////////////////////////////////////////////////////////////////////////////////

void MGPhotonProduction::add_photon_dd_xs_data(vector<vector<vector<vector<Real> > > >& photon_dd_xs_new,
                                               vector<vector<vector<vector<Real> > > >& photon_dd_xs_add)
{
  int i_max = static_cast<int>(photon_dd_xs_add.size());
  for(int i=0; i<i_max; i++) //e_in(number of neutron induced multi-group energies Ein)
  {
    int j_max = static_cast<int>(photon_dd_xs_add[i].size());
    for(int j=0; j<j_max; j++) //bg(number of backgrouund cross sections)
    {
      int k_max = static_cast<int>(photon_dd_xs_add[i][j].size());
      for(int k=0; k<k_max; k++) //pl(number of Legendre orders)
      {
        int l_max = static_cast<int>(photon_dd_xs_add[i][j][k].size());
        for(int l=0; l<l_max; l++) //e_out(number of outgoing multi-group energies Eout)
        {
          photon_dd_xs_new[i][j][k][l] += photon_dd_xs_add[i][j][k][l];
        }
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MGPhotonProduction::merge_gendf(GendfParser& gendf_obj)
{
  if( calc_dd_xs_flg == 0 )
  {
    return;
  }

  vector<GMF13Parser> mf13_data = get_mf13_data();
  vector<GMF16Parser> mf16_data = get_mf16_data();

  int mf13_no = static_cast<int>(mf13_data.size());
  int mf16_no = static_cast<int>(mf16_data.size());

  if( mf13_no == 0 && mf16_no == 0 )
  {
    string class_name = "MGPhotonProduction";
    string func_name  = "merge_gendf";

    vector<string> err_com;
    err_com.push_back("There is no MF=13 and MF=16 data.");
    err_com.push_back("Addition of MF=13 and MF=16 data is skipped.");

    err_obj.output_caution(class_name, func_name, err_com);
  }

  GMF01MT451Parser mf01_mt451_data = gendf_obj.get_mf01_mt451_data();

  Integer mat_no = mf01_mt451_data.get_mat_no();
  Real    za     = mf01_mt451_data.get_ZA();
  Real    awr    = mf01_mt451_data.get_AWR();
  Real    temp   = mf01_mt451_data.get_TEMP();

  mf01_mt451_data.set_NGG(static_cast<Integer>(egg_vec.size()) - 1);
  mf01_mt451_data.set_EGG(egg_vec);

  vector<vector<vector<Real> > > flux = gendf_obj.get_mf06_data(2).get_FLUX();
  if( static_cast<int>(flux.size()) == 0 )
  {
    flux = gendf_obj.get_mf03_data(1).get_FLUX();
  }

  for(int i=0; i<mf13_no; i++)
  {
    mf13_data[i].set_mat_no(mat_no);
    mf13_data[i].set_ZA(za);
    mf13_data[i].set_AWR(awr);
    mf13_data[i].set_TEMP(temp);
    mf13_data[i].set_FLUX(mg_obj.modify_flux(flux, mf13_data[i].get_IG(),
                                             mf13_data[i].get_NSIGZ(), mf13_data[i].get_NL()));
  }

  for(int i=0; i<mf16_no; i++)
  {
    mf16_data[i].set_mat_no(mat_no);
    mf16_data[i].set_ZA(za);
    mf16_data[i].set_AWR(awr);
    mf16_data[i].set_TEMP(temp);
    mf16_data[i].set_FLUX(mg_obj.modify_flux(flux, mf16_data[i].get_IG(),
                                             mf16_data[i].get_NSIGZ(), mf16_data[i].get_NL()));
  }

  gendf_obj.set_mf01_mt451_data(mf01_mt451_data);
  if( add_mf13_data_flg > 0 )
  {
    gendf_obj.set_mf13_data(mf13_data);
  }
  gendf_obj.set_mf16_data(mf16_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<vector<vector<Real> > > MGPhotonProduction::get_photon_xs()
{
  return photon_xs;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<vector<vector<vector<vector<Real> > > > > MGPhotonProduction::get_photon_dd_xs()
{
  return photon_dd_xs;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<GMF16Parser> MGPhotonProduction::get_mf16_data()
{
  vector<GMF16Parser> mf16_data;
  mf16_data.clear();
  if( calc_dd_xs_flg == 0 )
  {
    return mf16_data;
  }

  int i_max = static_cast<int>(mt_list.size());
  for(int i=0; i<i_max; i++)
  {
    if( static_cast<int>(photon_dd_xs[i].size()) == 0 )
    {
      continue;
    }

    vector<vector<vector<vector<Real> > > > dd_xs_vec = photon_dd_xs[i];
    vector<int> ig_vec, ng2_vec, ig2lo_vec;
    ig_vec.clear();
    ng2_vec.clear();
    ig2lo_vec.clear();

    mg_obj.remove_zero_dd_xs_data(dd_xs_vec, ig_vec, ng2_vec, ig2lo_vec);

    if( static_cast<int>(dd_xs_vec.size()) > 0 )
    {
      int ein_no = static_cast<int>(photon_dd_xs[i].size());
      int bg_no  = static_cast<int>(photon_dd_xs[i][0].size());
      int pl_no  = static_cast<int>(photon_dd_xs[i][0][0].size());
      if( add_pl_data_flg > 0 )
      {
        add_pl_data(i, pl_no, dd_xs_vec);
      }

      GMF16Parser mf16_data_each;
      mf16_data_each.set_mat_no(0);
      mf16_data_each.set_mt_no(mt_list[i]);
      mf16_data_each.set_NL(pl_no);
      mf16_data_each.set_NSIGZ(bg_no);
      mf16_data_each.set_LR(0);
      mf16_data_each.set_NGN(ein_no);

      mf16_data_each.set_NG2(ng2_vec);
      mf16_data_each.set_IG2LO(ig2lo_vec);
      mf16_data_each.set_IG(ig_vec);
      mf16_data_each.set_MATRIX(dd_xs_vec);

      GMF16Writer wri_obj;
      vector<string> mf16_data_str = wri_obj.get_gendf_text_data(mf16_data_each);
      mf16_data_str.pop_back(); //remove section end
      mf16_data_each.clear();
      wri_obj.clear();

      mf16_data_each.set_text(mf16_data_str);
      clr_obj.clear_vec_array1_str(mf16_data_str);

      mf16_data.push_back(mf16_data_each);
      mf16_data_each.clear();
    }
  }

  return mf16_data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<GMF13Parser> MGPhotonProduction::get_mf13_data()
{
  vector<GMF13Parser> mf13_data;
  mf13_data.clear();
  if( calc_dd_xs_flg == 0 )
  {
    return mf13_data;
  }

  int i_max = static_cast<int>(mt_list.size());
  for(int i=0; i<i_max; i++)
  {
    if( static_cast<int>(photon_xs[i].size()) == 0 )
    {
      continue;
    }

    vector<int> ig_vec, ng2_vec, ig2lo_vec;
    ig_vec.clear();
    ng2_vec.clear();
    ig2lo_vec.clear();

    vector<vector<vector<Real> > > xs_mod = mg_obj.remove_zero_xs_data
                                                     (photon_xs[i], ig_vec, ng2_vec, ig2lo_vec);

    if( static_cast<int>(xs_mod.size()) > 0 && static_cast<int>(photon_dd_xs[i].size()) > 0 )
    {
      int ein_no = static_cast<int>(photon_dd_xs[i].size());
      int bg_no  = static_cast<int>(photon_dd_xs[i][0].size());
      int pl_no  = static_cast<int>(photon_dd_xs[i][0][0].size());

      GMF13Parser mf13_data_each;
      mf13_data_each.set_mt_no(mt_list[i]);
      mf13_data_each.set_NL(pl_no);
      mf13_data_each.set_NSIGZ(bg_no);
      mf13_data_each.set_LR(0);
      mf13_data_each.set_NGN(ein_no);

      mf13_data_each.set_NG2(ng2_vec);
      mf13_data_each.set_IG2LO(ig2lo_vec);
      mf13_data_each.set_IG(ig_vec);
      mf13_data_each.set_SIG(xs_mod);

      mf13_data.push_back(mf13_data_each);
      mf13_data_each.clear();
    }
    clr_obj.clear_vec_array3_real(xs_mod);
  }

  return mf13_data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MGPhotonProduction::add_pl_data(int mt_pos, int& pl_no,
                                     vector<vector<vector<vector<Real> > > >& ddxs_vec)
{
  if( emit_photon_no[mt_pos] > 0 )
  {
    return;
  }

  if( add_pl_data_flg <= 0 )
  {
    return;
  }

  int mod_flg   = 0;
  int ene_in_no = static_cast<int>(ddxs_vec.size());
  for(int i=0; i<ene_in_no; i++)
  {
    int bg_size = static_cast<int>(ddxs_vec[i].size());
    for(int b=0; b<bg_size; b++)
    {
      int e_out_ori = -1;
      int pl_size = static_cast<int>(ddxs_vec[i][b].size());
      if( pl_no_ori + 1 != pl_size )
      {
        if( pl_size == 1 )
        {
          int ene_out_no = static_cast<int>(ddxs_vec[i][b][0].size());
          vector<Real> dummy_vec;
          dummy_vec.resize(ene_out_no);
          for(int k=0; k<ene_out_no; k++)
          {
            dummy_vec[k] = 0.0;
          }
          for(int p=1; p<pl_no_ori+1; p++)
          {
            ddxs_vec[i][b].push_back(dummy_vec);
          }

          if( mod_flg == 0 )
          {
            mod_flg = pl_no_ori + 1;
          }

          if( e_out_ori < 0 )
          {
            e_out_ori = ene_out_no;
          }
          else if( e_out_ori != ene_out_no )
          {
          }
        }
        else
        {
          string class_name = "MGPhotonProduction";
          string func_name  = "add_pl_data";

          ostringstream oss01, oss02, oss03;
          oss01 << mt_list[mt_pos];
          oss02 << pl_no_ori;
          oss03 << pl_size - 1;
          string str_data01 = "MT (reaction type)                                 : " + oss01.str();
          string str_data02 = "Number of Legendre order (from input)              : " + oss02.str();
          string str_data03 = "Number of Legendre order (from calculation result) : " + oss03.str();

          vector<string> err_com;
          err_com.push_back(str_data01);
          err_com.push_back(str_data02);
          err_com.push_back(str_data03);
          err_com.push_back("The number of Legendre order from input is different to that of");
          err_com.push_back("the calculation result (photon_dd_xs).");
          err_com.push_back("Please modify this program if you want to calculate inputted Legendre order.");

          err_obj.output_caution(class_name, func_name, err_com);
        }
      }
    }
  }

  if( mod_flg > 0 )
  {
    pl_no = mod_flg;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Integer MGPhotonProduction::get_za_val()
{
  return za_val;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Real MGPhotonProduction::get_awr_val()
{
  return awr_val;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

