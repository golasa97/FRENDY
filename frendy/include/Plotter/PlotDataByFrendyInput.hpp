#ifndef PLOT_DATA_BY_FRENDY_INPUT_H
#define PLOT_DATA_BY_FRENDY_INPUT_H

#include "CommonUtils/TimeUtils.hpp"
#include "CommonUtils/ErrorManager.hpp"
#include "CommonUtils/TabInterpolator.hpp"
#include "CommonUtils/FileCommentRemover.hpp"
#include "CommonUtils/TabAdjuster.hpp"
#include "CommonUtils/DigitAdjuster.hpp"
#include "NuclearDataUtils/OtherUtils/Endf6FileStore.hpp"
#include "EndfUtils/Endf6Parser/Endf6Parser.hpp"
#include "TabUtils/IntegrateTabData.hpp"
#include "TabUtils/LinearizeTabData.hpp"
#include "ReconResonance/ResonanceXSReconstructorByNjoyInput.hpp"
#include "DopplerBroadening/DopplerCalculatorByNjoyInput.hpp"
#include "FrendyUtils/MultiGroupDataGeneratorInputReader.hpp"
#include "FrendyUtils/NuclearDataPlotterInputReader.hpp"
#include "Plotter/PlotEndfData.hpp"
#include "Plotter/PlotAceData.hpp"
#include "Plotter/PlotGendfData.hpp"


namespace frendy
{
  class PlotDataByFrendyInput
  {
    private:
      frendy::VectorClearer       clr_obj;
      frendy::ErrorManager        err_obj;
      frendy::TabInterpolator     ti_obj;
      frendy::DigitAdjuster       digit_obj;
      frendy::TabAdjuster         tab_ad_obj;
      frendy::IntegrateTabData    integ_obj;

      frendy::NuclearDataPlotterInputReader  frendy_inp_obj;

#ifdef NJOY_MODE
      frendy::BroadenedXSCalculatorWithNjoyFormula calc_dop_obj;
#else
      frendy::BroadenedXSCalculator calc_dop_obj;
#endif
      int  calc_flg;
      Real temp_ref, temp_com;

      int             set_mg_option_flg;
      string          mg_w_mode;
      vector<Real>    mg_w_e, mg_w_f;
      vector<Integer> mg_w_int, mg_w_nbt;


      void set_file_name(string& ref_name, string& com_name);

      void plot_gendf_file(string ref_name);

      void plot_xs_data(string nucl_name, vector<Integer>& mt_list,
                        vector<vector<Real> >& ene_vec, vector<vector<Real> >& xs_vec);
      void plot_mg_xs_data(string nucl_name, vector<Integer>& mt_list,
                           vector<vector<Real> >& ene_vec, vector<vector<Real> >& xs_vec);

      void plot_comp_xs_data(string ref_name, string comp_name, vector<Integer>& mt_list,
                             vector<vector<Real> >& ene_vec_ref, vector<vector<Real> >& xs_vec_ref,
                             vector<vector<Real> >& ene_vec_com, vector<vector<Real> >& xs_vec_com);
      void plot_comp_mg_xs_data(string ref_name, string comp_name, vector<Integer>& mt_list,
                                vector<vector<Real> >& ene_vec_ref, vector<vector<Real> >& xs_vec_ref,
                                vector<vector<Real> >& ene_vec_com, vector<vector<Real> >& xs_vec_com);

      string set_output_name(string nucl_name, Integer mt_no);

      void set_mg_option(vector<vector<Real> >& ene_vec, vector<vector<Real> >& weight_vec,
                         vector<Real>& mg_structure);
      vector<vector<Real> > get_mg_xs_data(vector<Integer>& mt_list,
                                           vector<vector<Real> > ene_vec, vector<vector<Real> > xs_vec,
                                           vector<vector<Real> > weight_vec, vector<Real> mg_structure);


    public:
      //constructor
      PlotDataByFrendyInput(void);

      //destructor
      virtual ~PlotDataByFrendyInput(void);

      void clear();
      
      void plot_data();

      int  check_plot_flg(int i, vector<Real>& xs_vec);

      void set_frendy_input(string input_file_name);
      void set_frendy_inp_obj(frendy::NuclearDataPlotterInputReader inp_obj);

      frendy::NuclearDataPlotterInputReader get_frendy_inp_obj();
  };
}

#endif //PLOT_DATA_BY_FRENDY_INPUT_H
