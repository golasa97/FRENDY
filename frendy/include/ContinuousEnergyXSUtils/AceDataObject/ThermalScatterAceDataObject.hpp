#ifndef THERMAL_SCATTER_ACE_DATA_OBJECT_H
#define THERMAL_SCATTER_ACE_DATA_OBJECT_H

#include "Config/CommonData.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class ThermalScatterAceDataObject
  {
    private:
      void clear_ace_data();
      void clear_ace_pointer_data();

      frendy::VectorClearer clr_obj;

      Integer         mcnpx_mode_flg;
      Integer         mat;
      Real            temp;

      vector<Integer> mod_za;
      vector<Integer> zi_vec;
      vector<Real>    awr_vec;

      Real            aw0, tz;
      vector<string>  title_data;
      string          discriptive_data;

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
      int len2, idpni, nil, nieb, idpnc, ncl,  ifeng, ncli,
          itie, itix, itxe, itce, itcx,  itca, itcei, itcxi, itcai,
          nie, nee;

////////////////////////////////////////////////////////////////////////////////////////////////////

    public:
      //constructor
      ThermalScatterAceDataObject(void);

      //destructor
      virtual ~ThermalScatterAceDataObject(void);

      static const Real8 min_second_ene_dif_abs; //=  1.0E-15;

      void clear();

////////////////////////////////////////////////////////////////////////////////////////////////////

      //Setter
      void set_mcnpx_mode_flg(Integer int_val);
      void set_mat(Integer int_val);
      void set_temp(Real real_val);

      void set_mod_za(vector<Integer> int_vec);
      void set_zi_vec(vector<Integer> int_vec);
      void set_awr_vec(vector<Real>   real_vec);

      void set_aw0(Real real_val);
      void set_tz(Real real_val);
      void set_title_data(vector<string> str_vec);
      void set_discriptive_data(string str_data);

      //For elastic
      void set_coh_elastic_ene_data(vector<Real> real_vec);
      void set_coh_elastic_e_xs_data(vector<Real> real_vec);
      void set_incoh_elastic_ene_data(vector<Real> real_vec);
      void set_incoh_elastic_xs_data(vector<Real> real_vec);
      void set_incoh_elastic_scat_angle(vector<vector<Real> > real_vec);

      //For inelastic
      void set_inelastic_ene_data(vector<Real> real_vec);
      void set_inelastic_xs_data(vector<Real> real_vec);
      void set_inelastic_second_ene(vector<vector<Real> > real_vec);
      void set_inelastic_scat_xs_int(vector<vector<Real> > real_vec);
      void set_inelastic_weight(vector<vector<Real> > real_vec);
      void set_inelastic_scat_xs_weight(vector<vector<vector<Real> > > real_vec);

      //For pointer
      void set_len2(int int_val);
      void set_idpni(int int_val);
      void set_nil(int int_val);
      void set_nieb(int int_val);
      void set_idpnc(int int_val);
      void set_ncl(int int_val);
      void set_ifeng(int int_val);
      void set_ncli(int int_val);
      void set_itie(int int_val);
      void set_itix(int int_val);
      void set_itxe(int int_val);
      void set_itce(int int_val);
      void set_itcx(int int_val);
      void set_itca(int int_val);
      void set_itcei(int int_val);
      void set_itcxi(int int_val);
      void set_itcai(int int_val);
      void set_nie(int int_val);
      void set_nee(int int_val);

////////////////////////////////////////////////////////////////////////////////////////////////////

      //Getter
      Integer         get_mcnpx_mode_flg();
      Integer         get_mat();
      Real            get_temp();
      Real            get_temp_ev();
      Real            get_temp_kelvin();

      vector<Integer> get_mod_za();
      vector<Integer> get_zi_vec();
      vector<Real>    get_awr_vec();

      Real            get_aw0();
      Real            get_tz();
      vector<string>  get_title_data();
      string          get_discriptive_data();

      //For elastic
      vector<Real>          get_coh_elastic_ene_data();
      vector<Real>          get_coh_elastic_e_xs_data();
      vector<Real>          get_incoh_elastic_ene_data();
      vector<Real>          get_incoh_elastic_xs_data();
      vector<vector<Real> > get_incoh_elastic_scat_angle();

      //For inelastic
      vector<Real>                   get_inelastic_ene_data();
      vector<Real>                   get_inelastic_xs_data();
      vector<vector<Real> >          get_inelastic_second_ene();
      vector<vector<Real> >          get_inelastic_scat_xs_int();
      vector<vector<Real> >          get_inelastic_weight();
      vector<vector<vector<Real> > > get_inelastic_scat_xs_weight();

      //For pointer
      int         get_len2();
      int         get_idpni();
      int         get_nil();
      int         get_nieb();
      int         get_idpnc();
      int         get_ncl();
      int         get_ifeng();
      int         get_ncli();
      int         get_itie();
      int         get_itix();
      int         get_itxe();
      int         get_itce();
      int         get_itcx();
      int         get_itca();
      int         get_itcei();
      int         get_itcxi();
      int         get_itcai();
      int         get_nie();
      int         get_nee();
  };
}

#endif //THERMAL_SCATTER_ACE_DATA_OBJECT_H
