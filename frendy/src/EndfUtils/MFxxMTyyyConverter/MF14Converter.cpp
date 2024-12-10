#include "EndfUtils/MFxxMTyyyConverter/MF14Converter.hpp"

using namespace frendy;

//constructor
MF14Converter::MF14Converter(void)
{
}

//destructor
MF14Converter::~MF14Converter(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//PhotonDataContainer -> MF14Parser
void MF14Converter::convert_frendy_to_endf_format( PhotonDataContainer& frendy_obj, MF14Parser& endf_obj )
{
  //Get frendy data
  Integer                           mt_no    = frendy_obj.get_reaction_type();
  Integer                           LI       = frendy_obj.get_isotropic_flg();
  Integer                           LTT      = frendy_obj.get_angular_repr_flg();
  Integer                           NI       = frendy_obj.get_iso_photon_angular_no();
  vector<Real>                      ES       = frendy_obj.get_angular_ene_level();
  vector<Real>                      EG       = frendy_obj.get_angular_photon_ene();
  vector<vector<Integer> >          INT_E    = frendy_obj.get_angular_ene_int_data();
  vector<vector<Integer> >          NBT_E    = frendy_obj.get_angular_ene_range_data();
  vector<vector<Real> >             E        = frendy_obj.get_angular_ene_data();
  vector<vector<vector<Real> > >    A        = frendy_obj.get_angular_legendre_coef_data();
  vector<vector<vector<Integer> > > INT_P    = frendy_obj.get_angular_probability_int_data();
  vector<vector<vector<Integer> > > NBT_P    = frendy_obj.get_angular_probability_range_data();
  vector<vector<vector<Real> > >    P_TAB    = frendy_obj.get_angular_probability_cos_data();
  vector<vector<vector<Real> > >    MU_INT_P = frendy_obj.get_angular_probability_data();

  Integer mat_no = 0;
  if( LI == 0 && LTT == 0 && NI == 0 &&
      static_cast<int>(ES.size())    == 0 && static_cast<int>(EG.size())       == 0 &&
      static_cast<int>(INT_E.size()) == 0 && static_cast<int>(NBT_E.size())    == 0 &&
      static_cast<int>(E.size())     == 0 && static_cast<int>(A.size())        == 0 &&
      static_cast<int>(INT_P.size()) == 0 && static_cast<int>(NBT_P.size())    == 0 &&
      static_cast<int>(P_TAB.size()) == 0 && static_cast<int>(MU_INT_P.size()) == 0 )
  {
    mat_no = unassigned_mat_no;
    mt_no  = unassigned_mt_no;
  }

  Integer         NK = static_cast<Integer>(EG.size());
  vector<Integer> NE;
  
  if( LI == 0 )
  {
    int i_max = static_cast<int>(NK);
    NE.resize(i_max);
    for(int i=0; i<i_max; i++)
    {
      NE[i] = static_cast<Integer>(E[i].size());
    }
  }
  else
  {
    NK = 1;
  }
  
  //Set ENDF format data
  endf_obj.clear();
  endf_obj.set_mat_no(mat_no);
  endf_obj.set_mt_no(mt_no);
  endf_obj.set_LI(LI);
  endf_obj.set_NK(NK);
  endf_obj.set_LTT(LTT);
  endf_obj.set_NI(NI);
  endf_obj.set_EG(EG);
  endf_obj.set_ES(ES);
  endf_obj.set_NE(NE);
  endf_obj.set_NBT_E(NBT_E);
  endf_obj.set_INT_E(INT_E);
  endf_obj.set_E(E);
  endf_obj.set_A(A);
  endf_obj.set_NBT_P(NBT_P);
  endf_obj.set_INT_P(INT_P);
  endf_obj.set_MU_INT_P(MU_INT_P);
  endf_obj.set_P_TAB(P_TAB);

  //Clear declared data
  mt_no    = 0;
  LI       = 0;
  LTT      = 0;
  NI       = 0;
  ES.clear();
  EG.clear();
  clr_obj.clear_vec_array2_int(INT_E);
  clr_obj.clear_vec_array2_int(NBT_E);
  clr_obj.clear_vec_array2_real(E);
  clr_obj.clear_vec_array3_real(A);
  clr_obj.clear_vec_array3_int(INT_P);
  clr_obj.clear_vec_array3_int(NBT_P);
  clr_obj.clear_vec_array3_real(P_TAB);
  clr_obj.clear_vec_array3_real(MU_INT_P);
  
  NK = 0;
  NE.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//MF14Parser -> PhotonDataContainer
void MF14Converter::convert_endf_format_to_frendy( MF14Parser& endf_obj, PhotonDataContainer& frendy_obj )
{
  //Get frendy data
  Integer                           reaction_type                  = endf_obj.get_mt_no();
  Integer                           isotropic_flg                  = endf_obj.get_LI();
  Integer                           angular_repr_flg               = endf_obj.get_LTT();
  Integer                           iso_photon_angular_no          = endf_obj.get_NI();
  vector<Real>                      angular_ene_level              = endf_obj.get_ES();
  vector<Real>                      angular_photon_ene             = endf_obj.get_EG();
  vector<vector<Integer> >          angular_ene_int_data           = endf_obj.get_INT_E();
  vector<vector<Integer> >          angular_ene_range_data         = endf_obj.get_NBT_E();
  vector<vector<Real> >             angular_ene_data               = endf_obj.get_E();
  vector<vector<vector<Real> > >    angular_legendre_coef_data     = endf_obj.get_A();
  vector<vector<vector<Integer> > > angular_probability_int_data   = endf_obj.get_INT_P();
  vector<vector<vector<Integer> > > angular_probability_range_data = endf_obj.get_NBT_P();
  vector<vector<vector<Real> > >    angular_probability_cos_data   = endf_obj.get_P_TAB();
  vector<vector<vector<Real> > >    angular_probability_data       = endf_obj.get_MU_INT_P();

  if( isotropic_flg == 0 && angular_repr_flg == 0 && iso_photon_angular_no == 0 &&
      static_cast<int>(angular_ene_level.size())              == 0 &&
      static_cast<int>(angular_photon_ene.size())             == 0 &&
      static_cast<int>(angular_ene_int_data.size())           == 0 &&
      static_cast<int>(angular_ene_range_data.size())         == 0 &&
      static_cast<int>(angular_ene_data.size())               == 0 &&
      static_cast<int>(angular_legendre_coef_data.size())     == 0 &&
      static_cast<int>(angular_probability_int_data.size())   == 0 &&
      static_cast<int>(angular_probability_range_data.size()) == 0 &&
      static_cast<int>(angular_probability_cos_data.size())   == 0 &&
      static_cast<int>(angular_probability_data.size())       == 0 )
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
  frendy_obj.set_isotropic_flg(isotropic_flg);
  frendy_obj.set_angular_repr_flg(angular_repr_flg);
  frendy_obj.set_iso_photon_angular_no(iso_photon_angular_no);
  frendy_obj.set_angular_photon_ene(angular_photon_ene);
  frendy_obj.set_angular_ene_level(angular_ene_level);
  frendy_obj.set_angular_ene_range_data(angular_ene_range_data);
  frendy_obj.set_angular_ene_int_data(angular_ene_int_data);
  frendy_obj.set_angular_ene_data(angular_ene_data);
  frendy_obj.set_angular_legendre_coef_data(angular_legendre_coef_data);
  frendy_obj.set_angular_probability_range_data(angular_probability_range_data);
  frendy_obj.set_angular_probability_int_data(angular_probability_int_data);
  frendy_obj.set_angular_probability_data(angular_probability_data);
  frendy_obj.set_angular_probability_cos_data(angular_probability_cos_data);

  //Clear declared data
  reaction_type                  = 0;
  isotropic_flg                  = 0;
  angular_repr_flg               = 0;
  iso_photon_angular_no          = 0;
  angular_ene_level.clear();
  angular_photon_ene.clear();
  clr_obj.clear_vec_array2_int(angular_ene_int_data);
  clr_obj.clear_vec_array2_int(angular_ene_range_data);
  clr_obj.clear_vec_array2_real(angular_ene_data);
  clr_obj.clear_vec_array3_real(angular_legendre_coef_data);
  clr_obj.clear_vec_array3_int(angular_probability_int_data);
  clr_obj.clear_vec_array3_int(angular_probability_range_data);
  clr_obj.clear_vec_array3_real(angular_probability_cos_data);
  clr_obj.clear_vec_array3_real(angular_probability_data);
}

