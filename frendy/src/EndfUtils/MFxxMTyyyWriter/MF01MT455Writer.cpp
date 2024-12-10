#include "EndfUtils/MFxxMTyyyWriter/MF01MT455Writer.hpp"

using namespace frendy;

//constructor
MF01MT455Writer::MF01MT455Writer(void)
{
  clear();
}

//destructor
MF01MT455Writer::~MF01MT455Writer(void)
{ 
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF01MT455Writer::write_endf() 
{
  clr_obj.clear_vec_array1_str(text);

  string         line_data;
  vector<string> str_vec;
  efw_obj.set_mat_mf_mt(par_obj.get_mat_no(), mf_no, mt_no);

  //Line No.01
  //ZA, AWR, LDG, LNU
  line_data = efw_obj.write_cont
	            (par_obj.get_ZA(), par_obj.get_AWR(), par_obj.get_LDG(), par_obj.get_LNU(), 0, 0);
  text.push_back(line_data);

  if( par_obj.get_LDG() == 0 )
  {
    str_vec = efw_obj.write_list(0.0, 0.0, 0, 0, par_obj.get_NNF(), 0, par_obj.get_RAMDA());

    int i_max = static_cast<int>(str_vec.size());
    for(int i=0; i<i_max; i++)
    {
      text.push_back(str_vec[i]);
    }
  }
  else if( par_obj.get_LDG() == 1 )
  {
    str_vec = efw_obj.write_tab2(0.0, 0.0, 0, 0,  par_obj.get_NR_E(),  par_obj.get_NE_E(),
                                 par_obj.get_NBT_E(),  par_obj.get_INT_E());

    int i_max = static_cast<int>(str_vec.size());
    for(int i=0; i<i_max; i++)
    {
      text.push_back(str_vec[i]);
    }

    vector<Real> real_vec;
    int list_no = static_cast<int>(par_obj.get_NNF()) * 2;
    real_vec.resize(list_no);
    for(int g=0; g<static_cast<int>(par_obj.get_NE_E()); g++)
    {
      int ele_no = 0;
      for(int i=0; i<list_no; i+=2)
      {
        real_vec[i]   = par_obj.get_RAMDA_MAP()[g][ele_no];
        real_vec[i+1] = par_obj.get_ALPHA_MAP()[g][ele_no];
        ele_no++;
      }
      
      str_vec = efw_obj.write_list(0.0, par_obj.get_E()[g], 0, 0, par_obj.get_NNF()*2, 0, real_vec);

      int i_max = static_cast<int>(str_vec.size());
      for(int i=0; i<i_max; i++)
      {
        text.push_back(str_vec[i]);
      }
    }
    real_vec.clear();
  }


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
    str_vec = efw_obj.write_tab1(0.0, 0.0, 0, 0, par_obj.get_NR_NU(),  par_obj.get_NP_NU(),
                                 par_obj.get_NBT_NU(),   par_obj.get_INT_NU(),
                                 par_obj.get_E_INT_NU(), par_obj.get_NU());

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

void MF01MT455Writer::clear()
{
  clr_obj.clear_vec_array1_str(text);

  par_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> MF01MT455Writer::get_endf_text_data(MF01MT455Parser& mf01mt455parser_obj)
{
  clear();
  par_obj = mf01mt455parser_obj;

  write_endf();
  return text;
}

