#include "GasProduction/GasProductionXSCalculatorByFrendyInput.hpp"

using namespace frendy;

//constructor
GasProductionXSCalculatorByFrendyInput::GasProductionXSCalculatorByFrendyInput(void)
{
  clear();
}

//destructor
GasProductionXSCalculatorByFrendyInput::~GasProductionXSCalculatorByFrendyInput(void)
{
  clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void GasProductionXSCalculatorByFrendyInput::clear()
{
  calc_flg                  = 0;
  set_frendy_inp_obj_flg    = 0;
  set_nucl_data_obj_flg     = 0;
  set_nucl_data_obj_ori_flg = 0;

  nucl_data_obj.clear();
  nucl_data_obj_ori.clear();

  gas_prod_xs_obj.clear();
  frendy_inp_obj.clear();

  time_total = 0.0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void GasProductionXSCalculatorByFrendyInput::calc_gas_product_xs()
{
  if( calc_flg == 1 )
  {
    return;
  }
  calc_flg = 1;

  check_set_data_flg();

  cout << "****************************** Gas production XS calculation ******************************";
  cout << endl << endl;
  time_obj.output_current_time();

  boost::timer::cpu_timer timer_total;
  time_total = 0.0;

  //Set NuclearDataObject and input data to GasProductionXSCalculator
  gas_prod_xs_obj.set_nucl_data_obj_ori(nucl_data_obj_ori);
  gas_prod_xs_obj.set_nucl_data_obj_dop(nucl_data_obj);
  gas_prod_xs_obj.output_set_data_information();
  gas_prod_xs_obj.calc_gas_production_xs();

  //Get calculation result
  nucl_data_obj = gas_prod_xs_obj.get_nucl_data_obj();

  time_total = static_cast<Real>(timer_total.elapsed().wall * 1.0E-9);
  cout << "Total calculation time : " << time_total << " [s]" << endl;
  cout << endl;
  cout << "********************************************************************************************";
  cout << endl << endl;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void GasProductionXSCalculatorByFrendyInput::check_set_data_flg()
{
  if( set_frendy_inp_obj_flg == 0 || set_nucl_data_obj_flg == 0 || set_nucl_data_obj_ori_flg == 0)
  {
    string class_name = "GasProductionXSCalculatorByFrendyInput";
    string func_name  = "check_set_data_flg()";

    vector<string> err_com;
    if( set_frendy_inp_obj_flg == 0 )
    {
      err_com.push_back("Please set the GasProductionInputReader object");
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
      err_com.push_back("using set_nucl_data_obj_ori() function.");
    }

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void GasProductionXSCalculatorByFrendyInput::set_frendy_inp_obj(GasProductionInputReader inp_obj)
{
  calc_flg               = 0;
  set_frendy_inp_obj_flg = 1;

  frendy_inp_obj = inp_obj;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void GasProductionXSCalculatorByFrendyInput::set_nucl_data_obj(NuclearDataObject data_obj)
{
  calc_flg              = 0;
  set_nucl_data_obj_flg = 1;

  nucl_data_obj = data_obj;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void GasProductionXSCalculatorByFrendyInput::set_nucl_data_obj_ori(NuclearDataObject data_obj)
{
  calc_flg                  = 0;
  set_nucl_data_obj_ori_flg = 1;

  nucl_data_obj_ori = data_obj;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//Getter

GasProductionInputReader GasProductionXSCalculatorByFrendyInput::get_frendy_inp_obj()
{
  return frendy_inp_obj;
}

NuclearDataObject GasProductionXSCalculatorByFrendyInput::get_nucl_data_obj()
{
  calc_gas_product_xs();

  return nucl_data_obj;
}

NuclearDataObject GasProductionXSCalculatorByFrendyInput::get_nucl_data_obj_ori()
{
  return nucl_data_obj_ori;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Real GasProductionXSCalculatorByFrendyInput::get_time_total()
{
  return time_total;
}

Real GasProductionXSCalculatorByFrendyInput::get_calc_time()
{
  return time_total;
}
