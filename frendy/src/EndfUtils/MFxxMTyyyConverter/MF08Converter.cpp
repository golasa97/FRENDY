#include "EndfUtils/MFxxMTyyyConverter/MF08Converter.hpp"

using namespace frendy;

//constructor
MF08Converter::MF08Converter(void)
{
}

//destructor
MF08Converter::~MF08Converter(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//RadioactiveProductDataContainer -> MF08Parser
void MF08Converter::convert_frendy_to_endf_format( RadioactiveProductDataContainer& frendy_obj, MF08Parser& endf_obj )
{
  //Get frendy data
  Integer               mt_no = frendy_obj.get_reaction_type();
  vector<Real>          ZAP   = frendy_obj.get_mat_data_produced();
  vector<Integer>       LMF   = frendy_obj.get_contain_data_list();
  Integer               LIS   = frendy_obj.get_state_no_target();
  Integer               LISO  = frendy_obj.get_state_no_target_iso();
  vector<Integer>       LFS   = frendy_obj.get_state_no_product();
  vector<Real>          ELFS  = frendy_obj.get_excitation_ene();
  Integer               NO    = frendy_obj.get_decay_chain_flg();
  vector<vector<Real> > HL    = frendy_obj.get_half_life();
  vector<vector<Real> > RTYP  = frendy_obj.get_decay_type();
  vector<vector<Real> > ZAN   = frendy_obj.get_mat_data_daughter();
  vector<vector<Real> > BR    = frendy_obj.get_branching_ratio_daughter();
  vector<vector<Real> > END   = frendy_obj.get_endpoint_ene_daughter();
  vector<vector<Real> > CT    = frendy_obj.get_chain_terminator_daughter();

  Integer mat_no = 0;
  if( LIS == 0 && LISO == 0 && NO == 0 && 
      static_cast<int>(ZAP.size()) == 0 && static_cast<int>(LMF.size())  == 0 &&
      static_cast<int>(LFS.size()) == 0 && static_cast<int>(ELFS.size()) == 0 &&
      static_cast<int>(HL.size())  == 0 && static_cast<int>(RTYP.size()) == 0 &&
      static_cast<int>(ZAN.size()) == 0 && static_cast<int>(BR.size())   == 0 &&
      static_cast<int>(END.size()) == 0 && static_cast<int>(CT.size())   == 0 )
  {
    mat_no = unassigned_mat_no;
    mt_no  = unassigned_mt_no;
  }
  
  Integer NS = static_cast<Integer>(ZAP.size());

  //Set ENDF format data
  endf_obj.clear();
  endf_obj.set_mat_no(mat_no);
  endf_obj.set_mt_no(mt_no);
  endf_obj.set_LIS(LIS);
  endf_obj.set_LISO(LISO);
  endf_obj.set_NS(NS);
  endf_obj.set_NO(NO);
  endf_obj.set_ZAP(ZAP);
  endf_obj.set_ELFS(ELFS);
  endf_obj.set_LMF(LMF);
  endf_obj.set_LFS(LFS);
  endf_obj.set_HL(HL);
  endf_obj.set_RTYP(RTYP);
  endf_obj.set_ZAN(ZAN);
  endf_obj.set_BR(BR);
  endf_obj.set_END(END);
  endf_obj.set_CT(CT);

  //Clear declared data
  mt_no = 0;
  ZAP.clear();
  LMF.clear();
  LIS   = 0;
  LISO  = 0;
  LFS.clear();
  ELFS.clear();
  NO    = 0;
  clr_obj.clear_vec_array2_real(HL);
  clr_obj.clear_vec_array2_real(RTYP);
  clr_obj.clear_vec_array2_real(ZAN);
  clr_obj.clear_vec_array2_real(BR);
  clr_obj.clear_vec_array2_real(END);
  clr_obj.clear_vec_array2_real(CT);
  NS = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//MF08Parser -> RadioactiveProductDataContainer
void MF08Converter::convert_endf_format_to_frendy( MF08Parser& endf_obj, RadioactiveProductDataContainer& frendy_obj )
{
  //Get frendy data
  Integer               reaction_type             = endf_obj.get_mt_no();
  vector<Real>          mat_data_produced         = endf_obj.get_ZAP();
  vector<Integer>       contain_data_list         = endf_obj.get_LMF();
  Integer               state_no_target           = endf_obj.get_LIS();
  Integer               state_no_target_iso       = endf_obj.get_LISO();
  vector<Integer>       state_no_product          = endf_obj.get_LFS();
  vector<Real>          excitation_ene            = endf_obj.get_ELFS();
  Integer               decay_chain_flg           = endf_obj.get_NO();
  vector<vector<Real> > half_life                 = endf_obj.get_HL();
  vector<vector<Real> > decay_type                = endf_obj.get_RTYP();
  vector<vector<Real> > mat_data_daughter         = endf_obj.get_ZAN();
  vector<vector<Real> > branching_ratio_daughter  = endf_obj.get_BR();
  vector<vector<Real> > endpoint_ene_daughter     = endf_obj.get_END();
  vector<vector<Real> > chain_terminator_daughter = endf_obj.get_CT();

  if( state_no_target == 0 && state_no_target_iso == 0 && decay_chain_flg == 0 &&
      static_cast<int>(mat_data_produced.size())  == 0 && static_cast<int>(contain_data_list.size()) == 0 &&
      static_cast<int>(state_no_product.size())   == 0 && static_cast<int>(excitation_ene.size())    == 0 &&
      static_cast<int>(half_life.size())          == 0 && static_cast<int>(decay_type.size())        == 0 &&
      static_cast<int>(mat_data_daughter.size())  == 0 &&
      static_cast<int>(branching_ratio_daughter.size())  == 0 &&
      static_cast<int>(endpoint_ene_daughter.size())     == 0 &&
      static_cast<int>(chain_terminator_daughter.size()) == 0 )
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
  frendy_obj.set_state_no_target(state_no_target);
  frendy_obj.set_state_no_target_iso(state_no_target_iso);
  frendy_obj.set_decay_chain_flg(decay_chain_flg);
  frendy_obj.set_mat_data_produced(mat_data_produced);
  frendy_obj.set_excitation_ene(excitation_ene);
  frendy_obj.set_contain_data_list(contain_data_list);
  frendy_obj.set_state_no_product(state_no_product);
  frendy_obj.set_half_life(half_life);
  frendy_obj.set_decay_type(decay_type);
  frendy_obj.set_mat_data_daughter(mat_data_daughter);
  frendy_obj.set_branching_ratio_daughter(branching_ratio_daughter);
  frendy_obj.set_endpoint_ene_daughter(endpoint_ene_daughter);
  frendy_obj.set_chain_terminator_daughter(chain_terminator_daughter);

  //Clear declared data
  reaction_type             = 0;
  mat_data_produced.clear();
  contain_data_list.clear();
  state_no_target           = 0;
  state_no_target_iso       = 0;
  state_no_product.clear();
  excitation_ene.clear();
  decay_chain_flg           = 0;
  clr_obj.clear_vec_array2_real(half_life);
  clr_obj.clear_vec_array2_real(decay_type);
  clr_obj.clear_vec_array2_real(mat_data_daughter);
  clr_obj.clear_vec_array2_real(branching_ratio_daughter);
  clr_obj.clear_vec_array2_real(endpoint_ene_daughter);
  clr_obj.clear_vec_array2_real(chain_terminator_daughter);
}

