#include "EndfUtils/MFxxMTyyyConverter/MF13Converter.hpp"

using namespace frendy;

//constructor
MF13Converter::MF13Converter(void)
{
}

//destructor
MF13Converter::~MF13Converter(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//PhotonDataContainer -> MF13Parser
void MF13Converter::convert_frendy_to_endf_format( PhotonDataContainer& frendy_obj, MF13Parser& endf_obj )
{
  //Get frendy data
  Integer                  mt_no       = frendy_obj.get_reaction_type();
  Integer                  NK          = frendy_obj.get_ene_level_no();
  vector<Real>             ES          = frendy_obj.get_photon_ene();
  vector<Real>             EG          = frendy_obj.get_binding_ene();
  vector<Integer>          LP          = frendy_obj.get_binding_ene_flg();
  vector<Integer>          LF          = frendy_obj.get_distr_law_no();
  vector<Integer>          INT_S_TOT   = frendy_obj.get_photon_production_xs_tot_int_data();
  vector<Integer>          NBT_S_TOT   = frendy_obj.get_photon_production_xs_tot_range_data();
  vector<Real>             E_INT_S_TOT = frendy_obj.get_photon_production_xs_tot_ene_data();
  vector<Real>             S_TOT_TAB   = frendy_obj.get_photon_production_xs_tot_data();
  vector<vector<Integer> > INT_S_K     = frendy_obj.get_photon_production_xs_int_data();
  vector<vector<Integer> > NBT_S_K     = frendy_obj.get_photon_production_xs_range_data();
  vector<vector<Real> >    E_INT_S_K   = frendy_obj.get_photon_production_xs_ene_data();
  vector<vector<Real> >    S_K_TAB     = frendy_obj.get_photon_production_xs_data();

  Integer mat_no = 0;
  if( NK == 0 && 
      static_cast<int>(ES.size())          == 0 && static_cast<int>(EG.size())        == 0 &&
      static_cast<int>(LP.size())          == 0 && static_cast<int>(LF.size())        == 0 &&
      static_cast<int>(INT_S_TOT.size())   == 0 && static_cast<int>(NBT_S_TOT.size()) == 0 &&
      static_cast<int>(E_INT_S_TOT.size()) == 0 && static_cast<int>(S_TOT_TAB.size()) == 0 &&
      static_cast<int>(INT_S_K.size())     == 0 && static_cast<int>(NBT_S_K.size())   == 0 &&
      static_cast<int>(E_INT_S_K.size())   == 0 && static_cast<int>(S_K_TAB.size())   == 0 )
  {
    mat_no = unassigned_mat_no;
    mt_no  = unassigned_mt_no;
  }

  //Set ENDF format data
  endf_obj.clear();
  endf_obj.set_mat_no(mat_no);
  endf_obj.set_mt_no(mt_no);
  endf_obj.set_NK(NK);
  endf_obj.set_NBT_S_TOT(NBT_S_TOT);
  endf_obj.set_INT_S_TOT(INT_S_TOT);
  endf_obj.set_E_INT_S_TOT(E_INT_S_TOT);
  endf_obj.set_S_TOT_TAB(S_TOT_TAB);
  endf_obj.set_EG(EG);
  endf_obj.set_ES(ES);
  endf_obj.set_LP(LP);
  endf_obj.set_LF(LF);
  endf_obj.set_NBT_S_K(NBT_S_K);
  endf_obj.set_INT_S_K(INT_S_K);
  endf_obj.set_E_INT_S_K(E_INT_S_K);
  endf_obj.set_S_K_TAB(S_K_TAB);

  //Clear declared data
  mt_no       = 0;
  NK          = 0;
  ES.clear();
  EG.clear();
  LP.clear();
  LF.clear();
  INT_S_TOT.clear();
  NBT_S_TOT.clear();
  E_INT_S_TOT.clear();
  S_TOT_TAB.clear();
  clr_obj.clear_vec_array2_int(INT_S_K);
  clr_obj.clear_vec_array2_int(NBT_S_K);
  clr_obj.clear_vec_array2_real(E_INT_S_K);
  clr_obj.clear_vec_array2_real(S_K_TAB);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//MF13Parser -> PhotonDataContainer
void MF13Converter::convert_endf_format_to_frendy( MF13Parser& endf_obj, PhotonDataContainer& frendy_obj )
{
  //Get frendy data
  Integer                  reaction_type                       = endf_obj.get_mt_no();
  Integer                  ene_level_no                        = endf_obj.get_NK();
  vector<Real>             photon_ene                          = endf_obj.get_ES();
  vector<Real>             binding_ene                         = endf_obj.get_EG();
  vector<Integer>          binding_ene_flg                     = endf_obj.get_LP();
  vector<Integer>          distr_law_no                        = endf_obj.get_LF();
  vector<Integer>          photon_production_xs_tot_int_data   = endf_obj.get_INT_S_TOT();
  vector<Integer>          photon_production_xs_tot_range_data = endf_obj.get_NBT_S_TOT();
  vector<Real>             photon_production_xs_tot_ene_data   = endf_obj.get_E_INT_S_TOT();
  vector<Real>             photon_production_xs_tot_data       = endf_obj.get_S_TOT_TAB();
  vector<vector<Integer> > photon_production_xs_int_data       = endf_obj.get_INT_S_K();
  vector<vector<Integer> > photon_production_xs_range_data     = endf_obj.get_NBT_S_K();
  vector<vector<Real> >    photon_production_xs_ene_data       = endf_obj.get_E_INT_S_K();
  vector<vector<Real> >    photon_production_xs_data           = endf_obj.get_S_K_TAB();

  if( ene_level_no == 0 &&
      static_cast<int>(photon_ene.size())      == 0 && static_cast<int>(binding_ene.size())  == 0 &&
      static_cast<int>(binding_ene_flg.size()) == 0 && static_cast<int>(distr_law_no.size()) == 0 &&
      static_cast<int>(photon_production_xs_tot_int_data.size())   == 0 &&
      static_cast<int>(photon_production_xs_tot_range_data.size()) == 0 &&
      static_cast<int>(photon_production_xs_tot_ene_data.size())   == 0 &&
      static_cast<int>(photon_production_xs_tot_data.size())       == 0 &&
      static_cast<int>(photon_production_xs_int_data.size())       == 0 &&
      static_cast<int>(photon_production_xs_range_data.size())     == 0 &&
      static_cast<int>(photon_production_xs_ene_data.size())       == 0 &&
      static_cast<int>(photon_production_xs_data.size())           == 0 )
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
  frendy_obj.set_ene_level_no(ene_level_no);
  frendy_obj.set_photon_production_xs_tot_range_data(photon_production_xs_tot_range_data);
  frendy_obj.set_photon_production_xs_tot_int_data(photon_production_xs_tot_int_data);
  frendy_obj.set_photon_production_xs_tot_ene_data(photon_production_xs_tot_ene_data);
  frendy_obj.set_photon_production_xs_tot_data(photon_production_xs_tot_data);
  frendy_obj.set_binding_ene(binding_ene);
  frendy_obj.set_photon_ene(photon_ene);
  frendy_obj.set_binding_ene_flg(binding_ene_flg);
  frendy_obj.set_distr_law_no(distr_law_no);
  frendy_obj.set_photon_production_xs_range_data(photon_production_xs_range_data);
  frendy_obj.set_photon_production_xs_int_data(photon_production_xs_int_data);
  frendy_obj.set_photon_production_xs_ene_data(photon_production_xs_ene_data);
  frendy_obj.set_photon_production_xs_data(photon_production_xs_data);

  //Clear declared data
  reaction_type = 0;
  ene_level_no  = 0;
  photon_ene.clear();
  binding_ene.clear();
  binding_ene_flg.clear();
  distr_law_no.clear();
  photon_production_xs_tot_int_data.clear();
  photon_production_xs_tot_range_data.clear();
  photon_production_xs_tot_ene_data.clear();
  photon_production_xs_tot_data.clear();
  clr_obj.clear_vec_array2_int(photon_production_xs_int_data);
  clr_obj.clear_vec_array2_int(photon_production_xs_range_data);
  clr_obj.clear_vec_array2_real(photon_production_xs_ene_data);
  clr_obj.clear_vec_array2_real(photon_production_xs_data);
}

