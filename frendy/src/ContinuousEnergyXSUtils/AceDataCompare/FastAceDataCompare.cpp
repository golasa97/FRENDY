#include "ContinuousEnergyXSUtils/AceDataCompare/FastAceDataCompare.hpp"

using namespace frendy;

//constructor
FastAceDataCompare::FastAceDataCompare(void)
{ 
  clear();
}

//destructor
FastAceDataCompare::~FastAceDataCompare(void)
{
  clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataCompare::clear()
{
  time_read     = 0.0;
  time_read_ref = 0.0;

  class_name.clear();
  func_name.clear();

  ace_comp_obj.clear();

  ace_data_obj.clear();
  ace_data_obj_ref.clear();

  ace_file_name.clear();
  ace_file_name_ref.clear();

  comp_pointer_flg    = comp_pointer_mode;
  skip_prob_table_flg = skip_prob_table;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataCompare::comp_ace_data()
{
  boost::timer::cpu_timer timer_comp;

  if( comp_pointer_flg == no_comp_pointer_mode )
  {
    ace_comp_obj.set_comp_data_flg(ace_comp_obj.no_comp_data_number_mode);
  }

  class_name = "FastAceDataCompare";

  func_name = "comp_ace_data_header";
  ace_comp_obj.set_information_data(class_name, func_name);
  //cout << func_name << endl;
  comp_ace_data_header();

  if( comp_pointer_flg == comp_pointer_mode )
  {
    func_name = "comp_ace_data_pointer";
    ace_comp_obj.set_information_data(class_name, func_name);
    //cout << func_name << endl;
    comp_ace_data_pointer();
  }

  func_name = "comp_ace_data_base_data";
  ace_comp_obj.set_information_data(class_name, func_name);
  //cout << func_name << endl;
  comp_ace_data_base_data();

  func_name = "comp_ace_data_angular_distribution_data";
  ace_comp_obj.set_information_data(class_name, func_name);
  //cout << func_name << endl;
  comp_ace_data_angular_distribution_data();

  func_name = "comp_ace_data_energy_distribution_data";
  ace_comp_obj.set_information_data(class_name, func_name);
  //cout << func_name << endl;
  comp_ace_data_energy_distribution_data();

  func_name = "comp_ace_data_unreso_prob_table_data";
  ace_comp_obj.set_information_data(class_name, func_name);
  //cout << func_name << endl;
  comp_ace_data_unreso_prob_table_data();

  func_name = "comp_ace_data_nu_d_data";
  ace_comp_obj.set_information_data(class_name, func_name);
  //cout << func_name << endl;
  comp_ace_data_nu_d_data();

  func_name = "comp_ace_data_gamma_production_xs";
  ace_comp_obj.set_information_data(class_name, func_name);
  //cout << func_name << endl;
  comp_ace_data_gamma_production_xs();

  func_name = "comp_ace_data_photon_production_data";
  ace_comp_obj.set_information_data(class_name, func_name);
  //cout << func_name << endl;
  comp_ace_data_photon_production_data();

  func_name = "comp_ace_data_photon_energy_distr_data";
  ace_comp_obj.set_information_data(class_name, func_name);
  //cout << func_name << endl;
  comp_ace_data_photon_energy_distr_data();

  func_name = "comp_ace_data_particle_production_data";
  ace_comp_obj.set_information_data(class_name, func_name);
  //cout << func_name << endl;
  comp_ace_data_particle_production_data();

  Real time_comp = static_cast<Real>(timer_comp.elapsed().wall * 1.0E-9);
  Real time_tot  = time_comp;

  cout << endl;
  if( static_cast<int>(ace_file_name_ref.size()) > 0 )
  {
    time_tot += time_read_ref;
    cout << "  Reading time of reference ACE file : " << time_read_ref << " [s]" << endl;
    cout << "  Read reference ACE file end" << endl;
  }

  if( static_cast<int>(ace_file_name.size()) > 0 )
  {
    time_tot += time_read;
    cout << "  Reading time of compared ACE file  : " << time_read << " [s]" << endl;
    cout << "  Read compared ACE file end" << endl;
  }

  if( static_cast<int>(ace_file_name.size()) > 0 || static_cast<int>(ace_file_name_ref.size()) > 0 )
  {
    cout << "  Comparison time                    : " << time_comp << " [s]" << endl;
    cout << "  Total time                         : " << time_tot  << " [s]" << endl;
  }
  else
  {
    cout << "  Comparison time : " << time_comp << " [s]" << endl;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataCompare::comp_ace_data_header()
{
  ace_comp_obj.comp_title_data(ace_data_obj.get_aw0(),                  ace_data_obj.get_tz(),
                               ace_data_obj.get_discriptive_data(),     ace_data_obj.get_title_data(),
                               ace_data_obj_ref.get_aw0(),              ace_data_obj_ref.get_tz(),
                               ace_data_obj_ref.get_discriptive_data(), ace_data_obj_ref.get_title_data());

  ace_comp_obj.comp_mat_data(ace_data_obj.get_zi_vec(),     ace_data_obj.get_awr_vec(),
                             ace_data_obj_ref.get_zi_vec(), ace_data_obj_ref.get_awr_vec());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataCompare::comp_ace_data_pointer()
{
  ace_comp_obj.set_comp_data_information("len2");
  ace_comp_obj.comp_int_data(ace_data_obj.get_len2(),  ace_data_obj_ref.get_len2());
  ace_comp_obj.set_comp_data_information("izaid");
  ace_comp_obj.comp_int_data(ace_data_obj.get_izaid(), ace_data_obj_ref.get_izaid());
  ace_comp_obj.set_comp_data_information("nes");
  ace_comp_obj.comp_int_data(ace_data_obj.get_nes(),   ace_data_obj_ref.get_nes());
  ace_comp_obj.set_comp_data_information("ntr");
  ace_comp_obj.comp_int_data(ace_data_obj.get_ntr(),   ace_data_obj_ref.get_ntr());
  ace_comp_obj.set_comp_data_information("nr");
  ace_comp_obj.comp_int_data(ace_data_obj.get_nr(),    ace_data_obj_ref.get_nr());
  ace_comp_obj.set_comp_data_information("ntrp");
  ace_comp_obj.comp_int_data(ace_data_obj.get_ntrp(),  ace_data_obj_ref.get_ntrp());
  ace_comp_obj.set_comp_data_information("ntype");
  ace_comp_obj.comp_int_data(ace_data_obj.get_ntype(), ace_data_obj_ref.get_ntype());
  ace_comp_obj.set_comp_data_information("ndnf");
  ace_comp_obj.comp_int_data(ace_data_obj.get_ndnf(),  ace_data_obj_ref.get_ndnf());
  ace_comp_obj.set_comp_data_information("esz");
  ace_comp_obj.comp_int_data(ace_data_obj.get_esz(),   ace_data_obj_ref.get_esz());
  ace_comp_obj.set_comp_data_information("nu");
  ace_comp_obj.comp_int_data(ace_data_obj.get_nu(),    ace_data_obj_ref.get_nu());
  ace_comp_obj.set_comp_data_information("mtr");
  ace_comp_obj.comp_int_data(ace_data_obj.get_mtr(),   ace_data_obj_ref.get_mtr());
  ace_comp_obj.set_comp_data_information("lqr");
  ace_comp_obj.comp_int_data(ace_data_obj.get_lqr(),   ace_data_obj_ref.get_lqr());
  ace_comp_obj.set_comp_data_information("tyr");
  ace_comp_obj.comp_int_data(ace_data_obj.get_tyr(),   ace_data_obj_ref.get_tyr());
  ace_comp_obj.set_comp_data_information("lsig");
  ace_comp_obj.comp_int_data(ace_data_obj.get_lsig(),  ace_data_obj_ref.get_lsig());
  ace_comp_obj.set_comp_data_information("sig");
  ace_comp_obj.comp_int_data(ace_data_obj.get_sig(),   ace_data_obj_ref.get_sig());
  ace_comp_obj.set_comp_data_information("land");
  ace_comp_obj.comp_int_data(ace_data_obj.get_land(),  ace_data_obj_ref.get_land());
  ace_comp_obj.set_comp_data_information("and");
  ace_comp_obj.comp_int_data(ace_data_obj.get_andi(),  ace_data_obj_ref.get_andi());
  ace_comp_obj.set_comp_data_information("ldlw");
  ace_comp_obj.comp_int_data(ace_data_obj.get_ldlw(),  ace_data_obj_ref.get_ldlw());
  ace_comp_obj.set_comp_data_information("dlw");
  ace_comp_obj.comp_int_data(ace_data_obj.get_dlw(),   ace_data_obj_ref.get_dlw());
  ace_comp_obj.set_comp_data_information("gpd");
  ace_comp_obj.comp_int_data(ace_data_obj.get_gpd(),   ace_data_obj_ref.get_gpd());
  ace_comp_obj.set_comp_data_information("mtrp");
  ace_comp_obj.comp_int_data(ace_data_obj.get_mtrp(),  ace_data_obj_ref.get_mtrp());
  ace_comp_obj.set_comp_data_information("lsigp");
  ace_comp_obj.comp_int_data(ace_data_obj.get_lsigp(), ace_data_obj_ref.get_lsigp());
  ace_comp_obj.set_comp_data_information("sigp");
  ace_comp_obj.comp_int_data(ace_data_obj.get_sigp(),  ace_data_obj_ref.get_sigp());
  ace_comp_obj.set_comp_data_information("landp");
  ace_comp_obj.comp_int_data(ace_data_obj.get_landp(), ace_data_obj_ref.get_landp());
  ace_comp_obj.set_comp_data_information("andp");
  ace_comp_obj.comp_int_data(ace_data_obj.get_andp(),  ace_data_obj_ref.get_andp());
  ace_comp_obj.set_comp_data_information("ldlwp");
  ace_comp_obj.comp_int_data(ace_data_obj.get_ldlwp(), ace_data_obj_ref.get_ldlwp());
  ace_comp_obj.set_comp_data_information("dlwp");
  ace_comp_obj.comp_int_data(ace_data_obj.get_dlwp(),  ace_data_obj_ref.get_dlwp());
  ace_comp_obj.set_comp_data_information("yp");
  ace_comp_obj.comp_int_data(ace_data_obj.get_yp(),    ace_data_obj_ref.get_yp());
  ace_comp_obj.set_comp_data_information("fis");
  ace_comp_obj.comp_int_data(ace_data_obj.get_fis(),   ace_data_obj_ref.get_fis());
  ace_comp_obj.set_comp_data_information("end");
  ace_comp_obj.comp_int_data(ace_data_obj.get_endi(),  ace_data_obj_ref.get_endi());
  ace_comp_obj.set_comp_data_information("iurpt");
  ace_comp_obj.comp_int_data(ace_data_obj.get_iurpt(), ace_data_obj_ref.get_iurpt());
  ace_comp_obj.set_comp_data_information("nud");
  ace_comp_obj.comp_int_data(ace_data_obj.get_nud(),   ace_data_obj_ref.get_nud());
  ace_comp_obj.set_comp_data_information("dndat");
  ace_comp_obj.comp_int_data(ace_data_obj.get_dndat(), ace_data_obj_ref.get_dndat());
  ace_comp_obj.set_comp_data_information("ldnd");
  ace_comp_obj.comp_int_data(ace_data_obj.get_ldnd(),  ace_data_obj_ref.get_ldnd());
  ace_comp_obj.set_comp_data_information("dnd");
  ace_comp_obj.comp_int_data(ace_data_obj.get_dnd(),   ace_data_obj_ref.get_dnd());
  ace_comp_obj.set_comp_data_information("ptype");
  ace_comp_obj.comp_int_data(ace_data_obj.get_ptype(), ace_data_obj_ref.get_ptype());
  ace_comp_obj.set_comp_data_information("ntro");
  ace_comp_obj.comp_int_data(ace_data_obj.get_ntro(),  ace_data_obj_ref.get_ntro());
  ace_comp_obj.set_comp_data_information("ploct");
  ace_comp_obj.comp_int_data(ace_data_obj.get_ploct(), ace_data_obj_ref.get_ploct());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataCompare::comp_ace_data_base_data()
{
  vector<Real> ene_vec, ene_vec_ref;
  int ene_no = static_cast<int>(ace_data_obj.get_union_ene_grid().size());
  if( ene_no > 0 )
  {
    Real ene_pre = ace_data_obj.get_union_ene_grid()[0];
    for(int i=1; i<ene_no; i++)
    {
      Real ene_cur = ace_data_obj.get_union_ene_grid()[i];
      if( fabs((ene_cur - ene_pre) / ene_cur) > 1.0E-6 )
      {
        ene_vec.push_back(ene_pre);
        ene_pre = ene_cur;
      }
    }
    ene_vec.push_back(ene_pre);
  }

  int ene_no_ref = static_cast<int>(ace_data_obj_ref.get_union_ene_grid().size());
  if( ene_no_ref > 0 )
  {
    Real ene_pre = ace_data_obj_ref.get_union_ene_grid()[0];
    for(int i=1; i<ene_no_ref; i++)
    {
      Real ene_cur = ace_data_obj_ref.get_union_ene_grid()[i];
      if( fabs((ene_cur - ene_pre) / ene_cur) > 1.0E-6 )
      {
        ene_vec_ref.push_back(ene_pre);
        ene_pre = ene_cur;
      }
    }
    ene_vec_ref.push_back(ene_pre);
  }
  
  ace_comp_obj.set_comp_data_information("union_ene_grid");
  ace_comp_obj.comp_list_data(ene_vec, ene_vec_ref);

  ace_comp_obj.set_comp_data_information("react_xs_tot");
  ace_comp_obj.comp_table_data(ace_data_obj.get_union_ene_grid(),     ace_data_obj.get_react_xs_tot(),
                               ace_data_obj_ref.get_union_ene_grid(), ace_data_obj_ref.get_react_xs_tot());
  ace_comp_obj.set_comp_data_information("react_xs_cap");
  ace_comp_obj.comp_table_data(ace_data_obj.get_union_ene_grid(),     ace_data_obj.get_react_xs_cap(),
                               ace_data_obj_ref.get_union_ene_grid(), ace_data_obj_ref.get_react_xs_cap());
  ace_comp_obj.set_comp_data_information("react_xs_sc");
  ace_comp_obj.comp_table_data(ace_data_obj.get_union_ene_grid(),     ace_data_obj.get_react_xs_sc(),
                               ace_data_obj_ref.get_union_ene_grid(), ace_data_obj_ref.get_react_xs_sc());
  ace_comp_obj.set_comp_data_information("react_xs_heat");
  ace_comp_obj.comp_table_data(ace_data_obj.get_union_ene_grid(),     ace_data_obj.get_react_xs_heat(),
                               ace_data_obj_ref.get_union_ene_grid(), ace_data_obj_ref.get_react_xs_heat());
  
  ace_comp_obj.set_comp_data_information("size of nu_p_data");
  ace_comp_obj.comp_int_data(static_cast<int>(ace_data_obj.get_nu_p_data().size()),
                             static_cast<int>(ace_data_obj_ref.get_nu_p_data().size()));
  if( static_cast<int>(ace_data_obj_ref.get_nu_p_data().size()) > 0 )
  {
    ace_comp_obj.set_comp_data_information("nu_p_bar_repr_flg");
    ace_comp_obj.comp_int_data(ace_data_obj.get_nu_p_bar_repr_flg(),
                               ace_data_obj_ref.get_nu_p_bar_repr_flg());
    if( ace_data_obj_ref.get_nu_p_bar_repr_flg() == 1 )
    {
      ace_comp_obj.set_comp_data_information("nu_p_data");
      ace_comp_obj.comp_list_data(ace_data_obj.get_nu_p_data(), ace_data_obj_ref.get_nu_p_data());
    }
    else
    {
      ace_comp_obj.set_comp_data_information("nu_p_range_data, nu_p_int_data, nu_p_ene_data, nu_p_data");
      ace_comp_obj.comp_table_data
        (ace_data_obj.get_nu_p_range_data(),     ace_data_obj.get_nu_p_int_data(),
         ace_data_obj.get_nu_p_ene_data(),       ace_data_obj.get_nu_p_data(),
         ace_data_obj_ref.get_nu_p_range_data(), ace_data_obj_ref.get_nu_p_int_data(),
         ace_data_obj_ref.get_nu_p_ene_data(),   ace_data_obj_ref.get_nu_p_data());
    }
  }

  ace_comp_obj.set_comp_data_information("size of nu_data");
  ace_comp_obj.comp_int_data(static_cast<int>(ace_data_obj.get_nu_data().size()),
                             static_cast<int>(ace_data_obj_ref.get_nu_data().size()));
  if( static_cast<int>(ace_data_obj_ref.get_nu_data().size()) > 0 )
  {
    ace_comp_obj.set_comp_data_information("nu_bar_repr_flg");
    ace_comp_obj.comp_int_data(ace_data_obj.get_nu_bar_repr_flg(), ace_data_obj_ref.get_nu_bar_repr_flg());
    if( ace_data_obj_ref.get_nu_bar_repr_flg() == 1 )
    {
      ace_comp_obj.set_comp_data_information("nu_data");
      ace_comp_obj.comp_list_data(ace_data_obj.get_nu_data(), ace_data_obj_ref.get_nu_data());
    }
    else
    {
      ace_comp_obj.set_comp_data_information("nu_range_data, nu_int_data, nu_ene_data, nu_data");
      ace_comp_obj.comp_table_data
        (ace_data_obj.get_nu_range_data(),     ace_data_obj.get_nu_int_data(),
         ace_data_obj.get_nu_ene_data(),       ace_data_obj.get_nu_data(),
         ace_data_obj_ref.get_nu_range_data(), ace_data_obj_ref.get_nu_int_data(),
         ace_data_obj_ref.get_nu_ene_data(),   ace_data_obj_ref.get_nu_data());
    }
  }

  ace_comp_obj.set_comp_data_information("size of react_type_list");
  ace_comp_obj.comp_int_data(static_cast<int>(ace_data_obj.get_react_type_list().size()),
                             static_cast<int>(ace_data_obj_ref.get_react_type_list().size()));
  if( static_cast<int>(ace_data_obj_ref.get_react_type_list().size()) > 0 )
  {
    ace_comp_obj.set_comp_data_information("react_type_list");
    ace_comp_obj.comp_list_data(ace_data_obj.get_react_type_list(), ace_data_obj_ref.get_react_type_list());
    ace_comp_obj.set_comp_data_information("react_type_q_value");
    ace_comp_obj.comp_list_data(ace_data_obj.get_react_q_value(),   ace_data_obj_ref.get_react_q_value());
    ace_comp_obj.set_comp_data_information("react_type_flg");
    ace_comp_obj.comp_list_data(ace_data_obj.get_react_type_flg(),  ace_data_obj_ref.get_react_type_flg());

    int i_max = static_cast<int>(ace_data_obj_ref.get_react_xs().size());
    int j_max = static_cast<int>(ace_data_obj.get_react_xs().size());
    ace_comp_obj.set_comp_data_information("size of react_xs");
    ace_comp_obj.comp_int_data(static_cast<int>(ace_data_obj.get_react_xs().size()), i_max);

    vector<Real> ene_grid     = ace_data_obj.get_union_ene_grid();
    vector<Real> ene_grid_ref = ace_data_obj_ref.get_union_ene_grid();
    for(int i=0; i<i_max; i++)
    {
      Integer react_val_ref = ace_data_obj_ref.get_react_type_list()[i];

      int react_pos = -1;
      for(int j=0; j<j_max; j++)
      {
        if( react_val_ref == ace_data_obj.get_react_type_list()[j] )
        {
          react_pos = j;
        }
      }

      if( react_pos < 0 )
      {
        cout << "This reaction type does not found in the comparison ACE file : " << react_val_ref << endl;
      }
      else
      {
        vector<Real> react_xs, react_xs_ref, react_xs_tmp;
        react_xs_tmp =  ace_data_obj.get_react_xs()[react_pos];
            ene_no   = static_cast<int>(ene_grid.size());
        int xs_no    = static_cast<int>(react_xs_tmp.size());
        int ele_no   = 0;
        react_xs.resize(ene_no);
        for(int j=0; j<ene_no; j++)
        {
          if( ene_no - xs_no > j )
          {
            react_xs[j] = 0.0;
          }
          else
          {
            react_xs[j] = react_xs_tmp[ele_no];
            ele_no++;
          }
        }

        react_xs_tmp =  ace_data_obj_ref.get_react_xs()[i];
        ene_no       = static_cast<int>(ene_grid_ref.size());
        xs_no        = static_cast<int>(react_xs_tmp.size());
        ele_no       = 0;
        react_xs_tmp =  ace_data_obj_ref.get_react_xs()[i];
        react_xs_ref.resize(ene_no);
        for(int j=0; j<ene_no; j++)
        {
          if( ene_no - xs_no > j )
          {
            react_xs_ref[j] = 0.0;
          }
          else
          {
            react_xs_ref[j] = react_xs_tmp[ele_no];
            ele_no++;
          }
        }

        string pos_data;
        ostringstream oss01, oss02;
        oss01 << i+1;
        oss02 << react_val_ref;

        pos_data = "(pos : " + oss01.str() + ", MT : " + oss02.str() + ")";

        ace_comp_obj.set_comp_data_position(pos_data);
        ace_comp_obj.set_comp_data_information("react_xs");
        ace_comp_obj.comp_table_data(ene_grid, react_xs, ene_grid_ref, react_xs_ref);
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataCompare::comp_ace_data_angular_distribution_data()
{
  int i_max = static_cast<int>(ace_data_obj_ref.get_angular_distr_type_flg().size());
  ace_comp_obj.set_comp_data_information("angular_distr_type_flg");
  if( comp_pointer_flg == comp_pointer_mode )
  {
    ace_comp_obj.comp_list_data(ace_data_obj.get_angular_distr_type_flg(),
                                ace_data_obj_ref.get_angular_distr_type_flg());
  }
  else
  {
    ace_comp_obj.comp_int_data(static_cast<int>(ace_data_obj.get_angular_distr_type_flg().size()), i_max);
    for(int i=0; i<i_max; i++)
    {
      if( ace_data_obj_ref.get_angular_distr_type_flg()[i] <= 0 )
      {
        ace_comp_obj.set_comp_data_position(i+1);
        ace_comp_obj.comp_int_data(ace_data_obj.get_angular_distr_type_flg()[i],
                                   ace_data_obj_ref.get_angular_distr_type_flg()[i]);
      }
    }
  }

  if( i_max == 0 )
  {
    return;
  }

  int ele_no = 0;
  for(int i=0; i<i_max; i++)
  {
    ace_comp_obj.set_comp_data_position(i+1);
    if( ace_data_obj_ref.get_angular_distr_type_flg()[i] <= 0 )
    {
      continue;
    }
    while( ace_data_obj.get_angular_distr_type_flg()[ele_no] <= 0 )
    {
      ele_no++;
    }

    ace_comp_obj.set_comp_data_information("angular_distr_ene_data");
    ace_comp_obj.comp_list_data(ace_data_obj.get_angular_distr_ene_data()[ele_no],
                                ace_data_obj_ref.get_angular_distr_ene_data()[i]);

    if( comp_pointer_flg == comp_pointer_mode )
    {
      ace_comp_obj.set_comp_data_information("angular_distr_pointer");
      ace_comp_obj.comp_list_data_pointer(ace_data_obj.get_angular_distr_pointer()[ele_no],
                                          ace_data_obj_ref.get_angular_distr_pointer()[i]);
    }

    int j_max = static_cast<int>(ace_data_obj_ref.get_angular_distr_ene_data()[i].size());
    for(int j=0; j<j_max; j++)
    {
      ace_comp_obj.set_comp_data_position(i+1, j+1);
      ace_comp_obj.set_comp_data_information
      ("angular_distr_int_data, angular_distr_cos_data, angular_distr_data, angular_distr_data_integ");
      ace_comp_obj.set_min_val(2.0E-10);
      ace_comp_obj.comp_table_data(ace_data_obj.get_angular_distr_int_data()[ele_no][j],
                                   ace_data_obj.get_angular_distr_cos_data()[ele_no][j],
                                   ace_data_obj.get_angular_distr_data()[ele_no][j],
                                   ace_data_obj.get_angular_distr_data_integ()[ele_no][j],
                                   ace_data_obj_ref.get_angular_distr_int_data()[i][j],
                                   ace_data_obj_ref.get_angular_distr_cos_data()[i][j],
                                   ace_data_obj_ref.get_angular_distr_data()[i][j],
                                   ace_data_obj_ref.get_angular_distr_data_integ()[i][j]);
      ace_comp_obj.set_min_val_def();
    }
    ele_no++;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataCompare::comp_ace_data_energy_distribution_data()
{
  if( comp_pointer_flg == comp_pointer_mode )
  {
    ace_comp_obj.set_comp_data_information("ene_distr_pointer");
    ace_comp_obj.comp_list_data_pointer(ace_data_obj.get_ene_distr_pointer(),
                                        ace_data_obj_ref.get_ene_distr_pointer());
  }

  string func_name  = "comp_ace_data_energy_distribution_data";
  vector<int> prod_distr_prob_coef_a_pos_i, prod_distr_prob_coef_a_pos_j, prod_distr_prob_coef_a_pos_k,
              ene_distr_ene_out_data_pos_i, ene_distr_ene_out_data_pos_j, ene_distr_ene_out_data_pos_k,
              ene_distr_ene_out_data_no, ene_distr_ene_out_data_no_ref;

  int i_max  = static_cast<int>(ace_data_obj_ref.get_ene_distr_ene_repr_flg().size());
  if( i_max == 0 )
  {
    return;
  }

  for(int i=0; i<i_max; i++)
  {
    ace_comp_obj.set_comp_data_position(i+1);

    ace_comp_obj.set_comp_data_information("size of prod_yield_tot_ene_data");
    ace_comp_obj.comp_int_data(static_cast<int>(ace_data_obj.get_prod_yield_tot_ene_data()[i].size()),
                               static_cast<int>(ace_data_obj_ref.get_prod_yield_tot_ene_data()[i].size()));
    if( static_cast<int>(ace_data_obj_ref.get_prod_yield_tot_ene_data()[i].size()) > 0 )
    {
      ace_comp_obj.set_comp_data_information
      ("prod_yield_tot_range_data, prod_yield_tot_int_data, prod_yield_tot_ene_data, prod_yield_tot_data");
      ace_comp_obj.comp_table_data( ace_data_obj.get_prod_yield_tot_range_data()[i],
                                    ace_data_obj.get_prod_yield_tot_int_data()[i],
                                    ace_data_obj.get_prod_yield_tot_ene_data()[i],
                                    ace_data_obj.get_prod_yield_tot_data()[i],
                                    ace_data_obj_ref.get_prod_yield_tot_range_data()[i],
                                    ace_data_obj_ref.get_prod_yield_tot_int_data()[i],
                                    ace_data_obj_ref.get_prod_yield_tot_ene_data()[i],
                                    ace_data_obj_ref.get_prod_yield_tot_data()[i] );
    }

    int j_max = static_cast<int>(ace_data_obj_ref.get_ene_distr_ene_repr_flg()[i].size());
    ace_comp_obj.set_comp_data_information("size of ene_distr_ene_repr_flg");
    ace_comp_obj.comp_int_data(static_cast<int>(ace_data_obj.get_ene_distr_ene_repr_flg()[i].size()), j_max);
    for(int j=0; j<j_max; j++)
    {
      ace_comp_obj.set_comp_data_position(i+1, j+1);

      if( comp_pointer_flg == comp_pointer_mode )
      {
        ace_comp_obj.set_comp_data_information("ene_distr_ene_repr_end_pointer");
        ace_comp_obj.comp_int_data(ace_data_obj.get_ene_distr_ene_repr_end_pointer()[i][j],
                                   ace_data_obj_ref.get_ene_distr_ene_repr_end_pointer()[i][j]);

        ace_comp_obj.set_comp_data_information("ene_distr_ene_repr_pointer");
        ace_comp_obj.comp_int_data(ace_data_obj.get_ene_distr_ene_repr_pointer()[i][j],
                                   ace_data_obj_ref.get_ene_distr_ene_repr_pointer()[i][j]);
      }

      ace_comp_obj.set_comp_data_information("ene_distr_ene_repr_flg");
      ace_comp_obj.comp_int_data( ace_data_obj.get_ene_distr_ene_repr_flg()[i][j],
                                  ace_data_obj_ref.get_ene_distr_ene_repr_flg()[i][j] );
      ace_comp_obj.set_comp_data_information
      ("ene_distr_xs_part_range_data, ene_distr_xs_part_int_data, ene_distr_xs_part_ene_data, ene_distr_xs_part_data");
      vector<Real> x_vec     = ace_data_obj.get_ene_distr_xs_part_ene_data()[i][j];
      vector<Real> y_vec     = ace_data_obj.get_ene_distr_xs_part_data()[i][j];
      vector<Real> x_vec_ref = ace_data_obj_ref.get_ene_distr_xs_part_ene_data()[i][j];
      vector<Real> y_vec_ref = ace_data_obj_ref.get_ene_distr_xs_part_data()[i][j];
      ace_comp_obj.modify_initial_rise_region(x_vec,     y_vec);
      ace_comp_obj.modify_initial_rise_region(x_vec_ref, y_vec_ref);
      ace_comp_obj.modify_small_value(y_vec,     min_ene_dif);
      ace_comp_obj.modify_small_value(y_vec_ref, min_ene_dif);
      ace_comp_obj.comp_table_data( ace_data_obj.get_ene_distr_xs_part_range_data()[i][j],
                                    ace_data_obj.get_ene_distr_xs_part_int_data()[i][j],
                                    x_vec, y_vec,
                                    ace_data_obj_ref.get_ene_distr_xs_part_range_data()[i][j],
                                    ace_data_obj_ref.get_ene_distr_xs_part_int_data()[i][j],
                                    x_vec_ref, y_vec_ref);

      if( ace_data_obj_ref.get_ene_distr_ene_repr_flg()[i][j] == 1 )
      {
        //This flag is not available in this program
      }
      else if( ace_data_obj_ref.get_ene_distr_ene_repr_flg()[i][j] == 3 )
      {
        ace_comp_obj.set_comp_data_information("ene_distr_q_coef");
        ace_comp_obj.comp_real_data(ace_data_obj.get_ene_distr_q_coef()[i][j],
                                    ace_data_obj_ref.get_ene_distr_q_coef()[i][j]);
        ace_comp_obj.set_comp_data_information("ene_distr_mass_coef");
        ace_comp_obj.comp_real_data(ace_data_obj.get_ene_distr_mass_coef()[i][j],
                                    ace_data_obj_ref.get_ene_distr_mass_coef()[i][j]);
      }
      else if( ace_data_obj_ref.get_ene_distr_ene_repr_flg()[i][j] == 4 )
      {
        ace_comp_obj.set_comp_data_information
        ("ene_distr_ene_in_range_data, ene_distr_ene_in_int_data");
        ace_comp_obj.comp_interpolation_data(ace_data_obj.get_ene_distr_ene_in_range_data()[i][j],
                                             ace_data_obj.get_ene_distr_ene_in_int_data()[i][j],
                                             ace_data_obj_ref.get_ene_distr_ene_in_range_data()[i][j],
                                             ace_data_obj_ref.get_ene_distr_ene_in_int_data()[i][j]);
        ace_comp_obj.set_comp_data_information("ene_distr_ene_in_data");
        ace_comp_obj.comp_list_data(ace_data_obj.get_ene_distr_ene_in_data()[i][j],
                                    ace_data_obj_ref.get_ene_distr_ene_in_data()[i][j]);

        if( comp_pointer_flg == comp_pointer_mode )
        {
          ace_comp_obj.set_comp_data_information("ene_distr_ene_in_pointer");
          ace_comp_obj.comp_list_data_pointer(ace_data_obj.get_ene_distr_ene_in_pointer()[i][j],
                                              ace_data_obj_ref.get_ene_distr_ene_in_pointer()[i][j]);
        }

        int k_max = static_cast<int>(ace_data_obj_ref.get_ene_distr_ene_in_data()[i][j].size());
        for(int k=0; k<k_max; k++)
        {
          vector<Real> ene_vec, data_vec, data_integ_vec, ene_vec_ref, data_vec_ref, data_integ_vec_ref,
                       ene_vec_tmp, data_vec_tmp, data_integ_vec_tmp;

          ene_vec_tmp        = ace_data_obj.get_ene_distr_ene_out_ene_data()[i][j][k];
          data_vec_tmp       = ace_data_obj.get_ene_distr_ene_out_data()[i][j][k];
          data_integ_vec_tmp = ace_data_obj.get_ene_distr_ene_out_data_integ()[i][j][k];

          int l_max = static_cast<int>(ene_vec_tmp.size());
          for(int l=0; l<l_max; l++)
          {
            if( ene_vec_tmp[l] < 10.1999 )
            {
              ene_vec.push_back(ene_vec_tmp[l]);
              data_vec.push_back(data_vec_tmp[l]);
              data_integ_vec.push_back(data_integ_vec_tmp[l]); 
            }
          }
          integ_obj.integrate_for_ace_data( class_name, func_name,
                                            ene_vec, data_vec, data_integ_vec, int_lin_lin);

          ene_vec_tmp        = ace_data_obj_ref.get_ene_distr_ene_out_ene_data()[i][j][k];
          data_vec_tmp       = ace_data_obj_ref.get_ene_distr_ene_out_data()[i][j][k];
          data_integ_vec_tmp = ace_data_obj_ref.get_ene_distr_ene_out_data_integ()[i][j][k];

          l_max = static_cast<int>(ene_vec_tmp.size());
          for(int l=0; l<l_max; l++)
          {
            if( ene_vec_tmp[l] < 10.1999 )
            {
              ene_vec_ref.push_back(ene_vec_tmp[l]);
              data_vec_ref.push_back(data_vec_tmp[l]);
              data_integ_vec_ref.push_back(data_integ_vec_tmp[l]); 
            }
          }
          if( static_cast<int>(ene_vec_ref.size()) == 0 )
          {
            continue;
          }

          integ_obj.integrate_for_ace_data( class_name, func_name,
                                            ene_vec_ref, data_vec_ref, data_integ_vec_ref, int_lin_lin);

          //Check ene_distr_ene_out_data
          if( static_cast<int>(data_vec.size())     > static_cast<int>(data_vec_ref.size()) * 10 ||
              static_cast<int>(data_vec_ref.size()) > static_cast<int>(data_vec.size())     * 10 )
          {
              ene_distr_ene_out_data_pos_i.push_back(i+1);
              ene_distr_ene_out_data_pos_j.push_back(j+1);
              ene_distr_ene_out_data_pos_k.push_back(k+1);
              ene_distr_ene_out_data_no.push_back
                (static_cast<int>(ace_data_obj.get_ene_distr_ene_out_ene_data()[i][j][k].size()));
              ene_distr_ene_out_data_no_ref.push_back
                (static_cast<int>(ace_data_obj_ref.get_ene_distr_ene_out_ene_data()[i][j][k].size()));

            int mod_flg = 0;
            if( static_cast<int>(data_vec_ref.size()) > static_cast<int>(data_vec.size()) * 10 )
            {
              mod_flg = 1;
            }

            vector<Real> ene_mod, data_mod, data_integ_mod, ene_new, data_new, data_integ_new;
            if( mod_flg == 0 )
            {
              ene_new        = ene_vec_ref;
              ene_mod        = ene_vec;
              data_mod       = data_vec;
              data_integ_mod = data_integ_vec;
            }
            else
            {
              ene_new        = ene_vec;
              ene_mod        = ene_vec_ref;
              data_mod       = data_vec_ref;
              data_integ_mod = data_integ_vec_ref;
            }

            TabInterpolator ti_obj;
            l_max = static_cast<int>(ene_new.size());
            data_new.resize(l_max);
            for(int l=0; l<l_max; l++)
            {
              ti_obj.interpolation_1d(int_lin_lin, ene_new[l], data_new[l], ene_mod, data_mod);
            }
            integ_obj.integrate_for_ace_data( class_name, func_name,
                                              ene_new, data_new, data_integ_new, int_lin_lin);

            if( mod_flg == 0 )
            {
              ene_vec        = ene_new;
              data_vec       = data_new;
              data_integ_vec = data_integ_new;
            }
            else
            {
              ene_vec_ref        = ene_new;
              data_vec_ref       = data_new;
              data_integ_vec_ref = data_integ_new;
            }
          }

          ace_comp_obj.set_comp_data_position(i+1, j+1, k+1);
          ace_comp_obj.set_comp_data_information
            ("ene_distr_ene_out_int_data, ene_distr_ene_out_ene_data, ene_distr_ene_out_data, ene_distr_ene_out_data_integ");

          int l_max_ref = static_cast<int>(ene_vec_ref.size());
          if( l_max_ref == 0 )
          {
            l_max = static_cast<int>(ene_vec.size());
            if( l_max != 0 )
            {
              for(int l=0; l<l_max; l++)
              {
                if( fabs(data_vec[l]) > min_value )
                {
                  ace_comp_obj.comp_int_data(l_max, l_max_ref);
                  break;
                }
              }
            
            }
          }
          else
          {
            ace_comp_obj.comp_table_data(ace_data_obj.get_ene_distr_ene_out_int_data()[i][j][k],
                                         ene_vec, data_vec, data_integ_vec,
                                         ace_data_obj_ref.get_ene_distr_ene_out_int_data()[i][j][k],
                                         ene_vec_ref, data_vec_ref, data_integ_vec_ref);
          }
        }
      }
      else if( ace_data_obj_ref.get_ene_distr_ene_repr_flg()[i][j] == 5 )
      {
        //This flag is not available in this program
      }
      else if( ace_data_obj_ref.get_ene_distr_ene_repr_flg()[i][j] == 7 ||
               ace_data_obj_ref.get_ene_distr_ene_repr_flg()[i][j] == 9 )
      {
        ace_comp_obj.set_comp_data_information
        ("ene_distr_temp_eff_range_data, ene_distr_temp_eff_int_data, ene_distr_temp_eff_ene_data, ene_distr_temp_eff_data");
        ace_comp_obj.comp_table_data(ace_data_obj.get_ene_distr_temp_eff_range_data()[i][j],
                                     ace_data_obj.get_ene_distr_temp_eff_int_data()[i][j],
                                     ace_data_obj.get_ene_distr_temp_eff_ene_data()[i][j],
                                     ace_data_obj.get_ene_distr_temp_eff_data()[i][j],
                                     ace_data_obj_ref.get_ene_distr_temp_eff_range_data()[i][j],
                                     ace_data_obj_ref.get_ene_distr_temp_eff_int_data()[i][j],
                                     ace_data_obj_ref.get_ene_distr_temp_eff_ene_data()[i][j],
                                     ace_data_obj_ref.get_ene_distr_temp_eff_data()[i][j]);
        ace_comp_obj.set_comp_data_information("ene_distr_upper_ene_limit");
        ace_comp_obj.comp_real_data(ace_data_obj.get_ene_distr_upper_ene_limit()[i][j],
                                    ace_data_obj_ref.get_ene_distr_upper_ene_limit()[i][j]);
      }
      else if( ace_data_obj_ref.get_ene_distr_ene_repr_flg()[i][j] == 11 )
      {
        ace_comp_obj.set_comp_data_information
        ("ene_distr_watt_a_range_data, ene_distr_watt_a_int_data, ene_distr_watt_a_ene_data, ene_distr_watt_a_data");
        vector<Real> watt_a_comp_mod = ace_data_obj.get_ene_distr_watt_a_data()[i][j];
        vector<Real> watt_a_ref_mod  = ace_data_obj_ref.get_ene_distr_watt_a_data()[i][j];

        ace_comp_obj.comp_table_data(ace_data_obj.get_ene_distr_watt_a_range_data()[i][j],
                                     ace_data_obj.get_ene_distr_watt_a_int_data()[i][j],
                                     ace_data_obj.get_ene_distr_watt_a_ene_data()[i][j],
                                     watt_a_comp_mod,
                                     ace_data_obj_ref.get_ene_distr_watt_a_range_data()[i][j],
                                     ace_data_obj_ref.get_ene_distr_watt_a_int_data()[i][j],
                                     ace_data_obj_ref.get_ene_distr_watt_a_ene_data()[i][j],
                                     watt_a_ref_mod);
        ace_comp_obj.set_comp_data_information
        ("ene_distr_watt_b_range_data, ene_distr_watt_b_int_data, ene_distr_watt_b_ene_data, ene_distr_watt_b_data");
        ace_comp_obj.comp_table_data(ace_data_obj.get_ene_distr_watt_b_range_data()[i][j],
                                     ace_data_obj.get_ene_distr_watt_b_int_data()[i][j],
                                     ace_data_obj.get_ene_distr_watt_b_ene_data()[i][j],
                                     ace_data_obj.get_ene_distr_watt_b_data()[i][j],
                                     ace_data_obj_ref.get_ene_distr_watt_b_range_data()[i][j],
                                     ace_data_obj_ref.get_ene_distr_watt_b_int_data()[i][j],
                                     ace_data_obj_ref.get_ene_distr_watt_b_ene_data()[i][j],
                                     ace_data_obj_ref.get_ene_distr_watt_b_data()[i][j]);
      }
      else if( ace_data_obj_ref.get_ene_distr_ene_repr_flg()[i][j] == 44 ||
               ace_data_obj_ref.get_ene_distr_ene_repr_flg()[i][j] == 61 )
      {
        ace_comp_obj.set_comp_data_information
        ("prod_distr_prob_ene_in_range_data, prod_distr_prob_ene_in_int_data");
        ace_comp_obj.comp_interpolation_data(ace_data_obj.get_prod_distr_prob_ene_in_range_data()[i][j],
                                             ace_data_obj.get_prod_distr_prob_ene_in_int_data()[i][j],
                                             ace_data_obj_ref.get_prod_distr_prob_ene_in_range_data()[i][j],
                                             ace_data_obj_ref.get_prod_distr_prob_ene_in_int_data()[i][j]);
        ace_comp_obj.set_comp_data_information("prod_distr_prob_ene_in_data");
        ace_comp_obj.comp_list_data(ace_data_obj.get_prod_distr_prob_ene_in_data()[i][j],
                                    ace_data_obj_ref.get_prod_distr_prob_ene_in_data()[i][j]);

        if( comp_pointer_flg == comp_pointer_mode )
        {
          ace_comp_obj.set_comp_data_information("ene_distr_ene_in_pointer");
          ace_comp_obj.comp_list_data_pointer(ace_data_obj.get_ene_distr_ene_in_pointer()[i][j],
                                              ace_data_obj_ref.get_ene_distr_ene_in_pointer()[i][j]);
        }

        int k_max = static_cast<int>(ace_data_obj_ref.get_prod_distr_prob_ene_in_data()[i][j].size());
        ace_comp_obj.set_comp_data_information("k_max of prod_distr_prob_ene_in_data");
        ace_comp_obj.comp_int_data(ace_data_obj.get_prod_distr_prob_ene_in_data()[i][j].size(),
                                   k_max);
        if( k_max != static_cast<int>(ace_data_obj.get_prod_distr_prob_ene_in_data()[i][j].size()) )
        {
          continue;
        }
        for(int k=0; k<k_max; k++)
        {
          ace_comp_obj.set_comp_data_position(i+1, j+1, k+1);
          ace_comp_obj.set_comp_data_information
          ("prod_distr_prob_ene_out_int_data, prod_distr_prob_ene_out_data, prod_distr_prob_mu_data, prod_distr_prob_mu_data_integ");
          if( ace_comp_obj.check_list_data_order
                (ace_data_obj.get_prod_distr_prob_ene_out_data()[i][j][k]) < 0 ||
              ace_comp_obj.check_list_data_order
                (ace_data_obj_ref.get_prod_distr_prob_ene_out_data()[i][j][k]) < 0 )
          {
            ace_comp_obj.comp_int_data(ace_data_obj.get_prod_distr_prob_ene_out_int_data()[i][j][k],
                                       ace_data_obj_ref.get_prod_distr_prob_ene_out_int_data()[i][j][k]);
            ace_comp_obj.comp_list_data(ace_data_obj.get_prod_distr_prob_ene_out_data()[i][j][k],
                                        ace_data_obj_ref.get_prod_distr_prob_ene_out_data()[i][j][k]);
            ace_comp_obj.comp_list_data(ace_data_obj.get_prod_distr_prob_mu_data()[i][j][k],
                                        ace_data_obj_ref.get_prod_distr_prob_mu_data()[i][j][k]);
            ace_comp_obj.comp_list_data(ace_data_obj.get_prod_distr_prob_mu_data_integ()[i][j][k],
                                        ace_data_obj_ref.get_prod_distr_prob_mu_data_integ()[i][j][k]);
          }
          else
          {
            ace_comp_obj.comp_table_data(ace_data_obj.get_prod_distr_prob_ene_out_int_data()[i][j][k],
                                         ace_data_obj.get_prod_distr_prob_ene_out_data()[i][j][k],
                                         ace_data_obj.get_prod_distr_prob_mu_data()[i][j][k],
                                         ace_data_obj.get_prod_distr_prob_mu_data_integ()[i][j][k],
                                         ace_data_obj_ref.get_prod_distr_prob_ene_out_int_data()[i][j][k],
                                         ace_data_obj_ref.get_prod_distr_prob_ene_out_data()[i][j][k],
                                         ace_data_obj_ref.get_prod_distr_prob_mu_data()[i][j][k],
                                         ace_data_obj_ref.get_prod_distr_prob_mu_data_integ()[i][j][k]);
          }

          if( ace_data_obj_ref.get_ene_distr_ene_repr_flg()[i][j] == 44 )
          {
            vector<Real> ene_out_vec, ene_out_vec_ref, ene_out_vec_new;
            ene_out_vec     = ace_data_obj.get_prod_distr_prob_ene_out_data()[i][j][k];
            ene_out_vec_ref = ace_data_obj_ref.get_prod_distr_prob_ene_out_data()[i][j][k];

            int l_max = static_cast<int>(ene_out_vec_ref.size());
            int m_max = static_cast<int>(ene_out_vec.size());
            vector<Real> coef_a_vec, coef_a_vec_ref, coef_b_vec, coef_b_vec_ref;
            vector<Real> coef_a_vec_tmp, coef_a_vec_ref_tmp, coef_b_vec_tmp, coef_b_vec_ref_tmp;

            coef_a_vec_tmp     = ace_data_obj.get_prod_distr_prob_coef_a()[i][j][k];
            coef_b_vec_tmp     = ace_data_obj.get_prod_distr_prob_coef_b()[i][j][k];
            coef_a_vec_ref_tmp = ace_data_obj_ref.get_prod_distr_prob_coef_a()[i][j][k];
            coef_b_vec_ref_tmp = ace_data_obj_ref.get_prod_distr_prob_coef_b()[i][j][k];

            for(int l=0; l<l_max; l++)
            {
              Real ene_out_ref = ene_out_vec_ref[l];
              Real ene_out_dif = fabs(ene_out_ref) * 0.01 * ace_comp_obj.get_tolerance_val();
              if( ene_out_dif < min_value )
              {
                ene_out_dif = min_value;
              }

              for(int m=0; m<m_max; m++)
              {
                if( fabs(ene_out_vec[m] - ene_out_ref) < ene_out_dif )
                {
                  ene_out_vec_new.push_back(ene_out_ref);
                  coef_a_vec.push_back(coef_a_vec_tmp[m]);
                  coef_a_vec_ref.push_back(coef_a_vec_ref_tmp[l]);
                  coef_b_vec.push_back(coef_b_vec_tmp[m]);
                  coef_b_vec_ref.push_back(coef_b_vec_ref_tmp[l]);
                  break;
                }
              }
            }

            //Check prod_distr_prob_coef_a
            int change_pos     = -1;
            int change_pos_ref = -1;
            for(int l=1; l<static_cast<int>(coef_a_vec.size()); l++)
            {
              if( fabs(coef_a_vec[l] - coef_a_vec[l-1]) > fabs(min_ene_dif * coef_a_vec[l]) )
              {
                change_pos = l;
                break;
              }
            }
            for(int l=1; l<static_cast<int>(coef_a_vec_ref.size()); l++)
            {
              if( fabs(coef_a_vec_ref[l] - coef_a_vec_ref[l-1]) > fabs(min_ene_dif * coef_a_vec_ref[l]) )
              {
                change_pos_ref = l;
                break;
              }
            }
            if( change_pos > 0 && change_pos_ref > 0 )
            {
              if( fabs(ene_out_vec_new[change_pos] - ene_out_vec_new[change_pos_ref])
                    > fabs(min_ene_dif * ene_out_vec_new[change_pos_ref]) )
              {
                prod_distr_prob_coef_a_pos_i.push_back(i+1);
                prod_distr_prob_coef_a_pos_j.push_back(j+1);
                prod_distr_prob_coef_a_pos_k.push_back(k+1);

                Real ene_out_min = ene_out_vec_new[change_pos];
                if( ene_out_min < ene_out_vec_new[change_pos_ref] )
                {
                  ene_out_min = ene_out_vec_new[change_pos_ref];
                }
                ene_out_min *= 0.99999;

                vector<Real> coef_a_vec_new, coef_a_vec_ref_new;
                coef_a_vec_new.push_back(coef_a_vec[0]);
                coef_a_vec_ref_new.push_back(coef_a_vec_ref[0]);
                for(int l=1; l<static_cast<int>(coef_a_vec.size()); l++)
                {
                  if( ene_out_vec_new[l] > ene_out_min )
                  {
                    coef_a_vec_new.push_back(coef_a_vec[l]);
                  }
                }
                for(int l=1; l<static_cast<int>(coef_a_vec_ref.size()); l++)
                {
                  if( ene_out_vec_new[l] > ene_out_min )
                  {
                    coef_a_vec_ref_new.push_back(coef_a_vec_ref[l]);
                  }
                }
                coef_a_vec     = coef_a_vec_new;
                coef_a_vec_ref = coef_a_vec_ref_new;
              }
            }

            ace_comp_obj.set_comp_data_information("prod_distr_prob_coef_a");
            ace_comp_obj.comp_list_data(coef_a_vec, coef_a_vec_ref);
            ace_comp_obj.set_comp_data_information("prod_distr_prob_coef_b");
            ace_comp_obj.comp_list_data(coef_b_vec, coef_b_vec_ref);
          }
          else if( ace_data_obj_ref.get_ene_distr_ene_repr_flg()[i][j] == 61 )
          {
            if( comp_pointer_flg == comp_pointer_mode )
            {
              ace_comp_obj.set_comp_data_information("ene_distr_ene_out_pointer");
              ace_comp_obj.comp_list_data_pointer(ace_data_obj.get_ene_distr_ene_out_pointer()[i][j][k],
                                                  ace_data_obj_ref.get_ene_distr_ene_out_pointer()[i][j][k]);
            }

            int l_max = static_cast<int>(ace_data_obj_ref.get_prod_distr_prob_ene_out_data()[i][j][k].size());
            ace_comp_obj.set_comp_data_information("l_max of prod_distr_prob_ene_out_data");
            ace_comp_obj.comp_int_data(ace_data_obj.get_prod_distr_prob_ene_out_data()[i][j][k].size(),
                                       l_max);
            if( l_max != static_cast<int>(ace_data_obj.get_prod_distr_prob_ene_out_data()[i][j][k].size()) )
            {
              continue;
            }
            for(int l=0; l<l_max; l++)
            {
              Integer      prob_int     = ace_data_obj.get_prod_distr_prob_int_vec()[i][j][k][l][0];
              Integer      prob_int_ref = ace_data_obj_ref.get_prod_distr_prob_int_vec()[i][j][k][l][0];
              vector<Real> prob_mu_vec,     prob_vec,     prob_vec_integ,
                           prob_mu_vec_ref, prob_vec_ref, prob_vec_integ_ref,
                           prob_mu_vec_tmp, prob_vec_tmp;

              prob_mu_vec_tmp    = ace_data_obj.get_prod_distr_prob_mu_vec()[i][j][k][l];
              prob_vec_tmp       = ace_data_obj.get_prod_distr_prob_vec()[i][j][k][l];

              int m_max = static_cast<int>(prob_mu_vec_tmp.size());
              prob_mu_vec.push_back(prob_mu_vec_tmp[0]);
              prob_vec.push_back(prob_vec_tmp[0]);
              if( fabs(prob_vec[0]) < 1.0E-8 )
              {
                prob_vec[0] = 0.0;
              }
              for(int m=1; m<m_max; m++)
              {
                prob_mu_vec.push_back(prob_mu_vec_tmp[m]);
                if( fabs(prob_vec_tmp[m]) > min_ene_dif*10.0 )
                {
                  prob_vec.push_back(prob_vec_tmp[m]);
                }
                else
                {
                  prob_vec.push_back(1.0E-8);
                }
              }
              m_max = static_cast<int>(prob_mu_vec.size());
              prob_vec_integ.resize(m_max);
              prob_vec_integ[0] = 0.0;
              for(int m=1; m<m_max; m++)
              {
                prob_vec_integ[m] = prob_vec_integ[m-1]
                                  + integ_obj.integrate_data
                                      ( prob_mu_vec[m-1], prob_vec[m-1],
                                        prob_mu_vec[m],   prob_vec[m], prob_int );
              }

              prob_mu_vec_tmp    = ace_data_obj_ref.get_prod_distr_prob_mu_vec()[i][j][k][l];
              prob_vec_tmp       = ace_data_obj_ref.get_prod_distr_prob_vec()[i][j][k][l];

              m_max = static_cast<int>(prob_mu_vec_tmp.size());
              prob_mu_vec_ref.push_back(prob_mu_vec_tmp[0]);
              prob_vec_ref.push_back(prob_vec_tmp[0]);
              if( fabs(prob_vec_ref[0]) < 1.0E-8 )
              {
                prob_vec_ref[0] = 0.0;
              }
              for(int m=1; m<m_max; m++)
              {
                prob_mu_vec_ref.push_back(prob_mu_vec_tmp[m]);
                if( fabs(prob_vec_tmp[m]) > min_ene_dif*10.0 )
                {
                  prob_vec_ref.push_back(prob_vec_tmp[m]);
                }
                else
                {
                  prob_vec_ref.push_back(1.0E-8);
                }
              }
              m_max = static_cast<int>(prob_mu_vec_ref.size());
              prob_vec_integ_ref.resize(m_max);
              prob_vec_integ_ref[0] = 0.0;
              for(int m=1; m<m_max; m++)
              {
                prob_vec_integ_ref[m] = prob_vec_integ_ref[m-1]
                                      + integ_obj.integrate_data
                                         ( prob_mu_vec_ref[m-1], prob_vec_ref[m-1],
                                           prob_mu_vec_ref[m],   prob_vec_ref[m], prob_int_ref );
              }

              ace_comp_obj.set_comp_data_position(i+1, j+1, k+1, l+1);
              ace_comp_obj.set_comp_data_information
              ("prod_distr_prob_int_vec, prod_distr_prob_mu_vec, prod_distr_prob_vec, prod_distr_prob_vec_integ");
              //ace_comp_obj.comp_table_data(prob_int,     prob_mu_vec,     prob_vec,
              //                             prob_int_ref, prob_mu_vec_ref, prob_vec_ref);
              ace_comp_obj.comp_table_data(prob_int,     prob_mu_vec,     prob_vec,     prob_vec_integ,
                                           prob_int_ref, prob_mu_vec_ref, prob_vec_ref, prob_vec_integ_ref);
            }
          }
        }
      }
      else if( ace_data_obj_ref.get_ene_distr_ene_repr_flg()[i][j] == 66 )
      {
        ace_comp_obj.set_comp_data_information("prod_distr_n_body_particle_no");
        ace_comp_obj.comp_int_data(ace_data_obj.get_prod_distr_n_body_particle_no()[i][j],
                                   ace_data_obj_ref.get_prod_distr_n_body_particle_no()[i][j]);
        ace_comp_obj.set_comp_data_information("prod_distr_n_body_mass");
        ace_comp_obj.comp_real_data(ace_data_obj.get_prod_distr_n_body_mass()[i][j],
                                    ace_data_obj_ref.get_prod_distr_n_body_mass()[i][j]);
        ace_comp_obj.set_comp_data_information("prod_distr_prob_data_no");
        ace_comp_obj.comp_int_data(ace_data_obj.get_prod_distr_prob_data_no()[i][j],
                                   ace_data_obj_ref.get_prod_distr_prob_data_no()[i][j]);
        ace_comp_obj.set_comp_data_information
        ("prod_distr_prob_mu_data, prod_distr_prob_data, prod_distr_prob_data_integ");
        ace_comp_obj.comp_table_data(ace_data_obj.get_prod_distr_prob_mu_data()[i][j][0],
                                     ace_data_obj.get_prod_distr_prob_data()[i][j][0],
                                     ace_data_obj.get_prod_distr_prob_data_integ()[i][j][0],
                                     ace_data_obj_ref.get_prod_distr_prob_mu_data()[i][j][0],
                                     ace_data_obj_ref.get_prod_distr_prob_data()[i][j][0],
                                     ace_data_obj_ref.get_prod_distr_prob_data_integ()[i][j][0]);
      }
      else if( ace_data_obj_ref.get_ene_distr_ene_repr_flg()[i][j] == 67 )
      {
        ace_comp_obj.set_comp_data_information
        ("prod_distr_prob_ene_in_range_data, prod_distr_prob_ene_in_int_data");
        ace_comp_obj.comp_interpolation_data(ace_data_obj.get_prod_distr_prob_ene_in_range_data()[i][j],
                                             ace_data_obj.get_prod_distr_prob_ene_in_int_data()[i][j],
                                             ace_data_obj_ref.get_prod_distr_prob_ene_in_range_data()[i][j],
                                             ace_data_obj_ref.get_prod_distr_prob_ene_in_int_data()[i][j]);
        ace_comp_obj.set_comp_data_information("prod_distr_prob_ene_in_data");
        ace_comp_obj.comp_list_data(ace_data_obj.get_prod_distr_prob_ene_in_data()[i][j],
                                    ace_data_obj_ref.get_prod_distr_prob_ene_in_data()[i][j]);

        if( comp_pointer_flg == comp_pointer_mode )
        {
          ace_comp_obj.set_comp_data_information("ene_distr_ene_in_pointer");
          ace_comp_obj.comp_list_data_pointer(ace_data_obj.get_ene_distr_ene_in_pointer()[i][j],
                                              ace_data_obj_ref.get_ene_distr_ene_in_pointer()[i][j]);
        }

        int k_max = static_cast<int>(ace_data_obj_ref.get_prod_distr_prob_ene_in_data()[i][j].size());
        for(int k=0; k<k_max; k++)
        {
          ace_comp_obj.set_comp_data_position(i+1, j+1, k+1);
          ace_comp_obj.set_comp_data_information("prod_distr_prob_mu_int_data");
          ace_comp_obj.comp_int_data(ace_data_obj.get_prod_distr_prob_mu_int_data()[i][j][k][0],
                                     ace_data_obj_ref.get_prod_distr_prob_mu_int_data()[i][j][k][0]);
          ace_comp_obj.set_comp_data_information("prod_distr_prob_mu_data");
          ace_comp_obj.comp_list_data(ace_data_obj.get_prod_distr_prob_mu_data()[i][j][k],
                                      ace_data_obj_ref.get_prod_distr_prob_mu_data()[i][j][k]);

          if( comp_pointer_flg == comp_pointer_mode )
          {
            ace_comp_obj.set_comp_data_information("ene_distr_ene_out_pointer");
            ace_comp_obj.comp_list_data_pointer(ace_data_obj.get_ene_distr_ene_out_pointer()[i][j][k],
                                                ace_data_obj_ref.get_ene_distr_ene_out_pointer()[i][j][k]);
          }

          int l_max = static_cast<int>(ace_data_obj_ref.get_prod_distr_prob_mu_data()[i][j][k].size());
          for(int l=0; l<l_max; l++)
          {
            ace_comp_obj.set_comp_data_position(i+1, j+1, k+1, l+1);
            ace_comp_obj.set_comp_data_information
            ("prod_distr_prob_int_vec, prod_distr_prob_ene_out_vec, prod_distr_prob_vec, prod_distr_prob_vec_integ");
            ace_comp_obj.comp_table_data(ace_data_obj.get_prod_distr_prob_int_vec()[i][j][k][l][0],
                                         ace_data_obj.get_prod_distr_prob_ene_out_vec()[i][j][k][l],
                                         ace_data_obj.get_prod_distr_prob_vec()[i][j][k][l],
                                         ace_data_obj.get_prod_distr_prob_vec_integ()[i][j][k][l],
                                         ace_data_obj_ref.get_prod_distr_prob_int_vec()[i][j][k][l][0],
                                         ace_data_obj_ref.get_prod_distr_prob_ene_out_vec()[i][j][k][l],
                                         ace_data_obj_ref.get_prod_distr_prob_vec()[i][j][k][l],
                                         ace_data_obj_ref.get_prod_distr_prob_vec_integ()[i][j][k][l]);
          }
        }
      }
    }
  }

  if( static_cast<int>(ene_distr_ene_out_data_pos_i.size()) > 0 )
  {
    ostringstream oss01;
    oss01 << static_cast<int>(ene_distr_ene_out_data_pos_i.size());

    vector<string> err_com;
    string str_data01 = "Data name information : ene_distr_ene_out_data";
    string str_data02 = "  Number of data : " + oss01.str();

    err_com.push_back(str_data01);
    err_com.push_back("  The number of reference data is largely different to that of comparing data.");
    err_com.push_back("  The reference or comparing data may be inappropriate.");
    err_com.push_back("  Comparison of these inappropriate data is skipped.");
    err_com.push_back("");
    err_com.push_back("Position and array number of inappropriate data");
    err_com.push_back(str_data02);
    for(int i=0; i< static_cast<int>(ene_distr_ene_out_data_pos_i.size()); i++)
    {
      ostringstream oss_i, oss_j, oss_k, oss_no, oss_no_ref;
      oss_i      << ene_distr_ene_out_data_pos_i[i];
      oss_j      << ene_distr_ene_out_data_pos_j[i];
      oss_k      << ene_distr_ene_out_data_pos_k[i];
      oss_no     << ene_distr_ene_out_data_no[i];
      oss_no_ref << ene_distr_ene_out_data_no_ref[i];
      string str_data_pos = "    (" + oss_i.str() + ", " + oss_j.str() + ", " + oss_k.str() + ")"
                          + "  comp :" + oss_no.str() + " / ref : " + oss_no_ref.str();
      err_com.push_back(str_data_pos);
    }
    err_obj.output_caution(class_name, func_name, err_com);
  }

  if( static_cast<int>(prod_distr_prob_coef_a_pos_i.size()) > 0 )
  {
    ostringstream oss01;
    oss01 << static_cast<int>(prod_distr_prob_coef_a_pos_i.size());

    vector<string> err_com;
    string str_data01 = "Data name information : prod_distr_prob_coef_a";
    string str_data02 = "  Number of data : " + oss01.str(); 

    err_com.push_back(str_data01);
    err_com.push_back("  The reference data and comparing data is different.");
    err_com.push_back("  The reference or comparing data may be inappropriate.");
    err_com.push_back("  Comparison of these inappropriate data is skipped.");
    err_com.push_back("");
    err_com.push_back("Position of inappropriate data");
    err_com.push_back(str_data02);
    for(int i=0; i< static_cast<int>(prod_distr_prob_coef_a_pos_i.size()); i++)
    {
      ostringstream oss_i, oss_j, oss_k;
      oss_i << prod_distr_prob_coef_a_pos_i[i];
      oss_j << prod_distr_prob_coef_a_pos_j[i];
      oss_k << prod_distr_prob_coef_a_pos_k[i];
      string str_data_pos = "    (" + oss_i.str() + ", " + oss_j.str() + ", " + oss_k.str() + ")";
      err_com.push_back(str_data_pos);
    }
    err_obj.output_caution(class_name, func_name, err_com);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataCompare::comp_ace_data_unreso_prob_table_data()
{
  int table_no_chk = static_cast<int>(ace_data_obj.get_unreso_prob_tab_table().size());
  int table_no     = static_cast<int>(ace_data_obj_ref.get_unreso_prob_tab_table().size());
  ace_comp_obj.set_comp_data_information("table_no");
  ace_comp_obj.comp_int_data(table_no_chk, table_no);
  if( table_no == 0 )
  {
    return;
  }

  int bin_no_chk = static_cast<int>(ace_data_obj.get_unreso_prob_tab_sample_no()[0].size());
  int bin_no     = static_cast<int>(ace_data_obj_ref.get_unreso_prob_tab_sample_no()[0].size());
  ace_comp_obj.set_comp_data_information("bin_no");
  ace_comp_obj.comp_int_data(bin_no_chk, bin_no);

  ace_comp_obj.set_comp_data_information("unreso_prob_tab_int_data");
  ace_comp_obj.comp_int_data(ace_data_obj.get_unreso_prob_tab_int_data(),
                             ace_data_obj_ref.get_unreso_prob_tab_int_data());
  ace_comp_obj.set_comp_data_information("unreso_prob_tab_inela_comp_flg");
  ace_comp_obj.comp_int_data(ace_data_obj.get_unreso_prob_tab_inela_comp_flg(),
                             ace_data_obj_ref.get_unreso_prob_tab_inela_comp_flg());
  ace_comp_obj.set_comp_data_information("unreso_prob_tab_abs_comp_flg");
  ace_comp_obj.comp_int_data(ace_data_obj.get_unreso_prob_tab_abs_comp_flg(),
                             ace_data_obj_ref.get_unreso_prob_tab_abs_comp_flg());

  ace_comp_obj.set_comp_data_information("unreso_prob_tab_self_shielding_flg");
  ace_comp_obj.comp_int_data(ace_data_obj.get_unreso_prob_tab_self_shielding_flg(),
                             ace_data_obj_ref.get_unreso_prob_tab_self_shielding_flg());

  ace_comp_obj.set_comp_data_information("unreso_prob_tab_ene");
  ace_comp_obj.comp_list_data(ace_data_obj.get_unreso_prob_tab_ene(),
                              ace_data_obj_ref.get_unreso_prob_tab_ene());

  if( skip_prob_table_flg == skip_prob_table )
  {
    return;
  }

  for(int i=0; i<table_no; i++)
  {
    ace_comp_obj.set_comp_data_position(i+1);
    ace_comp_obj.set_comp_data_information("unreso_prob_tab_sample_no");
    ace_comp_obj.comp_list_data(ace_data_obj.get_unreso_prob_tab_sample_no()[i],
                                ace_data_obj_ref.get_unreso_prob_tab_sample_no()[i]);

    ace_comp_obj.set_comp_data_information("size of unreso_prob_tab_table");
    ace_comp_obj.comp_int_data(static_cast<int>(ace_data_obj.get_unreso_prob_tab_table()[i].size()),
                               static_cast<int>(ace_data_obj_ref.get_unreso_prob_tab_table()[i].size()));
    for(int j=0; j<static_cast<int>(ace_data_obj_ref.get_unreso_prob_tab_table()[i].size()); j++)
    {
      ace_comp_obj.set_comp_data_position(i+1, j+1);
      ace_comp_obj.set_comp_data_information("unreso_prob_tab_table");
      ace_comp_obj.comp_list_data(ace_data_obj.get_unreso_prob_tab_table()[i][j],
                                  ace_data_obj_ref.get_unreso_prob_tab_table()[i][j]);
    }

    ace_comp_obj.set_comp_data_position(i+1);
    ace_comp_obj.set_comp_data_information("unreso_prob_tab_heat");
    ace_comp_obj.comp_list_data(ace_data_obj.get_unreso_prob_tab_heat()[i],
                                ace_data_obj_ref.get_unreso_prob_tab_heat()[i]);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataCompare::comp_ace_data_nu_d_data()
{
  int i_max = static_cast<int>(ace_data_obj_ref.get_nu_d_decay_constant().size());
  ace_comp_obj.set_comp_data_information("size of nu_d_decay_constant");
  ace_comp_obj.comp_int_data(static_cast<int>(ace_data_obj.get_nu_d_decay_constant().size()), i_max);
  if( i_max == 0 )
  {
    return;
  }

  ace_comp_obj.set_comp_data_information("nu_d_bar_repr_flg");
  ace_comp_obj.comp_int_data(ace_data_obj.get_nu_d_bar_repr_flg(),
                             ace_data_obj_ref.get_nu_d_bar_repr_flg());
  ace_comp_obj.set_comp_data_information
  ("nu_d_range_data, nu_d_int_data, nu_d_ene_data, nu_d_data");
  ace_comp_obj.comp_table_data(ace_data_obj.get_nu_d_range_data(),     ace_data_obj.get_nu_d_int_data(),
                               ace_data_obj.get_nu_d_ene_data(),       ace_data_obj.get_nu_d_data(),
                               ace_data_obj_ref.get_nu_d_range_data(), ace_data_obj_ref.get_nu_d_int_data(),
                               ace_data_obj_ref.get_nu_d_ene_data(),   ace_data_obj_ref.get_nu_d_data());

  for(int i=0; i<i_max; i++)
  {
    ace_comp_obj.set_comp_data_position(i+1);
    ace_comp_obj.set_comp_data_information("nu_d_decay_constant");
    ace_comp_obj.comp_real_data(ace_data_obj.get_nu_d_decay_constant()[i],
                                ace_data_obj_ref.get_nu_d_decay_constant()[i]);
    ace_comp_obj.set_comp_data_information
    ("nu_d_xs_part_range_data, nu_d_xs_part_int_data, nu_d_xs_part_ene_data, nu_d_xs_part_data");
    ace_comp_obj.comp_table_data
      ( ace_data_obj.get_nu_d_xs_part_range_data()[i],     ace_data_obj.get_nu_d_xs_part_int_data()[i],
        ace_data_obj.get_nu_d_xs_part_ene_data()[i],       ace_data_obj.get_nu_d_xs_part_data()[i],
        ace_data_obj_ref.get_nu_d_xs_part_range_data()[i], ace_data_obj_ref.get_nu_d_xs_part_int_data()[i],
        ace_data_obj_ref.get_nu_d_xs_part_ene_data()[i],   ace_data_obj_ref.get_nu_d_xs_part_data()[i] );
  }

  ace_comp_obj.clear_comp_data_position();
  if( comp_pointer_flg == comp_pointer_mode )
  {
    ace_comp_obj.set_comp_data_information("nu_d_pointer");
    ace_comp_obj.comp_list_data_pointer(ace_data_obj.get_nu_d_pointer(), ace_data_obj_ref.get_nu_d_pointer());
  }

  for(int i=0; i<i_max; i++)
  {
    ace_comp_obj.set_comp_data_position(i+1);
    ace_comp_obj.set_comp_data_information("nu_d_ene_min");
    ace_comp_obj.comp_real_data(ace_data_obj.get_nu_d_ene_min()[i], ace_data_obj_ref.get_nu_d_ene_min()[i]);
    ace_comp_obj.set_comp_data_information("nu_d_ene_max");
    ace_comp_obj.comp_real_data(ace_data_obj.get_nu_d_ene_max()[i], ace_data_obj_ref.get_nu_d_ene_max()[i]);

    ace_comp_obj.set_comp_data_information
    ("nu_d_ene_in_range_data, nu_d_ene_in_int_data, nu_d_ene_in_range_data, nu_d_ene_in_int_data");
    ace_comp_obj.comp_interpolation_data(ace_data_obj.get_nu_d_ene_in_range_data()[i],
                                         ace_data_obj.get_nu_d_ene_in_int_data()[i],
                                         ace_data_obj_ref.get_nu_d_ene_in_range_data()[i],
                                         ace_data_obj_ref.get_nu_d_ene_in_int_data()[i]);
    ace_comp_obj.set_comp_data_information("nu_d_ene_in_data");
    ace_comp_obj.comp_list_data(ace_data_obj.get_nu_d_ene_in_data()[i],
                                ace_data_obj_ref.get_nu_d_ene_in_data()[i]);

    if( comp_pointer_flg == comp_pointer_mode )
    {
      ace_comp_obj.set_comp_data_information("nu_d_ene_in_pointer");
      ace_comp_obj.comp_list_data_pointer(ace_data_obj.get_nu_d_ene_in_pointer()[i],
                                          ace_data_obj_ref.get_nu_d_ene_in_pointer()[i]);
    }

    int j_max = static_cast<int>(ace_data_obj_ref.get_nu_d_ene_in_data()[i].size());
    for(int j=0; j<j_max; j++)
    {
      vector<Real> nu_d_ene, nu_d, nu_d_integ, nu_d_ene_ref, nu_d_ref, nu_d_integ_ref;
      nu_d_ene   = ace_data_obj.get_nu_d_ene_out_data()[i][j];
      nu_d       = ace_data_obj.get_nu_d_ene_distr_data()[i][j];
      nu_d_integ = ace_data_obj.get_nu_d_ene_distr_data_integ()[i][j];

      nu_d_ene_ref   = ace_data_obj_ref.get_nu_d_ene_out_data()[i][j];
      nu_d_ref       = ace_data_obj_ref.get_nu_d_ene_distr_data()[i][j];
      nu_d_integ_ref = ace_data_obj_ref.get_nu_d_ene_distr_data_integ()[i][j];
      if( static_cast<int>(nu_d_ene.size()) > 1 )
      {
        vector<Real> nu_d_ene_new, nu_d_new, nu_d_integ_new;
        Real nu_d_next = nu_d_ene[1] * 0.99999;
        for(int k=0; k<static_cast<int>(nu_d_ene_ref.size()); k++)
        {
          if( k==0 || nu_d_ene_ref[k] >= nu_d_next ) 
          {
            nu_d_ene_new.push_back(nu_d_ene_ref[k]);
            nu_d_new.push_back(nu_d_ref[k]);
            nu_d_integ_new.push_back(nu_d_integ_ref[k]);
          }
        }

        nu_d_ene_ref   = nu_d_ene_new;
        nu_d_ref       = nu_d_new;
        nu_d_integ_ref = nu_d_integ_new;

        integ_obj.integrate_for_ace_data(class_name, func_name, nu_d_ene_ref, nu_d_ref, nu_d_integ_ref, 
                                         ace_data_obj_ref.get_nu_d_ene_out_int_data()[i][j]);
      }

      ace_comp_obj.set_comp_data_position(i+1, j+1);
      ace_comp_obj.set_comp_data_information
      ("nu_d_ene_out_int_data, nu_d_ene_out_data, nu_d_ene_distr_data, nu_d_ene_distr_data_integ");
      ace_comp_obj.comp_table_data_without_small_value
        ( ace_data_obj.get_nu_d_ene_out_int_data()[i][j],     nu_d_ene,     nu_d,     nu_d_integ,
          ace_data_obj_ref.get_nu_d_ene_out_int_data()[i][j], nu_d_ene_ref, nu_d_ref, nu_d_integ_ref);
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataCompare::comp_ace_data_gamma_production_xs()
{
  if( static_cast<int>(ace_data_obj_ref.get_gamma_product_xs().size()) == 0 )
  {
    return;
  }

  ace_comp_obj.set_comp_data_information("gamma_product_xs");
  ace_comp_obj.comp_table_data
    (ace_data_obj.get_union_ene_grid(),     ace_data_obj.get_gamma_product_xs(),
     ace_data_obj_ref.get_union_ene_grid(), ace_data_obj_ref.get_gamma_product_xs());

  //For gendf data file
  //Modify multigroup photon data in GENDF file.
  //The GENDF file is not available in FRENDY.
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataCompare::comp_ace_data_photon_production_data()
{
  int i_max = static_cast<int>(ace_data_obj_ref.get_photon_prod_file_no().size());
  ace_comp_obj.set_comp_data_information("size of photon_prod_file_no");
  ace_comp_obj.comp_int_data(static_cast<int>(ace_data_obj.get_photon_prod_file_no().size()), i_max);
  if( i_max == 0 )
  {
    return;
  }

  ace_comp_obj.set_comp_data_information("photon_prod_reaction_type_all");
  ace_comp_obj.comp_list_data(ace_data_obj.get_photon_prod_reaction_type_all(),
                              ace_data_obj_ref.get_photon_prod_reaction_type_all());

  if( comp_pointer_flg == comp_pointer_mode )
  {
    ace_comp_obj.set_comp_data_information("photon_prod_pointer");
    ace_comp_obj.comp_list_data_pointer(ace_data_obj.get_photon_prod_pointer(),
                                        ace_data_obj_ref.get_photon_prod_pointer());
  }

  int modify_photon_prod_multiplicity_data_flg = 0;
  vector<vector<Integer> > multi_range_comp = ace_data_obj.get_photon_prod_multiplicity_range_data();
  vector<vector<Integer> > multi_int_comp   = ace_data_obj.get_photon_prod_multiplicity_int_data();
  vector<vector<Real> >    multi_ene_comp   = ace_data_obj.get_photon_prod_multiplicity_ene_data();
  vector<vector<Real> >    multi_data_comp  = ace_data_obj.get_photon_prod_multiplicity_data();
  vector<vector<Integer> > multi_range_ref  = ace_data_obj_ref.get_photon_prod_multiplicity_range_data();
  vector<vector<Integer> > multi_int_ref    = ace_data_obj_ref.get_photon_prod_multiplicity_int_data();
  vector<vector<Real> >    multi_ene_ref    = ace_data_obj_ref.get_photon_prod_multiplicity_ene_data();
  vector<vector<Real> >    multi_data_ref   = ace_data_obj_ref.get_photon_prod_multiplicity_data();

  vector<vector<Integer> > multi_range_comp_new = multi_range_comp;
  vector<vector<Integer> > multi_int_comp_new   = multi_int_comp;
  vector<vector<Real> >    multi_ene_comp_new   = multi_ene_comp;
  vector<vector<Real> >    multi_data_comp_new  = multi_data_comp;
  for(int i=0; i<i_max; i++)
  {
    if( ace_data_obj_ref.get_photon_prod_file_no()[i] == 12 )
    {
      int j_max_comp = static_cast<int>(multi_ene_comp[i].size());
      int j_max_ref  = static_cast<int>(multi_ene_ref[i].size());
      if( j_max_comp == j_max_ref && j_max_comp == 2 )
      {
        if( fabs(multi_data_comp[i][0] - multi_data_comp[i][1]) < min_ene_dif &&
            fabs(multi_data_ref[i][0]  - multi_data_ref[i][1])  < min_ene_dif )
        {
          Real dif_val = fabs(multi_data_ref[i][0]) * ace_comp_obj.get_tolerance_val();
          if( dif_val < min_value )
          {
            dif_val = min_value;
          } 

          if( fabs(multi_data_comp[i][0] - multi_data_ref[i][0]) > dif_val )
          {
            if( i != 0 )
            {
              int j_max_comp_m = static_cast<int>(multi_ene_comp[i-1].size());
              int j_max_ref_m  = static_cast<int>(multi_ene_ref[i-1].size());
              if( j_max_comp_m == j_max_ref_m && j_max_comp_m == 2 )
              {
                if( fabs(multi_data_comp[i-1][0] - multi_data_comp[i-1][1]) < min_ene_dif &&
                    fabs(multi_data_ref[i-1][0]  - multi_data_ref[i-1][1])  < min_ene_dif &&
                    fabs(multi_data_comp[i-1][0] - multi_data_ref[i][0]) < dif_val )
                {
                  modify_photon_prod_multiplicity_data_flg++;

                  multi_range_comp_new[i] = multi_range_comp[i-1];
                  multi_int_comp_new[i]   = multi_int_comp[i-1];
                  multi_ene_comp_new[i]   = multi_ene_comp[i-1];
                  multi_data_comp_new[i]  = multi_data_comp[i-1];
                }
              }
            }

            if( i != i_max - 1 )
            {
              int j_max_comp_p = static_cast<int>(multi_ene_comp[i+1].size());
              int j_max_ref_p  = static_cast<int>(multi_ene_ref[i+1].size());
              if( j_max_comp_p == j_max_ref_p && j_max_comp_p == 2 )
              {
                if( fabs(multi_data_comp[i+1][0] - multi_data_comp[i+1][1]) < min_ene_dif &&
                    fabs(multi_data_ref[i+1][0]  - multi_data_ref[i+1][1])  < min_ene_dif &&
                    fabs(multi_data_comp[i+1][0] - multi_data_ref[i][0]) < dif_val )
                {
                  modify_photon_prod_multiplicity_data_flg++;

                  multi_range_comp_new[i] = multi_range_comp[i+1];
                  multi_int_comp_new[i]   = multi_int_comp[i+1];
                  multi_ene_comp_new[i]   = multi_ene_comp[i+1];
                  multi_data_comp_new[i]  = multi_data_comp[i+1];
                }
              }
            }

            if( modify_photon_prod_multiplicity_data_flg == 1 )
            {
              cout << endl;
              cout << "Position : " << i+1 << " / " << i_max << endl;
              cout << "photon_prod_multiplicity_data[" << i+1 
                   << "][0] is not identical to the reference value." << endl;
              cout << "However, photon_prod_multiplicity_data[" << i << "][0] or "
                   << "photon_prod_multiplicity_data[" << i+2 << "][0] "
                   << "is identical to the reference value." << endl;
              cout << "In such case, this comparison program considers that there is no difference "
                   << "in this position (The comparison value is identical to the reference value)." << endl;
              cout << "This value is sorted of multiplicity_binding_ene." << endl;
              cout << "So, if the multiplicity_binding_ene value is overlapped, "
                   << "photon_prod_multiplicity_data may not be identical." << endl;
              cout << "Since the sorting method of FRENDY is different to that of  NJOY, "
                   << "the order of photon_prod_multiplicity_data may not be identical." << endl; 
              cout << "If identical sorting method is used, please check the calculation results." << endl;
              cout << "(This special treatment may not be appropriate.)" << endl;
              cout << endl;
            }
          }
        }
      }
    }
  }

  for(int i=0; i<i_max; i++)
  {
    ace_comp_obj.set_comp_data_position(i+1);
    ace_comp_obj.set_comp_data_information("photon_prod_file_no");
    ace_comp_obj.comp_int_data(ace_data_obj.get_photon_prod_file_no()[i],
                               ace_data_obj_ref.get_photon_prod_file_no()[i]);

    if( ace_data_obj_ref.get_photon_prod_file_no()[i] != 12 &&
        ace_data_obj_ref.get_photon_prod_file_no()[i] != 16 )
    {

      Integer grid_dif = abs( static_cast<Integer>(ace_data_obj.get_union_ene_grid().size())
                               - static_cast<Integer>(ace_data_obj_ref.get_union_ene_grid().size()) );

      int skip_flg = 0;
      for(Integer mod_no=0; mod_no<=2; mod_no++)
      {
        if( ace_data_obj.get_photon_prod_xs_non_zero_pos()[i][0]
              - ace_data_obj_ref.get_photon_prod_xs_non_zero_pos()[i][0] == grid_dif - mod_no &&
            ace_data_obj.get_photon_prod_xs_non_zero_pos()[i][1]
              - ace_data_obj_ref.get_photon_prod_xs_non_zero_pos()[i][1] == grid_dif + mod_no )
        {
          skip_flg = 1;
        }
        if( ace_data_obj.get_photon_prod_xs_non_zero_pos()[i][0]
              - ace_data_obj_ref.get_photon_prod_xs_non_zero_pos()[i][0] == grid_dif + mod_no &&
            ace_data_obj.get_photon_prod_xs_non_zero_pos()[i][1]
              - ace_data_obj_ref.get_photon_prod_xs_non_zero_pos()[i][1] == grid_dif - mod_no )
        {
          skip_flg = 1;
        }
        else if( ace_data_obj_ref.get_photon_prod_xs_non_zero_pos()[i][0]
                   - ace_data_obj.get_photon_prod_xs_non_zero_pos()[i][0] == grid_dif - mod_no &&
                 ace_data_obj_ref.get_photon_prod_xs_non_zero_pos()[i][1]
                   - ace_data_obj.get_photon_prod_xs_non_zero_pos()[i][1] == grid_dif + mod_no )
        {
          skip_flg = 1;
        }
        else if( ace_data_obj_ref.get_photon_prod_xs_non_zero_pos()[i][0]
                   - ace_data_obj.get_photon_prod_xs_non_zero_pos()[i][0] == grid_dif + mod_no &&
                 ace_data_obj_ref.get_photon_prod_xs_non_zero_pos()[i][1]
                   - ace_data_obj.get_photon_prod_xs_non_zero_pos()[i][1] == grid_dif - mod_no )
        {
          skip_flg = 1;
        }

        if( skip_flg != 0 )
        {
          break;
        }
      }

      if( skip_flg == 0 )
      {
        if( abs(ace_data_obj.get_photon_prod_xs_non_zero_pos()[i][0]
                - ace_data_obj_ref.get_photon_prod_xs_non_zero_pos()[i][0]) > grid_dif )
        {
          ace_comp_obj.set_comp_data_information("photon_prod_xs_non_zero_pos (start)");
          ace_comp_obj.comp_int_data(ace_data_obj.get_photon_prod_xs_non_zero_pos()[i][0],
                                     ace_data_obj_ref.get_photon_prod_xs_non_zero_pos()[i][0]);
        }

        if( abs(ace_data_obj.get_photon_prod_xs_non_zero_pos()[i][1]
                - ace_data_obj_ref.get_photon_prod_xs_non_zero_pos()[i][1]) > grid_dif )
        {
          ace_comp_obj.set_comp_data_information("photon_prod_xs_non_zero_pos (end)");
          ace_comp_obj.comp_int_data(ace_data_obj.get_photon_prod_xs_non_zero_pos()[i][1],
                                     ace_data_obj_ref.get_photon_prod_xs_non_zero_pos()[i][1]);
        }
      }

      vector<Real> ene_grid, ene_grid_ref;
      int j_max  = static_cast<int>(ace_data_obj.get_photon_prod_xs_non_zero_pos()[i][1]);
      int ene_no = static_cast<int>(ace_data_obj.get_photon_prod_xs_non_zero_pos()[i][0]) - 1;
      ene_grid.resize(j_max);
      for(int j=0; j<j_max; j++)
      {
        ene_grid[j] = ace_data_obj.get_union_ene_grid()[ene_no];
        ene_no++;
      }

      j_max  = static_cast<int>(ace_data_obj_ref.get_photon_prod_xs_non_zero_pos()[i][1]);
      ene_no = static_cast<int>(ace_data_obj_ref.get_photon_prod_xs_non_zero_pos()[i][0]) - 1;
      ene_grid_ref.resize(j_max);
      for(int j=0; j<j_max; j++)
      {
        ene_grid_ref[j] = ace_data_obj_ref.get_union_ene_grid()[ene_no];
        ene_no++;
      }

      ace_comp_obj.set_comp_data_information("photon_prod_xs_data");
      ace_comp_obj.comp_table_data(ene_grid,     ace_data_obj.get_photon_prod_xs_data()[i],
                                   ene_grid_ref, ace_data_obj_ref.get_photon_prod_xs_data()[i]);
    }
    else
    {
      ace_comp_obj.set_comp_data_information("photon_prod_reaction_type");
      ace_comp_obj.comp_int_data(ace_data_obj.get_photon_prod_reaction_type()[i],
                                 ace_data_obj_ref.get_photon_prod_reaction_type()[i]);
      if( ace_data_obj_ref.get_photon_prod_file_no()[i] == 12 )
      {
        ace_comp_obj.set_comp_data_information
        ("photon_prod_multiplicity_range_data, photon_prod_multiplicity_int_data, photon_prod_multiplicity_ene_data, photon_prod_multiplicity_data");
        ace_comp_obj.comp_table_data
          ( multi_range_comp_new[i], multi_int_comp_new[i], multi_ene_comp_new[i],  multi_data_comp_new[i],
            multi_range_ref[i],      multi_int_ref[i],      multi_ene_ref[i],       multi_data_ref[i] );
      }
      else
      {
        ace_comp_obj.set_comp_data_information
        ("photon_prod_distr_range_data, photon_prod_distr_int_data, photon_prod_distr_ene_data, photon_prod_distr_data");
        ace_comp_obj.comp_table_data( ace_data_obj.get_photon_prod_distr_range_data()[i],
                                      ace_data_obj.get_photon_prod_distr_int_data()[i],
                                      ace_data_obj.get_photon_prod_distr_ene_data()[i],
                                      ace_data_obj.get_photon_prod_distr_data()[i],
                                      ace_data_obj_ref.get_photon_prod_distr_range_data()[i],
                                      ace_data_obj_ref.get_photon_prod_distr_int_data()[i],
                                      ace_data_obj_ref.get_photon_prod_distr_ene_data()[i],
                                      ace_data_obj_ref.get_photon_prod_distr_data()[i] );
      }
    }
  }

  ace_comp_obj.clear_comp_data_position();
  if( comp_pointer_flg == comp_pointer_mode )
  {
    ace_comp_obj.set_comp_data_information("photon_angular_pointer");
    ace_comp_obj.comp_list_data_pointer(ace_data_obj.get_photon_angular_pointer(),
                                        ace_data_obj_ref.get_photon_angular_pointer());
  }

  for(int i=0; i<i_max; i++)
  {
    ace_comp_obj.set_comp_data_position(i+1);

    int j_max = static_cast<int>(ace_data_obj_ref.get_photon_angular_distr_ene_data()[i].size());
    ace_comp_obj.set_comp_data_information("photon_angular_distr_ene_data");
    ace_comp_obj.comp_int_data
      (static_cast<int>(ace_data_obj.get_photon_angular_distr_ene_data()[i].size()), j_max);
    if( j_max == 0 )
    {
      continue;
    }

    ace_comp_obj.set_comp_data_information("photon_angular_distr_ene_data");
    ace_comp_obj.comp_list_data(ace_data_obj.get_photon_angular_distr_ene_data()[i],
                                ace_data_obj_ref.get_photon_angular_distr_ene_data()[i]);

    if( comp_pointer_flg == comp_pointer_mode )
    {
      ace_comp_obj.set_comp_data_information("photon_angular_ene_pointer");
      ace_comp_obj.comp_list_data_pointer(ace_data_obj.get_photon_angular_ene_pointer()[i],
                                          ace_data_obj_ref.get_photon_angular_ene_pointer()[i]);
    }

    for(int j=0; j<j_max; j++)
    {
      Real min_val = 1.0E-8;

      ace_comp_obj.set_comp_data_position(i+1, j+1);
      ace_comp_obj.set_comp_data_information("photon_angular_distr_prob_cos_data");
      ace_comp_obj.comp_list_data_modify_small_value
        (ace_data_obj.get_photon_angular_distr_prob_cos_data()[i][j],
         ace_data_obj_ref.get_photon_angular_distr_prob_cos_data()[i][j], min_val);
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataCompare::comp_ace_data_photon_energy_distr_data()
{
  int i_max = static_cast<int>(ace_data_obj_ref.get_photon_energy_distr_flg().size());
  ace_comp_obj.set_comp_data_information("size of photon_energy_distr_flg");
  ace_comp_obj.comp_int_data(static_cast<int>(ace_data_obj.get_photon_energy_distr_flg().size()), i_max);
  if( i_max == 0 )
  {
    return;
  }

  if( comp_pointer_flg == comp_pointer_mode )
  {
    ace_comp_obj.set_comp_data_information("photon_ene_pointer");
    ace_comp_obj.comp_list_data_pointer(ace_data_obj.get_photon_ene_pointer(),
                                        ace_data_obj_ref.get_photon_ene_pointer());
  }

  int all_zero_flg = 0;
  for(int i=0; i<i_max; i++)
  {
    ace_comp_obj.set_comp_data_position(i+1);
    ace_comp_obj.set_comp_data_information("photon_energy_distr_flg");
    ace_comp_obj.comp_int_data(ace_data_obj.get_photon_energy_distr_flg()[i],
                               ace_data_obj_ref.get_photon_energy_distr_flg()[i]);

    if( comp_pointer_flg == comp_pointer_mode )
    {
      ace_comp_obj.set_comp_data_information("photon_ene_distr_pointer");
      ace_comp_obj.comp_int_data(ace_data_obj.get_photon_ene_distr_pointer()[i],
                                 ace_data_obj_ref.get_photon_ene_distr_pointer()[i]);
    }

    ace_comp_obj.set_comp_data_information
    ("photon_energy_distr_range_data, photon_energy_distr_int_data, photon_energy_distr_ene_data, photon_energy_distr_prob_data");
    ace_comp_obj.comp_table_data(ace_data_obj.get_photon_energy_distr_range_data()[i],
                                 ace_data_obj.get_photon_energy_distr_int_data()[i],
                                 ace_data_obj.get_photon_energy_distr_ene_data()[i],
                                 ace_data_obj.get_photon_energy_distr_prob_data()[i],
                                 ace_data_obj_ref.get_photon_energy_distr_range_data()[i],
                                 ace_data_obj_ref.get_photon_energy_distr_int_data()[i],
                                 ace_data_obj_ref.get_photon_energy_distr_ene_data()[i],
                                 ace_data_obj_ref.get_photon_energy_distr_prob_data()[i]);

    if( ace_data_obj_ref.get_photon_energy_distr_flg()[i] == 1 )
    {
      //This flag is not available in this program
    }
    else if( ace_data_obj_ref.get_photon_energy_distr_flg()[i] == 2 )
    {
      ace_comp_obj.set_comp_data_information("photon_energy_distr_ene_flg");
      ace_comp_obj.comp_int_data(ace_data_obj.get_photon_energy_distr_ene_flg()[i],
                                 ace_data_obj_ref.get_photon_energy_distr_ene_flg()[i]);
      ace_comp_obj.set_comp_data_information("photon_energy_distr_binding_ene_data");
      ace_comp_obj.comp_real_data(ace_data_obj.get_photon_energy_distr_binding_ene_data()[i],
                                  ace_data_obj_ref.get_photon_energy_distr_binding_ene_data()[i]);
    }
    else if( ace_data_obj_ref.get_photon_energy_distr_flg()[i] ==  4 ||
             ace_data_obj_ref.get_photon_energy_distr_flg()[i] == 44 )
    {
      ace_comp_obj.set_comp_data_information
      ("photon_energy_distr_ene_in_range_data, photon_energy_distr_ene_in_int_data");
      ace_comp_obj.comp_interpolation_data(ace_data_obj.get_photon_energy_distr_ene_in_range_data()[i],
                                           ace_data_obj.get_photon_energy_distr_ene_in_int_data()[i],
                                           ace_data_obj_ref.get_photon_energy_distr_ene_in_range_data()[i],
                                           ace_data_obj_ref.get_photon_energy_distr_ene_in_int_data()[i]);
      ace_comp_obj.set_comp_data_information("photon_energy_distr_ene_in_data");
      ace_comp_obj.comp_list_data(ace_data_obj.get_photon_energy_distr_ene_in_data()[i],
                                  ace_data_obj_ref.get_photon_energy_distr_ene_in_data()[i]);

      if( comp_pointer_flg == comp_pointer_mode )
      {
        ace_comp_obj.set_comp_data_information("photon_ene_weight_pointer");
        ace_comp_obj.comp_list_data_pointer(ace_data_obj.get_photon_ene_weight_pointer()[i],
                                            ace_data_obj_ref.get_photon_ene_weight_pointer()[i]);
      }

      int j_max = static_cast<int>(ace_data_obj_ref.get_photon_energy_distr_ene_in_data()[i].size());
      ace_comp_obj.set_comp_data_information("j_max of photon_energy_distr_ene_in_data");
      ace_comp_obj.comp_int_data(ace_data_obj.get_photon_energy_distr_ene_in_data()[i].size(), j_max);
      if( j_max != static_cast<int>(ace_data_obj.get_photon_energy_distr_ene_in_data()[i].size()) )
      {
        continue;
      }

      for(int j=0; j<j_max; j++)
      {
        Integer int_val = ace_data_obj.get_photon_energy_distr_weight_int_data()[i][j] % 10;
        Integer int_ref = ace_data_obj_ref.get_photon_energy_distr_weight_int_data()[i][j] % 10;

        ace_comp_obj.set_comp_data_position(i+1, j+1);
        ace_comp_obj.set_comp_data_information("photon_energy_distr_weight_int_data");
        if( comp_pointer_flg == comp_pointer_mode )
        {
          ace_comp_obj.comp_int_data(ace_data_obj.get_photon_energy_distr_weight_int_data()[i][j],
                                     ace_data_obj_ref.get_photon_energy_distr_weight_int_data()[i][j]);
        }
        else
        {
          ace_comp_obj.set_comp_data_information("photon_energy_distr_weight_int_data%10");
          ace_comp_obj.comp_int_data(int_val, int_ref);
        }

        vector<vector<Real> > weight_ene_data, weight_data, weight_data_integ,
                              weight_ene_data_ref, weight_data_ref, weight_data_integ_ref;
        vector<Real>          weight_ene_data_tmp, weight_data_tmp, weight_data_integ_tmp;

        weight_ene_data_tmp   = ace_data_obj.get_photon_energy_distr_weight_ene_data()[i][j];
        weight_data_tmp       = ace_data_obj.get_photon_energy_distr_weight_data()[i][j];
        weight_data_integ_tmp = ace_data_obj.get_photon_energy_distr_weight_data_integ()[i][j];

        weight_ene_data.resize(2);
        weight_data.resize(2);
        weight_data_integ.resize(2);
        Integer data_no = ace_data_obj.get_photon_energy_distr_weight_int_data()[i][j] / 10;
        int k_max = static_cast<int>(weight_ene_data_tmp.size());
        for(int k=0; k<k_max; k++)
        {
          int ele_no = 1;
          if( k < static_cast<int>(data_no) )
          {
            ele_no = 0;
          }

          weight_ene_data[ele_no].push_back(weight_ene_data_tmp[k]);
          weight_data[ele_no].push_back(weight_data_tmp[k]);
          weight_data_integ[ele_no].push_back(weight_data_integ_tmp[k]);
        }

        weight_ene_data_tmp   = ace_data_obj_ref.get_photon_energy_distr_weight_ene_data()[i][j];
        weight_data_tmp       = ace_data_obj_ref.get_photon_energy_distr_weight_data()[i][j];
        weight_data_integ_tmp = ace_data_obj_ref.get_photon_energy_distr_weight_data_integ()[i][j];

        weight_ene_data_ref.resize(2);
        weight_data_ref.resize(2);
        weight_data_integ_ref.resize(2);
        data_no = ace_data_obj_ref.get_photon_energy_distr_weight_int_data()[i][j] / 10;
        k_max = static_cast<int>(weight_ene_data_tmp.size());
        for(int k=0; k<k_max; k++)
        {
          int ele_no = 1;
          if( k < static_cast<int>(data_no) )
          {
            ele_no = 0;
          }

          weight_ene_data_ref[ele_no].push_back(weight_ene_data_tmp[k]);
          weight_data_ref[ele_no].push_back(weight_data_tmp[k]);
          weight_data_integ_ref[ele_no].push_back(weight_data_integ_tmp[k]);
        }

        Real initial_val = 0.0;
        if( static_cast<int>(weight_data[0].size() > 0) || static_cast<int>(weight_data_ref[0].size() > 0) )
        {
          if( ace_comp_obj.check_list_data_order(weight_ene_data[0]) >= 0 &&
              ace_comp_obj.check_list_data_order(weight_ene_data_ref[0]) >= 0 )
          {
            ace_comp_obj.set_comp_data_information
            ("No. 1 / 2, photon_energy_distr_weight_ene_data, photon_energy_distr_weight_data, photon_energy_distr_weight_data_integ");
            if( int_ref > 0 )
            {
              //Modify overlapped data
              int modify_vec_flg = 0;
              int l_max = static_cast<int>(weight_ene_data_ref[0].size());
              for(int l=1; l<l_max; l++)
              {
                Real ene_ref_pre = weight_ene_data_ref[0][l-1];
                if( fabs(weight_ene_data_ref[0][l] - ene_ref_pre) < fabs(3.0E-5*ene_ref_pre) )
                {
                  modify_vec_flg++;

                  int m_max = static_cast<int>(weight_ene_data[0].size());
                  for(int m=1; m<m_max; m++)
                  {
                    Real ene_pre = weight_ene_data[0][m-1];
                    if( fabs(weight_ene_data[0][m] - ene_pre) < fabs(3.0E-5*ene_pre) )
                    {
                      if( fabs(ene_pre - ene_ref_pre) < fabs(3.0E-5*ene_pre) )
                      {
                        if( fabs(weight_data[0][m] - weight_data_ref[0][l-1]) <
                            fabs(weight_data[0][m] - weight_data_ref[0][l]) )
                        {
                          weight_ene_data[0][m]     = weight_ene_data_ref[0][l-1];
                          weight_data[0][m]         = weight_data_ref[0][l-1];
                          weight_data_integ[0][m]   = weight_data_integ_ref[0][l-1];
                        }

                        if( fabs(weight_data[0][m-1] - weight_data_ref[0][l]) <
                            fabs(weight_data[0][m-1] - weight_data_ref[0][l-1]) )
                        {
                          weight_ene_data[0][m-1]     = weight_ene_data_ref[0][l];
                          weight_data[0][m-1]         = weight_data_ref[0][l];
                          weight_data_integ[0][m-1]   = weight_data_integ_ref[0][l];
                        }
                      }
                    }
                  }
                }
              }

              //For reference calculation data 
              vector<Real> weight_ene_data_new, weight_data_new, weight_data_integ_new;
              weight_ene_data_new.push_back(weight_ene_data_ref[0][0]);
              weight_data_new.push_back(weight_data_ref[0][0]);
              weight_data_integ_new.push_back(weight_data_integ_ref[0][0]);
                  l_max   = static_cast<int>(weight_ene_data_ref[0].size());
              int tail_no = 0;
              for(int l=1; l<l_max; l++)
              {
                Real ene_ref_pre = weight_ene_data_ref[0][l-1];
                if( fabs(weight_ene_data_ref[0][l] - ene_ref_pre) < fabs(3.0E-5*ene_ref_pre) )
                {
                  if( fabs(weight_data_ref[0][l-1]) < min_value && fabs(weight_data_ref[0][l]) > min_value )
                  {
                    weight_ene_data_new[tail_no]   = weight_ene_data_ref[0][l];
                    weight_data_new[tail_no]       = weight_data_ref[0][l];
                    weight_data_integ_new[tail_no] = weight_data_integ_ref[0][l];
                  }
                  else if( fabs(weight_data_ref[0][l]) > min_value )
                  {
                    weight_ene_data_new.push_back(weight_ene_data_ref[0][l]);
                    weight_data_new.push_back(weight_data_ref[0][l]);
                    weight_data_integ_new.push_back(weight_data_integ_ref[0][l]);
                    tail_no++;
                  }
                }
                else
                {
                  weight_ene_data_new.push_back(weight_ene_data_ref[0][l]);
                  weight_data_new.push_back(weight_data_ref[0][l]);
                  weight_data_integ_new.push_back(weight_data_integ_ref[0][l]);
                  tail_no++;
                }
              }
              weight_ene_data_ref[0]   = weight_ene_data_new;
              weight_data_ref[0]       = weight_data_new;
              weight_data_integ_ref[0] = weight_data_integ_new;
              weight_ene_data_new.resize(0);
              weight_data_new.resize(0);
              weight_data_integ_new.resize(0);

              if( weight_ene_data.size() == 0 )
              {
                ace_comp_obj.set_comp_data_information("size of weight_ene_data");
                ace_comp_obj.comp_int_data(weight_ene_data.size(), weight_ene_data_ref.size());
                continue;
              }
              else if( weight_ene_data[0].size() == 0 )
              {
                ace_comp_obj.set_comp_data_information("size of weight_ene_data[0]");
                ace_comp_obj.comp_int_data(weight_ene_data[0].size(), weight_ene_data_ref[0].size());
                continue;
              }

              //For comparing calculation data 
              weight_ene_data_new.push_back(weight_ene_data[0][0]);
              weight_data_new.push_back(weight_data[0][0]);
              weight_data_integ_new.push_back(weight_data_integ[0][0]);
              l_max   = static_cast<int>(weight_ene_data[0].size());
              tail_no = 0;
              for(int l=1; l<l_max; l++)
              {
                Real ene_pre = weight_ene_data[0][l-1];
                if( fabs(weight_ene_data[0][l] - ene_pre) < fabs(3.0E-5*ene_pre) )
                {
                  if( fabs(weight_data[0][l-1]) < min_value && fabs(weight_data[0][l]) > min_value )
                  {
                    weight_ene_data_new[tail_no]   = weight_ene_data[0][l];
                    weight_data_new[tail_no]       = weight_data[0][l];
                    weight_data_integ_new[tail_no] = weight_data_integ[0][l];
                  }
                  else if( fabs(weight_data[0][l]) > min_value )
                  {
                    weight_ene_data_new.push_back(weight_ene_data[0][l]);
                    weight_data_new.push_back(weight_data[0][l]);
                    weight_data_integ_new.push_back(weight_data_integ[0][l]);
                    tail_no++;
                  }
                }
                else
                {
                  weight_ene_data_new.push_back(weight_ene_data[0][l]);
                  weight_data_new.push_back(weight_data[0][l]);
                  weight_data_integ_new.push_back(weight_data_integ[0][l]);
                  tail_no++;
                }
              }
              weight_ene_data[0]   = weight_ene_data_new;
              weight_data[0]       = weight_data_new;
              weight_data_integ[0] = weight_data_integ_new;
              weight_ene_data_new.resize(0);
              weight_data_new.resize(0);
              weight_data_integ_new.resize(0);

              if( modify_vec_flg == 0 )
              {
                ace_comp_obj.comp_table_data_no_integral
                  (int_val, weight_ene_data[0],     weight_data[0],     weight_data_integ[0],
                   int_ref, weight_ene_data_ref[0], weight_data_ref[0], weight_data_integ_ref[0]);
              }
              else //if( modify_vec_flg > 0 )
              {
                ace_comp_obj.comp_table_data(int_val, weight_ene_data[0],     weight_data[0],
                                             int_ref, weight_ene_data_ref[0], weight_data_ref[0]);
              }
            }
            else
            {
              if( static_cast<int>(weight_ene_data[0].size())
                   == static_cast<int>(weight_ene_data_ref[0].size()) )
              {
                ace_comp_obj.set_comp_data_information("No. 1 / 2, photon_energy_distr_weight_ene_data");
                ace_comp_obj.comp_list_data(weight_ene_data[0],   weight_ene_data_ref[0]);

                ace_comp_obj.set_comp_data_information("No. 1 / 2, photon_energy_distr_weight_data");
                ace_comp_obj.comp_list_data(weight_data[0],       weight_data_ref[0]);

                ace_comp_obj.set_comp_data_information("No. 1 / 2, photon_energy_distr_weight_data_integ");
                ace_comp_obj.comp_list_data(weight_data_integ[0], weight_data_integ_ref[0]);
              }
              else
              {
                int l_max = static_cast<int>(weight_ene_data[0].size());
                for(int l=0; l<l_max; l++)
                {
                  Real weight_ene_data_val = weight_ene_data[0][l];
                  Real weight_ene_data_dif = fabs(weight_ene_data_val * 1.0E-5);

                  int  m_max                     = static_cast<int>(weight_ene_data_ref[0].size());
                  int  m_pos_n                   = -1; //normal data
                  int  m_pos_i                   = -1; //integral data
                  int  zero_chk                  = -1;
                  Real weight_data_dif_min       = 0.0;
                  Real weight_data_integ_dif_min = 0.0;
                  Real weight_data_dif           = 0.0;
                  Real weight_data_integ_dif     = 0.0;
                  for(int m=0; m<m_max; m++)
                  {
                    if( fabs( weight_data_ref[0][m] )  > min_value )
                    {
                      zero_chk = m;
                    }

                    if( fabs(weight_ene_data_val - weight_ene_data_ref[0][m]) < weight_ene_data_dif )
                    {
                      if( m_pos_n < 0 )
                      {
                        m_pos_n = m;
                        m_pos_i = m;
                        weight_data_dif_min       = fabs(weight_data[0][l]       - weight_data_ref[0][m]);
                        weight_data_integ_dif_min = fabs(weight_data_integ[0][l] - weight_data_integ_ref[0][m]);
                      }
                      else
                      {
                        weight_data_dif       = fabs(weight_data[0][l]       - weight_data_ref[0][m]);
                        weight_data_integ_dif = fabs(weight_data_integ[0][l] - weight_data_integ_ref[0][m]);
                        if( weight_data_dif < weight_data_dif_min )
                        {
                          m_pos_n = m;
                          weight_data_dif_min = weight_data_dif;
                        }

                        if( weight_data_integ_dif < weight_data_integ_dif_min )
                        {
                          m_pos_i = m;
                          weight_data_integ_dif_min = weight_data_integ_dif;
                        }
                      }
                    }
                  }

                  if( m_pos_n < 0 )
                  {
                    cout << endl;
                    cout << "Data name information : No. 1 / 2, photon_energy_distr_weight_ene_data" << endl;
                    cout << "Position : " << i+1 << " / " << i_max << ", " << j+1 << " / " << j_max << ", "
                                          << l+1 << " / " << l_max << endl;
                    cout << "weight_ene_data[0] : " << weight_ene_data_val << endl;
                    cout << "This value is not found in weight_ene_data_ref[0]" << endl;
                    cout << "The comparing scheme is skipped." << endl << endl;
                  }
                  else if( zero_chk < 0 )
                  {
                    if( all_zero_flg == 0 )
                    {
                      cout << endl;
                      cout << "Data name information : No. 1 / 2, photon_energy_distr_weight_data" << endl;
                      cout << "Position : " << i+1 << " / " << i_max << ", " << j+1 << " / " << j_max << ", "
                                            << l+1 << " / " << l_max << endl;
                      cout << "weight_ene_data[0] : " << weight_ene_data_val << endl;
                      cout << "All of weight_data_ref[0] is equal to zero." << endl;
                      cout << "The reference value may not be appropriated." << endl;
                      cout << "The comparing scheme is skipped." << endl << endl;
                    }

                    all_zero_flg++;
                  }
                  else
                  {
                    ace_comp_obj.set_comp_data_information("No. 1 / 2, photon_energy_distr_weight_data");
                    ace_comp_obj.comp_real_data(weight_data[0][l],       weight_data_ref[0][m_pos_n]);

                    ace_comp_obj.set_comp_data_information("No. 1 / 2, photon_energy_distr_weight_data_integ");
                    ace_comp_obj.comp_real_data(weight_data_integ[0][l], weight_data_integ_ref[0][m_pos_i]);
                  }
                }
              }
            }
          }
          else
          {
            cout << endl;
            cout << "Position : " << i+1 << " / " << i_max << ", " << j+1 << " / " << j_max << endl;

            Real    x_m            = 0.0;
            Real    x_p            = 0.0;
            Integer order_flg_comp = ace_comp_obj.check_list_data_order(weight_ene_data[0], x_p, x_m);
            if( order_flg_comp < 0 )
            {
              cout << "weight_ene_data[0] for comparison is not appropriate order." << endl;
              cout.precision(11);
              cout.setf(ios::showpoint);
              cout.setf(ios::scientific);
              cout << "  x[i-1] : " << x_m << endl << "  x[i]   : " << x_p << endl;
            }

            Integer order_flg_ref = ace_comp_obj.check_list_data_order(weight_ene_data_ref[0], x_p, x_m);
            if( order_flg_ref < 0 )
            {
              cout << "weight_ene_data[0] for reference is not appropriate order." << endl;
              cout.precision(11);
              cout.setf(ios::showpoint);
              cout.setf(ios::scientific);
              cout << "  x[i-1] : " << x_m << endl << "  x[i]   : " << x_p << endl;
            }
            cout << "The comparing scheme is skipped." << endl << endl;
          }

          k_max = static_cast<int>(weight_data_integ[0].size());
          initial_val = weight_data_integ[0][k_max-1];
        }
        weight_ene_data[0].clear();
        weight_data[0].clear();
        weight_data_integ[0].clear();
        weight_ene_data_ref[0].clear();
        weight_data_ref[0].clear();
        weight_data_integ_ref[0].clear();

        if( static_cast<int>(weight_data[1].size() > 0) || static_cast<int>(weight_data_ref[1].size() > 0) )
        {
          if( ace_comp_obj.check_list_data_order(weight_ene_data[1]) >= 0 &&
              ace_comp_obj.check_list_data_order(weight_ene_data_ref[1]) >= 0 )
          {
            ace_comp_obj.set_comp_data_information
            ("No. 2 / 2, photon_energy_distr_weight_ene_data, photon_energy_distr_weight_data, photon_energy_distr_weight_data_integ");
            if( int_ref > 0 )
            {
              int ene_chk_flg  = 0;
              int data_chk_flg = 0;
                  k_max       = static_cast<int>(weight_ene_data_ref[1].size());
              for(int k=0; k<k_max; k++)
              {
                if( fabs(weight_ene_data_ref[1][k]) > min_value )
                {
                  ene_chk_flg = 1;
                }

                if( fabs(weight_data_ref[1][k]) > min_value )
                {
                  data_chk_flg = 1;
                }

                if( ene_chk_flg > 0 && data_chk_flg > 0 )
                {
                  break;
                }
              }

              if( data_chk_flg == 0 )
              {
                if( ene_chk_flg > 0 )
                {
                  int data_chk_comp_flg = 0;
                  for(int k=0; k<static_cast<int>(weight_ene_data[1].size()); k++)
                  {
                    if( fabs(weight_data[1][k]) > min_value )
                    {
                      data_chk_comp_flg = 1;
                      break;
                    }
                  }

                  if( data_chk_comp_flg > 0 )
                  {
                    //skip comparison
                    string func_name  = "comp_ace_data_photon_energy_distr_data";

                    ostringstream oss01, oss02;
                    oss01 << i+1;
                    oss02 << j+1;
                    string str_data01 = "Data name information : No. 2 / 2, photon_energy_distr_weight_ene_data, photon_energy_distr_weight_data, photon_energy_distr_weight_data_integ";
                    string str_data02 = "Index information     : (" + oss01.str() + ", " + oss02.str() + ")";

                    vector<string> err_com;
                    err_com.push_back(str_data01);
                    err_com.push_back(str_data02);
                    err_com.push_back("All reference data (photon_energy_distr_weight_data) is zero.");
                    err_com.push_back("Reference data may not be appropriate.");
                    err_com.push_back("We skip this comparison.");
                    err_obj.output_caution(class_name, func_name, err_com);
                  }
                }
              }
              else if( ene_chk_flg > 0 )
              {
                ace_comp_obj.comp_table_data
                  (int_val, weight_ene_data[1],     weight_data[1],     weight_data_integ[1],
                   int_ref, weight_ene_data_ref[1], weight_data_ref[1], weight_data_integ_ref[1], initial_val);
              }
              else
              {
                ace_comp_obj.comp_int_data(int_val, int_ref);
                ace_comp_obj.comp_list_data(weight_ene_data[1], weight_ene_data_ref[1]);
                ace_comp_obj.comp_list_data(weight_data[1], weight_data_ref[1]);
                ace_comp_obj.comp_list_data(weight_data_integ[1], weight_data_integ_ref[1]);
              }
            }
            else
            {
              ace_comp_obj.set_comp_data_information("No. 2 / 2, photon_energy_distr_weight_ene_data");
              ace_comp_obj.comp_list_data(weight_ene_data[1],   weight_ene_data_ref[1]);

              ace_comp_obj.set_comp_data_information("No. 2 / 2, photon_energy_distr_weight_data");
              ace_comp_obj.comp_list_data(weight_data[1],       weight_data_ref[1]);

              ace_comp_obj.set_comp_data_information("No. 2 / 2, photon_energy_distr_weight_data_integ");
              ace_comp_obj.comp_list_data(weight_data_integ[1], weight_data_integ_ref[1]);
            }
          }
          else
          {
            cout << endl;
            cout << "Position : " << i+1 << " / " << i_max << ", " << j+1 << " / " << j_max << endl;
            if( ace_comp_obj.check_list_data_order(weight_ene_data[1]) < 0 )
            {
              cout << "weight_ene_data[1] for comparison is not appropriate order." << endl;
            }
            if( ace_comp_obj.check_list_data_order(weight_ene_data_ref[1]) < 0 )
            {
              cout << "weight_ene_data[1] for reference is not appropriate order." << endl;
            }
            cout << "The comparing scheme is skipped." << endl << endl;
          }
        }
        weight_ene_data[1].clear();
        weight_data[1].clear();
        weight_data_integ[1].clear();
        weight_ene_data_ref[1].clear();
        weight_data_ref[1].clear();
        weight_data_integ_ref[1].clear();

        weight_ene_data.clear();
        weight_data.clear();
        weight_data_integ.clear();
        weight_ene_data_ref.clear();
        weight_data_ref.clear();
        weight_data_integ_ref.clear();
      }
    }
  }

  ace_comp_obj.clear_comp_data_position();
  ace_comp_obj.set_comp_data_information("photon_prod_reaction_type_without_xs");
  ace_comp_obj.comp_list_data(ace_data_obj.get_photon_prod_reaction_type_without_xs(),
                              ace_data_obj_ref.get_photon_prod_reaction_type_without_xs());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataCompare::comp_ace_data_particle_production_data()
{
  int i_max     = static_cast<int>(ace_data_obj.get_particle_prod_flg().size());
  int i_max_ref = static_cast<int>(ace_data_obj_ref.get_particle_prod_flg().size());

  int         zero_count_no = 0;
  vector<int> zero_count_chk;
  zero_count_chk.resize(i_max);
  if( i_max != i_max_ref )
  {
    for(int i=0; i<i_max; i++)
    {
      zero_count_chk[i] = -1 * zero_count_no;
      if( ace_data_obj.get_particle_prod_count()[i] == 0 )
      {
        zero_count_no++;
        zero_count_chk[i] = zero_count_no;
      }
    }
  }


  if( i_max != i_max_ref + zero_count_no && i_max != i_max_ref )
  {
    ace_comp_obj.set_comp_data_information("size of particle_prod_flg");
    ace_comp_obj.comp_int_data(i_max, i_max_ref);
  }

  if( i_max == 0 )
  {
    return;
  }

  int ele_no                          = 0;
  int particle_prod_b_prob_data_check = 0;
  for(int i=0; i<i_max; i++)
  {
    ace_comp_obj.set_comp_data_position(i+1);
    if( zero_count_no != 0 )
    {
      if( zero_count_chk[i] > 0 )
      {
        continue;
      }
    }
    if( static_cast<int>(ace_data_obj_ref.get_particle_prod_flg().size()) < ele_no+1)
    {
      func_name  = "comp_ace_data_particle_production_data()";

      ostringstream oss01, oss02;
      oss01 << static_cast<int>(ace_data_obj_ref.get_particle_prod_flg().size());
      oss02 << ele_no + 1;
      string str_data01 = "size of particle_prod_flg (ref) : " + oss01.str();
      string str_data02 = "ele_no                          : " + oss02.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back("The size of particle_prod_flg (ref) is smaller than ele_no.");
      err_com.push_back("Reference data or comparison data may not be appropriate.");
      err_obj.output_caution(class_name, func_name, err_com);

      continue;
    }

    ace_comp_obj.set_comp_data_information("particle_prod_flg");
    ace_comp_obj.comp_int_data(ace_data_obj.get_particle_prod_flg()[i],
                               ace_data_obj_ref.get_particle_prod_flg()[ele_no]);

    ace_comp_obj.set_comp_data_information("particle_prod_count");
    ace_comp_obj.comp_int_data(ace_data_obj.get_particle_prod_count()[i],
                               ace_data_obj_ref.get_particle_prod_count()[ele_no]);

    if( comp_pointer_flg == comp_pointer_mode )
    {
      ace_comp_obj.set_comp_data_information("particle_prod_pointer");
      ace_comp_obj.comp_list_data_pointer(ace_data_obj.get_particle_prod_pointer()[i],
                                          ace_data_obj_ref.get_particle_prod_pointer()[ele_no]);
    }


    if( comp_pointer_flg == comp_pointer_mode )
    {
      ace_comp_obj.set_comp_data_information("particle_prod_ene_sta");
      ace_comp_obj.comp_int_data(ace_data_obj.get_particle_prod_ene_sta()[i],
                                 ace_data_obj_ref.get_particle_prod_ene_sta()[ele_no]);
      ace_comp_obj.set_comp_data_information("particle_prod_ene_no");
      ace_comp_obj.comp_int_data(ace_data_obj.get_particle_prod_ene_no()[i],
                                 ace_data_obj_ref.get_particle_prod_ene_no()[ele_no]);
    }

    vector<Real> ene_comp, ene_ref, ene_tmp;

    ene_tmp     = ace_data_obj.get_union_ene_grid();
    int j_max   = static_cast<int>(ene_tmp.size());
    int ene_no  = static_cast<int>(ace_data_obj.get_particle_prod_ene_no()[i]);
    int ene_sta = static_cast<int>(ace_data_obj.get_particle_prod_ene_sta()[i]) - 1;
    ene_comp.resize(ene_no);
    int pos = 0;
    for(int j=ene_sta; j<j_max; j++)
    {
      ene_comp[pos] = ene_tmp[j];
      pos++;
    }

    ene_tmp = ace_data_obj_ref.get_union_ene_grid();
    j_max   = static_cast<int>(ene_tmp.size());
    ene_no  = static_cast<int>(ace_data_obj_ref.get_particle_prod_ene_no()[ele_no]);
    ene_sta = static_cast<int>(ace_data_obj_ref.get_particle_prod_ene_sta()[ele_no]) - 1;
    ene_ref.resize(ene_no);
    pos = 0;
    for(int j=ene_sta; j<j_max; j++)
    {
      ene_ref[pos] = ene_tmp[j];
      pos++;
    }

    ace_comp_obj.set_comp_data_information("particle_prod_xs");
    ace_comp_obj.comp_table_data(ene_comp, ace_data_obj.get_particle_prod_xs()[i],
                                 ene_ref,  ace_data_obj_ref.get_particle_prod_xs()[ele_no]);

    vector<Real> prod_heat     = ace_data_obj.get_particle_prod_heat()[i];
    vector<Real> prod_heat_ref = ace_data_obj_ref.get_particle_prod_heat()[ele_no];
        j_max     = static_cast<int>(prod_heat.size());
    int j_max_ref = static_cast<int>(prod_heat_ref.size());
    if( j_max > 0 && j_max_ref > 0 )
    {
      if( fabs(prod_heat[0]) > min_value && fabs(prod_heat_ref[0]) < min_value )
      {
        vector<Real> ene_ref_new, prod_heat_ref_new;
        ene_ref_new.resize(j_max_ref-1);
        prod_heat_ref_new.resize(j_max_ref-1);
        for(int j=0; j<j_max_ref-1; j++)
        {
          ene_ref_new[j]       = ene_ref[j+1];
          prod_heat_ref_new[j] = prod_heat_ref[j+1];
        }
        ene_ref       = ene_ref_new;
        prod_heat_ref = prod_heat_ref_new;
        ene_ref_new.clear();
        prod_heat_ref_new.clear();
      }
    }
    ace_comp_obj.set_comp_data_information("particle_prod_heat");
    ace_comp_obj.comp_table_data(ene_comp, prod_heat, ene_ref, prod_heat_ref);

    ace_comp_obj.set_comp_data_information("particle_prod_reaction_type_all");
    ace_comp_obj.comp_list_data(ace_data_obj.get_particle_prod_reaction_type_all()[i],
                                ace_data_obj_ref.get_particle_prod_reaction_type_all()[ele_no]);
    ace_comp_obj.set_comp_data_information("particle_prod_frame_flg");
    ace_comp_obj.comp_list_data(ace_data_obj.get_particle_prod_frame_flg()[i],
                                ace_data_obj_ref.get_particle_prod_frame_flg()[ele_no]);

    if( comp_pointer_flg == comp_pointer_mode )
    {
      ace_comp_obj.set_comp_data_information("particle_prod_distr_pointer");
      ace_comp_obj.comp_list_data_pointer(ace_data_obj.get_particle_prod_distr_pointer()[i],
                                          ace_data_obj_ref.get_particle_prod_distr_pointer()[ele_no]);
    }

    j_max = static_cast<int>(ace_data_obj_ref.get_particle_prod_reaction_type_all()[ele_no].size());
    for(int j=0; j<j_max; j++)
    {
      ace_comp_obj.set_comp_data_position(i+1, j+1);
      ace_comp_obj.set_comp_data_information("particle_prod_file_no");
      ace_comp_obj.comp_int_data(ace_data_obj.get_particle_prod_file_no()[i][j],
                                 ace_data_obj_ref.get_particle_prod_file_no()[ele_no][j]);
      ace_comp_obj.set_comp_data_information("particle_prod_reaction_type");
      ace_comp_obj.comp_int_data(ace_data_obj.get_particle_prod_reaction_type()[i][j],
                                 ace_data_obj_ref.get_particle_prod_reaction_type()[ele_no][j]);

      ace_comp_obj.set_comp_data_information("size of particle_prod_distr_ene_data[i]");
      ace_comp_obj.comp_int_data(ace_data_obj.get_particle_prod_distr_ene_data()[i].size(),
                                 ace_data_obj_ref.get_particle_prod_distr_ene_data()[ele_no].size() );
      if( static_cast<int>(ace_data_obj.get_particle_prod_distr_ene_data()[i].size()) <= j+1 )
      {
        continue;
      }
      ace_comp_obj.set_comp_data_information
      ("particle_prod_distr_range_data, particle_prod_distr_int_data, particle_prod_distr_ene_data, particle_prod_distr_data");
      ace_comp_obj.comp_table_data(ace_data_obj.get_particle_prod_distr_range_data()[i][j],
                                   ace_data_obj.get_particle_prod_distr_int_data()[i][j],
                                   ace_data_obj.get_particle_prod_distr_ene_data()[i][j],
                                   ace_data_obj.get_particle_prod_distr_data()[i][j],
                                   ace_data_obj_ref.get_particle_prod_distr_range_data()[ele_no][j],
                                   ace_data_obj_ref.get_particle_prod_distr_int_data()[ele_no][j],
                                   ace_data_obj_ref.get_particle_prod_distr_ene_data()[ele_no][j],
                                   ace_data_obj_ref.get_particle_prod_distr_data()[ele_no][j]);
    }

    ace_comp_obj.set_comp_data_position(i+1);

    if( comp_pointer_flg == comp_pointer_mode )
    {
      ace_comp_obj.set_comp_data_information("particle_prod_angular_pointer");
      ace_comp_obj.comp_list_data_pointer(ace_data_obj.get_particle_prod_angular_pointer()[i],
                                          ace_data_obj_ref.get_particle_prod_angular_pointer()[ele_no]);
    }

    ace_comp_obj.set_comp_data_information("size of particle_prod_angular_ene_data[i]");
    ace_comp_obj.comp_int_data(ace_data_obj.get_particle_prod_angular_ene_data()[i].size(),
                               ace_data_obj_ref.get_particle_prod_angular_ene_data()[ele_no].size() );
    for(int j=0; j<j_max; j++)
    {
      if( static_cast<int>(ace_data_obj.get_particle_prod_angular_ene_data()[i].size()) <= j+1 )
      {
        continue;
      }

      ace_comp_obj.set_comp_data_position(i+1, j+1);
      ace_comp_obj.set_comp_data_information("particle_prod_angular_ene_data");
      ace_comp_obj.comp_list_data(ace_data_obj.get_particle_prod_angular_ene_data()[i][j],
                                  ace_data_obj_ref.get_particle_prod_angular_ene_data()[ele_no][j]);

      if( comp_pointer_flg == comp_pointer_mode )
      {
        ace_comp_obj.set_comp_data_information("particle_prod_angular_ene_pointer");
        ace_comp_obj.comp_list_data_pointer
          (ace_data_obj.get_particle_prod_angular_ene_pointer()[i][j],
           ace_data_obj_ref.get_particle_prod_angular_ene_pointer()[ele_no][j]);
      }

      int k_max = static_cast<int>(ace_data_obj_ref.get_particle_prod_angular_ene_data()[ele_no][j].size());
      for(int k=0; k<k_max; k++)
      {
        ace_comp_obj.set_comp_data_position(i+1, j+1, k+1);
        ace_comp_obj.set_comp_data_information
        ("particle_prod_angular_int_data, particle_prod_angular_cos_data, particle_prod_angular_distr_data, particle_prod_angular_distr_data_integ");
        ace_comp_obj.comp_table_data
          (ace_data_obj.get_particle_prod_angular_int_data()[i][j][k],
           ace_data_obj.get_particle_prod_angular_cos_data()[i][j][k],
           ace_data_obj.get_particle_prod_angular_distr_data()[i][j][k],
           ace_data_obj.get_particle_prod_angular_distr_data_integ()[i][j][k],
           ace_data_obj_ref.get_particle_prod_angular_int_data()[ele_no][j][k],
           ace_data_obj_ref.get_particle_prod_angular_cos_data()[ele_no][j][k],
           ace_data_obj_ref.get_particle_prod_angular_distr_data()[ele_no][j][k],
           ace_data_obj_ref.get_particle_prod_angular_distr_data_integ()[ele_no][j][k]);
      }
    }

    ace_comp_obj.set_comp_data_position(i+1);

    if( comp_pointer_flg == comp_pointer_mode )
    {
      ace_comp_obj.set_comp_data_information("particle_prod_ene_pointer");
      ace_comp_obj.comp_list_data_pointer(ace_data_obj.get_particle_prod_ene_pointer()[i],
                                          ace_data_obj_ref.get_particle_prod_ene_pointer()[ele_no]);
    }

    ace_comp_obj.set_comp_data_information("size of particle_prod_ene_data[i]");
    ace_comp_obj.comp_int_data(ace_data_obj.get_particle_prod_ene_data()[i].size(),
                               ace_data_obj_ref.get_particle_prod_ene_data()[ele_no].size() );
    for(int j=0; j<j_max; j++)
    {
      if( static_cast<int>(ace_data_obj.get_particle_prod_ene_data()[i].size()) <= j+1 )
      {
        continue;
      }

      ace_comp_obj.set_comp_data_position(i+1, j+1);
      ace_comp_obj.set_comp_data_information("size of particle_prod_ene_data");
      ace_comp_obj.comp_int_data
        (static_cast<int>(ace_data_obj.get_particle_prod_ene_data()[i][j].size()),
         static_cast<int>(ace_data_obj_ref.get_particle_prod_ene_data()[ele_no][j].size()));
      if( static_cast<int>(ace_data_obj_ref.get_particle_prod_ene_data()[ele_no][j].size()) == 0 )
      {
        continue;
      }

      ace_comp_obj.set_comp_data_information("particle_prod_ene_flg");
      ace_comp_obj.comp_int_data(ace_data_obj.get_particle_prod_ene_flg()[i][j],
                                 ace_data_obj_ref.get_particle_prod_ene_flg()[ele_no][j]);

      if( comp_pointer_flg == comp_pointer_mode )
      {
        ace_comp_obj.set_comp_data_information("particle_prod_ene_in_pointer");
        ace_comp_obj.comp_int_data(ace_data_obj.get_particle_prod_ene_in_pointer()[i][j],
                                   ace_data_obj_ref.get_particle_prod_ene_in_pointer()[ele_no][j]);
      }


      int skip_flg = 0;
      int k_max = static_cast<int>(ace_data_obj_ref.get_particle_prod_ene_data()[ele_no][j].size());
      if( k_max == 2 )
      {
        int ene_no = static_cast<int>(ace_data_obj_ref.get_union_ene_grid().size());
        Real ene_max = ace_data_obj_ref.get_union_ene_grid()[ene_no-1];

        if( fabs(ace_data_obj_ref.get_particle_prod_ene_prob_data()[ele_no][j][0] - ene_max) < min_ene_dif &&
            fabs(ace_data_obj_ref.get_particle_prod_ene_data()[ele_no][j][1]      - ene_max) > min_ene_dif )
        {
          skip_flg = 1;
        }
      }

      if( skip_flg == 0 )
      {
        ace_comp_obj.set_comp_data_information
        ("particle_prod_ene_range_data, particle_prod_ene_int_data, particle_prod_ene_data, particle_prod_ene_prob_data");
        ace_comp_obj.comp_table_data(ace_data_obj.get_particle_prod_ene_range_data()[i][j],
                                     ace_data_obj.get_particle_prod_ene_int_data()[i][j],
                                     ace_data_obj.get_particle_prod_ene_data()[i][j],
                                     ace_data_obj.get_particle_prod_ene_prob_data()[i][j],
                                     ace_data_obj_ref.get_particle_prod_ene_range_data()[ele_no][j],
                                     ace_data_obj_ref.get_particle_prod_ene_int_data()[ele_no][j],
                                     ace_data_obj_ref.get_particle_prod_ene_data()[ele_no][j],
                                     ace_data_obj_ref.get_particle_prod_ene_prob_data()[ele_no][j]);
      }
      else
      {
        cout << endl;
        cout << "Position : " << i+1 << " / " << i_max << ", " << j+1 << " / " << j_max << endl;
        cout << "The reference value of particle_prod_ene_data and particle_prod_ene_prob_data ";
        cout << "may not be appropriate." << endl;
        cout << "The comparing scheme is skipped." << endl << endl;
      }

      if( ace_data_obj_ref.get_particle_prod_ene_flg()[ele_no][j] ==  4 ||
          ace_data_obj_ref.get_particle_prod_ene_flg()[ele_no][j] == 44 ||
          ace_data_obj_ref.get_particle_prod_ene_flg()[ele_no][j] == 61)
      {
        ace_comp_obj.set_comp_data_information
        ("particle_prod_ene_in_range_data, particle_prod_ene_in_int_data");
        ace_comp_obj.comp_interpolation_data
          (ace_data_obj.get_particle_prod_ene_in_range_data()[i][j],
           ace_data_obj.get_particle_prod_ene_in_int_data()[i][j],
           ace_data_obj_ref.get_particle_prod_ene_in_range_data()[ele_no][j],
           ace_data_obj_ref.get_particle_prod_ene_in_int_data()[ele_no][j]);

        ace_comp_obj.set_comp_data_information("particle_prod_ene_in_data");
        ace_comp_obj.comp_list_data(ace_data_obj.get_particle_prod_ene_in_data()[i][j],
                                    ace_data_obj_ref.get_particle_prod_ene_in_data()[ele_no][j]);

        if( comp_pointer_flg == comp_pointer_mode )
        {
          ace_comp_obj.set_comp_data_information("particle_prod_a_pointer");
          ace_comp_obj.comp_list_data_pointer(ace_data_obj.get_particle_prod_a_pointer()[i][j],
                                              ace_data_obj_ref.get_particle_prod_a_pointer()[ele_no][j]);
        }

        int k_max = static_cast<int>(ace_data_obj_ref.get_particle_prod_ene_in_data()[ele_no][j].size());
        for(int k=0; k<k_max; k++)
        {
          ace_comp_obj.set_comp_data_position(i+1, j+1, k+1);
          ace_comp_obj.set_comp_data_information
          ("particle_prod_a_int_data, particle_prod_a_data, particle_prod_a_distr_data, particle_prod_a_distr_data_integ");
          ace_comp_obj.comp_table_data(ace_data_obj.get_particle_prod_a_int_data()[i][j][k],
                                       ace_data_obj.get_particle_prod_a_data()[i][j][k],
                                       ace_data_obj.get_particle_prod_a_distr_data()[i][j][k],
                                       ace_data_obj.get_particle_prod_a_distr_data_integ()[i][j][k],
                                       ace_data_obj_ref.get_particle_prod_a_int_data()[ele_no][j][k],
                                       ace_data_obj_ref.get_particle_prod_a_data()[ele_no][j][k],
                                       ace_data_obj_ref.get_particle_prod_a_distr_data()[ele_no][j][k],
                                       ace_data_obj_ref.get_particle_prod_a_distr_data_integ()[ele_no][j][k]);

          if( ace_data_obj_ref.get_particle_prod_ene_flg()[ele_no][j] == 44 )
          {
            ace_comp_obj.set_comp_data_information("particle_prod_ene_out_coef_a");
            ace_comp_obj.comp_list_data(ace_data_obj.get_particle_prod_ene_out_coef_a()[i][j][k],
                                        ace_data_obj_ref.get_particle_prod_ene_out_coef_a()[ele_no][j][k]);
            ace_comp_obj.set_comp_data_information("particle_prod_ene_out_coef_b");
            ace_comp_obj.comp_list_data(ace_data_obj.get_particle_prod_ene_out_coef_b()[i][j][k],
                                        ace_data_obj_ref.get_particle_prod_ene_out_coef_b()[ele_no][j][k]);
          }
          else if( ace_data_obj_ref.get_particle_prod_ene_flg()[ele_no][j] == 61 )
          {
            if( comp_pointer_flg == comp_pointer_mode )
            {
              ace_comp_obj.set_comp_data_information("particle_prod_b_pointer");
              ace_comp_obj.comp_list_data_pointer
               (ace_data_obj.get_particle_prod_b_pointer()[i][j][k],
                ace_data_obj_ref.get_particle_prod_b_pointer()[ele_no][j][k]);
            }

            int l_max = static_cast<int>(ace_data_obj_ref.get_particle_prod_a_data()[ele_no][j][k].size());
            for(int l=0; l<l_max; l++)
            {
              ace_comp_obj.set_comp_data_position(i+1, j+1, k+1, l+1);
              ace_comp_obj.set_comp_data_information
              ("particle_prod_b_int_data, particle_prod_b_data, particle_prod_b_prob_data, particle_prod_b_prob_data_integ");
              if( l==0 )
              {
                ace_comp_obj.comp_table_data
                  (ace_data_obj.get_particle_prod_b_int_data()[i][j][k][l],
                   ace_data_obj.get_particle_prod_b_data()[i][j][k][l],
                   ace_data_obj.get_particle_prod_b_prob_data()[i][j][k][l],
                   ace_data_obj.get_particle_prod_b_prob_data_integ()[i][j][k][l],
                   ace_data_obj_ref.get_particle_prod_b_int_data()[ele_no][j][k][l],
                   ace_data_obj_ref.get_particle_prod_b_data()[ele_no][j][k][l],
                   ace_data_obj_ref.get_particle_prod_b_prob_data()[ele_no][j][k][l],
                   ace_data_obj_ref.get_particle_prod_b_prob_data_integ()[ele_no][j][k][l]);
              }
              else if( particle_prod_b_prob_data_check == 0 )
              {
                particle_prod_b_prob_data_check = 1;

                int m_max = static_cast<int>
                              (ace_data_obj_ref.get_particle_prod_b_prob_data()[ele_no][j][k][l].size());
                for(int m=0; m<m_max; m++)
                {
                  Real comp_val = ace_data_obj.get_particle_prod_b_prob_data()[ele_no][j][k][l][m];
                  Real ref_val  = ace_data_obj_ref.get_particle_prod_b_prob_data()[ele_no][j][k][l][m];

                  Real dif_val = ace_comp_obj.get_tolerance_val() * fabs(ref_val);
                  if( dif_val < min_value )
                  {
                    dif_val = min_value;
                  }

                  if( fabs(comp_val - ref_val) > dif_val )
                  {
                    particle_prod_b_prob_data_check = 1;
                    cout << "Position : " << i+1 << ", " << j+1 << ", " << k+1 << ", " << l+1 << ", "
                                          << m+1 << endl;
                    cout << "particle_prod_b_prob_data are not identical." << endl;
                    cout << "Comparison value : " << comp_val << endl;
                    cout << "Reference  value : " << ref_val  << endl;
                    cout << endl;
                    cout << "If you compare the NJOY result, this difference is not problem." << endl;
                    cout << "NJOY has not renewal the 4-th loop (identical cont_data is used)." << endl;
                    cout << endl;
                    cout << "The comparing scheme is skipped." << endl << endl;
                  }
                }
              }
            }
          }
        }
      }
      else if( ace_data_obj_ref.get_particle_prod_ene_flg()[ele_no][j] == 33 )
      {
        ace_comp_obj.set_comp_data_information("particle_prod_q_value");
        ace_comp_obj.comp_real_data(ace_data_obj.get_particle_prod_q_value()[i][j],
                                    ace_data_obj_ref.get_particle_prod_q_value()[ele_no][j]);
        ace_comp_obj.set_comp_data_information("particle_prod_mass_coef");
        ace_comp_obj.comp_real_data(ace_data_obj.get_particle_prod_mass_coef()[i][j],
                                    ace_data_obj_ref.get_particle_prod_mass_coef()[ele_no][j]);
      }
      else if( ace_data_obj_ref.get_particle_prod_ene_flg()[ele_no][j] == 66 )
      {
        ace_comp_obj.set_comp_data_information("particle_prod_q_value");
        ace_comp_obj.comp_real_data(ace_data_obj.get_particle_prod_q_value()[i][j],
                                    ace_data_obj_ref.get_particle_prod_q_value()[ele_no][j]);
        ace_comp_obj.set_comp_data_information("particle_prod_mass_coef");
        ace_comp_obj.comp_real_data(ace_data_obj.get_particle_prod_mass_coef()[i][j],
                                    ace_data_obj_ref.get_particle_prod_mass_coef()[ele_no][j]);

        ace_comp_obj.set_comp_data_information
        ("particle_prod_a_int_data, particle_prod_a_data, particle_prod_a_distr_data, particle_prod_a_distr_data_integ");
        ace_comp_obj.comp_table_data(ace_data_obj.get_particle_prod_a_int_data()[i][j][0],
                                     ace_data_obj.get_particle_prod_a_data()[i][j][0],
                                     ace_data_obj.get_particle_prod_a_distr_data()[i][j][0],
                                     ace_data_obj.get_particle_prod_a_distr_data_integ()[i][j][0],
                                     ace_data_obj_ref.get_particle_prod_a_int_data()[ele_no][j][0],
                                     ace_data_obj_ref.get_particle_prod_a_data()[ele_no][j][0],
                                     ace_data_obj_ref.get_particle_prod_a_distr_data()[ele_no][j][0],
                                     ace_data_obj_ref.get_particle_prod_a_distr_data_integ()[ele_no][j][0]);
      }
      else if( ace_data_obj_ref.get_particle_prod_ene_flg()[ele_no][j] == 67 )
      {
        int k_max = static_cast<int>(ace_data_obj_ref.get_particle_prod_a_int_data()[ele_no][j].size());
        ace_comp_obj.set_comp_data_information("size of particle_prod_a_int_data");
        ace_comp_obj.comp_int_data
          (static_cast<int>(ace_data_obj.get_particle_prod_a_int_data()[i][j].size()), k_max);
        for(int k=0; k<k_max; k++)
        {
          ace_comp_obj.set_comp_data_position(i+1, j+1, k+1);
          ace_comp_obj.set_comp_data_information("particle_prod_a_int_data");
          ace_comp_obj.comp_int_data(ace_data_obj.get_particle_prod_a_int_data()[i][j][k],
                                     ace_data_obj_ref.get_particle_prod_a_int_data()[ele_no][j][k]);
          ace_comp_obj.set_comp_data_information("particle_prod_a_data");
          ace_comp_obj.comp_list_data(ace_data_obj.get_particle_prod_a_data()[i][j][k],
                                      ace_data_obj_ref.get_particle_prod_a_data()[ele_no][j][k]);

          int l_max = static_cast<int>(ace_data_obj_ref.get_particle_prod_a_data()[ele_no][j][k].size());
          for(int l=0; l<l_max; l++)
          {
            ace_comp_obj.set_comp_data_position(i+1, j+1, k+1, l+1);
            ace_comp_obj.set_comp_data_information
            ("particle_prod_b_int_data, particle_prod_b_data, particle_prod_b_prob_data, particle_prod_b_prob_data_integ");
            ace_comp_obj.comp_table_data
              (ace_data_obj.get_particle_prod_b_int_data()[i][j][k][l],
               ace_data_obj.get_particle_prod_b_data()[i][j][k][l],
               ace_data_obj.get_particle_prod_b_prob_data()[i][j][k][l],
               ace_data_obj.get_particle_prod_b_prob_data_integ()[i][j][k][l],
               ace_data_obj_ref.get_particle_prod_b_int_data()[ele_no][j][k][l],
               ace_data_obj_ref.get_particle_prod_b_data()[ele_no][j][k][l],
               ace_data_obj_ref.get_particle_prod_b_prob_data()[ele_no][j][k][l],
               ace_data_obj_ref.get_particle_prod_b_prob_data_integ()[ele_no][j][k][l]);
          }
        }
      }
    }

    ace_comp_obj.set_comp_data_position(i+1);
    ace_comp_obj.set_comp_data_information("particle_prod_reaction_type");
    ace_comp_obj.comp_list_data(ace_data_obj.get_particle_prod_reaction_type()[i],
                                ace_data_obj_ref.get_particle_prod_reaction_type()[ele_no]);

    ele_no++;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

FastAceDataObject FastAceDataCompare::parse_ace_data_file(string& file_name)
{
  //Read ACE format
  FastAceDataParser parse_obj;
  parse_obj.set_file_name(file_name);
  parse_obj.parse_ace_format();

  //Copy ACE data object and clear read ace format class
  return parse_obj.get_ace_data_obj();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//Setter

void FastAceDataCompare::set_ace_data_obj(FastAceDataObject& ace_obj, FastAceDataObject& ace_obj_ref)
{
  ace_file_name.clear();
  ace_file_name_ref.clear();

  ace_data_obj     = ace_obj;
  ace_data_obj_ref = ace_obj_ref;
}

void FastAceDataCompare::set_ace_file_name(string ace_name, string ace_name_ref)
{
  cout << "Read reference data : " << ace_name_ref << endl;
  boost::timer::cpu_timer timer_read_ref;
  ace_file_name_ref = ace_name_ref;
  ace_data_obj_ref  = parse_ace_data_file(ace_file_name_ref);
  time_read_ref     = static_cast<Real>(timer_read_ref.elapsed().wall * 1.0E-9);

  cout << "Read comparing data : " << ace_name << endl;
  boost::timer::cpu_timer timer_read;
  ace_file_name     = ace_name;
  ace_data_obj      = parse_ace_data_file(ace_file_name);
  time_read         = static_cast<Real>(timer_read.elapsed().wall * 1.0E-9);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//Getter

FastAceDataObject FastAceDataCompare::get_ace_data_obj()
{
  return ace_data_obj;
}

FastAceDataObject FastAceDataCompare::get_ace_data_obj_ref()
{
  return ace_data_obj_ref;
}

string  FastAceDataCompare::get_ace_file_name()
{
  return ace_file_name;
}

string  FastAceDataCompare::get_ace_file_name_ref()
{
  return ace_file_name_ref;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataCompare::set_tolerance_val_def()
{
  ace_comp_obj.set_tolerance_val_def();
}

void FastAceDataCompare::set_tolerance_val(Real tolerance_val)
{
  ace_comp_obj.set_tolerance_val(tolerance_val);
}

Real FastAceDataCompare::get_tolerance_val()
{
  return ace_comp_obj.get_tolerance_val();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataCompare::set_comp_pointer_flg(int comp_flg)
{
  if( comp_flg != comp_pointer_mode && comp_flg != no_comp_pointer_mode )
  {
    func_name  = "set_comp_pointer_flg(int comp_flg)";

    ostringstream oss01;
    oss01 << comp_flg;
    string str_data01 = "comp_flg : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("The available comp_flg is only 0 (comp_pointer_mode) or 1 (no_comp_pointer_mode).");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  comp_pointer_flg = comp_flg;
}

int FastAceDataCompare::get_comp_pointer_flg()
{
  return comp_pointer_flg;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void FastAceDataCompare::set_skip_prob_table_flg(int skip_flg)
{
  if( skip_flg != no_skip_prob_table && skip_flg != skip_prob_table )
  {
    func_name  = "set_skip_prob_table_flg(int skip_flg)";

    ostringstream oss01;
    oss01 << skip_flg;
    string str_data01 = "skip_flg : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("The available skip_flg is only 0 (no_skip_prob_table) or 1 (skip_prob_table).");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  skip_prob_table_flg = skip_flg;
}

int FastAceDataCompare::get_skip_prob_table_flg()
{
  return skip_prob_table_flg;
}
