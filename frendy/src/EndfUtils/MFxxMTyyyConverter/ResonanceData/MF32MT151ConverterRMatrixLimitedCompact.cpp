#include "EndfUtils/MFxxMTyyyConverter/ResonanceData/MF32MT151ConverterRMatrixLimitedCompact.hpp"

using namespace frendy;

//constructor
MF32MT151ConverterRMatrixLimitedCompact::MF32MT151ConverterRMatrixLimitedCompact(void)
{
}

//destructor
MF32MT151ConverterRMatrixLimitedCompact::~MF32MT151ConverterRMatrixLimitedCompact(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//RMatrixLimitedCompactCovarianceDataContainer -> MF32MT151Parser
void MF32MT151ConverterRMatrixLimitedCompact::convert_frendy_to_endf_format
  ( int& i, int& i_max, int& j, vector<int>& j_max,
  RMatrixLimitedCompactCovarianceDataContainer& frendy_obj, MF32MT151Parser& endf_obj )
{
  //Declare ENDF data
  vector<vector<Integer> >                         IFG                  = endf_obj.get_IFG();
  vector<vector<vector<vector<Real> > > >          DAP_LCOMP02_LRF07    = endf_obj.get_DAP_LCOMP02_LRF07();
  vector<vector<Integer> >                         NJSX_LCOMP02_LRF07   = endf_obj.get_NJSX_LCOMP02_LRF07();
  vector<vector<vector<Real> > >                   MA_LCOMP02_LRF07     = endf_obj.get_MA_LCOMP02_LRF07();
  vector<vector<vector<Real> > >                   MB_LCOMP02_LRF07     = endf_obj.get_MB_LCOMP02_LRF07();
  vector<vector<vector<Real> > >                   ZA_LCOMP02_LRF07     = endf_obj.get_ZA_LCOMP02_LRF07();
  vector<vector<vector<Real> > >                   ZB_LCOMP02_LRF07     = endf_obj.get_ZB_LCOMP02_LRF07();
  vector<vector<vector<Real> > >                   IA_LCOMP02_LRF07     = endf_obj.get_IA_LCOMP02_LRF07();
  vector<vector<vector<Real> > >                   IB_LCOMP02_LRF07     = endf_obj.get_IB_LCOMP02_LRF07();
  vector<vector<vector<Real> > >                   Q_LCOMP02_LRF07      = endf_obj.get_Q_LCOMP02_LRF07();
  vector<vector<vector<Real> > >                   PNT_LCOMP02_LRF07    = endf_obj.get_PNT_LCOMP02_LRF07();
  vector<vector<vector<Real> > >                   SHF_LCOMP02_LRF07    = endf_obj.get_SHF_LCOMP02_LRF07();
  vector<vector<vector<Real> > >                   MT_LCOMP02_LRF07     = endf_obj.get_MT_LCOMP02_LRF07();
  vector<vector<vector<Real> > >                   PA_LCOMP02_LRF07     = endf_obj.get_PA_LCOMP02_LRF07();
  vector<vector<vector<Real> > >                   PB_LCOMP02_LRF07     = endf_obj.get_PB_LCOMP02_LRF07();
  vector<vector<vector<Real> > >                   AJ_LCOMP02_LRF07     = endf_obj.get_AJ_LCOMP02_LRF07();
  vector<vector<vector<Real> > >                   PJ_LCOMP02_LRF07     = endf_obj.get_PJ_LCOMP02_LRF07();
  vector<vector<vector<vector<Real> > > >          PPI_LCOMP02_LRF07    = endf_obj.get_PPI_LCOMP02_LRF07();
  vector<vector<vector<vector<Real> > > >          L_LCOMP02_LRF07      = endf_obj.get_L_LCOMP02_LRF07();
  vector<vector<vector<vector<Real> > > >          SCH_LCOMP02_LRF07    = endf_obj.get_SCH_LCOMP02_LRF07();
  vector<vector<vector<vector<Real> > > >          BND_LCOMP02_LRF07    = endf_obj.get_BND_LCOMP02_LRF07();
  vector<vector<vector<vector<Real> > > >          APE_LCOMP02_LRF07    = endf_obj.get_APE_LCOMP02_LRF07();
  vector<vector<vector<vector<Real> > > >          APT_LCOMP02_LRF07    = endf_obj.get_APT_LCOMP02_LRF07();
  vector<vector<vector<vector<Real> > > >          ER_LCOMP02_LRF07     = endf_obj.get_ER_LCOMP02_LRF07();
  vector<vector<vector<vector<vector<Real> > > > > GAM_LCOMP02_LRF07    = endf_obj.get_GAM_LCOMP02_LRF07();
  vector<vector<vector<vector<Real> > > >          DER_LCOMP02_LRF07    = endf_obj.get_DER_LCOMP02_LRF07();
  vector<vector<vector<vector<vector<Real> > > > > DGAM_LCOMP02_LRF07   = endf_obj.get_DGAM_LCOMP02_LRF07();
  vector<vector<Integer> >                         NDIGIT_LCOMP02_LRF07 = endf_obj.get_NDIGIT_LCOMP02_LRF07();
  vector<vector<Integer> >                         NNN_LCOMP02_LRF07    = endf_obj.get_NNN_LCOMP02_LRF07();
  vector<vector<vector<Integer> > >                II_LCOMP02_LRF07     = endf_obj.get_II_LCOMP02_LRF07();
  vector<vector<vector<Integer> > >                JJ_LCOMP02_LRF07     = endf_obj.get_JJ_LCOMP02_LRF07();
  vector<vector<vector<vector<Integer> > > >       KIJ_LCOMP02_LRF07    = endf_obj.get_KIJ_LCOMP02_LRF07();
   
  vector<vector<Integer> >                         NM_LCOMP02_LRF07     = endf_obj.get_NM_LCOMP02_LRF07();
   
  //Resize ENDF data
  int ele_no = static_cast<int>(NJSX_LCOMP02_LRF07.size());
  if( ele_no == 0 )
  {
    IFG.resize(i_max);
    DAP_LCOMP02_LRF07.resize(i_max);
    NJSX_LCOMP02_LRF07.resize(i_max);
    MA_LCOMP02_LRF07.resize(i_max);
    MB_LCOMP02_LRF07.resize(i_max);
    ZA_LCOMP02_LRF07.resize(i_max);
    ZB_LCOMP02_LRF07.resize(i_max);
    IA_LCOMP02_LRF07.resize(i_max);
    IB_LCOMP02_LRF07.resize(i_max);
    Q_LCOMP02_LRF07.resize(i_max);
    PNT_LCOMP02_LRF07.resize(i_max);
    SHF_LCOMP02_LRF07.resize(i_max);
    MT_LCOMP02_LRF07.resize(i_max);
    PA_LCOMP02_LRF07.resize(i_max);
    PB_LCOMP02_LRF07.resize(i_max);
    AJ_LCOMP02_LRF07.resize(i_max);
    PJ_LCOMP02_LRF07.resize(i_max);
    PPI_LCOMP02_LRF07.resize(i_max);
    L_LCOMP02_LRF07.resize(i_max);
    SCH_LCOMP02_LRF07.resize(i_max);
    BND_LCOMP02_LRF07.resize(i_max);
    APE_LCOMP02_LRF07.resize(i_max);
    APT_LCOMP02_LRF07.resize(i_max);
    ER_LCOMP02_LRF07.resize(i_max);
    GAM_LCOMP02_LRF07.resize(i_max);
    DER_LCOMP02_LRF07.resize(i_max);
    DGAM_LCOMP02_LRF07.resize(i_max);
    NDIGIT_LCOMP02_LRF07.resize(i_max);
    NNN_LCOMP02_LRF07.resize(i_max);
    II_LCOMP02_LRF07.resize(i_max);
    JJ_LCOMP02_LRF07.resize(i_max);
    KIJ_LCOMP02_LRF07.resize(i_max);
    NM_LCOMP02_LRF07.resize(i_max);
    for(int i_tmp=0; i_tmp<i_max; i_tmp++)
    {
      IFG[i_tmp].resize(j_max[i_tmp]);
      DAP_LCOMP02_LRF07[i_tmp].resize(j_max[i_tmp]);
      NJSX_LCOMP02_LRF07[i_tmp].resize(j_max[i_tmp]);
      MA_LCOMP02_LRF07[i_tmp].resize(j_max[i_tmp]);
      MB_LCOMP02_LRF07[i_tmp].resize(j_max[i_tmp]);
      ZA_LCOMP02_LRF07[i_tmp].resize(j_max[i_tmp]);
      ZB_LCOMP02_LRF07[i_tmp].resize(j_max[i_tmp]);
      IA_LCOMP02_LRF07[i_tmp].resize(j_max[i_tmp]);
      IB_LCOMP02_LRF07[i_tmp].resize(j_max[i_tmp]);
      Q_LCOMP02_LRF07[i_tmp].resize(j_max[i_tmp]);
      PNT_LCOMP02_LRF07[i_tmp].resize(j_max[i_tmp]);
      SHF_LCOMP02_LRF07[i_tmp].resize(j_max[i_tmp]);
      MT_LCOMP02_LRF07[i_tmp].resize(j_max[i_tmp]);
      PA_LCOMP02_LRF07[i_tmp].resize(j_max[i_tmp]);
      PB_LCOMP02_LRF07[i_tmp].resize(j_max[i_tmp]);
      AJ_LCOMP02_LRF07[i_tmp].resize(j_max[i_tmp]);
      PJ_LCOMP02_LRF07[i_tmp].resize(j_max[i_tmp]);
      PPI_LCOMP02_LRF07[i_tmp].resize(j_max[i_tmp]);
      L_LCOMP02_LRF07[i_tmp].resize(j_max[i_tmp]);
      SCH_LCOMP02_LRF07[i_tmp].resize(j_max[i_tmp]);
      BND_LCOMP02_LRF07[i_tmp].resize(j_max[i_tmp]);
      APE_LCOMP02_LRF07[i_tmp].resize(j_max[i_tmp]);
      APT_LCOMP02_LRF07[i_tmp].resize(j_max[i_tmp]);
      ER_LCOMP02_LRF07[i_tmp].resize(j_max[i_tmp]);
      GAM_LCOMP02_LRF07[i_tmp].resize(j_max[i_tmp]);
      DER_LCOMP02_LRF07[i_tmp].resize(j_max[i_tmp]);
      DGAM_LCOMP02_LRF07[i_tmp].resize(j_max[i_tmp]);
      NDIGIT_LCOMP02_LRF07[i_tmp].resize(j_max[i_tmp]);
      NNN_LCOMP02_LRF07[i_tmp].resize(j_max[i_tmp]);
      II_LCOMP02_LRF07[i_tmp].resize(j_max[i_tmp]);
      JJ_LCOMP02_LRF07[i_tmp].resize(j_max[i_tmp]);
      KIJ_LCOMP02_LRF07[i_tmp].resize(j_max[i_tmp]);
      NM_LCOMP02_LRF07[i_tmp].resize(j_max[i_tmp]);
    }
  }
  else
  {
    if( ele_no != i_max )
    {
      string class_name = "MF32MT151ConverterRMatrixLimitedCompact";
      string func_name  = "convert_frendy_to_endf_format";
      ostringstream oss01, oss02, oss03, oss04;
      oss01 << i;
      oss02 << j;
      oss03 << ele_no;
      oss04 << i_max;
      string str_data01 = "(i, j) = (" + oss01.str() + ", " + oss02.str() + ")";
      string str_data02 = "  i_max from vector data : " + oss03.str();
      string str_data03 = "  i_max from parameter   : " + oss04.str();
      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back("The maximum element no i_max is not identical.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
     
    if( static_cast<int>(DAP_LCOMP02_LRF07[i].size()) != j_max[i] )
    {
      string class_name = "MF32MT151ConverterRMatrixLimitedCompact";
      string func_name  = "convert_frendy_to_endf_format";
      ostringstream oss01, oss02, oss03, oss04;
      oss01 << i;
      oss02 << j;
      oss03 <<  static_cast<int>(DAP_LCOMP02_LRF07[i].size());
      oss04 << j_max[i];
      string str_data01 = "(i, j) = (" + oss01.str() + ", " + oss02.str() + ")";
      string str_data02 = "  j_max from vector data : " + oss03.str();
      string str_data03 = "  j_max from parameter   : " + oss04.str();
      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back("The maximum element no j_max is not identical.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }

  //Get frendy data
  IFG[i][j]                  = frendy_obj.get_gam_width_flg();
  DAP_LCOMP02_LRF07[i][j]    = frendy_obj.get_scat_radius_list_uncertainty(); //Actual data name in Parser class is different (DAP_LRF07) 
  NJSX_LCOMP02_LRF07[i][j]   = frendy_obj.get_j_pi_no();
  MA_LCOMP02_LRF07[i][j]     = frendy_obj.get_mass_a();
  MB_LCOMP02_LRF07[i][j]     = frendy_obj.get_mass_b();
  ZA_LCOMP02_LRF07[i][j]     = frendy_obj.get_charge_a();
  ZB_LCOMP02_LRF07[i][j]     = frendy_obj.get_charge_b();
  IA_LCOMP02_LRF07[i][j]     = frendy_obj.get_spin_a();
  IB_LCOMP02_LRF07[i][j]     = frendy_obj.get_spin_b();
  Q_LCOMP02_LRF07[i][j]      = frendy_obj.get_q_value();
  PNT_LCOMP02_LRF07[i][j]    = frendy_obj.get_penetrability_calc_flg();
  SHF_LCOMP02_LRF07[i][j]    = frendy_obj.get_shift_factor_calc_flg();
  MT_LCOMP02_LRF07[i][j]     = frendy_obj.get_reaction_type_flg();
  PA_LCOMP02_LRF07[i][j]     = frendy_obj.get_parity_a();
  PB_LCOMP02_LRF07[i][j]     = frendy_obj.get_parity_b();
  AJ_LCOMP02_LRF07[i][j]     = frendy_obj.get_j_value_abs();
  PJ_LCOMP02_LRF07[i][j]     = frendy_obj.get_parity();
  PPI_LCOMP02_LRF07[i][j]    = frendy_obj.get_particle_pair_no();
  L_LCOMP02_LRF07[i][j]      = frendy_obj.get_l_value();
  SCH_LCOMP02_LRF07[i][j]    = frendy_obj.get_spin_channel();
  BND_LCOMP02_LRF07[i][j]    = frendy_obj.get_boundary_condition();
  APE_LCOMP02_LRF07[i][j]    = frendy_obj.get_scat_radius_eff();
  APT_LCOMP02_LRF07[i][j]    = frendy_obj.get_scat_radius_true();
  ER_LCOMP02_LRF07[i][j]     = frendy_obj.get_ene_reso();
  GAM_LCOMP02_LRF07[i][j]    = frendy_obj.get_gam_width();
  DER_LCOMP02_LRF07[i][j]    = frendy_obj.get_ene_reso_uncertainty();
  DGAM_LCOMP02_LRF07[i][j]   = frendy_obj.get_gam_width_uncertainty();
  NDIGIT_LCOMP02_LRF07[i][j] = frendy_obj.get_cov_matrix_digit_no(); //Actual data name in Parser class is different (NDIGIT) 
  NNN_LCOMP02_LRF07[i][j]    = frendy_obj.get_cov_param_no(); //Actual data name in Parser class is different (NNN) 
  II_LCOMP02_LRF07[i][j]     = frendy_obj.get_cov_matrix_location_i(); //Actual data name in Parser class is different (II) 
  JJ_LCOMP02_LRF07[i][j]     = frendy_obj.get_cov_matrix_location_j(); //Actual data name in Parser class is different (JJ) 
  KIJ_LCOMP02_LRF07[i][j]    = frendy_obj.get_cov_matrix_coef(); //Actual data name in Parser class is different (KIJ) 

  NM_LCOMP02_LRF07[i][j] = static_cast<Integer>(II_LCOMP02_LRF07[i][j].size());
  

  //Set ENDF format data
  //endf_obj.clear();
  endf_obj.set_IFG(IFG);
  endf_obj.set_DAP_LCOMP02_LRF07(DAP_LCOMP02_LRF07); //Actual data name in Parser class is different (DAP_LRF07) 
  endf_obj.set_NJSX_LCOMP02_LRF07(NJSX_LCOMP02_LRF07);
  endf_obj.set_MA_LCOMP02_LRF07(MA_LCOMP02_LRF07);
  endf_obj.set_MB_LCOMP02_LRF07(MB_LCOMP02_LRF07);
  endf_obj.set_ZA_LCOMP02_LRF07(ZA_LCOMP02_LRF07);
  endf_obj.set_ZB_LCOMP02_LRF07(ZB_LCOMP02_LRF07);
  endf_obj.set_IA_LCOMP02_LRF07(IA_LCOMP02_LRF07);
  endf_obj.set_IB_LCOMP02_LRF07(IB_LCOMP02_LRF07);
  endf_obj.set_Q_LCOMP02_LRF07(Q_LCOMP02_LRF07);
  endf_obj.set_PNT_LCOMP02_LRF07(PNT_LCOMP02_LRF07);
  endf_obj.set_SHF_LCOMP02_LRF07(SHF_LCOMP02_LRF07);
  endf_obj.set_MT_LCOMP02_LRF07(MT_LCOMP02_LRF07);
  endf_obj.set_PA_LCOMP02_LRF07(PA_LCOMP02_LRF07);
  endf_obj.set_PB_LCOMP02_LRF07(PB_LCOMP02_LRF07);
  endf_obj.set_AJ_LCOMP02_LRF07(AJ_LCOMP02_LRF07);
  endf_obj.set_PJ_LCOMP02_LRF07(PJ_LCOMP02_LRF07);
  endf_obj.set_PPI_LCOMP02_LRF07(PPI_LCOMP02_LRF07);
  endf_obj.set_L_LCOMP02_LRF07(L_LCOMP02_LRF07);
  endf_obj.set_SCH_LCOMP02_LRF07(SCH_LCOMP02_LRF07);
  endf_obj.set_BND_LCOMP02_LRF07(BND_LCOMP02_LRF07);
  endf_obj.set_APE_LCOMP02_LRF07(APE_LCOMP02_LRF07);
  endf_obj.set_APT_LCOMP02_LRF07(APT_LCOMP02_LRF07);
  endf_obj.set_ER_LCOMP02_LRF07(ER_LCOMP02_LRF07);
  endf_obj.set_DER_LCOMP02_LRF07(DER_LCOMP02_LRF07);
  endf_obj.set_GAM_LCOMP02_LRF07(GAM_LCOMP02_LRF07);
  endf_obj.set_DGAM_LCOMP02_LRF07(DGAM_LCOMP02_LRF07);
  endf_obj.set_NDIGIT_LCOMP02_LRF07(NDIGIT_LCOMP02_LRF07); //Actual data name in Parser class is different (NDIGIT) 
  endf_obj.set_NNN_LCOMP02_LRF07(NNN_LCOMP02_LRF07); //Actual data name in Parser class is different (NNN) 
  endf_obj.set_NM_LCOMP02_LRF07(NM_LCOMP02_LRF07); //Actual data name in Parser class is different (NM) 
  endf_obj.set_II_LCOMP02_LRF07(II_LCOMP02_LRF07); //Actual data name in Parser class is different (II) 
  endf_obj.set_JJ_LCOMP02_LRF07(JJ_LCOMP02_LRF07); //Actual data name in Parser class is different (JJ) 
  endf_obj.set_KIJ_LCOMP02_LRF07(KIJ_LCOMP02_LRF07); //Actual data name in Parser class is different (KIJ) 

  //Clear declared data
  clr_obj.clear_vec_array2_int(IFG);
  clr_obj.clear_vec_array4_real(DAP_LCOMP02_LRF07);
  clr_obj.clear_vec_array2_int(NJSX_LCOMP02_LRF07);
  clr_obj.clear_vec_array3_real(MA_LCOMP02_LRF07);
  clr_obj.clear_vec_array3_real(MB_LCOMP02_LRF07);
  clr_obj.clear_vec_array3_real(ZA_LCOMP02_LRF07);
  clr_obj.clear_vec_array3_real(ZB_LCOMP02_LRF07);
  clr_obj.clear_vec_array3_real(IA_LCOMP02_LRF07);
  clr_obj.clear_vec_array3_real(IB_LCOMP02_LRF07);
  clr_obj.clear_vec_array3_real(Q_LCOMP02_LRF07);
  clr_obj.clear_vec_array3_real(PNT_LCOMP02_LRF07);
  clr_obj.clear_vec_array3_real(SHF_LCOMP02_LRF07);
  clr_obj.clear_vec_array3_real(MT_LCOMP02_LRF07);
  clr_obj.clear_vec_array3_real(PA_LCOMP02_LRF07);
  clr_obj.clear_vec_array3_real(PB_LCOMP02_LRF07);
  clr_obj.clear_vec_array3_real(AJ_LCOMP02_LRF07);
  clr_obj.clear_vec_array3_real(PJ_LCOMP02_LRF07);
  clr_obj.clear_vec_array4_real(PPI_LCOMP02_LRF07);
  clr_obj.clear_vec_array4_real(L_LCOMP02_LRF07);
  clr_obj.clear_vec_array4_real(SCH_LCOMP02_LRF07);
  clr_obj.clear_vec_array4_real(BND_LCOMP02_LRF07);
  clr_obj.clear_vec_array4_real(APE_LCOMP02_LRF07);
  clr_obj.clear_vec_array4_real(APT_LCOMP02_LRF07);
  clr_obj.clear_vec_array4_real(ER_LCOMP02_LRF07);
  clr_obj.clear_vec_array5_real(GAM_LCOMP02_LRF07);
  clr_obj.clear_vec_array4_real(DER_LCOMP02_LRF07);
  clr_obj.clear_vec_array5_real(DGAM_LCOMP02_LRF07);
  clr_obj.clear_vec_array2_int(NDIGIT_LCOMP02_LRF07);
  clr_obj.clear_vec_array2_int(NNN_LCOMP02_LRF07);
  clr_obj.clear_vec_array2_int(NM_LCOMP02_LRF07);
  clr_obj.clear_vec_array3_int(II_LCOMP02_LRF07);
  clr_obj.clear_vec_array3_int(JJ_LCOMP02_LRF07);
  clr_obj.clear_vec_array4_int(KIJ_LCOMP02_LRF07);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//MF32MT151Parser -> RMatrixLimitedCompactCovarianceDataContainer
void MF32MT151ConverterRMatrixLimitedCompact::convert_endf_format_to_frendy( int& i, int& j,
  MF32MT151Parser& endf_obj, RMatrixLimitedCompactCovarianceDataContainer& frendy_obj )
{
  //Get frendy data
  Integer                        gam_width_flg                = endf_obj.get_IFG()[i][j];
  vector<vector<Real> >          scat_radius_list_uncertainty = endf_obj.get_DAP_LCOMP02_LRF07()[i][j]; //Actual data name in Parser class is different (DAP_LRF07) 
  Integer                        j_pi_no                      = endf_obj.get_NJSX_LCOMP02_LRF07()[i][j];
  vector<Real>                   mass_a                       = endf_obj.get_MA_LCOMP02_LRF07()[i][j];
  vector<Real>                   mass_b                       = endf_obj.get_MB_LCOMP02_LRF07()[i][j];
  vector<Real>                   charge_a                     = endf_obj.get_ZA_LCOMP02_LRF07()[i][j];
  vector<Real>                   charge_b                     = endf_obj.get_ZB_LCOMP02_LRF07()[i][j];
  vector<Real>                   spin_a                       = endf_obj.get_IA_LCOMP02_LRF07()[i][j];
  vector<Real>                   spin_b                       = endf_obj.get_IB_LCOMP02_LRF07()[i][j];
  vector<Real>                   q_value                      = endf_obj.get_Q_LCOMP02_LRF07()[i][j];
  vector<Real>                   penetrability_calc_flg       = endf_obj.get_PNT_LCOMP02_LRF07()[i][j];
  vector<Real>                   shift_factor_calc_flg        = endf_obj.get_SHF_LCOMP02_LRF07()[i][j];
  vector<Real>                   reaction_type_flg            = endf_obj.get_MT_LCOMP02_LRF07()[i][j];
  vector<Real>                   parity_a                     = endf_obj.get_PA_LCOMP02_LRF07()[i][j];
  vector<Real>                   parity_b                     = endf_obj.get_PB_LCOMP02_LRF07()[i][j];
  vector<Real>                   j_value_abs                  = endf_obj.get_AJ_LCOMP02_LRF07()[i][j];
  vector<Real>                   parity                       = endf_obj.get_PJ_LCOMP02_LRF07()[i][j];
  vector<vector<Real> >          particle_pair_no             = endf_obj.get_PPI_LCOMP02_LRF07()[i][j];
  vector<vector<Real> >          l_value                      = endf_obj.get_L_LCOMP02_LRF07()[i][j];
  vector<vector<Real> >          spin_channel                 = endf_obj.get_SCH_LCOMP02_LRF07()[i][j];
  vector<vector<Real> >          boundary_condition           = endf_obj.get_BND_LCOMP02_LRF07()[i][j];
  vector<vector<Real> >          scat_radius_eff              = endf_obj.get_APE_LCOMP02_LRF07()[i][j];
  vector<vector<Real> >          scat_radius_true             = endf_obj.get_APT_LCOMP02_LRF07()[i][j];
  vector<vector<Real> >          ene_reso                     = endf_obj.get_ER_LCOMP02_LRF07()[i][j];
  vector<vector<vector<Real> > > gam_width                    = endf_obj.get_GAM_LCOMP02_LRF07()[i][j];
  vector<vector<Real> >          ene_reso_uncertainty         = endf_obj.get_DER_LCOMP02_LRF07()[i][j];
  vector<vector<vector<Real> > > gam_width_uncertainty        = endf_obj.get_DGAM_LCOMP02_LRF07()[i][j];
  Integer                        cov_matrix_digit_no          = endf_obj.get_NDIGIT_LCOMP02_LRF07()[i][j]; //Actual data name in Parser class is different (NDIGIT) 
  Integer                        cov_param_no                 = endf_obj.get_NNN_LCOMP02_LRF07()[i][j]; //Actual data name in Parser class is different (NNN) 
  vector<Integer>                cov_matrix_location_i        = endf_obj.get_II_LCOMP02_LRF07()[i][j]; //Actual data name in Parser class is different (II) 
  vector<Integer>                cov_matrix_location_j        = endf_obj.get_JJ_LCOMP02_LRF07()[i][j]; //Actual data name in Parser class is different (JJ) 
  vector<vector<Integer> >       cov_matrix_coef              = endf_obj.get_KIJ_LCOMP02_LRF07()[i][j]; //Actual data name in Parser class is different (KIJ) 

  //Set ENDF format data
  frendy_obj.clear();
  frendy_obj.set_gam_width_flg(gam_width_flg);
  frendy_obj.set_scat_radius_list_uncertainty(scat_radius_list_uncertainty); //Actual data name in Parser class is different (DAP_LRF07) 
  frendy_obj.set_j_pi_no(j_pi_no);
  frendy_obj.set_mass_a(mass_a);
  frendy_obj.set_mass_b(mass_b);
  frendy_obj.set_charge_a(charge_a);
  frendy_obj.set_charge_b(charge_b);
  frendy_obj.set_spin_a(spin_a);
  frendy_obj.set_spin_b(spin_b);
  frendy_obj.set_q_value(q_value);
  frendy_obj.set_penetrability_calc_flg(penetrability_calc_flg);
  frendy_obj.set_shift_factor_calc_flg(shift_factor_calc_flg);
  frendy_obj.set_reaction_type_flg(reaction_type_flg);
  frendy_obj.set_parity_a(parity_a);
  frendy_obj.set_parity_b(parity_b);
  frendy_obj.set_j_value_abs(j_value_abs);
  frendy_obj.set_parity(parity);
  frendy_obj.set_particle_pair_no(particle_pair_no);
  frendy_obj.set_l_value(l_value);
  frendy_obj.set_spin_channel(spin_channel);
  frendy_obj.set_boundary_condition(boundary_condition);
  frendy_obj.set_scat_radius_eff(scat_radius_eff);
  frendy_obj.set_scat_radius_true(scat_radius_true);
  frendy_obj.set_ene_reso(ene_reso);
  frendy_obj.set_ene_reso_uncertainty(ene_reso_uncertainty);
  frendy_obj.set_gam_width(gam_width);
  frendy_obj.set_gam_width_uncertainty(gam_width_uncertainty);
  frendy_obj.set_cov_matrix_digit_no(cov_matrix_digit_no); //Actual data name in Parser class is different (NDIGIT) 
  frendy_obj.set_cov_param_no(cov_param_no); //Actual data name in Parser class is different (NNN) 
  frendy_obj.set_cov_matrix_location_i(cov_matrix_location_i); //Actual data name in Parser class is different (II) 
  frendy_obj.set_cov_matrix_location_j(cov_matrix_location_j); //Actual data name in Parser class is different (JJ) 
  frendy_obj.set_cov_matrix_coef(cov_matrix_coef); //Actual data name in Parser class is different (KIJ) 

  //Clear declared data
  clr_obj.clear_vec_array2_real(scat_radius_list_uncertainty);
  j_pi_no                      = 0;
  mass_a.clear();
  mass_b.clear();
  charge_a.clear();
  charge_b.clear();
  spin_a.clear();
  spin_b.clear();
  q_value.clear();
  penetrability_calc_flg.clear();
  shift_factor_calc_flg.clear();
  reaction_type_flg.clear();
  parity_a.clear();
  parity_b.clear();
  j_value_abs.clear();
  parity.clear();
  clr_obj.clear_vec_array2_real(particle_pair_no);
  clr_obj.clear_vec_array2_real(l_value);
  clr_obj.clear_vec_array2_real(spin_channel);
  clr_obj.clear_vec_array2_real(boundary_condition);
  clr_obj.clear_vec_array2_real(scat_radius_eff);
  clr_obj.clear_vec_array2_real(scat_radius_true);
  clr_obj.clear_vec_array2_real(ene_reso);
  clr_obj.clear_vec_array3_real(gam_width);
  clr_obj.clear_vec_array2_real(ene_reso_uncertainty);
  clr_obj.clear_vec_array3_real(gam_width_uncertainty);
  cov_matrix_digit_no          = 0;
  cov_param_no                 = 0;
  cov_matrix_location_i.clear();
  cov_matrix_location_j.clear();
  clr_obj.clear_vec_array2_int(cov_matrix_coef);
  gam_width_flg                = 0;
}

