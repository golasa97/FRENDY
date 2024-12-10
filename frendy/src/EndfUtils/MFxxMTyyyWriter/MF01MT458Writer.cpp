#include "EndfUtils/MFxxMTyyyWriter/MF01MT458Writer.hpp"

using namespace frendy;

//constructor
MF01MT458Writer::MF01MT458Writer(void)
{
  clear();
}

//destructor
MF01MT458Writer::~MF01MT458Writer(void)
{ 
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF01MT458Writer::write_endf() 
{
  clr_obj.clear_vec_array1_str(text);

  string         line_data;
  vector<string> str_vec;
  efw_obj.set_mat_mf_mt(par_obj.get_mat_no(), mf_no, mt_no);

  //Line No.01
  //ZA, AWR, LNU
  line_data = efw_obj.write_cont(par_obj.get_ZA(), par_obj.get_AWR(),
                                 0, par_obj.get_LFC(), 0, par_obj.get_NFC());
  text.push_back(line_data);

  //Line No.02
  //NPLY, N1, N2
  vector<Real> real_vec;
  int i_max = static_cast<int>(par_obj.get_N1());
  real_vec.resize(i_max);

  int data_no = 18;
  int ele_no  =  0;
  for(int i=0; i<i_max; i+=data_no)
  {
    real_vec[i]    =  par_obj.get_EFR()[ele_no];
    real_vec[i+ 2] =  par_obj.get_ENP()[ele_no];
    real_vec[i+ 4] =  par_obj.get_END()[ele_no];
    real_vec[i+ 6] =  par_obj.get_EGP()[ele_no];
    real_vec[i+ 8] =  par_obj.get_EGD()[ele_no];
    real_vec[i+10] =  par_obj.get_EB()[ele_no];
    real_vec[i+12] =  par_obj.get_ENU()[ele_no];
    real_vec[i+14] =  par_obj.get_ER()[ele_no];
    real_vec[i+16] =  par_obj.get_ET()[ele_no];

    real_vec[i+ 1] =  par_obj.get_D_EFR()[ele_no];
    real_vec[i+ 3] =  par_obj.get_D_ENP()[ele_no];
    real_vec[i+ 5] =  par_obj.get_D_END()[ele_no];
    real_vec[i+ 7] =  par_obj.get_D_EGP()[ele_no];
    real_vec[i+ 9] =  par_obj.get_D_EGD()[ele_no];
    real_vec[i+11] =  par_obj.get_D_EB()[ele_no];
    real_vec[i+13] =  par_obj.get_D_ENU()[ele_no];
    real_vec[i+15] =  par_obj.get_D_ER()[ele_no];
    real_vec[i+17] =  par_obj.get_D_ET()[ele_no];
    ele_no++;
  }

  str_vec = efw_obj.write_list(0.0, 0.0, 0, par_obj.get_NPLY(), par_obj.get_N1(), par_obj.get_N2(),
                               real_vec);
  real_vec.clear();

  i_max = static_cast<int>(str_vec.size());
  for(int i=0; i<i_max; i++)
  {
    text.push_back(str_vec[i]);
  }

  //Line No.03
  //LDRV, IFC, EIFC(E)
  i_max = static_cast<int>(par_obj.get_NFC());
  for(int i=0; i<i_max; i++)
  {
    Integer NR = static_cast<Integer>(par_obj.get_NBT_EIFC()[i].size());
    Integer NP = static_cast<Integer>(par_obj.get_E_INT_EIFC()[i].size());
    str_vec = efw_obj.write_tab1(0.0, 0.0, par_obj.get_LDRV()[i], par_obj.get_IFC()[i], NR, NP,
                               par_obj.get_NBT_EIFC()[i], par_obj.get_INT_EIFC()[i],
                               par_obj.get_E_INT_EIFC()[i], par_obj.get_EIFC_TAB()[i]);

    int j_max = static_cast<int>(str_vec.size());
    for(int j=0; j<j_max; j++)
    {
      text.push_back(str_vec[j]);
    }
  }

  line_data = efw_obj.write_mt_end();
  text.push_back(line_data);

  line_data.clear();
  clr_obj.clear_vec_array1_str(str_vec);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF01MT458Writer::clear()
{
  clr_obj.clear_vec_array1_str(text);

  par_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> MF01MT458Writer::get_endf_text_data(MF01MT458Parser& mf01mt458parser_obj)
{
  clear();
  par_obj = mf01mt458parser_obj;

  write_endf();
  return text;
}

