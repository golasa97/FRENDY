#ifndef THERMAL_SCATTER_CALCULATOR_BY_NJOY_INPUT_H
#define THERMAL_SCATTER_CALCULATOR_BY_NJOY_INPUT_H

#include "CommonUtils/TimeUtils.hpp"
#include "EndfUtils/OtherUtils/EndfTapeDivider.hpp"
#include "EndfUtils/Endf6Writer/Endf6Writer.hpp"
#include "NjoyUtils/ThermrInputReader.hpp"
#include "ThermalScatter/ThermalScatterCalculator.hpp"
#include "ThermalScatter/ThermalScatterDataConverter.hpp"

namespace frendy
{
  class ThermalScatterCalculatorByNjoyInput
  {
    private:
      frendy::ErrorManager    err_obj;
      frendy::VectorClearer   clr_obj;
      frendy::TimeUtils       time_obj;

#ifdef DEBUG_MODE
  public:
#endif
      frendy::ThermalScatterCalculator    scat_calc_obj;
      frendy::ThermalScatterDataConverter scat_conv_obj;

      vector<frendy::NuclearDataObject> pendf_new_data_obj;
      Integer calc_flg;

      string        input_file_name_njoy;
      int           start_line_no;

      string        endf_name, pendf_name_old, pendf_name_new, label_data;
      Integer       mat_endf, mat_pendf, bin_no, temp_no, opt_inelastic, opt_elastic,
                    atom_no, mt_out, opt_print;
      vector<Real8> temp;
      Real8         err, ene_max;
      int           temp_no_int, endf_data_no;
      vector<int>   temp_no_list;

      //For time measurement
      Real                  time_total;
      vector<Real>          time_each_temp;

      void set_input_data();
      void set_scat_calc_obj();
      void set_pendf_new_data_obj();

      void write_pendf_file_each_temp(int ele_no, vector<string>& text);

      void output_input_file_name();

    public:
      //constructor
      ThermalScatterCalculatorByNjoyInput(void);

      //destructor
      virtual ~ThermalScatterCalculatorByNjoyInput(void);

      void clear();

      void calc_thermal_scatter();
      void write_pendf_file();

      //Setter
      void set_njoy_input_file_name(string str_data);
      void set_njoy_input_file_name(string file_name, int line_no);

      //Getter
      vector<NuclearDataObject> get_nucl_data_obj();
      vector<NuclearDataObject> get_nucl_data_obj_without_tsl();
      string        get_njoy_input_file_name();

      string        get_endf_name();
      string        get_pendf_name_old();
      string        get_pendf_name_new();
      Integer       get_mat_endf();
      Integer       get_mat_pendf();
      Integer       get_bin_no();
      Integer       get_temp_no();
      Integer       get_opt_inelastic();
      Integer       get_opt_elastic();
      Integer       get_atom_no();
      Integer       get_mt_out();
      Integer       get_opt_print();
      vector<Real8> get_temp();
      Real8         get_err();
      Real8         get_ene_max();

      Real          get_time_total();
      vector<Real>  get_time_each_temp();
  };
}

#endif //THERMAL_SCATTER_CALCULATOR_BY_NJOY_INPUT_H
