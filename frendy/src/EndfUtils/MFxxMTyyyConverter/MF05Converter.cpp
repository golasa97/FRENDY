#include "EndfUtils/MFxxMTyyyConverter/MF05Converter.hpp"

using namespace frendy;

//constructor
MF05Converter::MF05Converter(void)
{
}

//destructor
MF05Converter::~MF05Converter(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//EnergyAngularDataContainer -> MF05Parser
void MF05Converter::convert_frendy_to_endf_format( EnergyAngularDataContainer& frendy_obj, MF05Parser& endf_obj )
{
  //Get frendy data
  Integer                           mt_no        = frendy_obj.get_reaction_type();
  vector<Integer>                   LF           = frendy_obj.get_ene_repr_flg();
  vector<Real>                      U            = frendy_obj.get_upper_ene_limit();
  vector<vector<Integer> >          INT_P        = frendy_obj.get_xs_part_int_data();
  vector<vector<Integer> >          NBT_P        = frendy_obj.get_xs_part_range_data();
  vector<vector<Real> >             E_INT_P      = frendy_obj.get_xs_part_ene_data();
  vector<vector<Real> >             P_TAB        = frendy_obj.get_xs_part_data();

  Integer mat_no = 0;
  if( static_cast<int>(LF.size())   == 0    && static_cast<int>(U.size())     == 0 &&
      static_cast<int>(INT_P.size()) == 0   && static_cast<int>(NBT_P.size()) == 0 &&
      static_cast<int>(E_INT_P.size()) == 0 && static_cast<int>(P_TAB.size()) == 0 )
  {
    mat_no = unassigned_mat_no;
    mt_no  = unassigned_mt_no;
  }

  vector<vector<Real> >             E_LF01;
  vector<vector<Integer> >          INT_E_LF01;
  vector<vector<Integer> >          NBT_E_LF01;
  vector<vector<vector<Integer> > > INT_G_LF01;
  vector<vector<vector<Integer> > > NBT_G_LF01;
  vector<vector<vector<Real> > >    E_INT_G_LF01;
  vector<vector<vector<Real> > >    G_TAB_LF01;
  vector<vector<Integer> >          INT_S_LF05;
  vector<vector<Integer> >          NBT_S_LF05;
  vector<vector<Real> >             E_INT_S_LF05;
  vector<vector<Real> >             S_TAB_LF05;
  vector<vector<Integer> >          INT_G_LF05;
  vector<vector<Integer> >          NBT_G_LF05;
  vector<vector<Real> >             E_INT_G_LF05;
  vector<vector<Real> >             G_TAB_LF05;
  vector<Real>                      EFL_LF12;
  vector<Real>                      EFH_LF12;

  Integer NK    = static_cast<Integer>(LF.size());
  int     i_max = static_cast<int>(NK);
  E_LF01.resize(i_max);
  INT_E_LF01.resize(i_max);
  NBT_E_LF01.resize(i_max);
  INT_G_LF01.resize(i_max);
  NBT_G_LF01.resize(i_max);
  E_INT_G_LF01.resize(i_max);
  G_TAB_LF01.resize(i_max);
  INT_S_LF05.resize(i_max);
  NBT_S_LF05.resize(i_max);
  E_INT_S_LF05.resize(i_max);
  S_TAB_LF05.resize(i_max);
  INT_G_LF05.resize(i_max);
  NBT_G_LF05.resize(i_max);
  E_INT_G_LF05.resize(i_max);
  G_TAB_LF05.resize(i_max);
  EFL_LF12.resize(i_max);
  EFH_LF12.resize(i_max);
  
  vector<Integer> NE_LF01;
  NE_LF01.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    NE_LF01[i]  = 0;
    EFL_LF12[i] = 0.0;
    EFH_LF12[i] = 0.0;
    if( LF[i] == 1 )
    {
      E_LF01[i]       = frendy_obj.get_incident_ene()[i];
      INT_E_LF01[i]   = frendy_obj.get_ene_int_data()[i];
      NBT_E_LF01[i]   = frendy_obj.get_ene_range_data()[i];
      INT_G_LF01[i]   = frendy_obj.get_ene_part_int_data()[i];
      NBT_G_LF01[i]   = frendy_obj.get_ene_part_range_data()[i];
      E_INT_G_LF01[i] = frendy_obj.get_ene_part_ene_data()[i];
      G_TAB_LF01[i]   = frendy_obj.get_ene_part_data()[i];
      NE_LF01[i]      = static_cast<Integer>(E_LF01[i].size());
    }
    else if( LF[i] == 5 || LF[i] == 7 || LF[i] == 9 )
    {
      INT_S_LF05[i]   = frendy_obj.get_temp_eff_int_data()[i];
      NBT_S_LF05[i]   = frendy_obj.get_temp_eff_range_data()[i];
      E_INT_S_LF05[i] = frendy_obj.get_temp_eff_ene_data()[i];
      S_TAB_LF05[i]   = frendy_obj.get_temp_eff_data()[i];
      
      if( LF[i] == 5 )
      {
        INT_G_LF05[i]   = frendy_obj.get_ene_part_int_data()[i][0];
        NBT_G_LF05[i]   = frendy_obj.get_ene_part_range_data()[i][0];
        E_INT_G_LF05[i] = frendy_obj.get_ene_part_ene_data()[i][0];
        G_TAB_LF05[i]   = frendy_obj.get_ene_part_data()[i][0];
      }
    }
    else if( LF[i] == 11 )
    {
      INT_S_LF05[i]   = frendy_obj.get_watt_a_int_data()[i];
      NBT_S_LF05[i]   = frendy_obj.get_watt_a_range_data()[i];
      E_INT_S_LF05[i] = frendy_obj.get_watt_a_ene_data()[i];
      S_TAB_LF05[i]   = frendy_obj.get_watt_a_data()[i];
      INT_G_LF05[i]   = frendy_obj.get_watt_b_int_data()[i];
      NBT_G_LF05[i]   = frendy_obj.get_watt_b_range_data()[i];
      E_INT_G_LF05[i] = frendy_obj.get_watt_b_ene_data()[i];
      G_TAB_LF05[i]   = frendy_obj.get_watt_b_data()[i];
    }
    else if( LF[i] == 12 )
    {
      EFL_LF12[i]     = frendy_obj.get_lower_ene_limit_fis_n()[i];
      EFH_LF12[i]     = frendy_obj.get_upper_ene_limit_fis_n()[i];
      INT_S_LF05[i]   = frendy_obj.get_temp_max_int_data()[i];
      NBT_S_LF05[i]   = frendy_obj.get_temp_max_range_data()[i];
      E_INT_S_LF05[i] = frendy_obj.get_temp_max_ene_data()[i];
      S_TAB_LF05[i]   = frendy_obj.get_temp_max_data()[i];
    }
  }

  //Set ENDF format data
  endf_obj.clear();
  endf_obj.set_mat_no(mat_no);
  endf_obj.set_mt_no(mt_no);
  endf_obj.set_NK(NK);
  endf_obj.set_U(U);
  endf_obj.set_LF(LF);
  endf_obj.set_NBT_P(NBT_P);
  endf_obj.set_INT_P(INT_P);
  endf_obj.set_E_INT_P(E_INT_P);
  endf_obj.set_P_TAB(P_TAB);
  endf_obj.set_NE_LF01(NE_LF01);
  endf_obj.set_NBT_E_LF01(NBT_E_LF01);
  endf_obj.set_INT_E_LF01(INT_E_LF01);
  endf_obj.set_E_LF01(E_LF01);
  endf_obj.set_NBT_G_LF01(NBT_G_LF01);
  endf_obj.set_INT_G_LF01(INT_G_LF01);
  endf_obj.set_E_INT_G_LF01(E_INT_G_LF01);
  endf_obj.set_G_TAB_LF01(G_TAB_LF01);
  endf_obj.set_NBT_S_LF05(NBT_S_LF05);
  endf_obj.set_INT_S_LF05(INT_S_LF05);
  endf_obj.set_E_INT_S_LF05(E_INT_S_LF05);
  endf_obj.set_S_TAB_LF05(S_TAB_LF05);
  endf_obj.set_NBT_G_LF05(NBT_G_LF05);
  endf_obj.set_INT_G_LF05(INT_G_LF05);
  endf_obj.set_E_INT_G_LF05(E_INT_G_LF05);
  endf_obj.set_G_TAB_LF05(G_TAB_LF05);
  endf_obj.set_EFL_LF12(EFL_LF12);
  endf_obj.set_EFH_LF12(EFH_LF12);

  //Clear declared data
  mt_no        = 0;
  U.clear();
  LF.clear();
  clr_obj.clear_vec_array2_int(INT_P);
  clr_obj.clear_vec_array2_int(NBT_P);
  clr_obj.clear_vec_array2_real(E_INT_P);
  clr_obj.clear_vec_array2_real(P_TAB);
  clr_obj.clear_vec_array2_real(E_LF01);
  clr_obj.clear_vec_array2_int(INT_E_LF01);
  clr_obj.clear_vec_array2_int(NBT_E_LF01);
  clr_obj.clear_vec_array3_int(INT_G_LF01);
  clr_obj.clear_vec_array3_int(NBT_G_LF01);
  clr_obj.clear_vec_array3_real(E_INT_G_LF01);
  clr_obj.clear_vec_array3_real(G_TAB_LF01);
  clr_obj.clear_vec_array2_int(INT_S_LF05);
  clr_obj.clear_vec_array2_int(NBT_S_LF05);
  clr_obj.clear_vec_array2_real(E_INT_S_LF05);
  clr_obj.clear_vec_array2_real(S_TAB_LF05);
  clr_obj.clear_vec_array2_int(INT_G_LF05);
  clr_obj.clear_vec_array2_int(NBT_G_LF05);
  clr_obj.clear_vec_array2_real(E_INT_G_LF05);
  clr_obj.clear_vec_array2_real(G_TAB_LF05);
  EFL_LF12.clear();
  EFH_LF12.clear();
  
  NK = 0;
  NE_LF01.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//MF05Parser -> EnergyAngularDataContainer
void MF05Converter::convert_endf_format_to_frendy( MF05Parser& endf_obj, EnergyAngularDataContainer& frendy_obj )
{
  //Get frendy data
  Integer                           reaction_type         = endf_obj.get_mt_no();
  vector<Real>                      upper_ene_limit       = endf_obj.get_U();
  vector<Integer>                   ene_repr_flg          = endf_obj.get_LF();
  vector<vector<Integer> >          xs_part_int_data      = endf_obj.get_INT_P();
  vector<vector<Integer> >          xs_part_range_data    = endf_obj.get_NBT_P();
  vector<vector<Real> >             xs_part_ene_data      = endf_obj.get_E_INT_P();
  vector<vector<Real> >             xs_part_data          = endf_obj.get_P_TAB();
  
  if( static_cast<int>(upper_ene_limit.size())  == 0 && static_cast<int>(ene_repr_flg.size())       == 0 &&
      static_cast<int>(xs_part_int_data.size()) == 0 && static_cast<int>(xs_part_range_data.size()) == 0 &&
      static_cast<int>(xs_part_ene_data.size()) == 0 && static_cast<int>(xs_part_data.size())       == 0 )
  {
    reaction_type = unassigned_mt_no;
  }

  vector<vector<Integer> >          temp_eff_int_data;
  vector<vector<Integer> >          temp_eff_range_data;
  vector<vector<Real> >             temp_eff_ene_data;
  vector<vector<Real> >             temp_eff_data;
  vector<vector<Real> >             incident_ene;
  vector<vector<Integer> >          ene_int_data;
  vector<vector<Integer> >          ene_range_data;
  vector<vector<vector<Integer> > > ene_part_int_data;
  vector<vector<vector<Integer> > > ene_part_range_data;
  vector<vector<vector<Real> > >    ene_part_ene_data;
  vector<vector<vector<Real> > >    ene_part_data;
  vector<vector<Integer> >          watt_a_int_data;
  vector<vector<Integer> >          watt_a_range_data;
  vector<vector<Real> >             watt_a_ene_data;
  vector<vector<Real> >             watt_a_data;
  vector<vector<Integer> >          watt_b_int_data;
  vector<vector<Integer> >          watt_b_range_data;
  vector<vector<Real> >             watt_b_ene_data;
  vector<vector<Real> >             watt_b_data;
  vector<Real>                      lower_ene_limit_fis_n;
  vector<Real>                      upper_ene_limit_fis_n;
  vector<vector<Integer> >          temp_max_int_data;
  vector<vector<Integer> >          temp_max_range_data;
  vector<vector<Real> >             temp_max_ene_data;
  vector<vector<Real> >             temp_max_data;

  int i_max = static_cast<int>(ene_repr_flg.size());
  temp_eff_int_data.resize(i_max);
  temp_eff_range_data.resize(i_max);
  temp_eff_ene_data.resize(i_max);
  temp_eff_data.resize(i_max);
  xs_part_int_data.resize(i_max);
  xs_part_range_data.resize(i_max);
  xs_part_ene_data.resize(i_max);
  xs_part_data.resize(i_max);
  incident_ene.resize(i_max);
  ene_int_data.resize(i_max);
  ene_range_data.resize(i_max);
  ene_part_int_data.resize(i_max);
  ene_part_range_data.resize(i_max);
  ene_part_ene_data.resize(i_max);
  ene_part_data.resize(i_max);
  watt_a_int_data.resize(i_max);
  watt_a_range_data.resize(i_max);
  watt_a_ene_data.resize(i_max);
  watt_a_data.resize(i_max);
  watt_b_int_data.resize(i_max);
  watt_b_range_data.resize(i_max);
  watt_b_ene_data.resize(i_max);
  watt_b_data.resize(i_max);
  lower_ene_limit_fis_n.resize(i_max);
  upper_ene_limit_fis_n.resize(i_max);
  temp_max_int_data.resize(i_max);
  temp_max_range_data.resize(i_max);
  temp_max_ene_data.resize(i_max);
  temp_max_data.resize(i_max);

  for(int i=0; i<i_max; i++)
  {
    if( ene_repr_flg[i] == 1 )
    {
      incident_ene[i]          = endf_obj.get_E_LF01()[i];
      ene_int_data[i]          = endf_obj.get_INT_E_LF01()[i];
      ene_range_data[i]        = endf_obj.get_NBT_E_LF01()[i];
      ene_part_int_data[i]     = endf_obj.get_INT_G_LF01()[i];
      ene_part_range_data[i]   = endf_obj.get_NBT_G_LF01()[i];
      ene_part_ene_data[i]     = endf_obj.get_E_INT_G_LF01()[i];
      ene_part_data[i]         = endf_obj.get_G_TAB_LF01()[i];
    }
    else if( ene_repr_flg[i] == 5 || ene_repr_flg[i] == 7 || ene_repr_flg[i] == 9 )
    {
      temp_eff_int_data[i]     = endf_obj.get_INT_S_LF05()[i];
      temp_eff_range_data[i]   = endf_obj.get_NBT_S_LF05()[i];
      temp_eff_ene_data[i]     = endf_obj.get_E_INT_S_LF05()[i];
      temp_eff_data[i]         = endf_obj.get_S_TAB_LF05()[i];
      
      if( ene_repr_flg[i] == 5 )
      {
        ene_part_int_data[i].resize(1);
        ene_part_range_data[i].resize(1);
        ene_part_ene_data[i].resize(1);
        ene_part_data[i].resize(1);
        ene_part_int_data[i][0]   = endf_obj.get_INT_G_LF05()[i];
        ene_part_range_data[i][0] = endf_obj.get_NBT_G_LF05()[i];
        ene_part_ene_data[i][0]   = endf_obj.get_E_INT_G_LF05()[i];
        ene_part_data[i][0]       = endf_obj.get_G_TAB_LF05()[i];
      }
    }
    else if( ene_repr_flg[i] == 11 )
    {
      watt_a_int_data[i]       = endf_obj.get_INT_S_LF05()[i];
      watt_a_range_data[i]     = endf_obj.get_NBT_S_LF05()[i];
      watt_a_ene_data[i]       = endf_obj.get_E_INT_S_LF05()[i];
      watt_a_data[i]           = endf_obj.get_S_TAB_LF05()[i];
      watt_b_int_data[i]       = endf_obj.get_INT_G_LF05()[i];
      watt_b_range_data[i]     = endf_obj.get_NBT_G_LF05()[i];
      watt_b_ene_data[i]       = endf_obj.get_E_INT_G_LF05()[i];
      watt_b_data[i]           = endf_obj.get_G_TAB_LF05()[i];
    }
    else if( ene_repr_flg[i] == 12 )
    {
      lower_ene_limit_fis_n[i] = endf_obj.get_EFL_LF12()[i];
      upper_ene_limit_fis_n[i] = endf_obj.get_EFH_LF12()[i];
      temp_max_int_data[i]     = endf_obj.get_INT_S_LF05()[i];
      temp_max_range_data[i]   = endf_obj.get_NBT_S_LF05()[i];
      temp_max_ene_data[i]     = endf_obj.get_E_INT_S_LF05()[i];
      temp_max_data[i]         = endf_obj.get_S_TAB_LF05()[i];
    }
  }

  //Set ENDF format data
  //frendy_obj.clear();
  //text
  //mat_no
  frendy_obj.set_reaction_type(reaction_type);
  //ZA
  //AWR
  frendy_obj.set_upper_ene_limit(upper_ene_limit);
  frendy_obj.set_ene_repr_flg(ene_repr_flg);
  frendy_obj.set_xs_part_range_data(xs_part_range_data);
  frendy_obj.set_xs_part_int_data(xs_part_int_data);
  frendy_obj.set_xs_part_ene_data(xs_part_ene_data);
  frendy_obj.set_xs_part_data(xs_part_data);
  frendy_obj.set_ene_range_data(ene_range_data);
  frendy_obj.set_ene_int_data(ene_int_data);
  frendy_obj.set_incident_ene(incident_ene);
  frendy_obj.set_ene_part_range_data(ene_part_range_data);
  frendy_obj.set_ene_part_int_data(ene_part_int_data);
  frendy_obj.set_ene_part_ene_data(ene_part_ene_data);
  frendy_obj.set_ene_part_data(ene_part_data);
  frendy_obj.set_temp_eff_range_data(temp_eff_range_data);
  frendy_obj.set_temp_eff_int_data(temp_eff_int_data);
  frendy_obj.set_temp_eff_ene_data(temp_eff_ene_data);
  frendy_obj.set_temp_eff_data(temp_eff_data);
  frendy_obj.set_watt_a_range_data(watt_a_range_data);
  frendy_obj.set_watt_a_int_data(watt_a_int_data);
  frendy_obj.set_watt_a_ene_data(watt_a_ene_data);
  frendy_obj.set_watt_a_data(watt_a_data);
  frendy_obj.set_watt_b_range_data(watt_b_range_data);
  frendy_obj.set_watt_b_int_data(watt_b_int_data);
  frendy_obj.set_watt_b_ene_data(watt_b_ene_data);
  frendy_obj.set_watt_b_data(watt_b_data);
  frendy_obj.set_lower_ene_limit_fis_n(lower_ene_limit_fis_n);
  frendy_obj.set_upper_ene_limit_fis_n(upper_ene_limit_fis_n);
  frendy_obj.set_temp_max_int_data(temp_max_int_data);
  frendy_obj.set_temp_max_range_data(temp_max_range_data);
  frendy_obj.set_temp_max_ene_data(temp_max_ene_data);
  frendy_obj.set_temp_max_data(temp_max_data);

  //Clear declared data
  reaction_type         = 0;
  upper_ene_limit.clear();
  clr_obj.clear_vec_array2_int(temp_eff_int_data);
  clr_obj.clear_vec_array2_int(temp_eff_range_data);
  clr_obj.clear_vec_array2_real(temp_eff_ene_data);
  clr_obj.clear_vec_array2_real(temp_eff_data);
  ene_repr_flg.clear();
  clr_obj.clear_vec_array2_int(xs_part_int_data);
  clr_obj.clear_vec_array2_int(xs_part_range_data);
  clr_obj.clear_vec_array2_real(xs_part_ene_data);
  clr_obj.clear_vec_array2_real(xs_part_data);
  clr_obj.clear_vec_array2_real(incident_ene);
  clr_obj.clear_vec_array2_int(ene_int_data);
  clr_obj.clear_vec_array2_int(ene_range_data);
  clr_obj.clear_vec_array3_int(ene_part_int_data);
  clr_obj.clear_vec_array3_int(ene_part_range_data);
  clr_obj.clear_vec_array3_real(ene_part_ene_data);
  clr_obj.clear_vec_array3_real(ene_part_data);
  clr_obj.clear_vec_array2_int(watt_a_int_data);
  clr_obj.clear_vec_array2_int(watt_a_range_data);
  clr_obj.clear_vec_array2_real(watt_a_ene_data);
  clr_obj.clear_vec_array2_real(watt_a_data);
  clr_obj.clear_vec_array2_int(watt_b_int_data);
  clr_obj.clear_vec_array2_int(watt_b_range_data);
  clr_obj.clear_vec_array2_real(watt_b_ene_data);
  clr_obj.clear_vec_array2_real(watt_b_data);
  lower_ene_limit_fis_n.clear();
  upper_ene_limit_fis_n.clear();
  clr_obj.clear_vec_array2_int(temp_max_int_data);
  clr_obj.clear_vec_array2_int(temp_max_range_data);
  clr_obj.clear_vec_array2_real(temp_max_ene_data);
  clr_obj.clear_vec_array2_real(temp_max_data);
}

