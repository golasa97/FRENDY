#ifndef UNRESOLVED_RESONANCE_COVARIANCE_DATA_CONTAINER_H
#define UNRESOLVED_RESONANCE_COVARIANCE_DATA_CONTAINER_H

#include "CommonUtils/ErrorManager.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class UnresolvedResonanceCovarianceDataContainer
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

      vector<Real>          mass_isotope;
      vector<Integer>       l_value;
      vector<vector<Real> > level_spacing;
      vector<vector<Real> > j_value_abs;
      vector<vector<Real> > ave_gam_width_n;
      vector<vector<Real> > ave_gam_width_rad;
      vector<vector<Real> > ave_gam_width_fis;
      vector<vector<Real> > ave_gam_width_comp;
      Integer               reso_parameter_no;
      vector<vector<Real> > relative_cov_value;

    public:
      //constructor
      UnresolvedResonanceCovarianceDataContainer(void);

      //destructor
      virtual ~UnresolvedResonanceCovarianceDataContainer(void);

      void clear();

      //Getter
      vector<Real>          get_mass_isotope();
      vector<Integer>       get_l_value();
      vector<vector<Real> > get_level_spacing();
      vector<vector<Real> > get_j_value_abs();
      vector<vector<Real> > get_ave_gam_width_n();
      vector<vector<Real> > get_ave_gam_width_rad();
      vector<vector<Real> > get_ave_gam_width_fis();
      vector<vector<Real> > get_ave_gam_width_comp();
      Integer               get_reso_parameter_no();
      vector<vector<Real> > get_relative_cov_value();

      //Setter
      void set_mass_isotope( vector<Real> real_vec );
      void set_l_value( vector<Integer> int_vec );
      void set_level_spacing( vector<vector<Real> > real_vec );
      void set_j_value_abs( vector<vector<Real> > real_vec );
      void set_ave_gam_width_n( vector<vector<Real> > real_vec );
      void set_ave_gam_width_rad( vector<vector<Real> > real_vec );
      void set_ave_gam_width_fis( vector<vector<Real> > real_vec );
      void set_ave_gam_width_comp( vector<vector<Real> > real_vec );
      void set_reso_parameter_no( Integer int_data );
      void set_relative_cov_value( vector<vector<Real> > real_vec );
  };
}

#endif //UNRESOLVED_RESONANCE_COVARIANCE_DATA_CONTAINER_H
