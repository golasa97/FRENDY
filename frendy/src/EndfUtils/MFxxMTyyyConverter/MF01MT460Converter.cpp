#include "EndfUtils/MFxxMTyyyConverter/MF01MT460Converter.hpp"

using namespace frendy;

//constructor
MF01MT460Converter::MF01MT460Converter(void)
{
}

//destructor
MF01MT460Converter::~MF01MT460Converter(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//FissionDataContainer -> MF01MT460Parser
void MF01MT460Converter::convert_frendy_to_endf_format( FissionDataContainer& frendy_obj, MF01MT460Parser& endf_obj )
{
  //Get frendy data
  Integer                  LO        = frendy_obj.get_photon_d_repr_flg();
  vector<Real>             E         = frendy_obj.get_photon_d_ene();
  vector<vector<Integer> > INT_MAP   = frendy_obj.get_photon_d_int_data();
  vector<vector<Integer> > NBT_MAP   = frendy_obj.get_photon_d_range_data();
  vector<vector<Real> >    T_INT_MAP = frendy_obj.get_photon_d_time_data();
  vector<vector<Real> >    T_MAP     = frendy_obj.get_photon_d_data();
  vector<Real>             RAMDA     = frendy_obj.get_photon_d_precursor_decay_const();

  Integer NG  = static_cast<Integer>(E.size());
  Integer NR  = 0;
  Integer NP  = 0;
  if( NG > 0 )
  {
    NR = static_cast<Integer>(NBT_MAP[NG-1].size());
    NP = static_cast<Integer>(T_INT_MAP[NG-1].size());
  }
  Integer NNF = static_cast<Integer>(RAMDA.size());

  Integer mat_no = 0;
  if( LO == 0 && NG == 0 && NR == 0 && NP == 0 && NNF == 0 )
  {
    mat_no = unassigned_mat_no;
  }

  //Set ENDF format data
  endf_obj.clear();
  endf_obj.set_mat_no(mat_no);
  endf_obj.set_LO(LO);
  endf_obj.set_NG(NG);
  endf_obj.set_NR(NR);
  endf_obj.set_NP(NP);
  endf_obj.set_NNF(NNF);
  endf_obj.set_E(E);
  endf_obj.set_RAMDA(RAMDA);
  endf_obj.set_NBT_MAP(NBT_MAP);
  endf_obj.set_INT_MAP(INT_MAP);
  endf_obj.set_T_INT_MAP(T_INT_MAP);
  endf_obj.set_T_MAP(T_MAP);

  //Clear declared data
  LO        = 0;
  E.clear();
  clr_obj.clear_vec_array2_int(INT_MAP);
  clr_obj.clear_vec_array2_int(NBT_MAP);
  clr_obj.clear_vec_array2_real(T_INT_MAP);
  clr_obj.clear_vec_array2_real(T_MAP);
  RAMDA.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//MF01MT460Parser -> FissionDataContainer
void MF01MT460Converter::convert_endf_format_to_frendy( MF01MT460Parser& endf_obj, FissionDataContainer& frendy_obj )
{
  //Get frendy data
  Integer                  photon_d_repr_flg              = endf_obj.get_LO();
  vector<Real>             photon_d_ene                   = endf_obj.get_E();
  vector<vector<Integer> > photon_d_int_data              = endf_obj.get_INT_MAP();
  vector<vector<Integer> > photon_d_range_data            = endf_obj.get_NBT_MAP();
  vector<vector<Real> >    photon_d_time_data             = endf_obj.get_T_INT_MAP();
  vector<vector<Real> >    photon_d_data                  = endf_obj.get_T_MAP();
  vector<Real>             photon_d_precursor_decay_const = endf_obj.get_RAMDA();

  //Set ENDF format data
  //frendy_obj.clear();
  //text
  //mat_no
  //ZA
  //AWR
  frendy_obj.set_photon_d_repr_flg(photon_d_repr_flg);
  frendy_obj.set_photon_d_ene(photon_d_ene);
  frendy_obj.set_photon_d_precursor_decay_const(photon_d_precursor_decay_const);
  frendy_obj.set_photon_d_range_data(photon_d_range_data);
  frendy_obj.set_photon_d_int_data(photon_d_int_data);
  frendy_obj.set_photon_d_time_data(photon_d_time_data);
  frendy_obj.set_photon_d_data(photon_d_data);

  //Clear declared data
  photon_d_repr_flg              = 0;
  photon_d_ene.clear();
  clr_obj.clear_vec_array2_int(photon_d_int_data);
  clr_obj.clear_vec_array2_int(photon_d_range_data);
  clr_obj.clear_vec_array2_real(photon_d_time_data);
  clr_obj.clear_vec_array2_real(photon_d_data);
  photon_d_precursor_decay_const.clear();
}

