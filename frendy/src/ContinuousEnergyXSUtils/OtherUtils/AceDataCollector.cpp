#include "ContinuousEnergyXSUtils/OtherUtils/AceDataCollector.hpp"

using namespace frendy;

//constructor
AceDataCollector::AceDataCollector(void)
{
  clear();

  calc_mode = collect_mode;

  set_awr_nat_list();

  vector<string>().swap(alphabet_list);
  alphabet_list.resize(26);

  alphabet_list[ 0] = "a";
  alphabet_list[ 1] = "b";
  alphabet_list[ 2] = "c";
  alphabet_list[ 3] = "d";
  alphabet_list[ 4] = "e";
  alphabet_list[ 5] = "f";
  alphabet_list[ 6] = "g";
  alphabet_list[ 7] = "h";
  alphabet_list[ 8] = "i";
  alphabet_list[ 9] = "j";
  alphabet_list[10] = "k";
  alphabet_list[11] = "l";
  alphabet_list[12] = "m";
  alphabet_list[13] = "n";
  alphabet_list[14] = "o";
  alphabet_list[15] = "p";
  alphabet_list[16] = "q";
  alphabet_list[17] = "r";
  alphabet_list[18] = "s";
  alphabet_list[19] = "t";
  alphabet_list[20] = "u";
  alphabet_list[21] = "v";
  alphabet_list[22] = "w";
  alphabet_list[23] = "x";
  alphabet_list[24] = "y";
  alphabet_list[25] = "z";
}

