#include "EndfUtils/MFxxMTyyyConverter/MF07MT004Converter.hpp"

using namespace frendy;

//constructor
MF07MT004Converter::MF07MT004Converter(void)
{
}

//destructor
MF07MT004Converter::~MF07MT004Converter(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//ThermalScatterDataContainer -> MF07MT004Parser
void MF07MT004Converter::convert_frendy_to_endf_format( ThermalScatterDataContainer& frendy_obj, MF07MT004Parser& endf_obj )
{
  //Get frendy data
  Integer                        LAT      = frendy_obj.get_inelastic_temp_flg();
  Integer                        LASYM    = frendy_obj.get_inelastic_symmetric_flg();
  Integer                        LLN      = frendy_obj.get_inelastic_stored_form_flg();
  Integer                        NS       = frendy_obj.get_non_principal_scat_type_no();
  vector<Real>                   B        = frendy_obj.get_inelastic_scat_law_coef();
  vector<vector<Integer> >       LI       = frendy_obj.get_inelastic_temp_int();
  vector<Integer>                INT_BETA = frendy_obj.get_inelastic_beta_int_data();
  vector<Integer>                NBT_BETA = frendy_obj.get_inelastic_beta_range_data();
  vector<Real>                   T0       = frendy_obj.get_inelastic_temp_data_base();
  vector<vector<Real> >          T        = frendy_obj.get_inelastic_temp_data();
  vector<Real>                   BETA     = frendy_obj.get_inelastic_beta_data();
  vector<vector<Integer> >       INT_S0   = frendy_obj.get_inelastic_scat_law_int_data();
  vector<vector<Integer> >       NBT_S0   = frendy_obj.get_inelastic_scat_law_range_data();
  vector<vector<Real> >          A_INT_S0 = frendy_obj.get_inelastic_scat_law_alpha_data();
  vector<vector<Real> >          S0_TAB   = frendy_obj.get_inelastic_scat_law_data_base();
  vector<vector<vector<Real> > > S        = frendy_obj.get_inelastic_scat_law_data();
  vector<vector<Integer> >       INT_T    = frendy_obj.get_inelastic_temp_eff_int_data();
  vector<vector<Integer> >       NBT_T    = frendy_obj.get_inelastic_temp_eff_range_data();
  vector<vector<Real> >          T_INT_T  = frendy_obj.get_inelastic_temp_eff_temp_data();
  vector<vector<Real> >          T_TAB    = frendy_obj.get_inelastic_temp_eff_data();

  Integer NB = static_cast<Integer>(T0.size());

  Integer mat_no = 0;
  if( LAT == 0 && LASYM == 0 && LLN == 0 && NS == 0 && NB == 0 &&
      static_cast<int>(B.size())        == 0 && static_cast<int>(LI.size())       == 0 &&
      static_cast<int>(INT_BETA.size()) == 0 && static_cast<int>(NBT_BETA.size()) == 0 &&
      static_cast<int>(T0.size())       == 0 && static_cast<int>(T.size())        == 0 &&
      static_cast<int>(BETA.size())     == 0 && static_cast<int>(INT_S0.size())   == 0 &&
      static_cast<int>(NBT_S0.size())   == 0 && static_cast<int>(S0_TAB.size())   == 0 &&
      static_cast<int>(S.size())        == 0 && static_cast<int>(INT_T.size())    == 0 &&
      static_cast<int>(T_TAB.size())    == 0 )
  {
    mat_no = unassigned_mat_no;
  }

  //Set ENDF format data
  endf_obj.clear();
  endf_obj.set_mat_no(mat_no);
  endf_obj.set_LAT(LAT);
  endf_obj.set_LASYM(LASYM);
  endf_obj.set_LLN(LLN);
  endf_obj.set_NS(NS);
  endf_obj.set_B(B);
  endf_obj.set_NB(NB);
  endf_obj.set_NBT_BETA(NBT_BETA);
  endf_obj.set_INT_BETA(INT_BETA);
  endf_obj.set_T0(T0);
  endf_obj.set_BETA(BETA);
  endf_obj.set_NBT_S0(NBT_S0);
  endf_obj.set_INT_S0(INT_S0);
  endf_obj.set_A_INT_S0(A_INT_S0);
  endf_obj.set_S0_TAB(S0_TAB);
  endf_obj.set_T(T);
  endf_obj.set_LI(LI);
  endf_obj.set_S(S);
  endf_obj.set_NBT_T(NBT_T);
  endf_obj.set_INT_T(INT_T);
  endf_obj.set_T_INT_T(T_INT_T);
  endf_obj.set_T_TAB(T_TAB);

  //Clear declared data
  LAT      = 0;
  LASYM    = 0;
  LLN      = 0;
  NS       = 0;
  B.clear();
  clr_obj.clear_vec_array2_int(LI);
  INT_BETA.clear();
  NBT_BETA.clear();
  T0.clear();
  clr_obj.clear_vec_array2_real(T);
  BETA.clear();
  clr_obj.clear_vec_array2_int(INT_S0);
  clr_obj.clear_vec_array2_int(NBT_S0);
  clr_obj.clear_vec_array2_real(A_INT_S0);
  clr_obj.clear_vec_array2_real(S0_TAB);
  clr_obj.clear_vec_array3_real(S);
  clr_obj.clear_vec_array2_int(INT_T);
  clr_obj.clear_vec_array2_int(NBT_T);
  clr_obj.clear_vec_array2_real(T_INT_T);
  clr_obj.clear_vec_array2_real(T_TAB);
  NB = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//MF07MT004Parser -> ThermalScatterDataContainer
void MF07MT004Converter::convert_endf_format_to_frendy( MF07MT004Parser& endf_obj, ThermalScatterDataContainer& frendy_obj )
{
  //Get frendy data
  Integer                        inelastic_temp_flg             = endf_obj.get_LAT();
  Integer                        inelastic_symmetric_flg        = endf_obj.get_LASYM();
  Integer                        inelastic_stored_form_flg      = endf_obj.get_LLN();
  Integer                        non_principal_scat_type_no     = endf_obj.get_NS();
  vector<Real>                   inelastic_scat_law_coef        = endf_obj.get_B();
  vector<vector<Integer> >       inelastic_temp_int             = endf_obj.get_LI();
  vector<Integer>                inelastic_beta_int_data        = endf_obj.get_INT_BETA();
  vector<Integer>                inelastic_beta_range_data      = endf_obj.get_NBT_BETA();
  vector<Real>                   inelastic_temp_data_base       = endf_obj.get_T0();
  vector<vector<Real> >          inelastic_temp_data            = endf_obj.get_T();
  vector<Real>                   inelastic_beta_data            = endf_obj.get_BETA();
  vector<vector<Integer> >       inelastic_scat_law_int_data    = endf_obj.get_INT_S0();
  vector<vector<Integer> >       inelastic_scat_law_range_data  = endf_obj.get_NBT_S0();
  vector<vector<Real> >          inelastic_scat_law_alpha_data  = endf_obj.get_A_INT_S0();
  vector<vector<Real> >          inelastic_scat_law_data_base   = endf_obj.get_S0_TAB();
  vector<vector<vector<Real> > > inelastic_scat_law_data        = endf_obj.get_S();
  vector<vector<Integer> >       inelastic_temp_eff_int_data    = endf_obj.get_INT_T();
  vector<vector<Integer> >       inelastic_temp_eff_range_data  = endf_obj.get_NBT_T();
  vector<vector<Real> >          inelastic_temp_eff_temp_data   = endf_obj.get_T_INT_T();
  vector<vector<Real> >          inelastic_temp_eff_data        = endf_obj.get_T_TAB();

  //Set ENDF format data
  //frendy_obj.clear();
  //text
  //mat_no
  //ZA
  //AWR
  frendy_obj.set_inelastic_temp_flg(inelastic_temp_flg);
  frendy_obj.set_inelastic_symmetric_flg(inelastic_symmetric_flg);
  frendy_obj.set_inelastic_stored_form_flg(inelastic_stored_form_flg);
  frendy_obj.set_non_principal_scat_type_no(non_principal_scat_type_no);
  frendy_obj.set_inelastic_scat_law_coef(inelastic_scat_law_coef);
  frendy_obj.set_inelastic_beta_range_data(inelastic_beta_range_data);
  frendy_obj.set_inelastic_beta_int_data(inelastic_beta_int_data);
  frendy_obj.set_inelastic_temp_data_base(inelastic_temp_data_base);
  frendy_obj.set_inelastic_beta_data(inelastic_beta_data);
  frendy_obj.set_inelastic_scat_law_range_data(inelastic_scat_law_range_data);
  frendy_obj.set_inelastic_scat_law_int_data(inelastic_scat_law_int_data);
  frendy_obj.set_inelastic_scat_law_alpha_data(inelastic_scat_law_alpha_data);
  frendy_obj.set_inelastic_scat_law_data_base(inelastic_scat_law_data_base);
  frendy_obj.set_inelastic_temp_data(inelastic_temp_data);
  frendy_obj.set_inelastic_temp_int(inelastic_temp_int);
  frendy_obj.set_inelastic_scat_law_data(inelastic_scat_law_data);
  frendy_obj.set_inelastic_temp_eff_range_data(inelastic_temp_eff_range_data);
  frendy_obj.set_inelastic_temp_eff_int_data(inelastic_temp_eff_int_data);
  frendy_obj.set_inelastic_temp_eff_temp_data(inelastic_temp_eff_temp_data);
  frendy_obj.set_inelastic_temp_eff_data(inelastic_temp_eff_data);

  //Clear declared data
  inelastic_temp_flg         = 0;
  inelastic_symmetric_flg    = 0;
  inelastic_stored_form_flg  = 0;
  non_principal_scat_type_no = 0;
  inelastic_scat_law_coef.clear();
  clr_obj.clear_vec_array2_int(inelastic_temp_int);
  inelastic_beta_int_data.clear();
  inelastic_beta_range_data.clear();
  inelastic_temp_data_base.clear();
  clr_obj.clear_vec_array2_real(inelastic_temp_data);
  inelastic_beta_data.clear();
  clr_obj.clear_vec_array2_int(inelastic_scat_law_int_data);
  clr_obj.clear_vec_array2_int(inelastic_scat_law_range_data);
  clr_obj.clear_vec_array2_real(inelastic_scat_law_alpha_data);
  clr_obj.clear_vec_array2_real(inelastic_scat_law_data_base);
  clr_obj.clear_vec_array3_real(inelastic_scat_law_data);
  clr_obj.clear_vec_array2_int(inelastic_temp_eff_int_data);
  clr_obj.clear_vec_array2_int(inelastic_temp_eff_range_data);
  clr_obj.clear_vec_array2_real(inelastic_temp_eff_temp_data);
  clr_obj.clear_vec_array2_real(inelastic_temp_eff_data);
}

