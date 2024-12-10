#include "EndfUtils/MFxxMTyyyParser/MF02MT151Parser.hpp"

using namespace frendy;

//constructor
MF02MT151Parser::MF02MT151Parser(void)
{
  clear();

  err_obj.set_output_mode(err_obj.warning_off);
}

//destructor
MF02MT151Parser::~MF02MT151Parser(void)
{ 
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF02MT151Parser::store_data() 
{
  MultiParser mp_obj;

  //Text file data check
  if( static_cast<Integer>(text.size()) < 2 )
  {
    string class_name = "MF02MT151Parser";
    string func_name  = "store_data()";

    ostringstream oss;
    oss << static_cast<Integer>(text.size());
    string str_data = "Text line number : " + oss.str();

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("The text line number is not appropriate for  MF=02, MT=151.");
    err_com.push_back("The text line number should be larger than 1.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //Check MT and MF number
  if( mp_obj.check_mf_mt(text, mf_no, mt_no) != 0)
  {
    string class_name = "MF02MT151Parser";
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
    err_com.push_back("The MF and MT numbers are different to MF=02, MT=151.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  mp_obj.get_mat(text, mat_no);

  int     line_no = 0;
  Integer tmp_int;

  //Line No.01
  //ZA, AWR, NIS
  mp_obj.read_head(text, line_no, ZAR, AWR, tmp_int, tmp_int, NIS, tmp_int);

  int nis = static_cast<int>(NIS);
  resize_matrix_vec_first(nis);
  for(int i=0; i<nis; i++)
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

      if( LRU[i][j] == 0 ) 
      {
        store_lru00(mp_obj, line_no, i, j);
      }
      else if( LRU[i][j] == 1 )
      {
        if( LRF[i][j] == 1 || LRF[i][j] == 2 )
        {
          store_lru01_lrf01_02(mp_obj, line_no, i, j);
        }
        else if( LRF[i][j] == 3 )
        {
          store_lru01_lrf03(mp_obj, line_no, i, j);
        }
        else if( LRF[i][j] == 4 )
        {
          store_lru01_lrf04(mp_obj, line_no, i, j);
        }
        else if( LRF[i][j] == 7 )
        {
          store_lru01_lrf07(mp_obj, line_no, i, j);
        }
        else
        {
          string class_name = "MF02MT151Parser";
          string func_name  = "store_data()";

          ostringstream oss01, oss02, oss03, oss04, oss05;
          oss01 << i+1;
          oss02 << nis;
          oss03 << j+1;
          oss04 << static_cast<int>(NER[i]);
          oss05 << static_cast<int>(LRF[i][j]);
          string str_data01 = "NIS : " + oss01.str() + " / " + oss02.str();
          string str_data02 = "NER : " + oss03.str() + " / " + oss04.str();
          string str_data03 = "LRF : " + oss05.str();

          vector<string> err_com;
          err_com.push_back(str_data01);
          err_com.push_back(str_data02);
          err_com.push_back(str_data03);

          if( LRF[i][j] == 5 || LRF[i][j] == 6 )
          {
            err_com.push_back("The format of LRF = 5 or 6 is no longer available in ENDF-6.");
          }
          else
          {
            err_com.push_back("This LRF value is not supported in this program.");
          }
          err_obj.output_runtime_error(class_name, func_name, err_com);
        }
      }
      else if( LRU[i][j] == 2 )
      {
        store_lru02(mp_obj, line_no, i, j);
      }
      else
      {
        string class_name = "MF02MT151Parser";
        string func_name  = "store_data()";

        ostringstream oss01, oss02, oss03, oss04, oss05;
        oss01 << i+1;
        oss02 << nis;
        oss03 << j+1;
        oss04 << static_cast<int>(NER[i]);
        oss05 << static_cast<int>(LRU[i][j]);
        string str_data01 = "NIS : " + oss01.str() + " / " + oss02.str();
        string str_data02 = "NER : " + oss03.str() + " / " + oss04.str();
        string str_data03 = "LRU : " + oss05.str();

        vector<string> err_com;
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back("This LRU value is not supported in this program.");

        err_obj.output_runtime_error(class_name, func_name, err_com);
      }
    }
  }

  mp_obj.line_no_check(text, line_no, mf_no, mt_no);
  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);

  check_spin_data();
  check_energy_range();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF02MT151Parser::check_spin_data() 
{
  //Check Spin of the target nucleus and scattering radius
  int i_max = static_cast<int>(SPI.size());
  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(SPI[i].size());
    for(int j=1; j<j_max; j++)
    {
      //if( fabs(SPI[i][j] - SPI[i][0]) > min_value || fabs(AP[i][j] - AP[i][0]) > min_value )
      if( fabs(SPI[i][j] - SPI[i][0]) > min_value )
      {
        string class_name = "MF02MT151Parser";
        string func_name  = "check_spin_data()";

        vector<string> err_com;
        ostringstream oss01, oss02, oss03, oss04;
        oss01 << i+1;
        oss02 << i_max;
        oss03 << j+1;
        oss04 << j_max;
        string str_data01 = "NIS : " + oss01.str() + " / " + oss02.str();
        string str_data02 = "NER : " + oss03.str() + " / " + oss04.str();
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);

        if( fabs(SPI[i][j] - SPI[i][0]) > min_value )
        {
          ostringstream oss05, oss06;
          oss05 << SPI[i][0];
          oss06 << SPI[i][j];
          string str_data03 = "  SPI[" + oss01.str() + "][0] : "                   + oss05.str();
          string str_data04 = "  SPI[" + oss01.str() + "][" + oss03.str() + "] : " + oss06.str();
          err_com.push_back(str_data03);
          err_com.push_back(str_data04);
          err_com.push_back("Spin of the target nucleus is different.");
          err_com.push_back("Spin data may not be appropriate.");
        }

        //if( fabs(AP[i][j] - AP[i][0]) > min_value )
        //{
        //  ostringstream oss05, oss06;
        //  oss05 << AP[i][0];
        //  oss06 << AP[i][j];
        //  string str_data03 = "  AP[" + oss01.str() + "][0]  : "                   + oss05.str();
        //  string str_data04 = "  AP[" + oss01.str() + "][" + oss03.str() + "]  : " + oss06.str();
        //  err_com.push_back(str_data03);
        //  err_com.push_back(str_data04);
        //  err_com.push_back("Scattering raduis of the target nucleus is different.");
        //  err_com.push_back("Scattering raduis data may not be appropriate.");
        //}
        err_obj.output_caution(class_name, func_name, err_com);
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF02MT151Parser::check_energy_range() 
{
  //Check energy range of the resolved resonance region (RRR) and unresolved resonance region (URR)
  int  rrr_flg = 0;
  int  urr_flg = 0;
  Real el_rrr = 1.0 / min_value;
  Real el_urr = 1.0 / min_value;
  Real eh_rrr = min_value;
  Real eh_urr = min_value;

  int i_max = static_cast<int>(EL.size());
  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(EL[i].size());
    for(int j=0; j<j_max; j++)
    {
      if( LRU[i][j] == 1 )
      {
        rrr_flg++;

        if( el_rrr > EL[i][j] )
        {
          el_rrr = EL[i][j];
        }
        if( eh_rrr < EH[i][j] )
        {
          eh_rrr = EH[i][j];
        }
      }
      else if( LRU[i][j] == 2 )
      {
        urr_flg++;

        if( el_urr > EL[i][j] )
        {
          el_urr = EL[i][j];
        }
        if( eh_urr < EH[i][j] )
        {
          eh_urr = EH[i][j];
        }
      }
    }
  }

  if( rrr_flg > 0 && urr_flg > 0 )
  {
    if( eh_rrr > el_urr * (1.0 + min_ene_dif) )
    {
      string class_name = "MF02MT151Parser";
      string func_name  = "check_energy_range()";

      vector<string> err_com;
      ostringstream oss01, oss02, oss03, oss04;
      oss01.precision(8);
      oss02.precision(8);
      oss03.precision(8);
      oss04.precision(8);
      oss01.setf(ios::scientific);
      oss02.setf(ios::scientific);
      oss03.setf(ios::scientific);
      oss04.setf(ios::scientific);
      oss01.setf(ios::showpoint);
      oss02.setf(ios::showpoint);
      oss03.setf(ios::showpoint);
      oss04.setf(ios::showpoint);

      oss01 << el_rrr;
      oss02 << eh_rrr;
      oss03 << el_urr;
      oss04 << eh_urr;
      string str_data01 = "Energy range of RRR [eV] : " + oss01.str() + " - " + oss02.str();
      string str_data02 = "Energy range of URR [eV] : " + oss03.str() + " - " + oss04.str();
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back("");
      err_com.push_back("The highest energy of resolved resonance region (RRR) is lower than");
      err_com.push_back("the lowest energy of unresolved resonance region(URR).");
      err_com.push_back("This evaluated nuclear data file may not be appropriate.");
      err_com.push_back("Please check the evaluated nuclear data file.");
      err_obj.output_caution(class_name, func_name, err_com);
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF02MT151Parser::store_lru00(MultiParser& mp_obj, int& line_no, int& i, int& j)
{
  vector<Real>    r_vec;
  vector<Integer> i_vec;
  r_vec.resize(6);
  i_vec.resize(6);

  if( LFW[i] == 0 &&  LRF[i][j] == 0 && NRO[i][j] == 0 && NAPS[i][j] == 0 )
  {
    mp_obj.read_cont(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3]);
    SPI[i][j] = r_vec[0]; 
    AP[i][j]  = r_vec[1]; 
    NLS[i][j] = i_vec[2];
  }
  else if( NRO[i][j] > 0 )
  {
    store_nro(mp_obj, line_no, i, j);
  }
  else
  {
    string class_name = "MF02MT151Parser";
    string func_name  = "store_lru00(MultiParser& mp_obj, int& line_no, int& i, int& j)";

    ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07, oss08;
    oss01 << i+1;
    oss02 << static_cast<int>(NIS);
    oss03 << j+1;
    oss04 << static_cast<int>(NER[i]);
    oss05 << static_cast<int>(LFW[i]);
    oss06 << static_cast<int>(LRF[i][j]);
    oss07 << static_cast<int>(NRO[i][j]);
    oss08 << static_cast<int>(NAPS[i][j]);
    string str_data01 = "NIS  : " + oss01.str() + " / " + oss02.str();
    string str_data02 = "NER  : " + oss03.str() + " / " + oss04.str();
    string str_data03 = "LFW  : " + oss05.str();
    string str_data04 = "LRF  : " + oss06.str();
    string str_data05 = "NRO  : " + oss07.str();
    string str_data06 = "NAPS : " + oss08.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back(str_data05);
    err_com.push_back(str_data06);
    err_com.push_back("The format of LRU = 0 has something trouble, please check LFW, NER, LRF, NRO and NAPS.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
  r_vec.clear();
  i_vec.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF02MT151Parser::store_lru01_lrf01_02(MultiParser& mp_obj, int& line_no, int&i, int& j)
{
  vector<Real>    r_vec;
  vector<Integer> i_vec;
  r_vec.resize(6);
  i_vec.resize(6);

  vector<Integer> nbt_vec, int_vec;
  vector<Real>    e_vec,   ap_vec;

  if( NRO[i][j] != 0 )
  {
    store_nro(mp_obj, line_no, i, j);
  }

  mp_obj.read_cont(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3]);
  SPI[i][j] = r_vec[0];
  AP[i][j]  = r_vec[1];
  NLS[i][j] = i_vec[2];

  int nls_max = static_cast<int>(NLS[i][j]);
  AWRI[i][j].resize(nls_max);
  QX_LRU01_LRF01[i][j].resize( nls_max);
  L_LRU01_LRF01[i][j].resize(  nls_max);
  LRX_LRU01_LRF01[i][j].resize(nls_max);
  NRS_LRU01_LRF01[i][j].resize(nls_max);
  ER_LRU01_LRF01[i][j].resize(nls_max);
  AJ_LRU01_LRF01[i][j].resize(nls_max);
  GT_LRU01_LRF01[i][j].resize(nls_max);
  GN_LRU01_LRF01[i][j].resize(nls_max);
  GG_LRU01_LRF01[i][j].resize(nls_max);
  GF_LRU01_LRF01[i][j].resize(nls_max);

  for(int nls=0; nls<nls_max; nls++)
  {
    e_vec.clear();
    mp_obj.read_list(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3], 
                     e_vec);
    AWRI[i][j][nls] = r_vec[0];
    QX_LRU01_LRF01[i][j][nls]   = r_vec[1];
    L_LRU01_LRF01[i][j][nls]    = i_vec[0];
    LRX_LRU01_LRF01[i][j][nls]  = i_vec[1];
    NRS_LRU01_LRF01[i][j][nls]  = i_vec[3];

    if( i_vec[2] != 6*i_vec[3] )
    {
      string class_name = "MF02MT151Parser";
      string func_name  = "store_lru01_lrf01_02(MultiParser& mp_obj, int& line_no, int&i, int& j)";

      ostringstream oss01, oss02, oss03, oss04, oss05, oss06;
      oss01 << i+1;
      oss02 << static_cast<int>(NIS);
      oss03 << j+1;
      oss04 << static_cast<int>(NER[i]);
      oss05 << i_vec[2];
      oss06 << i_vec[3];
      string str_data01 = "NIS    : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "NER    : " + oss03.str() + " / " + oss04.str();
      string str_data03 = "6*NRS  : " + oss05.str();
      string str_data04 = "NRS    : " + oss06.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back(str_data04);
      err_com.push_back("6*NRS at LRF = 1 or 2 must be multiples of 6.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    int k_max = static_cast<int>(NRS_LRU01_LRF01[i][j][nls]);
    ER_LRU01_LRF01[i][j][nls].resize(k_max);
    AJ_LRU01_LRF01[i][j][nls].resize(k_max);
    GT_LRU01_LRF01[i][j][nls].resize(k_max);
    GN_LRU01_LRF01[i][j][nls].resize(k_max);
    GG_LRU01_LRF01[i][j][nls].resize(k_max);
    GF_LRU01_LRF01[i][j][nls].resize(k_max);
    for(int k=0; k<k_max; k++)
    {
      int nrs_no = k * 6;
      ER_LRU01_LRF01[i][j][nls][k] = e_vec[nrs_no+0];
      AJ_LRU01_LRF01[i][j][nls][k] = e_vec[nrs_no+1];
      GT_LRU01_LRF01[i][j][nls][k] = e_vec[nrs_no+2];
      GN_LRU01_LRF01[i][j][nls][k] = e_vec[nrs_no+3];
      GG_LRU01_LRF01[i][j][nls][k] = e_vec[nrs_no+4];
      GF_LRU01_LRF01[i][j][nls][k] = e_vec[nrs_no+5];
    }
  }
  r_vec.clear();
  i_vec.clear();
  nbt_vec.clear();
  int_vec.clear();
  e_vec.clear();
  ap_vec.clear();

  //Check order of ER
  for(int nls=0; nls<nls_max; nls++)
  {
    int k_max = static_cast<int>(ER_LRU01_LRF01[i][j][nls].size());
    for(int k=1; k<k_max; k++)
    {
      if( ER_LRU01_LRF01[i][j][nls][k] < ER_LRU01_LRF01[i][j][nls][k-1] )
      {
        string class_name = "MF02MT151Parser";
        string func_name  = "store_lru01_lrf01_02(MultiParser& mp_obj, int& line_no, int&i, int& j)";

        ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07, oss08, oss09, oss10;
        oss01 << i+1;
        oss02 << static_cast<int>(NIS);
        oss03 << j+1;
        oss04 << static_cast<int>(NER[i]);
        oss05 << nls+1;
        oss06 << nls_max;
        oss07 << k+1;
        oss08 << k_max;
        oss09.setf(ios::scientific);
        oss09.setf(ios::showpoint);
        oss09.precision(8);
        oss10.setf(ios::scientific);
        oss10.setf(ios::showpoint);
        oss10.precision(8);
        oss09 << ER_LRU01_LRF01[i][j][nls][k-1];
        oss10 << ER_LRU01_LRF01[i][j][nls][k];
        string str_data01 = "NIS     : " + oss01.str() + " / " + oss02.str();
        string str_data02 = "NER     : " + oss03.str() + " / " + oss04.str();
        string str_data03 = "NLS     : " + oss05.str() + " / " + oss06.str();
        string str_data04 = "i       : " + oss07.str() + " / " + oss08.str();
        string str_data05 = "ER[i-1] : " + oss09.str();
        string str_data06 = "ER[i]   : " + oss10.str();

        vector<string> err_com;
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back(str_data04);
        err_com.push_back(str_data05);
        err_com.push_back(str_data06);
        err_com.push_back("The order of ER data list is not appropriate (ER[i] < ER[i-1]).");
        err_com.push_back("This resonance parameter may not be correct.");

        err_obj.output_caution(class_name, func_name, err_com);
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF02MT151Parser::store_lru01_lrf03(MultiParser& mp_obj, int& line_no, int&i, int& j)
{
  vector<Real>    r_vec;
  vector<Integer> i_vec;
  r_vec.resize(6);
  i_vec.resize(6);

  if( NRO[i][j] != 0 )
  {
    store_nro(mp_obj, line_no, i, j);
  }

  mp_obj.read_cont(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3]);
  SPI[i][j]              = r_vec[0];
  AP[i][j]               = r_vec[1];
  LAD_LRU01_LRF03[i][j]  = i_vec[0];
  NLS[i][j]              = i_vec[2];
  NLSC_LRU01_LRF03[i][j] = i_vec[3];

  int nls_max = static_cast<int>(NLS[i][j]);
  AWRI[i][j].resize(nls_max);
  APL_LRU01_LRF03[i][j].resize(nls_max);
  L_LRU01_LRF03[i][j].resize(nls_max);
  NRS_LRU01_LRF03[i][j].resize(nls_max);
  ER_LRU01_LRF03[i][j].resize(nls_max);
  AJ_LRU01_LRF03[i][j].resize(nls_max);
  GN_LRU01_LRF03[i][j].resize(nls_max);
  GG_LRU01_LRF03[i][j].resize(nls_max);
  GFA_LRU01_LRF03[i][j].resize(nls_max);
  GFB_LRU01_LRF03[i][j].resize(nls_max);

  for(int nls=0; nls<nls_max; nls++)
  {
    vector<Real>    e_vec;
    e_vec.clear();
    mp_obj.read_list(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                     e_vec);
    AWRI[i][j][nls] = r_vec[0];
    APL_LRU01_LRF03[i][j][nls]  = r_vec[1];
    L_LRU01_LRF03[i][j][nls]    = i_vec[0];
    NRS_LRU01_LRF03[i][j][nls]  = i_vec[3];

    if( i_vec[2] != 6*i_vec[3] )
    {
      string class_name = "MF02MT151Parser";
      string func_name  = "store_lru01_lrf03(MultiParser& mp_obj, int& line_no, int&i, int& j)";

      ostringstream oss01, oss02, oss03, oss04, oss05, oss06;
      oss01 << i+1;
      oss02 << static_cast<int>(NIS);
      oss03 << j+1;
      oss04 << static_cast<int>(NER[i]);
      oss05 << i_vec[2];
      oss06 << i_vec[3];
      string str_data01 = "NIS    : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "NER    : " + oss03.str() + " / " + oss04.str();
      string str_data03 = "6*NRS  : " + oss05.str();
      string str_data04 = "NRS    : " + oss06.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back(str_data04);
      err_com.push_back("6*NRS at LRF = 3 must be multiples of 6.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    int k_max = static_cast<int>(NRS_LRU01_LRF03[i][j][nls]);
    ER_LRU01_LRF03[i][j][nls].resize(k_max);
    AJ_LRU01_LRF03[i][j][nls].resize(k_max);
    GN_LRU01_LRF03[i][j][nls].resize(k_max);
    GG_LRU01_LRF03[i][j][nls].resize(k_max);
    GFA_LRU01_LRF03[i][j][nls].resize(k_max);
    GFB_LRU01_LRF03[i][j][nls].resize(k_max);
    for(int k=0; k<k_max; k++)
    {
      int nrs_no = k * 6;
      ER_LRU01_LRF03[i][j][nls][k]  = e_vec[nrs_no+0];
      AJ_LRU01_LRF03[i][j][nls][k]  = e_vec[nrs_no+1];
      GN_LRU01_LRF03[i][j][nls][k]  = e_vec[nrs_no+2];
      GG_LRU01_LRF03[i][j][nls][k]  = e_vec[nrs_no+3];
      GFA_LRU01_LRF03[i][j][nls][k] = e_vec[nrs_no+4];
      GFB_LRU01_LRF03[i][j][nls][k] = e_vec[nrs_no+5];
    }
  }
  r_vec.clear();
  i_vec.clear();

  //Check order of ER
  for(int nls=0; nls<nls_max; nls++)
  {
    int k_max = static_cast<int>(ER_LRU01_LRF03[i][j][nls].size());
    for(int k=1; k<k_max; k++)
    {
      if( ER_LRU01_LRF03[i][j][nls][k] < ER_LRU01_LRF03[i][j][nls][k-1] )
      {
        string class_name = "MF02MT151Parser";
        string func_name  = "store_lru01_lrf03(MultiParser& mp_obj, int& line_no, int&i, int& j)";

        ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07, oss08, oss09, oss10;
        oss01 << i+1;
        oss02 << static_cast<int>(NIS);
        oss03 << j+1;
        oss04 << static_cast<int>(NER[i]);
        oss05 << nls+1;
        oss06 << nls_max;
        oss07 << k+1;
        oss08 << k_max;
        oss09.setf(ios::scientific);
        oss09.setf(ios::showpoint);
        oss09.precision(8);
        oss10.setf(ios::scientific);
        oss10.setf(ios::showpoint);
        oss10.precision(8);
        oss09 << ER_LRU01_LRF03[i][j][nls][k-1];
        oss10 << ER_LRU01_LRF03[i][j][nls][k];
        string str_data01 = "NIS     : " + oss01.str() + " / " + oss02.str();
        string str_data02 = "NER     : " + oss03.str() + " / " + oss04.str();
        string str_data03 = "NLS     : " + oss05.str() + " / " + oss06.str();
        string str_data04 = "i       : " + oss07.str() + " / " + oss08.str();
        string str_data05 = "ER[i-1] : " + oss09.str();
        string str_data06 = "ER[i]   : " + oss10.str();

        vector<string> err_com;
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back(str_data04);
        err_com.push_back(str_data05);
        err_com.push_back(str_data06);
        err_com.push_back("The order of ER data list is not appropriate (ER[i] < ER[i-1]).");
        err_com.push_back("This resonance parameter may not be correct.");

        err_obj.output_caution(class_name, func_name, err_com);
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF02MT151Parser::store_lru01_lrf04(MultiParser& mp_obj, int& line_no, int& i, int& j)
{
  vector<Real>    r_vec, e_vec;
  vector<Integer> i_vec;
  r_vec.resize(6);
  i_vec.resize(6);

  if( NRO[i][j] != 0 )
  {
    store_nro(mp_obj, line_no, i, j);
  }

  mp_obj.read_cont(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3]);
  SPI[i][j]  = r_vec[0];
  AP[i][j]   = r_vec[1];
  NLS[i][j]  = i_vec[2];
  e_vec.clear();

  mp_obj.read_list(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                   e_vec);
  AWRI[i][j].push_back(r_vec[0]);
  LI_LRU01_LRF04[i][j]   = i_vec[0];
  NX_LRU01_LRF04[i][j]   = i_vec[3];

  if( i_vec[2] != 6*i_vec[3] )
  {
    string class_name = "MF02MT151Parser";
    string func_name  = "store_lru01_lrf04(MultiParser& mp_obj, int& line_no, int& i, int& j)";

    ostringstream oss01, oss02, oss03, oss04, oss05, oss06;
    oss01 << i+1;
    oss02 << static_cast<int>(NIS);
    oss03 << j+1;
    oss04 << static_cast<int>(NER[i]);
    oss05 << i_vec[2];
    oss06 << i_vec[3];
    string str_data01 = "NIS   : " + oss01.str() + " / " + oss02.str();
    string str_data02 = "NER   : " + oss03.str() + " / " + oss04.str();
    string str_data03 = "6*NX  : " + oss05.str();
    string str_data04 = "NX    : " + oss06.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back("6*NX at LRF = 4 must be multiples of 6.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  if( NX_LRU01_LRF04[i][j] > 0 )
  {
    for(int k=0; k<6; k++)
    {
      AT_LRU01_LRF04[i][j].push_back(e_vec[k]);
    }
  }

  if( NX_LRU01_LRF04[i][j] > 1 )
  {
    for(int k=0; k<6; k++)
    {
      AF_LRU01_LRF04[i][j].push_back(e_vec[k+6]);
    }
  }

  if( NX_LRU01_LRF04[i][j] > 2 )
  {
    for(int k=0; k<6; k++)
    {
      AC_LRU01_LRF04[i][j].push_back(e_vec[k+12]);
    }
  }

  int nls_max = static_cast<int>(NLS[i][j]);
  L_LRU01_LRF04[i][j].resize(nls_max);
  NJS_LRU01_LRF04[i][j].resize(nls_max);
  for(int nls=0; nls<nls_max; nls++)
  {
    mp_obj.read_cont(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3]);
    L_LRU01_LRF04[i][j][nls]   = i_vec[0];
    NJS_LRU01_LRF04[i][j][nls] = i_vec[2];

    resize_matrix_vec_lru01_lrf04(i, j, nls, nls_max, static_cast<int>(NJS_LRU01_LRF04[i][j][nls]));

    for(int njs=0; njs<static_cast<int>(NJS_LRU01_LRF04[i][j][nls]); njs++)
    {
      e_vec.clear();
      mp_obj.read_list(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                       e_vec);
      AJ_LRU01_LRF04[i][j][nls][njs]  = r_vec[0];
      NLJ_LRU01_LRF04[i][j][nls][njs] = i_vec[3];
      if( i_vec[2] != 12*i_vec[3] )
      {
        string class_name = "MF02MT151Parser";
        string func_name  = "store_lru01_lrf04(MultiParser& mp_obj, int& line_no, int& i, int& j)";

        ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07, oss08, oss09, oss10;
        oss01 << i+1;
        oss02 << static_cast<int>(NIS);
        oss03 << j+1;
        oss04 << static_cast<int>(NER[i]);
        oss05 << nls;
        oss06 << nls_max;
        oss07 << njs;
        oss08 << static_cast<int>(NJS_LRU01_LRF04[i][j][nls]);
        oss09 << i_vec[2];
        oss10 << i_vec[3];
        string str_data01 = "NIS    : " + oss01.str() + " / " + oss02.str();
        string str_data02 = "NER    : " + oss03.str() + " / " + oss04.str();
        string str_data03 = "NLS    : " + oss05.str() + " / " + oss06.str();
        string str_data04 = "NJS    : " + oss07.str() + " / " + oss08.str();
        string str_data05 = "12*NLJ : " + oss09.str();
        string str_data06 = "NLJ    : " + oss10.str();

        vector<string> err_com;
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back(str_data04);
        err_com.push_back(str_data05);
        err_com.push_back(str_data06);
        err_com.push_back("12*NLJ at LRF = 4 must be multiples of 12.");

        err_obj.output_runtime_error(class_name, func_name, err_com);
      }

      int k_max = static_cast<int>(NLJ_LRU01_LRF04[i][j][nls][njs]);
      DET_LRU01_LRF04[i][j][nls][njs].resize(k_max);
      DWT_LRU01_LRF04[i][j][nls][njs].resize(k_max);
      GRT_LRU01_LRF04[i][j][nls][njs].resize(k_max);
      GIT_LRU01_LRF04[i][j][nls][njs].resize(k_max);
      DEF_LRU01_LRF04[i][j][nls][njs].resize(k_max);
      DWF_LRU01_LRF04[i][j][nls][njs].resize(k_max);
      GRF_LRU01_LRF04[i][j][nls][njs].resize(k_max);
      GIF_LRU01_LRF04[i][j][nls][njs].resize(k_max);
      DEC_LRU01_LRF04[i][j][nls][njs].resize(k_max);
      DWC_LRU01_LRF04[i][j][nls][njs].resize(k_max);
      GRC_LRU01_LRF04[i][j][nls][njs].resize(k_max);
      GIC_LRU01_LRF04[i][j][nls][njs].resize(k_max);
      for(int k=0; k<k_max; k++)
      {
        int nlj_no = k * 12;
        DET_LRU01_LRF04[i][j][nls][njs][k] = e_vec[nlj_no+ 0];
        DWT_LRU01_LRF04[i][j][nls][njs][k] = e_vec[nlj_no+ 1];
        GRT_LRU01_LRF04[i][j][nls][njs][k] = e_vec[nlj_no+ 2];
        GIT_LRU01_LRF04[i][j][nls][njs][k] = e_vec[nlj_no+ 3];
        DEF_LRU01_LRF04[i][j][nls][njs][k] = e_vec[nlj_no+ 4];
        DWF_LRU01_LRF04[i][j][nls][njs][k] = e_vec[nlj_no+ 5];
        GRF_LRU01_LRF04[i][j][nls][njs][k] = e_vec[nlj_no+ 6];
        GIF_LRU01_LRF04[i][j][nls][njs][k] = e_vec[nlj_no+ 7];
        DEC_LRU01_LRF04[i][j][nls][njs][k] = e_vec[nlj_no+ 8];
        DWC_LRU01_LRF04[i][j][nls][njs][k] = e_vec[nlj_no+ 9];
        GRC_LRU01_LRF04[i][j][nls][njs][k] = e_vec[nlj_no+10];
        GIC_LRU01_LRF04[i][j][nls][njs][k] = e_vec[nlj_no+11];
      }
    }
  }
  r_vec.clear();
  e_vec.clear();
  i_vec.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF02MT151Parser::store_lru01_lrf07(MultiParser& mp_obj, int& line_no, int& i, int& j)
{
  vector<Real>    list_vec;
  vector<Real>    r_vec;
  vector<Integer> i_vec;
  r_vec.resize(6);
  i_vec.resize(6);

  mp_obj.read_cont(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3]);

  IFG_LRU01_LRF07[i][j] = i_vec[0];
  KRM_LRU01_LRF07[i][j] = i_vec[1];
  NJS_LRU01_LRF07[i][j] = i_vec[2];
  KRL_LRU01_LRF07[i][j] = i_vec[3];

  if( KRM_LRU01_LRF07[i][j] == 1 || KRM_LRU01_LRF07[i][j] == 2 || KRM_LRU01_LRF07[i][j] == 3 ) 
  {
    list_vec.clear();

    mp_obj.read_list(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                     list_vec);

    NPP_LRU01_LRF07[i][j] = i_vec[0];
    if( i_vec[2] != 12*i_vec[0] )
    {
      string class_name = "MF02MT151Parser";
      string func_name  = "store_lru01_lrf07(MultiParser& mp_obj, int& line_no, int& i, int& j)";

      ostringstream oss01, oss02, oss03, oss04, oss05, oss06;
      oss01 << i+1;
      oss02 << static_cast<int>(NIS);
      oss03 << j+1;
      oss04 << static_cast<int>(NER[i]);
      oss05 << i_vec[0];
      oss06 << i_vec[2];
      string str_data01 = "NIS    : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "NER    : " + oss03.str() + " / " + oss04.str();
      string str_data03 = "NPP    : " + oss05.str();
      string str_data04 = "12*NPP : " + oss06.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back(str_data04);
      err_com.push_back("12*NPP at LRF = 7 must be multiples of 12.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    int k_max = static_cast<int>(NPP_LRU01_LRF07[i][j]);
    MA_LRU01_LRF07[i][j].resize(k_max);
    MB_LRU01_LRF07[i][j].resize(k_max);
    ZA_LRU01_LRF07[i][j].resize(k_max);
    ZB_LRU01_LRF07[i][j].resize(k_max);
    IA_LRU01_LRF07[i][j].resize(k_max);
    IB_LRU01_LRF07[i][j].resize(k_max);
    Q_LRU01_LRF07[i][j].resize(k_max);
    PNT_LRU01_LRF07[i][j].resize(k_max);
    SHF_LRU01_LRF07[i][j].resize(k_max);
    MT_LRU01_LRF07[i][j].resize(k_max);
    PA_LRU01_LRF07[i][j].resize(k_max);
    PB_LRU01_LRF07[i][j].resize(k_max);
    for(int k=0; k<k_max; k++)
    {
      int npp_no = k * 12;
      MA_LRU01_LRF07[i][j][k]  = list_vec[npp_no + 0];
      MB_LRU01_LRF07[i][j][k]  = list_vec[npp_no + 1];
      ZA_LRU01_LRF07[i][j][k]  = list_vec[npp_no + 2];
      ZB_LRU01_LRF07[i][j][k]  = list_vec[npp_no + 3];
      IA_LRU01_LRF07[i][j][k]  = list_vec[npp_no + 4];
      IB_LRU01_LRF07[i][j][k]  = list_vec[npp_no + 5];
      Q_LRU01_LRF07[i][j][k]   = list_vec[npp_no + 6];
      PNT_LRU01_LRF07[i][j][k] = list_vec[npp_no + 7];
      SHF_LRU01_LRF07[i][j][k] = list_vec[npp_no + 8];
      MT_LRU01_LRF07[i][j][k]  = list_vec[npp_no + 9];
      PA_LRU01_LRF07[i][j][k]  = list_vec[npp_no +10];
      PB_LRU01_LRF07[i][j][k]  = list_vec[npp_no +11];
    }
    list_vec.clear();
  }

  int njs_max = static_cast<int>(NJS_LRU01_LRF07[i][j]);
  resize_matrix_vec_lru01_lrf07(i, j, njs_max);
  init_multi_array_lru01_lrf07( i, j, njs_max);

  for(int njs=0; njs<njs_max; njs++)
  {
    list_vec.clear();
    mp_obj.read_list(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                     list_vec);
    AJ_LRU01_LRF07[i][j][njs]  = r_vec[0];
    PJ_LRU01_LRF07[i][j][njs]  = r_vec[1];
    KBK_LRU01_LRF07[i][j][njs] = i_vec[0];
    KPS_LRU01_LRF07[i][j][njs] = i_vec[1];
    NCH_LRU01_LRF07[i][j][njs] = i_vec[3];
    if( i_vec[2] != 6*i_vec[3] )
    {
      string class_name = "MF02MT151Parser";
      string func_name  = "store_lru01_lrf07(MultiParser& mp_obj, int& line_no, int& i, int& j)";

      ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07, oss08;
      oss01 << i+1;
      oss02 << static_cast<int>(NIS);
      oss03 << j+1;
      oss04 << static_cast<int>(NER[i]);
      oss05 << njs+1;
      oss06 << njs_max;
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
      err_com.push_back("6*NCH at LRF = 7 must be multiples of 6.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    int k_max = static_cast<int>(NCH_LRU01_LRF07[i][j][njs]);
    PPI_LRU01_LRF07[i][j][njs].resize(k_max);
    L_LRU01_LRF07[i][j][njs].resize(  k_max);
    SCH_LRU01_LRF07[i][j][njs].resize(k_max);
    BND_LRU01_LRF07[i][j][njs].resize(k_max);
    APE_LRU01_LRF07[i][j][njs].resize(k_max);
    APT_LRU01_LRF07[i][j][njs].resize(k_max);
    for(int k=0; k<k_max; k++)
    {
      int nch_no = k * 6;
      PPI_LRU01_LRF07[i][j][njs][k] = list_vec[nch_no + 0];
      L_LRU01_LRF07[i][j][njs][k]   = list_vec[nch_no + 1];
      SCH_LRU01_LRF07[i][j][njs][k] = list_vec[nch_no + 2];
      BND_LRU01_LRF07[i][j][njs][k] = list_vec[nch_no + 3];
      APE_LRU01_LRF07[i][j][njs][k] = list_vec[nch_no + 4];
      APT_LRU01_LRF07[i][j][njs][k] = list_vec[nch_no + 5];
    }

    list_vec.clear();
    mp_obj.read_list(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                     list_vec);
    NRS_LRU01_LRF07[i][j][njs] = i_vec[1];
    NX_LRU01_LRF07[i][j][njs]  = i_vec[3];
    if( i_vec[2] != 6*i_vec[3] )
    {
      string class_name = "MF02MT151Parser";
      string func_name  = "store_lru01_lrf07(MultiParser& mp_obj, int& line_no, int& i, int& j)";

      ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07, oss08;
      oss01 << i+1;
      oss02 << static_cast<int>(NIS);
      oss03 << j+1;
      oss04 << static_cast<int>(NER[i]);
      oss05 << njs+1;
      oss06 << njs_max;
      oss07 << i_vec[2];
      oss08 << i_vec[3];
      string str_data01 = "NIS  : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "NER  : " + oss03.str() + " / " + oss04.str();
      string str_data03 = "NJS  : " + oss05.str() + " / " + oss06.str();
      string str_data04 = "6*NX : " + oss07.str();
      string str_data05 = "NX   : " + oss08.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back(str_data04);
      err_com.push_back(str_data05);
      err_com.push_back("6*NX at LRF = 7 must be multiples of 6.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    int ele_no = 0;
    k_max =  static_cast<int>(NRS_LRU01_LRF07[i][j][njs]);
    ER_LRU01_LRF07[i][j][njs].resize(k_max);
    GAM_LRU01_LRF07[i][j][njs].resize(k_max);
    for(int k=0; k<k_max; k++)
    {
      ER_LRU01_LRF07[i][j][njs][k] = list_vec[ele_no];
      ele_no++;

      int l_max  = static_cast<int>(NCH_LRU01_LRF07[i][j][njs]);
      GAM_LRU01_LRF07[i][j][njs][k].resize(l_max);
      for(int l=0; l<l_max; l++)
      {
        GAM_LRU01_LRF07[i][j][njs][k][l] = list_vec[ele_no];
        ele_no++;
      }

      while(ele_no%6 != 0 )
      {
        ele_no++;
      }
    }
    list_vec.clear();

    if( KBK_LRU01_LRF07[i][j][njs] > 0 )
    {
      store_lru01_lrf07_kbk(mp_obj, line_no, i, j, njs);
    }

    if( KPS_LRU01_LRF07[i][j][njs] == 1 )
    {
      store_lru01_lrf07_kps(mp_obj, line_no, i, j, njs);
    }
  }

  r_vec.clear();
  i_vec.clear();
  list_vec.clear();


  //Check order of ER
  for(int njs=0; njs<njs_max; njs++)
  {
    int k_max = static_cast<int>(ER_LRU01_LRF07[i][j][njs].size());
    for(int k=1; k<k_max; k++)
    {
      if( ER_LRU01_LRF07[i][j][njs][k] < ER_LRU01_LRF07[i][j][njs][k-1] )
      {
        string class_name = "MF02MT151Parser";
        string func_name  = "store_lru01_lrf07(MultiParser& mp_obj, int& line_no, int&i, int& j)";

        ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07, oss08, oss09, oss10;
        oss01 << i+1;
        oss02 << static_cast<int>(NIS);
        oss03 << j+1;
        oss04 << static_cast<int>(NER[i]);
        oss05 << njs+1;
        oss06 << njs_max;
        oss07 << k+1;
        oss08 << k_max;
        oss09.setf(ios::scientific);
        oss09.setf(ios::showpoint);
        oss09.precision(8);
        oss10.setf(ios::scientific);
        oss10.setf(ios::showpoint);
        oss10.precision(8);
        oss09 << ER_LRU01_LRF07[i][j][njs][k-1];
        oss10 << ER_LRU01_LRF07[i][j][njs][k];
        string str_data01 = "NIS     : " + oss01.str() + " / " + oss02.str();
        string str_data02 = "NER     : " + oss03.str() + " / " + oss04.str();
        string str_data03 = "NJS     : " + oss05.str() + " / " + oss06.str();
        string str_data04 = "i       : " + oss07.str() + " / " + oss08.str();
        string str_data05 = "ER[i-1] : " + oss09.str();
        string str_data06 = "ER[i]   : " + oss10.str();

        vector<string> err_com;
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back(str_data04);
        err_com.push_back(str_data05);
        err_com.push_back(str_data06);
        err_com.push_back("The order of ER data list is not appropriate (ER[i] < ER[i-1]).");
        err_com.push_back("This resonance parameter may not be correct.");

        err_obj.output_caution(class_name, func_name, err_com);
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF02MT151Parser::store_lru01_lrf07_kbk(MultiParser& mp_obj, int& line_no, int& i, int& j, int& njs)
{
  vector<Real>    list_vec;
  list_vec.clear();

  vector<Real>    r_vec;
  vector<Integer> i_vec;
  r_vec.resize(6);
  i_vec.resize(6);

  int read_flg    = -1;
  int line_no_old =  line_no;
  mp_obj.read_cont(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3]);
  if( i_vec[0] > 0 && i_vec[3] == 0 )
  {
    //For ENDF/B-VIII.1
    read_flg = 81;
    LCH_LRU01_LRF07[i][j][njs] = i_vec[0];
    LBK_LRU01_LRF07[i][j][njs] = i_vec[1];
  }
  else if( i_vec[0] == 0 && i_vec[3] == 1 )
  {
    //For ENDF/B-VIII.0, ENDF-B/VII.1, and ENDF-B/VII.0
    read_flg = 80;
    line_no--; //cont -> list
    mp_obj.read_list(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                     list_vec);
    LCH_LRU01_LRF07[i][j][njs] = 0;
    LBK_LRU01_LRF07[i][j][njs] = i_vec[2];
  }

  string class_name = "MF02MT151Parser";
  string func_name  = "store_lru01_lrf07_kbk(MultiParser& mp_obj, int& line_no, int& i, int& j, int& njs)";

  ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07, oss08;
  oss01 << i+1;
  oss02 << static_cast<int>(NIS);
  oss03 << j+1;
  oss04 << static_cast<int>(NER[i]);
  oss05 << njs+1;
  oss06 << static_cast<int>(NJS_LRU01_LRF07[i][j]);
  oss07 << LBK_LRU01_LRF07[i][j][njs];
  oss08 << line_no_old+1;
  string str_data01 = "NIS         : " + oss01.str() + " / " + oss02.str();
  string str_data02 = "NER         : " + oss03.str() + " / " + oss04.str();
  string str_data03 = "NJS         : " + oss05.str() + " / " + oss06.str();
  string str_data04 = "LBK         : " + oss07.str();
  string str_data05 = "line number : " + oss08.str();
  string str_data06 = "line data   : " + text[line_no_old];

  vector<string> err_com;
  err_com.push_back(str_data01);
  err_com.push_back(str_data02);
  err_com.push_back(str_data03);
  err_com.push_back(str_data04);
  err_com.push_back(str_data05);
  err_com.push_back(str_data06);
  err_com.push_back("");
  if( read_flg == 80 )
  {
    err_com.push_back("FRENDY recognized that this data format is ENDF/B-VIII.0 version.");
    err_com.push_back("This data format is used for ENDF/B-VII.0, -VIII.1, and -VIII.0 (BNL-203218-2018-INRE).");
    err_com.push_back("If this nuclear data is ENDF/B-VIII.1 or later version, the processing results may not correct.");
    err_com.push_back("Please check the nuclear data file.");
    err_obj.output_caution(class_name, func_name, err_com);
  }
  else if( read_flg == 81 )
  {
    err_com.push_back("");
    err_com.push_back("FRENDY recognized that this data format is ENDF/B-VIII.1 version.");
    err_com.push_back("This data format is used for ENDF/B-VIII.1 (BNL-224854-2023-INRE).");
    err_com.push_back("If this nuclear data is ENDF/B-VIII.0 or former version, the processing results may not correct.");
    err_com.push_back("Please check the nuclear data file.");
    err_obj.output_caution(class_name, func_name, err_com);
  }
  else
  {
    err_com.push_back("This data format is not available in this code.");
    err_com.push_back("Please check the nuclear data file or modify code.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  if( LBK_LRU01_LRF07[i][j][njs] == 1 )
  {
    vector<Integer> nbt_vec, int_vec;
    vector<Real>    e_vec, tab_vec;

    mp_obj.read_tab1(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                     nbt_vec, int_vec, e_vec, tab_vec);
    NBT_RBR_LRU01_LRF07[i][j][njs]   = nbt_vec;
    INT_RBR_LRU01_LRF07[i][j][njs]   = int_vec;
    E_INT_RBR_LRU01_LRF07[i][j][njs] = e_vec;
    RBR_TAB_LRU01_LRF07[i][j][njs]   = tab_vec;

    mp_obj.read_tab1(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                     nbt_vec, int_vec, e_vec, tab_vec);
    NBT_RBI_LRU01_LRF07[i][j][njs]   = nbt_vec;
    INT_RBI_LRU01_LRF07[i][j][njs]   = int_vec;
    E_INT_RBI_LRU01_LRF07[i][j][njs] = e_vec;
    RBI_TAB_LRU01_LRF07[i][j][njs]   = tab_vec;
    nbt_vec.clear();
    int_vec.clear();
    e_vec.clear();
    tab_vec.clear();
  }
  else if( LBK_LRU01_LRF07[i][j][njs] == 2 )
  {
    if( read_flg == 80 )
    {
      ED_LRU01_LRF07[i][j][njs] = r_vec[0];
      EU_LRU01_LRF07[i][j][njs] = r_vec[1];

      line_no--;

      mp_obj.read_cont_real(text, line_no, r_vec[0], r_vec[1], r_vec[2], r_vec[3], r_vec[4], r_vec[5]);
      R0_LRU01_LRF07[i][j][njs] = r_vec[0];
      R1_LRU01_LRF07[i][j][njs] = r_vec[1];
      R2_LRU01_LRF07[i][j][njs] = r_vec[2];
      S0_LRU01_LRF07[i][j][njs] = r_vec[3];
      S1_LRU01_LRF07[i][j][njs] = r_vec[4];
    }
    else //if( read_flg == 81 )
    {
      mp_obj.read_list(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                       list_vec);
      ED_LRU01_LRF07[i][j][njs] = r_vec[0];
      EU_LRU01_LRF07[i][j][njs] = r_vec[1];
      R0_LRU01_LRF07[i][j][njs] = list_vec[0];
      R1_LRU01_LRF07[i][j][njs] = list_vec[1];
      R2_LRU01_LRF07[i][j][njs] = list_vec[2];
      S0_LRU01_LRF07[i][j][njs] = list_vec[3];
      S1_LRU01_LRF07[i][j][njs] = list_vec[4];
    }
  }
  else if( LBK_LRU01_LRF07[i][j][njs] == 3 )
  {
    if( read_flg == 81 )
    {
      mp_obj.read_list(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                       list_vec);
    }

    ED_LRU01_LRF07[i][j][njs] = r_vec[0];
    EU_LRU01_LRF07[i][j][njs] = r_vec[1];
    R0_LRU01_LRF07[i][j][njs] = list_vec[0];
    S0_LRU01_LRF07[i][j][njs] = list_vec[1];
    GA_LRU01_LRF07[i][j][njs] = list_vec[2];
  }
  else if( LBK_LRU01_LRF07[i][j][njs] != 0 )
  {
    string class_name = "MF02MT151Parser";
    string func_name  = "store_lru01_lrf07_kbk(MultiParser& mp_obj, int& line_no, int& i, int& j, int& njs)";

    ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07;
    oss01 << i+1;
    oss02 << static_cast<int>(NIS);
    oss03 << j+1;
    oss04 << static_cast<int>(NER[i]);
    oss05 << njs+1;
    oss06 << static_cast<int>(NJS_LRU01_LRF07[i][j]);
    oss07 << LBK_LRU01_LRF07[i][j][njs];
    string str_data01 = "NIS   : " + oss01.str() + " / " + oss02.str();
    string str_data02 = "NER   : " + oss03.str() + " / " + oss04.str();
    string str_data03 = "NJS   : " + oss05.str() + " / " + oss06.str();
    string str_data04 = "LBK   : " + oss07.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back("This LBK value is not supported in this program.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
  list_vec.clear();
  r_vec.clear();
  i_vec.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF02MT151Parser::store_lru01_lrf07_kps(MultiParser& mp_obj, int& line_no, int& i, int& j, int& njs)
{
  vector<Real>    list_vec;
  list_vec.clear();

  vector<Real>    r_vec;
  vector<Integer> i_vec;
  r_vec.resize(6);
  i_vec.resize(6);

  mp_obj.read_list(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                   list_vec);
  LPS_LRU01_LRF07[i][j][njs] = i_vec[2];

  if( LPS_LRU01_LRF07[i][j][njs] == 1 )
  {
    vector<Integer> nbt_vec, int_vec;
    vector<Real>    e_vec, tab_vec;

    mp_obj.read_tab1(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                     nbt_vec, int_vec, e_vec, tab_vec);
    NBT_PSR_LRU01_LRF07[i][j][njs]   = nbt_vec;
    INT_PSR_LRU01_LRF07[i][j][njs]   = int_vec;
    E_INT_PSR_LRU01_LRF07[i][j][njs] = e_vec;
    PSR_TAB_LRU01_LRF07[i][j][njs]   = tab_vec;

    mp_obj.read_tab1(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                     nbt_vec, int_vec, e_vec, tab_vec);
    NBT_PSI_LRU01_LRF07[i][j][njs]   = nbt_vec;
    INT_PSI_LRU01_LRF07[i][j][njs]   = int_vec;
    E_INT_PSI_LRU01_LRF07[i][j][njs] = e_vec;
    PSI_TAB_LRU01_LRF07[i][j][njs]   = tab_vec;
    nbt_vec.clear();
    int_vec.clear();
    e_vec.clear();
    tab_vec.clear();
  }
  else if( LPS_LRU01_LRF07[i][j][njs] != 0 )
  {
    string class_name = "MF02MT151Parser";
    string func_name  = "store_lru01_lrf07_kps(MultiParser& mp_obj, int& line_no, int& i, int& j, int& njs)";

    ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07;
    oss01 << i+1;
    oss02 << static_cast<int>(NIS);
    oss03 << j+1;
    oss04 << static_cast<int>(NER[i]);
    oss05 << njs+1;
    oss06 << static_cast<int>(NJS_LRU01_LRF07[i][j]);
    oss07 << LPS_LRU01_LRF07[i][j][njs];
    string str_data01 = "NIS   : " + oss01.str() + " / " + oss02.str();
    string str_data02 = "NER   : " + oss03.str() + " / " + oss04.str();
    string str_data03 = "NJS   : " + oss05.str() + " / " + oss06.str();
    string str_data04 = "LPS   : " + oss07.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back("This LPS value is not supported in this program.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
  list_vec.clear();
  r_vec.clear();
  i_vec.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF02MT151Parser::store_lru02(MultiParser& mp_obj, int& line_no, int& i, int& j)
{
  if( NRO[i][j] != 0 )
  {
    store_nro(mp_obj, line_no, i, j);
  }

  //Case A
  if( LFW[i] == 0 && LRF[i][j] == 1 )
  {
    store_lru02_a(mp_obj, line_no, i, j);
  }
  //Case B
  else if( LFW[i] == 1 && LRF[i][j] == 1 )
  {
    store_lru02_b(mp_obj, line_no, i, j);
  }
  //Case C
  else if( (LFW[i] == 1 && LRF[i][j] == 2) || (LFW[i] == 0 && LRF[i][j] == 2) )
  {
    store_lru02_c(mp_obj, line_no, i, j);
  }
  else
  {
    string class_name = "MF02MT151Parser";
    string func_name  = "store_lru02(MultiParser& mp_obj, int& line_no, int& i, int& j)";

    ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07;
    oss01 << i+1;
    oss02 << static_cast<int>(NIS);
    oss03 << j+1;
    oss04 << static_cast<int>(NER[i]);
    oss05 << LFW[i];
    oss06 << LRF[i][j];
    string str_data01 = "NIS   : " + oss01.str() + " / " + oss02.str();
    string str_data02 = "NER   : " + oss03.str() + " / " + oss04.str();
    string str_data03 = "LFW   : " + oss05.str();
    string str_data04 = "LRF   : " + oss06.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back("The format of LRU = 2 has something trouble.");
    err_com.push_back("Please check LFW and LRF.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF02MT151Parser::store_lru02_a(MultiParser& mp_obj, int& line_no, int& i, int& j)
{
  vector<Real>    r_vec;
  vector<Integer> i_vec;
  r_vec.resize(6);
  i_vec.resize(6);

  mp_obj.read_cont(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3]);
  SPI[i][j]        = r_vec[0];
  AP[i][j]         = r_vec[1];
  LSSF_LRU02[i][j] = i_vec[0];
  NLS[i][j]        = i_vec[2];

  resize_matrix_vec_lru02_a(i, j, static_cast<int>(NLS[i][j]));

  for(int nls=0; nls<static_cast<int>(NLS[i][j]); nls++)
  {
    vector<Real> list_vec;

    mp_obj.read_list(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                     list_vec);
    AWRI[i][j][nls] = r_vec[0];
    L_LRU02[i][j][nls]    = i_vec[0];
    NJS_LRU02[i][j][nls]  = i_vec[3];
    if( i_vec[2] != 6*i_vec[3] )
    {
      string class_name = "MF02MT151Parser";
      string func_name  = "store_lru02_a(MultiParser& mp_obj, int& line_no, int& i, int& j)";

      ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07, oss08;
      oss01 << i+1;
      oss02 << static_cast<int>(NIS);
      oss03 << j+1;
      oss04 << static_cast<int>(NER[i]);
      oss05 << nls+1;
      oss06 << static_cast<int>(NLS[i][j]);
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
      err_com.push_back("6*NJS at LRU = 2, Case A must be multiples of 6.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    int k_max = static_cast<int>(NJS_LRU02[i][j][nls]);
    D_LRU02_A[i][j][nls].resize(   k_max);
    AJ_LRU02_A[i][j][nls].resize(  k_max);
    AMUN_LRU02_A[i][j][nls].resize(k_max);
    GNO_LRU02_A[i][j][nls].resize( k_max);
    GG_LRU02_A[i][j][nls].resize(  k_max);
    for(int k=0; k<k_max; k++)
    {
      int njs_no = k * 6;
      D_LRU02_A[i][j][nls][k]    = list_vec[njs_no + 0];
      AJ_LRU02_A[i][j][nls][k]   = list_vec[njs_no + 1];
      AMUN_LRU02_A[i][j][nls][k] = list_vec[njs_no + 2];
      GNO_LRU02_A[i][j][nls][k]  = list_vec[njs_no + 3];
      GG_LRU02_A[i][j][nls][k]   = list_vec[njs_no + 4];
    }
    list_vec.clear();
  }
  r_vec.clear();
  i_vec.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF02MT151Parser::store_lru02_b(MultiParser& mp_obj, int& line_no, int& i, int& j)
{
  vector<Real>    r_vec;
  vector<Integer> i_vec;
  r_vec.resize(6);
  i_vec.resize(6);

  vector<Real> list_vec;

  mp_obj.read_list(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                   list_vec);
  SPI[i][j]        = r_vec[0];
  AP[i][j]         = r_vec[1];
  LSSF_LRU02[i][j] = i_vec[0];
  NE_LRU02_B[i][j] = i_vec[2];
  NLS[i][j]        = i_vec[3];

  int k_max = static_cast<int>(NE_LRU02_B[i][j]);
  ES_LRU02_B[i][j].resize(k_max);
  for(int k=0; k<k_max; k++)
  {
    ES_LRU02_B[i][j][k] = list_vec[k];
  }
  list_vec.clear();

  if( fabs(ES_LRU02_B[i][j][0]       - EL[i][j]) > fabs(min_ene_dif*EL[i][j]) ||
      fabs(ES_LRU02_B[i][j][k_max-1] - EH[i][j]) > fabs(min_ene_dif*EH[i][j]) )
  {
    string class_name = "MF02MT151Parser";
    string func_name  = "store_lru02_b(MultiParser& mp_obj, int& line_no, int& i, int& j)";

    ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07, oss08, oss09, oss10;
    oss06.precision(8);
    oss06.setf(ios::showpoint);
    oss06.setf(ios::scientific);
    oss07.precision(8);
    oss07.setf(ios::showpoint);
    oss07.setf(ios::scientific);
    oss08.precision(8);
    oss08.setf(ios::showpoint);
    oss08.setf(ios::scientific);
    oss09.precision(8);
    oss09.setf(ios::showpoint);
    oss09.setf(ios::scientific);

    oss01 << i+1;
    oss02 << static_cast<int>(NIS);
    oss03 << j+1;
    oss04 << static_cast<int>(NER[i]);
    oss05 << k_max;
    oss06 << EL[i][j];
    oss07 << EH[i][j];
    oss08 << ES_LRU02_B[i][j][0];
    oss09 << ES_LRU02_B[i][j][k_max-1];
    string str_data01 = "NIS    : " + oss01.str() + " / " + oss02.str();
    string str_data02 = "NER    : " + oss03.str() + " / " + oss04.str();
    string str_data03 = "NE     : " + oss05.str();
    string str_data04 = "EL     : " + oss06.str();
    string str_data05 = "EH     : " + oss07.str();
    string str_data06 = "ES[1]  : " + oss08.str();
    string str_data07 = "ES[NE] : " + oss09.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back(str_data05);
    err_com.push_back(str_data06);
    err_com.push_back(str_data07);
    err_com.push_back("The energy range of EL - EH is different to that of ES[1] - ES[NE].");
    err_com.push_back("Please check the energy range.");

    err_obj.output_caution_format(class_name, func_name, err_com);
  }

  resize_matrix_vec_lru02_b(i, j, static_cast<int>(NLS[i][j]));

  for(int nls=0; nls<static_cast<int>(NLS[i][j]); nls++)
  {
    mp_obj.read_cont(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3]);
    AWRI[i][j][nls] = r_vec[0];
    L_LRU02[i][j][nls]    = i_vec[0];
    NJS_LRU02[i][j][nls]  = i_vec[2];

    int njs_max = static_cast<int>(NJS_LRU02[i][j][nls]);
    MUF_LRU02_B[i][j][nls].resize( njs_max);
    D_LRU02_B[i][j][nls].resize(   njs_max);
    AJ_LRU02_B[i][j][nls].resize(  njs_max);
    AMUN_LRU02_B[i][j][nls].resize(njs_max);
    GNO_LRU02_B[i][j][nls].resize( njs_max);
    GG_LRU02_B[i][j][nls].resize(  njs_max);
    GF_LRU02_B[i][j][nls].resize(  njs_max);

    for(int njs=0; njs<njs_max; njs++)
    {
      mp_obj.read_list(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                       list_vec);
      MUF_LRU02_B[i][j][nls][njs] = i_vec[1];
      if( i_vec[2] != 6+NE_LRU02_B[i][j] )
      {
        string class_name = "MF02MT151Parser";
        string func_name  = "store_lru02_b(MultiParser& mp_obj, int& line_no, int& i, int& j)";

        ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07, oss08, oss09, oss10;
        oss01 << i+1;
        oss02 << static_cast<int>(NIS);
        oss03 << j+1;
        oss04 << static_cast<int>(NER[i]);
        oss05 << nls+1;
        oss06 << static_cast<int>(NLS[i][j]);
        oss07 << njs+1;
        oss08 << njs_max;
        oss09 << i_vec[2];
        oss10 << NE_LRU02_B[i][j];
        string str_data01 = "NIS  : " + oss01.str() + " / " + oss02.str();
        string str_data02 = "NER  : " + oss03.str() + " / " + oss04.str();
        string str_data03 = "NLS  : " + oss05.str() + " / " + oss06.str();
        string str_data04 = "NJS  : " + oss07.str() + " / " + oss08.str();
        string str_data05 = "NE+6 : " + oss09.str();
        string str_data06 = "NE   : " + oss10.str();

        vector<string> err_com;
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back(str_data04);
        err_com.push_back(str_data05);
        err_com.push_back(str_data06);
        err_com.push_back("NE+6 at LRU = 2, Case B is not collect.");

        err_obj.output_runtime_error(class_name, func_name, err_com);
      }

      D_LRU02_B[i][j][nls][njs]    = list_vec[0];
      AJ_LRU02_B[i][j][nls][njs]   = list_vec[1];
      AMUN_LRU02_B[i][j][nls][njs] = list_vec[2];
      GNO_LRU02_B[i][j][nls][njs]  = list_vec[3];
      GG_LRU02_B[i][j][nls][njs]   = list_vec[4];

	  k_max = static_cast<int>(NE_LRU02_B[i][j]);
      GF_LRU02_B[i][j][nls][njs].resize(k_max);
      for(int k=0; k<k_max; k++)
      {
        GF_LRU02_B[i][j][nls][njs][k] = list_vec[k+6];
      }
      list_vec.clear();
    }
  }
  r_vec.clear();
  i_vec.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF02MT151Parser::store_lru02_c(MultiParser& mp_obj, int& line_no, int& i, int& j)
{
  vector<Real>    r_vec;
  vector<Integer> i_vec;
  r_vec.resize(6);
  i_vec.resize(6);

  mp_obj.read_cont(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3]);
  SPI[i][j]        = r_vec[0];
  AP[i][j]         = r_vec[1];
  LSSF_LRU02[i][j] = i_vec[0];
  NLS[i][j]        = i_vec[2];

  int nls_max = static_cast<int>(NLS[i][j]);
  for(int nls=0; nls<nls_max; nls++)
  {
    mp_obj.read_cont(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3]);

    int njs_max = static_cast<int>(i_vec[2]); //NJS_LRU02[i][j][nls]
    resize_matrix_vec_lru02_c(i, j, nls, nls_max, njs_max);

    AWRI[i][j][nls] = r_vec[0];
    L_LRU02[i][j][nls]    = i_vec[0];
    NJS_LRU02[i][j][nls]  = i_vec[2];

    for(int njs=0; njs<njs_max; njs++)
    {
      vector<Real> list_vec;

      mp_obj.read_list(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                       list_vec);
      AJ_LRU02_C[i][j][nls][njs]    = r_vec[0];
      INT_LRU02_C[i][j][nls][njs]   = i_vec[0];
      NE_LRU02_C[i][j][nls][njs]    = i_vec[3];
      AMUX_LRU02_C[i][j][nls][njs]  = list_vec[2];
      AMUN_LRU02_C[i][j][nls][njs]  = list_vec[3];
      AMUG_LRU02_C[i][j][nls][njs]  = list_vec[4];
      AMUF_LRU02_C[i][j][nls][njs]  = list_vec[5];
      if( i_vec[2] != 6*NE_LRU02_C[i][j][nls][njs]+6 )
      {
        string class_name = "MF02MT151Parser";
        string func_name  = "store_lru02_c(MultiParser& mp_obj, int& line_no, int& i, int& j)";

        ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07, oss08, oss09, oss10;
        oss01 << i+1;
        oss02 << static_cast<int>(NIS);
        oss03 << j+1;
        oss04 << static_cast<int>(NER[i]);
        oss05 << nls+1;
        oss06 << nls_max;
        oss07 << njs+1;
        oss08 << njs_max;
        oss09 << i_vec[2];
        oss10 << NE_LRU02_C[i][j][nls][njs];
        string str_data01 = "NIS    : " + oss01.str() + " / " + oss02.str();
        string str_data02 = "NER    : " + oss03.str() + " / " + oss04.str();
        string str_data03 = "NLS    : " + oss05.str() + " / " + oss06.str();
        string str_data04 = "NJS    : " + oss07.str() + " / " + oss08.str();
        string str_data05 = "6*NE+6 : " + oss09.str();
        string str_data06 = "NE     : " + oss10.str();

        vector<string> err_com;
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back(str_data04);
        err_com.push_back(str_data05);
        err_com.push_back(str_data06);
        err_com.push_back("6*NE+6 at LRU = 2, Case C must be multiples of 6");

        err_obj.output_runtime_error(class_name, func_name, err_com);
      }

      int k_max = static_cast<int>(NE_LRU02_C[i][j][nls][njs]);
      ES_LRU02_C[i][j][nls][njs].resize( k_max);
      D_LRU02_C[i][j][nls][njs].resize(  k_max);
      GX_LRU02_C[i][j][nls][njs].resize( k_max);
      GNO_LRU02_C[i][j][nls][njs].resize(k_max);
      GG_LRU02_C[i][j][nls][njs].resize( k_max);
      GF_LRU02_C[i][j][nls][njs].resize( k_max);
      for(int k=0; k<k_max; k++)
      {
        int ne_no = (k+1) * 6;
        ES_LRU02_C[i][j][nls][njs][k]  = list_vec[ne_no + 0];
        D_LRU02_C[i][j][nls][njs][k]   = list_vec[ne_no + 1];
        GX_LRU02_C[i][j][nls][njs][k]  = list_vec[ne_no + 2];
        GNO_LRU02_C[i][j][nls][njs][k] = list_vec[ne_no + 3];
        GG_LRU02_C[i][j][nls][njs][k]  = list_vec[ne_no + 4];
        GF_LRU02_C[i][j][nls][njs][k]  = list_vec[ne_no + 5];
      }
      list_vec.clear();
    }
  }
  r_vec.clear();
  i_vec.clear();

  if( nls_max > 0 )
  {
    Integer int_ori = INT_LRU02_C[i][j][0][0];
    for(int nls=0; nls<nls_max; nls++)
    {
      int njs_max = static_cast<int>(INT_LRU02_C[i][j][nls].size());
      for(int njs=0; njs<njs_max; njs++)
      {
        if( int_ori != INT_LRU02_C[i][j][nls][njs] )
        {
          string class_name = "MF02MT151Parser";
          string func_name  = "store_lru02_c(MultiParser& mp_obj, int& line_no, int& i, int& j)";

          ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07, oss08, oss09, oss10;
          oss01 << i+1;
          oss02 << static_cast<int>(NIS);
          oss03 << j+1;
          oss04 << static_cast<int>(NER[i]);
          oss05 << nls+1;
          oss06 << nls_max;
          oss07 << njs+1;
          oss08 << njs_max;
          oss09 << int_ori;
          oss10 << INT_LRU02_C[i][j][nls][njs];
          string str_data01 = "NIS           : " + oss01.str() + " / " + oss02.str();
          string str_data02 = "NER           : " + oss03.str() + " / " + oss04.str();
          string str_data03 = "NLS           : " + oss05.str() + " / " + oss06.str();
          string str_data04 = "NJS           : " + oss07.str() + " / " + oss08.str();
          string str_data05 = "INT[0][0]     : " + oss09.str();
          string str_data06 = "INT[NLS][NJS] : " + oss10.str();

          vector<string> err_com;
          err_com.push_back(str_data01);
          err_com.push_back(str_data02);
          err_com.push_back(str_data03);
          err_com.push_back(str_data04);
          err_com.push_back(str_data05);
          err_com.push_back(str_data06);
          err_com.push_back("INT value is different in each NLS or NJS.");
          err_com.push_back("In ProbabilityTableCalculatorByNjoyInput, only INT[0][0] value is output");
          err_com.push_back("in MF02MT152Parser.");
          err_com.push_back("Please be careful if you use the ProbabilityTableCalculatorByNjoyInput class");

          err_obj.output_caution(class_name, func_name, err_com);
        }

        int k_max = static_cast<int>(ES_LRU02_C[i][j][nls][njs].size());
        if( fabs(ES_LRU02_C[i][j][nls][njs][0]       - EL[i][j]) > fabs(min_ene_dif*EL[i][j]) ||
            fabs(ES_LRU02_C[i][j][nls][njs][k_max-1] - EH[i][j]) > fabs(min_ene_dif*EH[i][j]) )
        {
          string class_name = "MF02MT151Parser";
          string func_name  = "store_lru02_c(MultiParser& mp_obj, int& line_no, int& i, int& j)";

          ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07, oss08, oss09, oss10,
                        oss11, oss12, oss13;
          oss10.precision(8);
          oss10.setf(ios::showpoint);
          oss10.setf(ios::scientific);
          oss11.precision(8);
          oss11.setf(ios::showpoint);
          oss11.setf(ios::scientific);
          oss12.precision(8);
          oss12.setf(ios::showpoint);
          oss12.setf(ios::scientific);
          oss13.precision(8);
          oss13.setf(ios::showpoint);
          oss13.setf(ios::scientific);

          oss01 << i+1;
          oss02 << static_cast<int>(NIS);
          oss03 << j+1;
          oss04 << static_cast<int>(NER[i]);
          oss05 << nls+1;
          oss06 << nls_max;
          oss07 << njs+1;
          oss08 << njs_max;
          oss09 << k_max;
          oss10 << EL[i][j];
          oss11 << EH[i][j];
          oss12 << ES_LRU02_C[i][j][nls][njs][0];
          oss13 << ES_LRU02_C[i][j][nls][njs][k_max-1];

          string str_data01 = "NIS    : " + oss01.str() + " / " + oss02.str();
          string str_data02 = "NER    : " + oss03.str() + " / " + oss04.str();
          string str_data03 = "NLS    : " + oss05.str() + " / " + oss06.str();
          string str_data04 = "NJS    : " + oss07.str() + " / " + oss08.str();
          string str_data05 = "NE     : " + oss09.str();
          string str_data06 = "EL     : " + oss10.str();
          string str_data07 = "EH     : " + oss11.str();
          string str_data08 = "ES[1]  : " + oss12.str();
          string str_data09 = "ES[NE] : " + oss13.str();

          vector<string> err_com;
          err_com.push_back(str_data01);
          err_com.push_back(str_data02);
          err_com.push_back(str_data03);
          err_com.push_back(str_data04);
          err_com.push_back(str_data05);
          err_com.push_back(str_data06);
          err_com.push_back(str_data07);
          err_com.push_back(str_data08);
          err_com.push_back(str_data09);
          err_com.push_back("The energy range of EL - EH is different to that of ES[1] - ES[NE].");
          err_com.push_back("Please check the energy range.");

          err_obj.output_caution_format(class_name, func_name, err_com);
        }

      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF02MT151Parser::store_nro(MultiParser& mp_obj, int& line_no, int& i, int& j)
{
  vector<Real>    r_vec;
  vector<Integer> i_vec;
  r_vec.resize(6);
  i_vec.resize(6);

  vector<Integer> nbt_vec, int_vec;
  vector<Real>    e_vec,   ap_vec;

  mp_obj.read_tab1(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                   nbt_vec, int_vec, e_vec, ap_vec);

  NBT_AP_NRO[i][j]   = nbt_vec;
  INT_AP_NRO[i][j]   = int_vec;
  E_INT_AP_NRO[i][j] = e_vec;
  AP_TAB_NRO[i][j]   = ap_vec;

  r_vec.clear();
  i_vec.clear();
  nbt_vec.clear();
  int_vec.clear();
  e_vec.clear();
  ap_vec.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF02MT151Parser::resize_matrix_vec_first(int ele_no)
{
  //Common data
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

  SPI.resize(ele_no);
  AP.resize( ele_no);
  NLS.resize(ele_no);

  NBT_AP_NRO.resize(  ele_no);
  INT_AP_NRO.resize(  ele_no);
  E_INT_AP_NRO.resize(ele_no);
  AP_TAB_NRO.resize(  ele_no);

  AWRI.resize( ele_no);

  //LRU=1, LRF=1 or 2
  QX_LRU01_LRF01.resize(   ele_no);
  L_LRU01_LRF01.resize(    ele_no);
  LRX_LRU01_LRF01.resize(  ele_no);
  NRS_LRU01_LRF01.resize(  ele_no);
  ER_LRU01_LRF01.resize(   ele_no);
  AJ_LRU01_LRF01.resize(   ele_no);
  GT_LRU01_LRF01.resize(   ele_no);
  GN_LRU01_LRF01.resize(   ele_no);
  GG_LRU01_LRF01.resize(   ele_no);
  GF_LRU01_LRF01.resize(   ele_no);

  //LRU=1, LRF=3
  LAD_LRU01_LRF03.resize( ele_no);
  NLSC_LRU01_LRF03.resize(ele_no);

  APL_LRU01_LRF03.resize( ele_no);
  L_LRU01_LRF03.resize(   ele_no);
  NRS_LRU01_LRF03.resize( ele_no);
  ER_LRU01_LRF03.resize(  ele_no);
  AJ_LRU01_LRF03.resize(  ele_no);
  GN_LRU01_LRF03.resize(  ele_no);
  GG_LRU01_LRF03.resize(  ele_no);
  GFA_LRU01_LRF03.resize( ele_no);
  GFB_LRU01_LRF03.resize( ele_no);

  //LRU=1, LRF=4
  LI_LRU01_LRF04.resize(ele_no);
  NX_LRU01_LRF04.resize(ele_no);

  AT_LRU01_LRF04.resize(  ele_no);
  AF_LRU01_LRF04.resize(  ele_no);
  AC_LRU01_LRF04.resize(  ele_no);

  L_LRU01_LRF04.resize(  ele_no);
  NJS_LRU01_LRF04.resize(ele_no);
  AJ_LRU01_LRF04.resize( ele_no);
  NLJ_LRU01_LRF04.resize(ele_no);
  DET_LRU01_LRF04.resize(ele_no);
  DWT_LRU01_LRF04.resize(ele_no);
  GRT_LRU01_LRF04.resize(ele_no);
  GIT_LRU01_LRF04.resize(ele_no);
  DEF_LRU01_LRF04.resize(ele_no);
  DWF_LRU01_LRF04.resize(ele_no);
  GRF_LRU01_LRF04.resize(ele_no);
  GIF_LRU01_LRF04.resize(ele_no);
  DEC_LRU01_LRF04.resize(ele_no);
  DWC_LRU01_LRF04.resize(ele_no);
  GRC_LRU01_LRF04.resize(ele_no);
  GIC_LRU01_LRF04.resize(ele_no);

  //LRU=1, LRF=7
  IFG_LRU01_LRF07.resize(ele_no);
  KRM_LRU01_LRF07.resize(ele_no);
  NJS_LRU01_LRF07.resize(ele_no);
  KRL_LRU01_LRF07.resize(ele_no);
  NPP_LRU01_LRF07.resize(ele_no);

  MA_LRU01_LRF07.resize( ele_no);
  MB_LRU01_LRF07.resize( ele_no);
  ZA_LRU01_LRF07.resize( ele_no);
  ZB_LRU01_LRF07.resize( ele_no);
  IA_LRU01_LRF07.resize( ele_no);
  IB_LRU01_LRF07.resize( ele_no);
  Q_LRU01_LRF07.resize(  ele_no);
  PNT_LRU01_LRF07.resize(ele_no);
  SHF_LRU01_LRF07.resize(ele_no);
  MT_LRU01_LRF07.resize( ele_no);
  PA_LRU01_LRF07.resize( ele_no);
  PB_LRU01_LRF07.resize( ele_no);

  AJ_LRU01_LRF07.resize( ele_no);
  PJ_LRU01_LRF07.resize( ele_no);
  KBK_LRU01_LRF07.resize(ele_no);
  KPS_LRU01_LRF07.resize(ele_no);
  NCH_LRU01_LRF07.resize(ele_no);
  PPI_LRU01_LRF07.resize(ele_no);
  L_LRU01_LRF07.resize(  ele_no);
  SCH_LRU01_LRF07.resize(ele_no);
  BND_LRU01_LRF07.resize(ele_no);
  APE_LRU01_LRF07.resize(ele_no);
  APT_LRU01_LRF07.resize(ele_no);

  NRS_LRU01_LRF07.resize(ele_no);
  NX_LRU01_LRF07.resize( ele_no);
  ER_LRU01_LRF07.resize( ele_no);
  GAM_LRU01_LRF07.resize(ele_no);

  LCH_LRU01_LRF07.resize(      ele_no);
  LBK_LRU01_LRF07.resize(      ele_no);
  NBT_RBR_LRU01_LRF07.resize(  ele_no);
  INT_RBR_LRU01_LRF07.resize(  ele_no);
  E_INT_RBR_LRU01_LRF07.resize(ele_no);
  RBR_TAB_LRU01_LRF07.resize(  ele_no);
  NBT_RBI_LRU01_LRF07.resize(  ele_no);
  INT_RBI_LRU01_LRF07.resize(  ele_no);
  E_INT_RBI_LRU01_LRF07.resize(ele_no);
  RBI_TAB_LRU01_LRF07.resize(  ele_no);

  ED_LRU01_LRF07.resize(ele_no);
  EU_LRU01_LRF07.resize(ele_no);
  R0_LRU01_LRF07.resize(ele_no);
  R1_LRU01_LRF07.resize(ele_no);
  R2_LRU01_LRF07.resize(ele_no);
  S0_LRU01_LRF07.resize(ele_no);
  S1_LRU01_LRF07.resize(ele_no);
  GA_LRU01_LRF07.resize(ele_no);

  LPS_LRU01_LRF07.resize(      ele_no);
  NBT_PSR_LRU01_LRF07.resize(  ele_no);
  INT_PSR_LRU01_LRF07.resize(  ele_no);
  E_INT_PSR_LRU01_LRF07.resize(ele_no);
  PSR_TAB_LRU01_LRF07.resize(  ele_no);
  NBT_PSI_LRU01_LRF07.resize(  ele_no);
  INT_PSI_LRU01_LRF07.resize(  ele_no);
  E_INT_PSI_LRU01_LRF07.resize(ele_no);
  PSI_TAB_LRU01_LRF07.resize(  ele_no);

  //LRU=2
  LSSF_LRU02.resize(ele_no);
  L_LRU02.resize(   ele_no);
  NJS_LRU02.resize( ele_no);

  //LRU=2, Case A
  D_LRU02_A.resize(   ele_no);
  AJ_LRU02_A.resize(  ele_no);
  AMUN_LRU02_A.resize(ele_no);
  GNO_LRU02_A.resize( ele_no);
  GG_LRU02_A.resize(  ele_no);

  //LRU=2, Case B
  NE_LRU02_B.resize(ele_no);

  ES_LRU02_B.resize(  ele_no);
  MUF_LRU02_B.resize( ele_no);
  D_LRU02_B.resize(   ele_no);
  AJ_LRU02_B.resize(  ele_no);
  AMUN_LRU02_B.resize(ele_no);
  GNO_LRU02_B.resize( ele_no);
  GG_LRU02_B.resize(  ele_no);
  GF_LRU02_B.resize(  ele_no);

  //LRU=2, Case C
  AJ_LRU02_C.resize(  ele_no);
  INT_LRU02_C.resize( ele_no);
  NE_LRU02_C.resize(  ele_no);
  AMUX_LRU02_C.resize(ele_no);
  AMUN_LRU02_C.resize(ele_no);
  AMUG_LRU02_C.resize(ele_no);
  AMUF_LRU02_C.resize(ele_no);
  ES_LRU02_C.resize(  ele_no);
  D_LRU02_C.resize(   ele_no);
  GX_LRU02_C.resize(  ele_no);
  GNO_LRU02_C.resize( ele_no);
  GG_LRU02_C.resize(  ele_no);
  GF_LRU02_C.resize(  ele_no);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF02MT151Parser::resize_matrix_vec_second(int i, int ele_no)
{
  //Common data
  EL[i].resize(  ele_no);
  EH[i].resize(  ele_no);
  LRU[i].resize( ele_no);
  LRF[i].resize( ele_no);
  NRO[i].resize( ele_no);
  NAPS[i].resize(ele_no);

  SPI[i].resize(ele_no);
  AP[i].resize( ele_no);
  NLS[i].resize(ele_no);

  //LRU=0
  NBT_AP_NRO[i].resize(  ele_no);
  INT_AP_NRO[i].resize(  ele_no);
  E_INT_AP_NRO[i].resize(ele_no);
  AP_TAB_NRO[i].resize(  ele_no);

  AWRI[i].resize(ele_no);

  //LRU=1, LRF=1, 2
  QX_LRU01_LRF01[i].resize(  ele_no);
  L_LRU01_LRF01[i].resize(   ele_no);
  LRX_LRU01_LRF01[i].resize( ele_no);
  NRS_LRU01_LRF01[i].resize( ele_no);
  ER_LRU01_LRF01[i].resize(  ele_no);
  AJ_LRU01_LRF01[i].resize(  ele_no);
  GT_LRU01_LRF01[i].resize(  ele_no);
  GN_LRU01_LRF01[i].resize(  ele_no);
  GG_LRU01_LRF01[i].resize(  ele_no);
  GF_LRU01_LRF01[i].resize(  ele_no);

  //LRU=1, LRF=3
  LAD_LRU01_LRF03[i].resize( ele_no);
  NLSC_LRU01_LRF03[i].resize(ele_no);
  APL_LRU01_LRF03[i].resize( ele_no);
  L_LRU01_LRF03[i].resize(   ele_no);
  NRS_LRU01_LRF03[i].resize( ele_no);
  ER_LRU01_LRF03[i].resize(  ele_no);
  AJ_LRU01_LRF03[i].resize(  ele_no);
  GN_LRU01_LRF03[i].resize(  ele_no);
  GG_LRU01_LRF03[i].resize(  ele_no);
  GFA_LRU01_LRF03[i].resize( ele_no);
  GFB_LRU01_LRF03[i].resize( ele_no);

  //LRU=1, LRF=4
  LI_LRU01_LRF04[i].resize(ele_no);
  NX_LRU01_LRF04[i].resize(ele_no);

  AT_LRU01_LRF04[i].resize(      ele_no);
  AF_LRU01_LRF04[i].resize(      ele_no);
  AC_LRU01_LRF04[i].resize(      ele_no);

  L_LRU01_LRF04[i].resize(       ele_no);
  NJS_LRU01_LRF04[i].resize(     ele_no);
  AJ_LRU01_LRF04[i].resize(      ele_no);
  NLJ_LRU01_LRF04[i].resize(     ele_no);
  DET_LRU01_LRF04[i].resize(     ele_no);
  DWT_LRU01_LRF04[i].resize(     ele_no);
  GRT_LRU01_LRF04[i].resize(     ele_no);
  GIT_LRU01_LRF04[i].resize(     ele_no);
  DEF_LRU01_LRF04[i].resize(     ele_no);
  DWF_LRU01_LRF04[i].resize(     ele_no);
  GRF_LRU01_LRF04[i].resize(     ele_no);
  GIF_LRU01_LRF04[i].resize(     ele_no);
  DEC_LRU01_LRF04[i].resize(     ele_no);
  DWC_LRU01_LRF04[i].resize(     ele_no);
  GRC_LRU01_LRF04[i].resize(     ele_no);
  GIC_LRU01_LRF04[i].resize(     ele_no);

  //LRU=1, LRF=7
  IFG_LRU01_LRF07[i].resize(ele_no);
  KRM_LRU01_LRF07[i].resize(ele_no);
  NJS_LRU01_LRF07[i].resize(ele_no);
  KRL_LRU01_LRF07[i].resize(ele_no);
  NPP_LRU01_LRF07[i].resize(ele_no);

  MA_LRU01_LRF07[i].resize(       ele_no);
  MB_LRU01_LRF07[i].resize(       ele_no);
  ZA_LRU01_LRF07[i].resize(       ele_no);
  ZB_LRU01_LRF07[i].resize(       ele_no);
  IA_LRU01_LRF07[i].resize(       ele_no);
  IB_LRU01_LRF07[i].resize(       ele_no);
  Q_LRU01_LRF07[i].resize(        ele_no);
  PNT_LRU01_LRF07[i].resize(      ele_no);
  SHF_LRU01_LRF07[i].resize(      ele_no);
  MT_LRU01_LRF07[i].resize(       ele_no);
  PA_LRU01_LRF07[i].resize(       ele_no);
  PB_LRU01_LRF07[i].resize(       ele_no);

  AJ_LRU01_LRF07[i].resize(       ele_no);
  PJ_LRU01_LRF07[i].resize(       ele_no);
  KBK_LRU01_LRF07[i].resize(      ele_no);
  KPS_LRU01_LRF07[i].resize(      ele_no);
  NCH_LRU01_LRF07[i].resize(      ele_no);
  PPI_LRU01_LRF07[i].resize(      ele_no);
  L_LRU01_LRF07[i].resize(        ele_no);
  SCH_LRU01_LRF07[i].resize(      ele_no);
  BND_LRU01_LRF07[i].resize(      ele_no);
  APE_LRU01_LRF07[i].resize(      ele_no);
  APT_LRU01_LRF07[i].resize(      ele_no);

  NRS_LRU01_LRF07[i].resize(      ele_no);
  NX_LRU01_LRF07[i].resize(       ele_no);
  ER_LRU01_LRF07[i].resize(       ele_no);
  GAM_LRU01_LRF07[i].resize(      ele_no);

  LCH_LRU01_LRF07[i].resize(      ele_no);
  LBK_LRU01_LRF07[i].resize(      ele_no);
  NBT_RBR_LRU01_LRF07[i].resize(  ele_no);
  INT_RBR_LRU01_LRF07[i].resize(  ele_no);
  E_INT_RBR_LRU01_LRF07[i].resize(ele_no);
  RBR_TAB_LRU01_LRF07[i].resize(  ele_no);
  NBT_RBI_LRU01_LRF07[i].resize(  ele_no);
  INT_RBI_LRU01_LRF07[i].resize(  ele_no);
  E_INT_RBI_LRU01_LRF07[i].resize(ele_no);
  RBI_TAB_LRU01_LRF07[i].resize(  ele_no);

  ED_LRU01_LRF07[i].resize(       ele_no);
  EU_LRU01_LRF07[i].resize(       ele_no);
  R0_LRU01_LRF07[i].resize(       ele_no);
  R1_LRU01_LRF07[i].resize(       ele_no);
  R2_LRU01_LRF07[i].resize(       ele_no);
  S0_LRU01_LRF07[i].resize(       ele_no);
  S1_LRU01_LRF07[i].resize(       ele_no);
  GA_LRU01_LRF07[i].resize(       ele_no);

  LPS_LRU01_LRF07[i].resize(      ele_no);
  NBT_PSR_LRU01_LRF07[i].resize(  ele_no);
  INT_PSR_LRU01_LRF07[i].resize(  ele_no);
  E_INT_PSR_LRU01_LRF07[i].resize(ele_no);
  PSR_TAB_LRU01_LRF07[i].resize(  ele_no);
  NBT_PSI_LRU01_LRF07[i].resize(  ele_no);
  INT_PSI_LRU01_LRF07[i].resize(  ele_no);
  E_INT_PSI_LRU01_LRF07[i].resize(ele_no);
  PSI_TAB_LRU01_LRF07[i].resize(  ele_no);

  //LRU=2
  LSSF_LRU02[i].resize(ele_no);
  L_LRU02[i].resize(   ele_no);
  NJS_LRU02[i].resize( ele_no);

  //LRU=2, Case A
  D_LRU02_A[i].resize(   ele_no);
  AJ_LRU02_A[i].resize(  ele_no);
  AMUN_LRU02_A[i].resize(ele_no);
  GNO_LRU02_A[i].resize( ele_no);
  GG_LRU02_A[i].resize(  ele_no);

  //LRU=2, Case B
  NE_LRU02_B[i].resize(ele_no);

  ES_LRU02_B[i].resize(  ele_no);
  MUF_LRU02_B[i].resize( ele_no);
  D_LRU02_B[i].resize(   ele_no);
  AJ_LRU02_B[i].resize(  ele_no);
  AMUN_LRU02_B[i].resize(ele_no);
  GNO_LRU02_B[i].resize( ele_no);
  GG_LRU02_B[i].resize(  ele_no);
  GF_LRU02_B[i].resize(  ele_no);

  //LRU=2, Case C
  AJ_LRU02_C[i].resize(  ele_no);
  INT_LRU02_C[i].resize( ele_no);
  NE_LRU02_C[i].resize(  ele_no);
  AMUX_LRU02_C[i].resize(ele_no);
  AMUN_LRU02_C[i].resize(ele_no);
  AMUG_LRU02_C[i].resize(ele_no);
  AMUF_LRU02_C[i].resize(ele_no);
  ES_LRU02_C[i].resize(  ele_no);
  D_LRU02_C[i].resize(   ele_no);
  GX_LRU02_C[i].resize(  ele_no);
  GNO_LRU02_C[i].resize( ele_no);
  GG_LRU02_C[i].resize(  ele_no);
  GF_LRU02_C[i].resize(  ele_no);
}
  
////////////////////////////////////////////////////////////////////////////////////////////////////

void MF02MT151Parser:: resize_matrix_vec_lru01_lrf04(int i, int j, int k, int k_max, int l_max)
{
  if( k==0 )
  {
    AJ_LRU01_LRF04[i][j].resize( k_max);
    NLJ_LRU01_LRF04[i][j].resize(k_max);

    DET_LRU01_LRF04[i][j].resize(k_max);
    DWT_LRU01_LRF04[i][j].resize(k_max);
    GRT_LRU01_LRF04[i][j].resize(k_max);
    GIT_LRU01_LRF04[i][j].resize(k_max);
    DEF_LRU01_LRF04[i][j].resize(k_max);
    DWF_LRU01_LRF04[i][j].resize(k_max);
    GRF_LRU01_LRF04[i][j].resize(k_max);
    GIF_LRU01_LRF04[i][j].resize(k_max);
    DEC_LRU01_LRF04[i][j].resize(k_max);
    DWC_LRU01_LRF04[i][j].resize(k_max);
    GRC_LRU01_LRF04[i][j].resize(k_max);
    GIC_LRU01_LRF04[i][j].resize(k_max);
  }

  AJ_LRU01_LRF04[i][j][k].resize( l_max);
  NLJ_LRU01_LRF04[i][j][k].resize(l_max);

  DET_LRU01_LRF04[i][j][k].resize(l_max);
  DWT_LRU01_LRF04[i][j][k].resize(l_max);
  GRT_LRU01_LRF04[i][j][k].resize(l_max);
  GIT_LRU01_LRF04[i][j][k].resize(l_max);
  DEF_LRU01_LRF04[i][j][k].resize(l_max);
  DWF_LRU01_LRF04[i][j][k].resize(l_max);
  GRF_LRU01_LRF04[i][j][k].resize(l_max);
  GIF_LRU01_LRF04[i][j][k].resize(l_max);
  DEC_LRU01_LRF04[i][j][k].resize(l_max);
  DWC_LRU01_LRF04[i][j][k].resize(l_max);
  GRC_LRU01_LRF04[i][j][k].resize(l_max);
  GIC_LRU01_LRF04[i][j][k].resize(l_max);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF02MT151Parser:: resize_matrix_vec_lru01_lrf07(int i, int j, int ele_no)
{
  AJ_LRU01_LRF07[i][j].resize( ele_no);
  PJ_LRU01_LRF07[i][j].resize( ele_no);
  KBK_LRU01_LRF07[i][j].resize(ele_no);
  KPS_LRU01_LRF07[i][j].resize(ele_no);
  NCH_LRU01_LRF07[i][j].resize(ele_no);

  PPI_LRU01_LRF07[i][j].resize(ele_no);
  L_LRU01_LRF07[i][j].resize(  ele_no);
  SCH_LRU01_LRF07[i][j].resize(ele_no);
  BND_LRU01_LRF07[i][j].resize(ele_no);
  APE_LRU01_LRF07[i][j].resize(ele_no);
  APT_LRU01_LRF07[i][j].resize(ele_no);

  NRS_LRU01_LRF07[i][j].resize(ele_no);
  NX_LRU01_LRF07[i][j].resize(ele_no);

  LCH_LRU01_LRF07[i][j].resize(ele_no);
  LBK_LRU01_LRF07[i][j].resize(ele_no);
  LPS_LRU01_LRF07[i][j].resize(ele_no);

  ER_LRU01_LRF07[i][j].resize( ele_no);
  GAM_LRU01_LRF07[i][j].resize(ele_no);

  NBT_RBR_LRU01_LRF07[i][j].resize(  ele_no);
  INT_RBR_LRU01_LRF07[i][j].resize(  ele_no);
  E_INT_RBR_LRU01_LRF07[i][j].resize(ele_no);
  RBR_TAB_LRU01_LRF07[i][j].resize(  ele_no);
  NBT_RBI_LRU01_LRF07[i][j].resize(  ele_no);
  INT_RBI_LRU01_LRF07[i][j].resize(  ele_no);
  E_INT_RBI_LRU01_LRF07[i][j].resize(ele_no);
  RBI_TAB_LRU01_LRF07[i][j].resize(  ele_no);
  ED_LRU01_LRF07[i][j].resize(       ele_no);
  EU_LRU01_LRF07[i][j].resize(       ele_no);
  R0_LRU01_LRF07[i][j].resize(       ele_no);
  R1_LRU01_LRF07[i][j].resize(       ele_no);
  R2_LRU01_LRF07[i][j].resize(       ele_no);
  S0_LRU01_LRF07[i][j].resize(       ele_no);
  S1_LRU01_LRF07[i][j].resize(       ele_no);
  GA_LRU01_LRF07[i][j].resize(       ele_no);
  NBT_PSR_LRU01_LRF07[i][j].resize(  ele_no);
  INT_PSR_LRU01_LRF07[i][j].resize(  ele_no);
  E_INT_PSR_LRU01_LRF07[i][j].resize(ele_no);
  PSR_TAB_LRU01_LRF07[i][j].resize(  ele_no);
  NBT_PSI_LRU01_LRF07[i][j].resize(  ele_no);
  INT_PSI_LRU01_LRF07[i][j].resize(  ele_no);
  E_INT_PSI_LRU01_LRF07[i][j].resize(ele_no);
  PSI_TAB_LRU01_LRF07[i][j].resize(  ele_no);

  ED_LRU01_LRF07[i][j].resize(ele_no);
  EU_LRU01_LRF07[i][j].resize(ele_no);
  R0_LRU01_LRF07[i][j].resize(ele_no);
  R1_LRU01_LRF07[i][j].resize(ele_no);
  R2_LRU01_LRF07[i][j].resize(ele_no);
  S0_LRU01_LRF07[i][j].resize(ele_no);
  S1_LRU01_LRF07[i][j].resize(ele_no);
  GA_LRU01_LRF07[i][j].resize(ele_no);
}
 
////////////////////////////////////////////////////////////////////////////////////////////////////

void MF02MT151Parser:: resize_matrix_vec_lru02_a(int i, int j, int ele_no)
{
  AWRI[i][j].resize(ele_no);
  L_LRU02[i][j].resize(   ele_no);
  NJS_LRU02[i][j].resize( ele_no);

  D_LRU02_A[i][j].resize(   ele_no);
  AJ_LRU02_A[i][j].resize(  ele_no);
  AMUN_LRU02_A[i][j].resize(ele_no);
  GNO_LRU02_A[i][j].resize( ele_no);
  GG_LRU02_A[i][j].resize(  ele_no);
}
 
////////////////////////////////////////////////////////////////////////////////////////////////////

void MF02MT151Parser:: resize_matrix_vec_lru02_b(int i, int j, int ele_no)
{
  AWRI[i][j].resize(ele_no);
  L_LRU02[i][j].resize(   ele_no);
  NJS_LRU02[i][j].resize( ele_no);

  MUF_LRU02_B[i][j].resize( ele_no);
  D_LRU02_B[i][j].resize(   ele_no);
  AJ_LRU02_B[i][j].resize(  ele_no);
  AMUN_LRU02_B[i][j].resize(ele_no);
  GNO_LRU02_B[i][j].resize( ele_no);
  GG_LRU02_B[i][j].resize(  ele_no);
  GF_LRU02_B[i][j].resize(  ele_no);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF02MT151Parser:: resize_matrix_vec_lru02_c(int i, int j, int k, int k_max, int l_max)
{
  if( k==0 )
  {
    AWRI[i][j].resize(k_max);
    L_LRU02[i][j].resize(   k_max);
    NJS_LRU02[i][j].resize( k_max);

    AJ_LRU02_C[i][j].resize(  k_max);
    INT_LRU02_C[i][j].resize( k_max);
    NE_LRU02_C[i][j].resize(  k_max);
    AMUX_LRU02_C[i][j].resize(k_max);
    AMUN_LRU02_C[i][j].resize(k_max);
    AMUG_LRU02_C[i][j].resize(k_max);
    AMUF_LRU02_C[i][j].resize(k_max);

    ES_LRU02_C[i][j].resize( k_max);
    D_LRU02_C[i][j].resize(  k_max);
    GX_LRU02_C[i][j].resize( k_max);
    GNO_LRU02_C[i][j].resize(k_max);
    GG_LRU02_C[i][j].resize( k_max);
    GF_LRU02_C[i][j].resize( k_max);
  }

  AJ_LRU02_C[i][j][k].resize(  l_max);
  INT_LRU02_C[i][j][k].resize( l_max);
  NE_LRU02_C[i][j][k].resize(  l_max);
  AMUX_LRU02_C[i][j][k].resize(l_max);
  AMUN_LRU02_C[i][j][k].resize(l_max);
  AMUG_LRU02_C[i][j][k].resize(l_max);
  AMUF_LRU02_C[i][j][k].resize(l_max);

  ES_LRU02_C[i][j][k].resize( l_max);
  D_LRU02_C[i][j][k].resize(  l_max);
  GX_LRU02_C[i][j][k].resize( l_max);
  GNO_LRU02_C[i][j][k].resize(l_max);
  GG_LRU02_C[i][j][k].resize( l_max);
  GF_LRU02_C[i][j][k].resize( l_max);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF02MT151Parser::init_multi_array_lru01_lrf07(int i, int j, int k_max)
{
  for(int k=0; k<k_max; k++)
  {
    ED_LRU01_LRF07[i][j][k] = -1.0;
    EU_LRU01_LRF07[i][j][k] = -1.0;
    R0_LRU01_LRF07[i][j][k] = -1.0;
    R1_LRU01_LRF07[i][j][k] = -1.0;
    R2_LRU01_LRF07[i][j][k] = -1.0;
    S0_LRU01_LRF07[i][j][k] = -1.0;
    S1_LRU01_LRF07[i][j][k] = -1.0;
    GA_LRU01_LRF07[i][j][k] = -1.0;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF02MT151Parser::clear()
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

  clr_vec.clear_vec_array2_real(EL);
  clr_vec.clear_vec_array2_real(EH);
  clr_vec.clear_vec_array2_real(SPI);
  clr_vec.clear_vec_array2_real(AP);

  clr_vec.clear_vec_array2_int(LRU);
  clr_vec.clear_vec_array2_int(LRF);
  clr_vec.clear_vec_array2_int(NRO);
  clr_vec.clear_vec_array2_int(NAPS);
  clr_vec.clear_vec_array2_int(NLS);

  clear_vector_array();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF02MT151Parser::clear_vector_array()
{
  VectorClearer clr_vec;

  clr_vec.clear_vec_array3_real(AWRI);

  //NRO>0
  clr_vec.clear_vec_array3_int(NBT_AP_NRO);
  clr_vec.clear_vec_array3_int(INT_AP_NRO);
  clr_vec.clear_vec_array3_real(E_INT_AP_NRO);
  clr_vec.clear_vec_array3_real(AP_TAB_NRO);

  //LRU=1, LRF=1, 2
  clr_vec.clear_vec_array3_real(QX_LRU01_LRF01);
  clr_vec.clear_vec_array3_int(L_LRU01_LRF01);
  clr_vec.clear_vec_array3_int(LRX_LRU01_LRF01);
  clr_vec.clear_vec_array3_int(NRS_LRU01_LRF01);

  clr_vec.clear_vec_array4_real(ER_LRU01_LRF01);
  clr_vec.clear_vec_array4_real(AJ_LRU01_LRF01);
  clr_vec.clear_vec_array4_real(GT_LRU01_LRF01);
  clr_vec.clear_vec_array4_real(GN_LRU01_LRF01);
  clr_vec.clear_vec_array4_real(GG_LRU01_LRF01);
  clr_vec.clear_vec_array4_real(GF_LRU01_LRF01);

  //LRU=1, LRF=3
  clr_vec.clear_vec_array2_int(LAD_LRU01_LRF03);
  clr_vec.clear_vec_array2_int(NLSC_LRU01_LRF03);

  clr_vec.clear_vec_array3_real(APL_LRU01_LRF03);
  clr_vec.clear_vec_array3_int(L_LRU01_LRF03);
  clr_vec.clear_vec_array3_int(NRS_LRU01_LRF03);

  clr_vec.clear_vec_array4_real(ER_LRU01_LRF03);
  clr_vec.clear_vec_array4_real(AJ_LRU01_LRF03);
  clr_vec.clear_vec_array4_real(GN_LRU01_LRF03);
  clr_vec.clear_vec_array4_real(GG_LRU01_LRF03);
  clr_vec.clear_vec_array4_real(GFA_LRU01_LRF03);
  clr_vec.clear_vec_array4_real(GFB_LRU01_LRF03);

  //LRU=1, LRF=4
  clr_vec.clear_vec_array2_int(LI_LRU01_LRF04);
  clr_vec.clear_vec_array2_int(NX_LRU01_LRF04);
  
  clr_vec.clear_vec_array3_real(AT_LRU01_LRF04);
  clr_vec.clear_vec_array3_real(AF_LRU01_LRF04);
  clr_vec.clear_vec_array3_real(AC_LRU01_LRF04);
  clr_vec.clear_vec_array3_int(L_LRU01_LRF04);
  clr_vec.clear_vec_array3_int(NJS_LRU01_LRF04);
  clr_vec.clear_vec_array4_real(AJ_LRU01_LRF04);
  clr_vec.clear_vec_array4_int(NLJ_LRU01_LRF04);

  clr_vec.clear_vec_array5_real(DET_LRU01_LRF04);
  clr_vec.clear_vec_array5_real(DWT_LRU01_LRF04);
  clr_vec.clear_vec_array5_real(GRT_LRU01_LRF04);
  clr_vec.clear_vec_array5_real(GIT_LRU01_LRF04);
  clr_vec.clear_vec_array5_real(DEF_LRU01_LRF04);
  clr_vec.clear_vec_array5_real(DWF_LRU01_LRF04);
  clr_vec.clear_vec_array5_real(GRF_LRU01_LRF04);
  clr_vec.clear_vec_array5_real(GIF_LRU01_LRF04);
  clr_vec.clear_vec_array5_real(DEC_LRU01_LRF04);
  clr_vec.clear_vec_array5_real(DWC_LRU01_LRF04);
  clr_vec.clear_vec_array5_real(GRC_LRU01_LRF04);
  clr_vec.clear_vec_array5_real(GIC_LRU01_LRF04);

  //LRU=1, LRF=7
  clr_vec.clear_vec_array2_int(IFG_LRU01_LRF07);
  clr_vec.clear_vec_array2_int(KRM_LRU01_LRF07);
  clr_vec.clear_vec_array2_int(NJS_LRU01_LRF07);
  clr_vec.clear_vec_array2_int(KRL_LRU01_LRF07);
  clr_vec.clear_vec_array2_int(NPP_LRU01_LRF07);

  clr_vec.clear_vec_array3_real(MA_LRU01_LRF07);
  clr_vec.clear_vec_array3_real(MB_LRU01_LRF07);
  clr_vec.clear_vec_array3_real(ZA_LRU01_LRF07);
  clr_vec.clear_vec_array3_real(ZB_LRU01_LRF07);
  clr_vec.clear_vec_array3_real(IA_LRU01_LRF07);
  clr_vec.clear_vec_array3_real(IB_LRU01_LRF07);
  clr_vec.clear_vec_array3_real(Q_LRU01_LRF07);
  clr_vec.clear_vec_array3_real(PNT_LRU01_LRF07);
  clr_vec.clear_vec_array3_real(SHF_LRU01_LRF07);
  clr_vec.clear_vec_array3_real(MT_LRU01_LRF07);
  clr_vec.clear_vec_array3_real(PA_LRU01_LRF07);
  clr_vec.clear_vec_array3_real(PB_LRU01_LRF07);

  clr_vec.clear_vec_array3_real(AJ_LRU01_LRF07);
  clr_vec.clear_vec_array3_real(PJ_LRU01_LRF07);
  clr_vec.clear_vec_array3_int(KBK_LRU01_LRF07);
  clr_vec.clear_vec_array3_int(KPS_LRU01_LRF07);
  clr_vec.clear_vec_array3_int(NCH_LRU01_LRF07);
  clr_vec.clear_vec_array4_real(PPI_LRU01_LRF07);
  clr_vec.clear_vec_array4_real(L_LRU01_LRF07);
  clr_vec.clear_vec_array4_real(SCH_LRU01_LRF07);
  clr_vec.clear_vec_array4_real(BND_LRU01_LRF07);
  clr_vec.clear_vec_array4_real(APE_LRU01_LRF07);
  clr_vec.clear_vec_array4_real(APT_LRU01_LRF07);

  clr_vec.clear_vec_array3_int(NRS_LRU01_LRF07);
  clr_vec.clear_vec_array3_int(NX_LRU01_LRF07);
  clr_vec.clear_vec_array4_real(ER_LRU01_LRF07);
  clr_vec.clear_vec_array5_real(GAM_LRU01_LRF07);

  clr_vec.clear_vec_array3_int(LCH_LRU01_LRF07);
  clr_vec.clear_vec_array3_int(LBK_LRU01_LRF07);
  clr_vec.clear_vec_array4_int(NBT_RBR_LRU01_LRF07);
  clr_vec.clear_vec_array4_int(INT_RBR_LRU01_LRF07);
  clr_vec.clear_vec_array4_real(E_INT_RBR_LRU01_LRF07);
  clr_vec.clear_vec_array4_real(RBR_TAB_LRU01_LRF07);
  clr_vec.clear_vec_array4_int(NBT_RBI_LRU01_LRF07);
  clr_vec.clear_vec_array4_int(INT_RBI_LRU01_LRF07);
  clr_vec.clear_vec_array4_real(E_INT_RBI_LRU01_LRF07);
  clr_vec.clear_vec_array4_real(RBI_TAB_LRU01_LRF07);

  clr_vec.clear_vec_array3_real(ED_LRU01_LRF07);
  clr_vec.clear_vec_array3_real(EU_LRU01_LRF07);
  clr_vec.clear_vec_array3_real(R0_LRU01_LRF07);
  clr_vec.clear_vec_array3_real(R1_LRU01_LRF07);
  clr_vec.clear_vec_array3_real(R2_LRU01_LRF07);
  clr_vec.clear_vec_array3_real(S0_LRU01_LRF07);
  clr_vec.clear_vec_array3_real(S1_LRU01_LRF07);
  clr_vec.clear_vec_array3_real(GA_LRU01_LRF07);

  clr_vec.clear_vec_array3_int(LPS_LRU01_LRF07);
  clr_vec.clear_vec_array4_int(NBT_PSR_LRU01_LRF07);
  clr_vec.clear_vec_array4_int(INT_PSR_LRU01_LRF07);
  clr_vec.clear_vec_array4_real(E_INT_PSR_LRU01_LRF07);
  clr_vec.clear_vec_array4_real(PSR_TAB_LRU01_LRF07);
  clr_vec.clear_vec_array4_int(NBT_PSI_LRU01_LRF07);
  clr_vec.clear_vec_array4_int(INT_PSI_LRU01_LRF07);
  clr_vec.clear_vec_array4_real(E_INT_PSI_LRU01_LRF07);
  clr_vec.clear_vec_array4_real(PSI_TAB_LRU01_LRF07);

  //LRU=2
  clr_vec.clear_vec_array2_int(LSSF_LRU02);
  clr_vec.clear_vec_array3_int(L_LRU02);
  clr_vec.clear_vec_array3_int(NJS_LRU02);

  //LRU=2, Case A
  clr_vec.clear_vec_array4_real(D_LRU02_A);
  clr_vec.clear_vec_array4_real(AJ_LRU02_A);
  clr_vec.clear_vec_array4_real(AMUN_LRU02_A);
  clr_vec.clear_vec_array4_real(GNO_LRU02_A);
  clr_vec.clear_vec_array4_real(GG_LRU02_A);

  //LRU=2, Case B
  clr_vec.clear_vec_array2_int(NE_LRU02_B);

  clr_vec.clear_vec_array3_real(ES_LRU02_B);

  clr_vec.clear_vec_array4_int(MUF_LRU02_B);
  clr_vec.clear_vec_array4_real(D_LRU02_B);
  clr_vec.clear_vec_array4_real(AJ_LRU02_B);
  clr_vec.clear_vec_array4_real(AMUN_LRU02_B);
  clr_vec.clear_vec_array4_real(GNO_LRU02_B);
  clr_vec.clear_vec_array4_real(GG_LRU02_B);
  clr_vec.clear_vec_array5_real(GF_LRU02_B);

  //LRU=2, Case C
  clr_vec.clear_vec_array4_real(AJ_LRU02_C);
  clr_vec.clear_vec_array4_int(INT_LRU02_C);
  clr_vec.clear_vec_array4_int(NE_LRU02_C);
  clr_vec.clear_vec_array4_real(AMUX_LRU02_C);
  clr_vec.clear_vec_array4_real(AMUN_LRU02_C);
  clr_vec.clear_vec_array4_real(AMUG_LRU02_C);
  clr_vec.clear_vec_array4_real(AMUF_LRU02_C);
  clr_vec.clear_vec_array5_real(ES_LRU02_C);
  clr_vec.clear_vec_array5_real(D_LRU02_C);
  clr_vec.clear_vec_array5_real(GX_LRU02_C);
  clr_vec.clear_vec_array5_real(GNO_LRU02_C);
  clr_vec.clear_vec_array5_real(GG_LRU02_C);
  clr_vec.clear_vec_array5_real(GF_LRU02_C);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF02MT151Parser::set_text(vector<string> text_data)
{
  clear();

  text = text_data;
  store_data();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> MF02MT151Parser::get_text()
{
  return text;
}

Integer MF02MT151Parser::get_mat_no()
{
  return mat_no;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Real                                             MF02MT151Parser::get_ZAR()
{
  return ZAR;
}

Real                                             MF02MT151Parser::get_AWR()
{
  return AWR;
}

Integer                                          MF02MT151Parser::get_NIS()
{
  return NIS;
}

vector<Real>                                     MF02MT151Parser::get_ZAI()
{
  return ZAI;
}

vector<Real>                                     MF02MT151Parser::get_ABN()
{
  return ABN;
}

vector<Integer>                                  MF02MT151Parser::get_LFW()
{
  return LFW;
}

vector<Integer>                                  MF02MT151Parser::get_NER()
{
  return NER;
}

vector<vector<Real> >                            MF02MT151Parser::get_EL()
{
  return EL;
}

vector<vector<Real> >                            MF02MT151Parser::get_EH()
{
  return EH;
}

vector<vector<Integer> >                         MF02MT151Parser::get_LRU()
{
  return LRU;
}

vector<vector<Integer> >                         MF02MT151Parser::get_LRF()
{
  return LRF;
}

vector<vector<Integer> >                         MF02MT151Parser::get_NRO()
{
  return NRO;
}

vector<vector<Integer> >                         MF02MT151Parser::get_NAPS()
{
  return NAPS;
}

vector<vector<Real> >                            MF02MT151Parser::get_SPI()
{
  return SPI;
}

vector<vector<Real> >                            MF02MT151Parser::get_AP()
{
  return AP;
}

vector<vector<Integer> >                         MF02MT151Parser::get_NLS()
{
  return NLS;
}

vector<vector<vector<Real> > >                   MF02MT151Parser::get_AWRI()
{
  return AWRI;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//For NRO>0
vector<vector<vector<Integer> > >                MF02MT151Parser::get_NBT_AP_NRO()
{
  return NBT_AP_NRO;
}

vector<vector<vector<Integer> > >                MF02MT151Parser::get_INT_AP_NRO()
{
  return INT_AP_NRO;
}

vector<vector<vector<Real> > >                   MF02MT151Parser::get_E_INT_AP_NRO()
{
  return E_INT_AP_NRO;
}

vector<vector<vector<Real> > >                   MF02MT151Parser::get_AP_TAB_NRO()
{
  return AP_TAB_NRO;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//LRU=1, LRF=1 or 2

//LRU=1, LRF=1
vector<vector<vector<Real> > >                   MF02MT151Parser::get_QX_LRU01_LRF01()
{
  return QX_LRU01_LRF01;
}

vector<vector<vector<Integer> > >                MF02MT151Parser::get_L_LRU01_LRF01()
{
  return L_LRU01_LRF01;
}

vector<vector<vector<Integer> > >                MF02MT151Parser::get_LRX_LRU01_LRF01()
{
  return LRX_LRU01_LRF01;
}

vector<vector<vector<Integer> > >                MF02MT151Parser::get_NRS_LRU01_LRF01()
{
  return NRS_LRU01_LRF01;
}

vector<vector<vector<vector<Real> > > >          MF02MT151Parser::get_ER_LRU01_LRF01()
{
  return ER_LRU01_LRF01;
}

vector<vector<vector<vector<Real> > > >          MF02MT151Parser::get_AJ_LRU01_LRF01()
{
  return AJ_LRU01_LRF01;
}

vector<vector<vector<vector<Real> > > >          MF02MT151Parser::get_GT_LRU01_LRF01()
{
  return GT_LRU01_LRF01;
}

vector<vector<vector<vector<Real> > > >          MF02MT151Parser::get_GN_LRU01_LRF01()
{
  return GN_LRU01_LRF01;
}

vector<vector<vector<vector<Real> > > >          MF02MT151Parser::get_GG_LRU01_LRF01()
{
  return GG_LRU01_LRF01;
}

vector<vector<vector<vector<Real> > > >          MF02MT151Parser::get_GF_LRU01_LRF01()
{
  return GF_LRU01_LRF01;
}

//LRU=1, LRF=2
vector<vector<vector<Real> > >                   MF02MT151Parser::get_QX_LRU01_LRF02()
{
  return QX_LRU01_LRF01;
}

vector<vector<vector<Integer> > >                MF02MT151Parser::get_L_LRU01_LRF02()
{
  return L_LRU01_LRF01;
}

vector<vector<vector<Integer> > >                MF02MT151Parser::get_LRX_LRU01_LRF02()
{
  return LRX_LRU01_LRF01;
}

vector<vector<vector<Integer> > >                MF02MT151Parser::get_NRS_LRU01_LRF02()
{
  return NRS_LRU01_LRF01;
}

vector<vector<vector<vector<Real> > > >          MF02MT151Parser::get_ER_LRU01_LRF02()
{
  return ER_LRU01_LRF01;
}

vector<vector<vector<vector<Real> > > >          MF02MT151Parser::get_AJ_LRU01_LRF02()
{
  return AJ_LRU01_LRF01;
}

vector<vector<vector<vector<Real> > > >          MF02MT151Parser::get_GT_LRU01_LRF02()
{
  return GT_LRU01_LRF01;
}

vector<vector<vector<vector<Real> > > >          MF02MT151Parser::get_GN_LRU01_LRF02()
{
  return GN_LRU01_LRF01;
}

vector<vector<vector<vector<Real> > > >          MF02MT151Parser::get_GG_LRU01_LRF02()
{
  return GG_LRU01_LRF01;
}

vector<vector<vector<vector<Real> > > >          MF02MT151Parser::get_GF_LRU01_LRF02()
{
  return GF_LRU01_LRF01;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//LRU=1, LRF=3
vector<vector<Integer> >                         MF02MT151Parser::get_LAD_LRU01_LRF03()
{
  return LAD_LRU01_LRF03;
}

vector<vector<Integer> >                         MF02MT151Parser::get_NLSC_LRU01_LRF03()
{
  return NLSC_LRU01_LRF03;
}

vector<vector<vector<Real> > >                   MF02MT151Parser::get_APL_LRU01_LRF03()
{
  return APL_LRU01_LRF03;
}

vector<vector<vector<Integer> > >                MF02MT151Parser::get_L_LRU01_LRF03()
{
  return L_LRU01_LRF03;
}

vector<vector<vector<Integer> > >                MF02MT151Parser::get_NRS_LRU01_LRF03()
{
  return NRS_LRU01_LRF03;
}

vector<vector<vector<vector<Real> > > >          MF02MT151Parser::get_ER_LRU01_LRF03()
{
  return ER_LRU01_LRF03;
}

vector<vector<vector<vector<Real> > > >          MF02MT151Parser::get_AJ_LRU01_LRF03()
{
  return AJ_LRU01_LRF03;
}

vector<vector<vector<vector<Real> > > >          MF02MT151Parser::get_GN_LRU01_LRF03()
{
  return GN_LRU01_LRF03;
}

vector<vector<vector<vector<Real> > > >          MF02MT151Parser::get_GG_LRU01_LRF03()
{
  return GG_LRU01_LRF03;
}

vector<vector<vector<vector<Real> > > >          MF02MT151Parser::get_GFA_LRU01_LRF03()
{
  return GFA_LRU01_LRF03;
}

vector<vector<vector<vector<Real> > > >          MF02MT151Parser::get_GFB_LRU01_LRF03()
{
  return GFB_LRU01_LRF03;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//LRU=1, LRF=4
vector<vector<Integer> >                         MF02MT151Parser::get_LI_LRU01_LRF04()
{
  return LI_LRU01_LRF04;
}

vector<vector<Integer> >                         MF02MT151Parser::get_NX_LRU01_LRF04()
{
  return NX_LRU01_LRF04;
}

vector<vector<vector<Real> > >                   MF02MT151Parser::get_AT_LRU01_LRF04()
{
  return AT_LRU01_LRF04;
}

vector<vector<vector<Real> > >                   MF02MT151Parser::get_AF_LRU01_LRF04()
{
  return AF_LRU01_LRF04;
}

vector<vector<vector<Real> > >                   MF02MT151Parser::get_AC_LRU01_LRF04()
{
  return AC_LRU01_LRF04;
}

vector<vector<vector<Integer> > >                MF02MT151Parser::get_L_LRU01_LRF04()
{
  return L_LRU01_LRF04;
}

vector<vector<vector<Integer> > >                MF02MT151Parser::get_NJS_LRU01_LRF04()
{
  return NJS_LRU01_LRF04;
}

vector<vector<vector<vector<Real> > > >          MF02MT151Parser::get_AJ_LRU01_LRF04()
{
  return AJ_LRU01_LRF04;
}

vector<vector<vector<vector<Integer> > > >       MF02MT151Parser::get_NLJ_LRU01_LRF04()
{
  return NLJ_LRU01_LRF04;
}

vector<vector<vector<vector<vector<Real> > > > > MF02MT151Parser::get_DET_LRU01_LRF04()
{
  return DET_LRU01_LRF04;
}

vector<vector<vector<vector<vector<Real> > > > > MF02MT151Parser::get_DWT_LRU01_LRF04()
{
  return DWT_LRU01_LRF04;
}

vector<vector<vector<vector<vector<Real> > > > > MF02MT151Parser::get_GRT_LRU01_LRF04()
{
  return GRT_LRU01_LRF04;
}

vector<vector<vector<vector<vector<Real> > > > > MF02MT151Parser::get_GIT_LRU01_LRF04()
{
  return GIT_LRU01_LRF04;
}

vector<vector<vector<vector<vector<Real> > > > > MF02MT151Parser::get_DEF_LRU01_LRF04()
{
  return DEF_LRU01_LRF04;
}

vector<vector<vector<vector<vector<Real> > > > > MF02MT151Parser::get_DWF_LRU01_LRF04()
{
  return DWF_LRU01_LRF04;
}

vector<vector<vector<vector<vector<Real> > > > > MF02MT151Parser::get_GRF_LRU01_LRF04()
{
  return GRF_LRU01_LRF04;
}

vector<vector<vector<vector<vector<Real> > > > > MF02MT151Parser::get_GIF_LRU01_LRF04()
{
  return GIF_LRU01_LRF04;
}

vector<vector<vector<vector<vector<Real> > > > > MF02MT151Parser::get_DEC_LRU01_LRF04()
{
  return DEC_LRU01_LRF04;
}

vector<vector<vector<vector<vector<Real> > > > > MF02MT151Parser::get_DWC_LRU01_LRF04()
{
  return DWC_LRU01_LRF04;
}

vector<vector<vector<vector<vector<Real> > > > > MF02MT151Parser::get_GRC_LRU01_LRF04()
{
  return GRC_LRU01_LRF04;
}

vector<vector<vector<vector<vector<Real> > > > > MF02MT151Parser::get_GIC_LRU01_LRF04()
{
  return GIC_LRU01_LRF04;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//LRU=1, LRF=7
vector<vector<Integer> >                         MF02MT151Parser::get_IFG_LRU01_LRF07()
{
  return IFG_LRU01_LRF07;
}

vector<vector<Integer> >                         MF02MT151Parser::get_KRM_LRU01_LRF07()
{
  return KRM_LRU01_LRF07;
}

vector<vector<Integer> >                         MF02MT151Parser::get_NJS_LRU01_LRF07()
{
  return NJS_LRU01_LRF07;
}

vector<vector<Integer> >                         MF02MT151Parser::get_KRL_LRU01_LRF07()
{
  return KRL_LRU01_LRF07;
}

vector<vector<Integer> >                         MF02MT151Parser::get_NPP_LRU01_LRF07()
{
  return NPP_LRU01_LRF07;
}

vector<vector<vector<Real> > >                   MF02MT151Parser::get_MA_LRU01_LRF07()
{
  return MA_LRU01_LRF07;
}

vector<vector<vector<Real> > >                   MF02MT151Parser::get_MB_LRU01_LRF07()
{
  return MB_LRU01_LRF07;
}

vector<vector<vector<Real> > >                   MF02MT151Parser::get_ZA_LRU01_LRF07()
{
  return ZA_LRU01_LRF07;
}

vector<vector<vector<Real> > >                   MF02MT151Parser::get_ZB_LRU01_LRF07()
{
  return ZB_LRU01_LRF07;
}

vector<vector<vector<Real> > >                   MF02MT151Parser::get_IA_LRU01_LRF07()
{
  return IA_LRU01_LRF07;
}

vector<vector<vector<Real> > >                   MF02MT151Parser::get_IB_LRU01_LRF07()
{
  return IB_LRU01_LRF07;
}

vector<vector<vector<Real> > >                   MF02MT151Parser::get_Q_LRU01_LRF07()
{
  return Q_LRU01_LRF07;
}

vector<vector<vector<Real> > >                   MF02MT151Parser::get_PNT_LRU01_LRF07()
{
  return PNT_LRU01_LRF07;
}

vector<vector<vector<Real> > >                   MF02MT151Parser::get_SHF_LRU01_LRF07()
{
  return SHF_LRU01_LRF07;
}

vector<vector<vector<Real> > >                   MF02MT151Parser::get_MT_LRU01_LRF07()
{
  return MT_LRU01_LRF07;
}

vector<vector<vector<Real> > >                   MF02MT151Parser::get_PA_LRU01_LRF07()
{
  return PA_LRU01_LRF07;
}

vector<vector<vector<Real> > >                   MF02MT151Parser::get_PB_LRU01_LRF07()
{
  return PB_LRU01_LRF07;
}

vector<vector<vector<Real> > >                   MF02MT151Parser::get_AJ_LRU01_LRF07()
{
  return AJ_LRU01_LRF07;
}

vector<vector<vector<Real> > >                   MF02MT151Parser::get_PJ_LRU01_LRF07()
{
  return PJ_LRU01_LRF07;
}

vector<vector<vector<Integer> > >                MF02MT151Parser::get_KBK_LRU01_LRF07()
{
  return KBK_LRU01_LRF07;
}

vector<vector<vector<Integer> > >                MF02MT151Parser::get_KPS_LRU01_LRF07()
{
  return KPS_LRU01_LRF07;
}

vector<vector<vector<Integer> > >                MF02MT151Parser::get_NCH_LRU01_LRF07()
{
  return NCH_LRU01_LRF07;
}

vector<vector<vector<vector<Real> > > >          MF02MT151Parser::get_PPI_LRU01_LRF07()
{
  return PPI_LRU01_LRF07;
}

vector<vector<vector<vector<Real> > > >          MF02MT151Parser::get_L_LRU01_LRF07()
{
  return L_LRU01_LRF07;
}

vector<vector<vector<vector<Real> > > >          MF02MT151Parser::get_SCH_LRU01_LRF07()
{
  return SCH_LRU01_LRF07;
}

vector<vector<vector<vector<Real> > > >          MF02MT151Parser::get_BND_LRU01_LRF07()
{
  return BND_LRU01_LRF07;
}

vector<vector<vector<vector<Real> > > >          MF02MT151Parser::get_APE_LRU01_LRF07()
{
  return APE_LRU01_LRF07;
}

vector<vector<vector<vector<Real> > > >          MF02MT151Parser::get_APT_LRU01_LRF07()
{
  return APT_LRU01_LRF07;
}

vector<vector<vector<Integer> > >                MF02MT151Parser::get_NRS_LRU01_LRF07()
{
  return NRS_LRU01_LRF07;
}

vector<vector<vector<Integer> > >                MF02MT151Parser::get_NX_LRU01_LRF07()
{
  return NX_LRU01_LRF07;
}

vector<vector<vector<vector<Real> > > > MF02MT151Parser::get_ER_LRU01_LRF07()
{
  return ER_LRU01_LRF07;
}

vector<vector<vector<vector<vector<Real> > > > > MF02MT151Parser::get_GAM_LRU01_LRF07()
{
  return GAM_LRU01_LRF07;
}

vector<vector<vector<Integer> > >                MF02MT151Parser::get_LCH_LRU01_LRF07()
{
  return LCH_LRU01_LRF07;
}

vector<vector<vector<Integer> > >                MF02MT151Parser::get_LBK_LRU01_LRF07()
{
  return LBK_LRU01_LRF07;
}

vector<vector<vector<vector<Integer> > > >       MF02MT151Parser::get_NBT_RBR_LRU01_LRF07()
{
  return NBT_RBR_LRU01_LRF07;
}

vector<vector<vector<vector<Integer> > > >       MF02MT151Parser::get_INT_RBR_LRU01_LRF07()
{
  return INT_RBR_LRU01_LRF07;
}

vector<vector<vector<vector<Real> > > >          MF02MT151Parser::get_E_INT_RBR_LRU01_LRF07()
{
  return E_INT_RBR_LRU01_LRF07;
}

vector<vector<vector<vector<Real> > > >          MF02MT151Parser::get_RBR_TAB_LRU01_LRF07()
{
  return RBR_TAB_LRU01_LRF07;
}

vector<vector<vector<vector<Integer> > > >       MF02MT151Parser::get_NBT_RBI_LRU01_LRF07()
{
  return NBT_RBI_LRU01_LRF07;
}

vector<vector<vector<vector<Integer> > > >       MF02MT151Parser::get_INT_RBI_LRU01_LRF07()
{
  return INT_RBI_LRU01_LRF07;
}

vector<vector<vector<vector<Real> > > >          MF02MT151Parser::get_E_INT_RBI_LRU01_LRF07()
{
  return E_INT_RBI_LRU01_LRF07;
}

vector<vector<vector<vector<Real> > > >          MF02MT151Parser::get_RBI_TAB_LRU01_LRF07()
{
  return RBI_TAB_LRU01_LRF07;
}

vector<vector<vector<Real> > >                   MF02MT151Parser::get_ED_LRU01_LRF07()
{
  return ED_LRU01_LRF07;
}

vector<vector<vector<Real> > >                   MF02MT151Parser::get_EU_LRU01_LRF07()
{
  return EU_LRU01_LRF07;
}

vector<vector<vector<Real> > >                   MF02MT151Parser::get_R0_LRU01_LRF07()
{
  return R0_LRU01_LRF07;
}

vector<vector<vector<Real> > >                   MF02MT151Parser::get_R1_LRU01_LRF07()
{
  return R1_LRU01_LRF07;
}

vector<vector<vector<Real> > >                   MF02MT151Parser::get_R2_LRU01_LRF07()
{
  return R2_LRU01_LRF07;
}

vector<vector<vector<Real> > >                   MF02MT151Parser::get_S0_LRU01_LRF07()
{
  return S0_LRU01_LRF07;
}

vector<vector<vector<Real> > >                   MF02MT151Parser::get_S1_LRU01_LRF07()
{
  return S1_LRU01_LRF07;
}

vector<vector<vector<Real> > >                   MF02MT151Parser::get_GA_LRU01_LRF07()
{
  return GA_LRU01_LRF07;
}

vector<vector<vector<Integer> > >                MF02MT151Parser::get_LPS_LRU01_LRF07()
{
  return LPS_LRU01_LRF07;
}

vector<vector<vector<vector<Integer> > > >       MF02MT151Parser::get_NBT_PSR_LRU01_LRF07()
{
  return NBT_PSR_LRU01_LRF07;
}

vector<vector<vector<vector<Integer> > > >       MF02MT151Parser::get_INT_PSR_LRU01_LRF07()
{
  return INT_PSR_LRU01_LRF07;
}

vector<vector<vector<vector<Real> > > >          MF02MT151Parser::get_E_INT_PSR_LRU01_LRF07()
{
  return E_INT_PSR_LRU01_LRF07;
}

vector<vector<vector<vector<Real> > > >          MF02MT151Parser::get_PSR_TAB_LRU01_LRF07()
{
  return PSR_TAB_LRU01_LRF07;
}

vector<vector<vector<vector<Integer> > > >       MF02MT151Parser::get_NBT_PSI_LRU01_LRF07()
{
  return NBT_PSI_LRU01_LRF07;
}

vector<vector<vector<vector<Integer> > > >       MF02MT151Parser::get_INT_PSI_LRU01_LRF07()
{
  return INT_PSI_LRU01_LRF07;
}

vector<vector<vector<vector<Real> > > >          MF02MT151Parser::get_E_INT_PSI_LRU01_LRF07()
{
  return E_INT_PSI_LRU01_LRF07;
}

vector<vector<vector<vector<Real> > > >          MF02MT151Parser::get_PSI_TAB_LRU01_LRF07()
{
  return PSI_TAB_LRU01_LRF07;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//LRU=2
vector<vector<Integer> >                         MF02MT151Parser::get_LSSF_LRU02()
{
  return LSSF_LRU02;
}

vector<vector<vector<Integer> > >                MF02MT151Parser::get_L_LRU02()
{
  return L_LRU02;
}

vector<vector<vector<Integer> > >                MF02MT151Parser::get_NJS_LRU02()
{
  return NJS_LRU02;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//LRU=2, Case A
vector<vector<vector<vector<Real> > > >          MF02MT151Parser::get_D_LRU02_A()
{
  return D_LRU02_A;
}

vector<vector<vector<vector<Real> > > >          MF02MT151Parser::get_AJ_LRU02_A()
{
  return AJ_LRU02_A;
}

vector<vector<vector<vector<Real> > > >          MF02MT151Parser::get_AMUN_LRU02_A()
{
  return AMUN_LRU02_A;
}

vector<vector<vector<vector<Real> > > >          MF02MT151Parser::get_GNO_LRU02_A()
{
  return GNO_LRU02_A;
}

vector<vector<vector<vector<Real> > > >          MF02MT151Parser::get_GG_LRU02_A()
{
  return GG_LRU02_A;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//LRU=2, Case B
vector<vector<Integer> >                         MF02MT151Parser::get_NE_LRU02_B()
{
  return NE_LRU02_B;
}

vector<vector<vector<Real> > >                   MF02MT151Parser::get_ES_LRU02_B()
{
  return ES_LRU02_B;
}

vector<vector<vector<vector<Integer> > > >       MF02MT151Parser::get_MUF_LRU02_B()
{
  return MUF_LRU02_B;
}

vector<vector<vector<vector<Real> > > >          MF02MT151Parser::get_D_LRU02_B()
{
  return D_LRU02_B;
}

vector<vector<vector<vector<Real> > > >          MF02MT151Parser::get_AJ_LRU02_B()
{
  return AJ_LRU02_B;
}

vector<vector<vector<vector<Real> > > >          MF02MT151Parser::get_AMUN_LRU02_B()
{
  return AMUN_LRU02_B;
}

vector<vector<vector<vector<Real> > > >          MF02MT151Parser::get_GNO_LRU02_B()
{
  return GNO_LRU02_B;
}

vector<vector<vector<vector<Real> > > >          MF02MT151Parser::get_GG_LRU02_B()
{
  return GG_LRU02_B;
}

vector<vector<vector<vector<vector<Real> > > > > MF02MT151Parser::get_GF_LRU02_B()
{
  return GF_LRU02_B;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//LRU=2, Case C
vector<vector<vector<vector<Real> > > >          MF02MT151Parser::get_AJ_LRU02_C()
{
  return AJ_LRU02_C;
}

vector<vector<vector<vector<Integer> > > >       MF02MT151Parser::get_INT_LRU02_C()
{
  return INT_LRU02_C;
}

vector<vector<vector<vector<Integer> > > >       MF02MT151Parser::get_NE_LRU02_C()
{
  return NE_LRU02_C;
}

vector<vector<vector<vector<Real> > > >          MF02MT151Parser::get_AMUX_LRU02_C()
{
  return AMUX_LRU02_C;
}

vector<vector<vector<vector<Real> > > >          MF02MT151Parser::get_AMUN_LRU02_C()
{
  return AMUN_LRU02_C;
}

vector<vector<vector<vector<Real> > > >          MF02MT151Parser::get_AMUG_LRU02_C()
{
  return AMUG_LRU02_C;
}

vector<vector<vector<vector<Real> > > >          MF02MT151Parser::get_AMUF_LRU02_C()
{
  return AMUF_LRU02_C;
}

vector<vector<vector<vector<vector<Real> > > > > MF02MT151Parser::get_ES_LRU02_C()
{
  return ES_LRU02_C;
}

vector<vector<vector<vector<vector<Real> > > > > MF02MT151Parser::get_D_LRU02_C()
{
  return D_LRU02_C;
}

vector<vector<vector<vector<vector<Real> > > > > MF02MT151Parser::get_GX_LRU02_C()
{
  return GX_LRU02_C;
}

vector<vector<vector<vector<vector<Real> > > > > MF02MT151Parser::get_GNO_LRU02_C()
{
  return GNO_LRU02_C;
}

vector<vector<vector<vector<vector<Real> > > > > MF02MT151Parser::get_GG_LRU02_C()
{
  return GG_LRU02_C;
}

vector<vector<vector<vector<vector<Real> > > > > MF02MT151Parser::get_GF_LRU02_C()
{
  return GF_LRU02_C;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void MF02MT151Parser::set_mat_no(Integer& int_data)
{
  mat_no = int_data;
}

void MF02MT151Parser::set_ZAR(Real& real_data)
{
  ZAR = real_data;
}

void MF02MT151Parser::set_AWR(Real& real_data)
{
  AWR = real_data;
}

void MF02MT151Parser::set_NIS(Integer& int_data)
{
  NIS = int_data;
}

void MF02MT151Parser::set_ZAI(vector<Real>& real_vec)
{
  ZAI = real_vec;
}

void MF02MT151Parser::set_ABN(vector<Real>& real_vec)
{
  ABN = real_vec;
}

void MF02MT151Parser::set_LFW(vector<Integer>& int_vec)
{
  LFW = int_vec;
}

void MF02MT151Parser::set_NER(vector<Integer>& int_vec)
{
  NER = int_vec;
}

void MF02MT151Parser::set_EL(vector<vector<Real> >& real_vec)
{
  EL = real_vec;
}

void MF02MT151Parser::set_EH(vector<vector<Real> >& real_vec)
{
  EH = real_vec;
}

void MF02MT151Parser::set_LRU(vector<vector<Integer> >& int_vec)
{
  LRU = int_vec;
}

void MF02MT151Parser::set_LRF(vector<vector<Integer> >& int_vec)
{
  LRF = int_vec;
}

void MF02MT151Parser::set_NRO(vector<vector<Integer> >& int_vec)
{
  NRO = int_vec;
}

void MF02MT151Parser::set_NAPS(vector<vector<Integer> >& int_vec)
{
  NAPS = int_vec;
}


void MF02MT151Parser::set_SPI(vector<vector<Real> >& real_vec)
{
  SPI = real_vec;
}

void MF02MT151Parser::set_AP(vector<vector<Real> >& real_vec)
{
  AP = real_vec;
}

void MF02MT151Parser::set_NLS(vector<vector<Integer> >& int_vec)
{
  NLS = int_vec;
}

void MF02MT151Parser::set_AWRI(vector<vector<vector<Real> > >& real_vec)
{
  AWRI = real_vec;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//NRO>0
void MF02MT151Parser::set_NBT_AP_NRO(vector<vector<vector<Integer> > >& int_vec)
{
  NBT_AP_NRO = int_vec;
}

void MF02MT151Parser::set_INT_AP_NRO(vector<vector<vector<Integer> > >& int_vec)
{
  INT_AP_NRO = int_vec;
}

void MF02MT151Parser::set_E_INT_AP_NRO(vector<vector<vector<Real> > >& real_vec)
{
  E_INT_AP_NRO = real_vec;
}

void MF02MT151Parser::set_AP_TAB_NRO(vector<vector<vector<Real> > >& real_vec)
{
  AP_TAB_NRO = real_vec;
}


////////////////////////////////////////////////////////////////////////////////////////////////////

//LRU=1, LRF=1 or 2
void MF02MT151Parser::set_QX_LRU01_LRF01(vector<vector<vector<Real> > >& real_vec)
{
  QX_LRU01_LRF01 = real_vec;
}

void MF02MT151Parser::set_L_LRU01_LRF01(vector<vector<vector<Integer> > >& int_vec)
{
  L_LRU01_LRF01 = int_vec;
}

void MF02MT151Parser::set_LRX_LRU01_LRF01(vector<vector<vector<Integer> > >& int_vec)
{
  LRX_LRU01_LRF01 = int_vec;
}

void MF02MT151Parser::set_NRS_LRU01_LRF01(vector<vector<vector<Integer> > >& int_vec)
{
  NRS_LRU01_LRF01 = int_vec;
}

void MF02MT151Parser::set_ER_LRU01_LRF01(vector<vector<vector<vector<Real> > > >& real_vec)
{
  ER_LRU01_LRF01 = real_vec;
}

void MF02MT151Parser::set_AJ_LRU01_LRF01(vector<vector<vector<vector<Real> > > >& real_vec)
{
  AJ_LRU01_LRF01 = real_vec;
}

void MF02MT151Parser::set_GT_LRU01_LRF01(vector<vector<vector<vector<Real> > > >& real_vec)
{
  GT_LRU01_LRF01 = real_vec;
}

void MF02MT151Parser::set_GN_LRU01_LRF01(vector<vector<vector<vector<Real> > > >& real_vec)
{
  GN_LRU01_LRF01 = real_vec;
}

void MF02MT151Parser::set_GG_LRU01_LRF01(vector<vector<vector<vector<Real> > > >& real_vec)
{
  GG_LRU01_LRF01 = real_vec;
}

void MF02MT151Parser::set_GF_LRU01_LRF01(vector<vector<vector<vector<Real> > > >& real_vec)
{
  GF_LRU01_LRF01 = real_vec;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//LRU=1, LRF=3
void MF02MT151Parser::set_LAD_LRU01_LRF03(vector<vector<Integer> >& int_vec)
{
  LAD_LRU01_LRF03 = int_vec;
}

void MF02MT151Parser::set_NLSC_LRU01_LRF03(vector<vector<Integer> >& int_vec)
{
  NLSC_LRU01_LRF03 = int_vec;
}

void MF02MT151Parser::set_APL_LRU01_LRF03(vector<vector<vector<Real> > >& real_vec)
{
  APL_LRU01_LRF03 = real_vec;
}

void MF02MT151Parser::set_L_LRU01_LRF03(vector<vector<vector<Integer> > >& int_vec)
{
  L_LRU01_LRF03 = int_vec;
}

void MF02MT151Parser::set_NRS_LRU01_LRF03(vector<vector<vector<Integer> > >& int_vec)
{
  NRS_LRU01_LRF03 = int_vec;
}

void MF02MT151Parser::set_ER_LRU01_LRF03(vector<vector<vector<vector<Real> > > >& real_vec)
{
  ER_LRU01_LRF03 = real_vec;
}

void MF02MT151Parser::set_AJ_LRU01_LRF03(vector<vector<vector<vector<Real> > > >& real_vec)
{
  AJ_LRU01_LRF03 = real_vec;
}

void MF02MT151Parser::set_GN_LRU01_LRF03(vector<vector<vector<vector<Real> > > >& real_vec)
{
  GN_LRU01_LRF03 = real_vec;
}

void MF02MT151Parser::set_GG_LRU01_LRF03(vector<vector<vector<vector<Real> > > >& real_vec)
{
  GG_LRU01_LRF03 = real_vec;
}

void MF02MT151Parser::set_GFA_LRU01_LRF03(vector<vector<vector<vector<Real> > > >& real_vec)
{
  GFA_LRU01_LRF03 = real_vec;
}

void MF02MT151Parser::set_GFB_LRU01_LRF03(vector<vector<vector<vector<Real> > > >& real_vec)
{
  GFB_LRU01_LRF03 = real_vec;
}


////////////////////////////////////////////////////////////////////////////////////////////////////

//LRU=1, LRF=4
void MF02MT151Parser::set_LI_LRU01_LRF04(vector<vector<Integer> >& int_vec)
{
  LI_LRU01_LRF04 = int_vec;
}

void MF02MT151Parser::set_NX_LRU01_LRF04(vector<vector<Integer> >& int_vec)
{
  NX_LRU01_LRF04 = int_vec;
}

void MF02MT151Parser::set_AT_LRU01_LRF04(vector<vector<vector<Real> > >& real_vec)
{
  AT_LRU01_LRF04 = real_vec;
}

void MF02MT151Parser::set_AF_LRU01_LRF04(vector<vector<vector<Real> > >& real_vec)
{
  AF_LRU01_LRF04 = real_vec;
}

void MF02MT151Parser::set_AC_LRU01_LRF04(vector<vector<vector<Real> > >& real_vec)
{
  AC_LRU01_LRF04 = real_vec;
}

void MF02MT151Parser::set_L_LRU01_LRF04(vector<vector<vector<Integer> > >& int_vec)
{
  L_LRU01_LRF04 = int_vec;
}

void MF02MT151Parser::set_NJS_LRU01_LRF04(vector<vector<vector<Integer> > >& int_vec)
{
  NJS_LRU01_LRF04 = int_vec;
}

void MF02MT151Parser::set_AJ_LRU01_LRF04(vector<vector<vector<vector<Real> > > >& real_vec)
{
  AJ_LRU01_LRF04 = real_vec;
}

void MF02MT151Parser::set_NLJ_LRU01_LRF04(vector<vector<vector<vector<Integer> > > >& int_vec)
{
  NLJ_LRU01_LRF04 = int_vec;
}


void MF02MT151Parser::set_DET_LRU01_LRF04(vector<vector<vector<vector<vector<Real> > > > >& real_vec)
{
  DET_LRU01_LRF04 = real_vec;
}

void MF02MT151Parser::set_DWT_LRU01_LRF04(vector<vector<vector<vector<vector<Real> > > > >& real_vec)
{
  DWT_LRU01_LRF04 = real_vec;
}

void MF02MT151Parser::set_GRT_LRU01_LRF04(vector<vector<vector<vector<vector<Real> > > > >& real_vec)
{
  GRT_LRU01_LRF04 = real_vec;
}

void MF02MT151Parser::set_GIT_LRU01_LRF04(vector<vector<vector<vector<vector<Real> > > > >& real_vec)
{
  GIT_LRU01_LRF04 = real_vec;
}

void MF02MT151Parser::set_DEF_LRU01_LRF04(vector<vector<vector<vector<vector<Real> > > > >& real_vec)
{
  DEF_LRU01_LRF04 = real_vec;
}

void MF02MT151Parser::set_DWF_LRU01_LRF04(vector<vector<vector<vector<vector<Real> > > > >& real_vec)
{
  DWF_LRU01_LRF04 = real_vec;
}

void MF02MT151Parser::set_GRF_LRU01_LRF04(vector<vector<vector<vector<vector<Real> > > > >& real_vec)
{
  GRF_LRU01_LRF04 = real_vec;
}

void MF02MT151Parser::set_GIF_LRU01_LRF04(vector<vector<vector<vector<vector<Real> > > > >& real_vec)
{
  GIF_LRU01_LRF04 = real_vec;
}

void MF02MT151Parser::set_DEC_LRU01_LRF04(vector<vector<vector<vector<vector<Real> > > > >& real_vec)
{
  DEC_LRU01_LRF04 = real_vec;
}

void MF02MT151Parser::set_DWC_LRU01_LRF04(vector<vector<vector<vector<vector<Real> > > > >& real_vec)
{
  DWC_LRU01_LRF04 = real_vec;
}

void MF02MT151Parser::set_GRC_LRU01_LRF04(vector<vector<vector<vector<vector<Real> > > > >& real_vec)
{
  GRC_LRU01_LRF04 = real_vec;
}

void MF02MT151Parser::set_GIC_LRU01_LRF04(vector<vector<vector<vector<vector<Real> > > > >& real_vec)
{
  GIC_LRU01_LRF04 = real_vec;
}


////////////////////////////////////////////////////////////////////////////////////////////////////

//LRU=1, LRF=7
void MF02MT151Parser::set_IFG_LRU01_LRF07(vector<vector<Integer> >& int_vec)
{
  IFG_LRU01_LRF07 = int_vec;
}

void MF02MT151Parser::set_KRM_LRU01_LRF07(vector<vector<Integer> >& int_vec)
{
  KRM_LRU01_LRF07 = int_vec;
}

void MF02MT151Parser::set_NJS_LRU01_LRF07(vector<vector<Integer> >& int_vec)
{
  NJS_LRU01_LRF07 = int_vec;
}

void MF02MT151Parser::set_KRL_LRU01_LRF07(vector<vector<Integer> >& int_vec)
{
  KRL_LRU01_LRF07 = int_vec;
}

void MF02MT151Parser::set_NPP_LRU01_LRF07(vector<vector<Integer> >& int_vec)
{
  NPP_LRU01_LRF07 = int_vec;
}

void MF02MT151Parser::set_MA_LRU01_LRF07(vector<vector<vector<Real> > >& real_vec)
{
  MA_LRU01_LRF07 = real_vec;
}

void MF02MT151Parser::set_MB_LRU01_LRF07(vector<vector<vector<Real> > >& real_vec)
{
  MB_LRU01_LRF07 = real_vec;
}

void MF02MT151Parser::set_ZA_LRU01_LRF07(vector<vector<vector<Real> > >& real_vec)
{
  ZA_LRU01_LRF07 = real_vec;
}

void MF02MT151Parser::set_ZB_LRU01_LRF07(vector<vector<vector<Real> > >& real_vec)
{
  ZB_LRU01_LRF07 = real_vec;
}

void MF02MT151Parser::set_IA_LRU01_LRF07(vector<vector<vector<Real> > >& real_vec)
{
  IA_LRU01_LRF07 = real_vec;
}

void MF02MT151Parser::set_IB_LRU01_LRF07(vector<vector<vector<Real> > >& real_vec)
{
  IB_LRU01_LRF07 = real_vec;
}

void MF02MT151Parser::set_Q_LRU01_LRF07(vector<vector<vector<Real> > >& real_vec)
{
  Q_LRU01_LRF07 = real_vec;
}

void MF02MT151Parser::set_PNT_LRU01_LRF07(vector<vector<vector<Real> > >& real_vec)
{
  PNT_LRU01_LRF07 = real_vec;
}

void MF02MT151Parser::set_SHF_LRU01_LRF07(vector<vector<vector<Real> > >& real_vec)
{
  SHF_LRU01_LRF07 = real_vec;
}

void MF02MT151Parser::set_MT_LRU01_LRF07(vector<vector<vector<Real> > >& real_vec)
{
  MT_LRU01_LRF07 = real_vec;
}

void MF02MT151Parser::set_PA_LRU01_LRF07(vector<vector<vector<Real> > >& real_vec)
{
  PA_LRU01_LRF07 = real_vec;
}

void MF02MT151Parser::set_PB_LRU01_LRF07(vector<vector<vector<Real> > >& real_vec)
{
  PB_LRU01_LRF07 = real_vec;
}


void MF02MT151Parser::set_AJ_LRU01_LRF07(vector<vector<vector<Real> > >& real_vec)
{
  AJ_LRU01_LRF07 = real_vec;
}

void MF02MT151Parser::set_PJ_LRU01_LRF07(vector<vector<vector<Real> > >& real_vec)
{
  PJ_LRU01_LRF07 = real_vec;
}

void MF02MT151Parser::set_KBK_LRU01_LRF07(vector<vector<vector<Integer> > >& int_vec)
{
  KBK_LRU01_LRF07 = int_vec;
}

void MF02MT151Parser::set_KPS_LRU01_LRF07(vector<vector<vector<Integer> > >& int_vec)
{
  KPS_LRU01_LRF07 = int_vec;
}

void MF02MT151Parser::set_NCH_LRU01_LRF07(vector<vector<vector<Integer> > >& int_vec)
{
  NCH_LRU01_LRF07 = int_vec;
}

void MF02MT151Parser::set_PPI_LRU01_LRF07(vector<vector<vector<vector<Real> > > >& real_vec)
{
  PPI_LRU01_LRF07 = real_vec;
}

void MF02MT151Parser::set_L_LRU01_LRF07(vector<vector<vector<vector<Real> > > >& real_vec)
{
  L_LRU01_LRF07 = real_vec;
}

void MF02MT151Parser::set_SCH_LRU01_LRF07(vector<vector<vector<vector<Real> > > >& real_vec)
{
  SCH_LRU01_LRF07 = real_vec;
}

void MF02MT151Parser::set_BND_LRU01_LRF07(vector<vector<vector<vector<Real> > > >& real_vec)
{
  BND_LRU01_LRF07 = real_vec;
}

void MF02MT151Parser::set_APE_LRU01_LRF07(vector<vector<vector<vector<Real> > > >& real_vec)
{
  APE_LRU01_LRF07 = real_vec;
}

void MF02MT151Parser::set_APT_LRU01_LRF07(vector<vector<vector<vector<Real> > > >& real_vec)
{
  APT_LRU01_LRF07 = real_vec;
}


void MF02MT151Parser::set_NRS_LRU01_LRF07(vector<vector<vector<Integer> > >& int_vec)
{
  NRS_LRU01_LRF07 = int_vec;
}

void MF02MT151Parser::set_NX_LRU01_LRF07(vector<vector<vector<Integer> > >& int_vec)
{
  NX_LRU01_LRF07 = int_vec;
}

void MF02MT151Parser::set_ER_LRU01_LRF07(vector<vector<vector<vector<Real> > > >& real_vec)
{
  ER_LRU01_LRF07 = real_vec;
}

void MF02MT151Parser::set_GAM_LRU01_LRF07(vector<vector<vector<vector<vector<Real> > > > >& real_vec)
{
  GAM_LRU01_LRF07 = real_vec;
}


void MF02MT151Parser::set_LCH_LRU01_LRF07(vector<vector<vector<Integer> > >& int_vec)
{
  LCH_LRU01_LRF07 = int_vec;
}

void MF02MT151Parser::set_LBK_LRU01_LRF07(vector<vector<vector<Integer> > >& int_vec)
{
  LBK_LRU01_LRF07 = int_vec;
}

void MF02MT151Parser::set_NBT_RBR_LRU01_LRF07(vector<vector<vector<vector<Integer> > > >& int_vec)
{
  NBT_RBR_LRU01_LRF07 = int_vec;
}

void MF02MT151Parser::set_INT_RBR_LRU01_LRF07(vector<vector<vector<vector<Integer> > > >& int_vec)
{
  INT_RBR_LRU01_LRF07 = int_vec;
}

void MF02MT151Parser::set_E_INT_RBR_LRU01_LRF07(vector<vector<vector<vector<Real> > > >& real_vec)
{
  E_INT_RBR_LRU01_LRF07 = real_vec;
}

void MF02MT151Parser::set_RBR_TAB_LRU01_LRF07(vector<vector<vector<vector<Real> > > >& real_vec)
{
  RBR_TAB_LRU01_LRF07 = real_vec;
}

void MF02MT151Parser::set_NBT_RBI_LRU01_LRF07(vector<vector<vector<vector<Integer> > > >& int_vec)
{
  NBT_RBI_LRU01_LRF07 = int_vec;
}

void MF02MT151Parser::set_INT_RBI_LRU01_LRF07(vector<vector<vector<vector<Integer> > > >& int_vec)
{
  INT_RBI_LRU01_LRF07 = int_vec;
}

void MF02MT151Parser::set_E_INT_RBI_LRU01_LRF07(vector<vector<vector<vector<Real> > > >& real_vec)
{
  E_INT_RBI_LRU01_LRF07 = real_vec;
}

void MF02MT151Parser::set_RBI_TAB_LRU01_LRF07(vector<vector<vector<vector<Real> > > >& real_vec)
{
  RBI_TAB_LRU01_LRF07 = real_vec;
}


void MF02MT151Parser::set_ED_LRU01_LRF07(vector<vector<vector<Real> > >& real_vec)
{
  ED_LRU01_LRF07 = real_vec;
}

void MF02MT151Parser::set_EU_LRU01_LRF07(vector<vector<vector<Real> > >& real_vec)
{
  EU_LRU01_LRF07 = real_vec;
}

void MF02MT151Parser::set_R0_LRU01_LRF07(vector<vector<vector<Real> > >& real_vec)
{
  R0_LRU01_LRF07 = real_vec;
}

void MF02MT151Parser::set_R1_LRU01_LRF07(vector<vector<vector<Real> > >& real_vec)
{
  R1_LRU01_LRF07 = real_vec;
}

void MF02MT151Parser::set_R2_LRU01_LRF07(vector<vector<vector<Real> > >& real_vec)
{
  R2_LRU01_LRF07 = real_vec;
}

void MF02MT151Parser::set_S0_LRU01_LRF07(vector<vector<vector<Real> > >& real_vec)
{
  S0_LRU01_LRF07 = real_vec;
}

void MF02MT151Parser::set_S1_LRU01_LRF07(vector<vector<vector<Real> > >& real_vec)
{
  S1_LRU01_LRF07 = real_vec;
}

void MF02MT151Parser::set_GA_LRU01_LRF07(vector<vector<vector<Real> > >& real_vec)
{
  GA_LRU01_LRF07 = real_vec;
}


void MF02MT151Parser::set_LPS_LRU01_LRF07(vector<vector<vector<Integer> > >& int_vec)
{
  LPS_LRU01_LRF07 = int_vec;
}

void MF02MT151Parser::set_NBT_PSR_LRU01_LRF07(vector<vector<vector<vector<Integer> > > >& int_vec)
{
  NBT_PSR_LRU01_LRF07 = int_vec;
}

void MF02MT151Parser::set_INT_PSR_LRU01_LRF07(vector<vector<vector<vector<Integer> > > >& int_vec)
{
  INT_PSR_LRU01_LRF07 = int_vec;
}

void MF02MT151Parser::set_E_INT_PSR_LRU01_LRF07(vector<vector<vector<vector<Real> > > >& real_vec)
{
  E_INT_PSR_LRU01_LRF07 = real_vec;
}

void MF02MT151Parser::set_PSR_TAB_LRU01_LRF07(vector<vector<vector<vector<Real> > > >& real_vec)
{
  PSR_TAB_LRU01_LRF07 = real_vec;
}

void MF02MT151Parser::set_NBT_PSI_LRU01_LRF07(vector<vector<vector<vector<Integer> > > >& int_vec)
{
  NBT_PSI_LRU01_LRF07 = int_vec;
}

void MF02MT151Parser::set_INT_PSI_LRU01_LRF07(vector<vector<vector<vector<Integer> > > >& int_vec)
{
  INT_PSI_LRU01_LRF07 = int_vec;
}

void MF02MT151Parser::set_E_INT_PSI_LRU01_LRF07(vector<vector<vector<vector<Real> > > >& real_vec)
{
  E_INT_PSI_LRU01_LRF07 = real_vec;
}

void MF02MT151Parser::set_PSI_TAB_LRU01_LRF07(vector<vector<vector<vector<Real> > > >& real_vec)
{
  PSI_TAB_LRU01_LRF07 = real_vec;
}


////////////////////////////////////////////////////////////////////////////////////////////////////

//LRU=2
void MF02MT151Parser::set_LSSF_LRU02(vector<vector<Integer> >& int_vec)
{
  LSSF_LRU02 = int_vec;
}

void MF02MT151Parser::set_L_LRU02(vector<vector<vector<Integer> > >& int_vec)
{
  L_LRU02 = int_vec;
}

void MF02MT151Parser::set_NJS_LRU02(vector<vector<vector<Integer> > >& int_vec)
{
  NJS_LRU02 = int_vec;
}


////////////////////////////////////////////////////////////////////////////////////////////////////

//LRU=2, Case A
void MF02MT151Parser::set_D_LRU02_A(vector<vector<vector<vector<Real> > > >& real_vec)
{
  D_LRU02_A = real_vec;
}

void MF02MT151Parser::set_AJ_LRU02_A(vector<vector<vector<vector<Real> > > >& real_vec)
{
  AJ_LRU02_A = real_vec;
}

void MF02MT151Parser::set_AMUN_LRU02_A(vector<vector<vector<vector<Real> > > >& real_vec)
{
  AMUN_LRU02_A = real_vec;
}

void MF02MT151Parser::set_GNO_LRU02_A(vector<vector<vector<vector<Real> > > >& real_vec)
{
  GNO_LRU02_A = real_vec;
}

void MF02MT151Parser::set_GG_LRU02_A(vector<vector<vector<vector<Real> > > >& real_vec)
{
  GG_LRU02_A = real_vec;
}


////////////////////////////////////////////////////////////////////////////////////////////////////

//LRU=2, Case B
void MF02MT151Parser::set_NE_LRU02_B(vector<vector<Integer> >& int_vec)
{
  NE_LRU02_B = int_vec;
}

void MF02MT151Parser::set_ES_LRU02_B(vector<vector<vector<Real> > >& real_vec)
{
  ES_LRU02_B = real_vec;
}

void MF02MT151Parser::set_MUF_LRU02_B(vector<vector<vector<vector<Integer> > > >& int_vec)
{
  MUF_LRU02_B = int_vec;
}

void MF02MT151Parser::set_D_LRU02_B(vector<vector<vector<vector<Real> > > >& real_vec)
{
  D_LRU02_B = real_vec;
}

void MF02MT151Parser::set_AJ_LRU02_B(vector<vector<vector<vector<Real> > > >& real_vec)
{
  AJ_LRU02_B = real_vec;
}

void MF02MT151Parser::set_AMUN_LRU02_B(vector<vector<vector<vector<Real> > > >& real_vec)
{
  AMUN_LRU02_B = real_vec;
}

void MF02MT151Parser::set_GNO_LRU02_B(vector<vector<vector<vector<Real> > > >& real_vec)
{
  GNO_LRU02_B = real_vec;
}

void MF02MT151Parser::set_GG_LRU02_B(vector<vector<vector<vector<Real> > > >& real_vec)
{
  GG_LRU02_B = real_vec;
}

void MF02MT151Parser::set_GF_LRU02_B(vector<vector<vector<vector<vector<Real> > > > >& real_vec)
{
  GF_LRU02_B = real_vec;
}


////////////////////////////////////////////////////////////////////////////////////////////////////

//LRU=2, Case C
void MF02MT151Parser::set_AJ_LRU02_C(vector<vector<vector<vector<Real> > > >& real_vec)
{
  AJ_LRU02_C = real_vec;
}

void MF02MT151Parser::set_INT_LRU02_C(vector<vector<vector<vector<Integer> > > >& int_vec)
{
  INT_LRU02_C = int_vec;
}

void MF02MT151Parser::set_NE_LRU02_C(vector<vector<vector<vector<Integer> > > >& int_vec)
{
  NE_LRU02_C = int_vec;
}

void MF02MT151Parser::set_AMUX_LRU02_C(vector<vector<vector<vector<Real> > > >& real_vec)
{
  AMUX_LRU02_C = real_vec;
}

void MF02MT151Parser::set_AMUN_LRU02_C(vector<vector<vector<vector<Real> > > >& real_vec)
{
  AMUN_LRU02_C = real_vec;
}

void MF02MT151Parser::set_AMUG_LRU02_C(vector<vector<vector<vector<Real> > > >& real_vec)
{
  AMUG_LRU02_C = real_vec;
}

void MF02MT151Parser::set_AMUF_LRU02_C(vector<vector<vector<vector<Real> > > >& real_vec)
{
  AMUF_LRU02_C = real_vec;
}

void MF02MT151Parser::set_ES_LRU02_C(vector<vector<vector<vector<vector<Real> > > > >& real_vec)
{
  ES_LRU02_C = real_vec;
}

void MF02MT151Parser::set_D_LRU02_C(vector<vector<vector<vector<vector<Real> > > > >& real_vec)
{
  D_LRU02_C = real_vec;
}

void MF02MT151Parser::set_GX_LRU02_C(vector<vector<vector<vector<vector<Real> > > > >& real_vec)
{
  GX_LRU02_C = real_vec;
}

void MF02MT151Parser::set_GNO_LRU02_C(vector<vector<vector<vector<vector<Real> > > > >& real_vec)
{
  GNO_LRU02_C = real_vec;
}

void MF02MT151Parser::set_GG_LRU02_C(vector<vector<vector<vector<vector<Real> > > > >& real_vec)
{
  GG_LRU02_C = real_vec;
}

void MF02MT151Parser::set_GF_LRU02_C(vector<vector<vector<vector<vector<Real> > > > >& real_vec)
{
  GF_LRU02_C = real_vec;
}

