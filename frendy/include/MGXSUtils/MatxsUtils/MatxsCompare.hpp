#ifndef MATXS_COMPARE_H
#define MATXS_COMPARE_H

#include "MGXSUtils/MatxsUtils/MatxsParser.hpp"
#include "MGXSUtils/MatxsUtils/MatxsObject.hpp"
#include "ContinuousEnergyXSUtils/AceDataCompare/AceDataCompare.hpp"

namespace frendy
{
  class MatxsCompare
  {
    private:
      frendy::ErrorManager    err_obj;

      frendy::AceDataCompare  comp_obj;

      frendy::MatxsCommonData matxs_obj_com, matxs_obj_ref;

      string class_name;

      int    add_original_data_flg;
      string hmat_info, hmtx_info;
      int    structure_pos, mat_pos, submat_pos, matrix_pos;

      void comp_matxs_file();

      vector<Real> modify_vps_data(Integer nfg, Integer nlg, vector<Real> vps, Integer ng);
      vector<Real> modify_scat_data(Integer jband, Integer ijj, vector<Real> scat, Integer ng);

      frendy::MatxsSubmaterialData add_submaterial_data(frendy::MatxsSubmaterialData submat_obj_dif,
                                                        frendy::MatxsSubmaterialData submat_obj_ori);
      vector<frendy::MatxsMatrixData> add_matrix_data(vector<frendy::MatxsMatrixData> matrix_obj_dif,
                                                      vector<frendy::MatxsMatrixData> matrix_obj_ori);

    public:

      //constructor
      MatxsCompare(void);

      //destructor
      virtual ~MatxsCompare(void);

      void clear();

      void comp_matxs_file(string matxs_name_com, string matxs_name_ref);

      void comp_matxs_file(frendy::MatxsCommonData parse_obj_com, frendy::MatxsCommonData parse_obj_ref);

      //0v, 1d, 2d, and 3d
      void comp_common_data(frendy::MatxsCommonData parse_obj_com, frendy::MatxsCommonData parse_obj_ref);

      
      //4d
      void comp_structure_data(vector<frendy::MatxsGroupStructureData> parse_obj_com,
                               vector<frendy::MatxsGroupStructureData> parse_obj_ref);
      //5d
      void comp_material_data(vector<frendy::MatxsMaterialData> parse_obj_com,
                              vector<frendy::MatxsMaterialData> parse_obj_ref);
      //6d and 7d
      void comp_submaterial_data(vector<frendy::MatxsSubmaterialData> parse_obj_com,
                                 vector<frendy::MatxsSubmaterialData> parse_obj_ref);
      //8d, 9d, and 10d
      void comp_matrix_data(vector<frendy::MatxsMatrixData> parse_obj_com,
                            vector<frendy::MatxsMatrixData> parse_obj_ref);
      
      //4d
      void comp_structure_data(frendy::MatxsGroupStructureData parse_obj_com,
                               frendy::MatxsGroupStructureData parse_obj_ref);
      //5d
      void comp_material_data(frendy::MatxsMaterialData parse_obj_com,
                              frendy::MatxsMaterialData parse_obj_ref);
      //6d and 7d
      void comp_submaterial_data(frendy::MatxsSubmaterialData parse_obj_com,
                                 frendy::MatxsSubmaterialData parse_obj_ref);
      //8d, 9d, and 10d
      void comp_matrix_data(frendy::MatxsMatrixData parse_obj_com,
                            frendy::MatxsMatrixData parse_obj_ref);

      void set_tolerance_val(Real tolerance_val);
      Real get_tolerance_val();

      void set_add_original_data_flg(int int_data);
      int  get_add_original_data_flg();
  }; 
}

#endif //MATXS_COMPARE_H
