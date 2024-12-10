#ifndef ACE_DATA_GENERATOR_BY_NJOY_INPUT_H
#define ACE_DATA_GENERATOR_BY_NJOY_INPUT_H

#include "ContinuousEnergyXSUtils/AceDataGenerator/AceDataGenerator.hpp"
#include "CommonUtils/TimeUtils.hpp"
#include "NjoyUtils/AcerInputReader.hpp"
#include "EndfUtils/OtherUtils/EndfTapeDivider.hpp"
#include "EndfUtils/Endf6Writer/Endf6Writer.hpp"

namespace frendy
{
  class AceDataGeneratorByNjoyInput
  {
    private:
      frendy::ErrorManager     err_obj;
      frendy::VectorClearer    clr_obj;
      frendy::TimeUtils        time_obj;

      frendy::AceDataGenerator ace_obj;

      static const int fast_data_mode          = 1;
      static const int thermal_data_mode       = 2;
      static const int dosimetry_data_mode     = 3;
      static const int photo_atomic_data_mode  = 4;
      static const int photo_nuclear_data_mode = 5;

#ifdef DEBUG_MODE
  public:
#endif
      string input_file_name_njoy;
      int    start_line_no;

      string endf_name, pendf_name, gendf_name;

      Integer calc_flg, mat, time_total;
      int     opt_run;
      Real    temp;

      int     generate_mode_flg;

      void set_input_data();

      void output_input_file_name();

      void set_nucl_data_obj_all();
      void set_nucl_data_obj_fast(NuclearDataObject& nucl_data_obj);
      void set_nucl_data_obj_dosimetry(NuclearDataObject& nucl_data_obj);
      void set_nucl_data_obj(string& file_name, frendy::NuclearDataObject& nucl_obj, Real temp_val);

    public:
      //constructor
      AceDataGeneratorByNjoyInput(void);

      //destructor
      virtual ~AceDataGeneratorByNjoyInput(void);

      static const int generate_default_mode = 0;
      static const int generate_njoy_mode    = 1;

      void clear();

      void generate_ace_data();

      //Setter
      void set_njoy_input_file_name(string str_data);
      void set_njoy_input_file_name(string str_data, int line_no);

      void set_generate_mode_flg(int int_val);

      //Getter
      string get_njoy_input_file_name();
      int    get_generate_mode_flg();
  };
}

#endif //ACE_DATA_GENERATOR_BY_NJOY_INPUT_H
