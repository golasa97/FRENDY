#include "EndfUtils/MFxxMTyyyConverter/MF06Converter.hpp"

using namespace frendy;

//constructor
MF06Converter::MF06Converter(void)
{
}

//destructor
MF06Converter::~MF06Converter(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//ProductDistributionDataContainer -> MF06Parser
void MF06Converter::convert_frendy_to_endf_format( ProductDistributionDataContainer& frendy_obj, MF06Parser& endf_obj )
{
  //Get frendy data
  Integer                                    mt_no         = frendy_obj.get_reaction_type();
  Integer                                    JPN           = frendy_obj.get_prompt_fis_n_flg();
  Integer                                    JPP           = frendy_obj.get_prompt_fis_p_flg();
  Integer                                    LCT           = frendy_obj.get_ref_frame_flg();
  vector<Real>                               ZAP           = frendy_obj.get_mat_data_product();
  vector<Real>                               AWP           = frendy_obj.get_mass_product();
  vector<Integer>                            LIP           = frendy_obj.get_product_mod_flg();
  vector<Integer>                            LAW           = frendy_obj.get_distr_func_flg();
  vector<vector<Integer> >                   INT_Y         = frendy_obj.get_product_distr_int_data();
  vector<vector<Integer> >                   NBT_Y         = frendy_obj.get_product_distr_range_data();
  vector<vector<Real> >                      E_INT_Y       = frendy_obj.get_product_distr_ene_data();
  vector<vector<Real> >                      Y_TAB         = frendy_obj.get_product_distr_data();

  Real                            TEMP   = frendy_obj.get_temp();
  vector<Real>                    EN     = frendy_obj.get_incident_ene();
  vector<vector<Real> >           EP     = frendy_obj.get_second_ene();
  vector<vector<Real> >           PP     = frendy_obj.get_incoherent_inelastic_scat_xs_integrate();
  vector<vector<vector<Real> > >  EPM    = frendy_obj.get_incoherent_inelastic_scat_xs_weight();
  vector<vector<Real> >           U      = frendy_obj.get_incoherent_elastic_scat_angle();
  Integer                         NBRAGG = frendy_obj.get_bragg_edge_no();
  Integer                         NNE    = static_cast<Integer>(EN.size());


  Integer mat_no = 0;
  if( LCT == 0 && 
      static_cast<int>(ZAP.size())     == 0 && static_cast<int>(AWP.size())   == 0 &&
      static_cast<int>(LAW.size())     == 0 && static_cast<int>(LIP.size())   == 0 &&
      static_cast<int>(INT_Y.size())   == 0 && static_cast<int>(NBT_Y.size()) == 0 &&
      static_cast<int>(E_INT_Y.size()) == 0 && static_cast<int>(Y_TAB.size()) == 0 )
  {
    mat_no = unassigned_mat_no;
    mt_no  = unassigned_mt_no;
  }

  vector<Integer>                            LANG_LAW01;
  vector<Integer>                            LEP_LAW01;
  vector<vector<Integer> >                   INT_E;
  vector<vector<Integer> >                   NBT_E;
  vector<vector<Integer> >                   ND_LAW01;
  vector<vector<Real> >                      E1_LAW01;
  vector<vector<vector<Real> > >             E2_LAW01;
  vector<vector<vector<vector<Real> > > >    B_LAW01;
  vector<vector<Integer> >                   LANG_LAW02;
  vector<vector<Real> >                      E_LAW02;
  vector<vector<vector<Real> > >             A_LAW02;
  vector<Real>                               SPI_LAW05;
  vector<Integer>                            LIDP_LAW05;
  vector<vector<Integer> >                   LTP_LAW05;
  vector<vector<Real> >                      E_LAW05;
  vector<vector<vector<Real> > >             B_LAW05;
  vector<vector<vector<Real> > >             RA_LAW05;
  vector<vector<vector<Real> > >             IA_LAW05;
  vector<vector<vector<Real> > >             P_LAW05;
  vector<Real>                               APSX_LAW06;
  vector<Integer>                            NPSX_LAW06;
  vector<vector<Real> >                      E_LAW07;
  vector<vector<vector<Real> > >             MU_LAW07;
  vector<vector<vector<Integer> > >          INT_MU_LAW07;
  vector<vector<vector<Integer> > >          NBT_MU_LAW07;
  vector<vector<vector<vector<Integer> > > > INT_F_LAW07;
  vector<vector<vector<vector<Integer> > > > NBT_F_LAW07;
  vector<vector<vector<vector<Real> > > >    E_INT_F_LAW07;
  vector<vector<vector<vector<Real> > > >    F_TAB_LAW07;

  Integer NK    = static_cast<Integer>(LIP.size());
  int     i_max = static_cast<int>(NK);
  LANG_LAW01.resize(i_max);
  LEP_LAW01.resize(i_max);
  INT_E.resize(i_max);
  NBT_E.resize(i_max);
  ND_LAW01.resize(i_max);
  E1_LAW01.resize(i_max);
  E2_LAW01.resize(i_max);
  B_LAW01.resize(i_max);
  LANG_LAW02.resize(i_max);
  E_LAW02.resize(i_max);
  A_LAW02.resize(i_max);
  A_LAW02.resize(i_max);
  A_LAW02.resize(i_max);
  SPI_LAW05.resize(i_max);
  LIDP_LAW05.resize(i_max);
  LTP_LAW05.resize(i_max);
  E_LAW05.resize(i_max);
  B_LAW05.resize(i_max);
  RA_LAW05.resize(i_max);
  IA_LAW05.resize(i_max);
  P_LAW05.resize(i_max);
  APSX_LAW06.resize(i_max);
  NPSX_LAW06.resize(i_max);
  E_LAW07.resize(i_max);
  MU_LAW07.resize(i_max);
  INT_MU_LAW07.resize(i_max);
  NBT_MU_LAW07.resize(i_max);
  INT_F_LAW07.resize(i_max);
  NBT_F_LAW07.resize(i_max);
  E_INT_F_LAW07.resize(i_max);
  F_TAB_LAW07.resize(i_max);
  
  vector<Integer> NE;
  vector<vector<Integer> > NL_LAW02;
  vector<vector<Integer> > NMU_LAW07;
  NE.resize(i_max);
  NL_LAW02.resize(i_max);
  NMU_LAW07.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    if( LAW[i] == 1 )
    {
      LANG_LAW01[i]    = frendy_obj.get_angular_repr_flg()[i];
      LEP_LAW01[i]     = frendy_obj.get_second_ene_int_data()[i];
      INT_E[i]         = frendy_obj.get_cont_int_data()[i];
      NBT_E[i]         = frendy_obj.get_cont_range_data()[i];
      ND_LAW01[i]      = frendy_obj.get_discrete_ene_no()[i];
      E1_LAW01[i]      = frendy_obj.get_cont_ene_a()[i];
      E2_LAW01[i]      = frendy_obj.get_cont_ene_b()[i];
      B_LAW01[i]       = frendy_obj.get_cont_data()[i];
      
      NE[i] = static_cast<Integer>(E1_LAW01[i].size());
    }
    else if( LAW[i] == 2 )
    {
      LANG_LAW02[i]    = frendy_obj.get_two_body_repr_flg()[i];
      INT_E[i]         = frendy_obj.get_two_body_int_data()[i];
      NBT_E[i]         = frendy_obj.get_two_body_range_data()[i];
      E_LAW02[i]       = frendy_obj.get_two_body_ene_data()[i];
      
      NE[i] = static_cast<Integer>(E_LAW02[i].size());
      int j_max = static_cast<int>(NE[i]);
      A_LAW02[i].resize(j_max);
      NL_LAW02[i].resize(j_max);
      for(int j=0; j<j_max; j++)
      {
        if( LANG_LAW02[i][j] == 0 )
        {
          A_LAW02[i][j] = frendy_obj.get_two_body_legendre_coef()[i][j];
          NL_LAW02[i][j] = static_cast<Integer>(A_LAW02[i][j].size());
        }
        else
        {
          NL_LAW02[i][j] = static_cast<Integer>(frendy_obj.get_two_body_cos()[i][j].size());
          
          int k_max = static_cast<int>(NL_LAW02[i][j]);
          A_LAW02[i][j].resize(k_max*2);
          for(int k=0; k<k_max; k++)
          {
            A_LAW02[i][j][2*k]   = frendy_obj.get_two_body_cos()[i][j][k];
            A_LAW02[i][j][2*k+1] = frendy_obj.get_two_body_prob()[i][j][k];
          }
        }
      }
    }
    else if( LAW[i] == 5 )
    {
      SPI_LAW05[i]     = frendy_obj.get_spin_particle()[i];
      LIDP_LAW05[i]    = frendy_obj.get_charged_particle_flg()[i];
      E_LAW05[i]       = frendy_obj.get_charged_particle_ene_data()[i];
      LTP_LAW05[i]     = frendy_obj.get_charged_particle_repr_flg()[i];
      INT_E[i]         = frendy_obj.get_charged_particle_int_data()[i];
      NBT_E[i]         = frendy_obj.get_charged_particle_range_data()[i];
      
      NE[i] = static_cast<Integer>(E_LAW05[i].size());
      int j_max = static_cast<int>(NE[i]);
      B_LAW05[i].resize(j_max);
      RA_LAW05[i].resize(j_max);
      IA_LAW05[i].resize(j_max);
      P_LAW05[i].resize(j_max);
      for(int j=0; j<j_max; j++)
      {
        if( LTP_LAW05[i][j] == 1 && LIDP_LAW05[i] == 0 )
        {
          B_LAW05[i][j]  = frendy_obj.get_charged_particle_coef_b()[i][j];
          RA_LAW05[i][j] = frendy_obj.get_charged_particle_coef_r()[i][j];
          IA_LAW05[i][j] = frendy_obj.get_charged_particle_coef_i()[i][j];
        }
        else if( LTP_LAW05[i][j] == 1 && LIDP_LAW05[i] == 1 )
        {
          B_LAW05[i][j]  = frendy_obj.get_charged_particle_coef_b()[i][j];
          RA_LAW05[i][j] = frendy_obj.get_charged_particle_coef_r()[i][j];
          IA_LAW05[i][j] = frendy_obj.get_charged_particle_coef_i()[i][j];
        }
        else if( LTP_LAW05[i][j] == 2 )
        {
          B_LAW05[i][j]  = frendy_obj.get_charged_particle_coef_c()[i][j];
        }
        else if( LTP_LAW05[i][j] > 2 )
        {
          B_LAW05[i][j] = frendy_obj.get_charged_particle_coef_mu()[i][j];
          P_LAW05[i][j]  = frendy_obj.get_charged_particle_coef_p()[i][j];
        }
      }
    }
    else if( LAW[i] == 6 )
    {
      APSX_LAW06[i]    = frendy_obj.get_n_body_mass()[i];
      NPSX_LAW06[i]    = frendy_obj.get_n_body_particle_no()[i];
    }
    else if( LAW[i] == 7 )
    {
      E_LAW07[i]       = frendy_obj.get_lab_ene()[i];
      INT_E[i]         = frendy_obj.get_lab_ene_int_data()[i]; 
      NBT_E[i]         = frendy_obj.get_lab_ene_range_data()[i];
      MU_LAW07[i]      = frendy_obj.get_lab_cos()[i];
      INT_MU_LAW07[i]  = frendy_obj.get_lab_cos_int_data()[i];
      NBT_MU_LAW07[i]  = frendy_obj.get_lab_cos_range_data()[i];
      INT_F_LAW07[i]   = frendy_obj.get_lab_int_data()[i];
      NBT_F_LAW07[i]   = frendy_obj.get_lab_range_data()[i];
      E_INT_F_LAW07[i] = frendy_obj.get_lab_ene_sec_data()[i];
      F_TAB_LAW07[i]   = frendy_obj.get_lab_data()[i];
      
      NE[i] = static_cast<Integer>(E_LAW07[i].size());
      int j_max = static_cast<int>(NE[i]);
      NMU_LAW07[i].resize(j_max);
      for(int j=0; j<j_max; j++)
      {
        NMU_LAW07[i][j] = static_cast<Integer>(MU_LAW07[i][j].size());
      }
    }
  }

  //Set ENDF format data
  endf_obj.clear();
  endf_obj.set_mat_no(mat_no);
  endf_obj.set_mt_no(mt_no);
  endf_obj.set_JPN(JPN);
  endf_obj.set_JPP(JPP);
  endf_obj.set_LCT(LCT);
  endf_obj.set_NK(NK);
  endf_obj.set_ZAP(ZAP);
  endf_obj.set_AWP(AWP);
  endf_obj.set_LIP(LIP);
  endf_obj.set_LAW(LAW);
  endf_obj.set_NBT_Y(NBT_Y);
  endf_obj.set_INT_Y(INT_Y);
  endf_obj.set_E_INT_Y(E_INT_Y);
  endf_obj.set_Y_TAB(Y_TAB);
  endf_obj.set_LANG_LAW01(LANG_LAW01);
  endf_obj.set_LEP_LAW01(LEP_LAW01);
  endf_obj.set_NE_LAW01(NE);
  endf_obj.set_NBT_E_LAW01(NBT_E);
  endf_obj.set_INT_E_LAW01(INT_E);
  endf_obj.set_E1_LAW01(E1_LAW01);
  endf_obj.set_ND_LAW01(ND_LAW01);
  endf_obj.set_E2_LAW01(E2_LAW01);
  endf_obj.set_B_LAW01(B_LAW01);
  endf_obj.set_NE_LAW02(NE);
  endf_obj.set_NBT_E_LAW02(NBT_E);
  endf_obj.set_INT_E_LAW02(INT_E);
  endf_obj.set_E_LAW02(E_LAW02);
  endf_obj.set_LANG_LAW02(LANG_LAW02);
  endf_obj.set_NL_LAW02(NL_LAW02);
  endf_obj.set_A_LAW02(A_LAW02);
  endf_obj.set_SPI_LAW05(SPI_LAW05);
  endf_obj.set_LIDP_LAW05(LIDP_LAW05);
  endf_obj.set_NE_LAW05(NE);
  endf_obj.set_NBT_E_LAW05(NBT_E);
  endf_obj.set_INT_E_LAW05(INT_E);
  endf_obj.set_E_LAW05(E_LAW05);
  endf_obj.set_LTP_LAW05(LTP_LAW05);
  endf_obj.set_B_LAW05(B_LAW05);
  endf_obj.set_RA_LAW05(RA_LAW05);
  endf_obj.set_IA_LAW05(IA_LAW05);
  endf_obj.set_P_LAW05(P_LAW05);
  endf_obj.set_APSX_LAW06(APSX_LAW06);
  endf_obj.set_NPSX_LAW06(NPSX_LAW06);
  endf_obj.set_NE_LAW07(NE);
  endf_obj.set_NBT_E_LAW07(NBT_E);
  endf_obj.set_INT_E_LAW07(INT_E);
  endf_obj.set_E_LAW07(E_LAW07);
  endf_obj.set_NMU_LAW07(NMU_LAW07);
  endf_obj.set_NBT_MU_LAW07(NBT_MU_LAW07);
  endf_obj.set_INT_MU_LAW07(INT_MU_LAW07);
  endf_obj.set_MU_LAW07(MU_LAW07);
  endf_obj.set_NBT_F_LAW07(NBT_F_LAW07);
  endf_obj.set_INT_F_LAW07(INT_F_LAW07);
  endf_obj.set_E_INT_F_LAW07(E_INT_F_LAW07);
  endf_obj.set_F_TAB_LAW07(F_TAB_LAW07);

  endf_obj.set_TEMP(TEMP);
  endf_obj.set_EN(EN);
  endf_obj.set_EP(EP);
  endf_obj.set_PP(PP);
  endf_obj.set_EPM(EPM);
  endf_obj.set_U(U);
  endf_obj.set_NBRAGG(NBRAGG);
  endf_obj.set_NNE(NNE);

  //Clear declared data
  mt_no         = 0;
  JPN           = 0;
  JPP           = 0;
  LCT           = 0;
  ZAP.clear();
  AWP.clear();
  LIP.clear();
  LAW.clear();
  clr_obj.clear_vec_array2_int(INT_Y);
  clr_obj.clear_vec_array2_int(NBT_Y);
  clr_obj.clear_vec_array2_real(E_INT_Y);
  clr_obj.clear_vec_array2_real(Y_TAB);
  LANG_LAW01.clear();
  LEP_LAW01.clear();
  clr_obj.clear_vec_array2_int(INT_E);
  clr_obj.clear_vec_array2_int(NBT_E);
  clr_obj.clear_vec_array2_int(ND_LAW01);
  clr_obj.clear_vec_array2_real(E1_LAW01);
  clr_obj.clear_vec_array3_real(E2_LAW01);
  clr_obj.clear_vec_array4_real(B_LAW01);
  clr_obj.clear_vec_array2_int(LANG_LAW02);
  clr_obj.clear_vec_array2_real(E_LAW02);
  clr_obj.clear_vec_array3_real(A_LAW02);
  clr_obj.clear_vec_array3_real(A_LAW02);
  clr_obj.clear_vec_array3_real(A_LAW02);
  SPI_LAW05.clear();
  LIDP_LAW05.clear();
  clr_obj.clear_vec_array2_int(LTP_LAW05);
  clr_obj.clear_vec_array3_real(B_LAW05);
  clr_obj.clear_vec_array3_real(RA_LAW05);
  clr_obj.clear_vec_array3_real(IA_LAW05);
  clr_obj.clear_vec_array3_real(P_LAW05);
  APSX_LAW06.clear();
  NPSX_LAW06.clear();
  clr_obj.clear_vec_array2_real(E_LAW07);
  clr_obj.clear_vec_array3_real(MU_LAW07);
  clr_obj.clear_vec_array3_int(INT_MU_LAW07);
  clr_obj.clear_vec_array3_int(NBT_MU_LAW07);
  clr_obj.clear_vec_array4_int(INT_F_LAW07);
  clr_obj.clear_vec_array4_int(NBT_F_LAW07);
  clr_obj.clear_vec_array4_real(E_INT_F_LAW07);
  clr_obj.clear_vec_array4_real(F_TAB_LAW07);
  
  NE.clear();
  clr_obj.clear_vec_array2_int(NL_LAW02);
  clr_obj.clear_vec_array2_int(NMU_LAW07);

  TEMP = 0.0;
  EN.clear();
  clr_obj.clear_vec_array2_real(EP);
  clr_obj.clear_vec_array2_real(PP);
  clr_obj.clear_vec_array3_real(EPM);
  clr_obj.clear_vec_array2_real(U);
  NBRAGG = 0;
  NNE    = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//MF06Parser -> ProductDistributionDataContainer
void MF06Converter::convert_endf_format_to_frendy( MF06Parser& endf_obj, ProductDistributionDataContainer& frendy_obj )
{
  //Get frendy data
  Integer                                    reaction_type               = endf_obj.get_mt_no();
  Integer                                    ref_frame_flg               = endf_obj.get_LCT();
  Integer                                    prompt_fis_n_flg            = endf_obj.get_JPN();
  Integer                                    prompt_fis_p_flg            = endf_obj.get_JPP();
  vector<Real>                               mat_data_product            = endf_obj.get_ZAP();
  vector<Real>                               mass_product                = endf_obj.get_AWP();
  vector<Integer>                            product_mod_flg             = endf_obj.get_LIP();
  vector<Integer>                            distr_func_flg              = endf_obj.get_LAW();
  vector<vector<Integer> >                   product_distr_int_data      = endf_obj.get_INT_Y();
  vector<vector<Integer> >                   product_distr_range_data    = endf_obj.get_NBT_Y();
  vector<vector<Real> >                      product_distr_ene_data      = endf_obj.get_E_INT_Y();
  vector<vector<Real> >                      product_distr_data          = endf_obj.get_Y_TAB();

  Real                            temp                                   = endf_obj.get_TEMP();
  vector<Real>                    incident_ene                           = endf_obj.get_EN();
  vector<vector<Real> >           second_ene                             = endf_obj.get_EP();
  vector<vector<Real> >           incoherent_inelastic_scat_xs_integrate = endf_obj.get_PP();
  vector<vector<vector<Real> > >  incoherent_inelastic_scat_xs_weight    = endf_obj.get_EPM();
  vector<vector<Real> >           incoherent_elastic_scat_angle          = endf_obj.get_U();
  Integer                         bragg_edge_no                          = endf_obj.get_NBRAGG();

  if( ref_frame_flg == 0 && 
      static_cast<int>(mat_data_product.size()) == 0 && static_cast<int>(mass_product.size())   == 0 &&
      static_cast<int>(product_mod_flg.size())  == 0 && static_cast<int>(distr_func_flg.size()) == 0 &&
      static_cast<int>(product_distr_int_data.size())   == 0 &&
      static_cast<int>(product_distr_range_data.size()) == 0 &&
      static_cast<int>(product_distr_ene_data.size())   == 0 &&
      static_cast<int>(product_distr_data.size())       == 0 )
  {
    reaction_type = unassigned_mt_no;
  }
  
  vector<Integer>                            angular_repr_flg;
  vector<Integer>                            second_ene_int_data;
  vector<vector<Integer> >                   cont_int_data;
  vector<vector<Integer> >                   cont_range_data;
  vector<vector<Integer> >                   discrete_ene_no;
  vector<vector<Real> >                      cont_ene_a;
  vector<vector<vector<Real> > >             cont_ene_b;
  vector<vector<vector<vector<Real> > > >    cont_data;
  vector<vector<Integer> >                   two_body_repr_flg;
  vector<vector<Integer> >                   two_body_int_data;
  vector<vector<Integer> >                   two_body_range_data;
  vector<vector<Real> >                      two_body_ene_data;
  vector<vector<vector<Real> > >             two_body_legendre_coef;
  vector<vector<vector<Real> > >             two_body_cos;
  vector<vector<vector<Real> > >             two_body_prob;
  vector<Real>                               spin_particle;
  vector<Integer>                            charged_particle_flg;
  vector<vector<Integer> >                   charged_particle_repr_flg;
  vector<vector<Real> >                      charged_particle_ene_data;
  vector<vector<Real> >                      charged_particle_mass_data;
  vector<vector<Integer> >                   charged_particle_int_data;
  vector<vector<Integer> >                   charged_particle_range_data;
  vector<vector<vector<Real> > >             charged_particle_coef_b;
  vector<vector<vector<Real> > >             charged_particle_coef_r;
  vector<vector<vector<Real> > >             charged_particle_coef_i;
  vector<vector<vector<Real> > >             charged_particle_coef_c;
  vector<vector<vector<Real> > >             charged_particle_coef_mu;
  vector<vector<vector<Real> > >             charged_particle_coef_p;
  vector<Real>                               n_body_mass;
  vector<Integer>                            n_body_particle_no;
  vector<vector<Real> >                      lab_ene;
  vector<vector<Integer> >                   lab_ene_int_data;
  vector<vector<Integer> >                   lab_ene_range_data;
  vector<vector<vector<Real> > >             lab_cos;
  vector<vector<vector<Integer> > >          lab_integrate_int_data;
  vector<vector<vector<Integer> > >          lab_integrate_range_data;
  vector<vector<vector<Real> > >             lab_integrate_cos_data;
  vector<vector<vector<Real> > >             lab_integrate_data;
  vector<vector<vector<Integer> > >          lab_cos_int_data;
  vector<vector<vector<Integer> > >          lab_cos_range_data;
  vector<vector<vector<vector<Integer> > > > lab_int_data;
  vector<vector<vector<vector<Integer> > > > lab_range_data;
  vector<vector<vector<vector<Real> > > >    lab_ene_sec_data;
  vector<vector<vector<vector<Real> > > >    lab_data;
  
  int i_max = static_cast<int>(product_mod_flg.size());
  angular_repr_flg.resize(i_max);
  second_ene_int_data.resize(i_max);
  cont_int_data.resize(i_max);
  cont_range_data.resize(i_max);
  discrete_ene_no.resize(i_max);
  cont_ene_a.resize(i_max);
  cont_ene_b.resize(i_max);
  cont_data.resize(i_max);
  two_body_repr_flg.resize(i_max);
  two_body_int_data.resize(i_max);
  two_body_range_data.resize(i_max);
  two_body_ene_data.resize(i_max);
  two_body_legendre_coef.resize(i_max);
  two_body_cos.resize(i_max);
  two_body_prob.resize(i_max);
  spin_particle.resize(i_max);
  charged_particle_flg.resize(i_max);
  charged_particle_repr_flg.resize(i_max);
  charged_particle_ene_data.resize(i_max);
  charged_particle_mass_data.resize(i_max);
  charged_particle_int_data.resize(i_max);
  charged_particle_range_data.resize(i_max);
  charged_particle_coef_b.resize(i_max);
  charged_particle_coef_r.resize(i_max);
  charged_particle_coef_i.resize(i_max);
  charged_particle_coef_c.resize(i_max);
  charged_particle_coef_mu.resize(i_max);
  charged_particle_coef_p.resize(i_max);
  n_body_mass.resize(i_max);
  n_body_particle_no.resize(i_max);
  lab_ene.resize(i_max);
  lab_ene_int_data.resize(i_max);
  lab_ene_range_data.resize(i_max);
  lab_cos.resize(i_max);
  lab_integrate_int_data.resize(i_max);
  lab_integrate_range_data.resize(i_max);
  lab_integrate_cos_data.resize(i_max);
  lab_integrate_data.resize(i_max);
  lab_cos_int_data.resize(i_max);
  lab_cos_range_data.resize(i_max);
  lab_int_data.resize(i_max);
  lab_range_data.resize(i_max);
  lab_ene_sec_data.resize(i_max);
  lab_data.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    if( distr_func_flg[i] == 1 )
    {
      angular_repr_flg[i]    = endf_obj.get_LANG_LAW01()[i];
      second_ene_int_data[i] = endf_obj.get_LEP_LAW01()[i];
      cont_int_data[i]       = endf_obj.get_INT_E_LAW01()[i];
      cont_range_data[i]     = endf_obj.get_NBT_E_LAW01()[i];
      discrete_ene_no[i]     = endf_obj.get_ND_LAW01()[i];
      cont_ene_a[i]          = endf_obj.get_E1_LAW01()[i];
      cont_ene_b[i]          = endf_obj.get_E2_LAW01()[i];
      cont_data[i]           = endf_obj.get_B_LAW01()[i];
    }
    else if( distr_func_flg[i] == 2 )
    {
      two_body_repr_flg[i]   = endf_obj.get_LANG_LAW02()[i];
      two_body_int_data[i]   = endf_obj.get_INT_E_LAW02()[i];
      two_body_range_data[i] = endf_obj.get_NBT_E_LAW02()[i];
      two_body_ene_data[i]   = endf_obj.get_E_LAW02()[i];
      
      int j_max = static_cast<int>(two_body_ene_data[i].size());
      two_body_legendre_coef[i].resize(j_max);
      two_body_cos[i].resize(j_max);
      two_body_prob[i].resize(j_max);
      for(int j=0; j<j_max; j++)
      {
        if( two_body_repr_flg[i][j] == 0 )
        {
          two_body_legendre_coef[i][j] = endf_obj.get_A_LAW02()[i][j];
        }
        else
        {
          int k_max = static_cast<int>(endf_obj.get_A_LAW02()[i][j].size());
          k_max = k_max / 2;
          two_body_cos[i][j].resize(k_max);
          two_body_prob[i][j].resize(k_max);
          for(int k=0; k<k_max; k++)
          {
            two_body_cos[i][j][k]  = endf_obj.get_A_LAW02()[i][j][2*k];
            two_body_prob[i][j][k] = endf_obj.get_A_LAW02()[i][j][2*k+1];
          }
        }
      }
    }
    else if( distr_func_flg[i] == 5 )
    {
      spin_particle[i]               = endf_obj.get_SPI_LAW05()[i];
      charged_particle_flg[i]        = endf_obj.get_LIDP_LAW05()[i];
      charged_particle_repr_flg[i]   = endf_obj.get_LTP_LAW05()[i];
      charged_particle_ene_data[i]   = endf_obj.get_E_LAW05()[i];
      charged_particle_int_data[i]   = endf_obj.get_INT_E_LAW05()[i];
      charged_particle_range_data[i] = endf_obj.get_NBT_E_LAW05()[i];
      
      int j_max = static_cast<int>(charged_particle_ene_data[i].size());
      charged_particle_coef_b[i].resize(j_max);
      charged_particle_coef_r[i].resize(j_max);
      charged_particle_coef_i[i].resize(j_max);
      charged_particle_coef_c[i].resize(j_max);
      charged_particle_coef_mu[i].resize(j_max);
      charged_particle_coef_p[i].resize(j_max);
      for(int j=0; j<j_max; j++)
      {
        if( charged_particle_repr_flg[i][j] == 1 && charged_particle_flg[i] == 0 )
        {
          charged_particle_coef_b[i][j] = endf_obj.get_B_LAW05()[i][j];
          charged_particle_coef_r[i][j] = endf_obj.get_RA_LAW05()[i][j];
          charged_particle_coef_i[i][j] = endf_obj.get_IA_LAW05()[i][j];
        }
        else if( charged_particle_repr_flg[i][j] == 1 && charged_particle_flg[i] == 1 )
        {
          charged_particle_coef_b[i][j] = endf_obj.get_B_LAW05()[i][j];
          charged_particle_coef_r[i][j] = endf_obj.get_RA_LAW05()[i][j];
          charged_particle_coef_i[i][j] = endf_obj.get_IA_LAW05()[i][j];
        }
        else if( charged_particle_repr_flg[i][j] == 2 )
        {
          charged_particle_coef_c[i][j] = endf_obj.get_C_LAW05()[i][j];
        }
        else if( charged_particle_repr_flg[i][j] > 2 )
        {
          charged_particle_coef_mu[i][j] = endf_obj.get_MU_LAW05()[i][j];
          charged_particle_coef_p[i][j]  = endf_obj.get_P_LAW05()[i][j];;
        }
      }
    }
    else if( distr_func_flg[i] == 6 )
    {
      n_body_mass[i]        = endf_obj.get_APSX_LAW06()[i];
      n_body_particle_no[i] = endf_obj.get_NPSX_LAW06()[i];
    }
    else if( distr_func_flg[i] == 7 )
    {
      lab_ene[i]            = endf_obj.get_E_LAW07()[i];
      lab_ene_int_data[i]   = endf_obj.get_INT_E_LAW07()[i];
      lab_ene_range_data[i] = endf_obj.get_NBT_E_LAW07()[i];
      lab_cos[i]            = endf_obj.get_MU_LAW07()[i];
      lab_cos_int_data[i]   = endf_obj.get_INT_MU_LAW07()[i];
      lab_cos_range_data[i] = endf_obj.get_NBT_MU_LAW07()[i];
      lab_int_data[i]       = endf_obj.get_INT_F_LAW07()[i];
      lab_range_data[i]     = endf_obj.get_NBT_F_LAW07()[i];
      lab_ene_sec_data[i]   = endf_obj.get_E_INT_F_LAW07()[i];
      lab_data[i]           = endf_obj.get_F_TAB_LAW07()[i];
    }
  }

  //Set ENDF format data
  //frendy_obj.clear();
  //text
  //mat_no
  frendy_obj.set_reaction_type(reaction_type);
  //ZA
  //AWR
  frendy_obj.set_prompt_fis_n_flg(prompt_fis_n_flg);
  frendy_obj.set_prompt_fis_p_flg(prompt_fis_p_flg);
  frendy_obj.set_ref_frame_flg(ref_frame_flg);
  frendy_obj.set_mat_data_product(mat_data_product);
  frendy_obj.set_mass_product(mass_product);
  frendy_obj.set_product_mod_flg(product_mod_flg);
  frendy_obj.set_distr_func_flg(distr_func_flg);
  frendy_obj.set_product_distr_range_data(product_distr_range_data);
  frendy_obj.set_product_distr_int_data(product_distr_int_data);
  frendy_obj.set_product_distr_ene_data(product_distr_ene_data);
  frendy_obj.set_product_distr_data(product_distr_data);
  frendy_obj.set_angular_repr_flg(angular_repr_flg);
  frendy_obj.set_second_ene_int_data(second_ene_int_data);
  frendy_obj.set_cont_int_data(cont_int_data);
  frendy_obj.set_cont_range_data(cont_range_data);
  frendy_obj.set_cont_ene_a(cont_ene_a);
  frendy_obj.set_discrete_ene_no(discrete_ene_no);
  frendy_obj.set_cont_ene_b(cont_ene_b);
  frendy_obj.set_cont_data(cont_data);
  frendy_obj.set_two_body_range_data(two_body_range_data);
  frendy_obj.set_two_body_int_data(two_body_int_data);
  frendy_obj.set_two_body_ene_data(two_body_ene_data);
  frendy_obj.set_two_body_repr_flg(two_body_repr_flg);
  frendy_obj.set_two_body_legendre_coef(two_body_legendre_coef);
  frendy_obj.set_two_body_cos(two_body_cos);
  frendy_obj.set_two_body_prob(two_body_prob);
  frendy_obj.set_spin_particle(spin_particle);
  frendy_obj.set_charged_particle_flg(charged_particle_flg);
  frendy_obj.set_charged_particle_ene_data(charged_particle_ene_data);
  frendy_obj.set_charged_particle_mass_data(charged_particle_mass_data);
  frendy_obj.set_charged_particle_range_data(charged_particle_range_data);
  frendy_obj.set_charged_particle_int_data(charged_particle_int_data);
  frendy_obj.set_charged_particle_repr_flg(charged_particle_repr_flg);
  frendy_obj.set_charged_particle_coef_b(charged_particle_coef_b);
  frendy_obj.set_charged_particle_coef_r(charged_particle_coef_r);
  frendy_obj.set_charged_particle_coef_i(charged_particle_coef_i);
  frendy_obj.set_charged_particle_coef_c(charged_particle_coef_c);
  frendy_obj.set_charged_particle_coef_mu(charged_particle_coef_mu);
  frendy_obj.set_charged_particle_coef_p(charged_particle_coef_p);
  frendy_obj.set_n_body_mass(n_body_mass);
  frendy_obj.set_n_body_particle_no(n_body_particle_no);
  frendy_obj.set_lab_ene_int_data(lab_ene_int_data);
  frendy_obj.set_lab_ene_range_data(lab_ene_range_data);
  frendy_obj.set_lab_ene(lab_ene);
  frendy_obj.set_lab_cos_range_data(lab_cos_range_data);
  frendy_obj.set_lab_cos_int_data(lab_cos_int_data);
  frendy_obj.set_lab_integrate_int_data(lab_integrate_int_data);
  frendy_obj.set_lab_integrate_range_data(lab_integrate_range_data);
  frendy_obj.set_lab_integrate_cos_data(lab_integrate_cos_data);
  frendy_obj.set_lab_integrate_data(lab_integrate_data);
  frendy_obj.set_lab_cos(lab_cos);
  frendy_obj.set_lab_range_data(lab_range_data);
  frendy_obj.set_lab_int_data(lab_int_data);
  frendy_obj.set_lab_ene_sec_data(lab_ene_sec_data);
  frendy_obj.set_lab_data(lab_data);

  frendy_obj.set_temp(temp);
  frendy_obj.set_incident_ene(incident_ene);
  frendy_obj.set_second_ene(second_ene);
  frendy_obj.set_incoherent_inelastic_scat_xs_integrate(incoherent_inelastic_scat_xs_integrate);
  frendy_obj.set_incoherent_inelastic_scat_xs_weight(incoherent_inelastic_scat_xs_weight);
  frendy_obj.set_incoherent_elastic_scat_angle(incoherent_elastic_scat_angle);
  frendy_obj.set_bragg_edge_no(bragg_edge_no);

  //Clear declared data
  reaction_type               = 0;
  prompt_fis_n_flg            = 0;
  prompt_fis_p_flg            = 0;
  ref_frame_flg               = 0;
  mat_data_product.clear();
  mass_product.clear();
  product_mod_flg.clear();
  distr_func_flg.clear();
  clr_obj.clear_vec_array2_int(product_distr_int_data);
  clr_obj.clear_vec_array2_int(product_distr_range_data);
  clr_obj.clear_vec_array2_real(product_distr_ene_data);
  clr_obj.clear_vec_array2_real(product_distr_data);
  angular_repr_flg.clear();
  second_ene_int_data.clear();
  clr_obj.clear_vec_array2_int(cont_int_data);
  clr_obj.clear_vec_array2_int(cont_range_data);
  clr_obj.clear_vec_array2_int(discrete_ene_no);
  clr_obj.clear_vec_array2_real(cont_ene_a);
  clr_obj.clear_vec_array3_real(cont_ene_b);
  clr_obj.clear_vec_array4_real(cont_data);
  clr_obj.clear_vec_array2_int(two_body_repr_flg);
  clr_obj.clear_vec_array2_int(two_body_int_data);
  clr_obj.clear_vec_array2_int(two_body_range_data);
  clr_obj.clear_vec_array2_real(two_body_ene_data);
  clr_obj.clear_vec_array3_real(two_body_legendre_coef);
  clr_obj.clear_vec_array3_real(two_body_cos);
  clr_obj.clear_vec_array3_real(two_body_prob);
  spin_particle.clear();
  charged_particle_flg.clear();
  clr_obj.clear_vec_array2_int(charged_particle_repr_flg);
  clr_obj.clear_vec_array2_int(charged_particle_int_data);
  clr_obj.clear_vec_array2_int(charged_particle_range_data);
  clr_obj.clear_vec_array3_real(charged_particle_coef_b);
  clr_obj.clear_vec_array3_real(charged_particle_coef_r);
  clr_obj.clear_vec_array3_real(charged_particle_coef_i);
  clr_obj.clear_vec_array3_real(charged_particle_coef_c);
  clr_obj.clear_vec_array3_real(charged_particle_coef_mu);
  clr_obj.clear_vec_array3_real(charged_particle_coef_p);
  n_body_mass.clear();
  n_body_particle_no.clear();
  clr_obj.clear_vec_array2_real(lab_ene);
  clr_obj.clear_vec_array2_int(lab_ene_int_data);
  clr_obj.clear_vec_array2_int(lab_ene_range_data);
  clr_obj.clear_vec_array3_real(lab_cos);
  clr_obj.clear_vec_array3_int(lab_integrate_int_data);
  clr_obj.clear_vec_array3_int(lab_integrate_range_data);
  clr_obj.clear_vec_array3_real(lab_integrate_cos_data);
  clr_obj.clear_vec_array3_real(lab_integrate_data);
  clr_obj.clear_vec_array3_int(lab_cos_int_data);
  clr_obj.clear_vec_array3_int(lab_cos_range_data);
  clr_obj.clear_vec_array4_int(lab_int_data);
  clr_obj.clear_vec_array4_int(lab_range_data);
  clr_obj.clear_vec_array4_real(lab_ene_sec_data);
  clr_obj.clear_vec_array4_real(lab_data);

  temp = 0.0;
  incident_ene.clear();
  clr_obj.clear_vec_array2_real(second_ene);
  clr_obj.clear_vec_array2_real(incoherent_inelastic_scat_xs_integrate);
  clr_obj.clear_vec_array3_real(incoherent_inelastic_scat_xs_weight);
  clr_obj.clear_vec_array2_real(incoherent_elastic_scat_angle);
  bragg_edge_no = 0;
}

