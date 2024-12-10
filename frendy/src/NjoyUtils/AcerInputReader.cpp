#include "NjoyUtils/AcerInputReader.hpp"

using namespace frendy;

//Initialize static const value
const Real AcerInputReader::suffix_za_id_def = 0.0;
const Real AcerInputReader::temp_def         = 300.0;
const Real AcerInputReader::ene_max_th_def   = 1.0E+3;

AcerInputReader::AcerInputReader(void)
{
  clear();
}

AcerInputReader::~AcerInputReader(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void AcerInputReader::read_input(string file_name)
{
  read_input(file_name, 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void AcerInputReader::read_input(string file_name, int line_no)
{
  clear();

  input_acer = file_name;

  //open input file
  ifstream fin(input_acer.c_str());
  if( !fin )
  {
    string class_name = "AcerInputReader";
    string func_name  = "read_input(string file_name)";

    string str_data = "File name : " + file_name;

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("There is no input file.");
    err_com.push_back("Please check the input file name.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //read until acer input 
  string input_case = "acer";
  rn_obj.search_each_input(fin, input_case, line_no);

  //read acer input
  read_common_data(fin);

  if( opt_run == 1 )
  {
    read_fast_data(fin);
  }
  else if( opt_run == 2 )
  {
    read_thermal_data(fin);
  }
  else if( opt_run == 3 )
  {
    read_dosimetry_data(fin);
  }
  else if( opt_run == 4 || opt_run == 5 )
  {
    read_photo_atomic_nuclear_data(fin);
  }
  else
  {
    string class_name = "AcerInputReader";
    string func_name  = "read_input(string file_name)";

    ostringstream oss;
    oss << opt_run;
    string str_data01 = "Input file name = " + input_acer;
    string str_data02 = "opt_run         = " + oss.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("The opt_run number is only available from -5 to 5");
    err_com.push_back("Please check the opt_run data.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  fin.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void AcerInputReader::read_common_data(ifstream& fin)
{
  string line_data;
  vector<string> input_data;

  //Card 01
  getline(fin, line_data);
  input_data = rn_obj.read_line_without_slash(line_data);

  if( static_cast<int>(input_data.size()) < 5 )
  {
    string class_name = "AcerInputReader";
    string func_name  = "read_common_data(ifstream& fin)";

    ostringstream oss;
    oss << input_data.size();
    string str_data01 = "Input file name = " + input_acer;
    string str_data02 = "Data no         = " + oss.str();
    string str_data03 = "Input data      = " + line_data;

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("The data number of card 1 is less than 5.");
    err_com.push_back("In card 1, 5 string data is required, i.e., endf_name, pendf_name,");
    err_com.push_back("gend_name, ace_name and mcnp_dir");
    err_com.push_back("Please check the input file.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  for(int i=0; i<5; i++)
  {
    int j = static_cast<int>(input_data[i].find_first_of("-"));
    if( j >= 0 )
    {
      string class_name = "AcerInputReader";
      string func_name  = "read_common_data(ifstream& fin)";

      string str_data = "tape no : " + input_data[i];

      vector<string> err_com;
      err_com.push_back(str_data);
      err_com.push_back("Binary mode, i.e., tape no less than 0, can not treat in FRENDY.");

      if( j==0 )
      {
        err_com.push_back("This file considered as the ascii mode file.");
        err_obj.output_caution(class_name, func_name, err_com);
      }
      else
      {
        err_com.push_back("Please check the input file name.");
        err_obj.output_runtime_error(class_name, func_name, err_com);
      }

      input_data[i] = input_data[i].substr(j+1);
    }
  }

  endf_name  = "tape" + input_data[0]; 
  pendf_name = "tape" + input_data[1]; 
  gendf_name = "tape" + input_data[2];
  ace_name   = "tape" + input_data[3];
  mcnp_dir   = "tape" + input_data[4];


  //Card 02
  getline(fin, line_data);
  input_data = rn_obj.read_line_without_slash(line_data);
  rn_obj.erase_after_slash(input_data);

  int i_max = static_cast<int>(input_data.size());
  if( i_max < 1 )
  {
    string class_name = "AcerInputReader";
    string func_name  = "read_common_data(ifstream& fin)";

    ostringstream oss;
    oss << input_data.size();
    string str_data01 = "Input file name = " + input_acer;
    string str_data02 = "Data no         = " + oss.str();
    string str_data03 = "Input data      = " + line_data;

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("The data number of card 2 is less than 1.");
    err_com.push_back("In card 2, 1 integer data is required, i.e., opt_run");
    err_com.push_back("Please check the input file.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  opt_run = numeric_string_cast<Integer>(input_data[0]);
  if( opt_run < 0 )
  {
    mcnpx_mode_flg =  1;
    opt_run     *= -1;
  }
  if( i_max > 1 )
  {
    opt_print = numeric_string_cast<Integer>(input_data[1]);
    if( opt_print != 0 && opt_print != 1 )
    {
      string class_name = "AcerInputReader";
      string func_name  = "read_common_data(ifstream& fin)";

      ostringstream oss;
      oss << opt_print;
      string str_data01 = "Input file name       = " + input_acer;
      string str_data02 = "Print option (iprint) = " + oss.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back("The print option is only available for itype=1.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }
  if( i_max > 2 )
  {
    opt_out_type = numeric_string_cast<Integer>(input_data[2]);
  }
  if( i_max > 3 )
  {
    suffix_za_id = numeric_string_cast<Real>(input_data[3]);
  }
  if( i_max > 4 )
  {
    zi_awr_pair_no = numeric_string_cast<Integer>(input_data[4]);
  }


  //Card 03
  getline(fin, line_data);
  input_data = rn_obj.read_line(line_data);
  discriptive_data = input_data[0];


  //Card 04
  if( zi_awr_pair_no > 0 )
  {
    getline(fin, line_data);
    input_data = rn_obj.read_line_without_slash(line_data);

    if( static_cast<Integer>(input_data.size()) < zi_awr_pair_no*2 )
    {
      string class_name = "AcerInputReader";
      string func_name  = "read_common_data(ifstream& fin)";

      ostringstream oss01, oss02;
      oss01 << input_data.size();
      oss02 << zi_awr_pair_no;
      string str_data01 = "Input file name = " + input_acer;
      string str_data02 = "Data no         = " + oss01.str();
      string str_data03 = "zi_awr_pair_no  = " + oss02.str();
      string str_data04 = "Input data      = " + line_data;

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back(str_data04);
      err_com.push_back("The data number of card 4 is less than zi_awr_pair_no*2.");
      err_com.push_back("Please check the input file.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    i_max = static_cast<int>(zi_awr_pair_no);
    zi_vec.resize(i_max);
    awr_vec.resize(i_max);
    for(int i=0; i<i_max; i++)
    {
      zi_vec[i]  = numeric_string_cast<Integer>(input_data[i*2]);
      awr_vec[i] = numeric_string_cast<Real>(input_data[i*2+1]);
    }
  }

  line_data.clear();
  clr_obj.clear_vec_array1_str(input_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void AcerInputReader::read_fast_data(ifstream& fin)
{
  string line_data;
  vector<string> input_data;

  //Card 05
  getline(fin, line_data);
  input_data = rn_obj.read_line_without_slash(line_data);

  int i_max = static_cast<int>(input_data.size());
  if( i_max < 1 )
  {
    string class_name = "AcerInputReader";
    string func_name  = "read_fast_data(ifstream& fin)";

    ostringstream oss;
    oss << input_data.size();
    string str_data01 = "Input file name = " + input_acer;
    string str_data02 = "Data no         = " + oss.str();
    string str_data03 = "Input data      = " + line_data;

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("The data number of card 5 is less than 1.");
    err_com.push_back("In card 5, 1 integer data is required, i.e., mat");
    err_com.push_back("Please check the input file.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  mat = numeric_string_cast<Integer>(input_data[0]);
  if( i_max > 1 )
  {
    temp = numeric_string_cast<Real>(input_data[1]);
  }


  //Card 06
  getline(fin, line_data);
  input_data = rn_obj.read_line_without_slash(line_data);

  i_max = static_cast<int>(input_data.size());
  if( i_max > 0 )
  {
    new_cummulative_angle_distr_flg = numeric_string_cast<Integer>(input_data[0]);
  }
  if( i_max > 1 )
  {
    detailed_photon_flg = numeric_string_cast<Integer>(input_data[1]);
  }


  //Card 07
  getline(fin, line_data);
  input_data = rn_obj.read_line_without_slash(line_data);

  i_max = static_cast<int>(input_data.size());
  if( i_max > 0 )
  {
    thinning_ene[0] = numeric_string_cast<Real>(input_data[0]);
  }
  if( i_max > 1 )
  {
    thinning_ene[1] = numeric_string_cast<Real>(input_data[1]);
  }
  if( i_max > 2 )
  {
    thinning_ene[2] = numeric_string_cast<Real>(input_data[2]);
  }

  line_data.clear();
  clr_obj.clear_vec_array1_str(input_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void AcerInputReader::read_thermal_data(ifstream& fin)
{
  string line_data;
  vector<string> input_data;

  //Card 08
  getline(fin, line_data);
  input_data = rn_obj.read_line_without_slash(line_data);

  int i_max = static_cast<int>(input_data.size());
  if( i_max < 1 )
  {
    string class_name = "AcerInputReader";
    string func_name  = "read_thermal_data(ifstream& fin)";

    ostringstream oss;
    oss << input_data.size();
    string str_data01 = "Input file name = " + input_acer;
    string str_data02 = "Data no         = " + oss.str();
    string str_data03 = "Input data      = " + line_data;

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("The data number of card 5 is less than 1.");
    err_com.push_back("In card 8, 1 integer data is required, i.e., mat.");
    err_com.push_back("Please check the input file.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  mat = numeric_string_cast<Integer>(input_data[0]);
  if( i_max > 1 )
  {
    temp = numeric_string_cast<Real>(input_data[1]);
  }
  if( i_max > 2 )
  {
    thermal_za_id_name = input_data[2];
  }


  //Card 08a
  getline(fin, line_data);
  input_data = rn_obj.read_line_without_slash(line_data);

  i_max = static_cast<int>(input_data.size());
  if( i_max < 1 )
  {
    string class_name = "AcerInputReader";
    string func_name  = "read_thermal_data(ifstream& fin)";

    ostringstream oss;
    oss << input_data.size();
    string str_data01 = "Input file name = " + input_acer;
    string str_data02 = "Data no         = " + oss.str();
    string str_data03 = "Input data      = " + line_data;

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("The data number of card 8a is less than 1.");
    err_com.push_back("In card 8a, 1 integer data is required, i.e., mod_za.");
    err_com.push_back("Please check the input file.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  mod_za[0] = numeric_string_cast<Integer>(input_data[0]);
  if( i_max > 1 )
  {
    mod_za[1] = numeric_string_cast<Integer>(input_data[1]);
  }
  if( i_max > 2 )
  {
    mod_za[2] = numeric_string_cast<Integer>(input_data[2]);
  }


  //Card 09
  getline(fin, line_data);
  input_data = rn_obj.read_line_without_slash(line_data);

  i_max = static_cast<int>(input_data.size());
  if( i_max < 4 )
  {
    string class_name = "AcerInputReader";
    string func_name  = "read_thermal_data(ifstream& fin)";

    ostringstream oss;
    oss << input_data.size();
    string str_data01 = "Input file name = " + input_acer;
    string str_data02 = "Data no         = " + oss.str();
    string str_data03 = "Input data      = " + line_data;

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("The data number of card 9 is less than 4.");
    err_com.push_back("In card 9, 4 integer data is required, i.e., mt_inelastic, bin_no,");
    err_com.push_back("mt_elastic and elastic_flg.");
    err_com.push_back("Please check the input file.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  mt_inelastic  = numeric_string_cast<Integer>(input_data[0]);
  bin_no        = numeric_string_cast<Integer>(input_data[1]);
  if( bin_no == 0 )
  {
    bin_no = 16;
  }

  mt_elastic    = numeric_string_cast<Integer>(input_data[2]);
  elastic_flg   = numeric_string_cast<Integer>(input_data[3]);
  if( i_max > 4 )
  {
    atom_no_th = numeric_string_cast<Integer>(input_data[4]);
  }
  if( i_max > 5 )
  {
    ene_max_th = numeric_string_cast<Real>(input_data[5]);
  }
  if( i_max > 6 )
  {
    opt_weight = numeric_string_cast<Integer>(input_data[6]);
  }

  line_data.clear();
  clr_obj.clear_vec_array1_str(input_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void AcerInputReader::read_dosimetry_data(ifstream& fin)
{
  string line_data;
  vector<string> input_data;

  //Card 10
  getline(fin, line_data);
  input_data = rn_obj.read_line_without_slash(line_data);

  int i_max = static_cast<int>(input_data.size());
  if( i_max < 1 )
  {
    string class_name = "AcerInputReader";
    string func_name  = "read_dosimetry_data(ifstream& fin)";

    ostringstream oss;
    oss << input_data.size();
    string str_data01 = "Input file name = " + input_acer;
    string str_data02 = "Data no         = " + oss.str();
    string str_data03 = "Input data      = " + line_data;

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("The data number of card 10 is less than 1.");
    err_com.push_back("In card 10, 1 integer data is required, i.e., mat.");
    err_com.push_back("Please check the input file.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  mat = numeric_string_cast<Integer>(input_data[0]);
  if( i_max > 1 )
  {
    temp = numeric_string_cast<Real>(input_data[1]);
  }

  line_data.clear();
  clr_obj.clear_vec_array1_str(input_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void AcerInputReader::read_photo_atomic_nuclear_data(ifstream& fin)
{
  string line_data;
  vector<string> input_data;

  //Card 11
  getline(fin, line_data);
  input_data = rn_obj.read_line_without_slash(line_data);

  int i_max = static_cast<int>(input_data.size());
  if( i_max < 1 )
  {
    string class_name = "AcerInputReader";
    string func_name  = "read_photo_atomic_nuclear_data(ifstream& fin)";

    ostringstream oss;
    oss << input_data.size();
    string str_data01 = "Input file name = " + input_acer;
    string str_data02 = "Data no         = " + oss.str();
    string str_data03 = "Input data      = " + line_data;

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("The data number of card 11 is less than 1.");
    err_com.push_back("In card 11, 1 integer data is required, i.e., mat.");
    err_com.push_back("Please check the input file.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  mat = numeric_string_cast<Integer>(input_data[0]);

  line_data.clear();
  clr_obj.clear_vec_array1_str(input_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void AcerInputReader::clear()
{
  input_acer.clear();

  endf_name.clear();
  pendf_name.clear();
  gendf_name.clear();
  ace_name.clear();
  mcnp_dir.clear();

  mcnpx_mode_flg = mcnpx_mode_flg_def;
  opt_run        = 0;
  opt_print      = opt_print_def;
  opt_out_type   = 0;
  zi_awr_pair_no = zi_awr_pair_no_def;
  suffix_za_id   = suffix_za_id_def;

  discriptive_data.clear();

  zi_vec.clear();
  awr_vec.clear();

  mat  = 0;
  temp = temp_def;

  new_cummulative_angle_distr_flg = new_cummulative_angle_distr_flg_def;
  detailed_photon_flg             = detailed_photon_flg_def;

  thinning_ene.clear();
  thinning_ene.resize(thinning_ene_no);
  for(int i=0; i<thinning_ene_no; i++)
  {
    thinning_ene[i] = 0.0;
  }

  thermal_za_id_name.clear();
  thermal_za_id_name = "za";

  mod_za.clear();
  mod_za.resize(mod_za_no);
  for(int i=0; i<mod_za_no; i++)
  {
    mod_za[i] = mod_za_def;
  }

  mt_inelastic  = 0;
  bin_no        = 0;
  mt_elastic    = 0;
  elastic_flg   = 0;
  atom_no_th    = atom_no_th_def;
  opt_weight    = opt_weight_def;
  ene_max_th    = ene_max_th_def;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

string          AcerInputReader::get_input_acer()
{
  return input_acer;
}

string          AcerInputReader::get_endf_name()
{
  return endf_name;
}

string          AcerInputReader::get_pendf_name()
{
  return pendf_name;
}

string          AcerInputReader::get_gendf_name()
{
  return gendf_name;
}

string          AcerInputReader::get_ace_name()
{
  return ace_name;
}

string          AcerInputReader::get_mcnp_dir()
{
  return mcnp_dir;
}

Integer         AcerInputReader::get_mcnpx_mode_flg()
{
  return mcnpx_mode_flg;
}

Integer         AcerInputReader::get_opt_run()
{
  return opt_run;
}

Integer         AcerInputReader::get_opt_print()
{
  return opt_print;
}

Integer         AcerInputReader::get_opt_out_type()
{
  return opt_out_type;
}

Integer         AcerInputReader::get_zi_awr_pair_no()
{
  return zi_awr_pair_no;
}

Real            AcerInputReader::get_suffix_za_id()
{
  return suffix_za_id;
}

string          AcerInputReader::get_discriptive_data()
{
  return discriptive_data;
}

vector<Integer> AcerInputReader::get_zi_vec()
{
  return zi_vec;
}

vector<Real>    AcerInputReader::get_awr_vec()
{
  return awr_vec;
}

Integer         AcerInputReader::get_mat()
{
  return mat;
}

Real            AcerInputReader::get_temp()
{
  return temp;
}

Integer         AcerInputReader::get_new_cummulative_angle_distr_flg()
{
  return new_cummulative_angle_distr_flg;
}

Integer         AcerInputReader::get_detailed_photon_flg()
{
  return detailed_photon_flg;
}

vector<Real>    AcerInputReader::get_thinning_ene()
{
  return thinning_ene;
}

string          AcerInputReader::get_thermal_za_id_name()
{
  return thermal_za_id_name;
}

vector<Integer> AcerInputReader::get_mod_za()
{
  return mod_za;
}

Integer         AcerInputReader::get_mt_inelastic()
{
  return mt_inelastic;
}

Integer         AcerInputReader::get_bin_no()
{
  return bin_no;
}

Integer         AcerInputReader::get_mt_elastic()
{
  return mt_elastic;
}

Integer         AcerInputReader::get_elastic_flg()
{
  return elastic_flg;
}

Integer         AcerInputReader::get_atom_no_th()
{
  return atom_no_th;
}

Integer         AcerInputReader::get_opt_weight()
{
  return opt_weight;
}

Real            AcerInputReader::get_ene_max_th()
{
  return ene_max_th;
}


