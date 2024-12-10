#ifndef COMPATIBLE_RESOLVED_RESONANCE_DATA_CONTAINER_H
#define COMPATIBLE_RESOLVED_RESONANCE_DATA_CONTAINER_H

#include "CommonUtils/ErrorManager.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class CompatibleResolvedResonanceDataContainer
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

      Real                  scat_radius_uncertainty;
      vector<Integer>       l_value;
      vector<Real>          mass_isotope;
      vector<vector<Real> > ene_reso;
      vector<vector<Real> > j_value_abs;
      vector<vector<Real> > gam_width_tot;
      vector<vector<Real> > gam_width_n;
      vector<vector<Real> > gam_width_rad;
      vector<vector<Real> > gam_width_fis;
      vector<vector<Real> > ene_reso_variance;
      vector<vector<Real> > gam_width_n_variance;
      vector<vector<Real> > gam_width_n_rad_cov;
      vector<vector<Real> > gam_width_rad_variance;
      vector<vector<Real> > gam_width_n_rad_fis;
      vector<vector<Real> > gam_width_rad_fis_cov;
      vector<vector<Real> > gam_width_fis_variance;
      vector<vector<Real> > gam_width_n_j_cov;
      vector<vector<Real> > gam_width_rad_j_cov;
      vector<vector<Real> > gam_width_fis_j_cov;
      vector<vector<Real> > j_value_variance;

    public:
      //constructor
      CompatibleResolvedResonanceDataContainer(void);

      //destructor
      virtual ~CompatibleResolvedResonanceDataContainer(void);

      void clear();

      //Getter
      Real                  get_scat_radius_uncertainty();
      vector<Integer>       get_l_value();
      vector<Real>          get_mass_isotope();
      vector<vector<Real> > get_ene_reso();
      vector<vector<Real> > get_j_value_abs();
      vector<vector<Real> > get_gam_width_tot();
      vector<vector<Real> > get_gam_width_n();
      vector<vector<Real> > get_gam_width_rad();
      vector<vector<Real> > get_gam_width_fis();
      vector<vector<Real> > get_ene_reso_variance();
      vector<vector<Real> > get_gam_width_n_variance();
      vector<vector<Real> > get_gam_width_n_rad_cov();
      vector<vector<Real> > get_gam_width_rad_variance();
      vector<vector<Real> > get_gam_width_n_rad_fis();
      vector<vector<Real> > get_gam_width_rad_fis_cov();
      vector<vector<Real> > get_gam_width_fis_variance();
      vector<vector<Real> > get_gam_width_n_j_cov();
      vector<vector<Real> > get_gam_width_rad_j_cov();
      vector<vector<Real> > get_gam_width_fis_j_cov();
      vector<vector<Real> > get_j_value_variance();

      //Setter
      void set_scat_radius_uncertainty( Real real_data );
      void set_l_value( vector<Integer> int_vec );
      void set_mass_isotope( vector<Real> real_vec );
      void set_ene_reso( vector<vector<Real> > real_vec );
      void set_j_value_abs( vector<vector<Real> > real_vec );
      void set_gam_width_tot( vector<vector<Real> > real_vec );
      void set_gam_width_n( vector<vector<Real> > real_vec );
      void set_gam_width_rad( vector<vector<Real> > real_vec );
      void set_gam_width_fis( vector<vector<Real> > real_vec );
      void set_ene_reso_variance( vector<vector<Real> > real_vec );
      void set_gam_width_n_variance( vector<vector<Real> > real_vec );
      void set_gam_width_n_rad_cov( vector<vector<Real> > real_vec );
      void set_gam_width_rad_variance( vector<vector<Real> > real_vec );
      void set_gam_width_n_rad_fis( vector<vector<Real> > real_vec );
      void set_gam_width_rad_fis_cov( vector<vector<Real> > real_vec );
      void set_gam_width_fis_variance( vector<vector<Real> > real_vec );
      void set_gam_width_n_j_cov( vector<vector<Real> > real_vec );
      void set_gam_width_rad_j_cov( vector<vector<Real> > real_vec );
      void set_gam_width_fis_j_cov( vector<vector<Real> > real_vec );
      void set_j_value_variance( vector<vector<Real> > real_vec );
  };
}

#endif //COMPATIBLE_RESOLVED_RESONANCE_DATA_CONTAINER_H
