#ifndef ACE_DATA_GENERATOR_BY_FRENDY_INPUT_H
#define ACE_DATA_GENERATOR_BY_FRENDY_INPUT_H

#include "ContinuousEnergyXSUtils/AceDataGenerator/AceDataGenerator.hpp"
#include "CommonUtils/TimeUtils.hpp"
#include "FrendyUtils/AceDataGeneratorInputReader.hpp"

namespace frendy
{
  class AceDataGeneratorByFrendyInput
  {
    private:
      frendy::ErrorManager     err_obj;
      frendy::VectorClearer    clr_obj;
      frendy::TimeUtils        time_obj;

#ifdef DEBUG_MODE
  public:
#endif

      frendy::AceDataObject               ace_data_obj;
      frendy::NuclearDataObject           nucl_data_obj, nucl_data_obj_ori;

      frendy::AceDataGenerator            ace_obj;
      frendy::AceDataGeneratorInputReader frendy_inp_obj;

      Integer calc_flg, set_inp_mode_flg, set_frendy_inp_obj_flg,
              set_nucl_data_obj_flg, set_nucl_data_obj_ori_flg;

      int     write_ace_flg;
      int     inp_mode, inp_pos;
      int     generate_mode_flg;

      //For time measurement
      Real time_total;

      void check_set_data_flg();

      void set_nucl_data_obj_fast();
      void set_nucl_data_obj_dosimetry();

      void set_input_data();

    public:
      //constructor
      AceDataGeneratorByFrendyInput(void);

      //destructor
      virtual ~AceDataGeneratorByFrendyInput(void);

      static const int write_ace      = 0;
      static const int skip_write_ace = 1;

      void clear();

      void generate_ace_data();

      void set_frendy_inp_obj(frendy::AceDataGeneratorInputReader inp_obj);
      void set_nucl_data_obj(frendy::NuclearDataObject data_obj);
      void set_nucl_data_obj_ori(frendy::NuclearDataObject data_obj);

      void set_inp_mode(int int_val);
      void set_inp_pos(int int_val);
      void set_generate_mode_flg(int int_val);

      void set_write_ace_flg(int int_val);

      frendy::AceDataGeneratorInputReader get_frendy_inp_obj();
      frendy::NuclearDataObject           get_nucl_data_obj();
      frendy::NuclearDataObject           get_nucl_data_obj_ori();
      frendy::AceDataObject               get_ace_data_obj();

      int  get_inp_mode();
      int  get_inp_pos();
      int  get_generate_mode_flg();
      int  get_write_ace_flg();

      Real get_time_total();
      Real get_calc_time();
  };
}

#endif //ACE_DATA_GENERATOR_BY_FRENDY_INPUT_H
