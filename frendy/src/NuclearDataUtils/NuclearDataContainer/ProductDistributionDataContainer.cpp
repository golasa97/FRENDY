#include "NuclearDataUtils/NuclearDataContainer/ProductDistributionDataContainer.hpp"

using namespace frendy;

//constructor
ProductDistributionDataContainer::ProductDistributionDataContainer(void)
{
  clear();
}

//destructor
ProductDistributionDataContainer::~ProductDistributionDataContainer(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProductDistributionDataContainer::clear()
{
  reaction_type = unassigned_mt_no;
  prompt_fis_n_flg = 0;
  prompt_fis_p_flg = 0;
  ref_frame_flg    = 0;

  mat_data_product.clear();
  mass_product.clear();
  product_mod_flg.clear();
  distr_func_flg.clear();
  clr_obj.clear_vec_array2_int( product_distr_int_data );
  clr_obj.clear_vec_array2_int( product_distr_range_data );
  clr_obj.clear_vec_array2_real( product_distr_ene_data );
  clr_obj.clear_vec_array2_real( product_distr_data );
  angular_repr_flg.clear();
  second_ene_int_data.clear();
  clr_obj.clear_vec_array2_int( cont_int_data );
  clr_obj.clear_vec_array2_int( cont_range_data );
  clr_obj.clear_vec_array2_int( discrete_ene_no );
  clr_obj.clear_vec_array2_real( cont_ene_a );
  clr_obj.clear_vec_array3_real( cont_ene_b );
  clr_obj.clear_vec_array4_real( cont_data );
  clr_obj.clear_vec_array2_int( two_body_repr_flg );
  clr_obj.clear_vec_array2_int( two_body_int_data );
  clr_obj.clear_vec_array2_int( two_body_range_data );
  clr_obj.clear_vec_array2_real( two_body_ene_data );
  clr_obj.clear_vec_array3_real( two_body_legendre_coef );
  clr_obj.clear_vec_array3_real( two_body_cos );
  clr_obj.clear_vec_array3_real( two_body_prob );
  spin_particle.clear();
  charged_particle_flg.clear();
  clr_obj.clear_vec_array2_int( charged_particle_repr_flg );
  clr_obj.clear_vec_array2_real( charged_particle_ene_data );
  clr_obj.clear_vec_array2_real( charged_particle_mass_data );
  clr_obj.clear_vec_array2_int( charged_particle_int_data );
  clr_obj.clear_vec_array2_int( charged_particle_range_data );
  clr_obj.clear_vec_array3_real( charged_particle_coef_b );
  clr_obj.clear_vec_array3_real( charged_particle_coef_r );
  clr_obj.clear_vec_array3_real( charged_particle_coef_i );
  clr_obj.clear_vec_array3_real( charged_particle_coef_c );
  clr_obj.clear_vec_array3_real( charged_particle_coef_mu );
  clr_obj.clear_vec_array3_real( charged_particle_coef_p );
  n_body_mass.clear();
  n_body_particle_no.clear();
  clr_obj.clear_vec_array2_real( lab_ene );
  clr_obj.clear_vec_array2_int( lab_ene_int_data );
  clr_obj.clear_vec_array2_int( lab_ene_range_data );
  clr_obj.clear_vec_array3_real( lab_cos );
  clr_obj.clear_vec_array3_int( lab_integrate_int_data );
  clr_obj.clear_vec_array3_int( lab_integrate_range_data );
  clr_obj.clear_vec_array3_real( lab_integrate_cos_data );
  clr_obj.clear_vec_array3_real( lab_integrate_data );
  clr_obj.clear_vec_array3_int( lab_cos_int_data );
  clr_obj.clear_vec_array3_int( lab_cos_range_data );
  clr_obj.clear_vec_array4_int( lab_int_data );
  clr_obj.clear_vec_array4_int( lab_range_data );
  clr_obj.clear_vec_array4_real( lab_ene_sec_data );
  clr_obj.clear_vec_array4_real( lab_data );
  mat_data_second_product.clear();
  second_distr_func_flg.clear();
  clr_obj.clear_vec_array2_int( second_distr_yield_int_data );
  clr_obj.clear_vec_array2_int( second_distr_yield_range_data );
  clr_obj.clear_vec_array2_real( second_distr_yield_ene_data );
  clr_obj.clear_vec_array2_real( second_distr_yield_data );
  second_distr_angular_repr_flg.clear();
  second_distr_ene_int_data.clear();
  clr_obj.clear_vec_array2_int( second_distr_cont_int_data );
  clr_obj.clear_vec_array2_int( second_distr_cont_range_data );
  clr_obj.clear_vec_array2_int( second_distr_discrete_ene_no );
  clr_obj.clear_vec_array2_real( second_distr_cont_ene_a );
  clr_obj.clear_vec_array3_real( second_distr_cont_ene_b );
  clr_obj.clear_vec_array4_real( second_distr_cont_data );
  clr_obj.clear_vec_array2_int( second_distr_two_body_repr_flg );
  clr_obj.clear_vec_array2_int( second_distr_two_body_int_data );
  clr_obj.clear_vec_array2_int( second_distr_two_body_range_data );
  clr_obj.clear_vec_array2_real( second_distr_two_body_ene_data );
  clr_obj.clear_vec_array3_real( second_distr_two_body_legendre_coef );
  clr_obj.clear_vec_array3_real( second_distr_two_body_cos );
  clr_obj.clear_vec_array3_real( second_distr_two_body_prob );
  clr_obj.clear_vec_array2_int( second_distr_transfer_int_data );
  clr_obj.clear_vec_array2_int( second_distr_transfer_range_data );
  clr_obj.clear_vec_array2_real( second_distr_transfer_ene_data );
  clr_obj.clear_vec_array2_real( second_distr_transfer_data );

  temp = 0.0;
  incident_ene.clear();
  clr_obj.clear_vec_array2_real(second_ene);
  clr_obj.clear_vec_array2_real(incoherent_inelastic_scat_xs_integrate);
  clr_obj.clear_vec_array3_real(incoherent_inelastic_scat_xs_weight);
  clr_obj.clear_vec_array2_real(incoherent_elastic_scat_angle);
  bragg_edge_no = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Getter
Integer ProductDistributionDataContainer::get_reaction_type()
{
  return reaction_type;
}

Integer ProductDistributionDataContainer::get_prompt_fis_n_flg()
{
  return prompt_fis_n_flg;
}

Integer ProductDistributionDataContainer::get_prompt_fis_p_flg()
{
  return prompt_fis_p_flg;
}

Integer ProductDistributionDataContainer::get_ref_frame_flg()
{
  return ref_frame_flg;
}

vector<Real> ProductDistributionDataContainer::get_mat_data_product()
{
  return mat_data_product;
}

vector<Real> ProductDistributionDataContainer::get_mass_product()
{
  return mass_product;
}

vector<Integer> ProductDistributionDataContainer::get_product_mod_flg()
{
  return product_mod_flg;
}

vector<Integer> ProductDistributionDataContainer::get_distr_func_flg()
{
  return distr_func_flg;
}

vector<vector<Integer> > ProductDistributionDataContainer::get_product_distr_int_data()
{
  return product_distr_int_data;
}

vector<vector<Integer> > ProductDistributionDataContainer::get_product_distr_range_data()
{
  return product_distr_range_data;
}

vector<vector<Real> > ProductDistributionDataContainer::get_product_distr_ene_data()
{
  return product_distr_ene_data;
}

vector<vector<Real> > ProductDistributionDataContainer::get_product_distr_data()
{
  return product_distr_data;
}

vector<Integer> ProductDistributionDataContainer::get_angular_repr_flg()
{
  return angular_repr_flg;
}

vector<Integer> ProductDistributionDataContainer::get_second_ene_int_data()
{
  return second_ene_int_data;
}

vector<vector<Integer> > ProductDistributionDataContainer::get_cont_int_data()
{
  return cont_int_data;
}

vector<vector<Integer> > ProductDistributionDataContainer::get_cont_range_data()
{
  return cont_range_data;
}

vector<vector<Integer> > ProductDistributionDataContainer::get_discrete_ene_no()
{
  return discrete_ene_no;
}

vector<vector<Real> > ProductDistributionDataContainer::get_cont_ene_a()
{
  return cont_ene_a;
}

vector<vector<vector<Real> > > ProductDistributionDataContainer::get_cont_ene_b()
{
  return cont_ene_b;
}

vector<vector<vector<vector<Real> > > > ProductDistributionDataContainer::get_cont_data()
{
  return cont_data;
}

vector<vector<Integer> > ProductDistributionDataContainer::get_two_body_repr_flg()
{
  return two_body_repr_flg;
}

vector<vector<Integer> > ProductDistributionDataContainer::get_two_body_int_data()
{
  return two_body_int_data;
}

vector<vector<Integer> > ProductDistributionDataContainer::get_two_body_range_data()
{
  return two_body_range_data;
}

vector<vector<Real> > ProductDistributionDataContainer::get_two_body_ene_data()
{
  return two_body_ene_data;
}

vector<vector<vector<Real> > > ProductDistributionDataContainer::get_two_body_legendre_coef()
{
  return two_body_legendre_coef;
}

vector<vector<vector<Real> > > ProductDistributionDataContainer::get_two_body_cos()
{
  return two_body_cos;
}

vector<vector<vector<Real> > > ProductDistributionDataContainer::get_two_body_prob()
{
  return two_body_prob;
}

vector<Real> ProductDistributionDataContainer::get_spin_particle()
{
  return spin_particle;
}

vector<Integer> ProductDistributionDataContainer::get_charged_particle_flg()
{
  return charged_particle_flg;
}

vector<vector<Integer> > ProductDistributionDataContainer::get_charged_particle_repr_flg()
{
  return charged_particle_repr_flg;
}

vector<vector<Real> > ProductDistributionDataContainer::get_charged_particle_ene_data()
{
  return charged_particle_ene_data;
}

vector<vector<Real> > ProductDistributionDataContainer::get_charged_particle_mass_data()
{
  return charged_particle_mass_data;
}

vector<vector<Integer> > ProductDistributionDataContainer::get_charged_particle_int_data()
{
  return charged_particle_int_data;
}

vector<vector<Integer> > ProductDistributionDataContainer::get_charged_particle_range_data()
{
  return charged_particle_range_data;
}

vector<vector<vector<Real> > > ProductDistributionDataContainer::get_charged_particle_coef_b()
{
  return charged_particle_coef_b;
}

vector<vector<vector<Real> > > ProductDistributionDataContainer::get_charged_particle_coef_r()
{
  return charged_particle_coef_r;
}

vector<vector<vector<Real> > > ProductDistributionDataContainer::get_charged_particle_coef_i()
{
  return charged_particle_coef_i;
}

vector<vector<vector<Real> > > ProductDistributionDataContainer::get_charged_particle_coef_c()
{
  return charged_particle_coef_c;
}

vector<vector<vector<Real> > > ProductDistributionDataContainer::get_charged_particle_coef_mu()
{
  return charged_particle_coef_mu;
}

vector<vector<vector<Real> > > ProductDistributionDataContainer::get_charged_particle_coef_p()
{
  return charged_particle_coef_p;
}

vector<Real> ProductDistributionDataContainer::get_n_body_mass()
{
  return n_body_mass;
}

vector<Integer> ProductDistributionDataContainer::get_n_body_particle_no()
{
  return n_body_particle_no;
}

vector<vector<Real> > ProductDistributionDataContainer::get_lab_ene()
{
  return lab_ene;
}

vector<vector<Integer> > ProductDistributionDataContainer::get_lab_ene_int_data()
{
  return lab_ene_int_data;
}

vector<vector<Integer> > ProductDistributionDataContainer::get_lab_ene_range_data()
{
  return lab_ene_range_data;
}

vector<vector<vector<Real> > > ProductDistributionDataContainer::get_lab_cos()
{
  return lab_cos;
}

vector<vector<vector<Integer> > > ProductDistributionDataContainer::get_lab_integrate_int_data()
{
  return lab_integrate_int_data;
}

vector<vector<vector<Integer> > > ProductDistributionDataContainer::get_lab_integrate_range_data()
{
  return lab_integrate_range_data;
}

vector<vector<vector<Real> > > ProductDistributionDataContainer::get_lab_integrate_cos_data()
{
  return lab_integrate_cos_data;
}

vector<vector<vector<Real> > > ProductDistributionDataContainer::get_lab_integrate_data()
{
  return lab_integrate_data;
}

vector<vector<vector<Integer> > > ProductDistributionDataContainer::get_lab_cos_int_data()
{
  return lab_cos_int_data;
}

vector<vector<vector<Integer> > > ProductDistributionDataContainer::get_lab_cos_range_data()
{
  return lab_cos_range_data;
}

vector<vector<vector<vector<Integer> > > > ProductDistributionDataContainer::get_lab_int_data()
{
  return lab_int_data;
}

vector<vector<vector<vector<Integer> > > > ProductDistributionDataContainer::get_lab_range_data()
{
  return lab_range_data;
}

vector<vector<vector<vector<Real> > > > ProductDistributionDataContainer::get_lab_ene_sec_data()
{
  return lab_ene_sec_data;
}

vector<vector<vector<vector<Real> > > > ProductDistributionDataContainer::get_lab_data()
{
  return lab_data;
}

vector<Real> ProductDistributionDataContainer::get_mat_data_second_product()
{
  return mat_data_second_product;
}

vector<Integer> ProductDistributionDataContainer::get_second_distr_func_flg()
{
  return second_distr_func_flg;
}

vector<vector<Integer> > ProductDistributionDataContainer::get_second_distr_yield_int_data()
{
  return second_distr_yield_int_data;
}

vector<vector<Integer> > ProductDistributionDataContainer::get_second_distr_yield_range_data()
{
  return second_distr_yield_range_data;
}

vector<vector<Real> > ProductDistributionDataContainer::get_second_distr_yield_ene_data()
{
  return second_distr_yield_ene_data;
}

vector<vector<Real> > ProductDistributionDataContainer::get_second_distr_yield_data()
{
  return second_distr_yield_data;
}

vector<Integer> ProductDistributionDataContainer::get_second_distr_angular_repr_flg()
{
  return second_distr_angular_repr_flg;
}

vector<Integer> ProductDistributionDataContainer::get_second_distr_ene_int_data()
{
  return second_distr_ene_int_data;
}


vector<vector<Integer> > ProductDistributionDataContainer::get_second_distr_cont_int_data()
{
  return second_distr_cont_int_data;
}

vector<vector<Integer> > ProductDistributionDataContainer::get_second_distr_cont_range_data()
{
  return second_distr_cont_range_data;
}

vector<vector<Integer> > ProductDistributionDataContainer::get_second_distr_discrete_ene_no()
{
  return second_distr_discrete_ene_no;
}

vector<vector<Real> > ProductDistributionDataContainer::get_second_distr_cont_ene_a()
{
  return second_distr_cont_ene_a;
}

vector<vector<vector<Real> > > ProductDistributionDataContainer::get_second_distr_cont_ene_b()
{
  return second_distr_cont_ene_b;
}

vector<vector<vector<vector<Real> > > > ProductDistributionDataContainer::get_second_distr_cont_data()
{
  return second_distr_cont_data;
}

vector<vector<Integer> > ProductDistributionDataContainer::get_second_distr_two_body_repr_flg()
{
  return second_distr_two_body_repr_flg;
}

vector<vector<Integer> > ProductDistributionDataContainer::get_second_distr_two_body_int_data()
{
  return second_distr_two_body_int_data;
}

vector<vector<Integer> > ProductDistributionDataContainer::get_second_distr_two_body_range_data()
{
  return second_distr_two_body_range_data;
}

vector<vector<Real> > ProductDistributionDataContainer::get_second_distr_two_body_ene_data()
{
  return second_distr_two_body_ene_data;
}

vector<vector<vector<Real> > > ProductDistributionDataContainer::get_second_distr_two_body_legendre_coef()
{
  return second_distr_two_body_legendre_coef;
}

vector<vector<vector<Real> > > ProductDistributionDataContainer::get_second_distr_two_body_cos()
{
  return second_distr_two_body_cos;
}

vector<vector<vector<Real> > > ProductDistributionDataContainer::get_second_distr_two_body_prob()
{
  return second_distr_two_body_prob;
}

vector<vector<Integer> > ProductDistributionDataContainer::get_second_distr_transfer_int_data()
{
  return second_distr_transfer_int_data;
}

vector<vector<Integer> > ProductDistributionDataContainer::get_second_distr_transfer_range_data()
{
  return second_distr_transfer_range_data;
}

vector<vector<Real> > ProductDistributionDataContainer::get_second_distr_transfer_ene_data()
{
  return second_distr_transfer_ene_data;
}

vector<vector<Real> > ProductDistributionDataContainer::get_second_distr_transfer_data()
{
  return second_distr_transfer_data;
}


Real                            ProductDistributionDataContainer::get_temp()
{
  return temp;
}

vector<Real>                    ProductDistributionDataContainer::get_incident_ene()
{
  return incident_ene;
}

vector<vector<Real> >           ProductDistributionDataContainer::get_second_ene()
{
  return second_ene;
}

vector<vector<Real> >           ProductDistributionDataContainer::get_incoherent_inelastic_scat_xs_integrate()
{
  return incoherent_inelastic_scat_xs_integrate;
}

vector<vector<vector<Real> > >  ProductDistributionDataContainer::get_incoherent_inelastic_scat_xs_weight()
{
  return incoherent_inelastic_scat_xs_weight;
}

vector<vector<Real> >           ProductDistributionDataContainer::get_incoherent_elastic_scat_angle()
{
  return incoherent_elastic_scat_angle;
}

Integer                         ProductDistributionDataContainer::get_bragg_edge_no()
{
  return bragg_edge_no;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void ProductDistributionDataContainer::set_reaction_type( Integer int_data )
{
  reaction_type = int_data;
}

void ProductDistributionDataContainer::set_prompt_fis_n_flg( Integer int_data )
{
  prompt_fis_n_flg = int_data;
}

void ProductDistributionDataContainer::set_prompt_fis_p_flg( Integer int_data )
{
  prompt_fis_p_flg = int_data;
}

void ProductDistributionDataContainer::set_ref_frame_flg( Integer int_data )
{
  ref_frame_flg = int_data;
}

void ProductDistributionDataContainer::set_mat_data_product( vector<Real> real_vec )
{
  mat_data_product = real_vec;
  real_vec.clear();
}

void ProductDistributionDataContainer::set_mass_product( vector<Real> real_vec )
{
  mass_product = real_vec;
  real_vec.clear();
}

void ProductDistributionDataContainer::set_product_mod_flg( vector<Integer> int_vec )
{
  product_mod_flg = int_vec;
  int_vec.clear();
}

void ProductDistributionDataContainer::set_distr_func_flg( vector<Integer> int_vec )
{
  distr_func_flg = int_vec;
  int_vec.clear();
}

void ProductDistributionDataContainer::set_product_distr_int_data( vector<vector<Integer> > int_vec )
{
  product_distr_int_data = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void ProductDistributionDataContainer::set_product_distr_range_data( vector<vector<Integer> > int_vec )
{
  product_distr_range_data = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void ProductDistributionDataContainer::set_product_distr_ene_data( vector<vector<Real> > real_vec )
{
  product_distr_ene_data = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void ProductDistributionDataContainer::set_product_distr_data( vector<vector<Real> > real_vec )
{
  product_distr_data = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void ProductDistributionDataContainer::set_angular_repr_flg( vector<Integer> int_vec )
{
  angular_repr_flg = int_vec;
  int_vec.clear();
}

void ProductDistributionDataContainer::set_second_ene_int_data( vector<Integer> int_vec )
{
  second_ene_int_data = int_vec;
  int_vec.clear();
}

void ProductDistributionDataContainer::set_cont_int_data( vector<vector<Integer> > int_vec )
{
  cont_int_data = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void ProductDistributionDataContainer::set_cont_range_data( vector<vector<Integer> > int_vec )
{
  cont_range_data = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void ProductDistributionDataContainer::set_discrete_ene_no( vector<vector<Integer> > int_vec )
{
  discrete_ene_no = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void ProductDistributionDataContainer::set_cont_ene_a( vector<vector<Real> > real_vec )
{
  cont_ene_a = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void ProductDistributionDataContainer::set_cont_ene_b( vector<vector<vector<Real> > > real_vec )
{
  cont_ene_b = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

void ProductDistributionDataContainer::set_cont_data( vector<vector<vector<vector<Real> > > > real_vec )
{
  cont_data = real_vec;
  clr_obj.clear_vec_array4_real( real_vec );
}

void ProductDistributionDataContainer::set_two_body_repr_flg( vector<vector<Integer> > int_vec )
{
  two_body_repr_flg = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void ProductDistributionDataContainer::set_two_body_int_data( vector<vector<Integer> > int_vec )
{
  two_body_int_data = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void ProductDistributionDataContainer::set_two_body_range_data( vector<vector<Integer> > int_vec )
{
  two_body_range_data = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void ProductDistributionDataContainer::set_two_body_ene_data( vector<vector<Real> > real_vec )
{
  two_body_ene_data = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void ProductDistributionDataContainer::set_two_body_legendre_coef( vector<vector<vector<Real> > > real_vec )
{
  two_body_legendre_coef = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

void ProductDistributionDataContainer::set_two_body_cos( vector<vector<vector<Real> > > real_vec )
{
  two_body_cos = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

void ProductDistributionDataContainer::set_two_body_prob( vector<vector<vector<Real> > > real_vec )
{
  two_body_prob = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

void ProductDistributionDataContainer::set_spin_particle( vector<Real> real_vec )
{
  spin_particle = real_vec;
  real_vec.clear();
}

void ProductDistributionDataContainer::set_charged_particle_flg( vector<Integer> int_vec )
{
  charged_particle_flg = int_vec;
  int_vec.clear();
}

void ProductDistributionDataContainer::set_charged_particle_repr_flg( vector<vector<Integer> > int_vec )
{
  charged_particle_repr_flg = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void ProductDistributionDataContainer::set_charged_particle_ene_data( vector<vector<Real> > real_vec )
{
  charged_particle_ene_data = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void ProductDistributionDataContainer::set_charged_particle_mass_data( vector<vector<Real> > real_vec )
{
  charged_particle_mass_data = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void ProductDistributionDataContainer::set_charged_particle_int_data( vector<vector<Integer> > int_vec )
{
  charged_particle_int_data = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void ProductDistributionDataContainer::set_charged_particle_range_data( vector<vector<Integer> > int_vec )
{
  charged_particle_range_data = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void ProductDistributionDataContainer::set_charged_particle_coef_b( vector<vector<vector<Real> > > real_vec )
{
  charged_particle_coef_b = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

void ProductDistributionDataContainer::set_charged_particle_coef_r( vector<vector<vector<Real> > > real_vec )
{
  charged_particle_coef_r = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

void ProductDistributionDataContainer::set_charged_particle_coef_i( vector<vector<vector<Real> > > real_vec )
{
  charged_particle_coef_i = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

void ProductDistributionDataContainer::set_charged_particle_coef_c( vector<vector<vector<Real> > > real_vec )
{
  charged_particle_coef_c = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

void ProductDistributionDataContainer::set_charged_particle_coef_mu( vector<vector<vector<Real> > > real_vec )
{
  charged_particle_coef_mu = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

void ProductDistributionDataContainer::set_charged_particle_coef_p( vector<vector<vector<Real> > > real_vec )
{
  charged_particle_coef_p = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

void ProductDistributionDataContainer::set_n_body_mass( vector<Real> real_vec )
{
  n_body_mass = real_vec;
  real_vec.clear();
}

void ProductDistributionDataContainer::set_n_body_particle_no( vector<Integer> int_vec )
{
  n_body_particle_no = int_vec;
  int_vec.clear();
}

void ProductDistributionDataContainer::set_lab_ene( vector<vector<Real> > real_vec )
{
  lab_ene = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void ProductDistributionDataContainer::set_lab_ene_int_data( vector<vector<Integer> > int_vec )
{
  lab_ene_int_data = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void ProductDistributionDataContainer::set_lab_ene_range_data( vector<vector<Integer> > int_vec )
{
  lab_ene_range_data = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void ProductDistributionDataContainer::set_lab_cos( vector<vector<vector<Real> > > real_vec )
{
  lab_cos = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

void ProductDistributionDataContainer::set_lab_integrate_int_data( vector<vector<vector<Integer> > > int_vec )
{
  lab_integrate_int_data = int_vec;
  clr_obj.clear_vec_array3_int( int_vec );
}

void ProductDistributionDataContainer::set_lab_integrate_range_data( vector<vector<vector<Integer> > > int_vec )
{
  lab_integrate_range_data = int_vec;
  clr_obj.clear_vec_array3_int( int_vec );
}

void ProductDistributionDataContainer::set_lab_integrate_cos_data( vector<vector<vector<Real> > > real_vec )
{
  lab_integrate_cos_data = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

void ProductDistributionDataContainer::set_lab_integrate_data( vector<vector<vector<Real> > > real_vec )
{
  lab_integrate_data = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

void ProductDistributionDataContainer::set_lab_cos_int_data( vector<vector<vector<Integer> > > int_vec )
{
  lab_cos_int_data = int_vec;
  clr_obj.clear_vec_array3_int( int_vec );
}

void ProductDistributionDataContainer::set_lab_cos_range_data( vector<vector<vector<Integer> > > int_vec )
{
  lab_cos_range_data = int_vec;
  clr_obj.clear_vec_array3_int( int_vec );
}

void ProductDistributionDataContainer::set_lab_int_data( vector<vector<vector<vector<Integer> > > > int_vec )
{
  lab_int_data = int_vec;
  clr_obj.clear_vec_array4_int( int_vec );
}

void ProductDistributionDataContainer::set_lab_range_data( vector<vector<vector<vector<Integer> > > > int_vec )
{
  lab_range_data = int_vec;
  clr_obj.clear_vec_array4_int( int_vec );
}

void ProductDistributionDataContainer::set_lab_ene_sec_data( vector<vector<vector<vector<Real> > > > real_vec )
{
  lab_ene_sec_data = real_vec;
  clr_obj.clear_vec_array4_real( real_vec );
}

void ProductDistributionDataContainer::set_lab_data( vector<vector<vector<vector<Real> > > > real_vec )
{
  lab_data = real_vec;
  clr_obj.clear_vec_array4_real( real_vec );
}

void ProductDistributionDataContainer::set_mat_data_second_product( vector<Real> real_vec )
{
  mat_data_second_product = real_vec;
  real_vec.clear();
}

void ProductDistributionDataContainer::set_second_distr_func_flg( vector<Integer> int_vec )
{
  second_distr_func_flg = int_vec;
  int_vec.clear();
}

void ProductDistributionDataContainer::set_second_distr_yield_int_data( vector<vector<Integer> > int_vec )
{
  second_distr_yield_int_data = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void ProductDistributionDataContainer::set_second_distr_yield_range_data( vector<vector<Integer> > int_vec )
{
  second_distr_yield_range_data = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void ProductDistributionDataContainer::set_second_distr_yield_ene_data( vector<vector<Real> > real_vec )
{
  second_distr_yield_ene_data = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void ProductDistributionDataContainer::set_second_distr_yield_data( vector<vector<Real> > real_vec )
{
  second_distr_yield_data = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void ProductDistributionDataContainer::set_second_distr_angular_repr_flg( vector<Integer> int_vec )
{
  second_distr_angular_repr_flg = int_vec;
  int_vec.clear();
}

void ProductDistributionDataContainer::set_second_distr_ene_int_data( vector<Integer> int_vec )
{
  second_distr_ene_int_data = int_vec;
  int_vec.clear();
}

void ProductDistributionDataContainer::set_second_distr_cont_int_data( vector<vector<Integer> > int_vec )
{
  second_distr_cont_int_data = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void ProductDistributionDataContainer::set_second_distr_cont_range_data( vector<vector<Integer> > int_vec )
{
  second_distr_cont_range_data = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void ProductDistributionDataContainer::set_second_distr_discrete_ene_no( vector<vector<Integer> > int_vec )
{
  second_distr_discrete_ene_no = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void ProductDistributionDataContainer::set_second_distr_cont_ene_a( vector<vector<Real> > real_vec )
{
  second_distr_cont_ene_a = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void ProductDistributionDataContainer::set_second_distr_cont_ene_b( vector<vector<vector<Real> > > real_vec )
{
  second_distr_cont_ene_b = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

void ProductDistributionDataContainer::set_second_distr_cont_data( vector<vector<vector<vector<Real> > > > real_vec )
{
  second_distr_cont_data = real_vec;
  clr_obj.clear_vec_array4_real( real_vec );
}

void ProductDistributionDataContainer::set_second_distr_two_body_repr_flg( vector<vector<Integer> > int_vec )
{
  second_distr_two_body_repr_flg = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void ProductDistributionDataContainer::set_second_distr_two_body_int_data( vector<vector<Integer> > int_vec )
{
  second_distr_two_body_int_data = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void ProductDistributionDataContainer::set_second_distr_two_body_range_data( vector<vector<Integer> > int_vec )
{
  second_distr_two_body_range_data = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void ProductDistributionDataContainer::set_second_distr_two_body_ene_data( vector<vector<Real> > real_vec )
{
  second_distr_two_body_ene_data = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void ProductDistributionDataContainer::set_second_distr_two_body_legendre_coef( vector<vector<vector<Real> > > real_vec )
{
  second_distr_two_body_legendre_coef = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

void ProductDistributionDataContainer::set_second_distr_two_body_cos( vector<vector<vector<Real> > > real_vec )
{
  second_distr_two_body_cos = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

void ProductDistributionDataContainer::set_second_distr_two_body_prob( vector<vector<vector<Real> > > real_vec )
{
  second_distr_two_body_prob = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

void ProductDistributionDataContainer::set_second_distr_transfer_int_data( vector<vector<Integer> > int_vec )
{
  second_distr_transfer_int_data = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void ProductDistributionDataContainer::set_second_distr_transfer_range_data( vector<vector<Integer> > int_vec )
{
  second_distr_transfer_range_data = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void ProductDistributionDataContainer::set_second_distr_transfer_ene_data( vector<vector<Real> > real_vec )
{
  second_distr_transfer_ene_data = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void ProductDistributionDataContainer::set_second_distr_transfer_data( vector<vector<Real> > real_vec )
{
  second_distr_transfer_data = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void ProductDistributionDataContainer::set_temp( Real real_val )
{
  temp = real_val;
}

void ProductDistributionDataContainer::set_incident_ene( vector<Real> real_vec )
{
  incident_ene = real_vec;
  real_vec.clear();
}

void ProductDistributionDataContainer::set_second_ene( vector<vector<Real> > real_vec )
{
  second_ene = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void ProductDistributionDataContainer::set_incoherent_inelastic_scat_xs_integrate
                                         ( vector<vector<Real> > real_vec )
{
  incoherent_inelastic_scat_xs_integrate = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void ProductDistributionDataContainer::set_incoherent_inelastic_scat_xs_weight
                                         ( vector<vector<vector<Real> > > real_vec )
{
  incoherent_inelastic_scat_xs_weight = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

void ProductDistributionDataContainer::set_incoherent_elastic_scat_angle( vector<vector<Real> > real_vec )
{
  incoherent_elastic_scat_angle = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void ProductDistributionDataContainer::set_bragg_edge_no( Integer int_val )
{
  bragg_edge_no = int_val;
}

