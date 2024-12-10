#ifndef RESONANCE_XS_RECONSTRUCTOR_H
#define RESONANCE_XS_RECONSTRUCTOR_H

#include "NuclearDataUtils/OtherUtils/NuclearDataObjectUtils.hpp"
#include "ReconResonance/NonResonanceEnergyGridLinearizer.hpp"
#include "ReconResonance/ResonanceEnergyGridLinearizer.hpp"
#include "ReconResonance/ResonanceXSCalculator.hpp"
#include "ReconResonance/ResonanceXSCalculatorByInterpolation.hpp"
#include "ReconResonance/ReconstructXSMerger.hpp"
#include "ReconResonance/ResonanceNuclearDataModifier.hpp"

namespace frendy
{
  class ResonanceXSReconstructor
  {
    private:
      frendy::VectorClearer           clr_obj;
      frendy::ErrorManager            err_obj;
      frendy::NuclearDataObjectUtils  nucl_util_obj;
    
#ifdef DEBUG_MODE
  public:
#endif
      //Set using classes
      frendy::NonResonanceEnergyGridLinearizer non_reso_obj;
      frendy::ResonanceEnergyGridLinearizer    reso_obj;
      frendy::ReconstructXSMerger              mrg_obj;
      frendy::ResonanceNuclearDataModifier     mod_obj;

#ifdef NJOY_MODE
      frendy::ResonanceXSCalculatorByInterpolation  reso_xs_obj;
#else
      frendy::ResonanceXSCalculator                 reso_xs_obj;
#endif

      frendy::NuclearDataObject                     nucl_data_obj;

      int           modify_photon_data_flg;
      Integer       calc_reso_flg, nucl_data_set_flg;
      Real8         err, err_int, err_max, temp;
      vector<Real8> additional_grid;

      //Energy grid and cross section
      vector<Real8>                            non_reso_grid;
      vector<vector<vector<Integer> > >        reso_react_type_list;
      vector<vector<vector<Real8> > >          reso_q_val;
      vector<vector<vector<Real8> > >          reso_grid;
      vector<vector<vector<vector<Real8> > > > reso_xs;
      vector<Real8>                            merge_grid;
      vector<vector<Real8> >                   merge_xs;

      vector<vector<Integer> >                 linearize_file_list;

      void remove_unnecessary_file_data();

      void clear_ene_grid_and_xs();

    public:
      //constructor
      ResonanceXSReconstructor(void);

      //destructor
      virtual ~ResonanceXSReconstructor(void);

      void calc_reconstruct_resonance_xs();
      void output_set_data_information();

      void clear();

      //Setter
      void set_nucl_data_obj(frendy::NuclearDataObject& data_obj);

      void set_modify_photon_data_flg(int int_val);
      void set_err(Real8 real_val);
      void set_err_int(Real8 real_val);
      void set_err_max(Real8 real_val);
      void set_temp(Real8 real_val);
      void set_additional_grid(vector<Real8> real_vec);

      //Getter
      frendy::NuclearDataObject get_nucl_data_obj();

      int            get_modify_photon_data_flg();
      Real8          get_err();
      Real8          get_err_int();
      Real8          get_err_max();
      Real8          get_temp();
      vector<Real8>  get_additional_grid();

      vector<Real8>                            get_non_reso_grid();
      vector<vector<vector<Integer> > >        get_reso_react_type_list();
      vector<vector<vector<Real8> > >          get_reso_q_val();
      vector<vector<vector<Real8> > >          get_reso_grid();
      vector<vector<vector<vector<Real8> > > > get_reso_xs();
      vector<Real8>                            get_merge_grid();
      vector<vector<Real8> >                   get_merge_xs();
  };
}

#endif //RESONANCE_XS_RECONSTRUCTOR_H
