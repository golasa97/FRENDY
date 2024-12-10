#include "EndfUtils/MFxxMTyyyWriter/MF30MT001Writer.hpp"

using namespace frendy;

//constructor
MF30MT001Writer::MF30MT001Writer(void)
{
  clear();
}

//destructor
MF30MT001Writer::~MF30MT001Writer(void)
{ 
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF30MT001Writer::write_endf() 
{
  clr_obj.clear_vec_array1_str(text);

  string         line_data;
  efw_obj.set_mat_mf_mt(par_obj.get_mat_no(), mf_no, mt_no);

  //Line No.01
  //ZA, AWR, NP
  line_data = efw_obj.write_cont(par_obj.get_ZA(), par_obj.get_AWR(), 0, 0, 0, par_obj.get_NP());
  text.push_back(line_data);

  //Line No.02
  line_data = efw_obj.write_cont(0.0, 0.0, 0, 0, par_obj.get_NDIR(), par_obj.get_NCTAB());
  text.push_back(line_data);


  int i_max = static_cast<int>(par_obj.get_NDIR());
  for(int i=0; i<i_max; i++)
  {
    line_data = efw_obj.write_cont(0.0, 0.0,  par_obj.get_MP_NDIR()[i],    par_obj.get_MFSEN_NDIR()[i],
                                              par_obj.get_MTSEN_NDIR()[i], par_obj.get_NC_NDIR()[i]);
    text.push_back(line_data);
  }


  i_max = static_cast<int>(par_obj.get_NCTAB());
  for(int i=0; i<i_max; i++)
  {
    line_data = efw_obj.write_cont(0.0, 0.0,  par_obj.get_MP_NCTAB()[i],   par_obj.get_LIBF_NCTAB()[i],
                                              par_obj.get_MATF_NCTAB()[i], par_obj.get_MPF_NCTAB()[i]);
    text.push_back(line_data);
  }


  line_data = efw_obj.write_mt_end();
  text.push_back(line_data);

  line_data.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF30MT001Writer::clear()
{
  clr_obj.clear_vec_array1_str(text);

  par_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> MF30MT001Writer::get_endf_text_data(MF30MT001Parser& MF30MT001parser_obj)
{
  clear();
  par_obj = MF30MT001parser_obj;

  write_endf();
  return text;
}

