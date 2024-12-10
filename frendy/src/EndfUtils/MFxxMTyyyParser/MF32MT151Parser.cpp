#include "EndfUtils/MFxxMTyyyParser/MF32MT151Parser.hpp"

using namespace frendy;

//constructor
MF32MT151Parser::MF32MT151Parser(void)
{
  clear();

  err_obj.set_output_mode(err_obj.warning_off);
}

//destructor
MF32MT151Parser::~MF32MT151Parser(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF32MT151Parser::store_data()
{
  MultiParser mp_obj;

  //Text file data check
  if( static_cast<Integer>(text.size()) < 2 )
  {
    string class_name = "MF32MT151Parser";
    string func_name  = "store_data()";

    ostringstream oss;
    oss << static_cast<Integer>(text.size());
    string str_data = "Text line number : " + oss.str();

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("The text line number is not appropriate for  MF=32, MT=151.");
    err_com.push_back("The text line number should be larger than 1.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //Check MT and MF number
  if( mp_obj.check_mf_mt(text, mf_no, mt_no) != 0)
  {
    string class_name = "MF32MT151Parser";
    string func_name  = "store_data()";

    ostringstream oss01, oss02;
    oss01 << mf_no;
    oss02 << mt_no;
    string str_data01 = "Text data at first line : " + text[0];
    string str_data02 = "File number (MF)        : " + oss01.str();
    string str_data03 = "Section number (MT)     : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("The MF and MT numbers are different to MF=32, MT=151.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  mp_obj.get_mat(text, mat_no);

  int     line_no = 0;
  Integer tmp_int;

  //Line No.01
  //ZAR, AWR, NIS
  mp_obj.read_head(text, line_no, ZAR, AWR, tmp_int, tmp_int, NIS, tmp_int);

  resize_matrix_vec_first(static_cast<int>(NIS));
  for(int i=0; i<static_cast<int>(NIS); i++)
  {
    vector<Real>    r_vec;
    vector<Integer> i_vec;
    r_vec.resize(6);
    i_vec.resize(6);

    mp_obj.read_cont(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3]);
    ZAI[i] = r_vec[0];
    ABN[i] = r_vec[1];
    LFW[i] = i_vec[1];
    NER[i] = i_vec[2];

    int ner_int = static_cast<int>(NER[i]);
    resize_matrix_vec_second(i, ner_int);
    for(int j=0; j<static_cast<int>(NER[i]); j++)
    {
      mp_obj.read_cont(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3]);
      EL[i][j]   = r_vec[0];
      EH[i][j]   = r_vec[1];
      LRU[i][j]  = i_vec[0];
      LRF[i][j]  = i_vec[1];
      NRO[i][j]  = i_vec[2];
      NAPS[i][j] = i_vec[3];

      if( NRO[i][j] == 0 )
      {
        store_nro00(mp_obj, line_no, i, j);
      }
      else
      {
        store_nro01(mp_obj, line_no, i, j);
      }
    }
    r_vec.clear();
    i_vec.clear();
  }

  mp_obj.line_no_check(text, line_no, mf_no, mt_no);

  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF32MT151Parser::store_nro00(MultiParser& mp_obj, int& line_no, int& i, int& j)
{
  vector<Real>    r_vec;
  vector<Integer> i_vec;
  r_vec.resize(6);
  i_vec.resize(6);

  mp_obj.read_cont(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3]);
  SPI[i][j]   = r_vec[0];
  AP[i][j]    = r_vec[1];
  LAD[i][j]   = i_vec[0];
  LCOMP[i][j] = i_vec[1];
  NLS[i][j]   = i_vec[2];
  ISR[i][j]   = i_vec[3];

  if( LCOMP[i][j] == 0 )
  {
    if( LRU[i][j] == 2 )
    {
      store_lru02(mp_obj, line_no, i, j);
    }
    else
    {
      store_lcomp00(mp_obj, line_no, i, j);
    }
  }
  else if( LCOMP[i][j] == 1 )
  {
    if( LRF[i][j] == 1 || LRF[i][j] == 2 )
    {
      store_lcomp01_lrf01(mp_obj, line_no, i, j);
    }
    else if( LRF[i][j] == 3 )
    {
      store_lcomp01_lrf01(mp_obj, line_no, i, j);
    }
    else if( LRF[i][j] == 4 )
    {
      store_lcomp01_lrf01(mp_obj, line_no, i, j);
    }
    else if( LRF[i][j] == 7 )
    {
      store_lcomp01_lrf07(mp_obj, line_no, i, j);
    }
    else
    {
      string class_name = "MF32MT151Parser";
      string func_name  = "store_nro00(MultiParser& mp_obj, int& line_no, int& i, int& j)";

      ostringstream oss01, oss02, oss03, oss04, oss05;
      oss01 << i;
      oss02 << static_cast<int>(NIS);
      oss03 << j;
      oss04 << static_cast<int>(NER[i]);
      oss05 << LRF[i][j];
      string str_data01 = "NIS : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "NER : " + oss03.str() + " / " + oss04.str();
      string str_data03 = "LRF : " + oss05.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      if( LRF[i][j] == 5 || LRF[i][j] == 6 )
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

    if( LRU[i][j] == 1 && NLRS[i][j] > 0 )
    {
      int nlrs = static_cast<int>(NLRS[i][j]);
      IDP_LRU01[i][j].resize(nlrs);
      LB_LRU01[i][j].resize( nlrs);
      E_K_LRU01[i][j].resize(nlrs);
      F_K_LRU01[i][j].resize(nlrs);
      for(int k=0; k<nlrs; k++)
      {
        store_lru01(mp_obj, line_no, i, j, k);
      }
    }
  }
  else if( LCOMP[i][j] == 2 )
  {
    if( LRF[i][j] == 1 || LRF[i][j] == 2 )
    {
      store_lcomp02_lrf01(mp_obj, line_no, i, j);
    }
    else if( LRF[i][j] == 3 )
    {
      store_lcomp02_lrf03(mp_obj, line_no, i, j);
    }
    else if( LRF[i][j] == 7 )
    {
      store_lcomp02_lrf07(mp_obj, line_no, i, j);
    }
    else
    {
      string class_name = "MF32MT151Parser";
      string func_name  = "store_nro00(MultiParser& mp_obj, int& line_no, int& i, int& j)";

      ostringstream oss01, oss02, oss03, oss04, oss05;
      oss01 << i;
      oss02 << static_cast<int>(NIS);
      oss03 << j;
      oss04 << static_cast<int>(NER[i]);
      oss05 << LRF[i][j];
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
    string class_name = "MF32MT151Parser";
    string func_name  = "store_nro00(MultiParser& mp_obj, int& line_no, int& i, int& j)";

    ostringstream oss01, oss02, oss03, oss04, oss05;
    oss01 << i;
    oss02 << static_cast<int>(NIS);
    oss03 << j;
    oss04 << static_cast<int>(NER[i]);
    oss05 << LCOMP[i][j];
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

void MF32MT151Parser::store_lcomp00(MultiParser& mp_obj, int& line_no, int& i, int& j)
{
  vector<Real>    r_vec;
  vector<Integer> i_vec;
  r_vec.resize(6);
  i_vec.resize(6);

  if( ISR[i][j] > 0 )
  {
    mp_obj.read_cont(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3]);
    DAP[i][j] = r_vec[1];
  }

  int nls = static_cast<int>(NLS[i][j]);
  AWRI_NLS[i][j].resize(nls);
  L[i][j].resize(nls);
  ER_LCOMP00[i][j].resize(nls);
  AJ_LCOMP00[i][j].resize(nls);
  GT_LCOMP00[i][j].resize(nls);
  GN_LCOMP00[i][j].resize(nls);
  GG_LCOMP00[i][j].resize(nls);
  GF_LCOMP00[i][j].resize(nls);
  DE_LCOMP00[i][j].resize(nls);
  DN_LCOMP00[i][j].resize(nls);
  DNDG_LCOMP00[i][j].resize(nls);
  DG_LCOMP00[i][j].resize(nls);
  DNDF_LCOMP00[i][j].resize(nls);
  DGDF_LCOMP00[i][j].resize(nls);
  DF_LCOMP00[i][j].resize(nls);
  DJDN_LCOMP00[i][j].resize(nls);
  DJDG_LCOMP00[i][j].resize(nls);
  DJDF_LCOMP00[i][j].resize(nls);
  DJ_LCOMP00[i][j].resize(nls);

  for(int k=0; k<nls; k++)
  {
    vector<Real> e_vec;
    mp_obj.read_list(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                     e_vec);
    if( i_vec[2] != 18*i_vec[3] )
    {
      string class_name = "MF32MT151Parser";
      string func_name  = "store_lcomp00(MultiParser& mp_obj, int& line_no, int& i, int& j)";

      ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07, oss08;
      oss01 << i;
      oss02 << static_cast<int>(NIS);
      oss03 << j;
      oss04 << static_cast<int>(NER[i]);
      oss05 << k;
      oss06 << static_cast<int>(NLS[i][j]);
      oss07 << i_vec[2];
      oss08 << i_vec[3];
      string str_data01 = "NIS    : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "NER    : " + oss03.str() + " / " + oss04.str();
      string str_data03 = "NLS    : " + oss05.str() + " / " + oss06.str();
      string str_data04 = "18*NRS : " + oss07.str();
      string str_data05 = "NRS    : " + oss08.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back(str_data04);
      err_com.push_back(str_data05);
      err_com.push_back("18*NRS at LCOMP=0 is not appropriate.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    AWRI_NLS[i][j][k] = r_vec[0];
    L[i][j][k]        = i_vec[0];

    int l_max = static_cast<int>(i_vec[3]);
    ER_LCOMP00[i][j][k].resize(l_max);
    AJ_LCOMP00[i][j][k].resize(l_max);
    GT_LCOMP00[i][j][k].resize(l_max);
    GN_LCOMP00[i][j][k].resize(l_max);
    GG_LCOMP00[i][j][k].resize(l_max);
    GF_LCOMP00[i][j][k].resize(l_max);
    DE_LCOMP00[i][j][k].resize(l_max);
    DN_LCOMP00[i][j][k].resize(l_max);
    DNDG_LCOMP00[i][j][k].resize(l_max);
    DG_LCOMP00[i][j][k].resize(l_max);
    DNDF_LCOMP00[i][j][k].resize(l_max);
    DGDF_LCOMP00[i][j][k].resize(l_max);
    DF_LCOMP00[i][j][k].resize(l_max);
    DJDN_LCOMP00[i][j][k].resize(l_max);
    DJDG_LCOMP00[i][j][k].resize(l_max);
    DJDF_LCOMP00[i][j][k].resize(l_max);
    DJ_LCOMP00[i][j][k].resize(l_max);

    for(int l=0; l<l_max; l++)
    {
      ER_LCOMP00[i][j][k][l]   = e_vec[18*l+ 0];
      AJ_LCOMP00[i][j][k][l]   = e_vec[18*l+ 1];
      GT_LCOMP00[i][j][k][l]   = e_vec[18*l+ 2];
      GN_LCOMP00[i][j][k][l]   = e_vec[18*l+ 3];
      GG_LCOMP00[i][j][k][l]   = e_vec[18*l+ 4];
      GF_LCOMP00[i][j][k][l]   = e_vec[18*l+ 5];
      DE_LCOMP00[i][j][k][l]   = e_vec[18*l+ 6];
      DN_LCOMP00[i][j][k][l]   = e_vec[18*l+ 7];
      DNDG_LCOMP00[i][j][k][l] = e_vec[18*l+ 8];
      DG_LCOMP00[i][j][k][l]   = e_vec[18*l+ 9];
      DNDF_LCOMP00[i][j][k][l] = e_vec[18*l+10];
      DGDF_LCOMP00[i][j][k][l] = e_vec[18*l+11];
      DF_LCOMP00[i][j][k][l]   = e_vec[18*l+12];
      DJDN_LCOMP00[i][j][k][l] = e_vec[18*l+13];
      DJDG_LCOMP00[i][j][k][l] = e_vec[18*l+14];
      DJDF_LCOMP00[i][j][k][l] = e_vec[18*l+15];
      DJ_LCOMP00[i][j][k][l]   = e_vec[18*l+16];
    }
    e_vec.clear();
  }
  r_vec.clear();
  i_vec.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF32MT151Parser::store_lcomp01_lrf01(MultiParser& mp_obj, int& line_no, int&i, int& j)
{
  vector<Real>    r_vec;
  vector<Integer> i_vec;
  r_vec.resize(6);
  i_vec.resize(6);

  vector<Real> e_vec;
  if( ISR[i][j] > 0 )
  {
    if( LRF[i][j] == 1 || LRF[i][j] == 2 || LRF[i][j] == 4 )
    {
      mp_obj.read_cont(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3]);
      DAP[i][j] = r_vec[1];
    }
    else if( LRF[i][j] == 3 )
    {
      mp_obj.read_list(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                       e_vec);
      DAP_TAB[i][j] = e_vec;
      e_vec.clear();
    }
  }

  mp_obj.read_cont(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3]);
  AWRI[i][j] = r_vec[0];
  NSRS[i][j] = i_vec[2];
  NLRS[i][j] = i_vec[3];

  resize_matrix_vec_nsrs(i, j);

  for(int k=0; k<static_cast<int>(NSRS[i][j]); k++)
  {
    mp_obj.read_list(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                     e_vec);
    MPAR_LCOMP01_LRF01[i][j][k] = i_vec[0];
    Integer nvs = i_vec[3]*MPAR_LCOMP01_LRF01[i][j][k] * (i_vec[3]*MPAR_LCOMP01_LRF01[i][j][k]+1) / 2;

    int ele_no = 0;
    if( LRF[i][j] == 1 || LRF[i][j] == 2 || LRF[i][j] == 3 )
    {
      ele_no = static_cast<int>(6*i_vec[3]);
      if( i_vec[2] != nvs + static_cast<Integer>(ele_no))
      {
        string class_name = "MF32MT151Parser";
        string func_name  = "store_lcomp01_lrf01(MultiParser& mp_obj, int& line_no, int&i, int& j)";

        ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07, oss08, oss09;
        oss01 << i;
        oss02 << static_cast<int>(NIS);
        oss03 << j;
        oss04 << static_cast<int>(NER[i]);
        oss05 << k;
        oss06 << static_cast<int>(NSRS[i][j]);
        oss07 << i_vec[2];
        oss08 << nvs;
        oss09 << i_vec[3];
        string str_data01 = "NIS       : " + oss01.str() + " / " + oss02.str();
        string str_data02 = "NER       : " + oss03.str() + " / " + oss04.str();
        string str_data03 = "NSRS      : " + oss05.str() + " / " + oss06.str();
        string str_data04 = "NVS+6*NRB : " + oss07.str();
        string str_data05 = "NVS       : " + oss08.str();
        string str_data06 = "NRB       : " + oss09.str();

        vector<string> err_com;
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back(str_data04);
        err_com.push_back(str_data05);
        err_com.push_back(str_data06);
        err_com.push_back("NVS+6*NRB at LCOMP=1, LRF=1 or 2 or 3 is not appropriate.");

        err_obj.output_runtime_error(class_name, func_name, err_com);
      }

      int l_max = static_cast<int>(i_vec[3]);
      if( LRF[i][j] == 1 || LRF[i][j] == 2 )
      {
        ER_LCOMP01_LRF01[i][j][k].resize(l_max);
        AJ_LCOMP01_LRF01[i][j][k].resize(l_max);
        GT_LCOMP01_LRF01[i][j][k].resize(l_max);
        GN_LCOMP01_LRF01[i][j][k].resize(l_max);
        GG_LCOMP01_LRF01[i][j][k].resize(l_max);
        GF_LCOMP01_LRF01[i][j][k].resize(l_max);

        for(int l=0; l<l_max; l++)
        {
          ER_LCOMP01_LRF01[i][j][k][l] = e_vec[6*l+0];
          AJ_LCOMP01_LRF01[i][j][k][l] = e_vec[6*l+1];
          GT_LCOMP01_LRF01[i][j][k][l] = e_vec[6*l+2];
          GN_LCOMP01_LRF01[i][j][k][l] = e_vec[6*l+3];
          GG_LCOMP01_LRF01[i][j][k][l] = e_vec[6*l+4];
          GF_LCOMP01_LRF01[i][j][k][l] = e_vec[6*l+5];
        }
      }
      else if( LRF[i][j] == 3 )
      {
        ER_LCOMP01_LRF03[i][j][k].resize( l_max);
        AJ_LCOMP01_LRF03[i][j][k].resize( l_max);
        GN_LCOMP01_LRF03[i][j][k].resize( l_max);
        GG_LCOMP01_LRF03[i][j][k].resize( l_max);
        GFA_LCOMP01_LRF03[i][j][k].resize(l_max);
        GFB_LCOMP01_LRF03[i][j][k].resize(l_max);

        for(int l=0; l<l_max; l++)
        {
          ER_LCOMP01_LRF03[i][j][k][l]  = e_vec[6*l+0];
          AJ_LCOMP01_LRF03[i][j][k][l]  = e_vec[6*l+1];
          GN_LCOMP01_LRF03[i][j][k][l]  = e_vec[6*l+2];
          GG_LCOMP01_LRF03[i][j][k][l]  = e_vec[6*l+3];
          GFA_LCOMP01_LRF03[i][j][k][l] = e_vec[6*l+4];
          GFB_LCOMP01_LRF03[i][j][k][l] = e_vec[6*l+5];
        }
      }
    }
    else if( LRF[i][j] == 4 )
    {
      ele_no = static_cast<int>(12*i_vec[3]);
      if( i_vec[2] != nvs + static_cast<Integer>(ele_no))
      {
        string class_name = "MF32MT151Parser";
        string func_name  = "store_lcomp01_lrf01(MultiParser& mp_obj, int& line_no, int&i, int& j)";

        ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07, oss08, oss09;
        oss01 << i;
        oss02 << static_cast<int>(NIS);
        oss03 << j;
        oss04 << static_cast<int>(NER[i]);
        oss05 << k;
        oss06 << static_cast<int>(NSRS[i][j]);
        oss07 << i_vec[2];
        oss08 << nvs;
        oss09 << i_vec[3];
        string str_data01 = "NIS        : " + oss01.str() + " / " + oss02.str();
        string str_data02 = "NER        : " + oss03.str() + " / " + oss04.str();
        string str_data03 = "NSRS       : " + oss05.str() + " / " + oss06.str();
        string str_data04 = "NVS+12*NRB : " + oss07.str();
        string str_data05 = "NVS        : " + oss08.str();
        string str_data06 = "NRB        : " + oss09.str();

        vector<string> err_com;
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back(str_data04);
        err_com.push_back(str_data05);
        err_com.push_back(str_data06);
        err_com.push_back("NVS+12*NRB at LCOMP=1, LRF=4 is not appropriate.");

        err_obj.output_runtime_error(class_name, func_name, err_com);
      }

      int l_max = static_cast<int>(i_vec[3]);
      DET_LCOMP01_LRF04[i][j][k].resize(l_max);
      DWT_LCOMP01_LRF04[i][j][k].resize(l_max);
      GRT_LCOMP01_LRF04[i][j][k].resize(l_max);
      GIT_LCOMP01_LRF04[i][j][k].resize(l_max);
      DEF_LCOMP01_LRF04[i][j][k].resize(l_max);
      DWF_LCOMP01_LRF04[i][j][k].resize(l_max);
      GRF_LCOMP01_LRF04[i][j][k].resize(l_max);
      GIF_LCOMP01_LRF04[i][j][k].resize(l_max);
      DEC_LCOMP01_LRF04[i][j][k].resize(l_max);
      DWC_LCOMP01_LRF04[i][j][k].resize(l_max);
      GRC_LCOMP01_LRF04[i][j][k].resize(l_max);
      GIC_LCOMP01_LRF04[i][j][k].resize(l_max);

      for(int l=0; l<l_max; l++)
      {
        DET_LCOMP01_LRF04[i][j][k][l] = e_vec[12*l+ 0];
        DWT_LCOMP01_LRF04[i][j][k][l] = e_vec[12*l+ 1];
        GRT_LCOMP01_LRF04[i][j][k][l] = e_vec[12*l+ 2];
        GIT_LCOMP01_LRF04[i][j][k][l] = e_vec[12*l+ 3];
        DEF_LCOMP01_LRF04[i][j][k][l] = e_vec[12*l+ 4];
        DWF_LCOMP01_LRF04[i][j][k][l] = e_vec[12*l+ 5];
        GRF_LCOMP01_LRF04[i][j][k][l] = e_vec[12*l+ 6];
        GIF_LCOMP01_LRF04[i][j][k][l] = e_vec[12*l+ 7];
        DEC_LCOMP01_LRF04[i][j][k][l] = e_vec[12*l+ 8];
        DWC_LCOMP01_LRF04[i][j][k][l] = e_vec[12*l+ 9];
        GRC_LCOMP01_LRF04[i][j][k][l] = e_vec[12*l+10];
        GIC_LCOMP01_LRF04[i][j][k][l] = e_vec[12*l+11];
      }
    }

    int l_no = static_cast<int>(i_vec[3]*MPAR_LCOMP01_LRF01[i][j][k]);
    V[i][j][k].resize(l_no);
    for(int l=0; l<l_no; l++)
    {
      int m_no = l_no - l;
      V[i][j][k][l].resize(m_no);
      for(int m=0; m<m_no; m++)
      {
        V[i][j][k][l][m] = e_vec[ele_no];
        ele_no++;
      }
    }
    e_vec.clear();
  }
  r_vec.clear();
  i_vec.clear();
  e_vec.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF32MT151Parser::store_lcomp01_lrf07(MultiParser& mp_obj, int& line_no, int& i, int& j)
{
  vector<Real>    r_vec;
  vector<Integer> i_vec;
  r_vec.resize(6);
  i_vec.resize(6);

  int njs = static_cast<int>(NLS[i][j]);
  vector<Real> e_vec;
  if( ISR[i][j] > 0 )
  {
    mp_obj.read_list(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                     e_vec);

    int nch = static_cast<int>(i_vec[2])/njs;
    if( njs*nch != static_cast<int>(i_vec[2]) )
    {
      string class_name = "MF32MT151Parser";
      string func_name  = "store_lcomp01_lrf07(MultiParser& mp_obj, int& line_no, int& i, int& j)";

      ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07;
      oss01 << i;
      oss02 << static_cast<int>(NIS);
      oss03 << j;
      oss04 << static_cast<int>(NER[i]);
      oss05 << i_vec[2];
      oss06 << njs;
      oss07 << nch;
      string str_data01 = "NIS          : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "NER          : " + oss03.str() + " / " + oss04.str();
      string str_data03 = "NJCH=NJS*NCH : " + oss05.str();
      string str_data04 = "NJS          : " + oss06.str();
      string str_data05 = "NCH          : " + oss07.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back(str_data04);
      err_com.push_back(str_data05);
      err_com.push_back("NJCH(=NJS*NCH) at LCOMP=1, LRF=7 is not appropriate.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    DAP_LRF07[i][j].resize(njs);
    for(int k=0; k<njs; k++)
    {
      DAP_LRF07[i][j][k].resize(nch);
      for(int l=0; l<nch; l++)
      {
        DAP_LRF07[i][j][k][l] = e_vec[nch*k+l];
      }
    }
    e_vec.clear();
  }

  mp_obj.read_cont(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3]);
  AWRI[i][j] = r_vec[0];
  NSRS[i][j] = i_vec[2];
  NLRS[i][j] = i_vec[3];

  resize_matrix_vec_nsrs(i, j);

  for(int k=0; k<static_cast<int>(NSRS[i][j]); k++)
  {
    mp_obj.read_cont(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3]);
    NJSX_LCOMP01_LRF07[i][j][k] = i_vec[0];

    njs = static_cast<int>(NJSX_LCOMP01_LRF07[i][j][k]);
    GAM_LCOMP01_LRF07[i][j][k].resize(njs);
    ER_LCOMP01_LRF07[i][j][k].resize(njs);
    for(int l=0; l<njs; l++)
    {
      mp_obj.read_list(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                       e_vec);
      int nch = static_cast<int>(i_vec[0]);
      int nrb = static_cast<int>(i_vec[1]);
      if(i_vec[2] != 6*i_vec[3])
      {
        string class_name = "MF32MT151Parser";
        string func_name  = "store_lcomp01_lrf07(MultiParser& mp_obj, int& line_no, int& i, int& j)";

        ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07, oss08;
        oss01 << i;
        oss02 << static_cast<int>(NIS);
        oss03 << j;
        oss04 << static_cast<int>(NER[i]);
        oss05 << k;
        oss06 << static_cast<int>(NSRS[i][j]);
        oss07 << i_vec[2];
        oss08 << i_vec[3];
        string str_data01 = "NIS  : " + oss01.str() + " / " + oss02.str();
        string str_data02 = "NER  : " + oss03.str() + " / " + oss04.str();
        string str_data03 = "NSRS : " + oss05.str() + " / " + oss06.str();
        string str_data04 = "6*NX : " + oss07.str();
        string str_data05 = "NX   : " + oss08.str();

        vector<string> err_com;
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back(str_data04);
        err_com.push_back(str_data05);
        err_com.push_back("6*NX at LCOMP=1, LRF=7 is not appropriate.");

        err_obj.output_runtime_error(class_name, func_name, err_com);
      }

      int ele_no = 0;
      ER_LCOMP01_LRF07[i][j][k][l].resize(nrb);
      GAM_LCOMP01_LRF07[i][j][k][l].resize(nrb);
      for(int m=0; m<nrb; m++)
      {
        ER_LCOMP01_LRF07[i][j][k][l][m] = e_vec[ele_no];
        ele_no++;

        GAM_LCOMP01_LRF07[i][j][k][l][m].resize(nch);
        for(int n=0; n<nch; n++)
        {
          GAM_LCOMP01_LRF07[i][j][k][l][m][n] = e_vec[ele_no];
          ele_no++;
        }
      }
      e_vec.clear();
    }

    mp_obj.read_list(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                     e_vec);
    int l_no = static_cast<int>(i_vec[3]);
    V[i][j][k].resize(l_no);
    int ele_no = 0;
    for(int l=0; l<l_no; l++)
    {
      int m_no = l_no - l;
      V[i][j][k][l].resize(m_no);
      for(int m=0; m<m_no; m++)
      {
        V[i][j][k][l][m] = e_vec[ele_no];
        ele_no++;
      }
    }
    e_vec.clear();
  }
  r_vec.clear();
  i_vec.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF32MT151Parser::store_lcomp02_lrf01(MultiParser& mp_obj, int& line_no, int& i, int& j)
{
  vector<Real>    r_vec;
  vector<Integer> i_vec;
  r_vec.resize(6);
  i_vec.resize(6);

  if( ISR[i][j] > 0 )
  {
    mp_obj.read_cont(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3]);
    DAP[i][j] = r_vec[1];
  }

  vector<Real> e_vec;
  mp_obj.read_list(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                   e_vec);
  AWRI[i][j] = r_vec[0];
  QX[i][j]   = r_vec[1];
  LRX[i][j]  = i_vec[1];

  if(i_vec[2] != 12*i_vec[3])
  {
    string class_name = "MF32MT151Parser";
    string func_name  = "store_lcomp02_lrf01(MultiParser& mp_obj, int& line_no, int& i, int& j)";

    ostringstream oss01, oss02, oss03, oss04, oss05, oss06;
    oss01 << i;
    oss02 << static_cast<int>(NIS);
    oss03 << j;
    oss04 << static_cast<int>(NER[i]);
    oss05 << i_vec[2];
    oss06 << i_vec[3];
    string str_data01 = "NIS     : " + oss01.str() + " / " + oss02.str();
    string str_data02 = "NER     : " + oss03.str() + " / " + oss04.str();
    string str_data03 = "12*NRSA : " + oss05.str();
    string str_data04 = "NRSA    : " + oss06.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back("12*NRSA at LCOMP=2, LRF=1 is not appropriate.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  int k_max = static_cast<int>(i_vec[3]);
  ER_LCOMP02_LRF01[i][j].resize(k_max);
  AJ_LCOMP02_LRF01[i][j].resize(k_max);
  GT_LCOMP02_LRF01[i][j].resize(k_max);
  GN_LCOMP02_LRF01[i][j].resize(k_max);
  GG_LCOMP02_LRF01[i][j].resize(k_max);
  GF_LCOMP02_LRF01[i][j].resize(k_max);
  DER_LCOMP02_LRF01[i][j].resize(k_max);
  DGN_LCOMP02_LRF01[i][j].resize(k_max);
  DGG_LCOMP02_LRF01[i][j].resize(k_max);
  DGF_LCOMP02_LRF01[i][j].resize(k_max);
  for(int k=0; k<k_max; k++)
  {
    ER_LCOMP02_LRF01[i][j][k] = e_vec[12*k+ 0];
    AJ_LCOMP02_LRF01[i][j][k] = e_vec[12*k+ 1];
    GT_LCOMP02_LRF01[i][j][k] = e_vec[12*k+ 2];
    GN_LCOMP02_LRF01[i][j][k] = e_vec[12*k+ 3];
    GG_LCOMP02_LRF01[i][j][k] = e_vec[12*k+ 4];
    GF_LCOMP02_LRF01[i][j][k] = e_vec[12*k+ 5];
    DER_LCOMP02_LRF01[i][j][k] = e_vec[12*k+ 6];
    DGN_LCOMP02_LRF01[i][j][k] = e_vec[12*k+ 9];
    DGG_LCOMP02_LRF01[i][j][k] = e_vec[12*k+10];
    DGF_LCOMP02_LRF01[i][j][k] = e_vec[12*k+11];
  }
  e_vec.clear();
  r_vec.clear();
  i_vec.clear();

  store_lcomp02_intg(mp_obj, line_no, i, j);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF32MT151Parser::store_lcomp02_lrf03(MultiParser& mp_obj, int& line_no, int& i, int& j)
{
  vector<Real>    r_vec;
  vector<Integer> i_vec;
  r_vec.resize(6);
  i_vec.resize(6);

  vector<Real> e_vec;
  if( ISR[i][j] == 1 )
  {
    mp_obj.read_list(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                     e_vec);
    DAP_TAB[i][j] = e_vec;
    e_vec.clear();
  }

  mp_obj.read_list(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                   e_vec);
  AWRI[i][j] = r_vec[0];
  APL[i][j]  = r_vec[1];

  if(i_vec[2] != 12*i_vec[3])
  {
    string class_name = "MF32MT151Parser";
    string func_name  = "store_lcomp02_lrf03(MultiParser& mp_obj, int& line_no, int& i, int& j)";

    ostringstream oss01, oss02, oss03, oss04, oss05, oss06;
    oss01 << i;
    oss02 << static_cast<int>(NIS);
    oss03 << j;
    oss04 << static_cast<int>(NER[i]);
    oss05 << i_vec[2];
    oss06 << i_vec[3];
    string str_data01 = "NIS     : " + oss01.str() + " / " + oss02.str();
    string str_data02 = "NER     : " + oss03.str() + " / " + oss04.str();
    string str_data03 = "12*NRSA : " + oss05.str();
    string str_data04 = "NRSA    : " + oss06.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back("12*NRSA at LCOMP=2, LRF=3 is not appropriate. Please check MF=32.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  int k_max = static_cast<int>(i_vec[3]);

  ER_LCOMP02_LRF03[i][j].resize(k_max);
  AJ_LCOMP02_LRF03[i][j].resize(k_max);
  GN_LCOMP02_LRF03[i][j].resize(k_max);
  GG_LCOMP02_LRF03[i][j].resize(k_max);
  GFA_LCOMP02_LRF03[i][j].resize(k_max);
  GFB_LCOMP02_LRF03[i][j].resize(k_max);
  DER_LCOMP02_LRF03[i][j].resize(k_max);
  DGN_LCOMP02_LRF03[i][j].resize(k_max);
  DGG_LCOMP02_LRF03[i][j].resize(k_max);
  DGFA_LCOMP02_LRF03[i][j].resize(k_max);
  DGFB_LCOMP02_LRF03[i][j].resize(k_max);
  for(int k=0; k<k_max; k++)
  {
    ER_LCOMP02_LRF03[i][j][k]   = e_vec[12*k+ 0];
    AJ_LCOMP02_LRF03[i][j][k]   = e_vec[12*k+ 1];
    GN_LCOMP02_LRF03[i][j][k]   = e_vec[12*k+ 2];
    GG_LCOMP02_LRF03[i][j][k]   = e_vec[12*k+ 3];
    GFA_LCOMP02_LRF03[i][j][k]  = e_vec[12*k+ 4];
    GFB_LCOMP02_LRF03[i][j][k]  = e_vec[12*k+ 5];
    DER_LCOMP02_LRF03[i][j][k]  = e_vec[12*k+ 6];
    DGN_LCOMP02_LRF03[i][j][k]  = e_vec[12*k+ 8];
    DGG_LCOMP02_LRF03[i][j][k]  = e_vec[12*k+ 9];
    DGFA_LCOMP02_LRF03[i][j][k] = e_vec[12*k+10];
    DGFB_LCOMP02_LRF03[i][j][k] = e_vec[12*k+11];
  }
  e_vec.clear();
  r_vec.clear();
  i_vec.clear();

  store_lcomp02_intg(mp_obj, line_no, i, j);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF32MT151Parser::store_lcomp02_lrf07(MultiParser& mp_obj, int& line_no, int& i, int& j)
{
  vector<Real>    r_vec;
  vector<Integer> i_vec;
  r_vec.resize(6);
  i_vec.resize(6);

  vector<Real> e_vec;
  int njs = static_cast<int>(NLS[i][j]);
  if( ISR[i][j] > 0 )
  {
    mp_obj.read_list(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                     e_vec);

    int nch = static_cast<int>(i_vec[2])/njs;
    if( njs*nch != static_cast<int>(i_vec[2]) )
    {
      string class_name = "MF32MT151Parser";
      string func_name  = "store_lcomp02_lrf07(MultiParser& mp_obj, int& line_no, int& i, int& j)";

      ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07;
      oss01 << i;
      oss02 << static_cast<int>(NIS);
      oss03 << j;
      oss04 << static_cast<int>(NER[i]);
      oss05 << i_vec[2];
      oss06 << njs;
      oss07 << nch;
      string str_data01 = "NIS          : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "NER          : " + oss03.str() + " / " + oss04.str();
      string str_data03 = "NJCH=NJS*NCH : " + oss05.str();
      string str_data04 = "NJS          : " + oss06.str();
      string str_data05 = "NCH          : " + oss07.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back(str_data04);
      err_com.push_back(str_data05);
      err_com.push_back("NJCH at LCOMP=2, LRF=7 is not appropriate.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    DAP_LRF07[i][j].resize(njs);
    for(int k=0; k<njs; k++)
    {
      DAP_LRF07[i][j][k].resize(nch);
      for(int l=0; l<nch; l++)
      {
        DAP_LRF07[i][j][k][l] = e_vec[nch*k+l];
      }
    }
    e_vec.clear();
  }

  mp_obj.read_list(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                   e_vec);
  NJSX_LCOMP02_LRF07[i][j] = i_vec[1];

  if(i_vec[2] != 6*i_vec[3])
  {
    string class_name = "MF32MT151Parser";
    string func_name  = "store_lcomp02_lrf07(MultiParser& mp_obj, int& line_no, int& i, int& j)";

    ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07;
    oss01 << i;
    oss02 << static_cast<int>(NIS);
    oss03 << j;
    oss04 << static_cast<int>(NER[i]);
    oss05 << i_vec[0];
    oss06 << i_vec[2];
    oss07 << i_vec[3];
    string str_data01 = "NIS    : " + oss01.str() + " / " + oss02.str();
    string str_data02 = "NER    : " + oss03.str() + " / " + oss04.str();
    string str_data03 = "NPP    : " + oss05.str();
    string str_data04 = "12*NPP : " + oss06.str();
    string str_data05 = " 2*NPP : " + oss07.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back(str_data05);
    err_com.push_back("12*NPP at LCOMP=2, LRF=7 is not appropriate.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  int k_max = static_cast<int>(i_vec[0]);
  MA_LCOMP02_LRF07[i][j].resize(k_max);
  MB_LCOMP02_LRF07[i][j].resize(k_max);
  ZA_LCOMP02_LRF07[i][j].resize(k_max);

  ZB_LCOMP02_LRF07[i][j].resize(k_max);
  IA_LCOMP02_LRF07[i][j].resize(k_max);
  IB_LCOMP02_LRF07[i][j].resize(k_max);

  Q_LCOMP02_LRF07[i][j].resize(k_max);
  PNT_LCOMP02_LRF07[i][j].resize(k_max);
  SHF_LCOMP02_LRF07[i][j].resize(k_max);

  MT_LCOMP02_LRF07[i][j].resize(k_max);
  PA_LCOMP02_LRF07[i][j].resize(k_max);
  PB_LCOMP02_LRF07[i][j].resize(k_max);
  for(int k=0; k<k_max; k++)
  {
    MA_LCOMP02_LRF07[i][j][k] = e_vec[12*k+ 0];
    MB_LCOMP02_LRF07[i][j][k] = e_vec[12*k+ 1];
    ZA_LCOMP02_LRF07[i][j][k] = e_vec[12*k+ 2];

    ZB_LCOMP02_LRF07[i][j][k] = e_vec[12*k+ 3];
    IA_LCOMP02_LRF07[i][j][k] = e_vec[12*k+ 4];
    IB_LCOMP02_LRF07[i][j][k] = e_vec[12*k+ 5];

    Q_LCOMP02_LRF07[i][j][k]   = e_vec[12*k+ 6];
    PNT_LCOMP02_LRF07[i][j][k] = e_vec[12*k+ 7];
    SHF_LCOMP02_LRF07[i][j][k] = e_vec[12*k+ 8];

    MT_LCOMP02_LRF07[i][j][k] = e_vec[12*k+ 9];
    PA_LCOMP02_LRF07[i][j][k] = e_vec[12*k+10];
    PB_LCOMP02_LRF07[i][j][k] = e_vec[12*k+11];
  }
  e_vec.clear();

  AJ_LCOMP02_LRF07[i][j].resize(njs);
  PJ_LCOMP02_LRF07[i][j].resize(njs);

  PPI_LCOMP02_LRF07[i][j].resize(njs);
  L_LCOMP02_LRF07[i][j].resize(  njs);
  SCH_LCOMP02_LRF07[i][j].resize(njs);
  BND_LCOMP02_LRF07[i][j].resize(njs);
  APE_LCOMP02_LRF07[i][j].resize(njs);
  APT_LCOMP02_LRF07[i][j].resize(njs);

  ER_LCOMP02_LRF07[i][j].resize(  njs);
  GAM_LCOMP02_LRF07[i][j].resize( njs);
  DER_LCOMP02_LRF07[i][j].resize( njs);
  DGAM_LCOMP02_LRF07[i][j].resize(njs);
  for(int k=0; k<njs; k++)
  {
    mp_obj.read_list(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                     e_vec);
    AJ_LCOMP02_LRF07[i][j][k] = r_vec[0];
    PJ_LCOMP02_LRF07[i][j][k] = r_vec[1];

    int nch = static_cast<int>(i_vec[3]);
    if(i_vec[2] != 6*i_vec[3])
    {
      string class_name = "MF32MT151Parser";
      string func_name  = "store_lcomp02_lrf07(MultiParser& mp_obj, int& line_no, int& i, int& j)";

      ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07, oss08;
      oss01 << i;
      oss02 << static_cast<int>(NIS);
      oss03 << j;
      oss04 << static_cast<int>(NER[i]);
      oss05 << k;
      oss06 << njs;
      oss07 << i_vec[2];
      oss08 << i_vec[3];
      string str_data01 = "NIS   : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "NER   : " + oss03.str() + " / " + oss04.str();
      string str_data03 = "NJS   : " + oss05.str() + " / " + oss06.str();
      string str_data04 = "6*NCH : " + oss07.str();
      string str_data05 = "NCH   : " + oss08.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back(str_data04);
      err_com.push_back(str_data05);
      err_com.push_back("6*NCH at LCOMP=2, LRF=7 is not appropriate.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    PPI_LCOMP02_LRF07[i][j][k].resize(nch);
    L_LCOMP02_LRF07[i][j][k].resize(  nch);
    SCH_LCOMP02_LRF07[i][j][k].resize(nch);
    BND_LCOMP02_LRF07[i][j][k].resize(nch);
    APE_LCOMP02_LRF07[i][j][k].resize(nch);
    APT_LCOMP02_LRF07[i][j][k].resize(nch);
    for(int l=0; l<nch; l++)
    {
      PPI_LCOMP02_LRF07[i][j][k][l] = e_vec[6*l+ 0];
      L_LCOMP02_LRF07[i][j][k][l]   = e_vec[6*l+ 1];
      SCH_LCOMP02_LRF07[i][j][k][l] = e_vec[6*l+ 2];
      BND_LCOMP02_LRF07[i][j][k][l] = e_vec[6*l+ 3];
      APE_LCOMP02_LRF07[i][j][k][l] = e_vec[6*l+ 4];
      APT_LCOMP02_LRF07[i][j][k][l] = e_vec[6*l+ 5];
    }
    e_vec.clear();

    mp_obj.read_list(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                     e_vec);

    if( i_vec[2] != 12*i_vec[3] && i_vec[3] != nch*i_vec[1] )
    {
      string class_name = "MF32MT151Parser";
      string func_name  = "store_lcomp02_lrf07(MultiParser& mp_obj, int& line_no, int& i, int& j)";

      ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07, oss08, oss09, oss10;
      oss01 << i;
      oss02 << static_cast<int>(NIS);
      oss03 << j;
      oss04 << static_cast<int>(NER[i]);
      oss05 << k;
      oss06 << njs;
      oss07 << i_vec[2];
      oss08 << i_vec[3];
      oss09 << i_vec[1];
      oss10 << nch;
      string str_data01 = "NIS   : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "NER   : " + oss03.str() + " / " + oss04.str();
      string str_data03 = "NJS   : " + oss05.str() + " / " + oss06.str();
      string str_data04 = "12*NX : " + oss07.str();
      string str_data05 = "NX    : " + oss08.str();
      string str_data06 = "NSRA  : " + oss09.str();
      string str_data07 = "NCH   : " + oss10.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back(str_data04);
      err_com.push_back(str_data05);
      err_com.push_back(str_data06);
      err_com.push_back(str_data07);
      err_com.push_back("12*NX at LCOMP=2, LRF=7 is not appropriate.");
      err_com.push_back("NX must be equal to NCH*NSRA when fifth parameter (12*NX) is not equal to NX * 12.");

      int line_no_nx = (nch+1)/6;
      if( (nch+1)%6 > 0 )
      {
        line_no_nx++;
      }
      line_no_nx *= i_vec[1];

      if( line_no_nx*12 != i_vec[2] )
      {
        err_obj.output_runtime_error(class_name, func_name, err_com);
      }
      else
      {
        err_obj.output_caution(class_name, func_name, err_com);
      }
    }

    int zero_no = (nch+1)%6;
    if( zero_no != 0 )
    {
      zero_no = 6 - zero_no;
    }
    int ele_no  = 0;
    int l_max   = static_cast<int>(i_vec[1]);
    ER_LCOMP02_LRF07[i][j][k].resize(  l_max);
    GAM_LCOMP02_LRF07[i][j][k].resize( l_max);
    DER_LCOMP02_LRF07[i][j][k].resize( l_max);
    DGAM_LCOMP02_LRF07[i][j][k].resize(l_max);
    for(int l=0; l<l_max; l++)
    {
      GAM_LCOMP02_LRF07[i][j][k][l].resize( nch);
      DGAM_LCOMP02_LRF07[i][j][k][l].resize(nch);

      ER_LCOMP02_LRF07[i][j][k][l] = e_vec[ele_no];
      ele_no++;
      for(int m=0; m<nch; m++)
      {
        GAM_LCOMP02_LRF07[i][j][k][l][m] = e_vec[ele_no];
        ele_no++;
      }
      ele_no += zero_no;

      DER_LCOMP02_LRF07[i][j][k][l] = e_vec[ele_no];
      ele_no++;
      for(int m=0; m<nch; m++)
      {
        DGAM_LCOMP02_LRF07[i][j][k][l][m] = e_vec[ele_no];
        ele_no++;
      }
      ele_no += zero_no;
    }
    e_vec.clear();
  }

  r_vec.clear();
  i_vec.clear();

  store_lcomp02_intg(mp_obj, line_no, i, j);
}


////////////////////////////////////////////////////////////////////////////////////////////////////

void MF32MT151Parser::store_lcomp02_intg(MultiParser& mp_obj, int& line_no, int& i, int& j)
{
  vector<Real>    r_vec;
  vector<Integer> i_vec;
  r_vec.resize(6);
  i_vec.resize(6);

  mp_obj.read_cont(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3]);
  NDIGIT[i][j] = i_vec[0];
  NNN[i][j]    = i_vec[1];
  NM[i][j]     = i_vec[2];

  int k_max = static_cast<int>(NM[i][j]);
  vector<Integer>          ii_vec, jj_vec;
  vector<vector<Integer> > kij_vec;
  ii_vec.resize(k_max);
  jj_vec.resize(k_max);
  kij_vec.resize(k_max);
  for(int k=0; k<k_max; k++)
  {
    vector<Integer> itg_vec;
    mp_obj.read_intg(text, line_no, NDIGIT[i][j], i_vec[1], i_vec[2], itg_vec);

    ii_vec[k]  = i_vec[1];
    jj_vec[k]  = i_vec[2];
    kij_vec[k] = itg_vec;

    itg_vec.clear();
  }
  II[i][j]  = ii_vec;
  JJ[i][j]  = jj_vec;
  KIJ[i][j] = kij_vec;


  r_vec.clear();
  i_vec.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF32MT151Parser::store_lru01(MultiParser& mp_obj, int& line_no, int& i, int& j, int& k)
{
  vector<Real>    r_vec;
  vector<Integer> i_vec;
  r_vec.resize(6);
  i_vec.resize(6);

  vector<Real>    e_vec;
  mp_obj.read_list(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                   e_vec);

  IDP_LRU01[i][j][k] = i_vec[0];
  LB_LRU01[i][j][k]  = i_vec[1];

  int l_no = static_cast<int>(i_vec[3]);
  E_K_LRU01[i][j][k].resize(l_no);
  F_K_LRU01[i][j][k].resize(l_no);
  if( LB_LRU01[i][j][k] >= -1 && LB_LRU01[i][j][k] <= 2  )
  {
    if(i_vec[2] != 2*i_vec[3])
    {
      string class_name = "MF32MT151Parser";
      string func_name  = "store_lru01(MultiParser& mp_obj, int& line_no, int& i, int& j, int& k)";

      ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07, oss08;
      oss01 << i;
      oss02 << static_cast<int>(NIS);
      oss03 << j;
      oss04 << static_cast<int>(NER[i]);
      oss05 << k;
      oss06 << static_cast<int>(NLRS[i][j]);
      oss07 << i_vec[2];
      oss08 << i_vec[3];
      string str_data01 = "NIS  : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "NER  : " + oss03.str() + " / " + oss04.str();
      string str_data03 = "NLRS : " + oss05.str() + " / " + oss06.str();
      string str_data04 = "2*NE : " + oss07.str();
      string str_data05 = "NE   : " + oss08.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back(str_data04);
      err_com.push_back(str_data05);
      err_com.push_back("2*NE at LCOMP=1, LRU=1 is not appropriate.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    for(int l=0; l<l_no; l++)
    {
      E_K_LRU01[i][j][k][l] =         e_vec[2*l];
      F_K_LRU01[i][j][k][l].push_back(e_vec[2*l+1]);
    }
  }
  else if( LB_LRU01[i][j][k] == 5 )
  {
    if(i_vec[2] != i_vec[3]*(i_vec[3]+1)/2)
    {
      string class_name = "MF32MT151Parser";
      string func_name  = "store_lru01(MultiParser& mp_obj, int& line_no, int& i, int& j, int& k)";

      ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07, oss08;
      oss01 << i;
      oss02 << static_cast<int>(NIS);
      oss03 << j;
      oss04 << static_cast<int>(NER[i]);
      oss05 << k;
      oss06 << static_cast<int>(NLRS[i][j]);
      oss07 << i_vec[2];
      oss08 << i_vec[3];
      string str_data01 = "NIS            : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "NER            : " + oss03.str() + " / " + oss04.str();
      string str_data03 = "NLRS           : " + oss05.str() + " / " + oss06.str();
      string str_data04 = "NT=NE*(NE+1)/2 : " + oss07.str();
      string str_data05 = "NE             : " + oss08.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back(str_data04);
      err_com.push_back(str_data05);
      err_com.push_back("NT at LCOMP=1, LRF=1 is not equal to NE*(NE+1)/2.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    int ele_no = 0;
    for(int l=0; l<l_no; l++)
    {
      E_K_LRU01[i][j][k][l] = e_vec[ele_no];
      ele_no++;
    }
    for(int l=0; l<l_no-1; l++)
    {
      int m_no = l_no-1 - l;
      F_K_LRU01[i][j][k][l].resize(m_no);
      for(int m=0; m<m_no; m++)
      {
        F_K_LRU01[i][j][k][l][m] = e_vec[ele_no];
        ele_no++;
      }
    }
  }
  else
  {
    string class_name = "MF32MT151Parser";
    string func_name  = "store_lru01(MultiParser& mp_obj, int& line_no, int& i, int& j, int& k)";

    ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07;
    oss01 << i;
    oss02 << static_cast<int>(NIS);
    oss03 << j;
    oss04 << static_cast<int>(NER[i]);
    oss05 << k;
    oss06 << static_cast<int>(NLRS[i][j]);
    oss07 << LB_LRU01[i][j][k];
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
  e_vec.clear();
  r_vec.clear();
  i_vec.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF32MT151Parser::store_lru02(MultiParser& mp_obj, int& line_no, int& i, int& j)
{
  vector<Real>    list_vec;
  list_vec.clear();

  vector<Real>    r_vec;
  vector<Integer> i_vec;
  r_vec.resize(6);
  i_vec.resize(6);

  int nls = NLS[i][j];
  AWRI_NLS[i][j].resize(nls);
  L[i][j].resize(nls);
  D_LRU02[i][j].resize(  nls);
  AJ_LRU02[i][j].resize( nls);
  GNO_LRU02[i][j].resize(nls);
  GG_LRU02[i][j].resize( nls);
  GF_LRU02[i][j].resize( nls);
  GX_LRU02[i][j].resize( nls);

  for(int k=0; k<nls; k++)
  {
    vector<Real> e_vec;
    mp_obj.read_list(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                     e_vec);
    AWRI_NLS[i][j][k] = r_vec[0];
    L[i][j][k]        = i_vec[0];

    if(i_vec[2] != 6*i_vec[3])
    {
      string class_name = "MF32MT151Parser";
      string func_name  = "store_lru02(MultiParser& mp_obj, int& line_no, int& i, int& j)";

      ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07, oss08;
      oss01 << i;
      oss02 << static_cast<int>(NIS);
      oss03 << j;
      oss04 << static_cast<int>(NER[i]);
      oss05 << k;
      oss06 << nls;
      oss07 << i_vec[2];
      oss08 << i_vec[3];
      string str_data01 = "NIS   : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "NER   : " + oss03.str() + " / " + oss04.str();
      string str_data03 = "NLS   : " + oss05.str() + " / " + oss06.str();
      string str_data04 = "6*NJS : " + oss07.str();
      string str_data05 = "NJS   : " + oss08.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back(str_data04);
      err_com.push_back(str_data05);
      err_com.push_back("6*NJS at LRU=2 is not appropriate.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    int l_max = static_cast<int>(i_vec[3]);
    D_LRU02[i][j][k].resize(  l_max);
    AJ_LRU02[i][j][k].resize( l_max);
    GNO_LRU02[i][j][k].resize(l_max);
    GG_LRU02[i][j][k].resize( l_max);
    GF_LRU02[i][j][k].resize( l_max);
    GX_LRU02[i][j][k].resize( l_max);
    for(int l=0; l<l_max; l++)
    {
      D_LRU02[i][j][k][l]   = e_vec[6*l+0];
      AJ_LRU02[i][j][k][l]  = e_vec[6*l+1];
      GNO_LRU02[i][j][k][l] = e_vec[6*l+2];
      GG_LRU02[i][j][k][l]  = e_vec[6*l+3];
      GF_LRU02[i][j][k][l]  = e_vec[6*l+4];
      GX_LRU02[i][j][k][l]  = e_vec[6*l+5];
    }
    e_vec.clear();
  }

  vector<Real> e_vec;
  mp_obj.read_list(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                   e_vec);
  MPAR_LRU02[i][j] = i_vec[0];

  int k_no   = static_cast<int>(i_vec[3]);
  if( static_cast<int>(i_vec[2]) != k_no*(k_no+1)/2)
  {
    string class_name = "MF32MT151Parser";
    string func_name  = "store_lru02(MultiParser& mp_obj, int& line_no, int& i, int& j)";

    ostringstream oss01, oss02, oss03, oss04, oss05, oss06;
    oss01 << i;
    oss02 << static_cast<int>(NIS);
    oss03 << j;
    oss04 << static_cast<int>(NER[i]);
    oss05 << i_vec[2];
    oss06 << i_vec[3];
    string str_data01 = "NIS             : " + oss01.str() + " / " + oss02.str();
    string str_data02 = "NER             : " + oss03.str() + " / " + oss04.str();
    string str_data03 = "NPAR*(NPAR+1)/2 : " + oss05.str();
    string str_data04 = "NPAR            : " + oss06.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back("NPAR*(NPAR+1)/2 at LRU=2 is not appropriate.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  int ele_no = 0;
  RV_LRU02[i][j].resize(k_no);
  for(int k=0; k<k_no; k++)
  {
    int l_no = k_no - k;
    RV_LRU02[i][j][k].resize(l_no);
    for(int l=0; l<l_no; l++)
    {
      RV_LRU02[i][j][k][l] = e_vec[ele_no];
      ele_no++;
    }
  }
  e_vec.clear();

  r_vec.clear();
  i_vec.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF32MT151Parser::store_nro01(MultiParser& mp_obj, int& line_no, int& i, int& j)
{
  vector<Real>    r_vec;
  vector<Integer> i_vec;
  r_vec.resize(6);
  i_vec.resize(6);

  mp_obj.read_cont(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3]);
  NI[i][j] = i_vec[3];

  if( NI[i][j] > 0 )
  {
    resize_matrix_vec_nro01(i, j, static_cast<int>(NI[i][j]));

    for(int k=0; k<static_cast<int>(NI[i][j]); k++)
    {
      store_NI(mp_obj, line_no, i, j, k);
    }
  }
  r_vec.clear();
  i_vec.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF32MT151Parser::store_NI(MultiParser& mp_obj, int& line_no, int& i, int& j, int& k)
{
  vector<Real>    r_vec;
  vector<Integer> i_vec;
  r_vec.resize(6);
  i_vec.resize(6);

  vector<Real> e_vec;
  mp_obj.read_list(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                   e_vec);
  LB[i][j][k] = i_vec[1];

  if( LB[i][j][k] >= 0 && LB[i][j][k] <= 4 )
  {
    store_NI_lb00(r_vec, i_vec, e_vec, i, j, k);
  }
  else if( LB[i][j][k] == 5 )
  {
    store_NI_lb05(r_vec, i_vec, e_vec, i, j, k);
  }
  else if( LB[i][j][k] == 6 )
  {
    store_NI_lb06(r_vec, i_vec, e_vec, i, j, k);
  }
  else if( LB[i][j][k] == 8 || LB[i][j][k] == 9 )
  {
    if( i_vec[0] != 0 )
    {
      string class_name = "MF32MT151Parser";
      string func_name  = "store_NI(MultiParser& mp_obj, int& line_no, int& i, int& j, int& k)";

      ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07;
      oss01 << i;
      oss02 << static_cast<int>(NIS);
      oss03 << j;
      oss04 << static_cast<int>(NER[i]);
      oss05 << k;
      oss06 << static_cast<int>(NI[i][j]);
      oss07 << i_vec[0];
      string str_data01 = "NIS : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "NER : " + oss03.str() + " / " + oss04.str();
      string str_data03 = "NI  : " + oss05.str() + " / " + oss06.str();
      string str_data04 = "LT  : " + oss07.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back(str_data04);
      err_com.push_back("When you use LB=8 or 9, LT must be 0.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
    store_NI_lb00(r_vec, i_vec, e_vec, i, j, k);
  }
  else
  {
    string class_name = "MF32MT151Parser";
    string func_name  = "store_NI(MultiParser& mp_obj, int& line_no, int& i, int& j, int& k)";

    ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07;
    oss01 << i;
    oss02 << static_cast<int>(NIS);
    oss03 << j;
    oss04 << static_cast<int>(NER[i]);
    oss05 << k;
    oss06 << static_cast<int>(NI[i][j]);
    oss07 << LB[i][j][k];
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
  r_vec.clear();
  i_vec.clear();
  e_vec.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF32MT151Parser::store_NI_lb00(vector<Real>& r_vec, vector<Integer>& i_vec, vector<Real>& e_vec,
                               int& i, int& j, int& k)
{
  LT[i][j][k] = i_vec[0];

  if( i_vec[2]!=2*i_vec[3] )
  {
    string class_name = "MF32MT151Parser";
    string func_name  = "store_NI_lb00(vector<Real>& r_vec, vector<Integer>& i_vec, vector<Real>& e_vec, ";
           func_name += "int& i, int& j, int& k)";

    ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07, oss08;
    oss01 << i;
    oss02 << static_cast<int>(NIS);
    oss03 << j;
    oss04 << static_cast<int>(NER[i]);
    oss05 << k;
    oss06 << static_cast<int>(NI[i][j]);
    oss07 << i_vec[2];
    oss08 << i_vec[3];
    string str_data01 = "NIS     : " + oss01.str() + " / " + oss02.str();
    string str_data02 = "NER     : " + oss03.str() + " / " + oss04.str();
    string str_data03 = "NI      : " + oss05.str() + " / " + oss06.str();
    string str_data04 = "NT=2*NP : " + oss07.str();
    string str_data05 = "NP      : " + oss08.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back(str_data05);
    err_com.push_back("NT is not equal to 2*NP at LB=0-4, 8-9.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  int lt_k = static_cast<int>(i_vec[3] - LT[i][j][k]);
  E_K[i][j][k].resize(lt_k);
  F_K[i][j][k].resize(lt_k);
  E_T[i][j][k].resize(static_cast<int>(LT[i][j][k]));
  F_T[i][j][k].resize(static_cast<int>(LT[i][j][k]));
  for(int l=0; l<lt_k; l++)
  {
    E_K[i][j][k][l] =         e_vec[2*l];
    F_K[i][j][k][l].push_back(e_vec[2*l+1]);
  }
  for(int l=0; l<static_cast<int>(LT[i][j][k]); l++)
  {
    E_T[i][j][k][l] =         e_vec[2*lt_k+2*l];
    F_T[i][j][k][l].push_back(e_vec[2*lt_k+2*l+1]);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF32MT151Parser::store_NI_lb05(vector<Real>& r_vec, vector<Integer>& i_vec, vector<Real>& e_vec,
                               int& i, int& j, int& k)
{
  LT[i][j][k] = i_vec[0];

  int ne = static_cast<int>(i_vec[3]);
  E_K[i][j][k].resize(ne);
  for(int l=0; l<ne; l++)
  {
    E_K[i][j][k][l] = e_vec[l];
  }

  if( LT[i][j][k] == 0 )
  {
    if( i_vec[2]!=ne*(ne-1)+1 )
    {
      string class_name = "MF32MT151Parser";
      string func_name  = "store_NI_lb05(vector<Real>& r_vec, vector<Integer>& i_vec, vector<Real>& e_vec, ";
             func_name += "int& i, int& j, int& k)";

      ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07, oss08;
      oss01 << i;
      oss02 << static_cast<int>(NIS);
      oss03 << j;
      oss04 << static_cast<int>(NER[i]);
      oss05 << k;
      oss06 << static_cast<int>(NI[i][j]);
      oss07 << i_vec[2];
      oss08 << ne;
      string str_data01 = "NIS           : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "NER           : " + oss03.str() + " / " + oss04.str();
      string str_data03 = "NI            : " + oss05.str() + " / " + oss06.str();
      string str_data04 = "NT=NE(NE-1)+1 : " + oss07.str();
      string str_data05 = "NE            : " + oss08.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back(str_data04);
      err_com.push_back(str_data05);
      err_com.push_back("NT at LB=5, LS=0 is not equal to NE(NE-1)+1.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    int ele_no = ne;
    F_K[i][j][k].resize(ne-1);
    for(int l=0; l<ne-1; l++)
    {
      F_K[i][j][k][l].resize(ne-1);
      for(int m=0; m<ne-1; m++)
      {
        F_K[i][j][k][l][m] = e_vec[ele_no];
        ele_no++;
      }
    }
  }
  else if( LT[i][j][k] == 1 )
  {
    if( i_vec[2]!=ne*(ne+1)/2 )
    {
      string class_name = "MF32MT151Parser";
      string func_name  = "store_NI_lb05(vector<Real>& r_vec, vector<Integer>& i_vec, vector<Real>& e_vec, ";
             func_name += "int& i, int& j, int& k)";

      ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07, oss08;
      oss01 << i;
      oss02 << static_cast<int>(NIS);
      oss03 << j;
      oss04 << static_cast<int>(NER[i]);
      oss05 << k;
      oss06 << static_cast<int>(NI[i][j]);
      oss07 << i_vec[2];
      oss08 << ne;
      string str_data01 = "NIS           : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "NER           : " + oss03.str() + " / " + oss04.str();
      string str_data03 = "NI            : " + oss05.str() + " / " + oss06.str();
      string str_data04 = "NT=NE(NE+1)/2 : " + oss07.str();
      string str_data05 = "NE            : " + oss08.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back(str_data04);
      err_com.push_back(str_data05);
      err_com.push_back("NT at LB=5, LS=1 is not equal to NE(NE+1)/2.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    int ele_no = ne;
    F_K[i][j][k].resize(ne-1);
    for(int l=0; l<ne-1; l++)
    {
      int ne_d = ne-1-l;
      F_K[i][j][k][l].resize(ne_d);
      for(int m=0; m<ne_d; m++)
      {
        F_K[i][j][k][l][m] = e_vec[ele_no];
        ele_no++;
      }
    }
  }
  else
  {
    string class_name = "MF32MT151Parser";
    string func_name  = "store_NI_lb05(vector<Real>& r_vec, vector<Integer>& i_vec, vector<Real>& e_vec, ";
           func_name += "int& i, int& j, int& k)";

    ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07;
    oss01 << i;
    oss02 << static_cast<int>(NIS);
    oss03 << j;
    oss04 << static_cast<int>(NER[i]);
    oss05 << k;
    oss06 << static_cast<int>(NI[i][j]);
    oss07 << LT[i][j][k];
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
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF32MT151Parser::store_NI_lb06(vector<Real>& r_vec, vector<Integer>& i_vec, vector<Real>& e_vec,
                               int& i, int& j, int& k)
{
  LT[i][j][k] = i_vec[0];

  int ner =  i_vec[3];
  int nec = (i_vec[2] - 1)/ner;

  if( i_vec[2] != 1+ner*nec )
  {
    string class_name = "MF32MT151Parser";
    string func_name  = "store_NI_lb06(vector<Real>& r_vec, vector<Integer>& i_vec, vector<Real>& e_vec, ";
           func_name += "int& i, int& j, int& k)";

    ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07, oss08, oss09;
    oss01 << i;
    oss02 << static_cast<int>(NIS);
    oss03 << j;
    oss04 << static_cast<int>(NER[i]);
    oss05 << k;
    oss06 << static_cast<int>(NI[i][j]);
    oss07 << i_vec[2];
    oss08 << ner;
    oss09 << nec;
    string str_data01 = "NIS          : " + oss01.str() + " / " + oss02.str();
    string str_data02 = "NER          : " + oss03.str() + " / " + oss04.str();
    string str_data03 = "NI           : " + oss05.str() + " / " + oss06.str();
    string str_data04 = "NT=1+NER*NEC : " + oss07.str();
    string str_data05 = "NER          : " + oss08.str();
    string str_data06 = "NEC          : " + oss09.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back(str_data05);
    err_com.push_back(str_data06);
    err_com.push_back("NT at LB=6 is not equal to 1+NER*NEC.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  E_K[i][j][k].resize(ner);
  for(int l=0; l<ner; l++)
  {
    E_K[i][j][k][l] =  e_vec[l];
  }

  int ele_no = ner;
  E_T[i][j][k].resize(nec);
  for(int l=0; l<nec; l++)
  {
    E_T[i][j][k][l] =  e_vec[ele_no];
    ele_no++;
  }

  F_K[i][j][k].resize(ner-1);
  for(int l=0; l<ner-1; l++)
  {
    F_K[i][j][k][l].resize(nec-1);
    for(int m=0; m<nec-1; m++)
    {
      F_K[i][j][k][l][m] = e_vec[ele_no];
      ele_no++;
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF32MT151Parser::resize_matrix_vec_first(int ele_no)
{
  ZAI.resize(ele_no);
  ABN.resize(ele_no);
  LFW.resize(ele_no);
  NER.resize(ele_no);

  EL.resize(  ele_no);
  EH.resize(  ele_no);
  LRU.resize( ele_no);
  LRF.resize( ele_no);
  NRO.resize( ele_no);
  NAPS.resize(ele_no);

  SPI.resize(  ele_no);
  AP.resize(   ele_no);
  LAD.resize(  ele_no);
  LCOMP.resize(ele_no);
  NLS.resize(  ele_no);
  ISR.resize(  ele_no);

  DAP.resize(      ele_no);
  DAP_TAB.resize(  ele_no);
  DAP_LRF07.resize(ele_no);

  AWRI.resize(ele_no);
  QX.resize(  ele_no);
  APL.resize( ele_no);
  NSRS.resize(ele_no);
  NLRS.resize(ele_no);
  LRX.resize( ele_no);

  V.resize(ele_no);

  NDIGIT.resize(ele_no);
  NNN.resize(   ele_no);
  NM.resize(    ele_no);
  II.resize( ele_no);
  JJ.resize( ele_no);
  KIJ.resize(ele_no);

  AWRI_NLS.resize(ele_no);
  L.resize(ele_no);

  ER_LCOMP00.resize(  ele_no);
  AJ_LCOMP00.resize(  ele_no);
  GT_LCOMP00.resize(  ele_no);
  GN_LCOMP00.resize(  ele_no);
  GG_LCOMP00.resize(  ele_no);
  GF_LCOMP00.resize(  ele_no);
  DE_LCOMP00.resize(  ele_no);
  DN_LCOMP00.resize(  ele_no);
  DNDG_LCOMP00.resize(ele_no);
  DG_LCOMP00.resize(  ele_no);
  DNDF_LCOMP00.resize(ele_no);
  DGDF_LCOMP00.resize(ele_no);
  DF_LCOMP00.resize(  ele_no);
  DJDN_LCOMP00.resize(ele_no);
  DJDG_LCOMP00.resize(ele_no);
  DJDF_LCOMP00.resize(ele_no);
  DJ_LCOMP00.resize(  ele_no);

  MPAR_LCOMP01_LRF01.resize(ele_no);

  ER_LCOMP01_LRF01.resize(ele_no);
  AJ_LCOMP01_LRF01.resize(ele_no);
  GT_LCOMP01_LRF01.resize(ele_no);
  GN_LCOMP01_LRF01.resize(ele_no);
  GG_LCOMP01_LRF01.resize(ele_no);
  GF_LCOMP01_LRF01.resize(ele_no);

  ER_LCOMP01_LRF03.resize( ele_no);
  AJ_LCOMP01_LRF03.resize( ele_no);
  GN_LCOMP01_LRF03.resize( ele_no);
  GG_LCOMP01_LRF03.resize( ele_no);
  GFA_LCOMP01_LRF03.resize(ele_no);
  GFB_LCOMP01_LRF03.resize(ele_no);

  DET_LCOMP01_LRF04.resize(ele_no);
  DWT_LCOMP01_LRF04.resize(ele_no);
  GRT_LCOMP01_LRF04.resize(ele_no);
  GIT_LCOMP01_LRF04.resize(ele_no);
  DEF_LCOMP01_LRF04.resize(ele_no);
  DWF_LCOMP01_LRF04.resize(ele_no);
  GRF_LCOMP01_LRF04.resize(ele_no);
  GIF_LCOMP01_LRF04.resize(ele_no);
  DEC_LCOMP01_LRF04.resize(ele_no);
  DWC_LCOMP01_LRF04.resize(ele_no);
  GRC_LCOMP01_LRF04.resize(ele_no);
  GIC_LCOMP01_LRF04.resize(ele_no);

  NJSX_LCOMP01_LRF07.resize(ele_no);
  ER_LCOMP01_LRF07.resize(  ele_no);
  GAM_LCOMP01_LRF07.resize( ele_no);

  ER_LCOMP02_LRF01.resize( ele_no);
  AJ_LCOMP02_LRF01.resize( ele_no);
  GT_LCOMP02_LRF01.resize( ele_no);
  GN_LCOMP02_LRF01.resize( ele_no);
  GG_LCOMP02_LRF01.resize( ele_no);
  GF_LCOMP02_LRF01.resize( ele_no);
  DER_LCOMP02_LRF01.resize(ele_no);
  DGN_LCOMP02_LRF01.resize(ele_no);
  DGG_LCOMP02_LRF01.resize(ele_no);
  DGF_LCOMP02_LRF01.resize(ele_no);

  ER_LCOMP02_LRF03.resize(  ele_no);
  AJ_LCOMP02_LRF03.resize(  ele_no);
  GN_LCOMP02_LRF03.resize(  ele_no);
  GG_LCOMP02_LRF03.resize(  ele_no);
  GFA_LCOMP02_LRF03.resize( ele_no);
  GFB_LCOMP02_LRF03.resize( ele_no);
  DER_LCOMP02_LRF03.resize( ele_no);
  DGN_LCOMP02_LRF03.resize( ele_no);
  DGG_LCOMP02_LRF03.resize( ele_no);
  DGFA_LCOMP02_LRF03.resize(ele_no);
  DGFB_LCOMP02_LRF03.resize(ele_no);

  NJSX_LCOMP02_LRF07.resize(ele_no);
  MA_LCOMP02_LRF07.resize( ele_no);
  MB_LCOMP02_LRF07.resize( ele_no);
  ZA_LCOMP02_LRF07.resize( ele_no);
  ZB_LCOMP02_LRF07.resize( ele_no);
  IA_LCOMP02_LRF07.resize( ele_no);
  IB_LCOMP02_LRF07.resize( ele_no);
  Q_LCOMP02_LRF07.resize(  ele_no);
  PNT_LCOMP02_LRF07.resize(ele_no);
  SHF_LCOMP02_LRF07.resize(ele_no);
  MT_LCOMP02_LRF07.resize( ele_no);
  PA_LCOMP02_LRF07.resize( ele_no);
  PB_LCOMP02_LRF07.resize( ele_no);

  AJ_LCOMP02_LRF07.resize( ele_no);
  PJ_LCOMP02_LRF07.resize( ele_no);
  PPI_LCOMP02_LRF07.resize(ele_no);
  L_LCOMP02_LRF07.resize(  ele_no);
  SCH_LCOMP02_LRF07.resize(ele_no);
  BND_LCOMP02_LRF07.resize(ele_no);
  APE_LCOMP02_LRF07.resize(ele_no);
  APT_LCOMP02_LRF07.resize(ele_no);

  ER_LCOMP02_LRF07.resize(  ele_no);
  DER_LCOMP02_LRF07.resize( ele_no);
  GAM_LCOMP02_LRF07.resize( ele_no);
  DGAM_LCOMP02_LRF07.resize(ele_no);

  IDP_LRU01.resize(ele_no);
  LB_LRU01.resize( ele_no);
  E_K_LRU01.resize(ele_no);
  F_K_LRU01.resize(ele_no);

  D_LRU02.resize(  ele_no);
  AJ_LRU02.resize( ele_no);
  GNO_LRU02.resize(ele_no);
  GG_LRU02.resize( ele_no);
  GF_LRU02.resize( ele_no);
  GX_LRU02.resize( ele_no);
  RV_LRU02.resize( ele_no);
  MPAR_LRU02.resize(ele_no);

  NI.resize( ele_no);
  LB.resize( ele_no);
  LT.resize( ele_no);
  E_K.resize(ele_no);
  E_T.resize(ele_no);
  F_K.resize(ele_no);
  F_T.resize(ele_no);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF32MT151Parser::resize_matrix_vec_second(int i, int ele_no)
{
  EL[i].resize(  ele_no);
  EH[i].resize(  ele_no);
  LRU[i].resize( ele_no);
  LRF[i].resize( ele_no);
  NRO[i].resize( ele_no);
  NAPS[i].resize(ele_no);

  SPI[i].resize(  ele_no);
  AP[i].resize(   ele_no);
  LAD[i].resize(  ele_no);
  LCOMP[i].resize(ele_no);
  NLS[i].resize(  ele_no);
  ISR[i].resize(  ele_no);

  DAP[i].resize(ele_no);
  for(int j=0; j<ele_no; j++)
  {
    DAP[i][j] = 0.0;
  }
  DAP_TAB[i].resize(ele_no);
  DAP_LRF07[i].resize(ele_no);

  AWRI[i].resize(ele_no);
  QX[i].resize(  ele_no);
  APL[i].resize( ele_no);
  NSRS[i].resize(ele_no);
  NLRS[i].resize(ele_no);
  LRX[i].resize( ele_no);

  V[i].resize(ele_no);

  NDIGIT[i].resize(ele_no);
  NNN[i].resize(   ele_no);
  NM[i].resize(    ele_no);
  II[i].resize( ele_no);
  JJ[i].resize( ele_no);
  KIJ[i].resize(ele_no);

  AWRI_NLS[i].resize(ele_no);
  L[i].resize(ele_no);

  ER_LCOMP00[i].resize(  ele_no);
  AJ_LCOMP00[i].resize(  ele_no);
  GT_LCOMP00[i].resize(  ele_no);
  GN_LCOMP00[i].resize(  ele_no);
  GG_LCOMP00[i].resize(  ele_no);
  GF_LCOMP00[i].resize(  ele_no);
  DE_LCOMP00[i].resize(  ele_no);
  DN_LCOMP00[i].resize(  ele_no);
  DNDG_LCOMP00[i].resize(ele_no);
  DG_LCOMP00[i].resize(  ele_no);
  DNDF_LCOMP00[i].resize(ele_no);
  DGDF_LCOMP00[i].resize(ele_no);
  DF_LCOMP00[i].resize(  ele_no);
  DJDN_LCOMP00[i].resize(ele_no);
  DJDG_LCOMP00[i].resize(ele_no);
  DJDF_LCOMP00[i].resize(ele_no);
  DJ_LCOMP00[i].resize(  ele_no);

  MPAR_LCOMP01_LRF01[i].resize(ele_no);

  ER_LCOMP01_LRF01[i].resize(ele_no);
  AJ_LCOMP01_LRF01[i].resize(ele_no);
  GT_LCOMP01_LRF01[i].resize(ele_no);
  GN_LCOMP01_LRF01[i].resize(ele_no);
  GG_LCOMP01_LRF01[i].resize(ele_no);
  GF_LCOMP01_LRF01[i].resize(ele_no);

  ER_LCOMP01_LRF03[i].resize( ele_no);
  AJ_LCOMP01_LRF03[i].resize( ele_no);
  GN_LCOMP01_LRF03[i].resize( ele_no);
  GG_LCOMP01_LRF03[i].resize( ele_no);
  GFA_LCOMP01_LRF03[i].resize(ele_no);
  GFB_LCOMP01_LRF03[i].resize(ele_no);

  DET_LCOMP01_LRF04[i].resize(ele_no);
  DWT_LCOMP01_LRF04[i].resize(ele_no);
  GRT_LCOMP01_LRF04[i].resize(ele_no);
  GIT_LCOMP01_LRF04[i].resize(ele_no);
  DEF_LCOMP01_LRF04[i].resize(ele_no);
  DWF_LCOMP01_LRF04[i].resize(ele_no);
  GRF_LCOMP01_LRF04[i].resize(ele_no);
  GIF_LCOMP01_LRF04[i].resize(ele_no);
  DEC_LCOMP01_LRF04[i].resize(ele_no);
  DWC_LCOMP01_LRF04[i].resize(ele_no);
  GRC_LCOMP01_LRF04[i].resize(ele_no);
  GIC_LCOMP01_LRF04[i].resize(ele_no);

  NJSX_LCOMP01_LRF07[i].resize(ele_no);
  ER_LCOMP01_LRF07[i].resize(  ele_no);
  GAM_LCOMP01_LRF07[i].resize( ele_no);

  ER_LCOMP02_LRF01[i].resize( ele_no);
  AJ_LCOMP02_LRF01[i].resize( ele_no);
  GT_LCOMP02_LRF01[i].resize( ele_no);
  GN_LCOMP02_LRF01[i].resize( ele_no);
  GG_LCOMP02_LRF01[i].resize( ele_no);
  GF_LCOMP02_LRF01[i].resize( ele_no);
  DER_LCOMP02_LRF01[i].resize(ele_no);
  DGN_LCOMP02_LRF01[i].resize(ele_no);
  DGG_LCOMP02_LRF01[i].resize(ele_no);
  DGF_LCOMP02_LRF01[i].resize(ele_no);

  ER_LCOMP02_LRF03[i].resize(  ele_no);
  AJ_LCOMP02_LRF03[i].resize(  ele_no);
  GN_LCOMP02_LRF03[i].resize(  ele_no);
  GG_LCOMP02_LRF03[i].resize(  ele_no);
  GFA_LCOMP02_LRF03[i].resize( ele_no);
  GFB_LCOMP02_LRF03[i].resize( ele_no);
  DER_LCOMP02_LRF03[i].resize( ele_no);
  DGN_LCOMP02_LRF03[i].resize( ele_no);
  DGG_LCOMP02_LRF03[i].resize( ele_no);
  DGFA_LCOMP02_LRF03[i].resize(ele_no);
  DGFB_LCOMP02_LRF03[i].resize(ele_no);

  NJSX_LCOMP02_LRF07[i].resize(ele_no);
  MA_LCOMP02_LRF07[i].resize( ele_no);
  MB_LCOMP02_LRF07[i].resize( ele_no);
  ZA_LCOMP02_LRF07[i].resize( ele_no);
  ZB_LCOMP02_LRF07[i].resize( ele_no);
  IA_LCOMP02_LRF07[i].resize( ele_no);
  IB_LCOMP02_LRF07[i].resize( ele_no);
  Q_LCOMP02_LRF07[i].resize(  ele_no);
  PNT_LCOMP02_LRF07[i].resize(ele_no);
  SHF_LCOMP02_LRF07[i].resize(ele_no);
  MT_LCOMP02_LRF07[i].resize( ele_no);
  PA_LCOMP02_LRF07[i].resize( ele_no);
  PB_LCOMP02_LRF07[i].resize( ele_no);

  AJ_LCOMP02_LRF07[i].resize( ele_no);
  PJ_LCOMP02_LRF07[i].resize( ele_no);
  PPI_LCOMP02_LRF07[i].resize(ele_no);
  L_LCOMP02_LRF07[i].resize(  ele_no);
  SCH_LCOMP02_LRF07[i].resize(ele_no);
  BND_LCOMP02_LRF07[i].resize(ele_no);
  APE_LCOMP02_LRF07[i].resize(ele_no);
  APT_LCOMP02_LRF07[i].resize(ele_no);

  ER_LCOMP02_LRF07[i].resize(  ele_no);
  DER_LCOMP02_LRF07[i].resize( ele_no);
  GAM_LCOMP02_LRF07[i].resize( ele_no);
  DGAM_LCOMP02_LRF07[i].resize(ele_no);

  IDP_LRU01[i].resize(ele_no);
  LB_LRU01[i].resize( ele_no);
  E_K_LRU01[i].resize(ele_no);
  F_K_LRU01[i].resize(ele_no);

  D_LRU02[i].resize(  ele_no);
  AJ_LRU02[i].resize( ele_no);
  GNO_LRU02[i].resize(ele_no);
  GG_LRU02[i].resize( ele_no);
  GF_LRU02[i].resize( ele_no);
  GX_LRU02[i].resize( ele_no);
  RV_LRU02[i].resize( ele_no);
  MPAR_LRU02[i].resize(ele_no);

  NI[i].resize( ele_no);
  LB[i].resize( ele_no);
  LT[i].resize( ele_no);
  E_K[i].resize(ele_no);
  E_T[i].resize(ele_no);
  F_K[i].resize(ele_no);
  F_T[i].resize(ele_no);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF32MT151Parser::resize_matrix_vec_nsrs(int i, int j)
{
  int ele_no = NSRS[i][j];

  if( LRF[i][j] == 1 || LRF[i][j] == 2 )
  {
    MPAR_LCOMP01_LRF01[i][j].resize(ele_no);

    ER_LCOMP01_LRF01[i][j].resize(ele_no);
    AJ_LCOMP01_LRF01[i][j].resize(ele_no);
    GT_LCOMP01_LRF01[i][j].resize(ele_no);
    GN_LCOMP01_LRF01[i][j].resize(ele_no);
    GG_LCOMP01_LRF01[i][j].resize(ele_no);
    GF_LCOMP01_LRF01[i][j].resize(ele_no);

    V[i][j].resize(ele_no);
  }
  else if( LRF[i][j] == 3 )
  {
    MPAR_LCOMP01_LRF01[i][j].resize(ele_no);

    ER_LCOMP01_LRF03[i][j].resize( ele_no);
    AJ_LCOMP01_LRF03[i][j].resize( ele_no);
    GN_LCOMP01_LRF03[i][j].resize( ele_no);
    GG_LCOMP01_LRF03[i][j].resize( ele_no);
    GFA_LCOMP01_LRF03[i][j].resize(ele_no);
    GFB_LCOMP01_LRF03[i][j].resize(ele_no);

    V[i][j].resize(ele_no);
  }
  else if( LRF[i][j] == 4 )
  {
    MPAR_LCOMP01_LRF01[i][j].resize(ele_no);

    DET_LCOMP01_LRF04[i][j].resize(ele_no);
    DWT_LCOMP01_LRF04[i][j].resize(ele_no);
    GRT_LCOMP01_LRF04[i][j].resize(ele_no);
    GIT_LCOMP01_LRF04[i][j].resize(ele_no);
    DEF_LCOMP01_LRF04[i][j].resize(ele_no);
    DWF_LCOMP01_LRF04[i][j].resize(ele_no);
    GRF_LCOMP01_LRF04[i][j].resize(ele_no);
    GIF_LCOMP01_LRF04[i][j].resize(ele_no);
    DEC_LCOMP01_LRF04[i][j].resize(ele_no);
    DWC_LCOMP01_LRF04[i][j].resize(ele_no);
    GRC_LCOMP01_LRF04[i][j].resize(ele_no);
    GIC_LCOMP01_LRF04[i][j].resize(ele_no);

    V[i][j].resize(ele_no);
  }
  else if( LRF[i][j] == 7 )
  {
    NJSX_LCOMP01_LRF07[i][j].resize(ele_no);
    ER_LCOMP01_LRF07[i][j].resize(  ele_no);
    GAM_LCOMP01_LRF07[i][j].resize( ele_no);

    V[i][j].resize(ele_no);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF32MT151Parser::resize_matrix_vec_nro01(int i, int j, int ele_no)
{
  LB[i][j].resize( ele_no);
  LT[i][j].resize( ele_no);
  E_K[i][j].resize(ele_no);
  E_T[i][j].resize(ele_no);
  F_K[i][j].resize(ele_no);
  F_T[i][j].resize(ele_no);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF32MT151Parser::clear()
{
  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);

  mat_no = unassigned_mat_no;
  ZAR    = 0.0;
  AWR    = 0.0;
  NIS    = 0;
  ZAI.clear();
  ABN.clear();
  LFW.clear();
  NER.clear();

  clear_vector_array();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF32MT151Parser::clear_vector_array()
{
  VectorClearer clr_vec;
  clr_vec.clear_vec_array2_real(EL);
  clr_vec.clear_vec_array2_real(EH);
  clr_vec.clear_vec_array2_int( LRU);
  clr_vec.clear_vec_array2_int( LRF);
  clr_vec.clear_vec_array2_int( NRO);
  clr_vec.clear_vec_array2_int( NAPS);

  clr_vec.clear_vec_array2_real(SPI);
  clr_vec.clear_vec_array2_real(AP);
  clr_vec.clear_vec_array2_int( LAD);
  clr_vec.clear_vec_array2_int( LCOMP);
  clr_vec.clear_vec_array2_int( NLS);
  clr_vec.clear_vec_array2_int( ISR);

  clr_vec.clear_vec_array2_real(DAP);

  clr_vec.clear_vec_array3_real(DAP_TAB);
  clr_vec.clear_vec_array4_real(DAP_LRF07);

  clr_vec.clear_vec_array2_real(AWRI);
  clr_vec.clear_vec_array2_real(QX);
  clr_vec.clear_vec_array2_real(APL);
  clr_vec.clear_vec_array2_int( NSRS);
  clr_vec.clear_vec_array2_int( NLRS);
  clr_vec.clear_vec_array2_int( LRX);

  clr_vec.clear_vec_array5_real(V);

  clr_vec.clear_vec_array2_int(NDIGIT);
  clr_vec.clear_vec_array2_int(NNN);
  clr_vec.clear_vec_array2_int(NM);
  clr_vec.clear_vec_array3_int(II);
  clr_vec.clear_vec_array3_int(JJ);
  clr_vec.clear_vec_array4_int(KIJ);

  clr_vec.clear_vec_array3_real(AWRI_NLS);
  clr_vec.clear_vec_array3_int( L);

  clr_vec.clear_vec_array4_real(ER_LCOMP00);
  clr_vec.clear_vec_array4_real(AJ_LCOMP00);
  clr_vec.clear_vec_array4_real(GT_LCOMP00);
  clr_vec.clear_vec_array4_real(GN_LCOMP00);
  clr_vec.clear_vec_array4_real(GG_LCOMP00);
  clr_vec.clear_vec_array4_real(GF_LCOMP00);
  clr_vec.clear_vec_array4_real(DE_LCOMP00);
  clr_vec.clear_vec_array4_real(DN_LCOMP00);
  clr_vec.clear_vec_array4_real(DNDG_LCOMP00);
  clr_vec.clear_vec_array4_real(DG_LCOMP00);
  clr_vec.clear_vec_array4_real(DNDF_LCOMP00);
  clr_vec.clear_vec_array4_real(DGDF_LCOMP00);
  clr_vec.clear_vec_array4_real(DF_LCOMP00);
  clr_vec.clear_vec_array4_real(DJDN_LCOMP00);
  clr_vec.clear_vec_array4_real(DJDG_LCOMP00);
  clr_vec.clear_vec_array4_real(DJDF_LCOMP00);
  clr_vec.clear_vec_array4_real(DJ_LCOMP00);

  clr_vec.clear_vec_array3_int(MPAR_LCOMP01_LRF01);
  clr_vec.clear_vec_array4_real(ER_LCOMP01_LRF01);
  clr_vec.clear_vec_array4_real(AJ_LCOMP01_LRF01);
  clr_vec.clear_vec_array4_real(GT_LCOMP01_LRF01);
  clr_vec.clear_vec_array4_real(GN_LCOMP01_LRF01);
  clr_vec.clear_vec_array4_real(GG_LCOMP01_LRF01);
  clr_vec.clear_vec_array4_real(GF_LCOMP01_LRF01);

  clr_vec.clear_vec_array4_real(ER_LCOMP01_LRF03);
  clr_vec.clear_vec_array4_real(AJ_LCOMP01_LRF03);
  clr_vec.clear_vec_array4_real(GN_LCOMP01_LRF03);
  clr_vec.clear_vec_array4_real(GG_LCOMP01_LRF03);
  clr_vec.clear_vec_array4_real(GFA_LCOMP01_LRF03);
  clr_vec.clear_vec_array4_real(GFB_LCOMP01_LRF03);

  clr_vec.clear_vec_array4_real(DET_LCOMP01_LRF04);
  clr_vec.clear_vec_array4_real(DWT_LCOMP01_LRF04);
  clr_vec.clear_vec_array4_real(GRT_LCOMP01_LRF04);
  clr_vec.clear_vec_array4_real(GIT_LCOMP01_LRF04);
  clr_vec.clear_vec_array4_real(DEF_LCOMP01_LRF04);
  clr_vec.clear_vec_array4_real(DWF_LCOMP01_LRF04);
  clr_vec.clear_vec_array4_real(GRF_LCOMP01_LRF04);
  clr_vec.clear_vec_array4_real(GIF_LCOMP01_LRF04);
  clr_vec.clear_vec_array4_real(DEC_LCOMP01_LRF04);
  clr_vec.clear_vec_array4_real(DWC_LCOMP01_LRF04);
  clr_vec.clear_vec_array4_real(GRC_LCOMP01_LRF04);
  clr_vec.clear_vec_array4_real(GIC_LCOMP01_LRF04);

  clr_vec.clear_vec_array3_int(NJSX_LCOMP01_LRF07);
  clr_vec.clear_vec_array5_real(ER_LCOMP01_LRF07);
  clr_vec.clear_vec_array6_real(GAM_LCOMP01_LRF07);

  clr_vec.clear_vec_array3_real(ER_LCOMP02_LRF01);
  clr_vec.clear_vec_array3_real(AJ_LCOMP02_LRF01);
  clr_vec.clear_vec_array3_real(GT_LCOMP02_LRF01);
  clr_vec.clear_vec_array3_real(GN_LCOMP02_LRF01);
  clr_vec.clear_vec_array3_real(GG_LCOMP02_LRF01);
  clr_vec.clear_vec_array3_real(GF_LCOMP02_LRF01);
  clr_vec.clear_vec_array3_real(DER_LCOMP02_LRF01);
  clr_vec.clear_vec_array3_real(DGN_LCOMP02_LRF01);
  clr_vec.clear_vec_array3_real(DGG_LCOMP02_LRF01);
  clr_vec.clear_vec_array3_real(DGF_LCOMP02_LRF01);

  clr_vec.clear_vec_array3_real(ER_LCOMP02_LRF03);
  clr_vec.clear_vec_array3_real(AJ_LCOMP02_LRF03);
  clr_vec.clear_vec_array3_real(GN_LCOMP02_LRF03);
  clr_vec.clear_vec_array3_real(GG_LCOMP02_LRF03);
  clr_vec.clear_vec_array3_real(GFA_LCOMP02_LRF03);
  clr_vec.clear_vec_array3_real(GFB_LCOMP02_LRF03);
  clr_vec.clear_vec_array3_real(DER_LCOMP02_LRF03);
  clr_vec.clear_vec_array3_real(DGN_LCOMP02_LRF03);
  clr_vec.clear_vec_array3_real(DGG_LCOMP02_LRF03);
  clr_vec.clear_vec_array3_real(DGFA_LCOMP02_LRF03);
  clr_vec.clear_vec_array3_real(DGFB_LCOMP02_LRF03);

  clr_vec.clear_vec_array2_int( NJSX_LCOMP02_LRF07);
  clr_vec.clear_vec_array3_real(MA_LCOMP02_LRF07);
  clr_vec.clear_vec_array3_real(MB_LCOMP02_LRF07);
  clr_vec.clear_vec_array3_real(ZA_LCOMP02_LRF07);
  clr_vec.clear_vec_array3_real(ZB_LCOMP02_LRF07);
  clr_vec.clear_vec_array3_real(IA_LCOMP02_LRF07);
  clr_vec.clear_vec_array3_real(IB_LCOMP02_LRF07);
  clr_vec.clear_vec_array3_real(Q_LCOMP02_LRF07);
  clr_vec.clear_vec_array3_real(PNT_LCOMP02_LRF07);
  clr_vec.clear_vec_array3_real(SHF_LCOMP02_LRF07);
  clr_vec.clear_vec_array3_real(MT_LCOMP02_LRF07);
  clr_vec.clear_vec_array3_real(PA_LCOMP02_LRF07);
  clr_vec.clear_vec_array3_real(PB_LCOMP02_LRF07);

  clr_vec.clear_vec_array3_real(AJ_LCOMP02_LRF07);
  clr_vec.clear_vec_array3_real(PJ_LCOMP02_LRF07);
  clr_vec.clear_vec_array4_real(PPI_LCOMP02_LRF07);
  clr_vec.clear_vec_array4_real(L_LCOMP02_LRF07);
  clr_vec.clear_vec_array4_real(SCH_LCOMP02_LRF07);
  clr_vec.clear_vec_array4_real(BND_LCOMP02_LRF07);
  clr_vec.clear_vec_array4_real(APE_LCOMP02_LRF07);
  clr_vec.clear_vec_array4_real(APT_LCOMP02_LRF07);

  clr_vec.clear_vec_array4_real(ER_LCOMP02_LRF07);
  clr_vec.clear_vec_array4_real(DER_LCOMP02_LRF07);
  clr_vec.clear_vec_array5_real(GAM_LCOMP02_LRF07);
  clr_vec.clear_vec_array5_real(DGAM_LCOMP02_LRF07);

  clr_vec.clear_vec_array3_int( IDP_LRU01);
  clr_vec.clear_vec_array3_int( LB_LRU01);
  clr_vec.clear_vec_array4_real(E_K_LRU01);
  clr_vec.clear_vec_array5_real(F_K_LRU01);

  clr_vec.clear_vec_array4_real(D_LRU02);
  clr_vec.clear_vec_array4_real(AJ_LRU02);
  clr_vec.clear_vec_array4_real(GNO_LRU02);
  clr_vec.clear_vec_array4_real(GG_LRU02);
  clr_vec.clear_vec_array4_real(GF_LRU02);
  clr_vec.clear_vec_array4_real(GX_LRU02);
  clr_vec.clear_vec_array4_real(RV_LRU02);
  clr_vec.clear_vec_array2_int( MPAR_LRU02);

  clr_vec.clear_vec_array2_int( NI);
  clr_vec.clear_vec_array3_int( LB);
  clr_vec.clear_vec_array3_int( LT);
  clr_vec.clear_vec_array4_real(E_K);
  clr_vec.clear_vec_array4_real(E_T);
  clr_vec.clear_vec_array5_real(F_K);
  clr_vec.clear_vec_array5_real(F_T);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF32MT151Parser::set_text(vector<string> text_data)
{
  clear();

  text = text_data;
  store_data();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> MF32MT151Parser::get_text()
{
  return text;
}

Integer MF32MT151Parser::get_mat_no()
{
  return mat_no;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Real                              MF32MT151Parser::get_ZAR()
{
  return ZAR;
}

Real                              MF32MT151Parser::get_AWR()
{
  return AWR;
}

Integer                           MF32MT151Parser::get_NIS()
{
  return NIS;
}

vector<Real>                      MF32MT151Parser::get_ZAI()
{
  return ZAI;
}

vector<Real>                      MF32MT151Parser::get_ABN()
{
  return ABN;
}

vector<Integer>                   MF32MT151Parser::get_LFW()
{
  return LFW;
}

vector<Integer>                   MF32MT151Parser::get_NER()
{
  return NER;
}

vector<vector<Real> >             MF32MT151Parser::get_EL()
{
  return EL;
}

vector<vector<Real> >             MF32MT151Parser::get_EH()
{
  return EH;
}

vector<vector<Integer> >          MF32MT151Parser::get_LRU()
{
  return LRU;
}

vector<vector<Integer> >          MF32MT151Parser::get_LRF()
{
  return LRF;
}

vector<vector<Integer> >          MF32MT151Parser::get_NRO()
{
  return NRO;
}

vector<vector<Integer> >          MF32MT151Parser::get_NAPS()
{
  return NAPS;
}


//Common
vector<vector<Real> >             MF32MT151Parser::get_SPI()
{
  return SPI;
}

vector<vector<Real> >             MF32MT151Parser::get_AP()
{
  return AP;
}

vector<vector<Integer> >          MF32MT151Parser::get_LAD()
{
  return LAD;
}

vector<vector<Integer> >          MF32MT151Parser::get_IFG()
{
  return LAD;
}

vector<vector<Integer> >          MF32MT151Parser::get_LCOMP()
{
  return LCOMP;
}

vector<vector<Integer> >          MF32MT151Parser::get_NLS()
{
  return NLS;
}

vector<vector<Integer> >          MF32MT151Parser::get_NJS()
{
  return NLS;
}

vector<vector<Integer> >          MF32MT151Parser::get_ISR()
{
  return ISR;
}

vector<vector<Real> >             MF32MT151Parser::get_AWRI()
{
  return AWRI;
}


//LCOMP=0
vector<vector<vector<Real> > >    MF32MT151Parser::get_AWRI_LCOMP00()
{
  return AWRI_NLS;
}

vector<vector<vector<Integer> > > MF32MT151Parser::get_L_LCOMP00()
{
  return L;
}

vector<vector<Real> >             MF32MT151Parser::get_DAP_LCOMP00()
{
  return DAP;
}

vector<vector<vector<vector<Real> > > > MF32MT151Parser::get_ER_LCOMP00()
{
  return ER_LCOMP00;
}

vector<vector<vector<vector<Real> > > > MF32MT151Parser::get_AJ_LCOMP00()
{
  return AJ_LCOMP00;
}

vector<vector<vector<vector<Real> > > > MF32MT151Parser::get_GT_LCOMP00()
{
  return GT_LCOMP00;
}

vector<vector<vector<vector<Real> > > > MF32MT151Parser::get_GN_LCOMP00()
{
  return GN_LCOMP00;
}

vector<vector<vector<vector<Real> > > > MF32MT151Parser::get_GG_LCOMP00()
{
  return GG_LCOMP00;
}

vector<vector<vector<vector<Real> > > > MF32MT151Parser::get_GF_LCOMP00()
{
  return GF_LCOMP00;
}

vector<vector<vector<vector<Real> > > > MF32MT151Parser::get_DE_LCOMP00()
{
  return DE_LCOMP00;
}

vector<vector<vector<vector<Real> > > > MF32MT151Parser::get_DN_LCOMP00()
{
  return DN_LCOMP00;
}

vector<vector<vector<vector<Real> > > > MF32MT151Parser::get_DNDG_LCOMP00()
{
  return DNDG_LCOMP00;
}

vector<vector<vector<vector<Real> > > > MF32MT151Parser::get_DG_LCOMP00()
{
  return DG_LCOMP00;
}

vector<vector<vector<vector<Real> > > > MF32MT151Parser::get_DNDF_LCOMP00()
{
  return DNDF_LCOMP00;
}

vector<vector<vector<vector<Real> > > > MF32MT151Parser::get_DGDF_LCOMP00()
{
  return DGDF_LCOMP00;
}

vector<vector<vector<vector<Real> > > > MF32MT151Parser::get_DF_LCOMP00()
{
  return DF_LCOMP00;
}

vector<vector<vector<vector<Real> > > > MF32MT151Parser::get_DJDN_LCOMP00()
{
  return DJDN_LCOMP00;
}

vector<vector<vector<vector<Real> > > > MF32MT151Parser::get_DJDG_LCOMP00()
{
  return DJDG_LCOMP00;
}

vector<vector<vector<vector<Real> > > > MF32MT151Parser::get_DJDF_LCOMP00()
{
  return DJDF_LCOMP00;
}

vector<vector<vector<vector<Real> > > > MF32MT151Parser::get_DJ_LCOMP00()
{
  return DJ_LCOMP00;
}


//LCOMP=1, LRF=1 or 2
vector<vector<Real> >             MF32MT151Parser::get_AWRI_LCOMP01_LRF01()
{
  return AWRI;
}

vector<vector<Integer> >          MF32MT151Parser::get_NSRS_LCOMP01_LRF01()
{
  return NSRS;
}

vector<vector<Integer> >          MF32MT151Parser::get_NLRS_LCOMP01_LRF01()
{
  return NLRS;
}

vector<vector<Real> >             MF32MT151Parser::get_DAP_LCOMP01_LRF01()
{
  return DAP;
}

vector<vector<vector<Integer> > > MF32MT151Parser::get_MPAR_LCOMP01_LRF01()
{
  return MPAR_LCOMP01_LRF01;
}

vector<vector<vector<vector<Real> > > > MF32MT151Parser::get_ER_LCOMP01_LRF01()
{
  return ER_LCOMP01_LRF01;
}

vector<vector<vector<vector<Real> > > > MF32MT151Parser::get_AJ_LCOMP01_LRF01()
{
  return AJ_LCOMP01_LRF01;
}

vector<vector<vector<vector<Real> > > > MF32MT151Parser::get_GT_LCOMP01_LRF01()
{
  return GT_LCOMP01_LRF01;
}

vector<vector<vector<vector<Real> > > > MF32MT151Parser::get_GN_LCOMP01_LRF01()
{
  return GN_LCOMP01_LRF01;
}

vector<vector<vector<vector<Real> > > > MF32MT151Parser::get_GG_LCOMP01_LRF01()
{
  return GG_LCOMP01_LRF01;
}

vector<vector<vector<vector<Real> > > > MF32MT151Parser::get_GF_LCOMP01_LRF01()
{
  return GF_LCOMP01_LRF01;
}

vector<vector<vector<vector<vector<Real> > > > > MF32MT151Parser::get_V_LCOMP01_LRF01()
{
  return V;
}


//LCOMP=1, LRF=3
vector<vector<vector<Real> > >    MF32MT151Parser::get_DAP_LCOMP01_LRF03()
{
  return DAP_TAB;
}

vector<vector<Real> >             MF32MT151Parser::get_AWRI_LCOMP01_LRF03()
{
  return AWRI;
}

vector<vector<Integer> >          MF32MT151Parser::get_NSRS_LCOMP01_LRF03()
{
  return NSRS;
}

vector<vector<Integer> >          MF32MT151Parser::get_NLRS_LCOMP01_LRF03()
{
  return NLRS;
}

vector<vector<vector<Integer> > > MF32MT151Parser::get_MPAR_LCOMP01_LRF03()
{
  return MPAR_LCOMP01_LRF01;
}

vector<vector<vector<vector<Real> > > > MF32MT151Parser::get_ER_LCOMP01_LRF03()
{
  return ER_LCOMP01_LRF03;
}

vector<vector<vector<vector<Real> > > > MF32MT151Parser::get_AJ_LCOMP01_LRF03()
{
  return AJ_LCOMP01_LRF03;
}

vector<vector<vector<vector<Real> > > > MF32MT151Parser::get_GN_LCOMP01_LRF03()
{
  return GN_LCOMP01_LRF03;
}

vector<vector<vector<vector<Real> > > > MF32MT151Parser::get_GG_LCOMP01_LRF03()
{
  return GG_LCOMP01_LRF03;
}

vector<vector<vector<vector<Real> > > > MF32MT151Parser::get_GFA_LCOMP01_LRF03()
{
  return GFA_LCOMP01_LRF03;
}

vector<vector<vector<vector<Real> > > > MF32MT151Parser::get_GFB_LCOMP01_LRF03()
{
  return GFB_LCOMP01_LRF03;
}

vector<vector<vector<vector<vector<Real> > > > > MF32MT151Parser::get_V_LCOMP01_LRF03()
{
  return V;
}


//LCOMP=1, LRF=4
vector<vector<Real> >             MF32MT151Parser::get_AWRI_LCOMP01_LRF04()
{
  return AWRI;
}

vector<vector<Integer> >          MF32MT151Parser::get_NSRS_LCOMP01_LRF04()
{
  return NSRS;
}

vector<vector<Integer> >          MF32MT151Parser::get_NLRS_LCOMP01_LRF04()
{
  return NLRS;
}

vector<vector<Real> >             MF32MT151Parser::get_DAP_LCOMP01_LRF04()
{
  return DAP;
}

vector<vector<vector<Integer> > > MF32MT151Parser::get_MPAR_LCOMP01_LRF04()
{
  return MPAR_LCOMP01_LRF01;
}

vector<vector<vector<vector<Real> > > > MF32MT151Parser::get_DET_LCOMP01_LRF04()
{
  return DET_LCOMP01_LRF04;
}

vector<vector<vector<vector<Real> > > > MF32MT151Parser::get_DWT_LCOMP01_LRF04()
{
  return DWT_LCOMP01_LRF04;
}

vector<vector<vector<vector<Real> > > > MF32MT151Parser::get_GRT_LCOMP01_LRF04()
{
  return GRT_LCOMP01_LRF04;
}

vector<vector<vector<vector<Real> > > > MF32MT151Parser::get_GIT_LCOMP01_LRF04()
{
  return GIT_LCOMP01_LRF04;
}

vector<vector<vector<vector<Real> > > > MF32MT151Parser::get_DEF_LCOMP01_LRF04()
{
  return DEF_LCOMP01_LRF04;
}

vector<vector<vector<vector<Real> > > > MF32MT151Parser::get_DWF_LCOMP01_LRF04()
{
  return DWF_LCOMP01_LRF04;
}

vector<vector<vector<vector<Real> > > > MF32MT151Parser::get_GRF_LCOMP01_LRF04()
{
  return GRF_LCOMP01_LRF04;
}

vector<vector<vector<vector<Real> > > > MF32MT151Parser::get_GIF_LCOMP01_LRF04()
{
  return GIF_LCOMP01_LRF04;
}

vector<vector<vector<vector<Real> > > > MF32MT151Parser::get_DEC_LCOMP01_LRF04()
{
  return DEC_LCOMP01_LRF04;
}

vector<vector<vector<vector<Real> > > > MF32MT151Parser::get_DWC_LCOMP01_LRF04()
{
  return DWC_LCOMP01_LRF04;
}

vector<vector<vector<vector<Real> > > > MF32MT151Parser::get_GRC_LCOMP01_LRF04()
{
  return GRC_LCOMP01_LRF04;
}

vector<vector<vector<vector<Real> > > > MF32MT151Parser::get_GIC_LCOMP01_LRF04()
{
  return GIC_LCOMP01_LRF04;
}

vector<vector<vector<vector<vector<Real> > > > > MF32MT151Parser::get_V_LCOMP01_LRF04()
{
  return V;
}


//LCOMP=1, LRF=7
vector<vector<vector<vector<Real> > > >  MF32MT151Parser::get_DAP_LCOMP01_LRF07()
{
  return DAP_LRF07;
}

vector<vector<Real> >             MF32MT151Parser::get_AWRI_LCOMP01_LRF07()
{
  return AWRI;
}

vector<vector<Integer> >          MF32MT151Parser::get_NSRS_LCOMP01_LRF07()
{
  return NSRS;
}

vector<vector<Integer> >          MF32MT151Parser::get_NLRS_LCOMP01_LRF07()
{
  return NLRS;
}

vector<vector<vector<Integer> > > MF32MT151Parser::get_NJSX_LCOMP01_LRF07()
{
  return NJSX_LCOMP01_LRF07;
}

vector<vector<vector<vector<vector<Real> > > > > MF32MT151Parser::get_ER_LCOMP01_LRF07()
{
  return ER_LCOMP01_LRF07;
}

vector<vector<vector<vector<vector<vector<Real> > > > > > MF32MT151Parser::get_GAM_LCOMP01_LRF07()
{
  return GAM_LCOMP01_LRF07;
}

vector<vector<vector<vector<vector<Real> > > > > MF32MT151Parser::get_V_LCOMP01_LRF07()
{
  return V;
}


//LCOMP=2, LRF=1 or 2
vector<vector<Real> >             MF32MT151Parser::get_DAP_LCOMP02_LRF01()
{
  return DAP;
}

vector<vector<Real> >             MF32MT151Parser::get_AWRI_LCOMP02_LRF01()
{
  return AWRI;
}

vector<vector<Real> >             MF32MT151Parser::get_QX_LCOMP02_LRF01()
{
  return QX;
}

vector<vector<Integer> >          MF32MT151Parser::get_LRX_LCOMP02_LRF01()
{
  return LRX;
}


vector<vector<vector<Real> > >    MF32MT151Parser::get_ER_LCOMP02_LRF01()
{
  return ER_LCOMP02_LRF01;
}

vector<vector<vector<Real> > >    MF32MT151Parser::get_AJ_LCOMP02_LRF01()
{
  return AJ_LCOMP02_LRF01;
}

vector<vector<vector<Real> > >    MF32MT151Parser::get_GT_LCOMP02_LRF01()
{
  return GT_LCOMP02_LRF01;
}

vector<vector<vector<Real> > >    MF32MT151Parser::get_GN_LCOMP02_LRF01()
{
  return GN_LCOMP02_LRF01;
}

vector<vector<vector<Real> > >    MF32MT151Parser::get_GG_LCOMP02_LRF01()
{
  return GG_LCOMP02_LRF01;
}

vector<vector<vector<Real> > >    MF32MT151Parser::get_GF_LCOMP02_LRF01()
{
  return GF_LCOMP02_LRF01;
}

vector<vector<vector<Real> > >    MF32MT151Parser::get_DER_LCOMP02_LRF01()
{
  return DER_LCOMP02_LRF01;
}

vector<vector<vector<Real> > >    MF32MT151Parser::get_DGN_LCOMP02_LRF01()
{
  return DGN_LCOMP02_LRF01;
}

vector<vector<vector<Real> > >    MF32MT151Parser::get_DGG_LCOMP02_LRF01()
{
  return DGG_LCOMP02_LRF01;
}

vector<vector<vector<Real> > >    MF32MT151Parser::get_DGF_LCOMP02_LRF01()
{
  return DGF_LCOMP02_LRF01;
}


vector<vector<Integer> >          MF32MT151Parser::get_NDIGIT_LCOMP02_LRF01()
{
  return NDIGIT;
}

vector<vector<Integer> >          MF32MT151Parser::get_NNN_LCOMP02_LRF01()
{
  return NNN;
}

vector<vector<Integer> >          MF32MT151Parser::get_NM_LCOMP02_LRF01()
{
  return NM;
}

vector<vector<vector<Integer> > > MF32MT151Parser::get_II_LCOMP02_LRF01()
{
  return II;
}

vector<vector<vector<Integer> > > MF32MT151Parser::get_JJ_LCOMP02_LRF01()
{
  return JJ;
}

vector<vector<vector<vector<Integer> > > > MF32MT151Parser::get_KIJ_LCOMP02_LRF01()
{
  return KIJ;
}


//LCOMP=2, LRF=3
vector<vector<vector<Real> > >    MF32MT151Parser::get_DAP_LCOMP02_LRF03()
{
  return DAP_TAB;
}

vector<vector<Real> >             MF32MT151Parser::get_AWRI_LCOMP02_LRF03()
{
  return AWRI;
}

vector<vector<Real> >             MF32MT151Parser::get_APL_LCOMP02_LRF03()
{
  return APL;
}

vector<vector<vector<Real> > >    MF32MT151Parser::get_ER_LCOMP02_LRF03()
{
  return ER_LCOMP02_LRF03;
}

vector<vector<vector<Real> > >    MF32MT151Parser::get_AJ_LCOMP02_LRF03()
{
  return AJ_LCOMP02_LRF03;
}

vector<vector<vector<Real> > >    MF32MT151Parser::get_GN_LCOMP02_LRF03()
{
  return GN_LCOMP02_LRF03;
}

vector<vector<vector<Real> > >    MF32MT151Parser::get_GG_LCOMP02_LRF03()
{
  return GG_LCOMP02_LRF03;
}

vector<vector<vector<Real> > >    MF32MT151Parser::get_GFA_LCOMP02_LRF03()
{
  return GFA_LCOMP02_LRF03;
}

vector<vector<vector<Real> > >    MF32MT151Parser::get_GFB_LCOMP02_LRF03()
{
  return GFB_LCOMP02_LRF03;
}

vector<vector<vector<Real> > >    MF32MT151Parser::get_DER_LCOMP02_LRF03()
{
  return DER_LCOMP02_LRF03;
}

vector<vector<vector<Real> > >    MF32MT151Parser::get_DGN_LCOMP02_LRF03()
{
  return DGN_LCOMP02_LRF03;
}

vector<vector<vector<Real> > >    MF32MT151Parser::get_DGG_LCOMP02_LRF03()
{
  return DGG_LCOMP02_LRF03;
}

vector<vector<vector<Real> > >    MF32MT151Parser::get_DGFA_LCOMP02_LRF03()
{
  return DGFA_LCOMP02_LRF03;
}

vector<vector<vector<Real> > >    MF32MT151Parser::get_DGFB_LCOMP02_LRF03()
{
  return DGFB_LCOMP02_LRF03;
}


vector<vector<Integer> >          MF32MT151Parser::get_NDIGIT_LCOMP02_LRF03()
{
  return NDIGIT;
}

vector<vector<Integer> >          MF32MT151Parser::get_NNN_LCOMP02_LRF03()
{
  return NNN;
}

vector<vector<Integer> >          MF32MT151Parser::get_NM_LCOMP02_LRF03()
{
  return NM;
}

vector<vector<vector<Integer> > > MF32MT151Parser::get_II_LCOMP02_LRF03()
{
  return II;
}

vector<vector<vector<Integer> > > MF32MT151Parser::get_JJ_LCOMP02_LRF03()
{
  return JJ;
}

vector<vector<vector<vector<Integer> > > > MF32MT151Parser::get_KIJ_LCOMP02_LRF03()
{
  return KIJ;
}


//LCOMP=2, LRF=7
vector<vector<vector<vector<Real> > > >  MF32MT151Parser::get_DAP_LCOMP02_LRF07()
{
  return DAP_LRF07;
}


vector<vector<Integer> >          MF32MT151Parser::get_NJSX_LCOMP02_LRF07()
{
  return NJSX_LCOMP02_LRF07;
}

vector<vector<vector<Real> > >    MF32MT151Parser::get_MA_LCOMP02_LRF07()
{
  return MA_LCOMP02_LRF07;
}

vector<vector<vector<Real> > >    MF32MT151Parser::get_MB_LCOMP02_LRF07()
{
  return MB_LCOMP02_LRF07;
}

vector<vector<vector<Real> > >    MF32MT151Parser::get_ZA_LCOMP02_LRF07()
{
  return ZA_LCOMP02_LRF07;
}

vector<vector<vector<Real> > >    MF32MT151Parser::get_ZB_LCOMP02_LRF07()
{
  return ZB_LCOMP02_LRF07;
}

vector<vector<vector<Real> > >    MF32MT151Parser::get_IA_LCOMP02_LRF07()
{
  return IA_LCOMP02_LRF07;
}

vector<vector<vector<Real> > >    MF32MT151Parser::get_IB_LCOMP02_LRF07()
{
  return IB_LCOMP02_LRF07;
}

vector<vector<vector<Real> > >    MF32MT151Parser::get_Q_LCOMP02_LRF07()
{
  return Q_LCOMP02_LRF07;
}

vector<vector<vector<Real> > >    MF32MT151Parser::get_PNT_LCOMP02_LRF07()
{
  return PNT_LCOMP02_LRF07;
}

vector<vector<vector<Real> > >    MF32MT151Parser::get_SHF_LCOMP02_LRF07()
{
  return SHF_LCOMP02_LRF07;
}

vector<vector<vector<Real> > >    MF32MT151Parser::get_MT_LCOMP02_LRF07()
{
  return MT_LCOMP02_LRF07;
}

vector<vector<vector<Real> > >    MF32MT151Parser::get_PA_LCOMP02_LRF07()
{
  return PA_LCOMP02_LRF07;
}

vector<vector<vector<Real> > >    MF32MT151Parser::get_PB_LCOMP02_LRF07()
{
  return PB_LCOMP02_LRF07;
}


vector<vector<vector<Real> > >    MF32MT151Parser::get_AJ_LCOMP02_LRF07()
{
  return AJ_LCOMP02_LRF07;
}

vector<vector<vector<Real> > >    MF32MT151Parser::get_PJ_LCOMP02_LRF07()
{
  return PJ_LCOMP02_LRF07;
}

vector<vector<vector<vector<Real> > > > MF32MT151Parser::get_PPI_LCOMP02_LRF07()
{
  return PPI_LCOMP02_LRF07;
}

vector<vector<vector<vector<Real> > > > MF32MT151Parser::get_L_LCOMP02_LRF07()
{
  return L_LCOMP02_LRF07;
}

vector<vector<vector<vector<Real> > > > MF32MT151Parser::get_SCH_LCOMP02_LRF07()
{
  return SCH_LCOMP02_LRF07;
}

vector<vector<vector<vector<Real> > > > MF32MT151Parser::get_BND_LCOMP02_LRF07()
{
  return BND_LCOMP02_LRF07;
}

vector<vector<vector<vector<Real> > > > MF32MT151Parser::get_APE_LCOMP02_LRF07()
{
  return APE_LCOMP02_LRF07;
}

vector<vector<vector<vector<Real> > > > MF32MT151Parser::get_APT_LCOMP02_LRF07()
{
  return APT_LCOMP02_LRF07;
}


vector<vector<vector<vector<Real> > > >          MF32MT151Parser::get_ER_LCOMP02_LRF07()
{
  return ER_LCOMP02_LRF07;
}

vector<vector<vector<vector<Real> > > >          MF32MT151Parser::get_DER_LCOMP02_LRF07()
{
  return DER_LCOMP02_LRF07;
}

vector<vector<vector<vector<vector<Real> > > > > MF32MT151Parser::get_GAM_LCOMP02_LRF07()
{
  return GAM_LCOMP02_LRF07;
}

vector<vector<vector<vector<vector<Real> > > > > MF32MT151Parser::get_DGAM_LCOMP02_LRF07()
{
  return DGAM_LCOMP02_LRF07;
}


vector<vector<Integer> >          MF32MT151Parser::get_NDIGIT_LCOMP02_LRF07()
{
  return NDIGIT;
}

vector<vector<Integer> >          MF32MT151Parser::get_NNN_LCOMP02_LRF07()
{
  return NNN;
}

vector<vector<Integer> >          MF32MT151Parser::get_NM_LCOMP02_LRF07()
{
  return NM;
}

vector<vector<vector<Integer> > > MF32MT151Parser::get_II_LCOMP02_LRF07()
{
  return II;
}

vector<vector<vector<Integer> > > MF32MT151Parser::get_JJ_LCOMP02_LRF07()
{
  return JJ;
}

vector<vector<vector<vector<Integer> > > > MF32MT151Parser::get_KIJ_LCOMP02_LRF07()
{
  return KIJ;
}


//LRU=1
vector<vector<vector<Integer> > > MF32MT151Parser::get_IDP_LRU01()
{
  return IDP_LRU01;
}

vector<vector<vector<Integer> > > MF32MT151Parser::get_LB_LRU01()
{
  return LB_LRU01;
}

vector<vector<vector<vector<Real> > > > MF32MT151Parser::get_E_K_LRU01()
{
  return E_K_LRU01;
}

vector<vector<vector<vector<vector<Real> > > > > MF32MT151Parser::get_F_K_LRU01()
{
  return F_K_LRU01;
}


//LRU=2
vector<vector<vector<Real> > >    MF32MT151Parser::get_AWRI_LRU02()
{
  return AWRI_NLS;
}

vector<vector<vector<Integer> > > MF32MT151Parser::get_L_LRU02()
{
  return L;
}

vector<vector<vector<vector<Real> > > > MF32MT151Parser::get_D_LRU02()
{
  return D_LRU02;
}

vector<vector<vector<vector<Real> > > > MF32MT151Parser::get_AJ_LRU02()
{
  return AJ_LRU02;
}

vector<vector<vector<vector<Real> > > > MF32MT151Parser::get_GNO_LRU02()
{
  return GNO_LRU02;
}

vector<vector<vector<vector<Real> > > > MF32MT151Parser::get_GG_LRU02()
{
  return GG_LRU02;
}

vector<vector<vector<vector<Real> > > > MF32MT151Parser::get_GF_LRU02()
{
  return GF_LRU02;
}

vector<vector<vector<vector<Real> > > > MF32MT151Parser::get_GX_LRU02()
{
  return GX_LRU02;
}

vector<vector<Integer> >          MF32MT151Parser::get_MPAR_LRU02()
{
  return MPAR_LRU02;
}

vector<vector<vector<vector<Real> > > > MF32MT151Parser::get_RV_LRU02()
{
  return RV_LRU02;
}


//NRO!=0
vector<vector<Integer> >          MF32MT151Parser::get_NI()
{
  return NI;
}

vector<vector<vector<Integer> > > MF32MT151Parser::get_LB()
{
  return LB;
}

vector<vector<vector<Integer> > > MF32MT151Parser::get_LT()
{
  return LT;
}

vector<vector<vector<vector<Real> > > >          MF32MT151Parser::get_E_K()
{
  return E_K;
}

vector<vector<vector<vector<Real> > > >          MF32MT151Parser::get_E_T()
{
  return E_T;
}

vector<vector<vector<vector<vector<Real> > > > > MF32MT151Parser::get_F_K()
{
  return F_K;
}

vector<vector<vector<vector<vector<Real> > > > > MF32MT151Parser::get_F_T()
{
  return F_T;
}


vector<vector<vector<vector<Real> > > >          MF32MT151Parser::get_E_K_NER()
{
  return E_K;
}

vector<vector<vector<vector<Real> > > >          MF32MT151Parser::get_E_K_NEC()
{
  return E_T;
}


////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void MF32MT151Parser::set_mat_no(Integer& int_data)
{
  mat_no = int_data;
}

void MF32MT151Parser::set_ZAR(Real& real_data)
{
  ZAR = real_data;
}

void MF32MT151Parser::set_AWR(Real& real_data)
{
  AWR = real_data;
}

void MF32MT151Parser::set_NIS(Integer& int_data)
{
  NIS = int_data;
}

void MF32MT151Parser::set_ZAI(vector<Real>& real_vec)
{
  ZAI = real_vec;
}

void MF32MT151Parser::set_ABN(vector<Real>& real_vec)
{
  ABN = real_vec;
}

void MF32MT151Parser::set_LFW(vector<Integer>& int_vec)
{
  LFW = int_vec;
}

void MF32MT151Parser::set_NER(vector<Integer>& int_vec)
{
  NER = int_vec;
}

void MF32MT151Parser::set_EL(vector<vector<Real> >& real_vec)
{
  EL = real_vec;
}

void MF32MT151Parser::set_EH(vector<vector<Real> >& real_vec)
{
  EH = real_vec;
}

void MF32MT151Parser::set_LRU(vector<vector<Integer> >& int_vec)
{
  LRU = int_vec;
}

void MF32MT151Parser::set_LRF(vector<vector<Integer> >& int_vec)
{
  LRF = int_vec;
}

void MF32MT151Parser::set_NRO(vector<vector<Integer> >& int_vec)
{
  NRO = int_vec;
}

void MF32MT151Parser::set_NAPS(vector<vector<Integer> >& int_vec)
{
  NAPS = int_vec;
}

void MF32MT151Parser::set_SPI(vector<vector<Real> >& real_vec)
{
  SPI = real_vec;
}

void MF32MT151Parser::set_AP(vector<vector<Real> >& real_vec)
{
  AP = real_vec;
}

void MF32MT151Parser::set_LAD(vector<vector<Integer> >& int_vec)
{
  LAD = int_vec;
}

void MF32MT151Parser::set_IFG(vector<vector<Integer> >& int_vec)
{
  LAD = int_vec;
}

void MF32MT151Parser::set_LCOMP(vector<vector<Integer> >& int_vec)
{
  LCOMP = int_vec;
}

void MF32MT151Parser::set_NLS(vector<vector<Integer> >& int_vec)
{
  NLS = int_vec;
}

void MF32MT151Parser::set_NJS(vector<vector<Integer> >& int_vec)
{
  NLS = int_vec;
}

void MF32MT151Parser::set_ISR(vector<vector<Integer> >& int_vec)
{
  ISR = int_vec;
}

void MF32MT151Parser::set_AWRI(vector<vector<Real> >& real_vec)
{
  AWRI = real_vec;
}

void MF32MT151Parser::set_AWRI_LCOMP00(vector<vector<vector<Real> > >& real_vec)
{
  AWRI_NLS = real_vec;
}

void MF32MT151Parser::set_L_LCOMP00(vector<vector<vector<Integer> > >& int_vec)
{
  L = int_vec;
}

void MF32MT151Parser::set_DAP_LCOMP00(vector<vector<Real> >& real_vec)
{
  DAP = real_vec;
}

void MF32MT151Parser::set_ER_LCOMP00(vector<vector<vector<vector<Real> > > >& real_vec)
{
  ER_LCOMP00 = real_vec;
}

void MF32MT151Parser::set_AJ_LCOMP00(vector<vector<vector<vector<Real> > > >& real_vec)
{
  AJ_LCOMP00 = real_vec;
}

void MF32MT151Parser::set_GT_LCOMP00(vector<vector<vector<vector<Real> > > >& real_vec)
{
  GT_LCOMP00 = real_vec;
}

void MF32MT151Parser::set_GN_LCOMP00(vector<vector<vector<vector<Real> > > >& real_vec)
{
  GN_LCOMP00 = real_vec;
}

void MF32MT151Parser::set_GG_LCOMP00(vector<vector<vector<vector<Real> > > >& real_vec)
{
  GG_LCOMP00 = real_vec;
}

void MF32MT151Parser::set_GF_LCOMP00(vector<vector<vector<vector<Real> > > >& real_vec)
{
  GF_LCOMP00 = real_vec;
}

void MF32MT151Parser::set_DE_LCOMP00(vector<vector<vector<vector<Real> > > >& real_vec)
{
  DE_LCOMP00 = real_vec;
}

void MF32MT151Parser::set_DN_LCOMP00(vector<vector<vector<vector<Real> > > >& real_vec)
{
  DN_LCOMP00 = real_vec;
}

void MF32MT151Parser::set_DNDG_LCOMP00(vector<vector<vector<vector<Real> > > >& real_vec)
{
  DNDG_LCOMP00 = real_vec;
}

void MF32MT151Parser::set_DG_LCOMP00(vector<vector<vector<vector<Real> > > >& real_vec)
{
  DG_LCOMP00 = real_vec;
}

void MF32MT151Parser::set_DNDF_LCOMP00(vector<vector<vector<vector<Real> > > >& real_vec)
{
  DNDF_LCOMP00 = real_vec;
}

void MF32MT151Parser::set_DGDF_LCOMP00(vector<vector<vector<vector<Real> > > >& real_vec)
{
  DGDF_LCOMP00 = real_vec;
}

void MF32MT151Parser::set_DF_LCOMP00(vector<vector<vector<vector<Real> > > >& real_vec)
{
  DF_LCOMP00 = real_vec;
}

void MF32MT151Parser::set_DJDN_LCOMP00(vector<vector<vector<vector<Real> > > >& real_vec)
{
  DJDN_LCOMP00 = real_vec;
}

void MF32MT151Parser::set_DJDG_LCOMP00(vector<vector<vector<vector<Real> > > >& real_vec)
{
  DJDG_LCOMP00 = real_vec;
}

void MF32MT151Parser::set_DJDF_LCOMP00(vector<vector<vector<vector<Real> > > >& real_vec)
{
  DJDF_LCOMP00 = real_vec;
}

void MF32MT151Parser::set_DJ_LCOMP00(vector<vector<vector<vector<Real> > > >& real_vec)
{
  DJ_LCOMP00 = real_vec;
}

void MF32MT151Parser::set_AWRI_LCOMP01_LRF01(vector<vector<Real> >& real_vec)
{
  AWRI = real_vec;
}

void MF32MT151Parser::set_NSRS_LCOMP01_LRF01(vector<vector<Integer> >& int_vec)
{
  NSRS = int_vec;
}

void MF32MT151Parser::set_NLRS_LCOMP01_LRF01(vector<vector<Integer> >& int_vec)
{
  NLRS = int_vec;
}

void MF32MT151Parser::set_DAP_LCOMP01_LRF01(vector<vector<Real> >& real_vec)
{
  DAP = real_vec;
}

void MF32MT151Parser::set_MPAR_LCOMP01_LRF01(vector<vector<vector<Integer> > >& int_vec)
{
  MPAR_LCOMP01_LRF01 = int_vec;
}

void MF32MT151Parser::set_ER_LCOMP01_LRF01(vector<vector<vector<vector<Real> > > >& real_vec)
{
  ER_LCOMP01_LRF01 = real_vec;
}

void MF32MT151Parser::set_AJ_LCOMP01_LRF01(vector<vector<vector<vector<Real> > > >& real_vec)
{
  AJ_LCOMP01_LRF01 = real_vec;
}

void MF32MT151Parser::set_GT_LCOMP01_LRF01(vector<vector<vector<vector<Real> > > >& real_vec)
{
  GT_LCOMP01_LRF01 = real_vec;
}

void MF32MT151Parser::set_GN_LCOMP01_LRF01(vector<vector<vector<vector<Real> > > >& real_vec)
{
  GN_LCOMP01_LRF01 = real_vec;
}

void MF32MT151Parser::set_GG_LCOMP01_LRF01(vector<vector<vector<vector<Real> > > >& real_vec)
{
  GG_LCOMP01_LRF01 = real_vec;
}

void MF32MT151Parser::set_GF_LCOMP01_LRF01(vector<vector<vector<vector<Real> > > >& real_vec)
{
  GF_LCOMP01_LRF01 = real_vec;
}

void MF32MT151Parser::set_V_LCOMP01_LRF01(vector<vector<vector<vector<vector<Real> > > > >& real_vec)
{
  V = real_vec;
}

void MF32MT151Parser::set_DAP_LCOMP01_LRF03(vector<vector<vector<Real> > >& real_vec)
{
  DAP_TAB = real_vec;
}

void MF32MT151Parser::set_AWRI_LCOMP01_LRF03(vector<vector<Real> >& real_vec)
{
  AWRI = real_vec;
}

void MF32MT151Parser::set_NSRS_LCOMP01_LRF03(vector<vector<Integer> >& int_vec)
{
  NSRS = int_vec;
}

void MF32MT151Parser::set_NLRS_LCOMP01_LRF03(vector<vector<Integer> >& int_vec)
{
  NLRS = int_vec;
}

void MF32MT151Parser::set_MPAR_LCOMP01_LRF03(vector<vector<vector<Integer> > >& int_vec)
{
  MPAR_LCOMP01_LRF01 = int_vec;
}

void MF32MT151Parser::set_ER_LCOMP01_LRF03(vector<vector<vector<vector<Real> > > >& real_vec)
{
  ER_LCOMP01_LRF03 = real_vec;
}

void MF32MT151Parser::set_AJ_LCOMP01_LRF03(vector<vector<vector<vector<Real> > > >& real_vec)
{
  AJ_LCOMP01_LRF03 = real_vec;
}

void MF32MT151Parser::set_GN_LCOMP01_LRF03(vector<vector<vector<vector<Real> > > >& real_vec)
{
  GN_LCOMP01_LRF03 = real_vec;
}

void MF32MT151Parser::set_GG_LCOMP01_LRF03(vector<vector<vector<vector<Real> > > >& real_vec)
{
  GG_LCOMP01_LRF03 = real_vec;
}

void MF32MT151Parser::set_GFA_LCOMP01_LRF03(vector<vector<vector<vector<Real> > > >& real_vec)
{
  GFA_LCOMP01_LRF03 = real_vec;
}

void MF32MT151Parser::set_GFB_LCOMP01_LRF03(vector<vector<vector<vector<Real> > > >& real_vec)
{
  GFB_LCOMP01_LRF03 = real_vec;
}

void MF32MT151Parser::set_V_LCOMP01_LRF03(vector<vector<vector<vector<vector<Real> > > > >& real_vec)
{
  V = real_vec;
}

void MF32MT151Parser::set_AWRI_LCOMP01_LRF04(vector<vector<Real> >& real_vec)
{
  AWRI = real_vec;
}

void MF32MT151Parser::set_NSRS_LCOMP01_LRF04(vector<vector<Integer> >& int_vec)
{
  NSRS = int_vec;
}

void MF32MT151Parser::set_NLRS_LCOMP01_LRF04(vector<vector<Integer> >& int_vec)
{
  NLRS = int_vec;
}

void MF32MT151Parser::set_DAP_LCOMP01_LRF04(vector<vector<Real> >& real_vec)
{
  DAP = real_vec;
}

void MF32MT151Parser::set_MPAR_LCOMP01_LRF04(vector<vector<vector<Integer> > >& int_vec)
{
  MPAR_LCOMP01_LRF01 = int_vec;
}

void MF32MT151Parser::set_DET_LCOMP01_LRF04(vector<vector<vector<vector<Real> > > >& real_vec)
{
  DET_LCOMP01_LRF04 = real_vec;
}

void MF32MT151Parser::set_DWT_LCOMP01_LRF04(vector<vector<vector<vector<Real> > > >& real_vec)
{
  DWT_LCOMP01_LRF04 = real_vec;
}

void MF32MT151Parser::set_GRT_LCOMP01_LRF04(vector<vector<vector<vector<Real> > > >& real_vec)
{
  GRT_LCOMP01_LRF04 = real_vec;
}

void MF32MT151Parser::set_GIT_LCOMP01_LRF04(vector<vector<vector<vector<Real> > > >& real_vec)
{
  GIT_LCOMP01_LRF04 = real_vec;
}

void MF32MT151Parser::set_DEF_LCOMP01_LRF04(vector<vector<vector<vector<Real> > > >& real_vec)
{
  DEF_LCOMP01_LRF04 = real_vec;
}

void MF32MT151Parser::set_DWF_LCOMP01_LRF04(vector<vector<vector<vector<Real> > > >& real_vec)
{
  DWF_LCOMP01_LRF04 = real_vec;
}

void MF32MT151Parser::set_GRF_LCOMP01_LRF04(vector<vector<vector<vector<Real> > > >& real_vec)
{
  GRF_LCOMP01_LRF04 = real_vec;
}

void MF32MT151Parser::set_GIF_LCOMP01_LRF04(vector<vector<vector<vector<Real> > > >& real_vec)
{
  GIF_LCOMP01_LRF04 = real_vec;
}

void MF32MT151Parser::set_DEC_LCOMP01_LRF04(vector<vector<vector<vector<Real> > > >& real_vec)
{
  DEC_LCOMP01_LRF04 = real_vec;
}

void MF32MT151Parser::set_DWC_LCOMP01_LRF04(vector<vector<vector<vector<Real> > > >& real_vec)
{
  DWC_LCOMP01_LRF04 = real_vec;
}

void MF32MT151Parser::set_GRC_LCOMP01_LRF04(vector<vector<vector<vector<Real> > > >& real_vec)
{
  GRC_LCOMP01_LRF04 = real_vec;
}

void MF32MT151Parser::set_GIC_LCOMP01_LRF04(vector<vector<vector<vector<Real> > > >& real_vec)
{
  GIC_LCOMP01_LRF04 = real_vec;
}

void MF32MT151Parser::set_V_LCOMP01_LRF04(vector<vector<vector<vector<vector<Real> > > > >& real_vec)
{
  V = real_vec;
}

void MF32MT151Parser::set_DAP_LCOMP01_LRF07(vector<vector<vector<vector<Real> > > >& real_vec)
{
  DAP_LRF07 = real_vec;
}

void MF32MT151Parser::set_AWRI_LCOMP01_LRF07(vector<vector<Real> >& real_vec)
{
  AWRI = real_vec;
}

void MF32MT151Parser::set_NSRS_LCOMP01_LRF07(vector<vector<Integer> >& int_vec)
{
  NSRS = int_vec;
}

void MF32MT151Parser::set_NLRS_LCOMP01_LRF07(vector<vector<Integer> >& int_vec)
{
  NLRS = int_vec;
}

void MF32MT151Parser::set_NJSX_LCOMP01_LRF07(vector<vector<vector<Integer> > >& int_vec)
{
  NJSX_LCOMP01_LRF07 = int_vec;
}

void MF32MT151Parser::set_ER_LCOMP01_LRF07(vector<vector<vector<vector<vector<Real> > > > >& real_vec)
{
  ER_LCOMP01_LRF07 = real_vec;
}

void MF32MT151Parser::set_GAM_LCOMP01_LRF07(vector<vector<vector<vector<vector<vector<Real> > > > > >& real_vec)
{
  GAM_LCOMP01_LRF07 = real_vec;
}

void MF32MT151Parser::set_V_LCOMP01_LRF07(vector<vector<vector<vector<vector<Real> > > > >& real_vec)
{
  V = real_vec;
}

void MF32MT151Parser::set_DAP_LCOMP02_LRF01(vector<vector<Real> >& real_vec)
{
  DAP = real_vec;
}

void MF32MT151Parser::set_AWRI_LCOMP02_LRF01(vector<vector<Real> >& real_vec)
{
  AWRI = real_vec;
}

void MF32MT151Parser::set_QX_LCOMP02_LRF01(vector<vector<Real> >& real_vec)
{
  QX = real_vec;
}

void MF32MT151Parser::set_LRX_LCOMP02_LRF01(vector<vector<Integer> >& int_vec)
{
  LRX = int_vec;
}

void MF32MT151Parser::set_ER_LCOMP02_LRF01(vector<vector<vector<Real> > >& real_vec)
{
  ER_LCOMP02_LRF01 = real_vec;
}

void MF32MT151Parser::set_AJ_LCOMP02_LRF01(vector<vector<vector<Real> > >& real_vec)
{
  AJ_LCOMP02_LRF01 = real_vec;
}

void MF32MT151Parser::set_GT_LCOMP02_LRF01(vector<vector<vector<Real> > >& real_vec)
{
  GT_LCOMP02_LRF01 = real_vec;
}

void MF32MT151Parser::set_GN_LCOMP02_LRF01(vector<vector<vector<Real> > >& real_vec)
{
  GN_LCOMP02_LRF01 = real_vec;
}

void MF32MT151Parser::set_GG_LCOMP02_LRF01(vector<vector<vector<Real> > >& real_vec)
{
  GG_LCOMP02_LRF01 = real_vec;
}

void MF32MT151Parser::set_GF_LCOMP02_LRF01(vector<vector<vector<Real> > >& real_vec)
{
  GF_LCOMP02_LRF01 = real_vec;
}

void MF32MT151Parser::set_DER_LCOMP02_LRF01(vector<vector<vector<Real> > >& real_vec)
{
  DER_LCOMP02_LRF01 = real_vec;
}

void MF32MT151Parser::set_DGN_LCOMP02_LRF01(vector<vector<vector<Real> > >& real_vec)
{
  DGN_LCOMP02_LRF01 = real_vec;
}

void MF32MT151Parser::set_DGG_LCOMP02_LRF01(vector<vector<vector<Real> > >& real_vec)
{
  DGG_LCOMP02_LRF01 = real_vec;
}

void MF32MT151Parser::set_DGF_LCOMP02_LRF01(vector<vector<vector<Real> > >& real_vec)
{
  DGF_LCOMP02_LRF01 = real_vec;
}

void MF32MT151Parser::set_NDIGIT_LCOMP02_LRF01(vector<vector<Integer> >& int_vec)
{
  NDIGIT = int_vec;
}

void MF32MT151Parser::set_NNN_LCOMP02_LRF01(vector<vector<Integer> >& int_vec)
{
  NNN = int_vec;
}

void MF32MT151Parser::set_NM_LCOMP02_LRF01(vector<vector<Integer> >& int_vec)
{
  NM = int_vec;
}

void MF32MT151Parser::set_II_LCOMP02_LRF01(vector<vector<vector<Integer> > >& int_vec)
{
  II = int_vec;
}

void MF32MT151Parser::set_JJ_LCOMP02_LRF01(vector<vector<vector<Integer> > >& int_vec)
{
  JJ = int_vec;
}

void MF32MT151Parser::set_KIJ_LCOMP02_LRF01(vector<vector<vector<vector<Integer> > > >& int_vec)
{
  KIJ = int_vec;
}

void MF32MT151Parser::set_DAP_LCOMP02_LRF03(vector<vector<vector<Real> > >& real_vec)
{
  DAP_TAB = real_vec;
}

void MF32MT151Parser::set_AWRI_LCOMP02_LRF03(vector<vector<Real> >& real_vec)
{
  AWRI = real_vec;
}

void MF32MT151Parser::set_APL_LCOMP02_LRF03(vector<vector<Real> >& real_vec)
{
  APL = real_vec;
}

void MF32MT151Parser::set_ER_LCOMP02_LRF03(vector<vector<vector<Real> > >& real_vec)
{
  ER_LCOMP02_LRF03 = real_vec;
}

void MF32MT151Parser::set_AJ_LCOMP02_LRF03(vector<vector<vector<Real> > >& real_vec)
{
  AJ_LCOMP02_LRF03 = real_vec;
}

void MF32MT151Parser::set_GN_LCOMP02_LRF03(vector<vector<vector<Real> > >& real_vec)
{
  GN_LCOMP02_LRF03 = real_vec;
}

void MF32MT151Parser::set_GG_LCOMP02_LRF03(vector<vector<vector<Real> > >& real_vec)
{
  GG_LCOMP02_LRF03 = real_vec;
}

void MF32MT151Parser::set_GFA_LCOMP02_LRF03(vector<vector<vector<Real> > >& real_vec)
{
  GFA_LCOMP02_LRF03 = real_vec;
}

void MF32MT151Parser::set_GFB_LCOMP02_LRF03(vector<vector<vector<Real> > >& real_vec)
{
  GFB_LCOMP02_LRF03 = real_vec;
}

void MF32MT151Parser::set_DER_LCOMP02_LRF03(vector<vector<vector<Real> > >& real_vec)
{
  DER_LCOMP02_LRF03 = real_vec;
}

void MF32MT151Parser::set_DGN_LCOMP02_LRF03(vector<vector<vector<Real> > >& real_vec)
{
  DGN_LCOMP02_LRF03 = real_vec;
}

void MF32MT151Parser::set_DGG_LCOMP02_LRF03(vector<vector<vector<Real> > >& real_vec)
{
  DGG_LCOMP02_LRF03 = real_vec;
}

void MF32MT151Parser::set_DGFA_LCOMP02_LRF03(vector<vector<vector<Real> > >& real_vec)
{
  DGFA_LCOMP02_LRF03 = real_vec;
}

void MF32MT151Parser::set_DGFB_LCOMP02_LRF03(vector<vector<vector<Real> > >& real_vec)
{
  DGFB_LCOMP02_LRF03 = real_vec;
}

void MF32MT151Parser::set_NDIGIT_LCOMP02_LRF03(vector<vector<Integer> >& int_vec)
{
  NDIGIT = int_vec;
}

void MF32MT151Parser::set_NNN_LCOMP02_LRF03(vector<vector<Integer> >& int_vec)
{
  NNN = int_vec;
}

void MF32MT151Parser::set_NM_LCOMP02_LRF03(vector<vector<Integer> >& int_vec)
{
  NM = int_vec;
}

void MF32MT151Parser::set_II_LCOMP02_LRF03(vector<vector<vector<Integer> > >& int_vec)
{
  II = int_vec;
}

void MF32MT151Parser::set_JJ_LCOMP02_LRF03(vector<vector<vector<Integer> > >& int_vec)
{
  JJ = int_vec;
}

void MF32MT151Parser::set_KIJ_LCOMP02_LRF03(vector<vector<vector<vector<Integer> > > >& int_vec)
{
  KIJ = int_vec;
}

void MF32MT151Parser::set_DAP_LCOMP02_LRF07(vector<vector<vector<vector<Real> > > >& real_vec)
{
  DAP_LRF07 = real_vec;
}

void MF32MT151Parser::set_NJSX_LCOMP02_LRF07(vector<vector<Integer> >& int_vec)
{
  NJSX_LCOMP02_LRF07 = int_vec;
}

void MF32MT151Parser::set_MA_LCOMP02_LRF07(vector<vector<vector<Real> > >& real_vec)
{
  MA_LCOMP02_LRF07 = real_vec;
}

void MF32MT151Parser::set_MB_LCOMP02_LRF07(vector<vector<vector<Real> > >& real_vec)
{
  MB_LCOMP02_LRF07 = real_vec;
}

void MF32MT151Parser::set_ZA_LCOMP02_LRF07(vector<vector<vector<Real> > >& real_vec)
{
  ZA_LCOMP02_LRF07 = real_vec;
}

void MF32MT151Parser::set_ZB_LCOMP02_LRF07(vector<vector<vector<Real> > >& real_vec)
{
  ZB_LCOMP02_LRF07 = real_vec;
}

void MF32MT151Parser::set_IA_LCOMP02_LRF07(vector<vector<vector<Real> > >& real_vec)
{
  IA_LCOMP02_LRF07 = real_vec;
}

void MF32MT151Parser::set_IB_LCOMP02_LRF07(vector<vector<vector<Real> > >& real_vec)
{
  IB_LCOMP02_LRF07 = real_vec;
}

void MF32MT151Parser::set_Q_LCOMP02_LRF07(vector<vector<vector<Real> > >& real_vec)
{
  Q_LCOMP02_LRF07 = real_vec;
}

void MF32MT151Parser::set_PNT_LCOMP02_LRF07(vector<vector<vector<Real> > >& real_vec)
{
  PNT_LCOMP02_LRF07 = real_vec;
}

void MF32MT151Parser::set_SHF_LCOMP02_LRF07(vector<vector<vector<Real> > >& real_vec)
{
  SHF_LCOMP02_LRF07 = real_vec;
}

void MF32MT151Parser::set_MT_LCOMP02_LRF07(vector<vector<vector<Real> > >& real_vec)
{
  MT_LCOMP02_LRF07 = real_vec;
}

void MF32MT151Parser::set_PA_LCOMP02_LRF07(vector<vector<vector<Real> > >& real_vec)
{
  PA_LCOMP02_LRF07 = real_vec;
}

void MF32MT151Parser::set_PB_LCOMP02_LRF07(vector<vector<vector<Real> > >& real_vec)
{
  PB_LCOMP02_LRF07 = real_vec;
}

void MF32MT151Parser::set_AJ_LCOMP02_LRF07(vector<vector<vector<Real> > >& real_vec)
{
  AJ_LCOMP02_LRF07 = real_vec;
}

void MF32MT151Parser::set_PJ_LCOMP02_LRF07(vector<vector<vector<Real> > >& real_vec)
{
  PJ_LCOMP02_LRF07 = real_vec;
}

void MF32MT151Parser::set_PPI_LCOMP02_LRF07(vector<vector<vector<vector<Real> > > >& real_vec)
{
  PPI_LCOMP02_LRF07 = real_vec;
}

void MF32MT151Parser::set_L_LCOMP02_LRF07(vector<vector<vector<vector<Real> > > >& real_vec)
{
  L_LCOMP02_LRF07 = real_vec;
}

void MF32MT151Parser::set_SCH_LCOMP02_LRF07(vector<vector<vector<vector<Real> > > >& real_vec)
{
  SCH_LCOMP02_LRF07 = real_vec;
}

void MF32MT151Parser::set_BND_LCOMP02_LRF07(vector<vector<vector<vector<Real> > > >& real_vec)
{
  BND_LCOMP02_LRF07 = real_vec;
}

void MF32MT151Parser::set_APE_LCOMP02_LRF07(vector<vector<vector<vector<Real> > > >& real_vec)
{
  APE_LCOMP02_LRF07 = real_vec;
}

void MF32MT151Parser::set_APT_LCOMP02_LRF07(vector<vector<vector<vector<Real> > > >& real_vec)
{
  APT_LCOMP02_LRF07 = real_vec;
}

void MF32MT151Parser::set_ER_LCOMP02_LRF07(vector<vector<vector<vector<Real> > > >& real_vec)
{
  ER_LCOMP02_LRF07 = real_vec;
}

void MF32MT151Parser::set_DER_LCOMP02_LRF07(vector<vector<vector<vector<Real> > > >& real_vec)
{
  DER_LCOMP02_LRF07 = real_vec;
}

void MF32MT151Parser::set_GAM_LCOMP02_LRF07(vector<vector<vector<vector<vector<Real> > > > >& real_vec)
{
  GAM_LCOMP02_LRF07 = real_vec;
}

void MF32MT151Parser::set_DGAM_LCOMP02_LRF07(vector<vector<vector<vector<vector<Real> > > > >& real_vec)
{
  DGAM_LCOMP02_LRF07 = real_vec;
}

void MF32MT151Parser::set_NDIGIT_LCOMP02_LRF07(vector<vector<Integer> >& int_vec)
{
  NDIGIT = int_vec;
}

void MF32MT151Parser::set_NNN_LCOMP02_LRF07(vector<vector<Integer> >& int_vec)
{
  NNN = int_vec;
}

void MF32MT151Parser::set_NM_LCOMP02_LRF07(vector<vector<Integer> >& int_vec)
{
  NM = int_vec;
}

void MF32MT151Parser::set_II_LCOMP02_LRF07(vector<vector<vector<Integer> > >& int_vec)
{
  II = int_vec;
}

void MF32MT151Parser::set_JJ_LCOMP02_LRF07(vector<vector<vector<Integer> > >& int_vec)
{
  JJ = int_vec;
}

void MF32MT151Parser::set_KIJ_LCOMP02_LRF07(vector<vector<vector<vector<Integer> > > >& int_vec)
{
  KIJ = int_vec;
}

void MF32MT151Parser::set_IDP_LRU01(vector<vector<vector<Integer> > >& int_vec)
{
  IDP_LRU01 = int_vec;
}

void MF32MT151Parser::set_LB_LRU01(vector<vector<vector<Integer> > >& int_vec)
{
  LB_LRU01 = int_vec;
}

void MF32MT151Parser::set_E_K_LRU01(vector<vector<vector<vector<Real> > > >& real_vec)
{
  E_K_LRU01 = real_vec;
}

void MF32MT151Parser::set_F_K_LRU01(vector<vector<vector<vector<vector<Real> > > > >& real_vec)
{
  F_K_LRU01 = real_vec;
}

void MF32MT151Parser::set_AWRI_LRU02(vector<vector<vector<Real> > >& real_vec)
{
  AWRI_NLS = real_vec;
}

void MF32MT151Parser::set_L_LRU02(vector<vector<vector<Integer> > >& int_vec)
{
  L = int_vec;
}

void MF32MT151Parser::set_D_LRU02(vector<vector<vector<vector<Real> > > >& real_vec)
{
  D_LRU02 = real_vec;
}

void MF32MT151Parser::set_AJ_LRU02(vector<vector<vector<vector<Real> > > >& real_vec)
{
  AJ_LRU02 = real_vec;
}

void MF32MT151Parser::set_GNO_LRU02(vector<vector<vector<vector<Real> > > >& real_vec)
{
  GNO_LRU02 = real_vec;
}

void MF32MT151Parser::set_GG_LRU02(vector<vector<vector<vector<Real> > > >& real_vec)
{
  GG_LRU02 = real_vec;
}

void MF32MT151Parser::set_GF_LRU02(vector<vector<vector<vector<Real> > > >& real_vec)
{
  GF_LRU02 = real_vec;
}

void MF32MT151Parser::set_GX_LRU02(vector<vector<vector<vector<Real> > > >& real_vec)
{
  GX_LRU02 = real_vec;
}

void MF32MT151Parser::set_MPAR_LRU02(vector<vector<Integer> >& int_vec)
{
  MPAR_LRU02 = int_vec;
}

void MF32MT151Parser::set_RV_LRU02(vector<vector<vector<vector<Real> > > >& real_vec)
{
  RV_LRU02 = real_vec;
}

void MF32MT151Parser::set_NI(vector<vector<Integer> >& int_vec)
{
  NI = int_vec;
}

void MF32MT151Parser::set_LB(vector<vector<vector<Integer> > >& int_vec)
{
  LB = int_vec;
}

void MF32MT151Parser::set_LT(vector<vector<vector<Integer> > >& int_vec)
{
  LT = int_vec;
}

void MF32MT151Parser::set_E_K(vector<vector<vector<vector<Real> > > >& real_vec)
{
  E_K = real_vec;
}

void MF32MT151Parser::set_E_T(vector<vector<vector<vector<Real> > > >& real_vec)
{
  E_T = real_vec;
}

void MF32MT151Parser::set_F_K(vector<vector<vector<vector<vector<Real> > > > >& real_vec)
{
  F_K = real_vec;
}

void MF32MT151Parser::set_F_T(vector<vector<vector<vector<vector<Real> > > > >& real_vec)
{
  F_T = real_vec;
}

void MF32MT151Parser::set_E_K_NER(vector<vector<vector<vector<Real> > > >& real_vec)
{
  E_K = real_vec;
}

void MF32MT151Parser::set_E_K_NEC(vector<vector<vector<vector<Real> > > >& real_vec)
{
  E_T = real_vec;
}

