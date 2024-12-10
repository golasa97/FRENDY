#include "EndfUtils/MFxxMTyyyConverter/MF08MT459Converter.hpp"

using namespace frendy;

//constructor
MF08MT459Converter::MF08MT459Converter(void)
{
}

//destructor
MF08MT459Converter::~MF08MT459Converter(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//FissionDataContainer -> MF08MT459Parser
void MF08MT459Converter::convert_frendy_to_endf_format( FissionDataContainer& frendy_obj, MF08MT459Parser& endf_obj )
{
  //Get frendy data
  vector<vector<Real> > ZAFP = frendy_obj.get_fp_data_cumulative();
  vector<vector<Real> > FPS  = frendy_obj.get_state_designator_fp_cumulative();
  vector<vector<Real> > YC   = frendy_obj.get_yield_cumulative();
  vector<vector<Real> > DYC  = frendy_obj.get_yield_cumulative_uncertainty();
  vector<Real>          E    = frendy_obj.get_incident_ene_cumulative();
  vector<Integer>       I    = frendy_obj.get_ene_int_data_cumulative();

  Integer LE = static_cast<Integer>(E.size()) - 1;

  Integer mat_no = 0;
  if( static_cast<int>(ZAFP.size()) == 0 && static_cast<int>(FPS.size()) == 0 &&
      static_cast<int>(YC.size())   == 0 && static_cast<int>(DYC.size()) == 0 &&
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
  endf_obj.set_YC(YC);
  endf_obj.set_DYC(DYC);

  //Clear declared data
  clr_obj.clear_vec_array2_real(ZAFP);
  clr_obj.clear_vec_array2_real(FPS);
  clr_obj.clear_vec_array2_real(YC);
  clr_obj.clear_vec_array2_real(DYC);
  E.clear();
  I.clear();
  
  LE = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//MF08MT459Parser -> FissionDataContainer
void MF08MT459Converter::convert_endf_format_to_frendy( MF08MT459Parser& endf_obj, FissionDataContainer& frendy_obj )
{
  //Get frendy data
  vector<vector<Real> > fp_data_cumulative             = endf_obj.get_ZAFP();
  vector<vector<Real> > state_designator_fp_cumulative = endf_obj.get_FPS();
  vector<vector<Real> > yield_cumulative               = endf_obj.get_YC();
  vector<vector<Real> > yield_cumulative_uncertainty   = endf_obj.get_DYC();
  vector<Real>          incident_ene_cumulative        = endf_obj.get_E();
  vector<Integer>       ene_int_data_cumulative        = endf_obj.get_I();

  //Set ENDF format data
  //frendy_obj.clear();
  //text
  //mat_no
  //mt_no
  //ZA
  //AWR
  frendy_obj.set_incident_ene_cumulative(incident_ene_cumulative);
  frendy_obj.set_ene_int_data_cumulative(ene_int_data_cumulative);
  frendy_obj.set_fp_data_cumulative(fp_data_cumulative);
  frendy_obj.set_state_designator_fp_cumulative(state_designator_fp_cumulative);
  frendy_obj.set_yield_cumulative(yield_cumulative);
  frendy_obj.set_yield_cumulative_uncertainty(yield_cumulative_uncertainty);

  //Clear declared data
  clr_obj.clear_vec_array2_real(fp_data_cumulative);
  clr_obj.clear_vec_array2_real(state_designator_fp_cumulative);
  clr_obj.clear_vec_array2_real(yield_cumulative);
  clr_obj.clear_vec_array2_real(yield_cumulative_uncertainty);
  incident_ene_cumulative.clear();
  ene_int_data_cumulative.clear();
}

