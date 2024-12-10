#include "EndfUtils/MFxxMTyyyWriter/MF04Writer.hpp"

using namespace frendy;

//constructor
MF04Writer::MF04Writer(void)
{
  clear();
}

//destructor
MF04Writer::~MF04Writer(void)
{ 
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF04Writer::write_endf() 
{
  clr_obj.clear_vec_array1_str(text);

  string         line_data;
  vector<string> str_vec;
  efw_obj.set_mat_mf_mt(par_obj.get_mat_no(), mf_no, par_obj.get_mt_no());

  //Line No.01
  //ZA, AWR, LVT, LTT
  line_data = efw_obj.write_cont(par_obj.get_ZA(), par_obj.get_AWR(),
                                 par_obj.get_LVT(), par_obj.get_LTT(), 0, 0);
  text.push_back(line_data);


  //Line No.02
  //LI, LCT
  if( par_obj.get_LVT() == 0 )
  {
    line_data = efw_obj.write_cont(0.0, 0.0, par_obj.get_LI(), par_obj.get_LCT(),
                                   par_obj.get_NK(), par_obj.get_NM());
    text.push_back(line_data);
  }
  else if( par_obj.get_LVT() == 1 )
  {
    str_vec = efw_obj.write_list(0.0, 0.0, par_obj.get_LI(), par_obj.get_LCT(),
                                  par_obj.get_NK(), par_obj.get_NM(), par_obj.get_U());
    int i_max = static_cast<int>(str_vec.size());
    for(int i=0; i<i_max; i++)
    {
      text.push_back(str_vec[i]);
    }
  }


  if( par_obj.get_LTT() == 0 && par_obj.get_LI() == 1 )
  {

  }
  else if( par_obj.get_LTT() == 1 && par_obj.get_LI() == 0 )
  {
    write_ltt01();
  }
  else if( par_obj.get_LTT() == 2 && par_obj.get_LI() == 0 )
  {
    write_ltt02();
  }
  else if( par_obj.get_LTT() == 3 && par_obj.get_LI() == 0 )
  {
    //Legendre coefficients
    write_ltt01();

    //Tabulated data
    write_ltt02();
  }

  line_data = efw_obj.write_mt_end();
  text.push_back(line_data);

  clr_obj.clear_vec_array1_str(str_vec);
  line_data.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF04Writer::write_ltt01()
{
  vector<string> str_vec;

  int nbt_no = static_cast<int>(par_obj.get_NBT_E_LTT01().size());
  str_vec = efw_obj.write_tab2(0.0, 0.0, 0, 0, nbt_no, par_obj.get_NE_LTT01(),
                               par_obj.get_NBT_E_LTT01(), par_obj.get_INT_E_LTT01());
  int i_max = static_cast<int>(str_vec.size());
  for(int i=0; i<i_max; i++)
  {
    text.push_back(str_vec[i]);
  }


  for(int i=0; i<static_cast<int>(par_obj.get_NE_LTT01()); i++)
  {
    str_vec = efw_obj.write_list(par_obj.get_T_LTT01()[i], par_obj.get_E_LTT01()[i],
                                 par_obj.get_LT_LTT01()[i], 0, par_obj.get_NL_LTT01()[i], 0,
                                 par_obj.get_A_LTT01()[i]);
    int j_max = static_cast<int>(str_vec.size());
    for(int j=0; j<j_max; j++)
    {
      text.push_back(str_vec[j]);
    }
  }
  clr_obj.clear_vec_array1_str(str_vec);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF04Writer::write_ltt02()
{
  vector<string> str_vec;

  int nbt_no = static_cast<int>(par_obj.get_NBT_E_LTT02().size());
  str_vec = efw_obj.write_tab2(0.0, 0.0, 0, 0, nbt_no, par_obj.get_NE_LTT02(),
                               par_obj.get_NBT_E_LTT02(), par_obj.get_INT_E_LTT02());
  int i_max = static_cast<int>(str_vec.size());
  for(int i=0; i<i_max; i++)
  {
    text.push_back(str_vec[i]);
  }


  for(int i=0; i<static_cast<int>(par_obj.get_NE_LTT02()); i++)
  {
    str_vec = efw_obj.write_tab1(par_obj.get_T_LTT02()[i],       par_obj.get_E_LTT02()[i],
                                 par_obj.get_LT_LTT02()[i],      0,
                                 par_obj.get_NR_LTT02()[i],      par_obj.get_NP_LTT02()[i],
                                 par_obj.get_NBT_F_LTT02()[i],   par_obj.get_INT_F_LTT02()[i],
                                 par_obj.get_M_INT_F_LTT02()[i], par_obj.get_F_TAB_LTT02()[i]);
    int j_max = static_cast<int>(str_vec.size());
    for(int j=0; j<j_max; j++)
    {
      text.push_back(str_vec[j]);
    }
  }
  clr_obj.clear_vec_array1_str(str_vec);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF04Writer::clear()
{
  clr_obj.clear_vec_array1_str(text);

  par_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> MF04Writer::get_endf_text_data(MF04Parser& MF04parser_obj)
{
  clear();
  par_obj = MF04parser_obj;

  write_endf();
  return text;
}

