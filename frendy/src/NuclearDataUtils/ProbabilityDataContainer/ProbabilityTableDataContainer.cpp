#include "NuclearDataUtils/ProbabilityDataContainer/ProbabilityTableDataContainer.hpp"

using namespace frendy;

//constructor
ProbabilityTableDataContainer::ProbabilityTableDataContainer(void)
{
  clear();
}

//destructor
ProbabilityTableDataContainer::~ProbabilityTableDataContainer(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableDataContainer::clear()
{
  ene_grid = 0.0;
  nrest    = 0;

  temp.clear();
  sig_zero.clear();

  xs_unreso.clear();
  xs_back.clear();
  xs_tot_min.clear();
  xs_tot_max.clear();

  clr_obj.clear_vec_array2_real8(xs_tot_table);
  clr_obj.clear_vec_array2_real8(xs_inf_ave);
  clr_obj.clear_vec_array2_real8(xs_inf_var);
  clr_obj.clear_vec_array2_real8(prob_table_sample_no);
  clr_obj.clear_vec_array2_real8(prob_heat);

  clr_obj.clear_vec_array3_real8(prob_table);
  clr_obj.clear_vec_array3_real8(prob_table_mod);
  clr_obj.clear_vec_array3_real8(bondarenko_table);
  clr_obj.clear_vec_array3_real8(bondarenko_xs_direct);
  clr_obj.clear_vec_array3_real8(bondarenko_xs_prob);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Getter
Real8                           ProbabilityTableDataContainer::get_ene_grid()
{
  return ene_grid;
}

Integer                         ProbabilityTableDataContainer::get_nrest()
{
  return nrest;
}

vector<Real8>                   ProbabilityTableDataContainer::get_temp()
{
  return temp;
}

vector<Real8>                   ProbabilityTableDataContainer::get_sig_zero()
{
  return sig_zero;
}

vector<Real8>                   ProbabilityTableDataContainer::get_xs_unreso()
{
  return xs_unreso;
}

vector<Real8>                   ProbabilityTableDataContainer::get_xs_back()
{
  return xs_back;
}

vector<Real8>                   ProbabilityTableDataContainer::get_xs_tot_min()
{
  return xs_tot_min;
}

vector<Real8>                   ProbabilityTableDataContainer::get_xs_tot_max()
{
  return xs_tot_max;
}

vector<vector<Real8> >          ProbabilityTableDataContainer::get_xs_tot_table()
{
  return xs_tot_table;
}

vector<vector<Real8> >          ProbabilityTableDataContainer::get_xs_inf_ave()
{
  return xs_inf_ave;
}

vector<vector<Real8> >          ProbabilityTableDataContainer::get_xs_inf_var()
{
  return xs_inf_var;
}

vector<vector<Real8> > ProbabilityTableDataContainer::get_prob_table_sample_no()
{
  return prob_table_sample_no;
}

vector<vector<Real8> > ProbabilityTableDataContainer::get_prob_heat()
{
  return prob_heat;
}

vector<vector<vector<Real8> > > ProbabilityTableDataContainer::get_prob_table()
{
  return prob_table;
}

vector<vector<vector<Real8> > > ProbabilityTableDataContainer::get_prob_table_mod()
{
  //prob_table_mod is devided by bondarenko table (T=T0, SigZero=S0) when self shieldinf flg (LSSF) = 1.
  //(File 3 contains the entire dilute cross section for the unresolved resonance region)
  return prob_table_mod;
}

vector<vector<vector<Real8> > > ProbabilityTableDataContainer::get_bondarenko_table()
{
  return bondarenko_table;
}

vector<vector<vector<Real8> > > ProbabilityTableDataContainer::get_bondarenko_xs_direct()
{
  return bondarenko_xs_direct;
}

vector<vector<vector<Real8> > > ProbabilityTableDataContainer::get_bondarenko_xs_prob()
{
  return bondarenko_xs_prob;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void ProbabilityTableDataContainer::set_ene_grid( Real8 real_val )
{
  ene_grid = real_val;
}

void ProbabilityTableDataContainer::set_nrest( Integer int_val )
{
  nrest = int_val;
}

void ProbabilityTableDataContainer::set_temp( vector<Real8> real_vec )
{
  temp = real_vec;
  real_vec.clear();
}

void ProbabilityTableDataContainer::set_sig_zero( vector<Real8> real_vec )
{
  sig_zero = real_vec;
  real_vec.clear();
}

void ProbabilityTableDataContainer::set_xs_unreso( vector<Real8> real_vec )
{
  if( static_cast<int>(real_vec.size()) != xs_type_no )
  {
    string class_name = "ProbabilityTableDataContainer";
    string func_name  = "set_xs_unreso( vector<Real8> real_vec )";

    ostringstream oss01, oss02;
    oss01 << static_cast<int>(real_vec.size());
    oss02 << xs_type_no;

    string str01 = "The element number of xs_unreso is not identical to the xs type number.";
    string str02 = "  element number of xs_unreso : " + oss01.str();
    string str03 = "  xs type number              : " + oss02.str();
    vector<string> err_com;
    err_com.push_back(str01);
    err_com.push_back(str02);
    err_com.push_back(str03);
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  xs_unreso = real_vec;
  real_vec.clear();
}

void ProbabilityTableDataContainer::set_xs_back( vector<Real8> real_vec )
{
  if( static_cast<int>(real_vec.size()) != xs_type_no )
  {
    string class_name = "ProbabilityTableDataContainer";
    string func_name  = "set_xs_back( vector<Real8> real_vec )";

    ostringstream oss01, oss02;
    oss01 << static_cast<int>(real_vec.size());
    oss02 << xs_type_no;

    string str01 = "The element number of xs_unreso is not identical to the xs type number.";
    string str02 = "  element number of xs_unreso : " + oss01.str();
    string str03 = "  xs type number              : " + oss02.str();
    vector<string> err_com;
    err_com.push_back(str01);
    err_com.push_back(str02);
    err_com.push_back(str03);
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  xs_back = real_vec;
  real_vec.clear();
}

void ProbabilityTableDataContainer::set_xs_tot_min( vector<Real8> real_vec )
{
  xs_tot_min = real_vec;
  real_vec.clear();
}

void ProbabilityTableDataContainer::set_xs_tot_max( vector<Real8> real_vec )
{
  xs_tot_max = real_vec;
  real_vec.clear();
}

void ProbabilityTableDataContainer::set_xs_tot_table( vector<vector<Real8> > real_vec )
{
  xs_tot_table = real_vec;
  clr_obj.clear_vec_array2_real8(real_vec);
}

void ProbabilityTableDataContainer::set_xs_inf_ave( vector<vector<Real8> > real_vec )
{
  xs_inf_ave = real_vec;
  clr_obj.clear_vec_array2_real8(real_vec);
}

void ProbabilityTableDataContainer::set_xs_inf_var( vector<vector<Real8> > real_vec )
{
  xs_inf_var = real_vec;
  clr_obj.clear_vec_array2_real8(real_vec);
}

void ProbabilityTableDataContainer::set_prob_table_sample_no( vector<vector<Real8> > real_vec )
{
  prob_table_sample_no = real_vec;
  clr_obj.clear_vec_array2_real8(real_vec);
}

void ProbabilityTableDataContainer::set_prob_heat( vector<vector<Real8> > real_vec )
{
  prob_heat = real_vec;
  clr_obj.clear_vec_array2_real8(real_vec);
}

void ProbabilityTableDataContainer::set_prob_table( vector<vector<vector<Real8> > > real_vec )
{
  prob_table = real_vec;
  clr_obj.clear_vec_array3_real8(real_vec);
}

void ProbabilityTableDataContainer::set_prob_table_mod( vector<vector<vector<Real8> > > real_vec )
{
  //prob_table_mod is devided by bondarenko table (T=T0, SigZero=S0) when self shieldinf flg (LSSF) = 1.
  //(File 3 contains the entire dilute cross section for the unresolved resonance region)
  prob_table_mod = real_vec;
  clr_obj.clear_vec_array3_real8(real_vec);
}

void ProbabilityTableDataContainer::set_bondarenko_table( vector<vector<vector<Real8> > > real_vec )
{
  bondarenko_table = real_vec;
  clr_obj.clear_vec_array3_real8(real_vec);
}

void ProbabilityTableDataContainer::set_bondarenko_xs_direct( vector<vector<vector<Real8> > > real_vec )
{
  bondarenko_xs_direct = real_vec;
  clr_obj.clear_vec_array3_real8(real_vec);
}

void ProbabilityTableDataContainer::set_bondarenko_xs_prob( vector<vector<vector<Real8> > > real_vec )
{
  bondarenko_xs_prob = real_vec;
  clr_obj.clear_vec_array3_real8(real_vec);
}

