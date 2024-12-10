#include "UnresoUtils/ProbabilityTableCalculatorByNjoyInput.hpp"

using namespace frendy;

//constructor
ProbabilityTableCalculatorByNjoyInput::ProbabilityTableCalculatorByNjoyInput(void)
{
  clear();
}

//destructor
ProbabilityTableCalculatorByNjoyInput::~ProbabilityTableCalculatorByNjoyInput(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculatorByNjoyInput::clear()
{
  prob_obj.clear();

  output_result_name.clear();
  fout_result.close();

  calc_flg      = 0;
  read_inp_mode = purr_mode;

  nucl_data_obj.clear();

  input_file_name_njoy.clear();
  start_line_no = 0;

  endf_name.clear();
  pendf_name_old.clear();
  pendf_name_new.clear();

  temp_no_int = 0;
  mat_no      = 0;
  ladder_no   = 0;
  bin_no      = 0;
  opt_print   = 0;
  ene_grid_no = 0;

  PurrInputReader read_njoy_obj;
  random_seed = read_njoy_obj.get_random_seed();
  sample_no   = read_njoy_obj.get_sample_no();
  p_tab_file_name.clear();

  read_njoy_obj.clear();

  temp.clear();
  sig_zero.clear();

  time_each_ene.clear();
  time_total = 0.0;

  set_xs_tot_table_data_flg = 0;
  xs_tot_table_ene.clear();
  clr_obj.clear_vec_array3_real8(xs_tot_table_all);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculatorByNjoyInput::calc_probability_table()
{
  if( calc_flg == 1 )
  {
    return;
  }
  calc_flg = 1;

  output_result_name = "output";
  fout_result.open(output_result_name.c_str());

  cout << "****************************** Probability Table calculation ******************************";
  cout << endl << endl;
  time_obj.output_current_time();

  set_input_data();
  output_input_file_name();
  check_pendf_data();

  boost::timer::cpu_timer timer_total;

  set_nucl_data_obj();
  set_prob_obj();

  //Calculation of probability_table
  prob_obj.output_set_data_information();
  prob_obj.calc_probability_table();
  nucl_data_obj = prob_obj.get_nucl_data_obj();
  time_each_ene = prob_obj.get_time_each_ene();
  prob_obj.clear();

  output_prob_table_data();

  time_total = static_cast<Real>(timer_total.elapsed().wall * 1.0E-9);
  cout << "Total calculation time : " << time_total << " [s]" << endl;
  cout << endl;
  cout << "*******************************************************************************************";
  cout << endl << endl;

  fout_result.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculatorByNjoyInput::output_input_file_name()
{
  cout << "=== Nuclear data file information ===" << endl;
  cout << "  Input File Name          : " << input_file_name_njoy << endl;
  cout << "  ENDF  File Name          : " << endf_name            << endl;
  cout << "  PENDF File Name (input)  : " << pendf_name_old       << endl;
  cout << "  PENDF File Name (output) : " << pendf_name_new       << endl;
  cout << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculatorByNjoyInput::set_input_data()
{
  if( read_inp_mode == purr_mode )
  {
    set_input_data_purr();
  }
  else //if( read_inp_mode == unresr_mode )
  {
    set_input_data_unresr();
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculatorByNjoyInput::set_input_data_purr()
{
  //Read purr input file
  PurrInputReader read_njoy_obj;
  read_njoy_obj.read_input(input_file_name_njoy, start_line_no);

  endf_name       = read_njoy_obj.get_endf_name();
  pendf_name_old  = read_njoy_obj.get_pendf_name_old();
  pendf_name_new  = read_njoy_obj.get_pendf_name_new();
  mat_no          = read_njoy_obj.get_mat();
  bin_no          = read_njoy_obj.get_bin_no();
  ladder_no       = read_njoy_obj.get_ladder_no();
  opt_print       = read_njoy_obj.get_opt_print();
  ene_grid_no     = read_njoy_obj.get_ene_grid_no();
  random_seed     = read_njoy_obj.get_random_seed();
  sample_no       = read_njoy_obj.get_sample_no();
  p_tab_file_name = read_njoy_obj.get_p_tab_file_name();
  temp            = read_njoy_obj.get_temp();
  sig_zero        = read_njoy_obj.get_sig_zero();
  temp_no_int     = static_cast<int>(temp.size());

  read_njoy_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculatorByNjoyInput::set_input_data_unresr()
{
  //Output caution
  string class_name = "ProbabilityTableCalculatorByNjoyInput";
  string func_name  = "set_input_data_unresr()";

  vector<string> err_com;
  err_com.push_back("Though this input file is for UNRESR, FRENDY is not implemented UNRESR module.");
  err_com.push_back("FRENDY calculate the f-factor using probability table.");
  err_com.push_back("This input file is considered as the PURR input file.");
  err_obj.output_caution(class_name, func_name, err_com);

  //Read unresr input file
  UnresrInputReader read_njoy_obj;
  read_njoy_obj.read_input(input_file_name_njoy, start_line_no);

  endf_name      = read_njoy_obj.get_endf_name();
  pendf_name_old = read_njoy_obj.get_pendf_name_old();
  pendf_name_new = read_njoy_obj.get_pendf_name_new();
  mat_no         = read_njoy_obj.get_mat();
  bin_no         = read_njoy_obj.get_bin_no();
  ladder_no      = read_njoy_obj.get_ladder_no();
  opt_print      = read_njoy_obj.get_opt_print();
  ene_grid_no    = read_njoy_obj.get_ene_grid_no();
  random_seed    = read_njoy_obj.get_random_seed();
  sample_no      = read_njoy_obj.get_sample_no();
  temp           = read_njoy_obj.get_temp();
  sig_zero       = read_njoy_obj.get_sig_zero();
  temp_no_int    = static_cast<int>(temp.size());

  p_tab_file_name.clear();

  read_njoy_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculatorByNjoyInput::check_pendf_data()
{
  //Read label data
  EndfTapeDivider  div_obj;
  div_obj.set_file_name(pendf_name_old);
  label_data = div_obj.get_label_data();

  vector<Integer>       mat_list  = div_obj.get_mat_list();
  vector<vector<Real> > temp_list = div_obj.get_temp_list();
  div_obj.clear();

  //Check material data in pend_name_old
  int mat_data_flg = -1;
  for(int i=0; i<static_cast<int>(mat_list.size()); i++)
  {
    if( mat_no == mat_list[i] )
    {
      mat_data_flg = i;
      break;
    }
  }

  if( mat_data_flg < 0 )
  {
    string class_name = "ProbabilityTableCalculatorByNjoyInput";
    string func_name  = "check_pendf_data()";

    ostringstream oss01;
    oss01 << mat_no;
    string str_data01 = "  Material number (from input) : " + oss01.str(); 

    vector<string> err_com;
    err_com.push_back("There is no desired material number in PENDF File Name (input).");
    err_com.push_back(str_data01);
    err_com.push_back("  Material number (from PENDF)");
    for(int i=0; i<static_cast<int>(mat_list.size()); i++)
    {
      ostringstream oss02, oss03, oss04;
      oss02 << mat_list[i];
      oss03 << i+1;
      oss04 << static_cast<int>(mat_list.size());
      string str_data02 = "    " + oss02.str() + " ( " + oss03.str() + " / " + oss04.str() + " )";
      err_com.push_back(str_data02);
    }

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //Check temperature data in pend_name_old
  for(int i=0; i<temp_no_int; i++)
  {
    Real diff = 1.0E-4;
    if( fabs(temp[i]) > min_ene_dif )
    {
      diff *= fabs(temp[i]);
    }

    int temp_data_flg = -1;
    for(int j=0; j<static_cast<int>(temp_list[mat_data_flg].size()); j++)
    {
      if( fabs(temp[i] - temp_list[mat_data_flg][j]) < diff )
      {
        temp_data_flg = j;
        break;
      }
    }

    if( temp_data_flg < 0 )
    {
      string class_name = "ProbabilityTableCalculatorByNjoyInput";
      string func_name  = "check_pendf_data()";

      ostringstream oss01, oss02, oss03;
      oss01 << i+1;
      oss02 << temp_no_int;
      oss03 << temp[i];
      string str_data01 = "  Temperature (from input) at " + oss01.str() + " / " + oss02.str() + " : "
                                                           + oss03.str() + " [K]";

      vector<string> err_com;
      err_com.push_back("There is no desired temperature data in PENDF File Name (input).");
      err_com.push_back(str_data01);
      err_com.push_back("  Temperature (from PENDF) [K]");
      for(int j=0; j<static_cast<int>(temp_list[mat_data_flg].size()); j++)
      {
        ostringstream oss04, oss05, oss06;
        oss04 << temp_list[mat_data_flg][j];
        oss05 << j+1;
        oss06 << static_cast<int>(temp_list[mat_data_flg].size());
        string str_data02 = "    " + oss04.str() + " ( " + oss05.str() + " / " + oss06.str() + " )";
        err_com.push_back(str_data02);
      }

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculatorByNjoyInput::set_nucl_data_obj()
{
  nucl_data_obj = store_obj.get_nucl_data_obj_no_cov(endf_name, mat_no);
  store_obj.clear();


  //Read HEAT cross section data from PENDF file
  EndfTapeDivider div_obj;
  div_obj.set_file_name(pendf_name_old);
  vector<Real> temp_list_pendf = div_obj.get_temp_list(mat_no);
  div_obj.clear();

  if( static_cast<int>(temp_list_pendf.size()) == 0 )
  {
    string class_name = "ProbabilityTableCalculatorByNjoyInput";
    string func_name  = "set_nucl_data_obj()";

    vector<string> err_com;
    err_com.push_back("There is no temperature data in PENDF File Name (input).");
    err_com.push_back("Please check the PENDF file (input)");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  NuclearDataObject                 nucl_data_pendf;
  vector<CrossSectionDataContainer> xs_obj_pendf, xs_obj_heat;
  nucl_data_pendf  = store_obj.get_nucl_data_obj_no_cov(pendf_name_old, mat_no, temp_list_pendf[0]);
  xs_obj_pendf     = nucl_data_pendf.get_nucl_reaction_data_obj().get_xs_data_obj();
  store_obj.clear();
  nucl_data_pendf.clear();
  
  xs_obj_heat.clear();
  for(int i=0; i<static_cast<int>(xs_obj_pendf.size()); i++)
  {
    Integer react_type = xs_obj_pendf[i].get_reaction_type();
    if( react_type == prob_obj.heat_tot || react_type == prob_obj.heat_ela ||
        react_type == prob_obj.heat_fis || react_type == prob_obj.heat_rad )
    {
      xs_obj_heat.push_back(xs_obj_pendf[i]);
    }
  }
  vector<CrossSectionDataContainer>().swap(xs_obj_pendf);

  int heat_xs_no = static_cast<int>(xs_obj_heat.size());
  if( heat_xs_no > 0 )
  {
    NuclearReactionDataContainer  react_obj_ori = nucl_data_obj.get_nucl_reaction_data_obj();
    for(int i=0; i<heat_xs_no; i++)
    {
      react_obj_ori.set_xs_data_obj(xs_obj_heat[i]);
    }
    vector<CrossSectionDataContainer>().swap(xs_obj_heat);

    nucl_data_obj.set_nucl_reaction_data_obj(react_obj_ori);
    react_obj_ori.clear();
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculatorByNjoyInput::set_prob_obj()
{
  prob_obj.clear();

  prob_obj.set_time_print_opt(prob_obj.print_time_data);

  prob_obj.set_nucl_data_obj(nucl_data_obj);

  prob_obj.set_ladder_no(ladder_no);
  prob_obj.set_bin_no(bin_no);
  prob_obj.set_ene_grid_no(ene_grid_no);
  prob_obj.set_random_seed(random_seed);
  prob_obj.set_sample_no(sample_no);
  prob_obj.set_temp_data(temp);
  prob_obj.set_sig_zero_data(sig_zero);

  prob_obj.set_static_err(1.0E-5);

  if( static_cast<int>(p_tab_file_name.size()) > 0 )
  {
    set_xs_tot_table_data_from_output(p_tab_file_name);
  }

  if( set_xs_tot_table_data_flg > 0 )
  {
    if( set_xs_tot_table_data_flg == 1 )
    {
      prob_obj.set_xs_tot_table_data(xs_tot_table_all);
    }
    else
    {
      prob_obj.set_xs_tot_table_data(xs_tot_table_all, xs_tot_table_ene);
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculatorByNjoyInput::output_prob_table_data()
{
  fout_result.precision(10);
  fout_result.setf(ios::showpoint);
  fout_result.setf(ios::scientific);

  ProbabilityDataContainer prob_data_obj = nucl_data_obj.get_prob_data_obj();
  Real8                           ene_grid;
  vector<Real8>                   temp_prob, sig_zero_prob;
  vector<vector<Real8> >          xs_tot_table, prob_table_sample_no;
  vector<vector<vector<Real8> > > prob_table, bondarenko_xs;

  int i_max = prob_data_obj.get_prob_table_ene_no();
  for(int i=0; i<i_max; i++)
  {
    ProbabilityTableDataContainer prob_table_data_obj = prob_data_obj.get_prob_table_data_obj(i);
    ene_grid      = prob_table_data_obj.get_ene_grid();
    temp_prob     = prob_table_data_obj.get_temp();
    sig_zero_prob = prob_table_data_obj.get_sig_zero();

    //Output General Data
    fout_result << "  Grid No. " << i+1 << " / " << i_max << endl;
    fout_result << "    Energy Grid [eV] : " << ene_grid << endl;
    fout_result << "    Calc.  Time [s]  : " << time_each_ene[i] << endl;

    if( opt_print > 0 )
    {
      fout_result << "                     Total            Scatter          Fission          Radiation";
      fout_result << endl;
      fout_result << "    Back ground xs : "
           << prob_table_data_obj.get_xs_back()[total_xs]     << " " 
           << prob_table_data_obj.get_xs_back()[scatter_xs]   << " "
           << prob_table_data_obj.get_xs_back()[fission_xs]   << " "
           << prob_table_data_obj.get_xs_back()[radiation_xs] << endl;
      fout_result << "    Infinite xs    : "
           << prob_table_data_obj.get_xs_unreso()[total_xs]     << " " 
           << prob_table_data_obj.get_xs_unreso()[scatter_xs]   << " "
           << prob_table_data_obj.get_xs_unreso()[fission_xs]   << " "
           << prob_table_data_obj.get_xs_unreso()[radiation_xs] << endl;
      fout_result << "    Average        : "
           << prob_table_data_obj.get_xs_inf_ave()[0][total_xs]     << " " 
           << prob_table_data_obj.get_xs_inf_ave()[0][scatter_xs]   << " "
           << prob_table_data_obj.get_xs_inf_ave()[0][fission_xs]   << " "
           << prob_table_data_obj.get_xs_inf_ave()[0][radiation_xs] << endl;
      fout_result << "    Variance       : "
           << prob_table_data_obj.get_xs_inf_var()[0][total_xs]     << " " 
           << prob_table_data_obj.get_xs_inf_var()[0][scatter_xs]   << " "
           << prob_table_data_obj.get_xs_inf_var()[0][fission_xs]   << " "
           << prob_table_data_obj.get_xs_inf_var()[0][radiation_xs] << endl;
      fout_result << endl;
    }

    //Output Bondarenko table
    fout_result << "    Bondarenko table" << endl;
    fout_result << "    (Bondarenko cross sections by direct sampling)" << endl;
    fout_result << "      Temperature      Sigma zero       "
                << "P0 total         Scatter          Fission          Radiation        P1 total" << endl;
    bondarenko_xs = prob_table_data_obj.get_bondarenko_xs_direct();
    for(int j=0; j<static_cast<int>(bondarenko_xs.size()); j++) //temperature loop
    {
      for(int k=0; k<static_cast<int>(bondarenko_xs[j].size()); k++) //sig zero loop
      {
        fout_result <<"      " << temp_prob[j] << " " << sig_zero_prob[k];
        int l_max = static_cast<int>(bondarenko_xs[j][k].size());
        for(int l=0; l<l_max; l++)
        {
          fout_result << " " << bondarenko_xs[j][k][l];
        }
        fout_result << endl;
      }
    }
    fout_result << endl;
    clr_obj.clear_vec_array3_real8(bondarenko_xs);

    //Output probability table
    xs_tot_table         = prob_table_data_obj.get_xs_tot_table();
    prob_table_sample_no = prob_table_data_obj.get_prob_table_sample_no();
    prob_table           = prob_table_data_obj.get_prob_table();
    fout_result << "    Probability table" << endl;
    for(int j=0; j<static_cast<int>(prob_table.size()); j++) //temperature loop
    {
      fout_result << "      Temperature  : " << temp_prob[j] << endl;
      fout_result << "      Min total xs : " << prob_table_data_obj.get_xs_tot_min()[j] << endl;
      fout_result << "      Max total xs :";

      int   k_max         = static_cast<int>(xs_tot_table[j].size());
      for(int k=0; k<k_max; k++)
      {
        fout_result << " " << xs_tot_table[j][k];
        if( (k+1)%5 == 0 && k < k_max-1)
        {
          fout_result << endl;
          fout_result << "                    ";
        }
      }
      fout_result << endl;

      fout_result << "      Probability  :";
      for(int k=0; k<k_max; k++) //bin no loop
      {
        fout_result << " " << prob_table_sample_no[j][k]; 
        if( (k+1)%5 == 0 && k < k_max-1)
        {
          fout_result << endl;
          fout_result << "                    ";
        }
      }
      fout_result << endl;

      for(int l=0; l<xs_type_no; l++)
      {
        if( l == total_xs )
        {
          fout_result << "      Total        :";
        }
        else if( l == scatter_xs )
        {
          fout_result << "      Scatter      :";
        }
        else if( l == fission_xs )
        {
          fout_result << "      Fission      :";
        }
        else if( l == radiation_xs )
        {
          fout_result << "      Radiation    :";
        }

        for(int k=0; k<k_max; k++) //bin no loop
        {
          fout_result << " " << prob_table[j][k][l];
          if( (k+1)%5 == 0 && k < k_max-1)
          {
            fout_result << endl;
            fout_result << "                    ";
          }
        }
        fout_result << endl;
      }
    }
    fout_result << endl;
    clr_obj.clear_vec_array2_real8(xs_tot_table);
    clr_obj.clear_vec_array2_real8(prob_table_sample_no);
    clr_obj.clear_vec_array3_real8(prob_table);

    //Output Bondarenko xs
    fout_result << "    Bondarenko cross section" << endl;
    fout_result << "    (Bondarenko cross sections from probability table)" << endl;
    fout_result << "      Temperature      Sigma zero       "
                << "P0 total         Scatter          Fission          Radiation        P1 total" << endl;
    bondarenko_xs = prob_table_data_obj.get_bondarenko_xs_prob();
    for(int j=0; j<static_cast<int>(bondarenko_xs.size()); j++) //temperature loop
    {
      for(int k=0; k<static_cast<int>(bondarenko_xs[j].size()); k++) //sig zero loop
      {
        fout_result <<"      " << temp_prob[j] << " " << sig_zero_prob[k];
        int l_max = static_cast<int>(bondarenko_xs[j][k].size());
        for(int l=0; l<l_max; l++)
        {
          fout_result << " " << bondarenko_xs[j][k][l];
        }
        fout_result << endl;
      }
    }
    fout_result << endl;
    temp_prob.clear();
    sig_zero_prob.clear();
    clr_obj.clear_vec_array3_real8(bondarenko_xs);

    prob_table_data_obj.clear();
  }
  prob_data_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<vector<vector<Real8> > > ProbabilityTableCalculatorByNjoyInput::read_xs_tot_table(string& file_name)
{
  ifstream fin_inp;
  fin_inp.open(file_name.c_str());
  if( !fin_inp )
  {
    string class_name = "ProbabilityTableCalculatorByNjoyInput";
    string func_name  = "read_xs_tot_table(string& file_name)";
    string str_data   = "Probability table data file name : " + file_name;

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("There is no probability table data file.");
    err_com.push_back("Please check the input file name.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  int sig_zero_no = static_cast<int>(sig_zero.size());

  vector<vector<vector<Real8> > > xs_tot_table_all;
  vector<vector<Real8> >          xs_tot_table;
  xs_tot_table.resize(temp_no_int);
  for(int i=0; i<temp_no_int; i++)
  {
    xs_tot_table[i].resize(bin_no);
  }

  string line_data, str_tmp;
  getline(fin_inp, line_data);
  while( !fin_inp.eof() )
  {
    if( line_data.find("Grid No.") != string::npos )
    {
      while( line_data.find("Probability table") == string::npos )
      {
        getline(fin_inp, line_data);
      }

      for(int i=0; i<temp_no_int; i++)
      {
        while( line_data.find("Min total xs") == string::npos )
        {
          getline(fin_inp, line_data);
        }
        fin_inp >> str_tmp >> str_tmp >> str_tmp >> str_tmp;
        for(int j=0; j<bin_no; j++)
        {
          xs_tot_table[i][j] = 0.0;
          fin_inp >> xs_tot_table[i][j];
        }
        getline(fin_inp, line_data);
      }
      xs_tot_table_all.push_back(xs_tot_table);

      while( line_data.find("(Bondarenko cross sections from probability table)") == string::npos )
      {
        getline(fin_inp, line_data);
      }
      getline(fin_inp, line_data);
      for(int i=0; i<temp_no_int; i++)
      {
        for(int j=0; j<sig_zero_no; j++)
        {
          getline(fin_inp, line_data);
        }
      }
      getline(fin_inp, line_data);
      getline(fin_inp, line_data);
    }
  }

  return xs_tot_table_all;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<NuclearDataObject> ProbabilityTableCalculatorByNjoyInput::get_nucl_data_with_unreso_prob_data()
{
  calc_probability_table();

  vector<NuclearDataObject> nucl_data_vec;
  nucl_data_vec.resize(temp_no_int);

  ProbabilityDataContainer prob_data_obj = nucl_data_obj.get_prob_data_obj();
  for(int i=0; i<temp_no_int; i++)
  {
    nucl_data_vec[i] = store_obj.get_nucl_data_obj(pendf_name_old, mat_no, temp[i]);
    store_obj.clear();

    //Set UnresolvedCrossSectionDataContainer and UnresolvedProbabilityDataContainer object and
    //Set void ProbabilityDataContainer object
    set_unreso_xs_and_prob_data_obj(i, nucl_data_vec[i], prob_data_obj);
  }
  prob_data_obj.clear();

  return nucl_data_vec;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculatorByNjoyInput::set_unreso_xs_and_prob_data_obj
                                              (int temp_no, NuclearDataObject& nucl_data,
                                               ProbabilityDataContainer  prob_data_obj)
{
  //Set UnresolvedCrossSectionDataContainer and UnresolvedProbabilityDataContainer object
  if( prob_data_obj.get_prob_table_ene_no() != 0 )
  {
    ResonanceDataContainer reso_data_obj = nucl_data.get_reso_data_obj();

    //Convert ProbabilityDataContainer to UnresolvedCrossSectionDataContainer
    UnresolvedCrossSectionDataContainer unreso_xs_data_obj;
    conv_obj.conv_prob_data_container_to_unreso_xs_data(temp_no, prob_data_obj, unreso_xs_data_obj);
    reso_data_obj.set_unreso_xs_data_obj(unreso_xs_data_obj);
    unreso_xs_data_obj.clear();

    //Convert ProbabilityDataContainer to UnresolvedProbabilityDataContainer
    UnresolvedProbabilityDataContainer  unreso_prob_data_obj;
    conv_obj.conv_prob_data_container_to_unreso_prob_data(temp_no, prob_data_obj, unreso_prob_data_obj);
    reso_data_obj.set_unreso_prob_data_obj(unreso_prob_data_obj);
    unreso_prob_data_obj.clear();

    nucl_data.set_reso_data_obj(reso_data_obj);
    reso_data_obj.clear();
  }

  //Set void ProbabilityDataContainer object
  prob_data_obj.clear();
  nucl_data.set_prob_data_obj(prob_data_obj);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityTableCalculatorByNjoyInput::write_pendf_file()
{
  vector<NuclearDataObject> nucl_data_vec = get_nucl_data_with_unreso_prob_data();

  vector<string> text;
  clr_obj.clear_vec_array1_str(text);

  //Open PENDF file
  ofstream fout;
  fout.open(pendf_name_new.c_str());

  if( fout.fail() )
  {
    string class_name = "ProbabilityTableCalculatorByNjoyInput";
    string func_name  = "write_pendf_file()";

    string str_data = "  Output file name : " + pendf_name_new;

    vector<string> err_com;
    err_com.push_back("Output file can not be open.");
    err_com.push_back("Please check the file name, directory name or access authority.");
    err_com.push_back(str_data);

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //Write PENDF file
  Endf6Writer wri_obj;
  for(int i=0; i<temp_no_int; i++)
  {
    wri_obj.set_nucl_data_obj(nucl_data_vec[i]);
    if( i == 0 )
    {
      wri_obj.set_pendf_label(label_data);
      text = wri_obj.get_endf_text_data();
    }
    else
    {
      text = wri_obj.get_endf_text_data_without_label();
    }
    nucl_data_vec[i].clear();
    wri_obj.clear();

    for(int i=0; i<static_cast<int>(text.size()); i++)
    {
      fout << text[i] << endl;
    }
    clr_obj.clear_vec_array1_str(text);
  }
  nucl_data_vec.clear();

  //Write tape end
  EndfFileWriter efw_obj;
  fout << efw_obj.write_tape_end() << endl;

  fout.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//Setter

void ProbabilityTableCalculatorByNjoyInput::set_read_inp_mode(int inp_mode)
{
  if( inp_mode != purr_mode && inp_mode != unresr_mode )
  {
    string class_name = "ProbabilityTableCalculatorByNjoyInput";
    string func_name  = "set_read_inp_mode(int inp_mode)";

    ostringstream oss01, oss02, oss03;
    oss01 << inp_mode;
    oss02 << purr_mode;
    oss03 << unresr_mode;

    string str_data01 = "Set input mode : " + oss01.str();
    string str_data02 = "PURR mode      : " + oss02.str();
    string str_data03 = "UNRESR mode    : " + oss03.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);

    err_com.push_back("Set input mode is not available.");
    err_com.push_back("Please check the input mode.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  read_inp_mode = inp_mode;
}

void ProbabilityTableCalculatorByNjoyInput::set_njoy_input_file_name(string str_data)
{
  set_njoy_input_file_name(str_data, 0);
}

void ProbabilityTableCalculatorByNjoyInput::set_njoy_input_file_name(string str_data, int line_no)
{
  calc_flg             = 0;
  input_file_name_njoy = str_data;
  start_line_no        = line_no;
  str_data.clear();
}

void ProbabilityTableCalculatorByNjoyInput::set_xs_tot_table_data_from_output(string& file_name)
{
  string class_name = "ProbabilityTableCalculatorByNjoyInput";
  string func_name  = "set_xs_tot_table_data_from_output(string& file_name)";

  string str_data = "Probability table data file : " + file_name;
  vector<string> err_com;
  err_com.push_back("Cross section boundary of probability table is obtained");
  err_com.push_back("from probability table data file.");
  err_com.push_back("This option is only used for the debug mode.");
  err_com.push_back(str_data);
  err_obj.output_caution(class_name, func_name, err_com);
  
  set_xs_tot_table_data_flg = 1;
  xs_tot_table_all          = read_xs_tot_table(file_name);
}

void ProbabilityTableCalculatorByNjoyInput::set_xs_tot_table_data(vector<vector<vector<Real8> > >& real_vec)
{
  set_xs_tot_table_data_flg = 1;
  xs_tot_table_all          = real_vec;
}

void ProbabilityTableCalculatorByNjoyInput::set_xs_tot_table_data
                                              ( vector<vector<vector<Real8> > >& real_vec_xs,
                                                vector<Real8>& real_vec_ene )
{
  set_xs_tot_table_data_flg = 2;
  xs_tot_table_all          = real_vec_xs;
  xs_tot_table_ene          = real_vec_ene;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//Getter
int ProbabilityTableCalculatorByNjoyInput::get_read_inp_mode()
{
  return read_inp_mode;
}

NuclearDataObject ProbabilityTableCalculatorByNjoyInput::get_nucl_data_obj()
{
  //Probability table is only contain in ProbabilityDataContainer class.
  calc_probability_table();

  return nucl_data_obj;
}

vector<NuclearDataObject> ProbabilityTableCalculatorByNjoyInput::get_nucl_data_obj_each_temp()
{
  //Probability table is contain in ProbabilityDataContainer and
  //UnresolvedProbabilityDataContainer classes. 
  return get_nucl_data_with_unreso_prob_data();
}

string            ProbabilityTableCalculatorByNjoyInput::get_njoy_input_file_name()
{
  return input_file_name_njoy;
}

string            ProbabilityTableCalculatorByNjoyInput::get_endf_name()
{
  return endf_name;
}

string            ProbabilityTableCalculatorByNjoyInput::get_pendf_name_old()
{
  return pendf_name_old;
}

string            ProbabilityTableCalculatorByNjoyInput::get_pendf_name_new()
{
  return pendf_name_new;
}

Integer           ProbabilityTableCalculatorByNjoyInput::get_mat_no()
{
  return mat_no;
}

Integer           ProbabilityTableCalculatorByNjoyInput::get_bin_no()
{
  return bin_no;
}

Integer           ProbabilityTableCalculatorByNjoyInput::get_ladder_no()
{
  return ladder_no;
}

Integer           ProbabilityTableCalculatorByNjoyInput::get_opt_print()
{
  return opt_print;
}

Integer           ProbabilityTableCalculatorByNjoyInput::get_ene_grid_no()
{
  return ene_grid_no;
}

Integer           ProbabilityTableCalculatorByNjoyInput::get_random_seed()
{
  return random_seed;
}

Integer           ProbabilityTableCalculatorByNjoyInput::get_sample_no()
{
  return sample_no;
}

string            ProbabilityTableCalculatorByNjoyInput::get_p_tab_file_name()
{
  return p_tab_file_name;
}

vector<Real8>     ProbabilityTableCalculatorByNjoyInput::get_temp()
{
  return temp;
}

vector<Real8>     ProbabilityTableCalculatorByNjoyInput::get_sig_zero()
{
  return sig_zero;
}

vector<Real8>     ProbabilityTableCalculatorByNjoyInput::get_time_each_ene()
{
  return time_each_ene;
}

Real8             ProbabilityTableCalculatorByNjoyInput::get_time_total()
{
  return time_total;
}

