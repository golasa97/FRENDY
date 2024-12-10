#ifndef COVARIANCE_ENERGY_ANGULAR_DATA_CONTAINER_H
#define COVARIANCE_ENERGY_ANGULAR_DATA_CONTAINER_H

#include "CommonUtils/ErrorManager.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class CovarianceEnergyAngularDataContainer
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

      Integer                                                   reaction_type;
      Integer                                                   angular_repr_flg;
      vector<Integer>                                           mat_no_target;
      vector<Integer>                                           reaction_type_target;
      vector<vector<vector<Integer> > >                         legendre_coef_index;
      vector<vector<vector<Integer> > >                         legendre_coef_index_target;
      vector<vector<vector<Integer> > >                         ref_frame_flg;
      vector<vector<vector<vector<Integer> > > >                symmetric_flg_angle;
      vector<vector<vector<vector<Integer> > > >                cov_matrix_data_flg_angle;
      vector<vector<vector<vector<vector<Real> > > > >          cov_matrix_ene_angle_k;
      vector<vector<vector<vector<vector<vector<Real> > > > > > cov_matrix_coef_angle_k;
      vector<vector<vector<vector<vector<Real> > > > >          cov_matrix_ene_angle_l;
      vector<vector<vector<vector<vector<vector<Real> > > > > > cov_matrix_coef_angle_l;
      vector<Real>                                              ene_range_low;
      vector<Real>                                              ene_range_high;
      vector<Integer>                                           symmetric_flg_ene;
      vector<Integer>                                           cov_matrix_data_flg_ene;
      vector<vector<Real> >                                     cov_matrix_ene_data;
      vector<vector<vector<Real> > >                            cov_matrix_data;

    public:
      //constructor
      CovarianceEnergyAngularDataContainer(void);

      //destructor
      virtual ~CovarianceEnergyAngularDataContainer(void);

      void clear();

      //Getter
      Integer                                                   get_reaction_type();
      Integer                                                   get_angular_repr_flg();
      vector<Integer>                                           get_mat_no_target();
      vector<Integer>                                           get_reaction_type_target();
      vector<vector<vector<Integer> > >                         get_legendre_coef_index();
      vector<vector<vector<Integer> > >                         get_legendre_coef_index_target();
      vector<vector<vector<Integer> > >                         get_ref_frame_flg();
      vector<vector<vector<vector<Integer> > > >                get_symmetric_flg_angle();
      vector<vector<vector<vector<Integer> > > >                get_cov_matrix_data_flg_angle();
      vector<vector<vector<vector<vector<Real> > > > >          get_cov_matrix_ene_angle_k();
      vector<vector<vector<vector<vector<vector<Real> > > > > > get_cov_matrix_coef_angle_k();
      vector<vector<vector<vector<vector<Real> > > > >          get_cov_matrix_ene_angle_l();
      vector<vector<vector<vector<vector<vector<Real> > > > > > get_cov_matrix_coef_angle_l();
      vector<Real>                                              get_ene_range_low();
      vector<Real>                                              get_ene_range_high();
      vector<Integer>                                           get_symmetric_flg_ene();
      vector<Integer>                                           get_cov_matrix_data_flg_ene();
      vector<vector<Real> >                                     get_cov_matrix_ene_data();
      vector<vector<vector<Real> > >                            get_cov_matrix_data();

      //Setter
      void set_reaction_type( Integer int_data );
      void set_angular_repr_flg( Integer int_data );
      void set_mat_no_target( vector<Integer> int_vec );
      void set_reaction_type_target( vector<Integer> int_vec );
      void set_legendre_coef_index( vector<vector<vector<Integer> > > int_vec );
      void set_legendre_coef_index_target( vector<vector<vector<Integer> > > int_vec );
      void set_ref_frame_flg( vector<vector<vector<Integer> > > int_vec );
      void set_symmetric_flg_angle( vector<vector<vector<vector<Integer> > > > int_vec );
      void set_cov_matrix_data_flg_angle( vector<vector<vector<vector<Integer> > > > int_vec );
      void set_cov_matrix_ene_angle_k( vector<vector<vector<vector<vector<Real> > > > > real_vec );
      void set_cov_matrix_coef_angle_k( vector<vector<vector<vector<vector<vector<Real> > > > > > real_vec );
      void set_cov_matrix_ene_angle_l( vector<vector<vector<vector<vector<Real> > > > > real_vec );
      void set_cov_matrix_coef_angle_l( vector<vector<vector<vector<vector<vector<Real> > > > > > real_vec );
      void set_ene_range_low( vector<Real> real_vec );
      void set_ene_range_high( vector<Real> real_vec );
      void set_symmetric_flg_ene( vector<Integer> int_vec );
      void set_cov_matrix_data_flg_ene( vector<Integer> int_vec );
      void set_cov_matrix_ene_data( vector<vector<Real> > real_vec );
      void set_cov_matrix_data( vector<vector<vector<Real> > > real_vec );
  };
}

#endif //COVARIANCE_ENERGY_ANGULAR_DATA_CONTAINER_H
