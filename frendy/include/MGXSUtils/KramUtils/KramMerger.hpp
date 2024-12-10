#ifndef KRAM_MERGER_H
#define KRAM_MERGER_H

#include "MGXSUtils/KramUtils/KramObject.hpp"

namespace frendy
{
  class KramMerger
  {
    private:
      frendy::ErrorManager err_obj;

      vector<Real> set_weight_vec(int data_no);

      vector<vector<Real> > get_nsf_vec(vector<frendy::KramCommonData>& kram_obj,
                                        vector<vector<Real> >& flux_vec);

    public:
      //constructor
      KramMerger(void);

      //destructor
      virtual ~KramMerger(void);

      void clear();

      frendy::KramCommonData merge_kram(vector<frendy::KramCommonData> kram_obj, int mat_no);
      frendy::KramXsnData    merge_xsn(vector<frendy::KramXsnData> xsn_obj, int mat_no);
      frendy::KramFspData    merge_fsp(vector<frendy::KramFspData> fsp_obj, int mat_no);
      frendy::KramAscData    merge_asc(vector<frendy::KramAscData> asc_obj, int mat_no);

      frendy::KramCommonData merge_kram(vector<frendy::KramCommonData> kram_obj,
                                        vector<Real> weight_vec, int mat_no);
      frendy::KramXsnData    merge_xsn(vector<frendy::KramXsnData> xsn_obj,
                                       vector<Real> weight_vec, int mat_no);
      frendy::KramFspData    merge_fsp(vector<frendy::KramFspData> fsp_obj,
                                       vector<Real> weight_vec, int mat_no);
      frendy::KramAscData    merge_asc(vector<frendy::KramAscData> asc_obj,
                                       vector<Real> weight_vec, int mat_no);


      frendy::KramCommonData merge_kram(vector<frendy::KramCommonData> kram_obj,
                                        vector<Real> weight_vec, vector<vector<Real> > flux_vec,
                                        int mat_no);
      frendy::KramFspData    merge_fsp(vector<frendy::KramFspData> fsp_obj,
                                       vector<Real> weight_vec, vector<vector<Real> > nsf_vec,
                                       int mat_no);
  };
}

#endif // KRAM_MERGER_H
