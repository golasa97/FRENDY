#include "EndfUtils/MFxxMTyyyWriter/MF35Writer.hpp"

using namespace frendy;

//constructor
MF35Writer::MF35Writer(void)
{
  clear();
}

//destructor
MF35Writer::~MF35Writer(void)
{ 
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF35Writer::write_endf() 
{
  clr_obj.clear_vec_array1_str(text);

  string line_data;
  efw_obj.set_mat_mf_mt(par_obj.get_mat_no(), mf_no, par_obj.get_mt_no());

  //Line No.01
  //ZA, AWR, NK
  line_data = efw_obj.write_cont(par_obj.get_ZA(), par_obj.get_AWR(), 0, 0, par_obj.get_NK(), 0);
  text.push_back(line_data);


  int i_max = static_cast<int>(par_obj.get_NK());
  for(int i=0; i<i_max; i++)
  {
    /*if( par_obj.get_LB()[i] >= 0 && par_obj.get_LB()[i] <= 4 )
    {
      write_lb00(i);
    }
    else if( par_obj.get_LB()[i] == 5 )
    {
      write_lb05(i);
    }
    else if( par_obj.get_LB()[i] == 6 )
    {
      write_lb06(i);
    }
    else if( par_obj.get_LB()[i] == 7 )
    {
      write_lb05(i);
    }
    else if( par_obj.get_LB()[i]==8 || par_obj.get_LB()[i]==9 )
    {
      if( par_obj.get_LS()[i] != 0 )
      {
        string class_name = "MF35Writer";
        string func_name  = "write_data()";

        ostringstream oss00, oss01, oss02, oss03;
      	oss00 << par_obj.get_mt_no();
        oss01 << i;
        oss02 << static_cast<int>(par_obj.get_NK());
      	oss03 << par_obj.get_LS()[i];
        string str_data00 = "Section number (MT) : " + oss00.str();
        string str_data01 = "NK                  : " + oss01.str() + " / " + oss02.str();
        string str_data02 = "LS                  : " + oss03.str();

        vector<string> err_com;
        err_com.push_back(str_data00);
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back("IF you use LB=8 or 9, LS must be 0.");

        err_obj.output_runtime_error(class_name, func_name, err_com);
      }
      write_lb00(i);
    }*/

    if( par_obj.get_LB()[i] == 7 )
    {
      if( par_obj.get_LS()[i] != 1 )
      {
        string class_name = "MF35Writer";
        string func_name  = "write_data()";

        ostringstream oss00, oss01, oss02, oss03;
      	oss00 << par_obj.get_mt_no();
        oss01 << i;
        oss02 << static_cast<int>(par_obj.get_NK());
      	oss03 << par_obj.get_LS()[i];
        string str_data00 = "Section number (MT) : " + oss00.str();
        string str_data01 = "NK                  : " + oss01.str() + " / " + oss02.str();
        string str_data02 = "LS                  : " + oss03.str();

        vector<string> err_com;
        err_com.push_back(str_data00);
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back("IF you use LB=7, LS must be 1.");

        err_obj.output_runtime_error(class_name, func_name, err_com);
      }

      write_lb05(i);
    }
    else
    {
      string class_name = "MF35Writer";
      string func_name  = "write_data()";

      ostringstream oss00, oss01, oss02, oss03;
    	oss00 << par_obj.get_mt_no();
      oss01 << i;
      oss02 << static_cast<int>(par_obj.get_NK());
    	oss03 << par_obj.get_LB()[i];
      string str_data00 = "Section number (MT) : " + oss00.str();
      string str_data01 = "NK                  : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "LB                  : " + oss03.str();

      vector<string> err_com;
      err_com.push_back(str_data00);
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back("This LB value at MF=35 is not supported in this program.");
      err_com.push_back("Supported LB value is 0 - 9.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }

  line_data = efw_obj.write_mt_end();
  text.push_back(line_data);

  line_data.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF35Writer::write_lb00(int i)
{
  string         line_data;
  vector<string> str_vec;

  int j_no    = static_cast<int>(par_obj.get_E_K()[i].size());
  int t_no    = static_cast<int>(par_obj.get_LS()[i]);
  int tot_no  = j_no + t_no;
  int list_no = tot_no * 2;
  vector<Real> list_vec;
  list_vec.resize(list_no);

  int ele_no = 0;
  for(int j=0; j<j_no; j++)
  {
    list_vec[ele_no]   = par_obj.get_E_K()[i][j];
    list_vec[ele_no+1] = par_obj.get_F_K()[i][j][0];
    ele_no += 2;
  }

  for(int j=0; j<t_no; j++)
  {
    list_vec[ele_no]   = par_obj.get_E_T()[i][j];
    list_vec[ele_no+1] = par_obj.get_F_T()[i][j][0];
    ele_no += 2;
  }


  str_vec = efw_obj.write_list(par_obj.get_E1()[i], par_obj.get_E2()[i],
                               par_obj.get_LS()[i], par_obj.get_LB()[i],
                               par_obj.get_NT()[i], par_obj.get_NE()[i], list_vec);

  int j_max = static_cast<int>(str_vec.size());
  for(int j=0; j<j_max; j++)
  {
    text.push_back(str_vec[j]);
  }
  clr_obj.clear_vec_array1_str(str_vec);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF35Writer::write_lb05(int i)
{
  string         line_data;
  vector<string> str_vec;

  int ne = static_cast<int>(par_obj.get_E_K()[i].size());

  int list_no = 0;
  vector<Real> list_vec;
  if( par_obj.get_LS()[i] == 0 )
  {
    list_no = ne*(ne-1)+1;
  }
  else if( par_obj.get_LS()[i] == 1 )
  {
    list_no = (ne*(ne+1))/2;
  }
  list_vec.resize(list_no);

  int ele_no = 0;
  for(int j=0; j<ne; j++)
  {
    list_vec[ele_no] = par_obj.get_E_K()[i][j];
    ele_no++;
  }

  int j_max = static_cast<int>(par_obj.get_F_K()[i].size());
  for(int j=0; j<j_max; j++)
  {
    int k_max = static_cast<int>(par_obj.get_F_K()[i][j].size());
    for(int k=0; k<k_max; k++)
    {
      list_vec[ele_no] = par_obj.get_F_K()[i][j][k];
      ele_no++;
    }
  }


  efw_obj.set_digit_mod_mode(efw_obj.no_mod_digit);
  str_vec = efw_obj.write_list(par_obj.get_E1()[i], par_obj.get_E2()[i],
                               par_obj.get_LS()[i], par_obj.get_LB()[i],
                               par_obj.get_NT()[i], par_obj.get_NE()[i], list_vec);
  efw_obj.set_digit_mod_mode_default();

  j_max = static_cast<int>(str_vec.size());
  for(int j=0; j<j_max; j++)
  {
    text.push_back(str_vec[j]);
  }
  clr_obj.clear_vec_array1_str(str_vec);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF35Writer::write_lb06(int i)
{
  string         line_data;
  vector<string> str_vec;

  int ner     = static_cast<int>(par_obj.get_E_K()[i].size());
  int nec     = static_cast<int>(par_obj.get_E_T()[i].size());
  int list_no = 1+ner*nec;

  vector<Real> list_vec;
  list_vec.resize(list_no);

  int ele_no = 0;
  for(int j=0; j<ner; j++)
  {
    list_vec[ele_no] = par_obj.get_E_K()[i][j];
    ele_no++;
  }

  int j_max = static_cast<int>(par_obj.get_E_T()[i].size());
  for(int j=0; j<j_max; j++)
  {
    list_vec[ele_no] = par_obj.get_E_T()[i][j];
    ele_no++;
  }

  j_max = static_cast<int>(par_obj.get_F_K()[i].size());
  for(int j=0; j<j_max; j++)
  {
    int k_max = static_cast<int>(par_obj.get_F_K()[i][j].size());
    for(int k=0; k<k_max; k++)
    {
      list_vec[ele_no] = par_obj.get_F_K()[i][j][k];
      ele_no++;
    }
  }


  str_vec = efw_obj.write_list(par_obj.get_E1()[i], par_obj.get_E2()[i],
                               par_obj.get_LS()[i], par_obj.get_LB()[i],
                               par_obj.get_NT()[i], par_obj.get_NE()[i], list_vec);

  j_max = static_cast<int>(str_vec.size());
  for(int j=0; j<j_max; j++)
  {
    text.push_back(str_vec[j]);
  }
  clr_obj.clear_vec_array1_str(str_vec);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF35Writer::clear()
{
  clr_obj.clear_vec_array1_str(text);

  par_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> MF35Writer::get_endf_text_data(MF35Parser& MF35parser_obj)
{
  clear();
  par_obj = MF35parser_obj;

  write_endf();
  return text;
}

