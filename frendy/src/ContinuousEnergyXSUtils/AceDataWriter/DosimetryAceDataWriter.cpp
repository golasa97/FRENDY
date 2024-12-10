#include "ContinuousEnergyXSUtils/AceDataWriter/DosimetryAceDataWriter.hpp"

using namespace frendy;

//constructor
DosimetryAceDataWriter::DosimetryAceDataWriter(void)
{
  clear();
}

//destructor
DosimetryAceDataWriter::~DosimetryAceDataWriter(void)
{
  clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DosimetryAceDataWriter::clear()
{
  ace_wri_obj.clear();
  ace_data_obj.clear();

  set_data_flg         = 0;
  set_ace_data_obj_flg = 0;
  opt_out_type         = ascii_mode;

  line_no_pre          = 0;

  ace_file_name.clear();

  clear_ace_data();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DosimetryAceDataWriter::clear_ace_data()
{
  mcnpx_mode_flg = 0;

  zi_vec.clear();
  awr_vec.clear();

  aw0 = 0.0;
  tz  = 0.0;
  clr_obj.clear_vec_array1_str(title_data);
  discriptive_data.clear();

  reaction_xs_reaction_type.clear();
  reaction_xs_pointer.clear();
  clr_obj.clear_vec_array2_int(reaction_xs_range_data);
  clr_obj.clear_vec_array2_int(reaction_xs_int_data);
  clr_obj.clear_vec_array2_real(reaction_xs_ene_data);
  clr_obj.clear_vec_array2_real(reaction_xs_data);

  clr_obj.clear_vec_array2_int(production_xs_state_no_product);
  clr_obj.clear_vec_array2_int(production_xs_pointer);
  clr_obj.clear_vec_array3_int(production_xs_range_data);
  clr_obj.clear_vec_array3_int(production_xs_int_data);
  clr_obj.clear_vec_array3_real(production_xs_ene_data);
  clr_obj.clear_vec_array3_real(production_xs_data);

  clear_ace_pointer_data();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DosimetryAceDataWriter::clear_ace_pointer_data()
{
  len2 = 0;
  za   = 0;
  ntr  = 0;
  lone = 0;
  mtr  = 0;
  lsig = 0;
  sigd = 0;
  end  = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DosimetryAceDataWriter::copy_dosimetry_ace_data()
{
  mcnpx_mode_flg   = ace_data_obj.get_mcnpx_mode_flg();

  aw0              = ace_data_obj.get_aw0();
  tz               = ace_data_obj.get_tz();
  title_data       = ace_data_obj.get_title_data();
  discriptive_data = ace_data_obj.get_discriptive_data();

  zi_vec           = ace_data_obj.get_zi_vec();
  awr_vec          = ace_data_obj.get_awr_vec();

  reaction_xs_reaction_type = ace_data_obj.get_reaction_xs_reaction_type();
  reaction_xs_pointer       = ace_data_obj.get_reaction_xs_pointer();
  reaction_xs_range_data    = ace_data_obj.get_reaction_xs_range_data();
  reaction_xs_int_data      = ace_data_obj.get_reaction_xs_int_data();
  reaction_xs_ene_data      = ace_data_obj.get_reaction_xs_ene_data();
  reaction_xs_data          = ace_data_obj.get_reaction_xs_data();

  production_xs_state_no_product = ace_data_obj.get_production_xs_state_no_product();
  production_xs_pointer          = ace_data_obj.get_production_xs_pointer();
  production_xs_range_data       = ace_data_obj.get_production_xs_range_data();
  production_xs_int_data         = ace_data_obj.get_production_xs_int_data();
  production_xs_ene_data         = ace_data_obj.get_production_xs_ene_data();
  production_xs_data             = ace_data_obj.get_production_xs_data();

  //For pointer data
  len2 = ace_data_obj.get_len2();
  za   = ace_data_obj.get_za();
  ntr  = ace_data_obj.get_ntr();
  lone = ace_data_obj.get_lone();
  mtr  = ace_data_obj.get_mtr();
  lsig = ace_data_obj.get_lsig();
  sigd = ace_data_obj.get_sigd();
  end  = ace_data_obj.get_end();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DosimetryAceDataWriter::copy_dosimetry_ace_pointer_data
                                   (DosimetryAceDataObject& dosimetry_ace_data_obj)
{
  dosimetry_ace_data_obj.set_len2(len2);
  dosimetry_ace_data_obj.set_za(za);
  dosimetry_ace_data_obj.set_ntr(ntr);
  dosimetry_ace_data_obj.set_lone(lone);
  dosimetry_ace_data_obj.set_mtr(mtr);
  dosimetry_ace_data_obj.set_lsig(lsig);
  dosimetry_ace_data_obj.set_sigd(sigd);
  dosimetry_ace_data_obj.set_end(end);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Integer DosimetryAceDataWriter::get_line_no()
{
  return ace_wri_obj.get_data_count_total() / 4;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DosimetryAceDataWriter::write_dir_data(string dir_name)
{
  ofstream fout_dir;
  fout_dir.open(dir_name.c_str());

  if( fout_dir.fail() )
  {
    string class_name = "DosimetryAceDataWriter";
    string func_name  = "write_dir_data(string dir_name)";

    string str_data = "  Output xsdir file name : " + dir_name;

    vector<string> err_com;
    err_com.push_back("Output xsdir file can not be open.");
    err_com.push_back("Please check the file name, directory name or access authority.");
    err_com.push_back(str_data);

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  fout_dir << get_dir_data() << endl;
  fout_dir.close();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

string DosimetryAceDataWriter::get_dir_data()
{
  if( set_data_flg != 1 )
  {
    check_set_data();
    copy_dosimetry_ace_data();

    calc_ace_header_file_data();
  }

  vector<string> line_data_vec;
  line_data_vec.resize(8);

  int width = 10;
  if( mcnpx_mode_flg != 0 )
  {
    width = 13;
  }
  line_data_vec[0] = title_data[0].substr(0,width);

  ostringstream oss_aw0;
  oss_aw0.width(12);
  oss_aw0.precision(6);
  oss_aw0 << setiosflags(ios::right) << setiosflags(ios::showpoint) << fixed << aw0;
  line_data_vec[1] = oss_aw0.str();

  Integer itype = 1;
  ostringstream oss_itype;
  oss_itype.width(2);
  oss_itype << setiosflags(ios::right) << itype;
  line_data_vec[2] = oss_itype.str();

  Integer irec1 = 1;
  if( line_no_pre != 0 )
  {
    irec1 = line_no_pre + 1;
  }
  int char_no_irec1 = ad_obj.get_digit_number(static_cast<Real8>(irec1)) + 1;
  ostringstream oss_irec1;
  oss_irec1.width(8);
  if( char_no_irec1 >= 8 )
  {
    oss_irec1.width(char_no_irec1+1);
  }
  oss_irec1 << setiosflags(ios::right) << irec1;
  line_data_vec[3] = oss_irec1.str();

  int char_no_len2 = ad_obj.get_digit_number(static_cast<Real8>(len2)) + 1;
  ostringstream oss_len2;
  oss_len2.width(8);
  if( char_no_len2 >= 8 )
  {
    oss_len2.width(char_no_len2+1);
  }
  oss_len2 << setiosflags(ios::right) << len2;
  line_data_vec[4] = oss_len2.str();

  Integer lrec = 0;
  ostringstream oss_lrec;
  oss_lrec.width(2);
  oss_lrec << setiosflags(ios::right) << lrec;
  line_data_vec[5] = oss_lrec.str();

  Integer nern = 0;
  ostringstream oss_nern;
  oss_nern.width(2);
  oss_nern << setiosflags(ios::right) << nern;
  line_data_vec[6] = oss_nern.str();

  ostringstream oss_tz;
  oss_tz.width(10);
  oss_tz.precision(3);
  oss_tz << setiosflags(ios::scientific) << setiosflags(ios::right) << setiosflags(ios::showpoint) << tz;
  line_data_vec[7] = oss_tz.str();

  string char_data = " filename route";
  if( mcnpx_mode_flg != 0 )
  {
    char_data = " file route";
  }

  string line_data = line_data_vec[0] + line_data_vec[1] + char_data        + line_data_vec[2]
                   + line_data_vec[3] + line_data_vec[4] + line_data_vec[5] + line_data_vec[6]
                   + line_data_vec[7];
  clr_obj.clear_vec_array1_str(line_data_vec);

  return line_data;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DosimetryAceDataWriter::write_ace_format()
{
  if( set_data_flg == 1 )
  {
    return;
  }
  set_data_flg = 1;

  if( static_cast<int>(ace_file_name.size()) == 0 )
  {
    vector<string> err_com;
    err_com.push_back("There is no ace file name.");
    err_com.push_back("Please set ace file name by set_ace_file_name function.");
    err_com.push_back("");

    string class_name = "DosimetryAceDataWriter";
    string func_name  = "write_ace_format()";
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  check_set_data();
  copy_dosimetry_ace_data();

  if( opt_out_type == ascii_mode )
  {
    output_ace_format();
  }
  else if( opt_out_type == binary_mode )
  {
    output_ace_format_binary_mode();
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> DosimetryAceDataWriter::get_ace_text_data()
{
  vector<string> text_data;
  text_data.clear();

  if( set_data_flg == 1 )
  {
    return text_data;
  }
  set_data_flg = 1;

  check_set_data();
  copy_dosimetry_ace_data();

  ace_wri_obj.clear();
  ace_wri_obj.set_output_data_opt(ace_wri_obj.string_data_mode);

  output_ace_format_header();
  output_ace_format_xs();
  ace_wri_obj.output_storage_data();

  text_data = ace_wri_obj.get_output_data();
  ace_wri_obj.clear();

  return text_data;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DosimetryAceDataWriter::get_ace_data_for_mg(vector<string>& title_vec, vector<int>& izaw_vec,
                                                 vector<int>& nxs_vec, vector<int>& jxs_vec,
                                                 vector<double>& xss_vec)
{
  if( set_data_flg == 1 )
  {
    return;
  }

  //Get xss_vec
  xss_vec = get_xss_data();

  //Get title_vec
  copy_dosimetry_ace_data();
  ace_wri_obj.set_output_data_opt(ace_wri_obj.string_data_mode);
  ace_wri_obj.set_title_data(mcnpx_mode_flg, aw0, tz, discriptive_data, title_data);

  title_vec = ace_wri_obj.get_output_data();
  ace_wri_obj.clear();

  //Get izaw_vec
  int i_max = static_cast<int>(zi_vec.size());
  izaw_vec.resize(i_max*2);
  for(int i=0; i<i_max; i++)
  {
    izaw_vec[2*i]   = zi_vec[i];
    izaw_vec[2*i+1] = awr_vec[i];
  }

  //Get nxs_vec
  nxs_vec.clear();
  nxs_vec.push_back(len2);
  nxs_vec.push_back(za);
  nxs_vec.push_back(0);
  nxs_vec.push_back(ntr);

  for(int i=0; i<12; i++)
  {
    nxs_vec.push_back(0);
  }

  //Get jxs_vec
  jxs_vec.clear();
  jxs_vec.push_back(lone);
  jxs_vec.push_back(0);
  jxs_vec.push_back(mtr);
  jxs_vec.push_back(0);
  jxs_vec.push_back(0);
  jxs_vec.push_back(lsig);
  jxs_vec.push_back(sigd);

  for(int i=0; i<14; i++)
  {
    jxs_vec.push_back(0);
  }

  jxs_vec.push_back(end);

  for(int i=0; i<10; i++)
  {
    jxs_vec.push_back(0);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

vector<double> DosimetryAceDataWriter::get_xss_data()
{
  vector<double> xss_data;
  xss_data.clear();

  if( set_data_flg == 1 )
  {
    return xss_data;
  }
  set_data_flg = 1;

  check_set_data();
  copy_dosimetry_ace_data();

  ace_wri_obj.clear();
  ace_wri_obj.set_output_data_opt(ace_wri_obj.real_vec_mode);

  output_ace_format_header();
  output_ace_format_xs();
  ace_wri_obj.output_storage_data();

  xss_data = ace_wri_obj.get_xss_data();
  ace_wri_obj.clear();

  return xss_data;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DosimetryAceDataWriter::output_ace_format()
{
  ace_wri_obj.clear();
  ace_wri_obj.set_file_name(ace_file_name);

  pointer_data_count = ace_wri_obj.get_data_count_total();
  ace_wri_obj.clear_data_count_total();

  output_ace_format_header();
  output_ace_format_xs();

  ace_wri_obj.output_storage_data();
  ace_wri_obj.close_file();
  ace_wri_obj.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DosimetryAceDataWriter::output_ace_format_header()
{
  //Calc pointer data
  calc_ace_header_file_data();

  //Line No. 01-02
  ace_wri_obj.set_title_data(mcnpx_mode_flg, aw0, tz, discriptive_data, title_data);

  //Line No. 03-06
  ace_wri_obj.set_mat_data(zi_vec, awr_vec);

  //Output pointer data
  vector<Integer> pointer_vec;
  pointer_vec.push_back(len2);
  pointer_vec.push_back(za);
  pointer_vec.push_back(0);
  pointer_vec.push_back(ntr);

  for(int i=0; i<12; i++)
  {
    pointer_vec.push_back(0);
  }

  pointer_vec.push_back(lone);
  pointer_vec.push_back(0);
  pointer_vec.push_back(mtr);
  pointer_vec.push_back(0);
  pointer_vec.push_back(0);
  pointer_vec.push_back(lsig);
  pointer_vec.push_back(sigd);
  
  for(int i=0; i<14; i++)
  {
    pointer_vec.push_back(0);
  }
  
  pointer_vec.push_back(end);
  
  for(int i=0; i<10; i++)
  {
    pointer_vec.push_back(0);
  }

  ace_wri_obj.set_pointer_data(pointer_vec);
  pointer_vec.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DosimetryAceDataWriter::output_ace_format_xs()
{
  //Output reaction type
  ace_wri_obj.set_list_data_without_data_no(reaction_xs_reaction_type);

  int i_max = static_cast<int>(production_xs_state_no_product.size());
  for(int i=0; i<i_max; i++)
  {
    ace_wri_obj.set_list_data_without_data_no(production_xs_state_no_product[i]);
  }


  //Output pointer data
  ace_wri_obj.set_list_data_without_data_no(reaction_xs_pointer);

  i_max = static_cast<int>(production_xs_pointer.size());
  for(int i=0; i<i_max; i++)
  {
    ace_wri_obj.set_list_data_without_data_no(production_xs_pointer[i]);
  }


  //Output xs data for reaction xs
  i_max = static_cast<int>(reaction_xs_reaction_type.size());
  for(int i=0; i<i_max; i++)
  {
    ace_wri_obj.set_table_data(reaction_xs_range_data[i], reaction_xs_int_data[i],
                               reaction_xs_ene_data[i],   reaction_xs_data[i]);
  }


  //Output xs data for production xs
  i_max = static_cast<int>(production_xs_state_no_product.size());
  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(production_xs_state_no_product[i].size());
    for(int j=0; j<j_max; j++)
    {
      ace_wri_obj.set_table_data(production_xs_range_data[i][j], production_xs_int_data[i][j],
                                 production_xs_ene_data[i][j],   production_xs_data[i][j]);
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DosimetryAceDataWriter::calc_ace_header_file_data()
{
  int width = 10 - 4; //remove .XXy
  if( mcnpx_mode_flg != 0 )
  {
    width = 13 - 5; //remove .XXny
  }
  string za_str = title_data[0].substr(0,width);

  za  = atoi(za_str.c_str());

  ntr = static_cast<int>(reaction_xs_reaction_type.size());
  for(int i=0; i<static_cast<int>(production_xs_state_no_product.size()); i++)
  {
    ntr += static_cast<int>(production_xs_state_no_product[i].size());
  }

  lone = 1;
  mtr  = 1;
  lsig = mtr + ntr;
  sigd = mtr + 2*ntr;

  //Calculation of len2
  int pointer_no = 0;
  int i_max = static_cast<int>(reaction_xs_reaction_type.size());
  reaction_xs_pointer.resize(i_max);

  len2 = 2*i_max; //MT number + pointer
  for(int i=0; i<i_max; i++)
  {
    reaction_xs_pointer[i] = pointer_no + 1;

    int j_max = static_cast<int>(reaction_xs_int_data[i].size());
    if( j_max == 1 && reaction_xs_int_data[i][0] == int_lin_lin )
    {
      pointer_no += 1;
    }
    else
    {
      pointer_no += 2*j_max + 1;
    }

    j_max = static_cast<int>(reaction_xs_data[i].size());
    pointer_no += 2*j_max + 1;
  }

  i_max = static_cast<int>(production_xs_state_no_product.size());
  production_xs_pointer.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(production_xs_state_no_product[i].size());
    production_xs_pointer[i].resize(j_max);

    len2 += 2*j_max; //MT number + pointer
    for(int j=0; j<j_max; j++)
    {
      production_xs_pointer[i][j] = pointer_no + 1;

      int k_max = static_cast<int>(production_xs_int_data[i][j].size());
      if( k_max == 1 && production_xs_int_data[i][j][0] == int_lin_lin )
      {
        pointer_no += 1;
      }
      else
      {
        pointer_no += 2*k_max + 1;
      }

      k_max = static_cast<int>(production_xs_data[i][j].size());
      pointer_no += 2*k_max + 1;
    }
  }
  len2 += pointer_no;

  end = len2;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DosimetryAceDataWriter::output_ace_format_binary_mode()
{
  string class_name = "DosimetryAceDataWriter";
  string func_name  = "output_ace_format_binary_mode()";
  vector<string> err_com;
  err_com.push_back("This function is not implemented.");
  err_com.push_back("Please use output_ace_format function.");
  err_obj.output_runtime_error(class_name, func_name, err_com);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DosimetryAceDataWriter::check_set_data()
{
  vector<string> err_com;
  err_com.clear();

  if( set_ace_data_obj_flg != 1 )
  {
    err_com.push_back("There is no DosimetryAceDataObject.");
    err_com.push_back("Please set the DosimetryAceDataObject by using set_ace_data_obj method.");
    err_com.push_back("");
  }

  if( opt_out_type != ascii_mode && opt_out_type != binary_mode )
  {
    ostringstream oss;
    oss << opt_out_type;
    string str_data = "Print option : " + oss.str();
    err_com.push_back(str_data);
    err_com.push_back("This output type option is not available.");
    err_com.push_back("The available output type option is 1 (ascii mode) or 2 (binary mode).");
    err_com.push_back("");
  }

  if( static_cast<int>(err_com.size()) > 0 )
  {
    string class_name = "DosimetryAceDataWriter";
    string func_name  = "check_set_data()";
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//Setter

void DosimetryAceDataWriter::set_ace_data_obj(DosimetryAceDataObject& data_obj)
{
  set_data_flg         = 0;
  set_ace_data_obj_flg = 1;
  ace_data_obj         = data_obj;
}

void DosimetryAceDataWriter::set_opt_out_type(Integer int_val)
{
  set_data_flg = 0;
  opt_out_type = int_val;
}

void DosimetryAceDataWriter::set_ace_file_name(string str_data)
{
  set_data_flg  = 0;
  ace_file_name = str_data;
  str_data.clear();
}

void DosimetryAceDataWriter::set_previous_line_no(Integer int_val)
{
  set_data_flg = 0;
  line_no_pre = int_val;

  if( line_no_pre < 0 )
  {
    string class_name = "DosimetryAceDataWriter";
    string func_name  = "set_previous_line_no(Integer int_val)";
    ostringstream oss01;
    oss01 << line_no_pre;

    string str_data = "The previous line no : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("The previous line no must be larger than or equal to 0.");
    err_com.push_back("Please check the set value.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//Getter

DosimetryAceDataObject DosimetryAceDataWriter::get_ace_data_obj()
{
  if( set_data_flg == 0 && set_ace_data_obj_flg == 1 )
  {
    calc_ace_header_file_data();
    copy_dosimetry_ace_pointer_data(ace_data_obj);
  }

  return ace_data_obj;
}

Integer DosimetryAceDataWriter::get_opt_out_type()
{
  return opt_out_type;
}

string  DosimetryAceDataWriter::get_ace_file_name()
{
  return ace_file_name;
}

Integer DosimetryAceDataWriter::get_previous_line_no()
{
  return line_no_pre;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

