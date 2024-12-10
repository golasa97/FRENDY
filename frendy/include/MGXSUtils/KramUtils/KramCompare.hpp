#ifndef KRAM_COMPARE_H
#define KRAM_COMPARE_H

#include "MGXSUtils/KramUtils/KramParser.hpp"
#include "MGXSUtils/KramUtils/KramObject.hpp"
#include "ContinuousEnergyXSUtils/AceDataCompare/AceDataCompare.hpp"

namespace frendy
{
  class KramCompare
  {
    private:
      frendy::ErrorManager    err_obj;
      frendy::AceDataCompare  comp_obj;
      frendy::KramCommonData  kram_obj_com, kram_obj_ref;

#ifdef DEBUG_MODE
  public:
#endif
      string class_name;

      void comp_kram_file();

      void check_mat_list(string func_name, vector<Integer>& list_com, vector<Integer>& list_ref,
                                            vector<Integer>& list_both);

    public:

      //constructor
      KramCompare(void);

      //destructor
      virtual ~KramCompare(void);

      void clear();

      void comp_kram_file(string kram_name_com, string kram_name_ref, int mg_no);

      void comp_kram_file(frendy::KramCommonData parse_obj_com, frendy::KramCommonData parse_obj_ref);

      //Comparison of XSN data
      void comp_xsn_vec(vector<frendy::KramXsnData> xsn_vec_com,
                        vector<frendy::KramXsnData> xsn_vec_ref);
      void comp_xsn_data(frendy::KramXsnData xsn_obj_com, frendy::KramXsnData xsn_obj_ref);

      //Comparison of FSP data
      void comp_fsp_vec(vector<frendy::KramFspData> fsp_vec_com,
                        vector<frendy::KramFspData> fsp_vec_ref);
      void comp_fsp_data(frendy::KramFspData fsp_obj_com, frendy::KramFspData fsp_obj_ref);

      //Comparison of ASC data
      void comp_asc_vec(vector<frendy::KramAscData> asc_vec_com,
                        vector<frendy::KramAscData> asc_vec_ref);
      void comp_asc_data(frendy::KramAscData asc_obj_com, frendy::KramAscData asc_obj_ref);

      void set_tolerance_val(Real tolerance_val);
      Real get_tolerance_val();
  }; 
}

#endif //KRAM_COMPARE_H
