#include "EndfUtils/MFxxMTyyyWriter/MF15Writer.hpp"

using namespace frendy;

//constructor
MF15Writer::MF15Writer(void)
{
  clear();
}

//destructor
MF15Writer::~MF15Writer(void)
{ 
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF15Writer::write_endf() 
{
  clr_obj.clear_vec_array1_str(text);

  string         line_data;
  vector<string> str_vec;
  efw_obj.set_mat_mf_mt(par_obj.get_mat_no(), mf_no, par_obj.get_mt_no());

  //Line No.01
  //ZA, AWR, NC
  line_data = efw_obj.write_cont(par_obj.get_ZA(), par_obj.get_AWR(), 
                                 0, 0, par_obj.get_NC(), 0);
  text.push_back(line_data);


  int i_max = static_cast<int>(par_obj.get_NC());
  for(int i=0; i<i_max; i++)
  {
    int nbt_no = static_cast<int>(par_obj.get_NBT_P()[i].size());
    int tab_no = static_cast<int>(par_obj.get_P_TAB()[i].size());
    str_vec = efw_obj.write_tab1(0.0, 0.0, 0, par_obj.get_LF()[i], nbt_no, tab_no,
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
  }
  clr_obj.clear_vec_array1_str(str_vec);

  line_data = efw_obj.write_mt_end();
  text.push_back(line_data);
  line_data.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF15Writer::write_lf01(int i) 
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


  j_max = static_cast<int>(par_obj.get_NE_LF01()[i]);
  for(int j=0; j<j_max; j++)
  {
        nbt_no = static_cast<int>(par_obj.get_NBT_G_LF01()[i][j].size());
    int tab_no = static_cast<int>(par_obj.get_G_TAB_LF01()[i][j].size());
    str_vec = efw_obj.write_tab1(0.0, par_obj.get_E_LF01()[i][j], 0, 0, nbt_no, tab_no,
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

void MF15Writer::write_lf05(int i) 
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

void MF15Writer::write_lf07(int i) 
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
  clr_obj.clear_vec_array1_str(str_vec);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF15Writer::clear()
{
  clr_obj.clear_vec_array1_str(text);

  par_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> MF15Writer::get_endf_text_data(MF15Parser& MF15parser_obj)
{
  clear();
  par_obj = MF15parser_obj;

  write_endf();
  return text;
}

