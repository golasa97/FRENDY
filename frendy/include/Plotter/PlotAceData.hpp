#ifndef PLOT_ACE_DATA_H
#define PLOT_ACE_DATA_H

#include "CommonUtils/FileCommentRemover.hpp"
#include "CommonUtils/TabInterpolator.hpp"
#include "CommonUtils/TabAdjuster.hpp"
#include "CommonUtils/DigitAdjuster.hpp"
#include "NuclearDataUtils/OtherUtils/Endf6FileStore.hpp"
#include "ContinuousEnergyXSUtils/AceDataParser/FastAceDataParser.hpp"
#include "ContinuousEnergyXSUtils/AceDataParser/ThermalScatterAceDataParser.hpp"
#include "ContinuousEnergyXSUtils/AceDataParser/DosimetryAceDataParser.hpp"
#include "TabUtils/IntegrateTabData.hpp"
#include "TabUtils/LinearizeTabData.hpp"
#include "DopplerBroadening/DopplerCalculator.hpp"

namespace frendy
{
  class PlotAceData
  {
    private:
      frendy::ErrorManager        err_obj;

#ifdef NJOY_MODE
      frendy::BroadenedXSCalculatorWithNjoyFormula calc_dop_obj;
#else
      frendy::BroadenedXSCalculator calc_dop_obj;
#endif

      Real temp_ori;

      void set_xs_type_list_fast(frendy::FastAceDataObject& ace_obj, vector<Integer>& xs_type_list);
      void set_xs_data_fast(frendy::FastAceDataObject& ace_obj, vector<Integer>& xs_type_list,
                            vector<vector<Real> >& e_int_xs, vector<vector<Real> >& xs_tab);

      void read_nu_data(frendy::FastAceDataObject& ace_obj, int mt_no,
                        vector<Real>& e_vec, vector<Real>& nu_vec);


      void set_xs_type_list_tsl(frendy::ThermalScatterAceDataObject& ace_obj,
                                vector<Integer>& xs_type_list);
      void set_xs_data_tsl(frendy::ThermalScatterAceDataObject& ace_obj,
                           vector<Integer>& xs_type_list,
                           vector<vector<Real> >& e_int_xs, vector<vector<Real> >& xs_tab);

      void set_xs_type_list_dosi(frendy::DosimetryAceDataObject& ace_obj, vector<Integer>& xs_type_list);
      void set_xs_data_dosi(frendy::DosimetryAceDataObject& ace_obj, vector<Integer>& xs_type_list,
                            vector<vector<Real> >& e_int_xs, vector<vector<Real> >& xs_tab);

    public:
      //constructor
      PlotAceData(void);

      //destructor
      virtual ~PlotAceData(void);

      void clear();

      void read_ace_file_fast(string file_name, vector<int>& xs_type_list,
                              vector<vector<Real> >& e_int_xs, vector<vector<Real> >& xs_tab);
      void read_ace_file_tsl(string file_name, vector<int>& xs_type_list,
                             vector<vector<Real> >& e_int_xs, vector<vector<Real> >& xs_tab);
      void read_ace_file_dosi(string file_name, vector<int>& xs_type_list,
                              vector<vector<Real> >& e_int_xs, vector<vector<Real> >& xs_tab);

      void plot_ace(string file_name, vector<Integer>& xs_type_list,
                    vector<vector<Real> >& e_int_xs, vector<vector<Real> >& xs_tab,
                    Real temp);

      void plot_ace_fast(frendy::FastAceDataParser& ace_obj, vector<Integer>& xs_type_list,
                         vector<vector<Real> >& e_int_xs, vector<vector<Real> >& xs_tab);
      void plot_ace_tsl(frendy::ThermalScatterAceDataParser& ace_obj, vector<Integer>& xs_type_list,
                         vector<vector<Real> >& e_int_xs, vector<vector<Real> >& xs_tab);
      void plot_ace_dosi(frendy::DosimetryAceDataParser& ace_obj, vector<Integer>& xs_type_list,
                         vector<vector<Real> >& e_int_xs, vector<vector<Real> >& xs_tab);
      void plot_ace(string file_name, vector<Integer>& xs_type_list,
                    vector<vector<Real> >& e_int_xs, vector<vector<Real> >& xs_tab);

      Real get_temp_ori();
  };
}

#endif //PLOT_ACE_DATA_H
