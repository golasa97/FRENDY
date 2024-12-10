#include "EndfUtils/MFxxMTyyyConverter/MF02MT151Converter.hpp"

using namespace frendy;

//constructor
MF02MT151Converter::MF02MT151Converter(void)
{
}

//destructor
MF02MT151Converter::~MF02MT151Converter(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//ResonanceDataContainer -> MF02MT151Parser
void MF02MT151Converter::convert_frendy_to_endf_format( ResonanceDataContainer& frendy_obj, MF02MT151Parser& endf_obj )
{
  endf_obj.clear();
  MF02MT151ConverterBreitWigner    bw_conv_data_obj;
  MF02MT151ConverterReichMoore     rm_conv_data_obj;
  MF02MT151ConverterAdlerAdler     adler_conv_data_obj;
  MF02MT151ConverterRMatrixLimited r_matrix_conv_data_obj;
  MF02MT151ConverterUnresolved     unreso_conv_data_obj;
  
  BreitWignerDataContainer         bw_data_obj;
  ReichMooreDataContainer          rm_data_obj;
  AdlerAdlerDataContainer          adler_data_obj;
  RMatrixLimitedDataContainer      r_matrix_data_obj;
  UnresolvedResonanceDataContainer unreso_data_obj;

  //Get frendy data
  vector<Real>                      ZAI           = frendy_obj.get_mat_data_isotope();
  vector<Real>                      ABN           = frendy_obj.get_abundance_isotope();
  vector<Integer>                   LFW           = frendy_obj.get_fis_width_flg();
  vector<vector<Real> >             EL            = frendy_obj.get_lower_ene_limit();
  vector<vector<Real> >             EH            = frendy_obj.get_upper_ene_limit();
  vector<vector<Integer> >          LRU           = frendy_obj.get_reso_region_flg();
  vector<vector<Integer> >          LRF           = frendy_obj.get_xs_formula_flg();
  vector<vector<Integer> >          NRO           = frendy_obj.get_scat_radius_ene_dependence_flg();
  vector<vector<Integer> >          NAPS          = frendy_obj.get_radius_calc_flg();
  vector<vector<Real> >             SPI           = frendy_obj.get_spin_data();
  vector<vector<Real> >             AP            = frendy_obj.get_scat_radius();
  vector<vector<vector<Integer> > > INT_AP_NRO    = frendy_obj.get_scat_radius_tab_int_data();
  vector<vector<vector<Integer> > > NBT_AP_NRO    = frendy_obj.get_scat_radius_tab_range_data();
  vector<vector<vector<Real> > >    E_INT_AP_NRO  = frendy_obj.get_scat_radius_tab_ene_data();
  vector<vector<vector<Real> > >    AP_TAB_NRO    = frendy_obj.get_scat_radius_tab_data();
  vector<vector<vector<Integer> > > L             = frendy_obj.get_l_value();
  vector<vector<vector<Real> > >    AWRI          = frendy_obj.get_mass_isotope();

  Integer mat_no = 0;
  if( static_cast<int>(ZAI.size())  == 0 && static_cast<int>(ABN.size()) == 0 &&
      static_cast<int>(LFW.size())  == 0 && static_cast<int>(EL.size())  == 0 &&
      static_cast<int>(EH.size())   == 0 && static_cast<int>(LRU.size()) == 0 &&
      static_cast<int>(LRF.size())  == 0 && static_cast<int>(NRO.size()) == 0 &&
      static_cast<int>(NAPS.size()) == 0 && static_cast<int>(SPI.size()) == 0 &&
      static_cast<int>(AP.size())   == 0 && static_cast<int>(L.size())   == 0 &&
      static_cast<int>(AWRI.size()) == 0 )
  {
    mat_no = unassigned_mat_no;
  }

  Integer                  NIS;
  vector<Integer>          NER;
  vector<vector<Integer> > NLS;
  vector<vector<vector<Integer> > > L_LRU01_LRF01, L_LRU01_LRF03, L_LRU01_LRF04, L_LRU02;
  
  int i_max = static_cast<int>(LRU.size());
  vector<int> j_max;
  j_max.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    j_max[i] = static_cast<int>(LRU[i].size());
  }

  NIS = static_cast<Integer>(i_max);
  NER.resize(i_max);
  NLS.resize(i_max);
  L_LRU01_LRF01.resize(i_max);
  L_LRU01_LRF03.resize(i_max);
  L_LRU01_LRF04.resize(i_max);
  L_LRU02.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    NER[i] = j_max[i];
    NLS[i].resize(j_max[i]);
    L_LRU01_LRF01[i].resize(j_max[i]);
    L_LRU01_LRF03[i].resize(j_max[i]);
    L_LRU01_LRF04[i].resize(j_max[i]);
    L_LRU02[i].resize(j_max[i]);
    for(int j=0; j<j_max[i]; j++)
    {
      NLS[i][j] = 0;
      if( LRU[i][j] == 1 )
      {
        if( LRF[i][j] == 1 || LRF[i][j] == 2 )
        {
          NLS[i][j]           = static_cast<Integer>(AWRI[i][j].size());
          L_LRU01_LRF01[i][j] = L[i][j];
          
          bw_data_obj = frendy_obj.get_bw_data_obj(i, j);
          bw_conv_data_obj.convert_frendy_to_endf_format(i, i_max, j, j_max, bw_data_obj, endf_obj);
          bw_data_obj.clear();
        }
        else if( LRF[i][j] == 3 )
        {
          NLS[i][j]           = static_cast<Integer>(AWRI[i][j].size());
          L_LRU01_LRF03[i][j] = L[i][j];
          
          rm_data_obj = frendy_obj.get_rm_data_obj(i, j);
          rm_conv_data_obj.convert_frendy_to_endf_format(i, i_max, j, j_max, rm_data_obj, endf_obj);
          rm_data_obj.clear();
        }
        else if( LRF[i][j] == 4 )
        {
          NLS[i][j]           = static_cast<Integer>(L[i][j].size());
          L_LRU01_LRF04[i][j] = L[i][j];
          
          adler_data_obj = frendy_obj.get_adler_data_obj(i, j);
          adler_conv_data_obj.convert_frendy_to_endf_format(i, i_max, j, j_max, adler_data_obj, endf_obj);
          adler_data_obj.clear();
        }
        else if( LRF[i][j] == 7 )
        {
          r_matrix_data_obj = frendy_obj.get_r_matrix_data_obj(i, j);
          r_matrix_conv_data_obj.convert_frendy_to_endf_format(i, i_max, j, j_max, r_matrix_data_obj, endf_obj);
          r_matrix_data_obj.clear();
        }
      }
      else if( LRU[i][j] == 2 )
      {
        NLS[i][j]     = static_cast<Integer>(AWRI[i][j].size());
        L_LRU02[i][j] = L[i][j];
        
        unreso_data_obj = frendy_obj.get_unreso_data_obj(i, j);
        unreso_conv_data_obj.convert_frendy_to_endf_format(i, i_max, j, j_max, unreso_data_obj, endf_obj);
        unreso_data_obj.clear();
      }
    }
  }

  //Set ENDF format data
  endf_obj.set_mat_no(mat_no);
  endf_obj.set_NIS(NIS);
  endf_obj.set_ZAI(ZAI);
  endf_obj.set_ABN(ABN);
  endf_obj.set_LFW(LFW);
  endf_obj.set_NER(NER);
  endf_obj.set_EL(EL);
  endf_obj.set_EH(EH);
  endf_obj.set_LRU(LRU);
  endf_obj.set_LRF(LRF);
  endf_obj.set_NRO(NRO);
  endf_obj.set_NAPS(NAPS);
  endf_obj.set_SPI(SPI);
  endf_obj.set_AP(AP);
  endf_obj.set_NLS(NLS);
  endf_obj.set_AWRI(AWRI);
  endf_obj.set_NBT_AP_NRO(NBT_AP_NRO);
  endf_obj.set_INT_AP_NRO(INT_AP_NRO);
  endf_obj.set_E_INT_AP_NRO(E_INT_AP_NRO);
  endf_obj.set_AP_TAB_NRO(AP_TAB_NRO);
  endf_obj.set_L_LRU01_LRF01(L_LRU01_LRF01);
  endf_obj.set_L_LRU01_LRF03(L_LRU01_LRF03);
  endf_obj.set_L_LRU01_LRF04(L_LRU01_LRF04);
  endf_obj.set_L_LRU02(L_LRU02);

  //Clear declared data
  ZAI.clear();
  ABN.clear();
  LFW.clear();
  clr_obj.clear_vec_array2_real(EL);
  clr_obj.clear_vec_array2_real(EH);
  clr_obj.clear_vec_array2_int(LRU);
  clr_obj.clear_vec_array2_int(LRF);
  clr_obj.clear_vec_array2_int(NRO);
  clr_obj.clear_vec_array2_int(NAPS);
  clr_obj.clear_vec_array2_real(SPI);
  clr_obj.clear_vec_array2_real(AP);
  clr_obj.clear_vec_array3_int(INT_AP_NRO);
  clr_obj.clear_vec_array3_int(NBT_AP_NRO);
  clr_obj.clear_vec_array3_real(E_INT_AP_NRO);
  clr_obj.clear_vec_array3_real(AP_TAB_NRO);
  clr_obj.clear_vec_array3_int(L);
  clr_obj.clear_vec_array3_real(AWRI);
  
  j_max.clear();
  NIS = 0;
  NER.clear();
  clr_obj.clear_vec_array2_int(NLS);
  clr_obj.clear_vec_array3_int(L_LRU01_LRF01);
  clr_obj.clear_vec_array3_int(L_LRU01_LRF03);
  clr_obj.clear_vec_array3_int(L_LRU01_LRF04);
  clr_obj.clear_vec_array3_int(L_LRU02);
  
  bw_data_obj.clear();
  rm_data_obj.clear();
  adler_data_obj.clear();
  r_matrix_data_obj.clear();
  unreso_data_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//MF02MT151Parser -> ResonanceDataContainer
