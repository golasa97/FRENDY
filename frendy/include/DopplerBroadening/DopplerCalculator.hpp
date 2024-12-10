#ifndef DOPPLER_CALCULATOR_H
#define DOPPLER_CALCULATOR_H

#include "CommonUtils/TabAdjuster.hpp"
#include "NuclearDataUtils/OtherUtils/NuclearDataObjectUtils.hpp"
#include "DopplerBroadening/BroadenedXSCalculatorWithNjoyFormula.hpp"

namespace frendy
{
  class DopplerCalculator
  {
    private:
      static const Real8 min_distance; //= 1.0e-7;
      static const Real8 max_ratio;    //= 3.0;
      static const int   mt_mod_coef = 100000;
      
      frendy::ErrorManager            err_obj;
      frendy::VectorClearer           clr_obj;
      frendy::VectorCopier            cp_vec;
      frendy::TabInterpolator         ti_obj;
      frendy::TabAdjuster             ta_obj;
      frendy::DigitAdjuster           digit_obj;
      frendy::NuclearDataObjectUtils  nucl_util_obj;

#ifdef NJOY_MODE
      frendy::BroadenedXSCalculatorWithNjoyFormula calc_xs_obj;
#else
      frendy::BroadenedXSCalculator calc_xs_obj;
#endif

#ifdef DEBUG_MODE
  public:
#endif

      Integer calc_doppler_flg, nucl_data_set_flg;

      frendy::NuclearDataObject                  nucl_data_obj, nucl_data_obj_base;
      vector<frendy::CrossSectionDataContainer>  xs_data_obj;

      Real8 temp_ori, temp_dop, temp_dif, temp_nucl;
      Real8 error_value, error_max_value, error_int_value;
      Real8 dop_ene_max_inp, dop_ene_max_cal;

      void    check_set_data();
      void    check_int_scheme(vector<frendy::CrossSectionDataContainer>& xs_data_obj_ori);
      void    search_dop_ene_max();
      
      void    calc_doppler_effect();
      void    calc_doppler_effect_reaction_xs(vector<CrossSectionDataContainer>& xs_data_obj_ori);
      void    calc_doppler_effect_radio_product_xs();
      void    calc_doppler_effect_photon_production_xs();
      void    calc_doppler_effect_photon_interaction_xs();

      frendy::CrossSectionDataContainer generate_xs_data_obj
                                          (Integer reaction_type, Real q_val_mass, Real q_val, 
                                           vector<Integer> xs_range_data, vector<Integer> xs_int_data,
                                           vector<Real>    xs_ene_data,   vector<Real>    xs_data);

      void    calc_doppler_effect_each_group(vector<frendy::CrossSectionDataContainer>& xs_data_obj_part);
      
      void    grouping_xs_data(vector<frendy::CrossSectionDataContainer>&          xs_data_obj_ori,
                               vector<vector<frendy::CrossSectionDataContainer> >& xs_data_obj_part);
      void    merge_xs_data(vector<frendy::CrossSectionDataContainer>&          xs_data_obj_ori,
                            vector<vector<frendy::CrossSectionDataContainer> >& xs_data_obj_part);
      void    modify_broadened_xs(frendy::CrossSectionDataContainer& xs_data_obj_ori,
                                  frendy::CrossSectionDataContainer& xs_data_obj_dop);
      void    unify_energy_grid(vector<frendy::CrossSectionDataContainer>& xs_data_obj_part);
      void    modify_xs_to_adapt_unify_energy_grid( vector<Real8>& unify_grid, 
                                                    vector<Real8>& ene_data, vector<Real8>& sig_data );
      
      void    remove_unnecessary_energy_grid(vector<Real8>& ene_data, vector<vector<Real8> >& sig_data);
      void    add_middle_energy_grid(vector<Real8>& ene_data, vector<vector<Real8> >& sig_data);
      Integer check_energy_grid_distance(Real8& ene_pre_pre, Real8& ene_pre, Real8& ene_cur,
                                         vector<Real8>& sig_pre, vector<Real8>& sig_cur,
                                         Real8& mid_ene, vector<Real8>& mid_sig);
      void    insert_middle_energy_grid( int& ele_no, vector<Real8>& ene_data, vector<vector<Real8> >& sig_data,
                                         Real8& mid_ene, vector<Real8>& mid_sig);
      void    add_xs_at_each_grid( vector<Real8>& new_ene,      vector<vector<Real8> >& new_sig, 
                                   vector<Real8>& new_ene_part, vector<vector<Real8> >& new_sig_part );

    public:
      //constructor
      DopplerCalculator(void);

      //destructor
      virtual ~DopplerCalculator(void);

      void calc_doppler();
      void output_set_data_information();

      void clear();
      void clear_parser();
      
      //Setter
      void set_nucl_data_obj_base(frendy::NuclearDataObject& data_obj);
      void set_nucl_data_obj(frendy::NuclearDataObject& data_obj);
      void set_temp_ori(Real8 real_val);
      void set_temp_dop(Real8 real_val);
      void set_err(Real8 real_val);
      void set_err_max(Real8 real_val);
      void set_err_int(Real8 real_val);
      void set_dop_ene_max(Real8 real_val);
      
      //Getter
      Real8                      get_temp_ori();
      Real8                      get_temp_dop();
      Real8                      get_err();
      Real8                      get_err_max();
      Real8                      get_err_int();
      Real8                      get_dop_ene_max();
      frendy::NuclearDataObject  get_nucl_data_obj_base();
      frendy::NuclearDataObject  get_nucl_data_obj();
  };
}

#endif //DOPPLER_CALCULATOR_H
