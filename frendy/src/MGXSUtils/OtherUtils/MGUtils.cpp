#include "MGXSUtils/OtherUtils/MGUtils.hpp"

using namespace frendy;

// ***** MGUtils ***** //
//constructor
MGUtils::MGUtils(void)
{
  clear();
}

//destructor
MGUtils::~MGUtils(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MGUtils::clear()
{
  mce_bin_no =  2;
//  mce_bin_no =  1; //For unit base interpolation
  mce_pos_p  = -1;
  mce_pos_m  = -1;
  mce_int    = -1;

  if( mce_bin_no > 2 )
  {
    cout << "*** MCE bin no for photon production generation : " << mce_bin_no << " ***" << endl;
  }

  awr_val    = 0.0;
  awr_coef   = 0.0;

  xs_fine_ene.clear();
  xs_fine.clear();

  xs_mg.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<vector<vector<Real> > > MGUtils::calc_angular_flux(vector<Real>& flux_tot_e, vector<Real>& flux_tot,
                                                 vector<Real>& sig_tot_e,  vector<Real>& sig_tot,
                                                 vector<Real>& sig_bg, int pl_no)
{
  if( pl_no < 0 )
  {
    string class_name = "MGUtils";
    string func_name  = "calc_angular_flux";

    ostringstream oss;
    oss << pl_no;
    string str_data = "Legendre order number : " + oss.str();

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("Legendre order number must be larger than or equal to 0.");
    err_com.push_back("Please check the Legendre order.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  vector<vector<vector<Real> > > flux_ang;
  int ene_no = static_cast<int>(flux_tot.size());
  int bg_no  = static_cast<int>(sig_bg.size());

  flux_ang.resize(ene_no);
  for(int i=0; i<ene_no; i++)
  {
    flux_ang[i].resize(bg_no);
    for(int b=0; b<bg_no; b++)
    {
      flux_ang[i][b].resize(pl_no+1);
      flux_ang[i][b][0] = flux_tot[i];
    }
  }

  if( pl_no == 0 )
  {
    return flux_ang;
  }

  Real sig_val = 0.0;
  for(int i=0; i<ene_no; i++)
  {
    ti_obj.interpolation_1d_in_range(int_lin_lin, flux_tot_e[i], sig_val, sig_tot_e, sig_tot);

    for(int b=0; b<bg_no; b++)
    {
      Real inv_val = 1.0 / (sig_val + sig_bg[b]);
      for(int p=1; p<pl_no+1; p++)
      {
        flux_ang[i][b][p] = flux_ang[i][b][p-1] * inv_val;
      }
    }
  }

  return flux_ang;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<vector<vector<Real> > > MGUtils::calc_angular_flux(vector<vector<Real> >& flux,
                                                          vector<vector<Real> >& sig_t_sig_bg,
                                                          int pl_no)
{
  if( pl_no < 0 )
  {
    string class_name = "MGUtils";
    string func_name  = "calc_angular_flux";

    ostringstream oss;
    oss << pl_no;
    string str_data = "Legendre order number : " + oss.str();

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("Legendre order number must be larger than or equal to 0.");
    err_com.push_back("Please check the Legendre order.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  vector<vector<vector<Real> > > flux_ang;
  int bg_no  = static_cast<int>(flux.size());
  if( bg_no == 0 )
  {
    return flux_ang;
  }
  else if( bg_no != static_cast<int>(sig_t_sig_bg.size()) )
  {
    string class_name = "MGUtils";
    string func_name  = "calc_angular_flux";

    ostringstream oss01, oss02;
    oss01 << bg_no;
    oss02 << static_cast<int>(sig_t_sig_bg.size());
    string str_data01 = "Back ground cross section number from flux         : " + oss01.str();
    string str_data02 = "Back ground cross section number from sig_t_sig_bg : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("Back ground cross section number must be identical.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }


  int ene_no = static_cast<int>(flux[0].size());
  if( ene_no != static_cast<int>(sig_t_sig_bg[0].size()) )
  {
    string class_name = "MGUtils";
    string func_name  = "calc_angular_flux";

    ostringstream oss01, oss02;
    oss01 << ene_no;
    oss02 << static_cast<int>(sig_t_sig_bg[0].size());
    string str_data01 = "Ein number from flux         : " + oss01.str();
    string str_data02 = "Ein number from sig_t_sig_bg : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("Ein number must be identical.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  flux_ang.resize(ene_no);
  for(int i=0; i<ene_no; i++)
  {
    flux_ang[i].resize(bg_no);
    for(int b=0; b<bg_no; b++)
    {
      Real flux_val = flux[b][i];
      Real inv_val  = 1.0 / sig_t_sig_bg[b][i];

      flux_ang[i][b].resize(pl_no+1);
      flux_ang[i][b][0] = flux_val;
      for(int p=1; p<pl_no+1; p++)
      {
        flux_ang[i][b][p] = flux_ang[i][b][p-1] * inv_val;
      }
    }
  }

  return flux_ang;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MGUtils::calc_mg_xs(vector<Real>& flux_e, vector<Real>& flux,
                         vector<Real>& sig_e,  vector<Real>& sig,
                         vector<Real>& mg_structure, vector<Real>& sig_mg,
                         vector<Real>& sig_fine_ene, vector<Real>& sig_fine)
{
  calc_mg_xs(flux_e, flux, sig_e, sig, mg_structure, sig_mg);

  sig_fine_ene = xs_fine_ene;
  sig_fine     = xs_fine;

  if( static_cast<int>(sig_fine.size()) > 0 && static_cast<int>(flux_e.size()) > 0 )
  {
    TabAdjuster ta_obj;
    ta_obj.modify_x_grid_by_lin_lin(flux_e, sig_fine_ene, sig_fine);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MGUtils::calc_mg_xs(vector<Real>& flux_e, vector<Real>& flux,
                         vector<Real>& sig_e,  vector<Real>& sig,
                         vector<Real>& mg_structure, vector<Real>& sig_mg)
{
  int flux_no = static_cast<int>(flux_e.size());
  int sig_no  = static_cast<int>(sig.size());
  int mg_no   = static_cast<int>(mg_structure.size()) - 1;
  if( flux_no == 0 || sig_no == 0 || mg_no <= 0 )
  {
    return;
  }


  vector<Real> sig_e_mod = sig_e;
  if( sig_no != static_cast<int>(sig_e.size()) )
  {
    sig_e_mod.resize(sig_no);

    int ele_no = static_cast<int>(sig_e.size()) - sig_no;
    for(int i=0; i<sig_no; i++)
    {
      sig_e_mod[i] = sig_e[ele_no+i];
    }
  }


  vector<Real> flux_e_mod, flux_mod;
  int  i_max      = static_cast<int>(flux_e.size());
  int  flux_e_sta = i_max-1;
  Real sig_e_sta  = sig_e_mod[0] * (1.0 - min_sig_dif);
  for(int i=0; i<i_max; i++)
  {
    if( flux_e[i] > sig_e_sta )
    {
      if( i > 0 )
      {
        i--;
      }
      flux_e_sta = i;
      break;
    }
  }
  flux_e_mod.resize(i_max - flux_e_sta);
  for(int i=flux_e_sta; i<i_max; i++)
  {
    flux_e_mod[i - flux_e_sta] = flux_e[i];
  }

  vector<Real> add_data = sig_e_mod;
  ta_obj.add_grid_data(add_data, mg_structure, flux_e[i_max-1]);
  ta_obj.add_grid_data(flux_e_mod, add_data, flux_e[i_max-1]);
  add_data.clear();

  i_max = static_cast<int>(flux_e_mod.size());
  flux_mod.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    ti_obj.interpolation_1d(int_lin_lin, flux_e_mod[i], flux_mod[i], flux_e, flux);
  }

  calc_mg_xs_without_energy_grid_modification
     (flux_e_mod, flux_mod, flux_e, flux, sig_e_mod, sig, mg_structure, sig_mg);
  flux_e_mod.clear();
  flux_mod.clear();
  sig_e_mod.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MGUtils::calc_mg_xs_without_energy_grid_modification
                        (vector<Real>& flux_e,     vector<Real>& flux,
                         vector<Real>& sig_e,  vector<Real>& sig,
                         vector<Real>& mg_structure, vector<Real>& sig_mg)
{
  vector<Real> flux_all_e = flux_e;
  vector<Real> flux_all   = flux;

  calc_mg_xs_without_energy_grid_modification(flux_e, flux, flux_all_e, flux_all,
                                             sig_e, sig, mg_structure, sig_mg);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MGUtils::calc_mg_xs_without_energy_grid_modification
                        (vector<Real>& flux_e,     vector<Real>& flux,
                         vector<Real>& flux_all_e, vector<Real>& flux_all,
                         vector<Real>& sig_e,  vector<Real>& sig,
                         vector<Real>& mg_structure, vector<Real>& sig_mg)
{
  sig_mg.clear();
  xs_fine_ene.clear();
  xs_fine.clear();

  int flux_no = static_cast<int>(flux_e.size());
  int sig_no  = static_cast<int>(sig.size());
  int mg_no   = static_cast<int>(mg_structure.size()) - 1;
  if( flux_no == 0 || sig_no == 0 || mg_no <= 0 )
  {
    return;
  }

  if( flux_e[0] > mg_structure[0] * (1.0 + min_ene_dif) )
  {
    if( static_cast<int>(flux_all_e.size()) == 0 ||
        flux_all_e[0] > mg_structure[0] * (1.0 + min_ene_dif) )
    {
      string class_name = "MGUtils";
      string func_name  = "calc_mg_xs_without_energy_grid_modification";

      ostringstream oss01, oss02, oss03;
      oss01 << mg_structure[0];
      oss02 << flux_e[0];
      string str_data01 = "Minimum energy of multi-group structure : " + oss01.str();
      string str_data02 = "Minimum energy of flux                  : " + oss02.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back("The minimum energy of multi-group structure is larger than that of flux.");
      err_com.push_back("The calculation of the group-wised cross section may not be incorrect.");
      err_com.push_back("Please check the flux data.");

      err_obj.output_caution(class_name, func_name, err_com);
    }
  }

  vector<Real> sig_e_mod = sig_e;
  if( sig_no != static_cast<int>(sig_e.size()) )
  {
    sig_e_mod.resize(sig_no);

    int ele_no = static_cast<int>(sig_e.size()) - sig_no;
    for(int i=0; i<sig_no; i++)
    {
      sig_e_mod[i] = sig_e[ele_no+i];
    }  
  }

  sig_mg.resize(mg_no);
  for(int i=0; i<mg_no; i++)
  {
    sig_mg[i] = 0.0;
  }

  xs_fine_ene.resize(flux_no);
  xs_fine.resize(flux_no);
  for(int i=0; i<flux_no; i++)
  {
    xs_fine_ene[i] = 0.0;
    xs_fine[i]     = 0.0;
  }

  int i_sta = 0;
  int j_sta = flux_no-1;
  Real sig_e_sta = sig_e_mod[0] * (1.0 - min_sig_dif);
  for(int i=0; i<mg_no; i++)
  {
    if( mg_structure[i+1] > sig_e_sta )
    {
      i_sta = i;
      break;
    }
  }

  for(int i=1; i<flux_no; i++)
  {
    if( flux_e[i] > sig_e_sta )
    {
      j_sta = i;
      break;
    }
  }

  //Integration of flux(E) where the cross section is zero.
  vector<Real> flux_sum_zero_xs;
  flux_sum_zero_xs.resize(mg_no);
  for(int i=0; i<mg_no; i++)
  {
    flux_sum_zero_xs[i] = 0.0;
  }
  if( j_sta > 1 ) //For threshold reaction
  {
    int j_max = static_cast<int>(flux_all.size());
    int j     = 1;
    Real flux_e_max = flux_e[j_sta];
    Real flux_e_pre = flux_all_e[j-1];
    Real flux_e_cur = flux_all_e[j];
    Real flux_pre   = flux_all[j-1];
    Real flux_cur   = flux_all[j];
    for(int i=0; i<mg_no; i++)
    {
      flux_sum_zero_xs[i] = 0.0;
      while( flux_e_cur < mg_structure[i+1] * (1.0 + min_ene_dif) && 
             flux_e_cur < flux_e_max && j < j_max )
      {
        flux_sum_zero_xs[i] += 0.5 * (flux_e_cur - flux_e_pre) * (flux_cur + flux_pre);

        j++;
        if( j < j_max )
        {
          flux_e_pre = flux_e_cur;
          flux_e_cur = flux_all_e[j];
          flux_pre   = flux_cur;
          flux_cur   = flux_all[j];
        }
      }
    }
  }

  int  j=j_sta;
  int  k=1;
  Real flux_e_pre = flux_e[j-1];
  Real flux_e_cur = flux_e[j];
  Real flux_pre   = flux[j-1];
  Real flux_cur   = flux[j];

  Real sig_e_pre = sig_e_mod[0];
  Real sig_e_cur = sig_e_mod[1];
  Real sig_pre   = sig[0];
  Real sig_cur   = sig[1];
  Real slope     = 0.0;
  Real b_val     = 0.0;
  ti_obj.get_interpolation_linear_linear_coef(slope, b_val, sig_e_pre, sig_pre,
                                                            sig_e_cur, sig_cur);

  Real sig_flux_pre = slope*flux_e_pre + b_val;
  Real sig_flux_cur = slope*flux_e_cur + b_val;
  if( sig_flux_cur < min_value )
  {
    sig_flux_cur = 0.0;
  }

  if( j > 1 )
  {
    sig_flux_pre = 0.0;
  }
  xs_fine[j-1]      = sig_flux_pre;
  xs_fine[j]        = sig_flux_cur;
  xs_fine_ene[j-1]  = flux_e_pre;
  xs_fine_ene[j]    = flux_e_cur;

  for(int i=i_sta; i<mg_no; i++)
  {
    Real flux_sum = 0.0;
    Real rr_sum   = 0.0; //rr: reaction rate
    while( flux_e_cur < mg_structure[i+1] * (1.0 + min_ene_dif) && j < flux_no)
    {
      while( flux_e[j] > sig_e_mod[k] * (1.0 + min_ene_dif) && k < sig_no-1)
      {
        k++;

        sig_e_pre = sig_e_cur;
        sig_pre   = sig_cur;
        sig_e_cur = sig_e_mod[k];
        sig_cur   = sig[k];
        ti_obj.get_interpolation_linear_linear_coef(slope, b_val, sig_e_pre, sig_pre,
                                                                  sig_e_cur, sig_cur);
      }

      Real coef     = 0.5 * (flux_e_cur - flux_e_pre);
      sig_flux_cur  = slope*flux_e_cur + b_val;
      if( sig_flux_cur < min_value )
      {
        sig_flux_cur = 0.0;
      }
      flux_sum     += coef * (flux_cur              + flux_pre);
      rr_sum       += coef * (flux_cur*sig_flux_cur + flux_pre*sig_flux_pre);

      xs_fine_ene[j] = flux_e_cur;
      xs_fine[j]     = sig_flux_cur;

      j++;
      if( j < flux_no )
      {
        flux_e_pre     = flux_e_cur;
        flux_e_cur     = flux_e[j];
        flux_pre       = flux_cur;
        flux_cur       = flux[j];
        sig_flux_pre   = sig_flux_cur;
      }
    }
    flux_sum += flux_sum_zero_xs[i];

    sig_mg[i] = 0.0;
    if( fabs(flux_sum) > min_value )
    {
      sig_mg[i] = rr_sum / flux_sum;
    }
  }
  sig_e_mod.clear();

  xs_mg   = sig_mg;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MGUtils::calc_mg_xs_with_1e(vector<Real>& sig_e,  vector<Real>& sig,
                                 vector<Real>& mg_structure, vector<Real>& sig_mg)
{
  vector<Real> flux_e, flux;
  flux_e = sig_e;
  ta_obj.add_grid_data(flux_e, mg_structure);

  int ene_no = static_cast<int>(flux_e.size());
  flux.resize(ene_no);

  for(int i=0; i<ene_no; i++)
  {
    flux[i] = 1.0 / flux_e[i];
  }

  calc_mg_xs_without_energy_grid_modification(flux_e, flux, sig_e, sig, mg_structure, sig_mg);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MGUtils::calc_mg_xs_with_const(vector<Real>& sig_e,  vector<Real>& sig,
                                    vector<Real>& mg_structure, vector<Real>& sig_mg)
{
  vector<Real> flux_e, flux;
  flux_e = sig_e;
  ta_obj.add_grid_data(flux_e, mg_structure);

  int ene_no = static_cast<int>(flux_e.size());
  flux.resize(ene_no);

  for(int i=0; i<ene_no; i++)
  {
    flux[i] = 1.0;
  }

  calc_mg_xs_without_energy_grid_modification(flux_e, flux, sig_e, sig, mg_structure, sig_mg);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MGUtils::calc_energy_distribution
               (Real e_in, vector<Real>& e_out_vec_cont_new,  vector<Real>& e_out_pdf_cont_new,
                int& e_out_disc_flg, vector<Real>& e_out_vec_disc_new, vector<Real>& e_out_pdf_disc_new,
                vector<Integer>& e_in_range, vector<Integer>& e_in_int, vector<Real>& e_in_vec,
                vector<Integer>& e_out_int,
                vector<vector<Real> >& e_out_vec_cont,  vector<vector<Real> >& e_out_pdf_cont,
                vector<vector<Real> >& e_out_vec_disc,  vector<vector<Real> >& e_out_pdf_disc)
{
  LinearizeTabData lin_obj;

  int i_max = static_cast<int>(e_out_vec_cont.size());
  for(int i=0; i<i_max; i++)
  {
    if( e_out_int[i] != int_lin_lin )
    {
      if( static_cast<int>(e_out_vec_cont[i].size()) > 0 &&
          static_cast<int>(e_out_pdf_cont[i].size()) > 0 )
      {
        lin_obj.linearize_data(e_out_int[i], e_out_vec_cont[i], e_out_pdf_cont[i]);
      }
      e_out_int[i] = int_lin_lin;
    }
  }

  calc_energy_distribution_without_linearization
    (e_in, e_out_vec_cont_new, e_out_pdf_cont_new,
     e_out_disc_flg, e_out_vec_disc_new, e_out_pdf_disc_new,
     e_in_range, e_in_int, e_in_vec, e_out_vec_cont, e_out_pdf_cont, e_out_vec_disc, e_out_pdf_disc);
}


////////////////////////////////////////////////////////////////////////////////////////////////////

void MGUtils::calc_energy_distribution_without_linearization
               (Real e_in, vector<Real>& e_out_vec_cont_new,  vector<Real>& e_out_pdf_cont_new,
                int& e_out_disc_flg,
                vector<Real>& e_out_vec_disc_new, vector<Real>& e_out_pdf_disc_new,
                vector<Integer>& e_in_range, vector<Integer>& e_in_int, vector<Real>& e_in_vec,
                vector<vector<Real> >& e_out_vec_cont,  vector<vector<Real> >& e_out_pdf_cont,
                vector<vector<Real> >& e_out_vec_disc, vector<vector<Real> >& e_out_pdf_disc)
{
  //This subroutine approximated that the interpolation law of e_out_vec_cont and e_out_pdf_cont is linear-linear.

  e_out_vec_cont_new.clear();
  e_out_pdf_cont_new.clear();
  e_out_vec_disc_new.clear();
  e_out_pdf_disc_new.clear();

  int i_max = static_cast<int>(e_in_vec.size());
  if( i_max == 0 )
  {
    return;
  }
  else if( i_max == 1 )
  {
    if( static_cast<int>(e_out_pdf_cont.size()) > 0 )
    {
      e_out_vec_cont_new = e_out_vec_cont[0];
      e_out_pdf_cont_new = e_out_pdf_cont[0];
    }

    if( static_cast<int>(e_out_vec_disc.size()) > 0 )
    {
      e_out_vec_disc_new = e_out_vec_disc[0];
      e_out_pdf_disc_new = e_out_pdf_disc[0];
    }
    return;
  }

  int i_m = mce_pos_m;
  int i_p = mce_pos_p;
  if( mce_pos_m >= i_max || mce_pos_p >= i_max )
  {
    mce_pos_m = -1;
    mce_pos_p = -1;
    ti_obj.search_neighbor_value(e_in, e_in_vec, i_m, i_p);
  }
  else if( i_m >= 0 && i_p > i_m )
  {
    if( e_in_vec[i_m] <= e_in && e_in <= e_in_vec[i_p] )
    {
      //skip search_neighbor_value
    }
    else
    {
      ti_obj.search_neighbor_value(e_in, e_in_vec, i_m, i_p);
    }
  }
  else
  {
    ti_obj.search_neighbor_value(e_in, e_in_vec, i_m, i_p);
  }

  e_out_disc_flg = 0;
  if( i_m != mce_pos_m || i_p != mce_pos_p )
  {
    mce_pos_m = i_m;
    mce_pos_p = i_p;
    mce_int   = ti_obj.search_interpolation_range(e_in_range, e_in_int, i_p);
    if( static_cast<int>(e_out_pdf_cont.size()) > i_p ) 
    {
      if( static_cast<int>(e_out_pdf_cont[i_p].size()) > 0 ||
          static_cast<int>(e_out_pdf_cont[i_m].size()) > 0 ) 
      {
        //For continuous photon
        two_d_int_obj.mce_interpolation(e_in, mce_bin_no, mce_int,
                                        e_out_vec_cont[i_m], e_out_pdf_cont[i_m], e_in_vec[i_m],
                                        e_out_vec_cont[i_p], e_out_pdf_cont[i_p], e_in_vec[i_p],
                                        e_out_vec_cont_new,  e_out_pdf_cont_new);
      }
    }

    //For discrete photon
    e_out_disc_flg = 1;
  }
  else //if( i_m == mce_pos_m && i_p == mce_pos_p )
  {
    if( static_cast<int>(e_out_pdf_cont.size()) > i_p ) 
    {
      if( static_cast<int>(e_out_pdf_cont[i_p].size()) > 0 ||
          static_cast<int>(e_out_pdf_cont[i_m].size()) > 0 ) 
      {
        //For continuous photon
        two_d_int_obj.mce_interpolation_without_set_array
                        (e_in, mce_int, e_in_vec[i_m], e_in_vec[i_p], e_out_vec_cont_new, e_out_pdf_cont_new);
      }
    }
  }

  if( static_cast<int>(e_out_pdf_disc.size()) > mce_pos_p )
  {
    //For discrete photon
    vector<Real> e_out_vec_disc_pre = e_out_vec_disc[mce_pos_m];
    vector<Real> e_out_pdf_disc_pre = e_out_pdf_disc[mce_pos_m];
    vector<Real> e_out_vec_disc_cur = e_out_vec_disc[mce_pos_p];
    vector<Real> e_out_pdf_disc_cur = e_out_pdf_disc[mce_pos_p];

    if( mce_pos_m == 0 && e_in < e_in_vec[0] )
    {
      e_out_vec_disc_cur.clear();
      e_out_pdf_disc_cur.clear();
    }
    if( mce_pos_p == i_max-1 && e_in > e_in_vec[i_max-1] )
    {
      e_out_vec_disc_pre.clear();
      e_out_pdf_disc_pre.clear();
    }

    int pre_max = static_cast<int>(e_out_vec_disc_pre.size());
    int cur_max = static_cast<int>(e_out_vec_disc_cur.size());
        i_max   = cur_max + pre_max;
    e_out_vec_disc_new.resize(i_max);
    e_out_pdf_disc_new.resize(i_max);

    Integer int_disc = mce_int%10;
    Real    y_tmp    = min_value;
    for(int i=0; i<pre_max; i++)
    {
      e_out_vec_disc_new[i] = e_out_vec_disc_pre[i];
      ti_obj.interpolation_1d(int_disc, e_in, e_out_pdf_disc_new[i],
                              e_in_vec[mce_pos_m], e_out_pdf_disc_pre[i], 
                              e_in_vec[mce_pos_p], y_tmp);
      if( e_out_pdf_disc_new[i] < min_value )
      {
        e_out_pdf_disc_new[i] = 0.0;
      }
    }
    int ele_no = 0;
    for(int i=pre_max; i<i_max; i++)
    {
      e_out_vec_disc_new[i] = e_out_vec_disc_cur[ele_no];
      ti_obj.interpolation_1d(int_disc, e_in, e_out_pdf_disc_new[i],
                              e_in_vec[mce_pos_m], y_tmp,
                              e_in_vec[mce_pos_p], e_out_pdf_disc_cur[ele_no]);
      if( e_out_pdf_disc_new[i] < min_value )
      {
        e_out_pdf_disc_new[i] = 0.0;
      }
      ele_no++;
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//dd_xs : double differntial cross section
vector<vector<vector<vector<Real> > > > MGUtils::calc_mg_dd_xs
                        (vector<vector<vector<Real> > >& dd_xs_coef,
                         vector<Real>& flux_e, vector<vector<vector<Real> > >& flux,
                         vector<Real>& mg_e_in, vector<Real>& mg_e_out,
                         vector<Integer>& e_in_range, vector<Integer>& e_in_int, vector<Real>& e_in_vec,
                         vector<Integer>& e_out_int,
                         vector<vector<Real> >& e_out_vec_cont,  vector<vector<Real> >& e_out_pdf_cont,
                         vector<vector<Real> >& e_out_vec_disc,  vector<vector<Real> >& e_out_pdf_disc)
{
  int                                     e_sta_pos, flux_e_no, e_in_no, e_out_no, bg_no, pl_no;
  vector<vector<vector<Real> > >          flux_tot;
  vector<vector<vector<vector<Real> > > > xs_dd;
  vector<vector<Real> >                   flux_in_pre, flux_in_cur, flux_coef;
  initialize_mg_dd_xs(dd_xs_coef, e_sta_pos, flux_e, flux, mg_e_in, mg_e_out,
                      flux_e_no, e_in_no, e_out_no, bg_no, pl_no, xs_dd, flux_tot,
                      flux_in_pre, flux_in_cur, flux_coef);

  if( static_cast<int>(xs_dd.size()) == 0 )
  {
    return xs_dd;
  }

  int j = e_sta_pos;
  Real flux_e_in_pre, flux_e_in_cur, flux_e_width;
  get_flux_data(j, bg_no, pl_no, flux_e, flux,
                flux_e_in_pre, flux_e_in_cur, flux_e_width,
                flux_in_pre, flux_in_cur, flux_coef);

  vector<vector<Real> > dd_xs_coef_cur = dd_xs_coef[j];

  vector<Real> e_out_vec_cont_new, e_out_pdf_cont_new;
  int          e_out_disc_flg, e_out_disc_no_pre;
  vector<int>  e_out_pos_disc;
  vector<Real> e_out_vec_disc_new, e_out_pdf_disc_new;

  e_out_disc_no_pre = 0;
  mce_pos_m         = -1;
  mce_pos_p         = -1;
  for(int i=0; i<e_in_no; i++)
  {
    while( flux_e_in_cur < mg_e_in[i+1] && j < flux_e_no )
    {
      calc_energy_distribution(flux_e_in_cur, e_out_vec_cont_new, e_out_pdf_cont_new,
                               e_out_disc_flg, e_out_vec_disc_new, e_out_pdf_disc_new,
                               e_in_range, e_in_int, e_in_vec, e_out_int, 
                               e_out_vec_cont, e_out_pdf_cont, e_out_vec_disc, e_out_pdf_disc);

      vector<Real> xs_e_out;
      xs_e_out.clear();
      if( static_cast<int>(e_out_vec_cont_new.size()) > 0 )
      {
        //For continuous
        xs_e_out = integ_obj.integrate_using_specified_grid_with_lin_lin
                               (mg_e_out, e_out_vec_cont_new, e_out_pdf_cont_new);
      }

      //Add continuous photon data
      for(int b=0; b<bg_no; b++)
      {
        for(int p=0; p<pl_no; p++)
        {
          for(int k=0; k<static_cast<int>(xs_e_out.size()); k++)
          {
            if( xs_e_out[k] > min_value )
            {
              xs_dd[i][b][p][k] += xs_e_out[k] * flux_coef[b][p] * dd_xs_coef_cur[b][p];
            }
          }
          flux_tot[i][b][p] += flux_coef[b][p];
        }
      }

      //For discrete
      int disc_no = static_cast<int>(e_out_vec_disc_new.size());

      //Set output energy grid 
      if( e_out_disc_flg == 1 || e_out_disc_no_pre != disc_no )
      {
        e_out_disc_no_pre = disc_no;
        e_out_pos_disc.resize(disc_no);
        for(int k=0; k<disc_no; k++)
        {
          int pos_disc_m, pos_disc_p;
          ti_obj.search_neighbor_value(e_out_vec_disc_new[k], mg_e_out, pos_disc_m, pos_disc_p);

          e_out_pos_disc[k] = pos_disc_p;
          if( e_out_pos_disc[k] == e_out_no )
          {
            e_out_pos_disc[k] = pos_disc_m;
          }
          else if( mg_e_out[e_out_pos_disc[k]] > e_out_vec_disc_new[k] )
          {
            e_out_pos_disc[k] = pos_disc_m;
          }
        }
      }

      //Add discrete photon data
      for(int k=0; k<disc_no; k++)
      {
        int  e_out_pos = e_out_pos_disc[k];
        Real coef_disc = e_out_pdf_disc_new[k];
        if( coef_disc > min_value )
        {
          for(int b=0; b<bg_no; b++)
          {
            for(int p=0; p<pl_no; p++)
            {
              xs_dd[i][b][p][e_out_pos] += coef_disc * flux_coef[b][p] * dd_xs_coef_cur[b][p];
            }
          }
        }
      }

      //Common process (for continuous and discrete)
      j++;
      if( j < flux_e_no )
      {
        get_flux_data(j, bg_no, pl_no, flux_e, flux,
                      flux_e_in_pre, flux_e_in_cur, flux_e_width,
                      flux_in_pre, flux_in_cur, flux_coef);
        dd_xs_coef_cur = dd_xs_coef[j];
      }
    }
  }

  modify_dd_xs(xs_dd, flux_tot);

  return xs_dd;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<vector<vector<vector<Real> > > > MGUtils::calc_mg_dd_xs_with_discrete_ene
                        (vector<vector<vector<Real> > >& dd_xs_coef,
                         vector<Real>& flux_e, vector<vector<vector<Real> > >& flux,
                         vector<Real>& mg_e_in, vector<Real>& mg_e_out,
                         vector<Integer>& multi_range, vector<Integer>& multi_int,
                         vector<Real>&    multi_ene,   vector<Real>&    multi_data,
                         Integer lp, Real& binding_ene)
{
  int                                     e_sta_pos, flux_e_no, e_in_no, e_out_no, bg_no, pl_no;
  vector<vector<vector<Real> > >          flux_tot;
  vector<vector<vector<vector<Real> > > > xs_dd;
  vector<vector<Real> >                   flux_in_pre, flux_in_cur, flux_coef;
  initialize_mg_dd_xs(dd_xs_coef, e_sta_pos, flux_e, flux, mg_e_in, mg_e_out,
                      flux_e_no, e_in_no, e_out_no, bg_no, pl_no, xs_dd, flux_tot,
                      flux_in_pre, flux_in_cur, flux_coef);

  if( static_cast<int>(xs_dd.size()) == 0 )
  {
    return xs_dd;
  }

  int j = e_sta_pos;
  Real flux_e_in_pre, flux_e_in_cur, flux_e_width;
  get_flux_data(j, bg_no, pl_no, flux_e, flux,
                flux_e_in_pre, flux_e_in_cur, flux_e_width,
                flux_in_pre, flux_in_cur, flux_coef);

  vector<vector<Real> > dd_xs_coef_cur = dd_xs_coef[j];

  Real coef_multi       = 0.0;
  int multi_int_pos     = 0;
  int multi_int_pos_max = static_cast<int>(multi_int.size());
  int multi_xs_pos      = 1;
  int multi_xs_pos_max  = static_cast<int>(multi_ene.size());

  for(int i=0; i<e_in_no; i++)
  {
    while( flux_e_in_cur < mg_e_in[i+1] && j < flux_e_no )
    {
      //Calculation of multiplicity
      while( multi_ene[multi_xs_pos] < flux_e_in_cur )
      {
        multi_xs_pos++;

        if( multi_xs_pos >= multi_xs_pos_max )
        {
          multi_xs_pos = multi_xs_pos_max - 1;
          break;
        }
      }

      while( multi_range[multi_int_pos] <= multi_xs_pos )
      {
        multi_int_pos++;

        if( multi_int_pos >= multi_int_pos_max )
        {
          multi_int_pos = multi_int_pos_max - 1;
          break;
        }
      }

      ti_obj.interpolation_1d(multi_int[multi_int_pos], flux_e_in_cur, coef_multi,
                              multi_ene[multi_xs_pos-1], multi_data[multi_xs_pos-1],
                              multi_ene[multi_xs_pos],   multi_data[multi_xs_pos]);
      if( coef_multi < min_value )
      {
        coef_multi = 0.0;
      }

      Real photon_bind_ene = get_discrete_photon_energy(lp, binding_ene, flux_e_in_cur);

      int pos_m, pos_p, pos_cal;
      ti_obj.search_neighbor_value(photon_bind_ene, mg_e_out, pos_m, pos_p);

      pos_cal = pos_p;
      if( pos_cal == e_out_no )
      {
        pos_cal = pos_m;
      }
      else if( mg_e_out[pos_cal] > photon_bind_ene )
      {
        pos_cal = pos_m;
      }

      for(int b=0; b<bg_no; b++)
      {
        for(int p=0; p<pl_no; p++)
        {
          xs_dd[i][b][p][pos_cal] += coef_multi * flux_coef[b][p] * dd_xs_coef_cur[b][p];
          flux_tot[i][b][p] += flux_coef[b][p];
        }
      }

      j++;
      if( j < flux_e_no )
      {
        get_flux_data(j, bg_no, pl_no, flux_e, flux,
                      flux_e_in_pre, flux_e_in_cur, flux_e_width,
                      flux_in_pre, flux_in_cur, flux_coef);
        dd_xs_coef_cur = dd_xs_coef[j];
      }
    }
  }

  modify_dd_xs(xs_dd, flux_tot);

  return xs_dd;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MGUtils::initialize_mg_dd_xs
                (vector<vector<vector<Real> > >& dd_xs_coef, int& e_sta_pos,
                 vector<Real>& flux_e, vector<vector<vector<Real> > >& flux,
                 vector<Real>& mg_e_in, vector<Real>& mg_e_out,
                 int& flux_e_no, int& e_in_no, int& e_out_no, int& bg_no, int& pl_no,
                 vector<vector<vector<vector<Real> > > >& xs_dd,
                 vector<vector<vector<Real> > >& flux_tot,
                 vector<vector<Real> >& flux_in_pre, vector<vector<Real> >& flux_in_cur,
                 vector<vector<Real> >& flux_coef)
{
  clr_obj.clear_vec_array4_real(xs_dd);
  clr_obj.clear_vec_array3_real(flux_tot);

  clr_obj.clear_vec_array2_real(flux_in_pre);
  clr_obj.clear_vec_array2_real(flux_in_cur);
  clr_obj.clear_vec_array2_real(flux_coef);

  flux_e_no  = static_cast<int>(flux_e.size());
  if( flux_e_no == 0 )
  {
    return;
  }

  e_in_no    = static_cast<int>(mg_e_in.size())  - 1;
  e_out_no   = static_cast<int>(mg_e_out.size()) - 1;
  bg_no      = static_cast<int>(flux[0].size());
  pl_no      = static_cast<int>(flux[0][0].size());
  if( e_in_no <= 0 || e_out_no <= 0 || bg_no <= 0 || pl_no <= 0 )
  {
    return;
  }

  flux_in_pre.resize(bg_no);
  flux_in_cur.resize(bg_no);
  flux_coef.resize(bg_no);
  for(int b=0; b<bg_no; b++)
  {
    flux_in_pre[b].resize(pl_no);
    flux_in_cur[b].resize(pl_no);
    flux_coef[b].resize(pl_no);
  }

  if( static_cast<int>(dd_xs_coef.size()) != flux_e_no )
  {
    string class_name = "MGUtils";
    string func_name  = "initialize_mg_dd_xs";

    ostringstream oss01, oss02;
    oss01 << flux_e_no;
    oss02 << static_cast<int>(dd_xs_coef.size());
    string str_data01 = "Energy grid number of flux       : " + oss01.str();
    string str_data02 = "Energy grid number of dd_xs_coef : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("The energy grid number of dd_xs_coef must be equal to that of flux.");
    err_com.push_back("Please check the flux and dd_xs_coef data.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  e_sta_pos = -1;
  for(int i=1; i<flux_e_no; i++)
  {
    for(int j=0; j<bg_no; j++)
    {
      for(int k=0; k<pl_no; k++)
      {
        if( fabs(dd_xs_coef[i][j][k]) > min_value )
        {
          e_sta_pos = i;
          break;
        }
      }
      if( e_sta_pos >= 0 )
      {
        break;
      }
    }
    if( e_sta_pos >= 0 )
    {
      break;
    }
  }
  if( e_sta_pos < 0 )
  {
    e_sta_pos = flux_e_no-1;
  }

  flux_tot.resize(e_in_no);
  xs_dd.resize(e_in_no);
  for(int i=0; i<e_in_no; i++)
  {
    flux_tot[i].resize(bg_no);
    xs_dd[i].resize(bg_no);
    for(int j=0; j<bg_no; j++)
    {
      flux_tot[i][j].resize(pl_no);
      xs_dd[i][j].resize(pl_no);
      for(int k=0; k<pl_no; k++)
      {
        flux_tot[i][j][k] = 0.0;

        xs_dd[i][j][k].resize(e_out_no);
        for(int l=0; l<e_out_no; l++)
        {
          xs_dd[i][j][k][l] = 0.0;
        }
      }
    }
  }

  //Integration of flux(E) where the cross section is zero.
  if( e_sta_pos > 1 ) //For threshold reaction
  {
    int j_max = static_cast<int>(flux_e.size());
    int j     = 1;
    Real                  flux_e_max = flux_e[e_sta_pos];
    Real                  flux_e_pre = flux_e[j-1];
    Real                  flux_e_cur = flux_e[j];
    vector<vector<Real> > flux_pre   = flux[j-1];
    vector<vector<Real> > flux_cur   = flux[j];
    for(int i=0; i<e_in_no; i++)
    {
      while( flux_e_cur < mg_e_in[i+1] * (1.0 + min_ene_dif) &&
             flux_e_cur < flux_e_max && j < j_max )
      {
        Real flux_e_width = 0.5 * (flux_e_cur - flux_e_pre);
        for(int b=0; b<bg_no; b++)
        {
          for(int p=0; p<pl_no; p++)
          {
            flux_tot[i][b][p] += flux_e_width * (flux_cur[b][p] + flux_pre[b][p]);
          }
        }

        j++;
        if( j < j_max )
        {
          flux_e_pre = flux_e_cur;
          flux_e_cur = flux_e[j];
          flux_pre   = flux_cur;
          flux_cur   = flux[j];
        }
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MGUtils::get_flux_data(int j, int bg_no, int pl_no,
                            vector<Real>& flux_e, vector<vector<vector<Real> > >& flux,
                            Real& flux_e_in_pre, Real& flux_e_in_cur, Real& flux_e_width,
                            vector<vector<Real> >& flux_in_pre, vector<vector<Real> >& flux_in_cur,
                            vector<vector<Real> >& flux_coef)
{
  flux_e_in_pre = flux_e[j-1];
  flux_e_in_cur = flux_e[j];
  flux_e_width  = 0.5 * (flux_e_in_cur - flux_e_in_pre);

  for(int b=0; b<bg_no; b++)
  {
    for(int p=0; p<pl_no; p++)
    {
      flux_in_pre[b][p] = flux[j-1][b][p];
      flux_in_cur[b][p] = flux[j][b][p];
      flux_coef[b][p]   = flux_e_width * (flux_in_cur[b][p] + flux_in_pre[b][p]);
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MGUtils::modify_dd_xs(vector<vector<vector<vector<Real> > > >& xs_dd,
                           vector<vector<vector<Real> > >& flux_tot)
{
  for(int i=0; i<static_cast<int>(xs_dd.size()); i++)
  {
    for(int b=0; b<static_cast<int>(xs_dd[i].size()); b++)
    {
      for(int p=0; p<static_cast<int>(xs_dd[i][b].size()); p++)
      {
        Real coef_val = 1.0 / flux_tot[i][b][p];
        for(int j=0; j<static_cast<int>(xs_dd[i][b][p].size()); j++)
        {
          xs_dd[i][b][p][j] *= coef_val;

          if( fabs(xs_dd[i][b][p][j]) < min_value )
          {
            xs_dd[i][b][p][j] = 0.0;
          }
        }
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MGUtils::modify_mg_dd_xs_with_equi_prob_angular_data
                (vector<vector<vector<vector<Real> > > >& xs_dd, vector<Real>& equi_prob_data)
{
  int e_in_no = static_cast<int>(xs_dd.size());
  int bg_no   = static_cast<int>(xs_dd[0].size());
  int pl_no   = static_cast<int>(xs_dd[0][0].size());
  if( pl_no == 0 )
  {
    return;
  }

  vector<Real> legendre_coef = get_legendre_coef_from_equi_prob_data(equi_prob_data, pl_no);
  for(int i=0; i<e_in_no; i++)
  {
    for(int b=0; b<bg_no; b++)
    {
      for(int p=0; p<pl_no; p++)
      {
        int j_max = static_cast<int>(xs_dd[i][b][p].size());
        for(int j=0; j<j_max; j++)
        {
          xs_dd[i][b][p][j] *= legendre_coef[p];
        }
      }
    }
  }
}


////////////////////////////////////////////////////////////////////////////////////////////////////

vector<Real> MGUtils::get_legendre_coef_from_equi_prob_data
                        (vector<Real>& equi_prob_data, int pl_no)
{
  vector<Real> legendre_coef;

  int i_max = static_cast<int>(equi_prob_data.size());
  if( i_max == 0 )
  {
    legendre_coef.resize(pl_no+1);
    legendre_coef[0] = 1.0;
    for(int p=1; p<pl_no+1; p++)
    {
      legendre_coef[p] = 0.0;
    }
    return legendre_coef;
  }

  vector<Real> mu_mid, mu_delta, pdf_vec;
  mu_mid.resize(i_max);
  mu_delta.resize(i_max);
  pdf_vec.resize(i_max);

  Real pdf_val = 1.0 / static_cast<Real>(i_max);
  for(int i=0; i<i_max; i++)
  {
    pdf_vec[i] = pdf_val;

    if( i == 0 )
    {
      mu_delta[i] = equi_prob_data[i] + 1.0;
    }
    else
    {
      mu_delta[i] = equi_prob_data[i] - equi_prob_data[i-1];
    }

    mu_mid[i] = equi_prob_data[i] - 0.5*mu_delta[i];
  }

  FMGen::calcPlCoefficient(mu_mid, mu_delta, pdf_vec, legendre_coef, pl_no);
  mu_mid.clear();
  mu_delta.clear();
  pdf_vec.clear();

  return legendre_coef;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<Real> MGUtils::calc_part_xs_data
                        (vector<Real>& ene_data, vector<Real>& xs_data,
                         vector<Integer>& yield_range, vector<Integer>& yield_int,
                         vector<Real>&    yield_ene,   vector<Real>&    yield_data)
{
  int ene_no   = static_cast<int>(ene_data.size());
  int xs_no    = static_cast<int>(xs_data.size());

  vector<Real> ene_data_mod, yield_mod;
  yield_mod.resize(xs_no);
  ene_data_mod.resize(xs_no);
  
  int ene_sta_xs = ene_no - xs_no;
  for(int i=ene_sta_xs; i<ene_no; i++)
  {
    Real yield_val = 0.0;
    ti_obj.interpolation_tab1(ene_data[i], yield_val,
                              yield_range, yield_int, yield_ene, yield_data);

    yield_mod[i - ene_sta_xs]    = yield_val;
    ene_data_mod[i - ene_sta_xs] = ene_data[i];
  }
  ene_data = ene_data_mod;
  ene_data_mod.clear();

  return calc_part_xs_data(ene_data, xs_data, yield_mod);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<Real> MGUtils::calc_part_xs_data
                        (vector<Real>& ene_data, vector<Real>& xs_data, vector<Real>& yield_data)
{
  int ene_no   = static_cast<int>(ene_data.size());
  int xs_no    = static_cast<int>(xs_data.size());
  int yield_no = static_cast<int>(yield_data.size());

  if( ene_no < xs_no || ene_no < yield_no )
  {
    string class_name = "MGUtils";
    string func_name  = "modify_xs_data";

    ostringstream oss01, oss02, oss03;
    oss01 << ene_no;
    oss02 << xs_no;
    oss03 << yield_no;
    string str_data01 = "Energy grid number : " + oss01.str();
    string str_data02 = "XS data number     : " + oss02.str();
    string str_data03 = "Yield data number  : " + oss03.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("The energy grid number is less than XS data number or yield data number.");
    err_com.push_back("Please check the energy/xs/yield data.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  vector<Real> xs_data_mod;
  xs_data_mod.resize(xs_no);
  int ene_sta_yield = xs_no - yield_no;
  for(int i=0; i<xs_no; i++)
  {
    xs_data_mod[i] = 0.0;
    if( i >= ene_sta_yield )
    {
      xs_data_mod[i] = xs_data[i] * yield_data[i - ene_sta_yield];
    }
  }

  return xs_data_mod;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<Real> MGUtils::get_p0_flux(vector<vector<vector<Real> > >& flux_ang)
{
  vector<Real> flux;
  flux.clear();

  int ene_no = static_cast<int>(flux_ang.size());
  if( ene_no == 0 )
  {
    return flux;
  }

  int bg_no  = static_cast<int>(flux_ang[0].size());
  if( bg_no == 0 )
  {
    return flux;
  }

  int pl_no  = static_cast<int>(flux_ang[0][0].size());
  if( pl_no == 0 )
  {
    return flux;
  }

  flux.resize(ene_no);
  for(int i=0; i<ene_no; i++)
  {
    flux[i] = flux_ang[i][0][0];
  }

  return flux;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<vector<vector<Real> > > MGUtils::remove_zero_xs_data(vector<Real>& xs,
                                          vector<int>& ig_vec, vector<int>& ng2_vec, vector<int>& ig2lo_vec)
{
  vector<vector<vector<Real> > > xs_mod;
  clr_obj.clear_vec_array3_real(xs_mod);

  int e_in_no  = static_cast<int>(xs.size());

  ig_vec.clear();
  ng2_vec.clear();
  ig2lo_vec.clear();
  for(int i=0; i<e_in_no; i++)
  {
    if( fabs(xs[i]) > min_value )
    {
      ig_vec.push_back(i+1);
      ng2_vec.push_back(2);
      ig2lo_vec.push_back(1);

      vector<vector<Real> > xs_tmp;
      xs_tmp.resize(1);
      xs_tmp[0].resize(1);
      xs_tmp[0][0] = xs[i];

      xs_mod.push_back(xs_tmp);
      clr_obj.clear_vec_array2_real(xs_tmp);
    }
  }

  return xs_mod;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<vector<vector<Real> > > MGUtils::remove_zero_xs_data(vector<vector<Real> >& xs,
                                          vector<int>& ig_vec, vector<int>& ng2_vec, vector<int>& ig2lo_vec)
{
  vector<vector<vector<Real> > > xs_mod;
  clr_obj.clear_vec_array3_real(xs_mod);

  int bg_no = static_cast<int>(xs.size());
  if( bg_no == 0 )
  {
    return xs_mod;
  }

  int e_in_no  = static_cast<int>(xs[0].size());

  ig_vec.clear();
  ng2_vec.clear();
  ig2lo_vec.clear();
  for(int i=0; i<e_in_no; i++)
  {
    int no_e_in_flg = -1;
    for(int b=0; b<bg_no; b++)
    {
      if( fabs(xs[b][i]) > min_value )
      {
        no_e_in_flg = 1;
        break;
      }
    }

    if( no_e_in_flg > 0 )
    {
      ig_vec.push_back(i+1);
      ng2_vec.push_back(2);
      ig2lo_vec.push_back(1);

      vector<vector<Real> > xs_tmp;
      xs_tmp.resize(bg_no);
      for(int b=0; b<bg_no; b++)
      {
        xs_tmp[b].resize(1);
        xs_tmp[b][0] = xs[b][i];
      }

      xs_mod.push_back(xs_tmp);
      clr_obj.clear_vec_array2_real(xs_tmp);
    }
  }

  return xs_mod;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MGUtils::remove_zero_xs_data(vector<vector<vector<Real> > >& xs,
                                  vector<int>& ig_vec, vector<int>& ng2_vec, vector<int>& ig2lo_vec)
{
  int e_in_no  = static_cast<int>(xs.size());
  int bg_no    = static_cast<int>(xs[0].size());
  int pl_no    = static_cast<int>(xs[0][0].size());

  vector<vector<vector<Real> > > xs_mod;
  clr_obj.clear_vec_array3_real(xs_mod);

  ig_vec.clear();
  ng2_vec.clear();
  ig2lo_vec.clear();
  for(int i=0; i<e_in_no; i++)
  {
    int no_e_in_flg = -1;
    for(int b=0; b<bg_no; b++)
    {
      for(int p=0; p<pl_no; p++)
      {
        if( fabs(xs[i][b][p]) > min_value )
        {
          no_e_in_flg = 1;
          break;
        }
      }

      if( no_e_in_flg > 0 )
      {
        break;
      }
    }

    if( no_e_in_flg > 0 )
    {
      ig_vec.push_back(i+1);
      ng2_vec.push_back(2);
      ig2lo_vec.push_back(1);
      xs_mod.push_back(xs[i]);
    }
  }

  xs = xs_mod;
  clr_obj.clear_vec_array3_real(xs_mod);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MGUtils::remove_zero_dd_xs_data(vector<vector<vector<vector<Real> > > >& dd_xs,
                                  vector<int>& ig_vec, vector<int>& ng2_vec, vector<int>& ig2lo_vec)
{
  int e_in_no  = static_cast<int>(dd_xs.size());
  int bg_no    = static_cast<int>(dd_xs[0].size());
  int pl_no    = static_cast<int>(dd_xs[0][0].size());
  int e_out_no = static_cast<int>(dd_xs[0][0][0].size());

  vector<vector<vector<vector<Real> > > > dd_xs_mod;
  clr_obj.clear_vec_array4_real(dd_xs_mod);

  ig_vec.clear();
  ng2_vec.clear();
  ig2lo_vec.clear();
  for(int i=0; i<e_in_no; i++)
  {
    int no_e_in_flg = 0;
    int ig2lo_val   = 0;
    int ig2hi_val   = 0;
    for(int j=0; j<e_out_no; j++)
    {
      for(int b=0; b<bg_no; b++)
      {
        for(int p=0; p<pl_no; p++)
        {
          if( fabs(dd_xs[i][b][p][j]) > min_value )
          {
            no_e_in_flg = 1;
            ig2lo_val   = j;
            break;
          }
        }

        if( no_e_in_flg > 0 )
        {
          break;
        }
      }

      if( no_e_in_flg > 0 )
      {
        break;
      }
    }

    if( no_e_in_flg > 0 )
    {
      ig_vec.push_back(i+1);
      ig2lo_vec.push_back(ig2lo_val+1);

      no_e_in_flg = 0;
      ig2hi_val   = 0;
      for(int j=e_out_no-1; j>=0; j--)
      {
        for(int b=0; b<bg_no; b++)
        {
          for(int p=0; p<pl_no; p++)
          {
            if( fabs(dd_xs[i][b][p][j]) > min_value )
            {
              no_e_in_flg = 1;
              ig2hi_val   = j;
              break;
            }
          }

          if( no_e_in_flg > 0 )
          {
            break;
          }
        }

        if( no_e_in_flg > 0 )
        {
          break;
        }
      }

      int ng2_no = ig2hi_val - ig2lo_val + 2;
      ng2_vec.push_back(ng2_no);

      vector<vector<vector<Real> > > dd_xs_tmp;
      clr_obj.clear_vec_array3_real(dd_xs_tmp);
      dd_xs_tmp.resize(bg_no);   
      for(int b=0; b<bg_no; b++)
      {
        dd_xs_tmp[b].resize(pl_no);   
        for(int p=0; p<pl_no; p++)
        {
          dd_xs_tmp[b][p].resize(ng2_no-1);   
          for(int j=ig2lo_val; j<=ig2hi_val; j++)
          {
            dd_xs_tmp[b][p][j-ig2lo_val] = dd_xs[i][b][p][j];
          }
        }
      }

      dd_xs_mod.push_back(dd_xs_tmp);
      clr_obj.clear_vec_array3_real(dd_xs_tmp);
    }
  }

  dd_xs = dd_xs_mod;
  clr_obj.clear_vec_array4_real(dd_xs_mod);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<vector<vector<Real> > > MGUtils::modify_flux(vector<vector<vector<Real> > >& flux,
                                                    vector<int> ig_vec, int bg_no, int pl_no)
{
  vector<vector<vector<Real> > > flux_mod = modify_flux(flux, ig_vec);

  return modify_flux(flux_mod, bg_no, pl_no);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<vector<vector<Real> > > MGUtils::modify_flux(vector<vector<vector<Real> > >& flux,
                                                    vector<int> ig_vec)
{
  vector<vector<vector<Real> > > flux_mod;

  int e_max = static_cast<int>(flux.size());
  int i_max = static_cast<int>(ig_vec.size());
  flux_mod.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    if( ig_vec[i] >= e_max )
    {
      string class_name = "MGUtils";
      string func_name  = "modify_flux";

      ostringstream oss01, oss02, oss03, oss04;
      oss01 << i+1;
      oss02 << i_max;
      oss03 << ig_vec[i];
      oss04 << e_max;
      string str_data01 = "IG (" + oss01.str() + " / " + oss02.str() + ") : " + oss03.str();
      string str_data02 = "Ein number from FLUX : " + oss04.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back("IG is larger than Ein number from FLUX.");
      err_com.push_back("Please check the IG or FLUX data.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
    else if( ig_vec[i] < 0 )
    {
      flux_mod[i].clear();
      if( i == i_max - 1 )
      {
        flux_mod[i] = flux[e_max-1];
      }
    }
    else
    {
      //Energy grid number of flux is NGN + 1 to treat MF=6/MT=18.
      //So, flux_mod[i] is not equal to flux[ig_vec[i]-1].
      //See store_data() function in GMFxxParserBase class.
      //(EndfUtils/GendfParser/GMFxxParserBase.cpp)
      flux_mod[i] = flux[ig_vec[i]];
    }
  }

  return flux_mod;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<vector<vector<Real> > > MGUtils::modify_flux(vector<vector<vector<Real> > >& flux,
                                                    int bg_no, int pl_no)
{
  vector<vector<vector<Real> > > flux_mod;
  int i_max = static_cast<int>(flux.size());
  flux_mod.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(flux[i].size());
    if( j_max == 0 )
    {
      flux_mod[i].clear();
      continue;
    }

    if( bg_no > j_max )
    {
      string class_name = "MGUtils";
      string func_name  = "modify_flux(vector<vector<vector<Real> > >& flux, int bg_no, int pl_no)";

      ostringstream oss01, oss02;
      oss01 << bg_no;
      oss02 << j_max;
      string str_data01 = "Sig-z number (bg_no)          : " + oss01.str();
      string str_data02 = "Sig-z number (flux[i].size()) : " + oss02.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back("bg_no is larger than flux[i].size().");
      err_com.push_back("Please check the bg_no or flux data.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    flux_mod[i].resize(bg_no);
    for(int j=0; j<bg_no; j++)
    {
      int k_max = static_cast<int>(flux[i][j].size());
      if( pl_no > k_max )
      {
        string class_name = "MGUtils";
        string func_name  = "modify_flux(vector<vector<vector<Real> > >& flux, int bg_no, int pl_no)";

        ostringstream oss01, oss02, oss03, oss04;
        oss01 << bg_no;
        oss02 << j_max;
        oss03 << pl_no;
        oss04 << k_max;
        string str_data01 = "Sig-z number (bg_no)          : " + oss01.str();
        string str_data02 = "Sig-z number (flux[i].size()) : " + oss02.str();
        string str_data03 = "Pl number (pl_no)             : " + oss03.str();
        string str_data04 = "Pl number (flux[i][j].size()) : " + oss04.str();

        vector<string> err_com;
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back(str_data04);
        err_com.push_back("pl_no is larger than flux[i][j].size().");
        err_com.push_back("Please check the pl_no or flux data.");

        err_obj.output_runtime_error(class_name, func_name, err_com);
      }
      
      flux_mod[i][j].resize(pl_no);
      for(int k=0; k<pl_no; k++)
      {
        flux_mod[i][j][k] = flux[i][j][k];
      }
    }
  }

  return flux_mod;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<vector<vector<Real> > > MGUtils::multiply_coef(vector<Real>& xs_ene, vector<vector<Real> >& xs_vec,
                                                      vector<Real>& coef_ene, vector<vector<Real> >& coef_vec)
{
  vector<vector<vector<Real> > > xs_multi;
  xs_multi.clear();

  int xs_no   = static_cast<int>(xs_ene.size());
  int b_no    = static_cast<int>(xs_vec.size());
  int coef_no = static_cast<int>(coef_ene.size());
  if( xs_no == 0 || b_no == 0 || coef_no == 0 )
  {
    return xs_multi;
  }
  else if( xs_no != static_cast<int>(xs_vec[0].size()) )
  {
    string class_name = "MGUtils";
    string func_name  = "multiply_coef";

    ostringstream oss01, oss02;
    oss01 << xs_no;
    oss02 << static_cast<int>(xs_vec[0].size());
    string str_data01 = "Energy grid number of xs_ene    : " + oss01.str();
    string str_data02 = "Energy grid number of xs_vec[0] : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("Energy grid number of xs_ene is different to that of xs_vec[0].");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  xs_multi.resize(xs_no);
//  if( coef_no == 0 )
//  {
//    for(int i=0; i<xs_no; i++)
//    {
//      xs_multi[i].resize(b_no);
//      for(int b=0; b<b_no; b++)
//      {
//        xs_multi[i][b].resize(1);
//        xs_multi[i][b][0] = xs_vec[b][i];
//      }
//    }
//    return xs_multi;
//  }


  int j     = 0;
  int pl_no = static_cast<int>(coef_vec[0].size());
  for(int i=0; i<xs_no; i++)
  {
    xs_multi[i].resize(b_no);
    for(int b=0; b<b_no; b++)
    {
      xs_multi[i][b].resize(pl_no);
      for(int p=0; p<pl_no; p++)
      {
        xs_multi[i][b][p] = 0.0;
      }
    }

    while( coef_ene[j] < xs_ene[i] && j < coef_no-1 )
    {
      j++;
    }
  
    for(int b=0; b<b_no; b++)
    {
      if( fabs(xs_vec[b][i]) > min_value )
      {
        for(int p=0; p<pl_no; p++)
        {
          xs_multi[i][b][p] = xs_vec[b][i] * coef_vec[j][p]; 
        }
      }
    }
  }

  return xs_multi;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MGUtils::set_awr_val(Real real_val)
{
  if( real_val < min_value )
  {
    string class_name = "MGUtils";
    string func_name  = "set_awr_val(Real real_val)";

    ostringstream oss;
    oss.precision(8);
    oss.setf(ios::scientific);
    oss.setf(ios::showpoint);
    oss << real_val;
    string str_data = "AWR : " + oss.str();

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("The atomic weight ration (AWR) is less than or equal to 0.0.");
    err_com.push_back("Please check the AWR value.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  awr_val  = real_val;
  awr_coef = awr_val / (awr_val + 1.0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Real MGUtils::get_awr_val()
{
  return awr_val;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MGUtils::set_mce_bin_no(int int_val)
{
  mce_bin_no = int_val;

  mce_pos_p  = -1;
  mce_pos_m  = -1;
  mce_int    = -1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int MGUtils::get_mce_bin_no()
{
  return mce_bin_no;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Real MGUtils::get_discrete_photon_energy(Integer lp, Real& photon_ene, Real& e_in)
{
  if( lp == 0 || lp == 1 )
  {
    return photon_ene;
  }
  else if( lp != 2 )
  {
    string class_name = "MGUtils";
    string func_name  = "get_discrete_photon_energy";

    ostringstream oss;
    oss << lp;
    string str_data = "LP : " + oss.str();

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("(Indicator whether the photon is a primary or non-primary photon.)");
    err_com.push_back("Available LP value is 0, 1, and 2.");
    err_com.push_back("Please check the LP value.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }


  return photon_ene + e_in * awr_coef;
}

////////////////////////////////////////////////////////////////////////////////////////////////////


