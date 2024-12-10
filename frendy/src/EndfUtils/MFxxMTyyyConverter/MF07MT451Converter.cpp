#include "EndfUtils/MFxxMTyyyConverter/MF07MT451Converter.hpp"

using namespace frendy;

//constructor
MF07MT451Converter::MF07MT451Converter(void)
{
}

//destructor
MF07MT451Converter::~MF07MT451Converter(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//ThermalScatterDataContainer -> MF07MT451Parser
void MF07MT451Converter::convert_frendy_to_endf_format( ThermalScatterDataContainer& frendy_obj, MF07MT451Parser& endf_obj )
{
  //Get frendy data
  Integer         NA   = frendy_obj.get_element_no();
  Integer         NAS  = frendy_obj.get_principal_atom_no();
  vector<Real>    ZAI  = frendy_obj.get_mat_data_isotope();
  vector<Integer> LISI = frendy_obj.get_state_no_isotope();
  vector<Real>    AFI  = frendy_obj.get_abundance_isotope();
  vector<Real>    SFI  = frendy_obj.get_scat_xs_isotope();
  vector<Real>    AWRI = frendy_obj.get_mass_isotope();

  Integer         NI   = static_cast<Integer>(AWRI.size());

  Integer mat_no = 0;
  if( NA == 0 && NAS == 0 && NI == 0 )
  {
    mat_no = unassigned_mat_no;
  }

  //Set ENDF format data
  endf_obj.clear();
  endf_obj.set_mat_no(mat_no);
  endf_obj.set_NA(NA);
  endf_obj.set_NAS(NAS);
  endf_obj.set_NI(NI);
  endf_obj.set_ZAI(ZAI);
  endf_obj.set_LISI(LISI);
  endf_obj.set_AFI(AFI);
  endf_obj.set_SFI(SFI);
  endf_obj.set_AWRI(AWRI);

  //Clear declared data
  NA  = 0;
  NAS = 0;
  NI  = 0;
  ZAI.clear();
  LISI.clear();
  AFI.clear();
  SFI.clear();
  AWRI.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//MF07MT451Parser -> ThermalScatterDataContainer
void MF07MT451Converter::convert_endf_format_to_frendy( MF07MT451Parser& endf_obj, ThermalScatterDataContainer& frendy_obj )
{
  //Get frendy data
  Integer         element_no        = endf_obj.get_NA();
  Integer         principal_atom_no = endf_obj.get_NAS();
  vector<Real>    mat_data_isotope  = endf_obj.get_ZAI();
  vector<Integer> state_no_isotope  = endf_obj.get_LISI();
  vector<Real>    abundance_isotope = endf_obj.get_AFI();
  vector<Real>    scat_xs_isotope   = endf_obj.get_SFI();
  vector<Real>    mass_isotope      = endf_obj.get_AWRI();

  //Set ENDF format data
  //frendy_obj.clear();
  //text
  //mat_no
  //ZA
  //AWR
  frendy_obj.set_element_no(element_no);
  frendy_obj.set_principal_atom_no(principal_atom_no);
  frendy_obj.set_mat_data_isotope(mat_data_isotope);
  frendy_obj.set_state_no_isotope(state_no_isotope);
  frendy_obj.set_abundance_isotope(abundance_isotope);
  frendy_obj.set_scat_xs_isotope(scat_xs_isotope);
  frendy_obj.set_mass_isotope(mass_isotope);

  //Clear declared data
  element_no        = 0;
  principal_atom_no = 0;
  mat_data_isotope.clear();
  state_no_isotope.clear();
  abundance_isotope.clear();
  scat_xs_isotope.clear();
  mass_isotope.clear();
}

