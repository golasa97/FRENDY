#ifndef COVARIANCE_REACTION_DATA_CONTAINER_H
#define COVARIANCE_REACTION_DATA_CONTAINER_H

#include "CommonUtils/ErrorManager.hpp"
#include "CommonUtils/VectorClearer.hpp"
#include "NuclearDataUtils/CovarianceDataContainer/CovarianceFissionDataContainer.hpp"
#include "NuclearDataUtils/CovarianceDataContainer/CovarianceCrossSectionDataContainer.hpp"
#include "NuclearDataUtils/CovarianceDataContainer/CovarianceEnergyAngularDataContainer.hpp"
#include "NuclearDataUtils/CovarianceDataContainer/CovarianceRadioactiveProductDataContainer.hpp"

namespace frendy
{
  class CovarianceReactionDataContainer
  {
    private:
      frendy::ErrorManager  err_obj;

      static const int no_add_reaction_type = 1;
      static const int add_reaction_type    = 0;

      int              reaction_type_add_flg;
      int              reaction_type_no;
      vector<Integer>  reaction_type;

      vector<frendy::CovarianceFissionDataContainer>            cov_fis_data_obj;
      vector<frendy::CovarianceCrossSectionDataContainer>       cov_xs_data_obj;
      vector<frendy::CovarianceEnergyAngularDataContainer>      cov_ene_angular_data_obj;
      vector<frendy::CovarianceRadioactiveProductDataContainer> cov_radio_product_data_obj;

      int  add_new_reaction_type( Integer int_data );

      void sort_reaction_data();

    public:
      //constructor
      CovarianceReactionDataContainer(void);

      //destructor
      virtual ~CovarianceReactionDataContainer(void);

      void clear();

      int  check_reaction_type(Integer reaction_type_check);

      void remove_reaction_type(Integer react_val);

      //Getter
      vector<Integer>                                           get_reaction_type();

      vector<frendy::CovarianceFissionDataContainer>            get_cov_fis_data_obj();
      vector<frendy::CovarianceCrossSectionDataContainer>       get_cov_xs_data_obj();
      vector<frendy::CovarianceEnergyAngularDataContainer>      get_cov_ene_angular_data_obj();
      vector<frendy::CovarianceRadioactiveProductDataContainer> get_cov_radio_product_data_obj();

      frendy::CovarianceFissionDataContainer                    get_cov_fis_data_obj(Integer reaction_type_data);
      frendy::CovarianceCrossSectionDataContainer               get_cov_xs_data_obj(Integer reaction_type_data);
      frendy::CovarianceEnergyAngularDataContainer              get_cov_ene_angular_data_obj(Integer reaction_type_data);
      frendy::CovarianceRadioactiveProductDataContainer         get_cov_radio_product_data_obj(Integer reaction_type_data);

      vector<frendy::CovarianceFissionDataContainer>            get_cov_fis_data_obj_assigned();
      vector<frendy::CovarianceCrossSectionDataContainer>       get_cov_xs_data_obj_assigned();
      vector<frendy::CovarianceEnergyAngularDataContainer>      get_cov_ene_angular_data_obj_assigned();
      vector<frendy::CovarianceRadioactiveProductDataContainer> get_cov_radio_product_data_obj_assigned();

      //Setter
      void set_reaction_type( vector<Integer> int_vec );
      void set_cov_fis_data_obj( vector<frendy::CovarianceFissionDataContainer> obj_data );
      void set_cov_xs_data_obj( vector<frendy::CovarianceCrossSectionDataContainer> obj_data );
      void set_cov_ene_angular_data_obj( vector<frendy::CovarianceEnergyAngularDataContainer> obj_data );
      void set_cov_radio_product_data_obj( vector<frendy::CovarianceRadioactiveProductDataContainer> obj_data );

      void set_reaction_type( Integer reaction_type_data );
      void set_cov_fis_data_obj( Integer reaction_type_data, frendy::CovarianceFissionDataContainer obj_data );
      void set_cov_xs_data_obj( Integer reaction_type_data, frendy::CovarianceCrossSectionDataContainer obj_data );
      void set_cov_ene_angular_data_obj( Integer reaction_type_data, frendy::CovarianceEnergyAngularDataContainer obj_data );
      void set_cov_radio_product_data_obj( Integer reaction_type_data, frendy::CovarianceRadioactiveProductDataContainer obj_data );
  };
}

#endif //COVARIANCE_REACTION_DATA_CONTAINER_H
