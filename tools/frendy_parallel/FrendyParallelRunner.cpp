#include "../tools/frendy_parallel/FrendyParallelRunner.hpp"

using namespace frendy;

//constructor
FrendyParallelRunner::FrendyParallelRunner()
{
}

//destructor
FrendyParallelRunner::~FrendyParallelRunner()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void FrendyParallelRunner::clear()
{
  separation_record = "/";
#ifdef _WIN32
  separation_record = "\/";
#endif

  read_flg     = 0;
  thread_no    = 1;
  restart_opt  = 0; //no restart
  ace_data_flg = 0;

  frendy_exe.clear();

  vector<string>().swap(temp_case);
  vector<string>().swap(temp_data);
  vector<string>().swap(bgxs_case);
  vector<string>().swap(bgxs_data);
  vector<string>().swap(frendy_inp_case);
  vector<string>().swap(frendy_inp_data);
  nucl_dir.clear();
  tsl_dir.clear();
  out_dir_inp.clear();
  out_dir_log.clear();
  out_dir_ace.clear();
  out_dir_gendf.clear();
  out_dir_matxs.clear();
  vector<vector<string> >().swap(temp_data_vec);
  vector<vector<string> >().swap(inp_list);

  vector<string>().swap(nucl_list);
  vector<string>().swap(tsl_list);
  vector<string>().swap(inp_base_list);
  vector<string>().swap(temp_list);
  vector<string>().swap(bgxs_list);
  vector<string>().swap(tsl_type_list);
  vector<string>().swap(frendy_inp_list);
  vector<string>().swap(frendy_log_list);
  vector<string>().swap(ace_list);
  vector<string>().swap(ace_list_tsl);
  vector<string>().swap(mg_list);
  vector<vector<string> >().swap(temp_vec_list);

  vector<string>().swap(skip_inp_list);
  vector<string>().swap(skip_log_list);
  vector<string>().swap(err_inp_list);
  vector<string>().swap(err_log_list);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void FrendyParallelRunner::read_input_file(string input_name)
{
  if( read_flg != 0 )
  {
    return;
  }
  read_flg = 1;

  //Remove comment data
  FileCommentRemover file_mod_obj;
  vector<string> input_data = file_mod_obj.remove_comment(input_name);
  file_mod_obj.clear();

  //Divide string data by space
  int i_max = static_cast<int>(input_data.size());
  vector<vector<string> > input_data_div;
  for(int i=0; i<i_max; i++)
  {
    vector<string> str_vec = str_obj.divide_string_data_by_space_code(input_data[i]);
    input_data[i].clear();

    if( static_cast<int>(str_vec.size()) > 0 )
    {
      input_data_div.push_back(str_vec);
    }
    str_vec.clear();
  }
  input_data.clear();

  //Read input_data_div
  read_input_data(input_data_div);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void FrendyParallelRunner::read_input_data(vector<vector<string> >& input_data)
{
  cout << endl;
  cout << "=== Read input data ===" << endl;
  cout << endl;

  int i_max = static_cast<int>(input_data.size());
  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(input_data[i].size());
    for(int j=0; j<j_max; j++)
    {
      int read_mode = check_read_mode(input_data[i][j]);
      if( read_mode == thread_no_mode )          read_thread_no(i, j, input_data);
      else if( read_mode == frendy_exe_mode )    read_frendy_exe(i, j, input_data);
      else if( read_mode == restart_mode )       read_restart_opt(i, j, input_data);
      else if( read_mode == temp_data_mode )     read_temp_data(i, j, input_data);
      else if( read_mode == bgxs_data_mode )     read_bgxs_data(i, j, input_data);
      else if( read_mode == frendy_inp_mode )    read_frendy_input_template(i, j, input_data);
      else if( read_mode == nucl_dir_mode )      read_nucl_dir(i, j, input_data);
      else if( read_mode == tsl_dir_mode )       read_tsl_dir(i, j, input_data);
      else if( read_mode == out_dir_mode )       read_out_dir(i, j, input_data);
      else if( read_mode == out_dir_inp_mode )   read_out_dir_inp(i, j, input_data);
      else if( read_mode == out_dir_log_mode )   read_out_dir_log(i, j, input_data);
      else if( read_mode == out_dir_ace_mode )   read_out_dir_ace(i, j, input_data);
      else if( read_mode == out_dir_mg_mode )    read_out_dir_mg(i, j, input_data);
      else if( read_mode == out_dir_gendf_mode ) read_out_dir_gendf(i, j, input_data);
      else if( read_mode == out_dir_matxs_mode ) read_out_dir_matxs(i, j, input_data);
      else if( read_mode == inp_list_mode )      read_inp_list(i, j, input_data);
      else
      {
        string class_name = "FrendyParallelRunner";
        string func_name  = "read_input_data(vector<vector<string> >& input_data)";

        vector<string> err_com;
        string str_data01 = "mode name : " + input_data[i][j];
        err_com.push_back(str_data01);
        err_com.push_back("This mode name is not aveilable for this program.");
        err_com.push_back("Please modify mode name or input file.");
        err_com.push_back("");
        err_com.push_back("The available mode name is as follows:");
        err_com.push_back("  <TEMP>         : Temperature data list");
        err_com.push_back("  <BG_XS>        : Background cross section data list");
        err_com.push_back("  <FRENDY_INPUT> : FRENDY input file template");
        err_com.push_back("  <ENDF_DIR>     : ENDF file directory (neutron induced)");
        err_com.push_back("  <ACE_DIR>      : ACE file directory (neutron inuduced) (option)");
        err_com.push_back("  <TSL_DIR>      : ENDF or ACE file directory (TSL: thermal scattering law data)");
        err_com.push_back("  <OUT_DIR>      : Generated FRENDY input file and log file directories");
        err_com.push_back("  <OUT_DIR_ACE>  : Generated ACE file directory (option)");
        err_com.push_back("  <OUT_DIR_MG>   : Generated multi-group cross section file directory (option)");
        err_com.push_back("  <FRENDY_EXE>   : FRENDY executable file name (option)");
        err_com.push_back("  <RESTART>      : Restart option (option)");
        err_com.push_back("  <THREAD_NO>    : Number of parallels (option)");
        err_com.push_back("  <INP_LIST>     : Input data list");
        err_com.push_back("");

        err_obj.output_runtime_error(class_name, func_name, err_com);
      }

      if( i >= i_max )
      {
        break;
      }

      j_max = static_cast<int>(input_data[i].size());
      if( j >= j_max )
      {
        break;
      }
    }

    if( i >= i_max )
    {
      break;
    }
  }
  cout << endl;
  cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int FrendyParallelRunner::check_read_mode(string mode_name)
{
  transform(mode_name.begin(), mode_name.end(), mode_name.begin(), ::tolower);
  replace(mode_name.begin(), mode_name.end(), '-', '_');

  if( mode_name == "<thread>"   || mode_name == "<threadno>"   || mode_name == "<thread_no>"
   || mode_name == "<parallel>" || mode_name == "<parallelno>" || mode_name == "<parallel_no>" )
  {
    return thread_no_mode;
  }
  else if( mode_name == "<frendy>" || mode_name == "<exe>" || mode_name == "<module>"
        || mode_name == "<frendyexe>"      || mode_name == "<frendy_exe>" 
        || mode_name == "<frendymodule>"   || mode_name == "<frendy_module>" )
  {
    return frendy_exe_mode;
  }
  else if( mode_name == "<restart>" || mode_name == "<continue>"
        || mode_name == "<restartmode>"     || mode_name == "<restart_mode>" 
        || mode_name == "<restartopt>"     || mode_name == "<restart_opt>" 
        || mode_name == "<restartoption>"  || mode_name == "<restart_option>" 
        || mode_name == "<continuemode>"   || mode_name == "<continue_mode>" 
        || mode_name == "<continueopt>"    || mode_name == "<continue_opt>"
        || mode_name == "<continueoption>" || mode_name == "<continue_option>" )
  {
    return restart_mode;
  }
  else if( mode_name == "<temp>" || mode_name == "<temperature>"
        || mode_name == "<tempset>"   || mode_name == "<tempdata>"  || mode_name == "<tempdataset>" 
        || mode_name == "<temp_set>"  || mode_name == "<temp_data>" || mode_name == "<temp_data_set>"
        || mode_name == "<temperatureset>"  || mode_name == "<temperaturedata>"
        || mode_name == "<temperaturedataset>"
        || mode_name == "<temperature_set>"  || mode_name == "<tempderature_data>"
        || mode_name == "<temperature_data_set>" )
  {
    return temp_data_mode;
  }
  else if( mode_name == "<bg>" || mode_name == "<bgxs>" || mode_name == "<bg_xs>"
       ||  mode_name == "<bgset>"  || mode_name == "<bgdata>"  || mode_name == "<bgdataset>"
       ||  mode_name == "<bg_set>" || mode_name == "<bg_data>" || mode_name == "<bg_data_set>"
       ||  mode_name == "<bgxsset>"  || mode_name == "<bgxsdata>"  || mode_name == "<bgxsdataset>"
       ||  mode_name == "<bgxs_set>" || mode_name == "<bgxs_data>" || mode_name == "<bgxs_data_set>"
       ||  mode_name == "<bg_xs_set>" || mode_name == "<bg_xs_data>"
       ||  mode_name == "<bg_xs_data_set>" 
       ||  mode_name == "<sigmazero>" || mode_name == "<sigmazerodata>" || mode_name == "<sigmazerodataset>"
       ||  mode_name == "<sigma_zero>" || mode_name == "<sigma_zero_data>"
       || mode_name == "<sigma_zero_data_set>" )
  {
    return bgxs_data_mode;
  }
  else if( mode_name == "<frendyinput>"  || mode_name == "<frendyinputtemplate>"
        || mode_name == "<frendy_input>" || mode_name == "<frendy_input_template>" )
  {
    return frendy_inp_mode;
  }
  else if( mode_name == "<endfdir>" || mode_name == "<endffiledir>"
        || mode_name == "<endf_dir>" || mode_name == "<endf_file_dir>"
        || mode_name == "<acedir>" || mode_name == "<acefiledir>"
        || mode_name == "<ace_dir>" || mode_name == "<ace_file_dir>" )
  {
    return nucl_dir_mode;
  }
  else if( mode_name == "<tsldir>" || mode_name == "<tslfiledir>"
        || mode_name == "<tsl_dir>" || mode_name == "<tsl_file_dir>" )
  {
    return tsl_dir_mode;
  }
  else if( mode_name == "<out>"     || mode_name == "<output>" 
        || mode_name == "<outdir>"  || mode_name == "<outdirectory>" 
        || mode_name == "<out_dir>" || mode_name == "<out_directory>"
        || mode_name == "<outputdir>"  || mode_name == "<outputdirectory>" 
        || mode_name == "<output_dir>" || mode_name == "<output_directory>" )
  {
    return out_dir_mode;
  }
  else if( mode_name == "<outinp>"     || mode_name == "<outputinp>" 
        || mode_name == "<out_inp>"    || mode_name == "<output_inp>" 
        || mode_name == "<outdirinp>"  || mode_name == "<outdirectoryinp>" 
        || mode_name == "<out_dir_inp>" || mode_name == "<out_directory_inp>"
        || mode_name == "<outputdirinp>"  || mode_name == "<outputdirectoryinp>" 
        || mode_name == "<output_dir_inp>" || mode_name == "<output_directory_inp>"
        || mode_name == "<outinpdir>"  || mode_name == "<outinpdirectory>" 
        || mode_name == "<out_inp_dir>" || mode_name == "<out_inp_directory>"
        || mode_name == "<outputinpdir>"  || mode_name == "<outputinpdirectory>" 
        || mode_name == "<output_inp_dir>" || mode_name == "<output_inp_directory>" )
  {
    return out_dir_inp_mode;
  }
  else if( mode_name == "<outlog>"     || mode_name == "<outputlog>" 
        || mode_name == "<out_log>"    || mode_name == "<output_log>" 
        || mode_name == "<outdirlog>"  || mode_name == "<outdirectorylog>" 
        || mode_name == "<out_dir_log>" || mode_name == "<out_directory_log>"
        || mode_name == "<outputdirlog>"  || mode_name == "<outputdirectorylog>" 
        || mode_name == "<output_dir_log>" || mode_name == "<output_directory_log>"
        || mode_name == "<outlogdir>"  || mode_name == "<outlogdirectory>" 
        || mode_name == "<out_log_dir>" || mode_name == "<out_log_directory>"
        || mode_name == "<outputlogdir>"  || mode_name == "<outputlogdirectory>" 
        || mode_name == "<output_log_dir>" || mode_name == "<output_log_directory>" )
  {
    return out_dir_log_mode;
  }
  else if( mode_name == "<outace>"     || mode_name == "<outputace>" 
        || mode_name == "<out_ace>"    || mode_name == "<output_ace>" 
        || mode_name == "<outdirace>"  || mode_name == "<outdirectoryace>" 
        || mode_name == "<out_dir_ace>" || mode_name == "<out_directory_ace>"
        || mode_name == "<outputdirace>"  || mode_name == "<outputdirectoryace>" 
        || mode_name == "<output_dir_ace>" || mode_name == "<output_directory_ace>" 
        || mode_name == "<outdir>"  || mode_name == "<outacedirectory>" 
        || mode_name == "<out_ace_dir>" || mode_name == "<out_ace_directory>"
        || mode_name == "<outputacedir>"  || mode_name == "<outputacedirectory>" 
        || mode_name == "<output_ace_dir>" || mode_name == "<output_ace_directory>" )
  {
    return out_dir_ace_mode;
  }
  else if( mode_name == "<outmg>"     || mode_name == "<outputmg>" 
        || mode_name == "<out_mg>"    || mode_name == "<output_mg>" 
        || mode_name == "<outdirmg>"  || mode_name == "<outdirectorymg>" 
        || mode_name == "<out_dir_mg>" || mode_name == "<out_directory_mg>"
        || mode_name == "<outputdirmg>"  || mode_name == "<outputdirectorymg>" 
        || mode_name == "<output_dir_mg>" || mode_name == "<output_directory_mg>"
        || mode_name == "<outmgdir>"  || mode_name == "<outmgdirectory>" 
        || mode_name == "<out_mg_dir>" || mode_name == "<out_mg_directory>"
        || mode_name == "<outputmgdir>"  || mode_name == "<outputmgdirectory>" 
        || mode_name == "<output_mg_dir>" || mode_name == "<output_mg_directory>" )
  {
    return out_dir_mg_mode;
  }
  else if( mode_name == "<outgendf>"     || mode_name == "<outputgendf>" 
        || mode_name == "<out_gendf>"    || mode_name == "<output_gendf>" 
        || mode_name == "<outdirgendf>"  || mode_name == "<outdirectorygendf>" 
        || mode_name == "<out_dir_gendf>" || mode_name == "<out_directory_gendf>"
        || mode_name == "<outputdirgendf>"  || mode_name == "<outputdirectorygendf>" 
        || mode_name == "<output_dir_gendf>" || mode_name == "<output_directory_gendf>" 
        || mode_name == "<outgendfdir>"  || mode_name == "<outgendfdirectorygendf>" 
        || mode_name == "<out_gendf_dir>" || mode_name == "<out_gendf_directory>"
        || mode_name == "<outputgendfdir>"  || mode_name == "<outputgendfdirectory>" 
        || mode_name == "<output_gendf_dir>" || mode_name == "<output_gendf_directory>" )
  {
    //return out_dir_gendf_mode;
    return out_dir_mg_mode;
  }
  else if( mode_name == "<outmatxs>"     || mode_name == "<outputmatxs>" 
        || mode_name == "<out_matxs>"    || mode_name == "<output_matxs>" 
        || mode_name == "<outdirmatxs>"  || mode_name == "<outdirectorymatxs>" 
        || mode_name == "<out_dir_matxs>" || mode_name == "<out_directory_matxs>"
        || mode_name == "<outputdirmatxs>"  || mode_name == "<outputdirectorymatxs>" 
        || mode_name == "<output_dir_matxs>" || mode_name == "<output_directory_matxs>"
        || mode_name == "<outmatxsdir>"  || mode_name == "<outmatxsdirectory>" 
        || mode_name == "<out_matxs_dir>" || mode_name == "<out_matxs_directory>"
        || mode_name == "<outputmatxsdir>"  || mode_name == "<outputmatxsdirectory>" 
        || mode_name == "<output_matxs_dir>" || mode_name == "<output_matxs_directory>" )
  {
    //return out_dir_matxs_mode;
    return out_dir_mg_mode;
  }
  else if( mode_name == "<inp>"   || mode_name == "<inplist>"   || mode_name == "<inp_list>"
        || mode_name == "<input>" || mode_name == "<inputlist>" || mode_name == "<input_list>"
        || mode_name == "<data>"  || mode_name == "<datalist>"  || mode_name == "<data_list>"
        || mode_name == "<inputdata>" || mode_name == "<input_data>"
        || mode_name == "<inputdatalist>" || mode_name == "<input_data_list>" )
  {
    return inp_list_mode;
  }

  return non_related;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void FrendyParallelRunner::read_thread_no(int& i, int& j, vector<vector<string> >& input_data)
{
  int i_sta = i;
  int j_sta = j;

  if( check_read_mode(input_data[i_sta][j_sta]) != thread_no_mode )
  {
    return;
  }

  cout << endl;
  cout << "  Read number of threads" << endl;

  thread_no = -1;

  int j_pre = 0;
  int i_max = static_cast<int>(input_data.size());
  for(i=i_sta; i<i_max; i++)
  {
    int j_max = static_cast<int>(input_data[i].size());
    if( i == i_sta && j_max == 1 )
    {
      j_pre = j_max-1;
      j_sta = -1;
      continue;
    }
    else if( j_max == 0 )
    {
      j_pre = j_max-1;
      j_sta = -1;
      continue;
    }

    if( i!=i_sta && check_read_mode(input_data[i][0]) > 0 )
    {
      i--;
      j = j_pre;
      return;
    }

    if( j_max != j_sta + 2 )
    {
      string class_name = "FrendyParallelRunner";
      string func_name  = "read_thread_no(int& i, int& j, vector<vector<string> >& input_data)";

      vector<string> err_com;
      if( j_max <= j_sta )
      {
        err_com.push_back("Please set number of threads.");
      }
      else if( j_max > j_sta + 2 )
      {
        err_com.push_back("The multiple data is found in this section.");
        err_com.push_back("The number of data must be 1.");
      }
      err_obj.output_runtime_error(class_name, func_name, err_com);      
    }

    cout << "    Number of threads : " << input_data[i][j_sta+1] << endl;
    thread_no = numeric_string_cast<Integer>(input_data[i][j_sta+1]);

    j = j_sta+1;
    return;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void FrendyParallelRunner::read_frendy_exe(int& i, int& j, vector<vector<string> >& input_data)
{
  int i_sta = i;
  int j_sta = j;

  if( check_read_mode(input_data[i_sta][j_sta]) != frendy_exe_mode )
  {
    return;
  }

  cout << endl;
  cout << "  Read FRENDY module name" << endl;

  frendy_exe.clear();

  int j_pre = 0;
  int i_max = static_cast<int>(input_data.size());
  for(i=i_sta; i<i_max; i++)
  {
    int j_max = static_cast<int>(input_data[i].size());
    if( i == i_sta && j_max == 1 )
    {
      j_pre = j_max-1;
      j_sta = -1;
      continue;
    }
    else if( j_max == 0 )
    {
      j_pre = j_max-1;
      j_sta = -1;
      continue;
    }

    if( i!=i_sta && check_read_mode(input_data[i][0]) > 0 )
    {
      i--;
      j = j_pre;
      return;
    }

    if( j_max != j_sta + 2 )
    {
      string class_name = "FrendyParallelRunner";
      string func_name  = "read_frendy_exe(int& i, int& j, vector<vector<string> >& input_data)";

      vector<string> err_com;
      if( j_max <= j_sta )
      {
        err_com.push_back("Please set FRENDY module name.");
      }
      else if( j_max > j_sta + 2 )
      {
        err_com.push_back("The multiple data is found in this section.");
        err_com.push_back("The number of data must be 1.");
      }
      err_obj.output_runtime_error(class_name, func_name, err_com);      
    }

    cout << "    FRENDY module name : " << input_data[i][j_sta+1] << endl;
    frendy_exe = input_data[i][j_sta+1];

    j = j_sta+1;
    return;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void FrendyParallelRunner::read_restart_opt(int& i, int& j, vector<vector<string> >& input_data)
{
  int i_sta = i;
  int j_sta = j;

  if( check_read_mode(input_data[i_sta][j_sta]) != restart_mode )
  {
    return;
  }

  cout << endl;
  cout << "  Read Restart option" << endl;

  restart_opt  = 0; //no restart

  int j_pre = 0;
  int i_max = static_cast<int>(input_data.size());
  for(i=i_sta; i<i_max; i++)
  {
    int j_max = static_cast<int>(input_data[i].size());
    if( i == i_sta && j_max == 1 )
    {
      j_pre = j_max-1;
      j_sta = -1;
      continue;
    }
    else if( j_max == 0 )
    {
      j_pre = j_max-1;
      j_sta = -1;
      continue;
    }

    if( i!=i_sta && check_read_mode(input_data[i][0]) > 0 )
    {
      i--;
      j = j_pre;
      return;
    }

    if( j_max != j_sta + 2 )
    {
      string class_name = "FrendyParallelRunner";
      string func_name  = "read_restart_opt(int& i, int& j, vector<vector<string> >& input_data)";

      vector<string> err_com;
      if( j_max <= j_sta )
      {
        err_com.push_back("Please set restart option.");
      }
      else if( j_max > j_sta + 2 )
      {
        err_com.push_back("The multiple data is found in this section.");
        err_com.push_back("The number of data must be 1.");
      }
      err_obj.output_runtime_error(class_name, func_name, err_com);      
    }

    cout << "    Restart option : " << input_data[i][j_sta+1] << endl;
    string opt_name = input_data[i][j_sta+1];
    transform(opt_name.begin(), opt_name.end(), opt_name.begin(), ::tolower);
    replace(opt_name.begin(), opt_name.end(), '-', '_');

    restart_opt = -1;
    if( opt_name == "default"
     || opt_name == "off" || opt_name == "no" || opt_name == "none"
     || opt_name == "norestart"   || opt_name == "no_restart" )
    {
      restart_opt  = 0; //no restart
      cout << "    Process all nuclear data and FRENDY iput files." << endl;
    }
    else if( opt_name == "yes" || opt_name == "on" || opt_name == "restart" )
    {
      restart_opt  = 1; //restart
      cout << "    If the log file was found, skip this process." << endl;
    }
    else
    {
      string class_name = "FrendyParallelRunner";
      string func_name  = "read_restart_opt(int& i, int& j, vector<vector<string> >& input_data)";

      vector<string> err_com;
      err_com.push_back("This option name is not valid in this program.");
      err_com.push_back("The available option is as follows:");
      err_com.push_back("  on  (skip the process if input file is found)");
      err_com.push_back("  off (process all nuclear data and FRENDY input files)");
      err_com.push_back("");
      err_com.push_back("Please check input file or this program.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    j = j_sta+1;
    return;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void FrendyParallelRunner::read_temp_data(int& i, int& j, vector<vector<string> >& input_data)
{
  int i_sta = i;
  int j_sta = j;

  if( check_read_mode(input_data[i_sta][j_sta]) != temp_data_mode )
  {
    return;
  }

  cout << endl;
  cout << "  Read temperature data" << endl;
  temp_case.clear();
  temp_data.clear();
  vector<vector<string> >().swap(temp_data_vec);

  int j_pre = 0;
  int i_max = static_cast<int>(input_data.size());
  for(i=i_sta; i<i_max; i++)
  {
    int j_max = static_cast<int>(input_data[i].size());
    if( i == i_sta && j_max == 1 )
    {
      j_pre = j_max-1;
      j_sta = -1;
      continue;
    }
    else if( j_max == 0 )
    {
      j_pre = j_max-1;
      j_sta = -1;
      continue;
    }

    if( i!=i_sta && check_read_mode(input_data[i][0]) > 0 )
    {
      i--;
      j = j_pre;
      return;
    }

    if( j_max < j_sta + 3 )
    {
      string class_name = "FrendyParallelRunner";
      string func_name  = "read_temp_data(int& i, int& j, vector<vector<string> >& input_data)";

      vector<string> err_com;
      if( j_max <= j_sta + 1 )
      {
        err_com.push_back("Please set temperature case name.");
      }
      else
      {
        err_com.push_back("Please set temperature data.");
      }
      err_obj.output_runtime_error(class_name, func_name, err_com);      
    }

    temp_case.push_back(input_data[i][j_sta+1]); 

    string temp_inp = "";
    vector<string> temp_inp_vec;
    for(j=j_sta+2; j<j_max; j++)
    {
      temp_inp = temp_inp + " " + input_data[i][j] + " ";
      temp_inp_vec.push_back(input_data[i][j]);
    }
    temp_data.push_back(temp_inp);
    temp_data_vec.push_back(temp_inp_vec);

    int temp_no = static_cast<int>(temp_case.size());
    cout << "    " << temp_no << " : " << temp_case[temp_no-1] << " : " << temp_data[temp_no-1] << endl;

    j_pre = j_max-1;
    j_sta = -1;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void FrendyParallelRunner::read_bgxs_data(int& i, int& j, vector<vector<string> >& input_data)
{
  int i_sta = i;
  int j_sta = j;

  if( check_read_mode(input_data[i_sta][j_sta]) != bgxs_data_mode )
  {
    return;
  }

  cout << endl;
  cout << "  Read bgxs data" << endl;
  bgxs_case.clear();
  bgxs_data.clear();

  int j_pre = 0;
  int i_max = static_cast<int>(input_data.size());
  for(i=i_sta; i<i_max; i++)
  {
    int j_max = static_cast<int>(input_data[i].size());
    if( i == i_sta && j_max == 1 )
    {
      j_pre = j_max-1;
      j_sta = -1;
      continue;
    }
    else if( j_max == 0 )
    {
      j_pre = j_max-1;
      j_sta = -1;
      continue;
    }

    if( i!=i_sta && check_read_mode(input_data[i][0]) > 0 )
    {
      i--;
      j = j_pre;
      return;
    }

    if( j_max < j_sta + 3 )
    {
      string class_name = "FrendyParallelRunner";
      string func_name  = "read_bgxs_data(int& i, int& j, vector<vector<string> >& input_data)";

      vector<string> err_com;
      if( j_max <= j_sta + 1 )
      {
        err_com.push_back("Please set bgxs case name.");
      }
      else
      {
        err_com.push_back("Please set bgxs data.");
      }
      err_obj.output_runtime_error(class_name, func_name, err_com);      
    }

    bgxs_case.push_back(input_data[i][j_sta+1]); 

    string bgxs_inp = "";
    for(j=j_sta+2; j<j_max; j++)
    {
      bgxs_inp = bgxs_inp + " " + input_data[i][j] + " ";
    }
    bgxs_data.push_back(bgxs_inp);

    int bgxs_no = static_cast<int>(bgxs_case.size());
    cout << "    " << bgxs_no << " : " << bgxs_case[bgxs_no-1] << " : " << bgxs_data[bgxs_no-1] << endl;

    j_pre = j_max-1;
    j_sta = -1;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void FrendyParallelRunner::read_frendy_input_template(int& i, int& j, vector<vector<string> >& input_data)
{
  int i_sta = i;
  int j_sta = j;

  if( check_read_mode(input_data[i_sta][j_sta]) != frendy_inp_mode )
  {
    return;
  }

  cout << endl;
  cout << "  Read frendy input template" << endl;
  frendy_inp_case.clear();
  frendy_inp_data.clear();

  int j_pre = 0;
  int i_max = static_cast<int>(input_data.size());
  for(i=i_sta; i<i_max; i++)
  {
    int j_max = static_cast<int>(input_data[i].size());
    if( i == i_sta && j_max == 1 )
    {
      j_pre = j_max-1;
      j_sta = -1;
      continue;
    }
    else if( j_max == 0 )
    {
      j_pre = j_max-1;
      j_sta = -1;
      continue;
    }

    if( i!=i_sta && check_read_mode(input_data[i][0]) > 0 )
    {
      i--;
      j = j_pre;
      return;
    }

    if( j_max != j_sta + 3 )
    {
      string class_name = "FrendyParallelRunner";
      string func_name  = "read_frendy_inp_data(int& i, int& j, vector<vector<string> >& input_data)";

      vector<string> err_com;
      if( j_max <= j_sta + 1 )
      {
        err_com.push_back("Please set frendyi input template case name.");
      }
      else if( j_max > j_sta + 2 )
      {
        err_com.push_back("The number of frendy input template file name must be 1.");
      }
      err_obj.output_runtime_error(class_name, func_name, err_com);      
    }

    frendy_inp_case.push_back(input_data[i][j_sta+1]); 
    frendy_inp_data.push_back(input_data[i][j_sta+2]);

    int frendy_inp_no = static_cast<int>(frendy_inp_case.size());
    cout << "    " << frendy_inp_no << " : " << frendy_inp_case[frendy_inp_no-1]
                                  << " : " << frendy_inp_data[frendy_inp_no-1] << endl;

    j_pre = j_max-1;
    j_sta = -1;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void FrendyParallelRunner::read_nucl_dir(int& i, int& j, vector<vector<string> >& input_data)
{
  int i_sta = i;
  int j_sta = j;

  if( check_read_mode(input_data[i_sta][j_sta]) != nucl_dir_mode )
  {
    return;
  }

  string mode_name = input_data[i_sta][j_sta];
  transform(mode_name.begin(), mode_name.end(), mode_name.begin(), ::tolower);
  if( mode_name.find("ace") == std::string::npos )
  {
    ace_data_flg = 0;
  }
  else
  {
    ace_data_flg = 1;
  }

  cout << endl;
  if( ace_data_flg == 0 )
  {
    cout << "  Read nuclear data directory" << endl;
  }
  else
  {
    cout << "  Read ACE data directory" << endl;
  }

  int nucl_flg = 0;
  int tsl_flg  = 0;

  int i_pre = i_sta;
  int j_pre = j_sta;
  int i_max = static_cast<int>(input_data.size());
  for(i=i_sta; i<i_max; i++)
  {
    int j_max = static_cast<int>(input_data[i].size());
    for(j=j_sta; j<j_max; j++)
    {
      if( i == i_sta && j == j_sta )
      {
        i_pre = i;
        j_pre = j;
        continue;
      }

      if( i!=i_sta && check_read_mode(input_data[i][j]) > 0 )
      {
        i = i_pre;
        j = j_pre;
        return;
      }

      if( nucl_flg == 0 )
      {
        nucl_flg++;
        nucl_dir = input_data[i][j];
        if( ace_data_flg == 0 )
        {
          cout << "    Nuclear data directory : " << nucl_dir << endl;
        }
        else
        {
          cout << "    ACE data directory : " << nucl_dir << endl;
        }
      }
      else if( nucl_flg > 0 && tsl_flg == 0 )
      {
        tsl_flg++;
        cout << "    TSL data directory     : " << input_data[i][j] << endl;
        if( static_cast<int>(tsl_dir.size()) > 0 )
        {
          string class_name = "FrendyParallelRunner";
          string func_name  = "read_nucl_dir(int& i, int& j, vector<vector<string> >& input_data)";

          vector<string> err_com;
          err_com.push_back("The tsl data dirctory is modified from");
          err_com.push_back(tsl_dir);
          err_com.push_back("to");
          err_com.push_back(input_data[i][j]);

          err_obj.output_caution(class_name, func_name, err_com);
        }

        tsl_dir = input_data[i][j];
      }
      else if( nucl_flg > 0 && tsl_flg > 0 )
      {
        string class_name = "FrendyParallelRunner";
        string func_name  = "read_nucl_dir(int& i, int& j, vector<vector<string> >& input_data)";

        vector<string> err_com;
        err_com.push_back("The number of nucler data directory data must be less than or equal to 2.");
        err_com.push_back("The following data is not available in this program.");
        err_com.push_back(input_data[i][j]);
        err_com.push_back("");
        err_com.push_back("Please check the input file.");
        err_obj.output_runtime_error(class_name, func_name, err_com);
      }
      i_pre = i;
      j_pre = j;
    }
    j_sta = 0;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void FrendyParallelRunner::read_tsl_dir(int& i, int& j, vector<vector<string> >& input_data)
{
  int i_sta = i;
  int j_sta = j;

  if( check_read_mode(input_data[i_sta][j_sta]) != tsl_dir_mode )
  {
    return;
  }

  cout << endl;
  cout << "  Read tsl data directory" << endl;

  int tsl_flg  = 0;

  int i_pre = i_sta;
  int j_pre = j_sta;
  int i_max = static_cast<int>(input_data.size());
  for(i=i_sta; i<i_max; i++)
  {
    int j_max = static_cast<int>(input_data[i].size());
    for(j=j_sta; j<j_max; j++)
    {
      if( i == i_sta && j == j_sta )
      {
        i_pre = i;
        j_pre = j;
        continue;
      }

      if( i!=i_sta && check_read_mode(input_data[i][j]) > 0 )
      {
        i = i_pre;
        j = j_pre;
        return;
      }

      if( tsl_flg == 0 )
      {
        tsl_flg++;
        tsl_dir = input_data[i][j];
        cout << "    TSL data directory  : " << input_data[i][j] << endl;

        if( static_cast<int>(tsl_dir.size()) > 0 )
        {
          string class_name = "FrendyParallelRunner";
          string func_name  = "read_tsl_dir(int& i, int& j, vector<vector<string> >& input_data)";

          vector<string> err_com;
          err_com.push_back("The tsl data dirctory is modified from");
          err_com.push_back(tsl_dir);
          err_com.push_back("to");
          err_com.push_back(input_data[i][j]);

          err_obj.output_caution(class_name, func_name, err_com);
        }
        tsl_dir = input_data[i][j];
      }
      else if( tsl_flg > 0 )
      {
        string class_name = "FrendyParallelRunner";
        string func_name  = "read_tsl_dir(int& i, int& j, vector<vector<string> >& input_data)";

        vector<string> err_com;
        err_com.push_back("The number of nucler data directory data must be equal to 1.");
        err_com.push_back("The following data is not available in this program.");
        err_com.push_back(input_data[i][j]);
        err_com.push_back("");
        err_com.push_back("Please check the input file.");
        err_obj.output_runtime_error(class_name, func_name, err_com);
      }
      i_pre = i;
      j_pre = j;
    }
    j_sta = 0;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void FrendyParallelRunner::read_out_dir(int& i, int& j, vector<vector<string> >& input_data)
{
  int i_sta = i;
  int j_sta = j;

  if( check_read_mode(input_data[i_sta][j_sta]) != out_dir_mode )
  {
    return;
  }

  cout << endl;
  cout << "  Read output data directory" << endl;

  int out_inp_flg   = 0;
  int out_log_flg   = 0;
  int out_mg_flg    = 0;
  int out_gendf_flg = 0;
  int out_matxs_flg = 0;

  int i_pre = i_sta;
  int j_pre = j_sta;
  int i_max = static_cast<int>(input_data.size());
  for(i=i_sta; i<i_max; i++)
  {
    int j_max = static_cast<int>(input_data[i].size());
    for(j=j_sta; j<j_max; j++)
    {
      if( i == i_sta && j == j_sta )
      {
        i_pre = i;
        j_pre = j;
        continue;
      }

      if( i!=i_sta && check_read_mode(input_data[i][j]) > 0 )
      {
        i = i_pre;
        j = j_pre;
        return;
      }

      if( out_inp_flg == 0 )
      {
        out_inp_flg++;
        cout << "    FRENDY input data directory : " << input_data[i][j] << endl;
        if( static_cast<int>(out_dir_inp.size()) > 0 )
        {
          string class_name = "FrendyParallelRunner";
          string func_name  = "read_out_dir(int& i, int& j, vector<vector<string> >& input_data)";

          vector<string> err_com;
          err_com.push_back("The FRENDY input data dirctory is modified from");
          err_com.push_back(out_dir_inp);
          err_com.push_back("to");
          err_com.push_back(input_data[i][j]);

          err_obj.output_caution(class_name, func_name, err_com);
        }
        out_dir_inp = input_data[i][j];
      }
      else if( out_log_flg == 0 )
      {
        out_log_flg++;
        cout << "    FRENDY log data directory   : " << input_data[i][j] << endl;
        if( static_cast<int>(out_dir_log.size()) > 0 )
        {
          string class_name = "FrendyParallelRunner";
          string func_name  = "read_out_dir(int& i, int& j, vector<vector<string> >& input_data)";

          vector<string> err_com;
          err_com.push_back("The FRENDY log data dirctory is modified from");
          err_com.push_back(out_dir_log);
          err_com.push_back("to");
          err_com.push_back(input_data[i][j]);

          err_obj.output_caution(class_name, func_name, err_com);
        }
        out_dir_log = input_data[i][j];
      }
      else if( out_mg_flg == 0 )
      {
        out_mg_flg++;
        cout << "    Muti-group cross section data directory        : " << input_data[i][j] << endl;
        if( static_cast<int>(out_dir_mg.size()) > 0 )
        {
          string class_name = "FrendyParallelRunner";
          string func_name  = "read_out_dir(int& i, int& j, vector<vector<string> >& input_data)";

          vector<string> err_com;
          err_com.push_back("Muti-group cross section data dirctory is modified from");
          err_com.push_back(out_dir_mg);
          err_com.push_back("to");
          err_com.push_back(input_data[i][j]);

          err_obj.output_caution(class_name, func_name, err_com);
        }
        out_dir_gendf = input_data[i][j];
      }
      else if( out_gendf_flg == 0 )
      {
        out_gendf_flg++;
        cout << "    GENDF data directory        : " << input_data[i][j] << endl;
        if( static_cast<int>(out_dir_gendf.size()) > 0 )
        {
          string class_name = "FrendyParallelRunner";
          string func_name  = "read_out_dir(int& i, int& j, vector<vector<string> >& input_data)";

          vector<string> err_com;
          err_com.push_back("The GENDF data dirctory is modified from");
          err_com.push_back(out_dir_gendf);
          err_com.push_back("to");
          err_com.push_back(input_data[i][j]);

          err_obj.output_caution(class_name, func_name, err_com);
        }
        out_dir_gendf = input_data[i][j];
      }
      else if( out_matxs_flg == 0 )
      {
        out_matxs_flg++;
        cout << "    MATXS data directory        : " << input_data[i][j] << endl;
        if( static_cast<int>(out_dir_matxs.size()) > 0 )
        {
          string class_name = "FrendyParallelRunner";
          string func_name  = "read_out_dir(int& i, int& j, vector<vector<string> >& input_data)";

          vector<string> err_com;
          err_com.push_back("The MATXS data dirctory is modified from");
          err_com.push_back(out_dir_matxs);
          err_com.push_back("to");
          err_com.push_back(input_data[i][j]);

          err_obj.output_caution(class_name, func_name, err_com);
        }
        out_dir_matxs = input_data[i][j];
      }
      else
      {
        string class_name = "FrendyParallelRunner";
        string func_name  = "read_out_dir(int& i, int& j, vector<vector<string> >& input_data)";

        vector<string> err_com;
        err_com.push_back("The number of output data directory data must be less than or equal to 4.");
        err_com.push_back("The following data is not available in this program.");
        err_com.push_back(input_data[i][j]);
        err_com.push_back("");
        err_com.push_back("Please check the input file.");
        err_obj.output_runtime_error(class_name, func_name, err_com);
      }
      i_pre = i;
      j_pre = j;
    }
    j_sta = 0;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void FrendyParallelRunner::read_out_dir_inp(int& i, int& j, vector<vector<string> >& input_data)
{
  int i_sta = i;
  int j_sta = j;

  if( check_read_mode(input_data[i_sta][j_sta]) != out_dir_inp_mode )
  {
    return;
  }

  cout << endl;
  cout << "  Read FRENDY input data directory" << endl;

  int inp_flg  = 0;

  int i_pre = i_sta;
  int j_pre = j_sta;
  int i_max = static_cast<int>(input_data.size());
  for(i=i_sta; i<i_max; i++)
  {
    int j_max = static_cast<int>(input_data[i].size());
    for(j=j_sta; j<j_max; j++)
    {
      if( i == i_sta && j == j_sta )
      {
        i_pre = i;
        j_pre = j;
        continue;
      }

      if( i!=i_sta && check_read_mode(input_data[i][j]) > 0 )
      {
        i = i_pre;
        j = j_pre;
        return;
      }

      if( inp_flg == 0 )
      {
        inp_flg++;
        out_dir_inp = input_data[i][j];
        cout << "    FRENDY input data directory  : " << input_data[i][j] << endl;

        if( static_cast<int>(out_dir_inp.size()) > 0 )
        {
          string class_name = "FrendyParallelRunner";
          string func_name  = "read_out_dir_inp(int& i, int& j, vector<vector<string> >& input_data)";

          vector<string> err_com;
          err_com.push_back("The FRENDY input data dirctory is modified from");
          err_com.push_back(out_dir_inp);
          err_com.push_back("to");
          err_com.push_back(input_data[i][j]);

          err_obj.output_caution(class_name, func_name, err_com);
        }
        out_dir_inp = input_data[i][j];
      }
      else if( inp_flg > 0 )
      {
        string class_name = "FrendyParallelRunner";
        string func_name  = "read_out_dir_inp(int& i, int& j, vector<vector<string> >& input_data)";

        vector<string> err_com;
        err_com.push_back("The number of FRENDY input directory data must be equal to 1.");
        err_com.push_back("The following data is not available in this program.");
        err_com.push_back(input_data[i][j]);
        err_com.push_back("");
        err_com.push_back("Please check the input file.");
        err_obj.output_runtime_error(class_name, func_name, err_com);
      }
      i_pre = i;
      j_pre = j;
    }
    j_sta = 0;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void FrendyParallelRunner::read_out_dir_log(int& i, int& j, vector<vector<string> >& input_data)
{
  int i_sta = i;
  int j_sta = j;

  if( check_read_mode(input_data[i_sta][j_sta]) != out_dir_log_mode )
  {
    return;
  }

  cout << endl;
  cout << "  Read FRENDY log data directory" << endl;

  int log_flg  = 0;

  int i_pre = i_sta;
  int j_pre = j_sta;
  int i_max = static_cast<int>(input_data.size());
  for(i=i_sta; i<i_max; i++)
  {
    int j_max = static_cast<int>(input_data[i].size());
    for(j=j_sta; j<j_max; j++)
    {
      if( i == i_sta && j == j_sta )
      {
        i_pre = i;
        j_pre = j;
        continue;
      }

      if( i!=i_sta && check_read_mode(input_data[i][j]) > 0 )
      {
        i = i_pre;
        j = j_pre;
        return;
      }

      if( log_flg == 0 )
      {
        log_flg++;
        out_dir_log = input_data[i][j];
        cout << "    FRENDY log data directory  : " << input_data[i][j] << endl;

        if( static_cast<int>(out_dir_log.size()) > 0 )
        {
          string class_name = "FrendyParallelRunner";
          string func_name  = "read_out_dir_log(int& i, int& j, vector<vector<string> >& input_data)";

          vector<string> err_com;
          err_com.push_back("The FRENDY log data dirctory is modified from");
          err_com.push_back(out_dir_log);
          err_com.push_back("to");
          err_com.push_back(input_data[i][j]);

          err_obj.output_caution(class_name, func_name, err_com);
        }
        out_dir_log = input_data[i][j];
      }
      else if( log_flg > 0 )
      {
        string class_name = "FrendyParallelRunner";
        string func_name  = "read_out_dir_log(int& i, int& j, vector<vector<string> >& input_data)";

        vector<string> err_com;
        err_com.push_back("The number of FRENDY log directory data must be equal to 1.");
        err_com.push_back("The following data is not available in this program.");
        err_com.push_back(input_data[i][j]);
        err_com.push_back("");
        err_com.push_back("Please check the input file.");
        err_obj.output_runtime_error(class_name, func_name, err_com);
      }
      i_pre = i;
      j_pre = j;
    }
    j_sta = 0;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void FrendyParallelRunner::read_out_dir_ace(int& i, int& j, vector<vector<string> >& input_data)
{
  int i_sta = i;
  int j_sta = j;

  if( check_read_mode(input_data[i_sta][j_sta]) != out_dir_ace_mode )
  {
    return;
  }

  cout << endl;
  cout << "  Read output ACE data directory" << endl;

  int ace_flg  = 0;

  int i_pre = i_sta;
  int j_pre = j_sta;
  int i_max = static_cast<int>(input_data.size());
  for(i=i_sta; i<i_max; i++)
  {
    int j_max = static_cast<int>(input_data[i].size());
    for(j=j_sta; j<j_max; j++)
    {
      if( i == i_sta && j == j_sta )
      {
        i_pre = i;
        j_pre = j;
        continue;
      }

      if( i!=i_sta && check_read_mode(input_data[i][j]) > 0 )
      {
        i = i_pre;
        j = j_pre;
        return;
      }

      if( ace_flg == 0 )
      {
        ace_flg++;
        if( static_cast<int>(out_dir_ace.size()) > 0 )
        {
          string class_name = "FrendyParallelRunner";
          string func_name  = "read_out_dir_ace(int& i, int& j, vector<vector<string> >& input_data)";

          vector<string> err_com;
          err_com.push_back("The output ACE data dirctory is modified from");
          err_com.push_back(out_dir_ace);
          err_com.push_back("to");
          err_com.push_back(input_data[i][j]);

          err_obj.output_caution(class_name, func_name, err_com);
        }
        out_dir_ace = input_data[i][j];
        cout << "    output ACE data directory  : " << input_data[i][j] << endl;
      }
      else if( ace_flg > 0 )
      {
        string class_name = "FrendyParallelRunner";
        string func_name  = "read_out_dir_ace(int& i, int& j, vector<vector<string> >& input_data)";

        vector<string> err_com;
        err_com.push_back("The number of output ACE directory data must be equal to 1.");
        err_com.push_back("The following data is not available in this program.");
        err_com.push_back(input_data[i][j]);
        err_com.push_back("");
        err_com.push_back("Please check the input file.");
        err_obj.output_runtime_error(class_name, func_name, err_com);
      }
      i_pre = i;
      j_pre = j;
    }
    j_sta = 0;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void FrendyParallelRunner::read_out_dir_mg(int& i, int& j, vector<vector<string> >& input_data)
{
  int i_sta = i;
  int j_sta = j;

  if( check_read_mode(input_data[i_sta][j_sta]) != out_dir_mg_mode )
  {
    return;
  }

  cout << endl;
  cout << "  Read GENDF data directory" << endl;

  int mg_flg  = 0;

  int i_pre = i_sta;
  int j_pre = j_sta;
  int i_max = static_cast<int>(input_data.size());
  for(i=i_sta; i<i_max; i++)
  {
    int j_max = static_cast<int>(input_data[i].size());
    for(j=j_sta; j<j_max; j++)
    {
      if( i == i_sta && j == j_sta )
      {
        i_pre = i;
        j_pre = j;
        continue;
      }

      if( i!=i_sta && check_read_mode(input_data[i][j]) > 0 )
      {
        i = i_pre;
        j = j_pre;
        return;
      }

      if( mg_flg == 0 )
      {
        mg_flg++;
        out_dir_mg = input_data[i][j];
        cout << "    Multi-group cross section file directory  : " << input_data[i][j] << endl;

        if( static_cast<int>(out_dir_mg.size()) > 0 )
        {
          string class_name = "FrendyParallelRunner";
          string func_name  = "read_out_dir_mg(int& i, int& j, vector<vector<string> >& input_data)";

          vector<string> err_com;
          err_com.push_back("The multi-group cross section file dirctory is modified from");
          err_com.push_back(out_dir_mg);
          err_com.push_back("to");
          err_com.push_back(input_data[i][j]);

          err_obj.output_caution(class_name, func_name, err_com);
        }
        out_dir_mg = input_data[i][j];
      }
      else if( mg_flg > 0 )
      {
        string class_name = "FrendyParallelRunner";
        string func_name  = "read_out_dir_mg(int& i, int& j, vector<vector<string> >& input_data)";

        vector<string> err_com;
        err_com.push_back("The number of multi-group cross section file directory data must be equal to 1.");
        err_com.push_back("The following data is not available in this program.");
        err_com.push_back(input_data[i][j]);
        err_com.push_back("");
        err_com.push_back("Please check the input file.");
        err_obj.output_runtime_error(class_name, func_name, err_com);
      }
      i_pre = i;
      j_pre = j;
    }
    j_sta = 0;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void FrendyParallelRunner::read_out_dir_gendf(int& i, int& j, vector<vector<string> >& input_data)
{
  int i_sta = i;
  int j_sta = j;

  if( check_read_mode(input_data[i_sta][j_sta]) != out_dir_gendf_mode )
  {
    return;
  }

  cout << endl;
  cout << "  Read GENDF data directory" << endl;

  int gendf_flg  = 0;

  int i_pre = i_sta;
  int j_pre = j_sta;
  int i_max = static_cast<int>(input_data.size());
  for(i=i_sta; i<i_max; i++)
  {
    int j_max = static_cast<int>(input_data[i].size());
    for(j=j_sta; j<j_max; j++)
    {
      if( i == i_sta && j == j_sta )
      {
        i_pre = i;
        j_pre = j;
        continue;
      }

      if( i!=i_sta && check_read_mode(input_data[i][j]) > 0 )
      {
        i = i_pre;
        j = j_pre;
        return;
      }

      if( gendf_flg == 0 )
      {
        gendf_flg++;
        out_dir_gendf = input_data[i][j];
        cout << "    GENDF data directory  : " << input_data[i][j] << endl;

        if( static_cast<int>(out_dir_gendf.size()) > 0 )
        {
          string class_name = "FrendyParallelRunner";
          string func_name  = "read_out_dir_gendf(int& i, int& j, vector<vector<string> >& input_data)";

          vector<string> err_com;
          err_com.push_back("The GENDF data dirctory is modified from");
          err_com.push_back(out_dir_gendf);
          err_com.push_back("to");
          err_com.push_back(input_data[i][j]);

          err_obj.output_caution(class_name, func_name, err_com);
        }
        out_dir_gendf = input_data[i][j];
      }
      else if( gendf_flg > 0 )
      {
        string class_name = "FrendyParallelRunner";
        string func_name  = "read_out_dir_gendf(int& i, int& j, vector<vector<string> >& input_data)";

        vector<string> err_com;
        err_com.push_back("The number of GENDF directory data must be equal to 1.");
        err_com.push_back("The following data is not available in this program.");
        err_com.push_back(input_data[i][j]);
        err_com.push_back("");
        err_com.push_back("Please check the input file.");
        err_obj.output_runtime_error(class_name, func_name, err_com);
      }
      i_pre = i;
      j_pre = j;
    }
    j_sta = 0;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void FrendyParallelRunner::read_out_dir_matxs(int& i, int& j, vector<vector<string> >& input_data)
{
  int i_sta = i;
  int j_sta = j;

  if( check_read_mode(input_data[i_sta][j_sta]) != out_dir_matxs_mode )
  {
    return;
  }

  cout << endl;
  cout << "  Read MATXS data directory" << endl;

  int matxs_flg  = 0;

  int i_pre = i_sta;
  int j_pre = j_sta;
  int i_max = static_cast<int>(input_data.size());
  for(i=i_sta; i<i_max; i++)
  {
    int j_max = static_cast<int>(input_data[i].size());
    for(j=j_sta; j<j_max; j++)
    {
      if( i == i_sta && j == j_sta )
      {
        i_pre = i;
        j_pre = j;
        continue;
      }

      if( i!=i_sta && check_read_mode(input_data[i][j]) > 0 )
      {
        i = i_pre;
        j = j_pre;
        return;
      }

      if( matxs_flg == 0 )
      {
        matxs_flg++;
        out_dir_matxs = input_data[i][j];
        cout << "    MATXS data directory  : " << input_data[i][j] << endl;

        if( static_cast<int>(out_dir_matxs.size()) > 0 )
        {
          string class_name = "FrendyParallelRunner";
          string func_name  = "read_out_dir_matxs(int& i, int& j, vector<vector<string> >& input_data)";

          vector<string> err_com;
          err_com.push_back("The MATXS data dirctory is modified from");
          err_com.push_back(out_dir_matxs);
          err_com.push_back("to");
          err_com.push_back(input_data[i][j]);

          err_obj.output_caution(class_name, func_name, err_com);
        }
        out_dir_matxs = input_data[i][j];
      }
      else if( matxs_flg > 0 )
      {
        string class_name = "FrendyParallelRunner";
        string func_name  = "read_out_dir_matxs(int& i, int& j, vector<vector<string> >& input_data)";

        vector<string> err_com;
        err_com.push_back("The number of MATXS directory data must be equal to 1.");
        err_com.push_back("The following data is not available in this program.");
        err_com.push_back(input_data[i][j]);
        err_com.push_back("");
        err_com.push_back("Please check the input file.");
        err_obj.output_runtime_error(class_name, func_name, err_com);
      }
      i_pre = i;
      j_pre = j;
    }
    j_sta = 0;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void FrendyParallelRunner::read_inp_list(int& i, int& j, vector<vector<string> >& input_data)
{
  int i_sta = i;
  int j_sta = j;

  if( check_read_mode(input_data[i_sta][j_sta]) != inp_list_mode )
  {
    return;
  }

  cout << endl;
  cout << "  Read input data list" << endl;
  vector<vector<string> >().swap(inp_list);

  int i_pre = i_sta;
  int j_pre = 0;
  int i_max = static_cast<int>(input_data.size());
  for(i=i_sta; i<i_max; i++)
  {
    int j_max = static_cast<int>(input_data[i].size());
    if( i == i_sta && j_max == 1 )
    {
      i_pre = i;
      j_pre = j_max-1;
      j_sta = -1;
      continue;
    }
    else if( j_max == 0 )
    {
      i_pre = i;
      j_pre = j_max-1;
      j_sta = -1;
      continue;
    }

    if( i!=i_sta && check_read_mode(input_data[i][0]) > 0 )
    {
      i = i_pre;
      j = j_pre;
      return;
    }

    string         str_data_inp = "";
    vector<string> inp_list_each;
    for(j=j_sta+1; j<j_max; j++)
    {
      str_data_inp = str_data_inp + " " + input_data[i][j] + " ";
      inp_list_each.push_back(input_data[i][j]);
    }
    inp_list.push_back(inp_list_each);
    inp_list_each.clear();

    int inp_no = static_cast<int>(inp_list.size());
    cout << "    " << inp_no << " :" << str_data_inp << endl;
    str_data_inp.clear();

    i_pre = i;
    j_pre = j_max-1;
    j_sta = -1;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void FrendyParallelRunner::check_inp_data()
{
  int i_max = static_cast<int>(inp_list.size());
  for(int i=0; i<i_max; i++)
  {
    int j_max   = static_cast<int>(inp_list[i].size());
    if( j_max == 0 )
    {
      string class_name = "FrendyParallelRunner";
      string func_name  = "check_inp_data()";

      ostringstream oss01, oss02;
      oss01 << i+1;
      oss02 << i_max;
      string str_data = "i = " + oss01.str() + " / " + oss02.str();

      vector<string> err_com;
      err_com.push_back(str_data);
      err_com.push_back("The number of inp_list[i] is zero.");
      err_com.push_back("Please check the program.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }

  if( static_cast<int>(temp_case.size()) == 0 ||
      static_cast<int>(bgxs_case.size()) == 0 ||
      static_cast<int>(frendy_inp_case.size()) == 0 )
  {
    string class_name = "FrendyParallelRunner";
    string func_name  = "check_inp_data()";

    ostringstream oss01, oss02, oss03;
    oss01 << static_cast<int>(temp_case.size());
    oss02 << static_cast<int>(bgxs_case.size());
    oss03 << static_cast<int>(frendy_inp_case.size());

    string str_data01 = "Number of temperature data cases  : " + oss01.str();
    string str_data02 = "Number of background data cases   : " + oss02.str();
    string str_data03 = "Number of FRENDY input data cases : " + oss03.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("");
    err_com.push_back("The above data must be larger than equal to 1.");
    err_com.push_back("Please check the input data or program.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void FrendyParallelRunner::set_initial_data_list()
{
  for(int i=0; i<static_cast<int>(temp_case.size()); i++)
  {
    transform(temp_case[i].begin(), temp_case[i].end(), temp_case[i].begin(), ::tolower);
  }

  for(int i=0; i<static_cast<int>(bgxs_case.size()); i++)
  {
    transform(bgxs_case[i].begin(), bgxs_case[i].end(), bgxs_case[i].begin(), ::tolower);
  }

  for(int i=0; i<static_cast<int>(frendy_inp_case.size()); i++)
  {
    transform(frendy_inp_case[i].begin(), frendy_inp_case[i].end(), frendy_inp_case[i].begin(), ::tolower);
  }

  out_dir_inp   = str_obj.remove_suffix(out_dir_inp, separation_record);
  nucl_dir      = str_obj.remove_suffix(nucl_dir, separation_record);
  tsl_dir       = str_obj.remove_suffix(tsl_dir, separation_record);
  out_dir_inp   = str_obj.remove_suffix(out_dir_inp, separation_record);
  out_dir_log   = str_obj.remove_suffix(out_dir_log, separation_record);
  out_dir_ace   = str_obj.remove_suffix(out_dir_ace, separation_record);
  out_dir_gendf = str_obj.remove_suffix(out_dir_gendf, separation_record);
  out_dir_matxs = str_obj.remove_suffix(out_dir_matxs, separation_record);

  vector<string>().swap(nucl_list);
  vector<string>().swap(tsl_list);
  vector<string>().swap(inp_base_list);
  vector<string>().swap(temp_list);
  vector<string>().swap(bgxs_list);
  vector<string>().swap(tsl_type_list);
  vector<string>().swap(frendy_inp_list);
  vector<string>().swap(frendy_log_list);
  vector<string>().swap(ace_list);
  vector<string>().swap(ace_list_tsl);
  vector<string>().swap(mg_list);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void FrendyParallelRunner::add_data_list(string nucl_each, string tsl_each, string base_inp_each,
                                         vector<string> temp_each,
                                         string bgxs_each, string tsl_type_each,
                                         string inp_name_each, string log_name_each,
                                         string ace_name_nucl_each, string ace_name_tsl_each,
                                         string mg_name_each)
{
  int i_max = static_cast<int>(temp_each.size());
  for(int i=0; i<i_max; i++)
  {
    string inp_name_temp, log_name_temp, ace_name_temp, ace_name_tsl_temp, mg_name_temp;
    ace_name_temp.clear();
    ace_name_tsl_temp.clear();
    mg_name_temp.clear();

    inp_name_temp = inp_name_each + "_" + temp_each[i] + ".inp";
    log_name_temp = log_name_each + "_" + temp_each[i] + ".log";
    if( static_cast<int>(ace_name_nucl_each.size()) > 0 )
    {
      ace_name_temp = ace_name_nucl_each + "_" + temp_each[i] + ".ace";
    }
    if( static_cast<int>(ace_name_tsl_each.size()) > 0 )
    {
      ace_name_tsl_temp = ace_name_tsl_each + "_" + temp_each[i] + ".ace";
    }
    if( static_cast<int>(mg_name_each.size()) > 0 )
    {
      mg_name_temp  = mg_name_each  + "_" + temp_each[i];
    }

    if( restart_opt == 1 )
    {
      if( check_frendy_log_file(log_name_temp) > 0 )
      {
        skip_inp_list.push_back(inp_name_temp);
        skip_log_list.push_back(log_name_temp);
        continue;
      }
    }

    nucl_list.push_back(nucl_each);
    tsl_list.push_back(tsl_each);
    inp_base_list.push_back(base_inp_each);
    temp_list.push_back(temp_each[i]);
    bgxs_list.push_back(bgxs_each);
    tsl_type_list.push_back(tsl_type_each);

    frendy_inp_list.push_back(inp_name_temp);
    frendy_log_list.push_back(log_name_temp);
    ace_list.push_back(ace_name_temp);
    ace_list_tsl.push_back(ace_name_tsl_temp);
    mg_list.push_back(mg_name_temp);

    int data_no = static_cast<int>(nucl_list.size());
    output_data_list(data_no-1);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void FrendyParallelRunner::output_data_list(int i)
{
  cout << "  Case No. " << i+1 << endl;
  if( ace_data_flg == 0 )
  {
    cout << "    Nuclear file name               : " << nucl_list[i] << endl;
  }
  else
  {
    cout << "    ACE file name (input)           : " << nucl_list[i] << endl;
  }
  if( static_cast<int>(tsl_list[i].size()) > 0 )
  {
    cout << "    TSL file name                   : " << tsl_list[i] << endl;
    cout << "    TSL data type                   : " << tsl_type_list[i] << endl;
  }
  cout << "    FRENDY input template file name : " << inp_base_list[i] << endl;
  cout << "    Tempareture data                : " << temp_list[i] << endl;
  cout << "    Back ground cross section data  : " << bgxs_list[i] << endl;
  cout << "    FRENDY input file name          : " << frendy_inp_list[i] << endl;
  cout << "    FRENDY log file name            : " << frendy_log_list[i] << endl;
  if( static_cast<int>(ace_list_tsl[i].size()) > 0 )
  {
    cout << "    output ACE file name (TSL)      : " << ace_list_tsl[i] << endl;
  }
  else if( static_cast<int>(ace_list[i].size()) > 0 )
  {
    cout << "    output ACE file name            : " << ace_list[i] << endl;
  }
  if( static_cast<int>(mg_list[i].size()) > 0 )
  {
    cout << "    output multi group file name    : " << mg_list[i] << endl;
  }
  cout << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void FrendyParallelRunner::make_data_list()
{
  cout << endl;
  cout << "=== Make input data list ===" << endl;
  cout << endl;


  check_inp_data();
  set_initial_data_list();

  int i_max = static_cast<int>(inp_list.size());
  for(int i=0; i<i_max; i++)
  {
    int tsl_flg = 0;
    int ele_no  = 0;
    int inp_no  = static_cast<int>(inp_list[i].size());

    vector<string> temp_list_each = temp_data_vec[0];
    string bgxs_each          = bgxs_data[0];
    string inp_base_each      = frendy_inp_data[0];
    string tsl_list_each      = "";
    string tsl_type_list_each = "";

    //Set nuclear data file name
    string nucl_list_each = nucl_dir + separation_record + inp_list[i][ele_no];
    string case_name      = str_obj.basename_without_suffix(inp_list[i][ele_no]);
    ele_no++;
    
    string frendy_inp_list_each = case_name;
    if( static_cast<int>(out_dir_inp.size()) > 0 )
    {
      frendy_inp_list_each = out_dir_inp + separation_record + frendy_inp_list_each;
    }

    string frendy_log_list_each = case_name;
    if( static_cast<int>(out_dir_log.size()) > 0 )
    {
      frendy_log_list_each = out_dir_log + separation_record + frendy_log_list_each;
    }

    string ace_list_nucl_each = "";
    string ace_list_tsl_each  = "";
    if( static_cast<int>(out_dir_ace.size()) > 0 )
    {
      ace_list_nucl_each = out_dir_ace + separation_record + case_name;
    }

    string mg_list_each = "";
    if( static_cast<int>(out_dir_gendf.size()) > 0 )
    {
      mg_list_each = out_dir_gendf + separation_record + case_name;
    }

    if( inp_no <= ele_no )
    {
      add_data_list(nucl_list_each, tsl_list_each, inp_base_each,
                    temp_list_each, bgxs_each,     tsl_type_list_each,
                    frendy_inp_list_each, frendy_log_list_each,
                    ace_list_nucl_each, ace_list_tsl_each, mg_list_each);
      continue;
    }

    string tsl_name = inp_list[i][ele_no];
    transform(tsl_name.begin(), tsl_name.end(), tsl_name.begin(), ::tolower);
    for(int j=0; j<static_cast<int>(temp_case.size()); j++)
    {
      if( tsl_name.compare(temp_case[j]) == 0 )
      {
        tsl_flg = -1;
        break;
      }
    }

    if( tsl_flg == 0 )
    {
      //Set TSL data file name
      tsl_list_each = tsl_dir + separation_record + inp_list[i][ele_no];
      ele_no++;

      //Modify input and log file name from nuclear data name to TSL data name
      case_name = str_obj.basename_without_suffix(tsl_list_each);
      frendy_inp_list_each = case_name;
      if( static_cast<int>(out_dir_inp.size()) > 0 )
      {
        frendy_inp_list_each = out_dir_inp + separation_record + frendy_inp_list_each;
      }
      frendy_log_list_each = case_name;
      if( static_cast<int>(out_dir_log.size()) > 0 )
      {
        frendy_log_list_each = out_dir_log + separation_record + frendy_log_list_each;
      }
      if( static_cast<int>(out_dir_ace.size()) > 0 )
      {
        ace_list_tsl_each = out_dir_ace + separation_record + case_name;
      }
      mg_list_each = "";
      if( static_cast<int>(out_dir_gendf.size()) > 0 )
      {
        mg_list_each = out_dir_gendf + separation_record + case_name;
      }


      if( inp_no > ele_no )
      {
        //Set TSL data type
        tsl_type_list_each = inp_list[i][ele_no];
        ele_no++;
      }
      else
      {
        add_data_list(nucl_list_each, tsl_list_each, inp_base_each,
                      temp_list_each, bgxs_each,     tsl_type_list_each,
                      frendy_inp_list_each, frendy_log_list_each,
                      ace_list_nucl_each, ace_list_tsl_each, mg_list_each);
        continue;
      }
    }

    //Set temperature
    if( inp_no > ele_no )
    {
      string temp_name = inp_list[i][ele_no];
      transform(temp_name.begin(), temp_name.end(), temp_name.begin(), ::tolower);
      ele_no++;

      int temp_flg = -1;
      for(int j=0; j<static_cast<int>(temp_case.size()); j++)
      {
        if( temp_name.compare(temp_case[j]) == 0 )
        {
          temp_flg = j;
          break;
        }
      }

      if( temp_flg >= 0 )
      {
        temp_list_each  = temp_data_vec[temp_flg];
      }
      else
      {
        string class_name = "FrendyParallelRunner";
        string func_name  = "make_data_list()";
        string str_data01 = "temperature case name : " + temp_name;
        vector<string> err_com;
        err_com.push_back(str_data01);
        err_com.push_back("");

        string temp_all = "all";
        if( temp_name.compare(temp_all) == 0 )
        {
          if( static_cast<int>(tsl_list_each.size()) > 0 )
          {
            temp_list_each = set_temp_tsl(tsl_list_each);

            err_com.push_back("The temperature data is automatically set using the temperature data in the TSL file.");
            err_com.push_back("The temperature data for TSL processing is as follows:");
            for(int k=0; k<static_cast<int>(temp_list_each.size()); k++)
            {
              string str_data02 = "  " + temp_list_each[k];
              err_com.push_back(str_data02);
            }
            err_obj.output_caution(class_name, func_name, err_com);
          }
          else
          {
            err_com.push_back("This temperature case name is only available for the TSL data processing.");
            err_com.push_back("Please check the input data or program.");
            err_obj.output_runtime_error(class_name, func_name, err_com);
          }
        }
        else
        {
          err_com.push_back("This temperature case name is not found in temp_case.");
          err_com.push_back("Please check the input data or program.");
          err_obj.output_runtime_error(class_name, func_name, err_com);
        }
      }
    }
    else
    {
      add_data_list(nucl_list_each, tsl_list_each, inp_base_each,
                    temp_list_each, bgxs_each,     tsl_type_list_each,
                    frendy_inp_list_each, frendy_log_list_each,
                    ace_list_nucl_each, ace_list_tsl_each, mg_list_each);
      continue;
    }

    //Set background cross section
    if( inp_no > ele_no )
    {
      string bgxs_name = inp_list[i][ele_no];
      transform(bgxs_name.begin(), bgxs_name.end(), bgxs_name.begin(), ::tolower);
      ele_no++;

      int bgxs_flg = -1;
      for(int j=0; j<static_cast<int>(bgxs_case.size()); j++)
      {
        if( bgxs_name.compare(bgxs_case[j]) == 0 )
        {
          bgxs_flg = j;
          break;
        }
      }

      if( bgxs_flg >= 0 )
      {
        bgxs_each = bgxs_data[bgxs_flg];
      }
      else
      {
        string class_name = "FrendyParallelRunner";
        string func_name  = "make_data_list()";

        string str_data01 = "back ground cross section case name : " + bgxs_name;

        vector<string> err_com;
        err_com.push_back(str_data01);
        err_com.push_back("");
        err_com.push_back("This back ground cross section case name is not found in bgxs_case.");
        err_com.push_back("Please check the input data or program.");
        err_obj.output_runtime_error(class_name, func_name, err_com);
      }
    }
    else
    {
      add_data_list(nucl_list_each, tsl_list_each, inp_base_each,
                    temp_list_each, bgxs_each,     tsl_type_list_each,
                    frendy_inp_list_each, frendy_log_list_each,
                    ace_list_nucl_each, ace_list_tsl_each, mg_list_each);
      continue;
    }

    //Set FRENDY input template
    if( inp_no > ele_no )
    {
      string frendy_inp_name = inp_list[i][ele_no];
      transform(frendy_inp_name.begin(), frendy_inp_name.end(), frendy_inp_name.begin(), ::tolower);
      ele_no++;

      int frendy_inp_flg = -1;
      for(int j=0; j<static_cast<int>(frendy_inp_case.size()); j++)
      {
        if( frendy_inp_name.compare(frendy_inp_case[j]) == 0 )
        {
          frendy_inp_flg = j;
          break;
        }
      }

      if( frendy_inp_flg >= 0 )
      {
        inp_base_each = frendy_inp_data[frendy_inp_flg];
      }
      else
      {
        string class_name = "FrendyParallelRunner";
        string func_name  = "make_data_list()";

        string str_data01 = "FRENDY input template case name : " + frendy_inp_name;

        vector<string> err_com;
        err_com.push_back(str_data01);
        err_com.push_back("");
        err_com.push_back("This FRENDY input template case name is not found in frendy_inp_case.");
        err_com.push_back("Please check the input data or program.");
        err_obj.output_runtime_error(class_name, func_name, err_com);
      }
    }
    else
    {
      add_data_list(nucl_list_each, tsl_list_each, inp_base_each,
                    temp_list_each, bgxs_each,     tsl_type_list_each,
                    frendy_inp_list_each, frendy_log_list_each,
                    ace_list_nucl_each, ace_list_tsl_each, mg_list_each);
      continue;
    }

    add_data_list(nucl_list_each, tsl_list_each, inp_base_each,
                  temp_list_each, bgxs_each,     tsl_type_list_each,
                  frendy_inp_list_each, frendy_log_list_each,
                  ace_list_nucl_each, ace_list_tsl_each, mg_list_each);
  }

  cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> FrendyParallelRunner::set_temp_tsl(string tsl_file_name)
{
  Endf6FileStore store_obj;
  NuclearDataObject nucl_data_obj = store_obj.get_nucl_data_obj(tsl_file_name);
  store_obj.clear();

  ThermalScatterDataContainer tsl_obj = nucl_data_obj.get_thermal_scat_data_obj();
  nucl_data_obj.clear();

  vector<Real> temp_sab = tsl_obj.get_inelastic_temp_data_base();
  if( static_cast<int>(temp_sab.size()) > 0 )
  {
    vector<Real> temp_base = tsl_obj.get_inelastic_temp_data_base();
    for(int i=0; i<static_cast<int>(temp_base.size()); i++)
    {
      vector<Real> temp_each = tsl_obj.get_inelastic_temp_data()[i];
      for(int j=0; j<static_cast<int>(temp_each.size()); j++)
      {
        temp_sab.push_back(temp_each[j]);
      }
    }
  }
  else if( static_cast<int>(temp_sab.size()) == 0 )
  {
    temp_sab = tsl_obj.get_elastic_temp_data();
  }
  if( static_cast<int>(temp_sab.size()) == 0 )
  {
    temp_sab = tsl_obj.get_elastic_debye_waller_temp_data();
  }

  TabAdjuster tab_obj;
  tab_obj.delete_overlap_grid(temp_sab);

  DigitAdjuster digit_obj;
  vector<string> str_vec;
  str_vec.clear();
  for(int i=0; i<static_cast<int>(temp_sab.size()); i++)
  {
    int pre_no = 3;

    ostringstream oss;
    oss << setfill('0') << std::right << fixed << setprecision(pre_no) << setw(8) << temp_sab[i];
    string str_data = str_obj.trim_space(oss.str());
    str_vec.push_back(str_data);
  }
  
  return str_vec;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void FrendyParallelRunner::output_skip_list()
{
  int i_max = static_cast<int>(skip_inp_list.size());

  if( i_max == 0 )
  {
    //All process were not completed.
    return;
  }

  int max_len_inp = 0;
  for(int i=0; i<i_max; i++)
  {
    if( static_cast<int>(skip_inp_list[i].length()) > max_len_inp )
    {
      max_len_inp = static_cast<int>(skip_inp_list[i].length());
    }
  }

  cout << endl;
  cout << "=== Output skip (already completed) input file list ===" << endl;
  cout << endl;
  cout << "  The following input file was completed and skip the processing." << endl;
  cout << "  If you want to process these data, please modify <RESTART> option from ON to OFF" << endl;
  cout << "  or remove <RESTART> option." << endl;
  cout << endl;
  cout << "    input file / log file" << endl;

  for(int i=0; i<i_max; i++)
  {
    cout << "      " << setfill(' ') << std::left << setw(max_len_inp) << skip_inp_list[i]
         << " / " << skip_log_list[i] << endl;
  }

  cout << endl;
  cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int FrendyParallelRunner::check_frendy_log_file(string log_file_name)
{
  ifstream fin;
  fin.open(log_file_name);
  if(!fin)
  {
    return -10; //no log file
  }

  while(!fin.eof())
  {
    string line_data;
    getline(fin, line_data);

    if( line_data.find("FRENDY CALCULATION STATUS: NORMAL TERMINATION") != string::npos )
    {
      return 1; //nomal termination
    }
    else if( line_data.find("*  !!! FATAL ERROR !!!  *") != string::npos )
    {
      return -1; //output fatal error by ErrorManager class
    }
  }
  fin.close();

  return -2; //stop by trouble, e.g., error in FRENDY/MG or segmentation fault.
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void FrendyParallelRunner::set_thread_no()
{
#ifdef _OPENMP
  int processor_no = omp_get_num_procs();

  cout << "The number of processors : " << processor_no << endl;
  cout << "The number of threads    : " << thread_no    << endl;
  cout << endl;

  if( processor_no < thread_no || thread_no <= 0 )
  {
    string class_name = "FrendyParallelRunner";
    string func_name  = "set_thread_no()";

    vector<string> err_com;
    if( processor_no < thread_no )
    {
      err_com.push_back("The thread number is larger than the processor number.");
    }
    else //if( thread_no <= 0 )
    {
      err_com.push_back("The thread number is less than or equal to zero.");
    }
    err_com.push_back("The thread number is modified to the processor number.");
    err_obj.output_caution(class_name, func_name, err_com);

    thread_no = processor_no;
  }

  omp_set_num_threads(thread_no);
#endif //_OPENMP
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void FrendyParallelRunner::run_frendy()
{
  cout << endl;
  cout << "=== Running FRENDY ===" << endl;
  cout << endl;

  set_thread_no();

  int i_max        = static_cast<int>(nucl_list.size());
  int digit_i      = digit_obj.get_digit_number(i_max) + 1;
  int max_len_case = 0;
  for(int i=0; i<i_max; i++)
  {
    string case_name = str_obj.basename_without_suffix(frendy_inp_list[i]);
    if( static_cast<int>(case_name.length()) > max_len_case )
    {
      max_len_case = static_cast<int>(case_name.length());
    }
  }

#ifdef _OPENMP
#pragma omp parallel for schedule(dynamic, 1)
#endif //_OPENMP
  for(int i=0; i<i_max; i++)
  {
    if( thread_no > 1 )
    {
      int current_thread_no = omp_get_thread_num() * 30000;
      usleep(current_thread_no);
    }

    string case_name = str_obj.basename_without_suffix(frendy_inp_list[i]);
    cout << "  "  << setfill(' ') << std::left  << setw(max_len_case) << case_name
         << " @ " << setfill(' ') << std::right << setw(digit_i)      << i+1
         << " / " << setfill(' ') << std::right << setw(digit_i)      << i_max;
    if( thread_no == 1 )
    {
      cout << endl;
    }
    else
    {
      cout << " (Thread No." << setfill(' ') << std::right << setw(4) << omp_get_thread_num() + 1 << ")" << endl;
    }

    if( restart_opt == 1 )
    {
      if( check_frendy_log_file(frendy_log_list[i]) > 0 )
      {
        cout << "Skip this process since the normal terminated FRENDY log file was found." << endl;
        continue;
      }
    }

    run_frendy_each_file(i);
  }

  cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void FrendyParallelRunner::make_frendy_inp(int i)
{
  ofstream fout;
  fout.open(frendy_inp_list[i].c_str());
  if( fout.fail() )
  {
    string class_name = "FrendyParallelRunner";
    string func_name  = "make_frendy_inp(int i)";

    string str_data = "  FRENDY input file name : " + frendy_inp_list[i];

    vector<string> err_com;
    err_com.push_back("This FRENDY input file cannot be open.");
    err_com.push_back("Please check the file name, directory name or access authority.");
    err_com.push_back(str_data);

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  ifstream fin;
  fin.open(inp_base_list[i]);
  if(!fin)
  {
    string class_name = "FrendyParallelRunner";
    string func_name  = "make_frendy_inp(int i)";
    vector<string> err_com;
    string str_data = "  FRENDY input template file name : " + inp_base_list[i];
    err_com.push_back(str_data);
    err_com.push_back("This file is not found.");
    err_com.push_back("Please check the file name or directory name.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  while(!fin.eof())
  {
    string line_data;
    getline(fin, line_data);
    fout << line_data << endl;
  }
  fin.close();

  fout << endl;
  fout << "//Following input data are added by FrendyParallelRunner class." << endl;
  fout << endl;

  //Add nucl_list
  if( ace_data_flg == 0 )
  {
    fout << "  nucl_file_name ( " << nucl_list[i] << " )" << endl;

    if( static_cast<int>(tsl_list[i].size()) > 0 )
    {
      fout << "  nucl_file_name_tsl ( " << tsl_list[i] << " )" << endl;
    }
  }
  else
  {
    fout << "  ace_file_name ( " << nucl_list[i] << " )" << endl;

    if( static_cast<int>(tsl_list[i].size()) > 0 )
    {
      fout << "  ace_file_name_tsl ( " << tsl_list[i] << " )" << endl;
    }
  }
  fout << endl;

  //Add temperature
  fout << "  temp (" << temp_list[i] << ")" << endl;

  //Add background xs data
  fout << "  sigma_zero_data (" << bgxs_list[i] << ")" << endl;
  fout << endl;


  if( static_cast<int>(mg_list[i].size()) > 0 ) //For multi-group cross section file generation
  {
    //Add output GENDF file name
    fout << "  mg_file_name ( " << mg_list[i] << " )" << endl;

    //Add TSL data type
    if( static_cast<int>(tsl_type_list[i].size()) > 0 )
    {
      fout << "  mg_tsl_data_type ( " << tsl_type_list[i] << " )" << endl;
    }

    if(  static_cast<int>(ace_list_tsl[i].size()) > 0 && ace_data_flg == 0 )
    {
      //Add output ACE file name (TSL)
      fout << "  ace_file_name ( " << ace_list_tsl[i] << " )" << endl;
    }
    else if( static_cast<int>(ace_list[i].size()) > 0 && ace_data_flg == 0 )
    {
      //Add output ACE file name
      fout << "  ace_file_name ( " << ace_list[i] << " )" << endl;
    }
  }
  else //For ACE file generation
  {
    //Add output ACE file name
    if( static_cast<int>(ace_list[i].size()) > 0 && ace_data_flg == 0 )
    {
      if( static_cast<int>(ace_list_tsl[i].size()) == 0 )
      {
        fout << "  ace_file_name ( " << ace_list[i] << " )" << endl;
      }
      else
      {
        fout << "  ace_file_name ( " << ace_list_tsl[i] << " )" << endl;
      }
    }
  }
  fout << endl;

  //Clos input file
  fout.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void FrendyParallelRunner::run_frendy_each_file(int i)
{
  make_frendy_inp(i);

  ofstream fout;
  fout.open(frendy_log_list[i].c_str());
  if( fout.fail() )
  {
    string class_name = "FrendyParallelRunner";
    string func_name  = "run_frendy_each_file(int i)";

    string str_data = "  FRENDY log file name : " + frendy_log_list[i];

    vector<string> err_com;
    err_com.push_back("This FRENDY log file cannot be open.");
    err_com.push_back("Please check the file name, directory name or access authority.");
    err_com.push_back(str_data);

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
  fout.close();

  int process_check = 1;
  try
  {
    if( static_cast<int>(frendy_exe.size()) == 0 )
    {
      //temporary change cout -> ofstream
      ofstream ofs;
      streambuf* last;
      last = cout.rdbuf();
      ofs.open(frendy_log_list[i], ios_base::out);
      cout.rdbuf(ofs.rdbuf());

      NuclearDataProcessorByFrendyInput frendy_obj;
      frendy_obj.process_nucl_data(frendy_inp_list[i]);

      //ofstream -> cout
      ofs.close();
      cout.rdbuf(last);
    }
    else
    {
      string run_frendy_command = frendy_exe + "   " + frendy_inp_list[i]
                                             + " > " + frendy_log_list[i] + "  2>&1";
      process_check = system(run_frendy_command.c_str());
    }
  }
  catch (const std::runtime_error& e)
  {
    process_check = -1;
  }
  catch (const std::exception& e)
  {
    process_check = -2;
  }

  if( process_check >= 0 )
  {
    if( check_frendy_log_file(frendy_log_list[i]) < 0 )
    {
      process_check = -10;
    }
  }

  if( process_check < 0 )
  {
    cout << "  FRENDY stopped without completing the process: " << frendy_inp_list[i] << endl;
    err_inp_list.push_back(frendy_inp_list[i]);
    err_log_list.push_back(frendy_log_list[i]);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void FrendyParallelRunner::output_error_list()
{
  int i_max = static_cast<int>(err_inp_list.size());

  if( i_max == 0 )
  {
    //All process were completed.
    cout << "Complete all processes wighout runtime error or segmentation fault." << endl;
    cout << endl;
    return;
  }

  int max_len_inp = 0;
  for(int i=0; i<i_max; i++)
  {
    if( static_cast<int>(err_inp_list[i].length()) > max_len_inp )
    {
      max_len_inp = static_cast<int>(err_inp_list[i].length());
    }
  }

  cout << endl;
  cout << "=== Output error (incomplete) input file list ===" << endl;
  cout << endl;
  cout << "  The following input file does not finished all process." << endl;
  cout << "  Please check the log files." << endl;
  cout << endl;
  cout << "    input file / log file" << endl;

  for(int i=0; i<i_max; i++)
  {
    cout << "      " << setfill(' ') << std::left << setw(max_len_inp) << err_inp_list[i]
         << " / " << err_log_list[i] << endl;
  }

  cout << endl;
  cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void FrendyParallelRunner::run_frendy_parallel(string input_name)
{
  clear();
  read_input_file(input_name);

  make_data_list();
  output_skip_list();

  run_frendy();

  output_error_list();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

