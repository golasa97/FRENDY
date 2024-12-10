#ifndef PROBABILITY_TABLE_CALCULATOR_BY_FRENDY_INPUT_H
#define PROBABILITY_TABLE_CALCULATOR_BY_FRENDY_INPUT_H

#include "CommonUtils/TimeUtils.hpp"
#include "FrendyUtils/ProbTableInputReader.hpp"
#include "NuclearDataUtils/NuclearDataObject.hpp"
#include "UnresoUtils/ProbabilityTableCalculatorByNjoyInput.hpp"

namespace frendy
{
  class ProbabilityTableCalculatorByFrendyInput
  {
    private:
      frendy::ErrorManager      err_obj;
      frendy::VectorClearer     clr_obj;
      frendy::TimeUtils         time_obj;
 
#ifdef DEBUG_MODE
  public:
#endif
      frendy::NuclearDataObject          nucl_data_obj, nucl_data_obj_ori;

      frendy::ProbabilityTableCalculator prob_obj;
      frendy::ProbTableInputReader       frendy_inp_obj;

      Integer calc_flg, set_frendy_inp_obj_flg, set_nucl_data_obj_flg, set_nucl_data_obj_ori_flg;

      //For time measurement
      Real time_total;

      void calc_probability_table();
      void check_set_data_flg();
      void set_prob_obj();

    public:
      //constructor
      ProbabilityTableCalculatorByFrendyInput(void);

      //destructor
      virtual ~ProbabilityTableCalculatorByFrendyInput(void);

      void clear();

      void set_frendy_inp_obj(frendy::ProbTableInputReader inp_obj);
      void set_nucl_data_obj(frendy::NuclearDataObject data_obj);
      void set_nucl_data_obj_ori(frendy::NuclearDataObject data_obj);

      frendy::ProbTableInputReader get_frendy_inp_obj();
      frendy::NuclearDataObject    get_nucl_data_obj();
      frendy::NuclearDataObject    get_nucl_data_obj_ori();

      Real get_time_total();
      Real get_calc_time();
  };
}

#endif // PROBABILITY_TABLE_CALCULATOR_BY_FRENDY_INPUT_H
