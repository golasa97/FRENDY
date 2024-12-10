#ifndef RESONANCE_DATA_CONTAINER_H
#define RESONANCE_DATA_CONTAINER_H

#include "CommonUtils/ErrorManager.hpp"
#include "CommonUtils/VectorClearer.hpp"
#include "NuclearDataUtils/NuclearDataContainer/ResonanceData/BreitWignerDataContainer.hpp"
#include "NuclearDataUtils/NuclearDataContainer/ResonanceData/ReichMooreDataContainer.hpp"
#include "NuclearDataUtils/NuclearDataContainer/ResonanceData/AdlerAdlerDataContainer.hpp"
#include "NuclearDataUtils/NuclearDataContainer/ResonanceData/RMatrixLimitedDataContainer.hpp"
#include "NuclearDataUtils/NuclearDataContainer/ResonanceData/UnresolvedResonanceDataContainer.hpp"
#include "NuclearDataUtils/NuclearDataContainer/ResonanceData/UnresolvedCrossSectionDataContainer.hpp"
#include "NuclearDataUtils/NuclearDataContainer/ResonanceData/UnresolvedProbabilityDataContainer.hpp"

namespace frendy
{
  class ResonanceDataContainer
  {
    private:
      ErrorManager  err_obj;
      VectorClearer clr_obj;

      vector<Real>                      mat_data_isotope;
      vector<Real>                      abundance_isotope;
      vector<Integer>                   fis_width_flg;
      vector<vector<Real> >             lower_ene_limit;
      vector<vector<Real> >             upper_ene_limit;
      vector<vector<Integer> >          reso_region_flg;
      vector<vector<Integer> >          xs_formula_flg;
      vector<vector<Integer> >          scat_radius_ene_dependence_flg;
      vector<vector<Integer> >          radius_calc_flg;
      vector<vector<Real> >             spin_data;
      vector<vector<Real> >             scat_radius;
      vector<vector<vector<Integer> > > scat_radius_tab_int_data;
      vector<vector<vector<Integer> > > scat_radius_tab_range_data;
      vector<vector<vector<Real> > >    scat_radius_tab_ene_data;
      vector<vector<vector<Real> > >    scat_radius_tab_data;
      vector<vector<vector<Integer> > > l_value;
      vector<vector<vector<Real> > >    mass_isotope;

      vector<vector<frendy::BreitWignerDataContainer> >         bw_data_obj;
      vector<vector<frendy::ReichMooreDataContainer> >          rm_data_obj;
      vector<vector<frendy::AdlerAdlerDataContainer> >          adler_data_obj;
      vector<vector<frendy::RMatrixLimitedDataContainer> >      r_matrix_data_obj;
      vector<vector<frendy::UnresolvedResonanceDataContainer> > unreso_data_obj;

      frendy::UnresolvedCrossSectionDataContainer               unreso_xs_data_obj;
      frendy::UnresolvedProbabilityDataContainer                unreso_prob_data_obj;

      void clear_bw_data_obj(vector<vector<frendy::BreitWignerDataContainer> >& data_obj);
      void clear_rm_data_obj(vector<vector<frendy::ReichMooreDataContainer> >& data_obj);
      void clear_adler_data_obj(vector<vector<frendy::AdlerAdlerDataContainer> >& data_obj);
      void clear_r_matrix_data_obj(vector<vector<frendy::RMatrixLimitedDataContainer> >& data_obj);
      void clear_unreso_data_obj(vector<vector<frendy::UnresolvedResonanceDataContainer> >& data_obj);

      void check_data_size( int i, int j, int ele_no, int ele_max, string func_name, string ele_name );

    public:
      //constructor
      ResonanceDataContainer(void);

      //destructor
      virtual ~ResonanceDataContainer(void);

      void clear();

