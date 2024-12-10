#ifndef TAB_ADJUSTER_H
#define TAB_ADJUSTER_H

#include "TabInterpolator.hpp"
#include "DigitAdjuster.hpp"

namespace frendy
{
  class TabAdjuster
  {
    private:
      frendy::ErrorManager    err_obj;
      frendy::TabInterpolator ti_obj;
      frendy::DigitAdjuster   digit_obj;

#ifdef DEBUG_MODE
  public:
#endif
      void modify_y_data(vector<Integer>& nbt_data, vector<Integer>& int_data,
                         vector<Real>& x_data, vector<Real>& y_data,
                         vector<Real>& x_mod,  vector<Real>& y_mod);

      void    change_order_reverse_grid(vector<Real>& grid_data);
      void    change_order_reverse_grid(vector<Integer>& grid_data);
      void    change_order_reverse_table(vector<Integer>& nbt_data, vector<Integer>& int_data,
                                         vector<Real>&    x_data,   vector<Real>&    y_data);
    
    public:
      //constructor
      TabAdjuster(void);

      //destructor
      virtual ~TabAdjuster(void);

      Integer check_order(vector<Real>& grid_data);

      void modify_int_data(vector<Integer>& nbt_data, vector<Integer>& int_data);

      void modify_x_grid(vector<Real>& x_ref,  vector<Integer>& nbt_data, vector<Integer>& int_data,
                         vector<Real>& x_data, vector<Real>& y_data);
      void modify_x_grid_by_lin_lin(vector<Real>& x_ref,
                                    vector<Real>& x_data, vector<Real>& y_data);

      void delete_overlap_grid(vector<Real>& x_grid);
      void delete_overlap_grid(vector<Integer>& nbt_data, vector<Integer>& int_data,
                               vector<Real>& x_data, vector<Real>& y_data);

      void add_grid_data(vector<Real>& x_data, vector<Real>& add_data, Real max_add_val);
      void add_grid_data(vector<Real>& x_data, vector<Real>& add_data);

      void adjust_overlap_grid(vector<Real>& x_grid);

      void add_grid_data(vector<Real>& x_data, Real& add_data, int& pos);
      void add_grid_data(vector<Real>& x_data, Real& add_data);

      vector<int> search_add_grid_pos(vector<Real>& x_data, vector<Real>& add_data, int& add_no);

      void add_table_data(vector<Real>& x_data, vector<Real>& y_data, Real& add_x_data, Real& add_y_data);
      void add_table_data(vector<Real>& x_data, vector<vector<Real> >& y_data,
                          Real& add_x_data, vector<Real>& add_y_data);

      void add_grid_data_at_given_position(vector<Real>& x_data, Real& add_data, int pos);
      void add_grid_data_at_given_position(vector<vector<Real> >& x_data, vector<Real>& add_data, int pos);
      void add_table_data_at_given_position(vector<Real>& x_data, vector<Real>& y_data,
                                            Real& add_x_data, Real& add_y_data, int pos);
      void add_table_data_at_given_position(vector<Real>& x_data, vector<vector<Real> >& y_data,
                                            Real& add_x_data, vector<Real>& add_y_data, int pos);

      void remove_zero_data(vector<Integer>& nbt_data, vector<Integer>& int_data,
                            vector<Real>&    x_data,   vector<Real>&    y_data);

      void remove_specified_grid(vector<Integer>& nbt_data, vector<Integer>& int_data,
                                 vector<Real>&    x_data,   vector<Real>&    y_data, int remove_grid_pos);
      void remove_specified_grid(vector<Integer>& nbt_data, vector<Integer>& int_data,
                                 vector<Real>&    x_data,   vector<Real>&    y_data,
                                 vector<int> remove_grid_pos);
      void remove_descending_order_data(vector<Integer>& nbt_data, vector<Integer>& int_data,
                                        vector<Real>&    x_data,   vector<Real>&    y_data);
  };
}

#endif // TAB_ADJUSTER_H
