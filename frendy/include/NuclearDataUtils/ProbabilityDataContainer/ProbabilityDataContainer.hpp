#ifndef PROBABILITY_DATA_CONTAINER_H
#define PROBABILITY_DATA_CONTAINER_H

#include "NuclearDataUtils/ProbabilityDataContainer/ProbabilityTableDataContainer.hpp"

namespace frendy
{
  class ProbabilityDataContainer
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

      Integer unreso_int_data;
      Integer self_shielding_flg;
      Integer comp_flg_inela; //competition flag (inelastic)
      Integer comp_flg_abs;   //competition flag (absorption)
      Integer comp_flg;       //competition flag

      int prob_table_ene_no;
      vector<frendy::ProbabilityTableDataContainer> prob_table_data_obj;

    public:
      //constructor
      ProbabilityDataContainer(void);

      //destructor
      virtual ~ProbabilityDataContainer(void);

      void clear();
      void clear_prob_table_data_obj(vector<frendy::ProbabilityTableDataContainer>& data_obj);

      //Getter
      Integer get_unreso_int_data();
      Integer get_self_shielding_flg();
      Integer get_comp_flg_inela();
      Integer get_comp_flg_abs();
      Integer get_comp_flg();
      int     get_prob_table_ene_no();
      vector<frendy::ProbabilityTableDataContainer> get_prob_table_data_obj();
      frendy::ProbabilityTableDataContainer get_prob_table_data_obj(Integer ene_no);

      //Setter
      void set_unreso_int_data(Integer int_val);
      void set_self_shielding_flg(Integer int_val);
      void set_comp_flg_inela(Integer int_val);
      void set_comp_flg_abs(Integer int_val);
      void set_comp_flg(Integer int_val);
      void set_prob_table_ene_no(int ene_no);
      void set_prob_table_data_obj(vector<frendy::ProbabilityTableDataContainer> data_obj);
      void set_prob_table_data_obj(int ene_no, frendy::ProbabilityTableDataContainer data_obj);
  };
}

#endif //PROBABILITY_DATA_CONTAINER_H
