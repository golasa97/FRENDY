#ifndef MAKE_NJOY_INPUT_READER_H
#define MAKE_NJOY_INPUT_READER_H

#include "CommonUtils/VectorClearer.hpp"
#include "EndfUtils/EndfFileReader/StringConverter.hpp"
#include "CommonUtils/FileCommentRemover.hpp"
#include "FrendyUtils/FrendyInputCommonUtils.hpp"

namespace frendy
{
  class MakeNJOYInputReader
  {
    private:
      frendy::ErrorManager           err_obj;
      frendy::VectorClearer          clr_obj;
      frendy::StringConverter        str_obj;
      frendy::FrendyInputCommonUtils frendy_utils;

#ifdef DEBUG_MODE
  public:
#endif
      int print_set_data_flg, print_title_flg;

      int reconr_flg, broadr_flg, gaspr_flg, purr_flg, thermr_flg, acer_flg,
          groupr_flg, matxsr_flg, heatr_flg;

      void set_all_calc_flg_on();
      void set_all_calc_flg_off();

      void set_make_input_module(vector<string> input_data);

    public:

      //constructor
      MakeNJOYInputReader(void);

      //destructor
      virtual ~MakeNJOYInputReader(void);

      void clear();

      void read_input_data_from_input_file(string file_name);

      vector<int> read_input_data(vector<vector<string> >& input_data);
      int         read_input_data(vector<string>& input_type, vector<string>& input_data);
      int         read_input_data(string&         input_type, vector<string>& input_data);

      //Getter
      int            get_reconr_flg();
      int            get_broadr_flg();
      int            get_gaspr_flg();
      int            get_purr_flg();
      int            get_thermr_flg();
      int            get_acer_flg();
      int            get_groupr_flg();
      int            get_matxsr_flg();
      int            get_heatr_flg();
  }; 
}

#endif //MAKE_NJOY_INPUT_READER_H
