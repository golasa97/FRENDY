#include "EndfUtils/MFxxMTyyyConverter/MF01MT455Converter.hpp"

using namespace frendy;

//constructor
MF01MT455Converter::MF01MT455Converter(void)
{
}

//destructor
MF01MT455Converter::~MF01MT455Converter(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//FissionDataContainer -> MF01MT455Parser
void MF01MT455Converter::convert_frendy_to_endf_format( FissionDataContainer& frendy_obj, MF01MT455Parser& endf_obj )
{
  //Get frendy data
  Integer      LNU = frendy_obj.get_nu_d_bar_repr_flg();
  vector<Real> NU;
  if( LNU == 1 )
  {
    NU = frendy_obj.get_nu_d_bar_polynomial_coef();
  }
  else
  {
    NU = frendy_obj.get_nu_d_bar_data();
  }
  vector<Integer>       INT_NU    = frendy_obj.get_nu_d_bar_int_data();
  vector<Integer>       NBT_NU    = frendy_obj.get_nu_d_bar_range_data();
  vector<Real>          E_INT_NU  = frendy_obj.get_nu_d_bar_ene_data();
  vector<Real>          E         = frendy_obj.get_nu_d_ene_data();
  vector<Integer>       INT_E     = frendy_obj.get_nu_d_decay_int_data();
  vector<Integer>       NBT_E     = frendy_obj.get_nu_d_decay_range_data();
  vector<vector<Real> > RAMDA_MAP = frendy_obj.get_nu_d_decay_constant();
  vector<vector<Real> > ALPHA_MAP = frendy_obj.get_nu_d_delayed_group_abundance();

  Integer NC    = static_cast<Integer>(NU.size());
  Integer NR_E  = static_cast<Integer>(NBT_E.size());
  Integer NE_E  = static_cast<Integer>(RAMDA_MAP.size());
  Integer NNF   = 0;
  if( NE_E > 0 )
  {
    NNF = static_cast<Integer>(RAMDA_MAP[NE_E-1].size());
  }
  Integer NR_NU = static_cast<Integer>(INT_NU.size());
  Integer NP_NU = static_cast<Integer>(E_INT_NU.size());
  
  Integer      LDG = 1;
  vector<Real> RAMDA;
  if( static_cast<int>(RAMDA_MAP.size()) == 1 && static_cast<int>(ALPHA_MAP.size()) == 0 )
  {
    LDG = 0;
    RAMDA = RAMDA_MAP[0];
  }

  Integer mat_no = 0;
  if( LNU == 0 && NC == 0 && NR_E == 0 && NR_NU == 0 && NP_NU == 0 )
  {
    mat_no = unassigned_mat_no;
  }

  //Set ENDF format data
  endf_obj.clear();
  endf_obj.set_mat_no(mat_no);
  endf_obj.set_LDG(LDG);
  endf_obj.set_LNU(LNU);
  endf_obj.set_NC(NC);
  endf_obj.set_NNF(NNF);
  endf_obj.set_NR_E(NR_E);
  endf_obj.set_NE_E(NE_E);
  endf_obj.set_NP_NU(NP_NU);
  endf_obj.set_NR_NU(NR_NU);
  endf_obj.set_RAMDA(RAMDA);
  endf_obj.set_E(E);
  endf_obj.set_NBT_E(NBT_E);
  endf_obj.set_INT_E(INT_E);
  endf_obj.set_NBT_NU(NBT_NU);
  endf_obj.set_INT_NU(INT_NU);
  endf_obj.set_E_INT_NU(E_INT_NU);
  endf_obj.set_NU(NU);
  endf_obj.set_ALPHA_MAP(ALPHA_MAP);
  endf_obj.set_RAMDA_MAP(RAMDA_MAP);

  //Clear declared data
  LNU       = 0;
  NU.clear();
  INT_NU.clear();
  NBT_NU.clear();
  E_INT_NU.clear();
  NU.clear();
  E.clear();
  INT_E.clear();
  NBT_E.clear();
  clr_obj.clear_vec_array2_real(RAMDA_MAP);
  clr_obj.clear_vec_array2_real(ALPHA_MAP);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//MF01MT455Parser -> FissionDataContainer
void MF01MT455Converter::convert_endf_format_to_frendy( MF01MT455Parser& endf_obj, FissionDataContainer& frendy_obj )
{
  //Get frendy data
  Integer               nu_d_bar_repr_flg            = endf_obj.get_LNU();
  vector<Real>          nu_d_bar_polynomial_coef     = endf_obj.get_NU();
  vector<Integer>       nu_d_bar_int_data            = endf_obj.get_INT_NU();
  vector<Integer>       nu_d_bar_range_data          = endf_obj.get_NBT_NU();
  vector<Real>          nu_d_bar_ene_data            = endf_obj.get_E_INT_NU();
  vector<Real>          nu_d_bar_data                = endf_obj.get_NU();
  vector<Real>          nu_d_ene_data                = endf_obj.get_E();
  vector<Integer>       nu_d_decay_int_data          = endf_obj.get_INT_E();
  vector<Integer>       nu_d_decay_range_data        = endf_obj.get_NBT_E();
  vector<vector<Real> > nu_d_decay_constant          = endf_obj.get_RAMDA_MAP();
  vector<vector<Real> > nu_d_delayed_group_abundance = endf_obj.get_ALPHA_MAP();

  Integer LDG = endf_obj.get_LDG();
  if( LDG == 0 && static_cast<int>(endf_obj.get_RAMDA().size()) > 0 )
  {
    clr_obj.clear_vec_array2_real(nu_d_decay_constant);
    nu_d_decay_constant.resize(1);
    nu_d_decay_constant[0] = endf_obj.get_RAMDA();
  }

  if( nu_d_bar_repr_flg == 1 )
  {
    nu_d_bar_data.clear();
  }
  else
  {
    nu_d_bar_polynomial_coef.clear();
  }

  //Set ENDF format data
  //frendy_obj.clear();
  //text
  //mat_no
  //ZA
  //AWR
  frendy_obj.set_nu_d_bar_repr_flg(nu_d_bar_repr_flg);
  frendy_obj.set_nu_d_bar_data(nu_d_bar_data);
  frendy_obj.set_nu_d_ene_data(nu_d_ene_data);
  frendy_obj.set_nu_d_decay_range_data(nu_d_decay_range_data);
  frendy_obj.set_nu_d_decay_int_data(nu_d_decay_int_data);
  frendy_obj.set_nu_d_bar_range_data(nu_d_bar_range_data);
  frendy_obj.set_nu_d_bar_int_data(nu_d_bar_int_data);
  frendy_obj.set_nu_d_bar_ene_data(nu_d_bar_ene_data);
  frendy_obj.set_nu_d_bar_polynomial_coef(nu_d_bar_polynomial_coef);
  frendy_obj.set_nu_d_delayed_group_abundance(nu_d_delayed_group_abundance);
  frendy_obj.set_nu_d_decay_constant(nu_d_decay_constant);

  //Clear declared data
  nu_d_bar_repr_flg            = 0;
  nu_d_bar_polynomial_coef.clear();
  nu_d_bar_int_data.clear();
  nu_d_bar_range_data.clear();
  nu_d_bar_ene_data.clear();
  nu_d_bar_data.clear();
  nu_d_ene_data.clear();
  nu_d_decay_int_data.clear();
  nu_d_decay_range_data.clear();
  clr_obj.clear_vec_array2_real(nu_d_decay_constant);
  clr_obj.clear_vec_array2_real(nu_d_delayed_group_abundance);
}

