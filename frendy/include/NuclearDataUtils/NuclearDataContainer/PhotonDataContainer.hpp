#ifndef PHOTON_DATA_CONTAINER_H
#define PHOTON_DATA_CONTAINER_H

#include "CommonUtils/ErrorManager.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class PhotonDataContainer
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

      Integer                           reaction_type;
      vector<Real>                      multiplicity_ene_level;
      vector<Real>                      multiplicity_binding_ene;
      vector<Integer>                   multiplicity_tot_int_data;
      vector<Integer>                   multiplicity_tot_range_data;
      vector<Real>                      multiplicity_tot_ene_data;
      vector<Real>                      multiplicity_tot_data;
      vector<vector<Integer> >          multiplicity_int_data;
      vector<vector<Integer> >          multiplicity_range_data;
      vector<vector<Real> >             multiplicity_ene_data;
      vector<vector<Real> >             multiplicity_data;
      vector<Integer>                   multiplicity_binding_ene_flg;
      vector<Integer>                   multiplicity_distr_law_no;
      Integer                           level_no_max;
      Integer                           trans_photon_ene_flg;
      Real                              ene_level_max;
      vector<Real>                      trans_ene_level;
      vector<Real>                      direct_trans_probability;
      vector<Real>                      photon_trans_probability;
      Integer                           ene_level_no;
      vector<Real>                      photon_ene;
      vector<Real>                      binding_ene;
      vector<Integer>                   binding_ene_flg;
      vector<Integer>                   distr_law_no;
      vector<Integer>                   photon_production_xs_tot_int_data;
      vector<Integer>                   photon_production_xs_tot_range_data;
      vector<Real>                      photon_production_xs_tot_ene_data;
      vector<Real>                      photon_production_xs_tot_data;
      vector<vector<Integer> >          photon_production_xs_int_data;
      vector<vector<Integer> >          photon_production_xs_range_data;
      vector<vector<Real> >             photon_production_xs_ene_data;
      vector<vector<Real> >             photon_production_xs_data;
      Integer                           isotropic_flg;
      Integer                           angular_repr_flg;
      Integer                           iso_photon_angular_no;
      vector<Real>                      angular_ene_level;
      vector<Real>                      angular_photon_ene;
      vector<vector<Integer> >          angular_ene_int_data;
      vector<vector<Integer> >          angular_ene_range_data;
      vector<vector<Real> >             angular_ene_data;
      vector<vector<vector<Real> > >    angular_legendre_coef_data;
      vector<vector<vector<Integer> > > angular_probability_int_data;
      vector<vector<vector<Integer> > > angular_probability_range_data;
      vector<vector<vector<Real> > >    angular_probability_cos_data;
      vector<vector<vector<Real> > >    angular_probability_data;
      vector<Integer>                   ene_distr_law_no;
      vector<vector<Integer> >          ene_distr_weight_int_data;
      vector<vector<Integer> >          ene_distr_weight_range_data;
      vector<vector<Real> >             ene_distr_weight_ene_data;
      vector<vector<Real> >             ene_distr_weight_data;
      vector<vector<Integer> >          ene_distr_int_data;
      vector<vector<Integer> >          ene_distr_range_data;
      vector<vector<Real> >             incident_ene;
      vector<vector<vector<Integer> > > ene_distr_nomalized_int_data;
      vector<vector<vector<Integer> > > ene_distr_nomalized_range_data;
      vector<vector<vector<Real> > >    ene_distr_nomalized_ene_data;
      vector<vector<vector<Real> > >    ene_distr_nomalized_data;
      Real                              binding_ene_subshell;
      Real                              fluorescence_yield;
      vector<Integer>                   photon_interaction_xs_int_data;
      vector<Integer>                   photon_interaction_xs_range_data;
      vector<Real>                      photon_interaction_xs_ene_data;
      vector<Real>                      photon_interaction_xs_data;

    public:
      //constructor
      PhotonDataContainer(void);

      //destructor
      virtual ~PhotonDataContainer(void);

      void clear();

      //Getter
      Integer                           get_reaction_type();
      vector<Real>                      get_multiplicity_ene_level();
      vector<Real>                      get_multiplicity_binding_ene();
      vector<Integer>                   get_multiplicity_tot_int_data();
      vector<Integer>                   get_multiplicity_tot_range_data();
      vector<Real>                      get_multiplicity_tot_ene_data();
      vector<Real>                      get_multiplicity_tot_data();
      vector<vector<Integer> >          get_multiplicity_int_data();
      vector<vector<Integer> >          get_multiplicity_range_data();
      vector<vector<Real> >             get_multiplicity_ene_data();
      vector<vector<Real> >             get_multiplicity_data();
      vector<Integer>                   get_multiplicity_binding_ene_flg();
      vector<Integer>                   get_multiplicity_distr_law_no();
      Integer                           get_level_no_max();
      Integer                           get_trans_photon_ene_flg();
      Real                              get_ene_level_max();
      vector<Real>                      get_trans_ene_level();
      vector<Real>                      get_direct_trans_probability();
      vector<Real>                      get_photon_trans_probability();
      Integer                           get_ene_level_no();
      vector<Real>                      get_photon_ene();
      vector<Real>                      get_binding_ene();
      vector<Integer>                   get_binding_ene_flg();
      vector<Integer>                   get_distr_law_no();
      vector<Integer>                   get_photon_production_xs_tot_int_data();
      vector<Integer>                   get_photon_production_xs_tot_range_data();
      vector<Real>                      get_photon_production_xs_tot_ene_data();
      vector<Real>                      get_photon_production_xs_tot_data();
      vector<vector<Integer> >          get_photon_production_xs_int_data();
      vector<vector<Integer> >          get_photon_production_xs_range_data();
      vector<vector<Real> >             get_photon_production_xs_ene_data();
      vector<vector<Real> >             get_photon_production_xs_data();
      Integer                           get_isotropic_flg();
      Integer                           get_angular_repr_flg();
      Integer                           get_iso_photon_angular_no();
      vector<Real>                      get_angular_ene_level();
      vector<Real>                      get_angular_photon_ene();
      vector<vector<Integer> >          get_angular_ene_int_data();
      vector<vector<Integer> >          get_angular_ene_range_data();
      vector<vector<Real> >             get_angular_ene_data();
      vector<vector<vector<Real> > >    get_angular_legendre_coef_data();
      vector<vector<vector<Integer> > > get_angular_probability_int_data();
      vector<vector<vector<Integer> > > get_angular_probability_range_data();
      vector<vector<vector<Real> > >    get_angular_probability_cos_data();
      vector<vector<vector<Real> > >    get_angular_probability_data();
      vector<Integer>                   get_ene_distr_law_no();
      vector<vector<Integer> >          get_ene_distr_weight_int_data();
      vector<vector<Integer> >          get_ene_distr_weight_range_data();
      vector<vector<Real> >             get_ene_distr_weight_ene_data();
      vector<vector<Real> >             get_ene_distr_weight_data();
      vector<vector<Integer> >          get_ene_distr_int_data();
      vector<vector<Integer> >          get_ene_distr_range_data();
      vector<vector<Real> >             get_incident_ene();
      vector<vector<vector<Integer> > > get_ene_distr_nomalized_int_data();
      vector<vector<vector<Integer> > > get_ene_distr_nomalized_range_data();
      vector<vector<vector<Real> > >    get_ene_distr_nomalized_ene_data();
      vector<vector<vector<Real> > >    get_ene_distr_nomalized_data();
      Real                              get_binding_ene_subshell();
      Real                              get_fluorescence_yield();
      vector<Integer>                   get_photon_interaction_xs_int_data();
      vector<Integer>                   get_photon_interaction_xs_range_data();
      vector<Real>                      get_photon_interaction_xs_ene_data();
      vector<Real>                      get_photon_interaction_xs_data();

      //Setter
      void set_reaction_type( Integer int_data );
      void set_multiplicity_ene_level( vector<Real> real_vec );
      void set_multiplicity_binding_ene( vector<Real> real_vec );
      void set_multiplicity_tot_int_data( vector<Integer> int_vec );
      void set_multiplicity_tot_range_data( vector<Integer> int_vec );
      void set_multiplicity_tot_ene_data( vector<Real> real_vec );
      void set_multiplicity_tot_data( vector<Real> real_vec );
      void set_multiplicity_int_data( vector<vector<Integer> > int_vec );
      void set_multiplicity_range_data( vector<vector<Integer> > int_vec );
      void set_multiplicity_ene_data( vector<vector<Real> > real_vec );
      void set_multiplicity_data( vector<vector<Real> > real_vec );
      void set_multiplicity_binding_ene_flg( vector<Integer> int_vec );
      void set_multiplicity_distr_law_no( vector<Integer> int_vec );
      void set_level_no_max( Integer int_data );
      void set_trans_photon_ene_flg( Integer int_data );
      void set_ene_level_max( Real real_data );
      void set_trans_ene_level( vector<Real> real_vec );
      void set_direct_trans_probability( vector<Real> real_vec );
      void set_photon_trans_probability( vector<Real> real_vec );
      void set_ene_level_no( Integer int_data );
      void set_photon_ene( vector<Real> real_vec );
      void set_binding_ene( vector<Real> real_vec );
      void set_binding_ene_flg( vector<Integer> int_vec );
      void set_distr_law_no( vector<Integer> int_vec );
      void set_photon_production_xs_tot_int_data( vector<Integer> int_vec );
      void set_photon_production_xs_tot_range_data( vector<Integer> int_vec );
      void set_photon_production_xs_tot_ene_data( vector<Real> real_vec );
      void set_photon_production_xs_tot_data( vector<Real> real_vec );
      void set_photon_production_xs_int_data( vector<vector<Integer> > int_vec );
      void set_photon_production_xs_range_data( vector<vector<Integer> > int_vec );
      void set_photon_production_xs_ene_data( vector<vector<Real> > real_vec );
      void set_photon_production_xs_data( vector<vector<Real> > real_vec );
      void set_isotropic_flg( Integer int_data );
      void set_angular_repr_flg( Integer int_data );
      void set_iso_photon_angular_no( Integer int_data );
      void set_angular_ene_level( vector<Real> real_vec );
      void set_angular_photon_ene( vector<Real> real_vec );
      void set_angular_ene_int_data( vector<vector<Integer> > int_vec );
      void set_angular_ene_range_data( vector<vector<Integer> > int_vec );
      void set_angular_ene_data( vector<vector<Real> > real_vec );
      void set_angular_legendre_coef_data( vector<vector<vector<Real> > > real_vec );
      void set_angular_probability_int_data( vector<vector<vector<Integer> > > int_vec );
      void set_angular_probability_range_data( vector<vector<vector<Integer> > > int_vec );
      void set_angular_probability_cos_data( vector<vector<vector<Real> > > real_vec );
      void set_angular_probability_data( vector<vector<vector<Real> > > real_vec );
      void set_ene_distr_law_no( vector<Integer> int_vec );
      void set_ene_distr_weight_int_data( vector<vector<Integer> > int_vec );
      void set_ene_distr_weight_range_data( vector<vector<Integer> > int_vec );
      void set_ene_distr_weight_ene_data( vector<vector<Real> > real_vec );
      void set_ene_distr_weight_data( vector<vector<Real> > real_vec );
      void set_ene_distr_int_data( vector<vector<Integer> > int_vec );
      void set_ene_distr_range_data( vector<vector<Integer> > int_vec );
      void set_incident_ene( vector<vector<Real> > real_vec );
      void set_ene_distr_nomalized_int_data( vector<vector<vector<Integer> > > int_vec );
      void set_ene_distr_nomalized_range_data( vector<vector<vector<Integer> > > int_vec );
      void set_ene_distr_nomalized_ene_data( vector<vector<vector<Real> > > real_vec );
      void set_ene_distr_nomalized_data( vector<vector<vector<Real> > > real_vec );
      void set_binding_ene_subshell( Real real_data );
      void set_fluorescence_yield( Real real_data );
      void set_photon_interaction_xs_int_data( vector<Integer> int_vec );
      void set_photon_interaction_xs_range_data( vector<Integer> int_vec );
      void set_photon_interaction_xs_ene_data( vector<Real> real_vec );
      void set_photon_interaction_xs_data( vector<Real> real_vec );
  };
}

#endif //PHOTON_DATA_CONTAINER_H
