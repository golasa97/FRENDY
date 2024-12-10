#ifndef BROADENED_XS_CALCULATOR_H
#define BROADENED_XS_CALCULATOR_H

#include "CommonUtils/VectorCopier.hpp"
#include "CommonUtils/TabInterpolator.hpp"
#include "CommonUtils/DigitAdjuster.hpp"
#include "CommonUtils/TabAdjuster.hpp"
#include "MathUtils/MathUtils.hpp"
#include "NuclearDataUtils/NuclearDataObject.hpp"

namespace frendy
{
  class BroadenedXSCalculator
  {
    protected:
      Real8 pi_inv, rpi, rpi_inv; //, one_third;
      static const int   max_ex_order = 50;
      static const Real8 max_z_val;    //= 10.0; //exp(-100) = 3.7e-44, erf(10) = 1.0;
      
      frendy::ErrorManager    err_obj;
      frendy::VectorCopier    cp_vec;
      frendy::TabInterpolator ti_obj;
      frendy::DigitAdjuster   digit_obj;
      frendy::MathUtils       math_obj;

#ifdef DEBUG_MODE
  public:
#endif

      frendy::NuclearDataObject                  nucl_data_obj;
      vector<frendy::CrossSectionDataContainer>  xs_data_obj;

      int                    mt_no, grid_no;
      Real8                  temp_ori, temp_dop, dop_ene_max;
      
      Integer                calc_doppler_xs_flg, xs_part_flg;
      int                    int_rang_m_min, int_rang_m_max, int_rang_p_min, int_rang_p_max;
      Real8                  awr, alpha, alpha_r, beta, beta_r;
      Real8                  v_coef, v_t_sq, v_t_inv;
      vector<Real8>          ene_data, x_data;
      vector<vector<Real8> > sig_data, a_vec, c_vec;

      Real8                  y_val_pre, x_zero;
      int                    int_rang_m_min_pre, int_rang_m_max_pre, int_rang_p_min_pre, int_rang_p_max_pre;

      void                  check_integral_range(Real8& y_val);

      virtual vector<Real8> calc_doppler_broadened_xs_part(Real8& y_val, int int_min, int int_max);
      virtual void          calc_h_n(Real8& inte_sta, Real8& inte_fin, Real8 h_n[5], Real8 f_n_sta[5]);
      void                  calc_h_n_by_tayler_ex(int& n, Real8& inte_sta, Real8& inte_fin, Real8& h_n);
      virtual void          calc_f_n(Real8& inte_val, Real8 f_n[5]);
      
      void                  preparation_for_doppler_broadening();
      virtual void          calc_coef();

      void                  calc_x(Real8& ene_val, Real8& x_val);
      void                  calc_y(Real8& ene_val, Real8& y_val);

      void                  calc_doppler_broadened_xs(Real8& ene_val, vector<Real8>& sig_val, int& minus_flg);
      void                  calc_doppler_broadened_xs(Real8& ene_val, vector<Real8>& sig_val);
      
    public:
      //constructor
      BroadenedXSCalculator(void);

      //destructor
      virtual ~BroadenedXSCalculator(void);

      vector<Real8> calc_doppler_broadened_xs(Real8& ene_val);
      virtual void clear();

      void calc_doppler_broadened_xs_from_xs_table
            (Real temp_ori, Real temp_new, Real awr, vector<Integer>& mt_list,
             vector<vector<Real> >& ene_vec, vector<vector<Real> >& xs_vec);
      
      //Setter
      void set_nucl_data_obj(frendy::NuclearDataObject& data_obj);
      void set_temp_ori(Real8 real_val);
      void set_temp_dop(Real8 real_val);
      void set_dop_ene_max(Real8 real_val);
      
      //Getter
      frendy::NuclearDataObject get_nucl_data_obj();
      Real8                     get_temp_ori();
      Real8                     get_temp_dop();
      Real8                     get_dop_ene_max();
  };
}

#endif //BROADENED_XS_CALCULATOR_H
