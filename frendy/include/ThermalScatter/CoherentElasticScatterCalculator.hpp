#ifndef COHERENT_ELASTIC_SCATTER_CALCULATOR_H
#define COHERENT_ELASTIC_SCATTER_CALCULATOR_H

#include "NuclearDataUtils/NuclearDataObject.hpp"
#include "CommonUtils/VectorCopier.hpp"
#include "CommonUtils/TabAdjuster.hpp"
#include "CommonUtils/DigitAdjuster.hpp"
#include "MathUtils/MathUtils.hpp"
#include "ThermalScatter/IncoherentInelasticScatterCalculator.hpp"

namespace frendy
{
  class CoherentElasticScatterCalculator
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;
      frendy::VectorCopier  cp_obj;
      frendy::TabAdjuster   ta_obj;
      frendy::DigitAdjuster digit_obj;
      frendy::MathUtils     math_obj;

      Real8 pi_sq, third, tau_part, tau_part_inv;

#ifdef DEBUG_MODE
  public:
#endif
      frendy::NuclearDataObject          nucl_data_obj;

      Integer calc_coherent_elastic_scat_flg, opt_elastic;

      int                    bragg_edge_no;
      Integer                legendre_order, atom_no;
      Real8                  err, ene_max, temp;
      vector<Real8>          ene_grid, scat_xs_tot;
      vector<vector<Real8> > scat_xs;

      Real8                  sig_c, tau_sq_max;
      vector<Real8>          tau_sq, form_factor, structure_factor_ene_data, structure_factor_data;

      Integer check_ene_grid( Real8& ene_pre, Real8& ene_cur,
                              vector<Real8>& xs_pre, vector<Real8>& xs_cur,
                              Real8& mid_ene, vector<Real8>& mid_xs);
      void    insert_middle_ene_grid( int& ele_no, vector<Real8>& ene_data, vector<vector<Real8> >& xs_data,
                                      Real8& mid_ene, vector<Real8>& mid_xs);
      void    add_xs_at_each_ene_grid( vector<Real8>& new_ene,      vector<vector<Real8> >& new_xs,
                                       vector<Real8>& new_ene_part, vector<vector<Real8> >& new_xs_part );

      void calc_coherent_elastic_scatter(Real8& ene_data, vector<Real8>& xs_data);
      void calc_coherent_elastic_scatter_by_nuclear_data(Real8& ene_data, vector<Real8>& xs_data);
      void calc_coherent_elastic_scatter_by_form_factor(Real8& ene_data, vector<Real8>& xs_data);
      void legendre_expansion(Real8& ene_data, Real8& ene_bragg, Real8& coef, vector<Real8>& xs_data);

      void  preparation_for_coherent_erastic_scatter();
      void  check_set_data();
      void  set_structure_factor();
      void  set_form_factor();
      void  set_initial_value_for_form_factor(Real8& coef_a, Real8& coef_c, Real8& mass, Real8& debye_waller);
      Real8 calc_form_factor_weight(int i, int j, int k);
      Real8 calc_tau_sq(Real8& coef_tau1, Real8& coef_tau2, Real8& li, Real8& lj, Real8& lk);
      Real8 calc_crystallographis_structure_factor(Real8& li, Real8& lj, Real8& lk);
      void  calc_bragg_edge_no(vector<Real8>& ene_vec);
      void  set_energy_grid();
      void  add_energy_grid(vector<Real8>& ene_vec);

    public:
      //constructor
      CoherentElasticScatterCalculator(void);

      //destructor
      virtual ~CoherentElasticScatterCalculator(void);

      static const Integer no_calc       =  0;
      static const Integer use_nucl_data = 10;
      static const Integer calc_graphite =  1;
      static const Integer calc_be       =  2;
      static const Integer calc_be_o     =  3;

      void clear();

      void calc_coherent_elastic_scatter();

      //Setter
      void set_nucl_data_obj(frendy::NuclearDataObject& data_obj);
      void set_opt_elastic(Integer& int_data);
      void set_atom_no(Integer& int_data);
      void set_err(Real8& real_data);
      void set_ene_max(Real8& real_data);
      void set_temp(Real8& real_data);

      //Getter
      frendy::NuclearDataObject get_nucl_data_obj();
      Integer                   get_opt_elastic();
      Integer                   get_atom_no();
      Integer                   get_bragg_edge_no();
      Real8                     get_err();
      Real8                     get_ene_max();
      Real8                     get_temp();
  };
}

#endif //COHERENT_ELASTIC_SCATTER_CALCULATOR_H
