#include "EndfUtils/MFxxMTyyyWriter/MF27Writer.hpp"

using namespace frendy;

//constructor
MF27Writer::MF27Writer(void)
{
  clear();
}

//destructor
MF27Writer::~MF27Writer(void)
{ 
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF27Writer::write_endf() 
{
  clr_obj.clear_vec_array1_str(text);

  string         line_data;
  vector<string> str_vec;
  efw_obj.set_mat_mf_mt(par_obj.get_mat_no(), mf_no, par_obj.get_mt_no());

  //Line No.01
  //ZA, AWR
  line_data = efw_obj.write_cont(par_obj.get_ZA(), par_obj.get_AWR(), 0, 0, 0, 0);
  text.push_back(line_data);


  //Line No.02
  int nbt_no = static_cast<int>(par_obj.get_NBT_H().size());
  int tab_no = static_cast<int>(par_obj.get_H_TAB().size());
  str_vec = efw_obj.write_tab1(0.0, par_obj.get_Z(), 0, 0, nbt_no, tab_no, 
                               par_obj.get_NBT_H(),   par_obj.get_INT_H(),
                               par_obj.get_Q_INT_H(), par_obj.get_H_TAB());

  int i_max = static_cast<int>(str_vec.size());
  for(int i=0; i<i_max; i++)
  {
    text.push_back(str_vec[i]);
  }
  clr_obj.clear_vec_array1_str(str_vec);

  line_data = efw_obj.write_mt_end();
  text.push_back(line_data);
  line_data.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF27Writer::clear()
{
  clr_obj.clear_vec_array1_str(text);

  par_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> MF27Writer::get_endf_text_data(MF27Parser& MF27parser_obj)
{
  clear();
  par_obj = MF27parser_obj;

  write_endf();
  return text;
}

