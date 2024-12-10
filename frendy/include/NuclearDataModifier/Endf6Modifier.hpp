#ifndef ENDF6_MODIFIER_H
#define ENDF6_MODIFIER_H

#include "CommonUtils/ErrorManager.hpp"
#include "EndfUtils/Endf6Parser/Endf6Parser.hpp"
#include "EndfUtils/Endf6Converter/Endf6Converter.hpp"

namespace frendy
{
  class Endf6Modifier
  {
    private:
      frendy::ErrorManager  err_obj;

      frendy::Endf6Converter endf_conv_obj;

      Integer mat_ori;
      Real    za_ori, awr_ori;

      void check_MF_number(Integer mf_no);
      void check_MF_MT_number(Integer mf_no, Integer mt_no);
      void get_ZA_AWR_value(frendy::Endf6Parser& endf_obj_ori, frendy::Endf6Parser& endf_obj_add);

      void merge_specified_MF_data
             (frendy::Endf6Parser& endf_obj_ori, frendy::Endf6Parser& endf_obj_add, Integer mf_no,
              int& ori_flg, int& mod_flg);

      void merge_specified_MF_MT_data
             (frendy::Endf6Parser& endf_obj_ori, frendy::Endf6Parser& endf_obj_add, Integer mf_no, Integer mt_no,
              int& ori_flg, int& mod_flg);
      void merge_specified_MF_MT_data_without_error_message
             (frendy::Endf6Parser& endf_obj_ori, frendy::Endf6Parser& endf_obj_add, Integer mf_no, Integer mt_no,
              int& ori_flg, int& mod_flg, int& no_data_flg);

      void remove_specified_MF_MT_data_without_error_message
             (frendy::Endf6Parser& endf_obj, Integer mf_no, Integer mt_no, int& remove_flg);

    public:
      //constructor
      Endf6Modifier(void);

      //destructor
      virtual ~Endf6Modifier(void);

      void remove_specified_MF_data
             (frendy::NuclearDataObject& nucl_obj, Integer mf_no);
      void remove_specified_MF_data
             (frendy::Endf6Parser& endf_obj, Integer mf_no);

      void change_specified_MF_data
             (frendy::NuclearDataObject& nucl_obj_ori, frendy::NuclearDataObject& nucl_obj_add, Integer mf_no);
      void change_specified_MF_data
             (Endf6Parser& endf_obj_ori, Endf6Parser& endf_obj_add, Integer mf_no);

      void add_specified_MF_data
             (frendy::NuclearDataObject& nucl_obj_ori, frendy::NuclearDataObject& nucl_obj_add, Integer mf_no);
      void add_specified_MF_data
             (Endf6Parser& endf_obj_ori, Endf6Parser& endf_obj_add, Integer mf_no);

      void remove_specified_MF_MT_data
             (frendy::NuclearDataObject& nucl_obj, Integer mf_no, Integer mt_no);
      void remove_specified_MF_MT_data
             (Endf6Parser& endf_obj, Integer mf_no, Integer mt_no);

      void change_specified_MF_MT_data
             (frendy::NuclearDataObject& nucl_obj_ori, frendy::NuclearDataObject& nucl_obj_add, Integer mf_no, Integer mt_no);
      void change_specified_MF_MT_data
             (Endf6Parser& endf_obj_ori, Endf6Parser& endf_obj_add, Integer mf_no, Integer mt_no);

      void add_specified_MF_MT_data
             (frendy::NuclearDataObject& nucl_obj_ori, frendy::NuclearDataObject& nucl_obj_add, Integer mf_no, Integer mt_no);
      void add_specified_MF_MT_data
             (Endf6Parser& endf_obj_ori, Endf6Parser& endf_obj_add, Integer mf_no, Integer mt_no);
  };
}

#endif //ENDF6_MODIFIER_H
