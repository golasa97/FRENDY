#include "EndfUtils/MFxxMTyyyConverter/MF01MT456Converter.hpp"

using namespace frendy;

//constructor
MF01MT456Converter::MF01MT456Converter(void)
{
}

//destructor
MF01MT456Converter::~MF01MT456Converter(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//FissionDataContainer -> MF01MT456Parser
void MF01MT456Converter::convert_frendy_to_endf_format( FissionDataContainer& frendy_obj, MF01MT456Parser& endf_obj )
{
  //Get frendy data
  Integer         LNU   = frendy_obj.get_nu_p_bar_repr_flg();
  vector<Real>    NU;
  if( LNU == 1 )
  {
    NU = frendy_obj.get_nu_p_bar_polynomial_coef();
  }
  else
  {
    NU = frendy_obj.get_nu_p_bar_data();
  }
  vector<Integer> NBT   = frendy_obj.get_nu_p_bar_range_data();
  vector<Integer> INT   = frendy_obj.get_nu_p_bar_int_data();
  vector<Real>    E_INT = frendy_obj.get_nu_p_bar_ene_data();

  Integer NC = static_cast<Integer>(NU.size());
  Integer NR = static_cast<Integer>(NBT.size());
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
  endf_obj.set_NBT(NBT);
  endf_obj.set_INT(INT);
  endf_obj.set_E_INT(E_INT);
  endf_obj.set_NU(NU);

  //Clear declared data
  LNU   = 0;
  NU.clear();
  NBT.clear();
  INT.clear();
  E_INT.clear();
  NU.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//MF01MT456Parser -> FissionDataContainer
void MF01MT456Converter::convert_endf_format_to_frendy( MF01MT456Parser& endf_obj, FissionDataContainer& frendy_obj )
{
  //Get frendy data
  Integer         nu_p_bar_repr_flg        = endf_obj.get_LNU();
  vector<Real>    nu_p_bar_polynomial_coef = endf_obj.get_NU();
  vector<Integer> nu_p_bar_int_data        = endf_obj.get_INT();
  vector<Integer> nu_p_bar_range_data      = endf_obj.get_NBT();
  vector<Real>    nu_p_bar_ene_data        = endf_obj.get_E_INT();
  vector<Real>    nu_p_bar_data            = endf_obj.get_NU();

  if( nu_p_bar_repr_flg == 1 )
  {
    nu_p_bar_data.clear();
  }
  else
  {
    nu_p_bar_polynomial_coef.clear();
  }

  //Set ENDF format data
  //frendy_obj.clear();
  //text
  //mat_no
  //ZA
  //AWR
  frendy_obj.set_nu_p_bar_repr_flg(nu_p_bar_repr_flg);
  frendy_obj.set_nu_p_bar_int_data(nu_p_bar_int_data);
  frendy_obj.set_nu_p_bar_range_data(nu_p_bar_range_data);
  frendy_obj.set_nu_p_bar_ene_data(nu_p_bar_ene_data);
  frendy_obj.set_nu_p_bar_polynomial_coef(nu_p_bar_polynomial_coef);
  frendy_obj.set_nu_p_bar_data(nu_p_bar_data);

  //Clear declared data
  nu_p_bar_repr_flg        = 0;
  nu_p_bar_polynomial_coef.clear();
  nu_p_bar_int_data.clear();
  nu_p_bar_range_data.clear();
  nu_p_bar_ene_data.clear();
  nu_p_bar_data.clear();
}

