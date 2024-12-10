#include "ReconResonance/ResonanceNuclearDataModifier.hpp"

using namespace frendy;

//constructor
ResonanceNuclearDataModifier::ResonanceNuclearDataModifier(void)
{
  clear();
}

//destructor
ResonanceNuclearDataModifier::~ResonanceNuclearDataModifier(void)
{
  clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ResonanceNuclearDataModifier::modify_endf()
{
  if( modify_endf_flg != 0 )
  {
    return;
  }
  modify_endf_flg = 1;

  check_set_data();

  if( mf02mt151_par.get_mat_no() != unassigned_mat_no && 
      mf02mt152_par.get_mat_no() != unassigned_mat_no )
  {
    //Do not modify resonance parameter
  }
  else if( mf02mt151_par.get_mat_no() != unassigned_mat_no )
  {
    //Modify MF02MT151 & MF02MT152
    //MF01MT451 was modified in Endf6Writer class.
    modify_mf02mt151();
 
    mf02mt152_par.clear();
    if( unreso_flg > 0 && mf01mt451_par.get_LRP() == 1 )
    {
      modify_mf02mt152();
    }
  }
  else
  {
    set_void_mf02mt151();
  }

  if( modify_photon_data_flg == 1 )
  {
    //Modify MF12 and MF13 data
    remove_each_subsection_photon_data();
  }

  set_modified_endf6_parser_data();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ResonanceNuclearDataModifier::set_void_mf02mt151()
{
  mf02mt151_par_mod.clear();
  mf02mt152_par.clear();

  Integer mat_no = mf01mt451_par.get_mat_no();
  Real    ZAR    = mf01mt451_par.get_ZA();
  Real    AWR    = mf01mt451_par.get_AWR();
  Integer NIS    = 1;
  mf02mt151_par_mod.set_mat_no(mat_no);
  mf02mt151_par_mod.set_ZAR(ZAR);
  mf02mt151_par_mod.set_AWR(AWR);
  mf02mt151_par_mod.set_NIS(NIS);

  vector<Real>             ZAI, ABN;
  vector<Integer>          LFW, NER;
  vector<vector<Real> >    EL, EH, SPI, AP;
  vector<vector<Integer> > LRU, LRF, NRO, NAPS, NLS;

  ZAI.resize(1);
  ABN.resize(1);
  LFW.resize(1);
  NER.resize(1);
  ZAI[0] = ZAR;
  ABN[0] = 1.0;
  LFW[0] = 0;
  NER[0] = 1;
  mf02mt151_par_mod.set_ZAI(ZAI);
  mf02mt151_par_mod.set_ABN(ABN);
  mf02mt151_par_mod.set_LFW(LFW);
  mf02mt151_par_mod.set_NER(NER);

  EL.resize(1);
  EH.resize(1);
  SPI.resize(1);
  AP.resize(1);
  LRU.resize(1);
  LRF.resize(1);
  NRO.resize(1);
  NAPS.resize(1);
  NLS.resize(1);
  EL[0].resize(1);
  EH[0].resize(1);
  SPI[0].resize(1);
  AP[0].resize(1);
  LRU[0].resize(1);
  LRF[0].resize(1);
  NRO[0].resize(1);
  NAPS[0].resize(1);
  NLS[0].resize(1);

  EL[0][0]   = 1.0E-5;
  EH[0][0]   = mf01mt451_par.get_EMAX();
  SPI[0][0]  = 0.0;
  AP[0][0]   = 0.0;
  LRU[0][0]  = 0;
  LRF[0][0]  = 0;
  NRO[0][0]  = 0;
  NAPS[0][0] = 0;
  NLS[0][0]  = 0;

  //Modify EL and EH using total cross section data
  int i_max = static_cast<int>(mf03_par.size());
  if( i_max > 0 )
  {
    int ele_no = 0;
    for(int i=0; i<i_max; i++)
    {
      if( mf03_par[i].get_mt_no() == 1 )
      {
        ele_no = i;
        break;
      }
    }

    vector<Real> E_INT_SIG = mf03_par[ele_no].get_E_INT_SIG();
    int j_max = static_cast<int>(E_INT_SIG.size());
    if( j_max > 1 )
    {
      EL[0][0] = E_INT_SIG[0];
      EH[0][0] = E_INT_SIG[j_max-1];
    }
  }

  mf02mt151_par_mod.set_EL(EL);
  mf02mt151_par_mod.set_EH(EH);
  mf02mt151_par_mod.set_SPI(SPI);
  mf02mt151_par_mod.set_AP(AP);
  mf02mt151_par_mod.set_LRU(LRU);
  mf02mt151_par_mod.set_LRF(LRF);
  mf02mt151_par_mod.set_NRO(NRO);
  mf02mt151_par_mod.set_NAPS(NAPS);
  mf02mt151_par_mod.set_NLS(NLS);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ResonanceNuclearDataModifier::modify_mf02mt151()
{
  //Read SPI and AP value in unresolved resonance region
  Real spi_unreso_val = 0.0;
  Real ap_unreso_val  = 0.0;
  search_spi_ap_mf02mt151(spi_unreso_val, ap_unreso_val);

  Real         za   = mf02mt151_par.get_ZAR();
  Real         awr  = mf02mt151_par.get_AWR();
  Integer      nis  = 1;
  vector<Real> zai  = mf02mt151_par.get_ZAI();
  vector<Real> abn  = mf02mt151_par.get_ABN();
    
  vector<Integer> lfw;
  vector<Integer> ner;
  vector<vector<Integer> > lru;
  vector<vector<Integer> > lrf;
  vector<vector<Integer> > nro;
  vector<vector<Integer> > naps;
    
  vector<vector<Real> >     spi;
  vector<vector<Real> >     ap;
  vector<vector<Integer > > nls;

  int i_max = static_cast<int>(nis);
  lfw.resize(i_max);
  ner.resize(i_max);
  lru.resize(i_max);
  lrf.resize(i_max);
  nro.resize(i_max);
  naps.resize(i_max);
  spi.resize(i_max);
  ap.resize(i_max);
  nls.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    lfw[i] = 0;
    ner[i] = 1;
    int j_max = static_cast<int>(ner[i]);
    lru[i].resize(j_max);
    lrf[i].resize(j_max);
    nro[i].resize(j_max);
    naps[i].resize(j_max);
    spi[i].resize(j_max);
    ap[i].resize(j_max);
    nls[i].resize(j_max);
    for(int j=0; j<j_max; j++)
    {
      lru[i][j]  = 0;
      lrf[i][j]  = 0;
      nro[i][j]  = 0;
      naps[i][j] = 0;
      spi[i][j]  = spi_unreso_val;
      ap[i][j]   = ap_unreso_val;
      nls[i][j]  = 0;
    }
  }
  
  vector<vector<Real> > el, eh;
  search_el_eh_mf02mt151(el, eh);
  
  //Copy data to MF02MT152Parser class
  mf02mt151_par_mod.clear();
  
  mf02mt151_par_mod.set_mat_no(mat_no);
  
  mf02mt151_par_mod.set_ZAR(za);
  mf02mt151_par_mod.set_AWR(awr);
  mf02mt151_par_mod.set_NIS(nis);
  
  mf02mt151_par_mod.set_ZAI(zai);
  mf02mt151_par_mod.set_ABN(abn);
  mf02mt151_par_mod.set_LFW(lfw);
  mf02mt151_par_mod.set_NER(ner);
  
  mf02mt151_par_mod.set_EL(el);
  mf02mt151_par_mod.set_EH(eh);
  mf02mt151_par_mod.set_LRU(lru);
  mf02mt151_par_mod.set_LRF(lrf);
  mf02mt151_par_mod.set_NRO(nro);
  mf02mt151_par_mod.set_NAPS(naps);
  
  mf02mt151_par_mod.set_SPI(spi);
  mf02mt151_par_mod.set_AP(ap);
  mf02mt151_par_mod.set_NLS(nls);
  
  //Clear vector
  zai.clear();
  abn.clear();
  spi.clear();
  ap.clear();
  clr_obj.clear_vec_array2_real(el);
  clr_obj.clear_vec_array2_real(eh);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ResonanceNuclearDataModifier::search_spi_ap_mf02mt151(Real& spi_unreso_val, Real& ap_unreso_val)
{
  int  read_spi_flg   = 0;
       spi_unreso_val = 0.0;
       ap_unreso_val  = 0.0;
  int i_max = static_cast<int>(mf02mt151_par.get_SPI().size());
  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(mf02mt151_par.get_SPI()[i].size());
    for(int j=0; j<j_max; j++)
    {
      if( mf02mt151_par.get_LRU()[i][j] == 2 )
      {
        if( read_spi_flg == 0 )
        {
          read_spi_flg   = 1;
          spi_unreso_val = mf02mt151_par.get_SPI()[i][j];
          ap_unreso_val  = mf02mt151_par.get_AP()[i][j];
        }
        else
        {
          if( fabs(spi_unreso_val - mf02mt151_par.get_SPI()[i][j]) > min_ene_dif ||
              fabs(ap_unreso_val  - mf02mt151_par.get_AP()[i][j])  > min_ene_dif )
          {
            string class_name = "ResonanceNuclearDataModifier";
            string func_name  = "search_spi_ap_mf02mt151(Real& spi_unreso_val, Real& ap_unreso_val)";
            ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07, oss08;
            oss01 << i;
            oss02 << static_cast<int>(mf02mt151_par.get_NIS());
            oss03 << j;
            oss04 << static_cast<int>(mf02mt151_par.get_NER()[i]);
            oss05 << spi_unreso_val;
            oss06 << mf02mt151_par.get_SPI()[i][j];
            oss07 << ap_unreso_val;
            oss08 << mf02mt151_par.get_AP()[i][j];
            string str_data01 = "NIS : " + oss01.str() + " / " + oss02.str();
            string str_data02 = "NER : " + oss03.str() + " / " + oss04.str();
            string str_data03 = "Initial spin value in unresolved resion : " + oss05.str();
            string str_data04 = "Current spin value                      : " + oss06.str();
            string str_data05 = "Initial ap value in unresolved resion   : " + oss07.str();
            string str_data06 = "Current ap value                        : " + oss08.str();

            vector<string> err_com;
            err_com.push_back(str_data01);
            err_com.push_back(str_data02);
            err_com.push_back(str_data03);
            err_com.push_back(str_data04);
            err_com.push_back(str_data05);
            err_com.push_back(str_data06);
            err_com.push_back("The different spin or ap value is observed in unresolved resonance region.");
            err_com.push_back("MF=2 MT=151 data in the PENDF file may not be appropriate.");
            err_obj.output_caution(class_name, func_name, err_com);
          }
        }
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ResonanceNuclearDataModifier::search_el_eh_mf02mt151
                                     (vector<vector<Real> >& el, vector<vector<Real> >& eh)
{
  int  i_max   = static_cast<int>(mf03_par.size());
  Real ene_min = 1.0E-5;
  Real ene_max = 2.0E+7;
  for(int i=0; i<i_max; i++)
  {
    if( mf03_par[i].get_mt_no() == 1 )
    {
      int j_max = static_cast<int>(mf03_par[i].get_E_INT_SIG().size());
      if( j_max > 0 )
      {
        ene_min = mf03_par[i].get_E_INT_SIG()[0];
        ene_max = mf03_par[i].get_E_INT_SIG()[j_max-1];
      }
    }
  }

  i_max = static_cast<int>(mf02mt151_par.get_NIS());
  vector<vector<Integer> > lru     = mf02mt151_par.get_LRU();
  vector<vector<Real> >    el_ori  = mf02mt151_par.get_EL();
  vector<vector<Real> >    eh_ori  = mf02mt151_par.get_EH();
  Real8                    el_val, eh_val;
  el.resize(i_max);
  eh.resize(i_max);

  for(int i=0; i<i_max; i++)
  {
    int ene_set_flg = 0;
    el_val = ene_min;
    eh_val = ene_max;

    int j_max = static_cast<int>(mf02mt151_par.get_NER()[i]);
    for(int j=0; j<j_max; j++)
    {
      if( lru[i][j] == 1 )
      {
        if( ene_set_flg == 0 )
        {
          ene_set_flg = 1;
          el_val = el_ori[i][j];
          eh_val = eh_ori[i][j];
        }
        else
        {
          if( el_val > el_ori[i][j] )
          {
            el_val = el_ori[i][j];
          }
          if( eh_val < eh_ori[i][j] )
          {
            eh_val = eh_ori[i][j];
          }
        }
      }
      else if( ene_set_flg == 0 && lru[i][j] == 2 )
      {
        //If only unresolved resonance region data is contained
        //(resolved resonance region data is not contained),
        //eh_val is equal considered as the el_ori[i][j]
        ene_set_flg = 1;
        eh_val = el_ori[i][j];
      }
    }
    el[i].push_back(el_val);
    eh[i].push_back(eh_val);
  }
  clr_obj.clear_vec_array2_real(el_ori);
  clr_obj.clear_vec_array2_real(eh_ori);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ResonanceNuclearDataModifier::modify_mf02mt152()
{
  Real    za       = mf02mt151_par.get_ZAR();
  Real    awr      = mf02mt151_par.get_AWR();
  Real    temp     = mf01mt451_par.get_TEMP();
  Integer opt1_val = 5;
  Integer opt2_val = 1;
    
  //Set unresonance cross section and energy grid
  vector<Real8>          unreso_ene_grid;
  vector<vector<Real8> > unreso_sig_data;
  unreso_ene_grid.clear();
  Integer lssf_val = -1;
  Integer int_val  = -1;
  clr_obj.clear_vec_array2_real8(unreso_sig_data);
  modify_unreso_data_mf02mt152(unreso_ene_grid, unreso_sig_data, lssf_val, int_val);
  
  //Copy data to MF02MT152Parser class
  mf02mt152_par.clear();
  mf02mt152_par.set_mat_no(mat_no);
    
  mf02mt152_par.set_ZAR(za);
  mf02mt152_par.set_AWR(awr);
  mf02mt152_par.set_LSSF(lssf_val);
  mf02mt152_par.set_INT(int_val);

  mf02mt152_par.set_TEMP(temp);
  mf02mt152_par.set_OPT1(opt1_val);
  mf02mt152_par.set_OPT2(opt2_val);
  
  int i_max = static_cast<int>(unreso_ene_grid.size());
  Integer ne = static_cast<Integer>(i_max);
  vector<Real> ene, sig_tot, sig_sc, sig_fis, sig_rad;
  ene.resize(i_max);
  sig_tot.resize(i_max);
  sig_sc.resize(i_max);
  sig_fis.resize(i_max);
  sig_rad.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    ene[i]     = static_cast<Real>(unreso_ene_grid[i]);
    sig_tot[i] = static_cast<Real>(unreso_sig_data[i][total_xs]);
    sig_sc[i]  = static_cast<Real>(unreso_sig_data[i][scatter_xs]);
    sig_fis[i] = static_cast<Real>(unreso_sig_data[i][fission_xs]);
    sig_rad[i] = static_cast<Real>(unreso_sig_data[i][radiation_xs]);
  }
  mf02mt152_par.set_NE(ne);
  mf02mt152_par.set_E(ene);
  mf02mt152_par.set_SIG_TOT(sig_tot);
  mf02mt152_par.set_SIG_SC( sig_sc);
  mf02mt152_par.set_SIG_FIS(sig_fis);
  mf02mt152_par.set_SIG_RAD(sig_rad);
  
  //Clear vector
  unreso_ene_grid.clear();
  clr_obj.clear_vec_array2_real8(unreso_sig_data);
  ene.clear();
  sig_tot.clear();
  sig_sc.clear();
  sig_fis.clear();
  sig_rad.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ResonanceNuclearDataModifier::modify_unreso_data_mf02mt152(vector<Real8>& unreso_ene_grid, 
                                                                vector<vector<Real8> >& unreso_sig_data, 
                                                                Integer& lssf_val, Integer& int_val)
{
  vector<Real>             abn  = mf02mt151_par.get_ABN();
  vector<vector<Integer> > lrf  = mf02mt151_par.get_LRF();
  vector<vector<Integer> > lru  = mf02mt151_par.get_LRU();
  vector<vector<Integer> > lssf = mf02mt151_par.get_LSSF_LRU02();

  int i_max = static_cast<int>(mf02mt151_par.get_NIS());
  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(mf02mt151_par.get_NER()[i]);
    for(int j=0; j<j_max; j++)
    {
      if(lru[i][j] == 2)
      {
        add_unreso_data(unreso_ene_grid, unreso_sig_data, reso_ene_grid[i][j], reso_sig_data[i][j], abn[i]);
        
        if( lssf_val == -1 )
        {
          lssf_val = lssf[i][j];
          int_val  = 5;
          //if( lrf[i][j] == 2 )
          //{
          //  int_val = mf02mt151_par.get_INT_LRU02_C()[i][j];
          //}
        }
        else
        {
          //if( ( lssf_val != lssf[i][j] ) || ( lrf[i][j] != 2 )  || 
          //    ( ( int_val==5 && lrf[i][j]==2 ) && ( mf02mt151_par.get_INT_LRU02_C()[i][j] != 5 ) ) )
          if( lssf_val != lssf[i][j] )
          {
            string class_name = "ResonanceNuclearDataModifier";
            string func_name  = "modify_unreso_data_mf02mt152(vector<Real8>& unreso_ene_grid, ";
                   func_name += "vector<vector<Real8> >& unreso_sig_data, ";
                   func_name += "Integer& lssf_val, Integer& int_val)";

            ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07, oss08;
            oss01 << i;
            oss02 << static_cast<int>(mf02mt151_par.get_NIS());
            oss03 << j;
            oss04 << static_cast<int>(mf02mt151_par.get_NER()[i]);
            oss05 << lssf[i][j];
            oss06 << lssf_val;
            oss07 << lrf[i][j];
            oss08 << int_val;
            string str_data01 = "NIS      : " + oss01.str() + " / " + oss02.str();
            string str_data02 = "NER      : " + oss03.str() + " / " + oss04.str();
            string str_data03 = "LSSF     : " + oss05.str();
            string str_data04 = "lssf_val : " + oss06.str();
            string str_data05 = "LRF      : " + oss07.str();
            string str_data06 = "int_val  : " + oss08.str();

            vector<string> err_com;
            err_com.push_back(str_data01);
            err_com.push_back(str_data02);
            err_com.push_back(str_data03);
            err_com.push_back(str_data04);
            err_com.push_back(str_data05);
            err_com.push_back(str_data06);

            if( lssf_val != lssf[i][j] )
            {
              err_com.push_back("LSSF at each NIS in MF02MT151 is different.");
            }
            /*if( ( int_val==5 && lrf[i][j]==2 ) && ( mf02mt151_par.get_INT_LRU02_C()[i][j] != 5 ) )
            {
              err_com.push_back("INT at each NIS in MF02MT151 is different.");   
            }*/
            /*if( lrf[i][j] != 2 )
            {
              err_com.push_back("INT at each NIS in MF02MT151 is different.");
            }*/
            err_com.push_back("Please check the program or endf file.");
            err_obj.output_runtime_error(class_name, func_name, err_com);
          }
        }
        break;
      }
    }
  }
  clr_obj.clear_vec_array2_int(lrf);
  clr_obj.clear_vec_array2_int(lru);
  clr_obj.clear_vec_array2_int(lssf);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ResonanceNuclearDataModifier::add_unreso_data
                                     (vector<Real8>& base_ene_grid, vector<vector<Real8> >& base_sig_data, 
                                      vector<Real8>& add_ene_grid,  vector<vector<Real8> >& add_sig_data,
                                      Real& abn)
{
  int i_max = static_cast<int>(base_ene_grid.size());
  if( i_max == 0 )
  {
    base_ene_grid = add_ene_grid;
    base_sig_data = add_sig_data;
    
    i_max = static_cast<int>(base_ene_grid.size());
    for(int i=0; i<i_max; i++)
    {
      for(int j=0; j<xs_type_no; j++)
      {
        base_sig_data[i][j] *= abn;
      }
    }
    return;
  }
  
  Real8                  ene_dif, ene_cur;
  vector<Real8>          new_ene;
  vector<vector<Real8> > new_sig;
  new_ene.clear();
  clr_obj.clear_vec_array2_real8(new_sig);
  
  int new_ele     = 0;
  int add_ele     = 0;
  int add_ele_max = static_cast<int>(add_ene_grid.size());
  for(int i=0; i<i_max; i++)
  {
    ene_cur = base_ene_grid[i];
    ene_dif = min_ene_dif*ene_cur;
    if( add_ele < add_ele_max )
    {
      while( add_ene_grid[add_ele] - ene_cur <= ene_dif )
      {
        new_ene.push_back(add_ene_grid[add_ele]);
        new_sig.push_back(add_sig_data[add_ele]);
        for(int j=0; j<xs_type_no; j++)
        {
          new_sig[new_ele][j] *= abn;
        }
        add_ele++;
        new_ele++;

        if( add_ele >= add_ele_max )
        {
          break;
        }
      }
    }
  
    if( new_ele > 0 )
    { 
      if( fabs(new_ene[new_ele-1] - ene_cur ) <= ene_dif )
      {
        for(int j=0; j<xs_type_no; j++)
        {
          new_sig[new_ele-1][j] += base_sig_data[i][j];
        }
      }
      else
      {
        new_ene.push_back(ene_cur);
        new_sig.push_back(base_sig_data[i]);
        new_ele++;
      }
    }
    else
    {
      new_ene.push_back(ene_cur);
      new_sig.push_back(base_sig_data[i]);
      new_ele++;
    }
  }
  
  //Add additional energy grid which larger than maximum energy of base_ene_grid
  i_max = static_cast<int>(add_ene_grid.size());
  for(int i=add_ele; i<i_max; i++)
  {
    new_ene.push_back(add_ene_grid[i]);
    new_sig.push_back(add_sig_data[i]);
    for(int j=0; j<xs_type_no; j++)
    {
      new_sig[new_ele][j] *= abn;
    }
    new_ele++;
  }
  
  //Copy new xs and energy grid
  base_ene_grid.clear();
  clr_obj.clear_vec_array2_real8(base_sig_data);
  
  base_ene_grid = new_ene;
  base_sig_data = new_sig;
  
  new_ene.clear();
  clr_obj.clear_vec_array2_real8(new_sig);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ResonanceNuclearDataModifier::check_set_data()
{
  int i_max = static_cast<int>(ene_grid.size());
  Integer         nis = mf02mt151_par.get_NIS();
  vector<Integer> ner = mf02mt151_par.get_NER();

  if( ( endf_parser_flg == 0 ) || ( merge_grid_flg == 0 ) || ( merge_xs_flg == 0 ) ||
      ( reso_grid_flg == 0 )   || ( reso_xs_flg == 0 )    || ( i_max == 0 ) ||
      ( static_cast<int>(sig_data.size()) != i_max ) || 
      ( static_cast<Integer>(reso_ene_grid.size()) != nis && reso_flg == 1 ) || 
      ( static_cast<Integer>(reso_sig_data.size()) != nis && reso_flg == 1 ) )
  {
    string class_name = "ResonanceNuclearDataModifier";
    string func_name  = "check_set_data()";

    ostringstream oss01, oss02, oss03, oss04, oss05;
    oss01 << static_cast<int>(ene_grid.size());
    oss02 << static_cast<int>(sig_data.size());
    oss03 << nis;
    oss04 << static_cast<Integer>(reso_ene_grid.size());
    oss05 << static_cast<Integer>(reso_sig_data.size());

    string str_data01 = "Size of energy grid             : " + oss01.str();
    string str_data02 = "Size of cross section           : " + oss02.str();
    string str_data03 = "NIS                             : " + oss03.str();
    string str_data04 = "Size of resonance energy grid   : " + oss04.str();
    string str_data05 = "Size of resonance cross section : " + oss05.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back(str_data05);
    
    //Check the all data was set or not
    if( endf_parser_flg == 0 )
    {
      err_com.push_back("Endf6ParserNoCov class is not set.");
    }
    if( merge_grid_flg == 0 )
    {
      err_com.push_back("Merged energy grid is not set.");
    }
    else if( merge_xs_flg == 0 )
    {
      err_com.push_back("Merged cross section is not set.");
    }
    else if( reso_grid_flg == 0 )
    {
      err_com.push_back("Resonance energy grid is not set.");
    }
    else if( reso_xs_flg == 0 )
    {
      err_com.push_back("Resonance cross section is not set.");
    }

    //Check the array size of merged xs and energy grid
    if( i_max == 0 )
    {
      err_com.push_back("The array size of merged energy grid is 0.");
    }
    else if( static_cast<int>(sig_data.size()) != i_max )
    {
      err_com.push_back("The array size of merged xs and energy grid is not identical.");
    }

    //Check the array size of resonance xs and energy grid
    if( reso_flg == 1 )
    {
      if( static_cast<Integer>(reso_ene_grid.size()) != nis )
      {
        err_com.push_back("The array size of resonance energy grid is different to NIS in MF02MT151.");
      }
      else if( static_cast<Integer>(reso_sig_data.size()) != nis )
      {
        err_com.push_back("The array size of resonance cross section is different to NIS in MF02MT151.");
      }
    }
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  for(int i=0; i<i_max; i++)
  {
    if( static_cast<int>(sig_data[i].size()) != xs_type_no )
    {
      string class_name = "ResonanceNuclearDataModifier";
      string func_name  = "check_set_data()";

      ostringstream oss01, oss02, oss03, oss04;
      oss01 << i;
      oss02 << static_cast<int>(ene_grid.size());
      oss03 << xs_type_no;
      oss04 << static_cast<int>(sig_data[i].size());

      string str_data01 = "Energy grid           : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "Cross section type no : " + oss03.str();
      string str_data03 = "Size of cross section : " + oss04.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back("The arrasy size of merged xs is not equal to xs_type_no.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }

  //Check the array size of resonance xs and energy grid
  if( reso_flg == 1 )
  {
    for(int i=0; i<static_cast<int>(nis); i++)
    {
      if( static_cast<Integer>(reso_ene_grid[i].size()) != ner[i] ||
          static_cast<Integer>(reso_sig_data[i].size()) != ner[i]  )
      {
        string class_name = "ResonanceNuclearDataModifier";
        string func_name  = "check_set_data()";

        ostringstream oss01, oss02, oss03, oss04, oss05;
        oss01 << i;
        oss02 << static_cast<int>(nis);
        oss03 << ner[i];
        oss04 << static_cast<Integer>(reso_ene_grid[i].size());
        oss05 << static_cast<Integer>(reso_sig_data[i].size());

        string str_data01 = "NIS                             : " + oss01.str() + " / " + oss02.str();
        string str_data02 = "NER                             : " + oss03.str();
        string str_data03 = "Size of reconance energy grid   : " + oss04.str();
        string str_data04 = "Size of resonance cross section : " + oss05.str();

        vector<string> err_com;
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back(str_data04);
        if( static_cast<Integer>(reso_ene_grid[i].size()) != ner[i] )
        {
          err_com.push_back("The array size of resonance energy grid is different to NER in MF02MT151.");
        }
        else if( static_cast<Integer>(reso_sig_data[i].size()) != ner[i] )
        {
          err_com.push_back("The array size of resonance cross section is different to NER in MF02MT151.");
        }
        err_obj.output_runtime_error(class_name, func_name, err_com);
      }
    }
  }
  
  //check the number of unresolved resonance
  unreso_flg = 0;
  vector<vector<Integer> > lru = mf02mt151_par.get_LRU();
  for(int i=0; i<static_cast<int>(nis); i++)
  {
    Integer unreso_flg_nis = 0;
    for(int j=0; j<static_cast<int>(ner[i]); j++)
    {
      if( lru[i][j] == 2 )
      {
        unreso_flg_nis++;
      }
    }
    unreso_flg += unreso_flg_nis;
    if( unreso_flg_nis > 1 )
    {
      string class_name = "ResonanceNuclearDataModifier";
      string func_name  = "check_set_data()";

      ostringstream oss01, oss02;
      oss01 << i;
      oss02 << static_cast<int>(nis);

      string str_data01 = "NIS : " + oss01.str() + " / " + oss02.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back("The more than one unresolve data is exist in same NIS part.");
      err_com.push_back("Please check MF02MT151.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }
  clr_obj.clear_vec_array2_int(lru);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ResonanceNuclearDataModifier::remove_each_subsection_photon_data()
{
  int i_max = static_cast<int>(mf12_par.size());
  for(int i=0; i<i_max; i++)
  {
    if( mf12_par[i].get_mt_no() != unassigned_mt_no )
    {
      if( mf12_par[i].get_NK() > 1 && mf12_par[i].get_LO() == 1 )
      {
        Integer                  NK = 1;
        vector<Real>             EG, ES;
        vector<Integer>          LP, LF;
        vector<vector<Integer> > NBT_Y_K,   INT_Y_K;
        vector<vector<Real> >    E_INT_Y_K, Y_K_TAB;
        EG.resize(1);
        ES.resize(1);
        LP.resize(1);
        LF.resize(1);
        NBT_Y_K.resize(1);
        INT_Y_K.resize(1);
        E_INT_Y_K.resize(1);
        Y_K_TAB.resize(1);
        EG[0]        = 0.0;
        ES[0]        = 0.0;
        LP[0]        =   0;
        LF[0]        =   0;
        NBT_Y_K[0]   = mf12_par[i].get_NBT_Y_LO01();
        INT_Y_K[0]   = mf12_par[i].get_INT_Y_LO01();
        E_INT_Y_K[0] = mf12_par[i].get_E_INT_Y_LO01();
        Y_K_TAB[0]   = mf12_par[i].get_Y_TAB_LO01();

        mf12_par[i].set_NK(NK);
        mf12_par[i].set_EG_LO01(EG);
        mf12_par[i].set_ES_LO01(ES);
        mf12_par[i].set_LP_LO01(LP);
        mf12_par[i].set_LF_LO01(LF);
        mf12_par[i].set_NBT_Y_K_LO01(NBT_Y_K);
        mf12_par[i].set_INT_Y_K_LO01(INT_Y_K);
        mf12_par[i].set_E_INT_Y_K_LO01(E_INT_Y_K);
        mf12_par[i].set_Y_K_TAB_LO01(Y_K_TAB);       
      }
    }
  }

  i_max = static_cast<int>(mf13_par.size());
  for(int i=0; i<i_max; i++)
  {
    if( mf13_par[i].get_mt_no() != unassigned_mt_no )
    {
      if( mf13_par[i].get_NK() > 1 )
      {
        Integer                  NK = 1;
        vector<Real>             EG, ES;
        vector<Integer>          LP, LF;
        vector<vector<Integer> > NBT_S_K,   INT_S_K;
        vector<vector<Real> >    E_INT_S_K, S_K_TAB;
        EG.resize(1);
        ES.resize(1);
        LP.resize(1);
        LF.resize(1);
        NBT_S_K.resize(1);
        INT_S_K.resize(1);
        E_INT_S_K.resize(1);
        S_K_TAB.resize(1);
        EG[0]        = 0.0;
        ES[0]        = 0.0;
        LP[0]        =   0;
        LF[0]        =   0;
        NBT_S_K[0]   = mf13_par[i].get_NBT_S_TOT();
        INT_S_K[0]   = mf13_par[i].get_INT_S_TOT();
        E_INT_S_K[0] = mf13_par[i].get_E_INT_S_TOT();
        S_K_TAB[0]   = mf13_par[i].get_S_TOT_TAB();

        mf13_par[i].set_NK(NK);
        mf13_par[i].set_EG(EG);
        mf13_par[i].set_ES(ES);
        mf13_par[i].set_LP(LP);
        mf13_par[i].set_LF(LF);
        mf13_par[i].set_NBT_S_K(NBT_S_K);
        mf13_par[i].set_INT_S_K(INT_S_K);
        mf13_par[i].set_E_INT_S_K(E_INT_S_K);
        mf13_par[i].set_S_K_TAB(S_K_TAB);
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ResonanceNuclearDataModifier::clear()
{
  modify_photon_data_flg = 0;

  endf_parser_flg = 0;
  merge_grid_flg  = 0;
  merge_xs_flg    = 0;
  reso_grid_flg   = 0;
  reso_xs_flg     = 0;

  set_label_flg   = 0;
  
  parser_no_cov.clear();
  
  ene_grid.clear();
  clr_obj.clear_vec_array2_real8(sig_data);
  clr_obj.clear_vec_array3_real8(reso_ene_grid);
  clr_obj.clear_vec_array4_real8(reso_sig_data);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ResonanceNuclearDataModifier::clear_parser_data()
{
  modify_endf_flg = 0;
  unreso_flg      = 0;

  parser_no_cov.clear();
  mf01mt451_par.clear();
  mf02mt151_par.clear();
  mf02mt152_par.clear();
  
  mf02mt151_par_mod.clear();
  
  vector<MF03Parser>().swap(mf03_par);
  vector<MF10Parser>().swap(mf10_par);
  vector<MF12Parser>().swap(mf12_par);
  vector<MF13Parser>().swap(mf13_par);
  vector<MF23Parser>().swap(mf23_par);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ResonanceNuclearDataModifier::set_modify_photon_data_flg(int int_val)
{
  modify_photon_data_flg = int_val;

  if( modify_photon_data_flg != 0 && modify_photon_data_flg != 1 )
  {
    string class_name = "ResonanceNuclearDataModifier";
    string func_name  = "set_modify_photon_data_flg(int int_val)";

    ostringstream oss01;
    oss01 << modify_photon_data_flg;
    string str_data01 = "modify_photon_data_flg : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("The available modify_photon_data_flg is as follows:");
    err_com.push_back("  0 : do not modify photon data");
    err_com.push_back("  1 : modify photon data");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ResonanceNuclearDataModifier::set_endf6_parser_no_cov(Endf6ParserNoCov& parser_obj)
{
  clear_parser_data();
  
  parser_no_cov.set_mf01_mt451_data(parser_obj.get_mf01_mt451_data());
  parser_no_cov.set_mf02_mt151_data(parser_obj.get_mf02_mt151_data());
  parser_no_cov.set_mf02_mt152_data(parser_obj.get_mf02_mt152_data());
  parser_no_cov.set_mf03_data(parser_obj.get_mf03_data());
  parser_no_cov.set_mf10_data(parser_obj.get_mf10_data());
  parser_no_cov.set_mf12_data(parser_obj.get_mf12_data());
  parser_no_cov.set_mf13_data(parser_obj.get_mf13_data());
  parser_no_cov.set_mf23_data(parser_obj.get_mf23_data());

  set_endf6_parser_data();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ResonanceNuclearDataModifier::set_nucl_data_obj(NuclearDataObject& nucl_data_obj)
{
  Endf6Converter    conv_obj;
  Endf6ParserNoCov  parser_obj;
  conv_obj.convert_frendy_to_endf_format(nucl_data_obj, parser_obj);

  set_endf6_parser_no_cov(parser_obj);
  parser_obj.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ResonanceNuclearDataModifier::set_endf6_parser_data()
{
  endf_parser_flg = 1;

  mf01mt451_par = parser_no_cov.get_mf01_mt451_data();
  mf02mt151_par = parser_no_cov.get_mf02_mt151_data();
  mf02mt152_par = parser_no_cov.get_mf02_mt152_data();
  mf03_par      = parser_no_cov.get_mf03_data();
  mf10_par      = parser_no_cov.get_mf10_data();
  mf12_par      = parser_no_cov.get_mf12_data();
  mf13_par      = parser_no_cov.get_mf13_data();
  mf23_par      = parser_no_cov.get_mf23_data();

  mf02mt151_par_mod = mf02mt151_par;

  mat_no   = mf01mt451_par.get_mat_no();
  reso_flg = mf01mt451_par.get_LRP();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ResonanceNuclearDataModifier::set_modified_endf6_parser_data()
{
  parser_no_cov.set_mf01_mt451_data(mf01mt451_par);
  parser_no_cov.set_mf02_mt151_data(mf02mt151_par_mod);
  parser_no_cov.set_mf02_mt152_data(mf02mt152_par);
  parser_no_cov.set_mf03_data(mf03_par);
  parser_no_cov.set_mf10_data(mf10_par);
  parser_no_cov.set_mf12_data(mf12_par);
  parser_no_cov.set_mf13_data(mf13_par);
  parser_no_cov.set_mf23_data(mf23_par);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ResonanceNuclearDataModifier::set_ene_grid(vector<Real8>& real_vec)
{
  merge_grid_flg  = 1;
  modify_endf_flg = 0;
  ene_grid        = real_vec;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ResonanceNuclearDataModifier::set_sig_data(vector<vector<Real8> >& real_vec)
{
  merge_xs_flg    = 1;
  modify_endf_flg = 0;
  sig_data        = real_vec;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ResonanceNuclearDataModifier::set_reso_ene_grid(vector<vector<vector<Real8> > >& real_vec)
{
  reso_grid_flg   = 1;
  modify_endf_flg = 0;
  reso_ene_grid   = real_vec;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ResonanceNuclearDataModifier::set_reso_sig_data(vector<vector<vector<vector<Real8> > > >& real_vec)
{
  reso_xs_flg     = 1;
  modify_endf_flg = 0;
  reso_sig_data   = real_vec;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

int                    ResonanceNuclearDataModifier::get_modify_photon_data_flg()
{
  return modify_photon_data_flg;
}

Endf6ParserNoCov       ResonanceNuclearDataModifier::get_endf6_parser_no_cov()
{
  modify_endf();
  
  return parser_no_cov;
}

NuclearDataObject      ResonanceNuclearDataModifier::get_nucl_data_obj()
{
  modify_endf();

  Endf6Converter    conv_obj;
  NuclearDataObject nucl_data_obj;
  conv_obj.convert_endf_format_to_frendy(parser_no_cov, nucl_data_obj);

  return nucl_data_obj;
}

vector<Real8>          ResonanceNuclearDataModifier::get_ene_grid()
{
  return ene_grid;
}

vector<vector<Real8> > ResonanceNuclearDataModifier::get_sig_data()
{
  return sig_data;
}

vector<vector<vector<Real8> > >          ResonanceNuclearDataModifier::get_reso_ene_grid()
{
  return reso_ene_grid;
}

vector<vector<vector<vector<Real8> > > > ResonanceNuclearDataModifier::get_reso_sig_data()
{
  return reso_sig_data;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

