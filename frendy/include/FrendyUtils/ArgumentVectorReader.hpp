#ifndef ARGUMENT_VECTOR_READER_H
#define ARGUMENT_VECTOR_READER_H

#include "CommonUtils/VectorClearer.hpp"
#include "EndfUtils/EndfFileReader/StringConverter.hpp"
#include "CommonUtils/FileCommentRemover.hpp"
#include "FrendyUtils/FrendyInputReader.hpp"

namespace frendy
{
  class ArgumentVectorReader
  {
    private:
      frendy::ErrorManager           err_obj;
      frendy::VectorClearer          clr_obj;
      frendy::StringConverter        str_obj;
      frendy::FrendyInputCommonUtils frendy_utils;

#ifdef DEBUG_MODE
  public:
#endif
      static const int input_file_name_flg = 0;
      static const int nucl_file_name_flg  = 1;
      static const int temp_flg            = 2;
      static const int calc_mode_flg       = 3;

      int            flg_no,   calc_mode_no;
      vector<int>    flg_mode, calc_mode_list_mode;
      vector<string> flg_list, calc_mode_list_name;

      int set_arg_vec_flg;

      vector<string> arg_vec, nucl_file_name;
      string         input_file_name;
      Real           temp;
      int            calc_mode;

      void clear_input_data();

      void read_flg_data(string arg_flg);
      void read_calc_mode(string arg_data);

      int  search_flg_mode(string str_data);
      int  check_flg_data(string str_data);

    public:

      //constructor
      ArgumentVectorReader(void);

      //destructor
      virtual ~ArgumentVectorReader(void);

      void clear();

      void read_argument_data();

      //Setter
      void set_argument_vector(vector<string> str_vec);

      //Getter
      vector<string> get_argument_vector();
      string         get_input_file_name();
      vector<string> get_nucl_file_name();
      Real           get_temp();
      int            get_calc_mode();
  }; 
}

#endif //ARGUMENT_VECTOR_READER_H
