#ifndef INCOHERENT_INELASTIC_SCATTER_CALCULATOR_H
#define INCOHERENT_INELASTIC_SCATTER_CALCULATOR_H

#include "NuclearDataUtils/NuclearDataObject.hpp"
#include "CommonUtils/VectorCopier.hpp"
#include "CommonUtils/TabInterpolator.hpp"
#include "CommonUtils/TabAdjuster.hpp"
#include "CommonUtils/DigitAdjuster.hpp"
#include "MathUtils/MathUtils.hpp"

namespace frendy
{
  class IncoherentInelasticScatterCalculator
  {
    private:
      static const int   direct_stored_mode    =  0;
      static const int   log_stored_mode       =  1;
      static const int   symmetric_mode        =  0;
      static const int   asymmetric_mode       =  1;
      static const int   actual_temp_mode      =  0;
      static const int   const_temp_mode       =  1;
      static const int   njoy_mode_on          = -1;
      static const int   njoy_mode_off         =  1;
//#ifdef NJOY_MODE
      static const int   njoy_mode_flg         = njoy_mode_on;
//#else
//      static const int   njoy_mode_flg         = njoy_mode_off;
//#endif
      static const Real8 min_sab_index_number;  //= -225.0;
      static const Real8 min_sab_value;         //=    1.0E-225;
      static const Real8 beta_max_warning_val;  //=    5.0;
      static const Real8 alpha_min_val;         //=    1.0E-6;

  protected:
      static const Integer xs_type_elastic = 2;

      frendy::ErrorManager    err_obj;
      frendy::VectorClearer   clr_obj;
      frendy::VectorCopier    cp_obj;
      frendy::TabInterpolator ti_obj;
      frendy::TabAdjuster     ta_obj;
      frendy::DigitAdjuster   digit_obj;
      frendy::MathUtils       math_obj;
      Real8                   min_inelastic_xs_val;
      Real8                   conv_th_ene_inv;
      Real8                   third;

#ifdef DEBUG_MODE
  public:
#endif
      static const int   no_interpolation_mode = 0;
      static const int   interpolation_mode    = 1;
      int lagrange_interpolation_flg, ene_grid_flg;

      frendy::NuclearDataObject           nucl_data_obj;
      frendy::ThermalScatterDataContainer sab_data_obj;

      int                      bin_no_int;
      Integer                  bin_no, opt_inelastic, atom_no;
      Real8                    temp_tsl, temp_tsl_ev, temp_tsl_ev_inv;
      Real8                    err, err_half, err_int, ene_max, temp_inp, bin_no_real, bin_no_inv;

      Integer                  calc_incoherent_inelastic_scat_flg,
                               temp_flg, symmetric_flg, stored_form_flg;
      vector<vector<Integer> > sab_range_data, sab_int_data;  
      vector<vector<Real8> >   sab_alpha_data, sab_data;
      vector<Integer>          beta_range_data, beta_int_data;
      vector<Real8>            beta, sig_b, mass_inv, temp_eff, temp_eff_ev, temp_eff_ev_inv;
      Real8                    sab_chk, beta_min, beta_max;
      vector<Real8>            alpha_min, alpha_max;

      Real8                           ene_out_min;
      vector<Real8>                   ene_grid, ene_grid_prod_distr, scat_xs_tot;
      vector<vector<Real8> >          second_ene_grid, scat_xs_tot_second_ene;
      vector<vector<vector<Real8> > > scat_angle, scat_xs;
      vector<vector<vector<Real8> > > integrated_scat_angle, integrated_scat_xs;

      void calc_scat_xs();

