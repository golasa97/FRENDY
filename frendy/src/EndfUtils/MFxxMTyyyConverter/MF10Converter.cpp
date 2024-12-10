#include "EndfUtils/MFxxMTyyyConverter/MF10Converter.hpp"

using namespace frendy;

//constructor
MF10Converter::MF10Converter(void)
{
}

//destructor
MF10Converter::~MF10Converter(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//RadioactiveProductDataContainer -> MF10Parser
void MF10Converter::convert_frendy_to_endf_format( RadioactiveProductDataContainer& frendy_obj, MF10Parser& endf_obj )
{
  //Get frendy data
  Integer                  mt_no   = frendy_obj.get_reaction_type();
  Integer                  LIS     = frendy_obj.get_xs_state_no_target();
  vector<Integer>          LFS     = frendy_obj.get_xs_state_no_product();
  vector<Real>             QM      = frendy_obj.get_xs_q_value_mass();
  vector<Real>             QI      = frendy_obj.get_xs_q_value();
  vector<Integer>          IZAP    = frendy_obj.get_xs_mat_data_product();
  vector<vector<Integer> > INT_S   = frendy_obj.get_xs_int_data();
  vector<vector<Integer> > NBT_S   = frendy_obj.get_xs_range_data();
  vector<vector<Real> >    E_INT_S = frendy_obj.get_xs_ene_data();
  vector<vector<Real> >    S_TAB   = frendy_obj.get_xs_data();
  
  Integer mat_no = 0;
  if( LIS == 0 &&
      static_cast<int>(LFS.size())     == 0 && static_cast<int>(QM.size())    == 0 &&
      static_cast<int>(QI.size())      == 0 && static_cast<int>(IZAP.size())  == 0 &&
      static_cast<int>(INT_S.size())   == 0 && static_cast<int>(NBT_S.size()) == 0 &&
      static_cast<int>(E_INT_S.size()) == 0 && static_cast<int>(S_TAB.size()) == 0 )
  {
    mat_no = unassigned_mat_no;
    mt_no  = unassigned_mt_no;
  }

  Integer NS = static_cast<Integer>(QM.size());

  //Set ENDF format data
  endf_obj.clear();
  endf_obj.set_mat_no(mat_no);
  endf_obj.set_mt_no(mt_no);
  endf_obj.set_LIS(LIS);
  endf_obj.set_NS(NS);
  endf_obj.set_QM(QM);
  endf_obj.set_QI(QI);
  endf_obj.set_IZAP(IZAP);
  endf_obj.set_LFS(LFS);
  endf_obj.set_NBT_S(NBT_S);
  endf_obj.set_INT_S(INT_S);
  endf_obj.set_E_INT_S(E_INT_S);
  endf_obj.set_S_TAB(S_TAB);

  //Clear declared data
  mt_no   = 0;
  LIS     = 0;
  LFS.clear();
  QM.clear();
  QI.clear();
  IZAP.clear();
  clr_obj.clear_vec_array2_int(INT_S);
  clr_obj.clear_vec_array2_int(NBT_S);
  clr_obj.clear_vec_array2_real(E_INT_S);
  clr_obj.clear_vec_array2_real(S_TAB);
  
  NS = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//MF10Parser -> RadioactiveProductDataContainer
void MF10Converter::convert_endf_format_to_frendy( MF10Parser& endf_obj, RadioactiveProductDataContainer& frendy_obj )
{
  //Get frendy data
  Integer                  reaction_type       = endf_obj.get_mt_no();
  Integer                  xs_state_no_target  = endf_obj.get_LIS();
  vector<Integer>          xs_state_no_product = endf_obj.get_LFS();
  vector<Real>             xs_q_value_mass     = endf_obj.get_QM();
  vector<Real>             xs_q_value          = endf_obj.get_QI();
  vector<Integer>          xs_mat_data_product = endf_obj.get_IZAP();
  vector<vector<Integer> > xs_int_data         = endf_obj.get_INT_S();
  vector<vector<Integer> > xs_range_data       = endf_obj.get_NBT_S();
  vector<vector<Real> >    xs_ene_data         = endf_obj.get_E_INT_S();
  vector<vector<Real> >    xs_data             = endf_obj.get_S_TAB();

  if( xs_state_no_target == 0 &&
      static_cast<int>(xs_state_no_product.size()) == 0 && static_cast<int>(xs_q_value_mass.size()) == 0 &&
      static_cast<int>(xs_q_value.size())  == 0 && static_cast<int>(xs_mat_data_product.size()) == 0 &&
      static_cast<int>(xs_int_data.size()) == 0 && static_cast<int>(xs_range_data.size())       == 0 &&
      static_cast<int>(xs_ene_data.size()) == 0 && static_cast<int>(xs_data.size())             == 0 )
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
  frendy_obj.set_xs_state_no_target(xs_state_no_target);
  frendy_obj.set_xs_q_value_mass(xs_q_value_mass);
  frendy_obj.set_xs_q_value(xs_q_value);
  frendy_obj.set_xs_mat_data_product(xs_mat_data_product);
  frendy_obj.set_xs_state_no_product(xs_state_no_product);
  frendy_obj.set_xs_range_data(xs_range_data);
  frendy_obj.set_xs_int_data(xs_int_data);
  frendy_obj.set_xs_ene_data(xs_ene_data);
  frendy_obj.set_xs_data(xs_data);

  //Clear declared data
  reaction_type      = 0;
  xs_state_no_target = 0;
  xs_state_no_product.clear();
  xs_q_value_mass.clear();
  xs_q_value.clear();
  xs_mat_data_product.clear();
  clr_obj.clear_vec_array2_int(xs_int_data);
  clr_obj.clear_vec_array2_int(xs_range_data);
  clr_obj.clear_vec_array2_real(xs_ene_data);
  clr_obj.clear_vec_array2_real(xs_data);
}

