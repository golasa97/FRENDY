#ifndef GENDF_XS_DATA_MODIFIER_H
#define GENDF_XS_DATA_MODIFIER_H

#include "EndfUtils/GendfParser/GendfParser.hpp"
#include "EndfUtils/GendfParser/GendfMerger.hpp"
#include "NuclearDataUtils/OtherUtils/NuclearDataObjectUtils.hpp"

namespace frendy
{
  class GendfXsDataModifier
  {
    private:
      frendy::ErrorManager      err_obj;
      frendy::TabInterpolator   ti_obj;

      void modify_elastic_scattering(frendy::GMF03Parser& mf03_mt002_obj, frendy::GMF06Parser& mf06_mt002_obj,
                                     frendy::GMF03Parser& mf03_add_obj,   frendy::GMF06Parser& mf06_add_obj,
                                     vector<int>& ig_dif_vec,
                                     vector<vector<vector<Real> > >& xs_dif_vec);


      void modify_inelastic_scattering(frendy::GendfParser& gendf_obj, Integer mt_ela_new);

    public:
      //constructor
      GendfXsDataModifier(void);

      //destructor
      virtual ~GendfXsDataModifier(void);

      void clear();

      vector<Real> get_neutron_absorption(GendfParser& gendf_obj, Integer reaction_type);
      Real         get_neutron_absorption(GendfParser& gendf_obj, Integer reaction_type,
                                          Real ene);

      void generate_absorption_xs(frendy::GendfParser& gendf_obj, Integer mt_abs_new);
      void generate_production_xs(frendy::GendfParser& gendf_obj, Integer mt_pro_new);

      vector<Real> get_fission_spectrum(frendy::GendfParser& gendf_obj);

      void merge_tsl_data_to_total(frendy::GendfParser& gendf_obj, Integer mt_tot_new, Integer mt_ela_new);
  };
}

#endif // GENDF_XS_DATA_MODIFIER_H
