#ifndef GENDF_MERGER_H
#define GENDF_MERGER_H

#include "EndfUtils/GendfParser/GendfParser.hpp"
#include "CommonUtils/TabInterpolator.hpp"
#include "MGXSUtils/FMGenerator/FMZlib.h"

namespace frendy
{
  class GendfMerger
  {
    private:
      frendy::ErrorManager      err_obj;
      frendy::TabInterpolator   ti_obj;

      Integer mat_new_gendf;
      Real    za_new_gendf, awr_new_gendf;

      void initialize_data1(vector<vector<vector<Real> > >& data1, 
                            int ng, int nsigz, int pl_no);
      void initialize_data2(vector<vector<vector<vector<Real> > > >& data2,
                            int ng, int nsigz, int pl_no);

      vector<frendy::GMF03Parser> transform_gmf13_to_gmf03(vector<frendy::GMF13Parser>& gmf13_obj);

      void modify_total_xs(frendy::GMF03Parser& mf03_mt001_obj, vector<int>& ig_dif_vec,
                           vector<vector<vector<Real> > >& xs_dif_vec);

    public:
      //constructor
      GendfMerger(void);

      //destructor
      virtual ~GendfMerger(void);

      void clear();

      frendy::GMFxxParserBase merge_read_obj(vector<frendy::GMFxxParserBase>& read_obj,
                                             vector<Real> weight_vec);
      frendy::GMFxxParserBase merge_read_obj_micro(vector<frendy::GMFxxParserBase>& read_obj,
                                                   vector<Real> weight_vec);
      frendy::GMFxxParserBase merge_read_obj(vector<frendy::GMFxxParserBase>& read_obj,
                                             vector<Real> weight_vec,
                                             vector<frendy::GMF03Parser>& gmf03_obj);
      frendy::GMFxxParserBase merge_read_obj_micro(vector<frendy::GMFxxParserBase>& read_obj,
                                                   vector<Real> weight_vec,
                                                   vector<frendy::GMF03Parser>& gmf03_obj);
      frendy::GMFxxParserBase merge_read_obj_weight_flux
                                (vector<frendy::GMFxxParserBase>& read_obj, vector<Real> weight_vec,
                                 vector<vector<vector<vector<Real> > > >& flux_vec);
      frendy::GMFxxParserBase merge_read_obj_weight_flux_micro
                                (vector<frendy::GMFxxParserBase>& read_obj, vector<Real> weight_vec,
                                 vector<vector<vector<vector<Real> > > >& flux_vec);

      void check_data(vector<frendy::GMFxxParserBase>& read_obj);

      vector<Integer> get_unit_mt_list(vector<vector<Integer> >& mt_list);


      frendy::GendfParser merge_gendf_data(vector<frendy::GendfParser>& gendf_vec,
                                           vector<Real> weight_vec);
      frendy::GMF03Parser merge_gmf03_data(vector<frendy::GMF03Parser>& gmf03, vector<Real> weight_vec);
      frendy::GMF03Parser merge_gmf03_data(vector<frendy::GMF03Parser>& gmf03, vector<Real> weight_vec,
                                           vector<frendy::GMF03Parser>& gmf03_fis);

      frendy::GMF05Parser merge_gmf05_data(vector<frendy::GMF05Parser>& gmf05, vector<Real> weight_vec);
      frendy::GMF05Parser merge_gmf05_data(vector<frendy::GMF05Parser>& gmf05, vector<Real> weight_vec,
                                           vector<frendy::GMF03Parser>& gmf03);
      frendy::GMF05Parser merge_gmf05_data_weight_flux
                (vector<frendy::GMF05Parser>& gmf05, vector<Real> weight_vec, 
                 vector<vector<vector<vector<Real> > > >& flux_vec);
      frendy::GMF06Parser merge_gmf06_data(vector<frendy::GMF06Parser>& gmf06, vector<Real> weight_vec);
      frendy::GMF06Parser merge_gmf06_data(vector<frendy::GMF06Parser>& gmf06, vector<Real> weight_vec,
                                           vector<frendy::GMF03Parser>& gmf03);
      frendy::GMF06Parser merge_gmf06_data_weight_flux
                (vector<frendy::GMF06Parser>& gmf06, vector<Real> weight_vec, 
                 vector<vector<vector<vector<Real> > > >& flux_vec);
      frendy::GMF13Parser merge_gmf13_data(vector<frendy::GMF13Parser>& gmf13, vector<Real> weight_vec);
      frendy::GMF16Parser merge_gmf16_data(vector<frendy::GMF16Parser>& gmf16, vector<Real> weight_vec);
      frendy::GMF16Parser merge_gmf16_data(vector<frendy::GMF16Parser>& gmf16, vector<Real> weight_vec,
                                           vector<frendy::GMF03Parser>& gmf03);
  };
}

#endif // GENDF_MERGER_H
