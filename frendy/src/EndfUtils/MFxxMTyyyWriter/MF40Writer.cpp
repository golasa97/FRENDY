#include "EndfUtils/MFxxMTyyyWriter/MF40Writer.hpp"

using namespace frendy;

//constructor
MF40Writer::MF40Writer(void)
{
  clear();
}

//destructor
MF40Writer::~MF40Writer(void)
{ 
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF40Writer::write_endf() 
{
  clr_obj.clear_vec_array1_str(text);

  string line_data;
  efw_obj.set_mat_mf_mt(par_obj.get_mat_no(), mf_no, par_obj.get_mt_no());

  //Line No.01
  //ZA, AWR, LIS, NS
  line_data = efw_obj.write_cont(par_obj.get_ZA(), par_obj.get_AWR(),
                                 par_obj.get_LIS(), 0, par_obj.get_NS(), 0);
  text.push_back(line_data);


  int i_max = static_cast<int>(par_obj.get_NS());
  for(int i=0; i<i_max; i++)
  {
    line_data = efw_obj.write_cont(par_obj.get_QM()[i], par_obj.get_QI()[i],
                                   par_obj.get_IZAP()[i], par_obj.get_LFS()[i], 0, par_obj.get_NL()[i]);
    text.push_back(line_data);

    int j_max = static_cast<int>(par_obj.get_NL()[i]);
    for(int j=0; j<j_max; j++)
    {
      line_data = efw_obj.write_cont(par_obj.get_XMF1()[i][j], par_obj.get_XLFS1()[i][j],
                                     par_obj.get_MAT1()[i][j], par_obj.get_MT1()[i][j],
                                     par_obj.get_NC()[i][j],   par_obj.get_NI()[i][j]);
      text.push_back(line_data);

      //NC-type Sub-Sub-Subsections
      if( par_obj.get_NC()[i][j] > 0 )
      {
        for(int k=0; k<static_cast<int>(par_obj.get_NC()[i][j]); k++)
        {
          write_NC(i, j, k);
        }
      }

      //NI-type Sub-Sub-Subsections
      if( par_obj.get_NI()[i][j] > 0 )
      {
        for(int k=0; k<static_cast<int>(par_obj.get_NI()[i][j]); k++)
        {
          write_NI(i, j, k);
        }
      }
    }
  }

  line_data = efw_obj.write_mt_end();
  text.push_back(line_data);

  line_data.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF40Writer::write_NC(int i, int j, int k) 
{
  string         line_data;
  vector<string> str_vec;

  line_data = efw_obj.write_cont(0.0, 0.0, 0, par_obj.get_LTY()[i][j][k], 0, 0);
  text.push_back(line_data);


  if( par_obj.get_LTY()[i][j][k] == 0 )
  {
    int l_max   = static_cast<int>(par_obj.get_CI()[i][j][k].size());
    int list_no = l_max * 2;
    vector<Real> list_vec;
    list_vec.resize(list_no);

    int ele_no = 0;
    for(int l=0; l<l_max; l++)
    {
      list_vec[ele_no]   = par_obj.get_CI()[i][j][k][l];
      list_vec[ele_no+1] = par_obj.get_XMTI()[i][j][k][l];
      ele_no += 2;
    }

    str_vec = efw_obj.write_list(par_obj.get_E1()[i][j][k], par_obj.get_E2()[i][j][k],
                                 0, 0, list_no, l_max, list_vec);
  }
  else if( par_obj.get_LTY()[i][j][k] == 1 || par_obj.get_LTY()[i][j][k] == 2
        || par_obj.get_LTY()[i][j][k] == 3 )
  {
    int l_max   = static_cast<int>(par_obj.get_EI()[i][j][k].size());
    int list_no = l_max * 2 + 2;
    vector<Real> list_vec;
    list_vec.resize(list_no);

    list_vec[0] = par_obj.get_XMFS()[i][j][k];
    list_vec[1] = par_obj.get_XLFSS()[i][j][k];

    int ele_no = 2;
    for(int l=0; l<l_max; l++)
    {
      list_vec[ele_no]   = par_obj.get_EI()[i][j][k][l];
      list_vec[ele_no+1] = par_obj.get_WEI()[i][j][k][l];
      ele_no += 2;
    }

    str_vec = efw_obj.write_list(par_obj.get_E1()[i][j][k],   par_obj.get_E2()[i][j][k],
                                 par_obj.get_MATS()[i][j][k], par_obj.get_MTS()[i][j][k],
                                 list_no, l_max, list_vec);
  }

  int l_max = static_cast<int>(str_vec.size());
  for(int l=0; l<l_max; l++)
  {
    text.push_back(str_vec[l]);
  }

  line_data.clear();
  clr_obj.clear_vec_array1_str(str_vec);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF40Writer::write_NI(int i, int j, int k) 
{
  Integer LB = par_obj.get_LB()[i][j][k];

  if( LB >= 0 && LB <= 4 )
  {
    write_NI_lb00(i, j, k);
  }
  else if( LB == 5 )
  {
    write_NI_lb05(i, j, k);
  }
  else if( LB == 6 )
  {
    write_NI_lb06(i, j, k);
  }
  else if( LB == 8 || LB == 9 )
  {
    write_NI_lb00(i, j, k);
  }
  else
  {
    string class_name = "MF40Writer";
    string func_name  = "write_NI(MultiParser& mp_obj, int& line_no, int& i, int& j)";

    ostringstream oss00, oss01, oss02, oss03, oss04, oss05;
    oss00 << par_obj.get_mt_no();
    oss01 << i;
    oss02 << static_cast<int>(par_obj.get_NL()[i]);
    oss03 << j;
    oss04 << static_cast<int>(par_obj.get_NI()[i][j]);
  	oss05 << par_obj.get_LB()[i][j][k];
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

void MF40Writer::write_NI_lb00(int i, int j, int k) 
{
  string         line_data;
  vector<string> str_vec;

  int l_no    = static_cast<int>(par_obj.get_E_K()[i][j][k].size());
  int t_no    = static_cast<int>(par_obj.get_LT()[i][j][k]);
  int tot_no  = l_no + t_no;
  int list_no = tot_no * 2;
  vector<Real> list_vec;
  list_vec.resize(list_no);

  int ele_no = 0;
  for(int l=0; l<l_no; l++)
  {
    list_vec[ele_no]   = par_obj.get_E_K()[i][j][k][l];
    list_vec[ele_no+1] = par_obj.get_F_K()[i][j][k][l][0];
    ele_no += 2;
  }

  for(int l=0; l<t_no; l++)
  {
    list_vec[ele_no]   = par_obj.get_E_T()[i][j][k][l];
    list_vec[ele_no+1] = par_obj.get_F_T()[i][j][k][l][0];
    ele_no += 2;
  }

  str_vec = efw_obj.write_list(0.0, 0.0, par_obj.get_LT()[i][j][k], par_obj.get_LB()[i][j][k],
                               list_no, tot_no, list_vec);

  int l_max = static_cast<int>(str_vec.size());
  for(int l=0; l<l_max; l++)
  {
    text.push_back(str_vec[l]);
  }
  clr_obj.clear_vec_array1_str(str_vec);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF40Writer::write_NI_lb05(int i, int j, int k) 
{
  string         line_data;
  vector<string> str_vec;

  int ne = static_cast<int>(par_obj.get_E_K()[i][j][k].size());

  int list_no = 0;
  vector<Real> list_vec;
  if( par_obj.get_LT()[i][j][k] == 0 )
  {
    list_no = ne*(ne-1)+1;
    list_vec.resize(list_no);
  }
  else if( par_obj.get_LT()[i][j][k] == 1 )
  {
    list_no = (ne*(ne+1))/2;
    list_vec.resize(list_no);
  }

  int ele_no = 0;
  for(int l=0; l<ne; l++)
  {
    list_vec[ele_no] = par_obj.get_E_K()[i][j][k][l];
    ele_no++;
  }

  int l_max = static_cast<int>(par_obj.get_F_K()[i][j][k].size());
  for(int l=0; l<l_max; l++)
  {
    int m_max = static_cast<int>(par_obj.get_F_K()[i][j][k][l].size());
    for(int m=0; m<m_max; m++)
    {
      list_vec[ele_no] = par_obj.get_F_K()[i][j][k][l][m];
      ele_no++;
    }
  }


  str_vec = efw_obj.write_list(0.0, 0.0, par_obj.get_LT()[i][j][k], par_obj.get_LB()[i][j][k],
                               list_no, ne, list_vec);

  l_max = static_cast<int>(str_vec.size());
  for(int l=0; l<l_max; l++)
  {
    text.push_back(str_vec[l]);
  }
  clr_obj.clear_vec_array1_str(str_vec);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF40Writer::write_NI_lb06(int i, int j, int k) 
{
  string         line_data;
  vector<string> str_vec;

  int ner     = static_cast<int>(par_obj.get_E_K()[i][j][k].size());
  int nec     = static_cast<int>(par_obj.get_E_T()[i][j][k].size());
  int list_no = 1+ner*nec;

  vector<Real> list_vec;
  list_vec.resize(list_no);

  int ele_no = 0;
  for(int l=0; l<ner; l++)
  {
    list_vec[ele_no] = par_obj.get_E_K()[i][j][k][l];
    ele_no++;
  }

  int l_max = static_cast<int>(par_obj.get_E_T()[i][j][k].size());
  for(int l=0; l<l_max; l++)
  {
    list_vec[ele_no] = par_obj.get_E_T()[i][j][k][l];
    ele_no++;
  }

  l_max = static_cast<int>(par_obj.get_F_K()[i][j][k].size());
  for(int l=0; l<l_max; l++)
  {
    int m_max = static_cast<int>(par_obj.get_F_K()[i][j][k][l].size());
    for(int m=0; m<m_max; m++)
    {
      list_vec[ele_no] = par_obj.get_F_K()[i][j][k][l][m];
      ele_no++;
    }
  }


  str_vec = efw_obj.write_list(0.0, 0.0, par_obj.get_LT()[i][j][k], par_obj.get_LB()[i][j][k],
                               list_no, ner, list_vec);

  l_max = static_cast<int>(str_vec.size());
  for(int l=0; l<l_max; l++)
  {
    text.push_back(str_vec[l]);
  }
  clr_obj.clear_vec_array1_str(str_vec);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF40Writer::clear()
{
  clr_obj.clear_vec_array1_str(text);

  par_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> MF40Writer::get_endf_text_data(MF40Parser& MF40parser_obj)
{
  clear();
  par_obj = MF40parser_obj;

  write_endf();
  return text;
}

