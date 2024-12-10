#include "FrendyUtils/Endf6ModifierInputReader.hpp"

using namespace frendy;

// [ Input information ]
// remove  MF  MF-no  MT  MT-no  original-ENDF  output-ENDF
// change  MF  MF-no  MT  MT-no  original-ENDF  additional-ENDF  output-ENDF
// add     MF  MF-no  MT  MT-no  original-ENDF  additional-ENDF  output-ENDF
// "exchange" and "replace" commands are also available instead of "change" command.

const int Endf6ModifierInputReader::remove_data_mode;
const int Endf6ModifierInputReader::change_data_mode;
const int Endf6ModifierInputReader::add_data_mode;
const int Endf6ModifierInputReader::linearize_data_mode;
const int Endf6ModifierInputReader::mf_mode;
const int Endf6ModifierInputReader::mt_mode;
const int Endf6ModifierInputReader::mf_mt_mode;

const int Endf6ModifierInputReader::remove_mf_mode; //remove_data_mode + 100
const int Endf6ModifierInputReader::change_mf_mode;
const int Endf6ModifierInputReader::add_mf_mode;
const int Endf6ModifierInputReader::linearize_mf_mode;
const int Endf6ModifierInputReader::remove_mt_mode; //remove_data_mode + 200
const int Endf6ModifierInputReader::change_mt_mode;
const int Endf6ModifierInputReader::add_mt_mode;
const int Endf6ModifierInputReader::linearize_mt_mode;
const int Endf6ModifierInputReader::remove_mf_mt_mode; //remove_data_mode + 300
const int Endf6ModifierInputReader::change_mf_mt_mode;
const int Endf6ModifierInputReader::add_mf_mt_mode;
const int Endf6ModifierInputReader::linearize_mf_mt_mode;

const string Endf6ModifierInputReader::remove_flg_str    = "remove";
const string Endf6ModifierInputReader::change_flg_str    = "change";
const string Endf6ModifierInputReader::exchange_flg_str  = "exchange";
const string Endf6ModifierInputReader::replace_flg_str   = "replace";
const string Endf6ModifierInputReader::add_flg_str       = "add";
const string Endf6ModifierInputReader::linearize_flg_str = "linearize";

const string Endf6ModifierInputReader::mf_flg_str     = "mf";
const string Endf6ModifierInputReader::mt_flg_str     = "mt";

Endf6ModifierInputReader::Endf6ModifierInputReader(void)
{
  clear();
}

