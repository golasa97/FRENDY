#ifndef MATXS_MERGER_H
#define MATXS_MERGER_H

#include "CommonUtils/VectorClearer.hpp"
#include "CommonUtils/ErrorManager.hpp"
#include "CommonUtils/StringUtils.hpp"
#include "EndfUtils/EndfFileReader/EndfUtils.hpp"
#include "MGXSUtils/MatxsUtils/MatxsObject.hpp"
#include "MGXSUtils/MatxsUtils/MatxsParser.hpp"
#include "MGXSUtils/MatxsUtils/MatxsWriter.hpp"

namespace frendy
{
  class MatxsMerger
  {
    private:
      frendy::ErrorManager err_obj;
      frendy::StringUtils  str_util;

#ifdef DEBUG_MODE
  public:
#endif
      Real tolerance;


      frendy::MatxsCommonData         matxs_obj;
      vector<frendy::MatxsCommonData> matxs_obj_vec;

      vector<string> hpart_new, htype_new, hmatn_new;
      vector<vector<int> > diff_data_list;

      void merge_matxs_obj();

      void check_set_data();
      void add_name_list(vector<string>& name_list, vector<string> name_list_add);
      int  check_name_list(vector<string>& name_list, string name_list_add);

       void modify_part_and_type_data();
       void modify_part_data(vector<int> hpart_no_list, 
                             vector<int>& ngrp, vector<int>& jinp, vector<int>& joutp,
                             vector<frendy::MatxsGroupStructureData>& ng_obj);
       void modify_type_data(vector<int> htype_no_list,
                             vector<int>& jinp, vector<int>& joutp, vector<int>& itype);

       void check_energy_group();

       void merge_3d_and_4d_data();
       void merge_5d_data();
       int  check_temp_sigz_itype(vector<Real>&    temp_new,  Real&    temp_val,
                                  vector<Real>&    sigz_new,  Real&    sigz_val,
                                  vector<Integer>& itype_new, Integer& itype_val);
       void sort_5d_data();

       void mod_6d_10d_data();
       int  check_sigz_itype(int pos, vector<Real>& sigz, vector<Integer>& itype);

       void mod_submat_data(frendy::MatxsSubmaterialData& submat_ori,
                            frendy::MatxsSubmaterialData& submat_dif, int merge_flg);
       void mod_7d_data(string& hvps, Integer& nfg_ori, Integer& nlg_ori, vector<Real>& vps_ori,
                                      Integer& nfg_dif, Integer& nlg_dif, vector<Real>& vps_dif,
                        int merge_flg);
       void mod_matrix_data(frendy::MatxsSubmaterialData& submat_ori,
                            frendy::MatxsSubmaterialData& submat_dif, int merge_flg);
       void mod_8d_10d_data(frendy::MatxsMatrixData& matrix_ori,
                            frendy::MatxsMatrixData& matrix_dif, int merge_flg);
       void check_matrix_data(frendy::MatxsMatrixData& matrix_ori,
                              frendy::MatxsMatrixData& matrix_dif);
       void mod_9d_data(frendy::MatxsMatrixData& matrix_ori,
                        frendy::MatxsMatrixData& matrix_dif, int merge_flg);
       Real calc_scat(int j, int k, Integer& jband, Integer& ijj, vector<vector<Real> >& scat);
       void mod_scat_data(vector<Integer>& jband, vector<Integer>& ijj,
                          vector<vector<vector<Real > > >& scat);
       void remove_zero_scat_data(Integer& jband, Integer& ijj, vector<vector<Real > >& scat);


    public:

      //constructor
      MatxsMerger(void);

      //destructor
      virtual ~MatxsMerger(void);

      void clear();

      void merge_matxs_file(vector<string> file_name_vec);
      void merge_matxs_obj(vector<frendy::MatxsCommonData> matxs_vec);

      vector<string> get_text();

      frendy::MatxsCommonData get_matxs_obj();

      void write_matxs_obj(string file_name);
  }; 
}

#endif //MATXS_MERGER_H
