#include "ThermalScatter/ThermalScatterDataConverter.hpp"

using namespace frendy;

//constructor
ThermalScatterDataConverter::ThermalScatterDataConverter(void)
{
  clear();
}

//destructor
ThermalScatterDataConverter::~ThermalScatterDataConverter(void)
{
  clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterDataConverter::clear()
{
  nucl_reaction_data_obj.clear();

  reaction_type_inelastic = 0;
  reaction_type_elastic   = 0;

  temp = 0.0;

  coherent_elastic_bragg_no = 0;
  coherent_elastic_ene_grid.clear();
  coherent_elastic_scat_xs_tot.clear();

  incoherent_elastic_ene_grid.clear();
  incoherent_elastic_scat_xs.clear();
  clr_obj.clear_vec_array2_real8(incoherent_elastic_average_scat_angle);

  incoherent_inelastic_ene_grid.clear();
  incoherent_inelastic_ene_grid_scat_xs_tot.clear();
  incoherent_inelastic_scat_xs_tot.clear();
  clr_obj.clear_vec_array2_real8(incoherent_inelastic_second_ene_grid);
  clr_obj.clear_vec_array2_real8(incoherent_inelastic_scat_xs_tot_second_ene);
  clr_obj.clear_vec_array3_real8(incoherent_inelastic_integrated_scat_xs);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterDataConverter::convert_thermal_scatter_data( Integer reaction_type, 
                                                                NuclearDataObject& nucl_data_obj )
{
  set_reaction_type(reaction_type);
  set_thermal_scatter_data(nucl_data_obj);

  convert_thermal_scatter_to_product_distr();
  convert_thermal_scatter_to_xs_data();

  nucl_data_obj.set_nucl_reaction_data_obj(nucl_reaction_data_obj);
  clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterDataConverter::set_reaction_type( Integer& reaction_type )
{
  reaction_type_inelastic = reaction_type;
  reaction_type_elastic   = reaction_type + 1;

  if( reaction_type < reaction_type_min || reaction_type > reaction_type_max )
  {
    string class_name = "ThermalScatterDataConverter";
    string func_name  = "set_reaction_type( Integer& reaction_type )";

    ostringstream oss01, oss02, oss03;
    oss01 << reaction_type;
    oss02 << reaction_type_min;
    oss03 << reaction_type_max;
    
    string str_data00 = "Reaction type number is out of range.";
    string str_data01 = "  Reaction type number         : " + oss01.str();
    string str_data02 = "  Minimum reaction type number : " + oss02.str();
    string str_data03 = "  Maximum reaction type number : " + oss03.str();

    vector<string> err_com;
    err_com.push_back(str_data00);
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterDataConverter::set_thermal_scatter_data( NuclearDataObject& nucl_data_obj )
{
  nucl_reaction_data_obj = nucl_data_obj.get_nucl_reaction_data_obj();
  temp = nucl_data_obj.get_general_data_obj().get_temp();

  ThermalScatterDataContainer th_scat_obj     = nucl_data_obj.get_thermal_scat_data_obj();
  coherent_elastic_bragg_no                   = th_scat_obj.get_coherent_elastic_bragg_no();
  coherent_elastic_ene_grid                   = th_scat_obj.get_coherent_elastic_ene_grid();
  coherent_elastic_scat_xs_tot                = th_scat_obj.get_coherent_elastic_scat_xs_tot();
  incoherent_elastic_ene_grid                 = th_scat_obj.get_incoherent_elastic_ene_grid();
  incoherent_elastic_scat_xs                  = th_scat_obj.get_incoherent_elastic_scat_xs();
  incoherent_elastic_average_scat_angle       = th_scat_obj.get_incoherent_elastic_average_scat_angle();
  incoherent_inelastic_ene_grid               = th_scat_obj.get_incoherent_inelastic_ene_grid();
  incoherent_inelastic_ene_grid_scat_xs_tot   = th_scat_obj.get_incoherent_inelastic_ene_grid_scat_xs_tot();
  incoherent_inelastic_scat_xs_tot            = th_scat_obj.get_incoherent_inelastic_scat_xs_tot();
  incoherent_inelastic_second_ene_grid        = th_scat_obj.get_incoherent_inelastic_second_ene_grid();
  incoherent_inelastic_scat_xs_tot_second_ene = th_scat_obj.get_incoherent_inelastic_scat_xs_tot_second_ene();
  incoherent_inelastic_integrated_scat_xs     = th_scat_obj.get_incoherent_inelastic_integrated_scat_xs();
  th_scat_obj.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterDataConverter::convert_thermal_scatter_to_product_distr()
{
  if( static_cast<int>(incoherent_inelastic_ene_grid.size()) > 0 )
  {
    ProductDistributionDataContainer prod_distr_obj;
    prod_distr_obj.set_reaction_type(reaction_type_inelastic);
    prod_distr_obj.set_ref_frame_flg(5);
    prod_distr_obj.set_temp(temp);
    prod_distr_obj.set_incident_ene(incoherent_inelastic_ene_grid);
    prod_distr_obj.set_second_ene(incoherent_inelastic_second_ene_grid);
    prod_distr_obj.set_incoherent_inelastic_scat_xs_integrate(incoherent_inelastic_scat_xs_tot_second_ene);
    prod_distr_obj.set_incoherent_inelastic_scat_xs_weight(incoherent_inelastic_integrated_scat_xs);
    nucl_reaction_data_obj.set_product_distr_data_obj(prod_distr_obj);
    prod_distr_obj.clear();
  }

  if( static_cast<int>(coherent_elastic_ene_grid.size()) > 0 )
  {
    int mt_coh_ela = reaction_type_elastic;

    ProductDistributionDataContainer prod_distr_obj;
    prod_distr_obj.set_reaction_type(mt_coh_ela);
    prod_distr_obj.set_ref_frame_flg(7);
    prod_distr_obj.set_temp(temp);
    prod_distr_obj.set_bragg_edge_no(coherent_elastic_bragg_no);

    nucl_reaction_data_obj.set_product_distr_data_obj(prod_distr_obj);
    prod_distr_obj.clear();
  }

  if( static_cast<int>(incoherent_elastic_ene_grid.size()) > 0 )
  {
    int mt_incoh_ela = reaction_type_elastic;
    if( static_cast<int>(coherent_elastic_ene_grid.size()) > 0 )
    {
      mt_incoh_ela++;
    }

    ProductDistributionDataContainer prod_distr_obj;
    prod_distr_obj.set_reaction_type(mt_incoh_ela);
    prod_distr_obj.set_ref_frame_flg(6);
    prod_distr_obj.set_temp(temp);
    prod_distr_obj.set_incident_ene(incoherent_elastic_ene_grid);
    prod_distr_obj.set_incoherent_elastic_scat_angle(incoherent_elastic_average_scat_angle);

    nucl_reaction_data_obj.set_product_distr_data_obj(prod_distr_obj);
    prod_distr_obj.clear();
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterDataConverter::convert_thermal_scatter_to_xs_data()
{
  vector<Integer> int_vec, range_vec;
  int_vec.resize(1);
  range_vec.resize(1);
  int_vec[0] = int_lin_lin;

  if( static_cast<int>(incoherent_inelastic_ene_grid_scat_xs_tot.size()) > 0 )
  {
    CrossSectionDataContainer xs_data_obj;
    xs_data_obj.set_reaction_type(reaction_type_inelastic);
    xs_data_obj.set_q_value_mass(temp);
    xs_data_obj.set_q_value(0.0);
    xs_data_obj.set_reaction_flg(0);

    range_vec[0] = static_cast<Integer>(incoherent_inelastic_ene_grid_scat_xs_tot.size());
    xs_data_obj.set_xs_int_data(int_vec);
    xs_data_obj.set_xs_range_data(range_vec);
    xs_data_obj.set_xs_ene_data(incoherent_inelastic_ene_grid_scat_xs_tot);
    xs_data_obj.set_xs_data(incoherent_inelastic_scat_xs_tot);

    nucl_reaction_data_obj.set_xs_data_obj(xs_data_obj);
    xs_data_obj.clear();
  }

  if( static_cast<int>(coherent_elastic_ene_grid.size()) > 0 )
  {
    int mt_coh_ela = reaction_type_elastic;

    CrossSectionDataContainer xs_data_obj;
    xs_data_obj.set_reaction_type(mt_coh_ela);
    xs_data_obj.set_q_value_mass(temp);
    xs_data_obj.set_q_value(0.0);
    xs_data_obj.set_reaction_flg(0);

    range_vec[0] = static_cast<Integer>(coherent_elastic_ene_grid.size());
    xs_data_obj.set_xs_int_data(int_vec);
    xs_data_obj.set_xs_range_data(range_vec);
    xs_data_obj.set_xs_ene_data(coherent_elastic_ene_grid);
    xs_data_obj.set_xs_data(coherent_elastic_scat_xs_tot);

    nucl_reaction_data_obj.set_xs_data_obj(xs_data_obj);
    xs_data_obj.clear();
  }

  if( static_cast<int>(incoherent_elastic_ene_grid.size()) > 0 )
  {
    int mt_incoh_ela = reaction_type_elastic;
    if( static_cast<int>(coherent_elastic_ene_grid.size()) > 0 )
    {
      mt_incoh_ela++;
    }

    CrossSectionDataContainer xs_data_obj;
    xs_data_obj.set_reaction_type(mt_incoh_ela);
    xs_data_obj.set_q_value_mass(temp);
    xs_data_obj.set_q_value(0.0);
    xs_data_obj.set_reaction_flg(0);

    range_vec[0] = static_cast<Integer>(incoherent_elastic_ene_grid.size());
    xs_data_obj.set_xs_int_data(int_vec);
    xs_data_obj.set_xs_range_data(range_vec);
    xs_data_obj.set_xs_ene_data(incoherent_elastic_ene_grid);
    xs_data_obj.set_xs_data(incoherent_elastic_scat_xs);

    nucl_reaction_data_obj.set_xs_data_obj(xs_data_obj);
    xs_data_obj.clear();
  }
}

