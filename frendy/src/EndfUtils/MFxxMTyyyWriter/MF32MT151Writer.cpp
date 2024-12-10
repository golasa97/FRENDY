#include "EndfUtils/MFxxMTyyyWriter/MF32MT151Writer.hpp"

using namespace frendy;

//constructor
MF32MT151Writer::MF32MT151Writer(void)
{
  clear();
}

//destructor
MF32MT151Writer::~MF32MT151Writer(void)
{ 
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF32MT151Writer::write_endf() 
{
  clr_obj.clear_vec_array1_str(text);

  string         line_data;
  efw_obj.set_mat_mf_mt(par_obj.get_mat_no(), mf_no, mt_no);

  //Line No.01
  //ZAR, AWR, NIS
  line_data = efw_obj.write_cont(par_obj.get_ZAR(), par_obj.get_AWR(), 0, 0, par_obj.get_NIS(), 0);
  text.push_back(line_data);

  int i_max = static_cast<int>(par_obj.get_NIS());
  for(int i=0; i<i_max; i++)
  {
    line_data = efw_obj.write_cont(par_obj.get_ZAI()[i], par_obj.get_ABN()[i],
                                   0, par_obj.get_LFW()[i], par_obj.get_NER()[i], 0);
    text.push_back(line_data);

    int j_max = static_cast<int>(par_obj.get_NER()[i]);
    for(int j=0; j<j_max; j++)
    {
      line_data = efw_obj.write_cont(par_obj.get_EL()[i][j],  par_obj.get_EH()[i][j],
                                     par_obj.get_LRU()[i][j], par_obj.get_LRF()[i][j],
                                     par_obj.get_NRO()[i][j], par_obj.get_NAPS()[i][j]);
      text.push_back(line_data);

      if( par_obj.get_NRO()[i][j] == 0 )
      {
        write_nro00(i, j);
      }
      else
      {
        write_nro01(i, j);
      }
    }
  }


  line_data = efw_obj.write_mt_end();
  text.push_back(line_data);

  line_data.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF32MT151Writer::write_nro00(int i, int j)
{
  string line_data = efw_obj.write_cont(par_obj.get_SPI()[i][j], par_obj.get_AP()[i][j],
                                        par_obj.get_LAD()[i][j], par_obj.get_LCOMP()[i][j],
                                        par_obj.get_NLS()[i][j], par_obj.get_ISR()[i][j]);
  text.push_back(line_data);
  line_data.clear();

  if( par_obj.get_LCOMP()[i][j] == 0 )
  {
    if( par_obj.get_LRU()[i][j] == 2 )
    {
     write_lru02(i, j);
    }
    else
    {
      write_lcomp00(i, j);
    }
  }
  else if( par_obj.get_LCOMP()[i][j] == 1 )
  {
    if( par_obj.get_LRF()[i][j] == 1 || par_obj.get_LRF()[i][j] == 2 )
    {
      write_lcomp01_lrf01(i, j);
    }
    else if( par_obj.get_LRF()[i][j] == 3 )
    {
      write_lcomp01_lrf01(i, j);
    }
    else if( par_obj.get_LRF()[i][j] == 4 )
    {
      write_lcomp01_lrf01( i, j);
    }
    else if( par_obj.get_LRF()[i][j] == 7 )
    {
      write_lcomp01_lrf07(i, j);
    }
    else
    {
      string class_name = "MF32MT151Writer";
      string func_name  = "write_nro00(int i, int j)";

      ostringstream oss01, oss02, oss03, oss04, oss05;
      oss01 << i;
      oss02 << static_cast<int>(par_obj.get_NIS());
      oss03 << j;
      oss04 << static_cast<int>(par_obj.get_NER()[i]);
      oss05 << par_obj.get_LRF()[i][j];
      string str_data01 = "NIS : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "NER : " + oss03.str() + " / " + oss04.str();
      string str_data03 = "LRF : " + oss05.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      if( par_obj.get_LRF()[i][j] == 5 || par_obj.get_LRF()[i][j] == 6 )
      {
        err_com.push_back("The format of LCOMP = 5, 6 at MF=32, MT=151 is no longer available in ENDF-6.");
      }
      else
      {
        err_com.push_back("This LRF value at LCOMP=1 at MF=32, MT=151 is not supported in this program.");
        err_com.push_back("Supported LRF value at LCOMP=1 is 1 - 4 and 7.");
      }

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    if( par_obj.get_LRU()[i][j] == 1 && par_obj.get_NLRS_LCOMP01_LRF01()[i][j] > 0 )
    {
      int k_max = static_cast<int>(par_obj.get_NLRS_LCOMP01_LRF01()[i][j]);
      for(int k=0; k<k_max; k++)
      {
        write_lru01(i, j, k);
      }
    }
  }
  else if( par_obj.get_LCOMP()[i][j] == 2 )
  {
    if( par_obj.get_LRF()[i][j] == 1 || par_obj.get_LRF()[i][j] == 2 )
    {
      write_lcomp02_lrf01(i, j);
    }
    else if( par_obj.get_LRF()[i][j] == 3 )
    {
      write_lcomp02_lrf03(i, j);
    }
    else if( par_obj.get_LRF()[i][j] == 7 )
    {
      write_lcomp02_lrf07(i, j);
    }
    else
    {
      string class_name = "MF32MT151Write";
      string func_name  = "write_nro00(int i, int j)";

      ostringstream oss01, oss02, oss03, oss04, oss05;
      oss01 << i;
      oss02 << static_cast<int>(par_obj.get_NIS());
      oss03 << j;
      oss04 << static_cast<int>(par_obj.get_NER()[i]);
      oss05 << par_obj.get_LRF()[i][j];
      string str_data01 = "NIS : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "NER : " + oss03.str() + " / " + oss04.str();
      string str_data03 = "LRF : " + oss05.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back("This LRF at LCOMP=2 value at MF=32, MT=151 is not supported in this program.");
      err_com.push_back("Supported LRF value at LCOMP=2 is 1 - 3 and 7.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }
  else
  {
    string class_name = "MF32MT151Writer";
    string func_name  = "write_nro00(int i, int j)";

    ostringstream oss01, oss02, oss03, oss04, oss05;
    oss01 << i;
    oss02 << static_cast<int>(par_obj.get_NIS());
    oss03 << j;
    oss04 << static_cast<int>(par_obj.get_NER()[i]);
    oss05 << par_obj.get_LCOMP()[i][j];
    string str_data01 = "NIS   : " + oss01.str() + " / " + oss02.str();
    string str_data02 = "NER   : " + oss03.str() + " / " + oss04.str();
    string str_data03 = "LCOMP : " + oss05.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("This LCOMP value at MF=32, MT=151 is not supported in this program.");
    err_com.push_back("Supported LCOMP value is 0 - 2.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF32MT151Writer::write_lcomp00(int i, int j)
{
  vector<string> str_vec;

  if( par_obj.get_ISR()[i][j] > 0 )
  {
    string line_data = efw_obj.write_cont(0.0, par_obj.get_DAP_LCOMP00()[i][j], 0, 0, 0, 0);
    text.push_back(line_data);
    line_data.clear();
  }

  int k_max = static_cast<int>(par_obj.get_NLS()[i][j]);
  for(int k=0; k<k_max; k++)
  {
    vector<Real> list_vec;
    int l_max = static_cast<int>(par_obj.get_ER_LCOMP00()[i][j][k].size());
    list_vec.resize(l_max*18);

    int ele_no = 0;
    for(int l=0; l<l_max; l++)
    {
      list_vec[ele_no]    = par_obj.get_ER_LCOMP00()[i][j][k][l];
      list_vec[ele_no+ 1] = par_obj.get_AJ_LCOMP00()[i][j][k][l];
      list_vec[ele_no+ 2] = par_obj.get_GT_LCOMP00()[i][j][k][l];
      list_vec[ele_no+ 3] = par_obj.get_GN_LCOMP00()[i][j][k][l];
      list_vec[ele_no+ 4] = par_obj.get_GG_LCOMP00()[i][j][k][l];
      list_vec[ele_no+ 5] = par_obj.get_GF_LCOMP00()[i][j][k][l];
      list_vec[ele_no+ 6] = par_obj.get_DE_LCOMP00()[i][j][k][l];
      list_vec[ele_no+ 7] = par_obj.get_DN_LCOMP00()[i][j][k][l];
      list_vec[ele_no+ 8] = par_obj.get_DNDG_LCOMP00()[i][j][k][l];
      list_vec[ele_no+ 9] = par_obj.get_DG_LCOMP00()[i][j][k][l];
      list_vec[ele_no+10] = par_obj.get_DNDF_LCOMP00()[i][j][k][l];
      list_vec[ele_no+11] = par_obj.get_DGDF_LCOMP00()[i][j][k][l];
      list_vec[ele_no+12] = par_obj.get_DF_LCOMP00()[i][j][k][l];
      list_vec[ele_no+13] = par_obj.get_DJDN_LCOMP00()[i][j][k][l];
      list_vec[ele_no+14] = par_obj.get_DJDG_LCOMP00()[i][j][k][l];
      list_vec[ele_no+15] = par_obj.get_DJDF_LCOMP00()[i][j][k][l];
      list_vec[ele_no+16] = par_obj.get_DJ_LCOMP00()[i][j][k][l];
      list_vec[ele_no+17] = 0.0;
      ele_no += 18;
    }
  
    str_vec = efw_obj.write_list(par_obj.get_AWRI_LCOMP00()[i][j][k], 0.0,
                                 par_obj.get_L_LCOMP00()[i][j][k], 0, ele_no, l_max, list_vec);
    l_max = static_cast<int>(str_vec.size());
    for(int l=0; l<l_max; l++)
    {
      text.push_back(str_vec[l]);
    }
  }
  clr_obj.clear_vec_array1_str(str_vec);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF32MT151Writer::write_lcomp01_lrf01(int i, int j)
{
  string         line_data;
  vector<string> str_vec;

  if( par_obj.get_ISR()[i][j] > 0 )
  {
    if( par_obj.get_LRF()[i][j] == 1 || par_obj.get_LRF()[i][j] == 2 || par_obj.get_LRF()[i][j] == 4 )
    {
      line_data = efw_obj.write_cont(0.0, par_obj.get_DAP_LCOMP01_LRF01()[i][j], 0, 0, 0, 0);
      text.push_back(line_data);
    }
    else if( par_obj.get_LRF()[i][j] == 3 )
    {
      int k_max = static_cast<int>(par_obj.get_DAP_LCOMP01_LRF03()[i][j].size());
      str_vec = efw_obj.write_list(0.0, 0.0, 0, 0, k_max, 0, par_obj.get_DAP_LCOMP01_LRF03()[i][j]);
      k_max = static_cast<int>(str_vec.size());
      for(int k=0; k<k_max; k++)
      {
        text.push_back(str_vec[k]);
      }
    }
  }

  line_data = efw_obj.write_cont( par_obj.get_AWRI()[i][j], 0.0, 0, 0,
                                  par_obj.get_NSRS_LCOMP01_LRF01()[i][j],
                                  par_obj.get_NLRS_LCOMP01_LRF01()[i][j] );
  text.push_back(line_data);

  int k_max = static_cast<int>(par_obj.get_NSRS_LCOMP01_LRF01()[i][j]);
  for(int k=0; k<k_max; k++)
  {
    vector<Real> list_vec;

    int int_val = 0;
    int nvs     = 0;
    int ele_no  = 0;
    if( par_obj.get_LRF()[i][j] == 1 || par_obj.get_LRF()[i][j] == 2 ||
        par_obj.get_LRF()[i][j] == 3 )
    {
      if( par_obj.get_LRF()[i][j] == 1 || par_obj.get_LRF()[i][j] == 2 )
      {
        int_val = static_cast<int>(par_obj.get_ER_LCOMP01_LRF01()[i][j][k].size());
      }
      else
      {
        int_val = static_cast<int>(par_obj.get_ER_LCOMP01_LRF03()[i][j][k].size());
      }

      nvs    =  int_val * static_cast<int>(par_obj.get_MPAR_LCOMP01_LRF01()[i][j][k])
             * (int_val * static_cast<int>(par_obj.get_MPAR_LCOMP01_LRF01()[i][j][k]) + 1)/2;
      ele_no = nvs + 6*int_val;
      list_vec.resize(ele_no);

      if( par_obj.get_LRF()[i][j] == 1 || par_obj.get_LRF()[i][j] == 2 )
      {
        ele_no = 0;
        for(int l=0; l<int_val; l++)
        {
          list_vec[ele_no]   = par_obj.get_ER_LCOMP01_LRF01()[i][j][k][l];
          list_vec[ele_no+1] = par_obj.get_AJ_LCOMP01_LRF01()[i][j][k][l];
          list_vec[ele_no+2] = par_obj.get_GT_LCOMP01_LRF01()[i][j][k][l];
          list_vec[ele_no+3] = par_obj.get_GN_LCOMP01_LRF01()[i][j][k][l];
          list_vec[ele_no+4] = par_obj.get_GG_LCOMP01_LRF01()[i][j][k][l];
          list_vec[ele_no+5] = par_obj.get_GF_LCOMP01_LRF01()[i][j][k][l];
          ele_no += 6;
        }
      }
      else if( par_obj.get_LRF()[i][j] == 3 )
      {
        ele_no = 0;
        for(int l=0; l<int_val; l++)
        {
          list_vec[ele_no]   = par_obj.get_ER_LCOMP01_LRF03()[i][j][k][l];
          list_vec[ele_no+1] = par_obj.get_AJ_LCOMP01_LRF03()[i][j][k][l];
          list_vec[ele_no+2] = par_obj.get_GN_LCOMP01_LRF03()[i][j][k][l];
          list_vec[ele_no+3] = par_obj.get_GG_LCOMP01_LRF03()[i][j][k][l];
          list_vec[ele_no+4] = par_obj.get_GFA_LCOMP01_LRF03()[i][j][k][l];
          list_vec[ele_no+5] = par_obj.get_GFB_LCOMP01_LRF03()[i][j][k][l];
          ele_no += 6;
        }
      }
    }
    else if( par_obj.get_LRF()[i][j] == 4 )
    {
      int_val = static_cast<int>(par_obj.get_DET_LCOMP01_LRF04()[i][j][k].size());
      nvs     =  int_val * static_cast<int>(par_obj.get_MPAR_LCOMP01_LRF01()[i][j][k])
              * (int_val * static_cast<int>(par_obj.get_MPAR_LCOMP01_LRF01()[i][j][k]) + 1)/2;
      ele_no  = nvs + 12*int_val;
      list_vec.resize(ele_no);

      ele_no = 0;
      for(int l=0; l<int_val; l++)
      {
        list_vec[ele_no]    = par_obj.get_DET_LCOMP01_LRF04()[i][j][k][l];
        list_vec[ele_no+ 1] = par_obj.get_DWT_LCOMP01_LRF04()[i][j][k][l];
        list_vec[ele_no+ 2] = par_obj.get_GRT_LCOMP01_LRF04()[i][j][k][l];
        list_vec[ele_no+ 3] = par_obj.get_GIT_LCOMP01_LRF04()[i][j][k][l];
        list_vec[ele_no+ 4] = par_obj.get_DEF_LCOMP01_LRF04()[i][j][k][l];
        list_vec[ele_no+ 5] = par_obj.get_DWF_LCOMP01_LRF04()[i][j][k][l];
        list_vec[ele_no+ 6] = par_obj.get_GRF_LCOMP01_LRF04()[i][j][k][l];
        list_vec[ele_no+ 7] = par_obj.get_GIF_LCOMP01_LRF04()[i][j][k][l];
        list_vec[ele_no+ 8] = par_obj.get_DEC_LCOMP01_LRF04()[i][j][k][l];
        list_vec[ele_no+ 9] = par_obj.get_DWC_LCOMP01_LRF04()[i][j][k][l];
        list_vec[ele_no+10] = par_obj.get_GRC_LCOMP01_LRF04()[i][j][k][l];
        list_vec[ele_no+11] = par_obj.get_GIC_LCOMP01_LRF04()[i][j][k][l];
        ele_no += 12;
      }
    }

    for(int l=0; l<static_cast<int>(par_obj.get_V_LCOMP01_LRF01()[i][j][k].size()); l++)
    {
      for(int m=0; m<static_cast<int>(par_obj.get_V_LCOMP01_LRF01()[i][j][k][l].size()); m++)
      {
        list_vec[ele_no] = par_obj.get_V_LCOMP01_LRF01()[i][j][k][l][m];
        ele_no++;
      }
    }

    ele_no = static_cast<int>(list_vec.size());
    str_vec = efw_obj.write_list(0.0, 0.0, par_obj.get_MPAR_LCOMP01_LRF01()[i][j][k], 0,
                                 ele_no, int_val, list_vec);
    int l_max = static_cast<int>(str_vec.size());
    for(int l=0; l<l_max; l++)
    {
      text.push_back(str_vec[l]);
    }
  }

  clr_obj.clear_vec_array1_str(str_vec);
  line_data.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF32MT151Writer::write_lcomp01_lrf07(int i, int j)
{
  string         line_data;
  vector<string> str_vec;

  if( par_obj.get_ISR()[i][j] > 0 )
  {
    vector<Real> list_vec;
    int ele_no = 0;
    int njs    = static_cast<int>(par_obj.get_DAP_LCOMP01_LRF07()[i][j].size());
    for(int k=0; k<njs; k++)
    {
      ele_no += static_cast<int>(par_obj.get_DAP_LCOMP01_LRF07()[i][j][k].size());
    }
    list_vec.resize(ele_no);

    int nch = 0;
    ele_no  = 0;
    for(int k=0; k<njs; k++)
    {
      nch = static_cast<int>(par_obj.get_DAP_LCOMP01_LRF07()[i][j][k].size());
      for(int l=0; l<nch; l++)
      {
        list_vec[ele_no] = par_obj.get_DAP_LCOMP01_LRF07()[i][j][k][l];
        ele_no++;
      }
    }

    int int_val = 1 + (nch-1)/6;
    str_vec = efw_obj.write_list(0.0, 0.0, 0, 0, ele_no, int_val, list_vec);
    int k_max = static_cast<int>(str_vec.size());
    for(int k=0; k<k_max; k++)
    {
      text.push_back(str_vec[k]);
    }
  }

  line_data = efw_obj.write_cont
                (par_obj.get_AWRI_LCOMP01_LRF07()[i][j], 0.0, 0, 0,
                 par_obj.get_NSRS_LCOMP01_LRF07()[i][j], par_obj.get_NLRS_LCOMP01_LRF07()[i][j]);
  text.push_back(line_data);

  int k_max = static_cast<int>(par_obj.get_NSRS_LCOMP01_LRF07()[i][j]);
  for(int k=0; k<k_max; k++)
  {
    line_data = efw_obj.write_cont(0.0, 0.0, par_obj.get_NJSX_LCOMP01_LRF07()[i][j][k], 0, 0, 0);
    text.push_back(line_data);

    int l_max = static_cast<int>(par_obj.get_ER_LCOMP01_LRF07()[i][j][k].size());
    for(int l=0; l<l_max; l++)
    {
      vector<Real> list_vec;
      int nrb = static_cast<int>(par_obj.get_ER_LCOMP01_LRF07()[i][j][k][l].size());

      int ele_no = 0;
      for(int m=0; m<nrb; m++)
      {
        ele_no += static_cast<int>(par_obj.get_GAM_LCOMP01_LRF07()[i][j][k][l][m].size() + 1);
      }
      list_vec.resize(ele_no);

      int nch = 0;
      ele_no  = 0;
      for(int m=0; m<nrb; m++)
      {
        list_vec[ele_no] = par_obj.get_ER_LCOMP01_LRF07()[i][j][k][l][m];
        ele_no++;

        nch = static_cast<int>(par_obj.get_GAM_LCOMP01_LRF07()[i][j][k][l][m].size());
        for(int n=0; n<nch; n++)
        {
          list_vec[ele_no] = par_obj.get_GAM_LCOMP01_LRF07()[i][j][k][l][m][n];
          ele_no++;
        }
      }

      int int_val = ele_no / 6;
      str_vec = efw_obj.write_list(0.0, 0.0, nch, nrb, ele_no, int_val, list_vec);
      int m_max = static_cast<int>(str_vec.size());
      for(int m=0; m<m_max; m++)
      {
        text.push_back(str_vec[m]);
      }
    }


    vector<Real> list_vec;
    int int_val = static_cast<int>(par_obj.get_V_LCOMP01_LRF07()[i][j][k].size());
    int ele_no  = int_val * (int_val + 1) / 2;
    list_vec.resize(ele_no);

    ele_no = 0;
    for(int l=0; l<int_val; l++)
    {
      for(int m=0; m<static_cast<int>(par_obj.get_V_LCOMP01_LRF07()[i][j][k][l].size()); m++)
      {
        list_vec[ele_no] = par_obj.get_V_LCOMP01_LRF07()[i][j][k][l][m];
        ele_no++;
      }
    }

    ele_no  = static_cast<int>(list_vec.size());
    str_vec = efw_obj.write_list(0.0, 0.0, 0, 0, ele_no, int_val, list_vec);
    l_max   = static_cast<int>(str_vec.size());
    for(int l=0; l<l_max; l++)
    {
      text.push_back(str_vec[l]);
    }
  }

  clr_obj.clear_vec_array1_str(str_vec);
  line_data.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF32MT151Writer::write_lcomp02_lrf01(int i, int j)
{
  string         line_data;
  vector<string> str_vec;

  if( par_obj.get_ISR()[i][j] > 0 )
  {
    line_data = efw_obj.write_cont(0.0, par_obj.get_DAP_LCOMP02_LRF01()[i][j], 0, 0, 0, 0);
    text.push_back(line_data);
  }

  vector<Real> list_vec;
  int int_val = static_cast<int>(par_obj.get_ER_LCOMP02_LRF01()[i][j].size());
  int ele_no = int_val * 12;
  list_vec.resize(ele_no);

  ele_no = 0;
  for(int k=0; k<int_val; k++)
  {
    list_vec[ele_no]    = par_obj.get_ER_LCOMP02_LRF01()[i][j][k];
    list_vec[ele_no+ 1] = par_obj.get_AJ_LCOMP02_LRF01()[i][j][k];
    list_vec[ele_no+ 2] = par_obj.get_GT_LCOMP02_LRF01()[i][j][k];
    list_vec[ele_no+ 3] = par_obj.get_GN_LCOMP02_LRF01()[i][j][k];
    list_vec[ele_no+ 4] = par_obj.get_GG_LCOMP02_LRF01()[i][j][k];
    list_vec[ele_no+ 5] = par_obj.get_GF_LCOMP02_LRF01()[i][j][k];
    list_vec[ele_no+ 6] = par_obj.get_DER_LCOMP02_LRF01()[i][j][k];
    list_vec[ele_no+ 7] = 0.0;
    list_vec[ele_no+ 8] = 0.0;
    list_vec[ele_no+ 9] = par_obj.get_DGN_LCOMP02_LRF01()[i][j][k];
    list_vec[ele_no+10] = par_obj.get_DGG_LCOMP02_LRF01()[i][j][k];
    list_vec[ele_no+11] = par_obj.get_DGF_LCOMP02_LRF01()[i][j][k];
    ele_no += 12;
  }

  str_vec = efw_obj.write_list(par_obj.get_AWRI()[i][j], par_obj.get_QX_LCOMP02_LRF01()[i][j],
                                0, par_obj.get_LRX_LCOMP02_LRF01()[i][j], ele_no, int_val, list_vec);
  int k_max = static_cast<int>(str_vec.size());
  for(int k=0; k<k_max; k++)
  {
    text.push_back(str_vec[k]);
  }

  clr_obj.clear_vec_array1_str(str_vec);
  line_data.clear();

  write_lcomp02_intg(i, j);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF32MT151Writer::write_lcomp02_lrf03(int i, int j)
{
  vector<string> str_vec;

  if( par_obj.get_ISR()[i][j] == 1 )
  {
    vector<Real> list_vec = par_obj.get_DAP_LCOMP02_LRF03()[i][j];
    int          ele_no   = static_cast<int>(list_vec.size());

    str_vec = efw_obj.write_list(0.0, 0.0, 0, 0, ele_no, 0, list_vec);
    int k_max = static_cast<int>(str_vec.size());
    for(int k=0; k<k_max; k++)
    {
      text.push_back(str_vec[k]);
    }
  }

  vector<Real> list_vec;
  int int_val = static_cast<int>(par_obj.get_ER_LCOMP02_LRF03()[i][j].size());
  int ele_no  = int_val * 12;
  list_vec.resize(ele_no);

  ele_no = 0;
  for(int k=0; k<int_val; k++)
  {
    list_vec[ele_no]    = par_obj.get_ER_LCOMP02_LRF03()[i][j][k];
    list_vec[ele_no+ 1] = par_obj.get_AJ_LCOMP02_LRF03()[i][j][k];
    list_vec[ele_no+ 2] = par_obj.get_GN_LCOMP02_LRF03()[i][j][k];
    list_vec[ele_no+ 3] = par_obj.get_GG_LCOMP02_LRF03()[i][j][k];
    list_vec[ele_no+ 4] = par_obj.get_GFA_LCOMP02_LRF03()[i][j][k];
    list_vec[ele_no+ 5] = par_obj.get_GFB_LCOMP02_LRF03()[i][j][k];
    list_vec[ele_no+ 6] = par_obj.get_DER_LCOMP02_LRF03()[i][j][k];
    list_vec[ele_no+ 7] = 0.0;
    list_vec[ele_no+ 8] = par_obj.get_DGN_LCOMP02_LRF03()[i][j][k];
    list_vec[ele_no+ 9] = par_obj.get_DGG_LCOMP02_LRF03()[i][j][k];
    list_vec[ele_no+10] = par_obj.get_DGFA_LCOMP02_LRF03()[i][j][k];
    list_vec[ele_no+11] = par_obj.get_DGFB_LCOMP02_LRF03()[i][j][k];
    ele_no += 12;
  }

  str_vec = efw_obj.write_list(par_obj.get_AWRI()[i][j], par_obj.get_APL_LCOMP02_LRF03()[i][j],
                               0, 0, ele_no, int_val, list_vec);
  int k_max = static_cast<int>(str_vec.size());
  for(int k=0; k<k_max; k++)
  {
    text.push_back(str_vec[k]);
  }

  clr_obj.clear_vec_array1_str(str_vec);

  write_lcomp02_intg(i, j);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF32MT151Writer::write_lcomp02_lrf07(int i, int j)
{
  vector<string> str_vec;

  if( par_obj.get_ISR()[i][j] > 0 )
  {
    vector<Real> list_vec;
    int ele_no = 0;
    int njs    = static_cast<int>(par_obj.get_DAP_LCOMP02_LRF07()[i][j].size());
    for(int k=0; k<njs; k++)
    {
      ele_no += static_cast<int>(par_obj.get_DAP_LCOMP02_LRF07()[i][j][k].size());
    }
    list_vec.resize(ele_no);

    int nch = 0;
    ele_no  = 0;
    for(int k=0; k<njs; k++)
    {
      nch = static_cast<int>(par_obj.get_DAP_LCOMP02_LRF07()[i][j][k].size());
      for(int l=0; l<nch; l++)
      {
        list_vec[ele_no] = par_obj.get_DAP_LCOMP02_LRF07()[i][j][k][l];
        ele_no++;
      }
    }

    int int_val = 1 + (nch-1)/6;
    str_vec = efw_obj.write_list(0.0, 0.0, 0, 0, ele_no, int_val, list_vec);
    int k_max = static_cast<int>(str_vec.size());
    for(int k=0; k<k_max; k++)
    {
      text.push_back(str_vec[k]);
    }
  }

  vector<Real> list_vec;
  int npp     = static_cast<int>(par_obj.get_MA_LCOMP02_LRF07()[i][j].size());
  int int_val = npp *  2;
  int ele_no  = npp * 12;
  list_vec.resize(ele_no);

  ele_no = 0;
  for(int k=0; k<npp; k++)
  {
    list_vec[ele_no]    = par_obj.get_MA_LCOMP02_LRF07()[i][j][k];
    list_vec[ele_no+ 1] = par_obj.get_MB_LCOMP02_LRF07()[i][j][k];
    list_vec[ele_no+ 2] = par_obj.get_ZA_LCOMP02_LRF07()[i][j][k];
    list_vec[ele_no+ 3] = par_obj.get_ZB_LCOMP02_LRF07()[i][j][k];
    list_vec[ele_no+ 4] = par_obj.get_IA_LCOMP02_LRF07()[i][j][k];
    list_vec[ele_no+ 5] = par_obj.get_IB_LCOMP02_LRF07()[i][j][k];
    list_vec[ele_no+ 6] = par_obj.get_Q_LCOMP02_LRF07()[i][j][k];
    list_vec[ele_no+ 7] = par_obj.get_PNT_LCOMP02_LRF07()[i][j][k];
    list_vec[ele_no+ 8] = par_obj.get_SHF_LCOMP02_LRF07()[i][j][k];
    list_vec[ele_no+ 9] = par_obj.get_MT_LCOMP02_LRF07()[i][j][k];
    list_vec[ele_no+10] = par_obj.get_PA_LCOMP02_LRF07()[i][j][k];
    list_vec[ele_no+11] = par_obj.get_PB_LCOMP02_LRF07()[i][j][k];
    ele_no += 12;
  }

  str_vec = efw_obj.write_list(0.0, 0.0, npp, par_obj.get_NJSX_LCOMP02_LRF07()[i][j],
                               ele_no, int_val, list_vec);
  int k_max = static_cast<int>(str_vec.size());
  for(int k=0; k<k_max; k++)
  {
    text.push_back(str_vec[k]);
  }
  list_vec.clear();

  k_max = static_cast<int>(par_obj.get_NLS()[i][j]);
  for(int k=0; k<k_max; k++)
  {
    int nch = static_cast<int>(par_obj.get_PPI_LCOMP02_LRF07()[i][j][k].size());
    ele_no  = nch * 6;
    list_vec.resize(ele_no);

    ele_no = 0;
    for(int l=0; l<nch; l++)
    {
      list_vec[ele_no]    = par_obj.get_PPI_LCOMP02_LRF07()[i][j][k][l];
      list_vec[ele_no+ 1] = par_obj.get_L_LCOMP02_LRF07()[i][j][k][l];
      list_vec[ele_no+ 2] = par_obj.get_SCH_LCOMP02_LRF07()[i][j][k][l];
      list_vec[ele_no+ 3] = par_obj.get_BND_LCOMP02_LRF07()[i][j][k][l];
      list_vec[ele_no+ 4] = par_obj.get_APE_LCOMP02_LRF07()[i][j][k][l];
      list_vec[ele_no+ 5] = par_obj.get_APT_LCOMP02_LRF07()[i][j][k][l];
      ele_no += 6;
    }

    str_vec = efw_obj.write_list
                (par_obj.get_AJ_LCOMP02_LRF07()[i][j][k], par_obj.get_PJ_LCOMP02_LRF07()[i][j][k],
                 0, 0, ele_no, nch, list_vec);
    int l_max = static_cast<int>(str_vec.size());
    for(int l=0; l<l_max; l++)
    {
      text.push_back(str_vec[l]);
    }
    list_vec.clear();

    int nsra = static_cast<int>(par_obj.get_ER_LCOMP02_LRF07()[i][j][k].size());
    ele_no   = nsra * (nch+1)*2;
    list_vec.resize(ele_no);

    ele_no = 0;
    for(int l=0; l<nsra; l++)
    {
      list_vec[ele_no] = par_obj.get_ER_LCOMP02_LRF07()[i][j][k][l];
      ele_no++;
      for(int m=0; m<nch; m++)
      {
        list_vec[ele_no] = par_obj.get_GAM_LCOMP02_LRF07()[i][j][k][l][m];
        ele_no++;
      }

      list_vec[ele_no] = par_obj.get_DER_LCOMP02_LRF07()[i][j][k][l];
      ele_no++;
      for(int m=0; m<nch; m++)
      {
        list_vec[ele_no] = par_obj.get_DGAM_LCOMP02_LRF07()[i][j][k][l][m];
        ele_no++;
      }
    }

    int_val = ele_no / 12;
    str_vec = efw_obj.write_list(0.0, 0.0, 0, nsra, ele_no, int_val, list_vec);
    l_max = static_cast<int>(str_vec.size());
    for(int l=0; l<l_max; l++)
    {
      text.push_back(str_vec[l]);
    }
  }

  clr_obj.clear_vec_array1_str(str_vec);

  write_lcomp02_intg(i, j);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF32MT151Writer::write_lcomp02_intg(int i, int j)
{
  string line_data;
  line_data = efw_obj.write_cont(0.0, 0.0, par_obj.get_NDIGIT_LCOMP02_LRF01()[i][j],
                                           par_obj.get_NNN_LCOMP02_LRF01()[i][j],
                                           par_obj.get_NM_LCOMP02_LRF01()[i][j], 0);
  text.push_back(line_data);

  int k_max = static_cast<int>(par_obj.get_NM_LCOMP02_LRF01()[i][j]);
  int ele_no = static_cast<int>(text.size());
  text.resize(ele_no+k_max);

  vector<Integer>          ii_vec  = par_obj.get_II_LCOMP02_LRF01()[i][j];
  vector<Integer>          jj_vec  = par_obj.get_JJ_LCOMP02_LRF01()[i][j];
  vector<vector<Integer> > kij_vec = par_obj.get_KIJ_LCOMP02_LRF01()[i][j];
  for(int k=0; k<k_max; k++)
  {
    line_data = efw_obj.write_intg(ii_vec[k], jj_vec[k], kij_vec[k]);
    text[ele_no+k] = line_data;
  }
  ii_vec.clear();
  jj_vec.clear();
  vector<vector<Integer> >().swap(kij_vec);

  line_data.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF32MT151Writer::write_lru01(int i, int j, int k)
{
  vector<string> str_vec;

  vector<Real> list_vec;
  int int_val = static_cast<int>(par_obj.get_E_K_LRU01()[i][j][k].size());
  int ele_no  = 0;
  if( par_obj.get_LB_LRU01()[i][j][k] >= -1 && par_obj.get_LB_LRU01()[i][j][k] <= 2  )
  {
    ele_no = int_val * 2;
    list_vec.resize(ele_no);

    ele_no = 0;
    for(int l=0; l<int_val; l++)
    {
      list_vec[ele_no]   = par_obj.get_E_K_LRU01()[i][j][k][l];
      list_vec[ele_no+1] = par_obj.get_F_K_LRU01()[i][j][k][l][0];
      ele_no += 2;
    }
  }
  else if( par_obj.get_LB_LRU01()[i][j][k] == 5 )
  {
    ele_no = int_val * (int_val+1) / 2;
    list_vec.resize(ele_no);

    ele_no = 0;
    for(int l=0; l<int_val; l++)
    {
      list_vec[ele_no] = par_obj.get_E_K_LRU01()[i][j][k][l];
      ele_no++;
    }

    for(int l=0; l<int_val-1; l++)
    {
      for(int m=0; m<static_cast<int>(par_obj.get_F_K_LRU01()[i][j][k][l].size()); m++)
      {
        list_vec[ele_no] = par_obj.get_F_K_LRU01()[i][j][k][l][m];
        ele_no++;
      }
    }
  }
  else
  {
    string class_name = "MF32MT151Writer";
    string func_name  = "write_lru01(int i, int j, int k)";

    ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07;
    oss01 << i;
    oss02 << static_cast<int>(par_obj.get_NIS());
    oss03 << j;
    oss04 << static_cast<int>(par_obj.get_NER()[i]);
    oss05 << k;
    oss06 << static_cast<int>(par_obj.get_NLRS_LCOMP01_LRF01()[i][j]);
    oss07 << par_obj.get_LB_LRU01()[i][j][k];
    string str_data01 = "NIS  : " + oss01.str() + " / " + oss02.str();
    string str_data02 = "NER  : " + oss03.str() + " / " + oss04.str();
    string str_data03 = "NLRS : " + oss05.str() + " / " + oss06.str();
    string str_data04 = "LB   : " + oss07.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back("This LB value at LRU=1, MF=32, MT=151 is not supported in this program.");
    err_com.push_back("Supported LB value is -1 - 2 and 5.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  str_vec = efw_obj.write_list(0.0, 0.0, par_obj.get_IDP_LRU01()[i][j][k], par_obj.get_LB_LRU01()[i][j][k],
                               ele_no, int_val, list_vec);
  int l_max = static_cast<int>(str_vec.size());
  for(int l=0; l<l_max; l++)
  {
    text.push_back(str_vec[l]);
  }
  list_vec.clear();

  clr_obj.clear_vec_array1_str(str_vec);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF32MT151Writer::write_lru02(int i, int j)
{
  vector<string> str_vec;

  int k_max = static_cast<int>(par_obj.get_NLS()[i][j]);
  for(int k=0; k<k_max; k++)
  {
    vector<Real> list_vec;
    int int_val = static_cast<int>(par_obj.get_D_LRU02()[i][j][k].size());
    int ele_no  = int_val * 6;
    list_vec.resize(ele_no);

    ele_no = 0;
    for(int l=0; l<int_val; l++)
    {
      list_vec[ele_no]   = par_obj.get_D_LRU02()[i][j][k][l];
      list_vec[ele_no+1] = par_obj.get_AJ_LRU02()[i][j][k][l];
      list_vec[ele_no+2] = par_obj.get_GNO_LRU02()[i][j][k][l];
      list_vec[ele_no+3] = par_obj.get_GG_LRU02()[i][j][k][l];
      list_vec[ele_no+4] = par_obj.get_GF_LRU02()[i][j][k][l];
      list_vec[ele_no+5] = par_obj.get_GX_LRU02()[i][j][k][l];
      ele_no += 6;
    }

    str_vec = efw_obj.write_list(par_obj.get_AWRI_LRU02()[i][j][k], 0.0, par_obj.get_L_LRU02()[i][j][k], 0,
                                 ele_no, int_val, list_vec);
    int l_max = static_cast<int>(str_vec.size());
    for(int l=0; l<l_max; l++)
    {
      text.push_back(str_vec[l]);
    }
    list_vec.clear();
  }

  vector<Real> list_vec;
  int int_val = static_cast<int>(par_obj.get_RV_LRU02()[i][j].size());
  int ele_no  = int_val * (int_val+1) / 2;
  list_vec.resize(ele_no);

  ele_no = 0;
  for(int k=0; k<int_val; k++)
  {
    for(int l=0; l<static_cast<int>(par_obj.get_RV_LRU02()[i][j][k].size()); l++)
    {
      list_vec[ele_no] = par_obj.get_RV_LRU02()[i][j][k][l];
      ele_no++;
    }
  }

  str_vec = efw_obj.write_list(0.0, 0.0, par_obj.get_MPAR_LRU02()[i][j], 0,
                               ele_no, int_val, list_vec);
  k_max = static_cast<int>(str_vec.size());
  for(int k=0; k<k_max; k++)
  {
    text.push_back(str_vec[k]);
  }
  list_vec.clear();

  clr_obj.clear_vec_array1_str(str_vec);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF32MT151Writer::write_nro01(int i, int j)
{
  string line_data = efw_obj.write_cont(0.0, 0.0, 0, 0, 0, par_obj.get_NI()[i][j]);
  text.push_back(line_data);
  line_data.clear();

  if( par_obj.get_NI()[i][j] > 0 )
  {
    for(int k=0; k<static_cast<int>(par_obj.get_NI()[i][j]); k++)
    {
      write_NI(i, j, k);
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF32MT151Writer::write_NI(int i, int j, int k)
{
  if( par_obj.get_LB()[i][j][k] >= 0 && par_obj.get_LB()[i][j][k] <= 4 )
  {
    write_NI_lb00(i, j, k);
  }
  else if( par_obj.get_LB()[i][j][k] == 5 )
  {
    write_NI_lb05(i, j, k);
  }
  else if( par_obj.get_LB()[i][j][k] == 6 )
  {
    write_NI_lb06(i, j, k);
  }
  else if( par_obj.get_LB()[i][j][k] == 8 || par_obj.get_LB()[i][j][k] == 9 )
  {
    write_NI_lb00(i, j, k);
  }
  else
  {
    string class_name = "MF32MT151Writer";
    string func_name  = "write_NI(int i, int j, int k)";

    ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07;
    oss01 << i;
    oss02 << static_cast<int>(par_obj.get_NIS());
    oss03 << j;
    oss04 << static_cast<int>(par_obj.get_NER()[i]);
    oss05 << k;
    oss06 << static_cast<int>(par_obj.get_NI()[i][j]);
    oss07 << par_obj.get_LB()[i][j][k];
    string str_data01 = "NIS : " + oss01.str() + " / " + oss02.str();
    string str_data02 = "NER : " + oss03.str() + " / " + oss04.str();
    string str_data03 = "NI  : " + oss05.str() + " / " + oss06.str();
    string str_data04 = "LB  : " + oss07.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back("This LB value at MF=32, MT=151 is not supported in this program.");
    err_com.push_back("Supported LB value is 0 - 6, 8 and 9.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }



}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF32MT151Writer::write_NI_lb00(int i, int j, int k)
{
  vector<Real> list_vec;
  int int_val = static_cast<int>(par_obj.get_E_K()[i][j][k].size())
              + static_cast<int>(par_obj.get_LT()[i][j][k]);
  int ele_no  = int_val * 2;
  list_vec.resize(ele_no);

  ele_no = 0;
  for(int l=0; l<static_cast<int>(par_obj.get_E_K()[i][j][k].size()); l++)
  {
    list_vec[ele_no]   = par_obj.get_E_K()[i][j][k][l];
    list_vec[ele_no+1] = par_obj.get_F_K()[i][j][k][l][0];
    ele_no += 2;
  }

  for(int l=0; l<static_cast<int>(par_obj.get_LT()[i][j][k]); l++)
  {
    list_vec[ele_no]   = par_obj.get_E_T()[i][j][k][l];
    list_vec[ele_no+1] = par_obj.get_F_T()[i][j][k][l][0];
    ele_no += 2;
  }

  vector<string> str_vec;
  str_vec = efw_obj.write_list(0.0, 0.0, par_obj.get_LT()[i][j][k], par_obj.get_LB()[i][j][k],
                               ele_no, int_val, list_vec);
  int l_max = static_cast<int>(str_vec.size());
  for(int l=0; l<l_max; l++)
  {
    text.push_back(str_vec[l]);
  }
  list_vec.clear();

  clr_obj.clear_vec_array1_str(str_vec);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF32MT151Writer::write_NI_lb05(int i, int j, int k)
{
  vector<Real> list_vec;
  int int_val = static_cast<int>(par_obj.get_E_K()[i][j][k].size());
  int ele_no  = 0;
  if( par_obj.get_LT()[i][j][k] == 0 )
  {
    ele_no = int_val * (int_val-1) + 1;
  }
  else if( par_obj.get_LT()[i][j][k] == 1 )
  {
    ele_no = int_val * (int_val+1) / 2;
  }
  list_vec.resize(ele_no);

  ele_no = 0;
  for(int l=0; l<static_cast<int>(par_obj.get_E_K()[i][j][k].size()); l++)
  {
    list_vec[ele_no] = par_obj.get_E_K()[i][j][k][l];
    ele_no++;
  }

  if( par_obj.get_LT()[i][j][k] == 0 || par_obj.get_LT()[i][j][k] == 1 )
  {
    for(int l=0; l<int_val-1; l++)
    {
      for(int m=0; m<static_cast<int>(par_obj.get_F_K()[i][j][k][l].size()); m++)
      {
        list_vec[ele_no] = par_obj.get_F_K()[i][j][k][l][m];
        ele_no++;
      }
    }
  }
  else
  {
    string class_name = "MF32MT151Writer";
    string func_name  = "write_NI_lb05(int i, int j, int k)";

    ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07;
    oss01 << i;
    oss02 << static_cast<int>(par_obj.get_NIS());
    oss03 << j;
    oss04 << static_cast<int>(par_obj.get_NER()[i]);
    oss05 << k;
    oss06 << static_cast<int>(par_obj.get_NI()[i][j]);
    oss07 << par_obj.get_LT()[i][j][k];
    string str_data01 = "NIS : " + oss01.str() + " / " + oss02.str();
    string str_data02 = "NER : " + oss03.str() + " / " + oss04.str();
    string str_data03 = "NI  : " + oss05.str() + " / " + oss06.str();
    string str_data04 = "LS  : " + oss07.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back("This LS value at MF=32, MT=151 is not supported in this program.");
    err_com.push_back("Supported LS value is 0 and 1.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }


  vector<string> str_vec;
  str_vec = efw_obj.write_list(0.0, 0.0, par_obj.get_LT()[i][j][k], par_obj.get_LB()[i][j][k],
                               ele_no, int_val, list_vec);
  int l_max = static_cast<int>(str_vec.size());
  for(int l=0; l<l_max; l++)
  {
    text.push_back(str_vec[l]);
  }
  list_vec.clear();

  clr_obj.clear_vec_array1_str(str_vec);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF32MT151Writer::write_NI_lb06(int i, int j, int k)
{
  vector<Real> list_vec;
  int int_val = static_cast<int>(par_obj.get_E_K()[i][j][k].size());
  int nec     = static_cast<int>(par_obj.get_E_T()[i][j][k].size());
  int ele_no  = 1 + int_val * nec;
  list_vec.resize(ele_no);

  ele_no = 0;
  for(int l=0; l<int_val; l++)
  {
    list_vec[ele_no] = par_obj.get_E_K()[i][j][k][l];
    ele_no++;
  }

  for(int l=0; l<nec; l++)
  {
    list_vec[ele_no] = par_obj.get_E_T()[i][j][k][l];
    ele_no++;
  }

  for(int l=0; l<int_val-1; l++)
  {
    for(int m=0; m<nec-1; m++)
    {
      list_vec[ele_no] = par_obj.get_F_K()[i][j][k][l][m];
      ele_no++;
    }
  }

  vector<string> str_vec;
  str_vec = efw_obj.write_list(0.0, 0.0, par_obj.get_LT()[i][j][k], par_obj.get_LB()[i][j][k],
                               ele_no, int_val, list_vec);
  int l_max = static_cast<int>(str_vec.size());
  for(int l=0; l<l_max; l++)
  {
    text.push_back(str_vec[l]);
  }
  list_vec.clear();

  clr_obj.clear_vec_array1_str(str_vec);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF32MT151Writer::clear()
{
  clr_obj.clear_vec_array1_str(text);

  par_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> MF32MT151Writer::get_endf_text_data(MF32MT151Parser& MF32MT151parser_obj)
{
  clear();
  par_obj = MF32MT151parser_obj;

  write_endf();
  return text;
}

