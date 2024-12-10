#include "EndfUtils/MFxxMTyyyWriter/MF28Writer.hpp"

using namespace frendy;

//constructor
MF28Writer::MF28Writer(void)
{
  clear();
}

//destructor
MF28Writer::~MF28Writer(void)
{ 
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF28Writer::write_endf() 
{
  clr_obj.clear_vec_array1_str(text);

  string         line_data;
  vector<string> str_vec;
  efw_obj.set_mat_mf_mt(par_obj.get_mat_no(), mf_no, par_obj.get_mt_no());
  if( par_obj.get_mt_no() < 533 || par_obj.get_mt_no() > 599 )
  {
    string class_name = "MF28Writer";
    string func_name  = "write_endf()";

    ostringstream oss01;
    oss01 << par_obj.get_mt_no();
    string str_data01 = "Section number (MT) : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("The MT number of MF=28 is only applicable from 533 to 599.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //Line No.01
  //ZA, AWR, NK
  line_data = efw_obj.write_cont(par_obj.get_ZA(), par_obj.get_AWR(), 0, 0, par_obj.get_NSS(), 0);
  text.push_back(line_data);


  //Line No.02
  int i_max = static_cast<int>(par_obj.get_NSS());
  for(int i=0; i<i_max; i++)
  {
    int ntr     = static_cast<int>(par_obj.get_SUBJ()[i].size());
    int list_no = 6*(1+ntr);
    vector<Real> list_vec;
    list_vec.resize(list_no);
    list_vec[0] = par_obj.get_EBI()[i];
    list_vec[1] = par_obj.get_ELN()[i];
    list_vec[2] = 0.0;
    list_vec[3] = 0.0;
    list_vec[4] = 0.0;
    list_vec[5] = 0.0;

    int ele_no = 6;
    for(int j=0; j<ntr; j++)
    {
      list_vec[ele_no]   = par_obj.get_SUBJ()[i][j];
      list_vec[ele_no+1] = par_obj.get_SUBK()[i][j];
      list_vec[ele_no+2] = par_obj.get_ETR()[i][j];
      list_vec[ele_no+3] = par_obj.get_FTR()[i][j];
      list_vec[ele_no+4] = 0.0;
      list_vec[ele_no+5] = 0.0;
      ele_no += 6;
    }

    str_vec = efw_obj.write_list(par_obj.get_SUBI()[i], 0.0, 0, 0, list_no, ntr, list_vec);

    int j_max = static_cast<int>(str_vec.size());
    for(int j=0; j<j_max; j++)
    {
      text.push_back(str_vec[j]);
    }
  }
  clr_obj.clear_vec_array1_str(str_vec);

  line_data = efw_obj.write_mt_end();
  text.push_back(line_data);
  line_data.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF28Writer::clear()
{
  clr_obj.clear_vec_array1_str(text);

  par_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> MF28Writer::get_endf_text_data(MF28Parser& MF28parser_obj)
{
  clear();
  par_obj = MF28parser_obj;

  write_endf();
  return text;
}

