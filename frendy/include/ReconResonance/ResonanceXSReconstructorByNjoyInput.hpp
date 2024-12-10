#ifndef RESONANCE_XS_RECONSTRUCTOR_BY_NJOY_INPUT_H
#define RESONANCE_XS_RECONSTRUCTOR_BY_NJOY_INPUT_H

#include <boost/timer/timer.hpp>

#include "CommonUtils/TimeUtils.hpp"
#include "EndfUtils/OtherUtils/EndfTapeDivider.hpp"
#include "EndfUtils/Endf6Writer/Endf6Writer.hpp"
#include "NjoyUtils/ReconrInputReader.hpp"
#include "NuclearDataUtils/OtherUtils/Endf6FileStore.hpp"
#include "ReconResonance/ResonanceXSReconstructor.hpp"

namespace frendy
{
  class ResonanceXSReconstructorByNjoyInput
  {
    private:
      frendy::VectorClearer  clr_obj;
      frendy::ErrorManager   err_obj;
      frendy::TimeUtils      time_obj;
      frendy::Endf6Converter conv_obj;
      frendy::Endf6FileStore store_obj;
      frendy::Endf6Writer    wri_obj;
    
#ifdef DEBUG_MODE
  public:
#endif
      //Set using classes
      vector<frendy::NuclearDataObject> nucl_data_obj;
      frendy::ResonanceXSReconstructor  recon_obj;

      string input_file_name_njoy;
      int    start_line_no;
      
      //From input file
      string endf_file_name;
      string pendf_file_name;
      string pendf_label;
      
      vector<Integer>         mat_no_list;
      vector<Real8>           err;
      vector<Real8>           err_int;
      vector<Real8>           err_max;
      vector<Real8>           temp;
      vector<vector<string> > comment_line;
      vector<vector<Real8> >  additional_grid;
      
      //Cross section and energy grid
      vector<vector<Real8> >                            non_reso_grid;
      vector<vector<vector<vector<Real8> > > >          reso_grid;
      vector<vector<vector<vector<vector<Real8> > > > > reso_xs;
      vector<vector<Real8> >                            merge_grid;
      vector<vector<vector<Real8> > >                   merge_xs;

      Integer calc_flg;

      //For time measurement
      Real         time_total;
      vector<Real> time_each;

      void calc_reconstruct_resonance_xs();
      void calc_reconstruct_resonance_xs_each_mat(int& mat_no);

      void set_input_data();
      void check_set_data();

      void output_input_file_name();

    public:
      //constructor
      ResonanceXSReconstructorByNjoyInput(void);

      //destructor
      virtual ~ResonanceXSReconstructorByNjoyInput(void);

      void clear();

      void set_njoy_input_file_name(string file_name);
      void set_njoy_input_file_name(string file_name, int line_no);
      
      void write_pendf_file();
      
      string                  get_njoy_input_file_name();
      string                  get_endf_file_name();
      string                  get_pendf_file_name();
      vector<Real8>           get_err();
      vector<Real8>           get_err_int();
      vector<Real8>           get_err_max();
      vector<Real8>           get_temp();
      vector<vector<string> > get_comment_line();
      vector<vector<Real8> >  get_additional_grid();
      
      vector<vector<string> >                           get_text();
      frendy::NuclearDataObject                         get_nucl_data_obj(Integer mat_no);
      vector<frendy::NuclearDataObject>                 get_nucl_data_obj();
      frendy::Endf6ParserNoCov                          get_endf_obj(Integer mat_no);
      vector<frendy::Endf6ParserNoCov>                  get_endf_obj();
      vector<vector<Real8> >                            get_non_reso_grid();
      vector<vector<vector<vector<Real8> > > >          get_reso_grid();
      vector<vector<vector<vector<vector<Real8> > > > > get_reso_xs();
      vector<vector<Real8> >                            get_merge_grid();
      vector<vector<vector<Real8> > >                   get_merge_xs();

      Real         get_time_total();
      vector<Real> get_time_each_mat();
  };
}

#endif //RESONANCE_XS_RECONSTRUCTOR_BY_NJOY_INPUT_H
