#ifndef PLOT_GENDF_DATA_H
#define PLOT_GENDF_DATA_H

#include "CommonUtils/TabInterpolator.hpp"
#include "CommonUtils/FileCommentRemover.hpp"
#include "CommonUtils/StringUtils.hpp"
#include "CommonUtils/DigitAdjuster.hpp"
#include "EndfUtils/GendfParser/GendfParser.hpp"
#include "EndfUtils/GendfParser/GendfTapeDivider.hpp"
#include "TabUtils/LinearizeTabData.hpp"
#include "FrendyUtils/NuclearDataPlotterInputReader.hpp"

namespace frendy
{
  class PlotGendfData
  {
    private:
      frendy::ErrorManager                   err_obj;
      frendy::DigitAdjuster                  digit_obj;
      frendy::NuclearDataPlotterInputReader  frendy_inp_obj;

      int                   graph_type;

      string                gendf_file_name;
      Integer               mf_val, mt_val;
      Real                  temp_ori;

      vector<Real>          sigz_vec;

      vector<vector<vector<Real> > > make_xs_array(vector<Real>& xs_vec);

      void read_gmf03_data(string& out_name, string& gendf_name, frendy::GendfParser& gendf_obj,
                           vector<Integer>& mt_list);
      void read_gmf05_data(string& out_name, string& gendf_name, frendy::GendfParser& gendf_obj,
                           vector<Integer>& mt_list);
      void read_gmf06_data(string& out_name, string& gendf_name, frendy::GendfParser& gendf_obj,
                           vector<Integer>& mt_list);
      void read_gmf13_data(string& out_name, string& gendf_name, frendy::GendfParser& gendf_obj,
                           vector<Integer>& mt_list);
      void read_gmf16_data(string& out_name, string& gendf_name, frendy::GendfParser& gendf_obj,
                           vector<Integer>& mt_list);

     void output_gmf_data(string& out_name, string& gendf_name,
                          frendy::GMFxxParserBase gmf_obj,
                          vector<Real> mg_vec_in, vector<Real> mg_vec_out, int graph_type);
     void output_gmf_data(string& out_name, string& gendf_name,
                          frendy::GMFxxParserBase gmf_obj,
                          vector<Real> mg_vec_in, vector<Real> mg_vec_out);
     void output_gmf_data_histogram(string& out_name, string& gendf_name,
                                    frendy::GMFxxParserBase gmf_obj,
                                    vector<Real> mg_vec_in, vector<Real> mg_vec_out);

    public:
      //constructor
      PlotGendfData(void);

      //destructor
      virtual ~PlotGendfData(void);

      void clear();

      frendy::GendfParser read_gendf_file(string gendf_name);
      frendy::GendfParser read_gendf_file(string gendf_name, Integer& mat);
      frendy::GendfParser read_gendf_file(string gendf_name, Real& temp);
      frendy::GendfParser read_gendf_file(string gendf_name, Integer& mat, Real& temp);

      void output_1d_data(string case_name, vector<Real>& mg_vec_in,
                          vector<vector<vector<Real> > >& xs_vec);

      void output_1d_data(string case_name, vector<Real>& mg_vec_in, vector<Real>& xs_vec);

      void output_2d_data(string case_name, vector<Real>& mg_vec_in, vector<Real>& mg_vec_out,
                          vector<vector<vector<vector<Real> > > >& ddx_vec);
      void output_2d_data_angle(string case_name, vector<Real>& mg_vec_in,
                                vector<Real>& mg_vec_out,
                                vector<vector<vector<vector<Real> > > >& ddx_vec);

      void get_1d_data(vector<int>& ig, vector<vector<vector<Real> > >& data2,
                       vector<Real>& mg_vec_in, vector<vector<vector<Real> > >& xs_vec);

      void get_2d_data(vector<int>& ig, vector<int>& ng2, vector<int>& ig2,
                       vector<vector<vector<vector<Real> > > >& data2,
                       vector<Real>& mg_vec_in, vector<Real>& mg_vec_out,
                       vector<vector<vector<vector<Real> > > >& ddx_vec);

      void get_1d_data_from_2d_data
                      (vector<int>& ig, vector<int>& ng2, vector<int>& ig2,
                       vector<vector<vector<vector<Real> > > >& data2,
                       vector<Real>& mg_vec_in, vector<Real>& mg_vec_out,
                       vector<vector<vector<Real> > >& xs_vec);


      void output_gendf_data(string& out_name, string& gendf_name,
                             frendy::GendfParser& gendf_obj, Integer& mat, Real& temp,
                             vector<Integer>& mf_list, vector<Integer>& mt_list, int graph_type_flg);
      void output_gendf_data(string& out_name, string& gendf_name,
                             Integer& mat, Real& temp,
                             vector<Integer>& mf_list, vector<Integer>& mt_list, int graph_type_flg);

      void set_graph_type(int graph_type_flg);
      int  get_graph_type();

      Real get_temp_ori();
  };
}

#endif //PLOT_GENDF_DATA_H
