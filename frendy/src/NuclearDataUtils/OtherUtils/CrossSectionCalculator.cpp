#include "NuclearDataUtils/OtherUtils/CrossSectionCalculator.hpp"

using namespace frendy;

//constructor
CrossSectionCalculator::CrossSectionCalculator(void)
{
}

//destructor
CrossSectionCalculator::~CrossSectionCalculator(void)
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Real8 CrossSectionCalculator::calc_xs_data_double
                                (Real8 ene_data, Real8 xs_data,
                                 vector<Real8>& multi_ene_vec, vector<Real8>& multi_xs_vec)
{
  vector<Integer> multi_nbt_void, multi_int_void;
  multi_nbt_void.clear();
  multi_int_void.clear();

  return calc_xs_data_double(ene_data, xs_data, multi_nbt_void, multi_int_void, multi_ene_vec, multi_xs_vec);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Real  CrossSectionCalculator::calc_xs_data
                                (Real ene_data, Real xs_data,
                                 vector<Real>& multi_ene_vec, vector<Real>& multi_xs_vec)
{
  vector<Integer> multi_nbt_void, multi_int_void;
  multi_nbt_void.clear();
  multi_int_void.clear();

  return calc_xs_data(ene_data, xs_data, multi_nbt_void, multi_int_void, multi_ene_vec, multi_xs_vec);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Real8 CrossSectionCalculator::calc_xs_data_double
                                (Real8 ene_data, Real8 xs_data,
                                 vector<Integer>& multi_nbt_vec, vector<Integer>& multi_int_vec,
                                 vector<Real8>&   multi_ene_vec, vector<Real8>&   multi_xs_vec)
{
  if( static_cast<int>(multi_ene_vec.size()) == 0 || static_cast<int>(multi_xs_vec.size()) == 0 )
  {
    return xs_data;
  }


  Real8 multi_data = 0.0;
  if( static_cast<int>(multi_nbt_vec.size()) == 0 || static_cast<int>(multi_int_vec.size()) == 0 )
  {
    ti_obj.interpolation_1d(int_lin_lin, ene_data, multi_data, multi_ene_vec, multi_xs_vec);
  }
  else
  {
    ti_obj.interpolation_tab1(ene_data, multi_data, multi_nbt_vec, multi_int_vec,
                                                    multi_ene_vec, multi_xs_vec);
  }

  return xs_data * multi_data;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Real  CrossSectionCalculator::calc_xs_data
                                (Real ene_data, Real xs_data,
                                 vector<Integer>& multi_nbt_vec, vector<Integer>& multi_int_vec,
                                 vector<Real>&    multi_ene_vec, vector<Real>&    multi_vec)
{
  if( static_cast<int>(multi_ene_vec.size()) == 0 || static_cast<int>(multi_vec.size()) == 0 )
  {
    return xs_data;
  }


  Real multi_data = 0.0;
  if( static_cast<int>(multi_nbt_vec.size()) == 0 || static_cast<int>(multi_int_vec.size()) == 0 )
  {
    ti_obj.interpolation_1d(int_lin_lin, ene_data, multi_data, multi_ene_vec, multi_vec);
  }
  else
  {
    ti_obj.interpolation_tab1(ene_data, multi_data, multi_nbt_vec, multi_int_vec,
                                                    multi_ene_vec, multi_vec);
  }

  return xs_data * multi_data;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Real8 CrossSectionCalculator::calc_xs_data_double
                                (Real8 ene_data,
                                 vector<Integer>& xs_nbt_vec,    vector<Integer>& xs_int_vec,
                                 vector<Real8>&   xs_ene_vec,    vector<Real8>&   xs_vec,
                                 vector<Integer>& multi_nbt_vec, vector<Integer>& multi_int_vec,
                                 vector<Real8>&   multi_ene_vec, vector<Real8>&   multi_vec)
{
  Real8 xs_data = 0.0;
  ti_obj.interpolation_tab1(ene_data, xs_data, xs_nbt_vec, xs_int_vec, xs_ene_vec, xs_vec);

  return calc_xs_data_double(ene_data, xs_data,
                             multi_nbt_vec, multi_int_vec, multi_ene_vec, multi_vec);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Real  CrossSectionCalculator::calc_xs_data
                                (Real ene_data,
                                 vector<Integer>& xs_nbt_vec,    vector<Integer>& xs_int_vec,
                                 vector<Real>&    xs_ene_vec,    vector<Real>&    xs_vec,
                                 vector<Integer>& multi_nbt_vec, vector<Integer>& multi_int_vec,
                                 vector<Real>&    multi_ene_vec, vector<Real>&    multi_vec)
{
  Real xs_data = 0.0;
  ti_obj.interpolation_tab1(ene_data, xs_data, xs_nbt_vec, xs_int_vec, xs_ene_vec, xs_vec);

  return calc_xs_data(ene_data, xs_data, multi_nbt_vec, multi_int_vec, multi_ene_vec, multi_vec);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

vector<Real> CrossSectionCalculator::calc_xs_data(Real ene_data, CrossSectionDataContainer&       xs_obj,
                                                                 RadioactiveProductDataContainer& rad_obj)
{
  vector<Integer>          xs_nbt_vec    = xs_obj.get_xs_range_data();
  vector<Integer>          xs_int_vec    = xs_obj.get_xs_int_data();
  vector<Real>             xs_ene_vec    = xs_obj.get_xs_ene_data();
  vector<Real>             xs_vec        = xs_obj.get_xs_data();
  vector<vector<Integer> > multi_nbt_vec = rad_obj.get_multiplicity_range_data();
  vector<vector<Integer> > multi_int_vec = rad_obj.get_multiplicity_int_data();
  vector<vector<Real> >    multi_ene_vec = rad_obj.get_multiplicity_ene_data();
  vector<vector<Real> >    multi_vec     = rad_obj.get_multiplicity_data();

  int i_max = static_cast<int>(multi_vec.size());
  vector<Real> xs_data;
  xs_data.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    xs_data[i] = calc_xs_data
                   (ene_data, xs_nbt_vec,       xs_int_vec,       xs_ene_vec,       xs_vec,
                              multi_nbt_vec[i], multi_int_vec[i], multi_ene_vec[i], multi_vec[i]);
  }

  return xs_data;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

vector<Real> CrossSectionCalculator::calc_xs_data(Real ene_data, CrossSectionDataContainer& xs_obj,
                                                                 PhotonDataContainer&       photon_obj)
{
  vector<Integer>          xs_nbt_vec    = xs_obj.get_xs_range_data();
  vector<Integer>          xs_int_vec    = xs_obj.get_xs_int_data();
  vector<Real>             xs_ene_vec    = xs_obj.get_xs_ene_data();
  vector<Real>             xs_vec        = xs_obj.get_xs_data();
  vector<vector<Integer> > multi_nbt_vec = photon_obj.get_photon_production_xs_range_data();
  vector<vector<Integer> > multi_int_vec = photon_obj.get_photon_production_xs_int_data();
  vector<vector<Real> >    multi_ene_vec = photon_obj.get_photon_production_xs_ene_data();
  vector<vector<Real> >    multi_vec     = photon_obj.get_photon_production_xs_data();

  int i_max = static_cast<int>(multi_vec.size());
  vector<Real> xs_data;
  xs_data.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    xs_data[i] = calc_xs_data
                   (ene_data, xs_nbt_vec,       xs_int_vec,       xs_ene_vec,       xs_vec,
                              multi_nbt_vec[i], multi_int_vec[i], multi_ene_vec[i], multi_vec[i]);
  }

  return xs_data;
}

