#include "EndfUtils/MFxxMTyyyConverter/MF07MT002Converter.hpp"

using namespace frendy;

//constructor
MF07MT002Converter::MF07MT002Converter(void)
{
}

//destructor
MF07MT002Converter::~MF07MT002Converter(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//ThermalScatterDataContainer -> MF07MT002Parser
void MF07MT002Converter::convert_frendy_to_endf_format( ThermalScatterDataContainer& frendy_obj, MF07MT002Parser& endf_obj )
{
  //Get frendy data
  Integer               LTHR    = frendy_obj.get_elastic_scat_flg();
  Real                  T0      = frendy_obj.get_elastic_temp_data_base();
  vector<Real>          T       = frendy_obj.get_elastic_temp_data();
  vector<Integer>       LI      = frendy_obj.get_elastic_temp_int();
  vector<Integer>       INT_S   = frendy_obj.get_elastic_structure_factor_int_data();
  vector<Integer>       NBT_S   = frendy_obj.get_elastic_structure_factor_range_data();
  vector<Real>          E_INT_S = frendy_obj.get_elastic_structure_factor_ene_data();
  vector<Real>          S_TAB   = frendy_obj.get_elastic_structure_factor_data_base();
  vector<vector<Real> > S       = frendy_obj.get_elastic_structure_factor_data();
  Real                  SB      = frendy_obj.get_elastic_bound_xs();
  vector<Integer>       INT_W   = frendy_obj.get_elastic_debye_waller_int_data();
  vector<Integer>       NBT_W   = frendy_obj.get_elastic_debye_waller_range_data();
  vector<Real>          T_INT_W = frendy_obj.get_elastic_debye_waller_temp_data();
  vector<Real>          W_TAB   = frendy_obj.get_elastic_debye_waller_data();
  
  Integer LT = 0;
  if( LTHR == 1 || LTHR == 3 )
  {
    LT = static_cast<Integer>(T.size());
  }

  Integer mat_no = 0;
  if( LTHR == 0 && 
      static_cast<int>(T.size())       == 0 && static_cast<int>(LI.size())      == 0 &&
      static_cast<int>(INT_S.size())   == 0 && static_cast<int>(NBT_S.size())   == 0 &&
      static_cast<int>(E_INT_S.size()) == 0 && static_cast<int>(S_TAB.size())   == 0 &&
      static_cast<int>(S.size())       == 0 && static_cast<int>(INT_W.size())   == 0 &&
      static_cast<int>(NBT_W.size())   == 0 && static_cast<int>(T_INT_W.size()) == 0 &&
      static_cast<int>(W_TAB.size())   == 0 )
  {
    mat_no = unassigned_mat_no;
  }

  //Set ENDF format data
  endf_obj.clear();
  endf_obj.set_mat_no(mat_no);
  endf_obj.set_LTHR(LTHR);
  endf_obj.set_T0_LTHR01(T0);
  endf_obj.set_LT_LTHR01(LT);
  endf_obj.set_NBT_S_LTHR01(NBT_S);
  endf_obj.set_INT_S_LTHR01(INT_S);
  endf_obj.set_E_INT_S_LTHR01(E_INT_S);
  endf_obj.set_S_TAB_LTHR01(S_TAB);
  endf_obj.set_T_LTHR01(T);
  endf_obj.set_LI_LTHR01(LI);
  endf_obj.set_S_LTHR01(S);
  endf_obj.set_SB_LTHR02(SB);
  endf_obj.set_NBT_W_LTHR02(NBT_W);
  endf_obj.set_INT_W_LTHR02(INT_W);
  endf_obj.set_T_INT_W_LTHR02(T_INT_W);
  endf_obj.set_W_TAB_LTHR02(W_TAB);

  //Clear declared data
  LTHR = 0;
  T0   = 0.0;
  T.clear();
  LI.clear();
  INT_S.clear();
  NBT_S.clear();
  E_INT_S.clear();
  S_TAB.clear();
  clr_obj.clear_vec_array2_real(S);
  SB = 0.0;
  INT_W.clear();
  NBT_W.clear();
  T_INT_W.clear();
  W_TAB.clear();
  LT = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//MF07MT002Parser -> ThermalScatterDataContainer
void MF07MT002Converter::convert_endf_format_to_frendy( MF07MT002Parser& endf_obj, ThermalScatterDataContainer& frendy_obj )
{
  //Get frendy data
  Integer               elastic_scat_flg                    = endf_obj.get_LTHR();
  Real                  elastic_temp_data_base              = endf_obj.get_T0_LTHR01();
  vector<Real>          elastic_temp_data                   = endf_obj.get_T_LTHR01();
  vector<Integer>       elastic_temp_int                    = endf_obj.get_LI_LTHR01();
  vector<Integer>       elastic_structure_factor_int_data   = endf_obj.get_INT_S_LTHR01();
  vector<Integer>       elastic_structure_factor_range_data = endf_obj.get_NBT_S_LTHR01();
  vector<Real>          elastic_structure_factor_ene_data   = endf_obj.get_E_INT_S_LTHR01();
  vector<Real>          elastic_structure_factor_data_base  = endf_obj.get_S_TAB_LTHR01();
  vector<vector<Real> > elastic_structure_factor_data       = endf_obj.get_S_LTHR01();
  Real                  elastic_bound_xs                    = endf_obj.get_SB_LTHR02();
  vector<Integer>       elastic_debye_waller_int_data       = endf_obj.get_INT_W_LTHR02();
  vector<Integer>       elastic_debye_waller_range_data     = endf_obj.get_NBT_W_LTHR02();
  vector<Real>          elastic_debye_waller_temp_data      = endf_obj.get_T_INT_W_LTHR02();
  vector<Real>          elastic_debye_waller_data           = endf_obj.get_W_TAB_LTHR02();

  //Set ENDF format data
  //frendy_obj.clear();
  //text
  //mat_no
  //ZA
  //AWR
  frendy_obj.set_elastic_scat_flg(elastic_scat_flg);
  frendy_obj.set_elastic_temp_data_base(elastic_temp_data_base);
  frendy_obj.set_elastic_structure_factor_range_data(elastic_structure_factor_range_data);
  frendy_obj.set_elastic_structure_factor_int_data(elastic_structure_factor_int_data);
  frendy_obj.set_elastic_structure_factor_ene_data(elastic_structure_factor_ene_data);
  frendy_obj.set_elastic_structure_factor_data_base(elastic_structure_factor_data_base);
  frendy_obj.set_elastic_temp_data(elastic_temp_data);
  frendy_obj.set_elastic_temp_int(elastic_temp_int);
  frendy_obj.set_elastic_structure_factor_data(elastic_structure_factor_data);
  frendy_obj.set_elastic_bound_xs(elastic_bound_xs);
  frendy_obj.set_elastic_debye_waller_range_data(elastic_debye_waller_range_data);
  frendy_obj.set_elastic_debye_waller_int_data(elastic_debye_waller_int_data);
  frendy_obj.set_elastic_debye_waller_temp_data(elastic_debye_waller_temp_data);
  frendy_obj.set_elastic_debye_waller_data(elastic_debye_waller_data);

  //Clear declared data
  elastic_scat_flg       = 0;
  elastic_temp_data_base = 0.0;
  elastic_temp_data.clear();
  elastic_temp_int.clear();
  elastic_structure_factor_int_data.clear();
  elastic_structure_factor_range_data.clear();
  elastic_structure_factor_ene_data.clear();
  elastic_structure_factor_data_base.clear();
  clr_obj.clear_vec_array2_real(elastic_structure_factor_data);
  elastic_bound_xs = 0.0;
  elastic_debye_waller_int_data.clear();
  elastic_debye_waller_range_data.clear();
  elastic_debye_waller_temp_data.clear();
  elastic_debye_waller_data.clear();
}

