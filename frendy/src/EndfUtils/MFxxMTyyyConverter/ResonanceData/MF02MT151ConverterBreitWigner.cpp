#include "EndfUtils/MFxxMTyyyConverter/ResonanceData/MF02MT151ConverterBreitWigner.hpp"

using namespace frendy;

//constructor
MF02MT151ConverterBreitWigner::MF02MT151ConverterBreitWigner(void)
{
}

//destructor
MF02MT151ConverterBreitWigner::~MF02MT151ConverterBreitWigner(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//BreitWignerDataContainer -> MF02MT151Parser
void MF02MT151ConverterBreitWigner::convert_frendy_to_endf_format
  ( int& i, int& i_max, int& j, vector<int>& j_max,
  BreitWignerDataContainer& frendy_obj, MF02MT151Parser& endf_obj )
{
  //Declare ENDF data
  vector<vector<vector<Real> > >          QX_LRU01_LRF01  = endf_obj.get_QX_LRU01_LRF01();
  vector<vector<vector<Integer> > >       LRX_LRU01_LRF01 = endf_obj.get_LRX_LRU01_LRF01();
  vector<vector<vector<vector<Real> > > > ER_LRU01_LRF01  = endf_obj.get_ER_LRU01_LRF01();
  vector<vector<vector<vector<Real> > > > AJ_LRU01_LRF01  = endf_obj.get_AJ_LRU01_LRF01();
  vector<vector<vector<vector<Real> > > > GT_LRU01_LRF01  = endf_obj.get_GT_LRU01_LRF01();
  vector<vector<vector<vector<Real> > > > GN_LRU01_LRF01  = endf_obj.get_GN_LRU01_LRF01();
  vector<vector<vector<vector<Real> > > > GG_LRU01_LRF01  = endf_obj.get_GG_LRU01_LRF01();
  vector<vector<vector<vector<Real> > > > GF_LRU01_LRF01  = endf_obj.get_GF_LRU01_LRF01();
   
  vector<vector<vector<Integer> > > NRS_LRU01_LRF01 = endf_obj.get_NRS_LRU01_LRF01();
  
  //Resize ENDF data
  int ele_no = static_cast<int>(QX_LRU01_LRF01.size());
  if( ele_no == 0 )
  {
    QX_LRU01_LRF01.resize(i_max);
    LRX_LRU01_LRF01.resize(i_max);
    ER_LRU01_LRF01.resize(i_max);
    AJ_LRU01_LRF01.resize(i_max);
    GT_LRU01_LRF01.resize(i_max);
    GN_LRU01_LRF01.resize(i_max);
    GG_LRU01_LRF01.resize(i_max);
    GF_LRU01_LRF01.resize(i_max);
    NRS_LRU01_LRF01.resize(i_max);
    for(int i_tmp=0; i_tmp<i_max; i_tmp++)
    {
      QX_LRU01_LRF01[i_tmp].resize(j_max[i_tmp]);
      LRX_LRU01_LRF01[i_tmp].resize(j_max[i_tmp]);
      ER_LRU01_LRF01[i_tmp].resize(j_max[i_tmp]);
      AJ_LRU01_LRF01[i_tmp].resize(j_max[i_tmp]);
      GT_LRU01_LRF01[i_tmp].resize(j_max[i_tmp]);
      GN_LRU01_LRF01[i_tmp].resize(j_max[i_tmp]);
      GG_LRU01_LRF01[i_tmp].resize(j_max[i_tmp]);
      GF_LRU01_LRF01[i_tmp].resize(j_max[i_tmp]);
      NRS_LRU01_LRF01[i_tmp].resize(j_max[i_tmp]);
    }
  }
  else
  {
    if( ele_no != i_max )
    {
      string class_name = "MF02MT151ConverterBreitWigner";
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
     
    if( static_cast<int>(QX_LRU01_LRF01[i].size()) != j_max[i] )
    {
      string class_name = "MF02MT151ConverterBreitWigner";
      string func_name  = "convert_frendy_to_endf_format";
      ostringstream oss01, oss02, oss03, oss04;
      oss01 << i;
      oss02 << j;
      oss03 <<  static_cast<int>(QX_LRU01_LRF01[i].size());
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
  QX_LRU01_LRF01[i][j]  = frendy_obj.get_q_value();
  LRX_LRU01_LRF01[i][j] = frendy_obj.get_competitive_width_flg();
  ER_LRU01_LRF01[i][j]  = frendy_obj.get_ene_reso();
  AJ_LRU01_LRF01[i][j]  = frendy_obj.get_j_value_abs();
  GT_LRU01_LRF01[i][j]  = frendy_obj.get_gam_width_tot();
  GN_LRU01_LRF01[i][j]  = frendy_obj.get_gam_width_n();
  GG_LRU01_LRF01[i][j]  = frendy_obj.get_gam_width_rad();
  GF_LRU01_LRF01[i][j]  = frendy_obj.get_gam_width_fis();

  int k_max = static_cast<int>(ER_LRU01_LRF01[i][j].size());
  NRS_LRU01_LRF01[i][j].resize(k_max);
  for(int k=0; k<k_max; k++)
  {
    NRS_LRU01_LRF01[i][j][k] = static_cast<Integer>(ER_LRU01_LRF01[i][j][k].size());
  }
  
  //Set ENDF format data
  //endf_obj.clear();
  endf_obj.set_QX_LRU01_LRF01(QX_LRU01_LRF01);
  //!!! There is no Parser data !!!vector<Integer> L_LRU01_LRF01
  endf_obj.set_LRX_LRU01_LRF01(LRX_LRU01_LRF01);
  endf_obj.set_NRS_LRU01_LRF01(NRS_LRU01_LRF01);
  endf_obj.set_ER_LRU01_LRF01(ER_LRU01_LRF01);
  endf_obj.set_AJ_LRU01_LRF01(AJ_LRU01_LRF01);
  endf_obj.set_GT_LRU01_LRF01(GT_LRU01_LRF01);
  endf_obj.set_GN_LRU01_LRF01(GN_LRU01_LRF01);
  endf_obj.set_GG_LRU01_LRF01(GG_LRU01_LRF01);
  endf_obj.set_GF_LRU01_LRF01(GF_LRU01_LRF01);

  //Clear declared data
  clr_obj.clear_vec_array3_real(QX_LRU01_LRF01);
  clr_obj.clear_vec_array3_int(LRX_LRU01_LRF01);
  clr_obj.clear_vec_array3_int(NRS_LRU01_LRF01);
  clr_obj.clear_vec_array4_real(ER_LRU01_LRF01);
  clr_obj.clear_vec_array4_real(AJ_LRU01_LRF01);
  clr_obj.clear_vec_array4_real(GT_LRU01_LRF01);
  clr_obj.clear_vec_array4_real(GN_LRU01_LRF01);
  clr_obj.clear_vec_array4_real(GG_LRU01_LRF01);
  clr_obj.clear_vec_array4_real(GF_LRU01_LRF01);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//MF02MT151Parser -> BreitWignerDataContainer
void MF02MT151ConverterBreitWigner::convert_endf_format_to_frendy( int& i, int& j,
  MF02MT151Parser& endf_obj, BreitWignerDataContainer& frendy_obj )
{
  //Get frendy data
  vector<Real>          q_value               = endf_obj.get_QX_LRU01_LRF01()[i][j];
  vector<Integer>       competitive_width_flg = endf_obj.get_LRX_LRU01_LRF01()[i][j];
  vector<vector<Real> > ene_reso              = endf_obj.get_ER_LRU01_LRF01()[i][j];
  vector<vector<Real> > j_value_abs           = endf_obj.get_AJ_LRU01_LRF01()[i][j];
  vector<vector<Real> > gam_width_tot         = endf_obj.get_GT_LRU01_LRF01()[i][j];
  vector<vector<Real> > gam_width_n           = endf_obj.get_GN_LRU01_LRF01()[i][j];
  vector<vector<Real> > gam_width_rad         = endf_obj.get_GG_LRU01_LRF01()[i][j];
  vector<vector<Real> > gam_width_fis         = endf_obj.get_GF_LRU01_LRF01()[i][j];

  //Set ENDF format data
  frendy_obj.clear();
  frendy_obj.set_q_value(q_value);
  //!!! This Parser data is not contained in the Container class !!! //vector<Integer> L_LRU01_LRF01
  frendy_obj.set_competitive_width_flg(competitive_width_flg);
  frendy_obj.set_ene_reso(ene_reso);
  frendy_obj.set_j_value_abs(j_value_abs);
  frendy_obj.set_gam_width_tot(gam_width_tot);
  frendy_obj.set_gam_width_n(gam_width_n);
  frendy_obj.set_gam_width_rad(gam_width_rad);
  frendy_obj.set_gam_width_fis(gam_width_fis);

  //Clear declared data
  q_value.clear();
  competitive_width_flg.clear();
  clr_obj.clear_vec_array2_real(ene_reso);
  clr_obj.clear_vec_array2_real(j_value_abs);
  clr_obj.clear_vec_array2_real(gam_width_tot);
  clr_obj.clear_vec_array2_real(gam_width_n);
  clr_obj.clear_vec_array2_real(gam_width_rad);
  clr_obj.clear_vec_array2_real(gam_width_fis);
}

