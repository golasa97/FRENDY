#include "ContinuousEnergyXSUtils/AceDataObject/AceDataObject.hpp"

using namespace frendy;

//constructor
AceDataObject::AceDataObject(void)
{
  clear();
}

//destructor
AceDataObject::~AceDataObject(void)
{
  clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void AceDataObject::clear()
{
  fast_ace_data_obj.clear();
  thermal_scat_ace_data_obj.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void AceDataObject::set_fast_ace_data_obj(FastAceDataObject data_obj)
{
  fast_ace_data_obj = data_obj;
}

void AceDataObject::set_thermal_scat_ace_data_obj(ThermalScatterAceDataObject data_obj)
{
  thermal_scat_ace_data_obj = data_obj;
}

void AceDataObject::set_dosimetry_ace_data_obj(DosimetryAceDataObject data_obj)
{
  dosimetry_ace_data_obj = data_obj;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Getter
FastAceDataObject           AceDataObject::get_fast_ace_data_obj()
{
  return fast_ace_data_obj;
}

ThermalScatterAceDataObject AceDataObject::get_thermal_scat_ace_data_obj()
{
  return thermal_scat_ace_data_obj;
}

DosimetryAceDataObject AceDataObject::get_dosimetry_ace_data_obj()
{
  return dosimetry_ace_data_obj;
}

