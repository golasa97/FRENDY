#include "ReconResonance/ResonanceEnergyGridLinearizer.hpp"

using namespace frendy;

//constructor
ResonanceEnergyGridLinearizer::ResonanceEnergyGridLinearizer(void)
{
  clear();
}

//destructor
ResonanceEnergyGridLinearizer::~ResonanceEnergyGridLinearizer(void)
{
  clear();
  specified_grid.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ResonanceEnergyGridLinearizer::add_resonance_grid()
{
  //Add lower and upper limit energy (EL and EH)
  add_limit_energy_grid();

  if( reso_flg == 1 )
  {
    for(int i=0; i<nis; i++)
    {
      for(int j=0; j<ner[i]; j++)
      {
        vector<Real8> ene_data;
        ene_data = ene_array[i][j];

        //Add additional energy grid (1.0e+x, 2.0e+x, 5.0e+x)
        add_additional_energy_grid(ene_data);

        //Add user specified energy grid (0.0253, and so on)
        add_user_specified_energy_grid(ene_data, specified_grid);

        //Add case own energy grid (LRU=1, LRF=1-4, LRU=2, CaseA-C)
        add_case_own_additional_energy_grid(i, j, ene_data);

        ta_obj.delete_overlap_grid(ene_data);
        //delete_el_and_eh(i, j, ene_data);
        ene_array[i][j] = ene_data;
        ene_data.clear();
      }
    }
  }
  else
  {
    clr_obj.clear_vec_array3_real8(ene_array);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ResonanceEnergyGridLinearizer::add_limit_energy_grid()
{
  //Set EL and EH at each NIS and NER
  //To consider energy grid from el to digit_obj.get_adjusted_value(el, sig_fig-1, +1.0) and
  //from digit_obj.get_adjusted_value(eh, sig_fig-1, -1.0) to eh at add_user_specified_energy_grid,
  //high and low energy limit is added in this function. 
  ene_array.resize(nis);
  for(int i=0; i<nis; i++)
  {
    ene_array[i].resize(ner[i]);
    for(int j=0; j<ner[i]; j++)
    {
      Real8 el = static_cast<Real8>(reso_data_obj.get_lower_ene_limit()[i][j]);
      Real8 eh = static_cast<Real8>(reso_data_obj.get_upper_ene_limit()[i][j]);
      if( reso_region_flg[i][j] == 0 )
      {
        ene_array[i][j].push_back(el);
      }
      else if( fabs(el - 1.0e-5) < 1.0e-6 && reso_region_flg[i][j] != 2 )
      {
        el = 1.0e-5;
        ene_array[i][j].push_back(el);
        ene_array[i][j].push_back(digit_obj.get_adjusted_value(el, sig_fig, +1.0));
      }
      else
      {
        ene_array[i][j].push_back(digit_obj.get_adjusted_value(el, sig_fig, -1.0));
        //ene_array[i][j].push_back(el);
        ene_array[i][j].push_back(digit_obj.get_adjusted_value(el, sig_fig, +1.0));
      }

      if( reso_region_flg[i][j] == 0 )
      {
        ene_array[i][j].push_back(eh);
      }
      else
      {
        ene_array[i][j].push_back(digit_obj.get_adjusted_value(eh, sig_fig, -1.0));
        //ene_array[i][j].push_back(eh);
        ene_array[i][j].push_back(digit_obj.get_adjusted_value(eh, sig_fig, +1.0));
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ResonanceEnergyGridLinearizer::add_additional_energy_grid(vector<Real8>& ene_data)
{
  vector<Real8>   new_ene;
  new_ene.clear();

  Real8 ene_adj;
  vector<Real8> multi_value;
  multi_value.push_back(1.0);
  multi_value.push_back(2.0);
  multi_value.push_back(5.0);

  int i_max  = static_cast<int>(ene_data.size());
  int j_max  = static_cast<int>(multi_value.size());
  for(int i=0; i<i_max; i++)
  {
    if( i > 0 )
    {
      Integer add_flg = 1;
      Integer digit   = digit_obj.get_digit_number(ene_data[i-1]);
      Real8 ene       = pow(10.0, digit);
      while( ene_data[i] > ene || add_flg > 0 )
      {
        add_flg = 0;

        //Add a*1.0e+x or a*2.0e+x or a*5.0e+x
        for(int j=0; j<j_max; j++)
        {
          ene_adj = ene*multi_value[j];
          if( ene_data[i] > ene_adj && ene_data[i-1] < ene_adj )
          {
            new_ene.push_back(ene_adj);
            add_flg=1;
          }
        }

        ene = ene*10.0;
      }
    }
    new_ene.push_back(ene_data[i]);
  }
  ene_data = new_ene;
  new_ene.clear();
  multi_value.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ResonanceEnergyGridLinearizer::add_user_specified_energy_grid
                                      (vector<Real8>& ene_data, vector<Real8>& add_grid)
{
  Integer grid_chk = 0;
  int     grid_no  = 0;
  int     grid_max = static_cast<int>(add_grid.size());
  int     i_max    = static_cast<int>(ene_data.size());
  if( i_max > 0 )
  {
    for(int i=0; i<grid_max; i++)
    {
      if(ene_data[0] < add_grid[i])
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
  
  vector<Real8> new_ene;
  new_ene.clear();

  Real8 ene_adj = add_grid[grid_no];
  for(int i=0; i<i_max; i++)
  {
    if( i > 0 )
    {
      Integer add_flg = 1;
      while( grid_no < grid_max && add_flg > 0 )
      {
        add_flg = 0;

        if( ene_data[i] > ene_adj && ene_data[i-1] < ene_adj )
        {
          new_ene.push_back(ene_adj);
          grid_no++;

          if( grid_no < grid_max )
          {
            ene_adj = add_grid[grid_no];
            add_flg=1;
          }
        }
        else if( ene_data[i] > add_grid[grid_no] ) //If the indentical energy grid was exist.
        {
          grid_no++;

          if( grid_no < grid_max )
          {
            ene_adj = add_grid[grid_no];
            add_flg=1;
          }
        }
      }
    }
    new_ene.push_back(ene_data[i]);
  }
  ene_data = new_ene;
  new_ene.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ResonanceEnergyGridLinearizer::add_case_own_additional_energy_grid(int& i, int& j, vector<Real8>& ene_data)
{
  Integer reso_region_flg_val = reso_region_flg[i][j];
  Integer xs_formula_flg_val  = xs_formula_flg[i][j];

  if( reso_region_flg_val==1 )
  {
    if( xs_formula_flg_val==1 || xs_formula_flg_val==2 || xs_formula_flg_val==3 )
    {
      add_additional_energy_grid_reso_general(i, j, ene_data);
    }
    else if( xs_formula_flg_val==4 )
    {
      add_additional_energy_grid_reso_adler(i, j, ene_data);
    }
  }
  else if( reso_region_flg_val==2 )
  {
    Integer fis_width_flg_val = reso_data_obj.get_fis_width_flg()[i];
    if( xs_formula_flg_val==1 && fis_width_flg_val==0 )
    {
      add_additional_energy_grid_unreso_a(ene_data);
    }
    else if( xs_formula_flg_val==1 && fis_width_flg_val==1 )
    {
      add_additional_energy_grid_unreso_b_c(i, j, ene_data, xs_formula_flg_val);
    }
    else if( xs_formula_flg_val==2 )
    {
      add_additional_energy_grid_unreso_b_c(i, j, ene_data, xs_formula_flg_val);
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ResonanceEnergyGridLinearizer::add_additional_energy_grid_reso_general
                                      (int& i, int& j, vector<Real8>& ene_data)
{
  Integer xs_formula_flg_val = xs_formula_flg[i][j];
  vector<Real8> er_vec;
  er_vec.clear();

  vector<vector<Real> > ene_reso;
  if( xs_formula_flg_val == 1 || xs_formula_flg_val == 2 )
  {
    ene_reso = reso_data_obj.get_bw_data_obj(i,j).get_ene_reso();
  }
  else if(xs_formula_flg_val == 3)
  {
    ene_reso = reso_data_obj.get_rm_data_obj(i,j).get_ene_reso();
  }
  else if(xs_formula_flg_val == 7)
  {
    ene_reso = reso_data_obj.get_r_matrix_data_obj(i,j).get_ene_reso();
  }

  Real8 hw = 0.0;
  int k_max = static_cast<int>(ene_reso.size());
  for(int k=0; k<k_max; k++)
  {
    int l_max = static_cast<int>(ene_reso[k].size());
    for(int l=0; l<l_max; l++)
    {
      Real8 er = static_cast<Real8>(ene_reso[k][l]);
      er_vec.push_back(er);

      hw = 0.0;
      if(xs_formula_flg_val == 1 || xs_formula_flg_val == 2)
      {
        hw = 0.5*reso_data_obj.get_bw_data_obj(i,j).get_gam_width_tot()[k][l];
      }
      else if(xs_formula_flg_val == 3)
      {
        Real8 gn  = reso_data_obj.get_rm_data_obj(i,j).get_gam_width_n()[k][l];
        Real8 gg  = reso_data_obj.get_rm_data_obj(i,j).get_gam_width_rad()[k][l];
        Real8 gfa = reso_data_obj.get_rm_data_obj(i,j).get_gam_width_fis_a()[k][l];
        Real8 gfb = reso_data_obj.get_rm_data_obj(i,j).get_gam_width_fis_b()[k][l];

        hw = 0.5*(gn + gg + fabs(gfa) + fabs(gfb));
      }
      er_vec.push_back(er+hw);
      er_vec.push_back(er-hw);
    }
  }
  ta_obj.delete_overlap_grid(er_vec);

  //add er, er+hw/2, er-hw/2 to ene_data
  add_user_specified_energy_grid(ene_data, er_vec);

  er_vec.clear();
  clr_obj.clear_vec_array2_real(ene_reso);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ResonanceEnergyGridLinearizer::add_additional_energy_grid_reso_adler
                                      (int& i, int& j, vector<Real8>& ene_data)
{
  vector<Real8> add_ene_vec;
  add_ene_vec.clear();

  vector<vector<vector<Real> > > ene_reso_tot, gam_width_half_tot;
  ene_reso_tot       = reso_data_obj.get_adler_data_obj(i,j).get_ene_reso_tot();
  gam_width_half_tot = reso_data_obj.get_adler_data_obj(i,j).get_gam_width_half_tot();

  int k_max = static_cast<int>(ene_reso_tot.size());
  for(int k=0; k<k_max; k++)
  {
    int l_max = static_cast<int>(ene_reso_tot[k].size());
    for(int l=0; l<l_max; l++)
    {
      int m_max = static_cast<int>(ene_reso_tot[k][l].size());
      for(int m=0; m<m_max; m++)
      {
        Real8 ert = static_cast<Real8>(ene_reso_tot[k][l][m]);
        Real8 gwht = static_cast<Real8>(gam_width_half_tot[k][l][m]);
        add_ene_vec.push_back(ert);
        add_ene_vec.push_back(ert+gwht);
        add_ene_vec.push_back(ert-gwht);
      }
    }
  }
  ta_obj.delete_overlap_grid(add_ene_vec);

  //add ene_reso_tot, ene_reso_tot+am_width_half_tot/2 and ene_reso_tot-am_width_half_tot/2 to ene_data
  add_user_specified_energy_grid(ene_data, add_ene_vec);

  add_ene_vec.clear();
  clr_obj.clear_vec_array3_real(ene_reso_tot);
  clr_obj.clear_vec_array3_real(gam_width_half_tot);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ResonanceEnergyGridLinearizer::add_additional_energy_grid_unreso_a(vector<Real8>& ene_data)
{
  vector<Real8>   new_ene;
  new_ene.clear();

  Real8 ene_adj;
  vector<Real8> multi_value;
  //multi_value.push_back(1.00);
  multi_value.push_back(1.25);
  multi_value.push_back(1.50);
  multi_value.push_back(1.70);
  //multi_value.push_back(2.00);
  multi_value.push_back(2.50);
  multi_value.push_back(3.00);
  multi_value.push_back(3.50);
  multi_value.push_back(4.00);
  //multi_value.push_back(5.00);
  multi_value.push_back(6.00);
  multi_value.push_back(7.20);
  multi_value.push_back(8.50);

  int i_max  = static_cast<int>(ene_data.size());
  int j_max  = static_cast<int>(multi_value.size());
  for(int i=0; i<i_max; i++)
  {
    if( i > 0 )
    {
      Integer add_flg = 1;
      Integer digit   = digit_obj.get_digit_number(ene_data[i-1]);
      Real8 ene       = pow(10.0, digit);
      while( ene_data[i] > ene || add_flg > 0 )
      {
        add_flg = 0;

        //Add a*1.0e+x or a*2.0e+x or a*5.0e+x
        for(int j=0; j<j_max; j++)
        {
          ene_adj = ene*multi_value[j];
          if( ene_data[i] > ene_adj && ene_data[i-1] < ene_adj )
          {
            new_ene.push_back(ene_adj);
            add_flg=1;
          }
        }

        ene = ene*10.0;
      }
    }
    new_ene.push_back(ene_data[i]);
  }
  ene_data = new_ene;
  new_ene.clear();
  multi_value.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ResonanceEnergyGridLinearizer::add_additional_energy_grid_unreso_b_c
                                      (int& i, int& j, vector<Real8>& ene_data, Integer& xs_formula_flg_val)
{
  vector<Real8> new_ene, ene_unreso_vec;
  new_ene = ene_data;
  ene_unreso_vec.clear();

  vector<vector<vector<Real> > > ene_unreso_ori = reso_data_obj.get_unreso_data_obj(i,j).get_ene_unreso();
  Real el = reso_data_obj.get_lower_ene_limit()[i][j] * (1.0 + min_ene_dif);
  Real eh = reso_data_obj.get_upper_ene_limit()[i][j] * (1.0 - min_ene_dif);
  int k_max = static_cast<int>(ene_unreso_ori.size());
  for(int k=0; k<k_max; k++)
  {
    int l_max =static_cast<int>(ene_unreso_ori[k].size());
    for(int l=0; l<l_max; l++)
    {
      int m_max =static_cast<int>(ene_unreso_ori[k][l].size());
      for(int m=0; m<m_max; m++)
      {
        if( ene_unreso_ori[k][l][m] > el && ene_unreso_ori[k][l][m] < eh )
        {
          ene_unreso_vec.push_back(static_cast<Real8>(ene_unreso_ori[k][l][m]));
        }
      }
    }
  }
  ta_obj.delete_overlap_grid(ene_unreso_vec);

  vector<Real8> tmp_ene;
  tmp_ene.clear();

  k_max = static_cast<int>(ene_unreso_vec.size());
  if( k_max > 0 )
  {
    Real8 max_ene_distance = 1.26;
    new_ene.push_back(ene_unreso_vec[0]);
    for(int k=1; k<k_max; k++)
    {
      new_ene.push_back(ene_unreso_vec[k]);
      if( ene_unreso_vec[k]/ene_unreso_vec[k-1] >= max_ene_distance )
      {
        tmp_ene.push_back(ene_unreso_vec[k-1]);
        tmp_ene.push_back(ene_unreso_vec[k]);
        add_additional_energy_grid_unreso_a(tmp_ene);
      
        int l_max = static_cast<int>(tmp_ene.size());
        for(int l=1; l<l_max-1; l++) //l=0:ene_unreso_vec[k-1], l=l_max-1:ene_unreso_vec[k]
        {
          new_ene.push_back(tmp_ene[l]);
        }
        tmp_ene.clear();
      }
    }
  }
  ta_obj.delete_overlap_grid(new_ene);
  ene_data = new_ene;
  new_ene.clear();
  ene_unreso_vec.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ResonanceEnergyGridLinearizer::delete_el_and_eh(int& i, int& j, vector<Real8>& base_grid)
{
  vector<Real8> sorted_data;
  sorted_data.clear();

  int   i_max  = static_cast<int>(base_grid.size());
  Real8 el     = static_cast<Real8>(reso_data_obj.get_lower_ene_limit()[i][j]);
  Real8 eh     = static_cast<Real8>(reso_data_obj.get_upper_ene_limit()[i][j]);
  Real8 el_dif = el * min_ene_dif;
  Real8 eh_dif = eh * min_ene_dif;

  for(int i=0; i<i_max; i++)
  {
    if( fabs(base_grid[i] - el) > el_dif && fabs(base_grid[i] - eh) > eh_dif )
    {
      sorted_data.push_back(base_grid[i]);
    }
  }
  base_grid = sorted_data;
  sorted_data.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ResonanceEnergyGridLinearizer::clear()
{
  specified_grid.clear();
  specified_grid.push_back(conv_th_ene);

  nucl_data_obj.clear();
  reso_data_obj.clear();

  reso_flg = 0;
  nis      = 0;
  ner.clear();
  clr_obj.clear_vec_array2_int(reso_region_flg);
  clr_obj.clear_vec_array2_int(xs_formula_flg);
  clr_obj.clear_vec_array3_real8(ene_array);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ResonanceEnergyGridLinearizer::set_user_specified_grid(vector<Real8> real_vec)
{
  specified_grid = real_vec;

  specified_grid.push_back(conv_th_ene);
  ta_obj.delete_overlap_grid(specified_grid);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ResonanceEnergyGridLinearizer::set_nucl_data_obj( NuclearDataObject& data_obj )
{
  nucl_data_obj = data_obj;

  reso_flg      = nucl_data_obj.get_general_data_obj().get_reso_flg();
  reso_data_obj = nucl_data_obj.get_reso_data_obj();

  reso_region_flg = reso_data_obj.get_reso_region_flg();
  xs_formula_flg  = reso_data_obj.get_xs_formula_flg();

  nis = static_cast<int>(reso_region_flg.size());
  ner.resize(nis);
  for(int i=0; i<nis; i++)
  {
    ner[i] = static_cast<int>(reso_region_flg[i].size());
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//Getter

vector<vector<vector<Real8> > > ResonanceEnergyGridLinearizer::get_resonance_grid()
{
  add_resonance_grid();
  return ene_array;
}

vector<Real8> ResonanceEnergyGridLinearizer::get_user_specified_grid()
{
  return specified_grid;
}


NuclearDataObject ResonanceEnergyGridLinearizer::get_nucl_data_obj()
{
  //nucl_data_obj.set_reso_data_obj(reso_data_obj);

  return nucl_data_obj;
}

ResonanceDataContainer ResonanceEnergyGridLinearizer::get_reso_data_obj()
{
  return reso_data_obj;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

