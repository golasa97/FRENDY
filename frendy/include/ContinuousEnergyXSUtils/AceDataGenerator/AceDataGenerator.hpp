#ifndef ACE_DATA_GENERATOR_H
#define ACE_DATA_GENERATOR_H

#include "EndfUtils/Endf6Parser/Endf6Parser.hpp"
#include "EndfUtils/Endf6Converter/Endf6Converter.hpp"
#include "ContinuousEnergyXSUtils/AceDataObject/AceDataObject.hpp"
#include "ContinuousEnergyXSUtils/AceDataWriter/FastAceDataWriter.hpp"
#include "ContinuousEnergyXSUtils/AceDataWriter/ThermalScatterAceDataWriter.hpp"
#include "ContinuousEnergyXSUtils/AceDataWriter/DosimetryAceDataWriter.hpp"
#include "ContinuousEnergyXSUtils/AceDataGenerator/FastAceDataGenerator.hpp"
#include "ContinuousEnergyXSUtils/AceDataGenerator/ThermalScatterAceDataGenerator.hpp"
#include "ContinuousEnergyXSUtils/AceDataGenerator/DosimetryAceDataGenerator.hpp"

namespace frendy
{
  class AceDataGenerator
  {
    private:
      frendy::ErrorManager                   err_obj;
      frendy::FastAceDataGenerator           fast_ace_obj;
      frendy::ThermalScatterAceDataGenerator thermal_scat_ace_obj;
      frendy::DosimetryAceDataGenerator      dosimetry_ace_obj;

#ifdef DEBUG_MODE
  public:
#endif
      frendy::AceDataObject ace_data_obj;

      Integer generate_ace_data_flg;
      Integer nucl_data_set_flg;

      frendy::NuclearDataObject nucl_data_obj;
      string                    nucl_data_name;

      //For input data (Common)
      string          ace_file_name, mcnp_dir, discriptive_data;
      Integer         opt_run, mcnpx_mode_flg, opt_print, opt_out_type, mat;
      Real            temp, suffix_za_id;
      vector<Integer> zi_vec;
      vector<Real>    awr_vec;

      //For input data (Fast)
      Integer         new_cummulative_angle_distr_flg, detailed_photon_flg;
      vector<Real>    thinning_ene;

      //For input data (Thermal scattering)
      string          thermal_za_id_name;
      Integer         mt_inelastic, bin_no, mt_elastic, elastic_flg, atom_no_th, opt_weight;
      Real            ene_max_th;
      vector<Integer> mod_za;

      int generate_mode_flg, write_ace_flg;

      void output_set_data_information_common();
      void output_set_data_information_fast();
      void output_set_data_information_thermal();
      void output_set_data_information_dosimetry();

      void generate_ace_data_fast();
      void generate_ace_data_thermal();
      void generate_ace_data_dosimetry();

    public:
      //constructor
      AceDataGenerator(void);

      //destructor
      virtual ~AceDataGenerator(void);

      static const int generate_default_mode = 0;
      static const int generate_njoy_mode    = 1;

      static const int write_ace             = 0;
      static const int skip_write_ace        = 1;

      static const int fast_mode      = 1;
      static const int thermal_mode   = 2;
      static const int dosimetry_mode = 3;

      void clear();

      void generate_ace_data();

      //Setter
      void set_nucl_data_name(string str_data);
      void set_nucl_data_obj(frendy::NuclearDataObject& data_obj);

      //For input data (Common)
      void set_ace_file_name(string str_data);
      void set_mcnp_dir(string str_data);
      void set_discriptive_data(string str_data);
      void set_opt_run(Integer int_data);
      void set_mcnpx_mode_flg(Integer int_data);
      void set_opt_print(Integer int_data);
      void set_opt_out_type(Integer int_data);
      void set_mat(Integer int_data);
      void set_temp(Real real_data);
      void set_suffix_za_id(Real real_data);
      void set_zi_vec(vector<Integer> int_vec);
      void set_awr_vec(vector<Real> real_vec);

      //For input data (Fast)
      void set_new_cummulative_angle_distr_flg(Integer int_data);
      void set_detailed_photon_flg(Integer int_data);
      void set_thinning_ene(vector<Real> real_vec);

      //For input data (Thermal scattering)
      void set_thermal_za_id_name(string str_data);
      void set_mt_inelastic(Integer int_data);
      void set_bin_no(Integer int_data);
      void set_mt_elastic(Integer int_data);
      void set_elastic_flg(Integer int_data);
      void set_atom_no_th(Integer int_data);
      void set_opt_weight(Integer int_data);
      void set_ene_max_th(Real real_data);
      void set_mod_za(vector<Integer> int_vec);

      void set_generate_mode_flg(int int_val);
      void set_write_ace_flg(int int_val);

      //Getter
      frendy::AceDataObject     get_ace_data_obj();

      string                    get_nucl_data_name();
      frendy::NuclearDataObject get_nucl_data_obj();

      //For input data (Common)
      string          get_ace_file_name();
      string          get_mcnp_dir();
      string          get_discriptive_data();
      Integer         get_opt_run();
      Integer         get_mcnpx_mode_flg();
      Integer         get_opt_print();
      Integer         get_opt_out_type();
      Integer         get_mat();
      Real            get_temp();
      Real            get_suffix_za_id();
      vector<Integer> get_zi_vec();
      vector<Real>    get_awr_vec();

      //For input data (Fast)
      Integer         get_new_cummulative_angle_distr_flg();
      Integer         get_detailed_photon_flg();
      vector<Real>    get_thinning_ene();

      //For input data (Thermal scattering)
      string          get_thermal_za_id_name();
      Integer         get_mt_inelastic();
      Integer         get_bin_no();
      Integer         get_mt_elastic();
      Integer         get_elastic_flg();
      Integer         get_atom_no_th();
      Integer         get_opt_weight();
      Real            get_ene_max_th();
      vector<Integer> get_mod_za();

      int             get_generate_mode_flg();
      int             get_write_ace_flg();
  };
}

#endif //ACE_DATA_GENERATOR_H
