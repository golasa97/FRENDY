#ifndef MG_UTILS_H
#define MG_UTILS_H

#include "CommonUtils/TabInterpolator.hpp"
#include "TabUtils/TwoDInterpolator.hpp"
#include "TabUtils/IntegrateTabData.hpp"
#include "MGXSUtils/FMGenerator/FMZlib.h"

namespace frendy
{
  class MGUtils
  {
    private:
      frendy::ErrorManager    err_obj;
      frendy::VectorClearer   clr_obj;
      frendy::TabInterpolator ti_obj;
      frendy::TabAdjuster     ta_obj;

      frendy::TwoDInterpolator two_d_int_obj;
      frendy::IntegrateTabData integ_obj;

#ifdef DEBUG_MODE
  public:
#endif
      int     mce_bin_no, mce_pos_p, mce_pos_m;
      Integer mce_int;

      Real awr_val,  awr_coef;

      vector<Real> xs_fine_ene, xs_fine, xs_mg;
    public:

      //constructor
      MGUtils(void);

      //destructor
      virtual ~MGUtils(void);

      void clear();


      vector<vector<vector<Real> > > calc_angular_flux
                                       (vector<Real>& flux_tot_e, vector<Real>& flux_tot,
                                        vector<Real>& sig_tot_e,  vector<Real>& sig_tot,
                                        vector<Real>& sig_bg, int pl_no);

      vector<vector<vector<Real> > > calc_angular_flux
                                       (vector<vector<Real> >& flux,
                                        vector<vector<Real> >& sig_t_sig_bg, int pl_no);

      void         calc_mg_xs(vector<Real>& flux_e, vector<Real>& flux,
                              vector<Real>& sig_e,  vector<Real>& sig,
                              vector<Real>& mg_structure, vector<Real>& sig_mg,
                              vector<Real>& sig_fine_ene, vector<Real>& sig_fine);

      void         calc_mg_xs(vector<Real>& flux_e, vector<Real>& flux,
                              vector<Real>& sig_e,  vector<Real>& sig,
                              vector<Real>& mg_structure, vector<Real>& sig_mg);

      void         calc_mg_xs_without_energy_grid_modification
                     (vector<Real>& flux_e,     vector<Real>& flux,
                      vector<Real>& sig_e,  vector<Real>& sig, vector<Real>& mg_structure,
                      vector<Real>& sig_mg);

      void         calc_mg_xs_without_energy_grid_modification
                     (vector<Real>& flux_e,     vector<Real>& flux,
                      vector<Real>& flux_all_e, vector<Real>& flux_all,
                      vector<Real>& sig_e,  vector<Real>& sig, vector<Real>& mg_structure,
                      vector<Real>& sig_mg);

      void         calc_mg_xs_with_1e(vector<Real>& sig_e,  vector<Real>& sig,
                                      vector<Real>& mg_structure, vector<Real>& sig_mg);

      void         calc_mg_xs_with_const(vector<Real>& sig_e,  vector<Real>& sig,
                                         vector<Real>& mg_structure, vector<Real>& sig_mg);

      void         calc_energy_distribution
                     (Real e_in, vector<Real>& e_out_vec_cont_new,  vector<Real>& e_out_pdf_cont_new,
                      int& e_out_disc_flg,
                      vector<Real>& e_out_vec_disc_new, vector<Real>& e_out_pdf_disc_new,
                      vector<Integer>& e_in_range, vector<Integer>& e_in_int, vector<Real>& e_in_vec,
                      vector<Integer>& e_out_int, 
                      vector<vector<Real> >& e_out_vec_cont, vector<vector<Real> >& e_out_pdf_cont,
                      vector<vector<Real> >& e_out_vec_disc, vector<vector<Real> >& e_out_pdf_disc);

      void         calc_energy_distribution_without_linearization
                     (Real e_in, vector<Real>& e_out_vec_cont_new,  vector<Real>& e_out_pdf_cont_new,
                      int& e_out_disc_flg,
                      vector<Real>& e_out_vec_disc_new, vector<Real>& e_out_pdf_disc_new,
                      vector<Integer>& e_in_range, vector<Integer>& e_in_int, vector<Real>& e_in_vec,
                      vector<vector<Real> >& e_out_vec_cont, vector<vector<Real> >& e_out_pdf_cont,
                      vector<vector<Real> >& e_out_vec_disc, vector<vector<Real> >& e_out_pdf_disc);

