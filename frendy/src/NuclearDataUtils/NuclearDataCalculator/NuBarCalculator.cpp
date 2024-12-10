#include "NuclearDataUtils/NuclearDataCalculator/NuBarCalculator.hpp"

using namespace frendy;

//constructor
NuBarCalculator::NuBarCalculator(void)
{
}

//destructor
NuBarCalculator::~NuBarCalculator(void)
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Real8 NuBarCalculator::calc_nu_bar(NuclearDataObject& nucl_data_obj, Real8 ene_val)
{
  Real8 nu_bar;
  
  if( nucl_data_obj.get_fis_data_obj().get_nu_bar_repr_flg() == 1 )
  {
    vector<Real> coef = nucl_data_obj.get_fis_data_obj().get_nu_bar_polynomial_coef();
    nu_bar = calc_polynomial_expansion(coef, ene_val);
    coef.clear();
  }
  else
  {
    vector<Integer> nbt_vec = nucl_data_obj.get_fis_data_obj().get_nu_bar_range_data();
    vector<Integer> int_vec = nucl_data_obj.get_fis_data_obj().get_nu_bar_int_data();
    vector<Real>    ene_vec = nucl_data_obj.get_fis_data_obj().get_nu_bar_ene_data();
    vector<Real>    nu_vec  = nucl_data_obj.get_fis_data_obj().get_nu_bar_data();
    
    ti_obj.interpolation_tab1(ene_val, nu_bar, nbt_vec, int_vec, ene_vec, nu_vec);
    
    nbt_vec.clear();
    int_vec.clear();
    ene_vec.clear();
    nu_vec.clear();
  }
  
  return nu_bar;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Real8 NuBarCalculator::calc_nu_d_bar(NuclearDataObject& nucl_data_obj, Real8 ene_val)
{
  Real8 nu_bar;

  if( nucl_data_obj.get_fis_data_obj().get_nu_d_bar_repr_flg() == 1 )
  {
    vector<Real> coef = nucl_data_obj.get_fis_data_obj().get_nu_d_bar_polynomial_coef();
    nu_bar = calc_polynomial_expansion(coef, ene_val);
    coef.clear();
  }
  else
  {
    vector<Integer> nbt_vec = nucl_data_obj.get_fis_data_obj().get_nu_d_bar_range_data();
    vector<Integer> int_vec = nucl_data_obj.get_fis_data_obj().get_nu_d_bar_int_data();
    vector<Real>    ene_vec = nucl_data_obj.get_fis_data_obj().get_nu_d_bar_ene_data();
    vector<Real>    nu_vec  = nucl_data_obj.get_fis_data_obj().get_nu_d_bar_data();

    ti_obj.interpolation_tab1(ene_val, nu_bar, nbt_vec, int_vec, ene_vec, nu_vec);

    nbt_vec.clear();
    int_vec.clear();
    ene_vec.clear();
    nu_vec.clear();
  }

  return nu_bar;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Real8 NuBarCalculator::calc_nu_p_bar(NuclearDataObject& nucl_data_obj, Real8 ene_val)
{
  Real8 nu_bar;
  
  if( nucl_data_obj.get_fis_data_obj().get_nu_p_bar_repr_flg() == 1 )
  {
    vector<Real> coef = nucl_data_obj.get_fis_data_obj().get_nu_p_bar_polynomial_coef();
    nu_bar = calc_polynomial_expansion(coef, ene_val);
    coef.clear();
  }
  else
  {
    vector<Integer> nbt_vec = nucl_data_obj.get_fis_data_obj().get_nu_p_bar_range_data();
    vector<Integer> int_vec = nucl_data_obj.get_fis_data_obj().get_nu_p_bar_int_data();
    vector<Real>    ene_vec = nucl_data_obj.get_fis_data_obj().get_nu_p_bar_ene_data();
    vector<Real>    nu_vec  = nucl_data_obj.get_fis_data_obj().get_nu_p_bar_data();
    
    ti_obj.interpolation_tab1(ene_val, nu_bar, nbt_vec, int_vec, ene_vec, nu_vec);
    
    nbt_vec.clear();
    int_vec.clear();
    ene_vec.clear();
    nu_vec.clear();
  }
  
  return nu_bar;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Real8 NuBarCalculator::calc_polynomial_expansion(vector<Real>& coef, Real8& ene_val)
{
  Real8 nu_bar  = 0.0;
  Real8 ene_tmp = 1.0;
  
  int   i_max = static_cast<int>(coef.size());
  for(int i=0; i<i_max; i++)
  {
    nu_bar  += static_cast<Real8>(coef[i])*ene_tmp;
    ene_tmp *= ene_val;
  }
  
  return nu_bar;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
