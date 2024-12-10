#include "EndfUtils/MFxxMTyyyConverter/MF02MT152Converter.hpp"

using namespace frendy;

//constructor
MF02MT152Converter::MF02MT152Converter(void)
{
}

//destructor
MF02MT152Converter::~MF02MT152Converter(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//UnresolvedCrossSectionDataContainer -> MF02MT152Parser
void MF02MT152Converter::convert_frendy_to_endf_format( UnresolvedCrossSectionDataContainer& frendy_obj, MF02MT152Parser& endf_obj )
{
  //Get frendy data
  Integer      LSSF     = frendy_obj.get_self_shielding_flg();
  Integer      INT      = frendy_obj.get_unreso_opt_int();
  Integer      OPT1     = frendy_obj.get_unreso_opt_a();
  Integer      OPT2     = frendy_obj.get_unreso_opt_b();
  Integer      NE       = frendy_obj.get_unreso_data_no();
  Real         TEMP     = frendy_obj.get_temp();
  vector<Real> E        = frendy_obj.get_unreso_ene();
  vector<Real> SIG_TOT  = frendy_obj.get_unreso_sig_tot();
  vector<Real> SIG_SC   = frendy_obj.get_unreso_sig_scat();
  vector<Real> SIG_FIS  = frendy_obj.get_unreso_sig_fis();
  vector<Real> SIG_RAD  = frendy_obj.get_unreso_sig_rad();
  vector<Real> SIG_ZERO = frendy_obj.get_sig_zero();
  vector<vector<vector<Real> > > B_TABLE = frendy_obj.get_bondarenko_table();

  Integer mat_no = 0;
  if( LSSF == 0 && INT == 0 && OPT1 == 0 && OPT2 == 0 && NE == 0 )
  {
    mat_no = unassigned_mat_no;
  }

  //Set ENDF format data
  endf_obj.clear();
  endf_obj.set_mat_no(mat_no);
  endf_obj.set_LSSF(LSSF);
  endf_obj.set_INT(INT);
  endf_obj.set_OPT1(OPT1);
  endf_obj.set_OPT2(OPT2);
  endf_obj.set_NE(NE);
  endf_obj.set_TEMP(TEMP);
  endf_obj.set_E(E);
  endf_obj.set_SIG_TOT(SIG_TOT);
  endf_obj.set_SIG_SC(SIG_SC);
  endf_obj.set_SIG_FIS(SIG_FIS);
  endf_obj.set_SIG_RAD(SIG_RAD);
  endf_obj.set_SIG_ZERO(SIG_ZERO);
  endf_obj.set_B_TABLE(B_TABLE);

  //Clear declared data
  LSSF    = 0;
  INT     = 0;
  OPT1    = 0;
  OPT2    = 0;
  NE      = 0;
  TEMP    = 0;
  E.clear();
  SIG_TOT.clear();
  SIG_SC.clear();
  SIG_FIS.clear();
  SIG_RAD.clear();
  SIG_ZERO.clear();
  clr_obj.clear_vec_array3_real8(B_TABLE);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//MF02MT152Parser -> UnresolvedCrossSectionDataContainer
void MF02MT152Converter::convert_endf_format_to_frendy( MF02MT152Parser& endf_obj, UnresolvedCrossSectionDataContainer& frendy_obj )
{
  //Get frendy data
  Integer      self_shielding_flg = endf_obj.get_LSSF();
  Integer      unreso_opt_int     = endf_obj.get_INT();
  Integer      unreso_opt_a       = endf_obj.get_OPT1();
  Integer      unreso_opt_b       = endf_obj.get_OPT2();
  Integer      unreso_data_no     = endf_obj.get_NE();
  Real         temp               = endf_obj.get_TEMP();
  vector<Real> unreso_ene         = endf_obj.get_E();
  vector<Real> unreso_sig_tot     = endf_obj.get_SIG_TOT();
  vector<Real> unreso_sig_scat    = endf_obj.get_SIG_SC();
  vector<Real> unreso_sig_fis     = endf_obj.get_SIG_FIS();
  vector<Real> unreso_sig_rad     = endf_obj.get_SIG_RAD();
  vector<Real> sig_zero           = endf_obj.get_SIG_ZERO();
  vector<vector<vector<Real> > > bondarenko_table = endf_obj.get_B_TABLE();

  //Set ENDF format data
  //frendy_obj.clear();
  //text
  //mat_no
  //ZAR
  //AWR
  frendy_obj.set_self_shielding_flg(self_shielding_flg);
  frendy_obj.set_unreso_opt_int(unreso_opt_int);
  frendy_obj.set_unreso_opt_a(unreso_opt_a);
  frendy_obj.set_unreso_opt_b(unreso_opt_b);
  frendy_obj.set_unreso_data_no(unreso_data_no);
  frendy_obj.set_temp(temp);
  frendy_obj.set_unreso_ene(unreso_ene);
  frendy_obj.set_unreso_sig_tot(unreso_sig_tot);
  frendy_obj.set_unreso_sig_scat(unreso_sig_scat);
  frendy_obj.set_unreso_sig_fis(unreso_sig_fis);
  frendy_obj.set_unreso_sig_rad(unreso_sig_rad);
  frendy_obj.set_sig_zero(sig_zero);
  frendy_obj.set_bondarenko_table(bondarenko_table);

  //Clear declared data
  self_shielding_flg = 0;
  unreso_opt_int     = 0;
  unreso_opt_a       = 0;
  unreso_opt_b       = 0;
  unreso_data_no     = 0;
  temp               = 0.0;
  unreso_ene.clear();
  unreso_sig_tot.clear();
  unreso_sig_scat.clear();
  unreso_sig_fis.clear();
  unreso_sig_rad.clear();
  sig_zero.clear();
  clr_obj.clear_vec_array3_real8(bondarenko_table);
}

