#include "EndfUtils/MFxxMTyyyWriter/MF03Writer.hpp"

using namespace frendy;

//constructor
MF03Writer::MF03Writer(void)
{
  clear();
}

//destructor
MF03Writer::~MF03Writer(void)
{ 
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF03Writer::write_endf() 
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
  //QM, QI, LR and sigma
  Integer NR, NP;
  NR = static_cast<Integer>(par_obj.get_NBT_SIG().size());
  NP = static_cast<Integer>(par_obj.get_E_INT_SIG().size());
  str_vec = efw_obj.write_tab1(par_obj.get_QM(), par_obj.get_QI(), 0, par_obj.get_LR(), NR, NP,
                               par_obj.get_NBT_SIG(), par_obj.get_INT_SIG(), 
                               par_obj.get_E_INT_SIG(), par_obj.get_SIG_TAB());

  int i_max = static_cast<int>(str_vec.size());
  for(int i=0; i<i_max; i++)
  {
    text.push_back(str_vec[i]);
  }
  
  line_data = efw_obj.write_mt_end();
  text.push_back(line_data);

  clr_obj.clear_vec_array1_str(str_vec);
  line_data.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF03Writer::clear()
{
  clr_obj.clear_vec_array1_str(text);

  par_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> MF03Writer::get_endf_text_data(MF03Parser& mf03parser_obj)
{
  clear();
  par_obj = mf03parser_obj;

  write_endf();
  return text;
}

