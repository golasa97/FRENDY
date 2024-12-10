#ifndef MG_PHOTON_PRODUCTION_H
#define MG_PHOTON_PRODUCTION_H

#include "CommonUtils/TabInterpolator.hpp"
#include "CommonUtils/DigitAdjuster.hpp"
#include "ContinuousEnergyXSUtils/AceDataParser/FastAceDataParser.hpp"
#include "TabUtils/TwoDInterpolator.hpp"
#include "TabUtils/IntegrateTabData.hpp"
#include "MGXSUtils/FMGenerator/FMZlib.h"
#include "MGXSUtils/OtherUtils/MGUtils.hpp"
#include "EndfUtils/GendfParser/GendfParser.hpp"
#include "EndfUtils/GendfWriter/GMF16Writer.hpp"

namespace frendy
{
  class MGPhotonProduction
  {
    private:
      frendy::ErrorManager     err_obj;
      frendy::VectorClearer    clr_obj;
      frendy::DigitAdjuster    digit_obj;
      frendy::TabAdjuster      ta_obj;
      frendy::TabInterpolator  ti_obj;

#ifdef DEBUG_MODE
  public:
#endif
      frendy::MGUtils          mg_obj;

      int                      add_pl_data_flg;
      int                      pl_no_ori;
      int                      add_mf13_data_flg;

      //Data from ACE file
      vector<Real>             ace_ene_grid, ace_xs_tot;

      //Data from MTRP block
      vector<Integer>          mtrp_mt_list;

      //Data from SIGP block
      vector<Integer>          sigp_file_no;
      vector<Integer>          sigp_react_type;

      //For MF = 13
      vector<vector<Integer> > sigp_pos;
      vector<vector<Real> >    sigp_xs;

      //For MF = 12
      vector<vector<Integer> > sigp_multi_range, sigp_multi_int;
      vector<vector<Real> >    sigp_multi_ene,   sigp_multi_data;

      //For MF = 16
      vector<vector<Integer> > sigp_distr_range, sigp_distr_int;
      vector<vector<Real> >    sigp_distr_ene,   sigp_distr_data;
      

      //Data from ANDP block
      vector<vector<Real> >          andp_ene_data;
      vector<vector<vector<Real> > > andp_cos_data;

      //Data from DLWP block
      vector<Integer>          dlwp_distr_flg;
      vector<vector<Integer> > dlwp_range, dlwp_int;
      vector<vector<Real> >    dlwp_ene, dlwp_prob;

      //DLWP Law = 2
      vector<Integer>       dlwp_ene_distr_flg;
      vector<Real>          dlwp_binding_ene;

      //DLWP Law = 4
      vector<vector<Integer> >       dlwp_ein_range, dlwp_ein_int;
      vector<vector<Real> >          dlwp_ein_data;
      vector<vector<Integer> >       dlwp_eout_int;
      vector<vector<vector<Real> > > dlwp_eout_data, dlwp_eout_weight;

      //Calculation results
      vector<int>                    mt_list, mt_list_pos, emit_photon_no;
      vector<vector<Real> >          transition_prob;
      vector<vector<vector<Integer> > > ddxs_multi_range, ddxs_multi_int;
      vector<vector<vector<Real> > >    ddxs_multi_ene,   ddxs_multi_data;

      vector<Real>                   photon_xs_fine_ene;
      vector<vector<Real> >          photon_xs_fine;
      vector<vector<vector<Real> > > dd_xs_coef;
      vector<vector<vector<Real> > > flux_ang;

      vector<vector<vector<Real> > >                   photon_xs;
      vector<vector<vector<vector<vector<Real> > > > > photon_dd_xs;

      //Other data
      int calc_dd_xs_flg;
      vector<Real> egg_vec;

      Integer za_val;
      Real    awr_val;

      void modify_mg_ene_data(vector<Real>& mg_ene_data);

      void get_mt_list();

      void copy_ace_data(frendy::FastAceDataObject& ace_obj);

