#include "ReconResonance/NonResonanceEnergyGridLinearizer.hpp"

using namespace frendy;

//Initialize static const value
const Real8 NonResonanceEnergyGridLinearizer::min_value    = 1.0e-50; //If a<min_value, a can be consider 0.0.
const Real8 NonResonanceEnergyGridLinearizer::min_distance = min_ene_dif * 10.0;

//constructor
NonResonanceEnergyGridLinearizer::NonResonanceEnergyGridLinearizer(void)
{
  clear();
}

//destructor
NonResonanceEnergyGridLinearizer::~NonResonanceEnergyGridLinearizer(void)
{
  clear();
  specified_grid.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void NonResonanceEnergyGridLinearizer::add_non_resonance_grid()
{
  if( add_non_reso_grid_flg != 0 )
  {
    return;
  }
  add_non_reso_grid_flg = 1;

  non_reso_grid.clear();

  vector<Integer> reaction_type = nucl_reaction_data_obj.get_reaction_type();

  input_data_check();

  int i_max = static_cast<int>(reaction_type.size());
  for(int i=0; i<i_max; i++)
  {
    Integer mt_no = reaction_type[i];

    //For xs_data_obj (MF=03)
    add_non_resonance_grid_xs_data(i, mt_no);

    //For radio_product_data_obj (MF=09 or 10)
    add_non_resonance_grid_radio_product_data(i, mt_no);

    //For photon_data_obj (MF=12 or 13 or 23)
    add_non_resonance_grid_photon_data(i, mt_no);
  }

  //Delete overlap energy grid fron non resonanse base grid
  ta_obj.delete_overlap_grid(non_reso_grid);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void NonResonanceEnergyGridLinearizer::add_non_resonance_grid_xs_data(int i, Integer mt_no)
{
  if( xs_data_obj[i].get_reaction_type() != mt_no )
  {
    return;
  }

  if( mt_no == 1 )
  {
    vector<Integer> file_list_each;
    file_list_each.resize(2);
    file_list_each[0] = 3;
    file_list_each[1] = mt_no;
    linearize_file_list.push_back(file_list_each);
    file_list_each.clear();
  }

  if( check_mf_mt(3, mt_no, inela_tot_flg, fis_flg, photo_abs_flg) == 0 )
  {
    vector<Integer> file_list_each;
    file_list_each.resize(2);
    file_list_each[0] = 3;
    file_list_each[1] = mt_no;
    linearize_file_list.push_back(file_list_each);
    file_list_each.clear();

    vector<Integer> xs_nbt_data = xs_data_obj[i].get_xs_range_data();
    vector<Integer> xs_int_data = xs_data_obj[i].get_xs_int_data();
    vector<Real>    xs_ene_data = xs_data_obj[i].get_xs_ene_data();
    vector<Real>    xs_data     = xs_data_obj[i].get_xs_data();
    Real            qi          = xs_data_obj[i].get_q_value();
    if( static_cast<int>(xs_data.size()) > 0 )
    {
      if( mt_no == 1 || mt_no == 2 || mt_no == 18 || mt_no == 102 )
      {
        add_energy_grid_without_resolved_resonance_region
          (non_reso_grid, xs_nbt_data, xs_int_data, xs_ene_data, xs_data, qi);
      }
      else
      {
        add_energy_grid(non_reso_grid, xs_nbt_data, xs_int_data, xs_ene_data, xs_data, qi);
      }
      xs_data_obj[i].set_xs_range_data(xs_nbt_data);
      xs_data_obj[i].set_xs_int_data(xs_int_data);
      xs_data_obj[i].set_xs_ene_data(xs_ene_data);
      xs_data_obj[i].set_xs_data(xs_data);
    }
    xs_nbt_data.clear();
    xs_int_data.clear();
    xs_ene_data.clear();
    xs_data.clear();
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void NonResonanceEnergyGridLinearizer::add_non_resonance_grid_radio_product_data(int i, Integer mt_no)
{
  if( radio_product_data_obj[i].get_reaction_type() != mt_no )
  {
    return;
  }

  Integer mf03_flg = 0;
  if( static_cast<int>(xs_data_obj[i].get_xs_ene_data().size()) > 0 )
  {
    mf03_flg = 1;
  }

  Integer mf09_flg = 0;
  if( static_cast<int>(radio_product_data_obj[i].get_multiplicity_ene_data().size()) > 0 )
  {
    mf09_flg = 1;
  }

  Integer mf10_flg = 0;
  if( static_cast<int>(radio_product_data_obj[i].get_xs_ene_data().size()) > 0 )
  {
    mf10_flg = 1;
  }

  if( mf09_flg == 0 && mf10_flg == 0 )
  {
    return;
  }
  else if( mf03_flg == 0 )
  {
    string class_name = "NonResonanceEnergyGridLinearizer";
    string func_name  = "add_non_resonance_grid_radio_product_data(int i, Integer mt_no)";

    ostringstream oss01;
    oss01 << mt_no;
    string str_data01 = "Reaction type : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("Though this nuclear data has multiplicities or cross sections for");
    err_com.push_back("production of radioactive nuclides, reaction cross secion for");
    err_com.push_back("corresponding reaction type is not contained.");
    err_com.push_back("The nuclear data may not be appropriate.");
    err_obj.output_caution(class_name, func_name, err_com);
  }
  

  if( mt_no == 1 || check_mf_mt( 9, mt_no, inela_tot_flg, fis_flg, photo_abs_flg) == 0 ||
                    check_mf_mt(10, mt_no, inela_tot_flg, fis_flg, photo_abs_flg) == 0 )
  {
    vector<Integer> file_list_each;
    file_list_each.resize(2);
    file_list_each[1] = mt_no;
    if( mf09_flg > 0 &&  check_mf_mt(9, mt_no, inela_tot_flg, fis_flg, photo_abs_flg) == 0 )
    {
      file_list_each[0] =  9;
      linearize_file_list.push_back(file_list_each);
      file_list_each.clear();
    }

    if( mf10_flg > 0 && check_mf_mt(10, mt_no, inela_tot_flg, fis_flg, photo_abs_flg) == 0 )
    {
      file_list_each[0] = 10;
      linearize_file_list.push_back(file_list_each);
    }
    file_list_each.clear();
  }

  if( mf09_flg > 0 && mf03_flg > 0 )
  {
    if( check_mf_mt(9, mt_no, inela_tot_flg, fis_flg, photo_abs_flg) == 0 )
    {
      if( mf10_flg > 0 )
      {
        string class_name = "NonResonanceEnergyGridLinearizer";
        string func_name  = "add_non_resonance_grid_radio_product_data(int i, Integer mt_no)";

        ostringstream oss01;
        oss01 << mt_no;
        string str_data01 = "Reaction type : " + oss01.str();

        vector<string> err_com;
        err_com.push_back(str_data01);
        err_com.push_back("This nuclear data has multiplicities and cross sections for");
        err_com.push_back("production of radioactive nuclides.");
        err_com.push_back("In this program, cross sections for production of radioactive nuclides");
        err_com.push_back("is overwritten to the product of multiplicities for production of");
        err_com.push_back("radio active nuclides and reaction cross section.");
        err_obj.output_caution(class_name, func_name, err_com);
      }

      add_radio_product_data(xs_data_obj[i], radio_product_data_obj[i]);
    }
  }
  else if( mf10_flg > 0 )
  {
    if( check_mf_mt(10, mt_no, inela_tot_flg, fis_flg, photo_abs_flg) == 0 )
    {
      vector<Real>             qi_vec       = radio_product_data_obj[i].get_xs_q_value();
      vector<vector<Integer> > xs_nbt_array = radio_product_data_obj[i].get_xs_range_data();
      vector<vector<Integer> > xs_int_array = radio_product_data_obj[i].get_xs_int_data();
      vector<vector<Real> >    xs_ene_array = radio_product_data_obj[i].get_xs_ene_data();
      vector<vector<Real> >    xs_array     = radio_product_data_obj[i].get_xs_data();

      int j_max = static_cast<int>(xs_array.size());
      if( j_max > 0 )
      {
        for(int j=0; j<j_max; j++)
        {
          add_energy_grid(non_reso_grid, xs_nbt_array[j], xs_int_array[j],
                                         xs_ene_array[j], xs_array[j], qi_vec[j]);
        }
        radio_product_data_obj[i].set_xs_range_data(xs_nbt_array);
        radio_product_data_obj[i].set_xs_int_data(xs_int_array);
        radio_product_data_obj[i].set_xs_ene_data(xs_ene_array);
        radio_product_data_obj[i].set_xs_data(xs_array);
      }
      clr_vec.clear_vec_array2_int(xs_nbt_array);
      clr_vec.clear_vec_array2_int(xs_int_array);
      clr_vec.clear_vec_array2_real(xs_ene_array);
      clr_vec.clear_vec_array2_real(xs_array);
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void NonResonanceEnergyGridLinearizer::add_radio_product_data(CrossSectionDataContainer& xs_obj,
                                                              RadioactiveProductDataContainer& rad_obj)
{
  vector<Integer>          xs_nbt_data     = xs_obj.get_xs_range_data();
  vector<Integer>          xs_int_data     = xs_obj.get_xs_int_data();
  vector<Real>             xs_ene_data     = xs_obj.get_xs_ene_data();
  vector<Real>             xs_data         = xs_obj.get_xs_data();
  vector<Real>             q_vec           = rad_obj.get_multiplicity_q_value();
  vector<vector<Integer> > multi_nbt_array = rad_obj.get_multiplicity_range_data();
  vector<vector<Integer> > multi_int_array = rad_obj.get_multiplicity_int_data();
  vector<vector<Real> >    multi_ene_array = rad_obj.get_multiplicity_ene_data();
  vector<vector<Real> >    multi_array     = rad_obj.get_multiplicity_data();

  int j_max = static_cast<int>(multi_ene_array.size());
  vector<vector<Integer> > xs_nbt_array, xs_int_array;
  vector<vector<Real> >    xs_ene_array, xs_array;
  xs_nbt_array.resize(j_max);
  xs_int_array.resize(j_max);
  xs_ene_array.resize(j_max);
  xs_array.resize(j_max);
  for(int j=0; j<j_max; j++)
  {
    xs_nbt_array[j] = xs_nbt_data;
    xs_int_array[j] = xs_int_data;
    xs_ene_array[j] = xs_ene_data;
    xs_array[j]     = xs_data;
    add_energy_grid(non_reso_grid,
                    xs_nbt_array[j],    xs_int_array[j],    xs_ene_array[j],    xs_array[j], q_vec[j],
                    multi_nbt_array[j], multi_int_array[j], multi_ene_array[j], multi_array[j]);
  }

  //Copy linearized data to Cross Sections for Production of Radioactive Nucliedes
  rad_obj.set_xs_state_no_target(rad_obj.get_multiplicity_state_no_target());
  rad_obj.set_xs_state_no_product(rad_obj.get_multiplicity_state_no_product());
  rad_obj.set_xs_q_value_mass(rad_obj.get_multiplicity_q_value_mass());
  rad_obj.set_xs_mat_data_product(rad_obj.get_multiplicity_mat_data_product());

  rad_obj.set_xs_q_value(q_vec);
  rad_obj.set_xs_range_data(xs_nbt_array);
  rad_obj.set_xs_int_data(xs_int_array);
  rad_obj.set_xs_ene_data(xs_ene_array);
  rad_obj.set_xs_data(xs_array);

  //Copy linearized multiplicity data
  rad_obj.set_multiplicity_range_data(multi_nbt_array);
  rad_obj.set_multiplicity_int_data(multi_int_array);
  rad_obj.set_multiplicity_ene_data(multi_ene_array);
  rad_obj.set_multiplicity_data(multi_array);

  //Remove vector data
  clr_vec.clear_vec_array2_int(multi_nbt_array);
  clr_vec.clear_vec_array2_int(multi_int_array);
  clr_vec.clear_vec_array2_real(multi_ene_array);
  clr_vec.clear_vec_array2_real(multi_array);
  clr_vec.clear_vec_array2_int(xs_nbt_array);
  clr_vec.clear_vec_array2_int(xs_int_array);
  clr_vec.clear_vec_array2_real(xs_ene_array);
  clr_vec.clear_vec_array2_real(xs_array);
  xs_nbt_data.clear();
  xs_int_data.clear();
  xs_ene_data.clear();
  xs_data.clear();
  q_vec.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void NonResonanceEnergyGridLinearizer::add_non_resonance_grid_photon_data(int i, Integer mt_no)
{
  if( photon_data_obj[i].get_reaction_type() != mt_no )
  {
    return;
  }

  Integer mf03_flg = 0;
  if( static_cast<int>(xs_data_obj[i].get_xs_ene_data().size()) > 0 )
  {
    mf03_flg = 1;
  }

  Integer mf12_flg = 0;
  if( static_cast<int>(photon_data_obj[i].get_multiplicity_tot_ene_data().size()) > 0 )
  {
    mf12_flg = 1;
  }

  Integer mf13_flg = 0;
  if( static_cast<int>(photon_data_obj[i].get_photon_production_xs_tot_ene_data().size()) > 0 )
  {
    mf13_flg = 1;
  }

  Integer mf23_flg = 0;
  if( static_cast<int>(photon_data_obj[i].get_photon_interaction_xs_ene_data().size()) > 0 )
  {
    mf23_flg = 1;
  }

  if( mf12_flg == 0 && mf13_flg == 0 && mf23_flg == 0 )
  {
    return;
  }
  else if( mf03_flg == 0 )
  {
    string class_name = "NonResonanceEnergyGridLinearizer";
    string func_name  = "add_non_resonance_grid_photon_data(int i, Integer mt_no)";

    ostringstream oss01;
    oss01 << mt_no;
    string str_data01 = "Reaction type : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("Though this nuclear data has multiplicities or cross sections for");
    err_com.push_back("photon production, reaction cross secion for correspondint");
    err_com.push_back("reaction type is not contained.");
    err_com.push_back("The nuclear data may not be appropriate.");
    err_obj.output_caution(class_name, func_name, err_com);
  }

  if( mt_no == 1 || check_mf_mt(12, mt_no, inela_tot_flg, fis_flg, photo_abs_flg) == 0 ||
                    check_mf_mt(13, mt_no, inela_tot_flg, fis_flg, photo_abs_flg) == 0 ||
                    check_mf_mt(23, mt_no, inela_tot_flg, fis_flg, photo_abs_flg) == 0 )
  {
    vector<Integer> file_list_each;
    file_list_each.resize(2);
    file_list_each[1] = mt_no;

    if( mf12_flg > 0 && check_mf_mt(12, mt_no, inela_tot_flg, fis_flg, photo_abs_flg) == 0 )
    {
      file_list_each[0] = 12;
      linearize_file_list.push_back(file_list_each);
    }

    if( mf13_flg > 0 && check_mf_mt(13, mt_no, inela_tot_flg, fis_flg, photo_abs_flg) == 0 )
    {
      file_list_each[0] = 13;
      linearize_file_list.push_back(file_list_each);
    }

    if( mf23_flg > 0 && check_mf_mt(23, mt_no, inela_tot_flg, fis_flg, photo_abs_flg) == 0 )
    {
      file_list_each[0] = 23;
      linearize_file_list.push_back(file_list_each);
    }

    file_list_each.clear();
  }

  if( mf12_flg > 0 && check_mf_mt(12, mt_no, inela_tot_flg, fis_flg, photo_abs_flg) == 0 )
  {
    //For photon_data_obj MF=12)
    Real qi = 0.0;
    vector<Integer> multi_tot_nbt_data = photon_data_obj[i].get_multiplicity_tot_range_data();
    vector<Integer> multi_tot_int_data = photon_data_obj[i].get_multiplicity_tot_int_data();
    vector<Real>    multi_tot_ene_data = photon_data_obj[i].get_multiplicity_tot_ene_data();
    vector<Real>    multi_tot_data     = photon_data_obj[i].get_multiplicity_tot_data();

    add_energy_grid(non_reso_grid, multi_tot_nbt_data, multi_tot_int_data,
                                   multi_tot_ene_data, multi_tot_data, qi);
    photon_data_obj[i].set_multiplicity_tot_range_data(multi_tot_nbt_data);
    photon_data_obj[i].set_multiplicity_tot_int_data(multi_tot_int_data);
    photon_data_obj[i].set_multiplicity_tot_ene_data(multi_tot_ene_data);
    photon_data_obj[i].set_multiplicity_tot_data(multi_tot_data);

    if( static_cast<int>(photon_data_obj[i].get_multiplicity_binding_ene_flg().size()) == 1 )
    {
        vector<vector<Integer> > multi_nbt_array, multi_int_array;
        vector<vector<Real> >    multi_ene_array, multi_array;
        multi_nbt_array.push_back(multi_tot_nbt_data);
        multi_int_array.push_back(multi_tot_int_data);
        multi_ene_array.push_back(multi_tot_ene_data);
        multi_array.push_back(multi_tot_data);
        photon_data_obj[i].set_multiplicity_range_data(multi_nbt_array);
        photon_data_obj[i].set_multiplicity_int_data(multi_int_array);
        photon_data_obj[i].set_multiplicity_ene_data(multi_ene_array);
        photon_data_obj[i].set_multiplicity_data(multi_array);
        clr_vec.clear_vec_array2_int(multi_nbt_array);
        clr_vec.clear_vec_array2_int(multi_int_array);
        clr_vec.clear_vec_array2_real(multi_ene_array);
        clr_vec.clear_vec_array2_real(multi_array);
    }
    multi_tot_nbt_data.clear();
    multi_tot_int_data.clear();
    multi_tot_ene_data.clear();
    multi_tot_data.clear();
  }

  if( mf13_flg > 0 && check_mf_mt(13, mt_no, inela_tot_flg, fis_flg, photo_abs_flg) == 0 )
  {
    //For photon_data_obj (MF=13)
    Real qi = 0.0;
    vector<Integer> multi_nbt_data = photon_data_obj[i].get_photon_production_xs_tot_range_data();
    vector<Integer> multi_int_data = photon_data_obj[i].get_photon_production_xs_tot_int_data();
    vector<Real>    multi_ene_data = photon_data_obj[i].get_photon_production_xs_tot_ene_data();
    vector<Real>    multi_data     = photon_data_obj[i].get_photon_production_xs_tot_data();

    if( static_cast<int>(multi_data.size()) > 0 )
    {
      add_energy_grid(non_reso_grid, multi_nbt_data, multi_int_data, multi_ene_data, multi_data, qi);

      photon_data_obj[i].set_photon_production_xs_tot_range_data(multi_nbt_data);
      photon_data_obj[i].set_photon_production_xs_tot_int_data(multi_int_data);
      photon_data_obj[i].set_photon_production_xs_tot_ene_data(multi_ene_data);
      photon_data_obj[i].set_photon_production_xs_tot_data(multi_data);
    }
    multi_nbt_data.clear();
    multi_int_data.clear();
    multi_ene_data.clear();
    multi_data.clear();

    vector<vector<Integer> > multi_nbt_array = photon_data_obj[i].get_photon_production_xs_range_data();
    vector<vector<Integer> > multi_int_array = photon_data_obj[i].get_photon_production_xs_int_data();
    vector<vector<Real> >    multi_ene_array = photon_data_obj[i].get_photon_production_xs_ene_data();
    vector<vector<Real> >    multi_array     = photon_data_obj[i].get_photon_production_xs_data();
    int j_max = static_cast<int>(multi_array.size());
    if( j_max > 0 )
    {
      for(int j=0; j<j_max; j++)
      {
        if( static_cast<int>(multi_array[j].size()) > 0 )
        {
          add_energy_grid(non_reso_grid, multi_nbt_array[j], multi_int_array[j],
                                         multi_ene_array[j], multi_array[j], qi);
        }
      }

      photon_data_obj[i].set_photon_production_xs_range_data(multi_nbt_array);
      photon_data_obj[i].set_photon_production_xs_int_data(multi_int_array);
      photon_data_obj[i].set_photon_production_xs_ene_data(multi_ene_array);
      photon_data_obj[i].set_photon_production_xs_data(multi_array);
    }
    clr_vec.clear_vec_array2_int(multi_nbt_array);
    clr_vec.clear_vec_array2_int(multi_int_array);
    clr_vec.clear_vec_array2_real(multi_ene_array);
    clr_vec.clear_vec_array2_real(multi_array);
  }

  //For photon_data_obj (MF=23)
  if( mf23_flg > 0 && check_mf_mt(23, mt_no, inela_tot_flg, fis_flg, photo_abs_flg) == 0 )
  {
    Real qi = 0.0;
    vector<Integer> xs_nbt_data = photon_data_obj[i].get_photon_interaction_xs_range_data();
    vector<Integer> xs_int_data = photon_data_obj[i].get_photon_interaction_xs_int_data();
    vector<Real>    xs_ene_data = photon_data_obj[i].get_photon_interaction_xs_ene_data();
    vector<Real>    xs_data     = photon_data_obj[i].get_photon_interaction_xs_data();
    if( static_cast<int>(xs_data.size()) > 0 )
    {
      add_energy_grid(non_reso_grid, xs_nbt_data, xs_int_data, xs_ene_data, xs_data, qi);

      photon_data_obj[i].set_photon_interaction_xs_range_data(xs_nbt_data);
      photon_data_obj[i].set_photon_interaction_xs_int_data(xs_int_data);
      photon_data_obj[i].set_photon_interaction_xs_ene_data(xs_ene_data);
      photon_data_obj[i].set_photon_interaction_xs_data(xs_data);
    }
    xs_nbt_data.clear();
    xs_int_data.clear();
    xs_ene_data.clear();
    xs_data.clear();
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void NonResonanceEnergyGridLinearizer::input_data_check()
{
  if( error_int_value < min_value )
  {
    Real error_int_ori   = error_int_value;
         error_int_value = error_value / 20000.0;

    if( error_int_value >= 0.0 )
    {
      string class_name = "NonResonanceEnergyGridLinearizer";
      string func_name  = "input_data_check()";

      ostringstream oss01, oss02, oss03;
      oss01 << error_int_ori;
      oss02 << error_int_value;
      oss03 << min_ene_dif;
      string str_data01 = "Integrate error value          : " + oss01.str();
      string str_data02 = "Modified integrate error value : " + oss02.str();
      string str_data03 = "Minimum difference             : " + oss03.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);

      err_com.push_back("Integral error value is less than the minimum difference.");
      err_com.push_back("Integral error value is modified.");
      //err_obj.output_caution(class_name, func_name, err_com);
    }
  }

  if( error_value < min_ene_dif )
  {
    string class_name = "NonResonanceEnergyGridLinearizer";
    string func_name  = "input_data_check()";

    ostringstream oss01, oss02;
    oss01 << error_value;
    oss02 << min_ene_dif;
    string str_data01 = "Error value          : " + oss01.str();
    string str_data02 = "Minimum difference   : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);

    if( error_value < 0.0 )
    {
      err_com.push_back("Please set the positive error value.");
    }
    else if( error_value < min_ene_dif )
    {
      err_com.push_back("Error value is less than the minimum difference.");
      err_com.push_back("Please set more large value.");
    }
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Integer NonResonanceEnergyGridLinearizer::check_mf_mt(Integer mf, Integer mt, 
                                                      Integer inela_tot_val, Integer fis_val,
                                                      Integer photo_abs_val)
{
  Integer chk_flg = 0;

  if( mt == unassigned_mt_no )
  {
    chk_flg = -10;
    return chk_flg;
  }

  //MF = 03 :Reaction cross section (MF=03)
  //MF = 09 :Multiplicities of radioactive products (MF=09)
  //MF = 10 :Cross section for production of radioactive nuclides (MF=10)
  //MF = 12 :Photon production (MF=12)
  //MF = 13 :Photon production cross section (MF=13)
  //MF = 23 :Smooth photon interaction cross section (MF=23)
  if( mf==3 || mf==9 || mf==10 || mf==12 || mf==13 || mf==23 )
  {
    if( mt==460 || mt==501 )
    {
      //mt = 460 : Unassigned
      //mt = 501 : Total photon interaction cross section
      chk_flg = -1;
    }
    else if( mt==522 && photo_abs_val>0 )
    {
      //mt = 522 : Photoelectric absorption
      chk_flg = -1;
    } 
    else if( mf==3 )
    {
      if( mt==1 || mt==3 || mt==101 || mt==120 || mt==151 )
      {
        //mt =   1 : (n,total)         - Total of cross section
        //mt =   3 : (n,non-elastic)   - Non-elastic scatteringcross section
        //mt = 101 : (n,disappearance)
        //mt = 120 : Unassigned
        //mt = 151 : (n, resonance)
        chk_flg = -1;
      }
      else if( mt==4 && inela_tot_val > 0 )
      {
        //mt = 4 : (z,n) - Inelastic scattering cross section
        chk_flg = -1;
      }
      else if( mt==18 && fis_val > 0 )
      {
        //mt = 18 : (z,f) - Total of fission cross section
        chk_flg = -1;
      }
      else if( (mt>=251 && mt<=300) && mt != 261 ) 
      {
        //vaciour elastic scattering parameters
        chk_flg = -1;
      }
      else if( mt>=451 && mt<600 ) 
      {
        //mt = 451 - 599 : Other data
        chk_flg = -1;
      }
      else if( mt>850 && mt<=870 ) 
      {
        //mt = 851 - 870 : Lumped reaction covariances
        chk_flg = -1;
      }
      else if( mt>891 ) 
      {
        //mt = 892 - 999 : Unassigned
        chk_flg = -1;
      }
    }
  }
  else
  {
    chk_flg = -1;
  }

  return chk_flg;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void NonResonanceEnergyGridLinearizer::add_energy_grid_without_resolved_resonance_region
                                         (vector<Real8>&   base_grid, 
                                          vector<Integer>& xs_nbt_data, vector<Integer>& xs_int_data,
                                          vector<Real>&    xs_ene_data, vector<Real>&    xs_data, Real& qi)
{
  if( reso_eh < min_ene_val )
  {
    add_energy_grid(base_grid, xs_nbt_data,    xs_int_data,    xs_ene_data,    xs_data, qi);
    return;
  }

  //Set dummy multi data
  vector<Integer> multi_nbt_data, multi_int_data;
  vector<Real>    multi_ene_data, multi_data;
  multi_nbt_data.clear();
  multi_int_data.clear();
  multi_ene_data.clear();
  multi_data.clear();

  vector<Real> xs_ene_data_ori = xs_ene_data;
  linealize_xs_data(xs_nbt_data,    xs_int_data,    xs_ene_data,    xs_data, qi,
                    multi_nbt_data, multi_int_data, multi_ene_data, multi_data);

  //Add linearized grid to base grid
  Real8 reso_eh_ori = digit_obj.get_adjusted_value(reso_eh, sig_fig, -1.0);
  Real8 reso_el_mod = digit_obj.get_adjusted_value(reso_el, sig_fig, -1.0) * (1.0 - min_ene_dif);
  Real8 reso_eh_mod = reso_eh * (1.0 + min_ene_dif);

  int i_max = static_cast<int>(xs_ene_data.size());
  for(int i=0; i<i_max; i++)
  {
    Real8 ene_val = static_cast<Real8>(xs_ene_data[i]);

    if( ene_val < reso_el_mod || reso_eh_mod < ene_val )
    {
      base_grid.push_back(ene_val);
    }
  }

  //Add original energy grid to base grid
  i_max = static_cast<int>(xs_ene_data_ori.size());
  for(int i=0; i<i_max; i++)
  {
    Real8 ene_val = static_cast<Real8>(xs_ene_data_ori[i]);
    if( fabs(ene_val - reso_eh_ori) > fabs(min_ene_dif * reso_eh_ori) )
    {
      base_grid.push_back(static_cast<Real8>(ene_val));
    }
  }
  xs_ene_data_ori.clear();

  //Add specified energy grid to base grid
  i_max = static_cast<int>(specified_grid.size());
  for(int i=0; i<i_max; i++)
  {
    base_grid.push_back(specified_grid[i]);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void NonResonanceEnergyGridLinearizer::add_energy_grid
                                        (vector<Real8>& base_grid, 
                                         vector<Integer>& xs_nbt_data,    vector<Integer>& xs_int_data,
                                         vector<Real>&    xs_ene_data,    vector<Real>&    xs_data,
                                         Real& qi)
{
  vector<Integer> multi_nbt_data, multi_int_data;
  vector<Real>    multi_ene_data, multi_data;
  multi_nbt_data.clear();
  multi_int_data.clear();
  multi_ene_data.clear();
  multi_data.clear();

  add_energy_grid(base_grid, xs_nbt_data,    xs_int_data,    xs_ene_data,    xs_data, qi,
                             multi_nbt_data, multi_int_data, multi_ene_data, multi_data);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void NonResonanceEnergyGridLinearizer::add_energy_grid
                                        (vector<Real8>& base_grid, 
                                         vector<Integer>& xs_nbt_data,    vector<Integer>& xs_int_data,
                                         vector<Real>&    xs_ene_data,    vector<Real>&    xs_data,
                                         Real& qi,
                                         vector<Integer>& multi_nbt_data, vector<Integer>& multi_int_data,
                                         vector<Real>&    multi_ene_data, vector<Real>&    multi_data)
{
  linealize_xs_data(xs_nbt_data,    xs_int_data,    xs_ene_data,    xs_data, qi,
                    multi_nbt_data, multi_int_data, multi_ene_data, multi_data);

  //Add linearized grid to base grid
  int i_max = static_cast<int>(xs_ene_data.size());
  for(int i=0; i<i_max; i++)
  {
    base_grid.push_back(static_cast<Real8>(xs_ene_data[i]));
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void NonResonanceEnergyGridLinearizer::linealize_xs_data
                                         (vector<Integer>& xs_nbt_data,    vector<Integer>& xs_int_data,
                                          vector<Real>&    xs_ene_data,    vector<Real>&    xs_data,
                                          Real& qi,
                                          vector<Integer>& multi_nbt_data, vector<Integer>& multi_int_data,
                                          vector<Real>&    multi_ene_data, vector<Real>&    multi_data)
{
  //Calculation the threshold by the Q value
  Integer q_flg;
  Real8   threshold;
  calc_threshold(threshold, qi, q_flg);

  vector<Real8> xs_ene_double, xs_double, multi_ene_double, multi_double;
  int i_max = static_cast<int>(xs_ene_data.size());
  xs_ene_double.resize(i_max);
  xs_double.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    xs_ene_double[i] = static_cast<Real8>(xs_ene_data[i]);
    xs_double[i]     = static_cast<Real8>(xs_data[i]);
  }

  //Adjust energy grid
  adjust_energy_grid(xs_nbt_data, xs_int_data, xs_ene_double, xs_double, threshold);

  //Add additional energy grid (1.0e+x, 2.0e+x, 5.0e+x)
  add_additional_energy_grid(xs_nbt_data, xs_int_data, xs_ene_double, xs_double, threshold);

  //Add user specified energy grid (0.0253, and so on)
  add_user_specified_energy_grid(xs_nbt_data, xs_int_data, xs_ene_double, xs_double, threshold);

  //Adjust energy grid
  adjust_energy_grid(xs_nbt_data, xs_int_data, xs_ene_double, xs_double, threshold);

  i_max = static_cast<int>(multi_ene_data.size());
  if( i_max > 0 )
  {
    multi_ene_double.resize(i_max);
    multi_double.resize(i_max);
    for(int i=0; i<i_max; i++)
    {
      multi_ene_double[i] = static_cast<Real8>(multi_ene_data[i]);
      multi_double[i]     = static_cast<Real8>(multi_data[i]);
    }

    //Adjust energy grid
    adjust_energy_grid(multi_nbt_data, multi_int_data, multi_ene_double, multi_double, threshold);

    //Add additional energy grid (1.0e+x, 2.0e+x, 5.0e+x)
    add_additional_energy_grid(multi_nbt_data, multi_int_data, multi_ene_double, multi_double, threshold);

    //Add user specified energy grid (0.0253, and so on)
    add_user_specified_energy_grid(multi_nbt_data, multi_int_data, multi_ene_double, multi_double, threshold);

    //Adjust energy grid
    adjust_energy_grid(multi_nbt_data, multi_int_data, multi_ene_double, multi_double, threshold);
  }

  //Add middle point when the energy grid distance is large. 
  add_middle_energy_grid(xs_nbt_data,    xs_int_data,    xs_ene_double,    xs_double,
                         multi_nbt_data, multi_int_data, multi_ene_double, multi_double, threshold);

  //Change all xs_int_data to linear-linear(int_val = 2).
  i_max = static_cast<int>(xs_ene_double.size());
  xs_nbt_data.clear();
  xs_int_data.clear();
  xs_nbt_data.push_back(static_cast<Integer>(i_max));
  xs_int_data.push_back(int_lin_lin);

  //Add base grid
  xs_ene_data.clear();
  xs_data.clear();
  xs_ene_data.resize(i_max);
  xs_data.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    xs_ene_data[i] = static_cast<Real>(xs_ene_double[i]);
    xs_data[i]     = static_cast<Real>(xs_double[i]);
  }
  xs_ene_double.clear();
  xs_double.clear();

  ta_obj.delete_overlap_grid(xs_nbt_data, xs_int_data, xs_ene_data, xs_data);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void NonResonanceEnergyGridLinearizer::adjust_energy_grid
                                         (vector<Integer>& xs_nbt_data, vector<Integer>& xs_int_data,
                                          vector<Real8>&   xs_ene_data, vector<Real8>&   xs_data,
                                          Real& threshold)
{
  vector<Real8> new_ene, new_xs;
  new_ene.clear();
  new_xs.clear();

  //Adjust the energy grid and the cross section
  int   pre_pos;
  Real8 ene_cur, xs_cur, ene_pre, xs_pre, ene_dif;
  int ene_flg = 0;
  int i_max   = static_cast<int>(xs_ene_data.size());
  for(int i=0; i<i_max; i++)
  {
    Integer adjust_flg = 0;
    ene_cur = xs_ene_data[i];
    xs_cur  = xs_data[i];

    if( xs_cur < min_value && ene_flg == 0 && i < i_max - 1 )
    {
      if( xs_data[i+1] < min_value )
      {
        ene_pre = ene_cur;
        xs_pre  = xs_cur;
        continue;
      }
    }

    //Adjust E[i] when E[i] is lower than Q value.
    if( ene_cur <= threshold )
    {
      adjust_flg = 1;
      ene_cur    = digit_obj.get_adjusted_value(threshold, sig_fig, +1.0);
    }

    //Adjust the energy distance between E[i] and E[i-1].
    if( i > 0 && static_cast<int>(new_ene.size()) > 0 )
    {
      if( fabs(xs_cur - xs_pre) > fabs(xs_cur*min_sig_dif) || fabs(xs_cur) < min_value )
      {
        ene_dif = fabs(ene_pre*min_distance);
        if( fabs(ene_cur - ene_pre) <= ene_dif )
        {
          //If E[i] = E[i-1], E[i] and E[i-1] were modified. 
          //add x+x_dif
          Real8 ene_pre_ori = ene_pre;
          Real8 xs_pre_ori  = xs_pre;
          ene_pre = digit_obj.get_adjusted_value(ene_pre, sig_fig, -1.0);
          ti_obj.interpolation_tab1_in_range(ene_pre, xs_pre, xs_nbt_data, xs_int_data,
                                             xs_ene_data, xs_data, threshold);
          pre_pos = static_cast<int>(new_ene.size()) - 1;
          new_ene[pre_pos] = ene_pre;
          new_xs[pre_pos]  = xs_pre;
          new_ene.push_back(ene_pre_ori);
          new_xs.push_back(xs_pre_ori);
          new_ene.push_back(ene_cur);
          new_xs.push_back(xs_cur);

          //add x-x_dif
          adjust_flg = 1;
          ene_cur    = digit_obj.get_adjusted_value(ene_cur, sig_fig, +1.0);
        }
        else
        {
          if( ene_cur - ene_pre <= ene_dif )
          {
            adjust_flg = 1;
            ene_cur    = digit_obj.get_adjusted_value(ene_pre, sig_fig, +1.0);
            while( ene_cur - ene_pre <= ene_dif )
            {
              ene_cur  = digit_obj.get_adjusted_value(ene_cur, sig_fig, +1.0);
            }
          }
        }
      }
    }

    //Adjust xs_cur since grid_cur was adjusted by previous while loops.
    if( adjust_flg > 0 )
    {
      ti_obj.interpolation_tab1_in_range(ene_cur, xs_cur, xs_nbt_data, xs_int_data,
                                         xs_ene_data, xs_data, threshold);
    }
    new_ene.push_back(ene_cur);
    new_xs.push_back(xs_cur);
    ene_pre = ene_cur;
    xs_pre  = xs_cur;

    ene_flg++;
  }

  //Renewal nbt_data and int_data
  renewal_interpolation_scheme_list(xs_nbt_data, xs_int_data, xs_ene_data, new_ene);

  xs_ene_data = new_ene;
  xs_data     = new_xs;
  new_ene.clear();
  new_xs.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void NonResonanceEnergyGridLinearizer::calc_threshold(Real8& threshold, Real& qi, Integer& q_flg)
{
  Real    awi, awr;
  Real8   awrx;

  q_flg = 0;
  if( fabs(qi) > min_value )
  {
    q_flg = 1;

    awr =  nucl_data_obj.get_general_data_obj().get_mass();
    awi =  nucl_data_obj.get_general_data_obj().get_mass_projectile();
    if(fabs(awi) > min_value )
    {
      awrx      = static_cast<Real8>(awr)/static_cast<Real8>(awi);
      threshold = -1.0 * static_cast<Real8>(qi) * (awrx+1.0) / awrx;
    }
    else
    {
      threshold = -1.0 * static_cast<Real8>(qi);
    }
    threshold = digit_obj.get_adjusted_value(threshold, sig_fig, +1.0);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void NonResonanceEnergyGridLinearizer::add_additional_energy_grid
                                         (vector<Integer>& xs_nbt_data, vector<Integer>& xs_int_data,
                                          vector<Real8>&   xs_ene_data, vector<Real8>&   xs_data,
                                          Real& threshold)
{
  vector<Real8> new_ene, new_xs;
  new_ene.clear();
  new_xs.clear();

  Real8 xs_adj, ene_adj;
  vector<Real8> multi_value;
  multi_value.push_back(1.0);
  multi_value.push_back(2.0);
  multi_value.push_back(5.0);

  int i_max  = static_cast<int>(xs_ene_data.size());
  int j_max  = static_cast<int>(multi_value.size());
  for(int i=0; i<i_max; i++)
  {
    if( i > 0 )
    {
      Integer add_flg = 1;
      Integer digit   = digit_obj.get_digit_number(xs_ene_data[i-1]);
      Real8 ene       = pow(10.0, digit);
      while( xs_ene_data[i] > ene || add_flg > 0 )
      {
        add_flg = 0;

        //Add a*1.0e+x or 2.0e+x or 5.0e+x
        for(int j=0; j<j_max; j++)
        {
          ene_adj = ene*multi_value[j];
          if( xs_ene_data[i] > ene_adj && xs_ene_data[i-1] < ene_adj )
          {
            ti_obj.interpolation_tab1_in_range(ene_adj, xs_adj, xs_nbt_data, xs_int_data,
                                               xs_ene_data, xs_data, threshold);
            new_ene.push_back(ene_adj);
            new_xs.push_back(xs_adj);
            add_flg=1;
          }
        }

        ene = ene*10.0;
      }
    }
    new_ene.push_back(xs_ene_data[i]);
    new_xs.push_back(xs_data[i]);
  }

  //Renewal xs_nbt_data and xs_int_data
  renewal_interpolation_scheme_list(xs_nbt_data, xs_int_data, xs_ene_data, new_ene);

  xs_ene_data = new_ene;
  xs_data     = new_xs;
  new_ene.clear();
  new_xs.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void NonResonanceEnergyGridLinearizer::add_user_specified_energy_grid
                                         (vector<Integer>& xs_nbt_data, vector<Integer>& xs_int_data,
                                          vector<Real8>&   xs_ene_data, vector<Real8>&   xs_data,
                                          Real& threshold)
{
  Integer grid_chk = 0;
  int     grid_no  = 0;
  int     grid_max = static_cast<int>(specified_grid.size());
  int     i_max    = static_cast<int>(xs_ene_data.size());
  if( i_max > 0 )
  {
    for(int i=0; i<grid_max; i++)
    {
      if(xs_ene_data[0] < specified_grid[i])
      {
        grid_chk = 1;
        grid_no  = i;
        break;
      }
    }
  }
  if( grid_chk == 0 )
  {
    return;
  }
  
  vector<Real8>   new_ene, new_xs;
  new_ene.clear();
  new_xs.clear();

  Real8 xs_adj, ene_adj;
  ene_adj = specified_grid[grid_no];

  for(int i=0; i<i_max; i++)
  {
    if( i > 0 )
    {
      Integer add_flg = 1;
      while( grid_no < grid_max && add_flg > 0 )
      {
        add_flg = 0;

        if( xs_ene_data[i] > ene_adj && xs_ene_data[i-1] < ene_adj )
        {
          ti_obj.interpolation_tab1_in_range(ene_adj, xs_adj, xs_nbt_data, xs_int_data,
                                             xs_ene_data, xs_data, threshold);
          new_ene.push_back(ene_adj);
          new_xs.push_back(xs_adj);
          grid_no++;

          if( grid_no < grid_max )
          {
            ene_adj = specified_grid[grid_no];
            add_flg=1;
          }
        }
        else if( xs_ene_data[i] > specified_grid[grid_no] ) //If the identical energy grid was exist.
        {
          grid_no++;

          if( grid_no < grid_max )
          {
            ene_adj = specified_grid[grid_no];
            add_flg=1;
          }
        }
      }
    }
    new_ene.push_back(xs_ene_data[i]);
    new_xs.push_back(xs_data[i]);
  }

  //Renewal xs_nbt_data and xs_int_data
  renewal_interpolation_scheme_list(xs_nbt_data, xs_int_data, xs_ene_data, new_ene);

  xs_ene_data = new_ene;
  xs_data     = new_xs;
  new_ene.clear();
  new_xs.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void NonResonanceEnergyGridLinearizer::add_middle_energy_grid
                                         (vector<Integer>& xs_nbt_data,    vector<Integer>& xs_int_data,
                                          vector<Real8>&   xs_ene_data,    vector<Real8>&   xs_data,
                                          Real& threshold)
{
  vector<Integer> multi_nbt_data, multi_int_data;
  vector<Real8>   multi_ene_data, multi_data;
  multi_nbt_data.clear();
  multi_int_data.clear();
  multi_ene_data.clear();
  multi_data.clear();

  add_middle_energy_grid(xs_nbt_data,    xs_int_data,    xs_ene_data,    xs_data,
                         multi_nbt_data, multi_int_data, multi_ene_data, multi_data, threshold);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void NonResonanceEnergyGridLinearizer::add_middle_energy_grid
                                         (vector<Integer>& xs_nbt_data,    vector<Integer>& xs_int_data,
                                          vector<Real8>&   xs_ene_data,    vector<Real8>&   xs_data,
                                          vector<Integer>& multi_nbt_data, vector<Integer>& multi_int_data,
                                          vector<Real8>&   multi_ene_data, vector<Real8>&   multi_data,
                                          Real& threshold)
{
  Real8         mid_ene, mid_xs;
  vector<Real8> new_ene, new_xs, new_ene_part, new_xs_part;
  new_ene.clear();
  new_xs.clear();
  new_ene_part.clear();
  new_xs_part.clear();

  Real8 err_line = 1.0+sqrt(5.3*error_value);

  int     j;
  int     i_max     = static_cast<int>(xs_ene_data.size());
  int     range     = 0; 
  int     range_max = static_cast<int>(xs_nbt_data.size()); 
  Integer int_val   = xs_int_data[0];
  Integer int_chk;

  Real8 xs_cur, xs_pre;
  xs_cur = xs_calc_obj.calc_xs_data_double(xs_ene_data[0], xs_data[0], multi_nbt_data, multi_int_data,
                                                                       multi_ene_data, multi_data);
  new_ene.push_back(xs_ene_data[0]);
  new_xs.push_back(xs_cur);
  while(xs_nbt_data[range] < 1)
  {
    range++;
    if( range >= range_max )
    {
      int_val = xs_int_data[range_max-1];
      break;
    }
    else
    {
      int_val = xs_int_data[range];
    }
  }
  
  for(int i=1; i<i_max; i++)
  {
    while(xs_nbt_data[range] < i+1)
    {
      range++;
      int_val = xs_int_data[range];
      if( range >= range_max )
      {
        int_val = xs_int_data[range_max-1];
        break;
      }
      else
      {
        int_val = xs_int_data[range];
      }
    }

    xs_pre = xs_calc_obj.calc_xs_data_double(xs_ene_data[i-1], xs_data[i-1], multi_nbt_data, multi_int_data,
                                                                             multi_ene_data, multi_data);
    xs_cur = xs_calc_obj.calc_xs_data_double(xs_ene_data[i], xs_data[i], multi_nbt_data, multi_int_data,
                                                                         multi_ene_data, multi_data);
    new_ene_part.push_back(xs_ene_data[i-1]);
    new_xs_part.push_back(xs_pre);
    new_ene_part.push_back(xs_ene_data[i]);
    new_xs_part.push_back(xs_cur);
    
    j = 1;
    int_chk = comp_interpolation_value(j, int_val, new_ene_part, new_xs_part,
                                       multi_nbt_data, multi_int_data, multi_ene_data, multi_data,
                                       mid_ene, mid_xs, err_line, threshold);

    while( int_chk < 0 || j < static_cast<int>(new_ene_part.size()-1))
    {
      if( int_chk == 0 )
      {
        j++;
      }
      else
      {
        insert_middle_energy_grid(j, int_val, new_ene_part, new_xs_part, mid_ene, mid_xs);
      }
      int_chk = comp_interpolation_value(j, int_val, new_ene_part, new_xs_part,
                                         multi_nbt_data, multi_int_data, multi_ene_data, multi_data,
                                         mid_ene, mid_xs, err_line, threshold);
    }
    add_xs_at_each_grid(new_ene, new_xs, new_ene_part, new_xs_part);
  }

  //Renewal nbt_data and int_data
  renewal_interpolation_scheme_list(xs_nbt_data, xs_int_data, xs_ene_data, new_ene);

  xs_ene_data = new_ene;
  xs_data     = new_xs;
  new_ene.clear();
  new_xs.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Integer NonResonanceEnergyGridLinearizer::comp_interpolation_value
                                            (int& ele_no, Integer& int_val,
                                             vector<Real8>& ene_data, vector<Real8>& xs_data,
                                             Real8& mid_ene, Real8& mid_xs, Real8& err_line, Real& threshold)
{
  vector<Integer> multi_nbt_data, multi_int_data;
  vector<Real8>   multi_ene_data, multi_data;
  multi_nbt_data.clear();
  multi_int_data.clear();
  multi_ene_data.clear();
  multi_data.clear();

  return comp_interpolation_value(ele_no, int_val, ene_data, xs_data,
                                  multi_nbt_data, multi_int_data, multi_ene_data, multi_data,
                                  mid_ene, mid_xs, err_line, threshold);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Integer NonResonanceEnergyGridLinearizer::comp_interpolation_value
                                            (int& ele_no, Integer& int_val,
                                             vector<Real8>& ene_data, vector<Real8>& xs_data,
                                             vector<Integer>& multi_nbt_data, vector<Integer>& multi_int_data,
                                             vector<Real8>&   multi_ene_data, vector<Real8>&   multi_data,
                                             Real8& mid_ene, Real8& mid_xs, Real8& err_line, Real& threshold)
{
  Integer chk_flg = 0;

  mid_ene = 0.5*(ene_data[ele_no] + ene_data[ele_no-1]);
  mid_ene = digit_obj.get_truncation_value(mid_ene);

  if( ene_data[ele_no] - mid_ene            <= min_distance*mid_ene &&
      mid_ene          - ene_data[ele_no-1] <= min_distance*mid_ene )
  {
    return chk_flg;
  }

  //Interpolation which specified by evaluated nuclear data file
  Real8 xs_val = 0.0;
  ti_obj.interpolation_1d(int_val, mid_ene, xs_val, ene_data[ele_no-1], xs_data[ele_no-1],
                          ene_data[ele_no], xs_data[ele_no], threshold);
  mid_xs = xs_calc_obj.calc_xs_data_double(mid_ene, xs_val, multi_nbt_data, multi_int_data,
                                                            multi_ene_data, multi_data);
  if( fabs(mid_xs) < min_sig_val )
  {
    return chk_flg;
  }

  if( int_val >= 2 && ene_data[ele_no]/ene_data[ele_no-1] > err_line )
  {
    chk_flg = -1;
  }
  else if( int_val > 2 )
  {
    Real8 mid_xs_line, xs_pre, xs_cur;
    Real8 err;
    //Real8 err_int;
    if( ene_data[ele_no-1] < 0.5 )
    {
      err     = 0.2 * error_value;
      //err_int = 0.2 * error_int_value;
    }
    else
    {
      err     = error_value;
      //err_int = error_int_value;
    }

    //Interpolation by linear-linear
    Integer int_val_line = int_lin_lin;
    xs_pre = xs_calc_obj.calc_xs_data_double(ene_data[ele_no-1], xs_data[ele_no-1],
                                             multi_nbt_data, multi_int_data,
                                             multi_ene_data, multi_data);
    xs_cur = xs_calc_obj.calc_xs_data_double(ene_data[ele_no], xs_data[ele_no],
                                             multi_nbt_data, multi_int_data,
                                             multi_ene_data, multi_data);
    ti_obj.interpolation_1d(int_val_line, mid_ene, mid_xs_line, 
                            ene_data[ele_no-1], xs_pre, ene_data[ele_no], xs_cur, threshold);

    Real8 delta_xs    = fabs(mid_xs - mid_xs_line);
    Real8 mid_xs_coef = mid_xs;
    if( mid_xs_coef < 1.0E-10 && mid_xs_line < 1.0E-10 && mid_xs < mid_xs_line )
    {
      mid_xs_coef = mid_xs_line;
    }
    if( delta_xs > fabs(err*mid_xs_coef) + min_sig_dif )
    {
      chk_flg = -2;
    }
    //else if( delta_xs*(ene_data[ele_no] - ene_data[ele_no-1]) >= 2.0*err_int*mid_ene )
    //{
    //  chk_flg = -3;
    //}
  }
  return chk_flg;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void NonResonanceEnergyGridLinearizer::insert_middle_energy_grid
                                         (int& ele_no, Integer& int_val,
                                          vector<Real8>& ene_data, vector<Real8>& xs_data,
                                          Real8& mid_ene, Real8& mid_xs)
{
  ta_obj.add_table_data_at_given_position(ene_data, xs_data, mid_ene, mid_xs, ele_no);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void NonResonanceEnergyGridLinearizer::add_xs_at_each_grid
                                         (vector<Real8>& new_ene,      vector<Real8>& new_xs, 
                                          vector<Real8>& new_ene_part, vector<Real8>& new_xs_part)
{
  int k_max = static_cast<int>(new_ene_part.size());
  for(int k=1; k<k_max; k++)
  {
    new_ene.push_back(new_ene_part[k]);
    new_xs.push_back(new_xs_part[k]);
  }
  new_ene_part.clear();
  new_xs_part.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void NonResonanceEnergyGridLinearizer::renewal_interpolation_scheme_list
                                         (vector<Integer>& nbt_data, vector<Integer>& int_data, 
                                          vector<Real8>& ene_data,   vector<Real8>& new_ene)
{
  vector<Integer> new_nbt, new_int;
  new_nbt.clear();
  new_int.clear();

  int   ele_no  = 1;
  int   ele_max = static_cast<int>(new_ene.size());
  int   i_max   = static_cast<int>(nbt_data.size());
  Real8 ene_max;
  for(int i=0; i<i_max; i++)
  {
    ene_max = ene_data[static_cast<int>(nbt_data[i]-1)];

    while( ele_no < ele_max && new_ene[ele_no] <= ene_max )
    {
      ele_no++;
    }
    new_nbt.push_back(static_cast<Integer>(ele_no));
    new_int.push_back(int_data[i]);
  }
  nbt_data = new_nbt;
  int_data = new_int;
  new_nbt.clear();
  new_int.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void NonResonanceEnergyGridLinearizer::clear()
{
  add_non_reso_grid_flg = 0;

  non_reso_grid.clear();
  specified_grid.clear();
  specified_grid.push_back(conv_th_ene);

  error_value     = -1.0;
  error_int_value = -1.0;

  inela_tot_flg   = 0;
  fis_flg         = 0;
  photo_abs_flg   = 0;

  reso_el   = -100.0;
  reso_eh   = -100.0;
  unreso_eh = -100.0;

  vector<vector<Integer> >().swap(linearize_file_list);


  nucl_data_obj.clear();
  nucl_reaction_data_obj.clear();

  vector<CrossSectionDataContainer>().swap(xs_data_obj);
  vector<RadioactiveProductDataContainer>().swap(radio_product_data_obj);
  vector<PhotonDataContainer>().swap(photon_data_obj);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void NonResonanceEnergyGridLinearizer::set_err(Real8 real_val)
{
  add_non_reso_grid_flg = 0;

  error_value = real_val;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void NonResonanceEnergyGridLinearizer::set_err_int(Real8 real_val)
{
  add_non_reso_grid_flg = 0;

  error_int_value = real_val;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void NonResonanceEnergyGridLinearizer::set_user_specified_grid(vector<Real8> real_vec)
{
  add_non_reso_grid_flg = 0;

  specified_grid = real_vec;

  specified_grid.push_back(conv_th_ene);

  //Add upper limit of resolved resonance 
  if( reso_eh > min_ene_val )
  {
    specified_grid.push_back(reso_eh);
  }

  //Add upper limit of un-resolved resonance 
  if( unreso_eh > min_ene_val )
  {
    specified_grid.push_back(unreso_eh);
  }

  ta_obj.delete_overlap_grid(specified_grid);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void NonResonanceEnergyGridLinearizer::set_nucl_data_obj(NuclearDataObject& data_obj)
{
  add_non_reso_grid_flg  = 0;

  nucl_data_obj          = data_obj;
  nucl_reaction_data_obj = nucl_data_obj.get_nucl_reaction_data_obj();
  xs_data_obj            = nucl_reaction_data_obj.get_xs_data_obj();
  radio_product_data_obj = nucl_reaction_data_obj.get_radio_product_data_obj();
  photon_data_obj        = nucl_reaction_data_obj.get_photon_data_obj();

  read_resonance_upper_limit();

  //Check xs_data_obj (MF=03)
  inela_tot_flg = 0;
  fis_flg       = 0;
  for(int i=0; i<static_cast<int>(xs_data_obj.size()); i++)
  {
    Integer mt_no = xs_data_obj[i].get_reaction_type();
    if( mt_no >= 51 && mt_no <= 91 )
    {
      inela_tot_flg = 1;
    }

    if( mt_no == 19 )
    {
      fis_flg = 1;
    }

    if( inela_tot_flg > 0 && fis_flg > 0 )
    {
      break;
    }
  }

  //Check photon_data_obj (MF=23)
  photo_abs_flg = 0;
  for(int i=0; i<static_cast<int>(photon_data_obj.size()); i++)
  {
    Integer mt_no = photon_data_obj[i].get_reaction_type();
    if( mt_no >= 534 && mt_no <= 572 )
    {
      photo_abs_flg = 1;
      break;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void NonResonanceEnergyGridLinearizer::read_resonance_upper_limit()
{
  vector<vector<Real> >    lower_ene_limit = nucl_data_obj.get_reso_data_obj().get_lower_ene_limit();
  vector<vector<Real> >    upper_ene_limit = nucl_data_obj.get_reso_data_obj().get_upper_ene_limit();
  vector<vector<Integer> > reso_region_flg = nucl_data_obj.get_reso_data_obj().get_reso_region_flg();

  reso_el   = -100.0;
  reso_eh   = -100.0;
  unreso_eh = -100.0;
  int i_max = static_cast<int>(upper_ene_limit.size());
  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(upper_ene_limit[i].size());
    for(int j=0; j<j_max; j++)
    {
      Real8 el_tmp = static_cast<Real8>(lower_ene_limit[i][j]);
      if( reso_el < 0.0 )
      {
        reso_el = el_tmp;
      }
      else if( reso_el > el_tmp )
      {
        reso_el = el_tmp;
      }

      Real8 eh_tmp = static_cast<Real8>(upper_ene_limit[i][j]);
      if( reso_region_flg[i][j] == 1 && reso_eh < eh_tmp )
      {
        reso_eh = eh_tmp;
      }
      else if( reso_region_flg[i][j] == 2 && unreso_eh < eh_tmp )
      {
        unreso_eh = eh_tmp;
      }
    }
  }

  //Add upper limit of resolved resonance
  if( reso_eh > min_ene_val )
  {
    Real8 tmp_real = reso_eh;
    reso_eh = digit_obj.get_adjusted_value(tmp_real, sig_fig, +1.0);
    specified_grid.push_back(reso_eh);
  }

  //Add upper limit of un-resolved resonance
  if( unreso_eh > min_ene_val )
  {
    Real8 tmp_real = unreso_eh;
    unreso_eh = digit_obj.get_adjusted_value(tmp_real, sig_fig, +1.0);
    specified_grid.push_back(unreso_eh);
  }
  ta_obj.delete_overlap_grid(specified_grid);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//Getter

vector<Real8> NonResonanceEnergyGridLinearizer::get_non_resonance_grid()
{
  add_non_resonance_grid();
  return non_reso_grid;
}

vector<Real8> NonResonanceEnergyGridLinearizer::get_user_specified_grid()
{
  return specified_grid;
}

Real8 NonResonanceEnergyGridLinearizer::get_err()
{
  return error_value;
}

Real8 NonResonanceEnergyGridLinearizer::get_err_int()
{
  return error_int_value;
}

Real8 NonResonanceEnergyGridLinearizer::get_reso_eh()
{
  return reso_eh;
}

Real8 NonResonanceEnergyGridLinearizer::get_unreso_eh()
{
  return unreso_eh;
}

vector<vector<Integer> > NonResonanceEnergyGridLinearizer::get_linearize_file_list()
{
  add_non_resonance_grid();
  return linearize_file_list;
}


NuclearDataObject NonResonanceEnergyGridLinearizer::get_nucl_data_obj()
{
  add_non_resonance_grid();

  nucl_reaction_data_obj.set_xs_data_obj(xs_data_obj);
  nucl_reaction_data_obj.set_radio_product_data_obj(radio_product_data_obj);
  nucl_reaction_data_obj.set_photon_data_obj(photon_data_obj);
  nucl_data_obj.set_nucl_reaction_data_obj(nucl_reaction_data_obj);

  return nucl_data_obj;
}

NuclearReactionDataContainer NonResonanceEnergyGridLinearizer::get_nucl_reaction_data_obj()
{
  add_non_resonance_grid();

  nucl_reaction_data_obj.set_xs_data_obj(xs_data_obj);
  nucl_reaction_data_obj.set_radio_product_data_obj(radio_product_data_obj);
  nucl_reaction_data_obj.set_photon_data_obj(photon_data_obj);

  return nucl_reaction_data_obj;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

