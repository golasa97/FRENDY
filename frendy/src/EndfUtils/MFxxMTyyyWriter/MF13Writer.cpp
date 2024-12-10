#include "EndfUtils/MFxxMTyyyWriter/MF13Writer.hpp"

using namespace frendy;

//constructor
MF13Writer::MF13Writer(void)
{
  clear();
}

//destructor
MF13Writer::~MF13Writer(void)
{ 
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF13Writer::write_endf() 
{
  clr_obj.clear_vec_array1_str(text);

  string         line_data;
  vector<string> str_vec;
  efw_obj.set_mat_mf_mt(par_obj.get_mat_no(), mf_no, par_obj.get_mt_no());

  //Line No.01
  //ZA, AWR, NK
  line_data = efw_obj.write_cont(par_obj.get_ZA(), par_obj.get_AWR(), 
                                 0, 0, par_obj.get_NK(), 0);
  text.push_back(line_data);

  if( par_obj.get_NK() > 1 )
  {
    Integer NR = static_cast<Integer>(par_obj.get_NBT_S_TOT().size());
    Integer NP = static_cast<Integer>(par_obj.get_E_INT_S_TOT().size());

    str_vec = efw_obj.write_tab1(0.0, 0.0, 0, 0, NR, NP,
                                 par_obj.get_NBT_S_TOT(),   par_obj.get_INT_S_TOT(),
                                 par_obj.get_E_INT_S_TOT(), par_obj.get_S_TOT_TAB());

    int j_max = static_cast<int>(str_vec.size());
    for(int j=0; j<j_max; j++)
    {
      text.push_back(str_vec[j]);
    }
  }

  int int_max = static_cast<int>(par_obj.get_NK());
  vector<vector<Integer> > nbt_s_k   = par_obj.get_NBT_S_K();
  vector<vector<Integer> > int_s_k   = par_obj.get_INT_S_K();
  vector<vector<Real> >    e_int_s_k = par_obj.get_E_INT_S_K();
  vector<vector<Real> >    s_k_tab   = par_obj.get_S_K_TAB();
  for(int i=0; i<int_max; i++)
  {
    Integer NR = static_cast<Integer>(nbt_s_k[i].size());
    Integer NP = static_cast<Integer>(e_int_s_k[i].size());

    str_vec = efw_obj.write_tab1(par_obj.get_EG()[i],        par_obj.get_ES()[i], 
                                 par_obj.get_LP()[i],        par_obj.get_LF()[i], NR, NP,
                                 nbt_s_k[i], int_s_k[i], e_int_s_k[i], s_k_tab[i]);

    int j_max = static_cast<int>(str_vec.size());
    for(int j=0; j<j_max; j++)
    {
      text.push_back(str_vec[j]);
    }
  }
  clr_obj.clear_vec_array1_str(str_vec);
  clr_obj.clear_vec_array2_int(nbt_s_k);
  clr_obj.clear_vec_array2_int(int_s_k);
  clr_obj.clear_vec_array2_real(e_int_s_k);
  clr_obj.clear_vec_array2_real(s_k_tab);

  line_data = efw_obj.write_mt_end();
  text.push_back(line_data);
  line_data.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF13Writer::clear()
{
  clr_obj.clear_vec_array1_str(text);

  par_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> MF13Writer::get_endf_text_data(MF13Parser& mf13parser_obj)
{
  clear();
  par_obj = mf13parser_obj;

  write_endf();
  return text;
}

