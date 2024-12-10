#include "FrendyUtils/MultiGroupDataGeneratorInputReader.hpp"

using namespace frendy;

MultiGroupDataGeneratorInputReader::MultiGroupDataGeneratorInputReader(void)
{
  clear();
}

MultiGroupDataGeneratorInputReader::~MultiGroupDataGeneratorInputReader(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

const int MultiGroupDataGeneratorInputReader::process_mode_common;
const int MultiGroupDataGeneratorInputReader::process_mode_neutron;
const int MultiGroupDataGeneratorInputReader::process_mode_tsl;
const int MultiGroupDataGeneratorInputReader::process_mode_gam;

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputReader::clear()
{
  process_tsl_mode_flg = frendy_utils.off;
  process_gam_mode_flg = frendy_utils.off;

  mg_start_file_flg    = frendy_utils.get_mg_start_file_flg_def();

  print_title_flg    = 0;
  print_set_data_flg = frendy_utils.get_print_set_data_flg_def();
  process_flg        = frendy_utils.get_process_flg_def();

  ace_output_flg     = frendy_utils.get_ace_output_flg_def();

  temp_set_flg       = 0;

  inp_check_skip_flg = 0;

  input_file_name.clear();

  nucl_file_name.clear();
  nucl_file_name_tsl.clear();
  ace_file_name.clear();
  ace_file_name_tsl.clear();
  mg_edit_mode.clear();
  mg_edit_mode      = frendy_utils.get_mg_edit_mode_def();
  mg_process_reaction_name.clear();
  mg_ufg_div_mode.clear();
  mg_tsl_data_type.clear();
  mg_flux_calc_mode = frendy_utils.get_mg_flux_calc_mode_def();

  mg_print_reaction.clear();
  mg_mat_list.clear();

  input_file_name.clear();
  mg_start_file_mode         = frendy_utils.get_mg_start_file_mode_def();
  mg_weighting_spectrum_mode = frendy_utils.get_mg_weighting_spectrum_mode_def();
  mg_label_data.clear();

  iwt_no                     = 0;
  mg_weighting_spectrum_el   = frendy_utils.get_mg_weighting_spectrum_el_def();
  mg_weighting_spectrum_eh   = frendy_utils.get_mg_weighting_spectrum_eh_def();
  mg_weighting_fission_temp  = frendy_utils.get_mg_weighting_fission_temp_def();
  mg_weighting_1e_el         = frendy_utils.get_mg_weighting_1e_el_def();
  mg_weighting_1e_eh         = frendy_utils.get_mg_weighting_1e_eh_def();
  temp                       = frendy_utils.get_temp_def();
  max_thermal_ene_e_in       = frendy_utils.get_max_thermal_ene_in_def();
  max_thermal_ene_e_out      = frendy_utils.get_max_thermal_ene_out_def();

  mg_weighting_spectrum_data_e.clear();
  mg_weighting_spectrum_data_w.clear();
  sigma_zero_data            = frendy_utils.get_sigma_zero_data_def();
  sigma_zero_data_auto.clear();
  mg_structure               = frendy_utils.get_mg_structure_def();
  //mg_structure_gam           = frendy_utils.get_mg_structure_def();
  mg_structure_gam.clear();
  mg_structure_auto.clear();
  mg_ufg_structure.clear();
  mg_number_density          = frendy_utils.get_mg_number_density_def();
  mg_flux_calc_w             = frendy_utils.get_mg_flux_calc_w_def();
  mg_flux_calc_eh            = frendy_utils.get_mg_flux_calc_eh_def();
  mg_flux_calc_el            = frendy_utils.get_mg_flux_calc_el_def();
  potential_scat_xs.clear();

  reso_up_scat_0k_data.clear();
  reso_up_scat_mode = reso_up_scat_2d;

  mg_weighting_spectrum_data_int = frendy_utils.get_mg_weighting_spectrum_data_int_def();
  mg_weighting_spectrum_data_nbt = frendy_utils.get_mg_weighting_spectrum_data_nbt_def();
  mg_process_data.clear();
  mg_process_reaction.clear();
  mg_ufg_div_no.clear();

  legendre_order                 = frendy_utils.get_legendre_order_def();
  mg_thermal_xs_treatment        = frendy_utils.get_mg_thermal_xs_treatment_def();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputReader::check_set_data()
{
  if( inp_check_skip_flg == 0 )
  {
    check_start_file_mode();
    check_process_tsl_data();
    check_process_gam_data();

    check_mg_edit_mode();

    check_common_input_output_file_name();
  }

  check_weighting_spectrum();

  check_group_structure();

  if( inp_check_skip_flg == 0 )
  {
    check_flux_calc_mode();

    check_ufg_structure();

    set_mg_file_name_with_mg_edit_mode(mg_edit_mode);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputReader::check_start_file_mode()
{
  string class_name = "MultiGroupDataGeneratorInputReader";
  string func_name  = "check_start_file_mode()";

  string mode_name = mg_start_file_mode;
  transform(mode_name.begin(), mode_name.end(), mode_name.begin(), ::tolower);

  int data_no = 0;
  if( mode_name == "endf" )
  {
    mg_start_file_flg = frendy_utils.start_file_endf;
    data_no = static_cast<int>(nucl_file_name.size());
  }
  else if( mode_name == "ace" )
  {
    mg_start_file_flg = frendy_utils.start_file_ace;
    data_no = static_cast<int>(ace_file_name.size());
  }
  else
  {
    string str_data   = "mg_start_file_mode : " + mg_start_file_mode;

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("Available mg_start_file_mode is ENDF or ACE.");
    err_com.push_back("Please check mg_start_file_mode.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //Check data number of mg_number_density
  if( data_no > 1 )
  {
    if( data_no != static_cast<int>(mg_number_density.size()) )
    {
      vector<string> err_com;
      err_com.push_back("Data number of nucl/ace_file_name is different to that of mg_number_density.");
      err_com.push_back("Please check nucl/ace_file_name or mg_number_density.");
      err_com.push_back("");
      if( mg_start_file_flg == frendy_utils.start_file_endf )
      {
        err_com.push_back("List of nucl_file_name");
        add_data_name_to_error_message(err_com, nucl_file_name);
      }
      else //if( mg_start_file_flg == frendy_utils.start_file_ace )
      {
        err_com.push_back("List of ace_file_name");
        add_data_name_to_error_message(err_com, ace_file_name);
      }
      err_com.push_back("");
      err_com.push_back("List of mg_number_density");

      for(int i=0; i<static_cast<int>(mg_number_density.size()); i++)
      {
        ostringstream oss;
        oss.setf(ios::showpoint);
        oss.setf(ios::scientific);
        oss.width(8);
        oss << mg_number_density[i];
        string str_data = "  " + oss.str();
        err_com.push_back(str_data);
      }
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputReader::check_process_tsl_data()
{
  string class_name = "MultiGroupDataGeneratorInputReader";
  string func_name  = "check_process_tsl_data()";

  if( mg_start_file_flg == frendy_utils.start_file_endf )
  {
    if( static_cast<int>(nucl_file_name_tsl.size()) > 0 )
    {
      process_tsl_mode_flg = frendy_utils.on;
    }
    else
    {
      return;
    }

    if( static_cast<int>(ace_file_name_tsl.size()) > 0 )
    {
      vector<string> err_com;
      err_com.push_back("Data number of ace_file_name_tsl is larger than 0.");
      err_com.push_back("ace_file_name_tsl is not used in this processing.");
      err_com.push_back("");
      err_com.push_back("List of ace_file_name_tsl");
      add_data_name_to_error_message(err_com, ace_file_name_tsl);
      err_obj.output_caution(class_name, func_name, err_com);
    }

    if( static_cast<int>(nucl_file_name_tsl.size()) != static_cast<int>(nucl_file_name.size()) )
    {
      vector<string> err_com;
      err_com.push_back("Data number of nucl_file_name is different to that of nucl_file_name_tsl.");
      err_com.push_back("Please check nucl_file_name or nucl_file_name_tsl.");
      err_com.push_back("");
      err_com.push_back("List of nucl_file_name");
      add_data_name_to_error_message(err_com, nucl_file_name);
      err_com.push_back("");
      err_com.push_back("List of nucl_file_name_tsl");
      add_data_name_to_error_message(err_com, nucl_file_name_tsl);
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    if( static_cast<int>(mg_tsl_data_type.size()) > 0 )
    {
      if( static_cast<int>(mg_tsl_data_type.size()) != static_cast<int>(nucl_file_name_tsl.size()) )
      {
        vector<string> err_com;
        err_com.push_back("Data number of mg_tsl_data_type is different to that of nucl_file_name_tsl.");
        err_com.push_back("mg_tsl_data_type is automatically set by FRENDY.");
        err_com.push_back("");
        err_com.push_back("List of nucl_file_name_tsl");
        add_data_name_to_error_message(err_com, nucl_file_name_tsl);
        err_com.push_back("");
        err_com.push_back("List of mg_tsl_data_type");
        add_data_name_to_error_message(err_com, mg_tsl_data_type);
        err_obj.output_caution(class_name, func_name, err_com);
      }
    }
  }

  if( mg_start_file_flg == frendy_utils.start_file_ace )
  {
    if( static_cast<int>(ace_file_name_tsl.size()) > 0 )
    {
      process_tsl_mode_flg = frendy_utils.on;
    }
    else
    {
      return;
    }

    if( static_cast<int>(nucl_file_name_tsl.size()) > 0 )
    {
      vector<string> err_com;
      err_com.push_back("Data number of ace_file_name_tsl is larger than 0.");
      err_com.push_back("nucl_file_name_tsl is not used in this processing.");
      err_com.push_back("");
      err_com.push_back("List of nucl_file_name_tsl");
      add_data_name_to_error_message(err_com, nucl_file_name_tsl);
      err_obj.output_caution(class_name, func_name, err_com);
    }

    if( static_cast<int>(ace_file_name_tsl.size()) != static_cast<int>(ace_file_name.size()) )
    {
      vector<string> err_com;
      err_com.push_back("Data number of ace_file_name is different to that of ace_file_name_tsl.");
      err_com.push_back("Please check ace_file_name or ace_file_name_tsl.");
      err_com.push_back("");
      err_com.push_back("List of ace_file_name");
      add_data_name_to_error_message(err_com, ace_file_name);
      err_com.push_back("");
      err_com.push_back("List of ace_file_name_tsl");
      add_data_name_to_error_message(err_com, ace_file_name_tsl);
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    if( static_cast<int>(mg_tsl_data_type.size()) > 0 )
    {
      if( static_cast<int>(mg_tsl_data_type.size()) != static_cast<int>(ace_file_name_tsl.size()) )
      {
        vector<string> err_com;
        err_com.push_back("Data number of mg_tsl_data_type is different to that of ace_file_name_tsl.");
        err_com.push_back("mg_tsl_data_type is automatically set by FRENDY.");
        err_com.push_back("");
        err_com.push_back("List of ace_file_name_tsl");
        add_data_name_to_error_message(err_com, ace_file_name_tsl);
        err_com.push_back("");
        err_com.push_back("List of mg_tsl_data_type");
        add_data_name_to_error_message(err_com, mg_tsl_data_type);
        err_obj.output_caution(class_name, func_name, err_com);
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputReader::check_process_gam_data()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputReader::check_mg_edit_mode()
{
  vector<string> mg_mode_list;
  mg_mode_list.resize(34);
  mg_mode_list[ 0] = "all";
  mg_mode_list[ 1] = "default";
  mg_mode_list[ 2] = "1dxs";
  mg_mode_list[ 3] = "2dxs";
  mg_mode_list[ 4] = "nuchi";
  mg_mode_list[ 5] = "mgflux";
  mg_mode_list[ 6] = "ufg";
  mg_mode_list[ 7] = "ufg1dxs";
  mg_mode_list[ 8] = "ufg1dxsinputgrid";
  mg_mode_list[ 9] = "kramxs";
  mg_mode_list[10] = "matxs";
  mg_mode_list[11] = "fullmatxs";
  mg_mode_list[12] = "simplematxs";
  mg_mode_list[13] = "gendf";
  mg_mode_list[14] = "fullgendf";
  mg_mode_list[15] = "simplegendf";
  mg_mode_list[16] = "debug";
  mg_mode_list[17] = "skipprintout";
  mg_mode_list[18] = "default";
  mg_mode_list[19] = "-1dxs";
  mg_mode_list[20] = "-2dxs";
  mg_mode_list[21] = "-nuchi";
  mg_mode_list[22] = "-mgflux";
  mg_mode_list[23] = "-ufg";
  mg_mode_list[24] = "-ufg1dxs";
  mg_mode_list[25] = "-ufg1dxsinputgrid";
  mg_mode_list[26] = "-kramxs";
  mg_mode_list[27] = "-matxs";
  mg_mode_list[28] = "-fullmatxs";
  mg_mode_list[29] = "-simplematxs";
  mg_mode_list[30] = "-gendf";
  mg_mode_list[31] = "-fullgendf";
  mg_mode_list[32] = "-simplegendf";
  mg_mode_list[33] = "ruc"; //resonance upscattering correction

  vector<string> mg_mode_list_add;
  mg_mode_list_add.resize(5);
  mg_mode_list_add[0] = "1dxs";
  mg_mode_list_add[1] = "2dxs";
  mg_mode_list_add[2] = "ufg1dxs";
  mg_mode_list_add[3] = "ufg1dxsinputgrid";
  mg_mode_list_add[4] = "kramxs";

  vector<string> kram_list;
  kram_list.resize(3);
  kram_list[0] = "micro";
  kram_list[1] = "macro";
  kram_list[2] = "currentweighttotalxs";

  int i_max  = static_cast<int>(mg_edit_mode.size());
  int j_max  = static_cast<int>(mg_mode_list.size());
  int add_no = static_cast<int>(mg_mode_list_add.size());

  int skip_print_flg = 0;
  vector<string> mg_edit_mode_mod;
  for(int i=0; i<i_max; i++)
  {
    string mode_name = mg_edit_mode[i];
    transform(mode_name.begin(), mode_name.end(), mode_name.begin(), ::tolower);

    int mode_find_flg = 0;
    for(int j=0; j<j_max; j++)
    {
      if( static_cast<int>(mode_name.find(mg_mode_list[j])) == 0 )
      {
        if( j == 17 ) //mg_mode_list[17] = "skipprintout";
        {
          skip_print_flg = 1;
        }

        mode_find_flg = 1;
        break;
      }
    }

    if( mode_find_flg == 0 )
    {
      string class_name = "MultiGroupDataGeneratorInputReader";
      string func_name  = "check_mg_edit_mode()";

      vector<string> err_com;
      string str_data = "mg_edit_mode : " + mg_edit_mode[i];
      err_com.push_back(str_data);
      err_com.push_back("This mg_edit_mode name is not available.");
      err_com.push_back("");
      err_com.push_back("List of available mg_edit_mode");
      add_data_name_to_error_message(err_com, mg_mode_list);
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    string edit_xs_tmp = mg_edit_mode[i];
    for(int k=0; k<add_no; k++)
    {
      if( static_cast<int>(mode_name.find(mg_mode_list_add[k])) == 0 && i+1 < i_max )
      {
        mode_find_flg = 0;
        while( mode_find_flg == 0 )
        {
          for(int j=0; j<j_max; j++)
          {
            string mode_name_tmp = mg_edit_mode[i+1];
            transform(mode_name_tmp.begin(), mode_name_tmp.end(), mode_name_tmp.begin(), ::tolower);
            if( static_cast<int>(mode_name_tmp.find(mg_mode_list[j])) == 0 )
            {
              mode_find_flg = 1;
              break;
            }
          }

          if( mode_find_flg == 0 )
          {
            if( k == 4 ) //mg_mode_list_add[4] = "kramxs";
            {
              string mode_name_tmp = mg_edit_mode[i+1];
              transform(mode_name_tmp.begin(), mode_name_tmp.end(), mode_name_tmp.begin(), ::tolower);
              if( mode_name_tmp != kram_list[0] &&  //kram_list[0] = "micro";
                  mode_name_tmp != kram_list[1] &&  //kram_list[1] = "macro";
                  mode_name_tmp != kram_list[2] )   //kram_list[2] = "currentweighttotalxs";
              {
                string class_name = "MultiGroupDataGeneratorInputReader";
                string func_name  = "check_mg_edit_mode()";

                vector<string> err_com;
                string str_data = "mg_edit_mode : " + edit_xs_tmp + " " + mg_edit_mode[i+1];
                err_com.push_back(str_data);
                err_com.push_back("kramxs option is only available for following data.");
                for(int l=0; l<static_cast<int>(kram_list.size()); l++)
                {
                  err_com.push_back("  " + kram_list[l]);
                }
                err_obj.output_runtime_error(class_name, func_name, err_com);
              }
            } 

            edit_xs_tmp = edit_xs_tmp + " " + mg_edit_mode[i+1];
            i++;

            if( i+1 >= i_max )
            {
              mode_find_flg = 1;
              break;
            }
          }
        }
      }
    }
    mg_edit_mode_mod.push_back(edit_xs_tmp);
  }

  //Add skipprintout
  if( skip_print_flg == 0 )
  {
    mg_edit_mode_mod.push_back("SkipPrintout"); 
  }

  mg_edit_mode = mg_edit_mode_mod;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputReader::check_common_input_output_file_name()
{
  string class_name = "MultiGroupDataGeneratorInputReader";
  string func_name  = "check_common_input_output_file_name()";

  if( mg_start_file_flg == frendy_utils.start_file_endf &&
      static_cast<int>(ace_file_name.size())  >  0      &&
      static_cast<int>(nucl_file_name.size()) == 0 )
  {
    vector<string> err_com;
    err_com.push_back("Data number of nucl_file_name is 0.");
    err_com.push_back("Data number of ace_file_name is larger than 0.");
    err_com.push_back("The mg_start_file_mode parameter is modified from ENDF to ACE.");
    err_obj.output_caution(class_name, func_name, err_com);

    mg_start_file_flg = frendy_utils.start_file_ace;
  }
  else if( mg_start_file_flg == frendy_utils.start_file_ace &&
           static_cast<int>(ace_file_name.size())  == 0      &&
           static_cast<int>(nucl_file_name.size()) >  0 )
  {
    vector<string> err_com;
    err_com.push_back("Data number of ace_file_name is 0.");
    err_com.push_back("Data number of nucl_file_name is larger than 0.");
    err_com.push_back("The mg_start_file_mode parameter is modified from ACE to ENDF.");
    err_obj.output_caution(class_name, func_name, err_com);

    mg_start_file_flg = frendy_utils.start_file_ace;
  }

  if( mg_start_file_flg == frendy_utils.start_file_endf )
  {
    if( static_cast<int>(ace_file_name.size()) > 0 )
    {
      vector<string> err_com;
      err_com.push_back("Data number of ace_file_name is larger than 0.");
      err_com.push_back("ace_file_name is not used in this processing.");
      err_com.push_back("");
      err_com.push_back("List of ace_file_name");
      add_data_name_to_error_message(err_com, ace_file_name);
      err_obj.output_caution(class_name, func_name, err_com);
    }

    if( static_cast<int>(nucl_file_name.size()) == 0 )
    {
      vector<string> err_com;
      err_com.push_back("Data number of nucl_file_name is 0.");
      err_com.push_back("Please set nucl_file_name.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    if( static_cast<int>(potential_scat_xs.size()) > 0 )
    {
      if( static_cast<int>(potential_scat_xs.size()) != static_cast<int>(nucl_file_name.size()) )
      {
        vector<string> err_com;
        err_com.push_back("Data number of potential_scat_xs is different to that of nucl_file_name.");
        err_com.push_back("");
        err_com.push_back("List of nucl_file_name");
        add_data_name_to_error_message(err_com, nucl_file_name);
        err_com.push_back("");
        err_com.push_back("List of potential_scat_xs");
        for(int i=0; i<static_cast<int>(potential_scat_xs.size()); i++)
        {
          ostringstream oss;
          oss.setf(ios::showpoint);
          oss.setf(ios::scientific);
          oss.width(8);
          oss << potential_scat_xs[i];
          string str_data = "  " + oss.str();
          err_com.push_back(str_data);
        }
        err_obj.output_runtime_error(class_name, func_name, err_com);
      }
    }

    if( static_cast<int>(mg_mat_list.size()) > 0 )
    {
      vector<string> err_com;
      if( static_cast<int>(mg_mat_list.size()) != static_cast<int>(nucl_file_name.size()) )
      {
        err_com.push_back("Data number of mg_mat_list is different to that of nucl_file_name.");
      }
      else
      {
        err_com.push_back("This input option (mg_mat_list) modifies material number in the GENDF file.");
        err_com.push_back("If you do not set the mg_mat_list option, the matrial number is automatically");
        err_com.push_back("set from the ENDF file.");
        err_com.push_back("Please remove this option if user do not want to modify the material number.");
      }
      err_com.push_back("");
      err_com.push_back("List of nucl_file_name");
      add_data_name_to_error_message(err_com, nucl_file_name);
      err_com.push_back("");
      err_com.push_back("List of mg_mat_list");
      for(int i=0; i<static_cast<int>(mg_mat_list.size()); i++)
      {
        ostringstream oss;
        oss << mg_mat_list[i];
        string str_data = "  " + oss.str();
        err_com.push_back(str_data);
      }

      if( static_cast<int>(mg_mat_list.size()) != static_cast<int>(nucl_file_name.size()) )
      {
        err_obj.output_runtime_error(class_name, func_name, err_com);
      }
      else
      {
        err_obj.output_caution(class_name, func_name, err_com);
      }
    }

    if( static_cast<int>(reso_up_scat_0k_data.size()) > 0 )
    {
      if( static_cast<int>(reso_up_scat_0k_data.size()) != static_cast<int>(nucl_file_name.size()) )
      {
        vector<string> err_com;
        err_com.push_back("Data number of reso_up_scat_0k_data is different to that of nucl_file_name.");

        err_com.push_back("");
        err_com.push_back("List of nucl_file_name");
        add_data_name_to_error_message(err_com, nucl_file_name);
        err_com.push_back("");
        err_com.push_back("List of reso_up_scat_0k_data");
        add_data_name_to_error_message(err_com, reso_up_scat_0k_data);

        err_obj.output_runtime_error(class_name, func_name, err_com);
      }
    }
  }

  if( mg_start_file_flg == frendy_utils.start_file_ace )
  {
    if( static_cast<int>(nucl_file_name.size()) > 0 )
    {
      vector<string> err_com;
      err_com.push_back("Data number of nucl_file_name is larger than 0.");
      err_com.push_back("nucl_file_name is not used in this processing.");
      err_com.push_back("");
      err_com.push_back("List of nucl_file_name");
      add_data_name_to_error_message(err_com, nucl_file_name);
      err_obj.output_caution(class_name, func_name, err_com);
    }

    if( static_cast<int>(ace_file_name.size()) == 0 )
    {
      vector<string> err_com;
      err_com.push_back("Data number of ace_file_name is 0.");
      err_com.push_back("Please set ace_file_name.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    if( static_cast<int>(potential_scat_xs.size()) > 0 )
    {
      if( static_cast<int>(potential_scat_xs.size()) != static_cast<int>(ace_file_name.size()) )
      {
        vector<string> err_com;
        err_com.push_back("Data number of potential_scat_xs is different to that of ace_file_name.");
        err_com.push_back("");
        err_com.push_back("List of ace_file_name");
        add_data_name_to_error_message(err_com, ace_file_name);
        err_com.push_back("");
        err_com.push_back("List of potential_scat_xs");
        for(int i=0; i<static_cast<int>(potential_scat_xs.size()); i++)
        {
          ostringstream oss;
          oss.setf(ios::showpoint);
          oss.setf(ios::scientific);
          oss.width(8);
          oss << potential_scat_xs[i];
          string str_data = "  " + oss.str();
          err_com.push_back(str_data);
        }
        err_obj.output_runtime_error(class_name, func_name, err_com);
      }
    }

    if( static_cast<int>(mg_mat_list.size()) > 0 )
    {
      if( static_cast<int>(mg_mat_list.size()) != static_cast<int>(ace_file_name.size()) )
      {
        vector<string> err_com;
        err_com.push_back("Data number of mg_mat_list is different to that of ace_file_name.");
        err_com.push_back("");
        err_com.push_back("List of ace_file_name");
        add_data_name_to_error_message(err_com, ace_file_name);
        err_com.push_back("");
        err_com.push_back("List of mg_mat_list");
        for(int i=0; i<static_cast<int>(mg_mat_list.size()); i++)
        {
          ostringstream oss;
          oss << mg_mat_list[i];
          string str_data = "  " + oss.str();
          err_com.push_back(str_data);
        }
        err_obj.output_runtime_error(class_name, func_name, err_com);
      }
    }
    else
    {
      vector<string> err_com;
      err_com.push_back("Data number of mg_mat_list is zero.");
      err_com.push_back("The MAT number in the header of the ACE file is used for the MAT number of the GENDF file.");
      err_com.push_back("The MAT number of the GENDF file might be 0 if user do not set the material number.");
      //err_com.push_back("Please use the mg_mat_list option to set the material number.");
      err_obj.output_caution(class_name, func_name, err_com);
    }

    if( static_cast<int>(reso_up_scat_0k_data.size()) > 0 )
    {
      if( static_cast<int>(reso_up_scat_0k_data.size()) != static_cast<int>(ace_file_name.size()) )
      {
        vector<string> err_com;
        err_com.push_back("Data number of reso_up_scat_0k_data is different to that of ace_file_name.");
        err_com.push_back("");
        err_com.push_back("List of ace_file_name");
        add_data_name_to_error_message(err_com, ace_file_name);
        err_com.push_back("");
        err_com.push_back("List of reso_up_scat_0k_data");
        add_data_name_to_error_message(err_com, reso_up_scat_0k_data);

        err_obj.output_runtime_error(class_name, func_name, err_com);
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputReader::check_weighting_spectrum()
{
  string class_name = "MultiGroupDataGeneratorInputReader";
  string func_name  = "check_weighting_spectrum()";


  //Check max_thermal_ene_e_in and max_thermal_ene_e_out
  if( max_thermal_ene_e_in > max_thermal_ene_e_out )
  {
    vector<string> err_com;
    ostringstream oss01, oss02, oss03, oss04, oss05;
    oss01 << max_thermal_ene_e_in;
    oss02 << max_thermal_ene_e_out;
    string str_data01 = "max_thermal_ene_e_in  : " + oss01.str();
    string str_data02 = "max_thermal_ene_e_out : " + oss02.str();
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);

    err_com.push_back("");
    err_com.push_back("max_thermal_ene_e_in is larger than max_thermal_ene_e_out.");
    err_com.push_back("max_thermal_ene_e_out is modified to max_thermal_ene_e_in.");
    err_obj.output_caution(class_name, func_name, err_com);

    max_thermal_ene_e_out = max_thermal_ene_e_in;
  }

  //Check mg_weighting_spectrum_mode and mg_weighting_spectrum_data
  vector<string> spectrum_mode_list;
  spectrum_mode_list.push_back("1/e");
  spectrum_mode_list.push_back("fission+1/e+maxwell");

  int i_max = static_cast<int>(spectrum_mode_list.size());

  string mode_name = mg_weighting_spectrum_mode;
  transform(mode_name.begin(), mode_name.end(), mode_name.begin(), ::tolower);

  int mode_find_flg = 0;
  for(int i=0; i<i_max; i++)
  {
    if( mode_name == spectrum_mode_list[i] )
    {
      mode_find_flg = 1;
      break;
    }
  } 

  int weight_no = static_cast<int>(mg_weighting_spectrum_data_e.size());
  if( weight_no > 0 )
  {
    mg_weighting_spectrum_mode.clear();
  }
  else //if( weight_no == 0 )
  {
    if( mode_find_flg == 0 )
    {
      vector<string> err_com;
      string str_data = "mg_weighting_spectrum_mode : " + mg_weighting_spectrum_mode;
      err_com.push_back(str_data);
      err_com.push_back("This mg_weighting_spectrum_mode name is not available.");
      err_com.push_back("");
      err_com.push_back("List of available mg_weighting_spectrum_mode");
      add_data_name_to_error_message(err_com, spectrum_mode_list);
      err_obj.output_runtime_error(class_name, func_name, err_com);
    } 
  } 


  //Check mg_weighting_spectrum_el, mg_weighting_spectrum_eh, mg_weighting_fission_temp,
  //       mg_weighting_1e_el and mg_weighting_1e_eh
  int minus_flg = 0;
  if( mg_weighting_spectrum_el < 0.0 || mg_weighting_spectrum_eh < 0.0  ||
      mg_weighting_fission_temp < 0.0 || mg_weighting_1e_el < 0.0  || mg_weighting_1e_eh < 0.0 )
  {
    minus_flg = 1;
  }

  int spectrum_order_flg = 0;
  if( mg_weighting_spectrum_el > mg_weighting_spectrum_eh )
  {
    spectrum_order_flg = 1;
  }

  int e_order_flg = 0;
  if( mg_weighting_1e_el > mg_weighting_1e_eh )
  {
    e_order_flg = 1;
  }

  if( minus_flg > 0 || spectrum_order_flg > 0 || e_order_flg > 0 )
  {
    vector<string> err_com;
    ostringstream oss01, oss02, oss03, oss04, oss05;
    oss01 << mg_weighting_spectrum_el;
    oss02 << mg_weighting_spectrum_eh;
    oss03 << mg_weighting_fission_temp;
    oss04 << mg_weighting_1e_el;
    oss05 << mg_weighting_1e_eh;
    string str_data01 = "mg_weighting_spectrum_el  : " + oss01.str();
    string str_data02 = "mg_weighting_spectrum_eh  : " + oss02.str();
    string str_data03 = "mg_weighting_fission_temp : " + oss03.str();
    string str_data04 = "mg_weighting_1e_el        : " + oss04.str();
    string str_data05 = "mg_weighting_1e_eh        : " + oss05.str();
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back(str_data05);

    if( minus_flg > 0 )
    {
      err_com.push_back("");
      err_com.push_back("These values must be larger than 0.0.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    if( spectrum_order_flg > 0 )
    {
      err_com.push_back("");
      err_com.push_back("mg_weighting_spectrum_el is larger than mg_weighting_spectrum_eh.");
      err_com.push_back("These values are transposed.");
      err_com.push_back("(mg_weighting_spectrum_el <-> mg_weighting_spectrum_eh)");

      Real el_val = mg_weighting_spectrum_eh;
      Real eh_val = mg_weighting_spectrum_el;
      mg_weighting_spectrum_el = el_val;
      mg_weighting_spectrum_eh = eh_val;
    }

    if( e_order_flg > 0 )
    {
      err_com.push_back("");
      err_com.push_back("mg_weighting_1e_el is larger than mg_weighting_1e_eh.");
      err_com.push_back("These values are transposed.");
      err_com.push_back("(mg_weighting_1e_el <-> mg_weighting_1e_eh)");

      Real el_val = mg_weighting_1e_eh;
      Real eh_val = mg_weighting_1e_el;
      mg_weighting_1e_el = el_val;
      mg_weighting_1e_eh = eh_val;
    }
    err_obj.output_caution(class_name, func_name, err_com);
  }


  //Check mg_weighting_spectrum_data_nbt and mg_weighting_spectrum_data_int
  i_max = static_cast<int>(mg_weighting_spectrum_data_int.size());
  if( i_max == 1 )
  {
    mg_weighting_spectrum_data_nbt = frendy_utils.get_mg_weighting_spectrum_data_nbt_def();
  }

  if( mg_weighting_spectrum_data_nbt[i_max-1] < static_cast<int>(mg_weighting_spectrum_data_e.size()) )
  {
    vector<string> err_com;
    ostringstream oss01, oss02;
    oss01 << mg_weighting_spectrum_data_nbt[i_max-1];
    oss02 << static_cast<int>(mg_weighting_spectrum_data_e.size());

    string str_data01 = "mg_weighting_spectrum_data_nbt[i_max-1] : " + oss01.str();
    string str_data02 = "Number of mg_weighting_spectrum_data    : " + oss02.str();

    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("mg_weighting_spectrum_data_nbt[i_max-1] is less than the number of mg_weighting_spectrum_data.");
    err_com.push_back("mg_weighting_spectrum_data_nbt[i_max-1] is modified to cover all data of mg_weighting_spectrum_data.");
    err_obj.output_caution(class_name, func_name, err_com);

    mg_weighting_spectrum_data_nbt[i_max-1] = frendy_utils.get_mg_weighting_spectrum_data_nbt_def()[0];
  }

  for(int i=0; i<i_max; i++)
  {
    if( mg_weighting_spectrum_data_int[i] != int_const   &&
        mg_weighting_spectrum_data_int[i] != int_lin_lin &&
        mg_weighting_spectrum_data_int[i] != int_log_lin &&
        mg_weighting_spectrum_data_int[i] != int_lin_log &&
        mg_weighting_spectrum_data_int[i] != int_log_log )
    {
      vector<string> err_com;
      ostringstream oss;
      oss << mg_weighting_spectrum_data_int[i];
      string str_data = "Interpolation type : " + oss.str();
      err_com.push_back(str_data);
      err_com.push_back("Interpolation type of mg_weighting_spectrum_data_int is not available.");
      err_com.push_back("Available interpolation type is as follows:");
      err_com.push_back("  constant      : 1");
      err_com.push_back("  linear-linear : 2");
      err_com.push_back("  log-linear    : 3");
      err_com.push_back("  linear-log    : 4");
      err_com.push_back("  log-log       : 5");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputReader::check_group_structure()
{
  string class_name = "MultiGroupDataGeneratorInputReader";
  string func_name  = "check_group_structure()";

  //Check mg_structure
  int i_max = static_cast<int>(mg_structure.size());
  if( i_max == 0 )
  {
    if( static_cast<int>(mg_structure_auto.size()) == 0 )
    {
      mg_structure = frendy_utils.get_mg_structure_def();
      i_max = static_cast<int>(mg_structure.size());
    }
  }

  int minus_flg = 0;
  for(int i=0; i<i_max; i++)
  {
    if( mg_structure[i] < min_value )
    {
      minus_flg = 1;
      break;
    }
  }

  if( minus_flg > 0 )
  {
    vector<string> err_com;
    err_com.push_back("mg_structure must be larger than 0.0.");
    err_com.push_back("");
    err_com.push_back("List of mg_structure");
    for(int i=0; i<i_max; i++)
    {
      ostringstream oss;
      oss.setf(ios::showpoint);
      oss.setf(ios::scientific);
      oss.width(8);
      oss << mg_structure[i];
      string str_data = "  " + oss.str();
      err_com.push_back(str_data);
    }
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }




  vector<string> ufg_div_mode_list;
  ufg_div_mode_list.push_back("el");
  ufg_div_mode_list.push_back("ee");

      i_max = static_cast<int>(mg_ufg_div_mode.size());
  int j_max = static_cast<int>(ufg_div_mode_list.size());
  for(int i=0; i<i_max; i++)
  {
    string mode_name = mg_ufg_div_mode[i];
    transform(mode_name.begin(), mode_name.end(), mode_name.begin(), ::tolower);

    int mode_find_flg = 0;
    for(int j=0; j<j_max; j++)
    {
      if( mode_name == ufg_div_mode_list[j] )
      {
        mode_find_flg = 1;
        break;
      }
    }

    if( mode_find_flg == 0 )
    {
      vector<string> err_com;
      string str_data = "mg_ufg_div_mode : " + mg_ufg_div_mode[i];
      err_com.push_back(str_data);
      err_com.push_back("This mg_ufg_div_mode name is not available.");
      err_com.push_back("");
      err_com.push_back("List of available mg_ufg_div_mode");
      add_data_name_to_error_message(err_com, ufg_div_mode_list);
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    if( mg_ufg_div_no[i] < 0 )
    {
      vector<string> err_com;
      err_com.push_back("mg_ufg_div_no must be larger than 0.");
      err_com.push_back("");
      err_com.push_back("List of mg_ufg_div_no");
      for(int j=0; j<i_max; j++)
      {
        ostringstream oss;
        oss << mg_ufg_div_no[j];
        string str_data = "  " + oss.str();
        err_com.push_back(str_data);
      }
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputReader::check_flux_calc_mode()
{
  string class_name = "MultiGroupDataGeneratorInputReader";
  string func_name  = "check_flux_calc_mode()";

  //Check mg_flux_calc_mode
  vector<string> flux_mode_list;
  flux_mode_list.push_back("nr");
  flux_mode_list.push_back("sld");

  int i_max = static_cast<int>(mg_flux_calc_mode.size());
  int j_max = static_cast<int>(flux_mode_list.size());
  for(int i=0; i<i_max; i++)
  {
    string mode_name = mg_flux_calc_mode[i];
    transform(mode_name.begin(), mode_name.end(), mode_name.begin(), ::tolower);

    int mode_find_flg = 0;
    for(int j=0; j<j_max; j++)
    {
      if( mode_name == flux_mode_list[j] )
      {
        mode_find_flg = 1;
        break;
      }
    }

    if( mode_find_flg == 0 )
    {
      vector<string> err_com;
      string str_data = "mg_flux_calc_mode : " + mg_flux_calc_mode[i];
      err_com.push_back(str_data);
      err_com.push_back("This mg_flux_calc_mode name is not available.");
      err_com.push_back("");
      err_com.push_back("List of available mg_flux_calc_mode");
      add_data_name_to_error_message(err_com, flux_mode_list);
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }

  if( i_max == 0 )
  {
    i_max = 1;
    mg_flux_calc_mode = frendy_utils.get_mg_flux_calc_mode_def();
  }


  //Check mg_flux_calc_w_eh_el
  i_max = static_cast<int>(mg_flux_calc_mode.size());

  vector<int> ele_no_vec;
  ele_no_vec.resize(3);
  ele_no_vec[0] = static_cast<int>(mg_flux_calc_w.size());
  ele_no_vec[1] = static_cast<int>(mg_flux_calc_el.size());
  ele_no_vec[2] = static_cast<int>(mg_flux_calc_eh.size());

  for(int m=0; m<static_cast<int>(ele_no_vec.size()); m++)
  {
    if( i_max != ele_no_vec[m] && ele_no_vec[m] > 0 )
    {
      i_max = static_cast<int>(mg_flux_calc_mode.size());

      vector<string> err_com;
      err_com.push_back("Data number of mg_flux_calc_mode is smaller than that of");
      err_com.push_back("mg_flux_calc_w/mg_flux_calc_el/mg_flux_calc_eh.");
      err_com.push_back("mg_flux_calc_mode is modified.");
      err_com.push_back("");
      err_com.push_back("List of mg_flux_calc_mode (modified)");
      add_data_name_to_error_message(err_com, mg_flux_calc_mode);
      err_com.push_back("");

      vector<Real> real_vec;
      if( m==0 )
      {
        err_com.push_back("List of mg_flux_calc_w");
        real_vec = mg_flux_calc_w;
      }
      else if( m==1 )
      {
        err_com.push_back("List of mg_flux_calc_el");
        real_vec = mg_flux_calc_el;
      }
      else if( m==2 )
      {
        err_com.push_back("List of mg_flux_calc_eh");
        real_vec = mg_flux_calc_eh;
      }
      for(int j=0; j<ele_no_vec[m]; j++)
      {
        ostringstream oss;
        oss.precision(8);
        oss.setf(ios::showpoint);
        oss.setf(ios::scientific);
        oss << real_vec[j];
        string str_data = "  " + oss.str();
        err_com.push_back(str_data);
      }
      err_obj.output_caution(class_name, func_name, err_com);
    }
  }

  for(int m=0; m<static_cast<int>(ele_no_vec.size()); m++)
  {
    if( i_max > ele_no_vec[m] && ele_no_vec[m] > 0 )
    {
      for(int i=ele_no_vec[m]; i<i_max; i++)
      {
        if( m==0 )
        {
          mg_flux_calc_w.push_back(frendy_utils.get_mg_flux_calc_w_def()[0]);
        }
        else if( m==1 )
        {
          mg_flux_calc_el.push_back(frendy_utils.get_mg_flux_calc_el_def()[0]);
        }
        else if( m==2 )
        {
          mg_flux_calc_eh.push_back(frendy_utils.get_mg_flux_calc_eh_def()[0]);
        }
      }

      vector<string> err_com;
      err_com.push_back("Data number of mg_flux_calc_mode is larger than that of");
      err_com.push_back("mg_flux_calc_w/mg_flux_calc_el/mg_flux_calc_eh.");
      err_com.push_back("mg_flux_calc_w/mg_flux_calc_el/mg_flux_calc_eh is modified.");
      err_com.push_back("");
      err_com.push_back("List of mg_flux_calc_mode");
      add_data_name_to_error_message(err_com, mg_flux_calc_mode);
      err_com.push_back("");

      vector<Real> real_vec;
      if( m==0 )
      {
        err_com.push_back("List of mg_flux_calc_w (modified)");
        real_vec = mg_flux_calc_w;
      }
      else if( m==1 )
      {
        err_com.push_back("List of mg_flux_calc_el (modified)");
        real_vec = mg_flux_calc_el;
      }
      else if( m==2 )
      {
        err_com.push_back("List of mg_flux_calc_eh (modified)");
        real_vec = mg_flux_calc_eh;
      }
      for(int j=0; j<i_max; j++)
      {
        ostringstream oss;
        oss.precision(8);
        oss.setf(ios::showpoint);
        oss.setf(ios::scientific);
        oss << real_vec[j];
        string str_data = "  " + oss.str();
        err_com.push_back(str_data);
      }
      err_obj.output_caution(class_name, func_name, err_com);
    }
  }


  //Check value and order of el and eh
  int flux_calc_e_order_flg = 0;
  int minus_flg             = 0;
      i_max                 = static_cast<int>(mg_flux_calc_el.size());
  for(int i=0; i<i_max; i++)
  {
    if( mg_flux_calc_el[i] > mg_flux_calc_eh[i])
    {
      flux_calc_e_order_flg = 1;
      Real el_val = mg_flux_calc_eh[i];
      Real eh_val = mg_flux_calc_el[i];
      mg_flux_calc_el[i] = el_val;
      mg_flux_calc_eh[i] = eh_val;
    }

    if( mg_flux_calc_el[i] < 0.0 || mg_flux_calc_eh[i] < 0.0 )
    {
      minus_flg = 1;
    }
  }

  if( minus_flg > 0 || flux_calc_e_order_flg > 0 )
  {
    vector<string> err_com;
    if( minus_flg > 0 )
    {
      err_com.push_back("mg_flux_calc_el and mg_flux_calc_eh must be larger than 0.0.");
    }
    if( flux_calc_e_order_flg > 0 )
    {
      err_com.push_back("mg_flux_calc_el is larger than mg_flux_calc_eh.");
      err_com.push_back("These values are transposed.");
      err_com.push_back("(mg_flux_calc_el <-> mg_flux_calc_eh)");
      err_com.push_back("");
      err_com.push_back("List of modified mg_flux_calc_el / mg_flux_calc_eh");
    }

    for(int i=0; i<i_max; i++)
    {
      ostringstream oss01, oss02;
      oss01.precision(8);
      oss01.setf(ios::showpoint);
      oss01.setf(ios::scientific);
      oss02.precision(8);
      oss02.setf(ios::showpoint);
      oss02.setf(ios::scientific);
      oss01 << mg_flux_calc_el[i];
      oss02 << mg_flux_calc_eh[i];
      string str_data = "  " + oss01.str() + " / " + oss02.str();
      err_com.push_back(str_data);
    }

    if( minus_flg > 0 )
    {
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
    else if( flux_calc_e_order_flg > 0 )
    {
      err_obj.output_caution(class_name, func_name, err_com);
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputReader::check_ufg_structure()
{
  string class_name = "MultiGroupDataGeneratorInputReader";
  string func_name  = "check_ufg_structure()";

  int    flux_mode_flg = 0;
  string flux_mode_sld = "sld";
  for(int i=0; i<static_cast<int>(mg_flux_calc_mode.size()); i++)
  {
    string mode_name = mg_flux_calc_mode[i];
    transform(mode_name.begin(), mode_name.end(), mode_name.begin(), ::tolower);

    if( mode_name == flux_mode_sld )
    {
      flux_mode_flg = 1;
      break;
    }
  }

  int i_max = static_cast<int>(mg_ufg_structure.size());

  //Check minus value
  int minus_flg = 0;
  for(int i=0; i<i_max; i++)
  {
    if( mg_ufg_structure[i] < min_value )
    {
      minus_flg = 1;
      break;
    }
  }

  if( minus_flg > 0 )
  {
    vector<string> err_com;
    err_com.push_back("mg_ufg_structure must be larger than 0.0.");
    err_com.push_back("");
    err_com.push_back("List of mg_ufg_structure");
    for(int i=0; i<i_max; i++)
    {
      ostringstream oss;
      oss.setf(ios::showpoint);
      oss.setf(ios::scientific);
      oss.width(8);
      oss << mg_ufg_structure[i];
      string str_data = "  " + oss.str();
      err_com.push_back(str_data);
    }
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //Check data size
  if( ( i_max >  0 && i_max-1 != static_cast<int>(mg_ufg_div_no.size())   ) ||
      ( i_max >  0 && i_max-1 != static_cast<int>(mg_ufg_div_mode.size()) ) ||
      ( i_max == 0 && static_cast<int>(mg_ufg_div_no.size()) > 0   ) ||
      ( i_max == 0 && static_cast<int>(mg_ufg_div_mode.size()) > 0 ) )
  {
    vector<string> err_com;
    if( ( i_max >  0 && i_max-1 != static_cast<int>(mg_ufg_div_no.size()) ) ||
        ( i_max == 0 && static_cast<int>(mg_ufg_div_no.size()) > 0 ) )
    {
      err_com.push_back("Data number of mg_ufg_structure is different to that of mg_ufg_div_no.");
    }
    if( ( i_max >  0 && i_max-1 != static_cast<int>(mg_ufg_div_mode.size()) ) ||
        ( i_max == 0 && static_cast<int>(mg_ufg_div_mode.size()) > 0 ) )
    {
      err_com.push_back("Data number of mg_ufg_structure is different to that of mg_ufg_div_mode.");
    }

    err_com.push_back("List of mg_ufg_structure");
    for(int i=0; i<i_max; i++)
    {
      ostringstream oss;
      oss.precision(8);
      oss.setf(ios::showpoint);
      oss.setf(ios::scientific);
      oss << mg_ufg_structure[i];
      string str_data = "  " + oss.str();
      err_com.push_back(str_data);
    }
    err_com.push_back("");

    if( i_max-1 != static_cast<int>(mg_ufg_div_no.size()) )
    {
      err_com.push_back("List of mg_ufg_div_no");
      for(int i=0; i<static_cast<int>(mg_ufg_div_no.size()); i++)
      {
        ostringstream oss;
        oss << mg_ufg_div_no[i];
        string str_data = "  " + oss.str();
        err_com.push_back(str_data);
      }
      err_com.push_back("");
    }
    if( i_max-1 != static_cast<int>(mg_ufg_div_mode.size()) )
    {
      err_com.push_back("List of mg_ufg_div_mode");
      add_data_name_to_error_message(err_com, mg_ufg_div_mode);
      err_com.push_back("");
    }

    if( flux_mode_flg == 0 )
    {
      err_com.push_back("This input file is not selected SLD option in mg_flux_calc_mode.");
      err_com.push_back("Above parameters do not affect the processing results.");
      err_obj.output_caution(class_name, func_name, err_com);

      mg_ufg_structure.clear();
      mg_ufg_div_no.clear();
      mg_ufg_div_mode.clear();
    }
    else if( flux_mode_flg == 1 )
    {
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }

  //Check div_mode and div_no data
  vector<string> ufg_div_mode_list;
  ufg_div_mode_list.push_back("el");
  ufg_div_mode_list.push_back("ee");

      i_max = static_cast<int>(mg_ufg_div_mode.size());
  int j_max = static_cast<int>(ufg_div_mode_list.size());
  for(int i=0; i<i_max; i++)
  {
    string mode_name = mg_ufg_div_mode[i];
    transform(mode_name.begin(), mode_name.end(), mode_name.begin(), ::tolower);

    int mode_find_flg = 0;
    for(int j=0; j<j_max; j++)
    {
      if( mode_name == ufg_div_mode_list[j] )
      {
        mode_find_flg = 1;
        break;
      }
    }

    if( mode_find_flg == 0 )
    {
      vector<string> err_com;
      string str_data = "mg_ufg_div_mode : " + mg_ufg_div_mode[i];
      err_com.push_back(str_data);
      err_com.push_back("This mg_ufg_div_mode name is not available.");
      err_com.push_back("");
      err_com.push_back("List of available mg_ufg_div_mode");
      add_data_name_to_error_message(err_com, ufg_div_mode_list);
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    if( mg_ufg_div_no[i] < 0 )
    {
      vector<string> err_com;
      err_com.push_back("mg_ufg_div_no must be larger than 0.");
      err_com.push_back("");
      err_com.push_back("List of mg_ufg_div_no");
      for(int j=0; j<i_max; j++)
      {
        ostringstream oss;
        oss << mg_ufg_div_no[j];
        string str_data = "  " + oss.str();
        err_com.push_back(str_data);
      }
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }

  if( static_cast<int>(mg_ufg_structure.size()) == 0 )
  {
    get_ufg_data_def(mg_ufg_structure, mg_ufg_div_no, mg_ufg_div_mode);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputReader::get_ufg_data_def
       (vector<Real>& ufg_structure, vector<Integer>& ufg_div_no, vector<string>& ufg_div_mode)
{
  ufg_structure.resize(8);
  ufg_div_no.resize(7);
  ufg_div_mode.resize(7);

  ufg_structure[0] = 1.964033e+07;
  ufg_structure[1] = 52475.0;
  ufg_structure[2] =  9118.8;
  ufg_structure[3] =  4307.4;
  ufg_structure[4] =   961.12;
  ufg_structure[5] =   130.07;
  ufg_structure[6] =     0.32242;
  ufg_structure[7] = 1.0E-5;

  ufg_div_no[0] = 10000;
  ufg_div_no[1] = 56000;
  ufg_div_no[2] = 12000;
  ufg_div_no[3] = 12000;
  ufg_div_no[4] =  8000;
  ufg_div_no[5] = 12000;
  ufg_div_no[6] = 10000;

  for(int i=0; i<static_cast<int>(ufg_div_mode.size()); i++)
  {
    ufg_div_mode[i] = "el"; //Equi-lethagy division
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputReader::add_data_name_to_error_message
                                           (vector<string>& err_com, vector<string> str_vec)
{
  int i_max = static_cast<int>(str_vec.size());
  for(int i=0; i<i_max; i++)
  {
    string str_data = "  " + str_vec[i];
    err_com.push_back(str_data);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputReader::set_mg_file_name_with_mg_edit_mode
                                           (vector<string>& file_mode)
{
  int i_max   = static_cast<int>(file_mode.size());
  int data_no = static_cast<int>(mg_file_name.size());
  if( i_max != data_no )
  {
    StringUtils str_util_obj;
    if( data_no <= 1 )
    {
      string case_name = str_util_obj.basename_without_suffix(input_file_name);
      if( data_no == 1 )
      {
        case_name = mg_file_name[0];
      }

      mg_file_name.resize(i_max);
      for(int i=0; i<i_max; i++)
      {
        string file_mode_mod = str_util_obj.remove_after_space(file_mode[i]);

        mg_file_name[i] = case_name + "_" + file_mode_mod;
      }
    }
    else
    {
      string class_name = "MultiGroupDataGeneratorInputReader";
      string func_name  = "set_mg_file_name_with_mg_edit_mode(vector<string>& file_mode)";

      vector<string> err_com;
      err_com.push_back("Data number of mg_file_name is different to that of mg_edit_mode.");
      err_com.push_back("Please check mg_file_name or mg_edit_mode.");
      err_com.push_back("");
      err_com.push_back("List of mg_file_name");
      add_data_name_to_error_message(err_com, mg_file_name);
      err_com.push_back("");
      err_com.push_back("List of mg_edit_mode");
      add_data_name_to_error_message(err_com, mg_edit_mode);
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputReader::read_input_data_from_input_file(string file_name)
{
  input_file_name = file_name;

  FileCommentRemover file_handling_obj;
  vector<vector<string> > input_data = file_handling_obj.remove_comment_and_devide_text_data(file_name);

  read_input_data(input_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputReader::read_input_data_from_input_file_without_data_check(string file_name)
{
  inp_check_skip_flg = 1;

  input_file_name = file_name;

  FileCommentRemover file_handling_obj;
  vector<vector<string> > input_data = file_handling_obj.remove_comment_and_devide_text_data(file_name);

  read_input_data(input_data);
  inp_check_skip_flg = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<int> MultiGroupDataGeneratorInputReader::read_input_data(string inp_name, vector<vector<string> >& input_data)
{
  input_file_name = inp_name;

  return read_input_data(input_data); 
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<int> MultiGroupDataGeneratorInputReader::read_input_data(vector<vector<string> >& input_data)
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

  check_set_data();

  return inp_check_vec;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int MultiGroupDataGeneratorInputReader::read_input_data(vector<string>& input_type, vector<string>& input_data)
{
  if( static_cast<int>(input_type.size()) != 1 )
  {
    string class_name = "MultiGroupDataGeneratorInputReader";
    string func_name  = "read_input_data(vector<string>& input_type, vector<string>& input_data)";
    frendy_utils.error_input_type_size(class_name, func_name, input_type);
  }

  return read_input_data(input_type[0], input_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int MultiGroupDataGeneratorInputReader::read_input_data(string& input_type, vector<string>& input_data)
{
  if( static_cast<int>(input_data.size()) == 0 )
  {
    string class_name = "MultiGroupDataGeneratorInputReader";
    string func_name  = "read_input_data(string& input_type, vector<string>& input_data)";
    frendy_utils.error_input_data_size_is_zero(class_name, func_name, input_data);
  }

  if( print_set_data_flg == frendy_utils.print_set_data && print_title_flg == 0 )
  {
    print_title_flg = 1;
    cout << "=== Read input data for MultiGroupDataGenerator ===" << endl;
  }

  //Modify capital letter to lower-case letter
  string input_type_mod = input_type;
  transform(input_type_mod.begin(), input_type_mod.end(), input_type_mod.begin(), ::tolower);
  replace(input_type_mod.begin(), input_type_mod.end(), '-', '_');

  //Modify "," in input_data to space.
  for(int i=0; i<static_cast<int>(input_data.size()); i++)
  {
    replace(input_data[i].begin(), input_data[i].end(), ',', ' ');
  }

  int inp_check = process_mode_common;
  if( input_type_mod == "nucl_file_name"  || input_type_mod == "nucl_name" ||
      input_type_mod == "endf_file_name"  || input_type_mod == "endf_name" ||
      input_type_mod == "pendf_file_name" || input_type_mod == "pendf_name" )
  {
    set_nucl_file_name(input_data);
  }

  else if( input_type_mod == "nucl_file_name_tsl"  || input_type_mod == "nucl_name_tsl" ||
           input_type_mod == "endf_file_name_tsl"  || input_type_mod == "endf_name_tsl" ||
           input_type_mod == "pendf_file_name_tsl" || input_type_mod == "pndf_name_tsl" )
  {
    inp_check = process_mode_tsl;
    set_nucl_file_name_tsl(input_data);
  }
  else if( input_type_mod == "ace_file_name" || input_type_mod == "ace_name" )
  {
    set_ace_file_name(input_data);
  }
  else if( input_type_mod == "ace_file_name_tsl" || input_type_mod == "ace_name_tsl" )
  {
    inp_check = process_mode_tsl;
    set_ace_file_name_tsl(input_data);
  }
  else if( input_type_mod == "ace_output_option" ||
           input_type_mod == "ace_edit_option" )
  {
    set_ace_output_option(input_data);
  }
  else if( input_type_mod == "mg_file_name" )
  {
    set_mg_file_name(input_data);
  }
  else if( input_type_mod == "mg_edit_mode"   ||
           input_type_mod == "mg_edit_xs"     ||
           input_type_mod == "mg_edit_option" ||
           input_type_mod == "mg_file_mode"   )
  {
    set_mg_edit_mode(input_data);
  }
  else if( input_type_mod == "mg_print_reaction" )
  {
    set_mg_print_reaction(input_data);
  }
  else if( input_type_mod == "mg_mat_no" ||
           input_type_mod == "mg_mat_list" ||
           input_type_mod == "mg_mat_no_list" )
  {
    set_mg_mat_list(input_data);
  }
  else if( input_type_mod == "mg_start_file_mode" )
  {
    set_mg_start_file_mode(input_data);
  }
  else if( input_type_mod == "mg_weighting_spectrum_mode" )
  {
    set_mg_weighting_spectrum_mode(input_data);
  }
  else if( input_type_mod == "mg_weighting_spectrum_el" )
  {
    set_mg_weighting_spectrum_el(input_data);
  }
  else if( input_type_mod == "mg_weighting_spectrum_eh" )
  {
    set_mg_weighting_spectrum_eh(input_data);
  }
  else if( input_type_mod == "mg_weighting_fission_temp" )
  {
    set_mg_weighting_fission_temp(input_data);
  }
  else if( input_type_mod == "mg_weighting_1e_eh" || input_type_mod == "mg_weighting_e_eh" )
  {
    set_mg_weighting_1e_eh(input_data);
  }
  else if( input_type_mod == "mg_weighting_1e_el" || input_type_mod == "mg_weighting_e_el" )
  {
    set_mg_weighting_1e_el(input_data);
  }
  else if( input_type_mod == "mg_weighting_spectrum_data" || input_type_mod == "mg_weighting_spectrum" )
  {
    set_mg_weighting_spectrum_data(input_data);
  }
  else if( input_type_mod == "mg_weighting_spectrum_data_int" || input_type_mod == "mg_weighting_spectrum_int" )
  {
    set_mg_weighting_spectrum_data_int(input_data);
  }
  else if( input_type_mod == "legendre_order" )
  {
    set_legendre_order(input_data);
  }
  else if( input_type_mod == "mg_label_data" )
  {
    set_mg_label_data(input_data);
  }
  else if( input_type_mod == "temp" || input_type_mod == "temperature" )
  {
    set_temp(input_data);
  }
  else if( input_type_mod == "sigma_zero_data" || input_type_mod == "sig_zero_data" ||
           input_type_mod == "sigma_zero"      || input_type_mod == "sig_zero"  )
  {
    set_sigma_zero_data(input_data);
  }
  else if( input_type_mod == "mg_structure"          ||
           input_type_mod == "mg_structure_neutron"  ||
           input_type_mod == "mg_structure_neutrons" ||
           input_type_mod == "multi_group_structure" ||
           input_type_mod == "multi_group_neutrons"  ||
           input_type_mod == "multi_group_neutron"   )
  {
    set_mg_structure(input_data);
  }
  else if( input_type_mod == "mg_structure_g"              ||
           input_type_mod == "mg_structure_gam"            ||
           input_type_mod == "mg_structure_gamma"          ||
           input_type_mod == "multi_group_structure_g"     ||
           input_type_mod == "multi_group_structure_gam"   ||
           input_type_mod == "multi_group_structure_gamma" ||
           input_type_mod == "multi_group_g"               ||
           input_type_mod == "multi_group_gam"             ||
           input_type_mod == "multi_group_gamma"  )
  {
    set_mg_structure_gam(input_data);
  }
  else if( input_type_mod == "max_thermal_ene"       ||
           input_type_mod == "max_thermal_ene_in"    ||
           input_type_mod == "max_thermal_ene_e_in"  )
  {
    set_max_thermal_ene_e_in(input_data);
  }
  else if( input_type_mod == "max_thermal_ene_out"   ||
           input_type_mod == "max_thermal_ene_e_out"  )
  {
    set_max_thermal_ene_e_out(input_data);
  }
  else if( input_type_mod == "mg_process_data" )
  {
    set_mg_process_data(input_data);
  }
  else if( input_type_mod == "mg_process_reaction" )
  {
    set_mg_process_reaction(input_data);
  }
  else if( input_type_mod == "mg_process_reaction_name" )
  {
    set_mg_process_reaction_name(input_data);
  }
  else if( input_type_mod == "mg_ultra_fine_group_structure" ||
           input_type_mod == "mg_ufg_structure" )
  {
    set_mg_ufg_structure(input_data);
  }
  else if( input_type_mod == "mg_ultra_fine_group_div_no" ||
           input_type_mod == "mg_ufg_div_no" )
  {
    set_mg_ufg_div_no(input_data);
  }
  else if( input_type_mod == "mg_ultra_fine_group_div_mode" ||
           input_type_mod == "mg_ufg_div_mode" )
  {
    set_mg_ufg_div_mode(input_data);
  }
  else if( input_type_mod == "mg_number_density" )
  {
    set_mg_number_density(input_data);
  }
  else if( input_type_mod == "mg_tsl_data_type" )
  {
    set_mg_tsl_data_type(input_data);
  }
  else if( input_type_mod == "mg_flux_calc_mode" )
  {
    set_mg_flux_calc_mode(input_data);
  }
  else if( input_type_mod == "mg_flux_calc_w_eh_el" )
  {
    set_mg_flux_calc_w_eh_el(input_data);
  }
  else if( input_type_mod == "mg_flux_calc_w" )
  {
    set_mg_flux_calc_w(input_data);
  }
  else if( input_type_mod == "mg_flux_calc_eh" )
  {
    set_mg_flux_calc_eh(input_data);
  }
  else if( input_type_mod == "mg_flux_calc_el" )
  {
    set_mg_flux_calc_el(input_data);
  }
  else if( input_type_mod == "mg_thermal_upscatter_treatment" ||
           input_type_mod == "mg_thermal_xs_treatment" ||
           input_type_mod == "mg_free_gas_treatment" )
  {
    set_mg_thermal_xs_treatment(input_data);
  }
  else if( input_type_mod == "potential_scat_xs" )
  {
    set_potential_scat_xs(input_data);
  }
  else if( input_type_mod == "reso_upscat"       ||
           input_type_mod == "reso_up_scat"      ||
           input_type_mod == "reso_upscat_data"  ||
           input_type_mod == "reso_up_scat_data" )
  {
    set_reso_up_scat(input_data);
  }
  else if( input_type_mod == "reso_upscat_mode"  ||
           input_type_mod == "reso_up_scat_mode" )
  {
    set_reso_up_scat_mode(input_data);
  }
  else
  {
    inp_check = 0;
  }

  return inp_check;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputReader::set_nucl_file_name(vector<string>& input_data)
{
  //if( static_cast<int>(input_data.size()) > 1 )
  //{
  //  string class_name = "MultiGroupDataGeneratorInputReader";
  //  string func_name  = "set_nucl_file_name(vector<string>& input_data)";
  //  frendy_utils.error_input_data_size_is_larger_than_one(class_name, func_name, input_data);
  //}

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    int i_max = static_cast<int>(input_data.size());
    if( i_max == 1 )
    {
      cout << "  nucl_file_name                       : " << input_data[0] << endl;
    }
    else
    {
      cout << "  No. of nucl_file_name                : " << i_max << endl;
      for(int i=0; i<i_max; i++)
      {
        cout << "    nucl_file_name                     : " << input_data[i] << endl;
      }
    }
  }

  nucl_file_name = input_data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputReader::set_nucl_file_name_tsl(vector<string>& input_data)
{
  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    int i_max = static_cast<int>(input_data.size());
    if( i_max == 1 )
    {
      cout << "  nucl_file_name_tsl                   : " << input_data[0] << endl;
    }
    else
    {
      cout << "  No. of nucl_file_name_tsl            : " << i_max << endl;
      for(int i=0; i<i_max; i++)
      {
        cout << "    nucl_file_name_tsl                 : " << input_data[i] << endl;
      }
    }
  }

  nucl_file_name_tsl = input_data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputReader::set_ace_file_name(vector<string>& input_data)
{
  ace_output_flg = frendy_utils.on;

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    int i_max = static_cast<int>(input_data.size());
    if( i_max == 1 )
    {
      cout << "  ace_file_name                        : " << input_data[0] << endl;
    }
    else
    {
      cout << "  No. of ace_file_name                 : " << i_max << endl;
      for(int i=0; i<i_max; i++)
      {
        cout << "    ace_file_name                      : " << input_data[i] << endl;
      }
    }
  }

  ace_file_name = input_data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputReader::set_ace_file_name_tsl(vector<string>& input_data)
{
  ace_output_flg = frendy_utils.on;

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    int i_max = static_cast<int>(input_data.size());
    if( i_max == 1 )
    {
      cout << "  ace_file_name_tsl                    : " << input_data[0] << endl;
    }
    else
    {
      cout << "  No. of ace_file_name_tsl             : " << i_max << endl;
      for(int i=0; i<i_max; i++)
      {
        cout << "    ace_file_name_tsl                  : " << input_data[i] << endl;
      }
    }
  }

  ace_file_name_tsl = input_data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputReader::set_ace_output_option(vector<string>& input_data)
{
  if( static_cast<int>(input_data.size()) > 1 )
  {
    string class_name = "MultiGroupDataGeneratorInputReader";
    string func_name  = "set_ace_output_option(vector<string>& input_data)";
    frendy_utils.error_input_data_size_is_larger_than_one(class_name, func_name, input_data);
  }

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  ace_output_option                    : " << input_data[0] << endl;
  }

  string str_data = input_data[0];
  transform(str_data.begin(), str_data.end(), str_data.begin(), ::tolower);
  if( str_data == "on" || str_data == "output" || str_data == "edit" )
  {
    set_ace_output_flg(frendy_utils.on);
    if( print_set_data_flg == frendy_utils.print_set_data )
    {
      cout << "                                         (output ace files)" << endl;
    }
  }
  else if( str_data == "off" || str_data == "skip" || str_data == "no" )
  {
    set_ace_output_flg(frendy_utils.off);
    if( print_set_data_flg == frendy_utils.print_set_data )
    {
      cout << "                                         (skip output ace files)" << endl;
    }
  }
  else if( str_data == "default" || str_data == "def" )
  {
    set_ace_output_flg(frendy_utils.get_ace_output_flg_def());
  }
  else
  {
    string class_name = "MultiGroupDataGeneratorInputReader";
    string func_name  = "set_ace_output_option(vector<string>& input_data)";

    vector<string> err_com;
    err_com.push_back("This ace_output_option is not available.");
    err_com.push_back("The available ace_output_option is on/output/edit, off/skip/no, or default/def.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputReader::set_mg_file_name(vector<string>& input_data)
{
  if( static_cast<int>(input_data.size()) > 1 )
  {
    string class_name = "MultiGroupDataGeneratorInputReader";
    string func_name  = "set_mg_file_name(vector<string>& input_data)";
    frendy_utils.error_input_data_size_is_larger_than_one(class_name, func_name, input_data);
  }

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    int i_max = static_cast<int>(input_data.size());
    if( i_max == 1 )
    {
      cout << "  mg_file_name                         : " << input_data[0] << endl;
    }
  }

  mg_file_name = input_data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputReader::set_mg_file_name(string input_data)
{
  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  mg_file_name                         : " << input_data << endl;
  }

  mg_file_name.resize(1);
  mg_file_name[0] = input_data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputReader::set_mg_edit_mode(vector<string>& input_data)
{
  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    int i_max = static_cast<int>(input_data.size());
    if( i_max == 1 )
    {
      cout << "  mg_edit_mode                         : " << input_data[0] << endl;
    }
    else
    {
      cout << "  No. of mg_edit_mode                  : " << i_max << endl;
      for(int i=0; i<i_max; i++)
      {
        cout << "    mg_edit_mode                       : " << input_data[i] << endl;
      }
    }
  }

  mg_edit_mode = input_data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputReader::set_mg_print_reaction(vector<string>& input_data)
{
  int i_max = static_cast<int>(input_data.size());
  mg_print_reaction.resize(i_max);

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  No. of mg_print_reaction             : " << i_max << endl;
  }

  for(int i=0; i<i_max; i++)
  {
    if( print_set_data_flg == frendy_utils.print_set_data )
    {
      cout << "    mg_print_reaction                  : " << input_data[i] << endl;
    }

    str_obj.string_check(input_data[i]);
    mg_print_reaction[i] = numeric_string_cast<Integer>(input_data[i]);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputReader::set_mg_mat_list(vector<string>& input_data)
{
  int i_max = static_cast<int>(input_data.size());
  mg_mat_list.resize(i_max);

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  No. of mg_mat_list                   : " << i_max << endl;
  }

  for(int i=0; i<i_max; i++)
  {
    if( print_set_data_flg == frendy_utils.print_set_data )
    {
      cout << "    mg_mat_list                        : " << input_data[i] << endl;
    }
 
    str_obj.string_check(input_data[i]);
    mg_mat_list[i] = numeric_string_cast<Integer>(input_data[i]);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputReader::set_mg_start_file_mode(vector<string>& input_data)
{
  if( static_cast<int>(input_data.size()) > 1 )
  {
    string class_name = "MultiGroupDataGeneratorInputReader";
    string func_name  = "set_mg_start_file_mode(vector<string>& input_data)";
    frendy_utils.error_input_data_size_is_larger_than_one(class_name, func_name, input_data);
  }

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  mg_start_file_mode                   : " << input_data[0] << endl;
  }

  mg_start_file_mode = input_data[0];
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputReader::set_mg_weighting_spectrum_mode(vector<string>& input_data)
{
  if( static_cast<int>(input_data.size()) > 1 )
  {
    string class_name = "MultiGroupDataGeneratorInputReader";
    string func_name  = "set_weighting_spectrum_mode(vector<string>& input_data)";
    frendy_utils.error_input_data_size_is_larger_than_one(class_name, func_name, input_data);
  }

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  mg_weighting_spectrum_mode           : " << input_data[0] << endl;
  }

  mg_weighting_spectrum_mode = input_data[0];
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputReader::set_mg_weighting_spectrum_el(vector<string>& input_data)
{
  if( static_cast<int>(input_data.size()) > 1 )
  {
    string class_name = "MultiGroupDataGeneratorInputReader";
    string func_name  = "set_mg_weighting_spectrum_el(vector<string>& input_data)";
    frendy_utils.error_input_data_size_is_larger_than_one(class_name, func_name, input_data);
  }

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  mg_weighting_spectrum_el [eV]        : " << input_data[0] << endl;
  }

  str_obj.string_check(input_data[0]);
  mg_weighting_spectrum_el = numeric_string_cast<Real>(input_data[0]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputReader::set_mg_weighting_spectrum_eh(vector<string>& input_data)
{
  if( static_cast<int>(input_data.size()) > 1 )
  {
    string class_name = "MultiGroupDataGeneratorInputReader";
    string func_name  = "set_mg_weighting_spectrum_eh(vector<string>& input_data)";
    frendy_utils.error_input_data_size_is_larger_than_one(class_name, func_name, input_data);
  }

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  mg_weighting_spectrum_eh [eV]        : " << input_data[0] << endl;
  }

  str_obj.string_check(input_data[0]);
  mg_weighting_spectrum_eh = numeric_string_cast<Real>(input_data[0]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputReader::set_mg_weighting_fission_temp(vector<string>& input_data)
{
  if( static_cast<int>(input_data.size()) > 1 )
  {
    string class_name = "MultiGroupDataGeneratorInputReader";
    string func_name  = "set_mg_weighting_fission_temp(vector<string>& input_data)";
    frendy_utils.error_input_data_size_is_larger_than_one(class_name, func_name, input_data);
  }

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  mg_weighting_fission_temp [K]        : " << input_data[0] << endl;
  }

  str_obj.string_check(input_data[0]);
  mg_weighting_fission_temp = numeric_string_cast<Real>(input_data[0]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputReader::set_mg_weighting_1e_el(vector<string>& input_data)
{
  if( static_cast<int>(input_data.size()) > 1 )
  {
    string class_name = "MultiGroupDataGeneratorInputReader";
    string func_name  = "set_mg_weighting_1e_el(vector<string>& input_data)";
    frendy_utils.error_input_data_size_is_larger_than_one(class_name, func_name, input_data);
  }

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  mg_weighting_1e_el [eV]              : " << input_data[0] << endl;
  }

  str_obj.string_check(input_data[0]);
  mg_weighting_1e_el = numeric_string_cast<Real>(input_data[0]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputReader::set_mg_weighting_1e_eh(vector<string>& input_data)
{
  if( static_cast<int>(input_data.size()) > 1 )
  {
    string class_name = "MultiGroupDataGeneratorInputReader";
    string func_name  = "set_mg_weighting_1e_eh(vector<string>& input_data)";
    frendy_utils.error_input_data_size_is_larger_than_one(class_name, func_name, input_data);
  }

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  mg_weighting_1e_eh [eV]              : " << input_data[0] << endl;
  }

  str_obj.string_check(input_data[0]);
  mg_weighting_1e_eh = numeric_string_cast<Real>(input_data[0]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputReader::set_mg_weighting_spectrum_data(vector<string>& input_data)
{
  int data_no = static_cast<int>(input_data.size());
  if( data_no == 0 )
  {
    return;
  }

  iwt_no = check_mg_weighting_spectrum_mode(input_data[0]);

  if( iwt_no == 0 && data_no == 1 )
  {
    set_mg_weighting_spectrum_mode(input_data[0]);
    return;
  }
  else if( iwt_no == 3 )
  {
    mg_weighting_spectrum_mode = "1/e";
    return;
  }
  else if( iwt_no == 4 )
  {
    mg_weighting_spectrum_mode = "fission+1/e+maxwell";
    return;
  }
  else if( iwt_no > 0 )
  {
    if( print_set_data_flg == frendy_utils.print_set_data )
    {
      cout << "  mg_weighting_spectrum_mode           : " << input_data[0]
           << " (iwt = " << iwt_no << ")" << endl;
    }

    MultiGroupWeightFunction iwt_obj;
    iwt_obj.get_weighting_function(iwt_no, temp, mg_weighting_spectrum_data_e,
                                                 mg_weighting_spectrum_data_w);
    mg_weighting_spectrum_data_nbt.resize(1);
    mg_weighting_spectrum_data_int.resize(1);
    mg_weighting_spectrum_data_nbt[0] = static_cast<Integer>(mg_weighting_spectrum_data_e.size());
    mg_weighting_spectrum_data_int[0] = int_lin_lin;

    return;
  }
  else if( iwt_no < 0 )
  {
    set_mg_weighting_spectrum_mode(input_data[0]);
    if( print_set_data_flg == frendy_utils.print_set_data )
    {
      cout << "  mg_weighting_spectrum_mode           : " << input_data[0] << endl;
    }

    if( data_no > 1 )
    {
      mg_weighting_spectrum_eh  = numeric_string_cast<Real>(input_data[1]);
      if( print_set_data_flg == frendy_utils.print_set_data )
      {
        cout << "  mg_weighting_spectrum_eh [eV]        : " << mg_weighting_spectrum_eh << endl;
      }
    }

    if( data_no > 2 )
    {
      mg_weighting_spectrum_el  = numeric_string_cast<Real>(input_data[2]);
      if( print_set_data_flg == frendy_utils.print_set_data )
      {
        cout << "  mg_weighting_spectrum_el [eV]        : " << mg_weighting_spectrum_el << endl;
      }
    }

    if( data_no > 3 )
    {
      mg_weighting_fission_temp = numeric_string_cast<Real>(input_data[3]);
      if( print_set_data_flg == frendy_utils.print_set_data )
      {
        cout << "  mg_weighting_fission_temp [K]        : " << mg_weighting_fission_temp << endl;
      }
    }

    if( data_no > 4 )
    {
      mg_weighting_1e_eh        = numeric_string_cast<Real>(input_data[4]);
      if( print_set_data_flg == frendy_utils.print_set_data )
      {
        cout << "  mg_weighting_1e_eh [eV]              : " << mg_weighting_1e_eh << endl;
      }
    }

    if( data_no > 5 )
    {
      mg_weighting_1e_el        = numeric_string_cast<Real>(input_data[5]);
      if( print_set_data_flg == frendy_utils.print_set_data )
      {
        cout << "  mg_weighting_1e_el [eV]              : " << mg_weighting_1e_el << endl;
      }
    }

    return;
  }

  if( data_no%2 != 0 )
  {
    string class_name = "MultiGroupDataGeneratorInputReader";
    string func_name  = "set_mg_weighting_spectrum_data";

    vector<string> err_com;
    err_com.push_back("Data number of mg_weighting_spectrum_data must be even number.");
    err_com.push_back("mg_weighting_spectrum_data consists of energy and its weight.");
    err_com.push_back("Please check mg_weighting_spectrum_data data.");
    err_com.push_back("");
    err_com.push_back("List of mg_weighting_spectrum_data data");
    for(int i=0; i<data_no; i++)
    {
      err_com.push_back(input_data[i]);

      if( (i+1)%2 == 0 )
      {
        err_com.push_back("");
      }
    }
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  int i_max = data_no / 2;
  mg_weighting_spectrum_data_e.resize(i_max);
  mg_weighting_spectrum_data_w.resize(i_max);

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  No. of mg_weighting_spectrum_data (e/w)     : " << i_max << endl;
  }

  for(int i=0; i<i_max; i++)
  {
    if( print_set_data_flg == frendy_utils.print_set_data )
    {
      if( i==0 )
      {
        cout << "    mg_weighting_spectrum_data (ene [eV]/weight)" << endl;
      }
      cout << "        " << input_data[i*1] << " / " << input_data[i*2+1] << endl;
    }

    str_obj.string_check(input_data[i*2]);
    str_obj.string_check(input_data[i*2+1]);

    mg_weighting_spectrum_data_e[i] = numeric_string_cast<Real>(input_data[i*2]);
    mg_weighting_spectrum_data_w[i] = numeric_string_cast<Real>(input_data[i*2+1]);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int  MultiGroupDataGeneratorInputReader::check_mg_weighting_spectrum_mode(string str_data)
{
  transform(str_data.begin(), str_data.end(), str_data.begin(), ::tolower);

  if( static_cast<int>(str_data.find("iwt")) == 0 )
  {
    string iwt_no_str = str_data.substr(3);

    str_obj.string_check(iwt_no_str);

    int int_val = numeric_string_cast<int>(iwt_no_str);
    if( int_val < 0 )
    {
      int_val *= -1;

      string class_name = "MultiGroupDataGeneratorInputReader";
      string func_name  = "check_mg_weighting_spectrum_mode(string str_data)";

      vector<string> err_com;
      string err_str01 = "Input data : " + str_data;
      err_com.push_back(err_str01);
      err_com.push_back("The minus iwt option is changed to plus value.");
      err_com.push_back("If you want to calculate flux with weight spectrum,");
      err_com.push_back("please set SLD option in mg_flux_calc_mode.");
      err_obj.output_caution(class_name, func_name, err_com);
    }
    return int_val;
  }

  if( static_cast<int>(str_data.find("fission+1/e+maxwell")) == 0 ||
      static_cast<int>(str_data.find("1/e")) == 0 )
  {
    return -1;
  }

  string str_mod = str_data;
  replace(str_mod.begin(), str_mod.end(), '_', '-');
  replace(str_mod.begin(), str_mod.end(), '/', '-');
  if( str_mod == "constant"                    ) return  2;
  if( str_mod == "const"                       ) return  2;
  if( str_mod == "epri-cell-lwr"               ) return  5;
  if( str_mod == "epri-cell"                   ) return  5;
  if( str_mod == "epri"                        ) return  5;
  if( str_mod == "claw-weight-function"        ) return  9;
  if( str_mod == "claw-weight"                 ) return  9;
  if( str_mod == "claw-with-t-dependent"       ) return 10;
  if( str_mod == "claw-with-t-depend"          ) return 10;
  if( str_mod == "claw-with-t"                 ) return 10;
  if( str_mod == "claw-t"                      ) return 10;
  if( str_mod == "vitamine-e"                  ) return 11;
  if( str_mod == "vit-e"                       ) return 11;
  if( str_mod == "ornl-5505"                   ) return 11;
  if( str_mod == "vitamine-e-with-t-dependent" ) return 12;
  if( str_mod == "vitamine-e-with-t-depend"    ) return 12;
  if( str_mod == "vitamine-e-with-t"           ) return 12;
  if( str_mod == "vit-e-with-t-dependent"      ) return 12;
  if( str_mod == "vit-e-with-t-depend"         ) return 12;
  if( str_mod == "vit-e-with-t"                ) return 12;
  if( str_mod == "vit-e-w-t"                   ) return 12;

  return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputReader::set_mg_weighting_spectrum_data_int(vector<string>& input_data)
{
  int data_no = static_cast<int>(input_data.size());

  if( data_no == 1 )
  {
    mg_weighting_spectrum_data_nbt.resize(1);
    mg_weighting_spectrum_data_int.resize(1);

    mg_weighting_spectrum_data_nbt    = frendy_utils.get_mg_weighting_spectrum_data_nbt_def();
    mg_weighting_spectrum_data_int[0] = numeric_string_cast<Integer>(input_data[0]);

    if( print_set_data_flg == frendy_utils.print_set_data )
    {
      cout << "    mg_weighting_spectrum_data_int (int)      : " << input_data[0] << endl;
    }

    return;
  }

  if( data_no%2 != 0 )
  {
    string class_name = "MultiGroupDataGeneratorInputReader";
    string func_name  = "set_mg_weighting_spectrum_data_int";

    vector<string> err_com;
    err_com.push_back("Data number of mg_weighting_spectrum_data_int must be even number.");
    err_com.push_back("mg_weighting_spectrum_data_int consists of range (nbt) and");
    err_com.push_back("interpolation scheme (int).");
    err_com.push_back("Please check mg_weighting_spectrum_data_int data.");
    err_com.push_back("");
    err_com.push_back("List of mg_weighting_spectrum_data_int data");
    for(int i=0; i<data_no; i++)
    {
      err_com.push_back(input_data[i]);
 
      if( i+1%2 == 0 )
      {
        err_com.push_back("");
      }
    }
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  int i_max = data_no / 2;
  mg_weighting_spectrum_data_nbt.resize(i_max);
  mg_weighting_spectrum_data_int.resize(i_max);

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  No. of mg_weighting_spectrum_data (nbt/int) : " << i_max << endl;
  }

  for(int i=0; i<i_max; i++)
  {
    if( print_set_data_flg == frendy_utils.print_set_data )
    {
      cout << "    mg_weighting_spectrum_data_int (nbt/int)  : "
           << input_data[i*1] << " / " << input_data[i*2+1] << endl;
    }
 
    str_obj.string_check(input_data[i*2]);
    str_obj.string_check(input_data[i*2+1]);

    mg_weighting_spectrum_data_nbt[i] = numeric_string_cast<Integer>(input_data[i*2]);
    mg_weighting_spectrum_data_int[i] = numeric_string_cast<Integer>(input_data[i*2+1]);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputReader::set_legendre_order(vector<string>& input_data)
{
  if( static_cast<int>(input_data.size()) > 1 )
  {
    string class_name = "MultiGroupDataGeneratorInputReader";
    string func_name  = "set_legendre_order(vector<string>& input_data)";
    frendy_utils.error_input_data_size_is_larger_than_one(class_name, func_name, input_data);
  }

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  legendre_order                       : " << input_data[0] << endl;
  }

  str_obj.string_check(input_data[0]);
  legendre_order = numeric_string_cast<Integer>(input_data[0]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputReader::set_mg_label_data(vector<string>& input_data)
{
  if( static_cast<int>(input_data.size()) > 1 )
  {
    string class_name = "MultiGroupDataGeneratorInputReader";
    string func_name  = "set_mg_label_data(vector<string>& input_data)";
    frendy_utils.error_input_data_size_is_larger_than_one(class_name, func_name, input_data);
  }

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  mg_label_data                        : " << input_data[0] << endl;
  }

  mg_label_data = input_data[0];
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputReader::set_temp(vector<string>& input_data)
{
  if( static_cast<int>(input_data.size()) > 1 )
  {
    string class_name = "MultiGroupDataGeneratorInputReader";
    string func_name  = "set_temp(vector<string>& input_data)";
    frendy_utils.error_input_data_size_is_larger_than_one(class_name, func_name, input_data);
  }

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  temperature [K]                      : " << input_data[0] << endl;
  }

  temp_set_flg = 1;
  str_obj.string_check(input_data[0]);
  temp = numeric_string_cast<Real>(input_data[0]);

  if( fabs(temp) < 1.0E-10 )
  {
    string class_name = "MultiGroupDataGeneratorInputReader";
    string func_name  = "set_temp(vector<string>& input_data)";

    vector<string> err_com;
    err_com.push_back("Temperature is less than 1.0E-10 K.");
    err_com.push_back("Temperature is is modified to 1.0E-10 K.");

    err_obj.output_caution(class_name, func_name, err_com);

    temp = 1.0E-10;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputReader::set_sigma_zero_data(vector<string>& input_data)
{
  int i_max = static_cast<int>(input_data.size());
  if( i_max == 0 )
  {
    return;
  }

  sigma_zero_data.clear();
  sigma_zero_data_auto.clear();

  if( check_mg_structure_mode(input_data[0]) == -1 )
  {
    sigma_zero_data_auto = input_data[0];
    for(int i=1; i<i_max; i++)
    {
      sigma_zero_data_auto = sigma_zero_data_auto + "  " + input_data[i];
    }

    if( print_set_data_flg == frendy_utils.print_set_data )
    {
      cout << "  sigma_zero_data" << endl;
      cout << "    " << sigma_zero_data_auto << endl;
    }
    return;
  }

  sigma_zero_data.resize(i_max);

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  No. of sigma_zero_data               : " << i_max << endl;
    cout << "  sigma_zero_data [barn]" << endl;
  }

  string str_data = "";
  for(int i=0; i<i_max; i++)
  {
    if( print_set_data_flg == frendy_utils.print_set_data )
    {
      str_data = str_data + "  " + input_data[i];
      if( (i+1)%10 == 0 )
      {
        cout << "  " << str_data << endl;
        str_data.clear();
      }
    }
 
    str_obj.string_check(input_data[i]);
    sigma_zero_data[i] = numeric_string_cast<Real>(input_data[i]);
  }
  if( static_cast<int>(str_data.size()) > 0 )
  {
    if( print_set_data_flg == frendy_utils.print_set_data )
    {
      cout << "  " << str_data << endl;
      str_data.clear();
    }
  }

  sort( sigma_zero_data.begin(), sigma_zero_data.end(), greater<Real>() );
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputReader::set_mg_structure(vector<string>& input_data)
{
  int i_max = static_cast<int>(input_data.size());
  if( i_max == 0 )
  {
    return;
  }
  mg_structure_auto.clear();

  int mg_structure_mode = check_mg_structure_mode(input_data[0]);
  if( mg_structure_mode == 0 ) //Read multi-group structure data from input
  {
    mg_structure.resize(i_max);
    for(int i=0; i<i_max; i++)
    {
      str_obj.string_check(input_data[i]);
      mg_structure[i] = numeric_string_cast<Real>(input_data[i]);
    }
  }
  else if( mg_structure_mode > 0 )
  {
    GroupStructureNeutron mg_structure_obj;
    mg_structure = mg_structure_obj.get_group_structure(mg_structure_mode);
  }
  else //if( mg_structure_mode < 0 ) //auto
  {
    mg_structure.clear();
    if( (i_max - 2)%3 != 0 )
    {
      string class_name = "MultiGroupDataGeneratorInputReader";
      string func_name  = "set_mg_structure(vector<string>& input_data)";

      vector<string> err_com;
      err_com.push_back("The number of mg_structure for auto option is not appropriate.");
      err_com.push_back("The format of mg_structure data is as follows:");
      err_com.push_back("  auto");
      err_com.push_back("  Energy boundary,  number of divisions,  EL/EE");
      err_com.push_back("    .");
      err_com.push_back("    .");
      err_com.push_back("    .");
      err_com.push_back("  Lowest energy boundary");
      err_com.push_back("");
      err_com.push_back("Please check your input file.");

      for(int i=0; i<i_max; i++)
      {
        string str_data = "  " + input_data[i];
        err_com.push_back(str_data);
        if( i > 0 && i%3 == 0 )
        {
          err_com.push_back("");
        }
      }

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    mg_structure_auto.clear();
    mg_structure_auto.push_back("auto");

    for(int i=1; i<i_max; i+=3)
    {
      string str_data = input_data[i];
      if( i+1 < i_max ) str_data = str_data + "  " + input_data[i+1];
      if( i+2 < i_max ) str_data = str_data + "  " + input_data[i+2];
      mg_structure_auto.push_back(str_data);
    }
  }

  sort( mg_structure.begin(), mg_structure.end(), greater<Real>() );

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    if( mg_structure_mode >= 0 )
    {
      i_max = static_cast<int>(mg_structure.size());

      cout << "  No. of mg_structure                  : " << i_max - 1 << endl;
      cout << "  mg_structure [eV]" << endl;

      string str_data = "";
      for(int i=0; i<i_max; i++)
      {
        ostringstream oss;
        oss.precision(10);
        oss.setf(ios::showpoint);
        oss.setf(ios::scientific);
        oss << mg_structure[i];

        str_data = str_data + "  " + oss.str();
        if( (i+1)%10 == 0 )
        {
          cout << "  " << str_data << endl;
          str_data.clear();
        }
      }

      if( static_cast<int>(str_data.size()) > 0 )
      {
        cout << "  " << str_data << endl;
        str_data.clear();
      }
    }
    else //if( mg_structure_mode < 0 )
    {
      cout << "  mg_structure" << endl;
      for(int i=0; i<static_cast<int>(mg_structure_auto.size()); i++)
      {
        cout << "    " << mg_structure_auto[i] << endl;
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputReader::set_mg_structure_gam(vector<string>& input_data)
{
  int i_max = static_cast<int>(input_data.size());
  if( i_max == 0 )
  {
    return;
  }

  int mg_structure_mode = check_mg_structure_mode_gam(input_data[0]);
  if( mg_structure_mode == 0 ) //Read multi-group structure data from input
  {
    mg_structure_gam.resize(i_max);
    for(int i=0; i<i_max; i++)
    {
      str_obj.string_check(input_data[i]);
      mg_structure_gam[i] = numeric_string_cast<Real>(input_data[i]);
    }
  }
  else if( mg_structure_mode > 0 )
  {
    GroupStructureGamma mg_structure_obj;
    mg_structure_gam = mg_structure_obj.get_group_structure(mg_structure_mode);
  }
  else //if( mg_structure_mode < 0 ) //auto
  {
    string class_name = "MultiGroupDataGeneratorInputReader";
    string func_name  = "set_mg_structure_gam(vector<string>& input_data)";

    vector<string> err_com;
    err_com.push_back("The auto option is not available.");
    err_com.push_back("The auto option in only available for the set_mg_structure function.");
    err_com.push_back("Please check your input file.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  sort( mg_structure_gam.begin(), mg_structure_gam.end(), greater<Real>() );

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    if( mg_structure_mode >= 0 )
    {
      i_max = static_cast<int>(mg_structure_gam.size());

      cout << "  No. of mg_structure_gam              : " << i_max - 1 << endl;
      cout << "  mg_structure_gam [eV]" << endl;

      string str_data = "";
      for(int i=0; i<i_max; i++)
      {
        ostringstream oss;
        oss.precision(10);
        oss.setf(ios::showpoint);
        oss.setf(ios::scientific);
        oss << mg_structure_gam[i];

        str_data = str_data + "  " + oss.str();
        if( (i+1)%10 == 0 )
        {
          cout << "  " << str_data << endl;
          str_data.clear();
        }
      }

      if( static_cast<int>(str_data.size()) > 0 )
      {
        cout << "  " << str_data << endl;
        str_data.clear();
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int  MultiGroupDataGeneratorInputReader::check_mg_structure_mode(string str_data)
{
  transform(str_data.begin(), str_data.end(), str_data.begin(), ::tolower);

  if( str_data == "auto" )
  {
    return -1;
  }

  if( static_cast<int>(str_data.find("ign")) == 0 )
  {
    string ign_no_str = str_data.substr(3);

    str_obj.string_check(ign_no_str);
    return numeric_string_cast<int>(ign_no_str);
  }

  string str_mod = str_data;
  replace(str_mod.begin(), str_mod.end(), '_', '-');
  replace(str_mod.begin(), str_mod.end(), '/', '-');
  if( str_mod == "csewg-239"         ) return  2;
  if( str_mod == "csewg"             ) return  2;
  if( str_mod == "lanl-30"           ) return  3;
  if( str_mod == "anl-27"            ) return  4;
  if( str_mod == "anl"               ) return  4;
  if( str_mod == "rrd-50"            ) return  5;
  if( str_mod == "rrd"               ) return  5;
  if( str_mod == "gam-i-68"          ) return  6;
  if( str_mod == "gam-i"             ) return  6;
  if( str_mod == "gam-68"            ) return  6;
  if( str_mod == "gam-ii-100"        ) return  7;
  if( str_mod == "gam-ii"            ) return  7;
  if( str_mod == "gam-100"           ) return  7;
  if( str_mod == "laser-thermos-35"  ) return  8;
  if( str_mod == "laser-thermos"     ) return  8;
  if( str_mod == "laser"             ) return  8;
  if( str_mod == "laser-35"          ) return  8;
  if( str_mod == "epri-cpm-69"       ) return  9;
  if( str_mod == "epri-cpm"          ) return  9;
  if( str_mod == "epri"              ) return  9;
  if( str_mod == "epri-69"           ) return  9;
  if( str_mod == "lanl-187"          ) return 10;
  if( str_mod == "lanl-70"           ) return 11;
  if( str_mod == "sand-ii-620"       ) return 12;
  if( str_mod == "sand-ii"           ) return 12;
  if( str_mod == "sand-620"          ) return 12;
  if( str_mod == "lanl-80"           ) return 13;
  if( str_mod == "eurlib-100"        ) return 14;
  if( str_mod == "eurlib"            ) return 14;
  if( str_mod == "sand-iia-640"      ) return 15;
  if( str_mod == "sand-iia"          ) return 15;
  if( str_mod == "sand-640"          ) return 15;
  if( str_mod == "vitamin-e-174"     ) return 16;
  if( str_mod == "vitamin-e"         ) return 16;
  if( str_mod == "vitamin-174"       ) return 16;
  if( str_mod == "vit-e-174"         ) return 16;
  if( str_mod == "vit-e"             ) return 16;
  if( str_mod == "vit-174"           ) return 16;
  if( str_mod == "vitamin-j-175"     ) return 17;
  if( str_mod == "vitamin-j"         ) return 17;
  if( str_mod == "vitamin-175"       ) return 17;
  if( str_mod == "vit-j-175"         ) return 17;
  if( str_mod == "vit-j"             ) return 17;
  if( str_mod == "vit-175"           ) return 17;
  if( str_mod == "xmas-nea-lanl-172" ) return 18;
  if( str_mod == "xmas-nea-lanl"     ) return 18;
  if( str_mod == "xmas-lanl"         ) return 18;
  if( str_mod == "xmas-nea"          ) return 18;
  if( str_mod == "ecco-33"           ) return 19;
  if( str_mod == "ecco-1968"         ) return 20;
  if( str_mod == "tripoli-315"       ) return 21;
  if( str_mod == "tripoli"           ) return 21;
  if( str_mod == "xmas-lwpc-172"     ) return 22;
  if( str_mod == "xmas-lwpc"         ) return 22;
  if( str_mod == "vit-j-lwpc-175"    ) return 23;
  if( str_mod == "vit-j-lwpc"        ) return 23;
  if( str_mod == "shem-cea-281"      ) return 24;
  if( str_mod == "shem-cea"          ) return 24;
  if( str_mod == "shem-281"          ) return 24;
  if( str_mod == "shem-epm-295"      ) return 25;
  if( str_mod == "shem-295"          ) return 25;
  if( str_mod == "shem-cea-epm-361"  ) return 26;
  if( str_mod == "shem-cea-epm"      ) return 26;
  if( str_mod == "shem-361"          ) return 26;
  if( str_mod == "shem-epm-315"      ) return 27;
  if( str_mod == "shem-315"          ) return 27;
  if( str_mod == "rahab-aecl-89"     ) return 28;
  if( str_mod == "rahab-aecl"        ) return 28;
  if( str_mod == "rahab-89"          ) return 28;
  if( str_mod == "rahab"             ) return 28;
  if( str_mod == "ccfe-660"          ) return 29;
  if( str_mod == "ccfe"              ) return 29;
  if( str_mod == "ukaea-1025"        ) return 30;
  if( str_mod == "ukaea-1067"        ) return 31;
  if( str_mod == "ukaea-1102"        ) return 32;
  if( str_mod == "ukaea-142"         ) return 33;
  if( str_mod == "lanl-618"          ) return 34;
  if( str_mod == "vitamin-b6-199"    ) return 101;
  if( str_mod == "vitamin-199"       ) return 101;
  if( str_mod == "vit-b6-199"        ) return 101;
  if( str_mod == "vit-199"           ) return 101;
  if( str_mod == "vitamin-b6-200"    ) return 102;
  if( str_mod == "vitamin-200"       ) return 102;
  if( str_mod == "vit-b6-200"        ) return 102;
  if( str_mod == "vit-200"           ) return 102;
  if( str_mod == "srac-107"          ) return 107;
  if( str_mod == "srac"              ) return 107;
  if( str_mod == "srac-108"          ) return 108;
  if( str_mod == "srac-200"          ) return 109;
  if( str_mod == "mosra-srac-200"    ) return 109;
  if( str_mod == "mosra-200"         ) return 109;
  if( str_mod == "mosra-srac"        ) return 109;

  return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int  MultiGroupDataGeneratorInputReader::check_mg_structure_mode_gam(string str_data)
{
  transform(str_data.begin(), str_data.end(), str_data.begin(), ::tolower);

  if( static_cast<int>(str_data.find("igg")) == 0 )
  {
    string igg_no_str = str_data.substr(3);

    str_obj.string_check(igg_no_str);
    return numeric_string_cast<int>(igg_no_str);
  }

  string str_mod = str_data;
  replace(str_mod.begin(), str_mod.end(), '_', '-');
  replace(str_mod.begin(), str_mod.end(), '/', '-');
  if( str_mod == "csewg-94"          ) return  2;
  if( str_mod == "csewg"             ) return  2;
  if( str_mod == "lanl-12"           ) return  3;
  if( str_mod == "steiner-21"        ) return  4;
  if( str_mod == "steiner"           ) return  4;
  if( str_mod == "straker-22"        ) return  5;
  if( str_mod == "straker"           ) return  5;
  if( str_mod == "lanl-48"           ) return  6;
  if( str_mod == "lanl-24"           ) return  7;
  if( str_mod == "vitamin-c-36"      ) return  8;
  if( str_mod == "vitamin-c"         ) return  8;
  if( str_mod == "vitamin-36"        ) return  8;
  if( str_mod == "vit-c-36"          ) return  8;
  if( str_mod == "vit-c"             ) return  8;
  if( str_mod == "vit-36"            ) return  8;
  if( str_mod == "vitamin-e-38"      ) return  9;
  if( str_mod == "vitamin-e"         ) return  9;
  if( str_mod == "vitamin-38"        ) return  9;
  if( str_mod == "vit-e-38"          ) return  9;
  if( str_mod == "vit-e"             ) return  9;
  if( str_mod == "vit-38"            ) return  9;
  if( str_mod == "vitamin-j-42"      ) return 10;
  if( str_mod == "vitamin-j"         ) return 10;
  if( str_mod == "vitamin-42"        ) return 10;
  if( str_mod == "vit-j-42"          ) return 10;
  if( str_mod == "vit-j"             ) return 10;
  if( str_mod == "vit-42"            ) return 10;

  return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputReader::clear_ace_file_name()
{
  ace_file_name.clear();
  ace_file_name_tsl.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputReader::set_max_thermal_ene_e_in(vector<string>& input_data)
{
  if( static_cast<int>(input_data.size()) > 1 )
  {
    string class_name = "MultiGroupDataGeneratorInputReader";
    string func_name  = "set_max_thermal_ene_e_in(vector<string>& input_data)";
    frendy_utils.error_input_data_size_is_larger_than_one(class_name, func_name, input_data);
  }

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  max_thermal_ene_e_in [eV]            : " << input_data[0] << endl;
  }

  str_obj.string_check(input_data[0]);
  max_thermal_ene_e_in = numeric_string_cast<Real>(input_data[0]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputReader::set_max_thermal_ene_e_out(vector<string>& input_data)
{
  if( static_cast<int>(input_data.size()) > 1 )
  {
    string class_name = "MultiGroupDataGeneratorInputReader";
    string func_name  = "set_max_thermal_ene_e_out(vector<string>& input_data)";
    frendy_utils.error_input_data_size_is_larger_than_one(class_name, func_name, input_data);
  }

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  max_thermal_ene_e_out [eV]           : " << input_data[0] << endl;
  }

  str_obj.string_check(input_data[0]);
  max_thermal_ene_e_out = numeric_string_cast<Real>(input_data[0]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputReader::set_mg_process_data(vector<string>& input_data)
{
  int i_max = static_cast<int>(input_data.size());
  mg_process_data.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    cout << "  No. of mg_process_data               : " << i_max << endl;
    if( print_set_data_flg == frendy_utils.print_set_data )
    {
      cout << "    mg_process_data                    : " << input_data[i] << endl;
    }
 
    str_obj.string_check(input_data[i]);
    mg_process_data[i] = numeric_string_cast<Integer>(input_data[i]);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputReader::set_mg_process_reaction(vector<string>& input_data)
{
  int i_max = static_cast<int>(input_data.size());
  mg_process_reaction.resize(i_max);

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  No. of mg_process_reaction           : " << i_max << endl;
  }

  for(int i=0; i<i_max; i++)
  {
    if( print_set_data_flg == frendy_utils.print_set_data )
    {
      cout << "    mg_process_reaction                : " << input_data[i] << endl;
    }
 
    str_obj.string_check(input_data[i]);
    mg_process_reaction[i] = numeric_string_cast<Integer>(input_data[i]);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputReader::set_mg_process_reaction_name(vector<string>& input_data)
{
  int i_max = static_cast<int>(input_data.size());

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  No. of mg_process_reaction_name      : " << i_max << endl;
  }

  for(int i=0; i<i_max; i++)
  {
    if( print_set_data_flg == frendy_utils.print_set_data )
    {
      cout << "    mg_process_reaction_name           : " << input_data[i] << endl;
    }
  }

  mg_process_reaction_name = input_data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputReader::set_mg_ufg_structure(vector<string>& input_data)
{
  int i_max = static_cast<int>(input_data.size());
  mg_ufg_structure.resize(i_max);

  int mix_inp_flg = 0;
  if( i_max > 3 )
  {
    string div_mode_check = input_data[2];
    transform(div_mode_check.begin(), div_mode_check.end(), div_mode_check.begin(), ::tolower);
    if( div_mode_check == "el" || div_mode_check == "ee" )
    {
      mix_inp_flg = 1;
    }
  }

  if( mix_inp_flg == 0 )
  {
    if( print_set_data_flg == frendy_utils.print_set_data )
    {
      cout << "  No. of mg_ufg_structure              : " << i_max - 1 << endl;
    }

    for(int i=0; i<i_max; i++)
    {
      if( print_set_data_flg == frendy_utils.print_set_data )
      {
        cout << "    mg_ufg_structure [eV]              : " << input_data[i] << endl;
      }
 
      str_obj.string_check(input_data[i]);
      mg_ufg_structure[i] = numeric_string_cast<Real>(input_data[i]);
    }
  }
  else //if( mix_inp_flg == 1 )
  {
    int data_no = i_max / 3;
    if( print_set_data_flg == frendy_utils.print_set_data )
    {
      cout << "  No. of mg_ufg_structure, mg_ufg_div_no, and mg_ufg_div_mode : " << data_no << endl;
    }

    if( i_max % 3 != 1 )
    {
      string class_name = "MultiGroupDataGeneratorInputReader";
      string func_name  = "set_mg_ufg_structure(vector<string>& input_data)";

      ostringstream oss01;
      oss01 << i_max;

      string str_data01 = "The total number of mg_ufg_structure data : " + oss01.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back("The total number of mg_ufg_structure data must be a multiple of three + 1 as follows:");
      err_com.push_back("   mg_ufg_structure[0]  mg_ufg_div_no[0]  mg_ufg_div_mode[0]");
      err_com.push_back("   mg_ufg_structure[1]  mg_ufg_div_no[1]  mg_ufg_div_mode[1]");
      err_com.push_back("                              .");
      err_com.push_back("                              .");
      err_com.push_back("                              .");
      err_com.push_back("   mg_ufg_structure[i]  mg_ufg_div_no[i]  mg_ufg_div_mode[i]");
      err_com.push_back("   mg_ufg_structure[i+1]");
      err_com.push_back("Please modify mg_ufg_structure data.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    mg_ufg_structure.resize(data_no+1);
    mg_ufg_div_no.resize(data_no);
    mg_ufg_div_mode.resize(data_no);

    if( print_set_data_flg == frendy_utils.print_set_data )
    {
      cout << "    mg_ufg_structure [eV] / mg_ufg_div_no / mg_ufg_div_mode" << endl;
    }

    for(int i=0; i<data_no; i++)
    {
      if( print_set_data_flg == frendy_utils.print_set_data )
      {
        cout << "      "
             << input_data[3*i] << " / " << input_data[3*i+1] << " / " << input_data[3*i+2] << endl;
      }

      mg_ufg_structure[i] = numeric_string_cast<Real>(input_data[3*i]);
      mg_ufg_div_no[i]    = numeric_string_cast<Integer>(input_data[3*i+1]);
      mg_ufg_div_mode[i]  = input_data[3*i+2];
    }

    if( print_set_data_flg == frendy_utils.print_set_data )
    {
      cout << "      " << input_data[i_max-1] << endl;
    }

    mg_ufg_structure[data_no] = numeric_string_cast<Real>(input_data[i_max-1]);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputReader::set_mg_ufg_div_no(vector<string>& input_data)
{
  int i_max = static_cast<int>(input_data.size());
  mg_ufg_div_no.resize(i_max);

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  No. of mg_ufg_div_no                 : " << i_max << endl;
  }

  for(int i=0; i<i_max; i++)
  {
    if( print_set_data_flg == frendy_utils.print_set_data )
    {
      cout << "    mg_ufg_div_no                      : " << input_data[i] << endl;
    }
 
    str_obj.string_check(input_data[i]);
    mg_ufg_div_no[i] = numeric_string_cast<Integer>(input_data[i]);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputReader::set_mg_ufg_div_mode(vector<string>& input_data)
{
  int i_max = static_cast<int>(input_data.size());

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  No. of mg_ufg_div_mode               : " << i_max << endl;
  }

  for(int i=0; i<i_max; i++)
  {
    if( print_set_data_flg == frendy_utils.print_set_data )
    {
      cout << "    mg_ufg_div_mode                    : " << input_data[i] << endl;
    }
  }

  mg_ufg_div_mode = input_data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputReader::set_mg_number_density(vector<string>& input_data)
{
  int i_max = static_cast<int>(input_data.size());
  mg_number_density.resize(i_max);

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  No. of mg_number_density             : " << i_max << endl;
  }

  for(int i=0; i<i_max; i++)
  {
    if( print_set_data_flg == frendy_utils.print_set_data )
    {
      cout << "    mg_number_density [1/barn/cm]      : " << input_data[i] << endl;
    }
 
    str_obj.string_check(input_data[i]);
    mg_number_density[i] = numeric_string_cast<Real>(input_data[i]);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputReader::set_mg_tsl_data_type(vector<string>& input_data)
{
  int i_max = static_cast<int>(input_data.size());

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  No. of mg_tsl_data_type              : " << i_max << endl;
  }

  for(int i=0; i<i_max; i++)
  {
    if( print_set_data_flg == frendy_utils.print_set_data )
    {
      cout << "    mg_tsl_data_type                   : " << input_data[i] << endl;
    }
  }
  mg_tsl_data_type = input_data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputReader::set_mg_flux_calc_mode(vector<string>& input_data)
{
  int i_max = static_cast<int>(input_data.size());

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  No. of mg_flux_calc_mode             : " << i_max << endl;
  }

  for(int i=0; i<i_max; i++)
  {
    if( print_set_data_flg == frendy_utils.print_set_data )
    {
      cout << "    mg_flux_calc_mode                  : " << input_data[i] << endl;
    }
  }
  mg_flux_calc_mode = input_data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputReader::set_mg_flux_calc_w_eh_el(vector<string>& input_data)
{
  int data_no = static_cast<int>(input_data.size());

  if( data_no%3 != 0 )
  {
    string class_name = "MultiGroupDataGeneratorInputReader";
    string func_name  = "set_mg_flux_calc_w_eh_el";

    vector<string> err_com;
    err_com.push_back("Data number of mg_flux_calc_w_eh_el must be multiple of 3.");
    err_com.push_back("mg_flux_calc_w_eh_el consists of weight (w), upper and lower");
    err_com.push_back("limit of energy (eh and el)." );
    err_com.push_back("Please check set_mg_flux_calc_w_eh_el data.");
    err_com.push_back("");
    err_com.push_back("List of set_mg_flux_calc_w_eh_el data");
    for(int i=0; i<data_no; i++)
    {
      err_com.push_back(input_data[i]);
 
      if( i+1%3 == 0 )
      {
        err_com.push_back("");
      }
    }
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  int i_max = data_no / 3;
  vector<string> input_data_w, input_data_eh, input_data_el;
  input_data_w.resize(i_max);
  input_data_eh.resize(i_max);
  input_data_el.resize(i_max);

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  No. of mg_flux_calc_w_eh_el(w/eh/el) : " << i_max << endl;
  }

  for(int i=0; i<i_max; i++)
  {
    if( print_set_data_flg == frendy_utils.print_set_data )
    {
      cout << "    mg_flux_calc_w_eh_el (w/eh [eV]/el [eV]) : "
           << input_data[i*3] << " / " << input_data[i*3+1] << " / "
           << input_data[i*3+2] << endl;
    }
 
    str_obj.string_check(input_data[i*3]);
    str_obj.string_check(input_data[i*3+1]);
    str_obj.string_check(input_data[i*3+2]);
    input_data_w[i]  = input_data[i*3];
    input_data_eh[i] = input_data[i*3+1];
    input_data_el[i] = input_data[i*3+2];
  }

  set_mg_flux_calc_w(input_data_w);
  set_mg_flux_calc_eh(input_data_eh);
  set_mg_flux_calc_el(input_data_el);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputReader::set_mg_flux_calc_w(vector<string>& input_data)
{
  int i_max = static_cast<int>(input_data.size());
  mg_flux_calc_w.resize(i_max);

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  No. of set_mg_flux_calc_w            : " << i_max << endl;
  }

  for(int i=0; i<i_max; i++)
  {
    if( print_set_data_flg == frendy_utils.print_set_data )
    {
      cout << "    set_mg_flux_calc_w                 : " << input_data[i] << endl;
    }

    str_obj.string_check(input_data[i]);
    mg_flux_calc_w[i] = numeric_string_cast<Real>(input_data[i]);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputReader::set_mg_flux_calc_eh(vector<string>& input_data)
{
  int i_max = static_cast<int>(input_data.size());
  mg_flux_calc_eh.resize(i_max);

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  No. of set_mg_flux_calc_eh           : " << i_max << endl;
  }

  for(int i=0; i<i_max; i++)
  {
    if( print_set_data_flg == frendy_utils.print_set_data )
    {
      cout << "    set_mg_flux_calc_eh [eV]           : " << input_data[i] << endl;
    }

    str_obj.string_check(input_data[i]);
    mg_flux_calc_eh[i] = numeric_string_cast<Real>(input_data[i]);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputReader::set_mg_flux_calc_el(vector<string>& input_data)
{
  int i_max = static_cast<int>(input_data.size());
  mg_flux_calc_el.resize(i_max);

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  No. of set_mg_flux_calc_el           : " << i_max << endl;
  }

  for(int i=0; i<i_max; i++)
  {
    if( print_set_data_flg == frendy_utils.print_set_data )
    {
      cout << "    set_mg_flux_calc_el [eV]           : " << input_data[i] << endl;
    }

    str_obj.string_check(input_data[i]);
    mg_flux_calc_el[i] = numeric_string_cast<Real>(input_data[i]);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputReader::set_mg_thermal_xs_treatment(vector<string>& input_data)
{
  int data_no = static_cast<int>(input_data.size());

  if( data_no != 1 )
  {
    string class_name = "MultiGroupDataGeneratorInputReader";
    string func_name  = "set_mg_thermal_xs_treatment";

    vector<string> err_com;
    err_com.push_back("Data number of mg_thermal_xs_treatment must be 1.");
    err_com.push_back("Please check mg_thermal_xs_treatment data.");
    err_com.push_back("");
    err_com.push_back("List of mg_thermal_xs_treatment data");
    for(int i=0; i<data_no; i++)
    {
      err_com.push_back(input_data[i]);
    }
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  cout << "    mg_thremal_xs_treatment            : " << input_data[0] << endl;

  string mode_name = input_data[0];
  transform(mode_name.begin(), mode_name.end(), mode_name.begin(), ::tolower);

  Integer calc_flg = 0;
  if( mode_name == "on" || mode_name == "yes" || mode_name == "def" || mode_name == "default" )
  {
    calc_flg = frendy_utils.on;
  }
  else if( mode_name == "off" || mode_name == "no" )
  {
    calc_flg = frendy_utils.off;
  }
  else
  {
    string class_name = "MultiGroupDataGeneratorInputReader";
    string func_name  = "set_mg_thermal_xs_treatment";

    vector<string> err_com;
    err_com.push_back("Available mg_thermal_xs_treatment is ON, OFF, YES, and NO.");
    err_com.push_back("Please check mg_thermal_xs_treatment data.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  set_mg_thermal_xs_treatment(calc_flg);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputReader::set_potential_scat_xs(vector<string>& input_data)
{
  int i_max = static_cast<int>(input_data.size());
  potential_scat_xs.resize(i_max);

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  No. of potential_scat_xs             : " << i_max << endl;
  }

  for(int i=0; i<i_max; i++)
  {
    if( print_set_data_flg == frendy_utils.print_set_data )
    {
      cout << "    potential_scat_xs [barn]           : " << input_data[i] << endl;
    }
 
    str_obj.string_check(input_data[i]);
    potential_scat_xs[i] = numeric_string_cast<Real>(input_data[i]);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputReader::set_reso_up_scat(vector<string>& input_data)
{
  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    int i_max = static_cast<int>(input_data.size());
    cout << "  No. of resonance upscattering data   : " << i_max << endl;

    for(int i=0; i<i_max; i++)
    {
      cout << "    reso_up_scat_0k_data               : " << input_data[i] << endl;
    }
  }

  set_reso_up_scat_0k_data(input_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputReader::set_reso_up_scat_mode(vector<string>& input_data)
{
  int data_no = static_cast<int>(input_data.size());

  if( data_no != 1 )
  {
    string class_name = "MultiGroupDataGeneratorInputReader";
    string func_name  = "set_reso_up_scat_mode";

    vector<string> err_com;
    err_com.push_back("Data number of reso_up_scat_mode must be 1.");
    err_com.push_back("Please check reso_up_scat_mode data.");
    err_com.push_back("");
    err_com.push_back("List of reso_up_scat_mode data");
    for(int i=0; i<data_no; i++)
    {
      err_com.push_back(input_data[i]);
    }
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "    reso_up_scat_mode                   : " << input_data[0] << endl;
  }

  string mode_name = input_data[0];
  transform(mode_name.begin(), mode_name.end(), mode_name.begin(), ::tolower);

  Integer calc_mode = 0;
  if( mode_name == "2"   || mode_name == "2d" || mode_name == "all" || mode_name == "both" ||
      mode_name == "def" || mode_name == "default" )
  {
    calc_mode = reso_up_scat_2d;
  }
  else if( mode_name == "1" || mode_name == "1d" || mode_name == "xs" )
  {
    calc_mode = reso_up_scat_1d;
  }
  else
  {
    string class_name = "MultiGroupDataGeneratorInputReader";
    string func_name  = "set_reso_up_scat_mode";

    vector<string> err_com;
    err_com.push_back("Available reso_up_scat_mode is 1D and 2D.");
    err_com.push_back("Please check reso_up_scat_mode data.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  set_reso_up_scat_mode(calc_mode);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//Setter

void MultiGroupDataGeneratorInputReader::set_print_title_flg(int int_val)
{
  print_title_flg = int_val;
}

void MultiGroupDataGeneratorInputReader::set_ace_output_flg(int int_val)
{
  ace_output_flg = int_val;

  if( ace_output_flg != frendy_utils.on && ace_output_flg != frendy_utils.off )
  {
    string class_name = "MultiGroupDataGeneratorInputReader";
    string func_name  = "set_ace_output_flg(int int_val)";

    ostringstream oss01, oss02;
    oss01 << frendy_utils.on;
    oss02 << frendy_utils.off;

    string str_data01 = "  ON  : " + oss01.str();
    string str_data02 = "  OFF : " + oss02.str();

    vector<string> err_com;
    err_com.push_back("Available ace_output_flg (ace_output_option) is as follows:");
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("Please check ace_output_flg (ace_output_option).");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

void MultiGroupDataGeneratorInputReader::set_input_file_name(string str_data)
{
  input_file_name = str_data;
}

void MultiGroupDataGeneratorInputReader::set_mg_print_reaction(vector<Integer> int_vec)
{
  mg_print_reaction = int_vec;
}

void MultiGroupDataGeneratorInputReader::set_mg_mat_list(vector<Integer> int_vec)
{
  mg_mat_list = int_vec;
}

void MultiGroupDataGeneratorInputReader::set_mg_start_file_mode(string str_data)
{
  mg_start_file_mode = str_data;
}

void MultiGroupDataGeneratorInputReader::set_mg_weighting_spectrum_mode(string str_data)
{
  mg_weighting_spectrum_mode = str_data;
}

void MultiGroupDataGeneratorInputReader::set_mg_label_data(string str_data)
{
  mg_label_data = str_data;
}

void MultiGroupDataGeneratorInputReader::set_mg_weighting_spectrum_el(Real real_val)
{
  mg_weighting_spectrum_el = real_val;
}

void MultiGroupDataGeneratorInputReader::set_mg_weighting_spectrum_eh(Real real_val)
{
  mg_weighting_spectrum_eh = real_val;
}

void MultiGroupDataGeneratorInputReader::set_mg_weighting_fission_temp(Real real_val)
{
  mg_weighting_fission_temp = real_val;
}

void MultiGroupDataGeneratorInputReader::set_mg_weighting_1e_el(Real real_val)
{
  mg_weighting_1e_el = real_val;
}

void MultiGroupDataGeneratorInputReader::set_mg_weighting_1e_eh(Real real_val)
{
  mg_weighting_1e_eh = real_val;
}

void MultiGroupDataGeneratorInputReader::set_temp(Real real_val)
{
  temp_set_flg = 1;
  temp = real_val;
}

void MultiGroupDataGeneratorInputReader::set_max_thermal_ene_e_in(Real real_val)
{
  max_thermal_ene_e_in = real_val;
}

void MultiGroupDataGeneratorInputReader::set_max_thermal_ene_e_out(Real real_val)
{
  max_thermal_ene_e_out = real_val;
}

void MultiGroupDataGeneratorInputReader::set_mg_weighting_spectrum_data_e(vector<Real> real_vec)
{
  mg_weighting_spectrum_data_e = real_vec;
}

void MultiGroupDataGeneratorInputReader::set_mg_weighting_spectrum_data_w(vector<Real> real_vec)
{
  mg_weighting_spectrum_data_w = real_vec;
}

void MultiGroupDataGeneratorInputReader::set_sigma_zero_data(vector<Real> real_vec)
{
  sigma_zero_data = real_vec;
}

void MultiGroupDataGeneratorInputReader::set_mg_structure(vector<Real> real_vec)
{
  mg_structure = real_vec;
}

void MultiGroupDataGeneratorInputReader::set_mg_structure_gam(vector<Real> real_vec)
{
  mg_structure_gam = real_vec;
}

void MultiGroupDataGeneratorInputReader::set_mg_ufg_structure(vector<Real> real_vec)
{
  mg_ufg_structure = real_vec;
}

void MultiGroupDataGeneratorInputReader::set_mg_number_density(vector<Real> real_vec)
{
  mg_number_density = real_vec;
}

void MultiGroupDataGeneratorInputReader::set_mg_flux_calc_w(vector<Real> real_vec)
{
  mg_flux_calc_w = real_vec;
}

void MultiGroupDataGeneratorInputReader::set_mg_flux_calc_eh(vector<Real> real_vec)
{
  mg_flux_calc_eh = real_vec;
}

void MultiGroupDataGeneratorInputReader::set_mg_flux_calc_el(vector<Real> real_vec)
{
  mg_flux_calc_el = real_vec;
}

void MultiGroupDataGeneratorInputReader::set_potential_scat_xs(vector<Real> real_vec)
{
  potential_scat_xs = real_vec;
}

void MultiGroupDataGeneratorInputReader::set_reso_up_scat_0k_data(vector<string> str_vec)
{
  reso_up_scat_0k_data = str_vec;

  int i_max = static_cast<int>(reso_up_scat_0k_data.size());
  if( i_max == 0 )
  {
    return;
  }

  int skip_flg = 0;
  for(int i=0; i<i_max; i++)
  {
    string str_data = reso_up_scat_0k_data[i];
    transform(str_data.begin(), str_data.end(), str_data.begin(), ::tolower);
    if( str_data == "skip" || str_data == "none" || str_data == "off" )
    {
      skip_flg++;
      reso_up_scat_0k_data[i].clear();
    }
  }

  if( skip_flg == i_max )
  {
    clr_obj.clear_vec_array1_str(reso_up_scat_0k_data);

    string class_name = "MultiGroupDataGeneratorInputReader";
    string func_name  = "set_reso_up_scat_0k_data";

    vector<string> err_com;
    err_com.push_back("The all data is skip, none, or off.");
    err_com.push_back("The consideration of resonance upscattering is skipped.");
    err_com.push_back("Please set the file name if you want consider the resonance upscattering.");
    err_obj.output_caution(class_name, func_name, err_com);
  }
}

void MultiGroupDataGeneratorInputReader::set_reso_up_scat_mode(Integer int_val)
{
  if( int_val != reso_up_scat_1d && int_val != reso_up_scat_2d )
  {
    string class_name = "MultiGroupDataGeneratorInputReader";
    string func_name  = "set_reso_up_scat_mode(Integer int_val)";

    ostringstream oss01, oss02;
    oss01 << reso_up_scat_1d;
    oss02 << reso_up_scat_2d;

    string str_data01 = "  1D : " + oss01.str();
    string str_data02 = "  2D : " + oss02.str();

    vector<string> err_com;
    err_com.push_back("Available reso_up_scat_mode is as follows:");
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("Please check reso_up_scat_mode data.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  reso_up_scat_mode = int_val;
}

void MultiGroupDataGeneratorInputReader::set_mg_weighting_spectrum_data_int(vector<Integer> int_vec)
{
  mg_weighting_spectrum_data_int = int_vec;
}

void MultiGroupDataGeneratorInputReader::set_mg_weighting_spectrum_data_nbt(vector<Integer> int_vec)
{
  mg_weighting_spectrum_data_nbt = int_vec;
}

void MultiGroupDataGeneratorInputReader::set_mg_process_data(vector<Integer> int_vec)
{
  mg_process_data = int_vec;
}

void MultiGroupDataGeneratorInputReader::set_mg_process_reaction(vector<Integer> int_vec)
{
  mg_process_reaction = int_vec;
}

void MultiGroupDataGeneratorInputReader::set_mg_ufg_div_no(vector<Integer> int_vec)
{
  mg_ufg_div_no = int_vec;
}

void MultiGroupDataGeneratorInputReader::set_legendre_order(Integer int_val)
{
  legendre_order = int_val;
}

void MultiGroupDataGeneratorInputReader::set_mg_thermal_xs_treatment(Integer int_val)
{
  if( int_val != frendy_utils.on && int_val != frendy_utils.off )
  {
    string class_name = "MultiGroupDataGeneratorInputReader";
    string func_name  = "set_mg_thermal_xs_treatment(Integer int_val)";

    ostringstream oss01, oss02;
    oss01 << frendy_utils.on;
    oss02 << frendy_utils.off;

    string str_data01 = "  ON  : " + oss01.str();
    string str_data02 = "  OFF : " + oss02.str();

    vector<string> err_com;
    err_com.push_back("Available mg_thermal_xs_treatment is as follows:");
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("Please check mg_thermal_xs_treatment data.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  mg_thermal_xs_treatment = int_val;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//Getter

int             MultiGroupDataGeneratorInputReader::get_process_tsl_mode_flg()
{
  return process_tsl_mode_flg;
}

int             MultiGroupDataGeneratorInputReader::get_process_gam_mode_flg()
{
  return process_gam_mode_flg;
}

int             MultiGroupDataGeneratorInputReader::get_mg_start_file_flg()
{
  return mg_start_file_flg;
}

int             MultiGroupDataGeneratorInputReader::get_print_set_data_flg()
{
  return print_set_data_flg;
}

int             MultiGroupDataGeneratorInputReader::get_process_flg()
{
  return process_flg;
}

int             MultiGroupDataGeneratorInputReader::get_print_title_flg()
{
  return print_title_flg;
}

int             MultiGroupDataGeneratorInputReader::get_ace_output_flg()
{
  return ace_output_flg;
}

string          MultiGroupDataGeneratorInputReader::get_input_file_name()
{
  return input_file_name;
}

vector<string>  MultiGroupDataGeneratorInputReader::get_nucl_file_name()
{
  return nucl_file_name;
}

vector<string>  MultiGroupDataGeneratorInputReader::get_nucl_file_name_tsl()
{
  return nucl_file_name_tsl;
}

vector<string>  MultiGroupDataGeneratorInputReader::get_ace_file_name()
{
  return ace_file_name;
}

vector<string>  MultiGroupDataGeneratorInputReader::get_ace_file_name_tsl()
{
  return ace_file_name_tsl;
}

vector<string>  MultiGroupDataGeneratorInputReader::get_mg_file_name()
{
  return mg_file_name;
}

vector<string>  MultiGroupDataGeneratorInputReader::get_mg_edit_mode()
{
  return mg_edit_mode;
}

vector<string>  MultiGroupDataGeneratorInputReader::get_mg_process_reaction_name()
{
  return mg_process_reaction_name;
}

vector<string>  MultiGroupDataGeneratorInputReader::get_mg_ufg_div_mode()
{
  return mg_ufg_div_mode;
}

vector<string>  MultiGroupDataGeneratorInputReader::get_mg_tsl_data_type()
{
  return mg_tsl_data_type;
}

vector<string>  MultiGroupDataGeneratorInputReader::get_mg_flux_calc_mode()
{
  return mg_flux_calc_mode;
}

vector<Integer> MultiGroupDataGeneratorInputReader::get_mg_print_reaction()
{
  return mg_print_reaction;
}

vector<Integer> MultiGroupDataGeneratorInputReader::get_mg_mat_list()
{
  return mg_mat_list;
}

string          MultiGroupDataGeneratorInputReader::get_mg_start_file_mode()
{
  return mg_start_file_mode;
}

string          MultiGroupDataGeneratorInputReader::get_mg_weighting_spectrum_mode()
{
  return mg_weighting_spectrum_mode;
}

string          MultiGroupDataGeneratorInputReader::get_mg_label_data()
{
  return mg_label_data;
}

Real            MultiGroupDataGeneratorInputReader::get_mg_weighting_spectrum_el()
{
  return mg_weighting_spectrum_el;
}

Real            MultiGroupDataGeneratorInputReader::get_mg_weighting_spectrum_eh()
{
  return mg_weighting_spectrum_eh;
}

Real            MultiGroupDataGeneratorInputReader::get_mg_weighting_fission_temp()
{
  return mg_weighting_fission_temp;
}

Real            MultiGroupDataGeneratorInputReader::get_mg_weighting_1e_el()
{
  return mg_weighting_1e_el;
}

Real            MultiGroupDataGeneratorInputReader::get_mg_weighting_1e_eh()
{
  return mg_weighting_1e_eh;
}

Real            MultiGroupDataGeneratorInputReader::get_temp()
{
  if( temp_set_flg == 0 )
  {
    string mode_name = mg_start_file_mode;
    transform(mode_name.begin(), mode_name.end(), mode_name.begin(), ::tolower);
    if( mode_name == "ace" || mg_start_file_flg == frendy_utils.start_file_ace )
    {
      temp = -100.0;
    }
  }

  return temp;
}

Real            MultiGroupDataGeneratorInputReader::get_max_thermal_ene_e_in()
{
  return max_thermal_ene_e_in;
}

Real            MultiGroupDataGeneratorInputReader::get_max_thermal_ene_e_out()
{
  return max_thermal_ene_e_out;
}

vector<Real>    MultiGroupDataGeneratorInputReader::get_mg_weighting_spectrum_data_e()
{
  return mg_weighting_spectrum_data_e;
}

vector<Real>    MultiGroupDataGeneratorInputReader::get_mg_weighting_spectrum_data_w()
{
  return mg_weighting_spectrum_data_w;
}

vector<Real>    MultiGroupDataGeneratorInputReader::get_sigma_zero_data()
{
  return sigma_zero_data;
}

vector<Real>    MultiGroupDataGeneratorInputReader::get_mg_structure()
{
  return mg_structure;
}

vector<Real>    MultiGroupDataGeneratorInputReader::get_mg_structure_gam()
{
  return mg_structure_gam;
}

vector<Real>    MultiGroupDataGeneratorInputReader::get_mg_ufg_structure()
{
  return mg_ufg_structure;
}

vector<Real>    MultiGroupDataGeneratorInputReader::get_mg_number_density()
{
  return mg_number_density;
}

vector<Real>    MultiGroupDataGeneratorInputReader::get_mg_flux_calc_w()
{
  return mg_flux_calc_w;
}

vector<Real>    MultiGroupDataGeneratorInputReader::get_mg_flux_calc_eh()
{
  return mg_flux_calc_eh;
}

vector<Real>    MultiGroupDataGeneratorInputReader::get_mg_flux_calc_el()
{
  return mg_flux_calc_el;
}

vector<Real>    MultiGroupDataGeneratorInputReader::get_potential_scat_xs()
{
  return potential_scat_xs;
}

vector<string>  MultiGroupDataGeneratorInputReader::get_reso_up_scat_0k_data()
{
  return reso_up_scat_0k_data;
}

Integer         MultiGroupDataGeneratorInputReader::get_reso_up_scat_mode()
{
  return reso_up_scat_mode;
}

string          MultiGroupDataGeneratorInputReader::get_sigma_zero_data_auto()
{
  return sigma_zero_data_auto;
}

vector<string>  MultiGroupDataGeneratorInputReader::get_mg_structure_auto()
{
  return mg_structure_auto;
}

vector<Integer> MultiGroupDataGeneratorInputReader::get_mg_weighting_spectrum_data_int()
{
  return mg_weighting_spectrum_data_int;
}

vector<Integer> MultiGroupDataGeneratorInputReader::get_mg_weighting_spectrum_data_nbt()
{
  return mg_weighting_spectrum_data_nbt;
}

vector<Integer> MultiGroupDataGeneratorInputReader::get_mg_process_data()
{
  return mg_process_data;
}

vector<Integer> MultiGroupDataGeneratorInputReader::get_mg_process_reaction()
{
  return mg_process_reaction;
}

vector<Integer> MultiGroupDataGeneratorInputReader::get_mg_ufg_div_no()
{
  return mg_ufg_div_no;
}

Integer         MultiGroupDataGeneratorInputReader::get_legendre_order()
{
  return legendre_order;
}

Integer         MultiGroupDataGeneratorInputReader::get_mg_thermal_xs_treatment()
{
  return mg_thermal_xs_treatment;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputReader::set_print_set_data_flg(vector<string>& input_data)
{
  string class_name = "MultiGroupDataGeneratorInputReader";
  string func_name  = "set_print_set_data_flg(vector<string>& input_data)";

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  print_set_data_flg                   : " << input_data[0] << endl;
  }

  print_set_data_flg = frendy_utils.read_print_set_data_flg(class_name, func_name, input_data);
}

void MultiGroupDataGeneratorInputReader::set_process_flg(vector<string>& input_data)
{
  string class_name = "MultiGroupDataGeneratorInputReader";
  string func_name  = "set_process_flg(vector<string>& input_data)";

  if( print_set_data_flg == frendy_utils.print_set_data )
  {
    cout << "  process_flg                          : " << input_data[0] << endl;
  }

  process_flg = frendy_utils.read_process_flg(class_name, func_name, input_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupDataGeneratorInputReader::set_print_set_data_flg(int int_val)
{
  frendy_utils.check_print_set_data_flg("MultiGroupDataGeneratorInputReader", int_val);

  print_set_data_flg = int_val;
}

void MultiGroupDataGeneratorInputReader::set_process_flg(int int_val)
{
  frendy_utils.check_process_flg("MultiGroupDataGeneratorInputReader", int_val);

  process_flg = int_val;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

