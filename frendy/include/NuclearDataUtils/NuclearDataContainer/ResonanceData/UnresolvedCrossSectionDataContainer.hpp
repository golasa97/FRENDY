#ifndef UNRESOLVED_CROSS_SECTION_DATA_CONTAINER_H
#define UNRESOLVED_CROSS_SECTION_DATA_CONTAINER_H

#include "CommonUtils/ErrorManager.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class UnresolvedCrossSectionDataContainer
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

      Integer      self_shielding_flg;
      Integer      unreso_opt_int;
      Integer      unreso_opt_a;
      Integer      unreso_opt_b;
      Integer      unreso_data_no;
      Real         temp;
      vector<Real> unreso_ene;
      vector<Real> unreso_sig_tot;
      vector<Real> unreso_sig_scat;
      vector<Real> unreso_sig_fis;
      vector<Real> unreso_sig_rad;
      vector<Real> sig_zero;
      vector<vector<vector<Real> > > bondarenko_table;

    public:
      //constructor
      UnresolvedCrossSectionDataContainer(void);

      //destructor
      virtual ~UnresolvedCrossSectionDataContainer(void);

      void clear();

      //Getter
      Integer      get_self_shielding_flg();
      Integer      get_unreso_opt_int();
      Integer      get_unreso_opt_a();
      Integer      get_unreso_opt_b();
      Integer      get_unreso_data_no();
      Real         get_temp();
      vector<Real> get_unreso_ene();
      vector<Real> get_unreso_sig_tot();
      vector<Real> get_unreso_sig_scat();
      vector<Real> get_unreso_sig_fis();
      vector<Real> get_unreso_sig_rad();
      vector<Real> get_sig_zero();
      vector<vector<vector<Real> > > get_bondarenko_table();

      //Setter
      void set_self_shielding_flg( Integer int_data );
      void set_unreso_opt_int( Integer int_data );
      void set_unreso_opt_a( Integer int_data );
      void set_unreso_opt_b( Integer int_data );
      void set_unreso_data_no( Integer int_data );
      void set_temp( Real real_data );
      void set_unreso_ene( vector<Real> real_vec );
      void set_unreso_sig_tot( vector<Real> real_vec );
      void set_unreso_sig_scat( vector<Real> real_vec );
      void set_unreso_sig_fis( vector<Real> real_vec );
      void set_unreso_sig_rad( vector<Real> real_vec );
      void set_sig_zero( vector<Real> real_vec );
      void set_bondarenko_table( vector<vector<vector<Real> > > real_vec );
  };
}

#endif //UNRESOLVED_CROSS_SECTION_DATA_CONTAINER_H
