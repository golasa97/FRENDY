#ifndef COVARIANCE_RESONANCE_DATA_CONTAINER_H
#define COVARIANCE_RESONANCE_DATA_CONTAINER_H

#include "CommonUtils/ErrorManager.hpp"
#include "CommonUtils/VectorClearer.hpp"
#include "NuclearDataUtils/CovarianceDataContainer/CovarianceResonanceData/CompatibleResolvedResonanceDataContainer.hpp"
#include "NuclearDataUtils/CovarianceDataContainer/CovarianceResonanceData/BreitWignerCovarianceDataContainer.hpp"
#include "NuclearDataUtils/CovarianceDataContainer/CovarianceResonanceData/ReichMooreCovarianceDataContainer.hpp"
#include "NuclearDataUtils/CovarianceDataContainer/CovarianceResonanceData/AdlerAdlerCovarianceDataContainer.hpp"
#include "NuclearDataUtils/CovarianceDataContainer/CovarianceResonanceData/RMatrixLimitedCovarianceDataContainer.hpp"
#include "NuclearDataUtils/CovarianceDataContainer/CovarianceResonanceData/BreitWignerCompactCovarianceDataContainer.hpp"
#include "NuclearDataUtils/CovarianceDataContainer/CovarianceResonanceData/ReichMooreCompactCovarianceDataContainer.hpp"
#include "NuclearDataUtils/CovarianceDataContainer/CovarianceResonanceData/RMatrixLimitedCompactCovarianceDataContainer.hpp"
#include "NuclearDataUtils/CovarianceDataContainer/CovarianceResonanceData/UnresolvedResonanceCovarianceDataContainer.hpp"

namespace frendy
{
  class CovarianceResonanceDataContainer
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

      vector<Real>                                     mat_data_isotope;
      vector<Real>                                     abundance_isotope;
      vector<Integer>                                  fis_width_flg;
      vector<vector<Real> >                            lower_ene_limit;
      vector<vector<Real> >                            upper_ene_limit;
      vector<vector<Integer> >                         reso_region_flg;
      vector<vector<Integer> >                         xs_formula_flg;
      vector<vector<Integer> >                         scat_radius_ene_dependence_flg;
      vector<vector<Integer> >                         radius_calc_flg;
      vector<vector<Real> >                            spin_data;
      vector<vector<Real> >                            scat_radius;
      vector<vector<Integer> >                         angular_distr_calc_flg;
      vector<vector<Integer> >                         compatibility_flg;
      vector<vector<vector<Integer> > >                cov_matrix_data_flg;
      vector<vector<vector<vector<Real> > > >          cov_matrix_ene_k;
      vector<vector<vector<vector<vector<Real> > > > > cov_matrix_coef_k;
      vector<vector<vector<vector<Real> > > >          cov_matrix_ene_l;
      vector<vector<vector<vector<vector<Real> > > > > cov_matrix_coef_l;
      vector<vector<Real> >                            mass_isotope;

      vector<vector<frendy::CompatibleResolvedResonanceDataContainer> >      compatible_obj;
      vector<vector<frendy::BreitWignerCovarianceDataContainer> >            bw_obj;
      vector<vector<frendy::ReichMooreCovarianceDataContainer> >             rm_obj;
      vector<vector<frendy::AdlerAdlerCovarianceDataContainer> >             adler_obj;
      vector<vector<frendy::RMatrixLimitedCovarianceDataContainer> >         r_matrix_obj;
      vector<vector<frendy::BreitWignerCompactCovarianceDataContainer> >     bw_compact_obj;
      vector<vector<frendy::ReichMooreCompactCovarianceDataContainer> >      rm_compact_obj;
      vector<vector<frendy::RMatrixLimitedCompactCovarianceDataContainer> >  r_matrix_compact_obj;
      vector<vector<frendy::UnresolvedResonanceCovarianceDataContainer> >    unreso_obj;

