#ifndef THERMAL_SCATTER_ACE_DATA_GENERATOR_H
#define THERMAL_SCATTER_ACE_DATA_GENERATOR_H

#include "NuclearDataUtils/NuclearDataObject.hpp"
#include "CommonUtils/TabInterpolator.hpp"
#include "CommonUtils/VectorClearer.hpp"
#include "CommonUtils/TimeUtils.hpp"
#include "CommonUtils/VectorSizeChecker.hpp"
#include "ContinuousEnergyXSUtils/AceDataObject/ThermalScatterAceDataObject.hpp"

namespace frendy
{
  class ThermalScatterAceDataGenerator
  {
    private:
      frendy::ErrorManager      err_obj;
      frendy::VectorClearer     clr_obj;
      frendy::TabInterpolator   ti_obj;
      frendy::TimeUtils         time_obj;
      frendy::VectorSizeChecker vec_size_check_obj;

      static const int max_zi_awr_pair_no = 16;
      static const int mod_za_no          =  3;

      static const Real8 min_second_ene_dif_abs;

      Real8 third;

#ifdef DEBUG_MODE
  public:
#endif
      Integer gen_th_scat_data_flg, nucl_data_set_flg, mat_set_flg, temp_set_flg;

      frendy::NuclearDataObject                nucl_data_obj;
      frendy::CrossSectionDataContainer        xs_data_inelastic,         xs_data_elastic;
      frendy::ProductDistributionDataContainer prod_distr_data_inelastic, prod_distr_data_elastic;

      vector<string> title_data;

      Real aw0, tz;

      //For elastic
      vector<Real>          coh_elastic_ene_data,   coh_elastic_e_xs_data,
                            incoh_elastic_ene_data, incoh_elastic_xs_data;
      vector<vector<Real> > incoh_elastic_scat_angle;

      //For inelastic
      vector<Real>                   inelastic_ene_data, inelastic_xs_data;
      vector<vector<Real> >          inelastic_second_ene_cal, inelastic_scat_xs_int_cal,
                                     inelastic_weight;
      vector<vector<vector<Real> > > inelastic_scat_xs_weight;

      Integer         mat;
      Real            temp;

      int             bin_no_int;
      Integer         mt_inelastic, bin_no, mt_elastic, elastic_flg, atom_no_th, opt_weight;
      Real            suffix_za_id, ene_max_th;
      vector<Integer> zi_vec, mod_za;
      vector<Real>    awr_vec;

      //For output
      Integer mcnpx_mode_flg;
      string  discriptive_data, thermal_za_id_name;

      void generate_coherent_elastic_scatter_data();
      void generate_incoherent_elastic_scatter_data();
      void remove_unnecessary_energy_grid_incoherent_elastic_data(vector<int>& pos_vec);

      void generate_inelastic_scatter_data();
      vector<Real8> set_weight();
      void calc_second_energy_data( int i,  vector<Real8>& weight_vec,
                                     vector<Real>& second_ene, vector<Real>& scat_xs_integrate,
                                     vector<vector<Real> >& scat_xs_weight );
      void output_error_calc_second_energy_data( int i, int j, int j_max,
                                                 Real8 second_ene_cal, Real8 second_ene_pre,
                                                 Real8 second_ene_cur, int pos );
      void remove_unnecessary_energy_grid_inelastic_data(vector<int>& pos_vec);

      void modify_calc_data();

      void output_inelastic_ene_out_grid();
      void comp_scat_xs_tot();
      void modify_scat_xs(Integer atom_no_mod);

      void calc_ace_header_file_data();

      //For pointer data
      int         len2, idpni, nil, nieb, idpnc, ncl, ifeng, itie, itix, itxe, itce, itcx, itca,
                  nie,  nee;

      void output_ace_data();
      void output_ace_data_title();
      void output_ace_data_inelastic();
      void output_ace_data_coherent_elastic();
      void output_ace_data_incoherent_elastic();


      void copy_thermal_scat_ace_data(frendy::ThermalScatterAceDataObject& ace_data_obj);

      void clear_calc_data();
      void clear_ace_data();
      void clear_ace_pointer_data();
      void check_set_data();

    public:
      //constructor
      ThermalScatterAceDataGenerator(void);

      //destructor
      virtual ~ThermalScatterAceDataGenerator(void);

      void clear();

      void generate_ace_data();

      //Setter
      void set_nucl_data_obj(frendy::NuclearDataObject& data_obj);
      void set_mat(Integer int_val);
      void set_temp(Real real_val);

      void set_mt_inelastic(Integer int_val);
      void set_bin_no(Integer int_val);
      void set_mt_elastic(Integer int_val);
      void set_elastic_flg(Integer int_val);
      void set_atom_no_th(Integer int_val);
      void set_opt_weight(Integer int_val);
      void set_suffix_za_id(Real real_val);
      void set_ene_max_th(Real real_val);
      void set_zi_awr_pair(vector<Integer> int_vec_zi, vector<Real> real_vec_awr);
      void set_mod_za(vector<Integer> int_vec);

      void set_mcnpx_mode_flg(Integer int_val);
      void set_discriptive_data(string str_data);
      void set_thermal_za_id_name(string str_data);

      //Getter
      frendy::ThermalScatterAceDataObject get_ace_data_obj();

      frendy::NuclearDataObject           get_nucl_data_obj();
      Integer                             get_mat();
      Real                                get_temp();

      Integer                             get_mt_inelastic();
      Integer                             get_bin_no();
      Integer                             get_mt_elastic();
      Integer                             get_elastic_flg();
      Integer                             get_atom_no_th();
      Integer                             get_opt_weight();
      Real                                get_suffix_za_id();
      Real                                get_ene_max_th();
      vector<Integer>                     get_zi_vec();
      vector<Real>                        get_awr_vec();
      vector<Integer>                     get_mod_za();

      Integer                             get_mcnpx_mode_flg();
      string                              get_discriptive_data();
      string                              get_thermal_za_id_name();
  };
}

#endif //THERMAL_SCATTER_ACE_DATA_GENERATOR_H