//destructor
AceDataCollector::~AceDataCollector(void)
{
  clear();

  vector<string>().swap(alphabet_list);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataCollector::collect_ace_file()
{
  set_data_check();

  search_ace_data_file(ace_dir_name);

  modify_ace_file_list_order();

  ofstream       fout;
  int            line_no_tot = 0;
  int            line_no_pre;
  vector<string> xsdir_vec;
  string         collected_file_name;

  int i_max        = static_cast<int>(ace_file_list.size());
  int ele_no       = 0;
  int alpha_no     = 0;
  int alpha_no_max = static_cast<int>(alphabet_list.size());
  for(int i=0; i<i_max; i++)
  {
    cout << i+1 << " / " << i_max << " : " << ace_file_list[i] << endl;

    vector<string> text_each = copy_ace_file(ace_file_list[i]);
    line_no_pre = line_no_tot;

    int line_no_each = static_cast<int>(text_each.size());
    read_ace_data(text_each);

    if( calc_mode == collect_mode )
    {
      //Output collected ace file
      if( i != 0 && line_no_tot + line_no_each < max_line_no )
      {
        line_no_tot += line_no_each;
        for(int j=0; j<line_no_each; j++)
        {
          fout << text_each[j] << endl;
        }
      }
      else
      {
        line_no_pre = 0;
        line_no_tot = line_no_each;
        write_ace_file(fout, collected_file_name, text_each, ele_no, alpha_no);
        alpha_no++;

        if( alpha_no == alpha_no_max )
        {
          ele_no++;
          alpha_no = 0;
        }
      }
    }
    else //if( calc_mode == individual_mode )
    {
      line_no_pre = 0;
      line_no_tot = line_no_each;
      write_ace_file(fout, collected_file_name, text_each, ele_no, alpha_no);
    }
    //vector<string>().swap(text_each);


    //Output modified ace directory data
    string xsdir_data;
    string dummy_data = "dummy_data";
    if( output_ace_file_mode == fast_ace_mode )
    {
      FastAceDataObject ace_data_obj;
      FastAceDataParser ace_parse_obj;
      FastAceDataWriter ace_wri_obj;

      //Read ace data
      //ace_parse_obj.set_file_name(ace_file_list[i]);
      ace_parse_obj.set_text_data(text_each);
      ace_data_obj = ace_parse_obj.get_ace_data_obj();
      ace_parse_obj.clear();

      //Write directory data
      ace_wri_obj.set_ace_file_name(dummy_data.c_str());
      ace_wri_obj.set_ace_data_obj(ace_data_obj);
      ace_wri_obj.set_previous_line_no(line_no_pre);
      xsdir_data = ace_wri_obj.get_dir_data();
      ace_data_obj.clear();
      ace_wri_obj.clear();
    }
    else if( output_ace_file_mode == thermal_ace_mode )
    {
      ThermalScatterAceDataObject ace_data_obj;
      ThermalScatterAceDataParser ace_parse_obj;
      ThermalScatterAceDataWriter ace_wri_obj;

      //Read ace data
      //ace_parse_obj.set_file_name(ace_file_list[i]);
      ace_parse_obj.set_text_data(text_each);
      ace_data_obj = ace_parse_obj.get_ace_data_obj();
      ace_parse_obj.clear();

      //Write directory data
      ace_wri_obj.set_ace_file_name(dummy_data.c_str());
      ace_wri_obj.set_ace_data_obj(ace_data_obj);
      ace_wri_obj.set_previous_line_no(line_no_pre);
      xsdir_data = ace_wri_obj.get_dir_data();
      ace_data_obj.clear();
      ace_wri_obj.clear();
    }
    else if( output_ace_file_mode == dosimetry_ace_mode )
    {
      DosimetryAceDataObject ace_data_obj;
      DosimetryAceDataParser ace_parse_obj;
      DosimetryAceDataWriter ace_wri_obj;

      //Read ace data
      //ace_parse_obj.set_file_name(ace_file_list[i]);
      ace_parse_obj.set_text_data(text_each);
      ace_data_obj = ace_parse_obj.get_ace_data_obj();
      ace_parse_obj.clear();

      //Write directory data
      ace_wri_obj.set_ace_file_name(dummy_data.c_str());
      ace_wri_obj.set_ace_data_obj(ace_data_obj);
      ace_wri_obj.set_previous_line_no(line_no_pre);
      xsdir_data = ace_wri_obj.get_dir_data();
      ace_data_obj.clear();
      ace_wri_obj.clear();
    }
    remove(dummy_data.c_str());
    vector<string>().swap(text_each);

    modify_file_name_route(collected_file_name, xsdir_data);

    xsdir_vec.push_back(xsdir_data);
  }
  fout.close();

  
  set_xsdir_header_list();
  if( static_cast<int>(output_xsdir_name.size()) == 0 )
  {
    cout << endl;
    for(int i=0; i<static_cast<int>(xsdir_header_list.size()); i++)
    {
      cout << xsdir_header_list[i] << endl;
    }
    for(int i=0; i<static_cast<int>(xsdir_vec.size()); i++)
    {
      cout << xsdir_vec[i] << endl;
    }
  }
  else
  {
    fout.open(output_xsdir_name.c_str());
    for(int i=0; i<static_cast<int>(xsdir_header_list.size()); i++)
    {
      fout << xsdir_header_list[i] << endl;
    }
    for(int i=0; i<static_cast<int>(xsdir_vec.size()); i++)
    {
      fout << xsdir_vec[i] << endl;
    }
    fout.close();
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataCollector::set_data_check()
{
  vector<string> err_com;

  if( static_cast<int>(output_ace_file_name.size()) == 0 )
  {
    err_com.push_back("Output ace file name is not set.");
    err_com.push_back("Please set the output ace file name.");
    err_com.push_back("");
  }

  if( static_cast<int>(ace_dir_name.size()) == 0 )
  {
    err_com.push_back("Ace directory name is not set.");
    err_com.push_back("Please set the ace directory name.");
    err_com.push_back("");
  }

  if( static_cast<int>(mod_suffix.size()) > 3 )
  {
    string mod_suffix_tras = mod_suffix;
    transform(mod_suffix_tras.begin(), mod_suffix_tras.end(), mod_suffix_tras.begin(), ::tolower);
    if( mod_suffix_tras == "none" || mod_suffix_tras == "skip" )
    {
      mod_suffix.clear();
    }
    else
    {
      string str_data = "Modified suffix id : " + mod_suffix;
      err_com.push_back(str_data);
      err_com.push_back("The character number of modified suffix id must be equal to 3.");
      err_com.push_back("(For example, 50c or 20t)");
      err_com.push_back("Please check the modified suffix id.");
      err_com.push_back("");
    }
  }

  if( static_cast<int>(err_com.size()) > 0 )
  {
    string class_name = "AceDataCollector";
    string func_name  = "set_data_check()";
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataCollector::search_ace_data_file(string dir_name)
{
  vector<int>().swap(mat_list);
  vector<string>().swap(ace_file_list);

  DIR* ace_dir = opendir(dir_name.c_str());
  if( ace_dir != NULL )
  {
    struct dirent* ace_file;
    do
    {
      ace_file = readdir(ace_dir);
      if( ace_file != NULL )
      {
        string file_name = ace_file->d_name;

        if( file_name.find(".",0) != string::npos )
        {
          if( static_cast<int>(file_name.find(".",0)) == 0 )
          {
            continue;
          }
        }

        file_name = dir_name + "/" + file_name;
        if( check_ace_file_name(file_name) == 0 )
        {
          ace_file_list.push_back(file_name);

          int mat_val = read_mat_data(file_name);
          mat_list.push_back(mat_val);
        }
      }
    }
    while( ace_file != NULL );
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int AceDataCollector::check_ace_file_name(string file_name)
{
  ifstream fin;
  fin.open(file_name.c_str());

  if( !fin )
  {
    return -1;
  }

  int line_no_max = 2;
  int line_no     = 0;
  while( !fin.eof() )
  {
    string line_data;
    getline(fin, line_data);

    if( static_cast<int>(line_data.size()) > 0 )
    {
      line_no++;
    }

    if( line_no > line_no_max )
    {
      return 0;
    }
  }

  if( line_no <= line_no_max )
  {
    return -2;
  }

  return -3;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int AceDataCollector::read_mat_data(string file_name)
{
  ifstream fin;
  fin.open(file_name.c_str());

  int mat_val = -1;
  if( !fin )
  {
    return mat_val;
  }

  string line_data;
  getline(fin, line_data);
  getline(fin, line_data);
  fin.close();

  mat_val = -2;
  if( line_data.find_last_of("mat") != string::npos )
  {
    int pos = static_cast<int>(line_data.find_last_of("mat")) + 1;
    line_data = line_data.substr(pos,4);

    mat_val = atoi(line_data.c_str());
  }

  return mat_val;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataCollector::modify_ace_file_list_order()
{
  int file_no = static_cast<int>(ace_file_list.size());

  vector<int>    mod_pos_list;
  vector<string> ace_file_list_new;
  mod_pos_list.resize(file_no);
  ace_file_list_new.resize(file_no);
  for(int i=0; i<file_no; i++)
  {
    mod_pos_list[i] = 0;
  }
 
  if( output_ace_file_mode != thermal_ace_mode )
  {
    //Sort with material number
    sort(mat_list.begin(), mat_list.end());
    for(int i=0; i<file_no; i++)
    {
      int mat_val = read_mat_data(ace_file_list[i]);
      for(int j=0; j<file_no; j++)
      {
        if( mod_pos_list[j] != 0 )
        {
          continue;
        }
  
        if( mat_val == mat_list[j] )
        {
          mod_pos_list[j] = 1;
          ace_file_list_new[j] = ace_file_list[i];
          break;
        }
      }
    }
    ace_file_list = ace_file_list_new;
  }
  else
  {
    //Sort with ACE file name
    sort(ace_file_list.begin(), ace_file_list.end());
  }

  vector<string>().swap(ace_file_list_new);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> AceDataCollector::copy_ace_file(string file_name)
{
  vector<string> ace_text;
  vector<string>().swap(ace_text);

  ifstream fin;
  fin.open(file_name.c_str());
  if( !fin )
  {
    return ace_text;
  }

  int line_no        = 0;
  int mod_suffix_flg = static_cast<int>(mod_suffix.size());
  int blank_no       = 0;

  string line_data;
  while( !fin.eof() )
  {
    getline(fin, line_data);

    if( line_data.size() > 0 )
    {
      blank_no = 0;
    }
    else
    {
      blank_no++;

      if( blank_no > 100000000 )
      {
        string class_name = "AceDataCollector";
        string func_name  = "copy_ace_file(string file_name)";

        string str_data   = "  ACE file name : " + file_name;

        vector<string> err_com;
        err_com.push_back("A huge number of blank line data is found.");
        err_com.push_back("The ACE file name may not be the directory name.");
        err_com.push_back("Please check the ACE file name is collect or not.");
        err_com.push_back("");
        err_com.push_back(str_data);
        err_com.push_back("");
        err_com.push_back("FRENDY recognizes that after // is comment line.");
        err_com.push_back("Please check that the ACE file name contains // or not.");

        err_obj.output_runtime_error(class_name, func_name, err_com);
      }
    }

    if( !fin.eof() )
    {
      if( line_no == 0 && mod_suffix_flg > 0 )
      {
        modify_suffix_id(line_data, mod_suffix);
      }

      ace_text.push_back(line_data);
      line_no++;
    }
  }
  fin.close();

  return ace_text;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataCollector::modify_suffix_id(string& line_data, string suffix_new)
{
  if( static_cast<int>(line_data.size()) < 10 )
  {
    return;
  }
  else if( static_cast<int>(suffix_new.size()) == 0 )
  {
    return;
  }

  int suffix_no = static_cast<int>(suffix_new.size());
  if( suffix_no > 3 )
  {
    suffix_new = suffix_new.substr(0, 3);
  }
  else if( suffix_no < 3 )
  {
    for(int i=0; i<3-suffix_no; i++)
    {
      suffix_new = suffix_new + "0";
    }
  }

  line_data.replace(7, 3, suffix_new.c_str());
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataCollector::read_ace_data(vector<string>& text)
{
  //Read basic parameters
  Integer         mcnpx_mode_flg;
  Real            aw0, tz;
  string          discriptive_data;
  vector<string>  title_data;

  AceFileReader ace_read_obj;
  ace_read_obj.set_text_data(text);
  ace_read_obj.get_title_data(mcnpx_mode_flg, aw0, tz, discriptive_data, title_data);

  string ace_case = str_obj.trim_space(title_data[0]);
  ace_case = ace_case.substr(ace_case.length() - 1);
  transform(ace_case.begin(), ace_case.end(), ace_case.begin(), ::tolower);
  if( ace_case == "c" ) //fast data only
  {
    vector<Integer> zi_vec;
    vector<Real>    awr_vec;
    ace_read_obj.get_mat_data(zi_vec, awr_vec);

    //Add izaid and awr data
    int pointer_data_no = 8;
    vector<int> pointer_vec;
    ace_read_obj.get_pointer_data(pointer_data_no, pointer_vec);

    zaid_list.push_back(pointer_vec[1]); //e.g., 1001, 92235
    awr_list.push_back(aw0);
  }
  ace_read_obj.clear();
}


////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataCollector::write_ace_file(ofstream& fout, string& ace_output, vector<string>& text,
                                      int ele_no, int alpha_no)
{
  //Set output ace file name
  if( calc_mode == collect_mode )
  {
    ace_output = output_ace_file_name; 

    if( ele_no > 0 )
    {
      ace_output = ace_output + alphabet_list[ele_no-1];
    }
 
    ace_output = ace_output + alphabet_list[alpha_no];
  }
  else //if( calc_mode == individual_mode )
  {
    //Read basic parameters
    Integer         mcnpx_mode_flg;
    Real            aw0, tz;
    string          discriptive_data;
    vector<string>  title_data;

    AceFileReader ace_read_obj;
    ace_read_obj.set_text_data(text);
    ace_read_obj.get_title_data(mcnpx_mode_flg, aw0, tz, discriptive_data, title_data);
    ace_read_obj.clear();

    ace_output = str_obj.trim_space(title_data[0]);  //e.g., 1001.50c, lwtr.50t
    discriptive_data.clear();
    vector<string>().swap(title_data);

    modify_suffix_id(ace_output, mod_suffix);

    if( output_ace_file_mode != thermal_ace_mode )
    {
      int digit_no = static_cast<int>(ace_output.find("."));
      if( digit_no > 0 && digit_no < 5 )
      {
        for(int i=0; i<5 - digit_no; i++)
        {
          ace_output = "0" + ace_output;
        }
      }
    }
  }

  //Output ace file
  fout.close();
  fout.open(ace_output.c_str());

  if( !fout )
  {
    string class_name = "AceDataCollector";
    string func_name  = "write_ace_file(vector<string>& text, int ele_no, int alpha_no)";

    vector<string> err_com;
    string str_data = "Output file name : " + ace_output;
    err_com.push_back(str_data);
    err_com.push_back("This output file can not open.");
    err_com.push_back("Please check the output file or write authority of this directory.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  int i_max = static_cast<int>(text.size());
  for(int i=0; i<i_max; i++)
  {
    fout << text[i] << endl;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataCollector::modify_file_name_route(string ace_output, string& xsdir_data)
{
  string original_name = "filename route";
  if( xsdir_data.find(original_name.c_str(), 0) == string::npos )
  {
    return;
  }

  int pos_sta = static_cast<int>(xsdir_data.find(original_name.c_str(), 0));
  int pos_end = static_cast<int>(original_name.size()) + pos_sta;

  string xsdir_new = xsdir_data.substr(0, pos_sta) + ace_output + " 0" + xsdir_data.substr(pos_end);

  xsdir_data = xsdir_new;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataCollector::set_xsdir_header_list()
{
  xsdir_header_list.clear();

  if( static_cast<int>(zaid_list.size()) == 0 )
  {
    return;
  }

  xsdir_header_list = get_awr_list();

  TimeUtils time_obj;
  xsdir_header_list.push_back(time_obj.get_current_date_dd_mmm_yyyy());

  xsdir_header_list.push_back("directory");
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> AceDataCollector::get_awr_list()
{
  vector<string> awr_list;
  awr_list.clear();

  awr_list.push_back("atomic weight ratios");
  awr_list.push_back("   0001   1.00000000   0001   1.00000000");

  vector<int>           z_sort;
  vector<vector<int> >  zaid_sort;
  vector<vector<Real> > awr_sort;
  get_zaid_awr_list(z_sort, zaid_sort, awr_sort);


  int i_max = static_cast<int>(zaid_sort.size());
  for(int i=0; i<i_max; i++)
  {
    vector<string> awr_list_each;
    awr_list_each.clear();

    int nat_flg = 0;
    if( z_sort[i] < static_cast<int>(awr_nat_list.size()) )
    {
      if( awr_nat_list[z_sort[i]] > min_value )
      {
        nat_flg = 1;
      }
    }

    int j_max = static_cast<int>(zaid_sort[i].size());
    awr_list_each.resize(j_max + nat_flg);
    if( nat_flg > 0 )
    {
      ostringstream oss_z, oss_a; 
      oss_z << z_sort[i] * 1000;
      oss_a << fixed << setprecision(8) << showpoint << awr_nat_list[z_sort[i]];
      string str_z = oss_z.str();
      string str_a = oss_a.str();

      int space_no_z =  7 - static_cast<int>(str_z.length());
      int space_no_a = 13 - static_cast<int>(str_a.length());
      for(int k=0; k<space_no_z; k++)
      {
        str_z = " " + str_z;
      }
      for(int k=0; k<space_no_a; k++)
      {
        str_a = " " + str_a;
      }
      awr_list_each[0] = str_z + str_a;
    }

    for(int j=0; j<j_max; j++)
    {
      ostringstream oss_z, oss_a;
      oss_z << zaid_sort[i][j];
      oss_a << fixed << setprecision(8) << showpoint << awr_sort[i][j];
      string str_z = oss_z.str();
      string str_a = oss_a.str();

      int space_no_z =  7 - static_cast<int>(str_z.length());
      int space_no_a = 13 - static_cast<int>(str_a.length());
      for(int k=0; k<space_no_z; k++)
      {
        str_z = " " + str_z;
      }
      for(int k=0; k<space_no_a; k++)
      {
        str_a = " " + str_a;
      }
      awr_list_each[j + nat_flg] = str_z + str_a;
    }

    string awr_line = "";
    for(int j=0; j<j_max+nat_flg; j++)
    {
      awr_line = awr_line + awr_list_each[j];
      if( static_cast<int>(awr_line.length()) > 70 )
      {
        awr_list.push_back(awr_line);
        awr_line = "                    ";
      }
    }
    if( str_obj.get_no_space_string_length(awr_line) > 0 )
    {
      awr_list.push_back(awr_line);
    }
    awr_line.clear();
  }

  return awr_list;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataCollector::get_zaid_awr_list(vector<int>&           z_sort,
                                         vector<vector<int> >&  zaid_sort,
                                         vector<vector<Real> >& awr_sort)
{
  int zaid_no = static_cast<int>(zaid_list.size());

  z_sort.clear();
  vector<vector<int> >().swap(zaid_sort);
  vector<vector<Real> >().swap(awr_sort);
  if( zaid_no == 0 )
  {
    return;
  }

  vector<int> zaid_list_mod = zaid_list;
  sort(zaid_list_mod.begin(), zaid_list_mod.end());
  int zaid_pre = 0;
  int z_pre    = zaid_list_mod[0] / 1000;

  vector<int> zaid_each;
  zaid_each.clear();
  zaid_sort.clear();
  for(int i=0; i<zaid_no; i++)
  {
    if( zaid_pre != zaid_list_mod[i] )
    {
      if( z_pre != zaid_list_mod[i] / 1000 )
      {
        z_sort.push_back(z_pre);
        zaid_sort.push_back(zaid_each);
        zaid_each.clear();

        z_pre = zaid_list_mod[i] / 1000;
      }

      zaid_each.push_back(zaid_list_mod[i]);
      zaid_pre = zaid_list_mod[i];
    }
  }

  if( static_cast<int>(zaid_each.size()) > 0 )
  {
    z_sort.push_back(z_pre);
    zaid_sort.push_back(zaid_each);
    zaid_each.clear();
  }

  int i_max = static_cast<int>(zaid_sort.size());
  awr_sort.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(zaid_sort[i].size());
    awr_sort[i].resize(j_max);
    for(int j=0; j<j_max; j++)
    {
      for(int k=0; k<zaid_no; k++)
      {
        if( zaid_sort[i][j] == zaid_list[k] )
        {
          awr_sort[i][j] = awr_list[k];
          break;
        }
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataCollector::clear()
{
  vector<string>().swap(ace_file_list);
  vector<int>().swap(mat_list);

  vector<Real>().swap(awr_nat_list);
  vector<Real>().swap(awr_list);
  vector<int>().swap(zaid_list);
  vector<string>().swap(xsdir_header_list);

  output_ace_file_mode = fast_ace_mode;

  output_ace_file_name.clear();
  ace_dir_name.clear();
  mod_suffix.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataCollector::set_calc_mode(int int_val)
{
  calc_mode = int_val;

  if( calc_mode != collect_mode && calc_mode != individual_mode )
  {
    string class_name = "AceDataCollector";
    string func_name  = "set_calc_mode(int int_val)";

    ostringstream oss01;
    oss01 << int_val;
    string str_data = "Calculation mode you set : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("This calculation mode can not be treated in this program.");
    err_com.push_back("The available calculation mode is 1 (collect mode) and 2 (individual mode).");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

void AceDataCollector::set_output_ace_file_mode(int int_val)
{
  output_ace_file_mode = int_val;

  if( output_ace_file_mode != fast_ace_mode && output_ace_file_mode != thermal_ace_mode )
  {
    string class_name = "AceDataCollector";
    string func_name  = "set_output_ace_file_mode(int int_val)";

    ostringstream oss01;
    oss01 << int_val;
    string str_data = "Output ace file mode you set : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("This output ace file mode can not be treated in this program.");
    err_com.push_back("The available output ace file mode is 1 (for fast), 2 (for thermal scatter).");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

void AceDataCollector::set_output_ace_file_name(string str_data)
{
  output_ace_file_name = str_data;
}

void AceDataCollector::set_output_xsdir_name(string str_data)
{
  output_xsdir_name = str_data;
}

void AceDataCollector::set_ace_dir_name(string str_data)
{
  ace_dir_name = str_data;
}

void AceDataCollector::set_mod_suffix_id(string str_data)
{
  mod_suffix = str_data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int    AceDataCollector::get_calc_mode()
{
  return calc_mode;
}

int    AceDataCollector::get_output_ace_file_mode()
{
  return output_ace_file_mode;
}

string AceDataCollector::get_output_ace_file_name()
{
  return output_ace_file_name;
}

string AceDataCollector::get_output_xsdir_name()
{
  return output_xsdir_name;
}

string AceDataCollector::get_ace_dir_name()
{
  return ace_dir_name;
}

string AceDataCollector::get_mod_suffix_id()
{
  return mod_suffix;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataCollector::set_awr_nat_list()
{
  awr_nat_list.resize(119);
  awr_nat_list[ 0] =   1.00000000;
  awr_nat_list[ 1] =   0.99928126;
  awr_nat_list[ 2] =   3.96821753;
  awr_nat_list[ 3] =   6.88137314;
  awr_nat_list[ 4] =   8.93476259;
  awr_nat_list[ 5] =  10.71812779;
  awr_nat_list[ 6] =  11.90752173;
  awr_nat_list[ 7] =  13.88637504;
  awr_nat_list[ 8] =  15.86195669;
  awr_nat_list[ 9] =  18.83519687;
  awr_nat_list[10] =  20.00634570;
  awr_nat_list[11] =  22.79227500;
  awr_nat_list[12] =  24.09620719;
  awr_nat_list[13] =  26.74975291;
  awr_nat_list[14] =  27.84423070;
  awr_nat_list[15] =  30.70768100;
  awr_nat_list[16] =  31.78954469;
  awr_nat_list[17] =  35.14843998;
  awr_nat_list[18] =  39.60482555;
  awr_nat_list[19] =  38.76242492;
  awr_nat_list[20] =  39.73370878;
  awr_nat_list[21] =  44.56971693;
  awr_nat_list[22] =  47.45579715;
  awr_nat_list[23] =  50.50388557;
  awr_nat_list[24] =  51.54942600;
  awr_nat_list[25] =  54.46609813;
  awr_nat_list[26] =  55.36526191;
  awr_nat_list[27] =  58.42692768;
  awr_nat_list[28] =  58.18919265;
  awr_nat_list[29] =  63.00010624;
  awr_nat_list[30] =  64.81835121;
  awr_nat_list[31] =  69.12404255;
  awr_nat_list[32] =  72.01598397;
  awr_nat_list[33] =  74.27798382;
  awr_nat_list[34] =  78.28169183;
  awr_nat_list[35] =  79.21758237;
  awr_nat_list[36] =  83.07813085;
  awr_nat_list[37] =  84.73358639;
  awr_nat_list[38] =  86.86729785;
  awr_nat_list[39] =  88.14210172;
  awr_nat_list[40] =  90.44033758;
  awr_nat_list[41] =  92.10826505;
  awr_nat_list[42] =  95.13565284;
  awr_nat_list[43] =  98.05659454;
  awr_nat_list[44] = 100.20175523;
  awr_nat_list[45] = 102.02148732;
  awr_nat_list[46] = 105.50579590;
  awr_nat_list[47] = 106.94155510;
  awr_nat_list[48] = 111.44533005;
  awr_nat_list[49] = 113.83165264;
  awr_nat_list[50] = 117.69021830;
  awr_nat_list[51] = 120.71401719;
  awr_nat_list[52] = 126.50384850;
  awr_nat_list[53] = 125.81429347;
  awr_nat_list[54] = 130.16512368;
  awr_nat_list[55] = 131.76372376;
  awr_nat_list[56] = 136.14728843;
  awr_nat_list[57] = 137.71219853;
  awr_nat_list[58] = 138.91232944;
  awr_nat_list[59] = 139.69717875;
  awr_nat_list[60] = 143.00288492;
  awr_nat_list[61] = 145.65305955;
  awr_nat_list[62] = 149.06832806;
  awr_nat_list[63] = 150.65854885;
  awr_nat_list[64] = 155.89913932;
  awr_nat_list[65] = 157.56009717;
  awr_nat_list[66] = 161.10403904;
  awr_nat_list[67] = 163.51348130;
  awr_nat_list[68] = 165.82215671;
  awr_nat_list[69] = 167.48297577;
  awr_nat_list[70] = 171.56737460;
  awr_nat_list[71] = 173.46374263;
  awr_nat_list[72] = 176.95667648;
  awr_nat_list[73] = 179.39344199;
  awr_nat_list[74] = 182.26071715;
  awr_nat_list[75] = 184.60738337;
  awr_nat_list[76] = 188.59582367;
  awr_nat_list[77] = 190.56575429;
  awr_nat_list[78] = 193.40812524;
  awr_nat_list[79] = 195.27452198;
  awr_nat_list[80] = 198.86682579;
  awr_nat_list[81] = 202.62753934;
  awr_nat_list[82] = 205.42004239;
  awr_nat_list[83] = 207.18514782;
  awr_nat_list[84] = 207.20500000;
  awr_nat_list[85] = 208.19600000;
  awr_nat_list[86] = 220.11100000;
  awr_nat_list[87] = 221.08400000;
  awr_nat_list[88] = 224.08400000;
  awr_nat_list[89] = 225.05000000;
  awr_nat_list[90] = 230.04473032;
  awr_nat_list[91] = 229.05115957;
  awr_nat_list[92] = 235.98411575;
  awr_nat_list[93] = 235.01200000;
  awr_nat_list[94] = 241.96800000;
  awr_nat_list[95] = 240.91200000;
  awr_nat_list[96] = 244.87800000;
  awr_nat_list[97] = 244.87800000;
  awr_nat_list[98] = 248.84400000;
  awr_nat_list[99] = 251.81800000;
  awr_nat_list[100]= 254.79200000;
  awr_nat_list[101]= 242.97546700;
  awr_nat_list[102]= 245.95541300;
  awr_nat_list[103]= 248.93733800;
  awr_nat_list[104]= 250.92643200;
  awr_nat_list[105]= 252.91590300;
  awr_nat_list[106]= 255.89585200;
  awr_nat_list[107]= 257.88739700;
  awr_nat_list[108]= 260.86815700;
  awr_nat_list[109]= 262.85850400;
  awr_nat_list[110]= 264.84944200;
  awr_nat_list[111]= 269.81568400;
  awr_nat_list[112]= 274.78297100;
  awr_nat_list[113]= 280.74382900;
  awr_nat_list[114]= 282.73383300;
  awr_nat_list[115]= 284.72407500;
  awr_nat_list[116]= 286.71450400;
  awr_nat_list[117]= 288.70495900;
  awr_nat_list[118]= 290.69581500;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

