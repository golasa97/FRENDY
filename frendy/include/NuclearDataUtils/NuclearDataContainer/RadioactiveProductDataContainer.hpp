#ifndef RADIOACTIVE_PRODUCT_DATA_CONTAINER_H
#define RADIOACTIVE_PRODUCT_DATA_CONTAINER_H

#include "CommonUtils/ErrorManager.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class RadioactiveProductDataContainer
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

      Integer                  reaction_type;
      vector<Real>             mat_data_produced;
      vector<Integer>          contain_data_list;
      Integer                  state_no_target;
      Integer                  state_no_target_iso;
      vector<Integer>          state_no_product;
      vector<Real>             excitation_ene;
      Integer                  decay_chain_flg;
      vector<vector<Real> >    half_life;
      vector<vector<Real> >    decay_type;
      vector<vector<Real> >    mat_data_daughter;
      vector<vector<Real> >    branching_ratio_daughter;
      vector<vector<Real> >    endpoint_ene_daughter;
      vector<vector<Real> >    chain_terminator_daughter;
      Integer                  multiplicity_state_no_target;
      vector<Integer>          multiplicity_state_no_product;
      vector<Real>             multiplicity_q_value_mass;
      vector<Real>             multiplicity_q_value;
      vector<Integer>          multiplicity_mat_data_product;
      vector<vector<Integer> > multiplicity_int_data;
      vector<vector<Integer> > multiplicity_range_data;
      vector<vector<Real> >    multiplicity_ene_data;
      vector<vector<Real> >    multiplicity_data;
      Integer                  xs_state_no_target;
      vector<Integer>          xs_state_no_product;
      vector<Real>             xs_q_value_mass;
      vector<Real>             xs_q_value;
      vector<Integer>          xs_mat_data_product;
      vector<vector<Integer> > xs_int_data;
      vector<vector<Integer> > xs_range_data;
      vector<vector<Real> >    xs_ene_data;
      vector<vector<Real> >    xs_data;

    public:
      //constructor
      RadioactiveProductDataContainer(void);

      //destructor
      virtual ~RadioactiveProductDataContainer(void);

      void clear();

      //Getter
      Integer                  get_reaction_type();
      vector<Real>             get_mat_data_produced();
      vector<Integer>          get_contain_data_list();
      Integer                  get_state_no_target();
      Integer                  get_state_no_target_iso();
      vector<Integer>          get_state_no_product();
      vector<Real>             get_excitation_ene();
      Integer                  get_decay_chain_flg();
      vector<vector<Real> >    get_half_life();
      vector<vector<Real> >    get_decay_type();
      vector<vector<Real> >    get_mat_data_daughter();
      vector<vector<Real> >    get_branching_ratio_daughter();
      vector<vector<Real> >    get_endpoint_ene_daughter();
      vector<vector<Real> >    get_chain_terminator_daughter();
      Integer                  get_multiplicity_state_no_target();
      vector<Integer>          get_multiplicity_state_no_product();
      vector<Real>             get_multiplicity_q_value_mass();
      vector<Real>             get_multiplicity_q_value();
      vector<Integer>          get_multiplicity_mat_data_product();
      vector<vector<Integer> > get_multiplicity_int_data();
      vector<vector<Integer> > get_multiplicity_range_data();
      vector<vector<Real> >    get_multiplicity_ene_data();
      vector<vector<Real> >    get_multiplicity_data();
      Integer                  get_xs_state_no_target();
      vector<Integer>          get_xs_state_no_product();
      vector<Real>             get_xs_q_value_mass();
      vector<Real>             get_xs_q_value();
      vector<Integer>          get_xs_mat_data_product();
      vector<vector<Integer> > get_xs_int_data();
      vector<vector<Integer> > get_xs_range_data();
      vector<vector<Real> >    get_xs_ene_data();
      vector<vector<Real> >    get_xs_data();

      //Setter
      void set_reaction_type( Integer int_data );
      void set_mat_data_produced( vector<Real> real_vec );
      void set_contain_data_list( vector<Integer> int_vec );
      void set_state_no_target( Integer int_data );
      void set_state_no_target_iso( Integer int_data );
      void set_state_no_product( vector<Integer> int_vec );
      void set_excitation_ene( vector<Real> real_vec );
      void set_decay_chain_flg( Integer int_data );
      void set_half_life( vector<vector<Real> > real_vec );
      void set_decay_type( vector<vector<Real> > real_vec );
      void set_mat_data_daughter( vector<vector<Real> > real_vec );
      void set_branching_ratio_daughter( vector<vector<Real> > real_vec );
      void set_endpoint_ene_daughter( vector<vector<Real> > real_vec );
      void set_chain_terminator_daughter( vector<vector<Real> > real_vec );
      void set_multiplicity_state_no_target( Integer int_data );
      void set_multiplicity_state_no_product( vector<Integer> int_vec );
      void set_multiplicity_q_value_mass( vector<Real> real_vec );
      void set_multiplicity_q_value( vector<Real> real_vec );
      void set_multiplicity_mat_data_product( vector<Integer> int_vec );
      void set_multiplicity_int_data( vector<vector<Integer> > int_vec );
      void set_multiplicity_range_data( vector<vector<Integer> > int_vec );
      void set_multiplicity_ene_data( vector<vector<Real> > real_vec );
      void set_multiplicity_data( vector<vector<Real> > real_vec );
      void set_xs_state_no_target( Integer int_data );
      void set_xs_state_no_product( vector<Integer> int_vec );
      void set_xs_q_value_mass( vector<Real> real_vec );
      void set_xs_q_value( vector<Real> real_vec );
      void set_xs_mat_data_product( vector<Integer> int_vec );
      void set_xs_int_data( vector<vector<Integer> > int_vec );
      void set_xs_range_data( vector<vector<Integer> > int_vec );
      void set_xs_ene_data( vector<vector<Real> > real_vec );
      void set_xs_data( vector<vector<Real> > real_vec );
  };
}

#endif //RADIOACTIVE_PRODUCT_DATA_CONTAINER_H
