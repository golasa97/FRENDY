#include "EndfUtils/MFxxMTyyyConverter/ResonanceData/MF02MT151ConverterReichMoore.hpp"

using namespace frendy;

//constructor
MF02MT151ConverterReichMoore::MF02MT151ConverterReichMoore(void)
{
}

//destructor
MF02MT151ConverterReichMoore::~MF02MT151ConverterReichMoore(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//ReichMooreDataContainer -> MF02MT151Parser
void MF02MT151ConverterReichMoore::convert_frendy_to_endf_format
  ( int& i, int& i_max, int& j, vector<int>& j_max,
  ReichMooreDataContainer& frendy_obj, MF02MT151Parser& endf_obj )
{
  //Declare ENDF data
  vector<vector<Integer> >                LAD_LRU01_LRF03  = endf_obj.get_LAD_LRU01_LRF03();
  vector<vector<Integer> >                NLSC_LRU01_LRF03 = endf_obj.get_NLSC_LRU01_LRF03();
  vector<vector<vector<Real> > >          APL_LRU01_LRF03  = endf_obj.get_APL_LRU01_LRF03();
  vector<vector<vector<vector<Real> > > > ER_LRU01_LRF03   = endf_obj.get_ER_LRU01_LRF03();
  vector<vector<vector<vector<Real> > > > AJ_LRU01_LRF03   = endf_obj.get_AJ_LRU01_LRF03();
  vector<vector<vector<vector<Real> > > > GN_LRU01_LRF03   = endf_obj.get_GN_LRU01_LRF03();
  vector<vector<vector<vector<Real> > > > GG_LRU01_LRF03   = endf_obj.get_GG_LRU01_LRF03();
  vector<vector<vector<vector<Real> > > > GFA_LRU01_LRF03  = endf_obj.get_GFA_LRU01_LRF03();
  vector<vector<vector<vector<Real> > > > GFB_LRU01_LRF03  = endf_obj.get_GFB_LRU01_LRF03();
  
  vector<vector<vector<Integer> > > NRS_LRU01_LRF03 = endf_obj.get_NRS_LRU01_LRF03();
   
  //Resize ENDF data
  int ele_no = static_cast<int>(LAD_LRU01_LRF03.size());
  if( ele_no == 0 )
  {
    LAD_LRU01_LRF03.resize(i_max);
    NLSC_LRU01_LRF03.resize(i_max);
    APL_LRU01_LRF03.resize(i_max);
    ER_LRU01_LRF03.resize(i_max);
    AJ_LRU01_LRF03.resize(i_max);
    GN_LRU01_LRF03.resize(i_max);
    GG_LRU01_LRF03.resize(i_max);
    GFA_LRU01_LRF03.resize(i_max);
    GFB_LRU01_LRF03.resize(i_max);
    NRS_LRU01_LRF03.resize(i_max);
    for(int i_tmp=0; i_tmp<i_max; i_tmp++)
    {
      LAD_LRU01_LRF03[i_tmp].resize(j_max[i_tmp]);
      NLSC_LRU01_LRF03[i_tmp].resize(j_max[i_tmp]);
      APL_LRU01_LRF03[i_tmp].resize(j_max[i_tmp]);
      ER_LRU01_LRF03[i_tmp].resize(j_max[i_tmp]);
      AJ_LRU01_LRF03[i_tmp].resize(j_max[i_tmp]);
      GN_LRU01_LRF03[i_tmp].resize(j_max[i_tmp]);
      GG_LRU01_LRF03[i_tmp].resize(j_max[i_tmp]);
      GFA_LRU01_LRF03[i_tmp].resize(j_max[i_tmp]);
      GFB_LRU01_LRF03[i_tmp].resize(j_max[i_tmp]);
      NRS_LRU01_LRF03[i_tmp].resize(j_max[i_tmp]);
    }
  }
  else
  {
    if( ele_no != i_max )
    {
      string class_name = "MF02MT151ConverterReichMoore";
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
     
    if( static_cast<int>(LAD_LRU01_LRF03[i].size()) != j_max[i] )
    {
      string class_name = "MF02MT151ConverterReichMoore";
      string func_name  = "convert_frendy_to_endf_format";
      ostringstream oss01, oss02, oss03, oss04;
      oss01 << i;
      oss02 << j;
      oss03 <<  static_cast<int>(LAD_LRU01_LRF03[i].size());
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
  LAD_LRU01_LRF03[i][j]  = frendy_obj.get_angular_distr_calc_flg();
  NLSC_LRU01_LRF03[i][j] = frendy_obj.get_l_no_conv_calc();
  APL_LRU01_LRF03[i][j]  = frendy_obj.get_scat_radius_l();
  ER_LRU01_LRF03[i][j]   = frendy_obj.get_ene_reso();
  AJ_LRU01_LRF03[i][j]   = frendy_obj.get_j_value_abs();
  GN_LRU01_LRF03[i][j]   = frendy_obj.get_gam_width_n();
  GG_LRU01_LRF03[i][j]   = frendy_obj.get_gam_width_rad();
  GFA_LRU01_LRF03[i][j]  = frendy_obj.get_gam_width_fis_a();
  GFB_LRU01_LRF03[i][j]  = frendy_obj.get_gam_width_fis_b();

  int k_max = static_cast<int>(ER_LRU01_LRF03[i][j].size());
  NRS_LRU01_LRF03[i][j].resize(k_max);
  for(int k=0; k<k_max; k++)
  {
    NRS_LRU01_LRF03[i][j][k] = static_cast<Integer>(ER_LRU01_LRF03[i][j][k].size());
  }

  //Set ENDF format data
  //endf_obj.clear();
  endf_obj.set_LAD_LRU01_LRF03(LAD_LRU01_LRF03);
  endf_obj.set_NLSC_LRU01_LRF03(NLSC_LRU01_LRF03);
  endf_obj.set_APL_LRU01_LRF03(APL_LRU01_LRF03);
  //!!! There is no Parser data !!!vector<Integer> L_LRU01_LRF03
  endf_obj.set_NRS_LRU01_LRF03(NRS_LRU01_LRF03);
  endf_obj.set_ER_LRU01_LRF03(ER_LRU01_LRF03);
  endf_obj.set_AJ_LRU01_LRF03(AJ_LRU01_LRF03);
  endf_obj.set_GN_LRU01_LRF03(GN_LRU01_LRF03);
  endf_obj.set_GG_LRU01_LRF03(GG_LRU01_LRF03);
  endf_obj.set_GFA_LRU01_LRF03(GFA_LRU01_LRF03);
  endf_obj.set_GFB_LRU01_LRF03(GFB_LRU01_LRF03);

  //Clear declared data
  clr_obj.clear_vec_array2_int(LAD_LRU01_LRF03);
  clr_obj.clear_vec_array2_int(NLSC_LRU01_LRF03);
  clr_obj.clear_vec_array3_int(NRS_LRU01_LRF03);
  clr_obj.clear_vec_array3_real(APL_LRU01_LRF03);
  clr_obj.clear_vec_array4_real(ER_LRU01_LRF03);
  clr_obj.clear_vec_array4_real(AJ_LRU01_LRF03);
  clr_obj.clear_vec_array4_real(GN_LRU01_LRF03);
  clr_obj.clear_vec_array4_real(GG_LRU01_LRF03);
  clr_obj.clear_vec_array4_real(GFA_LRU01_LRF03);
  clr_obj.clear_vec_array4_real(GFB_LRU01_LRF03);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//MF02MT151Parser -> ReichMooreDataContainer
void MF02MT151ConverterReichMoore::convert_endf_format_to_frendy( int& i, int& j,
  MF02MT151Parser& endf_obj, ReichMooreDataContainer& frendy_obj )
{
  //Get frendy data
  Integer               angular_distr_calc_flg = endf_obj.get_LAD_LRU01_LRF03()[i][j];
  Integer               l_no_conv_calc         = endf_obj.get_NLSC_LRU01_LRF03()[i][j];
  vector<Real>          scat_radius_l          = endf_obj.get_APL_LRU01_LRF03()[i][j];
  vector<vector<Real> > ene_reso               = endf_obj.get_ER_LRU01_LRF03()[i][j];
  vector<vector<Real> > j_value_abs            = endf_obj.get_AJ_LRU01_LRF03()[i][j];
  vector<vector<Real> > gam_width_n            = endf_obj.get_GN_LRU01_LRF03()[i][j];
  vector<vector<Real> > gam_width_rad          = endf_obj.get_GG_LRU01_LRF03()[i][j];
  vector<vector<Real> > gam_width_fis_a        = endf_obj.get_GFA_LRU01_LRF03()[i][j];
  vector<vector<Real> > gam_width_fis_b        = endf_obj.get_GFB_LRU01_LRF03()[i][j];

  //Set ENDF format data
  frendy_obj.clear();
  frendy_obj.set_angular_distr_calc_flg(angular_distr_calc_flg);
  frendy_obj.set_l_no_conv_calc(l_no_conv_calc);
  frendy_obj.set_scat_radius_l(scat_radius_l);
  //!!! This Parser data is not contained in the Container class !!! //vector<Integer> L_LRU01_LRF03
  frendy_obj.set_ene_reso(ene_reso);
  frendy_obj.set_j_value_abs(j_value_abs);
  frendy_obj.set_gam_width_n(gam_width_n);
  frendy_obj.set_gam_width_rad(gam_width_rad);
  frendy_obj.set_gam_width_fis_a(gam_width_fis_a);
  frendy_obj.set_gam_width_fis_b(gam_width_fis_b);

  //Clear declared data
  angular_distr_calc_flg = 0;
  l_no_conv_calc         = 0;
  scat_radius_l.clear();
  clr_obj.clear_vec_array2_real(ene_reso);
  clr_obj.clear_vec_array2_real(j_value_abs);
  clr_obj.clear_vec_array2_real(gam_width_n);
  clr_obj.clear_vec_array2_real(gam_width_rad);
  clr_obj.clear_vec_array2_real(gam_width_fis_a);
  clr_obj.clear_vec_array2_real(gam_width_fis_b);
}

