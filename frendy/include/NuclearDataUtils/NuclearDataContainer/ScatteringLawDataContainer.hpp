#ifndef SCATTERING_LAW_DATA_CONTAINER_H
#define SCATTERING_LAW_DATA_CONTAINER_H

#include "CommonUtils/ErrorManager.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class ScatteringLawDataContainer
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

      Integer                        elastic_scat_flg;
      Real                           elastic_temp_ori;
      vector<Real>                   elastic_temp_target;
      vector<Integer>                elastic_temp_int;
      vector<Integer>                elastic_scat_law_int_data;
      vector<Integer>                elastic_scat_law_range_data;
      vector<Real>                   elastic_scat_law_ene_data;
      vector<Real>                   elastic_scat_law_data_ori;
      vector<vector<Real> >          elastic_scat_law_data_target;
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
      vector<Real>                   inelastic_temp_ori;
      vector<vector<Real> >          inelastic_temp_target;
      vector<Real>                   inelastic_beta_data;
      vector<vector<Integer> >       inelastic_scat_law_int_data;
      vector<vector<Integer> >       inelastic_scat_law_range_data;
      vector<vector<Real> >          inelastic_scat_law_alpha_data;
      vector<vector<Real> >          inelastic_scat_law_data_ori;
      vector<vector<vector<Real> > > inelastic_scat_law_data_target;
      vector<vector<Integer> >       inelastic_temp_eff_int_data;
      vector<vector<Integer> >       inelastic_temp_eff_range_data;
      vector<vector<Real> >          inelastic_temp_eff_temp_data;
      vector<vector<Real> >          inelastic_temp_eff_data;

    public:
      //constructor
      ScatteringLawDataContainer(void);

      //destructor
      virtual ~ScatteringLawDataContainer(void);

      void clear();

      //Getter
      Integer                        get_elastic_scat_flg();
      Real                           get_elastic_temp_ori();
      vector<Real>                   get_elastic_temp_target();
      vector<Integer>                get_elastic_temp_int();
      vector<Integer>                get_elastic_scat_law_int_data();
      vector<Integer>                get_elastic_scat_law_range_data();
      vector<Real>                   get_elastic_scat_law_ene_data();
      vector<Real>                   get_elastic_scat_law_data_ori();
      vector<vector<Real> >          get_elastic_scat_law_data_target();
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
      vector<Real>                   get_inelastic_temp_ori();
      vector<vector<Real> >          get_inelastic_temp_target();
      vector<Real>                   get_inelastic_beta_data();
      vector<vector<Integer> >       get_inelastic_scat_law_int_data();
      vector<vector<Integer> >       get_inelastic_scat_law_range_data();
      vector<vector<Real> >          get_inelastic_scat_law_alpha_data();
      vector<vector<Real> >          get_inelastic_scat_law_data_ori();
      vector<vector<vector<Real> > > get_inelastic_scat_law_data_target();
      vector<vector<Integer> >       get_inelastic_temp_eff_int_data();
      vector<vector<Integer> >       get_inelastic_temp_eff_range_data();
      vector<vector<Real> >          get_inelastic_temp_eff_temp_data();
      vector<vector<Real> >          get_inelastic_temp_eff_data();

      //Setter
      void set_elastic_scat_flg( Integer int_data );
      void set_elastic_temp_ori( Real real_data );
      void set_elastic_temp_target( vector<Real> real_vec );
      void set_elastic_temp_int( vector<Integer> int_vec );
      void set_elastic_scat_law_int_data( vector<Integer> int_vec );
      void set_elastic_scat_law_range_data( vector<Integer> int_vec );
      void set_elastic_scat_law_ene_data( vector<Real> real_vec );
      void set_elastic_scat_law_data_ori( vector<Real> real_vec );
      void set_elastic_scat_law_data_target( vector<vector<Real> > real_vec );
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
      void set_inelastic_temp_ori( vector<Real> real_vec );
      void set_inelastic_temp_target( vector<vector<Real> > real_vec );
      void set_inelastic_beta_data( vector<Real> real_vec );
      void set_inelastic_scat_law_int_data( vector<vector<Integer> > int_vec );
      void set_inelastic_scat_law_range_data( vector<vector<Integer> > int_vec );
      void set_inelastic_scat_law_alpha_data( vector<vector<Real> > real_vec );
      void set_inelastic_scat_law_data_ori( vector<vector<Real> > real_vec );
      void set_inelastic_scat_law_data_target( vector<vector<vector<Real> > > real_vec );
      void set_inelastic_temp_eff_int_data( vector<vector<Integer> > int_vec );
      void set_inelastic_temp_eff_range_data( vector<vector<Integer> > int_vec );
      void set_inelastic_temp_eff_temp_data( vector<vector<Real> > real_vec );
      void set_inelastic_temp_eff_data( vector<vector<Real> > real_vec );
  };
}

#endif //SCATTERING_LAW_DATA_CONTAINER_H
