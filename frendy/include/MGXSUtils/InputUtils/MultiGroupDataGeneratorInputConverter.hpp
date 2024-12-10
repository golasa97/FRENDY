#ifndef MULTI_GROUP_DATA_GENERATOR_INPUT_CONVERTER_H
#define MULTI_GROUP_DATA_GENERATOR_INPUT_CONVERTER_H

#include <map>
#include "CommonUtils/VectorClearer.hpp"
#include "FrendyUtils/MultiGroupDataGeneratorInputReader.hpp"
#include "ContinuousEnergyXSUtils/OtherUtils/AceFileReader.hpp"
#include "ContinuousEnergyXSUtils/AceDataObject/ThermalScatterAceDataObject.hpp"
#include "ContinuousEnergyXSUtils/AceDataObject/FastAceDataObject.hpp"
#include "NjoyUtils/GrouprInputReader.hpp"
#include "NjoyUtils/MatxsrInputReader.hpp"
#include "NuclearDataUtils/NuclearDataObject.hpp"
#include "NjoyUtils/GroupStructureGamma.hpp"
#include "NjoyUtils/GroupStructureNeutron.hpp"
#include "NjoyUtils//MultiGroupWeightFunction.hpp"
#include "MGXSUtils/MatxsUtils/MatxsObject.hpp"

namespace frendy
{
  class NuclearDataInfoNjoyMG
  {
    private:
#ifdef DEBUG_MODE
  public:
#endif
      frendy::NuclearDataObject nucl_data_obj;

    public:

      //constructor
      NuclearDataInfoNjoyMG(void);

      //destructor
      virtual ~NuclearDataInfoNjoyMG(void);

      void clear();

      void set_nucl_data_obj(frendy::NuclearDataObject& nucl_obj);

      string get_tsl_data_type(int tsl_flg);

      Integer get_mat_no();

      Real get_el();
      Real get_eh();
      Real get_temp();

      vector<Real> get_sigma_zero_data();

      Real    get_thermal_cutoff();
      Integer get_thermal_xs_treatment();
  };

  class MultiGroupDataGeneratorInputConverter
  {
    private:
      frendy::ErrorManager                        err_obj;
      frendy::VectorClearer                       clr_obj;
      frendy::FrendyInputCommonUtils              frendy_utils;

      frendy::MultiGroupDataGeneratorInputReader  f_inp_obj;
      frendy::NuclearDataInfoNjoyMG               n_inp_obj;
      frendy::GrouprInputReader                   groupr_obj;
      frendy::MatxsrInputReader                   matxsr_obj;

      static const int frendy_mode = 1;
      static const int njoy_mode   = 2;

      static const int njoy16_mode = 1;
      static const int njoy99_mode = 2;
      static const int full_mode   = 3;


#ifdef DEBUG_MODE
  public:
#endif
      int output_mode;

      int set_data_flg;
      int set_data_mode;

      int pos_i, pos_j;

      //For input data of NJOY
      int tsl_data_flg;
      frendy::FastAceDataObject           ace_data_obj_fast;
      frendy::ThermalScatterAceDataObject ace_data_obj_tsl;

      //For input data of FRENDY/MG
      vector<string>          input_data_key;
      vector<vector<string> > input_data;

      //For ultra_fine_group
      vector<Real>    ultra_fine_group_ene;
      vector<Integer> ultra_fine_group_div_no;
      vector<string>  ultra_fine_group_opt;

      //For mult_group
      vector<Real>    multi_group, multi_group_gam;
      vector<string>  multi_group_auto;

      //For default_spectrum
      string          default_spectrum_mode;
      Real            default_spectrum_eh,       default_spectrum_el,
                      default_spectrum_temp_fis, default_spectrum_temp_maxwell,
                      default_spectrum_el_fis,   default_spectrum_eh_maxwell;
      vector<Real>    default_spectrum_ene,      default_spectrum_weight;

      //For material
      vector<string>  material_id, material_id_set;
      vector<Real>    material_number_density;
      vector<string>  material_sab_id,  material_sab_id_set, material_sab_type;

      //For ace_file
      vector<string>  ace_file, ace_file_fast, ace_file_tsl;

