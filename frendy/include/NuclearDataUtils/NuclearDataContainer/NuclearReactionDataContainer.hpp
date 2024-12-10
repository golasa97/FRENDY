#ifndef NUCLEAR_REACTION_DATA_CONTAINER_H
#define NUCLEAR_REACTION_DATA_CONTAINER_H

#include "CommonUtils/ErrorManager.hpp"
#include "CommonUtils/VectorClearer.hpp"
#include "NuclearDataUtils/NuclearDataContainer/CrossSectionDataContainer.hpp"
#include "NuclearDataUtils/NuclearDataContainer/EnergyAngularDataContainer.hpp"
#include "NuclearDataUtils/NuclearDataContainer/ProductDistributionDataContainer.hpp"
#include "NuclearDataUtils/NuclearDataContainer/RadioactiveProductDataContainer.hpp"
#include "NuclearDataUtils/NuclearDataContainer/PhotonDataContainer.hpp"
#include "NuclearDataUtils/NuclearDataContainer/OtherNuclearDataContainer.hpp"

namespace frendy
{
  class NuclearReactionDataContainer
  {
    private:
      frendy::ErrorManager  err_obj;

      static const int no_add_reaction_type_mode = 1;
      static const int add_reaction_type_mode    = 0;

      int             reaction_type_add_flg;
      int             reaction_type_no;
      vector<Integer> reaction_type;

      vector<frendy::CrossSectionDataContainer>         xs_data_obj;
      vector<frendy::EnergyAngularDataContainer>        ene_angular_data_obj;
      vector<frendy::ProductDistributionDataContainer>  product_distr_data_obj;
      vector<frendy::RadioactiveProductDataContainer>   radio_product_data_obj;
      vector<frendy::PhotonDataContainer>               photon_data_obj;
      vector<frendy::OtherNuclearDataContainer>         other_data_obj;

      int  add_new_reaction_type(Integer int_data);

      void sort_reaction_data();

      void check_reaction_type(Integer reaction_type_inp, Integer reaction_type_nucl);

      void add_all_container_data(
             vector<frendy::CrossSectionDataContainer>&         xs_data_obj_mod,
             vector<frendy::EnergyAngularDataContainer>&        ene_angular_data_obj_mod,
             vector<frendy::ProductDistributionDataContainer>&  product_distr_data_obj_mod,
             vector<frendy::RadioactiveProductDataContainer>&   radio_product_data_obj_mod,
             vector<frendy::PhotonDataContainer>&               photon_data_obj_mod,
             vector<frendy::OtherNuclearDataContainer>&         other_data_obj_mod);

      void modify_reaction_type();

    public:
      //constructor
      NuclearReactionDataContainer(void);

      //destructor
      virtual ~NuclearReactionDataContainer(void);

      void clear();

      int  check_reaction_type(Integer reaction_type_check);

      void remove_reaction_type(Integer react_val);

      void add_reaction_type(vector<Integer> int_vec);
      void add_xs_data_obj
             (vector<frendy::CrossSectionDataContainer> xs_data_obj_mod);
      void add_ene_angular_data_obj
             (vector<frendy::EnergyAngularDataContainer> ene_angle_data_obj_mod);
      void add_product_distr_data_obj
             (vector<frendy::ProductDistributionDataContainer> product_distr_data_obj_mod);
      void add_radio_product_data_obj
             (vector<frendy::RadioactiveProductDataContainer> radio_product_data_obj_mod);
      void add_photon_data_obj
             (vector<frendy::PhotonDataContainer> photon_data_obj_mod);
      void add_other_data_obj
             (vector<frendy::OtherNuclearDataContainer> other_data_obj_mod);

      //Getter
      vector<Integer> get_reaction_type();

      vector<frendy::CrossSectionDataContainer>         get_xs_data_obj();
      vector<frendy::EnergyAngularDataContainer>        get_ene_angular_data_obj();
      vector<frendy::ProductDistributionDataContainer>  get_product_distr_data_obj();
      vector<frendy::RadioactiveProductDataContainer>   get_radio_product_data_obj();
      vector<frendy::PhotonDataContainer>               get_photon_data_obj();
      vector<frendy::OtherNuclearDataContainer>         get_other_data_obj();

      frendy::CrossSectionDataContainer         get_xs_data_obj(Integer reaction_type_data);
      frendy::EnergyAngularDataContainer        get_ene_angular_data_obj(Integer reaction_type_data);
      frendy::ProductDistributionDataContainer  get_product_distr_data_obj(Integer reaction_type_data);
      frendy::RadioactiveProductDataContainer   get_radio_product_data_obj(Integer reaction_type_data);
      frendy::PhotonDataContainer               get_photon_data_obj(Integer reaction_type_data);
      frendy::OtherNuclearDataContainer         get_other_data_obj(Integer reaction_type_data);

      vector<frendy::CrossSectionDataContainer>         get_xs_data_obj_assigned();
      vector<frendy::EnergyAngularDataContainer>        get_ene_angular_data_obj_assigned();
      vector<frendy::ProductDistributionDataContainer>  get_product_distr_data_obj_assigned();
      vector<frendy::RadioactiveProductDataContainer>   get_radio_product_data_obj_assigned();
      vector<frendy::PhotonDataContainer>               get_photon_data_obj_assigned();
      vector<frendy::OtherNuclearDataContainer>         get_other_data_obj_assigned();

      //Setter
      void set_reaction_type(vector<Integer> int_vec);
      void set_xs_data_obj
             (vector<frendy::CrossSectionDataContainer> xs_data_obj_mod);
      void set_ene_angular_data_obj
             (vector<frendy::EnergyAngularDataContainer> ene_angle_data_obj_mod);
      void set_product_distr_data_obj
             (vector<frendy::ProductDistributionDataContainer> product_distr_data_obj_mod);
      void set_radio_product_data_obj
             (vector<frendy::RadioactiveProductDataContainer> radio_product_data_obj_mod);
      void set_photon_data_obj
             (vector<frendy::PhotonDataContainer> photon_data_obj_mod);
      void set_other_data_obj
             (vector<frendy::OtherNuclearDataContainer> other_data_obj_mod);

      void set_reaction_type(Integer reaction_type_data);
      void set_xs_data_obj
             (Integer reaction_type_data, frendy::CrossSectionDataContainer obj_data);
      void set_ene_angular_data_obj
             (Integer reaction_type_data, frendy::EnergyAngularDataContainer obj_data);
      void set_product_distr_data_obj
             (Integer reaction_type_data, frendy::ProductDistributionDataContainer obj_data);
      void set_radio_product_data_obj
             (Integer reaction_type_data, frendy::RadioactiveProductDataContainer obj_data);
      void set_photon_data_obj
             (Integer reaction_type_data, frendy::PhotonDataContainer obj_data);
      void set_other_data_obj
             (Integer reaction_type_data, frendy::OtherNuclearDataContainer obj_data);

      void set_xs_data_obj(frendy::CrossSectionDataContainer obj_data);
      void set_ene_angular_data_obj(frendy::EnergyAngularDataContainer obj_data);
      void set_product_distr_data_obj(frendy::ProductDistributionDataContainer obj_data);
      void set_radio_product_data_obj(frendy::RadioactiveProductDataContainer obj_data);
      void set_photon_data_obj(frendy::PhotonDataContainer obj_data);
      void set_other_data_obj(frendy::OtherNuclearDataContainer obj_data);
  };
}

#endif //NUCLEAR_REACTION_DATA_CONTAINER_H
