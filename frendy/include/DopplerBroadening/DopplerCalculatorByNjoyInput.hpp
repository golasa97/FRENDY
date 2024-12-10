#ifndef DOPPLER_CALCULATOR_BY_NJOY_H
#define DOPPLER_CALCULATOR_BY_NJOY_H

#include <boost/timer/timer.hpp>

#include "CommonUtils/TimeUtils.hpp"
#include "EndfUtils/Endf6Converter/Endf6Converter.hpp"
#include "EndfUtils/Endf6Writer/Endf6Writer.hpp"
#include "EndfUtils/OtherUtils/EndfTapeDivider.hpp"
#include "NjoyUtils/BroadrInputReader.hpp"
#include "NuclearDataUtils/OtherUtils/Endf6FileStore.hpp"
#include "DopplerBroadening/DopplerCalculator.hpp"
#include "DopplerBroadening/ThermalQuantityCalculator.hpp"

namespace frendy
{
  class DopplerCalculatorByNjoyInput
  {
    private:
      frendy::VectorClearer  clr_obj;
      frendy::ErrorManager   err_obj;
      frendy::TimeUtils      time_obj;
      frendy::Endf6Converter conv_obj;
      frendy::Endf6FileStore store_obj;

      frendy::DopplerCalculator         dop_obj;
      frendy::ThermalQuantityCalculator th_q_obj;
      frendy::Endf6Writer               wri_obj;

      frendy::NuclearDataObject                  nucl_data_obj_base;
      vector<frendy::NuclearDataObject>          nucl_data_obj_ori;
      vector<vector<frendy::NuclearDataObject> > nucl_data_obj_dop;

      string                 input_file_name_njoy;
      int                    start_line_no;

      string                 endf_file_name, pendf_input_name, pendf_output_name, label_data;
      vector<Integer>        mat_no_list, temp_no_list, istart_list, istrap_list;
      vector<Real8>          temp_ini, err, err_int, err_max, dop_ene_max_inp, dop_ene_max_cal;
      vector<vector<Real8> > temp_dop;
      vector<Real8>          temp_ini_chk;
      
      Integer calc_flg, set_nucl_data_obj_flg;
      
      //For time measurement
      Real                  time_total;
      vector<Real>          time_each_mat;
      vector<vector<Real> > time_each_temp;
      
      void calc_doppler_broader();
      void calc_doppler_broader_each_mat(int mat_no);
      void calc_doppler_broader_each_temp(int mat_no, int temp_no, Real8 temp_ori);
      void calc_thermal_quantity(int mat_no, int temp_no);
      
      void set_input_data();
      void check_set_data();
      
      void write_text_data(ofstream& fout, vector<string>& text);
      void add_previous_pendf_text(int mat_no, vector<string>& text);

      void output_input_file_name();
    
    public:
      //constructor
      DopplerCalculatorByNjoyInput(void);

      //destructor
      virtual ~DopplerCalculatorByNjoyInput(void);

      void clear();
      
      void set_njoy_input_file_name(string file_name);
      void set_njoy_input_file_name(string file_name, int line_no);

      void write_pendf_file();

      void set_nucl_data_obj_ori(vector<frendy::NuclearDataObject>& data_obj);

      string                 get_njoy_input_file_name();
      string                 get_endf_file_name();
      string                 get_pendf_input_name();
      string                 get_pendf_output_name();
      vector<Integer>        get_mat_no_list();
      vector<Integer>        get_temp_no_list();
      vector<Integer>        get_istart_list();
      vector<Integer>        get_istrap_list();
      vector<Real8>          get_temp_ini();
      vector<Real8>          get_err();
      vector<Real8>          get_err_int();
      vector<Real8>          get_err_max();
      vector<Real8>          get_dop_ene_max();
      vector<vector<Real8> > get_temp_dop();
      vector<Real8>          get_temp_ini_chk();
      
      vector<frendy::NuclearDataObject>          get_nucl_data_obj_ori();
      vector<vector<frendy::NuclearDataObject> > get_nucl_data_obj_dop();
      
      Real                  get_time_total();
      vector<Real>          get_time_each_mat();
      vector<vector<Real> > get_time_each_temp();
  };
}

#endif //DOPPLER_CALCULATOR_BY_NJOY_H
