#include "ContinuousEnergyXSUtils/OtherUtils/AceFileWriter.hpp"

using namespace frendy;

//constructor
AceFileWriter::AceFileWriter(void)
{
  text_data.resize(data_no_each_line);

  clear();
}

//destructor
AceFileWriter::~AceFileWriter(void)
{
  clr_obj.clear_vec_array1_str(text_data);

  clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceFileWriter::clear()
{
  output_data_opt = write_file_mode;
  clr_obj.clear_vec_array1_str(text_data_all);
  xss_data.clear();

  fout.close();
  file_name.clear();

  set_file_name_flg = 0;
  data_count        = 0;

  clear_data_count_total();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceFileWriter::clear_data_count_total()
{
  data_count_total = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceFileWriter::set_int_data(Integer int_val)
{
  if( !isfinite((double)int_val) )
  {
    string class_name = "AceFileWriter";
    string func_name  = "set_int_data(Integer int_val)";

    vector<string> err_com;
    err_com.push_back("NaN data is observed.");
    err_com.push_back("Output of ACE file is aborted.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  ostringstream oss;
  oss << setw(width_int) << setiosflags(ios::right) << int_val;

  text_data[data_count] = oss.str();
  oss.clear();
  data_count++;
  data_count_total++;

  if( output_data_opt == real_vec_mode )
  {
    xss_data.push_back(static_cast<double>(int_val));
  }

  check_data_count();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceFileWriter::set_real_data(Real real_val)
{
  if( !isfinite(real_val) )
  {
    string class_name = "AceFileWriter";
    string func_name  = "set_real_data(Real real_val)";

    vector<string> err_com;
    err_com.push_back("NaN data is observed.");
    err_com.push_back("Output of ACE file is aborted.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  ostringstream oss;
  oss.width(width_int);
  oss.precision(width_real);
  oss << setiosflags(ios::scientific) << setiosflags(ios::right) << setiosflags(ios::showpoint)
      << real_val;
  
  text_data[data_count] = oss.str();
  oss.clear();
  data_count++;
  data_count_total++;

  if( output_data_opt == real_vec_mode )
  {
    xss_data.push_back(static_cast<double>(real_val));
  }

  check_data_count();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceFileWriter::set_real8_data(Real8 real_val)
{
  if( !isfinite(real_val) )
  {
    string class_name = "AceFileWriter";
    string func_name  = "set_real8_data(Real8 real_val)";

    vector<string> err_com;
    err_com.push_back("NaN data is observed.");
    err_com.push_back("Output of ACE file is aborted.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  ostringstream oss;
  oss.width(width_int);
  oss.precision(width_real);
  oss << setiosflags(ios::scientific) << setiosflags(ios::right) << setiosflags(ios::showpoint)
      << real_val;

  text_data[data_count] = oss.str();
  oss.clear();
  data_count++;
  data_count_total++;

  if( output_data_opt == real_vec_mode )
  {
    xss_data.push_back(static_cast<double>(real_val));
  }

  check_data_count();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceFileWriter::check_data_count()
{
  if( data_count >= data_no_each_line )
  {
    output_storage_data();
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceFileWriter::set_line_data(string str_data)
{
  output_storage_data();

  if( output_data_opt == write_file_mode )
  {
    fout << str_data << endl;
  }
  else if( output_data_opt == string_data_mode )
  {
    text_data_all.push_back(str_data);
  }
  //else if( output_data_opt == pointer_calc_mode )
  //{
  //}
  str_data.clear();

  data_count_total += 4;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceFileWriter::output_storage_data()
{
  fout_check();

  if( data_count > 0 )
  {
    if( output_data_opt == write_file_mode )
    {
      for(int i=0; i<data_count; i++)
      {
        fout << text_data[i];
      }
      fout << endl;
    }
    else if( output_data_opt == string_data_mode )
    {
      string str_data = "";
      for(int i=0; i<data_count; i++)
      {
        str_data = str_data + text_data[i];
      }
      text_data_all.push_back(str_data);
    }
    //else if( output_data_opt == pointer_calc_mode )
    //{
    //}
  }
  data_count = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceFileWriter::set_list_data(vector<Integer>& list_vec)
{
  int i_max = static_cast<int>(list_vec.size());
  set_int_data(i_max);
  for(int i=0; i<i_max; i++)
  {
    set_int_data(list_vec[i]);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceFileWriter::set_list_data_without_data_no(vector<Integer>& list_vec)
{
  int i_max = static_cast<int>(list_vec.size());
  for(int i=0; i<i_max; i++)
  {
    set_int_data(list_vec[i]);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceFileWriter::set_list_data(vector<Real>& list_vec)
{
  int i_max = static_cast<int>(list_vec.size());
  set_int_data(i_max);
  for(int i=0; i<i_max; i++)
  {
    set_real_data(list_vec[i]);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceFileWriter::set_list_data_without_data_no(vector<Real>& list_vec)
{
  int i_max = static_cast<int>(list_vec.size());
  for(int i=0; i<i_max; i++)
  {
    set_real_data(list_vec[i]);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceFileWriter::set_interpolation_data(vector<Integer>& range_vec, vector<Integer>& int_vec)
{
  int i_max = static_cast<int>(range_vec.size());
  if( i_max == 1 && int_vec[0] == int_lin_lin )
  {
    set_int_data(0);
  }
  else
  {
    set_list_data(range_vec);
    set_list_data_without_data_no(int_vec);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceFileWriter::set_table_data(vector<Real>& x_vec, vector<Real>& y_vec)
{
  set_list_data(x_vec);
  set_list_data_without_data_no(y_vec);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceFileWriter::set_table_data(vector<Real>& x_vec, vector<Real>& y_vec, vector<Real>& y_vec_integ)
{
  set_table_data(x_vec, y_vec);
  set_list_data_without_data_no(y_vec_integ);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceFileWriter::set_table_data(vector<Integer>& range_vec, vector<Integer>& int_vec,
                                   vector<Real>&    x_vec,     vector<Real>&    y_vec)
{
  set_interpolation_data(range_vec, int_vec);
  set_table_data(x_vec, y_vec);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceFileWriter::set_table_data(vector<Integer>& range_vec, vector<Integer>& int_vec,
                                   vector<Real>& x_vec, vector<Real>& y_vec, vector<Real>& y_vec_integ)
{
  set_table_data(range_vec, int_vec, x_vec, y_vec);

  set_list_data_without_data_no(y_vec_integ);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

int AceFileWriter::get_ace_ver(vector<string>& title_data)
{
  int ace_ver = 0;
  if( static_cast<int>(title_data.size()) == 3 )
  {
    if( static_cast<int>(title_data[0].size()) <= 10 )
    {
      ace_ver = 1;
    }
  }
  else if( static_cast<int>(title_data.size()) >= 5 )
  {
    ace_ver = 2;
  }

  return ace_ver;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceFileWriter::set_title_data(Integer& mcnpx_mode_flg, Real& aw0, Real& tz,
                                   string& discriptive_data, vector<string>& title_data)
{
  int ace_ver = get_ace_ver(title_data);

  if( ace_ver == 1 )
  {
    set_title_data_legacy_ver(mcnpx_mode_flg, aw0, tz, discriptive_data, title_data);
  }
  else if( ace_ver == 2 )
  {
    set_title_data_new_ver(mcnpx_mode_flg, aw0, tz, discriptive_data, title_data);
  }
  else
  {
    string class_name = "AceFileWriter";
    string func_name  = "set_title_data";
    ostringstream oss;
    oss << static_cast<int>(title_data.size());
    string str_data = "Number of title data : " + oss.str();

    vector<string> err_com;
    err_com.push_back(str_data);
    for(int i=0; i<static_cast<int>(title_data.size()); i++)
    {
      err_com.push_back(title_data[i]);
    }
    err_com.push_back("");
    err_com.push_back("This title data is not appropriate for the ACE file.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceFileWriter::set_title_data_legacy_ver(Integer& mcnpx_mode_flg, Real& aw0, Real& tz,
                                              string& discriptive_data, vector<string>& title_data)
{
  if( static_cast<int>(title_data.size()) != 3 )
  {
    string class_name = "AceFileWriter";
    string func_name  = "set_title_data_legacy_ver";
    ostringstream oss;
    oss << static_cast<int>(title_data.size());
    string str_data = "Number of title data : " + oss.str();

    vector<string> err_com;
    err_com.push_back(str_data);
    for(int i=0; i<static_cast<int>(title_data.size()); i++)
    {
      err_com.push_back(title_data[i]);
    }
    err_com.push_back("");
    err_com.push_back("The number of title data must be 3.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  string line_data;
  int width = 10;
  if( mcnpx_mode_flg != 0 )
  {
    width = 13;
  }
  line_data = title_data[0].substr(0,width);

  if( mcnpx_mode_flg != 0 && mcnpx_mode_flg != 1 )
  {
    string class_name = "AceFileWriter";
    string func_name  = "set_title_data";
    ostringstream oss;
    oss << static_cast<int>(mcnpx_mode_flg);
    string str_data = "MCNPX mode flag : " + oss.str();

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("MCNPX mode flag is only available for 0 or 1.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  add_space_data(width, line_data);

  //Line No. 01
  ostringstream oss01, oss02;
  oss01.width(12);
  oss01.precision(6);
  oss01 << setiosflags(ios::right) << setiosflags(ios::showpoint) << fixed << aw0;
  oss02.width(11);
  oss02.precision(4);
  oss02 << setiosflags(ios::scientific) << setiosflags(ios::right) << setiosflags(ios::showpoint) << tz;

  line_data = line_data + oss01.str() + " " + oss02.str() + " " + title_data[1];
  set_line_data(line_data);
  line_data.clear();

  //Line No. 02
  line_data = discriptive_data;
  width = 70;
  line_data = discriptive_data.substr(0,width);
  add_space_data(width, line_data);

  line_data = line_data + title_data[2];
  set_line_data(line_data);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceFileWriter::set_title_data_new_ver(Integer& mcnpx_mode_flg, Real& aw0, Real& tz,
                                           string& discriptive_data, vector<string>& title_data)
{
  //Check ACE format version
  char   *ep;
  Real   ace_ver         = strtod(title_data[3].c_str(), &ep);
  string ace_ver_end_str = ep;
  Real   ace_ver_end     = strtod(ace_ver_end_str.c_str(), &ep);
  int    ver_flg         = static_cast<int>(round(ace_ver*100.0))
                         + static_cast<int>(round(ace_ver_end*10.0));

  //Line No. 01
  //version format (VERS)
  int width = 10;
  string line_data1 = title_data[3].substr(0,width);

  add_space_data(width, line_data1);

  //SZAID
  if( ver_flg == 200 )
  {
    width = 24;
  }
  else //if( ver_flg == 201 )
  {
    width = 25;
  }
  string line_data2 = title_data[0].substr(0,width);

  add_space_data(width, line_data2);

  //VERS + HZ + SRC
  string line_data = line_data1 + line_data2 + title_data[4];
  set_line_data(line_data);
  line_data.clear();

  //Line No. 02
  //atomic weight ratio (AW)
  ostringstream oss01, oss02, oss03;
  if( ver_flg == 200 )
  {
    oss01.width(10);
    oss01.precision(6);
    oss02.width(11);
    oss02.precision(4);
  }
  else //if( ver_flg == 201 )
  {
    oss01.width(12);
    oss01.precision(6);
    oss02.width(12);
    oss02.precision(4);
  }
  oss01 << setiosflags(ios::right) << setiosflags(ios::showpoint) << fixed << aw0;
  oss02 << setiosflags(ios::scientific) << setiosflags(ios::right) << setiosflags(ios::showpoint) << tz;
 
  width = 10;
  line_data1 = title_data[1].substr(0,width);

  add_space_data(width, line_data1);

  int comment_line_no = static_cast<int>(title_data.size()) - 5;
  width = 5;
  oss03.width(width);
  oss03 << comment_line_no;
  line_data2 = oss03.str();
  
  add_space_data(width, line_data2);

  if( ver_flg == 200 )
  {
    line_data = oss01.str() + oss02.str() + " " + line_data1 + line_data2;
  }
  else //if( ver_flg == 201 )
  {
    line_data = oss01.str() + " " + oss02.str() + " " + line_data1 + line_data2;
  }
  set_line_data(line_data);
  line_data.clear();

  for(int i=0; i<comment_line_no; i++)
  {
    set_line_data(title_data[5+i]);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceFileWriter::add_space_data(int width, string& line_data)
{
  int char_no = static_cast<int>(line_data.size());

  if( char_no < width )
  {
    for(int i=0; i<width - char_no; i++)
    {
      line_data = line_data + " ";
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceFileWriter::set_mat_data(vector<Integer>& zi_vec, vector<Real>& awr_vec)
{
  int i_max = static_cast<int>(zi_vec.size());
  if( i_max != static_cast<int>(awr_vec.size()) )
  {
    string class_name = "AceFileWriter";
    string func_name  = "set_mat_data(vector<Integer>& zi_vec, vector<Real>& awr_vec)";

    ostringstream oss01, oss02;
    oss01 << static_cast<int>(zi_vec.size());
    oss02 << static_cast<int>(awr_vec.size());

    string str_data01 = "Number of ZI  array data : " + oss01.str();
    string str_data02 = "Number of AWR array data : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("Number of ZI array data and that of AWR array data is not identical.");
    err_com.push_back("Please check the set data.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  if( i_max < max_zi_awr_pair_no )
  {
    for(int i=0; i<max_zi_awr_pair_no - i_max; i++)
    {
      zi_vec.push_back(0);
      awr_vec.push_back(0.0);
    }
  }
  else if( i_max > max_zi_awr_pair_no )
  {
    string class_name = "AceFileWriter";
    string func_name  = "set_mat_data(vector<Integer>& zi_vec, vector<Real>& awr_vec)";
    ostringstream oss01;
    oss01 << i_max;
    string str_data01 = "Number of ZI and AWR pair data : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    for(int i=0; i<i_max; i++)
    {
      ostringstream oss02, oss03, oss04;
      oss02 << i+1;
      oss03 << zi_vec[i];
      oss04 << awr_vec[i];
      string str_data02 = "  ZI and AWR data at " + oss02.str() + " / " + oss01.str() + " : "
                        + oss03.str() + ", " + oss04.str();
      if( i >= max_zi_awr_pair_no )
      {
        str_data02 + " * not used";
      }
      err_com.push_back(str_data02);
    }
    ostringstream oss05;
    oss05 << max_zi_awr_pair_no;
    string str_data03 = "ZI and AWR data array must be less than or equal to " + oss05.str() + ".";
    err_com.push_back("So, some data in ZI and AWR pair is not used.");
    err_obj.output_caution(class_name, func_name, err_com);

    vector<Integer> zi_vec_ori  = zi_vec;
    vector<Real>    awr_vec_ori = awr_vec;
    zi_vec.resize(max_zi_awr_pair_no);
    awr_vec.resize(max_zi_awr_pair_no);
    for(int i=0; i<max_zi_awr_pair_no; i++)
    {
      zi_vec[i]  = zi_vec_ori[i];
      awr_vec[i] = awr_vec_ori[i];
    }
    zi_vec_ori.clear();
    awr_vec_ori.clear();
  }

  int    data_no   = 0;
  string line_data = "";
  for(int i=0; i<max_zi_awr_pair_no; i++)
  {
    data_no++;

    ostringstream oss01, oss02;
    oss01.width(7);
    oss01 << setiosflags(ios::right) << zi_vec[i];
    oss02.width(11);
    oss02 << setiosflags(ios::right) << static_cast<Integer>(awr_vec[i]);

    line_data = line_data + oss01.str() + oss02.str();
    if( data_no == 4 || i==max_zi_awr_pair_no-1 )
    {
      set_line_data(line_data);
      data_no   = 0;
      line_data = "";
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceFileWriter::set_pointer_data(vector<int>& pointer_vec)
{
  int    i_max   = static_cast<int>(pointer_vec.size());
  int    data_no = 0;
  string line_data  = "";
  for(int i=0; i<i_max; i++)
  {
    data_no++;

    ostringstream oss01;
    oss01.width(9);
    oss01 << setiosflags(ios::right) << pointer_vec[i];

    line_data = line_data + oss01.str();
    if( data_no == 8 || i==i_max-1 )
    {
      set_line_data(line_data);
      data_no   = 0;
      line_data = "";
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceFileWriter::fout_check()
{
  if( set_file_name_flg == 0 && output_data_opt == write_file_mode )
  {
    string class_name = "AceFileWriter";
    string func_name  = "fout_check()";
    string err_com    = "Please set output file name.";
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceFileWriter::close_file()
{
  output_storage_data();
  clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceFileWriter::set_file_name(string& str_data)
{
  clear();

  file_name         = str_data;
  set_file_name_flg = 1;
  fout.open(file_name.c_str());

  if( fout.fail() )
  {
    string class_name = "AceFileWriter";
    string func_name  = "set_file_name(string& str_data)";

    string str_data = "  Output ACE file name : " + file_name;

    vector<string> err_com;
    err_com.push_back("Output ACE file can not be open.");
    err_com.push_back("Please check the file name, directory name or access authority.");
    err_com.push_back(str_data);

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

string AceFileWriter::get_file_name()
{
  return file_name;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

int AceFileWriter::get_data_count()
{
  return data_count + 1;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

int AceFileWriter::get_data_count_total()
{
  return data_count_total + 1;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> AceFileWriter::get_output_data()
{
  output_storage_data();

  return text_data_all;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

vector<double> AceFileWriter::get_xss_data()
{
  return xss_data;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceFileWriter::set_output_data_opt(int int_value)
{
  if( output_data_opt != int_value )
  {
    clear();
    output_data_opt = int_value;

    if( int_value != write_file_mode   && int_value != string_data_mode &&
        int_value != pointer_calc_mode && int_value != real_vec_mode )
    {
      string class_name = "AceFileWriter";
      string func_name  = "set_output_data_opt(int int_value)";

      ostringstream oss;
      oss << int_value;
      string str_data = "Output data option : " + oss.str();

      vector<string> err_com;
      err_com.push_back(str_data);
      err_com.push_back("This output data option is not available.");
      err_com.push_back("The availabile output data option is");
      err_com.push_back("0 (write_file_mode), 1 (string_data_mode), 2 (pointer_calc_mode) and 3 (real_vec_mode).");
      err_com.push_back("Please check the output data option.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

int AceFileWriter::get_output_data_opt()
{
  return output_data_opt;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
