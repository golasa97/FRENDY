#include "EndfUtils/MFxxMTyyyConverter/MF04Converter.hpp"

using namespace frendy;

//constructor
MF04Converter::MF04Converter(void)
{
}

//destructor
MF04Converter::~MF04Converter(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//EnergyAngularDataContainer -> MF04Parser
void MF04Converter::convert_frendy_to_endf_format( EnergyAngularDataContainer& frendy_obj, MF04Parser& endf_obj )
{
  //Get frendy data
  Integer                  mt_no         = frendy_obj.get_reaction_type();
  Integer                  LTT           = frendy_obj.get_angular_repr_flg();
  Integer                  LI            = frendy_obj.get_isotropic_flg();
  Integer                  LCT           = frendy_obj.get_ref_frame_flg();
  Integer                  LVT           = frendy_obj.get_transformation_matrix_flg();
  vector<Real>             U             = frendy_obj.get_transformation_matrix();
  vector<Integer>          INT_E_LTT01   = frendy_obj.get_angular_int_data_polynomial();
  vector<Integer>          NBT_E_LTT01   = frendy_obj.get_angular_range_data_polynomial();
  vector<vector<Real> >    A_LTT01       = frendy_obj.get_angular_data_polynomial();
  vector<Real>             T_LTT01       = frendy_obj.get_temp_target_polynomial();
  vector<Real>             E_LTT01       = frendy_obj.get_angular_probability_ene_polynomial();
  vector<Integer>          LT_LTT01      = frendy_obj.get_temp_target_dependence_flg_polynomial();
  vector<Integer>          INT_E_LTT02   = frendy_obj.get_angular_int_data_tab();
  vector<Integer>          NBT_E_LTT02   = frendy_obj.get_angular_range_data_tab();
  vector<vector<Integer> > INT_F_LTT02   = frendy_obj.get_angular_probability_int_data_tab();
  vector<vector<Integer> > NBT_F_LTT02   = frendy_obj.get_angular_probability_range_data_tab();
  vector<vector<Real> >    M_INT_F_LTT02 = frendy_obj.get_angular_probability_cos_tab();
  vector<vector<Real> >    F_TAB_LTT02   = frendy_obj.get_angular_probability_data_tab();
  vector<Real>             T_LTT02       = frendy_obj.get_temp_target_tab();
  vector<Real>             E_LTT02       = frendy_obj.get_angular_probability_ene_tab();
  vector<Integer>          LT_LTT02      = frendy_obj.get_temp_target_dependence_flg_tab();

  Integer mat_no = 0;
  if( LTT == 0 && LI == 0 && LCT == 0 && LVT == 0 && 
      static_cast<int>(INT_E_LTT01.size())   == 0 && static_cast<int>(NBT_E_LTT01.size()) == 0 &&
      static_cast<int>(A_LTT01.size())       == 0 && static_cast<int>(T_LTT01.size())     == 0 &&
      static_cast<int>(E_LTT01.size())       == 0 && static_cast<int>(LT_LTT01.size())    == 0 &&
      static_cast<int>(INT_E_LTT02.size())   == 0 && static_cast<int>(NBT_E_LTT02.size()) == 0 &&
      static_cast<int>(INT_F_LTT02.size())   == 0 && static_cast<int>(NBT_F_LTT02.size()) == 0 &&
      static_cast<int>(M_INT_F_LTT02.size()) == 0 && static_cast<int>(F_TAB_LTT02.size()) == 0 &&
      static_cast<int>(T_LTT02.size())       == 0 && static_cast<int>(E_LTT02.size())     == 0 &&
      static_cast<int>(LT_LTT02.size())      == 0 && static_cast<int>(U.size())           == 0 )

  {
    mat_no = unassigned_mat_no;
    mt_no  = unassigned_mt_no;
  }

  Integer NK = 0;
  Integer NM = 0;
  if( LVT == 1 )
  {
    NK = static_cast<Integer>(U.size());
  }
  
  Integer         NE_LTT01 = 0;
  vector<Integer> NL_LTT01;
  if( LTT == 1 || LTT == 3 )
  {
    NE_LTT01 = static_cast<Integer>(T_LTT01.size());
    NL_LTT01.resize(static_cast<int>(NE_LTT01));
    for(int i=0; i<static_cast<int>(NE_LTT01); i++)
    {
      NL_LTT01[i] = static_cast<Integer>(A_LTT01[i].size());
    }
  }
  
  Integer         NE_LTT02 = 0;
  vector<Integer> NR_LTT02, NP_LTT02;
  if( LTT == 2 || LTT == 3 )
  {
    NE_LTT02 = static_cast<Integer>(T_LTT02.size());
    NR_LTT02.resize(static_cast<int>(NE_LTT02));
    NP_LTT02.resize(static_cast<int>(NE_LTT02));
    for(int i=0; i<static_cast<int>(NE_LTT02); i++)
    {
      NR_LTT02[i] = static_cast<Integer>(NBT_F_LTT02[i].size());
      NP_LTT02[i] = static_cast<Integer>(M_INT_F_LTT02[i].size());
    }
  }

  //Set ENDF format data
  endf_obj.clear();
  endf_obj.set_mat_no(mat_no);
  endf_obj.set_mt_no(mt_no);
  endf_obj.set_LVT(LVT);
  endf_obj.set_LTT(LTT);
  endf_obj.set_LI(LI);
  endf_obj.set_LCT(LCT);
  endf_obj.set_NK(NK);
  endf_obj.set_NM(NM);
  endf_obj.set_U(U);
  endf_obj.set_NE_LTT01(NE_LTT01);
  endf_obj.set_NBT_E_LTT01(NBT_E_LTT01);
  endf_obj.set_INT_E_LTT01(INT_E_LTT01);
  endf_obj.set_A_LTT01(A_LTT01);
  endf_obj.set_T_LTT01(T_LTT01);
  endf_obj.set_E_LTT01(E_LTT01);
  endf_obj.set_LT_LTT01(LT_LTT01);
  endf_obj.set_NL_LTT01(NL_LTT01);
  endf_obj.set_NE_LTT02(NE_LTT02);
  endf_obj.set_NBT_E_LTT02(NBT_E_LTT02);
  endf_obj.set_INT_E_LTT02(INT_E_LTT02);
  endf_obj.set_NBT_F_LTT02(NBT_F_LTT02);
  endf_obj.set_INT_F_LTT02(INT_F_LTT02);
  endf_obj.set_M_INT_F_LTT02(M_INT_F_LTT02);
  endf_obj.set_F_TAB_LTT02(F_TAB_LTT02);
  endf_obj.set_T_LTT02(T_LTT02);
  endf_obj.set_E_LTT02(E_LTT02);
  endf_obj.set_LT_LTT02(LT_LTT02);
  endf_obj.set_NR_LTT02(NR_LTT02);
  endf_obj.set_NP_LTT02(NP_LTT02);
  
  endf_obj.set_NE_LTT03_L(NE_LTT01);
  endf_obj.set_NBT_E_LTT03_L(NBT_E_LTT01);
  endf_obj.set_INT_E_LTT03_L(INT_E_LTT01);
  endf_obj.set_A_LTT03_L(A_LTT01);
  endf_obj.set_T_LTT03_L(T_LTT01);
  endf_obj.set_E_LTT03_L(E_LTT01);
  endf_obj.set_LT_LTT03_L(LT_LTT01);
  endf_obj.set_NL_LTT03_L(NL_LTT01);
  
  endf_obj.set_NE_LTT03_T(NE_LTT02);
  endf_obj.set_NBT_E_LTT03_T(NBT_E_LTT02);
  endf_obj.set_INT_E_LTT03_T(INT_E_LTT02);
  endf_obj.set_NBT_F_LTT03_T(NBT_F_LTT02);
  endf_obj.set_INT_F_LTT03_T(INT_F_LTT02);
  endf_obj.set_M_INT_F_LTT03_T(M_INT_F_LTT02);
  endf_obj.set_F_TAB_LTT03_T(F_TAB_LTT02);
  endf_obj.set_T_LTT03_T(T_LTT02);
  endf_obj.set_E_LTT03_T(E_LTT02);
  endf_obj.set_LT_LTT03_T(LT_LTT02);
  endf_obj.set_NR_LTT03_T(NR_LTT02);
  endf_obj.set_NP_LTT03_T(NP_LTT02);

  //Clear declared data
  mt_no         = 0;
  LTT           = 0;
  LI            = 0;
  LCT           = 0;
  LVT           = 0;
  U.clear();
  INT_E_LTT01.clear();
  NBT_E_LTT01.clear();
  clr_obj.clear_vec_array2_real(A_LTT01);
  T_LTT01.clear();
  E_LTT01.clear();
  LT_LTT01.clear();
  INT_E_LTT02.clear();
  NBT_E_LTT02.clear();
  clr_obj.clear_vec_array2_int(INT_F_LTT02);
  clr_obj.clear_vec_array2_int(NBT_F_LTT02);
  clr_obj.clear_vec_array2_real(M_INT_F_LTT02);
  clr_obj.clear_vec_array2_real(F_TAB_LTT02);
  T_LTT02.clear();
  E_LTT02.clear();
  LT_LTT02.clear();
  
  NK = 0;
  NM = 0;
  NE_LTT01 = 0;
  NL_LTT01.clear();
  NE_LTT02 = 0;
  NR_LTT02.clear();
  NP_LTT02.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//MF04Parser -> EnergyAngularDataContainer
void MF04Converter::convert_endf_format_to_frendy( MF04Parser& endf_obj, EnergyAngularDataContainer& frendy_obj )
{
  //Get frendy data
  Integer                  reaction_type                         = endf_obj.get_mt_no();
  Integer                  angular_repr_flg                      = endf_obj.get_LTT();
  Integer                  isotropic_flg                         = endf_obj.get_LI();
  Integer                  ref_frame_flg                         = endf_obj.get_LCT();
  Integer                  transformation_matrix_flg             = endf_obj.get_LVT();
  vector<Real>             transformation_matrix                 = endf_obj.get_U();
  vector<Integer>          angular_int_data_polynomial           = endf_obj.get_INT_E_LTT01();
  vector<Integer>          angular_range_data_polynomial         = endf_obj.get_NBT_E_LTT01();
  vector<vector<Real> >    angular_data_polynomial               = endf_obj.get_A_LTT01();
  vector<Real>             temp_target_polynomial                = endf_obj.get_T_LTT01();
  vector<Real>             angular_probability_ene_polynomial    = endf_obj.get_E_LTT01();
  vector<Integer>          temp_target_dependence_flg_polynomial = endf_obj.get_LT_LTT01();
  vector<Integer>          angular_int_data_tab                  = endf_obj.get_INT_E_LTT02();
  vector<Integer>          angular_range_data_tab                = endf_obj.get_NBT_E_LTT02();
  vector<vector<Integer> > angular_probability_int_data_tab      = endf_obj.get_INT_F_LTT02();
  vector<vector<Integer> > angular_probability_range_data_tab    = endf_obj.get_NBT_F_LTT02();
  vector<vector<Real> >    angular_probability_cos_tab           = endf_obj.get_M_INT_F_LTT02();
  vector<vector<Real> >    angular_probability_data_tab          = endf_obj.get_F_TAB_LTT02();
  vector<Real>             temp_target_tab                       = endf_obj.get_T_LTT02();
  vector<Real>             angular_probability_ene_tab           = endf_obj.get_E_LTT02();
  vector<Integer>          temp_target_dependence_flg_tab        = endf_obj.get_LT_LTT02();

  if( angular_repr_flg == 0 && isotropic_flg == 0 && ref_frame_flg == 0 && transformation_matrix_flg == 0 &&
      static_cast<int>(transformation_matrix.size())                 == 0 &&
      static_cast<int>(angular_int_data_polynomial.size())           == 0 &&
      static_cast<int>(angular_range_data_polynomial.size())         == 0 &&
      static_cast<int>(angular_data_polynomial.size())               == 0 &&
      static_cast<int>(temp_target_polynomial.size())                == 0 &&
      static_cast<int>(angular_probability_ene_polynomial.size())    == 0 &&
      static_cast<int>(temp_target_dependence_flg_polynomial.size()) == 0 &&
      static_cast<int>(angular_int_data_tab.size())                  == 0 &&
      static_cast<int>(angular_range_data_tab.size())                == 0 &&
      static_cast<int>(angular_probability_int_data_tab.size())      == 0 &&
      static_cast<int>(angular_probability_range_data_tab.size())    == 0 &&
      static_cast<int>(angular_probability_cos_tab.size())           == 0 &&
      static_cast<int>(angular_probability_data_tab.size())          == 0 &&
      static_cast<int>(temp_target_tab.size())                       == 0 &&
      static_cast<int>(angular_probability_ene_tab.size())           == 0 &&
      static_cast<int>(temp_target_dependence_flg_tab.size())        == 0 )

  {
    reaction_type = unassigned_mt_no;
  }

  //Set ENDF format data
  //frendy_obj.clear();
  //text
  //mat_no
  frendy_obj.set_reaction_type(reaction_type);
  //ZA
  //AWR
  frendy_obj.set_transformation_matrix_flg(transformation_matrix_flg);
  frendy_obj.set_angular_repr_flg(angular_repr_flg);
  frendy_obj.set_isotropic_flg(isotropic_flg);
  frendy_obj.set_ref_frame_flg(ref_frame_flg);
  frendy_obj.set_transformation_matrix(transformation_matrix);
  frendy_obj.set_angular_range_data_polynomial(angular_range_data_polynomial);
  frendy_obj.set_angular_int_data_polynomial(angular_int_data_polynomial);
  frendy_obj.set_angular_data_polynomial(angular_data_polynomial);
  frendy_obj.set_temp_target_polynomial(temp_target_polynomial);
  frendy_obj.set_angular_probability_ene_polynomial(angular_probability_ene_polynomial);
  frendy_obj.set_temp_target_dependence_flg_polynomial(temp_target_dependence_flg_polynomial);
  frendy_obj.set_angular_range_data_tab(angular_range_data_tab);
  frendy_obj.set_angular_int_data_tab(angular_int_data_tab);
  frendy_obj.set_angular_probability_range_data_tab(angular_probability_range_data_tab);
  frendy_obj.set_angular_probability_int_data_tab(angular_probability_int_data_tab);
  frendy_obj.set_angular_probability_cos_tab(angular_probability_cos_tab);
  frendy_obj.set_angular_probability_data_tab(angular_probability_data_tab);
  frendy_obj.set_temp_target_tab(temp_target_tab);
  frendy_obj.set_angular_probability_ene_tab(angular_probability_ene_tab);
  frendy_obj.set_temp_target_dependence_flg_tab(temp_target_dependence_flg_tab);

  //Clear declared data
  reaction_type                         = 0;
  angular_repr_flg                      = 0;
  isotropic_flg                         = 0;
  ref_frame_flg                         = 0;
  transformation_matrix_flg             = 0;
  transformation_matrix.clear();
  angular_int_data_polynomial.clear();
  angular_range_data_polynomial.clear();
  clr_obj.clear_vec_array2_real(angular_data_polynomial);
  temp_target_polynomial.clear();
  angular_probability_ene_polynomial.clear();
  temp_target_dependence_flg_polynomial.clear();
  angular_int_data_tab.clear();
  angular_range_data_tab.clear();
  clr_obj.clear_vec_array2_int(angular_probability_int_data_tab);
  clr_obj.clear_vec_array2_int(angular_probability_range_data_tab);
  clr_obj.clear_vec_array2_real(angular_probability_cos_tab);
  clr_obj.clear_vec_array2_real(angular_probability_data_tab);
  temp_target_tab.clear();
  angular_probability_ene_tab.clear();
  temp_target_dependence_flg_tab.clear();
}