      //For linearization of scat_xs_tot
      void linearize_scat_xs(vector<Real>& ene_grid_cal);
      int  comp_interpolation_value
             (int& ele_no, vector<Real8>& new_ene_grid_part,
                           vector<Real8>& new_scat_xs_tot_part,
                           vector<vector<Real8> >& new_second_ene_grid_part,
                           vector<vector<Real8> >& new_scat_xs_tot_second_ene_part,
                           vector<vector<vector<Real8> > >& new_scat_angle_part,
                           vector<vector<vector<Real8> > >& new_scat_xs_part,
                           vector<vector<vector<Real8> > >& new_integrated_scat_angle_part,
                           vector<vector<vector<Real8> > >& new_integrated_scat_xs_part,
                           Real& mid_ene_grid, Real& mid_scat_xs_tot,
                           vector<Real8>& mid_scat_xs_tot_second_ene_vec,
                           vector<Real8>& mid_second_ene_grid_vec,
                           vector<vector<Real8> >& mid_scat_angle_vec,
                           vector<vector<Real8> >& mid_scat_xs_vec,
                           vector<vector<Real8> >& mid_integrated_scat_angle_vec,
                           vector<vector<Real8> >& mid_integrated_scat_xs_vec);
      void insert_middle_scat_xs_data
             (int& ele_no, vector<Real8>& new_ene_grid_part,
                           vector<Real8>& new_scat_xs_tot_part,
                           vector<vector<Real8> >& new_second_ene_grid_part,
                           vector<vector<Real8> >& new_scat_xs_tot_second_ene_part,
                           vector<vector<vector<Real8> > >& new_scat_angle_part,
                           vector<vector<vector<Real8> > >& new_scat_xs_part,
                           vector<vector<vector<Real8> > >& new_integrated_scat_angle_part,
                           vector<vector<vector<Real8> > >& new_integrated_scat_xs_part,
                           Real& mid_ene_grid, Real& mid_scat_xs_tot,
                           vector<Real8>& mid_scat_xs_tot_second_ene_vec,
                           vector<Real8>& mid_second_ene_grid_vec,
                           vector<vector<Real8> >& mid_scat_angle_vec,
                           vector<vector<Real8> >& mid_scat_xs_vec,
                           vector<vector<Real8> >& mid_integrated_scat_angle_vec,
                           vector<vector<Real8> >& mid_integrated_scat_xs_vec);
      void add_ene_and_scat_xs_data
             (vector<Real8>& new_ene_grid, vector<Real8>& new_scat_xs_tot,
              vector<vector<Real8> >& new_second_ene_grid,
              vector<vector<Real8> >& new_scat_xs_tot_second_ene,
              vector<vector<vector<Real8> > >& new_scat_angle,
              vector<vector<vector<Real8> > >& new_scat_xs,
              vector<vector<vector<Real8> > >& new_integrated_scat_angle,
              vector<vector<vector<Real8> > >& new_integrated_scat_xs,
              vector<Real8>& new_ene_grid_part, vector<Real8>& new_scat_xs_tot_part,
              vector<vector<Real8> >& new_second_ene_grid_part,
              vector<vector<Real8> >& new_scat_xs_tot_second_ene_part,
              vector<vector<vector<Real8> > >& new_scat_angle_part,
              vector<vector<vector<Real8> > >& new_scat_xs_part,
              vector<vector<vector<Real8> > >& new_integrated_scat_angle_part,
              vector<vector<vector<Real8> > >& new_integrated_scat_xs_part);

      //For calculation of scat_xs_tot
      void calc_scat_xs_each_ene(Real& ene_val, Real8& scat_xs_tot_val,
                                 vector<Real8>& scat_xs_tot_second_ene_vec,
                                 vector<Real8>& second_ene_grid_vec,
                                 vector<vector<Real8> >& scat_angle_vec,
                                 vector<vector<Real8> >& scat_xs_vec,
                                 vector<vector<Real8> >& integrated_scat_angle_vec,
                                 vector<vector<Real8> >& integrated_scat_xs_vec);
      void init_scat_data( Real8& ene_in_data, Real8& xs_tot_data, vector<Real8>& xs_tot_ene_out,
                           vector<Real8>& ene_out_data,
                           vector<vector<Real8> >& mu_data,     vector<vector<Real8> >& xs_data,
                           vector<vector<Real8> >& mu_data_int, vector<vector<Real8> >& xs_data_int );
      void calc_scat_xs_tot(Real8& xs_tot_data, vector<Real8>& xs_tot_ene_out, vector<Real8>& ene_out_data);
      void calc_scat_xs_mu_tot(Real8& xs_tot_data, vector<Real8>& mu_data, vector<Real8>& xs_data);

