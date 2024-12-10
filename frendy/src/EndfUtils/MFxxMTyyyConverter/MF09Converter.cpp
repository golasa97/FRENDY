#include "EndfUtils/MFxxMTyyyConverter/MF09Converter.hpp"

using namespace frendy;

//constructor
MF09Converter::MF09Converter(void)
{
}

//destructor
MF09Converter::~MF09Converter(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//RadioactiveProductDataContainer -> MF09Parser
void MF09Converter::convert_frendy_to_endf_format( RadioactiveProductDataContainer& frendy_obj, MF09Parser& endf_obj )
{
  //Get frendy data
  Integer                  mt_no   = frendy_obj.get_reaction_type();
  Integer                  LIS     = frendy_obj.get_multiplicity_state_no_target();
  vector<Integer>          LFS     = frendy_obj.get_multiplicity_state_no_product();
  vector<Real>             QM      = frendy_obj.get_multiplicity_q_value_mass();
  vector<Real>             QI      = frendy_obj.get_multiplicity_q_value();
  vector<Integer>          IZAP    = frendy_obj.get_multiplicity_mat_data_product();
  vector<vector<Integer> > INT_Y   = frendy_obj.get_multiplicity_int_data();
  vector<vector<Integer> > NBT_Y   = frendy_obj.get_multiplicity_range_data();
  vector<vector<Real> >    E_INT_Y = frendy_obj.get_multiplicity_ene_data();
  vector<vector<Real> >    Y_TAB   = frendy_obj.get_multiplicity_data();

  Integer mat_no = 0;
  if( LIS == 0 &&
      static_cast<int>(LFS.size())     == 0 && static_cast<int>(QM.size())    == 0 &&
      static_cast<int>(QI.size())      == 0 && static_cast<int>(IZAP.size())  == 0 &&
      static_cast<int>(INT_Y.size())   == 0 && static_cast<int>(NBT_Y.size()) == 0 &&
      static_cast<int>(E_INT_Y.size()) == 0 && static_cast<int>(Y_TAB.size()) == 0 )
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
  endf_obj.set_NBT_Y(NBT_Y);
  endf_obj.set_INT_Y(INT_Y);
  endf_obj.set_E_INT_Y(E_INT_Y);
  endf_obj.set_Y_TAB(Y_TAB);

  //Clear declared data
  mt_no   = 0;
  LIS     = 0;
  LFS.clear();
  QM.clear();
  QI.clear();
  IZAP.clear();
  clr_obj.clear_vec_array2_int(INT_Y);
  clr_obj.clear_vec_array2_int(NBT_Y);
  clr_obj.clear_vec_array2_real(E_INT_Y);
  clr_obj.clear_vec_array2_real(Y_TAB);
  
  NS = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//MF09Parser -> RadioactiveProductDataContainer
void MF09Converter::convert_endf_format_to_frendy( MF09Parser& endf_obj, RadioactiveProductDataContainer& frendy_obj )
{
  //Get frendy data
  Integer                  reaction_type                 = endf_obj.get_mt_no();
  Integer                  multiplicity_state_no_target  = endf_obj.get_LIS();
  vector<Integer>          multiplicity_state_no_product = endf_obj.get_LFS();
  vector<Real>             multiplicity_q_value_mass     = endf_obj.get_QM();
  vector<Real>             multiplicity_q_value          = endf_obj.get_QI();
  vector<Integer>          multiplicity_mat_data_product = endf_obj.get_IZAP();
  vector<vector<Integer> > multiplicity_int_data         = endf_obj.get_INT_Y();
  vector<vector<Integer> > multiplicity_range_data       = endf_obj.get_NBT_Y();
  vector<vector<Real> >    multiplicity_ene_data         = endf_obj.get_E_INT_Y();
  vector<vector<Real> >    multiplicity_data             = endf_obj.get_Y_TAB();

  if( multiplicity_state_no_target == 0 &&
      static_cast<int>(multiplicity_state_no_product.size()) == 0 &&
      static_cast<int>(multiplicity_q_value_mass.size())     == 0 &&
      static_cast<int>(multiplicity_q_value.size())          == 0 &&
      static_cast<int>(multiplicity_mat_data_product.size()) == 0 &&
      static_cast<int>(multiplicity_int_data.size())         == 0 &&
      static_cast<int>(multiplicity_range_data.size())       == 0 &&
      static_cast<int>(multiplicity_ene_data.size())         == 0 &&
      static_cast<int>(multiplicity_data.size())             == 0 )
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
  frendy_obj.set_multiplicity_state_no_target(multiplicity_state_no_target);
  frendy_obj.set_multiplicity_q_value_mass(multiplicity_q_value_mass);
  frendy_obj.set_multiplicity_q_value(multiplicity_q_value);
  frendy_obj.set_multiplicity_mat_data_product(multiplicity_mat_data_product);
  frendy_obj.set_multiplicity_state_no_product(multiplicity_state_no_product);
  frendy_obj.set_multiplicity_range_data(multiplicity_range_data);
  frendy_obj.set_multiplicity_int_data(multiplicity_int_data);
  frendy_obj.set_multiplicity_ene_data(multiplicity_ene_data);
  frendy_obj.set_multiplicity_data(multiplicity_data);

  //Clear declared data
  reaction_type                = 0;
  multiplicity_state_no_target = 0;
  multiplicity_state_no_product.clear();
  multiplicity_q_value_mass.clear();
  multiplicity_q_value.clear();
  multiplicity_mat_data_product.clear();
  clr_obj.clear_vec_array2_int(multiplicity_int_data);
  clr_obj.clear_vec_array2_int(multiplicity_range_data);
  clr_obj.clear_vec_array2_real(multiplicity_ene_data);
  clr_obj.clear_vec_array2_real(multiplicity_data);
}

