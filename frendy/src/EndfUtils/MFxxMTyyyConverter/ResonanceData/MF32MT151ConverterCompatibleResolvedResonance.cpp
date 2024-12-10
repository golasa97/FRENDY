#include "EndfUtils/MFxxMTyyyConverter/ResonanceData/MF32MT151ConverterCompatibleResolvedResonance.hpp"

using namespace frendy;

//constructor
MF32MT151ConverterCompatibleResolvedResonance::MF32MT151ConverterCompatibleResolvedResonance(void)
{
}

//destructor
MF32MT151ConverterCompatibleResolvedResonance::~MF32MT151ConverterCompatibleResolvedResonance(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//CompatibleResolvedResonanceDataContainer -> MF32MT151Parser
void MF32MT151ConverterCompatibleResolvedResonance::convert_frendy_to_endf_format
  ( int& i, int& i_max, int& j, vector<int>& j_max,
  CompatibleResolvedResonanceDataContainer& frendy_obj, MF32MT151Parser& endf_obj )
{
  //Declare ENDF data
  vector<vector<Real> >                   DAP_LCOMP00  = endf_obj.get_DAP_LCOMP00();
  vector<vector<vector<Integer> > >       L_LCOMP00    = endf_obj.get_L_LCOMP00();
  vector<vector<vector<Real> > >          AWRI_LCOMP00 = endf_obj.get_AWRI_LCOMP00();
  vector<vector<vector<vector<Real> > > > ER_LCOMP00   = endf_obj.get_ER_LCOMP00();
  vector<vector<vector<vector<Real> > > > AJ_LCOMP00   = endf_obj.get_AJ_LCOMP00();
  vector<vector<vector<vector<Real> > > > GT_LCOMP00   = endf_obj.get_GT_LCOMP00();
  vector<vector<vector<vector<Real> > > > GN_LCOMP00   = endf_obj.get_GN_LCOMP00();
  vector<vector<vector<vector<Real> > > > GG_LCOMP00   = endf_obj.get_GG_LCOMP00();
  vector<vector<vector<vector<Real> > > > GF_LCOMP00   = endf_obj.get_GF_LCOMP00();
  vector<vector<vector<vector<Real> > > > DE_LCOMP00   = endf_obj.get_DE_LCOMP00();
  vector<vector<vector<vector<Real> > > > DN_LCOMP00   = endf_obj.get_DN_LCOMP00();
  vector<vector<vector<vector<Real> > > > DNDG_LCOMP00 = endf_obj.get_DNDG_LCOMP00();
  vector<vector<vector<vector<Real> > > > DG_LCOMP00   = endf_obj.get_DG_LCOMP00();
  vector<vector<vector<vector<Real> > > > DNDF_LCOMP00 = endf_obj.get_DNDF_LCOMP00();
  vector<vector<vector<vector<Real> > > > DGDF_LCOMP00 = endf_obj.get_DGDF_LCOMP00();
  vector<vector<vector<vector<Real> > > > DF_LCOMP00   = endf_obj.get_DF_LCOMP00();
  vector<vector<vector<vector<Real> > > > DJDN_LCOMP00 = endf_obj.get_DJDN_LCOMP00();
  vector<vector<vector<vector<Real> > > > DJDG_LCOMP00 = endf_obj.get_DJDG_LCOMP00();
  vector<vector<vector<vector<Real> > > > DJDF_LCOMP00 = endf_obj.get_DJDF_LCOMP00();
  vector<vector<vector<vector<Real> > > > DJ_LCOMP00   = endf_obj.get_DJ_LCOMP00();
   
  //Resize ENDF data
  int ele_no = static_cast<int>(ER_LCOMP00.size());
  if( ele_no == 0 )
  {
    DAP_LCOMP00.resize(i_max);
    L_LCOMP00.resize(i_max);
    AWRI_LCOMP00.resize(i_max);
    ER_LCOMP00.resize(i_max);
    AJ_LCOMP00.resize(i_max);
    GT_LCOMP00.resize(i_max);
    GN_LCOMP00.resize(i_max);
    GG_LCOMP00.resize(i_max);
    GF_LCOMP00.resize(i_max);
    DE_LCOMP00.resize(i_max);
    DN_LCOMP00.resize(i_max);
    DNDG_LCOMP00.resize(i_max);
    DG_LCOMP00.resize(i_max);
    DNDF_LCOMP00.resize(i_max);
    DGDF_LCOMP00.resize(i_max);
    DF_LCOMP00.resize(i_max);
    DJDN_LCOMP00.resize(i_max);
    DJDG_LCOMP00.resize(i_max);
    DJDF_LCOMP00.resize(i_max);
    DJ_LCOMP00.resize(i_max);
    for(int i_tmp=0; i_tmp<i_max; i_tmp++)
    {
      DAP_LCOMP00[i_tmp].resize(j_max[i_tmp]);
      L_LCOMP00[i_tmp].resize(j_max[i_tmp]);
      AWRI_LCOMP00[i_tmp].resize(j_max[i_tmp]);
      ER_LCOMP00[i_tmp].resize(j_max[i_tmp]);
      AJ_LCOMP00[i_tmp].resize(j_max[i_tmp]);
      GT_LCOMP00[i_tmp].resize(j_max[i_tmp]);
      GN_LCOMP00[i_tmp].resize(j_max[i_tmp]);
      GG_LCOMP00[i_tmp].resize(j_max[i_tmp]);
      GF_LCOMP00[i_tmp].resize(j_max[i_tmp]);
      DE_LCOMP00[i_tmp].resize(j_max[i_tmp]);
      DN_LCOMP00[i_tmp].resize(j_max[i_tmp]);
      DNDG_LCOMP00[i_tmp].resize(j_max[i_tmp]);
      DG_LCOMP00[i_tmp].resize(j_max[i_tmp]);
      DNDF_LCOMP00[i_tmp].resize(j_max[i_tmp]);
      DGDF_LCOMP00[i_tmp].resize(j_max[i_tmp]);
      DF_LCOMP00[i_tmp].resize(j_max[i_tmp]);
      DJDN_LCOMP00[i_tmp].resize(j_max[i_tmp]);
      DJDG_LCOMP00[i_tmp].resize(j_max[i_tmp]);
      DJDF_LCOMP00[i_tmp].resize(j_max[i_tmp]);
      DJ_LCOMP00[i_tmp].resize(j_max[i_tmp]);
    }
  }
  else
  {
    if( ele_no != i_max )
    {
      string class_name = "MF32MT151ConverterCompatibleResolvedResonance";
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
     
    if( static_cast<int>(DAP_LCOMP00[i].size()) != j_max[i] )
    {
      string class_name = "MF32MT151ConverterCompatibleResolvedResonance";
      string func_name  = "convert_frendy_to_endf_format";
      ostringstream oss01, oss02, oss03, oss04;
      oss01 << i;
      oss02 << j;
      oss03 <<  static_cast<int>(DAP_LCOMP00[i].size());
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
  DAP_LCOMP00[i][j]  = frendy_obj.get_scat_radius_uncertainty(); //Actual data name in Parser class is different (DAP) 
  L_LCOMP00[i][j]    = frendy_obj.get_l_value(); //Actual data name in Parser class is different (L) 
  AWRI_LCOMP00[i][j] = frendy_obj.get_mass_isotope(); //Actual data name in Parser class is different (AWRI_NLS) 
  ER_LCOMP00[i][j]   = frendy_obj.get_ene_reso();
  AJ_LCOMP00[i][j]   = frendy_obj.get_j_value_abs();
  GT_LCOMP00[i][j]   = frendy_obj.get_gam_width_tot();
  GN_LCOMP00[i][j]   = frendy_obj.get_gam_width_n();
  GG_LCOMP00[i][j]   = frendy_obj.get_gam_width_rad();
  GF_LCOMP00[i][j]   = frendy_obj.get_gam_width_fis();
  DE_LCOMP00[i][j]   = frendy_obj.get_ene_reso_variance();
  DN_LCOMP00[i][j]   = frendy_obj.get_gam_width_n_variance();
  DNDG_LCOMP00[i][j] = frendy_obj.get_gam_width_n_rad_cov();
  DG_LCOMP00[i][j]   = frendy_obj.get_gam_width_rad_variance();
  DNDF_LCOMP00[i][j] = frendy_obj.get_gam_width_n_rad_fis();
  DGDF_LCOMP00[i][j] = frendy_obj.get_gam_width_rad_fis_cov();
  DF_LCOMP00[i][j]   = frendy_obj.get_gam_width_fis_variance();
  DJDN_LCOMP00[i][j] = frendy_obj.get_gam_width_n_j_cov();
  DJDG_LCOMP00[i][j] = frendy_obj.get_gam_width_rad_j_cov();
  DJDF_LCOMP00[i][j] = frendy_obj.get_gam_width_fis_j_cov();
  DJ_LCOMP00[i][j]   = frendy_obj.get_j_value_variance();

  //Set ENDF format data
  //endf_obj.clear();
  endf_obj.set_AWRI_LCOMP00(AWRI_LCOMP00); //Actual data name in Parser class is different (AWRI_NLS) 
  endf_obj.set_L_LCOMP00(L_LCOMP00); //Actual data name in Parser class is different (L) 
  endf_obj.set_DAP_LCOMP00(DAP_LCOMP00); //Actual data name in Parser class is different (DAP) 
  endf_obj.set_ER_LCOMP00(ER_LCOMP00);
  endf_obj.set_AJ_LCOMP00(AJ_LCOMP00);
  endf_obj.set_GT_LCOMP00(GT_LCOMP00);
  endf_obj.set_GN_LCOMP00(GN_LCOMP00);
  endf_obj.set_GG_LCOMP00(GG_LCOMP00);
  endf_obj.set_GF_LCOMP00(GF_LCOMP00);
  endf_obj.set_DE_LCOMP00(DE_LCOMP00);
  endf_obj.set_DN_LCOMP00(DN_LCOMP00);
  endf_obj.set_DNDG_LCOMP00(DNDG_LCOMP00);
  endf_obj.set_DG_LCOMP00(DG_LCOMP00);
  endf_obj.set_DNDF_LCOMP00(DNDF_LCOMP00);
  endf_obj.set_DGDF_LCOMP00(DGDF_LCOMP00);
  endf_obj.set_DF_LCOMP00(DF_LCOMP00);
  endf_obj.set_DJDN_LCOMP00(DJDN_LCOMP00);
  endf_obj.set_DJDG_LCOMP00(DJDG_LCOMP00);
  endf_obj.set_DJDF_LCOMP00(DJDF_LCOMP00);
  endf_obj.set_DJ_LCOMP00(DJ_LCOMP00);

  //Clear declared data
  clr_obj.clear_vec_array2_real(DAP_LCOMP00);
  clr_obj.clear_vec_array3_int(L_LCOMP00);
  clr_obj.clear_vec_array3_real(AWRI_LCOMP00);
  clr_obj.clear_vec_array4_real(ER_LCOMP00);
  clr_obj.clear_vec_array4_real(AJ_LCOMP00);
  clr_obj.clear_vec_array4_real(GT_LCOMP00);
  clr_obj.clear_vec_array4_real(GN_LCOMP00);
  clr_obj.clear_vec_array4_real(GG_LCOMP00);
  clr_obj.clear_vec_array4_real(GF_LCOMP00);
  clr_obj.clear_vec_array4_real(DE_LCOMP00);
  clr_obj.clear_vec_array4_real(DN_LCOMP00);
  clr_obj.clear_vec_array4_real(DNDG_LCOMP00);
  clr_obj.clear_vec_array4_real(DG_LCOMP00);
  clr_obj.clear_vec_array4_real(DNDF_LCOMP00);
  clr_obj.clear_vec_array4_real(DGDF_LCOMP00);
  clr_obj.clear_vec_array4_real(DF_LCOMP00);
  clr_obj.clear_vec_array4_real(DJDN_LCOMP00);
  clr_obj.clear_vec_array4_real(DJDG_LCOMP00);
  clr_obj.clear_vec_array4_real(DJDF_LCOMP00);
  clr_obj.clear_vec_array4_real(DJ_LCOMP00);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//MF32MT151Parser -> CompatibleResolvedResonanceDataContainer
void MF32MT151ConverterCompatibleResolvedResonance::convert_endf_format_to_frendy( int& i, int& j,
  MF32MT151Parser& endf_obj, CompatibleResolvedResonanceDataContainer& frendy_obj )
{
  //Get frendy data
  Real                  scat_radius_uncertainty = endf_obj.get_DAP_LCOMP00()[i][j]; //Actual data name in Parser class is different (DAP) 
  vector<Integer>       l_value                 = endf_obj.get_L_LCOMP00()[i][j]; //Actual data name in Parser class is different (L) 
  vector<Real>          mass_isotope            = endf_obj.get_AWRI_LCOMP00()[i][j]; //Actual data name in Parser class is different (AWRI_NLS) 
  vector<vector<Real> > ene_reso                = endf_obj.get_ER_LCOMP00()[i][j];
  vector<vector<Real> > j_value_abs             = endf_obj.get_AJ_LCOMP00()[i][j];
  vector<vector<Real> > gam_width_tot           = endf_obj.get_GT_LCOMP00()[i][j];
  vector<vector<Real> > gam_width_n             = endf_obj.get_GN_LCOMP00()[i][j];
  vector<vector<Real> > gam_width_rad           = endf_obj.get_GG_LCOMP00()[i][j];
  vector<vector<Real> > gam_width_fis           = endf_obj.get_GF_LCOMP00()[i][j];
  vector<vector<Real> > ene_reso_variance       = endf_obj.get_DE_LCOMP00()[i][j];
  vector<vector<Real> > gam_width_n_variance    = endf_obj.get_DN_LCOMP00()[i][j];
  vector<vector<Real> > gam_width_n_rad_cov     = endf_obj.get_DNDG_LCOMP00()[i][j];
  vector<vector<Real> > gam_width_rad_variance  = endf_obj.get_DG_LCOMP00()[i][j];
  vector<vector<Real> > gam_width_n_rad_fis     = endf_obj.get_DNDF_LCOMP00()[i][j];
  vector<vector<Real> > gam_width_rad_fis_cov   = endf_obj.get_DGDF_LCOMP00()[i][j];
  vector<vector<Real> > gam_width_fis_variance  = endf_obj.get_DF_LCOMP00()[i][j];
  vector<vector<Real> > gam_width_n_j_cov       = endf_obj.get_DJDN_LCOMP00()[i][j];
  vector<vector<Real> > gam_width_rad_j_cov     = endf_obj.get_DJDG_LCOMP00()[i][j];
  vector<vector<Real> > gam_width_fis_j_cov     = endf_obj.get_DJDF_LCOMP00()[i][j];
  vector<vector<Real> > j_value_variance        = endf_obj.get_DJ_LCOMP00()[i][j];

  //Set ENDF format data
  frendy_obj.clear();
  frendy_obj.set_mass_isotope(mass_isotope); //Actual data name in Parser class is different (AWRI_NLS) 
  frendy_obj.set_l_value(l_value); //Actual data name in Parser class is different (L) 
  frendy_obj.set_scat_radius_uncertainty(scat_radius_uncertainty); //Actual data name in Parser class is different (DAP) 
  frendy_obj.set_ene_reso(ene_reso);
  frendy_obj.set_j_value_abs(j_value_abs);
  frendy_obj.set_gam_width_tot(gam_width_tot);
  frendy_obj.set_gam_width_n(gam_width_n);
  frendy_obj.set_gam_width_rad(gam_width_rad);
  frendy_obj.set_gam_width_fis(gam_width_fis);
  frendy_obj.set_ene_reso_variance(ene_reso_variance);
  frendy_obj.set_gam_width_n_variance(gam_width_n_variance);
  frendy_obj.set_gam_width_n_rad_cov(gam_width_n_rad_cov);
  frendy_obj.set_gam_width_rad_variance(gam_width_rad_variance);
  frendy_obj.set_gam_width_n_rad_fis(gam_width_n_rad_fis);
  frendy_obj.set_gam_width_rad_fis_cov(gam_width_rad_fis_cov);
  frendy_obj.set_gam_width_fis_variance(gam_width_fis_variance);
  frendy_obj.set_gam_width_n_j_cov(gam_width_n_j_cov);
  frendy_obj.set_gam_width_rad_j_cov(gam_width_rad_j_cov);
  frendy_obj.set_gam_width_fis_j_cov(gam_width_fis_j_cov);
  frendy_obj.set_j_value_variance(j_value_variance);

  //Clear declared data
  scat_radius_uncertainty = 0.0;
  l_value.clear();
  mass_isotope.clear();
  clr_obj.clear_vec_array2_real(ene_reso);
  clr_obj.clear_vec_array2_real(j_value_abs);
  clr_obj.clear_vec_array2_real(gam_width_tot);
  clr_obj.clear_vec_array2_real(gam_width_n);
  clr_obj.clear_vec_array2_real(gam_width_rad);
  clr_obj.clear_vec_array2_real(gam_width_fis);
  clr_obj.clear_vec_array2_real(ene_reso_variance);
  clr_obj.clear_vec_array2_real(gam_width_n_variance);
  clr_obj.clear_vec_array2_real(gam_width_n_rad_cov);
  clr_obj.clear_vec_array2_real(gam_width_rad_variance);
  clr_obj.clear_vec_array2_real(gam_width_n_rad_fis);
  clr_obj.clear_vec_array2_real(gam_width_rad_fis_cov);
  clr_obj.clear_vec_array2_real(gam_width_fis_variance);
  clr_obj.clear_vec_array2_real(gam_width_n_j_cov);
  clr_obj.clear_vec_array2_real(gam_width_rad_j_cov);
  clr_obj.clear_vec_array2_real(gam_width_fis_j_cov);
  clr_obj.clear_vec_array2_real(j_value_variance);
}