      //For thermal_cutoff
      Real            thermal_cutoff_ene_in, thermal_cutoff_ene_out;

      //For calc_cond
      vector<string>  calc_cond_opt;
      vector<Real>    calc_cond_atomic_weight, calc_cond_el, calc_cond_eh;
      string          calc_cond_sab_opt; //NoThermalXS

      //For bg_xs_set
      vector<Real>    bg_xs_set;
      string          bg_xs_auto;

      //For potential_xs
      vector<Real>    potential_xs;

      //For max_pl
      Integer         max_pl;

      //For reso_upscat
      Integer         reso_up_scat_mode;
      vector<string>  reso_up_scat_0k_data;

      //For edit_xs
      vector<string>           edit_xs_opt;
      vector<vector<Integer> > edit_xs_mt;

      void check_input_data();


      //Convert input file FRENDY or NJOY to that of FRENDY/MG
      void convert_input_data();
      void convert_input_data_frendy();
      void convert_input_data_njoy();

      //Convert input paramters to vector<string> input_data
      void make_input_data_list();

    public:

      //constructor
      MultiGroupDataGeneratorInputConverter(void);

      //destructor
      virtual ~MultiGroupDataGeneratorInputConverter(void);

      void clear();

      vector<string> get_id_list(vector<string> ace_name_list);
      string         get_id(string ace_name);

      //*** Setter ***//
      void set_input_obj_frendy(frendy::MultiGroupDataGeneratorInputReader inp_obj);
      void set_input_obj_njoy(int i, int j,
                              frendy::NuclearDataInfoNjoyMG& nucl_data_info_obj,
                              frendy::GrouprInputReader      inp_obj_groupr,
                              frendy::MatxsrInputReader      inp_obj_matxsr,
                              int tsl_flg,
                              frendy::FastAceDataObject&           ace_obj_fast,
                              frendy::ThermalScatterAceDataObject& ace_obj_tsl);

      void set_material_id(vector<string> str_vec);
      void set_material_sab_id(vector<string> str_vec);

      //*** Getter ***//
      //For ultra_fine_group
      vector<Real>    get_ultra_fine_group_ene();
      vector<Integer> get_ultra_fine_group_div_no();
      vector<string>  get_ultra_fine_group_opt();

      //For mult_group
      vector<Real>    get_multi_group();
      vector<Real>    get_multi_group_gam();

      //For default_spectrum
      string          get_default_spectrum_mode();
      Real            get_default_spectrum_eh();
      Real            get_default_spectrum_el();
      Real            get_default_spectrum_temp_fis();
      Real            get_default_spectrum_temp_maxwell();
      Real            get_default_spectrum_el_fis();
      Real            get_default_spectrum_eh_maxwell();
      vector<Real>    get_default_spectrum_ene();
      vector<Real>    get_default_spectrum_weight();

      //For material
      vector<string>  get_material_id();
      vector<Real>    get_material_number_density();
      vector<string>  get_material_sab_id();
      vector<string>  get_material_sab_type();

      //For ace_file
      vector<string>  get_ace_file();
      vector<string>  get_ace_file_fast();
      vector<string>  get_ace_file_tsl();

      //For thermal_cutoff
      Real            get_thermal_cutoff_ene_in();
      Real            get_thermal_cutoff_ene_out();

      //For calc_cond
      vector<string>  get_calc_cond_opt();
      vector<Real>    get_calc_cond_atomic_weight();
      vector<Real>    get_calc_cond_el();
      vector<Real>    get_calc_cond_eh();
      string          get_calc_cond_sab_opt();

      //For bg_xs_set
      vector<Real>    get_bg_xs_set();

      //For max_pl
      Integer         get_max_pl();

      //For reso_upscat
      Integer         get_reso_up_scat_mode();
      vector<string>  get_reso_up_scat_0k_data();

      //For edit_xs
      vector<string>           get_edit_xs_opt();
      vector<vector<Integer> > get_edit_xs_mt();

      //For input data of FRENDY/MG
      vector<string>          get_input_data_key();
      vector<vector<string> > get_input_data();
      map<string, vector<string> > get_input_data_map();

      void output_input_data();
  }; 
}

#endif //MULTI_GROUP_DATA_GENERATOR_INPUT_CONVERTER_H
