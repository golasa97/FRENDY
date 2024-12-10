#ifndef ENERGY_ANGULAR_DATA_CONTAINER_H
#define ENERGY_ANGULAR_DATA_CONTAINER_H

#include "CommonUtils/ErrorManager.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class EnergyAngularDataContainer
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

      Integer                           reaction_type;
      Integer                           angular_repr_flg;
      Integer                           isotropic_flg;
      Integer                           ref_frame_flg;
      Integer                           transformation_matrix_flg;
      vector<Real>                      transformation_matrix;
      vector<Integer>                   angular_int_data_polynomial;
      vector<Integer>                   angular_range_data_polynomial;
      vector<vector<Real> >             angular_data_polynomial;
      vector<Real>                      temp_target_polynomial;
      vector<Real>                      angular_probability_ene_polynomial;
      vector<Integer>                   temp_target_dependence_flg_polynomial;
      vector<Integer>                   angular_int_data_tab;
      vector<Integer>                   angular_range_data_tab;
      vector<vector<Integer> >          angular_probability_int_data_tab;
      vector<vector<Integer> >          angular_probability_range_data_tab;
      vector<vector<Real> >             angular_probability_cos_tab;
      vector<vector<Real> >             angular_probability_data_tab;
      vector<Real>                      temp_target_tab;
      vector<Real>                      angular_probability_ene_tab;
      vector<Integer>                   temp_target_dependence_flg_tab;
      vector<Real>                      upper_ene_limit;
      vector<vector<Integer> >          temp_eff_int_data;
      vector<vector<Integer> >          temp_eff_range_data;
      vector<vector<Real> >             temp_eff_ene_data;
      vector<vector<Real> >             temp_eff_data;
      vector<Integer>                   ene_repr_flg;
      vector<vector<Integer> >          xs_part_int_data;
      vector<vector<Integer> >          xs_part_range_data;
      vector<vector<Real> >             xs_part_ene_data;
      vector<vector<Real> >             xs_part_data;
      vector<vector<Real> >             incident_ene;
      vector<vector<Integer> >          ene_int_data;
      vector<vector<Integer> >          ene_range_data;
      vector<vector<vector<Integer> > > ene_part_int_data;
      vector<vector<vector<Integer> > > ene_part_range_data;
      vector<vector<vector<Real> > >    ene_part_ene_data;
      vector<vector<vector<Real> > >    ene_part_data;
      vector<vector<Integer> >          watt_a_int_data;
      vector<vector<Integer> >          watt_a_range_data;
      vector<vector<Real> >             watt_a_ene_data;
      vector<vector<Real> >             watt_a_data;
      vector<vector<Integer> >          watt_b_int_data;
      vector<vector<Integer> >          watt_b_range_data;
      vector<vector<Real> >             watt_b_ene_data;
      vector<vector<Real> >             watt_b_data;
      vector<Real>                      lower_ene_limit_fis_n;
      vector<Real>                      upper_ene_limit_fis_n;
      vector<vector<Integer> >          temp_max_int_data;
      vector<vector<Integer> >          temp_max_range_data;
      vector<vector<Real> >             temp_max_ene_data;
      vector<vector<Real> >             temp_max_data;

    public:
      //constructor
      EnergyAngularDataContainer(void);

      //destructor
      virtual ~EnergyAngularDataContainer(void);

      void clear();

      //Getter
      Integer                           get_reaction_type();
      Integer                           get_angular_repr_flg();
      Integer                           get_isotropic_flg();
      Integer                           get_ref_frame_flg();
      Integer                           get_transformation_matrix_flg();
      vector<Real>                      get_transformation_matrix();
      vector<Integer>                   get_angular_int_data_polynomial();
      vector<Integer>                   get_angular_range_data_polynomial();
      vector<vector<Real> >             get_angular_data_polynomial();
      vector<Real>                      get_temp_target_polynomial();
      vector<Real>                      get_angular_probability_ene_polynomial();
      vector<Integer>                   get_temp_target_dependence_flg_polynomial();
      vector<Integer>                   get_angular_int_data_tab();
      vector<Integer>                   get_angular_range_data_tab();
      vector<vector<Integer> >          get_angular_probability_int_data_tab();
      vector<vector<Integer> >          get_angular_probability_range_data_tab();
      vector<vector<Real> >             get_angular_probability_cos_tab();
      vector<vector<Real> >             get_angular_probability_data_tab();
      vector<Real>                      get_temp_target_tab();
      vector<Real>                      get_angular_probability_ene_tab();
      vector<Integer>                   get_temp_target_dependence_flg_tab();
      vector<Real>                      get_upper_ene_limit();
      vector<vector<Integer> >          get_temp_eff_int_data();
      vector<vector<Integer> >          get_temp_eff_range_data();
      vector<vector<Real> >             get_temp_eff_ene_data();
      vector<vector<Real> >             get_temp_eff_data();
      vector<Integer>                   get_ene_repr_flg();
      vector<vector<Integer> >          get_xs_part_int_data();
      vector<vector<Integer> >          get_xs_part_range_data();
      vector<vector<Real> >             get_xs_part_ene_data();
      vector<vector<Real> >             get_xs_part_data();
      vector<vector<Real> >             get_incident_ene();
      vector<vector<Integer> >          get_ene_int_data();
      vector<vector<Integer> >          get_ene_range_data();
      vector<vector<vector<Integer> > > get_ene_part_int_data();
      vector<vector<vector<Integer> > > get_ene_part_range_data();
      vector<vector<vector<Real> > >    get_ene_part_ene_data();
      vector<vector<vector<Real> > >    get_ene_part_data();
      vector<vector<Integer> >          get_watt_a_int_data();
      vector<vector<Integer> >          get_watt_a_range_data();
      vector<vector<Real> >             get_watt_a_ene_data();
      vector<vector<Real> >             get_watt_a_data();
      vector<vector<Integer> >          get_watt_b_int_data();
      vector<vector<Integer> >          get_watt_b_range_data();
      vector<vector<Real> >             get_watt_b_ene_data();
      vector<vector<Real> >             get_watt_b_data();
      vector<Real>                      get_lower_ene_limit_fis_n();
      vector<Real>                      get_upper_ene_limit_fis_n();
      vector<vector<Integer> >          get_temp_max_int_data();
      vector<vector<Integer> >          get_temp_max_range_data();
      vector<vector<Real> >             get_temp_max_ene_data();
      vector<vector<Real> >             get_temp_max_data();

      //Setter
      void set_reaction_type( Integer int_data );
      void set_angular_repr_flg( Integer int_data );
      void set_isotropic_flg( Integer int_data );
      void set_ref_frame_flg( Integer int_data );
      void set_transformation_matrix_flg( Integer int_data );
      void set_transformation_matrix( vector<Real> real_vec );
      void set_angular_int_data_polynomial( vector<Integer> int_vec );
      void set_angular_range_data_polynomial( vector<Integer> int_vec );
      void set_angular_data_polynomial( vector<vector<Real> > real_vec );
      void set_temp_target_polynomial( vector<Real> real_vec );
      void set_angular_probability_ene_polynomial( vector<Real> real_vec );
      void set_temp_target_dependence_flg_polynomial( vector<Integer> int_vec );
      void set_angular_int_data_tab( vector<Integer> int_vec );
      void set_angular_range_data_tab( vector<Integer> int_vec );
      void set_angular_probability_int_data_tab( vector<vector<Integer> > int_vec );
      void set_angular_probability_range_data_tab( vector<vector<Integer> > int_vec );
      void set_angular_probability_cos_tab( vector<vector<Real> > real_vec );
      void set_angular_probability_data_tab( vector<vector<Real> > real_vec );
      void set_temp_target_tab( vector<Real> real_vec );
      void set_angular_probability_ene_tab( vector<Real> real_vec );
      void set_temp_target_dependence_flg_tab( vector<Integer> int_vec );
      void set_upper_ene_limit( vector<Real> real_vec );
      void set_temp_eff_int_data( vector<vector<Integer> > int_vec );
      void set_temp_eff_range_data( vector<vector<Integer> > int_vec );
      void set_temp_eff_ene_data( vector<vector<Real> > real_vec );
      void set_temp_eff_data( vector<vector<Real> > real_vec );
      void set_ene_repr_flg( vector<Integer> int_vec );
      void set_xs_part_int_data( vector<vector<Integer> > int_vec );
      void set_xs_part_range_data( vector<vector<Integer> > int_vec );
      void set_xs_part_ene_data( vector<vector<Real> > real_vec );
      void set_xs_part_data( vector<vector<Real> > real_vec );
      void set_incident_ene( vector<vector<Real> > real_vec );
      void set_ene_int_data( vector<vector<Integer> > int_vec );
      void set_ene_range_data( vector<vector<Integer> > int_vec );
      void set_ene_part_int_data( vector<vector<vector<Integer> > > int_vec );
      void set_ene_part_range_data( vector<vector<vector<Integer> > > int_vec );
      void set_ene_part_ene_data( vector<vector<vector<Real> > > real_vec );
      void set_ene_part_data( vector<vector<vector<Real> > > real_vec );
      void set_watt_a_int_data( vector<vector<Integer> > int_vec );
      void set_watt_a_range_data( vector<vector<Integer> > int_vec );
      void set_watt_a_ene_data( vector<vector<Real> > real_vec );
      void set_watt_a_data( vector<vector<Real> > real_vec );
      void set_watt_b_int_data( vector<vector<Integer> > int_vec );
      void set_watt_b_range_data( vector<vector<Integer> > int_vec );
      void set_watt_b_ene_data( vector<vector<Real> > real_vec );
      void set_watt_b_data( vector<vector<Real> > real_vec );
      void set_lower_ene_limit_fis_n( vector<Real> real_vec );
      void set_upper_ene_limit_fis_n( vector<Real> real_vec );
      void set_temp_max_int_data( vector<vector<Integer> > int_vec );
      void set_temp_max_range_data( vector<vector<Integer> > int_vec );
      void set_temp_max_ene_data( vector<vector<Real> > real_vec );
      void set_temp_max_data( vector<vector<Real> > real_vec );
  };
}

#endif //ENERGY_ANGULAR_DATA_CONTAINER_H
