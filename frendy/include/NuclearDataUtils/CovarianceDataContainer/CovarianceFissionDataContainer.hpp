#ifndef COVARIANCE_FISSION_DATA_CONTAINER_H
#define COVARIANCE_FISSION_DATA_CONTAINER_H

#include "CommonUtils/ErrorManager.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class CovarianceFissionDataContainer
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

      Integer                                 reaction_type;
      Integer                                 reaction_type_target;
      vector<Real>                            target_second_file_no;
      vector<Real>                            target_second_excited_state;
      vector<Integer>                         target_second_mat_no;
      vector<Integer>                         target_second_reaction_type;
      vector<vector<Integer> >                cov_matrix_flg;
      vector<vector<Real> >                   xs_ene_range_low;
      vector<vector<Real> >                   xs_ene_range_high;
      vector<vector<vector<Real> > >          xs_contribute_coef;
      vector<vector<vector<Real> > >          xs_contribute_reaction_type;
      vector<vector<Integer> >                relevant_mat_no;
      vector<vector<Integer> >                relevant_reaction_type;
      vector<vector<Real> >                   relevant_file_no;
      vector<vector<Real> >                   relevant_level_no;
      vector<vector<vector<Real> > >          relevant_ene_data;
      vector<vector<vector<Real> > >          relevant_weight;
      vector<vector<Integer> >                cov_matrix_data_flg;
      vector<vector<Integer> >                symmetric_coef_flg;
      vector<vector<vector<Real> > >          cov_matrix_ene_k;
      vector<vector<vector<vector<Real> > > > cov_matrix_coef_k;
      vector<vector<vector<Real> > >          cov_matrix_ene_l;
      vector<vector<vector<vector<Real> > > > cov_matrix_coef_l;

    public:
      //constructor
      CovarianceFissionDataContainer(void);

      //destructor
      virtual ~CovarianceFissionDataContainer(void);

      void clear();

      //Getter
      Integer                                 get_reaction_type();
      Integer                                 get_reaction_type_target();
      vector<Real>                            get_target_second_file_no();
      vector<Real>                            get_target_second_excited_state();
      vector<Integer>                         get_target_second_mat_no();
      vector<Integer>                         get_target_second_reaction_type();
      vector<vector<Integer> >                get_cov_matrix_flg();
      vector<vector<Real> >                   get_xs_ene_range_low();
      vector<vector<Real> >                   get_xs_ene_range_high();
      vector<vector<vector<Real> > >          get_xs_contribute_coef();
      vector<vector<vector<Real> > >          get_xs_contribute_reaction_type();
      vector<vector<Integer> >                get_relevant_mat_no();
      vector<vector<Integer> >                get_relevant_reaction_type();
      vector<vector<Real> >                   get_relevant_file_no();
      vector<vector<Real> >                   get_relevant_level_no();
      vector<vector<vector<Real> > >          get_relevant_ene_data();
      vector<vector<vector<Real> > >          get_relevant_weight();
      vector<vector<Integer> >                get_cov_matrix_data_flg();
      vector<vector<Integer> >                get_symmetric_coef_flg();
      vector<vector<vector<Real> > >          get_cov_matrix_ene_k();
      vector<vector<vector<vector<Real> > > > get_cov_matrix_coef_k();
      vector<vector<vector<Real> > >          get_cov_matrix_ene_l();
      vector<vector<vector<vector<Real> > > > get_cov_matrix_coef_l();

      //Setter
      void set_reaction_type( Integer int_data );
      void set_reaction_type_target( Integer int_data );
      void set_target_second_file_no( vector<Real> real_vec );
      void set_target_second_excited_state( vector<Real> real_vec );
      void set_target_second_mat_no( vector<Integer> int_vec );
      void set_target_second_reaction_type( vector<Integer> int_vec );
      void set_cov_matrix_flg( vector<vector<Integer> > int_vec );
      void set_xs_ene_range_low( vector<vector<Real> > real_vec );
      void set_xs_ene_range_high( vector<vector<Real> > real_vec );
      void set_xs_contribute_coef( vector<vector<vector<Real> > > real_vec );
      void set_xs_contribute_reaction_type( vector<vector<vector<Real> > > real_vec );
      void set_relevant_mat_no( vector<vector<Integer> > int_vec );
      void set_relevant_reaction_type( vector<vector<Integer> > int_vec );
      void set_relevant_file_no( vector<vector<Real> > real_vec );
      void set_relevant_level_no( vector<vector<Real> > real_vec );
      void set_relevant_ene_data( vector<vector<vector<Real> > > real_vec );
      void set_relevant_weight( vector<vector<vector<Real> > > real_vec );
      void set_cov_matrix_data_flg( vector<vector<Integer> > int_vec );
      void set_symmetric_coef_flg( vector<vector<Integer> > int_vec );
      void set_cov_matrix_ene_k( vector<vector<vector<Real> > > real_vec );
      void set_cov_matrix_coef_k( vector<vector<vector<vector<Real> > > > real_vec );
      void set_cov_matrix_ene_l( vector<vector<vector<Real> > > real_vec );
      void set_cov_matrix_coef_l( vector<vector<vector<vector<Real> > > > real_vec );
  };
}

#endif //COVARIANCE_FISSION_DATA_CONTAINER_H
