#ifndef PLOT_ENDF_DATA_H
#define PLOT_ENDF_DATA_H

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
#include "DopplerBroadening/DopplerCalculator.hpp"

namespace frendy
{
  class PlotEndfData
  {
    private:
#ifdef NJOY_MODE
      frendy::BroadenedXSCalculatorWithNjoyFormula calc_dop_obj;
#else
      frendy::BroadenedXSCalculator calc_dop_obj;
#endif

      frendy::LinearizeTabData lin_tab_obj;

      Real temp_ori;

      void set_xs_type_list(frendy::Endf6Parser& endf_obj,  vector<Integer>& xs_type_list);
      void set_xs_data(frendy::Endf6Parser& endf_obj,  vector<Integer> xs_type_list,
                       vector<vector<Real> >& e_int_xs, vector<vector<Real> >& xs_tab);

      void set_mf03_data(frendy::Endf6Parser& endf_obj, int mt_no,
                         vector<Real>& e_int_xs, vector<Real>& xs_tab);
      void set_mf01mt452_data(frendy::Endf6Parser& endf_obj, 
                              vector<Real>& e_int_xs, vector<Real>& xs_tab);
      void set_mf01mt455_data(frendy::Endf6Parser& endf_obj, 
                              vector<Real>& e_int_xs, vector<Real>& xs_tab);
      void set_mf01mt456_data(frendy::Endf6Parser& endf_obj, 
                              vector<Real>& e_int_xs, vector<Real>& xs_tab);
      void set_mf09_data(frendy::Endf6Parser& endf_obj, int mt_no,
                         vector<Real>& e_int_xs, vector<Real>& xs_tab);
      void set_mf10_data(frendy::Endf6Parser& endf_obj, int mt_no,
                         vector<Real>& e_int_xs, vector<Real>& xs_tab);
      void calc_mf10_data(frendy::Endf6Parser& endf_obj, int mt_no,
                          vector<Real>& e_int_xs, vector<Real>& xs_tab);

      void calc_nu_data(vector<Real>& coef_vec,
                        vector<Real>& ene_vec, vector<Real>& nu_vec);

      void resonance_reconstruction(frendy::Endf6Parser& endf_obj,
                                    Real err, Real err_max, Real err_int);

    public:
      //constructor
      PlotEndfData(void);

      //destructor
      virtual ~PlotEndfData(void);

      void clear();

      void plot_endf(string file_name, vector<Integer>& xs_type_list,
                     vector<vector<Real> >& e_int_xs, vector<vector<Real> >& xs_tab,
                     Integer mat, Real temp, Real err, Real err_max, Real err_int);

      void plot_endf(frendy::Endf6Parser& endf_obj, vector<Integer>& xs_type_list,
                     vector<vector<Real> >& e_int_xs, vector<vector<Real> >& xs_tab,
                     Real temp, Real err, Real err_max, Real err_int);
      void plot_endf(string file_name, vector<Integer>& xs_type_list,
                     vector<vector<Real> >& e_int_xs, vector<vector<Real> >& xs_tab,
                     Real temp, Real err, Real err_max, Real err_int);

      void plot_endf(frendy::Endf6Parser& endf_obj, vector<Integer>& xs_type_list,
                     vector<vector<Real> >& e_int_xs, vector<vector<Real> >& xs_tab,
                     Real err, Real err_max, Real err_int);
      void plot_endf(string file_name, vector<Integer>& xs_type_list,
                     vector<vector<Real> >& e_int_xs, vector<vector<Real> >& xs_tab,
                     Real err, Real err_max, Real err_int);

      void plot_endf(frendy::Endf6Parser& endf_obj, vector<Integer>& xs_type_list,
                     vector<vector<Real> >& e_int_xs, vector<vector<Real> >& xs_tab);
      void plot_endf(string file_name, vector<Integer>& xs_type_list,
                     vector<vector<Real> >& e_int_xs, vector<vector<Real> >& xs_tab);

      Real get_temp_ori();
  };
}

#endif //PLOT_ENDF_DATA_H
