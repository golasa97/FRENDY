#include "EndfUtils/MFxxMTyyyConverter/MF27Converter.hpp"

using namespace frendy;

//constructor
MF27Converter::MF27Converter(void)
{
}

//destructor
MF27Converter::~MF27Converter(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//OtherNuclearDataContainer -> MF27Parser
void MF27Converter::convert_frendy_to_endf_format( OtherNuclearDataContainer& frendy_obj, MF27Parser& endf_obj )
{
  //Get frendy data
  Integer         mt_no   = frendy_obj.get_reaction_type();
  Real            Z       = frendy_obj.get_atomic_no();
  vector<Integer> INT_H   = frendy_obj.get_scat_func_int_data();
  vector<Integer> NBT_H   = frendy_obj.get_scat_func_range_data();
  vector<Real>    Q_INT_H = frendy_obj.get_scat_func_recoil_electron_data();
  vector<Real>    H_TAB   = frendy_obj.get_scat_func_data();
  //vector<Integer> INT_F   = frendy_obj.get_form_factor_int_data(); //Actual data name in Parser class is different (INT_H) 
  //vector<Integer> NBT_F   = frendy_obj.get_form_factor_range_data(); //Actual data name in Parser class is different (NBT_H) 
  //vector<Real>    E_INT_F = frendy_obj.get_form_factor_ene_data(); //Actual data name in Parser class is different (Q_INT_H) 
  //vector<Real>    F_TAB   = frendy_obj.get_form_factor_data(); //Actual data name in Parser class is different (H_TAB) 

  Integer mat_no = 0;
  if( fabs(Z) < min_value && 
      static_cast<int>(INT_H.size())   == 0 && static_cast<int>(NBT_H.size()) == 0 &&
      static_cast<int>(Q_INT_H.size()) == 0 && static_cast<int>(H_TAB.size()) == 0 )
  {
    mat_no = unassigned_mat_no;
    mt_no  = unassigned_mt_no;
  }

  //Set ENDF format data
  endf_obj.clear();
  endf_obj.set_mat_no(mat_no);
  endf_obj.set_mt_no(mt_no);
  endf_obj.set_Z(Z);
  endf_obj.set_NBT_H(NBT_H);
  endf_obj.set_INT_H(INT_H);
  endf_obj.set_Q_INT_H(Q_INT_H);
  endf_obj.set_H_TAB(H_TAB);
  //endf_obj.set_NBT_F(NBT_F); //Actual data name in Parser class is different (NBT_H) 
  //endf_obj.set_INT_F(INT_F); //Actual data name in Parser class is different (INT_H) 
  //endf_obj.set_E_INT_F(E_INT_F); //Actual data name in Parser class is different (Q_INT_H) 
  //endf_obj.set_F_TAB(F_TAB); //Actual data name in Parser class is different (H_TAB) 

  //Clear declared data
  mt_no   = 0;
  Z       = 0.0;
  INT_H.clear();
  NBT_H.clear();
  Q_INT_H.clear();
  H_TAB.clear();
  //INT_F.clear();
  //NBT_F.clear();
  //E_INT_F.clear();
  //F_TAB.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//MF27Parser -> OtherNuclearDataContainer
void MF27Converter::convert_endf_format_to_frendy( MF27Parser& endf_obj, OtherNuclearDataContainer& frendy_obj )
{
  //Get frendy data
  Integer         reaction_type                  = endf_obj.get_mt_no();
  Real            atomic_no                      = endf_obj.get_Z();
  vector<Integer> scat_func_int_data             = endf_obj.get_INT_H();
  vector<Integer> scat_func_range_data           = endf_obj.get_NBT_H();
  vector<Real>    scat_func_recoil_electron_data = endf_obj.get_Q_INT_H();
  vector<Real>    scat_func_data                 = endf_obj.get_H_TAB();
  vector<Integer> form_factor_int_data           = endf_obj.get_INT_F(); //Actual data name in Parser class is different (INT_H) 
  vector<Integer> form_factor_range_data         = endf_obj.get_NBT_F(); //Actual data name in Parser class is different (NBT_H) 
  vector<Real>    form_factor_ene_data           = endf_obj.get_E_INT_F(); //Actual data name in Parser class is different (Q_INT_H) 
  vector<Real>    form_factor_data               = endf_obj.get_F_TAB(); //Actual data name in Parser class is different (H_TAB) 

  if( fabs(atomic_no) < min_value &&
      static_cast<int>(scat_func_int_data.size()) == 0 && static_cast<int>(scat_func_range_data.size()) == 0 &&
      static_cast<int>(scat_func_recoil_electron_data.size()) == 0 &&
      static_cast<int>(scat_func_data.size())                 == 0 &&
      static_cast<int>(form_factor_int_data.size())           == 0 &&
      static_cast<int>(form_factor_range_data.size())         == 0 &&
      static_cast<int>(form_factor_ene_data.size())           == 0 &&
      static_cast<int>(form_factor_data.size())               == 0 )
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
  frendy_obj.set_atomic_no(atomic_no);
  frendy_obj.set_scat_func_range_data(scat_func_range_data);
  frendy_obj.set_scat_func_int_data(scat_func_int_data);
  frendy_obj.set_scat_func_recoil_electron_data(scat_func_recoil_electron_data);
  frendy_obj.set_scat_func_data(scat_func_data);
  frendy_obj.set_form_factor_range_data(form_factor_range_data); //Actual data name in Parser class is different (NBT_H) 
  frendy_obj.set_form_factor_int_data(form_factor_int_data); //Actual data name in Parser class is different (INT_H) 
  frendy_obj.set_form_factor_ene_data(form_factor_ene_data); //Actual data name in Parser class is different (Q_INT_H) 
  frendy_obj.set_form_factor_data(form_factor_data); //Actual data name in Parser class is different (H_TAB) 

  //Clear declared data
  reaction_type                  = 0;
  atomic_no                      = 0.0;
  scat_func_int_data.clear();
  scat_func_range_data.clear();
  scat_func_recoil_electron_data.clear();
  scat_func_data.clear();
  form_factor_int_data.clear();
  form_factor_range_data.clear();
  form_factor_ene_data.clear();
  form_factor_data.clear();
}

