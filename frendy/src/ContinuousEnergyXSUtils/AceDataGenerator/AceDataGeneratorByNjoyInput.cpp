#include "ContinuousEnergyXSUtils/AceDataGenerator/AceDataGeneratorByNjoyInput.hpp"

using namespace frendy;

//constructor
AceDataGeneratorByNjoyInput::AceDataGeneratorByNjoyInput(void)
{
  clear();
}

//destructor
AceDataGeneratorByNjoyInput::~AceDataGeneratorByNjoyInput(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataGeneratorByNjoyInput::clear()
{
  calc_flg   = 0;
  time_total = 0;

  ace_obj.clear();

  input_file_name_njoy.clear();
  start_line_no = 0;

  endf_name.clear();
  pendf_name.clear();
  gendf_name.clear();

  opt_run = 0;
  mat     = -1;
  temp    = -1.0;

  generate_mode_flg = ace_obj.get_generate_mode_flg();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataGeneratorByNjoyInput::generate_ace_data()
{
  if( calc_flg == 1 )
  {
    return;
  }
  calc_flg = 1;

  cout << "************************************* Ace file generation *************************************";
  cout << endl << endl;
  time_obj.output_current_time();

  boost::timer::cpu_timer timer_total;

  set_input_data();
  output_input_file_name();

  set_nucl_data_obj_all();
  ace_obj.set_generate_mode_flg(generate_mode_flg);
  ace_obj.generate_ace_data();

  time_total = static_cast<Integer>(timer_total.elapsed().wall * 1.0E-9);
  cout << "Total calculation time : " << time_total << " [s]" << endl;
  cout << endl;
  cout << "***********************************************************************************************";
  cout << endl << endl;

  ace_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataGeneratorByNjoyInput::output_input_file_name()
{
  cout << "=== Nuclear data file information ===" << endl;
  cout << "  Input File Name          : " << input_file_name_njoy << endl;
  cout << "  ENDF  File Name          : " << endf_name            << endl;
  cout << "  PENDF File Name          : " << pendf_name           << endl;
  cout << "  GENDF File Name          : " << gendf_name           << endl;
  cout << "  Material Number          : " << mat                  << endl;
  cout << "  Temperature data         : " << temp                 << endl;
  cout << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataGeneratorByNjoyInput::set_input_data()
{
  //Read acer input file
  AcerInputReader read_njoy_obj;
  read_njoy_obj.read_input(input_file_name_njoy, start_line_no);

  endf_name  = read_njoy_obj.get_endf_name();
  pendf_name = read_njoy_obj.get_pendf_name();
  gendf_name = read_njoy_obj.get_gendf_name();

  mat     = read_njoy_obj.get_mat();
  temp    = read_njoy_obj.get_temp();
  opt_run = read_njoy_obj.get_opt_run();

  //For input data (Common)
  ace_obj.set_opt_run(opt_run);

  ace_obj.set_ace_file_name(read_njoy_obj.get_ace_name());
  ace_obj.set_mcnp_dir(read_njoy_obj.get_mcnp_dir());
  ace_obj.set_discriptive_data(read_njoy_obj.get_discriptive_data());
  ace_obj.set_mcnpx_mode_flg(read_njoy_obj.get_mcnpx_mode_flg());
  ace_obj.set_opt_print(read_njoy_obj.get_opt_print());
  ace_obj.set_opt_out_type(read_njoy_obj.get_opt_out_type());
  ace_obj.set_mat(read_njoy_obj.get_mat());
  ace_obj.set_temp(read_njoy_obj.get_temp());
  ace_obj.set_suffix_za_id(read_njoy_obj.get_suffix_za_id());
  ace_obj.set_zi_vec(read_njoy_obj.get_zi_vec());
  ace_obj.set_awr_vec(read_njoy_obj.get_awr_vec());

  //For input data (Fast)
  ace_obj.set_new_cummulative_angle_distr_flg(read_njoy_obj.get_new_cummulative_angle_distr_flg());
  ace_obj.set_detailed_photon_flg(read_njoy_obj.get_detailed_photon_flg());
  ace_obj.set_thinning_ene(read_njoy_obj.get_thinning_ene());

  //For input data (Thermal scattering)
  ace_obj.set_thermal_za_id_name(read_njoy_obj.get_thermal_za_id_name());
  ace_obj.set_mt_inelastic(read_njoy_obj.get_mt_inelastic());
  ace_obj.set_bin_no(read_njoy_obj.get_bin_no());
  ace_obj.set_mt_elastic(read_njoy_obj.get_mt_elastic());
  ace_obj.set_elastic_flg(read_njoy_obj.get_elastic_flg());
  ace_obj.set_atom_no_th(read_njoy_obj.get_atom_no_th());
  ace_obj.set_opt_weight(read_njoy_obj.get_opt_weight());
  ace_obj.set_ene_max_th(read_njoy_obj.get_ene_max_th());
  ace_obj.set_mod_za(read_njoy_obj.get_mod_za());
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataGeneratorByNjoyInput::set_nucl_data_obj_all()
{
  //Set endf file
  NuclearDataObject nucl_data_obj;
  if( opt_run == fast_data_mode )
  {
    set_nucl_data_obj_fast(nucl_data_obj);
  }
  else if( opt_run == thermal_data_mode ) //For thermal scattering low data
  {
    //Only PENDF file is required for calculation.
    //(Since ENDF file is not required, ENDF file read scheme is skipped.)
    set_nucl_data_obj(pendf_name, nucl_data_obj, temp);
  }
  else if( opt_run == dosimetry_data_mode )
  {
    set_nucl_data_obj_dosimetry(nucl_data_obj);
  }

  //Set NuclearDataObject to AceDataGenerator
  ace_obj.set_nucl_data_obj(nucl_data_obj);
  nucl_data_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataGeneratorByNjoyInput::set_nucl_data_obj_fast(NuclearDataObject& nucl_data_obj)
{
  NuclearDataObject nucl_data_obj_pendf;

  //Set endf file
  set_nucl_data_obj(endf_name, nucl_data_obj, -1.0);

  //Set pendf file
  set_nucl_data_obj(pendf_name, nucl_data_obj_pendf, temp);

  //Copy resonance data
  nucl_data_obj.set_reso_data_obj(nucl_data_obj_pendf.get_reso_data_obj());

  //Copy temperature and error data
  Real temp_val  = nucl_data_obj_pendf.get_general_data_obj().get_temp();
  Real error_val = nucl_data_obj_pendf.get_general_data_obj().get_error_value();

  GeneralDataContainer gen_obj = nucl_data_obj.get_general_data_obj();
  gen_obj.set_temp(temp_val);
  gen_obj.set_error_value(error_val);
  nucl_data_obj.set_general_data_obj(gen_obj);


  //Copy cross section data
  vector<CrossSectionDataContainer>        xs_obj;
  xs_obj = nucl_data_obj_pendf.get_nucl_reaction_data_obj().get_xs_data_obj();

  NuclearReactionDataContainer nucl_reaction_data_obj = nucl_data_obj.get_nucl_reaction_data_obj();
  nucl_reaction_data_obj.set_xs_data_obj(xs_obj);
  vector<CrossSectionDataContainer>().swap(xs_obj);
  
  //Set cross section data to NuclearDataObject
  nucl_data_obj.set_nucl_reaction_data_obj(nucl_reaction_data_obj);
  nucl_reaction_data_obj.clear();

  nucl_data_obj_pendf.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataGeneratorByNjoyInput::set_nucl_data_obj_dosimetry(NuclearDataObject& nucl_data_obj)
{
  NuclearDataObject nucl_data_obj_ori;

  //Set endf file
  set_nucl_data_obj(endf_name, nucl_data_obj_ori, -1.0);

  //Set pendf file
  set_nucl_data_obj(pendf_name, nucl_data_obj, temp);

  //Copy radio active product data from endf file
  NuclearReactionDataContainer            nucl_reaction_data_obj;
  vector<RadioactiveProductDataContainer> radio_product_data_obj, radio_product_data_obj_ori;

  //For original ENDF file
  nucl_reaction_data_obj     = nucl_data_obj_ori.get_nucl_reaction_data_obj();
  radio_product_data_obj_ori = nucl_reaction_data_obj.get_radio_product_data_obj();
  nucl_reaction_data_obj.clear();

  //For PENDF file
  nucl_reaction_data_obj = nucl_data_obj.get_nucl_reaction_data_obj();
  radio_product_data_obj = nucl_reaction_data_obj.get_radio_product_data_obj();

  int i_max = static_cast<int>(radio_product_data_obj_ori.size());
  int j_max = static_cast<int>(radio_product_data_obj.size());
  for(int i=0; i<i_max; i++)
  {
    if( static_cast<int>(radio_product_data_obj_ori[i].get_multiplicity_state_no_product().size()) > 0 )
    {
      Integer reaction_type = radio_product_data_obj_ori[i].get_reaction_type();

      Integer         multiplicity_state_no_target;
      vector<Integer> multiplicity_state_no_product, multiplicity_mat_data_product;
      vector<Real>    multiplicity_q_value_mass,     multiplicity_q_value;
      vector<vector<Integer> > multiplicity_range_data, multiplicity_int_data;
      vector<vector<Real> >    multiplicity_ene_data,   multiplicity_data;

      multiplicity_state_no_target  = radio_product_data_obj_ori[i].get_multiplicity_state_no_target();
      multiplicity_state_no_product = radio_product_data_obj_ori[i].get_multiplicity_state_no_product();
      multiplicity_q_value_mass     = radio_product_data_obj_ori[i].get_multiplicity_q_value_mass();
      multiplicity_q_value          = radio_product_data_obj_ori[i].get_multiplicity_q_value();
      multiplicity_mat_data_product = radio_product_data_obj_ori[i].get_multiplicity_mat_data_product();
      multiplicity_range_data       = radio_product_data_obj_ori[i].get_multiplicity_range_data();
      multiplicity_int_data         = radio_product_data_obj_ori[i].get_multiplicity_int_data();
      multiplicity_ene_data         = radio_product_data_obj_ori[i].get_multiplicity_ene_data();
      multiplicity_data             = radio_product_data_obj_ori[i].get_multiplicity_data();

      int add_flg = -1;
      for(int j=0; j<j_max; j++)
      {
        if( radio_product_data_obj[j].get_reaction_type() == reaction_type )
        {
          add_flg = j;
          radio_product_data_obj[j].set_multiplicity_state_no_target(multiplicity_state_no_target);
          radio_product_data_obj[j].set_multiplicity_state_no_product(multiplicity_state_no_product);
          radio_product_data_obj[j].set_multiplicity_q_value_mass(multiplicity_q_value_mass);
          radio_product_data_obj[j].set_multiplicity_q_value(multiplicity_q_value);
          radio_product_data_obj[j].set_multiplicity_mat_data_product(multiplicity_mat_data_product);
          radio_product_data_obj[j].set_multiplicity_range_data(multiplicity_range_data);
          radio_product_data_obj[j].set_multiplicity_int_data(multiplicity_int_data);
          radio_product_data_obj[j].set_multiplicity_ene_data(multiplicity_ene_data);
          radio_product_data_obj[j].set_multiplicity_data(multiplicity_data);
          break;
        }
      }
      if( add_flg >= 0 )
      {
        //Add Cross Sections for Production of Radioactive Nucliedes in original data
        nucl_reaction_data_obj.set_radio_product_data_obj(radio_product_data_obj[add_flg]);
      }
      else
      {
        //Newly add Cross Sections for Production of Radioactive Nucliedes
        nucl_reaction_data_obj.set_radio_product_data_obj(radio_product_data_obj_ori[i]);
      }
    }
  }
  vector<RadioactiveProductDataContainer>().swap(radio_product_data_obj);
  vector<RadioactiveProductDataContainer>().swap(radio_product_data_obj_ori);

  nucl_data_obj.set_nucl_reaction_data_obj(nucl_reaction_data_obj);
  nucl_reaction_data_obj.clear();
}


////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataGeneratorByNjoyInput::set_nucl_data_obj(string& file_name, NuclearDataObject& nucl_obj, Real temp_val)
{
  EndfTapeDivider         div_obj;
  EndfFileReader          efr_obj;
  Endf6Parser             endf_file_parser;
  Endf6Converter          conv_obj;
  vector<string>          endf_file_text;

  div_obj.set_file_name(file_name);
  if( mat != 0 )
  {
    if( temp_val > 0.0 )
    {
      endf_file_text = div_obj.get_designated_temp_data(mat, temp_val);
    }
    else
    {
      endf_file_text = div_obj.get_data(mat);
    }
  }
  else
  {
    endf_file_text = div_obj.get_data_all();
  }

  //Remove warning from read and convert endf-6 format
  //err_obj.set_err_mes_opt(err_obj.err_mes_debug);

  efr_obj.set_endf_data(endf_file_text);
  clr_obj.clear_vec_array1_str(endf_file_text);

  //endf_file_parser.set_endf_file_reader(efr_obj);
  endf_file_parser.set_endf_file_reader_no_cov(efr_obj); //To fast read of the nuclear data
  efr_obj.clear();

  conv_obj.convert_endf_format_to_frendy(endf_file_parser, nucl_obj);
  endf_file_parser.clear();

  //err_obj.set_err_mes_opt(err_obj.err_mes_default);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//Setter

void AceDataGeneratorByNjoyInput::set_njoy_input_file_name(string str_data)
{
  set_njoy_input_file_name(str_data, 0);
}

void AceDataGeneratorByNjoyInput::set_njoy_input_file_name(string str_data, int line_no)
{
  calc_flg = 0;
  input_file_name_njoy = str_data;
  start_line_no        = line_no;

  str_data.clear();
}

void AceDataGeneratorByNjoyInput::set_generate_mode_flg(int int_val)
{
  calc_flg          = 0;
  generate_mode_flg = int_val;

  ace_obj.set_generate_mode_flg(generate_mode_flg);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//Getter

string AceDataGeneratorByNjoyInput::get_njoy_input_file_name()
{
  return input_file_name_njoy;
}

int    AceDataGeneratorByNjoyInput::get_generate_mode_flg()
{
  return generate_mode_flg;
}

