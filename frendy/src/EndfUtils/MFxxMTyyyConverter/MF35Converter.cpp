#include "EndfUtils/MFxxMTyyyConverter/MF35Converter.hpp"

using namespace frendy;

//constructor
MF35Converter::MF35Converter(void)
{
}

//destructor
MF35Converter::~MF35Converter(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//CovarianceEnergyAngularDataContainer -> MF35Parser
void MF35Converter::convert_frendy_to_endf_format( CovarianceEnergyAngularDataContainer& frendy_obj, MF35Parser& endf_obj )
{
  //Get frendy data
  Integer                        mt_no = frendy_obj.get_reaction_type();
  vector<Real>                   E1    = frendy_obj.get_ene_range_low();
  vector<Real>                   E2    = frendy_obj.get_ene_range_high();
  vector<Integer>                LS    = frendy_obj.get_symmetric_flg_ene();
  vector<Integer>                LB    = frendy_obj.get_cov_matrix_data_flg_ene();
  vector<vector<Real> >          E_K   = frendy_obj.get_cov_matrix_ene_data();
  vector<vector<vector<Real> > > F_K   = frendy_obj.get_cov_matrix_data();

  Integer mat_no = 0;
  if( static_cast<int>(E1.size())  == 0 && static_cast<int>(E2.size())  == 0 &&
      static_cast<int>(LS.size())  == 0 && static_cast<int>(LB.size())  == 0 &&
      static_cast<int>(E_K.size()) == 0 && static_cast<int>(F_K.size()) == 0 )
  {
    mat_no = unassigned_mat_no;
    mt_no  = unassigned_mt_no;
  }

  Integer NK = static_cast<Integer>(E1.size());
  vector<Integer> NT, NE;
  
  int i_max = static_cast<int>(NK);
  NT.resize(i_max);
  NE.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    if( LB[i] == 5 || LB[i] == 7 )
    {
      if( LS[i] == 0 )
      {
        NE[i] = static_cast<Integer>(E_K[i].size());
        NT[i] = NE[i] * (NE[i] - 1) + 1;
      }
      else if( LS[i] == 1 )
      {
        NE[i] = static_cast<Integer>(E_K[i].size());
        NT[i] = NE[i] * (NE[i] + 1) / 2;
      }
    }
    //LB = 7 is only supported in MF=35
    /*else if( (LB[i] >= 0 && LB[i] <= 4) || LB[i] == 8 || LB[i] == 9 )
    {
      NE[i] = static_cast<Integer>(E_K[i].size()) + LS[i];
      NT[i] = 2 * NE[i];
    }
    else if( LB[i] == 6 )
    {
      NE[i] = static_cast<Integer>(E_K[i].size());
      NT[i] = static_cast<Integer>(E_T[i].size()) * NE[i] + 1;
    }*/
  }

  //Set ENDF format data
  endf_obj.clear();
  endf_obj.set_mat_no(mat_no);
  endf_obj.set_mt_no(mt_no);
  endf_obj.set_NK(NK);
  endf_obj.set_E1(E1);
  endf_obj.set_E2(E2);
  endf_obj.set_LS(LS);
  endf_obj.set_LB(LB);
  endf_obj.set_NT(NT);
  endf_obj.set_NE(NE);
  endf_obj.set_E_K(E_K);
  endf_obj.set_F_K(F_K);

  //Clear declared data
  mt_no = 0;
  E1.clear();
  E2.clear();
  LS.clear();
  LB.clear();
  clr_obj.clear_vec_array2_real(E_K);
  clr_obj.clear_vec_array3_real(F_K);
  
  NK = 0;
  NT.clear();
  NE.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//MF35Parser -> CovarianceEnergyAngularDataContainer
void MF35Converter::convert_endf_format_to_frendy( MF35Parser& endf_obj, CovarianceEnergyAngularDataContainer& frendy_obj )
{
  //Get frendy data
  Integer                        reaction_type           = endf_obj.get_mt_no();
  vector<Real>                   ene_range_low           = endf_obj.get_E1();
  vector<Real>                   ene_range_high          = endf_obj.get_E2();
  vector<Integer>                symmetric_flg_ene       = endf_obj.get_LS();
  vector<Integer>                cov_matrix_data_flg_ene = endf_obj.get_LB();
  vector<vector<Real> >          cov_matrix_ene_data     = endf_obj.get_E_K();
  vector<vector<vector<Real> > > cov_matrix_data         = endf_obj.get_F_K();

  if( static_cast<int>(ene_range_low.size()) == 0 && static_cast<int>(ene_range_high.size()) == 0 &&
      static_cast<int>(symmetric_flg_ene.size())       == 0 &&
      static_cast<int>(cov_matrix_data_flg_ene.size()) == 0 &&
      static_cast<int>(cov_matrix_ene_data.size())     == 0 &&
      static_cast<int>(cov_matrix_data.size())         == 0 )
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
  frendy_obj.set_ene_range_low(ene_range_low);
  frendy_obj.set_ene_range_high(ene_range_high);
  frendy_obj.set_symmetric_flg_ene(symmetric_flg_ene);
  frendy_obj.set_cov_matrix_data_flg_ene(cov_matrix_data_flg_ene);
  frendy_obj.set_cov_matrix_ene_data(cov_matrix_ene_data);
  frendy_obj.set_cov_matrix_data(cov_matrix_data);

  //Clear declared data
  reaction_type = 0;
  ene_range_low.clear();
  ene_range_high.clear();
  symmetric_flg_ene.clear();
  cov_matrix_data_flg_ene.clear();
  clr_obj.clear_vec_array2_real(cov_matrix_ene_data);
  clr_obj.clear_vec_array3_real(cov_matrix_data);
}

