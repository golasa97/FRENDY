#ifndef RESONANCE_XS_RECONSTRUCTOR_BY_FRENDY_INPUT_H
#define RESONANCE_XS_RECONSTRUCTOR_BY_FRENDY_INPUT_H

#include <boost/timer/timer.hpp>

#include "CommonUtils/TimeUtils.hpp"
#include "FrendyUtils/ReconResonanceInputReader.hpp"
#include "ReconResonance/ResonanceXSReconstructor.hpp"

namespace frendy
{
  class ResonanceXSReconstructorByFrendyInput
  {
    private:
      frendy::VectorClearer  clr_obj;
      frendy::ErrorManager   err_obj;
      frendy::TimeUtils      time_obj;
    
#ifdef DEBUG_MODE
  public:
#endif
      frendy::NuclearDataObject         nucl_data_obj;

      frendy::ResonanceXSReconstructor  recon_obj;
      frendy::ReconResonanceInputReader frendy_inp_obj;
      
      Integer calc_flg, set_frendy_inp_obj_flg, set_nucl_data_obj_flg;

      //For time measurement
      Real time_total;

      void calc_reconstruct_resonance_xs();
      void check_set_data_flg();

    public:
      //constructor
      ResonanceXSReconstructorByFrendyInput(void);

      //destructor
      virtual ~ResonanceXSReconstructorByFrendyInput(void);

      void clear();

      void set_frendy_inp_obj(frendy::ReconResonanceInputReader inp_obj);
      void set_nucl_data_obj(frendy::NuclearDataObject data_obj);
      
      frendy::ReconResonanceInputReader get_frendy_inp_obj();
      frendy::NuclearDataObject         get_nucl_data_obj();

      Real get_time_total();
      Real get_calc_time();
  };
}

#endif //RESONANCE_XS_RECONSTRUCTOR_BY_FRENDY_INPUT_H
