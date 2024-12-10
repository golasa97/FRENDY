#ifndef NUCLEAR_DATA_OBJECT_H
#define NUCLEAR_DATA_OBJECT_H

#include "CommonUtils/ErrorManager.hpp"
#include "CommonUtils/VectorClearer.hpp"
#include "NuclearDataUtils/NuclearDataContainer/GeneralDataContainer.hpp"
#include "NuclearDataUtils/NuclearDataContainer/FissionDataContainer.hpp"
#include "NuclearDataUtils/NuclearDataContainer/ResonanceDataContainer.hpp"
#include "NuclearDataUtils/NuclearDataContainer/ThermalScatterDataContainer.hpp"
#include "NuclearDataUtils/NuclearDataContainer/NuclearReactionDataContainer.hpp"
#include "NuclearDataUtils/CovarianceDataContainer/CovarianceGeneralDataContainer.hpp"
#include "NuclearDataUtils/CovarianceDataContainer/CovarianceResonanceDataContainer.hpp"
#include "NuclearDataUtils/CovarianceDataContainer/CovarianceReactionDataContainer.hpp"
#include "NuclearDataUtils/ProbabilityDataContainer/ProbabilityDataContainer.hpp"

namespace frendy
{
  class NuclearDataObject
  {
    private:
      frendy::ErrorManager  err_obj;

      frendy::GeneralDataContainer              general_data_obj;
      frendy::FissionDataContainer              fis_data_obj;
      frendy::ResonanceDataContainer            reso_data_obj;
      frendy::ThermalScatterDataContainer       thermal_scat_data_obj;
      frendy::NuclearReactionDataContainer      nucl_reaction_data_obj;
      frendy::CovarianceGeneralDataContainer    cov_general_data_obj;
      frendy::CovarianceResonanceDataContainer  cov_reso_data_obj;
      frendy::CovarianceReactionDataContainer   cov_reaction_data_obj;
      frendy::ProbabilityDataContainer          prob_data_obj;

      void modify_mt_no_for_endf5_no_cov(vector<Integer> mt_endf5, vector<Integer> mt_endf6);
      void modify_mt_no_for_endf5_cov(vector<Integer> mt_endf5, vector<Integer> mt_endf6);

    public:
      //constructor
      NuclearDataObject(void);

      //destructor
      virtual ~NuclearDataObject(void);

      void clear();

      void modify_mt_no_for_endf5();

      //Getter
      frendy::GeneralDataContainer              get_general_data_obj();
      frendy::FissionDataContainer              get_fis_data_obj();
      frendy::ResonanceDataContainer            get_reso_data_obj();
      frendy::ThermalScatterDataContainer       get_thermal_scat_data_obj();
      frendy::NuclearReactionDataContainer      get_nucl_reaction_data_obj();
      frendy::CovarianceGeneralDataContainer    get_cov_general_data_obj();
      frendy::CovarianceResonanceDataContainer  get_cov_reso_data_obj();
      frendy::CovarianceReactionDataContainer   get_cov_reaction_data_obj();
      frendy::ProbabilityDataContainer          get_prob_data_obj();

      //Setter
      void set_general_data_obj( frendy::GeneralDataContainer obj_data );
      void set_fis_data_obj( frendy::FissionDataContainer obj_data );
      void set_reso_data_obj( frendy::ResonanceDataContainer obj_data );
      void set_thermal_scat_data_obj( frendy::ThermalScatterDataContainer obj_data );
      void set_nucl_reaction_data_obj( frendy::NuclearReactionDataContainer obj_data );
      void set_cov_general_data_obj( frendy::CovarianceGeneralDataContainer obj_data );
      void set_cov_reso_data_obj( frendy::CovarianceResonanceDataContainer obj_data );
      void set_cov_reaction_data_obj( frendy::CovarianceReactionDataContainer obj_data );
      void set_prob_data_obj( frendy::ProbabilityDataContainer obj_data );
  };
}

#endif //NUCLEAR_DATA_OBJECT_H