Endf6ModifierInputReader::~Endf6ModifierInputReader(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6ModifierInputReader::clear()
{
  linearize_tolerance = -1.0;

  run_flg.clear();
  clr_obj.clear_vec_array2_int(mf_no);
  clr_obj.clear_vec_array2_int(mt_no);
  clr_obj.clear_vec_array1_str(endf_name_ori);
  clr_obj.clear_vec_array1_str(endf_name_add);
  clr_obj.clear_vec_array1_str(endf_name_mod);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6ModifierInputReader::read_input_data_from_input_file(string file_name)
{
  FileCommentRemover file_handling_obj;
  vector<vector<string> > input_data = file_handling_obj.remove_comment_and_devide_text_data(file_name);

  read_input_data(input_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6ModifierInputReader::read_input_data(vector<vector<string> >& input_data)
{
  int run_mode_flg    = -1;
  int target_mode_flg = -1;

  check_tolerance(input_data);

  int ele_no = 0;
  int i_max  = static_cast<int>(input_data.size());
  for(int i=0; i<i_max; i++)
  {
    //Read running mode (remove, change, add)
    string input_str = input_data[i][0];
    transform(input_str.begin(), input_str.end(), input_str.begin(), ::tolower);
    replace(input_str.begin(), input_str.end(),  '-', '_');
    if( strcmp(input_str.c_str(), remove_flg_str.c_str()) == 0 )
    {
      run_mode_flg = remove_data_mode;
    }
    else if( strcmp(input_str.c_str(), change_flg_str.c_str())   == 0 ||
             strcmp(input_str.c_str(), exchange_flg_str.c_str()) == 0 ||
             strcmp(input_str.c_str(), replace_flg_str.c_str())  == 0 )
    {
      run_mode_flg = change_data_mode;
    }
    else if( strcmp(input_str.c_str(), add_flg_str.c_str()) == 0 )
    {
      run_mode_flg = add_data_mode;
    }
    else if( strcmp(input_str.c_str(), linearize_flg_str.c_str()) == 0 )
    {
      run_mode_flg = linearize_data_mode;
    }
    else if( i==0 || static_cast<int>(input_data[i][0].size()) == 0 ) //include calculation mode at input_data[0][0]
    {
      continue;
    }
    else
    {
      string class_name = "Endf6ModifierInputReader";
      string func_name  = "read_input_data(vector<vector<string> >& input_data)";
      vector<string> err_com;
      string str_data01 = "Running mode : " + input_str;
      string str_data02 = "  " + remove_flg_str;
      string str_data03 = "  " + change_flg_str + ", " + exchange_flg_str + ", " + replace_flg_str;
      string str_data04 = "  " + add_flg_str;
      string str_data05 = "  " + linearize_flg_str;
      err_com.push_back(str_data01);
      err_com.push_back("");
      err_com.push_back("This running mode is not supported in this program.");
      err_com.push_back("The available running mode is as follows:");
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back(str_data04);
      err_com.push_back(str_data05);
      err_com.push_back("");
      err_com.push_back("Please check the input file.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    if( i_max < i+2 )
    {
      string class_name = "Endf6ModifierInputReader";
      string func_name  = "read_input_data(vector<vector<string> >& input_data)";
      vector<string> err_com;
      err_com.push_back("The last input data which is read by this program.");
      err_com.push_back(input_data[i_max-1][0]);
      err_com.push_back("");
      err_com.push_back("The number of input data is not correct.");
      err_com.push_back("Please check the input file.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    //Read target MF/MT number
    vector<Integer> mf_no_inp, mt_no_inp;
    mf_no_inp.clear();
    mt_no_inp.clear();

    string target_str = input_data[i+1][0];
    transform(target_str.begin(), target_str.end(), target_str.begin(), ::tolower);
    if( strcmp(target_str.c_str(), mf_flg_str.c_str()) == 0 )
    {
      target_mode_flg = mf_mode;
      mf_no_inp = str_conv_obj.get_int_data_list(input_data[i+2]);

      if( i_max > i+4 )
      {
        target_str = input_data[i+3][0];
        transform(target_str.begin(), target_str.end(), target_str.begin(), ::tolower);
        if( strcmp(target_str.c_str(), mt_flg_str.c_str()) == 0 )
        {
          target_mode_flg = mf_mt_mode;

          mt_no_inp = str_conv_obj.get_int_data_list(input_data[i+4]);
        }
      }
    }
    else if( strcmp(target_str.c_str(), mt_flg_str.c_str()) == 0 )
    {
      target_mode_flg = mt_mode;

      mt_no_inp = str_conv_obj.get_int_data_list(input_data[i+2]);

      if( i_max > i+4 )
      {
        target_str = input_data[i+3][0];
        transform(target_str.begin(), target_str.end(), target_str.begin(), ::tolower);
        if( strcmp(target_str.c_str(), mf_flg_str.c_str()) == 0 )
        {
          target_mode_flg = mf_mt_mode;

          mf_no_inp = str_conv_obj.get_int_data_list(input_data[i+4]);
        }
      }
    }
    else
    {
      string class_name = "Endf6ModifierInputReader";
      string func_name  = "read_input_data(vector<vector<string> >& input_data)";
      vector<string> err_com;
      err_com.push_back("The last input data which is read by this program.");
      err_com.push_back(input_data[i+1][0]);
      err_com.push_back("");
      err_com.push_back("Please set MF or MT and its number.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    if( target_mode_flg == mf_mode || target_mode_flg == mt_mode )
    {
      i+=3;
    }
    else if( target_mode_flg == mf_mt_mode )
    {
      i+=5;
    }

    //Read ENDF file name (original, add, and modified)
    string endf_name_ori_inp = "";
    string endf_name_add_inp = "";
    string endf_name_mod_inp = "";

    if( run_mode_flg == remove_data_mode || run_mode_flg == linearize_data_mode )
    {
      if( i_max < i+1 )
      {
        string class_name = "Endf6ModifierInputReader";
        string func_name  = "read_input_data(vector<vector<string> >& input_data)";
        vector<string> err_com;
        err_com.push_back("The last input data which is read by this program.");
        err_com.push_back(input_data[i_max-1][0]);
        err_com.push_back("");
        err_com.push_back("Please set original and added nuclear data file name.");

        err_obj.output_runtime_error(class_name, func_name, err_com);
      }

      endf_name_ori_inp = input_data[i][0];
      endf_name_mod_inp = input_data[i+1][0];
      i+=1;
    }
    else //if( run_mode_flg == change_data_mode || run_mode_flg == add_data_mode )
    {
      if( i_max < i+2 )
      {
        string class_name = "Endf6ModifierInputReader";
        string func_name  = "read_input_data(vector<vector<string> >& input_data)";
        vector<string> err_com;
        err_com.push_back("The last input data which is read by this program.");
        err_com.push_back(input_data[i_max-1][0]);
        err_com.push_back("");
        err_com.push_back("Please set original, added and modified nuclear data file name.");

        err_obj.output_runtime_error(class_name, func_name, err_com);
      }

      endf_name_ori_inp = input_data[i][0];
      endf_name_add_inp = input_data[i+1][0];
      endf_name_mod_inp = input_data[i+2][0];
      i+=2;
    }

    run_flg.push_back(run_mode_flg*100 + target_mode_flg);
    mf_no.push_back(mf_no_inp);
    mt_no.push_back(mt_no_inp);
    endf_name_ori.push_back(endf_name_ori_inp);
    endf_name_add.push_back(endf_name_add_inp);
    endf_name_mod.push_back(endf_name_mod_inp);

    output_input_information(run_mode_flg, target_mode_flg, mf_no_inp, mt_no_inp,
                             endf_name_ori_inp, endf_name_add_inp, endf_name_mod_inp, ele_no);
    ele_no++;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6ModifierInputReader::check_tolerance(vector<vector<string> >& input_data)
{
  vector<Real> err_vec;
  err_vec.clear();

  vector<vector<string> > input_data_mod;

  int i_max  = static_cast<int>(input_data.size());
  for(int i=0; i<i_max; i++)
  {
    //Read running mode (remove, change, add)
    string input_str = input_data[i][0];
    transform(input_str.begin(), input_str.end(), input_str.begin(), ::tolower);
    replace(input_str.begin(), input_str.end(),  '-', '_');
    if( input_str == "error" || input_str == "tolerance" )
    {
      i++;
      if( static_cast<int>(input_data[i].size()) != 1 )
      {
        string class_name = "Endf6ModifierInputReader";
        string func_name  = "check_tolerance(vector<vector<string> >& input_data)";

        if( static_cast<int>(input_data[i].size()) > 1 )
        {
          frendy_utils.error_input_data_size_is_larger_than_one(class_name, func_name, input_data[i]);
        }
        else if( static_cast<int>(input_data[i].size()) == 0 )
        {
          frendy_utils.error_input_data_size_is_zero(class_name, func_name, input_data[i]);
        }
      }

      str_obj.string_check(input_data[i][0]);
      linearize_tolerance = numeric_string_cast<Real>(input_data[i][0]);
      err_vec.push_back(linearize_tolerance);
    }
    else
    {
      input_data_mod.push_back(input_data[i]);
    }
  }
  input_data = input_data_mod;

  int j_max = static_cast<int>(err_vec.size());
  if( j_max > 1 )
  {
    string class_name = "Endf6ModifierInputReader";
    string func_name  = "check_tolerance(vector<vector<string> >& input_data)";


    vector<string> err_com;
    err_com.push_back("Many error or tolerance data are found in this input file.");
    err_com.push_back("The final value is only available in this program.");
    err_com.push_back("");
    err_com.push_back("  The error and torelance data in the input file is as follows:");
    for(int j=0; j<j_max; j++)
    {
      ostringstream oss01, oss02, oss03;
      oss01 << j+1;
      oss02 << j_max;
      oss03 << setw(8) << std::showpoint << std::scientific << err_vec[j];
      string str_data01 = "    " + oss01.str() + " / " + oss02.str() + " : " + oss03.str();
      err_com.push_back(str_data01);
    }

    err_com.push_back("");
    ostringstream oss;
    oss << setw(8) << std::showpoint << std::scientific << linearize_tolerance;
    string str_data02 = "  The torelance value for linearization : " + oss.str();
    err_com.push_back(str_data02);

    err_obj.output_caution(class_name, func_name, err_com);
  }

  ostringstream oss;
  oss << setw(8) << std::showpoint << std::scientific << linearize_tolerance;
  cout << "The torelance value for linearization : " << oss.str();
  cout << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6ModifierInputReader::output_input_information 
                                 (int run_mode_flg, int target_mode_flg,
                                  vector<int> mf_no_inp, vector<int> mt_no_inp,
                                  string endf_name_ori_inp, string endf_name_add_inp, string endf_name_mod_inp,
                                  int ele_no)
{
  cout << "Input case number : " << ele_no+1 << endl;
  if( run_mode_flg == remove_data_mode )
  {
    cout << "  Running mode : remove" << endl;
  }
  else if( run_mode_flg == change_data_mode )
  {
    cout << "  Running mode : change" << endl;
  }
  else if( run_mode_flg == add_data_mode )
  {
    cout << "  Running mode : add" << endl;
  }
  else if( run_mode_flg == linearize_data_mode )
  {
    cout << "  Running mode : linearize" << endl;
  }

  if( target_mode_flg == mf_mode )
  {
    int i_max = static_cast<int>(mf_no_inp.size());
    cout << "  Target MF" << endl;
    cout << "    Number of MF data : " << i_max << endl;
    for(int i=0; i<i_max; i++)
    {
      cout << "      " << mf_no_inp[i] << endl;
    }
  }
  else if( target_mode_flg == mt_mode )
  {
    int i_max = static_cast<int>(mt_no_inp.size());
    cout << "  Target MT" << endl;
    cout << "    Number of MT data : " << i_max << endl;
    for(int i=0; i<i_max; i++)
    {
      cout << "      " << mt_no_inp[i] << endl;
    }
  }
  if( target_mode_flg == mf_mt_mode )
  {
    int i_max = static_cast<int>(mf_no_inp.size());
    int j_max = static_cast<int>(mt_no_inp.size());

    cout << "  Target MF/MT" << endl;
    cout << "    Number of MF data : " << i_max << endl;
    for(int i=0; i<i_max; i++)
    {
      cout << "      " << mf_no_inp[i] << endl;
    }
    cout << "    Number of MT data : " << j_max << endl;
    for(int j=0; j<j_max; j++)
    {
      cout << "      " << mt_no_inp[j] << endl;
    }
  }

  cout << "  Original ENDF file name : " << endf_name_ori_inp << endl;
  if( run_mode_flg == change_data_mode )
  {
    cout << "  Changed  ENDF file name : " << endf_name_add_inp << endl;
  }
  else if( run_mode_flg == add_data_mode )
  {
    cout << "  Added    ENDF file name : " << endf_name_add_inp << endl;
  }
  cout << "  Modified ENDF file name : " << endf_name_mod_inp << endl;

  cout << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void Endf6ModifierInputReader::set_run_flg(vector<int> int_vec)
{
  run_flg = int_vec;
}

void Endf6ModifierInputReader::set_mf_no(vector<vector<Integer> > int_vec)
{
  mf_no = int_vec;
}

void Endf6ModifierInputReader::set_mt_no(vector<vector<Integer> > int_vec)
{
  mt_no = int_vec;
}


void Endf6ModifierInputReader::set_endf_name_ori(vector<string> str_vec)
{
  endf_name_ori = str_vec;
}

void Endf6ModifierInputReader::set_endf_name_add(vector<string> str_vec)
{
  endf_name_add = str_vec;
}

void Endf6ModifierInputReader::set_endf_name_mod(vector<string> str_vec)
{
  endf_name_mod = str_vec;
}

void Endf6ModifierInputReader::set_linearize_tolerance(Real real_val)
{
  linearize_tolerance = real_val;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Getter
vector<int>     Endf6ModifierInputReader::get_run_flg()
{
  return run_flg;
}

vector<vector<Integer> > Endf6ModifierInputReader::get_mf_no()
{
  return mf_no;
}

vector<vector<Integer> > Endf6ModifierInputReader::get_mt_no()
{
  return mt_no;
}

vector<string>  Endf6ModifierInputReader::get_endf_name_ori()
{
  return endf_name_ori;
}

vector<string>  Endf6ModifierInputReader::get_endf_name_add()
{
  return endf_name_add;
}

vector<string>  Endf6ModifierInputReader::get_endf_name_mod()
{
  return endf_name_mod;
}

Real            Endf6ModifierInputReader::get_linearize_tolerance()
{
  return linearize_tolerance;
}

