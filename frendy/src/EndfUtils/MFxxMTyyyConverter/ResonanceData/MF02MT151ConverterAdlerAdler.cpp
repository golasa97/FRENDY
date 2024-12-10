#include "EndfUtils/MFxxMTyyyConverter/ResonanceData/MF02MT151ConverterAdlerAdler.hpp"

using namespace frendy;

//constructor
MF02MT151ConverterAdlerAdler::MF02MT151ConverterAdlerAdler(void)
{
}

//destructor
MF02MT151ConverterAdlerAdler::~MF02MT151ConverterAdlerAdler(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//AdlerAdlerDataContainer -> MF02MT151Parser
void MF02MT151ConverterAdlerAdler::convert_frendy_to_endf_format
  ( int& i, int& i_max, int& j, vector<int>& j_max,
  AdlerAdlerDataContainer& frendy_obj, MF02MT151Parser& endf_obj )
{
  //Declare ENDF data
  vector<vector<Integer> >                         LI_LRU01_LRF04  = endf_obj.get_LI_LRU01_LRF04();
  vector<vector<vector<Real> > >                   AT_LRU01_LRF04  = endf_obj.get_AT_LRU01_LRF04();
  vector<vector<vector<Real> > >                   AF_LRU01_LRF04  = endf_obj.get_AF_LRU01_LRF04();
  vector<vector<vector<Real> > >                   AC_LRU01_LRF04  = endf_obj.get_AC_LRU01_LRF04();
  vector<vector<vector<vector<Real> > > >          AJ_LRU01_LRF04  = endf_obj.get_AJ_LRU01_LRF04();
  vector<vector<vector<vector<vector<Real> > > > > DET_LRU01_LRF04 = endf_obj.get_DET_LRU01_LRF04();
  vector<vector<vector<vector<vector<Real> > > > > DEF_LRU01_LRF04 = endf_obj.get_DEF_LRU01_LRF04();
  vector<vector<vector<vector<vector<Real> > > > > DEC_LRU01_LRF04 = endf_obj.get_DEC_LRU01_LRF04();
  vector<vector<vector<vector<vector<Real> > > > > DWT_LRU01_LRF04 = endf_obj.get_DWT_LRU01_LRF04();
  vector<vector<vector<vector<vector<Real> > > > > DWF_LRU01_LRF04 = endf_obj.get_DWF_LRU01_LRF04();
  vector<vector<vector<vector<vector<Real> > > > > DWC_LRU01_LRF04 = endf_obj.get_DWC_LRU01_LRF04();
  vector<vector<vector<vector<vector<Real> > > > > GRT_LRU01_LRF04 = endf_obj.get_GRT_LRU01_LRF04();
  vector<vector<vector<vector<vector<Real> > > > > GIT_LRU01_LRF04 = endf_obj.get_GIT_LRU01_LRF04();
  vector<vector<vector<vector<vector<Real> > > > > GRF_LRU01_LRF04 = endf_obj.get_GRF_LRU01_LRF04();
  vector<vector<vector<vector<vector<Real> > > > > GIF_LRU01_LRF04 = endf_obj.get_GIF_LRU01_LRF04();
  vector<vector<vector<vector<vector<Real> > > > > GRC_LRU01_LRF04 = endf_obj.get_GRC_LRU01_LRF04();
  vector<vector<vector<vector<vector<Real> > > > > GIC_LRU01_LRF04 = endf_obj.get_GIC_LRU01_LRF04();
  
  vector<vector<Integer> >                   NX_LRU01_LRF04  = endf_obj.get_NX_LRU01_LRF04();
  vector<vector<vector<Integer> > >          NJS_LRU01_LRF04 = endf_obj.get_NJS_LRU01_LRF04();
  vector<vector<vector<vector<Integer> > > > NLJ_LRU01_LRF04 = endf_obj.get_NLJ_LRU01_LRF04();
   
  //Resize ENDF data
  int ele_no = static_cast<int>(LI_LRU01_LRF04.size());
  if( ele_no == 0 )
  {
    LI_LRU01_LRF04.resize(i_max);
    AT_LRU01_LRF04.resize(i_max);
    AF_LRU01_LRF04.resize(i_max);
    AC_LRU01_LRF04.resize(i_max);
    AJ_LRU01_LRF04.resize(i_max);
    DET_LRU01_LRF04.resize(i_max);
    DEF_LRU01_LRF04.resize(i_max);
    DEC_LRU01_LRF04.resize(i_max);
    DWT_LRU01_LRF04.resize(i_max);
    DWF_LRU01_LRF04.resize(i_max);
    DWC_LRU01_LRF04.resize(i_max);
    GRT_LRU01_LRF04.resize(i_max);
    GIT_LRU01_LRF04.resize(i_max);
    GRF_LRU01_LRF04.resize(i_max);
    GIF_LRU01_LRF04.resize(i_max);
    GRC_LRU01_LRF04.resize(i_max);
    GIC_LRU01_LRF04.resize(i_max);
    NX_LRU01_LRF04.resize(i_max);
    NJS_LRU01_LRF04.resize(i_max);
    NLJ_LRU01_LRF04.resize(i_max);
    for(int i_tmp=0; i_tmp<i_max; i_tmp++)
    {
      LI_LRU01_LRF04[i_tmp].resize(j_max[i_tmp]);
      AT_LRU01_LRF04[i_tmp].resize(j_max[i_tmp]);
      AF_LRU01_LRF04[i_tmp].resize(j_max[i_tmp]);
      AC_LRU01_LRF04[i_tmp].resize(j_max[i_tmp]);
      AJ_LRU01_LRF04[i_tmp].resize(j_max[i_tmp]);
      DET_LRU01_LRF04[i_tmp].resize(j_max[i_tmp]);
      DEF_LRU01_LRF04[i_tmp].resize(j_max[i_tmp]);
      DEC_LRU01_LRF04[i_tmp].resize(j_max[i_tmp]);
      DWT_LRU01_LRF04[i_tmp].resize(j_max[i_tmp]);
      DWF_LRU01_LRF04[i_tmp].resize(j_max[i_tmp]);
      DWC_LRU01_LRF04[i_tmp].resize(j_max[i_tmp]);
      GRT_LRU01_LRF04[i_tmp].resize(j_max[i_tmp]);
      GIT_LRU01_LRF04[i_tmp].resize(j_max[i_tmp]);
      GRF_LRU01_LRF04[i_tmp].resize(j_max[i_tmp]);
      GIF_LRU01_LRF04[i_tmp].resize(j_max[i_tmp]);
      GRC_LRU01_LRF04[i_tmp].resize(j_max[i_tmp]);
      GIC_LRU01_LRF04[i_tmp].resize(j_max[i_tmp]);
      NX_LRU01_LRF04[i_tmp].resize(j_max[i_tmp]);
      NJS_LRU01_LRF04[i_tmp].resize(j_max[i_tmp]);
      NLJ_LRU01_LRF04[i_tmp].resize(j_max[i_tmp]);
    }
  }
  else
  {
    if( ele_no != i_max )
    {
      string class_name = "MF02MT151ConverterAdlerAdler";
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
     
    if( static_cast<int>(LI_LRU01_LRF04[i].size()) != j_max[i] )
    {
      string class_name = "MF02MT151ConverterAdlerAdler";
      string func_name  = "convert_frendy_to_endf_format";
      ostringstream oss01, oss02, oss03, oss04;
      oss01 << i;
      oss02 << j;
      oss03 <<  static_cast<int>(LI_LRU01_LRF04[i].size());
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
  LI_LRU01_LRF04[i][j]  = frendy_obj.get_adler_calc_flg();
  AT_LRU01_LRF04[i][j]  = frendy_obj.get_back_ground_tot();
  AF_LRU01_LRF04[i][j]  = frendy_obj.get_back_ground_fis();
  AC_LRU01_LRF04[i][j]  = frendy_obj.get_back_ground_rad();
  AJ_LRU01_LRF04[i][j]  = frendy_obj.get_j_value_abs();
  DET_LRU01_LRF04[i][j] = frendy_obj.get_ene_reso_tot();
  DEF_LRU01_LRF04[i][j] = frendy_obj.get_ene_reso_fis();
  DEC_LRU01_LRF04[i][j] = frendy_obj.get_ene_reso_rad();
  DWT_LRU01_LRF04[i][j] = frendy_obj.get_gam_width_half_tot();
  DWF_LRU01_LRF04[i][j] = frendy_obj.get_gam_width_half_fis();
  DWC_LRU01_LRF04[i][j] = frendy_obj.get_gam_width_half_rad();
  GRT_LRU01_LRF04[i][j] = frendy_obj.get_symmetrical_data_tot();
  GIT_LRU01_LRF04[i][j] = frendy_obj.get_non_symmetrical_data_tot();
  GRF_LRU01_LRF04[i][j] = frendy_obj.get_symmetrical_data_fis();
  GIF_LRU01_LRF04[i][j] = frendy_obj.get_non_symmetrical_data_fis();
  GRC_LRU01_LRF04[i][j] = frendy_obj.get_symmetrical_data_rad();
  GIC_LRU01_LRF04[i][j] = frendy_obj.get_non_symmetrical_data_rad();

  NX_LRU01_LRF04[i][j] = 0;
  if( static_cast<int>(AC_LRU01_LRF04[i][j].size()) > 0 )
  {
    NX_LRU01_LRF04[i][j] = 3;
  }
  else if( static_cast<int>(AF_LRU01_LRF04[i][j].size()) > 0 )
  {
    NX_LRU01_LRF04[i][j] = 2;
  }
  else if( static_cast<int>(AT_LRU01_LRF04[i][j].size()) > 0 )
  {
    NX_LRU01_LRF04[i][j] = 1;
  }
  
  int k_max = static_cast<int>(AJ_LRU01_LRF04[i][j].size());
  NJS_LRU01_LRF04[i][j].resize(k_max);
  NLJ_LRU01_LRF04[i][j].resize(k_max);
  for(int k=0; k<k_max; k++)
  {
    int l_max = static_cast<int>(AJ_LRU01_LRF04[i][j][k].size());
    NJS_LRU01_LRF04[i][j][k] = l_max;
    NLJ_LRU01_LRF04[i][j][k].resize(l_max);
    
    for(int l=0; l<l_max; l++)
    {
      NLJ_LRU01_LRF04[i][j][k][l] = static_cast<Integer>(DET_LRU01_LRF04[i][j][k][l].size());
    }
  }
  
  //Set ENDF format data
  //endf_obj.clear();
  endf_obj.set_LI_LRU01_LRF04(LI_LRU01_LRF04);
  endf_obj.set_NX_LRU01_LRF04(NX_LRU01_LRF04);
  endf_obj.set_AT_LRU01_LRF04(AT_LRU01_LRF04);
  endf_obj.set_AF_LRU01_LRF04(AF_LRU01_LRF04);
  endf_obj.set_AC_LRU01_LRF04(AC_LRU01_LRF04);
  //!!! There is no Parser data !!!vector<Integer> L_LRU01_LRF04
  endf_obj.set_NJS_LRU01_LRF04(NJS_LRU01_LRF04);
  endf_obj.set_AJ_LRU01_LRF04(AJ_LRU01_LRF04);
  endf_obj.set_NLJ_LRU01_LRF04(NLJ_LRU01_LRF04);
  endf_obj.set_DET_LRU01_LRF04(DET_LRU01_LRF04);
  endf_obj.set_DWT_LRU01_LRF04(DWT_LRU01_LRF04);
  endf_obj.set_GRT_LRU01_LRF04(GRT_LRU01_LRF04);
  endf_obj.set_GIT_LRU01_LRF04(GIT_LRU01_LRF04);
  endf_obj.set_DEF_LRU01_LRF04(DEF_LRU01_LRF04);
  endf_obj.set_DWF_LRU01_LRF04(DWF_LRU01_LRF04);
  endf_obj.set_GRF_LRU01_LRF04(GRF_LRU01_LRF04);
  endf_obj.set_GIF_LRU01_LRF04(GIF_LRU01_LRF04);
  endf_obj.set_DEC_LRU01_LRF04(DEC_LRU01_LRF04);
  endf_obj.set_DWC_LRU01_LRF04(DWC_LRU01_LRF04);
  endf_obj.set_GRC_LRU01_LRF04(GRC_LRU01_LRF04);
  endf_obj.set_GIC_LRU01_LRF04(GIC_LRU01_LRF04);

  //Clear declared data
  clr_obj.clear_vec_array2_int(LI_LRU01_LRF04);
  clr_obj.clear_vec_array2_int(NX_LRU01_LRF04);
  clr_obj.clear_vec_array3_int(NJS_LRU01_LRF04);
  clr_obj.clear_vec_array4_int(NLJ_LRU01_LRF04);
  clr_obj.clear_vec_array3_real(AT_LRU01_LRF04);
  clr_obj.clear_vec_array3_real(AF_LRU01_LRF04);
  clr_obj.clear_vec_array3_real(AC_LRU01_LRF04);
  clr_obj.clear_vec_array4_real(AJ_LRU01_LRF04);
  clr_obj.clear_vec_array5_real(DET_LRU01_LRF04);
  clr_obj.clear_vec_array5_real(DEF_LRU01_LRF04);
  clr_obj.clear_vec_array5_real(DEC_LRU01_LRF04);
  clr_obj.clear_vec_array5_real(DWT_LRU01_LRF04);
  clr_obj.clear_vec_array5_real(DWF_LRU01_LRF04);
  clr_obj.clear_vec_array5_real(DWC_LRU01_LRF04);
  clr_obj.clear_vec_array5_real(GRT_LRU01_LRF04);
  clr_obj.clear_vec_array5_real(GIT_LRU01_LRF04);
  clr_obj.clear_vec_array5_real(GRF_LRU01_LRF04);
  clr_obj.clear_vec_array5_real(GIF_LRU01_LRF04);
  clr_obj.clear_vec_array5_real(GRC_LRU01_LRF04);
  clr_obj.clear_vec_array5_real(GIC_LRU01_LRF04);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//MF02MT151Parser -> AdlerAdlerDataContainer
void MF02MT151ConverterAdlerAdler::convert_endf_format_to_frendy( int& i, int& j,
  MF02MT151Parser& endf_obj, AdlerAdlerDataContainer& frendy_obj )
{
  //Get frendy data
  Integer                        adler_calc_flg           = endf_obj.get_LI_LRU01_LRF04()[i][j];
  vector<Real>                   back_ground_tot          = endf_obj.get_AT_LRU01_LRF04()[i][j];
  vector<Real>                   back_ground_fis          = endf_obj.get_AF_LRU01_LRF04()[i][j];
  vector<Real>                   back_ground_rad          = endf_obj.get_AC_LRU01_LRF04()[i][j];
  vector<vector<Real> >          j_value_abs              = endf_obj.get_AJ_LRU01_LRF04()[i][j];
  vector<vector<vector<Real> > > ene_reso_tot             = endf_obj.get_DET_LRU01_LRF04()[i][j];
  vector<vector<vector<Real> > > ene_reso_fis             = endf_obj.get_DEF_LRU01_LRF04()[i][j];
  vector<vector<vector<Real> > > ene_reso_rad             = endf_obj.get_DEC_LRU01_LRF04()[i][j];
  vector<vector<vector<Real> > > gam_width_half_tot       = endf_obj.get_DWT_LRU01_LRF04()[i][j];
  vector<vector<vector<Real> > > gam_width_half_fis       = endf_obj.get_DWF_LRU01_LRF04()[i][j];
  vector<vector<vector<Real> > > gam_width_half_rad       = endf_obj.get_DWC_LRU01_LRF04()[i][j];
  vector<vector<vector<Real> > > symmetrical_data_tot     = endf_obj.get_GRT_LRU01_LRF04()[i][j];
  vector<vector<vector<Real> > > non_symmetrical_data_tot = endf_obj.get_GIT_LRU01_LRF04()[i][j];
  vector<vector<vector<Real> > > symmetrical_data_fis     = endf_obj.get_GRF_LRU01_LRF04()[i][j];
  vector<vector<vector<Real> > > non_symmetrical_data_fis = endf_obj.get_GIF_LRU01_LRF04()[i][j];
  vector<vector<vector<Real> > > symmetrical_data_rad     = endf_obj.get_GRC_LRU01_LRF04()[i][j];
  vector<vector<vector<Real> > > non_symmetrical_data_rad = endf_obj.get_GIC_LRU01_LRF04()[i][j];

  //Set ENDF format data
  frendy_obj.clear();
  frendy_obj.set_adler_calc_flg(adler_calc_flg);
  frendy_obj.set_back_ground_tot(back_ground_tot);
  frendy_obj.set_back_ground_fis(back_ground_fis);
  frendy_obj.set_back_ground_rad(back_ground_rad);
  //!!! This Parser data is not contained in the Container class !!! //vector<Integer> L_LRU01_LRF04
  frendy_obj.set_j_value_abs(j_value_abs);
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

  //Clear declared data
  adler_calc_flg           = 0;
  back_ground_tot.clear();
  back_ground_fis.clear();
  back_ground_rad.clear();
  clr_obj.clear_vec_array2_real(j_value_abs);
  clr_obj.clear_vec_array3_real(ene_reso_tot);
  clr_obj.clear_vec_array3_real(ene_reso_fis);
  clr_obj.clear_vec_array3_real(ene_reso_rad);
  clr_obj.clear_vec_array3_real(gam_width_half_tot);
  clr_obj.clear_vec_array3_real(gam_width_half_fis);
  clr_obj.clear_vec_array3_real(gam_width_half_rad);
  clr_obj.clear_vec_array3_real(symmetrical_data_tot);
  clr_obj.clear_vec_array3_real(non_symmetrical_data_tot);
  clr_obj.clear_vec_array3_real(symmetrical_data_fis);
  clr_obj.clear_vec_array3_real(non_symmetrical_data_fis);
  clr_obj.clear_vec_array3_real(symmetrical_data_rad);
  clr_obj.clear_vec_array3_real(non_symmetrical_data_rad);
}

