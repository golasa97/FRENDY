#include "EndfUtils/MFxxMTyyyWriter/MF26Writer.hpp"

using namespace frendy;

//constructor
MF26Writer::MF26Writer(void)
{
  clear();
}

//destructor
MF26Writer::~MF26Writer(void)
{ 
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF26Writer::write_endf() 
{
  clr_obj.clear_vec_array1_str(text);

  string         line_data;
  vector<string> str_vec;
  efw_obj.set_mat_mf_mt(par_obj.get_mat_no(), mf_no, par_obj.get_mt_no());

  //Line No.01
  //ZA, AWR, NK
  line_data = efw_obj.write_cont(par_obj.get_ZA(), par_obj.get_AWR(), 0, 0, par_obj.get_NK(), 0);
  text.push_back(line_data);


  int i_max = static_cast<int>(par_obj.get_NK());
  for(int i=0; i<i_max; i++)
  {
    int nbt_no = static_cast<int>(par_obj.get_NBT_Y()[i].size());
    int tab_no = static_cast<int>(par_obj.get_Y_TAB()[i].size());
    str_vec = efw_obj.write_tab1(par_obj.get_ZAP()[i], 0.0, 0, par_obj.get_LAW()[i], nbt_no, tab_no, 
                                 par_obj.get_NBT_Y()[i],   par_obj.get_INT_Y()[i],
                                 par_obj.get_E_INT_Y()[i], par_obj.get_Y_TAB()[i]);

    int j_max = static_cast<int>(str_vec.size());
    for(int j=0; j<j_max; j++)
    {
      text.push_back(str_vec[j]);
    }

    if( par_obj.get_LAW()[i] == 1 )
    {
      write_law01(i);
    }
    else if( par_obj.get_LAW()[i] == 2 )
    {
      write_law02(i);
    }
    else if( par_obj.get_LAW()[i] == 8 )
    {
      write_law08(i);
    }
  }
  clr_obj.clear_vec_array1_str(str_vec);

  line_data = efw_obj.write_mt_end();
  text.push_back(line_data);
  line_data.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF26Writer::write_law01(int i)
{
  vector<string> str_vec;

  int nbt_no = static_cast<int>(par_obj.get_NBT_E_LAW01()[i].size());
  str_vec = efw_obj.write_tab2(0.0, 0.0, par_obj.get_LANG_LAW01()[i], par_obj.get_LEP_LAW01()[i],
                               nbt_no, par_obj.get_NE_LAW01()[i], 
                               par_obj.get_NBT_E_LAW01()[i], par_obj.get_INT_E_LAW01()[i]);

  int j_max = static_cast<int>(str_vec.size());
  for(int j=0; j<j_max; j++)
  {
    text.push_back(str_vec[j]);
  }

  j_max = static_cast<int>(par_obj.get_NE_LAW01()[i]);
  for(int j=0; j<j_max; j++)
  {
    int nep   = static_cast<int>(par_obj.get_B_LAW01()[i][j].size());
    int na    = static_cast<int>(par_obj.get_B_LAW01()[i][j][0].size()) - 1;
    int k_max = nep * (na+2);
  
    vector<Real> list_vec;
    list_vec.resize(k_max);
    int ele_no = 0;
    for(int k=0; k<nep; k++)
    {
      list_vec[ele_no] = par_obj.get_E2_LAW01()[i][j][k];
      ele_no++;

      for(int l=0; l<na+1; l++)
      {
        list_vec[ele_no] = par_obj.get_B_LAW01()[i][j][k][l];
        ele_no++;
      }
    }
  
    str_vec = efw_obj.write_list(0.0, par_obj.get_E1_LAW01()[i][j], par_obj.get_ND_LAW01()[i][j],
                                 na, k_max, nep, list_vec);
    
    k_max = static_cast<int>(str_vec.size());
    for(int k=0; k<k_max; k++)
    {
      text.push_back(str_vec[k]);
    }
  }
  clr_obj.clear_vec_array1_str(str_vec);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF26Writer::write_law02(int i)
{
  vector<string> str_vec;

  int nbt_no = static_cast<int>(par_obj.get_NBT_E_LAW02()[i].size());
  str_vec = efw_obj.write_tab2(0.0, 0.0, 0, 0, nbt_no, par_obj.get_NE_LAW02()[i], 
                               par_obj.get_NBT_E_LAW02()[i], par_obj.get_INT_E_LAW02()[i]);

  int j_max = static_cast<int>(str_vec.size());
  for(int j=0; j<j_max; j++)
  {
    text.push_back(str_vec[j]);
  }

  j_max = static_cast<int>(par_obj.get_NE_LAW02()[i]);
  for(int j=0; j<j_max; j++)
  {
    int          k_max    = static_cast<int>(par_obj.get_A_LAW02()[i][j].size());
    vector<Real> list_vec = par_obj.get_A_LAW02()[i][j];

    str_vec = efw_obj.write_list(0.0, par_obj.get_E_LAW02()[i][j], par_obj.get_LANG_LAW02()[i][j],
                                 0, k_max, par_obj.get_NL_LAW02()[i][j], list_vec);
    
    k_max = static_cast<int>(str_vec.size());
    for(int k=0; k<k_max; k++)
    {
      text.push_back(str_vec[k]);
    }
  }
  clr_obj.clear_vec_array1_str(str_vec);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF26Writer::write_law08(int i)
{
  vector<string> str_vec;

  int nbt_no = static_cast<int>(par_obj.get_NBT_ET_LAW08()[i].size());
  int tab_no = static_cast<int>(par_obj.get_ET_TAB_LAW08()[i].size());
  str_vec = efw_obj.write_tab1(0.0, 0.0, 0, 0, nbt_no, tab_no, 
                               par_obj.get_NBT_ET_LAW08()[i],   par_obj.get_INT_ET_LAW08()[i],
                               par_obj.get_E_INT_ET_LAW08()[i], par_obj.get_ET_TAB_LAW08()[i]);

  int j_max = static_cast<int>(str_vec.size());
  for(int j=0; j<j_max; j++)
  {
    text.push_back(str_vec[j]);
  }
  clr_obj.clear_vec_array1_str(str_vec);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF26Writer::clear()
{
  clr_obj.clear_vec_array1_str(text);

  par_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> MF26Writer::get_endf_text_data(MF26Parser& MF26parser_obj)
{
  clear();
  par_obj = MF26parser_obj;

  write_endf();
  return text;
}