void MF02MT151Converter::convert_endf_format_to_frendy( MF02MT151Parser& endf_obj, ResonanceDataContainer& frendy_obj )
{
  MF02MT151ConverterBreitWigner    bw_conv_data_obj;
  MF02MT151ConverterReichMoore     rm_conv_data_obj;
  MF02MT151ConverterAdlerAdler     adler_conv_data_obj;
  MF02MT151ConverterRMatrixLimited r_matrix_conv_data_obj;
  MF02MT151ConverterUnresolved     unreso_conv_data_obj;
  
  //Get frendy data
  vector<Real>                      mat_data_isotope               = endf_obj.get_ZAI();
  vector<Real>                      abundance_isotope              = endf_obj.get_ABN();
  vector<Integer>                   fis_width_flg                  = endf_obj.get_LFW();
  vector<vector<Real> >             lower_ene_limit                = endf_obj.get_EL();
  vector<vector<Real> >             upper_ene_limit                = endf_obj.get_EH();
  vector<vector<Integer> >          reso_region_flg                = endf_obj.get_LRU();
  vector<vector<Integer> >          xs_formula_flg                 = endf_obj.get_LRF();
  vector<vector<Integer> >          scat_radius_ene_dependence_flg = endf_obj.get_NRO();
  vector<vector<Integer> >          radius_calc_flg                = endf_obj.get_NAPS();
  vector<vector<Real> >             spin_data                      = endf_obj.get_SPI();
  vector<vector<Real> >             scat_radius                    = endf_obj.get_AP();
  vector<vector<vector<Integer> > > scat_radius_tab_int_data       = endf_obj.get_INT_AP_NRO();
  vector<vector<vector<Integer> > > scat_radius_tab_range_data     = endf_obj.get_NBT_AP_NRO();
  vector<vector<vector<Real> > >    scat_radius_tab_ene_data       = endf_obj.get_E_INT_AP_NRO();
  vector<vector<vector<Real> > >    scat_radius_tab_data           = endf_obj.get_AP_TAB_NRO();
  vector<vector<vector<Real> > >    mass_isotope                   = endf_obj.get_AWRI();

  vector<vector<vector<Integer> > >                 l_value;
  vector<vector<BreitWignerDataContainer> >         bw_data_obj;
  vector<vector<ReichMooreDataContainer> >          rm_data_obj;
  vector<vector<AdlerAdlerDataContainer> >          adler_data_obj;
  vector<vector<RMatrixLimitedDataContainer> >      r_matrix_data_obj;
  vector<vector<UnresolvedResonanceDataContainer> > unreso_data_obj;
  
  int i_max = static_cast<int>(reso_region_flg.size());
  l_value.resize(i_max);
  bw_data_obj.resize(i_max);
  rm_data_obj.resize(i_max);
  adler_data_obj.resize(i_max);
  r_matrix_data_obj.resize(i_max);
  unreso_data_obj.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(reso_region_flg[i].size());
    l_value[i].resize(j_max);
    bw_data_obj[i].resize(j_max);
    rm_data_obj[i].resize(j_max);
    adler_data_obj[i].resize(j_max);
    r_matrix_data_obj[i].resize(j_max);
    unreso_data_obj[i].resize(j_max);
    for(int j=0; j<j_max; j++)
    {
      if( reso_region_flg[i][j] == 1 )
      {
        if( xs_formula_flg[i][j] == 1 || xs_formula_flg[i][j] == 2 )
        {
          l_value[i][j] = endf_obj.get_L_LRU01_LRF01()[i][j];
          bw_conv_data_obj.convert_endf_format_to_frendy(i, j, endf_obj, bw_data_obj[i][j]);
        }
        else if( xs_formula_flg[i][j] == 3 )
        {
          l_value[i][j] = endf_obj.get_L_LRU01_LRF03()[i][j];
          rm_conv_data_obj.convert_endf_format_to_frendy(i, j, endf_obj, rm_data_obj[i][j]);
        }
        else if( xs_formula_flg[i][j] == 4 )
        {
          l_value[i][j] = endf_obj.get_L_LRU01_LRF04()[i][j];
          adler_conv_data_obj.convert_endf_format_to_frendy(i, j, endf_obj, adler_data_obj[i][j]);
        }
        else if( xs_formula_flg[i][j] == 7 )
        {
          l_value[i][j].resize(0);
          r_matrix_conv_data_obj.convert_endf_format_to_frendy(i, j, endf_obj, r_matrix_data_obj[i][j]);
        }
      }
      else if( reso_region_flg[i][j] == 2 )
      {
        l_value[i][j] = endf_obj.get_L_LRU02()[i][j];
        unreso_conv_data_obj.convert_endf_format_to_frendy(i, j, endf_obj, unreso_data_obj[i][j]);
      }
      else
      {
        l_value[i][j].resize(0);
      }
    }
  }
  
  //Set ENDF format data
  //frendy_obj.clear();
  //text
  //mat_no
  //AWR
  frendy_obj.set_mat_data_isotope(mat_data_isotope);
  frendy_obj.set_abundance_isotope(abundance_isotope);
  frendy_obj.set_fis_width_flg(fis_width_flg);
  frendy_obj.set_lower_ene_limit(lower_ene_limit);
  frendy_obj.set_upper_ene_limit(upper_ene_limit);
  frendy_obj.set_reso_region_flg(reso_region_flg);
  frendy_obj.set_xs_formula_flg(xs_formula_flg);
  frendy_obj.set_scat_radius_ene_dependence_flg(scat_radius_ene_dependence_flg);
  frendy_obj.set_radius_calc_flg(radius_calc_flg);
  frendy_obj.set_spin_data(spin_data);
  frendy_obj.set_scat_radius(scat_radius);
  frendy_obj.set_mass_isotope(mass_isotope);
  frendy_obj.set_scat_radius_tab_range_data(scat_radius_tab_range_data);
  frendy_obj.set_scat_radius_tab_int_data(scat_radius_tab_int_data);
  frendy_obj.set_scat_radius_tab_ene_data(scat_radius_tab_ene_data);
  frendy_obj.set_scat_radius_tab_data(scat_radius_tab_data);
  
  frendy_obj.set_l_value(l_value);
  frendy_obj.set_bw_data_obj(bw_data_obj);
  frendy_obj.set_rm_data_obj(rm_data_obj);
  frendy_obj.set_adler_data_obj(adler_data_obj);
  frendy_obj.set_r_matrix_data_obj(r_matrix_data_obj);
  frendy_obj.set_unreso_data_obj(unreso_data_obj);

  //Clear declared data
  mat_data_isotope.clear();
  abundance_isotope.clear();
  fis_width_flg.clear();
  clr_obj.clear_vec_array2_real(lower_ene_limit);
  clr_obj.clear_vec_array2_real(upper_ene_limit);
  clr_obj.clear_vec_array2_int(reso_region_flg);
  clr_obj.clear_vec_array2_int(xs_formula_flg);
  clr_obj.clear_vec_array2_int(scat_radius_ene_dependence_flg);
  clr_obj.clear_vec_array2_int(radius_calc_flg);
  clr_obj.clear_vec_array2_real(spin_data);
  clr_obj.clear_vec_array2_real(scat_radius);
  clr_obj.clear_vec_array3_int(scat_radius_tab_int_data);
  clr_obj.clear_vec_array3_int(scat_radius_tab_range_data);
  clr_obj.clear_vec_array3_real(scat_radius_tab_ene_data);
  clr_obj.clear_vec_array3_real(scat_radius_tab_data);
  clr_obj.clear_vec_array3_int(l_value);
  clr_obj.clear_vec_array3_real(mass_isotope);
  
  i_max = static_cast<int>(bw_data_obj.size());
  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(bw_data_obj[i].size());
    for(int j=0; j<j_max; j++)
    {
      bw_data_obj[i][j].clear();
      rm_data_obj[i][j].clear();
      adler_data_obj[i][j].clear();
      r_matrix_data_obj[i][j].clear();
      unreso_data_obj[i][j].clear();
    }
    bw_data_obj[i].resize(0);
    rm_data_obj[i].resize(0);
    adler_data_obj[i].resize(0);
    r_matrix_data_obj[i].resize(0);
    unreso_data_obj[i].resize(0);
  }
  bw_data_obj.resize(0);
  rm_data_obj.resize(0);
  adler_data_obj.resize(0);
  r_matrix_data_obj.resize(0);
  unreso_data_obj.resize(0);
}

