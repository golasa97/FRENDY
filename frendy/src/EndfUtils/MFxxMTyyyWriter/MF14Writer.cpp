#include "EndfUtils/MFxxMTyyyWriter/MF14Writer.hpp"

using namespace frendy;

//constructor
MF14Writer::MF14Writer(void)
{
  clear();
}

//destructor
MF14Writer::~MF14Writer(void)
{ 
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF14Writer::write_endf() 
{
  clr_obj.clear_vec_array1_str(text);

  string         line_data;
  vector<string> str_vec;
  efw_obj.set_mat_mf_mt(par_obj.get_mat_no(), mf_no, par_obj.get_mt_no());

  if( par_obj.get_LI() == 0 )
  {
    //Line No.01
    //ZA, AWR, LI, LTT, NK, NI
    line_data = efw_obj.write_cont(par_obj.get_ZA(), par_obj.get_AWR(), 
                                   par_obj.get_LI(), par_obj.get_LTT(),
                                   par_obj.get_NK(), par_obj.get_NI());
    text.push_back(line_data);

    if( par_obj.get_LTT() == 1 )
    {
      write_ltt01();
    }
    else if( par_obj.get_LTT() == 2 )
    {
      write_ltt02();
    }
  }
  else if( par_obj.get_LI() == 1 )
  {
    //Line No.01
    //ZA, AWR, LI, NK
    line_data = efw_obj.write_cont(par_obj.get_ZA(), par_obj.get_AWR(), 
                                   par_obj.get_LI(), 0, par_obj.get_NK(), 0);
    text.push_back(line_data);
  }

  line_data = efw_obj.write_mt_end();
  text.push_back(line_data);
  line_data.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF14Writer::write_ltt01() 
{
  string         line_data;
  vector<string> str_vec;

  int i_max = static_cast<int>(par_obj.get_NI());
  for(int i=0; i<i_max; i++)
  {
    line_data = efw_obj.write_cont(par_obj.get_EG()[i], par_obj.get_ES()[i], 0, 0, 0, 0);
    text.push_back(line_data);
  }


  int i_sta = i_max; //NI
      i_max = static_cast<int>(par_obj.get_NK());
  for(int i=i_sta; i<i_max; i++)
  {
    int j_max = static_cast<int>(par_obj.get_NBT_E()[i].size());
    str_vec = efw_obj.write_tab2(par_obj.get_EG()[i], par_obj.get_ES()[i], 0, 0, j_max, par_obj.get_NE()[i],
                                 par_obj.get_NBT_E()[i], par_obj.get_INT_E()[i]);

    j_max = static_cast<int>(str_vec.size());
    for(int j=0; j<j_max; j++)
    {
      text.push_back(str_vec[j]);
    }

    j_max = static_cast<int>(par_obj.get_NE()[i]);
    for(int j=0; j<j_max; j++)
    {
      int k_max = static_cast<int>(par_obj.get_A()[i][j].size());
      str_vec = efw_obj.write_list(0.0, par_obj.get_E()[i][j], 0, 0, k_max, 0,
                                   par_obj.get_A()[i][j]);

      k_max = static_cast<int>(str_vec.size());
      for(int k=0; k<k_max; k++)
      {
        text.push_back(str_vec[k]);
      }
    }
  }

  line_data.clear();
  clr_obj.clear_vec_array1_str(str_vec);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF14Writer::write_ltt02() 
{
  string         line_data;
  vector<string> str_vec;

  int i_max = static_cast<int>(par_obj.get_NI());
  for(int i=0; i<i_max; i++)
  {
    line_data = efw_obj.write_cont(par_obj.get_EG()[i], par_obj.get_ES()[i], 0, 0, 0, 0);
    text.push_back(line_data);
  }


  int i_sta = i_max; //NI
      i_max = static_cast<int>(par_obj.get_NK());
  for(int i=i_sta; i<i_max; i++)
  {
    int j_max = static_cast<int>(par_obj.get_NBT_E()[i].size());
    str_vec = efw_obj.write_tab2(par_obj.get_EG()[i], par_obj.get_ES()[i], 0, 0, j_max, par_obj.get_NE()[i],
                                 par_obj.get_NBT_E()[i], par_obj.get_INT_E()[i]);

    j_max = static_cast<int>(str_vec.size());
    for(int j=0; j<j_max; j++)
    {
      text.push_back(str_vec[j]);
    }

    j_max = static_cast<int>(par_obj.get_NE()[i]);
    for(int j=0; j<j_max; j++)
    {
      int nbt_no = static_cast<int>(par_obj.get_NBT_P()[i][j].size());
      int tab_no = static_cast<int>(par_obj.get_P_TAB()[i][j].size());
      str_vec = efw_obj.write_tab1(0.0, par_obj.get_E()[i][j], 0, 0, nbt_no, tab_no,
                                   par_obj.get_NBT_P()[i][j],    par_obj.get_INT_P()[i][j],
                                   par_obj.get_MU_INT_P()[i][j], par_obj.get_P_TAB()[i][j]);

      int k_max = static_cast<int>(str_vec.size());
      for(int k=0; k<k_max; k++)
      {
        text.push_back(str_vec[k]);
      }
    }
  }

  line_data.clear();
  clr_obj.clear_vec_array1_str(str_vec);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF14Writer::clear()
{
  clr_obj.clear_vec_array1_str(text);

  par_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> MF14Writer::get_endf_text_data(MF14Parser& MF14parser_obj)
{
  clear();
  par_obj = MF14parser_obj;

  write_endf();
  return text;
}

