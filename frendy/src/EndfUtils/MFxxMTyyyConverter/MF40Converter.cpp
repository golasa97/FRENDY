#include "EndfUtils/MFxxMTyyyConverter/MF40Converter.hpp"

using namespace frendy;

//constructor
MF40Converter::MF40Converter(void)
{
}

//destructor
MF40Converter::~MF40Converter(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//CovarianceRadioactiveProductDataContainer -> MF40Parser
void MF40Converter::convert_frendy_to_endf_format( CovarianceRadioactiveProductDataContainer& frendy_obj, MF40Parser& endf_obj )
{
  //Get frendy data
  Integer                                          mt_no = frendy_obj.get_reaction_type();
  Integer                                          LIS   = frendy_obj.get_state_no_target();
  vector<Real>                                     QM    = frendy_obj.get_q_value_mass();
  vector<Real>                                     QI    = frendy_obj.get_q_value();
  vector<Integer>                                  IZAP  = frendy_obj.get_mat_data_product();
  vector<Integer>                                  LFS   = frendy_obj.get_state_no_product();
  vector<vector<Real> >                            XMF1  = frendy_obj.get_target_second_file_no();
  vector<vector<Real> >                            XLFS1 = frendy_obj.get_target_second_excited_state();
  vector<vector<Integer> >                         MAT1  = frendy_obj.get_target_second_mat_no();
  vector<vector<Integer> >                         MT1   = frendy_obj.get_target_second_reaction_type();
  vector<vector<vector<Integer> > >                LTY   = frendy_obj.get_cov_matrix_flg();
  vector<vector<vector<Real> > >                   E1    = frendy_obj.get_xs_ene_range_low();
  vector<vector<vector<Real> > >                   E2    = frendy_obj.get_xs_ene_range_high();
  vector<vector<vector<vector<Real> > > >          CI    = frendy_obj.get_xs_contribute_coef();
  vector<vector<vector<vector<Real> > > >          XMTI  = frendy_obj.get_xs_contribute_reaction_type();
  vector<vector<vector<Integer> > >                MATS  = frendy_obj.get_relevant_mat_no();
  vector<vector<vector<Integer> > >                MTS   = frendy_obj.get_relevant_reaction_type();
  vector<vector<vector<Real> > >                   XMFS  = frendy_obj.get_relevant_file_no();
  vector<vector<vector<Real> > >                   XLFSS = frendy_obj.get_relevant_level_no();
  vector<vector<vector<vector<Real> > > >          EI    = frendy_obj.get_relevant_ene_data();
  vector<vector<vector<vector<Real> > > >          WEI   = frendy_obj.get_relevant_weight();
  vector<vector<vector<Integer> > >                LB    = frendy_obj.get_cov_matrix_data_flg();
  vector<vector<vector<vector<Real> > > >          E_K   = frendy_obj.get_cov_matrix_ene_k();
  vector<vector<vector<vector<vector<Real> > > > > F_K   = frendy_obj.get_cov_matrix_coef_k();
  vector<vector<vector<vector<Real> > > >          E_T   = frendy_obj.get_cov_matrix_ene_l();
  vector<vector<vector<vector<vector<Real> > > > > F_T   = frendy_obj.get_cov_matrix_coef_l();

  Integer mat_no = 0;
  if( LIS == 0 &&
      static_cast<int>(QM.size())    == 0 && static_cast<int>(QI.size())    == 0 &&
      static_cast<int>(IZAP.size())  == 0 && static_cast<int>(LFS.size())   == 0 &&
      static_cast<int>(XMF1.size())  == 0 && static_cast<int>(XLFS1.size()) == 0 &&
      static_cast<int>(MAT1.size())  == 0 && static_cast<int>(MT1.size())   == 0 &&
      static_cast<int>(LTY.size())   == 0 && static_cast<int>(E1.size())    == 0 &&
      static_cast<int>(E2.size())    == 0 && static_cast<int>(CI.size())    == 0 &&
      static_cast<int>(XMTI.size())  == 0 && static_cast<int>(MATS.size())  == 0 &&
      static_cast<int>(MTS.size())   == 0 && static_cast<int>(XMFS.size())  == 0 &&
      static_cast<int>(XLFSS.size()) == 0 && static_cast<int>(EI.size())    == 0 &&
      static_cast<int>(WEI.size())   == 0 && static_cast<int>(LB.size())    == 0 &&
      static_cast<int>(E_K.size())   == 0 && static_cast<int>(F_K.size())   == 0 &&
      static_cast<int>(E_T.size())   == 0 && static_cast<int>(F_T.size())   == 0 )
  {
    mat_no = unassigned_mat_no;
    mt_no  = unassigned_mt_no;
  }

  Integer NS = static_cast<Integer>(QM.size());
  vector<Integer>                   NL;
  vector<vector<Integer> >          NC, NI;
  vector<vector<vector<Integer> > > LT;
  int i_max = static_cast<int>(NS);
  NL.resize(i_max);
  NC.resize(i_max);
  NI.resize(i_max);
  LT.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    NL[i] = static_cast<Integer>(XMF1[i].size());
    
    int j_max = static_cast<int>(NL[i]);
    NC[i].resize(j_max);
    NI[i].resize(j_max);
    LT[i].resize(j_max);
    for(int j=0; j<j_max; j++)
    {
      NC[i][j] = static_cast<Integer>(E1[i][j].size());
      NI[i][j] = static_cast<Integer>(LB[i][j].size());

      int k_max = static_cast<int>(NI[i][j]);
      LT[i][j].resize(k_max);
      for(int k=0; k<k_max; k++)
      {
        if( LB[i][j][k] == 5 )
        {
          LT[i][j][k] = frendy_obj.get_symmetric_flg_angle()[i][j][k]; //LS
        }
        else if( LB[i][j][k] == 6 )
        {
          LT[i][j][k] = 0;
        }
        else
        {
          LT[i][j][k] = static_cast<Integer>(E_T[i][j][k].size());
        }
      }
    }
  }
  
  //Set ENDF format data
  endf_obj.clear();
  endf_obj.set_mat_no(mat_no);
  endf_obj.set_mt_no(mt_no);
  endf_obj.set_LIS(LIS);
  endf_obj.set_NS(NS);
  endf_obj.set_QM(QM);
  endf_obj.set_QI(QI);
  endf_obj.set_IZAP(IZAP);
  endf_obj.set_LFS(LFS);
  endf_obj.set_NL(NL);
  endf_obj.set_XMF1(XMF1);
  endf_obj.set_XLFS1(XLFS1);
  endf_obj.set_MAT1(MAT1);
  endf_obj.set_MT1(MT1);
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
  LIS   = 0;
  QM.clear();
  QI.clear();
  IZAP.clear();
  LFS.clear();
  clr_obj.clear_vec_array2_real(XMF1);
  clr_obj.clear_vec_array2_real(XLFS1);
  clr_obj.clear_vec_array2_int(MAT1);
  clr_obj.clear_vec_array2_int(MT1);
  clr_obj.clear_vec_array3_int(LTY);
  clr_obj.clear_vec_array3_real(E1);
  clr_obj.clear_vec_array3_real(E2);
  clr_obj.clear_vec_array4_real(CI);
  clr_obj.clear_vec_array4_real(XMTI);
  clr_obj.clear_vec_array3_int(MATS);
  clr_obj.clear_vec_array3_int(MTS);
  clr_obj.clear_vec_array3_real(XMFS);
  clr_obj.clear_vec_array3_real(XLFSS);
  clr_obj.clear_vec_array4_real(EI);
  clr_obj.clear_vec_array4_real(WEI);
  clr_obj.clear_vec_array3_int(LB);
  clr_obj.clear_vec_array4_real(E_K);
  clr_obj.clear_vec_array5_real(F_K);
  clr_obj.clear_vec_array4_real(E_T);
  clr_obj.clear_vec_array5_real(F_T);
  
  NS = 0;
  NL.clear();
  clr_obj.clear_vec_array2_int(NC);
  clr_obj.clear_vec_array2_int(NI);
  clr_obj.clear_vec_array3_int(LT);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//MF40Parser -> CovarianceRadioactiveProductDataContainer
void MF40Converter::convert_endf_format_to_frendy( MF40Parser& endf_obj, CovarianceRadioactiveProductDataContainer& frendy_obj )
{
  //Get frendy data
  Integer                                          reaction_type               = endf_obj.get_mt_no();
  Integer                                          state_no_target             = endf_obj.get_LIS();
  vector<Real>                                     q_value_mass                = endf_obj.get_QM();
  vector<Real>                                     q_value                     = endf_obj.get_QI();
  vector<Integer>                                  mat_data_product            = endf_obj.get_IZAP();
  vector<Integer>                                  state_no_product            = endf_obj.get_LFS();
  vector<vector<Real> >                            target_second_file_no       = endf_obj.get_XMF1();
  vector<vector<Real> >                            target_second_excited_state = endf_obj.get_XLFS1();
  vector<vector<Integer> >                         target_second_mat_no        = endf_obj.get_MAT1();
  vector<vector<Integer> >                         target_second_reaction_type = endf_obj.get_MT1();
  vector<vector<vector<Integer> > >                cov_matrix_flg              = endf_obj.get_LTY();
  vector<vector<vector<Real> > >                   xs_ene_range_low            = endf_obj.get_E1();
  vector<vector<vector<Real> > >                   xs_ene_range_high           = endf_obj.get_E2();
  vector<vector<vector<vector<Real> > > >          xs_contribute_coef          = endf_obj.get_CI();
  vector<vector<vector<vector<Real> > > >          xs_contribute_reaction_type = endf_obj.get_XMTI();
  vector<vector<vector<Integer> > >                relevant_mat_no             = endf_obj.get_MATS();
  vector<vector<vector<Integer> > >                relevant_reaction_type      = endf_obj.get_MTS();
  vector<vector<vector<Real> > >                   relevant_file_no            = endf_obj.get_XMFS();
  vector<vector<vector<Real> > >                   relevant_level_no           = endf_obj.get_XLFSS();
  vector<vector<vector<vector<Real> > > >          relevant_ene_data           = endf_obj.get_EI();
  vector<vector<vector<vector<Real> > > >          relevant_weight             = endf_obj.get_WEI();
  vector<vector<vector<Integer> > >                cov_matrix_data_flg         = endf_obj.get_LB();
  vector<vector<vector<vector<Real> > > >          cov_matrix_ene_k            = endf_obj.get_E_K();
  vector<vector<vector<vector<vector<Real> > > > > cov_matrix_coef_k           = endf_obj.get_F_K();
  vector<vector<vector<vector<Real> > > >          cov_matrix_ene_l            = endf_obj.get_E_T();
  vector<vector<vector<vector<vector<Real> > > > > cov_matrix_coef_l           = endf_obj.get_F_T();

  if( state_no_target == 0 &&
      static_cast<int>(q_value_mass.size())                == 0 &&
      static_cast<int>(q_value.size())                     == 0 &&
      static_cast<int>(mat_data_product.size())            == 0 &&
      static_cast<int>(state_no_product.size())            == 0 &&
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
      static_cast<int>(cov_matrix_coef_l.size()) == 0 )
  {
    reaction_type = unassigned_mt_no;
  }

  vector<vector<vector<Integer> > > symmetric_flg_angle;
  int i_max = static_cast<int>(cov_matrix_data_flg.size());
  symmetric_flg_angle.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(cov_matrix_data_flg[i].size());
    symmetric_flg_angle[i].resize(j_max);
    for(int j=0; j<j_max; j++)
    {
      int k_max = static_cast<int>(cov_matrix_data_flg[i][j].size());
      symmetric_flg_angle[i][j].resize(k_max);
      for(int k=0; k<k_max; k++)
      {
        symmetric_flg_angle[i][j][k] = 0;
        if( cov_matrix_data_flg[i][j][k] == 5 )
        {
          symmetric_flg_angle[i][j][k] = endf_obj.get_LS()[i][j][k];
        }
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
  frendy_obj.set_state_no_target(state_no_target);
  frendy_obj.set_q_value_mass(q_value_mass);
  frendy_obj.set_q_value(q_value);
  frendy_obj.set_mat_data_product(mat_data_product);
  frendy_obj.set_state_no_product(state_no_product);
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
  frendy_obj.set_symmetric_flg_angle(symmetric_flg_angle);
  frendy_obj.set_cov_matrix_ene_k(cov_matrix_ene_k);
  frendy_obj.set_cov_matrix_ene_l(cov_matrix_ene_l);
  frendy_obj.set_cov_matrix_coef_k(cov_matrix_coef_k);
  frendy_obj.set_cov_matrix_coef_l(cov_matrix_coef_l);

  //Clear declared data
  reaction_type               = 0;
  state_no_target             = 0;
  q_value_mass.clear();
  q_value.clear();
  mat_data_product.clear();
  state_no_product.clear();
  clr_obj.clear_vec_array2_real(target_second_file_no);
  clr_obj.clear_vec_array2_real(target_second_excited_state);
  clr_obj.clear_vec_array2_int(target_second_mat_no);
  clr_obj.clear_vec_array2_int(target_second_reaction_type);
  clr_obj.clear_vec_array3_int(cov_matrix_flg);
  clr_obj.clear_vec_array3_real(xs_ene_range_low);
  clr_obj.clear_vec_array3_real(xs_ene_range_high);
  clr_obj.clear_vec_array4_real(xs_contribute_coef);
  clr_obj.clear_vec_array4_real(xs_contribute_reaction_type);
  clr_obj.clear_vec_array3_int(relevant_mat_no);
  clr_obj.clear_vec_array3_int(relevant_reaction_type);
  clr_obj.clear_vec_array3_real(relevant_file_no);
  clr_obj.clear_vec_array3_real(relevant_level_no);
  clr_obj.clear_vec_array4_real(relevant_ene_data);
  clr_obj.clear_vec_array4_real(relevant_weight);
  clr_obj.clear_vec_array3_int(cov_matrix_data_flg);
  clr_obj.clear_vec_array3_int(symmetric_flg_angle);
  clr_obj.clear_vec_array4_real(cov_matrix_ene_k);
  clr_obj.clear_vec_array5_real(cov_matrix_coef_k);
  clr_obj.clear_vec_array4_real(cov_matrix_ene_l);
  clr_obj.clear_vec_array5_real(cov_matrix_coef_l);
}

