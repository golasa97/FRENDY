#include "EndfUtils/MFxxMTyyyConverter/ResonanceData/MF02MT151ConverterUnresolved.hpp"

using namespace frendy;

//constructor
MF02MT151ConverterUnresolved::MF02MT151ConverterUnresolved(void)
{
}

//destructor
MF02MT151ConverterUnresolved::~MF02MT151ConverterUnresolved(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//UnresolvedResonanceDataContainer -> MF02MT151Parser
void MF02MT151ConverterUnresolved::convert_frendy_to_endf_format
  ( int& i, int& i_max, int& j, vector<int>& j_max,
  UnresolvedResonanceDataContainer& frendy_obj, MF02MT151Parser& endf_obj )
{
  //Declare ENDF data
  vector<Integer>                                  LFW          = endf_obj.get_LFW();
  vector<vector<Integer> >                         LRF          = endf_obj.get_LRF();
  vector<vector<Integer> >                         LSSF_LRU02   = endf_obj.get_LSSF_LRU02();
  vector<vector<vector<Integer> > >                NJS_LRU02    = endf_obj.get_NJS_LRU02();
  
  vector<vector<vector<vector<Real> > > >          D_LRU02_A    = endf_obj.get_D_LRU02_A();
  vector<vector<vector<vector<Real> > > >          AJ_LRU02_A   = endf_obj.get_AJ_LRU02_A();
  vector<vector<vector<vector<Real> > > >          AMUN_LRU02_A = endf_obj.get_AMUN_LRU02_A();
  vector<vector<vector<vector<Real> > > >          GNO_LRU02_A  = endf_obj.get_GNO_LRU02_A();
  vector<vector<vector<vector<Real> > > >          GG_LRU02_A   = endf_obj.get_GG_LRU02_A();
  
  vector<vector<Integer> >                         NE_LRU02_B   = endf_obj.get_NE_LRU02_B();
  vector<vector<vector<Real> > >                   ES_LRU02_B   = endf_obj.get_ES_LRU02_B();
  vector<vector<vector<vector<Integer> > > >       MUF_LRU02_B  = endf_obj.get_MUF_LRU02_B();
  vector<vector<vector<vector<Real> > > >          D_LRU02_B    = endf_obj.get_D_LRU02_B();
  vector<vector<vector<vector<Real> > > >          AJ_LRU02_B   = endf_obj.get_AJ_LRU02_B();
  vector<vector<vector<vector<Real> > > >          AMUN_LRU02_B = endf_obj.get_AMUN_LRU02_B();
  vector<vector<vector<vector<Real> > > >          GNO_LRU02_B  = endf_obj.get_GNO_LRU02_B();
  vector<vector<vector<vector<Real> > > >          GG_LRU02_B   = endf_obj.get_GG_LRU02_B();
  vector<vector<vector<vector<vector<Real> > > > > GF_LRU02_B   = endf_obj.get_GF_LRU02_B();
  
  vector<vector<vector<vector<Integer> > > >       NE_LRU02_C   = endf_obj.get_NE_LRU02_C();
  vector<vector<vector<vector<Integer> > > >       INT_LRU02_C  = endf_obj.get_INT_LRU02_C();
  vector<vector<vector<vector<Real> > > >          AJ_LRU02_C   = endf_obj.get_AJ_LRU02_C();
  vector<vector<vector<vector<Real> > > >          AMUX_LRU02_C = endf_obj.get_AMUX_LRU02_C();
  vector<vector<vector<vector<Real> > > >          AMUN_LRU02_C = endf_obj.get_AMUN_LRU02_C();
  vector<vector<vector<vector<Real> > > >          AMUG_LRU02_C = endf_obj.get_AMUG_LRU02_C();
  vector<vector<vector<vector<Real> > > >          AMUF_LRU02_C = endf_obj.get_AMUF_LRU02_C();
  vector<vector<vector<vector<vector<Real> > > > > ES_LRU02_C   = endf_obj.get_ES_LRU02_C();
  vector<vector<vector<vector<vector<Real> > > > > D_LRU02_C    = endf_obj.get_D_LRU02_C();
  vector<vector<vector<vector<vector<Real> > > > > GX_LRU02_C   = endf_obj.get_GX_LRU02_C();
  vector<vector<vector<vector<vector<Real> > > > > GNO_LRU02_C  = endf_obj.get_GNO_LRU02_C();
  vector<vector<vector<vector<vector<Real> > > > > GG_LRU02_C   = endf_obj.get_GG_LRU02_C();
  vector<vector<vector<vector<vector<Real> > > > > GF_LRU02_C   = endf_obj.get_GF_LRU02_C();
  
  //Resize ENDF data
  int ele_no = static_cast<int>(LSSF_LRU02.size());
  if( ele_no == 0 )
  {
    LFW.resize(i_max);
    LRF.resize(i_max);
    LSSF_LRU02.resize(i_max);
    D_LRU02_A.resize(i_max);
    AJ_LRU02_A.resize(i_max);
    AMUN_LRU02_A.resize(i_max);
    GNO_LRU02_A.resize(i_max);
    GG_LRU02_A.resize(i_max);
    ES_LRU02_B.resize(i_max);
    MUF_LRU02_B.resize(i_max);
    GF_LRU02_B.resize(i_max);
    INT_LRU02_C.resize(i_max);
    AMUX_LRU02_C.resize(i_max);
    AMUG_LRU02_C.resize(i_max);
    AMUF_LRU02_C.resize(i_max);
    GX_LRU02_C.resize(i_max);
    
    NJS_LRU02.resize(i_max);
    NE_LRU02_B.resize(i_max);
    NE_LRU02_C.resize(i_max);
    D_LRU02_B.resize(i_max);
    AJ_LRU02_B.resize(i_max);
    AMUN_LRU02_B.resize(i_max);
    GNO_LRU02_B.resize(i_max);
    GG_LRU02_B.resize(i_max);
    AJ_LRU02_C.resize(i_max);
    AMUN_LRU02_C.resize(i_max);
    ES_LRU02_C.resize(i_max);
    D_LRU02_C.resize(i_max);
    GNO_LRU02_C.resize(i_max);
    GG_LRU02_C.resize(i_max);
    GF_LRU02_C.resize(i_max);
    for(int i_tmp=0; i_tmp<i_max; i_tmp++)
    {
      LRF[i_tmp].resize(j_max[i_tmp]);
      LSSF_LRU02[i_tmp].resize(j_max[i_tmp]);
      D_LRU02_A[i_tmp].resize(j_max[i_tmp]);
      AJ_LRU02_A[i_tmp].resize(j_max[i_tmp]);
      AMUN_LRU02_A[i_tmp].resize(j_max[i_tmp]);
      GNO_LRU02_A[i_tmp].resize(j_max[i_tmp]);
      GG_LRU02_A[i_tmp].resize(j_max[i_tmp]);
      ES_LRU02_B[i_tmp].resize(j_max[i_tmp]);
      MUF_LRU02_B[i_tmp].resize(j_max[i_tmp]);
      GF_LRU02_B[i_tmp].resize(j_max[i_tmp]);
      INT_LRU02_C[i_tmp].resize(j_max[i_tmp]);
      AMUX_LRU02_C[i_tmp].resize(j_max[i_tmp]);
      AMUG_LRU02_C[i_tmp].resize(j_max[i_tmp]);
      AMUF_LRU02_C[i_tmp].resize(j_max[i_tmp]);
      GX_LRU02_C[i_tmp].resize(j_max[i_tmp]);
      
      NJS_LRU02[i_tmp].resize(j_max[i_tmp]);
      NE_LRU02_B[i_tmp].resize(j_max[i_tmp]);
      NE_LRU02_C[i_tmp].resize(j_max[i_tmp]);
      D_LRU02_B[i_tmp].resize(j_max[i_tmp]);
      AJ_LRU02_B[i_tmp].resize(j_max[i_tmp]);
      AMUN_LRU02_B[i_tmp].resize(j_max[i_tmp]);
      GNO_LRU02_B[i_tmp].resize(j_max[i_tmp]);
      GG_LRU02_B[i_tmp].resize(j_max[i_tmp]);
      AJ_LRU02_C[i_tmp].resize(j_max[i_tmp]);
      AMUN_LRU02_C[i_tmp].resize(j_max[i_tmp]);
      ES_LRU02_C[i_tmp].resize(j_max[i_tmp]);
      D_LRU02_C[i_tmp].resize(j_max[i_tmp]);
      GNO_LRU02_C[i_tmp].resize(j_max[i_tmp]);
      GG_LRU02_C[i_tmp].resize(j_max[i_tmp]);
      GF_LRU02_C[i_tmp].resize(j_max[i_tmp]);
    }
  }
  else
  {
    if( ele_no != i_max )
    {
      string class_name = "MF02MT151ConverterUnresolved";
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
     
    if( static_cast<int>(LSSF_LRU02[i].size()) != j_max[i] )
    {
      string class_name = "MF02MT151ConverterUnresolved";
      string func_name  = "convert_frendy_to_endf_format";
      ostringstream oss01, oss02, oss03, oss04;
      oss01 << i;
      oss02 << j;
      oss03 <<  static_cast<int>(LSSF_LRU02[i].size());
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
  LFW[i]             = frendy_obj.get_fis_width_flg();
  LRF[i][j]          = frendy_obj.get_xs_formula_flg();
  LSSF_LRU02[i][j]   = frendy_obj.get_self_shielding_flg();
  
  if( LFW[i] == 0 && LRF[i][j] == 1 )
  {
    AJ_LRU02_A[i][j]   = frendy_obj.get_j_value_abs();
    AMUN_LRU02_A[i][j] = frendy_obj.get_freedom_n();
    
    int k_max = static_cast<int>(AJ_LRU02_A[i][j].size());
    NJS_LRU02[i][j].resize(k_max);
    D_LRU02_A[i][j].resize(k_max);
    GNO_LRU02_A[i][j].resize(k_max);
    GG_LRU02_A[i][j].resize(k_max);
    for(int k=0; k<k_max; k++)
    {
      NJS_LRU02[i][j][k] = static_cast<Integer>(AJ_LRU02_A[i][j][k].size());

      int l_max = static_cast<int>(NJS_LRU02[i][j][k]);
      D_LRU02_A[i][j][k].resize(l_max);
      GNO_LRU02_A[i][j][k].resize(l_max);
      GG_LRU02_A[i][j][k].resize(l_max);
      for(int l=0; l<l_max; l++)
      {
        D_LRU02_A[i][j][k][l]   = frendy_obj.get_level_spacing()[k][l][0];
        GNO_LRU02_A[i][j][k][l] = frendy_obj.get_ave_gam_width_n()[k][l][0];
        GG_LRU02_A[i][j][k][l]  = frendy_obj.get_ave_gam_width_rad()[k][l][0];
      }
    }
  }
  else if( LFW[i] == 1 && LRF[i][j] == 1 )
  {
    MUF_LRU02_B[i][j]  = frendy_obj.get_freedom_fis_int();
    AJ_LRU02_B[i][j]   = frendy_obj.get_j_value_abs();
    AMUN_LRU02_B[i][j] = frendy_obj.get_freedom_n();
    GF_LRU02_B[i][j]   = frendy_obj.get_ave_gam_width_fis();

    int k_max = static_cast<int>(AJ_LRU02_B[i][j].size());
    NJS_LRU02[i][j].resize(k_max);
    D_LRU02_B[i][j].resize(k_max);
    GNO_LRU02_B[i][j].resize(k_max);
    GG_LRU02_B[i][j].resize(k_max);
    for(int k=0; k<k_max; k++)
    {
      NJS_LRU02[i][j][k] = static_cast<Integer>(AJ_LRU02_B[i][j][k].size());

      int l_max = static_cast<int>(NJS_LRU02[i][j][k]);
      D_LRU02_B[i][j][k].resize(l_max);
      GNO_LRU02_B[i][j][k].resize(l_max);
      GG_LRU02_B[i][j][k].resize(l_max);
      for(int l=0; l<l_max; l++)
      {
        D_LRU02_B[i][j][k][l]    = frendy_obj.get_level_spacing()[k][l][0];
        GNO_LRU02_B[i][j][k][l]  = frendy_obj.get_ave_gam_width_n()[k][l][0];
        GG_LRU02_B[i][j][k][l]   = frendy_obj.get_ave_gam_width_rad()[k][l][0];
      }
    }

    NE_LRU02_B[i][j] = static_cast<Integer>(frendy_obj.get_ene_unreso().size());
    k_max = static_cast<int>(NE_LRU02_B[i][j]);
    ES_LRU02_B[i][j].resize(k_max);
    for(int k=0; k<k_max; k++)
    {
      ES_LRU02_B[i][j][k] = frendy_obj.get_ene_unreso()[k][0][0];
    }
  }
  else if( (LFW[i] == 1 && LRF[i][j] == 2) || (LFW[i] == 0 && LRF[i][j] == 2) )
  {
    AJ_LRU02_C[i][j]   = frendy_obj.get_j_value_abs();
    INT_LRU02_C[i][j]  = frendy_obj.get_unreso_int_data();
    
    AMUX_LRU02_C[i][j] = frendy_obj.get_freedom_comp();
    AMUN_LRU02_C[i][j] = frendy_obj.get_freedom_n();
    AMUG_LRU02_C[i][j] = frendy_obj.get_freedom_rad();
    AMUF_LRU02_C[i][j] = frendy_obj.get_freedom_fis();
    ES_LRU02_C[i][j]   = frendy_obj.get_ene_unreso();
    D_LRU02_C[i][j]    = frendy_obj.get_level_spacing();
    GX_LRU02_C[i][j]   = frendy_obj.get_ave_gam_width_comp();
    GNO_LRU02_C[i][j]  = frendy_obj.get_ave_gam_width_n();
    GG_LRU02_C[i][j]   = frendy_obj.get_ave_gam_width_rad();
    GF_LRU02_C[i][j]   = frendy_obj.get_ave_gam_width_fis();
    
    int k_max = static_cast<int>(D_LRU02_C[i][j].size());
    NJS_LRU02[i][j].resize(k_max);
    NE_LRU02_C[i][j].resize(k_max);
    for(int k=0; k<k_max; k++)
    {
      NJS_LRU02[i][j][k] = static_cast<Integer>(D_LRU02_C[i][j][k].size());
      
      int l_max = static_cast<int>(NJS_LRU02[i][j][k]);
      NE_LRU02_C[i][j][k].resize(l_max);
      for(int l=0; l<l_max; l++)
      {
        NE_LRU02_C[i][j][k][l] = static_cast<Integer>(D_LRU02_C[i][j][k][l].size());
      }
    }
  }
  
  //Set ENDF format data
  //endf_obj.clear();
  endf_obj.set_LFW(LFW);
  endf_obj.set_LRF(LRF);
  endf_obj.set_LSSF_LRU02(LSSF_LRU02);
  endf_obj.set_NJS_LRU02(NJS_LRU02);
  endf_obj.set_D_LRU02_A(D_LRU02_A);
  endf_obj.set_AJ_LRU02_A(AJ_LRU02_A);
  endf_obj.set_AMUN_LRU02_A(AMUN_LRU02_A);
  endf_obj.set_GNO_LRU02_A(GNO_LRU02_A);
  endf_obj.set_GG_LRU02_A(GG_LRU02_A);
  endf_obj.set_NE_LRU02_B(NE_LRU02_B);
  endf_obj.set_ES_LRU02_B(ES_LRU02_B);
  endf_obj.set_MUF_LRU02_B(MUF_LRU02_B);
  endf_obj.set_D_LRU02_B(D_LRU02_B);
  endf_obj.set_AJ_LRU02_B(AJ_LRU02_B);
  endf_obj.set_AMUN_LRU02_B(AMUN_LRU02_B);
  endf_obj.set_GNO_LRU02_B(GNO_LRU02_B);
  endf_obj.set_GG_LRU02_B(GG_LRU02_B);
  endf_obj.set_GF_LRU02_B(GF_LRU02_B);
  endf_obj.set_AJ_LRU02_C(AJ_LRU02_C);
  endf_obj.set_INT_LRU02_C(INT_LRU02_C);
  endf_obj.set_NE_LRU02_C(NE_LRU02_C);
  endf_obj.set_AMUX_LRU02_C(AMUX_LRU02_C);
  endf_obj.set_AMUN_LRU02_C(AMUN_LRU02_C);
  endf_obj.set_AMUG_LRU02_C(AMUG_LRU02_C);
  endf_obj.set_AMUF_LRU02_C(AMUF_LRU02_C);
  endf_obj.set_ES_LRU02_C(ES_LRU02_C);
  endf_obj.set_D_LRU02_C(D_LRU02_C);
  endf_obj.set_GX_LRU02_C(GX_LRU02_C);
  endf_obj.set_GNO_LRU02_C(GNO_LRU02_C);
  endf_obj.set_GG_LRU02_C(GG_LRU02_C);
  endf_obj.set_GF_LRU02_C(GF_LRU02_C);

  //Clear declared data
  LFW.clear();
  clr_obj.clear_vec_array2_int(LRF);
  clr_obj.clear_vec_array2_int(LSSF_LRU02);
  clr_obj.clear_vec_array3_int(NJS_LRU02);

  clr_obj.clear_vec_array4_real(D_LRU02_A);
  clr_obj.clear_vec_array4_real(AJ_LRU02_A);
  clr_obj.clear_vec_array4_real(AMUN_LRU02_A);
  clr_obj.clear_vec_array4_real(GNO_LRU02_A);
  clr_obj.clear_vec_array4_real(GG_LRU02_A);

  clr_obj.clear_vec_array2_int(NE_LRU02_B);
  clr_obj.clear_vec_array3_real(ES_LRU02_B);
  clr_obj.clear_vec_array4_int(MUF_LRU02_B);
  clr_obj.clear_vec_array4_real(D_LRU02_B);
  clr_obj.clear_vec_array4_real(AJ_LRU02_B);
  clr_obj.clear_vec_array4_real(AMUN_LRU02_B);
  clr_obj.clear_vec_array4_real(GNO_LRU02_B);
  clr_obj.clear_vec_array4_real(GG_LRU02_B);
  clr_obj.clear_vec_array5_real(GF_LRU02_B);

  clr_obj.clear_vec_array4_int(NE_LRU02_C);
  clr_obj.clear_vec_array4_int(INT_LRU02_C);
  clr_obj.clear_vec_array4_real(AJ_LRU02_C);
  clr_obj.clear_vec_array4_real(AMUX_LRU02_C);
  clr_obj.clear_vec_array4_real(AMUN_LRU02_C);
  clr_obj.clear_vec_array4_real(AMUG_LRU02_C);
  clr_obj.clear_vec_array4_real(AMUF_LRU02_C);
  clr_obj.clear_vec_array5_real(ES_LRU02_C);
  clr_obj.clear_vec_array5_real(D_LRU02_C);
  clr_obj.clear_vec_array5_real(GX_LRU02_C);
  clr_obj.clear_vec_array5_real(GNO_LRU02_C);
  clr_obj.clear_vec_array5_real(GG_LRU02_C);
  clr_obj.clear_vec_array5_real(GF_LRU02_C);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//MF02MT151Parser -> UnresolvedResonanceDataContainer
void MF02MT151ConverterUnresolved::convert_endf_format_to_frendy( int& i, int& j,
  MF02MT151Parser& endf_obj, UnresolvedResonanceDataContainer& frendy_obj )
{
  //Get frendy data
  Integer                        fis_width_flg       = endf_obj.get_LFW()[i];
  Integer                        xs_formula_flg      = endf_obj.get_LRF()[i][j];
  Integer                        self_shielding_flg  = endf_obj.get_LSSF_LRU02()[i][j];
  
  vector<vector<vector<Real> > > level_spacing;
  vector<vector<Real> >          j_value_abs;
  vector<vector<Real> >          freedom_n;
  vector<vector<vector<Real> > > ave_gam_width_n;
  vector<vector<vector<Real> > > ave_gam_width_rad;
  vector<vector<vector<Real> > > ene_unreso;
  vector<vector<Integer> >       freedom_fis_int;
  vector<vector<vector<Real> > > ave_gam_width_fis;
  vector<vector<Integer> >       unreso_int_data;
  vector<vector<Real> >          freedom_comp;
  vector<vector<Real> >          freedom_rad;
  vector<vector<Real> >          freedom_fis;
  vector<vector<vector<Real> > > ave_gam_width_comp;

  if( fis_width_flg == 0 && xs_formula_flg == 1 )
  {
    j_value_abs = endf_obj.get_AJ_LRU02_A()[i][j];
    freedom_n   = endf_obj.get_AMUN_LRU02_A()[i][j];
    
    int k_max = static_cast<int>(endf_obj.get_D_LRU02_A()[i][j].size());
    level_spacing.resize(k_max);
    ave_gam_width_n.resize(k_max);
    ave_gam_width_rad.resize(k_max);
    for(int k=0; k<k_max; k++)
    {
      int l_max = static_cast<int>(endf_obj.get_D_LRU02_A()[i][j][k].size());
      level_spacing[k].resize(l_max);
      ave_gam_width_n[k].resize(l_max);
      ave_gam_width_rad[k].resize(l_max);
      for(int l=0; l<l_max; l++)
      {
        level_spacing[k][l].resize(1);
        ave_gam_width_n[k][l].resize(1);
        ave_gam_width_rad[k][l].resize(1);
        
        level_spacing[k][l][0]      = endf_obj.get_D_LRU02_A()[i][j][k][l];
        ave_gam_width_n[k][l][0]    = endf_obj.get_GNO_LRU02_A()[i][j][k][l];
        ave_gam_width_rad[k][l][0]  = endf_obj.get_GG_LRU02_A()[i][j][k][l];
      }
    }
  }
  else if( fis_width_flg == 1 && xs_formula_flg == 1)
  {
    freedom_fis_int   = endf_obj.get_MUF_LRU02_B()[i][j];
    j_value_abs       = endf_obj.get_AJ_LRU02_B()[i][j];
    freedom_n         = endf_obj.get_AMUN_LRU02_B()[i][j];
    ave_gam_width_fis = endf_obj.get_GF_LRU02_B()[i][j];
    
    int k_max = static_cast<int>(endf_obj.get_D_LRU02_B()[i][j].size());
    level_spacing.resize(k_max);
    ave_gam_width_n.resize(k_max);
    ave_gam_width_rad.resize(k_max);
    for(int k=0; k<k_max; k++)
    {
      int l_max = static_cast<int>(endf_obj.get_D_LRU02_B()[i][j][k].size());
      level_spacing[k].resize(l_max);
      ave_gam_width_n[k].resize(l_max);
      ave_gam_width_rad[k].resize(l_max);
      for(int l=0; l<l_max; l++)
      {
        level_spacing[k][l].resize(1);
        ave_gam_width_n[k][l].resize(1);
        ave_gam_width_rad[k][l].resize(1);

        level_spacing[k][l][0]     = endf_obj.get_D_LRU02_B()[i][j][k][l];
        ave_gam_width_n[k][l][0]   = endf_obj.get_GNO_LRU02_B()[i][j][k][l];
        ave_gam_width_rad[k][l][0] = endf_obj.get_GG_LRU02_B()[i][j][k][l];
      }
    }

    k_max = static_cast<int>(endf_obj.get_ES_LRU02_B()[i][j].size());
    ene_unreso.resize(k_max);
    for(int k=0; k<k_max; k++)
    {
      ene_unreso[k].resize(1);
      ene_unreso[k][0].resize(1);
      ene_unreso[k][0][0] = endf_obj.get_ES_LRU02_B()[i][j][k];
    }
    
  }
  else if( (fis_width_flg == 1 && xs_formula_flg == 2) || (fis_width_flg == 0 && xs_formula_flg == 2) )
  {
    j_value_abs        = endf_obj.get_AJ_LRU02_C()[i][j];
    unreso_int_data    = endf_obj.get_INT_LRU02_C()[i][j];
    freedom_comp       = endf_obj.get_AMUX_LRU02_C()[i][j];
    freedom_n          = endf_obj.get_AMUN_LRU02_C()[i][j];
    freedom_rad        = endf_obj.get_AMUG_LRU02_C()[i][j];
    freedom_fis        = endf_obj.get_AMUF_LRU02_C()[i][j];
    ene_unreso         = endf_obj.get_ES_LRU02_C()[i][j];
    level_spacing      = endf_obj.get_D_LRU02_C()[i][j];
    ave_gam_width_comp = endf_obj.get_GX_LRU02_C()[i][j];
    ave_gam_width_n    = endf_obj.get_GNO_LRU02_C()[i][j];
    ave_gam_width_rad  = endf_obj.get_GG_LRU02_C()[i][j];
    ave_gam_width_fis  = endf_obj.get_GF_LRU02_C()[i][j];
  }

  //Set ENDF format data
  frendy_obj.clear();
  frendy_obj.set_fis_width_flg(fis_width_flg );
  frendy_obj.set_xs_formula_flg(xs_formula_flg);
  frendy_obj.set_self_shielding_flg(self_shielding_flg);
  frendy_obj.set_level_spacing(level_spacing);
  frendy_obj.set_j_value_abs(j_value_abs);
  frendy_obj.set_freedom_n(freedom_n);
  frendy_obj.set_ave_gam_width_n(ave_gam_width_n);
  frendy_obj.set_ave_gam_width_rad(ave_gam_width_rad);
  frendy_obj.set_ene_unreso(ene_unreso);
  frendy_obj.set_freedom_fis_int(freedom_fis_int);
  frendy_obj.set_ave_gam_width_fis(ave_gam_width_fis);
  frendy_obj.set_unreso_int_data(unreso_int_data);
  frendy_obj.set_freedom_comp(freedom_comp);
  frendy_obj.set_freedom_rad(freedom_rad);
  frendy_obj.set_freedom_fis(freedom_fis);
  frendy_obj.set_ave_gam_width_comp(ave_gam_width_comp);

  //Clear declared data
  fis_width_flg       = 0;
  xs_formula_flg      = 0;
  self_shielding_flg  = 0;
  clr_obj.clear_vec_array3_real(level_spacing);
  clr_obj.clear_vec_array2_real(j_value_abs);
  clr_obj.clear_vec_array2_real(freedom_n);
  clr_obj.clear_vec_array3_real(ave_gam_width_n);
  clr_obj.clear_vec_array3_real(ave_gam_width_rad);
  clr_obj.clear_vec_array3_real(ene_unreso);
  clr_obj.clear_vec_array2_int(freedom_fis_int);
  clr_obj.clear_vec_array3_real(ave_gam_width_fis);
  clr_obj.clear_vec_array2_int(unreso_int_data);
  clr_obj.clear_vec_array2_real(freedom_comp);
  clr_obj.clear_vec_array2_real(freedom_rad);
  clr_obj.clear_vec_array2_real(freedom_fis);
  clr_obj.clear_vec_array3_real(ave_gam_width_comp);
}

