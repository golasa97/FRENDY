#include "EndfUtils/MFxxMTyyyWriter/MF01MT456Writer.hpp"

using namespace frendy;

//constructor
MF01MT456Writer::MF01MT456Writer(void)
{
  clear();
}

//destructor
MF01MT456Writer::~MF01MT456Writer(void)
{ 
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF01MT456Writer::write_endf() 
{
  clr_obj.clear_vec_array1_str(text);

  string         line_data;
  vector<string> str_vec;
  efw_obj.set_mat_mf_mt(par_obj.get_mat_no(), mf_no, mt_no);

  //Line No.01
  //ZA, AWR, LNU
  line_data = efw_obj.write_cont
	            (par_obj.get_ZA(), par_obj.get_AWR(), 0, par_obj.get_LNU(), 0, 0);
  text.push_back(line_data);

  if( par_obj.get_LNU() == 1 )
  {
    str_vec = efw_obj.write_list(0.0, 0.0, 0, 0, par_obj.get_NC(), 0, par_obj.get_NU());

    int i_max = static_cast<int>(str_vec.size());
    for(int i=0; i<i_max; i++)
    {
      text.push_back(str_vec[i]);
    }
  }
  else if( par_obj.get_LNU() == 2 )
  {
    str_vec = efw_obj.write_tab1(0.0, 0.0, 0, 0, par_obj.get_NR(),  par_obj.get_NP(),
                                 par_obj.get_NBT(),   par_obj.get_INT(),
                                 par_obj.get_E_INT(), par_obj.get_NU());

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

void MF01MT456Writer::clear()
{
  clr_obj.clear_vec_array1_str(text);

  par_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> MF01MT456Writer::get_endf_text_data(MF01MT456Parser& mf01mt456parser_obj)
{
  clear();
  par_obj = mf01mt456parser_obj;

  write_endf();
  return text;
}

