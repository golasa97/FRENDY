#include "EndfUtils/MFxxMTyyyConverter/MF32MT151Converter.hpp"

using namespace frendy;

//constructor
MF32MT151Converter::MF32MT151Converter(void)
{
}

//destructor
MF32MT151Converter::~MF32MT151Converter(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//CovarianceResonanceDataContainer -> MF32MT151Parser
void MF32MT151Converter::convert_frendy_to_endf_format( CovarianceResonanceDataContainer& frendy_obj, MF32MT151Parser& endf_obj )
{
  endf_obj.clear();
  MF32MT151ConverterCompatibleResolvedResonance  compatible_conv_obj;
  MF32MT151ConverterBreitWigner                  bw_conv_obj;
  MF32MT151ConverterBreitWignerCompact           bw_compact_conv_obj;
  MF32MT151ConverterReichMoore                   rm_conv_obj;
  MF32MT151ConverterReichMooreCompact            rm_compact_conv_obj;
  MF32MT151ConverterAdlerAdler                   adler_conv_obj;
  MF32MT151ConverterRMatrixLimited               r_matrix_conv_obj;
  MF32MT151ConverterRMatrixLimitedCompact        r_matrix_compact_conv_obj;
  MF32MT151ConverterUnresolvedResonance          unresolved_conv_obj;

  CompatibleResolvedResonanceDataContainer       compatible_obj;
  BreitWignerCovarianceDataContainer             bw_obj;
  ReichMooreCovarianceDataContainer              rm_obj;
  AdlerAdlerCovarianceDataContainer              adler_obj;
  RMatrixLimitedCovarianceDataContainer          r_matrix_obj;
  BreitWignerCompactCovarianceDataContainer      bw_compact_obj;
  ReichMooreCompactCovarianceDataContainer       rm_compact_obj;
  RMatrixLimitedCompactCovarianceDataContainer   r_matrix_compact_obj;
  UnresolvedResonanceCovarianceDataContainer     unreso_obj;

  //Get frendy data
  vector<Real>                                     ZAI   = frendy_obj.get_mat_data_isotope();
  vector<Real>                                     ABN   = frendy_obj.get_abundance_isotope();
  vector<Integer>                                  LFW   = frendy_obj.get_fis_width_flg();
  vector<vector<Real> >                            EL    = frendy_obj.get_lower_ene_limit();
  vector<vector<Real> >                            EH    = frendy_obj.get_upper_ene_limit();
  vector<vector<Integer> >                         LRU   = frendy_obj.get_reso_region_flg();
  vector<vector<Integer> >                         LRF   = frendy_obj.get_xs_formula_flg();
  vector<vector<Integer> >                         NRO   = frendy_obj.get_scat_radius_ene_dependence_flg();
  vector<vector<Integer> >                         NAPS  = frendy_obj.get_radius_calc_flg();
  vector<vector<Real> >                            SPI   = frendy_obj.get_spin_data();
  vector<vector<Real> >                            AP    = frendy_obj.get_scat_radius();
  vector<vector<Integer> >                         LAD   = frendy_obj.get_angular_distr_calc_flg();
  vector<vector<Integer> >                         LCOMP = frendy_obj.get_compatibility_flg();
  vector<vector<vector<Integer> > >                LB    = frendy_obj.get_cov_matrix_data_flg();
  vector<vector<vector<vector<Real> > > >          E_K   = frendy_obj.get_cov_matrix_ene_k();
  vector<vector<vector<vector<vector<Real> > > > > F_K   = frendy_obj.get_cov_matrix_coef_k();
  vector<vector<vector<vector<Real> > > >          E_T   = frendy_obj.get_cov_matrix_ene_l();
  vector<vector<vector<vector<vector<Real> > > > > F_T   = frendy_obj.get_cov_matrix_coef_l();
  vector<vector<Real> >                            AWRI  = frendy_obj.get_mass_isotope();

  Integer mat_no = 0;
  if( static_cast<int>(ZAI.size())  == 0 && static_cast<int>(ABN.size())   == 0 &&
      static_cast<int>(LFW.size())  == 0 && static_cast<int>(EL.size())    == 0 &&
      static_cast<int>(EH.size())   == 0 && static_cast<int>(LRU.size())   == 0 &&
      static_cast<int>(LRF.size())  == 0 && static_cast<int>(NRO.size())   == 0 &&
      static_cast<int>(NAPS.size()) == 0 && static_cast<int>(SPI.size())   == 0 &&
      static_cast<int>(AP.size())   == 0 && static_cast<int>(LCOMP.size()) == 0 &&
      static_cast<int>(LB.size())   == 0 && static_cast<int>(E_K.size())   == 0 &&
      static_cast<int>(F_K.size())  == 0 && static_cast<int>(E_T.size())   == 0 &&
      static_cast<int>(F_T.size())  == 0 && static_cast<int>(AWRI.size())  == 0 )
  {
    mat_no = unassigned_mat_no;
  }

  Integer NIS;
  vector<Integer> NER;
  vector<vector<Integer> > NLS;
  vector<vector<Integer> > ISR;
  vector<vector<Integer> > NI;
  vector<vector<vector<Integer> > > LT;
  
  int i_max = static_cast<int>(LCOMP.size());
  vector<int> j_max;
  j_max.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    j_max[i] = static_cast<int>(LCOMP[i].size());
  }

  NIS = i_max;
  NER.resize(i_max);
  NLS.resize(i_max);
  ISR.resize(i_max);
  NI.resize(i_max);
  LT.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    NER[i] = j_max[i];
    NLS[i].resize(j_max[i]);
    ISR[i].resize(j_max[i]);
    NI[i].resize(j_max[i]);
    LT[i].resize(j_max[i]);
    for(int j=0; j<j_max[i]; j++)
    {
      NI[i][j]  = static_cast<Integer>(LB[i][j].size());
      NLS[i][j] = 0;
      ISR[i][j] = 0;

      if( NI[i][j] > 0 )
      {
        int k_max = static_cast<int>(NI[i][j]);
        LT[i][j].resize(k_max);
        for(int k=0; k<k_max; k++)
        {
          LT[i][j][k] = 0;
          if( LB[i][j][k] >= 0 && LB[i][j][k] <= 4 )
          {
            LT[i][j][k] = static_cast<Integer>(E_T[i][j][k].size());
          }
          else if( LB[i][j][k]==5 )
          {
            if( static_cast<int>(F_K[i][j][k].size()) > 2 )
            {
              if( F_K[i][j][k][0].size() != F_K[i][j][k][1].size() )
              {
                LT[i][j][k] = 1;
              }
            }
          }
        }
      }
      else
      {
        if( LCOMP[i][j] == 0 )
        {
          if( LRU[i][j] == 2 )
          {
            unreso_obj = frendy_obj.get_unreso_obj(i, j);
            unresolved_conv_obj.convert_frendy_to_endf_format(i, i_max, j, j_max, unreso_obj, endf_obj);
            
            NLS[i][j] = static_cast<Integer>(unreso_obj.get_mass_isotope().size());
            unreso_obj.clear();
          }
          else
          {
            compatible_obj = frendy_obj.get_compatible_obj(i, j);
            compatible_conv_obj.convert_frendy_to_endf_format(i, i_max, j, j_max, compatible_obj, endf_obj);
            
            NLS[i][j] = static_cast<Integer>(compatible_obj.get_mass_isotope().size());
            
            if( fabs(compatible_obj.get_scat_radius_uncertainty()) > min_value )
            {
              ISR[i][j] = 1;
            }
            compatible_obj.clear();
          }
        }
        else if( LCOMP[i][j] == 1 )
        {
          if( LRF[i][j] == 1 || LRF[i][j] == 2 )
          {
            bw_obj = frendy_obj.get_bw_obj(i, j);
            bw_conv_obj.convert_frendy_to_endf_format(i, i_max, j, j_max, bw_obj, endf_obj);
            
            if( fabs(bw_obj.get_scat_radius_uncertainty()) > min_value )
            {
              ISR[i][j] = 1;
            }
            bw_obj.clear();
          }
          else if( LRF[i][j] == 3 )
          {
            rm_obj = frendy_obj.get_rm_obj(i, j);
            rm_conv_obj.convert_frendy_to_endf_format(i, i_max, j, j_max, rm_obj, endf_obj);
            
            if( static_cast<int>(rm_obj.get_scat_radius_uncertainty().size()) > 0 )
            {
              ISR[i][j] = 1;
            }
            rm_obj.clear();
          }
          else if( LRF[i][j] == 4 )
          {
            adler_obj = frendy_obj.get_adler_obj(i, j);
            adler_conv_obj.convert_frendy_to_endf_format(i, i_max, j, j_max, adler_obj, endf_obj);
            
            if( fabs(adler_obj.get_scat_radius_uncertainty()) > min_value )
            {
              ISR[i][j] = 1;
            }
            adler_obj.clear();
          }
          else if( LRF[i][j] == 7 )
          {
            r_matrix_obj = frendy_obj.get_r_matrix_obj(i, j);
            r_matrix_conv_obj.convert_frendy_to_endf_format(i, i_max, j, j_max, r_matrix_obj, endf_obj);
            
            NLS[i][j] = static_cast<Integer>(r_matrix_obj.get_scat_radius_list_uncertainty().size());
            if( NLS[i][j] > 0 )
            {
              ISR[i][j] = 1;
            }
            r_matrix_obj.clear();
          }
        }
        else if( LCOMP[i][j] == 2 )
        {
          if( LRF[i][j] == 1 || LRF[i][j] == 2 )
          {
            bw_compact_obj = frendy_obj.get_bw_compact_obj(i, j);
            bw_compact_conv_obj.convert_frendy_to_endf_format(i, i_max, j, j_max, bw_compact_obj, endf_obj);
            
            if( fabs(bw_compact_obj.get_scat_radius_uncertainty()) > min_value )
            {
              ISR[i][j] = 1;
            }
            bw_compact_obj.clear();
          }
          else if( LRF[i][j] == 3 )
          {
            rm_compact_obj = frendy_obj.get_rm_compact_obj(i, j);
            rm_compact_conv_obj.convert_frendy_to_endf_format(i, i_max, j, j_max, rm_compact_obj, endf_obj);
            
            if( static_cast<int>(rm_compact_obj.get_scat_radius_uncertainty().size()) > 0 )
            {
              ISR[i][j] = 1;
            }
            rm_compact_obj.clear();
          }
          else if( LRF[i][j] == 7 )
          {
            r_matrix_compact_obj = frendy_obj.get_r_matrix_compact_obj(i, j);
            r_matrix_compact_conv_obj.convert_frendy_to_endf_format(i, i_max, j, j_max, r_matrix_compact_obj, endf_obj);
            
            NLS[i][j] = static_cast<Integer>(r_matrix_compact_obj.get_scat_radius_list_uncertainty().size());
            if( NLS[i][j] > 0 )
            {
              ISR[i][j] = 1;
            }
            r_matrix_compact_obj.clear();
          }
        }
      }
    }
  }
  
  //Set ENDF format data
  endf_obj.set_mat_no(mat_no);
  endf_obj.set_AWRI(AWRI);
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
  endf_obj.set_LAD(LAD);
  endf_obj.set_LCOMP(LCOMP);
  endf_obj.set_NLS(NLS);
  endf_obj.set_ISR(ISR);
  
  endf_obj.set_NI(NI);
  endf_obj.set_LB(LB);
  endf_obj.set_LT(LT);
  endf_obj.set_E_K(E_K);
  endf_obj.set_E_T(E_T);
  endf_obj.set_F_K(F_K);
  endf_obj.set_F_T(F_T);

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
  clr_obj.clear_vec_array2_int(LAD);
  clr_obj.clear_vec_array2_int(LCOMP);
  clr_obj.clear_vec_array3_int(LB);
  clr_obj.clear_vec_array4_real(E_K);
  clr_obj.clear_vec_array5_real(F_K);
  clr_obj.clear_vec_array4_real(E_T);
  clr_obj.clear_vec_array5_real(F_T);
  clr_obj.clear_vec_array2_real(AWRI);
  
  j_max.clear();
  NIS = 0;
  NER.clear();
  clr_obj.clear_vec_array2_int(NLS);
  clr_obj.clear_vec_array2_int(ISR);
  clr_obj.clear_vec_array2_int(NI);
  clr_obj.clear_vec_array3_int(LT);
  
  compatible_obj.clear();
  bw_obj.clear();
  rm_obj.clear();
  adler_obj.clear();
  r_matrix_obj.clear();
  bw_compact_obj.clear();
  rm_compact_obj.clear();
  r_matrix_compact_obj.clear();
  unreso_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//MF32MT151Parser -> CovarianceResonanceDataContainer
