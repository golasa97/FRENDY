#include "EndfUtils/MFxxMTyyyWriter/MF02MT152Writer.hpp"

using namespace frendy;

//constructor
MF02MT152Writer::MF02MT152Writer(void)
{
  clear();
}

//destructor
MF02MT152Writer::~MF02MT152Writer(void)
{ 
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF02MT152Writer::write_endf() 
{
  clr_obj.clear_vec_array1_str(text);

  string         line_data;
  vector<string> str_vec;
  efw_obj.set_mat_mf_mt(par_obj.get_mat_no(), mf_no, mt_no);

  //Line No.01
  //ZA, AWR, LSSF and NR
  line_data = efw_obj.write_cont(par_obj.get_ZAR(), par_obj.get_AWR(), 
                                 par_obj.get_LSSF(), 0, 0, par_obj.get_INT());
  text.push_back(line_data);


  //Line No.02
  vector<Real> real_vec;
  if( par_obj.get_SIG_TOT().size() > 0 )
  {
    write_endf_reconr_mode(real_vec);
  }
  else if( par_obj.get_SIG_ZERO().size() > 0 )
  {
    write_endf_purr_mode(real_vec);
  }
  else
  {
    string class_name = "MF02MT152Writer";
    string func_name  = "write_endf()";

    vector<string> err_com;
    err_com.push_back("The set data is not RECONR mode nor PURR mode.");
    err_com.push_back("Please check the MF02MT152Parser object.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  Integer ele_max = static_cast<Integer>(real_vec.size());
  str_vec = efw_obj.write_list(par_obj.get_TEMP(), 0.0, par_obj.get_OPT1(), par_obj.get_OPT2(),
                               ele_max, par_obj.get_NE(), real_vec);

  int i_max = static_cast<int>(str_vec.size());
  for(int i=0; i<i_max; i++)
  {
    text.push_back(str_vec[i]);
  }

  line_data = efw_obj.write_mt_end();
  text.push_back(line_data);

  line_data.clear();
  clr_obj.clear_vec_array1_str(str_vec);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF02MT152Writer::write_endf_reconr_mode(vector<Real>& real_vec) 
{
  real_vec.clear();

  Integer sigmax = static_cast<Integer>(par_obj.get_E().size());
  if( sigmax != par_obj.get_NE() )
  {
    string class_name = "MF02MT152Writer";
    string func_name  = "write_endf_reconr_mode(vector<Real>& real_vec)";

    ostringstream oss01, oss02;
    oss01 << sigmax;
    oss02 << par_obj.get_NE();
    string str_data01 = "1+6*NE : " + oss01.str();
    string str_data02 = "NE     : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("The number of list data is not equal to 1+6*NE.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  int i_max = static_cast<int>(sigmax);
  real_vec.resize(i_max*6+1);
  for(int i=0; i<i_max; i++)
  {
    if( i==0 )
    {
      real_vec[6*i+0] = 1.0e+10;
    }
    else
    {
      real_vec[6*i+0] = par_obj.get_SIG_TOT()[i-1];
    }

    real_vec[6*i+1] = par_obj.get_E()[i];
    real_vec[6*i+2] = par_obj.get_SIG_TOT()[i];
    real_vec[6*i+3] = par_obj.get_SIG_SC()[i];
    real_vec[6*i+4] = par_obj.get_SIG_FIS()[i];
    real_vec[6*i+5] = par_obj.get_SIG_RAD()[i];
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF02MT152Writer::write_endf_purr_mode(vector<Real>& real_vec)
{
  real_vec.clear();

  int sig_zero_no = static_cast<int>(par_obj.get_OPT2());
  int ene_no      = static_cast<int>(par_obj.get_NE());

  vector<Real>                   sig_zero = par_obj.get_SIG_ZERO();
  vector<Real>                   ene      = par_obj.get_E();
  vector<vector<vector<Real> > > b_table  = par_obj.get_B_TABLE();
  if( sig_zero_no != static_cast<int>(sig_zero.size()) ||
      ene_no      != static_cast<int>(ene.size())      )
  {
    string class_name = "MF02MT152Writer";
    string func_name  = "write_endf_reconr_mode(vector<Real>& real_vec)";

    ostringstream oss01, oss02, oss03, oss04;
    oss01 << sig_zero_no;
    oss02 << sig_zero.size();
    oss03 << ene_no;
    oss04 << ene.size();
    string str_data01 = "OPT2 (Element No. of SIG_ZERO) : " + oss01.str();
    string str_data02 = "Element No. of SIG_ZERO        : " + oss02.str();
    string str_data03 = "NE                             : " + oss03.str();
    string str_data04 = "Element No. of E               : " + oss04.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back("The number of element data is not identical.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  int ele_max = sig_zero_no + ene_no*(1 + 5*sig_zero_no);
  real_vec.resize(ele_max);

  int ele_no = 0;
  for(int i=0; i<sig_zero_no; i++)
  {
    real_vec[ele_no] = sig_zero[i];
    ele_no++;
  }

  for(int i=0; i<ene_no; i++)
  {
    real_vec[ele_no] = ene[i];
    ele_no++;

    for(int j=0; j<static_cast<int>(b_table[i].size()); j++)
    {
      for(int k=0; k<sig_zero_no; k++)
      {
        real_vec[ele_no] = b_table[i][j][k];
        ele_no++;
      }
    }
  }

  sig_zero.clear();
  ene.clear();
  clr_obj.clear_vec_array3_real(b_table);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF02MT152Writer::clear()
{
  clr_obj.clear_vec_array1_str(text);

  par_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> MF02MT152Writer::get_endf_text_data(MF02MT152Parser& mf02mt152parser_obj)
{
  clear();
  par_obj = mf02mt152parser_obj;

  write_endf();
  return text;
}

