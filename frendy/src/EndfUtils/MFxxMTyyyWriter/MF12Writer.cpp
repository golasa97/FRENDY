#include "EndfUtils/MFxxMTyyyWriter/MF12Writer.hpp"

using namespace frendy;

//constructor
MF12Writer::MF12Writer(void)
{
  clear();
}

//destructor
MF12Writer::~MF12Writer(void)
{ 
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF12Writer::write_endf() 
{
  clr_obj.clear_vec_array1_str(text);

  string         line_data;
  efw_obj.set_mat_mf_mt(par_obj.get_mat_no(), mf_no, par_obj.get_mt_no());

  //Line No.01
  //ZA, AWR, LIS, NK
  line_data = efw_obj.write_cont(par_obj.get_ZA(), par_obj.get_AWR(), par_obj.get_LO(), 
                                 par_obj.get_LG(), par_obj.get_NK(), 0);
  text.push_back(line_data);

  if( par_obj.get_LO() == 1 )
  {
    write_lo01();
  }
  else if( par_obj.get_LO() == 2 )
  {
    write_lo02();
  }
  else
  {
    string class_name = "MF12Writer";
    string func_name  = "write_endf()";

    ostringstream oss01, oss02;
    oss01 << par_obj.get_mt_no();
    oss02 << par_obj.get_LO();
    string str_data01 = "Section number (MT) : " + oss01.str();
    string str_data02 = "LO                  : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("This LO value at MF=12 is not supported in this writer program.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  line_data = efw_obj.write_mt_end();
  text.push_back(line_data);

  line_data.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF12Writer::write_lo01()
{
  vector<string> str_vec;

  int i_max = static_cast<int>(par_obj.get_NK());

  if( i_max > 1 )
  {
    Integer NR = par_obj.get_NBT_Y_LO01().size();
    Integer NP = par_obj.get_E_INT_Y_LO01().size();
    str_vec = efw_obj.write_tab1(0.0, 0.0, 0, 0, NR, NP,
                                 par_obj.get_NBT_Y_LO01(), par_obj.get_INT_Y_LO01(), 
                                 par_obj.get_E_INT_Y_LO01(), par_obj.get_Y_TAB_LO01());

    int j_max = static_cast<int>(str_vec.size());
    for(int j=0; j<j_max; j++)
    {
      text.push_back(str_vec[j]);
    }
  }

  vector<vector<Integer> > nbt_y_k   = par_obj.get_NBT_Y_K_LO01();
  vector<vector<Integer> > int_y_k   = par_obj.get_INT_Y_K_LO01();
  vector<vector<Real> >    e_int_y_k = par_obj.get_E_INT_Y_K_LO01();
  vector<vector<Real> >    y_k_tab   = par_obj.get_Y_K_TAB_LO01();
  for(int i=0; i<i_max; i++)
  {
    Integer NR = static_cast<Integer>(nbt_y_k[i].size());
    Integer NP = static_cast<Integer>(e_int_y_k[i].size());

    str_vec = efw_obj.write_tab1(par_obj.get_EG_LO01()[i], par_obj.get_ES_LO01()[i],
                                 par_obj.get_LP_LO01()[i], par_obj.get_LF_LO01()[i], NR, NP,
                                 nbt_y_k[i], int_y_k[i], e_int_y_k[i], y_k_tab[i]);

    int j_max = static_cast<int>(str_vec.size());
    for(int j=0; j<j_max; j++)
    {
      text.push_back(str_vec[j]);
    }
  }
  clr_obj.clear_vec_array1_str(str_vec);
  clr_obj.clear_vec_array2_int(nbt_y_k);
  clr_obj.clear_vec_array2_int(int_y_k);
  clr_obj.clear_vec_array2_real(e_int_y_k);
  clr_obj.clear_vec_array2_real(y_k_tab);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF12Writer::write_lo02()
{
  vector<string> str_vec;

  Integer b_max = static_cast<Integer>(par_obj.get_B_LO02().size());
  if( b_max != (par_obj.get_LG()+1)*par_obj.get_NT_LO02() )
  {
    string class_name = "MF12Writer";
    string func_name  = "write_lo02()";

    ostringstream oss01, oss02, oss03, oss04;
    oss01 << par_obj.get_mt_no();
    oss02 << b_max;
    oss02 << par_obj.get_LG();
    oss02 << par_obj.get_NT_LO02();
    string str_data01 = "Section number (MT) : " + oss01.str();
    string str_data02 = "(LG+1)*NT           : " + oss02.str();
    string str_data03 = "LG                  : " + oss03.str();
    string str_data04 = "NT                  : " + oss04.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back("The number of (LG+1)*NT at LO=2 is not correct value.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  str_vec = efw_obj.write_list(par_obj.get_ES_LO02(), 0.0, par_obj.get_LP_LO02(), 
                               0, b_max, par_obj.get_NT_LO02(), par_obj.get_B_LO02());
  int j_max = static_cast<int>(str_vec.size());
  for(int j=0; j<j_max; j++)
  {
    text.push_back(str_vec[j]);
  }

  clr_obj.clear_vec_array1_str(str_vec);
}


////////////////////////////////////////////////////////////////////////////////////////////////////

void MF12Writer::clear()
{
  clr_obj.clear_vec_array1_str(text);

  par_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> MF12Writer::get_endf_text_data(MF12Parser& mf12parser_obj)
{
  clear();
  par_obj = mf12parser_obj;

  write_endf();
  return text;
}

