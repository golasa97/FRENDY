#ifndef UNRESOLVED_RESONANCE_DATA_CONTAINER_H
#define UNRESOLVED_RESONANCE_DATA_CONTAINER_H

#include "CommonUtils/ErrorManager.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class UnresolvedResonanceDataContainer
  {
    private:
      ErrorManager  err_obj;
      VectorClearer clr_obj;

      Integer                        fis_width_flg;
      Integer                        xs_formula_flg;
      Integer                        self_shielding_flg;
      vector<vector<vector<Real> > > level_spacing;
      vector<vector<Real> >          j_value_abs;
      vector<vector<Real> >          freedom_n;
      vector<vector<vector<Real> > > ave_gam_width_n;
      vector<vector<vector<Real> > > ave_gam_width_rad;
      vector<vector<vector<Real> > > ene_unreso;
      vector<vector<Integer> >       freedom_fis_int;
      vector<vector<vector<Real> > > ave_gam_width_fis;
      vector<vector<Integer> >       unreso_int_data;
      vector<vector<Real> >          freedom_comp;
      vector<vector<Real> >          freedom_rad;
      vector<vector<Real> >          freedom_fis;
      vector<vector<vector<Real> > > ave_gam_width_comp;

    public:
      //constructor
      UnresolvedResonanceDataContainer(void);

      //destructor
      virtual ~UnresolvedResonanceDataContainer(void);

      void clear();

      //Getter
      Integer                        get_fis_width_flg();
      Integer                        get_xs_formula_flg();
      Integer                        get_self_shielding_flg();
      vector<vector<vector<Real> > > get_level_spacing();
      vector<vector<Real> >          get_j_value_abs();
      vector<vector<Real> >          get_freedom_n();
      vector<vector<vector<Real> > > get_ave_gam_width_n();
      vector<vector<vector<Real> > > get_ave_gam_width_rad();
      vector<vector<vector<Real> > > get_ene_unreso();
      vector<vector<Integer> >       get_freedom_fis_int();
      vector<vector<vector<Real> > > get_ave_gam_width_fis();
      vector<vector<Integer> >       get_unreso_int_data();
      vector<vector<Real> >          get_freedom_comp();
      vector<vector<Real> >          get_freedom_rad();
      vector<vector<Real> >          get_freedom_fis();
      vector<vector<vector<Real> > > get_ave_gam_width_comp();

      //Setter
      void set_fis_width_flg( Integer int_data );
      void set_xs_formula_flg( Integer int_data );
      void set_self_shielding_flg( Integer int_data );
      void set_level_spacing( vector<vector<vector<Real> > > real_vec );
      void set_j_value_abs( vector<vector<Real> > real_vec );
      void set_freedom_n( vector<vector<Real> > real_vec );
      void set_ave_gam_width_n( vector<vector<vector<Real> > > real_vec );
      void set_ave_gam_width_rad( vector<vector<vector<Real> > > real_vec );
      void set_ene_unreso( vector<vector<vector<Real> > > real_vec );
      void set_freedom_fis_int( vector<vector<Integer> > int_vec );
      void set_ave_gam_width_fis( vector<vector<vector<Real> > > real_vec );
      void set_unreso_int_data( vector<vector<Integer> > int_vec );
      void set_freedom_comp( vector<vector<Real> > real_vec );
      void set_freedom_rad( vector<vector<Real> > real_vec );
      void set_freedom_fis( vector<vector<Real> > real_vec );
      void set_ave_gam_width_comp( vector<vector<vector<Real> > > real_vec );
  };
}

#endif //UNRESOLVED_RESONANCE_DATA_CONTAINER_H
