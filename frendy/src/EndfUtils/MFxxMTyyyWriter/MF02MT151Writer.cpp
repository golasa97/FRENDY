#include "EndfUtils/MFxxMTyyyWriter/MF02MT151Writer.hpp"

using namespace frendy;

//constructor
MF02MT151Writer::MF02MT151Writer(void)
{
  clear();
}

//destructor
MF02MT151Writer::~MF02MT151Writer(void)
{ 
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF02MT151Writer::write_endf() 
{
  clr_obj.clear_vec_array1_str(text);

  string line_data;
  efw_obj.set_mat_mf_mt(par_obj.get_mat_no(), mf_no, mt_no);

  //Line No.01
  //ZA, AWR, NIS
  line_data = efw_obj.write_cont(par_obj.get_ZAR(), par_obj.get_AWR(), 0, 0, par_obj.get_NIS(), 0);
  text.push_back(line_data);

  int i_max = static_cast<int>(par_obj.get_NIS());
  for(int i=0; i<i_max; i++)
  {
    line_data = efw_obj.write_cont(par_obj.get_ZAI()[i], par_obj.get_ABN()[i], 0, 
                                   par_obj.get_LFW()[i], par_obj.get_NER()[i], 0);
    text.push_back(line_data);

    int j_max = static_cast<int>(par_obj.get_NER()[i]);
    vector<Real>    el   = par_obj.get_EL()[i];
    vector<Real>    eh   = par_obj.get_EH()[i];
    vector<Integer> lru  = par_obj.get_LRU()[i];
    vector<Integer> lrf  = par_obj.get_LRF()[i];
    vector<Integer> nro  = par_obj.get_NRO()[i];
    vector<Integer> naps = par_obj.get_NAPS()[i];
  
    for(int j=0; j<j_max; j++)
    {
      line_data = efw_obj.write_cont(el[j], eh[j], lru[j], lrf[j], nro[j], naps[j]);
      text.push_back(line_data);

      if( lru[j] == 0 ) 
      {
        write_lru00(i, j);
      }
      else if( lru[j] == 1 )
      {
        if( lrf[j] == 1 || lrf[j] == 2 )
        {
          write_lru01_lrf01_02(i, j);
        }
        else if( lrf[j] == 3 )
        {
          write_lru01_lrf03(i, j);
        }
        else if( lrf[j] == 4 )
        {
          write_lru01_lrf04(i, j);
        }
        else if( lrf[j] == 7 )
        {
          write_lru01_lrf07(i, j);
        }
        else
        {
          string class_name = "MF02MT151Writer";
          string func_name  = "write_endf()";

          ostringstream oss01, oss02, oss03, oss04, oss05;
          oss01 << i+1;
          oss02 << static_cast<int>(par_obj.get_NIS());
          oss03 << j+1;
          oss04 << static_cast<int>(par_obj.get_NER()[i]);
          oss05 << lrf[j];
          string str_data01 = "NIS : " + oss01.str() + " / " + oss02.str();
          string str_data02 = "NER : " + oss03.str() + " / " + oss04.str();
          string str_data03 = "LRF : " + oss05.str();

          vector<string> err_com;
          err_com.push_back(str_data01);
          err_com.push_back(str_data02);
          err_com.push_back(str_data03);
          if( lrf[j] == 5 || lrf[j] == 6 )
          {
            err_com.push_back("The format of LRF=5 or 6 at MF=02, MT=151 is no longer available in ENDF-6.");
          }
          else
          {
            err_com.push_back("This LRF value at MF=02, MT=151 is not supported in this writer program.");
            err_com.push_back("Supportes LRF value is 1 - 4 and 7.");
          }

          err_obj.output_runtime_error(class_name, func_name, err_com);
        }
      }
      else if( lru[j] == 2 )
      {
        write_lru02(i, j);
      }
      else
      {
        string class_name = "MF02MT151Writer";
        string func_name  = "write_endf()";

        ostringstream oss01, oss02, oss03, oss04, oss05;
        oss01 << i+1;
        oss02 << static_cast<int>(par_obj.get_NIS());
        oss03 << j+1;
        oss04 << static_cast<int>(par_obj.get_NER()[i]);
        oss05 << lru[j];
        string str_data01 = "NIS : " + oss01.str() + " / " + oss02.str();
        string str_data02 = "NER : " + oss03.str() + " / " + oss04.str();
        string str_data03 = "LRU : " + oss05.str();

        vector<string> err_com;
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back("This LRU value at MF=02, MT=151 is not supported in this writer program.");
        err_com.push_back("Supported LRU value is 0 - 2.");

        err_obj.output_runtime_error(class_name, func_name, err_com);
      }
    }
    el.clear();
    eh.clear();
    lru.clear();
    lrf.clear();
    nro.clear();
    naps.clear();
  }
  line_data = efw_obj.write_mt_end();
  text.push_back(line_data);
  line_data.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF02MT151Writer::write_lru00(int& i, int& j)
{
  if( par_obj.get_LFW()[j]    == 0 && par_obj.get_LRF()[i][j]  == 0 && 
      par_obj.get_NRO()[i][j] == 0 && par_obj.get_NAPS()[i][j] == 0 )
  {
    string line_data = efw_obj.write_cont(par_obj.get_SPI()[i][j], par_obj.get_AP()[i][j],  0, 0,
                                          par_obj.get_NLS()[i][j], 0);
    text.push_back(line_data);
    line_data.clear();
  }
  else if( par_obj.get_NRO()[i][j] > 0 )
  {
    write_nro(i, j);
  }
  else
  {
    string class_name = "MF02MT151Writer";
    string func_name  = "write_lru00(int& i, int& j)";

    ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07, oss08;
    oss01 << i+1;
    oss02 << static_cast<int>(par_obj.get_NIS());
    oss03 << j+1;
    oss04 << static_cast<int>(par_obj.get_NER()[i]);
    oss05 << par_obj.get_LFW()[i];
    oss06 << par_obj.get_LRF()[i][j];
    oss07 << par_obj.get_NRO()[i][j];
    oss08 << par_obj.get_NAPS()[i][j];
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
    err_com.push_back("The format of LRU = 0 at MF=02, MT=151 has something trouble.");
    err_com.push_back("Please check LFW, NER, LRF, NRO and NAPS in writer class.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF02MT151Writer::write_lru01_lrf01_02(int& i, int& j)
{
  string line_data;
  vector<string> str_vec;

  if( par_obj.get_NRO()[i][j] != 0 )
  {
    write_nro(i, j);
  }

  line_data = efw_obj.write_cont(par_obj.get_SPI()[i][j], par_obj.get_AP()[i][j], 0, 0,
                                 par_obj.get_NLS()[i][j], 0);
  text.push_back(line_data);

  int k_max = static_cast<int>(par_obj.get_NLS()[i][j]);
  vector<vector<Real> > er = par_obj.get_ER_LRU01_LRF01()[i][j];
  vector<vector<Real> > aj = par_obj.get_AJ_LRU01_LRF01()[i][j];
  vector<vector<Real> > gt = par_obj.get_GT_LRU01_LRF01()[i][j];
  vector<vector<Real> > gn = par_obj.get_GN_LRU01_LRF01()[i][j];
  vector<vector<Real> > gg = par_obj.get_GG_LRU01_LRF01()[i][j];
  vector<vector<Real> > gf = par_obj.get_GF_LRU01_LRF01()[i][j];
  for(int k=0; k<k_max; k++)
  {
    vector<Real> real_vec;
    int l_max = static_cast<int>(par_obj.get_NRS_LRU01_LRF01()[i][j][k]);
    real_vec.resize(6*l_max);
    for(int l=0; l<l_max; l++)
    {
      real_vec[6*l+0] = er[k][l];
      real_vec[6*l+1] = aj[k][l];
      real_vec[6*l+2] = gt[k][l];
      real_vec[6*l+3] = gn[k][l];
      real_vec[6*l+4] = gg[k][l];
      real_vec[6*l+5] = gf[k][l];
    }

    str_vec = efw_obj.write_list(par_obj.get_AWRI()[i][j][k], par_obj.get_QX_LRU01_LRF01()[i][j][k],
                                 par_obj.get_L_LRU01_LRF01()[i][j][k], par_obj.get_LRX_LRU01_LRF01()[i][j][k],
                                 static_cast<Integer>(real_vec.size()), par_obj.get_NRS_LRU01_LRF01()[i][j][k],
                                 real_vec);
    l_max = static_cast<int>(str_vec.size());
    for(int l=0; l<l_max; l++)
    {
      text.push_back(str_vec[l]);
    }
    real_vec.clear();
  }
  line_data.clear();
  clr_obj.clear_vec_array1_str(str_vec);
  clr_obj.clear_vec_array2_real(er);
  clr_obj.clear_vec_array2_real(aj);
  clr_obj.clear_vec_array2_real(gt);
  clr_obj.clear_vec_array2_real(gn);
  clr_obj.clear_vec_array2_real(gg);
  clr_obj.clear_vec_array2_real(gf);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF02MT151Writer::write_lru01_lrf03(int& i, int& j)
{
  string line_data;
  vector<string> str_vec;

  if( par_obj.get_NRO()[i][j] != 0 )
  {
    write_nro(i, j);
  }

  line_data = efw_obj.write_cont(par_obj.get_SPI()[i][j], par_obj.get_AP()[i][j], 
                                 par_obj.get_LAD_LRU01_LRF03()[i][j], 0, par_obj.get_NLS()[i][j], 
                                 par_obj.get_NLSC_LRU01_LRF03()[i][j]);
  text.push_back(line_data);

  int k_max = static_cast<int>(par_obj.get_NLS()[i][j]);
  vector<vector<Real> > er  = par_obj.get_ER_LRU01_LRF03()[i][j];
  vector<vector<Real> > aj  = par_obj.get_AJ_LRU01_LRF03()[i][j];
  vector<vector<Real> > gn  = par_obj.get_GN_LRU01_LRF03()[i][j];
  vector<vector<Real> > gg  = par_obj.get_GG_LRU01_LRF03()[i][j];
  vector<vector<Real> > gfa = par_obj.get_GFA_LRU01_LRF03()[i][j];
  vector<vector<Real> > gfb = par_obj.get_GFB_LRU01_LRF03()[i][j];
  for(int k=0; k<k_max; k++)
  {
    vector<Real> real_vec;
    int l_max = static_cast<int>(par_obj.get_NRS_LRU01_LRF03()[i][j][k]);
    real_vec.resize(6*l_max);
    for(int l=0; l<l_max; l++)
    {
      real_vec[6*l+0] = er[k][l];
      real_vec[6*l+1] = aj[k][l];
      real_vec[6*l+2] = gn[k][l];
      real_vec[6*l+3] = gg[k][l];
      real_vec[6*l+4] = gfa[k][l];
      real_vec[6*l+5] = gfb[k][l];
    }

    str_vec = efw_obj.write_list(par_obj.get_AWRI()[i][j][k], par_obj.get_APL_LRU01_LRF03()[i][j][k],
                                 par_obj.get_L_LRU01_LRF03()[i][j][k], 0,
                                 static_cast<Integer>(real_vec.size()), par_obj.get_NRS_LRU01_LRF03()[i][j][k],
                                 real_vec);
    l_max = static_cast<int>(str_vec.size());
    for(int l=0; l<l_max; l++)
    {
      text.push_back(str_vec[l]);
    }
    real_vec.clear();
  }
  line_data.clear();
  clr_obj.clear_vec_array1_str(str_vec);
  clr_obj.clear_vec_array2_real(er);
  clr_obj.clear_vec_array2_real(aj);
  clr_obj.clear_vec_array2_real(gn);
  clr_obj.clear_vec_array2_real(gg);
  clr_obj.clear_vec_array2_real(gfa);
  clr_obj.clear_vec_array2_real(gfb);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF02MT151Writer::write_lru01_lrf04(int& i, int& j)
{
  string line_data;
  vector<string> str_vec;

  //if( par_obj.get_NRO()[i][j] != 0 )
  //{
    write_nro(i, j);
  //}

  int k_max = static_cast<int>(str_vec.size());
  for(int k=0; k<k_max; k++)
  {
    text.push_back(str_vec[k]);
  }

  line_data = efw_obj.write_cont(par_obj.get_SPI()[i][j], par_obj.get_AP()[i][j], 
                                 0, 0, par_obj.get_NLS()[i][j], 0);
  text.push_back(line_data);

  vector<Real> real_vec;
  k_max = static_cast<int>(par_obj.get_NX_LRU01_LRF04()[i][j]);
  vector<Real> at = par_obj.get_AT_LRU01_LRF04()[i][j];
  vector<Real> af = par_obj.get_AF_LRU01_LRF04()[i][j];
  vector<Real> ac = par_obj.get_AC_LRU01_LRF04()[i][j];
  real_vec.resize(6*k_max);
  if( k_max > 0 )
  {
    for(int k=0; k<6; k++)
    {
      real_vec[k] = at[k];
    }
  }
  if( k_max > 1 )
  {
    for(int k=0; k<6; k++)
    {
      real_vec[6+k] = af[k];
    }
  }
  if( k_max > 2 )
  {
    for(int k=0; k<6; k++)
    {
      real_vec[12+k] = ac[k];
    }
  }
  at.clear();
  af.clear();
  ac.clear();

  str_vec = efw_obj.write_list(par_obj.get_AWRI()[i][j][0], 0.0, par_obj.get_LI_LRU01_LRF04()[i][j],
                               0, static_cast<Integer>(real_vec.size()), par_obj.get_NX_LRU01_LRF04()[i][j],
                               real_vec);
  k_max = static_cast<int>(str_vec.size());
  for(int k=0; k<k_max; k++)
  {
    text.push_back(str_vec[k]);
  }
  real_vec.clear();
  
  k_max = static_cast<int>(par_obj.get_NLS()[i][j]);
  vector<vector<vector<Real> > > det = par_obj.get_DET_LRU01_LRF04()[i][j];
  vector<vector<vector<Real> > > dwt = par_obj.get_DWT_LRU01_LRF04()[i][j];
  vector<vector<vector<Real> > > grt = par_obj.get_GRT_LRU01_LRF04()[i][j];
  vector<vector<vector<Real> > > git = par_obj.get_GIT_LRU01_LRF04()[i][j];
  vector<vector<vector<Real> > > def = par_obj.get_DEF_LRU01_LRF04()[i][j];
  vector<vector<vector<Real> > > dwf = par_obj.get_DWF_LRU01_LRF04()[i][j];
  vector<vector<vector<Real> > > grf = par_obj.get_GRF_LRU01_LRF04()[i][j];
  vector<vector<vector<Real> > > gif = par_obj.get_GIF_LRU01_LRF04()[i][j];
  vector<vector<vector<Real> > > dec = par_obj.get_DEC_LRU01_LRF04()[i][j];
  vector<vector<vector<Real> > > dwc = par_obj.get_DWC_LRU01_LRF04()[i][j];
  vector<vector<vector<Real> > > grc = par_obj.get_GRC_LRU01_LRF04()[i][j];
  vector<vector<vector<Real> > > gic = par_obj.get_GIC_LRU01_LRF04()[i][j];
  for(int k=0; k<k_max; k++)
  {
    line_data = efw_obj.write_cont(0.0, 0.0, par_obj.get_L_LRU01_LRF04()[i][j][k], 0, 
                                             par_obj.get_NJS_LRU01_LRF04()[i][j][k],  0);
    text.push_back(line_data);

    int l_max = static_cast<int>(par_obj.get_NJS_LRU01_LRF04()[i][j][k]);
    for(int l=0; l<l_max; l++)
    {
      int m_max = static_cast<int>(par_obj.get_NLJ_LRU01_LRF04()[i][j][k][l]);
      real_vec.resize(m_max*12);
      for(int m=0; m<m_max; m++)
      {
        real_vec[12*m+ 0] = det[k][l][m];
        real_vec[12*m+ 1] = dwt[k][l][m];
        real_vec[12*m+ 2] = grt[k][l][m];
        real_vec[12*m+ 3] = git[k][l][m];
        real_vec[12*m+ 4] = def[k][l][m];
        real_vec[12*m+ 5] = dwf[k][l][m];
        real_vec[12*m+ 6] = grf[k][l][m];
        real_vec[12*m+ 7] = gif[k][l][m];
        real_vec[12*m+ 8] = dec[k][l][m];
        real_vec[12*m+ 9] = dwc[k][l][m];
        real_vec[12*m+10] = grc[k][l][m];
        real_vec[12*m+11] = gic[k][l][m];
      }
      str_vec = efw_obj.write_list(par_obj.get_AJ_LRU01_LRF04()[i][j][k][l], 0.0, 0, 0,
                  static_cast<Integer>(real_vec.size()), par_obj.get_NLJ_LRU01_LRF04()[i][j][k][l], real_vec);
      m_max = static_cast<int>(str_vec.size());
      for(int m=0; m<m_max; m++)
      {
        text.push_back(str_vec[m]);
      }
      real_vec.clear();
    }
  }
  line_data.clear();
  clr_obj.clear_vec_array1_str(str_vec);
  clr_obj.clear_vec_array3_real(det);
  clr_obj.clear_vec_array3_real(dwt);
  clr_obj.clear_vec_array3_real(grt);
  clr_obj.clear_vec_array3_real(git);
  clr_obj.clear_vec_array3_real(def);
  clr_obj.clear_vec_array3_real(dwf);
  clr_obj.clear_vec_array3_real(grf);
  clr_obj.clear_vec_array3_real(gif);
  clr_obj.clear_vec_array3_real(dec);
  clr_obj.clear_vec_array3_real(dwc);
  clr_obj.clear_vec_array3_real(grc);
  clr_obj.clear_vec_array3_real(gic);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF02MT151Writer::write_lru01_lrf07(int& i, int& j)
{
  string line_data;
  vector<string> str_vec;

  line_data = efw_obj.write_cont(0.0, 0.0,
                                 par_obj.get_IFG_LRU01_LRF07()[i][j], par_obj.get_KRM_LRU01_LRF07()[i][j],
                                 par_obj.get_NJS_LRU01_LRF07()[i][j], par_obj.get_KRL_LRU01_LRF07()[i][j]);
  text.push_back(line_data);

  if( par_obj.get_KRM_LRU01_LRF07()[i][j] == 1 || par_obj.get_KRM_LRU01_LRF07()[i][j] == 2
   || par_obj.get_KRM_LRU01_LRF07()[i][j] == 3 ) 
  {
    Integer NPP = par_obj.get_NPP_LRU01_LRF07()[i][j];

    vector<Real> real_vec;
    int k_max = static_cast<int>(NPP);
    real_vec.resize(k_max*12);
    vector<Real> ma  = par_obj.get_MA_LRU01_LRF07()[i][j];
    vector<Real> mb  = par_obj.get_MB_LRU01_LRF07()[i][j];
    vector<Real> za  = par_obj.get_ZA_LRU01_LRF07()[i][j];
    vector<Real> zb  = par_obj.get_ZB_LRU01_LRF07()[i][j];
    vector<Real> ia  = par_obj.get_IA_LRU01_LRF07()[i][j];
    vector<Real> ib  = par_obj.get_IB_LRU01_LRF07()[i][j];
    vector<Real> q   = par_obj.get_Q_LRU01_LRF07()[i][j];
    vector<Real> pnt = par_obj.get_PNT_LRU01_LRF07()[i][j];
    vector<Real> shf = par_obj.get_SHF_LRU01_LRF07()[i][j];
    vector<Real> mt  = par_obj.get_MT_LRU01_LRF07()[i][j];
    vector<Real> pa  = par_obj.get_PA_LRU01_LRF07()[i][j];
    vector<Real> pb  = par_obj.get_PB_LRU01_LRF07()[i][j];
    for(int k=0; k<k_max; k++)
    {
      real_vec[12*k+ 0] = ma[k];
      real_vec[12*k+ 1] = mb[k];
      real_vec[12*k+ 2] = za[k];
      real_vec[12*k+ 3] = zb[k];
      real_vec[12*k+ 4] = ia[k];
      real_vec[12*k+ 5] = ib[k];
      real_vec[12*k+ 6] = q[k];
      real_vec[12*k+ 7] = pnt[k];
      real_vec[12*k+ 8] = shf[k];
      real_vec[12*k+ 9] = mt[k];
      real_vec[12*k+10] = pa[k];
      real_vec[12*k+11] = pb[k];
    }
    str_vec = efw_obj.write_list(0.0, 0.0, NPP, 0, 12*NPP, 2*NPP, real_vec);
    k_max = static_cast<int>(str_vec.size());
    for(int k=0; k<k_max; k++)
    {
      text.push_back(str_vec[k]);
    }
    real_vec.clear();
    ma.clear();
    mb.clear();
    za.clear();
    zb.clear();
    ia.clear();
    ib.clear();
    q.clear();
    pnt.clear();
    shf.clear();
    mt.clear();
    pa.clear();
    pb.clear();
  }

  int k_max = static_cast<int>(par_obj.get_NJS_LRU01_LRF07()[i][j]);
  vector<vector<Real> > ppi   = par_obj.get_PPI_LRU01_LRF07()[i][j];
  vector<vector<Real> > l_vec = par_obj.get_L_LRU01_LRF07()[i][j];
  vector<vector<Real> > sch   = par_obj.get_SCH_LRU01_LRF07()[i][j];
  vector<vector<Real> > bnd   = par_obj.get_BND_LRU01_LRF07()[i][j];
  vector<vector<Real> > ape   = par_obj.get_APE_LRU01_LRF07()[i][j];
  vector<vector<Real> > apt   = par_obj.get_APT_LRU01_LRF07()[i][j];
  vector<vector<Real> > er    = par_obj.get_ER_LRU01_LRF07()[i][j];
  vector<vector<vector<Real> > > gam = par_obj.get_GAM_LRU01_LRF07()[i][j];
  for(int k=0; k<k_max; k++)
  {
    vector<Real> real_vec;
    int l_max = static_cast<int>(par_obj.get_NCH_LRU01_LRF07()[i][j][k]);
    real_vec.resize(l_max*6);
    for(int l=0; l<l_max; l++)
    {
      real_vec[6*l+0] = ppi[k][l];
      real_vec[6*l+1] = l_vec[k][l];
      real_vec[6*l+2] = sch[k][l];
      real_vec[6*l+3] = bnd[k][l];
      real_vec[6*l+4] = ape[k][l];
      real_vec[6*l+5] = apt[k][l];
    }
    str_vec = efw_obj.write_list(par_obj.get_AJ_LRU01_LRF07()[i][j][k],  par_obj.get_PJ_LRU01_LRF07()[i][j][k],
                                 par_obj.get_KBK_LRU01_LRF07()[i][j][k], par_obj.get_KPS_LRU01_LRF07()[i][j][k],
                                 static_cast<Integer>(real_vec.size()),  par_obj.get_NCH_LRU01_LRF07()[i][j][k],
                                 real_vec);
    l_max = static_cast<int>(str_vec.size());
    for(int l=0; l<l_max; l++)
    {
      text.push_back(str_vec[l]);
    }
    real_vec.clear();

    int ele_no = 0;
    l_max = static_cast<int>(par_obj.get_NRS_LRU01_LRF07()[i][j][k]);
    for(int l=0; l<l_max; l++)
    {
      int m_max = static_cast<int>(par_obj.get_NCH_LRU01_LRF07()[i][j][k]);

      real_vec.push_back(er[k][l]);
      ele_no++;
      for(int m=0; m<m_max; m++)
      {
        real_vec.push_back(gam[k][l][m]);
        ele_no++;
      }

      while(ele_no%6 != 0 )
      {
        real_vec.push_back(0.0);
        ele_no++;
      }
    }
    str_vec = efw_obj.write_list(0.0, 0.0, 0,
                                 par_obj.get_NRS_LRU01_LRF07()[i][j][k], static_cast<Integer>(real_vec.size()),
                                 static_cast<Integer>(real_vec.size()/6),  real_vec);
    l_max = static_cast<int>(str_vec.size());
    for(int l=0; l<l_max; l++)
    {
      text.push_back(str_vec[l]);
    }
    real_vec.clear();

    if( par_obj.get_KBK_LRU01_LRF07()[i][j][k] > 0 )
    {
      if( par_obj.get_LCH_LRU01_LRF07()[i][j][k] == 0 )
      {
        write_lru01_lrf07_kbk_b80(i, j, k);
      }
      else if( par_obj.get_LCH_LRU01_LRF07()[i][j][k] > 0 )
      {
        write_lru01_lrf07_kbk_b81(i, j, k);
      }
      else
      {
        string class_name = "MF02MT151Writer";
        string func_name  = "write_lru01_lrf07(int& i, int& j)";

        ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07, oss08;
        oss01 << i+1;
        oss02 << static_cast<int>(par_obj.get_NIS());
        oss03 << j+1;
        oss04 << static_cast<int>(par_obj.get_NER()[i]);
        oss05 << k+1;
        oss06 << static_cast<int>(par_obj.get_NJS_LRU01_LRF07()[i][j]);
        oss07 << par_obj.get_LCH_LRU01_LRF07()[i][j][k];
        oss08 << par_obj.get_LBK_LRU01_LRF07()[i][j][k];
        string str_data01 = "NIS  : " + oss01.str() + " / " + oss02.str();
        string str_data02 = "NER  : " + oss03.str() + " / " + oss04.str();
        string str_data03 = "NJS  : " + oss05.str() + " / " + oss06.str();
        string str_data04 = "LCH  : " + oss07.str();
        string str_data05 = "LBK  : " + oss08.str();

        vector<string> err_com;
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back(str_data04);
        err_com.push_back(str_data05);
        err_com.push_back("This LCH value at MF=02, MT=151 is not supported in this writer program.");
        err_com.push_back("Supported LCH value is zero (for ENDF/B-VIII.0) and larger than 1 (for ENDF/B-VIII.1).");

        err_obj.output_runtime_error(class_name, func_name, err_com);
      }
    }

    if( par_obj.get_KPS_LRU01_LRF07()[i][j][k] == 1 )
    {
      write_lru01_lrf07_kps(i, j, k);
    }
  }
  line_data.clear();
  clr_obj.clear_vec_array1_str(str_vec);
  clr_obj.clear_vec_array2_real(ppi);
  clr_obj.clear_vec_array2_real(l_vec);
  clr_obj.clear_vec_array2_real(sch);
  clr_obj.clear_vec_array2_real(bnd);
  clr_obj.clear_vec_array2_real(ape);
  clr_obj.clear_vec_array2_real(apt);
  clr_obj.clear_vec_array2_real(er);
  clr_obj.clear_vec_array3_real(gam);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF02MT151Writer::write_lru01_lrf07_kbk_b80(int& i, int& j, int& k)
{
  string         line_data;
  vector<string> str_vec;

  if( par_obj.get_LBK_LRU01_LRF07()[i][j][k] == 0 )
  {
    line_data = efw_obj.write_cont(0.0, 0.0, 0, 0, par_obj.get_LBK_LRU01_LRF07()[i][j][k], 1);
    text.push_back(line_data);
    line_data = efw_obj.write_cont_real(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    text.push_back(line_data);
  }
  else if( par_obj.get_LBK_LRU01_LRF07()[i][j][k] == 1 )
  {
    line_data = efw_obj.write_cont(0.0, 0.0, 0, 0, par_obj.get_LBK_LRU01_LRF07()[i][j][k], 1);
    text.push_back(line_data);
    line_data = efw_obj.write_cont_real(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    text.push_back(line_data);

    Integer NR = static_cast<Integer>(par_obj.get_NBT_RBR_LRU01_LRF07()[i][j][k].size());
    Integer NP = static_cast<Integer>(par_obj.get_E_INT_RBR_LRU01_LRF07()[i][j][k].size());

    str_vec = efw_obj.write_tab1(0.0, 0.0, 0, 0, NR, NP,
                      par_obj.get_NBT_RBR_LRU01_LRF07()[i][j][k],   par_obj.get_INT_RBR_LRU01_LRF07()[i][j][k],
                      par_obj.get_E_INT_RBR_LRU01_LRF07()[i][j][k], par_obj.get_RBR_TAB_LRU01_LRF07()[i][j][k]);
    int l_max = static_cast<int>(str_vec.size());
    for(int l=0; l<l_max; l++)
    {
      text.push_back(str_vec[l]);
    }

    NR = par_obj.get_NBT_RBI_LRU01_LRF07()[i][j][k].size();
    NP = par_obj.get_E_INT_RBI_LRU01_LRF07()[i][j][k].size();

    str_vec = efw_obj.write_tab1(0.0, 0.0, 0, 0, NR, NP,
                      par_obj.get_NBT_RBI_LRU01_LRF07()[i][j][k],   par_obj.get_INT_RBI_LRU01_LRF07()[i][j][k],
                      par_obj.get_E_INT_RBI_LRU01_LRF07()[i][j][k], par_obj.get_RBI_TAB_LRU01_LRF07()[i][j][k]);
    l_max = static_cast<int>(str_vec.size());
    for(int l=0; l<l_max; l++)
    {
      text.push_back(str_vec[l]);
    }
  }
  else if( par_obj.get_LBK_LRU01_LRF07()[i][j][k] == 2 )
  {
    line_data = efw_obj.write_cont(par_obj.get_ED_LRU01_LRF07()[i][j][k], par_obj.get_EU_LRU01_LRF07()[i][j][k],
                                    0, 0, par_obj.get_LBK_LRU01_LRF07()[i][j][k], 1);
    text.push_back(line_data);
    line_data = efw_obj.write_cont_real(
                         par_obj.get_R0_LRU01_LRF07()[i][j][k], par_obj.get_R1_LRU01_LRF07()[i][j][k],
                         par_obj.get_R2_LRU01_LRF07()[i][j][k], par_obj.get_S0_LRU01_LRF07()[i][j][k],
                         par_obj.get_S1_LRU01_LRF07()[i][j][k], 0.0);
    text.push_back(line_data);
  }
  else if( par_obj.get_LBK_LRU01_LRF07()[i][j][k] == 3 )
  {
    line_data = efw_obj.write_cont(par_obj.get_ED_LRU01_LRF07()[i][j][k], par_obj.get_EU_LRU01_LRF07()[i][j][k],
                                    0, 0, par_obj.get_LBK_LRU01_LRF07()[i][j][k], 1);
    text.push_back(line_data);
    line_data = efw_obj.write_cont_real(
                          par_obj.get_R0_LRU01_LRF07()[i][j][k], par_obj.get_S0_LRU01_LRF07()[i][j][k],
                          par_obj.get_GA_LRU01_LRF07()[i][j][k], 0.0, 0.0, 0.0);
    text.push_back(line_data);
  }
  else
  {
    string class_name = "MF02MT151Writer";
    string func_name  = "write_lru01_lrf07_kbk_b80(int& i, int& j, int& k)";

    ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07;
    oss01 << i+1;
    oss02 << static_cast<int>(par_obj.get_NIS());
    oss03 << j+1;
    oss04 << static_cast<int>(par_obj.get_NER()[i]);
    oss05 << k+1;
    oss06 << static_cast<int>(par_obj.get_NJS_LRU01_LRF07()[i][j]);
    oss07 << par_obj.get_LBK_LRU01_LRF07()[i][j][k];
    string str_data01 = "NIS  : " + oss01.str() + " / " + oss02.str();
    string str_data02 = "NER  : " + oss03.str() + " / " + oss04.str();
    string str_data03 = "NJS  : " + oss05.str() + " / " + oss06.str();
    string str_data04 = "LBK  : " + oss07.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back("This LBK value at MF=02, MT=151 is not supported in this writer program.");
    err_com.push_back("Supported LBK value is 0 - 3.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
  line_data.clear();
  clr_obj.clear_vec_array1_str(str_vec);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF02MT151Writer::write_lru01_lrf07_kbk_b81(int& i, int& j, int& k)
{
  string         line_data;
  vector<string> str_vec;

  line_data = efw_obj.write_cont(0.0, 0.0, par_obj.get_LCH_LRU01_LRF07()[i][j][k],
                                           par_obj.get_LBK_LRU01_LRF07()[i][j][k], 0, 0);
  text.push_back(line_data);

  if( par_obj.get_LBK_LRU01_LRF07()[i][j][k] == 1 )
  {
    Integer NR = static_cast<Integer>(par_obj.get_NBT_RBR_LRU01_LRF07()[i][j][k].size());
    Integer NP = static_cast<Integer>(par_obj.get_E_INT_RBR_LRU01_LRF07()[i][j][k].size());

    str_vec = efw_obj.write_tab1(0.0, 0.0, 0, 0, NR, NP,
                      par_obj.get_NBT_RBR_LRU01_LRF07()[i][j][k],   par_obj.get_INT_RBR_LRU01_LRF07()[i][j][k],
                      par_obj.get_E_INT_RBR_LRU01_LRF07()[i][j][k], par_obj.get_RBR_TAB_LRU01_LRF07()[i][j][k]);
    int l_max = static_cast<int>(str_vec.size());
    for(int l=0; l<l_max; l++)
    {
      text.push_back(str_vec[l]);
    }

    NR = par_obj.get_NBT_RBI_LRU01_LRF07()[i][j][k].size();
    NP = par_obj.get_E_INT_RBI_LRU01_LRF07()[i][j][k].size();

    str_vec = efw_obj.write_tab1(0.0, 0.0, 0, 0, NR, NP,
                      par_obj.get_NBT_RBI_LRU01_LRF07()[i][j][k],   par_obj.get_INT_RBI_LRU01_LRF07()[i][j][k],
                      par_obj.get_E_INT_RBI_LRU01_LRF07()[i][j][k], par_obj.get_RBI_TAB_LRU01_LRF07()[i][j][k]);
    l_max = static_cast<int>(str_vec.size());
    for(int l=0; l<l_max; l++)
    {
      text.push_back(str_vec[l]);
    }
  }
  else if( par_obj.get_LBK_LRU01_LRF07()[i][j][k] == 2 )
  {
    vector<Real> real_vec;
    real_vec.resize(5);
    real_vec[0] = par_obj.get_R0_LRU01_LRF07()[i][j][k];
    real_vec[1] = par_obj.get_R1_LRU01_LRF07()[i][j][k];
    real_vec[2] = par_obj.get_R2_LRU01_LRF07()[i][j][k];
    real_vec[3] = par_obj.get_S0_LRU01_LRF07()[i][j][k];
    real_vec[4] = par_obj.get_S1_LRU01_LRF07()[i][j][k];
    str_vec = efw_obj.write_list(par_obj.get_ED_LRU01_LRF07()[i][j][k], par_obj.get_EU_LRU01_LRF07()[i][j][k],
                                 0, 0, static_cast<Integer>(real_vec.size()), 0, real_vec);
    int l_max = static_cast<int>(str_vec.size());
    for(int l=0; l<l_max; l++)
    {
      text.push_back(str_vec[l]);
    }
  }
  else if( par_obj.get_LBK_LRU01_LRF07()[i][j][k] == 3 )
  {
    vector<Real> real_vec;
    real_vec.resize(3);
    real_vec[0] = par_obj.get_R0_LRU01_LRF07()[i][j][k];
    real_vec[1] = par_obj.get_S0_LRU01_LRF07()[i][j][k];
    real_vec[2] = par_obj.get_GA_LRU01_LRF07()[i][j][k];
    str_vec = efw_obj.write_list(par_obj.get_ED_LRU01_LRF07()[i][j][k], par_obj.get_EU_LRU01_LRF07()[i][j][k],
                                 0, 0, static_cast<Integer>(real_vec.size()), 0, real_vec);
    int l_max = static_cast<int>(str_vec.size());
    for(int l=0; l<l_max; l++)
    {
      text.push_back(str_vec[l]);
    }
  }
  else if( par_obj.get_LBK_LRU01_LRF07()[i][j][k] != 0 )
  {
    string class_name = "MF02MT151Writer";
    string func_name  = "write_lru01_lrf07_kbk_b81(int& i, int& j, int& k)";

    ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07;
    oss01 << i+1;
    oss02 << static_cast<int>(par_obj.get_NIS());
    oss03 << j+1;
    oss04 << static_cast<int>(par_obj.get_NER()[i]);
    oss05 << k+1;
    oss06 << static_cast<int>(par_obj.get_NJS_LRU01_LRF07()[i][j]);
    oss07 << par_obj.get_LBK_LRU01_LRF07()[i][j][k];
    string str_data01 = "NIS  : " + oss01.str() + " / " + oss02.str();
    string str_data02 = "NER  : " + oss03.str() + " / " + oss04.str();
    string str_data03 = "NJS  : " + oss05.str() + " / " + oss06.str();
    string str_data04 = "LBK  : " + oss07.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back("This LBK value at MF=02, MT=151 is not supported in this writer program.");
    err_com.push_back("Supported LBK value is 0 - 3.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
  line_data.clear();
  clr_obj.clear_vec_array1_str(str_vec);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF02MT151Writer::write_lru01_lrf07_kps(int& i, int& j, int& k)
{
  string         line_data;
  vector<string> str_vec;

  if( par_obj.get_LPS_LRU01_LRF07()[i][j][k] == 0 )
  {
    line_data = efw_obj.write_cont(0.0, 0.0, 0, 0, par_obj.get_LPS_LRU01_LRF07()[i][j][k], 1);
    text.push_back(line_data);
    line_data = efw_obj.write_cont_real(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    text.push_back(line_data);
  }
  else if(par_obj.get_LPS_LRU01_LRF07()[i][j][k] == 1 )
  {
    line_data = efw_obj.write_cont(0.0, 0.0, 0, 0, par_obj.get_LPS_LRU01_LRF07()[i][j][k], 1);
    text.push_back(line_data);
    line_data = efw_obj.write_cont_real(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    text.push_back(line_data);

    Integer NR = par_obj.get_NBT_PSR_LRU01_LRF07()[i][j][k].size();
    Integer NP = par_obj.get_E_INT_PSR_LRU01_LRF07()[i][j][k].size();

    str_vec = efw_obj.write_tab1(0.0, 0.0, 0, 0, NR, NP,
                      par_obj.get_NBT_PSR_LRU01_LRF07()[i][j][k],   par_obj.get_INT_PSR_LRU01_LRF07()[i][j][k],
                      par_obj.get_E_INT_PSR_LRU01_LRF07()[i][j][k], par_obj.get_PSR_TAB_LRU01_LRF07()[i][j][k]);
    int l_max = static_cast<int>(str_vec.size());
    for(int l=0; l<l_max; l++)
    {
      text.push_back(str_vec[l]);
    }

    NR = par_obj.get_NBT_PSI_LRU01_LRF07()[i][j][k].size();
    NP = par_obj.get_E_INT_PSI_LRU01_LRF07()[i][j][k].size();

    str_vec = efw_obj.write_tab1(0.0, 0.0, 0, 0, NR, NP,
                      par_obj.get_NBT_PSI_LRU01_LRF07()[i][j][k],   par_obj.get_INT_PSI_LRU01_LRF07()[i][j][k],
                      par_obj.get_E_INT_PSI_LRU01_LRF07()[i][j][k], par_obj.get_PSI_TAB_LRU01_LRF07()[i][j][k]);
    l_max = static_cast<int>(str_vec.size());
    for(int l=0; l<l_max; l++)
    {
      text.push_back(str_vec[l]);
    }
  }
  else
  {
    string class_name = "MF02MT151Writer";
    string func_name  = "write_lru01_lrf07_kps(int& i, int& j, int& k)";

    ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07;
    oss01 << i+1;
    oss02 << static_cast<int>(par_obj.get_NIS());
    oss03 << j+1;
    oss04 << static_cast<int>(par_obj.get_NER()[i]);
    oss05 << k+1;
    oss06 << static_cast<int>(par_obj.get_NJS_LRU01_LRF07()[i][j]);
    oss07 << par_obj.get_LPS_LRU01_LRF07()[i][j][k];
    string str_data01 = "NIS  : " + oss01.str() + " / " + oss02.str();
    string str_data02 = "NER  : " + oss03.str() + " / " + oss04.str();
    string str_data03 = "NJS  : " + oss05.str() + " / " + oss06.str();
    string str_data04 = "LPS  : " + oss07.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back("This LPS value at MF=02, MT=151 is not supported in this writer program.");
    err_com.push_back("Supported LPS value is 0 and 1.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
  line_data.clear();
  clr_obj.clear_vec_array1_str(str_vec);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF02MT151Writer::write_lru02(int& i, int& j)
{
  if( par_obj.get_NRO()[i][j] != 0 )
  {
    write_nro(i, j);
  }

  //Case A
  if( par_obj.get_LFW()[i] == 0 && par_obj.get_LRF()[i][j] == 1 )
  {
    write_lru02_a(i, j);
  }
  //Case B
  else if( par_obj.get_LFW()[i] == 1 && par_obj.get_LRF()[i][j] == 1 )
  {
    write_lru02_b(i, j);
  }
  //Case C
  else if( (par_obj.get_LFW()[i] == 1 && par_obj.get_LRF()[i][j] == 2)
        || (par_obj.get_LFW()[i] == 0 && par_obj.get_LRF()[i][j] == 2) )
  {
    write_lru02_c(i, j);
  }
  else
  {
    string class_name = "MF02MT151Writer";
    string func_name  = "write_lru02(int& i, int& j)";

    ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07;
    oss01 << i+1;
    oss02 << static_cast<int>(par_obj.get_NIS());
    oss03 << j+1;
    oss04 << static_cast<int>(par_obj.get_NER()[i]);
    oss05 << par_obj.get_NRO()[i][j];
    oss06 << par_obj.get_LFW()[i];
    oss07 << par_obj.get_LRF()[i][j];
    string str_data01 = "NIS  : " + oss01.str() + " / " + oss02.str();
    string str_data02 = "NER  : " + oss03.str() + " / " + oss04.str();
    string str_data03 = "NRO  : " + oss05.str();
    string str_data04 = "LFW  : " + oss06.str();
    string str_data05 = "LRF  : " + oss07.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back(str_data05);
    err_com.push_back("The format of LRU = 2 at MF=02, MT=151 has something trouble.");
    err_com.push_back("Please check LFW and LRF in MF02MT151Writer class.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF02MT151Writer::write_lru02_a(int& i, int& j)
{
  string         line_data;
  vector<string> str_vec;

  line_data = efw_obj.write_cont(par_obj.get_SPI()[i][j], par_obj.get_AP()[i][j], 
                                  par_obj.get_LSSF_LRU02()[i][j], 0, par_obj.get_NLS()[i][j], 0);
  text.push_back(line_data);

  int k_max = static_cast<int>(par_obj.get_NLS()[i][j]);
  vector<vector<Real> > d    = par_obj.get_D_LRU02_A()[i][j];
  vector<vector<Real> > aj   = par_obj.get_AJ_LRU02_A()[i][j];
  vector<vector<Real> > amun = par_obj.get_AMUN_LRU02_A()[i][j];
  vector<vector<Real> > gno  = par_obj.get_GNO_LRU02_A()[i][j];
  vector<vector<Real> > gg   = par_obj.get_GG_LRU02_A()[i][j];
  for(int k=0; k<k_max; k++)
  {
    int l_max = static_cast<int>(par_obj.get_NJS_LRU02()[i][j][k]);
    vector<Real> real_vec;
    real_vec.resize(l_max*6);
    for(int l=0; l<l_max; l++)
    {
      real_vec[6*l+0] = par_obj.get_D_LRU02_A()[i][j][k][l];
      real_vec[6*l+1] = par_obj.get_AJ_LRU02_A()[i][j][k][l];
      real_vec[6*l+2] = par_obj.get_AMUN_LRU02_A()[i][j][k][l];
      real_vec[6*l+3] = par_obj.get_GNO_LRU02_A()[i][j][k][l];
      real_vec[6*l+4] = par_obj.get_GG_LRU02_A()[i][j][k][l];
      real_vec[6*l+5] = 0.0;
    }
    str_vec = efw_obj.write_list(par_obj.get_AWRI()[i][j][k], 0.0, par_obj.get_L_LRU02()[i][j][k], 0,
                                 static_cast<Integer>(real_vec.size()), par_obj.get_NJS_LRU02()[i][j][k], 
                                 real_vec);
    l_max = static_cast<int>(str_vec.size());
    for(int l=0; l<l_max; l++)
    {
      text.push_back(str_vec[l]);
    }
    real_vec.clear();
  }
  line_data.clear();
  clr_obj.clear_vec_array1_str(str_vec);
  clr_obj.clear_vec_array2_real(d);
  clr_obj.clear_vec_array2_real(aj);
  clr_obj.clear_vec_array2_real(amun);
  clr_obj.clear_vec_array2_real(gno);
  clr_obj.clear_vec_array2_real(gg);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF02MT151Writer::write_lru02_b(int& i, int& j)
{
  string         line_data;
  vector<string> str_vec;

  int k_max = static_cast<int>(par_obj.get_NE_LRU02_B()[i][j]);
  vector<Real> real_vec;
  vector<Real> es = par_obj.get_ES_LRU02_B()[i][j];
  real_vec.resize(k_max);
  for(int k=0; k<k_max; k++)
  {
    real_vec[k] = es[k];
  }
  str_vec = efw_obj.write_list(par_obj.get_SPI()[i][j], par_obj.get_AP()[i][j], par_obj.get_LSSF_LRU02()[i][j],
                               0, par_obj.get_NE_LRU02_B()[i][j], par_obj.get_NLS()[i][j],
                               real_vec);
  k_max = static_cast<int>(str_vec.size());
  for(int k=0; k<k_max; k++)
  {
    text.push_back(str_vec[k]);
  }
  real_vec.clear();
  es.clear();

  k_max = static_cast<int>(par_obj.get_NLS()[i][j]);
  vector<vector<Real> > d    = par_obj.get_D_LRU02_B()[i][j];
  vector<vector<Real> > aj   = par_obj.get_AJ_LRU02_B()[i][j];
  vector<vector<Real> > amun = par_obj.get_AMUN_LRU02_B()[i][j];
  vector<vector<Real> > gno  = par_obj.get_GNO_LRU02_B()[i][j];
  vector<vector<Real> > gg   = par_obj.get_GG_LRU02_B()[i][j];
  vector<vector<vector<Real> > > gf = par_obj.get_GF_LRU02_B()[i][j];
  for(int k=0; k<k_max; k++)
  {
    line_data = efw_obj.write_cont(par_obj.get_AWRI()[i][j][k], 0.0, par_obj.get_L_LRU02()[i][j][k], 
                                    0, par_obj.get_NJS_LRU02()[i][j][k], 0);
    text.push_back(line_data);

    int l_max = static_cast<int>(par_obj.get_NJS_LRU02()[i][j][k]);
    for(int l=0; l<l_max; l++)
    {
      int m_max = static_cast<int>(par_obj.get_NE_LRU02_B()[i][j]);
      real_vec.resize(m_max+6);
      real_vec[0] = d[k][l];
      real_vec[1] = aj[k][l];
      real_vec[2] = amun[k][l];
      real_vec[3] = gno[k][l];
      real_vec[4] = gg[k][l];
      real_vec[5] = 0.0;
      for(int m=0; m<m_max; m++)
      {
        real_vec[m+6] = gf[k][l][m];
      }
      str_vec = efw_obj.write_list(0.0, 0.0,
                                   par_obj.get_L_LRU02()[i][j][k], par_obj.get_MUF_LRU02_B()[i][j][k][l],
                                   static_cast<Integer>(real_vec.size()), 0, real_vec);
      m_max = static_cast<int>(str_vec.size());
      for(int m=0; m<m_max; m++)
      {
        text.push_back(str_vec[m]);
      }
      real_vec.clear();
    }
  }
  line_data.clear();
  clr_obj.clear_vec_array1_str(str_vec);
  clr_obj.clear_vec_array2_real(d);
  clr_obj.clear_vec_array2_real(aj);
  clr_obj.clear_vec_array2_real(amun);
  clr_obj.clear_vec_array2_real(gno);
  clr_obj.clear_vec_array2_real(gg);
  clr_obj.clear_vec_array3_real(gf);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF02MT151Writer::write_lru02_c(int& i, int& j)
{
  string         line_data;
  vector<string> str_vec;

  line_data = efw_obj.write_cont(par_obj.get_SPI()[i][j], par_obj.get_AP()[i][j], par_obj.get_LSSF_LRU02()[i][j],
                                  0, par_obj.get_NLS()[i][j], 0);
  text.push_back(line_data);

  int k_max = static_cast<int>(par_obj.get_NLS()[i][j]);
  vector<vector<Real> > amux = par_obj.get_AMUX_LRU02_C()[i][j];
  vector<vector<Real> > amun = par_obj.get_AMUN_LRU02_C()[i][j];
  vector<vector<Real> > amug = par_obj.get_AMUG_LRU02_C()[i][j];
  vector<vector<Real> > amuf = par_obj.get_AMUF_LRU02_C()[i][j];
  vector<vector<vector<Real> > > es  = par_obj.get_ES_LRU02_C()[i][j];
  vector<vector<vector<Real> > > d   = par_obj.get_D_LRU02_C()[i][j];
  vector<vector<vector<Real> > > gx  = par_obj.get_GX_LRU02_C()[i][j];
  vector<vector<vector<Real> > > gno = par_obj.get_GNO_LRU02_C()[i][j];
  vector<vector<vector<Real> > > gg  = par_obj.get_GG_LRU02_C()[i][j];
  vector<vector<vector<Real> > > gf  = par_obj.get_GF_LRU02_C()[i][j];
  for(int k=0; k<k_max; k++)
  {
    line_data = efw_obj.write_cont(par_obj.get_AWRI()[i][j][k], 0.0, par_obj.get_L_LRU02()[i][j][k],
                                    0, par_obj.get_NJS_LRU02()[i][j][k], 0);
    text.push_back(line_data);

    int l_max = static_cast<int>(par_obj.get_NJS_LRU02()[i][j][k]);
    for(int l=0; l<l_max; l++)
    {
      int m_max = static_cast<int>(par_obj.get_NE_LRU02_C()[i][j][k][l]);
      vector<Real> real_vec;
      real_vec.resize(m_max*6+6);
      real_vec[0] = 0.0;
      real_vec[1] = 0.0;
      real_vec[2] = amux[k][l];
      real_vec[3] = amun[k][l];
      real_vec[4] = amug[k][l];
      real_vec[5] = amuf[k][l];
      for(int m=0; m<m_max; m++)
      {
        real_vec[6*m+0+6] = es[k][l][m];
        real_vec[6*m+1+6] = d[k][l][m];
        real_vec[6*m+2+6] = gx[k][l][m];
        real_vec[6*m+3+6] = gno[k][l][m];
        real_vec[6*m+4+6] = gg[k][l][m];
        real_vec[6*m+5+6] = gf[k][l][m];
      }
      str_vec = efw_obj.write_list(par_obj.get_AJ_LRU02_C()[i][j][k][l], 0.0,
                                   par_obj.get_INT_LRU02_C()[i][j][k][l],  0,
                                   static_cast<Integer>(real_vec.size()), par_obj.get_NE_LRU02_C()[i][j][k][l],
                                   real_vec);
      m_max = static_cast<int>(str_vec.size());
      for(int m=0; m<m_max; m++)
      {
        text.push_back(str_vec[m]);
      }
      real_vec.clear();
    }
  }
  line_data.clear();
  clr_obj.clear_vec_array1_str(str_vec);
  clr_obj.clear_vec_array2_real(amux);
  clr_obj.clear_vec_array2_real(amun);
  clr_obj.clear_vec_array2_real(amug);
  clr_obj.clear_vec_array2_real(amuf);
  clr_obj.clear_vec_array3_real(es);
  clr_obj.clear_vec_array3_real(d);
  clr_obj.clear_vec_array3_real(gx);
  clr_obj.clear_vec_array3_real(gno);
  clr_obj.clear_vec_array3_real(gg);
  clr_obj.clear_vec_array3_real(gf);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF02MT151Writer::write_nro(int& i, int& j)
{
  vector<string> str_vec;
  Integer NR = par_obj.get_NBT_AP_NRO()[i][j].size();
  Integer NP = par_obj.get_E_INT_AP_NRO()[i][j].size();

  str_vec = efw_obj.write_tab1(0.0, 0.0, 0, 0, NR, NP,
                               par_obj.get_NBT_AP_NRO()[i][j],   par_obj.get_INT_AP_NRO()[i][j],
                               par_obj.get_E_INT_AP_NRO()[i][j], par_obj.get_AP_TAB_NRO()[i][j]);

  int k_max = static_cast<int>(str_vec.size());
  for(int k=0; k<k_max; k++)
  {
    text.push_back(str_vec[k]);
  }
  clr_obj.clear_vec_array1_str(str_vec);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF02MT151Writer::clear()
{
  clr_obj.clear_vec_array1_str(text);

  par_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> MF02MT151Writer::get_endf_text_data(MF02MT151Parser& mf02mt151parser_obj)
{
  clear();
  par_obj = mf02mt151parser_obj;

  write_endf();
  return text;
}
