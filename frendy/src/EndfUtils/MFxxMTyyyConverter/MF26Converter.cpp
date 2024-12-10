#include "EndfUtils/MFxxMTyyyConverter/MF26Converter.hpp"

using namespace frendy;

//constructor
MF26Converter::MF26Converter(void)
{
}

//destructor
MF26Converter::~MF26Converter(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//ProductDistributionDataContainer -> MF26Parser
void MF26Converter::convert_frendy_to_endf_format( ProductDistributionDataContainer& frendy_obj, MF26Parser& endf_obj )
{
  //Get frendy data
  Integer                                 mt_no          = frendy_obj.get_reaction_type();
  vector<Real>                            ZAP            = frendy_obj.get_mat_data_second_product();
  vector<Integer>                         LAW            = frendy_obj.get_second_distr_func_flg();
  vector<vector<Integer> >                INT_Y          = frendy_obj.get_second_distr_yield_int_data();
  vector<vector<Integer> >                NBT_Y          = frendy_obj.get_second_distr_yield_range_data();
  vector<vector<Real> >                   E_INT_Y        = frendy_obj.get_second_distr_yield_ene_data();
  vector<vector<Real> >                   Y_TAB          = frendy_obj.get_second_distr_yield_data();

  Integer mat_no = 0;
  if( static_cast<int>(ZAP.size())     == 0 && static_cast<int>(LAW.size())   == 0 &&
      static_cast<int>(INT_Y.size())   == 0 && static_cast<int>(NBT_Y.size()) == 0 &&
      static_cast<int>(E_INT_Y.size()) == 0 && static_cast<int>(Y_TAB.size()) == 0 )
  {
    mat_no = unassigned_mat_no;
    mt_no  = unassigned_mt_no;
  }

  Integer NK = static_cast<Integer>(ZAP.size());
  vector<Integer>                         NE;
  vector<vector<Integer> >                INT_E;
  vector<vector<Integer> >                NBT_E;
  vector<Integer>                         LANG_LAW01;
  vector<Integer>                         LEP_LAW01;
  vector<vector<Integer> >                ND_LAW01;
  vector<vector<Real> >                   E1_LAW01;
  vector<vector<vector<Real> > >          E2_LAW01;
  vector<vector<vector<vector<Real> > > > B_LAW01;
  vector<vector<Integer> >                LANG_LAW02;
  vector<vector<Integer> >                NL_LAW02;
  vector<vector<Real> >                   E_LAW02;
  vector<vector<vector<Real> > >          A_LAW02;
  vector<vector<Integer> >                INT_ET;
  vector<vector<Integer> >                NBT_ET;
  vector<vector<Real> >                   E_INT_ET;
  vector<vector<Real> >                   ET_TAB;
  
  int i_max = static_cast<int>(NK);
  NE.resize(i_max);
  INT_E.resize(i_max);
  NBT_E.resize(i_max);
  LANG_LAW01.resize(i_max);
  LEP_LAW01.resize(i_max);
  ND_LAW01.resize(i_max);
  E1_LAW01.resize(i_max);
  E2_LAW01.resize(i_max);
  B_LAW01.resize(i_max);
  LANG_LAW02.resize(i_max);
  NL_LAW02.resize(i_max);
  E_LAW02.resize(i_max);
  A_LAW02.resize(i_max);
  INT_ET.resize(i_max);
  NBT_ET.resize(i_max);
  E_INT_ET.resize(i_max);
  ET_TAB.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    if( LAW[i] == 1 )
    {
      LANG_LAW01[i] = frendy_obj.get_second_distr_angular_repr_flg()[i];
      LEP_LAW01[i]  = frendy_obj.get_second_distr_ene_int_data()[i];
      ND_LAW01[i]   = frendy_obj.get_second_distr_discrete_ene_no()[i];
      E1_LAW01[i]   = frendy_obj.get_second_distr_cont_ene_a()[i];
      E2_LAW01[i]   = frendy_obj.get_second_distr_cont_ene_b()[i];
      B_LAW01[i]    = frendy_obj.get_second_distr_cont_data()[i];
      
      NE[i]         = static_cast<Integer>(E1_LAW01[i].size());
      INT_E[i]      = frendy_obj.get_second_distr_cont_int_data()[i];
      NBT_E[i]      = frendy_obj.get_second_distr_cont_range_data()[i];
    }
    else if( LAW[i] == 2 )
    {
      E_LAW02[i]    = frendy_obj.get_second_distr_two_body_ene_data()[i];
      LANG_LAW02[i] = frendy_obj.get_second_distr_two_body_repr_flg()[i];
  
      NE[i]    = static_cast<Integer>(E_LAW02[i].size());
      INT_E[i] = frendy_obj.get_second_distr_two_body_int_data()[i];
      NBT_E[i] = frendy_obj.get_second_distr_two_body_range_data()[i];
      
      int j_max = static_cast<int>(NE[i]);
      NL_LAW02[i].resize(j_max);
      A_LAW02[i].resize(j_max);
      for(int j=0; j<j_max; j++)
      {
        if( LANG_LAW02[i][j] == 0 )
        {
          A_LAW02[i][j] = frendy_obj.get_second_distr_two_body_legendre_coef()[i][j];
          NL_LAW02[i][j] = static_cast<Integer>(A_LAW02[i][j].size());
        }
        else
        {
          NL_LAW02[i][j] = static_cast<Integer>(frendy_obj.get_second_distr_two_body_cos()[i][j].size());
          
          int k_max = static_cast<int>(NL_LAW02[i][j]);
          A_LAW02[i][j].resize(2*k_max);
          for(int k=0; k<k_max; k++)
          {
            A_LAW02[i][j][2*k]   = frendy_obj.get_second_distr_two_body_cos()[i][j][k];
            A_LAW02[i][j][2*k+1] = frendy_obj.get_second_distr_two_body_prob()[i][j][k];
          }
        }
      }
    }
    else if( LAW[i] == 8 )
    {
      NE[i]       = 0;
      INT_ET[i]   = frendy_obj.get_second_distr_transfer_int_data()[i];
      NBT_ET[i]   = frendy_obj.get_second_distr_transfer_range_data()[i];
      E_INT_ET[i] = frendy_obj.get_second_distr_transfer_ene_data()[i];
      ET_TAB[i]   = frendy_obj.get_second_distr_transfer_data()[i];
    }
  }
  
  
  //Set ENDF format data
  endf_obj.clear();
  endf_obj.set_mat_no(mat_no);
  endf_obj.set_mt_no(mt_no);
  endf_obj.set_NK(NK);
  endf_obj.set_ZAP(ZAP);
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
  endf_obj.set_E_LAW02(E_LAW02);
  endf_obj.set_LANG_LAW02(LANG_LAW02);
  endf_obj.set_NL_LAW02(NL_LAW02);
  endf_obj.set_A_LAW02(A_LAW02);
  endf_obj.set_NBT_ET_LAW08(NBT_ET);
  endf_obj.set_INT_ET_LAW08(INT_ET);
  endf_obj.set_E_INT_ET_LAW08(E_INT_ET);
  endf_obj.set_ET_TAB_LAW08(ET_TAB);

  //Clear declared data
  mt_no = 0;
  NK    = 0;
  ZAP.clear();
  LAW.clear();
  clr_obj.clear_vec_array2_int(INT_Y);
  clr_obj.clear_vec_array2_int(NBT_Y);
  clr_obj.clear_vec_array2_real(E_INT_Y);
  clr_obj.clear_vec_array2_real(Y_TAB);
  clr_obj.clear_vec_array2_int(INT_E);
  clr_obj.clear_vec_array2_int(NBT_E);
  NE.clear();
  LANG_LAW01.clear();
  LEP_LAW01.clear();
  clr_obj.clear_vec_array2_int(ND_LAW01);
  clr_obj.clear_vec_array2_real(E1_LAW01);
  clr_obj.clear_vec_array3_real(E2_LAW01);
  clr_obj.clear_vec_array2_int(LANG_LAW02);
  clr_obj.clear_vec_array2_int(NL_LAW02);
  clr_obj.clear_vec_array4_real(B_LAW01);
  clr_obj.clear_vec_array2_real(E_LAW02);
  clr_obj.clear_vec_array3_real(A_LAW02);
  clr_obj.clear_vec_array2_int(INT_ET);
  clr_obj.clear_vec_array2_int(NBT_ET);
  clr_obj.clear_vec_array2_real(E_INT_ET);
  clr_obj.clear_vec_array2_real(ET_TAB);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//MF26Parser -> ProductDistributionDataContainer
void MF26Converter::convert_endf_format_to_frendy( MF26Parser& endf_obj, ProductDistributionDataContainer& frendy_obj )
{
  //Get frendy data
  Integer                                 reaction_type                       = endf_obj.get_mt_no();
  vector<Real>                            mat_data_second_product             = endf_obj.get_ZAP();
  vector<Integer>                         second_distr_func_flg               = endf_obj.get_LAW();
  vector<vector<Integer> >                second_distr_yield_int_data         = endf_obj.get_INT_Y();
  vector<vector<Integer> >                second_distr_yield_range_data       = endf_obj.get_NBT_Y();
  vector<vector<Real> >                   second_distr_yield_ene_data         = endf_obj.get_E_INT_Y();
  vector<vector<Real> >                   second_distr_yield_data             = endf_obj.get_Y_TAB();
  vector<Integer>                         second_distr_angular_repr_flg       = endf_obj.get_LANG_LAW01();
  vector<Integer>                         second_distr_ene_int_data           = endf_obj.get_LEP_LAW01();
  vector<vector<Integer> >                second_distr_discrete_ene_no        = endf_obj.get_ND_LAW01();
  vector<vector<Real> >                   second_distr_cont_ene_a             = endf_obj.get_E1_LAW01();
  vector<vector<vector<Real> > >          second_distr_cont_ene_b             = endf_obj.get_E2_LAW01();
  vector<vector<vector<vector<Real> > > > second_distr_cont_data              = endf_obj.get_B_LAW01();
  vector<vector<Integer> >                second_distr_two_body_repr_flg      = endf_obj.get_LANG_LAW02();
  vector<vector<Real> >                   second_distr_two_body_ene_data      = endf_obj.get_E_LAW02();
  vector<vector<Integer> >                second_distr_transfer_int_data      = endf_obj.get_INT_ET_LAW08();
  vector<vector<Integer> >                second_distr_transfer_range_data    = endf_obj.get_NBT_ET_LAW08();
  vector<vector<Real> >                   second_distr_transfer_ene_data      = endf_obj.get_E_INT_ET_LAW08();
  vector<vector<Real> >                   second_distr_transfer_data          = endf_obj.get_ET_TAB_LAW08();

  if( static_cast<int>(mat_data_second_product.size())          == 0 &&
      static_cast<int>(second_distr_func_flg.size())            == 0 &&
      static_cast<int>(second_distr_yield_int_data.size())      == 0 &&
      static_cast<int>(second_distr_yield_range_data.size())    == 0 &&
      static_cast<int>(second_distr_yield_ene_data.size())      == 0 &&
      static_cast<int>(second_distr_yield_data.size())          == 0 &&
      static_cast<int>(second_distr_angular_repr_flg.size())    == 0 &&
      static_cast<int>(second_distr_ene_int_data.size())        == 0 &&
      static_cast<int>(second_distr_discrete_ene_no.size())     == 0 &&
      static_cast<int>(second_distr_cont_ene_a.size())          == 0 &&
      static_cast<int>(second_distr_cont_ene_b.size())          == 0 &&
      static_cast<int>(second_distr_cont_data.size())           == 0 &&
      static_cast<int>(second_distr_two_body_repr_flg.size())   == 0 &&
      static_cast<int>(second_distr_two_body_ene_data.size())   == 0 &&
      static_cast<int>(second_distr_transfer_int_data.size())   == 0 &&
      static_cast<int>(second_distr_transfer_range_data.size()) == 0 &&
      static_cast<int>(second_distr_transfer_ene_data.size())   == 0 &&
      static_cast<int>(second_distr_transfer_data.size())       == 0 )
  {
    reaction_type = unassigned_mt_no;
  }

  vector<vector<Integer> >                second_distr_cont_int_data;
  vector<vector<Integer> >                second_distr_cont_range_data;
  vector<vector<Integer> >                second_distr_two_body_int_data;
  vector<vector<Integer> >                second_distr_two_body_range_data;
  vector<vector<vector<Real> > >          second_distr_two_body_legendre_coef;
  vector<vector<vector<Real> > >          second_distr_two_body_cos;
  vector<vector<vector<Real> > >          second_distr_two_body_prob;
  
  int i_max = static_cast<int>(second_distr_func_flg.size());
  second_distr_cont_int_data.resize(i_max);
  second_distr_cont_range_data.resize(i_max);
  second_distr_two_body_int_data.resize(i_max);
  second_distr_two_body_range_data.resize(i_max);
  second_distr_two_body_legendre_coef.resize(i_max);
  second_distr_two_body_cos.resize(i_max);
  second_distr_two_body_prob.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    if( second_distr_func_flg[i] == 1 )
    {
      second_distr_cont_int_data[i]   = endf_obj.get_INT_E_LAW01()[i];
      second_distr_cont_range_data[i] = endf_obj.get_NBT_E_LAW01()[i];
    }
    else if( second_distr_func_flg[i] == 2 )
    {
      second_distr_two_body_int_data[i]   = endf_obj.get_INT_E_LAW02()[i];
      second_distr_two_body_range_data[i] = endf_obj.get_NBT_E_LAW02()[i];

      int j_max = static_cast<int>(second_distr_two_body_repr_flg[i].size());
      second_distr_two_body_legendre_coef[i].resize(j_max);
      second_distr_two_body_cos[i].resize(j_max);
      second_distr_two_body_prob[i].resize(j_max);
      for(int j=0; j<j_max; j++)
      {
        if( second_distr_two_body_repr_flg[i][j] == 0 )
        {
          second_distr_two_body_legendre_coef[i][j] = endf_obj.get_A_LAW02()[i][j];
        }
        else
        {
          int k_max = static_cast<int>(endf_obj.get_NL_LAW02()[i][j]);
          second_distr_two_body_cos[i][j].resize(k_max);
          second_distr_two_body_prob[i][j].resize(k_max);
          for(int k=0; k<k_max; k++)
          {
            second_distr_two_body_cos[i][j][k]  = endf_obj.get_A_LAW02()[i][j][2*k];
            second_distr_two_body_prob[i][j][k] = endf_obj.get_A_LAW02()[i][j][2*k+1];
          }
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
  frendy_obj.set_mat_data_second_product(mat_data_second_product);
  frendy_obj.set_second_distr_func_flg(second_distr_func_flg);
  frendy_obj.set_second_distr_yield_range_data(second_distr_yield_range_data);
  frendy_obj.set_second_distr_yield_int_data(second_distr_yield_int_data);
  frendy_obj.set_second_distr_yield_ene_data(second_distr_yield_ene_data);
  frendy_obj.set_second_distr_yield_data(second_distr_yield_data);
  frendy_obj.set_second_distr_angular_repr_flg(second_distr_angular_repr_flg);
  frendy_obj.set_second_distr_ene_int_data(second_distr_ene_int_data);
  frendy_obj.set_second_distr_cont_range_data(second_distr_cont_range_data);
  frendy_obj.set_second_distr_cont_int_data(second_distr_cont_int_data);
  frendy_obj.set_second_distr_cont_ene_a(second_distr_cont_ene_a);
  frendy_obj.set_second_distr_discrete_ene_no(second_distr_discrete_ene_no);
  frendy_obj.set_second_distr_cont_ene_b(second_distr_cont_ene_b);
  frendy_obj.set_second_distr_cont_data(second_distr_cont_data);
  frendy_obj.set_second_distr_two_body_range_data(second_distr_two_body_range_data);
  frendy_obj.set_second_distr_two_body_int_data(second_distr_two_body_int_data);
  frendy_obj.set_second_distr_two_body_ene_data(second_distr_two_body_ene_data);
  frendy_obj.set_second_distr_two_body_repr_flg(second_distr_two_body_repr_flg);
  frendy_obj.set_second_distr_two_body_legendre_coef(second_distr_two_body_legendre_coef);
  frendy_obj.set_second_distr_two_body_cos(second_distr_two_body_cos);
  frendy_obj.set_second_distr_two_body_prob(second_distr_two_body_prob);
  frendy_obj.set_second_distr_transfer_int_data(second_distr_transfer_int_data);
  frendy_obj.set_second_distr_transfer_range_data(second_distr_transfer_range_data);
  frendy_obj.set_second_distr_transfer_ene_data(second_distr_transfer_ene_data);
  frendy_obj.set_second_distr_transfer_data(second_distr_transfer_data);

  //Clear declared data
  reaction_type = 0;
  mat_data_second_product.clear();
  second_distr_func_flg.clear();
  clr_obj.clear_vec_array2_int(second_distr_yield_int_data);
  clr_obj.clear_vec_array2_int(second_distr_yield_range_data);
  clr_obj.clear_vec_array2_real(second_distr_yield_ene_data);
  clr_obj.clear_vec_array2_real(second_distr_yield_data);
  second_distr_angular_repr_flg.clear();
  second_distr_ene_int_data.clear();
  clr_obj.clear_vec_array2_int(second_distr_cont_int_data);
  clr_obj.clear_vec_array2_int(second_distr_cont_range_data);
  clr_obj.clear_vec_array2_int(second_distr_discrete_ene_no);
  clr_obj.clear_vec_array2_real(second_distr_cont_ene_a);
  clr_obj.clear_vec_array3_real(second_distr_cont_ene_b);
  clr_obj.clear_vec_array4_real(second_distr_cont_data);
  clr_obj.clear_vec_array2_int(second_distr_two_body_repr_flg);
  clr_obj.clear_vec_array2_int(second_distr_two_body_int_data);
  clr_obj.clear_vec_array2_int(second_distr_two_body_range_data);
  clr_obj.clear_vec_array2_real(second_distr_two_body_ene_data);
  clr_obj.clear_vec_array3_real(second_distr_two_body_legendre_coef);
  clr_obj.clear_vec_array3_real(second_distr_two_body_cos);
  clr_obj.clear_vec_array3_real(second_distr_two_body_prob);
  clr_obj.clear_vec_array2_int(second_distr_transfer_int_data);
  clr_obj.clear_vec_array2_int(second_distr_transfer_range_data);
  clr_obj.clear_vec_array2_real(second_distr_transfer_ene_data);
  clr_obj.clear_vec_array2_real(second_distr_transfer_data);
}

