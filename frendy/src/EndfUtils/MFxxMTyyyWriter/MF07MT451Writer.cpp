#include "EndfUtils/MFxxMTyyyWriter/MF07MT451Writer.hpp"

using namespace frendy;

//constructor
MF07MT451Writer::MF07MT451Writer(void)
{
  clear();
}

//destructor
MF07MT451Writer::~MF07MT451Writer(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF07MT451Writer::write_endf()
{
  clr_obj.clear_vec_array1_str(text);

  string line_data;
  efw_obj.set_mat_mf_mt(par_obj.get_mat_no(), mf_no, mt_no);

  //Line No.01
  //ZA, AWR, LTHR
  line_data = efw_obj.write_cont(par_obj.get_ZA(), par_obj.get_AWR(), par_obj.get_NA(), 0, 0, 0);
  text.push_back(line_data);
  line_data.clear();


  //Line No.02
  vector<Real> e_vec;
  int i_max  = static_cast<int>(par_obj.get_NI());
  int ele_no = 0;
  e_vec.resize(i_max*6);
  for(int i=0; i<i_max; i++)
  {
    e_vec[ele_no+0] = par_obj.get_ZAI()[i];
    e_vec[ele_no+1] = par_obj.get_LISI()[i];
    e_vec[ele_no+2] = par_obj.get_AFI()[i];
    e_vec[ele_no+3] = par_obj.get_AWRI()[i];
    e_vec[ele_no+4] = par_obj.get_SFI()[i];
    e_vec[ele_no+5] = 0.0;
    ele_no += 6;
  }
  ele_no = i_max*6;

  vector<string> str_vec;
  str_vec = efw_obj.write_list(0.0, 0.0, par_obj.get_NAS(), 0, ele_no, par_obj.get_NI(), e_vec);
  for(int i=0; i<static_cast<int>(str_vec.size()); i++)
  {
    text.push_back(str_vec[i]);
  }
  clr_obj.clear_vec_array1_str(str_vec);

  line_data = efw_obj.write_mt_end();
  text.push_back(line_data);
  line_data.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF07MT451Writer::clear()
{
  clr_obj.clear_vec_array1_str(text);

  par_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> MF07MT451Writer::get_endf_text_data(MF07MT451Parser& mf07mt451parser_obj)
{
  clear();
  par_obj = mf07mt451parser_obj;

  write_endf();
  return text;
}
