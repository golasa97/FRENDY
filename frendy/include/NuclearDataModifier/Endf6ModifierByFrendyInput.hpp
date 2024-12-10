#ifndef ENDF6_MODIFIER_BY_FRENDY_INPUT_H
#define ENDF6_MODIFIER_BY_FRENDY_INPUT_H

#include "CommonUtils/TimeUtils.hpp"
#include "CommonUtils/ErrorManager.hpp"
#include "NuclearDataUtils/NuclearDataObject.hpp"
#include "EndfUtils/Endf6Writer/Endf6Writer.hpp"
#include "FrendyUtils/Endf6ModifierInputReader.hpp"
#include "NuclearDataModifier/NuclearDataModifier.hpp"
#include "NuclearDataModifier/Endf6Modifier.hpp"
#include "NuclearDataUtils/OtherUtils/Endf6FileStore.hpp"


namespace frendy
{
  class Endf6ModifierByFrendyInput
  {
    private:
      frendy::VectorClearer  clr_obj;
      frendy::ErrorManager   err_obj;
      frendy::TimeUtils      time_obj;

      frendy::Endf6Writer         endf_wri_obj;

      frendy::Endf6Modifier       endf_mod_obj;
      frendy::NuclearDataModifier nucl_mod_obj;

      frendy::Endf6FileStore read_obj;

      frendy::Endf6ModifierInputReader  frendy_inp_obj;
      frendy::NuclearDataObject nucl_data_obj_ori, nucl_data_obj_add, nucl_data_obj_mod;

      int  calc_flg;
      Real linearize_tolerance;

      //For time measurement
      Real time_total;

      void modify_endf6_format(int run_flg, vector<Integer> mf_no, vector<Integer> mt_no,
                               string endf_name_ori_inp, string endf_name_add_inp, string endf_name_mod_inp);

      void remove_endf6_data
             (int target_mode_flg, vector<Integer> mf_no, vector<Integer> mt_no,
              frendy::NuclearDataObject& nucl_data_obj);

      void change_endf6_data
             (int target_mode_flg, vector<Integer> mf_no, vector<Integer> mt_no,
              frendy::NuclearDataObject& nucl_data_obj, frendy::NuclearDataObject& nucl_data_obj_add);
      void add_endf6_data
             (int target_mode_flg, vector<Integer> mf_no, vector<Integer> mt_no,
              frendy::NuclearDataObject& nucl_data_obj, frendy::NuclearDataObject& nucl_data_obj_add);

      void linearize_endf6_data
             (int target_mode_flg, vector<Integer> mf_no, vector<Integer> mt_no, string endf_name_ori_inp,
              frendy::NuclearDataObject& nucl_data_obj);

    public:
      //constructor
      Endf6ModifierByFrendyInput(void);

      //destructor
      virtual ~Endf6ModifierByFrendyInput(void);

      void clear();
      
      void calc_endf6_modifier();

      void set_frendy_input(string input_file_name);
      void set_frendy_inp_obj(frendy::Endf6ModifierInputReader inp_obj);

      frendy::Endf6ModifierInputReader get_frendy_inp_obj();
      frendy::NuclearDataObject get_nucl_data_obj_ori();
      frendy::NuclearDataObject get_nucl_data_obj_add();
      frendy::NuclearDataObject get_nucl_data_obj_mod();

      Real get_time_total();
      Real get_calc_time();
  };
}

#endif //ENDF6_MODIFIER_BY_FRENDY_INPUT_H
