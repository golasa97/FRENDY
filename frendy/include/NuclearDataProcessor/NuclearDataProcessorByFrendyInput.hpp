#ifndef NUCLEAR_DATA_PROCESSOR_BY_FRENDY_INPUT_H
#define NUCLEAR_DATA_PROCESSOR_BY_FRENDY_INPUT_H

#include "FrendyUtils/FrendyInputReader.hpp"
#include "FrendyUtils/ThermalScatterMatList.hpp"
#include "FrendyUtils/Endf6FormatCheckInputReader.hpp"
#include "ReconResonance/ResonanceXSReconstructorByFrendyInput.hpp"
#include "DopplerBroadening/DopplerCalculatorByFrendyInput.hpp"
#include "ThermalScatter/ThermalScatterCalculatorByFrendyInput.hpp"
#include "UnresoUtils/ProbabilityTableCalculatorByFrendyInput.hpp"
#include "GasProduction/GasProductionXSCalculatorByFrendyInput.hpp"
#include "ContinuousEnergyXSUtils/AceDataGenerator/AceDataGeneratorByFrendyInput.hpp"
#include "NuclearDataProcessor/NuclearDataProcessorByNjoyInput.hpp"
#include "NuclearDataProcessor/MakeInputFromFRENDYtoNJOY.hpp"
#include "NuclearDataModifier/Endf6ModifierByFrendyInput.hpp"
#include "Plotter/PlotDataByFrendyInput.hpp"
#include "MGXSUtils/MGUtils/MultiGroupDataGeneratorByFrendyInput.hpp"

namespace frendy
{
  class NuclearDataProcessorByFrendyInput
  {
    private:
      frendy::ErrorManager                    err_obj;
      frendy::TimeUtils                       time_obj;
      frendy::NuclearDataProcessorCommonUtils common_obj;
      frendy::FrendyInputReader               frendy_inp_obj;
      frendy::FrendyInputCommonUtils          frendy_inp_common_obj;

#ifdef DEBUG_MODE
  public:
#endif
      vector<frendy::NuclearDataObject> nucl_data_obj_ori, nucl_data_obj_cal;
      vector<frendy::NuclearDataObject> nucl_data_obj_tsl;

      vector<string> skip_nucl_name_tsl;

      string  input_name;
      int     calc_mode;
      Integer principal_atom_no,     atom_type_no,
              tsl_za_data_principal, tsl_za_data_non_principal;
      int     tsl_mat_data_pos;

      void modify_endf_file();
      void check_endf_file();
      void plot_file();
      void process_nucl_data_njoy();
      void process_nucl_data_frendy();
      void make_input_from_frendy_to_njoy();

      void modify_endf_file(vector<vector<string> >& input_data);
      void check_endf_file(vector<vector<string> >& input_data);
      void plot_file(vector<vector<string> >& input_data);

      void check_endf_file(frendy::Endf6FormatCheckInputReader& input_reader_obj);

      void process_nucl_data_ace_fast();
      void process_nucl_data_ace_therm();
      void process_nucl_data_ace_dosi();
      void process_nucl_data_mg_neutron();
      void process_nucl_data_mg_tsl();

      void linearize_cross_section(int i);
      void calc_gas_production_xs(int i);
      void calc_probability_table(int i);
      void calc_thermal_scatter(int i);

      void generate_ace_file(int i);
      void generate_ace_file(int i, frendy::AceDataObject& ace_obj,
                             MultiGroupDataGeneratorInputReader& inp_mg_obj);
      void generate_ace_file_common(int i, frendy::AceDataGeneratorByFrendyInput& ace_gen_obj);

      void check_tsl_data(int i);
      void check_tsl_mass_data(int i);
      void read_principal_atom_no(int i);
      void read_atom_type_no_and_tsl_za_data(int i);
      void check_thermal_scatter_inp_data(int i);
      void check_thermal_scatter_inp_data_ace_mode(int i);

      void write_pendf(int i, string pendf_name, string pendf_label, vector<string> comment_data);

    public:
      //constructor
      NuclearDataProcessorByFrendyInput(void);

      //destructor
      virtual ~NuclearDataProcessorByFrendyInput(void);

      void clear();

      void process_nucl_data(string input_file_name);
      void process_nucl_data(vector<vector<string> >& input_data);

      string get_input_name();
  };
}

#endif // NUCLEAR_DATA_PROCESSOR_BY_FRENDY_INPUT_H
