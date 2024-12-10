#include "EndfUtils/MFxxMTyyyConverter/MF33Converter.hpp"

using namespace frendy;

//constructor
MF33Converter::MF33Converter(void)
{
}

//destructor
MF33Converter::~MF33Converter(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//CovarianceCrossSectionDataContainer -> MF33Parser
void MF33Converter::convert_frendy_to_endf_format( CovarianceCrossSectionDataContainer& frendy_obj, MF33Parser& endf_obj )
{
  //Get frendy data
  Integer                                 mt_no = frendy_obj.get_reaction_type();
  Integer                                 MTL   = frendy_obj.get_reaction_type_target();
  vector<Real>                            XMF   = frendy_obj.get_target_second_file_no();
  vector<Real>                            XLFS  = frendy_obj.get_target_second_excited_state();
  vector<Integer>                         MAT   = frendy_obj.get_target_second_mat_no();
  vector<Integer>                         MT    = frendy_obj.get_target_second_reaction_type();
  vector<vector<Integer> >                LTY   = frendy_obj.get_cov_matrix_flg();
  vector<vector<Real> >                   E1    = frendy_obj.get_xs_ene_range_low();
  vector<vector<Real> >                   E2    = frendy_obj.get_xs_ene_range_high();
  vector<vector<vector<Real> > >          CI    = frendy_obj.get_xs_contribute_coef();
  vector<vector<vector<Real> > >          XMTI  = frendy_obj.get_xs_contribute_reaction_type();
  vector<vector<Integer> >                MATS  = frendy_obj.get_relevant_mat_no();
  vector<vector<Integer> >                MTS   = frendy_obj.get_relevant_reaction_type();
  vector<vector<Real> >                   XMFS  = frendy_obj.get_relevant_file_no();
  vector<vector<Real> >                   XLFSS = frendy_obj.get_relevant_level_no();
  vector<vector<vector<Real> > >          EI    = frendy_obj.get_relevant_ene_data();
  vector<vector<vector<Real> > >          WEI   = frendy_obj.get_relevant_weight();
  vector<vector<Integer> >                LB    = frendy_obj.get_cov_matrix_data_flg();
  vector<vector<vector<Real> > >          E_K   = frendy_obj.get_cov_matrix_ene_k();
  vector<vector<vector<vector<Real> > > > F_K   = frendy_obj.get_cov_matrix_coef_k();
  vector<vector<vector<Real> > >          E_T   = frendy_obj.get_cov_matrix_ene_l();
  vector<vector<vector<vector<Real> > > > F_T   = frendy_obj.get_cov_matrix_coef_l();

  Integer mat_no = 0;
  if( MTL == 0 &&
      static_cast<int>(XMF.size())   == 0 && static_cast<int>(XLFS.size()) == 0 &&
      static_cast<int>(MAT.size())   == 0 && static_cast<int>(MT.size())   == 0 &&
      static_cast<int>(LTY.size())   == 0 && static_cast<int>(E1.size())   == 0 &&
      static_cast<int>(E2.size())    == 0 && static_cast<int>(CI.size())   == 0 &&
      static_cast<int>(XMTI.size())  == 0 && static_cast<int>(MATS.size()) == 0 &&
      static_cast<int>(MTS.size())   == 0 && static_cast<int>(XMFS.size()) == 0 &&
      static_cast<int>(XLFSS.size()) == 0 && static_cast<int>(EI.size())   == 0 &&
      static_cast<int>(WEI.size())   == 0 && static_cast<int>(LB.size())   == 0 &&
      static_cast<int>(E_K.size())   == 0 && static_cast<int>(F_K.size())  == 0 &&
      static_cast<int>(E_T.size())   == 0 && static_cast<int>(F_T.size())  == 0 )
  {
    mat_no = unassigned_mat_no;
    mt_no  = unassigned_mt_no;
  }

  Integer NL = static_cast<Integer>(XMF.size());
  vector<Integer>          NC;
  vector<Integer>          NI;
  vector<vector<Integer> > LT;
  int i_max = static_cast<int>(NL);
  NC.resize(i_max);
  NI.resize(i_max);
  LT.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    NC[i] = static_cast<Integer>(E1[i].size());
    NI[i] = static_cast<Integer>(LB[i].size());

    int j_max = static_cast<int>(NI[i]);
    LT[i].resize(j_max);
    for(int j=0; j<j_max; j++)
    {
      if( LB[i][j] == 5 )
      {
        LT[i][j] = frendy_obj.get_symmetric_coef_flg()[i][j]; //LS
      }
      else if( LB[i][j] == 6 )
      {
        LT[i][j] = 0;
      }
      else
      {
        LT[i][j] = static_cast<Integer>(E_T[i][j].size());
      }
    }
  }
  
  //Set ENDF format data
  endf_obj.clear();
  endf_obj.set_mat_no(mat_no);
  endf_obj.set_mt_no(mt_no);
  endf_obj.set_MTL(MTL);
  endf_obj.set_NL(NL);
  endf_obj.set_XMF(XMF);
  endf_obj.set_XLFS(XLFS);
  endf_obj.set_MAT(MAT);
  endf_obj.set_MT(MT);
  endf_obj.set_NC(NC);
  endf_obj.set_NI(NI);
  endf_obj.set_LTY(LTY);
  endf_obj.set_E1(E1);
  endf_obj.set_E2(E2);
  endf_obj.set_CI(CI);
  endf_obj.set_XMTI(XMTI);
  endf_obj.set_MATS(MATS);
  endf_obj.set_MTS(MTS);
  endf_obj.set_XMFS(XMFS);
  endf_obj.set_XLFSS(XLFSS);
  endf_obj.set_EI(EI);
  endf_obj.set_WEI(WEI);
  endf_obj.set_LB(LB);
  endf_obj.set_LT(LT);
  endf_obj.set_E_K(E_K);
  endf_obj.set_E_T(E_T);
  endf_obj.set_F_K(F_K);
  endf_obj.set_F_T(F_T);

  //Clear declared data
  mt_no = 0;
  MTL   = 0;
  XMF.clear();
  XLFS.clear();
  MAT.clear();
  MT.clear();
  clr_obj.clear_vec_array2_int(LTY);
  clr_obj.clear_vec_array2_real(E1);
  clr_obj.clear_vec_array2_real(E2);
  clr_obj.clear_vec_array3_real(CI);
  clr_obj.clear_vec_array3_real(XMTI);
  clr_obj.clear_vec_array2_int(MATS);
  clr_obj.clear_vec_array2_int(MTS);
  clr_obj.clear_vec_array2_real(XMFS);
  clr_obj.clear_vec_array2_real(XLFSS);
  clr_obj.clear_vec_array3_real(EI);
  clr_obj.clear_vec_array3_real(WEI);
  clr_obj.clear_vec_array2_int(LB);
  clr_obj.clear_vec_array3_real(E_K);
  clr_obj.clear_vec_array4_real(F_K);
  clr_obj.clear_vec_array3_real(E_T);
  clr_obj.clear_vec_array4_real(F_T);
  
  NL = 0;
  NC.clear();
  NI.clear();
  clr_obj.clear_vec_array2_int(LT);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//MF33Parser -> CovarianceCrossSectionDataContainer
void MF33Converter::convert_endf_format_to_frendy( MF33Parser& endf_obj, CovarianceCrossSectionDataContainer& frendy_obj )
{
  //Get frendy data
  Integer                                 reaction_type               = endf_obj.get_mt_no();
  Integer                                 reaction_type_target        = endf_obj.get_MTL();
  vector<Real>                            target_second_file_no       = endf_obj.get_XMF();
  vector<Real>                            target_second_excited_state = endf_obj.get_XLFS();
  vector<Integer>                         target_second_mat_no        = endf_obj.get_MAT();
  vector<Integer>                         target_second_reaction_type = endf_obj.get_MT();
  vector<vector<Integer> >                cov_matrix_flg              = endf_obj.get_LTY();
  vector<vector<Real> >                   xs_ene_range_low            = endf_obj.get_E1();
  vector<vector<Real> >                   xs_ene_range_high           = endf_obj.get_E2();
  vector<vector<vector<Real> > >          xs_contribute_coef          = endf_obj.get_CI();
  vector<vector<vector<Real> > >          xs_contribute_reaction_type = endf_obj.get_XMTI();
  vector<vector<Integer> >                relevant_mat_no             = endf_obj.get_MATS();
  vector<vector<Integer> >                relevant_reaction_type      = endf_obj.get_MTS();
  vector<vector<Real> >                   relevant_file_no            = endf_obj.get_XMFS();
  vector<vector<Real> >                   relevant_level_no           = endf_obj.get_XLFSS();
  vector<vector<vector<Real> > >          relevant_ene_data           = endf_obj.get_EI();
  vector<vector<vector<Real> > >          relevant_weight             = endf_obj.get_WEI();
  vector<vector<Integer> >                cov_matrix_data_flg         = endf_obj.get_LB();
  vector<vector<vector<Real> > >          cov_matrix_ene_k            = endf_obj.get_E_K();
  vector<vector<vector<vector<Real> > > > cov_matrix_coef_k           = endf_obj.get_F_K();
  vector<vector<vector<Real> > >          cov_matrix_ene_l            = endf_obj.get_E_T();
  vector<vector<vector<vector<Real> > > > cov_matrix_coef_l           = endf_obj.get_F_T();

  if( reaction_type_target == 0 &&
      static_cast<int>(target_second_file_no.size())       == 0 &&
      static_cast<int>(target_second_excited_state.size()) == 0 &&
      static_cast<int>(target_second_mat_no.size())        == 0 &&
      static_cast<int>(target_second_reaction_type.size()) == 0 &&
      static_cast<int>(cov_matrix_flg.size())              == 0 &&
      static_cast<int>(xs_ene_range_low.size())            == 0 &&
      static_cast<int>(xs_ene_range_high.size())           == 0 &&
      static_cast<int>(xs_contribute_coef.size())          == 0 &&
      static_cast<int>(xs_contribute_reaction_type.size()) == 0 &&
      static_cast<int>(relevant_mat_no.size())             == 0 &&
      static_cast<int>(relevant_reaction_type.size())      == 0 &&
      static_cast<int>(relevant_file_no.size())            == 0 &&
      static_cast<int>(relevant_level_no.size())           == 0 &&
      static_cast<int>(relevant_ene_data.size())           == 0 &&
      static_cast<int>(relevant_weight.size())             == 0 &&
      static_cast<int>(cov_matrix_data_flg.size())         == 0 &&
      static_cast<int>(cov_matrix_ene_k.size())            == 0 &&
      static_cast<int>(cov_matrix_coef_k.size())           == 0 &&
      static_cast<int>(cov_matrix_ene_l.size())            == 0 &&
      static_cast<int>(cov_matrix_coef_l.size())           == 0 )
  {
    reaction_type = unassigned_mt_no;
  }

  if( reaction_type_target == 0 &&
      static_cast<int>(target_second_file_no.size())       == 0 &&
      static_cast<int>(target_second_excited_state.size()) == 0 &&
      static_cast<int>(target_second_mat_no.size())        == 0 &&
      static_cast<int>(target_second_reaction_type.size()) == 0 &&
      static_cast<int>(cov_matrix_flg.size())              == 0 &&
      static_cast<int>(xs_ene_range_low.size())            == 0 &&
      static_cast<int>(xs_ene_range_high.size())           == 0 &&
      static_cast<int>(xs_contribute_coef.size())          == 0 &&
      static_cast<int>(xs_contribute_reaction_type.size()) == 0 &&
      static_cast<int>(relevant_mat_no.size())             == 0 &&
      static_cast<int>(relevant_reaction_type.size())      == 0 &&
      static_cast<int>(relevant_file_no.size())            == 0 &&
      static_cast<int>(relevant_level_no.size())           == 0 &&
      static_cast<int>(relevant_ene_data.size())           == 0 &&
      static_cast<int>(relevant_weight.size())             == 0 &&
      static_cast<int>(cov_matrix_data_flg.size())         == 0 &&
      static_cast<int>(cov_matrix_ene_k.size())            == 0 &&
      static_cast<int>(cov_matrix_coef_k.size())           == 0 &&
      static_cast<int>(cov_matrix_ene_l.size())            == 0 &&
      static_cast<int>(cov_matrix_coef_l.size())           == 0 )
  {
    reaction_type = unassigned_mt_no;
  }

  vector<vector<Integer> > symmetric_coef_flg;
  int i_max = static_cast<int>(cov_matrix_data_flg.size());
  symmetric_coef_flg.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(cov_matrix_data_flg[i].size());
    symmetric_coef_flg[i].resize(j_max);
    for(int j=0; j<j_max; j++)
    {
      symmetric_coef_flg[i][j] = 0;
      if( cov_matrix_data_flg[i][j] == 5 )
      {
        symmetric_coef_flg[i][j] = endf_obj.get_LS()[i][j];
      }
    }
  }

  //Set ENDF format data
  //frendy_obj.clear();
  //text
  //mat_no
  frendy_obj.set_reaction_type(reaction_type);
  //ZA
  //AWR
  frendy_obj.set_reaction_type_target(reaction_type_target);
  frendy_obj.set_target_second_file_no(target_second_file_no);
  frendy_obj.set_target_second_excited_state(target_second_excited_state);
  frendy_obj.set_target_second_mat_no(target_second_mat_no);
  frendy_obj.set_target_second_reaction_type(target_second_reaction_type);
  frendy_obj.set_cov_matrix_flg(cov_matrix_flg);
  frendy_obj.set_xs_ene_range_low(xs_ene_range_low);
  frendy_obj.set_xs_ene_range_high(xs_ene_range_high);
  frendy_obj.set_xs_contribute_coef(xs_contribute_coef);
  frendy_obj.set_xs_contribute_reaction_type(xs_contribute_reaction_type);
  frendy_obj.set_relevant_mat_no(relevant_mat_no);
  frendy_obj.set_relevant_reaction_type(relevant_reaction_type);
  frendy_obj.set_relevant_file_no(relevant_file_no);
  frendy_obj.set_relevant_level_no(relevant_level_no);
  frendy_obj.set_relevant_ene_data(relevant_ene_data);
  frendy_obj.set_relevant_weight(relevant_weight);
  frendy_obj.set_cov_matrix_data_flg(cov_matrix_data_flg);
  frendy_obj.set_cov_matrix_ene_k(cov_matrix_ene_k);
  frendy_obj.set_cov_matrix_ene_l(cov_matrix_ene_l);
  frendy_obj.set_cov_matrix_coef_k(cov_matrix_coef_k);
  frendy_obj.set_cov_matrix_coef_l(cov_matrix_coef_l);
  frendy_obj.set_symmetric_coef_flg(symmetric_coef_flg);

  //Clear declared data
  reaction_type               = 0;
  reaction_type_target        = 0;
  target_second_file_no.clear();
  target_second_excited_state.clear();
  target_second_mat_no.clear();
  target_second_reaction_type.clear();
  clr_obj.clear_vec_array2_int(cov_matrix_flg);
  clr_obj.clear_vec_array2_real(xs_ene_range_low);
  clr_obj.clear_vec_array2_real(xs_ene_range_high);
  clr_obj.clear_vec_array3_real(xs_contribute_coef);
  clr_obj.clear_vec_array3_real(xs_contribute_reaction_type);
  clr_obj.clear_vec_array2_int(relevant_mat_no);
  clr_obj.clear_vec_array2_int(relevant_reaction_type);
  clr_obj.clear_vec_array2_real(relevant_file_no);
  clr_obj.clear_vec_array2_real(relevant_level_no);
  clr_obj.clear_vec_array3_real(relevant_ene_data);
  clr_obj.clear_vec_array3_real(relevant_weight);
  clr_obj.clear_vec_array2_int(cov_matrix_data_flg);
  clr_obj.clear_vec_array2_int(symmetric_coef_flg);
  clr_obj.clear_vec_array3_real(cov_matrix_ene_k);
  clr_obj.clear_vec_array4_real(cov_matrix_coef_k);
  clr_obj.clear_vec_array3_real(cov_matrix_ene_l);
  clr_obj.clear_vec_array4_real(cov_matrix_coef_l);
}

