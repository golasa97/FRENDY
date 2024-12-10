#include "ReconResonance/ResonanceXSReconstructor.hpp"

using namespace frendy;

//constructor
ResonanceXSReconstructor::ResonanceXSReconstructor(void)
{
  clear();
}

//destructor
ResonanceXSReconstructor::~ResonanceXSReconstructor(void)
{
  clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ResonanceXSReconstructor::calc_reconstruct_resonance_xs()
{
  if( calc_reso_flg == 1 )
  {
    return;
  }
  calc_reso_flg = 1;

  if( nucl_data_set_flg == 0 )
  {
    string class_name = "ResonanceXSReconstructor";
    string func_name  = "calc_reconstruct_resonance_xs()";

    vector<string> err_com;
    err_com.push_back("There is no NuclearDataObject..");
    err_com.push_back("Please set nuclear data object using set_nucl_data_obj function");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  clear_ene_grid_and_xs();

  //Get non resonance energy grid (using NonResonanceEnergyGridLinearizer class)
  non_reso_obj.set_nucl_data_obj(nucl_data_obj);
  non_reso_obj.set_user_specified_grid(additional_grid);
  non_reso_obj.set_err(err);
  non_reso_obj.set_err_int(err_int);
  non_reso_grid.clear();
  non_reso_grid       = non_reso_obj.get_non_resonance_grid();
  linearize_file_list = non_reso_obj.get_linearize_file_list();
  non_reso_obj.clear();
  
  //Get resonance energy grid (using ResonanceEnergyGridLinearizer class)
  reso_obj.set_nucl_data_obj(nucl_data_obj);
  reso_obj.set_user_specified_grid(non_reso_grid);
  clr_obj.clear_vec_array3_real8(reso_grid);
  reso_grid = reso_obj.get_resonance_grid();
  reso_obj.clear();

  //Following for loops are used to avoid unexpected additional energy grid
  //larger than highest energy grid.
  //This problem is found in U-235 from JEFF-3.3 library when GCC 8.5.0 is used.
  //(This problem is not found when GCC 4.8.5 is used.)
  int p_max = static_cast<int>(reso_grid.size());
  cout << endl;
  cout << "Number of resonance energy grids after ResonanceEnergyGridLinearizer" << endl;
  for(int p=0; p<p_max; p++)
  {
    cout << "  " << p+1 << " / " << p_max << " : " << reso_grid[p].size() << endl;
    int q_max = static_cast<int>(reso_grid[p].size());
    for(int q=0; q<q_max; q++)
    {
      cout << "    " << q+1 << " / " << q_max << " : " << reso_grid[p][q].size() << endl;
      int r_max = static_cast<int>(reso_grid[p][q].size());
      for(int r=0; r<r_max; r++)
      {
        //cout << "    " << r+1 << " / " << r_max << " : " << reso_grid[p][q][r] << endl;
      }
    }
  }
  cout << endl;
  
  //Calc resonance cross section and modified energy grid (using ResonanceXSCalculator class)
  reso_xs_obj.set_nucl_data_obj(nucl_data_obj);
  reso_xs_obj.set_resonance_grid(reso_grid);
  reso_xs_obj.set_temp(temp);
  reso_xs_obj.set_err(err);
  reso_xs_obj.set_err_max(err_max);
  reso_xs_obj.set_err_int(err_int);
  clr_obj.clear_vec_array3_real8(reso_grid); 
  reso_react_type_list = reso_xs_obj.get_resonance_react_type_list();
  reso_q_val           = reso_xs_obj.get_resonance_q_val();
  reso_grid            = reso_xs_obj.get_resonance_grid();
  reso_xs              = reso_xs_obj.get_resonance_xs();
  nucl_data_obj        = reso_xs_obj.get_nucl_data_obj();
  //Real xs_pot          = reso_xs_obj.get_xs_potential();
  reso_xs_obj.clear();

  //Merge non resonance and resonance cross section and energy grid (using ReconstructXSMerger class)
  mrg_obj.set_nucl_data_obj(nucl_data_obj);
  mrg_obj.set_non_resonance_grid(non_reso_grid);
  mrg_obj.set_resonance_react_type_list(reso_react_type_list);
  mrg_obj.set_resonance_q_val(reso_q_val);
  mrg_obj.set_resonance_grid(reso_grid);
  mrg_obj.set_resonance_xs(reso_xs);
  merge_grid    = mrg_obj.get_merge_grid();
  merge_xs      = mrg_obj.get_merge_xs();
  nucl_data_obj = mrg_obj.get_nucl_data_obj();

  //Remove not linearize file data
  //remove_unnecessary_file_data();
  mrg_obj.clear();

  //Modify nuclear data object
  //(Modify resonance data and remove nuclear data without linearized data)
  mod_obj.set_nucl_data_obj(nucl_data_obj);
  mod_obj.set_modify_photon_data_flg(modify_photon_data_flg);
  mod_obj.set_ene_grid(merge_grid);
  mod_obj.set_sig_data(merge_xs);
  mod_obj.set_reso_ene_grid(reso_grid);
  mod_obj.set_reso_sig_data(reso_xs);
  nucl_data_obj = mod_obj.get_nucl_data_obj();
  mod_obj.clear();

  //Modify reso_flg (LRP) from 1 to 2.
  //LRP=1 : resolved and/or unresolved parameter data are given in File 2 and
  //        cross sections computed from them must be added to background
  //        criss sectuibs given in File 3
  //LRP=2 : parameters are given in File 2, but cross sections derived from
  //        them are not to be added to the cross section in File 3.
  GeneralDataContainer general_data_obj = nucl_data_obj.get_general_data_obj();
  if( general_data_obj.get_reso_flg() == 1 )
  {
    general_data_obj.set_reso_flg(2);
    nucl_data_obj.set_general_data_obj(general_data_obj);
  }
  general_data_obj.clear();

  //Modify cross section data
  nucl_util_obj.modify_xs_data_without_caution(nucl_data_obj);
  nucl_util_obj.check_total_product_xs(nucl_data_obj);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ResonanceXSReconstructor::remove_unnecessary_file_data()
{
  vector<Integer> reaction_type;
  vector<CrossSectionDataContainer>       xs_data_obj,            xs_data_obj_new;
  vector<RadioactiveProductDataContainer> radio_product_data_obj, radio_product_data_obj_new;
  vector<PhotonDataContainer>             photon_data_obj,        photon_data_obj_new;

  reaction_type          = nucl_data_obj.get_nucl_reaction_data_obj().get_reaction_type();
  xs_data_obj            = nucl_data_obj.get_nucl_reaction_data_obj().get_xs_data_obj();
  radio_product_data_obj = nucl_data_obj.get_nucl_reaction_data_obj().get_radio_product_data_obj();
  photon_data_obj        = nucl_data_obj.get_nucl_reaction_data_obj().get_photon_data_obj();

  int i_max = static_cast<int>(linearize_file_list.size());
  int j_max = static_cast<int>(reaction_type.size());
  for(int i=0; i<i_max; i++)
  {
    Integer mf_no = linearize_file_list[i][0];
    Integer mt_no = linearize_file_list[i][1];

    if( mt_no != 1 && mt_no != 2 && mt_no != 18 && mt_no != 102 )
    {
      vector<int> add_xs_vec = mrg_obj.check_add_xs(mt_no);
      if( static_cast<int>(add_xs_vec.size()) == 0 )
      {
        continue;
      }
    }

    int pos = -1;
    for(int j=0; j<j_max; j++)
    {
      if( mt_no == reaction_type[j] )
      {
        pos = j;
        break;
      }
    }

    if( mf_no == 3 )
    {
      xs_data_obj_new.push_back(xs_data_obj[pos]);
    }
    else if( mf_no == 10 )
    {
      radio_product_data_obj_new.push_back(radio_product_data_obj[pos]);
    }
    else if( mf_no == 12 || mf_no == 13 || mf_no == 23 )
    {
      photon_data_obj_new.push_back(photon_data_obj[pos]);
    }
  }
  vector<CrossSectionDataContainer>().swap(xs_data_obj);
  vector<RadioactiveProductDataContainer>().swap(radio_product_data_obj);
  vector<PhotonDataContainer>().swap(photon_data_obj);

  NuclearReactionDataContainer nucl_reaction_data_obj_new;
  nucl_reaction_data_obj_new.set_xs_data_obj(xs_data_obj_new);
  nucl_reaction_data_obj_new.set_radio_product_data_obj(radio_product_data_obj_new);
  nucl_reaction_data_obj_new.set_photon_data_obj(photon_data_obj_new);
  vector<CrossSectionDataContainer>().swap(xs_data_obj_new);
  vector<RadioactiveProductDataContainer>().swap(radio_product_data_obj_new);
  vector<PhotonDataContainer>().swap(photon_data_obj_new);

  nucl_data_obj.set_nucl_reaction_data_obj(nucl_reaction_data_obj_new);
  nucl_reaction_data_obj_new.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ResonanceXSReconstructor::clear_ene_grid_and_xs()
{
  non_reso_grid.clear();
  merge_grid.clear();
  clr_obj.clear_vec_array3_int(reso_react_type_list);
  clr_obj.clear_vec_array3_real8(reso_q_val);
  clr_obj.clear_vec_array3_real8(reso_grid);
  clr_obj.clear_vec_array4_real8(reso_xs);
  clr_obj.clear_vec_array2_real8(merge_xs);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ResonanceXSReconstructor::clear()
{
  modify_photon_data_flg = 0;
  calc_reso_flg          = 0;
  nucl_data_set_flg      = 0;

  non_reso_obj.clear();
  reso_obj.clear();
  reso_xs_obj.clear();
  mrg_obj.clear();
  mod_obj.clear();

  nucl_data_obj.clear();

  err     = 0.0;
  err_int = 0.0;
  err_max = 0.0;
  temp    = 0.0;
  
  additional_grid.clear();

  clr_obj.clear_vec_array2_int(linearize_file_list);

  clear_ene_grid_and_xs();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ResonanceXSReconstructor::output_set_data_information()
{
  cout << "=== Nuclear data information ===" << endl;
  cout << "  Material No.       : " << nucl_data_obj.get_general_data_obj().get_mat_no()   << endl;
  cout << "  Material Data (ZA) : " << nucl_data_obj.get_general_data_obj().get_mat_data() << endl;
  cout << "  Mass               : " << nucl_data_obj.get_general_data_obj().get_mass()     << endl;
  cout << endl;
  cout << "=== Set data information ===" << endl;
  cout << "  Error             : " << err     << endl;
  cout << "  Integral Error    : " << err_int << endl;
  cout << "  Maximum Error     : " << err_max << endl;
  cout << "  Temperature       : " << temp    << endl;

  int i_max = static_cast<int>(additional_grid.size());
  if( i_max > 0 )
  {
    cout << "  Additional Energy Grid" << endl;
    cout << "  ";
    for(int i=0; i<static_cast<int>(additional_grid.size()); i++)
    {
      cout << "  " << additional_grid[i];
    }
    cout << endl;
  }
  else
  {
    cout << "  No Additional Energy Grid" << endl;
  }
  cout << endl;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//Setter

void ResonanceXSReconstructor::set_nucl_data_obj(frendy::NuclearDataObject& data_obj)
{
  calc_reso_flg     = 0;
  nucl_data_set_flg = 1;
  nucl_data_obj     = data_obj;
}

void ResonanceXSReconstructor::set_modify_photon_data_flg(int int_val)
{
  calc_reso_flg = 0;
  modify_photon_data_flg = int_val;
}

void ResonanceXSReconstructor::set_err(Real8 real_val)
{
  calc_reso_flg = 0;
  err           = real_val;
}

void ResonanceXSReconstructor::set_err_int(Real8 real_val)
{
  calc_reso_flg = 0;
  err_int       = real_val;
}

void ResonanceXSReconstructor::set_err_max(Real8 real_val)
{
  calc_reso_flg = 0;
  err_max       = real_val;
}

void ResonanceXSReconstructor::set_temp(Real8 real_val)
{
  calc_reso_flg = 0;
  temp          = real_val;
}

void ResonanceXSReconstructor::set_additional_grid(vector<Real8> real_vec)
{
  calc_reso_flg   = 0;
  additional_grid = real_vec;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//Getter

NuclearDataObject ResonanceXSReconstructor::get_nucl_data_obj()
{
  calc_reconstruct_resonance_xs();
  return nucl_data_obj;
}

int            ResonanceXSReconstructor::get_modify_photon_data_flg()
{
  return modify_photon_data_flg;
}

Real8          ResonanceXSReconstructor::get_err()
{
  return err;
}

Real8          ResonanceXSReconstructor::get_err_int()
{
  return err_int;
}

Real8          ResonanceXSReconstructor::get_err_max()
{
  return err_max;
}

Real8          ResonanceXSReconstructor::get_temp()
{
  return temp;
}

vector<Real8>  ResonanceXSReconstructor::get_additional_grid()
{
  return additional_grid;
}

vector<Real8>                            ResonanceXSReconstructor::get_non_reso_grid()
{
  calc_reconstruct_resonance_xs();
  return non_reso_grid;
}

vector<vector<vector<Integer> > >        ResonanceXSReconstructor::get_reso_react_type_list()
{
  calc_reconstruct_resonance_xs();
  return reso_react_type_list;
}

vector<vector<vector<Real8> > >        ResonanceXSReconstructor::get_reso_q_val()
{
  calc_reconstruct_resonance_xs();
  return reso_q_val;
}

vector<vector<vector<Real8> > >          ResonanceXSReconstructor::get_reso_grid()
{
  calc_reconstruct_resonance_xs();
  return reso_grid;
}

vector<vector<vector<vector<Real8> > > > ResonanceXSReconstructor::get_reso_xs()
{
  calc_reconstruct_resonance_xs();
  return reso_xs;
}

vector<Real8>                            ResonanceXSReconstructor::get_merge_grid()
{
  calc_reconstruct_resonance_xs();
  return merge_grid;
}

vector<vector<Real8> >                   ResonanceXSReconstructor::get_merge_xs()
{
  calc_reconstruct_resonance_xs();
  return merge_xs;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

