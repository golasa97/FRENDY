#include "NuclearDataUtils/OtherUtils/ProbDataConverter.hpp"

using namespace frendy;

//constructor
ProbDataConverter::ProbDataConverter(void)
{
  clear();
}

//destructor
ProbDataConverter::~ProbDataConverter(void)
{
  clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbDataConverter::clear()
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbDataConverter::conv_prob_data_container_to_unreso_xs_data
                          ( int temp_no,
                            ProbabilityDataContainer&            prob_data_obj,
                            UnresolvedCrossSectionDataContainer& unreso_xs_data_obj )
{
  int i_max = prob_data_obj.get_prob_table_ene_no();
  if( i_max == 0 )
  {
    unreso_xs_data_obj.clear();
    return;
  }

  Integer data_no = static_cast<Integer>(i_max);
  vector<Real8>                   ene_grid;
  vector<vector<vector<Real8> > > bondarenko_table;
  ene_grid.resize(i_max);
  bondarenko_table.resize(i_max);

  Real8                  temp = 0.0;
  vector<Real8>          sig_zero;
  vector<vector<Real8> > b_table_ori;
  sig_zero.clear();
  for(int i=0; i<i_max; i++)
  {
    ProbabilityTableDataContainer prob_table_data_obj = prob_data_obj.get_prob_table_data_obj(i);
    if( i == 0 )
    {
      temp     = prob_table_data_obj.get_temp()[temp_no];
      sig_zero = prob_table_data_obj.get_sig_zero();
    }

    ene_grid[i] = prob_table_data_obj.get_ene_grid();

    b_table_ori = prob_table_data_obj.get_bondarenko_table()[temp_no];
    int k_max = static_cast<int>(b_table_ori.size());
    if( k_max > 0 )
    {
      int j_max = static_cast<int>(b_table_ori[0].size());
      bondarenko_table[i].resize(j_max);
      for(int j=0; j<j_max; j++)
      {
        bondarenko_table[i][j].resize(k_max);
        for(int k=0; k<k_max; k++)
        {
          bondarenko_table[i][j][k] = b_table_ori[k][j];
        }
      }
    }
    prob_table_data_obj.clear();
    clr_obj.clear_vec_array2_real8(b_table_ori);
  }

  Integer unreso_int_data    = prob_data_obj.get_unreso_int_data();
  Integer self_shielding_flg = prob_data_obj.get_self_shielding_flg();
  Integer opt_a_val          = 5;
  Integer opt_b_val          = static_cast<Integer>(sig_zero.size());

  unreso_xs_data_obj.clear();
  unreso_xs_data_obj.set_self_shielding_flg( self_shielding_flg );
  unreso_xs_data_obj.set_unreso_opt_int( unreso_int_data );
  unreso_xs_data_obj.set_temp( temp );
  unreso_xs_data_obj.set_unreso_opt_a( opt_a_val );
  unreso_xs_data_obj.set_unreso_opt_b( opt_b_val );
  unreso_xs_data_obj.set_unreso_data_no( data_no );
  unreso_xs_data_obj.set_bondarenko_table( bondarenko_table );
  unreso_xs_data_obj.set_sig_zero( sig_zero );
  unreso_xs_data_obj.set_unreso_ene( ene_grid );

  sig_zero.clear();
  ene_grid.clear();
  clr_obj.clear_vec_array3_real8(bondarenko_table);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbDataConverter::conv_prob_data_container_to_unreso_prob_data
                          ( int temp_no,
                            ProbabilityDataContainer&           prob_data_obj,
                            UnresolvedProbabilityDataContainer& unreso_prob_data_obj )
{
  int i_max = prob_data_obj.get_prob_table_ene_no();
  if( i_max == 0 )
  {
    unreso_prob_data_obj.clear();
    return;
  }

  Integer data_no = static_cast<Integer>(i_max);
  vector<Real8>                   ene_grid;
  vector<vector<Real8> >          prob_table_sample_no, prob_heat;
  vector<vector<vector<Real8> > > prob_table_mod;
  ene_grid.resize(i_max);
  prob_table_sample_no.resize(i_max);
  prob_heat.resize(i_max);
  prob_table_mod.resize(i_max);

  Real8                  temp   = 0.0;
  Integer                bin_no = 0;
  vector<vector<Real8> > p_table_mod;
  for(int i=0; i<i_max; i++)
  {
    ProbabilityTableDataContainer prob_table_data_obj = prob_data_obj.get_prob_table_data_obj(i);
    if( i == 0 )
    {
      temp = prob_table_data_obj.get_temp()[temp_no];
    }

    ene_grid[i]             = prob_table_data_obj.get_ene_grid();
    prob_table_sample_no[i] = prob_table_data_obj.get_prob_table_sample_no()[temp_no];
    prob_heat[i]            = prob_table_data_obj.get_prob_heat()[temp_no];
    p_table_mod             = prob_table_data_obj.get_prob_table_mod()[temp_no];

    int k_max = static_cast<int>(p_table_mod.size());
    bin_no    = static_cast<Integer>(k_max);
    if( static_cast<int>(prob_heat[i].size()) != k_max )
    {
      prob_heat[i].resize(k_max);
      for(int k=0; k<k_max; k++)
      {
        prob_heat[i][k] = 0.0;
      }
    }

    if( k_max > 0 )
    {
      int j_max = static_cast<int>(p_table_mod[0].size());
      prob_table_mod[i].resize(j_max);
      for(int j=0; j<j_max; j++)
      {
        prob_table_mod[i][j].resize(k_max);
        for(int k=0; k<k_max; k++)
        {
          prob_table_mod[i][j][k] = p_table_mod[k][j];
        }
      }
    }
    prob_table_data_obj.clear();
    clr_obj.clear_vec_array2_real8(p_table_mod);
  }

  Integer unreso_int_data    = prob_data_obj.get_unreso_int_data();
  Integer self_shielding_flg = prob_data_obj.get_self_shielding_flg();
  Integer comp_flg_inela     = prob_data_obj.get_comp_flg_inela();
  Integer comp_flg_abs       = prob_data_obj.get_comp_flg_abs();
  Integer comp_flg           = prob_data_obj.get_comp_flg();

  unreso_prob_data_obj.clear();
  unreso_prob_data_obj.set_prob_int( unreso_int_data );
  unreso_prob_data_obj.set_prob_bin_no( bin_no );
  unreso_prob_data_obj.set_self_shielding_flg( self_shielding_flg );
  unreso_prob_data_obj.set_comp_flg_inela( comp_flg_inela );
  unreso_prob_data_obj.set_comp_flg_abs( comp_flg_abs );
  unreso_prob_data_obj.set_comp_flg( comp_flg );
  unreso_prob_data_obj.set_prob_ene_no( data_no );
  unreso_prob_data_obj.set_temp( temp );
  unreso_prob_data_obj.set_prob_ene( ene_grid );
  unreso_prob_data_obj.set_prob_heat( prob_heat );
  unreso_prob_data_obj.set_prob_table_sample_no( prob_table_sample_no );
  unreso_prob_data_obj.set_prob_table( prob_table_mod );

  ene_grid.clear();
  clr_obj.clear_vec_array2_real8(prob_heat);
  clr_obj.clear_vec_array2_real8(prob_table_sample_no);
  clr_obj.clear_vec_array3_real8(prob_table_mod);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

