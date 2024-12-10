#include "NuclearDataProcessor/NuclearDataProcessorCommonUtils.hpp"

using namespace frendy;

//constructor
NuclearDataProcessorCommonUtils::NuclearDataProcessorCommonUtils(void)
{
}

//destructor
NuclearDataProcessorCommonUtils::~NuclearDataProcessorCommonUtils(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataProcessorCommonUtils::output_frendy_start()
{
  cout << endl;
  cout << "/////////////////////////////////////////////////////////////////////////////////////////" << endl;
  cout << "//                                                                                     //" << endl;
  cout << "//  //////////  ///////////    //////////  /////      ///  /////////    ///       ///  //" << endl;
  cout << "//  ///         ///      ///   ///         //////     ///  ///     ///   ///     ///   //" << endl;
  cout << "//  ///         ///      ///   ///         /// ///    ///  ///      ///   ///   ///    //" << endl;
  cout << "//  //////////  ///////////    //////////  ///  ///   ///  ///       ///   ///////     //" << endl;
  cout << "//  ///         ///    ///     ///         ///   ///  ///  ///       ///     ///       //" << endl;
  cout << "//  ///         ///     ///    ///         ///    /// ///  ///      ///      ///       //" << endl;
  cout << "//  ///         ///      ///   ///         ///     //////  ///     ///       ///       //" << endl;
  cout << "//  ///         ///       ///  //////////  ///      /////  /////////         ///       //" << endl;
  cout << "//                                                                                     //" << endl;
  cout << "/////////////////////////////////////////////////////////////////////////////////////////" << endl;
  cout << endl;
  time_obj.output_current_time();
  cout << "  Version : " << "2.05.000 (2024/Oct/30)" << endl;
  cout << "  Developed by Japan Atomic Energy Agency" << endl;
  cout << endl;

#ifdef A680_MODE
  cout << "  Calculation algorithm for complex error function : Algorithm 680" << endl;
#elif defined PADE_MODE
  cout << "  Calculation algorithm for complex error function : Pade approximation" << endl;
#endif

#ifdef NJOY_MODE
  cout << "  Calculation algorithm which is used in NJOY is used to process the nuclear data." << endl;
#endif

#ifdef NO_AMUR_MODE
  cout << "  AMUR module is not implemented in this execution file." << endl;
  cout << "  This mode cannot treat the R-matrix limited formula (MF=2/MT=151/LRF=7)." << endl;
#endif

  cout << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataProcessorCommonUtils::output_frendy_end(string input_name)
{
  cout << endl;
  cout << "Finish all calculation." << endl;
  time_obj.output_current_time();
  cout << "/////////////////////////////////////////////////////////////////////////////////////////" << endl;
  cout << endl;
  cout << "FRENDY CALCULATION STATUS: NORMAL TERMINATION ( input: " << input_name << " )" << endl;
  cout << endl;
}
 
////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataProcessorCommonUtils::output_frendy_input_file_information(string input_file_name)
{
  cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << endl;
  cout << "  === Input file information (original) ===" << endl;
  cout << "    Input file name : " << input_file_name << endl;
  cout << endl;

  ifstream fin;
  fin.open(input_file_name.c_str());
  if( !fin )
  {
    string class_name = "NuclearDataProcessorCommonUtils";
    string func_name  = "output_frendy_input_file_information(string input_file_name)";

    string str_data   = "Input file name of NJOY : " + input_file_name;
    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("Input file can not open.");
    err_com.push_back("Please check the input file name.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  int    blank_no  = 0;
  string line_data;
  while( !fin.eof() )
  {
    line_data.clear();
    getline(fin, line_data);
    cout << "        " << line_data << endl;

    if( line_data.size() > 0 )
    {
      blank_no = 0;
    }
    else
    {
      blank_no++;

      if( blank_no > 100000000 )
      {
        string class_name = "NuclearDataProcessorCommonUtils";
        string func_name  = "output_frendy_input_file_information(string input_file_name)";

        string str_data   = "  Input file name of NJOY : " + input_file_name;

        vector<string> err_com;
        err_com.push_back("A huge number of blank line data is found.");
        err_com.push_back("The NJOY input file name may not be the directory name.");
        err_com.push_back("Please check the NJOY input file name is collect or not.");
        err_com.push_back("");
        err_com.push_back(str_data);
        err_com.push_back("");
        err_com.push_back("FRENDY recognizes that after // is comment line.");
        err_com.push_back("Please check that the NJOY input file name contains // or not.");

        err_obj.output_runtime_error(class_name, func_name, err_com);
      }
    }
  }
  fin.close();

  cout << endl;
  cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << endl;
}
 
////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataProcessorCommonUtils::output_frendy_input_file_information_without_comment
                                        (string input_file_name)
{
  cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << endl;
  cout << "  === Input file information (without comment) ===" << endl;
  cout << "    Input file name : " << input_file_name << endl;
  cout << endl;

  vector<string> inp_data = file_obj.remove_comment(input_file_name);

  int i_max = static_cast<int>(inp_data.size());
  for(int i=0; i<i_max; i++)
  {
    cout << "        " << inp_data[i] << endl;
  }

  cout << endl;
  cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << endl;
}
 
////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataProcessorCommonUtils::change_pendf_name(string input_file_name)
{
  change_pendf_name(input_file_name, 0);
}
 
////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataProcessorCommonUtils::change_pendf_name(string input_file_name, int line_no)
{
  cout << "********************************** change PENDF tape name **********************************";
  cout << endl << endl;
  time_obj.output_current_time();

  boost::timer::cpu_timer timer_total;

  ModerInputReader moder_obj;
  moder_obj.read_input(input_file_name, line_no);

  Integer data_format_no = moder_obj.get_data_format_no();
  if( data_format_no == 2 || data_format_no == 3 )
  {
    string class_name = "NuclearDataProcessorCommonUtils";
    string func_name  = "skip_moder(string input_file_name)";

    ostringstream oss;
    oss << data_format_no;

    string str_data = "Data format type (nin) : " + oss.str();

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("The available data format is only 1 (ENDF or PENDF).");
    err_com.push_back("This data file type cannot be treated in this program.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  string           pendf_in  = moder_obj.get_pendf_input_name();
  string           pendf_out = moder_obj.get_pendf_output_name();
  string           tape_id   = moder_obj.get_tape_id();
  vector<string>   tape_in   = moder_obj.get_tape_name();
  vector<Integer>  mat       = moder_obj.get_mat();

  cout << "  Original PENDF name : " << pendf_in  << endl;
  cout << "  Modified PENDF name : " << pendf_out << endl;

  if( static_cast<int>(tape_in.size()) > 0 )
  {
    cout << "  Tape id for output  : " << tape_id << endl;

    int i_max = static_cast<int>(tape_in.size());
    for(int i=0; i<i_max; i++)
    {
      cout << "    Original TAPE name (" << i+1 << " / " << i_max << ") : " << tape_in[i] << endl;
      cout << "    Material No.       (" << i+1 << " / " << i_max << ") : " << mat[i] << endl;
    }
  }
  cout << endl;

  cout << "Total calculation time : " << timer_total.elapsed().wall * 1.0E-9 << "[s]" << endl;
  cout << endl;
  cout << "********************************************************************************************";
  cout << endl << endl;

  vector<string> text;
  EndfFileWriter efw_obj;

  int    tape_in_no = static_cast<int>(tape_in.size());
  string tape_end   = efw_obj.write_tape_end();
  string file_end   = efw_obj.write_file_end();

  int blank_no = 0;
  if( tape_in_no == 0 )
  {
    ifstream fin;
    fin.open(pendf_in.c_str());
    if( !fin )
    {
      string class_name = "NuclearDataProcessorCommonUtils";
      string func_name  = "skip_moder(string input_file_name)";

      string str_data = "Input PENDF file name : " + pendf_in;

      vector<string> err_com;
      err_com.push_back(str_data);
      err_com.push_back("There is no PENDF input file.");
      err_com.push_back("Please check the PENDF input file name.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    string line_data;
    while(!fin.eof())
    {
      getline(fin, line_data);
      text.push_back(line_data);

      if( line_data.size() > 0 )
      {
        blank_no = 0;
      }
      else
      {
        blank_no++;

        if( blank_no > 100000000 )
        {
          string class_name = "NuclearDataProcessorCommonUtils";
          string func_name  = "skip_moder(string input_file_name)";

          string str_data = "Input PENDF file name : " + pendf_in;

          vector<string> err_com;
          err_com.push_back("A huge number of blank line data is found.");
          err_com.push_back("The PENDF file name may not be the directory name.");
          err_com.push_back("Please check the PENDF file name is collect or not.");
          err_com.push_back("");
          err_com.push_back(str_data);
          err_com.push_back("");
          err_com.push_back("FRENDY recognizes that after // is comment line.");
          err_com.push_back("Please check that the PENDF file name contains // or not.");

          err_obj.output_runtime_error(class_name, func_name, err_com);
        }
      }
    }
  }
  else
  {
    text.clear();
    //Write TAPE ID
    efw_obj.set_mat(1);
    efw_obj.set_mf_mt(0, 0);
    text.push_back(efw_obj.write_text(tape_id));

    for(int i=0; i<tape_in_no; i++)
    {
      EndfTapeDivider divide_obj;
      divide_obj.set_file_name(tape_in[i]);

      vector<string> text_tmp = divide_obj.get_data(mat[i]);
      int j_max = static_cast<int>(text_tmp.size());

      //Write ENDF data
      for(int j=0; j<j_max; j++)
      {
        if( static_cast<int>(text_tmp[j].length()) > 66 &&
            text_tmp[j].find(file_end.c_str(),0) == string::npos &&
            text_tmp[j].find(tape_end.c_str(),0) == string::npos )
        {
          text.push_back(text_tmp[j]);
        }
      }
      vector<string>().swap(text_tmp);

      text.push_back(file_end);
    }
  }

  ofstream fout;
  fout.open(pendf_out.c_str());
  if( !fout )
  {
    string class_name = "NuclearDataProcessorCommonUtils";
    string func_name  = "skip_moder(string input_file_name)";

    vector<string> err_com;
    err_com.push_back("Output PENDF file can not be open.");
    err_com.push_back("Please check the file name, directory name or access authority.");
    string str_data = "  Output PENDF file name : " + pendf_out;
    err_com.push_back(str_data);
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  int i_max = static_cast<int>(text.size());
  while( static_cast<int>(text[i_max-1].size()) == 0 )
  {
    i_max--;
  }

  for(int i=0; i<i_max; i++)
  {
    fout << text[i] << endl;
  }

  //Write tape end
  if( static_cast<int>(text[i_max-1].length()) > 66 &&
      text[i_max-1].find(tape_end.c_str(),0) == string::npos )
  {
    fout << tape_end << endl;
  }
}

