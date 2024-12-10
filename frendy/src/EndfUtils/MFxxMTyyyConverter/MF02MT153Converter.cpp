#include "EndfUtils/MFxxMTyyyConverter/MF02MT153Converter.hpp"

using namespace frendy;

//constructor
MF02MT153Converter::MF02MT153Converter(void)
{
}

//destructor
MF02MT153Converter::~MF02MT153Converter(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//UnresolvedProbabilityDataContainer -> MF02MT153Parser
void MF02MT153Converter::convert_frendy_to_endf_format( UnresolvedProbabilityDataContainer& frendy_obj, MF02MT153Parser& endf_obj )
{
  //Get frendy data
  Integer      INEL  = frendy_obj.get_comp_flg_inela();
  Integer      ABSO  = frendy_obj.get_comp_flg_abs();
  Integer      INT   = frendy_obj.get_prob_int();
  Integer      NBIN  = frendy_obj.get_prob_bin_no();
  Integer      LSSF  = frendy_obj.get_self_shielding_flg();
  Integer      ICOMP = frendy_obj.get_comp_flg();
  Integer      NUNR  = frendy_obj.get_prob_ene_no();
  Real         TEMP  = frendy_obj.get_temp();
  vector<Real> ENE   = frendy_obj.get_prob_ene();

  vector<vector<Real> > HEAT    = frendy_obj.get_prob_heat();
  vector<vector<Real> > P_COUNT = frendy_obj.get_prob_table_sample_no();

  vector<vector<vector<Real> > > P_TABLE = frendy_obj.get_prob_table();

  Integer mat_no = 0;
  if( INT == 0 && NBIN == 0 && LSSF == 0 && ICOMP == 0 && NUNR == 0 )
  {
    mat_no = unassigned_mat_no;
  }

  //Set ENDF format data
  endf_obj.clear();
  endf_obj.set_mat_no(mat_no);
  endf_obj.set_INEL(INEL);
  endf_obj.set_ABSO(ABSO);
  endf_obj.set_INT(INT);
  endf_obj.set_NBIN(NBIN);
  endf_obj.set_LSSF(LSSF);
  endf_obj.set_ICOMP(ICOMP);
  endf_obj.set_NUNR(NUNR);
  endf_obj.set_TEMP(TEMP);
  endf_obj.set_ENE(ENE);
  endf_obj.set_HEAT(HEAT);
  endf_obj.set_P_COUNT(P_COUNT);
  endf_obj.set_P_TABLE(P_TABLE);

  //Clear declared data
  INEL    = 0;
  ABSO    = 0;
  INT     = 0;
  NBIN    = 0;
  LSSF    = 0;
  ICOMP   = 0;
  NUNR    = 0;
  TEMP    = 0.0;
  ENE.clear();
  clr_obj.clear_vec_array2_real8(HEAT);
  clr_obj.clear_vec_array2_real8(P_COUNT);
  clr_obj.clear_vec_array3_real8(P_TABLE);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//MF02MT153Parser -> UnresolvedProbabilityDataContainer
void MF02MT153Converter::convert_endf_format_to_frendy( MF02MT153Parser& endf_obj, UnresolvedProbabilityDataContainer& frendy_obj )
{
  //Get frendy data
  Integer      comp_flg_inela     = endf_obj.get_INEL();
  Integer      comp_flg_abs       = endf_obj.get_ABSO();
  Integer      prob_int           = endf_obj.get_INT();
  Integer      prob_bin_no        = endf_obj.get_NBIN();
  Integer      self_shielding_flg = endf_obj.get_LSSF();
  Integer      comp_flg           = endf_obj.get_ICOMP();
  Integer      prob_ene_no        = endf_obj.get_NUNR();
  Real         temp               = endf_obj.get_TEMP();
  vector<Real> prob_ene           = endf_obj.get_ENE();

  vector<vector<Real> >          prob_heat            = endf_obj.get_HEAT();
  vector<vector<Real> >          prob_table_sample_no = endf_obj.get_P_COUNT();
  vector<vector<vector<Real> > > prob_table           = endf_obj.get_P_TABLE();

  //Set ENDF format data
  //frendy_obj.clear();
  //text
  //mat_no
  //ZAR
  //AWR
  frendy_obj.set_comp_flg_inela(comp_flg_inela);
  frendy_obj.set_comp_flg_abs(comp_flg_abs);
  frendy_obj.set_prob_int(prob_int);
  frendy_obj.set_prob_bin_no(prob_bin_no);
  frendy_obj.set_self_shielding_flg(self_shielding_flg);
  frendy_obj.set_comp_flg(comp_flg);
  frendy_obj.set_prob_ene_no(prob_ene_no);
  frendy_obj.set_temp(temp);
  frendy_obj.set_prob_ene(prob_ene);
  frendy_obj.set_prob_heat(prob_heat);
  frendy_obj.set_prob_table_sample_no(prob_table_sample_no);
  frendy_obj.set_prob_table(prob_table);

  //Clear declared data
  comp_flg_inela     = 0;
  comp_flg_abs       = 0;
  prob_int           = 0;
  prob_bin_no        = 0;
  self_shielding_flg = 0;
  comp_flg           = 0;
  prob_ene_no        = 0;
  temp               = 0.0;
  prob_ene.clear();
  clr_obj.clear_vec_array2_real8(prob_heat);
  clr_obj.clear_vec_array2_real8(prob_table_sample_no);
  clr_obj.clear_vec_array3_real8(prob_table);
}

