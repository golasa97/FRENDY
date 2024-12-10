#ifndef PRODUCT_DISTRIBUTION_DATA_CONTAINER_H
#define PRODUCT_DISTRIBUTION_DATA_CONTAINER_H

#include "CommonUtils/ErrorManager.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class ProductDistributionDataContainer
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

      Integer                                    reaction_type;
      Integer                                    prompt_fis_n_flg;
      Integer                                    prompt_fis_p_flg;
      Integer                                    ref_frame_flg;
      vector<Real>                               mat_data_product;
      vector<Real>                               mass_product;
      vector<Integer>                            product_mod_flg;
      vector<Integer>                            distr_func_flg;
      vector<vector<Integer> >                   product_distr_int_data;
      vector<vector<Integer> >                   product_distr_range_data;
      vector<vector<Real> >                      product_distr_ene_data;
      vector<vector<Real> >                      product_distr_data;
      vector<Integer>                            angular_repr_flg;
      vector<Integer>                            second_ene_int_data;
      vector<vector<Integer> >                   cont_int_data;
      vector<vector<Integer> >                   cont_range_data;
      vector<vector<Integer> >                   discrete_ene_no;
      vector<vector<Real> >                      cont_ene_a;
      vector<vector<vector<Real> > >             cont_ene_b;
