#include "NjoyUtils/NjoyInputReader.hpp"

using namespace frendy;

NjoyInputReader::NjoyInputReader(void)
{
  func_name_list_no = 23;
  func_name_list.resize(func_name_list_no);
  func_name_list_implemented.resize(func_name_list_no);

  func_name_list[pos_reconr] = "reconr";
  func_name_list[pos_broadr] = "broadr";
  func_name_list[pos_unresr] = "unresr";
  func_name_list[pos_heatr]  = "heatr";
  func_name_list[pos_thermr] = "thermr";
  func_name_list[pos_groupr] = "groupr";
  func_name_list[pos_gaminr] = "gaminr";
  func_name_list[pos_errorr] = "errorr";
  func_name_list[pos_covr]   = "covr";
  func_name_list[pos_moder]  = "moder";
  func_name_list[pos_dtfr]   = "dtfr";
  func_name_list[pos_ccccr]  = "ccccr";
  func_name_list[pos_matxsr] = "matxsr";
  func_name_list[pos_resxsr] = "resxsr";
  func_name_list[pos_acer]   = "acer";
  func_name_list[pos_powr]   = "powr";
  func_name_list[pos_wimsr]  = "wimsr";
  func_name_list[pos_plotr]  = "plotr";
  func_name_list[pos_viewr]  = "viewr";
  func_name_list[pos_mixr]   = "mixr";
  func_name_list[pos_purr]   = "purr";
  func_name_list[pos_leapr]  = "leapr";
  func_name_list[pos_gaspr]  = "gaspr";

  //0 : not implemented in FRENDY
  //1 : implemented in FRENDY
  func_name_list_implemented[pos_reconr] = 1; //reconr
  func_name_list_implemented[pos_broadr] = 1; //broadr
  func_name_list_implemented[pos_unresr] = 1; //unresr
  func_name_list_implemented[pos_heatr]  = 0; //heatr
  func_name_list_implemented[pos_thermr] = 1; //thermr
  func_name_list_implemented[pos_groupr] = 0; //groupr
  func_name_list_implemented[pos_gaminr] = 0; //gaminr
  func_name_list_implemented[pos_errorr] = 0; //errorr
  func_name_list_implemented[pos_covr]   = 0; //covr
  func_name_list_implemented[pos_moder]  = 1; //moder
  func_name_list_implemented[pos_dtfr]   = 0; //dtfr
  func_name_list_implemented[pos_ccccr]  = 0; //ccccr
  func_name_list_implemented[pos_matxsr] = 0; //matxsr
  func_name_list_implemented[pos_resxsr] = 0; //resxsr
  func_name_list_implemented[pos_acer]   = 1; //acer
  func_name_list_implemented[pos_powr]   = 0; //powr
  func_name_list_implemented[pos_wimsr]  = 0; //wimsr
  func_name_list_implemented[pos_plotr]  = 0; //plotr
  func_name_list_implemented[pos_viewr]  = 0; //viewr
  func_name_list_implemented[pos_mixr]   = 0; //mixr
  func_name_list_implemented[pos_purr]   = 1; //purr
  func_name_list_implemented[pos_leapr]  = 0; //leapr
  func_name_list_implemented[pos_gaspr]  = 1; //gaspr
}

