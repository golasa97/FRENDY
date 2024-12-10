#include "NuclearDataUtils/NuclearDataContainer/ThermalScatterDataContainer.hpp"

using namespace frendy;

//constructor
ThermalScatterDataContainer::ThermalScatterDataContainer(void)
{
  clear();
}

//destructor
ThermalScatterDataContainer::~ThermalScatterDataContainer(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterDataContainer::clear()
{
  elastic_scat_flg           = 0;
  elastic_temp_data_base     = 0.0;
  elastic_bound_xs           = 0.0;
  inelastic_temp_flg         = 0;
  inelastic_symmetric_flg    = 0;
  inelastic_stored_form_flg  = 0;
  non_principal_scat_type_no = 0;

  elastic_temp_data.clear();
  elastic_temp_int.clear();
  elastic_structure_factor_int_data.clear();
  elastic_structure_factor_range_data.clear();
  elastic_structure_factor_ene_data.clear();
  elastic_structure_factor_data_base.clear();
  clr_obj.clear_vec_array2_real( elastic_structure_factor_data );
  elastic_debye_waller_int_data.clear();
  elastic_debye_waller_range_data.clear();
  elastic_debye_waller_temp_data.clear();
  elastic_debye_waller_data.clear();
  inelastic_scat_law_coef.clear();
  clr_obj.clear_vec_array2_int( inelastic_temp_int );
  inelastic_beta_int_data.clear();
  inelastic_beta_range_data.clear();
  inelastic_temp_data_base.clear();
  clr_obj.clear_vec_array2_real( inelastic_temp_data );
  inelastic_beta_data.clear();
  clr_obj.clear_vec_array2_int( inelastic_scat_law_int_data );
  clr_obj.clear_vec_array2_int( inelastic_scat_law_range_data );
  clr_obj.clear_vec_array2_real( inelastic_scat_law_alpha_data );
  clr_obj.clear_vec_array2_real( inelastic_scat_law_data_base );
  clr_obj.clear_vec_array3_real( inelastic_scat_law_data );
  clr_obj.clear_vec_array2_int( inelastic_temp_eff_int_data );
  clr_obj.clear_vec_array2_int( inelastic_temp_eff_range_data );
  clr_obj.clear_vec_array2_real( inelastic_temp_eff_temp_data );
  clr_obj.clear_vec_array2_real( inelastic_temp_eff_data );
  element_no        = 0;
  principal_atom_no = 0;
  mat_data_isotope.clear();
  state_no_isotope.clear();
  abundance_isotope.clear();
  scat_xs_isotope.clear();
  mass_isotope.clear();


  coherent_elastic_bragg_no = 0;
  coherent_elastic_ene_grid.clear();
  coherent_elastic_scat_xs_tot.clear();
  clr_obj.clear_vec_array2_real8(coherent_elastic_scat_xs);

  incoherent_elastic_ene_grid.clear();
  incoherent_elastic_scat_xs.clear();
  clr_obj.clear_vec_array2_real8(incoherent_elastic_scat_angle);
  clr_obj.clear_vec_array2_real8(incoherent_elastic_average_scat_angle);

  incoherent_inelastic_ene_grid.clear();
  incoherent_inelastic_ene_grid_scat_xs_tot.clear();
  incoherent_inelastic_scat_xs_tot.clear();
  clr_obj.clear_vec_array2_real8(incoherent_inelastic_second_ene_grid);
  clr_obj.clear_vec_array2_real8(incoherent_inelastic_scat_xs_tot_second_ene);
  clr_obj.clear_vec_array3_real8(incoherent_inelastic_scat_angle);
  clr_obj.clear_vec_array3_real8(incoherent_inelastic_scat_xs);
  clr_obj.clear_vec_array3_real8(incoherent_inelastic_integrated_scat_angle);
  clr_obj.clear_vec_array3_real8(incoherent_inelastic_integrated_scat_xs);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Getter
Integer ThermalScatterDataContainer::get_elastic_scat_flg()
{
  return elastic_scat_flg;
}

Real ThermalScatterDataContainer::get_elastic_temp_data_base()
{
  return elastic_temp_data_base;
}

vector<Real> ThermalScatterDataContainer::get_elastic_temp_data()
{
  return elastic_temp_data;
}

vector<Integer> ThermalScatterDataContainer::get_elastic_temp_int()
{
  return elastic_temp_int;
}

vector<Integer> ThermalScatterDataContainer::get_elastic_structure_factor_int_data()
{
  return elastic_structure_factor_int_data;
}

vector<Integer> ThermalScatterDataContainer::get_elastic_structure_factor_range_data()
{
  return elastic_structure_factor_range_data;
}

vector<Real> ThermalScatterDataContainer::get_elastic_structure_factor_ene_data()
{
  return elastic_structure_factor_ene_data;
}

vector<Real> ThermalScatterDataContainer::get_elastic_structure_factor_data_base()
{
  return elastic_structure_factor_data_base;
}

vector<vector<Real> > ThermalScatterDataContainer::get_elastic_structure_factor_data()
{
  return elastic_structure_factor_data;
}

Real ThermalScatterDataContainer::get_elastic_bound_xs()
{
  return elastic_bound_xs;
}

vector<Integer> ThermalScatterDataContainer::get_elastic_debye_waller_int_data()
{
  return elastic_debye_waller_int_data;
}

vector<Integer> ThermalScatterDataContainer::get_elastic_debye_waller_range_data()
{
  return elastic_debye_waller_range_data;
}

vector<Real> ThermalScatterDataContainer::get_elastic_debye_waller_temp_data()
{
  return elastic_debye_waller_temp_data;
}

vector<Real> ThermalScatterDataContainer::get_elastic_debye_waller_data()
{
  return elastic_debye_waller_data;
}

Integer ThermalScatterDataContainer::get_inelastic_temp_flg()
{
  return inelastic_temp_flg;
}

Integer ThermalScatterDataContainer::get_inelastic_symmetric_flg()
{
  return inelastic_symmetric_flg;
}

Integer ThermalScatterDataContainer::get_inelastic_stored_form_flg()
{
  return inelastic_stored_form_flg;
}

Integer ThermalScatterDataContainer::get_non_principal_scat_type_no()
{
  return non_principal_scat_type_no;
}

vector<Real> ThermalScatterDataContainer::get_inelastic_scat_law_coef()
{
  return inelastic_scat_law_coef;
}

vector<vector<Integer> > ThermalScatterDataContainer::get_inelastic_temp_int()
{
  return inelastic_temp_int;
}

vector<Integer> ThermalScatterDataContainer::get_inelastic_beta_int_data()
{
  return inelastic_beta_int_data;
}

vector<Integer> ThermalScatterDataContainer::get_inelastic_beta_range_data()
{
  return inelastic_beta_range_data;
}

vector<Real> ThermalScatterDataContainer::get_inelastic_temp_data_base()
{
  return inelastic_temp_data_base;
}

vector<vector<Real> > ThermalScatterDataContainer::get_inelastic_temp_data()
{
  return inelastic_temp_data;
}

vector<Real> ThermalScatterDataContainer::get_inelastic_beta_data()
{
  return inelastic_beta_data;
}

vector<vector<Integer> > ThermalScatterDataContainer::get_inelastic_scat_law_int_data()
{
  return inelastic_scat_law_int_data;
}

vector<vector<Integer> > ThermalScatterDataContainer::get_inelastic_scat_law_range_data()
{
  return inelastic_scat_law_range_data;
}

vector<vector<Real> > ThermalScatterDataContainer::get_inelastic_scat_law_alpha_data()
{
  return inelastic_scat_law_alpha_data;
}

vector<vector<Real> > ThermalScatterDataContainer::get_inelastic_scat_law_data_base()
{
  return inelastic_scat_law_data_base;
}

vector<vector<vector<Real> > > ThermalScatterDataContainer::get_inelastic_scat_law_data()
{
  return inelastic_scat_law_data;
}

vector<vector<Integer> > ThermalScatterDataContainer::get_inelastic_temp_eff_int_data()
{
  return inelastic_temp_eff_int_data;
}

vector<vector<Integer> > ThermalScatterDataContainer::get_inelastic_temp_eff_range_data()
{
  return inelastic_temp_eff_range_data;
}

vector<vector<Real> > ThermalScatterDataContainer::get_inelastic_temp_eff_temp_data()
{
  return inelastic_temp_eff_temp_data;
}

vector<vector<Real> > ThermalScatterDataContainer::get_inelastic_temp_eff_data()
{
  return inelastic_temp_eff_data;
}

Integer ThermalScatterDataContainer::get_element_no()
{
  return element_no;
}

Integer ThermalScatterDataContainer::get_principal_atom_no()
{
  return principal_atom_no;
}

vector<Real> ThermalScatterDataContainer::get_mat_data_isotope()
{
  return mat_data_isotope;
}

vector<Integer> ThermalScatterDataContainer::get_state_no_isotope()
{
  return state_no_isotope;
}

vector<Real> ThermalScatterDataContainer::get_abundance_isotope()
{
  return abundance_isotope;
}

vector<Real> ThermalScatterDataContainer::get_scat_xs_isotope()
{
  return scat_xs_isotope;
}

vector<Real> ThermalScatterDataContainer::get_mass_isotope()
{
  return mass_isotope;
}


//Getter for cohelent elastic scattering cross section
Integer                         ThermalScatterDataContainer::get_coherent_elastic_bragg_no()
{
  return coherent_elastic_bragg_no;
}

vector<Real8>                   ThermalScatterDataContainer::get_coherent_elastic_ene_grid()
{
  return coherent_elastic_ene_grid;
}

vector<Real8>                   ThermalScatterDataContainer::get_coherent_elastic_scat_xs_tot()
{
  return coherent_elastic_scat_xs_tot;
}

vector<vector<Real8> >          ThermalScatterDataContainer::get_coherent_elastic_scat_xs()
{
  return coherent_elastic_scat_xs;
}


//Getter for incohelent elastic scattering cross section
vector<Real8>                   ThermalScatterDataContainer::get_incoherent_elastic_ene_grid()
{
  return incoherent_elastic_ene_grid;
}

vector<Real8>                   ThermalScatterDataContainer::get_incoherent_elastic_scat_xs()
{
  return incoherent_elastic_scat_xs;
}

vector<vector<Real8> >          ThermalScatterDataContainer::get_incoherent_elastic_scat_angle()
{
  return incoherent_elastic_scat_angle;
}

vector<vector<Real8> >          ThermalScatterDataContainer::get_incoherent_elastic_average_scat_angle()
{
  return incoherent_elastic_average_scat_angle;
}


//Getter for incohelent inelastic scattering cross section
vector<Real8>                   ThermalScatterDataContainer::get_incoherent_inelastic_ene_grid()
{
  return incoherent_inelastic_ene_grid;
}

vector<Real8>                   ThermalScatterDataContainer::get_incoherent_inelastic_ene_grid_scat_xs_tot()
{
  return incoherent_inelastic_ene_grid_scat_xs_tot;
}

vector<Real8>                   ThermalScatterDataContainer::get_incoherent_inelastic_scat_xs_tot()
{
  return incoherent_inelastic_scat_xs_tot;
}

vector<vector<Real8> >          ThermalScatterDataContainer::get_incoherent_inelastic_second_ene_grid()
{
  return incoherent_inelastic_second_ene_grid;
}

vector<vector<Real8> >          ThermalScatterDataContainer::get_incoherent_inelastic_scat_xs_tot_second_ene()
{
  return incoherent_inelastic_scat_xs_tot_second_ene;
}

vector<vector<vector<Real8> > > ThermalScatterDataContainer::get_incoherent_inelastic_scat_angle()
{
  return incoherent_inelastic_scat_angle;
}

vector<vector<vector<Real8> > > ThermalScatterDataContainer::get_incoherent_inelastic_scat_xs()
{
  return incoherent_inelastic_scat_xs;
}

vector<vector<vector<Real8> > > ThermalScatterDataContainer::get_incoherent_inelastic_integrated_scat_angle()
{
  return incoherent_inelastic_integrated_scat_angle;
}

vector<vector<vector<Real8> > > ThermalScatterDataContainer::get_incoherent_inelastic_integrated_scat_xs()
{
  return incoherent_inelastic_integrated_scat_xs;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void ThermalScatterDataContainer::set_elastic_scat_flg( Integer int_data )
{
  elastic_scat_flg = int_data;
}

void ThermalScatterDataContainer::set_elastic_temp_data_base( Real real_data )
{
  elastic_temp_data_base = real_data;
}

void ThermalScatterDataContainer::set_elastic_temp_data( vector<Real> real_vec )
{
  elastic_temp_data = real_vec;
  real_vec.clear();
}

void ThermalScatterDataContainer::set_elastic_temp_int( vector<Integer> int_vec )
{
  elastic_temp_int = int_vec;
  int_vec.clear();
}

void ThermalScatterDataContainer::set_elastic_structure_factor_int_data( vector<Integer> int_vec )
{
  elastic_structure_factor_int_data = int_vec;
  int_vec.clear();
}

void ThermalScatterDataContainer::set_elastic_structure_factor_range_data( vector<Integer> int_vec )
{
  elastic_structure_factor_range_data = int_vec;
  int_vec.clear();
}

void ThermalScatterDataContainer::set_elastic_structure_factor_ene_data( vector<Real> real_vec )
{
  elastic_structure_factor_ene_data = real_vec;
  real_vec.clear();
}

void ThermalScatterDataContainer::set_elastic_structure_factor_data_base( vector<Real> real_vec )
{
  elastic_structure_factor_data_base = real_vec;
  real_vec.clear();
}

void ThermalScatterDataContainer::set_elastic_structure_factor_data( vector<vector<Real> > real_vec )
{
  elastic_structure_factor_data = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void ThermalScatterDataContainer::set_elastic_bound_xs( Real real_data )
{
  elastic_bound_xs = real_data;
}

void ThermalScatterDataContainer::set_elastic_debye_waller_int_data( vector<Integer> int_vec )
{
  elastic_debye_waller_int_data = int_vec;
  int_vec.clear();
}

void ThermalScatterDataContainer::set_elastic_debye_waller_range_data( vector<Integer> int_vec )
{
  elastic_debye_waller_range_data = int_vec;
  int_vec.clear();
}

void ThermalScatterDataContainer::set_elastic_debye_waller_temp_data( vector<Real> real_vec )
{
  elastic_debye_waller_temp_data = real_vec;
  real_vec.clear();
}

void ThermalScatterDataContainer::set_elastic_debye_waller_data( vector<Real> real_vec )
{
  elastic_debye_waller_data = real_vec;
  real_vec.clear();
}

void ThermalScatterDataContainer::set_inelastic_temp_flg( Integer int_data )
{
  inelastic_temp_flg = int_data;
}

void ThermalScatterDataContainer::set_inelastic_symmetric_flg( Integer int_data )
{
  inelastic_symmetric_flg = int_data;
}

void ThermalScatterDataContainer::set_inelastic_stored_form_flg( Integer int_data )
{
  inelastic_stored_form_flg = int_data;
}

void ThermalScatterDataContainer::set_non_principal_scat_type_no( Integer int_data )
{
  non_principal_scat_type_no = int_data;
}

void ThermalScatterDataContainer::set_inelastic_scat_law_coef( vector<Real> real_vec )
{
  inelastic_scat_law_coef = real_vec;
  real_vec.clear();
}

void ThermalScatterDataContainer::set_inelastic_temp_int( vector<vector<Integer> > int_vec )
{
  inelastic_temp_int = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void ThermalScatterDataContainer::set_inelastic_beta_int_data( vector<Integer> int_vec )
{
  inelastic_beta_int_data = int_vec;
  int_vec.clear();
}

void ThermalScatterDataContainer::set_inelastic_beta_range_data( vector<Integer> int_vec )
{
  inelastic_beta_range_data = int_vec;
  int_vec.clear();
}

void ThermalScatterDataContainer::set_inelastic_temp_data_base( vector<Real> real_vec )
{
  inelastic_temp_data_base = real_vec;
  real_vec.clear();
}

void ThermalScatterDataContainer::set_inelastic_temp_data( vector<vector<Real> > real_vec )
{
  inelastic_temp_data = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void ThermalScatterDataContainer::set_inelastic_beta_data( vector<Real> real_vec )
{
  inelastic_beta_data = real_vec;
  real_vec.clear();
}

void ThermalScatterDataContainer::set_inelastic_scat_law_int_data( vector<vector<Integer> > int_vec )
{
  inelastic_scat_law_int_data = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void ThermalScatterDataContainer::set_inelastic_scat_law_range_data( vector<vector<Integer> > int_vec )
{
  inelastic_scat_law_range_data = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void ThermalScatterDataContainer::set_inelastic_scat_law_alpha_data( vector<vector<Real> > real_vec )
{
  inelastic_scat_law_alpha_data = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void ThermalScatterDataContainer::set_inelastic_scat_law_data_base( vector<vector<Real> > real_vec )
{
  inelastic_scat_law_data_base = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void ThermalScatterDataContainer::set_inelastic_scat_law_data( vector<vector<vector<Real> > > real_vec )
{
  inelastic_scat_law_data = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

void ThermalScatterDataContainer::set_inelastic_temp_eff_int_data( vector<vector<Integer> > int_vec )
{
  inelastic_temp_eff_int_data = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void ThermalScatterDataContainer::set_inelastic_temp_eff_range_data( vector<vector<Integer> > int_vec )
{
  inelastic_temp_eff_range_data = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void ThermalScatterDataContainer::set_inelastic_temp_eff_temp_data( vector<vector<Real> > real_vec )
{
  inelastic_temp_eff_temp_data = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void ThermalScatterDataContainer::set_inelastic_temp_eff_data( vector<vector<Real> > real_vec )
{
  inelastic_temp_eff_data = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void ThermalScatterDataContainer::set_element_no( Integer int_data )
{
  element_no = int_data;
}

void ThermalScatterDataContainer::set_principal_atom_no( Integer int_data )
{
  principal_atom_no = int_data;
}

void ThermalScatterDataContainer::set_mat_data_isotope( vector<Real> real_vec )
{
  mat_data_isotope = real_vec;
  real_vec.clear();
}

void ThermalScatterDataContainer::set_state_no_isotope( vector<Integer> int_vec )
{
  state_no_isotope = int_vec;
  int_vec.clear();
}

void ThermalScatterDataContainer::set_abundance_isotope( vector<Real> real_vec )
{
  abundance_isotope = real_vec;
  real_vec.clear();
}

void ThermalScatterDataContainer::set_scat_xs_isotope( vector<Real> real_vec )
{
  scat_xs_isotope = real_vec;
  real_vec.clear();
}

void ThermalScatterDataContainer::set_mass_isotope( vector<Real> real_vec )
{
  mass_isotope = real_vec;
  real_vec.clear();
}


//Setter for cohelent elastic scattering cross section
void ThermalScatterDataContainer::set_coherent_elastic_bragg_no(Integer int_data)
{
  coherent_elastic_bragg_no = int_data;
}

void ThermalScatterDataContainer::set_coherent_elastic_ene_grid(vector<Real8> real_vec)
{
  coherent_elastic_ene_grid = real_vec;
  real_vec.clear();
}

void ThermalScatterDataContainer::set_coherent_elastic_scat_xs_tot(vector<Real8> real_vec)
{
  coherent_elastic_scat_xs_tot = real_vec;
  real_vec.clear();
}

void ThermalScatterDataContainer::set_coherent_elastic_scat_xs(vector<vector<Real8> > real_vec)
{
  coherent_elastic_scat_xs = real_vec;
  clr_obj.clear_vec_array2_real8( real_vec );
}


//Setter for incohelent elastic scattering cross section
void ThermalScatterDataContainer::set_incoherent_elastic_ene_grid(vector<Real8> real_vec)
{
  incoherent_elastic_ene_grid = real_vec;
  real_vec.clear();
}

void ThermalScatterDataContainer::set_incoherent_inelastic_scat_xs_tot(vector<Real8> real_vec)
{
  incoherent_inelastic_scat_xs_tot = real_vec;
  real_vec.clear();
}

void ThermalScatterDataContainer::set_incoherent_elastic_scat_xs(vector<Real8> real_vec)
{
  incoherent_elastic_scat_xs = real_vec;
  real_vec.clear();
}

void ThermalScatterDataContainer::set_incoherent_elastic_scat_angle(vector<vector<Real8> > real_vec)
{
  incoherent_elastic_scat_angle = real_vec;
  clr_obj.clear_vec_array2_real8( real_vec );
}

void ThermalScatterDataContainer::set_incoherent_elastic_average_scat_angle(vector<vector<Real8> > real_vec)
{
  incoherent_elastic_average_scat_angle = real_vec;
  clr_obj.clear_vec_array2_real8( real_vec );
}


//Setter for incohelent inelastic scattering cross section
void ThermalScatterDataContainer::set_incoherent_inelastic_ene_grid(vector<Real8> real_vec)
{
  incoherent_inelastic_ene_grid = real_vec;
  real_vec.clear();
}

void ThermalScatterDataContainer::set_incoherent_inelastic_ene_grid_scat_xs_tot(vector<Real8> real_vec)
{
  incoherent_inelastic_ene_grid_scat_xs_tot = real_vec;
  real_vec.clear();
}

void ThermalScatterDataContainer::set_incoherent_inelastic_second_ene_grid(vector<vector<Real8> > real_vec)
{
  incoherent_inelastic_second_ene_grid = real_vec;
  clr_obj.clear_vec_array2_real8( real_vec );
}

void ThermalScatterDataContainer::set_incoherent_inelastic_scat_xs_tot_second_ene(vector<vector<Real8> > real_vec)
{
  incoherent_inelastic_scat_xs_tot_second_ene = real_vec;
  clr_obj.clear_vec_array2_real8( real_vec );
}

void ThermalScatterDataContainer::set_incoherent_inelastic_scat_angle(vector<vector<vector<Real8> > > real_vec)
{
  incoherent_inelastic_scat_angle = real_vec;
  clr_obj.clear_vec_array3_real8( real_vec );
}

void ThermalScatterDataContainer::set_incoherent_inelastic_scat_xs(vector<vector<vector<Real8> > > real_vec)
{
  incoherent_inelastic_scat_xs = real_vec;
  clr_obj.clear_vec_array3_real8( real_vec );
}

void ThermalScatterDataContainer::set_incoherent_inelastic_integrated_scat_angle(vector<vector<vector<Real8> > > real_vec)
{
  incoherent_inelastic_integrated_scat_angle = real_vec;
  clr_obj.clear_vec_array3_real8( real_vec );
}

void ThermalScatterDataContainer::set_incoherent_inelastic_integrated_scat_xs(vector<vector<vector<Real8> > > real_vec)
{
  incoherent_inelastic_integrated_scat_xs = real_vec;
  clr_obj.clear_vec_array3_real8( real_vec );
}

