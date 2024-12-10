#include "ContinuousEnergyXSUtils/AceDataParser/DosimetryAceDataParser.hpp"

using namespace frendy;

//constructor
DosimetryAceDataParser::DosimetryAceDataParser(void)
{
  clear();
}

//destructor
DosimetryAceDataParser::~DosimetryAceDataParser(void)
{
  clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DosimetryAceDataParser::clear()
{
  ace_read_obj.clear();
  set_data_flg = 0;

  file_name.clear();

  clear_ace_data();

  mcnpx_mode_flg = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DosimetryAceDataParser::clear_ace_data()
{
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

void DosimetryAceDataParser::clear_ace_pointer_data()
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

void DosimetryAceDataParser::copy_dosimetry_ace_data(DosimetryAceDataObject& ace_data_obj)
{
  ace_data_obj.clear();
  
  ace_data_obj.set_mcnpx_mode_flg(mcnpx_mode_flg);

  ace_data_obj.set_aw0(aw0);
  ace_data_obj.set_tz(tz);
  ace_data_obj.set_title_data(title_data);
  ace_data_obj.set_discriptive_data(discriptive_data);

  ace_data_obj.set_zi_vec(zi_vec);
  ace_data_obj.set_awr_vec(awr_vec);

  ace_data_obj.set_reaction_xs_reaction_type(reaction_xs_reaction_type);
  ace_data_obj.set_reaction_xs_pointer(reaction_xs_pointer);
  ace_data_obj.set_reaction_xs_range_data(reaction_xs_range_data);
  ace_data_obj.set_reaction_xs_int_data(reaction_xs_int_data);
  ace_data_obj.set_reaction_xs_ene_data(reaction_xs_ene_data);
  ace_data_obj.set_reaction_xs_data(reaction_xs_data);

  ace_data_obj.set_production_xs_state_no_product(production_xs_state_no_product);
  ace_data_obj.set_production_xs_pointer(production_xs_pointer);
  ace_data_obj.set_production_xs_range_data(production_xs_range_data);
  ace_data_obj.set_production_xs_int_data(production_xs_int_data);
  ace_data_obj.set_production_xs_ene_data(production_xs_ene_data);
  ace_data_obj.set_production_xs_data(production_xs_data);

  //For pointer data
  ace_data_obj.set_len2(len2);
  ace_data_obj.set_za(za);
  ace_data_obj.set_ntr(ntr);
  ace_data_obj.set_lone(lone);
  ace_data_obj.set_mtr(mtr);
  ace_data_obj.set_lsig(lsig);
  ace_data_obj.set_sigd(sigd);
  ace_data_obj.set_end(end);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DosimetryAceDataParser::parse_ace_format()
{
  if( set_data_flg != 0 )
  {
    return;
  }
  set_data_flg = 1;

  parse_ace_format_header();
  parse_ace_format_xs();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DosimetryAceDataParser::parse_ace_format_header()
{
  ace_read_obj.get_title_data(mcnpx_mode_flg, aw0, tz, discriptive_data, title_data);

  ace_read_obj.get_mat_data(zi_vec, awr_vec);

  int         pointer_data_no = 48;
  vector<int> pointer_vec;
  ace_read_obj.get_pointer_data(pointer_data_no, pointer_vec);

  len2  = pointer_vec[0]; 
  za    = pointer_vec[1];
  ntr   = pointer_vec[3];

  int ele_no = 4 + 12;
  lone  = pointer_vec[ele_no];
  mtr   = pointer_vec[ele_no+2];
  lsig  = pointer_vec[ele_no+5];
  sigd  = pointer_vec[ele_no+6];

  ele_no += 7 + 14;
  end   = pointer_vec[ele_no];
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DosimetryAceDataParser::parse_ace_format_xs()
{
  //Read MT number data
  vector<Integer> mt_tot;
  ace_read_obj.get_list_data_without_data_no(ntr, mt_tot);

  Integer mf_pre = 0;
  vector<Integer> mt_prod;

  int i_max  = static_cast<int>(mt_tot.size());
  for(int i=0; i<i_max; i++)
  {
    if( mt_tot[i] < 0 )
    {
      mf_pre += 1000;
      mt_prod.push_back(mf_pre);

      string class_name = "DosimetryAceDataParser";
      string func_name  = "parse_ace_format_xs()";

      ostringstream oss01, oss02, oss03, oss04;
      oss01 << i+1;
      oss02 << i_max;
      oss03 << mt_tot[i];
      oss04 << mf_pre;
      string str_data01 = "Position           : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "MT number          : " + oss03.str();
      string str_data03 = "Modified MT number : " + oss04.str();
      

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back("The MT number is less than 0.");
      err_com.push_back("This MT number is not appropriate.");
      err_com.push_back("FRENDY modified MT number automatically.");
      err_obj.output_caution(class_name, func_name, err_com);
      
    }
    else if( mt_tot[i] < 1000 )
    {
      reaction_xs_reaction_type.push_back(mt_tot[i]);

      if( mf_pre > 0 )
      {
        production_xs_state_no_product.push_back(mt_prod);
        mf_pre = 0;
        mt_prod.clear();
      }
    }
    else
    {
      Integer mf_cur = mt_tot[i] / 1000;
      if( mf_cur > mf_pre )
      {
        mt_prod.push_back(mt_tot[i]);
        mf_pre = mf_cur;
      }
      else
      {
        production_xs_state_no_product.push_back(mt_prod);
        mt_prod.clear();

        mt_prod.push_back(mt_tot[i]);
        mf_pre = mf_cur;
      }
    }
  }
  mt_tot.clear();

  if( static_cast<int>(mt_prod.size()) > 0 )
  {
    production_xs_state_no_product.push_back(mt_prod);
    mt_prod.clear();
  }


  //Read pointer data
  i_max = static_cast<int>(reaction_xs_reaction_type.size());
  ace_read_obj.get_list_data_without_data_no(i_max, reaction_xs_pointer);

  i_max = static_cast<int>(production_xs_state_no_product.size());
  production_xs_pointer.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(production_xs_state_no_product[i].size());
    ace_read_obj.get_list_data_without_data_no(j_max, production_xs_pointer[i]);
  }

  //Read xs data for reaction xs
  i_max = static_cast<int>(reaction_xs_reaction_type.size());
  reaction_xs_range_data.resize(i_max);
  reaction_xs_int_data.resize(i_max);
  reaction_xs_ene_data.resize(i_max);
  reaction_xs_data.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    ace_read_obj.get_table_data(reaction_xs_range_data[i], reaction_xs_int_data[i],
                                reaction_xs_ene_data[i],   reaction_xs_data[i]);
  }

  //Read xs data for production xs
  i_max = static_cast<int>(production_xs_state_no_product.size());
  production_xs_range_data.resize(i_max);
  production_xs_int_data.resize(i_max);
  production_xs_ene_data.resize(i_max);
  production_xs_data.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(production_xs_state_no_product[i].size());
    production_xs_range_data[i].resize(j_max);
    production_xs_int_data[i].resize(j_max);
    production_xs_ene_data[i].resize(j_max);
    production_xs_data[i].resize(j_max);
    for(int j=0; j<j_max; j++)
    {
      ace_read_obj.get_table_data(production_xs_range_data[i][j], production_xs_int_data[i][j],
                                  production_xs_ene_data[i][j],   production_xs_data[i][j]);
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DosimetryAceDataParser::set_file_name(string& str_data)
{
  set_data_flg = 0;

  file_name = str_data;

  ace_read_obj.clear();
  ace_read_obj.set_file_name(file_name);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DosimetryAceDataParser::set_text_data(vector<string>& str_vec)
{
  set_data_flg = 0;

  ace_read_obj.clear();
  ace_read_obj.set_text_data(str_vec);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

DosimetryAceDataObject DosimetryAceDataParser::get_ace_data_obj()
{
  if( set_data_flg == 0 )
  {
    parse_ace_format();
  }

  DosimetryAceDataObject ace_data_obj;
  copy_dosimetry_ace_data(ace_data_obj);

  return ace_data_obj;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

string DosimetryAceDataParser::get_file_name()
{
  return file_name;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

