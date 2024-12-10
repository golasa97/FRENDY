#ifndef GENDF_MODIFIER_H
#define GENDF_MODIFIER_H

#include "CommonUtils/ErrorManager.hpp"
#include "EndfUtils/GendfParser/GendfParser.hpp"

namespace frendy
{
  class GendfModifier
  {
    private:
      frendy::ErrorManager  err_obj;

      Integer mat_ori;
      Real    za_ori, awr_ori, temp_ori;

      void check_MF_number(Integer mf_no);
      void check_MF_MT_number(Integer mf_no, Integer mt_no);
      void get_ZA_AWR_value(frendy::GendfParser& gendf_obj_ori, frendy::GendfParser& gendf_obj_add);
      void get_EGN_EGG_value(frendy::GendfParser& gendf_obj_ori, frendy::GendfParser& gendf_obj_add);

      void merge_specified_MF_data
             (frendy::GendfParser& gendf_obj_ori, frendy::GendfParser& gendf_obj_add, Integer mf_no,
              int& ori_flg, int& mod_flg);

      void merge_specified_MF_MT_data
             (frendy::GendfParser& gendf_obj_ori, frendy::GendfParser& gendf_obj_add, Integer mf_no, Integer mt_no,
              int& ori_flg, int& mod_flg);
      void merge_specified_MF_MT_data_without_error_message
             (frendy::GendfParser& gendf_obj_ori, frendy::GendfParser& gendf_obj_add, Integer mf_no, Integer mt_no,
              int& ori_flg, int& mod_flg, int& no_data_flg);

      void remove_specified_MF_MT_data_without_error_message
             (frendy::GendfParser& gendf_obj, Integer mf_no, Integer mt_no, int& remove_flg);

    public:
      //constructor
      GendfModifier(void);

      //destructor
      virtual ~GendfModifier(void);

      void remove_specified_MF_data
             (frendy::GendfParser& gendf_obj, Integer mf_no);

      void change_specified_MF_data
             (GendfParser& gendf_obj_ori, GendfParser& gendf_obj_add, Integer mf_no);

      void add_specified_MF_data
             (GendfParser& gendf_obj_ori, GendfParser& gendf_obj_add, Integer mf_no);

      void remove_specified_MF_MT_data
             (GendfParser& gendf_obj, Integer mf_no, Integer mt_no);

      void change_specified_MF_MT_data
             (GendfParser& gendf_obj_ori, GendfParser& gendf_obj_add, Integer mf_no, Integer mt_no);

      void add_specified_MF_MT_data
             (GendfParser& gendf_obj_ori, GendfParser& gendf_obj_add, Integer mf_no, Integer mt_no);
  };
}

#endif //GENDF_MODIFIER_H
