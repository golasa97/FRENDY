#include "EndfUtils/MFxxMTyyyConverter/ResonanceData/MF32MT151ConverterRMatrixLimited.hpp"

using namespace frendy;

//constructor
MF32MT151ConverterRMatrixLimited::MF32MT151ConverterRMatrixLimited(void)
{
}

//destructor
MF32MT151ConverterRMatrixLimited::~MF32MT151ConverterRMatrixLimited(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//RMatrixLimitedCovarianceDataContainer -> MF32MT151Parser
void MF32MT151ConverterRMatrixLimited::convert_frendy_to_endf_format
  ( int& i, int& i_max, int& j, vector<int>& j_max,
  RMatrixLimitedCovarianceDataContainer& frendy_obj, MF32MT151Parser& endf_obj )
{
  //Declare ENDF data
  vector<vector<Integer> >                                  IFG                = endf_obj.get_IFG();
  vector<vector<vector<vector<Real> > > >                   DAP_LCOMP01_LRF07  = endf_obj.get_DAP_LCOMP01_LRF07();
  vector<vector<vector<Integer> > >                         NJSX_LCOMP01_LRF07 = endf_obj.get_NJSX_LCOMP01_LRF07();
  vector<vector<vector<vector<vector<Real> > > > >          ER_LCOMP01_LRF07   = endf_obj.get_ER_LCOMP01_LRF07();
  vector<vector<vector<vector<vector<vector<Real> > > > > > GAM_LCOMP01_LRF07  = endf_obj.get_GAM_LCOMP01_LRF07();
  vector<vector<vector<vector<vector<Real> > > > >          V_LCOMP01_LRF07    = endf_obj.get_V_LCOMP01_LRF07();
  vector<vector<vector<Integer> > >                         IDP_LRU01          = endf_obj.get_IDP_LRU01();
  vector<vector<vector<Integer> > >                         LB_LRU01           = endf_obj.get_LB_LRU01();
  vector<vector<vector<vector<Real> > > >                   E_K_LRU01          = endf_obj.get_E_K_LRU01();
  vector<vector<vector<vector<vector<Real> > > > >          F_K_LRU01          = endf_obj.get_F_K_LRU01();
   
  vector<vector<Integer> >                                  NSRS_LCOMP01_LRF07 = endf_obj.get_NSRS_LCOMP01_LRF07();
  vector<vector<Integer> >                                  NLRS_LCOMP01_LRF07 = endf_obj.get_NLRS_LCOMP01_LRF07();
   
  //Resize ENDF data
  int ele_no = static_cast<int>(NJSX_LCOMP01_LRF07.size());
  if( ele_no == 0 )
  {
    IFG.resize(i_max);
    DAP_LCOMP01_LRF07.resize(i_max);
    NJSX_LCOMP01_LRF07.resize(i_max);
    ER_LCOMP01_LRF07.resize(i_max);
    GAM_LCOMP01_LRF07.resize(i_max);
    V_LCOMP01_LRF07.resize(i_max);
    IDP_LRU01.resize(i_max);
    LB_LRU01.resize(i_max);
    E_K_LRU01.resize(i_max);
    F_K_LRU01.resize(i_max);
    NSRS_LCOMP01_LRF07.resize(i_max);
    NLRS_LCOMP01_LRF07.resize(i_max);
    for(int i_tmp=0; i_tmp<i_max; i_tmp++)
    {
      IFG[i_tmp].resize(j_max[i_tmp]);
      DAP_LCOMP01_LRF07[i_tmp].resize(j_max[i_tmp]);
      NJSX_LCOMP01_LRF07[i_tmp].resize(j_max[i_tmp]);
      ER_LCOMP01_LRF07[i_tmp].resize(j_max[i_tmp]);
      GAM_LCOMP01_LRF07[i_tmp].resize(j_max[i_tmp]);
      V_LCOMP01_LRF07[i_tmp].resize(j_max[i_tmp]);
      IDP_LRU01[i_tmp].resize(j_max[i_tmp]);
      LB_LRU01[i_tmp].resize(j_max[i_tmp]);
      E_K_LRU01[i_tmp].resize(j_max[i_tmp]);
      F_K_LRU01[i_tmp].resize(j_max[i_tmp]);
      NSRS_LCOMP01_LRF07[i_tmp].resize(j_max[i_tmp]);
      NLRS_LCOMP01_LRF07[i_tmp].resize(j_max[i_tmp]);
    }
  }
  else
  {
    if( ele_no != i_max )
    {
      string class_name = "MF32MT151ConverterRMatrixLimited";
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
     
    if( static_cast<int>(DAP_LCOMP01_LRF07[i].size()) != j_max[i] )
    {
      string class_name = "MF32MT151ConverterRMatrixLimited";
      string func_name  = "convert_frendy_to_endf_format";
      ostringstream oss01, oss02, oss03, oss04;
      oss01 << i;
      oss02 << j;
      oss03 <<  static_cast<int>(DAP_LCOMP01_LRF07[i].size());
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
  IFG[i][j]                = frendy_obj.get_gam_width_flg();
  DAP_LCOMP01_LRF07[i][j]  = frendy_obj.get_scat_radius_list_uncertainty(); //Actual data name in Parser class is different (DAP_LRF07) 
  NJSX_LCOMP01_LRF07[i][j] = frendy_obj.get_j_pi_no();
  ER_LCOMP01_LRF07[i][j]   = frendy_obj.get_ene_reso();
  GAM_LCOMP01_LRF07[i][j]  = frendy_obj.get_gam_width();
  V_LCOMP01_LRF07[i][j]    = frendy_obj.get_cov_matrix_data(); //Actual data name in Parser class is different (V) 
  IDP_LRU01[i][j]          = frendy_obj.get_reso_parameter_type(); //The data name is not found in Parser class.
  LB_LRU01[i][j]           = frendy_obj.get_cov_pattern_flg();
  E_K_LRU01[i][j]          = frendy_obj.get_cov_table_ene();
  F_K_LRU01[i][j]          = frendy_obj.get_cov_table_coef(); 

  NSRS_LCOMP01_LRF07[i][j] = static_cast<Integer>(NJSX_LCOMP01_LRF07[i][j].size());
  NLRS_LCOMP01_LRF07[i][j] = static_cast<Integer>(IDP_LRU01[i][j].size());

  //Set ENDF format data
  //endf_obj.clear();
  endf_obj.set_IFG(IFG);
  endf_obj.set_DAP_LCOMP01_LRF07(DAP_LCOMP01_LRF07); //Actual data name in Parser class is different (DAP_LRF07) 
  endf_obj.set_NSRS_LCOMP01_LRF07(NSRS_LCOMP01_LRF07); //Actual data name in Parser class is different (NSRS) 
  endf_obj.set_NLRS_LCOMP01_LRF07(NLRS_LCOMP01_LRF07); //Actual data name in Parser class is different (NLRS) 
  endf_obj.set_NJSX_LCOMP01_LRF07(NJSX_LCOMP01_LRF07);
  endf_obj.set_ER_LCOMP01_LRF07(ER_LCOMP01_LRF07);
  endf_obj.set_GAM_LCOMP01_LRF07(GAM_LCOMP01_LRF07);
  endf_obj.set_V_LCOMP01_LRF07(V_LCOMP01_LRF07); //Actual data name in Parser class is different (V) 
  endf_obj.set_IDP_LRU01(IDP_LRU01);
  endf_obj.set_LB_LRU01(LB_LRU01);
  endf_obj.set_E_K_LRU01(E_K_LRU01);
  endf_obj.set_F_K_LRU01(F_K_LRU01);

  //Clear declared data
  clr_obj.clear_vec_array2_int(IFG);
  clr_obj.clear_vec_array4_real(DAP_LCOMP01_LRF07);
  clr_obj.clear_vec_array3_int(NJSX_LCOMP01_LRF07);
  clr_obj.clear_vec_array5_real(ER_LCOMP01_LRF07);
  clr_obj.clear_vec_array6_real(GAM_LCOMP01_LRF07);
  clr_obj.clear_vec_array5_real(V_LCOMP01_LRF07);
  clr_obj.clear_vec_array3_int(IDP_LRU01);
  clr_obj.clear_vec_array3_int(LB_LRU01);
  clr_obj.clear_vec_array4_real(E_K_LRU01);
  clr_obj.clear_vec_array5_real(F_K_LRU01);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//MF32MT151Parser -> RMatrixLimitedCovarianceDataContainer
void MF32MT151ConverterRMatrixLimited::convert_endf_format_to_frendy( int& i, int& j,
  MF32MT151Parser& endf_obj, RMatrixLimitedCovarianceDataContainer& frendy_obj )
{
  //Get frendy data
  vector<vector<Real> >                   scat_radius_list_uncertainty = endf_obj.get_DAP_LCOMP01_LRF07()[i][j]; //Actual data name in Parser class is different (DAP_LRF07) 
  vector<Integer>                         j_pi_no                      = endf_obj.get_NJSX_LCOMP01_LRF07()[i][j];
  vector<vector<vector<Real> > >          ene_reso                     = endf_obj.get_ER_LCOMP01_LRF07()[i][j];
  vector<vector<vector<vector<Real> > > > gam_width                    = endf_obj.get_GAM_LCOMP01_LRF07()[i][j];
  vector<vector<vector<Real> > >          cov_matrix_data              = endf_obj.get_V_LCOMP01_LRF07()[i][j]; //Actual data name in Parser class is different (V) 
  vector<Integer>                         reso_parameter_type          = endf_obj.get_IDP_LRU01()[i][j]; //The data name is not found in Parser class.
  vector<Integer>                         cov_pattern_flg              = endf_obj.get_LB_LRU01()[i][j]; //The data name is not found in Parser class.
  vector<vector<Real> >                   cov_table_ene                = endf_obj.get_E_K_LRU01()[i][j]; //The data name is not found in Parser class.
  vector<vector<vector<Real> > >          cov_table_coef               = endf_obj.get_F_K_LRU01()[i][j]; //The data name is not found in Parser class.
  Integer                                 gam_width_flg                = endf_obj.get_IFG()[i][j]; //The data name is not found in Parser class.

  //Set ENDF format data
  frendy_obj.clear();
  frendy_obj.set_scat_radius_list_uncertainty(scat_radius_list_uncertainty); //Actual data name in Parser class is different (DAP_LRF07) 
  frendy_obj.set_j_pi_no(j_pi_no);
  frendy_obj.set_ene_reso(ene_reso);
  frendy_obj.set_gam_width(gam_width);
  frendy_obj.set_cov_matrix_data(cov_matrix_data); //Actual data name in Parser class is different (V) 
  frendy_obj.set_reso_parameter_type(reso_parameter_type);
  frendy_obj.set_cov_pattern_flg(cov_pattern_flg);
  frendy_obj.set_cov_table_ene(cov_table_ene);
  frendy_obj.set_cov_table_coef(cov_table_coef);
  frendy_obj.set_gam_width_flg(gam_width_flg);

  //Clear declared data
  clr_obj.clear_vec_array2_real(scat_radius_list_uncertainty);
  clr_obj.clear_vec_array3_real(ene_reso);
  clr_obj.clear_vec_array4_real(gam_width);
  clr_obj.clear_vec_array3_real(cov_matrix_data);
  j_pi_no.clear();
  reso_parameter_type.clear();
  cov_pattern_flg.clear();
  clr_obj.clear_vec_array2_real(cov_table_ene);
  clr_obj.clear_vec_array3_real(cov_table_coef);
  gam_width_flg                = 0;
}