      void calc_photon_production_data_each_mt
             (int mt_pos, frendy::FastAceDataObject& ace_obj, vector<Real>& ene_vec,
              vector<vector<Real> >& flux_vec, vector<vector<Real> >& sig_t_sig_bg,
              vector<Real>& mg_ein, vector<Real>& mg_eout, int pl_no);

      void calc_photon_production_xs
             (int mt_pos, frendy::FastAceDataObject& ace_obj,
              vector<Real>& ene_vec, vector<vector<Real> >& flux_vec, vector<Real>& mg_ein);

      void calc_photon_production_dd_xs
             (int mt_pos, frendy::FastAceDataObject& ace_obj, vector<Real>& ene_vec,
              vector<vector<Real> >& flux_vec, vector<vector<Real> >& sig_t_sig_bg,
              vector<Real>& mg_ein, vector<Real>& mg_eout, int pl_no);
      void modify_dlwp_eout_data
             (vector<Integer>& dlwp_eout_int_ori,
              vector<vector<Real> >& dlwp_eout_data_ori,  vector<vector<Real> >& dlwp_eout_weight_ori,
              vector<Integer>& dlwp_eout_int_mod,
              vector<vector<Real> >& dlwp_eout_data_cont, vector<vector<Real> >& dlwp_eout_weight_cont,
              vector<vector<Real> >& dlwp_eout_data_disc, vector<vector<Real> >& dlwp_eout_weight_disc);
      void modify_dlwp_eout_data_threshold_ene
             (int mt_pos_tot,
              vector<vector<Real> >& dlwp_eout_data_cont, vector<vector<Real> >& dlwp_eout_weight_cont,
              vector<vector<Real> >& dlwp_eout_data_disc, vector<vector<Real> >& dlwp_eout_weight_disc);

      void calc_photon_production_dd_xs_with_discrete_ene
             (int mt_pos, frendy::FastAceDataObject& ace_obj, vector<Real>& ene_vec,
              vector<vector<Real> >& flux_vec, vector<vector<Real> >& sig_t_sig_bg,
              vector<Real>& mg_ein, vector<Real>& mg_eout, int pl_no);
      void add_photon_dd_xs_data(int mt_pos, Real coef,
                                 vector<vector<vector<vector<Real> > > >& photon_dd_xs_add);

      void calc_ddxs_coef(int mt_pos_tot, vector<Real>& ene_vec, int pl_no);

      void add_pl_data(int mt_pos, int& pl_no, vector<vector<vector<vector<Real> > > >& ddxs_vec);

      void merge_continuous_and_discrete_data();
      void add_photon_xs_data(vector<vector<Real> >& photon_xs_new,
                              vector<vector<Real> >& photon_xs_add);
      void add_photon_dd_xs_data(vector<vector<vector<vector<Real> > > >& photon_dd_xs_new,
                                 vector<vector<vector<vector<Real> > > >& photon_dd_xs_add);

    public:

      //constructor
      MGPhotonProduction(void);

      //destructor
      virtual ~MGPhotonProduction(void);

      void clear();
      void clear_calc_data();

      void modify_flux(vector<Real>& ene_vec,
                       vector<vector<Real> >& flux_vec,
                       vector<vector<Real> >& sig_t_sig_bg);

      void calc_photon_production_data
            (frendy::FastAceDataObject& ace_obj, vector<Real> ene_vec,
             vector<vector<Real> > flux_vec, vector<vector<Real> > sig_t_sig_bg,
             vector<Real> mg_ein, vector<Real> mg_eout, int pl_no);

      void merge_gendf(frendy::GendfParser& gendf_obj);

      vector<vector<vector<Real> > >                   get_photon_xs();
      vector<vector<vector<vector<vector<Real> > > > > get_photon_dd_xs();

     vector<frendy::GMF16Parser> get_mf16_data();
     vector<frendy::GMF13Parser> get_mf13_data();

     Integer get_za_val();
     Real    get_awr_val();
  }; 
}

#endif //MG_PHOTON_PRODUCTION_H
