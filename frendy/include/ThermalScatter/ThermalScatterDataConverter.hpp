#ifndef THERMAL_SCATTER_DATA_CONVERTER_H
#define THERMAL_SCATTER_DATA_CONVERTER_H

#include "NuclearDataUtils/NuclearDataObject.hpp"

namespace frendy
{
  class ThermalScatterDataConverter
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

      static const Integer reaction_type_min = 221;
      static const Integer reaction_type_max = 250;

#ifdef DEBUG_MODE
  public:
#endif
      frendy::NuclearReactionDataContainer nucl_reaction_data_obj;

      Integer reaction_type_inelastic, reaction_type_elastic;
      Real    temp;

      //Cohelent elastic scattering cross section data
      Integer                         coherent_elastic_bragg_no;
      vector<Real8>                   coherent_elastic_ene_grid;
      vector<Real8>                   coherent_elastic_scat_xs_tot;

      //Incohelent elastic scattering cross section data
      vector<Real8>                   incoherent_elastic_ene_grid;
      vector<Real8>                   incoherent_elastic_scat_xs;
      vector<vector<Real8> >          incoherent_elastic_average_scat_angle;

      //Incohelent inelastic scattering cross section data
      vector<Real8>                   incoherent_inelastic_ene_grid;
      vector<Real8>                   incoherent_inelastic_ene_grid_scat_xs_tot;
      vector<Real8>                   incoherent_inelastic_scat_xs_tot;
      vector<vector<Real8> >          incoherent_inelastic_second_ene_grid;
      vector<vector<Real8> >          incoherent_inelastic_scat_xs_tot_second_ene;
      vector<vector<vector<Real8> > > incoherent_inelastic_integrated_scat_xs;

      void set_reaction_type( Integer& reaction_type );
      void set_thermal_scatter_data( frendy::NuclearDataObject& nucl_data_obj );
      void convert_thermal_scatter_to_product_distr();
      void convert_thermal_scatter_to_xs_data();

    public:
      //constructor
      ThermalScatterDataConverter(void);

      //destructor
      virtual ~ThermalScatterDataConverter(void);

      void clear();

      void convert_thermal_scatter_data( Integer reaction_type,
                                         frendy::NuclearDataObject& nucl_data_obj );
  };
}

#endif //THERMAL_SCATTER_DATA_CONVERTER_H
