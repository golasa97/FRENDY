#include "EndfUtils/MFxxMTyyyConverter/MF03Converter.hpp"

using namespace frendy;

//constructor
MF03Converter::MF03Converter(void)
{
}

//destructor
MF03Converter::~MF03Converter(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//CrossSectionDataContainer -> MF03Parser
void MF03Converter::convert_frendy_to_endf_format( CrossSectionDataContainer& frendy_obj, MF03Parser& endf_obj )
{
  //Get frendy data
  Integer         mt_no     = frendy_obj.get_reaction_type();
  Real            QM        = frendy_obj.get_q_value_mass();
  Real            QI        = frendy_obj.get_q_value();
  Integer         LR        = frendy_obj.get_reaction_flg();
  vector<Integer> INT_SIG   = frendy_obj.get_xs_int_data();
  vector<Integer> NBT_SIG   = frendy_obj.get_xs_range_data();
  vector<Real>    E_INT_SIG = frendy_obj.get_xs_ene_data();
  vector<Real>    SIG_TAB   = frendy_obj.get_xs_data();

  Integer mat_no = 0;
  if( fabs(QM) < min_value && fabs(QI) < min_value && LR == 0 &&
      static_cast<int>(INT_SIG.size())   == 0 && static_cast<int>(NBT_SIG.size()) == 0 &&
      static_cast<int>(E_INT_SIG.size()) == 0 && static_cast<int>(SIG_TAB.size()) == 0 )
  {
    mat_no = unassigned_mat_no;
    mt_no  = unassigned_mt_no;
  }

  //Set ENDF format data
  endf_obj.clear();
  endf_obj.set_mat_no(mat_no);
  endf_obj.set_mt_no(mt_no);
  endf_obj.set_QM(QM);
  endf_obj.set_QI(QI);
  endf_obj.set_LR(LR);
  endf_obj.set_NBT_SIG(NBT_SIG);
  endf_obj.set_INT_SIG(INT_SIG);
  endf_obj.set_E_INT_SIG(E_INT_SIG);
  endf_obj.set_SIG_TAB(SIG_TAB);

  //Clear declared data
  mt_no     = 0;
  QM        = 0.0;
  QI        = 0.0;
  LR        = 0;
  INT_SIG.clear();
  NBT_SIG.clear();
  E_INT_SIG.clear();
  SIG_TAB.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//MF03Parser -> CrossSectionDataContainer
void MF03Converter::convert_endf_format_to_frendy( MF03Parser& endf_obj, CrossSectionDataContainer& frendy_obj )
{
  //Get frendy data
  Integer         reaction_type = endf_obj.get_mt_no();
  Real            q_value_mass  = endf_obj.get_QM();
  Real            q_value       = endf_obj.get_QI();
  Integer         reaction_flg  = endf_obj.get_LR();
  vector<Integer> xs_int_data   = endf_obj.get_INT_SIG();
  vector<Integer> xs_range_data = endf_obj.get_NBT_SIG();
  vector<Real>    xs_ene_data   = endf_obj.get_E_INT_SIG();
  vector<Real>    xs_data       = endf_obj.get_SIG_TAB();

  if( fabs(q_value_mass) < min_value && fabs(q_value) < min_value && reaction_flg == 0 &&
      static_cast<int>(xs_int_data.size()) == 0 && static_cast<int>(xs_range_data.size()) == 0 &&
      static_cast<int>(xs_ene_data.size()) == 0 && static_cast<int>(xs_data.size())       == 0 )
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
  frendy_obj.set_q_value_mass(q_value_mass);
  frendy_obj.set_q_value(q_value);
  frendy_obj.set_reaction_flg(reaction_flg);
  frendy_obj.set_xs_range_data(xs_range_data);
  frendy_obj.set_xs_int_data(xs_int_data);
  frendy_obj.set_xs_ene_data(xs_ene_data);
  frendy_obj.set_xs_data(xs_data);

  //Clear declared data
  reaction_type = 0;
  q_value_mass  = 0.0;
  q_value       = 0.0;
  reaction_flg  = 0;
  xs_int_data.clear();
  xs_range_data.clear();
  xs_ene_data.clear();
  xs_data.clear();
}

