#ifndef ADLER_ADLER_DATA_CONTAINER_H
#define ADLER_ADLER_DATA_CONTAINER_H

#include "CommonUtils/ErrorManager.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class AdlerAdlerDataContainer
  {
    private:
      ErrorManager  err_obj;
      VectorClearer clr_obj;

      Integer                        adler_calc_flg;
      vector<Real>                   back_ground_tot;
      vector<Real>                   back_ground_fis;
      vector<Real>                   back_ground_rad;
      vector<vector<Real> >          j_value_abs;
      vector<vector<vector<Real> > > ene_reso_tot;
      vector<vector<vector<Real> > > ene_reso_fis;
      vector<vector<vector<Real> > > ene_reso_rad;
      vector<vector<vector<Real> > > gam_width_half_tot;
      vector<vector<vector<Real> > > gam_width_half_fis;
      vector<vector<vector<Real> > > gam_width_half_rad;
      vector<vector<vector<Real> > > symmetrical_data_tot;
      vector<vector<vector<Real> > > non_symmetrical_data_tot;
      vector<vector<vector<Real> > > symmetrical_data_fis;
      vector<vector<vector<Real> > > non_symmetrical_data_fis;
      vector<vector<vector<Real> > > symmetrical_data_rad;
      vector<vector<vector<Real> > > non_symmetrical_data_rad;

    public:
      //constructor
      AdlerAdlerDataContainer(void);

      //destructor
      virtual ~AdlerAdlerDataContainer(void);

      void clear();

      //Getter
      Integer                        get_adler_calc_flg();
      vector<Real>                   get_back_ground_tot();
      vector<Real>                   get_back_ground_fis();
      vector<Real>                   get_back_ground_rad();
      vector<vector<Real> >          get_j_value_abs();
      vector<vector<vector<Real> > > get_ene_reso_tot();
      vector<vector<vector<Real> > > get_ene_reso_fis();
      vector<vector<vector<Real> > > get_ene_reso_rad();
      vector<vector<vector<Real> > > get_gam_width_half_tot();
      vector<vector<vector<Real> > > get_gam_width_half_fis();
      vector<vector<vector<Real> > > get_gam_width_half_rad();
      vector<vector<vector<Real> > > get_symmetrical_data_tot();
      vector<vector<vector<Real> > > get_non_symmetrical_data_tot();
      vector<vector<vector<Real> > > get_symmetrical_data_fis();
      vector<vector<vector<Real> > > get_non_symmetrical_data_fis();
      vector<vector<vector<Real> > > get_symmetrical_data_rad();
      vector<vector<vector<Real> > > get_non_symmetrical_data_rad();

      //Setter
      void set_adler_calc_flg( Integer int_data );
      void set_back_ground_tot( vector<Real> real_vec );
      void set_back_ground_fis( vector<Real> real_vec );
      void set_back_ground_rad( vector<Real> real_vec );
      void set_j_value_abs( vector<vector<Real> > real_vec );
      void set_ene_reso_tot( vector<vector<vector<Real> > > real_vec );
      void set_ene_reso_fis( vector<vector<vector<Real> > > real_vec );
      void set_ene_reso_rad( vector<vector<vector<Real> > > real_vec );
      void set_gam_width_half_tot( vector<vector<vector<Real> > > real_vec );
      void set_gam_width_half_fis( vector<vector<vector<Real> > > real_vec );
      void set_gam_width_half_rad( vector<vector<vector<Real> > > real_vec );
      void set_symmetrical_data_tot( vector<vector<vector<Real> > > real_vec );
      void set_non_symmetrical_data_tot( vector<vector<vector<Real> > > real_vec );
      void set_symmetrical_data_fis( vector<vector<vector<Real> > > real_vec );
      void set_non_symmetrical_data_fis( vector<vector<vector<Real> > > real_vec );
      void set_symmetrical_data_rad( vector<vector<vector<Real> > > real_vec );
      void set_non_symmetrical_data_rad( vector<vector<vector<Real> > > real_vec );
  };
}

#endif //ADLER_ADLER_DATA_CONTAINER_H
