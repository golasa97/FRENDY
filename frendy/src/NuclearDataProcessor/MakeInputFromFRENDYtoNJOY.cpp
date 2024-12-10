#include "NuclearDataProcessor/MakeInputFromFRENDYtoNJOY.hpp"

using namespace frendy;

//constructor
MakeInputFromFRENDYtoNJOY::MakeInputFromFRENDYtoNJOY(void)
{
  tolerance_input    =  1.0E-3;
  precision          =  5;
  comment_row_number = 30;

  clear();
}

//destructor
MakeInputFromFRENDYtoNJOY::~MakeInputFromFRENDYtoNJOY(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MakeInputFromFRENDYtoNJOY::clear()
{
  frendy_inp_obj.clear();

  nucl_data_obj_ori.clear();
  nucl_data_obj_tsl.clear();

  calc_mode   = 0;

  mt_tsl_iin  = 0;
  mt_tsl_icoh = 0;

  clr_obj.clear_vec_array1_str(njoy_input_data);

  set_default_tape_no();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MakeInputFromFRENDYtoNJOY::set_default_tape_no()
{
  nendf_ori    = 20;
  npend_reconr = 21;
  npend_broadr = 22;
  npend_gaspr  = 23;
  npend_purr   = 24;

  nendf_tsl    = 26;
  npend_thermr = 27;

  nace         = 30;
  nacedir      = 31;

  ngendf       = 35;
  nmatxs       = 36;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MakeInputFromFRENDYtoNJOY::make_input_from_frendy_to_njoy(FrendyInputReader inp_obj,
                                                               string output_name)
{
  make_input_from_frendy_to_njoy(inp_obj);

  write_njoy_input(output_name);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MakeInputFromFRENDYtoNJOY::make_input_from_frendy_to_njoy(FrendyInputReader inp_obj)
{
  clear();

  frendy_inp_obj = inp_obj;
  calc_mode = frendy_inp_obj.get_calc_mode();

  njoy_module_flg_obj = frendy_inp_obj.get_inp_make_njoy_obj();

  Endf6FileStore endf_read_obj;
  nucl_data_obj_ori = endf_read_obj.get_nucl_data_obj(frendy_inp_obj.get_nucl_file_name()[0]);
  endf_read_obj.clear();

  clr_obj.clear_vec_array1_str(njoy_input_data);
  if( calc_mode == frendy_inp_common_obj.ace_fast_mode + frendy_inp_common_obj.make_inp_mode )
  {
    make_input_ace_fast();
  }
  else if( calc_mode == frendy_inp_common_obj.ace_therm_mode + frendy_inp_common_obj.make_inp_mode )
  {
    string nucl_file_name_tsl = frendy_inp_obj.get_inp_thermal_scatter_obj().get_nucl_file_name_tsl()[0];
    nucl_data_obj_tsl = endf_read_obj.get_nucl_data_obj(nucl_file_name_tsl);
    endf_read_obj.clear();

    make_input_ace_therm();
  }
  else if( calc_mode == frendy_inp_common_obj.ace_dosi_mode + frendy_inp_common_obj.make_inp_mode )
  {
    make_input_ace_dosi();
  }
  else if( calc_mode == frendy_inp_common_obj.mg_neutron_mode  + frendy_inp_common_obj.make_inp_mode ||
           calc_mode == frendy_inp_common_obj.mg_tsl_mode_fast + frendy_inp_common_obj.make_inp_mode )
  {
    if( static_cast<int>(frendy_inp_obj.get_inp_thermal_scatter_obj().get_nucl_file_name_tsl().size()) == 0 )
    {
      make_input_matxs();
    }
    else
    {
      string nucl_file_name_tsl = frendy_inp_obj.get_inp_thermal_scatter_obj().get_nucl_file_name_tsl()[0];
      nucl_data_obj_tsl = endf_read_obj.get_nucl_data_obj(nucl_file_name_tsl);
      endf_read_obj.clear();

      make_input_matxs_tsl();
    }
  }
  else if( calc_mode == frendy_inp_common_obj.mg_tsl_mode + frendy_inp_common_obj.make_inp_mode )
  {
    string nucl_file_name_tsl = frendy_inp_obj.get_inp_thermal_scatter_obj().get_nucl_file_name_tsl()[0];
    nucl_data_obj_tsl = endf_read_obj.get_nucl_data_obj(nucl_file_name_tsl);
    endf_read_obj.clear();

    make_input_matxs_tsl();
  }
  else
  {
    string class_name = "MakeInputFromFRENDYtoNJOY";
    string func_name  = "make_input_from_frendy_to_njoy(FrendyInputReader inp_obj)";

    vector<string> err_com;
    err_com.push_back("This input file may not be input file for this program.");
    err_com.push_back("Please check the input file.");
    err_com.push_back("The available input mode is as follows:");
    
    vector<string> func_name_list = frendy_inp_obj.get_func_name_list();
    for(int i=0; i<static_cast<int>(func_name_list.size()); i++)
    {
      string str_data = "  " + func_name_list[i];
      err_com.push_back(str_data);
    }

    err_com.push_back("");

    vector<string> func_name_list_make_inp = frendy_inp_obj.get_func_name_list_make_inp();
    for(int i=0; i<static_cast<int>(func_name_list_make_inp.size()); i++)
    {
      string str_data = "  " + func_name_list_make_inp[i];
      err_com.push_back(str_data);
    }

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  njoy_input_data.push_back("stop /");

  adjust_comment_data(njoy_input_data, comment_row_number);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MakeInputFromFRENDYtoNJOY::make_input_ace_fast()
{
  if( njoy_module_flg_obj.get_reconr_flg() > 0 )
  {
    make_input_reconr();
  }

  if( njoy_module_flg_obj.get_broadr_flg() > 0 )
  {
    make_input_broadr();
  }

  if( njoy_module_flg_obj.get_gaspr_flg() > 0 )
  {
    make_input_gaspr();
  }

  if( njoy_module_flg_obj.get_heatr_flg() > 0 )
  {
    make_input_heatr();
  }

  if( njoy_module_flg_obj.get_purr_flg() > 0 )
  {
    make_input_purr();
  }

  if( njoy_module_flg_obj.get_acer_flg() > 0 )
  {
    make_input_acer_fast();
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MakeInputFromFRENDYtoNJOY::make_input_ace_therm()
{
  if( njoy_module_flg_obj.get_reconr_flg() > 0 )
  {
    make_input_reconr();
  }

  if( njoy_module_flg_obj.get_broadr_flg() > 0 )
  {
    make_input_broadr();
  }

  if( njoy_module_flg_obj.get_gaspr_flg() > 0 )
  {
    make_input_gaspr();
  }

  if( njoy_module_flg_obj.get_thermr_flg() > 0 )
  {
    make_input_thermr();
  }

  if( njoy_module_flg_obj.get_acer_flg() > 0 )
  {
    make_input_acer_therm();
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MakeInputFromFRENDYtoNJOY::make_input_ace_dosi()
{
  if( njoy_module_flg_obj.get_reconr_flg() > 0 )
  {
    make_input_reconr();
  }

  if( njoy_module_flg_obj.get_broadr_flg() > 0 )
  {
    make_input_broadr();
  }

  if( njoy_module_flg_obj.get_gaspr_flg() > 0 )
  {
    make_input_gaspr();
  }

  if( njoy_module_flg_obj.get_acer_flg() > 0 )
  {
    make_input_acer_dosi();
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MakeInputFromFRENDYtoNJOY::make_input_matxs()
{
  if( njoy_module_flg_obj.get_reconr_flg() > 0 )
  {
    make_input_reconr();
  }

  if( njoy_module_flg_obj.get_broadr_flg() > 0 )
  {
    make_input_broadr();
  }

  if( njoy_module_flg_obj.get_gaspr_flg() > 0 )
  {
    make_input_gaspr();
  }

  if( njoy_module_flg_obj.get_heatr_flg() > 0 )
  {
    make_input_heatr();
  }

  if( njoy_module_flg_obj.get_purr_flg() > 0 )
  {
    make_input_purr();
  }

  if( njoy_module_flg_obj.get_thermr_flg() > 0 )
  {
    make_input_thermr_freegas();
  }

  if( njoy_module_flg_obj.get_groupr_flg() > 0 )
  {
    make_input_groupr();
  }

  if( njoy_module_flg_obj.get_matxsr_flg() > 0 )
  {
    make_input_matxsr();
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MakeInputFromFRENDYtoNJOY::make_input_matxs_tsl()
{
  if( njoy_module_flg_obj.get_reconr_flg() > 0 )
  {
    make_input_reconr();
  }

  if( njoy_module_flg_obj.get_broadr_flg() > 0 )
  {
    make_input_broadr();
  }

  if( njoy_module_flg_obj.get_gaspr_flg() > 0 )
  {
    make_input_gaspr();
  }

  if( njoy_module_flg_obj.get_thermr_flg() > 0 )
  {
    make_input_thermr();
  }

  if( njoy_module_flg_obj.get_groupr_flg() > 0 )
  {
    make_input_groupr();
  }

  if( njoy_module_flg_obj.get_matxsr_flg() > 0 )
  {
    make_input_matxsr();
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MakeInputFromFRENDYtoNJOY::make_input_reconr()
{
  ReconResonanceInputReader  reconr_inp_obj = frendy_inp_obj.get_inp_recon_obj();
  if( reconr_inp_obj.get_process_flg() == frendy_inp_common_obj.skip_process_data )
  {
    //Skip output reconr process
    string class_name = "MakeInputFromFRENDYtoNJOY";
    string func_name  = "make_input_reconr()";

    vector<string> err_com;
    err_com.push_back("The calculation skip flag is on.");
    err_com.push_back("The RECONR process is skipped in the NJOY input file.");
    err_obj.output_caution(class_name, func_name, err_com);

    return;
  }

  njoy_input_data.push_back("reconr /reconr start");
 
  //card 01
  nendf_ori    = get_tape_no(reconr_inp_obj.get_nucl_file_name()[0],  nendf_ori); 
  npend_reconr = get_tape_no(reconr_inp_obj.get_pendf_file_name()[0], npend_reconr); 

  ostringstream nendf_oss, npend_oss;
  nendf_oss << nendf_ori;
  npend_oss << npend_reconr;
  string str_card = nendf_oss.str() + " " + npend_oss.str() + " /card01: nendf npend";
  njoy_input_data.push_back(str_card);

  //card 02
  string tlabel = reconr_inp_obj.get_pendf_label_data()[0];
  if( static_cast<int>(tlabel.size()) == 0 )
  {
    tlabel = "no label data";
  }
  str_card = "'" + tlabel + "' /card02: tlabel";
  njoy_input_data.push_back(str_card);

  //card 03
  ostringstream mat_oss, ncards_oss, ngrid_oss;
  mat_oss    << nucl_data_obj_ori.get_general_data_obj().get_mat_no();
  ncards_oss << static_cast<Integer>(reconr_inp_obj.get_comment_data().size());
  ngrid_oss  << static_cast<Integer>(reconr_inp_obj.get_add_grid_data().size());
  str_card = mat_oss.str() + " " + ncards_oss.str() + " " + ngrid_oss.str() + " /card03: mat ncards ngrid";

  if( static_cast<Integer>(reconr_inp_obj.get_comment_data().size()) == 0 )
  {
    str_card = mat_oss.str() + " " + ncards_oss.str() + " /card03: mat ncards";
    if( static_cast<Integer>(reconr_inp_obj.get_add_grid_data().size()) == 0 )
    {
      str_card = mat_oss.str() + " /card03: mat";
    }
  }
  njoy_input_data.push_back(str_card);

  //card 04
  //tempr  = 0.0
  //FRENDY does not calculate Doppler broadened XS in resonance reconstruction.
  ostringstream err_oss, errmax_oss, errint_oss;
  err_oss.precision(precision);
  errmax_oss.precision(precision);
  errint_oss.precision(precision);
  err_oss.setf(ios::scientific);
  errmax_oss.setf(ios::scientific);
  errint_oss.setf(ios::scientific);
  Real err    = reconr_inp_obj.get_error();
  Real errmax = reconr_inp_obj.get_error_max();
  Real errint = reconr_inp_obj.get_error_integral();

  err_oss    << err;
  errmax_oss << errmax;
  errint_oss << errint;
  str_card = err_oss.str() + " 0.0 " + errmax_oss.str() + " " + errint_oss.str()
           + " /card04: err tempr errmax errint";

  if( fabs((err/20000.0 - errint) / errint) < tolerance_input )
  {
    str_card = err_oss.str() + " 0.0 " + errmax_oss.str() + " /card04: err tempr errmax";

    if( fabs((err*10.0 - errmax) / errmax) < tolerance_input )
    {
      str_card = err_oss.str() + " /card04: err";
    }
  }
  njoy_input_data.push_back(str_card);

  //card 05
  if( static_cast<Integer>(reconr_inp_obj.get_comment_data().size()) > 0 )
  {
    vector<string> cards = reconr_inp_obj.get_comment_data();
    for(int i=0; i<static_cast<int>(cards.size()); i++)
    {
      ostringstream oss01;
      oss01 << i+1;

      if( static_cast<int>(cards[i].size()) == 0 )
      {
        cards[i] = "no card data";
      }
      str_card = "'" + cards[i] + "' /card05: cards " + oss01.str();
      njoy_input_data.push_back(str_card);
    }
  }

  //card06
  if( static_cast<Integer>(reconr_inp_obj.get_add_grid_data().size()) > 0 )
  {
    str_card = "";

    vector<Real> enode = reconr_inp_obj.get_add_grid_data();
    sort(enode.begin(), enode.end());
    for(int i=0; i<static_cast<int>(enode.size()); i++)
    {
      ostringstream enode_oss;
      enode_oss.precision(precision);
      enode_oss.setf(ios::scientific);

      enode_oss << enode[i];
      str_card = str_card + enode_oss.str() + " ";
    }

    str_card = str_card + "/card06: enode";
    njoy_input_data.push_back(str_card);
  }

  njoy_input_data.push_back("0 /reconr end");
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MakeInputFromFRENDYtoNJOY::make_input_broadr()
{
  DopplerBroadeningInputReader broadr_inp_obj = frendy_inp_obj.get_inp_dop_obj();
  if( broadr_inp_obj.get_process_flg() == frendy_inp_common_obj.skip_process_data )
  {
    //Skip output broadr process
    string class_name = "MakeInputFromFRENDYtoNJOY";
    string func_name  = "make_input_broadr()";

    vector<string> err_com;
    err_com.push_back("The calculation skip flag is on.");
    err_com.push_back("The BROADR process is skipped in the NJOY input file.");
    err_obj.output_caution(class_name, func_name, err_com);
    return;
  }

  njoy_input_data.push_back("broadr /broadr start");
 
  //card 01
  npend_broadr = get_tape_no(broadr_inp_obj.get_pendf_file_name()[0], npend_broadr); 

  ostringstream nendf_oss, nin_oss, nout_oss;
  nendf_oss << nendf_ori;
  nin_oss   << npend_reconr;
  nout_oss  << npend_broadr;
  string str_card = nendf_oss.str() + " " + nin_oss.str() + " " + nout_oss.str() + " /card01: nendf nin nout";
  njoy_input_data.push_back(str_card);

  //card 03
  //ntemp2=1, istart=0, istrap=0, temp1=0.0;
  ostringstream mat1_oss, ntemp2_oss;
  mat1_oss   << nucl_data_obj_ori.get_general_data_obj().get_mat_no();
  ntemp2_oss << 1;
  str_card = mat1_oss.str() + " " + ntemp2_oss.str() + " /card02: nmat1 ntemp2";
  njoy_input_data.push_back(str_card);

  //card 03
  ostringstream errthn_oss, thnmax_oss, errmax_oss, errint_oss;
  errthn_oss.precision(precision);
  thnmax_oss.precision(precision);
  errmax_oss.precision(precision);
  errint_oss.precision(precision);
  errthn_oss.setf(ios::scientific);
  thnmax_oss.setf(ios::scientific);
  errmax_oss.setf(ios::scientific);
  errint_oss.setf(ios::scientific);
  
  Real errthn = broadr_inp_obj.get_error();
  Real errmax = broadr_inp_obj.get_error_max();
  Real errint = broadr_inp_obj.get_error_integral();
  errthn_oss << errthn;
  thnmax_oss << search_thn_max();
  errmax_oss << errmax;
  errint_oss << errint;
  str_card = errthn_oss.str() + " " + thnmax_oss.str() + " " + errmax_oss.str() + " " + errint_oss.str()
           + " /card03: errthn thnmax errmax errint";

  if( fabs((errthn/20000.0 - errint) / errint) < tolerance_input )
  {
    str_card = errthn_oss.str() + " " + thnmax_oss.str() + " " + errmax_oss.str()
             + " /card03: errthn thnmax errmax";

    if( fabs((errthn*10.0 - errmax) / errmax) < tolerance_input )
    {
      str_card = errthn_oss.str() + " " + thnmax_oss.str() + " /card03: errthn thnmax";
    }
  }
  njoy_input_data.push_back(str_card);

  //card 04
  ostringstream temp2_oss;
  temp2_oss.precision(precision);
  temp2_oss.setf(ios::scientific);
  temp2_oss << broadr_inp_obj.get_temp();
  str_card = temp2_oss.str() + " /card04: temp2";
  njoy_input_data.push_back(str_card);

  njoy_input_data.push_back("0 /broadr end");
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MakeInputFromFRENDYtoNJOY::make_input_gaspr()
{
  GasProductionInputReader gaspr_inp_obj = frendy_inp_obj.get_inp_gas_xs_obj();
  if( gaspr_inp_obj.get_process_flg() == frendy_inp_common_obj.skip_process_data )
  {
    //Skip output gaspr process
    string class_name = "MakeInputFromFRENDYtoNJOY";
    string func_name  = "make_input_gaspr()";

    vector<string> err_com;
    err_com.push_back("The calculation skip flag is on.");
    err_com.push_back("The GASPR process is skipped in the NJOY input file.");
    err_obj.output_caution(class_name, func_name, err_com);
    return;
  }

  njoy_input_data.push_back("gaspr /gaspr start");
 
  //card 01
  npend_gaspr = get_tape_no(gaspr_inp_obj.get_pendf_file_name()[0], npend_gaspr); 

  ostringstream nendf_oss, nin_oss, nout_oss;
  nendf_oss << nendf_ori;
  nin_oss   << npend_broadr;
  nout_oss  << npend_gaspr;
  string str_card = nendf_oss.str() + " " + nin_oss.str() + " " + nout_oss.str() + " /card01: nendf nin nout";
  njoy_input_data.push_back(str_card);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MakeInputFromFRENDYtoNJOY::make_input_purr()
{
  ProbTableInputReader purr_inp_obj = frendy_inp_obj.get_inp_prob_table_obj();
  if( purr_inp_obj.get_process_flg() == frendy_inp_common_obj.skip_process_data )
  {
    //Skip output purr process
    string class_name = "MakeInputFromFRENDYtoNJOY";
    string func_name  = "make_input_purr()";

    vector<string> err_com;
    err_com.push_back("The calculation skip flag is on.");
    err_com.push_back("The PURR process is skipped in the NJOY input file.");
    err_obj.output_caution(class_name, func_name, err_com);
    return;
  }

  njoy_input_data.push_back("purr /purr start");
 
  //card 01
  npend_purr = get_tape_no(purr_inp_obj.get_pendf_file_name()[0], npend_purr); 

  ostringstream nendf_oss, nin_oss, nout_oss;
  nendf_oss << nendf_ori;
  nin_oss   << npend_gaspr;
  nout_oss  << npend_purr;
  string str_card = nendf_oss.str() + " " + nin_oss.str() + " " + nout_oss.str() + " /card01: nendf nin nout";
  njoy_input_data.push_back(str_card);

  //card 02
  ostringstream matd_oss, ntemp_oss, nsigz_oss, nbin_oss, nladr_oss, iprint_oss;
  matd_oss   << nucl_data_obj_ori.get_general_data_obj().get_mat_no();
  ntemp_oss  << 1;
  nsigz_oss  << static_cast<Integer>(purr_inp_obj.get_sigma_zero_data().size());
  nbin_oss   << purr_inp_obj.get_probability_bin_no();
  nladr_oss  << purr_inp_obj.get_ladder_no();
  iprint_oss << purr_inp_obj.get_print_set_data_flg();
  //nunx_oss   << 0;
  str_card = matd_oss.str() + " " + ntemp_oss.str() + " " + nsigz_oss.str() + " " + nbin_oss.str()
           + " " + nladr_oss.str() + " " + iprint_oss.str() + " /card02: matd ntemp nsigz nbin nladr iprint";
  njoy_input_data.push_back(str_card);

  //card 03
  ostringstream temp_oss;
  temp_oss.precision(precision);
  temp_oss.setf(ios::scientific);
  temp_oss << frendy_inp_obj.get_inp_dop_obj().get_temp();
  str_card = temp_oss.str() + " /card03: temp";
  njoy_input_data.push_back(str_card);

  //card 04
  vector<Real> sigz = purr_inp_obj.get_sigma_zero_data();
  sort(sigz.rbegin(), sigz.rend());

  str_card = "";
  for(int i=0; i<static_cast<int>(sigz.size()); i++)
  {
    ostringstream sigz_oss;
    sigz_oss.precision(precision);
    sigz_oss.setf(ios::scientific);

    sigz_oss << sigz[i];
    str_card = str_card + sigz_oss.str() + " ";
  }
  str_card = str_card + "/card04: sigz";
  njoy_input_data.push_back(str_card);

  njoy_input_data.push_back("0 /purr end");
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MakeInputFromFRENDYtoNJOY::make_input_thermr()
{
  ThermalScatterInputReader thermr_inp_obj = frendy_inp_obj.get_inp_thermal_scatter_obj();

  ThermalScatterMatList tsl_mat_list;
  vector<ThermalScatterMatData> tsl_data = tsl_mat_list.get_thermal_scat_data(nucl_data_obj_tsl.get_general_data_obj().get_mat_no());

  int ele_no = -1;
  if( static_cast<int>(tsl_data.size()) == 1 )
  {
    ele_no = 0;
  }
  else if( static_cast<int>(tsl_data.size()) == 0 )
  {
    string class_name = "MakeInputFromFRENDYtoNJOY";
    string func_name  = "make_input_thermr()";

    vector<string> err_com;

    ostringstream oss01;
    oss01 << nucl_data_obj_tsl.get_general_data_obj().get_mat_no();
    string str_data01 = "Material number of TSL : " + oss01.str();
    err_com.push_back(str_data01);
    err_com.push_back("This material number is not available in this program.");
    err_com.push_back("Please check your input file, nuclear data file, and FrendyUtils/ThermalScatterMatList.cpp.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
  else if( static_cast<int>(tsl_data.size()) > 1 )
  {
    Integer mat_nucl = nucl_data_obj_ori.get_general_data_obj().get_mat_no();
    for(int i=0; i<static_cast<int>(tsl_data.size()); i++)
    {
      if( mat_nucl/100 == tsl_data[i].get_mat_no_principal() / 100 )
      {
        ele_no = i;
        break;
      }
    }

    string class_name = "MakeInputFromFRENDYtoNJOY";
    string func_name  = "make_input_thermr()";

    vector<string> err_com;
    if( ele_no < 0 )
    {
      err_com.push_back("Material number of nucleus is different to FRENDY data from");
      err_com.push_back("FrendyUtils/ThermalScatterMatList.cpp.");
      err_com.push_back("The nuleus data may be inappropriate.");
      err_com.push_back("The first material number from ThermalScatterMatList is used for the material number.");
      err_com.push_back("Please check your input file and nuclear data file.");

      ele_no = 0;
    }
    else
    {
      err_com.push_back("Material number of nucleus is duplicated.");
      err_com.push_back("The first material number from ThermalScatterMatList is used for the material number.");
      err_com.push_back("Please check your input file, nuclear data file, and FrendyUtils/ThermalScatterMatList.cpp.");
    }

    ostringstream oss01;
    oss01 << mat_nucl;
    string str_data01 = "  Material number of nucleus : " + oss01.str();
    err_com.push_back(str_data01);

    err_com.push_back("  Material name / number from ThermalScatterMatList : ");
    for(int i=0; i<static_cast<int>(tsl_data.size()); i++)
    {
      ostringstream oss02;
      oss02 << static_cast<Integer>(tsl_data[i].get_mat_no_principal());
      string str_data02 = "    " + tsl_data[i].get_mat_name() + " / " + oss02.str();
      err_com.push_back(str_data02);
    }
    err_obj.output_caution(class_name, func_name, err_com);
  }


  mt_tsl_iin  = 0;
  mt_tsl_icoh = 0;
  if( get_inelastic_options_tsl() != 0 )
  {
    mt_tsl_iin = tsl_data[ele_no].get_mt_no();
  }
  if( get_elastic_options_tsl() != 0 )
  {
    mt_tsl_icoh = mt_tsl_iin + 1;
  }

  if( thermr_inp_obj.get_process_flg() == frendy_inp_common_obj.skip_process_data )
  {
    //Skip output thermr process
    string class_name = "MakeInputFromFRENDYtoNJOY";
    string func_name  = "make_input_thermr()";

    vector<string> err_com;
    err_com.push_back("The calculation skip flag is on.");
    err_com.push_back("The THERMR process is skipped in the NJOY input file.");
    err_obj.output_caution(class_name, func_name, err_com);
    return;
  }

  njoy_input_data.push_back("thermr /thermr start");
 
  //card 01
  npend_thermr = get_tape_no(thermr_inp_obj.get_pendf_file_name()[0], npend_thermr);

  ostringstream nendf_oss, nin_oss, nout_oss;
  nendf_oss << nendf_tsl;
  nin_oss   << npend_gaspr;
  nout_oss  << npend_thermr;
  string str_card = nendf_oss.str() + " " + nin_oss.str() + " " + nout_oss.str() + " /card01: nendf nin nout";
  njoy_input_data.push_back(str_card);

  //card 02
  //Input parameter of NJOY99 is different. NJOY99 does not need iform option.
  ostringstream matde_oss, matdp_oss, nbin_oss, ntemp_oss, iin_oss, icoh_oss, iform_oss, natom_oss,
                mtref_oss;
  matde_oss << nucl_data_obj_tsl.get_general_data_obj().get_mat_no();
  matdp_oss << nucl_data_obj_ori.get_general_data_obj().get_mat_no();
  nbin_oss  << thermr_inp_obj.get_equi_probable_angle_no();
  ntemp_oss << 1;
  iin_oss   << get_inelastic_options_tsl();
  icoh_oss  << get_elastic_options_tsl();
  iform_oss << 0;
  natom_oss << get_atom_no_principal_tsl(ele_no);
  mtref_oss << mt_tsl_iin;
  str_card = matde_oss.str() + " " + matdp_oss.str() + " " + nbin_oss.str() + " " + ntemp_oss.str()
           + " " + iin_oss.str() + " " + icoh_oss.str() + " " + iform_oss.str() + " "
           + natom_oss.str() + " " + mtref_oss.str()
           + " /card02: matde matdp nbin ntemp iin icoh iform natom mtref";
  njoy_input_data.push_back(str_card);

  //card 03
  ostringstream tempr_oss;
  tempr_oss.precision(precision);
  tempr_oss.setf(ios::scientific);
  tempr_oss << frendy_inp_obj.get_inp_dop_obj().get_temp();
  str_card = tempr_oss.str() + " /card03: tempr";
  njoy_input_data.push_back(str_card);

  //card 04
  ostringstream tol_oss, emax_oss;
  tol_oss.precision(precision);
  emax_oss.precision(precision);
  tol_oss.setf(ios::scientific);
  emax_oss.setf(ios::scientific);
  tol_oss  << thermr_inp_obj.get_error();
  emax_oss << get_max_thermal_ene();
  str_card = tol_oss.str() + " " + emax_oss.str() + " /card04: tol emax";
  njoy_input_data.push_back(str_card);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MakeInputFromFRENDYtoNJOY::make_input_thermr_freegas()
{
  ThermalScatterInputReader thermr_inp_obj = frendy_inp_obj.get_inp_thermal_scatter_obj();

  njoy_input_data.push_back("thermr /thermr start");
 
  ostringstream nendf_oss, nin_oss, nout_oss;
  nendf_oss << 0;
  nin_oss   << npend_purr;
  nout_oss  << npend_thermr;
  string str_card = nendf_oss.str() + " " + nin_oss.str() + " " + nout_oss.str() + " /card01: nendf nin nout";
  njoy_input_data.push_back(str_card);

  //card 02
  //Input parameter of NJOY99 is different. NJOY99 does not need iform option.
  ostringstream matde_oss, matdp_oss, nbin_oss, ntemp_oss, iin_oss, icoh_oss, iform_oss, natom_oss,
                mtref_oss;
  matde_oss << nucl_data_obj_ori.get_general_data_obj().get_mat_no();
  matdp_oss << nucl_data_obj_ori.get_general_data_obj().get_mat_no();
  nbin_oss  << thermr_inp_obj.get_equi_probable_angle_no();
  ntemp_oss << 1;
  iin_oss   << 1;
  icoh_oss  << 0;
  iform_oss << 0;
  natom_oss << 1;
  mtref_oss << 221;
  str_card = matde_oss.str() + " " + matdp_oss.str() + " " + nbin_oss.str() + " " + ntemp_oss.str()
           + " " + iin_oss.str() + " " + icoh_oss.str() + " " + iform_oss.str() + " "
           + natom_oss.str() + " " + mtref_oss.str()
           + " /card02: matde matdp nbin ntemp iin icoh iform natom mtref";
  njoy_input_data.push_back(str_card);

  mt_tsl_iin  = 221;
  mt_tsl_icoh = 0;

  //card 03
  ostringstream tempr_oss;
  tempr_oss.precision(precision);
  tempr_oss.setf(ios::scientific);
  tempr_oss << frendy_inp_obj.get_inp_dop_obj().get_temp();
  str_card = tempr_oss.str() + " /card03: tempr";
  njoy_input_data.push_back(str_card);

  //card 04
  ostringstream tol_oss, emax_oss;
  tol_oss.precision(precision);
  emax_oss.precision(precision);
  tol_oss.setf(ios::scientific);
  emax_oss.setf(ios::scientific);
  tol_oss  << thermr_inp_obj.get_error();
  emax_oss << frendy_inp_common_obj.get_max_thermal_ene_in_def();
  str_card = tol_oss.str() + " " + emax_oss.str() + " /card04: tol emax";
  njoy_input_data.push_back(str_card);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MakeInputFromFRENDYtoNJOY::make_input_acer_common(Integer iopt)
{
  AceDataGeneratorInputReader acer_inp_obj = frendy_inp_obj.get_inp_ace_obj();
  if( acer_inp_obj.get_process_flg() == frendy_inp_common_obj.skip_process_data )
  {
    //Skip output acer process
    string class_name = "MakeInputFromFRENDYtoNJOY";
    string func_name  = "make_input_acer_common(Integer iopt)";

    vector<string> err_com;
    err_com.push_back("The calculation skip flag is on.");
    err_com.push_back("The ACER process is skipped in the NJOY input file.");
    err_obj.output_caution(class_name, func_name, err_com);
    return;
  }

  njoy_input_data.push_back("acer /acer start");
 
  //card 01
  Integer nendf = nendf_ori;
  Integer npend = npend_purr;
  if( iopt == 2 )
  {
    nendf = nendf_tsl;
    npend = npend_thermr;
  }

  ostringstream nendf_oss, npend_oss, ngend_oss, nace_oss, ndir_oss;
  nendf_oss << nendf;
  npend_oss << npend;
  ngend_oss << 0;
  nace_oss  << get_tape_no(acer_inp_obj.get_ace_file_name()[0], nace);
  ndir_oss  << get_tape_no(acer_inp_obj.get_ace_dir_file_name()[0], nacedir);
  string str_card = nendf_oss.str() + " " + npend_oss.str() + " " + ngend_oss.str() + " "
                  + nace_oss.str() + " " + ndir_oss.str() + " /card01: nendf npend ngend nace ndir";
  njoy_input_data.push_back(str_card);

  //card 02
  Integer nxtra = static_cast<Integer>(acer_inp_obj.get_iz_aw_data().size());
  if( nxtra > 0 )
  {
    nxtra = static_cast<Integer>(acer_inp_obj.get_iz_aw_data()[0].size());
  }

  ostringstream iopt_oss, iprint_oss, itype_oss, nxtra_oss, suff_oss;
  suff_oss.precision(precision);
  suff_oss.setf(ios::scientific);
  iopt_oss   << iopt;
  iprint_oss << 1;
  itype_oss  << 1;
  suff_oss   << acer_inp_obj.get_suffix_id();
  nxtra_oss  << nxtra;
  str_card = iopt_oss.str() + " " + iprint_oss.str() + " " + itype_oss.str() + " " +  suff_oss.str()
           + " " + nxtra_oss.str() + " /card02: iopt iprint itype suff nxtra";
  njoy_input_data.push_back(str_card);

  //card 03
  string hk = acer_inp_obj.get_ace_label_data()[0];
  if( static_cast<int>(hk.size()) == 0 )
  {
    hk = "no label data";
  }
  str_card = "'" + hk + "' /card03: hk";
  njoy_input_data.push_back(str_card);

  //card 04
  if( nxtra > 0 )
  {
    for(int i=0; i<static_cast<int>(acer_inp_obj.get_iz_aw_data()[0].size()); i++)
    {
      ostringstream iz_oss, aw_oss;
      aw_oss.precision(precision);
      aw_oss.setf(ios::scientific);

      iz_oss << static_cast<Integer>(acer_inp_obj.get_iz_aw_data()[0][i]);
      aw_oss <<                      acer_inp_obj.get_iz_aw_data()[1][i];
      str_card = iz_oss.str() + " " + aw_oss.str() + " ";
    }
    str_card = str_card + "/card04: iz, aw";
    njoy_input_data.push_back(str_card);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MakeInputFromFRENDYtoNJOY::make_input_acer_fast()
{
  make_input_acer_common(1);

  AceDataGeneratorInputReader acer_inp_obj = frendy_inp_obj.get_inp_ace_obj();
  if( acer_inp_obj.get_process_flg() == frendy_inp_common_obj.skip_process_data )
  {
    //Skip output acer process
    return;
  }

  //card 05
  ostringstream matd_oss, tempd_oss;
  tempd_oss.precision(precision);
  tempd_oss.setf(ios::scientific);
  matd_oss  << nucl_data_obj_ori.get_general_data_obj().get_mat_no();
  tempd_oss << frendy_inp_obj.get_inp_dop_obj().get_temp();
  string str_card = matd_oss.str() + " " + tempd_oss.str() + " /card05: matd tempd";
  njoy_input_data.push_back(str_card);

  //card 06
  ostringstream newfor_oss;
  newfor_oss << acer_inp_obj.get_cumulative_angle_distribution_format();
  str_card = newfor_oss.str() + " /card06: newfor";
  njoy_input_data.push_back(str_card);

  //card 07
  //no thinning (skip card 07)
  //njoy_input_data.push_back("/card07: thin (no thinning)");

  njoy_input_data.push_back("/acer end");
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MakeInputFromFRENDYtoNJOY::make_input_acer_therm()
{
  make_input_acer_common(2);

  AceDataGeneratorInputReader acer_inp_obj = frendy_inp_obj.get_inp_ace_obj();
  if( acer_inp_obj.get_process_flg() == frendy_inp_common_obj.skip_process_data )
  {
    //Skip output acer process
    return;
  }

  //card 08
  ThermalScatterMatList tsl_mat_list;
  vector<ThermalScatterMatData> tsl_data = tsl_mat_list.get_thermal_scat_data(nucl_data_obj_tsl.get_general_data_obj().get_mat_no());

  Integer mat_nucl = nucl_data_obj_ori.get_general_data_obj().get_mat_no();

  int ele_no = -1;
  if( static_cast<int>(tsl_data.size()) == 1 )
  {
    ele_no = 0;
  }
  else if( static_cast<int>(tsl_data.size()) == 0 )
  {
    string class_name = "MakeInputFromFRENDYtoNJOY";
    string func_name  = "make_input_acer_therm()";

    vector<string> err_com;

    ostringstream oss01;
    oss01 << nucl_data_obj_tsl.get_general_data_obj().get_mat_no();
    string str_data01 = "Material number of TSL : " + oss01.str();
    err_com.push_back(str_data01);
    err_com.push_back("This material number is not available in this program.");
    err_com.push_back("Please check your input file, nuclear data file, and FrendyUtils/ThermalScatterMatList.cpp.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
  else if( static_cast<int>(tsl_data.size()) > 1 )
  {
    for(int i=0; i<static_cast<int>(tsl_data.size()); i++)
    {
      if( mat_nucl/100 == tsl_data[i].get_mat_no_principal() / 100 )
      {
        ele_no = i;
        break;
      }
    }

    string class_name = "MakeInputFromFRENDYtoNJOY";
    string func_name  = "make_input_acer_therm()";

    vector<string> err_com;
    if( ele_no < 0 )
    {
      err_com.push_back("Material number of nucleus is different to FRENDY data from");
      err_com.push_back("FrendyUtils/ThermalScatterMatList.cpp.");
      err_com.push_back("The nuleus data may be inappropriate.");
      err_com.push_back("The first material number from ThermalScatterMatList is used for the material number.");
      err_com.push_back("Please check your input file and nuclear data file.");

      ele_no = 0;
    }
    else
    {
      err_com.push_back("Material number of nucleus is duplicated.");
      err_com.push_back("The first material number from ThermalScatterMatList is used for the material number.");
      err_com.push_back("Please check your input file, nuclear data file, and FrendyUtils/ThermalScatterMatList.cpp.");
    }

    ostringstream oss01;
    oss01 << mat_nucl;
    string str_data01 = "  Material number of nucleus : " + oss01.str();
    err_com.push_back(str_data01);

    err_com.push_back("  Material name / number from ThermalScatterMatList : ");
    for(int i=0; i<static_cast<int>(tsl_data.size()); i++)
    {
      ostringstream oss02;
      oss02 << static_cast<Integer>(tsl_data[i].get_mat_no_principal());
      string str_data02 = "    " + tsl_data[i].get_mat_name() + " / " + oss02.str();

      if( i == ele_no )
      {
        str_data02 = str_data02 + " *** use this data ***";
      }
      err_com.push_back(str_data02);
    }
    err_obj.output_caution(class_name, func_name, err_com);
  }


  Integer mat_tsl_list = static_cast<Integer>(tsl_data[ele_no].get_mat_no_principal());
  if( mat_tsl_list != mat_nucl )
  {
    string class_name = "MakeInputFromFRENDYtoNJOY";
    string func_name  = "make_input_acer_therm()";

    vector<string> err_com;
    ostringstream oss01, oss02;
    oss01 << mat_nucl;
    oss02 << mat_tsl_list;
    string str_data01 = "  material number from nuclear data file     : " + oss01.str();
    string str_data02 = "  material number from ThermalScatterMatList : " + oss02.str();

    err_com.push_back("The material number from nuclear data file is different to that from");
    err_com.push_back("ThermalScatterMatList class.");
    err_com.push_back("The material number for nuclear data file is used for matd in ACER/card 8.");

    if( mat_tsl_list/100 != mat_nucl/100 )
    {
      err_com.push_back("Nuclear data file or input file may be incorrect.");
    }

    err_com.push_back("Please check your input file.");
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);

    err_obj.output_caution(class_name, func_name, err_com);
  }

  ostringstream matd_oss, tempd_oss;
  tempd_oss.precision(precision);
  tempd_oss.setf(ios::scientific);
  matd_oss  << mat_nucl;
  tempd_oss << frendy_inp_obj.get_inp_dop_obj().get_temp();

  string  tname = acer_inp_obj.get_thermal_za_id_name();
  if( static_cast<int>(tname.size()) == 0 )
  {
    tname = "za_id";
  }

  string str_card = matd_oss.str() + " " + tempd_oss.str() + " '" + tname + "' /card08: matd tempd tname";
  njoy_input_data.push_back(str_card);

  //card 08a
  str_card = "";
  if( static_cast<int>(acer_inp_obj.get_moderator_za_data().size()) > 0 )
  {
    for(int i=0; i<static_cast<int>(acer_inp_obj.get_moderator_za_data().size()); i++)
    {
      ostringstream iza_oss;
      iza_oss << static_cast<Integer>(acer_inp_obj.get_moderator_za_data()[i]);
      str_card = str_card + iza_oss.str() + " ";
    }
  }
  else
  {
    vector<Integer> iza_vec;
    iza_vec = get_moderator_za_data(nucl_data_obj_tsl, nucl_data_obj_ori, ele_no);

    for(int i=0; i<static_cast<int>(iza_vec.size()); i++)
    {
      ostringstream iza_oss;
      iza_oss << iza_vec[i];
      str_card = str_card + iza_oss.str() + " ";
    }
  }
  str_card = str_card + "/card08a: iza";
  njoy_input_data.push_back(str_card);
 
  //card 09
  ThermalScatterInputReader thermr_inp_obj = frendy_inp_obj.get_inp_thermal_scatter_obj();
  int mte   = mt_tsl_icoh;
  int ielas = check_elastic_scattering_tsl();
  if( ielas < 0 )
  {
    ielas = 0;
    mte   = 0;
  }

  ostringstream mti_oss, nbint_oss, mte_oss, ielas_oss, nmix_oss, emax_oss, iwt_oss;
  emax_oss.precision(precision);
  emax_oss.setf(ios::scientific);
  mti_oss   << mt_tsl_iin;
  nbint_oss << acer_inp_obj.get_equi_probable_angle_no();
  mte_oss   << mte;
  ielas_oss << ielas;
  nmix_oss  << get_atom_no_mix_tsl(ele_no);
  emax_oss  << get_max_thermal_ene();
  iwt_oss   << acer_inp_obj.get_weight_option();
  str_card = mti_oss.str() + " " + nbint_oss.str() + " " + mte_oss.str() + " " + ielas_oss.str()
           + " " + nmix_oss.str() + " " + emax_oss.str() + " " + iwt_oss.str()
           + " /card09: mti nbint mte ielas nmix emax iwt";
  njoy_input_data.push_back(str_card);

  //njoy_input_data.push_back("/acer end");
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<Integer> MakeInputFromFRENDYtoNJOY::get_moderator_za_data(NuclearDataObject& nucl_obj_tsl,
                                                                 NuclearDataObject& nucl_obj, int ele_no)
{
  Integer mat_no_benz   = 40;
  Integer mat_no_beo    = 27;
  Integer mat_no_sio2_a = 47;
  Integer mat_no_sio2_b = 49;

  ThermalScatterMatList tsl_mat_list;
  ThermalScatterMatData tsl_data_benz   = tsl_mat_list.get_thermal_scat_data(mat_no_benz)[0];    //Benzene
  ThermalScatterMatData tsl_data_beo    = tsl_mat_list.get_thermal_scat_data(mat_no_beo)[0];     //BeO
  ThermalScatterMatData tsl_data_sio2_a = tsl_mat_list.get_thermal_scat_data(mat_no_sio2_a)[0];  //SiO2-alpha
  ThermalScatterMatData tsl_data_sio2_b = tsl_mat_list.get_thermal_scat_data(mat_no_sio2_b)[0];  //SiO2-beta

  Integer mat_no_tsl = nucl_obj_tsl.get_general_data_obj().get_mat_no();
  ThermalScatterMatData tsl_data = tsl_mat_list.get_thermal_scat_data(mat_no_tsl)[ele_no];

  if( tsl_data_benz.get_mat_no_principal() != 125 || tsl_data_benz.get_mat_no_non_principal() / 100 != 6 )
  {
    string class_name = "MakeInputFromFRENDYtoNJOY";
    string func_name  = "get_moderator_za_data";

    vector<string> err_com;
    err_com.push_back("This function considers that mat number 40 is H in benzene.");
    err_com.push_back("However, mat_no_principal and mat_no_non_principal is not identical to H in benzene data.");
    err_com.push_back("Please check FrendyUtils/ThermalScatterMatList.cpp");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  if( tsl_data_beo.get_mat_no_principal() != 425 || tsl_data_beo.get_mat_no_non_principal() != 825 )
  {
    string class_name = "MakeInputFromFRENDYtoNJOY";
    string func_name  = "get_moderator_za_data";

    vector<string> err_com;
    err_com.push_back("This function considers that mat number 27 is BeO.");
    err_com.push_back("However, mat_no_principal and mat_no_non_principal is not identical to BeO data.");
    err_com.push_back("Please check FrendyUtils/ThermalScatterMatList.cpp");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }


  if( tsl_data_sio2_a.get_mat_no_principal() / 100 != 14 || tsl_data_sio2_a.get_mat_no_non_principal() / 100 != 8 ||
      tsl_data_sio2_b.get_mat_no_principal() / 100 != 14 || tsl_data_sio2_b.get_mat_no_non_principal() / 100 != 8 )
  {
    string class_name = "MakeInputFromFRENDYtoNJOY";
    string func_name  = "get_moderator_za_data";

    vector<string> err_com;
    err_com.push_back("This function considers that mat number 47 is SiO2-alpha and 49 is SiO2-beta.");
    err_com.push_back("However, mat_no_principal and mat_no_non_principal is not identical to SiO2 data.");
    err_com.push_back("Please check FrendyUtils/ThermalScatterMatList.cpp");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  vector<Integer> iza_vec;
  iza_vec.clear();

  Integer mat_data_principal = get_mat_data_principal(nucl_obj_tsl, nucl_obj);
  iza_vec.push_back(mat_data_principal);

  if( mat_no_tsl == mat_no_benz )
  {
    iza_vec.push_back(tsl_data_benz.get_mat_data_non_principal());
  }
  else if( mat_no_tsl == mat_no_sio2_a )
  {
    iza_vec.push_back(tsl_data_sio2_a.get_mat_data_non_principal());
  }
  else if( mat_no_tsl == mat_no_sio2_b )
  {
    iza_vec.push_back(tsl_data_sio2_b.get_mat_data_non_principal());
  }
  else if( mat_no_tsl == mat_no_beo )
  {
    string class_name = "MakeInputFromFRENDYtoNJOY";
    string func_name  = "get_moderator_za_data";

    vector<string> err_com;
    err_com.push_back("BeO has two different data.");
    err_com.push_back("One is  Be in BeO for ENDF/B-VIII.0 and another is BeO for JENDL-4.0.");
    err_com.push_back("Since the material number is identical, FRENDY can not identify.");
    err_com.push_back("If this material data is BeO, you should change moderator_za_id_name");
    err_com.push_back("(iza01 and iza02 in ACER/card 8a) and atom type no (nmiz in ACER/card 9)");
    err_com.push_back(" as follows:");
    err_com.push_back("  moderator_za_id_name ( 4009  8016 )");
    err_com.push_back("  atom_type_no         ( 2 )");

    err_obj.output_caution(class_name, func_name, err_com);
  }
  else if( tsl_data.get_atom_no_mix() > 1 )
  {
    string class_name = "MakeInputFromFRENDYtoNJOY";
    string func_name  = "get_moderator_za_data";

    vector<string> err_com;
    ostringstream oss01, oss02;
    oss01 << mat_no_tsl;
    oss02 << tsl_data.get_atom_no_mix();
    string str_data01 = "material number : " + oss01.str();
    string str_data02 = "atom_no_mix     : " + oss02.str();
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("");
   
    err_com.push_back("atom_no_mix in ThermalScatterMatData is larger than 1.");
    if ( (tsl_data.get_mat_no_principal() / 100 == 14 && tsl_data.get_mat_no_non_principal() / 100 ==  8)
      || (tsl_data.get_mat_no_principal() / 100 ==  8 && tsl_data.get_mat_no_non_principal() / 100 == 14) )
    {
      err_com.push_back("FRENDY considers that this material data might not mixed moderator.");
      err_com.push_back("Please check the processing results (compare the elastic scattering cross section).");
      err_obj.output_caution(class_name, func_name, err_com);
    }
    else
    {
      err_com.push_back("FRENDY considers that this material data is not mixed moderator.");
      err_com.push_back("Please check FrendyUtils/ThermalScatterMatList.cpp.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }

  for(int i=0; i<static_cast<int>(iza_vec.size()); i++)
  {
    Integer mat_data_principal_int = static_cast<Integer>(round(iza_vec[i]));
    Integer mat_data_principal_mod = static_cast<Integer>(round(iza_vec[i]/1000.0));
    mat_data_principal_mod *= 1000;
    if( mat_data_principal_int == mat_data_principal_mod) //AAA000
    {
      string class_name = "MakeInputFromFRENDYtoNJOY";
      string func_name  = "get_moderator_za_data";

      vector<string> err_com;
      ostringstream oss01;
      oss01 << mat_data_principal_int;
      string str_data01;
      if( i==0 )
      {
        str_data01 = "First material data : " + oss01.str();
      }
      else if( i==1 )
      {
        str_data01 = "Second material data : " + oss01.str();
      }
      else if( i==2 )
      {
        str_data01 = "Third material data : " + oss01.str();
      }
      else if( i>2 )
      {
        ostringstream oss02;
        oss02 << i+1;
        str_data01 = oss02.str() + "th material data : " + oss01.str();
      }
      err_com.push_back("The mass number of material data (moderator_za_data, iza in ACER/card 8a) is zero.");
      err_com.push_back("Please modify mass number by your self.");
      err_com.push_back(str_data01);
  
      err_obj.output_caution(class_name, func_name, err_com);
    }
  }

  return iza_vec;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Integer MakeInputFromFRENDYtoNJOY::get_mat_data_principal(NuclearDataObject& nucl_obj_tsl, 
                                                          NuclearDataObject& nucl_obj)
{
  Integer mat_no_tsl = nucl_obj_tsl.get_general_data_obj().get_mat_no();

  ThermalScatterMatList tsl_mat_list;
  vector<ThermalScatterMatData> tsl_data = tsl_mat_list.get_thermal_scat_data(mat_no_tsl);

  Integer za_val = static_cast<Integer>(round(nucl_obj.get_general_data_obj().get_mat_data()));

  int i_max = static_cast<int>(tsl_data.size());
  if( i_max == 0 )
  {
    string class_name = "MakeInputFromFRENDYtoNJOY";
    string func_name  = "get_mat_data_principal";

    vector<string> err_com;

    ostringstream oss01;
    oss01 << mat_no_tsl;
    string str_data01 = "Material number of TSL : " + oss01.str();
    err_com.push_back(str_data01);
    err_com.push_back("This material number is not available in this program.");
    err_com.push_back("MAT number for principal atom is set as 0.");
    err_com.push_back("Please check your input file, nuclear data file, and FrendyUtils/ThermalScatterMatList.cpp.");

    err_obj.output_caution(class_name, func_name, err_com);

    return 0;
  }

  vector<int> pos_vec;
  for(int i=0; i<i_max; i++)
  {
    Integer mat_data_principal = static_cast<Integer>(tsl_data[i].get_mat_data_principal());

    if( mat_data_principal/1000 == za_val/1000 )
    {
      pos_vec.push_back(i);
    }
  }

  if( static_cast<int>(pos_vec.size()) != 1 )
  {
    string class_name = "MakeInputFromFRENDYtoNJOY";
    string func_name  = "get_mat_data_principal";

    vector<string> err_com;
    Integer mat_data_principal = static_cast<Integer>(tsl_data[0].get_mat_data_principal());
    if( static_cast<int>(pos_vec.size()) == 0 )
    {
      err_com.push_back("Material number of nucleus is different to FRENDY data from");
      err_com.push_back("FrendyUtils/ThermalScatterMatList.cpp.");
      err_com.push_back("The nuleus data may be inappropriate.");
      err_com.push_back("The first material number from ThermalScatterMatList is used for the material number.");
      err_com.push_back("Please check your input file and nuclear data file.");
    }
    else
    {
      mat_data_principal =  static_cast<Integer>(tsl_data[pos_vec[0]].get_mat_data_principal());

      err_com.push_back("Material number of nucleus is duplicated.");
      err_com.push_back("The first material number from ThermalScatterMatList is used for the material number.");
      err_com.push_back("Please check your input file, nuclear data file, and FrendyUtils/ThermalScatterMatList.cpp.");
    }

    ostringstream oss01;
    oss01 << za_val;
    string str_data01 = "  Material number of nucleus                 : " + oss01.str();
    err_com.push_back(str_data01);

    err_com.push_back("  Material name / number from ThermalScatterMatList : ");
    for(int i=0; i<i_max; i++)
    {
      ostringstream oss02;
      oss02 << static_cast<Integer>(tsl_data[i].get_mat_data_principal());
      string str_data02 = "    " + tsl_data[i].get_mat_name() + " / " + oss02.str();

      if( static_cast<int>(pos_vec.size()) == 0 && i == 0 )
      {
        str_data02 = str_data02 + " *** use this data ***";
      }
      if( static_cast<int>(pos_vec.size()) > 0 )
      {
        if( i == pos_vec[0] )
        {
          str_data02 = str_data02 + " *** use this data ***";
        }
      }
      err_com.push_back(str_data02);
    }

    err_obj.output_caution(class_name, func_name, err_com);

    return mat_data_principal;
  }

  return za_val;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MakeInputFromFRENDYtoNJOY::make_input_acer_dosi()
{
  make_input_acer_common(3);

  AceDataGeneratorInputReader acer_inp_obj = frendy_inp_obj.get_inp_ace_obj();
  if( acer_inp_obj.get_process_flg() == frendy_inp_common_obj.skip_process_data )
  {
    //Skip output acer process
    return;
  }

  //card 10
  ostringstream matd_oss, tempd_oss;
  tempd_oss.precision(precision);
  tempd_oss.setf(ios::scientific);
  matd_oss  << nucl_data_obj_ori.get_general_data_obj().get_mat_no();
  tempd_oss << frendy_inp_obj.get_inp_dop_obj().get_temp();

  string str_card = matd_oss.str() + " " + tempd_oss.str() + " /card10: matd tempd";
  njoy_input_data.push_back(str_card);

  //njoy_input_data.push_back("/acer end");
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MakeInputFromFRENDYtoNJOY::make_input_groupr()
{
  MultiGroupDataGeneratorInputReader mg_inp_obj = frendy_inp_obj.get_inp_mg_obj();

  if( mg_inp_obj.get_process_flg() == frendy_inp_common_obj.skip_process_data )
  {
    //Skip output groupr process
    string class_name = "MakeInputFromFRENDYtoNJOY";
    string func_name  = "make_input_groupr()";

    vector<string> err_com;
    err_com.push_back("The calculation skip flag is on.");
    err_com.push_back("The GROUPR process is skipped in the NJOY input file.");
    err_obj.output_caution(class_name, func_name, err_com);
    return;
  }

  njoy_input_data.push_back("groupr /groupr start");

  //card 01
  ostringstream nendf_oss, npend_oss, ngout1_oss, ngout2_oss;
  nendf_oss  << nendf_ori;
  npend_oss  << npend_thermr;
  ngout1_oss << 0;
  ngout2_oss << ngendf;
  string str_card = nendf_oss.str() + " " + npend_oss.str() + " " + ngout1_oss.str() + " " + ngout2_oss.str() + " /card01: nendf npend ngout1 ngout2";
  njoy_input_data.push_back(str_card);

  //card 02
  string e_mode       = "1/e";
  string maxwell_mode = "fission+1/e+maxwell";
  string mode_name    = mg_inp_obj.get_mg_weighting_spectrum_mode();
  int iwt_val         = 3; //1/e
  transform(mode_name.begin(), mode_name.end(), mode_name.begin(), ::tolower);
  if( mode_name == maxwell_mode )
  {
    iwt_val = 4; //1/e + fission spectrum + thermal maxwellian
  }
  else if( mode_name == e_mode )
  {
    iwt_val = 3; //1/e
  }
  else
  {
    iwt_val = 1; //read in smooth weight function
  }

  vector<Real> egg = mg_inp_obj.get_mg_structure_gam();
  int          igg = static_cast<int>(egg.size());

  ostringstream mat_oss, ign_oss, igg_oss, iwt_oss, lord_oss, ntemp_oss, nsigz_oss;
  mat_oss    << nucl_data_obj_ori.get_general_data_obj().get_mat_no();
  ign_oss    << 1;
  if( igg == 0 )
  {
    igg_oss    << 0;
  }
  else
  {
    igg_oss    << 1;
  }
  iwt_oss    << iwt_val;
  lord_oss   << mg_inp_obj.get_legendre_order();
  ntemp_oss  << 1;
  nsigz_oss  << static_cast<int>(mg_inp_obj.get_sigma_zero_data().size());
  str_card = mat_oss.str() + " " + ign_oss.str() + " " + igg_oss.str() + " " +iwt_oss.str() + " " + lord_oss.str() + " " + ntemp_oss.str() + " " + nsigz_oss.str() + " /card02: mat ign igg iwt lord ntemp nsigz";
  njoy_input_data.push_back(str_card);

  //card 03
  string title = mg_inp_obj.get_mg_label_data();
  if( static_cast<int>(title.size()) == 0 )
  {
    title = "no label data";
  }
  str_card = "'" + title + "' /card03: title";
  njoy_input_data.push_back(str_card);

  //card 04
  ostringstream temp_oss;
  temp_oss.precision(precision);
  temp_oss.setf(ios::scientific);
  temp_oss << mg_inp_obj.get_temp();
  str_card = temp_oss.str() + " /card04: temp";
  njoy_input_data.push_back(str_card);

  //card 05
  vector<Real> sigz = mg_inp_obj.get_sigma_zero_data();
  sort(sigz.rbegin(), sigz.rend());

  str_card = "";
  for(int i=0; i<static_cast<int>(sigz.size()); i++)
  {
    ostringstream sigz_oss;
    sigz_oss.precision(precision);
    sigz_oss.setf(ios::scientific);

    sigz_oss << sigz[i];
    str_card = str_card + sigz_oss.str() + " ";
  }
  str_card = str_card + "/card05: sigz";
  njoy_input_data.push_back(str_card);

  //card 06a and 06b
  vector<Real> egn = mg_inp_obj.get_mg_structure();
  sort(egn.begin(), egn.end());

  int ngn_val = static_cast<int>(egn.size());
  ostringstream ngn_oss;
  ngn_oss << ngn_val - 1;
  str_card = ngn_oss.str();
  njoy_input_data.push_back(str_card);

  int ele_no = 0;
  str_card   = "";
  for(int i=0; i<ngn_val; i++)
  {
    ostringstream egn_oss;
    egn_oss.precision(precision);
    egn_oss.setf(ios::scientific);

    egn_oss << egn[i];
    str_card = str_card + egn_oss.str() + " ";

    ele_no++;
    if( ele_no%5 == 0 )
    {
      if( i == ngn_val - 1 )
      {
        str_card = str_card + "/card06: egn";
      }
      njoy_input_data.push_back(str_card);

      ele_no   = 0;
      str_card = "";
    }
  }

  if( static_cast<int>(str_card.size()) > 0 )
  {
    str_card = str_card + "/card06: egn";
    njoy_input_data.push_back(str_card);
  }

  //card 07a and 07b
  if( igg > 0 )
  {
    sort(egg.begin(), egg.end());

    ostringstream ngg_oss;
    ngg_oss << igg - 1;
    str_card = ngg_oss.str();
    njoy_input_data.push_back(str_card);

    int ele_no = 0;
    str_card   = "";
    for(int i=0; i<igg; i++)
    {
      ostringstream egg_oss;
      egg_oss.precision(precision);
      egg_oss.setf(ios::scientific);

      egg_oss << egg[i];
      str_card = str_card + egg_oss.str() + " ";
  
      ele_no++;
      if( ele_no%5 == 0 )
      {
        if( i == igg - 1 )
        {
          str_card = str_card + "/card07: egg";
        }
        njoy_input_data.push_back(str_card);

        ele_no   = 0;
        str_card = "";
      }
    }

    if( static_cast<int>(str_card.size()) > 0 )
    {
      str_card = str_card + "/card07: egg";
      njoy_input_data.push_back(str_card);
    }
  }

  //card 08
  if( iwt_val == 1 ) //read in smooth weight function
  {
    vector<Real> wght_e = mg_inp_obj.get_mg_weighting_spectrum_data_e();
    vector<Real> wght_w = mg_inp_obj.get_mg_weighting_spectrum_data_w();
    int wght_no = static_cast<int>(wght_e.size());

    ostringstream wght_no_oss;
    wght_no_oss << wght_no;

    str_card = "0  0  0  0  1  " + wght_no_oss.str();
    njoy_input_data.push_back(str_card);

    str_card = wght_no_oss.str() + "  2";
    njoy_input_data.push_back(str_card);


    ele_no     = 0;
    str_card   = "";
    for(int i=0; i<wght_no; i++)
    {
      ostringstream wght_e_oss, wght_w_oss;
      wght_e_oss.precision(precision);
      wght_w_oss.precision(precision);
      wght_e_oss.setf(ios::scientific);
      wght_w_oss.setf(ios::scientific);

      wght_e_oss << wght_e[i];
      wght_w_oss << wght_w[i];
      str_card = str_card + " " + wght_e_oss.str() + " " + wght_w_oss.str();

      ele_no++;
      if( ele_no%3 == 0 )
      {
        if( i == wght_no - 1 )
        {
          str_card = str_card + "/card08b: wght";
        }
        njoy_input_data.push_back(str_card);

        ele_no   = 0;
        str_card = "";
      }
    }

    if( static_cast<int>(str_card.size()) > 0 )
    {
      str_card = str_card + "/card08b: wght";
      njoy_input_data.push_back(str_card);
    }
  }
  else if( iwt_val == 4 ) //1/e + fission spectrum + thermal maxwellian
  {
    ostringstream eb_oss, tb_oss, ec_oss, tc_oss;
    eb_oss.precision(precision);
    tb_oss.precision(precision);
    ec_oss.precision(precision);
    tc_oss.precision(precision);
    eb_oss.setf(ios::scientific);
    tb_oss.setf(ios::scientific);
    ec_oss.setf(ios::scientific);
    tc_oss.setf(ios::scientific);

    Real eb_val = mg_inp_obj.get_mg_weighting_1e_el();
    Real ec_val = mg_inp_obj.get_mg_weighting_1e_eh();
    Real tc_val = mg_inp_obj.get_mg_weighting_fission_temp();
    if( eb_val < min_value )
    {
      eb_val = 0.625;
    }
    if( ec_val < min_value )
    {
      ec_val = 1.0e+6;
    }
    if( tc_val < min_value )
    {
      tc_val = 1.6e+6;
    }

    eb_oss << eb_val;
    tb_oss << mg_inp_obj.get_temp() * boltzmann_const;
    ec_oss << ec_val;
    tc_oss << tc_val;
    str_card = eb_oss.str() + " " + tb_oss.str() + " " + ec_oss.str() + " " + tc_oss.str() + " /card08c eb tb ec tc";
    njoy_input_data.push_back(str_card);
  }

  //card 09
  make_groupr_mf_mt_list();

  njoy_input_data.push_back("0 /groupr end");
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MakeInputFromFRENDYtoNJOY::make_groupr_mf_mt_list()
{
  //Check cross section (MF=3/mfd=3) data
  vector<CrossSectionDataContainer> xs_obj = nucl_data_obj_ori.get_nucl_reaction_data_obj().get_xs_data_obj();
  for(int i=0; i<static_cast<int>(xs_obj.size()); i++)
  {
    if( xs_obj[i].get_reaction_type() != unassigned_mt_no )
    {
      njoy_input_data.push_back("3 /cross section or yield vector");
      break;
    }
  }
  vector<CrossSectionDataContainer>().swap(xs_obj);

  //Check neuton-neturon matrix (MF=4, 5/mfd=6) data
  int mf06_flg = 0;
  vector<EnergyAngularDataContainer> ene_angular_obj = nucl_data_obj_ori.get_nucl_reaction_data_obj().get_ene_angular_data_obj();
  for(int i=0; i<static_cast<int>(ene_angular_obj.size()); i++)
  {
    if( ene_angular_obj[i].get_reaction_type() != unassigned_mt_no &&
        ene_angular_obj[i].get_reaction_type() !=  18 &&
        ene_angular_obj[i].get_reaction_type() != 455 )
    {
      mf06_flg = 1;
      njoy_input_data.push_back("6 /neuton-neturon matrix (mf4-5)");
      break;
    }
  }
  vector<EnergyAngularDataContainer>().swap(ene_angular_obj);

  //Check neuton-neturon matrix (MF=6/mfd=8) data
  vector<ProductDistributionDataContainer> prod_obj = nucl_data_obj_ori.get_nucl_reaction_data_obj().get_product_distr_data_obj();
  for(int i=0; i<static_cast<int>(prod_obj.size()); i++)
  {
    if( prod_obj[i].get_reaction_type() != unassigned_mt_no )
    {
      njoy_input_data.push_back("8 /neutron-neutron matrix (mf6)");
      break;
    }
  }
  vector<ProductDistributionDataContainer>().swap(prod_obj);


  //Check special options
  vector<int>    mf_list, mt_list;
  vector<string> mtname_list;
  mf_list.clear();
  mt_list.clear();
  mtname_list.clear();

  if( mt_tsl_iin > 0 )
  {
    mf_list.push_back(3);
    mt_list.push_back(mt_tsl_iin);
    mtname_list.push_back("THERMAL SCATTERING INCOH");
    mf_list.push_back(6);
    mt_list.push_back(mt_tsl_iin);
    mtname_list.push_back("THERMAL SCATTERING INCOH");
  }
  if( mt_tsl_icoh > 0 )
  {
    mf_list.push_back(3);
    mt_list.push_back(mt_tsl_icoh);
    mtname_list.push_back("THERMAL SCATTERING COH");
    mf_list.push_back(6);
    mt_list.push_back(mt_tsl_icoh);
    mtname_list.push_back("THERMAL SCATTERING COH");
  }

  if( nucl_data_obj_ori.get_nucl_reaction_data_obj().get_ene_angular_data_obj(2).get_reaction_type() == 2 )
  {
    mf_list.push_back(3);
    mt_list.push_back(251);
    mtname_list.push_back("MU BAR");
  }

  if( nucl_data_obj_ori.get_nucl_reaction_data_obj().get_xs_data_obj(18).get_reaction_type() == 18 )
  {
    if( nucl_data_obj_ori.get_fis_data_obj().get_nu_bar_repr_flg() > 0 )
    {
      mf_list.push_back(3);
      mt_list.push_back(452);
      mtname_list.push_back("NU BAR");
    }

    if( nucl_data_obj_ori.get_fis_data_obj().get_nu_d_bar_repr_flg() > 0 )
    {
      mf_list.push_back(3);
      mt_list.push_back(455);
      mtname_list.push_back("NU_D BAR");
    }

    if( nucl_data_obj_ori.get_fis_data_obj().get_nu_p_bar_repr_flg() > 0 )
    {
      mf_list.push_back(3);
      mt_list.push_back(456);
      mtname_list.push_back("NU_P BAR");
    }
  }

  if( nucl_data_obj_ori.get_nucl_reaction_data_obj().get_ene_angular_data_obj(18).get_reaction_type() == 18 )
  {
    mf_list.push_back(5);
    mt_list.push_back(18);
    mtname_list.push_back("PROMPT FISSION SPECTRUM");
  }

  if( nucl_data_obj_ori.get_nucl_reaction_data_obj().get_ene_angular_data_obj(455).get_reaction_type() == 455 )
  {
    mf_list.push_back(5);
    mt_list.push_back(455);
    mtname_list.push_back("DELAYED FISSION SPECTRUM");
  }

  if( mf06_flg > 0 )
  {
    MultiGroupDataGeneratorInputReader mg_inp_obj = frendy_inp_obj.get_inp_mg_obj();
    if( static_cast<int>(mg_inp_obj.get_mg_structure_gam().size()) > 0 )
    {
      njoy_input_data.push_back("16 /photon production data");
    }
  }

  for(int i=0; i<static_cast<int>(mf_list.size()); i++)
  {
    ostringstream mfd_oss, mtd_oss;
    mfd_oss << mf_list[i];
    mtd_oss << mt_list[i];
    string str_card = mfd_oss.str() + " " + mtd_oss.str() + " '" + mtname_list[i] + "' /";
    njoy_input_data.push_back(str_card);
  }

  njoy_input_data.push_back("0 /card09: mfd mtd mtname");
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MakeInputFromFRENDYtoNJOY::make_input_matxsr()
{
  MultiGroupDataGeneratorInputReader mg_inp_obj = frendy_inp_obj.get_inp_mg_obj();

  if( mg_inp_obj.get_process_flg() == frendy_inp_common_obj.skip_process_data )
  {
    //Skip output matxsr process
    string class_name = "MakeInputFromFRENDYtoNJOY";
    string func_name  = "make_input_matxsr()";

    vector<string> err_com;
    err_com.push_back("The calculation skip flag is on.");
    err_com.push_back("The MATXSR process is skipped in the NJOY input file.");
    err_obj.output_caution(class_name, func_name, err_com);
    return;
  }

  njoy_input_data.push_back("matxsr /matxsr start");

  //card 01
  ostringstream ngen1_oss, ngen2_oss, nmatx_oss;
  ngen1_oss << ngendf;
  ngen2_oss << 0;
  nmatx_oss << nmatxs;
  string str_card = ngen1_oss.str() + " " + ngen2_oss.str() + " " + nmatx_oss.str() + " /card01: ngen1 ngen2 nmatx";
  njoy_input_data.push_back(str_card);

  //card 02
  ostringstream ivers_oss;
  ivers_oss << 0;

  string huse = mg_inp_obj.get_mg_label_data();
  if( static_cast<int>(huse.size()) == 0 )
  {
    huse = "no label data";
  }
  else if( static_cast<int>(huse.size()) > 16 )
  {
    huse = huse.substr(0, 16);
  }
  str_card = ivers_oss.str() + " '" + huse + "' /card02: ivers huse";
  njoy_input_data.push_back(str_card);

  //card 03
  ostringstream npart_oss, ntype_oss, nholl_oss, nmat_oss;
  npart_oss << 1;
  if( mt_tsl_iin > 0 || mt_tsl_icoh > 0 )
  {
    ntype_oss << 2;
  }
  else
  {
    ntype_oss << 1;
  }
  nholl_oss << 1;
  nmat_oss  << 1;
  str_card = npart_oss.str() + " " + ntype_oss.str() + " " + nholl_oss.str() + " " + nmat_oss.str() + " /card03: npart ntype nholl nmat";
  njoy_input_data.push_back(str_card);

  //card 04
  string hsetid = mg_inp_obj.get_mg_label_data();
  if( static_cast<int>(hsetid.size()) == 0 )
  {
    hsetid = "no label data";
  }
  else if( static_cast<int>(hsetid.size()) > 72 )
  {
    hsetid = hsetid.substr(0, 72);
  }
  str_card = " '" + hsetid + "' /card04: hsetid";
  njoy_input_data.push_back(str_card);

  //card 05
  string hpart = "n";
  str_card = "'" + hpart + "' /card05: hpart";
  njoy_input_data.push_back(str_card);

  //card 06
  ostringstream ngrp_oss;
  ngrp_oss << static_cast<int>(mg_inp_obj.get_mg_structure().size()) - 1;
  str_card = ngrp_oss.str() + " /card06: ngrp";
  njoy_input_data.push_back(str_card);

  //card 07
  str_card = "'nscat'";
  if( mt_tsl_iin > 0 || mt_tsl_icoh > 0 )
  {
    str_card = str_card + " 'ntherm'";
  }
  str_card = str_card + " /card07: htype";
  njoy_input_data.push_back(str_card);

  //card 08 and 09
  if( mt_tsl_iin > 0 || mt_tsl_icoh > 0 )
  {
    str_card = "1  1 /card08 jinp";
    njoy_input_data.push_back(str_card);
    str_card = "1  1 /card09 joutp";
    njoy_input_data.push_back(str_card);
  }
  else
  {
    str_card = "1 /card08 jinp";
    njoy_input_data.push_back(str_card);
    str_card = "1 /card09 joutp";
    njoy_input_data.push_back(str_card);
  }

  //card 10
  ostringstream mat_oss, za_oss;
  mat_oss << nucl_data_obj_ori.get_general_data_obj().get_mat_no();
  za_oss  << static_cast<int>(round(nucl_data_obj_ori.get_general_data_obj().get_mat_data()));

  str_card = "'" + za_oss.str() + "' " + mat_oss.str() + " /card10 hmat matno";
  njoy_input_data.push_back(str_card);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MakeInputFromFRENDYtoNJOY::make_input_heatr()
{
  ReconResonanceInputReader  reconr_inp_obj = frendy_inp_obj.get_inp_recon_obj();

  njoy_input_data.push_back("heatr /heatr start");

  //card 01
  nendf_ori   = get_tape_no(reconr_inp_obj.get_nucl_file_name()[0],  nendf_ori);
  npend_heatr = 40;

  ostringstream nendf_oss, nin_oss, nout_oss;
  nendf_oss << nendf_ori;
  nin_oss   << npend_gaspr;
  nout_oss  << npend_heatr;
  string str_card = nendf_oss.str() + " " + nin_oss.str() + " " + nout_oss.str()
                  + " 0 /card01: nendf nin nout graphical-check";
  njoy_input_data.push_back(str_card);

  //card02
  ostringstream mat_oss;
  mat_oss << nucl_data_obj_ori.get_general_data_obj().get_mat_no();
  str_card = mat_oss.str() + "  5 0 0 0 2  0 /card02: matd  npk nqa ntemp local iprint  ed  add-opt";
  njoy_input_data.push_back(str_card);

  //card03
  str_card = "302  318  402  443  444 /card03: non-ela fis rad kerma total-dep";
  njoy_input_data.push_back(str_card);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Integer MakeInputFromFRENDYtoNJOY::get_tape_no(string tape_str, Integer tape_no_ori)
{
  string trim_character = "tape";
  string tape_str_ori  = tape_str;

  StringUtils str_util_obj;
  str_util_obj.trim_space(tape_str);

  Integer tape_no = tape_no_ori;
  if( tape_str.find_first_of(trim_character.c_str()) == string::npos ||
      static_cast<int>(tape_str.size()) != 6 )
  {
    return tape_no;
  }

  tape_str = str_util_obj.trim_data(tape_str, trim_character);
  if( static_cast<int>(tape_str.size()) == 1 || static_cast<int>(tape_str.size()) == 2 )
  {
    Integer tape_no_from_inp = atoi(tape_str.c_str());
    if( tape_no_from_inp > 19 && tape_no_from_inp < 100 )
    {
      tape_no = tape_no_from_inp;
    }
    else
    {
      string class_name = "MakeInputFromFRENDYtoNJOY";
      string func_name  = "get_tape_no(string tape_str, Integer tape_no_ori)";

      vector<string> err_com;
      string err_str01 = "Tape name : " + tape_str_ori;
      err_com.push_back(err_str01);
      err_com.push_back("This tape number is not appropriate.");
      err_com.push_back("Appropriate tape number is 20 - 99.");
      err_com.push_back("The original tape number is used.");

      err_obj.output_caution(class_name, func_name, err_com);
    }
  }

  return tape_no;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Real MakeInputFromFRENDYtoNJOY::search_thn_max()
{
  //Copy from DopplerCalculator (search_dop_ene_max())
  Real thn_max = frendy_inp_obj.get_inp_dop_obj().get_max_broadening_ene();
  if( thn_max < 0.0 )
  {
    return thn_max;
  }

  vector<vector<Integer> > reso_flg   = nucl_data_obj_ori.get_reso_data_obj().get_reso_region_flg();
  vector<vector<Real> >    reso_eh    = nucl_data_obj_ori.get_reso_data_obj().get_upper_ene_limit();
  vector<Real>             unreso_ene = nucl_data_obj_ori.get_reso_data_obj().get_unreso_xs_data_obj().get_unreso_ene();

  int  set_max_ene_flg = 0;
  Real max_ene         = 1.0 / min_ene_val;
  int i_max = static_cast<int>(reso_eh.size());
  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(reso_eh[i].size());
    for(int j=0; j<j_max; j++)
    {
      if( max_ene > reso_eh[i][j] && reso_flg[i][j] == 1 )
      {
        set_max_ene_flg = 1;
        max_ene         = reso_eh[i][j];
      }
    }
  }
  clr_obj.clear_vec_array2_real(reso_eh);

  i_max = static_cast<int>(unreso_ene.size());
  if( i_max > 0 )
  {
    if( max_ene > unreso_ene[0] )
    {
      set_max_ene_flg = 1;
      max_ene         = unreso_ene[0];
    }
  }
  unreso_ene.clear();

  if( set_max_ene_flg > 0 )
  {
    thn_max = -1.0 * max_ene;
  }

  return thn_max;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Integer MakeInputFromFRENDYtoNJOY::check_elastic_scattering_tsl()
{
  //0:coherent, 1:incoherent
  Integer ielas = -1;

  ThermalScatterDataContainer tsl_data_obj = nucl_data_obj_tsl.get_thermal_scat_data_obj();
  if( static_cast<int>(tsl_data_obj.get_elastic_structure_factor_data_base().size()) > 0 )
  {
    //coherent
    ielas = 0;
  }
  else if( static_cast<int>(tsl_data_obj.get_elastic_debye_waller_data().size()) > 0 )
  {
    //incoherent
    ielas = 1;
  }

  if( tsl_data_obj.get_elastic_scat_flg() == 3 )
  {
    //mixed elastic
    ielas = 2;
  }
  tsl_data_obj.clear();

  return ielas;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Integer MakeInputFromFRENDYtoNJOY::get_inelastic_options_tsl()
{
  Integer iin = 1; //compute as free gas

  ThermalScatterDataContainer tsl_data_obj = nucl_data_obj_tsl.get_thermal_scat_data_obj();
  if( static_cast<int>(tsl_data_obj.get_inelastic_scat_law_data().size()) > 0 )
  {
    //Input parameter of NJOY99 is different. iin of NJOY99 is 4 for s(a, b)
    iin = 2; //read s(a, b) and compute matrix
  }
  tsl_data_obj.clear();

  return iin;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Integer MakeInputFromFRENDYtoNJOY::get_elastic_options_tsl()
{
  Integer icoh = 0;

  ThermalScatterDataContainer tsl_data_obj = nucl_data_obj_tsl.get_thermal_scat_data_obj();
  if( static_cast<int>(tsl_data_obj.get_elastic_structure_factor_data_base().size()) > 0 ||
      static_cast<int>(tsl_data_obj.get_elastic_debye_waller_data().size()) > 0 )
  {
    icoh = 1;
  }
  tsl_data_obj.clear();

  return icoh;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Integer MakeInputFromFRENDYtoNJOY::get_atom_no_principal_tsl(int ele_no)
{
  Integer principal_atom_no = 0;
  vector<Real> scat_law_coef = nucl_data_obj_tsl.get_thermal_scat_data_obj().get_inelastic_scat_law_coef();
  if( static_cast<int>(scat_law_coef.size()) >= 5 )
  {
    principal_atom_no = static_cast<Integer>(scat_law_coef[5]);
  }

  if( principal_atom_no <= 0 )
  {
    Integer mat_no_tsl = nucl_data_obj_tsl.get_general_data_obj().get_mat_no();
    ThermalScatterMatList tsl_list;

    principal_atom_no = tsl_list.get_thermal_scat_data(mat_no_tsl)[ele_no].get_atom_no_principal();
  }

  return principal_atom_no;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Integer MakeInputFromFRENDYtoNJOY::get_atom_no_mix_tsl(int ele_no)
{
  Integer mat_no_tsl = nucl_data_obj_tsl.get_general_data_obj().get_mat_no();

  ThermalScatterMatList tsl_list;
  return static_cast<Integer>(tsl_list.get_thermal_scat_data(mat_no_tsl)[ele_no].get_atom_no_mix());
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Integer MakeInputFromFRENDYtoNJOY::get_moderator_component(int ele_no)
{
  Integer mat_no_tsl = nucl_data_obj_tsl.get_general_data_obj().get_mat_no();

  ThermalScatterMatList tsl_list;
  return static_cast<Integer>(tsl_list.get_thermal_scat_data(mat_no_tsl)[ele_no].get_mat_data_principal());
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Real MakeInputFromFRENDYtoNJOY::get_max_thermal_ene()
{
  //Copy from ThermalScatterCalculatorByFrendyInput (set_max_thermal_ene()) and
  //           ThermalScatterCalculator (get_max_thermal_ene_endf())
  ThermalScatterInputReader thermr_inp_obj = frendy_inp_obj.get_inp_thermal_scatter_obj();

  Real max_thermal_ene = thermr_inp_obj.get_max_thermal_ene();
  if( thermr_inp_obj.get_set_max_thermal_ene_flg() == 0 )
  {
    //Automatically set parameter
    vector<Real> b_vec = nucl_data_obj_tsl.get_thermal_scat_data_obj().get_inelastic_scat_law_coef();

    Real max_thermal_ene_endf = -1.0;
   if( static_cast<int>(b_vec.size()) > 4 )
    {
      max_thermal_ene_endf = b_vec[3]; //B(4) : Emax
    }
     
    if( max_thermal_ene_endf > max_thermal_ene )
    {
      max_thermal_ene = max_thermal_ene_endf;
    }
  }
  thermr_inp_obj.clear();

  return max_thermal_ene;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MakeInputFromFRENDYtoNJOY::adjust_comment_data(vector<string>& text_vec, int row_number)
{
  int i_max = static_cast<int>(text_vec.size());
  for(int i=0; i<i_max; i++)
  {
    adjust_comment_line(text_vec[i], row_number);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MakeInputFromFRENDYtoNJOY::adjust_comment_line(string& text_data, int row_number)
{
  string comment_data = "/";
 
  if( text_data.find_last_of(comment_data.c_str()) != string::npos )
  {
    int comment_row_no = static_cast<int>(text_data.find_last_of(comment_data.c_str()));
    if( comment_row_no == 0 )
    {
      comment_row_no++;
      row_number++;
    }
    for(int i=comment_row_no-1; i<row_number-1; i++)
    {
      text_data.insert(i, " ");
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MakeInputFromFRENDYtoNJOY::write_njoy_input(string output_name)
{
  int line_no = static_cast<int>(njoy_input_data.size());
  if( line_no == 0 )
  {
    string class_name = "MakeInputFromFRENDYtoNJOY";
    string func_name  = "write_njoy_input(string output_name)";

    vector<string> err_com;
    err_com.push_back("There is no NJOY input data.");
    err_com.push_back("Please check your program.");
    err_com.push_back("Output of NJOY input data process is skipped.");

    err_obj.output_caution(class_name, func_name, err_com);
    return;
  }

  ofstream fout;
  fout.open(output_name.c_str());

  if( fout.fail() )
  {
    string class_name = "MakeInputFromFRENDYtoNJOY";
    string func_name  = "write_njoy_input(string output_name)";

    string str_data = "  Output file name : " + output_name;

    vector<string> err_com;
    err_com.push_back("Output file can not be open.");
    err_com.push_back("Please check the file name, directory name or access authority.");
    err_com.push_back(str_data);

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  for(int i=0; i<line_no; i++)
  {
    fout << njoy_input_data[i] << endl;
  }
  fout.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> MakeInputFromFRENDYtoNJOY::get_njoy_input_data()
{
  return njoy_input_data;
}

