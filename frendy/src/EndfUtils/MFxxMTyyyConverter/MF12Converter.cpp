#include "EndfUtils/MFxxMTyyyConverter/MF12Converter.hpp"

using namespace frendy;

//constructor
MF12Converter::MF12Converter(void)
{
}

//destructor
MF12Converter::~MF12Converter(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//PhotonDataContainer -> MF12Parser
void MF12Converter::convert_frendy_to_endf_format( PhotonDataContainer& frendy_obj, MF12Parser& endf_obj )
{
  //Get frendy data
  Integer                  mt_no          = frendy_obj.get_reaction_type();
  vector<Real>             ES_LO01        = frendy_obj.get_multiplicity_ene_level();
  vector<Integer>          INT_Y_LO01     = frendy_obj.get_multiplicity_tot_int_data();
  vector<Integer>          NBT_Y_LO01     = frendy_obj.get_multiplicity_tot_range_data();
  vector<Real>             E_INT_Y_LO01   = frendy_obj.get_multiplicity_tot_ene_data();
  vector<Real>             Y_TAB_LO01     = frendy_obj.get_multiplicity_tot_data();
  vector<vector<Integer> > INT_Y_K_LO01   = frendy_obj.get_multiplicity_int_data();
  vector<vector<Integer> > NBT_Y_K_LO01   = frendy_obj.get_multiplicity_range_data();
  vector<vector<Real> >    E_INT_Y_K_LO01 = frendy_obj.get_multiplicity_ene_data();
  vector<vector<Real> >    Y_K_TAB_LO01   = frendy_obj.get_multiplicity_data();
  vector<Integer>          LP_LO01        = frendy_obj.get_multiplicity_binding_ene_flg();
  vector<Integer>          LF_LO01        = frendy_obj.get_multiplicity_distr_law_no();
  Integer                  NK             = frendy_obj.get_level_no_max();
  Integer                  LP_LO02        = frendy_obj.get_trans_photon_ene_flg();
  Real                     ES_LO02        = frendy_obj.get_ene_level_max();

  Integer mat_no = 0;
  if( fabs(ES_LO02) < min_value && NK == 0 && LP_LO02 == 0 &&
      static_cast<int>(ES_LO01.size())      == 0 && static_cast<int>(INT_Y_LO01.size())     == 0 &&
      static_cast<int>(NBT_Y_LO01.size())   == 0 && static_cast<int>(E_INT_Y_LO01.size())   == 0 &&
      static_cast<int>(Y_TAB_LO01.size())   == 0 && static_cast<int>(INT_Y_K_LO01.size())   == 0 &&
      static_cast<int>(NBT_Y_K_LO01.size()) == 0 && static_cast<int>(E_INT_Y_K_LO01.size()) == 0 &&
      static_cast<int>(Y_K_TAB_LO01.size()) == 0 && static_cast<int>(LP_LO01.size())        == 0 &&
      static_cast<int>(LF_LO01.size())      == 0 )
  {
    mat_no = unassigned_mat_no;
    mt_no  = unassigned_mt_no;
  }
  
  vector<Real>             B_LO02_ES      = frendy_obj.get_trans_ene_level();
  vector<Real>             B_LO02_TP      = frendy_obj.get_direct_trans_probability();
  vector<Real>             B_LO02_GP      = frendy_obj.get_photon_trans_probability();
  
  Integer      LO = 0;
  Integer      LG = 0;
  vector<Real> EG_LO01;
  if( static_cast<Integer>(LP_LO01.size()) > 0 )
  {
    LO = 1;
    NK = static_cast<Integer>(LP_LO01.size());
    EG_LO01 = frendy_obj.get_multiplicity_binding_ene();
  }
  else if( static_cast<Integer>(B_LO02_ES.size()) > 0 )
  {
    LO = 2;
    
    LG = 1;
    if( static_cast<Integer>(B_LO02_GP.size()) > 0 )
    {
      LG = 2;
    }
  }
  
  Integer NT_LO02 = static_cast<Integer>(B_LO02_ES.size());
  vector<Real> B_LO02;
  if( LO == 2 )
  {
    int i_max = static_cast<int>(NT_LO02);
    if( LG == 1 )
    {
      B_LO02.resize(i_max*2);
      for(int i=0; i<i_max; i++)
      {
        B_LO02[2*i]   = B_LO02_ES[i];
        B_LO02[2*i+1] = B_LO02_TP[i];
      }
    }
    else
    {
      B_LO02.resize(i_max*3);
      for(int i=0; i<i_max; i++)
      {
        B_LO02[3*i]   = B_LO02_ES[i];
        B_LO02[3*i+1] = B_LO02_TP[i];
        B_LO02[3*i+2] = B_LO02_GP[i];
      }
    }
  }


  //Set ENDF format data
  endf_obj.clear();
  endf_obj.set_mat_no(mat_no);
  endf_obj.set_mt_no(mt_no);
  endf_obj.set_LO(LO);
  endf_obj.set_LG(LG);
  endf_obj.set_NK(NK);
  endf_obj.set_NBT_Y_LO01(NBT_Y_LO01);
  endf_obj.set_INT_Y_LO01(INT_Y_LO01);
  endf_obj.set_E_INT_Y_LO01(E_INT_Y_LO01);
  endf_obj.set_Y_TAB_LO01(Y_TAB_LO01);
  endf_obj.set_EG_LO01(EG_LO01);
  endf_obj.set_ES_LO01(ES_LO01);
  endf_obj.set_LP_LO01(LP_LO01);
  endf_obj.set_LF_LO01(LF_LO01);
  endf_obj.set_NBT_Y_K_LO01(NBT_Y_K_LO01);
  endf_obj.set_INT_Y_K_LO01(INT_Y_K_LO01);
  endf_obj.set_E_INT_Y_K_LO01(E_INT_Y_K_LO01);
  endf_obj.set_Y_K_TAB_LO01(Y_K_TAB_LO01);
  endf_obj.set_ES_LO02(ES_LO02);
  endf_obj.set_LP_LO02(LP_LO02);
  endf_obj.set_NT_LO02(NT_LO02);
  endf_obj.set_B_LO02(B_LO02);

  //Clear declared data
  mt_no          = 0;
  ES_LO01.clear();
  EG_LO01.clear();
  INT_Y_LO01.clear();
  NBT_Y_LO01.clear();
  E_INT_Y_LO01.clear();
  Y_TAB_LO01.clear();
  clr_obj.clear_vec_array2_int(INT_Y_K_LO01);
  clr_obj.clear_vec_array2_int(NBT_Y_K_LO01);
  clr_obj.clear_vec_array2_real(E_INT_Y_K_LO01);
  clr_obj.clear_vec_array2_real(Y_K_TAB_LO01);
  LP_LO01.clear();
  LF_LO01.clear();
  NK             = 0;
  LP_LO02        = 0;
  ES_LO02        = 0.0;
  B_LO02.clear();
  B_LO02_ES.clear();
  B_LO02_TP.clear();
  B_LO02_GP.clear();
  
  LO = 0;
  LG = 0;
  NT_LO02 = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//MF12Parser -> PhotonDataContainer
void MF12Converter::convert_endf_format_to_frendy( MF12Parser& endf_obj, PhotonDataContainer& frendy_obj )
{
  //Get frendy data
  Integer                  reaction_type                = endf_obj.get_mt_no();
  vector<Integer>          multiplicity_tot_int_data    = endf_obj.get_INT_Y_LO01();
  vector<Integer>          multiplicity_tot_range_data  = endf_obj.get_NBT_Y_LO01();
  vector<Real>             multiplicity_tot_ene_data    = endf_obj.get_E_INT_Y_LO01();
  vector<Real>             multiplicity_tot_data        = endf_obj.get_Y_TAB_LO01();
  vector<vector<Integer> > multiplicity_int_data        = endf_obj.get_INT_Y_K_LO01();
  vector<vector<Integer> > multiplicity_range_data      = endf_obj.get_NBT_Y_K_LO01();
  vector<vector<Real> >    multiplicity_ene_data        = endf_obj.get_E_INT_Y_K_LO01();
  vector<vector<Real> >    multiplicity_data            = endf_obj.get_Y_K_TAB_LO01();
  vector<Integer>          multiplicity_binding_ene_flg = endf_obj.get_LP_LO01();
  vector<Integer>          multiplicity_distr_law_no    = endf_obj.get_LF_LO01();
  Integer                  level_no_max                 = endf_obj.get_NS();
  Integer                  trans_photon_ene_flg         = endf_obj.get_LP_LO02();
  Real                     ene_level_max                = endf_obj.get_ES_LO02();

  if( fabs(ene_level_max) < min_value && level_no_max == 0 && trans_photon_ene_flg == 0 &&
      static_cast<int>(multiplicity_tot_int_data.size())    == 0 &&
      static_cast<int>(multiplicity_tot_range_data.size())  == 0 &&
      static_cast<int>(multiplicity_tot_ene_data.size())    == 0 &&
      static_cast<int>(multiplicity_tot_data.size())        == 0 &&
      static_cast<int>(multiplicity_int_data.size())        == 0 &&
      static_cast<int>(multiplicity_range_data.size())      == 0 &&
      static_cast<int>(multiplicity_ene_data.size())        == 0 &&
      static_cast<int>(multiplicity_data.size())            == 0 &&
      static_cast<int>(multiplicity_binding_ene_flg.size()) == 0 &&
      static_cast<int>(multiplicity_distr_law_no.size())    == 0 )
  {
    reaction_type = unassigned_mt_no;
  }
  
  vector<Real>             multiplicity_ene_level, trans_ene_level;
  vector<Real>             direct_trans_probability;
  vector<Real>             photon_trans_probability;
  
  Integer      LO = endf_obj.get_LO();
  Integer      LG = endf_obj.get_LG();
  vector<Real> multiplicity_photon_ene;
  vector<Real> multiplicity_binding_ene;
  if( LO == 1 )
  {
    level_no_max = 0;
    multiplicity_ene_level   = endf_obj.get_ES_LO01();
    multiplicity_binding_ene = endf_obj.get_EG_LO01();
  }
  else if( LO == 2 )
  {
    int i_max = static_cast<int>(endf_obj.get_NT_LO02());
    trans_ene_level.resize(i_max);
    direct_trans_probability.resize(i_max);
    if( LG == 1 )
    {
      for(int i=0; i<i_max; i++)
      {
        trans_ene_level[i]          = endf_obj.get_B_LO02()[2*i];
        direct_trans_probability[i] = endf_obj.get_B_LO02()[2*i+1];
      }
    }
    else
    {
      photon_trans_probability.resize(i_max);
      for(int i=0; i<i_max; i++)
      {
        trans_ene_level[i]          = endf_obj.get_B_LO02()[3*i];
        direct_trans_probability[i] = endf_obj.get_B_LO02()[3*i+1];
        photon_trans_probability[i] = endf_obj.get_B_LO02()[3*i+2];
      }
    }
  }

  //Set ENDF format data
  //frendy_obj.clear();
  //text
  //mat_no
  frendy_obj.set_reaction_type(reaction_type);
  //ZA
  //AWR
  frendy_obj.set_level_no_max(level_no_max);
  frendy_obj.set_multiplicity_tot_range_data(multiplicity_tot_range_data);
  frendy_obj.set_multiplicity_tot_int_data(multiplicity_tot_int_data);
  frendy_obj.set_multiplicity_tot_ene_data(multiplicity_tot_ene_data);
  frendy_obj.set_multiplicity_tot_data(multiplicity_tot_data);
  frendy_obj.set_multiplicity_ene_level(multiplicity_ene_level);
  frendy_obj.set_multiplicity_binding_ene(multiplicity_binding_ene);
  frendy_obj.set_multiplicity_binding_ene_flg(multiplicity_binding_ene_flg);
  frendy_obj.set_multiplicity_distr_law_no(multiplicity_distr_law_no);
  frendy_obj.set_multiplicity_range_data(multiplicity_range_data);
  frendy_obj.set_multiplicity_int_data(multiplicity_int_data);
  frendy_obj.set_multiplicity_ene_data(multiplicity_ene_data);
  frendy_obj.set_multiplicity_data(multiplicity_data);
  frendy_obj.set_ene_level_max(ene_level_max);
  frendy_obj.set_trans_photon_ene_flg(trans_photon_ene_flg);
  frendy_obj.set_trans_ene_level(trans_ene_level);
  frendy_obj.set_direct_trans_probability(direct_trans_probability);
  frendy_obj.set_photon_trans_probability(photon_trans_probability);

  //Clear declared data
  reaction_type               = 0;
  multiplicity_ene_level.clear();
  multiplicity_photon_ene.clear();
  multiplicity_binding_ene.clear();
  multiplicity_tot_int_data.clear();
  multiplicity_tot_range_data.clear();
  multiplicity_tot_ene_data.clear();
  multiplicity_tot_data.clear();
  clr_obj.clear_vec_array2_int(multiplicity_int_data);
  clr_obj.clear_vec_array2_int(multiplicity_range_data);
  clr_obj.clear_vec_array2_real(multiplicity_ene_data);
  clr_obj.clear_vec_array2_real(multiplicity_data);
  multiplicity_binding_ene_flg.clear();
  multiplicity_distr_law_no.clear();
  level_no_max                = 0;
  trans_photon_ene_flg        = 0;
  ene_level_max               = 0.0;
  trans_ene_level.clear();
  direct_trans_probability.clear();
  photon_trans_probability.clear();
  
  LO = 0;
  LG = 0;
}

