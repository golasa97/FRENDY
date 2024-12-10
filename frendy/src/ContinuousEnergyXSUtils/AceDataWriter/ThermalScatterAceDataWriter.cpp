#include "ContinuousEnergyXSUtils/AceDataWriter/ThermalScatterAceDataWriter.hpp"

using namespace frendy;

//Initialize static const value
const Real8 ThermalScatterAceDataWriter::min_second_ene_dif_abs = ThermalScatterAceDataObject::min_second_ene_dif_abs;

//constructor
ThermalScatterAceDataWriter::ThermalScatterAceDataWriter(void)
{
  clear();
}

//destructor
ThermalScatterAceDataWriter::~ThermalScatterAceDataWriter(void)
{
  clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterAceDataWriter::clear()
{
  ace_wri_obj.clear();
  ace_data_obj.clear();

  set_data_flg         = 0;
  set_ace_data_obj_flg = 0;
  opt_out_type         = ascii_mode;
  opt_weight           = -1;

  line_no_pre          = 0;

  ace_file_name.clear();

  clear_ace_data();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterAceDataWriter::clear_ace_data()
{
  mcnpx_mode_flg = 0;

  mod_za.clear();

  zi_vec.clear();
  awr_vec.clear();

  aw0 = 0.0;
  tz  = 0.0;
  clr_obj.clear_vec_array1_str(title_data);
  discriptive_data.clear();

  coh_elastic_ene_data.clear();
  coh_elastic_e_xs_data.clear();
  incoh_elastic_ene_data.clear();
  incoh_elastic_xs_data.clear();
  clr_obj.clear_vec_array2_real(incoh_elastic_scat_angle);

  inelastic_ene_data.clear();
  inelastic_xs_data.clear();
  clr_obj.clear_vec_array2_real(inelastic_second_ene);
  clr_obj.clear_vec_array2_real(inelastic_scat_xs_int);
  clr_obj.clear_vec_array2_real(inelastic_weight);
  clr_obj.clear_vec_array3_real(inelastic_scat_xs_weight);

  clear_ace_pointer_data();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterAceDataWriter::clear_ace_pointer_data()
{
  len2  = 0;
  idpni = 0;
  nil   = 0;
  nieb  = 0;
  idpnc = 0;
  ncl   = 0;
  ncli  = 0;
  ifeng = 0;
  itie  = 0;
  itix  = 0;
  itxe  = 0;
  itce  = 0;
  itcx  = 0;
  itca  = 0;
  itcei = 0;
  itcxi = 0;
  itcai = 0;
  nie   = 0;
  nee   = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterAceDataWriter::copy_thermal_scat_ace_data()
{
  mcnpx_mode_flg   = ace_data_obj.get_mcnpx_mode_flg();

  aw0              = ace_data_obj.get_aw0();
  tz               = ace_data_obj.get_tz();
  title_data       = ace_data_obj.get_title_data();
  discriptive_data = ace_data_obj.get_discriptive_data();

  mod_za           = ace_data_obj.get_mod_za();

  zi_vec           = ace_data_obj.get_zi_vec();
  awr_vec          = ace_data_obj.get_awr_vec();

  //For elastic
  coh_elastic_ene_data     = ace_data_obj.get_coh_elastic_ene_data();
  coh_elastic_e_xs_data    = ace_data_obj.get_coh_elastic_e_xs_data();
  incoh_elastic_ene_data   = ace_data_obj.get_incoh_elastic_ene_data();
  incoh_elastic_xs_data    = ace_data_obj.get_incoh_elastic_xs_data();
  incoh_elastic_scat_angle = ace_data_obj.get_incoh_elastic_scat_angle();

  //For inelastic
  inelastic_ene_data       = ace_data_obj.get_inelastic_ene_data();
  inelastic_xs_data        = ace_data_obj.get_inelastic_xs_data();
  inelastic_second_ene     = ace_data_obj.get_inelastic_second_ene();
  inelastic_scat_xs_int    = ace_data_obj.get_inelastic_scat_xs_int();
  inelastic_weight         = ace_data_obj.get_inelastic_weight();
  inelastic_scat_xs_weight = ace_data_obj.get_inelastic_scat_xs_weight();

  //For pointer data
  len2  = ace_data_obj.get_len2();
  idpni = ace_data_obj.get_idpni();
  nil   = ace_data_obj.get_nil();
  nieb  = ace_data_obj.get_nieb();
  idpnc = ace_data_obj.get_idpnc();
  ncl   = ace_data_obj.get_ncl();
  ifeng = ace_data_obj.get_ifeng();
  ncli  = ace_data_obj.get_ncli();
  itie  = ace_data_obj.get_itie();
  itix  = ace_data_obj.get_itix();
  itxe  = ace_data_obj.get_itxe();
  itce  = ace_data_obj.get_itce();
  itcx  = ace_data_obj.get_itcx();
  itca  = ace_data_obj.get_itca();
  itcei = ace_data_obj.get_itcei();
  itcxi = ace_data_obj.get_itcxi();
  itcai = ace_data_obj.get_itcai();
  nie   = ace_data_obj.get_nie();
  nee   = ace_data_obj.get_nee();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterAceDataWriter::copy_thermal_scat_ace_pointer_data
                                   (ThermalScatterAceDataObject& thermal_scat_ace_data_obj)
{
  thermal_scat_ace_data_obj.set_len2(len2);
  thermal_scat_ace_data_obj.set_idpni(idpni);
  thermal_scat_ace_data_obj.set_nil(nil);
  thermal_scat_ace_data_obj.set_nieb(nieb);
  thermal_scat_ace_data_obj.set_idpnc(idpnc);
  thermal_scat_ace_data_obj.set_ncl(ncl);
  thermal_scat_ace_data_obj.set_ifeng(ifeng);
  thermal_scat_ace_data_obj.set_ncl(ncli);
  thermal_scat_ace_data_obj.set_itie(itie);
  thermal_scat_ace_data_obj.set_itix(itix);
  thermal_scat_ace_data_obj.set_itxe(itxe);
  thermal_scat_ace_data_obj.set_itce(itce);
  thermal_scat_ace_data_obj.set_itcx(itcx);
  thermal_scat_ace_data_obj.set_itca(itca);
  thermal_scat_ace_data_obj.set_itcei(itcei);
  thermal_scat_ace_data_obj.set_itcxi(itcxi);
  thermal_scat_ace_data_obj.set_itcai(itcai);
  thermal_scat_ace_data_obj.set_nie(nie);
  thermal_scat_ace_data_obj.set_nee(nee);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Integer ThermalScatterAceDataWriter::get_line_no()
{
  return ace_wri_obj.get_data_count_total() / 4;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterAceDataWriter::write_dir_data(string dir_name)
{
  ofstream fout_dir;
  fout_dir.open(dir_name.c_str());

  if( fout_dir.fail() )
  {
    string class_name = "ThermalScatterAceDataWriter";
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

string ThermalScatterAceDataWriter::get_dir_data()
{
  if( set_data_flg != 1 )
  {
    check_set_data();
    copy_thermal_scat_ace_data();

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

void ThermalScatterAceDataWriter::write_ace_format()
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

    string class_name = "ThermalScatterAceDataWriter";
    string func_name  = "write_ace_format()";
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  check_set_data();
  copy_thermal_scat_ace_data();

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

vector<string> ThermalScatterAceDataWriter::get_ace_text_data()
{
  vector<string> text_data;
  text_data.clear();

  if( set_data_flg == 1 )
  {
    return text_data;
  }
  set_data_flg = 1;

  check_set_data();
  copy_thermal_scat_ace_data();

  ace_wri_obj.clear();
  ace_wri_obj.set_output_data_opt(ace_wri_obj.string_data_mode);

  output_ace_format_header();
  output_ace_format_inelastic();
  output_ace_format_elastic();
  ace_wri_obj.output_storage_data();

  text_data = ace_wri_obj.get_output_data();
  ace_wri_obj.clear();

  return text_data;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterAceDataWriter::get_ace_data_for_mg(vector<string>& title_vec, vector<int>& izaw_vec,
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
  copy_thermal_scat_ace_data();
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
  nxs_vec.push_back(idpni);
  nxs_vec.push_back(nil);
  nxs_vec.push_back(nieb);
  nxs_vec.push_back(idpnc);
  nxs_vec.push_back(ncl);
  nxs_vec.push_back(ifeng);
  nxs_vec.push_back(ncli);

  for(int i=0; i<8; i++)
  {
    nxs_vec.push_back(0);
  }

  //Get jxs_vec
  jxs_vec.clear();
  jxs_vec.push_back(itie);
  jxs_vec.push_back(itix);
  jxs_vec.push_back(itxe);
  jxs_vec.push_back(itce);
  jxs_vec.push_back(itcx);
  jxs_vec.push_back(itca);
  jxs_vec.push_back(itcei);
  jxs_vec.push_back(itcxi);
  jxs_vec.push_back(itcai);

  for(int i=0; i<23; i++)
  {
    jxs_vec.push_back(0);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

vector<double> ThermalScatterAceDataWriter::get_xss_data()
{
  vector<double> xss_data;
  xss_data.clear();

  if( set_data_flg == 1 )
  {
    return xss_data;
  }
  set_data_flg = 1;

  check_set_data();
  copy_thermal_scat_ace_data();

  ace_wri_obj.clear();
  ace_wri_obj.set_output_data_opt(ace_wri_obj.real_vec_mode);

  output_ace_format_header();
  output_ace_format_inelastic();
  output_ace_format_elastic();
  ace_wri_obj.output_storage_data();

  xss_data = ace_wri_obj.get_xss_data();
  ace_wri_obj.clear();

  return xss_data;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterAceDataWriter::output_ace_format()
{
  ace_wri_obj.clear();
  ace_wri_obj.set_file_name(ace_file_name);

  pointer_data_count = ace_wri_obj.get_data_count_total();
  ace_wri_obj.clear_data_count_total();

  output_ace_format_header();
  output_ace_format_inelastic();
  output_ace_format_elastic();

  ace_wri_obj.output_storage_data();
  ace_wri_obj.close_file();
  ace_wri_obj.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterAceDataWriter::output_ace_format_header()
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
  pointer_vec.push_back(idpni);
  pointer_vec.push_back(nil);
  pointer_vec.push_back(nieb);
  pointer_vec.push_back(idpnc);
  pointer_vec.push_back(ncl);
  pointer_vec.push_back(ifeng);
  pointer_vec.push_back(ncli); //Add for LTHR=3 (mixed elastic)
  
  for(int i=0; i<8; i++)
  {
    pointer_vec.push_back(0);
  }
  
  pointer_vec.push_back(itie);
  pointer_vec.push_back(itix);
  pointer_vec.push_back(itxe);
  pointer_vec.push_back(itce);
  pointer_vec.push_back(itcx);
  pointer_vec.push_back(itca);
  pointer_vec.push_back(itcei); //Add for LTHR=3 (mixed elastic)
  pointer_vec.push_back(itcxi); //Add for LTHR=3 (mixed elastic)
  pointer_vec.push_back(itcai); //Add for LTHR=3 (mixed elastic)
  
  for(int i=0; i<23; i++)
  {
    pointer_vec.push_back(0);
  }

  ace_wri_obj.set_pointer_data(pointer_vec);
  pointer_vec.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterAceDataWriter::output_ace_format_inelastic()
{
  ace_wri_obj.set_table_data(inelastic_ene_data, inelastic_xs_data);

  int i_max = static_cast<int>(inelastic_ene_data.size());
  if( opt_weight <= 1 )
  {
    for(int i=0; i<i_max; i++)
    {
      int j_max = static_cast<int>(inelastic_second_ene[i].size());
      for(int j=0; j<j_max; j++)
      {
        ace_wri_obj.set_real_data(inelastic_second_ene[i][j]);
        ace_wri_obj.set_list_data_without_data_no(inelastic_scat_xs_weight[i][j]);
      }
    }
  }
  else
  {
    Integer index = 1 + 4*static_cast<Integer>(i_max);
    for(int i=0; i<i_max; i++)
    {
      ace_wri_obj.set_int_data(index);

      int ele_no = 0;
      int j_max  = static_cast<int>(inelastic_second_ene[i].size());
      for(int j=0; j<j_max; j++)
      {
        int k_max = static_cast<int>(inelastic_scat_xs_weight[i][j].size());
        ele_no += 3 + k_max;
      }
      index += static_cast<Integer>(ele_no);
    }

    for(int i=0; i<i_max; i++)
    {
      ace_wri_obj.set_int_data(static_cast<Integer>(inelastic_second_ene[i].size()));
    }

    for(int i=0; i<i_max; i++)
    {

      int j_max  = static_cast<int>(inelastic_second_ene[i].size());
      for(int j=0; j<j_max; j++)
      {
        ace_wri_obj.set_real_data(inelastic_second_ene[i][j]);
        ace_wri_obj.set_real_data(inelastic_scat_xs_int[i][j]);
        ace_wri_obj.set_real_data(inelastic_weight[i][j]);
        ace_wri_obj.set_list_data_without_data_no(inelastic_scat_xs_weight[i][j]);
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterAceDataWriter::mod_inelastic_data()
{
  //Modify inelastic data when ifeng and opt_wight is 2 (new format)
  if( opt_weight != 2 )
  {
    return;
  }

  int i_max = static_cast<int>(inelastic_second_ene.size());
  if( i_max == 0 )
  {
    return;
  }

  for(int i=0; i<i_max; i++)
  {
    mod_inelastic_second_ene_data(i);

    int j_max  = static_cast<int>(inelastic_second_ene[i].size());
    for(int j=0; j<j_max; j++)
    {
      mod_inelastic_scat_xs_weight_data(i, j);
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterAceDataWriter::mod_inelastic_second_ene_data(int i)
{
  vector<Real>          second_ene_new, scat_xs_int_new, weight_new;
  vector<vector<Real> > scat_xs_weight_new;

  int j_max  = static_cast<int>(inelastic_second_ene[i].size());
  if( j_max <= 1 )
  {
    return;
  }

  second_ene_new.push_back(inelastic_second_ene[i][0]);
  scat_xs_int_new.push_back(inelastic_scat_xs_int[i][0]);
  weight_new.push_back(inelastic_weight[i][0]);
  scat_xs_weight_new.push_back(inelastic_scat_xs_weight[i][0]);

  Real second_ene_pre = inelastic_second_ene[i][0];
  for(int j=1; j<j_max; j++)
  {
    Real second_ene_cur = inelastic_second_ene[i][j];
    Real second_ene_dif = second_ene_cur - second_ene_pre;
    if( fabs(second_ene_dif) < fabs(min_ene_dif * second_ene_cur) ||
        fabs(second_ene_dif) < min_second_ene_dif_abs )
    {
      continue;
    }

    second_ene_new.push_back(second_ene_cur);
    scat_xs_int_new.push_back(inelastic_scat_xs_int[i][j]);
    weight_new.push_back(inelastic_weight[i][j]);
    scat_xs_weight_new.push_back(inelastic_scat_xs_weight[i][j]);

    second_ene_pre = second_ene_cur;
  }

  inelastic_second_ene[i]     = second_ene_new;
  inelastic_scat_xs_int[i]    = scat_xs_int_new;
  inelastic_weight[i]         = weight_new;
  inelastic_scat_xs_weight[i] = scat_xs_weight_new;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterAceDataWriter::mod_inelastic_scat_xs_weight_data(int i, int j)
{
  //Modify inelastic_scat_xs_weight
  int k_max = static_cast<int>(inelastic_scat_xs_weight[i][j].size());
  for(int k=1; k<k_max; k++)
  {
    Real weight_pre = inelastic_scat_xs_weight[i][j][k-1];
    Real mod_val    = 0.0;
    //Real mod_val    = 1.0E-7;
    //Real mod_val    = 1.0E-4;
    if( weight_pre > 0.0 )
    {
      weight_pre *= 1.0+mod_val;
      if( weight_pre > 1.0 )
      {
        weight_pre = 1.0;
      }
    }
    else if( weight_pre < 0.0 )
    {
      weight_pre *= 1.0-mod_val;
      if( weight_pre < -1.0 )
      {
        weight_pre = -1.0;
      }
    }

    if( inelastic_scat_xs_weight[i][j][k] < weight_pre )
    {
      inelastic_scat_xs_weight[i][j][k] = weight_pre;
    }
  }
  //sort(inelastic_scat_xs_weight[i][j].begin(), inelastic_scat_xs_weight[i][j].end());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterAceDataWriter::output_ace_format_elastic()
{
  if( static_cast<int>(coh_elastic_ene_data.size()) > 0 )
  {
    ace_wri_obj.set_table_data(coh_elastic_ene_data, coh_elastic_e_xs_data);
  }

  int i_max = static_cast<int>(incoh_elastic_ene_data.size());
  if( i_max > 0 )
  {
    ace_wri_obj.set_table_data(incoh_elastic_ene_data, incoh_elastic_xs_data);

    for(int i=0; i<i_max; i++)
    {
      ace_wri_obj.set_list_data_without_data_no(incoh_elastic_scat_angle[i]);
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterAceDataWriter::calc_ace_header_file_data()
{
  idpni = 3;

  //Set ifeng and opt_weight
  if( opt_weight == -1 )
  {
    opt_weight = ifeng;
    if( ifeng == 0 )
    {
      opt_weight = 1;
    }
    else if( ifeng == 1 )
    {
      opt_weight = 0;
    }
  }
  else
  {
    ifeng = 0;
    if( opt_weight == 0 )
    {
      ifeng = 1;
    }
    else if( opt_weight == 2 )
    {
      ifeng = 2;
    }
  }

  //Modify inelastic data
  //mod_inelastic_data();

  Integer nea = 0;
  nie   = static_cast<Integer>(inelastic_ene_data.size());
  nee   = 0;
  if( static_cast<Integer>(coh_elastic_ene_data.size()) > 0 )
  {
    nee = static_cast<Integer>(coh_elastic_ene_data.size());
  }
  else if( static_cast<Integer>(incoh_elastic_ene_data.size()) > 0 )
  {
    nee = static_cast<Integer>(incoh_elastic_ene_data.size());

    string class_name = "ThermalScatterAceDataWriter";
    string func_name  = "calc_ace_header_file_data";
    nea = vec_size_check_obj.vec_size_check_array2_real(class_name, func_name, incoh_elastic_scat_angle);
  }
  itie  = 1;
  itix  = itie + 1 + nie;
  itxe  = itix + nie;
  itce  = 0;
  itcx  = 0;
  itcei = 0;
  itcxi = 0;

  nil   = 0;
  idpnc = 0;
  ncl   = 0;
  ncli  = 0;
  if( nee != 0 )
  {
    idpnc =  4;
    ncl   = -1;
    if( static_cast<int>(incoh_elastic_scat_angle.size()) != 0 )
    {
      if( static_cast<int>(incoh_elastic_scat_angle[0].size()) > 0 )
      {
        if( static_cast<int>(coh_elastic_ene_data.size()) == 0 )
        {
          idpnc = 3;
          ncl   = static_cast<int>(incoh_elastic_scat_angle[0].size()) - 1;
        }
        else
        {
          idpnc = 5;
          ncli  = static_cast<int>(incoh_elastic_scat_angle[0].size()) - 1;
        }
      }
    }
  }

  if( nie != 0 )
  {
    if( static_cast<int>(inelastic_scat_xs_weight[0].size()) > 0 )
    {
      nil = static_cast<int>(inelastic_scat_xs_weight[0][0].size());
    }
  }
  if( ifeng <= 1 )
  {
    nil--;
  }
  else
  {
    nil++;
  }

  len2 = itxe - 1;
  int i_max = static_cast<int>(inelastic_ene_data.size());
  for(int i=0; i<i_max; i++)
  {
    if( opt_weight <= 1 )
    {
      int j_max = static_cast<int>(inelastic_second_ene[i].size());
      len2 += j_max; //inelastic_second_ene
      for(int j=0; j<j_max; j++)
      {
        len2 += static_cast<Integer>(inelastic_scat_xs_weight[i][j].size());
      }
    }
    else
    {
      len2 += 2; //index, inelastic_second_ene

      int j_max = static_cast<int>(inelastic_second_ene[i].size());
      len2 += 3*j_max; //inelastic_second_ene, inelastic_scat_xs_int, inelastic_weight
      for(int j=0; j<j_max; j++)
      {
        len2 += static_cast<Integer>(inelastic_scat_xs_weight[i][j].size());
      }
    }
  }

  //if( ifeng > 1 )
  //{
  //  len2 += 2*nie;
  //}

  if( nee > 0 )
  {
    itce = len2 + 1;
    itcx = itce + nee + 1;
    len2 = itcx + nee - 1;  
  }

  itca  = 0;
  itcai = 0;
  if( idpnc == 5 )
  {
    itcei = len2  + 1;
    itcxi = itcei + nee + 1;
    itcai = itcxi + nee;
    len2  = itcai + nee*nea - 1;
  }
  else if( nee > 0 && nea > 0 )
  {
    itca = itcx + nee;
    len2 = itca + nee*nea - 1;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterAceDataWriter::output_ace_format_binary_mode()
{
  string class_name = "ThermalScatterAceDataWriter";
  string func_name  = "output_ace_format_binary_mode()";
  vector<string> err_com;
  err_com.push_back("This function is not implemented.");
  err_com.push_back("Please use output_ace_format function.");
  err_obj.output_runtime_error(class_name, func_name, err_com);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterAceDataWriter::check_set_data()
{
  vector<string> err_com;
  err_com.clear();

  if( set_ace_data_obj_flg != 1 )
  {
    err_com.push_back("There is no ThermalScatterAceDataObject.");
    err_com.push_back("Please set the ThermalScatterAceDataObject by using set_ace_data_obj method.");
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

  if( opt_weight != -1 )
  {
    if( opt_weight != 0 && opt_weight != 1 && opt_weight != 2 )
    {
      ostringstream oss01;
      oss01 << opt_weight;
      string str_data01 = "Weighting option : " + oss01.str();
      err_com.push_back(str_data01);
      err_com.push_back("The weighting option is only available for 0 (variable),");
      err_com.push_back("1 (constant) or 2 (tabulated).");
      err_com.push_back("");
    }
  }

  if( static_cast<int>(err_com.size()) > 0 )
  {
    string class_name = "ThermalScatterAceDataWriter";
    string func_name  = "check_set_data()";
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//Setter

void ThermalScatterAceDataWriter::set_ace_data_obj(ThermalScatterAceDataObject& data_obj)
{
  set_data_flg         = 0;
  set_ace_data_obj_flg = 1;
  ace_data_obj         = data_obj;
}

void ThermalScatterAceDataWriter::set_opt_out_type(Integer int_val)
{
  set_data_flg = 0;
  opt_out_type    = int_val;
}

void ThermalScatterAceDataWriter::set_opt_weight(Integer int_val)
{
  set_data_flg = 0;
  opt_weight   = int_val;
}

void ThermalScatterAceDataWriter::set_ace_file_name(string str_data)
{
  set_data_flg  = 0;
  ace_file_name = str_data;
  str_data.clear();
}

void ThermalScatterAceDataWriter::set_previous_line_no(Integer int_val)
{
  set_data_flg = 0;
  line_no_pre = int_val;

  if( line_no_pre < 0 )
  {
    string class_name = "ThermalScatterAceDataWriter";
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

ThermalScatterAceDataObject ThermalScatterAceDataWriter::get_ace_data_obj()
{
  if( set_data_flg == 0 && set_ace_data_obj_flg == 1 )
  {
    calc_ace_header_file_data();
    copy_thermal_scat_ace_pointer_data(ace_data_obj);
  }

  return ace_data_obj;
}

Integer ThermalScatterAceDataWriter::get_opt_out_type()
{
  return opt_out_type;
}

Integer ThermalScatterAceDataWriter::get_opt_weight()
{
  return opt_weight;
}

string  ThermalScatterAceDataWriter::get_ace_file_name()
{
  return ace_file_name;
}

Integer ThermalScatterAceDataWriter::get_previous_line_no()
{
  return line_no_pre;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

