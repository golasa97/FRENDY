#include "ContinuousEnergyXSUtils/AceDataGenerator/AceDataGeneratorByFrendyInput.hpp"

using namespace frendy;

//constructor
AceDataGeneratorByFrendyInput::AceDataGeneratorByFrendyInput(void)
{
  clear();
}

//destructor
AceDataGeneratorByFrendyInput::~AceDataGeneratorByFrendyInput(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataGeneratorByFrendyInput::clear()
{
  calc_flg                  = 0;
  set_inp_mode_flg          = 0;
  set_frendy_inp_obj_flg    = 0;
  set_nucl_data_obj_flg     = 0;
  set_nucl_data_obj_ori_flg = 0;

  ace_data_obj.clear();
  nucl_data_obj.clear();
  nucl_data_obj_ori.clear();

  ace_obj.clear();
  frendy_inp_obj.clear();

  inp_mode = 0;
  inp_pos  = 0;
  generate_mode_flg = ace_obj.get_generate_mode_flg();

  time_total = 0.0;

  write_ace_flg = write_ace;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataGeneratorByFrendyInput::generate_ace_data()
{
  if( calc_flg == 1 )
  {
    return;
  }
  calc_flg = 1;

  cout << "****************************** Ace file generation ******************************";
  cout << endl << endl;
  time_obj.output_current_time();

  boost::timer::cpu_timer timer_total;
  time_total = 0.0;

  //Set input data to AceDataGenerator
  set_input_data();

  //Mearge nucl_data_obj and nucl_data_obj_ori to nucl_data_obj
  if( inp_mode == ace_obj.fast_mode )
  {
    set_nucl_data_obj_fast();
  }
  else if( inp_mode == ace_obj.dosimetry_mode )
  {
    set_nucl_data_obj_dosimetry();
  }

  //Set NuclearDataObject input data to AceDataGenerator
  ace_obj.set_nucl_data_obj(nucl_data_obj);
  ace_obj.set_generate_mode_flg(generate_mode_flg);
  ace_obj.set_write_ace_flg(write_ace_flg);

  //Run AceDataGenerator
  ace_obj.generate_ace_data();
  ace_data_obj = ace_obj.get_ace_data_obj();
  ace_obj.clear();

  time_total = static_cast<Integer>(timer_total.elapsed().wall * 1.0E-9);
  cout << "Total calculation time : " << time_total << " [s]" << endl;
  cout << endl;
  cout << "***********************************************************************************************";
  cout << endl << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataGeneratorByFrendyInput::set_input_data()
{
  inp_mode = frendy_inp_obj.get_generation_mode();

  //For input data (Common)
  ace_obj.set_opt_run(inp_mode);

  if( inp_mode == ace_obj.fast_mode )
  {
    ace_obj.set_ace_file_name(frendy_inp_obj.get_ace_file_name_fast()[inp_pos]);
    ace_obj.set_mcnp_dir(frendy_inp_obj.get_ace_dir_file_name_fast()[inp_pos]);
  }
  else if ( inp_mode == ace_obj.thermal_mode )
  {
    ace_obj.set_ace_file_name(frendy_inp_obj.get_ace_file_name_therm()[inp_pos]);
    ace_obj.set_mcnp_dir(frendy_inp_obj.get_ace_dir_file_name_therm()[inp_pos]);
  }
  else
  {
    ace_obj.set_ace_file_name(frendy_inp_obj.get_ace_file_name()[inp_pos]);
    ace_obj.set_mcnp_dir(frendy_inp_obj.get_ace_dir_file_name()[inp_pos]);
  }

  ace_obj.set_discriptive_data(frendy_inp_obj.get_ace_label_data()[inp_pos]);
  ace_obj.set_mat(nucl_data_obj.get_general_data_obj().get_mat_no());
  ace_obj.set_temp(nucl_data_obj.get_general_data_obj().get_temp());
  ace_obj.set_suffix_za_id(frendy_inp_obj.get_suffix_id());

  vector<Integer> zi_vec;
  vector<Real>    zi_vec_real, awr_vec;
  if( static_cast<int>(frendy_inp_obj.get_iz_aw_data().size()) > 1 )
  {
    zi_vec_real = frendy_inp_obj.get_iz_aw_data()[0];
    awr_vec     = frendy_inp_obj.get_iz_aw_data()[1];
  }

  int i_max = static_cast<int>(zi_vec_real.size());
  zi_vec.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    zi_vec[i] = static_cast<Integer>(zi_vec_real[i]);
  }

  ace_obj.set_zi_vec(zi_vec);
  ace_obj.set_awr_vec(awr_vec);

  if( inp_mode == ace_obj.fast_mode )
  {
    //For input data (Fast)
    ace_obj.set_new_cummulative_angle_distr_flg(frendy_inp_obj.get_cumulative_angle_distribution_format());
  }
  else if( inp_mode == ace_obj.thermal_mode )
  {
    //For input data (Thermal scattering)
    Integer elastic_raction_type = frendy_inp_obj.get_inelastic_reaction_type_no() + 1; 
    Integer elastic_scat_flg     = nucl_data_obj_ori.get_thermal_scat_data_obj().get_elastic_scat_flg();

    Integer opt_elastic = 0; //For coherent elastic scattering
    if( elastic_scat_flg == 0 ) //No elastic scattering
    {
      elastic_raction_type = 0; //Skip elastic scattering data generation
    }
    else if( elastic_scat_flg == 2 ) //For incoherent elastic scattering
    {
      opt_elastic = 1; //Modify elastic option from coherent to incoherent
    }
    else if( elastic_scat_flg == 3 ) //For mixed coherent and incoherent elastic scattering
    {
      opt_elastic = 2; //Modify elastic option from coherent to mixed
    }

    ace_obj.set_thermal_za_id_name(frendy_inp_obj.get_thermal_za_id_name());
    ace_obj.set_mt_inelastic(frendy_inp_obj.get_inelastic_reaction_type_no());
    ace_obj.set_bin_no(frendy_inp_obj.get_equi_probable_angle_no());
    ace_obj.set_mt_elastic(elastic_raction_type);
    ace_obj.set_elastic_flg(opt_elastic);
    ace_obj.set_atom_no_th(frendy_inp_obj.get_atom_type_no());
    ace_obj.set_opt_weight(frendy_inp_obj.get_weight_option());
    ace_obj.set_ene_max_th(frendy_inp_obj.get_max_thermal_ene());
    ace_obj.set_mod_za(frendy_inp_obj.get_moderator_za_data());
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataGeneratorByFrendyInput::set_nucl_data_obj_fast()
{
  NuclearDataObject nucl_data_obj_tmp = nucl_data_obj_ori;

  //Copy resonance data
  nucl_data_obj_tmp.set_reso_data_obj(nucl_data_obj.get_reso_data_obj());

  //Copy temperature and error data
  Real temp_val  = nucl_data_obj.get_general_data_obj().get_temp();
  Real error_val = nucl_data_obj.get_general_data_obj().get_error_value();

  GeneralDataContainer gen_obj = nucl_data_obj_ori.get_general_data_obj();
  gen_obj.set_temp(temp_val);
  gen_obj.set_error_value(error_val);
  nucl_data_obj_tmp.set_general_data_obj(gen_obj);


  //Copy cross section data
  vector<CrossSectionDataContainer> xs_obj;
  xs_obj = nucl_data_obj.get_nucl_reaction_data_obj().get_xs_data_obj();

  NuclearReactionDataContainer nucl_reaction_data_obj = nucl_data_obj_ori.get_nucl_reaction_data_obj();
  nucl_reaction_data_obj.set_xs_data_obj(xs_obj);
  vector<CrossSectionDataContainer>().swap(xs_obj);
  
  //Set cross section data to NuclearDataObject
  nucl_data_obj_tmp.set_nucl_reaction_data_obj(nucl_reaction_data_obj);
  nucl_reaction_data_obj.clear();

  nucl_data_obj = nucl_data_obj_tmp;
  nucl_data_obj_tmp.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataGeneratorByFrendyInput::set_nucl_data_obj_dosimetry()
{
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

void AceDataGeneratorByFrendyInput::check_set_data_flg()
{
  if( set_inp_mode_flg      == 0 || set_frendy_inp_obj_flg    == 0 ||
      set_nucl_data_obj_flg == 0 || set_nucl_data_obj_ori_flg == 0)
  {
    string class_name = "AceDataGeneratorByFrendyInput";
    string func_name  = "check_set_data_flg()";

    vector<string> err_com;
    if( set_inp_mode_flg == 0 )
    {
      err_com.push_back("Please set the input data mode (fast, thermal or dosimetry)");
      err_com.push_back("using set_inp_mode() function.");
    }

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

    if( set_nucl_data_obj_ori_flg == 0 )
    {
      err_com.push_back("Please set the original NuclearDataObject");
      err_com.push_back("using set_nucl_data_obj_ori() function.");
    }

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//Setter

void AceDataGeneratorByFrendyInput::set_frendy_inp_obj(AceDataGeneratorInputReader inp_obj)
{
  calc_flg               = 0;
  set_frendy_inp_obj_flg = 1;

  frendy_inp_obj = inp_obj;
}

void AceDataGeneratorByFrendyInput::set_nucl_data_obj(NuclearDataObject data_obj)
{
  calc_flg              = 0;
  set_nucl_data_obj_flg = 1;

  nucl_data_obj = data_obj;
}

void AceDataGeneratorByFrendyInput::set_nucl_data_obj_ori(NuclearDataObject data_obj)
{
  calc_flg                  = 0;
  set_nucl_data_obj_ori_flg = 1;

  nucl_data_obj_ori = data_obj;
}

void AceDataGeneratorByFrendyInput::set_inp_mode(int int_val)
{
  calc_flg         = 0;
  set_inp_mode_flg = 1;

  inp_mode = int_val;
}

void AceDataGeneratorByFrendyInput::set_inp_pos(int int_val)
{
  calc_flg = 0;
  inp_pos  = int_val;
}

void AceDataGeneratorByFrendyInput::set_generate_mode_flg(int int_val)
{
  calc_flg          = 0;
  generate_mode_flg = int_val;

  ace_obj.set_generate_mode_flg(generate_mode_flg);
}

void AceDataGeneratorByFrendyInput::set_write_ace_flg(int int_val)
{
  calc_flg      = 0;
  write_ace_flg = int_val;

  if( write_ace_flg != write_ace && write_ace_flg != skip_write_ace )
  {
    string class_name = "AceDataGeneratorByFrendyInput";
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

AceDataGeneratorInputReader AceDataGeneratorByFrendyInput::get_frendy_inp_obj()
{
  return frendy_inp_obj;
}

NuclearDataObject AceDataGeneratorByFrendyInput::get_nucl_data_obj()
{
  generate_ace_data();

  return nucl_data_obj;
}

NuclearDataObject AceDataGeneratorByFrendyInput::get_nucl_data_obj_ori()
{
  return nucl_data_obj_ori;
}

AceDataObject AceDataGeneratorByFrendyInput::get_ace_data_obj()
{
  generate_ace_data();

  return ace_data_obj;
}

int AceDataGeneratorByFrendyInput::get_inp_mode()
{
  return inp_mode;
}

int AceDataGeneratorByFrendyInput::get_inp_pos()
{
  return inp_pos;
}

int AceDataGeneratorByFrendyInput::get_generate_mode_flg()
{
  return generate_mode_flg;
}

int AceDataGeneratorByFrendyInput::get_write_ace_flg()
{
  return write_ace_flg;
}


////////////////////////////////////////////////////////////////////////////////////////////////////

Real AceDataGeneratorByFrendyInput::get_time_total()
{
  return time_total;
}

Real AceDataGeneratorByFrendyInput::get_calc_time()
{
  return time_total;
}

