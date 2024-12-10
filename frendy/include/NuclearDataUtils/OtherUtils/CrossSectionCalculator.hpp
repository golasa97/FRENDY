#ifndef CROSS_SECTION_CALCULATOR_H
#define CROSS_SECTION_CALCULATOR_H

#include "NuclearDataUtils/NuclearDataObject.hpp"
#include "CommonUtils/TabInterpolator.hpp"

namespace frendy
{
  class CrossSectionCalculator
  {
    private:
      frendy::TabInterpolator ti_obj;

    public:
      //constructor
      CrossSectionCalculator(void);

      //destructor
      virtual ~CrossSectionCalculator(void);

      Real8 calc_xs_data_double(Real8 ene_data, Real8 xs_data,
                                vector<Real8>& multi_ene_vec, vector<Real8>& multi_vec);
      Real  calc_xs_data(Real ene_data, Real xs_data,
                         vector<Real>& multi_ene_vec, vector<Real>& multi_vec);

      Real8 calc_xs_data_double(Real8 ene_data, Real8 xs_data,
                                vector<Integer>& multi_nbt_vec, vector<Integer>& multi_int_vec,
                                vector<Real8>&   multi_ene_vec, vector<Real8>&   multi_vec);
      Real  calc_xs_data(Real ene_data, Real xs_data,
                         vector<Integer>& multi_nbt_vec, vector<Integer>& multi_int_vec,
                         vector<Real>&    multi_ene_vec, vector<Real>&    multi_vec);


      Real8 calc_xs_data_double(Real8 ene_data,
                                vector<Integer>& xs_nbt_vec,    vector<Integer>& xs_int_vec,
                                vector<Real8>&   xs_ene_vec,    vector<Real8>&   xs_vec,
                                vector<Integer>& multi_nbt_vec, vector<Integer>& multi_int_vec,
                                vector<Real8>&   multi_ene_vec, vector<Real8>&   multi_vec);
      Real  calc_xs_data(Real ene_data,
                         vector<Integer>& xs_nbt_vec,    vector<Integer>& xs_int_vec,
                         vector<Real>&    xs_ene_vec,    vector<Real>&    xs_vec,
                         vector<Integer>& multi_nbt_vec, vector<Integer>& multi_int_vec,
                         vector<Real>&    multi_ene_vec, vector<Real>&    multi_vec);

      vector<Real> calc_xs_data(Real ene_data, frendy::CrossSectionDataContainer&       xs_obj,
                                               frendy::RadioactiveProductDataContainer& rad_obj);

      vector<Real> calc_xs_data(Real ene_data, frendy::CrossSectionDataContainer& xs_obj,
                                               frendy::PhotonDataContainer&       photon_obj);
  };
}

#endif // CROSS_SECTION_CALCULATOR_H
