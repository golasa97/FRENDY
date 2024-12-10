#include "ContinuousEnergyXSUtils/AceDataObject/ThermalScatterAceDataObject.hpp"

using namespace frendy;

//Initialize static const value
const Real8 ThermalScatterAceDataObject::min_second_ene_dif_abs = 1.0E-15;

//constructor
ThermalScatterAceDataObject::ThermalScatterAceDataObject(void)
{
  clear();
}

//destructor
ThermalScatterAceDataObject::~ThermalScatterAceDataObject(void)
{
  clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterAceDataObject::clear()
{
  clear_ace_data();
  clear_ace_pointer_data();

  mcnpx_mode_flg = 0;
  mat            = 0;
  temp           = 0.0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterAceDataObject::clear_ace_data()
{
  mod_za.clear();
  zi_vec.clear();
  awr_vec.clear();

  aw0   = 0.0;
  tz    = 0.0;
  clr_obj.clear_vec_array1_str(title_data);
  discriptive_data.clear();

  coh_elastic_ene_data.clear();
  coh_elastic_e_xs_data.clear();
  incoh_elastic_ene_data.clear();
  incoh_elastic_xs_data.clear();
  clr_obj.clear_vec_array2_real(incoh_elastic_scat_angle);

  inelastic_ene_data.clear();
  inelastic_xs_data.clear();
  clr_obj.clear_vec_array2_real(inelastic_second_ene);
  clr_obj.clear_vec_array2_real(inelastic_scat_xs_int);
  clr_obj.clear_vec_array2_real(inelastic_weight);
  clr_obj.clear_vec_array3_real(inelastic_scat_xs_weight);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterAceDataObject::clear_ace_pointer_data()
{
  len2  = 0;
  idpni = 0;
  nil   = 0;
  nieb  = 0;
  idpnc = 0;
  ncl   = 0;
  ifeng = 0;
  ncli  = 0;
  itie  = 0;
  itix  = 0;
  itxe  = 0;
  itce  = 0;
  itcx  = 0;
  itca  = 0;
  itcei = 0;
  itcxi = 0;
  itcai = 0;
  nie   = 0;
  nee   = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void ThermalScatterAceDataObject::set_mcnpx_mode_flg(Integer int_val)
{
  mcnpx_mode_flg = int_val;
}

void ThermalScatterAceDataObject::set_mat(Integer int_val)
{
  mat = int_val;
}

void ThermalScatterAceDataObject::set_temp(Real real_val)
{
  temp = real_val;
}


void ThermalScatterAceDataObject::set_mod_za(vector<Integer> int_vec)
{
  mod_za = int_vec;
}


void ThermalScatterAceDataObject::set_zi_vec(vector<Integer> int_vec)
{
  zi_vec = int_vec;
}

void ThermalScatterAceDataObject::set_awr_vec(vector<Real> real_vec)
{
  awr_vec = real_vec;
}


void ThermalScatterAceDataObject::set_aw0(Real real_val)
{
  aw0 = real_val;
}

void ThermalScatterAceDataObject::set_tz(Real real_val)
{
  tz = real_val;
}

void ThermalScatterAceDataObject::set_title_data(vector<string> str_vec)
{
  title_data = str_vec;
  clr_obj.clear_vec_array1_str(str_vec);
}

void ThermalScatterAceDataObject::set_discriptive_data(string str_data)
{
  discriptive_data = str_data;
  str_data.clear();
}

//For elastic
void ThermalScatterAceDataObject::set_coh_elastic_ene_data(vector<Real> real_vec)
{
  coh_elastic_ene_data = real_vec;
  real_vec.clear();
}

void ThermalScatterAceDataObject::set_coh_elastic_e_xs_data(vector<Real> real_vec)
{
  coh_elastic_e_xs_data = real_vec;
  real_vec.clear();
}

void ThermalScatterAceDataObject::set_incoh_elastic_ene_data(vector<Real> real_vec)
{
  incoh_elastic_ene_data = real_vec;
  real_vec.clear();
}

void ThermalScatterAceDataObject::set_incoh_elastic_xs_data(vector<Real> real_vec)
{
  incoh_elastic_xs_data = real_vec;
  real_vec.clear();
}

void ThermalScatterAceDataObject::set_incoh_elastic_scat_angle(vector<vector<Real> > real_vec)
{
  incoh_elastic_scat_angle = real_vec;
  clr_obj.clear_vec_array2_real(real_vec);
}

//For inelastic
void ThermalScatterAceDataObject::set_inelastic_ene_data(vector<Real> real_vec)
{
  inelastic_ene_data = real_vec;
  real_vec.clear();
}

void ThermalScatterAceDataObject::set_inelastic_xs_data(vector<Real> real_vec)
{
  inelastic_xs_data = real_vec;
  real_vec.clear();
}

void ThermalScatterAceDataObject::set_inelastic_second_ene(vector<vector<Real> > real_vec)
{
  inelastic_second_ene = real_vec;
  clr_obj.clear_vec_array2_real(real_vec);
}

void ThermalScatterAceDataObject::set_inelastic_scat_xs_int(vector<vector<Real> > real_vec)
{
  inelastic_scat_xs_int = real_vec;
  clr_obj.clear_vec_array2_real(real_vec);
}

void ThermalScatterAceDataObject::set_inelastic_weight(vector<vector<Real> > real_vec)
{
  inelastic_weight = real_vec;
  clr_obj.clear_vec_array2_real(real_vec);
}

void ThermalScatterAceDataObject::set_inelastic_scat_xs_weight(vector<vector<vector<Real> > > real_vec)
{
  inelastic_scat_xs_weight = real_vec;
  clr_obj.clear_vec_array3_real(real_vec);
}

//For pointer
void ThermalScatterAceDataObject::set_len2(int int_val)
{
  len2 = int_val;
}

void ThermalScatterAceDataObject::set_idpni(int int_val)
{
  idpni = int_val;
}

void ThermalScatterAceDataObject::set_nil(int int_val)
{
  nil = int_val;
}

void ThermalScatterAceDataObject::set_nieb(int int_val)
{
  nieb = int_val;
}

void ThermalScatterAceDataObject::set_idpnc(int int_val)
{
  idpnc = int_val;
}

void ThermalScatterAceDataObject::set_ncl(int int_val)
{
  ncl = int_val;
}

void ThermalScatterAceDataObject::set_ifeng(int int_val)
{
  ifeng = int_val;
}

void ThermalScatterAceDataObject::set_ncli(int int_val)
{
  ncli = int_val;
}

void ThermalScatterAceDataObject::set_itie(int int_val)
{
  itie = int_val;
}

void ThermalScatterAceDataObject::set_itix(int int_val)
{
  itix = int_val;
}

void ThermalScatterAceDataObject::set_itxe(int int_val)
{
  itxe = int_val;
}

void ThermalScatterAceDataObject::set_itce(int int_val)
{
  itce = int_val;
}

void ThermalScatterAceDataObject::set_itcx(int int_val)
{
  itcx = int_val;
}

void ThermalScatterAceDataObject::set_itca(int int_val)
{
  itca = int_val;
}

void ThermalScatterAceDataObject::set_itcei(int int_val)
{
  itcei = int_val;
}

void ThermalScatterAceDataObject::set_itcxi(int int_val)
{
  itcxi = int_val;
}

void ThermalScatterAceDataObject::set_itcai(int int_val)
{
  itcai = int_val;
}

void ThermalScatterAceDataObject::set_nie(int int_val)
{
  nie = int_val;
}

void ThermalScatterAceDataObject::set_nee(int int_val)
{
  nee = int_val;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Getter
Integer         ThermalScatterAceDataObject::get_mcnpx_mode_flg()
{
  return mcnpx_mode_flg;
}

Integer         ThermalScatterAceDataObject::get_mat()
{
  return mat;
}

Real            ThermalScatterAceDataObject::get_temp()
{
  if( fabs(temp) < min_value && fabs(tz) > min_value )
  {
    temp = tz;
  }
  return temp;
}

Real            ThermalScatterAceDataObject::get_temp_ev()
{
  return get_temp() * 1.0E6;
}

Real            ThermalScatterAceDataObject::get_temp_kelvin()
{
  Real temp_ev = get_temp_ev();
  return temp_ev / boltzmann_const;
}


vector<Integer> ThermalScatterAceDataObject::get_mod_za()
{
  return mod_za;
}


vector<Integer> ThermalScatterAceDataObject::get_zi_vec()
{
  return zi_vec;
}

vector<Real>    ThermalScatterAceDataObject::get_awr_vec()
{
  return awr_vec;
}


Real            ThermalScatterAceDataObject::get_aw0()
{
  return aw0;
}

Real            ThermalScatterAceDataObject::get_tz()
{
  return tz;
}

vector<string> ThermalScatterAceDataObject::get_title_data()
{
  return title_data;
}

string ThermalScatterAceDataObject::get_discriptive_data()
{
  return discriptive_data;
}

//For elastic
vector<Real>          ThermalScatterAceDataObject::get_coh_elastic_ene_data()
{
  return coh_elastic_ene_data;
}

vector<Real>          ThermalScatterAceDataObject::get_coh_elastic_e_xs_data()
{
  return coh_elastic_e_xs_data;
}

vector<Real>          ThermalScatterAceDataObject::get_incoh_elastic_ene_data()
{
  return incoh_elastic_ene_data;
}

vector<Real>          ThermalScatterAceDataObject::get_incoh_elastic_xs_data()
{
  return incoh_elastic_xs_data;
}

vector<vector<Real> > ThermalScatterAceDataObject::get_incoh_elastic_scat_angle()
{
  return incoh_elastic_scat_angle;
}

//For inelastic
vector<Real>                   ThermalScatterAceDataObject::get_inelastic_ene_data()
{
  return inelastic_ene_data;
}

vector<Real>                   ThermalScatterAceDataObject::get_inelastic_xs_data()
{
  return inelastic_xs_data;
}

vector<vector<Real> >          ThermalScatterAceDataObject::get_inelastic_second_ene()
{
  return inelastic_second_ene;
}

vector<vector<Real> >          ThermalScatterAceDataObject::get_inelastic_scat_xs_int()
{
  return inelastic_scat_xs_int;
}

vector<vector<Real> >          ThermalScatterAceDataObject::get_inelastic_weight()
{
  return inelastic_weight;
}

vector<vector<vector<Real> > > ThermalScatterAceDataObject::get_inelastic_scat_xs_weight()
{
  return inelastic_scat_xs_weight;
}

//For pointer
int ThermalScatterAceDataObject::get_len2()
{
  return len2;
}

int ThermalScatterAceDataObject::get_idpni()
{
  return idpni;
}

int ThermalScatterAceDataObject::get_nil()
{
  return nil;
}

int ThermalScatterAceDataObject::get_nieb()
{
  return nieb;
}

int ThermalScatterAceDataObject::get_idpnc()
{
  return idpnc;
}

int ThermalScatterAceDataObject::get_ncl()
{
  return ncl;
}

int ThermalScatterAceDataObject::get_ifeng()
{
  return ifeng;
}

int ThermalScatterAceDataObject::get_ncli()
{
  return ncli;
}

int ThermalScatterAceDataObject::get_itie()
{
  return itie;
}

int ThermalScatterAceDataObject::get_itix()
{
  return itix;
}

int ThermalScatterAceDataObject::get_itxe()
{
  return itxe;
}

int ThermalScatterAceDataObject::get_itce()
{
  return itce;
}

int ThermalScatterAceDataObject::get_itcx()
{
  return itcx;
}

int ThermalScatterAceDataObject::get_itca()
{
  return itca;
}

int ThermalScatterAceDataObject::get_itcei()
{
  return itcei;
}

int ThermalScatterAceDataObject::get_itcxi()
{
  return itcxi;
}

int ThermalScatterAceDataObject::get_itcai()
{
  return itcai;
}

int ThermalScatterAceDataObject::get_nie()
{
  return nie;
}

int ThermalScatterAceDataObject::get_nee()
{
  return nee;
}

