#ifndef CROSS_SECTION_DATA_CONTAINER_H
#define CROSS_SECTION_DATA_CONTAINER_H

#include "CommonUtils/ErrorManager.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class CrossSectionDataContainer
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

      Integer         reaction_type;
      Real            q_value_mass;
      Real            q_value;
      Integer         reaction_flg;
      vector<Integer> xs_int_data;
      vector<Integer> xs_range_data;
      vector<Real>    xs_ene_data;
      vector<Real>    xs_data;

    public:
      //constructor
      CrossSectionDataContainer(void);

      //destructor
      virtual ~CrossSectionDataContainer(void);

      void clear();

      //Getter
      Integer         get_reaction_type();
      Real            get_q_value_mass();
      Real            get_q_value();
      Integer         get_reaction_flg();
      vector<Integer> get_xs_int_data();
      vector<Integer> get_xs_range_data();
      vector<Real>    get_xs_ene_data();
      vector<Real>    get_xs_data();

      //Setter
      void set_reaction_type( Integer int_data );
      void set_q_value_mass( Real real_data );
      void set_q_value( Real real_data );
      void set_reaction_flg( Integer int_data );
      void set_xs_int_data( vector<Integer> int_vec );
      void set_xs_range_data( vector<Integer> int_vec );
      void set_xs_ene_data( vector<Real> real_vec );
      void set_xs_data( vector<Real> real_vec );
  };
}

#endif //CROSS_SECTION_DATA_CONTAINER_H
