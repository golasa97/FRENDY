#ifndef PROBABILITY_TABLE_CALCULATOR_BY_NJOY_INPUT_H
#define PROBABILITY_TABLE_CALCULATOR_BY_NJOY_INPUT_H

#include "CommonUtils/TimeUtils.hpp"
#include "EndfUtils/OtherUtils/EndfTapeDivider.hpp"
#include "EndfUtils/Endf6Writer/Endf6Writer.hpp"
#include "NjoyUtils/PurrInputReader.hpp"
#include "NjoyUtils/UnresrInputReader.hpp"
#include "NuclearDataUtils/OtherUtils/Endf6FileStore.hpp"
#include "NuclearDataUtils/OtherUtils/ProbDataConverter.hpp"
#include "UnresoUtils/ProbabilityTableCalculator.hpp"

namespace frendy
{
  class ProbabilityTableCalculatorByNjoyInput
  {
    private:
      frendy::ErrorManager      err_obj;
      frendy::VectorClearer     clr_obj;
      frendy::TimeUtils         time_obj;
      frendy::Endf6FileStore    store_obj;
      frendy::ProbDataConverter conv_obj;
 
      frendy::ProbabilityTableCalculator prob_obj;

      string   output_result_name;
      ofstream fout_result;

#ifdef DEBUG_MODE
  public:
#endif
      int calc_flg;
      int read_inp_mode;

      frendy::NuclearDataObject nucl_data_obj;

      string        input_file_name_njoy;
      int           start_line_no;

      string        endf_name, pendf_name_old, pendf_name_new, label_data;
      int           temp_no_int;
      Integer       mat_no, ladder_no, bin_no, opt_print, ene_grid_no,
                    random_seed, sample_no;
      string        p_tab_file_name;
      vector<Real8> temp, sig_zero;

      //For time measurement
      vector<Real> time_each_ene;
      Real         time_total;

      void set_input_data();
      void set_input_data_purr();
      void set_input_data_unresr();
      void check_pendf_data();

      void set_nucl_data_obj();
      void set_prob_obj();

      vector<frendy::NuclearDataObject> get_nucl_data_with_unreso_prob_data();

      void output_input_file_name();
      void output_prob_table_data();

      //For debug
      Integer                         set_xs_tot_table_data_flg;
      vector<Real8>                   xs_tot_table_ene;
      vector<vector<vector<Real8> > > xs_tot_table_all;
      vector<vector<vector<Real8> > > read_xs_tot_table(string& file_name);

    public:
      //constructor
      ProbabilityTableCalculatorByNjoyInput(void);

      //destructor
      virtual ~ProbabilityTableCalculatorByNjoyInput(void);

      static const int purr_mode   = 0;
      static const int unresr_mode = 1;

      void clear();

      void calc_probability_table();

      void write_pendf_file();

      void set_unreso_xs_and_prob_data_obj(int temp_no, frendy::NuclearDataObject&       nucl_data,
                                                        frendy::ProbabilityDataContainer prob_data_obj);

      //Setter
      void set_read_inp_mode(int inp_mode);
      void set_njoy_input_file_name(string str_data);
      void set_njoy_input_file_name(string str_data, int line_no);

      void set_xs_tot_table_data_from_output(string& file_name); //for debug
      void set_xs_tot_table_data(vector<vector<vector<Real8> > >& real_vec); //for debug
      void set_xs_tot_table_data(vector<vector<vector<Real8> > >& real_vec_xs,
                                 vector<Real8>&                   real_vec_ene); //for debug

      //Getter
      int get_read_inp_mode();

      //Probability table is only contain in ProbabilityDataContainer class.
      frendy::NuclearDataObject         get_nucl_data_obj();

      //Probability table is contain in ProbabilityDataContainer and
      //UnresolvedProbabilityDataContainer classes
      vector<frendy::NuclearDataObject> get_nucl_data_obj_each_temp();

      string                    get_njoy_input_file_name();
      string                    get_endf_name();
      string                    get_pendf_name_old();
      string                    get_pendf_name_new();
      Integer                   get_mat_no();
      Integer                   get_bin_no();
      Integer                   get_ladder_no();
      Integer                   get_opt_print();
      Integer                   get_ene_grid_no();
      Integer                   get_random_seed();
      Integer                   get_sample_no();
      string                    get_p_tab_file_name();
      vector<Real8>             get_temp();
      vector<Real8>             get_sig_zero();

      vector<Real8>             get_time_each_ene();
      Real8                     get_time_total();
  };
}

#endif // PROBABILITY_TABLE_CALCULATOR_BY_NJOY_INPUT_H
