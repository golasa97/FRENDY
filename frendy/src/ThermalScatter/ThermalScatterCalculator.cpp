#include "ThermalScatter/ThermalScatterCalculator.hpp"

using namespace frendy;

//constructor
ThermalScatterCalculator::ThermalScatterCalculator(void)
{
  clear();
}

//destructor
ThermalScatterCalculator::~ThermalScatterCalculator(void)
{
  clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterCalculator::clear()
{
  incoh_inela_calc_obj.clear();
  coh_ela_calc_obj.clear();
  incoh_ela_calc_obj.clear();

  nucl_data_obj.clear();
  nucl_data_name.clear();

  calc_thermal_scat_flg = 0;
  nucl_data_set_flg     = 0;
  elastic_scat_flg      = 0;

  opt_inelastic         = 0;
  opt_elastic           = 0;
  bin_no                = 0;
  atom_no               = 0;

  err                   = 0.0;
  ene_max               = 0.0;
  temp                  = 0.0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterCalculator::calc_thermal_scatter()
{
  if( calc_thermal_scat_flg != 0 )
  {
    return;
  }
  calc_thermal_scat_flg = 1;

  if( nucl_data_set_flg == 0 )
  {
    string class_name = "ThermalScatterCalculator";
    string func_name  = "calc_thermal_scatter()";

    vector<string> err_com;
    err_com.push_back("There is no NuclearDataObject.");
    err_com.push_back("Please set nuclear data object using set_nucl_data_obj function.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //Check set data
  check_opt_elastic();
  check_set_data();

  //Calculation of thermal scattering cross section
  calc_coherent_elastic_scatter();
  calc_incoherent_elastic_scatter();
  calc_incoherent_inelastic_scatter();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterCalculator::calc_incoherent_inelastic_scatter()
{
  if( opt_inelastic == incoh_inela_calc_obj.no_calc )
  {
    return;
  }

  //Calculation of incoherent inelastic scatter cross section
  incoh_inela_calc_obj.set_nucl_data_obj(nucl_data_obj);
  incoh_inela_calc_obj.set_opt_inelastic(opt_inelastic);
  incoh_inela_calc_obj.set_bin_no(bin_no);
  incoh_inela_calc_obj.set_atom_no(atom_no);
  incoh_inela_calc_obj.set_err(err);
  incoh_inela_calc_obj.set_ene_max(ene_max);
  incoh_inela_calc_obj.set_temp(temp);

  nucl_data_obj = incoh_inela_calc_obj.get_nucl_data_obj();
  incoh_inela_calc_obj.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterCalculator::calc_coherent_elastic_scatter()
{
  if( opt_elastic == coh_ela_calc_obj.no_calc )
  {
    return;
  }

  //If incoherent elastic scatter calculation is avallable,
  //coherent elastic scattering cross section calculation is skipped.
  if( (opt_elastic == incoh_ela_calc_obj.use_nucl_data     && elastic_scat_flg == 2 ) ||
       opt_elastic == incoh_ela_calc_obj.calc_polyethylene ||
       opt_elastic == incoh_ela_calc_obj.calc_h_in_zrh     ||
       opt_elastic == incoh_ela_calc_obj.calc_zr_in_zrh    )
  {
    return;
  }

  if( elastic_scat_flg != 1 && elastic_scat_flg != 3 )
  {
    string class_name = "ThermalScatterCalculator";
    string func_name  = "calc_coherent_elastic_scatter()";

    ostringstream oss01, oss02, oss03, oss04, oss05, oss06;
    oss01 << opt_elastic;
    oss02 << coh_ela_calc_obj.no_calc;
    oss03 << coh_ela_calc_obj.use_nucl_data;
    oss04 << coh_ela_calc_obj.calc_graphite;
    oss05 << coh_ela_calc_obj.calc_be;
    oss06 << coh_ela_calc_obj.calc_be_o;
    string str_data01 = "Elastic option " + oss01.str();
    string str_data02 = "Available elastic option";
    string str_data03 = "  Skip calculation : " + oss02.str();
    string str_data04 = "  Use nuclear data : " + oss03.str();
    string str_data05 = "  Glaphite         : " + oss04.str();
    string str_data06 = "  Beryllium        : " + oss05.str();
    string str_data07 = "  Beryllium oxide  : " + oss06.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back(str_data05);
    err_com.push_back(str_data06);
    err_com.push_back(str_data07);
    err_com.push_back("There is no coherent elastic calculation data in evaluated nuclear data file.");
    err_com.push_back("However, user set the elastic calculation option.");
    err_com.push_back("The calculation of coherent elastic scattering cross section may inappropriate");
    err_com.push_back("if user do not want to calculate above materials.");
    err_com.push_back("Please check your input file and evaluated nuclear data file.");
    err_obj.output_caution(class_name, func_name, err_com);
  }

  //Calculation of coherent elastic scatter cross section
  coh_ela_calc_obj.set_nucl_data_obj(nucl_data_obj);
  coh_ela_calc_obj.set_opt_elastic(opt_elastic);
  coh_ela_calc_obj.set_atom_no(atom_no);
  coh_ela_calc_obj.set_err(err);
  coh_ela_calc_obj.set_ene_max(ene_max);
  coh_ela_calc_obj.set_temp(temp);

  nucl_data_obj = coh_ela_calc_obj.get_nucl_data_obj();
  coh_ela_calc_obj.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterCalculator::calc_incoherent_elastic_scatter()
{
  if( opt_elastic == incoh_ela_calc_obj.no_calc )
  {
    return;
  }

  //If coherent elastic scatter calculation is avallable,
  //incoherent elastic scattering cross section calculation is skipped.
  if( (opt_elastic == coh_ela_calc_obj.use_nucl_data && elastic_scat_flg == 1 ) ||
       opt_elastic == coh_ela_calc_obj.calc_graphite ||
       opt_elastic == coh_ela_calc_obj.calc_be       ||
       opt_elastic == coh_ela_calc_obj.calc_be_o     )
  {
    return;
  }

  if( elastic_scat_flg != 2 && elastic_scat_flg != 3 )
  {
    string class_name = "ThermalScatterCalculator";
    string func_name  = "calc_incoherent_elastic_scatter()";

    ostringstream oss01, oss02, oss03, oss04, oss05, oss06;
    oss01 << opt_elastic;
    oss02 << incoh_ela_calc_obj.no_calc;
    oss03 << incoh_ela_calc_obj.use_nucl_data;
    oss04 << incoh_ela_calc_obj.calc_polyethylene;
    oss05 << incoh_ela_calc_obj.calc_h_in_zrh;
    oss06 << incoh_ela_calc_obj.calc_zr_in_zrh;
    string str_data01 = "Elastic option " + oss01.str();
    string str_data02 = "Available elastic option";
    string str_data03 = "  Skip calculation : " + oss02.str();
    string str_data04 = "  Use nuclear data : " + oss03.str();
    string str_data05 = "  Polyethylene     : " + oss04.str();
    string str_data06 = "  H in ZrH         : " + oss05.str();
    string str_data07 = "  Zr in ZrH        : " + oss06.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back(str_data05);
    err_com.push_back(str_data06);
    err_com.push_back(str_data07);
    err_com.push_back("There is no incoherent elastic calculation data in evaluated nuclear data file.");
    err_com.push_back("However, user set the elastic calculation option.");
    err_com.push_back("The calculation of incoherent elastic scattering cross section may inappropriate");
    err_com.push_back("if user do not want to calculate above materials.");
    err_com.push_back("Please check your input file and evaluated nuclear data file.");
    err_obj.output_caution(class_name, func_name, err_com);
  }

  //Calculation of incoherent elastic scatter cross section
  incoh_ela_calc_obj.set_nucl_data_obj(nucl_data_obj);
  incoh_ela_calc_obj.set_opt_elastic(opt_elastic);
  incoh_ela_calc_obj.set_bin_no(bin_no);
  incoh_ela_calc_obj.set_atom_no(atom_no);
  incoh_ela_calc_obj.set_ene_max(ene_max);
  incoh_ela_calc_obj.set_temp(temp);

  nucl_data_obj = incoh_ela_calc_obj.get_nucl_data_obj();
  incoh_ela_calc_obj.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterCalculator::check_opt_elastic()
{
  if( opt_elastic == coh_ela_calc_obj.no_calc )
  {
    return;
  }

  if( elastic_scat_flg == 1 || elastic_scat_flg == 3 )
  {
    //For coherent elastic scatter cross section
    if( opt_elastic == use_nucl_data_default )
    {
      opt_elastic = coh_ela_calc_obj.use_nucl_data;
    }
    else if( opt_elastic == coh_ela_calc_obj.calc_graphite ||
             opt_elastic == coh_ela_calc_obj.calc_be       ||
             opt_elastic == coh_ela_calc_obj.calc_be_o     )
    {
      opt_elastic = coh_ela_calc_obj.use_nucl_data;

      vector<string> err_com;
      ostringstream oss01, oss02, oss03, oss04, oss05, oss06;
      oss01 << opt_elastic;
      oss02 << use_nucl_data_default;
      oss03 << coh_ela_calc_obj.no_calc;
      oss04 << coh_ela_calc_obj.calc_graphite;
      oss05 << coh_ela_calc_obj.calc_be;
      oss06 << coh_ela_calc_obj.calc_be_o;
      string str_data01 = "Elastic option " + oss01.str();
      string str_data02 = "Available coherent elastic option";
      string str_data03 = "  Calculate using nuclear data : " + oss02.str();
      string str_data04 = "  No calculation               : " + oss03.str();
      string str_data05 = "  Glaphite                     : " + oss04.str();
      string str_data06 = "  Beryllium                    : " + oss05.str();
      string str_data07 = "  Beryllium oxide              : " + oss06.str();
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back(str_data04);
      err_com.push_back(str_data05);
      err_com.push_back(str_data06);
      err_com.push_back(str_data07);
      err_com.push_back("");
      err_com.push_back("Since thermal scatter data can be obtained from nuclear data,");
      err_com.push_back("FRENDY calculate coherent elastic thermal scatter cross section");
      err_com.push_back("using nuclear data.");

      string class_name = "ThermalScatterCalculator";
      string func_name  = "check_opt_elastic()";
      err_obj.output_caution(class_name, func_name, err_com);
    }
  }

  if( elastic_scat_flg == 2 || elastic_scat_flg == 3 )
  {
    //For coherent elastic scatter cross section
    if( opt_elastic == use_nucl_data_default )
    {
      opt_elastic = incoh_ela_calc_obj.use_nucl_data;
    }
    else if( opt_elastic == incoh_ela_calc_obj.calc_polyethylene ||
             opt_elastic == incoh_ela_calc_obj.calc_h_in_zrh     ||
             opt_elastic == incoh_ela_calc_obj.calc_zr_in_zrh    )
    {
      opt_elastic = incoh_ela_calc_obj.use_nucl_data;

      ostringstream oss01, oss02, oss03, oss04, oss05, oss06;
      oss01 << opt_elastic;
      oss02 << use_nucl_data_default;
      oss03 << incoh_ela_calc_obj.no_calc;
      oss04 << incoh_ela_calc_obj.calc_polyethylene;
      oss05 << incoh_ela_calc_obj.calc_h_in_zrh;
      oss06 << incoh_ela_calc_obj.calc_zr_in_zrh;
      string str_data01 = "Elastic option " + oss01.str();
      string str_data02 = "Available coherent elastic option";
      string str_data03 = "  Calculate using nuclear data : " + oss02.str();
      string str_data04 = "  No calculation               : " + oss03.str();
      string str_data05 = "  Polyethylene                 : " + oss04.str();
      string str_data06 = "  H  in ZrH                    : " + oss05.str();
      string str_data07 = "  Zr in ZrH                    : " + oss06.str();
      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back(str_data04);
      err_com.push_back(str_data05);
      err_com.push_back(str_data06);
      err_com.push_back(str_data07);
      err_com.push_back("");
      err_com.push_back("Since thermal scatter data can be obtained from nuclear data,");
      err_com.push_back("FRENDY calculate coherent elastic thermal scatter cross section");
      err_com.push_back("using nuclear data.");

      string class_name = "ThermalScatterCalculator";
      string func_name  = "check_opt_elastic()";
      err_obj.output_caution(class_name, func_name, err_com);
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterCalculator::check_set_data()
{
  vector<string> err_com;
  err_com.clear();

  if( opt_inelastic == 4 )
  {
    opt_inelastic = incoh_inela_calc_obj.use_nucl_data;
  }

  if( opt_inelastic != incoh_inela_calc_obj.use_nucl_data &&
      opt_inelastic != incoh_inela_calc_obj.no_calc       &&
      opt_inelastic != incoh_inela_calc_obj.free_gas_mode )
  {
    ostringstream oss01, oss02, oss03, oss04;
    oss01 << opt_inelastic;
    oss02 << incoh_inela_calc_obj.no_calc;
    oss03 << incoh_inela_calc_obj.free_gas_mode;
    oss04 << incoh_inela_calc_obj.use_nucl_data;
    string str_data01 = "Inelastic option : " + oss01.str();
    string str_data02 = "Inelastic option is not appropriate.";
    string str_data03 = "Available elastic option";
    string str_data04 = "  No calculation               : " + oss02.str();
    string str_data05 = "  Calculate as a free gas      : " + oss03.str();
    string str_data06 = "  Calculate using nuclear data : " + oss04.str();
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back(str_data05);
    err_com.push_back(str_data06);
  }

  if( opt_elastic != coh_ela_calc_obj.use_nucl_data       &&
      opt_elastic != coh_ela_calc_obj.no_calc             &&
      opt_elastic != coh_ela_calc_obj.calc_graphite       &&
      opt_elastic != coh_ela_calc_obj.calc_be             &&
      opt_elastic != coh_ela_calc_obj.calc_be_o           &&
      opt_elastic != incoh_ela_calc_obj.calc_polyethylene &&
      opt_elastic != incoh_ela_calc_obj.calc_h_in_zrh     &&
      opt_elastic != incoh_ela_calc_obj.calc_zr_in_zrh    )
  {
    ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07, oss08, oss09;
    oss01 << opt_elastic;
    oss02 << use_nucl_data_default;
    oss03 << coh_ela_calc_obj.no_calc;
    oss04 << coh_ela_calc_obj.calc_graphite;
    oss05 << coh_ela_calc_obj.calc_be;
    oss06 << coh_ela_calc_obj.calc_be_o;
    oss07 << incoh_ela_calc_obj.calc_polyethylene;
    oss08 << incoh_ela_calc_obj.calc_h_in_zrh;
    oss09 << incoh_ela_calc_obj.calc_zr_in_zrh;
    string str_data01 = "Elastic option " + oss01.str();
    string str_data02 = "Elastic option is not appropriate.";
    string str_data03 = "Available elastic option";
    string str_data04 = "  Calculate using nuclear data : " + oss02.str();
    string str_data05 = "  No calculation               : " + oss03.str();
    string str_data06 = "  Glaphite                     : " + oss04.str();
    string str_data07 = "  Beryllium                    : " + oss05.str();
    string str_data08 = "  Beryllium oxide              : " + oss06.str();
    string str_data09 = "  Polyethylene                 : " + oss07.str();
    string str_data10 = "  H  in ZrH                    : " + oss08.str();
    string str_data11 = "  Zr in ZrH                    : " + oss09.str();
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back(str_data05);
    err_com.push_back(str_data06);
    err_com.push_back(str_data07);
    err_com.push_back(str_data08);
    err_com.push_back(str_data09);
    err_com.push_back(str_data10);
    err_com.push_back(str_data11);
  }

  if( bin_no <= 0 )
  {
    ostringstream oss01;
    oss01 << bin_no;
    string str_data01 = "Bin number : " + oss01.str();
    err_com.push_back(str_data01);
    err_com.push_back("Bin number is not input or set inappropriate value.");
  }

  if( atom_no < min_value )
  {
    ostringstream oss01;
    oss01 << atom_no;
    string str_data01 = "Atom number : " + oss01.str();
    err_com.push_back(str_data01);
    err_com.push_back("Atom number is not input or set inappropriate value.");
  }

  if( err < min_value )
  {
    ostringstream oss01;
    oss01 << err;
    string str_data01 = "Error value : " + oss01.str();
    err_com.push_back(str_data01);
    err_com.push_back("Error value is not input or set inappropriate value.");
  }

  if( ene_max < min_value )
  {
    ostringstream oss01;
    oss01 << ene_max;
    string str_data01 = "Maximum energy : " + oss01.str();
    err_com.push_back(str_data01);
    err_com.push_back("Maximum energy is not input or set inappropriate value.");
  }

  if( temp < min_value )
  {
    ostringstream oss01;
    oss01 << temp;
    string str_data01 = "Temperature : " + oss01.str();
    err_com.push_back(str_data01);
    err_com.push_back("Temperature is not input or set inappropriate value.");
  }

  if( static_cast<int>(err_com.size()) > 0 )
  {
    string class_name = "ThermalScatterCalculator";
    string func_name  = "check_set_data()";
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  Real max_thermal_ene_endf = get_max_thermal_ene_endf();
  if( max_thermal_ene_endf > 0.0 )
  {
    if( fabs((max_thermal_ene_endf - ene_max) / ene_max) < 0.01 )
    {
      //skip output
    }
    else
    {
      string class_name = "ThermalScatterCalculator";
      string func_name  = "check_set_data()";

      ostringstream oss01, oss02;
      oss01.precision(8);
      oss01.setf(ios::showpoint);
      oss02.precision(8);
      oss02.setf(ios::showpoint);

      oss01 << max_thermal_ene_endf;
      oss02 << ene_max;

      string str_data01 = "Maximium energy from nuclear data file : " + oss01.str();
      string str_data02 = "Maximium energy in this calculation    : " + oss02.str();

      err_com.push_back(str_data01);
      err_com.push_back(str_data02);

      FrendyInputCommonUtils inp_obj_def;
      Real ene_max_def = inp_obj_def.get_max_thermal_ene_in_def();

      if( max_thermal_ene_endf > ene_max )
      {
        err_com.push_back("Maximum energy in this calculation is less than");
        err_com.push_back("that from the evaluated nuclear data file.");
        err_com.push_back("This calculation may not be appropriate.");
        err_obj.output_caution(class_name, func_name, err_com);
      }
      else if( ene_max > max_thermal_ene_endf && ene_max > ene_max_def )
      {
        ostringstream oss03;
        oss03 << ene_max_def;
        string str_data03 = "upper limit of energy (" + oss03.str() +").";

        err_com.push_back("Maximum energy in this calculation is larger than");
        err_com.push_back("that from the evaluated nuclear data file and");
        err_com.push_back(str_data03);
        err_com.push_back("This calculation may not be appropriate.");
        err_obj.output_caution(class_name, func_name, err_com);
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterCalculator::output_set_data_information()
{
  cout << "=== Nuclear data information ===" << endl;
  cout << "  Material No.       : " << nucl_data_obj.get_general_data_obj().get_mat_no()      << endl;
  cout << "  Material Data (ZA) : " << nucl_data_obj.get_general_data_obj().get_mat_data()    << endl;
  cout << "  Mass               : " << nucl_data_obj.get_general_data_obj().get_mass()        << endl;
  cout << "  Temperature        : " << nucl_data_obj.get_general_data_obj().get_temp()        << endl;
  cout << "  Error              : " << nucl_data_obj.get_general_data_obj().get_error_value() << endl;
  cout << endl;
  cout << "=== Set data information ===" << endl;
  cout << "  Inelastic Option     : " << opt_inelastic << endl;
  cout << "  Elastic Option       : " << opt_elastic   << endl;
  cout << "  Bin No.              : " << bin_no        << endl;
  cout << "  Atom No.             : " << atom_no       << endl;
  cout << "  Maximum Energy       : " << ene_max       << endl;
  cout << "  Temperature          : " << temp          << endl;
  cout << "  Error                : " << err           << endl;
  cout << endl;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Real ThermalScatterCalculator::get_max_thermal_ene_endf()
{
  vector<Real> b_vec = nucl_data_obj.get_thermal_scat_data_obj().get_inelastic_scat_law_coef();

  Real max_thermal_ene_endf = -1.0;
  if( static_cast<int>(b_vec.size()) > 4 )
  {
    max_thermal_ene_endf = b_vec[3]; //B(4) : Emax
  }

  return max_thermal_ene_endf;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//Setter

void ThermalScatterCalculator::set_nucl_data_name(string& str_data)
{
  calc_thermal_scat_flg = 0;
  nucl_data_name        = str_data;

  Endf6Parser       endf_parser_obj;
  Endf6Converter    conv_obj;
  NuclearDataObject data_obj;

  endf_parser_obj.set_file_name(nucl_data_name);
  conv_obj.convert_endf_format_to_frendy(endf_parser_obj, data_obj);

  set_nucl_data_obj(data_obj);
  data_obj.clear();
}

void ThermalScatterCalculator::set_nucl_data_obj(NuclearDataObject& data_obj)
{
  calc_thermal_scat_flg = 0;
  nucl_data_set_flg     = 1;

  nucl_data_obj = data_obj;

  elastic_scat_flg = nucl_data_obj.get_thermal_scat_data_obj().get_elastic_scat_flg();

  Integer err_chk = 0;
  if( elastic_scat_flg == 0 )
  {
    ThermalScatterDataContainer th_obj = nucl_data_obj.get_thermal_scat_data_obj();
    if( static_cast<int>(th_obj.get_elastic_structure_factor_data_base().size())  != 0 ||
        static_cast<int>(th_obj.get_elastic_structure_factor_ene_data().size())   != 0 ||
        static_cast<int>(th_obj.get_elastic_structure_factor_range_data().size()) != 0 ||
        static_cast<int>(th_obj.get_elastic_structure_factor_int_data().size())   != 0 ||
        static_cast<int>(th_obj.get_elastic_structure_factor_data().size())       != 0 ||
        static_cast<int>(th_obj.get_elastic_debye_waller_data().size())           != 0 ||
        static_cast<int>(th_obj.get_elastic_debye_waller_temp_data().size())      != 0 ||
        static_cast<int>(th_obj.get_elastic_debye_waller_range_data().size())     != 0 ||
        static_cast<int>(th_obj.get_elastic_debye_waller_int_data().size())       != 0 )
    {
      err_chk = 1;
    }
  }
  else if( elastic_scat_flg != 1 && elastic_scat_flg != 2 && elastic_scat_flg != 3 )
  {
    err_chk = 2;
  }

  if( err_chk != 0 )
  {
    ostringstream oss01;
    oss01 << elastic_scat_flg;
    string str_data01 = "Elastic scattering representation flag : " + oss01.str();
    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("Elastic scattering representation flag is not appropriate.");
    err_com.push_back("Available elastic scattering representation flag");
    err_com.push_back("  Thermal data for coherent elastic scattering   : 1");
    err_com.push_back("  Thermal data for incoherent elastic scattering : 2");
    string class_name = "ThermalScatterCalculator";
    string func_name  = "set_nucl_data_obj(NuclearDataObject& data_obj)";
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

void ThermalScatterCalculator::set_opt_inelastic(Integer int_data)
{
  calc_thermal_scat_flg = 0;
  opt_inelastic         = int_data;
}

void ThermalScatterCalculator::set_opt_elastic(Integer int_data)
{
  calc_thermal_scat_flg = 0;
  opt_elastic           = int_data;
}

void ThermalScatterCalculator::set_bin_no(Integer int_data)
{
  calc_thermal_scat_flg = 0;
  bin_no                = int_data;
}

void ThermalScatterCalculator::set_atom_no(Integer int_data)
{
  calc_thermal_scat_flg = 0;
  atom_no               = int_data;
}

void ThermalScatterCalculator::set_err(Real8 real_data)
{
  calc_thermal_scat_flg = 0;
  err                   = real_data;
}

void ThermalScatterCalculator::set_ene_max(Real8 real_data)
{
  calc_thermal_scat_flg = 0;
  ene_max               = real_data;
}

void ThermalScatterCalculator::set_temp(Real8 real_data)
{
  calc_thermal_scat_flg = 0;
  temp                  = real_data;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//Getter

string ThermalScatterCalculator::get_nucl_data_name()
{
  return nucl_data_name;
}

NuclearDataObject ThermalScatterCalculator::get_nucl_data_obj()
{
  calc_thermal_scatter();

  return nucl_data_obj;
}

Integer ThermalScatterCalculator::get_opt_inelastic()
{
  return opt_inelastic;
}

Integer ThermalScatterCalculator::get_opt_elastic()
{
  return opt_elastic;
}

Integer ThermalScatterCalculator::get_bin_no()
{
  return bin_no;
}

Integer ThermalScatterCalculator::get_atom_no()
{
  return atom_no;
}

Real8 ThermalScatterCalculator::get_err()
{
  return err;
}

Real8 ThermalScatterCalculator::get_ene_max()
{
  return ene_max;
}

Real8 ThermalScatterCalculator::get_temp()
{
  return temp;
}

