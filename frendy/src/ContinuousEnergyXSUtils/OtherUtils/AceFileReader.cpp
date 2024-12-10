#include "ContinuousEnergyXSUtils/OtherUtils/AceFileReader.hpp"

using namespace frendy;

//constructor
AceFileReader::AceFileReader(void)
{
  clear();
}

//destructor
AceFileReader::~AceFileReader(void)
{
  clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

const int AceFileReader::fast_data;
const int AceFileReader::tsl_data;
const int AceFileReader::dosi_data;
const int AceFileReader::pa_data;
const int AceFileReader::pn_data;
const int AceFileReader::proton_data;
const int AceFileReader::deuteron_data;
const int AceFileReader::triton_data;
const int AceFileReader::he_data;
const int AceFileReader::alpha_data;

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceFileReader::clear()
{
  clr_obj.clear_vec_array1_str(text_data);

  file_name.clear();

  data_count        = 0;
  data_count_total  = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

string AceFileReader::get_string_data()
{
  int data_sta = data_count * data_width;

  string str_data_part = text_data[data_count_total].substr(data_sta, data_width);

  data_count++;
  if( data_count >= data_no_each_line )
  {
    data_count = 0;

    data_count_total++;
    if( data_count_total > line_no )
    {
      string class_name = "AceFileReader";
      string func_name  = "get_string_data()";

      ostringstream oss01;
      oss01 << line_no;
      string str_data01 = "Number of lines : " + oss01.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back("Number of lines are achieved.");
      err_com.push_back("There is no additional data.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }

  return str_data_part;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Integer AceFileReader::get_int_data()
{
  string str_data_part = get_string_data();

  return numeric_string_cast<int>(str_data_part);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Real AceFileReader::get_real_data()
{
  string str_data_part = get_string_data();

  return numeric_string_cast<Real>(str_data_part);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Real8 AceFileReader::get_real8_data()
{
  string str_data_part = get_string_data();

  return numeric_string_cast<Real8>(str_data_part);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

string AceFileReader::get_line_data()
{
  if( data_count > 0 )
  {
    data_count_total++;
  }
  string line_data = text_data[data_count_total];

  data_count_total++;
  data_count = 0;
  return line_data;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceFileReader::get_int_data(Integer& int_val)
{
  int_val = get_int_data();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceFileReader::get_real_data(Real& real_val)
{
  real_val = get_real_data();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceFileReader::get_real8_data(Real8& real_val)
{
  real_val = get_real8_data();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceFileReader::get_line_data(string& str_data)
{
  str_data = get_line_data();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceFileReader::get_list_data(vector<Integer>& list_vec)
{
  int data_no = static_cast<int>(get_int_data());

  get_list_data_without_data_no(data_no, list_vec);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceFileReader::get_list_data_without_data_no(int data_no, vector<Integer>& list_vec)
{
  list_vec.resize(data_no);
  for(int i=0; i<data_no; i++)
  {
    list_vec[i] = get_int_data();
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceFileReader::get_list_data(vector<Real>& list_vec)
{
  int data_no = static_cast<int>(get_int_data());

  get_list_data_without_data_no(data_no, list_vec);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceFileReader::get_list_data_without_data_no(int data_no, vector<Real>& list_vec)
{
  list_vec.resize(data_no);
  for(int i=0; i<data_no; i++)
  {
    list_vec[i] = get_real_data();
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceFileReader::get_interpolation_data(vector<Integer>& range_vec, vector<Integer>& int_vec)
{
  int data_no = static_cast<int>(get_int_data());

  range_vec.clear();
  int_vec.clear();
  if( data_no == 0 )
  {
    range_vec.resize(1);
    int_vec.resize(1);
    range_vec[0] = max_data_no;
    int_vec[0]   = int_lin_lin;
  }
  else
  {
    get_list_data_without_data_no(data_no, range_vec);
    get_list_data_without_data_no(data_no, int_vec);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceFileReader::get_table_data(vector<Real>& x_vec, vector<Real>& y_vec)
{
  int data_no = static_cast<int>(get_int_data());

  get_list_data_without_data_no(data_no, x_vec);
  get_list_data_without_data_no(data_no, y_vec);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceFileReader::get_table_data(vector<Real>& x_vec, vector<Real>& y_vec, vector<Real>& y_vec_integ)
{
  get_table_data(x_vec, y_vec);

  int data_no = static_cast<int>(x_vec.size());
  get_list_data_without_data_no(data_no, y_vec_integ);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceFileReader::get_table_data(vector<Integer>& range_vec, vector<Integer>& int_vec,
                                   vector<Real>&    x_vec,     vector<Real>&    y_vec)
{
  get_interpolation_data(range_vec, int_vec);
  get_table_data(x_vec, y_vec);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceFileReader::get_table_data(vector<Integer>& range_vec, vector<Integer>& int_vec,
                                   vector<Real>& x_vec, vector<Real>& y_vec, vector<Real>& y_vec_integ)
{
  get_table_data(range_vec, int_vec, x_vec, y_vec);

  int data_no = static_cast<int>(x_vec.size());
  get_list_data_without_data_no(data_no, y_vec_integ);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceFileReader::get_title_data(Integer& mcnpx_mode_flg, Real& aw0, Real& tz,
                                   string& discriptive_data, vector<string>& title_data)
{
  int ace_ver = get_ace_file_version();
  if( ace_ver == 1 )
  {
    get_title_data_legacy_ver(mcnpx_mode_flg, aw0, tz, discriptive_data, title_data);
  }
  else
  {
    get_title_data_new_ver(mcnpx_mode_flg, aw0, tz, discriptive_data, title_data);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceFileReader::get_title_data_legacy_ver(Integer& mcnpx_mode_flg, Real& aw0, Real& tz,
                                              string& discriptive_data, vector<string>& title_data)
{
  int title_no = 3;
  title_data.resize(title_no);

  string space_chk = " ";

  //Line No. 1
  string line_data = get_line_data();

  mcnpx_mode_flg = 1;
  if( line_data.substr(22,1) == space_chk && line_data.substr(21,1) != space_chk )
  {
    mcnpx_mode_flg = 0;
  }
  else if( line_data.substr(25,1) == space_chk && line_data.substr(24,1) != space_chk )
  {
    mcnpx_mode_flg = 1;
  }
  else
  {
    string class_name = "AceFileReader";
    string func_name  = "get_title_data_legacy_ver";
    vector<string> err_com;
    err_com.push_back("======================================================================"); 
    err_com.push_back("");
    err_com.push_back(line_data);
    err_com.push_back("");
    err_com.push_back("======================================================================"); 
    err_com.push_back("This line data is not appropriate for ACE file.");
    err_com.push_back("Please check the data file.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  int data_no = 10;
  if( mcnpx_mode_flg != 0 )
  {
    data_no = 13;
  }
  title_data[0] = line_data.substr(0,data_no);

  int width = 12;
  aw0 = numeric_string_cast<Real>(line_data.substr(data_no, width));
  data_no += width;

  tz  = numeric_string_cast<Real>(line_data.substr(data_no, width));
  data_no += width;

  data_no += 1; //blank

  title_data[1] = line_data.substr(data_no);

  //Line No. 2
  data_no   = 70;
  line_data = get_line_data();
  discriptive_data = line_data.substr(0, data_no);
  title_data[2]    = line_data.substr(data_no);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceFileReader::check_comment_data(vector<string>& comment_end,
                                       Integer& mcnpx_mode_flg, Real& aw0, Real& tz,
                                       string& discriptive_data, vector<string>& title_data)
{
  int title_no = 3;
  vector<string> title_data_comment;
  title_data_comment.resize(title_no);

  string space_chk = " ";

  //Line No. 1
  string line_data = comment_end[0];

  int mcnpx_mode_flg_comment = 1;
  if( line_data.substr(22,1) == space_chk && line_data.substr(21,1) != space_chk )
  {
    mcnpx_mode_flg_comment = 0;
  }
  else if( line_data.substr(25,1) == space_chk && line_data.substr(24,1) != space_chk )
  {
    mcnpx_mode_flg_comment = 1;
  }

  if( mcnpx_mode_flg_comment != mcnpx_mode_flg )
  {
    return;
  }

  int data_no = 10;
  if( mcnpx_mode_flg != 0 )
  {
    data_no = 13;
  }
  title_data_comment[0] = line_data.substr(0,data_no);

  int width = 12;
  string aw0_str = line_data.substr(data_no, width);
         aw0_str = str_obj.trim_space(aw0_str);
  data_no += width;
  string tz_str  = line_data.substr(data_no, width);
         tz_str  = str_obj.trim_space(tz_str);
  data_no += width;
  title_data_comment[1] = line_data.substr(data_no);

  char *ep;
  Real aw0_comment = strtod(aw0_str.c_str(), &ep);
  if( *ep != '\0' )
  {
    return;
  }

  Real tz_comment = strtod(tz_str.c_str(), &ep);
  if( *ep != '\0' )
  {
    return;
  }

  if( fabs(aw0_comment - aw0) > fabs(1.0E-5 * aw0) ||
      fabs(tz_comment  -  tz) > fabs(1.0E-5 *  tz) )
  {
    return;
  }
  
  //Line No. 2
  data_no   = 70;
  line_data = comment_end[1];
  string discriptive_data_comment = line_data.substr(0, data_no);
         title_data_comment[2]    = line_data.substr(data_no);

  std::string::size_type char_pos = title_data_comment[2].find("mat");
  if( char_pos == string::npos )
  {
    return;
  }
  string mat_no_str = title_data_comment[2].substr(char_pos+3);
         mat_no_str = str_obj.trim_space(mat_no_str);
  Real mat_no = strtod(mat_no_str.c_str(), &ep);
  if( *ep != '\0' )
  {
    return;
  }

  if( mat_no < 0.0 || mat_no > 20000.0 )
  {
    return;
  }

  //Change new ACE header format to old ACE header format
  title_data       = title_data_comment;
  discriptive_data = discriptive_data_comment;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceFileReader::get_title_data_new_ver(Integer& mcnpx_mode_flg, Real& aw0, Real& tz,
                                           string& discriptive_data, vector<string>& title_data)
{
  mcnpx_mode_flg = 0;

  int title_no = 5;
  title_data.resize(title_no);

  //Line No. 1
  string line_data = get_line_data();

  
  title_data[3] = line_data.substr(0,10); //version format string

  //Check ACE format version
  int ver_flg = get_ace_format_version(title_data[3]);
  if( ver_flg == 200 )
  {
    title_data[4] = line_data.substr(34);    //evaluation source
    title_data[0] = line_data.substr(10,24); //SZAID
  }
  else //if( ver_flg == 201 )
  {
    title_data[4] = line_data.substr(35);    //evaluation source
    title_data[0] = line_data.substr(10,25); //SZAID
  }

  //Line No. 2
  line_data = get_line_data();

  int width   = 11; //ver_flg == 200
  if( ver_flg >= 201 )
  {
    width = 13;
  }

  int unreadable_flg  = 0;
  int comment_line_no = 0;
  if( ver_flg == 200 )
  {
    string space_chk = " ";
    if( line_data.substr(width*2,1) != space_chk &&
        line_data.substr(width*2,11).find("/") == string::npos )
    {
      unreadable_flg = 1;
    }
    else
    {
      int data_no =  0;
      aw0 = numeric_string_cast<Real>(line_data.substr(data_no, 9));
      if( aw0 + min_value < 10.0 )
      {
        //1.234567 1.2345E-12 12/34/56     X
        data_no += 9;
      }
      else if( aw0 + min_value < 100.0 )
      {
        //12.345678 1.2345E-12 12/34/56     X
        aw0 = numeric_string_cast<Real>(line_data.substr(data_no, 10));
        data_no += 10;
      }
      else
      {
        //123.456789 1.2345E-12 12/34/56     X
        aw0 = numeric_string_cast<Real>(line_data.substr(data_no, width));
        data_no += width;
      }

      tz  = numeric_string_cast<Real>(line_data.substr(data_no, width));
      data_no += width;

      width   = 11;
      title_data[1] = line_data.substr(data_no, width); //processing date
      data_no += width;

      comment_line_no = numeric_string_cast<int>(line_data.substr(data_no, width));
    }
  }
  else //if( ver_flg == 201 )
  {
    char   *ep;
    string aw0_str = line_data.substr(0,width);
           aw0_str = str_obj.trim_space(aw0_str);
    aw0 =  strtod(aw0_str.c_str(), &ep);
    if( *ep != '\0' )
    {
      unreadable_flg = 1;
    }

    string tz_str = line_data.substr(width, width);
           tz_str = str_obj.trim_space(tz_str);
    tz =  strtod(tz_str.c_str(), &ep);
    if( *ep != '\0' )
    {
      unreadable_flg = 1;
    }

    title_data[1] = line_data.substr(width*2, 10); //processing date

    string comment_line_no_str = line_data.substr(width*2+10, 10);
           comment_line_no_str = str_obj.trim_space(comment_line_no_str);
    comment_line_no =  static_cast<int>(round(strtod(comment_line_no_str.c_str(), &ep)));
    if( *ep != '\0' )
    {
      unreadable_flg = 1;
    }
  }

  if( unreadable_flg > 0 )
  {
    string class_name = "AceFileReader";
    string func_name  = "get_title_data_new_ver";
    vector<string> err_com;
    err_com.push_back("======================================================================");
    err_com.push_back("");
    err_com.push_back(text_data[0]);
    err_com.push_back(text_data[1]);
    err_com.push_back("");
    err_com.push_back("======================================================================");
    err_com.push_back("This line data is not appropriate for ACE file.");
    err_com.push_back("Please check the data file.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  for(int i=0; i<comment_line_no; i++)
  {
    line_data = get_line_data();
    title_data.push_back(line_data);
  }

  //Descriptive string is all space
  discriptive_data = "                                                                      ";
  title_data[2]    = "matXXXX   ";

  if( comment_line_no >= 2 )
  {
    int title_data_no = static_cast<int>(title_data.size());
    vector<string> comment_end;
    comment_end.resize(2);
    comment_end[0] = title_data[title_data_no-2];
    comment_end[1] = title_data[title_data_no-1];

    check_comment_data(comment_end, mcnpx_mode_flg, aw0, tz, discriptive_data, title_data);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceFileReader::get_mat_data(vector<Integer>& zi_vec, vector<Real>& awr_vec)
{
  zi_vec.resize(max_zi_awr_pair_no);
  awr_vec.resize(max_zi_awr_pair_no);

  int    width_zi  = 7;
  int    width_awr = 11;
  int    width_all = width_zi + width_awr;
  int    data_no   = 0;
  string line_data = get_line_data();
  for(int i=0; i<max_zi_awr_pair_no; i++)
  {
    zi_vec[i]  = numeric_string_cast<Integer>(line_data.substr(width_all*data_no,            width_zi));
    awr_vec[i] = numeric_string_cast<Real>(   line_data.substr(width_all*data_no + width_zi, width_awr));

    data_no++;
    if( data_no == 4 && i < max_zi_awr_pair_no - 1 )
    {
      data_no   = 0;
      line_data = get_line_data();
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceFileReader::get_pointer_data(int pointer_data_no, vector<int>& pointer_data)
{
  pointer_data.resize(pointer_data_no);

  int    width     = 9;
  int    data_no   = 0;
  string line_data = get_line_data();
  for(int i=0; i<pointer_data_no; i++)
  {
    pointer_data[i] = numeric_string_cast<int>(line_data.substr(width*data_no, width));

    data_no++;
    if( data_no == 8 && i < pointer_data_no - 1 )
    {
      data_no   = 0;
      line_data = get_line_data();
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

int AceFileReader::get_ace_file_version()
{
  int ver_no = 1;

  string line_data = text_data[1];
  if( line_data.find("mat",0) != string::npos         &&
      static_cast<int>(line_data.find("mat",0)) >= 70 &&
      static_cast<int>(line_data.find("mat",0)) <= 80 )
  {
    //Old ACE format
    ver_no = 1;
  }
  else
  {
    ver_no = 2;
  }

  return ver_no;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

int AceFileReader::get_ace_format_version(string str_data)
{
  char   *ep;
  Real   ace_ver         = strtod(str_data.c_str(), &ep);
  string ace_ver_end_str = ep;
  Real   ace_ver_end     = strtod(ace_ver_end_str.c_str(), &ep);
  int    ver_flg         = static_cast<int>(round(ace_ver*100.0))
                         + static_cast<int>(round(ace_ver_end*10.0));

  return ver_flg;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceFileReader::set_file_name(string& str_data)
{
  clear();

  file_name = str_data;

  ifstream fin(file_name.c_str());
  if( !fin )
  {
    string class_name = "AceFileReader";
    string func_name  = "set_file_name(string& str_data)";

    vector<string> err_com;
    err_com.push_back("There is no ace file.");

    string str_data = "File name : " + file_name;
    err_com.push_back(str_data);
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  int    blank_no = 0;
  string line_data;
  getline(fin, line_data);
  while( !fin.eof() )
  {
    text_data.push_back(line_data);
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
        string class_name = "AceFileReader";
        string func_name  = "set_file_name(string& str_data)";

        string str_data   = "  file name : " + file_name;

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
  }
  fin.close();

  line_no = static_cast<int>(text_data.size());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceFileReader::set_text_data(vector<string>& str_vec)
{
  clear();

  text_data = str_vec;
  line_no   = static_cast<int>(text_data.size());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

string AceFileReader::get_file_name()
{
  return file_name;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> AceFileReader::get_output_data()
{
  return text_data;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

int AceFileReader::get_current_data_position()
{
  return data_count;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

int AceFileReader::get_data_position()
{
  return data_count;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

int AceFileReader::get_current_line_no()
{
  return data_count_total + 1;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

int AceFileReader::get_line_no()
{
  return data_count_total + 1;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

string AceFileReader::get_current_line_data()
{
  return text_data[data_count_total];
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

int AceFileReader::get_ace_data_type_from_ace_file(string ace_file_name)
{
  Integer mcnpx_mode_flg;
  Real    aw0,  tz;
  string  discriptive_data;
  vector<string> title_data;

  clear();

  set_file_name(ace_file_name);
  get_title_data(mcnpx_mode_flg, aw0, tz, discriptive_data, title_data);

  return get_ace_data_type(title_data[0]);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

int AceFileReader::get_ace_data_type(string ace_file_name)
{
  ace_file_name = str_obj.trim_space(ace_file_name);

  int length      = static_cast<int>(ace_file_name.length());
  int ace_data_no = -1;

  transform(ace_file_name.begin(), ace_file_name.end(), ace_file_name.begin(), ::tolower);
  string suffix = ace_file_name.substr(length-1, 1);

  if( suffix == "c" )
  {
    //continuous-energy neutron data
    ace_data_no = fast_data;
  }
  else if( suffix == "t" )
  {
    //thermal scattering law data
    ace_data_no = tsl_data;
  }
  else if( suffix == "y" )
  {
    //dosimetry data
    ace_data_no = dosi_data;
  }
  else if( suffix == "p" )
  {
    //photo-atomic data
    ace_data_no = pa_data;
  }
  else if( suffix == "u" )
  {
    //photonuclear data
    ace_data_no = pn_data;
  }
  else if( suffix == "h" )
  {
    //continuous-energy proton data
    ace_data_no = proton_data;
  }
  else if( suffix == "o" )
  {
    //continuous-energy deuteron data
    ace_data_no = deuteron_data;
  }
  else if( suffix == "r" )
  {
    //continuous-energy triton data
    ace_data_no = triton_data;
  }
  else if( suffix == "s" )
  {
    //continuous-energy He-3 data
    ace_data_no = he_data;
  }
  else if( suffix == "a" )
  {
    //continuous-energy alpha data
    ace_data_no = alpha_data;
  }

  return ace_data_no;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Real AceFileReader::get_awr(string ace_file_name)
{
  Integer mcnpx_mode_flg;
  Real    aw0,  tz;
  string  discriptive_data;
  vector<string> title_data;

  clear();

  set_file_name(ace_file_name);
  get_title_data(mcnpx_mode_flg, aw0, tz, discriptive_data, title_data);

  return aw0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Real AceFileReader::get_temp(string ace_file_name)
{
  Integer mcnpx_mode_flg;
  Real    aw0,  tz;
  string  discriptive_data;
  vector<string> title_data;

  clear();

  set_file_name(ace_file_name);
  get_title_data(mcnpx_mode_flg, aw0, tz, discriptive_data, title_data);

  Real temp = tz / (boltzmann_const * unit_micro);

  return temp;
}

