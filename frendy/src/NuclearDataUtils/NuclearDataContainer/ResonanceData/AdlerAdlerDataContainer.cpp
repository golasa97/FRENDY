#include "NuclearDataUtils/NuclearDataContainer/ResonanceData/AdlerAdlerDataContainer.hpp"

using namespace frendy;

//constructor
AdlerAdlerDataContainer::AdlerAdlerDataContainer(void)
{
  clear();
}

//destructor
AdlerAdlerDataContainer::~AdlerAdlerDataContainer(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void AdlerAdlerDataContainer::clear()
{
  adler_calc_flg = 0;

  back_ground_tot.clear();
  back_ground_fis.clear();
  back_ground_rad.clear();
  clr_obj.clear_vec_array2_real( j_value_abs );
  clr_obj.clear_vec_array3_real( ene_reso_tot );
  clr_obj.clear_vec_array3_real( ene_reso_fis );
  clr_obj.clear_vec_array3_real( ene_reso_rad );
  clr_obj.clear_vec_array3_real( gam_width_half_tot );
  clr_obj.clear_vec_array3_real( gam_width_half_fis );
  clr_obj.clear_vec_array3_real( gam_width_half_rad );
  clr_obj.clear_vec_array3_real( symmetrical_data_tot );
  clr_obj.clear_vec_array3_real( non_symmetrical_data_tot );
  clr_obj.clear_vec_array3_real( symmetrical_data_fis );
  clr_obj.clear_vec_array3_real( non_symmetrical_data_fis );
  clr_obj.clear_vec_array3_real( symmetrical_data_rad );
  clr_obj.clear_vec_array3_real( non_symmetrical_data_rad );
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Getter
Integer AdlerAdlerDataContainer::get_adler_calc_flg()
{
  return adler_calc_flg;
}

vector<Real> AdlerAdlerDataContainer::get_back_ground_tot()
{
  return back_ground_tot;
}

vector<Real> AdlerAdlerDataContainer::get_back_ground_fis()
{
  return back_ground_fis;
}

vector<Real> AdlerAdlerDataContainer::get_back_ground_rad()
{
  return back_ground_rad;
}

vector<vector<Real> > AdlerAdlerDataContainer::get_j_value_abs()
{
  return j_value_abs;
}

vector<vector<vector<Real> > > AdlerAdlerDataContainer::get_ene_reso_tot()
{
  return ene_reso_tot;
}

vector<vector<vector<Real> > > AdlerAdlerDataContainer::get_ene_reso_fis()
{
  return ene_reso_fis;
}

vector<vector<vector<Real> > > AdlerAdlerDataContainer::get_ene_reso_rad()
{
  return ene_reso_rad;
}

vector<vector<vector<Real> > > AdlerAdlerDataContainer::get_gam_width_half_tot()
{
  return gam_width_half_tot;
}

vector<vector<vector<Real> > > AdlerAdlerDataContainer::get_gam_width_half_fis()
{
  return gam_width_half_fis;
}

vector<vector<vector<Real> > > AdlerAdlerDataContainer::get_gam_width_half_rad()
{
  return gam_width_half_rad;
}

vector<vector<vector<Real> > > AdlerAdlerDataContainer::get_symmetrical_data_tot()
{
  return symmetrical_data_tot;
}

vector<vector<vector<Real> > > AdlerAdlerDataContainer::get_non_symmetrical_data_tot()
{
  return non_symmetrical_data_tot;
}

vector<vector<vector<Real> > > AdlerAdlerDataContainer::get_symmetrical_data_fis()
{
  return symmetrical_data_fis;
}

vector<vector<vector<Real> > > AdlerAdlerDataContainer::get_non_symmetrical_data_fis()
{
  return non_symmetrical_data_fis;
}

vector<vector<vector<Real> > > AdlerAdlerDataContainer::get_symmetrical_data_rad()
{
  return symmetrical_data_rad;
}

vector<vector<vector<Real> > > AdlerAdlerDataContainer::get_non_symmetrical_data_rad()
{
  return non_symmetrical_data_rad;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void AdlerAdlerDataContainer::set_adler_calc_flg( Integer int_data )
{
  adler_calc_flg = int_data;
}

void AdlerAdlerDataContainer::set_back_ground_tot( vector<Real> real_vec )
{
  back_ground_tot = real_vec;
  real_vec.clear();
}

void AdlerAdlerDataContainer::set_back_ground_fis( vector<Real> real_vec )
{
  back_ground_fis = real_vec;
  real_vec.clear();
}

void AdlerAdlerDataContainer::set_back_ground_rad( vector<Real> real_vec )
{
  back_ground_rad = real_vec;
  real_vec.clear();
}

void AdlerAdlerDataContainer::set_j_value_abs( vector<vector<Real> > real_vec )
{
  j_value_abs = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void AdlerAdlerDataContainer::set_ene_reso_tot( vector<vector<vector<Real> > > real_vec )
{
  ene_reso_tot = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

void AdlerAdlerDataContainer::set_ene_reso_fis( vector<vector<vector<Real> > > real_vec )
{
  ene_reso_fis = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

void AdlerAdlerDataContainer::set_ene_reso_rad( vector<vector<vector<Real> > > real_vec )
{
  ene_reso_rad = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

void AdlerAdlerDataContainer::set_gam_width_half_tot( vector<vector<vector<Real> > > real_vec )
{
  gam_width_half_tot = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

void AdlerAdlerDataContainer::set_gam_width_half_fis( vector<vector<vector<Real> > > real_vec )
{
  gam_width_half_fis = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

void AdlerAdlerDataContainer::set_gam_width_half_rad( vector<vector<vector<Real> > > real_vec )
{
  gam_width_half_rad = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

void AdlerAdlerDataContainer::set_symmetrical_data_tot( vector<vector<vector<Real> > > real_vec )
{
  symmetrical_data_tot = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

void AdlerAdlerDataContainer::set_non_symmetrical_data_tot( vector<vector<vector<Real> > > real_vec )
{
  non_symmetrical_data_tot = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

void AdlerAdlerDataContainer::set_symmetrical_data_fis( vector<vector<vector<Real> > > real_vec )
{
  symmetrical_data_fis = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

void AdlerAdlerDataContainer::set_non_symmetrical_data_fis( vector<vector<vector<Real> > > real_vec )
{
  non_symmetrical_data_fis = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

void AdlerAdlerDataContainer::set_symmetrical_data_rad( vector<vector<vector<Real> > > real_vec )
{
  symmetrical_data_rad = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

void AdlerAdlerDataContainer::set_non_symmetrical_data_rad( vector<vector<vector<Real> > > real_vec )
{
  non_symmetrical_data_rad = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

