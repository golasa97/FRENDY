#include "NuclearDataUtils/NuclearDataContainer/ResonanceData/BreitWignerDataContainer.hpp"

using namespace frendy;

//constructor
BreitWignerDataContainer::BreitWignerDataContainer(void)
{
  clear();
}

//destructor
BreitWignerDataContainer::~BreitWignerDataContainer(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void BreitWignerDataContainer::clear()
{
  q_value.clear();
  competitive_width_flg.clear();
  clr_obj.clear_vec_array2_real( ene_reso );
  clr_obj.clear_vec_array2_real( j_value_abs );
  clr_obj.clear_vec_array2_real( gam_width_tot );
  clr_obj.clear_vec_array2_real( gam_width_n );
  clr_obj.clear_vec_array2_real( gam_width_rad );
  clr_obj.clear_vec_array2_real( gam_width_fis );
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Getter
vector<Real> BreitWignerDataContainer::get_q_value()
{
  return q_value;
}

vector<Integer> BreitWignerDataContainer::get_competitive_width_flg()
{
  return competitive_width_flg;
}

vector<vector<Real> > BreitWignerDataContainer::get_ene_reso()
{
  return ene_reso;
}

vector<vector<Real> > BreitWignerDataContainer::get_j_value_abs()
{
  return j_value_abs;
}

vector<vector<Real> > BreitWignerDataContainer::get_gam_width_tot()
{
  return gam_width_tot;
}

vector<vector<Real> > BreitWignerDataContainer::get_gam_width_n()
{
  return gam_width_n;
}

vector<vector<Real> > BreitWignerDataContainer::get_gam_width_rad()
{
  return gam_width_rad;
}

vector<vector<Real> > BreitWignerDataContainer::get_gam_width_fis()
{
  return gam_width_fis;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void BreitWignerDataContainer::set_q_value( vector<Real> real_vec )
{
  q_value = real_vec;
  real_vec.clear();
}

void BreitWignerDataContainer::set_competitive_width_flg( vector<Integer> int_vec )
{
  competitive_width_flg = int_vec;
  int_vec.clear();
}

void BreitWignerDataContainer::set_ene_reso( vector<vector<Real> > real_vec )
{
  ene_reso = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void BreitWignerDataContainer::set_j_value_abs( vector<vector<Real> > real_vec )
{
  j_value_abs = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void BreitWignerDataContainer::set_gam_width_tot( vector<vector<Real> > real_vec )
{
  gam_width_tot = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void BreitWignerDataContainer::set_gam_width_n( vector<vector<Real> > real_vec )
{
  gam_width_n = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void BreitWignerDataContainer::set_gam_width_rad( vector<vector<Real> > real_vec )
{
  gam_width_rad = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void BreitWignerDataContainer::set_gam_width_fis( vector<vector<Real> > real_vec )
{
  gam_width_fis = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

