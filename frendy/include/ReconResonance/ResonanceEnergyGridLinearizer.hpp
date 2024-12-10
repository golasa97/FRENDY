#ifndef RESONANCE_ENERGY_GRID_LINEARIZER_H
#define RESONANCE_ENERGY_GRID_LINEARIZER_H

#include "Config/CommonData.hpp"
#include "CommonUtils/DigitAdjuster.hpp"
#include "CommonUtils/TabAdjuster.hpp"
#include "NuclearDataUtils/NuclearDataObject.hpp"

namespace frendy
{
  class ResonanceEnergyGridLinearizer
  {
    private:
      frendy::ErrorManager   err_obj;
      frendy::VectorClearer  clr_obj;
      frendy::DigitAdjuster  digit_obj;
      frendy::TabAdjuster    ta_obj;

      frendy::NuclearDataObject      nucl_data_obj;
      frendy::ResonanceDataContainer reso_data_obj;

      vector<vector<vector<Real8> > > ene_array;
      vector<Real8>                   specified_grid;

      Integer                  reso_flg;
      vector<vector<Integer> > reso_region_flg, xs_formula_flg;

      int         nis; //Number of isotpes in the material.
      vector<int> ner; //Number of resonance energy range for each isotope.

      void add_resonance_grid();
      void add_limit_energy_grid();

      void add_additional_energy_grid(vector<Real8>& ene_data);
      void add_user_specified_energy_grid(vector<Real8>& ene_data, vector<Real8>& add_grid);
      void add_case_own_additional_energy_grid(int& i, int& j, vector<Real8>& ene_data);
      void add_additional_energy_grid_reso_general(int& i, int& j, vector<Real8>& ene_data);
      void add_additional_energy_grid_reso_adler(int& i, int& j, vector<Real8>& ene_data);
      void add_additional_energy_grid_unreso_a(vector<Real8>& ene_data);
      void add_additional_energy_grid_unreso_b_c(int& i, int& j, vector<Real8>& ene_data, Integer& lrf_val);

      void delete_el_and_eh(int& i, int& j, vector<Real8>& base_grid);

    public:
      //constructor
      ResonanceEnergyGridLinearizer(void);

      //destructor
      virtual ~ResonanceEnergyGridLinearizer(void);

      void clear();

      void set_user_specified_grid(vector<Real8> real_vec);
      void set_nucl_data_obj(frendy::NuclearDataObject& data_obj);

      vector<vector<vector<Real8> > > get_resonance_grid();
      vector<Real8>                   get_user_specified_grid();

      frendy::NuclearDataObject      get_nucl_data_obj();
      frendy::ResonanceDataContainer get_reso_data_obj();
  };
}

#endif // RESONANCE_ENERGY_GRID_LINEARIZER_H
