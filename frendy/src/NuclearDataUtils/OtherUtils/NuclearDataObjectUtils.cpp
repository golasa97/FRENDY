#include "NuclearDataUtils/OtherUtils/NuclearDataObjectUtils.hpp"

using namespace frendy;

//constructor
NuclearDataObjectUtils::NuclearDataObjectUtils(void)
{
  clear();
}

//destructor
NuclearDataObjectUtils::~NuclearDataObjectUtils(void)
{
  clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataObjectUtils::clear()
{
  caution_flg      = caution_flg_on;

  ene_min          = 1.0E-5;
  reaction_type_no = unassigned_mt_no;

  data_name.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataObjectUtils::modify_comment_data(NuclearDataObject& nucl_data_obj,
                                                 vector<string> comment_data)
{
  GeneralDataContainer general_data_obj = nucl_data_obj.get_general_data_obj();

  //Add comment line in original nuclear data file (only first and second line)
  vector<string> comment_data_ori, comment_data_mod;
  comment_data_ori = general_data_obj.get_comment_data();
  for(int i=0; i<static_cast<int>(comment_data_ori.size()); i++)
  {
    if( i == 0 || i == 1 )
    {
      comment_data_mod.push_back(comment_data_ori[i]);
    }
    else
    {
      break;
    }
  }
  clr_obj.clear_vec_array1_str(comment_data_ori);

  //Add comment line in frendy input file
  for(int i=0; i<static_cast<int>(comment_data.size()); i++)
  {
    comment_data_mod.push_back(comment_data[i]);
  }
  clr_obj.clear_vec_array1_str(comment_data);

  general_data_obj.set_comment_data(comment_data_mod);
  clr_obj.clear_vec_array1_str(comment_data_mod);

  nucl_data_obj.set_general_data_obj(general_data_obj);
  general_data_obj.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataObjectUtils::modify_xs_data_without_caution(NuclearDataObject& nucl_data_obj)
{
  caution_flg = caution_flg_off;

  modify_xs_data(nucl_data_obj);

  caution_flg = caution_flg_on;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataObjectUtils::modify_xs_data(NuclearDataObject& nucl_data_obj)
{
  NuclearReactionDataContainer            react_obj           = nucl_data_obj.get_nucl_reaction_data_obj();
  vector<CrossSectionDataContainer>       xs_data_obj         = react_obj.get_xs_data_obj();
  vector<RadioactiveProductDataContainer> radio_prod_data_obj = react_obj.get_radio_product_data_obj();
  vector<PhotonDataContainer>             photon_data_obj     = react_obj.get_photon_data_obj();

  search_ene_min(react_obj, xs_data_obj, radio_prod_data_obj, photon_data_obj);

  vector<Integer> range_vec, int_vec;
  vector<Real>    ene_vec,   xs_vec;

  vector<vector<Integer> > range_array, int_array;
  vector<vector<Real> >    ene_array,   xs_array;

  //MF=3
  data_name = "CrossSectionDataContainer";
  int i_max = static_cast<int>(xs_data_obj.size());
  for(int i=0; i<i_max; i++)
  {
    reaction_type_no = xs_data_obj[i].get_reaction_type();
    if( reaction_type_no == unassigned_mt_no )
    {
      continue;
    }

    range_vec = xs_data_obj[i].get_xs_range_data();
    int_vec   = xs_data_obj[i].get_xs_int_data();
    ene_vec   = xs_data_obj[i].get_xs_ene_data();
    xs_vec    = xs_data_obj[i].get_xs_data();

    modify_table_data(range_vec, int_vec, ene_vec, xs_vec);

    xs_data_obj[i].set_xs_range_data(range_vec);
    xs_data_obj[i].set_xs_int_data(int_vec);
    xs_data_obj[i].set_xs_ene_data(ene_vec);
    xs_data_obj[i].set_xs_data(xs_vec);
  }

  //MF=10
  data_name = "RadioactiveProductDataContainer";
  i_max = static_cast<int>(radio_prod_data_obj.size());
  for(int i=0; i<i_max; i++)
  {
    reaction_type_no = radio_prod_data_obj[i].get_reaction_type();
    if( reaction_type_no == unassigned_mt_no )
    {
      continue;
    }

    range_array = radio_prod_data_obj[i].get_xs_range_data();
    int_array   = radio_prod_data_obj[i].get_xs_int_data();
    ene_array   = radio_prod_data_obj[i].get_xs_ene_data();
    xs_array    = radio_prod_data_obj[i].get_xs_data();

    int j_max = static_cast<int>(xs_array.size());
    for(int j=0; j<j_max; j++)
    {
      modify_table_data(range_array[j], int_array[j], ene_array[j], xs_array[j]);
    }

    radio_prod_data_obj[i].set_xs_range_data(range_array);
    radio_prod_data_obj[i].set_xs_int_data(int_array);
    radio_prod_data_obj[i].set_xs_ene_data(ene_array);
    radio_prod_data_obj[i].set_xs_data(xs_array);
  }

  //MF=13
  data_name = "PhotonDataContainer";
  i_max = static_cast<int>(photon_data_obj.size());
  for(int i=0; i<i_max; i++)
  {
    reaction_type_no = photon_data_obj[i].get_reaction_type();
    if( reaction_type_no == unassigned_mt_no )
    {
      continue;
    }

    range_vec = photon_data_obj[i].get_photon_production_xs_tot_range_data();
    int_vec   = photon_data_obj[i].get_photon_production_xs_tot_int_data();
    ene_vec   = photon_data_obj[i].get_photon_production_xs_tot_ene_data();
    xs_vec    = photon_data_obj[i].get_photon_production_xs_tot_data();

    modify_table_data(range_vec, int_vec, ene_vec, xs_vec);

    photon_data_obj[i].set_photon_production_xs_tot_range_data(range_vec);
    photon_data_obj[i].set_photon_production_xs_tot_int_data(int_vec);
    photon_data_obj[i].set_photon_production_xs_tot_ene_data(ene_vec);
    photon_data_obj[i].set_photon_production_xs_tot_data(xs_vec);


    range_array = photon_data_obj[i].get_photon_production_xs_range_data();
    int_array   = photon_data_obj[i].get_photon_production_xs_int_data();
    ene_array   = photon_data_obj[i].get_photon_production_xs_ene_data();
    xs_array    = photon_data_obj[i].get_photon_production_xs_data();

    int j_max = static_cast<int>(xs_array.size());
    for(int j=0; j<j_max; j++)
    {
      modify_table_data(range_array[j], int_array[j], ene_array[j], xs_array[j]);
    }

    photon_data_obj[i].set_photon_production_xs_range_data(range_array);
    photon_data_obj[i].set_photon_production_xs_int_data(int_array);
    photon_data_obj[i].set_photon_production_xs_ene_data(ene_array);
    photon_data_obj[i].set_photon_production_xs_data(xs_array);
  }

  react_obj.set_xs_data_obj(xs_data_obj);
  react_obj.set_radio_product_data_obj(radio_prod_data_obj);
  react_obj.set_photon_data_obj(photon_data_obj);
  nucl_data_obj.set_nucl_reaction_data_obj(react_obj);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataObjectUtils::search_ene_min(NuclearReactionDataContainer&            react_obj,
                                            vector<CrossSectionDataContainer>&       xs_data_obj,
                                            vector<RadioactiveProductDataContainer>& radio_prod_data_obj,
                                            vector<PhotonDataContainer>&             photon_data_obj)
{
  ene_min = 1.0 / min_value;

  vector<Integer> reaction_type = react_obj.get_reaction_type();
  int i_max = static_cast<int>(reaction_type.size());
  for(int i=0; i<i_max; i++)
  {
    //MF= 3
    if( xs_data_obj[i].get_reaction_type() == reaction_type[i] )
    {
      vector<Real> ene_vec = xs_data_obj[i].get_xs_ene_data();
      if( static_cast<int>(ene_vec.size()) > 0 )
      {
        if( ene_min > ene_vec[0] )
        {
          ene_min = ene_vec[0];
        }
      }
    }

    //MF=10
    if( radio_prod_data_obj[i].get_reaction_type() == reaction_type[i] )
    {
      vector<vector<Real> > ene_array = radio_prod_data_obj[i].get_xs_ene_data();
      for(int j=0; j<static_cast<int>(ene_array.size()); j++)
      {
        if( static_cast<int>(ene_array[j].size()) > 0 )
        {
          if( ene_min > ene_array[j][0] )
          {
            ene_min = ene_array[j][0];
          }
        }
      }
    }

    //MF=13
    if( photon_data_obj[i].get_reaction_type() == reaction_type[i] )
    {
      vector<Real> ene_vec = photon_data_obj[i].get_photon_production_xs_tot_ene_data();
      if( static_cast<int>(ene_vec.size()) > 0 )
      {
        if( ene_min > ene_vec[0] )
        {
          ene_min = ene_vec[0];
        }
      }

      vector<vector<Real> > ene_array = photon_data_obj[i].get_photon_production_xs_ene_data();
      for(int j=0; j<static_cast<int>(ene_array.size()); j++)
      {
        if( static_cast<int>(ene_array[j].size()) > 0 )
        {
          if( ene_min > ene_array[j][0] )
          {
            ene_min = ene_array[j][0];
          }
        }
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataObjectUtils::modify_table_data(vector<Integer>& range_vec, vector<Integer>& int_vec,
                                               vector<Real>&    x_vec,     vector<Real>&    y_vec)
{
  adjust_discontinuity_data(range_vec, int_vec, x_vec, y_vec);

  int i_max = static_cast<int>(x_vec.size());
  for(int i=0; i<i_max; i++)
  {
    if( y_vec[i] < 0.0 )
    {
      y_vec[i] = 0.0;
    }
  }

  remove_zero_data(range_vec, int_vec, x_vec, y_vec);
  add_zero_data(range_vec, int_vec, x_vec, y_vec);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataObjectUtils::remove_zero_data(vector<Integer>& range_vec, vector<Integer>& int_vec,
                                              vector<Real>&    x_vec,     vector<Real>&    y_vec)
{
  int i_max = static_cast<int>(x_vec.size());
  if( i_max <= 1 )
  {
    return;
  }

  int ele_no = 0;
  for(int i=0; i<i_max; i++)
  {
    if( fabs(y_vec[i]) > min_sig_val )
    {
      ele_no = i;

      if( i > 0 )
      {
        if( fabs(x_vec[i] - x_vec[i-1]) < fabs(min_ene_dif * x_vec[i]) )
        {
          ele_no--;
        }
      }
      break;
    }
  }

  if( ele_no > 1 )
  {
    vector<Integer> range_new, int_new;
    vector<Real>    x_new,     y_new;
    for(int i=ele_no-1; i<i_max; i++)
    {
      x_new.push_back(x_vec[i]);
      y_new.push_back(y_vec[i]);
    }

    for(int i=0; i<static_cast<int>(range_vec.size()); i++)
    {
      range_vec[i] -= static_cast<Integer>(ele_no-1);

      if( range_vec[i] > 0 )
      {
        range_new.push_back(range_vec[i]);
        int_new.push_back(int_vec[i]);
      }
    }

    range_vec = range_new;
    int_vec   = int_new;
    x_vec     = x_new;
    y_vec     = y_new;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataObjectUtils::add_zero_data(vector<Integer>& range_vec, vector<Integer>& int_vec,
                                           vector<Real>&    x_vec,     vector<Real>&    y_vec)
{
  int i_max = static_cast<int>(x_vec.size());
  if( i_max == 0 )
  {
    return;
  }

  if( x_vec[0] > ene_min * 1.01 )
  {
    if( y_vec[0] > min_sig_val )
    {
      Real add_x = digit_obj.get_adjusted_value(x_vec[0], sig_fig, -1.0);
      Real add_y = 0.0;
      add_ene_grid(add_x, add_y, range_vec, int_vec, x_vec, y_vec);

      if( caution_flg == caution_flg_on )
      {
        string class_name = "NuclearDataObjectUtils";
        string func_name  = "adde_zero_data";

        ostringstream oss01, oss02, oss03, oss04, oss05;
        oss02.setf(ios::showpoint);
        oss02.setf(ios::scientific);
        oss03.setf(ios::showpoint);
        oss03.setf(ios::scientific);
        oss04.setf(ios::showpoint);
        oss04.setf(ios::scientific);
        oss05.setf(ios::showpoint);
        oss05.setf(ios::scientific);

        oss01 << reaction_type_no;
        oss02 << setw(8) << x_vec[1];
        oss03 << setw(8) << y_vec[1];
        oss04 << setw(8) << add_x;
        oss05 << setw(8) << ene_min;
        string str_data01 = "Data name       : " + data_name;
        string str_data02 = "Reaction type   : " + oss01.str();
        string str_data03 = "Minimum energy  : " + oss02.str();
        string str_data04 = "XS value        : " + oss03.str();
        string str_data05 = "Additional grid : " + oss04.str();
        string str_data06 = "(Minimum energy in this nuclear data object : " + oss05.str() + ")";

        vector<string> err_com;
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back(str_data04);
        err_com.push_back(str_data05);
        err_com.push_back(str_data06);
        err_com.push_back("Though this reaction is threshold reaction, the initial XS value is not zero.");
        err_com.push_back("FRENDY add additional energy grid to add zero XS data.");
        err_obj.output_caution(class_name, func_name, err_com);
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataObjectUtils::add_ene_grid(Real add_x, Real add_y,
                                          vector<Integer>& range_vec, vector<Integer>& int_vec,
                                          vector<Real>&    x_vec,     vector<Real>&    y_vec)
{
  int i_max = static_cast<int>(range_vec.size());
  for(int i=0; i<i_max; i++)
  {
    range_vec[i]++;
  }

  vector<Real> x_new, y_new;
  i_max = static_cast<int>(x_vec.size());
  x_new.resize(i_max+1);
  y_new.resize(i_max+1);
  x_new[0] = add_x;
  y_new[0] = add_y;
  for(int i=0; i<i_max; i++)
  {
    x_new[i+1] = x_vec[i];
    y_new[i+1] = y_vec[i];
  }

  x_vec = x_new;
  y_vec = y_new;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataObjectUtils::adjust_discontinuity_data
                               (vector<Integer>& range_vec, vector<Integer>& int_vec,
                                vector<Real>&    x_vec,     vector<Real>&    y_vec)
{
  for(int i=0; i<static_cast<int>(int_vec.size()); i++)
  {
    if( int_vec[i] != int_lin_lin )
    {
      return;
    }
  }

  int i_max = static_cast<int>(x_vec.size());
  if( i_max == 0 )
  {
    return;
  }

  vector<Real> y_new = y_vec;
  for(int i=1; i<i_max; i++)
  {
    if( fabs(x_vec[i] - x_vec[i-1]) < fabs(min_sig_dif * x_vec[i]) )
    {
      if( (fabs(y_vec[i-1]) < min_sig_val && fabs(y_vec[i]) < min_sig_val) ||
          (fabs(y_vec[i-1]) < min_sig_val && fabs(y_vec[i]) > min_sig_val) )
      {
        continue;
      }
      else if( fabs(y_vec[i] - y_vec[i-1]) < fabs(min_sig_dif * y_vec[i]) )
      {
        continue;
      }

      //Modify x_vec[i]
      if( i < i_max-2 )
      {
        ti_obj.interpolation_1d(int_lin_lin, x_vec[i], y_new[i],
                                x_vec[i+1], y_vec[i+1], x_vec[i+2], y_vec[i+2]);
      }
      else
      {
        y_new[i] = y_vec[i_max-1];
      }

      //Modify x_vec[i-1]
      if( i > 2 )
      {
        ti_obj.interpolation_1d(int_lin_lin, x_vec[i-1], y_new[i-1],
                                x_vec[i-2], y_vec[i-2], x_vec[i-3], y_vec[i-3]);
      }
      else
      {
        y_new[i-1] = y_vec[0];
      }
    }
  }
  y_vec = y_new;
  y_new.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataObjectUtils::check_total_product_xs(NuclearDataObject& nucl_data_obj)
{
  TabInterpolator ti_obj;

  NuclearReactionDataContainer            react_obj           = nucl_data_obj.get_nucl_reaction_data_obj();
  vector<RadioactiveProductDataContainer> radio_prod_data_obj = react_obj.get_radio_product_data_obj();

  //MF=10
  int i_max = static_cast<int>(radio_prod_data_obj.size());
  for(int i=0; i<i_max; i++)
  {
    reaction_type_no = radio_prod_data_obj[i].get_reaction_type();
    if( reaction_type_no == unassigned_mt_no )
    {
      continue;
    }

    vector<vector<Integer> > range_array = radio_prod_data_obj[i].get_xs_range_data();
    vector<vector<Integer> > int_array   = radio_prod_data_obj[i].get_xs_int_data();
    vector<vector<Real> >    ene_array   = radio_prod_data_obj[i].get_xs_ene_data();
    vector<vector<Real> >    xs_array    = radio_prod_data_obj[i].get_xs_data();

    int product_no = static_cast<int>(xs_array.size());
    if( product_no == 0 )
    {
      continue;
    }

    //MF=3 (Cross section data)
    CrossSectionDataContainer xs_data_obj = react_obj.get_xs_data_obj(reaction_type_no);
    if( reaction_type_no != xs_data_obj.get_reaction_type() )
    {
      continue;
    }

    vector<Real> ene_vec = xs_data_obj.get_xs_ene_data();
    vector<Real> xs_vec  = xs_data_obj.get_xs_data();

    int fatal_flg = 0;
    int ene_no    = static_cast<int>(ene_vec.size());
    if( ene_no == 0 )
    {
      continue;
    }

    vector<int>   xs_pos;
    vector<Real>  xs_rad, xs_dif;
    xs_pos.clear();
    xs_rad.clear();
    xs_dif.clear();

    //Comparing MF=3 and sum of MF=10
    for(int j=0; j<ene_no; j++)
    {
      Real xs_ori = xs_vec[j];
      //if( xs_ori < min_sig_val * 1.1 )
      if( xs_ori < 1.0E-10 )
      {
        continue;
      }

      Real xs_tot = 0.0;
      for(int k=0; k<product_no; k++)
      {
        Real xs_part = 0.0;
        ti_obj.interpolation_tab1(ene_vec[j], xs_part,
                                  range_array[k], int_array[k], ene_array[k], xs_array[k]);
        xs_tot += xs_part;
      }

      Real relative_dif = (xs_tot - xs_ori) / xs_ori;
      if( fabs(relative_dif) > 0.01 )
      {
        xs_pos.push_back(j);
        xs_rad.push_back(xs_tot);
        xs_dif.push_back((xs_tot - xs_ori) / xs_ori);

        if( fabs(relative_dif) > 0.1 )
        {
          fatal_flg++;
        }
      }
    }

    int j_max = static_cast<int>(xs_pos.size());
    if( j_max > 0 )
    {
      string class_name = "NuclearDataObjectUtils";
      string func_name  = "check_total_product_xs(NuclearDataObject& nucl_data_obj)";

      vector<string> err_com;
      ostringstream oss_mt;
      oss_mt << reaction_type_no;
      string str_data_mt = "  Reaction type : " + oss_mt.str();

      err_com.push_back("The sum of the XS value from MF=10 is different to the XS value from MF=3.");
      err_com.push_back("");
      err_com.push_back(str_data_mt);
      err_com.push_back("    position : energy [eV] : XS (MF=3) [barn] / XS (sum of MF=10) : relative difference [%]");
      for(int j=0; j<j_max; j++)
      {
        ostringstream oss01, oss02, oss03, oss04, oss05, oss06;
        oss03.setf(ios::showpoint);
        oss03.setf(ios::scientific);
        oss04.setf(ios::showpoint);
        oss04.setf(ios::scientific);
        oss05.setf(ios::showpoint);
        oss05.setf(ios::scientific);
        oss06.setf(ios::showpoint);

        oss01 << xs_pos[j] + 1;
        oss02 << ene_no;
        oss03 << setw(8) << ene_vec[xs_pos[j]];
        oss04 << setw(8) << xs_vec[xs_pos[j]];
        oss05 << setw(8) << xs_rad[j];
        oss06 << setw(4) << xs_dif[j] * 100.0;

        string str_data01 = "    " + oss01.str() + " / " + oss02.str() + " : "
                          + oss03.str() + "[eV]  : "  + oss04.str() + "[barn]  / "
                          + oss05.str() + "[barn] : " + oss06.str() + "[%]";
        err_com.push_back(str_data01);
      }

      //if( fatal_flg == 0 )
      //{
        err_obj.output_caution_format(class_name, func_name, err_com);
      //}
      //else
      //{
      //  err_obj.output_runtime_error(class_name, func_name, err_com);
      //}
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Integer NuclearDataObjectUtils::get_emission_no_n(Integer reaction_type)
{
  Integer lib_format = 6;
  return get_emission_no_n(reaction_type, lib_format);
}

Integer NuclearDataObjectUtils::get_emission_no_n(Integer reaction_type, Integer lib_format)
{
  Integer n2n_min = mt_n2n_min_endf6;
  Integer n2n_max = mt_n2n_max_endf6;

  if( lib_format == 5 )
  {
    n2n_min = mt_n2n_min_endf5; //MT=46-49 are not considered
    n2n_max = mt_n2n_max_endf5;
  }
  else if( lib_format != 6 )
  {
    string class_name = "NuclearDataObjectUtils";
    string func_name  = "get_emission_no_n";

    ostringstream oss01;
    oss01 << lib_format;

    string str_data01 = "library format (lib_format) : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("The available lib_foramt is 5 or 6.");
    err_com.push_back("Please modify lib_format.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  int n_no = 0;
  if( reaction_type ==   2 || reaction_type ==   4 || reaction_type ==  22 ||
      reaction_type ==  23 || reaction_type ==  28 || reaction_type ==  29 ||
      reaction_type ==  44 || reaction_type ==  45 || reaction_type == 158 ||
     (reaction_type >=  32 && reaction_type <=  36) ||
     (reaction_type >=  50 && reaction_type <=  91) ||
     (reaction_type >= 183 && reaction_type <= 189) )
  {
    n_no = 1;
  }
  else if( reaction_type ==  11 || reaction_type ==  16 || reaction_type ==  24 ||
           reaction_type ==  30 || reaction_type ==  41 || reaction_type == 154 ||
           reaction_type == 159 || reaction_type == 176 || reaction_type == 190 ||
          (reaction_type >= n2n_min && reaction_type <= n2n_max) )
  {
    n_no = 2;
  }
  else if( reaction_type ==  17 || reaction_type ==  25 || reaction_type ==  42 ||
           reaction_type == 157 || reaction_type == 172 || reaction_type == 177 ||
           reaction_type == 179 || reaction_type == 180 || reaction_type == 181 ||
           reaction_type == 199 )
  {
    n_no = 3;
  }
  else if( reaction_type ==  37 || reaction_type == 156 || reaction_type == 165 ||
           reaction_type == 169 || reaction_type == 173 || reaction_type == 178 ||
          (reaction_type >= 194 && reaction_type <= 196) )
  {
    n_no = 4;
  }
  else if( reaction_type == 152 || reaction_type == 162 || reaction_type == 166 ||
           reaction_type == 170 || reaction_type == 174 || reaction_type == 200 )
  {
    n_no = 5;
  }
  else if( reaction_type == 153 || reaction_type == 163 || reaction_type == 167 ||
           reaction_type == 171 || reaction_type == 175 )
  {
    n_no = 6;
  }
  else if( reaction_type == 160 || reaction_type == 164 || reaction_type == 168 )
  {
    n_no = 7;
  }
  else if( reaction_type == 161 )
  {
    n_no = 8;
  }

  return n_no;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Integer NuclearDataObjectUtils::get_neutron_absorption(Integer reaction_type)
{
  Integer lib_format = 6;
  return get_neutron_absorption(reaction_type, lib_format);
}

Integer NuclearDataObjectUtils::get_neutron_absorption(Integer reaction_type, Integer lib_format)
{
  Integer n_no = 1 - get_emission_no_n(reaction_type, lib_format);

  if( reaction_type == 1 ||
      reaction_type == 258 || reaction_type == 259  ||
     (reaction_type >= 221 && reaction_type <= 250) || //TSL data
     (reaction_type >= 201 && reaction_type <= 218) )  //(z,Xn), (z,Xp,), ..., (z,Xn-)
  {
    return 0;
  }

  if( reaction_type == 18 || reaction_type == 27 ||
      (reaction_type >= 101 && reaction_type <= 117) )
  {
    n_no = 1;
  }

  if( reaction_type == 5 )
  {
    //n_no = 1;
    n_no = -1000; //return dummy data to avoid bug
  }

  return n_no;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Integer NuclearDataObjectUtils::get_lib_format(vector<Integer>& reaction_type_list)
{
  Integer lib_format = 6;

  vector<Integer>          mt_min, mt_max;
  vector<vector<Integer> > mt_particle_vec;
  int i_max = 6;
  mt_min.resize(i_max);
  mt_max.resize(i_max);
  mt_particle_vec.resize(i_max); //p, d, t, he3, alpha

  mt_min[0] = mt_p_min_endf5;
  mt_max[0] = mt_p_max_endf5;
  mt_min[1] = mt_d_min_endf5;
  mt_max[1] = mt_d_max_endf5;
  mt_min[2] = mt_t_min_endf5;
  mt_max[2] = mt_t_max_endf5;
  mt_min[3] = mt_he3_min_endf5;
  mt_max[3] = mt_he3_max_endf5;
  mt_min[4] = mt_a_min_endf5;
  mt_max[4] = mt_a_max_endf5;
  mt_min[5] = mt_n2n_min_endf5;
  mt_max[5] = mt_n2n_max_endf5;

  int mt_no = static_cast<int>(reaction_type_list.size());
  for(int j=0; j<mt_no; j++)
  {
    for(int i=0; i<i_max; i++)
    {
      if( reaction_type_list[j] >= mt_min[i] && reaction_type_list[j] <= mt_max[i] )
      {
        mt_particle_vec[i].push_back(reaction_type_list[j]);
      }
    }
  }

  Integer lib_flg = 0;
  for(int i=0; i<i_max; i++)
  {
    mt_no = static_cast<int>(mt_particle_vec[i].size());
    if( mt_no == 0 )
    {
      continue;
    }

    Integer lib_mode = 6;
    sort(mt_particle_vec[i].begin(), mt_particle_vec[i].end());

    if( mt_particle_vec[i][0] == mt_min[i] || mt_particle_vec[i][0] == mt_max[i] )
    {
      int order_check = 0;
      for(int j=1; j<mt_no; j++)
      {
        if( mt_particle_vec[i][j] - mt_particle_vec[i][j-1] != 1 )
        {
          if( j == mt_no - 1 && mt_particle_vec[i][j] == mt_max[i] )
          {
            lib_mode = 5;
          }
          else
          {
            order_check = 1;
            break;
          }
        }
      }

      if( order_check == 0 )
      {
        lib_mode = 5;
      }
    }

    if( lib_flg == 0 )
    {
      lib_flg = lib_mode;
    }
    else if( lib_flg == 5 && lib_mode == 5 )
    {
      //lib_flg = 5;
    }
    else
    {
      lib_flg = 6;
    }
  }

  if( lib_flg == 5 )
  {
    lib_format = 5;
  }

  return lib_format;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

vector<Integer> NuclearDataObjectUtils::get_related_reaction_type(Integer reaction_type,
                                                                  vector<Integer>& reaction_list)
{
  Integer lib_format = 6;
  return get_related_reaction_type(reaction_type, reaction_list, lib_format);
}

vector<Integer> NuclearDataObjectUtils::get_related_reaction_type(Integer reaction_type,
                                                                  vector<Integer>& reaction_list,
                                                                  Integer lib_format)
{
  int mt3_flg   = 0; //(z, nonelastic)
  int mt4_flg   = 0; //z, n)
  int mt16_flg  = 0; //z, 2n)
  int mt18_flg  = 0; //(z, fission)
  int mt27_flg  = 0; //(n, abs)
  int mt101_flg = 0; //(n, disap)
  int mt103_flg = 0; //(z, p)
  int mt104_flg = 0; //(z, d)
  int mt105_flg = 0; //(z, t)
  int mt106_flg = 0; //(z, 3He)
  int mt107_flg = 0; //(z, alpha)

  int mt_no = static_cast<int>(reaction_list.size());
  for(int i=0; i<mt_no; i++)
  {
    if( reaction_list[i] == 3 && reaction_type != 3 )
    {
      mt3_flg = 1;
    }
    else if( reaction_list[i] == 4 && reaction_type != 4 )
    {
      mt4_flg = 1;
    }
    else if( reaction_list[i] == 16 && reaction_type != 16 )
    {
      mt16_flg = 1;
    }
    else if( reaction_list[i] == 18 && reaction_type != 18 )
    {
      mt18_flg = 1;
    }
    else if( reaction_list[i] == 27 && reaction_type != 27 )
    {
      mt27_flg = 1;
    }
    else if( reaction_list[i] == 101 && reaction_type != 101 )
    {
      mt101_flg = 1;
    }
    else if( reaction_list[i] == 103 && reaction_type != 103 )
    {
      mt103_flg = 1;
    }
    else if( reaction_list[i] == 104 && reaction_type != 104 )
    {
      mt104_flg = 1;
    }
    else if( reaction_list[i] == 105 && reaction_type != 105 )
    {
      mt105_flg = 1;
    }
    else if( reaction_list[i] == 106 && reaction_type != 106 )
    {
      mt106_flg = 1;
    }
    else if( reaction_list[i] == 107 && reaction_type != 107 )
    {
      mt107_flg = 1;
    }
  }

  Integer mt_p_min   = mt_p_min_endf6;
  Integer mt_p_max   = mt_p_max_endf6;
  Integer mt_d_min   = mt_d_min_endf6;
  Integer mt_d_max   = mt_d_max_endf6;
  Integer mt_t_min   = mt_t_min_endf6;
  Integer mt_t_max   = mt_t_max_endf6;
  Integer mt_he3_min = mt_he3_min_endf6;
  Integer mt_he3_max = mt_he3_max_endf6;
  Integer mt_a_min   = mt_a_min_endf6;
  Integer mt_a_max   = mt_a_max_endf6;
  Integer mt_n2n_min = mt_n2n_min_endf6;
  Integer mt_n2n_max = mt_n2n_max_endf6;

  if( lib_format == 5 )
  {
    mt_p_min   = mt_p_min_endf5;
    mt_p_max   = mt_p_max_endf5;
    mt_d_min   = mt_d_min_endf5;
    mt_d_max   = mt_d_max_endf5;
    mt_t_min   = mt_t_min_endf5;
    mt_t_max   = mt_t_max_endf5;
    mt_he3_min = mt_he3_min_endf5;
    mt_he3_max = mt_he3_max_endf5;
    mt_a_min   = mt_a_min_endf5;
    mt_a_max   = mt_a_max_endf5;
    mt_n2n_min = mt_n2n_min_endf5;
    mt_n2n_max = mt_n2n_max_endf5;
  }
  else if( lib_format != 6 )
  {
    string class_name = "NuclearDataObjectUtils";
    string func_name  = "get_related_reaction_type";

    ostringstream oss01;
    oss01 << lib_format;

    string str_data01 = "library format (lib_format) : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("The available lib_foramt is 5 or 6.");
    err_com.push_back("Please modify lib_format.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  vector<Integer> mt_list;
  mt_list.clear();
  for(int i=0; i<mt_no; i++)
  {
    if( reaction_list[i] == 2 || reaction_list[i] == 3 )
    {
      if( reaction_type == 1 )
      {
        mt_list.push_back(reaction_list[i]);
      }
    }

    if( mt3_flg != 0 && reaction_type == 1 )
    {
      continue;
    }

      if( reaction_list[i] == 4 || reaction_list[i] == 16 )
      {
        if( reaction_type == 1 || reaction_type == 3 )
        {
          mt_list.push_back(reaction_list[i]);
        }
      }
      else if( reaction_list[i] >= 50 && reaction_list[i] <= 91 )
      {
        if( mt4_flg == 0 )
        {
          if( reaction_type == 1 || reaction_type == 3 || reaction_type == 4 )
          {
            mt_list.push_back(reaction_list[i]);
          }
        }
      }
      else if( reaction_list[i] >= mt_n2n_min  && reaction_list[i] <= mt_n2n_max )
      {
        if( mt16_flg == 0 )
        {
          if( reaction_type == 1 || reaction_type == 3 || reaction_type == 16 )
          {
            mt_list.push_back(reaction_list[i]);
          }
        }
      }
      else if( reaction_list[i] ==  5 || reaction_list[i] == 11 || reaction_list[i] == 17 ||
               (reaction_list[i] >=  22 && reaction_list[i] <=  25) ||
               (reaction_list[i] >=  28 && reaction_list[i] <=  37) ||
               (reaction_list[i] >=  41 && reaction_list[i] <=  45) ||
               (reaction_list[i] >= 152 && reaction_list[i] <= 154) ||
               (reaction_list[i] >= 156 && reaction_list[i] <= 181) ||
               (reaction_list[i] >= 183 && reaction_list[i] <= 190) ||
               (reaction_list[i] >= 194 && reaction_list[i] <= 196) ||
               (reaction_list[i] >= 198 && reaction_list[i] <= 200) )
      {
        if( reaction_type == 1 || reaction_type == 3 )
        {
          mt_list.push_back(reaction_list[i]);
        }
      }
      else if( reaction_list[i] == 18 )
      {
        if( reaction_type == 27 )
        {
          mt_list.push_back(reaction_list[i]);
        }
        else if( mt27_flg == 0 )
        {
          if( reaction_type == 1 || reaction_type == 3 )
          {
            mt_list.push_back(reaction_list[i]);
          }
        }
      }
      else if( reaction_list[i] == 27 )
      {
        if( reaction_type == 1 || reaction_type == 3 )
        {
          mt_list.push_back(reaction_list[i]);
        }
      }
      else if( reaction_list[i] == 38 ||  
               (reaction_list[i] >=  19 && reaction_list[i] <=  21) )
      {
        if( mt18_flg == 0 )
        {
          if( reaction_type == 18 || reaction_type == 27 )
          {
            mt_list.push_back(reaction_list[i]);
          }
          else if( mt27_flg == 0 )
          {
            if( reaction_type == 1 || reaction_type == 3 )
            {
              mt_list.push_back(reaction_list[i]);
            }
          }
        }
      }
      else if( reaction_list[i] == 101 )
      {
        if( reaction_type == 27 )
        {
          mt_list.push_back(reaction_list[i]);
        }
        else if( mt27_flg == 0 )
        {
          if( reaction_type == 1 || reaction_type == 3 )
          {
            mt_list.push_back(reaction_list[i]);
          }
        }
      }
      else if( reaction_list[i] == 103 )
      {
        if( reaction_type == 101 )
        {
          mt_list.push_back(reaction_list[i]);
        }
        else if( mt101_flg == 0 )
        {
          if( reaction_type == 27 )
          {
            mt_list.push_back(reaction_list[i]);
          }
          else if( mt27_flg == 0 )
          {
            if( reaction_type == 1 || reaction_type == 3 )
            {
              mt_list.push_back(reaction_list[i]);
            }
          }
        }
      }
      else if( reaction_list[i] == 104 )
      {
        if( reaction_type == 101 )
        {
          mt_list.push_back(reaction_list[i]);
        }
        else if( mt101_flg == 0 )
        {
          if( reaction_type == 27 )
          {
            mt_list.push_back(reaction_list[i]);
          }
          else if( mt27_flg == 0 )
          {
            if( reaction_type == 1 || reaction_type == 3 )
            {
              mt_list.push_back(reaction_list[i]);
            }
          }
        }
      }
      else if( reaction_list[i] == 105 )
      {
        if( reaction_type == 101 )
        {
          mt_list.push_back(reaction_list[i]);
        }
        else if( mt101_flg == 0 )
        {
          if( reaction_type == 27 )
          {
            mt_list.push_back(reaction_list[i]);
          }
          else if( mt27_flg == 0 )
          {
            if( reaction_type == 1 || reaction_type == 3 )
            {
              mt_list.push_back(reaction_list[i]);
            }
          }
        }
      }
      else if( reaction_list[i] == 106 )
      {
        if( reaction_type == 101 )
        {
          mt_list.push_back(reaction_list[i]);
        }
        else if( mt101_flg == 0 )
        {
          if( reaction_type == 27 )
          {
            mt_list.push_back(reaction_list[i]);
          }
          else if( mt27_flg == 0 )
          {
            if( reaction_type == 1 || reaction_type == 3 )
            {
              mt_list.push_back(reaction_list[i]);
            }
          }
        }
      }
      else if( reaction_list[i] == 107 )
      {
        if( reaction_type == 101 )
        {
          mt_list.push_back(reaction_list[i]);
        }
        else if( mt101_flg == 0 )
        {
          if( reaction_type == 27 )
          {
            mt_list.push_back(reaction_list[i]);
          }
          else if( mt27_flg == 0 )
          {
            if( reaction_type == 1 || reaction_type == 3 )
            {
              mt_list.push_back(reaction_list[i]);
            }
          }
        }
      }
      else if( reaction_list[i] >= mt_p_min && reaction_list[i] <= mt_p_max )
      {
        if( mt103_flg == 0 )
        {
          if( reaction_type == 101 || reaction_type == 103 )
          {
            mt_list.push_back(reaction_list[i]);
          }
          else if( mt101_flg == 0 )
          {
            if( reaction_type == 27 )
            {
              mt_list.push_back(reaction_list[i]);
            }
            else if( mt27_flg == 0 )
            {
              if( reaction_type == 1 || reaction_type == 3 )
              {
                mt_list.push_back(reaction_list[i]);
              }
            }
          }
        }
      }
      else if( reaction_list[i] >= mt_d_min && reaction_list[i] <= mt_d_max )
      {
        if( mt104_flg == 0 )
        {
          if( reaction_type == 101 || reaction_type == 104 )
          {
            mt_list.push_back(reaction_list[i]);
          }
          else if( mt101_flg == 0 )
          {
            if( reaction_type == 27 )
            {
              mt_list.push_back(reaction_list[i]);
            }
            else if( mt27_flg == 0 )
            {
              if( reaction_type == 1 || reaction_type == 3 )
              {
                mt_list.push_back(reaction_list[i]);
              }
            }
          }
        }
      }
      else if( reaction_list[i] >= mt_t_min && reaction_list[i] <= mt_t_max )
      {
        if( mt105_flg == 0 )
        {
          if( reaction_type == 101 || reaction_type == 105 )
          {
            mt_list.push_back(reaction_list[i]);
          }
          else if( mt101_flg == 0 )
          {
            if( reaction_type == 27 )
            {
              mt_list.push_back(reaction_list[i]);
            }
            else if( mt27_flg == 0 )
            {
              if( reaction_type == 1 || reaction_type == 3 )
              {
                mt_list.push_back(reaction_list[i]);
              }
            }
          }
        }
      }
      else if( reaction_list[i] >= mt_he3_min && reaction_list[i] <= mt_he3_max )
      {
        if( mt106_flg == 0 )
        {
          if( reaction_type == 101 || reaction_type == 106 )
          {
            mt_list.push_back(reaction_list[i]);
          }
          else if( mt101_flg == 0 )
          {
            if( reaction_type == 27 )
            {
              mt_list.push_back(reaction_list[i]);
            }
            else if( mt27_flg == 0 )
            {
              if( reaction_type == 1 || reaction_type == 3 )
              {
                mt_list.push_back(reaction_list[i]);
              }
            }
          }
        }
      }
      else if( reaction_list[i] >= mt_a_min && reaction_list[i] <= mt_a_max )
      {
        if( mt107_flg == 0 )
        {
          if( reaction_type == 101 || reaction_type == 107 )
          {
            mt_list.push_back(reaction_list[i]);
          }
          else if( mt101_flg == 0 )
          {
            if( reaction_type == 27 )
            {
              mt_list.push_back(reaction_list[i]);
            }
            else if( mt27_flg == 0 )
            {
              if( reaction_type == 1 || reaction_type == 3 )
              {
                mt_list.push_back(reaction_list[i]);
              }
            }
          }
        }
      }
      else if( reaction_list[i] == 102 || reaction_list[i] == 155 ||
               reaction_list[i] == 182 || reaction_list[i] == 197 ||
               (reaction_list[i] >= 108 && reaction_list[i] <= 117) ||
               (reaction_list[i] >= 191 && reaction_list[i] <= 193) )
      {
        if( mt101_flg == 0 )
        {
          if( reaction_type == 27 || reaction_type == 101 )
          {
            mt_list.push_back(reaction_list[i]);
          }
          else if( mt27_flg == 0 )
          {
            if( reaction_type == 1 || reaction_type == 3 )
            {
              mt_list.push_back(reaction_list[i]);
            }
          }
        }
      }
  }

  return mt_list;
}

