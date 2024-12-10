#ifndef PROBABILITY_TABLE_DATA_CONTAINER_H
#define PROBABILITY_TABLE_DATA_CONTAINER_H

#include "CommonUtils/ErrorManager.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class ProbabilityTableDataContainer
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

      Real8                           ene_grid;
      Integer                         nrest;
      vector<Real8>                   temp, sig_zero, xs_unreso, xs_back, xs_tot_min, xs_tot_max;
      vector<vector<Real8> >          xs_tot_table, xs_inf_ave, xs_inf_var, prob_table_sample_no,
                                      prob_heat;
      vector<vector<vector<Real8> > > prob_table, prob_table_mod, bondarenko_table,
                                      bondarenko_xs_direct, bondarenko_xs_prob;

    public:
      //constructor
      ProbabilityTableDataContainer(void);

      //destructor
      virtual ~ProbabilityTableDataContainer(void);

      void clear();

      //Getter
      Real8                           get_ene_grid();
      Integer                         get_nrest();
      vector<Real8>                   get_temp();
      vector<Real8>                   get_sig_zero();
      vector<Real8>                   get_xs_unreso();
      vector<Real8>                   get_xs_back();
      vector<Real8>                   get_xs_tot_min();
      vector<Real8>                   get_xs_tot_max();
      vector<vector<Real8> >          get_xs_tot_table();
      vector<vector<Real8> >          get_xs_inf_ave();
      vector<vector<Real8> >          get_xs_inf_var();
      vector<vector<Real8> >          get_prob_table_sample_no();
      vector<vector<Real8> >          get_prob_heat();
      vector<vector<vector<Real8> > > get_prob_table();
      vector<vector<vector<Real8> > > get_prob_table_mod(); //devided by bondarenko table
      vector<vector<vector<Real8> > > get_bondarenko_table();
      vector<vector<vector<Real8> > > get_bondarenko_xs_direct();
      vector<vector<vector<Real8> > > get_bondarenko_xs_prob();

      //Setter
      void set_ene_grid( Real8 real_val );
      void set_nrest( Integer int_val );
      void set_temp( vector<Real8> real_vec );
      void set_sig_zero( vector<Real8> real_vec );
      void set_xs_unreso( vector<Real8> real_vec );
      void set_xs_back( vector<Real8> real_vec );
      void set_xs_tot_min( vector<Real8> real_vec );
      void set_xs_tot_max( vector<Real8> real_vec );
      void set_xs_tot_table( vector<vector<Real8> > real_vec );
      void set_xs_inf_ave( vector<vector<Real8> > real_vec );
      void set_xs_inf_var( vector<vector<Real8> > real_vec );
      void set_prob_table_sample_no( vector<vector<Real8> > real_vec );
      void set_prob_heat( vector<vector<Real8> > real_vec );
      void set_prob_table( vector<vector<vector<Real8> > > real_vec );
      void set_prob_table_mod( vector<vector<vector<Real8> > > real_vec ); //devided by bondarenko table
      void set_bondarenko_table( vector<vector<vector<Real8> > > real_vec );
      void set_bondarenko_xs_direct( vector<vector<vector<Real8> > > real_vec );
      void set_bondarenko_xs_prob( vector<vector<vector<Real8> > > real_vec );
  };
}

#endif //PROBABILITY_TABLE_DATA_CONTAINER_H
