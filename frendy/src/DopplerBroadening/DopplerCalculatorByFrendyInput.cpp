#include "DopplerBroadening/DopplerCalculatorByFrendyInput.hpp"

using namespace frendy;

//constructor
DopplerCalculatorByFrendyInput::DopplerCalculatorByFrendyInput(void)
{
  clear();
}

//destructor
DopplerCalculatorByFrendyInput::~DopplerCalculatorByFrendyInput(void)
{
  clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DopplerCalculatorByFrendyInput::clear()
{
  calc_flg                  = 0;
  set_frendy_inp_obj_flg    = 0;
  set_nucl_data_obj_flg     = 0;
  set_nucl_data_obj_ori_flg = 0;

  nucl_data_obj.clear();
  nucl_data_obj_ori.clear();

  dop_obj.clear();
  th_q_obj.clear();

  frendy_inp_obj.clear();

  time_total = 0.0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DopplerCalculatorByFrendyInput::calc_doppler_broader()
{
  if( calc_flg == 1 )
  {
    return;
  }
  calc_flg = 1;

  check_set_data_flg();

  cout << "****************************** Doppler broadening calculation ******************************";
  cout << endl << endl;
  time_obj.output_current_time();

  boost::timer::cpu_timer timer_total;
  time_total = 0.0;

  //Set NuclearDataObject and input data to DopplerCalculator
  dop_obj.set_nucl_data_obj(nucl_data_obj);
  dop_obj.set_nucl_data_obj_base(nucl_data_obj_ori);
  dop_obj.set_temp_dop(frendy_inp_obj.get_temp());
  dop_obj.set_err(frendy_inp_obj.get_error());
  dop_obj.set_err_max(frendy_inp_obj.get_error_max());
  dop_obj.set_err_int(frendy_inp_obj.get_error_integral());
  dop_obj.set_dop_ene_max(frendy_inp_obj.get_max_broadening_ene());
  
  //Run DopplerCalculator
  dop_obj.output_set_data_information();
  dop_obj.calc_doppler();

  //Get calculation result
  nucl_data_obj    = dop_obj.get_nucl_data_obj();
  Real dop_ene_max = dop_obj.get_dop_ene_max();
  dop_obj.clear();

  //Thermal quantity calculation when temp_dop is 293.6K
  calc_thermal_quantity();


  //Output calculation result
  time_total = static_cast<Real>(timer_total.elapsed().wall * 1.0E-9);
  cout << "Max energy for broader and thinning : " << dop_ene_max << " [eV]" << endl;
  cout << "Total calculation time              : " << time_total  << " [s]" << endl;
  cout << endl;
  cout << "********************************************************************************************";
  cout << endl << endl;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DopplerCalculatorByFrendyInput::calc_thermal_quantity()
{
  Real temp = frendy_inp_obj.get_temp();

  if( th_q_obj.check_temp(temp) != 0 || set_nucl_data_obj_ori_flg == 0 )
  {
    return;
  }

  //Add FissionDataContainer in nucl_data_obj_ori to nucl_data_obj
  NuclearDataObject    nucl_data_obj_tmp = nucl_data_obj;
  FissionDataContainer fis_data_obj      = nucl_data_obj_ori.get_fis_data_obj();
  nucl_data_obj_tmp.set_fis_data_obj(fis_data_obj);

  if( th_q_obj.check_nucl_data_obj(nucl_data_obj_tmp) != 0 )
  {
    return;
  }

  th_q_obj.set_nucl_data_obj(nucl_data_obj_tmp);
  nucl_data_obj_tmp.clear();

  th_q_obj.set_temp_ori(temp);

  Integer fis_flg = th_q_obj.get_fissile_flg();
  if( th_q_obj.get_err_flg() < 0 )
  {
    return;
  }

  cout << endl;
  cout << "thermal quantities at " << temp << " K = "
                                   << th_q_obj.get_ene_ori()    << " eV" << endl;
  cout << "-----------------------------------------" << endl;
  cout.setf(ios::scientific);
  if( fis_flg == 0 )
  {
    cout << " thermal fission xsec       : " << th_q_obj.get_sig_f_th()  << endl;
    cout << " thermal fission nubar      : " << th_q_obj.get_nu_bar_th() << endl;
  }
  cout << " thermal capture xsec       : " << th_q_obj.get_sig_c_th()      << endl;
  cout << " thermal capture g-factor   : " << th_q_obj.get_g_fac_cap()     << endl;
  cout << " thermal capture integral   : " << th_q_obj.get_inte_cap()      << endl;
  cout << " capture resonance integral : " << th_q_obj.get_inte_cap_reso() << endl;
  if( fis_flg == 0 )
  { 
    cout << " thermal fission integral   : " << th_q_obj.get_inte_fis()      << endl;
    cout << " thermal fission g-factor   : " << th_q_obj.get_g_fac_fis()     << endl;
    cout << " thermal alpha integral     : " << th_q_obj.get_alpha()         << endl;
    cout << " thermal eta integral       : " << th_q_obj.get_eta()           << endl;
    cout << " thermal k1 integral        : " << th_q_obj.get_k1()            << endl;
    cout << " equivalent k1              : " << th_q_obj.get_k1_eq()         << endl;
    cout << " fission resonance integral : " << th_q_obj.get_inte_fis_reso() << endl;
  }
  cout.unsetf(ios::scientific);
  cout << "-----------------------------------------" << endl;
  cout << endl;

  th_q_obj.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DopplerCalculatorByFrendyInput::check_set_data_flg()
{
  if( set_frendy_inp_obj_flg == 0 || set_nucl_data_obj_flg == 0 )
  {
    string class_name = "DopplerCalculatorByFrendyInput";
    string func_name  = "check_set_data_flg()";

    vector<string> err_com;
    if( set_frendy_inp_obj_flg == 0 )
    {
      err_com.push_back("Please set the ReconResonanceInputReader object");
      err_com.push_back("using set_frendy_inp_obj() function.");
    }

    if( set_nucl_data_obj_flg == 0 )
    {
      err_com.push_back("Please set the NuclearDataObject");
      err_com.push_back("using set_nucl_data_obj() function.");
    }

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DopplerCalculatorByFrendyInput::set_frendy_inp_obj(DopplerBroadeningInputReader inp_obj)
{
  calc_flg               = 0;
  set_frendy_inp_obj_flg = 1;

  frendy_inp_obj = inp_obj;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DopplerCalculatorByFrendyInput::set_nucl_data_obj_ori(NuclearDataObject data_obj)
{
  calc_flg                  = 0;
  set_nucl_data_obj_ori_flg = 1;

  nucl_data_obj_ori = data_obj;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DopplerCalculatorByFrendyInput::set_nucl_data_obj(NuclearDataObject data_obj)
{
  calc_flg              = 0;
  set_nucl_data_obj_flg = 1;

  nucl_data_obj = data_obj;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//Getter

DopplerBroadeningInputReader DopplerCalculatorByFrendyInput::get_frendy_inp_obj()
{
  return frendy_inp_obj;
}

NuclearDataObject DopplerCalculatorByFrendyInput::get_nucl_data_obj()
{
  calc_doppler_broader();

  return nucl_data_obj;
}

NuclearDataObject DopplerCalculatorByFrendyInput::get_nucl_data_obj_ori()
{
  return nucl_data_obj_ori;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Real DopplerCalculatorByFrendyInput::get_time_total()
{
  return time_total;
}

Real DopplerCalculatorByFrendyInput::get_calc_time()
{
  return time_total;
}

