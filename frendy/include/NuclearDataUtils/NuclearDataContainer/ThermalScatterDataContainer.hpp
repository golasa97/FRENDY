#ifndef THERMAL_SCATTER_DATA_CONTAINER_H
#define THERMAL_SCATTER_DATA_CONTAINER_H

#include "CommonUtils/ErrorManager.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class ThermalScatterDataContainer
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

      Integer                        elastic_scat_flg;
      Real                           elastic_temp_data_base;
      vector<Real>                   elastic_temp_data;
      vector<Integer>                elastic_temp_int;
      vector<Integer>                elastic_structure_factor_int_data;
      vector<Integer>                elastic_structure_factor_range_data;
      vector<Real>                   elastic_structure_factor_ene_data;
      vector<Real>                   elastic_structure_factor_data_base;
      vector<vector<Real> >          elastic_structure_factor_data;
      Real                           elastic_bound_xs;
      vector<Integer>                elastic_debye_waller_int_data;
      vector<Integer>                elastic_debye_waller_range_data;
      vector<Real>                   elastic_debye_waller_temp_data;
      vector<Real>                   elastic_debye_waller_data;
      Integer                        inelastic_temp_flg;
      Integer                        inelastic_symmetric_flg;
      Integer                        inelastic_stored_form_flg;
      Integer                        non_principal_scat_type_no;
      vector<Real>                   inelastic_scat_law_coef;
      vector<vector<Integer> >       inelastic_temp_int;
      vector<Integer>                inelastic_beta_int_data;
      vector<Integer>                inelastic_beta_range_data;
      vector<Real>                   inelastic_temp_data_base;
      vector<vector<Real> >          inelastic_temp_data;
      vector<Real>                   inelastic_beta_data;
      vector<vector<Integer> >       inelastic_scat_law_int_data;
      vector<vector<Integer> >       inelastic_scat_law_range_data;
      vector<vector<Real> >          inelastic_scat_law_alpha_data;
      vector<vector<Real> >          inelastic_scat_law_data_base;
      vector<vector<vector<Real> > > inelastic_scat_law_data;
      vector<vector<Integer> >       inelastic_temp_eff_int_data;
      vector<vector<Integer> >       inelastic_temp_eff_range_data;
      vector<vector<Real> >          inelastic_temp_eff_temp_data;
      vector<vector<Real> >          inelastic_temp_eff_data;
      Integer                         element_no;
      Integer                         principal_atom_no;
      vector<Real>                    mat_data_isotope;
      vector<Integer>                 state_no_isotope;
      vector<Real>                    abundance_isotope;
      vector<Real>                    scat_xs_isotope;
      vector<Real>                    mass_isotope;
    

      //Cohelent elastic scattering cross section data
      Integer                         coherent_elastic_bragg_no;
      vector<Real8>                   coherent_elastic_ene_grid;
      vector<Real8>                   coherent_elastic_scat_xs_tot;
      vector<vector<Real8> >          coherent_elastic_scat_xs;

      //Incohelent elastic scattering cross section data
      vector<Real8>                   incoherent_elastic_ene_grid;
      vector<Real8>                   incoherent_elastic_scat_xs;
      vector<vector<Real8> >          incoherent_elastic_scat_angle;
      vector<vector<Real8> >          incoherent_elastic_average_scat_angle;

      //Incohelent inelastic scattering cross section data
      vector<Real8>                   incoherent_inelastic_ene_grid;
      vector<Real8>                   incoherent_inelastic_ene_grid_scat_xs_tot;
      vector<Real8>                   incoherent_inelastic_scat_xs_tot;
      vector<vector<Real8> >          incoherent_inelastic_second_ene_grid;
      vector<vector<Real8> >          incoherent_inelastic_scat_xs_tot_second_ene;
      vector<vector<vector<Real8> > > incoherent_inelastic_scat_angle;
      vector<vector<vector<Real8> > > incoherent_inelastic_scat_xs;
      vector<vector<vector<Real8> > > incoherent_inelastic_integrated_scat_angle;
      vector<vector<vector<Real8> > > incoherent_inelastic_integrated_scat_xs;

    public:
      //constructor
      ThermalScatterDataContainer(void);

      //destructor
      virtual ~ThermalScatterDataContainer(void);

      void clear();

      //Getter
      Integer                        get_elastic_scat_flg();
      Real                           get_elastic_temp_data_base();
      vector<Real>                   get_elastic_temp_data();
      vector<Integer>                get_elastic_temp_int();
      vector<Integer>                get_elastic_structure_factor_int_data();
      vector<Integer>                get_elastic_structure_factor_range_data();
      vector<Real>                   get_elastic_structure_factor_ene_data();
      vector<Real>                   get_elastic_structure_factor_data_base();
      vector<vector<Real> >          get_elastic_structure_factor_data();
      Real                           get_elastic_bound_xs();
      vector<Integer>                get_elastic_debye_waller_int_data();
      vector<Integer>                get_elastic_debye_waller_range_data();
      vector<Real>                   get_elastic_debye_waller_temp_data();
      vector<Real>                   get_elastic_debye_waller_data();
      Integer                        get_inelastic_temp_flg();
      Integer                        get_inelastic_symmetric_flg();
      Integer                        get_inelastic_stored_form_flg();
      Integer                        get_non_principal_scat_type_no();
      vector<Real>                   get_inelastic_scat_law_coef();
      vector<vector<Integer> >       get_inelastic_temp_int();
      vector<Integer>                get_inelastic_beta_int_data();
      vector<Integer>                get_inelastic_beta_range_data();
      vector<Real>                   get_inelastic_temp_data_base();
      vector<vector<Real> >          get_inelastic_temp_data();
      vector<Real>                   get_inelastic_beta_data();
      vector<vector<Integer> >       get_inelastic_scat_law_int_data();
      vector<vector<Integer> >       get_inelastic_scat_law_range_data();
      vector<vector<Real> >          get_inelastic_scat_law_alpha_data();
      vector<vector<Real> >          get_inelastic_scat_law_data_base();
      vector<vector<vector<Real> > > get_inelastic_scat_law_data();
      vector<vector<Integer> >       get_inelastic_temp_eff_int_data();
      vector<vector<Integer> >       get_inelastic_temp_eff_range_data();
      vector<vector<Real> >          get_inelastic_temp_eff_temp_data();
      vector<vector<Real> >          get_inelastic_temp_eff_data();
      Integer                        get_element_no();
      Integer                        get_principal_atom_no();
      vector<Real>                   get_mat_data_isotope();
      vector<Integer>                get_state_no_isotope();
      vector<Real>                   get_abundance_isotope();
      vector<Real>                   get_scat_xs_isotope();
      vector<Real>                   get_mass_isotope();

      Integer                         get_coherent_elastic_bragg_no();
      vector<Real8>                   get_coherent_elastic_ene_grid();
      vector<Real8>                   get_coherent_elastic_scat_xs_tot();
      vector<vector<Real8> >          get_coherent_elastic_scat_xs();

      vector<Real8>                   get_incoherent_elastic_ene_grid();
      vector<Real8>                   get_incoherent_elastic_scat_xs();
      vector<vector<Real8> >          get_incoherent_elastic_scat_angle();
      vector<vector<Real8> >          get_incoherent_elastic_average_scat_angle();

      vector<Real8>                   get_incoherent_inelastic_ene_grid();
      vector<Real8>                   get_incoherent_inelastic_ene_grid_scat_xs_tot();
      vector<Real8>                   get_incoherent_inelastic_scat_xs_tot();
      vector<vector<Real8> >          get_incoherent_inelastic_second_ene_grid();
      vector<vector<Real8> >          get_incoherent_inelastic_scat_xs_tot_second_ene();
      vector<vector<vector<Real8> > > get_incoherent_inelastic_scat_angle();
      vector<vector<vector<Real8> > > get_incoherent_inelastic_scat_xs();
      vector<vector<vector<Real8> > > get_incoherent_inelastic_integrated_scat_angle();
      vector<vector<vector<Real8> > > get_incoherent_inelastic_integrated_scat_xs();

      //Setter
      void set_elastic_scat_flg( Integer int_data );
      void set_elastic_temp_data_base( Real real_data );
      void set_elastic_temp_data( vector<Real> real_vec );
      void set_elastic_temp_int( vector<Integer> int_vec );
      void set_elastic_structure_factor_int_data( vector<Integer> int_vec );
      void set_elastic_structure_factor_range_data( vector<Integer> int_vec );
      void set_elastic_structure_factor_ene_data( vector<Real> real_vec );
      void set_elastic_structure_factor_data_base( vector<Real> real_vec );
      void set_elastic_structure_factor_data( vector<vector<Real> > real_vec );
      void set_elastic_bound_xs( Real real_data );
      void set_elastic_debye_waller_int_data( vector<Integer> int_vec );
      void set_elastic_debye_waller_range_data( vector<Integer> int_vec );
      void set_elastic_debye_waller_temp_data( vector<Real> real_vec );
      void set_elastic_debye_waller_data( vector<Real> real_vec );
      void set_inelastic_temp_flg( Integer int_data );
      void set_inelastic_symmetric_flg( Integer int_data );
      void set_inelastic_stored_form_flg( Integer int_data );
      void set_non_principal_scat_type_no( Integer int_data );
      void set_inelastic_scat_law_coef( vector<Real> real_vec );
      void set_inelastic_temp_int( vector<vector<Integer> > int_vec );
      void set_inelastic_beta_int_data( vector<Integer> int_vec );
      void set_inelastic_beta_range_data( vector<Integer> int_vec );
      void set_inelastic_temp_data_base( vector<Real> real_vec );
      void set_inelastic_temp_data( vector<vector<Real> > real_vec );
      void set_inelastic_beta_data( vector<Real> real_vec );
      void set_inelastic_scat_law_int_data( vector<vector<Integer> > int_vec );
      void set_inelastic_scat_law_range_data( vector<vector<Integer> > int_vec );
      void set_inelastic_scat_law_alpha_data( vector<vector<Real> > real_vec );
      void set_inelastic_scat_law_data_base( vector<vector<Real> > real_vec );
      void set_inelastic_scat_law_data( vector<vector<vector<Real> > > real_vec );
      void set_inelastic_temp_eff_int_data( vector<vector<Integer> > int_vec );
      void set_inelastic_temp_eff_range_data( vector<vector<Integer> > int_vec );
      void set_inelastic_temp_eff_temp_data( vector<vector<Real> > real_vec );
      void set_inelastic_temp_eff_data( vector<vector<Real> > real_vec );
      void set_element_no( Integer int_data );
      void set_principal_atom_no( Integer int_data );
      void set_mat_data_isotope( vector<Real> real_vec );
      void set_state_no_isotope( vector<Integer> int_vec );
      void set_abundance_isotope( vector<Real> real_vec );
      void set_scat_xs_isotope( vector<Real> real_vec );
      void set_mass_isotope( vector<Real> real_vec );

      void set_coherent_elastic_bragg_no(Integer int_data);
      void set_coherent_elastic_ene_grid(vector<Real8> real_vec);
      void set_coherent_elastic_scat_xs_tot(vector<Real8> real_vec);
      void set_coherent_elastic_scat_xs(vector<vector<Real8> > real_vec);

      void set_incoherent_elastic_ene_grid(vector<Real8> real_vec);
      void set_incoherent_elastic_scat_xs(vector<Real8> real_vec);
      void set_incoherent_elastic_scat_angle(vector<vector<Real8> > real_vec);
      void set_incoherent_elastic_average_scat_angle(vector<vector<Real8> > real_vec);

      void set_incoherent_inelastic_ene_grid(vector<Real8> real_vec);
      void set_incoherent_inelastic_ene_grid_scat_xs_tot(vector<Real8> real_vec);
      void set_incoherent_inelastic_scat_xs_tot(vector<Real8> real_vec);
      void set_incoherent_inelastic_second_ene_grid(vector<vector<Real8> > real_vec);
      void set_incoherent_inelastic_scat_xs_tot_second_ene(vector<vector<Real8> > real_vec);
      void set_incoherent_inelastic_scat_angle(vector<vector<vector<Real8> > > real_vec);
      void set_incoherent_inelastic_scat_xs(vector<vector<vector<Real8> > > real_vec);
      void set_incoherent_inelastic_integrated_scat_angle(vector<vector<vector<Real8> > > real_vec);
      void set_incoherent_inelastic_integrated_scat_xs(vector<vector<vector<Real8> > > real_vec);
  };
}

#endif //THERMAL_SCATTER_DATA_CONTAINER_H
