#ifndef THERMAL_SCATTER_ACE_DATA_WRITER_H
#define THERMAL_SCATTER_ACE_DATA_WRITER_H

#include "CommonUtils/ErrorManager.hpp"
#include "CommonUtils/VectorClearer.hpp"
#include "CommonUtils/VectorSizeChecker.hpp"
#include "CommonUtils/DigitAdjuster.hpp"
#include "ContinuousEnergyXSUtils/AceDataObject/ThermalScatterAceDataObject.hpp"
#include "ContinuousEnergyXSUtils/OtherUtils/AceFileWriter.hpp"

namespace frendy
{
  class ThermalScatterAceDataWriter
  {
    private:
      frendy::ErrorManager      err_obj;
      frendy::VectorClearer     clr_obj;
      frendy::DigitAdjuster     ad_obj;
      frendy::VectorSizeChecker vec_size_check_obj;
      frendy::AceFileWriter     ace_wri_obj;

      static const Real8 min_second_ene_dif_abs;

#ifdef DEBUG_MODE
  public:
#endif
      Integer set_data_flg, set_ace_data_obj_flg;

      frendy::ThermalScatterAceDataObject ace_data_obj;

      Integer pointer_data_count;

      //For output
      Integer opt_out_type;
      Integer opt_weight;
      string  ace_file_name;

      Integer line_no_pre;

      //For ACE data
      Integer         mcnpx_mode_flg;
      Real            aw0, tz;
      vector<string>  title_data;
      string          discriptive_data;

      vector<Integer> mod_za;
      vector<Integer> zi_vec;
      vector<Real>    awr_vec;

      //For elastic
      vector<Real>          coh_elastic_ene_data,   coh_elastic_e_xs_data,
                            incoh_elastic_ene_data, incoh_elastic_xs_data;
      vector<vector<Real> > incoh_elastic_scat_angle;

      //For inelastic
      vector<Real>                   inelastic_ene_data, inelastic_xs_data;
      vector<vector<Real> >          inelastic_second_ene, inelastic_scat_xs_int,
                                     inelastic_weight;
      vector<vector<vector<Real> > > inelastic_scat_xs_weight;

      //For pointer data
      int         len2, idpni, nil, nieb, idpnc, ncl,  ifeng, ncli,
                  itie, itix, itxe, itce, itcx,  itca, itcei, itcxi, itcai,
                  nie,  nee;

      void clear_ace_data();
      void clear_ace_pointer_data();

      void copy_thermal_scat_ace_data();
      void copy_thermal_scat_ace_pointer_data(frendy::ThermalScatterAceDataObject& thermal_scat_ace_data_obj);

      Integer get_line_no();

      //Write ace file
      void output_ace_format();
      void output_ace_format_header();
      void output_ace_format_inelastic();
      void output_ace_format_elastic();

      void output_ace_format_binary_mode();

      void calc_ace_header_file_data();

      void check_set_data();

      void mod_inelastic_data();
      void mod_inelastic_second_ene_data(int i);
      void mod_inelastic_scat_xs_weight_data(int i, int j);

    public:
      //constructor
      ThermalScatterAceDataWriter(void);

      //destructor
      virtual ~ThermalScatterAceDataWriter(void);

      static const Integer ascii_mode  = 1;
      static const Integer binary_mode = 2;

      void clear();

      void write_ace_format();
      vector<string> get_ace_text_data();
      void get_ace_data_for_mg(vector<string>& title_vec, vector<int>& izaw_vec,
                               vector<int>& nxs_vec, vector<int>& jxs_vec,
                               vector<double>& xss_vec);
      vector<double> get_xss_data();

      void   write_dir_data(string dir_name);
      string get_dir_data();

      //Setter
      void set_ace_data_obj(frendy::ThermalScatterAceDataObject& data_obj);
      void set_opt_out_type(Integer int_val);
      void set_opt_weight(Integer int_val);
      void set_ace_file_name(string str_data);
      void set_previous_line_no(Integer int_val);

      //Getter
      frendy::ThermalScatterAceDataObject get_ace_data_obj();
      Integer                             get_opt_out_type();
      Integer                             get_opt_weight();
      string                              get_ace_file_name();
      Integer                             get_previous_line_no();
  };
}

#endif //THERMAL_SCATTER_ACE_DATA_WRITER_H
