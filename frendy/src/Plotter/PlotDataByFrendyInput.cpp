#include "Plotter/PlotDataByFrendyInput.hpp"

using namespace frendy;

//constructor
PlotDataByFrendyInput::PlotDataByFrendyInput(void)
{
  clear();
}

//destructor
PlotDataByFrendyInput::~PlotDataByFrendyInput(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotDataByFrendyInput::clear()
{
  frendy_inp_obj.clear();


  calc_flg = 0;
  temp_ref = 0.0;
  temp_com = 0.0;

  set_mg_option_flg = 0;

  mg_w_mode.clear();

  mg_w_e.clear();
  mg_w_f.clear();
  mg_w_int.clear();
  mg_w_nbt.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotDataByFrendyInput::plot_data()
{
  if( calc_flg != 0 )
  {
    return;
  }

  calc_flg = 1;

  cout << endl;
  cout << "======================================================================" << endl;
  cout << endl;
  cout << "+++ Start Plot Data +++" << endl;
  cout << endl;

  if( frendy_inp_obj.get_file_no() > 2 )
  {
    string class_name = "PlotDataByFrendyInput";
    string func_name  = "plot_data()";

    ostringstream oss;
    oss << frendy_inp_obj.get_file_no();
    string str_data01 = "File number : " + oss.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("The file number must be less than or equal to 2.");
    err_com.push_back("Please modify your input file.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  string ref_name, com_name;
  set_file_name(ref_name, com_name);

  if( frendy_inp_obj.get_ref_flg() == frendy_inp_obj.gendf_file )
  {
    cout << "Read GENDF file : " << ref_name << endl;

    plot_gendf_file(ref_name);
    return;
  }

  Real                  mat_no  = frendy_inp_obj.get_mat_no();
  Real                  temp    = frendy_inp_obj.get_temp();
  Real                  err     = frendy_inp_obj.get_error();
  Real                  err_max = frendy_inp_obj.get_error_max();
  Real                  err_int = frendy_inp_obj.get_error_integral();
  vector<Integer>       mt_list = frendy_inp_obj.get_mt_list();
  vector<vector<Real> > ene_vec_ref, xs_vec_ref, ene_vec_com, xs_vec_com;
  if( frendy_inp_obj.get_ref_flg() == frendy_inp_obj.endf_file ||
      frendy_inp_obj.get_ref_flg() == frendy_inp_obj.pendf_file )
  {
    cout << "Read ENDF-6 formatted file : " << ref_name << endl;

    PlotEndfData plot_endf_obj;
    plot_endf_obj.plot_endf(ref_name, mt_list, ene_vec_ref, xs_vec_ref,
                            mat_no, temp, err, err_max, err_int);
    temp_ref = plot_endf_obj.get_temp_ori();
  }
  else if( frendy_inp_obj.get_ref_flg() == frendy_inp_obj.ace_file )
  {
    cout << "Read ACE formatted file : " << ref_name << " (ref)" << endl;

    PlotAceData plot_ace_obj;
    plot_ace_obj.plot_ace(ref_name, mt_list, ene_vec_ref, xs_vec_ref, temp);
    temp_ref = plot_ace_obj.get_temp_ori();
  }
  cout << "Read completed." << endl;
  cout << endl;

  if( static_cast<int>(com_name.length()) == 0 )
  {
    //Output xs_vec_ref
    plot_xs_data(ref_name, mt_list, ene_vec_ref, xs_vec_ref);
    return;
  }
  else
  {
    if( frendy_inp_obj.get_com_flg() == frendy_inp_obj.endf_file ||
        frendy_inp_obj.get_com_flg() == frendy_inp_obj.pendf_file )
    {
      cout << "Read ENDF-6 formatted file : " << com_name << " (comp)" << endl;

      PlotEndfData plot_endf_obj;
      plot_endf_obj.plot_endf(com_name, mt_list, ene_vec_com, xs_vec_com,
                              mat_no, temp, err, err_max, err_int);
      temp_com = plot_endf_obj.get_temp_ori();
    }
    else if( frendy_inp_obj.get_com_flg() == frendy_inp_obj.ace_file )
    {
      cout << "Read ACE formatted file : " << com_name << " (comp)" << endl;

      PlotAceData plot_ace_obj;
      plot_ace_obj.plot_ace(com_name, mt_list, ene_vec_com, xs_vec_com, temp);
      temp_com = plot_ace_obj.get_temp_ori();
    }
    cout << "Read completed." << endl;
    cout << endl;

    //Output xs_vec_ref, xs_vec_com, and relative difference
    plot_comp_xs_data(ref_name, com_name, mt_list,
                      ene_vec_ref, xs_vec_ref, ene_vec_com, xs_vec_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotDataByFrendyInput::set_file_name(string& ref_name, string& com_name)
{
  ref_name.clear();
  com_name.clear();

  if( frendy_inp_obj.get_ref_flg() == frendy_inp_obj.no_file )
  {
    string class_name = "PlotDataByFrendyInput";
    string func_name  = "set_file_name(string& ref_name, string& com_name)";

    vector<string> err_com;
    err_com.push_back("There is no nuclear data file.");
    err_com.push_back("Please set ENDF(PENDF), ACE, or GENDF file name.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
  else if( frendy_inp_obj.get_ref_flg() == frendy_inp_obj.endf_file )
  {
    ref_name = frendy_inp_obj.get_nucl_file_name()[0];
  }
  else if( frendy_inp_obj.get_ref_flg() == frendy_inp_obj.ace_file )
  {
    ref_name = frendy_inp_obj.get_ace_file_name()[0];
  }
  else if( frendy_inp_obj.get_ref_flg() == frendy_inp_obj.pendf_file )
  {
    ref_name = frendy_inp_obj.get_pendf_file_name()[0];
  }
  else if( frendy_inp_obj.get_ref_flg() == frendy_inp_obj.gendf_file )
  {
    ref_name = frendy_inp_obj.get_gendf_file_name()[0];
  }

  if( frendy_inp_obj.get_com_flg() != frendy_inp_obj.no_file )
  {
    if( frendy_inp_obj.get_ref_flg() == frendy_inp_obj.gendf_file )
    {
      string class_name = "PlotDataByFrendyInput";
      string func_name  = "set_file_name(string& ref_name, string& com_name)";

      vector<string> err_com;
      err_com.push_back("The GENDF file cannot output the comparison results.");
      err_com.push_back("This program only plots cross sections and double differential cross sections.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }


    if( frendy_inp_obj.get_com_flg() == frendy_inp_obj.endf_file )
    {
      com_name = frendy_inp_obj.get_nucl_file_name()[0];
      if( frendy_inp_obj.get_ref_flg() == frendy_inp_obj.endf_file )
      {
        com_name = frendy_inp_obj.get_nucl_file_name()[1];
      }
    }
    else if( frendy_inp_obj.get_com_flg() == frendy_inp_obj.ace_file )
    {
      com_name = frendy_inp_obj.get_ace_file_name()[0];
      if( frendy_inp_obj.get_ref_flg() == frendy_inp_obj.ace_file )
      {
        com_name = frendy_inp_obj.get_ace_file_name()[1];
      }
    }
    else if( frendy_inp_obj.get_com_flg() == frendy_inp_obj.pendf_file )
    {
      com_name = frendy_inp_obj.get_pendf_file_name()[0];
      if( frendy_inp_obj.get_ref_flg() == frendy_inp_obj.pendf_file )
      {
        com_name = frendy_inp_obj.get_pendf_file_name()[1];
      }
    }
    else if( frendy_inp_obj.get_com_flg() == frendy_inp_obj.gendf_file )
    {
      com_name = frendy_inp_obj.get_gendf_file_name()[0];
      if( frendy_inp_obj.get_ref_flg() == frendy_inp_obj.gendf_file )
      {
        com_name = frendy_inp_obj.get_gendf_file_name()[1];
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotDataByFrendyInput::plot_gendf_file(string ref_name)
{
  string          out_name   = frendy_inp_obj.get_output_file_name();
  Integer         mat        = frendy_inp_obj.get_mat_no();
  Real            temp       = frendy_inp_obj.get_temp();
  vector<Integer> mf_list    = frendy_inp_obj.get_mf_list();
  vector<Integer> mt_list    = frendy_inp_obj.get_mt_list();
  Integer         graph_type = frendy_inp_obj.get_edit_flg();

  PlotGendfData plot_gendf_obj;
  plot_gendf_obj.output_gendf_data(out_name, ref_name, mat, temp, mf_list, mt_list, graph_type);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotDataByFrendyInput::plot_xs_data(string nucl_name, vector<Integer>& mt_list,
                                         vector<vector<Real> >& ene_vec, vector<vector<Real> >& xs_vec)
{
  if( frendy_inp_obj.get_mg_flg() > 0 )
  {
    plot_mg_xs_data(nucl_name, mt_list, ene_vec, xs_vec);
    return;
  }

  ostringstream oss_temp_inp, oss_temp_nucl;
  oss_temp_inp  << setw(8) << std::showpoint << frendy_inp_obj.get_temp();
  oss_temp_nucl << setw(8) << std::showpoint << temp_ref;

  int i_max = static_cast<int>(mt_list.size());
  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(xs_vec[i].size());
    if( j_max == 0 )
    {
      continue;
    }

    string output = set_output_name(nucl_name, mt_list[i]);

    ofstream fout;
    fout.open(output.c_str());

    if( fout.fail() )
    {
      string class_name = "PlotDataByFrendyInput";
      string func_name  = "plot_xs_data";

      string str_data = "  Output file name : " + output;

      vector<string> err_com;
      err_com.push_back("Output file can not be open.");
      err_com.push_back("Please check the file name, directory name or access authority.");
      err_com.push_back(str_data);

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    fout.precision(10);
    fout.setf(ios::showpoint);
    fout.setf(ios::scientific);

    fout << "# endf/pendf/ace file name     : " << nucl_name  << endl;
    if( frendy_inp_obj.get_temp() > -1.0*min_value )
    {
      fout << "# Temperature [K] (inp / nucl) : " << oss_temp_inp.str() << " / " << oss_temp_nucl.str() << endl;
    }
    else
    {
      fout << "# Temperature [K] (nucl)       : " << oss_temp_nucl.str() << endl;
    }
    fout << "# MT (reaction type)           : " << mt_list[i] << endl;
    fout << "#" << endl;
    fout << "# energy [eV] / data" << endl;
    for(int j=0; j<j_max; j++)
    {
      if( check_plot_flg(j, xs_vec[i]) < 0 )
      {
        continue;
      }

      fout << ene_vec[i][j] << "  " << xs_vec[i][j] << endl;
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotDataByFrendyInput::plot_mg_xs_data(string nucl_name, vector<Integer>& mt_list,
                                            vector<vector<Real> >& ene_vec, vector<vector<Real> >& xs_vec)
{
  vector<vector<Real> > weight_vec;
  vector<Real>          mg_structure;
  set_mg_option_flg = 0;
  set_mg_option(ene_vec, weight_vec, mg_structure);

  vector<vector<Real> > mg_xs_vec = get_mg_xs_data(mt_list, ene_vec, xs_vec, weight_vec, mg_structure);

  ostringstream oss_temp_inp, oss_temp_nucl;
  oss_temp_inp  << setw(8) << std::showpoint << frendy_inp_obj.get_temp();
  oss_temp_nucl << setw(8) << std::showpoint << temp_ref;

  int i_max = static_cast<int>(mt_list.size());
  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(mg_xs_vec[i].size());
    if( j_max == 0 )
    {
      continue;
    }

    string output = set_output_name(nucl_name, mt_list[i]);

    ofstream fout;
    fout.open(output.c_str());

    if( fout.fail() )
    {
      string class_name = "PlotDataByFrendyInput";
      string func_name  = "plot_mg_xs_data";

      string str_data = "  Output file name : " + output;

      vector<string> err_com;
      err_com.push_back("Output file can not be open.");
      err_com.push_back("Please check the file name, directory name or access authority.");
      err_com.push_back(str_data);

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    fout.precision(10);
    fout.setf(ios::showpoint);
    fout.setf(ios::scientific);

    fout << "# endf/pendf/ace file name     : " << nucl_name  << endl;
    if( frendy_inp_obj.get_temp() > -1.0*min_value )
    {
      fout << "# Temperature [K] (inp / nucl) : " << oss_temp_inp.str() << " / " << oss_temp_nucl.str() << endl;
    }
    else
    {
      fout << "# Temperature [K] (nucl)       : " << oss_temp_nucl.str() << endl;
    }
    fout << "# MT (reaction type)           : " << mt_list[i] << endl;
    fout << "#" << endl;
    fout << "# energy [eV] / data" << endl;

    for(int j=0; j<j_max; j++)
    {
      if( check_plot_flg(j, mg_xs_vec[i]) < 0 )
      {
        continue;
      }

      if(frendy_inp_obj.get_edit_flg() == frendy_inp_obj.one_point)
      {
        fout << mg_structure[j] << "  " << mg_xs_vec[i][j] << endl;
      }
      else //if(frendy_inp_obj.get_edit_flg() == frendy_inp_obj.histogram)
      {
        Real mg_el = mg_structure[j];
        Real mg_eh = digit_obj.get_adjusted_value(mg_structure[j+1], sig_fig, -1.0); //eh of each energy grid
        fout << mg_el << "  " << mg_xs_vec[i][j] << endl;
        fout << mg_eh << "  " << mg_xs_vec[i][j] << endl;
      }
    }
    fout.close();
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotDataByFrendyInput::plot_comp_xs_data
                              (string ref_name, string comp_name, vector<Integer>& mt_list,
                               vector<vector<Real> >& ene_vec_ref, vector<vector<Real> >& xs_vec_ref,
                               vector<vector<Real> >& ene_vec_com, vector<vector<Real> >& xs_vec_com)
{
  if( frendy_inp_obj.get_mg_flg() > 0 )
  {
    plot_comp_mg_xs_data(ref_name, comp_name, mt_list, ene_vec_ref, xs_vec_ref, ene_vec_com, xs_vec_com);
    return;
  }

  ostringstream oss_temp_inp, oss_temp_ref, oss_temp_com;
  oss_temp_inp << setw(8) << std::showpoint << frendy_inp_obj.get_temp();
  oss_temp_ref << setw(8) << std::showpoint << temp_ref;
  oss_temp_com << setw(8) << std::showpoint << temp_com;

  vector<Real> rms_vec;

  int i_max = static_cast<int>(mt_list.size());
  rms_vec.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    rms_vec[i] = 0.0;
    if( static_cast<int>(ene_vec_ref[i].size()) == 0 ||
        static_cast<int>(ene_vec_com[i].size()) == 0 )
    {
      rms_vec[i] = -1.0;
      continue;
    }

    vector<Real> ene_vec_mod = ene_vec_ref[i];
    tab_ad_obj.add_grid_data(ene_vec_mod, ene_vec_com[i]);

    string output = set_output_name(comp_name, mt_list[i]);

    ofstream fout;
    fout.open(output.c_str());

    if( fout.fail() )
    {
      string class_name = "PlotDataByFrendyInput";
      string func_name  = "plot_comp_xs_data";

      string str_data = "  Output file name : " + output;

      vector<string> err_com;
      err_com.push_back("Output file can not be open.");
      err_com.push_back("Please check the file name, directory name or access authority.");
      err_com.push_back(str_data);

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    fout.precision(10);
    fout.setf(ios::showpoint);
    fout.setf(ios::scientific);

    fout << "# endf/pendf/ace file name (ref)     : " << ref_name  << endl;
    fout << "# endf/pendf/ace file name (comp)    : " << comp_name  << endl;
    if( frendy_inp_obj.get_temp() > -1.0*min_value )
    {
      fout << "# Temperature [K] (inp / ref / comp) : " << oss_temp_inp.str() << " / " << oss_temp_ref.str()
                                                                              << " / " << oss_temp_com.str() << endl;
    }
    else
    {
      fout << "# Temperature [K] (ref / comp)       : " << oss_temp_ref.str()
                                               << " / " << oss_temp_com.str() << endl;
    }
    fout << "# MT (reaction type)                 : " << mt_list[i] << endl;
    fout << "#" << endl;
    fout << "# energy [eV] / ref data / comp data / relative dif (comp - ref)/ref" << endl;

    int j_max = static_cast<int>(ene_vec_mod.size());
    for(int j=0; j<j_max; j++)
    {
      Real xs_val_ref, xs_val_com, xs_val_dif;
      ti_obj.interpolation_1d_in_range(int_lin_lin, ene_vec_mod[j], xs_val_ref, ene_vec_ref[i], xs_vec_ref[i]);
      ti_obj.interpolation_1d_in_range(int_lin_lin, ene_vec_mod[j], xs_val_com, ene_vec_com[i], xs_vec_com[i]);
      xs_val_dif = xs_val_com - xs_val_ref;
      if( fabs(xs_val_ref) > min_value )
      {
        xs_val_dif = xs_val_dif / xs_val_ref;
      }

      fout << ene_vec_mod[j] << "  " << xs_val_ref << "  " << xs_val_com << "  " << xs_val_dif << endl;
      rms_vec[i] += xs_val_dif * xs_val_dif;
    }
    fout.close();

    if( j_max > 0 )
    {
      rms_vec[i] = sqrt(rms_vec[i] / static_cast<Real>(j_max));
    }
  }

  cout << endl;
  cout << "+++ Comparison results +++" << endl;
  cout << endl;
  cout << "Reaction type / RMS value" << endl;
  cout.precision(8);
  cout.setf(ios::showpoint);
  cout.setf(ios::scientific);
  for(int i=0; i<i_max; i++)
  {
    if( rms_vec[i] > -0.1 )
    {
      cout << "  " << setw(4) << setfill(' ') << mt_list[i] << " / " << rms_vec[i] << endl;
    }
  }
  cout << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotDataByFrendyInput::plot_comp_mg_xs_data
                              (string ref_name, string comp_name, vector<Integer>& mt_list,
                               vector<vector<Real> >& ene_vec_ref, vector<vector<Real> >& xs_vec_ref,
                               vector<vector<Real> >& ene_vec_com, vector<vector<Real> >& xs_vec_com)
{
  vector<vector<Real> > weight_vec_ref, weight_vec_com;
  vector<Real>          mg_structure;
  set_mg_option_flg = 0;
  set_mg_option(ene_vec_ref, weight_vec_ref, mg_structure);
  set_mg_option(ene_vec_com, weight_vec_com, mg_structure);

  vector<vector<Real> > mg_xs_ref, mg_xs_com;
  mg_xs_ref = get_mg_xs_data(mt_list, ene_vec_ref, xs_vec_ref, weight_vec_ref, mg_structure);
  mg_xs_com = get_mg_xs_data(mt_list, ene_vec_com, xs_vec_com, weight_vec_com, mg_structure);

  ostringstream oss_temp_inp, oss_temp_ref, oss_temp_com;
  oss_temp_inp << setw(8) << std::showpoint << frendy_inp_obj.get_temp();
  oss_temp_ref << setw(8) << std::showpoint << temp_ref;
  oss_temp_com << setw(8) << std::showpoint << temp_com;

  vector<Real> rms_vec;

  int i_max = static_cast<int>(mt_list.size());
  rms_vec.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    rms_vec[i] = 0.0;

    int j_max = static_cast<int>(mg_xs_ref[i].size());
    if( j_max == 0 || static_cast<int>(mg_xs_com[i].size()) == 0 )
    {
      rms_vec[i] = -1.0;
      continue;
    }

    string output = set_output_name(comp_name, mt_list[i]);

    ofstream fout;
    fout.open(output.c_str());

    if( fout.fail() )
    {
      string class_name = "PlotDataByFrendyInput";
      string func_name  = "plot_comp_mg_xs_data";

      string str_data = "  Output file name : " + output;

      vector<string> err_com;
      err_com.push_back("Output file can not be open.");
      err_com.push_back("Please check the file name, directory name or access authority.");
      err_com.push_back(str_data);

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    fout.precision(10);
    fout.setf(ios::showpoint);
    fout.setf(ios::scientific);

    fout << "# endf/pendf/ace file name (ref)     : " << ref_name  << endl;
    fout << "# endf/pendf/ace file name (comp)    : " << comp_name  << endl;
    if( frendy_inp_obj.get_temp() > -1.0*min_value )
    {
      fout << "# Temperature [K] (inp / ref / comp) : " << oss_temp_inp.str() << " / " << oss_temp_ref.str()
                                                                              << " / " << oss_temp_com.str() << endl;
    }
    else
    {
      fout << "# Temperature [K] (ref / comp)       : " << oss_temp_ref.str()
                                               << " / " << oss_temp_com.str() << endl;
    }
    fout << "# MT (reaction type)                 : " << mt_list[i] << endl;
    fout << "#" << endl;
    fout << "# energy [eV] / ref data / comp data / relative dif (comp - ref)/ref" << endl;

    for(int j=0; j<j_max; j++)
    {
      if( check_plot_flg(j, mg_xs_ref[i]) < 0 && check_plot_flg(j, mg_xs_com[i]) < 0 )
      {
        continue;
      }

      Real mg_xs_dif =  mg_xs_com[i][j] - mg_xs_ref[i][j];
      if( fabs(mg_xs_ref[i][j]) > min_value )
      {
        mg_xs_dif = mg_xs_dif / mg_xs_ref[i][j];
      }
      rms_vec[i] += mg_xs_dif * mg_xs_dif;

      if(frendy_inp_obj.get_edit_flg() == frendy_inp_obj.one_point)
      {
        fout << mg_structure[j] << "  " << mg_xs_ref[i][j] << "  " << mg_xs_com[i][j] << "  " << mg_xs_dif << endl;
      }
      else //if(frendy_inp_obj.get_edit_flg() == frendy_inp_obj.histogram)
      {
        Real mg_el = mg_structure[j];
        Real mg_eh = digit_obj.get_adjusted_value(mg_structure[j+1], sig_fig, -1.0); //eh of each energy grid
        fout << mg_el << "  " << mg_xs_ref[i][j] << "  " << mg_xs_com[i][j] << "  " << mg_xs_dif << endl;
        fout << mg_eh << "  " << mg_xs_ref[i][j] << "  " << mg_xs_com[i][j] << "  " << mg_xs_dif << endl;
      }
    }
    fout.close();

    if( j_max > 0 )
    {
      rms_vec[i] = sqrt(rms_vec[i] / static_cast<Real>(j_max));
    }
  }

  cout << endl;
  cout << "+++ Comparison results +++" << endl;
  cout << endl;
  cout << "Reaction type / RMS value" << endl;
  cout.precision(8);
  cout.setf(ios::showpoint);
  cout.setf(ios::scientific);
  for(int i=0; i<i_max; i++)
  {
    if( rms_vec[i] > -0.1 )
    {
      cout << "  " << setw(4) << setfill(' ') << mt_list[i] << " / " << rms_vec[i] << endl;
    }
  }
  cout << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int PlotDataByFrendyInput::check_plot_flg(int i, vector<Real>& xs_vec)
{
  if( xs_vec[i] < min_value )
  {
    int i_max = static_cast<int>(xs_vec.size());
    if( i != 0 && i != i_max - 1 )
    {
      if( xs_vec[i-1] < min_value && xs_vec[i+1] < min_value )
      {
        return -1;
      }
    }
    else if( i_max > 1 )
    {
      if( i==0 )
      {
        if( xs_vec[i+1] < min_value )
        {
          return -2;
        }
      }
      else if( i==i_max-1 )
      {
        if( xs_vec[i-1] < min_value )
        {
          return -3;
        }
      }
    }
  }

  return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

string PlotDataByFrendyInput::set_output_name(string nucl_name, Integer mt_no)
{
  string output = frendy_inp_obj.get_output_file_name();
  if( static_cast<int>(output.size()) == 0 )
  {
    output = nucl_name;
  }

  if( mt_no < 10000 )
  {
    ostringstream oss;
    oss << setw(4) << setfill('0') << mt_no;
    output = output + "_" + oss.str() + ".dat";
  }
  else
  {
    //For MF=09 and MF=10
    int mf       = (mt_no % 10000) / 100;
    int mt       =  mt_no / 10000;
    int state_no = (mt_no %   100);
    ostringstream oss_mf, oss_mt, oss_state;
    oss_mf    << setw(2) << setfill('0') << mf;
    oss_mt    << setw(3) << setfill('0') << mt;
    oss_state << setw(2) << setfill('0') << state_no;
    output = output + "_mf" + oss_mf.str() + "_mt" + oss_mt.str()
                    + "_"   + oss_state.str() + ".dat";
  }

  return output;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotDataByFrendyInput::set_mg_option(vector<vector<Real> >& ene_vec, vector<vector<Real> >& weight_vec,
                                          vector<Real>& mg_structure)
{
  if( set_mg_option_flg == 0 )
  {
    set_mg_option_flg = 1;

    string inp_name = frendy_inp_obj.get_input_file_name();
    MultiGroupDataGeneratorInputReader mg_inp_obj;
    mg_inp_obj.read_input_data_from_input_file_without_data_check(inp_name);

    mg_structure = mg_inp_obj.get_mg_structure();
    sort(mg_structure.begin(), mg_structure.end());

    mg_w_mode = mg_inp_obj.get_mg_weighting_spectrum_mode();
    mg_w_e    = mg_inp_obj.get_mg_weighting_spectrum_data_e();
    mg_w_f    = mg_inp_obj.get_mg_weighting_spectrum_data_w();
    mg_w_int  = mg_inp_obj.get_mg_weighting_spectrum_data_int();
    mg_w_nbt  = mg_inp_obj.get_mg_weighting_spectrum_data_nbt();
    transform(mg_w_mode.begin(), mg_w_mode.end(), mg_w_mode.begin(), ::tolower);

    if( static_cast<int>(mg_w_mode.find("fission+1/e+maxwell")) == 0 )
    {
      string class_name = "PlotDataByFrendyInput";
      string func_name  = "set_mg_option";

      string str_data01 = "Multi group weighting spectrum mode : " + mg_w_mode;

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back("This weighting spectrum mode is not available in the plotting funtion.");
      err_com.push_back("Please modify your input file.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }

  int i_max = static_cast<int>(ene_vec.size());
  weight_vec.clear();
  weight_vec.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(ene_vec[i].size());
    weight_vec[i].resize(j_max);
    if( static_cast<int>(mg_w_mode.find("1/e")) == 0 )
    {
      for(int j=0; j<j_max; j++)
      {
        weight_vec[i][j] = 1.0 / ene_vec[i][j];
      }
    }
    else
    {
      for(int j=0; j<j_max; j++)
      {
        ti_obj.interpolation_tab1_in_range(ene_vec[i][j], weight_vec[i][j],
                                           mg_w_nbt, mg_w_int, mg_w_e, mg_w_f);
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<vector<Real> > PlotDataByFrendyInput::get_mg_xs_data(vector<Integer>& mt_list, 
                                              vector<vector<Real> > ene_vec, vector<vector<Real> > xs_vec,
                                              vector<vector<Real> > weight_vec, vector<Real> mg_structure)
{
  vector<vector<Real> > mg_xs;
  int i_max = static_cast<int>(ene_vec.size());
  mg_xs.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    mg_xs[i].clear();
    if( static_cast<int>(xs_vec[i].size()) == 0 || static_cast<int>(weight_vec[i].size()) == 0 )
    {
      continue;
    }

    if( mt_list[i] == 1018 )
    {
      //Remove without initial incident energy data
      vector<Real> e_new, xs_new;
      e_new.clear();
      xs_new.clear();

      int j_sta = 0;
      if( ene_vec[i][0]  < 0.0 )
      {
         j_sta++;
      }
      for(int j=j_sta; j<static_cast<int>(ene_vec[i].size()); j++)
      {
        if( ene_vec[i][j] < 0.0 )
        {
          break;
        }

        e_new.push_back(ene_vec[i][j]);
        xs_new.push_back(xs_vec[i][j]);
      }

      ene_vec[i] = e_new;
      xs_vec[i]  = xs_new;
    }

    vector<Real> weight_tab = weight_vec[i];
    vector<Real> xs_tab_mod = xs_vec[i];
    int j_max = static_cast<int>(xs_tab_mod.size());
    if( mt_list[i] < 1000 )
    {
      for(int j=0; j<j_max; j++)
      {
        xs_tab_mod[j] *= weight_tab[j];
      }
    }
    else
    {
      weight_tab.resize(j_max);
      for(int j=0; j<j_max; j++)
      {
        weight_tab[j] = 1.0;
      }
    }

    vector<Integer> nbt_xs, int_xs;
    nbt_xs.resize(1);
    int_xs.resize(1);
    nbt_xs[0] = j_max;
    int_xs[0] = int_lin_lin;

    Real ene_min = ene_vec[i][0];
    Real ene_max = ene_vec[i][static_cast<int>(ene_vec[i].size())-1];

    int mg_no = static_cast<int>(mg_structure.size()-1);
    vector<Real> xs_tab_mg;
    xs_tab_mg.resize(mg_no);
    for(int j=0; j<mg_no; j++)
    {
      Real xs_mg_val     = 0.0;
      Real weight_mg_val = 0.0;
      Real el            = mg_structure[j];
      Real eh            = mg_structure[j+1];
      if( ene_min > eh || ene_max < el )
      {
        xs_mg_val = 0.0;
      }
      else
      {
        if( ene_min > el )
        {
          el = ene_min;
        }
        else if( ene_max < el )
        {
          el = ene_max;
        }

        if( ene_max < eh )
        {
          eh = ene_max;
        }
        else if( ene_min > eh )
        {
          eh = ene_min;
        }
        Real div_val = 0.0;
        if( fabs( eh - el ) > fabs(min_ene_dif * eh) )
        {
          div_val = 1.0 / (eh - el);
        }

        xs_mg_val = integ_obj.integrate_tab1_data(nbt_xs, int_xs, ene_vec[i], xs_tab_mod, el, eh);
        xs_mg_val *= div_val;

        weight_mg_val = integ_obj.integrate_tab1_data(nbt_xs, int_xs, ene_vec[i], weight_tab, el, eh);
        weight_mg_val *= div_val;

        if( fabs(weight_mg_val) > min_value )
        {
          xs_mg_val /= weight_mg_val;
        }

        if( xs_mg_val <= min_value )
        {
          xs_mg_val = 0.0;
        }
      }
      xs_tab_mg[j] = xs_mg_val;
    }

    mg_xs[i] = xs_tab_mg;
  }

  return mg_xs;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotDataByFrendyInput::set_frendy_input(string input_file_name)
{
  calc_flg = 0;
  frendy_inp_obj.read_input_data_from_input_file(input_file_name);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotDataByFrendyInput::set_frendy_inp_obj(NuclearDataPlotterInputReader inp_obj)
{
  calc_flg = 0;
  frendy_inp_obj = inp_obj;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

NuclearDataPlotterInputReader PlotDataByFrendyInput::get_frendy_inp_obj()
{
  return frendy_inp_obj;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

