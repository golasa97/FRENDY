#ifndef RECONSTRUCT_XS_MERGER_H
#define RECONSTRUCT_XS_MERGER_H

#include "ReconResonance/NonResonanceEnergyGridLinearizer.hpp"
#include "CommonUtils/TabAdjuster.hpp"

namespace frendy
{
  class ReconstructXSMerger
  {
    private:
      frendy::ErrorManager    err_obj;
      frendy::VectorClearer   clr_obj;
      frendy::TabInterpolator ti_obj;
      frendy::DigitAdjuster   digit_obj;
      frendy::TabAdjuster     ta_obj;
      
#ifdef DEBUG_MODE
  public:
#endif
      frendy::NuclearDataObject             nucl_data_obj;
      frendy::NuclearReactionDataContainer  nucl_reaction_data_obj;

      int                    reaction_type_no;
      vector<Integer>        reaction_type;

      vector<vector<Real8> > sig_merge;
      vector<Real8>          ene_merge;
      
      vector<Real8>                            ene_non_reso;
      vector<vector<vector<vector<Real8> > > > sig_reso;
      vector<vector<vector<Real8> > >          ene_reso;
      vector<Real8>                            ene_reso_uni;
      vector<vector<Real8> >                   sig_reso_uni;

      //For R-matrix limited
      vector<Integer>                          react_type_list_reso_uni;
      vector<vector<vector<Integer> > >        react_type_list_reso;
      vector<Real8>                            q_val_reso_uni;
      vector<vector<vector<Real8> > >          q_val_reso;

      Integer merge_xs_flg;
      Integer nucl_data_flg, reso_grid_flg, reso_xs_flg, non_reso_grid_flg;
      Integer proton_xs_min, proton_xs_max, deuteron_xs_min, deuteron_xs_max, triton_xs_min, triton_xs_max,
              he_xs_min, he_xs_max, alpha_xs_min, alpha_xs_max;

      Integer reso_flg;
      Integer inelastic_scat_xs_flg,   fission_xs_flg,
              proton_xs_flg, deuteron_xs_flg, triton_xs_flg, he_xs_flg, alpha_xs_flg,
              photon_interaction_xs_flg, photoelectric_xs_flg;

      void merge_non_reso_and_reso_xs();
      void get_base_grid();
      void calc_non_reso_xs_on_unified_grid();
      void calc_non_reso_xs( vector<Real8>&   sig_data,
                             vector<Integer>& nbt_e,    vector<Integer>& int_e, 
                             vector<Real>&    ene_data, vector<Real>&    xs_data );
      void calc_non_reso_xs( int mf_no, vector<Real8>&   sig_data,
                             vector<Integer>& nbt_e,    vector<Integer>& int_e, 
                             vector<Real>&    ene_data, vector<Real>&    xs_data );
      void calc_non_reso_xs( int mf_no, int mt_no, vector<Real8>&   sig_data,
                             vector<Integer>& nbt_e,    vector<Integer>& int_e, 
                             vector<Real>&    ene_data, vector<Real>&    xs_data );
      void add_non_reso_xs(vector<Real8>& sig_tmp, int xs_type);
      void calc_total_inelastic_scat_xs();
      
      void calc_reso_xs_on_unified_grid();
      void add_reso_xs();
      void unify_reso_xs();
      void unify_react_type_list();
      void energy_bound_check(vector<Integer>& ene_chk_el,      vector<Integer>& ene_chk_eh,
                              vector<Real>&    el,              vector<Real>&    eh,
                              vector<Integer>& reso_region_flg, vector<Integer>& self_shielding_flg);
      vector<vector<Real8> > modify_sig_reso_with_unify_react_type_list
                               (vector<vector<Real8> >& sig_data, vector<Integer>& react_type_data);


      void delete_unnecessary_xs();
      void delete_el_and_eh();
      void add_el_and_eh();
      void mod_first_chance_fission_xs();
      void mod_tot_prod_xs();
      void sum_part_xs(frendy::CrossSectionDataContainer& xs_data_obj_tot_prod,
                       frendy::CrossSectionDataContainer& xs_data_obj);
      void comp_tot_prod_xs_and_mod_tot_xs(frendy::CrossSectionDataContainer& xs_data_obj_tot_prod,
                                           frendy::CrossSectionDataContainer& xs_data_obj_tot_prod_ori);
      void mod_non_elastic_xs();
      
      void update_xs_tot_sc_fis_rad();
      void update_each_xs(int xs_type, frendy::CrossSectionDataContainer& data_obj);

      void update_xs_other();
      void check_add_total_reaction( vector<frendy::CrossSectionDataContainer>& xs_data_obj,
                                     vector<int>& add_react_type_pos_reso,
                                     vector<int>& add_react_type_pos_xs_obj );
      void merge_xs_other(int i, frendy::CrossSectionDataContainer& data_obj);
      frendy::CrossSectionDataContainer add_new_xs_data_obj(int i);

      void add_mf10_mt102_data();

      void remove_non_linearize_xs_data();
      int  check_interpolation_type(vector<Integer> int_vec);
      
      void        check_set_data();
      vector<int> check_add_photon_interaction_xs(Integer mt);
      void        check_minus_xs();
      void        check_total_xs_data();

    public:
      //constructor
      ReconstructXSMerger(void);

      //destructor
      virtual ~ReconstructXSMerger(void);
      
      void clear();
      void clear_parser_data();

      vector<int> check_add_xs(Integer mt);

      void set_nucl_data_obj(frendy::NuclearDataObject& data_obj);

      void set_resonance_react_type_list(vector<vector<vector<Integer> > >& int_vec);
      void set_resonance_q_val(vector<vector<vector<Real8> > >& real_vec);

      void set_resonance_grid(vector<vector<vector<Real8> > >& real_vec);
      void set_resonance_xs(vector<vector<vector<vector<Real8> > > >& real_vec);
      void set_non_resonance_grid(vector<Real8>& real_vec);

      frendy::NuclearDataObject                get_nucl_data_obj();

      vector<vector<vector<Integer> > >        get_resonance_react_type_list();
      vector<Integer>                          get_resonance_react_type_list_uni();
      vector<vector<vector<Real8> > >          get_resonance_q_val();
      vector<Real8>                            get_resonance_q_val_uni();

      vector<vector<vector<Real8> > >          get_resonance_grid();
      vector<vector<vector<vector<Real8> > > > get_resonance_xs();
      vector<Real8>                            get_non_resonance_grid();

      vector<vector<Real8> > get_merge_xs();
      vector<Real8>          get_merge_grid();
  };
}

#endif //RECONSTRUCT_XS_MERGER_H
