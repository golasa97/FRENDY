#include "EndfUtils/MFxxMTyyyWriter/MF33Writer.hpp"

using namespace frendy;

//constructor
MF33Writer::MF33Writer(void)
{
  clear();
}

//destructor
MF33Writer::~MF33Writer(void)
{ 
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF33Writer::write_endf() 
{
  clr_obj.clear_vec_array1_str(text);

  string line_data;
  efw_obj.set_mat_mf_mt(par_obj.get_mat_no(), mf_no, par_obj.get_mt_no());

  //Line No.01
  //ZA, AWR, MTL, NL
  line_data = efw_obj.write_cont(par_obj.get_ZA(), par_obj.get_AWR(), 0, par_obj.get_MTL(),
                                 0, par_obj.get_NL());
  text.push_back(line_data);


  int i_max = static_cast<int>(par_obj.get_NL());
  for(int i=0; i<i_max; i++)
  {
    line_data = efw_obj.write_cont(par_obj.get_XMF()[i], par_obj.get_XLFS()[i], par_obj.get_MAT()[i],
                                   par_obj.get_MT()[i],  par_obj.get_NC()[i],   par_obj.get_NI()[i]);
    text.push_back(line_data);


    int j_max = static_cast<int>(par_obj.get_NC()[i]);
    for(int j=0; j<j_max; j++)
    {
      write_NC(i, j);
    }


    j_max = static_cast<int>(par_obj.get_NI()[i]);
    for(int j=0; j<j_max; j++)
    {
      write_NI(i, j);
    }
  }

  line_data = efw_obj.write_mt_end();
  text.push_back(line_data);

  line_data.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF33Writer::write_NC(int i, int j) 
{
  string         line_data;
  vector<string> str_vec;

  line_data = efw_obj.write_cont(0.0, 0.0, 0, par_obj.get_LTY()[i][j], 0, 0);
  text.push_back(line_data);


  if( par_obj.get_LTY()[i][j] == 0 )
  {
    int k_max   = static_cast<int>(par_obj.get_CI()[i][j].size());
    int list_no = k_max * 2;
    vector<Real> list_vec;
    list_vec.resize(list_no);

    int ele_no = 0;
    for(int k=0; k<k_max; k++)
    {
      list_vec[ele_no]   = par_obj.get_CI()[i][j][k];
      list_vec[ele_no+1] = par_obj.get_XMTI()[i][j][k];
      ele_no += 2;
    }

    str_vec = efw_obj.write_list(par_obj.get_E1()[i][j], par_obj.get_E2()[i][j], 0, 0, list_no, k_max,
                                 list_vec);
  }
  else if( par_obj.get_LTY()[i][j] == 1 || par_obj.get_LTY()[i][j] == 2 || par_obj.get_LTY()[i][j] == 3 )
  {
    int k_max   = static_cast<int>(par_obj.get_EI()[i][j].size());
    int list_no = k_max * 2 + 2;
    vector<Real> list_vec;
    list_vec.resize(list_no);

    list_vec[0] = par_obj.get_XMFS()[i][j];
    list_vec[1] = par_obj.get_XLFSS()[i][j];

    int ele_no = 2;
    for(int k=0; k<k_max; k++)
    {
      list_vec[ele_no]   = par_obj.get_EI()[i][j][k];
      list_vec[ele_no+1] = par_obj.get_WEI()[i][j][k];
      ele_no += 2;
    }

    str_vec = efw_obj.write_list(par_obj.get_E1()[i][j],   par_obj.get_E2()[i][j],
                                 par_obj.get_MATS()[i][j], par_obj.get_MTS()[i][j], list_no, k_max,
                                 list_vec);
  }

  int k_max = static_cast<int>(str_vec.size());
  for(int k=0; k<k_max; k++)
  {
    text.push_back(str_vec[k]);
  }

  line_data.clear();
  clr_obj.clear_vec_array1_str(str_vec);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF33Writer::write_NI(int i, int j) 
{
  Integer LB = par_obj.get_LB()[i][j];

  if( LB >= 0 && LB <= 4 )
  {
    write_NI_lb00(i, j);
  }
  else if( LB == 5 )
  {
    write_NI_lb05(i, j);
  }
  else if( LB == 6 )
  {
    write_NI_lb06(i, j);
  }
  else if( LB == 8 || LB == 9 )
  {
    write_NI_lb00(i, j);
  }
  else
  {
    string class_name = "MF33Writer";
    string func_name  = "write_NI(MultiParser& mp_obj, int& line_no, int& i, int& j)";

    ostringstream oss00, oss01, oss02, oss03, oss04, oss05;
    oss00 << par_obj.get_mt_no();
    oss01 << i;
    oss02 << static_cast<int>(par_obj.get_NL());
    oss03 << j;
    oss04 << static_cast<int>(par_obj.get_NI()[i]);
  	oss05 << par_obj.get_LB()[i][j];
    string str_data00 = "Section number (MT) : " + oss00.str();
    string str_data01 = "NL                  : " + oss01.str() + " / " + oss02.str();
    string str_data02 = "NI                  : " + oss03.str() + " / " + oss04.str();
    string str_data03 = "LB                  : " + oss05.str();

    vector<string> err_com;
    err_com.push_back(str_data00);
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("This LB value at MF=33 is not supported in this program.");
    err_com.push_back("Supported LB value is 0 - 6, 8 and 9.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF33Writer::write_NI_lb00(int i, int j) 
{
  string         line_data;
  vector<string> str_vec;

  int k_no    = static_cast<int>(par_obj.get_E_K()[i][j].size());
  int t_no    = static_cast<int>(par_obj.get_LT()[i][j]);
  int tot_no  = k_no + t_no;
  int list_no = tot_no * 2;
  vector<Real> list_vec;
  list_vec.resize(list_no);

  int ele_no = 0;
  for(int k=0; k<k_no; k++)
  {
    list_vec[ele_no]   = par_obj.get_E_K()[i][j][k];
    list_vec[ele_no+1] = par_obj.get_F_K()[i][j][k][0];
    ele_no += 2;
  }

  for(int k=0; k<t_no; k++)
  {
    list_vec[ele_no]   = par_obj.get_E_T()[i][j][k];
    list_vec[ele_no+1] = par_obj.get_F_T()[i][j][k][0];
    ele_no += 2;
  }

  str_vec = efw_obj.write_list(0.0, 0.0, par_obj.get_LT()[i][j], par_obj.get_LB()[i][j],
                               list_no, tot_no, list_vec);

  int k_max = static_cast<int>(str_vec.size());
  for(int k=0; k<k_max; k++)
  {
    text.push_back(str_vec[k]);
  }
  clr_obj.clear_vec_array1_str(str_vec);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF33Writer::write_NI_lb05(int i, int j) 
{
  string         line_data;
  vector<string> str_vec;

  int ne = static_cast<int>(par_obj.get_E_K()[i][j].size());

  int list_no = 0;
  vector<Real> list_vec;
  if( par_obj.get_LT()[i][j] == 0 )
  {
    list_no = ne*(ne-1)+1;
    list_vec.resize(list_no);
  }
  else if( par_obj.get_LT()[i][j] == 1 )
  {
    list_no = (ne*(ne+1))/2;
    list_vec.resize(list_no);
  }

  int ele_no = 0;
  for( int k=0; k<ne; k++)
  {
    list_vec[ele_no] = par_obj.get_E_K()[i][j][k];
    ele_no++;
  }

  int k_max = static_cast<int>(par_obj.get_F_K()[i][j].size());
  for(int k=0; k<k_max; k++)
  {
    int l_max = static_cast<int>(par_obj.get_F_K()[i][j][k].size());
    for(int l=0; l<l_max; l++)
    {
      list_vec[ele_no] = par_obj.get_F_K()[i][j][k][l];
      ele_no++;
    }
  }


  str_vec = efw_obj.write_list(0.0, 0.0, par_obj.get_LT()[i][j], par_obj.get_LB()[i][j],
                               list_no, ne, list_vec);

  k_max = static_cast<int>(str_vec.size());
  for(int k=0; k<k_max; k++)
  {
    text.push_back(str_vec[k]);
  }
  clr_obj.clear_vec_array1_str(str_vec);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF33Writer::write_NI_lb06(int i, int j) 
{
  string         line_data;
  vector<string> str_vec;

  int ner     = static_cast<int>(par_obj.get_E_K()[i][j].size());
  int nec     = static_cast<int>(par_obj.get_E_T()[i][j].size());
  int list_no = 1+ner*nec;

  vector<Real> list_vec;
  list_vec.resize(list_no);

  int ele_no = 0;
  for(int k=0; k<ner; k++)
  {
    list_vec[ele_no] = par_obj.get_E_K()[i][j][k];
    ele_no++;
  }

  int k_max = static_cast<int>(par_obj.get_E_T()[i][j].size());
  for(int k=0; k<k_max; k++)
  {
    list_vec[ele_no] = par_obj.get_E_T()[i][j][k];
    ele_no++;
  }

  k_max = static_cast<int>(par_obj.get_F_K()[i][j].size());
  for(int k=0; k<k_max; k++)
  {
    int l_max = static_cast<int>(par_obj.get_F_K()[i][j][k].size());
    for(int l=0; l<l_max; l++)
    {
      list_vec[ele_no] = par_obj.get_F_K()[i][j][k][l];
      ele_no++;
    }
  }


  str_vec = efw_obj.write_list(0.0, 0.0, par_obj.get_LT()[i][j], par_obj.get_LB()[i][j],
                               list_no, ner, list_vec);

  k_max = static_cast<int>(str_vec.size());
  for(int k=0; k<k_max; k++)
  {
    text.push_back(str_vec[k]);
  }
  clr_obj.clear_vec_array1_str(str_vec);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF33Writer::clear()
{
  clr_obj.clear_vec_array1_str(text);

  par_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> MF33Writer::get_endf_text_data(MF33Parser& MF33parser_obj)
{
  clear();
  par_obj = MF33parser_obj;

  write_endf();
  return text;
}