      void clear_compatible_obj(vector<vector<frendy::CompatibleResolvedResonanceDataContainer> >& data_obj);
      void clear_bw_obj(vector<vector<frendy::BreitWignerCovarianceDataContainer> >& data_obj);
      void clear_rm_obj(vector<vector<frendy::ReichMooreCovarianceDataContainer> >& data_obj);
      void clear_adler_obj(vector<vector<frendy::AdlerAdlerCovarianceDataContainer> >& data_obj);
      void clear_r_matrix_obj(vector<vector<frendy::RMatrixLimitedCovarianceDataContainer> >& data_obj);
      void clear_bw_compact_obj(vector<vector<frendy::BreitWignerCompactCovarianceDataContainer> >& data_obj);
      void clear_rm_compact_obj(vector<vector<frendy::ReichMooreCompactCovarianceDataContainer> >& data_obj);
      void clear_r_matrix_compact_obj(vector<vector<frendy::RMatrixLimitedCompactCovarianceDataContainer> >& data_obj);
      void clear_unreso_obj(vector<vector<frendy::UnresolvedResonanceCovarianceDataContainer> >& data_obj);

      void check_data_size( int i, int j, int ele_no, int ele_max, string func_name, string ele_name );

    public:
      //constructor
      CovarianceResonanceDataContainer(void);

      //destructor
      virtual ~CovarianceResonanceDataContainer(void);

      void clear();

      //Getter
      vector<Real>                                     get_mat_data_isotope();
      vector<Real>                                     get_abundance_isotope();
      vector<Integer>                                  get_fis_width_flg();
      vector<vector<Real> >                            get_lower_ene_limit();
      vector<vector<Real> >                            get_upper_ene_limit();
      vector<vector<Integer> >                         get_reso_region_flg();
      vector<vector<Integer> >                         get_xs_formula_flg();
      vector<vector<Integer> >                         get_scat_radius_ene_dependence_flg();
      vector<vector<Integer> >                         get_radius_calc_flg();
      vector<vector<Real> >                            get_spin_data();
      vector<vector<Real> >                            get_scat_radius();
      vector<vector<Integer> >                         get_angular_distr_calc_flg();
      vector<vector<Integer> >                         get_compatibility_flg();
      vector<vector<vector<Integer> > >                get_cov_matrix_data_flg();
      vector<vector<vector<vector<Real> > > >          get_cov_matrix_ene_k();
      vector<vector<vector<vector<vector<Real> > > > > get_cov_matrix_coef_k();
      vector<vector<vector<vector<Real> > > >          get_cov_matrix_ene_l();
      vector<vector<vector<vector<vector<Real> > > > > get_cov_matrix_coef_l();
      vector<vector<Real> >                            get_mass_isotope();

      vector<vector<frendy::CompatibleResolvedResonanceDataContainer> >      get_compatible_obj();
      vector<vector<frendy::BreitWignerCovarianceDataContainer> >            get_bw_obj();
      vector<vector<frendy::ReichMooreCovarianceDataContainer> >             get_rm_obj();
      vector<vector<frendy::AdlerAdlerCovarianceDataContainer> >             get_adler_obj();
      vector<vector<frendy::RMatrixLimitedCovarianceDataContainer> >         get_r_matrix_obj();
      vector<vector<frendy::BreitWignerCompactCovarianceDataContainer> >     get_bw_compact_obj();
      vector<vector<frendy::ReichMooreCompactCovarianceDataContainer> >      get_rm_compact_obj();
      vector<vector<frendy::RMatrixLimitedCompactCovarianceDataContainer> >  get_r_matrix_compact_obj();
      vector<vector<frendy::UnresolvedResonanceCovarianceDataContainer> >    get_unreso_obj();

      frendy::CompatibleResolvedResonanceDataContainer      get_compatible_obj(int i, int j);
      frendy::BreitWignerCovarianceDataContainer            get_bw_obj(int i, int j);
      frendy::ReichMooreCovarianceDataContainer             get_rm_obj(int i, int j);
      frendy::AdlerAdlerCovarianceDataContainer             get_adler_obj(int i, int j);
      frendy::RMatrixLimitedCovarianceDataContainer         get_r_matrix_obj(int i, int j);
      frendy::BreitWignerCompactCovarianceDataContainer     get_bw_compact_obj(int i, int j);
      frendy::ReichMooreCompactCovarianceDataContainer      get_rm_compact_obj(int i, int j);
      frendy::RMatrixLimitedCompactCovarianceDataContainer  get_r_matrix_compact_obj(int i, int j);
      frendy::UnresolvedResonanceCovarianceDataContainer    get_unreso_obj(int i, int j);

