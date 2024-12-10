#ifndef GENDF_INTERPOLATOR_H
#define GENDF_INTERPOLATOR_H

#include "EndfUtils/GendfParser/GendfParser.hpp"
#include "CommonUtils/TabInterpolator.hpp"
#include "MGXSUtils/FMGenerator/FMZlib.h"

namespace frendy
{
  class GendfInterpolator
  {
    private:
      frendy::ErrorManager    err_obj;
      frendy::TabInterpolator ti_obj;

    public:
      //constructor
      GendfInterpolator(void);

      //destructor
      virtual ~GendfInterpolator(void);

      void clear();

      frendy::GMFxxParserBase interpolate_read_obj(frendy::GMFxxParserBase read_obj,
                                                   int int_val, Real sigz, vector<Real> sigz_vec);
      frendy::GMFxxParserBase interpolate_read_obj(vector<frendy::GMFxxParserBase> read_obj,
                                                   int int_val, Real temp);
      frendy::GMFxxParserBase interpolate_read_obj(frendy::GMFxxParserBase read_obj01,
                                                   frendy::GMFxxParserBase read_obj02,
                                                   int int_val, Real temp);
      frendy::GMFxxParserBase interpolate_read_obj(frendy::GMFxxParserBase read_obj01,
                                                   frendy::GMFxxParserBase read_obj02,
                                                   frendy::GMFxxParserBase read_obj03,
                                                   int int_val, Real temp);

      void check_data(vector<frendy::GMFxxParserBase>& read_obj, vector<Real>& temp_vec, Real temp);
      void sort_temp(vector<frendy::GMFxxParserBase>& read_obj, vector<Real>& temp_vec);


      frendy::GMF03Parser interpolate_gmf03_data(frendy::GMF03Parser gmf_obj,
                                                 int int_val, Real sigz, vector<Real> sigz_vec);
      frendy::GMF05Parser interpolate_gmf05_data(frendy::GMF05Parser gmf_obj,
                                                 int int_val, Real sigz, vector<Real> sigz_vec);
      frendy::GMF06Parser interpolate_gmf06_data(frendy::GMF06Parser gmf_obj,
                                                 int int_val, Real sigz, vector<Real> sigz_vec);
      frendy::GMF13Parser interpolate_gmf13_data(frendy::GMF13Parser gmf_obj,
                                                 int int_val, Real sigz, vector<Real> sigz_vec);
      frendy::GMF16Parser interpolate_gmf16_data(frendy::GMF16Parser gmf_obj,
                                                 int int_val, Real sigz, vector<Real> sigz_vec);

      vector<frendy::GMF03Parser> interpolate_gmf03_data(vector<frendy::GMF03Parser> gmf_vec,
                                                         int int_val, Real sigz, vector<Real> sigz_vec);
      vector<frendy::GMF05Parser> interpolate_gmf05_data(vector<frendy::GMF05Parser> gmf_vec,
                                                         int int_val, Real sigz, vector<Real> sigz_vec);
      vector<frendy::GMF06Parser> interpolate_gmf06_data(vector<frendy::GMF06Parser> gmf_vec,
                                                         int int_val, Real sigz, vector<Real> sigz_vec);
      vector<frendy::GMF13Parser> interpolate_gmf13_data(vector<frendy::GMF13Parser> gmf_vec,
                                                         int int_val, Real sigz, vector<Real> sigz_vec);
      vector<frendy::GMF16Parser> interpolate_gmf16_data(vector<frendy::GMF16Parser> gmf_vec,
                                                         int int_val, Real sigz, vector<Real> sigz_vec);

      frendy::GendfParser interpolate_gendf_data(frendy::GendfParser gendf_obj, int int_val, Real sigz);


      frendy::GMF03Parser interpolate_gmf03_data(vector<frendy::GMF03Parser>& gmf,
                                                 int int_val, Real temp);
      frendy::GMF05Parser interpolate_gmf05_data(vector<frendy::GMF05Parser>& gmf,
                                                 int int_val, Real temp);
      frendy::GMF06Parser interpolate_gmf06_data(vector<frendy::GMF06Parser>& gmf,
                                                 int int_val, Real temp);
      frendy::GMF13Parser interpolate_gmf13_data(vector<frendy::GMF13Parser>& gmf,
                                                 int int_val, Real temp);
      frendy::GMF16Parser interpolate_gmf16_data(vector<frendy::GMF16Parser>& gmf,
                                                 int int_val, Real temp);

      vector<frendy::GMF03Parser> interpolate_gmf03_data
                                    (vector<vector<frendy::GMF03Parser> >& gmf_vec,
                                     int int_val, Real temp);
      vector<frendy::GMF05Parser> interpolate_gmf05_data
                                    (vector<vector<frendy::GMF05Parser> >& gmf_vec,
                                     int int_val, Real temp);
      vector<frendy::GMF06Parser> interpolate_gmf06_data
                                    (vector<vector<frendy::GMF06Parser> >& gmf_vec,
                                     int int_val, Real temp);
      vector<frendy::GMF13Parser> interpolate_gmf13_data
                                    (vector<vector<frendy::GMF13Parser> >& gmf_vec,
                                     int int_val, Real temp);
      vector<frendy::GMF16Parser> interpolate_gmf16_data
                                    (vector<vector<frendy::GMF16Parser> >& gmf_vec,
                                     int int_val, Real temp);

      frendy::GendfParser interpolate_gendf_data
                            (vector<frendy::GendfParser>& gendf_vec,
                             int int_val, Real temp);



      frendy::GendfParser interpolate_gendf_data
                            (vector<frendy::GendfParser> gendf_vec,
                             int int_temp, Real temp, int int_sigz, Real sigz);
  };
}

#endif // GENDF_INTERPOLATOR_H
