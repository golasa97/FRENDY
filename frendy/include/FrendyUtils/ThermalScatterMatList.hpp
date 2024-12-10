#ifndef THERMAL_SCAT_MAT_LIST_H
#define THERMAL_SCAT_MAT_LIST_H

#include "Config/FrendyTypes.hpp"

namespace frendy
{
  class ThermalScatterMatData
  {
    private:
      string mat_name;
      string atom_name_principal;
      string atom_name_non_principal;

      //atom_no_principal is only used when B(4)=M0 of MF=7/MT=4 is less than or equal to 0.
      //If B(4) > 0, atom_no_principal is overwritten by B(4).
      //See follwing classes:
      //(1) read_principal_atom_no(int i) function in NuclearDataProcessorByFrendyInput class
      //    (NuclearDataProcessor/NuclearDataProcessorByFrendyInput.cpp)
      //(2) get_atom_no_principal_tsl(int ele_no) function in MakeInputFromFRENDYtoNJOY class
      //    (NuclearDataProcessor/MakeInputFromFRENDYtoNJOY.cpp)

      int mat_no,                                     //Mat (TSL data)
          mat_no_principal,   mat_no_non_principal,   //MAT (nucleus)
          mat_data_principal, mat_data_non_principal, //ZA
          atom_no_principal,  atom_no_mix;            //for ThermalScatter

      int     mt_no;
      string  tsl_name;

    public:
      //constructor
      ThermalScatterMatData(void);

      //destructor
      virtual ~ThermalScatterMatData(void);

      void clear();

      //Setter
      void set_mat_name(string str_data);
      void set_atom_name_principal(string str_data);
      void set_atom_name_non_principal(string str_data);

      void set_mat_no(int int_data);
      void set_mat_no_principal(int int_data);
      void set_mat_no_non_principal(int int_data);
      void set_mat_data_principal(int int_data);
      void set_mat_data_non_principal(int int_data);
      void set_atom_no_principal(int int_data);
      void set_atom_no_mix(int int_data);

      void set_mt_no(int int_data);
      void set_tsl_name(string str_data);

      //Getter
      string get_mat_name();
      string get_atom_name_principal();
      string get_atom_name_non_principal();

      int    get_mat_no();
      int    get_mat_no_principal();
      int    get_mat_no_non_principal();
      int    get_mat_data_principal();
      int    get_mat_data_non_principal();
      int    get_proton_no_principal();
      int    get_proton_no_non_principal();
      int    get_mass_no_principal();
      int    get_mass_no_non_principal();
      int    get_atom_no_principal();
      int    get_atom_no_mix();

      int    get_mt_no();
      string get_tsl_name();
  };

  class ThermalScatterMatList
  {
    private:
       int data_no;
       vector<frendy::ThermalScatterMatData> thermal_scat_data;

       void set_thermal_scat_data();

    public:
      //constructor
      ThermalScatterMatList(void);

      //destructor
      virtual ~ThermalScatterMatList(void);

      void clear();

      vector<frendy::ThermalScatterMatData> get_thermal_scat_data_all();

      vector<frendy::ThermalScatterMatData> get_thermal_scat_data(string mat_name);
      vector<frendy::ThermalScatterMatData> get_thermal_scat_data(int    mat_no);
  };
}

#endif //THERMAL_SCAT_MAT_LIST_H
