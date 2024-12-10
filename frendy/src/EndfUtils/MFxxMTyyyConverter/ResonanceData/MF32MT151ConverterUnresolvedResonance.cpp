#include "EndfUtils/MFxxMTyyyConverter/ResonanceData/MF32MT151ConverterUnresolvedResonance.hpp"

using namespace frendy;

//constructor
MF32MT151ConverterUnresolvedResonance::MF32MT151ConverterUnresolvedResonance(void)
{
}

//destructor
MF32MT151ConverterUnresolvedResonance::~MF32MT151ConverterUnresolvedResonance(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//UnresolvedResonanceCovarianceDataContainer -> MF32MT151Parser
void MF32MT151ConverterUnresolvedResonance::convert_frendy_to_endf_format
  ( int& i, int& i_max, int& j, vector<int>& j_max,
  UnresolvedResonanceCovarianceDataContainer& frendy_obj, MF32MT151Parser& endf_obj )
{
  //Declare ENDF data
  vector<vector<vector<Real> > >          AWRI_LRU02 = endf_obj.get_AWRI_LRU02();
  vector<vector<vector<Integer> > >       L_LRU02    = endf_obj.get_L_LRU02();
  vector<vector<vector<vector<Real> > > > D_LRU02    = endf_obj.get_D_LRU02();
  vector<vector<vector<vector<Real> > > > AJ_LRU02   = endf_obj.get_AJ_LRU02();
  vector<vector<vector<vector<Real> > > > GNO_LRU02  = endf_obj.get_GNO_LRU02();
  vector<vector<vector<vector<Real> > > > GG_LRU02   = endf_obj.get_GG_LRU02();
  vector<vector<vector<vector<Real> > > > GF_LRU02   = endf_obj.get_GF_LRU02();
  vector<vector<vector<vector<Real> > > > GX_LRU02   = endf_obj.get_GX_LRU02();
  vector<vector<Integer> >                MPAR_LRU02 = endf_obj.get_MPAR_LRU02();
  vector<vector<vector<vector<Real> > > > RV_LRU02   = endf_obj.get_RV_LRU02();
   
  //Resize ENDF data
  int ele_no = static_cast<int>(D_LRU02.size());
  if( ele_no == 0 )
  {
    AWRI_LRU02.resize(i_max);
    L_LRU02.resize(i_max);
    D_LRU02.resize(i_max);
    AJ_LRU02.resize(i_max);
    GNO_LRU02.resize(i_max);
    GG_LRU02.resize(i_max);
    GF_LRU02.resize(i_max);
    GX_LRU02.resize(i_max);
    MPAR_LRU02.resize(i_max);
    RV_LRU02.resize(i_max);
    for(int i_tmp=0; i_tmp<i_max; i_tmp++)
    {
      AWRI_LRU02[i_tmp].resize(j_max[i_tmp]);
      L_LRU02[i_tmp].resize(j_max[i_tmp]);
      D_LRU02[i_tmp].resize(j_max[i_tmp]);
      AJ_LRU02[i_tmp].resize(j_max[i_tmp]);
      GNO_LRU02[i_tmp].resize(j_max[i_tmp]);
      GG_LRU02[i_tmp].resize(j_max[i_tmp]);
      GF_LRU02[i_tmp].resize(j_max[i_tmp]);
      GX_LRU02[i_tmp].resize(j_max[i_tmp]);
      MPAR_LRU02[i_tmp].resize(j_max[i_tmp]);
      RV_LRU02[i_tmp].resize(j_max[i_tmp]);
    }
  }
  else
  {
    if( ele_no != i_max )
    {
      string class_name = "MF32MT151ConverterUnresolvedResonance";
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
     
    if( static_cast<int>(AWRI_LRU02[i].size()) != j_max[i] )
    {
      string class_name = "MF32MT151ConverterUnresolvedResonance";
      string func_name  = "convert_frendy_to_endf_format";
      ostringstream oss01, oss02, oss03, oss04;
      oss01 << i;
      oss02 << j;
      oss03 <<  static_cast<int>(AWRI_LRU02[i].size());
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
  AWRI_LRU02[i][j] = frendy_obj.get_mass_isotope(); //Actual data name in Parser class is different (AWRI_NLS) 
  L_LRU02[i][j]    = frendy_obj.get_l_value(); //Actual data name in Parser class is different (L) 
  D_LRU02[i][j]    = frendy_obj.get_level_spacing();
  AJ_LRU02[i][j]   = frendy_obj.get_j_value_abs();
  GNO_LRU02[i][j]  = frendy_obj.get_ave_gam_width_n();
  GG_LRU02[i][j]   = frendy_obj.get_ave_gam_width_rad();
  GF_LRU02[i][j]   = frendy_obj.get_ave_gam_width_fis();
  GX_LRU02[i][j]   = frendy_obj.get_ave_gam_width_comp();
  MPAR_LRU02[i][j] = frendy_obj.get_reso_parameter_no();
  RV_LRU02[i][j]   = frendy_obj.get_relative_cov_value();

  //Set ENDF format data
  //endf_obj.clear();
  endf_obj.set_AWRI_LRU02(AWRI_LRU02); //Actual data name in Parser class is different (AWRI_NLS) 
  endf_obj.set_L_LRU02(L_LRU02); //Actual data name in Parser class is different (L) 
  endf_obj.set_D_LRU02(D_LRU02);
  endf_obj.set_AJ_LRU02(AJ_LRU02);
  endf_obj.set_GNO_LRU02(GNO_LRU02);
  endf_obj.set_GG_LRU02(GG_LRU02);
  endf_obj.set_GF_LRU02(GF_LRU02);
  endf_obj.set_GX_LRU02(GX_LRU02);
  endf_obj.set_MPAR_LRU02(MPAR_LRU02);
  endf_obj.set_RV_LRU02(RV_LRU02);

  //Clear declared data
  clr_obj.clear_vec_array3_real(AWRI_LRU02);
  clr_obj.clear_vec_array3_int(L_LRU02);
  clr_obj.clear_vec_array4_real(D_LRU02);
  clr_obj.clear_vec_array4_real(AJ_LRU02);
  clr_obj.clear_vec_array4_real(GNO_LRU02);
  clr_obj.clear_vec_array4_real(GG_LRU02);
  clr_obj.clear_vec_array4_real(GF_LRU02);
  clr_obj.clear_vec_array4_real(GX_LRU02);
  clr_obj.clear_vec_array2_int(MPAR_LRU02);
  clr_obj.clear_vec_array4_real(RV_LRU02);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//MF32MT151Parser -> UnresolvedResonanceCovarianceDataContainer
void MF32MT151ConverterUnresolvedResonance::convert_endf_format_to_frendy( int& i, int& j,
  MF32MT151Parser& endf_obj, UnresolvedResonanceCovarianceDataContainer& frendy_obj )
{
  //Get frendy data
  vector<Real>          mass_isotope       = endf_obj.get_AWRI_LRU02()[i][j]; //Actual data name in Parser class is different (AWRI_NLS) 
  vector<Integer>       l_value            = endf_obj.get_L_LRU02()[i][j]; //Actual data name in Parser class is different (L) 
  vector<vector<Real> > level_spacing      = endf_obj.get_D_LRU02()[i][j];
  vector<vector<Real> > j_value_abs        = endf_obj.get_AJ_LRU02()[i][j];
  vector<vector<Real> > ave_gam_width_n    = endf_obj.get_GNO_LRU02()[i][j];
  vector<vector<Real> > ave_gam_width_rad  = endf_obj.get_GG_LRU02()[i][j];
  vector<vector<Real> > ave_gam_width_fis  = endf_obj.get_GF_LRU02()[i][j];
  vector<vector<Real> > ave_gam_width_comp = endf_obj.get_GX_LRU02()[i][j];
  Integer               reso_parameter_no  = endf_obj.get_MPAR_LRU02()[i][j];
  vector<vector<Real> > relative_cov_value = endf_obj.get_RV_LRU02()[i][j];

  //Set ENDF format data
  frendy_obj.clear();
  frendy_obj.set_mass_isotope(mass_isotope); //Actual data name in Parser class is different (AWRI_NLS) 
  frendy_obj.set_l_value(l_value); //Actual data name in Parser class is different (L) 
  frendy_obj.set_level_spacing(level_spacing);
  frendy_obj.set_j_value_abs(j_value_abs);
  frendy_obj.set_ave_gam_width_n(ave_gam_width_n);
  frendy_obj.set_ave_gam_width_rad(ave_gam_width_rad);
  frendy_obj.set_ave_gam_width_fis(ave_gam_width_fis);
  frendy_obj.set_ave_gam_width_comp(ave_gam_width_comp);
  frendy_obj.set_reso_parameter_no(reso_parameter_no);
  frendy_obj.set_relative_cov_value(relative_cov_value);

  //Clear declared data
  mass_isotope.clear();
  l_value.clear();
  clr_obj.clear_vec_array2_real(level_spacing);
  clr_obj.clear_vec_array2_real(j_value_abs);
  clr_obj.clear_vec_array2_real(ave_gam_width_n);
  clr_obj.clear_vec_array2_real(ave_gam_width_rad);
  clr_obj.clear_vec_array2_real(ave_gam_width_fis);
  clr_obj.clear_vec_array2_real(ave_gam_width_comp);
  reso_parameter_no  = 0;
  clr_obj.clear_vec_array2_real(relative_cov_value);
}

