#include "ContinuousEnergyXSUtils/AceDataGenerator/DosimetryAceDataGenerator.hpp"

using namespace frendy;

//constructor
DosimetryAceDataGenerator::DosimetryAceDataGenerator(void)
{
  clear();
}

//destructor
DosimetryAceDataGenerator::~DosimetryAceDataGenerator(void)
{
  clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DosimetryAceDataGenerator::clear()
{
  clear_calc_data();
  clear_ace_data();

  gen_dosimetry_data_flg = 0;
  nucl_data_set_flg      = 0;
  mat_set_flg            = 0;
  temp_set_flg           = 0;

  nucl_data_obj.clear();

  mat            = 0;
  temp           = 0.0;

  suffix_za_id   = 0.0;

  mcnpx_mode_flg = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DosimetryAceDataGenerator::clear_calc_data()
{
  clr_obj.clear_vec_array1_str(title_data);

  reaction_type_list.clear();
  zi_vec.clear();
  awr_vec.clear();

  vector<CrossSectionDataContainer>().swap(xs_data_obj);
  vector<RadioactiveProductDataContainer>().swap(radio_product_data_obj);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DosimetryAceDataGenerator::clear_ace_data()
{
  aw0 = 0.0;
  tz  = 0.0;
  clr_obj.clear_vec_array1_str(title_data);

  discriptive_data.clear();

  reaction_xs_reaction_type.clear();
  reaction_xs_pointer.clear();
  clr_obj.clear_vec_array2_int(reaction_xs_range_data);
  clr_obj.clear_vec_array2_int(reaction_xs_int_data);
  clr_obj.clear_vec_array2_real(reaction_xs_ene_data);
  clr_obj.clear_vec_array2_real(reaction_xs_data);

  clr_obj.clear_vec_array2_int(production_xs_state_no_product);
  clr_obj.clear_vec_array2_int(production_xs_pointer);
  clr_obj.clear_vec_array3_int(production_xs_range_data);
  clr_obj.clear_vec_array3_int(production_xs_int_data);
  clr_obj.clear_vec_array3_real(production_xs_ene_data);
  clr_obj.clear_vec_array3_real(production_xs_data);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DosimetryAceDataGenerator::copy_dosimetry_ace_data(DosimetryAceDataObject& ace_data_obj)
{
  ace_data_obj.clear();

  ace_data_obj.set_mcnpx_mode_flg(mcnpx_mode_flg);
  
  ace_data_obj.set_aw0(aw0);
  ace_data_obj.set_tz(tz);
  ace_data_obj.set_title_data(title_data);
  ace_data_obj.set_discriptive_data(discriptive_data);

  ace_data_obj.set_zi_vec(zi_vec);
  ace_data_obj.set_awr_vec(awr_vec);

  ace_data_obj.set_reaction_xs_reaction_type(reaction_xs_reaction_type);
  ace_data_obj.set_reaction_xs_pointer(reaction_xs_pointer);
  ace_data_obj.set_reaction_xs_range_data(reaction_xs_range_data);
  ace_data_obj.set_reaction_xs_int_data(reaction_xs_int_data);
  ace_data_obj.set_reaction_xs_ene_data(reaction_xs_ene_data);
  ace_data_obj.set_reaction_xs_data(reaction_xs_data);

  ace_data_obj.set_production_xs_state_no_product(production_xs_state_no_product);
  ace_data_obj.set_production_xs_pointer(production_xs_pointer);
  ace_data_obj.set_production_xs_range_data(production_xs_range_data);
  ace_data_obj.set_production_xs_int_data(production_xs_int_data);
  ace_data_obj.set_production_xs_ene_data(production_xs_ene_data);
  ace_data_obj.set_production_xs_data(production_xs_data);

  ace_data_obj.set_len2(len2);
  ace_data_obj.set_za(za);
  ace_data_obj.set_ntr(ntr);
  ace_data_obj.set_lone(lone);
  ace_data_obj.set_mtr(mtr);
  ace_data_obj.set_lsig(lsig);
  ace_data_obj.set_sigd(sigd);
  ace_data_obj.set_end(end);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DosimetryAceDataGenerator::generate_ace_data()
{
  if( gen_dosimetry_data_flg != 0 )
  {
    return;
  }
  gen_dosimetry_data_flg = 1;

  za  = nucl_data_obj.get_general_data_obj().get_izaid_ace();
  aw0 = nucl_data_obj.get_general_data_obj().get_mass();
  tz  = nucl_data_obj.get_general_data_obj().get_temp() * boltzmann_const * unit_micro;

  clear_calc_data();
  check_set_data();

  NuclearReactionDataContainer nucl_reaction_data_obj;
  nucl_reaction_data_obj = nucl_data_obj.get_nucl_reaction_data_obj();
  xs_data_obj            = nucl_reaction_data_obj.get_xs_data_obj();
  radio_product_data_obj = nucl_reaction_data_obj.get_radio_product_data_obj();
  reaction_type_list     = nucl_reaction_data_obj.get_reaction_type();
  nucl_reaction_data_obj.clear();

  //Check the interpolation scheme
  //(linear-linear is only available for the interpolation type)
  check_xs_data_obj();

  modify_radio_product_data_obj();

  generate_ace_data_xs();

  modify_calc_data();
  calc_ace_header_file_data();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void DosimetryAceDataGenerator::check_xs_data_obj()
{
  int i_max = static_cast<int>(reaction_type_list.size());
  for(int i=0; i<i_max; i++)
  {
    if( xs_data_obj[i].get_reaction_type() == reaction_type_list[i] )
    {
      vector<Integer> xs_range_data = xs_data_obj[i].get_xs_range_data();
      vector<Integer> xs_int_data   = xs_data_obj[i].get_xs_int_data();

      int j_max = static_cast<int>(xs_int_data.size());
      for(int j=0; j<j_max; j++)
      {
        if( xs_int_data[j] != int_lin_lin )
        {
          string class_name = "DosimetryAceDataGenerator";
          string func_name  = "check_xs_data_obj()";

          string        str_data01, str_data02;
          ostringstream oss01, oss02, oss03, oss04, oss05, oss06;
          oss01 << i+1;
          oss02 << i_max;
          oss03 << reaction_type_list[i];
          oss04 << j+1;
          oss05 << j_max;
          oss06 << xs_int_data[j];
          str_data01 = "Reaction type      (" + oss01.str() + " / " + oss02.str() + ") : " + oss03.str();
          str_data02 = "Interpolation type (" + oss04.str() + " / " + oss05.str() + ") : " + oss06.str();

          vector<string> err_com;
          err_com.push_back(str_data01);
          err_com.push_back(str_data02);
          err_com.push_back("linear-linear (=2) interpolation is only available for this program.");
          err_com.push_back("Please check nuclear data or linearize before running this program.");
          err_obj.output_runtime_error(class_name, func_name, err_com);
        }
      }

      xs_range_data.clear();
      xs_int_data.clear();
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void DosimetryAceDataGenerator::modify_radio_product_data_obj()
{
  //Change Multipicities for Production of Radioactive Nuclides (MF=9)
  //to Cross Sections for Production of Radioactive Nucliedes (MF=10)
  calc_radio_product_xs_by_multiplicity();


  //Modify radio product cross section when cross section data is
  //stored in MT=5 (Z, anything) to each MT (MT=22-116);
  //to Cross Sections for Production of Radioactive Nucliedes (MF=10)
  devide_radio_product_xs_by_product_nucleus();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void DosimetryAceDataGenerator::calc_radio_product_xs_by_multiplicity()
{
  int i_max = static_cast<int>(reaction_type_list.size());
  for(int i=0; i<i_max; i++)
  {
    if( radio_product_data_obj[i].get_reaction_type() == reaction_type_list[i] )
    {
      if( static_cast<int>(radio_product_data_obj[i].get_multiplicity_data().size()) > 0 )
      {
        //Check nuclear data
        if( static_cast<int>(radio_product_data_obj[i].get_xs_data().size()) > 0 )
        {
          continue;
        }

        if( xs_data_obj[i].get_reaction_type() != reaction_type_list[i] )
        {
          string class_name = "DosimetryAceDataGenerator";
          string func_name  = "calc_radio_product_xs_by_multiplicity()";

          string        str_data;
          ostringstream oss01, oss02, oss03;
          oss01 << i+1;
          oss02 << i_max;
          oss03 << reaction_type_list[i];
          str_data = "Reaction type (" + oss01.str() + " / " + oss02.str() + ") : " + oss03.str();

          vector<string> err_com;
          err_com.push_back(str_data);

          err_com.push_back("Though this nuclear data has multiplicities data, cross section data");
          err_com.push_back("does not containe.");
          err_com.push_back("FRENDY can not calculate xs for radioactive nuclide using multiplicities");
          err_com.push_back("data and cross section data.");
          err_com.push_back("This nuclear data may not be appropriate.");
          err_com.push_back("Please check the nuclear data.");
          err_obj.output_runtime_error(class_name, func_name, err_com);
        }

        calc_radio_xs(i);
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void DosimetryAceDataGenerator::calc_radio_xs(int i)
{
  vector<Real> xs_ene_data = xs_data_obj[i].get_xs_ene_data();
  vector<Real> xs_data     = xs_data_obj[i].get_xs_data();

  vector<vector<Integer> > multi_range_data, multi_int_data, radio_xs_range_data, radio_xs_int_data;
  vector<vector<Real> >    multi_ene_data,   multi_data,     radio_xs_ene_data,   radio_xs_data;
  multi_range_data = radio_product_data_obj[i].get_multiplicity_range_data();
  multi_int_data   = radio_product_data_obj[i].get_multiplicity_int_data();
  multi_ene_data   = radio_product_data_obj[i].get_multiplicity_ene_data();
  multi_data       = radio_product_data_obj[i].get_multiplicity_data();

  int j_max = static_cast<int>(multi_data.size());
  int k_max = static_cast<int>(xs_data.size());
  radio_xs_range_data.resize(j_max);
  radio_xs_int_data.resize(j_max);
  radio_xs_ene_data.resize(j_max);
  radio_xs_data.resize(j_max);
  for(int j=0; j<j_max; j++)
  {
    int non_zero_flg = 0;
    for(int k=0; k<k_max; k++)
    {
      Real xs_val = xs_calc_obj.calc_xs_data(xs_ene_data[k], xs_data[k],
                                             multi_range_data[j],  multi_int_data[j],
                                             multi_ene_data[j],    multi_data[j]);

      if( non_zero_flg == 0 )
      {
        if( xs_val > min_sig_val )
        {
          non_zero_flg = 1;
          if( k > 0 )
          {
            radio_xs_ene_data[j].push_back(xs_ene_data[k-1]);
            radio_xs_data[j].push_back(0.0);
          }
          radio_xs_ene_data[j].push_back(xs_ene_data[k]);
          radio_xs_data[j].push_back(xs_val);
        }
      }
      else
      {
        radio_xs_ene_data[j].push_back(xs_ene_data[k]);
        radio_xs_data[j].push_back(xs_val);
      }
    }

    radio_xs_range_data[j].resize(1);
    radio_xs_int_data[j].resize(1);
    radio_xs_range_data[j][0] = static_cast<Integer>(radio_xs_ene_data[j].size());
    radio_xs_int_data[j][0]   = int_lin_lin;

    ta_obj.remove_zero_data(radio_xs_range_data[j], radio_xs_int_data[j],
                            radio_xs_ene_data[j], radio_xs_data[j]);
  }
  xs_ene_data.clear();
  xs_data.clear();

  radio_product_data_obj[i].set_xs_state_no_target
                             (radio_product_data_obj[i].get_multiplicity_state_no_target());
  radio_product_data_obj[i].set_xs_state_no_product
                             (radio_product_data_obj[i].get_multiplicity_state_no_product());
  radio_product_data_obj[i].set_xs_q_value_mass
                             (radio_product_data_obj[i].get_multiplicity_q_value_mass());
  radio_product_data_obj[i].set_xs_q_value
                             (radio_product_data_obj[i].get_multiplicity_q_value());
  radio_product_data_obj[i].set_xs_mat_data_product
                             (radio_product_data_obj[i].get_multiplicity_mat_data_product());

  radio_product_data_obj[i].set_xs_range_data(radio_xs_range_data);
  radio_product_data_obj[i].set_xs_int_data(radio_xs_int_data);
  radio_product_data_obj[i].set_xs_ene_data(radio_xs_ene_data);
  radio_product_data_obj[i].set_xs_data(radio_xs_data);
  clr_obj.clear_vec_array2_int(radio_xs_range_data);
  clr_obj.clear_vec_array2_int(radio_xs_int_data);
  clr_obj.clear_vec_array2_real(radio_xs_ene_data);
  clr_obj.clear_vec_array2_real(radio_xs_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void DosimetryAceDataGenerator::devide_radio_product_xs_by_product_nucleus()
{
  int i_max = static_cast<int>(radio_product_data_obj.size());
  for(int i=0; i<i_max; i++)
  {
    Integer react_val = radio_product_data_obj[i].get_reaction_type();
    if( react_val != unassigned_mt_no )
    {
      if( check_product_nucleus(radio_product_data_obj[i].get_xs_mat_data_product()) > 0 )
      {
        if( react_val == 5 || (react_val >= 201 && react_val <= 207) )
        {
          devide_radio_product_xs(i);
        }
        else
        {
          string class_name = "DosimetryAceDataGenerator";
          string func_name  = "devide_radio_product_xs_by_product_nucleus()";

          string        str_data01;
          ostringstream oss01, oss02, oss03;
          oss01 << i+1;
          oss02 << i_max;
          oss03 << react_val;
          str_data01 = "Reaction type (" + oss01.str() + " / " + oss02.str() + ") : " + oss03.str();

          vector<string> err_com;
          err_com.push_back(str_data01);
          err_com.push_back("This reaction type has multiple product nucleaus data.");
          err_com.push_back("This program can not treat such data.");
          err_com.push_back("Please check nuclear data.");
          err_obj.output_runtime_error(class_name, func_name, err_com);
        }
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int  DosimetryAceDataGenerator::check_product_nucleus(vector<Integer> mat_data_product_list)
{
  int check_flg = 0;

  int i_max = static_cast<int>(mat_data_product_list.size());
  for(int i=1; i<i_max; i++)
  {
    if( mat_data_product_list[i] != mat_data_product_list[0] )
    {
      check_flg = 1;
      break;
    }
  }

  return check_flg;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void DosimetryAceDataGenerator::devide_radio_product_xs(int i)
{
  //This function has not been implemented.
  //To identify reaction data, MF=6 data is required.
  //(If IZAP = 1002, we can not identify this reaction is (n, np) or (n, d).)

  string class_name = "DosimetryAceDataGenerator";
  string func_name  = "devide_radio_product_xs(int i)";

  string        str_data01;
  ostringstream oss01, oss02;
  oss01 << i+1;
  oss02 << radio_product_data_obj[i].get_reaction_type();
  str_data01 = "Reaction type @ " + oss01.str() + " : " + oss02.str();

  vector<string> err_com;
  err_com.push_back(str_data01);
  err_com.push_back("This reaction type has multiple product nucleaus data.");
  err_com.push_back("This program can not treat such data.");
  err_com.push_back("Modification of this function is required to appropriately");
  err_com.push_back("process this nuclear data");
  err_obj.output_caution(class_name, func_name, err_com);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void DosimetryAceDataGenerator::generate_ace_data_xs()
{
  int i_max = static_cast<int>(reaction_type_list.size());
  for(int i=0; i<i_max; i++)
  {
    if( reaction_type_list[i] == 1 )
    {
      continue;
    }

    if( xs_data_obj[i].get_reaction_type() == reaction_type_list[i] )
    {
      vector<Integer> range_vec = xs_data_obj[i].get_xs_range_data();
      vector<Integer> int_vec   = xs_data_obj[i].get_xs_int_data();
      vector<Real>    ene_vec   = xs_data_obj[i].get_xs_ene_data();
      vector<Real>    xs_vec    = xs_data_obj[i].get_xs_data();

      ta_obj.remove_zero_data(range_vec, int_vec, ene_vec, xs_vec);
      if( static_cast<int>(ene_vec.size()) <= 2 )
      {
        if( static_cast<int>(ene_vec.size()) == 0 )
        {
          continue;
        }
        else if( static_cast<int>(ene_vec.size()) == 1 && xs_vec[0] < min_value )
        {
          continue;
        }
        else if( static_cast<int>(ene_vec.size()) == 2 &&
                 xs_vec[0] < min_value && xs_vec[1] < min_value )
        {
          continue;
        }
      }

      reaction_xs_reaction_type.push_back(reaction_type_list[i]);
      reaction_xs_range_data.push_back(range_vec);
      reaction_xs_int_data.push_back(int_vec);
      reaction_xs_ene_data.push_back(ene_vec);
      reaction_xs_data.push_back(xs_vec);
      range_vec.clear();
      int_vec.clear();
      ene_vec.clear();
      xs_vec.clear();
    }

    if( radio_product_data_obj[i].get_reaction_type() == reaction_type_list[i] )
    {
      vector<Integer> xs_state_no_product = radio_product_data_obj[i].get_xs_state_no_product();
      vector<vector<Integer> > range_vec  = radio_product_data_obj[i].get_xs_range_data();
      vector<vector<Integer> > int_vec    = radio_product_data_obj[i].get_xs_int_data();
      vector<vector<Real> >    ene_vec    = radio_product_data_obj[i].get_xs_ene_data();
      vector<vector<Real> >    xs_vec     = radio_product_data_obj[i].get_xs_data();

      vector<Integer>          xs_state_no_product_mod;
      vector<vector<Integer> > range_vec_mod, int_vec_mod;
      vector<vector<Real> >    ene_vec_mod,   xs_vec_mod;

      int j_max = static_cast<int>(xs_state_no_product.size());
      for(int j=0; j<j_max; j++)
      {
        xs_state_no_product[j] = reaction_type_list[i] + 1000*(10 + xs_state_no_product[j]);

        ta_obj.remove_zero_data(range_vec[j], int_vec[j], ene_vec[j], xs_vec[j]);
        if( static_cast<int>(ene_vec[j].size()) <= 2 )
        {
          if( static_cast<int>(ene_vec[j].size()) == 0 )
          {
            continue;
          }
          else if( static_cast<int>(ene_vec[j].size()) == 1 && xs_vec[j][0] < min_value )
          {
            continue;
          }
          else if( static_cast<int>(ene_vec[j].size()) == 2 &&
                   xs_vec[j][0] < min_value && xs_vec[j][1] < min_value )
          {
            continue;
          }
        }

        xs_state_no_product_mod.push_back(xs_state_no_product[j]);
        range_vec_mod.push_back(range_vec[j]);
        int_vec_mod.push_back(int_vec[j]);
        ene_vec_mod.push_back(ene_vec[j]);
        xs_vec_mod.push_back(xs_vec[j]);
      }

      production_xs_state_no_product.push_back(xs_state_no_product_mod);
      production_xs_range_data.push_back(range_vec_mod);
      production_xs_int_data.push_back(int_vec_mod);
      production_xs_ene_data.push_back(ene_vec_mod);
      production_xs_data.push_back(xs_vec_mod);

      xs_state_no_product.clear();
      clr_obj.clear_vec_array2_int(range_vec);
      clr_obj.clear_vec_array2_int(int_vec);
      clr_obj.clear_vec_array2_real(ene_vec);
      clr_obj.clear_vec_array2_real(xs_vec);
      xs_state_no_product_mod.clear();
      clr_obj.clear_vec_array2_int(range_vec_mod);
      clr_obj.clear_vec_array2_int(int_vec_mod);
      clr_obj.clear_vec_array2_real(ene_vec_mod);
      clr_obj.clear_vec_array2_real(xs_vec_mod);
    }
  }

  //Modify unit of reaction_xs_ene_data from [eV] to [MeV]
  i_max = static_cast<int>(reaction_xs_ene_data.size());
  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(reaction_xs_ene_data[i].size());
    for(int j=0; j<j_max; j++)
    {
      reaction_xs_ene_data[i][j] *= unit_micro;
    }
  }

  //Modify unit of production_xs_ene_data from [eV] to [MeV]
  i_max = static_cast<int>(production_xs_ene_data.size());
  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(production_xs_ene_data[i].size());
    for(int j=0; j<j_max; j++)
    {
      int k_max = static_cast<int>(production_xs_ene_data[i][j].size());
      for(int k=0; k<k_max; k++)
      {
        production_xs_ene_data[i][j][k] *= unit_micro;
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void DosimetryAceDataGenerator::modify_calc_data()
{
  string        str_tmp;
  ostringstream oss01, oss02;
  title_data.resize(3);

  //Copy thermal_za_id_name and suffix_za_id
  if( mcnpx_mode_flg == 0 )
  {
    oss01.width(9);
    oss01.precision(2);
    oss01 << fixed << suffix_za_id + za;
    title_data[0] = oss01.str() + "y";
  }
  else
  {
    oss01.width(10);
    oss01.precision(3);
    oss01 << fixed << suffix_za_id + za;
    title_data[0] = oss01.str() + "ny";
  }

  //Copy date
  str_tmp       = time_obj.get_current_date_no_slash();
  title_data[1] = "  " + str_tmp;

  //Copy material data
  mat = nucl_data_obj.get_general_data_obj().get_mat_no();
  oss02 << setw(4) << setiosflags(ios::right) << mat;
  title_data[2] = "   mat" + oss02.str();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void DosimetryAceDataGenerator::calc_ace_header_file_data()
{
  ntr = static_cast<int>(reaction_xs_reaction_type.size());
  for(int i=0; i<static_cast<int>(production_xs_state_no_product.size()); i++)
  {
    ntr += static_cast<int>(production_xs_state_no_product[i].size());
  }

  lone = 1;
  mtr  = 1;
  lsig = mtr + ntr;
  sigd = mtr + 2*ntr;

  //Calculation of len2
  int pointer_no = 0;
  int i_max = static_cast<int>(reaction_xs_reaction_type.size());
  reaction_xs_pointer.resize(i_max);

  len2 = 2*i_max; //MT number + pointer
  for(int i=0; i<i_max; i++)
  {
    reaction_xs_pointer[i] = pointer_no + 1;

    int j_max = static_cast<int>(reaction_xs_int_data[i].size());
    if( j_max == 1 && reaction_xs_int_data[i][0] == int_lin_lin )
    {
      pointer_no += 1;
    }
    else
    {
      pointer_no += 2*j_max + 1;
    }

    j_max = static_cast<int>(reaction_xs_data[i].size());
    pointer_no += 2*j_max + 1;
  }

  i_max = static_cast<int>(production_xs_state_no_product.size());
  production_xs_pointer.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(production_xs_state_no_product[i].size());
    production_xs_pointer[i].resize(j_max);

    len2 += 2*j_max; //MT number + pointer
    for(int j=0; j<j_max; j++)
    {
      production_xs_pointer[i][j] = pointer_no + 1;

      int k_max = static_cast<int>(production_xs_int_data[i][j].size());
      if( k_max == 1 && production_xs_int_data[i][j][0] == int_lin_lin )
      {
        pointer_no += 1;
      }
      else
      {
        pointer_no += 2*k_max + 1;
      }

      k_max = static_cast<int>(production_xs_data[i][j].size());
      pointer_no += 2*k_max + 1;
    }
  }
  len2 += pointer_no;

  end = len2;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DosimetryAceDataGenerator::output_ace_data()
{
  output_ace_data_title();
  
  output_ace_data_reaction_xs();

  output_ace_data_production_xs();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DosimetryAceDataGenerator::output_ace_data_title()
{
  calc_ace_header_file_data();

  cout << setiosflags(ios::right);
  cout << "1" << endl << endl << endl << endl << endl << endl << endl;
  cout << "      ***********************          awr" << setw(10) << aw0   << endl;
  cout << "      *                     *         temp" << setw(10)
                                                       << setiosflags(ios::scientific)
                                                       << tz << endl
                                                       << resetiosflags(ios::scientific);
  cout << "      *      dosimetry      *         date" <<  title_data[1] << endl;
  cout << "      *                     *          mat" << title_data[2] << endl;
  cout << "      *   ace format file   *" << endl;
  cout << "      *                     *         len2" << setw(10) << len2  << endl;
  cout << "      *     processed by    *           za" << setw(10) << za    << endl;
  cout << "      *                     *" << endl;
  cout << "      *        frendy       *          ntr" << setw(10) << ntr   << endl;
  cout << "      *                     *" << endl;
  cout << "      ***********************         lone" << setw(10) << lone  << endl;
  cout << "                                       mtr" << setw(10) << mtr   << endl;
  cout << "                                      lsig" << setw(10) << lsig  << endl;
  cout << "                                      sigd" << setw(10) << sigd  << endl;
  cout << endl << endl;
  cout << "hk---" << discriptive_data << endl;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DosimetryAceDataGenerator::output_ace_data_reaction_xs()
{
  //Print inelastic data
  cout << setiosflags(ios::right);

  int i_max = static_cast<int>(reaction_xs_reaction_type.size());
  for(int i=0; i<i_max; i++)
  {
    cout << "  reaction mt = " << setw(6) << reaction_xs_reaction_type[i] << endl;

    int j_max = static_cast<int>(reaction_xs_int_data[i].size());
    if( j_max == 1 && reaction_xs_int_data[i][0] == int_lin_lin )
    {
      cout << "  linear interpolation" << endl;
    }
    else
    {
      cout << "  interpolation:";
      for(int j=0; j<j_max; j++)
      {
        cout << setw(6) << reaction_xs_range_data[i][j] << setw(6) << reaction_xs_int_data[i][j];
      }
      cout << endl;
    }

    j_max = static_cast<int>(production_xs_data[i].size());
    cout << "         energy          xsec        energy          xsec        energy          xsec" << endl;
    cout << "         ------          ----        ------          ----        ------          ----" << endl;

    for(int j=0; j<j_max; j++)
    {
      cout.precision(4);
      cout.setf(ios::showpoint);
      cout.setf(ios::scientific);
      cout << "    " << reaction_xs_ene_data[i][j] << "    " << reaction_xs_data[i][j];
      if( j%3 == 2 && j != j_max-1 )
      {
        cout << endl;
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DosimetryAceDataGenerator::output_ace_data_production_xs()
{
  //Print inelastic data
  cout << setiosflags(ios::right);

  int i_max = static_cast<int>(production_xs_state_no_product.size());
  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(production_xs_state_no_product[i].size());
    for(int j=0; j<j_max; j++)
    {
      cout << "  reaction mt = " << setw(6) << production_xs_state_no_product[i][j] << endl;

      int k_max = static_cast<int>(production_xs_int_data[i][j].size());
      if( k_max == 1 && production_xs_int_data[i][j][0] == int_lin_lin )
      {
        cout << "  linear interpolation" << endl;
      }
      else
      {
        cout << "  interpolation:";
        for(int k=0; k<k_max; k++)
        {
          cout << setw(6) << production_xs_range_data[i][j][k] << setw(6) << production_xs_int_data[i][j][k];
        }
        cout << endl;
      }

      j_max = static_cast<int>(production_xs_data[i][j].size());
      cout << "         energy          xsec        energy          xsec        energy          xsec" << endl;
      cout << "         ------          ----        ------          ----        ------          ----" << endl;

      for(int k=0; k<k_max; k++)
      {
        cout.precision(4);
        cout.setf(ios::showpoint);
        cout.setf(ios::scientific);
        cout << "    " << production_xs_ene_data[i][j][k] << "    " << production_xs_data[i][j][k];
        if( k%3 == 2 && k != k_max-1 )
        {
          cout << endl;
        }
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DosimetryAceDataGenerator::check_set_data()
{
  string class_name = "DosimetryAceDataGenerator";
  string func_name  = "check_set_data()";

  if( nucl_data_set_flg == 0 )
  {
    vector<string> err_com;
    err_com.push_back("The NuclearDataObject data is not set.");
    err_com.push_back("Please set the NuclearDataObject data using set_nucl_data_obj() function.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  if( temp_set_flg > 0 )
  {
    Real8 temp_ref = static_cast<Real8>(nucl_data_obj.get_general_data_obj().get_temp());
    Real8 temp_dif = (temp - temp_ref);
    if( temp_ref > min_value )
    {
      temp_dif /= temp_ref;
    }

    if( fabs(temp_dif) > 1.0E-5 )
    {
      ostringstream oss01, oss02;
      oss01 << temp;
      oss02 << temp_ref;

      string str_data01 = "Set temperature data                  : " + oss01.str();
      string str_data02 = "Temperature data in NuclearDataObject : " + oss02.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);

      if( fabs(temp_dif) > 1.0E-2 )
      {
        err_com.push_back("The set temperature data is not identical to temperature in NuclearDataObject.");
        err_com.push_back("Please check the set temperature data or NuclearDataObject data.");
        err_obj.output_runtime_error(class_name, func_name, err_com);
      }
      else
      {
        err_com.push_back("The difference between set temp. data and NuclearDataObject's temp.");
        err_com.push_back("is not larger than 1.0E-5.");
        err_com.push_back("The set temperature data may not be appropriate.");
        err_obj.output_caution(class_name, func_name, err_com);
      }
    }
  }

  if( mat_set_flg > 0 )
  {
    Integer mat_ref = nucl_data_obj.get_general_data_obj().get_mat_no();
    if( mat != mat_ref )
    {
      ostringstream oss01, oss02;
      oss01 << mat;
      oss02 << mat_ref;

      string str_data01 = "Set material number                  : " + oss01.str();
      string str_data02 = "Material number in NuclearDataObject : " + oss02.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back("The set material number is not identical to that in NuclearDataObject.");
      err_com.push_back("Please check the set material number or NuclearDataObject data.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }

  class_name.clear();
  func_name.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//Setter

void DosimetryAceDataGenerator::set_nucl_data_obj(NuclearDataObject& data_obj)
{
  gen_dosimetry_data_flg = 0;
  nucl_data_set_flg      = 1;
  nucl_data_obj          = data_obj;
}

void DosimetryAceDataGenerator::set_mat(Integer int_val)
{
  gen_dosimetry_data_flg = 0;
  mat_set_flg            = 1;
  mat                    = int_val;
}

void DosimetryAceDataGenerator::set_temp(Real real_val)
{
  gen_dosimetry_data_flg = 0;
  temp_set_flg           = 1;
  temp                   = real_val;
}

void DosimetryAceDataGenerator::set_suffix_za_id(Real real_val)
{
  gen_dosimetry_data_flg = 0;
  suffix_za_id           = real_val;
}

void DosimetryAceDataGenerator::set_zi_awr_pair( vector<Integer> int_vec_zi,
                                                 vector<Real>    real_vec_awr )
{
  if( static_cast<int>(int_vec_zi.size()) != static_cast<int>(real_vec_awr.size()) )
  {
    string class_name = "DosimetryAceDataGenerator";
    string func_name  = "set_zi_awr_pair(vector<Integer> int_vec_zi, vector<Real> real_vec_awr)";

    ostringstream oss01, oss02;
    oss01 << static_cast<int>(int_vec_zi.size());
    oss02 << static_cast<int>(real_vec_awr.size());

    string str_data01 = "Number of zi  array data : " + oss01.str();
    string str_data02 = "Number of awr array data : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("Number of zi array data and that of awr array data is not identical.");
    err_com.push_back("Please check the set data.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  int i_max = static_cast<int>(int_vec_zi.size());
  if( i_max > max_zi_awr_pair_no )
  {
    string class_name = "DosimetryAceDataGenerator";
    string func_name  = "set_zi_awr_pair(vector<Integer> int_vec_zi, vector<Real> real_vec_awr)";

    ostringstream oss01;
    oss01 << i_max;
    string str_data01 = "Number of zi and awr pair data : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    for(int i=0; i<i_max; i++)
    {
      ostringstream oss02, oss03, oss04;
      oss02 << i+1;
      oss03 << int_vec_zi[i];
      oss04 << real_vec_awr[i];
      string str_data02 = "  zi and awr data at " + oss02.str() + " / " + oss01.str() + " : "
                        + oss03.str() + ", " + oss04.str();
      if( i >= max_zi_awr_pair_no )
      {
        str_data02 + " * not used";
      }
      err_com.push_back(str_data02);
    }
    ostringstream oss05;
    oss05 << max_zi_awr_pair_no;
    string str_data03 = "Zi and awr data array must be less than or equal to " + oss05.str() + ".";
    err_com.push_back("So, some data in zi and awr pair is not used.");
    err_obj.output_caution(class_name, func_name, err_com);
  }

  zi_vec  = int_vec_zi;
  awr_vec = real_vec_awr;

  int_vec_zi.clear();
  real_vec_awr.clear();
}

void DosimetryAceDataGenerator::set_discriptive_data(string str_data)
{
  gen_dosimetry_data_flg = 0;
  discriptive_data       = str_data;
  str_data.clear();
}

void DosimetryAceDataGenerator::set_mcnpx_mode_flg(Integer int_val)
{
  gen_dosimetry_data_flg = 0;
  mcnpx_mode_flg         = int_val;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//Getter
DosimetryAceDataObject DosimetryAceDataGenerator::get_ace_data_obj()
{
  generate_ace_data();

  DosimetryAceDataObject ace_data_obj;
  copy_dosimetry_ace_data(ace_data_obj);

  return ace_data_obj;
}

NuclearDataObject DosimetryAceDataGenerator::get_nucl_data_obj()
{
  return nucl_data_obj;
}

Integer           DosimetryAceDataGenerator::get_mat()
{
  return mat;
}

Real              DosimetryAceDataGenerator::get_temp()
{
  return temp;
}

Real              DosimetryAceDataGenerator::get_suffix_za_id()
{
  return suffix_za_id;
}

vector<Integer>   DosimetryAceDataGenerator::get_zi_vec()
{
  return zi_vec;
}

vector<Real>      DosimetryAceDataGenerator::get_awr_vec()
{
  return awr_vec;
}

string            DosimetryAceDataGenerator::get_discriptive_data()
{
  return discriptive_data;
}

Integer           DosimetryAceDataGenerator::get_mcnpx_mode_flg()
{
  return mcnpx_mode_flg;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

