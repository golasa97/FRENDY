#include "EndfUtils/MFxxMTyyyWriter/MF34Writer.hpp"

using namespace frendy;

//constructor
MF34Writer::MF34Writer(void)
{
  clear();
}

//destructor
MF34Writer::~MF34Writer(void)
{ 
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF34Writer::write_endf() 
{
  clr_obj.clear_vec_array1_str(text);

  string line_data;
  efw_obj.set_mat_mf_mt(par_obj.get_mat_no(), mf_no, par_obj.get_mt_no());

  //Line No.01
  //ZA, AWR, LTT, NMT1
  line_data = efw_obj.write_cont(par_obj.get_ZA(), par_obj.get_AWR(), 0, par_obj.get_LTT(),
                                 0, par_obj.get_NMT1());
  text.push_back(line_data);


  int i_max = static_cast<int>(par_obj.get_NMT1());
  for(int i=0; i<i_max; i++)
  {
    line_data = efw_obj.write_cont(0.0, 0.0, par_obj.get_MAT1()[i], par_obj.get_MT1()[i],
                                   par_obj.get_NL()[i],  par_obj.get_NL1()[i]);
    text.push_back(line_data);

    write_NSS(i);
  }

  line_data = efw_obj.write_mt_end();
  text.push_back(line_data);

  line_data.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF34Writer::write_NSS(int i) 
{
  string line_data;

  int j_max = static_cast<int>(par_obj.get_L()[i].size());
  for(int j=0; j<j_max; j++)
  {
    int k_max = static_cast<int>(par_obj.get_L()[i][j].size());
    for(int k=0; k<k_max; k++)
    {
      line_data = efw_obj.write_cont(0.0, 0.0, par_obj.get_L()[i][j][k], par_obj.get_L1()[i][j][k],
                                     par_obj.get_LCT()[i][j][k], par_obj.get_NI()[i][j][k]);
      text.push_back(line_data);

      int l_max = static_cast<int>(par_obj.get_NI()[i][j][k]);
      for(int l=0; l<l_max; l++)
      {
        if( par_obj.get_LB()[i][j][k][l] == 0 || par_obj.get_LB()[i][j][k][l] == 1
         || par_obj.get_LB()[i][j][k][l] == 2 )
        {
          write_lb00(i, j, k, l);
        }
        else if( par_obj.get_LB()[i][j][k][l] == 5 )
        {
          write_lb05(i, j, k, l);
        }
        else if( par_obj.get_LB()[i][j][k][l] == 6 )
        {
          write_lb06(i, j, k, l);
        }
        else
        {
          string class_name = "MF34Writer";
          string func_name  = "write_NSS(int i)";

          ostringstream oss00, oss01, oss02, oss03, oss04, oss05, oss06, oss07, oss08, oss09;
          oss00 << par_obj.get_mt_no();
          oss01 << i;
          oss02 << static_cast<int>(par_obj.get_NMT1());
          oss03 << j;
          oss04 << j_max;
          oss05 << k;
          oss06 << k_max;
          oss07 << l;
          oss08 << l_max;
          oss09 << par_obj.get_LB()[i][j][k][l];
          string str_data00 = "Section number (MT) : " + oss00.str();
          string str_data01 = "NNT1                : " + oss01.str() + " / " + oss02.str();
          string str_data02 = "J                   : " + oss03.str() + " / " + oss04.str();
          string str_data03 = "K                   : " + oss05.str() + " / " + oss06.str();
          string str_data04 = "L                   : " + oss07.str() + " / " + oss08.str();
          string str_data05 = "LB                  : " + oss09.str();

          vector<string> err_com;
          err_com.push_back(str_data00);
          err_com.push_back(str_data01);
          err_com.push_back(str_data02);
          err_com.push_back(str_data03);
          err_com.push_back(str_data04);
          err_com.push_back(str_data05);
          err_com.push_back("This LB value at MF=34 is not supported in this program.");
          err_com.push_back("Supported LB value is 0 - 2, 5 and 6.");

          err_obj.output_runtime_error(class_name, func_name, err_com);
        }
      }
    }
  }

  line_data.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF34Writer::write_lb00(int i, int j, int k, int l) 
{
  vector<Real> list_vec;
  int ele_no = static_cast<int>(par_obj.get_NT()[i][j][k][l]);
  list_vec.resize(ele_no);

  ele_no = 0;
  int m_max = static_cast<int>(par_obj.get_NE()[i][j][k][l] - par_obj.get_LS()[i][j][k][l]);
  for(int m=0; m<m_max; m++)
  {
    list_vec[ele_no]   =  par_obj.get_E_K()[i][j][k][l][m];
    list_vec[ele_no+1] =  par_obj.get_F_K()[i][j][k][l][m][0];
    ele_no += 2;
  }

  m_max = static_cast<int>(par_obj.get_LS()[i][j][k][l]);
  for(int m=0; m<m_max; m++)
  {
    list_vec[ele_no]   =  par_obj.get_E_T()[i][j][k][l][m];
    list_vec[ele_no+1] =  par_obj.get_F_T()[i][j][k][l][m][0];
    ele_no += 2;
  }

  vector<string> str_vec;
  str_vec = efw_obj.write_list(0.0, 0.0, par_obj.get_LS()[i][j][k][l], par_obj.get_LB()[i][j][k][l],
                               par_obj.get_NT()[i][j][k][l], par_obj.get_NE()[i][j][k][l], list_vec);
  m_max = static_cast<int>(str_vec.size());
  for(int m=0; m<m_max; m++)
  {
    text.push_back(str_vec[m]);
  }
  clr_obj.clear_vec_array1_str(str_vec);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF34Writer::write_lb05(int i, int j, int k, int l) 
{
  vector<Real> list_vec;
  int ele_no = static_cast<int>(par_obj.get_NT()[i][j][k][l]);
  list_vec.resize(ele_no);

  ele_no = 0;
  int m_max = static_cast<int>(par_obj.get_NE()[i][j][k][l]);
  for(int m=0; m<m_max; m++)
  {
    list_vec[ele_no] =  par_obj.get_E_K()[i][j][k][l][m];
    ele_no++;
  }

  if( par_obj.get_LS()[i][j][k][l] == 0 || par_obj.get_LS()[i][j][k][l] == 1 )
  {
    m_max = static_cast<int>(par_obj.get_F_K()[i][j][k][l].size());
    for(int m=0; m<m_max; m++)
    {
      int n_max = static_cast<int>(par_obj.get_F_K()[i][j][k][l][m].size());
      for(int n=0; n<n_max; n++)
      {
        list_vec[ele_no] =  par_obj.get_F_K()[i][j][k][l][m][n];
        ele_no++;
      }
    }
  }
  else
  {
    string class_name = "MF34Writer";
    string func_name  = "write_lb05(int i, int j, int k, int l)";

    ostringstream oss00, oss01, oss02, oss03, oss04, oss05, oss06;
    oss00 << par_obj.get_mt_no();
    oss01 << i;
    oss02 << static_cast<int>(par_obj.get_NMT1());
    oss03 << j;
    oss04 << k;
    oss05 << l;
  	oss06 << par_obj.get_LS()[i][j][k][l];
    string str_data00 = "Section number (MT) : " + oss00.str();
    string str_data01 = "NNT1                : " + oss01.str() + " / " + oss02.str();
    string str_data02 = "J                   : " + oss03.str();
    string str_data03 = "K                   : " + oss04.str();
    string str_data04 = "L                   : " + oss05.str();
    string str_data05 = "LS                  : " + oss06.str();

    vector<string> err_com;
    err_com.push_back(str_data00);
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back(str_data05);
    err_com.push_back("This LS value at MF=34 is not supported in this program.");
    err_com.push_back("Supported LS value is 0 and 1.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }


  vector<string> str_vec;
  str_vec = efw_obj.write_list(0.0, 0.0, par_obj.get_LS()[i][j][k][l], par_obj.get_LB()[i][j][k][l],
                               par_obj.get_NT()[i][j][k][l], par_obj.get_NE()[i][j][k][l], list_vec);
  m_max = static_cast<int>(str_vec.size());
  for(int m=0; m<m_max; m++)
  {
    text.push_back(str_vec[m]);
  }
  clr_obj.clear_vec_array1_str(str_vec);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF34Writer::write_lb06(int i, int j, int k, int l) 
{
  vector<Real> list_vec;
  int ele_no = static_cast<int>(par_obj.get_NT()[i][j][k][l]);
  list_vec.resize(ele_no);

  ele_no = 0;
  int m_max = static_cast<int>(par_obj.get_NE()[i][j][k][l]);
  for(int m=0; m<m_max; m++)
  {
    list_vec[ele_no] =  par_obj.get_E_K()[i][j][k][l][m];
    ele_no++;
  }

  m_max = static_cast<int>(par_obj.get_E_T()[i][j][k][l].size());
  for(int m=0; m<m_max; m++)
  {
    list_vec[ele_no] =  par_obj.get_E_T()[i][j][k][l][m];
    ele_no++;
  }

  m_max = static_cast<int>(par_obj.get_F_K()[i][j][k][l].size());
  for(int m=0; m<m_max; m++)
  {
    int n_max = static_cast<int>(par_obj.get_F_K()[i][j][k][l][m].size());
    for(int n=0; n<n_max; n++)
    {
      list_vec[ele_no] =  par_obj.get_F_K()[i][j][k][l][m][n];
      ele_no++;
    }
  }

  vector<string> str_vec;
  str_vec = efw_obj.write_list(0.0, 0.0, par_obj.get_LS()[i][j][k][l], par_obj.get_LB()[i][j][k][l],
                               par_obj.get_NT()[i][j][k][l], par_obj.get_NE()[i][j][k][l], list_vec);
  m_max = static_cast<int>(str_vec.size());
  for(int m=0; m<m_max; m++)
  {
    text.push_back(str_vec[m]);
  }
  clr_obj.clear_vec_array1_str(str_vec);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF34Writer::clear()
{
  clr_obj.clear_vec_array1_str(text);

  par_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> MF34Writer::get_endf_text_data(MF34Parser& MF34parser_obj)
{
  clear();
  par_obj = MF34parser_obj;

  write_endf();
  return text;
}

