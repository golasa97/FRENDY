#ifndef NUCLEAR_DATA_MODIFIER_H
#define NUCLEAR_DATA_MODIFIER_H

#include "CommonUtils/ErrorManager.hpp"
#include "NuclearDataUtils/NuclearDataObject.hpp"

namespace frendy
{
  class NuclearDataModifier
  {
    private:
      frendy::ErrorManager  err_obj;

    public:
      //constructor
      NuclearDataModifier(void);

      //destructor
      virtual ~NuclearDataModifier(void);

      void remove_specified_reaction_type_data
             (frendy::NuclearDataObject& nucl_data_obj, Integer react_type_no);

      void change_specified_reaction_type_data
             (frendy::NuclearDataObject& nucl_data_obj_ori,
              frendy::NuclearDataObject& nucl_data_obj_add, Integer react_type_no);

      void add_specified_reaction_type_data
             (frendy::NuclearDataObject& nucl_data_obj_ori,
              frendy::NuclearDataObject& nucl_data_obj_add, Integer react_type_no);
      void add_specified_reaction_type_data_react
             (frendy::NuclearReactionDataContainer& react_data_obj_ori,
              frendy::NuclearReactionDataContainer& react_data_obj_add, Integer react_type_no);
      void add_specified_reaction_type_data_cov_react
             (frendy::CovarianceReactionDataContainer& cov_react_data_obj_ori,
              frendy::CovarianceReactionDataContainer& cov_react_data_obj_add, Integer react_type_no);
  };
}

#endif //NUCLEAR_DATA_MODIFIER_H
