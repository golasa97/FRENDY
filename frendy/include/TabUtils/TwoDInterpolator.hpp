#ifndef TWO_D_INTERPOLATOR_H
#define TWO_D_INTERPOLATOR_H

#include "CommonUtils/TabInterpolator.hpp"
#include "CommonUtils/ErrorManager.hpp"
#include "TabUtils/LinearizeTabData.hpp"
#include "TabUtils/IntegrateTabData.hpp"

namespace frendy
{
  class TwoDInterpolator
  {
    private:
      frendy::ErrorManager      err_obj;
      frendy::VectorClearer     clr_obj;

      frendy::TabInterpolator   ti_obj;
      frendy::TabAdjuster       ta_obj;

      frendy::LinearizeTabData  lin_obj;
      frendy::IntegrateTabData  integ_obj;

      vector<vector<Real> > x1_array, y1_array, x2_array, y2_array;

      vector<Real>          x1_range_inv;
      vector<vector<Real> > x1_array_diff, x1_array_ori, x2_array_ori,
                            x_mce_array,   y_mce_array;

#ifdef DEBUG_MODE
  public:
#endif
      int                   data_no_total;
      vector<int>           data_no_each_bin;

      void make_array_data(int bin_no, vector<Real> x_vec, vector<Real> y_vec,
                           vector<vector<Real> >& x_array, vector<vector<Real> >& y_array);

      void remove_zero_data(vector<Real>& x_vec, vector<Real>& y_vec);

      void set_normarized_table_data(int bin_no);

      void mce_interpolation_each_bin(Real z_val, int int_tab2,
                                      vector<Real>& x1_vec, vector<Real>& y1_vec, Real z1_val,
                                      vector<Real>& x2_vec, vector<Real>& y2_vec, Real z2_val,
                                      vector<Real>& x_new,  vector<Real>& y_new);

      void merge_array_data(vector<vector<Real> >& x_array, vector<vector<Real> >& y_array,
                            vector<Real>& x_vec, vector<Real>& y_vec);

    public:
      //constructor
      TwoDInterpolator(void);

      //destructor
      virtual ~TwoDInterpolator(void);

      void clear();

      void set_array_data(int& bin_no, vector<Real>& x1_vec, vector<Real>& y1_vec,
                          vector<Real>& x2_vec, vector<Real>& y2_vec);

      void mce_interpolation_without_set_array(Real z_val, int int_tab2, Real z1_val, Real z2_val,
                                               vector<Real>& x_new, vector<Real>& y_new);

      //### Interpolation by MCE ###
      void mce_interpolation(Real z_val, int bin_no, int int_tab2,
                             vector<Integer>& nbt1_vec, vector<Integer>& int1_vec,
                             vector<Real>&    x1_vec,   vector<Real>&    y1_vec, Real z1_val,
                             vector<Integer>& nbt2_vec, vector<Integer>& int2_vec,
                             vector<Real>&    x2_vec,   vector<Real>&    y2_vec, Real z2_val,
                             vector<Integer>& nbt_new,  vector<Integer>& int_new,
                             vector<Real>&    x_new,    vector<Real>&    y_new);

      //Interpolation law of (x_new, y_new) is linear-linear.
      void mce_interpolation(Real z_val, int bin_no, int int_tab2,
                             Integer int1_val, vector<Real>& x1_vec, vector<Real>& y1_vec, Real z1_val,
                             Integer int2_val, vector<Real>& x2_vec, vector<Real>& y2_vec, Real z2_val,
                             vector<Real>& x_new, vector<Real>& y_new);

      //Interpolation law of (x_new, y_new) is linear-linear.
      void mce_interpolation(Real z_val, int bin_no, int int_tab2,
                             vector<Integer>& nbt1_vec, vector<Integer>& int1_vec,
                             vector<Real>&    x1_vec,   vector<Real>&    y1_vec,   Real z1_val,
                             vector<Integer>& nbt2_vec, vector<Integer>& int2_vec,
                             vector<Real>&    x2_vec,   vector<Real>&    y2_vec,   Real z2_val,
                             vector<Real>&    x_new,    vector<Real>&    y_new);

