#include "EndfUtils/MFxxMTyyyWriter/MF05Writer.hpp"

using namespace frendy;

//constructor
MF05Writer::MF05Writer(void)
{
  clear();
}

//destructor
MF05Writer::~MF05Writer(void)
{ 
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF05Writer::write_endf() 
{
  clr_obj.clear_vec_array1_str(text);

  string         line_data;
  vector<string> str_vec;
  efw_obj.set_mat_mf_mt(par_obj.get_mat_no(), mf_no, par_obj.get_mt_no());

  //Line No.01
  //ZA, AWR, NK
  line_data = efw_obj.write_cont(par_obj.get_ZA(), par_obj.get_AWR(), 0, 0, par_obj.get_NK(), 0);
  text.push_back(line_data);

  
  for(int i=0; i<static_cast<int>(par_obj.get_NK()); i++)
  {
    //Line No.02
    //LF, p
    int nbt_no = static_cast<int>(par_obj.get_NBT_P()[i].size());
    int p_no   = static_cast<int>(par_obj.get_P_TAB()[i].size());
    str_vec = efw_obj.write_tab1(par_obj.get_U()[i], 0.0, 0, par_obj.get_LF()[i], nbt_no, p_no,
                                 par_obj.get_NBT_P()[i],   par_obj.get_INT_P()[i], 
                                 par_obj.get_E_INT_P()[i], par_obj.get_P_TAB()[i]);
    int j_max = static_cast<int>(str_vec.size());
    for(int j=0; j<j_max; j++)
    {
      text.push_back(str_vec[j]);
    }


    if( par_obj.get_LF()[i] == 1 )
    {
      write_lf01(i);
    }
    else if( par_obj.get_LF()[i] == 5 )
    {
      write_lf05(i);
    }
    else if( par_obj.get_LF()[i] == 7 )
    {
      write_lf07(i);
    }
    else if( par_obj.get_LF()[i] == 9 )
    {
      write_lf07(i);
    }
    else if( par_obj.get_LF()[i] == 11 )
    {
      write_lf05(i);
    }
    else if( par_obj.get_LF()[i] == 12 )
    {
      write_lf07(i);
    }
  }


  line_data = efw_obj.write_mt_end();
  text.push_back(line_data);

  clr_obj.clear_vec_array1_str(str_vec);
  line_data.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF05Writer::write_lf01(int i) 
{
  vector<string> str_vec;

  int nbt_no = static_cast<int>(par_obj.get_NBT_E_LF01()[i].size());
  str_vec = efw_obj.write_tab2(0.0, 0.0, 0, 0, nbt_no, par_obj.get_NE_LF01()[i],
                               par_obj.get_NBT_E_LF01()[i], par_obj.get_INT_E_LF01()[i]);
  int j_max = static_cast<int>(str_vec.size());
  for(int j=0; j<j_max; j++)
  {
    text.push_back(str_vec[j]);
  }


  for(int j=0; j<static_cast<int>(par_obj.get_NE_LF01()[i]); j++)
  {
        nbt_no = static_cast<int>(par_obj.get_NBT_G_LF01()[i][j].size());
    int g_no   = static_cast<int>(par_obj.get_G_TAB_LF01()[i][j].size());
    str_vec = efw_obj.write_tab1(0.0, par_obj.get_E_LF01()[i][j], 0, 0, nbt_no, g_no,
                                 par_obj.get_NBT_G_LF01()[i][j],   par_obj.get_INT_G_LF01()[i][j],
                                 par_obj.get_E_INT_G_LF01()[i][j], par_obj.get_G_TAB_LF01()[i][j]);
    int k_max = static_cast<int>(str_vec.size());
    for(int k=0; k<k_max; k++)
    {
      text.push_back(str_vec[k]);
    }
  }
  clr_obj.clear_vec_array1_str(str_vec);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF05Writer::write_lf05(int i) 
{
  vector<string> str_vec;

  int nbt_no = static_cast<int>(par_obj.get_NBT_S_LF05()[i].size());
  int tab_no = static_cast<int>(par_obj.get_S_TAB_LF05()[i].size());
  str_vec = efw_obj.write_tab1(0.0, 0.0, 0, 0, nbt_no, tab_no,
                               par_obj.get_NBT_S_LF05()[i],   par_obj.get_INT_S_LF05()[i],
                               par_obj.get_E_INT_S_LF05()[i], par_obj.get_S_TAB_LF05()[i]);
  int j_max = static_cast<int>(str_vec.size());
  for(int j=0; j<j_max; j++)
  {
    text.push_back(str_vec[j]);
  }

  nbt_no = static_cast<int>(par_obj.get_NBT_G_LF05()[i].size());
  tab_no = static_cast<int>(par_obj.get_G_TAB_LF05()[i].size());
  str_vec = efw_obj.write_tab1(0.0, 0.0, 0, 0, nbt_no, tab_no,
                               par_obj.get_NBT_G_LF05()[i],   par_obj.get_INT_G_LF05()[i],
                               par_obj.get_E_INT_G_LF05()[i], par_obj.get_G_TAB_LF05()[i]);
  j_max = static_cast<int>(str_vec.size());
  for(int j=0; j<j_max; j++)
  {
    text.push_back(str_vec[j]);
  }
  clr_obj.clear_vec_array1_str(str_vec);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF05Writer::write_lf07(int i) 
{
  vector<string> str_vec;

  int nbt_no = static_cast<int>(par_obj.get_NBT_S_LF07()[i].size());
  int tab_no = static_cast<int>(par_obj.get_S_TAB_LF07()[i].size());
  str_vec = efw_obj.write_tab1(par_obj.get_EFL_LF12()[i], par_obj.get_EFH_LF12()[i], 0, 0, nbt_no, tab_no,
                               par_obj.get_NBT_S_LF07()[i],   par_obj.get_INT_S_LF07()[i],
                               par_obj.get_E_INT_S_LF07()[i], par_obj.get_S_TAB_LF07()[i]);
  int j_max = static_cast<int>(str_vec.size());
  for(int j=0; j<j_max; j++)
  {
    text.push_back(str_vec[j]);
  }
  clr_obj.clear_vec_array1_str(str_vec);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF05Writer::clear()
{
  clr_obj.clear_vec_array1_str(text);

  par_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> MF05Writer::get_endf_text_data(MF05Parser& MF05parser_obj)
{
  clear();
  par_obj = MF05parser_obj;

  write_endf();
  return text;
}

