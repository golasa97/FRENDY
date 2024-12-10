#ifndef BREIT_WIGNER_DATA_CONTAINER_H
#define BREIT_WIGNER_DATA_CONTAINER_H

#include "CommonUtils/ErrorManager.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class BreitWignerDataContainer
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

      vector<Real>          q_value;
      vector<Integer>       competitive_width_flg;
      vector<vector<Real> > ene_reso;
      vector<vector<Real> > j_value_abs;
      vector<vector<Real> > gam_width_tot;
      vector<vector<Real> > gam_width_n;
      vector<vector<Real> > gam_width_rad;
      vector<vector<Real> > gam_width_fis;

    public:
      //constructor
      BreitWignerDataContainer(void);

      //destructor
      virtual ~BreitWignerDataContainer(void);

      void clear();

      //Getter
      vector<Real>          get_q_value();
      vector<Integer>       get_competitive_width_flg();
      vector<vector<Real> > get_ene_reso();
      vector<vector<Real> > get_j_value_abs();
      vector<vector<Real> > get_gam_width_tot();
      vector<vector<Real> > get_gam_width_n();
      vector<vector<Real> > get_gam_width_rad();
      vector<vector<Real> > get_gam_width_fis();

      //Setter
      void set_q_value( vector<Real> real_vec );
      void set_competitive_width_flg( vector<Integer> int_vec );
      void set_ene_reso( vector<vector<Real> > real_vec );
      void set_j_value_abs( vector<vector<Real> > real_vec );
      void set_gam_width_tot( vector<vector<Real> > real_vec );
      void set_gam_width_n( vector<vector<Real> > real_vec );
      void set_gam_width_rad( vector<vector<Real> > real_vec );
      void set_gam_width_fis( vector<vector<Real> > real_vec );
  };
}

#endif //BREIT_WIGNER_DATA_CONTAINER_H
