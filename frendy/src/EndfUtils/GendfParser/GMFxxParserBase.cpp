#include "EndfUtils/GendfParser/GMFxxParserBase.hpp"

using namespace frendy;

//constructor
GMFxxParserBase::GMFxxParserBase(void)
{
  clear();

  err_obj.set_output_mode(err_obj.warning_off);
}

//destructor
GMFxxParserBase::~GMFxxParserBase(void)
{ 
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GMFxxParserBase::store_data() 
{
  MultiParser mp_obj;

  if( mf_no == 0 )
  {
    string class_name = "GMFxxParserBase";
    string func_name  = "store_data()";

    vector<string> err_com;
    err_com.push_back("Please set MF number before storing the data.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //Text file data check
  if( static_cast<Integer>(text.size()) < 2 )
  {
    string class_name = "GMFxxParserBase";
    string func_name  = "store_data()";

    ostringstream oss;
    oss << static_cast<Integer>(text.size());
    string str_data = "Text line number : " + oss.str();

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("The text line number is not appropriate for MF=03.");
    err_com.push_back("The text line number should be larger than 1.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //Check MF number
  if( mp_obj.check_mf(text, mf_no) != 0)
  {
    string class_name = "GMFxxParserBase";
    string func_name  = "store_data()";

    ostringstream oss01;
    oss01 << mf_no;
    string str_data01 = "Text data at first line : " + text[0];
    string str_data02 = "File number (MF)        : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("The MF number is different.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  mp_obj.get_mat(text, mat_no);

  int     line_no = 0;
  Integer tmp_int;
  Real    tmp_real;

  //Get MT number
  mp_obj.get_mf_mt(text, tmp_int, mt_no);
  //cout << "    MF = " << mf_no << " / MT = " << mt_no << endl;

  //Line No.01
  //ZA, AWR
  mp_obj.read_head(text, line_no, ZA, AWR, NL, NSIGZ, LR, NGN);

  int eg_no   = static_cast<int>(NGN) + 1; //MF=6 MT=18 has NGN+1 data
  int sigz_no = static_cast<int>(NSIGZ);
  int pl_no   = static_cast<int>(NL);

  NG2.resize(eg_no);
  IG2LO.resize(eg_no);
  IG.resize(eg_no);
  DATA1.resize(eg_no);
  DATA2.resize(eg_no);
  for(int i=0; i<eg_no; i++)
  {
    NG2[i]   = -1;
    IG2LO[i] = -1;
    IG[i]    = -1;
  }

  int ng1         = 0;
  int line_no_max = static_cast<int>(text.size());
  while( line_no < line_no_max )
  {
    //Line No.02
    //TEMP, DATA1 and DATA2
    Real         temp_each;
    int          ng2_each, ig2lo_each, data_no, ig_each;
    vector<Real> e_vec;
    mp_obj.read_list(text, line_no, temp_each, tmp_real, ng2_each, ig2lo_each, data_no, ig_each, e_vec);

    if( ng1 == 0 )
    {
      TEMP = temp_each;
    }
    else
    {
      if( fabs(TEMP - temp_each) > 1.0E-3 )
      {
        string class_name = "GMFxxParserBase";
        string func_name  = "store_data()";

        ostringstream oss01, oss02, oss03, oss04, oss05;
        oss01 << mf_no;
        oss02 << mt_no;
        oss03 << ig_each;
        oss04 << setw(8) << std::showpoint << std::scientific << TEMP;
        oss05 << setw(8) << std::showpoint << std::scientific << temp_each;
        string str_data01 = "MF number           : " + oss01.str();
        string str_data02 = "MT number           : " + oss02.str();
        string str_data03 = "IG                  : " + oss03.str();
        string str_data04 = "TEMP of first grid  : " + oss04.str();
        string str_data05 = "TEMP of IG grid     : " + oss05.str();

        vector<string> err_com;
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back(str_data04);
        err_com.push_back(str_data05);
        err_com.push_back("");
        err_com.push_back("Line data");
        err_com.push_back(text[line_no-1]);
        err_com.push_back("");
        err_com.push_back("TEMP data must be identical in all energy grid.");
        err_com.push_back("This GENDF file might be incorrect.");

        err_obj.output_caution(class_name, func_name, err_com);
      }
    }
    ng1++;


    int e_vec_no    = static_cast<int>(e_vec.size());
    int e_pos       = ig_each; //MF=6 MT=18 has IG=0-NGN
    int sigz_no_mod = sigz_no;
    if( e_vec_no == 0 )
    {
      continue;
    }
    if( e_pos == 0 )
    {
      if( e_vec_no != ng2_each * sigz_no * pl_no )
      {
        sigz_no_mod = 1;
      }
    }

    NG2[e_pos]   = ng2_each;
    IG2LO[e_pos] = ig2lo_each;
    IG[e_pos]    = ig_each;
    DATA1[e_pos].resize(sigz_no_mod);
    DATA2[e_pos].resize(sigz_no_mod);
    for(int i=0; i<sigz_no_mod; i++)
    {
      DATA1[e_pos][i].resize(pl_no);
      DATA2[e_pos][i].resize(pl_no);
      for(int j=0; j<pl_no; j++)
      {
        DATA1[e_pos][i][j] = 0.0;
        DATA2[e_pos][i][j].resize(ng2_each - 1);
        for(int k=0; k<ng2_each - 1; k++)
        {
          DATA2[e_pos][i][j][k] = 0.0;
        }
      }
    }


    int ele_no = 0;
    for(int i=0; i<sigz_no_mod; i++)
    {
      for(int j=0; j<pl_no; j++)
      {
        DATA1[e_pos][i][j] = e_vec[ele_no];
        ele_no++;
      }
    }

    for(int k=0; k<ng2_each - 1; k++)
    {
      for(int i=0; i<sigz_no_mod; i++)
      {
        for(int j=0; j<pl_no; j++)
        {
          DATA2[e_pos][i][j][k] = e_vec[ele_no];
          ele_no++;
        }
      }
    }

    if( e_pos == 0 && e_vec_no != ng2_each * sigz_no * pl_no )
    {
      ele_no = 0;
      for(int i=0; i<sigz_no_mod; i++)
      {
        for(int j=0; j<pl_no; j++)
        {
          DATA1[e_pos][i][j] = 0.0;
        }
      }

      for(int i=0; i<sigz_no_mod; i++)
      {
        for(int j=0; j<pl_no; j++)
        {
          DATA2[e_pos][i][j].resize(ng2_each);
          for(int k=0; k<ng2_each; k++)
          {
            DATA2[e_pos][i][j][k] = e_vec[ele_no];
            ele_no++;
          }
        }
      }
    }

    if( ele_no != e_vec_no )
    {
      string class_name = "GMFxxParserBase";
      string func_name  = "store_data()";

      ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07, oss08, oss09;
      oss01 << mf_no;
      oss02 << mt_no;
      oss03 << ig_each;
      oss04 << setw(8) << std::showpoint << std::scientific << TEMP;
      oss05 << e_vec_no;
      oss06 << ele_no;
      string str_data01 = "MF number           : " + oss01.str();
      string str_data02 = "MT number           : " + oss02.str();
      string str_data03 = "IG                  : " + oss03.str();
      string str_data04 = "TEMP                : " + oss04.str();
      string str_data05 = "Data number of list : " + oss05.str();
      string str_data06 = "Parsed data number  : " + oss06.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back(str_data04);
      err_com.push_back(str_data05);
      err_com.push_back(str_data06);
      err_com.push_back("Data number of list is different to the parsed data number.");
      err_com.push_back("This program may cannot correctly read the GENDF file.");

      //err_obj.output_runtime_error(class_name, func_name, err_com);
      err_obj.output_caution(class_name, func_name, err_com);
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GMFxxParserBase::clear()
{
  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);

  mat_no = unassigned_mat_no;
  mf_no  = 0;
  mt_no  = unassigned_mt_no;
  ZA     = 0.0;
  AWR    = 0.0;
  NL     = 0;
  NSIGZ  = 0;
  LR     = 0;
  NGN    = 0;

  TEMP   = 0.0;
  NG2.clear();
  IG2LO.clear();
  IG.clear();

  clr_vec.clear_vec_array3_real(DATA1);
  clr_vec.clear_vec_array4_real(DATA2);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GMFxxParserBase::set_text(vector<string> text_data)
{
  text = text_data;
  store_data();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GMFxxParserBase::remove_DATA2_NG2_zero_data()
{
  //This subroutine was copied from the remove_zero_dd_xs_data subroutine in MGXSUtils/OtherUtils/MGUtils.cpp
  int e_in_no  = static_cast<int>(DATA2.size());
  if( e_in_no == 0 )
  {
    string class_name = "GMFxxParserBase";
    string func_name  = "remove_DATA2_NG2_zero_data()";

    ostringstream oss01, oss02, oss03;
    oss01 << mat_no;
    oss02 << mf_no;
    oss03 << mt_no;
    string str_data01 = "MAT Number                : " + oss01.str();
    string str_data02 = "MF  Number                : " + oss02.str();
    string str_data03 = "MT  Number                : " + oss03.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("");
    err_com.push_back("The number of incident neutron energies is zero");
    err_com.push_back("The remove zero data process is skipped.");
    err_com.push_back("Please check the DATA2 data.");

    err_obj.output_caution(class_name, func_name, err_com);
    return;
  }

  int bg_no    = static_cast<int>(DATA2[0].size());
  if( bg_no == 0 )
  {
    string class_name = "GMFxxParserBase";
    string func_name  = "remove_DATA2_NG2_zero_data()";

    ostringstream oss01, oss02, oss03, oss04;
    oss01 << mat_no;
    oss02 << mf_no;
    oss03 << mt_no;
    oss04 << e_in_no;
    string str_data01 = "MAT Number                : " + oss01.str();
    string str_data02 = "MF  Number                : " + oss02.str();
    string str_data03 = "MT  Number                : " + oss03.str();
    string str_data04 = "e_in_no                   : " + oss04.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back("");
    err_com.push_back("The number of back ground cross sections energy is zero");
    err_com.push_back("The remove zero data process is skipped.");
    err_com.push_back("Please check the DATA2 data.");

    //err_obj.output_runtime_error(class_name, func_name, err_com);
    err_obj.output_caution(class_name, func_name, err_com);
    return;
  }

  int pl_no    = static_cast<int>(DATA2[0][0].size());
  if( pl_no == 0 )
  {
    string class_name = "GMFxxParserBase";
    string func_name  = "remove_DATA2_NG2_zero_data()";

    ostringstream oss01, oss02, oss03, oss04, oss05;
    oss01 << mat_no;
    oss02 << mf_no;
    oss03 << mt_no;
    oss04 << e_in_no;
    oss05 << bg_no;
    string str_data01 = "MAT Number                : " + oss01.str();
    string str_data02 = "MF  Number                : " + oss02.str();
    string str_data03 = "MT  Number                : " + oss03.str();
    string str_data04 = "e_in_no                   : " + oss04.str();
    string str_data05 = "bg_no                     : " + oss05.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back(str_data05);
    err_com.push_back("");
    err_com.push_back("The number of back ground cross sections energy is zero");
    err_com.push_back("The remove zero data process is skipped.");
    err_com.push_back("Please check the DATA2 data.");

    //err_obj.output_runtime_error(class_name, func_name, err_com);
    err_obj.output_caution(class_name, func_name, err_com);
    return;
  }

  int e_out_no = static_cast<int>(DATA2[0][0][0].size());
  if( e_out_no == 0 )
  {
    string class_name = "GMFxxParserBase";
    string func_name  = "remove_DATA2_NG2_zero_data()";

    ostringstream oss01, oss02, oss03, oss04, oss05, oss06;
    oss01 << mat_no;
    oss02 << mf_no;
    oss03 << mt_no;
    oss04 << e_in_no;
    oss05 << bg_no;
    oss06 << pl_no;
    string str_data01 = "MAT Number                : " + oss01.str();
    string str_data02 = "MF  Number                : " + oss02.str();
    string str_data03 = "MT  Number                : " + oss03.str();
    string str_data04 = "e_in_no                   : " + oss04.str();
    string str_data05 = "bg_no                     : " + oss05.str();
    string str_data06 = "pl_no                     : " + oss06.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back(str_data05);
    err_com.push_back(str_data06);
    err_com.push_back("");
    err_com.push_back("The number of back ground cross sections energy is zero");
    err_com.push_back("The remove zero data process is skipped.");
    err_com.push_back("Please check the DATA2 data.");

    //err_obj.output_runtime_error(class_name, func_name, err_com);
    err_obj.output_caution(class_name, func_name, err_com);
    return;
  }

  vector<vector<vector<Real> > >          DATA1_mod;
  vector<vector<vector<vector<Real> > > > DATA2_mod;
  clr_obj.clear_vec_array3_real(DATA1_mod);
  clr_obj.clear_vec_array4_real(DATA2_mod);

  vector<int>  ig_vec, ng2_vec, ig2lo_vec;
  ig_vec.clear();
  ng2_vec.clear();
  ig2lo_vec.clear();
  for(int i=0; i<e_in_no; i++)
  {
    int no_e_in_flg = 0;
    int ig2lo_val   = 0;
    int ig2hi_val   = 0;
    for(int j=0; j<e_out_no; j++)
    {
      for(int b=0; b<bg_no; b++)
      {
        for(int p=0; p<pl_no; p++)
        {
          if( fabs(DATA2[i][b][p][j]) > min_value )
          {
            no_e_in_flg = 1;
            ig2lo_val   = j;
            break;
          }
        }

        if( no_e_in_flg > 0 )
        {
          break;
        }
      }

      if( no_e_in_flg > 0 )
      {
        break;
      }
    }

    if( no_e_in_flg > 0 )
    {
      DATA1_mod.push_back(DATA1[i]);
      ig_vec.push_back(IG[i]);
      ig2lo_vec.push_back(ig2lo_val+1);

      no_e_in_flg = 0;
      ig2hi_val   = 0;
      for(int j=e_out_no-1; j>=0; j--)
      {
        for(int b=0; b<bg_no; b++)
        {
          for(int p=0; p<pl_no; p++)
          {
            if( fabs(DATA2[i][b][p][j]) > min_value )
            {
              no_e_in_flg = 1;
              ig2hi_val   = j;
              break;
            }
          }

          if( no_e_in_flg > 0 )
          {
            break;
          }
        }

        if( no_e_in_flg > 0 )
        {
          break;
        }
      }

      int ng2_no = ig2hi_val - ig2lo_val + 2;
      ng2_vec.push_back(ng2_no);

      vector<vector<vector<Real> > > DATA2_tmp;
      clr_obj.clear_vec_array3_real(DATA2_tmp);
      DATA2_tmp.resize(bg_no);
      for(int b=0; b<bg_no; b++)
      {
        DATA2_tmp[b].resize(pl_no);
        for(int p=0; p<pl_no; p++)
        {
          DATA2_tmp[b][p].resize(ng2_no-1);
          for(int j=ig2lo_val; j<=ig2hi_val; j++)
          {
            DATA2_tmp[b][p][j-ig2lo_val] = DATA2[i][b][p][j];
          }
        }
      }

      DATA2_mod.push_back(DATA2_tmp);
      clr_obj.clear_vec_array3_real(DATA2_tmp);
    }
  }

  DATA1 = DATA1_mod;
  DATA2 = DATA2_mod;
  IG    = ig_vec;
  NG2   = ng2_vec;
  IG2LO = ig2lo_vec;
  
  clr_obj.clear_vec_array3_real(DATA1_mod);
  clr_obj.clear_vec_array4_real(DATA2_mod);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GMFxxParserBase::multiply_coef(Real weight_val)
{
  multiply_coef_data1(weight_val);
  multiply_coef_data2(weight_val);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GMFxxParserBase::multiply_coef_data1(Real weight_val)
{
  int i_max = static_cast<int>(DATA1.size());
  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(DATA1[i].size());
    for(int j=0; j<j_max; j++)
    {
      int k_max = static_cast<int>(DATA1[i][j].size());
      for(int k=0; k<k_max; k++)
      {
        DATA1[i][j][k] *= weight_val;
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GMFxxParserBase::multiply_coef_data2(Real weight_val)
{
  int i_max = static_cast<int>(DATA2.size());
  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(DATA2[i].size());
    for(int j=0; j<j_max; j++)
    {
      int k_max = static_cast<int>(DATA2[i][j].size());
      for(int k=0; k<k_max; k++)
      {
        int l_max = static_cast<int>(DATA2[i][j][k].size());
        for(int l=0; l<l_max; l++)
        {
          DATA2[i][j][k][l] *= weight_val;
        }
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string>  GMFxxParserBase::get_text()
{
  return text;
}

Integer         GMFxxParserBase::get_mat_no()
{
  return mat_no;
}

Integer         GMFxxParserBase::get_mf_no()
{
  return mf_no;
}

Integer         GMFxxParserBase::get_mt_no()
{
  return mt_no;
}

//Getter at line No.01
Real            GMFxxParserBase::get_ZA()
{
  return ZA;
}

Real            GMFxxParserBase::get_AWR()
{
  return AWR;
}

Integer         GMFxxParserBase::get_NL()
{
  return NL;
}

Integer         GMFxxParserBase::get_NSIGZ()
{
  return NSIGZ;
}

Integer         GMFxxParserBase::get_LR()
{
  return LR;
}

Integer         GMFxxParserBase::get_NGN()
{
  return NGN;
}

//Getter at line No.02
Real            GMFxxParserBase::get_TEMP()
{
  return TEMP;
}

vector<int>     GMFxxParserBase::get_NG2()
{
  return NG2;
}

vector<int>     GMFxxParserBase::get_IG2LO()
{
  return IG2LO;
}

vector<int>     GMFxxParserBase::get_IG()
{
  return IG;
}

vector<vector<vector<Real> > > GMFxxParserBase::get_DATA1()
{
  return DATA1;
}

vector<vector<vector<vector<Real> > > > GMFxxParserBase::get_DATA2_NG2()
{
  return DATA2;
}

vector<vector<vector<Real> > > GMFxxParserBase::get_DATA2()
{
  vector<vector<vector<Real> > > real_vec;

  int i_max = static_cast<int>(DATA2.size());
  real_vec.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(DATA2[i].size());
    real_vec[i].resize(j_max);
    for(int j=0; j<j_max; j++)
    {
      int k_max = static_cast<int>(DATA2[i][j].size());
      real_vec[i][j].resize(k_max);
      for(int k=0; k<k_max; k++)
      {
        int l_max = static_cast<int>(DATA2[i][j][k].size());
        if( l_max == 0 )
        {
          real_vec[i][j][k] = 0.0;
        }
        else
        {
          real_vec[i][j][k] = DATA2[i][j][k][0];
        }

        if( l_max > 1 )
        {
          string class_name = "GMFxxParserBase";
          string func_name  = "vector<vector<vector<Real> > > get_DATA2()";

          ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07, oss08, oss09;
          oss01 << mf_no;
          oss02 << mt_no;
          oss03 << IG[i];
          oss04 << i_max;
          oss05 << j+1;
          oss06 << j_max;
          oss07 << k+1;
          oss08 << k_max;
          oss09 << l_max;
          string str_data01 = "MF number           : " + oss01.str();
          string str_data02 = "MT number           : " + oss02.str();
          string str_data03 = "IG                  : " + oss03.str() + " / " + oss04.str();
          string str_data04 = "NSIGZ               : " + oss05.str() + " / " + oss06.str();
          string str_data05 = "NL                  : " + oss07.str() + " / " + oss08.str();
          string str_data06 = "NG2                 : " + oss09.str();

          vector<string> err_com;
          err_com.push_back(str_data01);
          err_com.push_back(str_data02);
          err_com.push_back(str_data03);
          err_com.push_back(str_data04);
          err_com.push_back(str_data05);
          err_com.push_back(str_data06);
          err_com.push_back("NG2 is larger than 1.");
          err_com.push_back("Please use vector<vector<vector<vector<Real> > > > get_DATA2() function.");

          err_obj.output_runtime_error(class_name, func_name, err_com);
        }
      }
    }
  }

  return real_vec;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<vector<vector<vector<Real> > > > GMFxxParserBase::get_DATA2_NG2_fill_data()
{
  vector<vector<vector<vector<Real> > > > real_vec;

  int i_max = static_cast<int>(DATA2.size());
  real_vec.resize(i_max);
  for(int i=0; i<i_max; i++) //e_in
  {
    int ng2_new = 0;
    int j_max   = static_cast<int>(DATA2[i].size());
    real_vec[i].resize(j_max);
    for(int j=0; j<j_max; j++) //bg_no
    {
      int k_max = static_cast<int>(DATA2[i][j].size());
      real_vec[i][j].resize(k_max);

      //Set ng2_new (number of secondary energy groups)
      ng2_new = NGN;
      for(int k=0; k<k_max; k++) //pl_no
      {
        int ig2lo_val = IG2LO[i];
        int l_max     = static_cast<int>(DATA2[i][j][k].size());
        if( ng2_new < l_max + ig2lo_val - 1 )
        {
          ng2_new = l_max + ig2lo_val - 1;
        }
      }

      for(int k=0; k<k_max; k++) //pl_no
      {
        int l_max = static_cast<int>(DATA2[i][j][k].size());
        if( (mf_no == 3 || mf_no == 13) && IG2LO[i] == 1 && l_max == 1 && NG2[i] == 2 )
        {
          //For 1D vector
          ng2_new = NG2[i];
          real_vec[i][j][k] = DATA2[i][j][k];
          continue;
        }

        int ig2lo_val = IG2LO[i];
        real_vec[i][j][k].resize(ng2_new);
        for(int l=0; l<ng2_new; l++)
        {
          real_vec[i][j][k][l] = 0.0;
        }

        for(int l=0; l<l_max; l++) //eout_no
        {
          real_vec[i][j][k][l+ig2lo_val-1] = DATA2[i][j][k][l];
        }
      }
    }

    NG2[i]   = ng2_new;
    IG2LO[i] = 1;
  }

  return real_vec;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<vector<vector<Real> > > GMFxxParserBase::get_DATA2_integ()
{
  vector<vector<vector<Real> > > data2_integ_vec;

  int i_max = static_cast<int>(DATA2.size());
  data2_integ_vec.resize(i_max);
  for(int i=0; i<i_max; i++) //e_in
  {
    int j_max   = static_cast<int>(DATA2[i].size());
    data2_integ_vec[i].resize(j_max);
    for(int j=0; j<j_max; j++) //bg_no
    {
      int k_max = static_cast<int>(DATA2[i][j].size());
      data2_integ_vec[i][j].resize(k_max);
      for(int k=0; k<k_max; k++) //pl_no
      {
        data2_integ_vec[i][j][k] = get_DATA2_integ(i, j, k);
      }
    }
  }

  return data2_integ_vec;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
      
Real GMFxxParserBase::get_DATA2_integ(int ene_in, int sigz_no, int pl_no)
{
  Real data2_integ = 0.0;

  int data_flg = -1;
  if( static_cast<int>(DATA2.size()) > ene_in )
  {
    if( static_cast<int>(DATA2[ene_in].size()) > sigz_no )
    {
      if( static_cast<int>(DATA2[ene_in][sigz_no].size()) > pl_no )
      {
        data_flg = 1;
      }
    }
  }

  if( data_flg < 0 )
  {
    return data2_integ;
  }

  int l_max = static_cast<int>(DATA2[ene_in][sigz_no][pl_no].size());
  for(int l=0; l<l_max; l++) //eout_no
  {
    data2_integ += DATA2[ene_in][sigz_no][pl_no][l];
  }

  return data2_integ;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
      
vector<Real> GMFxxParserBase::get_DATA1(vector<vector<vector<Real> > > & data1_vec,
                                        int sigz_no, int pl_no)
{
  vector<Real> data1_new;
  data1_new.clear();

  int i_max = static_cast<int>(data1_vec.size());
  int i_mod = i_max - NGN;  //MF=6 MT=18 has NGN+1 data
  if( i_mod < 0 )
  {
    i_mod = 0;
  }

  data1_new.resize(i_max-i_mod);
  for(int i=i_mod; i<i_max; i++)
  {
    data1_new[i-i_mod] = 0.0;

    int data_flg = -1;
    if( static_cast<int>(data1_vec[i].size()) > sigz_no )
    {
      if( static_cast<int>(data1_vec[i][sigz_no].size()) > pl_no )
      {
        data_flg = 1;
      }
    }

    if( data_flg < 0 )
    {
      continue;
    }

    data1_new[i-i_mod] = data1_vec[i][sigz_no][pl_no];
  }

  return data1_new;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<Real> GMFxxParserBase::get_DATA1(int sigz_no, int pl_no)
{

  return get_DATA1(DATA1, sigz_no, pl_no);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<Real> GMFxxParserBase::get_DATA2(int sigz_no, int pl_no)
{
  vector<vector<vector<Real> > > data2_new = get_DATA2();
  return get_DATA1(data2_new, sigz_no, pl_no);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<vector<Real> > GMFxxParserBase::get_DATA2_NG2(vector<vector<vector<vector<Real> > > >& data2_vec,
                                                     int sigz_no, int pl_no)
{
  vector<vector<Real> > data2_new;
  data2_new.clear();

  int i_max = static_cast<int>(data2_vec.size());
  int i_mod = i_max - NGN;  //MF=6 MT=18 has NGN+1 data
  if( i_mod < 0 )
  {
    i_mod = 0;
  }

  data2_new.resize(i_max-i_mod);
  for(int i=i_mod; i<i_max; i++)
  {
    data2_new[i-i_mod].clear();

    int data_flg = -1;
    if( static_cast<int>(data2_vec[i].size()) > sigz_no )
    {
      if( static_cast<int>(data2_vec[i][sigz_no].size()) > pl_no )
      {
        data_flg = 1;
      }
    }

    if( data_flg < 0 )
    {
      continue;
    }

    data2_new[i-i_mod] = data2_vec[i][sigz_no][pl_no];
  }

  return data2_new;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<vector<Real> > GMFxxParserBase::get_DATA2_NG2(int sigz_no, int pl_no)
{

  return get_DATA2_NG2(DATA2, sigz_no, pl_no);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<vector<Real> > GMFxxParserBase::get_DATA2_NG2_fill_data(int sigz_no, int pl_no)
{
  vector<vector<vector<vector<Real> > > > data2_full = get_DATA2_NG2_fill_data();

  return get_DATA2_NG2(data2_full, sigz_no, pl_no);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void GMFxxParserBase::set_mat_no(Integer int_no)
{
  mat_no = int_no;
}

void GMFxxParserBase::set_mf_no(Integer int_no)
{
  mf_no = int_no;
}

void GMFxxParserBase::set_mt_no(Integer int_no)
{
  mt_no = int_no;
}

//line No.01
void GMFxxParserBase::set_ZA(Real real_data)
{
  ZA = real_data;
}

void GMFxxParserBase::set_AWR(Real real_data)
{
  AWR = real_data;
}

void GMFxxParserBase::set_NL(Integer int_data)
{
  NL = int_data;
}
void GMFxxParserBase::set_NSIGZ(Integer int_data)
{
  NSIGZ = int_data;
}

void GMFxxParserBase::set_LR(Integer int_data)
{
  LR = int_data;
}

void GMFxxParserBase::set_NGN(Integer int_data)
{
  NGN = int_data;
}

//line No.02
void GMFxxParserBase::set_TEMP(Real real_data)
{
  TEMP = real_data;
}

void GMFxxParserBase::set_NG2(vector<int> int_data)
{
  NG2 = int_data;
}

void GMFxxParserBase::set_IG2LO(vector<int> int_data)
{
  IG2LO = int_data;
}

void GMFxxParserBase::set_IG(vector<int> int_data)
{
  IG = int_data;
}

void GMFxxParserBase::set_DATA1(vector<vector<vector<Real> > > real_vec)
{
  DATA1 = real_vec;
}

void GMFxxParserBase::set_DATA2_NG2(vector<vector<vector<vector<Real> > > > real_vec)
{
  DATA2 = real_vec;
}

void GMFxxParserBase::set_DATA2(vector<vector<vector<Real> > > real_vec)
{
  int i_max = static_cast<int>(real_vec.size());
  DATA2.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(real_vec[i].size());
    DATA2[i].resize(j_max);
    for(int j=0; j<j_max; j++)
    {
      int k_max = static_cast<int>(real_vec[i][j].size());
      DATA2[i][j].resize(k_max);
      for(int k=0; k<k_max; k++)
      {
        DATA2[i][j][k].resize(1);
        DATA2[i][j][k][0] = real_vec[i][j][k];
      }
    }
  }
}

