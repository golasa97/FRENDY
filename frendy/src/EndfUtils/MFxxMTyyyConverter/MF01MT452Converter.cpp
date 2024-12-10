#include "EndfUtils/MFxxMTyyyConverter/MF01MT452Converter.hpp"

using namespace frendy;

//constructor
MF01MT452Converter::MF01MT452Converter(void)
{
}

//destructor
MF01MT452Converter::~MF01MT452Converter(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//FissionDataContainer -> MF01MT452Parser
void MF01MT452Converter::convert_frendy_to_endf_format( FissionDataContainer& frendy_obj, MF01MT452Parser& endf_obj )
{
  //Get frendy data
  Integer         LNU   = frendy_obj.get_nu_bar_repr_flg();
  vector<Real>    C     = frendy_obj.get_nu_bar_polynomial_coef();
  vector<Integer> INT   = frendy_obj.get_nu_bar_int_data();
  vector<Integer> NBT   = frendy_obj.get_nu_bar_range_data();
  vector<Real>    E_INT = frendy_obj.get_nu_bar_ene_data();
  vector<Real>    NU    = frendy_obj.get_nu_bar_data();

  Integer NC = static_cast<Integer>(C.size());
  Integer NR = static_cast<Integer>(INT.size());
  Integer NP = static_cast<Integer>(E_INT.size());

  Integer mat_no = 0;
  if( LNU == 0 && NC == 0 && NR == 0 && NP == 0 )
  {
    mat_no = unassigned_mat_no;
  }
  
  //Set ENDF format data
  endf_obj.clear();
  endf_obj.set_mat_no(mat_no);
  endf_obj.set_LNU(LNU);
  endf_obj.set_NC(NC);
  endf_obj.set_NR(NR);
  endf_obj.set_NP(NP);
  endf_obj.set_C(C);
  endf_obj.set_NBT(NBT);
  endf_obj.set_INT(INT);
  endf_obj.set_E_INT(E_INT);
  endf_obj.set_NU(NU);

  //Clear declared data
  LNU   = 0;
  C.clear();
  INT.clear();
  NBT.clear();
  E_INT.clear();
  NU.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//MF01MT452Parser -> FissionDataContainer
void MF01MT452Converter::convert_endf_format_to_frendy( MF01MT452Parser& endf_obj, FissionDataContainer& frendy_obj )
{
  //Get frendy data
  Integer         nu_bar_repr_flg        = endf_obj.get_LNU();
  vector<Real>    nu_bar_polynomial_coef = endf_obj.get_C();
  vector<Integer> nu_bar_int_data        = endf_obj.get_INT();
  vector<Integer> nu_bar_range_data      = endf_obj.get_NBT();
  vector<Real>    nu_bar_ene_data        = endf_obj.get_E_INT();
  vector<Real>    nu_bar_data            = endf_obj.get_NU();

  //Set ENDF format data
  //frendy_obj.clear();
  //text
  //mat_no
  //ZA
  //AWR
  frendy_obj.set_nu_bar_repr_flg(nu_bar_repr_flg);
  frendy_obj.set_nu_bar_polynomial_coef(nu_bar_polynomial_coef);
  frendy_obj.set_nu_bar_range_data(nu_bar_range_data);
  frendy_obj.set_nu_bar_int_data(nu_bar_int_data);
  frendy_obj.set_nu_bar_ene_data(nu_bar_ene_data);
  frendy_obj.set_nu_bar_data(nu_bar_data);

  //Clear declared data
  nu_bar_repr_flg        = 0;
  nu_bar_polynomial_coef.clear();
  nu_bar_int_data.clear();
  nu_bar_range_data.clear();
  nu_bar_ene_data.clear();
  nu_bar_data.clear();
}