void MF32MT151Converter::convert_endf_format_to_frendy( MF32MT151Parser& endf_obj, CovarianceResonanceDataContainer& frendy_obj )
{
  MF32MT151ConverterCompatibleResolvedResonance  compatible_conv_obj;
  MF32MT151ConverterBreitWigner                  bw_conv_obj;
  MF32MT151ConverterBreitWignerCompact           bw_compact_conv_obj;
  MF32MT151ConverterReichMoore                   rm_conv_obj;
  MF32MT151ConverterReichMooreCompact            rm_compact_conv_obj;
  MF32MT151ConverterAdlerAdler                   adler_conv_obj;
  MF32MT151ConverterRMatrixLimited               r_matrix_conv_obj;
  MF32MT151ConverterRMatrixLimitedCompact        r_matrix_compact_conv_obj;
  MF32MT151ConverterUnresolvedResonance          unresolved_conv_obj;

  //Get frendy data
  vector<Real>                                     mat_data_isotope               = endf_obj.get_ZAI();
  vector<Real>                                     abundance_isotope              = endf_obj.get_ABN();
  vector<Integer>                                  fis_width_flg                  = endf_obj.get_LFW();
  vector<vector<Real> >                            lower_ene_limit                = endf_obj.get_EL();
  vector<vector<Real> >                            upper_ene_limit                = endf_obj.get_EH();
  vector<vector<Integer> >                         reso_region_flg                = endf_obj.get_LRU();
  vector<vector<Integer> >                         xs_formula_flg                 = endf_obj.get_LRF();
  vector<vector<Integer> >                         scat_radius_ene_dependence_flg = endf_obj.get_NRO();
  vector<vector<Integer> >                         radius_calc_flg                = endf_obj.get_NAPS();
  vector<vector<Real> >                            spin_data                      = endf_obj.get_SPI();
  vector<vector<Real> >                            scat_radius                    = endf_obj.get_AP();
  vector<vector<Integer> >                         angular_distr_calc_flg         = endf_obj.get_LAD();
  vector<vector<Integer> >                         compatibility_flg              = endf_obj.get_LCOMP();
  vector<vector<vector<Integer> > >                cov_matrix_data_flg            = endf_obj.get_LB();
  vector<vector<vector<vector<Real> > > >          cov_matrix_ene_k               = endf_obj.get_E_K();
  vector<vector<vector<vector<vector<Real> > > > > cov_matrix_coef_k              = endf_obj.get_F_K();
  vector<vector<vector<vector<Real> > > >          cov_matrix_ene_l               = endf_obj.get_E_T();
  vector<vector<vector<vector<vector<Real> > > > > cov_matrix_coef_l              = endf_obj.get_F_T();
  vector<vector<Real> >                            mass_isotope                   = endf_obj.get_AWRI(); //The data name is not found in Parser class.

  vector<vector<CompatibleResolvedResonanceDataContainer> >      compatible_obj;
  vector<vector<BreitWignerCovarianceDataContainer> >            bw_obj;
  vector<vector<ReichMooreCovarianceDataContainer> >             rm_obj;
  vector<vector<AdlerAdlerCovarianceDataContainer> >             adler_obj;
  vector<vector<RMatrixLimitedCovarianceDataContainer> >         r_matrix_obj;
  vector<vector<BreitWignerCompactCovarianceDataContainer> >     bw_compact_obj;
  vector<vector<ReichMooreCompactCovarianceDataContainer> >      rm_compact_obj;
  vector<vector<RMatrixLimitedCompactCovarianceDataContainer> >  r_matrix_compact_obj;
  vector<vector<UnresolvedResonanceCovarianceDataContainer> >    unreso_obj;
  
  int i_max = static_cast<int>(reso_region_flg.size());
  compatible_obj.resize(i_max);
  bw_obj.resize(i_max);
  rm_obj.resize(i_max);
  adler_obj.resize(i_max);
  r_matrix_obj.resize(i_max);
  bw_compact_obj.resize(i_max);
  rm_compact_obj.resize(i_max);
  r_matrix_compact_obj.resize(i_max);
  unreso_obj.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(reso_region_flg[i].size());
    compatible_obj[i].resize(j_max);
    bw_obj[i].resize(j_max);
    rm_obj[i].resize(j_max);
    adler_obj[i].resize(j_max);
    r_matrix_obj[i].resize(j_max);
    bw_compact_obj[i].resize(j_max);
    rm_compact_obj[i].resize(j_max);
    r_matrix_compact_obj[i].resize(j_max);
    unreso_obj[i].resize(j_max);
    for(int j=0; j<j_max; j++)
    {
      if( compatibility_flg[i][j] == 0 )
      {
        if( reso_region_flg[i][j] == 2 )
        {
          unresolved_conv_obj.convert_endf_format_to_frendy(i, j, endf_obj, unreso_obj[i][j]);
        }
        else
        {
          compatible_conv_obj.convert_endf_format_to_frendy(i, j, endf_obj, compatible_obj[i][j]);
        }
      }
      else if( compatibility_flg[i][j] == 1 )
      {
        if( xs_formula_flg[i][j] == 1 || xs_formula_flg[i][j] == 2 )
        {
          bw_conv_obj.convert_endf_format_to_frendy(i, j, endf_obj, bw_obj[i][j]);
        }
        else if( xs_formula_flg[i][j] == 3 )
        {
          rm_conv_obj.convert_endf_format_to_frendy(i, j, endf_obj, rm_obj[i][j]);
        }
        else if( xs_formula_flg[i][j] == 4 )
        {
          adler_conv_obj.convert_endf_format_to_frendy(i, j, endf_obj, adler_obj[i][j]);
        }
        else if( xs_formula_flg[i][j] == 7 )
        {
          r_matrix_conv_obj.convert_endf_format_to_frendy(i, j, endf_obj, r_matrix_obj[i][j]);
        }
      }
      else if( compatibility_flg[i][j] == 2 )
      {
        if( xs_formula_flg[i][j] == 1 || xs_formula_flg[i][j] == 2 )
        {
          bw_compact_conv_obj.convert_endf_format_to_frendy(i, j, endf_obj, bw_compact_obj[i][j]);
        }
        else if( xs_formula_flg[i][j] == 3 )
        {
          rm_compact_conv_obj.convert_endf_format_to_frendy(i, j, endf_obj, rm_compact_obj[i][j]);
        }
        else if( xs_formula_flg[i][j] == 7 )
        {
          r_matrix_compact_conv_obj.convert_endf_format_to_frendy(i, j, endf_obj, r_matrix_compact_obj[i][j]);
        }
      }
    }
  }
  
  //Set ENDF format data
  //frendy_obj.clear();
  //text
  //mat_no
  //AWR
  frendy_obj.set_mass_isotope(mass_isotope);
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
  frendy_obj.set_angular_distr_calc_flg(angular_distr_calc_flg);
  frendy_obj.set_compatibility_flg(compatibility_flg);
  
  frendy_obj.set_cov_matrix_data_flg(cov_matrix_data_flg);
  frendy_obj.set_cov_matrix_ene_k(cov_matrix_ene_k);
  frendy_obj.set_cov_matrix_ene_l(cov_matrix_ene_l);
  frendy_obj.set_cov_matrix_coef_k(cov_matrix_coef_k);
  frendy_obj.set_cov_matrix_coef_l(cov_matrix_coef_l);

  frendy_obj.set_compatible_obj( compatible_obj );
  frendy_obj.set_bw_obj( bw_obj );
  frendy_obj.set_rm_obj( rm_obj );
  frendy_obj.set_adler_obj( adler_obj );
  frendy_obj.set_r_matrix_obj( r_matrix_obj );
  frendy_obj.set_bw_compact_obj( bw_compact_obj );
  frendy_obj.set_rm_compact_obj( rm_compact_obj );
  frendy_obj.set_r_matrix_compact_obj( r_matrix_compact_obj );
  frendy_obj.set_unreso_obj( unreso_obj );


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
  clr_obj.clear_vec_array2_int(angular_distr_calc_flg);
  clr_obj.clear_vec_array2_int(compatibility_flg);
  clr_obj.clear_vec_array3_int(cov_matrix_data_flg);
  clr_obj.clear_vec_array4_real(cov_matrix_ene_k);
  clr_obj.clear_vec_array5_real(cov_matrix_coef_k);
  clr_obj.clear_vec_array4_real(cov_matrix_ene_l);
  clr_obj.clear_vec_array5_real(cov_matrix_coef_l);
  clr_obj.clear_vec_array2_real(mass_isotope);
  
  i_max = static_cast<int>(compatible_obj.size());
  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(compatible_obj[i].size());
    for(int j=0; j<j_max; j++)
    {
      compatible_obj[i][j].clear();
      bw_obj[i][j].clear();
      rm_obj[i][j].clear();
      adler_obj[i][j].clear();
      r_matrix_obj[i][j].clear();
      bw_compact_obj[i][j].clear();
      rm_compact_obj[i][j].clear();
      r_matrix_compact_obj[i][j].clear();
      unreso_obj[i][j].clear();
    }
    compatible_obj[i].resize(0);
    bw_obj[i].resize(0);
    rm_obj[i].resize(0);
    adler_obj[i].resize(0);
    r_matrix_obj[i].resize(0);
    bw_compact_obj[i].resize(0);
    rm_compact_obj[i].resize(0);
    r_matrix_compact_obj[i].resize(0);
    unreso_obj[i].resize(0);
  }
  compatible_obj.resize(0);
  bw_obj.resize(0);
  rm_obj.resize(0);
  adler_obj.resize(0);
  r_matrix_obj.resize(0);
  bw_compact_obj.resize(0);
  rm_compact_obj.resize(0);
  r_matrix_compact_obj.resize(0);
  unreso_obj.resize(0);
}

