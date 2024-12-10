#ifndef DOSIMETRY_ACE_DATA_OBJECT_H
#define DOSIMETRY_ACE_DATA_OBJECT_H

#include "Config/CommonData.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class DosimetryAceDataObject
  {
    private:
      void clear_ace_data();
      void clear_ace_pointer_data();

      frendy::VectorClearer clr_obj;

      Integer         mat, za_val;
      Real            temp;

      //For ACE data
      vector<Integer> zi_vec;
      vector<Real>    awr_vec;

      Integer         mcnpx_mode_flg;

      Real            aw0, tz;
      vector<string>  title_data;
      string          discriptive_data;

      //For XS data
      vector<Integer>          reaction_xs_reaction_type, reaction_xs_pointer;
      vector<vector<Integer> > reaction_xs_range_data, reaction_xs_int_data;
      vector<vector<Real> >    reaction_xs_ene_data,   reaction_xs_data;

      vector<vector<Integer> >          production_xs_state_no_product, production_xs_pointer;
      vector<vector<vector<Integer> > > production_xs_range_data, production_xs_int_data;
      vector<vector<vector<Real> > >    production_xs_ene_data,   production_xs_data;

      //For pointer data
      int len2, za, ntr, lone, mtr, lsig, sigd, end;

////////////////////////////////////////////////////////////////////////////////////////////////////

    public:
      //constructor
      DosimetryAceDataObject(void);

      //destructor
      virtual ~DosimetryAceDataObject(void);

      void clear();

////////////////////////////////////////////////////////////////////////////////////////////////////

      //Setter
      void set_mcnpx_mode_flg(Integer int_val);
      void set_mat(Integer int_val);
      void set_temp(Real real_val);

      void set_zi_vec(vector<Integer> int_vec);
      void set_awr_vec(vector<Real>   real_vec);

      void set_aw0(Real real_val);
      void set_tz(Real real_val);
      void set_title_data(vector<string> str_vec);
      void set_discriptive_data(string str_data);

      void set_reaction_xs_reaction_type(vector<Integer> int_vec);
      void set_reaction_xs_pointer(vector<Integer> int_vec);
      void set_reaction_xs_range_data(vector<vector<Integer> > int_vec);
      void set_reaction_xs_int_data(vector<vector<Integer> > int_vec);
      void set_reaction_xs_ene_data(vector<vector<Real> > real_vec);
      void set_reaction_xs_data(vector<vector<Real> > real_vec);

      void set_production_xs_state_no_product(vector<vector<Integer> > int_vec);
      void set_production_xs_pointer(vector<vector<Integer> > int_vec);
      void set_production_xs_range_data(vector<vector<vector<Integer> > > int_vec);
      void set_production_xs_int_data(vector<vector<vector<Integer> > > int_vec);
      void set_production_xs_ene_data(vector<vector<vector<Real> > > real_vec);
      void set_production_xs_data(vector<vector<vector<Real> > > real_vec);

      //For pointer
      void set_len2(int int_val);
      void set_za(int int_val);
      void set_ntr(int int_val);
      void set_lone(int int_val);
      void set_mtr(int int_val);
      void set_lsig(int int_val);
      void set_sigd(int int_val);
      void set_end(int int_val);

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

      vector<Integer>          get_reaction_xs_reaction_type();
      vector<Integer>          get_reaction_xs_pointer();
      vector<vector<Integer> > get_reaction_xs_range_data();
      vector<vector<Integer> > get_reaction_xs_int_data();
      vector<vector<Real> >    get_reaction_xs_ene_data();
      vector<vector<Real> >    get_reaction_xs_data();

      vector<vector<Integer> >          get_production_xs_state_no_product();
      vector<vector<Integer> >          get_production_xs_pointer();
      vector<vector<vector<Integer> > > get_production_xs_range_data();
      vector<vector<vector<Integer> > > get_production_xs_int_data();
      vector<vector<vector<Real> > >    get_production_xs_ene_data();
      vector<vector<vector<Real> > >    get_production_xs_data();

      //For pointer
      int         get_len2();
      int         get_za();
      int         get_ntr();
      int         get_lone();
      int         get_mtr();
      int         get_lsig();
      int         get_sigd();
      int         get_end();
  };
}

#endif //DOSIMETRY_ACE_DATA_OBJECT_H
