#include "ThermalScatter/ThermalScatterCalculatorByFrendyInput.hpp"

using namespace frendy;

//constructor
ThermalScatterCalculatorByFrendyInput::ThermalScatterCalculatorByFrendyInput(void)
{
  clear();
}

//destructor
ThermalScatterCalculatorByFrendyInput::~ThermalScatterCalculatorByFrendyInput(void)
{
  clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterCalculatorByFrendyInput::clear()
{
  calc_flg                  = 0;
  set_frendy_inp_obj_flg    = 0;
  set_nucl_data_obj_flg     = 0;
  set_nucl_data_obj_tsl_flg = 0;

  opt_elastic   = 0;
  opt_inelastic = 0;

  nucl_data_obj.clear();
  nucl_data_obj_tsl.clear();

  scat_calc_obj.clear();
  scat_conv_obj.clear();
  frendy_inp_obj.clear();

  time_total = 0.0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterCalculatorByFrendyInput::calc_thermal_scatter()
{
  if( calc_flg == 1 )
  {
    return;
  }
  calc_flg = 1;

  check_set_data_flg();

  cout << "****************************** Thermal scattering xs calculation ******************************";
  cout << endl << endl;
  time_obj.output_current_time();

  boost::timer::cpu_timer timer_total;
  time_total = 0.0;

  //Set NuclearDataObject and input data to ThermalScatterCalculator
  nucl_data_obj.set_thermal_scat_data_obj(nucl_data_obj_tsl.get_thermal_scat_data_obj());
  Real temp = nucl_data_obj.get_general_data_obj().get_temp();

  scat_calc_obj.set_nucl_data_obj(nucl_data_obj);
  scat_calc_obj.set_opt_inelastic(opt_inelastic);
  scat_calc_obj.set_opt_elastic(opt_elastic);
  scat_calc_obj.set_bin_no(frendy_inp_obj.get_equi_probable_angle_no());
  scat_calc_obj.set_atom_no(frendy_inp_obj.get_principal_atom_no());
  scat_calc_obj.set_err(frendy_inp_obj.get_error());
  scat_calc_obj.set_temp(temp);

  scat_calc_obj.set_ene_max(set_max_thermal_ene());

  //Run ThermalScatterCalculator
  scat_calc_obj.output_set_data_information();
  scat_calc_obj.calc_thermal_scatter();

  //Get calculation result
  nucl_data_obj = scat_calc_obj.get_nucl_data_obj();
  scat_conv_obj.convert_thermal_scatter_data
                  (frendy_inp_obj.get_inelastic_reaction_type_no(), nucl_data_obj);
  scat_calc_obj.clear();
  scat_conv_obj.clear();

  time_total = static_cast<Real>(timer_total.elapsed().wall * 1.0E-9);
  cout << "Total calculation time : " << time_total << " [s]" << endl;
  cout << endl;
  cout << "***********************************************************************************************";
  cout << endl << endl;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterCalculatorByFrendyInput::check_set_data_flg()
{
  if( set_frendy_inp_obj_flg == 0 || set_nucl_data_obj_flg == 0 || set_nucl_data_obj_tsl_flg == 0)
  {
    string class_name = "ThermalScatterCalculatorByFrendyInput";
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

    if( set_nucl_data_obj_tsl_flg == 0 )
    {
      err_com.push_back("Please set the NuclearDataObject for thermal scattering low");
      err_com.push_back("using set_nucl_data_obj_tsl() function.");
    }

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Real ThermalScatterCalculatorByFrendyInput::set_max_thermal_ene()
{
  //Copy from MakeInputFromFRENDYtoNJOY (get_max_thermal_ene())
  Real max_thermal_ene = frendy_inp_obj.get_max_thermal_ene();
  if( frendy_inp_obj.get_set_max_thermal_ene_flg() == 0 ) //Automatically set parameter
  {
    if( scat_calc_obj.get_max_thermal_ene_endf() > max_thermal_ene )
    {
      string class_name = "ThermalScatterCalculatorByFrendyInput";
      string func_name  = "set_max_thermal_ene()";

      ostringstream oss01, oss02;
      oss01 << max_thermal_ene;
      oss02 << scat_calc_obj.get_max_thermal_ene_endf();
      string str_data01 = "Maximum thermal scattering energy from input   : " + oss01.str() + " [eV]";
      string str_data02 = "Maximum thermal scattering energy from XS data : " + oss02.str() + " [eV]";
      string str_data03 = "The maximum thermal scattering energy is reset to " + oss02.str() + " eV.";

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back("The maximum thermal scattering energy from xs data is larger than input data.");
      err_com.push_back(str_data03);
      err_obj.output_caution(class_name, func_name, err_com);

      max_thermal_ene = scat_calc_obj.get_max_thermal_ene_endf();
    }
  }

  return max_thermal_ene;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter

void ThermalScatterCalculatorByFrendyInput::set_frendy_inp_obj(ThermalScatterInputReader inp_obj)
{
  calc_flg               = 0;
  set_frendy_inp_obj_flg = 1;

  frendy_inp_obj = inp_obj;
}

void ThermalScatterCalculatorByFrendyInput::set_nucl_data_obj(NuclearDataObject data_obj)
{
  calc_flg              = 0;
  set_nucl_data_obj_flg = 1;

  nucl_data_obj = data_obj;
}

void ThermalScatterCalculatorByFrendyInput::set_nucl_data_obj_tsl(NuclearDataObject data_obj)
{
  calc_flg                  = 0;
  set_nucl_data_obj_tsl_flg = 1;

  nucl_data_obj_tsl = data_obj;

  //Set opt_elastic and opt_inelastic
  ThermalScatterDataContainer tsl_obj = nucl_data_obj_tsl.get_thermal_scat_data_obj();

  //Set opt_elastic
  if( tsl_obj.get_elastic_scat_flg() == 0 ||
      ( static_cast<int>(tsl_obj.get_elastic_temp_data().size()) == 0 &&
        static_cast<int>(tsl_obj.get_elastic_debye_waller_data().size()) == 0 ) )
  {  
    opt_elastic = 0;
  }
  else
  {
    opt_elastic = 10;
  }

  //Set opt_inelastic
  if( static_cast<int>(tsl_obj.get_inelastic_scat_law_coef().size()) == 0 &&
      static_cast<int>(tsl_obj.get_inelastic_temp_int().size())      == 0 &&
      static_cast<int>(tsl_obj.get_inelastic_temp_data().size())     == 0 &&
      static_cast<int>(tsl_obj.get_inelastic_scat_law_data().size()) == 0 )
  {
    opt_inelastic = 1;
  }
  else
  {
    opt_inelastic = 2;
  }
  tsl_obj.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//Getter

ThermalScatterInputReader ThermalScatterCalculatorByFrendyInput::get_frendy_inp_obj()
{
  return frendy_inp_obj;
}

NuclearDataObject ThermalScatterCalculatorByFrendyInput::get_nucl_data_obj()
{
  calc_thermal_scatter();

  return nucl_data_obj;
}

NuclearDataObject ThermalScatterCalculatorByFrendyInput::get_nucl_data_obj_without_tsl()
{
  calc_thermal_scatter();

  NuclearDataObject           nucl_data_obj_without_tsl = nucl_data_obj;
  ThermalScatterDataContainer tsl_obj;
  tsl_obj.clear();

  nucl_data_obj_without_tsl.set_thermal_scat_data_obj(tsl_obj);

  return nucl_data_obj_without_tsl;
}

NuclearDataObject ThermalScatterCalculatorByFrendyInput::get_nucl_data_obj_tsl()
{
  return nucl_data_obj_tsl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Real ThermalScatterCalculatorByFrendyInput::get_time_total()
{
  return time_total;
}

Real ThermalScatterCalculatorByFrendyInput::get_calc_time()
{
  return time_total;
}


