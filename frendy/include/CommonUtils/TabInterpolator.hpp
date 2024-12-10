#ifndef TAB_INTERPORATOR_H
#define TAB_INTERPORATOR_H


#include "Config/FrendyTypes.hpp"
#include "Config/CommonData.hpp"
#include "ErrorManager.hpp"

namespace frendy
{
  class TabInterpolator
  {
    private:
      frendy::ErrorManager err_obj;

#ifdef DEBUG_MODE
  public:
#endif
      void mod_rounding_error(Real8& x, Real8& y, int i_m, int i_p,
                              vector<Real8>& x_data, vector<Real8>& y_data);
      int  check_boundary_data(Real8& x, Real8& y, int i_m, int i_p,
                               vector<Real8>& x_data, vector<Real8>& y_data);

    public:

      void interpolation_const(Real8& x, Real8& y, Real8& x_m, Real8& y_m, Real8& x_p, Real8& y_p);
      void interpolation_linear_linear(Real8& x, Real8& y, Real8& x_m, Real8& y_m, Real8& x_p, Real8& y_p);
      void interpolation_linear_log(Real8& x, Real8& y, Real8& x_m, Real8& y_m, Real8& x_p, Real8& y_p);
      void interpolation_log_linear(Real8& x, Real8& y, Real8& x_m, Real8& y_m, Real8& x_p, Real8& y_p);
      void interpolation_log_log(Real8& x, Real8& y, Real8& x_m, Real8& y_m, Real8& x_p, Real8& y_p);
      void interpolation_special_1d_law(Real8& x, Real8& y, Real8& x_m, Real8& y_m, Real8& x_p, Real8& y_p, 
                                        Real8& q, Real8& thrx);

      void mod_grid_data(vector<Real8>& grid_main, vector<Real8>& data_main,
                         vector<Integer>& range_sub, vector<Integer>& int_sub,
                         vector<Real8>& grid_sub, vector<Real8>& data_sub);
    
      //constructor
      TabInterpolator(void);

      //destructor
      virtual ~TabInterpolator(void);

      void    search_neighbor_value(Real8& x_real, vector<Real8>& x_data, int& i_m, int& i_p);
      int     get_interpolation_range_pos(vector<Integer>& nbt_data, vector<Integer>& int_data, int i_pos);
      Integer search_interpolation_range(vector<Integer>& nbt_data, vector<Integer>& int_data, int i_pos); 

      //void interpolation_tab1( Real8& x, Real8& y, vector<Integer>& nbt_data, vector<Integer>& int_data,
      //                         vector<Real>& x_data, vector<Real>& y_data );
      //void interpolation_tab1( Real8& x, Real8& y, vector<Integer>& nbt_data, vector<Integer>& int_data,
      //                         vector<Real>& x_data, vector<Real>& y_data, Real& q, Real& thrx );

      void interpolation_tab1( Real8& x, Real8& y, vector<Integer>& nbt_data, vector<Integer>& int_data,
                               vector<Real8>& x_data, vector<Real8>& y_data );
      void interpolation_tab1_in_range( Real8& x, Real8& y,
                                        vector<Integer>& nbt_data, vector<Integer>& int_data,
                                        vector<Real8>& x_data, vector<Real8>& y_data );
      void interpolation_tab1( Real8& x, Real8& y, vector<Integer>& nbt_data, vector<Integer>& int_data,
                               vector<Real8>& x_data, vector<Real8>& y_data, Real8& q, Real8& thrx );
      void interpolation_tab1_in_range( Real8& x, Real8& y,
                                        vector<Integer>& nbt_data, vector<Integer>& int_data,
                                        vector<Real8>& x_data, vector<Real8>& y_data, Real8& q, Real8& thrx );
      void interpolation_tab1( Real8& x, Real8& y, vector<Integer>& nbt_data, vector<Integer>& int_data,
                               vector<Real8>& x_data, vector<Real8>& y_data, Real8& threshold );
      void interpolation_tab1_in_range( Real8& x, Real8& y,
                                        vector<Integer>& nbt_data, vector<Integer>& int_data,
                                        vector<Real8>& x_data, vector<Real8>& y_data, Real8& threshold );
      
      void interpolation_1d(Integer int_val, Real8& x, Real8& y, vector<Real8>& x_data, vector<Real8>& y_data);
      void interpolation_1d_in_range(Integer int_val, Real8& x, Real8& y,
                                     vector<Real8>& x_data, vector<Real8>& y_data);
      void interpolation_1d(Integer int_val, Real8& x, Real8& y, vector<Real8>& x_data, vector<Real8>& y_data,
                            Real8& q, Real8& thrx);
      void interpolation_1d_in_range(Integer int_val, Real8& x, Real8& y,
                                     vector<Real8>& x_data, vector<Real8>& y_data, Real8& q, Real8& thrx);
      void interpolation_1d(Integer int_val, Real8& x, Real8& y, vector<Real8>& x_data, vector<Real8>& y_data,
                            Real8& threshold);
      void interpolation_1d_in_range(Integer int_val, Real8& x, Real8& y,
                                     vector<Real8>& x_data, vector<Real8>& y_data, Real8& threshold);

      void interpolation_1d(Integer int_val, Real8& x, Real8& y, Real8& x_m, Real8& y_m, Real8& x_p, Real8& y_p);
      void interpolation_1d(Integer int_val, Real8& x, Real8& y, Real8& x_m, Real8& y_m, Real8& x_p, Real8& y_p,
                            Real8& q, Real8& thrx);
      void interpolation_1d(Integer int_val, Real8& x, Real8& y, Real8& x_m, Real8& y_m, Real8& x_p, Real8& y_p,
                            Real8& threshold);

      void interpolation_2d(Integer int_val, Real8& x, vector<Integer>& range_vec, vector<Integer>& int_vec,
             vector<Real8>& y, vector<Real8>& z, Real8& x_m, Real8& x_p, 
             vector<Integer>& range_m, vector<Integer>& int_m, vector<Real8>& y_m, vector<Real8>& z_m,
             vector<Integer>& range_p, vector<Integer>& int_p, vector<Real8>& y_p, vector<Real8>& z_p);

      void interpolation_2d(Real8& x, Real8& y, Real8& z,
                            vector<Integer>& range_x, vector<Integer>& int_x, vector<Real8>& x_grid,
                            vector<vector<Integer> >& range_y, vector<vector<Integer> >& int_y,
                            vector<vector<Real8> >& y_grid, vector<vector<Real8> >& y_data);

      void get_interpolation_linear_linear_coef(Real8& a_val, Real8& b_val,
                                                Real8& x_m, Real8& y_m, Real8& x_p, Real8& y_p);
  };
}

#endif // TAB_INTERPORATOR_H
