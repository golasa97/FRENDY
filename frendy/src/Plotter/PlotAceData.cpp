#include "Plotter/PlotAceData.hpp"

using namespace frendy;

//constructor
PlotAceData::PlotAceData(void)
{
  clear();
}

//destructor
PlotAceData::~PlotAceData(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotAceData::clear()
{
  temp_ori = -1.0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotAceData::set_xs_type_list_fast(FastAceDataObject& ace_obj,  vector<Integer>& xs_type_list)
{
  if( static_cast<int>(xs_type_list.size()) != 0 )
  {
    return;
  }

  xs_type_list.push_back(  1); //total
  xs_type_list.push_back(  2); //scatter;
  xs_type_list.push_back(101); //disappearance

  int fis_flg = 0;
  vector<int> xs_type_list_add = ace_obj.get_react_type_list();
  for(int i=0; i<static_cast<int>(xs_type_list_add.size()); i++)
  {
    xs_type_list.push_back(xs_type_list_add[i]);
    if( xs_type_list_add[i] == 18 )
    {
      fis_flg = 1;
    }
  }
  xs_type_list_add.clear();


  if( fis_flg > 0 )
  {
    //For chi (fission spectrum)
    xs_type_list.push_back(1018);

    //For nu_tot (total number of neutrons per fission)
    if( static_cast<int>(ace_obj.get_nu_data().size()) > 0 )
    {
      int mt_add = static_cast<int>(ace_obj.get_nu_bar_repr_flg())*1000 + 452;
      xs_type_list.push_back(mt_add);
    }

    //For nu_f
    if( static_cast<int>(ace_obj.get_nu_d_data().size()) > 0 &&
        static_cast<int>(ace_obj.get_nu_d_bar_repr_flg()) == 2 )
    {
      int mt_add = static_cast<int>(ace_obj.get_nu_d_bar_repr_flg())*1000 + 455;
      xs_type_list.push_back(mt_add);
    }

    //For nu_p
    if( static_cast<int>(ace_obj.get_nu_p_data().size()) > 0 )
    {
      int mt_add = static_cast<int>(ace_obj.get_nu_p_bar_repr_flg())*1000 + 456;
      xs_type_list.push_back(mt_add);
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotAceData::read_nu_data(FastAceDataObject& ace_obj, int mt_no, vector<Real>& e_vec, vector<Real>& nu_vec)
{
  ace_obj.get_xs_data(1, e_vec, nu_vec);
  nu_vec.clear();

  vector<Real> nu_coef;
  if( mt_no == 1452 )
  {
    nu_coef = ace_obj.get_nu_data();
  }
  else if( mt_no == 1456 )
  {
    nu_coef = ace_obj.get_nu_p_data();
  }
  else if( mt_no == 1455 )
  {
    nu_coef = ace_obj.get_nu_d_data();
  }
  else
  {
    return;
  }

  int i_max = static_cast<int>(e_vec.size());
  int j_max = static_cast<int>(nu_coef.size());
  if( j_max == 0 )
  {
    e_vec.clear();
    nu_vec.clear();
    return;
  }

  nu_vec.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    Real e_coef = 1.0;
    nu_vec[i]   = 0.0;
    for(int j=0; j<j_max; j++)
    {
      nu_vec[i] += nu_coef[j] * e_coef;
      e_coef    *= e_vec[i];
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotAceData::read_ace_file_fast(string file_name, vector<int>& xs_type_list,
                                     vector<vector<Real> >& e_int_xs, vector<vector<Real> >& xs_tab)
{
  //Read ACE file
  FastAceDataParser read_obj;
  read_obj.set_file_name(file_name);
  FastAceDataObject ace_obj = read_obj.get_ace_data_obj();

  set_xs_data_fast(ace_obj, xs_type_list, e_int_xs, xs_tab);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotAceData::set_xs_data_fast(frendy::FastAceDataObject& ace_obj, vector<int>& xs_type_list,
                                   vector<vector<Real> >& e_int_xs, vector<vector<Real> >& xs_tab)
{
  set_xs_type_list_fast(ace_obj, xs_type_list);

  int i_max = static_cast<int>(xs_type_list.size());

  //Resize xs data
  e_int_xs.resize(i_max);
  xs_tab.resize(i_max);

  for(int i=0; i<i_max; i++)
  {
    if( xs_type_list[i] < 1000 )
    {
      ace_obj.get_xs_data(xs_type_list[i], e_int_xs[i], xs_tab[i]);
    }
    else
    {
      if( xs_type_list[i] == 1018 )
      {
        ace_obj.get_chi_data(e_int_xs[i], xs_tab[i]);
      }
      else if( xs_type_list[i] < 2000 )
      {
        read_nu_data(ace_obj, xs_type_list[i], e_int_xs[i], xs_tab[i]);
      }
      else if( xs_type_list[i] == 2452 )
      {
        e_int_xs[i] = ace_obj.get_nu_ene_data();
        xs_tab[i]   = ace_obj.get_nu_data();
      }
      else if( xs_type_list[i] == 2455 )
      {
        e_int_xs[i] = ace_obj.get_nu_d_ene_data();
        xs_tab[i]   = ace_obj.get_nu_d_data();
      }
      else if( xs_type_list[i] == 2456 )
      {
        e_int_xs[i] = ace_obj.get_nu_p_ene_data();
        xs_tab[i]   = ace_obj.get_nu_p_data();
      }
    }

    int j_max = static_cast<int>(e_int_xs[i].size());
    for(int j=0; j<j_max; j++)
    {
      e_int_xs[i][j] *= 1.0E6; //MeV -> eV
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotAceData::set_xs_type_list_tsl(ThermalScatterAceDataObject& ace_obj, vector<Integer>& xs_type_list)
{
  if( static_cast<int>(xs_type_list.size()) != 0 )
  {
    return;
  }

  if( static_cast<int>(ace_obj.get_inelastic_xs_data().size()) > 0 )
  {
    xs_type_list.push_back(221); //inelastic scattering
  }

  if( static_cast<int>(ace_obj.get_coh_elastic_e_xs_data().size()) > 0 )
  {
    xs_type_list.push_back(222); //coherent elastic scattering
  }

  if( static_cast<int>(ace_obj.get_incoh_elastic_xs_data().size()) > 0 )
  {
    xs_type_list.push_back(223); //incoherent elastic scattering
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotAceData::read_ace_file_tsl(string file_name, vector<int>& xs_type_list,
                                    vector<vector<Real> >& e_int_xs, vector<vector<Real> >& xs_tab)
{
  //Read ACE file
  ThermalScatterAceDataParser read_obj;
  read_obj.set_file_name(file_name);
  ThermalScatterAceDataObject ace_obj = read_obj.get_ace_data_obj();

  set_xs_data_tsl(ace_obj, xs_type_list, e_int_xs, xs_tab);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotAceData::set_xs_data_tsl(frendy::ThermalScatterAceDataObject& ace_obj,
                                 vector<Integer>& xs_type_list,
                                 vector<vector<Real> >& e_int_xs, vector<vector<Real> >& xs_tab)
{
  set_xs_type_list_tsl(ace_obj, xs_type_list);

  int i_max = static_cast<int>(xs_type_list.size());
  vector<Real> coh_ene   = ace_obj.get_coh_elastic_ene_data();
  vector<Real> coh_xs    = ace_obj.get_coh_elastic_e_xs_data();
  vector<Real> incoh_ene = ace_obj.get_incoh_elastic_ene_data();
  vector<Real> incoh_xs  = ace_obj.get_incoh_elastic_xs_data();
  vector<Real> inela_ene = ace_obj.get_inelastic_ene_data();
  vector<Real> inela_xs  = ace_obj.get_inelastic_xs_data();

  //Resize xs data
  e_int_xs.resize(i_max);
  xs_tab.resize(i_max);

  for(int i=0; i<i_max; i++)
  {
    if( xs_type_list[i] == 221 )
    {
      e_int_xs[i] = inela_ene;
      xs_tab[i]   = inela_xs;
    }

    if( xs_type_list[i] == 222 )
    {
      e_int_xs[i] = coh_ene;
      xs_tab[i]   = coh_xs;
    }

    if( xs_type_list[i] == 223 )
    {
      e_int_xs[i] = incoh_ene;
      xs_tab[i]   = incoh_xs;
    }

    int j_max = static_cast<int>(e_int_xs[i].size());
    for(int j=0; j<j_max; j++)
    {
      e_int_xs[i][j] *= 1.0E6; //MeV -> eV
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotAceData::set_xs_type_list_dosi(DosimetryAceDataObject& ace_obj,  vector<Integer>& xs_type_list)
{
  if( static_cast<int>(xs_type_list.size()) != 0 )
  {
    return;
  }

  vector<int>                    xs_type_list_add = ace_obj.get_reaction_xs_reaction_type();
  vector<vector<int> >           state_no         = ace_obj.get_production_xs_state_no_product();
  vector<vector<Real> >          xs_vec           = ace_obj.get_reaction_xs_data();
  vector<vector<vector<Real> > > xs_prod_vec      = ace_obj.get_production_xs_data();
  for(int i=0; i<static_cast<int>(xs_type_list_add.size()); i++)
  {
    int mt_val = xs_type_list_add[i];
    if( static_cast<int>(xs_vec[i].size()) > 0 )
    {
      int mt_add = mt_val * 10000 + 300; //300 = MF3 * 100
      xs_type_list.push_back(mt_add);
    }
  }

  for(int i=0; i<static_cast<int>(state_no.size()); i++)
  {
    int j_max = static_cast<int>(xs_prod_vec[i].size());
    for(int j=0; j<j_max; j++)
    {
      if( static_cast<int>(xs_prod_vec[i][j].size()) > 0 )
      {
        //state_no = mt + 1000 * (10 + state_no_product)
        int mt_val    = state_no[i][j] % 1000;
        int state_val = state_no[i][j] / 1000 - 10;
        int mt_add = mt_val * 10000 + 1000 + state_val; //1000 = MF10 * 100
        xs_type_list.push_back(mt_add);
      }
    }
  }
  xs_type_list_add.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotAceData::read_ace_file_dosi(string file_name, vector<int>& xs_type_list,
                                     vector<vector<Real> >& e_int_xs, vector<vector<Real>
>& xs_tab)
{
  //Read ACE file
  DosimetryAceDataParser read_obj;
  read_obj.set_file_name(file_name);
  DosimetryAceDataObject ace_obj = read_obj.get_ace_data_obj();

  set_xs_data_dosi(ace_obj, xs_type_list, e_int_xs, xs_tab);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotAceData::set_xs_data_dosi(frendy::DosimetryAceDataObject& ace_obj, vector<int>& xs_type_list,
                                   vector<vector<Real> >& e_int_xs, vector<vector<Real> >& xs_tab)
{
  set_xs_type_list_dosi(ace_obj, xs_type_list);

  int i_max = static_cast<int>(xs_type_list.size());

  //Resize xs data
  e_int_xs.resize(i_max);
  xs_tab.resize(i_max);

  vector<int>          mt_list       = ace_obj.get_reaction_xs_reaction_type();
  vector<vector<int> > state_no_list = ace_obj.get_production_xs_state_no_product();

  LinearizeTabData lin_tab_obj;
  for(int i=0; i<i_max; i++)
  {
    int mf       = (xs_type_list[i] % 10000) / 100;
    int mt       =  xs_type_list[i] / 10000;
    int state_no = (xs_type_list[i] %   100);

    vector<Integer> xs_int, xs_range;
    if( mf == 3 )
    {
      int j_max  = static_cast<int>(mt_list.size());
      int mt_pos = -1;
      for(int j=0; j<j_max; j++)
      {
        if( mt_list[j] == mt )
        {
          mt_pos = j;
          break;
        }
      }
      if( mt_pos < 0 )
      {
        continue;
      }

      xs_int      = ace_obj.get_reaction_xs_int_data()[mt_pos];
      xs_range    = ace_obj.get_reaction_xs_range_data()[mt_pos];
      xs_tab[i]   = ace_obj.get_reaction_xs_data()[mt_pos];
      e_int_xs[i] = ace_obj.get_reaction_xs_ene_data()[mt_pos];
    }
    else if( mf == 10 )
    {
      int state_no_ace = mt + 1000*(10 + state_no);

      int s_pos_j = -1;
      int s_pos_k = -1;
      int j_max  = static_cast<int>(state_no_list.size());
      for(int j=0; j<j_max; j++)
      {
        int k_max  = static_cast<int>(state_no_list[j].size());
        for(int k=0; k<k_max; k++)
        {
          if( state_no_list[j][k] == state_no_ace )
          {
            s_pos_j = j;
            s_pos_k = k;
            break;
          }
        }

        if( s_pos_j >= 0 )
        {
          break;
        }
      }
      if( s_pos_j < 0 || s_pos_k < 0 )
      {
        continue;
      }

      xs_int      = ace_obj.get_production_xs_int_data()[s_pos_j][s_pos_k];
      xs_range    = ace_obj.get_production_xs_range_data()[s_pos_j][s_pos_k];
      xs_tab[i]   = ace_obj.get_production_xs_data()[s_pos_j][s_pos_k];
      e_int_xs[i] = ace_obj.get_production_xs_ene_data()[s_pos_j][s_pos_k];
    }
    else
    {
      continue;
    }

    lin_tab_obj.linearize_tab1_data(xs_range, xs_int, e_int_xs[i], xs_tab[i]);
    xs_range.clear();
    xs_int.clear();

    int j_max = static_cast<int>(e_int_xs[i].size());
    for(int j=0; j<j_max; j++)
    {
      e_int_xs[i][j] *= 1.0E6; //MeV -> eV
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotAceData::plot_ace(string file_name, vector<Integer>& xs_type_list,
                           vector<vector<Real> >& e_int_xs, vector<vector<Real> >& xs_tab)
{
  AceFileReader read_obj;
  int ace_type_no = read_obj.get_ace_data_type_from_ace_file(file_name);
      temp_ori    = read_obj.get_temp(file_name);

  if( ace_type_no == read_obj.fast_data )
  {
    read_ace_file_fast(file_name, xs_type_list, e_int_xs, xs_tab);
  }
  else if( ace_type_no == read_obj.tsl_data )
  {
    read_ace_file_tsl(file_name, xs_type_list, e_int_xs, xs_tab);
  }
  else if( ace_type_no == read_obj.dosi_data )
  {
    read_ace_file_dosi(file_name, xs_type_list, e_int_xs, xs_tab);
  }
  else
  {
    string class_name = "PlotAceData";
    string func_name  = "plot_ace";

    vector<string> err_com;

    string str_data01 = "ACE file name : " + file_name;
    err_com.push_back(str_data01);
    err_com.push_back("This program cannot read this ACE file.");
    err_com.push_back("This program only treat following data:");
    err_com.push_back("  fast (neutron induced data)");
    err_com.push_back("  tsl  (thermal scattering law data");
    err_com.push_back("  dosi (dosimetry data");
    err_com.push_back("Please check the ACE file or the ACE file name.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotAceData::plot_ace(string file_name, vector<Integer>& xs_type_list,
                           vector<vector<Real> >& e_int_xs, vector<vector<Real> >& xs_tab,
                           Real temp)
{
  AceFileReader read_obj;
  int ace_type_no = read_obj.get_ace_data_type_from_ace_file(file_name);
      temp_ori    = read_obj.get_temp(file_name);

  if( ace_type_no == read_obj.fast_data )
  {
    read_ace_file_fast(file_name, xs_type_list, e_int_xs, xs_tab);
  }
  else if( ace_type_no == read_obj.tsl_data )
  {
    read_ace_file_tsl(file_name, xs_type_list, e_int_xs, xs_tab);
  }
  else if( ace_type_no == read_obj.dosi_data )
  {
    read_ace_file_dosi(file_name, xs_type_list, e_int_xs, xs_tab);
  }
  else
  {
    string class_name = "PlotAceData";
    string func_name  = "plot_ace";

    vector<string> err_com;

    string str_data01 = "ACE file name : " + file_name;
    err_com.push_back(str_data01);
    err_com.push_back("");
    err_com.push_back("This program cannot read this ACE file.");
    err_com.push_back("This program only treat following data:");
    err_com.push_back("  fast (neutron induced data)");
    err_com.push_back("  tsl  (thermal scattering law data");
    err_com.push_back("  dosi (dosimetry data");
    err_com.push_back("Please check the ACE file or the ACE file name.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  if( temp > -1.0 * min_value )
  {
    //Doppler broadening
    Real awr_ace  = read_obj.get_awr(file_name);
    cout << "Doppler broadening from " << temp_ori << " [K] to " << temp << " [K]." << endl;
    calc_dop_obj.calc_doppler_broadened_xs_from_xs_table
      (temp_ori, temp, awr_ace, xs_type_list,  e_int_xs, xs_tab);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Real PlotAceData::get_temp_ori()
{
  return temp_ori;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

