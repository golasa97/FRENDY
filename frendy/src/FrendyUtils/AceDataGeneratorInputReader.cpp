#include "FrendyUtils/AceDataGeneratorInputReader.hpp"

using namespace frendy;

AceDataGeneratorInputReader::AceDataGeneratorInputReader(void)
{
  clear();
}

AceDataGeneratorInputReader::~AceDataGeneratorInputReader(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

const int AceDataGeneratorInputReader::inp_mode_common;
const int AceDataGeneratorInputReader::inp_mode_fast;
const int AceDataGeneratorInputReader::inp_mode_therm;
const int AceDataGeneratorInputReader::inp_mode_dosi;

////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataGeneratorInputReader::clear()
{
  print_title_flg           = 0;
  mod_ace_file_name_flg     = 0;
  mod_ace_dir_file_name_flg = 0;

  print_set_data_flg      = frendy_utils.get_print_set_data_flg_def();
  process_flg             = frendy_utils.get_process_flg_def();

  nucl_file_name          = frendy_utils.get_nucl_file_name_def();
  nucl_file_name_tsl      = frendy_utils.get_nucl_file_name_tsl_def();
  ace_file_name           = frendy_utils.get_ace_file_name_def();
  ace_file_name_fast      = frendy_utils.get_ace_file_name_def();
  ace_file_name_therm     = frendy_utils.get_ace_file_name_def();
  ace_dir_file_name       = frendy_utils.get_ace_dir_file_name_def();
  ace_dir_file_name_fast  = frendy_utils.get_ace_dir_file_name_def();
  ace_dir_file_name_therm = frendy_utils.get_ace_dir_file_name_def();

  ace_label_data          = frendy_utils.get_ace_label_data_def();
  suffix_id               = frendy_utils.get_suffix_id_def();
  iz_aw_data              = frendy_utils.get_iz_aw_data_def();

  //For FastAceDataGenerator
  cumulative_angle_distribution_format = frendy_utils.get_cumulative_angle_distribution_format_def();

  //For ThermalScatterAceDataGenerator
  thermal_za_id_name         = frendy_utils.get_thermal_za_id_name_def();
  inelastic_reaction_type_no = frendy_utils.get_inelastic_reaction_type_no_def();
  moderator_za_data          = frendy_utils.get_moderator_za_data_def();
  atom_type_no               = frendy_utils.get_atom_type_no_def();
  equi_probable_angle_no     = frendy_utils.get_equi_probable_angle_no_def();
  weight_option              = frendy_utils.get_weight_option_def();
  max_thermal_ene            = frendy_utils.get_max_thermal_ene_in_def();

  //Please modify skip_nucl_name_tsl in AceDataGeneratorInputReader class
  //if you modify skip_nucl_name_tsl.
  skip_nucl_name_tsl.resize(3);
  skip_nucl_name_tsl[0] = "no";
  skip_nucl_name_tsl[1] = "none";
  skip_nucl_name_tsl[2] = "skip";
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataGeneratorInputReader::read_input_data_from_input_file(string file_name)
{
  FileCommentRemover file_handling_obj;
  vector<vector<string> > input_data = file_handling_obj.remove_comment_and_devide_text_data(file_name);

  read_input_data(input_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<int> AceDataGeneratorInputReader::read_input_data(vector<vector<string> >& input_data)
{
  int i_max = static_cast<int>(input_data.size());
  int i_sta = 0;
  if( i_max%2 == 1 ) //include calculation mode at input_data[0][0]
  {
    i_sta = 1;
  }

  int data_no = (i_max - i_sta) / 2;
  vector<int> inp_check_vec;
  inp_check_vec.resize(data_no);

  int ele_no = 0;
  for(int i=i_sta; i<i_max; i+=2)
  {
    inp_check_vec[ele_no] = read_input_data(input_data[i], input_data[i+1]);
    ele_no++;
  }

  return inp_check_vec;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int AceDataGeneratorInputReader::read_input_data(vector<string>& input_type, vector<string>& input_data)
{
  if( static_cast<int>(input_type.size()) != 1 )
  {
    string class_name = "AceDataGeneratorInputReader";
    string func_name  = "read_input_data(vector<string>& input_type, vector<string>& input_data)";
    frendy_utils.error_input_type_size(class_name, func_name, input_data);
  }

  return read_input_data(input_type[0], input_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int AceDataGeneratorInputReader::read_input_data(string& input_type, vector<string>& input_data)
{
  if( static_cast<int>(input_data.size()) == 0 )
  {
    string class_name = "AceDataGeneratorInputReader";
    string func_name  = "read_input_data(string& input_type, vector<string>& input_data)";
    frendy_utils.error_input_data_size_is_zero(class_name, func_name, input_data);
  }

  if( print_set_data_flg == frendy_utils.print_set_data && print_title_flg == 0 )
  {
    print_title_flg = 1;
    cout << "=== Read input data for AceDataGenerator ===" << endl;
  }

  //Modify capital letter to lower-case letter
  string input_type_mod = input_type;
  transform(input_type_mod.begin(), input_type_mod.end(), input_type_mod.begin(), ::tolower);
  replace(input_type_mod.begin(), input_type_mod.end(), '-', '_');

  int inp_check = inp_mode_common;
  if( input_type_mod == "nucl_file_name" || input_type_mod == "nucl_name" ||
      input_type_mod == "endf_file_name" || input_type_mod == "endf_name" )
  {
    set_nucl_file_name(input_data);
  }
  else if( input_type_mod == "nucl_file_name_tsl" || input_type_mod == "nucl_name_tsl" ||
           input_type_mod == "endf_file_name_tsl" || input_type_mod == "endf_name_tsl" )
  {
    inp_check = inp_mode_therm;
    set_nucl_file_name_tsl(input_data);
  }
  else if( input_type_mod == "ace_file_name" || input_type_mod == "ace_name" )
  {
    set_ace_file_name(input_data);
  }
  else if( input_type_mod == "ace_dir_file_name"  || input_type_mod == "ace_dir" ||
           input_type_mod == "mcnp_dir_file_name" || input_type_mod == "mcnp_dir" )
  {
    set_ace_dir_file_name(input_data);
  }
  else if( input_type_mod == "ace_label_data" )
  {
    set_ace_label_data(input_data);
  }
  else if( input_type_mod == "suffix_id" )
  {
    set_suffix_id(input_data);
  }
  else if( input_type_mod == "iz_aw_data" )
  {
    set_iz_aw_data(input_data);
  }
  else if( input_type_mod == "cumulative_angle_distribution_format" )
  {
    inp_check = inp_mode_fast;
    set_cumulative_angle_distribution_format(input_data);
  }
  else if( input_type_mod == "thermal_za_id_name" )
  {
    inp_check = inp_mode_therm;
    set_thermal_za_id_name(input_data);
  }
  else if( input_type_mod == "inelastic_reaction_type_no" )
  {
    inp_check = inp_mode_therm;
    set_inelastic_reaction_type_no(input_data);
  }
  else if( input_type_mod == "moderator_za_data" || input_type_mod == "moderator_za_id_name" )
  {
    inp_check = inp_mode_therm;
    set_moderator_za_data(input_data);
  }
  else if( input_type_mod == "atom_type_no" )
  {
    inp_check = inp_mode_therm;
    set_atom_type_no(input_data);
  }
  else if( input_type_mod == "equi_probable_angle_no" )
  {
    inp_check = inp_mode_therm;
    set_equi_probable_angle_no(input_data);
  }
  else if( input_type_mod == "weight_option" )
  {
    inp_check = inp_mode_therm;
    set_weight_option(input_data);
  }
  else if( input_type_mod == "max_thermal_ene" )
  {
    inp_check = inp_mode_therm;
    set_max_thermal_ene(input_data);
  }
  else if( input_type_mod == "print_set_data_ace" ||
           input_type_mod == "print_set_data_ace_data_generator" )
  {
    set_print_set_data_flg(input_data);
  }
  else if( input_type_mod == "process_ace" ||
           input_type_mod == "process_ace_data_generator" )
  {
    set_process_flg(input_data);
  }
  else
  {
    inp_check = 0;
  }

  return inp_check;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataGeneratorInputReader::set_nucl_file_name_tsl(vector<string>& input_data)
{
  int i_max = static_cast<int>(input_data.size());
  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    for(int i=0; i<i_max; i++)
    {
      if( i==0 )
      {
        cout << "  nucl_file_name_tsl                   : " << input_data[i] << endl;
      }
      else
      {
        cout << "                                       : " << input_data[i] << endl;
      }
    }
  }

  nucl_file_name_tsl = input_data;
  if( static_cast<int>(ace_file_name.size()) == 0 || mod_ace_file_name_flg == 1 )
  {
    ace_file_name.resize(i_max);
    ace_file_name_therm.resize(i_max);
    for(int i=0; i<i_max; i++)
    {
      ace_file_name[i].clear();
      ace_file_name_therm[i].clear();

      string tsl_chk = nucl_file_name_tsl[i];
      transform(tsl_chk.begin(), tsl_chk.end(), tsl_chk.begin(), ::tolower);

      int skip_flg = 0;
      for(int j=0; j<static_cast<int>(skip_nucl_name_tsl.size()); j++)
      {
        if( tsl_chk == skip_nucl_name_tsl[j] )
        {
          skip_flg = 1;
          break;
        }
      }

      if( skip_flg == 0 )
      {
        StringUtils str_util_obj;
        ace_file_name[i] = str_util_obj.basename(nucl_file_name_tsl[i]) + ".ace";
        ace_file_name_therm[i] = str_util_obj.basename(nucl_file_name_tsl[i]) + ".ace";
      }
    }
  }
  if( static_cast<int>(ace_dir_file_name.size()) == 0 || mod_ace_dir_file_name_flg == 1 )
  {
    ace_dir_file_name.resize(i_max);
    ace_dir_file_name_therm.resize(i_max);
    for(int i=0; i<i_max; i++)
    {
      ace_dir_file_name[i].clear();
      ace_dir_file_name_therm[i].clear();

      string tsl_chk = nucl_file_name_tsl[i];
      transform(tsl_chk.begin(), tsl_chk.end(), tsl_chk.begin(), ::tolower);

      int skip_flg = 0;
      for(int j=0; j<static_cast<int>(skip_nucl_name_tsl.size()); j++)
      {
        if( tsl_chk == skip_nucl_name_tsl[j] )
        {
          skip_flg = 1;
          break;
        }
      }

      if( skip_flg == 0 )
      {
        StringUtils str_util_obj;
        ace_dir_file_name[i] = str_util_obj.basename(nucl_file_name_tsl[i]) + ".ace.dir";
        ace_dir_file_name_therm[i] = str_util_obj.basename(nucl_file_name_tsl[i]) + ".ace.dir";
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataGeneratorInputReader::set_suffix_id(vector<string>& input_data)
{
  if( static_cast<int>(input_data.size()) > 1 )
  {
    string class_name = "AceDataGeneratorInputReader";
    string func_name  = "set_suffix_id(vector<string>& input_data)";
    frendy_utils.error_input_data_size_is_larger_than_one(class_name, func_name, input_data);
  }

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  suffix_id                            : " << input_data[0] << endl;
  }

  str_obj.string_check(input_data[0]);
  suffix_id = numeric_string_cast<Real>(input_data[0]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataGeneratorInputReader::set_iz_aw_data(vector<string>& input_data)
{
  int i_max = static_cast<int>(input_data.size());
  if( i_max%2 != 0 )
  {
    string class_name = "AceDataGeneratorInputReader";
    string func_name  = "set_iz_aw_data(vector<string>& input_data)";

    vector<string> err_com;
    ostringstream oss01;
    oss01 << i_max;
    string str_data01 = "Number of iz_aw_data : " + oss01.str();
    err_com.push_back(str_data01);
 
    err_com.push_back("iz_aw_data");
    for(int i=0; i<i_max; i++)
    {
      ostringstream oss02, oss03;
      oss02 << i+1;
      oss03 << i_max;
      string str_data02 = "  " + oss02.str() + " / " + oss03.str() + " : " + input_data[i];
      err_com.push_back(str_data02);
    }

    err_com.push_back("The number of iz_aw_data is uneven number.");
    err_com.push_back("The number of iz_aw_data must be even number.");
    err_com.push_back("Please check the iz_aw_data.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  iz_aw_data" << endl;
  }

  iz_aw_data.resize(2);
  iz_aw_data[0].resize(i_max/2);
  iz_aw_data[1].resize(i_max/2);

  int ele_no = 0;
  for(int i=0; i<i_max; i+=2)
  {
    if( print_set_data_flg == frendy_utils.print_set_data )
    {
        cout << "    " << ele_no+1 << " / " << i_max/2 << " : "
             << input_data[i] << " / " << input_data[i+1] << endl;
    }

    str_obj.string_check(input_data[i]);
    str_obj.string_check(input_data[i+1]);
    iz_aw_data[0][ele_no] = numeric_string_cast<Real>(input_data[i]);
    iz_aw_data[1][ele_no] = numeric_string_cast<Real>(input_data[i+1]);
    ele_no++;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataGeneratorInputReader::set_cumulative_angle_distribution_format(vector<string>& input_data)
{
  if( static_cast<int>(input_data.size()) > 1 )
  {
    string class_name = "AceDataGeneratorInputReader";
    string func_name  = "set_cumulative_angle_distribution_format(vector<string>& input_data)";
    frendy_utils.error_input_data_size_is_larger_than_one(class_name, func_name, input_data);
  }

  string input_data_mod = input_data[0];
  transform(input_data_mod.begin(), input_data_mod.end(), input_data_mod.begin(), ::tolower);

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  cumulative_angle_distribution_format : " << input_data_mod << endl;
  }

  if( input_data_mod == "use_cumulative_angle_distribution_format" || input_data_mod == "use" ||
      input_data_mod == "yes")
  {
    cumulative_angle_distribution_format = frendy_utils.use_cumulative_angle_distribution_format;
  }
  else if( input_data_mod == "no_cumulative_angle_distribution_format" || input_data_mod == "no" )
  {
    cumulative_angle_distribution_format = frendy_utils.no_cumulative_angle_distribution_format;
  }
  else if( input_data_mod == "default" || input_data_mod == "def" )
  {
    cumulative_angle_distribution_format = frendy_utils.get_cumulative_angle_distribution_format_def();
  }
  else
  {
    str_obj.string_check(input_data_mod);
    cumulative_angle_distribution_format = numeric_string_cast<int>(input_data_mod);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataGeneratorInputReader::set_thermal_za_id_name(vector<string>& input_data)
{
  if( static_cast<int>(input_data.size()) > 1 )
  {
    string class_name = "AceDataGeneratorInputReader";
    string func_name  = "set_thermal_za_id_name(vector<string>& input_data)";
    frendy_utils.error_input_data_size_is_larger_than_one(class_name, func_name, input_data);
  }

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  thermal_za_id_name                   : " << input_data[0] << endl;
  }

  thermal_za_id_name = input_data[0];
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataGeneratorInputReader::set_inelastic_reaction_type_no(vector<string>& input_data)
{
  if( static_cast<int>(input_data.size()) > 1 )
  {
    string class_name = "AceDataGeneratorInputReader";
    string func_name  = "set_inelastic_reaction_type_no(vector<string>& input_data)";
    frendy_utils.error_input_data_size_is_larger_than_one(class_name, func_name, input_data);
  }

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  inelastic_reaction_type_no           : " << input_data[0] << endl;
  }

  str_obj.string_check(input_data[0]);
  inelastic_reaction_type_no = numeric_string_cast<Integer>(input_data[0]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataGeneratorInputReader::set_moderator_za_data(vector<string>& input_data)
{
  int i_max = static_cast<int>(input_data.size());

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  moderator_za_data" << endl;
  }

  moderator_za_data.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    if( print_set_data_flg == frendy_utils.print_set_data )
    {
      cout << "    " << i+1 << " / " << i_max << " : " << input_data[i] << endl;
    }

    str_obj.string_check(input_data[i]);
    moderator_za_data[i] = numeric_string_cast<Integer>(input_data[i]);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataGeneratorInputReader::set_atom_type_no(vector<string>& input_data)
{
  if( static_cast<int>(input_data.size()) > 1 )
  {
    string class_name = "AceDataGeneratorInputReader";
    string func_name  = "set_atom_type_no(vector<string>& input_data)";
    frendy_utils.error_input_data_size_is_larger_than_one(class_name, func_name, input_data);
  }

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  atom_type_no                         : " << input_data[0] << endl;
  }

  str_obj.string_check(input_data[0]);
  atom_type_no = numeric_string_cast<Integer>(input_data[0]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataGeneratorInputReader::set_equi_probable_angle_no(vector<string>& input_data)
{
  if( static_cast<int>(input_data.size()) > 1 )
  {
    string class_name = "AceDataGeneratorInputReader";
    string func_name  = "set_equi_probable_angle_no(vector<string>& input_data)";
    frendy_utils.error_input_data_size_is_larger_than_one(class_name, func_name, input_data);
  }

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  equi_probable_angle_no               : " << input_data[0] << endl;
  }

  str_obj.string_check(input_data[0]);
  equi_probable_angle_no = numeric_string_cast<Integer>(input_data[0]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataGeneratorInputReader::set_weight_option(vector<string>& input_data)
{
  if( static_cast<int>(input_data.size()) > 1 )
  {
    string class_name = "AceDataGeneratorInputReader";
    string func_name  = "set_weight_option(vector<string>& input_data)";
    frendy_utils.error_input_data_size_is_larger_than_one(class_name, func_name, input_data);
  }

  string input_data_mod = input_data[0];
  transform(input_data_mod.begin(), input_data_mod.end(), input_data_mod.begin(), ::tolower);
  replace(input_data_mod.begin(), input_data_mod.end(), '-', '_');

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  weight_option                        : " << input_data_mod << endl;
  }

  if( input_data_mod == "variable_weight" || input_data_mod == "variable" )
  {
    weight_option = frendy_utils.variable_weight;
  }
  else if( input_data_mod == "constant_weight" || input_data_mod == "constant" )
  {
    weight_option = frendy_utils.constant_weight;
  }
  else if( input_data_mod == "tabulated_weight" || input_data_mod == "tabulated" ||
           input_data_mod == "table_weight"     || input_data_mod == "table"     )
  {
    weight_option = frendy_utils.tabulated_weight;
  }
  else if( input_data_mod == "default_weight" || input_data_mod == "default" || input_data_mod == "def" )
  {
    weight_option = frendy_utils.get_weight_option_def();
  }
  else
  {
    str_obj.string_check(input_data_mod);
    weight_option = numeric_string_cast<int>(input_data_mod);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataGeneratorInputReader::set_max_thermal_ene(vector<string>& input_data)
{
  if( static_cast<int>(input_data.size()) > 1 )
  {
    string class_name = "AceDataGeneratorInputReader";
    string func_name  = "set_max_thermal_ene(vector<string>& input_data)";
    frendy_utils.error_input_data_size_is_larger_than_one(class_name, func_name, input_data);
  }

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  max_thermal_ene [eV]                 : " << input_data[0] << endl;
  }

  str_obj.string_check(input_data[0]);
  max_thermal_ene = numeric_string_cast<Real>(input_data[0]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataGeneratorInputReader::set_nucl_file_name(string str_data)
{
  vector<string> str_vec;
  str_vec.resize(1);

  str_vec[0] = str_data;
  set_nucl_file_name(str_vec);
}

void AceDataGeneratorInputReader::set_nucl_file_name(vector<string> str_vec)
{
  nucl_file_name = str_vec;

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    for(int i=0; i<static_cast<int>(nucl_file_name.size()); i++)
    {
      if( i==0 )
      {
        cout << "  nucl_file_name                       : " << nucl_file_name[i] << endl;
      }
      else
      {
        cout << "                                       : " << nucl_file_name[i] << endl;
      }
    }
  }

  if( static_cast<int>(ace_file_name.size()) == 0 )
  {
    if( generation_mode != inp_mode_therm )
    {
      mod_ace_file_name_flg = 1;

      int i_max = static_cast<int>(nucl_file_name.size());
      ace_file_name.resize(i_max);
      ace_file_name_fast.resize(i_max);
      for(int i=0; i<i_max; i++)
      {
        StringUtils str_util_obj;
        ace_file_name[i]      = str_util_obj.basename(nucl_file_name[i]) + ".ace";
        ace_file_name_fast[i] = str_util_obj.basename(nucl_file_name[i]) + ".ace";
      }
    }
  }
  if( static_cast<int>(ace_dir_file_name.size()) == 0 )
  {
    if( generation_mode != inp_mode_therm )
    {
      mod_ace_dir_file_name_flg = 1;

      int i_max = static_cast<int>(nucl_file_name.size());
      ace_dir_file_name.resize(i_max);
      ace_dir_file_name_fast.resize(i_max);
      for(int i=0; i<i_max; i++)
      {
        StringUtils str_util_obj;
        ace_dir_file_name[i] = str_util_obj.basename(nucl_file_name[i]) + ".ace.dir";
        ace_dir_file_name_fast[i] = str_util_obj.basename(nucl_file_name[i]) + ".ace.dir";
      }
    }
  }
}

void AceDataGeneratorInputReader::set_nucl_file_name_tsl(string str_data)
{
  nucl_file_name_tsl.resize(1);
  nucl_file_name_tsl[0] = str_data;

  if( static_cast<int>(ace_file_name.size()) == 0 || mod_ace_file_name_flg == 1 )
  {
    StringUtils str_util_obj;

    ace_file_name.resize(1);
    ace_file_name[0] = str_util_obj.basename(nucl_file_name_tsl[0]) + ".ace";
    ace_file_name_therm.resize(1);
    ace_file_name_therm[0] = str_util_obj.basename(nucl_file_name_tsl[0]) + ".ace";
  }
  if( static_cast<int>(ace_dir_file_name.size()) == 0 || mod_ace_dir_file_name_flg == 1 )
  {
    StringUtils str_util_obj;

    ace_dir_file_name.resize(1);
    ace_dir_file_name[0] = str_util_obj.basename(nucl_file_name_tsl[0]) + ".ace.dir";
    ace_dir_file_name_therm.resize(1);
    ace_dir_file_name_therm[0] = str_util_obj.basename(nucl_file_name_tsl[0]) + ".ace.dir";
  }
}

void AceDataGeneratorInputReader::set_ace_file_name(string str_data)
{
  vector<string> str_vec;
  str_vec.resize(1);

  str_vec[0] = str_data;
  set_ace_file_name(str_vec);
}

void AceDataGeneratorInputReader::set_ace_file_name(vector<string> str_data)
{
  ace_file_name = str_data;

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    for(int i=0; i<static_cast<int>(ace_file_name.size()); i++)
    {
      if( i==0 )
      {
        cout << "  ace_file_name                        : " << ace_file_name[i] << endl;
      }
      else
      {
        cout << "                                       : " << ace_file_name[i] << endl;
      }
    }
  }

  mod_ace_file_name_flg = 0;
  if( static_cast<int>(ace_dir_file_name.size()) == 0 || mod_ace_dir_file_name_flg == 1 )
  {
    mod_ace_dir_file_name_flg = 0;

    int i_max = static_cast<int>(ace_file_name.size());
    ace_dir_file_name.resize(i_max);
    for(int i=0; i<i_max; i++)
    {
      ace_dir_file_name[i] = ace_file_name[i] + ".ace.dir";
    }
  }

  ace_file_name_fast  = ace_file_name;
  ace_file_name_therm = ace_file_name;

  ace_dir_file_name_fast  = ace_dir_file_name;
  ace_dir_file_name_therm = ace_dir_file_name;
}

void AceDataGeneratorInputReader::set_ace_dir_file_name(string str_data)
{
  vector<string> str_vec;
  str_vec.resize(1);

  str_vec[0] = str_data;
  set_ace_dir_file_name(str_vec);
}

void AceDataGeneratorInputReader::set_ace_dir_file_name(vector<string> str_data)
{
  ace_dir_file_name = str_data;

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    for(int i=0; i<static_cast<int>(ace_dir_file_name.size()); i++)
    {
      if( i==0 )
      {
        cout << "  ace_dir_file_name                    : " << ace_dir_file_name[i] << endl;
      }
      else
      {
        cout << "                                       : " << ace_dir_file_name[i] << endl;
      }
    }
  }

  mod_ace_dir_file_name_flg = 0;

  ace_dir_file_name_fast  = ace_dir_file_name;
  ace_dir_file_name_therm = ace_dir_file_name;
}

void AceDataGeneratorInputReader::set_ace_label_data(string str_data)
{
  vector<string> str_vec;
  str_vec.resize(1);

  str_vec[0] = str_data;
  set_ace_label_data(str_vec);
}

void AceDataGeneratorInputReader::set_ace_label_data(vector<string> str_vec)
{
  ace_label_data = str_vec;

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    for(int i=0; i<static_cast<int>(ace_label_data.size()); i++)
    {
      if( i==0 )
      {
        cout << "  ace_label_data                       : " << ace_label_data[i] << endl;
      }
      else
      {
        cout << "                                       : " << ace_label_data[i] << endl;
      }
    }
  }
}

void AceDataGeneratorInputReader::set_suffix_id(Real real_data)
{
  suffix_id = real_data;
}

void AceDataGeneratorInputReader::set_iz_aw_data(vector<vector<Real> > real_vec)
{
  iz_aw_data = real_vec;
}


void AceDataGeneratorInputReader::set_cumulative_angle_distribution_format(int int_data)
{
  cumulative_angle_distribution_format = int_data;
}


void AceDataGeneratorInputReader::set_thermal_za_id_name(string str_data)
{
  thermal_za_id_name = str_data;
}

void AceDataGeneratorInputReader::set_inelastic_reaction_type_no(Integer int_data)
{
  inelastic_reaction_type_no = int_data;
}

void AceDataGeneratorInputReader::set_moderator_za_data(vector<Integer> int_vec)
{
  moderator_za_data = int_vec;
}

void AceDataGeneratorInputReader::set_atom_type_no(Integer int_data)
{
  atom_type_no = int_data;
}

void AceDataGeneratorInputReader::set_equi_probable_angle_no(Integer int_data)
{
  equi_probable_angle_no = int_data;
}

void AceDataGeneratorInputReader::set_weight_option(int int_data)
{
  weight_option = int_data;
}

void AceDataGeneratorInputReader::set_max_thermal_ene(Real real_data)
{
  max_thermal_ene = real_data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> AceDataGeneratorInputReader::get_nucl_file_name()
{
  return nucl_file_name;
}

vector<string> AceDataGeneratorInputReader::get_nucl_file_name_tsl()
{
  return nucl_file_name_tsl;
}

vector<string> AceDataGeneratorInputReader::get_ace_file_name()
{
  int i_max = static_cast<int>(nucl_file_name.size());
  if( i_max > 0 )
  {
    if( static_cast<int>(ace_file_name.size()) != i_max )
    {
      ace_file_name.resize(i_max);
    }

    int nucl_no = static_cast<int>(nucl_file_name.size());
    for(int i=0; i<i_max; i++)
    {
      if( static_cast<int>(ace_file_name[i].size()) == 0 && i < nucl_no )
      {
        StringUtils str_util_obj;
        ace_file_name[i] = str_util_obj.basename(nucl_file_name[i]) + ".ace";
      }
    }
  }

  return ace_file_name;
}

vector<string> AceDataGeneratorInputReader::get_ace_file_name_fast()
{
  int i_max = static_cast<int>(nucl_file_name.size());
  if( i_max > 0 )
  {
    if( static_cast<int>(ace_file_name_fast.size()) != i_max )
    {
      ace_file_name_fast.resize(i_max);
    }

    int nucl_no = static_cast<int>(nucl_file_name.size());
    for(int i=0; i<i_max; i++)
    {
      if( static_cast<int>(ace_file_name_fast[i].size()) == 0 && i < nucl_no )
      {
        StringUtils str_util_obj;
        ace_file_name_fast[i] = str_util_obj.basename(nucl_file_name[i]) + ".ace";
      }
    }
  }

  return ace_file_name_fast;
}

vector<string> AceDataGeneratorInputReader::get_ace_file_name_therm()
{
  int i_max = static_cast<int>(nucl_file_name_tsl.size());
  if( i_max > 0 )
  {
    if( static_cast<int>(ace_file_name_therm.size()) != i_max )
    {
      ace_file_name_therm.resize(i_max);
    }

    int nucl_no = static_cast<int>(nucl_file_name_tsl.size());
    for(int i=0; i<i_max; i++)
    {
      if( static_cast<int>(ace_file_name_therm[i].size()) == 0 && i < nucl_no )
      {
        StringUtils str_util_obj;
        ace_file_name_therm[i] = str_util_obj.basename(nucl_file_name_tsl[i]) + ".ace";
      }
    }
  }

  return ace_file_name_therm;
}

vector<string> AceDataGeneratorInputReader::get_ace_dir_file_name()
{
  int i_max = static_cast<int>(nucl_file_name.size());
  if( i_max > 0 )
  {
    if( static_cast<int>(ace_dir_file_name.size()) != i_max )
    {
      ace_dir_file_name.resize(i_max);
    }

    int nucl_no = static_cast<int>(nucl_file_name.size());
    for(int i=0; i<i_max; i++)
    {
      if( static_cast<int>(ace_dir_file_name[i].size()) == 0 && i < nucl_no )
      {
        StringUtils str_util_obj;
        ace_dir_file_name[i] = str_util_obj.basename(nucl_file_name[i]) + ".ace.dir";
      }
    }
  }

  return ace_dir_file_name;
}

vector<string> AceDataGeneratorInputReader::get_ace_dir_file_name_fast()
{
  int i_max = static_cast<int>(nucl_file_name.size());
  if( i_max > 0 )
  {
    if( static_cast<int>(ace_dir_file_name_fast.size()) != i_max )
    {
      ace_dir_file_name_fast.resize(i_max);
    }

    int nucl_no = static_cast<int>(nucl_file_name.size());
    for(int i=0; i<i_max; i++)
    {
      if( static_cast<int>(ace_dir_file_name_fast[i].size()) == 0 && i < nucl_no )
      {
        StringUtils str_util_obj;
        ace_dir_file_name_fast[i] = str_util_obj.basename(nucl_file_name[i]) + ".ace.dir";
      }
    }
  }

  return ace_dir_file_name_fast;
}

vector<string> AceDataGeneratorInputReader::get_ace_dir_file_name_therm()
{
  int i_max = static_cast<int>(nucl_file_name_tsl.size());
  if( i_max > 0 )
  {
    if( static_cast<int>(ace_dir_file_name_therm.size()) != i_max )
    {
      ace_dir_file_name_therm.resize(i_max);
    }

    int nucl_no = static_cast<int>(nucl_file_name.size());
    for(int i=0; i<i_max; i++)
    {
      if( static_cast<int>(ace_dir_file_name_therm[i].size()) == 0 && i < nucl_no )
      {
        StringUtils str_util_obj;
        ace_dir_file_name_therm[i] = str_util_obj.basename(nucl_file_name_tsl[i]) + ".ace.dir";
      }
    }
  }

  return ace_dir_file_name_therm;
}

vector<string> AceDataGeneratorInputReader::get_ace_label_data()
{
  int i_max = static_cast<int>(nucl_file_name.size());
  if( i_max > 0 )
  {
    if( static_cast<int>(ace_label_data.size()) != i_max )
    {
      ace_label_data.resize(i_max);
    }
  }

  return ace_label_data;
}

Real AceDataGeneratorInputReader::get_suffix_id()
{
  return suffix_id;
}

vector<vector<Real> > AceDataGeneratorInputReader::get_iz_aw_data()
{
  return iz_aw_data;
}

int AceDataGeneratorInputReader::get_cumulative_angle_distribution_format()
{
  return cumulative_angle_distribution_format;
}

string AceDataGeneratorInputReader::get_thermal_za_id_name()
{
  return thermal_za_id_name;
}

Integer AceDataGeneratorInputReader::get_inelastic_reaction_type_no()
{
  return inelastic_reaction_type_no;
}

vector<Integer> AceDataGeneratorInputReader::get_moderator_za_data()
{
  return moderator_za_data;
}

Integer AceDataGeneratorInputReader::get_atom_type_no()
{
  return atom_type_no;
}

Integer AceDataGeneratorInputReader::get_equi_probable_angle_no()
{
  return equi_probable_angle_no;
}

int AceDataGeneratorInputReader::get_weight_option()
{
  return weight_option;
}

Real AceDataGeneratorInputReader::get_max_thermal_ene()
{
  return max_thermal_ene;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataGeneratorInputReader::set_print_set_data_flg(vector<string>& input_data)
{
  string class_name = "AceDataGeneratorInputReader";
  string func_name  = "set_print_set_data_flg(vector<string>& input_data)";

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  print_set_data_flg                   : " << input_data[0] << endl;
  }

  print_set_data_flg = frendy_utils.read_print_set_data_flg(class_name, func_name, input_data);
}

void AceDataGeneratorInputReader::set_process_flg(vector<string>& input_data)
{
  string class_name = "AceDataGeneratorInputReader";
  string func_name  = "set_process_flg(vector<string>& input_data)";

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  process_flg                          : " << input_data[0] << endl;
  }

  process_flg = frendy_utils.read_process_flg(class_name, func_name, input_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataGeneratorInputReader::set_print_set_data_flg(int int_val)
{
  frendy_utils.check_print_set_data_flg("AceDataGeneratorInputReader", int_val);

  print_set_data_flg = int_val;
}

void AceDataGeneratorInputReader::set_process_flg(int int_val)
{
  frendy_utils.check_process_flg("AceDataGeneratorInputReader", int_val);

  process_flg = int_val;
}

void AceDataGeneratorInputReader::set_generation_mode(int int_val)
{
  if( int_val != inp_mode_fast && int_val != inp_mode_therm && int_val != inp_mode_dosi )
  {
    string class_name = "AceDataGeneratorInputReader";
    string func_name  = "set_generation_mode(int int_val)";

    ostringstream oss01, oss02, oss03, oss04;
    oss01 << int_val;
    oss02 << inp_mode_fast;
    oss03 << inp_mode_therm;
    oss04 << inp_mode_dosi;

    string str_data01 = "ACE file generation mode that you set : " + oss01.str();
    string str_data02 = "  Fast ACE file generation mode            : " + oss02.str();
    string str_data03 = "  Thermal scatter ACE file generation mode : " + oss03.str();
    string str_data04 = "  Dosimetry ACE file generation mode       : " + oss04.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("ACE file generation mode that you set is not appropriate.");
    err_com.push_back("The available ACE file generation mode is as follows:");
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back("Please modify the ACE file generation mode.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  generation_mode = int_val;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int AceDataGeneratorInputReader::get_print_set_data_flg()
{
  return print_set_data_flg;
}

int AceDataGeneratorInputReader::get_process_flg()
{
  return process_flg;
}

int AceDataGeneratorInputReader::get_generation_mode()
{
  return generation_mode;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

