#include "EndfUtils/MFxxMTyyyWriter/MF06Writer.hpp"

using namespace frendy;

//constructor
MF06Writer::MF06Writer(void)
{
  clear();
}

//destructor
MF06Writer::~MF06Writer(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF06Writer::write_endf()
{
  clr_obj.clear_vec_array1_str(text);

  string         line_data;
  vector<string> str_vec;
  efw_obj.set_mat_mf_mt(par_obj.get_mat_no(), mf_no, par_obj.get_mt_no());

  //Line No.01
  //ZA, AWR, LTT
  line_data = efw_obj.write_cont(par_obj.get_ZA(), par_obj.get_AWR(),
                                 par_obj.get_JP(), par_obj.get_LCT(), par_obj.get_NK(), 0);
  text.push_back(line_data);
  line_data.clear();

  if( par_obj.get_LCT() == 5 || par_obj.get_LCT() == 6 || par_obj.get_LCT() == 7 )
  {
    write_thermal_scatter(text);
  }
  else
  {
    int i_max = static_cast<int>(par_obj.get_NK());
    for(int i=0; i<i_max; i++)
    {
      //Line No.02
      //LF, p
      Integer NR = static_cast<Integer>(par_obj.get_NBT_Y()[i].size());
      Integer NP = static_cast<Integer>(par_obj.get_E_INT_Y()[i].size());
      str_vec = efw_obj.write_tab1(par_obj.get_ZAP()[i], par_obj.get_AWP()[i],
                                   par_obj.get_LIP()[i], par_obj.get_LAW()[i], NR, NP,
                                   par_obj.get_NBT_Y()[i],   par_obj.get_INT_Y()[i],
                                   par_obj.get_E_INT_Y()[i], par_obj.get_Y_TAB()[i]);
      for(int j=0; j<static_cast<int>(str_vec.size()); j++)
      {
        text.push_back(str_vec[j]);
      }
      clr_obj.clear_vec_array1_str(str_vec);

      Integer law_val = par_obj.get_LAW()[i];
      if( law_val == 1 )
      {
        write_law01(i, str_vec);
      }
      else if( law_val == 2 )
      {
        write_law02(i, str_vec);
      }
      else if( law_val == 5 )
      {
        write_law05(i, str_vec);
      }
      else if( law_val == 6 )
      {
        str_vec.resize(1);
        str_vec[0] = efw_obj.write_cont( par_obj.get_APSX_LAW06()[i], 0.0,
                                         0, 0, 0, par_obj.get_NPSX_LAW06()[i] );
      }
      else if( law_val == 7 )
      {
        write_law07(i, str_vec);
      }
      else if( law_val < 0 && par_obj.get_JP() > 0 )
      {
        //No LAW-dependent structure is given.
      }
      else if( law_val < 0 || law_val > 7 )
      {
        string class_name = "MF06Writer";
        string func_name  = "write_endf()";

        ostringstream oss00, oss01, oss02, oss03;
        oss00 << par_obj.get_mt_no();
        oss01 << i;
        oss02 << i_max;
        oss03 << law_val;
        string str_data00 = "Section number (MT) : " + oss00.str();
        string str_data01 = "NK                  : " + oss01.str() + " / " + oss02.str();
        string str_data02 = "LAW                 : " + oss03.str();

        vector<string> err_com;
        err_com.push_back(str_data00);
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back("This LAW value at MF=06 is not supported in this program.");
        err_com.push_back("Supported LAW value is 0 - 7.");
  
        err_obj.output_runtime_error(class_name, func_name, err_com);
      }

      for(int j=0; j<static_cast<int>(str_vec.size()); j++)
      {
        text.push_back(str_vec[j]);
      }
      clr_obj.clear_vec_array1_str(str_vec);
    }
  }

  line_data = efw_obj.write_mt_end();
  text.push_back(line_data);
  line_data.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF06Writer::write_law01(int& i, vector<string>& text)
{
  vector<string> str_vec;

  Integer NR = static_cast<Integer>(par_obj.get_NBT_E_LAW01()[i].size());
  str_vec = efw_obj.write_tab2(0.0, 0.0, par_obj.get_LANG_LAW01()[i], par_obj.get_LEP_LAW01()[i], 
                               NR, par_obj.get_NE_LAW01()[i],
                               par_obj.get_NBT_E_LAW01()[i],  par_obj.get_INT_E_LAW01()[i]);
  for(int j=0; j<static_cast<int>(str_vec.size()); j++)
  {
    text.push_back(str_vec[j]);
  }
  clr_obj.clear_vec_array1_str(str_vec);

  int j_max = static_cast<int>(par_obj.get_NE_LAW01()[i]);
  vector<vector<Real> >          e2 = par_obj.get_E2_LAW01()[i];
  vector<vector<vector<Real> > > b  = par_obj.get_B_LAW01()[i];
  for(int j=0; j<j_max; j++)
  {
    Integer      NA  = static_cast<Integer>(par_obj.get_B_LAW01()[i][j][0].size()) - 1;
    Integer      NEP = static_cast<Integer>(par_obj.get_B_LAW01()[i][j].size());
    Integer      NW  = NEP*(NA+2);

    int na = static_cast<int>(NA);

    vector<Real> b_vec;
    b_vec.resize(static_cast<int>(NW));
    for(int k=0; k<static_cast<int>(NEP); k++)
    {
      int ele_no = (na+2)*k;
      b_vec[ele_no] = e2[j][k];
      for(int l=1; l<na+2; l++)
      {
        b_vec[ele_no+l] = b[j][k][l-1];
      }
    }
    efw_obj.set_digit_mod_mode(efw_obj.no_mod_digit);
    str_vec = efw_obj.write_list(0.0, par_obj.get_E1_LAW01()[i][j], par_obj.get_ND_LAW01()[i][j],
                                 NA, NW, NEP, b_vec);
    efw_obj.set_digit_mod_mode_default();

    for(int k=0; k<static_cast<int>(str_vec.size()); k++)
    {
      text.push_back(str_vec[k]);
    }
    clr_obj.clear_vec_array1_str(str_vec);
    b_vec.clear();
  }
  clr_obj.clear_vec_array2_real(e2);
  clr_obj.clear_vec_array3_real(b);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF06Writer::write_law02(int& i, vector<string>& text)
{
  vector<string> str_vec;

  Integer NR = static_cast<Integer>(par_obj.get_NBT_E_LAW02()[i].size());

  str_vec = efw_obj.write_tab2(0.0, 0.0, 0, 0, NR, par_obj.get_NE_LAW02()[i], 
                               par_obj.get_NBT_E_LAW02()[i], par_obj.get_INT_E_LAW02()[i]);
  for(int j=0; j<static_cast<int>(str_vec.size()); j++)
  {
    text.push_back(str_vec[j]);
  }
  clr_obj.clear_vec_array1_str(str_vec);

  int j_max = static_cast<int>(par_obj.get_NE_LAW02()[i]);
  for(int j=0; j<j_max; j++)
  {
    Integer NW = static_cast<Integer>(par_obj.get_A_LAW02()[i][j].size());
    str_vec = efw_obj.write_list(0.0, par_obj.get_E_LAW02()[i][j], par_obj.get_LANG_LAW02()[i][j], 0, NW,
                                 par_obj.get_NL_LAW02()[i][j], par_obj.get_A_LAW02()[i][j]);
    for(int k=0; k<static_cast<int>(str_vec.size()); k++)
    {
      text.push_back(str_vec[k]);
    }
    clr_obj.clear_vec_array1_str(str_vec);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF06Writer::write_law05(int& i, vector<string>& text)
{
  vector<string> str_vec;

  Integer NR       = static_cast<Integer>(par_obj.get_NBT_E_LAW05()[i].size());
  Integer lidp_val = par_obj.get_LIDP_LAW05()[i];

  str_vec = efw_obj.write_tab2(par_obj.get_SPI_LAW05()[i], 0.0, lidp_val, 0, NR, par_obj.get_NE_LAW05()[i],
                               par_obj.get_NBT_E_LAW05()[i], par_obj.get_INT_E_LAW05()[i]);
  for(int j=0; j<static_cast<int>(str_vec.size()); j++)
  {
    text.push_back(str_vec[j]);
  }
  clr_obj.clear_vec_array1_str(str_vec);

  int j_max = static_cast<int>(par_obj.get_NE_LAW05()[i]);
  vector<vector<Real> > b  = par_obj.get_B_LAW05()[i];
  vector<vector<Real> > ra = par_obj.get_RA_LAW05()[i];
  vector<vector<Real> > ia = par_obj.get_IA_LAW05()[i];
  vector<vector<Real> > c  = par_obj.get_C_LAW05()[i];
  vector<vector<Real> > mu = par_obj.get_MU_LAW05()[i];
  vector<vector<Real> > p  = par_obj.get_P_LAW05()[i];
  for(int j=0; j<j_max; j++)
  {
    Integer      NW = 0;
    Integer      NL = 0;
    vector<Real> a_vec;
    Integer ltp_val = par_obj.get_LTP_LAW05()[i][j];

    int ele_no = 0;
    if( ltp_val == 1 && lidp_val == 0 )
    {
      NL = static_cast<Integer>(ra[j].size()) - 1;
      NW = 4*NL+3;
      a_vec.resize(static_cast<int>(NW));

      int k_max = static_cast<int>(NL) + 1;
      for(int k=0; k<2*k_max-1; k++)
      {
        a_vec[ele_no] = b[j][k];
        ele_no++;
      }
      for(int k=0; k<k_max; k++)
      {
        a_vec[ele_no]   = ra[j][k];
        a_vec[ele_no+1] = ia[j][k];
        ele_no += 2;
      }
    }
    else if( ltp_val == 1 && lidp_val == 1 )
    {
      NL = static_cast<Integer>(ra[j].size()) - 1;
      NW = 3*NL+3;
      a_vec.resize(static_cast<int>(NW));

      int k_max = static_cast<int>(NL) + 1;
      for(int k=0; k<k_max; k++)
      {
        a_vec[k]             = b[j][k];
        a_vec[k_max + 2*k+0] = ra[j][k];
        a_vec[k_max + 2*k+1] = ia[j][k];
      }
    }
    else if( ltp_val == 2 )
    {
      NL = static_cast<int>(c[j].size()) - 1;
      NW = NL + 1;
      a_vec.resize(static_cast<int>(NW));

      int k_max = static_cast<int>(NL) + 1;
      for(int k=0; k<k_max; k++)
      {
        a_vec[k] = c[j][k];
      }
    }
    else if( ltp_val > 2 )
    {
      NL = static_cast<int>(mu[j].size());
      NW = 2*NL;
      a_vec.resize(static_cast<int>(NW));

      int k_max = static_cast<int>(NL);
      for(int k=0; k<k_max; k++)
      {
        a_vec[2*k+0] = mu[j][k];
        a_vec[2*k+1] = p[j][k];
      }
    }
    else
    {
      string class_name = "MF06Writer";
      string func_name  = "write_law07(int& i, vector<string>& text)";

      ostringstream oss00, oss01, oss02, oss03, oss04, oss05, oss06, oss07, oss08;
      oss00 << par_obj.get_mt_no();
      oss01 << i;
      oss02 << j;
      oss03 << j_max;
      oss04 << ltp_val;
      oss05 << lidp_val;
      string str_data00 = "Section number (MT) : " + oss00.str();
      string str_data01 = "NK                  : " + oss01.str();
      string str_data02 = "NE                  : " + oss02.str() + " / " + oss03.str();
      string str_data03 = "LTP                 : " + oss04.str();
      string str_data04 = "LIDP                : " + oss05.str();

      vector<string> err_com;
      err_com.push_back(str_data00);
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back(str_data04);
      err_com.push_back("These LIDP and LTP values at MF=06 are not supported in this program.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    str_vec = efw_obj.write_list(0.0, par_obj.get_E_LAW05()[i][j], ltp_val, 0, NW, NL, a_vec);
    for(int k=0; k<static_cast<int>(str_vec.size()); k++)
    {
      text.push_back(str_vec[k]);
    }
    clr_obj.clear_vec_array1_str(str_vec);
    a_vec.clear();
  }
  clr_obj.clear_vec_array2_real(b);
  clr_obj.clear_vec_array2_real(ra);
  clr_obj.clear_vec_array2_real(ia);
  clr_obj.clear_vec_array2_real(c);
  clr_obj.clear_vec_array2_real(mu);
  clr_obj.clear_vec_array2_real(p);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF06Writer::write_law07(int& i, vector<string>& text)
{
  vector<string> str_vec;

  Integer NR = static_cast<Integer>(par_obj.get_NBT_E_LAW07()[i].size());

  str_vec = efw_obj.write_tab2(0.0, 0.0, 0, 0, NR, par_obj.get_NE_LAW07()[i],
                               par_obj.get_NBT_E_LAW07()[i], par_obj.get_INT_E_LAW07()[i]);
  for(int j=0; j<static_cast<int>(str_vec.size()); j++)
  {
    text.push_back(str_vec[j]);
  }
  clr_obj.clear_vec_array1_str(str_vec);

  int j_max = static_cast<int>(par_obj.get_NE_LAW07()[i]);
  vector<vector<Integer> >          nbt_mu  = par_obj.get_NBT_MU_LAW07()[i];
  vector<vector<Integer> >          int_mu  = par_obj.get_INT_MU_LAW07()[i];
  vector<vector<vector<Integer> > > nbt_f   = par_obj.get_NBT_F_LAW07()[i];
  vector<vector<vector<Integer> > > int_f   = par_obj.get_INT_F_LAW07()[i];
  vector<vector<vector<Real> > >    e_int_f = par_obj.get_E_INT_F_LAW07()[i];
  vector<vector<vector<Real> > >    f_tab   = par_obj.get_F_TAB_LAW07()[i];
  for(int j=0; j<j_max; j++)
  {
    NR = static_cast<Integer>(nbt_mu[j].size());
    str_vec = efw_obj.write_tab2(0.0, par_obj.get_E_LAW07()[i][j], 0, 0, NR, par_obj.get_NMU_LAW07()[i][j],
                                 nbt_mu[j], int_mu[j]);
    for(int k=0; k<static_cast<int>(str_vec.size()); k++)
    {
      text.push_back(str_vec[k]);
    }
    clr_obj.clear_vec_array1_str(str_vec);

    int k_max = static_cast<int>(par_obj.get_NMU_LAW07()[i][j]);
    for(int k=0; k<k_max; k++)
    {
              NR = static_cast<Integer>(nbt_f[j][k].size());
      Integer NP = static_cast<Integer>(e_int_f[j][k].size());
      str_vec = efw_obj.write_tab1(0.0, par_obj.get_MU_LAW07()[i][j][k], 0, 0, NR, NP,
                                   nbt_f[j][k], int_f[j][k], e_int_f[j][k], f_tab[j][k]);
      for(int l=0; l<static_cast<int>(str_vec.size()); l++)
      {
        text.push_back(str_vec[l]);
      }
      clr_obj.clear_vec_array1_str(str_vec);
    }
  }
  clr_obj.clear_vec_array2_int(nbt_mu);
  clr_obj.clear_vec_array2_int(int_mu);
  clr_obj.clear_vec_array3_int(nbt_f);
  clr_obj.clear_vec_array3_int(int_f);
  clr_obj.clear_vec_array3_real(e_int_f);
  clr_obj.clear_vec_array3_real(f_tab);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF06Writer::write_thermal_scatter(vector<string>& text)
{
  if( par_obj.get_LCT() == 5 )
  {
    write_incoherent_inelastic_scatter(text);
  }
  else if( par_obj.get_LCT() == 6 )
  {
    write_incoherent_elastic_scatter(text);
  }
  else //par_obj.get_LCT() == 7
  {
    //Write coherent elastic scatter data
    string line_data;
    line_data = efw_obj.write_cont(par_obj.get_TEMP(), 0.0, 0, 0, 0, par_obj.get_NBRAGG());
    text.push_back(line_data);
    line_data.clear();
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF06Writer::write_incoherent_inelastic_scatter(vector<string>& text)
{
  vector<string>  str_vec;
  vector<Integer> nbt_vec, int_vec;
  vector<Real>    e_vec;
  nbt_vec.resize(1);
  int_vec.resize(1);
  nbt_vec[0] = par_obj.get_NNE();
  int_vec[0] = int_lin_lin;

  str_vec = efw_obj.write_tab2(par_obj.get_TEMP(), 0.0, 0, 0, 1, par_obj.get_NNE(), nbt_vec, int_vec);
  for(int i=0; i<static_cast<int>(str_vec.size()); i++)
  {
    text.push_back(str_vec[i]);
  }
  nbt_vec.clear();
  int_vec.clear();
  clr_obj.clear_vec_array1_str(str_vec);

  int i_max = static_cast<int>(par_obj.get_NNE());
  vector<vector<Real> >          ep  = par_obj.get_EP();
  vector<vector<Real> >          pp  = par_obj.get_PP();
  vector<vector<vector<Real> > > epm = par_obj.get_EPM();
  for(int i=0; i<i_max; i++)
  {
    Integer NEP = static_cast<Integer>(ep[i].size());
    Integer NLP = static_cast<Integer>(epm[i][0].size()) + 2;
    Integer NEP_NLP = NEP*NLP;
    e_vec.resize(static_cast<int>(NEP_NLP));
    int ele_no = 0;
    for(int j=0; j<static_cast<int>(NEP); j++)
    {
      e_vec[ele_no]   = ep[i][j];
      e_vec[ele_no+1] = pp[i][j];
      ele_no += 2;
      for(int k=0; k<static_cast<int>(NLP-2); k++)
      {
        e_vec[ele_no] = epm[i][j][k];
        ele_no++;
      }
    }

    str_vec = efw_obj.write_list(0.0, par_obj.get_EN()[i], 0, 0, NEP_NLP, NLP, e_vec);
    for(int j=0; j<static_cast<int>(str_vec.size()); j++)
    {
      text.push_back(str_vec[j]);
    }
    e_vec.clear();
    clr_obj.clear_vec_array1_str(str_vec);
  }
  clr_obj.clear_vec_array2_real(ep);
  clr_obj.clear_vec_array2_real(pp);
  clr_obj.clear_vec_array3_real(epm);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF06Writer::write_incoherent_elastic_scatter(vector<string>& text)
{
  vector<string>  str_vec;
  vector<Integer> nbt_vec, int_vec;
  vector<Real>    e_vec;
  nbt_vec.resize(1);
  int_vec.resize(1);
  nbt_vec[0] = par_obj.get_NNE();
  int_vec[0] = int_lin_lin;

  str_vec = efw_obj.write_tab2(par_obj.get_TEMP(), 0.0, 0, 0, 1, par_obj.get_NNE(), nbt_vec, int_vec);
  for(int i=0; i<static_cast<int>(str_vec.size()); i++)
  {
    text.push_back(str_vec[i]);
  }
  nbt_vec.clear();
  int_vec.clear();
  clr_obj.clear_vec_array1_str(str_vec);

  int i_max = static_cast<int>(par_obj.get_NNE());
  vector<vector<Real> > u = par_obj.get_U();
  for(int i=0; i<i_max; i++)
  {
    Integer NU = static_cast<Integer>(u[i].size()) + 2;
    Real    EN = par_obj.get_EN()[i];
    e_vec.resize(static_cast<int>(NU));
    e_vec[0] = EN;
    e_vec[1] = 1.0;
    for(int j=0; j<static_cast<int>(NU-2); j++)
    {
      e_vec[j+2] = u[i][j];
    }

    str_vec = efw_obj.write_list(0.0, EN, 0, 0, NU, NU, e_vec);
    for(int j=0; j<static_cast<int>(str_vec.size()); j++)
    {
      text.push_back(str_vec[j]);
    }
    e_vec.clear();
    clr_obj.clear_vec_array1_str(str_vec);
  }
  clr_obj.clear_vec_array2_real(u);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF06Writer::clear()
{
  clr_obj.clear_vec_array1_str(text);

  par_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> MF06Writer::get_endf_text_data(frendy::MF06Parser& mf06parser_obj)
{
  clear();
  par_obj = mf06parser_obj;

  write_endf();
  return text;
}
