#ifndef NON_RESONANCE_ENERGY_GRID_LINEARIZER_H
#define NON_RESONANCE_ENERGY_GRID_LINEARIZER_H

#include "Config/CommonData.hpp"
#include "CommonUtils/DigitAdjuster.hpp"
#include "CommonUtils/TabInterpolator.hpp"
#include "CommonUtils/TabAdjuster.hpp"
#include "NuclearDataUtils/NuclearDataObject.hpp"
#include "NuclearDataUtils/OtherUtils/CrossSectionCalculator.hpp"

namespace frendy
{
  class NonResonanceEnergyGridLinearizer
  {
    private:
      frendy::ErrorManager           err_obj;
      frendy::DigitAdjuster          digit_obj;
      frendy::VectorClearer          clr_vec;
      frendy::TabInterpolator        ti_obj;
      frendy::TabAdjuster            ta_obj;
      frendy::CrossSectionCalculator xs_calc_obj;

#ifdef DEBUG_MODE
  public:
#endif
      Integer add_non_reso_grid_flg;

      static const Real8 min_value; //= 1.0e-50; //If a<min_value, a can be consider 0.0.
      static const Real8 min_distance;

      vector<Real8>   non_reso_grid, specified_grid;
      Real8           error_value, error_int_value;

      Integer         inela_tot_flg, fis_flg, photo_abs_flg;
      Real8           reso_el, reso_eh, unreso_eh;

      vector<vector<Integer> > linearize_file_list;

      frendy::NuclearDataObject                       nucl_data_obj;
      frendy::NuclearReactionDataContainer            nucl_reaction_data_obj;
      vector<frendy::CrossSectionDataContainer>       xs_data_obj;
      vector<frendy::RadioactiveProductDataContainer> radio_product_data_obj;
      vector<frendy::PhotonDataContainer>             photon_data_obj;

      void add_non_resonance_grid();
      void add_non_resonance_grid_xs_data(int i, Integer mt_no);
      void add_non_resonance_grid_radio_product_data(int i, Integer mt_no);
      void add_non_resonance_grid_photon_data(int i, Integer mt_no);

      void add_energy_grid_without_resolved_resonance_region
                          (vector<Real8>&   base_grid, 
                           vector<Integer>& xs_nbt_data, vector<Integer>& xs_int_data,
                           vector<Real>&    xs_ene_data, vector<Real>&    xs_data, Real& qi);
      void add_energy_grid(vector<Real8>&   base_grid, 
                           vector<Integer>& xs_nbt_data, vector<Integer>& xs_int_data,
                           vector<Real>&    xs_ene_data, vector<Real>&    xs_data, Real& qi);
      void add_energy_grid(vector<Real8>&   base_grid, 
                           vector<Integer>& xs_nbt_data,    vector<Integer>& xs_int_data,
                           vector<Real>&    xs_ene_data,    vector<Real>&    xs_data,
                           Real& qi,
                           vector<Integer>& multi_nbt_data, vector<Integer>& multi_int_data,
                           vector<Real>&    multi_ene_data, vector<Real>&    multi_data);

      void linealize_xs_data(vector<Integer>& xs_nbt_data,    vector<Integer>& xs_int_data,
                             vector<Real>&    xs_ene_data,    vector<Real>&    xs_data,
                             Real& qi,
                             vector<Integer>& multi_nbt_data, vector<Integer>& multi_int_data,
                             vector<Real>&    multi_ene_data, vector<Real>&    multi_data);

      void adjust_energy_grid(vector<Integer>& xs_nbt_data,    vector<Integer>& xs_int_data,
                              vector<Real8>&   xs_ene_data,    vector<Real8>&   xs_data,
                              Real&            threshold);
      void calc_threshold(Real8& threshold, Real& qi, Integer& q_flg);

      void add_additional_energy_grid(vector<Integer>& xs_nbt_data,    vector<Integer>& xs_int_data,
                                      vector<Real8>&   xs_ene_data,    vector<Real8>&   xs_data,
                                      Real&            threshold);
      void add_user_specified_energy_grid(vector<Integer>& xs_nbt_data,    vector<Integer>& xs_int_data,
                                          vector<Real8>&   xs_ene_data,    vector<Real8>&   xs_data,
                                          Real&            threshold);

      void add_middle_energy_grid(vector<Integer>& xs_nbt_data,    vector<Integer>& xs_int_data,
                                  vector<Real8>&   xs_ene_data,    vector<Real8>&   xs_data,
                                  Real&            threshold);
      void add_middle_energy_grid(vector<Integer>& xs_nbt_data,    vector<Integer>& xs_int_data,
                                  vector<Real8>&   xs_ene_data,    vector<Real8>&   xs_data,
                                  vector<Integer>& multi_nbt_data, vector<Integer>& multi_int_data,
                                  vector<Real8>&   multi_ene_data, vector<Real8>&   multi_data,
                                  Real&            threshold);

      Integer comp_interpolation_value(int& ele_no, Integer& int_val,
                                       vector<Real8>& ene_data, vector<Real8>& xs_data,
                                       Real8& mid_ene, Real8& mid_xs, Real8& err_line, Real& threshold);
      Integer comp_interpolation_value(int& ele_no, Integer& int_val,
                                       vector<Real8>& ene_data, vector<Real8>& xs_data,
                                       vector<Integer>& multi_nbt_data, vector<Integer>& multi_int_data,
                                       vector<Real8>&   multi_ene_data, vector<Real8>&   multi_data,
                                       Real8& mid_ene, Real8& mid_xs, Real8& err_line, Real& threshold);
      void insert_middle_energy_grid(int& ele_no, Integer& int_val, 
                                     vector<Real8>& ene_data, vector<Real8>& xs_data,
                                     Real8& mid_ene, Real8& mid_xs);
      void add_xs_at_each_grid(vector<Real8>& new_ene,      vector<Real8>& new_xs, 
                               vector<Real8>& new_ene_part, vector<Real8>& new_xs_part);

      void renewal_interpolation_scheme_list(vector<Integer>& nbt_data, vector<Integer>& int_data,
                                             vector<Real8>& ene_data,   vector<Real8>& new_ene);
    
      void read_resonance_upper_limit();
      void input_data_check();

    public:
      //constructor
      NonResonanceEnergyGridLinearizer(void);

      //destructor
      virtual ~NonResonanceEnergyGridLinearizer(void);

      void clear();

      void add_radio_product_data(frendy::CrossSectionDataContainer&       xs_obj,
                                  frendy::RadioactiveProductDataContainer& rad_obj);

      Integer check_mf_mt(Integer mf, Integer mt,
                          Integer inela_tot_val, Integer fis_val, Integer photo_abs_val);

      void set_err(Real8 real_val);
      void set_err_int(Real8 real_val);
      void set_user_specified_grid(vector<Real8> real_vec);
      void set_nucl_data_obj(frendy::NuclearDataObject& data_obj);

      vector<Real8>            get_non_resonance_grid();
      vector<Real8>            get_user_specified_grid();
      Real8                    get_err();
      Real8                    get_err_int();
      Real8                    get_reso_eh();
      Real8                    get_unreso_eh();

      vector<vector<Integer> > get_linearize_file_list();

      frendy::NuclearDataObject             get_nucl_data_obj();
      frendy::NuclearReactionDataContainer  get_nucl_reaction_data_obj();
  };
}

#endif // NON_RESONANCE_ENERGY_GRID_LINEARIZER_H
