#ifndef REICH_MOORE_DATA_CONTAINER_H
#define REICH_MOORE_DATA_CONTAINER_H

#include "CommonUtils/ErrorManager.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class ReichMooreDataContainer
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

      Integer               angular_distr_calc_flg;
      Integer               l_no_conv_calc;
      vector<Real>          scat_radius_l;
      vector<vector<Real> > ene_reso;
      vector<vector<Real> > j_value_abs;
      vector<vector<Real> > gam_width_n;
      vector<vector<Real> > gam_width_rad;
      vector<vector<Real> > gam_width_fis_a;
      vector<vector<Real> > gam_width_fis_b;

    public:
      //constructor
      ReichMooreDataContainer(void);

      //destructor
      virtual ~ReichMooreDataContainer(void);

      void clear();

      //Getter
      Integer               get_angular_distr_calc_flg();
      Integer               get_l_no_conv_calc();
      vector<Real>          get_scat_radius_l();
      vector<vector<Real> > get_ene_reso();
      vector<vector<Real> > get_j_value_abs();
      vector<vector<Real> > get_gam_width_n();
      vector<vector<Real> > get_gam_width_rad();
      vector<vector<Real> > get_gam_width_fis_a();
      vector<vector<Real> > get_gam_width_fis_b();

      //Setter
      void set_angular_distr_calc_flg( Integer int_data );
      void set_l_no_conv_calc( Integer int_data );
      void set_scat_radius_l( vector<Real> real_vec );
      void set_ene_reso( vector<vector<Real> > real_vec );
      void set_j_value_abs( vector<vector<Real> > real_vec );
      void set_gam_width_n( vector<vector<Real> > real_vec );
      void set_gam_width_rad( vector<vector<Real> > real_vec );
      void set_gam_width_fis_a( vector<vector<Real> > real_vec );
      void set_gam_width_fis_b( vector<vector<Real> > real_vec );
  };
}

#endif //REICH_MOORE_DATA_CONTAINER_H
