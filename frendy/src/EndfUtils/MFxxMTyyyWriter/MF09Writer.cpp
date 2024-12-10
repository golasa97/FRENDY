#include "EndfUtils/MFxxMTyyyWriter/MF09Writer.hpp"

using namespace frendy;

//constructor
MF09Writer::MF09Writer(void)
{
  clear();
}

//destructor
MF09Writer::~MF09Writer(void)
{ 
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF09Writer::write_endf() 
{
  clr_obj.clear_vec_array1_str(text);

  string         line_data;
  vector<string> str_vec;
  efw_obj.set_mat_mf_mt(par_obj.get_mat_no(), mf_no, par_obj.get_mt_no());

  //Line No.01
  //ZA, AWR, LIS, NS
  line_data = efw_obj.write_cont(par_obj.get_ZA(), par_obj.get_AWR(),
                                 par_obj.get_LIS(), 0, par_obj.get_NS(), 0);
  text.push_back(line_data);

  int i_max = static_cast<int>(par_obj.get_NS());
  for(int i=0; i<i_max; i++)
  {
    int nbt_no = static_cast<int>(par_obj.get_NBT_Y()[i].size());
    int vec_no = static_cast<int>(par_obj.get_Y_TAB()[i].size());
    str_vec = efw_obj.write_tab1(par_obj.get_QM()[i],      par_obj.get_QI()[i],
                                 par_obj.get_IZAP()[i],    par_obj.get_LFS()[i], nbt_no, vec_no,
                                 par_obj.get_NBT_Y()[i],   par_obj.get_INT_Y()[i],
                                 par_obj.get_E_INT_Y()[i], par_obj.get_Y_TAB()[i]);
    int j_max = static_cast<int>(str_vec.size());
    for(int j=0; j<j_max; j++)
    {
      text.push_back(str_vec[j]);
    }
  }

  line_data = efw_obj.write_mt_end();
  text.push_back(line_data);

  clr_obj.clear_vec_array1_str(str_vec);
  line_data.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF09Writer::clear()
{
  clr_obj.clear_vec_array1_str(text);

  par_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> MF09Writer::get_endf_text_data(MF09Parser& mf09parser_obj)
{
  clear();
  par_obj = mf09parser_obj;

  write_endf();
  return text;
}

