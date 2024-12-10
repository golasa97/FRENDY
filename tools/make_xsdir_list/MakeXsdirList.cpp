#include "ContinuousEnergyXSUtils/OtherUtils/AceDataCollector.hpp"

using namespace frendy;

//   Explanation of input file for this program
//     ACE mode (1 for fast neutron data, 2 for thermal scattering law data, 3 for dosimetry)
//     ACE file name
//     XSDIR file name
//     relative path of ACE file 
//     suffix
//     calculation mode (collect or individual) *optional (default: collect)
//

//  Sample input file for this program
//    1
//    j40a00f
//    xsdir.j40a00f
//    ace_fast
//    50c
//    individual  //collect or individual
//
//    2
//    j40a00t
//    xsdir.j40a00t
//    ace_thermal
//    20t
//    individual  //collect or individual
//
//    3
//    j40a00d
//    xsdir.j40a00d
//    ace_dosi
//    70y
//    individual  //collect or individual

void read_input_file(string inp_name, int& calc_mode, int& ace_mode,
                     string& ace_name, string& xsdir_name, string& dir_name, string& suffix_name)
{
  ifstream fin;
  fin.open(inp_name.c_str());

  if( !fin )
  {
    string class_name = "main";
    string func_name  = "read_input_file";
    string str_data   = "Input file name : " + inp_name;

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("Input file can not open.");
    err_com.push_back("Please check the inut file.");

    ErrorManager err_obj;
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  cout << "Input file name        : " << inp_name << endl;

  fin >> ace_mode;
  cout << "Ace file mode          : " << ace_mode << endl;
  cout << "(1: fast, 2: thermal scattering law, 3: dosimetry)" << endl;

  fin >> ace_name;
  cout << "Output ace file name   : " << ace_name << endl;

  fin >> xsdir_name;
  cout << "Output XSDIR file name : " << xsdir_name << endl;

  fin >> dir_name;
  cout << "Ace file directory     : " << dir_name << endl;

  fin >> suffix_name;
  cout << "Modified suffix ID     : " << suffix_name << endl;

  calc_mode = 1; //collect_mode
  if( !fin.eof() )
  {
    string calc_mode_str;
    fin >> calc_mode_str;
    transform(calc_mode_str.begin(), calc_mode_str.end(), calc_mode_str.begin(), ::tolower);

    if( calc_mode_str == "1" ||
        calc_mode_str == "collect" || calc_mode_str == "collect_mode" )
    {
      cout << "Calculation mode       : collect_mode" << endl;
      calc_mode = 1;
    }
    else if( calc_mode_str == "2" ||
        calc_mode_str == "individual" || calc_mode_str == "individual_mode" )
    {
      cout << "Calculation mode       : individual_mode" << endl;
      calc_mode = 2;
    }
  }

  cout << endl;
  cout << "Read input file is completed." << endl;
  cout << "Running AceDataCollector class." << endl;
  cout << endl;

  fin.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
  if( argc <= 1 )
  {
    throw runtime_error("Please set input file name.");
  }

  string input_file_name = argv[1];

  //Read input file
  int    calc_mode, ace_file_mode;
  string ace_file_name, xsdir_name, ace_dir_name, mod_suffix;
  read_input_file(input_file_name, calc_mode, ace_file_mode,
                  ace_file_name, xsdir_name, ace_dir_name, mod_suffix);


  //Collect ace file to run the MCNP code
  AceDataCollector collect_obj;
  collect_obj.set_output_ace_file_mode(ace_file_mode);
  collect_obj.set_output_ace_file_name(ace_file_name);
  collect_obj.set_output_xsdir_name(xsdir_name);
  collect_obj.set_ace_dir_name(ace_dir_name);
  collect_obj.set_mod_suffix_id(mod_suffix);
  collect_obj.set_calc_mode(calc_mode);
 
  collect_obj.collect_ace_file();

  return 0;
}

