#include "EndfUtils/MFxxMTyyyConverter/ResonanceData/MF32MT151ConverterAdlerAdler.hpp"

using namespace frendy;

//constructor
MF32MT151ConverterAdlerAdler::MF32MT151ConverterAdlerAdler(void)
{
}

//destructor
MF32MT151ConverterAdlerAdler::~MF32MT151ConverterAdlerAdler(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//AdlerAdlerCovarianceDataContainer -> MF32MT151Parser
void MF32MT151ConverterAdlerAdler::convert_frendy_to_endf_format
  ( int& i, int& i_max, int& j, vector<int>& j_max,
  AdlerAdlerCovarianceDataContainer& frendy_obj, MF32MT151Parser& endf_obj )
{
  //Declare ENDF data
  vector<vector<Real> >                            DAP_LCOMP01_LRF04 = endf_obj.get_DAP_LCOMP01_LRF04();
  vector<vector<vector<vector<Real> > > >          DET_LCOMP01_LRF04 = endf_obj.get_DET_LCOMP01_LRF04();
  vector<vector<vector<vector<Real> > > >          DEF_LCOMP01_LRF04 = endf_obj.get_DEF_LCOMP01_LRF04();
  vector<vector<vector<vector<Real> > > >          DEC_LCOMP01_LRF04 = endf_obj.get_DEC_LCOMP01_LRF04();
  vector<vector<vector<vector<Real> > > >          DWT_LCOMP01_LRF04 = endf_obj.get_DWT_LCOMP01_LRF04();
  vector<vector<vector<vector<Real> > > >          DWF_LCOMP01_LRF04 = endf_obj.get_DWF_LCOMP01_LRF04();
  vector<vector<vector<vector<Real> > > >          DWC_LCOMP01_LRF04 = endf_obj.get_DWC_LCOMP01_LRF04();
  vector<vector<vector<vector<Real> > > >          GRT_LCOMP01_LRF04 = endf_obj.get_GRT_LCOMP01_LRF04();
  vector<vector<vector<vector<Real> > > >          GIT_LCOMP01_LRF04 = endf_obj.get_GIT_LCOMP01_LRF04();
  vector<vector<vector<vector<Real> > > >          GRF_LCOMP01_LRF04 = endf_obj.get_GRF_LCOMP01_LRF04();
  vector<vector<vector<vector<Real> > > >          GIF_LCOMP01_LRF04 = endf_obj.get_GIF_LCOMP01_LRF04();
  vector<vector<vector<vector<Real> > > >          GRC_LCOMP01_LRF04 = endf_obj.get_GRC_LCOMP01_LRF04();
  vector<vector<vector<vector<Real> > > >          GIC_LCOMP01_LRF04 = endf_obj.get_GIC_LCOMP01_LRF04();
  vector<vector<vector<vector<vector<Real> > > > > V_LCOMP01_LRF04   = endf_obj.get_V_LCOMP01_LRF04();
  vector<vector<vector<Integer> > >                IDP_LRU01         = endf_obj.get_IDP_LRU01();
  vector<vector<vector<Integer> > >                LB_LRU01          = endf_obj.get_LB_LRU01();
  vector<vector<vector<vector<Real> > > >          E_K_LRU01         = endf_obj.get_E_K_LRU01();
  vector<vector<vector<vector<vector<Real> > > > > F_K_LRU01         = endf_obj.get_F_K_LRU01();
   
  vector<vector<Integer> >          NSRS_LCOMP01_LRF04 = endf_obj.get_NSRS_LCOMP01_LRF04();
  vector<vector<Integer> >          NLRS_LCOMP01_LRF04 = endf_obj.get_NLRS_LCOMP01_LRF04();
  vector<vector<vector<Integer> > > MPAR_LCOMP01_LRF04 = endf_obj.get_MPAR_LCOMP01_LRF04();
  
  //Resize ENDF data
  int ele_no = static_cast<int>(DET_LCOMP01_LRF04.size());
  if( ele_no == 0 )
  {
    DAP_LCOMP01_LRF04.resize(i_max);
    DET_LCOMP01_LRF04.resize(i_max);
    DEF_LCOMP01_LRF04.resize(i_max);
    DEC_LCOMP01_LRF04.resize(i_max);
    DWT_LCOMP01_LRF04.resize(i_max);
    DWF_LCOMP01_LRF04.resize(i_max);
    DWC_LCOMP01_LRF04.resize(i_max);
    GRT_LCOMP01_LRF04.resize(i_max);
    GIT_LCOMP01_LRF04.resize(i_max);
    GRF_LCOMP01_LRF04.resize(i_max);
    GIF_LCOMP01_LRF04.resize(i_max);
    GRC_LCOMP01_LRF04.resize(i_max);
    GIC_LCOMP01_LRF04.resize(i_max);
    V_LCOMP01_LRF04.resize(i_max);
    IDP_LRU01.resize(i_max);
    LB_LRU01.resize(i_max);
    E_K_LRU01.resize(i_max);
    F_K_LRU01.resize(i_max);
    NSRS_LCOMP01_LRF04.resize(i_max);
    NLRS_LCOMP01_LRF04.resize(i_max);
    MPAR_LCOMP01_LRF04.resize(i_max);
    for(int i_tmp=0; i_tmp<i_max; i_tmp++)
    {
      DAP_LCOMP01_LRF04[i_tmp].resize(j_max[i_tmp]);
      DET_LCOMP01_LRF04[i_tmp].resize(j_max[i_tmp]);
      DEF_LCOMP01_LRF04[i_tmp].resize(j_max[i_tmp]);
      DEC_LCOMP01_LRF04[i_tmp].resize(j_max[i_tmp]);
      DWT_LCOMP01_LRF04[i_tmp].resize(j_max[i_tmp]);
      DWF_LCOMP01_LRF04[i_tmp].resize(j_max[i_tmp]);
      DWC_LCOMP01_LRF04[i_tmp].resize(j_max[i_tmp]);
      GRT_LCOMP01_LRF04[i_tmp].resize(j_max[i_tmp]);
      GIT_LCOMP01_LRF04[i_tmp].resize(j_max[i_tmp]);
      GRF_LCOMP01_LRF04[i_tmp].resize(j_max[i_tmp]);
      GIF_LCOMP01_LRF04[i_tmp].resize(j_max[i_tmp]);
      GRC_LCOMP01_LRF04[i_tmp].resize(j_max[i_tmp]);
      GIC_LCOMP01_LRF04[i_tmp].resize(j_max[i_tmp]);
      V_LCOMP01_LRF04[i_tmp].resize(j_max[i_tmp]);
      IDP_LRU01[i_tmp].resize(j_max[i_tmp]);
      LB_LRU01[i_tmp].resize(j_max[i_tmp]);
      E_K_LRU01[i_tmp].resize(j_max[i_tmp]);
      F_K_LRU01[i_tmp].resize(j_max[i_tmp]);
      NSRS_LCOMP01_LRF04[i_tmp].resize(j_max[i_tmp]);
      NLRS_LCOMP01_LRF04[i_tmp].resize(j_max[i_tmp]);
      MPAR_LCOMP01_LRF04[i_tmp].resize(j_max[i_tmp]);
    }
  }
  else
  {
    if( ele_no != i_max )
    {
      string class_name = "MF32MT151ConverterAdlerAdler";
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
     
    if( static_cast<int>(DAP_LCOMP01_LRF04[i].size()) != j_max[i] )
    {
      string class_name = "MF32MT151ConverterAdlerAdler";
      string func_name  = "convert_frendy_to_endf_format";
      ostringstream oss01, oss02, oss03, oss04;
      oss01 << i;
      oss02 << j;
      oss03 <<  static_cast<int>(DAP_LCOMP01_LRF04[i].size());
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
  DAP_LCOMP01_LRF04[i][j] = frendy_obj.get_scat_radius_uncertainty(); //Actual data name in Parser class is different (DAP) 
  DET_LCOMP01_LRF04[i][j] = frendy_obj.get_ene_reso_tot();
  DEF_LCOMP01_LRF04[i][j] = frendy_obj.get_ene_reso_fis();
  DEC_LCOMP01_LRF04[i][j] = frendy_obj.get_ene_reso_rad();
  DWT_LCOMP01_LRF04[i][j] = frendy_obj.get_gam_width_half_tot();
  DWF_LCOMP01_LRF04[i][j] = frendy_obj.get_gam_width_half_fis();
  DWC_LCOMP01_LRF04[i][j] = frendy_obj.get_gam_width_half_rad();
  GRT_LCOMP01_LRF04[i][j] = frendy_obj.get_symmetrical_data_tot();
  GIT_LCOMP01_LRF04[i][j] = frendy_obj.get_non_symmetrical_data_tot();
  GRF_LCOMP01_LRF04[i][j] = frendy_obj.get_symmetrical_data_fis();
  GIF_LCOMP01_LRF04[i][j] = frendy_obj.get_non_symmetrical_data_fis();
  GRC_LCOMP01_LRF04[i][j] = frendy_obj.get_symmetrical_data_rad();
  GIC_LCOMP01_LRF04[i][j] = frendy_obj.get_non_symmetrical_data_rad();
  V_LCOMP01_LRF04[i][j]   = frendy_obj.get_cov_matrix_data(); //Actual data name in Parser class is different (V) 
  IDP_LRU01[i][j]         = frendy_obj.get_reso_parameter_type();
  LB_LRU01[i][j]          = frendy_obj.get_cov_pattern_flg();
  E_K_LRU01[i][j]         = frendy_obj.get_cov_table_ene();
  F_K_LRU01[i][j]         = frendy_obj.get_cov_table_coef();

  NSRS_LCOMP01_LRF04[i][j] = static_cast<Integer>(DET_LCOMP01_LRF04[i][j].size());
  NLRS_LCOMP01_LRF04[i][j] = static_cast<Integer>(IDP_LRU01[i][j].size());

  int k_max = static_cast<int>(NSRS_LCOMP01_LRF04[i][j]);
  MPAR_LCOMP01_LRF04[i][j].resize(k_max);
  for(int k=0; k<k_max; k++)
  {
    Integer l_max = static_cast<Integer>(DET_LCOMP01_LRF04[i][j][k].size());
    Integer v_max = static_cast<Integer>(V_LCOMP01_LRF04[i][j][k].size());
    MPAR_LCOMP01_LRF04[i][j][k] = v_max / l_max;
  }

  //Set ENDF format data
  //endf_obj.clear();
  endf_obj.set_NSRS_LCOMP01_LRF04(NSRS_LCOMP01_LRF04);
  endf_obj.set_NLRS_LCOMP01_LRF04(NLRS_LCOMP01_LRF04);
  endf_obj.set_DAP_LCOMP01_LRF04(DAP_LCOMP01_LRF04); //Actual data name in Parser class is different (DAP) 
  endf_obj.set_MPAR_LCOMP01_LRF04(MPAR_LCOMP01_LRF04); //Actual data name in Parser class is different (MPAR_LCOMP01_LRF01) 
  endf_obj.set_DET_LCOMP01_LRF04(DET_LCOMP01_LRF04);
  endf_obj.set_DWT_LCOMP01_LRF04(DWT_LCOMP01_LRF04);
  endf_obj.set_GRT_LCOMP01_LRF04(GRT_LCOMP01_LRF04);
  endf_obj.set_GIT_LCOMP01_LRF04(GIT_LCOMP01_LRF04);
  endf_obj.set_DEF_LCOMP01_LRF04(DEF_LCOMP01_LRF04);
  endf_obj.set_DWF_LCOMP01_LRF04(DWF_LCOMP01_LRF04);
  endf_obj.set_GRF_LCOMP01_LRF04(GRF_LCOMP01_LRF04);
  endf_obj.set_GIF_LCOMP01_LRF04(GIF_LCOMP01_LRF04);
  endf_obj.set_DEC_LCOMP01_LRF04(DEC_LCOMP01_LRF04);
  endf_obj.set_DWC_LCOMP01_LRF04(DWC_LCOMP01_LRF04);
  endf_obj.set_GRC_LCOMP01_LRF04(GRC_LCOMP01_LRF04);
  endf_obj.set_GIC_LCOMP01_LRF04(GIC_LCOMP01_LRF04);
  endf_obj.set_V_LCOMP01_LRF04(V_LCOMP01_LRF04); //Actual data name in Parser class is different (V) 
  endf_obj.set_IDP_LRU01(IDP_LRU01);
  endf_obj.set_LB_LRU01(LB_LRU01);
  endf_obj.set_E_K_LRU01(E_K_LRU01);
  endf_obj.set_F_K_LRU01(F_K_LRU01);

  //Clear declared data
  clr_obj.clear_vec_array2_real(DAP_LCOMP01_LRF04);
  clr_obj.clear_vec_array4_real(DET_LCOMP01_LRF04);
  clr_obj.clear_vec_array4_real(DEF_LCOMP01_LRF04);
  clr_obj.clear_vec_array4_real(DEC_LCOMP01_LRF04);
  clr_obj.clear_vec_array4_real(DWT_LCOMP01_LRF04);
  clr_obj.clear_vec_array4_real(DWF_LCOMP01_LRF04);
  clr_obj.clear_vec_array4_real(DWC_LCOMP01_LRF04);
  clr_obj.clear_vec_array4_real(GRT_LCOMP01_LRF04);
  clr_obj.clear_vec_array4_real(GIT_LCOMP01_LRF04);
  clr_obj.clear_vec_array4_real(GRF_LCOMP01_LRF04);
  clr_obj.clear_vec_array4_real(GIF_LCOMP01_LRF04);
  clr_obj.clear_vec_array4_real(GRC_LCOMP01_LRF04);
  clr_obj.clear_vec_array4_real(GIC_LCOMP01_LRF04);
  clr_obj.clear_vec_array5_real(V_LCOMP01_LRF04);
  clr_obj.clear_vec_array3_int(IDP_LRU01);
  clr_obj.clear_vec_array3_int(LB_LRU01);
  clr_obj.clear_vec_array4_real(E_K_LRU01);
  clr_obj.clear_vec_array5_real(F_K_LRU01);
  
  clr_obj.clear_vec_array2_int(NSRS_LCOMP01_LRF04);
  clr_obj.clear_vec_array2_int(NLRS_LCOMP01_LRF04);
  clr_obj.clear_vec_array3_int(MPAR_LCOMP01_LRF04);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//MF32MT151Parser -> AdlerAdlerCovarianceDataContainer
void MF32MT151ConverterAdlerAdler::convert_endf_format_to_frendy( int& i, int& j,
  MF32MT151Parser& endf_obj, AdlerAdlerCovarianceDataContainer& frendy_obj )
{
  //Get frendy data
  Real                           scat_radius_uncertainty  = endf_obj.get_DAP_LCOMP01_LRF04()[i][j]; //Actual data name in Parser class is different (DAP) 
  vector<vector<Real> >          ene_reso_tot             = endf_obj.get_DET_LCOMP01_LRF04()[i][j];
  vector<vector<Real> >          ene_reso_fis             = endf_obj.get_DEF_LCOMP01_LRF04()[i][j];
  vector<vector<Real> >          ene_reso_rad             = endf_obj.get_DEC_LCOMP01_LRF04()[i][j];
  vector<vector<Real> >          gam_width_half_tot       = endf_obj.get_DWT_LCOMP01_LRF04()[i][j];
  vector<vector<Real> >          gam_width_half_fis       = endf_obj.get_DWF_LCOMP01_LRF04()[i][j];
  vector<vector<Real> >          gam_width_half_rad       = endf_obj.get_DWC_LCOMP01_LRF04()[i][j];
  vector<vector<Real> >          symmetrical_data_tot     = endf_obj.get_GRT_LCOMP01_LRF04()[i][j];
  vector<vector<Real> >          non_symmetrical_data_tot = endf_obj.get_GIT_LCOMP01_LRF04()[i][j];
  vector<vector<Real> >          symmetrical_data_fis     = endf_obj.get_GRF_LCOMP01_LRF04()[i][j];
  vector<vector<Real> >          non_symmetrical_data_fis = endf_obj.get_GIF_LCOMP01_LRF04()[i][j];
  vector<vector<Real> >          symmetrical_data_rad     = endf_obj.get_GRC_LCOMP01_LRF04()[i][j];
  vector<vector<Real> >          non_symmetrical_data_rad = endf_obj.get_GIC_LCOMP01_LRF04()[i][j];
  vector<vector<vector<Real> > > cov_matrix_data          = endf_obj.get_V_LCOMP01_LRF04()[i][j]; //Actual data name in Parser class is different (V) 
  vector<Integer>                reso_parameter_type      = endf_obj.get_IDP_LRU01()[i][j];
  vector<Integer>                cov_pattern_flg          = endf_obj.get_LB_LRU01()[i][j];
  vector<vector<Real> >          cov_table_ene            = endf_obj.get_E_K_LRU01()[i][j];
  vector<vector<vector<Real> > > cov_table_coef           = endf_obj.get_F_K_LRU01()[i][j];

  //Set ENDF format data
  frendy_obj.clear();
  frendy_obj.set_scat_radius_uncertainty(scat_radius_uncertainty); //Actual data name in Parser class is different (DAP) 
  frendy_obj.set_ene_reso_tot(ene_reso_tot);
  frendy_obj.set_gam_width_half_tot(gam_width_half_tot);
  frendy_obj.set_symmetrical_data_tot(symmetrical_data_tot);
  frendy_obj.set_non_symmetrical_data_tot(non_symmetrical_data_tot);
  frendy_obj.set_ene_reso_fis(ene_reso_fis);
  frendy_obj.set_gam_width_half_fis(gam_width_half_fis);
  frendy_obj.set_symmetrical_data_fis(symmetrical_data_fis);
  frendy_obj.set_non_symmetrical_data_fis(non_symmetrical_data_fis);
  frendy_obj.set_ene_reso_rad(ene_reso_rad);
  frendy_obj.set_gam_width_half_rad(gam_width_half_rad);
  frendy_obj.set_symmetrical_data_rad(symmetrical_data_rad);
  frendy_obj.set_non_symmetrical_data_rad(non_symmetrical_data_rad);
  frendy_obj.set_cov_matrix_data(cov_matrix_data); //Actual data name in Parser class is different (V) 
  frendy_obj.set_reso_parameter_type(reso_parameter_type);
  frendy_obj.set_cov_pattern_flg(cov_pattern_flg);
  frendy_obj.set_cov_table_ene(cov_table_ene);
  frendy_obj.set_cov_table_coef(cov_table_coef);

  //Clear declared data
  scat_radius_uncertainty  = 0.0;
  clr_obj.clear_vec_array2_real(ene_reso_tot);
  clr_obj.clear_vec_array2_real(ene_reso_fis);
  clr_obj.clear_vec_array2_real(ene_reso_rad);
  clr_obj.clear_vec_array2_real(gam_width_half_tot);
  clr_obj.clear_vec_array2_real(gam_width_half_fis);
  clr_obj.clear_vec_array2_real(gam_width_half_rad);
  clr_obj.clear_vec_array2_real(symmetrical_data_tot);
  clr_obj.clear_vec_array2_real(non_symmetrical_data_tot);
  clr_obj.clear_vec_array2_real(symmetrical_data_fis);
  clr_obj.clear_vec_array2_real(non_symmetrical_data_fis);
  clr_obj.clear_vec_array2_real(symmetrical_data_rad);
  clr_obj.clear_vec_array2_real(non_symmetrical_data_rad);
  clr_obj.clear_vec_array3_real(cov_matrix_data);
  reso_parameter_type.clear();
  cov_pattern_flg.clear();
  clr_obj.clear_vec_array2_real(cov_table_ene);
  clr_obj.clear_vec_array3_real(cov_table_coef);
}

