#ifndef OTHER_NUCLEAR_DATA_CONTAINER_H
#define OTHER_NUCLEAR_DATA_CONTAINER_H

#include "CommonUtils/ErrorManager.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class OtherNuclearDataContainer
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

      Integer               reaction_type;
      Real                  atomic_no;
      vector<Integer>       scat_func_int_data;
      vector<Integer>       scat_func_range_data;
      vector<Real>          scat_func_recoil_electron_data;
      vector<Real>          scat_func_data;
      vector<Integer>       form_factor_int_data;
      vector<Integer>       form_factor_range_data;
      vector<Real>          form_factor_ene_data;
      vector<Real>          form_factor_data;
      vector<Real>          first_subshell_type;
      vector<vector<Real> > second_subshell_type;
      vector<vector<Real> > third_subshell_type;
      vector<Real>          binding_ene_subshell;
      vector<Real>          electron_no;
      vector<vector<Real> > trans_probability;
      vector<vector<Real> > trans_ene;

    public:
      //constructor
      OtherNuclearDataContainer(void);

      //destructor
      virtual ~OtherNuclearDataContainer(void);

      void clear();

      //Getter
      Integer               get_reaction_type();
      Real                  get_atomic_no();
      vector<Integer>       get_scat_func_int_data();
      vector<Integer>       get_scat_func_range_data();
      vector<Real>          get_scat_func_recoil_electron_data();
      vector<Real>          get_scat_func_data();
      vector<Integer>       get_form_factor_int_data();
      vector<Integer>       get_form_factor_range_data();
      vector<Real>          get_form_factor_ene_data();
      vector<Real>          get_form_factor_data();
      vector<Real>          get_first_subshell_type();
      vector<vector<Real> > get_second_subshell_type();
      vector<vector<Real> > get_third_subshell_type();
      vector<Real>          get_binding_ene_subshell();
      vector<Real>          get_electron_no();
      vector<vector<Real> > get_trans_probability();
      vector<vector<Real> > get_trans_ene();

      //Setter
      void set_reaction_type( Integer int_data );
      void set_atomic_no( Real real_data );
      void set_scat_func_int_data( vector<Integer> int_vec );
      void set_scat_func_range_data( vector<Integer> int_vec );
      void set_scat_func_recoil_electron_data( vector<Real> real_vec );
      void set_scat_func_data( vector<Real> real_vec );
      void set_form_factor_int_data( vector<Integer> int_vec );
      void set_form_factor_range_data( vector<Integer> int_vec );
      void set_form_factor_ene_data( vector<Real> real_vec );
      void set_form_factor_data( vector<Real> real_vec );
      void set_first_subshell_type( vector<Real> real_vec );
      void set_second_subshell_type( vector<vector<Real> > real_vec );
      void set_third_subshell_type( vector<vector<Real> > real_vec );
      void set_binding_ene_subshell( vector<Real> real_vec );
      void set_electron_no( vector<Real> real_vec );
      void set_trans_probability( vector<vector<Real> > real_vec );
      void set_trans_ene( vector<vector<Real> > real_vec );
  };
}

#endif //OTHER_NUCLEAR_DATA_CONTAINER_H