      //Setter
      void set_mat_data_isotope( vector<Real> real_vec );
      void set_abundance_isotope( vector<Real> real_vec );
      void set_fis_width_flg( vector<Integer> int_vec );
      void set_lower_ene_limit( vector<vector<Real> > real_vec );
      void set_upper_ene_limit( vector<vector<Real> > real_vec );
      void set_reso_region_flg( vector<vector<Integer> > int_vec );
      void set_xs_formula_flg( vector<vector<Integer> > int_vec );
      void set_scat_radius_ene_dependence_flg( vector<vector<Integer> > int_vec );
      void set_radius_calc_flg( vector<vector<Integer> > int_vec );
      void set_spin_data( vector<vector<Real> > real_vec );
      void set_scat_radius( vector<vector<Real> > real_vec );
      void set_angular_distr_calc_flg( vector<vector<Integer> > int_vec );
      void set_compatibility_flg( vector<vector<Integer> > int_vec );
      void set_cov_matrix_data_flg( vector<vector<vector<Integer> > > int_vec );
      void set_cov_matrix_ene_k( vector<vector<vector<vector<Real> > > > real_vec );
      void set_cov_matrix_coef_k( vector<vector<vector<vector<vector<Real> > > > > real_vec );
      void set_cov_matrix_ene_l( vector<vector<vector<vector<Real> > > > real_vec );
      void set_cov_matrix_coef_l( vector<vector<vector<vector<vector<Real> > > > > real_vec );
      void set_mass_isotope( vector<vector<Real> > real_vec );

      void set_compatible_obj( vector<vector<frendy::CompatibleResolvedResonanceDataContainer> > obj_data );
      void set_bw_obj( vector<vector<frendy::BreitWignerCovarianceDataContainer> > obj_data );
      void set_rm_obj( vector<vector<frendy::ReichMooreCovarianceDataContainer> > obj_data );
      void set_adler_obj( vector<vector<frendy::AdlerAdlerCovarianceDataContainer> > obj_data );
      void set_r_matrix_obj( vector<vector<frendy::RMatrixLimitedCovarianceDataContainer> > obj_data );
      void set_bw_compact_obj( vector<vector<frendy::BreitWignerCompactCovarianceDataContainer> > obj_data );
      void set_rm_compact_obj( vector<vector<frendy::ReichMooreCompactCovarianceDataContainer> > obj_data );
      void set_r_matrix_compact_obj( vector<vector<frendy::RMatrixLimitedCompactCovarianceDataContainer> > obj_data );
      void set_unreso_obj( vector<vector<frendy::UnresolvedResonanceCovarianceDataContainer> > obj_data );

      void set_compatible_obj( int i, int j, frendy::CompatibleResolvedResonanceDataContainer obj_data );
      void set_bw_obj( int i, int j, frendy::BreitWignerCovarianceDataContainer obj_data );
      void set_rm_obj( int i, int j, frendy::ReichMooreCovarianceDataContainer obj_data );
      void set_adler_obj( int i, int j, frendy::AdlerAdlerCovarianceDataContainer obj_data );
      void set_r_matrix_obj( int i, int j, frendy::RMatrixLimitedCovarianceDataContainer obj_data );
      void set_bw_compact_obj( int i, int j, frendy::BreitWignerCompactCovarianceDataContainer obj_data );
      void set_rm_compact_obj( int i, int j, frendy::ReichMooreCompactCovarianceDataContainer obj_data );
      void set_r_matrix_compact_obj( int i, int j, frendy::RMatrixLimitedCompactCovarianceDataContainer obj_data );
      void set_unreso_obj( int i, int j, frendy::UnresolvedResonanceCovarianceDataContainer obj_data );
  };
}

#endif //COVARIANCE_RESONANCE_DATA_CONTAINER_H
