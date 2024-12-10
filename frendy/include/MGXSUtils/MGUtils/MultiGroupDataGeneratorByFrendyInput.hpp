#ifndef MULTI_GROUP_DATA_GENERATOR_BY_FRENDY_H
#define MULTI_GROUP_DATA_GENERATOR_BY_FRENDY_H

#include "ContinuousEnergyXSUtils/AceDataParser/FastAceDataParser.hpp"
#include "ContinuousEnergyXSUtils/AceDataParser/ThermalScatterAceDataParser.hpp"
#include "ContinuousEnergyXSUtils/AceDataWriter/FastAceDataWriter.hpp"
#include "ContinuousEnergyXSUtils/AceDataWriter/ThermalScatterAceDataWriter.hpp"
#include "MGXSUtils/InputUtils/MultiGroupDataGeneratorInputConverter.hpp"
#include "MGXSUtils/FMGenerator/FMGenerator.h"
#include "MGXSUtils/FMGenerator/FMDefaultInputGenerator.h"
#include "MGXSUtils/MGUtils/MGPhotonProduction.hpp"
#include "MGXSUtils/MatxsUtils/MatxsParser.hpp"
#include "MGXSUtils/MatxsUtils/MatxsWriter.hpp"
#include "EndfUtils/GendfParser/GendfParser.hpp"
#include "EndfUtils/GendfWriter/GendfWriter.hpp"

namespace frendy
{
  class MultiGroupDataGeneratorByFrendyInput
  {
    private:
      frendy::ErrorManager                          err_obj;
      frendy::StringUtils                           str_obj;
      frendy::MultiGroupDataGeneratorInputReader    f_inp_obj;
      frendy::MultiGroupDataGeneratorInputConverter conv_inp_obj;

      vector<frendy::FastAceDataObject>             ace_obj_fast;
      vector<frendy::ThermalScatterAceDataObject>   ace_obj_tsl;

      vector<frendy::NuclearDataObject>             nucl_data_obj;

      vector<frendy::MGPhotonProduction>            g_prod_obj;

#ifdef DEBUG_MODE
  public:
#endif
      Integer         tsl_mt_no;
      vector<Integer> mat_no;

      void read_ace_file();

      void write_xs_data(FMGen::FMGenerator& fm_gen);
      void write_other_data(string wk, FMGen::FMGenerator& fm_gen);

      void write_matxs(vector<string>& matxs_name, vector<vector<string> >& matxs_data_str);
      void write_gendf(vector<string>& gendf_name, vector<vector<string> >& gendf_data_str);

      void check_temp();

      void run_mg_photon_production(FMGen::FMGenerator& fm_gen);

    public:

      //constructor
      MultiGroupDataGeneratorByFrendyInput(void);

      //destructor
      virtual ~MultiGroupDataGeneratorByFrendyInput(void);

      void clear();

      void run_frendy_mg();

      void set_mat_no(vector<Integer> int_vec);
      void set_tsl_mt_no(Integer int_val);
      void set_frendy_inp_obj(frendy::MultiGroupDataGeneratorInputReader inp_obj);

      void set_ace_file_name_fast(string ace_file_name);
      void set_ace_file_name_fast(vector<string> ace_file_name);
      void set_ace_file_name_tsl(string ace_file_name_fast, string ace_file_name_tsl);
      void set_ace_file_name_tsl
             (vector<string> ace_file_name_fast, vector<string> ace_file_name_tsl);

      void set_ace_obj_fast(frendy::FastAceDataObject& ace_obj);
      void set_ace_obj_fast(vector<frendy::FastAceDataObject>& ace_obj);
      void set_ace_obj_tsl(frendy::FastAceDataObject&           ace_obj_f,
                           frendy::ThermalScatterAceDataObject& ace_obj_t);
      void set_ace_obj_tsl(vector<frendy::FastAceDataObject>&           ace_obj_f,
                           vector<frendy::ThermalScatterAceDataObject>& ace_obj_t);

      void set_nucl_data_obj(vector<frendy::NuclearDataObject> nucl_obj);
  }; 
}

#endif //MULTI_GROUP_DATA_GENERATOR_BY_FRENDY_H