      //If fabs(a_val) < 1.0E-30, a_val considerd as 0.0
      void adjust_xs_and_mu( vector<vector<Real8> >& mu_data,     vector<vector<Real8> >& xs_data,
                             vector<vector<Real8> >& mu_data_int, vector<vector<Real8> >& xs_data_int,
                             Real8& xs_tot_data, vector<Real8>& xs_tot_ene_out );

      //modify xs_tot_ene_out and xs_data_int to meet the PENDF data format
      void modify_second_xs_data( Real8& ene_in_data, Real8& xs_tot_data,
                                  vector<Real8>& xs_tot_ene_out, vector<vector<Real8> >& xs_data_int );

      //When free-gas model is used, scat_xs_tot is identical to elastic scatter cross section
      void modify_scat_xs_tot( vector<Real8>& ene_in_data, vector<Real8>& xs_tot_data );

      //Calculate scat_xs_tot at the original energy grid by 5th order kagrange interpolation
      void calc_scat_xs_tot_by_lagrange_interpolation(vector<Real8>& ene_in_data, vector<Real8>& xs_tot_data );

      //For secondary energy
      void    linearize_incoherent_inelastic_scatter_e_out
                (Real8& ene_in_data, vector<Real8>& ene_out_data, vector<Real>& xs_data_tot,
                 vector<vector<Real8> >& mu_data,     vector<vector<Real8> >& xs_data,
                 vector<vector<Real8> >& mu_data_int, vector<vector<Real8> >& xs_data_int);
      void    set_ene_out_grid(Real8& ene_in_data, vector<Real8>& ene_out_data);
      void    remove_unnecessary_ene_out_grid
                (Real& ene_in_data, vector<Real>& ene_out_data, vector<Real>& xs_data_tot,
                 vector<vector<Real8> >& mu_data,     vector<vector<Real8> >& xs_data,
                 vector<vector<Real8> >& mu_data_int, vector<vector<Real8> >& xs_data_int);
      Integer check_ene_out_grid
               ( Real8&         ene_out_pre, Real8&         ene_out_cur,
                 Real8&         xs_tot_pre,  Real8&         xs_tot_cur,  Real8&         mid_xs_tot,
                 vector<Real8>& xs_int_pre,  vector<Real8>& xs_int_cur,  vector<Real8>& mid_xs_int );
      void    insert_middle_ene_out_grid
                ( int& ele_no, vector<Real8>& ene_out_data,         vector<Real8>& xs_data_tot,
                               vector<vector<Real8> >& mu_data,     vector<vector<Real8> >& xs_data,
                               vector<vector<Real8> >& mu_data_int, vector<vector<Real8> >& xs_data_int,
                               Real8&                  mid_ene,     Real8&                  mid_xs_tot,
                               vector<Real8>&          mid_mu,      vector<Real8>&          mid_xs,
                               vector<Real8>&          mid_mu_int,  vector<Real8>&          mid_xs_int );
      void    add_xs_at_each_ene_out_grid
                ( vector<Real8>&          new_ene_out,      vector<Real8>&          new_xs_tot,
                  vector<vector<Real8> >& new_mu,           vector<vector<Real8> >& new_xs,
                  vector<vector<Real8> >& new_mu_int,       vector<vector<Real8> >& new_xs_int,
                  vector<Real8>&          new_ene_out_part, vector<Real8>&          new_xs_tot_part,
                  vector<vector<Real8> >& new_mu_part,      vector<vector<Real8> >& new_xs_part,
                  vector<vector<Real8> >& new_mu_int_part,  vector<vector<Real8> >& new_xs_int_part );

