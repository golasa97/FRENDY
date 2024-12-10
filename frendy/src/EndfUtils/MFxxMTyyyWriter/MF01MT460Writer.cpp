#include "EndfUtils/MFxxMTyyyWriter/MF01MT460Writer.hpp"

using namespace frendy;

//constructor
MF01MT460Writer::MF01MT460Writer(void)
{
  clear();
}

//destructor
MF01MT460Writer::~MF01MT460Writer(void)
{ 
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF01MT460Writer::write_endf() 
{
  clr_obj.clear_vec_array1_str(text);

  string         line_data;
  vector<string> str_vec;
  efw_obj.set_mat_mf_mt(par_obj.get_mat_no(), mf_no, mt_no);

  //Line No.01
  //ZA, AWR, LO, NG
  line_data = efw_obj.write_cont(par_obj.get_ZA(), par_obj.get_AWR(),
                                 par_obj.get_LO(), 0, par_obj.get_NG(), 0);
  text.push_back(line_data);

  if( par_obj.get_LO() == 1 )
  {
    for(int g=0; g<static_cast<int>(par_obj.get_NG()); g++)
    {
      str_vec = efw_obj.write_tab1(par_obj.get_E()[g], 0.0, 0, 0, par_obj.get_NR(),  par_obj.get_NP(),
                                   par_obj.get_NBT_MAP()[g], par_obj.get_INT_MAP()[g],
                                   par_obj.get_T_INT_MAP()[g], par_obj.get_T_MAP()[g]);

      int i_max = static_cast<int>(str_vec.size());
      for(int i=0; i<i_max; i++)
      {
        text.push_back(str_vec[i]);
      }
    }
  }
  else if( par_obj.get_LO() == 2 )
  {
    str_vec = efw_obj.write_list(0.0, 0.0, 0, 0,  par_obj.get_NNF(), 0, par_obj.get_RAMDA());

    int i_max = static_cast<int>(str_vec.size());
    for(int i=0; i<i_max; i++)
    {
      text.push_back(str_vec[i]);
    }
  }

  line_data = efw_obj.write_mt_end();
  text.push_back(line_data);

  line_data.clear();
  clr_obj.clear_vec_array1_str(str_vec);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF01MT460Writer::clear()
{
  clr_obj.clear_vec_array1_str(text);

  par_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> MF01MT460Writer::get_endf_text_data(MF01MT460Parser& mf01mt460parser_obj)
{
  clear();
  par_obj = mf01mt460parser_obj;

  write_endf();
  return text;
}