//      vector<vector<vector<vector<Real> > > >    cont_data;
      vector<vector<Integer> >                   two_body_repr_flg;
      vector<vector<Integer> >                   two_body_int_data;
      vector<vector<Integer> >                   two_body_range_data;
      vector<vector<Real> >                      two_body_ene_data;
      vector<vector<vector<Real> > >             two_body_legendre_coef;
      vector<vector<vector<Real> > >             two_body_cos;
      vector<vector<vector<Real> > >             two_body_prob;
      vector<Real>                               spin_particle;
      vector<Integer>                            charged_particle_flg;
      vector<vector<Integer> >                   charged_particle_repr_flg;
      vector<vector<Real> >                      charged_particle_ene_data;
      vector<vector<Real> >                      charged_particle_mass_data;
      vector<vector<Integer> >                   charged_particle_int_data;
      vector<vector<Integer> >                   charged_particle_range_data;
      vector<vector<vector<Real> > >             charged_particle_coef_b;
      vector<vector<vector<Real> > >             charged_particle_coef_r;
      vector<vector<vector<Real> > >             charged_particle_coef_i;
      vector<vector<vector<Real> > >             charged_particle_coef_c;
      vector<vector<vector<Real> > >             charged_particle_coef_mu;
      vector<vector<vector<Real> > >             charged_particle_coef_p;
      vector<Real>                               n_body_mass;
      vector<Integer>                            n_body_particle_no;
      vector<vector<Real> >                      lab_ene;
      vector<vector<Integer> >                   lab_ene_int_data;
      vector<vector<Integer> >                   lab_ene_range_data;
      vector<vector<vector<Real> > >             lab_cos;
      vector<vector<vector<Integer> > >          lab_integrate_int_data;
      vector<vector<vector<Integer> > >          lab_integrate_range_data;
      vector<vector<vector<Real> > >             lab_integrate_cos_data;
      vector<vector<vector<Real> > >             lab_integrate_data;
      vector<vector<vector<Integer> > >          lab_cos_int_data;
      vector<vector<vector<Integer> > >          lab_cos_range_data;
      vector<vector<vector<vector<Integer> > > > lab_int_data;
      vector<vector<vector<vector<Integer> > > > lab_range_data;
      vector<vector<vector<vector<Real> > > >    lab_ene_sec_data;
      vector<vector<vector<vector<Real> > > >    lab_data;
      vector<Real>                               mat_data_second_product;
      vector<Integer>                            second_distr_func_flg;
      vector<vector<Integer> >                   second_distr_yield_int_data;
      vector<vector<Integer> >                   second_distr_yield_range_data;
      vector<vector<Real> >                      second_distr_yield_ene_data;
      vector<vector<Real> >                      second_distr_yield_data;
      vector<Integer>                            second_distr_angular_repr_flg;
      vector<Integer>                            second_distr_ene_int_data;
      vector<vector<Integer> >                   second_distr_cont_int_data;
      vector<vector<Integer> >                   second_distr_cont_range_data;
      vector<vector<Integer> >                   second_distr_discrete_ene_no;
      vector<vector<Real> >                      second_distr_cont_ene_a;
      vector<vector<vector<Real> > >             second_distr_cont_ene_b;
      vector<vector<vector<vector<Real> > > >    second_distr_cont_data;
      vector<vector<Integer> >                   second_distr_two_body_repr_flg;
      vector<vector<Integer> >                   second_distr_two_body_int_data;
      vector<vector<Integer> >                   second_distr_two_body_range_data;
      vector<vector<Real> >                      second_distr_two_body_ene_data;
      vector<vector<vector<Real> > >             second_distr_two_body_legendre_coef;
      vector<vector<vector<Real> > >             second_distr_two_body_cos;
      vector<vector<vector<Real> > >             second_distr_two_body_prob;
      vector<vector<Integer> >                   second_distr_transfer_int_data;
      vector<vector<Integer> >                   second_distr_transfer_range_data;
      vector<vector<Real> >                      second_distr_transfer_ene_data;
      vector<vector<Real> >                      second_distr_transfer_data;

      Real                            temp;
      vector<Real>                    incident_ene;
      vector<vector<Real> >           second_ene;
      vector<vector<Real> >           incoherent_inelastic_scat_xs_integrate;
      vector<vector<vector<Real> > >  incoherent_inelastic_scat_xs_weight;
      vector<vector<Real> >           incoherent_elastic_scat_angle;
      Integer                         bragg_edge_no;

    public:
      //constructor
      ProductDistributionDataContainer(void);

      //destructor
      virtual ~ProductDistributionDataContainer(void);

      void clear();

      vector<vector<vector<vector<Real> > > >    cont_data; //To reduce calculation time

      //Getter
      Integer                                    get_reaction_type();
      Integer                                    get_prompt_fis_n_flg();
      Integer                                    get_prompt_fis_p_flg();
      Integer                                    get_ref_frame_flg();
      vector<Real>                               get_mat_data_product();
      vector<Real>                               get_mass_product();
      vector<Integer>                            get_product_mod_flg();
      vector<Integer>                            get_distr_func_flg();
      vector<vector<Integer> >                   get_product_distr_int_data();
      vector<vector<Integer> >                   get_product_distr_range_data();
      vector<vector<Real> >                      get_product_distr_ene_data();
      vector<vector<Real> >                      get_product_distr_data();
      vector<Integer>                            get_angular_repr_flg();
      vector<Integer>                            get_second_ene_int_data();
      vector<vector<Integer> >                   get_cont_int_data();
      vector<vector<Integer> >                   get_cont_range_data();
      vector<vector<Integer> >                   get_discrete_ene_no();
      vector<vector<Real> >                      get_cont_ene_a();
      vector<vector<vector<Real> > >             get_cont_ene_b();
      vector<vector<vector<vector<Real> > > >    get_cont_data();
      vector<vector<Integer> >                   get_two_body_repr_flg();
      vector<vector<Integer> >                   get_two_body_int_data();
      vector<vector<Integer> >                   get_two_body_range_data();
      vector<vector<Real> >                      get_two_body_ene_data();
      vector<vector<vector<Real> > >             get_two_body_legendre_coef();
      vector<vector<vector<Real> > >             get_two_body_cos();
      vector<vector<vector<Real> > >             get_two_body_prob();
      vector<Real>                               get_spin_particle();
      vector<Integer>                            get_charged_particle_flg();
      vector<vector<Integer> >                   get_charged_particle_repr_flg();
      vector<vector<Real> >                      get_charged_particle_ene_data();
      vector<vector<Real> >                      get_charged_particle_mass_data();
      vector<vector<Integer> >                   get_charged_particle_int_data();
      vector<vector<Integer> >                   get_charged_particle_range_data();
      vector<vector<vector<Real> > >             get_charged_particle_coef_b();
      vector<vector<vector<Real> > >             get_charged_particle_coef_r();
      vector<vector<vector<Real> > >             get_charged_particle_coef_i();
      vector<vector<vector<Real> > >             get_charged_particle_coef_c();
      vector<vector<vector<Real> > >             get_charged_particle_coef_mu();
      vector<vector<vector<Real> > >             get_charged_particle_coef_p();
      vector<Real>                               get_n_body_mass();
      vector<Integer>                            get_n_body_particle_no();
      vector<vector<Real> >                      get_lab_ene();
      vector<vector<Integer> >                   get_lab_ene_int_data();
      vector<vector<Integer> >                   get_lab_ene_range_data();
      vector<vector<vector<Real> > >             get_lab_cos();
      vector<vector<vector<Integer> > >          get_lab_integrate_int_data();
      vector<vector<vector<Integer> > >          get_lab_integrate_range_data();
      vector<vector<vector<Real> > >             get_lab_integrate_cos_data();
      vector<vector<vector<Real> > >             get_lab_integrate_data();
      vector<vector<vector<Integer> > >          get_lab_cos_int_data();
      vector<vector<vector<Integer> > >          get_lab_cos_range_data();
      vector<vector<vector<vector<Integer> > > > get_lab_int_data();
      vector<vector<vector<vector<Integer> > > > get_lab_range_data();
      vector<vector<vector<vector<Real> > > >    get_lab_ene_sec_data();
      vector<vector<vector<vector<Real> > > >    get_lab_data();
      vector<Real>                               get_mat_data_second_product();
      vector<Integer>                            get_second_distr_func_flg();
      vector<vector<Integer> >                   get_second_distr_yield_int_data();
      vector<vector<Integer> >                   get_second_distr_yield_range_data();
      vector<vector<Real> >                      get_second_distr_yield_ene_data();
      vector<vector<Real> >                      get_second_distr_yield_data();
      vector<Integer>                            get_second_distr_angular_repr_flg();
      vector<Integer>                            get_second_distr_ene_int_data();
      vector<vector<Integer> >                   get_second_distr_cont_int_data();
      vector<vector<Integer> >                   get_second_distr_cont_range_data();
      vector<vector<Integer> >                   get_second_distr_discrete_ene_no();
      vector<vector<Real> >                      get_second_distr_cont_ene_a();
      vector<vector<vector<Real> > >             get_second_distr_cont_ene_b();
      vector<vector<vector<vector<Real> > > >    get_second_distr_cont_data();
      vector<vector<Integer> >                   get_second_distr_two_body_repr_flg();
      vector<vector<Integer> >                   get_second_distr_two_body_int_data();
      vector<vector<Integer> >                   get_second_distr_two_body_range_data();
      vector<vector<Real> >                      get_second_distr_two_body_ene_data();
      vector<vector<vector<Real> > >             get_second_distr_two_body_legendre_coef();
      vector<vector<vector<Real> > >             get_second_distr_two_body_cos();
      vector<vector<vector<Real> > >             get_second_distr_two_body_prob();
      vector<vector<Integer> >                   get_second_distr_transfer_int_data();
      vector<vector<Integer> >                   get_second_distr_transfer_range_data();
      vector<vector<Real> >                      get_second_distr_transfer_ene_data();
      vector<vector<Real> >                      get_second_distr_transfer_data();

      Real                            get_temp();
      vector<Real>                    get_incident_ene();
      vector<vector<Real> >           get_second_ene();
      vector<vector<Real> >           get_incoherent_inelastic_scat_xs_integrate();
      vector<vector<vector<Real> > >  get_incoherent_inelastic_scat_xs_weight();
      vector<vector<Real> >           get_incoherent_elastic_scat_angle();
      Integer                         get_bragg_edge_no();

      //Setter
      void set_reaction_type( Integer int_data );
      void set_prompt_fis_n_flg( Integer int_data );
      void set_prompt_fis_p_flg( Integer int_data );
      void set_ref_frame_flg( Integer int_data );
      void set_mat_data_product( vector<Real> real_vec );
      void set_mass_product( vector<Real> real_vec );
      void set_product_mod_flg( vector<Integer> int_vec );
      void set_distr_func_flg( vector<Integer> int_vec );
      void set_product_distr_int_data( vector<vector<Integer> > int_vec );
      void set_product_distr_range_data( vector<vector<Integer> > int_vec );
      void set_product_distr_ene_data( vector<vector<Real> > real_vec );
      void set_product_distr_data( vector<vector<Real> > real_vec );
      void set_angular_repr_flg( vector<Integer> int_vec );
      void set_second_ene_int_data( vector<Integer> int_vec );
      void set_cont_int_data( vector<vector<Integer> > int_vec );
      void set_cont_range_data( vector<vector<Integer> > int_vec );
      void set_discrete_ene_no( vector<vector<Integer> > int_vec );
      void set_cont_ene_a( vector<vector<Real> > real_vec );
      void set_cont_ene_b( vector<vector<vector<Real> > > real_vec );
      void set_cont_data( vector<vector<vector<vector<Real> > > > real_vec );
      void set_two_body_repr_flg( vector<vector<Integer> > int_vec );
      void set_two_body_int_data( vector<vector<Integer> > int_vec );
      void set_two_body_range_data( vector<vector<Integer> > int_vec );
      void set_two_body_ene_data( vector<vector<Real> > real_vec );
      void set_two_body_legendre_coef( vector<vector<vector<Real> > > real_vec );
      void set_two_body_cos( vector<vector<vector<Real> > > real_vec );
      void set_two_body_prob( vector<vector<vector<Real> > > real_vec );
      void set_spin_particle( vector<Real> real_vec );
      void set_charged_particle_flg( vector<Integer> int_vec );
      void set_charged_particle_repr_flg( vector<vector<Integer> > int_vec );
      void set_charged_particle_ene_data( vector<vector<Real> > real_vec );
      void set_charged_particle_mass_data( vector<vector<Real> > real_vec );
      void set_charged_particle_int_data( vector<vector<Integer> > int_vec );
      void set_charged_particle_range_data( vector<vector<Integer> > int_vec );
      void set_charged_particle_coef_b( vector<vector<vector<Real> > > real_vec );
      void set_charged_particle_coef_r( vector<vector<vector<Real> > > real_vec );
      void set_charged_particle_coef_i( vector<vector<vector<Real> > > real_vec );
      void set_charged_particle_coef_c( vector<vector<vector<Real> > > real_vec );
      void set_charged_particle_coef_mu( vector<vector<vector<Real> > > real_vec );
      void set_charged_particle_coef_p( vector<vector<vector<Real> > > real_vec );
      void set_n_body_mass( vector<Real> real_vec );
      void set_n_body_particle_no( vector<Integer> int_vec );
      void set_lab_ene( vector<vector<Real> > real_vec );
      void set_lab_ene_int_data( vector<vector<Integer> > int_vec );
      void set_lab_ene_range_data( vector<vector<Integer> > int_vec );
      void set_lab_cos( vector<vector<vector<Real> > > real_vec );
      void set_lab_integrate_int_data( vector<vector<vector<Integer> > > int_vec );
      void set_lab_integrate_range_data( vector<vector<vector<Integer> > > int_vec );
      void set_lab_integrate_cos_data( vector<vector<vector<Real> > > real_vec );
      void set_lab_integrate_data( vector<vector<vector<Real> > > real_vec );
      void set_lab_cos_int_data( vector<vector<vector<Integer> > > int_vec );
      void set_lab_cos_range_data( vector<vector<vector<Integer> > > int_vec );
      void set_lab_int_data( vector<vector<vector<vector<Integer> > > > int_vec );
      void set_lab_range_data( vector<vector<vector<vector<Integer> > > > int_vec );
      void set_lab_ene_sec_data( vector<vector<vector<vector<Real> > > > real_vec );
      void set_lab_data( vector<vector<vector<vector<Real> > > > real_vec );
      void set_mat_data_second_product( vector<Real> real_vec );
      void set_second_distr_func_flg( vector<Integer> int_vec );
      void set_second_distr_yield_int_data( vector<vector<Integer> > int_vec );
      void set_second_distr_yield_range_data( vector<vector<Integer> > int_vec );
      void set_second_distr_yield_ene_data( vector<vector<Real> > real_vec );
      void set_second_distr_yield_data( vector<vector<Real> > real_vec );
      void set_second_distr_angular_repr_flg( vector<Integer> int_vec );
      void set_second_distr_ene_int_data( vector<Integer> int_vec );
      void set_second_distr_cont_int_data( vector<vector<Integer> > int_vec );
      void set_second_distr_cont_range_data( vector<vector<Integer> > int_vec );
      void set_second_distr_discrete_ene_no( vector<vector<Integer> > int_vec );
      void set_second_distr_cont_ene_a( vector<vector<Real> > real_vec );
      void set_second_distr_cont_ene_b( vector<vector<vector<Real> > > real_vec );
      void set_second_distr_cont_data( vector<vector<vector<vector<Real> > > > real_vec );
      void set_second_distr_two_body_repr_flg( vector<vector<Integer> > int_vec );
      void set_second_distr_two_body_int_data( vector<vector<Integer> > int_vec );
      void set_second_distr_two_body_range_data( vector<vector<Integer> > int_vec );
      void set_second_distr_two_body_ene_data( vector<vector<Real> > real_vec );
      void set_second_distr_two_body_legendre_coef( vector<vector<vector<Real> > > real_vec );
      void set_second_distr_two_body_cos( vector<vector<vector<Real> > > real_vec );
      void set_second_distr_two_body_prob( vector<vector<vector<Real> > > real_vec );
      void set_second_distr_transfer_int_data( vector<vector<Integer> > int_vec );
      void set_second_distr_transfer_range_data( vector<vector<Integer> > int_vec );
      void set_second_distr_transfer_ene_data( vector<vector<Real> > real_vec );
      void set_second_distr_transfer_data( vector<vector<Real> > real_vec );

      void set_temp( Real real_val );
      void set_incident_ene( vector<Real> real_vec );
      void set_second_ene( vector<vector<Real> > real_vec );
      void set_incoherent_inelastic_scat_xs_integrate( vector<vector<Real> > real_vec );
      void set_incoherent_inelastic_scat_xs_weight( vector<vector<vector<Real> > > real_vec );
      void set_incoherent_elastic_scat_angle( vector<vector<Real> > real_vec );
      void set_bragg_edge_no( Integer int_val );
  };
}

#endif //PRODUCT_DISTRIBUTION_DATA_CONTAINER_H
