#include "DopplerBroadening/DopplerCalculatorByNjoyInput.hpp"

using namespace frendy;

//constructor
DopplerCalculatorByNjoyInput::DopplerCalculatorByNjoyInput(void)
{
  clear();
}

//destructor
DopplerCalculatorByNjoyInput::~DopplerCalculatorByNjoyInput(void)
{
  clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DopplerCalculatorByNjoyInput::calc_doppler_broader()
{
  if( calc_flg == 1 )
  {
    return;
  }
  calc_flg = 1;

  cout << "****************************** Doppler broadening calculation ******************************";
  cout << endl << endl;
  time_obj.output_current_time();

  boost::timer::cpu_timer timer_total;

  set_input_data();
  output_input_file_name();

  check_set_data();

  //Divide endf tape in each endf file
  int mat_no_max = static_cast<int>(mat_no_list.size());
  for(int mat_no=0; mat_no<mat_no_max; mat_no++)
  {
    cout << "  Material No. : " << mat_no_list[mat_no] << endl;
    boost::timer::cpu_timer timer_mat;

    calc_doppler_broader_each_mat(mat_no);
    time_each_mat[mat_no] = static_cast<Real>(timer_mat.elapsed().wall * 1.0E-9);

    cout << "  Calculation time of material No. " << mat_no_list[mat_no] << " : " 
         << time_each_mat[mat_no] << "[s]" << endl << endl;
  }

  time_total = static_cast<Real>(timer_total.elapsed().wall * 1.0E-9);
  cout << "Total calculation time : " << time_total << " [s]" << endl;
  cout << endl;
  cout << "********************************************************************************************";
  cout << endl << endl;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DopplerCalculatorByNjoyInput::calc_doppler_broader_each_mat(int mat_no)
{
  //Read endf file (using ENDF6ParserNoCov class)
  if( set_nucl_data_obj_flg == 0 )
  {
    nucl_data_obj_ori[mat_no] = store_obj.get_nucl_data_obj_no_cov(pendf_input_name, mat_no_list[mat_no]);
    store_obj.clear();
  }

  nucl_data_obj_base = store_obj.get_nucl_data_obj_no_cov(endf_file_name, mat_no_list[mat_no]);
  store_obj.clear();
  
  Real8 temp_ori = temp_ini[mat_no];
  temp_ini_chk.clear();
  int temp_no_max = static_cast<int>(temp_dop[mat_no].size());
  for(int temp_no=0; temp_no<temp_no_max; temp_no++)
  {
    if( istrap_list[mat_no] == 1 && temp_no > 0 )
    {
      temp_ori = temp_dop[mat_no][temp_no-1];
    } 
    temp_ini_chk.push_back(temp_ori);

    cout << "    Temperature : " << temp_ori << " -> " << temp_dop[mat_no][temp_no] << endl;
    boost::timer::cpu_timer timer_temp;
    calc_doppler_broader_each_temp(mat_no, temp_no, temp_ori);
    cout << "      Max energy for broader and thinning : " << dop_ene_max_cal[mat_no] << " [eV]" << endl;
    time_each_temp[mat_no][temp_no] = static_cast<Real>(timer_temp.elapsed().wall * 1.0E-9);
    cout << "      Calculation time of temperature " << temp_dop[mat_no][temp_no] << " [K] : "
         << time_each_temp[mat_no][temp_no] << " [s]" << endl << endl;
  }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////

void DopplerCalculatorByNjoyInput::calc_doppler_broader_each_temp(int mat_no, int temp_no, Real8 temp_ori)
{
  //Calculation of doppler broadened xs using CalcDoppler class
  if( istrap_list[mat_no] == 1 && temp_no > 0 )
  {
    dop_obj.set_nucl_data_obj(nucl_data_obj_dop[mat_no][temp_no-1]);
  }
  else
  {
    dop_obj.set_nucl_data_obj(nucl_data_obj_ori[mat_no]);
  }
  dop_obj.set_nucl_data_obj_base(nucl_data_obj_base);

  dop_obj.set_temp_ori(temp_ori);
  dop_obj.set_temp_dop(temp_dop[mat_no][temp_no]);
  dop_obj.set_err(err[mat_no]);
  dop_obj.set_err_max(err_max[mat_no]);
  dop_obj.set_err_int(err_int[mat_no]);
  dop_obj.set_dop_ene_max(dop_ene_max_inp[mat_no]);
  
  dop_obj.output_set_data_information();
  dop_obj.calc_doppler();
  nucl_data_obj_dop[mat_no][temp_no] = dop_obj.get_nucl_data_obj();

  dop_ene_max_cal[mat_no] = dop_obj.get_dop_ene_max();
  dop_obj.clear();

  //Thermal quantity calculation when temp_dop is 293.6K
  calc_thermal_quantity(mat_no, temp_no);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DopplerCalculatorByNjoyInput::calc_thermal_quantity(int mat_no, int temp_no)
{
  if( th_q_obj.check_temp(temp_dop[mat_no][temp_no]) != 0 )
  {
    return;
  }

  NuclearDataObject nucl_data_obj_tmp;
  nucl_data_obj_tmp = store_obj.get_nucl_data_obj_no_cov(endf_file_name, mat_no_list[mat_no]);
  store_obj.clear();

  if( th_q_obj.check_nucl_data_obj(nucl_data_obj_tmp) != 0 )
  {
    return;
  }

  //Add FissionDataContainer to nucl_data_obj_dop
  //(FissionDataContainer may not be included in nucl_data_obj_dop)
  FissionDataContainer fis_data_obj = nucl_data_obj_tmp.get_fis_data_obj();
  nucl_data_obj_tmp.clear();
  nucl_data_obj_tmp = nucl_data_obj_dop[mat_no][temp_no];
  nucl_data_obj_tmp.set_fis_data_obj(fis_data_obj);

  th_q_obj.set_nucl_data_obj(nucl_data_obj_tmp);
  nucl_data_obj_tmp.clear();

  th_q_obj.set_temp_ori(temp_dop[mat_no][temp_no]);

  Integer fis_flg = th_q_obj.get_fissile_flg();
  if( th_q_obj.get_err_flg() < 0 )
  {
    return;
  }

  cout << endl;
  cout << "thermal quantities at " << temp_dop[mat_no][temp_no] << " K = "
                                   << th_q_obj.get_ene_ori()    << " eV" << endl;
  cout << "-----------------------------------------" << endl;
  cout.setf(ios::scientific);
  if( fis_flg == 0 )
  {
    cout << " thermal fission xsec       : " << th_q_obj.get_sig_f_th()  << endl;
    cout << " thermal fission nubar      : " << th_q_obj.get_nu_bar_th() << endl;
  }
  cout << " thermal capture xsec       : " << th_q_obj.get_sig_c_th()      << endl;
  cout << " thermal capture g-factor   : " << th_q_obj.get_g_fac_cap()     << endl;
  cout << " thermal capture integral   : " << th_q_obj.get_inte_cap()      << endl;
  cout << " capture resonance integral : " << th_q_obj.get_inte_cap_reso() << endl;
  if( fis_flg == 0 )
  { 
    cout << " thermal fission integral   : " << th_q_obj.get_inte_fis()      << endl;
    cout << " thermal fission g-factor   : " << th_q_obj.get_g_fac_fis()     << endl;
    cout << " thermal alpha integral     : " << th_q_obj.get_alpha()         << endl;
    cout << " thermal eta integral       : " << th_q_obj.get_eta()           << endl;
    cout << " thermal k1 integral        : " << th_q_obj.get_k1()            << endl;
    cout << " equivalent k1              : " << th_q_obj.get_k1_eq()         << endl;
    cout << " fission resonance integral : " << th_q_obj.get_inte_fis_reso() << endl;
  }
  cout.unsetf(ios::scientific);
  cout << "-----------------------------------------" << endl;
  cout << endl;

  th_q_obj.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DopplerCalculatorByNjoyInput::check_set_data()
{
  int i_max = static_cast<int>(mat_no_list.size());

  if( ( mat_no_list.size() < 1 ) || ( temp_no_list.size() < 1 ) || ( istart_list.size() < 1 ) ||
      ( istrap_list.size() < 1 ) || ( temp_ini.size() < 1 ) || ( err.size() < 1 ) || 
      ( err_int.size() < 1 ) || ( err_max.size() < 1 ) || ( dop_ene_max_inp.size() < 1 ) ||
      ( temp_dop.size() < 1 ) || ( i_max != static_cast<int>(temp_no_list.size()) ) ||
      ( i_max != static_cast<int>(istart_list.size()) ) ||
      ( i_max != static_cast<int>(istrap_list.size()) ) ||
      ( i_max != static_cast<int>(temp_ini.size()) ) ||
      ( i_max != static_cast<int>(temp_ini.size()) ) ||
      ( i_max != static_cast<int>(temp_ini.size()) ) ||
      ( i_max != static_cast<int>(temp_ini.size()) ) ||
      ( i_max != static_cast<int>(temp_ini.size()) ) ||
      ( i_max != static_cast<int>(temp_ini.size()) ) ||
      ( ( set_nucl_data_obj_flg == 1 ) && ( i_max != static_cast<int>(nucl_data_obj_ori.size()) ) ) )
  {
    string class_name = "DopplerCalculatorByNjoyInput";
    string func_name  = "check_set_data()";

    ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07, oss08, oss09, oss10;
    oss01 << mat_no_list.size();
    oss02 << temp_no_list.size();
    oss03 << istart_list.size();
    oss04 << istrap_list.size();
    oss05 << temp_ini.size();
    oss06 << err.size();
    oss07 << err_max.size();
    oss08 << err_int.size();
    oss09 << dop_ene_max_inp.size();
    oss10 << temp_dop.size();
    string str_data01 = "Material data number               : " + oss01.str();
    string str_data02 = "Temperature data number            : " + oss02.str();
    string str_data03 = "istart data number                 : " + oss03.str();
    string str_data04 = "istrap data number                 : " + oss04.str();
    string str_data05 = "Initial temperature data number    : " + oss05.str();
    string str_data06 = "Error data number                  : " + oss06.str();
    string str_data07 = "Maximum error data number          : " + oss07.str();
    string str_data08 = "Integral error data number         : " + oss08.str();
    string str_data09 = "Maximum Doppler energy data number : " + oss09.str();
    string str_data10 = "Doppler tempareture data number    : " + oss10.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back(str_data05);
    err_com.push_back(str_data06);
    err_com.push_back(str_data07);
    err_com.push_back(str_data08);
    err_com.push_back(str_data09);
    err_com.push_back(str_data10);
 
    //Check the size of list
    if( mat_no_list.size() < 1 )
    {
      err_com.push_back("The material data is not set. Please set the material data.");
    }
    if( temp_no_list.size() < 1 )
    {
      err_com.push_back("The doppler temp. data is not set. Please set the doppler temp. data.");
    }
    if( istart_list.size() < 1 )
    {
      err_com.push_back("The istart data is not set. Please set the istart data.");
    }
    if( istrap_list.size() < 1 )
    {
      err_com.push_back("The istrap data is not set. Please set the istrap data.");
    }
    
    if( temp_ini.size() < 1 )
    {
      err_com.push_back("The initial temp. data is not set. Please set the initial temp. data.");
    }
    if( err.size() < 1 )
    {
      err_com.push_back("The error data is not set. Please set the error data.");
    }
    if( err_max.size() < 1 )
    {
      err_com.push_back("The max error data is not set. Please set the max error data.");
    }
    if( err_int.size() < 1 )
    {
      err_com.push_back("The integral error data is not set. Please set the integral error data.");
    }
    if( dop_ene_max_inp.size() < 1 )
    {
      err_com.push_back("The max doppler energy is not set. Please set the max doppler energy.");
    }
    if( temp_dop.size() < 1 )
    {
      err_com.push_back("The doppler temp. data is not set. Please set the doppler temp. data.");
    }
    
    if( i_max != static_cast<int>(temp_no_list.size()) )
    {
      err_com.push_back("The element no of doppler temp. data is not equal to that of material data.");
    }
    if( i_max != static_cast<int>(istart_list.size()) )
    {
      err_com.push_back("The element no of istart data is not equal to that of material data.");
    }
    if( i_max != static_cast<int>(istrap_list.size()) )
    {
      err_com.push_back("The element no of istrap data is not equal to that of material data.");
    }
    if( i_max != static_cast<int>(temp_ini.size()) )
    {
      err_com.push_back("The element no of initial temp. data is not equal to that of material data.");
    }
    if( i_max != static_cast<int>(temp_ini.size()) )
    {
      err_com.push_back("The element no of error data is not equal to that of material data.");
    }
    if( i_max != static_cast<int>(temp_ini.size()) )
    {
      err_com.push_back("The element no of max error data is not equal to that of material data.");
    }
    if( i_max != static_cast<int>(temp_ini.size()) )
    {
      err_com.push_back("The element no of integral error data is not equal to that of material data.");
    }
    if( i_max != static_cast<int>(temp_ini.size()) )
    {
      err_com.push_back("The element no of max doppler energy is not equal to that of material data.");
    }
    if( i_max != static_cast<int>(temp_ini.size()) )
    {
      err_com.push_back("The element no of doppler temp. data is not equal to that of material data.");
    }
  
    if( set_nucl_data_obj_flg == 1 )
    {
      if( i_max != static_cast<int>(nucl_data_obj_ori.size()) )
      {
        err_com.push_back("The array size of nucl_data_obj_ori is not equal to that of material data");
      }
    }
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
  
  for(int i=0; i<i_max; i++)
  {
    if( ( temp_dop[i].size() < 1 ) ||
        ( istart_list[i] != 0 && istart_list[i] != 1 ) ||
        ( istrap_list[i] != 0 && istrap_list[i] != 1 ) )
    {
      string class_name = "DopplerCalculatorByNjoyInput";
      string func_name  = "check_set_data()";

      ostringstream oss01, oss02, oss03, oss04, oss05;
      oss01 << i;
      oss02 << static_cast<int>(mat_no_list.size());
      oss03 << temp_dop[i].size();
      oss04 << istart_list[i];
      oss05 << istrap_list[i];
      string str_data01 = "Material number                 : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "Doppler temperature data number : " + oss03.str();
      string str_data03 = "istart                          : " + oss04.str();
      string str_data04 = "istrap                          : " + oss05.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back(str_data04);
      if( temp_dop[i].size() < 1 )
      {
        err_com.push_back("The doppler temp. data at each material is not set.");
        err_com.push_back("Please set the doppler temp. data.");
      }
      if( istart_list[i] != 0 && istart_list[i] != 1 )
      {
        err_com.push_back("istart option is only applicable 0 or 1.");
      }
      if( istrap_list[i] != 0 && istrap_list[i] != 1 )
      {
        err_com.push_back("istrap option is only applicable 0 or 1.");
      }
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DopplerCalculatorByNjoyInput::clear()
{
  calc_flg              = 0;
  set_nucl_data_obj_flg = 0;

  nucl_data_obj_base.clear();
  vector<NuclearDataObject>().swap(nucl_data_obj_ori);
  vector<vector<NuclearDataObject> >().swap(nucl_data_obj_dop);
  //int i_max = static_cast<int>(nucl_data_obj_dop.size());
  //for(int i=0; i<i_max; i++)
  //{
  //  int j_max = static_cast<int>(nucl_data_obj_dop[i].size());
  //  for(int j=0; j<j_max; j++)
  //  {
  //    nucl_data_obj_dop[i][j].clear();
  //  }
  //  
  //  nucl_data_obj_ori[i].clear();
  //  nucl_data_obj_dop[i].clear();
  //}
  //nucl_data_obj_ori.resize(0);
  //nucl_data_obj_dop.resize(0);

  dop_obj.clear();
  wri_obj.clear();
  
  input_file_name_njoy.clear();
  start_line_no = 0;

  endf_file_name.clear();
  pendf_input_name.clear();
  pendf_output_name.clear();
  
  mat_no_list.clear();
  temp_no_list.clear();
  istart_list.clear();
  istrap_list.clear();
  temp_ini.clear();
  err.clear();
  err_int.clear();
  err_max.clear();
  dop_ene_max_inp.clear();
  dop_ene_max_cal.clear();
  clr_obj.clear_vec_array2_real8(temp_dop);
  temp_ini_chk.clear();
  
  time_total = 0.0;
  time_each_mat.clear();
  clr_obj.clear_vec_array2_real(time_each_temp);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DopplerCalculatorByNjoyInput::output_input_file_name()
{
  cout << "=== Nuclear data file information ===" << endl;
  cout << "  Input File Name          : " << input_file_name_njoy << endl;
  cout << "  ENDF  File Name          : " << endf_file_name       << endl;
  cout << "  PENDF File Name (input)  : " << pendf_input_name     << endl;
  cout << "  PENDF File Name (output) : " << pendf_output_name    << endl;
  cout << endl;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DopplerCalculatorByNjoyInput::set_input_data()
{
  BroadrInputReader read_njoy_obj;
  read_njoy_obj.read_input(input_file_name_njoy, start_line_no);

  endf_file_name    = read_njoy_obj.get_endf_name();
  pendf_input_name  = read_njoy_obj.get_pendf_input_name();
  pendf_output_name = read_njoy_obj.get_pendf_output_name();
  mat_no_list       = read_njoy_obj.get_mat();
  temp_no_list      = read_njoy_obj.get_temp_no();
  istart_list       = read_njoy_obj.get_istart();
  istrap_list       = read_njoy_obj.get_istrap();
  temp_ini          = read_njoy_obj.get_temp_ini();
  err               = read_njoy_obj.get_err();
  err_int           = read_njoy_obj.get_err_int();
  err_max           = read_njoy_obj.get_err_max();
  dop_ene_max_inp   = read_njoy_obj.get_dop_ene_max();
  temp_dop          = read_njoy_obj.get_temp();

  read_njoy_obj.clear();

  //resize matrix
  int i_max = static_cast<int>(temp_dop.size());
  nucl_data_obj_ori.resize(i_max);
  nucl_data_obj_dop.resize(i_max);
  dop_ene_max_cal.resize(i_max);
  time_each_mat.resize(i_max);
  time_each_temp.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(temp_dop[i].size());
    nucl_data_obj_dop[i].resize(j_max);
    time_each_temp[i].resize(j_max);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DopplerCalculatorByNjoyInput::set_njoy_input_file_name(string file_name)
{
  set_njoy_input_file_name(file_name, 0);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DopplerCalculatorByNjoyInput::set_njoy_input_file_name(string file_name, int line_no)
{
  calc_flg = 0;
  if( set_nucl_data_obj_flg == 1 )
  {
    cout << endl;
    cout << "***************************************************************" << endl;
    cout << endl;
    cout << "              !!! C A U T I O N !!!" << endl;
    cout << "  Though the set_nucl_data_obj_ori function was called "    << endl;
    cout << "  before the set_njoy_input_file_name function, "           << endl;
    cout << "  the set_nucl_data_obj_ori function was declared."         << endl;
    cout << "  If you want to use the set_nucl_data_obj_ori function, "  << endl;
    cout << "  please call after the set_njoy_input_file_name function." << endl;
    cout << endl;
    cout << "***************************************************************" << endl;
    cout << endl;

    set_nucl_data_obj_flg = 0;
  }
  
  input_file_name_njoy = file_name;
  start_line_no        = line_no;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DopplerCalculatorByNjoyInput::write_pendf_file()
{
  calc_doppler_broader();
  
  vector<string> text;
  clr_obj.clear_vec_array1_str(text);

  //Get label data
  EndfTapeDivider div_obj;
  div_obj.set_file_name(pendf_input_name);
  label_data = div_obj.get_label_data();
  div_obj.clear();

  //Open PENDF file
  ofstream fout;
  fout.open(pendf_output_name.c_str());

  if( fout.fail() )
  {
    string class_name = "DopplerCalculatorByNjoyInput";
    string func_name  = "write_pendf_file()";

    string str_data = "  Output file name : " + pendf_output_name;

    vector<string> err_com;
    err_com.push_back("Output file can not be open.");
    err_com.push_back("Please check the file name, directory name or access authority.");
    err_com.push_back(str_data);

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
  
  int i_max = static_cast<int>(temp_dop.size());
  for(int i=0; i<i_max; i++)
  {
    if( istart_list[i] == 1 )
    {
      add_previous_pendf_text(i, text);
      write_text_data(fout, text);
    }
    
    int j_max = static_cast<int>(temp_dop[i].size());
    for(int j=0; j<j_max; j++)
    {
      //get endf file (string data)
      wri_obj.set_nucl_data_obj(nucl_data_obj_dop[i][j]);
      if( istart_list[i] != 1 && i == 0 && j == 0 )
      {
        wri_obj.set_pendf_label(label_data);
        text = wri_obj.get_endf_text_data();
      }
      else
      {
        text = wri_obj.get_endf_text_data_without_label();
      }
      wri_obj.clear();

      write_text_data(fout, text);
    }
  }

  //Write tape end
  EndfFileWriter efw_obj;
  fout <<  efw_obj.write_tape_end() << endl;

  fout.close();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DopplerCalculatorByNjoyInput::write_text_data(ofstream& fout, vector<string>& text)
{
  int i_max = static_cast<int>(text.size());
  for(int i=0; i<i_max; i++)
  {
    fout << text[i] << endl;
  }
  clr_obj.clear_vec_array1_str(text);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DopplerCalculatorByNjoyInput::add_previous_pendf_text(int mat_no, vector<string>& text)
{
  EndfTapeDivider div_obj;
  div_obj.set_file_name(pendf_input_name);
  vector<string> text_old = div_obj.get_data(mat_no);

  label_data = div_obj.get_label_data();

  EndfFileWriter efw_obj;
  efw_obj.set_mat(1);
  efw_obj.set_mf_mt(0, 0);
  text.push_back(efw_obj.write_text(label_data));
  
  int i_max = static_cast<int>(text_old.size());
  for(int i=0; i<i_max; i++)
  {
    text.push_back(text_old[i]);
  }
  clr_obj.clear_vec_array1_str(text_old);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DopplerCalculatorByNjoyInput::set_nucl_data_obj_ori(vector<NuclearDataObject>& data_obj)
{
  set_nucl_data_obj_flg = 1;
  calc_flg              = 0;

  for(int i=0; i<static_cast<int>(nucl_data_obj_ori.size()); i++)
  {
    nucl_data_obj_ori[i].clear();
  }
  nucl_data_obj_ori.resize(0);

  nucl_data_obj_ori = data_obj;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

string                 DopplerCalculatorByNjoyInput::get_njoy_input_file_name()
{
  return input_file_name_njoy;
}

string                 DopplerCalculatorByNjoyInput::get_endf_file_name()
{
  return endf_file_name;
}

string                 DopplerCalculatorByNjoyInput::get_pendf_input_name()
{
  return pendf_input_name;
}

string                 DopplerCalculatorByNjoyInput::get_pendf_output_name()
{
  return pendf_output_name;
}

vector<Integer>        DopplerCalculatorByNjoyInput::get_mat_no_list()
{
  return mat_no_list;
}

vector<Integer>        DopplerCalculatorByNjoyInput::get_temp_no_list()
{
  return temp_no_list;
}

vector<Integer>        DopplerCalculatorByNjoyInput::get_istart_list()
{
  return istart_list;
}

vector<Integer>        DopplerCalculatorByNjoyInput::get_istrap_list()
{
  return istrap_list;
}

vector<Real8>          DopplerCalculatorByNjoyInput::get_temp_ini()
{
  return temp_ini;
}

vector<Real8>          DopplerCalculatorByNjoyInput::get_err()
{
  return err;
}

vector<Real8>          DopplerCalculatorByNjoyInput::get_err_int()
{
  return err_int;
}

vector<Real8>          DopplerCalculatorByNjoyInput::get_err_max()
{
  return err_max;
}
vector<Real8>          DopplerCalculatorByNjoyInput::get_dop_ene_max()
{
  return dop_ene_max_inp;
}

vector<vector<Real8> > DopplerCalculatorByNjoyInput::get_temp_dop()
{
  return temp_dop;
}

vector<Real8>          DopplerCalculatorByNjoyInput::get_temp_ini_chk()
{
  return temp_ini_chk;
}

vector<NuclearDataObject> DopplerCalculatorByNjoyInput::get_nucl_data_obj_ori()
{
  return nucl_data_obj_ori;
}

vector<vector<NuclearDataObject> > DopplerCalculatorByNjoyInput::get_nucl_data_obj_dop()
{
  calc_doppler_broader();
  return nucl_data_obj_dop;
}

Real DopplerCalculatorByNjoyInput::get_time_total()
{
  return time_total;
}

vector<Real> DopplerCalculatorByNjoyInput::get_time_each_mat()
{
  return time_each_mat;
}

vector<vector<Real> > DopplerCalculatorByNjoyInput::get_time_each_temp()
{
  return time_each_temp;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
