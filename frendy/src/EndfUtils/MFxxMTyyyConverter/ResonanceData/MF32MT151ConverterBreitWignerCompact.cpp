#include "EndfUtils/MFxxMTyyyConverter/ResonanceData/MF32MT151ConverterBreitWignerCompact.hpp"

using namespace frendy;

//constructor
MF32MT151ConverterBreitWignerCompact::MF32MT151ConverterBreitWignerCompact(void)
{
}

//destructor
MF32MT151ConverterBreitWignerCompact::~MF32MT151ConverterBreitWignerCompact(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//BreitWignerCompactCovarianceDataContainer -> MF32MT151Parser
void MF32MT151ConverterBreitWignerCompact::convert_frendy_to_endf_format
  ( int& i, int& i_max, int& j, vector<int>& j_max,
  BreitWignerCompactCovarianceDataContainer& frendy_obj, MF32MT151Parser& endf_obj )
{
  //Declare ENDF data
  vector<vector<Real> >                      DAP_LCOMP02_LRF01    = endf_obj.get_DAP_LCOMP02_LRF01();
  vector<vector<Real> >                      QX_LCOMP02_LRF01     = endf_obj.get_QX_LCOMP02_LRF01();
  vector<vector<Integer> >                   LRX_LCOMP02_LRF01    = endf_obj.get_LRX_LCOMP02_LRF01();
  vector<vector<vector<Real> > >             ER_LCOMP02_LRF01     = endf_obj.get_ER_LCOMP02_LRF01();
  vector<vector<vector<Real> > >             AJ_LCOMP02_LRF01     = endf_obj.get_AJ_LCOMP02_LRF01();
  vector<vector<vector<Real> > >             GT_LCOMP02_LRF01     = endf_obj.get_GT_LCOMP02_LRF01();
  vector<vector<vector<Real> > >             GN_LCOMP02_LRF01     = endf_obj.get_GN_LCOMP02_LRF01();
  vector<vector<vector<Real> > >             GG_LCOMP02_LRF01     = endf_obj.get_GG_LCOMP02_LRF01();
  vector<vector<vector<Real> > >             GF_LCOMP02_LRF01     = endf_obj.get_GF_LCOMP02_LRF01();
  vector<vector<vector<Real> > >             DER_LCOMP02_LRF01    = endf_obj.get_DER_LCOMP02_LRF01();
  vector<vector<vector<Real> > >             DGN_LCOMP02_LRF01    = endf_obj.get_DGN_LCOMP02_LRF01();
  vector<vector<vector<Real> > >             DGG_LCOMP02_LRF01    = endf_obj.get_DGG_LCOMP02_LRF01();
  vector<vector<vector<Real> > >             DGF_LCOMP02_LRF01    = endf_obj.get_DGF_LCOMP02_LRF01();
  vector<vector<Integer> >                   NDIGIT_LCOMP02_LRF01 = endf_obj.get_NDIGIT_LCOMP02_LRF01();
  vector<vector<Integer> >                   NNN_LCOMP02_LRF01    = endf_obj.get_NNN_LCOMP02_LRF01();
  vector<vector<vector<Integer> > >          II_LCOMP02_LRF01     = endf_obj.get_II_LCOMP02_LRF01();
  vector<vector<vector<Integer> > >          JJ_LCOMP02_LRF01     = endf_obj.get_JJ_LCOMP02_LRF01();
  vector<vector<vector<vector<Integer> > > > KIJ_LCOMP02_LRF01    = endf_obj.get_KIJ_LCOMP02_LRF01();
   
  vector<vector<Integer> >                   NM_LCOMP02_LRF01     = endf_obj.get_NM_LCOMP02_LRF01();
  
  //Resize ENDF data
  int ele_no = static_cast<int>(ER_LCOMP02_LRF01.size());
  if( ele_no == 0 )
  {
    DAP_LCOMP02_LRF01.resize(i_max);
    QX_LCOMP02_LRF01.resize(i_max);
    LRX_LCOMP02_LRF01.resize(i_max);
    ER_LCOMP02_LRF01.resize(i_max);
    AJ_LCOMP02_LRF01.resize(i_max);
    GT_LCOMP02_LRF01.resize(i_max);
    GN_LCOMP02_LRF01.resize(i_max);
    GG_LCOMP02_LRF01.resize(i_max);
    GF_LCOMP02_LRF01.resize(i_max);
    DER_LCOMP02_LRF01.resize(i_max);
    DGN_LCOMP02_LRF01.resize(i_max);
    DGG_LCOMP02_LRF01.resize(i_max);
    DGF_LCOMP02_LRF01.resize(i_max);
    NDIGIT_LCOMP02_LRF01.resize(i_max);
    NNN_LCOMP02_LRF01.resize(i_max);
    II_LCOMP02_LRF01.resize(i_max);
    JJ_LCOMP02_LRF01.resize(i_max);
    KIJ_LCOMP02_LRF01.resize(i_max);
    NM_LCOMP02_LRF01.resize(i_max);
    for(int i_tmp=0; i_tmp<i_max; i_tmp++)
    {
      DAP_LCOMP02_LRF01[i_tmp].resize(j_max[i_tmp]);
      QX_LCOMP02_LRF01[i_tmp].resize(j_max[i_tmp]);
      LRX_LCOMP02_LRF01[i_tmp].resize(j_max[i_tmp]);
      ER_LCOMP02_LRF01[i_tmp].resize(j_max[i_tmp]);
      AJ_LCOMP02_LRF01[i_tmp].resize(j_max[i_tmp]);
      GT_LCOMP02_LRF01[i_tmp].resize(j_max[i_tmp]);
      GN_LCOMP02_LRF01[i_tmp].resize(j_max[i_tmp]);
      GG_LCOMP02_LRF01[i_tmp].resize(j_max[i_tmp]);
      GF_LCOMP02_LRF01[i_tmp].resize(j_max[i_tmp]);
      DER_LCOMP02_LRF01[i_tmp].resize(j_max[i_tmp]);
      DGN_LCOMP02_LRF01[i_tmp].resize(j_max[i_tmp]);
      DGG_LCOMP02_LRF01[i_tmp].resize(j_max[i_tmp]);
      DGF_LCOMP02_LRF01[i_tmp].resize(j_max[i_tmp]);
      NDIGIT_LCOMP02_LRF01[i_tmp].resize(j_max[i_tmp]);
      NNN_LCOMP02_LRF01[i_tmp].resize(j_max[i_tmp]);
      II_LCOMP02_LRF01[i_tmp].resize(j_max[i_tmp]);
      JJ_LCOMP02_LRF01[i_tmp].resize(j_max[i_tmp]);
      KIJ_LCOMP02_LRF01[i_tmp].resize(j_max[i_tmp]);
      NM_LCOMP02_LRF01[i_tmp].resize(j_max[i_tmp]);
    }
  }
  else
  {
    if( ele_no != i_max )
    {
      string class_name = "MF32MT151ConverterBreitWignerCompact";
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
     
    if( static_cast<int>(DAP_LCOMP02_LRF01[i].size()) != j_max[i] )
    {
      string class_name = "MF32MT151ConverterBreitWignerCompact";
      string func_name  = "convert_frendy_to_endf_format";
      ostringstream oss01, oss02, oss03, oss04;
      oss01 << i;
      oss02 << j;
      oss03 <<  static_cast<int>(DAP_LCOMP02_LRF01[i].size());
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
  DAP_LCOMP02_LRF01[i][j]    = frendy_obj.get_scat_radius_uncertainty(); //Actual data name in Parser class is different (DAP) 
  QX_LCOMP02_LRF01[i][j]     = frendy_obj.get_q_value(); //Actual data name in Parser class is different (QX) 
  LRX_LCOMP02_LRF01[i][j]    = frendy_obj.get_competitive_width_flg(); //Actual data name in Parser class is different (LRX) 
  ER_LCOMP02_LRF01[i][j]     = frendy_obj.get_ene_reso();
  AJ_LCOMP02_LRF01[i][j]     = frendy_obj.get_j_value_abs();
  GT_LCOMP02_LRF01[i][j]     = frendy_obj.get_gam_width_tot();
  GN_LCOMP02_LRF01[i][j]     = frendy_obj.get_gam_width_n();
  GG_LCOMP02_LRF01[i][j]     = frendy_obj.get_gam_width_rad();
  GF_LCOMP02_LRF01[i][j]     = frendy_obj.get_gam_width_fis();
  DER_LCOMP02_LRF01[i][j]    = frendy_obj.get_ene_reso_uncertainty();
  DGN_LCOMP02_LRF01[i][j]    = frendy_obj.get_gam_width_n_uncertainty();
  DGG_LCOMP02_LRF01[i][j]    = frendy_obj.get_gam_width_rad_uncertainty();
  DGF_LCOMP02_LRF01[i][j]    = frendy_obj.get_gam_width_fis_uncertainty();
  NDIGIT_LCOMP02_LRF01[i][j] = frendy_obj.get_cov_matrix_digit_no(); //Actual data name in Parser class is different (NDIGIT) 
  NNN_LCOMP02_LRF01[i][j]    = frendy_obj.get_cov_param_no(); //Actual data name in Parser class is different (NNN) 
  II_LCOMP02_LRF01[i][j]     = frendy_obj.get_cov_matrix_location_i(); //Actual data name in Parser class is different (II) 
  JJ_LCOMP02_LRF01[i][j]     = frendy_obj.get_cov_matrix_location_j(); //Actual data name in Parser class is different (JJ) 
  KIJ_LCOMP02_LRF01[i][j]    = frendy_obj.get_cov_matrix_coef(); //Actual data name in Parser class is different (KIJ) 

  NM_LCOMP02_LRF01[i][j] = static_cast<Integer>(II_LCOMP02_LRF01[i][j].size());

  //Set ENDF format data
  //endf_obj.clear();
  endf_obj.set_DAP_LCOMP02_LRF01(DAP_LCOMP02_LRF01); //Actual data name in Parser class is different (DAP) 
  endf_obj.set_QX_LCOMP02_LRF01(QX_LCOMP02_LRF01); //Actual data name in Parser class is different (QX) 
  endf_obj.set_LRX_LCOMP02_LRF01(LRX_LCOMP02_LRF01); //Actual data name in Parser class is different (LRX) 
  endf_obj.set_ER_LCOMP02_LRF01(ER_LCOMP02_LRF01);
  endf_obj.set_AJ_LCOMP02_LRF01(AJ_LCOMP02_LRF01);
  endf_obj.set_GT_LCOMP02_LRF01(GT_LCOMP02_LRF01);
  endf_obj.set_GN_LCOMP02_LRF01(GN_LCOMP02_LRF01);
  endf_obj.set_GG_LCOMP02_LRF01(GG_LCOMP02_LRF01);
  endf_obj.set_GF_LCOMP02_LRF01(GF_LCOMP02_LRF01);
  endf_obj.set_DER_LCOMP02_LRF01(DER_LCOMP02_LRF01);
  endf_obj.set_DGN_LCOMP02_LRF01(DGN_LCOMP02_LRF01);
  endf_obj.set_DGG_LCOMP02_LRF01(DGG_LCOMP02_LRF01);
  endf_obj.set_DGF_LCOMP02_LRF01(DGF_LCOMP02_LRF01);
  endf_obj.set_NDIGIT_LCOMP02_LRF01(NDIGIT_LCOMP02_LRF01); //Actual data name in Parser class is different (NDIGIT) 
  endf_obj.set_NNN_LCOMP02_LRF01(NNN_LCOMP02_LRF01); //Actual data name in Parser class is different (NNN) 
  endf_obj.set_NM_LCOMP02_LRF01(NM_LCOMP02_LRF01); //Actual data name in Parser class is different (NM) 
  endf_obj.set_II_LCOMP02_LRF01(II_LCOMP02_LRF01); //Actual data name in Parser class is different (II) 
  endf_obj.set_JJ_LCOMP02_LRF01(JJ_LCOMP02_LRF01); //Actual data name in Parser class is different (JJ) 
  endf_obj.set_KIJ_LCOMP02_LRF01(KIJ_LCOMP02_LRF01); //Actual data name in Parser class is different (KIJ) 

  //Clear declared data
  clr_obj.clear_vec_array2_real(DAP_LCOMP02_LRF01);
  clr_obj.clear_vec_array2_real(QX_LCOMP02_LRF01);
  clr_obj.clear_vec_array2_int(LRX_LCOMP02_LRF01);
  clr_obj.clear_vec_array3_real(ER_LCOMP02_LRF01);
  clr_obj.clear_vec_array3_real(AJ_LCOMP02_LRF01);
  clr_obj.clear_vec_array3_real(GT_LCOMP02_LRF01);
  clr_obj.clear_vec_array3_real(GN_LCOMP02_LRF01);
  clr_obj.clear_vec_array3_real(GG_LCOMP02_LRF01);
  clr_obj.clear_vec_array3_real(GF_LCOMP02_LRF01);
  clr_obj.clear_vec_array3_real(DER_LCOMP02_LRF01);
  clr_obj.clear_vec_array3_real(DGN_LCOMP02_LRF01);
  clr_obj.clear_vec_array3_real(DGG_LCOMP02_LRF01);
  clr_obj.clear_vec_array3_real(DGF_LCOMP02_LRF01);
  clr_obj.clear_vec_array2_int(NDIGIT_LCOMP02_LRF01);
  clr_obj.clear_vec_array2_int(NNN_LCOMP02_LRF01);
  clr_obj.clear_vec_array2_int(NM_LCOMP02_LRF01);
  clr_obj.clear_vec_array3_int(II_LCOMP02_LRF01);
  clr_obj.clear_vec_array3_int(JJ_LCOMP02_LRF01);
  clr_obj.clear_vec_array4_int(KIJ_LCOMP02_LRF01);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//MF32MT151Parser -> BreitWignerCompactCovarianceDataContainer
void MF32MT151ConverterBreitWignerCompact::convert_endf_format_to_frendy( int& i, int& j,
  MF32MT151Parser& endf_obj, BreitWignerCompactCovarianceDataContainer& frendy_obj )
{
  //Get frendy data
  Real                     scat_radius_uncertainty   = endf_obj.get_DAP_LCOMP02_LRF01()[i][j]; //Actual data name in Parser class is different (DAP) 
  Real                     q_value                   = endf_obj.get_QX_LCOMP02_LRF01()[i][j]; //Actual data name in Parser class is different (QX) 
  Integer                  competitive_width_flg     = endf_obj.get_LRX_LCOMP02_LRF01()[i][j]; //Actual data name in Parser class is different (LRX) 
  vector<Real>             ene_reso                  = endf_obj.get_ER_LCOMP02_LRF01()[i][j];
  vector<Real>             j_value_abs               = endf_obj.get_AJ_LCOMP02_LRF01()[i][j];
  vector<Real>             gam_width_tot             = endf_obj.get_GT_LCOMP02_LRF01()[i][j];
  vector<Real>             gam_width_n               = endf_obj.get_GN_LCOMP02_LRF01()[i][j];
  vector<Real>             gam_width_rad             = endf_obj.get_GG_LCOMP02_LRF01()[i][j];
  vector<Real>             gam_width_fis             = endf_obj.get_GF_LCOMP02_LRF01()[i][j];
  vector<Real>             ene_reso_uncertainty      = endf_obj.get_DER_LCOMP02_LRF01()[i][j];
  vector<Real>             gam_width_n_uncertainty   = endf_obj.get_DGN_LCOMP02_LRF01()[i][j];
  vector<Real>             gam_width_rad_uncertainty = endf_obj.get_DGG_LCOMP02_LRF01()[i][j];
  vector<Real>             gam_width_fis_uncertainty = endf_obj.get_DGF_LCOMP02_LRF01()[i][j];
  Integer                  cov_matrix_digit_no       = endf_obj.get_NDIGIT_LCOMP02_LRF01()[i][j]; //Actual data name in Parser class is different (NDIGIT) 
  Integer                  cov_param_no              = endf_obj.get_NNN_LCOMP02_LRF01()[i][j]; //Actual data name in Parser class is different (NNN) 
  vector<Integer>          cov_matrix_location_i     = endf_obj.get_II_LCOMP02_LRF01()[i][j]; //Actual data name in Parser class is different (II) 
  vector<Integer>          cov_matrix_location_j     = endf_obj.get_JJ_LCOMP02_LRF01()[i][j]; //Actual data name in Parser class is different (JJ) 
  vector<vector<Integer> > cov_matrix_coef           = endf_obj.get_KIJ_LCOMP02_LRF01()[i][j]; //Actual data name in Parser class is different (KIJ) 

  //Set ENDF format data
  frendy_obj.clear();
  frendy_obj.set_scat_radius_uncertainty(scat_radius_uncertainty); //Actual data name in Parser class is different (DAP) 
  frendy_obj.set_q_value(q_value); //Actual data name in Parser class is different (QX) 
  frendy_obj.set_competitive_width_flg(competitive_width_flg); //Actual data name in Parser class is different (LRX) 
  frendy_obj.set_ene_reso(ene_reso);
  frendy_obj.set_j_value_abs(j_value_abs);
  frendy_obj.set_gam_width_tot(gam_width_tot);
  frendy_obj.set_gam_width_n(gam_width_n);
  frendy_obj.set_gam_width_rad(gam_width_rad);
  frendy_obj.set_gam_width_fis(gam_width_fis);
  frendy_obj.set_ene_reso_uncertainty(ene_reso_uncertainty);
  frendy_obj.set_gam_width_n_uncertainty(gam_width_n_uncertainty);
  frendy_obj.set_gam_width_rad_uncertainty(gam_width_rad_uncertainty);
  frendy_obj.set_gam_width_fis_uncertainty(gam_width_fis_uncertainty);
  frendy_obj.set_cov_matrix_digit_no(cov_matrix_digit_no); //Actual data name in Parser class is different (NDIGIT) 
  frendy_obj.set_cov_param_no(cov_param_no); //Actual data name in Parser class is different (NNN) 
  frendy_obj.set_cov_matrix_location_i(cov_matrix_location_i); //Actual data name in Parser class is different (II) 
  frendy_obj.set_cov_matrix_location_j(cov_matrix_location_j); //Actual data name in Parser class is different (JJ) 
  frendy_obj.set_cov_matrix_coef(cov_matrix_coef); //Actual data name in Parser class is different (KIJ) 

  //Clear declared data
  scat_radius_uncertainty   = 0.0;
  q_value                   = 0.0;
  competitive_width_flg     = 0;
  ene_reso.clear();
  j_value_abs.clear();
  gam_width_tot.clear();
  gam_width_n.clear();
  gam_width_rad.clear();
  gam_width_fis.clear();
  ene_reso_uncertainty.clear();
  gam_width_n_uncertainty.clear();
  gam_width_rad_uncertainty.clear();
  gam_width_fis_uncertainty.clear();
  cov_matrix_digit_no       = 0;
  cov_param_no              = 0;
  cov_matrix_location_i.clear();
  cov_matrix_location_j.clear();
  clr_obj.clear_vec_array2_int(cov_matrix_coef);
}

