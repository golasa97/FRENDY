#include "EndfUtils/MFxxMTyyyWriter/MF07MT002Writer.hpp"

using namespace frendy;

//constructor
MF07MT002Writer::MF07MT002Writer(void)
{
  clear();
}

//destructor
MF07MT002Writer::~MF07MT002Writer(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF07MT002Writer::write_endf()
{
  clr_obj.clear_vec_array1_str(text);

  string line_data;
  efw_obj.set_mat_mf_mt(par_obj.get_mat_no(), mf_no, mt_no);

  //Line No.01
  //ZA, AWR, LTHR
  line_data = efw_obj.write_cont(par_obj.get_ZA(), par_obj.get_AWR(), par_obj.get_LTHR(), 0, 0, 0);
  text.push_back(line_data);
  line_data.clear();

  vector<string> str_vec;
  clr_obj.clear_vec_array1_str(str_vec);
  if( par_obj.get_LTHR() == 1 )
  {
    write_lthr01(str_vec);
  }
  else if( par_obj.get_LTHR() == 2 )
  {
    write_lthr02(str_vec);
  }
  else if( par_obj.get_LTHR() == 3 )
  {
    write_lthr01(str_vec);
    write_lthr02(str_vec);
  }
  else
  {
    string class_name = "MF07MT002Writer";
    string func_name  = "write_endf()";

    ostringstream oss01;
    oss01 << par_obj.get_LTHR();
    string str_data01 = "LTHR : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("This of LTHR value at MF=07, MT=002 is not supported in this program.");
    err_com.push_back("Supported LTHR value is 1 and 2");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

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

void MF07MT002Writer::write_lthr01(vector<string>& text)
{
  vector<string> str_vec;

  Integer NR = static_cast<Integer>(par_obj.get_NBT_S_LTHR01().size());
  Integer NP = static_cast<Integer>(par_obj.get_E_INT_S_LTHR01().size());
  str_vec = efw_obj.write_tab1(par_obj.get_T0_LTHR01(), 0.0, par_obj.get_LT_LTHR01(), 0, NR, NP,
                               par_obj.get_NBT_S_LTHR01(),   par_obj.get_INT_S_LTHR01(),
                               par_obj.get_E_INT_S_LTHR01(), par_obj.get_S_TAB_LTHR01());
  for(int i=0; i<static_cast<int>(str_vec.size()); i++)
  {
    text.push_back(str_vec[i]);
  }
  clr_obj.clear_vec_array1_str(str_vec);

  int i_max = static_cast<int>(par_obj.get_LT_LTHR01());
  vector<vector<Real> > s = par_obj.get_S_LTHR01();
  for(int i=0; i<i_max; i++)
  {
     NP = static_cast<Integer>(s[i].size());
     str_vec = efw_obj.write_list(par_obj.get_T_LTHR01()[i], 0.0, par_obj.get_LI_LTHR01()[i], 0, NP, 0, s[i]);

    for(int j=0; j<static_cast<int>(str_vec.size()); j++)
    {
      text.push_back(str_vec[j]);
    }
    clr_obj.clear_vec_array1_str(str_vec);
  }
  clr_obj.clear_vec_array2_real(s);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF07MT002Writer::write_lthr02(vector<string>& text)
{
  vector<string> str_vec;

  Integer NR = static_cast<Integer>(par_obj.get_NBT_W_LTHR02().size());
  Integer NP = static_cast<Integer>(par_obj.get_T_INT_W_LTHR02().size());
  str_vec = efw_obj.write_tab1(par_obj.get_SB_LTHR02(), 0.0, 0, 0, NR, NP,
                            par_obj.get_NBT_W_LTHR02(),   par_obj.get_INT_W_LTHR02(),
                            par_obj.get_T_INT_W_LTHR02(), par_obj.get_W_TAB_LTHR02());
  for(int i=0; i<static_cast<int>(str_vec.size()); i++)
  {
    text.push_back(str_vec[i]);
  }
  clr_obj.clear_vec_array1_str(str_vec);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF07MT002Writer::clear()
{
  clr_obj.clear_vec_array1_str(text);

  par_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> MF07MT002Writer::get_endf_text_data(MF07MT002Parser& mf07mt002parser_obj)
{
  clear();
  par_obj = mf07mt002parser_obj;

  write_endf();
  return text;
}