      //Interpolation law of (x1, y1), (x2, y2), (x_new, y_new) are linear-linear.
      void mce_interpolation(Real z_val, int bin_no, int int_tab2, 
                             vector<Real>&    x1_vec,   vector<Real>&    y1_vec,  Real z1_val,
                             vector<Real>&    x2_vec,   vector<Real>&    y2_vec,  Real z2_val,
                             vector<Real>&    x_new,    vector<Real>&    y_new);

      //Get y value using MCE interpolation
      Real mce_interpolation(Real z_val, Real y_val, int bin_no, int int_tab2, 
                             vector<Integer>& nbt1_vec, vector<Integer>& int1_vec,
                             vector<Real>&    x1_vec,   vector<Real>&    y1_vec,   Real z1_val,
                             vector<Integer>& nbt2_vec, vector<Integer>& int2_vec,
                             vector<Real>&    x2_vec,   vector<Real>&    y2_vec,   Real z2_val);

      //Get y value using MCE interpolation
      //Interpolation law of (x1, y1), (x2, y2), (x_new, y_new) are linear-linear.
      Real mce_interpolation(Real z_val, Real y_val, int bin_no, int int_tab2, 
                             vector<Real>& x1_vec, vector<Real>& y1_vec, Real z1_val,
                             vector<Real>& x2_vec, vector<Real>& y2_vec, Real z2_val);



      //### Interpolation by unit base ###
      void unit_base_interpolation(Real z_val, int int_tab2,
                                   vector<Integer>& nbt1_vec, vector<Integer>& int1_vec,
                                   vector<Real>&    x1_vec,   vector<Real>&    y1_vec,   Real z1_val,
                                   vector<Integer>& nbt2_vec, vector<Integer>& int2_vec,
                                   vector<Real>&    x2_vec,   vector<Real>&    y2_vec,   Real z2_val,
                                   vector<Integer>& nbt_new,  vector<Integer>& int_new,
                                   vector<Real>&    x_new,    vector<Real>&    y_new);

      //Interpolation law of (x_new, y_new) is linear-linear.
      void unit_base_interpolation(Real z_val, int int_tab2,
                                   Integer int1_val, vector<Real>& x1_vec, vector<Real>& y1_vec, Real z1_val,
                                   Integer int2_val, vector<Real>& x2_vec, vector<Real>& y2_vec, Real z2_val,
                                   vector<Real>& x_new, vector<Real>& y_new);

      //Interpolation law of (x_new, y_new) is linear-linear.
      void unit_base_interpolation(Real z_val, int int_tab2,
                                   vector<Integer>& nbt1_vec, vector<Integer>& int1_vec,
                                   vector<Real>&    x1_vec,   vector<Real>&    y1_vec,   Real z1_val,
                                   vector<Integer>& nbt2_vec, vector<Integer>& int2_vec,
                                   vector<Real>&    x2_vec,   vector<Real>&    y2_vec,   Real z2_val,
                                   vector<Real>&    x_new,    vector<Real>&    y_new);

      //Interpolation law of (x1, y1), (x2, y2), (x_new, y_new) are linear-linear.
      void unit_base_interpolation(Real z_val, int int_tab2, 
                                   vector<Real>&    x1_vec,   vector<Real>&    y1_vec, Real z1_val,
                                   vector<Real>&    x2_vec,   vector<Real>&    y2_vec, Real z2_val,
                                   vector<Real>&    x_new,    vector<Real>&    y_new);

      //Get y value using unit base interpolation
      Real unit_base_interpolation(Real z_val, Real y_val, int int_tab2, 
                                   vector<Integer>& nbt1_vec, vector<Integer>& int1_vec,
                                   vector<Real>&    x1_vec,   vector<Real>&    y1_vec,   Real z1_val,
                                   vector<Integer>& nbt2_vec, vector<Integer>& int2_vec,
                                   vector<Real>&    x2_vec,   vector<Real>&    y2_vec,   Real z2_val);

      //Get y value using unit base interpolation
      //Interpolation law of (x1, y1), (x2, y2), (x_new, y_new) are linear-linear.
      Real unit_base_interpolation(Real z_val, Real y_val, int int_tab2, 
                                   vector<Real>&    x1_vec,   vector<Real>&    y1_vec, Real z1_val,
                                   vector<Real>&    x2_vec,   vector<Real>&    y2_vec, Real z2_val);

  };
}

#endif //TWO_D_INTERPOLATOR_H
