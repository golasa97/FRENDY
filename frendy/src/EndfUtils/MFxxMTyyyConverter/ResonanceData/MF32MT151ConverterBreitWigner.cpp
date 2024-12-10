#include "EndfUtils/MFxxMTyyyConverter/ResonanceData/MF32MT151ConverterBreitWigner.hpp"

using namespace frendy;

//constructor
MF32MT151ConverterBreitWigner::MF32MT151ConverterBreitWigner(void)
{
}

//destructor
MF32MT151ConverterBreitWigner::~MF32MT151ConverterBreitWigner(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//BreitWignerCovarianceDataContainer -> MF32MT151Parser
void MF32MT151ConverterBreitWigner::convert_frendy_to_endf_format
  ( int& i, int& i_max, int& j, vector<int>& j_max,
  BreitWignerCovarianceDataContainer& frendy_obj, MF32MT151Parser& endf_obj )
{
  //Declare ENDF data
  vector<vector<Real> >                            DAP_LCOMP01_LRF01  = endf_obj.get_DAP_LCOMP01_LRF01();
  vector<vector<vector<Integer> > >                MPAR_LCOMP01_LRF01 = endf_obj.get_MPAR_LCOMP01_LRF01();
  vector<vector<vector<vector<Real> > > >          ER_LCOMP01_LRF01   = endf_obj.get_ER_LCOMP01_LRF01();
  vector<vector<vector<vector<Real> > > >          AJ_LCOMP01_LRF01   = endf_obj.get_AJ_LCOMP01_LRF01();
  vector<vector<vector<vector<Real> > > >          GT_LCOMP01_LRF01   = endf_obj.get_GT_LCOMP01_LRF01();
  vector<vector<vector<vector<Real> > > >          GN_LCOMP01_LRF01   = endf_obj.get_GN_LCOMP01_LRF01();
  vector<vector<vector<vector<Real> > > >          GG_LCOMP01_LRF01   = endf_obj.get_GG_LCOMP01_LRF01();
  vector<vector<vector<vector<Real> > > >          GF_LCOMP01_LRF01   = endf_obj.get_GF_LCOMP01_LRF01();
  vector<vector<vector<vector<vector<Real> > > > > V_LCOMP01_LRF01    = endf_obj.get_V_LCOMP01_LRF01();
  vector<vector<vector<Integer> > >                IDP_LRU01          = endf_obj.get_IDP_LRU01();
  vector<vector<vector<Integer> > >                LB_LRU01           = endf_obj.get_LB_LRU01();
  vector<vector<vector<vector<Real> > > >          E_K_LRU01          = endf_obj.get_E_K_LRU01();
  vector<vector<vector<vector<vector<Real> > > > > F_K_LRU01          = endf_obj.get_F_K_LRU01();
   
  vector<vector<Integer> > NSRS_LCOMP01_LRF01 = endf_obj.get_NSRS_LCOMP01_LRF01();
  vector<vector<Integer> > NLRS_LCOMP01_LRF01 = endf_obj.get_NLRS_LCOMP01_LRF01();
   
  //Resize ENDF data
  int ele_no = static_cast<int>(ER_LCOMP01_LRF01.size());
  if( ele_no == 0 )
  {
    DAP_LCOMP01_LRF01.resize(i_max);
    MPAR_LCOMP01_LRF01.resize(i_max);
    ER_LCOMP01_LRF01.resize(i_max);
    AJ_LCOMP01_LRF01.resize(i_max);
    GT_LCOMP01_LRF01.resize(i_max);
    GN_LCOMP01_LRF01.resize(i_max);
    GG_LCOMP01_LRF01.resize(i_max);
    GF_LCOMP01_LRF01.resize(i_max);
    V_LCOMP01_LRF01.resize(i_max);
    IDP_LRU01.resize(i_max);
    LB_LRU01.resize(i_max);
    E_K_LRU01.resize(i_max);
    F_K_LRU01.resize(i_max);
    NSRS_LCOMP01_LRF01.resize(i_max);
    NLRS_LCOMP01_LRF01.resize(i_max);
    for(int i_tmp=0; i_tmp<i_max; i_tmp++)
    {
      DAP_LCOMP01_LRF01[i_tmp].resize(j_max[i_tmp]);
      MPAR_LCOMP01_LRF01[i_tmp].resize(j_max[i_tmp]);
      ER_LCOMP01_LRF01[i_tmp].resize(j_max[i_tmp]);
      AJ_LCOMP01_LRF01[i_tmp].resize(j_max[i_tmp]);
      GT_LCOMP01_LRF01[i_tmp].resize(j_max[i_tmp]);
      GN_LCOMP01_LRF01[i_tmp].resize(j_max[i_tmp]);
      GG_LCOMP01_LRF01[i_tmp].resize(j_max[i_tmp]);
      GF_LCOMP01_LRF01[i_tmp].resize(j_max[i_tmp]);
      V_LCOMP01_LRF01[i_tmp].resize(j_max[i_tmp]);
      IDP_LRU01[i_tmp].resize(j_max[i_tmp]);
      LB_LRU01[i_tmp].resize(j_max[i_tmp]);
      E_K_LRU01[i_tmp].resize(j_max[i_tmp]);
      F_K_LRU01[i_tmp].resize(j_max[i_tmp]);
      NSRS_LCOMP01_LRF01[i_tmp].resize(j_max[i_tmp]);
      NLRS_LCOMP01_LRF01[i_tmp].resize(j_max[i_tmp]);
    }
  }
  else
  {
    if( ele_no != i_max )
    {
      string class_name = "MF32MT151ConverterBreitWigner";
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
     
    if( static_cast<int>(DAP_LCOMP01_LRF01[i].size()) != j_max[i] )
    {
      string class_name = "MF32MT151ConverterBreitWigner";
      string func_name  = "convert_frendy_to_endf_format";
      ostringstream oss01, oss02, oss03, oss04;
      oss01 << i;
      oss02 << j;
      oss03 <<  static_cast<int>(DAP_LCOMP01_LRF01[i].size());
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
  DAP_LCOMP01_LRF01[i][j]  = frendy_obj.get_scat_radius_uncertainty(); //Actual data name in Parser class is different (DAP) 
  MPAR_LCOMP01_LRF01[i][j] = frendy_obj.get_reso_parameter_no();
  ER_LCOMP01_LRF01[i][j]   = frendy_obj.get_ene_reso();
  AJ_LCOMP01_LRF01[i][j]   = frendy_obj.get_j_value_abs();
  GT_LCOMP01_LRF01[i][j]   = frendy_obj.get_gam_width_tot();
  GN_LCOMP01_LRF01[i][j]   = frendy_obj.get_gam_width_n();
  GG_LCOMP01_LRF01[i][j]   = frendy_obj.get_gam_width_rad();
  GF_LCOMP01_LRF01[i][j]   = frendy_obj.get_gam_width_fis();
  V_LCOMP01_LRF01[i][j]    = frendy_obj.get_cov_matrix_data(); //Actual data name in Parser class is different (V) 
  IDP_LRU01[i][j]          = frendy_obj.get_reso_parameter_type();
  LB_LRU01[i][j]           = frendy_obj.get_cov_pattern_flg();
  E_K_LRU01[i][j]          = frendy_obj.get_cov_table_ene();
  F_K_LRU01[i][j]          = frendy_obj.get_cov_table_coef();

  NSRS_LCOMP01_LRF01[i][j] = static_cast<Integer>(ER_LCOMP01_LRF01[i][j].size());
  NLRS_LCOMP01_LRF01[i][j] = static_cast<Integer>(IDP_LRU01[i][j].size());
  
  //Set ENDF format data
  //endf_obj.clear();
  endf_obj.set_NSRS_LCOMP01_LRF01(NSRS_LCOMP01_LRF01);
  endf_obj.set_NLRS_LCOMP01_LRF01(NLRS_LCOMP01_LRF01);
  endf_obj.set_DAP_LCOMP01_LRF01(DAP_LCOMP01_LRF01); //Actual data name in Parser class is different (DAP) 
  endf_obj.set_MPAR_LCOMP01_LRF01(MPAR_LCOMP01_LRF01);
  endf_obj.set_ER_LCOMP01_LRF01(ER_LCOMP01_LRF01);
  endf_obj.set_AJ_LCOMP01_LRF01(AJ_LCOMP01_LRF01);
  endf_obj.set_GT_LCOMP01_LRF01(GT_LCOMP01_LRF01);
  endf_obj.set_GN_LCOMP01_LRF01(GN_LCOMP01_LRF01);
  endf_obj.set_GG_LCOMP01_LRF01(GG_LCOMP01_LRF01);
  endf_obj.set_GF_LCOMP01_LRF01(GF_LCOMP01_LRF01);
  endf_obj.set_V_LCOMP01_LRF01(V_LCOMP01_LRF01); //Actual data name in Parser class is different (V) 
  endf_obj.set_IDP_LRU01(IDP_LRU01);
  endf_obj.set_LB_LRU01(LB_LRU01);
  endf_obj.set_E_K_LRU01(E_K_LRU01);
  endf_obj.set_F_K_LRU01(F_K_LRU01);

  //Clear declared data
  clr_obj.clear_vec_array2_real(DAP_LCOMP01_LRF01);
  clr_obj.clear_vec_array3_int(MPAR_LCOMP01_LRF01);
  clr_obj.clear_vec_array4_real(ER_LCOMP01_LRF01);
  clr_obj.clear_vec_array4_real(AJ_LCOMP01_LRF01);
  clr_obj.clear_vec_array4_real(GT_LCOMP01_LRF01);
  clr_obj.clear_vec_array4_real(GN_LCOMP01_LRF01);
  clr_obj.clear_vec_array4_real(GG_LCOMP01_LRF01);
  clr_obj.clear_vec_array4_real(GF_LCOMP01_LRF01);
  clr_obj.clear_vec_array5_real(V_LCOMP01_LRF01);
  clr_obj.clear_vec_array3_int(IDP_LRU01);
  clr_obj.clear_vec_array3_int(LB_LRU01);
  clr_obj.clear_vec_array4_real(E_K_LRU01);
  clr_obj.clear_vec_array5_real(F_K_LRU01);
  
  clr_obj.clear_vec_array2_int(NSRS_LCOMP01_LRF01);
  clr_obj.clear_vec_array2_int(NLRS_LCOMP01_LRF01);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//MF32MT151Parser -> BreitWignerCovarianceDataContainer
void MF32MT151ConverterBreitWigner::convert_endf_format_to_frendy( int& i, int& j,
  MF32MT151Parser& endf_obj, BreitWignerCovarianceDataContainer& frendy_obj )
{
  //Get frendy data
  Real                           scat_radius_uncertainty = endf_obj.get_DAP_LCOMP01_LRF01()[i][j]; //Actual data name in Parser class is different (DAP) 
  vector<Integer>                reso_parameter_no       = endf_obj.get_MPAR_LCOMP01_LRF01()[i][j];
  vector<vector<Real> >          ene_reso                = endf_obj.get_ER_LCOMP01_LRF01()[i][j];
  vector<vector<Real> >          j_value_abs             = endf_obj.get_AJ_LCOMP01_LRF01()[i][j];
  vector<vector<Real> >          gam_width_tot           = endf_obj.get_GT_LCOMP01_LRF01()[i][j];
  vector<vector<Real> >          gam_width_n             = endf_obj.get_GN_LCOMP01_LRF01()[i][j];
  vector<vector<Real> >          gam_width_rad           = endf_obj.get_GG_LCOMP01_LRF01()[i][j];
  vector<vector<Real> >          gam_width_fis           = endf_obj.get_GF_LCOMP01_LRF01()[i][j];
  vector<vector<vector<Real> > > cov_matrix_data         = endf_obj.get_V_LCOMP01_LRF01()[i][j]; //Actual data name in Parser class is different (V) 
  vector<Integer>                reso_parameter_type     = endf_obj.get_IDP_LRU01()[i][j];
  vector<Integer>                cov_pattern_flg         = endf_obj.get_LB_LRU01()[i][j];
  vector<vector<Real> >          cov_table_ene           = endf_obj.get_E_K_LRU01()[i][j];
  vector<vector<vector<Real> > > cov_table_coef          = endf_obj.get_F_K_LRU01()[i][j];

  //Set ENDF format data
  frendy_obj.clear();
  frendy_obj.set_scat_radius_uncertainty(scat_radius_uncertainty); //Actual data name in Parser class is different (DAP) 
  frendy_obj.set_reso_parameter_no(reso_parameter_no);
  frendy_obj.set_ene_reso(ene_reso);
  frendy_obj.set_j_value_abs(j_value_abs);
  frendy_obj.set_gam_width_tot(gam_width_tot);
  frendy_obj.set_gam_width_n(gam_width_n);
  frendy_obj.set_gam_width_rad(gam_width_rad);
  frendy_obj.set_gam_width_fis(gam_width_fis);
  frendy_obj.set_cov_matrix_data(cov_matrix_data); //Actual data name in Parser class is different (V) 
  frendy_obj.set_reso_parameter_type(reso_parameter_type);
  frendy_obj.set_cov_pattern_flg(cov_pattern_flg);
  frendy_obj.set_cov_table_ene(cov_table_ene);
  frendy_obj.set_cov_table_coef(cov_table_coef);

  //Clear declared data
  scat_radius_uncertainty = 0.0;
  reso_parameter_no.clear();
  clr_obj.clear_vec_array2_real(ene_reso);
  clr_obj.clear_vec_array2_real(j_value_abs);
  clr_obj.clear_vec_array2_real(gam_width_tot);
  clr_obj.clear_vec_array2_real(gam_width_n);
  clr_obj.clear_vec_array2_real(gam_width_rad);
  clr_obj.clear_vec_array2_real(gam_width_fis);
  clr_obj.clear_vec_array3_real(cov_matrix_data);
  reso_parameter_type.clear();
  cov_pattern_flg.clear();
  clr_obj.clear_vec_array2_real(cov_table_ene);
  clr_obj.clear_vec_array3_real(cov_table_coef);
}