      //Getter
      vector<Real>                      get_mat_data_isotope();
      vector<Real>                      get_abundance_isotope();
      vector<Integer>                   get_fis_width_flg();
      vector<vector<Real> >             get_lower_ene_limit();
      vector<vector<Real> >             get_upper_ene_limit();
      vector<vector<Integer> >          get_reso_region_flg();
      vector<vector<Integer> >          get_xs_formula_flg();
      vector<vector<Integer> >          get_scat_radius_ene_dependence_flg();
      vector<vector<Integer> >          get_radius_calc_flg();
      vector<vector<Real> >             get_spin_data();
      vector<vector<Real> >             get_scat_radius();
      vector<vector<vector<Integer> > > get_scat_radius_tab_int_data();
      vector<vector<vector<Integer> > > get_scat_radius_tab_range_data();
      vector<vector<vector<Real> > >    get_scat_radius_tab_ene_data();
      vector<vector<vector<Real> > >    get_scat_radius_tab_data();
      vector<vector<vector<Integer> > > get_l_value();
      vector<vector<vector<Real> > >    get_mass_isotope();

      vector<vector<frendy::BreitWignerDataContainer> >         get_bw_data_obj();
      vector<vector<frendy::ReichMooreDataContainer> >          get_rm_data_obj();
      vector<vector<frendy::AdlerAdlerDataContainer> >          get_adler_data_obj();
      vector<vector<frendy::RMatrixLimitedDataContainer> >      get_r_matrix_data_obj();
      vector<vector<frendy::UnresolvedResonanceDataContainer> > get_unreso_data_obj();

      frendy::BreitWignerDataContainer            get_bw_data_obj(int i, int j);
      frendy::ReichMooreDataContainer             get_rm_data_obj(int i, int j);
      frendy::AdlerAdlerDataContainer             get_adler_data_obj(int i, int j);
      frendy::RMatrixLimitedDataContainer         get_r_matrix_data_obj(int i, int j);
      frendy::UnresolvedResonanceDataContainer    get_unreso_data_obj(int i, int j);

      frendy::UnresolvedCrossSectionDataContainer get_unreso_xs_data_obj();
      frendy::UnresolvedProbabilityDataContainer  get_unreso_prob_data_obj();

      Real get_el_reso();
      Real get_eh_reso();
      Real get_el_unreso();
      Real get_eh_unreso();

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
      void set_scat_radius_tab_int_data( vector<vector<vector<Integer> > > int_vec );
      void set_scat_radius_tab_range_data( vector<vector<vector<Integer> > > int_vec );
      void set_scat_radius_tab_ene_data( vector<vector<vector<Real> > > real_vec );
      void set_scat_radius_tab_data( vector<vector<vector<Real> > > real_vec );
      void set_l_value( vector<vector<vector<Integer> > > int_vec );
      void set_mass_isotope( vector<vector<vector<Real> > > real_vec );

      void set_bw_data_obj( vector<vector<frendy::BreitWignerDataContainer> > obj_data );
      void set_rm_data_obj( vector<vector<frendy::ReichMooreDataContainer> > obj_data );
      void set_adler_data_obj( vector<vector<frendy::AdlerAdlerDataContainer> > obj_data );
      void set_r_matrix_data_obj( vector<vector<frendy::RMatrixLimitedDataContainer> > obj_data );
      void set_unreso_data_obj( vector<vector<frendy::UnresolvedResonanceDataContainer> > obj_data );

      void set_bw_data_obj( int i, int j, frendy::BreitWignerDataContainer obj_data );
      void set_rm_data_obj( int i, int j, frendy::ReichMooreDataContainer obj_data );
      void set_adler_data_obj( int i, int j, frendy::AdlerAdlerDataContainer obj_data );
      void set_r_matrix_data_obj( int i, int j, frendy::RMatrixLimitedDataContainer obj_data );
      void set_unreso_data_obj( int i, int j, frendy::UnresolvedResonanceDataContainer obj_data );

      void set_unreso_xs_data_obj( frendy::UnresolvedCrossSectionDataContainer obj_data );
      void set_unreso_prob_data_obj( frendy::UnresolvedProbabilityDataContainer obj_data );
  };
}
#endif //RESONANCE_DATA_CONTAINER_H
