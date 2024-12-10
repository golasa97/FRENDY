#ifndef FRENDY_INPUT_READER_H
#define FRENDY_INPUT_READER_H

#include "CommonUtils/FileCommentRemover.hpp"
#include "NjoyUtils/NjoyInputReader.hpp"
#include "FrendyUtils/ReconResonanceInputReader.hpp"
#include "FrendyUtils/DopplerBroadeningInputReader.hpp"
#include "FrendyUtils/GasProductionInputReader.hpp"
#include "FrendyUtils/ProbTableInputReader.hpp"
#include "FrendyUtils/ThermalScatterInputReader.hpp"
#include "FrendyUtils/AceDataGeneratorInputReader.hpp"
#include "FrendyUtils/MultiGroupDataGeneratorInputReader.hpp"
#include "FrendyUtils/MakeNJOYInputReader.hpp"

namespace frendy
{
  class FrendyInputReader
  {
    private:
      frendy::ErrorManager    err_obj;
      frendy::VectorClearer   clr_obj;
      frendy::NjoyInputReader njoy_reader_obj;

#ifdef DEBUG_MODE
  public:
#endif
      frendy::FrendyInputCommonUtils             inp_common_obj;
      frendy::ReconResonanceInputReader          inp_recon_obj;
      frendy::DopplerBroadeningInputReader       inp_dop_obj;
      frendy::GasProductionInputReader           inp_gas_xs_obj;
      frendy::ProbTableInputReader               inp_prob_table_obj;
      frendy::ThermalScatterInputReader          inp_thermal_scatter_obj;
      frendy::AceDataGeneratorInputReader        inp_ace_obj;
      frendy::MultiGroupDataGeneratorInputReader inp_mg_obj;

      frendy::MakeNJOYInputReader                inp_make_njoy_obj;

      vector<string> func_name_list, func_name_list_make_inp;
      vector<int>    func_name_mode, func_name_mode_make_inp;
      vector<int>    inp_check_recon, inp_check_dop, inp_check_gas, inp_check_prob_table,
                     inp_check_therm, inp_check_ace, inp_check_mg,  inp_check_make_njoy;

      int            calc_mode,  read_flg;
      string         input_name;
      vector<string>  nucl_file_name;

      void read_common_input(vector<vector<string> >& input_data);

      void read_input_for_ace_mode(vector<vector<string> >& input_data);
      void check_input_data_number(vector<vector<string> >& input_data);
      void read_input_for_mg_mode(vector<vector<string> >& input_data);

      void check_not_used_input_data(vector<vector<string> >& input_data);
      void set_err_com_for_input_data_check
             (int i, vector<vector<string> >& input_vec, vector<string>& err_com);
      void set_inp_check_data(int i_max, vector<int>& inp_check_data);

      void set_common_data();

    public:

      //constructor
      FrendyInputReader(void);

      //destructor
      virtual ~FrendyInputReader(void);

      void clear();

      int  check_file_format(string file_name);
      int  check_input_case(string input_case);

      void read_input_file();
      void read_input_data(vector<vector<string> >& input_data);

      void set_input_file_name(string input);

      void set_inp_recon_obj(frendy::ReconResonanceInputReader inp_obj);
      void set_inp_dop_obj(frendy::DopplerBroadeningInputReader inp_obj);
      void set_inp_gas_xs_obj(frendy::GasProductionInputReader inp_obj);
      void set_inp_prob_table_obj(frendy::ProbTableInputReader inp_obj);
      void set_inp_thermal_scatter_obj(frendy::ThermalScatterInputReader inp_obj);
      void set_inp_ace_obj(frendy::AceDataGeneratorInputReader inp_obj);
      void set_inp_mg_obj(frendy::MultiGroupDataGeneratorInputReader inp_obj);
      void set_inp_make_njoy_obj(frendy::MakeNJOYInputReader inp_obj);

      string get_input_file_name();
      int    get_calc_mode();

      vector<string> get_func_name_list();
      vector<int>    get_func_name_mode();
      vector<string> get_func_name_list_make_inp();
      vector<int>    get_func_name_mode_make_inp();

      frendy::ReconResonanceInputReader          get_inp_recon_obj();
      frendy::DopplerBroadeningInputReader       get_inp_dop_obj();
      frendy::GasProductionInputReader           get_inp_gas_xs_obj();
      frendy::ProbTableInputReader               get_inp_prob_table_obj();
      frendy::ThermalScatterInputReader          get_inp_thermal_scatter_obj();
      frendy::AceDataGeneratorInputReader        get_inp_ace_obj();
      frendy::MultiGroupDataGeneratorInputReader get_inp_mg_obj();
      frendy::MakeNJOYInputReader                get_inp_make_njoy_obj();

      vector<string> get_nucl_file_name();
  }; 
}

#endif //FRENDY_INPUT_READER_H
