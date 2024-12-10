#include "ContinuousEnergyXSUtils/AceDataObject/DosimetryAceDataObject.hpp"

using namespace frendy;

//constructor
DosimetryAceDataObject::DosimetryAceDataObject(void)
{
  clear();
}

//destructor
DosimetryAceDataObject::~DosimetryAceDataObject(void)
{
  clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DosimetryAceDataObject::clear()
{
  clear_ace_data();
  clear_ace_pointer_data();

  mcnpx_mode_flg = 0;
  mat            = 0;
  temp           = 0.0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DosimetryAceDataObject::clear_ace_data()
{
  zi_vec.clear();
  awr_vec.clear();

  aw0   = 0.0;
  tz    = 0.0;
  clr_obj.clear_vec_array1_str(title_data);
  discriptive_data.clear();

  reaction_xs_reaction_type.clear();
  reaction_xs_pointer.clear();
  clr_obj.clear_vec_array2_int(reaction_xs_range_data);
  clr_obj.clear_vec_array2_int(reaction_xs_int_data);
  clr_obj.clear_vec_array2_real(reaction_xs_ene_data);
  clr_obj.clear_vec_array2_real(reaction_xs_data);

  clr_obj.clear_vec_array2_int(production_xs_state_no_product);
  clr_obj.clear_vec_array2_int(production_xs_pointer);
  clr_obj.clear_vec_array3_int(production_xs_range_data);
  clr_obj.clear_vec_array3_int(production_xs_int_data);
  clr_obj.clear_vec_array3_real(production_xs_ene_data);
  clr_obj.clear_vec_array3_real(production_xs_data);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DosimetryAceDataObject::clear_ace_pointer_data()
{
  len2 = 0;
  za   = 0;
  ntr  = 0;
  lone = 0;
  mtr  = 0;
  lsig = 0;
  sigd = 0;
  end  = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void DosimetryAceDataObject::set_mcnpx_mode_flg(Integer int_val)
{
  mcnpx_mode_flg = int_val;
}

void DosimetryAceDataObject::set_mat(Integer int_val)
{
  mat = int_val;
}

void DosimetryAceDataObject::set_temp(Real real_val)
{
  temp = real_val;
}


void DosimetryAceDataObject::set_zi_vec(vector<Integer> int_vec)
{
  zi_vec = int_vec;
}

void DosimetryAceDataObject::set_awr_vec(vector<Real> real_vec)
{
  awr_vec = real_vec;
}


void DosimetryAceDataObject::set_aw0(Real real_val)
{
  aw0 = real_val;
}

void DosimetryAceDataObject::set_tz(Real real_val)
{
  tz = real_val;
}

void DosimetryAceDataObject::set_title_data(vector<string> str_vec)
{
  title_data = str_vec;
  clr_obj.clear_vec_array1_str(str_vec);
}

void DosimetryAceDataObject::set_discriptive_data(string str_data)
{
  discriptive_data = str_data;
  str_data.clear();
}


void DosimetryAceDataObject::set_reaction_xs_reaction_type(vector<Integer> int_vec)
{
  reaction_xs_reaction_type = int_vec;
  int_vec.clear();
}

void DosimetryAceDataObject::set_reaction_xs_pointer(vector<Integer> int_vec)
{
  reaction_xs_pointer = int_vec;
  int_vec.clear();
}

void DosimetryAceDataObject::set_reaction_xs_range_data(vector<vector<Integer> > int_vec)
{
  reaction_xs_range_data = int_vec;
  clr_obj.clear_vec_array2_int(int_vec);
}

void DosimetryAceDataObject::set_reaction_xs_int_data(vector<vector<Integer> > int_vec)
{
  reaction_xs_int_data = int_vec;
  clr_obj.clear_vec_array2_int(int_vec);
}

void DosimetryAceDataObject::set_reaction_xs_ene_data(vector<vector<Real> > real_vec)
{
  reaction_xs_ene_data = real_vec;
  clr_obj.clear_vec_array2_real(real_vec);
}

void DosimetryAceDataObject::set_reaction_xs_data(vector<vector<Real> > real_vec)
{
  reaction_xs_data = real_vec;
  clr_obj.clear_vec_array2_real(real_vec);
}


void DosimetryAceDataObject::set_production_xs_pointer(vector<vector<Integer> > int_vec)
{
  production_xs_pointer = int_vec;
  clr_obj.clear_vec_array2_int(int_vec);
}

void DosimetryAceDataObject::set_production_xs_state_no_product(vector<vector<Integer> > int_vec)
{
  production_xs_state_no_product = int_vec;
  clr_obj.clear_vec_array2_int(int_vec);
}

void DosimetryAceDataObject::set_production_xs_range_data(vector<vector<vector<Integer> > > int_vec)
{
  production_xs_range_data = int_vec;
  clr_obj.clear_vec_array3_int(int_vec);
}

void DosimetryAceDataObject::set_production_xs_int_data(vector<vector<vector<Integer> > > int_vec)
{
  production_xs_int_data = int_vec;
  clr_obj.clear_vec_array3_int(int_vec);
}

void DosimetryAceDataObject::set_production_xs_ene_data(vector<vector<vector<Real> > > real_vec)
{
  production_xs_ene_data = real_vec;
  clr_obj.clear_vec_array3_real(real_vec);
}

void DosimetryAceDataObject::set_production_xs_data(vector<vector<vector<Real> > > real_vec)
{
  production_xs_data = real_vec;
  clr_obj.clear_vec_array3_real(real_vec);
}


//For pointer
void DosimetryAceDataObject::set_len2(int int_val)
{
  len2 = int_val;
}

void DosimetryAceDataObject::set_za(int int_val)
{
  za = int_val;
}

void DosimetryAceDataObject::set_ntr(int int_val)
{
  ntr = int_val;
}

void DosimetryAceDataObject::set_lone(int int_val)
{
  lone = int_val;
}

void DosimetryAceDataObject::set_mtr(int int_val)
{
  mtr = int_val;
}

void DosimetryAceDataObject::set_lsig(int int_val)
{
  lsig = int_val;
}

void DosimetryAceDataObject::set_sigd(int int_val)
{
  sigd = int_val;
}

void DosimetryAceDataObject::set_end(int int_val)
{
  end = int_val;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Getter
Integer         DosimetryAceDataObject::get_mcnpx_mode_flg()
{
  return mcnpx_mode_flg;
}

Integer         DosimetryAceDataObject::get_mat()
{
  return mat;
}

Real            DosimetryAceDataObject::get_temp()
{
  if( fabs(temp) < min_value && fabs(tz) > min_value )
  {
    temp = tz;
  }
  return temp;
}

Real            DosimetryAceDataObject::get_temp_ev()
{
  return get_temp() * 1.0E6;
}

Real            DosimetryAceDataObject::get_temp_kelvin()
{
  Real temp_ev = get_temp_ev();
  return temp_ev / boltzmann_const;
}


vector<Integer> DosimetryAceDataObject::get_zi_vec()
{
  return zi_vec;
}

vector<Real>    DosimetryAceDataObject::get_awr_vec()
{
  return awr_vec;
}


Real            DosimetryAceDataObject::get_aw0()
{
  return aw0;
}

Real            DosimetryAceDataObject::get_tz()
{
  return tz;
}

vector<string> DosimetryAceDataObject::get_title_data()
{
  return title_data;
}

string DosimetryAceDataObject::get_discriptive_data()
{
  return discriptive_data;
}


vector<Integer>          DosimetryAceDataObject::get_reaction_xs_reaction_type()
{
  return reaction_xs_reaction_type;
}

vector<Integer>          DosimetryAceDataObject::get_reaction_xs_pointer()
{
  return reaction_xs_pointer;
}

vector<vector<Integer> > DosimetryAceDataObject::get_reaction_xs_range_data()
{
  return reaction_xs_range_data;
}

vector<vector<Integer> > DosimetryAceDataObject::get_reaction_xs_int_data()
{
  return reaction_xs_int_data;
}

vector<vector<Real> >    DosimetryAceDataObject::get_reaction_xs_ene_data()
{
  return reaction_xs_ene_data;
}

vector<vector<Real> >    DosimetryAceDataObject::get_reaction_xs_data()
{
  return reaction_xs_data;
}


vector<vector<Integer> >          DosimetryAceDataObject::get_production_xs_state_no_product()
{
  return production_xs_state_no_product;
}

vector<vector<Integer> >          DosimetryAceDataObject::get_production_xs_pointer()
{
  return production_xs_pointer;
}

vector<vector<vector<Integer> > > DosimetryAceDataObject::get_production_xs_range_data()
{
  return production_xs_range_data;
}

vector<vector<vector<Integer> > > DosimetryAceDataObject::get_production_xs_int_data()
{
  return production_xs_int_data;
}

vector<vector<vector<Real> > >    DosimetryAceDataObject::get_production_xs_ene_data()
{
  return production_xs_ene_data;
}

vector<vector<vector<Real> > >    DosimetryAceDataObject::get_production_xs_data()
{
  return production_xs_data;
}


//For pointer
int DosimetryAceDataObject::get_len2()
{
  return len2;
}

int DosimetryAceDataObject::get_za()
{
  return za;
}

int DosimetryAceDataObject::get_ntr()
{
  return ntr;
}

int DosimetryAceDataObject::get_lone()
{
  return lone;
}

int DosimetryAceDataObject::get_mtr()
{
  return mtr;
}

int DosimetryAceDataObject::get_lsig()
{
  return lsig;
}

int DosimetryAceDataObject::get_sigd()
{
  return sigd;
}

int DosimetryAceDataObject::get_end()
{
  return end;
}

