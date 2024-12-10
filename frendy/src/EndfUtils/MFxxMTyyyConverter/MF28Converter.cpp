#include "EndfUtils/MFxxMTyyyConverter/MF28Converter.hpp"

using namespace frendy;

//constructor
MF28Converter::MF28Converter(void)
{
}

//destructor
MF28Converter::~MF28Converter(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//OtherNuclearDataContainer -> MF28Parser
void MF28Converter::convert_frendy_to_endf_format( OtherNuclearDataContainer& frendy_obj, MF28Parser& endf_obj )
{
  //Get frendy data
  Integer               mt_no = frendy_obj.get_reaction_type();
  vector<Real>          SUBI  = frendy_obj.get_first_subshell_type();
  vector<vector<Real> > SUBJ  = frendy_obj.get_second_subshell_type();
  vector<vector<Real> > SUBK  = frendy_obj.get_third_subshell_type();
  vector<Real>          EBI   = frendy_obj.get_binding_ene_subshell();
  vector<Real>          ELN   = frendy_obj.get_electron_no();
  vector<vector<Real> > FTR   = frendy_obj.get_trans_probability();
  vector<vector<Real> > ETR   = frendy_obj.get_trans_ene();

  Integer mat_no = 0;
  if( static_cast<int>(SUBI.size()) == 0 && static_cast<int>(SUBJ.size()) == 0 &&
      static_cast<int>(SUBK.size()) == 0 && static_cast<int>(EBI.size())  == 0 &&
      static_cast<int>(ELN.size())  == 0 && static_cast<int>(FTR.size())  == 0 &&
      static_cast<int>(ETR.size())  == 0 )
  {
    mat_no = unassigned_mat_no;
    mt_no  = unassigned_mt_no;
  }

  Integer NSS = static_cast<Integer>(SUBI.size());

  //Set ENDF format data
  endf_obj.clear();
  endf_obj.set_mat_no(mat_no);
  endf_obj.set_mt_no(mt_no);
  endf_obj.set_NSS(NSS);
  endf_obj.set_SUBI(SUBI);
  endf_obj.set_EBI(EBI);
  endf_obj.set_ELN(ELN);
  endf_obj.set_SUBJ(SUBJ);
  endf_obj.set_SUBK(SUBK);
  endf_obj.set_ETR(ETR);
  endf_obj.set_FTR(FTR);

  //Clear declared data
  mt_no = 0;
  NSS   = 0;
  SUBI.clear();
  clr_obj.clear_vec_array2_real(SUBJ);
  clr_obj.clear_vec_array2_real(SUBK);
  EBI.clear();
  ELN.clear();
  clr_obj.clear_vec_array2_real(FTR);
  clr_obj.clear_vec_array2_real(ETR);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//MF28Parser -> OtherNuclearDataContainer
void MF28Converter::convert_endf_format_to_frendy( MF28Parser& endf_obj, OtherNuclearDataContainer& frendy_obj )
{
  //Get frendy data
  Integer               reaction_type        = endf_obj.get_mt_no();
  vector<Real>          first_subshell_type  = endf_obj.get_SUBI();
  vector<vector<Real> > second_subshell_type = endf_obj.get_SUBJ();
  vector<vector<Real> > third_subshell_type  = endf_obj.get_SUBK();
  vector<Real>          binding_ene_subshell = endf_obj.get_EBI();
  vector<Real>          electron_no          = endf_obj.get_ELN();
  vector<vector<Real> > trans_probability    = endf_obj.get_FTR();
  vector<vector<Real> > trans_ene            = endf_obj.get_ETR();

  if( static_cast<int>(first_subshell_type.size()) == 0 && static_cast<int>(second_subshell_type.size()) == 0 &&
      static_cast<int>(third_subshell_type.size()) == 0 && static_cast<int>(binding_ene_subshell.size()) == 0 &&
      static_cast<int>(electron_no.size())         == 0 && static_cast<int>(trans_probability.size())    == 0 &&
      static_cast<int>(trans_ene.size())           == 0 )
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
  frendy_obj.set_first_subshell_type(first_subshell_type);
  frendy_obj.set_binding_ene_subshell(binding_ene_subshell);
  frendy_obj.set_electron_no(electron_no);
  frendy_obj.set_second_subshell_type(second_subshell_type);
  frendy_obj.set_third_subshell_type(third_subshell_type);
  frendy_obj.set_trans_ene(trans_ene);
  frendy_obj.set_trans_probability(trans_probability);

  //Clear declared data
  reaction_type = 0;
  first_subshell_type.clear();
  clr_obj.clear_vec_array2_real(second_subshell_type);
  clr_obj.clear_vec_array2_real(third_subshell_type);
  binding_ene_subshell.clear();
  electron_no.clear();
  clr_obj.clear_vec_array2_real(trans_probability);
  clr_obj.clear_vec_array2_real(trans_ene);
}

