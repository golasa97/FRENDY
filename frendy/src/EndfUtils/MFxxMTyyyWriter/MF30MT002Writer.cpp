#include "EndfUtils/MFxxMTyyyWriter/MF30MT002Writer.hpp"

using namespace frendy;

//constructor
MF30MT002Writer::MF30MT002Writer(void)
{
  clear();
}

//destructor
MF30MT002Writer::~MF30MT002Writer(void)
{ 
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF30MT002Writer::write_endf() 
{
  clr_obj.clear_vec_array1_str(text);

  string         line_data;
  vector<string> str_vec;
  efw_obj.set_mat_mf_mt(par_obj.get_mat_no(), mf_no, mt_no);

  //Line No.01
  //ZA, AWR, NP
  line_data = efw_obj.write_cont(par_obj.get_ZA(), par_obj.get_AWR(), 0, 0, 0, par_obj.get_NP());
  text.push_back(line_data);


  int i_max = static_cast<int>(par_obj.get_NP());
  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(par_obj.get_R_COV()[i].size());
    str_vec = efw_obj.write_list(par_obj.get_PARM()[i], 0.0, 0, 0, j_max, 0, par_obj.get_R_COV()[i]);

    j_max = static_cast<int>(str_vec.size());
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

void MF30MT002Writer::clear()
{
  clr_obj.clear_vec_array1_str(text);

  par_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> MF30MT002Writer::get_endf_text_data(MF30MT002Parser& MF30MT002parser_obj)
{
  clear();
  par_obj = MF30MT002parser_obj;

  write_endf();
  return text;
}

