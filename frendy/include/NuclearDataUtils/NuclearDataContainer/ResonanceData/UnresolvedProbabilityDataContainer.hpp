#ifndef UNRESOLVED_PROBABILITY_DATA_CONTAINER_H
#define UNRESOLVED_PROBABILITY_DATA_CONTAINER_H

#include "CommonUtils/ErrorManager.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class UnresolvedProbabilityDataContainer
  {
    private:
      ErrorManager  err_obj;
      VectorClearer clr_obj;

      Integer                        comp_flg_inela; //competition flg (z,n)
      Integer                        comp_flg_abs;
      Integer                        prob_int;
      Integer                        prob_bin_no;
      Integer                        self_shielding_flg;
      Integer                        comp_flg; //competition flag
      Integer                        prob_ene_no;
      Real                           temp;
      vector<Real>                   prob_ene;
      vector<vector<Real> >          prob_heat;
      vector<vector<Real> >          prob_table_sample_no;
      vector<vector<vector<Real> > > prob_table;

    public:
      //constructor
      UnresolvedProbabilityDataContainer(void);

      //destructor
      virtual ~UnresolvedProbabilityDataContainer(void);

      void clear();

      //Getter
      Integer                        get_comp_flg_inela();
      Integer                        get_comp_flg_abs();
      Integer                        get_prob_int();
      Integer                        get_prob_bin_no();
      Integer                        get_self_shielding_flg();
      Integer                        get_comp_flg();
      Integer                        get_prob_ene_no();
      Real                           get_temp();
      vector<Real>                   get_prob_ene();
      vector<vector<Real> >          get_prob_heat();
      vector<vector<Real> >          get_prob_table_sample_no();
      vector<vector<vector<Real> > > get_prob_table();

      //Setter
      void set_comp_flg_inela( Integer int_data );
      void set_comp_flg_abs( Integer int_data );
      void set_prob_int( Integer int_data );
      void set_prob_bin_no( Integer int_data );
      void set_self_shielding_flg( Integer int_data );
      void set_comp_flg( Integer int_data );
      void set_prob_ene_no( Integer int_data );
      void set_temp( Real real_data );
      void set_prob_ene( vector<Real> real_vec );
      void set_prob_heat( vector<vector<Real> > real_vec );
      void set_prob_table_sample_no( vector<vector<Real> > real_vec );
      void set_prob_table( vector<vector<vector<Real> > > real_vec );
  };
}

#endif //UNRESOLVED_PROBABILITY_DATA_CONTAINER_H
