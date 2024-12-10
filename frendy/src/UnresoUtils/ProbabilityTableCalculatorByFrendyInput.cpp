#include "UnresoUtils/ProbabilityTableCalculatorByFrendyInput.hpp"

using namespace frendy;

//constructor
ProbabilityTableCalculatorByFrendyInput::ProbabilityTableCalculatorByFrendyInput(void)
{
  clear();
}

//destructor
ProbabilityTableCalculatorByFrendyInput::~ProbabilityTableCalculatorByFrendyInput(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculatorByFrendyInput::clear()
{
  calc_flg                  = 0;
  set_frendy_inp_obj_flg    = 0;
  set_nucl_data_obj_flg     = 0;
  set_nucl_data_obj_ori_flg = 0;

  nucl_data_obj.clear();
  nucl_data_obj_ori.clear();

  prob_obj.clear();
  frendy_inp_obj.clear();

  time_total = 0.0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculatorByFrendyInput::calc_probability_table()
{
  if( calc_flg == 1 )
  {
    return;
  }
  calc_flg = 1;

  check_set_data_flg();

  cout << "****************************** Probability Table calculation ******************************";
  cout << endl << endl;
  time_obj.output_current_time();

  boost::timer::cpu_timer timer_total;
  time_total = 0.0;

  //Set NuclearDataObject and input data to ProbabilityTableCalculator
  prob_obj.set_time_print_opt(prob_obj.print_time_data);

  Real temp = nucl_data_obj.get_general_data_obj().get_temp();
  prob_obj.set_nucl_data_obj(nucl_data_obj_ori);
  prob_obj.set_ladder_no(frendy_inp_obj.get_ladder_no());
  prob_obj.set_static_err(frendy_inp_obj.get_err_p_tab());
  prob_obj.set_bin_no(frendy_inp_obj.get_probability_bin_no());
  prob_obj.set_random_seed(frendy_inp_obj.get_random_seed());
  prob_obj.set_sample_no(frendy_inp_obj.get_ene_grid_no_per_ladder());
  prob_obj.set_temp_data(temp);
  prob_obj.set_sig_zero_data(frendy_inp_obj.get_sigma_zero_data());

  //Calculation of probability_table
  prob_obj.output_set_data_information();
  prob_obj.calc_probability_table();

  ProbabilityTableCalculatorByNjoyInput prob_calc_njoy;
  prob_calc_njoy.set_unreso_xs_and_prob_data_obj
                  (0, nucl_data_obj, prob_obj.get_nucl_data_obj().get_prob_data_obj());
  prob_calc_njoy.clear();

  time_total = static_cast<Real>(timer_total.elapsed().wall * 1.0E-9);
  cout << "Total calculation time : " << time_total << " [s]" << endl;
  cout << endl;
  cout << "*******************************************************************************************";
  cout << endl << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculatorByFrendyInput::check_set_data_flg()
{
  if( set_frendy_inp_obj_flg == 0 || set_nucl_data_obj_flg == 0 || set_nucl_data_obj_ori_flg == 0 )
  {
    string class_name = "ProbabilityTableCalculatorByFrendyInput";
    string func_name  = "check_set_data_flg()";

    vector<string> err_com;
    if( set_frendy_inp_obj_flg == 0 )
    {
      err_com.push_back("Please set the ProbTableInputReader object");
      err_com.push_back("using set_frendy_inp_obj() function.");
    }

    if( set_nucl_data_obj_flg == 0 )
    {
      err_com.push_back("Please set the NuclearDataObject");
      err_com.push_back("using set_nucl_data_obj() function.");
    }

    if( set_nucl_data_obj_ori_flg == 0 )
    {
      err_com.push_back("Please set the original NuclearDataObject");
      err_com.push_back("using set_nucl_data_ori_obj() function.");
    }

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//Setter

void ProbabilityTableCalculatorByFrendyInput::set_frendy_inp_obj(ProbTableInputReader inp_obj)
{
  calc_flg               = 0;
  set_frendy_inp_obj_flg = 1;

  frendy_inp_obj = inp_obj;
}

void ProbabilityTableCalculatorByFrendyInput::set_nucl_data_obj(NuclearDataObject data_obj)
{
  calc_flg              = 0;
  set_nucl_data_obj_flg = 1;

  nucl_data_obj = data_obj;
}

void ProbabilityTableCalculatorByFrendyInput::set_nucl_data_obj_ori(NuclearDataObject data_obj)
{
  calc_flg                  = 0;
  set_nucl_data_obj_ori_flg = 1;

  nucl_data_obj_ori = data_obj;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//Getter

ProbTableInputReader ProbabilityTableCalculatorByFrendyInput::get_frendy_inp_obj()
{
  return frendy_inp_obj;
}

NuclearDataObject ProbabilityTableCalculatorByFrendyInput::get_nucl_data_obj()
{
  calc_probability_table();

  return nucl_data_obj;
}

NuclearDataObject ProbabilityTableCalculatorByFrendyInput::get_nucl_data_obj_ori()
{
  return nucl_data_obj_ori;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Real ProbabilityTableCalculatorByFrendyInput::get_time_total()
{
  return time_total;
}

Real ProbabilityTableCalculatorByFrendyInput::get_calc_time()
{
  return time_total;
}
