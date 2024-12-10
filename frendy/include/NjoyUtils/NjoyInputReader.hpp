#ifndef READ_NJOY_INPUT_H
#define READ_NJOY_INPUT_H

#include "CommonUtils/VectorClearer.hpp"
#include "CommonUtils/ErrorManager.hpp"
#include "CommonUtils/StringUtils.hpp"
#include "EndfUtils/EndfFileReader/EndfUtils.hpp"

namespace frendy
{
  class NjoyInputReader
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;
      frendy::StringUtils   str_util;

      //When quote("'  '") was used, space was not considerd as delimiter
      void substitute_quote(string& str_data);
      void search_quote(vector<string>& str_vec);

      int            func_name_list_no;
      vector<string> func_name_list;
      vector<int>    func_name_list_implemented;


    public:
      static const int pos_reconr =  0;
      static const int pos_broadr =  1;
      static const int pos_unresr =  2;
      static const int pos_heatr  =  3;
      static const int pos_thermr =  4;
      static const int pos_groupr =  5;
      static const int pos_gaminr =  6;
      static const int pos_errorr =  7;
      static const int pos_covr   =  8;
      static const int pos_moder  =  9;
      static const int pos_dtfr   = 10;
      static const int pos_ccccr  = 11;
      static const int pos_matxsr = 12;
      static const int pos_resxsr = 13;
      static const int pos_acer   = 14;
      static const int pos_powr   = 15;
      static const int pos_wimsr  = 16;
      static const int pos_plotr  = 17;
      static const int pos_viewr  = 18;
      static const int pos_mixr   = 19;
      static const int pos_purr   = 20;
      static const int pos_leapr  = 21;
      static const int pos_gaspr  = 22;

      //constructor
      NjoyInputReader(void);

      //destructor
      virtual ~NjoyInputReader(void);

      //search input index, e.g., "reconr" and "broadr"
      void search_each_input(ifstream& fin, string& input_case);
      void search_each_input(ifstream& fin, string& input_case, int line_no);

      //check input case, e.g., "reconr" and "broadr" are exist or not
      int check_input_case(ifstream& fin, string& input_case);
      int check_input_case(ifstream& fin, string& input_case, int start_line_no);
      int check_input_case(string& input_case);

      //devide each data 
      vector<string> read_line_without_slash(string line_data);
      vector<string> read_line(string line_data);

      void erase_after_slash(string& str_data);
      void erase_after_slash(vector<string>& str_vec);

      vector<vector<int> > get_njoy_input_list(string file_name);
      vector<string>       get_func_name_list();

      Integer              get_file_no(string tape_name);
  }; 
}

#endif //READ_NJOY_INPUT_H
