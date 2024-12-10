#include "FrendyUtils/ThermalScatterMatList.hpp"

using namespace frendy;

//constructor
ThermalScatterMatData::ThermalScatterMatData(void)
{
  clear();
}

//destructor
ThermalScatterMatData::~ThermalScatterMatData(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterMatData::clear()
{
  mat_name.clear();
  atom_name_principal.clear();
  atom_name_non_principal.clear();

  mat_no                 = 0;
  mat_no_principal       = 0;
  mat_no_non_principal   = 0;
  mat_data_principal     = 0;
  mat_data_non_principal = 0;
  atom_no_principal      = 0;
  atom_no_mix            = 0;

  mt_no                  = 249;
  tsl_name               = "other";
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//Setter

void ThermalScatterMatData::set_mat_name(string str_data)
{
  transform(str_data.begin(), str_data.end(), str_data.begin(), ::tolower);

  mat_name = str_data;
}

void ThermalScatterMatData::set_atom_name_principal(string str_data)
{
  transform(str_data.begin(), str_data.end(), str_data.begin(), ::tolower);

  atom_name_principal = str_data;
}

void ThermalScatterMatData::set_atom_name_non_principal(string str_data)
{
  transform(str_data.begin(), str_data.end(), str_data.begin(), ::tolower);

  atom_name_non_principal = str_data;
}


void ThermalScatterMatData::set_mat_no(int int_data)
{
  mat_no = int_data;
}

void ThermalScatterMatData::set_mat_no_principal(int int_data)
{
  mat_no_principal = int_data;
}

void ThermalScatterMatData::set_mat_no_non_principal(int int_data)
{
  mat_no_non_principal = int_data;
}

void ThermalScatterMatData::set_mat_data_principal(int int_data)
{
  mat_data_principal = int_data;
}

void ThermalScatterMatData::set_mat_data_non_principal(int int_data)
{
  mat_data_non_principal = int_data;
}

void ThermalScatterMatData::set_atom_no_principal(int int_data)
{
  atom_no_principal = int_data;
}

void ThermalScatterMatData::set_atom_no_mix(int int_data)
{
  atom_no_mix = int_data;
}

void ThermalScatterMatData::set_mt_no(int int_data)
{
  mt_no = int_data;
}

void ThermalScatterMatData::set_tsl_name(string str_data)
{
  transform(str_data.begin(), str_data.end(), str_data.begin(), ::tolower);

  tsl_name = str_data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//Getter

string ThermalScatterMatData::get_mat_name()
{
  return mat_name;
}

string ThermalScatterMatData::get_atom_name_principal()
{
  return atom_name_principal;
}

string ThermalScatterMatData::get_atom_name_non_principal()
{
  return atom_name_non_principal;
}


int    ThermalScatterMatData::get_mat_no()
{
  return mat_no;
}

int    ThermalScatterMatData::get_mat_no_principal()
{
  return mat_no_principal;
}

int    ThermalScatterMatData::get_mat_no_non_principal()
{
  return mat_no_non_principal;
}

int    ThermalScatterMatData::get_mat_data_principal()
{
  return mat_data_principal;
}

int    ThermalScatterMatData::get_mat_data_non_principal()
{
  return mat_data_non_principal;
}

int    ThermalScatterMatData::get_proton_no_principal()
{
  return mat_data_principal/1000;
}

int    ThermalScatterMatData::get_proton_no_non_principal()
{
  return mat_data_non_principal/1000;
}

int    ThermalScatterMatData::get_mass_no_principal()
{
  return mat_data_principal%1000;
}

int    ThermalScatterMatData::get_mass_no_non_principal()
{
  return mat_data_non_principal%1000;
}

int    ThermalScatterMatData::get_atom_no_principal()
{
  return atom_no_principal;
}

int    ThermalScatterMatData::get_atom_no_mix()
{
  return atom_no_mix;
}

int    ThermalScatterMatData::get_mt_no()
{
  return mt_no;
}

string ThermalScatterMatData::get_tsl_name()
{
  return tsl_name;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//================================================================================================// 
////////////////////////////////////////////////////////////////////////////////////////////////////


//constructor
ThermalScatterMatList::ThermalScatterMatList(void)
{
  set_thermal_scat_data();
}

//destructor
ThermalScatterMatList::~ThermalScatterMatList(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterMatList::clear()
{
  vector<ThermalScatterMatData>().swap(thermal_scat_data);

  data_no = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterMatList::set_thermal_scat_data()
{
  //atom_no_principal is only used when B(4)=M0 of MF=7/MT=4 is less than or equal to 0.
  //If B(4) > 0, atom_no_principal is overwritten by B(4).
  //See follwing classes:
  //(1) read_principal_atom_no(int i) function in NuclearDataProcessorByFrendyInput class
  //    (NuclearDataProcessor/NuclearDataProcessorByFrendyInput.cpp)
  //(2) get_atom_no_principal_tsl(int ele_no) function in MakeInputFromFRENDYtoNJOY class
  //    (NuclearDataProcessor/MakeInputFromFRENDYtoNJOY.cpp)

  clear();

  ThermalScatterMatData tsl_data;
  tsl_data.clear();

  //Case No. 00 (H in H2O)
  tsl_data.set_mat_name("H_in_H2O");
  tsl_data.set_atom_name_principal("h");
  tsl_data.set_atom_name_non_principal("o");

  tsl_data.set_mat_no(1);
  tsl_data.set_mat_no_principal(125);
  tsl_data.set_mat_no_non_principal(825);
  tsl_data.set_mat_data_principal(1001);
  tsl_data.set_mat_data_non_principal(8016);
  tsl_data.set_atom_no_principal(2);
  tsl_data.set_atom_no_mix(1);

  tsl_data.set_mt_no(222);
  tsl_data.set_tsl_name("hh2o");

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 01 (para hydrogen)
  tsl_data.set_mat_name("para_hydrogen");
  tsl_data.set_atom_name_principal("h");
  tsl_data.set_atom_name_non_principal("");

  tsl_data.set_mat_no(2);
  tsl_data.set_mat_no_principal(125);
  tsl_data.set_mat_no_non_principal(0);
  tsl_data.set_mat_data_principal(1001);
  tsl_data.set_mat_data_non_principal(0);
  tsl_data.set_atom_no_principal(2);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 02 (ortho hydrogen)
  tsl_data.set_mat_name("ortho_hydrogen");
  tsl_data.set_atom_name_principal("h");
  tsl_data.set_atom_name_non_principal("");

  tsl_data.set_mat_no(3);
  tsl_data.set_mat_no_principal(125);
  tsl_data.set_mat_no_non_principal(0);
  tsl_data.set_mat_data_principal(1001);
  tsl_data.set_mat_data_non_principal(0);
  tsl_data.set_atom_no_principal(2);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 03 (H in YH2)
  tsl_data.set_mat_name("H_in_YH2");
  tsl_data.set_atom_name_principal("h");
  tsl_data.set_atom_name_non_principal("y");

  tsl_data.set_mat_no(5);
  tsl_data.set_mat_no_principal(125);
  tsl_data.set_mat_no_non_principal(3900);
  tsl_data.set_mat_data_principal(1001);
  tsl_data.set_mat_data_non_principal(39000);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 04 (H in ZrH)
  tsl_data.set_mat_name("H_in_ZrH");
  tsl_data.set_atom_name_principal("h");
  tsl_data.set_atom_name_non_principal("zr");

  tsl_data.set_mat_no(7);
  tsl_data.set_mat_no_principal(125);
  tsl_data.set_mat_no_non_principal(4000);
  tsl_data.set_mat_data_principal(1001);
  tsl_data.set_mat_data_non_principal(40000);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  tsl_data.set_mt_no(225);
  tsl_data.set_tsl_name("hzrh");

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Zr in ZrH2
  tsl_data.set_mat_name("Zr_in_ZrH2");
  tsl_data.set_atom_name_principal("zr");
  tsl_data.set_atom_name_non_principal("h");

  tsl_data.set_mat_no(3001);
  tsl_data.set_mat_no_principal(4000);
  tsl_data.set_mat_no_non_principal(125);
  tsl_data.set_mat_data_principal(40000);
  tsl_data.set_mat_data_non_principal(1001);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //H in ZrH2
  tsl_data.set_mat_name("H_in_ZrH2");
  tsl_data.set_atom_name_principal("h");
  tsl_data.set_atom_name_non_principal("zr");

  tsl_data.set_mat_no(3002);
  tsl_data.set_mat_no_principal(125);
  tsl_data.set_mat_no_non_principal(4000);
  tsl_data.set_mat_data_principal(1001);
  tsl_data.set_mat_data_non_principal(40000);
  tsl_data.set_atom_no_principal(2);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Zr in ZrHx
  tsl_data.set_mat_name("Zr_in_ZrHx");
  tsl_data.set_atom_name_principal("zr");
  tsl_data.set_atom_name_non_principal("h");

  tsl_data.set_mat_no(3006);
  tsl_data.set_mat_no_principal(4000);
  tsl_data.set_mat_no_non_principal(125);
  tsl_data.set_mat_data_principal(40000);
  tsl_data.set_mat_data_non_principal(1001);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //H in ZrHx
  tsl_data.set_mat_name("H_in_ZrHx");
  tsl_data.set_atom_name_principal("h");
  tsl_data.set_atom_name_non_principal("zr");

  tsl_data.set_mat_no(3007);
  tsl_data.set_mat_no_principal(125);
  tsl_data.set_mat_no_non_principal(4000);
  tsl_data.set_mat_data_principal(1001);
  tsl_data.set_mat_data_non_principal(40000);
  tsl_data.set_atom_no_principal(2);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 05 (H in CaH2)
  tsl_data.set_mat_name("H_in_CaH2");
  tsl_data.set_atom_name_principal("h");
  tsl_data.set_atom_name_non_principal("ca");

  tsl_data.set_mat_no(8);
  tsl_data.set_mat_no_principal(125);
  tsl_data.set_mat_no_non_principal(2000);
  tsl_data.set_mat_data_principal(1001);
  tsl_data.set_mat_data_non_principal(20000);
  //The atom_no_principal value is changed from 2 to 1
  //due to the comment of JEFF3.3 library. (2023/10/23) 
  // Thermr: icoh 0, natom 1, mtref 237                                  8 1451   51
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 06 (H in Ice-H2O)
  tsl_data.set_mat_name("H_in_Ice_H2O");
  tsl_data.set_atom_name_principal("h");
  tsl_data.set_atom_name_non_principal("o");

  tsl_data.set_mat_no(10);
  tsl_data.set_mat_no_principal(125);
  tsl_data.set_mat_no_non_principal(825);
  tsl_data.set_mat_data_principal(1001);
  tsl_data.set_mat_data_non_principal(8016);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  tsl_data.set_mt_no(222);
  tsl_data.set_tsl_name("hh2o");

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 07 (D in D2O)
  tsl_data.set_mat_name("D_in_D2O");
  tsl_data.set_atom_name_principal("d");
  tsl_data.set_atom_name_non_principal("o");

  tsl_data.set_mat_no(11);
  tsl_data.set_mat_no_principal(128);
  tsl_data.set_mat_no_non_principal(825);
  tsl_data.set_mat_data_principal(1002);
  tsl_data.set_mat_data_non_principal(8016);
  tsl_data.set_atom_no_principal(2);
  tsl_data.set_atom_no_mix(1);

  tsl_data.set_mt_no(228);
  tsl_data.set_tsl_name("dd2o");

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 08 (para_deuterium)
  tsl_data.set_mat_name("para_deuterium");
  tsl_data.set_atom_name_principal("d");
  tsl_data.set_atom_name_non_principal("");

  tsl_data.set_mat_no(12);
  tsl_data.set_mat_no_principal(128);
  tsl_data.set_mat_no_non_principal(0);
  tsl_data.set_mat_data_principal(1002);
  tsl_data.set_mat_data_non_principal(0);
  tsl_data.set_atom_no_principal(2);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 09 (ortho_deuterium)
  tsl_data.set_mat_name("ortho_deuterium");
  tsl_data.set_atom_name_principal("d");
  tsl_data.set_atom_name_non_principal("");

  tsl_data.set_mat_no(13);
  tsl_data.set_mat_no_principal(128);
  tsl_data.set_mat_no_non_principal(0);
  tsl_data.set_mat_data_principal(1002);
  tsl_data.set_mat_data_non_principal(0);
  tsl_data.set_atom_no_principal(2);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 10 (Be)
  tsl_data.set_mat_name("Be");
  tsl_data.set_atom_name_principal("be");
  tsl_data.set_atom_name_non_principal("");

  tsl_data.set_mat_no(26);
  tsl_data.set_mat_no_principal(425);
  tsl_data.set_mat_no_non_principal(0);
  tsl_data.set_mat_data_principal(4009);
  tsl_data.set_mat_data_non_principal(0);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  tsl_data.set_mt_no(231);
  tsl_data.set_tsl_name("be");

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Be + Sd (tsl-Be-metal+Sd.endf in B8.1)
  tsl_data.set_mat_name("Be");
  tsl_data.set_atom_name_principal("be");
  tsl_data.set_atom_name_non_principal("");

  tsl_data.set_mat_no(204);
  tsl_data.set_mat_no_principal(425);
  tsl_data.set_mat_no_non_principal(0);
  tsl_data.set_mat_data_principal(4009);
  tsl_data.set_mat_data_non_principal(0);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  tsl_data.set_mt_no(231);
  tsl_data.set_tsl_name("be");

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 11 (Be in BeO)
  tsl_data.set_mat_name("Be_in_BeO");
  tsl_data.set_atom_name_principal("be");
  tsl_data.set_atom_name_non_principal("o");

  tsl_data.set_mat_no(27);
  tsl_data.set_mat_no_principal(425);
  tsl_data.set_mat_no_non_principal(825);
  tsl_data.set_mat_data_principal(4009);
  tsl_data.set_mat_data_non_principal(8016);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  tsl_data.set_mt_no(233);
  tsl_data.set_tsl_name("bebeo");

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Be in Be2C
  tsl_data.set_mat_name("Be_in_Be2C");
  tsl_data.set_atom_name_principal("be");
  tsl_data.set_atom_name_non_principal("c");

  tsl_data.set_mat_no(28);
  tsl_data.set_mat_no_principal(425);
  tsl_data.set_mat_no_non_principal(600);
  tsl_data.set_mat_data_principal(4009);
  tsl_data.set_mat_data_non_principal(6000);
  tsl_data.set_atom_no_principal(2);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //C in Be2C
  tsl_data.set_mat_name("C_in_Be2C");
  tsl_data.set_atom_name_principal("c");
  tsl_data.set_atom_name_non_principal("be");

  tsl_data.set_mat_no(1021);
  tsl_data.set_mat_no_principal(600);
  tsl_data.set_mat_no_non_principal(425);
  tsl_data.set_mat_data_principal(6000);
  tsl_data.set_mat_data_non_principal(4009);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 12 (graphite, crystalline-graphite 10P)
  tsl_data.set_mat_name("graphite");
  tsl_data.set_atom_name_principal("c");
  tsl_data.set_atom_name_non_principal("");

  tsl_data.set_mat_no(31);
  tsl_data.set_mat_no_principal(600);
  tsl_data.set_mat_no_non_principal(0);
  tsl_data.set_mat_data_principal(6000);
  tsl_data.set_mat_data_non_principal(0);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);


  tsl_data.set_mt_no(229);
  tsl_data.set_tsl_name("graph");

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 13 (crystalline-graphite)
  tsl_data.set_mat_name("cry-graphite");
  tsl_data.set_atom_name_principal("c");
  tsl_data.set_atom_name_non_principal("");

  tsl_data.set_mat_no(30);
  tsl_data.set_mat_no_principal(600);
  tsl_data.set_mat_no_non_principal(0);
  tsl_data.set_mat_data_principal(6000);
  tsl_data.set_mat_data_non_principal(0);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  tsl_data.set_mt_no(229);
  tsl_data.set_tsl_name("graph");

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //crystalline-graphite 20P
  tsl_data.set_mat_name("cry-graphite-20p");
  tsl_data.set_atom_name_principal("c");
  tsl_data.set_atom_name_non_principal("");

  tsl_data.set_mat_no(320);
  tsl_data.set_mat_no_principal(600);
  tsl_data.set_mat_no_non_principal(0);
  tsl_data.set_mat_data_principal(6000);
  tsl_data.set_mat_data_non_principal(0);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  tsl_data.set_mt_no(229);
  tsl_data.set_tsl_name("graph");

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 14 (crystalline-graphite 30P)
  tsl_data.set_mat_name("cry-graphite-30p");
  tsl_data.set_atom_name_principal("c");
  tsl_data.set_atom_name_non_principal("");

  tsl_data.set_mat_no(32);
  tsl_data.set_mat_no_principal(600);
  tsl_data.set_mat_no_non_principal(0);
  tsl_data.set_mat_data_principal(6000);
  tsl_data.set_mat_data_non_principal(0);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  tsl_data.set_mt_no(229);
  tsl_data.set_tsl_name("graph");

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //crystalline-graphite Sd
  tsl_data.set_mat_name("cry-graphite-sd");
  tsl_data.set_atom_name_principal("c");
  tsl_data.set_atom_name_non_principal("");

  tsl_data.set_mat_no(301);
  tsl_data.set_mat_no_principal(600);
  tsl_data.set_mat_no_non_principal(0);
  tsl_data.set_mat_data_principal(6000);
  tsl_data.set_mat_data_non_principal(0);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  tsl_data.set_mt_no(229);
  tsl_data.set_tsl_name("graph");

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 15 (H in liquid_methane (CH4))
  tsl_data.set_mat_name("H_in_Liquid_Methane");
  tsl_data.set_atom_name_principal("h");
  tsl_data.set_atom_name_non_principal("c");

  tsl_data.set_mat_no(33);
  tsl_data.set_mat_no_principal(125);
  tsl_data.set_mat_no_non_principal(600);
  tsl_data.set_mat_data_principal(1001);
  tsl_data.set_mat_data_non_principal(6000);
  tsl_data.set_atom_no_principal(4);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 16 (H in solid_methane) (CH4)
  tsl_data.set_mat_name("H_in_Solid_Methane");
  tsl_data.set_atom_name_principal("h");
  tsl_data.set_atom_name_non_principal("c");

  tsl_data.set_mat_no(34);
  tsl_data.set_mat_no_principal(125);
  tsl_data.set_mat_no_non_principal(600);
  tsl_data.set_mat_data_principal(1001);
  tsl_data.set_mat_data_non_principal(6000);
  tsl_data.set_atom_no_principal(4);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 17 (H in polyethylene (CH2))
  tsl_data.set_mat_name("H_in_Polyethylene");
  tsl_data.set_atom_name_principal("h");
  tsl_data.set_atom_name_non_principal("c");

  tsl_data.set_mat_no(37);
  tsl_data.set_mat_no_principal(125);
  tsl_data.set_mat_no_non_principal(600);
  tsl_data.set_mat_data_principal(1001);
  tsl_data.set_mat_data_non_principal(6000);
  tsl_data.set_atom_no_principal(2);
  tsl_data.set_atom_no_mix(1);

  tsl_data.set_mt_no(223);
  tsl_data.set_tsl_name("poly");

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //C in polyethylene (C8H8)
  tsl_data.set_mat_name("C_in_Polyethylene");
  tsl_data.set_atom_name_principal("c");
  tsl_data.set_atom_name_non_principal("h");

  tsl_data.set_mat_no(1011);
  tsl_data.set_mat_no_principal(600);
  tsl_data.set_mat_no_non_principal(125);
  tsl_data.set_mat_data_principal(6000);
  tsl_data.set_mat_data_non_principal(1001);
  tsl_data.set_atom_no_principal(8);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //H in polyethylene (C8H8)
  tsl_data.set_mat_name("H_in_Polyethylene");
  tsl_data.set_atom_name_principal("h");
  tsl_data.set_atom_name_non_principal("c");

  tsl_data.set_mat_no(1012);
  tsl_data.set_mat_no_principal(125);
  tsl_data.set_mat_no_non_principal(600);
  tsl_data.set_mat_data_principal(1001);
  tsl_data.set_mat_data_non_principal(6000);
  tsl_data.set_atom_no_principal(8);
  tsl_data.set_atom_no_mix(1);

  tsl_data.set_mt_no(223);
  tsl_data.set_tsl_name("poly");

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 18 (H in C5O2H8 (Lucite))
  tsl_data.set_mat_name("H_in_C5O2H8");
  tsl_data.set_atom_name_principal("h");
  tsl_data.set_atom_name_non_principal("c");

  tsl_data.set_mat_no(39);
  tsl_data.set_mat_no_principal(125);
  tsl_data.set_mat_no_non_principal(600);
  tsl_data.set_mat_data_principal(1001);
  tsl_data.set_mat_data_non_principal(6000);
  tsl_data.set_atom_no_principal(8);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //O in C5O2H8 (Lucite) (b81)
  tsl_data.set_mat_name("O_in_C5O2H8");
  tsl_data.set_atom_name_principal("o");
  tsl_data.set_atom_name_non_principal("h");

  tsl_data.set_mat_no(1501);
  tsl_data.set_mat_no_principal(825);
  tsl_data.set_mat_no_non_principal(125);
  tsl_data.set_mat_data_principal(8016);
  tsl_data.set_mat_data_non_principal(1001);
  tsl_data.set_atom_no_principal(2);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //C in C5O2H8 (Lucite) (b81)
  tsl_data.set_mat_name("C_in_C5O2H8");
  tsl_data.set_atom_name_principal("c");
  tsl_data.set_atom_name_non_principal("h");

  tsl_data.set_mat_no(1502);
  tsl_data.set_mat_no_principal(600);
  tsl_data.set_mat_no_non_principal(125);
  tsl_data.set_mat_data_principal(6000);
  tsl_data.set_mat_data_non_principal(1001);
  tsl_data.set_atom_no_principal(5);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 19 (H in benzene (C6H6))
  tsl_data.set_mat_name("H_in_benzene");
  tsl_data.set_atom_name_principal("h");
  tsl_data.set_atom_name_non_principal("c");

  tsl_data.set_mat_no(40);
  tsl_data.set_mat_no_principal(125);
  tsl_data.set_mat_no_non_principal(600);
  tsl_data.set_mat_data_principal(1001);
  tsl_data.set_mat_data_non_principal(6000);
  tsl_data.set_atom_no_principal(6);
  tsl_data.set_atom_no_mix(1);

  tsl_data.set_mt_no(227);
  tsl_data.set_tsl_name("benz");

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 20 (O in D2O)
  tsl_data.set_mat_name("O_in_D2O");
  tsl_data.set_atom_name_principal("o");
  tsl_data.set_atom_name_non_principal("d");

  tsl_data.set_mat_no(41);
  tsl_data.set_mat_no_principal(825);
  tsl_data.set_mat_no_non_principal(128);
  tsl_data.set_mat_data_principal(8016);
  tsl_data.set_mat_data_non_principal(1002);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //H in Paraffinic Oil for ENDF/B-VIII.1 (Same MAT number as O in D2O)
  tsl_data.set_mat_name("H_in_ParaffinicOil");
  tsl_data.set_atom_name_principal("h");
  tsl_data.set_atom_name_non_principal("c");

  tsl_data.set_mat_no(41);
  tsl_data.set_mat_no_principal(125);
  tsl_data.set_mat_no_non_principal(600);
  tsl_data.set_mat_data_principal(1001);
  tsl_data.set_mat_data_non_principal(6000);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 21 (Si in SiC)
  tsl_data.set_mat_name("Si_in_SiC");
  tsl_data.set_atom_name_principal("si");
  tsl_data.set_atom_name_non_principal("c");

  tsl_data.set_mat_no(43);
  tsl_data.set_mat_no_principal(1400);
  tsl_data.set_mat_no_non_principal(600);
  tsl_data.set_mat_data_principal(14000);
  tsl_data.set_mat_data_non_principal(6000);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 22 (C in SiC)
  tsl_data.set_mat_name("C_in_SiC");
  tsl_data.set_atom_name_principal("c");
  tsl_data.set_atom_name_non_principal("si");

  tsl_data.set_mat_no(44);
  tsl_data.set_mat_no_principal(600);
  tsl_data.set_mat_no_non_principal(1400);
  tsl_data.set_mat_data_principal(6000);
  tsl_data.set_mat_data_non_principal(14000);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 23 (O in BeO)
  tsl_data.set_mat_name("O_in_BeO");
  tsl_data.set_atom_name_principal("o");
  tsl_data.set_atom_name_non_principal("be");

  tsl_data.set_mat_no(46);
  tsl_data.set_mat_no_principal(825);
  tsl_data.set_mat_no_non_principal(425);
  tsl_data.set_mat_data_principal(8016);
  tsl_data.set_mat_data_non_principal(4009);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  tsl_data.set_mt_no(237);
  tsl_data.set_tsl_name("obeo");

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 24 (Si in alpha_quartz (SiO2))
  tsl_data.set_mat_name("si_in_alpha_quartz");
  tsl_data.set_atom_name_principal("si");
  tsl_data.set_atom_name_non_principal("o");

  tsl_data.set_mat_no(47);
  tsl_data.set_mat_no_principal(1400);
  tsl_data.set_mat_no_non_principal(825);
  tsl_data.set_mat_data_principal(14000);
  tsl_data.set_mat_data_non_principal(8016);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(3);
  //For crystall material, atom_no_mix is not 2 (Si + O2) but atom_no_mix is 3 (Si + O + O).

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Si in alpha_quartz (SiO2) for ENDF/B-VIII.1
  tsl_data.set_mat_name("si_in_alpha_quartz");
  tsl_data.set_atom_name_principal("si");
  tsl_data.set_atom_name_non_principal("o");

  tsl_data.set_mat_no(3016);
  tsl_data.set_mat_no_principal(1400);
  tsl_data.set_mat_no_non_principal(825);
  tsl_data.set_mat_data_principal(14000);
  tsl_data.set_mat_data_non_principal(8016);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);
  //atom_no_mix is set 1 from the processing results of ENDF/B-VIII.1 (tsl-OinSiO2-alpha.endf).

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //O in alpha_quartz (SiO2)
  tsl_data.set_mat_name("o_in_alpha_quartz");
  tsl_data.set_atom_name_principal("o");
  tsl_data.set_atom_name_non_principal("si");

  tsl_data.set_mat_no(3017);
  tsl_data.set_mat_no_principal(825);
  tsl_data.set_mat_no_non_principal(1400);
  tsl_data.set_mat_data_principal(8016);
  tsl_data.set_mat_data_non_principal(14000);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);
  //atom_no_mix is set 1 from the processing results of ENDF/B-VIII.1 (tsl-OinSiO2-alpha.endf).

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 25 (U in UO2)
  tsl_data.set_mat_name("U_in_UO2");
  tsl_data.set_atom_name_principal("u");
  tsl_data.set_atom_name_non_principal("o");

  tsl_data.set_mat_no(48);
  tsl_data.set_mat_no_principal(9200);
  tsl_data.set_mat_no_non_principal(825);
  tsl_data.set_mat_data_principal(92000);
  tsl_data.set_mat_data_non_principal(8016);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  tsl_data.set_mt_no(241);
  tsl_data.set_tsl_name("uuo2");

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //U in UO2 (Natual Uranium 0.7204wt%) ENDF/B-VIII.1
  tsl_data.set_mat_name("U_in_UO2");
  tsl_data.set_atom_name_principal("u");
  tsl_data.set_atom_name_non_principal("o");

  tsl_data.set_mat_no(75);
  tsl_data.set_mat_no_principal(9237);
  tsl_data.set_mat_no_non_principal(825);
  tsl_data.set_mat_data_principal(92238);
  tsl_data.set_mat_data_non_principal(8016);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  tsl_data.set_mt_no(241);
  tsl_data.set_tsl_name("uuo2");

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //U in UO2 (100wt%) ENDF/B-VIII.1
  tsl_data.set_mat_name("U_in_UO2");
  tsl_data.set_atom_name_principal("u");
  tsl_data.set_atom_name_non_principal("o");

  tsl_data.set_mat_no(84);
  tsl_data.set_mat_no_principal(9228);
  tsl_data.set_mat_no_non_principal(825);
  tsl_data.set_mat_data_principal(92235);
  tsl_data.set_mat_data_non_principal(8016);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  tsl_data.set_mt_no(241);
  tsl_data.set_tsl_name("uuo2");

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //U in UO2 (100wt%) ENDF/B-VIII.1
  tsl_data.set_mat_name("U_in_UO2");
  tsl_data.set_atom_name_principal("u");
  tsl_data.set_atom_name_non_principal("o");

  tsl_data.set_mat_no(84);
  tsl_data.set_mat_no_principal(9228);
  tsl_data.set_mat_no_non_principal(825);
  tsl_data.set_mat_data_principal(92235);
  tsl_data.set_mat_data_non_principal(8016);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  tsl_data.set_mt_no(241);
  tsl_data.set_tsl_name("uuo2");

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //U in UO2 (5wt%) ENDF/B-VIII.1
  tsl_data.set_mat_name("U_in_UO2");
  tsl_data.set_atom_name_principal("u");
  tsl_data.set_atom_name_non_principal("o");

  tsl_data.set_mat_no(8205);
  tsl_data.set_mat_no_principal(9237);
  tsl_data.set_mat_no_non_principal(825);
  tsl_data.set_mat_data_principal(92238);
  tsl_data.set_mat_data_non_principal(8016);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  tsl_data.set_mt_no(241);
  tsl_data.set_tsl_name("uuo2");

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //U in UO2 (10wt%) ENDF/B-VIII.1
  tsl_data.set_mat_name("U_in_UO2");
  tsl_data.set_atom_name_principal("u");
  tsl_data.set_atom_name_non_principal("o");

  tsl_data.set_mat_no(8210);
  tsl_data.set_mat_no_principal(9237);
  tsl_data.set_mat_no_non_principal(825);
  tsl_data.set_mat_data_principal(92238);
  tsl_data.set_mat_data_non_principal(8016);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  tsl_data.set_mt_no(241);
  tsl_data.set_tsl_name("uuo2");

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //U in UO2 (HALEU / 19.75wt%) ENDF/B-VIII.1
  tsl_data.set_mat_name("U_in_UO2");
  tsl_data.set_atom_name_principal("u");
  tsl_data.set_atom_name_non_principal("o");

  tsl_data.set_mat_no(8248);
  tsl_data.set_mat_no_principal(9237);
  tsl_data.set_mat_no_non_principal(825);
  tsl_data.set_mat_data_principal(92238);
  tsl_data.set_mat_data_non_principal(8016);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  tsl_data.set_mt_no(241);
  tsl_data.set_tsl_name("uuo2");

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //U in UO2 (HEU / 93wt%) ENDF/B-VIII.1
  tsl_data.set_mat_name("U_in_UO2");
  tsl_data.set_atom_name_principal("u");
  tsl_data.set_atom_name_non_principal("o");

  tsl_data.set_mat_no(8249);
  tsl_data.set_mat_no_principal(9228);
  tsl_data.set_mat_no_non_principal(825);
  tsl_data.set_mat_data_principal(92235);
  tsl_data.set_mat_data_non_principal(8016);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  tsl_data.set_mt_no(241);
  tsl_data.set_tsl_name("uuo2");

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 26 (Si in beta_quartz (SiO2))
  tsl_data.set_mat_name("si_in_beta_quartz");
  tsl_data.set_atom_name_principal("si");
  tsl_data.set_atom_name_non_principal("o");

  tsl_data.set_mat_no(49);
  tsl_data.set_mat_no_principal(1400);
  tsl_data.set_mat_no_non_principal(825);
  tsl_data.set_mat_data_principal(14000);
  tsl_data.set_mat_data_non_principal(8016);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(3);
  //For crystall material, atom_no_mix is not 2 (Si + O2) but atom_no_mix is 3 (Si + O + O).

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 27 (O in IceH)
  tsl_data.set_mat_name("O_in_Ice_H2O");
  tsl_data.set_atom_name_principal("o");
  tsl_data.set_atom_name_non_principal("h");

  tsl_data.set_mat_no(50);
  tsl_data.set_mat_no_principal(825);
  tsl_data.set_mat_no_non_principal(125);
  tsl_data.set_mat_data_principal(8016);
  tsl_data.set_mat_data_non_principal(1001);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 28 (O in D2O)
  tsl_data.set_mat_name("O_in_D2O");
  tsl_data.set_atom_name_principal("o");
  tsl_data.set_atom_name_non_principal("d");

  tsl_data.set_mat_no(51);
  tsl_data.set_mat_no_principal(825);
  tsl_data.set_mat_no_non_principal(128);
  tsl_data.set_mat_data_principal(8016);
  tsl_data.set_mat_data_non_principal(1002);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 29 (Mg)
  tsl_data.set_mat_name("Mg");
  tsl_data.set_atom_name_principal("mg");
  tsl_data.set_atom_name_non_principal("");

  tsl_data.set_mat_no(52);
  tsl_data.set_mat_no_principal(1200);
  tsl_data.set_mat_no_non_principal(0);
  tsl_data.set_mat_data_principal(12000);
  tsl_data.set_mat_data_non_principal(0);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 30 (Al)
  tsl_data.set_mat_name("Al");
  tsl_data.set_atom_name_principal("al");
  tsl_data.set_atom_name_non_principal("");

  tsl_data.set_mat_no(53);
  tsl_data.set_mat_no_principal(1325);
  tsl_data.set_mat_no_non_principal(0);
  tsl_data.set_mat_data_principal(13027);
  tsl_data.set_mat_data_non_principal(0);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  tsl_data.set_mt_no(243);
  tsl_data.set_tsl_name("al");

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 31 (Y in YH2)
  tsl_data.set_mat_name("Y_in_YH2");
  tsl_data.set_atom_name_principal("y");
  tsl_data.set_atom_name_non_principal("h");

  tsl_data.set_mat_no(55);
  tsl_data.set_mat_no_principal(3900);
  tsl_data.set_mat_no_non_principal(125);
  tsl_data.set_mat_data_principal(39000);
  tsl_data.set_mat_data_non_principal(1001);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 32 (Fe)
  tsl_data.set_mat_name("Fe");
  tsl_data.set_atom_name_principal("fe");
  tsl_data.set_atom_name_non_principal("");

  tsl_data.set_mat_no(56);
  tsl_data.set_mat_no_principal(2600);
  tsl_data.set_mat_no_non_principal(0);
  tsl_data.set_mat_data_principal(26000);
  tsl_data.set_mat_data_non_principal(0);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  tsl_data.set_mt_no(245);
  tsl_data.set_tsl_name("fe");

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 33 (Zr in ZrH)
  tsl_data.set_mat_name("Zr_in_ZrH");
  tsl_data.set_atom_name_principal("zr");
  tsl_data.set_atom_name_non_principal("h");

  tsl_data.set_mat_no(58);
  tsl_data.set_mat_no_principal(4000);
  tsl_data.set_mat_no_non_principal(125);
  tsl_data.set_mat_data_principal(40000);
  tsl_data.set_mat_data_non_principal(1001);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  tsl_data.set_mt_no(235);
  tsl_data.set_tsl_name("zrzrh");

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 34 (Ca in CaH2)
  tsl_data.set_mat_name("Ca_in_CaH2");
  tsl_data.set_atom_name_principal("ca");
  tsl_data.set_atom_name_non_principal("h");

  tsl_data.set_mat_no(59);
  tsl_data.set_mat_no_principal(2000);
  tsl_data.set_mat_no_non_principal(125);
  tsl_data.set_mat_data_principal(20000);
  tsl_data.set_mat_data_non_principal(1001);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Si (mono-crystal) for JEFF-3.3 (Same MAT number as Ca in CaH2) 
  tsl_data.set_mat_name("Si");
  tsl_data.set_atom_name_principal("si");
  tsl_data.set_atom_name_non_principal("");

  tsl_data.set_mat_no(59);
  tsl_data.set_mat_no_principal(1400);
  tsl_data.set_mat_no_non_principal(0);
  tsl_data.set_mat_data_principal(14000);
  tsl_data.set_mat_data_non_principal(0);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 35 (O in UO2)
  tsl_data.set_mat_name("O_in_UO2");
  tsl_data.set_atom_name_principal("o");
  tsl_data.set_atom_name_non_principal("u");

  tsl_data.set_mat_no(75);
  tsl_data.set_mat_no_principal(825);
  tsl_data.set_mat_no_non_principal(9200);
  tsl_data.set_mat_data_principal(8016);
  tsl_data.set_mat_data_non_principal(92000);
  tsl_data.set_atom_no_principal(2);
  tsl_data.set_atom_no_mix(1);

  tsl_data.set_mt_no(239);
  tsl_data.set_tsl_name("ouo2");

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //O in UO2 (Natural Uranium, 99.2742wt%), ENDF/B-VIII.1
  tsl_data.set_mat_name("O_in_UO2");
  tsl_data.set_atom_name_principal("o");
  tsl_data.set_atom_name_non_principal("u");

  tsl_data.set_mat_no(45);
  tsl_data.set_mat_no_principal(825);
  tsl_data.set_mat_no_non_principal(9237);
  tsl_data.set_mat_data_principal(8016);
  tsl_data.set_mat_data_non_principal(92238);
  tsl_data.set_atom_no_principal(2);
  tsl_data.set_atom_no_mix(1);

  tsl_data.set_mt_no(239);
  tsl_data.set_tsl_name("ouo2");

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //O in UO2 (5wt%), ENDF/B-VIII.1
  tsl_data.set_mat_name("O_in_UO2");
  tsl_data.set_atom_name_principal("o");
  tsl_data.set_atom_name_non_principal("u");

  tsl_data.set_mat_no(8255);
  tsl_data.set_mat_no_principal(825);
  tsl_data.set_mat_no_non_principal(9237);
  tsl_data.set_mat_data_principal(8016);
  tsl_data.set_mat_data_non_principal(92238);
  tsl_data.set_atom_no_principal(2);
  tsl_data.set_atom_no_mix(1);

  tsl_data.set_mt_no(239);
  tsl_data.set_tsl_name("ouo2");

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //O in UO2 (10wt%), ENDF/B-VIII.1
  tsl_data.set_mat_name("O_in_UO2");
  tsl_data.set_atom_name_principal("o");
  tsl_data.set_atom_name_non_principal("u");

  tsl_data.set_mat_no(8260);
  tsl_data.set_mat_no_principal(825);
  tsl_data.set_mat_no_non_principal(9237);
  tsl_data.set_mat_data_principal(8016);
  tsl_data.set_mat_data_non_principal(92238);
  tsl_data.set_atom_no_principal(2);
  tsl_data.set_atom_no_mix(1);

  tsl_data.set_mt_no(239);
  tsl_data.set_tsl_name("ouo2");

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //O in UO2 (100wt%), ENDF/B-VIII.1
  tsl_data.set_mat_name("O_in_UO2");
  tsl_data.set_atom_name_principal("o");
  tsl_data.set_atom_name_non_principal("u");

  tsl_data.set_mat_no(8297);
  tsl_data.set_mat_no_principal(825);
  tsl_data.set_mat_no_non_principal(9228);
  tsl_data.set_mat_data_principal(8016);
  tsl_data.set_mat_data_non_principal(92235);
  tsl_data.set_atom_no_principal(2);
  tsl_data.set_atom_no_mix(1);

  tsl_data.set_mt_no(239);
  tsl_data.set_tsl_name("ouo2");

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //O in UO2 (HALEU, 19.75wt%), ENDF/B-VIII.1
  tsl_data.set_mat_name("O_in_UO2");
  tsl_data.set_atom_name_principal("o");
  tsl_data.set_atom_name_non_principal("u");

  tsl_data.set_mat_no(8298);
  tsl_data.set_mat_no_principal(825);
  tsl_data.set_mat_no_non_principal(9237);
  tsl_data.set_mat_data_principal(8016);
  tsl_data.set_mat_data_non_principal(92238);
  tsl_data.set_atom_no_principal(2);
  tsl_data.set_atom_no_mix(1);

  tsl_data.set_mt_no(239);
  tsl_data.set_tsl_name("ouo2");

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //O in UO2 (HEU, 93wt%), ENDF/B-VIII.1
  tsl_data.set_mat_name("O_in_UO2");
  tsl_data.set_atom_name_principal("o");
  tsl_data.set_atom_name_non_principal("u");

  tsl_data.set_mat_no(8299);
  tsl_data.set_mat_no_principal(825);
  tsl_data.set_mat_no_non_principal(9228);
  tsl_data.set_mat_data_principal(8016);
  tsl_data.set_mat_data_non_principal(92235);
  tsl_data.set_atom_no_principal(2);
  tsl_data.set_atom_no_mix(1);

  tsl_data.set_mt_no(239);
  tsl_data.set_tsl_name("ouo2");

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 36 (N in UN)
  tsl_data.set_mat_name("N_in_UN");
  tsl_data.set_atom_name_principal("n");
  tsl_data.set_atom_name_non_principal("u");

  tsl_data.set_mat_no(71);
  tsl_data.set_mat_no_principal(725);
  tsl_data.set_mat_no_non_principal(9200);
  tsl_data.set_mat_data_principal(7014);
  tsl_data.set_mat_data_non_principal(92000);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 37 (U in UN)
  tsl_data.set_mat_name("U_in_UN");
  tsl_data.set_atom_name_principal("u");
  tsl_data.set_atom_name_non_principal("n");

  tsl_data.set_mat_no(72);
  tsl_data.set_mat_no_principal(9200);
  tsl_data.set_mat_no_non_principal(725);
  tsl_data.set_mat_data_principal(92000);
  tsl_data.set_mat_data_non_principal(7014);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 38 (Al in Al2O3)
  tsl_data.set_mat_name("Al_in_Al2O3");
  tsl_data.set_atom_name_principal("al");
  tsl_data.set_atom_name_non_principal("o");

  tsl_data.set_mat_no(60);
  tsl_data.set_mat_no_principal(1325);
  tsl_data.set_mat_no_non_principal(825);
  tsl_data.set_mat_data_principal(13027);
  tsl_data.set_mat_data_non_principal(8016);
  tsl_data.set_atom_no_principal(2);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 39 (H in Mesitylene (C9H12))
  tsl_data.set_mat_name("H_in_Mesitylene");
  tsl_data.set_atom_name_principal("h");
  tsl_data.set_atom_name_non_principal("c");

  tsl_data.set_mat_no(38);
  tsl_data.set_mat_no_principal(125);
  tsl_data.set_mat_no_non_principal(600);
  tsl_data.set_mat_data_principal(1001);
  tsl_data.set_mat_data_non_principal(6000);
  tsl_data.set_atom_no_principal(12);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 40 (H in Toluene (C7H8))
  tsl_data.set_mat_name("H_in_toluene");
  tsl_data.set_atom_name_principal("h");
  tsl_data.set_atom_name_non_principal("c");

  tsl_data.set_mat_no(42);
  tsl_data.set_mat_no_principal(125);
  tsl_data.set_mat_no_non_principal(600);
  tsl_data.set_mat_data_principal(1001);
  tsl_data.set_mat_data_non_principal(6000);
  tsl_data.set_atom_no_principal(8);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 41 (H in H2O @ JENDL-5a4)
  tsl_data.set_mat_name("H_in_H2O_demo");
  tsl_data.set_atom_name_principal("h");
  tsl_data.set_atom_name_non_principal("o");

  tsl_data.set_mat_no(101);
  tsl_data.set_mat_no_principal(125);
  tsl_data.set_mat_no_non_principal(825);
  tsl_data.set_mat_data_principal(1001);
  tsl_data.set_mat_data_non_principal(8016);
  tsl_data.set_atom_no_principal(2);
  tsl_data.set_atom_no_mix(1);

  tsl_data.set_mt_no(222);
  tsl_data.set_tsl_name("hh2o");

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 42 (O in H2O @ JENDL-5a4)
  tsl_data.set_mat_name("O_in_H2O_demo");
  tsl_data.set_atom_name_principal("o");
  tsl_data.set_atom_name_non_principal("h");

  tsl_data.set_mat_no(100);
  tsl_data.set_mat_no_principal(825);
  tsl_data.set_mat_no_non_principal(125);
  tsl_data.set_mat_data_principal(8016);
  tsl_data.set_mat_data_non_principal(1001);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 43 (O in H2O @ JENDL-5)
  tsl_data.set_mat_name("O_in_H2O");
  tsl_data.set_atom_name_principal("o");
  tsl_data.set_atom_name_non_principal("h");

  tsl_data.set_mat_no(661);
  tsl_data.set_mat_no_principal(825);
  tsl_data.set_mat_no_non_principal(125);
  tsl_data.set_mat_data_principal(8016);
  tsl_data.set_mat_data_non_principal(1001);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 44 (C in liquid_methane (CH4))
  tsl_data.set_mat_name("C_in_Liquid_Methane");
  tsl_data.set_atom_name_principal("c");
  tsl_data.set_atom_name_non_principal("h");

  tsl_data.set_mat_no(633);
  tsl_data.set_mat_no_principal(600);
  tsl_data.set_mat_no_non_principal(125);
  tsl_data.set_mat_data_principal(6000);
  tsl_data.set_mat_data_non_principal(1001);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 45 (C in solid_methane (CH4))
  tsl_data.set_mat_name("C_in_Solid_Methane");
  tsl_data.set_atom_name_principal("c");
  tsl_data.set_atom_name_non_principal("h");

  tsl_data.set_mat_no(634);
  tsl_data.set_mat_no_principal(600);
  tsl_data.set_mat_no_non_principal(125);
  tsl_data.set_mat_data_principal(6000);
  tsl_data.set_mat_data_non_principal(1001);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 46 (H in liquid_mesitylene (C9H12))
  tsl_data.set_mat_name("H_in_Liquid_Mesitylene");
  tsl_data.set_atom_name_principal("h");
  tsl_data.set_atom_name_non_principal("c");

  tsl_data.set_mat_no(602);
  tsl_data.set_mat_no_principal(125);
  tsl_data.set_mat_no_non_principal(600);
  tsl_data.set_mat_data_principal(1001);
  tsl_data.set_mat_data_non_principal(6000);
  tsl_data.set_atom_no_principal(12);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 47 (C in liquid_mesitylene (C9H12))
  tsl_data.set_mat_name("C_in_Liquid_Mesitylene");
  tsl_data.set_atom_name_principal("c");
  tsl_data.set_atom_name_non_principal("h");

  tsl_data.set_mat_no(632);
  tsl_data.set_mat_no_principal(600);
  tsl_data.set_mat_no_non_principal(125);
  tsl_data.set_mat_data_principal(6000);
  tsl_data.set_mat_data_non_principal(1001);
  tsl_data.set_atom_no_principal(9);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 48 (C in solid_mesitylene (C9H12))
  tsl_data.set_mat_name("C_in_Solid_Mesitylene");
  tsl_data.set_atom_name_principal("c");
  tsl_data.set_atom_name_non_principal("h");

  tsl_data.set_mat_no(638);
  tsl_data.set_mat_no_principal(600);
  tsl_data.set_mat_no_non_principal(125);
  tsl_data.set_mat_data_principal(6000);
  tsl_data.set_mat_data_non_principal(1001);
  tsl_data.set_atom_no_principal(9);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 49 (C_in benzene (C6H6))
  tsl_data.set_mat_name("C_in_Benzene");
  tsl_data.set_atom_name_principal("c");
  tsl_data.set_atom_name_non_principal("h");

  tsl_data.set_mat_no(640);
  tsl_data.set_mat_no_principal(600);
  tsl_data.set_mat_no_non_principal(125);
  tsl_data.set_mat_data_principal(6000);
  tsl_data.set_mat_data_non_principal(1001);
  tsl_data.set_atom_no_principal(6);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 50 (H in solid_benzene (C6H6))
  tsl_data.set_mat_name("H_in_Solid_Benzene");
  tsl_data.set_atom_name_principal("h");
  tsl_data.set_atom_name_non_principal("c");

  tsl_data.set_mat_no(611);
  tsl_data.set_mat_no_principal(125);
  tsl_data.set_mat_no_non_principal(600);
  tsl_data.set_mat_data_principal(1001);
  tsl_data.set_mat_data_non_principal(6000);
  tsl_data.set_atom_no_principal(6);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 51 (C in solid_benzene (C6H6))
  tsl_data.set_mat_name("C_in_Solid_Benzene");
  tsl_data.set_atom_name_principal("c");
  tsl_data.set_atom_name_non_principal("h");

  tsl_data.set_mat_no(641);
  tsl_data.set_mat_no_principal(600);
  tsl_data.set_mat_no_non_principal(125);
  tsl_data.set_mat_data_principal(6000);
  tsl_data.set_mat_data_non_principal(1001);
  tsl_data.set_atom_no_principal(6);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 52 (H in liquid_toluene (C7H8))
  tsl_data.set_mat_name("H_in_Liquid_Toluene");
  tsl_data.set_atom_name_principal("h");
  tsl_data.set_atom_name_non_principal("c");

  tsl_data.set_mat_no(605);
  tsl_data.set_mat_no_principal(125);
  tsl_data.set_mat_no_non_principal(600);
  tsl_data.set_mat_data_principal(1001);
  tsl_data.set_mat_data_non_principal(6000);
  tsl_data.set_atom_no_principal(8);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 53 (C in liquid_toluene (C7H8))
  tsl_data.set_mat_name("C_in_Liquid_Toluene");
  tsl_data.set_atom_name_principal("c");
  tsl_data.set_atom_name_non_principal("h");

  tsl_data.set_mat_no(635);
  tsl_data.set_mat_no_principal(600);
  tsl_data.set_mat_no_non_principal(125);
  tsl_data.set_mat_data_principal(6000);
  tsl_data.set_mat_data_non_principal(1001);
  tsl_data.set_atom_no_principal(7);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 54 (C in solid_toluene (C7H8))
  tsl_data.set_mat_name("C_in_Solid_Toluene");
  tsl_data.set_atom_name_principal("c");
  tsl_data.set_atom_name_non_principal("h");

  tsl_data.set_mat_no(642);
  tsl_data.set_mat_no_principal(600);
  tsl_data.set_mat_no_non_principal(125);
  tsl_data.set_mat_data_principal(6000);
  tsl_data.set_mat_data_non_principal(1001);
  tsl_data.set_atom_no_principal(7);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 55 (H in liquid_ethanol (C2H6O))
  tsl_data.set_mat_name("H_in_Liquid_Ethanol");
  tsl_data.set_atom_name_principal("h");
  tsl_data.set_atom_name_non_principal("c");

  tsl_data.set_mat_no(606);
  tsl_data.set_mat_no_principal(125);
  tsl_data.set_mat_no_non_principal(600);
  tsl_data.set_mat_data_principal(1001);
  tsl_data.set_mat_data_non_principal(6000);
  tsl_data.set_atom_no_principal(6);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 56 (C in liquid_ethanol (C2H6O))
  tsl_data.set_mat_name("C_in_Liquid_Ethanol");
  tsl_data.set_atom_name_principal("c");
  tsl_data.set_atom_name_non_principal("h");

  tsl_data.set_mat_no(636);
  tsl_data.set_mat_no_principal(600);
  tsl_data.set_mat_no_non_principal(125);
  tsl_data.set_mat_data_principal(6000);
  tsl_data.set_mat_data_non_principal(1001);
  tsl_data.set_atom_no_principal(2);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 57 (O in liquid_ethanol (C2H6O))
  tsl_data.set_mat_name("O_in_Liquid_Ethanol");
  tsl_data.set_atom_name_principal("o");
  tsl_data.set_atom_name_non_principal("h");

  tsl_data.set_mat_no(666);
  tsl_data.set_mat_no_principal(825);
  tsl_data.set_mat_no_non_principal(125);
  tsl_data.set_mat_data_principal(8016);
  tsl_data.set_mat_data_non_principal(1001);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 58 (H in solid_ethanol (C2H6O))
  tsl_data.set_mat_name("H_in_Solid_Ethanol");
  tsl_data.set_atom_name_principal("h");
  tsl_data.set_atom_name_non_principal("c");

  tsl_data.set_mat_no(607);
  tsl_data.set_mat_no_principal(125);
  tsl_data.set_mat_no_non_principal(600);
  tsl_data.set_mat_data_principal(1001);
  tsl_data.set_mat_data_non_principal(6000);
  tsl_data.set_atom_no_principal(6);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 59 (C in solid_ethanol (C2H6O))
  tsl_data.set_mat_name("C_in_Solid_Ethanol");
  tsl_data.set_atom_name_principal("c");
  tsl_data.set_atom_name_non_principal("h");

  tsl_data.set_mat_no(637);
  tsl_data.set_mat_no_principal(600);
  tsl_data.set_mat_no_non_principal(125);
  tsl_data.set_mat_data_principal(6000);
  tsl_data.set_mat_data_non_principal(1001);
  tsl_data.set_atom_no_principal(2);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 60 (O in solid_ethanol (C2H6O))
  tsl_data.set_mat_name("O_in_Solid_Ethanol");
  tsl_data.set_atom_name_principal("o");
  tsl_data.set_atom_name_non_principal("h");

  tsl_data.set_mat_no(667);
  tsl_data.set_mat_no_principal(825);
  tsl_data.set_mat_no_non_principal(125);
  tsl_data.set_mat_data_principal(8016);
  tsl_data.set_mat_data_non_principal(1001);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 61 (H in liquid_meta-xylene (C8H10))
  tsl_data.set_mat_name("H_in_Liquid_Meta_Xylene");
  tsl_data.set_atom_name_principal("h");
  tsl_data.set_atom_name_non_principal("c");

  tsl_data.set_mat_no(609);
  tsl_data.set_mat_no_principal(125);
  tsl_data.set_mat_no_non_principal(600);
  tsl_data.set_mat_data_principal(1001);
  tsl_data.set_mat_data_non_principal(6000);
  tsl_data.set_atom_no_principal(10);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 62 (C in liquid_meta-xylene (C8H10))
  tsl_data.set_mat_name("C_in_Liquid_Meta_Xylene");
  tsl_data.set_atom_name_principal("c");
  tsl_data.set_atom_name_non_principal("h");

  tsl_data.set_mat_no(639);
  tsl_data.set_mat_no_principal(600);
  tsl_data.set_mat_no_non_principal(125);
  tsl_data.set_mat_data_principal(6000);
  tsl_data.set_mat_data_non_principal(1001);
  tsl_data.set_atom_no_principal(8);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 63 (H in solid_meta-xylene (C8H10))
  tsl_data.set_mat_name("H_in_Solid_Meta_Xylene");
  tsl_data.set_atom_name_principal("h");
  tsl_data.set_atom_name_non_principal("c");

  tsl_data.set_mat_no(613);
  tsl_data.set_mat_no_principal(125);
  tsl_data.set_mat_no_non_principal(600);
  tsl_data.set_mat_data_principal(1001);
  tsl_data.set_mat_data_non_principal(6000);
  tsl_data.set_atom_no_principal(10);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 64 (C in solid_meta-xylene (C8H10))
  tsl_data.set_mat_name("C_in_Solid_Meta_Xylene");
  tsl_data.set_atom_name_principal("c");
  tsl_data.set_atom_name_non_principal("h");

  tsl_data.set_mat_no(643);
  tsl_data.set_mat_no_principal(600);
  tsl_data.set_mat_no_non_principal(125);
  tsl_data.set_mat_data_principal(6000);
  tsl_data.set_mat_data_non_principal(1001);
  tsl_data.set_atom_no_principal(8);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 65 (H in liquid_triphenylmethane (C19H16))
  tsl_data.set_mat_name("H_in_Liquid_Triphenylmethane");
  tsl_data.set_atom_name_principal("h");
  tsl_data.set_atom_name_non_principal("c");

  tsl_data.set_mat_no(614);
  tsl_data.set_mat_no_principal(125);
  tsl_data.set_mat_no_non_principal(600);
  tsl_data.set_mat_data_principal(1001);
  tsl_data.set_mat_data_non_principal(6000);
  tsl_data.set_atom_no_principal(16);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 66 (C in liquid_triphenylmethane (C19H16))
  tsl_data.set_mat_name("C_in_Liquid_Triphenylmethane");
  tsl_data.set_atom_name_principal("c");
  tsl_data.set_atom_name_non_principal("h");

  tsl_data.set_mat_no(644);
  tsl_data.set_mat_no_principal(600);
  tsl_data.set_mat_no_non_principal(125);
  tsl_data.set_mat_data_principal(6000);
  tsl_data.set_mat_data_non_principal(1001);
  tsl_data.set_atom_no_principal(19);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 67 (H in solid_triphenylmethane (C19H16))
  tsl_data.set_mat_name("H_in_Solid_Triphenylmethane");
  tsl_data.set_atom_name_principal("h");
  tsl_data.set_atom_name_non_principal("c");

  tsl_data.set_mat_no(615);
  tsl_data.set_mat_no_principal(125);
  tsl_data.set_mat_no_non_principal(600);
  tsl_data.set_mat_data_principal(1001);
  tsl_data.set_mat_data_non_principal(6000);
  tsl_data.set_atom_no_principal(16);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Case No. 68 (C in solid_triphenylmethane (C19H16))
  tsl_data.set_mat_name("C_in_Solid_Triphenylmethane");
  tsl_data.set_atom_name_principal("c");
  tsl_data.set_atom_name_non_principal("h");

  tsl_data.set_mat_no(645);
  tsl_data.set_mat_no_principal(600);
  tsl_data.set_mat_no_non_principal(125);
  tsl_data.set_mat_data_principal(6000);
  tsl_data.set_mat_data_non_principal(1001);
  tsl_data.set_atom_no_principal(19);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Zr in ZrC
  tsl_data.set_mat_name("Zr_in_Zrc");
  tsl_data.set_atom_name_principal("zr");
  tsl_data.set_atom_name_non_principal("c");

  tsl_data.set_mat_no(1001);
  tsl_data.set_mat_no_principal(4000);
  tsl_data.set_mat_no_non_principal(600);
  tsl_data.set_mat_data_principal(40000);
  tsl_data.set_mat_data_non_principal(6000);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //C in ZrC
  tsl_data.set_mat_name("C_in_Zrc");
  tsl_data.set_atom_name_principal("c");
  tsl_data.set_atom_name_non_principal("zr");

  tsl_data.set_mat_no(1002);
  tsl_data.set_mat_no_principal(600);
  tsl_data.set_mat_no_non_principal(4000);
  tsl_data.set_mat_data_principal(6000);
  tsl_data.set_mat_data_non_principal(40000);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //C in Teflon (CF2)
  tsl_data.set_mat_name("C_in_CF2");
  tsl_data.set_atom_name_principal("c");
  tsl_data.set_atom_name_non_principal("f");

  tsl_data.set_mat_no(1051);
  tsl_data.set_mat_no_principal(600);
  tsl_data.set_mat_no_non_principal(925);
  tsl_data.set_mat_data_principal(6000);
  tsl_data.set_mat_data_non_principal(9019);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //F in Teflon (CF2)
  tsl_data.set_mat_name("F_in_CF2");
  tsl_data.set_atom_name_principal("c");
  tsl_data.set_atom_name_non_principal("f");

  tsl_data.set_mat_no(1052);
  tsl_data.set_mat_no_principal(925);
  tsl_data.set_mat_no_non_principal(600);
  tsl_data.set_mat_data_principal(9019);
  tsl_data.set_mat_data_non_principal(6000);
  tsl_data.set_atom_no_principal(2);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Ca in CaH2
  tsl_data.set_mat_name("Ca_in_CaH2");
  tsl_data.set_atom_name_principal("ca");
  tsl_data.set_atom_name_non_principal("h");

  tsl_data.set_mat_no(3011);
  tsl_data.set_mat_no_principal(2025);
  tsl_data.set_mat_no_non_principal(125);
  tsl_data.set_mat_data_principal(20040);
  tsl_data.set_mat_data_non_principal(1001);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //H1 in CaH2
  tsl_data.set_mat_name("H_in_CaH2");
  tsl_data.set_atom_name_principal("h");
  tsl_data.set_atom_name_non_principal("ca");

  tsl_data.set_mat_no(3013);
  tsl_data.set_mat_no_principal(125);
  tsl_data.set_mat_no_non_principal(2025);
  tsl_data.set_mat_data_principal(1001);
  tsl_data.set_mat_data_non_principal(20040);
  tsl_data.set_atom_no_principal(2);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //H2 in CaH2
  tsl_data.set_mat_name("H2_in_CaH2");
  tsl_data.set_atom_name_principal("h");
  tsl_data.set_atom_name_non_principal("ca");

  tsl_data.set_mat_no(3014);
  tsl_data.set_mat_no_principal(125);
  tsl_data.set_mat_no_non_principal(2025);
  tsl_data.set_mat_data_principal(1001);
  tsl_data.set_mat_data_non_principal(20040);
  tsl_data.set_atom_no_principal(2);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Li-7 in Lithium hydride (LiH)
  tsl_data.set_mat_name("Li_in_7LiH");
  tsl_data.set_atom_name_principal("li");
  tsl_data.set_atom_name_non_principal("h");

  tsl_data.set_mat_no(3031);
  tsl_data.set_mat_no_principal(328);
  tsl_data.set_mat_no_non_principal(125);
  tsl_data.set_mat_data_principal(3007);
  tsl_data.set_mat_data_non_principal(1001);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //H in Lithium hydride (LiH)
  tsl_data.set_mat_name("H_in_7LiH");
  tsl_data.set_atom_name_principal("h");
  tsl_data.set_atom_name_non_principal("li");

  tsl_data.set_mat_no(3032);
  tsl_data.set_mat_no_principal(125);
  tsl_data.set_mat_no_non_principal(328);
  tsl_data.set_mat_data_principal(1001);
  tsl_data.set_mat_data_non_principal(3007);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Li-7 in Lithium hydride (LiD)
  tsl_data.set_mat_name("Li_in_7LiD");
  tsl_data.set_atom_name_principal("li");
  tsl_data.set_atom_name_non_principal("d");

  tsl_data.set_mat_no(3034);
  tsl_data.set_mat_no_principal(328);
  tsl_data.set_mat_no_non_principal(128);
  tsl_data.set_mat_data_principal(3007);
  tsl_data.set_mat_data_non_principal(1002);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //D in Lithium hydride (LiD)
  tsl_data.set_mat_name("D_in_7LiD");
  tsl_data.set_atom_name_principal("d");
  tsl_data.set_atom_name_non_principal("li");

  tsl_data.set_mat_no(3035);
  tsl_data.set_mat_no_principal(128);
  tsl_data.set_mat_no_non_principal(328);
  tsl_data.set_mat_data_principal(1002);
  tsl_data.set_mat_data_non_principal(3007);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //F in HF
  tsl_data.set_mat_name("F_in_HF");
  tsl_data.set_atom_name_principal("f");
  tsl_data.set_atom_name_non_principal("h");

  tsl_data.set_mat_no(3047);
  tsl_data.set_mat_no_principal(925);
  tsl_data.set_mat_no_non_principal(125);
  tsl_data.set_mat_data_principal(9019);
  tsl_data.set_mat_data_non_principal(1001);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //H in HF
  tsl_data.set_mat_name("H_in_HF");
  tsl_data.set_atom_name_principal("h");
  tsl_data.set_atom_name_non_principal("f");

  tsl_data.set_mat_no(3048);
  tsl_data.set_mat_no_principal(125);
  tsl_data.set_mat_no_non_principal(925);
  tsl_data.set_mat_data_principal(1001);
  tsl_data.set_mat_data_non_principal(9019);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Al in Al2O3
  tsl_data.set_mat_name("Al_in_Al2O3");
  tsl_data.set_atom_name_principal("al");
  tsl_data.set_atom_name_non_principal("o");

  tsl_data.set_mat_no(3052);
  tsl_data.set_mat_no_principal(1325);
  tsl_data.set_mat_no_non_principal(825);
  tsl_data.set_mat_data_principal(13027);
  tsl_data.set_mat_data_non_principal(8016);
  tsl_data.set_atom_no_principal(2);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //O in Al2O3 for JEFF-3.3 (Same MAT number as U in UO2)
  tsl_data.set_mat_name("O_in_Al2O3");
  tsl_data.set_atom_name_principal("o");
  tsl_data.set_atom_name_non_principal("al");

  tsl_data.set_mat_no(48);
  tsl_data.set_mat_no_principal(825);
  tsl_data.set_mat_no_non_principal(1325);
  tsl_data.set_mat_data_principal(8016);
  tsl_data.set_mat_data_non_principal(13027);
  tsl_data.set_atom_no_principal(3);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //O in Al2O3
  tsl_data.set_mat_name("O_in_Al2O3");
  tsl_data.set_atom_name_principal("o");
  tsl_data.set_atom_name_non_principal("al");

  tsl_data.set_mat_no(3053);
  tsl_data.set_mat_no_principal(825);
  tsl_data.set_mat_no_non_principal(1325);
  tsl_data.set_mat_data_principal(8016);
  tsl_data.set_mat_data_non_principal(13027);
  tsl_data.set_atom_no_principal(3);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //F in BeF2
  tsl_data.set_mat_name("F_in_BeF2");
  tsl_data.set_atom_name_principal("f");
  tsl_data.set_atom_name_non_principal("be");

  tsl_data.set_mat_no(3136);
  tsl_data.set_mat_no_principal(925);
  tsl_data.set_mat_no_non_principal(425);
  tsl_data.set_mat_data_principal(9019);
  tsl_data.set_mat_data_non_principal(4009);
  tsl_data.set_atom_no_principal(2);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Be in BeF2
  tsl_data.set_mat_name("Be_in_BeF2");
  tsl_data.set_atom_name_principal("be");
  tsl_data.set_atom_name_non_principal("f");

  tsl_data.set_mat_no(3137);
  tsl_data.set_mat_no_principal(425);
  tsl_data.set_mat_no_non_principal(925);
  tsl_data.set_mat_data_principal(4009);
  tsl_data.set_mat_data_non_principal(9019);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Mg in MgF2
  tsl_data.set_mat_name("Mg_in_MgF2");
  tsl_data.set_atom_name_principal("mg");
  tsl_data.set_atom_name_non_principal("f");

  tsl_data.set_mat_no(3141);
  tsl_data.set_mat_no_principal(1200);
  tsl_data.set_mat_no_non_principal(925);
  tsl_data.set_mat_data_principal(12000);
  tsl_data.set_mat_data_non_principal(9019);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //F in MgF2
  tsl_data.set_mat_name("F_in_MgF2");
  tsl_data.set_atom_name_principal("f");
  tsl_data.set_atom_name_non_principal("mg");

  tsl_data.set_mat_no(3142);
  tsl_data.set_mat_no_principal(925);
  tsl_data.set_mat_no_non_principal(1200);
  tsl_data.set_mat_data_principal(9019);
  tsl_data.set_mat_data_non_principal(12000);
  tsl_data.set_atom_no_principal(2);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Mg in MgO
  tsl_data.set_mat_name("Mg_in_MgO");
  tsl_data.set_atom_name_principal("mg");
  tsl_data.set_atom_name_non_principal("o");

  tsl_data.set_mat_no(3146);
  tsl_data.set_mat_no_principal(1200);
  tsl_data.set_mat_no_non_principal(825);
  tsl_data.set_mat_data_principal(12000);
  tsl_data.set_mat_data_non_principal(8016);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //O in MgO
  tsl_data.set_mat_name("O_in_MgO");
  tsl_data.set_atom_name_principal("o");
  tsl_data.set_atom_name_non_principal("mg");

  tsl_data.set_mat_no(3147);
  tsl_data.set_mat_no_principal(825);
  tsl_data.set_mat_no_non_principal(1200);
  tsl_data.set_mat_data_principal(8016);
  tsl_data.set_mat_data_non_principal(12000);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //F in FLiBe
  tsl_data.set_mat_name("F_in_FLiBe");
  tsl_data.set_atom_name_principal("f");
  tsl_data.set_atom_name_non_principal("be");

  tsl_data.set_mat_no(4001);
  tsl_data.set_mat_no_principal(925);
  tsl_data.set_mat_no_non_principal(425);
  tsl_data.set_mat_data_principal(9019);
  tsl_data.set_mat_data_non_principal(4009);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Be in FLiBe
  tsl_data.set_mat_name("Be_in_FLiBe");
  tsl_data.set_atom_name_principal("be");
  tsl_data.set_atom_name_non_principal("f");

  tsl_data.set_mat_no(4002);
  tsl_data.set_mat_no_principal(425);
  tsl_data.set_mat_no_non_principal(925);
  tsl_data.set_mat_data_principal(4009);
  tsl_data.set_mat_data_non_principal(9019);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Li in FLiBe
  tsl_data.set_mat_name("Li_in_FLiBe");
  tsl_data.set_atom_name_principal("li");
  tsl_data.set_atom_name_non_principal("f");

  tsl_data.set_mat_no(4003);
  tsl_data.set_mat_no_principal(328);
  tsl_data.set_mat_no_non_principal(925);
  tsl_data.set_mat_data_principal(3007);
  tsl_data.set_mat_data_non_principal(9019);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Pu in PuO2 (100% Pu239)
  tsl_data.set_mat_name("Pu_in_PuO2");
  tsl_data.set_atom_name_principal("pu");
  tsl_data.set_atom_name_non_principal("o");

  tsl_data.set_mat_no(7200);
  tsl_data.set_mat_no_principal(9437);
  tsl_data.set_mat_no_non_principal(825);
  tsl_data.set_mat_data_principal(94239);
  tsl_data.set_mat_data_non_principal(8016);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //O in PuO2 (100% Pu239)
  tsl_data.set_mat_name("O_in_PuO2");
  tsl_data.set_atom_name_principal("o");
  tsl_data.set_atom_name_non_principal("pu");

  tsl_data.set_mat_no(7250);
  tsl_data.set_mat_no_principal(825);
  tsl_data.set_mat_no_non_principal(9437);
  tsl_data.set_mat_data_principal(8016);
  tsl_data.set_mat_data_non_principal(94239);
  tsl_data.set_atom_no_principal(2);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //U-metal (Natural U / 0.7204% enriched U)
  tsl_data.set_mat_name("U");
  tsl_data.set_atom_name_principal("u");
  tsl_data.set_atom_name_non_principal("");

  tsl_data.set_mat_no(8000);
  tsl_data.set_mat_no_principal(9237);
  tsl_data.set_mat_no_non_principal(0);
  tsl_data.set_mat_data_principal(92238);
  tsl_data.set_mat_data_non_principal(0);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //U-metal (5% enriched U)
  tsl_data.set_mat_name("U");
  tsl_data.set_atom_name_principal("u");
  tsl_data.set_atom_name_non_principal("");

  tsl_data.set_mat_no(8005);
  tsl_data.set_mat_no_principal(9237);
  tsl_data.set_mat_no_non_principal(0);
  tsl_data.set_mat_data_principal(92238);
  tsl_data.set_mat_data_non_principal(0);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //U-metal (10% enriched U)
  tsl_data.set_mat_name("U");
  tsl_data.set_atom_name_principal("u");
  tsl_data.set_atom_name_non_principal("");

  tsl_data.set_mat_no(8010);
  tsl_data.set_mat_no_principal(9237);
  tsl_data.set_mat_no_non_principal(0);
  tsl_data.set_mat_data_principal(92238);
  tsl_data.set_mat_data_non_principal(0);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //U-metal (100% enriched U)
  tsl_data.set_mat_name("U");
  tsl_data.set_atom_name_principal("u");
  tsl_data.set_atom_name_non_principal("");

  tsl_data.set_mat_no(8047);
  tsl_data.set_mat_no_principal(9228);
  tsl_data.set_mat_no_non_principal(0);
  tsl_data.set_mat_data_principal(92235);
  tsl_data.set_mat_data_non_principal(0);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //U-metal (HALEU / 19.75% enriched U)
  tsl_data.set_mat_name("U");
  tsl_data.set_atom_name_principal("u");
  tsl_data.set_atom_name_non_principal("");

  tsl_data.set_mat_no(8048);
  tsl_data.set_mat_no_principal(9237);
  tsl_data.set_mat_no_non_principal(0);
  tsl_data.set_mat_data_principal(92238);
  tsl_data.set_mat_data_non_principal(0);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //U-metal (HEU / 93% enriched U)
  tsl_data.set_mat_name("U");
  tsl_data.set_atom_name_principal("u");
  tsl_data.set_atom_name_non_principal("");

  tsl_data.set_mat_no(8099);
  tsl_data.set_mat_no_principal(9228);
  tsl_data.set_mat_no_non_principal(0);
  tsl_data.set_mat_data_principal(92235);
  tsl_data.set_mat_data_non_principal(0);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //U in UC (Natural U / 0.7204% enriched U)
  tsl_data.set_mat_name("U_in_UC");
  tsl_data.set_atom_name_principal("u");
  tsl_data.set_atom_name_non_principal("c");

  tsl_data.set_mat_no(76);
  tsl_data.set_mat_no_principal(9237);
  tsl_data.set_mat_no_non_principal(600);
  tsl_data.set_mat_data_principal(92238);
  tsl_data.set_mat_data_non_principal(6000);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //U in UC (5% enriched U)
  tsl_data.set_mat_name("U_in_UC");
  tsl_data.set_atom_name_principal("u");
  tsl_data.set_atom_name_non_principal("c");

  tsl_data.set_mat_no(8105);
  tsl_data.set_mat_no_principal(9237);
  tsl_data.set_mat_no_non_principal(600);
  tsl_data.set_mat_data_principal(92238);
  tsl_data.set_mat_data_non_principal(6000);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //U in UC (10% enriched U)
  tsl_data.set_mat_name("U_in_UC");
  tsl_data.set_atom_name_principal("u");
  tsl_data.set_atom_name_non_principal("c");

  tsl_data.set_mat_no(8110);
  tsl_data.set_mat_no_principal(9237);
  tsl_data.set_mat_no_non_principal(600);
  tsl_data.set_mat_data_principal(92238);
  tsl_data.set_mat_data_non_principal(6000);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //U in UC (100% enriched U)
  tsl_data.set_mat_name("U_in_UC");
  tsl_data.set_atom_name_principal("u");
  tsl_data.set_atom_name_non_principal("c");

  tsl_data.set_mat_no(8147);
  tsl_data.set_mat_no_principal(9228);
  tsl_data.set_mat_no_non_principal(600);
  tsl_data.set_mat_data_principal(92235);
  tsl_data.set_mat_data_non_principal(6000);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //U in UC (HALEU / 19.75% enriched U)
  tsl_data.set_mat_name("U_in_UC");
  tsl_data.set_atom_name_principal("u");
  tsl_data.set_atom_name_non_principal("c");

  tsl_data.set_mat_no(8148);
  tsl_data.set_mat_no_principal(9237);
  tsl_data.set_mat_no_non_principal(600);
  tsl_data.set_mat_data_principal(92238);
  tsl_data.set_mat_data_non_principal(6000);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //U in UC (HEU / 93% enriched U)
  tsl_data.set_mat_name("U_in_UC");
  tsl_data.set_atom_name_principal("u");
  tsl_data.set_atom_name_non_principal("c");

  tsl_data.set_mat_no(8149);
  tsl_data.set_mat_no_principal(9228);
  tsl_data.set_mat_no_non_principal(600);
  tsl_data.set_mat_data_principal(92235);
  tsl_data.set_mat_data_non_principal(6000);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //C in UC (natural U)
  tsl_data.set_mat_name("C_in_UC");
  tsl_data.set_atom_name_principal("c");
  tsl_data.set_atom_name_non_principal("u");

  tsl_data.set_mat_no(8150);
  tsl_data.set_mat_no_principal(600);
  tsl_data.set_mat_no_non_principal(9237);
  tsl_data.set_mat_data_principal(6000);
  tsl_data.set_mat_data_non_principal(92238);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //C in UC (5% enriched U)
  tsl_data.set_mat_name("C_in_UC");
  tsl_data.set_atom_name_principal("c");
  tsl_data.set_atom_name_non_principal("u");

  tsl_data.set_mat_no(8155);
  tsl_data.set_mat_no_principal(600);
  tsl_data.set_mat_no_non_principal(9237);
  tsl_data.set_mat_data_principal(6000);
  tsl_data.set_mat_data_non_principal(92238);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //C in UC (10% enriched U)
  tsl_data.set_mat_name("C_in_UC");
  tsl_data.set_atom_name_principal("c");
  tsl_data.set_atom_name_non_principal("u");

  tsl_data.set_mat_no(8160);
  tsl_data.set_mat_no_principal(600);
  tsl_data.set_mat_no_non_principal(9237);
  tsl_data.set_mat_data_principal(6000);
  tsl_data.set_mat_data_non_principal(92238);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //C in UC (100% enriched U)
  tsl_data.set_mat_name("C_in_UC");
  tsl_data.set_atom_name_principal("c");
  tsl_data.set_atom_name_non_principal("u");

  tsl_data.set_mat_no(8197);
  tsl_data.set_mat_no_principal(600);
  tsl_data.set_mat_no_non_principal(9228);
  tsl_data.set_mat_data_principal(6000);
  tsl_data.set_mat_data_non_principal(92235);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //C in UC (HALEU / 19.75% enriched U)
  tsl_data.set_mat_name("C_in_UC");
  tsl_data.set_atom_name_principal("c");
  tsl_data.set_atom_name_non_principal("u");

  tsl_data.set_mat_no(8198);
  tsl_data.set_mat_no_principal(600);
  tsl_data.set_mat_no_non_principal(9237);
  tsl_data.set_mat_data_principal(6000);
  tsl_data.set_mat_data_non_principal(92238);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //C in UC (HEU / 93% enriched U)
  tsl_data.set_mat_name("C_in_UC");
  tsl_data.set_atom_name_principal("c");
  tsl_data.set_atom_name_non_principal("u");

  tsl_data.set_mat_no(8199);
  tsl_data.set_mat_no_principal(600);
  tsl_data.set_mat_no_non_principal(9228);
  tsl_data.set_mat_data_principal(6000);
  tsl_data.set_mat_data_non_principal(92235);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //U in UN (5% enriched U)
  tsl_data.set_mat_name("U_in_UN");
  tsl_data.set_atom_name_principal("n");
  tsl_data.set_atom_name_non_principal("u");

  tsl_data.set_mat_no(8305);
  tsl_data.set_mat_no_principal(9237);
  tsl_data.set_mat_no_non_principal(725);
  tsl_data.set_mat_data_principal(92238);
  tsl_data.set_mat_data_non_principal(7014);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //U in UN (10% enriched U)
  tsl_data.set_mat_name("U_in_UN");
  tsl_data.set_atom_name_principal("n");
  tsl_data.set_atom_name_non_principal("u");

  tsl_data.set_mat_no(8310);
  tsl_data.set_mat_no_principal(9237);
  tsl_data.set_mat_no_non_principal(725);
  tsl_data.set_mat_data_principal(92238);
  tsl_data.set_mat_data_non_principal(7014);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //U in UN (100% enriched U)
  tsl_data.set_mat_name("U_in_UN");
  tsl_data.set_atom_name_principal("n");
  tsl_data.set_atom_name_non_principal("u");

  tsl_data.set_mat_no(8347);
  tsl_data.set_mat_no_principal(9228);
  tsl_data.set_mat_no_non_principal(725);
  tsl_data.set_mat_data_principal(92235);
  tsl_data.set_mat_data_non_principal(7014);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //U in UN (HALEU / 19.75% enriched U)
  tsl_data.set_mat_name("U_in_UN");
  tsl_data.set_atom_name_principal("n");
  tsl_data.set_atom_name_non_principal("u");

  tsl_data.set_mat_no(8348);
  tsl_data.set_mat_no_principal(9237);
  tsl_data.set_mat_no_non_principal(725);
  tsl_data.set_mat_data_principal(92238);
  tsl_data.set_mat_data_non_principal(7014);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //U in UN (HEU / 93% enriched U)
  tsl_data.set_mat_name("U_in_UN");
  tsl_data.set_atom_name_principal("n");
  tsl_data.set_atom_name_non_principal("u");

  tsl_data.set_mat_no(8349);
  tsl_data.set_mat_no_principal(9228);
  tsl_data.set_mat_no_non_principal(725);
  tsl_data.set_mat_data_principal(92235);
  tsl_data.set_mat_data_non_principal(7014);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //N in UN (5% enriched U)
  tsl_data.set_mat_name("N_in_UN");
  tsl_data.set_atom_name_principal("n");
  tsl_data.set_atom_name_non_principal("u");

  tsl_data.set_mat_no(8355);
  tsl_data.set_mat_no_principal(725);
  tsl_data.set_mat_no_non_principal(9237);
  tsl_data.set_mat_data_principal(7014);
  tsl_data.set_mat_data_non_principal(92238);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //N in UN (10% enriched U)
  tsl_data.set_mat_name("N_in_UN");
  tsl_data.set_atom_name_principal("n");
  tsl_data.set_atom_name_non_principal("u");

  tsl_data.set_mat_no(8360);
  tsl_data.set_mat_no_principal(725);
  tsl_data.set_mat_no_non_principal(9237);
  tsl_data.set_mat_data_principal(7014);
  tsl_data.set_mat_data_non_principal(92238);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //N in UN (100% enriched U)
  tsl_data.set_mat_name("N_in_UN");
  tsl_data.set_atom_name_principal("n");
  tsl_data.set_atom_name_non_principal("u");

  tsl_data.set_mat_no(8397);
  tsl_data.set_mat_no_principal(725);
  tsl_data.set_mat_no_non_principal(9228);
  tsl_data.set_mat_data_principal(7014);
  tsl_data.set_mat_data_non_principal(92235);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //N in UN (HALEU / 19.75% enriched U)
  tsl_data.set_mat_name("N_in_UN");
  tsl_data.set_atom_name_principal("n");
  tsl_data.set_atom_name_non_principal("u");

  tsl_data.set_mat_no(8398);
  tsl_data.set_mat_no_principal(725);
  tsl_data.set_mat_no_non_principal(9237);
  tsl_data.set_mat_data_principal(7014);
  tsl_data.set_mat_data_non_principal(92238);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //N in UN (HEU / 93% enriched U)
  tsl_data.set_mat_name("N_in_UN");
  tsl_data.set_atom_name_principal("n");
  tsl_data.set_atom_name_non_principal("u");

  tsl_data.set_mat_no(8399);
  tsl_data.set_mat_no_principal(725);
  tsl_data.set_mat_no_non_principal(9228);
  tsl_data.set_mat_data_principal(7014);
  tsl_data.set_mat_data_non_principal(92235);
  tsl_data.set_atom_no_principal(1);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //H in UH3 
  tsl_data.set_mat_name("H_in_UH3");
  tsl_data.set_atom_name_principal("h");
  tsl_data.set_atom_name_non_principal("u");

  tsl_data.set_mat_no(8450);
  tsl_data.set_mat_no_principal(125);
  tsl_data.set_mat_no_non_principal(9237);
  tsl_data.set_mat_data_principal(1001);
  tsl_data.set_mat_data_non_principal(92238);
  tsl_data.set_atom_no_principal(3);
  tsl_data.set_atom_no_mix(1);

  thermal_scat_data.push_back(tsl_data);
  tsl_data.clear();

  //Calc data_no
  data_no = static_cast<int>(thermal_scat_data.size());
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<ThermalScatterMatData>  ThermalScatterMatList::get_thermal_scat_data_all()
{
  return thermal_scat_data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<ThermalScatterMatData> ThermalScatterMatList::get_thermal_scat_data(string mat_name)
{
  transform(mat_name.begin(), mat_name.end(), mat_name.begin(), ::tolower);

  vector<ThermalScatterMatData> tsl_vec;
  tsl_vec.clear();

  for(int i=0; i<data_no; i++)
  {
    if( mat_name == thermal_scat_data[i].get_mat_name() )
    {
      tsl_vec.push_back(thermal_scat_data[i]);
    }
  }

  return tsl_vec;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<ThermalScatterMatData> ThermalScatterMatList::get_thermal_scat_data(int mat_no)
{
  vector<ThermalScatterMatData> tsl_vec;
  tsl_vec.clear();

  for(int i=0; i<data_no; i++)
  {
    if( mat_no == thermal_scat_data[i].get_mat_no() )
    {
      tsl_vec.push_back(thermal_scat_data[i]);
    }
  }

  return tsl_vec;
}

