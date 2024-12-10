#ifndef NUCL_DATA_OBJECT_UTILS_H
#define NUCL_DATA_OBJECT_UTILS_H

#include "CommonUtils/ErrorManager.hpp"
#include "CommonUtils/VectorClearer.hpp"
#include "CommonUtils/DigitAdjuster.hpp"
#include "CommonUtils/TabInterpolator.hpp"
#include "NuclearDataUtils/NuclearDataObject.hpp"

namespace frendy
{
  class NuclearDataObjectUtils
  {
    private:
      frendy::ErrorManager    err_obj;
      frendy::VectorClearer   clr_obj;
      frendy::TabInterpolator ti_obj;
      frendy::DigitAdjuster   digit_obj;

      static const int caution_flg_on  = 0;
      static const int caution_flg_off = 1;

      int     caution_flg;

      Real   ene_min;
      int    reaction_type_no;
      string data_name;

      void search_ene_min(NuclearReactionDataContainer&            react_obj,
                          vector<CrossSectionDataContainer>&       xs_data_obj,
                          vector<RadioactiveProductDataContainer>& radio_prod_data_obj,
                          vector<PhotonDataContainer>&             photon_data_obj);

    public:
      //constructor
      NuclearDataObjectUtils(void);

      //destructor
      virtual ~NuclearDataObjectUtils(void);

      void clear();

      void modify_comment_data(frendy::NuclearDataObject& nucl_data_obj,
                               vector<string> comment_data);

      //MF=3, 10, and 13
      void modify_xs_data(frendy::NuclearDataObject& nucl_data_obj);
      void modify_xs_data_without_caution(frendy::NuclearDataObject& nucl_data_obj);
      void modify_table_data(vector<Integer>& range_vec, vector<Integer>& int_vec,
                             vector<Real>&    x_vec,     vector<Real>&    y_vec);
      void remove_zero_data(vector<Integer>& range_vec, vector<Integer>& int_vec,
                            vector<Real>&    x_vec,     vector<Real>&    y_vec);
      void add_zero_data(vector<Integer>& range_vec, vector<Integer>& int_vec,
                         vector<Real>&    x_vec,     vector<Real>&    y_vec);
      void add_ene_grid(Real add_x, Real add_y,
                        vector<Integer>& range_vec, vector<Integer>& int_vec,
                        vector<Real>&    x_vec,     vector<Real>&    y_vec);
      void adjust_discontinuity_data
             (vector<Integer>& range_vec, vector<Integer>& int_vec,
              vector<Real>&    x_vec,     vector<Real>&    y_vec);

      //MF=10
      void check_total_product_xs(frendy::NuclearDataObject& nucl_data_obj);

      //Number of particle emissions in each reaction
      Integer get_emission_no_n(Integer reaction_type);
      //Integer get_emission_no_p(Integer reaction_type);
      //Integer get_emission_no_d(Integer reaction_type);
      //Integer get_emission_no_t(Integer reaction_type);
      //Integer get_emission_no_he(Integer reaction_type);
      //Integer get_emission_no_alpha(Integer reaction_type);

      Integer get_emission_no_n(Integer reaction_type, Integer lib_format);
      //Integer get_emission_no_p(Integer reaction_type, Integer lib_format);
      //Integer get_emission_no_d(Integer reaction_type, Integer lib_format);
      //Integer get_emission_no_t(Integer reaction_type, Integer lib_format);
      //Integer get_emission_no_he(Integer reaction_type, Integer lib_format);
      //Integer get_emission_no_alpha(Integer reaction_type, Integer lib_format);

      //Neutron absorption (1 -^ n_no)
      Integer get_neutron_absorption(Integer reaction_type);
      Integer get_neutron_absorption(Integer reaction_type, Integer lib_format);

      //Other functions
      Integer get_lib_format(vector<Integer>& reaction_type_list);

      vector<Integer> get_related_reaction_type
                        (Integer reaction_type, vector<Integer>& reaction_list);
      vector<Integer> get_related_reaction_type
                        (Integer reaction_type, vector<Integer>& reaction_list, Integer lib_format);


  };
}

#endif //NUCL_DATA_OBJECT_UTILS_H
