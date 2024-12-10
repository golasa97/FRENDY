#include "EndfUtils/MFxxMTyyyConverter/ResonanceData/MF32MT151ConverterReichMooreCompact.hpp"

using namespace frendy;

//constructor
MF32MT151ConverterReichMooreCompact::MF32MT151ConverterReichMooreCompact(void)
{
}

//destructor
MF32MT151ConverterReichMooreCompact::~MF32MT151ConverterReichMooreCompact(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//ReichMooreCompactCovarianceDataContainer -> MF32MT151Parser
void MF32MT151ConverterReichMooreCompact::convert_frendy_to_endf_format
  ( int& i, int& i_max, int& j, vector<int>& j_max,
  ReichMooreCompactCovarianceDataContainer& frendy_obj, MF32MT151Parser& endf_obj )
{
  //Declare ENDF data
  vector<vector<Integer> >                   LAD                  = endf_obj.get_LAD();
  vector<vector<vector<Real> > >             DAP_LCOMP02_LRF03    = endf_obj.get_DAP_LCOMP02_LRF03();
  vector<vector<Real> >                      APL_LCOMP02_LRF03    = endf_obj.get_APL_LCOMP02_LRF03();
  vector<vector<vector<Real> > >             ER_LCOMP02_LRF03     = endf_obj.get_ER_LCOMP02_LRF03();
  vector<vector<vector<Real> > >             AJ_LCOMP02_LRF03     = endf_obj.get_AJ_LCOMP02_LRF03();
  vector<vector<vector<Real> > >             GN_LCOMP02_LRF03     = endf_obj.get_GN_LCOMP02_LRF03();
  vector<vector<vector<Real> > >             GG_LCOMP02_LRF03     = endf_obj.get_GG_LCOMP02_LRF03();
  vector<vector<vector<Real> > >             GFA_LCOMP02_LRF03    = endf_obj.get_GFA_LCOMP02_LRF03();
  vector<vector<vector<Real> > >             GFB_LCOMP02_LRF03    = endf_obj.get_GFB_LCOMP02_LRF03();
  vector<vector<vector<Real> > >             DER_LCOMP02_LRF03    = endf_obj.get_DER_LCOMP02_LRF03();
  vector<vector<vector<Real> > >             DGN_LCOMP02_LRF03    = endf_obj.get_DGN_LCOMP02_LRF03();
  vector<vector<vector<Real> > >             DGG_LCOMP02_LRF03    = endf_obj.get_DGG_LCOMP02_LRF03();
  vector<vector<vector<Real> > >             DGFA_LCOMP02_LRF03   = endf_obj.get_DGFA_LCOMP02_LRF03();
  vector<vector<vector<Real> > >             DGFB_LCOMP02_LRF03   = endf_obj.get_DGFB_LCOMP02_LRF03();
  vector<vector<Integer> >                   NDIGIT_LCOMP02_LRF03 = endf_obj.get_NDIGIT_LCOMP02_LRF03();
  vector<vector<Integer> >                   NNN_LCOMP02_LRF03    = endf_obj.get_NNN_LCOMP02_LRF03();
  vector<vector<vector<Integer> > >          II_LCOMP02_LRF03     = endf_obj.get_II_LCOMP02_LRF03();
  vector<vector<vector<Integer> > >          JJ_LCOMP02_LRF03     = endf_obj.get_JJ_LCOMP02_LRF03();
  vector<vector<vector<vector<Integer> > > > KIJ_LCOMP02_LRF03    = endf_obj.get_KIJ_LCOMP02_LRF03();
   
  vector<vector<Integer> >                   NM_LCOMP02_LRF03     = endf_obj.get_NM_LCOMP02_LRF03();
   
  //Resize ENDF data
  int ele_no = static_cast<int>(ER_LCOMP02_LRF03.size());
  if( ele_no == 0 )
  {
    LAD.resize(i_max);
    DAP_LCOMP02_LRF03.resize(i_max);
    APL_LCOMP02_LRF03.resize(i_max);
    ER_LCOMP02_LRF03.resize(i_max);
    AJ_LCOMP02_LRF03.resize(i_max);
    GN_LCOMP02_LRF03.resize(i_max);
    GG_LCOMP02_LRF03.resize(i_max);
    GFA_LCOMP02_LRF03.resize(i_max);
    GFB_LCOMP02_LRF03.resize(i_max);
    DER_LCOMP02_LRF03.resize(i_max);
    DGN_LCOMP02_LRF03.resize(i_max);
    DGG_LCOMP02_LRF03.resize(i_max);
    DGFA_LCOMP02_LRF03.resize(i_max);
    DGFB_LCOMP02_LRF03.resize(i_max);
    NDIGIT_LCOMP02_LRF03.resize(i_max);
    NNN_LCOMP02_LRF03.resize(i_max);
    II_LCOMP02_LRF03.resize(i_max);
    JJ_LCOMP02_LRF03.resize(i_max);
    KIJ_LCOMP02_LRF03.resize(i_max);
    NM_LCOMP02_LRF03.resize(i_max);
    for(int i_tmp=0; i_tmp<i_max; i_tmp++)
    {
      LAD[i_tmp].resize(j_max[i_tmp]);
      DAP_LCOMP02_LRF03[i_tmp].resize(j_max[i_tmp]);
      APL_LCOMP02_LRF03[i_tmp].resize(j_max[i_tmp]);
      ER_LCOMP02_LRF03[i_tmp].resize(j_max[i_tmp]);
      AJ_LCOMP02_LRF03[i_tmp].resize(j_max[i_tmp]);
      GN_LCOMP02_LRF03[i_tmp].resize(j_max[i_tmp]);
      GG_LCOMP02_LRF03[i_tmp].resize(j_max[i_tmp]);
      GFA_LCOMP02_LRF03[i_tmp].resize(j_max[i_tmp]);
      GFB_LCOMP02_LRF03[i_tmp].resize(j_max[i_tmp]);
      DER_LCOMP02_LRF03[i_tmp].resize(j_max[i_tmp]);
      DGN_LCOMP02_LRF03[i_tmp].resize(j_max[i_tmp]);
      DGG_LCOMP02_LRF03[i_tmp].resize(j_max[i_tmp]);
      DGFA_LCOMP02_LRF03[i_tmp].resize(j_max[i_tmp]);
      DGFB_LCOMP02_LRF03[i_tmp].resize(j_max[i_tmp]);
      NDIGIT_LCOMP02_LRF03[i_tmp].resize(j_max[i_tmp]);
      NNN_LCOMP02_LRF03[i_tmp].resize(j_max[i_tmp]);
      II_LCOMP02_LRF03[i_tmp].resize(j_max[i_tmp]);
      JJ_LCOMP02_LRF03[i_tmp].resize(j_max[i_tmp]);
      KIJ_LCOMP02_LRF03[i_tmp].resize(j_max[i_tmp]);
      NM_LCOMP02_LRF03[i_tmp].resize(j_max[i_tmp]);
    }
  }
  else
  {
    if( ele_no != i_max )
    {
      string class_name = "MF32MT151ConverterReichMooreCompact";
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
     
    if( static_cast<int>(DAP_LCOMP02_LRF03[i].size()) != j_max[i] )
    {
      string class_name = "MF32MT151ConverterReichMooreCompact";
      string func_name  = "convert_frendy_to_endf_format";
      ostringstream oss01, oss02, oss03, oss04;
      oss01 << i;
      oss02 << j;
      oss03 <<  static_cast<int>(DAP_LCOMP02_LRF03[i].size());
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
  LAD[i][j]                  = frendy_obj.get_angular_distr_calc_flg();
  DAP_LCOMP02_LRF03[i][j]    = frendy_obj.get_scat_radius_uncertainty(); //Actual data name in Parser class is different (DAP_TAB) 
  APL_LCOMP02_LRF03[i][j]    = frendy_obj.get_scat_radius_l(); //Actual data name in Parser class is different (APL) 
  ER_LCOMP02_LRF03[i][j]     = frendy_obj.get_ene_reso();
  AJ_LCOMP02_LRF03[i][j]     = frendy_obj.get_j_value_abs();
  GN_LCOMP02_LRF03[i][j]     = frendy_obj.get_gam_width_tot();
  GG_LCOMP02_LRF03[i][j]     = frendy_obj.get_gam_width_n();
  GFA_LCOMP02_LRF03[i][j]    = frendy_obj.get_gam_width_fis_a();
  GFB_LCOMP02_LRF03[i][j]    = frendy_obj.get_gam_width_fis_b();
  DER_LCOMP02_LRF03[i][j]    = frendy_obj.get_ene_reso_uncertainty();
  DGN_LCOMP02_LRF03[i][j]    = frendy_obj.get_gam_width_n_uncertainty();
  DGG_LCOMP02_LRF03[i][j]    = frendy_obj.get_gam_width_rad_uncertainty();
  DGFA_LCOMP02_LRF03[i][j]   = frendy_obj.get_gam_width_fis_a_uncertainty();
  DGFB_LCOMP02_LRF03[i][j]   = frendy_obj.get_gam_width_fis_b_uncertainty();
  NDIGIT_LCOMP02_LRF03[i][j] = frendy_obj.get_cov_matrix_digit_no(); //Actual data name in Parser class is different (NDIGIT) 
  NNN_LCOMP02_LRF03[i][j]    = frendy_obj.get_cov_param_no(); //Actual data name in Parser class is different (NNN) 
  II_LCOMP02_LRF03[i][j]     = frendy_obj.get_cov_matrix_location_i(); //Actual data name in Parser class is different (II) 
  JJ_LCOMP02_LRF03[i][j]     = frendy_obj.get_cov_matrix_location_j(); //Actual data name in Parser class is different (JJ) 
  KIJ_LCOMP02_LRF03[i][j]    = frendy_obj.get_cov_matrix_coef(); //Actual data name in Parser class is different (KIJ) 

  NM_LCOMP02_LRF03[i][j] = static_cast<Integer>(II_LCOMP02_LRF03[i][j].size());
  
  //Set ENDF format data
  //endf_obj.clear();
  endf_obj.set_LAD(LAD);
  endf_obj.set_DAP_LCOMP02_LRF03(DAP_LCOMP02_LRF03); //Actual data name in Parser class is different (DAP_TAB) 
  endf_obj.set_APL_LCOMP02_LRF03(APL_LCOMP02_LRF03); //Actual data name in Parser class is different (APL) 
  endf_obj.set_ER_LCOMP02_LRF03(ER_LCOMP02_LRF03);
  endf_obj.set_AJ_LCOMP02_LRF03(AJ_LCOMP02_LRF03);
  endf_obj.set_GN_LCOMP02_LRF03(GN_LCOMP02_LRF03);
  endf_obj.set_GG_LCOMP02_LRF03(GG_LCOMP02_LRF03);
  endf_obj.set_GFA_LCOMP02_LRF03(GFA_LCOMP02_LRF03);
  endf_obj.set_GFB_LCOMP02_LRF03(GFB_LCOMP02_LRF03);
  endf_obj.set_DER_LCOMP02_LRF03(DER_LCOMP02_LRF03);
  endf_obj.set_DGN_LCOMP02_LRF03(DGN_LCOMP02_LRF03);
  endf_obj.set_DGG_LCOMP02_LRF03(DGG_LCOMP02_LRF03);
  endf_obj.set_DGFA_LCOMP02_LRF03(DGFA_LCOMP02_LRF03);
  endf_obj.set_DGFB_LCOMP02_LRF03(DGFB_LCOMP02_LRF03);
  endf_obj.set_NDIGIT_LCOMP02_LRF03(NDIGIT_LCOMP02_LRF03); //Actual data name in Parser class is different (NDIGIT) 
  endf_obj.set_NNN_LCOMP02_LRF03(NNN_LCOMP02_LRF03); //Actual data name in Parser class is different (NNN) 
  endf_obj.set_NM_LCOMP02_LRF03(NM_LCOMP02_LRF03); //Actual data name in Parser class is different (NM) 
  endf_obj.set_II_LCOMP02_LRF03(II_LCOMP02_LRF03); //Actual data name in Parser class is different (II) 
  endf_obj.set_JJ_LCOMP02_LRF03(JJ_LCOMP02_LRF03); //Actual data name in Parser class is different (JJ) 
  endf_obj.set_KIJ_LCOMP02_LRF03(KIJ_LCOMP02_LRF03); //Actual data name in Parser class is different (KIJ) 

  //Clear declared data
  clr_obj.clear_vec_array2_int(LAD);
  clr_obj.clear_vec_array3_real(DAP_LCOMP02_LRF03);
  clr_obj.clear_vec_array2_real(APL_LCOMP02_LRF03);
  clr_obj.clear_vec_array3_real(ER_LCOMP02_LRF03);
  clr_obj.clear_vec_array3_real(AJ_LCOMP02_LRF03);
  clr_obj.clear_vec_array3_real(GN_LCOMP02_LRF03);
  clr_obj.clear_vec_array3_real(GG_LCOMP02_LRF03);
  clr_obj.clear_vec_array3_real(GFA_LCOMP02_LRF03);
  clr_obj.clear_vec_array3_real(GFB_LCOMP02_LRF03);
  clr_obj.clear_vec_array3_real(DER_LCOMP02_LRF03);
  clr_obj.clear_vec_array3_real(DGN_LCOMP02_LRF03);
  clr_obj.clear_vec_array3_real(DGG_LCOMP02_LRF03);
  clr_obj.clear_vec_array3_real(DGFA_LCOMP02_LRF03);
  clr_obj.clear_vec_array3_real(DGFB_LCOMP02_LRF03);
  clr_obj.clear_vec_array2_int(NDIGIT_LCOMP02_LRF03);
  clr_obj.clear_vec_array2_int(NNN_LCOMP02_LRF03);
  clr_obj.clear_vec_array2_int(NM_LCOMP02_LRF03);
  clr_obj.clear_vec_array3_int(II_LCOMP02_LRF03);
  clr_obj.clear_vec_array3_int(JJ_LCOMP02_LRF03);
  clr_obj.clear_vec_array4_int(KIJ_LCOMP02_LRF03);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//MF32MT151Parser -> ReichMooreCompactCovarianceDataContainer
void MF32MT151ConverterReichMooreCompact::convert_endf_format_to_frendy( int& i, int& j,
  MF32MT151Parser& endf_obj, ReichMooreCompactCovarianceDataContainer& frendy_obj )
{
  //Get frendy data
  Integer                  angular_distr_calc_flg      = endf_obj.get_LAD()[i][j];
  vector<Real>             scat_radius_uncertainty     = endf_obj.get_DAP_LCOMP02_LRF03()[i][j]; //Actual data name in Parser class is different (DAP_TAB) 
  Real                     scat_radius_l               = endf_obj.get_APL_LCOMP02_LRF03()[i][j]; //Actual data name in Parser class is different (APL) 
  vector<Real>             ene_reso                    = endf_obj.get_ER_LCOMP02_LRF03()[i][j];
  vector<Real>             j_value_abs                 = endf_obj.get_AJ_LCOMP02_LRF03()[i][j];
  vector<Real>             gam_width_tot               = endf_obj.get_GN_LCOMP02_LRF03()[i][j];
  vector<Real>             gam_width_n                 = endf_obj.get_GG_LCOMP02_LRF03()[i][j];
  vector<Real>             gam_width_fis_a             = endf_obj.get_GFA_LCOMP02_LRF03()[i][j];
  vector<Real>             gam_width_fis_b             = endf_obj.get_GFB_LCOMP02_LRF03()[i][j];
  vector<Real>             ene_reso_uncertainty        = endf_obj.get_DER_LCOMP02_LRF03()[i][j];
  vector<Real>             gam_width_n_uncertainty     = endf_obj.get_DGN_LCOMP02_LRF03()[i][j];
  vector<Real>             gam_width_rad_uncertainty   = endf_obj.get_DGG_LCOMP02_LRF03()[i][j];
  vector<Real>             gam_width_fis_a_uncertainty = endf_obj.get_DGFA_LCOMP02_LRF03()[i][j];
  vector<Real>             gam_width_fis_b_uncertainty = endf_obj.get_DGFB_LCOMP02_LRF03()[i][j];
  Integer                  cov_matrix_digit_no         = endf_obj.get_NDIGIT_LCOMP02_LRF03()[i][j]; //Actual data name in Parser class is different (NDIGIT) 
  Integer                  cov_param_no                = endf_obj.get_NNN_LCOMP02_LRF03()[i][j]; //Actual data name in Parser class is different (NNN) 
  vector<Integer>          cov_matrix_location_i       = endf_obj.get_II_LCOMP02_LRF03()[i][j]; //Actual data name in Parser class is different (II) 
  vector<Integer>          cov_matrix_location_j       = endf_obj.get_JJ_LCOMP02_LRF03()[i][j]; //Actual data name in Parser class is different (JJ) 
  vector<vector<Integer> > cov_matrix_coef             = endf_obj.get_KIJ_LCOMP02_LRF03()[i][j]; //Actual data name in Parser class is different (KIJ) 

  //Set ENDF format data
  frendy_obj.clear();
  frendy_obj.set_angular_distr_calc_flg(angular_distr_calc_flg);
  frendy_obj.set_scat_radius_uncertainty(scat_radius_uncertainty); //Actual data name in Parser class is different (DAP_TAB) 
  frendy_obj.set_scat_radius_l(scat_radius_l); //Actual data name in Parser class is different (APL) 
  frendy_obj.set_ene_reso(ene_reso);
  frendy_obj.set_j_value_abs(j_value_abs);
  frendy_obj.set_gam_width_tot(gam_width_tot);
  frendy_obj.set_gam_width_n(gam_width_n);
  frendy_obj.set_gam_width_fis_a(gam_width_fis_a);
  frendy_obj.set_gam_width_fis_b(gam_width_fis_b);
  frendy_obj.set_ene_reso_uncertainty(ene_reso_uncertainty);
  frendy_obj.set_gam_width_n_uncertainty(gam_width_n_uncertainty);
  frendy_obj.set_gam_width_rad_uncertainty(gam_width_rad_uncertainty);
  frendy_obj.set_gam_width_fis_a_uncertainty(gam_width_fis_a_uncertainty);
  frendy_obj.set_gam_width_fis_b_uncertainty(gam_width_fis_b_uncertainty);
  frendy_obj.set_cov_matrix_digit_no(cov_matrix_digit_no); //Actual data name in Parser class is different (NDIGIT) 
  frendy_obj.set_cov_param_no(cov_param_no); //Actual data name in Parser class is different (NNN) 
  frendy_obj.set_cov_matrix_location_i(cov_matrix_location_i); //Actual data name in Parser class is different (II) 
  frendy_obj.set_cov_matrix_location_j(cov_matrix_location_j); //Actual data name in Parser class is different (JJ) 
  frendy_obj.set_cov_matrix_coef(cov_matrix_coef); //Actual data name in Parser class is different (KIJ) 

  //Clear declared data
  angular_distr_calc_flg      = 0;
  scat_radius_uncertainty.clear();
  scat_radius_l               = 0.0;
  ene_reso.clear();
  j_value_abs.clear();
  gam_width_tot.clear();
  gam_width_n.clear();
  gam_width_fis_a.clear();
  gam_width_fis_b.clear();
  ene_reso_uncertainty.clear();
  gam_width_n_uncertainty.clear();
  gam_width_rad_uncertainty.clear();
  gam_width_fis_a_uncertainty.clear();
  gam_width_fis_b_uncertainty.clear();
  cov_matrix_digit_no         = 0;
  cov_param_no                = 0;
  cov_matrix_location_i.clear();
  cov_matrix_location_j.clear();
  clr_obj.clear_vec_array2_int(cov_matrix_coef);
}

