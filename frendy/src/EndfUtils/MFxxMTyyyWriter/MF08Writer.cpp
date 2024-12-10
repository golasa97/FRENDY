#include "EndfUtils/MFxxMTyyyWriter/MF08Writer.hpp"

using namespace frendy;

//constructor
MF08Writer::MF08Writer(void)
{
  clear();
}

//destructor
MF08Writer::~MF08Writer(void)
{ 
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF08Writer::write_endf() 
{
  clr_obj.clear_vec_array1_str(text);

  string         line_data;
  vector<string> str_vec;
  efw_obj.set_mat_mf_mt(par_obj.get_mat_no(), mf_no, par_obj.get_mt_no());
  if( par_obj.get_mt_no() == 454 || par_obj.get_mt_no() == 457 || par_obj.get_mt_no() == 459 )
  {
    string class_name = "MF08Writer";
    string func_name  = "write_endf()";

    ostringstream oss01;
    oss01 << par_obj.get_mt_no();
    string str_data01 = "Section number (MT)     : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    if( par_obj.get_mt_no() == 454 )
    {
      err_com.push_back("This MT number is not supported in this class, please use MT08MF454Writer class.");
    }
    else if( par_obj.get_mt_no() == 459 )
    {
      err_com.push_back("This MT number is not supported in this class, please use MT08MF459Writer class.");
    }
    else if( par_obj.get_mt_no() == 457 )
    {
      err_com.push_back("This MT number is not supported in this class, please use MT08MF457Writer class.");
    }
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //Line No.01
  //ZA, AWR, LIS, LISO, NS, NO
  line_data = efw_obj.write_cont(par_obj.get_ZA(), par_obj.get_AWR(), par_obj.get_LIS(), par_obj.get_LISO(),
                                 par_obj.get_NS(), par_obj.get_NO());
  text.push_back(line_data);


  int i_max = static_cast<int>(par_obj.get_NS());
  if( par_obj.get_NO() == 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      int j_max = static_cast<int>(par_obj.get_HL()[i].size()) * 6;
      vector<Real> real_vec;
      real_vec.resize(j_max);
      int ele_no = 0;
      for(int j=0; j<j_max; j+=6)
      {
        real_vec[j]   = par_obj.get_HL()[i][ele_no];
        real_vec[j+1] = par_obj.get_RTYP()[i][ele_no];
        real_vec[j+2] = par_obj.get_ZAN()[i][ele_no];
        real_vec[j+3] = par_obj.get_BR()[i][ele_no];
        real_vec[j+4] = par_obj.get_END()[i][ele_no];
        real_vec[j+5] = par_obj.get_CT()[i][ele_no];
        ele_no++;
      }

      str_vec = efw_obj.write_list(par_obj.get_ZAP()[i], par_obj.get_ELFS()[i],
                                   par_obj.get_LMF()[i], par_obj.get_LFS()[i], j_max, 0, real_vec);
      real_vec.clear();

      j_max = static_cast<int>(str_vec.size());
      for(int j=0; j<j_max; j++)
      {
        text.push_back(str_vec[j]);
      }
    }
  }
  else if( par_obj.get_NO() == 1 )
  {
    for(int i=0; i<i_max; i++)
    {
      line_data = efw_obj.write_cont(par_obj.get_ZAP()[i], par_obj.get_ELFS()[i],
                                     par_obj.get_LMF()[i], par_obj.get_LFS()[i], 0, 0);
      text.push_back(line_data);
    }
  }

  line_data = efw_obj.write_mt_end();
  text.push_back(line_data);

  clr_obj.clear_vec_array1_str(str_vec);
  line_data.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF08Writer::clear()
{
  clr_obj.clear_vec_array1_str(text);

  par_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> MF08Writer::get_endf_text_data(MF08Parser& mf08parser_obj)
{
  clear();
  par_obj = mf08parser_obj;

  write_endf();
  return text;
}

