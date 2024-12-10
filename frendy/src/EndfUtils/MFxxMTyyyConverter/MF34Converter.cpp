#include "EndfUtils/MFxxMTyyyConverter/MF34Converter.hpp"

using namespace frendy;

//constructor
MF34Converter::MF34Converter(void)
{
}

//destructor
MF34Converter::~MF34Converter(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//CovarianceEnergyAngularDataContainer -> MF34Parser
void MF34Converter::convert_frendy_to_endf_format( CovarianceEnergyAngularDataContainer& frendy_obj, MF34Parser& endf_obj )
{
  //Get frendy data
  Integer                                                   mt_no = frendy_obj.get_reaction_type();
  Integer                                                   LTT   = frendy_obj.get_angular_repr_flg();
  vector<Integer>                                           MAT1  = frendy_obj.get_mat_no_target();
  vector<Integer>                                           MT1   = frendy_obj.get_reaction_type_target();
  vector<vector<vector<Integer> > >                         L     = frendy_obj.get_legendre_coef_index();
  vector<vector<vector<Integer> > >                         L1    = frendy_obj.get_legendre_coef_index_target();
  vector<vector<vector<Integer> > >                         LCT   = frendy_obj.get_ref_frame_flg();
  vector<vector<vector<vector<Integer> > > >                LS    = frendy_obj.get_symmetric_flg_angle();
  vector<vector<vector<vector<Integer> > > >                LB    = frendy_obj.get_cov_matrix_data_flg_angle();
  vector<vector<vector<vector<vector<Real> > > > >          E_K   = frendy_obj.get_cov_matrix_ene_angle_k();
  vector<vector<vector<vector<vector<vector<Real> > > > > > F_K   = frendy_obj.get_cov_matrix_coef_angle_k();
  vector<vector<vector<vector<vector<Real> > > > >          E_T   = frendy_obj.get_cov_matrix_ene_angle_l();
  vector<vector<vector<vector<vector<vector<Real> > > > > > F_T   = frendy_obj.get_cov_matrix_coef_angle_l();

  Integer mat_no = 0;
  if( LTT == 0 &&
      static_cast<int>(MAT1.size()) == 0 && static_cast<int>(MT1.size()) == 0 &&
      static_cast<int>(L.size())    == 0 && static_cast<int>(L1.size())  == 0 &&
      static_cast<int>(LCT.size())  == 0 && static_cast<int>(LS.size())  == 0 &&
      static_cast<int>(LB.size())   == 0 && static_cast<int>(E_K.size()) == 0 &&
      static_cast<int>(F_K.size())  == 0 && static_cast<int>(E_T.size()) == 0 &&
      static_cast<int>(F_T.size())  == 0 )
  {
    mat_no = unassigned_mat_no;
    mt_no  = unassigned_mt_no;
  }

  Integer NMT1 = static_cast<Integer>(MAT1.size());
  vector<Integer>                            NL, NL1, NSS;
  vector<vector<vector<Integer> > >          NI;
  vector<vector<vector<vector<Integer> > > > NT, NE;
  
  int i_max = static_cast<int>(NMT1);
  NL.resize(i_max);
  NL1.resize(i_max);
  NSS.resize(i_max);
  NI.resize(i_max);
  NT.resize(i_max);
  NE.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    NL[i] = static_cast<Integer>(L[i].size());
    NSS[i] = 1;
    NL1[i] = 1;

    int j_max = static_cast<int>(NL[i]);
    if( j_max > 1 )
    {
      if( L[i][0].size() != L[i][1].size() )
      {
        NSS[i] = NL[i] * (NL[i] + 1) / 2;
      }
      else
      {
        NL1[i] = static_cast<Integer>(L[i][0].size());
        NSS[i] = NL[i] * NL1[i];
      }
    }
    
    NI[i].resize(j_max);
    NT[i].resize(j_max);
    NE[i].resize(j_max);
    for(int j=0; j<j_max; j++)
    {
      int k_max = static_cast<int>(L[i][j].size());
      NI[i][j].resize(k_max);
      NT[i][j].resize(k_max);
      NE[i][j].resize(k_max);
      for(int k=0; k<k_max; k++)
      {
        NI[i][j][k] = static_cast<Integer>(LS[i][j][k].size());
        
        int l_max = static_cast<int>(NI[i][j][k]);
        NT[i][j][k].resize(l_max);
        NE[i][j][k].resize(l_max);
        for(int l=0; l<l_max; l++)
        {
          if( LB[i][j][k][l] == 0 || LB[i][j][k][l] == 1 || LB[i][j][k][l] == 2 )
          {
            NE[i][j][k][l] = static_cast<Integer>(E_K[i][j][k][l].size()) + LS[i][j][k][l];
            NT[i][j][k][l] = 2 * NE[i][j][k][l];
          }
          else if( LB[i][j][k][l] == 5 )
          {
            NE[i][j][k][l] = static_cast<Integer>(E_K[i][j][k][l].size());
            if( LS[i][j][k][l] == 0 )
            {
              NT[i][j][k][l] = NE[i][j][k][l] * ( NE[i][j][k][l] - 1 ) + 1;
            }
            else
            {
              NT[i][j][k][l] = NE[i][j][k][l] * ( NE[i][j][k][l] + 1 ) / 2;
            }
          }
          else if( LB[i][j][k][l] == 6 )
          {
            NE[i][j][k][l] = static_cast<Integer>(E_K[i][j][k][l].size());
            NT[i][j][k][l] = static_cast<Integer>(E_T[i][j][k][l].size()) * NE[i][j][k][l] + 1;
          }
        }
      }
    }
  }

  //Set ENDF format data
  endf_obj.clear();
  endf_obj.set_mat_no(mat_no);
  endf_obj.set_mt_no(mt_no);
  endf_obj.set_LTT(LTT);
  endf_obj.set_NMT1(NMT1);
  endf_obj.set_MAT1(MAT1);
  endf_obj.set_MT1(MT1);
  endf_obj.set_NL(NL);
  endf_obj.set_NL1(NL1);
  endf_obj.set_NSS(NSS);
  endf_obj.set_L(L);
  endf_obj.set_L1(L1);
  endf_obj.set_LCT(LCT);
  endf_obj.set_NI(NI);
  endf_obj.set_LS(LS);
  endf_obj.set_LB(LB);
  endf_obj.set_NT(NT);
  endf_obj.set_NE(NE);
  endf_obj.set_E_K(E_K);
  endf_obj.set_E_T(E_T);
  endf_obj.set_F_K(F_K);
  endf_obj.set_F_T(F_T);

  //Clear declared data
  mt_no = 0;
  LTT   = 0;
  MAT1.clear();
  MT1.clear();
  clr_obj.clear_vec_array3_int(L);
  clr_obj.clear_vec_array3_int(L1);
  clr_obj.clear_vec_array3_int(LCT);
  clr_obj.clear_vec_array4_int(LS);
  clr_obj.clear_vec_array4_int(LB);
  clr_obj.clear_vec_array5_real(E_K);
  clr_obj.clear_vec_array6_real(F_K);
  clr_obj.clear_vec_array5_real(E_T);
  clr_obj.clear_vec_array6_real(F_T);
  
  
  NMT1 = 0;
  NL.clear();
  NL1.clear();
  NSS.clear();
  clr_obj.clear_vec_array3_int(NI);
  clr_obj.clear_vec_array4_int(NT);
  clr_obj.clear_vec_array4_int(NE);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//MF34Parser -> CovarianceEnergyAngularDataContainer
void MF34Converter::convert_endf_format_to_frendy( MF34Parser& endf_obj, CovarianceEnergyAngularDataContainer& frendy_obj )
{
  //Get frendy data
  Integer                                                   reaction_type              = endf_obj.get_mt_no();
  Integer                                                   angular_repr_flg           = endf_obj.get_LTT();
  vector<Integer>                                           mat_no_target              = endf_obj.get_MAT1();
  vector<Integer>                                           reaction_type_target       = endf_obj.get_MT1();
  vector<vector<vector<Integer> > >                         legendre_coef_index        = endf_obj.get_L();
  vector<vector<vector<Integer> > >                         legendre_coef_index_target = endf_obj.get_L1();
  vector<vector<vector<Integer> > >                         ref_frame_flg              = endf_obj.get_LCT();
  vector<vector<vector<vector<Integer> > > >                symmetric_flg_angle        = endf_obj.get_LS();
  vector<vector<vector<vector<Integer> > > >                cov_matrix_data_flg_angle  = endf_obj.get_LB();
  vector<vector<vector<vector<vector<Real> > > > >          cov_matrix_ene_angle_k     = endf_obj.get_E_K();
  vector<vector<vector<vector<vector<vector<Real> > > > > > cov_matrix_coef_angle_k    = endf_obj.get_F_K();
  vector<vector<vector<vector<vector<Real> > > > >          cov_matrix_ene_angle_l     = endf_obj.get_E_T();
  vector<vector<vector<vector<vector<vector<Real> > > > > > cov_matrix_coef_angle_l    = endf_obj.get_F_T();

  if( angular_repr_flg == 0 &&
      static_cast<int>(mat_no_target.size())              == 0 &&
      static_cast<int>(reaction_type_target.size())       == 0 &&
      static_cast<int>(legendre_coef_index.size())        == 0 &&
      static_cast<int>(legendre_coef_index_target.size()) == 0 &&
      static_cast<int>(ref_frame_flg.size())              == 0 &&
      static_cast<int>(symmetric_flg_angle.size())        == 0 &&
      static_cast<int>(cov_matrix_data_flg_angle.size())  == 0 &&
      static_cast<int>(cov_matrix_ene_angle_k.size())     == 0 &&
      static_cast<int>(cov_matrix_coef_angle_k.size())    == 0 &&
      static_cast<int>(cov_matrix_ene_angle_l.size())     == 0 &&
      static_cast<int>(cov_matrix_coef_angle_l.size())    == 0 )
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
  frendy_obj.set_angular_repr_flg(angular_repr_flg);
  frendy_obj.set_mat_no_target(mat_no_target);
  frendy_obj.set_reaction_type_target(reaction_type_target);
  frendy_obj.set_legendre_coef_index(legendre_coef_index);
  frendy_obj.set_legendre_coef_index_target(legendre_coef_index_target);
  frendy_obj.set_ref_frame_flg(ref_frame_flg);
  frendy_obj.set_symmetric_flg_angle(symmetric_flg_angle);
  frendy_obj.set_cov_matrix_data_flg_angle(cov_matrix_data_flg_angle);
  frendy_obj.set_cov_matrix_ene_angle_k(cov_matrix_ene_angle_k);
  frendy_obj.set_cov_matrix_ene_angle_l(cov_matrix_ene_angle_l);
  frendy_obj.set_cov_matrix_coef_angle_k(cov_matrix_coef_angle_k);
  frendy_obj.set_cov_matrix_coef_angle_l(cov_matrix_coef_angle_l);

  //Clear declared data
  reaction_type              = 0;
  angular_repr_flg           = 0;
  mat_no_target.clear();
  reaction_type_target.clear();
  clr_obj.clear_vec_array3_int(legendre_coef_index);
  clr_obj.clear_vec_array3_int(legendre_coef_index_target);
  clr_obj.clear_vec_array3_int(ref_frame_flg);
  clr_obj.clear_vec_array4_int(symmetric_flg_angle);
  clr_obj.clear_vec_array4_int(cov_matrix_data_flg_angle);
  clr_obj.clear_vec_array5_real(cov_matrix_ene_angle_k);
  clr_obj.clear_vec_array6_real(cov_matrix_coef_angle_k);
  clr_obj.clear_vec_array5_real(cov_matrix_ene_angle_l);
  clr_obj.clear_vec_array6_real(cov_matrix_coef_angle_l);
}