NjoyInputReader::~NjoyInputReader(void)
{
  clr_obj.clear_vec_array1_str(func_name_list);
  func_name_list_implemented.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NjoyInputReader::search_each_input(ifstream& fin, string& input_case)
{
  search_each_input(fin, input_case, 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NjoyInputReader::search_each_input(ifstream& fin, string& input_case, int line_no)
{
  int input_case_check = check_input_case(fin, input_case, line_no);

  if( input_case_check < 0 )
  {
    string class_name = "NjoyInputReader";
    string func_name  = "search_each_input(ifstream& fin, string& input_case)";

    vector<string> err_com;
    string str_data01 = "Input case     : " + input_case;
    err_com.push_back(str_data01);

    if( line_no > 0 )
    {
      ostringstream oss01;
      oss01 << line_no;
      string str_data02 = "Start line No. : " + oss01.str();
      err_com.push_back(str_data02);
    }

    if( input_case_check == -1 )
    {
      err_com.push_back("stop is found before the input case.");
    }
    else if( input_case_check == -2 )
    {
      err_com.push_back("In this input file, there is no input case.");
    }
    else
    {
      err_com.push_back("This input file may not be appropriate.");
    }

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int NjoyInputReader::check_input_case(ifstream& fin, string& input_case)
{
  return check_input_case(fin, input_case, 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int NjoyInputReader::check_input_case(ifstream& fin, string& input_case, int start_line_no)
{
  string class_name = "NjoyInputReader";
  string func_name  = "check_input_case(ifstream& fin, string& input_case)";
  if( !fin )
  {
    string str_data = "Input case : " + input_case;

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("There is no input file.");
    err_com.push_back("Please check the input file name.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  string         line_data;
  vector<string> read_data;
  string         end_data = "stop";

  int list_no = check_input_case(input_case);
  if( list_no == -1 )
  {
    string str_data = "Input case : " + input_case;

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("This input case is not used in NJOY input file.");
    err_com.push_back("Please check the input case or func_name_list used in this class.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  int input_case_size = static_cast<int>(input_case.size());
  int end_data_size   = static_cast<int>(end_data.size());

  int input_case_check =  0;
  int line_no          = -1;
  while(!fin.eof())
  {
    line_data.clear();
    getline(fin, line_data);
    line_no++;

    if( line_no < start_line_no )
    {
      continue;
    }

    read_data = read_line_without_slash(line_data);

    if( static_cast<int>(read_data.size()) == 0 )
    {
      //If parameter is not found, this data must be parameter line.
      continue;
    }

    int    read_data_size = static_cast<int>(read_data[0].size());
    string read_data_up   = read_data[0];
    string input_case_up  = input_case;
    string end_data_up    = end_data;
    transform(read_data_up.begin(),  read_data_up.end(),  read_data_up.begin(),  ::toupper);
    transform(input_case_up.begin(), input_case_up.end(), input_case_up.begin(), ::toupper);
    transform(end_data_up.begin(),   end_data_up.end(),   end_data_up.begin(),   ::toupper);

    if( read_data_size == input_case_size
        && strcmp(read_data_up.c_str(), input_case_up.c_str()) == 0 )
    {
      input_case_check = line_no; //line_no > 0
      break;
    }
    else if( read_data_size == end_data_size
             && strcmp(read_data_up.c_str(), end_data_up.c_str()) == 0 )
    {
      input_case_check = -1;
      break;
    }
    clr_obj.clear_vec_array1_str(read_data);
  }
  line_data.clear();
  clr_obj.clear_vec_array1_str(read_data);

  if( input_case_check == 0 && fin.eof() )
  {
    input_case_check = -2;
  }

  return input_case_check;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int NjoyInputReader::check_input_case(string& input_case)
{
  int list_no        = -1;
  string input_case_up = input_case;
  transform(input_case_up.begin(), input_case_up.end(), input_case_up.begin(), ::toupper);
  for(int i=0; i<func_name_list_no; i++)
  {
    string func_name_up = func_name_list[i];
    transform(func_name_up.begin(), func_name_up.end(), func_name_up.begin(), ::toupper);
    if( strcmp(input_case_up.c_str(), func_name_up.c_str()) == 0 )
    {
      list_no = i;
      break;
    }
  }

  return list_no;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> NjoyInputReader::read_line_without_slash(string line_data)
{
    erase_after_slash(line_data);
    return read_line(line_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> NjoyInputReader::read_line(string line_data)
{
  vector<string> str_vec;
  str_vec.clear();

  substitute_quote(line_data);

  line_data = str_util.trim_space(line_data);

  int i = static_cast<int>(line_data.find_first_of(" 　\t"));
  while( i >= 0 )
  {
    str_vec.push_back(line_data.substr(0, i));
    line_data.erase(0, i);

    line_data = str_util.trim_space(line_data);

    i = static_cast<int>(line_data.find_first_of(" 　\t"));
  }

  str_vec.push_back(line_data);

  search_quote(str_vec);

  vector<string> str_mod;
  str_mod.clear();
  for(int j=0; j<static_cast<int>(str_vec.size()); j++)
  {
    if( static_cast<int>(str_vec[j].size()) > 0 )
    {
      str_mod.push_back(str_vec[j]);
    }
  }
  str_vec = str_mod;
  str_mod.clear();

  return str_vec;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NjoyInputReader::substitute_quote(string& str_data)
{
  vector<string> quote_vec;
  quote_vec.resize(2);
  quote_vec[0] = "'";
  quote_vec[1] = '"';

  for(int j=0; j<static_cast<int>(quote_vec.size()); j++)
  {
    string ori_data, mod_data;
    ori_data = str_data;
    mod_data.clear();

    int i = static_cast<int>(str_data.find_first_of(quote_vec[j]));
    while( i >= 0 )
    {
      if( i != 0 )
      {
        mod_data = mod_data + ori_data.substr(0, i);
        ori_data.erase(0, i+1);
      }
      else
      {
        ori_data.erase(0, 1);
      }
      mod_data = mod_data + " " + quote_vec[j] + " ";

      i = static_cast<int>(ori_data.find_first_of(quote_vec[j]));
    }
    mod_data = mod_data + ori_data;

    str_data = mod_data;
    mod_data.clear();
    ori_data.clear();
  }
  quote_vec.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NjoyInputReader::search_quote(vector<string>& str_vec)
{
  vector<string> quote_vec;
  quote_vec.resize(2);
  quote_vec[0] = "'";
  quote_vec[1] = '"';

  vector<int> quote_pos;
  quote_pos.resize(2);
  quote_pos[0] = 0;
  quote_pos[1] = 0;

  vector<string> str_mod;
  str_mod.clear();

  int quote_flg  = 0;
  int quote_mode = -1;
  for(int i=0; i<static_cast<int>(str_vec.size()); i++)
  {
    quote_pos[0] = static_cast<int>(str_vec[i].find(quote_vec[0]));
    quote_pos[1] = static_cast<int>(str_vec[i].find(quote_vec[1]));
    if( quote_flg > 0 && quote_pos[quote_mode] >= 0 )
    {
      quote_flg  =  0;
      quote_mode = -1;
      continue;
    }

    if( quote_flg == 0 && (quote_pos[0] >= 0 || quote_pos[1] >= 0 ) )
    {
      quote_flg = 1; 

      if( quote_pos[0] >= 0 )
      {
        if( quote_pos[1] >= 0 && quote_pos[1] < quote_pos[0] )
        {
          quote_mode = 1;
        }
        else
        {
          quote_mode = 0;
        }
      }
      else
      {
        quote_mode = 1;
      }
      continue;
    }

    if( quote_flg <= 1 )
    {
      str_mod.push_back(str_vec[i]);
      if( quote_flg == 1 )
      {
        quote_flg++;
      }
    }
    else
    {
      int j = static_cast<int>(str_mod.size()) - 1;
      str_mod[j] = str_mod[j] + " " + str_vec[i];
      quote_flg++;
    }
  }
  str_vec.clear();
  quote_vec.clear();

  str_vec = str_mod;
  str_mod.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NjoyInputReader::erase_after_slash(string& str_data)
{
  vector<string> str_vec;
  str_vec.resize(1);
  str_vec[0] = str_data;

  erase_after_slash(str_vec);

  str_data = str_vec[0];
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NjoyInputReader::erase_after_slash(vector<string>& str_vec)
{
  vector<string> str_mod;
  str_mod.clear();

  string::size_type pos_j;

  for(int i=0; i<static_cast<int>(str_vec.size()); i++)
  {
    pos_j = str_vec[i].find_first_of("/");

    int j = static_cast<int>(pos_j);
    int k = static_cast<int>(str_vec[i].find_first_of("'"));
    int l = static_cast<int>(str_vec[i].find_first_of('"'));
    if( k >= 0 || l >= 0)
    {
      if( k >=0 && (k < l || l < 0) )
      {
        if( k < j )
        {
          int m = static_cast<int>(str_vec[i].find("'", k+1));
          if( j < m )
          {
            pos_j = str_vec[i].find_first_of("/", m+1);
            j = static_cast<int>(pos_j);
          }
        }
      }
      else if( l >= 0 && (l < k || k < 0) )
      {
        if( l < j )
        {
          int m = static_cast<int>(str_vec[i].find('"', l+1));
          if( j < m )
          {
            pos_j = str_vec[i].find_first_of("/", m+1);
            j = static_cast<int>(pos_j);
          }
        }
      }
    }

    if( j == 0 && pos_j == string::npos )
    {
      break;
    }
    else if( j >= 0 )
    {
      str_mod.push_back(str_vec[i].substr(0, j));
      break;
    }
    else
    {
      str_mod.push_back(str_vec[i]);
    }
  }
  str_vec.clear();

  str_vec = str_mod;
  str_mod.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<vector<int> > NjoyInputReader::get_njoy_input_list(string file_name)
{
  ifstream fin_njoy;
  fin_njoy.open(file_name.c_str());

  if( !fin_njoy )
  {
    string class_name = "NjoyInputReader";
    string func_name  = "get_njoy_input_list";

    string str_data   = "Input file name of NJOY : " + file_name;
    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("Input file can not open.");
    err_com.push_back("Please check the input file name.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
  fin_njoy.close();

  vector<int>          line_no_list;
  vector<vector<int> > njoy_input_name_array;
  njoy_input_name_array.resize(2);
  for(int i=0; i<func_name_list_no; i++)
  {
    int line_no = 0;
    while( line_no >= 0 )
    {
      fin_njoy.open(file_name.c_str());
      line_no = check_input_case(fin_njoy, func_name_list[i], line_no);
      fin_njoy.close();

      if( line_no >= 0 )
      {
        njoy_input_name_array[0].push_back(i);
        njoy_input_name_array[1].push_back(line_no);
        line_no_list.push_back(line_no);

        line_no++;
      }
    }
  }

  vector<vector<int> > njoy_input_list;
  int data_no = static_cast<int>(line_no_list.size());
  njoy_input_list.resize(data_no);
  if( data_no > 0 )
  {
    sort(line_no_list.begin(), line_no_list.end());
    for(int i=0; i<data_no; i++)
    {
      int line_no = njoy_input_name_array[1][i];
      for(int j=0; j<data_no; j++)
      {
        if( line_no_list[j] == line_no )
        {
          njoy_input_list[j].resize(2);
          njoy_input_list[j][0] = njoy_input_name_array[0][i];
          njoy_input_list[j][1] = line_no;
          break;
        }
      }
    }
  }

  return njoy_input_list;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> NjoyInputReader::get_func_name_list()
{
  return func_name_list;
}


////////////////////////////////////////////////////////////////////////////////////////////////////

Integer NjoyInputReader::get_file_no(string tape_name)
{
  string tape_name_mod = tape_name;
  transform(tape_name_mod.begin(), tape_name_mod.end(), tape_name_mod.begin(), ::tolower);

  if( (static_cast<int>(tape_name.size()) != 6 && static_cast<int>(tape_name.size()) != 5) ||
       static_cast<int>(tape_name_mod.find("tape")) != 0 )
  {
    string class_name = "NjoyInputReader";
    string func_name  = "get_file_no(string tape_name)";

    ostringstream oss;
    oss << static_cast<int>(tape_name.size());
    string str_data01   = "tape_name : " + tape_name;
    string str_data02   = "            (" + oss.str() + " characters)";

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("This tape_name is not available in this program.");
    err_com.push_back("Available tape_name is tapeXX (6 characters).");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  return numeric_string_cast<Integer>(tape_name.substr(4, 2));
}

