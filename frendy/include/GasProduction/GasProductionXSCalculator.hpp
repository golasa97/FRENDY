#ifndef GAS_PRODUCTION_XS_CALCULATOR_H
#define GAS_PRODUCTION_XS_CALCULATOR_H

#include "CommonUtils/VectorClearer.hpp"
#include "CommonUtils/TabInterpolator.hpp"
#include "CommonUtils/TabAdjuster.hpp"
#include "NuclearDataUtils/NuclearDataObject.hpp"

namespace frendy
{
  class GasProductionXSCalculator
  {
    private:
      frendy::ErrorManager          err_obj;
      frendy::VectorClearer         clr_obj;
      frendy::TabInterpolator       ti_obj;

      static const int xs_gas_no  = 5;
      static const int xs_gas_p   = 0; //1H (proton)
      static const int xs_gas_d   = 1; //2H (deuteron)
      static const int xs_gas_t   = 2; //3H (triton)
      static const int xs_gas_he3 = 3; //3He
      static const int xs_gas_a   = 4; //4He (alpha) 

#ifdef DEBUG_MODE
  public:
#endif
      Integer write_gas_no_flg;

      Integer mt_p_min, mt_p_max, mt_d_min, mt_d_max, mt_t_min, mt_t_max,
              mt_he3_min, mt_he3_max, mt_a_min, mt_a_max;
      Integer mt_tot, mt_ela, mt_nonela, mt_n, mt_any, mt_cont,
              mt_2nd, mt_2n, mt_3n, mt_f_tot, mt_f, mt_nf, mt_2nf, 
              mt_na, mt_n3a, mt_2na, mt_3na, mt_abs, mt_np, mt_n2a, mt_2n2a,
              mt_nd, mt_nt, mt_nhe, mt_nd2a, mt_nt2a, mt_4n, mt_3nf,
              mt_2np, mt_3np, mt_n2p, mt_npa, mt_n0, mt_nc, mt_dis,
              mt_gam, mt_p, mt_d, mt_t, mt_he, mt_a, mt_2a, mt_3a,
              mt_2p, mt_pa, mt_t2a, mt_d2a, mt_pd, mt_pt, mt_da, mt_reso,
              mt_5n, mt_6n, mt_2nt, mt_ta, mt_4np, mt_3nd, mt_nda,
              mt_2npa, mt_7n, mt_8n, mt_5np, mt_6np, mt_7np,
              mt_4na, mt_5na, mt_6na, mt_7na, mt_4nd, mt_5nd, mt_6nd,
              mt_3nt, mt_4nt, mt_5nt, mt_6nt, mt_2nhe, mt_3nhe, mt_4nhe,
              mt_3n2p, mt_3n2a, mt_3npa, mt_dt, mt_npd, mt_npt, mt_ndt,
              mt_nphe, mt_ndhe, mt_nthe, mt_nta, mt_2n2p, mt_phe, mt_dhe,
              mt_ahe, mt_4n2p, mt_4n2a, mt_4npa, mt_3p, mt_n3p, mt_3n2pa,
              mt_5n2p, mt_xn, mt_xgam, mt_xp, mt_xd, mt_xt, mt_xhe, mt_xa;


      Integer calc_gas_production_xs_flg, nucl_data_ori_set_flg, nucl_data_dop_set_flg;

      frendy::NuclearDataObject nucl_data_obj_ori, nucl_data_obj_dop;

      int         xs_gas_any_flg;
      vector<int> xs_gas_tot_flg, xs_gas_each_flg;

      Integer lib_format;
      Integer ene_max_reaction_type, min_threshold_reaction_type;
      Real    ene_max,               min_threshold_ene;

      vector<Real>          base_grid;
      vector<vector<Real> > gas_prod_xs_data;

      void    check_set_data();
      Integer check_xs_data();

      void    set_reaction_type();
      void    check_reaction_type();

      void    search_min_threshold_ene();
      void    modify_base_grid();

      void    calc_gas_production_reaction_xs();
      void    calc_gas_prod_xs_using_product_distr_data_object
                (int react_no, frendy::CrossSectionDataContainer  xs_data_obj_ori,
                               frendy::CrossSectionDataContainer& xs_data_obj);
      void    add_gas_prod_xs_using_product_distr_data_object
                (int react_no, frendy::CrossSectionDataContainer& xs_data_obj_ori,
                               frendy::CrossSectionDataContainer& xs_data_obj,
                 vector<Integer> prod_range_vec, vector<Integer> prod_int_vec,
                 vector<Real>    prod_ene_vec,   vector<Real>    prod_vec);
      void    add_gas_prod_xs(frendy::CrossSectionDataContainer  xs_data_obj_ori,
                              frendy::CrossSectionDataContainer& xs_data_obj, vector<Real>& prod_no_vec);
      void    check_interpolation(Integer reaction_type, vector<Integer> xs_int_vec);

      Integer check_gas_production_reaction_type
                (Integer mt_no, Integer mat_data, Integer reaction_flg, vector<Real>& prod_no_vec);
      void    check_production_reaction(Integer mt_no, Integer reaction_flg, vector<Real>& prod_no_vec);
      void    check_residual_material(Integer mt_no, Integer mat_data, Integer reaction_flg,
                                      vector<Real>& prod_no_vec);
      Integer check_production_material(Integer mt_no, Integer reaction_flg, vector<Real>& prod_no_vec);

      void add_gas_prod_xs_to_nuclear_data_obj();

    public:
      //constructor
      GasProductionXSCalculator(void);

      //destructor
      virtual ~GasProductionXSCalculator(void);

      void calc_gas_production_xs();
      void output_set_data_information();

      void clear();
      void clear_parser();
      
      //Setter
      void set_nucl_data_obj_ori(frendy::NuclearDataObject data_obj);
      void set_nucl_data_obj_dop(frendy::NuclearDataObject data_obj);
      
      //Getter
      frendy::NuclearDataObject get_nucl_data_obj_ori();
      frendy::NuclearDataObject get_nucl_data_obj();
  };
}

#endif //GAS_PRODUCTION_XS_CALCULATOR_H
