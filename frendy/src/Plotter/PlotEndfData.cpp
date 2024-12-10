#include "Plotter/PlotEndfData.hpp"

using namespace frendy;

//constructor
PlotEndfData::PlotEndfData(void)
{
  clear();
}

//destructor
PlotEndfData::~PlotEndfData(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotEndfData::clear()
{
  temp_ori = -1.0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotEndfData::set_xs_type_list(Endf6Parser& endf_obj,  vector<Integer>& xs_type_list)
{
  if( static_cast<int>(xs_type_list.size()) != 0 )
  {
    return;
  }
  xs_type_list.clear();

  //Get MF3 data
  vector<MF03Parser> mf03 = endf_obj.get_mf03_data();

  int fis_flg = 0;
  for(int i=0; i<static_cast<int>(mf03.size()); i++)
  {
    Integer mt_no = mf03[i].get_mt_no();
    if( mt_no != unassigned_mt_no )
    {
      xs_type_list.push_back(mt_no);

      if( mt_no == 18 )
      {
        fis_flg = 1;
      }
    }
  }
  vector<MF03Parser>().swap(mf03);

  //Get Nu data
  if( fis_flg > 0 )
  {
    MF01MT452Parser mt452_obj = endf_obj.get_mf01_mt452_data();
    if( static_cast<int>(mt452_obj.get_C().size())  > 0 ||
        static_cast<int>(mt452_obj.get_NU().size()) > 0 )
    {
      xs_type_list.push_back(1452);
    }

    MF01MT455Parser mt455_obj = endf_obj.get_mf01_mt455_data();
    if( static_cast<int>(mt455_obj.get_NU().size())  > 0 )
    {
      xs_type_list.push_back(1455);
    }

    MF01MT456Parser mt456_obj = endf_obj.get_mf01_mt456_data();
    if( static_cast<int>(mt456_obj.get_NU().size())  > 0 )
    {
      xs_type_list.push_back(1456);
    }
  }

  //Get MF=09 data
  vector<MF09Parser> mf09 = endf_obj.get_mf09_data();

  for(int i=0; i<static_cast<int>(mf09.size()); i++)
  {
    Integer mt_no = mf09[i].get_mt_no();
    if( mt_no != unassigned_mt_no )
    {
      vector<Integer> lfs = mf09[i].get_LFS();
      for(int j=0; j<static_cast<int>(lfs.size()); j++)
      {
        //Add MF=9 and MF=10 data
        Integer mt_add = mt_no * 10000 +  900 + lfs[j]; // 900 = MF9  * 100
        xs_type_list.push_back(mt_add);

        mt_add = mt_no * 10000 + 1000 + lfs[j]; //1000 = MF10 * 100
        xs_type_list.push_back(mt_add);
      }
    }
  }
  vector<MF09Parser>().swap(mf09);

  //Get MF=10 data
  vector<MF10Parser> mf10 = endf_obj.get_mf10_data();

  for(int i=0; i<static_cast<int>(mf10.size()); i++)
  {
    Integer mt_no = mf10[i].get_mt_no();
    if( mt_no != unassigned_mt_no )
    {
      vector<Integer> lfs = mf10[i].get_LFS();
      for(int j=0; j<static_cast<int>(lfs.size()); j++)
      {
        Integer mt_add = mt_no * 10000 + 1000 + lfs[j]; //1000 = MF10 * 100

        int mt_chk = -1;
        for(int k=0; k<static_cast<int>(xs_type_list.size()); k++)
        {
          if( mt_add == xs_type_list[k] )
          {
            mt_chk = k;
            break;
          }
        }
        if( mt_chk < 0 )
        {
          xs_type_list.push_back(mt_add);
        }
      }
    }
  }
  vector<MF10Parser>().swap(mf10);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotEndfData::set_xs_data(Endf6Parser& endf_obj,  vector<Integer> xs_type_list,
                              vector<vector<Real> >& e_int_xs, vector<vector<Real> >& xs_tab)
{
  //Resize xs data
  int xs_data_no = static_cast<int>(xs_type_list.size());
  e_int_xs.resize(xs_data_no);
  xs_tab.resize(xs_data_no);

  for(int i=0; i<xs_data_no; i++)
  {
    e_int_xs[i].clear();
    xs_tab[i].clear();

    int mt = xs_type_list[i];
    if( mt < 1000 )
    {
      set_mf03_data(endf_obj, mt, e_int_xs[i], xs_tab[i]);
    }
    else if( mt == 1452 || mt == 2452 )
    {
      set_mf01mt452_data(endf_obj, e_int_xs[i], xs_tab[i]);
    }
    else if( mt == 1455 || mt == 2455 )
    {
      set_mf01mt455_data(endf_obj, e_int_xs[i], xs_tab[i]);
    }
    else if( mt == 1456 || mt == 2456 )
    {
      set_mf01mt456_data(endf_obj, e_int_xs[i], xs_tab[i]);
    }
    else
    {
      int mf = (mt % 10000) / 1000;
      if( mf == 9 )
      {
        set_mf09_data(endf_obj, mt, e_int_xs[i], xs_tab[i]);
      }
      else if( mf == 10 )
      {
        set_mf10_data(endf_obj, mt, e_int_xs[i], xs_tab[i]);
      }
      else if( mf == 3 )
      {
        int mt_mod = (mt / 10000);
        set_mf03_data(endf_obj, mt_mod, e_int_xs[i], xs_tab[i]);
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotEndfData::set_mf03_data(Endf6Parser& endf_obj, int mt_no,
                                 vector<Real>& e_int_xs, vector<Real>& xs_tab)
{
  e_int_xs.clear();
  xs_tab.clear();

  vector<MF03Parser> mf03 = endf_obj.get_mf03_data();
  for(int i=0; i<static_cast<int>(mf03.size()); i++)
  {
    if( mt_no ==  mf03[i].get_mt_no() )
    {
      vector<Integer> range_vec = mf03[i].get_NBT_SIG();
      vector<Integer> int_vec   = mf03[i].get_INT_SIG();
                      e_int_xs  = mf03[i].get_E_INT_SIG();
                      xs_tab    = mf03[i].get_SIG_TAB();
      lin_tab_obj.linearize_tab1_data(range_vec, int_vec, e_int_xs, xs_tab);
      break;
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotEndfData::set_mf01mt452_data(Endf6Parser& endf_obj,
                                      vector<Real>& e_int_xs, vector<Real>& xs_tab)
{
  e_int_xs.clear();
  xs_tab.clear();

  MF01MT452Parser mt452_obj = endf_obj.get_mf01_mt452_data();
  if( mt452_obj.get_LNU() == 1 )
  {
    //Polynomial representation
    vector<Real> nu_vec = mt452_obj.get_C();
    calc_nu_data(nu_vec, e_int_xs, xs_tab);
  }
  else if( mt452_obj.get_LNU() == 2 )
  {
    //Tabulated representation
    vector<Integer> range_vec = mt452_obj.get_NBT();
    vector<Integer> int_vec   = mt452_obj.get_INT();
                    e_int_xs  = mt452_obj.get_E_INT();
                    xs_tab    = mt452_obj.get_NU();
    lin_tab_obj.linearize_tab1_data(range_vec, int_vec, e_int_xs, xs_tab);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotEndfData::set_mf01mt455_data(Endf6Parser& endf_obj,
                                      vector<Real>& e_int_xs, vector<Real>& xs_tab)
{
  e_int_xs.clear();
  xs_tab.clear();

  MF01MT455Parser mt455_obj = endf_obj.get_mf01_mt455_data();
  if( mt455_obj.get_LNU() == 1 )
  {
    //Polynomial representation
    vector<Real> nu_vec = mt455_obj.get_NU();
    calc_nu_data(nu_vec, e_int_xs, xs_tab);
  }
  else if( mt455_obj.get_LNU() == 2 )
  {
    //Tabulated representation
    vector<Integer> range_vec = mt455_obj.get_NBT_NU();
    vector<Integer> int_vec   = mt455_obj.get_INT_NU();
                    e_int_xs  = mt455_obj.get_E_INT_NU();
                    xs_tab    = mt455_obj.get_NU();
    lin_tab_obj.linearize_tab1_data(range_vec, int_vec, e_int_xs, xs_tab);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotEndfData::set_mf01mt456_data(Endf6Parser& endf_obj,
                                      vector<Real>& e_int_xs, vector<Real>& xs_tab)
{
  e_int_xs.clear();
  xs_tab.clear();

  MF01MT456Parser mt456_obj = endf_obj.get_mf01_mt456_data();
  if( mt456_obj.get_LNU() == 1 )
  {
    //Polynomial representation
    vector<Real> nu_vec = mt456_obj.get_NU();
    calc_nu_data(nu_vec, e_int_xs, xs_tab);
  }
  else if( mt456_obj.get_LNU() == 2 )
  {
    //Tabulated representation
    vector<Integer> range_vec = mt456_obj.get_NBT();
    vector<Integer> int_vec   = mt456_obj.get_INT();
                    e_int_xs  = mt456_obj.get_E_INT();
                    xs_tab    = mt456_obj.get_NU();
    lin_tab_obj.linearize_tab1_data(range_vec, int_vec, e_int_xs, xs_tab);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotEndfData::set_mf09_data(Endf6Parser& endf_obj, int mt_no,
                                 vector<Real>& e_int_xs, vector<Real>& xs_tab)
{
  e_int_xs.clear();
  xs_tab.clear();

  int mt       =  mt_no / 10000;
  int state_no = (mt_no %   100);

  vector<MF09Parser> mf09 = endf_obj.get_mf09_data();
  for(int i=0; i<static_cast<int>(mf09.size()); i++)
  {
    if( mt ==  mf09[i].get_mt_no() )
    {
      vector<Integer> lfs_vec = mf09[i].get_LFS();
      for(int j=0; j<static_cast<int>(lfs_vec.size()); j++)
      {
        if( lfs_vec[j] == state_no )
        {
          vector<Integer> range_vec = mf09[i].get_NBT_Y()[j];
          vector<Integer> int_vec   = mf09[i].get_INT_Y()[j];
                          e_int_xs  = mf09[i].get_E_INT_Y()[j];
                          xs_tab    = mf09[i].get_Y_TAB()[j];
          lin_tab_obj.linearize_tab1_data(range_vec, int_vec, e_int_xs, xs_tab);
          break;
        }
      }
    }

    if( static_cast<int>(e_int_xs.size()) > 0 )
    {
      break;
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotEndfData::set_mf10_data(Endf6Parser& endf_obj, int mt_no,
                                 vector<Real>& e_int_xs, vector<Real>& xs_tab)
{
  e_int_xs.clear();
  xs_tab.clear();

  int mt       =  mt_no / 10000;
  int state_no = (mt_no %   100);

  vector<MF10Parser> mf10 = endf_obj.get_mf10_data();
  for(int i=0; i<static_cast<int>(mf10.size()); i++)
  {
    if( mt ==  mf10[i].get_mt_no() )
    {
      vector<Integer> lfs_vec = mf10[i].get_LFS();
      for(int j=0; j<static_cast<int>(lfs_vec.size()); j++)
      {
        if( lfs_vec[j] == state_no )
        {
          vector<Integer> range_vec = mf10[i].get_NBT_S()[j];
          vector<Integer> int_vec   = mf10[i].get_INT_S()[j];
                          e_int_xs  = mf10[i].get_E_INT_S()[j];
                          xs_tab    = mf10[i].get_S_TAB()[j];
          lin_tab_obj.linearize_tab1_data(range_vec, int_vec, e_int_xs, xs_tab);
          break;
        }
      }
    }

    if( static_cast<int>(e_int_xs.size()) > 0 )
    {
      break;
    }
  }

  if( static_cast<int>(e_int_xs.size()) == 0 )
  {
    calc_mf10_data(endf_obj, mt_no, e_int_xs, xs_tab);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotEndfData::calc_mf10_data(Endf6Parser& endf_obj, int mt_no,
                                  vector<Real>& e_int_xs, vector<Real>& xs_tab)
{
  e_int_xs.clear();
  xs_tab.clear();

  int mt       =  mt_no / 10000;
  int mt_mod   =  mt_no - 100; //MF10 (10*100) -> MF9 (9*100)


  set_mf03_data(endf_obj, mt, e_int_xs, xs_tab);

  vector<Real> ene_yield, yield_vec;
  set_mf09_data(endf_obj, mt_mod, ene_yield, yield_vec);

  if( static_cast<int>(e_int_xs.size())  > 0 &&
      static_cast<int>(ene_yield.size()) > 0 )
  {
    TabInterpolator ti_obj;
    for(int i=0; i<static_cast<int>(e_int_xs.size()); i++)
    {
      Real yield_val = 0.0;
      ti_obj.interpolation_1d(int_lin_lin, e_int_xs[i], yield_val, ene_yield, yield_vec);

      xs_tab[i] *= yield_val;
    }
  }
  else
  {
    e_int_xs.clear();
    xs_tab.clear();
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotEndfData:: calc_nu_data(vector<Real>& coef_vec,
                                 vector<Real>& ene_vec, vector<Real>& nu_vec)
{
  nu_vec.clear();

  int coef_no = static_cast<int>(coef_vec.size());
  if( coef_no == 0 )
  {
    return;
  }

  int ene_no  = static_cast<int>(ene_vec.size());
  if( ene_no == 0 )
  {
    ene_vec.clear();
    Real ene_min = 1.0E-5;
    Real ene_max = 2.0E+7;

    int j_max = 3;
    vector<Real> ene_add;
    ene_add.resize(j_max);

    ene_vec.push_back(ene_min);
    for(int i=-5; i<8; i++)
    {
      Real ene_val = pow(10.0, i); 
      ene_add[0] = ene_val * 1.0;
      ene_add[1] = ene_val * 2.0;
      ene_add[2] = ene_val * 5.0;

      for(int j=0; j<j_max; j++)
      {
        if( ene_add[j] * 1.001 > ene_min && ene_add[j] * 0.999 < ene_max )
        {
          ene_vec.push_back(ene_add[j]);
        }
      }
    }
    ene_vec.push_back(ene_max);

    sort(ene_vec.begin(), ene_vec.end());
  }
  ene_no = static_cast<int>(ene_vec.size());

  nu_vec.resize(ene_no);
  for(int i=0; i<ene_no; i++)
  {
    nu_vec[i] = coef_vec[0];

    Real ene_coef = ene_vec[i];
    for(int j=1; j<coef_no; j++)
    {
      nu_vec[i] += coef_vec[j] * ene_coef;
      ene_coef  *= ene_vec[i];
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotEndfData::resonance_reconstruction(Endf6Parser& endf_obj, Real err, Real err_max, Real err_int)
{
  //Convert Endf6Parser object to NuclearDataObject using Endf6Converter
  NuclearDataObject nucl_data_obj;
  Endf6Converter    conv_obj;
  conv_obj.convert_endf_format_to_frendy(endf_obj, nucl_data_obj);

  //*** Resonance reconstruction ***
  //Check interpolation scheme of all cross section data
  int linearization_flg = 0;
  vector<CrossSectionDataContainer> xs_data_obj;
  xs_data_obj = nucl_data_obj.get_nucl_reaction_data_obj().get_xs_data_obj_assigned();
  int i_max = static_cast<int>(xs_data_obj.size());
  for(int i=0; i<i_max; i++)
  {
    vector<Integer> int_vec = xs_data_obj[i].get_xs_int_data();

    int j_max = static_cast<int>(int_vec.size());
    for(int j=0; j<j_max; j++)
    {
      if( int_vec[j] != int_lin_lin )
      {
        linearization_flg++;
        break;
      }
    }

    if( linearization_flg > 0 ) break;
  }
  vector<CrossSectionDataContainer>().swap(xs_data_obj);

  int reso_flg = 0;
  vector<vector<Integer> > lru = endf_obj.get_mf02_mt151_data().get_LRU();
  for(int i=0; i<static_cast<int>(lru.size()); i++)
  {
    for(int j=0; j<static_cast<int>(lru[i].size()); j++)
    {
      if( lru[i][j] > 0 )
      {
        reso_flg++;
      }
    }
  }
  lru.clear();

  int mod_flg = 0;
  if( reso_flg > 0 || linearization_flg > 0 )
  {
    cout << "  Resonance reconstruction" << endl;
    mod_flg++;

    ResonanceXSReconstructor  recon_obj;
    recon_obj.clear();

    //Set NuclearDataObject and input data to ResonanceXSReconstructor 
    recon_obj.set_nucl_data_obj(nucl_data_obj);
    recon_obj.set_modify_photon_data_flg(1); //modify photon data
    recon_obj.set_err(err);
    recon_obj.set_err_int(err_int);
    recon_obj.set_err_max(err_max);

    //Run ResonanceXSReconstructor
    recon_obj.output_set_data_information();
    recon_obj.calc_reconstruct_resonance_xs();

    //Get calculation result
    nucl_data_obj = recon_obj.get_nucl_data_obj();
    recon_obj.clear();
    cout << endl;
  }

  if( mod_flg > 0 )
  {
    //Convert NuclearDataObject to Endf6Parser object using Endf6Converter
    MF01MT452Parser    mt452_obj = endf_obj.get_mf01_mt452_data();
    MF01MT455Parser    mt455_obj = endf_obj.get_mf01_mt455_data();
    MF01MT456Parser    mt456_obj = endf_obj.get_mf01_mt456_data();
    vector<MF09Parser> mf09      = endf_obj.get_mf09_data();

    endf_obj.clear();
    conv_obj.convert_frendy_to_endf_format(nucl_data_obj, endf_obj);
    nucl_data_obj.clear();

    endf_obj.set_mf01_mt452_data(mt452_obj);
    endf_obj.set_mf01_mt455_data(mt455_obj);
    endf_obj.set_mf01_mt456_data(mt456_obj);
    endf_obj.set_mf09_data(mf09);
    mt452_obj.clear();
    mt455_obj.clear();
    mt456_obj.clear();
    vector<MF09Parser>().swap(mf09);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotEndfData::plot_endf(Endf6Parser& endf_obj, vector<Integer>& xs_type_list,
                             vector<vector<Real> >& e_int_xs, vector<vector<Real> >& xs_tab,
                             Real err, Real err_max, Real err_int)
{
  resonance_reconstruction(endf_obj, err, err_max, err_int);

  if( static_cast<int>(xs_type_list.size()) == 0 )
  {
    set_xs_type_list(endf_obj, xs_type_list);
  }

  set_xs_data(endf_obj, xs_type_list, e_int_xs, xs_tab);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotEndfData::plot_endf(string file_name, vector<Integer>& xs_type_list,
                             vector<vector<Real> >& e_int_xs, vector<vector<Real> >& xs_tab,
                             Integer mat, Real temp, Real err, Real err_max, Real err_int)
{
  if( mat <= 0 )
  {
    plot_endf(file_name, xs_type_list, e_int_xs, xs_tab, temp, err, err_max, err_int);
    return;
  }


  EndfTapeDivider div_obj;
  div_obj.set_file_name(file_name);
  vector<string> text_vec = div_obj.get_nearby_temp_data(mat, temp);
  if( static_cast<int>(text_vec.size()) == 0 )
  {
    return;
  }


  //Allocate Endf6Parser class to endf_obj;
  Endf6Parser endf_obj;

  //Set pendf file name
  endf_obj.set_text_no_cov(text_vec);
  temp_ori = endf_obj.get_mf01_mt451_data().get_TEMP();

  plot_endf(endf_obj, xs_type_list, e_int_xs, xs_tab, temp, err, err_max, err_int);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotEndfData::plot_endf(string file_name, vector<Integer>& xs_type_list,
                             vector<vector<Real> >& e_int_xs, vector<vector<Real> >& xs_tab,
                             Real temp, Real err, Real err_max, Real err_int)
{
  //Allocate Endf6Parser class to endf_obj;
  Endf6Parser endf_obj;

  //Set pendf file name
  endf_obj.set_file_name_no_cov(file_name);
  temp_ori = endf_obj.get_mf01_mt451_data().get_TEMP();

  plot_endf(endf_obj, xs_type_list, e_int_xs, xs_tab, temp, err, err_max, err_int);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotEndfData::plot_endf(Endf6Parser& endf_obj, vector<Integer>& xs_type_list,
                             vector<vector<Real> >& e_int_xs, vector<vector<Real> >& xs_tab,
                             Real temp, Real err, Real err_max, Real err_int)
{
  plot_endf(endf_obj, xs_type_list, e_int_xs, xs_tab, err, err_max, err_int);

  if( temp > -1.0 * min_value )
  {
    //Doppler broadening
    Real awr      = endf_obj.get_mf01_mt451_data().get_AWR();
    cout << "Doppler broadening from " << temp_ori << " [K] to " << temp << " [K]." << endl;
    calc_dop_obj.calc_doppler_broadened_xs_from_xs_table
      (temp_ori, temp, awr, xs_type_list, e_int_xs, xs_tab);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotEndfData::plot_endf(string file_name, vector<Integer>& xs_type_list,
                             vector<vector<Real> >& e_int_xs, vector<vector<Real> >& xs_tab,
                             Real err, Real err_max, Real err_int)
{
  //Allocate Endf6Parser class to endf_obj;
  Endf6Parser endf_obj;

  //Set pendf file name
  endf_obj.set_file_name_no_cov(file_name);

  plot_endf(endf_obj, xs_type_list, e_int_xs, xs_tab, err, err_max, err_int);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotEndfData::plot_endf(Endf6Parser& endf_obj, vector<Integer>& xs_type_list,
                             vector<vector<Real> >& e_int_xs, vector<vector<Real> >& xs_tab)
{
  Real err     = 1.0E-3;
  Real err_max = err * 10.0;
  Real err_int = err / 20000.0;

  plot_endf(endf_obj, xs_type_list, e_int_xs, xs_tab, err, err_max, err_int);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotEndfData::plot_endf(string file_name, vector<Integer>& xs_type_list,
                             vector<vector<Real> >& e_int_xs, vector<vector<Real> >& xs_tab)
{
  //Allocate Endf6Parser class to endf_obj;
  Endf6Parser endf_obj;

  //Set pendf file name
  endf_obj.set_file_name_no_cov(file_name);

  plot_endf(endf_obj, xs_type_list, e_int_xs, xs_tab);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Real PlotEndfData::get_temp_ori()
{
  return temp_ori;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