      //For mu = cos(theta)
      void    linearize_incoherent_inelastic_scatter_mu(Real8& ene_in_data, Real8& ene_out_data,
                                                        Real8& xs_data_tot,
                                                        vector<Real8>& mu_data, vector<Real8>& xs_data,
                                                        vector<Real8>& mu_data_int, vector<Real8>& xs_data_int);
      Integer check_mu_grid( Real8& mu_pre, Real8& mu_cur, Real8& xs_pre, Real8& xs_cur,
                             Real8& mid_xs, Real8& min_xs_val );
      void    insert_middle_mu_grid( int& ele_no, vector<Real8>& mu_data, vector<Real8>& xs_data,
                                     Real8& mid_mu, Real8& mid_xs );
      void    add_xs_at_each_mu_grid( vector<Real8>& new_mu, vector<Real8>& new_xs,
                                      vector<Real8>& new_mu_part, vector<Real8>& new_xs_part );
      void    integrate_xs_at_mu_grid( vector<Real8>& mu_data,     vector<Real8>& xs_data,
                                       vector<Real8>& mu_data_int, vector<Real8>& xs_data_int );
      void    integrate_xs_at_mu_grid_with_weight_mu( vector<Real8>& mu_data,     vector<Real8>& xs_data,
                                                      vector<Real8>& mu_data_int, vector<Real8>& xs_data_int );

      //For calculation of incoherent inelastic scatter cross section
      void    calc_incoherent_inelastic_scatter(Real8& ene_in_data, Real8& ene_out_data, Real8& mu_data,
                                                Real8& xs_data);
      void    calc_alpha_beta(Real8& ene_in_data, Real8& ene_out_data, Real8& mu_data,
                              Real8& temp_tsl_ev_inv_data, Real8& mass_inv_data,
                              Real8& alpha_data, Real8& beta_data);
      void    calc_beta(Real8& ene_in_data, Real8& ene_out_data, Real8& temp_tsl_ev_inv_data,
                        Real8& beta_data);
      Integer check_alpha_beta_data(Real8& alpha_data, Real8& beta_data);
      Real8   calc_sab(Real8& alpha_data, Real8& beta_data, Real8& mass_inv_data);
      Real8   quadratic_interpolation(Real8& x_val,
                                    Real8& x1, Real8& y1, Real8& x2, Real8& y2, Real8& x3, Real8& y3);

      void preparation_for_incoherent_inerastic_scatter();
      void check_set_data();

      void search_sab_temp();
      void set_sab_data();
      void set_sab_data_arbitrary_temperature();
      void set_beta_max();
      void set_alpha_max_and_min();
      void modify_sab_data();

      void set_temp_tsl_ev(Real8 temp_val);

      void search_temp_eff();
      void calc_bound_scattering_xs();

      void comp_scat_xs_tot();

      virtual void set_energy_grid();

    public:
      //constructor
      IncoherentInelasticScatterCalculator(void);

      //destructor
      virtual ~IncoherentInelasticScatterCalculator(void);

      static const int no_calc            =  0;
      static const int free_gas_mode      =  1;
      static const int use_nucl_data      =  2;

      static const int use_nucl_ene_grid  =  1;
      static const int linearize_ene_grid =  2;

      vector<Real8> ene_in_incoherent_inelastic;

      void clear();

      virtual void calc_incoherent_inelastic_scatter();


      //For calculation of scat_xs_tot
      void calc_scat_xs_tot_with_free_gas_mode(frendy::NuclearDataObject& data_obj,
                                               vector<Real>& ein_vec, vector<Real>& xs_vec_tot);

      void merge_energy_grid(vector<Real>& ene_grid_base, vector<Real>& ene_grid_add);

      void output_ene_out_grid(Real8 ene_in_data, vector<Real> ene_out_data);

      //Setter
      void set_ene_grid_flg(int int_val);
      void set_nucl_data_obj(frendy::NuclearDataObject& data_obj);
      void set_opt_inelastic(Integer& int_data);
      void set_bin_no(Integer& int_data);
      void set_atom_no(Integer& int_data);
      void set_err(Real8& real_data);
      void set_ene_max(Real8& real_data);
      void set_temp(Real8& real_data);

      //Getter
      int                               get_ene_grid_flg();
      virtual frendy::NuclearDataObject get_nucl_data_obj();
      Integer                           get_opt_inelastic();
      Integer                           get_bin_no();
      Integer                           get_atom_no();
      Real8                             get_err();
      Real8                             get_ene_max();
      Real8                             get_temp();
  };
}

#endif //INCOHERENT_INELASTIC_SCATTER_CALCULATOR_H
