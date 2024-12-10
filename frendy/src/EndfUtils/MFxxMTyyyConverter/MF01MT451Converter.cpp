#include "EndfUtils/MFxxMTyyyConverter/MF01MT451Converter.hpp"

using namespace frendy;

//constructor
MF01MT451Converter::MF01MT451Converter(void)
{
}

//destructor
MF01MT451Converter::~MF01MT451Converter(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//GeneralDataContainer -> MF01MT451Parser
void MF01MT451Converter::convert_frendy_to_endf_format( GeneralDataContainer& frendy_obj, MF01MT451Parser& endf_obj )
{
  //Get frendy data
  Integer         MAT          = frendy_obj.get_mat_no();
  Real            ZA           = frendy_obj.get_mat_data();
  Real            AWR          = frendy_obj.get_mass();
  Integer         LRP          = frendy_obj.get_reso_flg();
  Integer         LFI          = frendy_obj.get_fis_flg();
  Integer         NLIB         = frendy_obj.get_lib_identifier();
  Integer         NMOD         = frendy_obj.get_lib_mod_no();
  Real            ELIS         = frendy_obj.get_excitation_ene();
  Integer         STA          = frendy_obj.get_stability_flg_target();
  Integer         LIS          = frendy_obj.get_state_no();
  Integer         LISO         = frendy_obj.get_iso_state_no();
  Integer         NFOR         = frendy_obj.get_lib_format();
  Real            AWI          = frendy_obj.get_mass_projectile();
  Real            EMAX         = frendy_obj.get_upper_ene_limit();
  Integer         LREL         = frendy_obj.get_lib_release_no();
  Integer         NSUB         = frendy_obj.get_sub_lib_no();
  Integer         NVER         = frendy_obj.get_lib_ver();
  Real            TEMP         = frendy_obj.get_temp();
  Real            ERROR        = frendy_obj.get_error_value();
  Integer         LDRV         = frendy_obj.get_special_derived_mat_flg();
  string          ZSYMAM       = frendy_obj.get_brief_explain_word();
  string          ALAB         = frendy_obj.get_evaluated_institute();
  string          EDATE        = frendy_obj.get_evaluated_date();
  string          AUTH         = frendy_obj.get_evaluated_author();
  string          REF          = frendy_obj.get_evaluated_ref();
  string          DDATE        = frendy_obj.get_evaluated_date_ori();
  string          RDATE        = frendy_obj.get_evaluated_date_rev();
  string          ENDATE       = frendy_obj.get_evaluated_date_end();
  string          HSUB         = frendy_obj.get_evaluated_data_specification();
  vector<Integer> MF           = frendy_obj.get_file_section_data_list()[0];
  vector<Integer> MT           = frendy_obj.get_file_section_data_list()[1];
  vector<Integer> NC           = frendy_obj.get_file_section_data_list()[2];
  vector<Integer> MOD          = frendy_obj.get_file_section_data_list()[3];
  vector<string>  comment_line = frendy_obj.get_comment_data();
  
  Integer NWD = static_cast<Integer>(comment_line.size());
  Integer NXC = static_cast<Integer>(MF.size());

  //Set ENDF format data
  endf_obj.clear();
  endf_obj.set_mat_no(MAT);
  endf_obj.set_ZA(ZA);
  endf_obj.set_AWR(AWR);
  endf_obj.set_LRP(LRP);
  endf_obj.set_LFI(LFI);
  endf_obj.set_NLIB(NLIB);
  endf_obj.set_NMOD(NMOD);
  endf_obj.set_ELIS(ELIS);
  endf_obj.set_STA(STA);
  endf_obj.set_LIS(LIS);
  endf_obj.set_LISO(LISO);
  endf_obj.set_NFOR(NFOR);
  endf_obj.set_AWI(AWI);
  endf_obj.set_EMAX(EMAX);
  endf_obj.set_LREL(LREL);
  endf_obj.set_NSUB(NSUB);
  endf_obj.set_NVER(NVER);
  endf_obj.set_TEMP(TEMP);
  endf_obj.set_ERROR(ERROR);
  endf_obj.set_LDRV(LDRV);
  endf_obj.set_NWD(NWD);
  endf_obj.set_NXC(NXC);
  endf_obj.set_ZSYMAM(ZSYMAM);
  endf_obj.set_ALAB(ALAB);
  endf_obj.set_EDATE(EDATE);
  endf_obj.set_AUTH(AUTH);
  endf_obj.set_REF(REF);
  endf_obj.set_DDATE(DDATE);
  endf_obj.set_RDATE(RDATE);
  endf_obj.set_ENDATE(ENDATE);
  endf_obj.set_HSUB(HSUB);
  endf_obj.set_comment_line(comment_line);
  endf_obj.set_MF(MF);
  endf_obj.set_MT(MT);
  endf_obj.set_NC(NC);
  endf_obj.set_MOD(MOD);

  //Clear declared data
  MAT   = 0;
  ZA    = 0.0;
  AWR   = 0.0;
  LRP   = 0;
  LFI   = 0;
  NLIB  = 0;
  NMOD  = 0;
  ELIS  = 0.0;
  STA   = 0;
  LIS   = 0;
  LISO  = 0;
  NFOR  = 0;
  AWI   = 0.0;
  EMAX  = 0.0;
  LREL  = 0;
  NSUB  = 0;
  NVER  = 0;
  TEMP  = 0.0;
  ERROR = 0.0;
  LDRV  = 0;
  NWD   = 0;
  NXC   = 0;
  ZSYMAM.clear();
  ALAB.clear();
  EDATE.clear();
  AUTH.clear();
  REF.clear();
  DDATE.clear();
  RDATE.clear();
  ENDATE.clear();
  HSUB.clear();
  MF.clear();
  MT.clear();
  NC.clear();
  MOD.clear();
  clr_obj.clear_vec_array1_str(comment_line);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//MF01MT451Parser -> GeneralDataContainer
void MF01MT451Converter::convert_endf_format_to_frendy( MF01MT451Parser& endf_obj, GeneralDataContainer& frendy_obj )
{
  //Get frendy data
  Integer                  mat_no                       = endf_obj.get_mat_no();
  Real                     mat_data                     = endf_obj.get_ZA();
  Real                     mass                         = endf_obj.get_AWR();
  Integer                  reso_flg                     = endf_obj.get_LRP();
  Integer                  fis_flg                      = endf_obj.get_LFI();
  Integer                  lib_identifier               = endf_obj.get_NLIB();
  Integer                  lib_mod_no                   = endf_obj.get_NMOD();
  Real                     excitation_ene               = endf_obj.get_ELIS();
  Integer                  stability_flg_target         = endf_obj.get_STA();
  Integer                  state_no                     = endf_obj.get_LIS();
  Integer                  iso_state_no                 = endf_obj.get_LISO();
  Integer                  lib_format                   = endf_obj.get_NFOR();
  Real                     mass_projectile              = endf_obj.get_AWI();
  Real                     upper_ene_limit              = endf_obj.get_EMAX();
  Integer                  lib_release_no               = endf_obj.get_LREL();
  Integer                  sub_lib_no                   = endf_obj.get_NSUB();
  Integer                  lib_ver                      = endf_obj.get_NVER();
  Real                     temp                         = endf_obj.get_TEMP();
  Real                     error_value                  = endf_obj.get_ERROR();
  Integer                  special_derived_mat_flg      = endf_obj.get_LDRV();
  string                   brief_explain_word           = endf_obj.get_ZSYMAM();
  string                   evaluated_institute          = endf_obj.get_ALAB();
  string                   evaluated_date               = endf_obj.get_EDATE();
  string                   evaluated_author             = endf_obj.get_AUTH();
  string                   evaluated_ref                = endf_obj.get_REF();
  string                   evaluated_date_ori           = endf_obj.get_DDATE();
  string                   evaluated_date_rev           = endf_obj.get_RDATE();
  string                   evaluated_date_end           = endf_obj.get_ENDATE();
  string                   evaluated_data_specification = endf_obj.get_HSUB();
  vector<string>           comment_data                 = endf_obj.get_comment_line();

  vector<vector<Integer> > file_section_data_list;
  file_section_data_list.resize(4);
  file_section_data_list[0] = endf_obj.get_MF();
  file_section_data_list[1] = endf_obj.get_MT();
  file_section_data_list[2] = endf_obj.get_NC();
  file_section_data_list[3] = endf_obj.get_MOD();
  
  //Set ENDF format data
  //frendy_obj.clear();
  //text
  frendy_obj.set_mat_no(mat_no);
  frendy_obj.set_mat_data(mat_data);
  frendy_obj.set_mass(mass);
  frendy_obj.set_reso_flg(reso_flg);
  frendy_obj.set_fis_flg(fis_flg);
  frendy_obj.set_lib_identifier(lib_identifier);
  frendy_obj.set_lib_mod_no(lib_mod_no);
  frendy_obj.set_excitation_ene(excitation_ene);
  frendy_obj.set_stability_flg_target(stability_flg_target);
  frendy_obj.set_state_no(state_no);
  frendy_obj.set_iso_state_no(iso_state_no);
  frendy_obj.set_lib_format(lib_format);
  frendy_obj.set_mass_projectile(mass_projectile);
  frendy_obj.set_upper_ene_limit(upper_ene_limit);
  frendy_obj.set_lib_release_no(lib_release_no);
  frendy_obj.set_sub_lib_no(sub_lib_no);
  frendy_obj.set_lib_ver(lib_ver);
  frendy_obj.set_temp(temp);
  frendy_obj.set_error_value(error_value);
  frendy_obj.set_special_derived_mat_flg(special_derived_mat_flg);
  frendy_obj.set_brief_explain_word(brief_explain_word);
  frendy_obj.set_evaluated_institute(evaluated_institute);
  frendy_obj.set_evaluated_date(evaluated_date);
  frendy_obj.set_evaluated_author(evaluated_author);
  frendy_obj.set_evaluated_ref(evaluated_ref);
  frendy_obj.set_evaluated_date_ori(evaluated_date_ori);
  frendy_obj.set_evaluated_date_rev(evaluated_date_rev);
  frendy_obj.set_evaluated_date_end(evaluated_date_end);
  frendy_obj.set_evaluated_data_specification(evaluated_data_specification);
  frendy_obj.set_comment_data(comment_data);
  frendy_obj.set_file_section_data_list(file_section_data_list);

  //Clear declared data
  mat_no                       = 0;
  mat_data                     = 0.0;
  mass                         = 0.0;
  reso_flg                     = 0;
  fis_flg                      = 0;
  lib_identifier               = 0;
  lib_mod_no                   = 0;
  excitation_ene               = 0.0;
  stability_flg_target         = 0;
  state_no                     = 0;
  iso_state_no                 = 0;
  lib_format                   = 0;
  mass_projectile              = 0.0;
  upper_ene_limit              = 0.0;
  lib_release_no               = 0;
  sub_lib_no                   = 0;
  lib_ver                      = 0;
  temp                         = 0.0;
  error_value                  = 0.0;
  special_derived_mat_flg      = 0;
  brief_explain_word.clear();
  evaluated_institute.clear();
  evaluated_date.clear();
  evaluated_author.clear();
  evaluated_ref.clear();
  evaluated_date_ori.clear();
  evaluated_date_rev.clear();
  evaluated_date_end.clear();
  evaluated_data_specification.clear();
  clr_obj.clear_vec_array2_int(file_section_data_list);
  clr_obj.clear_vec_array1_str(comment_data);
}

