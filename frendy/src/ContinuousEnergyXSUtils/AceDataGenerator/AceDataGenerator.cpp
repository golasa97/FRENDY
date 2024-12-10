#include "ContinuousEnergyXSUtils/AceDataGenerator/AceDataGenerator.hpp"

using namespace frendy;

//constructor
AceDataGenerator::AceDataGenerator(void)
{
  clear();
}

//destructor
AceDataGenerator::~AceDataGenerator(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

const int AceDataGenerator::generate_default_mode;
const int AceDataGenerator::generate_njoy_mode;

const int AceDataGenerator::write_ace;
const int AceDataGenerator::skip_write_ace;

const int AceDataGenerator::fast_mode;
const int AceDataGenerator::thermal_mode;
const int AceDataGenerator::dosimetry_mode;

////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataGenerator::clear()
{
  fast_ace_obj.clear();
  thermal_scat_ace_obj.clear();

  generate_ace_data_flg = 0;
  nucl_data_set_flg     = 0;

  ace_data_obj.clear();

  nucl_data_obj.clear();
  nucl_data_name.clear();

  //For input data (Common)
  ace_file_name.clear();
  mcnp_dir.clear();
  discriptive_data.clear();
  opt_run        = 0;
  mcnpx_mode_flg = 0;
  opt_print      = 1;
  opt_out_type   = 1;
  temp           = 0.0;
  suffix_za_id   = 0.0;
  zi_vec.clear();
  awr_vec.clear();

  //For input data (Fast)
  mat                             = 0;
  new_cummulative_angle_distr_flg = 1;
  detailed_photon_flg             = 1;
  thinning_ene.clear();

  //For input data (Thermal scattering)
  thermal_za_id_name.clear();
  mt_inelastic = 0;
  bin_no       = 0;
  mt_elastic   = 0;
  elastic_flg  = 0;
  atom_no_th   = 0;
  opt_weight   = 0;
  ene_max_th   = 0.0;
  mod_za.clear();

  generate_mode_flg = generate_default_mode;
#ifdef NJOY_MODE
  generate_mode_flg = generate_njoy_mode;
#endif //NJOY_MODE

  fast_ace_obj.set_generate_mode_flg(generate_mode_flg);

  write_ace_flg = write_ace;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataGenerator::generate_ace_data()
{
  if( generate_ace_data_flg != 0 )
  {
    return;
  }
  generate_ace_data_flg = 1;

  if( nucl_data_set_flg == 0 )
  {
    string class_name = "AceDataGenerator";
    string func_name  = "generate_ace_data()";

    vector<string> err_com;
    err_com.push_back("There is no nuclear data object.");
    err_com.push_back("Please set the nuclear data object or nuclear data name.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  if( opt_run == 1 )
  {
    output_set_data_information_fast();
    generate_ace_data_fast();
  }
  else if( opt_run == 2 )
  {
    output_set_data_information_thermal();
    generate_ace_data_thermal();
  }
  else if( opt_run == 3 )
  {
    output_set_data_information_dosimetry();
    generate_ace_data_dosimetry();
  }
  else
  {
    string class_name = "AceDataGenerator";
    string func_name  = "generate_ace_data()";

    ostringstream oss;
    oss << opt_run;
    string str_data = "Run option : " + oss.str();

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("This run option is not available in this program.");
    err_com.push_back("Available run option is 1 (fast), 2 (thermal scatter) and 3 (dosimetry).");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataGenerator::output_set_data_information_common()
{
  cout << "=== Nuclear data information ===" << endl;
  cout << "  Material No.       : " << nucl_data_obj.get_general_data_obj().get_mat_no()      << endl;
  cout << "  Material Data (ZA) : " << nucl_data_obj.get_general_data_obj().get_mat_data()    << endl;
  cout << "  Mass               : " << nucl_data_obj.get_general_data_obj().get_mass()        << endl;
  cout << "  Temperature        : " << nucl_data_obj.get_general_data_obj().get_temp()        << endl;
  cout << "  Error              : " << nucl_data_obj.get_general_data_obj().get_error_value() << endl;
  cout << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataGenerator::output_set_data_information_fast()
{
  output_set_data_information_common();

  cout << "=== Set data information ===" << endl;
  cout << "  Material data               : " << mat          << endl;
  cout << "  Temperature                 : " << temp         << endl;
  cout << "  Cummulative angle option    : " << new_cummulative_angle_distr_flg << " (0:no, 1:yes)" << endl;
  cout << "  Detailed photon option      : " << detailed_photon_flg             << " (0:no, 1:yes)" << endl;
  if( static_cast<int>(thinning_ene.size()) > 0 )
  {
    cout << "  Thinning energy option" << endl;
    cout << "    thin(1)                   : " << thinning_ene[0] << endl;
    cout << "    thin(2)                   : " << thinning_ene[1] << endl;
    cout << "    thin(3)                   : " << thinning_ene[2] << endl;
  }
  cout << endl;

  cout << "=== Set output information ===" << endl;
  cout << "  ACE file name               : " << ace_file_name      << endl;
  cout << "  Output type                 : " << opt_out_type       << endl;
  cout << "  Suffix ID for ACE file      : " << suffix_za_id       << endl;
  cout << "  IZ, AWR pair No.            : " << zi_vec.size()      << endl;
  for(int i=0; i<static_cast<int>(zi_vec.size()); i++)
  {
    cout << "    IZ, AWR                   : " << zi_vec[i] << ", " << awr_vec[i] << endl;
  }
  if( static_cast<int>(discriptive_data.size()) > 0 )
  {
    cout << "  Description                 : " << discriptive_data << endl;
  }
  cout << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataGenerator::output_set_data_information_thermal()
{
  output_set_data_information_common();

  cout << "=== Set data information ===" << endl;
  cout << "  Material data               : " << mat          << endl;
  cout << "  Temperature                 : " << temp         << endl;
  cout << "  Inelastic MT No.            : " << mt_inelastic << endl;
  cout << "  Elastic MT No.              : " << mt_elastic   << endl;
  cout << "  Bin No.                     : " << bin_no       << endl;
  cout << "  Elastic option              : " << elastic_flg  << " (0:coherent, 1:incoherent, 2: mixed)" << endl;
  cout << "  Atom No. in mixed moderator : " << atom_no_th   << endl;
  cout << "  Maximum energy              : " << ene_max_th   << endl;
  cout << "  Weighting option            : " << opt_weight   << endl;
  cout << endl;

  cout << "=== Set output information ===" << endl;
  cout << "  ACE file name               : " << ace_file_name      << endl;
  cout << "  Output type                 : " << opt_out_type       << endl;
  cout << "  ZAID name (TSL)             : " << thermal_za_id_name << endl;
  cout << "  Suffix ID for ACE file      : " << suffix_za_id       << endl;
  cout << "  IZ, AWR pair No.            : " << zi_vec.size()      << endl;
  for(int i=0; i<static_cast<int>(zi_vec.size()); i++)
  {
    cout << "    IZ, AWR                   : " << zi_vec[i] << ", " << awr_vec[i] << endl;
  }
  cout << "  Moderator component No.     : " << mod_za.size() << endl;
  for(int i=0; i<static_cast<int>(mod_za.size()); i++)
  {
    cout << "    Moderator component       : " << mod_za[i] << endl;
  }
  if( static_cast<int>(discriptive_data.size()) > 0 )
  {
    cout << "  Description                 : " << discriptive_data << endl;
  }
  cout << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataGenerator::output_set_data_information_dosimetry()
{
  output_set_data_information_common();

  cout << "=== Set data information ===" << endl;
  cout << "  Material data               : " << mat          << endl;
  cout << "  Temperature                 : " << temp         << endl;
  cout << endl;

  cout << "=== Set output information ===" << endl;
  cout << "  ACE file name               : " << ace_file_name      << endl;
  cout << "  Output type                 : " << opt_out_type       << endl;
  cout << "  Suffix ID for ACE file      : " << suffix_za_id       << endl;
  cout << "  IZ, AWR pair No.            : " << zi_vec.size()      << endl;
  for(int i=0; i<static_cast<int>(zi_vec.size()); i++)
  {
    cout << "    IZ, AWR                   : " << zi_vec[i] << ", " << awr_vec[i] << endl;
  }
  if( static_cast<int>(discriptive_data.size()) > 0 )
  {
    cout << "  Description                 : " << discriptive_data << endl;
  }
  cout << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataGenerator::generate_ace_data_fast()
{
  //Set input data for FastAceDataGenerator object
  fast_ace_obj.set_nucl_data_obj(nucl_data_obj);

  fast_ace_obj.set_mat(mat);
  fast_ace_obj.set_temp(temp);
  fast_ace_obj.set_new_cummulative_angle_distr_flg(new_cummulative_angle_distr_flg);
  fast_ace_obj.set_detailed_photon_flg(detailed_photon_flg);
  fast_ace_obj.set_thinning_ene(thinning_ene);

  fast_ace_obj.set_suffix_za_id(suffix_za_id);
  fast_ace_obj.set_zi_awr_pair(zi_vec, awr_vec);

  fast_ace_obj.set_mcnpx_mode_flg(mcnpx_mode_flg);
  fast_ace_obj.set_discriptive_data(discriptive_data);

  //Running FastAceDataGenerator object
  fast_ace_obj.generate_ace_data();

  FastAceDataObject fast_ace_data_obj = fast_ace_obj.get_ace_data_obj();

  if( write_ace_flg == write_ace )
  {
    //Write calculation retsults with ACE format
    FastAceDataWriter ace_wri_obj;
    ace_wri_obj.set_ace_data_obj(fast_ace_data_obj);
    ace_wri_obj.set_opt_out_type(opt_out_type);
    ace_wri_obj.set_new_cummulative_angle_distr_flg(new_cummulative_angle_distr_flg);
    ace_wri_obj.set_detailed_photon_flg(detailed_photon_flg);
    ace_wri_obj.set_ace_file_name(ace_file_name);
    ace_wri_obj.write_ace_format();

    //Write directory data
    ace_wri_obj.write_dir_data(mcnp_dir);
    ace_wri_obj.clear();
  }

  ace_data_obj.set_fast_ace_data_obj(fast_ace_data_obj);
  fast_ace_data_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataGenerator::generate_ace_data_thermal()
{
  //Set input data for ThermalScatterAceDataGenerator object
  thermal_scat_ace_obj.set_nucl_data_obj(nucl_data_obj);

  thermal_scat_ace_obj.set_mat(mat);
  thermal_scat_ace_obj.set_temp(temp);
  thermal_scat_ace_obj.set_mt_inelastic(mt_inelastic);
  thermal_scat_ace_obj.set_bin_no(bin_no);
  thermal_scat_ace_obj.set_mt_elastic(mt_elastic);
  thermal_scat_ace_obj.set_elastic_flg(elastic_flg);
  thermal_scat_ace_obj.set_atom_no_th(atom_no_th);
  thermal_scat_ace_obj.set_opt_weight(opt_weight);
  thermal_scat_ace_obj.set_suffix_za_id(suffix_za_id);
  thermal_scat_ace_obj.set_ene_max_th(ene_max_th);
  thermal_scat_ace_obj.set_zi_awr_pair(zi_vec, awr_vec);
  thermal_scat_ace_obj.set_mod_za(mod_za);
  thermal_scat_ace_obj.set_thermal_za_id_name(thermal_za_id_name);

  thermal_scat_ace_obj.set_mcnpx_mode_flg(mcnpx_mode_flg);
  thermal_scat_ace_obj.set_discriptive_data(discriptive_data);

  //Running ThermalScatterAceDataGenerator object
  thermal_scat_ace_obj.generate_ace_data();

  ThermalScatterAceDataObject thermal_scat_ace_data_obj = thermal_scat_ace_obj.get_ace_data_obj();

  if( write_ace_flg == write_ace )
  {
    //Write calculation retsults with ACE format
    ThermalScatterAceDataWriter ace_wri_obj;
    ace_wri_obj.set_ace_data_obj(thermal_scat_ace_data_obj);
    ace_wri_obj.set_opt_out_type(opt_out_type);
    ace_wri_obj.set_opt_weight(opt_weight);
    ace_wri_obj.set_ace_file_name(ace_file_name);
    ace_wri_obj.write_ace_format();

    //Write directory data
    ace_wri_obj.write_dir_data(mcnp_dir);
    ace_wri_obj.clear();
  }

  ace_data_obj.set_thermal_scat_ace_data_obj(thermal_scat_ace_data_obj);
  thermal_scat_ace_data_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataGenerator::generate_ace_data_dosimetry()
{
  //Set input data for DosimetryAceDataGenerator object
  dosimetry_ace_obj.set_nucl_data_obj(nucl_data_obj);

  dosimetry_ace_obj.set_mat(mat);
  dosimetry_ace_obj.set_temp(temp);
  dosimetry_ace_obj.set_suffix_za_id(suffix_za_id);
  dosimetry_ace_obj.set_zi_awr_pair(zi_vec, awr_vec);

  dosimetry_ace_obj.set_mcnpx_mode_flg(mcnpx_mode_flg);
  dosimetry_ace_obj.set_discriptive_data(discriptive_data);

  //Running DosimetryAceDataGenerator object
  dosimetry_ace_obj.generate_ace_data();

  DosimetryAceDataObject dosimetry_ace_data_obj = dosimetry_ace_obj.get_ace_data_obj();

  if( write_ace_flg == write_ace )
  {
    //Write calculation retsults with ACE format
    DosimetryAceDataWriter ace_wri_obj;
    ace_wri_obj.set_ace_data_obj(dosimetry_ace_data_obj);
    ace_wri_obj.set_opt_out_type(opt_out_type);
    ace_wri_obj.set_ace_file_name(ace_file_name);
    ace_wri_obj.write_ace_format();

    //Write directory data
    ace_wri_obj.write_dir_data(mcnp_dir);
    ace_wri_obj.clear();
  }

  ace_data_obj.set_dosimetry_ace_data_obj(dosimetry_ace_data_obj);
  dosimetry_ace_data_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//Setter

void AceDataGenerator::set_nucl_data_name(string str_data)
{
  generate_ace_data_flg = 0;
  nucl_data_set_flg     = 1;
  nucl_data_name        = str_data;
  str_data.clear();

  Endf6Parser       endf_parser_obj;
  Endf6Converter    conv_obj;
  NuclearDataObject data_obj;

  endf_parser_obj.set_file_name(nucl_data_name);
  conv_obj.convert_endf_format_to_frendy(endf_parser_obj, data_obj);

  set_nucl_data_obj(data_obj);
  data_obj.clear();
}

void AceDataGenerator::set_nucl_data_obj(NuclearDataObject& data_obj)
{
  generate_ace_data_flg = 0;
  nucl_data_set_flg     = 1;

  nucl_data_obj = data_obj;

  //Modifying MT numbers from ENDF-5 to ENDF-6
  nucl_data_obj.modify_mt_no_for_endf5();
}

void AceDataGenerator::set_ace_file_name(string str_data)
{
  generate_ace_data_flg = 0;

  ace_file_name = str_data;
  str_data.clear();
}

void AceDataGenerator::set_mcnp_dir(string str_data)
{
  generate_ace_data_flg = 0;

  mcnp_dir = str_data;
  str_data.clear();
}

void AceDataGenerator::set_discriptive_data(string str_data)
{
  generate_ace_data_flg = 0;

  discriptive_data = str_data;
  str_data.clear();
}

void AceDataGenerator::set_opt_run(Integer int_data)
{
  generate_ace_data_flg = 0;

  opt_run = int_data;
}

void AceDataGenerator::set_mcnpx_mode_flg(Integer int_data)
{
  generate_ace_data_flg = 0;

  mcnpx_mode_flg = int_data;
}

void AceDataGenerator::set_opt_print(Integer int_data)
{
  generate_ace_data_flg = 0;

  opt_print = int_data;
}

void AceDataGenerator::set_opt_out_type(Integer int_data)
{
  generate_ace_data_flg = 0;

  opt_out_type = int_data;
}

void AceDataGenerator::set_mat(Integer int_data)
{
  generate_ace_data_flg = 0;

  mat = int_data;
}

void AceDataGenerator::set_temp(Real real_data)
{
  generate_ace_data_flg = 0;

  temp = real_data;
}

void AceDataGenerator::set_suffix_za_id(Real real_data)
{
  generate_ace_data_flg = 0;

  suffix_za_id = real_data;

  int mod_flg = 0;
  if( suffix_za_id > 0.999999 )
  {
    mod_flg = 1;
    suffix_za_id /= 100.0;
  }

  if( suffix_za_id > 1.0 )
  {
    ostringstream oss01;
    oss01 << setw(8) << std::showpoint << real_data;

    string class_name = "AceDataGenerator";
    string func_name  = "set_suffix_za_id(Real real_data)";
    string str_data01 = "Suffix ID for ACE file : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("The suffix ID is 0.00 - 0.99 or 0 - 99.");
    err_com.push_back("This suffix ID may not be correct.");
    err_obj.output_caution(class_name, func_name, err_com);
  }
  else if( mod_flg > 0 )
  {
    ostringstream oss01, oss02;
    oss01 << setw(8) << std::showpoint << real_data;
    oss02 << setw(8) << std::showpoint << suffix_za_id;

    string class_name = "AceDataGenerator";
    string func_name  = "set_suffix_za_id(Real real_data)";
    string str_data01 = "Suffix ID (from input file) : " + oss01.str();
    string str_data02 = "Suffix ID (modified)        : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("The suffix ID is larger than 1.0.");
    err_com.push_back("The suffix ID is modified.");
    err_com.push_back("");
    err_com.push_back("Please check suffix_id in FRENDY input format or suff in NJOY/ACER card 2.");
    err_obj.output_caution(class_name, func_name, err_com);
  }
}

void AceDataGenerator::set_zi_vec(vector<Integer> int_vec)
{
  generate_ace_data_flg = 0;

  zi_vec = int_vec;
  int_vec.clear();
}

void AceDataGenerator::set_awr_vec(vector<Real> real_vec)
{
  generate_ace_data_flg = 0;

  awr_vec = real_vec;
  real_vec.clear();
}

void AceDataGenerator::set_new_cummulative_angle_distr_flg(Integer int_data)
{
  generate_ace_data_flg = 0;

  new_cummulative_angle_distr_flg = int_data;
}

void AceDataGenerator::set_detailed_photon_flg(Integer int_data)
{
  generate_ace_data_flg = 0;

  detailed_photon_flg = int_data;
}

void AceDataGenerator::set_thinning_ene(vector<Real> real_vec)
{
  generate_ace_data_flg = 0;

  thinning_ene = real_vec;
  real_vec.clear();
}

void AceDataGenerator::set_thermal_za_id_name(string str_data)
{
  generate_ace_data_flg = 0;

  thermal_za_id_name = str_data;
  str_data.clear();
}

void AceDataGenerator::set_mt_inelastic(Integer int_data)
{
  generate_ace_data_flg = 0;

  mt_inelastic = int_data;
}

void AceDataGenerator::set_bin_no(Integer int_data)
{
  generate_ace_data_flg = 0;

  bin_no = int_data;
}

void AceDataGenerator::set_mt_elastic(Integer int_data)
{
  generate_ace_data_flg = 0;

  mt_elastic = int_data;
}

void AceDataGenerator::set_elastic_flg(Integer int_data)
{
  generate_ace_data_flg = 0;

  elastic_flg = int_data;
}

void AceDataGenerator::set_atom_no_th(Integer int_data)
{
  generate_ace_data_flg = 0;

  atom_no_th = int_data;
}

void AceDataGenerator::set_opt_weight(Integer int_data)
{
  generate_ace_data_flg = 0;

  opt_weight = int_data;
}

void AceDataGenerator::set_ene_max_th(Real real_data)
{
  generate_ace_data_flg = 0;

  ene_max_th = real_data;
}

void AceDataGenerator::set_mod_za(vector<Integer> int_vec)
{
  generate_ace_data_flg = 0;

  mod_za = int_vec;
  int_vec.clear();
}

void AceDataGenerator::set_generate_mode_flg(int int_val)
{
  generate_ace_data_flg  = 0;
  generate_mode_flg      = int_val;

  if( generate_mode_flg != generate_default_mode && generate_mode_flg != generate_njoy_mode )
  {
    string class_name = "AceDataGenerator";
    string func_name  = "set_generate_mode_flg(int int_val)";
    ostringstream oss01;
    oss01 << generate_mode_flg;
    string str_data01 = "The generate_mode_flg : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("This generate_mode_flg is not available.");
    err_com.push_back("The generate_mode_flg is only available for generate_default_mode (0) or");
    err_com.push_back("generate_njoy_mode (1).");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  fast_ace_obj.set_generate_mode_flg(generate_mode_flg);
}

void AceDataGenerator::set_write_ace_flg(int int_val)
{
  generate_ace_data_flg  = 0;
  write_ace_flg          = int_val;

  if( write_ace_flg != write_ace && write_ace_flg != skip_write_ace )
  {
    string class_name = "AceDataGenerator";
    string func_name  = "set_write_ace_flg(int int_val)";
    ostringstream oss01;
    oss01 << write_ace_flg;
    string str_data01 = "The write_ace_flg : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("This write_ace_flg is not available.");
    err_com.push_back("The write_ace_flg is only available for write_ace (0) or");
    err_com.push_back("skip_write_ace (1).");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}



////////////////////////////////////////////////////////////////////////////////////////////////////
//Getter
AceDataObject AceDataGenerator::get_ace_data_obj()
{
  generate_ace_data();
  return ace_data_obj;
}

string AceDataGenerator::get_nucl_data_name()
{
  return nucl_data_name;
}

NuclearDataObject AceDataGenerator::get_nucl_data_obj()
{
  return nucl_data_obj;
}

string          AceDataGenerator::get_ace_file_name()
{
  return ace_file_name;
}

string          AceDataGenerator::get_mcnp_dir()
{
  return mcnp_dir;
}

string          AceDataGenerator::get_discriptive_data()
{
  return discriptive_data;
}

Integer         AceDataGenerator::get_opt_run()
{
  return opt_run;
}

Integer         AceDataGenerator::get_mcnpx_mode_flg()
{
  return mcnpx_mode_flg;
}

Integer         AceDataGenerator::get_opt_print()
{
  return opt_print;
}

Integer         AceDataGenerator::get_opt_out_type()
{
  return opt_out_type;
}

Integer         AceDataGenerator::get_mat()
{
  return mat;
}

Real            AceDataGenerator::get_temp()
{
  return temp;
}

Real            AceDataGenerator::get_suffix_za_id()
{
  return suffix_za_id;
}

vector<Integer> AceDataGenerator::get_zi_vec()
{
  return zi_vec;
}

vector<Real>    AceDataGenerator::get_awr_vec()
{
  return awr_vec;
}

Integer         AceDataGenerator::get_new_cummulative_angle_distr_flg()
{
  return new_cummulative_angle_distr_flg;
}

Integer         AceDataGenerator::get_detailed_photon_flg()
{
  return detailed_photon_flg;
}

vector<Real>    AceDataGenerator::get_thinning_ene()
{
  return thinning_ene;
}

string          AceDataGenerator::get_thermal_za_id_name()
{
  return thermal_za_id_name;
}

Integer         AceDataGenerator::get_mt_inelastic()
{
  return mt_inelastic;
}

Integer         AceDataGenerator::get_bin_no()
{
  return bin_no;
}

Integer         AceDataGenerator::get_mt_elastic()
{
  return mt_elastic;
}

Integer         AceDataGenerator::get_elastic_flg()
{
  return elastic_flg;
}

Integer         AceDataGenerator::get_atom_no_th()
{
  return atom_no_th;
}

Integer         AceDataGenerator::get_opt_weight()
{
  return opt_weight;
}

Real            AceDataGenerator::get_ene_max_th()
{
  return ene_max_th;
}

vector<Integer> AceDataGenerator::get_mod_za()
{
  return mod_za;
}

int             AceDataGenerator::get_generate_mode_flg()
{
  return generate_mode_flg;
}

int             AceDataGenerator::get_write_ace_flg()
{
  return write_ace_flg;
}

