#include "EndfUtils/MFxxMTyyyConverter/ResonanceData/MF02MT151ConverterRMatrixLimited.hpp"

using namespace frendy;

//constructor
MF02MT151ConverterRMatrixLimited::MF02MT151ConverterRMatrixLimited(void)
{
}

//destructor
MF02MT151ConverterRMatrixLimited::~MF02MT151ConverterRMatrixLimited(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//RMatrixLimitedDataContainer -> MF02MT151Parser
void MF02MT151ConverterRMatrixLimited::convert_frendy_to_endf_format
  ( int& i, int& i_max, int& j, vector<int>& j_max,
  RMatrixLimitedDataContainer& frendy_obj, MF02MT151Parser& endf_obj )
{
  //Declare ENDF data
  vector<vector<Integer> >                         IFG_LRU01_LRF07       = endf_obj.get_IFG_LRU01_LRF07();
  vector<vector<Integer> >                         KRM_LRU01_LRF07       = endf_obj.get_KRM_LRU01_LRF07();
  vector<vector<Integer> >                         KRL_LRU01_LRF07       = endf_obj.get_KRL_LRU01_LRF07();
  vector<vector<vector<Real> > >                   MA_LRU01_LRF07        = endf_obj.get_MA_LRU01_LRF07();
  vector<vector<vector<Real> > >                   MB_LRU01_LRF07        = endf_obj.get_MB_LRU01_LRF07();
  vector<vector<vector<Real> > >                   ZA_LRU01_LRF07        = endf_obj.get_ZA_LRU01_LRF07();
  vector<vector<vector<Real> > >                   ZB_LRU01_LRF07        = endf_obj.get_ZB_LRU01_LRF07();
  vector<vector<vector<Real> > >                   IA_LRU01_LRF07        = endf_obj.get_IA_LRU01_LRF07();
  vector<vector<vector<Real> > >                   IB_LRU01_LRF07        = endf_obj.get_IB_LRU01_LRF07();
  vector<vector<vector<Real> > >                   Q_LRU01_LRF07         = endf_obj.get_Q_LRU01_LRF07();
  vector<vector<vector<Real> > >                   PNT_LRU01_LRF07       = endf_obj.get_PNT_LRU01_LRF07();
  vector<vector<vector<Real> > >                   SHF_LRU01_LRF07       = endf_obj.get_SHF_LRU01_LRF07();
  vector<vector<vector<Real> > >                   MT_LRU01_LRF07        = endf_obj.get_MT_LRU01_LRF07();
  vector<vector<vector<Real> > >                   PA_LRU01_LRF07        = endf_obj.get_PA_LRU01_LRF07();
  vector<vector<vector<Real> > >                   PB_LRU01_LRF07        = endf_obj.get_PB_LRU01_LRF07();
  vector<vector<vector<Real> > >                   AJ_LRU01_LRF07        = endf_obj.get_AJ_LRU01_LRF07();
  vector<vector<vector<Real> > >                   PJ_LRU01_LRF07        = endf_obj.get_PJ_LRU01_LRF07();
  vector<vector<vector<Integer> > >                KBK_LRU01_LRF07       = endf_obj.get_KBK_LRU01_LRF07();
  vector<vector<vector<Integer> > >                KPS_LRU01_LRF07       = endf_obj.get_KPS_LRU01_LRF07();
  vector<vector<vector<vector<Real> > > >          PPI_LRU01_LRF07       = endf_obj.get_PPI_LRU01_LRF07();
  vector<vector<vector<vector<Real> > > >          L_LRU01_LRF07         = endf_obj.get_L_LRU01_LRF07();
  vector<vector<vector<vector<Real> > > >          SCH_LRU01_LRF07       = endf_obj.get_SCH_LRU01_LRF07();
  vector<vector<vector<vector<Real> > > >          BND_LRU01_LRF07       = endf_obj.get_BND_LRU01_LRF07();
  vector<vector<vector<vector<Real> > > >          APE_LRU01_LRF07       = endf_obj.get_APE_LRU01_LRF07();
  vector<vector<vector<vector<Real> > > >          APT_LRU01_LRF07       = endf_obj.get_APT_LRU01_LRF07();
  vector<vector<vector<vector<Real> > > >          ER_LRU01_LRF07        = endf_obj.get_ER_LRU01_LRF07();
  vector<vector<vector<vector<vector<Real> > > > > GAM_LRU01_LRF07       = endf_obj.get_GAM_LRU01_LRF07();
  vector<vector<vector<Integer> > >                LCH_LRU01_LRF07       = endf_obj.get_LCH_LRU01_LRF07();
  vector<vector<vector<Integer> > >                LBK_LRU01_LRF07       = endf_obj.get_LBK_LRU01_LRF07();
  vector<vector<vector<vector<Integer> > > >       INT_RBR_LRU01_LRF07   = endf_obj.get_INT_RBR_LRU01_LRF07();
  vector<vector<vector<vector<Integer> > > >       NBT_RBR_LRU01_LRF07   = endf_obj.get_NBT_RBR_LRU01_LRF07();
  vector<vector<vector<vector<Real> > > >          E_INT_RBR_LRU01_LRF07 = endf_obj.get_E_INT_RBR_LRU01_LRF07();
  vector<vector<vector<vector<Real> > > >          RBR_TAB_LRU01_LRF07   = endf_obj.get_RBR_TAB_LRU01_LRF07();
  vector<vector<vector<vector<Integer> > > >       INT_RBI_LRU01_LRF07   = endf_obj.get_INT_RBI_LRU01_LRF07();
  vector<vector<vector<vector<Integer> > > >       NBT_RBI_LRU01_LRF07   = endf_obj.get_NBT_RBI_LRU01_LRF07();
  vector<vector<vector<vector<Real> > > >          E_INT_RBI_LRU01_LRF07 = endf_obj.get_E_INT_RBI_LRU01_LRF07();
  vector<vector<vector<vector<Real> > > >          RBI_TAB_LRU01_LRF07   = endf_obj.get_RBI_TAB_LRU01_LRF07();
  vector<vector<vector<Real> > >                   R0_LRU01_LRF07        = endf_obj.get_R0_LRU01_LRF07();
  vector<vector<vector<Real> > >                   S0_LRU01_LRF07        = endf_obj.get_S0_LRU01_LRF07();
  vector<vector<vector<Real> > >                   R1_LRU01_LRF07        = endf_obj.get_R1_LRU01_LRF07();
  vector<vector<vector<Real> > >                   S1_LRU01_LRF07        = endf_obj.get_S1_LRU01_LRF07();
  vector<vector<vector<Real> > >                   R2_LRU01_LRF07        = endf_obj.get_R2_LRU01_LRF07();
  vector<vector<vector<Real> > >                   EU_LRU01_LRF07        = endf_obj.get_EU_LRU01_LRF07();
  vector<vector<vector<Real> > >                   ED_LRU01_LRF07        = endf_obj.get_ED_LRU01_LRF07();
  vector<vector<vector<Real> > >                   GA_LRU01_LRF07        = endf_obj.get_GA_LRU01_LRF07();
  vector<vector<vector<Integer> > >                LPS_LRU01_LRF07       = endf_obj.get_LPS_LRU01_LRF07();
  vector<vector<vector<vector<Integer> > > >       INT_PSR_LRU01_LRF07   = endf_obj.get_INT_PSR_LRU01_LRF07();
  vector<vector<vector<vector<Integer> > > >       NBT_PSR_LRU01_LRF07   = endf_obj.get_NBT_PSR_LRU01_LRF07();
  vector<vector<vector<vector<Real> > > >          E_INT_PSR_LRU01_LRF07 = endf_obj.get_E_INT_PSR_LRU01_LRF07();
  vector<vector<vector<vector<Real> > > >          PSR_TAB_LRU01_LRF07   = endf_obj.get_PSR_TAB_LRU01_LRF07();
  vector<vector<vector<vector<Integer> > > >       INT_PSI_LRU01_LRF07   = endf_obj.get_INT_PSI_LRU01_LRF07();
  vector<vector<vector<vector<Integer> > > >       NBT_PSI_LRU01_LRF07   = endf_obj.get_NBT_PSI_LRU01_LRF07();
  vector<vector<vector<vector<Real> > > >          E_INT_PSI_LRU01_LRF07 = endf_obj.get_E_INT_PSI_LRU01_LRF07();
  vector<vector<vector<vector<Real> > > >          PSI_TAB_LRU01_LRF07   = endf_obj.get_PSI_TAB_LRU01_LRF07();
   
  vector<vector<Integer> >                         NJS_LRU01_LRF07       = endf_obj.get_NJS_LRU01_LRF07();
  vector<vector<Integer> >                         NPP_LRU01_LRF07       = endf_obj.get_NPP_LRU01_LRF07();
  vector<vector<vector<Integer> > >                NCH_LRU01_LRF07       = endf_obj.get_NCH_LRU01_LRF07();
  vector<vector<vector<Integer> > >                NRS_LRU01_LRF07       = endf_obj.get_NRS_LRU01_LRF07();
  vector<vector<vector<Integer> > >                NX_LRU01_LRF07        = endf_obj.get_NX_LRU01_LRF07();
  
  //Resize ENDF data
  int ele_no = static_cast<int>(IFG_LRU01_LRF07.size());
  if( ele_no == 0 )
  {
    IFG_LRU01_LRF07.resize(i_max);
    KRM_LRU01_LRF07.resize(i_max);
    KRL_LRU01_LRF07.resize(i_max);
    MA_LRU01_LRF07.resize(i_max);
    MB_LRU01_LRF07.resize(i_max);
    ZA_LRU01_LRF07.resize(i_max);
    ZB_LRU01_LRF07.resize(i_max);
    IA_LRU01_LRF07.resize(i_max);
    IB_LRU01_LRF07.resize(i_max);
    Q_LRU01_LRF07.resize(i_max);
    PNT_LRU01_LRF07.resize(i_max);
    SHF_LRU01_LRF07.resize(i_max);
    MT_LRU01_LRF07.resize(i_max);
    PA_LRU01_LRF07.resize(i_max);
    PB_LRU01_LRF07.resize(i_max);
    AJ_LRU01_LRF07.resize(i_max);
    PJ_LRU01_LRF07.resize(i_max);
    KBK_LRU01_LRF07.resize(i_max);
    KPS_LRU01_LRF07.resize(i_max);
    PPI_LRU01_LRF07.resize(i_max);
    L_LRU01_LRF07.resize(i_max);
    SCH_LRU01_LRF07.resize(i_max);
    BND_LRU01_LRF07.resize(i_max);
    APE_LRU01_LRF07.resize(i_max);
    APT_LRU01_LRF07.resize(i_max);
    ER_LRU01_LRF07.resize(i_max);
    GAM_LRU01_LRF07.resize(i_max);
    LCH_LRU01_LRF07.resize(i_max);
    LBK_LRU01_LRF07.resize(i_max);
    INT_RBR_LRU01_LRF07.resize(i_max);
    NBT_RBR_LRU01_LRF07.resize(i_max);
    E_INT_RBR_LRU01_LRF07.resize(i_max);
    RBR_TAB_LRU01_LRF07.resize(i_max);
    INT_RBI_LRU01_LRF07.resize(i_max);
    NBT_RBI_LRU01_LRF07.resize(i_max);
    E_INT_RBI_LRU01_LRF07.resize(i_max);
    RBI_TAB_LRU01_LRF07.resize(i_max);
    R0_LRU01_LRF07.resize(i_max);
    S0_LRU01_LRF07.resize(i_max);
    R1_LRU01_LRF07.resize(i_max);
    S1_LRU01_LRF07.resize(i_max);
    R2_LRU01_LRF07.resize(i_max);
    EU_LRU01_LRF07.resize(i_max);
    ED_LRU01_LRF07.resize(i_max);
    GA_LRU01_LRF07.resize(i_max);
    LPS_LRU01_LRF07.resize(i_max);
    INT_PSR_LRU01_LRF07.resize(i_max);
    NBT_PSR_LRU01_LRF07.resize(i_max);
    E_INT_PSR_LRU01_LRF07.resize(i_max);
    PSR_TAB_LRU01_LRF07.resize(i_max);
    INT_PSI_LRU01_LRF07.resize(i_max);
    NBT_PSI_LRU01_LRF07.resize(i_max);
    E_INT_PSI_LRU01_LRF07.resize(i_max);
    PSI_TAB_LRU01_LRF07.resize(i_max);
    NJS_LRU01_LRF07.resize(i_max);
    NPP_LRU01_LRF07.resize(i_max);
    NCH_LRU01_LRF07.resize(i_max);
    NRS_LRU01_LRF07.resize(i_max);
    NX_LRU01_LRF07.resize(i_max);
    for(int i_tmp=0; i_tmp<i_max; i_tmp++)
    {
      IFG_LRU01_LRF07[i_tmp].resize(j_max[i_tmp]);
      KRM_LRU01_LRF07[i_tmp].resize(j_max[i_tmp]);
      KRL_LRU01_LRF07[i_tmp].resize(j_max[i_tmp]);
      MA_LRU01_LRF07[i_tmp].resize(j_max[i_tmp]);
      MB_LRU01_LRF07[i_tmp].resize(j_max[i_tmp]);
      ZA_LRU01_LRF07[i_tmp].resize(j_max[i_tmp]);
      ZB_LRU01_LRF07[i_tmp].resize(j_max[i_tmp]);
      IA_LRU01_LRF07[i_tmp].resize(j_max[i_tmp]);
      IB_LRU01_LRF07[i_tmp].resize(j_max[i_tmp]);
      Q_LRU01_LRF07[i_tmp].resize(j_max[i_tmp]);
      PNT_LRU01_LRF07[i_tmp].resize(j_max[i_tmp]);
      SHF_LRU01_LRF07[i_tmp].resize(j_max[i_tmp]);
      MT_LRU01_LRF07[i_tmp].resize(j_max[i_tmp]);
      PA_LRU01_LRF07[i_tmp].resize(j_max[i_tmp]);
      PB_LRU01_LRF07[i_tmp].resize(j_max[i_tmp]);
      AJ_LRU01_LRF07[i_tmp].resize(j_max[i_tmp]);
      PJ_LRU01_LRF07[i_tmp].resize(j_max[i_tmp]);
      KBK_LRU01_LRF07[i_tmp].resize(j_max[i_tmp]);
      KPS_LRU01_LRF07[i_tmp].resize(j_max[i_tmp]);
      PPI_LRU01_LRF07[i_tmp].resize(j_max[i_tmp]);
      L_LRU01_LRF07[i_tmp].resize(j_max[i_tmp]);
      SCH_LRU01_LRF07[i_tmp].resize(j_max[i_tmp]);
      BND_LRU01_LRF07[i_tmp].resize(j_max[i_tmp]);
      APE_LRU01_LRF07[i_tmp].resize(j_max[i_tmp]);
      APT_LRU01_LRF07[i_tmp].resize(j_max[i_tmp]);
      ER_LRU01_LRF07[i_tmp].resize(j_max[i_tmp]);
      GAM_LRU01_LRF07[i_tmp].resize(j_max[i_tmp]);
      LCH_LRU01_LRF07[i_tmp].resize(j_max[i_tmp]);
      LBK_LRU01_LRF07[i_tmp].resize(j_max[i_tmp]);
      INT_RBR_LRU01_LRF07[i_tmp].resize(j_max[i_tmp]);
      NBT_RBR_LRU01_LRF07[i_tmp].resize(j_max[i_tmp]);
      E_INT_RBR_LRU01_LRF07[i_tmp].resize(j_max[i_tmp]);
      RBR_TAB_LRU01_LRF07[i_tmp].resize(j_max[i_tmp]);
      INT_RBI_LRU01_LRF07[i_tmp].resize(j_max[i_tmp]);
      NBT_RBI_LRU01_LRF07[i_tmp].resize(j_max[i_tmp]);
      E_INT_RBI_LRU01_LRF07[i_tmp].resize(j_max[i_tmp]);
      RBI_TAB_LRU01_LRF07[i_tmp].resize(j_max[i_tmp]);
      R0_LRU01_LRF07[i_tmp].resize(j_max[i_tmp]);
      S0_LRU01_LRF07[i_tmp].resize(j_max[i_tmp]);
      R1_LRU01_LRF07[i_tmp].resize(j_max[i_tmp]);
      S1_LRU01_LRF07[i_tmp].resize(j_max[i_tmp]);
      R2_LRU01_LRF07[i_tmp].resize(j_max[i_tmp]);
      EU_LRU01_LRF07[i_tmp].resize(j_max[i_tmp]);
      ED_LRU01_LRF07[i_tmp].resize(j_max[i_tmp]);
      GA_LRU01_LRF07[i_tmp].resize(j_max[i_tmp]);
      LPS_LRU01_LRF07[i_tmp].resize(j_max[i_tmp]);
      INT_PSR_LRU01_LRF07[i_tmp].resize(j_max[i_tmp]);
      NBT_PSR_LRU01_LRF07[i_tmp].resize(j_max[i_tmp]);
      E_INT_PSR_LRU01_LRF07[i_tmp].resize(j_max[i_tmp]);
      PSR_TAB_LRU01_LRF07[i_tmp].resize(j_max[i_tmp]);
      INT_PSI_LRU01_LRF07[i_tmp].resize(j_max[i_tmp]);
      NBT_PSI_LRU01_LRF07[i_tmp].resize(j_max[i_tmp]);
      E_INT_PSI_LRU01_LRF07[i_tmp].resize(j_max[i_tmp]);
      PSI_TAB_LRU01_LRF07[i_tmp].resize(j_max[i_tmp]);
      NJS_LRU01_LRF07[i_tmp].resize(j_max[i_tmp]);
      NPP_LRU01_LRF07[i_tmp].resize(j_max[i_tmp]);
      NCH_LRU01_LRF07[i_tmp].resize(j_max[i_tmp]);
      NRS_LRU01_LRF07[i_tmp].resize(j_max[i_tmp]);
      NX_LRU01_LRF07[i_tmp].resize(j_max[i_tmp]);
    }
  }
  else
  {
    if( ele_no != i_max )
    {
      string class_name = "MF02MT151ConverterRMatrixLimited";
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
     
    if( static_cast<int>(IFG_LRU01_LRF07[i].size()) != j_max[i] )
    {
      string class_name = "MF02MT151ConverterRMatrixLimited";
      string func_name  = "convert_frendy_to_endf_format";
      ostringstream oss01, oss02, oss03, oss04;
      oss01 << i;
      oss02 << j;
      oss03 <<  static_cast<int>(IFG_LRU01_LRF07[i].size());
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
  IFG_LRU01_LRF07[i][j]       = frendy_obj.get_gam_width_flg();
  KRM_LRU01_LRF07[i][j]       = frendy_obj.get_r_matrix_calc_flg();
  KRL_LRU01_LRF07[i][j]       = frendy_obj.get_relativistic_flg();
  MA_LRU01_LRF07[i][j]        = frendy_obj.get_mass_a();
  MB_LRU01_LRF07[i][j]        = frendy_obj.get_mass_b();
  ZA_LRU01_LRF07[i][j]        = frendy_obj.get_charge_a();
  ZB_LRU01_LRF07[i][j]        = frendy_obj.get_charge_b();
  IA_LRU01_LRF07[i][j]        = frendy_obj.get_spin_a();
  IB_LRU01_LRF07[i][j]        = frendy_obj.get_spin_b();
  Q_LRU01_LRF07[i][j]         = frendy_obj.get_q_value();
  PNT_LRU01_LRF07[i][j]       = frendy_obj.get_penetrability_calc_flg();
  SHF_LRU01_LRF07[i][j]       = frendy_obj.get_shift_factor_calc_flg();
  MT_LRU01_LRF07[i][j]        = frendy_obj.get_reaction_type_flg();
  PA_LRU01_LRF07[i][j]        = frendy_obj.get_parity_a();
  PB_LRU01_LRF07[i][j]        = frendy_obj.get_parity_b();
  AJ_LRU01_LRF07[i][j]        = frendy_obj.get_j_value_abs();
  PJ_LRU01_LRF07[i][j]        = frendy_obj.get_parity();
  KBK_LRU01_LRF07[i][j]       = frendy_obj.get_back_ground_r_matrix_flg();
  KPS_LRU01_LRF07[i][j]       = frendy_obj.get_non_hard_sphere_flg();
  PPI_LRU01_LRF07[i][j]       = frendy_obj.get_particle_pair_no();
  L_LRU01_LRF07[i][j]         = frendy_obj.get_l_value();
  SCH_LRU01_LRF07[i][j]       = frendy_obj.get_spin_channel();
  BND_LRU01_LRF07[i][j]       = frendy_obj.get_boundary_condition();
  APE_LRU01_LRF07[i][j]       = frendy_obj.get_scat_radius_eff();
  APT_LRU01_LRF07[i][j]       = frendy_obj.get_scat_radius_true();
  ER_LRU01_LRF07[i][j]        = frendy_obj.get_ene_reso();
  GAM_LRU01_LRF07[i][j]       = frendy_obj.get_gam_width();
  LCH_LRU01_LRF07[i][j]       = frendy_obj.get_back_ground_r_matrix_index();
  LBK_LRU01_LRF07[i][j]       = frendy_obj.get_back_ground_r_matrix_add_flg();

  int k_max = static_cast<int>(LBK_LRU01_LRF07[i][j].size());
  for(int k=0; k<k_max; k++)
  {
    INT_RBR_LRU01_LRF07[i][j].resize(k_max);
    NBT_RBR_LRU01_LRF07[i][j].resize(k_max);
    E_INT_RBR_LRU01_LRF07[i][j].resize(k_max);
    RBR_TAB_LRU01_LRF07[i][j].resize(k_max);
    INT_RBI_LRU01_LRF07[i][j].resize(k_max);
    NBT_RBI_LRU01_LRF07[i][j].resize(k_max);
    E_INT_RBI_LRU01_LRF07[i][j].resize(k_max);
    RBI_TAB_LRU01_LRF07[i][j].resize(k_max);
    R0_LRU01_LRF07[i][j].resize(k_max);
    S0_LRU01_LRF07[i][j].resize(k_max);
    R1_LRU01_LRF07[i][j].resize(k_max);
    S1_LRU01_LRF07[i][j].resize(k_max);
    R2_LRU01_LRF07[i][j].resize(k_max);
    EU_LRU01_LRF07[i][j].resize(k_max);
    ED_LRU01_LRF07[i][j].resize(k_max);
    GA_LRU01_LRF07[i][j].resize(k_max);

    if( LBK_LRU01_LRF07[i][j][k] == 1 )
    {
      INT_RBR_LRU01_LRF07[i][j][k]   = frendy_obj.get_complex_real_int_data()[k];
      NBT_RBR_LRU01_LRF07[i][j][k]   = frendy_obj.get_complex_real_range_data()[k];
      E_INT_RBR_LRU01_LRF07[i][j][k] = frendy_obj.get_complex_real_ene_data()[k];
      RBR_TAB_LRU01_LRF07[i][j][k]   = frendy_obj.get_complex_real_data()[k];
      INT_RBI_LRU01_LRF07[i][j][k]   = frendy_obj.get_complex_imagin_int_data()[k];
      NBT_RBI_LRU01_LRF07[i][j][k]   = frendy_obj.get_complex_imagin_range_data()[k];
      E_INT_RBI_LRU01_LRF07[i][j][k] = frendy_obj.get_complex_imagin_ene_data()[k];
      RBI_TAB_LRU01_LRF07[i][j][k]   = frendy_obj.get_complex_imagin_data()[k];
    }
    else if( LBK_LRU01_LRF07[i][j][k] == 2 )
    {
      R0_LRU01_LRF07[i][j][k]        = frendy_obj.get_sammy_logarithmic_data_r_com()[k];
      S0_LRU01_LRF07[i][j][k]        = frendy_obj.get_sammy_logarithmic_data_s_com()[k];
      R1_LRU01_LRF07[i][j][k]        = frendy_obj.get_sammy_logarithmic_data_r_lin()[k];
      S1_LRU01_LRF07[i][j][k]        = frendy_obj.get_sammy_logarithmic_data_s_lin()[k];
      R2_LRU01_LRF07[i][j][k]        = frendy_obj.get_sammy_logarithmic_data_r_q()[k];
      EU_LRU01_LRF07[i][j][k]        = frendy_obj.get_sammy_logarithmic_data_e_up()[k];
      ED_LRU01_LRF07[i][j][k]        = frendy_obj.get_sammy_logarithmic_data_e_down()[k];
    }
    else if( LBK_LRU01_LRF07[i][j][k] == 3 )
    {
      R0_LRU01_LRF07[i][j][k]        = frendy_obj.get_frohner_data_rc()[k];
      S0_LRU01_LRF07[i][j][k]        = frendy_obj.get_frohner_data_s()[k];
      GA_LRU01_LRF07[i][j][k]        = frendy_obj.get_frohner_data_gam_r()[k];
      EU_LRU01_LRF07[i][j][k]        = frendy_obj.get_frohner_data_e_up()[k];
      ED_LRU01_LRF07[i][j][k]        = frendy_obj.get_frohner_data_e_down()[k];
    }
  }

  LPS_LRU01_LRF07[i][j]       = frendy_obj.get_non_hard_sphere_add_flg();
  INT_PSR_LRU01_LRF07[i][j]   = frendy_obj.get_phase_shift_real_int_data();
  NBT_PSR_LRU01_LRF07[i][j]   = frendy_obj.get_phase_shift_real_range_data();
  E_INT_PSR_LRU01_LRF07[i][j] = frendy_obj.get_phase_shift_real_ene_data();
  PSR_TAB_LRU01_LRF07[i][j]   = frendy_obj.get_phase_shift_real_data();
  INT_PSI_LRU01_LRF07[i][j]   = frendy_obj.get_phase_shift_imagin_int_data();
  NBT_PSI_LRU01_LRF07[i][j]   = frendy_obj.get_phase_shift_imagin_range_data();
  E_INT_PSI_LRU01_LRF07[i][j] = frendy_obj.get_phase_shift_imagin_ene_data();
  PSI_TAB_LRU01_LRF07[i][j]   = frendy_obj.get_phase_shift_imagin_data();

  NJS_LRU01_LRF07[i][j] = static_cast<Integer>(AJ_LRU01_LRF07[i][j].size());
  NPP_LRU01_LRF07[i][j] = static_cast<Integer>(MA_LRU01_LRF07[i][j].size());
  
  k_max = static_cast<int>(NJS_LRU01_LRF07[i][j]);
  NCH_LRU01_LRF07[i][j].resize(k_max);
  NRS_LRU01_LRF07[i][j].resize(k_max);
  NX_LRU01_LRF07[i][j].resize(k_max);
  for(int k=0; k<k_max; k++)
  {
    Integer nch_val = static_cast<Integer>(PPI_LRU01_LRF07[i][j][k].size());
    Integer nrs_val = static_cast<Integer>(ER_LRU01_LRF07[i][j][k].size());
    NCH_LRU01_LRF07[i][j][k] = nch_val;
    NRS_LRU01_LRF07[i][j][k] = nrs_val;
    
    NX_LRU01_LRF07[i][j][k] = (1 + nch_val);
    if( (1 + nch_val) % 6 > 0 )
    {
      NX_LRU01_LRF07[i][j][k]++;
    }
    NX_LRU01_LRF07[i][j][k] = (NX_LRU01_LRF07[i][j][k] * nrs_val) / 6;
  }
  
  //Set ENDF format data
  //endf_obj.clear();
  endf_obj.set_IFG_LRU01_LRF07(IFG_LRU01_LRF07);
  endf_obj.set_KRM_LRU01_LRF07(KRM_LRU01_LRF07);
  endf_obj.set_NJS_LRU01_LRF07(NJS_LRU01_LRF07);
  endf_obj.set_KRL_LRU01_LRF07(KRL_LRU01_LRF07);
  endf_obj.set_NPP_LRU01_LRF07(NPP_LRU01_LRF07);
  endf_obj.set_MA_LRU01_LRF07(MA_LRU01_LRF07);
  endf_obj.set_MB_LRU01_LRF07(MB_LRU01_LRF07);
  endf_obj.set_ZA_LRU01_LRF07(ZA_LRU01_LRF07);
  endf_obj.set_ZB_LRU01_LRF07(ZB_LRU01_LRF07);
  endf_obj.set_IA_LRU01_LRF07(IA_LRU01_LRF07);
  endf_obj.set_IB_LRU01_LRF07(IB_LRU01_LRF07);
  endf_obj.set_Q_LRU01_LRF07(Q_LRU01_LRF07);
  endf_obj.set_PNT_LRU01_LRF07(PNT_LRU01_LRF07);
  endf_obj.set_SHF_LRU01_LRF07(SHF_LRU01_LRF07);
  endf_obj.set_MT_LRU01_LRF07(MT_LRU01_LRF07);
  endf_obj.set_PA_LRU01_LRF07(PA_LRU01_LRF07);
  endf_obj.set_PB_LRU01_LRF07(PB_LRU01_LRF07);
  endf_obj.set_AJ_LRU01_LRF07(AJ_LRU01_LRF07);
  endf_obj.set_PJ_LRU01_LRF07(PJ_LRU01_LRF07);
  endf_obj.set_KBK_LRU01_LRF07(KBK_LRU01_LRF07);
  endf_obj.set_KPS_LRU01_LRF07(KPS_LRU01_LRF07);
  endf_obj.set_NCH_LRU01_LRF07(NCH_LRU01_LRF07);
  endf_obj.set_PPI_LRU01_LRF07(PPI_LRU01_LRF07);
  endf_obj.set_L_LRU01_LRF07(L_LRU01_LRF07);
  endf_obj.set_SCH_LRU01_LRF07(SCH_LRU01_LRF07);
  endf_obj.set_BND_LRU01_LRF07(BND_LRU01_LRF07);
  endf_obj.set_APE_LRU01_LRF07(APE_LRU01_LRF07);
  endf_obj.set_APT_LRU01_LRF07(APT_LRU01_LRF07);
  endf_obj.set_NRS_LRU01_LRF07(NRS_LRU01_LRF07);
  endf_obj.set_NX_LRU01_LRF07(NX_LRU01_LRF07);
  endf_obj.set_ER_LRU01_LRF07(ER_LRU01_LRF07);
  endf_obj.set_GAM_LRU01_LRF07(GAM_LRU01_LRF07);
  endf_obj.set_LCH_LRU01_LRF07(LCH_LRU01_LRF07);
  endf_obj.set_LBK_LRU01_LRF07(LBK_LRU01_LRF07);
  endf_obj.set_NBT_RBR_LRU01_LRF07(NBT_RBR_LRU01_LRF07);
  endf_obj.set_INT_RBR_LRU01_LRF07(INT_RBR_LRU01_LRF07);
  endf_obj.set_E_INT_RBR_LRU01_LRF07(E_INT_RBR_LRU01_LRF07);
  endf_obj.set_RBR_TAB_LRU01_LRF07(RBR_TAB_LRU01_LRF07);
  endf_obj.set_NBT_RBI_LRU01_LRF07(NBT_RBI_LRU01_LRF07);
  endf_obj.set_INT_RBI_LRU01_LRF07(INT_RBI_LRU01_LRF07);
  endf_obj.set_E_INT_RBI_LRU01_LRF07(E_INT_RBI_LRU01_LRF07);
  endf_obj.set_RBI_TAB_LRU01_LRF07(RBI_TAB_LRU01_LRF07);
  endf_obj.set_ED_LRU01_LRF07(ED_LRU01_LRF07);
  endf_obj.set_EU_LRU01_LRF07(EU_LRU01_LRF07);
  endf_obj.set_R0_LRU01_LRF07(R0_LRU01_LRF07);
  endf_obj.set_R1_LRU01_LRF07(R1_LRU01_LRF07);
  endf_obj.set_R2_LRU01_LRF07(R2_LRU01_LRF07);
  endf_obj.set_S0_LRU01_LRF07(S0_LRU01_LRF07);
  endf_obj.set_S1_LRU01_LRF07(S1_LRU01_LRF07);
  endf_obj.set_GA_LRU01_LRF07(GA_LRU01_LRF07);
  endf_obj.set_LPS_LRU01_LRF07(LPS_LRU01_LRF07);
  endf_obj.set_NBT_PSR_LRU01_LRF07(NBT_PSR_LRU01_LRF07);
  endf_obj.set_INT_PSR_LRU01_LRF07(INT_PSR_LRU01_LRF07);
  endf_obj.set_E_INT_PSR_LRU01_LRF07(E_INT_PSR_LRU01_LRF07);
  endf_obj.set_PSR_TAB_LRU01_LRF07(PSR_TAB_LRU01_LRF07);
  endf_obj.set_NBT_PSI_LRU01_LRF07(NBT_PSI_LRU01_LRF07);
  endf_obj.set_INT_PSI_LRU01_LRF07(INT_PSI_LRU01_LRF07);
  endf_obj.set_E_INT_PSI_LRU01_LRF07(E_INT_PSI_LRU01_LRF07);
  endf_obj.set_PSI_TAB_LRU01_LRF07(PSI_TAB_LRU01_LRF07);

  //Clear declared data
  clr_obj.clear_vec_array2_int(IFG_LRU01_LRF07);
  clr_obj.clear_vec_array2_int(KRM_LRU01_LRF07);
  clr_obj.clear_vec_array2_int(KRL_LRU01_LRF07);
  clr_obj.clear_vec_array3_real(MA_LRU01_LRF07);
  clr_obj.clear_vec_array3_real(MB_LRU01_LRF07);
  clr_obj.clear_vec_array3_real(ZA_LRU01_LRF07);
  clr_obj.clear_vec_array3_real(ZB_LRU01_LRF07);
  clr_obj.clear_vec_array3_real(IA_LRU01_LRF07);
  clr_obj.clear_vec_array3_real(IB_LRU01_LRF07);
  clr_obj.clear_vec_array3_real(Q_LRU01_LRF07);
  clr_obj.clear_vec_array3_real(PNT_LRU01_LRF07);
  clr_obj.clear_vec_array3_real(SHF_LRU01_LRF07);
  clr_obj.clear_vec_array3_real(MT_LRU01_LRF07);
  clr_obj.clear_vec_array3_real(PA_LRU01_LRF07);
  clr_obj.clear_vec_array3_real(PB_LRU01_LRF07);
  clr_obj.clear_vec_array3_real(AJ_LRU01_LRF07);
  clr_obj.clear_vec_array3_real(PJ_LRU01_LRF07);
  clr_obj.clear_vec_array3_int(KBK_LRU01_LRF07);
  clr_obj.clear_vec_array3_int(KPS_LRU01_LRF07);
  clr_obj.clear_vec_array4_real(PPI_LRU01_LRF07);
  clr_obj.clear_vec_array4_real(L_LRU01_LRF07);
  clr_obj.clear_vec_array4_real(SCH_LRU01_LRF07);
  clr_obj.clear_vec_array4_real(BND_LRU01_LRF07);
  clr_obj.clear_vec_array4_real(APE_LRU01_LRF07);
  clr_obj.clear_vec_array4_real(APT_LRU01_LRF07);
  clr_obj.clear_vec_array4_real(ER_LRU01_LRF07);
  clr_obj.clear_vec_array5_real(GAM_LRU01_LRF07);
  clr_obj.clear_vec_array3_int(LCH_LRU01_LRF07);
  clr_obj.clear_vec_array3_int(LBK_LRU01_LRF07);
  clr_obj.clear_vec_array4_int(INT_RBR_LRU01_LRF07);
  clr_obj.clear_vec_array4_int(NBT_RBR_LRU01_LRF07);
  clr_obj.clear_vec_array4_real(E_INT_RBR_LRU01_LRF07);
  clr_obj.clear_vec_array4_real(RBR_TAB_LRU01_LRF07);
  clr_obj.clear_vec_array4_int(INT_RBI_LRU01_LRF07);
  clr_obj.clear_vec_array4_int(NBT_RBI_LRU01_LRF07);
  clr_obj.clear_vec_array4_real(E_INT_RBI_LRU01_LRF07);
  clr_obj.clear_vec_array4_real(RBI_TAB_LRU01_LRF07);
  clr_obj.clear_vec_array3_real(R0_LRU01_LRF07);
  clr_obj.clear_vec_array3_real(S0_LRU01_LRF07);
  clr_obj.clear_vec_array3_real(R1_LRU01_LRF07);
  clr_obj.clear_vec_array3_real(S1_LRU01_LRF07);
  clr_obj.clear_vec_array3_real(R2_LRU01_LRF07);
  clr_obj.clear_vec_array3_real(EU_LRU01_LRF07);
  clr_obj.clear_vec_array3_real(ED_LRU01_LRF07);
  clr_obj.clear_vec_array3_real(R0_LRU01_LRF07);
  clr_obj.clear_vec_array3_real(GA_LRU01_LRF07);
  clr_obj.clear_vec_array3_int(LPS_LRU01_LRF07);
  clr_obj.clear_vec_array4_int(INT_PSR_LRU01_LRF07);
  clr_obj.clear_vec_array4_int(NBT_PSR_LRU01_LRF07);
  clr_obj.clear_vec_array4_real(E_INT_PSR_LRU01_LRF07);
  clr_obj.clear_vec_array4_real(PSR_TAB_LRU01_LRF07);
  clr_obj.clear_vec_array4_int(INT_PSI_LRU01_LRF07);
  clr_obj.clear_vec_array4_int(NBT_PSI_LRU01_LRF07);
  clr_obj.clear_vec_array4_real(E_INT_PSI_LRU01_LRF07);
  clr_obj.clear_vec_array4_real(PSI_TAB_LRU01_LRF07);
  
  clr_obj.clear_vec_array2_int(NJS_LRU01_LRF07);
  clr_obj.clear_vec_array2_int(NPP_LRU01_LRF07);
  clr_obj.clear_vec_array3_int(NCH_LRU01_LRF07);
  clr_obj.clear_vec_array3_int(NRS_LRU01_LRF07);
  clr_obj.clear_vec_array3_int(NX_LRU01_LRF07);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//MF02MT151Parser -> RMatrixLimitedDataContainer
void MF02MT151ConverterRMatrixLimited::convert_endf_format_to_frendy( int& i, int& j,
  MF02MT151Parser& endf_obj, RMatrixLimitedDataContainer& frendy_obj )
{
  //Get frendy data
  Integer                        gam_width_flg                 = endf_obj.get_IFG_LRU01_LRF07()[i][j];
  Integer                        r_matrix_calc_flg             = endf_obj.get_KRM_LRU01_LRF07()[i][j];
  Integer                        relativistic_flg              = endf_obj.get_KRL_LRU01_LRF07()[i][j];
  vector<Real>                   mass_a                        = endf_obj.get_MA_LRU01_LRF07()[i][j];
  vector<Real>                   mass_b                        = endf_obj.get_MB_LRU01_LRF07()[i][j];
  vector<Real>                   charge_a                      = endf_obj.get_ZA_LRU01_LRF07()[i][j];
  vector<Real>                   charge_b                      = endf_obj.get_ZB_LRU01_LRF07()[i][j];
  vector<Real>                   spin_a                        = endf_obj.get_IA_LRU01_LRF07()[i][j];
  vector<Real>                   spin_b                        = endf_obj.get_IB_LRU01_LRF07()[i][j];
  vector<Real>                   q_value                       = endf_obj.get_Q_LRU01_LRF07()[i][j];
  vector<Real>                   penetrability_calc_flg        = endf_obj.get_PNT_LRU01_LRF07()[i][j];
  vector<Real>                   shift_factor_calc_flg         = endf_obj.get_SHF_LRU01_LRF07()[i][j];
  vector<Real>                   reaction_type_flg             = endf_obj.get_MT_LRU01_LRF07()[i][j];
  vector<Real>                   parity_a                      = endf_obj.get_PA_LRU01_LRF07()[i][j];
  vector<Real>                   parity_b                      = endf_obj.get_PB_LRU01_LRF07()[i][j];
  vector<Real>                   j_value_abs                   = endf_obj.get_AJ_LRU01_LRF07()[i][j];
  vector<Real>                   parity                        = endf_obj.get_PJ_LRU01_LRF07()[i][j];
  vector<Integer>                back_ground_r_matrix_flg      = endf_obj.get_KBK_LRU01_LRF07()[i][j];
  vector<Integer>                non_hard_sphere_flg           = endf_obj.get_KPS_LRU01_LRF07()[i][j];
  vector<vector<Real> >          particle_pair_no              = endf_obj.get_PPI_LRU01_LRF07()[i][j];
  vector<vector<Real> >          l_value                       = endf_obj.get_L_LRU01_LRF07()[i][j];
  vector<vector<Real> >          spin_channel                  = endf_obj.get_SCH_LRU01_LRF07()[i][j];
  vector<vector<Real> >          boundary_condition            = endf_obj.get_BND_LRU01_LRF07()[i][j];
  vector<vector<Real> >          scat_radius_eff               = endf_obj.get_APE_LRU01_LRF07()[i][j];
  vector<vector<Real> >          scat_radius_true              = endf_obj.get_APT_LRU01_LRF07()[i][j];
  vector<vector<Real> >          ene_reso                      = endf_obj.get_ER_LRU01_LRF07()[i][j];
  vector<vector<vector<Real> > > gam_width                     = endf_obj.get_GAM_LRU01_LRF07()[i][j];
  vector<Integer>                back_ground_r_matrix_index    = endf_obj.get_LCH_LRU01_LRF07()[i][j];
  vector<Integer>                back_ground_r_matrix_add_flg  = endf_obj.get_LBK_LRU01_LRF07()[i][j];
  
  vector<vector<Integer> >       complex_real_int_data;
  vector<vector<Integer> >       complex_real_range_data;
  vector<vector<Real> >          complex_real_ene_data;
  vector<vector<Real> >          complex_real_data;
  vector<vector<Integer> >       complex_imagin_int_data;
  vector<vector<Integer> >       complex_imagin_range_data;
  vector<vector<Real> >          complex_imagin_ene_data;
  vector<vector<Real> >          complex_imagin_data;
  vector<Real>                   sammy_logarithmic_data_r_com;
  vector<Real>                   sammy_logarithmic_data_s_com;
  vector<Real>                   sammy_logarithmic_data_r_lin;
  vector<Real>                   sammy_logarithmic_data_s_lin;
  vector<Real>                   sammy_logarithmic_data_r_q;
  vector<Real>                   sammy_logarithmic_data_e_up;
  vector<Real>                   sammy_logarithmic_data_e_down;
  vector<Real>                   frohner_data_rc;
  vector<Real>                   frohner_data_s;
  vector<Real>                   frohner_data_gam_r;
  vector<Real>                   frohner_data_e_up;
  vector<Real>                   frohner_data_e_down;
  
  int k_max = static_cast<int>(back_ground_r_matrix_add_flg.size());
  complex_real_int_data.resize(k_max);
  complex_real_range_data.resize(k_max);
  complex_real_ene_data.resize(k_max);
  complex_real_data.resize(k_max);
  complex_imagin_int_data.resize(k_max);
  complex_imagin_range_data.resize(k_max);
  complex_imagin_ene_data.resize(k_max);
  complex_imagin_data.resize(k_max);
  sammy_logarithmic_data_r_com.resize(k_max);
  sammy_logarithmic_data_s_com.resize(k_max);
  sammy_logarithmic_data_r_lin.resize(k_max);
  sammy_logarithmic_data_s_lin.resize(k_max);
  sammy_logarithmic_data_r_q.resize(k_max);
  sammy_logarithmic_data_e_up.resize(k_max);
  sammy_logarithmic_data_e_down.resize(k_max);
  frohner_data_rc.resize(k_max);
  frohner_data_s.resize(k_max);
  frohner_data_gam_r.resize(k_max);
  frohner_data_e_up.resize(k_max);
  frohner_data_e_down.resize(k_max);
  for(int k=0; k<k_max; k++)
  {
    if( back_ground_r_matrix_add_flg[k] == 1 )
    {
      complex_real_int_data[k]         = endf_obj.get_INT_RBR_LRU01_LRF07()[i][j][k];
      complex_real_range_data[k]       = endf_obj.get_NBT_RBR_LRU01_LRF07()[i][j][k];
      complex_real_ene_data[k]         = endf_obj.get_E_INT_RBR_LRU01_LRF07()[i][j][k];
      complex_real_data[k]             = endf_obj.get_RBR_TAB_LRU01_LRF07()[i][j][k];
      complex_imagin_int_data[k]       = endf_obj.get_INT_RBI_LRU01_LRF07()[i][j][k];
      complex_imagin_range_data[k]     = endf_obj.get_NBT_RBI_LRU01_LRF07()[i][j][k];
      complex_imagin_ene_data[k]       = endf_obj.get_E_INT_RBI_LRU01_LRF07()[i][j][k];
      complex_imagin_data[k]           = endf_obj.get_RBI_TAB_LRU01_LRF07()[i][j][k];
    }
    else if( back_ground_r_matrix_add_flg[k] == 2 )
    {
      sammy_logarithmic_data_r_com[k]  = endf_obj.get_R0_LRU01_LRF07()[i][j][k];
      sammy_logarithmic_data_s_com[k]  = endf_obj.get_S0_LRU01_LRF07()[i][j][k];
      sammy_logarithmic_data_r_lin[k]  = endf_obj.get_R1_LRU01_LRF07()[i][j][k];
      sammy_logarithmic_data_s_lin[k]  = endf_obj.get_S1_LRU01_LRF07()[i][j][k];
      sammy_logarithmic_data_r_q[k]    = endf_obj.get_R2_LRU01_LRF07()[i][j][k];
      sammy_logarithmic_data_e_up[k]   = endf_obj.get_EU_LRU01_LRF07()[i][j][k];
      sammy_logarithmic_data_e_down[k] = endf_obj.get_ED_LRU01_LRF07()[i][j][k];
    }
    else if( back_ground_r_matrix_add_flg[k] == 3 )
    {
      frohner_data_rc[k]               = endf_obj.get_R0_LRU01_LRF07()[i][j][k];
      frohner_data_s[k]                = endf_obj.get_S0_LRU01_LRF07()[i][j][k];
      frohner_data_gam_r[k]            = endf_obj.get_GA_LRU01_LRF07()[i][j][k];
      frohner_data_e_up[k]             = endf_obj.get_EU_LRU01_LRF07()[i][j][k];
      frohner_data_e_down[k]           = endf_obj.get_ED_LRU01_LRF07()[i][j][k];
    }
  }
  
  vector<Integer>                non_hard_sphere_add_flg       = endf_obj.get_LPS_LRU01_LRF07()[i][j];
  vector<vector<Integer> >       phase_shift_real_int_data     = endf_obj.get_INT_PSR_LRU01_LRF07()[i][j];
  vector<vector<Integer> >       phase_shift_real_range_data   = endf_obj.get_NBT_PSR_LRU01_LRF07()[i][j];
  vector<vector<Real> >          phase_shift_real_ene_data     = endf_obj.get_E_INT_PSR_LRU01_LRF07()[i][j];
  vector<vector<Real> >          phase_shift_real_data         = endf_obj.get_PSR_TAB_LRU01_LRF07()[i][j];
  vector<vector<Integer> >       phase_shift_imagin_int_data   = endf_obj.get_INT_PSI_LRU01_LRF07()[i][j];
  vector<vector<Integer> >       phase_shift_imagin_range_data = endf_obj.get_NBT_PSI_LRU01_LRF07()[i][j];
  vector<vector<Real> >          phase_shift_imagin_ene_data   = endf_obj.get_E_INT_PSI_LRU01_LRF07()[i][j];
  vector<vector<Real> >          phase_shift_imagin_data       = endf_obj.get_PSI_TAB_LRU01_LRF07()[i][j];

  //Set ENDF format data
  frendy_obj.clear();
  frendy_obj.set_gam_width_flg(gam_width_flg);
  frendy_obj.set_r_matrix_calc_flg(r_matrix_calc_flg);
  frendy_obj.set_relativistic_flg(relativistic_flg);
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
  frendy_obj.set_back_ground_r_matrix_flg(back_ground_r_matrix_flg);
  frendy_obj.set_non_hard_sphere_flg(non_hard_sphere_flg);
  frendy_obj.set_particle_pair_no(particle_pair_no);
  frendy_obj.set_l_value(l_value);
  frendy_obj.set_spin_channel(spin_channel);
  frendy_obj.set_boundary_condition(boundary_condition);
  frendy_obj.set_scat_radius_eff(scat_radius_eff);
  frendy_obj.set_scat_radius_true(scat_radius_true);
  frendy_obj.set_ene_reso(ene_reso);
  frendy_obj.set_gam_width(gam_width);
  frendy_obj.set_back_ground_r_matrix_index(back_ground_r_matrix_index);
  frendy_obj.set_back_ground_r_matrix_add_flg(back_ground_r_matrix_add_flg);
  frendy_obj.set_complex_real_range_data(complex_real_range_data);
  frendy_obj.set_complex_real_int_data(complex_real_int_data);
  frendy_obj.set_complex_real_ene_data(complex_real_ene_data);
  frendy_obj.set_complex_real_data(complex_real_data);
  frendy_obj.set_complex_imagin_range_data(complex_imagin_range_data);
  frendy_obj.set_complex_imagin_int_data(complex_imagin_int_data);
  frendy_obj.set_complex_imagin_ene_data(complex_imagin_ene_data);
  frendy_obj.set_complex_imagin_data(complex_imagin_data);
  frendy_obj.set_sammy_logarithmic_data_e_down(sammy_logarithmic_data_e_down);
  frendy_obj.set_sammy_logarithmic_data_e_up(sammy_logarithmic_data_e_up);
  frendy_obj.set_sammy_logarithmic_data_r_com(sammy_logarithmic_data_r_com);
  frendy_obj.set_sammy_logarithmic_data_r_lin(sammy_logarithmic_data_r_lin);
  frendy_obj.set_sammy_logarithmic_data_r_q(sammy_logarithmic_data_r_q);
  frendy_obj.set_sammy_logarithmic_data_s_com(sammy_logarithmic_data_s_com);
  frendy_obj.set_sammy_logarithmic_data_s_lin(sammy_logarithmic_data_s_lin);
  frendy_obj.set_frohner_data_gam_r(frohner_data_gam_r);
  frendy_obj.set_frohner_data_rc(frohner_data_rc);
  frendy_obj.set_frohner_data_s(frohner_data_s);
  frendy_obj.set_frohner_data_e_up(frohner_data_e_up);
  frendy_obj.set_frohner_data_e_down(frohner_data_e_down);
  frendy_obj.set_non_hard_sphere_add_flg(non_hard_sphere_add_flg);
  frendy_obj.set_phase_shift_real_range_data(phase_shift_real_range_data);
  frendy_obj.set_phase_shift_real_int_data(phase_shift_real_int_data);
  frendy_obj.set_phase_shift_real_ene_data(phase_shift_real_ene_data);
  frendy_obj.set_phase_shift_real_data(phase_shift_real_data);
  frendy_obj.set_phase_shift_imagin_range_data(phase_shift_imagin_range_data);
  frendy_obj.set_phase_shift_imagin_int_data(phase_shift_imagin_int_data);
  frendy_obj.set_phase_shift_imagin_ene_data(phase_shift_imagin_ene_data);
  frendy_obj.set_phase_shift_imagin_data(phase_shift_imagin_data);

  //Clear declared data
  gam_width_flg                 = 0;
  r_matrix_calc_flg             = 0;
  relativistic_flg              = 0;
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
  back_ground_r_matrix_flg.clear();
  non_hard_sphere_flg.clear();
  clr_obj.clear_vec_array2_real(particle_pair_no);
  clr_obj.clear_vec_array2_real(l_value);
  clr_obj.clear_vec_array2_real(spin_channel);
  clr_obj.clear_vec_array2_real(boundary_condition);
  clr_obj.clear_vec_array2_real(scat_radius_eff);
  clr_obj.clear_vec_array2_real(scat_radius_true);
  clr_obj.clear_vec_array2_real(ene_reso);
  clr_obj.clear_vec_array3_real(gam_width);
  back_ground_r_matrix_index.clear();
  back_ground_r_matrix_add_flg.clear();
  clr_obj.clear_vec_array2_int(complex_real_int_data);
  clr_obj.clear_vec_array2_int(complex_real_range_data);
  clr_obj.clear_vec_array2_real(complex_real_ene_data);
  clr_obj.clear_vec_array2_real(complex_real_data);
  clr_obj.clear_vec_array2_int(complex_imagin_int_data);
  clr_obj.clear_vec_array2_int(complex_imagin_range_data);
  clr_obj.clear_vec_array2_real(complex_imagin_ene_data);
  clr_obj.clear_vec_array2_real(complex_imagin_data);
  sammy_logarithmic_data_r_com.clear();
  sammy_logarithmic_data_s_com.clear();
  sammy_logarithmic_data_r_lin.clear();
  sammy_logarithmic_data_s_lin.clear();
  sammy_logarithmic_data_r_q.clear();
  sammy_logarithmic_data_e_up.clear();
  sammy_logarithmic_data_e_down.clear();
  frohner_data_rc.clear();
  frohner_data_s.clear();
  frohner_data_gam_r.clear();
  frohner_data_e_up.clear();
  frohner_data_e_down.clear();
  non_hard_sphere_add_flg.clear();
  clr_obj.clear_vec_array2_int(phase_shift_real_int_data);
  clr_obj.clear_vec_array2_int(phase_shift_real_range_data);
  clr_obj.clear_vec_array2_real(phase_shift_real_ene_data);
  clr_obj.clear_vec_array2_real(phase_shift_real_data);
  clr_obj.clear_vec_array2_int(phase_shift_imagin_int_data);
  clr_obj.clear_vec_array2_int(phase_shift_imagin_range_data);
  clr_obj.clear_vec_array2_real(phase_shift_imagin_ene_data);
  clr_obj.clear_vec_array2_real(phase_shift_imagin_data);
}

