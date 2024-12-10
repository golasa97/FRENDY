#include "EndfUtils/MFxxMTyyyConverter/MF08MT454Converter.hpp"

using namespace frendy;

//constructor
MF08MT454Converter::MF08MT454Converter(void)
{
}

//destructor
MF08MT454Converter::~MF08MT454Converter(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//FissionDataContainer -> MF08MT454Parser
void MF08MT454Converter::convert_frendy_to_endf_format( FissionDataContainer& frendy_obj, MF08MT454Parser& endf_obj )
{
  //Get frendy data
  vector<vector<Real> > ZAFP = frendy_obj.get_fp_data_independent();
  vector<vector<Real> > FPS  = frendy_obj.get_state_designator_fp_independent();
  vector<vector<Real> > YI   = frendy_obj.get_yield_independent();
  vector<vector<Real> > DYI  = frendy_obj.get_yield_independent_uncertainty();
  vector<Real>          E    = frendy_obj.get_incident_ene_independent();
  vector<Integer>       I    = frendy_obj.get_ene_int_data_independent();

  Integer LE = static_cast<Integer>(E.size()) - 1;

  Integer mat_no = 0;
  if( static_cast<int>(ZAFP.size()) == 0 && static_cast<int>(FPS.size()) == 0 &&
      static_cast<int>(YI.size())   == 0 && static_cast<int>(DYI.size()) == 0 &&
      static_cast<int>(E.size())    == 0 && static_cast<int>(I.size())   == 0 )
  {
    mat_no = unassigned_mat_no;
  }

  //Set ENDF format data
  endf_obj.clear();
  endf_obj.set_mat_no(mat_no);
  endf_obj.set_LE(LE);
  endf_obj.set_E(E);
  endf_obj.set_I(I);
  endf_obj.set_ZAFP(ZAFP);
  endf_obj.set_FPS(FPS);
  endf_obj.set_YI(YI);
  endf_obj.set_DYI(DYI);

  //Clear declared data
  clr_obj.clear_vec_array2_real(ZAFP);
  clr_obj.clear_vec_array2_real(FPS);
  clr_obj.clear_vec_array2_real(YI);
  clr_obj.clear_vec_array2_real(DYI);
  E.clear();
  I.clear();
  LE = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//MF08MT454Parser -> FissionDataContainer
void MF08MT454Converter::convert_endf_format_to_frendy( MF08MT454Parser& endf_obj, FissionDataContainer& frendy_obj )
{
  //Get frendy data
  vector<vector<Real> > fp_data_independent             = endf_obj.get_ZAFP();
  vector<vector<Real> > state_designator_fp_independent = endf_obj.get_FPS();
  vector<vector<Real> > yield_independent               = endf_obj.get_YI();
  vector<vector<Real> > yield_independent_uncertainty   = endf_obj.get_DYI();
  vector<Real>          incident_ene_independent        = endf_obj.get_E();
  vector<Integer>       ene_int_data_independent        = endf_obj.get_I();

  //Set ENDF format data
  //frendy_obj.clear();
  //text
  //mat_no
  //mt_no
  //ZA
  //AWR
  frendy_obj.set_incident_ene_independent(incident_ene_independent);
  frendy_obj.set_ene_int_data_independent(ene_int_data_independent);
  frendy_obj.set_fp_data_independent(fp_data_independent);
  frendy_obj.set_state_designator_fp_independent(state_designator_fp_independent);
  frendy_obj.set_yield_independent(yield_independent);
  frendy_obj.set_yield_independent_uncertainty(yield_independent_uncertainty);

  //Clear declared data
  clr_obj.clear_vec_array2_real(fp_data_independent);
  clr_obj.clear_vec_array2_real(state_designator_fp_independent);
  clr_obj.clear_vec_array2_real(yield_independent);
  clr_obj.clear_vec_array2_real(yield_independent_uncertainty);
  incident_ene_independent.clear();
  ene_int_data_independent.clear();
}

