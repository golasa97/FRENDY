#include "EndfUtils/MFxxMTyyyConverter/MF08MT457Converter.hpp"

using namespace frendy;

//constructor
MF08MT457Converter::MF08MT457Converter(void)
{
}

//destructor
MF08MT457Converter::~MF08MT457Converter(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//GeneralDataContainer -> MF08MT457Parser
void MF08MT457Converter::convert_frendy_to_endf_format( GeneralDataContainer& frendy_obj, MF08MT457Parser& endf_obj )
{
  //Get frendy data
  Integer                  LIS      = frendy_obj.get_state_no_target();
  Integer                  LISO     = frendy_obj.get_state_no_target_iso();
  Integer                  NST      = frendy_obj.get_stability_flg();
  Real                     T_HALF   = frendy_obj.get_half_life();
  Real                     D_T_HALF = frendy_obj.get_half_life_uncertainty();
  vector<Real>             E_X      = frendy_obj.get_decay_ene();
  vector<Real>             D_E_X    = frendy_obj.get_decay_ene_uncertainty();
  Real                     SPI      = frendy_obj.get_spin_target();
  Real                     PAR      = frendy_obj.get_parity_target();
  vector<Real>             RTYP0    = frendy_obj.get_decay_type();
  vector<Real>             RFS      = frendy_obj.get_daughter_iso_flg();
  vector<Real>             Q        = frendy_obj.get_decay_ene_tot();
  vector<Real>             D_Q      = frendy_obj.get_decay_ene_tot_uncertainty();
  vector<Real>             BR       = frendy_obj.get_branching_ratio();
  vector<Real>             D_BR     = frendy_obj.get_branching_ratio_uncertainty();
  vector<Real>             STYP     = frendy_obj.get_radiation_type();
  vector<Integer>          LCON     = frendy_obj.get_con_spectrum_flg();
  vector<Real>             FD       = frendy_obj.get_discrete_spectrum_factor();
  vector<Real>             D_FD     = frendy_obj.get_discrete_spectrum_factor_uncertainty();
  vector<Real>             ER_AV    = frendy_obj.get_discrete_ene_ave();
  vector<Real>             D_ER_AV  = frendy_obj.get_discrete_ene_ave_uncertainty();
  vector<Real>             FC       = frendy_obj.get_cont_spectrum_factor();
  vector<Real>             D_FC     = frendy_obj.get_cont_spectrum_factor_uncertainty();
  vector<vector<Real> >    ER       = frendy_obj.get_discrete_ene();
  vector<vector<Real> >    D_ER     = frendy_obj.get_discrete_ene_uncertainty();
  vector<vector<Real> >    RI       = frendy_obj.get_discrete_intensity();
  vector<vector<Real> >    D_RI     = frendy_obj.get_discrete_intensity_uncertainty();
  vector<vector<Real> >    RTYP1    = frendy_obj.get_decay_type_each_ene();
  vector<vector<Real> >    TYPE     = frendy_obj.get_transition_type();
  vector<vector<Real> >    RIS      = frendy_obj.get_internal_pair_form_coef();
  vector<vector<Real> >    D_RIS    = frendy_obj.get_internal_pair_form_coef_uncertainty();
  vector<vector<Real> >    RICC     = frendy_obj.get_conv_coef_tot();
  vector<vector<Real> >    D_RICC   = frendy_obj.get_conv_coef_tot_uncertainty();
  vector<vector<Real> >    RICK     = frendy_obj.get_conv_coef_k();
  vector<vector<Real> >    D_RICK   = frendy_obj.get_conv_coef_k_uncertainty();
  vector<vector<Real> >    RICL     = frendy_obj.get_conv_coef_l();
  vector<vector<Real> >    D_RICL   = frendy_obj.get_conv_coef_l_uncertainty();
  vector<Real>             RTYP2    = frendy_obj.get_decay_type_each_rad();
  vector<Integer>          LCOV     = frendy_obj.get_cont_spectrum_cov_flg();
  vector<vector<Integer> > INT_RP   = frendy_obj.get_cont_spectrum_cov_int_data();
  vector<vector<Integer> > NBT_RP   = frendy_obj.get_cont_spectrum_cov_range_data();
  vector<vector<Real> >    E_INT_RP = frendy_obj.get_cont_spectrum_cov_ene_data();
  vector<vector<Real> >    RP_TAB   = frendy_obj.get_cont_spectrum_cov_data();
  vector<Integer>          LB       = frendy_obj.get_cont_spectrum_cov_matrix_data_flg();
  vector<vector<Real> >    E_K      = frendy_obj.get_cont_spectrum_cov_ek_table();
  vector<vector<Real> >    F_K      = frendy_obj.get_cont_spectrum_cov_fk_table();

  Integer NSP = static_cast<Integer>(ER.size());
  vector<Integer> NER;
  NER.resize(static_cast<int>(NSP));
  for(int i=0; i<static_cast<int>(NSP); i++)
  {
    NER[i] = static_cast<Integer>(ER[i].size());
  }

  Integer mat_no = 0;
  if( LIS == 0 && LISO == 0 && NST == 0 && NSP == 0 &&
      static_cast<int>(E_X.size())   == 0 && static_cast<int>(D_E_X.size())   == 0 &&
      static_cast<int>(RTYP0.size()) == 0 && static_cast<int>(RFS.size())     == 0 &&
      static_cast<int>(Q.size())     == 0 && static_cast<int>(D_Q.size())     == 0 &&
      static_cast<int>(BR.size())    == 0 && static_cast<int>(D_BR.size())    == 0 &&
      static_cast<int>(STYP.size())  == 0 && static_cast<int>(LCON.size())    == 0 &&
      static_cast<int>(FD.size())    == 0 && static_cast<int>(D_FD.size())    == 0 &&
      static_cast<int>(ER_AV.size()) == 0 && static_cast<int>(D_ER_AV.size()) == 0 &&
      static_cast<int>(FC.size())    == 0 && static_cast<int>(D_FC.size())    == 0 )
  {
    mat_no = unassigned_mat_no;
  }

  //Set ENDF format data
  endf_obj.clear();
  endf_obj.set_mat_no(mat_no);
  endf_obj.set_LIS(LIS);
  endf_obj.set_LISO(LISO);
  endf_obj.set_NST(NST);
  endf_obj.set_NSP(NSP);
  endf_obj.set_T_HALF(T_HALF);
  endf_obj.set_D_T_HALF(D_T_HALF);
  endf_obj.set_E_X(E_X);
  endf_obj.set_D_E_X(D_E_X);
  endf_obj.set_SPI(SPI);
  endf_obj.set_PAR(PAR);
  endf_obj.set_RTYP0(RTYP0);
  endf_obj.set_RFS(RFS);
  endf_obj.set_Q(Q);
  endf_obj.set_D_Q(D_Q);
  endf_obj.set_BR(BR);
  endf_obj.set_D_BR(D_BR);
  endf_obj.set_STYP(STYP);
  endf_obj.set_LCON(LCON);
  endf_obj.set_NER(NER);
  endf_obj.set_FD(FD);
  endf_obj.set_D_FD(D_FD);
  endf_obj.set_ER_AV(ER_AV);
  endf_obj.set_D_ER_AV(D_ER_AV);
  endf_obj.set_FC(FC);
  endf_obj.set_D_FC(D_FC);
  endf_obj.set_ER(ER);
  endf_obj.set_D_ER(D_ER);
  endf_obj.set_RTYP1(RTYP1);
  endf_obj.set_TYPE(TYPE);
  endf_obj.set_RI(RI);
  endf_obj.set_D_RI(D_RI);
  endf_obj.set_RIS(RIS);
  endf_obj.set_D_RIS(D_RIS);
  endf_obj.set_RICC(RICC);
  endf_obj.set_D_RICC(D_RICC);
  endf_obj.set_RICK(RICK);
  endf_obj.set_D_RICK(D_RICK);
  endf_obj.set_RICL(RICL);
  endf_obj.set_D_RICL(D_RICL);
  endf_obj.set_RTYP2(RTYP2);
  endf_obj.set_LCOV(LCOV);
  endf_obj.set_NBT_RP(NBT_RP);
  endf_obj.set_INT_RP(INT_RP);
  endf_obj.set_E_INT_RP(E_INT_RP);
  endf_obj.set_RP_TAB(RP_TAB);
  endf_obj.set_LB(LB);
  endf_obj.set_E_K(E_K);
  endf_obj.set_F_K(F_K);

  //Clear declared data
  LIS      = 0;
  LISO     = 0;
  NST      = 0;
  T_HALF   = 0.0;
  D_T_HALF = 0.0;
  E_X.clear();
  D_E_X.clear();
  SPI      = 0.0;
  PAR      = 0.0;
  RTYP0.clear();
  RFS.clear();
  Q.clear();
  D_Q.clear();
  BR.clear();
  D_BR.clear();
  STYP.clear();
  LCON.clear();
  FD.clear();
  D_FD.clear();
  ER_AV.clear();
  D_ER_AV.clear();
  FC.clear();
  D_FC.clear();
  clr_obj.clear_vec_array2_real(ER);
  clr_obj.clear_vec_array2_real(D_ER);
  clr_obj.clear_vec_array2_real(RI);
  clr_obj.clear_vec_array2_real(D_RI);
  clr_obj.clear_vec_array2_real(RTYP1);
  clr_obj.clear_vec_array2_real(TYPE);
  clr_obj.clear_vec_array2_real(RIS);
  clr_obj.clear_vec_array2_real(D_RIS);
  clr_obj.clear_vec_array2_real(RICC);
  clr_obj.clear_vec_array2_real(D_RICC);
  clr_obj.clear_vec_array2_real(RICK);
  clr_obj.clear_vec_array2_real(D_RICK);
  clr_obj.clear_vec_array2_real(RICL);
  clr_obj.clear_vec_array2_real(D_RICL);
  RTYP2.clear();
  LCOV.clear();
  clr_obj.clear_vec_array2_int(INT_RP);
  clr_obj.clear_vec_array2_int(NBT_RP);
  clr_obj.clear_vec_array2_real(E_INT_RP);
  clr_obj.clear_vec_array2_real(RP_TAB);
  LB.clear();
  clr_obj.clear_vec_array2_real(E_K);
  clr_obj.clear_vec_array2_real(F_K);
  
  NSP = 0;
  NER.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//MF08MT457Parser -> GeneralDataContainer
void MF08MT457Converter::convert_endf_format_to_frendy( MF08MT457Parser& endf_obj, GeneralDataContainer& frendy_obj )
{
  //Get frendy data
  Integer                  state_no_target                      = endf_obj.get_LIS();
  Integer                  state_no_target_iso                  = endf_obj.get_LISO();
  Integer                  stability_flg                        = endf_obj.get_NST();
  Real                     half_life                            = endf_obj.get_T_HALF();
  Real                     half_life_uncertainty                = endf_obj.get_D_T_HALF();
  vector<Real>             decay_ene                            = endf_obj.get_E_X();
  vector<Real>             decay_ene_uncertainty                = endf_obj.get_D_E_X();
  Real                     spin_target                          = endf_obj.get_SPI();
  Real                     parity_target                        = endf_obj.get_PAR();
  vector<Real>             decay_type                           = endf_obj.get_RTYP0();
  vector<Real>             daughter_iso_flg                     = endf_obj.get_RFS();
  vector<Real>             decay_ene_tot                        = endf_obj.get_Q();
  vector<Real>             decay_ene_tot_uncertainty            = endf_obj.get_D_Q();
  vector<Real>             branching_ratio                      = endf_obj.get_BR();
  vector<Real>             branching_ratio_uncertainty          = endf_obj.get_D_BR();
  vector<Real>             radiation_type                       = endf_obj.get_STYP();
  vector<Integer>          con_spectrum_flg                     = endf_obj.get_LCON();
  vector<Real>             discrete_spectrum_factor             = endf_obj.get_FD();
  vector<Real>             discrete_spectrum_factor_uncertainty = endf_obj.get_D_FD();
  vector<Real>             discrete_ene_ave                     = endf_obj.get_ER_AV();
  vector<Real>             discrete_ene_ave_uncertainty         = endf_obj.get_D_ER_AV();
  vector<Real>             cont_spectrum_factor                 = endf_obj.get_FC();
  vector<Real>             cont_spectrum_factor_uncertainty     = endf_obj.get_D_FC();
  vector<vector<Real> >    discrete_ene                         = endf_obj.get_ER();
  vector<vector<Real> >    discrete_ene_uncertainty             = endf_obj.get_D_ER();
  vector<vector<Real> >    discrete_intensity                   = endf_obj.get_RI();
  vector<vector<Real> >    discrete_intensity_uncertainty       = endf_obj.get_D_RI();
  vector<vector<Real> >    decay_type_each_ene                  = endf_obj.get_RTYP1();
  vector<vector<Real> >    transition_type                      = endf_obj.get_TYPE();
  vector<vector<Real> >    internal_pair_form_coef              = endf_obj.get_RIS();
  vector<vector<Real> >    internal_pair_form_coef_uncertainty  = endf_obj.get_D_RIS();
  vector<vector<Real> >    conv_coef_tot                        = endf_obj.get_RICC();
  vector<vector<Real> >    conv_coef_tot_uncertainty            = endf_obj.get_D_RICC();
  vector<vector<Real> >    conv_coef_k                          = endf_obj.get_RICK();
  vector<vector<Real> >    conv_coef_k_uncertainty              = endf_obj.get_D_RICK();
  vector<vector<Real> >    conv_coef_l                          = endf_obj.get_RICL();
  vector<vector<Real> >    conv_coef_l_uncertainty              = endf_obj.get_D_RICL();
  vector<Real>             decay_type_each_rad                  = endf_obj.get_RTYP2();
  vector<Integer>          cont_spectrum_cov_flg                = endf_obj.get_LCOV();
  vector<vector<Integer> > cont_spectrum_cov_int_data           = endf_obj.get_INT_RP();
  vector<vector<Integer> > cont_spectrum_cov_range_data         = endf_obj.get_NBT_RP();
  vector<vector<Real> >    cont_spectrum_cov_ene_data           = endf_obj.get_E_INT_RP();
  vector<vector<Real> >    cont_spectrum_cov_data               = endf_obj.get_RP_TAB();
  vector<Integer>          cont_spectrum_cov_matrix_data_flg    = endf_obj.get_LB();
  vector<vector<Real> >    cont_spectrum_cov_ek_table           = endf_obj.get_E_K();
  vector<vector<Real> >    cont_spectrum_cov_fk_table           = endf_obj.get_F_K();

  //Set ENDF format data
  //frendy_obj.clear();
  //text
  //mat_no
  //ZA
  //AWR
  frendy_obj.set_state_no_target(state_no_target);
  frendy_obj.set_state_no_target_iso(state_no_target_iso);
  frendy_obj.set_stability_flg(stability_flg);
  frendy_obj.set_half_life(half_life);
  frendy_obj.set_half_life_uncertainty(half_life_uncertainty);
  frendy_obj.set_decay_ene(decay_ene);
  frendy_obj.set_decay_ene_uncertainty(decay_ene_uncertainty);
  frendy_obj.set_spin_target(spin_target);
  frendy_obj.set_parity_target(parity_target);
  frendy_obj.set_decay_type(decay_type);
  frendy_obj.set_daughter_iso_flg(daughter_iso_flg);
  frendy_obj.set_decay_ene_tot(decay_ene_tot);
  frendy_obj.set_decay_ene_tot_uncertainty(decay_ene_tot_uncertainty);
  frendy_obj.set_branching_ratio(branching_ratio);
  frendy_obj.set_branching_ratio_uncertainty(branching_ratio_uncertainty);
  frendy_obj.set_radiation_type(radiation_type);
  frendy_obj.set_con_spectrum_flg(con_spectrum_flg);
  frendy_obj.set_discrete_spectrum_factor(discrete_spectrum_factor);
  frendy_obj.set_discrete_spectrum_factor_uncertainty(discrete_spectrum_factor_uncertainty);
  frendy_obj.set_discrete_ene_ave(discrete_ene_ave);
  frendy_obj.set_discrete_ene_ave_uncertainty(discrete_ene_ave_uncertainty);
  frendy_obj.set_cont_spectrum_factor(cont_spectrum_factor);
  frendy_obj.set_cont_spectrum_factor_uncertainty(cont_spectrum_factor_uncertainty);
  frendy_obj.set_discrete_ene(discrete_ene);
  frendy_obj.set_discrete_ene_uncertainty(discrete_ene_uncertainty);
  frendy_obj.set_decay_type_each_ene(decay_type_each_ene);
  frendy_obj.set_transition_type(transition_type);
  frendy_obj.set_discrete_intensity(discrete_intensity);
  frendy_obj.set_discrete_intensity_uncertainty(discrete_intensity_uncertainty);
  frendy_obj.set_internal_pair_form_coef(internal_pair_form_coef);
  frendy_obj.set_internal_pair_form_coef_uncertainty(internal_pair_form_coef_uncertainty);
  frendy_obj.set_conv_coef_tot(conv_coef_tot);
  frendy_obj.set_conv_coef_tot_uncertainty(conv_coef_tot_uncertainty);
  frendy_obj.set_conv_coef_k(conv_coef_k);
  frendy_obj.set_conv_coef_k_uncertainty(conv_coef_k_uncertainty);
  frendy_obj.set_conv_coef_l(conv_coef_l);
  frendy_obj.set_conv_coef_l_uncertainty(conv_coef_l_uncertainty);
  frendy_obj.set_decay_type_each_rad(decay_type_each_rad);
  frendy_obj.set_cont_spectrum_cov_flg(cont_spectrum_cov_flg);
  frendy_obj.set_cont_spectrum_cov_range_data(cont_spectrum_cov_range_data);
  frendy_obj.set_cont_spectrum_cov_int_data(cont_spectrum_cov_int_data);
  frendy_obj.set_cont_spectrum_cov_ene_data(cont_spectrum_cov_ene_data);
  frendy_obj.set_cont_spectrum_cov_data(cont_spectrum_cov_data);
  frendy_obj.set_cont_spectrum_cov_matrix_data_flg(cont_spectrum_cov_matrix_data_flg);
  frendy_obj.set_cont_spectrum_cov_ek_table(cont_spectrum_cov_ek_table);
  frendy_obj.set_cont_spectrum_cov_fk_table(cont_spectrum_cov_fk_table);

  //Clear declared data
  state_no_target                      = 0;
  state_no_target_iso                  = 0;
  stability_flg                        = 0;
  half_life                            = 0.0;
  half_life_uncertainty                = 0.0;
  decay_ene.clear();
  decay_ene_uncertainty.clear();
  spin_target                          = 0.0;
  parity_target                        = 0.0;
  decay_type.clear();
  daughter_iso_flg.clear();
  decay_ene_tot.clear();
  decay_ene_tot_uncertainty.clear();
  branching_ratio.clear();
  branching_ratio_uncertainty.clear();
  radiation_type.clear();
  con_spectrum_flg.clear();
  discrete_spectrum_factor.clear();
  discrete_spectrum_factor_uncertainty.clear();
  discrete_ene_ave.clear();
  discrete_ene_ave_uncertainty.clear();
  cont_spectrum_factor.clear();
  cont_spectrum_factor_uncertainty.clear();
  clr_obj.clear_vec_array2_real(discrete_ene);
  clr_obj.clear_vec_array2_real(discrete_ene_uncertainty);
  clr_obj.clear_vec_array2_real(discrete_intensity);
  clr_obj.clear_vec_array2_real(discrete_intensity_uncertainty);
  clr_obj.clear_vec_array2_real(decay_type_each_ene);
  clr_obj.clear_vec_array2_real(transition_type);
  clr_obj.clear_vec_array2_real(internal_pair_form_coef);
  clr_obj.clear_vec_array2_real(internal_pair_form_coef_uncertainty);
  clr_obj.clear_vec_array2_real(conv_coef_tot);
  clr_obj.clear_vec_array2_real(conv_coef_tot_uncertainty);
  clr_obj.clear_vec_array2_real(conv_coef_k);
  clr_obj.clear_vec_array2_real(conv_coef_k_uncertainty);
  clr_obj.clear_vec_array2_real(conv_coef_l);
  clr_obj.clear_vec_array2_real(conv_coef_l_uncertainty);
  decay_type_each_rad.clear();
  cont_spectrum_cov_flg.clear();
  clr_obj.clear_vec_array2_int(cont_spectrum_cov_int_data);
  clr_obj.clear_vec_array2_int(cont_spectrum_cov_range_data);
  clr_obj.clear_vec_array2_real(cont_spectrum_cov_ene_data);
  clr_obj.clear_vec_array2_real(cont_spectrum_cov_data);
  cont_spectrum_cov_matrix_data_flg.clear();
  clr_obj.clear_vec_array2_real(cont_spectrum_cov_ek_table);
  clr_obj.clear_vec_array2_real(cont_spectrum_cov_fk_table);
}

