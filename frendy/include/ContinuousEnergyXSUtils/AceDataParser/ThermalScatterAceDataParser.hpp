#ifndef THERMAL_SCATTER_ACE_DATA_PARSER_H
#define THERMAL_SCATTER_ACE_DATA_PARSER_H

#include "CommonUtils/ErrorManager.hpp"
#include "ContinuousEnergyXSUtils/OtherUtils/AceFileReader.hpp"
#include "ContinuousEnergyXSUtils/AceDataObject/ThermalScatterAceDataObject.hpp"

namespace frendy
{
  class ThermalScatterAceDataParser
  {
    private:
      frendy::ErrorManager      err_obj;
      frendy::VectorClearer     clr_obj;

      static const int max_zi_awr_pair_no = 16;

#ifdef DEBUG_MODE
  public:
#endif
      frendy::AceFileReader     ace_read_obj;

      string          file_name;

      Integer         set_data_flg;

      Integer         mcnpx_mode_flg;
      Real            aw0, tz;
      vector<string>  title_data;
      string          discriptive_data;

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

      void parse_ace_format_header();
      void parse_ace_format_inelastic();
      void parse_ace_format_elastic();

      void clear_ace_data();
      void clear_ace_pointer_data();

      void copy_thermal_scat_ace_data(frendy::ThermalScatterAceDataObject& ace_data_obj);

    public:
      //constructor
      ThermalScatterAceDataParser(void);

      //destructor
      virtual ~ThermalScatterAceDataParser(void);

      void clear();

      void parse_ace_format();

      void set_file_name(string& str_data);
      void set_text_data(vector<string>& str_vec);

      frendy::ThermalScatterAceDataObject get_ace_data_obj();
      string                              get_file_name();
  };
}

#endif //THERMAL_SCATTER_ACE_DATA_PARSER_H
