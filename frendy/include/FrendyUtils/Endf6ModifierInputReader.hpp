#ifndef ENDF6_MODIFIER_INPUT_READER_H
#define ENDF6_MODIFIER_INPUT_READER_H

#include "CommonUtils/VectorClearer.hpp"
#include "EndfUtils/EndfFileReader/StringConverter.hpp"
#include "CommonUtils/FileCommentRemover.hpp"
#include "FrendyUtils/FrendyInputCommonUtils.hpp"
#include "FrendyUtils/StringDataConverter.hpp"

namespace frendy
{
  class Endf6ModifierInputReader
  {
    private:
      frendy::ErrorManager           err_obj;
      frendy::VectorClearer          clr_obj;
      frendy::StringConverter        str_obj;
      frendy::StringDataConverter    str_conv_obj;
      frendy::FrendyInputCommonUtils frendy_utils;

#ifdef DEBUG_MODE
  public:
#endif

      vector<int>              run_flg;
      vector<vector<Integer> > mf_no, mt_no;
      vector<string>           endf_name_ori, endf_name_add, endf_name_mod;

      Real linearize_tolerance;

      void check_tolerance(vector<vector<string> >& input_data);

    public:

      //constructor
      Endf6ModifierInputReader(void);

      //destructor
      virtual ~Endf6ModifierInputReader(void);

      static const int   remove_data_mode     =   1;
      static const int   change_data_mode     =   2;
      static const int   add_data_mode        =   3;
      static const int   linearize_data_mode  =   4;
      static const int   mf_mode              =   0;
      static const int   mt_mode              =   1;
      static const int   mf_mt_mode           =   2;

      static const int   remove_mf_mode       = 101; //remove_data_mode + 100
      static const int   change_mf_mode       = 102;
      static const int   add_mf_mode          = 103;
      static const int   linearize_mf_mode    = 104;
      static const int   remove_mt_mode       = 201; //remove_data_mode + 200
      static const int   change_mt_mode       = 202;
      static const int   add_mt_mode          = 203;
      static const int   linearize_mt_mode    = 204;
      static const int   remove_mf_mt_mode    = 301; //remove_data_mode + 300
      static const int   change_mf_mt_mode    = 302;
      static const int   add_mf_mt_mode       = 303;
      static const int   linearize_mf_mt_mode = 304;

      static const string remove_flg_str;
      static const string change_flg_str;
      static const string exchange_flg_str;
      static const string replace_flg_str;
      static const string add_flg_str;
      static const string linearize_flg_str;
      static const string mf_flg_str;
      static const string mt_flg_str;

      void clear();

      void read_input_data_from_input_file(string file_name);
      void read_input_data(vector<vector<string> >& input_data);

      void output_input_information
             (int run_mode_flg, int target_mode_flg, vector<int> mf_no_inp, vector<int> mt_no_inp,
              string endf_name_ori_inp, string endf_name_add_inp, string endf_name_mod_inp, int ele_no);


      //Setter
      void set_run_flg(vector<int> int_vec);
      void set_mf_no(vector<vector<Integer> > int_vec);
      void set_mt_no(vector<vector<Integer> > int_vec);

      void set_endf_name_ori(vector<string> str_vec);
      void set_endf_name_add(vector<string> str_vec);
      void set_endf_name_mod(vector<string> str_vec);
      void set_endf_name_linearize(vector<string> str_vec);

      void set_linearize_tolerance(Real real_val);

      //Getter
      vector<int>              get_run_flg();
      vector<vector<Integer> > get_mf_no();
      vector<vector<Integer> > get_mt_no();
      vector<string>           get_endf_name_ori();
      vector<string>           get_endf_name_add();
      vector<string>           get_endf_name_mod();
      vector<string>           get_endf_name_renearize();
      Real                     get_linearize_tolerance();
  }; 
}

#endif //ENDF6_MODIFIER_INPUT_READER_H
