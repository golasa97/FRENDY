#ifndef THERMAL_QUANTITY_CALCULATOR_H
#define THERMAL_QUANTITY_CALCULATOR_H

#include "NuclearDataUtils/NuclearDataCalculator/NuBarCalculator.hpp"
#include "NuclearDataUtils/NuclearDataObject.hpp"

namespace frendy
{
  class ThermalQuantityCalculator
  {
    private:
      static const Real8 ene_reso; //= 0.5000;
      
      frendy::ErrorManager    err_obj;
      frendy::TabInterpolator ti_obj;
      frendy::NuBarCalculator nu_obj;

#ifdef DEBUG_MODE
  public:
#endif

      frendy::NuclearDataObject                 nucl_data_obj;
      vector<frendy::CrossSectionDataContainer> xs_data_obj; 
      
      Integer err_flg, calc_flg, fissile_flg;
      Real8   temp_ori,   ene_ori;
      Real8   sig_f_th,   sig_c_th,   nu_bar_th;
      Real8   sig_f_ori,  sig_c_ori,  nu_bar_ori;
      Real8   sig_f_reso, sig_c_reso;
      Real8   g_fac_fis,  g_fac_cap,  inte_fis, inte_cap, inte_fis_reso, inte_cap_reso, alpha,
              eta, k1, k1_eq;
      
      void calc_integral_value(vector<Real>& ene_vec, vector<Real>& sig_fis, vector<Real>& sig_cap,
                               int ene_fis_sta, int ene_fis_end);
      void calc_resonance_integral_value(vector<Real>& ene_vec, vector<Real>& sig_fis, vector<Real>& sig_cap,
                                         int ene_fis_sta, int ene_fis_end);
      
      void check_xs_data(vector<Integer>& nbt_fis, vector<Integer>& int_fis, vector<Real>& ene_fis,
                         vector<Integer>& nbt_cap, vector<Integer>& int_cap, vector<Real>& ene_cap);

      void clear_thermal_quantity();
      
    public:
      //constructor
      ThermalQuantityCalculator(void);

      //destructor
      virtual ~ThermalQuantityCalculator(void);

      void clear();
      
      void search_fission_energy_grid(vector<Real>& ene_fis, vector<Real>& ene_cap, 
                                      int& ene_fis_sta, int& ene_fis_end);

      void calc_thermal_quantity();
      void calc_thermal_quantity(vector<Real>& ene_vec, vector<Real>& sig_fis, vector<Real>& sig_cap,
                                 int& ene_fis_sta, int& ene_fis_end);
      
      Integer check_temp(Real8 temp_val);
      Integer check_nucl_data_obj(frendy::NuclearDataObject& data_obj);
      
      void set_nucl_data_obj(frendy::NuclearDataObject data_obj);
      void set_temp_ori(Real8 real_val);

      frendy::NuclearDataObject  get_nucl_data_obj();
      Real8                      get_temp_ori();
      
      Integer get_err_flg();
      Integer get_fissile_flg();

      Real8 get_ene_ori();

      Real8 get_sig_f_th();
      Real8 get_sig_c_th();
      Real8 get_nu_bar_th();
      Real8 get_sig_f_ori();
      Real8 get_sig_c_ori();
      Real8 get_nu_bar_ori();
      Real8 get_sig_f_reso();
      Real8 get_sig_c_reso();
      
      Real8 get_g_fac_fis();
      Real8 get_g_fac_cap();
      Real8 get_inte_fis();
      Real8 get_inte_cap();
      Real8 get_inte_fis_reso();
      Real8 get_inte_cap_reso();
      Real8 get_alpha();
      Real8 get_eta();
      Real8 get_k1();
      Real8 get_k1_eq();
  };
}

#endif //THERMAL_QUANTITY_CALCULATOR_H
