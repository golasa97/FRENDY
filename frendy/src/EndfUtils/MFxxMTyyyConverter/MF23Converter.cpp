#include "EndfUtils/MFxxMTyyyConverter/MF23Converter.hpp"

using namespace frendy;

//constructor
MF23Converter::MF23Converter(void)
{
}

//destructor
MF23Converter::~MF23Converter(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//PhotonDataContainer -> MF23Parser
void MF23Converter::convert_frendy_to_endf_format( PhotonDataContainer& frendy_obj, MF23Parser& endf_obj )
{
  //Get frendy data
  Integer         mt_no   = frendy_obj.get_reaction_type();
  Real            EPE     = frendy_obj.get_binding_ene_subshell();
  Real            EFL     = frendy_obj.get_fluorescence_yield();
  vector<Integer> INT_S   = frendy_obj.get_photon_interaction_xs_int_data();
  vector<Integer> NBT_S   = frendy_obj.get_photon_interaction_xs_range_data();
  vector<Real>    E_INT_S = frendy_obj.get_photon_interaction_xs_ene_data();
  vector<Real>    S_TAB   = frendy_obj.get_photon_interaction_xs_data();

  Integer mat_no = 0;
  if( fabs(EPE) < min_value && fabs(EFL) < min_value &&
      static_cast<int>(INT_S.size())   == 0 && static_cast<int>(NBT_S.size()) == 0 &&
      static_cast<int>(E_INT_S.size()) == 0 && static_cast<int>(S_TAB.size()) == 0 )
  {
    mat_no = unassigned_mat_no;
    mt_no  = unassigned_mt_no;
  }

  //Set ENDF format data
  endf_obj.clear();
  endf_obj.set_mat_no(mat_no);
  endf_obj.set_mt_no(mt_no);
  endf_obj.set_EPE(EPE);
  endf_obj.set_EFL(EFL);
  endf_obj.set_NBT_S(NBT_S);
  endf_obj.set_INT_S(INT_S);
  endf_obj.set_E_INT_S(E_INT_S);
  endf_obj.set_S_TAB(S_TAB);

  //Clear declared data
  mt_no   = 0;
  EPE     = 0.0;
  EFL     = 0.0;
  INT_S.clear();
  NBT_S.clear();
  E_INT_S.clear();
  S_TAB.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//MF23Parser -> PhotonDataContainer
void MF23Converter::convert_endf_format_to_frendy( MF23Parser& endf_obj, PhotonDataContainer& frendy_obj )
{
  //Get frendy data
  Integer         reaction_type                    = endf_obj.get_mt_no();
  Real            binding_ene_subshell             = endf_obj.get_EPE();
  Real            fluorescence_yield               = endf_obj.get_EFL();
  vector<Integer> photon_interaction_xs_int_data   = endf_obj.get_INT_S();
  vector<Integer> photon_interaction_xs_range_data = endf_obj.get_NBT_S();
  vector<Real>    photon_interaction_xs_ene_data   = endf_obj.get_E_INT_S();
  vector<Real>    photon_interaction_xs_data       = endf_obj.get_S_TAB();

  if( fabs(binding_ene_subshell) < min_value && fabs(fluorescence_yield) < min_value && 
      static_cast<int>(photon_interaction_xs_int_data.size())   == 0 &&
      static_cast<int>(photon_interaction_xs_range_data.size()) == 0 &&
      static_cast<int>(photon_interaction_xs_ene_data.size())   == 0 &&
      static_cast<int>(photon_interaction_xs_data.size())       == 0 )
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
  frendy_obj.set_binding_ene_subshell(binding_ene_subshell);
  frendy_obj.set_fluorescence_yield(fluorescence_yield);
  frendy_obj.set_photon_interaction_xs_range_data(photon_interaction_xs_range_data);
  frendy_obj.set_photon_interaction_xs_int_data(photon_interaction_xs_int_data);
  frendy_obj.set_photon_interaction_xs_ene_data(photon_interaction_xs_ene_data);
  frendy_obj.set_photon_interaction_xs_data(photon_interaction_xs_data);

  //Clear declared data
  reaction_type                    = 0;
  binding_ene_subshell             = 0.0;
  fluorescence_yield               = 0.0;
  photon_interaction_xs_int_data.clear();
  photon_interaction_xs_range_data.clear();
  photon_interaction_xs_ene_data.clear();
  photon_interaction_xs_data.clear();
}

