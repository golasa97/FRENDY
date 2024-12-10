#ifndef DOSIMETRY_ACE_DATA_GENERATOR_H
#define DOSIMETRY_ACE_DATA_GENERATOR_H

#include "NuclearDataUtils/NuclearDataObject.hpp"
#include "NuclearDataUtils/OtherUtils/CrossSectionCalculator.hpp"
#include "CommonUtils/TabInterpolator.hpp"
#include "CommonUtils/TabAdjuster.hpp"
#include "CommonUtils/VectorClearer.hpp"
#include "CommonUtils/TimeUtils.hpp"
#include "CommonUtils/VectorSizeChecker.hpp"
#include "ContinuousEnergyXSUtils/AceDataObject/DosimetryAceDataObject.hpp"

namespace frendy
{
  class DosimetryAceDataGenerator
  {
    private:
      frendy::ErrorManager           err_obj;
      frendy::VectorClearer          clr_obj;
      frendy::TabInterpolator        ti_obj;
      frendy::TabAdjuster            ta_obj;
      frendy::CrossSectionCalculator xs_calc_obj;
      frendy::TimeUtils              time_obj;

      static const int max_zi_awr_pair_no = 16;

#ifdef DEBUG_MODE
  public:
#endif
      Integer gen_dosimetry_data_flg, nucl_data_set_flg, mat_set_flg, temp_set_flg;

      frendy::NuclearDataObject  nucl_data_obj;

      vector<string> title_data;

      Real aw0, tz;

      vector<Integer> reaction_type_list;
      vector<frendy::CrossSectionDataContainer>       xs_data_obj;
      vector<frendy::RadioactiveProductDataContainer> radio_product_data_obj;

      string          discriptive_data;
      Integer         mat;
      Real            temp;
      vector<Integer> zi_vec;
      vector<Real>    awr_vec;

      Real    suffix_za_id;
      Integer mcnpx_mode_flg;

      vector<Integer>          reaction_xs_reaction_type, reaction_xs_pointer;
      vector<vector<Integer> > reaction_xs_range_data, reaction_xs_int_data;
      vector<vector<Real> >    reaction_xs_ene_data,   reaction_xs_data;

      vector<vector<Integer> >          production_xs_state_no_product, production_xs_pointer;
      vector<vector<vector<Integer> > > production_xs_range_data, production_xs_int_data;
      vector<vector<vector<Real> > >    production_xs_ene_data,   production_xs_data;

      void check_xs_data_obj();

      void modify_radio_product_data_obj();
      void calc_radio_product_xs_by_multiplicity();
      void calc_radio_xs(int i);
      void devide_radio_product_xs_by_product_nucleus();
      int  check_product_nucleus(vector<Integer> mat_data_product_list);
      void devide_radio_product_xs(int i);

      void generate_ace_data_xs();

      void modify_calc_data();

      void calc_ace_header_file_data();

      //For pointer data
      int len2, za, ntr, lone, mtr, lsig, sigd, end;

      void output_ace_data();
      void output_ace_data_title();
      void output_ace_data_reaction_xs();
      void output_ace_data_production_xs();


      void copy_dosimetry_ace_data(frendy::DosimetryAceDataObject& ace_data_obj);

      void clear_calc_data();
      void clear_ace_data();
      void clear_ace_pointer_data();
      void check_set_data();

    public:
      //constructor
      DosimetryAceDataGenerator(void);

      //destructor
      virtual ~DosimetryAceDataGenerator(void);

      void clear();

      void generate_ace_data();

      //Setter
      void set_nucl_data_obj(frendy::NuclearDataObject& data_obj);
      void set_mat(Integer int_val);
      void set_temp(Real real_val);
      void set_suffix_za_id(Real real_val);
      void set_zi_awr_pair(vector<Integer> int_vec_zi, vector<Real> real_vec_awr);
      void set_discriptive_data(string str_data);
      void set_mcnpx_mode_flg(Integer int_val);

      //Getter
      frendy::DosimetryAceDataObject get_ace_data_obj();

      frendy::NuclearDataObject      get_nucl_data_obj();
      Integer                        get_mat();
      Real                           get_temp();
      Real                           get_suffix_za_id();
      vector<Integer>                get_zi_vec();
      vector<Real>                   get_awr_vec();
      string                         get_discriptive_data();

      Integer                        get_mcnpx_mode_flg();
  };
}

#endif //DOSIMETRY_ACE_DATA_GENERATOR_H