      vector<vector<vector<vector<Real> > > > calc_mg_dd_xs
                    (vector<vector<vector<Real> > >& dd_xs_coef,
                     vector<Real>& flux_e,  vector<vector<vector<Real> > >& flux,
                     vector<Real>& mg_e_in, vector<Real>& mg_e_out,
                     vector<Integer>& e_in_range, vector<Integer>& e_in_int,
                     vector<Real>& e_in_vec,
                     vector<Integer>& e_out_int,
                     vector<vector<Real> >& e_out_vec_cont,  vector<vector<Real> >& e_out_pdf_cont,
                     vector<vector<Real> >& e_out_vec_disc,  vector<vector<Real> >& e_out_pdf_disc);

      vector<vector<vector<vector<Real> > > > calc_mg_dd_xs_with_discrete_ene
                    (vector<vector<vector<Real> > >& dd_xs_coef,
                     vector<Real>& flux_e, vector<vector<vector<Real> > >& flux,
                     vector<Real>& mg_e_in, vector<Real>& mg_e_out,
                     vector<Integer>& multi_range, vector<Integer>& multi_int,
                     vector<Real>&    multi_ene,   vector<Real>&    multi_data,
                     Integer lp, Real& binding_ene);

      void        initialize_mg_dd_xs
                    (vector<vector<vector<Real> > >& dd_xs_coef, int& e_sta_pos,
                     vector<Real>& flux_e, vector<vector<vector<Real> > >& flux,
                     vector<Real>& mg_e_in, vector<Real>& mg_e_out,
                     int& flux_e_no, int& e_in_no, int& e_out_no, int& bg_no, int& pl_no,
                     vector<vector<vector<vector<Real> > > >& xs_dd,
                     vector<vector<vector<Real> > >& flux_tot,
                     vector<vector<Real> >& flux_in_pre, vector<vector<Real> >& flux_in_cur,
                     vector<vector<Real> >& flux_coef);

     void        get_flux_data(int j, int bg_no, int pl_no,
                   vector<Real>& flux_e, vector<vector<vector<Real> > >& flux,
                   Real& flux_e_in_pre, Real& flux_e_in_cur, Real& flux_e_width,
                   vector<vector<Real> >& flux_in_pre, vector<vector<Real> >& flux_in_cur,
                   vector<vector<Real> >& flux_coef);

      void         modify_dd_xs(vector<vector<vector<vector<Real> > > >& xs_dd,
                                vector<vector<vector<Real> > >& flux_tot);

      void         modify_mg_dd_xs_with_equi_prob_angular_data
                     (vector<vector<vector<vector<Real> > > >& xs_dd, vector<Real>& equi_prob_data);
      vector<Real> get_legendre_coef_from_equi_prob_data
                     (vector<Real>& equi_prob_data, int pl_no);

      vector<Real> calc_part_xs_data(vector<Real>& ene_data, vector<Real>& xs_data,
                                     vector<Integer>& yield_range, vector<Integer>& yield_int,
                                     vector<Real>&    yield_ene,   vector<Real>&    yield_data);

      vector<Real> calc_part_xs_data(vector<Real>& ene_data,
                                     vector<Real>& xs_data, vector<Real>& yield_data);

      vector<Real> get_p0_flux(vector<vector<vector<Real> > >& flux_ang);

      vector<vector<vector<Real> > > remove_zero_xs_data(vector<Real>& xs,
                                       vector<int>& ig_vec, vector<int>& ng2_vec, vector<int>& ig2lo_vec);
      vector<vector<vector<Real> > > remove_zero_xs_data(vector<vector<Real> >& xs,
                                       vector<int>& ig_vec, vector<int>& ng2_vec, vector<int>& ig2lo_vec);
      void         remove_zero_xs_data(vector<vector<vector<Real> > >& xs,
                                       vector<int>& ig_vec, vector<int>& ng2_vec, vector<int>& ig2lo_vec);
      void         remove_zero_dd_xs_data(vector<vector<vector<vector<Real> > > >& dd_xs,
                                          vector<int>& ig_vec, vector<int>& ng2_vec, vector<int>& ig2lo_vec);

      vector<vector<vector<Real> > > modify_flux(vector<vector<vector<Real> > >& flux, vector<int> ig_vec,
                                                 int bg_no, int pl_no);
      vector<vector<vector<Real> > > modify_flux(vector<vector<vector<Real> > >& flux, vector<int> ig_vec);
      vector<vector<vector<Real> > > modify_flux(vector<vector<vector<Real> > >& flux, int bg_no, int pl_no);

      vector<vector<vector<Real> > > multiply_coef(vector<Real>& xs_ene,   vector<vector<Real> >& xs_vec, 
                                                   vector<Real>& coef_ene, vector<vector<Real> >& coef_vec);

      void         set_awr_val(Real real_val);
      Real         get_awr_val();

      void         set_mce_bin_no(int int_val);
      int          get_mce_bin_no();

      Real         get_discrete_photon_energy(Integer lp, Real& photon_ene, Real& e_in);
  }; 
}

#endif //MG_UTILS_H
