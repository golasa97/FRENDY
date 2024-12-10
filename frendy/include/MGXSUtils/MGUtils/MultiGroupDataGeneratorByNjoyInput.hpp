#ifndef MULTI_GROUP_DATA_GENERATOR_BY_NJOY_INPUT_H
#define MULTI_GROUP_DATA_GENERATOR_BY_NJOY_INPUT_H

#include "CommonUtils/TimeUtils.hpp"
#include "NuclearDataUtils/OtherUtils/Endf6FileStore.hpp"
#include "ThermalScatter/IncoherentInelasticScatterCalculator.hpp"
#include "ContinuousEnergyXSUtils/AceDataGenerator/AceDataGenerator.hpp"
#include "ContinuousEnergyXSUtils/AceDataParser/FastAceDataParser.hpp"
#include "ContinuousEnergyXSUtils/AceDataParser/ThermalScatterAceDataParser.hpp"
#include "ContinuousEnergyXSUtils/AceDataParser/DosimetryAceDataParser.hpp"
#include "MGXSUtils/InputUtils/MultiGroupDataGeneratorInputConverter.hpp"
#include "MGXSUtils/FMGenerator/FMGenerator.h"
#include "MGXSUtils/FMGenerator/FMDefaultInputGenerator.h"
#include "MGXSUtils/MGUtils/MGPhotonProduction.hpp"
#include "MGXSUtils/MatxsUtils/MatxsParser.hpp"
#include "MGXSUtils/MatxsUtils/MatxsWriter.hpp"
#include "MGXSUtils/MatxsUtils/MatxsMerger.hpp"
#include "EndfUtils/GendfParser/GendfParser.hpp"
#include "EndfUtils/GendfWriter/GendfWriter.hpp"
#include "NuclearDataModifier/GendfModifier.hpp"

namespace frendy
{
  class MultiGroupDataGeneratorByNjoyInput
  {
    private:
      frendy::ErrorManager            err_obj;
      frendy::VectorClearer           clr_obj;
      frendy::StringUtils             str_obj;
      frendy::TimeUtils               time_obj;
      frendy::FrendyInputCommonUtils  f_inp_common_obj;

      static const Real               suffix_za_id_def; //=   0.0;

#ifdef DEBUG_MODE
  public:
#endif
      frendy::MultiGroupDataGeneratorInputConverter  conv_inp_obj;

      frendy::NuclearDataInfoNjoyMG       nucl_data_info_obj;
      frendy::NuclearDataObject           nucl_data_obj, nucl_data_obj_tsl;
      frendy::FastAceDataObject           ace_data_obj_fast;
      frendy::ThermalScatterAceDataObject ace_data_obj_tsl;

      frendy::MGPhotonProduction          g_prod_obj;

      frendy::GrouprInputReader           read_groupr_obj;
      vector<frendy::MatxsrInputReader>   read_matxsr_obj;

      int calc_flg, tsl_data_flg;
      vector<int>   tsl_mt_no, tsl_ref_frame_flg;

      string      input_file_name_njoy;
      int         start_line_no;
      vector<int> matxsr_line_no;

      GendfParser     gendf_obj;
      MatxsCommonData matxs_obj;
      vector<string>  matxs_obj_name_list;

      //For time measurement
      Real time_total;

      //For dosimetry
      frendy::DosimetryAceDataObject ace_data_obj_dosi;
      int dosi_data_flg;
      vector<Integer>                mf_dosi, mt_dosi;
      vector<vector<vector<Real> > > dosi_xs;
 
      string                endf_name, pendf_name, gendf_name_out;
      vector<string>        title_vec;
      vector<Integer>       mat_vec;
      vector<vector<Real> > temp_vec, sigz_vec;

      void set_input_data();
      void set_nucl_data_obj(Integer mat_no, Real temp);

      Integer  check_tsl_data(frendy::NuclearDataObject& pendf_obj);

      void read_ace_file(int i, int j);
      void ace_file_generation(int i, int j);
      void set_thermal_data(int i, int j, frendy::AceDataGenerator& ace_gen_obj);

      void mg_file_generation(int i, int j);
      void set_mg_input(int i, int j, FMGen::FMGenerator& fm_gen);
      void set_ace_file_data(int i, int j, FMGen::FMGenerator& fm_gen);
      void output_mg_file_data(int i, int j, FMGen::FMGenerator& fm_gen);

      void run_mg_photon_production(FMGen::FMGenerator& fm_gen);
      void run_mg_dosimetry_production(int i, int j, FMGen::FMGenerator& fm_gen);
      void get_dosi_xs_data(int mf, int mt, vector<Real>& dosi_ene_vec, vector<Real>& dosi_xs_vec);

      void output_gendf_file_dosi(ofstream& fout_gendf, int i, int j);
      void output_gendf_file(ofstream& fout_gendf, int i, int j);
      void write_gendf_file(ofstream& fout_gendf, int i, int j);
      void output_matxs_file(int mg_file_no);
      void output_matxs_file_merge();

      void check_mf_mt_list(vector<Integer> mf_list, vector<Integer> mt_list,
                            frendy::GendfParser& gendf_data);
      void modify_gendf(vector<Integer> mf_list, vector<Integer> mt_list,
                        frendy::GendfParser& gendf_data);
      vector<Integer> get_output_mt_list(Integer mf_no,
                                         vector<Integer>& mf_list, vector<Integer>& mt_list);
      vector<Integer> get_remove_mt_list(vector<Integer> gendf_mt_list,
                                         vector<Integer> output_mt_list);

    public:

      //constructor
      MultiGroupDataGeneratorByNjoyInput(void);

      //destructor
      virtual ~MultiGroupDataGeneratorByNjoyInput(void);

      void clear();

      void generate_mg_data();
      void output_input_file_name();

      void run_frendy_mg();

      void set_njoy_input_file_name(string str_data, int line_no,
                                    vector<int> matxsr_line_no_vec);
  }; 
}

#endif //MULTI_GROUP_DATA_GENERATOR_BY_NJOY_INPUT_H
