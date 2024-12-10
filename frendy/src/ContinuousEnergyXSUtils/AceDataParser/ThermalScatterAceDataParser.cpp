#include "ContinuousEnergyXSUtils/AceDataParser/ThermalScatterAceDataParser.hpp"

using namespace frendy;

//constructor
ThermalScatterAceDataParser::ThermalScatterAceDataParser(void)
{
  clear();
}

//destructor
ThermalScatterAceDataParser::~ThermalScatterAceDataParser(void)
{
  clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterAceDataParser::clear()
{
  ace_read_obj.clear();
  set_data_flg = 0;

  file_name.clear();

  clear_ace_data();

  mcnpx_mode_flg = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterAceDataParser::clear_ace_data()
{
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

void ThermalScatterAceDataParser::clear_ace_pointer_data()
{
  len2  = 0;
  idpni = 0;
  nil   = 0;
  nieb  = 0;
  idpnc = 0;
  ncl   = 0;
  ifeng = 0;
  ncli  = 0;
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

void ThermalScatterAceDataParser::copy_thermal_scat_ace_data(ThermalScatterAceDataObject& ace_data_obj)
{
  ace_data_obj.clear();
  
  ace_data_obj.set_mcnpx_mode_flg(mcnpx_mode_flg);

  ace_data_obj.set_aw0(aw0);
  ace_data_obj.set_tz(tz);
  ace_data_obj.set_title_data(title_data);
  ace_data_obj.set_discriptive_data(discriptive_data);

  ace_data_obj.set_zi_vec(zi_vec);
  ace_data_obj.set_awr_vec(awr_vec);

  //For elastic
  ace_data_obj.set_coh_elastic_ene_data(coh_elastic_ene_data);
  ace_data_obj.set_coh_elastic_e_xs_data(coh_elastic_e_xs_data);
  ace_data_obj.set_incoh_elastic_ene_data(incoh_elastic_ene_data);
  ace_data_obj.set_incoh_elastic_xs_data(incoh_elastic_xs_data);
  ace_data_obj.set_incoh_elastic_scat_angle(incoh_elastic_scat_angle);

  //For inelastic
  ace_data_obj.set_inelastic_ene_data(inelastic_ene_data);
  ace_data_obj.set_inelastic_xs_data(inelastic_xs_data);
  ace_data_obj.set_inelastic_second_ene(inelastic_second_ene);
  ace_data_obj.set_inelastic_scat_xs_int(inelastic_scat_xs_int);
  ace_data_obj.set_inelastic_weight(inelastic_weight);
  ace_data_obj.set_inelastic_scat_xs_weight(inelastic_scat_xs_weight);

  //For pointer data
  ace_data_obj.set_len2(len2);
  ace_data_obj.set_idpni(idpni);
  ace_data_obj.set_nil(nil);
  ace_data_obj.set_nieb(nieb);
  ace_data_obj.set_idpnc(idpnc);
  ace_data_obj.set_ncl(ncl);
  ace_data_obj.set_ifeng(ifeng);
  ace_data_obj.set_ncli(ncli);
  ace_data_obj.set_itie(itie);
  ace_data_obj.set_itix(itix);
  ace_data_obj.set_itxe(itxe);
  ace_data_obj.set_itce(itce);
  ace_data_obj.set_itcx(itcx);
  ace_data_obj.set_itca(itca);
  ace_data_obj.set_itce(itcei);
  ace_data_obj.set_itcx(itcxi);
  ace_data_obj.set_itca(itcai);
  ace_data_obj.set_nie(nie);
  ace_data_obj.set_nee(nee);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterAceDataParser::parse_ace_format()
{
  if( set_data_flg != 0 )
  {
    return;
  }
  set_data_flg = 1;

  parse_ace_format_header();
  parse_ace_format_inelastic();
  parse_ace_format_elastic();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterAceDataParser::parse_ace_format_header()
{
  ace_read_obj.get_title_data(mcnpx_mode_flg, aw0, tz, discriptive_data, title_data);

  ace_read_obj.get_mat_data(zi_vec, awr_vec);

  vector<int> nxsd, jxsd;
  int nxsd_no =  8;
  int jxsd_no = 23;
  nxsd.resize(nxsd_no);
  jxsd.resize(jxsd_no);

  int         pointer_data_no = 13 + nxsd_no + jxsd_no; //=48
  vector<int> pointer_vec;
  ace_read_obj.get_pointer_data(pointer_data_no, pointer_vec);

  len2  = pointer_vec[0]; 
  idpni = pointer_vec[1];
  nil   = pointer_vec[2];
  nieb  = pointer_vec[3];
  idpnc = pointer_vec[4];
  ncl   = pointer_vec[5];
  ifeng = pointer_vec[6];
  ncli  = pointer_vec[7];

  int ele_no = 8;
  for(int i=0; i<nxsd_no; i++)
  {
    nxsd[i] = pointer_vec[ele_no];
    ele_no++;
  }
  nxsd.clear();

  itie  = pointer_vec[ele_no];
  itix  = pointer_vec[ele_no+1];
  itxe  = pointer_vec[ele_no+2];
  itce  = pointer_vec[ele_no+3];
  itcx  = pointer_vec[ele_no+4];
  itca  = pointer_vec[ele_no+5];
  itcei = pointer_vec[ele_no+6];
  itcxi = pointer_vec[ele_no+7];
  itcai = pointer_vec[ele_no+8];

  ele_no += 9;
  for(int i=0; i<jxsd_no; i++)
  {
    jxsd[i] = pointer_vec[ele_no];
    ele_no++;
  }
  jxsd.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterAceDataParser::parse_ace_format_inelastic()
{
  ace_read_obj.get_table_data(inelastic_ene_data, inelastic_xs_data);

  int i_max = inelastic_ene_data.size();
  if( ifeng <= 1 )
  {
    inelastic_second_ene.resize(i_max);
    inelastic_scat_xs_weight.resize(i_max);
    for(int i=0; i<i_max; i++)
    {
      inelastic_second_ene[i].resize(nieb);
      inelastic_scat_xs_weight[i].resize(nieb);
      for(int j=0; j<nieb; j++)
      {
        inelastic_second_ene[i][j] = ace_read_obj.get_real_data();
        ace_read_obj.get_list_data_without_data_no(nil+1, inelastic_scat_xs_weight[i][j]);
      }
    }
  }
  else
  {
    vector<Integer> index, second_ene_no;
    index.resize(i_max);
    for(int i=0; i<i_max; i++)
    {
      index[i] = static_cast<Integer>(round(ace_read_obj.get_real_data()));
    }
    for(int i=i_max-1; i>0; i--)
    {
      index[i] -= index[i-1];
    }
    index[0] -= 1 + 4*static_cast<Integer>(i_max);

    second_ene_no.resize(i_max);
    for(int i=0; i<i_max; i++)
    {
      Real real_val = ace_read_obj.get_real_data();
      second_ene_no[i] = static_cast<Integer>(round(real_val));
    }

    int j_max = 0;
    int k_max = 0;
    inelastic_second_ene.resize(i_max);
    inelastic_scat_xs_int.resize(i_max);
    inelastic_weight.resize(i_max);
    inelastic_scat_xs_weight.resize(i_max);
    for(int i=0; i<i_max; i++)
    {
      j_max = static_cast<int>(second_ene_no[i]);
      inelastic_second_ene[i].resize(j_max);
      inelastic_scat_xs_int[i].resize(j_max);
      inelastic_weight[i].resize(j_max);
      inelastic_scat_xs_weight[i].resize(j_max);

      if( i==0 )
      {
        k_max = static_cast<int>(index[i+1]/second_ene_no[i] - 3);
      }
      for(int j=0; j<j_max; j++)
      {
        inelastic_second_ene[i][j]  = ace_read_obj.get_real_data();
        inelastic_scat_xs_int[i][j] = ace_read_obj.get_real_data();
        inelastic_weight[i][j]      = ace_read_obj.get_real_data();

        ace_read_obj.get_list_data_without_data_no(k_max, inelastic_scat_xs_weight[i][j]);
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterAceDataParser::parse_ace_format_elastic()
{
  if( itce != 0 )
  {
    if( ncl == -1 && ncli == 0 )
    {
      //Cohelent elastic
      ace_read_obj.get_table_data(coh_elastic_ene_data, coh_elastic_e_xs_data);
    }
    else if( ncli == 0 )
    {
      //Incohelent elastic
      ace_read_obj.get_table_data(incoh_elastic_ene_data, incoh_elastic_xs_data);

      int i_max = static_cast<int>(incoh_elastic_ene_data.size());
      incoh_elastic_scat_angle.resize(i_max);
      for(int i=0; i<i_max; i++)
      {
        ace_read_obj.get_list_data_without_data_no(ncl+1, incoh_elastic_scat_angle[i]);
      }
    }
    else
    {
      //Cohelent elastic
      ace_read_obj.get_table_data(coh_elastic_ene_data, coh_elastic_e_xs_data);

      //Incohelent elastic
      ace_read_obj.get_table_data(incoh_elastic_ene_data, incoh_elastic_xs_data);

      int i_max = static_cast<int>(incoh_elastic_ene_data.size());
      incoh_elastic_scat_angle.resize(i_max);
      for(int i=0; i<i_max; i++)
      {
        ace_read_obj.get_list_data_without_data_no(ncl+1, incoh_elastic_scat_angle[i]);
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterAceDataParser::set_file_name(string& str_data)
{
  set_data_flg = 0;

  file_name = str_data;

  ace_read_obj.clear();
  ace_read_obj.set_file_name(file_name);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterAceDataParser::set_text_data(vector<string>& str_vec)
{
  set_data_flg = 0;

  ace_read_obj.clear();
  ace_read_obj.set_text_data(str_vec);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

ThermalScatterAceDataObject ThermalScatterAceDataParser::get_ace_data_obj()
{
  if( set_data_flg == 0 )
  {
    parse_ace_format();
  }

  ThermalScatterAceDataObject ace_data_obj;
  copy_thermal_scat_ace_data(ace_data_obj);

  return ace_data_obj;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

string ThermalScatterAceDataParser::get_file_name()
{
  return file_name;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

